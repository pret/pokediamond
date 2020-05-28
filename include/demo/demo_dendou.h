//============================================================================================
/**
 * @file	demo_dendou.h
 * @brief	ポケモン殿堂入りデモ呼び出し
 * @author	taya
 * @date	2006.04.26
 */
//============================================================================================
#ifndef  __DEMO_DENDOU_H__
#define  __DEMO_DENDOU_H__

#include "system\procsys.h"
#include "savedata\mystatus.h"
#include "savedata\playtime.h"
#include "poketool\pokeparty.h"


typedef struct {
	const MYSTATUS*		player;
	const POKEPARTY*	party;
	const PLAYTIME*		playTime;
}DEMO_DENDOU_PARAM;



extern PROC_RESULT  DemoDendouPROC_Init( PROC* proc, int* seq );
extern PROC_RESULT  DemoDendouPROC_Main( PROC* proc, int* seq );
extern PROC_RESULT  DemoDendouPROC_Quit( PROC* proc, int* seq );



#endif
