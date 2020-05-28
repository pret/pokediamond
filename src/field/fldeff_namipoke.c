//******************************************************************************
/**
 * 
 * @file	fldeff_namipoke.c
 * @brief	フィールドOBJ　自機波乗りポケモン
 * @author	kagaya
 * @data	05.07.13
 *
 */
//******************************************************************************
#include "common.h"
#include "fieldsys.h"
#include "field_effect.h"
#include "fieldobj.h"
#include "fldeff_namipoke.h"

//==============================================================================
//	define
//==============================================================================
//#define DEBUG_NAMIPOKE_WRITE_OFF	//定義で波乗りポケモン描画OFF

//#define NAMIPOKE_DRAW_Z_OFFSET (FX32_ONE*(3))
//#define NAMIPOKE_DRAW_Z_OFFSET (FX32_ONE*(5))			///<波乗りポケモン描画オフセットZ軸
//#define NAMIPOKE_DRAW_Z_OFFSET (FX32_ONE*(3))				

#define NAMIPOKE_RIDE_Y_OFFSET (FX32_ONE*7)				///<波ポケ乗りへの表示オフセットY
#define NAMIPOKE_RIDE_Z_OFFSET (FX32_ONE*4)				///<波ポケ乗りへの表示オフセットZ

#define NAMIPOKE_SHAKE_VALUE (0x0400)					///<初期揺れ幅
#define NAMIPOKE_SHAKE_MAX (FX32_ONE*4)

#define NAMIPOKE_ON_FRAME (30)
#define NAMIPOKE_OFF_FRAME (NAMIPOKE_ON_FRAME+30)

//==============================================================================
//	typedef struct
//==============================================================================
//--------------------------------------------------------------
///	FE_NAMIPOKE型
//--------------------------------------------------------------
typedef struct _TAG_FE_NAMIPOKE * FE_NAMIPOKE_PTR;

//--------------------------------------------------------------
///	FE_NAMIPOKE構造体
//--------------------------------------------------------------
typedef struct _TAG_FE_NAMIPOKE
{
	FE_SYS *fes;
	NNSG3dRenderObj render;
	NNSG3dResMdl *model;
	NNSG3dResFileHeader *res_file;
}FE_NAMIPOKE;

#define FE_NAMIPOKE_SIZE (sizeof(FE_NAMIPOKE)) ///<FE_NAMIPOKEサイズ

//--------------------------------------------------------------
///	NAMIPOKE_ADD_H構造体
//--------------------------------------------------------------
typedef struct
{
	int init_dir;					///<表示方向
	FE_SYS *fes;					///<FE_SYS_PTR
	FE_NAMIPOKE_PTR namipoke;		///<FE_NAMIPOKE_PTR
	FIELD_OBJ_PTR fldobj;			///<FIELD_OBJ_PTR
}NAMIPOKE_ADD_H;

#define NAMIPOKE_ADD_H_SIZE (sizeof(NAMIPOKE_ADD_H)) ///<NAMIPOKE_ADD_Hサイズ

//--------------------------------------------------------------
///	NAMIPOKE_WORK構造体
//--------------------------------------------------------------
typedef struct
{
	int vanish_sw;								///<非表示SW
	int dir;									///<方向
	int draw_dir;								///<描画方向
	int obj_id;									///<OBJ ID
	int zone_id;								///<ZONE ID
	int frame;									///<表示フレーム
	int joint;									///<接続フラグ
	fx32 shake_offs;							///<揺れ
	fx32 shake_value;							///<揺れ量
#ifdef DEBUG_NAMIPOKE_ROT
	int rot_x;
	int rot_y;
	int rot_z;
#endif
	NAMIPOKE_ADD_H head;						///<追加時のNAMIPOKE_ADD_H
}NAMIPOKE_WORK;

#define NAMIPOKE_WORK_SIZE (sizeof(NAMIPOKE_WORK))	///<NAMIPOKE_WORKサイズ

