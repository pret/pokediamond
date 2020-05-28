//==============================================================================
/**
 * @file	fldeff_exclamation.h
 * @brief	一枚ポリゴン 地下用 びっくりマーク
 * @author	k.ohno
 * @data	06.02.13
 */
//==============================================================================
#ifndef FLDEFF_EXCLAMATION_H_FILE
#define FLDEFF_EXCLAMATION_H_FILE

#include "fieldobj.h"
#include "field_effect.h"

//==============================================================================
//	typedef
//==============================================================================

//==============================================================================
//	外部参照
//==============================================================================
extern void * FE_Exclamation_Init( FE_SYS *fes );
extern void FE_Exclamation_Delete( void *work );

extern EOA_PTR FE_Exclamation_Add( FIELD_OBJ_PTR fldobj );

#endif //FLDEFF_EXCLAMATION_H_FILE

