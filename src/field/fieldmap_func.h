//============================================================================================
/**
 * @file	fieldmap_func.h
 * @brief	フィールドマップ上で動作する制御タスクシステム
 * @author	tamada GAME FREAK inc.
 * @date	2006.03.15
 */
//============================================================================================
#ifndef	__FIELDMAP_FUNC_H__
#define	__FIELDMAP_FUNC_H__

#include "fieldmap_func_def.h"

//------------------------------------------------------------------
/**
 * @brief	FLDMAPFUNCの制御ワークへの不完全型定義
 */
//------------------------------------------------------------------
typedef struct FLDMAPFUNC_WORK FLDMAPFUNC_WORK;

typedef void (*FLDMAPFUNC_UPDATE)(FLDMAPFUNC_WORK *, FIELDSYS_WORK *, void *);
typedef void (*FLDMAPFUNC_DRAW3D)(FLDMAPFUNC_WORK *, FIELDSYS_WORK *, void *);
typedef void (*FLDMAPFUNC_CREATE)(FLDMAPFUNC_WORK *, FIELDSYS_WORK *, void *);
typedef void (*FLDMAPFUNC_DELETE)(FLDMAPFUNC_WORK *, FIELDSYS_WORK *, void *);

//------------------------------------------------------------------
/**
 * @brief	FLDMAPFUNCを生成するのに必要なデータ定義
 */
//------------------------------------------------------------------
typedef struct {
	u32 pri;						///<動作プライオリティ
	u16 work_size;					///<確保するワークのサイズ
	FLDMAPFUNC_CREATE create_func;	///<生成処理
	FLDMAPFUNC_DELETE delete_func;	///<消去処理
	FLDMAPFUNC_UPDATE update_func;	///<更新処理
	FLDMAPFUNC_DRAW3D draw3d_func;	///<3D描画処理
}FLDMAPFUNC_DATA;

//------------------------------------------------------------------
//		システム関数
//------------------------------------------------------------------
extern FLDMAPFUNC_SYS * FLDMAPFUNC_Sys_Create(FIELDSYS_WORK * fsys, int heapID, int max);
extern void FLDMAPFUNC_Sys_Delete(FLDMAPFUNC_SYS * sys);
extern void FLDMAPFUNC_Sys_Draw3D(FLDMAPFUNC_SYS * sys);

//------------------------------------------------------------------
//		個別処理用関数
//------------------------------------------------------------------
extern FLDMAPFUNC_WORK * FLDMAPFUNC_Create(FLDMAPFUNC_SYS * sys, const FLDMAPFUNC_DATA * data);
extern void FLDMAPFUNC_Delete(FLDMAPFUNC_WORK * fwk);

//------------------------------------------------------------------
//		ツール関数
//------------------------------------------------------------------
extern void * FLDMAPFUNC_GetFreeWork(FLDMAPFUNC_WORK * fwk);

#endif	/* __FIELDMAP_FUNC_H__ */
