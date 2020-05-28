//******************************************************************************
/**
 * 
 * @file	fldeff_lgrass.c
 * @brief	フィールドOBJ長い草
 * @author	kagaya
 * @data	05.07.13
 *
 */
//******************************************************************************
#include "common.h"
#include "fieldsys.h"
#include "field_effect.h"
#include "fieldobj.h"

#include "fldeff_lgrass.h"
#include "map_tool.h"

//==============================================================================
//	define
//==============================================================================
#define YURE_KUSA_SET

///長い草表示位置　グリッドからのオフセットX
#define LGRASS_GIRD_VEC_OFFS_X (FLDOBJ_VEC_X_GRID_OFFS_FX32)
///長い草表示位置　グリッドからのオフセットZ
#define LGRASS_GIRD_VEC_OFFS_Z \
	(FLDOBJ_VEC_Z_GRID_OFFS_FX32+FLDOBJ_BLACT_Z_GROUND_OFFS_FX32+(FX32_ONE*4))
///長い草表示位置　地面からのオフセットY
#define LGRASS_GROUND_OFFS_Y (FX32_ONE)

///長い草揺れアニメフレーム数
#define LGRASS_SHAKE_FRAME (12)

//==============================================================================
//	typedef struct
//==============================================================================
//--------------------------------------------------------------
///	FE_LGRASS_PTR型
//--------------------------------------------------------------
typedef struct _TAG_FE_LGRASS * FE_LGRASS_PTR;

//--------------------------------------------------------------
///	FE_LGRASS構造体
//--------------------------------------------------------------
typedef struct _TAG_FE_LGRASS
{
	FE_SYS *fes;
}FE_LGRASS;

#define FE_LGRASS_SIZE (sizeof(FE_LGRASS))	///<FE_GRASSサイズ

//--------------------------------------------------------------
///	LGRASS_ADD_H構造体
//--------------------------------------------------------------
typedef struct
{
	int init_gx;								///<初期X グリッド
	int init_gy;								///<初期Y
	int init_gz;								///<初期Z
	FIELDSYS_WORK *fsys;						///<FIELDSYS_WORK *
	FE_SYS *fes;								///<FE_SYS_PTR
	FE_LGRASS_PTR kusa;							///<FE_GRASS_PTR
	FIELD_OBJ_PTR fldobj;						///<対象のFIELD_OBJ_PTR
}LGRASS_ADD_H;

#define LGRASS_ADD_H_SIZE (sizeof(LGRASS_ADD_H))	///<LGRASS_ADD_Hサイズ

//--------------------------------------------------------------
///	LGRASS_WORK構造体
//--------------------------------------------------------------
typedef struct
{
	int seq_no;									///<動作番号
	int obj_code;								///<対象フィールドOBJ OBJ CODE
	int obj_id;									///<対象フィールドOBJ OBJ ID
	int zone_id;								///<対象フィールドOBJ ZONE ID
	int frame;									///<フレーム
	int height_get;								///<高さ取得済み
	LGRASS_ADD_H head;							///<追加時のLGRASS_ADD_H
	BLACT_WORK_PTR act;							///<ビルボードアクター
}LGRASS_WORK;

#define LGRASS_WORK_SIZE (sizeof(LGRASS_WORK))	///<LGRASS_WORKサイズ

//==============================================================================
//	プロトタイプ
//==============================================================================
static void LGrass_GraphicInit( FE_LGRASS_PTR lgrass );
static void LGrass_GraphicDelete( FE_LGRASS_PTR lgrass );

static const EOA_H_NPP DATA_EoaH_LGrass;
const BLACT_ANIME_TBL DATA_BlActAnmTbl_LGrass[];


const BLACT_ANIME_TBL DATA_BlActAnmTbl_LGrassSmall[];
const BLACT_ANIME_TBL DATA_BlActAnmTbl_LGrassBig[];
const BLACT_ANIME_TBL DATA_BlActAnmTbl_LGrassKiraKira[];

//==============================================================================
//	長い草	システム
//==============================================================================
//--------------------------------------------------------------
/**
 * 長い草初期化
 * @param	fes		FE_SYS_PTR
 * @retval	FE_LGRASS_PTR	FE_GRASS_PTR
 */
//--------------------------------------------------------------
void * FE_LGrass_Init( FE_SYS *fes )
{
	FE_LGRASS_PTR kusa;
	
	kusa = FE_AllocClearMemory( fes, FE_LGRASS_SIZE, ALLOC_FR, 0 );
	kusa->fes = fes;
	
	LGrass_GraphicInit( kusa );
	return( kusa );
}

