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


[v0,Row_len] = Subblock_interleave_index(Info_data(1,:),0);
[v1,Row_len] = Subblock_interleave_index(Info_data(2,:),0);
[v2,Row_len] = Subblock_interleave_index(Info_data(3,:),1);

W_k = [v0,reshape([v1;v2],1,[])];
Kw = length(W_k);

if direction == 0
    N_cb = min(floor(Nir/C),Kw);
else
    N_cb = Kw;
end

Qm = 2*module_type;

G_prime = G/(Nl * Qm);%64QAM
gamma_my = mod (G_prime,C);
if r <= C - gamma_my - 1
    E = Nl*Qm*floor(G_prime/C);
else
    E = Nl*Qm*ceil(G_prime/C);
end

k_0 = Row_len * (2*ceil(N_cb/(8*Row_len))*RVidx + 2);

k = 0; j = 0;
while k < E
    if  isnan(W_k(mod(k_0 + j,N_cb) + 1)) == 0
        e(k+1) = W_k(mod(k_0 + j,N_cb) + 1);
        k = k + 1;
    end
    j = j+ 1;
end

Output = e;
out_len = length(e);


end