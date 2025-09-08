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

  udbitlength = tbsize + 24; /*����CRC�ĳ���*/

  /*����CRC*/
  ptempbit = &InterweaveData[0]; /*�ͽ�֯buffer����*/
  poutbit = &OriginalBuffer[0];
  CRCAdd(poutbit, ptempbit, tbsize);

  /*���ָ�*/
  pcdblocksegbit = &CodeBlockBit[0][0];
  poutbit = &OriginalBuffer[0];
  ptempbit = &InterweaveData[0]; /*�ͽ�֯buffer����*/
  cdblockseg(pcdblocksegbit, poutbit, ptempbit, udbitlength);

  return 0;
}
