//******************************************************************************
/**
 * 
 * @file	fldeff_ripple.c
 * @brief	フィールドOBJ　水波紋
 * @author	kagaya
 * @data	05.07.13
 *
 */
//******************************************************************************
#include "common.h"
#include "fieldsys.h"
#include "field_effect.h"
#include "fieldobj.h"
#include "fldeff_ripple.h"

#include "field_3dobj.h"

//==============================================================================
//	define
//==============================================================================
//#define DEBUG_RIPPLE_WRITE_OFF	//定義で水波紋描画OFF

#define RIPPLE_DRAW_Y_OFFSET (-FX32_ONE*(8))		///<水波紋描画オフセットY軸
#define RIPPLE_DRAW_Z_OFFSET (FX32_ONE*(1))

#define RIPPLE_ON_FRAME (30)
#define RIPPLE_OFF_FRAME (RIPPLE_ON_FRAME+30)

//==============================================================================
//	typedef struct
//==============================================================================
//--------------------------------------------------------------
///	FE_RIPPLE型
//--------------------------------------------------------------
typedef struct _TAG_FE_RIPPLE * FE_RIPPLE_PTR;

//--------------------------------------------------------------
///	FE_RIPPLE構造体
//--------------------------------------------------------------
typedef struct _TAG_FE_RIPPLE
{
	FE_SYS *fes;
	
	FLD_3DOBJ_MDL obj_mdl;
	FLD_3DOBJ_ANM obj_anm;
	NNSFndAllocator allocator;
}FE_RIPPLE;

#define FE_RIPPLE_SIZE (sizeof(FE_RIPPLE)) ///<FE_RIPPLEサイズ

//--------------------------------------------------------------
///	RIPPLE_ADD_H構造体
//--------------------------------------------------------------
typedef struct
{
	FE_SYS *fes;					///<FE_SYS_PTR
	FE_RIPPLE_PTR ripple;		///<FE_RIPPLE_PTR
}RIPPLE_ADD_H;

#define RIPPLE_ADD_H_SIZE (sizeof(RIPPLE_ADD_H)) ///<RIPPLE_ADD_Hサイズ

//--------------------------------------------------------------
///	RIPPLE_3DOBJ構造体
//--------------------------------------------------------------
typedef struct
{
	NNSG3dAnmObj*			pAnmObj;			// アニメーションオブジェ
	NNSFndAllocator allocator;
	fx32 frame;
	FLD_3DOBJ obj;
}RIPPLE_3DOBJ;

#define RIPPLE_3DOBJ_SIZE (sizeof(RIPPLE_3DOBJ))

//--------------------------------------------------------------
///	RIPPLE_WORK構造体
//--------------------------------------------------------------
typedef struct
{
	RIPPLE_3DOBJ *ripobj;
	RIPPLE_ADD_H head;						///<追加時のRIPPLE_ADD_H
}RIPPLE_WORK;

#define RIPPLE_WORK_SIZE (sizeof(RIPPLE_WORK))	///<RIPPLE_WORKサイズ

//==============================================================================
//	プロトタイプ
//==============================================================================
static void Ripple_GraphicInit( FE_RIPPLE_PTR ripple );
static void Ripple_GraphicDelete( FE_RIPPLE_PTR ripple );

static const EOA_H_NPP DATA_EoaH_Ripple;

//==============================================================================
//	水波紋　システム
//==============================================================================
//--------------------------------------------------------------
/**
 * 水波紋初期化
 * @param	fes		FE_SYS_PTR
 * @retval	FE_RIPPLE_PTR	FE_RIPPLE_PTR
 */
//--------------------------------------------------------------
void * FE_Ripple_Init( FE_SYS *fes )
{
	FE_RIPPLE_PTR ripple;
	
	ripple = FE_AllocClearMemory( fes, FE_RIPPLE_SIZE, ALLOC_FR, 0 );
	ripple->fes = fes;
	
	Ripple_GraphicInit( ripple );
	return( ripple );
}

//--------------------------------------------------------------
/**
 * 水波紋削除
 * @param	ripple		FE_RIPPLE_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void FE_Ripple_Delete( void *work )
{
	FE_RIPPLE_PTR ripple = work;
	Ripple_GraphicDelete( ripple );
	FE_FreeMemory( ripple );
}

//==============================================================================
//	水波紋	パーツ
//==============================================================================

//==============================================================================
//	水波紋　グラフィック
//==============================================================================
//--------------------------------------------------------------
/**
 * 水波紋 グラフィック初期化
 * @param	ripple	FE_RIPPLE_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void Ripple_GraphicInit( FE_RIPPLE_PTR ripple )
{
	FE_InitAllocator( ripple->fes, &ripple->allocator );
	FE_3DObjMdlLoad( ripple->fes, &ripple->obj_mdl, NARC_fldeff_ripple_nsbmd, ALLOC_FR );
	FE_3DObjAnmLoad( ripple->fes, &ripple->obj_anm, &ripple->obj_mdl, &ripple->allocator, 
		NARC_fldeff_ripple_nsbtp, ALLOC_FR );
}

//--------------------------------------------------------------
/**
 * 水波紋 グラフィック削除
 * @param	ripple	FE_RIPPLE_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void Ripple_GraphicDelete( FE_RIPPLE_PTR ripple )
{
	FLD_3DObjMdlDelete( &ripple->obj_mdl );	
	FLD_3DObjAnmDelete( &ripple->obj_anm, &ripple->allocator );	
}

//==============================================================================
//	水波紋　EOA
//==============================================================================
//--------------------------------------------------------------
/**
 * 水波紋追加
 * @param	fldobj	対象となるFIELD_OBJ_PTR
 * @param	gx		表示するグリッドX座標
 * @param	gz		表示するグリッドZ座標
 * @retval	EOA_PTR	水波紋EOA_PTR
 */
