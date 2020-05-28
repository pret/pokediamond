//******************************************************************************
/**
 * 
 * @file	fldeff_footmark.c
 * @brief	フィールドOBJ足跡
 * @author	kagaya
 * @data	05.07.13
 *
 */
//******************************************************************************
#include "common.h"
#include "fieldsys.h"
#include "field_effect.h"
#include "fieldobj.h"
#include "fldeff_footmark.h"

//==============================================================================
//	define
//==============================================================================
#define FOOTMARK_VANISH_START_FRAME (16)						///<点滅開始フレーム(赤緑40)
//#define FOOTMARK_VANISH_START_FRAME (20)						///<点滅開始フレーム(赤緑40)
#define FOOTMARK_VANISH_END_FRAME (28)							///<点滅終了フレーム(赤緑56)

//--------------------------------------------------------------
///	足跡識別
//--------------------------------------------------------------
enum
{
	FOOTMARK_WALK_UP = 0,										///<足跡　上
	FOOTMARK_WALK_DOWN,											///<足跡　下
	FOOTMARK_WALK_LEFT,											///<足跡　左
	FOOTMARK_WALK_RIGHT,										///<足跡　右
	FOOTMARK_CYCLE_UD,											///<自転車足跡 上下
	FOOTMARK_CYCLE_LR,											///<自転車足跡 左右
	FOOTMARK_CYCLE_UL,											///<自転車足跡 上左
	FOOTMARK_CYCLE_UR,											///<自転車足跡 上右
	FOOTMARK_CYCLE_DL,											///<自転車足跡 下左
	FOOTMARK_CYCLE_DR,											///<自転車足跡 下右
	FOOTMARK_MAX,												///<足跡最大数
};

//--------------------------------------------------------------
///	足跡タイプ
//--------------------------------------------------------------
typedef enum
{
	FOOTMARKTYPE_NORMAL = 0,		///<足跡タイプ　２足
	FOOTMARKTYPE_CYCLE,				///<足跡タイプ　自転車
	FOOTMARKTYPE_SNOW,				///<足跡タイプ　雪
	FOOTMARKTYPE_SNOWDEEP,			///<足跡タイプ　深い雪
}FOOTMARKTYPE;

//==============================================================================
//	typedef struct
//==============================================================================
//--------------------------------------------------------------
///	FE_FOOTMARK型
//--------------------------------------------------------------
typedef struct _TAG_FE_FOOTMARK * FE_FOOTMARK_PTR;

//--------------------------------------------------------------
///	FE_FOOTMARK構造体
//--------------------------------------------------------------
typedef struct _TAG_FE_FOOTMARK
{
	FE_SYS *fes;
	NNSG3dRenderObj render[FOOTMARK_MAX];
	NNSG3dRenderObj render_snow[FOOTMARK_MAX];
	NNSG3dResMdl *model[FOOTMARK_MAX];
	NNSG3dResMdl *model_snow[FOOTMARK_MAX];
	NNSG3dResFileHeader *res_file[FOOTMARK_MAX];
	NNSG3dResFileHeader *res_file_snow[FOOTMARK_MAX];
}FE_FOOTMARK;

#define FE_FOOTMARK_SIZE (sizeof(FE_FOOTMARK)) ///<FE_FOOTMARKサイズ

//--------------------------------------------------------------
///	FOOTMARK_ADD_H構造体
//--------------------------------------------------------------
typedef struct
{
	FOOTMARKTYPE type;
	NNSG3dRenderObj *render;
	NNSG3dResMdl *model;
}FOOTMARK_ADD_H;

//--------------------------------------------------------------
///	FOOTMARK_WORK構造体
//--------------------------------------------------------------
typedef struct
{
	int seq_no;
	int frame;
	int vanish_sw;
	int alpha;
	FOOTMARKTYPE type;
	NNSG3dRenderObj *render;
	NNSG3dResMdl *model;
}FOOTMARK_WORK;

#define FOOTMARK_WORK_SIZE (sizeof(FOOTMARK_WORK))

