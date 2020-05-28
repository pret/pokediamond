//******************************************************************************
/**
 *
 * @file	fldeff_elight.c
 * @brief	フィールドOBJ　電灯　懐中電灯 electric light
 * @author	kagaya
 * @data	05.07.13
 *
 */
//******************************************************************************
#include "common.h"
#include "fieldsys.h"
#include "field_effect.h"
#include "fieldobj.h"

#include "fldeff_elight.h"

//==============================================================================
//	define
//==============================================================================
//--------------------------------------------------------------
///	光の長さ
//--------------------------------------------------------------
enum
{
	EL_LEN_0 = 0,											//長さ0
	EL_LEN_1,												//長さ1
	EL_LEN_2,												//長さ2
	EL_LEN_3,												//長さ3
	EL_LEN_MAX,												//長さ最大
	
	EL_LEN_SIZE_MAX = EL_LEN_3,
};

//--------------------------------------------------------------
///	光種類
//--------------------------------------------------------------
enum
{
	EL_TYPE_D_0,											///<電灯足元
	EL_TYPE_U_1,											///<電灯 1　上
	EL_TYPE_U_2,											///<電灯 2　上
	EL_TYPE_U_3,											///<電灯 3　上
	EL_TYPE_D_1,											///<電灯 1　下
	EL_TYPE_D_2,											///<電灯 2　下
	EL_TYPE_D_3,											///<電灯 3　下
	EL_TYPE_L_1,											///<電灯 1　左
	EL_TYPE_L_2,											///<電灯 2　左
	EL_TYPE_L_3,											///<電灯 3　左
	EL_TYPE_R_1,											///<電灯 1　左
	EL_TYPE_R_2,											///<電灯 2　左
	EL_TYPE_R_3,											///<電灯 3　左
	EL_MDL_MAX,												///<電灯最大数
};

//==============================================================================
//	typedef struct
//==============================================================================
//--------------------------------------------------------------
///	FE_ELLIGHT構造体
//--------------------------------------------------------------
typedef struct _TAG_FE_ELIGHT
{
	int heap_id;
	FE_SYS_PTR fes;
	NNSG3dRenderObj render[EL_MDL_MAX];
	NNSG3dResMdl *model[EL_MDL_MAX];
	NNSG3dResFileHeader *res_file[EL_MDL_MAX];
}FE_ELIGHT;

#define FE_ELIGHT_SIZE (sizeof(FE_ELIGHT))

//--------------------------------------------------------------
///	ELIGHT_ADD_H構造体
//--------------------------------------------------------------
typedef struct
{
	FIELDSYS_WORK *fsys;
	FE_SYS_PTR fes;
	FE_ELIGHT_PTR el;
	FIELD_OBJ_PTR fldobj;
}ELIGHT_ADD_H;

#define ELIGHT_ADD_H_SIZE (sizeof(ELIGHT_ADD_H))

//--------------------------------------------------------------
///	ELIGHT_WORK構造体
//--------------------------------------------------------------
typedef struct
{
	int dir;
	int len;
	int seq_no;
	int obj_id;
	int zone_id;
	int vanish_sw;
	ELIGHT_ADD_H head;
	NNSG3dRenderObj draw_render;
}EL_WORK;

#define EL_WORK_SIZE (sizeof(EL_WORK))

//==============================================================================
//	プロトタイプ
//==============================================================================
static FE_ELIGHT_PTR ELight_AllocMemory( int heap_id );
static void ELight_FreeMemory( FE_ELIGHT_PTR el );

static void ELight_GraphicInit( FE_ELIGHT_PTR el );
static void ELight_GraphicDelete( FE_ELIGHT_PTR el );

static int ELight_LengthCheck( EL_WORK *work, int x, int z, int dir );
static int ELight_DirLenTypeGet( int dir, int len );
static BLACT_WORK_PTR ELight_BlActAdd( FE_ELIGHT_PTR el, int dir, int len );

static const char * const DATA_3DModelFile_ELight[EL_MDL_MAX];
static const EOA_H_NPP DATA_EoaH_ELight;