//--------------------------------------------------------------
void FE_FldOBJRippleSet( FIELD_OBJ_PTR fldobj, int gx, int gy, int gz )
{
	int pri,param;
	RIPPLE_ADD_H head;
	VecFx32 mtx;
	
	head.fes = FE_FieldOBJ_FE_SYS_Get( fldobj );
	head.ripple = FE_EffectWorkGet( head.fes, FE_FLD_RIPPLE );
	
	FieldOBJTool_GridCenterPosGet( gx, gz, &mtx );
	mtx.z += H_GRID_SIZE( gy ) + RIPPLE_DRAW_Z_OFFSET;
	
	mtx.y = H_GRID_SIZE_FX32( FieldOBJ_OldPosGY_Get(fldobj) ) + RIPPLE_DRAW_Y_OFFSET;
	
	param = 0;
	pri = FieldOBJ_TCBPriGet( fldobj, FLDOBJ_TCBPRI_OFFS_AFTER );
	FE_EoaAddNpp( head.fes, &DATA_EoaH_Ripple, &mtx, param, &head,pri );
}

//--------------------------------------------------------------
/**
 * EOA 水波紋　初期化
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work *
 * @retval	int		TRUE=正常終了。FALSE=異常終了
 */
//--------------------------------------------------------------
static int EoaRipple_Init( EOA_PTR eoa, void *wk )
{
	VecFx32 mtx;
	RIPPLE_WORK *work = wk;
	RIPPLE_3DOBJ *ripobj;
	const RIPPLE_ADD_H *head = EOA_AddPtrGet( eoa );
	
	work->head = *head;
	ripobj = FE_AllocClearMemory( work->head.ripple->fes, RIPPLE_3DOBJ_SIZE, ALLOC_LO, 0 );
	work->ripobj = ripobj;
	
	FE_InitAllocator( work->head.fes, &ripobj->allocator );
	
	ripobj->pAnmObj = NNS_G3dAllocAnmObj( 
			&ripobj->allocator,
			work->head.ripple->obj_anm.pOneResAnm,
			work->head.ripple->obj_mdl.pModel );
	
	NNS_G3dAnmObjInit(
		ripobj->pAnmObj,
		work->head.ripple->obj_anm.pOneResAnm,
		work->head.ripple->obj_mdl.pModel,
		work->head.ripple->obj_mdl.pMdlTex );
	
	FLD_3DObjInit( &ripobj->obj, &work->head.ripple->obj_mdl );
	NNS_G3dRenderObjAddAnmObj( &ripobj->obj.render, ripobj->pAnmObj );
	
	EOA_MatrixGet( eoa, &mtx );
	FLD_3DObjSetMatrix( &ripobj->obj, mtx.x, mtx.y, mtx.z );
	
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * EOA 水波紋　削除
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work *
 * @retval	nothing
 */
//--------------------------------------------------------------
static void EoaRipple_Delete( EOA_PTR eoa, void *wk )
{
	RIPPLE_WORK *work = wk;
	RIPPLE_3DOBJ *ripobj = work->ripobj;
	NNS_G3dFreeAnmObj( &ripobj->allocator, ripobj->pAnmObj );
	FE_FreeMemory( ripobj );
}

//--------------------------------------------------------------
/**
 * EOA 水波紋　動作
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work *
 * @retval	nothing
 */
//--------------------------------------------------------------
static void EoaRipple_Move( EOA_PTR eoa, void *wk )
{
	RIPPLE_WORK *work = wk;
	RIPPLE_3DOBJ *ripobj = work->ripobj;
	fx32 end_frame = NNS_G3dAnmObjGetNumFrame( ripobj->pAnmObj );
	
	ripobj->frame += FX32_ONE;
	
	if( ripobj->frame > end_frame ){
		FE_EoaDelete( eoa );
		return;
	}
	
	NNS_G3dAnmObjSetFrame( ripobj->pAnmObj, ripobj->frame );
}

//--------------------------------------------------------------
/**
 * EOA 水波紋　描画
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work *
 * @retval	nothing
 */
//--------------------------------------------------------------
static void EoaRipple_Draw( EOA_PTR eoa, void *wk )
{
	RIPPLE_WORK *work = wk;
	RIPPLE_3DOBJ *ripobj = work->ripobj;
	FLD_3DObjDraw( &ripobj->obj );
}

//==============================================================================
//	data
//==============================================================================
//--------------------------------------------------------------
///	水波紋EOA_H
//--------------------------------------------------------------
static const EOA_H_NPP DATA_EoaH_Ripple =
{
	RIPPLE_WORK_SIZE,
	EoaRipple_Init,
	EoaRipple_Delete,
	EoaRipple_Move,
	EoaRipple_Draw,
};

