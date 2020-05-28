//============================================================================================
/**
 * @file	dendou_pc.h
 * @bfief	“a“°“ü‚èƒpƒ\ƒRƒ“‰æ–Ê
 * @author	taya GAME FREAK inc.
 *
 * @date	2006.04.21
 */
//============================================================================================
#ifndef __DENDOU_PC_H__
#define __DENDOU_PC_H__

#include "system\procsys.h"

extern PROC_RESULT DendouPc_PROC_Init( PROC * proc, int * seq );
extern PROC_RESULT DendouPc_PROC_Quit( PROC * proc, int * seq );
extern PROC_RESULT DendouPc_PROC_Main( PROC * proc, int * seq );

#endif
