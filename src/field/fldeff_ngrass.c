//******************************************************************************
/**
 * 
 * @file	fldeff_ngrass.c
 * @brief	フィールドOBJ沼草
 * @author	kagaya
 * @data	05.07.13
 *
 */
//******************************************************************************
#include "common.h"
#include "fieldsys.h"
#include "field_effect.h"
#include "fieldobj.h"

#include "fldeff_ngrass.h"
#include "map_tool.h"

//==============================================================================
//	define
//==============================================================================
#define YURE_KUSA_SET

///沼草表示位置　グリッドからのオフセットX
#define NGRASS_GIRD_VEC_OFFS_X (FLDOBJ_VEC_X_GRID_OFFS_FX32-(FX32_ONE/2))
///沼草表示位置　グリッドからのオフセットZ
#define NGRASS_GIRD_VEC_OFFS_Z \
	(FLDOBJ_VEC_Z_GRID_OFFS_FX32+FLDOBJ_BLACT_Z_GROUND_OFFS_FX32-NUM_FX32(1))
/*
#define NGRASS_GIRD_VEC_OFFS_Z \
	(FLDOBJ_VEC_Z_GRID_OFFS_FX32+FLDOBJ_BLACT_Z_GROUND_OFFS_FX32+(FX32_ONE*4))
*/
///沼草表示位置　地面からのオフセットY
#define NGRASS_GROUND_OFFS_Y (-NUM_FX32(8))

///沼草揺れアニメフレーム数
#define NGRASS_SHAKE_FRAME (2)

//==============================================================================
//	typedef struct
//==============================================================================
//--------------------------------------------------------------
///	FE_NGRASS_PTR型
//--------------------------------------------------------------
typedef struct _TAG_FE_NGRASS * FE_NGRASS_PTR;

//--------------------------------------------------------------
///	FE_NGRASS構造体
//--------------------------------------------------------------
typedef struct _TAG_FE_NGRASS
{
	FE_SYS *fes;
}FE_NGRASS;

#define FE_NGRASS_SIZE (sizeof(FE_NGRASS))	///<FE_GRASSサイズ

//--------------------------------------------------------------
///	NGRASS_ADD_H構造体
//--------------------------------------------------------------
typedef struct
{
	int init_gx;								///<初期X グリッド
	int init_gy;								///<初期Y
	int init_gz;								///<初期Z
	FIELDSYS_WORK *fsys;						///<FIELDSYS_WORK *
	FE_SYS *fes;								///<FE_SYS_PTR
	FE_NGRASS_PTR kusa;							///<FE_GRASS_PTR
	FIELD_OBJ_PTR fldobj;						///<対象のFIELD_OBJ_PTR
}NGRASS_ADD_H;

#define NGRASS_ADD_H_SIZE (sizeof(NGRASS_ADD_H))	///<NGRASS_ADD_Hサイズ

//--------------------------------------------------------------
///	NGRASS_WORK構造体
//--------------------------------------------------------------
typedef struct
{
	int seq_no;									///<動作番号
	int obj_code;								///<対象フィールドOBJ OBJ CODE
	int obj_id;									///<対象フィールドOBJ OBJ ID
	int zone_id;								///<対象フィールドOBJ ZONE ID
	int frame;									///<フレーム
	int height_get;								///<高さ取得
	NGRASS_ADD_H head;							///<追加時のNGRASS_ADD_H
	BLACT_WORK_PTR act;							///<ビルボードアクター
}NGRASS_WORK;

#define NGRASS_WORK_SIZE (sizeof(NGRASS_WORK))	///<NGRASS_WORKサイズ

//==============================================================================
//	プロトタイプ
//==============================================================================
static void NGrass_GraphicInit( FE_NGRASS_PTR ngrass );
static void NGrass_GraphicDelete( FE_NGRASS_PTR ngrass );

static const EOA_H_NPP DATA_EoaH_NGrass;
const BLACT_ANIME_TBL DATA_BlActAnmTbl_NGrass[];


const BLACT_ANIME_TBL DATA_BlActAnmTbl_NGrassSmall[];
const BLACT_ANIME_TBL DATA_BlActAnmTbl_NGrassBig[];
const BLACT_ANIME_TBL DATA_BlActAnmTbl_NGrassKiraKira[];

//==============================================================================
//	沼草	システム
//==============================================================================
//--------------------------------------------------------------
/**
 * 沼草初期化
 * @param	fes		FE_SYS_PTR
 * @retval	FE_NGRASS_PTR	FE_GRASS_PTR
 */
