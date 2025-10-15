#include "..\Include\task_2.h"
#include "..\Include\Fun.h"
#include "..\Include\Globe.h"
#include "..\Include\Type.h"
#include "math.h"


int Int_matrix[3][188] = {
    {40,   48,   56,   64,   72,   80,   88,   96,   104,  112,  120,  128,
     136,  144,  152,  160,  168,  176,  184,  192,  200,  208,  216,  224,
     232,  240,  248,  256,  264,  272,  280,  288,  296,  304,  312,  320,
     328,  336,  344,  352,  360,  368,  376,  384,  392,  400,  408,  416,
     424,  432,  440,  448,  456,  464,  472,  480,  488,  496,  504,  512,
     528,  544,  560,  576,  592,  608,  624,  640,  656,  672,  688,  704,
     720,  736,  752,  768,  784,  800,  816,  832,  848,  864,  880,  896,
     912,  928,  944,  960,  976,  992,  1008, 1024, 1056, 1088, 1120, 1152,
     1184, 1216, 1248, 1280, 1312, 1344, 1376, 1408, 1440, 1472, 1504, 1536,
     1568, 1600, 1632, 1664, 1696, 1728, 1760, 1792, 1824, 1856, 1888, 1920,
     1952, 1984, 2016, 2048, 2112, 2176, 2240, 2304, 2368, 2432, 2496, 2560,
     2624, 2688, 2752, 2816, 2880, 2944, 3008, 3072, 3136, 3200, 3264, 3328,
     3392, 3456, 3520, 3584, 3648, 3712, 3776, 3840, 3904, 3968, 4032, 4096,
     4160, 4224, 4288, 4352, 4416, 4480, 4544, 4608, 4672, 4736, 4800, 4864,
     4928, 4992, 5056, 5120, 5184, 5248, 5312, 5376, 5440, 5504, 5568, 5632,
     5696, 5760, 5824, 5888, 5952, 6016, 6080, 6144},
    {3,   7,   19,  7,   7,   11,  5,   11,  7,   41,  103, 15,  9,   17,  9,
     21,  101, 21,  57,  23,  13,  27,  11,  27,  85,  29,  33,  15,  17,  33,
     103, 19,  19,  37,  19,  21,  21,  115, 193, 21,  133, 81,  45,  23,  243,
     151, 155, 25,  51,  47,  91,  29,  29,  247, 29,  89,  91,  157, 55,  31,
     17,  35,  227, 65,  19,  37,  41,  39,  185, 43,  21,  155, 79,  139, 23,
     217, 25,  17,  127, 25,  239, 17,  137, 215, 29,  15,  147, 29,  59,  65,
     55,  31,  17,  171, 67,  35,  19,  39,  19,  199, 21,  211, 21,  43,  149,
     45,  49,  71,  13,  17,  25,  183, 55,  127, 27,  29,  29,  57,  45,  31,
     59,  185, 113, 31,  17,  171, 209, 253, 367, 265, 181, 39,  27,  127, 143,
     43,  29,  45,  157, 47,  13,  111, 443, 51,  51,  451, 257, 57,  313, 271,
     179, 331, 363, 375, 127, 31,  33,  43,  33,  477, 35,  233, 357, 337, 37,
     71,  71,  37,  39,  127, 39,  39,  31,  113, 41,  251, 43,  21,  43,  45,
     45,  161, 89,  323, 47,  23,  47,  263},
    {10,  12,  42,  16,  18,  20,  22,  24,  26,  84,  90,  32,  34,  108, 38,
     120, 84,  44,  46,  48,  50,  52,  36,  56,  58,  60,  62,  32,  198, 68,
     210, 36,  74,  76,  78,  120, 82,  84,  86,  44,  90,  46,  94,  48,  98,
     40,  102, 52,  106, 72,  110, 168, 114, 58,  118, 180, 122, 62,  84,  64,
     66,  68,  420, 96,  74,  76,  234, 80,  82,  252, 86,  44,  120, 92,  94,
     48,  98,  80,  102, 52,  106, 48,  110, 112, 114, 58,  118, 60,  122, 124,
     84,  64,  66,  204, 140, 72,  74,  76,  78,  240, 82,  252, 86,  88,  60,
     92,  846, 48,  28,  80,  102, 104, 954, 96,  110, 112, 114, 116, 354, 120,
     610, 124, 420, 64,  66,  136, 420, 216, 444, 456, 468, 80,  164, 504, 172,
     88,  300, 92,  188, 96,  28,  240, 204, 104, 212, 192, 220, 336, 228, 232,
     236, 120, 244, 248, 168, 64,  130, 264, 134, 408, 138, 280, 142, 480, 146,
     444, 120, 152, 462, 234, 158, 80,  96,  902, 166, 336, 170, 86,  174, 176,
     178, 120, 182, 184, 186, 94,  190, 480}};

