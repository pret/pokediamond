//==============================================================================
/**
 * @file	fldeff_namipoke.h
 * @brief	フィールドOBJ波乗りポケモン
 * @author	kagaya
 * @data	05.07.13
 */
//==============================================================================
#ifndef FLDEFF_NAMIPOKE_H_FILE
#define FLDEFF_NAMIPOKE_H_FILE

#include "fieldobj.h"
#include "field_effect.h"
#include "player.h"

//==============================================================================
//	define
//==============================================================================
#define NAMIPOKE_RIDE_Y_OFFSET (FX32_ONE*7)				///<波ポケ乗りへの表示オフセットY
#define NAMIPOKE_RIDE_Z_OFFSET (FX32_ONE*4)				///<波ポケ乗りへの表示オフセットZ

//==============================================================================
//	typedef
//==============================================================================

//==============================================================================
//	外部参照
//==============================================================================
extern void * FE_NamiPoke_Init( FE_SYS *fes );
extern void FE_NamiPoke_Delete( void *work );

extern EOA_PTR FE_FldOBJNamiPokeSet( FIELD_OBJ_PTR fldobj, int gx, int gz, int dir, int joint );
extern void FE_FldOBJNamiPokeJointFlagSet( EOA_PTR eoa, int flag );

#ifdef DEBUG_NAMIPOKE_ROT
void DEBUG_NamiPoke_Rot( EOA_PTR eoa, int x, int y, int z );
#endif

#endif //FLDEFF_NAMIPOKE_H_FILE
