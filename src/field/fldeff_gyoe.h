//==============================================================================
/**
 * @file	fldeff_gyoe.h
 * @brief	フィールドOBJギョエー
 * @author	kagaya
 * @data	05.07.13
 */
//==============================================================================
#ifndef FLDEFF_GYOE_H_FILE
#define FLDEFF_GYOE_H_FILE

#include "eoa.h"
#include "fieldobj.h"
#include "field_effect.h"

//==============================================================================
//	typedef
//==============================================================================
//--------------------------------------------------------------
///	ギョエー種類
//--------------------------------------------------------------
typedef enum
{
	GYOE_GYOE = 0,
	GYOE_SAISEN,
}GYOE_TYPE;

//==============================================================================
//	外部参照
//==============================================================================
extern void * FE_Gyoe_Init( FE_SYS *fes );
extern void FE_Gyoe_Delete( void *work );

extern EOA_PTR FE_Gyoe_Add( FE_SYS *fes, const VecFx32 *mtx, int se_play );
extern EOA_PTR FE_FldOBJGyoe_Add( FIELD_OBJ_PTR fldobj, GYOE_TYPE type, int se_play );
extern int FE_Gyoe_EndCheck( EOA_PTR eoa );

#endif //FLDEFF_GYOE_H_FILE
