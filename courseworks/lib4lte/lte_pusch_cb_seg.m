function [Cp, Kp, Cm, Km, F, cdblkseg_data] =  lte_pusch_cb_seg(tbCrcBits)
% function [Cp, Kp, Cm, Km, F, cdblkseg_data] =  lte_pusch_cb_seg(tbCrcBits)
% Code block segmentation function,
% specification ref. to 3GPP TS 36.212 ch.5.1.2
%
% input:
%   tbCrcBits, vector of binary, TB of information bits with CRC24A attached
% output:
%   Cp, C+ in specification
%   Kp, K+ in specification
%   Cm, C- in specification
%   Km, K- in specification
%   F, F in specification
%   cdblkseg_data, output of segmentation result

% function [Cp, Kp, Cm, Km, F, Out_data] = Cdblk_seg1(Info_data)

Info_data = tbCrcBits;

K = [40 48 56 64 72 80 88 96 104 112 120 128 136 144 152 ...
     160 168 176 184 192 200 208 216 224 232 240 248 256 ...
     264 272 280 288 296 304 312 320 328 336 344 352 360 ...
     368 376 384 392 400 408 416 424 432 440 448 456 464 ...
     472 480 488 496 504 512 528 544 560 576 592 608 624 ...
     640 656 672 688 704 720 736 752 768 784 800 816 832 ...
     848 864 880 896 912 928 944 960 976 992 1008 1024 ...
     1056 1088 1120 1152 1184 1216 1248 1280 1312 1344 ...
     1376 1408 1440 1472 1504 1536 1568 1600 1632 1664 ...
     1696 1728 1760 1792 1824 1856 1888 1920 1952 1984 ...
     2016 2048 2112 2176 2240 2304 2368 2432 2496 2560 ...
     2624 2688 2752 2816 2880 2944 3008 3072 3136 3200 ...
     3264 3328 3392 3456 3520 3584 3648 3712 3776 3840 ...
     3904 3968 4032 4096 4160 4224 4288 4352 4416 4480 ...
     4544 4608 4672 4736 4800 4864 4928 4992 5056 5120 ...
     5184 5248 5312 5376 5440 5504 5568 5632 5696 5760 ...
     5824 5888 5952 6016 6080 6144];

Z = 6144;

%计算码块数、总发送bit数
B = length(Info_data);
if B <= Z
    L = 0;
    C = 1;
    B_ = B;
else
    L = 24;
    C = ceil(B/(Z - L));
    B_ = B + C * L;
end

positon = find(K > (B_ / C));
Kp = K(1, positon(1,1));

if C == 1
    Cp = 1;
    km = 0;
    Cm = 0;
elseif C > 1
    Km = K(1, positon(1,1) - 1);
    delta_K = Kp -  Km;
    Cm = floor((C * Kp - B_)/delta_K);
    Cp = C - Cm;
end

F = Cp * Kp + Cm * Km - B_;

k = F;
s = 0;
for r = 0: C-1
    if r < Cm
        K_r = Km;
    else
        K_r = Kp;
    end
    if r == 0 && k > 0
        c(r+1, 1:1:k) = NAN;
        c(r + 1,1 + k:1:K_r - L) = tbCrcBits(1, s+1:1:s+K_r - L - k);
        s = s + K_r - L - k;
    else
        c(r + 1,1:1:K_r - L) = tbCrcBits(1, s+1:1:s+K_r - L);
        s = s + K_r - L;
    end
    if C > 1
        c(r + 1, K_r - L + 1 + k: 1: K_r + k) = lte_CRC24B(c(r+1,1:1:K_r - L));
    end
    k = 0;
end

cdblkseg_data = reshape(c, 1,[]);

end



