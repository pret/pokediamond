//******************************************************************************
/**
 * 
 * @file	fldeff_board
 * @brief	フィールドOBJ看板
 * @author	kagaya
 * @data	05.07.13
 *
 */
//******************************************************************************
#include "common.h"
#include "fieldsys.h"
#include "field_effect.h"
#include "fieldobj.h"

#include "fldeff_board.h"

//==============================================================================
//	define
//==============================================================================
//--------------------------------------------------------------
///	看板識別
//--------------------------------------------------------------
enum
{
	BOARDNO_A = 0,											///<看板A
	BOARDNO_B,												///<看板B
	BOARDNO_C,												///<看板C
	BOARDNO_D,												///<看板D
	BOARDNO_E,												///<看板E
	BOARDNO_F,												///<看板F
	BOARDNO_MAX,											///<看板最大
};

//==============================================================================
//	typedef struct
//==============================================================================
//--------------------------------------------------------------
///	FE_BOARD型
//--------------------------------------------------------------
typedef struct _TAG_FE_BOARD * FE_BOARD_PTR;

//--------------------------------------------------------------
///	FE_BOARD構造体
//--------------------------------------------------------------
typedef struct _TAG_FE_BOARD
{
	FE_SYS *fes;
	NNSG3dRenderObj render[BOARDNO_MAX];
	NNSG3dResMdl *model[BOARDNO_MAX];
	NNSG3dResFileHeader *res_file[BOARDNO_MAX];
}FE_BOARD;

#define FE_BOARD_SIZE (sizeof(FE_BOARD)) 					///<FE_BOARDサイズ

//--------------------------------------------------------------
///	BOARD_ADD_H構造体
//--------------------------------------------------------------
typedef struct
{
	int board_no;
	FE_SYS *fes;
	NNSG3dRenderObj render;
	FIELD_OBJ_PTR fldobj;									///<看板対象であるフィールドOBJ
}BOARD_ADD_H;

//--------------------------------------------------------------
///	EOA_BOARD_WORK構造体
//--------------------------------------------------------------
typedef struct
{
	int seq_no;
	int obj_id;
	int zone_id;
	BOARD_ADD_H head;
}EOA_BOARD_WORK;

#define EOA_BOARD_WORK_SIZE (sizeof(EOA_BOARD_WORK))

//==============================================================================
//	プロトタイプ
//==============================================================================
static void Board_GraphicInit( FE_BOARD_PTR bd );
static void Board_GraphicDelete( FE_BOARD_PTR bd );
static NNSG3dRenderObj Board_NoRenderGet( FE_BOARD_PTR bd, int type );
static int Board_OBJCodeBoardNo( int code );

static const u32 DATA_3DModelArcID_Board[BOARDNO_MAX];
static const EOA_H_NPP DATA_EoaH_Board;

//==============================================================================
//	看板　システム
//==============================================================================
//--------------------------------------------------------------
/**
 * 看板初期化
 * @param	fes		FE_SYS_PTR
 * @retval	FE_BOARD_PTR		FE_FOOTMARK_PTR
 */
//--------------------------------------------------------------
void * FE_Board_Init( FE_SYS *fes )
{
	FE_BOARD_PTR bd;
	
	bd = FE_AllocClearMemory( fes, FE_BOARD_SIZE, ALLOC_FR, 0 );
	bd->fes = fes;
	
	Board_GraphicInit( bd );
	return( bd );
}

//--------------------------------------------------------------
/**
 * 看板削除
 * @param	bd		FE_BOARD_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void FE_Board_Delete( void *work )
{
	FE_BOARD_PTR bd = work;
	Board_GraphicDelete( bd );
	FE_FreeMemory( bd );
}

//==============================================================================
//	看板	パーツ
//==============================================================================

//==============================================================================
//	看板　グラフィック
//==============================================================================
//--------------------------------------------------------------
/**
 * 看板 グラフィック初期化
 * @param	bd		FE_BOARD_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void Board_GraphicInit( FE_BOARD_PTR bd )
{
	int i;
	u32 id;
	
	for( i = 0; i < BOARDNO_MAX; i++ ){
		id = DATA_3DModelArcID_Board[i];
		FE_simple3DModelInit( bd->fes, id, ALLOC_FR,
			&bd->render[i], &bd->model[i], &bd->res_file[i] );
	}
}

//--------------------------------------------------------------
/**
 * 看板　グラフィック初期化
 * @param	bd		FE_BOARD_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void Board_GraphicDelete( FE_BOARD_PTR bd )
{
	int i;
	
	for( i = 0; i < BOARDNO_MAX; i++ ){
		FE_FreeMemory( bd->res_file[i] );
	}
}

//--------------------------------------------------------------
/**
 * 指定タイプのレンダ取得
 * @param	bd		FE_BOARD_PTR
 * @param	no		BOARDNO_A等
 * @retval	NNSG3dRenderObj 指定のレンダ
 */
//--------------------------------------------------------------
static NNSG3dRenderObj Board_NoRenderGet( FE_BOARD_PTR bd, int no )
{
	return( bd->render[no] );
}

//--------------------------------------------------------------
/**
 * フィールドOBJ OBJコードからボード種類
 * @param	code	OBJ コード
 * @retval	int		BOARDNO_A等
 */
