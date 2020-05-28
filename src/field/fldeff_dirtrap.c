//******************************************************************************
/**
 * 
 * @file	fldeff_dirtrap.c
 * @brief	一枚ポリゴン 方向矢印罠
 * @author	k.ohno
 * @data	05.11.29
 *
 */
//******************************************************************************
#include "common.h"
#include "fieldsys.h"
#include "field_effect.h"
#include "fieldobj.h"
#include "fldeff_dirtrap.h"

//==============================================================================
//	define
//==============================================================================

#define DIRTRAP_DRAW_Z_OFFSET (FX32_ONE*(5))			///<罠描画オフセットZ軸

//==============================================================================
//	typedef struct
//==============================================================================
//--------------------------------------------------------------
///	FE_DIRTRAP型
//--------------------------------------------------------------
typedef struct _TAG_FE_DIRTRAP * FE_DIRTRAP_PTR;

//--------------------------------------------------------------
///	FE_DIRTRAP構造体
//--------------------------------------------------------------
typedef struct _TAG_FE_DIRTRAP
{
	FE_SYS *fes;
	NNSG3dRenderObj render;
	NNSG3dResMdl *model;
	NNSG3dResFileHeader *res_file;
}FE_DIRTRAP;

#define FE_DIRTRAP_SIZE (sizeof(FE_DIRTRAP)) ///<FE_DIRTRAPサイズ

//--------------------------------------------------------------
///	DIRTRAP_ADD_H構造体
//--------------------------------------------------------------
typedef struct
{
	int init_gx;
	int init_gz;
	FIELDSYS_WORK *fsys;
	FE_SYS *fes;
	FE_DIRTRAP_PTR dirtrap;						///<FE_DIRTRAP_PTR
}DIRTRAP_ADD_H;

#define DIRTRAP_ADD_H_SIZE (sizeof(DIRTRAP_ADD_H)) ///<DIRTRAP_ADD_Hサイズ

//--------------------------------------------------------------
///	DIRTRAP_WORK構造体
//--------------------------------------------------------------
typedef struct
{
    int counter;
    int dir;
	int obj_id;									///<罠対象OBJID
	int zone_id;								///<罠対象ゾーンID
	int vanish_sw;								///<非表示SW
	DIRTRAP_ADD_H head;							///<追加時のDIRTRAP_ADD_H
}DIRTRAP_WORK;

#define DIRTRAP_WORK_SIZE (sizeof(DIRTRAP_WORK))	///<DIRTRAP_WORKサイズ

//==============================================================================
//	プロトタイプ
//==============================================================================
static void DirTrap_GraphicInit( FE_DIRTRAP_PTR sd );
static void DirTrap_GraphicDelete( FE_DIRTRAP_PTR sd );

static const EOA_H_NPP DATA_EoaH_DirTrap;

//==============================================================================
//	罠　システム
//==============================================================================
//--------------------------------------------------------------
/**
 * 罠初期化
 * @param	fes		FE_SYS_PTR
 * @retval	FE_DIRTRAP_PTR	FE_DIRTRAP_PTR
 */
//--------------------------------------------------------------
void * FE_DirTrap_Init( FE_SYS *fes )
{
	FE_DIRTRAP_PTR sd;

	sd = FE_AllocClearMemory( fes, FE_DIRTRAP_SIZE, ALLOC_FR, 0 );
	sd->fes = fes;
	
	DirTrap_GraphicInit( sd );
	
	return( sd );
}

//--------------------------------------------------------------
/**
 * 罠削除
 * @param	sd		FE_DIRTRAP_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void FE_DirTrap_Delete( void *work )
{
	FE_DIRTRAP_PTR sd = work;
	DirTrap_GraphicDelete( sd );
	FE_FreeMemory( sd );
}

//==============================================================================
//	罠	パーツ
//==============================================================================

//==============================================================================
//	罠　グラフィック
//==============================================================================
//--------------------------------------------------------------
/**
 * 罠 グラフィック初期化
 * @param	sd	FE_DIRTRAP_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void DirTrap_GraphicInit( FE_DIRTRAP_PTR sd )
{
	FE_simple3DModelInit( sd->fes, NARC_fldeff_t_yaji_nsbmd, ALLOC_FR,
			&sd->render, &sd->model, &sd->res_file );
}

//--------------------------------------------------------------
/**
 * 罠 グラフィック削除
 * @param	sd	FE_DIRTRAP_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void DirTrap_GraphicDelete( FE_DIRTRAP_PTR sd )
{
    FE_FreeMemory( sd->res_file );
}

//==============================================================================
//	罠　EOA
//==============================================================================
//--------------------------------------------------------------
/**
 * トラップ追加
 * @param	fldobj		FIELD_OBJ_PTR
 * @retval	EOA_PTR
 */