//--------------------------------------------------------------
void * FE_NGrass_Init( FE_SYS *fes )
{
	FE_NGRASS_PTR kusa;
	
	kusa = FE_AllocClearMemory( fes, FE_NGRASS_SIZE, ALLOC_FR, 0 );
	kusa->fes = fes;
	
	NGrass_GraphicInit( kusa );
	return( kusa );
}

//--------------------------------------------------------------
/**
 * 沼草削除
 * @param	kusa		FE_NGRASS_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void FE_NGrass_Delete( void *work )
{
	FE_NGRASS_PTR kusa = work;
	NGrass_GraphicDelete( kusa );
	FE_FreeMemory( kusa );
}

//==============================================================================
//	沼草　グラフィック
//==============================================================================
//--------------------------------------------------------------
/**
 * 沼草　グラフィック初期化
 * @param	kusa	FE_NGRASS_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void NGrass_GraphicInit( FE_NGRASS_PTR kusa )
{
	FE_BlActResAdd_MdlArc( kusa->fes, FE_RESID_MDL_NGRASS, NARC_fldeff_ngrass_ani1_nsbmd );
	FE_BlActResAdd_AnmArc( kusa->fes, FE_RESID_ANM_NGRASS, NARC_fldeff_ngrass_ani1_itpcv_dat );
	FE_BlActResAdd_TexArc( kusa->fes,
			FE_RESID_TEX_NGRASS, NARC_fldeff_ngrass_ani1_nsbtx, TEXRESM_TEX_CUT_TRUE );
	
	FE_BlActHeaderManageAddResmID( kusa->fes, FE_BLACT_H_ID_NGRASS,
			FE_RESID_MDL_NGRASS, FE_RESID_ANM_NGRASS,
			FE_RESID_TEX_NGRASS, FE_BLACT_TEX_VRAM,
			DATA_BlActAnmTbl_NGrass );
}

//--------------------------------------------------------------
/**
 * 沼草　グラフィック削除
 * @param	kusa	FE_NGRASS_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void NGrass_GraphicDelete( FE_NGRASS_PTR kusa )
{
	FE_BlActResDelete_Mdl( kusa->fes, FE_RESID_MDL_NGRASS );
	FE_BlActResDelete_Anm( kusa->fes, FE_RESID_ANM_NGRASS );
	FE_BlActResDelete_Tex( kusa->fes, FE_RESID_TEX_NGRASS );
	FE_BlActHeaderManageFree( kusa->fes, FE_BLACT_H_ID_NGRASS );
}

//==============================================================================
//	沼草パーツ
//==============================================================================

//==============================================================================
//	沼草　EOA
//==============================================================================
//--------------------------------------------------------------
/**
 * フィールドOBJ用沼草追加
 * @param	fldobj		FIELD_OBJ_PTR
 * @param	shake		TRUE=沼草ゆれから開始。FALSE=揺れなしから開始
 * @retval	nothing		
 */
//--------------------------------------------------------------
void FE_FldOBJNGrass_Add( FIELD_OBJ_PTR fldobj, int shake )
{
	int pri;
	VecFx32 mtx;
	NGRASS_ADD_H head;
	FE_SYS *fes;
	EOA_PTR eoa;
	
	fes = FE_FieldOBJ_FE_SYS_Get( fldobj );
	
	head.init_gx = FieldOBJ_NowPosGX_Get( fldobj );
	head.init_gy = FieldOBJ_NowPosGY_Get( fldobj );
	head.init_gz = FieldOBJ_NowPosGZ_Get( fldobj );
	head.fes = fes;
	head.fsys = FE_FieldSysWorkGet( fes );
	head.kusa = FE_EffectWorkGet( fes, FE_FLD_NGRASS );
	head.fldobj = fldobj;
	
	FieldOBJ_VecPosGet( fldobj, &mtx );
	pri = FieldOBJ_TCBPriGet( fldobj, FLDOBJ_TCBPRI_OFFS_AFTER );
	eoa = FE_EoaAddNpp( fes, &DATA_EoaH_NGrass, &mtx, shake, &head, pri );
}

//--------------------------------------------------------------
/**
 * EOA 沼草　初期化
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work *
 * @retval	int		TRUE=正常終了。FALSE=異常終了
 */