//--------------------------------------------------------------
static int Board_OBJCodeBoardNo( int code )
{
	switch( code ){
	case BOARD_A:	return( BOARDNO_A );
	case BOARD_B:	return( BOARDNO_B );
	case BOARD_C:	return( BOARDNO_C );
	case BOARD_D:	return( BOARDNO_D );
	case BOARD_E:	return( BOARDNO_E );
	case BOARD_F:	return( BOARDNO_F );
	}
	
	GF_ASSERT( 0 && "Board_OBJCodeBoardNo()無効OBJコード" );
	return( 0 );
}

//==============================================================================
//	看板　EOA
//==============================================================================
//--------------------------------------------------------------
/**
 * フィールドOBJ看板追加
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	eoa		EOA_PTR
 */
//--------------------------------------------------------------
EOA_PTR FE_FldOBJBoard_Add( FIELD_OBJ_PTR fldobj )
{
	EOA_PTR eoa;
	FE_SYS *fes;
	FE_BOARD_PTR bd;
	BOARD_ADD_H head;
	
	fes = FE_FieldOBJ_FE_SYS_Get( fldobj );
	bd = FE_EffectWorkGet( fes, FE_FLD_BOARD );
	
	head.board_no = Board_OBJCodeBoardNo( FieldOBJ_OBJCodeGet(fldobj) );
	head.render = Board_NoRenderGet( bd, head.board_no );
	head.fes = fes;
	head.fldobj = fldobj;
	
	{
		VecFx32 mtx = {0,0,0};
		int pri = FieldOBJ_TCBPriGet( fldobj, FLDOBJ_TCBPRI_OFFS_AFTER );
		eoa = FE_EoaAddNpp( fes, &DATA_EoaH_Board, &mtx, 0, &head, pri );
	}
	
	return( eoa );
}

//--------------------------------------------------------------
/**
 * EOA 看板　初期化
 * @param	eoa	EOA_PTR
 * @param	wk	eoa work *
 * @retval	int TRUE=正常終了。FALSE=異常終了
 */
//--------------------------------------------------------------
static int EoaBoard_Init( EOA_PTR eoa, void *wk )
{
	EOA_BOARD_WORK *work;
	const BOARD_ADD_H *head;
	
	work = wk;
	head = EOA_AddPtrGet( eoa );
	work->head = *head;
	
	work->obj_id = FieldOBJ_OBJIDGet( work->head.fldobj );
	
	if( FieldOBJ_StatusBitCheck_Alies(work->head.fldobj) == TRUE ){
		work->zone_id = FieldOBJ_ZoneIDGetAlies( work->head.fldobj );
	}else{
		work->zone_id = FieldOBJ_ZoneIDGet( work->head.fldobj );
	}
	
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * EOA 看板　削除
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work *
 * @retval	nothing
 */
//--------------------------------------------------------------
static void EoaBoard_Delete( EOA_PTR eoa, void *wk )
{
}

//--------------------------------------------------------------
/**
 * EOA 看板　動作
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work *
 * @retval	nothing
 */
//--------------------------------------------------------------
static void EoaBoard_Move( EOA_PTR eoa, void *wk )
{
	EOA_BOARD_WORK *work;
	FIELD_OBJ_PTR fldobj;
	
	work = wk;
	fldobj = work->head.fldobj;
	
	if( FieldOBJ_CheckSameID(fldobj,work->obj_id,work->zone_id) == FALSE ){
		FE_EoaDelete( eoa );
		return;
	}
	
	{
		VecFx32 mtx,d_mtx;
			
		FieldOBJ_VecPosGet( fldobj, &mtx );
		FieldOBJ_VecDrawOffsGet( fldobj, &d_mtx );
		
		mtx.x += d_mtx.x + FLDOBJ_BLACT_X_GROUND_OFFS_FX32;
		mtx.y += d_mtx.y + FLDOBJ_BLACT_Y_GROUND_OFFS_FX32;
		mtx.z += d_mtx.z + FLDOBJ_BLACT_Z_GROUND_OFFS_FX32 - (FX32_ONE * 6) - (FX32_ONE*2);
		
		EOA_MatrixSet( eoa, &mtx );
	}
}

//--------------------------------------------------------------
/**
 * EOA 看板　描画
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work *
 * @retval	nothing
 */
//--------------------------------------------------------------
static void EoaBoard_Draw( EOA_PTR eoa, void *wk )
{
	EOA_BOARD_WORK *work;
	
	work = wk;
	
	{
		VecFx32 vec;
		VecFx32 scale = { FX32_ONE, FX32_ONE, FX32_ONE };
		MtxFx33 rot	  = { FX32_ONE, 0,0,0, FX32_ONE, 0,0,0,FX32_ONE};
		
		EOA_MatrixGet( eoa, &vec );
		simple_3DModelDraw( &work->head.render, &vec, &rot, &scale );
	}
}

//==============================================================================
//	data
//==============================================================================
//--------------------------------------------------------------
///	看板imdテーブル　並びはBOARD_WALK_UP等の値に一致
//--------------------------------------------------------------
static const u32 DATA_3DModelArcID_Board[BOARDNO_MAX] =
{
	NARC_fldeff_board_a_nsbmd,
	NARC_fldeff_board_b_nsbmd,
	NARC_fldeff_board_c_nsbmd,
	NARC_fldeff_board_d_nsbmd,
	NARC_fldeff_board_e_nsbmd,
	NARC_fldeff_board_f_nsbmd,
};

//--------------------------------------------------------------
///	看板EOA_H
//--------------------------------------------------------------
static const EOA_H_NPP DATA_EoaH_Board =
{
	EOA_BOARD_WORK_SIZE,
	EoaBoard_Init,
	EoaBoard_Delete,
	EoaBoard_Move,
	EoaBoard_Draw,
};
