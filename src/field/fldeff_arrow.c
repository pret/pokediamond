//******************************************************************************
/**
 * 
 * @file	fldeff_arrow.c
 * @brief	フィールドOBJ　自機出口矢印
 * @author	kagaya
 * @data	05.07.13
 *
 */
//******************************************************************************
#include "common.h"
#include "fieldsys.h"
#include "field_effect.h"
#include "fieldobj.h"
#include "fldeff_arrow.h"

//==============================================================================
//	define
//==============================================================================
//#define DEBUG_ARROW_WRITE_OFF	//定義で矢印描画OFF

//#define ARROW_DRAW_Z_OFFSET (FX32_ONE*(3))
//#define ARROW_DRAW_Z_OFFSET (FX32_ONE*(5))			///<矢印描画オフセットZ軸
#define ARROW_DRAW_Z_OFFSET (FX32_ONE*(3))				

#define ARROW_OFFSET_FRAME (15)
#define ARROW_OFFSET_NUM_MAX (2)

//==============================================================================
//	typedef struct
//==============================================================================
//--------------------------------------------------------------
///	FE_ARROW型
//--------------------------------------------------------------
typedef struct _TAG_FE_ARROW * FE_ARROW_PTR;

//--------------------------------------------------------------
///	FE_ARROW構造体
//--------------------------------------------------------------
typedef struct _TAG_FE_ARROW
{
	FE_SYS *fes;
	NNSG3dRenderObj render;
	NNSG3dResMdl *model;
	NNSG3dResFileHeader *res_file;
}FE_ARROW;

#define FE_ARROW_SIZE (sizeof(FE_ARROW)) ///<FE_ARROWサイズ

//--------------------------------------------------------------
///	ARROW_ADD_H構造体
//--------------------------------------------------------------
typedef struct
{
	FE_SYS *fes;					///<FE_SYS_PTR
	FE_ARROW_PTR arrow;				///<FE_ARROW_PTR
	PLAYER_STATE_PTR jiki;			///<PLAYER_STATE_PTR
}ARROW_ADD_H;

#define ARROW_ADD_H_SIZE (sizeof(ARROW_ADD_H)) ///<ARROW_ADD_Hサイズ

//--------------------------------------------------------------
///	ARROW_WORK構造体
//--------------------------------------------------------------
typedef struct
{
	int vanish_sw;								///<非表示SW
	int dir;									///<方向
	MATR attr;									///<現在のアトリビュート
	int gx;										///<現在のGX
	int gz;										///<現在のGZ
	int obj_id;									///<自機OBJ ID
	int zone_id;								///<自機ZONE ID
	int frame;									///<表示フレーム
	int draw_offs_no;							///<移動オフセット
	ARROW_ADD_H head;							///<追加時のARROW_ADD_H
}ARROW_WORK;

#define ARROW_WORK_SIZE (sizeof(ARROW_WORK))	///<ARROW_WORKサイズ

//==============================================================================
//	プロトタイプ
//==============================================================================
static void Arrow_GraphicInit( FE_ARROW_PTR arrow );
static void Arrow_GraphicDelete( FE_ARROW_PTR arrow );

static int Arrow_AttrDirGet( MATR attr );

static const EOA_H_NPP DATA_EoaH_Arrow;
static const VecFx32 DATA_ArrowDrawOffsTbl[DIR_4_MAX][ARROW_OFFSET_NUM_MAX];

//==============================================================================
//	矢印　システム
//==============================================================================
//--------------------------------------------------------------
/**
 * 矢印初期化
 * @param	fes		FE_SYS_PTR
 * @retval	FE_ARROW_PTR	FE_ARROW_PTR
 */
//--------------------------------------------------------------
void * FE_Arrow_Init( FE_SYS *fes )
{
	FE_ARROW_PTR arrow;
	
	arrow = FE_AllocClearMemory( fes, FE_ARROW_SIZE, ALLOC_FR, 0 );
	arrow->fes = fes;
	
	Arrow_GraphicInit( arrow );
	return( arrow );
}

