//******************************************************************************
/**
 *
 * @file	fieldobj_move_1.c
 * @brief	�t�B�[���hOBJ�@��{����n����1�@�T�u����
 * @author	kagaya
 * @data	05.07.21
 *
 */
//******************************************************************************
#include "common.h"
#include "fieldsys.h"
#include "fieldobj.h"

//==============================================================================
//	define
//==============================================================================
//#define DEBUG_IDO_ASSERT

//==============================================================================
//	struct
//==============================================================================

//==============================================================================
//	�v���g�^�C�v
//==============================================================================
static void MoveSub_InitProcCall( FIELD_OBJ_PTR fldobj );
static int MoveSub_StartCheckProcCall( FIELD_OBJ_PTR fldobj );
static int MoveSub_MoveProcCall( FIELD_OBJ_PTR fldobj );

static int MoveSub_PosUpdateStartCheck( FIELD_OBJ_PTR fldobj );
static int MoveSub_PosUpdateEndCheck( FIELD_OBJ_PTR fldobj );

static void SubMoveNon_Init( FIELD_OBJ_PTR fldobj );
static int SubMoveNon_StartCheck( FIELD_OBJ_PTR fldobj );
static int SubMoveNon_Move( FIELD_OBJ_PTR fldobj );

static void SubMoveKyoro_Init( FIELD_OBJ_PTR fldobj );
static int SubMoveKyoro_StartCheck( FIELD_OBJ_PTR fldobj );
static int SubMoveKyoro_Move( FIELD_OBJ_PTR fldobj );

static void SubMoveSpinStop_Init( FIELD_OBJ_PTR fldobj );
static int SubMoveSpinStop_StartCheck( FIELD_OBJ_PTR fldobj );
static int SubMoveSpinStop_Move( FIELD_OBJ_PTR fldobj );

void (* const DATA_FldOBJ_EventTypeInitProcTbl[])( FIELD_OBJ_PTR );
int (* const DATA_FldOBJ_EventTypeStartCheckProcTbl[])( FIELD_OBJ_PTR );
int (* const DATA_FldOBJ_EventTypeMoveProcTbl[])( FIELD_OBJ_PTR );

//==============================================================================
//	�T�u����
//==============================================================================
//--------------------------------------------------------------
/**
 * �T�u���쏉����
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_MoveSubProcInit( FIELD_OBJ_PTR fldobj )
{
	MoveSub_InitProcCall( fldobj );
}

//--------------------------------------------------------------
/**
 * �T�u����
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	int		TRUE=�T�u����ɂ��ړ��A��
 */
//--------------------------------------------------------------
int FieldOBJ_MoveSub( FIELD_OBJ_PTR fldobj )
{
	if( MoveSub_StartCheckProcCall(fldobj) == FALSE ){
		return( FALSE );
	}
	
	if( MoveSub_MoveProcCall(fldobj) == FALSE ){
		return( FALSE );
	}
	
	return( TRUE );
}

//==============================================================================
//	�T�u���쏈���@�p�[�c
//==============================================================================
//--------------------------------------------------------------
/**
 * �������֐��Ăяo��
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void MoveSub_InitProcCall( FIELD_OBJ_PTR fldobj )
{
	int type = FieldOBJ_EventTypeGet( fldobj );
	DATA_FldOBJ_EventTypeInitProcTbl[type]( fldobj );
}

//--------------------------------------------------------------
/**
 * �`�F�b�N�֐��Ăяo��
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	int		TRUE=�`�F�b�N�Ɉ�����������
 */
//--------------------------------------------------------------
static int MoveSub_StartCheckProcCall( FIELD_OBJ_PTR fldobj )
{
	int type = FieldOBJ_EventTypeGet( fldobj );
	return( DATA_FldOBJ_EventTypeStartCheckProcTbl[type](fldobj) );
}

//--------------------------------------------------------------
/**
 * ����֐��Ăяo��
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	int		TRUE=���쒆
 */
//--------------------------------------------------------------
static int MoveSub_MoveProcCall( FIELD_OBJ_PTR fldobj )
{
	int type = FieldOBJ_EventTypeGet( fldobj );
	return( DATA_FldOBJ_EventTypeMoveProcTbl[type](fldobj) );
}

