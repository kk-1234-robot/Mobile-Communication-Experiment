/*
 * main.c
 */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include <ti/dsplib/dsplib.h>
#include "..\Include\Fun.h"
#include "..\Include\Globe.h"
#include "..\Include\Type.h"

int main(void)
{

  int tbsize = 57336;
  int udbitlength = 0;

  int *ptempbit = NULL;
  int *poutbit = NULL;
  int *pcdblocksegbit = NULL;

  // ���ֶ���ز���
  int C = 0, Kp = 0, Km = 0, Cp = 0, Cm = 0, F = 0;

  udbitlength = tbsize + 24; /*CRCУ��λ����*/

  /*CRC*/
  ptempbit = &InterweaveData[0]; /*��֯bufferָ��*/
  poutbit = &OriginalBuffer[0];
  CRCAdd(poutbit, ptempbit, tbsize);

  /*���ֶ�*/
  pcdblocksegbit = &CodeBlockBit[0][0];
  poutbit = &OriginalBuffer[0];
  ptempbit = &InterweaveData[0]; /*��֯bufferָ��*/
  cdblockseg(pcdblocksegbit, poutbit, ptempbit, udbitlength);

  // �����ֶ���ز�������
  C = ptempbit[0];
  Kp = ptempbit[1];
  Km = ptempbit[2];
  Cp = ptempbit[3];
  Cm = ptempbit[4];
  F = ptempbit[5];

  int *TurboEncodedBits = (int *)malloc((Kp + 4) * C * 3 * sizeof(int));

  int *C_len = (int *)malloc(C * sizeof(int));

  int prb_num = 100;
  int module_type = 3;
  int Qm = 2 * module_type; // 64QAM
  int UL_subframe_num = 2;
  int ue_index = 60;
  int cellid = 0;

  int channel_type = 1;
  int Nir = 0;
  int direction = 1;
  int Rvdix = 0;
  int Nl = 1;
  int G = 12 * 12 * prb_num * Qm;

  int cfi = 1;
  int cp_type = 0;

  /*Turbo����*/
  // ���ΪTurboEncodedBits�� ����Ϊpcdblocksegbit��ptempbit��Ϊ��ʱbuffer
  TurboEncode(pcdblocksegbit, ptempbit, TurboEncodedBits, C, Kp, Km, Cm, F);
  /*LTE ����ƥ��*/
  // ���Ϊptempbit�� ����ΪTurboEncodedBits
  LTE_RateMatch(TurboEncodedBits, ptempbit, C_len, channel_type, Nir, C, Cm,
                direction, module_type, Rvdix, Nl, G, Km, Kp);
  free(TurboEncodedBits);

  /*LTE �ŵ�����鼶��*/
  int *ccbcSym = (int *)malloc(3 * (Kp + 4) * C * sizeof(int));
  int ccbcLen = 0;
  LTE_CB_concat(C, ptempbit, C_len, ccbcSym, &ccbcLen, Kp);

  free(ccbcSym);

  return 0;
}
