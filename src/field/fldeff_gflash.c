//******************************************************************************
/**
 * 
 * @file	fldeff_gflash.c
 * @brief	フィールドOBJ　地面フラッシュ
 * @author	k.ohno
 * @data	06.05.05
 *
 */
//******************************************************************************
#include "common.h"
#include "fieldsys.h"
#include "field_effect.h"
#include "fieldobj.h"
#include "fldeff_gflash.h"

#include "field_3dobj.h"

//==============================================================================
//	define
//==============================================================================

#define GFLASH_DRAW_Y_OFFSET (0)
#define GFLASH_DRAW_Z_OFFSET (0)

#define GFLASH_ON_FRAME (30)
#define GFLASH_OFF_FRAME (GFLASH_ON_FRAME+30)

//==============================================================================
//	typedef struct
//==============================================================================
//--------------------------------------------------------------
///	FE_GFLASH型
//--------------------------------------------------------------
typedef struct _TAG_FE_GFLASH * FE_GFLASH_PTR;

//--------------------------------------------------------------
///	FE_GFLASH構造体
//--------------------------------------------------------------
typedef struct _TAG_FE_GFLASH
{
	int heap_id;
	FE_SYS *fes;
	
	FLD_3DOBJ_MDL obj_mdl;
	FLD_3DOBJ_ANM obj_anm;
	NNSFndAllocator allocator;
}FE_GFLASH;

#define FE_GFLASH_SIZE (sizeof(FE_GFLASH)) ///<FE_GFLASHサイズ

//--------------------------------------------------------------
///	GFLASH_ADD_H構造体
//--------------------------------------------------------------
typedef struct
{
	FE_SYS *fes;					///<FE_SYS_PTR
	FE_GFLASH_PTR gflash;		///<FE_GFLASH_PTR
}GFLASH_ADD_H;

#define GFLASH_ADD_H_SIZE (sizeof(GFLASH_ADD_H)) ///<GFLASH_ADD_Hサイズ

//--------------------------------------------------------------
///	GFLASH_3DOBJ構造体
//--------------------------------------------------------------
typedef struct
{
	NNSG3dAnmObj*			pAnmObj;			// アニメーションオブジェ
	NNSFndAllocator allocator;
	fx32 frame;
	FLD_3DOBJ obj;
}GFLASH_3DOBJ;

#define GFLASH_3DOBJ_SIZE (sizeof(GFLASH_3DOBJ))

//--------------------------------------------------------------
///	GFLASH_WORK構造体
//--------------------------------------------------------------
typedef struct
{
	GFLASH_3DOBJ *ripobj;
	GFLASH_ADD_H head;						///<追加時のGFLASH_ADD_H
}GFLASH_WORK;

#define GFLASH_WORK_SIZE (sizeof(GFLASH_WORK))	///<GFLASH_WORKサイズ

//==============================================================================
//	プロトタイプ
//==============================================================================
static FE_GFLASH_PTR GFlash_AllocMemory( int heap_id );
static void GFlash_FreeMemory( FE_GFLASH_PTR gflash );

static void GFlash_GraphicInit( FE_GFLASH_PTR gflash );
static void GFlash_GraphicDelete( FE_GFLASH_PTR gflash );

static const EOA_H_NPP DATA_EoaH_GFlash;

//==============================================================================
//	地面フラッシュ　システム
//==============================================================================
//--------------------------------------------------------------
/**
 * 地面フラッシュ初期化
 * @param	fes		FE_SYS_PTR
 * @param	heap_id	ヒープID
 * @retval	FE_GFLASH_PTR	FE_GFLASH_PTR
 */
//--------------------------------------------------------------
void * FE_GFlash_Init( FE_SYS *fes )
{
	FE_GFLASH_PTR gflash;
	
	gflash = FE_AllocClearMemory( fes, FE_GFLASH_SIZE, ALLOC_FR, 0 );
	gflash->fes = fes;
	
	GFlash_GraphicInit( gflash );
	return( gflash );
}

//--------------------------------------------------------------
/**
 * 地面フラッシュ削除
 * @param	gflash		FE_GFLASH_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void FE_GFlash_Delete( void *work )
{
	FE_GFLASH_PTR gflash = work;
	GFlash_GraphicDelete( gflash );
	FE_FreeMemory( gflash );
}

//==============================================================================
//	地面フラッシュ	パーツ
//==============================================================================

//==============================================================================
//	地面フラッシュ　グラフィック
//==============================================================================
//--------------------------------------------------------------
/**
 * 地面フラッシュ グラフィック初期化
 * @param	gflash	FE_GFLASH_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void GFlash_GraphicInit( FE_GFLASH_PTR gflash )
{
	FE_InitAllocator( gflash->fes, &gflash->allocator );
	FE_3DObjMdlLoad( gflash->fes, &gflash->obj_mdl, NARC_fldeff_ug_ef_gflash_nsbmd, ALLOC_FR );
	FE_3DObjAnmLoad( gflash->fes, &gflash->obj_anm, &gflash->obj_mdl, &gflash->allocator,
		NARC_fldeff_ug_ef_gflash_nsbtp, ALLOC_FR );
}

//--------------------------------------------------------------
/**
 * 地面フラッシュ グラフィック削除
 * @param	gflash	FE_GFLASH_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void GFlash_GraphicDelete( FE_GFLASH_PTR gflash )
{
	FLD_3DObjMdlDelete( &gflash->obj_mdl );	
	FLD_3DObjAnmDelete( &gflash->obj_anm, &gflash->allocator );	
}

//==============================================================================
//	地面フラッシュEOA
//==============================================================================
//--------------------------------------------------------------
/**
 * 地面フラッシュ追加
 * @param	fldobj	対象となるFIELD_OBJ_PTR
 * @param	gx		表示するグリッドX座標
 * @param	gz		表示するグリッドZ座標
 * @retval	none
 */