//==============================================================================
//	電灯　システム
//==============================================================================
//--------------------------------------------------------------
/**
 * 電灯初期化
 * @param	fes		FE_SYS_PTR
 * @param	heap_id	ヒープID
 * @retval	FE_GRASS_PTR	FE_GRASS_PTR
 */
//--------------------------------------------------------------
FE_ELIGHT_PTR FE_ELight_Init( FE_SYS_PTR fes, int heap_id )
{
	FE_ELIGHT_PTR el;
	
	el = ELight_AllocMemory( heap_id );
	el->heap_id = heap_id;
	el->fes = fes;
	
	ELight_GraphicInit( el );
	
	return( el );
}

//--------------------------------------------------------------
/**
 * 電灯削除
 * @param	el		FE_ELIGHT_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void FE_ELight_Delete( FE_ELIGHT_PTR el )
{
	FE_SYS_PTR fes;
	
	fes = el->fes;
	
	ELight_GraphicDelete( el );
	ELight_FreeMemory( el );
}

//--------------------------------------------------------------
/**
 * 電灯メモリ確保
 * @param	heap_id		ヒープID
 * @retval	FE_ELIGHT_PTR	確保したFE_ELIGHT_PTR
 */
//--------------------------------------------------------------
static FE_ELIGHT_PTR ELight_AllocMemory( int heap_id )
{
	FE_ELIGHT_PTR el;
	
	el = sys_AllocMemory( heap_id, FE_ELIGHT_SIZE );
	GF_ASSERT( el != NULL && "ELight_AllocMemory()メモリ確保失敗" );
	
	return( el );
}

//--------------------------------------------------------------
/**
 * 電灯メモリ開放
 * @param	kusa	FE_GRASS_PTR
 * @retval	FE_GRASS_PTR	確保したFE_GRASS_PTR
 */
//--------------------------------------------------------------
static void ELight_FreeMemory( FE_ELIGHT_PTR el )
{
	sys_FreeMemory( el->heap_id, el );
}

//==============================================================================
//	電灯　グラフィック
//==============================================================================
//--------------------------------------------------------------
/**
 * 電灯　グラフィック初期化
 * @param	kusa	FE_GRASS_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void ELight_GraphicInit( FE_ELIGHT_PTR el )
{
	int i;
	const char *file_path;
	
	for( i = 0; i < EL_MDL_MAX; i++ ){
		file_path = DATA_3DModelFile_ELight[i];
//		NNS_G3dRenderObjInit( &el->render[i], el->model[i] );
		simple_3DModelSet( el->heap_id, file_path,
				&el->render[i], &el->model[i], &el->res_file[i] );
	}
}

//--------------------------------------------------------------
/**
 * 電灯　グラフィック初期化
 * @param	kusa	FE_GRASS_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void ELight_GraphicDelete( FE_ELIGHT_PTR el )
{
	int i;
	
	for( i = 0; i < EL_MDL_MAX; i++ ){
		sys_FreeMemory( el->heap_id, el->res_file[i] );
	}
}

//==============================================================================
//	電灯　EOA
//==============================================================================
//--------------------------------------------------------------
/**
 * フィールドOBJ電灯追加
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	eoa		EOA_PTR
 */
//--------------------------------------------------------------
EOA_PTR FE_FldOBJELight_Add( FIELD_OBJ_PTR fldobj )
{
	EOA_PTR eoa;
	ELIGHT_ADD_H head;
	
	head.fsys = FieldOBJ_FieldSysWorkGet( fldobj );
	head.fes = FE_FieldOBJ_FE_SYS_PTR_Get( fldobj );
	head.el = FE_ELightPtrGet( head.fes );
	head.fldobj = fldobj;
	
	{
		VecFx32 mtx = { 0, 0, 0 };
		int pri = FE_FldOBJ_TCBPriGet( fldobj, 1 );
		eoa = FE_EoaAddNpp( head.fes, &DATA_EoaH_ELight, &mtx, 0, &head, pri );
	}
	
	return( eoa );
}

//--------------------------------------------------------------
/**
 * EOA 電灯　初期化
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work *
 * @retval	int		TRUE=正常終了。FALSE=異常終了
 */