//==============================================================================
//	プロトタイプ
//==============================================================================
static void FootMark_GraphicInit( FE_FOOTMARK_PTR fm );
static void FootMark_GraphicDelete( FE_FOOTMARK_PTR fm );

static NNSG3dRenderObj * FootMark_TypeRenderGet(
		FE_FOOTMARK_PTR fm, FOOTMARKTYPE type, int now_dir, int old_dir );
static NNSG3dResMdl * FootMark_TypeMdlGet(
		FE_FOOTMARK_PTR fm, FOOTMARKTYPE type, int now_dir, int old_dir );

static EOA_PTR FldOBJFootMark_AddMain( CONST_FIELD_OBJ_PTR fldobj, FOOTMARKTYPE type );

static const u32 DATA_3DModelArcID_FootMark[FOOTMARK_MAX];
static const u32 DATA_3DModelArcID_FootMarkSnow[FOOTMARK_MAX];
static const int DATA_FootMarkCycleDirTbl[DIR_4_MAX][DIR_4_MAX];
static const EOA_H_NPP DATA_EoaH_FootMark;

//==============================================================================
//	足跡　システム
//==============================================================================
//--------------------------------------------------------------
/**
 * 足跡初期化
 * @param	fes		FE_SYS_PTR
 * @retval	FE_FOOTMARK_PTR		FE_FOOTMARK_PTR
 */
//--------------------------------------------------------------
void * FE_FootMark_Init( FE_SYS *fes )
{
	FE_FOOTMARK_PTR fm;
	
	fm = FE_AllocClearMemory( fes, FE_FOOTMARK_SIZE, ALLOC_FR, 0 );
	fm->fes = fes;
	
	FootMark_GraphicInit( fm );
	return( fm );
}

//--------------------------------------------------------------
/**
 * 足跡削除
 * @param	fm		FE_FOOTMARK_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void FE_FootMark_Delete( void *work )
{
	FE_FOOTMARK_PTR fm = work;
	FootMark_GraphicDelete( fm );
	FE_FreeMemory( fm );
}

//==============================================================================
//	足跡	パーツ
//==============================================================================

//==============================================================================
//	足跡　グラフィック
//==============================================================================
//--------------------------------------------------------------
/**
 * 足跡 グラフィック初期化
 * @param	fm		FE_FOOTMARK_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FootMark_GraphicInit( FE_FOOTMARK_PTR fm )
{
	int i;
	u32 id;
	
	for( i = 0; i < FOOTMARK_MAX; i++ ){
		id = DATA_3DModelArcID_FootMark[i];
		FE_simple3DModelInit( fm->fes, id, ALLOC_FR,
			&fm->render[i], &fm->model[i], &fm->res_file[i] );
		
		id = DATA_3DModelArcID_FootMarkSnow[i];
		FE_simple3DModelInit( fm->fes, id, ALLOC_FR,
			&fm->render_snow[i], &fm->model_snow[i], &fm->res_file_snow[i] );
	}
}

//--------------------------------------------------------------
/**
 * 足跡　グラフィック削除
 * @param	fm		FE_FOOTMARK_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FootMark_GraphicDelete( FE_FOOTMARK_PTR fm )
{
	int i;
	
	for( i = 0; i < FOOTMARK_MAX; i++ ){
		FE_FreeMemory( fm->res_file[i] );
		FE_FreeMemory( fm->res_file_snow[i] );
	}
}

//--------------------------------------------------------------
/**
 * 指定タイプのレンダ取得
 * @param	fm		FE_FOOTMARK_PTR
 * @param	type	FOOTMARK_TYPE_NORMAL等
 * @param	now_dir	現在の向き DIR_UP等
 * @param	old_dir	過去の向き DIR_UP等
 * @param	attr	FOOTMARK_ATTR
 * @retval	NNSG3dRenderObj 指定のレンダ
 */
