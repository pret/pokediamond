//==============================================================================
/**
 * @file	fldeff_snowball.h
 * @brief	フィールドOBJ雪玉
 * @author	kagaya
 * @data	05.07.13
 */
//==============================================================================
#ifndef FLDEFF_SNOWBALL_H_FILE
#define FLDEFF_SNOWBALL_H_FILE

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
extern void * FE_SnowBall_Init( FE_SYS *fes );
extern void FE_SnowBall_Delete( void *work );
extern EOA_PTR FE_FldOBJSnowBall_Add( FIELD_OBJ_PTR fldobj );
extern void FE_FldOBJSnowBall_BreakAnimeSet( EOA_PTR eoa );

extern void * FE_Book_Init( FE_SYS *fes );
extern void FE_Book_Delete( void *work );
extern EOA_PTR FE_FldOBJBook_Add( FIELD_OBJ_PTR fldobj );

extern void * FE_Door2_Init( FE_SYS *fes );
extern void FE_Door2_Delete( void *work );
extern EOA_PTR FE_FldOBJDoor2_Add( FIELD_OBJ_PTR fldobj );

#endif //FLDEFF_SNOWBALL_H_FILE
