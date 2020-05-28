//******************************************************************************
/**
 * 
 * @file	fldeff_rockride.c
 * @brief	フィールドOBJ　自機壁上りポケモン
 * @author	kagaya
 * @data	05.07.13
 *
 */
//******************************************************************************
#include "common.h"
#include "fieldsys.h"
#include "field_effect.h"
#include "fieldobj.h"
#include "fldeff_rockride.h"

//==============================================================================
//	define
//==============================================================================
//#define DEBUG_ROCKRIDE_WRITE_OFF	//定義で壁上りポケモン描画OFF

//#define ROCKRIDE_DRAW_Z_OFFSET (FX32_ONE*(3))
//#define ROCKRIDE_DRAW_Z_OFFSET (FX32_ONE*(5))			///<壁上りポケモン描画オフセットZ軸
//#define ROCKRIDE_DRAW_Z_OFFSET (FX32_ONE*(3))				

#define ROCKRIDE_RIDE_Y_OFFSET (FX32_ONE*8)				///<波ポケ乗りへの表示オフセットY
#define ROCKRIDE_RIDE_Z_OFFSET (FX32_ONE*4)				///<波ポケ乗りへの表示オフセットZ

#define ROCKRIDE_SHAKE_VALUE (0x0400)					///<初期揺れ幅
#define ROCKRIDE_SHAKE_MAX (FX32_ONE*4)

#define ROCKRIDE_ON_FRAME (30)
#define ROCKRIDE_OFF_FRAME (ROCKRIDE_ON_FRAME+30)

//==============================================================================
//	typedef struct
//==============================================================================
//--------------------------------------------------------------
///	FE_ROCKRIDE型
//--------------------------------------------------------------
typedef struct _TAG_FE_ROCKRIDE * FE_ROCKRIDE_PTR;

//--------------------------------------------------------------
///	FE_ROCKRIDE構造体
//--------------------------------------------------------------
typedef struct _TAG_FE_ROCKRIDE
{
	int add_count;
	int draw_init;
	int trans_set;
	TCB_PTR tcb_vintr_trans;
	FE_SYS *fes;
	NNSG3dRenderObj render;
	NNSG3dResMdl *model;
	NNSG3dResFileHeader *res_file;
}FE_ROCKRIDE;

#define FE_ROCKRIDE_SIZE (sizeof(FE_ROCKRIDE)) ///<FE_ROCKRIDEサイズ

//--------------------------------------------------------------
///	ROCKRIDE_ADD_H構造体
//--------------------------------------------------------------
typedef struct
{
	int init_dir;					///<表示方向
	FE_SYS *fes;					///<FE_SYS_PTR
	FIELDSYS_WORK *fsys;			///<FIELDSYS_WORK
	FE_ROCKRIDE_PTR rockride;		///<FE_ROCKRIDE_PTR
	FIELD_OBJ_PTR fldobj;			///<FIELD_OBJ_PTR
}ROCKRIDE_ADD_H;

#define ROCKRIDE_ADD_H_SIZE (sizeof(ROCKRIDE_ADD_H)) ///<ROCKRIDE_ADD_Hサイズ

//--------------------------------------------------------------
///	ROCKRIDE_WORK構造体
//--------------------------------------------------------------
typedef struct
{
	int vanish_sw;								///<非表示SW
	int dir;									///<方向
	int frame;									///<表示フレーム
	int joint;									///<接続フラグ
	ROCKRIDE_ADD_H head;						///<追加時のROCKRIDE_ADD_H
}ROCKRIDE_WORK;

#define ROCKRIDE_WORK_SIZE (sizeof(ROCKRIDE_WORK))	///<ROCKRIDE_WORKサイズ

//==============================================================================
//	プロトタイプ
//==============================================================================
static void RockRide_AddCountUp( FE_ROCKRIDE_PTR rockride );
static void RockRide_AddCountDown( FE_ROCKRIDE_PTR rockride );

