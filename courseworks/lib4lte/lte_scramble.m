function out = lte_scramble(pusch_coding_bit,vrb_num,qm,subframeno,ue_index,cellid)

cinit = 0;
out = [];
N_rnti = ue_index;
ns = subframeno * 2;
cinit = N_rnti * 2^14 + floor(ns/2) * 2^9 + cellid;
out = [out,mod(pseudo_random_seq_gen(cinit,length(pusch_coding_bit))+pusch_coding_bit,2)];
end