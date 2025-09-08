#ifndef TASK_1_H
#define TASK_1_H

#include "math.h"
#include "Globe.h"
#include "Type.h"

int upper_bound(int arr[], int size, int target)
{
  int left = 0, right = size;
  while (left < right)
  {
    int mid = left + (right - left) / 2;
    if (arr[mid] < target)
      left = mid + 1;
    else
      right = mid;
  }
  // left即为第一个大于等于target的元素下标，若left==size则没有比target大的元素
  return left;
}

// add 3GPP CRC24A
int CRCAdd(int *poutbit, int *ptempinput, unsigned int udBitLen)
{
  // CRC24A
  int L = 24;
  // 生成多项式
  int *poly = &G;
  int i = 0;
  int j = 0;

  for (i = 0; i < udBitLen; i++)
  {
    ptempinput[i] = poutbit[i];
  }

  for (i = 0; i < udBitLen - 24; i++)
  {
    // 寻找不为零的
    if (ptempinput[i] == 1)
    {
      // 每一位进行异或操作
      for (j = 0; j < 25; j++)
      {
        ptempinput[i + j] ^= poly[j];
      }
    }
  }
  // 将计算出来的校验码添加到数据后面
  for (i = udBitLen - 24; i < udBitLen; i++)
  {
    poutbit[i] = ptempinput[i];
  }
  return 0;
}

int CRCbAdd(int *poutbit, int *ptempinput,
            unsigned int udBitLen)
{
  // CRC24B
  int L = 24;
  // 生成多项式
  int *poly = &G1;
  int i = 0;
  int j = 0;
  for (i = 0; i < udBitLen; i++)
  {
    ptempinput[i] = poutbit[i];
  }

  for (i = 0; i < udBitLen - 24; i++)
  {
    // 寻找不为零的
    if (ptempinput[i] == 1)
    {
      // 每一位进行异或操作
      for (j = 0; j < 25; j++)
      {
        ptempinput[i + j] ^= poly[j];
      }
    }
  }
  // 将计算出来的校验码添加到数据后面
  for (i = udBitLen - 24; i < udBitLen; i++)
  {
    poutbit[i] = ptempinput[i];
  }
  return 0;
}
int cdblockseg(int *pcodeblockbit,
               int *pinputbit,
               int *ptempbit,
               unsigned int udbitlen)
{
  unsigned int K[] = {40, 48, 56, 64, 72, 80, 88, 96, 104, 112, 120, 128, 136, 144, 152, 160, 168, 176, 184, 192, 200, 208, 216, 224, 232, 240, 248, 256, 264, 272, 280, 288, 296, 304, 312, 320, 328, 336, 344, 352, 360, 368, 376, 384, 392, 400, 408, 416, 424, 432, 440, 448, 456, 464, 472, 480, 488, 496, 504, 512, 528, 544, 560, 576, 592, 608, 624, 640, 656, 672, 688, 704, 720, 736, 752, 768, 784, 800, 816, 832, 848, 864, 880, 896, 912, 928, 944, 960, 976, 992, 1008, 1024, 1056, 1088, 1120, 1152, 1184, 1216, 1248, 1280, 1312, 1344, 1376, 1408, 1440, 1472, 1504, 1536, 1568, 1600, 1632, 1664, 1696, 1728, 1760, 1792, 1824, 1856, 1888, 1920, 1952, 1984, 2016, 2048, 2112, 2176, 2240, 2304, 2368, 2432, 2496, 2560, 2624, 2688, 2752, 2816, 2880, 2944, 3008, 3072, 3136, 3200, 3264, 3328, 3392, 3456, 3520, 3584, 3648, 3712, 3776, 3840, 3904, 3968, 4032, 4096, 4160, 4224, 4288, 4352, 4416, 4480, 4544, 4608, 4672, 4736, 4800, 4864, 4928, 4992, 5056, 5120, 5184, 5248, 5312, 5376, 5440, 5504, 5568, 5632, 5696, 5760, 5824, 5888, 5952, 6016, 6080, 6144};
  int K_arr_size = sizeof(K) / sizeof(K[0]);
  unsigned int Z = 6144;
  unsigned int B = udbitlen; // 信息bit数
  unsigned int L = 0;        // CRC长度
  unsigned int C = 0;        // 码块数量
  unsigned int F = 0;        // 填充比特数量
  unsigned int Kp = 0;
  unsigned int Km = 0;
  unsigned int Cp = 0;
  unsigned int Cm = 0;
  unsigned int r = 0;
  unsigned int B_prime = 0;
  unsigned int delta_K = 0;
  unsigned int idx = 0;
  unsigned int s = 0;
  unsigned int k = 0;
  // 计算码块数和发送bit数
  if (B <= Z)
  {
    L = 0;
    C = 1;
    B_prime = B;
  }
  else
  {
    L = 24;
    C = (unsigned int)ceil((double)B / (Z - L)); // 向上取整
    B_prime = B + C * L;
  }

  // 寻找合适的Kp
  idx = upper_bound(K, K_arr_size, (int)ceil((double)B_prime / C));
  if (idx >= K_arr_size)
  {
    idx = K_arr_size - 1;
  }
  Kp = K[idx];

  if (C == 1)
  {
    Cp = 1;
    Km = 0;
    Cm = 0;
  }
  else if (C > 1)
  {
    Km = K[idx - 1];
    delta_K = Kp - Km;
    Cm = (unsigned int)floor((double)(C * Kp - B_prime) / delta_K);
    Cp = C - Cm;
  }

  F = Cp * Kp + Cm * Km - B_prime;

  // 码块分割
  k = F;
  s = 0;
  // 根据对数组的理解不同可能需要修改部K_r的值为6144.
  for (r = 0; r < C; r++)
  {
    unsigned int K_r = (r < Cm) ? Km : Kp;
    // 前F个填充比特
    if (r == 0 && k > 0)
    {
      // 填充比特可用特殊值标记，这里用-1
      for (unsigned int i = 0; i < k; i++)
        pcodeblockbit[r * Z + i] = -1;
      for (unsigned int i = k; i < K_r - L; i++)
      {
        pcodeblockbit[r * Z + i] = pinputbit[s + i - k];
      }
      s += K_r - L - k;
    }
    else
    {
      for (unsigned int i = 0; i < K_r - L; i++)
      {
        pcodeblockbit[r * Z + i] = pinputbit[s + i];
      }
      s += K_r - L;
    }
    // CRC24B添加
    if (C > 1)
    {
      CRCbAdd(&pcodeblockbit[r * Z + K_r - L], ptempbit, K_r);
    }
    k = 0;
  }

  return 0;
}

#endif