static void RockRide_GraphicInit( FE_ROCKRIDE_PTR rockride );
static void RockRide_GraphicDelete( FE_ROCKRIDE_PTR rockride );
static void RockRide_GraphicCheckInit( FE_ROCKRIDE_PTR rockride );
static void RockRide_GraphicCheckDelete( FE_ROCKRIDE_PTR rockride );
static void RockRide_VIntrTCBTrans( TCB_PTR tcb, void *wk );

static const EOA_H_NPP DATA_EoaH_RockRide;

//==============================================================================
//	壁上りポケモン　システム
//==============================================================================
//--------------------------------------------------------------
/**
 * 壁上りポケモン初期化
 * @param	fes		FE_SYS_PTR
 * @retval	FE_ROCKRIDE_PTR	FE_ROCKRIDE_PTR
 */
//--------------------------------------------------------------
void * FE_RockRide_Init( FE_SYS *fes )
{
	FE_ROCKRIDE_PTR rockride;
	
	rockride = FE_AllocClearMemory( fes, FE_ROCKRIDE_SIZE, ALLOC_FR, 0 );
	rockride->fes = fes;
	
	return( rockride );
}

//--------------------------------------------------------------
/**
 * 壁上りポケモン削除
 * @param	rockride		FE_ROCKRIDE_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void FE_RockRide_Delete( void *work )
{
	FE_ROCKRIDE_PTR rockride = work;
	RockRide_GraphicDelete( rockride );
	FE_FreeMemory( rockride );
}

//==============================================================================
//	壁上りポケモン	パーツ
//==============================================================================
//--------------------------------------------------------------
/**
 * 壁上り数カウント
 * @param	rockride	FE_ROCKRIDE_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void RockRide_AddCountUp( FE_ROCKRIDE_PTR rockride )
{
	rockride->add_count++;
}

//--------------------------------------------------------------
/**
 * 壁上り数デクリメント
 * @param	rockride	FE_ROCKRIDE_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void RockRide_AddCountDown( FE_ROCKRIDE_PTR rockride )
{
	rockride->add_count--;
	
	GF_ASSERT( rockride->add_count >= 0 &&
		"RockRide_AddCountDown()　壁上りの追加と削除の回数が合わない" );
}

//==============================================================================
//	壁上りポケモン　グラフィック
//==============================================================================
//--------------------------------------------------------------
/**
 * 壁上りポケモン グラフィック初期化
 * @param	rockride	FE_ROCKRIDE_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void RockRide_GraphicInit( FE_ROCKRIDE_PTR rockride )
{
	if( rockride->draw_init == FALSE ){
		rockride->res_file = FE_ArcDataLoadAlloc(
			rockride->fes, NARC_fldeff_rock_ride_nsbmd, ALLOC_LO );
		rockride->tcb_vintr_trans = VIntrTCB_Add( RockRide_VIntrTCBTrans, rockride, 0x80 );
		rockride->draw_init = TRUE;
	}
}

//--------------------------------------------------------------
/**
 * 壁上りポケモン グラフィック削除
 * @param	rockride	FE_ROCKRIDE_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void RockRide_GraphicDelete( FE_ROCKRIDE_PTR rockride )
{
	if( rockride->tcb_vintr_trans != NULL ){
		TCB_Delete( rockride->tcb_vintr_trans );
		rockride->tcb_vintr_trans = NULL;
		rockride->trans_set = FALSE;
	}
	
	if( rockride->draw_init == TRUE ){
		rockride->draw_init = FALSE;
		FE_FreeMemory( rockride->res_file );
	}
}

//--------------------------------------------------------------
/**
 * 判定つきグラフィック初期化
 * @param	rockride	FE_ROCKRIDE_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void RockRide_GraphicCheckInit( FE_ROCKRIDE_PTR rockride )
{
	if( rockride->add_count == 0 ){
		RockRide_GraphicInit( rockride );
	}
}

//--------------------------------------------------------------
/**
 * 判定つきグラフィック削除
 * @param	rockride	FE_ROCKRIDE_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void RockRide_GraphicCheckDelete( FE_ROCKRIDE_PTR rockride )
{
	if( rockride->add_count == 0 ){
		RockRide_GraphicDelete( rockride );
	}
}

//--------------------------------------------------------------
/**
 * VIntrTcb グラフィック初期化
 * @param	tcb		TCB_PTR
 * @param	wk		tcb work *
 * @retval	nothing
 */