int TurboEncode(int *pinputbit, int *ptempbit, int *poutputbit, int C, int Kp,
                int Km, int Cm, int F) {
  int i = 0;
  int index[12] = {3, 1, 9, 7, 0, 5, 6, 11, 4, 2, 9, 10}; // 交织顺序
  for (i = 0; i < F; i++) {
    pinputbit[i] = 0; // 将填充位设为0
  }

  // 计算每个码块的数据长度
  int *data_len = (int *)malloc(C * sizeof(int));
  for (i = 0; i < C; i++) {
    if (i < Cm) {
      data_len[i] = Km;
    } else {
      data_len[i] = Kp;
    }
  }

  // 交织
  for (i = 0; i < C; i++) {
    interleaver(&pinputbit[i * Kp], &ptempbit[i * Kp], data_len[i]);
  }

  // RSC编码
  int *tail_bits = (int *)malloc(12 * sizeof(int));
  int j = 0;
  for (i = 0; i < C; i++) {
    for (j = 0; j < data_len[i]; j++) {
      poutputbit[i * (Kp + 4) * 3 + j] = pinputbit[i * Kp + j]; // 系统比特
    }
    rsc_encode(&pinputbit[i * Kp], &poutputbit[i * (Kp + 4) * 3 + Kp + 4],
               tail_bits, data_len[i]);
    rsc_encode(&ptempbit[i * Kp], &poutputbit[i * (Kp + 4) * 3 + 2 * (Kp + 4)],
               &tail_bits[6], data_len[i]);
    // 添加尾比特
    for (j = 0; j < 4; j++) {
      poutputbit[i * (Kp + 4) * 3 + j + data_len[i]] = tail_bits[index[j]];
      poutputbit[i * (Kp + 4) * 3 + Kp + 4 + j + data_len[i]] =
          tail_bits[index[j + 4]];
      poutputbit[i * (Kp + 4) * 3 + 2 * (Kp + 4) + j + data_len[i]] =
          tail_bits[index[j + 8]];
    }
    if (i == 0 && F > 0) {
      for (j = 0; j < F; j++) {
        poutputbit[i * (Kp + 4) * 3 + j] = -1;          // 将填充位设为-1
        poutputbit[i * (Kp + 4) * 3 + Kp + 4 + j] = -1; // 将填充位设为-1
      }
    }
  }
  free(data_len);
  free(tail_bits);
  return 0;
}

int interleaver(int *input_bits, int *output_bits, int K) {
  int i = 0;
  // 使用upper_bound函数找到合适的列值
  int col = upper_bound(Int_matrix[0], 188, K);
  int f_1 = Int_matrix[1][col];
  int f_2 = Int_matrix[2][col];
  int *Pi_index = (int *)malloc(K * sizeof(int));
  for (i = 0; i < K; i++) {
    Pi_index[i] = (f_1 * i + f_2 * i * i) % K;
    output_bits[i] = input_bits[Pi_index[i]];
  }
  free(Pi_index);
  return 0;
}

int rsc_encode(int *input_bits, int *output_bits, int *out_tail_bits, int K) {
  // RSC 编码器状态寄存器
  int registers[4] = {0};
  // 生成多项式
  int g1[] = {1, 0, 1, 1};
  int g2[] = {1, 1, 0, 1};
  int i = 0;
  int in = 0;
  for (i = 0; i < K; i++) {
    registers[0] = input_bits[i];
    in = (registers[0] * g1[0]) ^ (registers[1] * g1[1]) ^
         (registers[2] * g1[2]) ^ (registers[3] * g1[3]);
    output_bits[i] = (in * g2[0]) ^ (registers[1] * g2[1]) ^
                     (registers[2] * g2[2]) ^ (registers[3] * g2[3]);
    // 更新寄存器状态
    registers[3] = registers[2];
    registers[2] = registers[1];
    registers[1] = in;
  }
  for (i = 0; i < 3; i++) {
    int in = 0;
    out_tail_bits[i] = (in * g2[0]) ^ (registers[1] * g2[1]) ^
                       (registers[2] * g2[2]) ^ (registers[3] * g2[3]);
    out_tail_bits[i + 3] = (registers[2] * g1[2]) ^ (registers[3] * g1[3]);
    // 更新寄存器状态
    registers[3] = registers[2];
    registers[2] = registers[1];
    registers[1] = in;
  }
  return 0;
}

