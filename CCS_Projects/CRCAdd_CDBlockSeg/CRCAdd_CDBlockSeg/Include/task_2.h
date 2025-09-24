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
              int Nir, int C, int module_type, int Rvdix, int Nl, int G, int block_idx);

int SubblockInterleaver(int *input_bits, int *output_bits, int input_len, int intl_mode);

#endif