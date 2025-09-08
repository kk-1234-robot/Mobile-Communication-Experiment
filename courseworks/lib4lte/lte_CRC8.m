function par8 = lte_CRC8(inf_bits)
% function par8 = lte_CRC8(inf_bits)
% CRC of type 8 generator function,
% specification ref. to 3GPP TS 36.212 ch.5.2.2
%
% input:
%     inf_bits, vector of binary number
% output:
%     par8, vector of parity bits with length 8
% 
% author: xxx,  
% date: sept. 3rd, 2024

c = inf_bits;
L = 8;
poly = [1 1 0 0 1 1 0 1 1];

%末尾补零
c = [inf_bits(:).' zeros(1, L)];
msg_len = length(inf_bits);

%多项式除法
for i = 1:msg_len
    if c(i) == 1
        c(i:i+L) = xor(c(i:i+L), poly);
    end
end

%余数为最后8位
par8 = c(end-L+1:end);
end





