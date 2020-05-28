//==============================================================================
/**
 * @file	localres.h
 * @brief	確保したリソース領域を更に配分して再利用しまくる。
 * @author	kagaya
 * @data	05.07.13
 */
//==============================================================================
#ifndef LOCALRES_H_FILE
#define LOCALRES_H_FILE

#include "system/arc_tool.h"

//==============================================================================
//	debug
//==============================================================================

//==============================================================================
//	define
//==============================================================================

//==============================================================================
//	typedef
//==============================================================================
//--------------------------------------------------------------
///	LRES定義　ローカルリソース管理情報を纏めている
//--------------------------------------------------------------
typedef struct _LRES		LRES;

//--------------------------------------------------------------
///	ALLOCTYPE 領域確保方法
//--------------------------------------------------------------
typedef enum
{
	ALLOC_FR = 0,											///<領域の前から確保
	ALLOC_LO,												///<領域の後ろから確保
}ALLOCTYPE;

//==============================================================================
//	外部宣言関数
//==============================================================================
extern LRES * LRes_Init( u32 main_heap_id, u32 reg_heap_id, u32 size, u32 resid_max );
extern void LRes_Delete( LRES *lres );
extern void * LRes_Alloc( LRES *lres, u32 size, ALLOCTYPE type );
extern void * LRes_AllocID( LRES *lres, u32 id, u32 size, ALLOCTYPE type );
extern void LRes_Free( LRES *lres, void *alloc );
extern void LRes_FreeID( LRES *lres, u32 id );
extern void * LRes_IDResGet( LRES *lres, u32 id );
extern int LRes_IDResCheck( LRES *lres, u32 id );

extern void * LResUtil_AllocArcLoad( LRES *lres, ARCHANDLE *handle, u32 datId, ALLOCTYPE type );
extern void * LResUtil_AllocIDArcLoad(
		LRES *lres, u32 id, ARCHANDLE *handle, u32 datId, ALLOCTYPE type );

#endif //LOCALRES_H_FILE