int LTE_RateMatch(int *input_codedata, int *rmdata, int *rmlen,
                  int channel_type, int Nir, int C, int Cm, int direction,
                  int module_type, int Rvdix, int Nl, int G, int Km, int Kp) {
  int i = 0;
  // 计算每个码块的编码长度
  int *code_len = (int *)malloc((C) * sizeof(int));
  for (i = 0; i < C; i++) {
    if (i < Cm) {
      code_len[i] = Km + 4;
    } else {
      code_len[i] = Kp + 4;
    }
    RateMatch(&input_codedata[i * (Kp + 4) * 3], code_len[i],
              &rmdata[i * 3 * (Kp + 4)], &rmlen[i], channel_type, Nir, C,
              direction, module_type, Rvdix, Nl, G, i, Km, Kp);
  }
  return 0;
}

int RateMatch(int *input_codedata, int input_len, int *out_data, int *out_len,
              int channel_type, int Nir, int C, int direction, int module_type,
              int Rvdix, int Nl, int G, int block_idx, int Km, int Kp) {
  int Row_len = 0;
  int K_w = 3 * input_len;
  int *temp_bits = (int *)malloc(K_w * sizeof(int));
  int *temp_bits_interleaved = (int *)malloc(2 * input_len * sizeof(int));
  SubblockInterleaver(&input_codedata[0], &temp_bits[0], input_len, 0,
                      &Row_len);
  SubblockInterleaver(&input_codedata[Kp + 4], &temp_bits[input_len], input_len,
                      0, &Row_len);
  SubblockInterleaver(&input_codedata[2 * (Kp + 4)], &temp_bits[2 * input_len],
                      input_len, 1, &Row_len);

  int i = 0;

  for (i = 0; i < 2 * input_len; i++) {
    temp_bits_interleaved[i] = i % 2 == 0 ? temp_bits[input_len + i / 2]
                                          : temp_bits[2 * input_len + i / 2];
  }
  memcpy(&temp_bits[input_len], &temp_bits_interleaved[0],
         2 * input_len * sizeof(int));
  free(temp_bits_interleaved);

  int N_cb = 0;
  if (direction == 0) {
    N_cb = fmin(floor((double)Nir / C), K_w);
  } else {
    N_cb = K_w;
  }

  int Q_m = 2 * module_type;

  int G_prime = G / (Nl * Q_m);
  int gamma = G_prime % C;
  int E = 0;
  if (block_idx <= C - gamma - 1)
    E = Nl * Q_m * floor((double)G_prime / C);
  else
    E = Nl * Q_m * ceil((double)G_prime / C);

  int K_0 = Row_len * (2 * ceil((double)N_cb / (8 * Row_len)) * Rvdix + 2);

  int k = 0, j = 0;

  *out_len = 0;
  for (k = 0, j = 0; k < E; j++) {
    if (temp_bits[(K_0 + j) % N_cb] != -1) // 跳过填充位
    {
      out_data[k] = temp_bits[(K_0 + j) % N_cb];
      k++;
      (*out_len)++;
    } else {
      j++;
    }
  }
  return 0;
}

