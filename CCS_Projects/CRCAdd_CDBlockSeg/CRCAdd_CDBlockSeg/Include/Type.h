#include <stdio.h>
#include <stdlib.h>

#ifndef TYPE_H_
#define TYPE_H_

typedef signed   short    INT16;
typedef unsigned short    UINT16;

typedef signed   int      INT32;
typedef unsigned int      UINT32;
#define NA      8        //<NULL>
struct IQData
{
//	float Idata;
//	float Qdata;
	double Idata;
	double Qdata;
};

struct Kparam
{
	int Kplus;
	int Kneg;
	int Cplus;
	int Cneg;
	int C;
	int F;
	int codelen[13];
	int ratematchlen[13];
	int index;  /*K,f1,f2µÄË÷Òý*/
};

struct subblockInterParam
{
	int Kpi;
	int RsubblockTC;
};

#endif
