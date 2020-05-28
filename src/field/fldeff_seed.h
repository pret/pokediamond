
//==============================================================================
/**
 * @file	fldeff_shadow.h
 * @brief	フィールドOBJ影
 * @author	kagaya
 * @data	05.07.13
 */
//==============================================================================
#ifndef FLDEFF_SEEDGROUND_H_FILE
#define FLDEFF_SEEDGROUND_H_FILE

#include "fieldobj.h"
#include "field_effect.h"

//==============================================================================
//	typedef
//==============================================================================

//==============================================================================
//	外部参照
//==============================================================================
extern void * FE_SeedGround_Init( FE_SYS *fes );
extern void FE_SeedGround_Delete( void *work );

extern void FE_FldOBJSeedGround_Add( FIELD_OBJ_PTR fldobj );

extern void * FE_SeedEff_Init( FE_SYS *fes );
extern void FE_SeedEff_Delete( void *work );

extern EOA_PTR FE_FldOBJSeedEff_Add( FIELD_OBJ_PTR fldobj );

#endif //FLDEFF_SEEDGROUND_H_FILE
