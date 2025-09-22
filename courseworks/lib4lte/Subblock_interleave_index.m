%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Subblock_interleave subfunction of RateMatch according 3gpp 36212
% Info_data: the input data for subblock interleave
% intl_mode: 0 for turbo coded transport channel d0 and d1 branch
%            1 for turbo coded transport channel d2 branch
%            2 for convolutional coded tansport channel
% Note: input data must be 1 stream.
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function [Output,Row_len] = Subblock_interleave_index(Info_data, intl_mode)
if (intl_mode  == 0)||(intl_mode == 1)
    Col_intl = [0, 16, 8, 24, 4, 20, 12, 28, 2, 18, 10, 26, 6, 22, 14, 30, 1, 17, 9, 25, 5, 21, 13, 29, 3, 19, 11, 27, 7, 23, 15, 31];
    Col_intl = Col_intl + 1;
else
    Col_intl = [1, 17, 9, 25, 5, 21, 13, 29, 3, 19, 11, 27, 7, 23, 15, 31, 0, 16, 8, 24, 4, 20, 12, 28, 2, 18, 10, 26, 6, 22, 14, 30];
    Col_intl = Col_intl + 1;
end    
        
Col_len = 32;
%每个数据流的bit数，K+4
len = length(Info_data(1,:));
Row_len = ceil(len/Col_len);
c = zeros(1,Row_len*Col_len);
index = 0;
if len < Col_len * Row_len
    index =Col_len * Row_len - len;
    c(:,1:index) = nan;
end
K_pi = Col_len * Row_len;
PI_index = mod((Col_intl(floor((0:1:K_pi - 1) / Row_len) + 1) - 1 + Col_len .* mod((0:1:K_pi - 1),Row_len) + 1),K_pi) + 1;

if intl_mode == 0
c(1,index + 1:1:end) = Info_data(1,:);
c = reshape(c,Col_len,Row_len)';
c_prime(:,:) = c(:,Col_intl);
c_prime = reshape(c_prime,1,[]);
Output(1,:) = c_prime;
elseif intl_mode == 1
c(1,index+1:1:end) = Info_data(1,:);
c_prime(1,1:1:length(c)) = c(1,PI_index);
Output(1,:) = c_prime;
end

end