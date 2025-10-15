#ifndef TASK_2_H
#define TASK_2_H

// 函数声明
// Turbo编码函数
int TurboEncode(int *pinputbit, int *ptempbit, int *poutputbit, int C, int Kp, int Km, int Cm, int F);
int interleaver(int *input_bits, int *output_bits, int K);
int rsc_encode(int *input_bits, int *output_bits, int *tail_bits, int K);

// 速率匹配函数
int LTE_RateMatch(int *input_codedata, int *rmdata, int *rmlen, int channel_type,
                  int Nir, int C, int Cm, int direction, int module_type,
                  int Rvdix, int Nl, int G, int Km, int Kp);
int RateMatch(int *input_codedata, int input_len, int *out_data, int *out_len, int channel_type,
              int Nir, int C, int direction, int module_type, int Rvdix, int Nl, int G, int block_idx, int Km, int Kp);

int SubblockInterleaver(int *input_bits, int *output_bits, int input_len, int intl_mode, int *Row_len);

int LTE_CB_concat(int C, int *input_sym, int *C_len, int *output_sym, int *output_len, int Kp);

int LTE_interleaver(int *data_in, int prb_num, int Qm, int *data_out, int *out_len);

int lte_scramble(int *intlvSym, int input_len, int vrb_num, int Qm,
                 int subframeno, int ue_index, int cell_id, int *scramble_Sym);

int pseudo_random_seq_gen(int init_value, int length, int *output_seq, int *output_len);

#endif