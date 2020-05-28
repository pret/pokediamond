//===========================================================================
/**
 * @file	safari_scope_calc.h
 * @brief	ƒTƒtƒ@ƒŠ–]‰“‹¾
 * @author	Nozomu Saito
 * @date	2006.04.24
 * 
 */
//===========================================================================
#ifndef __SAFARI_SCOPE_CALC_H__
#define __SAFARI_SCOPE_CALC_H__

#include "field_common.h"

typedef struct SCOPE_DATA_tag * SSC_SD_PTR;

extern int SSC_GetSafScpMons(FIELDSYS_WORK * fsys);
extern SSC_SD_PTR SSC_CreateScopePointList(const int inHeapID, FIELDSYS_WORK * fsys);
extern void SSC_RereaseScopePointList(SSC_SD_PTR ptr);
extern void SSC_SetNextLocation(const u8 inNo, SSC_SD_PTR ptr);
extern void SSC_JumpMap(GMEVENT_CONTROL * event, SSC_SD_PTR ptr);
extern LOCATION_WORK *SSC_GetNextLocaton(SSC_SD_PTR ptr);


#endif	//__SAFARI_SCOPE_CALC_H__
