//============================================================================================
/**
 * @file	ship_demo_call.h
 * @brief	船デモコール
 * @date	2006.05.23
 * @author	Nozomu Saito
 *
 */
//============================================================================================
#ifndef __SHIP_DEMO_CALL_H__
#define	__SHIP_DENO_CALL_H__

#include "field_common.h"

extern void ShipDemo_CallDemo(	FIELDSYS_WORK * fsys,
								const u8 inShipDir,
								const u8 inPlayerDir,
								const int inNextZone,
								const int inNextX,
								const int inNextZ );

#endif	//__SHIP_DENO_CALL_H__