//==============================================================================
//	プロトタイプ
//==============================================================================
static void NamiPoke_GraphicInit( FE_NAMIPOKE_PTR namipoke );
static void NamiPoke_GraphicDelete( FE_NAMIPOKE_PTR namipoke );

static const EOA_H_NPP DATA_EoaH_NamiPoke;

//==============================================================================
//	波乗りポケモン　システム
//==============================================================================
//--------------------------------------------------------------
/**
 * 波乗りポケモン初期化
 * @param	fes		FE_SYS_PTR
 * @retval	FE_NAMIPOKE_PTR	FE_NAMIPOKE_PTR
 */
//--------------------------------------------------------------
void * FE_NamiPoke_Init( FE_SYS *fes )
{
	FE_NAMIPOKE_PTR namipoke;
	
	namipoke = FE_AllocClearMemory( fes, FE_NAMIPOKE_SIZE, ALLOC_FR, 0 );
	namipoke->fes = fes;
	
	NamiPoke_GraphicInit( namipoke );
	return( namipoke );
}

//--------------------------------------------------------------
/**
 * 波乗りポケモン削除
 * @param	namipoke		FE_NAMIPOKE_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void FE_NamiPoke_Delete( void *work )
{
	FE_NAMIPOKE_PTR namipoke = work;
	NamiPoke_GraphicDelete( namipoke );
	FE_FreeMemory( namipoke );
}

//==============================================================================
//	波乗りポケモン	パーツ
//==============================================================================

//==============================================================================
//	波乗りポケモン　グラフィック
//==============================================================================
//--------------------------------------------------------------
/**
 * 波乗りポケモン グラフィック初期化
 * @param	namipoke	FE_NAMIPOKE_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void NamiPoke_GraphicInit( FE_NAMIPOKE_PTR namipoke )
{
	FE_simple3DModelInit( namipoke->fes, NARC_fldeff_sea_ride_nsbmd, ALLOC_FR,
			&namipoke->render, &namipoke->model, &namipoke->res_file );
}

//--------------------------------------------------------------
/**
 * 波乗りポケモン グラフィック削除
 * @param	namipoke	FE_NAMIPOKE_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void NamiPoke_GraphicDelete( FE_NAMIPOKE_PTR namipoke )
{
	FE_FreeMemory( namipoke->res_file );
}

//==============================================================================
//	波乗りポケモン　EOA
//==============================================================================
//--------------------------------------------------------------
/**
 * 波乗りポケモン追加
 * @param	fldobj	対象となるFIELD_OBJ_PTR
 * @param	gx		表示するグリッドX座標
 * @param	gz		表示するグリッドZ座標
 * @param	dir		表示する方向
 * @param	joint	TRUE=fldobj座標に接続　FALSE=接続しない
 * @retval	EOA_PTR	波乗りポケモンEOA_PTR
 */
//--------------------------------------------------------------
EOA_PTR FE_FldOBJNamiPokeSet( FIELD_OBJ_PTR fldobj, int gx, int gz, int dir, int joint )
{
	NAMIPOKE_ADD_H head;
	VecFx32 mtx = { 0, 0, 0 };
	
	head.init_dir = dir;
	head.fes = FE_FieldOBJ_FE_SYS_Get( fldobj );
	head.namipoke = FE_EffectWorkGet( head.fes, FE_FLD_NAMIPOKE );
	head.fldobj = fldobj;
	
	if( joint == FALSE ){
		FIELDSYS_WORK *fsys = FieldOBJ_FieldSysWorkGet( fldobj );
		mtx.x = GRID_SIZE_FX32( gx ) + FLDOBJ_VEC_X_GRID_OFFS_FX32;
		mtx.z = GRID_SIZE_FX32( gz ) + FLDOBJ_VEC_Z_GRID_OFFS_FX32;
		FieldOBJTool_GetHeight( fsys, &mtx );
	}else{
		VecFx32 offs = { 0, NAMIPOKE_RIDE_Y_OFFSET, NAMIPOKE_RIDE_Z_OFFSET };
		FieldOBJ_VecPosGet( fldobj, &mtx );
		FieldOBJ_VecDrawOffsOutSideSet( fldobj, &offs );
	}
	
	{
		int pri = FieldOBJ_TCBPriGet( fldobj, FLDOBJ_TCBPRI_OFFS_AFTER );
		return( FE_EoaAddNpp(head.fes,&DATA_EoaH_NamiPoke,&mtx,joint,&head,pri) );
	}
}