//--------------------------------------------------------------
/**
 * 矢印削除
 * @param	arrow		FE_ARROW_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void FE_Arrow_Delete( void *work )
{
	FE_ARROW_PTR arrow = work;
	Arrow_GraphicDelete( arrow );
	FE_FreeMemory( arrow );
}

//==============================================================================
//	矢印	パーツ
//==============================================================================

//==============================================================================
//	矢印　グラフィック
//==============================================================================
//--------------------------------------------------------------
/**
 * 矢印 グラフィック初期化
 * @param	arrow	FE_ARROW_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void Arrow_GraphicInit( FE_ARROW_PTR arrow )
{
	FE_simple3DModelInit( arrow->fes, NARC_fldeff_h_exit_nsbmd, ALLOC_FR,
			&arrow->render, &arrow->model, &arrow->res_file );
}

//--------------------------------------------------------------
/**
 * 矢印 グラフィック削除
 * @param	arrow	FE_ARROW_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void Arrow_GraphicDelete( FE_ARROW_PTR arrow )
{
	FE_FreeMemory( arrow->res_file );
}

//==============================================================================
//	矢印　EOA
//==============================================================================
//--------------------------------------------------------------
/**
 * 自機出口矢印追加
 * @param	jiki	PLAYER_STATE_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void FE_PlayerExitArrow_Add( PLAYER_STATE_PTR jiki )
{
	int param = 0,pri;
	ARROW_ADD_H head;
	FE_SYS *fes;
	FIELD_OBJ_PTR fldobj;
	VecFx32 mtx = { 0, 0, 0 };
	
	fldobj = Player_FieldOBJGet( jiki );
	fes = FE_FieldOBJ_FE_SYS_Get( fldobj );
	
	head.fes = fes;
	head.arrow = FE_EffectWorkGet( fes, FE_FLD_ARROW );
	head.jiki = jiki;
	
	pri = FieldOBJ_TCBPriGet( fldobj, FLDOBJ_TCBPRI_OFFS_AFTER );
	FE_EoaAddNpp( fes, &DATA_EoaH_Arrow, &mtx, param, &head, pri );
}

//--------------------------------------------------------------
/**
 * EOA 矢印　初期化
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work *
 * @retval	int		TRUE=正常終了。FALSE=異常終了
 */