//==============================================================================
//	�T�u����p�p�[�c
//==============================================================================
//--------------------------------------------------------------
/**
 * ���W�X�V�J�n���`�F�b�N
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	int		TRUE=�X�V
 */
//--------------------------------------------------------------
static int MoveSub_PosUpdateStartCheck( FIELD_OBJ_PTR fldobj )
{
	int now = FieldOBJ_NowPosGX_Get( fldobj );
	int old = FieldOBJ_OldPosGX_Get( fldobj );
	
	if( now != old ){
		return( TRUE );
	}
	
	now = FieldOBJ_NowPosGZ_Get( fldobj );
	old = FieldOBJ_OldPosGZ_Get( fldobj );
	
	if( now != old ){
		return( TRUE );
	}
	
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * ���W�X�V�I�����`�F�b�N
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	int		TRUE=�I��
 */
//--------------------------------------------------------------
static int MoveSub_PosUpdateEndCheck( FIELD_OBJ_PTR fldobj )
{
	int now = FieldOBJ_NowPosGX_Get( fldobj );
	int old = FieldOBJ_OldPosGX_Get( fldobj );
	
	if( now != old ){
		return( FALSE );
	}
	
	now = FieldOBJ_NowPosGZ_Get( fldobj );
	old = FieldOBJ_OldPosGZ_Get( fldobj );
	
	if( now != old ){
		return( FALSE );
	}
	
	return( TRUE );
}

//==============================================================================
//	�T�u����@����
//==============================================================================
//--------------------------------------------------------------
/**
 * �T�u���쏉�����@����
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void SubMoveNon_Init( FIELD_OBJ_PTR fldobj )
{
}

//--------------------------------------------------------------
/**
 * �T�u����X�^�[�g�`�F�b�N�@����
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	int		FALSE
 */
//--------------------------------------------------------------
static int SubMoveNon_StartCheck( FIELD_OBJ_PTR fldobj )
{
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * �T�u����@����
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	int		TRUE=���쒆
 */
//--------------------------------------------------------------
static int SubMoveNon_Move( FIELD_OBJ_PTR fldobj )
{
	return( FALSE );
}

//==============================================================================
//	�T�u����@�~�܂��Ă���낫���
//==============================================================================
//--------------------------------------------------------------
///	SUBWORK_KYORO�\����
//--------------------------------------------------------------
typedef struct
{
	u8 check_seq_no;
	u8 move_seq_no;
	s8 walk_count;
	s8 max_count;
	
	s8 origin_dir;
	s8 dir_type;
	s8 dir_no;
	s8 dir_count;
	s8 wait;
}SUBWORK_KYORO;

#define SUBWORK_KYORO_SIZE (sizeof(SUBWORK_KYORO))

//--------------------------------------------------------------
///	����낫������
//--------------------------------------------------------------
enum
{
	DIR_H_TYPE = 0,		///<����������낫���
	DIR_V_TYPE,			///<�c��������낫���
};

#define KYORO_WAIT_FRAME (8)		///<����낫���̍���
#define KYORO_COUNT_MAX (4)			///<����낫���񐔍ő�

//--------------------------------------------------------------
/**
 * �~�܂��Ă���낫���@������
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void SubMoveKyoro_Init( FIELD_OBJ_PTR fldobj )
{
	SUBWORK_KYORO *work;
	
	work = FieldOBJ_MoveSubProcWorkInit( fldobj, SUBWORK_KYORO_SIZE );
	work->max_count = FieldOBJ_ParamGet( fldobj, FLDOBJ_PARAM_1 );
}

//--------------------------------------------------------------
/**
 * �~�܂��Ă���낫���@�X�^�[�g�`�F�b�N
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	int		TRUE=����A��
 */
//--------------------------------------------------------------
static int SubMoveKyoro_StartCheck( FIELD_OBJ_PTR fldobj )
{
	SUBWORK_KYORO *work;
	
	work = FieldOBJ_MoveSubProcWorkGet( fldobj );
	
	switch( work->check_seq_no ){
	case 0:														//�ړ��J�n�Ď�
		if( MoveSub_PosUpdateStartCheck(fldobj) == TRUE ){
			work->check_seq_no++;
		}
		
		break;
	case 1:														//�ړ��I���Ď�
		if( MoveSub_PosUpdateEndCheck(fldobj) == FALSE ){
			break;
		}
		
		work->walk_count++;
		
		if( work->walk_count < work->max_count ){
			work->check_seq_no = 0;
			break;
		}
		
		work->check_seq_no++;
	case 2:														//�ړ������Ď�
		if( FieldOBJ_StatusBitCheck_Move(fldobj) == TRUE ){
#ifdef DEBUG_IDO_ASSERT
			GF_ASSERT( MoveSub_PosUpdateStartCheck(fldobj) == TRUE &&
					"SubMoveKyoro_StartCheck()ERROR" );
#endif
			break;
		}
		
		work->check_seq_no++;
		work->walk_count = 0;
		work->move_seq_no = 0;
	case 3:														//�T�u���쒆
		return( TRUE );
	}
	
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * �~�܂��Ă���낫���@����
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	int		TRUE=���쒆
 */
//--------------------------------------------------------------
static int SubMoveKyoro_Move( FIELD_OBJ_PTR fldobj )
{
	SUBWORK_KYORO *work;
	
	work = FieldOBJ_MoveSubProcWorkGet( fldobj );
	
	switch( work->move_seq_no ){
	case 0:														//������
		{
			int type_tbl[4] = {DIR_H_TYPE,DIR_H_TYPE,DIR_V_TYPE,DIR_V_TYPE};
			int dir = FieldOBJ_DirDispGet( fldobj );
			work->origin_dir = dir;
			work->dir_type = type_tbl[dir];
			work->move_seq_no++;
		}
	case 1:														//�����Z�b�g	
		{
			int dir_tbl[2][2] = { {DIR_LEFT,DIR_RIGHT},{DIR_UP,DIR_DOWN} };
			int dir = dir_tbl[work->dir_type][work->dir_no];
			int code = FieldOBJ_AcmdCodeDirChange( dir, AC_DIR_U );
			FieldOBJ_CmdSet( fldobj, code );
			work->move_seq_no++;
		}
	case 2:
		{
			if( FieldOBJ_CmdAction(fldobj) == FALSE ){
				return( TRUE );
			}
			
			work->move_seq_no++;
		}
	case 3:
		{
			work->wait++;
			
			if( work->wait < KYORO_WAIT_FRAME ){
				return( TRUE );
			}
			
			work->wait = 0;
			work->dir_count++;
			
			if( work->dir_count < KYORO_COUNT_MAX ){
				work->dir_no = (work->dir_no + 1) & 0x01;
				work->move_seq_no = 1;
				return( TRUE );
			}
			
			FieldOBJ_DirDispCheckSet( fldobj, work->origin_dir );
			work->move_seq_no++;
			work->dir_count = 0;
			work->check_seq_no = 0;
		}
	}
	
	return( FALSE );
}

//==============================================================================
//	�T�u����@�~�܂��ăN���N��
//==============================================================================
//--------------------------------------------------------------
///	SUBWORK_SPIN_STOP�\����
//--------------------------------------------------------------
typedef struct
{
	u8 check_seq_no;
	u8 move_seq_no;
	s8 walk_count;
	s8 max_count;
	
	s8 origin_dir;
	s8 dir_type;
	s8 dir_no;
	s8 dir_count;
	s8 wait;
}SUBWORK_SPIN_STOP;

#define SUBWORK_SPIN_STOP_SIZE (sizeof(SUBWORK_SPIN_STOP))

//--------------------------------------------------------------
///	��]����
//--------------------------------------------------------------
enum
{
	SPIN_STOP_L_TYPE = 0,		///<����]
	SPIN_STOP_R_TYPE,			///<�E��]
};

#define SPIN_STOP_WAIT_FRAME (8)	///<��]�̊�
#define SPIN_STOP_COUNT_MAX (4)		///<��]�ő吔

//--------------------------------------------------------------
/**
 * �~�܂��ăN���N���@������
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void SubMoveSpinStop_Init( FIELD_OBJ_PTR fldobj )
{
	int type;
	SUBWORK_SPIN_STOP *work;
	
	work = FieldOBJ_MoveSubProcWorkInit( fldobj, SUBWORK_SPIN_STOP_SIZE );
	work->max_count = FieldOBJ_ParamGet( fldobj, FLDOBJ_PARAM_1 );
	
	type = FieldOBJ_EventTypeGet( fldobj );
	
	if( type == EV_TYPE_TRAINER_SPIN_STOP_L ){
		type = SPIN_STOP_L_TYPE;
	}else{
		type = SPIN_STOP_R_TYPE;
	}
	
	work->dir_type = type;
}

//--------------------------------------------------------------
/**
 * �~�܂��ăN���N���@�X�^�[�g�`�F�b�N
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	int		TRUE=����A��
 */
//--------------------------------------------------------------
static int SubMoveSpinStop_StartCheck( FIELD_OBJ_PTR fldobj )
{
	SUBWORK_SPIN_STOP *work;
	
	work = FieldOBJ_MoveSubProcWorkGet( fldobj );
	
	switch( work->check_seq_no ){
	case 0:														//�ړ��J�n�Ď�
		if( MoveSub_PosUpdateStartCheck(fldobj) == TRUE ){
			work->check_seq_no++;
		}
		
		break;
	case 1:														//�ړ��I���Ď�
		if( MoveSub_PosUpdateEndCheck(fldobj) == FALSE ){
			break;
		}
		
		work->walk_count++;
		
		if( work->walk_count < work->max_count ){
			work->check_seq_no = 0;
			break;
		}
		
		work->check_seq_no++;
	case 2:														//�ړ������Ď�
		if( FieldOBJ_StatusBitCheck_Move(fldobj) == TRUE ){
#ifdef DEBUG_IDO_ASSERT
			GF_ASSERT( MoveSub_PosUpdateStartCheck(fldobj) == TRUE &&
				"SubMoveKyoro_StartCheck()�Ώۂ̈ړ����@���ُ�" );
#endif
			break;
		}
		
		work->check_seq_no++;
		work->walk_count = 0;
		work->move_seq_no = 0;
	case 3:														//�T�u���쒆
		return( TRUE );
	}
	
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * �~�܂��ăN���N���@����
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	int		TRUE=���쒆
 */
//--------------------------------------------------------------
static int SubMoveSpinStop_Move( FIELD_OBJ_PTR fldobj )
{
	SUBWORK_KYORO *work;
	int spin_tbl[2][4] =
	{ {DIR_UP,DIR_LEFT,DIR_DOWN,DIR_RIGHT},{DIR_UP,DIR_RIGHT,DIR_DOWN,DIR_LEFT} };
	
	work = FieldOBJ_MoveSubProcWorkGet( fldobj );
	
	switch( work->move_seq_no ){
	case 0:														//������
		{
			int i,dir = FieldOBJ_DirDispGet( fldobj );
			
			for( i = 0; (i < DIR_4_MAX && dir != spin_tbl[work->dir_type][i]); i++ ){}
			GF_ASSERT( i < DIR_4_MAX && "SubMoveKyoro_Move()�����ُ�" );
			
			work->origin_dir = dir;
			work->dir_no = (i + 1) % SPIN_STOP_COUNT_MAX;		//+1=1��
			work->move_seq_no++;
		}
	case 1:														//�����Z�b�g	
		{
			int dir = spin_tbl[work->dir_type][work->dir_no];
			int code = FieldOBJ_AcmdCodeDirChange( dir, AC_DIR_U );
			FieldOBJ_CmdSet( fldobj, code );
			work->move_seq_no++;
		}
	case 2:
		{
			if( FieldOBJ_CmdAction(fldobj) == FALSE ){
				return( TRUE );
			}
			
			work->move_seq_no++;
		}
	case 3:
		{
			work->wait++;
			
			if( work->wait < SPIN_STOP_WAIT_FRAME ){
				return( TRUE );
			}
			
			work->wait = 0;
			work->dir_count++;
			
			if( work->dir_count < SPIN_STOP_COUNT_MAX ){
				work->dir_no = (work->dir_no + 1) % SPIN_STOP_COUNT_MAX;
				work->move_seq_no = 1;
				return( TRUE );
			}
			
			FieldOBJ_DirDispCheckSet( fldobj, work->origin_dir );
			work->move_seq_no++;
			work->dir_count = 0;
			work->check_seq_no = 0;
		}
	}
	
	return( FALSE );
}

//==============================================================================
//	data
//==============================================================================
//--------------------------------------------------------------
//	�C�x���g�^�C�v�ʏ������֐� EV_TYPE_NORMAL���̒l�Ɉ�v
//--------------------------------------------------------------
static void (* const DATA_FldOBJ_EventTypeInitProcTbl[])( FIELD_OBJ_PTR ) =
{
	SubMoveNon_Init, //EV_TYPE_NORMAL
	SubMoveNon_Init, //EV_TYPE_TRAINER
	SubMoveNon_Init, //EV_TYPE_TRAINER_EYEALL
	SubMoveNon_Init, //EV_TYPE_ITEM
	SubMoveKyoro_Init, //EV_TYPE_TRAINER_KYORO
	SubMoveSpinStop_Init, //EV_TYPE_TRAINER_SPIN_STOP_L
	SubMoveSpinStop_Init, //EV_TYPE_TRAINER_SPIN_STOP_R
	SubMoveNon_Init, //EV_TYPE_TRAINER_SPIN_MOVE_L
	SubMoveNon_Init, //EV_TYPE_TRAINER_SPIN_MOVE_R
	SubMoveNon_Init, //EV_TYPE_MSG
	
	SubMoveNon_Init, //EV_TYPE_TRAINER_ESCAPE
	SubMoveNon_Init, //EV_TYPE_TRAINER_SWIM_H
};

//--------------------------------------------------------------
//	�C�x���g�^�C�v�ʃX�^�[�g�`�F�b�N�֐��@EV_TYPE_NORMAL���̒l�Ɉ�v
//--------------------------------------------------------------
static int (* const DATA_FldOBJ_EventTypeStartCheckProcTbl[])( FIELD_OBJ_PTR ) =
{
	SubMoveNon_StartCheck, //EV_TYPE_NORMAL
	SubMoveNon_StartCheck, //EV_TYPE_TRAINER
	SubMoveNon_StartCheck, //EV_TYPE_TRAINER_EYEALL
	SubMoveNon_StartCheck, //EV_TYPE_ITEM
	SubMoveKyoro_StartCheck, //EV_TYPE_TRAINER_KYORO
	SubMoveSpinStop_StartCheck, //EV_TYPE_TRAINER_SPIN_STOP_L
	SubMoveSpinStop_StartCheck, //EV_TYPE_TRAINER_SPIN_STOP_R
	SubMoveNon_StartCheck, //EV_TYPE_TRAINER_SPIN_MOVE_L
	SubMoveNon_StartCheck, //EV_TYPE_TRAINER_SPIN_MOVE_R
	SubMoveNon_StartCheck, //EV_TYPE_MSG
	
	SubMoveNon_StartCheck, //EV_TYPE_TRAINER_ESCAPE
	SubMoveNon_StartCheck, //EV_TYPE_TRAINER_SWIM_H
};

//--------------------------------------------------------------
//	�C�x���g�^�C�v�ʓ���֐� EV_TYPE_NORMAL���̒l�Ɉ�v
//--------------------------------------------------------------
static int (* const DATA_FldOBJ_EventTypeMoveProcTbl[])( FIELD_OBJ_PTR ) =
{
	SubMoveNon_Move, //EV_TYPE_NORMAL
	SubMoveNon_Move, //EV_TYPE_TRAINER
	SubMoveNon_Move, //EV_TYPE_TRAINER_EYEALL
	SubMoveNon_Move, //EV_TYPE_ITEM
	SubMoveKyoro_Move, //EV_TYPE_TRAINER_KYORO
	SubMoveSpinStop_Move, //EV_TYPE_TRAINER_SPIN_STOP_L
	SubMoveSpinStop_Move, //EV_TYPE_TRAINER_SPIN_STOP_R
	SubMoveNon_Move, //EV_TYPE_TRAINER_SPIN_MOVE_L
	SubMoveNon_Move, //EV_TYPE_TRAINER_SPIN_MOVE_R
	SubMoveNon_Move, //EV_TYPE_MSG
	
	SubMoveNon_Move, //EV_TYPE_TRAINER_ESCAPE
	SubMoveNon_Move, //EV_TYPE_TRAINER_SWIM_H
};