//--------------------------------------------------------------
static int EoaNGrass_Init( EOA_PTR eoa, void *wk )
{
	int gx,gz;
	VecFx32 vec;
	NGRASS_WORK *work;
	const NGRASS_ADD_H *head;
	
	work = wk;
	head = EOA_AddPtrGet( eoa );
	
	work->head = *head;
	work->obj_code = FieldOBJ_OBJCodeGetSeedIn( work->head.fldobj );
	work->obj_id = FieldOBJ_OBJIDGet( work->head.fldobj );
	work->zone_id = FieldOBJ_ZoneIDGet( work->head.fldobj );
	
	vec.x = GRID_SIZE_FX32( work->head.init_gx );
	vec.z = GRID_SIZE_FX32( work->head.init_gz );
	vec.y = FieldOBJ_VecPosYGet( work->head.fldobj );
	work->height_get = FieldOBJTool_GetHeight( work->head.fsys, &vec );
	
	vec.x += NGRASS_GIRD_VEC_OFFS_X;
	vec.y += NGRASS_GROUND_OFFS_Y;
	vec.z += NGRASS_GIRD_VEC_OFFS_Z;
	EOA_MatrixSet( eoa, &vec );
	
	work->act = FE_BlActAddID( work->head.fes, FE_BLACT_H_ID_NGRASS, &vec );
	
	if( EOA_AddParamGet(eoa) == FALSE ){						//沼草揺れなし
		work->seq_no = 1;
	}
	
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * EOA 沼草　削除
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work *
 * @retval	nothing
 */
//--------------------------------------------------------------
static void EoaNGrass_Delete( EOA_PTR eoa, void *wk )
{
	NGRASS_WORK *work;
	
	work = wk;
	BLACT_Delete( work->act );
}

//--------------------------------------------------------------
/**
 * EOA 沼草　動作
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work *
 * @retval	nothing
 */
//--------------------------------------------------------------
static void EoaNGrass_Move( EOA_PTR eoa, void *wk )
{
	int frame;
	NGRASS_WORK *work;
	FIELD_OBJ_PTR fldobj;
	
	work = wk;
	fldobj = work->head.fldobj;
	
	if( FieldOBJ_CheckSameIDOBJCodeIn(
		fldobj,work->obj_code,work->obj_id,work->zone_id) == FALSE ){
		FE_EoaDelete( eoa );
		return;
	}
	
	if( work->height_get == FALSE ){
		VecFx32 mtx,vec;
		
		EOA_MatrixGet( eoa, &mtx );
		
		vec.x = GRID_SIZE_FX32( work->head.init_gx );
		vec.z = GRID_SIZE_FX32( work->head.init_gz );
		vec.y = mtx.y;
		
		work->height_get = FieldOBJTool_GetHeight( work->head.fsys, &vec );
		
		if( work->height_get == TRUE ){
			mtx.y = vec.y;
			EOA_MatrixSet( eoa, &mtx );
		}
	}
	
	switch( work->seq_no ){
	case 0:													//揺れ
		BLACT_AnmFrameChg( work->act, FX32_ONE );
		frame = FX32_NUM( BLACT_AnmFrameGetOffs(work->act) );
		
		if( frame >= NGRASS_SHAKE_FRAME ){
			work->seq_no = 1;
		}
		
		break;
	case 1:
		BLACT_AnmFrameSet( work->act, NUM_FX32(NGRASS_SHAKE_FRAME) );
		BLACT_AnmFrameChg( work->act, 0 );
		work->seq_no = 2;
	case 2:
		{
			int gx = FieldOBJ_NowPosGX_Get( fldobj );
			int gz = FieldOBJ_NowPosGZ_Get( fldobj );
			
			if( work->head.init_gx != gx || work->head.init_gz != gz ){
				FE_EoaDelete( eoa );
				return;
			}
		}
		
		break;
	}
}

//--------------------------------------------------------------
/**
 * EOA 沼草　描画
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work *
 * @retval	nothing
 */
//--------------------------------------------------------------
static void EoaNGrass_Draw( EOA_PTR eoa, void *wk )
{
	VecFx32 vec;
	NGRASS_WORK *work;
	FIELD_OBJ_PTR fldobj;
	
	work = wk;
	fldobj = work->head.fldobj;
	
	if( FieldOBJ_CheckSameID(fldobj,work->obj_id,work->zone_id) == FALSE ){
		FE_EoaDelete( eoa );
		return;
	}
	
	EOA_MatrixGet( eoa, &vec );
	BLACT_MatrixSet( work->act, &vec );
}

//--------------------------------------------------------------
///	沼草EOA_H
//--------------------------------------------------------------
static const EOA_H_NPP DATA_EoaH_NGrass =
{
	NGRASS_WORK_SIZE,
	EoaNGrass_Init,
	EoaNGrass_Delete,
	EoaNGrass_Move,
	EoaNGrass_Draw,
};

//--------------------------------------------------------------
///	沼草アニメ
//--------------------------------------------------------------
static const BLACT_ANIME_TBL DATA_BlActAnmTbl_NGrass[] =
{
	{ 0, NGRASS_SHAKE_FRAME, BLACT_ANIM_LOOP },
	{ 0, 0, BLACT_ANIM_CMD_MAX },
};
