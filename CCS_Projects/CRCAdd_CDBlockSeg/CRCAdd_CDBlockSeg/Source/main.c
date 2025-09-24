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

  int *TurboEncodedBits = malloc((Kp + 4) * C * 3 * sizeof(int));

  /*Turbo����*/
  TurboEncode(pcdblocksegbit, ptempbit, TurboEncodedBits, C, Kp, Km, Cm, F);

  return 0;
}
