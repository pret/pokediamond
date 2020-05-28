//==============================================================================
/**
 * @file	fldeff_splash.h
 * @brief	フィールドOBJ水飛沫
 * @author	kagaya
 * @data	05.07.13
 */
//==============================================================================
#ifndef FLDEFF_SPLASH_H_FILE
#define FLDEFF_SPLASH_H_FILE

#include "eoa.h"
#include "fieldobj.h"
#include "field_effect.h"

//==============================================================================
//	typedef
//==============================================================================

//==============================================================================
//	外部参照
//==============================================================================
extern void * FE_Splash_Init( FE_SYS *fes );
extern void FE_Splash_Delete( void *work );

extern void FE_FldOBJSplash_Add( FIELD_OBJ_PTR fldobj, int joint );

#endif //FLDEFF_SPLASH_H_FILE
