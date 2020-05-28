//==============================================================================
/**
 * @file	fldeff_shadow.h
 * @brief	�t�B�[���hOBJ�e
 * @author	kagaya
 * @data	05.07.13
 */
//==============================================================================
#ifndef FLDEFF_SHADOW_H_FILE
#define FLDEFF_SHADOW_H_FILE

#include "field_effect.h"

//==============================================================================
//	define
//==============================================================================
//--------------------------------------------------------------
///	�e���
//--------------------------------------------------------------
enum
{
	SHADOW_BLACK = 0,										///<���F�̉e
	SHADOW_RED,												///<�ԐF�̉e
	SHADOW_BLUE,											///<�F�̉e
};

//==============================================================================
//	�O���Q��
//==============================================================================
extern void * FE_Shadow_Init( FE_SYS *fes );
extern void FE_Shadow_Delete( void *work );

extern void FE_FldOBJShadow_Add( FIELD_OBJ_PTR fldobj );
extern EOA_PTR FE_FldOBJShadowSet( FIELD_OBJ_PTR fldobj, int type );

#endif //FLDEFF_SHADOW_H_FILE
