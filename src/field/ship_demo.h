//============================================================================================
/**
 * @file	ship_demo.h
 * @brief	‘Dƒfƒ‚
 * @date	2006.05.23
 * @author	Nozomu Saito
 *
 */
//============================================================================================
#ifndef __SHIP_DEMO_H__
#define	__SHIP_DENO_H__

#include "field_common.h"
#include "field_glb_state.h"

extern PROC_RESULT ShipDemoProc_Init( PROC * proc, int * seq );
extern PROC_RESULT ShipDemoProc_Main( PROC * proc, int * seq );
extern PROC_RESULT ShipDemoProc_End( PROC * proc, int * seq );

typedef struct SHIPDEMO_DAT_tag
{
	u8 Dir;
	GLST_DATA *LightDataPtr;
}SHIPDEMO_DAT;

extern void ShipDemo_ProcSet( FIELDSYS_WORK * fsys , void * wk );

#endif	//__SHIP_DENO_H__
