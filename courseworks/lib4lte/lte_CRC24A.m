function par24A = lte_CRC24A(inf_bits)
% function par24A = lte_CRC24a(inf_bits)
% CRC of type 24a generator function,
% specification ref. to 3GPP TS 36.212 ch.5.2.2
%
% input:
%     inf_bits, vector of binary number
% output:
%     par24a, vector of parity bits with length 24
% 
% author: xxx,  
% date: sept. 3rd, 2024

c = inf_bits;
L = 24;
poly = [1 1 0 0 0 0 1 1 0 0 1 0 0 1 1 0 0 1 1 1 1 1 0 1 1];

%末尾补零
c = [inf_bits(:).' zeros(1, L)];
msg_len = length(inf_bits);

%多项式除法
for i = 1:msg_len
    if c(i) == 1
        c(i:i+L) = xor(c(i:i+L), poly);
    end
end

%余数为最后24位
par24A = c(end-L+1:end);
end