//--------------------------------------------------------------
void FE_FldOBJGFlashSet( FIELDSYS_WORK *fsys, int gx, int gz )
{
	int pri,param;
	GFLASH_ADD_H head;
	VecFx32 mtx;

	head.fes = fsys->fes;
//	head.fes = FE_FieldOBJ_FE_SYS_PTR_Get( fldobj );
	head.gflash = FE_EffectWorkGet( head.fes, FE_UG_TRAP_GFLASH );

	mtx.x = GRID_SIZE_FX32( gx ) + GRID_HALF_FX32;
	mtx.y = 0;
	mtx.z = GRID_SIZE_FX32( gz ) + GRID_HALF_FX32;

	param = 0;
//	pri = FE_FldOBJ_TCBPriGet( fldobj, 1 );
	FE_EoaAddNpp( head.fes, &DATA_EoaH_GFlash, &mtx, param, &head,0xff );
}

//--------------------------------------------------------------
/**
 * EOA 地面フラッシュ　初期化
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work *
 * @retval	int		TRUE=正常終了。FALSE=異常終了
 */
//--------------------------------------------------------------
static int EoaGFlash_Init( EOA_PTR eoa, void *wk )
{
	VecFx32 mtx;
	GFLASH_WORK *work = wk;
	GFLASH_3DOBJ *ripobj = work->ripobj;
	const GFLASH_ADD_H *head = EOA_AddPtrGet( eoa );
	
	work->head = *head;
	ripobj = FE_AllocClearMemory( work->head.fes, GFLASH_3DOBJ_SIZE, ALLOC_LO, 0 );
	work->ripobj = ripobj;
	
	FE_InitAllocator( work->head.fes, &ripobj->allocator );
	
	ripobj->pAnmObj = NNS_G3dAllocAnmObj( 
			&ripobj->allocator,
			work->head.gflash->obj_anm.pOneResAnm,
			work->head.gflash->obj_mdl.pModel );
	
	NNS_G3dAnmObjInit(
		ripobj->pAnmObj,
		work->head.gflash->obj_anm.pOneResAnm,
		work->head.gflash->obj_mdl.pModel,
		work->head.gflash->obj_mdl.pMdlTex );
	
	FLD_3DObjInit( &ripobj->obj, &work->head.gflash->obj_mdl );
	NNS_G3dRenderObjAddAnmObj( &ripobj->obj.render, ripobj->pAnmObj );
	
	EOA_MatrixGet( eoa, &mtx );
	FLD_3DObjSetMatrix( &ripobj->obj, mtx.x, mtx.y, mtx.z );
	
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * EOA 地面フラッシュ　削除
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work *
 * @retval	nothing
 */
//--------------------------------------------------------------
static void EoaGFlash_Delete( EOA_PTR eoa, void *wk )
{
	GFLASH_WORK *work = wk;
	GFLASH_3DOBJ *ripobj = work->ripobj;
	NNS_G3dFreeAnmObj( &ripobj->allocator, ripobj->pAnmObj );
	FE_FreeMemory( ripobj );
}

//--------------------------------------------------------------
/**
 * EOA 地面フラッシュ　動作
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work *
 * @retval	nothing
 */
//--------------------------------------------------------------
static void EoaGFlash_Move( EOA_PTR eoa, void *wk )
{
	GFLASH_WORK *work = wk;
	GFLASH_3DOBJ *ripobj = work->ripobj;
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
 * EOA 地面フラッシュ　描画
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work *
 * @retval	nothing
 */
//--------------------------------------------------------------
static void EoaGFlash_Draw( EOA_PTR eoa, void *wk )
{
	GFLASH_WORK *work = wk;
	GFLASH_3DOBJ *ripobj = work->ripobj;
	FLD_3DObjDraw( &ripobj->obj );
}

//==============================================================================
//	data
//==============================================================================
//--------------------------------------------------------------
///	地面フラッシュEOA_H
//--------------------------------------------------------------
static const EOA_H_NPP DATA_EoaH_GFlash =
{
	GFLASH_WORK_SIZE,
	EoaGFlash_Init,
	EoaGFlash_Delete,
	EoaGFlash_Move,
	EoaGFlash_Draw,
};