//--------------------------------------------------------------
static int EoaELight_Init( EOA_PTR eoa, void *wk )
{
	EL_WORK *work;
	const ELIGHT_ADD_H *head;
	
	work = wk;
	head = EOA_AddPtrGet( eoa );
	work->head = *head;
	
	work->dir = DIR_NOT;
	work->len = EL_LEN_MAX;
	work->obj_id = FieldOBJ_OBJIDGet( work->head.fldobj );
	work->zone_id = FieldOBJ_ZoneIDGet( work->head.fldobj );
	work->vanish_sw = TRUE;
	
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * EOA 電灯　削除
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work *
 * @retval	nothing
 */
//--------------------------------------------------------------
static void EoaELight_Delete( EOA_PTR eoa, void *wk )
{
}

//--------------------------------------------------------------
/**
 * EOA 電灯　動作
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work *
 * @retval	nothing
 */
//--------------------------------------------------------------
static void EoaELight_Move( EOA_PTR eoa, void *wk )
{
	int add,dir,len,x,z;
	EL_WORK *work;
	FIELD_OBJ_PTR fldobj;
	
	work = wk;
	fldobj = work->head.fldobj;
	
	if( FE_FldOBJ_CheckSameID(fldobj,work->obj_id,work->zone_id) == FALSE ){
		EOA_Delete( eoa );
		return;
	}
		
	add = FALSE;
	dir = FieldOBJ_DirDispGet( fldobj );
	x = FieldOBJ_NowPosGX_Get( fldobj );
	z = FieldOBJ_NowPosGZ_Get( fldobj );
	
	len = ELight_LengthCheck( work, x, z, dir );
	
	work->dir = dir;
	work->len = len;
	work->vanish_sw = FALSE;
	
	if( work->dir == DIR_NOT || work->len >= EL_LEN_MAX ){
		work->vanish_sw = TRUE;
		return;
	}
	
#if 0	
	len = 0;
	
	if( work->len != 0 ){
		len = (work->dir*3) + (work->len - 1) + 1;
	}
#else
	len = ELight_DirLenTypeGet( work->dir, work->len );
#endif
	
	work->draw_render = work->head.el->render[len];
	
	{
		VecFx32 vec;
		FieldOBJ_VecPosGet( fldobj, &vec );
		
		vec.y += -(FX32_ONE * 1);
		
		switch( work->dir ){
		case DIR_UP:
			vec.z += -(FX32_ONE * 4);
			break;
		case DIR_DOWN:
			vec.z += (FX32_ONE * 4);
			break;
		case DIR_LEFT:
			vec.x += -(FX32_ONE * 4);
			vec.z += (FX32_ONE * 4);
			break;
		case DIR_RIGHT:
			vec.x += (FX32_ONE * 4);
			vec.z += (FX32_ONE * 4);
			break;
		}
		
		EOA_MatrixSet( eoa, &vec );
	}
}

//--------------------------------------------------------------
/**
 * EOA 電灯　描画
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work *
 * @retval	nothing
 */
//--------------------------------------------------------------
static void EoaELight_Draw( EOA_PTR eoa, void *wk )
{
	EL_WORK *work;
	
	work = wk;
	
	if( work->vanish_sw == TRUE ){
		return;
	}
	
	{
		VecFx32 vec;
		VecFx32 scale = { FX32_ONE, FX32_ONE, FX32_ONE };
		MtxFx33 rot	  = { FX32_ONE, 0,0,0, FX32_ONE, 0,0,0,FX32_ONE};
		
		EOA_MatrixGet( eoa, &vec );
		simple_3DModelDraw( &work->draw_render, &vec, &rot, &scale );
	}
}

//==============================================================================
//	パーツ
//==============================================================================
//--------------------------------------------------------------
/**
 * 電灯　電灯の長さチェック
 * @param	work	EL_WORK *
 * @param	x		開始グリッドX
 * @param	z		開始グリッドZ
 * @param	dir		表示方向
 * @retval	int		電灯長さ 0-3
 */
//--------------------------------------------------------------
static int ELight_LengthCheck( EL_WORK *work, int x, int z, int dir )
{
	int len;
	CONST_FIELD_OBJ_SYS_PTR fos;
	
	fos = FieldOBJ_FieldOBJSysGet( work->head.fldobj );
	
	for( len = 0; len < EL_LEN_MAX; len++ ){
		x += FieldOBJ_DirAddValueGX( dir );
		z += FieldOBJ_DirAddValueGZ( dir );
		
		if( FieldOBJ_PosHitCheck(fos,x,z) != FLDOBJ_MOVE_HIT_BIT_NON ){
			return( len );
		}
	}
	
	len--;	//0 origin
	return( len );
}

//--------------------------------------------------------------
/**
 * 電灯の方向　長さからEL_TYPE_D_0等を取得
 * @param	dir		電灯方向 DIR_UP等
 * @param	len		電灯長さ EL_LEN_0等
 * @retval	int		EL_TYPE_D_0等
 */
//--------------------------------------------------------------
static int ELight_DirLenTypeGet( int dir, int len )
{
	GF_ASSERT( (u32)dir <= DIR_RIGHT && "ELight_DirLenTypeGet()方向異常" );
	GF_ASSERT( (u32)len < EL_LEN_MAX && "ELight_DirLenTypeGet()距離異常" );
	
	if( len == 0 ){
		return( EL_TYPE_D_0 );
	}
	
	len--;														//0 origin
	len += EL_TYPE_U_1 + (dir * EL_LEN_SIZE_MAX);
	
	return( len );
}

#if 0
//--------------------------------------------------------------
/**
 * 電灯　アクター追加
 * @param	el		FE_ELIGHT_PTR
 * @param	dir		表示方向
 * @param	len		電灯長さ 0-3
 * @retval	BLACT_WORK_PTR　追加されたBLACT_WORK_PTR
 */
//--------------------------------------------------------------
static BLACT_WORK_PTR ELight_BlActAdd( FE_ELIGHT_PTR el, int dir, int len )
{
	int id,mdl,tex;
	BLACT_WORK_PTR act;
	VecFx32 mtx = { 0, 0, 0 };
	
	GF_ASSERT( dir <= DIR_RIGHT && "ELight_BlActAdd()方向異常" );
	GF_ASSERT( len < EL_LEN_MAX && "ELight_BlActAdd()方向異常" );
	
	id = FE_BLACT_H_ID_ELIGHT;
		
	if( len == EL_LEN_0 ){
		mdl = FE_RESMID_MDL_ELIGHT_0;
		tex = FE_RESMID_TEX_ELIGHT_0;
	}else{
		len--;	//0 origin
	}
	
	FE_BlActHeaderManageAddResmID( el->fes, id, mdl, FE_RESMID_ANM_GRASS,
			tex, FE_BLACT_TEX_VRAM, DATA_BlActAnmTbl_ELight );
	
	act = FE_BlActAddID( el->fes, FE_BLACT_H_ID_ELIGHT, &mtx );
	FE_BlActHeaderManageFree( el->fes, FE_BLACT_H_ID_ELIGHT );
	
	return( act );
}
#endif

//==============================================================================
//	data
//==============================================================================
//--------------------------------------------------------------
///	モデルデータファイルパス
//--------------------------------------------------------------
static const char * const DATA_3DModelFile_ELight[EL_MDL_MAX] = 
{
	"data/e_light_d_0.nsbmd",
	"data/e_light_u_1.nsbmd","data/e_light_u_2.nsbmd","data/e_light_u_3.nsbmd",
	"data/e_light_d_1.nsbmd","data/e_light_d_2.nsbmd","data/e_light_d_3.nsbmd",
	"data/e_light_l_1.nsbmd","data/e_light_l_2.nsbmd","data/e_light_l_3.nsbmd",
	"data/e_light_r_1.nsbmd","data/e_light_r_2.nsbmd","data/e_light_r_3.nsbmd",
};

//--------------------------------------------------------------
///	電灯EOA_H
//--------------------------------------------------------------
static const EOA_H_NPP DATA_EoaH_ELight =
{
	EL_WORK_SIZE,
	EoaELight_Init,
	EoaELight_Delete,
	EoaELight_Move,
	EoaELight_Draw,
};