int SubblockInterleaver(int *input_bits, int *output_bits, int input_len,
                        int intl_mode, int *Row_len) {
  int Col_intl[32];
  if (intl_mode == 0 || intl_mode == 1) {
    int tmp[32] = {0, 16, 8, 24, 4, 20, 12, 28, 2, 18, 10, 26, 6, 22, 14, 30,
                   1, 17, 9, 25, 5, 21, 13, 29, 3, 19, 11, 27, 7, 23, 15, 31};
    memcpy(Col_intl, tmp, sizeof(tmp));
  } else {
    int tmp[32] = {1, 17, 9, 25, 5, 21, 13, 29, 3, 19, 11, 27, 7, 23, 15, 31,
                   0, 16, 8, 24, 4, 20, 12, 28, 2, 18, 10, 26, 6, 22, 14, 30};
    memcpy(Col_intl, tmp, sizeof(tmp));
  }
  int col_len = 32;
  int row_len = ceil((double)input_len / col_len);
  int K_pi = row_len * col_len; // 补齐后的长度
  int start_index = K_pi - input_len;
  int i = 0;
  if (start_index > 0) {
    for (i = 0; i < start_index; i++) {
      output_bits[i] = -1; // 用-1填充
    }
  }

  int j = 0;
  if (intl_mode == 0) {
    for (i = 0; i < row_len; i++) {
      for (j = 0; (j < col_len) && (i * col_len + j + start_index < K_pi);
           j++) {
        output_bits[i * col_len + j + start_index] =
            input_bits[i * col_len + Col_intl[j]];
      }
    }
  } else if (intl_mode == 1) {
    int *Pi_index = (int *)malloc(K_pi * sizeof(int));
    for (i = 0; i < K_pi; i++) {
      Pi_index[i] = (Col_intl[(int)floor((double)i / row_len)] - 1 +
                     ((i % row_len)) * col_len + 1) %
                    K_pi;
    }
    for (i = 0; i < input_len - start_index; i++) {
      output_bits[i + start_index] = input_bits[Pi_index[i]];
    }
    free(Pi_index);
  }
  *Row_len = row_len;

  return 0;
}

int LTE_CB_concat(int C, int *input_sym, int *C_len, int *output_sym,
                  int *output_len, int Kp) {
  int i = 0, j = 0;
  int pos = 0;
  for (i = 0; i < C; i++) {
    for (j = 0; j < C_len[i]; j++) {
      output_sym[pos] = input_sym[i * 3 * (Kp + 4) + j];
      pos++;
    }
  }
  *output_len = pos;
  return 0;
}

int LTE_interleaver(int *data_in, int prb_num, int Qm, int *data_out,
                    int *out_len) {
  int symb_len = prb_num * 12 * Qm;
  int data_len = prb_num * 144 * Qm;
  int data_row = data_len / (12 * Qm);
  int count = 0;
  int index = 0;
  int len = 0;

  int i = 0, j = 0;
  for (i = 0; i < 12; i++) {
    for (j = 0; j < data_row; j++) {
      index = j * 12 * Qm + i * Qm;
      for (count = 0; count < Qm; count++) {
        data_out[count + len] = data_in[index + count];
      }
      len = len + Qm;
    }
  }

  *out_len = len;
  return 0;
}

int lte_scramble(int *intlvSym, int input_len, int vrb_num, int Qm,
                 int subframeno, int ue_index, int cell_id, int *scramble_Sym) {
  int cinit = 0;
  int N_rnti = ue_index;
  int ns = subframeno * 2;
  cinit = N_rnti * (1 << 14) + floor((double)ns / 2) * (1 << 9) + cell_id;
  int i = 0;
  int *prbs = (int *)malloc(input_len * sizeof(int));
  int prbs_len = 0;
  pseudo_random_seq_gen(cinit, input_len, prbs, &prbs_len);
  for (i = 0; i < input_len; i++) {
    scramble_Sym[i] = intlvSym[i] ^ prbs[i];
  }
  free(prbs);
  return 0;
}

int pseudo_random_seq_gen(int init_value, int length, int *output_seq,
                          int *output_len) {
  int x1[31] = {0};
  int x2[31] = {0};
  int i = 0;
  int Nc = 1600;
  x1[0] = 1;
  for (i = 0; i < 31; i++) {
    x2[i] = (init_value >> i) & 0x01;
  }
  for (i = 0; i < length + Nc - 31 - 1; i++) {
    x1[i + 31] = (x1[i + 3] + x1[i]) % 2;
    x2[i + 31] = (x2[i + 3] + x2[i + 2] + x2[i + 1] + x2[i]) % 2;
  }
  for (i = 0; i < length; i++) {
    output_seq[i] = (x1[i + Nc] + x2[i + Nc]) % 2;
  }
  *output_len = length;
  return 0;
}