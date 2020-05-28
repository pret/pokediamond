//==============================================================================
/**
 * @file	fldeff_rockride.h
 * @brief	フィールドOBJ壁上りポケモン
 * @author	kagaya
 * @data	05.07.13
 */
//==============================================================================
#ifndef FLDEFF_ROCKRIDE_H_FILE
#define FLDEFF_ROCKRIDE_H_FILE

#include "fieldobj.h"
#include "field_effect.h"

//==============================================================================
//	define
//==============================================================================

//==============================================================================
//	typedef
//==============================================================================

//==============================================================================
//	外部参照
//==============================================================================
extern void * FE_RockRide_Init( FE_SYS *fes );
extern void FE_RockRide_Delete( void *work );

extern EOA_PTR FE_FldOBJRockRidePoke_Add(
		FIELD_OBJ_PTR fldobj, int gx, int gz, int dir, int joint );
extern void FE_FldOBJRockRidePokeJointFlagSet( EOA_PTR eoa, int joint );

#endif //FLDEFF_ROCKRIDE_H_FILE