//--------------------------------------------------------------
static NNSG3dRenderObj * FootMark_TypeRenderGet(
		FE_FOOTMARK_PTR fm, FOOTMARKTYPE type, int now_dir, int old_dir )
{
	int no;
	NNSG3dRenderObj * render = NULL;
	
	switch( type ){
	case FOOTMARKTYPE_NORMAL:
		no = FOOTMARK_WALK_UP + now_dir;
		render = &fm->render[no];
		break;
	case FOOTMARKTYPE_CYCLE:
		no = DATA_FootMarkCycleDirTbl[old_dir][now_dir];
		render = &fm->render[no];
		break;
	case FOOTMARKTYPE_SNOW:
		no = FOOTMARK_WALK_UP + now_dir;
		render = &fm->render_snow[no];
		break;
	case FOOTMARKTYPE_SNOWDEEP:
		no = DATA_FootMarkCycleDirTbl[old_dir][now_dir];
		render = &fm->render_snow[no];
		break;
	}
	
	GF_ASSERT( render != NULL && "FootMark_TypeRenderGet()不正\n" );
	return( render );
}

//--------------------------------------------------------------
/**
 * 指定タイプのモデル取得
 * @param	fm		FE_FOOTMARK_PTR
 * @param	type	FOOTMARK_TYPE_NORMAL等
 * @param	now_dir	現在の向き DIR_UP等
 * @param	old_dir	過去の向き DIR_UP等
 * @param	attr	FOOTMARK_ATTR
 * @retval	NNSG3dMdl 指定のレンダ
 */
//--------------------------------------------------------------
static NNSG3dResMdl * FootMark_TypeMdlGet(
		FE_FOOTMARK_PTR fm, FOOTMARKTYPE type, int now_dir, int old_dir )
{
	int no = 0;
	NNSG3dResMdl *model = NULL;
	
	switch( type ){
	case FOOTMARKTYPE_NORMAL:
		no = FOOTMARK_WALK_UP + now_dir;
		model = fm->model[no];
		break;
	case FOOTMARKTYPE_CYCLE:
		no = DATA_FootMarkCycleDirTbl[old_dir][now_dir];
		model = fm->model[no];
		break;
	case FOOTMARKTYPE_SNOW:
		no = FOOTMARK_WALK_UP + now_dir;
		model = fm->model_snow[no];
		break;
	case FOOTMARKTYPE_SNOWDEEP:
		no = DATA_FootMarkCycleDirTbl[old_dir][now_dir];
		model = fm->model_snow[no];
		break;
	}
	
	GF_ASSERT( model != NULL && "FootMark_TypeMdlGet()不正\n" );
	return( model );
}

//==============================================================================
//	足跡　EOA
//==============================================================================
//--------------------------------------------------------------
/**
 * フィールドOBJ ２速足跡追加
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	eoa		EOA_PTR
 */
//--------------------------------------------------------------
EOA_PTR FE_FldOBJFootMarkNormal_Add( CONST_FIELD_OBJ_PTR fldobj )
{
	return( FldOBJFootMark_AddMain(fldobj,FOOTMARKTYPE_NORMAL) );
}

//--------------------------------------------------------------
/**
 * フィールドOBJ 自転車足跡追加
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	eoa		EOA_PTR
 */
//--------------------------------------------------------------
EOA_PTR FE_FldOBJFootMarkCycle_Add( CONST_FIELD_OBJ_PTR fldobj )
{
	return( FldOBJFootMark_AddMain(fldobj,FOOTMARKTYPE_CYCLE) );
}

//--------------------------------------------------------------
/**
 * フィールドOBJ 雪足跡追加
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	eoa		EOA_PTR
 */
//--------------------------------------------------------------
EOA_PTR FE_FldOBJFootMarkSnow_Add( CONST_FIELD_OBJ_PTR fldobj )
{
	return( FldOBJFootMark_AddMain(fldobj,FOOTMARKTYPE_SNOW) );
}

//--------------------------------------------------------------
/**
 * フィールドOBJ 深い雪足跡追加
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	eoa		EOA_PTR
 */
//--------------------------------------------------------------
EOA_PTR FE_FldOBJFootMarkSnowDeep_Add( CONST_FIELD_OBJ_PTR fldobj )
{
	return( FldOBJFootMark_AddMain(fldobj,FOOTMARKTYPE_SNOWDEEP) );
}

