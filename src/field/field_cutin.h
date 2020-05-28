//==============================================================================
/**
 * @file	field_cutin.h
 * @brief	フィールド　カットイン
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
///	カットイン種類
//--------------------------------------------------------------
enum
{
	CUTIN_TYPE_HIDEN,		///<秘伝技用カットイン
	CUTIN_TYPE_SKY,		///<秘伝技　空を飛ぶカットイン
};

//==============================================================================
//	typedef
//==============================================================================

//==============================================================================
//	外部参照
//==============================================================================
extern TCB_PTR FieldCutIn_Init(
	FIELDSYS_WORK *fsys, u32 cutin_type, POKEMON_PARAM *param, int hero_sex );
extern int FieldCutIn_EndCheck( TCB_PTR tcb );
extern void FieldCutIn_End( TCB_PTR tcb );

extern TCB_PTR FieldHidenSkyLanding_Init( FIELDSYS_WORK *fsys, int sex );
extern int FieldHidenSkyLanding_EndCheck( TCB_PTR tcb );
extern void FieldHidenSkyLanding_End( TCB_PTR tcb );

#endif //FIELD_CUTIN_H_FILE
