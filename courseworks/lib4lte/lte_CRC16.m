function par16 = lte_CRC16(inf_bits)
% function par16 = lte_CRC16(inf_bits)
% CRC of type 16 generator function,
% specification ref. to 3GPP TS 36.212 ch.5.2.2
%
% input:
%     inf_bits, vector of binary number
% output:
%     par16, vector of parity bits with length 16
% 
% author: xxx,  
% date: sept. 3rd, 2024

c = inf_bits;
L = 16;
poly = [1 0 0 0 1 0 0 0 0 0 0 1 0 0 0 0 1];

%末尾补零
c = [inf_bits(:).' zeros(1, L)];
msg_len = length(inf_bits);

%多项式除法
for i = 1:msg_len
    if c(i) == 1
        c(i:i+L) = xor(c(i:i+L), poly);
    end
end

%余数为最后16位
par16 = c(end-L+1:end);
end