//--------------------------------------------------------------
EOA_PTR FE_DirTrap_Add(  FIELDSYS_WORK *fsys, int x, int z, int dir )
{
	int param,pri;
	DIRTRAP_ADD_H head;
	FE_SYS *fes;
	VecFx32 mtx;
    EOA_PTR eoa;
	DIRTRAP_WORK *work;
	
    fes = fsys->fes;
	head.fes = fes;
	head.dirtrap = FE_EffectWorkGet( fes, FE_UG_TRAP_DIR );
	head.init_gx = x;
	head.init_gz = z;
	head.fsys = fsys;
	mtx.x = GRID_SIZE_FX32( x ) + (FX32_ONE * 9 );
	mtx.y = 0;
	mtx.z = GRID_SIZE_FX32( z );
	param = 0;

	eoa = FE_EoaAddNpp( fes, &DATA_EoaH_DirTrap, &mtx, param, &head, 0xff );
	work = EOA_LocalWorkGet( eoa );
    work->dir = dir;
    return eoa;
}

//--------------------------------------------------------------
/**
 * EOA 罠　初期化
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work *
 * @retval	int		TRUE=正常終了。FALSE=異常終了
 */
//--------------------------------------------------------------
static int EoaDirTrap_Init( EOA_PTR eoa, void *wk )
{
	DIRTRAP_WORK *work;
	const DIRTRAP_ADD_H *head;
    VecFx32 vec;
	
	work = wk;
	head = EOA_AddPtrGet( eoa );
	work->head = *head;

	vec.x = GRID_SIZE_FX32( work->head.init_gx ) + (FX32_ONE * 9 );
	vec.z = GRID_SIZE_FX32( work->head.init_gz );
    vec.y = 0;
	
	EOA_MatrixSet( eoa, &vec );

    work->counter = 20;// @@OO test time
    
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * EOA 罠　削除
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work *
 * @retval	nothing
 */
//--------------------------------------------------------------
static void EoaDirTrap_Delete( EOA_PTR eoa, void *wk )
{
}

//--------------------------------------------------------------
/**
 * EOA 罠　動作
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work *
 * @retval	nothing
 */
//--------------------------------------------------------------
static void EoaDirTrap_Move( EOA_PTR eoa, void *wk )
{
    DIRTRAP_WORK *work;
	work = wk;

    if(work->counter != 0){
        work->counter--;
    }
    else{
        FE_EoaDelete(eoa);
    }
}

//--------------------------------------------------------------
/**
 * EOA 罠　描画
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work *
 * @retval	nothing
 */
//--------------------------------------------------------------
static void EoaDirTrap_Draw( EOA_PTR eoa, void *wk )
{
	DIRTRAP_WORK *work;
	
	work = wk;
	
    {
		VecFx32 vec;
		VecFx32 scale = { FX32_ONE, FX32_ONE, FX32_ONE };
		MtxFx33 rot	  = { FX32_ONE, 0,0,0, FX32_ONE, 0,0,0,FX32_ONE};
		
		EOA_MatrixGet( eoa, &vec );
		
		vec.x += -(FX32_ONE * 1) / 2;
		vec.y += -(FX32_ONE * 1);
		vec.z += DIRTRAP_DRAW_Z_OFFSET;


        switch(work->dir){
          case DIR_UP:
            Rot360_to_MtxFx33(&rot, 0, 270, 0);
            break;
          case DIR_DOWN:
            Rot360_to_MtxFx33(&rot, 0, 90, 0);
            break;
          case DIR_RIGHT:
            Rot360_to_MtxFx33(&rot, 0, 180, 0);
            break;
          case DIR_LEFT:
          default:
            break;
        }
        simple_3DModelDraw_1mat1shape( &work->head.dirtrap->render, &vec, &rot, &scale );
	}
}

//--------------------------------------------------------------
///	罠EOA_H
//--------------------------------------------------------------
static const EOA_H_NPP DATA_EoaH_DirTrap =
{
	DIRTRAP_WORK_SIZE,
	EoaDirTrap_Init,
	EoaDirTrap_Delete,
	EoaDirTrap_Move,
	EoaDirTrap_Draw,
};

