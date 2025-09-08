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

  return 0;
}
