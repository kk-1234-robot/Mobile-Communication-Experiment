%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Subblock_interleave subfunction of RateMatch according 3gpp 36212
% Info_data: the input data for subblock interleave
% intl_mode: 0 for turbo coded transport channel d0 and d1 branch
%            1 for turbo coded transport channel d2 branch
%            2 for convolutional coded tansport channel
% Note: input data must be 1 stream.
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function Output = Subblock_interleave_index(Info_data, intl_mode)
if (intl_mode  == 0)||(intl_mode == 1)
    Col_intl = [0, 16, 8, 24, 4, 20, 12, 28, 2, 18, 10, 26, 6, 22, 14, 30, 1, 17, 9, 25, 5, 21, 13, 29, 3, 19, 11, 27, 7, 23, 15, 31];
    Col_intl = Col_intl + 1;
else
    Col_intl = [1, 17, 9, 25, 5, 21, 13, 29, 3, 19, 11, 27, 7, 23, 15, 31, 0, 16, 8, 24, 4, 20, 12, 28, 2, 18, 10, 26, 6, 22, 14, 30];
    Col_intl = Col_intl + 1;
end    
        
Col_len = 32;
