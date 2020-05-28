//=============================================================================
/**
 * @file	builddate.c
 * @brief	ソースファイル全般に変更がかかるとmakeかかるようにしてみた
            本当はデバッグ用にしたくないのだが、
            buildTimeがわかると困ることがあるかもしれないのでくくってある
 * @author	Katsumi Ohno
 * @date    2005.10.03
 */
//=============================================================================

#include "common.h"
#include "system/builddate.h"

#ifdef PM_DEBUG		// Debug ROM

char BuildDate[]=__DATE__;
char BuildTime[]=__TIME__;


void DebugBuildTimeDisp(void)
{
    OS_TPrintf("build %s %s\n", BuildDate, BuildTime);
}


void WORDSET_DebugBuildTime(WORDSET * ws)
{
    char* month[]={"Jan","Feb","Mar","Apl","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"};
    int i;
    STRCODE temp[20];
    int monNum = 0;
    int dayNum = 0;
    int timNum = 0;
    int minNum = 0;
    int secNum = 0;
    
    for(i = 0; i < 12; i++){  // 月を3文字比較
        if(strncmp(month[i], BuildDate, 3)==0){
            monNum = i+1;
        }
    }
    dayNum = atoi(&BuildDate[4]);
    timNum = atoi(&BuildTime[0]);
    minNum = atoi(&BuildTime[3]);
    secNum = atoi(&BuildTime[6]);

	WORDSET_RegisterNumber(ws, 0, monNum, 2, NUMBER_DISPTYPE_SPACE, NUMBER_CODETYPE_DEFAULT);
	WORDSET_RegisterNumber(ws, 1, dayNum, 2, NUMBER_DISPTYPE_SPACE, NUMBER_CODETYPE_DEFAULT);
	WORDSET_RegisterNumber(ws, 2, timNum, 2, NUMBER_DISPTYPE_SPACE, NUMBER_CODETYPE_DEFAULT);
	WORDSET_RegisterNumber(ws, 3, minNum, 2, NUMBER_DISPTYPE_SPACE, NUMBER_CODETYPE_DEFAULT);
	DebugBuildTimeDisp();
}

#if 0
void DebugGetBuildTime(STRCODE* buf)
{
    char* month[]={"Jan","Feb","Mar","Apl","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"};
    int i;
    STRCODE temp[20];
    int monNum = 0;
    int dayNum = 0;
    int timNum = 0;
    int minNum = 0;
    int secNum = 0;
    STRCODE* pStr = buf;
    
    for(i = 0; i < 12; i++){  // 月を3文字比較
        if(strncmp(month[i], BuildDate, 3)==0){
            monNum = i+1;
        }
    }
    dayNum = atoi(&BuildDate[4]);
    timNum = atoi(&BuildTime[0]);
    minNum = atoi(&BuildTime[3]);
    secNum = atoi(&BuildTime[6]);

//    OS_TPrintf("%d %d %d %d %d\n", monNum, dayNum, timNum, minNum, secNum);

    pStr = PM_NumMsgSet(pStr, monNum, NUM_MODE_SPACE, 2);
    pStr = PM_NumMsgSet(pStr, dayNum, NUM_MODE_SPACE, 3);
    pStr = PM_NumMsgSet(pStr, timNum, NUM_MODE_SPACE, 3);
    pStr = PM_NumMsgSet(pStr, minNum, NUM_MODE_SPACE, 3);
    PM_NumMsgSet(pStr, secNum, NUM_MODE_SPACE, 3);
}
#endif

#else


char BuildDate[]="";
char BuildTime[]="";


void DebugBuildTimeDisp(void)
{
}

   
#endif

