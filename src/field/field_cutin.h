//==============================================================================
/**
 * @file	field_cutin.h
 * @brief	�t�B�[���h�@�J�b�g�C��
 * @author	kagaya
 * @data	05.07.13
 */
//==============================================================================
#ifndef FIELD_CUTIN_H_FILE
#define FIELD_CUTIN_H_FILE

#include "poketool/poke_tool.h"

//==============================================================================
//	define
//==============================================================================
//--------------------------------------------------------------
///	�J�b�g�C�����
//--------------------------------------------------------------
enum
{
	CUTIN_TYPE_HIDEN,		///<��`�Z�p�J�b�g�C��
	CUTIN_TYPE_SKY,		///<��`�Z�@����ԃJ�b�g�C��
};

//==============================================================================
//	typedef
//==============================================================================

//==============================================================================
//	�O���Q��
//==============================================================================
extern TCB_PTR FieldCutIn_Init(
	FIELDSYS_WORK *fsys, u32 cutin_type, POKEMON_PARAM *param, int hero_sex );
extern int FieldCutIn_EndCheck( TCB_PTR tcb );
extern void FieldCutIn_End( TCB_PTR tcb );

extern TCB_PTR FieldHidenSkyLanding_Init( FIELDSYS_WORK *fsys, int sex );
extern int FieldHidenSkyLanding_EndCheck( TCB_PTR tcb );
extern void FieldHidenSkyLanding_End( TCB_PTR tcb );

#endif //FIELD_CUTIN_H_FILE
