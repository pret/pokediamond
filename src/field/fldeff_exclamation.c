//******************************************************************************
/**
 * 
 * @file	fldeff_exclamation.c
 * @brief	一枚ポリゴン 地下用 ！マーク
 * @author	k.ohno
 * @data	05.02.13
 *
 */
//******************************************************************************
#include "common.h"
#include "fieldsys.h"
#include "field_effect.h"
#include "fieldobj.h"
#include "fldeff_exclamation.h"

//==============================================================================
//	define
//==============================================================================

#define EXCLAMATION_FLDOBJ_Y_MOVE_START ((FX32_ONE*6))				///<旗初速
#define EXCLAMATION_FLDOBJ_Y_OFFSET ((FX32_ONE*25))				///<フィールドOBJからのYオフセット
#define EXCLAMATION_FLDOBJ_Z_OFFSET ((FX32_ONE*-10))					///<フィールドOBJからのZオフセット
#define EXCLAMATION_END_FRAME (30)									///<旗終了フレーム	

//==============================================================================
//	typedef struct
//==============================================================================
//--------------------------------------------------------------
///	FE_EXCLAMATION型
//--------------------------------------------------------------
typedef struct _TAG_FE_EXCLAMATION * FE_EXCLAMATION_PTR;

//--------------------------------------------------------------
///	FE_EXCLAMATION構造体
//--------------------------------------------------------------
typedef struct _TAG_FE_EXCLAMATION
{
	int add_count;
	int draw_init;
	FE_SYS *fes;
	NNSG3dRenderObj render;
	NNSG3dResMdl *model;
	NNSG3dResFileHeader *res_file;
	FIELD_OBJ_PTR fldobj;						///<旗の対象FIELD_OBJ_PTR
}FE_EXCLAMATION;

#define FE_EXCLAMATION_SIZE (sizeof(FE_EXCLAMATION)) ///<FE_EXCLAMATIONサイズ

//--------------------------------------------------------------
///	EXCLAMATION_ADD_H構造体
//--------------------------------------------------------------
typedef struct
{
	FE_SYS *fes;
	FE_EXCLAMATION_PTR exclamation;						///<FE_EXCLAMATION_PTR
	FIELD_OBJ_PTR fldobj;						///<旗の対象FIELD_OBJ_PTR
}EXCLAMATION_ADD_H;

#define EXCLAMATION_ADD_H_SIZE (sizeof(EXCLAMATION_ADD_H)) ///<EXCLAMATION_ADD_Hサイズ

//--------------------------------------------------------------
///	EXCLAMATION_WORK構造体
//--------------------------------------------------------------
typedef struct
{
	int seq_no;									///<動作番号
	int frame;									///<フレーム
	int obj_id;									///<旗対象OBJID
	int zone_id;								///<旗対象ゾーンID
	int vanish_sw;								///<非表示SW
	int end_sw;									///<終了SW
	VecFx32 offset;								///<オフセット
	VecFx32 move;								///<移動量
	EXCLAMATION_ADD_H head;							///<追加時のEXCLAMATION_ADD_H
}EXCLAMATION_WORK;

#define EXCLAMATION_WORK_SIZE (sizeof(EXCLAMATION_WORK))	///<EXCLAMATION_WORKサイズ

//==============================================================================
//	プロトタイプ
//==============================================================================
static void Exclamation_GraphicInit( FE_EXCLAMATION_PTR sd );
static void Exclamation_GraphicDelete( FE_EXCLAMATION_PTR sd );

static const EOA_H_NPP DATA_EoaH_Exclamation;

//==============================================================================
//	旗　システム
//==============================================================================
//--------------------------------------------------------------
/**
 * 旗初期化
 * @param	fes		FE_SYS_PTR
 * @retval	FE_EXCLAMATION_PTR	FE_EXCLAMATION_PTR
 */
//--------------------------------------------------------------
void * FE_Exclamation_Init( FE_SYS *fes )
{
	FE_EXCLAMATION_PTR sd;

	sd = FE_AllocClearMemory( fes, FE_EXCLAMATION_SIZE, ALLOC_FR, 0 );
	sd->fes = fes;
	
	Exclamation_GraphicInit( sd );
	
	return( sd );
}

//--------------------------------------------------------------
/**
 * 旗削除
 * @param	sd		FE_EXCLAMATION_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void FE_Exclamation_Delete( void *work )
{
	FE_EXCLAMATION_PTR sd = work;
	Exclamation_GraphicDelete( sd );
	FE_FreeMemory( sd );
}

//==============================================================================
//	旗	パーツ
//==============================================================================

//==============================================================================
//	旗　グラフィック
//==============================================================================
//--------------------------------------------------------------
/**
 * 旗 グラフィック初期化
 * @param	sd	FE_EXCLAMATION_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void Exclamation_GraphicInit( FE_EXCLAMATION_PTR sd )
{
	FE_simple3DModelInit( sd->fes, NARC_fldeff_ug_exclamation_nsbmd, ALLOC_FR,
			&sd->render, &sd->model, &sd->res_file );
}

//--------------------------------------------------------------
/**
 * 旗 グラフィック削除
 * @param	sd	FE_EXCLAMATION_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void Exclamation_GraphicDelete( FE_EXCLAMATION_PTR sd )
{
    FE_FreeMemory( sd->res_file );
}

//==============================================================================
//	旗　EOA
//==============================================================================
//--------------------------------------------------------------
/**
 * トラップ追加
 * @param	fldobj		FIELD_OBJ_PTR
 * @retval	EOA_PTR
 */