//--------------------------------------------------------------
static void RockRide_VIntrTCBTrans( TCB_PTR tcb, void *wk )
{
	FE_ROCKRIDE_PTR rockride = wk;
	
	FE_simple3DModelInitOnly( rockride->fes,
		&rockride->render, &rockride->model, &rockride->res_file );
	
	rockride->tcb_vintr_trans = NULL;
	rockride->trans_set = TRUE;
	TCB_Delete( tcb );
}

//==============================================================================
//	壁上りポケモン　EOA
//==============================================================================
//--------------------------------------------------------------
/**
 * EOA 壁上りポケモン追加
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	gx		表示グリッドX
 * @param	gz		表示グリッドZ
 * @param	dir		表示方向
 * @param	joint	TRUE=fldobjの座標に接続 FALSE=しない
 * @retval	EOA_PTR	追加されたポケモンEOA_PTR
 */
//--------------------------------------------------------------
EOA_PTR FE_FldOBJRockRidePoke_Add( FIELD_OBJ_PTR fldobj, int gx, int gz, int dir, int joint )
{
	int pri;
	EOA_PTR eoa;
	ROCKRIDE_ADD_H head;
	VecFx32 mtx = {0,0,0};
	FE_SYS *fes = FE_FieldOBJ_FE_SYS_Get( fldobj );
	
	head.init_dir = dir;
	head.fes = fes;
	head.fsys = FieldOBJ_FieldSysWorkGet( fldobj );
	head.rockride = FE_EffectWorkGet( fes, FE_FLD_ROCKRIDE );
	head.fldobj = fldobj;
		
	if( joint == FALSE ){
		mtx.x = GRID_SIZE_FX32( gx ) + FLDOBJ_VEC_X_GRID_OFFS_FX32;
		mtx.z = GRID_SIZE_FX32( gz ) + FLDOBJ_VEC_Z_GRID_OFFS_FX32;
		FieldOBJTool_GetHeight( head.fsys, &mtx );
	}else{
		FieldOBJ_VecPosGet( fldobj, &mtx );
	}
	
	pri = FieldOBJ_TCBPriGet( fldobj, FLDOBJ_TCBPRI_OFFS_AFTER );
	eoa = FE_EoaAddNpp( fes, &DATA_EoaH_RockRide, &mtx, joint, &head, pri );
	
	return( eoa );
}

//--------------------------------------------------------------
/**
 * 壁上りポケモンの接続フラグセット
 * @param	eoa		EOA_PTR
 * @param	joint	TRUE=接続 FALSE=非接続
 * @retval	nothing
 */
//--------------------------------------------------------------
void FE_FldOBJRockRidePokeJointFlagSet( EOA_PTR eoa, int joint )
{
	ROCKRIDE_WORK *work = EOA_LocalWorkGet( eoa );
	work->joint = joint;
}

//--------------------------------------------------------------
/**
 * EOA 壁上りポケモン　初期化
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work *
 * @retval	int		TRUE=正常終了。FALSE=異常終了
 */
