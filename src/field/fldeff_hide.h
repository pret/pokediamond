//==============================================================================
/**
 * @file	fldeff_hide.h
 * @brief	�t�B�[���hOBJ�B�ꖪ
 * @author	kagaya
 * @data	05.07.13
 */
//==============================================================================
#ifndef FLDEFF_HIDE_H_FILE
#define FLDEFF_HIDE_H_FILE

#include "field_effect.h"

//==============================================================================
//	define
//==============================================================================
//--------------------------------------------------------------
///	�B�ꖪ���
//--------------------------------------------------------------
typedef enum
{
	HIDE_SNOW = 0,
	HIDE_SAND,
	HIDE_GROUND,
	HIDE_GRASS,
	HIDE_MAX,
}HIDETYPE;

//==============================================================================
//	�O���Q��
//==============================================================================
extern void * FE_Hide_Init( FE_SYS *fes );
extern void FE_Hide_Delete( void *work );

extern EOA_PTR FE_FldOBJHide_Add( FIELD_OBJ_PTR fldobj, HIDETYPE type );

#endif //FLDEFF_HIDE_H_FILE