//--------------------------------------------------------------
/**
 * EOA 波乗りポケモン　初期化
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work *
 * @retval	int		TRUE=正常終了。FALSE=異常終了
 */
//--------------------------------------------------------------
static int EoaNamiPoke_Init( EOA_PTR eoa, void *wk )
{
	NAMIPOKE_WORK *work = wk;
	const NAMIPOKE_ADD_H *head = EOA_AddPtrGet( eoa );
	FIELD_OBJ_PTR fldobj = head->fldobj;
	
	work->head = *head;
	work->obj_id = FieldOBJ_OBJIDGet( fldobj );
	work->zone_id = FieldOBJ_ZoneIDGet( fldobj );
	work->draw_dir = head->init_dir;
	work->joint = EOA_AddParamGet( eoa );
	work->shake_offs = FX32_ONE;
	work->shake_value = NAMIPOKE_SHAKE_VALUE;
	
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * EOA 波乗りポケモン　削除
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work *
 * @retval	nothing
 */
//--------------------------------------------------------------
static void EoaNamiPoke_Delete( EOA_PTR eoa, void *wk )
{
	NAMIPOKE_WORK *work = wk;
	FIELD_OBJ_PTR fldobj = work->head.fldobj;
	VecFx32 offs = { 0, 0, 0 };
	FieldOBJ_VecDrawOffsOutSideSet( fldobj, &offs );
}

//--------------------------------------------------------------
/**
 * EOA 波乗りポケモン　動作
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work *
 * @retval	nothing
 */
//--------------------------------------------------------------
static void EoaNamiPoke_Move( EOA_PTR eoa, void *wk )
{
	NAMIPOKE_WORK *work = wk;
	FIELD_OBJ_PTR fldobj = work->head.fldobj;
	
	if( FieldOBJ_CheckSameID(fldobj,work->obj_id,work->zone_id) == FALSE ){
		FE_EoaDelete( eoa );									//同一ではない
		return;
	}
	
	work->vanish_sw = FALSE;
	work->dir = FieldOBJ_DirDispGet( fldobj );
	
	if( work->dir == DIR_NOT ){								//方向が取れない
		work->vanish_sw = TRUE;
		return;
	}
	
	if( work->joint == FALSE ){								//接続しない
		return;
	}
	
	work->draw_dir = work->dir;
	
	{
		work->shake_offs += work->shake_value;
		
		if( work->shake_offs >= NAMIPOKE_SHAKE_MAX ){
			work->shake_offs = NAMIPOKE_SHAKE_MAX;
			work->shake_value = -work->shake_value;
		}else if( work->shake_offs <= FX32_ONE ){
			work->shake_offs = FX32_ONE;
			work->shake_value = -work->shake_value;
		}
	}
	
	{
		VecFx32 offs;
		offs.x = 0;
		offs.y = work->shake_offs + NAMIPOKE_RIDE_Y_OFFSET;
		offs.z = NAMIPOKE_RIDE_Z_OFFSET;
		FieldOBJ_VecDrawOffsOutSideSet( fldobj, &offs );
	}
	
	{
		VecFx32 vec;
		FieldOBJ_VecPosGet( fldobj, &vec );
		vec.y += work->shake_offs - FX32_ONE;
		EOA_MatrixSet( eoa, &vec );
	}
}

//--------------------------------------------------------------
/**
 * EOA 波乗りポケモン　描画
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work *
 * @retval	nothing
 */
//--------------------------------------------------------------
static void EoaNamiPoke_Draw( EOA_PTR eoa, void *wk )
{
	NAMIPOKE_WORK *work;
	
	work = wk;
	
	if( work->vanish_sw == TRUE || work->draw_dir == DIR_NOT ){
		return;
	}
	
	{
		work->frame++;
	}
	
	{
		VecFx32 vec;
		VecFx32 scale = { FX32_ONE, FX32_ONE, FX32_ONE };
		MtxFx33 rot	  = { FX32_ONE, 0,0,0, FX32_ONE, 0,0,0,FX32_ONE};
		
		switch( work->draw_dir ){
		case DIR_UP:	Rot360_to_MtxFx33( &rot, 0, 180, 0 ); break;
		case DIR_DOWN:	Rot360_to_MtxFx33( &rot, 0, 0, 0 ); break;
		case DIR_LEFT:	Rot360_to_MtxFx33( &rot, 0, 270, 0 ); break;
		case DIR_RIGHT:	Rot360_to_MtxFx33( &rot, 0, 90, 0 ); break;
		}
		
		EOA_MatrixGet( eoa, &vec );
		simple_3DModelDraw( &work->head.namipoke->render, &vec, &rot, &scale );
	}
}

#ifdef DEBUG_NAMIPOKE_ROT 
static void EoaNamiPoke_Draw( EOA_PTR eoa, void *wk )
{
	NAMIPOKE_WORK *work;
	
	work = wk;
	
	if( work->vanish_sw == TRUE || work->dir == DIR_NOT ){
		return;
	}
	
	{
		work->frame++;
	}
	
	{
		VecFx32 vec;
		VecFx32 scale = { FX32_ONE, FX32_ONE, FX32_ONE };
		MtxFx33 rot	  = { FX32_ONE, 0,0,0, FX32_ONE, 0,0,0,FX32_ONE};
		
		{
			if( work->dir != work->draw_dir ){
				work->draw_dir = work->dir;
				OS_Printf( "なみぽけ　表示方向が更新されました %d\n", work->dir );
			}
		}
		
		{
			OS_Printf("なみぽけ回転角度 X=%d,Y=%d,Z=%d\n",work->rot_x,work->rot_y,work->rot_z);
			Rot360_to_MtxFx33( &rot, work->rot_x, work->rot_y, work->rot_z );
		}
		
		EOA_MatrixGet( eoa, &vec );
		
		vec.x += 0;
		vec.y += 0;
		vec.z += 0;
		simple_3DModelDraw( &work->head.namipoke->render, &vec, &rot, &scale );
	}
}
#endif

//==============================================================================
//	波乗りポケモンアクターパーツ
//==============================================================================
//--------------------------------------------------------------
/**
 * 接続フラグON OFF
 * @param	eoa		波乗りポケモンEOA_PTR
 * @param	flag	TRUE=接続 FALSE=未接続
 * @retval	nothing
 */
//--------------------------------------------------------------
void FE_FldOBJNamiPokeJointFlagSet( EOA_PTR eoa, int flag )
{
	NAMIPOKE_WORK *work = EOA_LocalWorkGet( eoa );
	work->joint = flag;
	
	work->shake_offs = FX32_ONE;
	work->shake_value = NAMIPOKE_SHAKE_VALUE;
}

//==============================================================================
//	data
//==============================================================================
//--------------------------------------------------------------
///	波乗りポケモンEOA_H
//--------------------------------------------------------------
static const EOA_H_NPP DATA_EoaH_NamiPoke =
{
	NAMIPOKE_WORK_SIZE,
	EoaNamiPoke_Init,
	EoaNamiPoke_Delete,
	EoaNamiPoke_Move,
	EoaNamiPoke_Draw,
};


//==============================================================================
//	debug
//==============================================================================
#ifdef DEBUG_NAMIPOKE_ROT
void DEBUG_NamiPoke_Rot( EOA_PTR eoa, int x, int y, int z )
{
	NAMIPOKE_WORK *work = EOA_LocalWorkGet( eoa );
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