//--------------------------------------------------------------
static int EoaArrow_Init( EOA_PTR eoa, void *wk )
{
	ARROW_WORK *work;
	FIELD_OBJ_PTR fldobj;
	const ARROW_ADD_H *head;
	
	work = wk;
	head = EOA_AddPtrGet( eoa );
	work->head = *head;
	fldobj = Player_FieldOBJGet( head->jiki );
	
	work->dir = DIR_NOT;
	work->obj_id = FieldOBJ_OBJIDGet( fldobj );
	work->zone_id = FieldOBJ_ZoneIDGet( fldobj );
	
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * EOA 矢印　削除
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work *
 * @retval	nothing
 */
//--------------------------------------------------------------
static void EoaArrow_Delete( EOA_PTR eoa, void *wk )
{
}

//--------------------------------------------------------------
/**
 * EOA 矢印　動作
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work *
 * @retval	nothing
 */
//--------------------------------------------------------------
static void EoaArrow_Move( EOA_PTR eoa, void *wk )
{
	int old_dir;
	ARROW_WORK *work = wk;
	PLAYER_STATE_PTR jiki = work->head.jiki;
	FIELD_OBJ_PTR fldobj = Player_FieldOBJGet( jiki );
	
	if( FieldOBJ_CheckSameID(fldobj,work->obj_id,work->zone_id) == FALSE ){
		FE_EoaDelete( eoa );										//同一ではない
		return;
	}
	
	old_dir = work->dir;
	
	work->attr = FieldOBJ_NowMapAttrGet( fldobj );
	work->dir = Arrow_AttrDirGet( work->attr );
	work->vanish_sw = FALSE;
	
	if( work->dir == DIR_NOT || work->dir != Player_DirGet(jiki) ){
		work->frame = 0;
		work->draw_offs_no = 0;
		work->vanish_sw = TRUE;
		return;
	}
	
	if( old_dir != work->dir ){
		work->frame = 0;
		work->draw_offs_no = 0;
	}
	
	{
		VecFx32 h_vec,vec;
		int gx = FieldOBJ_NowPosGX_Get( fldobj ) + FieldOBJ_DirAddValueGX( work->dir );
		int gz = FieldOBJ_NowPosGZ_Get( fldobj ) + FieldOBJ_DirAddValueGZ( work->dir );
		FieldOBJTool_GridCenterPosGet( gx, gz, &vec );
		FieldOBJ_VecPosGet( fldobj, &h_vec );
		vec.y = h_vec.y;
		
		EOA_MatrixSet( eoa, &vec );
	}
}

//--------------------------------------------------------------
/**
 * EOA 矢印　描画
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work *
 * @retval	nothing
 */
//--------------------------------------------------------------
static void EoaArrow_Draw( EOA_PTR eoa, void *wk )
{
	ARROW_WORK *work;
	
	work = wk;
	
	if( work->vanish_sw == TRUE || work->dir == DIR_NOT ){
		return;
	}
	
	{
		work->frame++;
		
		if( work->frame > ARROW_OFFSET_FRAME ){
			work->frame = 0;
			work->draw_offs_no++;
			work->draw_offs_no %= ARROW_OFFSET_NUM_MAX;
		}
	}
	
	
	{
		VecFx32 vec;
		VecFx32 scale = { FX32_ONE, FX32_ONE, FX32_ONE };
		MtxFx33 rot	  = { FX32_ONE, 0,0,0, FX32_ONE, 0,0,0,FX32_ONE};
		const VecFx32 *offs = &DATA_ArrowDrawOffsTbl[work->dir][work->draw_offs_no];
		
		{
			switch( work->dir ){
			case DIR_UP:	Rot360_to_MtxFx33( &rot, 0, 180, 0 ); break;
			case DIR_DOWN:	Rot360_to_MtxFx33( &rot, 0, 0, 0 ); break;
			case DIR_LEFT:	Rot360_to_MtxFx33( &rot, 0, 270, 0 ); break;
			case DIR_RIGHT:	Rot360_to_MtxFx33( &rot, 0, 90, 0 ); break;
			}
		}
		
		EOA_MatrixGet( eoa, &vec );
		
		vec.x += 0 + offs->x;
		vec.y += 0 + offs->y;
		vec.z += 0 + offs->z;
		simple_3DModelDraw( &work->head.arrow->render, &vec, &rot, &scale );
	}
}

//==============================================================================
//	矢印アクターパーツ
//==============================================================================
//--------------------------------------------------------------
/**
 * アトリビュートから表示方向を取得
 * @param	attr	MATR
 * @retval	int		DIR_UP等 DIR_NOT=マットではない
 */
//--------------------------------------------------------------
static int Arrow_AttrDirGet( MATR attr )
{
	if( MATR_IsUpMat(attr) ){ return( DIR_UP ); }
	if( MATR_IsDownMat(attr) ){ return( DIR_DOWN ); }
	if( MATR_IsLeftMat(attr) ){ return( DIR_LEFT ); }
	if( MATR_IsRightMat(attr) ){ return( DIR_RIGHT ); }
	
	return( DIR_NOT );
}

//==============================================================================
//	data
//==============================================================================
//--------------------------------------------------------------
///	矢印EOA_H
//--------------------------------------------------------------
static const EOA_H_NPP DATA_EoaH_Arrow =
{
	ARROW_WORK_SIZE,
	EoaArrow_Init,
	EoaArrow_Delete,
	EoaArrow_Move,
	EoaArrow_Draw,
};

//--------------------------------------------------------------
///	方向別表示オフセット
//--------------------------------------------------------------
static const VecFx32 DATA_ArrowDrawOffsTbl[DIR_4_MAX][ARROW_OFFSET_NUM_MAX] =
{
	{					//DIR_UP
		{0,0,0},
		{0,0,-(FX32_ONE*2)},
	},
	{					//DIR_DOWN
		{0,0,0},
		{0,0,(FX32_ONE*2)},
	},
	{					//DIR_LEFT
		{0,0,0},
		{-(FX32_ONE*2),0,0},
	},
	{					//DIR_RIGHT
		{0,0,0},
		{(FX32_ONE*2),0,0},
	},
};

