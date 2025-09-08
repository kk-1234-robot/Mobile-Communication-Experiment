#include "..\Include\Globe.h"
#include "..\Include\Type.h"
#include <stdio.h>
#include <stdlib.h>

#pragma DATA_SECTION(InterweaveData, "myDDRdata")
int InterweaveData[86400];

/*100RB MCS28��bit��75376 +24=75400*/
#pragma DATA_SECTION(OriginalBuffer, "myDDRdata")
int OriginalBuffer[75400] = {
#include "../data/data.dat"
};

#pragma DATA_SECTION(CodeBlockBit, "myDDRdata")
INT32 CodeBlockBit[13][6144]; /*13�����������6144���� ÿ��������󳤶�*/

#pragma DATA_SECTION(G, "myDDRdata")
int G[25] = {1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0,
             1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 1, 1};

#pragma DATA_SECTION(G1, "myDDRdata")
int G1[25] = {1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
              0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1};

struct Kparam Kcodeblock; /*�����ز���*/