//--------------------------------------------------------------
/**
 * フィールドOBJ足跡追加　メイン
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	attr	FOOTMARK_ATTR
 * @retval	eoa		EOA_PTR
 */
//--------------------------------------------------------------
static EOA_PTR FldOBJFootMark_AddMain( CONST_FIELD_OBJ_PTR fldobj, FOOTMARKTYPE type )
{
	VecFx32 mtx;
	EOA_PTR eoa;
	FOOTMARK_ADD_H head;
	int gx = FieldOBJ_OldPosGX_Get( fldobj );
	int gz = FieldOBJ_OldPosGZ_Get( fldobj );
	fx32 y = FieldOBJ_VecPosYGet( fldobj );
	int now_dir = FieldOBJ_DirDispGet( fldobj );
	int old_dir = FieldOBJ_DirDispOldGet( fldobj );
	int pri = FieldOBJ_TCBPriGet( fldobj, FLDOBJ_TCBPRI_OFFS_AFTER );
	FE_SYS *fes = FE_FieldOBJ_FE_SYS_Get( fldobj );
	FE_FOOTMARK_PTR fm = FE_EffectWorkGet( fes, FE_FLD_FOOTMARK );
	
	head.render = FootMark_TypeRenderGet( fm, type, now_dir, old_dir );
	head.model = FootMark_TypeMdlGet( fm, type, now_dir, old_dir );
	head.type = type;
	
	FieldOBJTool_GridCenterPosGet( gx, gz, &mtx );
	mtx.y = y;
	
	switch( type ){
	case FOOTMARKTYPE_NORMAL:
	case FOOTMARKTYPE_CYCLE:
		mtx.y += NUM_FX32( -8 );
			
		if( type == FOOTMARK_WALK_LEFT || type == FOOTMARK_WALK_RIGHT ){
			mtx.z += NUM_FX32( -2 );
		}else{
			mtx.z += NUM_FX32( 1 );
		}
		
		break;
	case FOOTMARKTYPE_SNOW:
	case FOOTMARKTYPE_SNOWDEEP:
		mtx.y += NUM_FX32( -10 );
			
		if( type == FOOTMARK_WALK_LEFT || type == FOOTMARK_WALK_RIGHT ){
			mtx.z += NUM_FX32( -2 );
		}else{
			mtx.z += NUM_FX32( 2 );
		}
	}
	
	eoa = FE_EoaAddNpp( fes, &DATA_EoaH_FootMark, &mtx, 0, &head, pri );
	return( eoa );
}

//--------------------------------------------------------------
/**
 * EOA 足跡　初期化
 * @param	eoa	EOA_PTR
 * @param	wk	eoa work *
 * @retval	int TRUE=正常終了。FALSE=異常終了
 */