//--------------------------------------------------------------
EOA_PTR FE_Exclamation_Add(  FIELD_OBJ_PTR fldobj )
{
	int param,pri;
	EXCLAMATION_ADD_H head;
	FE_SYS *fes;
	VecFx32 mtx;
    EOA_PTR eoa;
	EXCLAMATION_WORK *work;
	
	fes = FE_FieldOBJ_FE_SYS_Get( fldobj );
	head.fes = fes;
	head.exclamation = FE_EffectWorkGet( fes, FE_UG_TRAP_EXCLAMATION );
	head.fldobj = fldobj;

    FieldOBJ_VecPosGet( fldobj, &mtx );
	param = 0;

	eoa = FE_EoaAddNpp( fes, &DATA_EoaH_Exclamation, &mtx, param, &head, 0xff );
    return eoa;
}

//--------------------------------------------------------------
/**
 * EOA 旗　初期化
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work *
 * @retval	int		TRUE=正常終了。FALSE=異常終了
 */
//--------------------------------------------------------------
static int EoaExclamation_Init( EOA_PTR eoa, void *wk )
{
	EXCLAMATION_WORK *work;
	const EXCLAMATION_ADD_H *head;
    VecFx32 vec;
	
	work = wk;
	head = EOA_AddPtrGet( eoa );
	work->head = *head;

	work->obj_id = FieldOBJ_OBJIDGet( work->head.fldobj );
	work->zone_id = FieldOBJ_ZoneIDGet( work->head.fldobj );
	work->move.y = EXCLAMATION_FLDOBJ_Y_MOVE_START;

    FieldOBJ_VecPosGet( work->head.fldobj, &vec );

    EOA_MatrixSet( eoa, &vec );

    
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * EOA 旗　削除
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work *
 * @retval	nothing
 */
//--------------------------------------------------------------
static void EoaExclamation_Delete( EOA_PTR eoa, void *wk )
{
}

//--------------------------------------------------------------
/**
 * EOA 旗　動作
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work *
 * @retval	nothing
 */
//--------------------------------------------------------------
static void EoaExclamation_Move( EOA_PTR eoa, void *wk )
{
	EXCLAMATION_WORK *work;
	FIELD_OBJ_PTR fldobj;
	VecFx32 vec;
	
	work = wk;
    fldobj = work->head.fldobj;
	
	GF_ASSERT( FieldOBJ_CheckSameID(fldobj,work->obj_id,work->zone_id) != FALSE &&
		"旗動作中に対象のフィールドOBJが削除されました" );
	
    FieldOBJ_VecPosGet( fldobj, &vec );
    vec.z += EXCLAMATION_FLDOBJ_Z_OFFSET;
    EOA_MatrixSet( eoa, &vec );

}

//--------------------------------------------------------------
/**
 * EOA 旗　描画
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work *
 * @retval	nothing
 */
//--------------------------------------------------------------
static void EoaExclamation_Draw( EOA_PTR eoa, void *wk )
{
	EXCLAMATION_WORK *work;
	
	work = wk;
	
    {
		VecFx32 vec;
		VecFx32 scale = { FX32_ONE, FX32_ONE, FX32_ONE };
		MtxFx33 rot	  = { FX32_ONE, 0,0,0, FX32_ONE, 0,0,0,FX32_ONE};
		
		EOA_MatrixGet( eoa, &vec );
		
		vec.y += EXCLAMATION_FLDOBJ_Y_OFFSET;
        vec.z += - (FX32_ONE*5);

        {    // カメラ逆行列を入れる
            const MtxFx43* pCamInv = NNS_G3dGlbGetInvCameraMtx();
            MtxFx33 Mat33;
            
            Rot360_to_MtxFx33(&rot, 90, 0, 0);
            MTX_Copy43To33(pCamInv, &Mat33);
            MTX_Concat33(&rot, &Mat33, &rot);
        }
        simple_3DModelDraw_1mat1shape( &work->head.exclamation->render, &vec, &rot, &scale );
	}
}

//--------------------------------------------------------------
///	旗EOA_H
//--------------------------------------------------------------
static const EOA_H_NPP DATA_EoaH_Exclamation =
{
	EXCLAMATION_WORK_SIZE,
	EoaExclamation_Init,
	EoaExclamation_Delete,
	EoaExclamation_Move,
	EoaExclamation_Draw,
};