//--------------------------------------------------------------
static int EoaRockRide_Init( EOA_PTR eoa, void *wk )
{
	ROCKRIDE_WORK *work = wk;
	const ROCKRIDE_ADD_H *head = EOA_AddPtrGet( eoa );
	
	work->head = *head;
	work->dir = head->init_dir;
	work->joint = EOA_AddParamGet( eoa );
	
	RockRide_GraphicCheckInit( work->head.rockride );
	RockRide_AddCountUp( work->head.rockride );
	
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * EOA 壁上りポケモン　削除
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work *
 * @retval	nothing
 */
//--------------------------------------------------------------
static void EoaRockRide_Delete( EOA_PTR eoa, void *wk )
{
	ROCKRIDE_WORK *work = wk;
	
	RockRide_AddCountDown( work->head.rockride );
	RockRide_GraphicCheckDelete( work->head.rockride );
}

//--------------------------------------------------------------
/**
 * EOA 壁上りポケモン　動作
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work *
 * @retval	nothing
 */
//--------------------------------------------------------------
static void EoaRockRide_Move( EOA_PTR eoa, void *wk )
{
	ROCKRIDE_WORK *work = wk;
	FIELD_OBJ_PTR fldobj = work->head.fldobj;
	
	if( work->joint == FALSE ){
		return;
	}
	
	{
		VecFx32 offs = { 0, 0, 0 };
		FieldOBJ_VecDrawOffsOutSideSet( fldobj, &offs );
	}
	
	{
		VecFx32 vec;
		FieldOBJ_VecPosGet( fldobj, &vec );
		vec.y += 0;
		EOA_MatrixSet( eoa, &vec );
	}
}

//--------------------------------------------------------------
/**
 * EOA 壁上りポケモン　描画
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work *
 * @retval	nothing
 */
//--------------------------------------------------------------
static void EoaRockRide_Draw( EOA_PTR eoa, void *wk )
{
	ROCKRIDE_WORK *work;
	
	work = wk;
	
	if( work->vanish_sw == TRUE || work->head.rockride->trans_set == FALSE ){
		return;
	}
	
	{
		work->frame++;
	}
	
	{
		VecFx32 vec;
		VecFx32 scale = { FX32_ONE, FX32_ONE, FX32_ONE };
		MtxFx33 rot	  = { FX32_ONE, 0,0,0, FX32_ONE, 0,0,0,FX32_ONE};
		
		switch( work->dir ){
		case DIR_UP:	Rot360_to_MtxFx33( &rot, 0, 180, 0 ); break;
		case DIR_DOWN:	Rot360_to_MtxFx33( &rot, 0, 0, 0 ); break;
		case DIR_LEFT:	Rot360_to_MtxFx33( &rot, 0, 270, 0 ); break;
		case DIR_RIGHT:	Rot360_to_MtxFx33( &rot, 0, 90, 0 ); break;
		}
		
		EOA_MatrixGet( eoa, &vec );
		simple_3DModelDraw( &work->head.rockride->render, &vec, &rot, &scale );
	}
}

//==============================================================================
//	data
//==============================================================================
//--------------------------------------------------------------
///	壁上りポケモンEOA_H
//--------------------------------------------------------------
static const EOA_H_NPP DATA_EoaH_RockRide =
{
	ROCKRIDE_WORK_SIZE,
	EoaRockRide_Init,
	EoaRockRide_Delete,
	EoaRockRide_Move,
	EoaRockRide_Draw,
};


//==============================================================================
//	debug
//==============================================================================
#ifdef DEBUG_ROCKRIDE_ROT
void DEBUG_RockRide_Rot( EOA_PTR eoa, int x, int y, int z )
{
	ROCKRIDE_WORK *work = EOA_LocalWorkGet( eoa );
	work->rot_x += x;
	if( work->rot_x >= 360 ){ work->rot_x = 0; }
	if( work->rot_x < 0 ){ work->rot_x = 360 - work->rot_x; }
	work->rot_y += y;
	if( work->rot_y >= 360 ){ work->rot_y = 0; }
	if( work->rot_y < 0 ){ work->rot_y = 360 - work->rot_y; }
	work->rot_z += z;
	if( work->rot_z >= 360 ){ work->rot_z = 0; }
	if( work->rot_z < 0 ){ work->rot_z = 360 - work->rot_z; }
}
#endif