//--------------------------------------------------------------
static int EoaFootMark_Init( EOA_PTR eoa, void *wk )
{
	VecFx32 mtx;
	FOOTMARK_WORK *work;
	const FOOTMARK_ADD_H *head;
	
	work = wk;
	work->type = EOA_AddParamGet( eoa );
	
	head = EOA_AddPtrGet( eoa );
	work->render = head->render;
	work->model = head->model;
	work->alpha = 31;
	work->type = head->type;
	
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * EOA 足跡　削除
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work *
 * @retval	nothing
 */
//--------------------------------------------------------------
static void EoaFootMark_Delete( EOA_PTR eoa, void *wk )
{
}

//--------------------------------------------------------------
/**
 * EOA 足跡　動作
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work *
 * @retval	nothing
 */
//--------------------------------------------------------------
static void EoaFootMark_Move( EOA_PTR eoa, void *wk )
{
	FOOTMARK_WORK *work;
	
	work = wk;
	
	switch( work->seq_no ){
	case 0:
		work->frame++;
		
		if( work->frame >= FOOTMARK_VANISH_START_FRAME ){
			work->seq_no++;
		}
		
		break;
	case 1:
		work->alpha -= 2;
		
		if( work->alpha < 0 ){
			FE_EoaDelete( eoa );
			return;
		}
	}
}

//--------------------------------------------------------------
/**
 * EOA 足跡　描画
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work *
 * @retval	nothing
 */
//--------------------------------------------------------------
static void EoaFootMark_Draw( EOA_PTR eoa, void *wk )
{
	FOOTMARK_WORK *work;
	
	work = wk;
	
	if( work->vanish_sw == TRUE ){
		return;
	}
	
	{
		VecFx32 vec;
		VecFx32 scale = { FX32_ONE, FX32_ONE, FX32_ONE };
		MtxFx33 rot	  = { FX32_ONE, 0,0,0, FX32_ONE, 0,0,0,FX32_ONE};
		
		EOA_MatrixGet( eoa, &vec );
		
		NNS_G3dMdlUseMdlAlpha( work->model );
		NNS_G3dMdlSetMdlAlphaAll( work->model, work->alpha );
		simple_3DModelDraw( work->render, &vec, &rot, &scale );
	}
}

//==============================================================================
//	data
//==============================================================================
//--------------------------------------------------------------
///	足跡imdテーブル　並びはFOOTMARK_WALK_UP等の値に一致
//--------------------------------------------------------------
static const u32 DATA_3DModelArcID_FootMark[FOOTMARK_MAX] =
{
	NARC_fldeff_f_mark_u_nsbmd,
	NARC_fldeff_f_mark_d_nsbmd,
	NARC_fldeff_f_mark_l_nsbmd,
	NARC_fldeff_f_mark_r_nsbmd,
	NARC_fldeff_c_mark_u_nsbmd,
	NARC_fldeff_c_mark_l_nsbmd,
	NARC_fldeff_c_mark_ul_nsbmd,
	NARC_fldeff_c_mark_ur_nsbmd,
	NARC_fldeff_c_mark_dl_nsbmd,
	NARC_fldeff_c_mark_dr_nsbmd,
};

//--------------------------------------------------------------
///	足跡imdテーブル　並びはFOOTMARK_WALK_UP等の値に一致　雪
//--------------------------------------------------------------
static const u32 DATA_3DModelArcID_FootMarkSnow[FOOTMARK_MAX] =
{
	NARC_fldeff_nf_mark_u_nsbmd,
	NARC_fldeff_nf_mark_d_nsbmd,
	NARC_fldeff_nf_mark_l_nsbmd,
	NARC_fldeff_nf_mark_r_nsbmd,
	NARC_fldeff_nc_mark_u_nsbmd,
	NARC_fldeff_nc_mark_l_nsbmd,
	NARC_fldeff_nc_mark_ul_nsbmd,
	NARC_fldeff_nc_mark_ur_nsbmd,
	NARC_fldeff_nc_mark_dl_nsbmd,
	NARC_fldeff_nc_mark_dr_nsbmd,
};

//--------------------------------------------------------------
///	自転車足跡テーブル [過去方向][現在方向]
//--------------------------------------------------------------
static const int DATA_FootMarkCycleDirTbl[DIR_4_MAX][DIR_4_MAX] =
{
	{FOOTMARK_CYCLE_UD,FOOTMARK_CYCLE_UD,FOOTMARK_CYCLE_UR,FOOTMARK_CYCLE_UL},
	{FOOTMARK_CYCLE_UD,FOOTMARK_CYCLE_UD,FOOTMARK_CYCLE_DR,FOOTMARK_CYCLE_DL},
	{FOOTMARK_CYCLE_DL,FOOTMARK_CYCLE_UL,FOOTMARK_CYCLE_LR,FOOTMARK_CYCLE_LR},
	{FOOTMARK_CYCLE_DR,FOOTMARK_CYCLE_UR,FOOTMARK_CYCLE_LR,FOOTMARK_CYCLE_LR},
};

//--------------------------------------------------------------
///	足跡EOA_H
//--------------------------------------------------------------
static const EOA_H_NPP DATA_EoaH_FootMark =
{
	FOOTMARK_WORK_SIZE,
	EoaFootMark_Init,
	EoaFootMark_Delete,
	EoaFootMark_Move,
	EoaFootMark_Draw,
};

