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

  udbitlength = tbsize + 24; /*CRC校验位长度*/

  /*CRC*/
  ptempbit = &InterweaveData[0]; /*交织buffer指针*/
  poutbit = &OriginalBuffer[0];
  CRCAdd(poutbit, ptempbit, tbsize);

  /*码块分段*/
  pcdblocksegbit = &CodeBlockBit[0][0];
  poutbit = &OriginalBuffer[0];
  ptempbit = &InterweaveData[0]; /*交织buffer指针*/
  cdblockseg(pcdblocksegbit, poutbit, ptempbit, udbitlength);

  return 0;
}