//--------------------------------------------------------------
/**
 * 長い草削除
 * @param	kusa		FE_LGRASS_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void FE_LGrass_Delete( void *work )
{
	FE_LGRASS_PTR kusa = work;
	LGrass_GraphicDelete( kusa );
	FE_FreeMemory( kusa );
}

//==============================================================================
//	長い草　グラフィック
//==============================================================================
//--------------------------------------------------------------
/**
 * 長い草　グラフィック初期化
 * @param	kusa	FE_LGRASS_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void LGrass_GraphicInit( FE_LGRASS_PTR kusa )
{
	FE_BlActResAdd_MdlArc( kusa->fes, FE_RESID_MDL_LGRASS, NARC_fldeff_lgrass_ani1_nsbmd );
	FE_BlActResAdd_AnmArc( kusa->fes, FE_RESID_ANM_LGRASS, NARC_fldeff_lgrass_ani1_itpcv_dat );
	FE_BlActResAdd_TexArc( kusa->fes,
			FE_RESID_TEX_LGRASS, NARC_fldeff_lgrass_ani1_nsbtx, TEXRESM_TEX_CUT_TRUE );
	
	FE_BlActHeaderManageAddResmID( kusa->fes, FE_BLACT_H_ID_LGRASS,
			FE_RESID_MDL_LGRASS, FE_RESID_ANM_LGRASS,
			FE_RESID_TEX_LGRASS, FE_BLACT_TEX_VRAM,
			DATA_BlActAnmTbl_LGrass );
}

//--------------------------------------------------------------
/**
 * 長い草　グラフィック削除
 * @param	kusa	FE_LGRASS_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void LGrass_GraphicDelete( FE_LGRASS_PTR kusa )
{
	FE_BlActResDelete_Mdl( kusa->fes, FE_RESID_MDL_LGRASS );
	FE_BlActResDelete_Anm( kusa->fes, FE_RESID_ANM_LGRASS );
	FE_BlActResDelete_Tex( kusa->fes, FE_RESID_TEX_LGRASS );
	FE_BlActHeaderManageFree( kusa->fes, FE_BLACT_H_ID_LGRASS );
}

//==============================================================================
//	長い草パーツ
//==============================================================================

//==============================================================================
//	長い草　EOA
//==============================================================================
//--------------------------------------------------------------
/**
 * フィールドOBJ用長い草追加
 * @param	fldobj		FIELD_OBJ_PTR
 * @param	shake		TRUE=長い草ゆれから開始。FALSE=揺れなしから開始
 * @retval	nothing		
 */
//--------------------------------------------------------------
void FE_FldOBJLGrass_Add( FIELD_OBJ_PTR fldobj, int shake )
{
	int pri;
	VecFx32 mtx;
	LGRASS_ADD_H head;
	FE_SYS *fes;
	EOA_PTR eoa;
	
	fes = FE_FieldOBJ_FE_SYS_Get( fldobj );
	
	head.init_gx = FieldOBJ_NowPosGX_Get( fldobj );
	head.init_gy = FieldOBJ_NowPosGY_Get( fldobj );
	head.init_gz = FieldOBJ_NowPosGZ_Get( fldobj );
	head.fes = fes;
	head.fsys = FE_FieldSysWorkGet( fes );
	head.kusa = FE_EffectWorkGet( fes, FE_FLD_LGRASS );
	head.fldobj = fldobj;
	
	FieldOBJ_VecPosGet( fldobj, &mtx );
	pri = FieldOBJ_TCBPriGet( fldobj, FLDOBJ_TCBPRI_OFFS_AFTER );
	eoa = FE_EoaAddNpp( fes, &DATA_EoaH_LGrass, &mtx, shake, &head, pri );
}

//--------------------------------------------------------------
/**
 * EOA 長い草　初期化
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work *
 * @retval	int		TRUE=正常終了。FALSE=異常終了
 */
//--------------------------------------------------------------
static int EoaLGrass_Init( EOA_PTR eoa, void *wk )
{
	int gx,gz;
	VecFx32 vec;
	LGRASS_WORK *work;
	const LGRASS_ADD_H *head;
	
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
	
	vec.x += LGRASS_GIRD_VEC_OFFS_X;
	vec.z += LGRASS_GIRD_VEC_OFFS_Z;
	EOA_MatrixSet( eoa, &vec );
	
	work->act = FE_BlActAddID( work->head.fes, FE_BLACT_H_ID_LGRASS, &vec );
	
	if( EOA_AddParamGet(eoa) == FALSE ){						//長い草揺れなし
		work->seq_no = 1;
	}
	
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * EOA 長い草　削除
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work *
 * @retval	nothing
 */
//--------------------------------------------------------------
static void EoaLGrass_Delete( EOA_PTR eoa, void *wk )
{
	LGRASS_WORK *work;
	
	work = wk;
	BLACT_Delete( work->act );
}

//--------------------------------------------------------------
/**
 * EOA 長い草　動作
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work *
 * @retval	nothing
 */
//--------------------------------------------------------------
static void EoaLGrass_Move( EOA_PTR eoa, void *wk )
{
	int frame;
	LGRASS_WORK *work;
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
		
		if( frame >= LGRASS_SHAKE_FRAME ){
			work->seq_no = 1;
		}
		
		break;
	case 1:
		BLACT_AnmFrameSet( work->act, NUM_FX32(LGRASS_SHAKE_FRAME) );
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
 * EOA 長い草　描画
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work *
 * @retval	nothing
 */
//--------------------------------------------------------------
static void EoaLGrass_Draw( EOA_PTR eoa, void *wk )
{
	VecFx32 vec;
	LGRASS_WORK *work;
	FIELD_OBJ_PTR fldobj;
	
	work = wk;
	fldobj = work->head.fldobj;
	
	if( FieldOBJ_CheckSameIDOBJCodeIn(
		fldobj,work->obj_code,work->obj_id,work->zone_id) == FALSE ){
		FE_EoaDelete( eoa );
		return;
	}
	
	EOA_MatrixGet( eoa, &vec );
	BLACT_MatrixSet( work->act, &vec );
}

//--------------------------------------------------------------
///	長い草EOA_H
//--------------------------------------------------------------
static const EOA_H_NPP DATA_EoaH_LGrass =
{
	LGRASS_WORK_SIZE,
	EoaLGrass_Init,
	EoaLGrass_Delete,
	EoaLGrass_Move,
	EoaLGrass_Draw,
};

//--------------------------------------------------------------
///	長い草アニメ
//--------------------------------------------------------------
static const BLACT_ANIME_TBL DATA_BlActAnmTbl_LGrass[] =
{
	{ 0, LGRASS_SHAKE_FRAME, BLACT_ANIM_LOOP },
	{ 0, 0, BLACT_ANIM_CMD_MAX },
};
