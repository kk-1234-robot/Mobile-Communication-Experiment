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
#include "..\Include\task_1.h"
#include "..\Include\task_2.h"

int main(void) {

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

  /*LTE ����ƥ�����ؽ�֯*/
  int *intlvSym = (int *)malloc(ccbcLen * sizeof(int));
  int intlvLen = 0;
  LTE_interleaver(ccbcSym, prb_num, Qm, intlvSym, &intlvLen);
  free(ccbcSym);

  /*LTE α������в���*/
  int *scramble_Sym = (int *)malloc(intlvLen * sizeof(int));
  int vrb_num = prb_num; // 1��UEռ�õ�VRB��
  lte_scramble(intlvSym, intlvLen, vrb_num, Qm, UL_subframe_num, ue_index,
               cellid, scramble_Sym);
  free(intlvSym);

  /* this is in . c file, to record the data -> file */
  int N = 1;
  int M = intlvLen;
  FILE *fp;
  int idx;
  int jdx;
  int rows = N; /*�������ݾ��������ΪN*/
  int cols = M; /*�������ݾ��������ΪM*/
  fp = fopen("ccsdata.ascii", "w+");

  /*д����,����д�뷽ʽ,������(%d)��������Ϊ��*/
  for (idx = 0; idx < rows; idx++) {
    for (jdx = 0; jdx < cols; jdx++) {
      fprintf(fp, "%d\n", scramble_Sym[jdx]);
    }
  }
  fclose(fp);

  return 0;
}