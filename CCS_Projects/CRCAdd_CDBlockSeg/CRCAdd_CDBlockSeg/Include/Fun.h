#ifndef FUN_H_
#define FUN_H_

// extern INT32 CRCAdd(INT32 *poutbit, INT32 *ptempinput, UINT32 udBitLen);
// extern INT32 CRCbAdd(INT32 *poutbit, INT32 *ptempinput, UINT32 udBitLen);
// extern INT32 cdblockseg(INT32 *pcodeblockbit, INT32 *pinputbit, INT32
// *ptempbit,
//                         UINT32 udbitlen);

extern int CRCAdd(int *poutbit, int *ptempinput, unsigned int udBitLen);
extern int CRCbAdd(int *poutbit, int *ptempinput, unsigned int udBitLen);
extern int cdblockseg(int *pcodeblockbit, int *pinputbit, int *ptempbit,
                      unsigned int udbitlen);

extern int TurboEncode(int *pinputbit, int *ptempbit, int *poutputbit, int C, int Kp, int Km, int Cm, int F);
extern int interleaver(int *input_bits, int *output_bits, int K);
extern int rsc_encode(int *input_bits, int *output_bits, int *tail_bits, int K);

#endif /* FUN_H_ */
