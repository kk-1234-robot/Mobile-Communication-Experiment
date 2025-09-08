% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Info_data-----Information data input to Rate Matching module
%               the input data must have 3 streams.
% Channel_type------0 for turbo coded transport channel, 
%                   1 for convolutional coded transport channel.
% Nir-----Soft buffer size
%----Parameter list below is Only used for turbo coded channel
% C ---- code block number
% direction ----- 0 for downlink, 1 for uplink
% module_type ----- 1 for QPSK, 2 for 16QAM, 3 for 64QAM
% RVidx ----- redundancy version number(0/1/2/3)
% Nl ----- transmission layer 1~1layer 2~2/4layer (1/2)
% G ----- total number of bits available for the transmission of one transport channel
% r ----- rth coded block input to rate matching module(begin with 0 according to 3gpp)
% output: data bit after ratematching
% out_len: data length after ratematching

function [Output,out_len] = RateMatching(Info_data, Channel_type, Nir, C, direction, module_type, RVidx, Nl, G, r)

