//******************************************************************************
/**
 * 
 * @file	fldeff_board
 * @brief	�t�B�[���hOBJ�Ŕ�
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
///	�Ŕ���
//--------------------------------------------------------------
enum
{
	BOARDNO_A = 0,											///<�Ŕ�A
	BOARDNO_B,												///<�Ŕ�B
	BOARDNO_C,												///<�Ŕ�C
	BOARDNO_D,												///<�Ŕ�D
	BOARDNO_E,												///<�Ŕ�E
	BOARDNO_F,												///<�Ŕ�F
	BOARDNO_MAX,											///<�Ŕő�
};

//==============================================================================
//	typedef struct
//==============================================================================
//--------------------------------------------------------------
///	FE_BOARD�^
//--------------------------------------------------------------
typedef struct _TAG_FE_BOARD * FE_BOARD_PTR;

//--------------------------------------------------------------
///	FE_BOARD�\����
//--------------------------------------------------------------
typedef struct _TAG_FE_BOARD
{
	FE_SYS *fes;
	NNSG3dRenderObj render[BOARDNO_MAX];
	NNSG3dResMdl *model[BOARDNO_MAX];
	NNSG3dResFileHeader *res_file[BOARDNO_MAX];
}FE_BOARD;

#define FE_BOARD_SIZE (sizeof(FE_BOARD)) 					///<FE_BOARD�T�C�Y

//--------------------------------------------------------------
///	BOARD_ADD_H�\����
//--------------------------------------------------------------
typedef struct
{
	int board_no;
	FE_SYS *fes;
	NNSG3dRenderObj render;
	FIELD_OBJ_PTR fldobj;									///<�ŔΏۂł���t�B�[���hOBJ
}BOARD_ADD_H;

//--------------------------------------------------------------
///	EOA_BOARD_WORK�\����
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
//	�v���g�^�C�v
//==============================================================================
static void Board_GraphicInit( FE_BOARD_PTR bd );
static void Board_GraphicDelete( FE_BOARD_PTR bd );
static NNSG3dRenderObj Board_NoRenderGet( FE_BOARD_PTR bd, int type );
static int Board_OBJCodeBoardNo( int code );

static const u32 DATA_3DModelArcID_Board[BOARDNO_MAX];
static const EOA_H_NPP DATA_EoaH_Board;

//==============================================================================
//	�Ŕ@�V�X�e��
//==============================================================================
//--------------------------------------------------------------
/**
 * �Ŕ�����
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
 * �Ŕ폜
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
//	�Ŕ�	�p�[�c
//==============================================================================

//==============================================================================
//	�Ŕ@�O���t�B�b�N
//==============================================================================
//--------------------------------------------------------------
/**
 * �Ŕ� �O���t�B�b�N������
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
 * �Ŕ@�O���t�B�b�N������
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
 * �w��^�C�v�̃����_�擾
 * @param	bd		FE_BOARD_PTR
 * @param	no		BOARDNO_A��
 * @retval	NNSG3dRenderObj �w��̃����_
 */
//--------------------------------------------------------------
static NNSG3dRenderObj Board_NoRenderGet( FE_BOARD_PTR bd, int no )
{
	return( bd->render[no] );
}

//--------------------------------------------------------------
/**
 * �t�B�[���hOBJ OBJ�R�[�h����{�[�h���
 * @param	code	OBJ �R�[�h
 * @retval	int		BOARDNO_A��
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
	
	GF_ASSERT( 0 && "Board_OBJCodeBoardNo()����OBJ�R�[�h" );
	return( 0 );
}

//==============================================================================
//	�Ŕ@EOA
//==============================================================================
//--------------------------------------------------------------
/**
 * �t�B�[���hOBJ�Ŕǉ�
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
 * EOA �Ŕ@������
 * @param	eoa	EOA_PTR
 * @param	wk	eoa work *
 * @retval	int TRUE=����I���BFALSE=�ُ�I��
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
 * EOA �Ŕ@�폜
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
 * EOA �Ŕ@����
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
 * EOA �Ŕ@�`��
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
///	�Ŕ�imd�e�[�u���@���т�BOARD_WALK_UP���̒l�Ɉ�v
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
///	�Ŕ�EOA_H
//--------------------------------------------------------------
static const EOA_H_NPP DATA_EoaH_Board =
{
	EOA_BOARD_WORK_SIZE,
	EoaBoard_Init,
	EoaBoard_Delete,
	EoaBoard_Move,
	EoaBoard_Draw,
};
