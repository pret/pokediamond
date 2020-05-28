//******************************************************************************
/**
 * 
 * @file	fieldobj.c
 * @brief	�t�B�[���h�I�u�W�F�N�g
 * @author	kagaya
 * @data	05.07.13
 *
 */
//******************************************************************************
#include "common.h"
#include "fieldsys.h"
#include "fieldobj.h"

#include "script.h"
#include "map_tool.h"

//==============================================================================
//	define
//==============================================================================
//--------------------------------------------------------------
//	�ł΂���
//--------------------------------------------------------------
#ifdef PM_DEBUG
//#define DEBUG_OBJID_SAM_CHECK		//��`��OBJ ID����`�F�b�N
//#define DEBUG_PRINT_FLDOBJ_COUNT	//��`��OBJ���ݐ��o��
#endif //PM_DEBUG

//--------------------------------------------------------------
///	�G�C���A�X�V���{��
//--------------------------------------------------------------
enum
{
	RET_ALIES_NOT = 0,	//�G�C���A�X�ł͂Ȃ�
	RET_ALIES_EXIST,	//�G�C���A�X�Ƃ��Ċ��ɑ��݂��Ă���
	RET_ALIES_CHANGE,	//�G�C���A�X�ύX���K�v�ł���
};

//==============================================================================
//	struct
//==============================================================================
//--------------------------------------------------------------
///	FIELD_OBJ_SYS�\����
//--------------------------------------------------------------
typedef struct _TAG_FIELD_OBJ_SYS
{
	u32 status_bit;											///<�X�e�[�^�X�r�b�g
	int fldobj_max;											///<FIELD_OBJ�ő吔
	int fldobj_count;										///<�t�B�[���hOBJ���ݐ�
	int tcb_pri;											///<TCB�v���C�I���e�B
	int blact_idx;											///<�r���{�[�h�A�N�^�[�C���f�b�N�X
	ARCHANDLE *archandle;									///<�A�[�J�C�u�n���h��
	FIELD_OBJ_BLACT_CONT blact_cont;						///<FIELD_OBJ_BLACT_CONT
	FIELD_OBJ_RENDER_CONT_PTR render_cont;					///<FIELD_OBJ_RENDER_CONT
	FIELD_OBJ_PTR fldobj_work;								///<FIELD_OBJ���[�N *
	FIELDSYS_WORK *fieldsys;								///<FIELDSYS_WORK *
}FIELD_OBJ_SYS;

#define FIELD_OBJ_SYS_SIZE (sizeof(FIELD_OBJ_SYS))			///<FIELD_OBJ_SYS�T�C�Y

//--------------------------------------------------------------
///	FIELD_OBJ�\����
//--------------------------------------------------------------
typedef struct _TAG_FIELD_OBJ
{
	u32 status_bit;											///<�X�e�[�^�X�r�b�g
	u32 move_bit;											///<����r�b�g
	u32 obj_id;												///<OBJ ID
	u32 zone_id;											///<�]�[�� ID
	u32 obj_code;											///<OBJ�R�[�h
	u32 move_code;											///<����R�[�h
	u32 event_type;											///<�C�x���g�^�C�v
	u32 event_flag;											///<�C�x���g�t���O
	u32 event_id;											///<�C�x���gID
	int dir_head;											///<FIELD_OBJ_H�w�����
	int dir_disp;											///<���݌����Ă������
	int dir_move;											///<���ݓ����Ă������
	int dir_disp_old;										///<�ߋ��̓����Ă�������
	int dir_move_old;										///<�ߋ��̓����Ă�������
	int param0;												///<�w�b�_�w��p�����^
	int param1;												///<�w�b�_�w��p�����^
	int param2;												///<�w�b�_�w��p�����^
	int move_limit_x;										///<X�����ړ�����
	int move_limit_z;										///<Z�����ړ�����
	int gx_init;											///<�����O���b�hX
	int gy_init;											///<�����O���b�hY
	int gz_init;											///<�����O���b�hZ
	int gx_old;												///<�ߋ��O���b�hX
	int gy_old;												///<�ߋ��O���b�hY
	int gz_old;												///<�ߋ��O���b�hZ
	int gx_now;												///<���݃O���b�hX
	int gy_now;												///<���݃O���b�hY
	int gz_now;												///<���݃O���b�hZ
	VecFx32 vec_pos_now;									///<���ݎ������W
	VecFx32 vec_draw_offs;									///<�\�����W�I�t�Z�b�g
	VecFx32 vec_draw_offs_outside;							///<�O���w��\�����W�I�t�Z�b�g
	VecFx32 vec_attr_offs;								///<�A�g���r���[�g�ɂ����W�I�t�Z�b�g
	u32 draw_status;										///<�`��X�e�[�^�X
	int acmd_code;											///<�A�j���[�V�����R�}���h�R�[�h
	int acmd_seq;											///<�A�j���[�V�����R�}���h�V�[�P���X
	u16 now_attr;											///<���݂̃}�b�v�A�g���r���[�g
	u16 old_attr;											///<�ߋ��̃}�b�v�A�g���r���[�g
	
	TCB_PTR tcb;											///<����֐�TCB*
	CONST_FIELD_OBJ_SYS_PTR fldobj_sys;						///<FIELD_OBJ_SYS�ւ� *
	
	FIELD_OBJ_MOVE_PROC_INIT move_init_proc;				///<�������֐�
	FIELD_OBJ_MOVE_PROC move_proc;							///<����֐�
	FIELD_OBJ_MOVE_PROC_DEL move_delete_proc;				///<�폜�֐�
	FIELD_OBJ_DRAW_PROC_INIT draw_init_proc;				///<�`�揉�����֐�
	FIELD_OBJ_DRAW_PROC draw_proc;							///<�`��֐�
	FIELD_OBJ_DRAW_PROC_DEL draw_delete_proc;				///<�`��폜�֐�
	FIELD_OBJ_DRAW_PROC_PUSH draw_push_proc;				///<�`��ޔ��֐�
	FIELD_OBJ_DRAW_PROC_POP draw_pop_proc;					///<�`�敜�A�֐�
	
	u8 move_proc_work[FLDOBJ_MOVE_WORK_SIZE];				///<����֐��p���[�N
	u8 move_sub_proc_work[FLDOBJ_MOVE_SUB_WORK_SIZE];		///<����T�u�֐��p���[�N
	u8 move_cmd_proc_work[FLDOBJ_MOVE_CMD_WORK_SIZE];		///<����R�}���h�p���[�N
	u8 draw_proc_work[FLDOBJ_DRAW_WORK_SIZE];				///<�`��֐��p���[�N
}FIELD_OBJ;

#define FIELD_OBJ_SIZE (sizeof(FIELD_OBJ))					///<FIELD_OBJ�T�C�Y

//--------------------------------------------------------------
///	FIELD_OBJ_H_LOAD_FILE�\����
//--------------------------------------------------------------
typedef struct
{
	int zone;
	int add_max;											//�o�^�ő吔
	int add_count;											//�ǉ���
	CONST_FIELD_OBJ_SYS_PTR sys;							//FIELD_OBJ_SYS_PTR 
	FIELD_OBJ_H *head;										//�w�b�_�[
}FIELD_OBJ_H_LOAD_FILE;
															///FIELD_OBJ_H_LOAD_FILE�T�C�Y
#define FIELD_OBJ_H_LOAD_FILE_SIZE (sizeof(FIELD_OBJ_H_LOAD_FILE))

//==============================================================================
//	�v���g�^�C�v
//==============================================================================
static FIELD_OBJ_SYS_PTR  FldOBJSys_AllocMemory( int max );

static void FldOBJ_SaveDataSave( FIELDSYS_WORK *fsys, FIELD_OBJ_PTR fldobj, FIELD_OBJ_SAVE_DATA_PTR save );
static void FldOBJ_SaveDataLoad( FIELD_OBJ_PTR fldobj, FIELD_OBJ_SAVE_DATA_PTR save );
static void FldOBJ_DataLoadRecover( CONST_FIELD_OBJ_SYS_PTR fos, FIELD_OBJ_PTR fldobj );
static void FldOBJ_DataLoadStatusBitRecover( FIELD_OBJ_PTR fldobj );
static void FldOBJ_DataLoadPosRecover( FIELD_OBJ_PTR fldobj );

static void FldOBJ_AddFileProc( FIELD_OBJ_H_LOAD_FILE *work );

static FIELD_OBJ_PTR  FldOBJ_SpaceSearch( CONST_FIELD_OBJ_SYS_PTR sys );
static FIELD_OBJ_PTR  FldOBJ_AliesSearch( CONST_FIELD_OBJ_SYS_PTR fos, int obj_id,int zone_id );
static void FldOBJ_MoveTcbAdd( CONST_FIELD_OBJ_SYS_PTR sys, FIELD_OBJ_PTR fldobj );
static void FldOBJ_AddHeaderSet(
		FIELD_OBJ_PTR fldobj, const FIELD_OBJ_H *head, FIELDSYS_WORK *fsys );
static void FldOBJ_AddHeaderPosInit( FIELD_OBJ_PTR fldobj, const FIELD_OBJ_H *head );
static void FldOBJ_WorkInit( FIELD_OBJ_PTR fldobj, CONST_FIELD_OBJ_SYS_PTR sys );
static void FldOBJ_WorkInit_MoveProcInit( FIELD_OBJ_PTR fldobj );
static void FldOBJ_WorkInit_DrawProcInit( FIELD_OBJ_PTR fldobj );
static void FldOBJ_WorkClear( FIELD_OBJ_PTR fldobj );
static int FldOBJ_HeaderAliesCheck(
		CONST_FIELD_OBJ_PTR fldobj, int h_zone_id, int max, const FIELD_OBJ_H *head );
static FIELD_OBJ_PTR FldOBJ_OBJIDZoneIDSearch(
		CONST_FIELD_OBJ_SYS_PTR fos, int obj_id, int zone_id );
static void FldOBJ_DeleteAll_OldZoneID( FIELD_OBJ_SYS_PTR fos, u32 zone_id );
static void FldOBJ_DrawInitStatusSet( FIELD_OBJ_PTR fldobj );
static void FldOBJ_DrawEffectFlagInit( FIELD_OBJ_PTR fldobj );
static void FldOBJ_DrawDeleteStatusSet( FIELD_OBJ_PTR fldobj );
static int FldOBJ_OBJCodeWkOBJCodeConv( FIELDSYS_WORK *fsys, int code );
static void FldOBJ_HeightNeedCheckInit( FIELD_OBJ_PTR fldobj );
static void FldOBJ_MoveWorkInit( FIELD_OBJ_PTR fldobj );
static void FldOBJ_DrawWorkInit( FIELD_OBJ_PTR fldobj );
static void FldOBJ_AliesOBJChange( FIELD_OBJ_PTR fldobj, const FIELD_OBJ_H *head, int zone_id );
static void FldOBJ_OBJAliesChange( FIELD_OBJ_PTR fldobj, int zone_id, const FIELD_OBJ_H *head );

static void FldOBJ_TCB_MoveProc( TCB_PTR tcb, void *work );
static void FldOBJ_TCB_DrawProc( FIELD_OBJ_PTR fldobj );

static FIELD_OBJ_SYS_PTR  FldOBJ_ConstSysLocalGet( CONST_FIELD_OBJ_SYS_PTR sys );
static void FldOBJSys_OBJCountInc( FIELD_OBJ_SYS_PTR sys );
static void FldOBJSys_OBJCountDec( FIELD_OBJ_SYS_PTR sys );
static void FldOBJSys_OBJCountSet( FIELD_OBJ_SYS_PTR sys, int count );
static FIELD_OBJ_PTR FldOBJSys_FieldOBJWorkGet( CONST_FIELD_OBJ_SYS_PTR sys );

static FIELD_OBJ_SYS_PTR  FldOBJ_FieldOBJSysGet( CONST_FIELD_OBJ_PTR fldobj );

static const FIELD_OBJ_H * FldOBJ_H_OBJIDSearch( int id, int max, const FIELD_OBJ_H *head );
static int FldOBJ_H_AliesCheck( const FIELD_OBJ_H *head );
static int FldOBJ_H_AliesZoneIDGet( const FIELD_OBJ_H *head );

static const FIELD_OBJ_MOVE_PROC_LIST * FldOBJ_MoveProcListGet( u32 code );
static FIELD_OBJ_MOVE_PROC_INIT FldOBJ_MoveProcList_InitGet(
		const FIELD_OBJ_MOVE_PROC_LIST *list );
static FIELD_OBJ_MOVE_PROC FldOBJ_MoveProcList_MoveGet(
		const FIELD_OBJ_MOVE_PROC_LIST *list );
static FIELD_OBJ_MOVE_PROC_DEL FldOBJ_MoveProcList_DeleteGet(
		const FIELD_OBJ_MOVE_PROC_LIST *list );
static FIELD_OBJ_DRAW_PROC_PUSH FldOBJ_DrawProcList_PushGet(
		const FIELD_OBJ_DRAW_PROC_LIST *list );
static FIELD_OBJ_DRAW_PROC_POP FldOBJ_DrawProcList_PopGet(
		const FIELD_OBJ_DRAW_PROC_LIST *list );

static FIELD_OBJ_DRAW_PROC_INIT FldOBJ_DrawProcList_InitGet(
	const FIELD_OBJ_DRAW_PROC_LIST *list );
static FIELD_OBJ_DRAW_PROC FldOBJ_DrawProcList_DrawGet( const FIELD_OBJ_DRAW_PROC_LIST *list );
static FIELD_OBJ_DRAW_PROC_DEL FldOBJ_DrawProcList_DeleteGet(
		const FIELD_OBJ_DRAW_PROC_LIST *list );
static const FIELD_OBJ_DRAW_PROC_LIST * FldOBJ_DrawProcListGet( u32 code );

//==============================================================================
//	�t�B�[���hOBJ	�V�X�e��
//==============================================================================
//--------------------------------------------------------------
/**
 * FIELD OBJ �V�X�e��������
 * @param		fsys			FIELDSYS_WORK *
 * @param		max 			��������OBJ�ő吔
 * @param		pri				�t�B�[���hOBJ�̊�{TCB�v���C�I���e�B
 * @retval		FIELD_OBJ_SYS*	�ǉ����ꂽ�t�B�[���hOBJ*
 */
//--------------------------------------------------------------
FIELD_OBJ_SYS_PTR FieldOBJSys_Init( FIELDSYS_WORK *fsys, int max, int pri )
{
	FIELD_OBJ_SYS_PTR fos;
	
	fos = FldOBJSys_AllocMemory( max );
	FieldOBJSys_FieldSysWorkSet( fos, fsys );
	FieldOBJSys_OBJMaxSet( fos, max );
	FieldOBJSys_TCBStandardPrioritySet( fos, pri );
	
//	OS_Printf( "OLD FIELD_OBJ_SAVE_DATA_SIZE %x\n", FIELD_OBJ_SAVE_DATA_OLD_SIZE );
//	OS_Printf( "NEW FIELD_OBJ_SAVE_DATA_SIZE %x\n", FIELD_OBJ_SAVE_DATA_SIZE );
	
	return( fos );
}

//--------------------------------------------------------------
/**
 * FIELD OBJ �V�X�e���폜
 * @param	fos		FIELD_OBJ_SYS_PTR 
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJSys_Delete( FIELD_OBJ_SYS_PTR fos )
{
	sys_FreeMemory( HEAPID_WORLD, FieldOBJSys_FldOBJWorkGet(fos) );
	sys_FreeMemory( HEAPID_WORLD, fos );
}

//--------------------------------------------------------------
/**
 * FIELD OBJ�@�S�Ă��폜
 * @param	fos		FIELD_OBJ_SYS_PTR 
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJSys_DeleteAll( FIELD_OBJ_SYS_PTR fos )
{
	FieldOBJ_DeleteAll( fos );
	FieldOBJSys_DrawDelete( fos );
	FieldOBJSys_Delete( fos );
	
	OS_Printf( "�t�B�[���hOBJ �S�Ă��폜���܂���\n" );
}

//--------------------------------------------------------------
/**
 * FIELD OBJ�@�]�[���X�V���̍폜����
 * @param	sys		FIELD_OBJ_SYS_PTR 
 * @param	old_zone	�Â��]�[��ID
 * @param	new_zone	�V�����]�[��ID
 * @param	head_max	head�v�f��
 * @param	head	�V�����̃]�[���ɔz�u����FIELD_OBJ_H *
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJSys_ZoneUpdateDelete( FIELD_OBJ_SYS_PTR fos,
		int old_zone, int new_zone, int head_max, const FIELD_OBJ_H *head )
{
	int ret,max = FieldOBJSys_OBJMaxGet( fos );
	FIELD_OBJ_PTR fldobj = FieldOBJSys_FldOBJWorkGet( fos );
	
	OS_Printf( "�Â�Zone�ɔz�u���ꂽ�t�B�[���hOBJ�@�폜�J�n\n" );
	
	while( max ){
		if( FieldOBJ_StatusBitCheck_Use(fldobj) == TRUE ){
			ret = FldOBJ_HeaderAliesCheck( fldobj, new_zone, head_max, head );
			
			switch( ret ){
			case RET_ALIES_NOT:
				if( FieldOBJ_ZoneIDGet(fldobj) != new_zone ){
					if( FieldOBJ_StatusBit_CheckEasy(
							fldobj,FLDOBJ_STA_BIT_ZONE_DEL_NOT) == FALSE ){
						FieldOBJ_Delete( fldobj );
					}
				}
				
				break;
			case RET_ALIES_CHANGE:
				OS_Printf(
					"�G�C���A�X�Ώۂ�OBJ���� OBJ_ID=%d ZONE_ID=%d GRID X=%d,GRID Z=%d \n",
					FieldOBJ_OBJIDGet(fldobj),
					new_zone,
					FieldOBJ_NowPosGX_Get(fldobj), FieldOBJ_NowPosGZ_Get(fldobj) );
				break;
			case RET_ALIES_EXIST:
				OS_Printf( "�G�C���A�X�Ώۂ�OBJ�����ɃG�C���A�X�����Ă��܂� " );
				OS_Printf( "OBJ_ID=%d ", FieldOBJ_OBJIDGet(fldobj) );
				OS_Printf( "ZONE_ID=%d ", FieldOBJ_ZoneIDGetAlies(fldobj) );
				OS_Printf( "�ǉ����̃]�[��ID=%d ", new_zone );
				OS_Printf( "GRID X=%d, ", FieldOBJ_NowPosGX_Get(fldobj) );
				OS_Printf( "GRID Z=%d\n", FieldOBJ_NowPosGZ_Get(fldobj) );
				break;
			}
		}
		
		fldobj++;
		max--;
	}
	
	FieldOBJ_BlActCont_ResmGuestDeleteAll( fos, FieldOBJSys_BlActContGet(fos) );
	OS_Printf( "�Â�Zone�ɔz�u���ꂽ�t�B�[���hOBJ�@�폜����\n" );
}

//==============================================================================
//	�t�B�[���hOBJ�V�X�e���@�p�[�c
//==============================================================================
//--------------------------------------------------------------
/**
 * FIELD OBJ ��Ɨ̈�m��
 * @param	max				��������OBJ�ő吔
 * @retval	FIELD_OBJ_SYS	�m�ۂ����̈�*
 */
//--------------------------------------------------------------
static FIELD_OBJ_SYS_PTR FldOBJSys_AllocMemory( int max )
{
	int size;
	FIELD_OBJ_PTR fldobj;
	FIELD_OBJ_SYS_PTR fos;
	
	fos = sys_AllocMemory( HEAPID_WORLD, FIELD_OBJ_SYS_SIZE );
	
	GF_ASSERT( fos != NULL && "fldobj sys alloc memory error" );
	memset( fos, 0, FIELD_OBJ_SYS_SIZE );
	
	size = FIELD_OBJ_SIZE * max;
	fldobj = sys_AllocMemory( HEAPID_WORLD, size );
	
	GF_ASSERT( fldobj != NULL && "fldobj alloc memory error" );
	memset( fldobj, 0, size );
	
	FieldOBJSys_FieldOBJWorkSet( fos, fldobj );
	
	return( fos );
}

//==============================================================================
//	�t�B�[���hOBJ
//==============================================================================
//--------------------------------------------------------------
/**
 * �t�B�[���hOBJ��ǉ� �����w�b�_�[
 * @param	fos			FIELD_OBJ_SYS_PTR 
 * @param	head		�ǉ��������Z�߂�FIELD_OBJ_H *
 * @param	zone_id		�]�[��ID
 * @retval	FIELD_OBJ	�ǉ����ꂽFIELD_OBJ_PTR �BNULL=�ǉ��s��
 */
//--------------------------------------------------------------
FIELD_OBJ_PTR FieldOBJ_AddH( CONST_FIELD_OBJ_SYS_PTR fos, const FIELD_OBJ_H *head, int zone_id )
{
	FIELD_OBJ_PTR fldobj;
	
	{
		int obj_id = FieldOBJ_H_IDGet( head );
		
		if( FldOBJ_H_AliesCheck(head) == FALSE ){				//�G�C���A�X�ł͂Ȃ�
			fldobj = FldOBJ_AliesSearch( fos, obj_id, zone_id );
			
			if( fldobj != NULL ){								//�G�C���A�X�Ŋ��ɑ��݂��Ă���
				FldOBJ_AliesOBJChange( fldobj, head, zone_id );	//�G�C���A�X����t�B�[���hOBJ��
				OS_Printf( "�G�C���A�X -> �t�B�[���hOBJ OBJ_ID %d ", obj_id );
				OS_Printf( "GIRD X=%d ", FieldOBJ_H_PosXGet(head) );
				OS_Printf( "GIRD Z=%d\n", FieldOBJ_H_PosZGet(head) );
				return( fldobj );
			}
		}else{													//�G�C���A�X�ł���
			fldobj = FldOBJ_OBJIDZoneIDSearch( fos, obj_id, FldOBJ_H_AliesZoneIDGet(head) );
			
			if( fldobj != NULL ){								//���Ƀt�B�[���hOBJ�����݂���
				FldOBJ_OBJAliesChange( fldobj, zone_id, head );	//�t�B�[���hOBJ����G�C���A�X��
				OS_Printf( "�t�B�[���hOBJ -> �G�C���A�X OBJ_ID %d ", obj_id );
				OS_Printf( "GIRD X=%d ", FieldOBJ_H_PosXGet(head) );
				OS_Printf( "GIRD Z=%d\n", FieldOBJ_H_PosZGet(head) );
				return( fldobj );
			}
			
			OS_Printf( "�G�C���A�X���z�u����܂� " );
			OS_Printf( "ZONE_ID %d, OBJ_ID %d ", obj_id, FldOBJ_H_AliesZoneIDGet(head) );
			OS_Printf( "GIRD X=%d ", FieldOBJ_H_PosXGet(head) );
			OS_Printf( "GIRD Z=%d\n", FieldOBJ_H_PosZGet(head) );
		}
	}
	
	fldobj = FldOBJ_SpaceSearch( fos );
	
	if( fldobj == NULL ){
		return( fldobj );
	}
	
	FldOBJ_AddHeaderSet( fldobj, head, FieldOBJSys_FieldSysWorkGet(fos) );
	FldOBJ_WorkInit( fldobj, fos );
	FieldOBJ_ZoneIDSet( fldobj, zone_id );
	
	FldOBJ_MoveWorkInit( fldobj );
	FldOBJ_DrawWorkInit( fldobj );
	
	FieldOBJ_StatusBit_ON( fldobj, FLDOBJ_STA_BIT_MOVE_START );
	
	FldOBJ_MoveTcbAdd( fos, fldobj );
	FldOBJSys_OBJCountInc( FldOBJ_ConstSysLocalGet(fos) );
	
	return( fldobj );
}

//--------------------------------------------------------------
/**
 * �t�B�[���hOBJ��ǉ��B�Œ���K�v�ȏ�񂩂�w�b�_�[�쐬���Ēǉ��B
 * ����Ȃ�����0�ŃN���A����Ă���B�K�v����Βǉ���Ɋe���Ŏ��R�ɐݒ�B
 * @param	fos			FIELD_OBJ_SYS_PTR 
 * @param	x			�����O���b�h���WX
 * @param	z			�����O���b�h���WZ
 * @param	dir			���������BDIR_UP��
 * @param	obj			OBJ�R�[�h�BHERO��
 * @param	move		����R�[�h�BMV_RND��
 * @param	zone_id		�]�[��ID ZONE_ID_NOTHING��
 * @retval	FIELD_OBJ	�ǉ����ꂽFIELD_OBJ_PTR �BNULL=�ǉ��s��
 */
//--------------------------------------------------------------
FIELD_OBJ_PTR FieldOBJ_AddHMake(
		CONST_FIELD_OBJ_SYS_PTR fos, int x, int z, int dir, int obj, int move, int zone_id )
{
	FIELD_OBJ_H head;
	FIELD_OBJ_PTR fldobj;
	
	FieldOBJ_H_IDSet( &head, 0 );
	FieldOBJ_H_OBJCodeSet( &head, obj );
	FieldOBJ_H_MoveCodeSet( &head, move );
	FieldOBJ_H_EventTypeSet( &head, 0 );
	FieldOBJ_H_EventFlagSet( &head, 0 );
	FieldOBJ_H_EventIDSet( &head, 0 );
	FieldOBJ_H_DirSet( &head, dir );
	FieldOBJ_H_ParamSet( &head, 0, FLDOBJ_PARAM_0 );
	FieldOBJ_H_ParamSet( &head, 0, FLDOBJ_PARAM_1 );
	FieldOBJ_H_ParamSet( &head, 0, FLDOBJ_PARAM_2 );
	FieldOBJ_H_MoveLimitXSet( &head, 0 );
	FieldOBJ_H_MoveLimitZSet( &head, 0 );
	FieldOBJ_H_PosXSet( &head, x );
	FieldOBJ_H_PosZSet( &head, z );
	FieldOBJ_H_PosYSet( &head, 0 );
	
	fldobj = FieldOBJ_AddH( fos, &head, zone_id );
	
	return( fldobj );
}

//--------------------------------------------------------------
/**
 * FIELD_OBJ_H�e�[�u�����w���ID��������OBJ��ǉ�
 * @param	fos		FIELD_OBJ_SYS_PTR
 * @param	id		�ǉ�����head����ID
 * @param	zone	�ǉ��̍ۂɎw�肷��]�[��ID
 * @param	max		head�v�f��
 * @param	head	FIELD_OBJ_H *
 * @retval	FIELD_OBJ_PTR	�ǉ����ꂽFIELD_OBJ_PTR NULL=id�Y������
 */
//--------------------------------------------------------------
FIELD_OBJ_PTR FieldOBJ_AddHEvent(
		CONST_FIELD_OBJ_SYS_PTR fos, int id, int max, int zone, const FIELD_OBJ_H *head )
{
	FIELD_OBJ_PTR fldobj = NULL;
	const FIELD_OBJ_H *hit_head = FldOBJ_H_OBJIDSearch( id, max, head );
	
	if( hit_head != NULL ){
		int flag = FieldOBJ_H_EventFlagGet( hit_head );
		FIELDSYS_WORK *fsys = FieldOBJSys_FieldSysWorkGet( fos );
		
		if( CheckEventFlag(fsys,flag) == FALSE ){
			fldobj = FieldOBJ_AddH( fos, hit_head, zone );
		}
	}
	
	return( fldobj );
}

//--------------------------------------------------------------
/**
 * FIELD OBJ�@�\���n�̂ݍĐݒ�@�폜�͍s��Ȃ�
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	code	OBJ�R�[�h HERO��
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_DrawResetAlone( FIELD_OBJ_PTR fldobj, int code )
{
#ifdef PM_DEBUG
	{	//�`��V�X�e���������������Ă��Ȃ�
		CONST_FIELD_OBJ_SYS_PTR fos = FieldOBJ_FieldOBJSysGet( fldobj );
		GF_ASSERT( FieldOBJSys_DrawInitCompCheck(fos) != FALSE &&
			"FieldOBJ_DrawReset() DRAW SYS NOT INIT" );
	}
#endif
	
	FieldOBJ_OBJCodeSet( fldobj, code );
	FldOBJ_DrawInitStatusSet( fldobj );
	FieldOBJ_StatusBit_OFF( fldobj, FLDOBJ_STA_BIT_DRAW_PROC_INIT_COMP );
	FldOBJ_DrawWorkInit( fldobj );
}

//--------------------------------------------------------------
/**
 * FIELD OBJ�@���݂̕`��֐����폜���čĐݒ�
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	code	OBJ�R�[�h HERO��
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_DrawReset( FIELD_OBJ_PTR fldobj, int code )
{
	if( FieldOBJ_StatusBit_DrawInitCompCheck(fldobj) == TRUE ){
		FieldOBJ_DrawDelete( fldobj );
	}
	
	FieldOBJ_DrawResetAlone( fldobj, code );
}

//--------------------------------------------------------------
/**
 * �t�B�[���hOBJ���폜
 * @param	fldobj		�폜����FIELD_OBJ_PTR 
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_Delete( FIELD_OBJ_PTR fldobj )
{
	CONST_FIELD_OBJ_SYS_PTR fos;
	
	fos = FieldOBJ_FieldOBJSysGet( fldobj );
	
	if( FieldOBJSys_DrawInitCompCheck(fos) == TRUE ){
		FieldOBJ_DrawDeleteProcCall( fldobj );
	}
	
	FieldOBJ_MoveDeleteProcCall( fldobj );
	FieldOBJ_MoveTcbDelete( fldobj );
	FldOBJSys_OBJCountDec( FldOBJ_FieldOBJSysGet(fldobj) );
	FldOBJ_WorkClear( fldobj );
}

//--------------------------------------------------------------
/**
 * �t�B�[���hOBJ���폜�@�X�N���v�g��OBJ�폜�t���O��ON�ɂ���
 * @param	fldobj		�폜����FIELD_OBJ_PTR 
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_DeleteEvent( FIELD_OBJ_PTR fldobj )
{
	int ev;
	
	ev = FieldOBJ_EventFlagGet( fldobj );
	SetEventFlag( FieldOBJ_FieldSysWorkGet(fldobj), ev );
	FieldOBJ_Delete( fldobj );
}

//--------------------------------------------------------------
/**
 * FIELD OBJ�@�\���n�̂ݍ폜
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_DrawDelete( FIELD_OBJ_PTR fldobj )
{
	CONST_FIELD_OBJ_SYS_PTR fos;
	
	fos = FieldOBJ_FieldOBJSysGet( fldobj );
	
	if( FieldOBJSys_DrawInitCompCheck(fos) == TRUE ){
		if( FieldOBJ_StatusBit_Check(fldobj,FLDOBJ_STA_BIT_DRAW_PROC_INIT_COMP) ){
			FieldOBJ_DrawDeleteProcCall( fldobj );
		}
		
		FieldOBJ_StatusBit_OFF( fldobj, FLDOBJ_STA_BIT_DRAW_PROC_INIT_COMP );
	}
	
	FieldOBJ_OBJCodeSet( fldobj, OBJCODEMAX );
	
	FieldOBJ_DrawInitProcSet( fldobj, FieldOBJ_DrawInitProcDummy );
	FieldOBJ_DrawProcSet( fldobj, FieldOBJ_DrawProcDummy );
	FieldOBJ_DrawDeleteProcSet( fldobj, FieldOBJ_DrawProcDummy );
	FieldOBJ_DrawPushProcSet( fldobj, FieldOBJ_DrawPushProcDummy );
	FieldOBJ_DrawPopProcSet( fldobj, FieldOBJ_DrawPopProcDummy );
}

//--------------------------------------------------------------
/**
 * ���ݔ������Ă���t�B�[���hOBJ��S�č폜
 * @param	fldobj		�폜����FIELD_OBJ_PTR 
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_DeleteAll( FIELD_OBJ_SYS_PTR fos )
{
	int i,max;
	FIELD_OBJ_PTR fldobj;
	
	i = 0;
	max = FieldOBJSys_OBJMaxGet( fos );
	fldobj = FieldOBJSys_FldOBJWorkGet( fos );
	
	do{
		if( FieldOBJ_StatusBit_Check(fldobj,FLDOBJ_STA_BIT_USE) ){
			FieldOBJ_Delete( fldobj );
		}
		
		fldobj++;
		i++;
	}while( i < max );
}

//--------------------------------------------------------------
/**
 * ���ݔ������Ă���t�B�[���hOBJ�S�Ă�ޔ�
 * @param	fldobj		�폜����FIELD_OBJ_PTR 
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_PushAll( FIELD_OBJ_SYS_PTR fos )
{
	int i,max;
	FIELD_OBJ_PTR fldobj;
	
	i = 0;
	max = FieldOBJSys_OBJMaxGet( fos );
	fldobj = FieldOBJSys_FldOBJWorkGet( fos );
	
	do{
		if( FieldOBJ_StatusBit_Check(fldobj,FLDOBJ_STA_BIT_USE) ){
			if( FieldOBJ_StatusBitCheck_DrawProcInitComp(fldobj) == TRUE ){
				FieldOBJ_DrawPushProcCall( fldobj );
			}
		}
		
		fldobj++;
		i++;
	}while( i < max );
}

//--------------------------------------------------------------
/**
 * ���ݔ������Ă���t�B�[���hOBJ�S�Ăɂ������ĕ`�揈���̑ޔ����s��
 * @param	fos		FIELD_OBJ_SYS_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_DrawProcPushAll( FIELD_OBJ_SYS_PTR fos )
{
	GF_ASSERT( FieldOBJSys_DrawInitCompCheck(fos) == TRUE &&
		"FLDOBJ �`�揈�������݂��Ă��Ȃ��̂�FieldOBJ_DrawProcPushAll()���Ă΂�Ă��܂�" );
	
	{
		int i,max;
		FIELD_OBJ_PTR fldobj;
	
		i = 0;
		max = FieldOBJSys_OBJMaxGet( fos );
		fldobj = FieldOBJSys_FldOBJWorkGet( fos );
	
		do{
			if( FieldOBJ_StatusBit_Check(fldobj,FLDOBJ_STA_BIT_USE) ){
				if( FieldOBJ_StatusBit_Check(fldobj,FLDOBJ_STA_BIT_DRAW_PROC_INIT_COMP) ){
					FieldOBJ_DrawPushProcCall( fldobj );
					FldOBJ_DrawDeleteStatusSet( fldobj );
				}
			}
		
			fldobj++;
			i++;
		}while( i < max );
	}
	
	OS_Printf( "�t�B�[���hOBJ �`�����ޔ����܂���\n" );
}

//--------------------------------------------------------------
/**
 * ���ݔ������Ă���t�B�[���hOBJ�S�Ă𕜋A
 * @param	fldobj		�폜����FIELD_OBJ_PTR 
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_PopAll( FIELD_OBJ_SYS_PTR fos )
{
	int i,max;
	FIELD_OBJ_PTR fldobj;
	
	i = 0;
	max = FieldOBJSys_OBJMaxGet( fos );
	fldobj = FieldOBJSys_FldOBJWorkGet( fos );
	
	do{
		if( FieldOBJ_StatusBitCheck_Use(fldobj) == TRUE ){
			if( FieldOBJ_StatusBitCheck_DrawProcInitComp(fldobj) == TRUE ){
				FieldOBJ_DrawPopProcCall( fldobj );
			}
		}
	
		fldobj++;
		i++;
	}while( i < max );
}

//--------------------------------------------------------------
/**
 * ���ݔ������Ă���t�B�[���hOBJ�S�Ăɑ΂��ĕ`�揈�����A
 * @param	fldobj		�폜����FIELD_OBJ_PTR 
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_DrawProcPopAll( FIELD_OBJ_SYS_PTR fos )
{
	GF_ASSERT( FieldOBJSys_DrawInitCompCheck(fos) == TRUE &&
		"FLDOBJ �`�揈�����������ŕ`�敜�A�������Ă΂�Ă��܂�" );
	
	{
		int i = 0;
		int max = FieldOBJSys_OBJMaxGet( fos );
		FIELD_OBJ_PTR fldobj = FieldOBJSys_FldOBJWorkGet( fos );
	
		do{
			if( FieldOBJ_StatusBitCheck_Use(fldobj) == TRUE ){
				if( FieldOBJ_StatusBitCheck_DrawProcInitComp(fldobj) == TRUE ){
					FieldOBJ_DrawPopProcCall( fldobj );
				}else{
					FldOBJ_DrawWorkInit( fldobj );
				}
				
				FldOBJ_DrawInitStatusSet( fldobj );
			}
		
			fldobj++;
			i++;
		}while( i < max );
	}
	
	OS_Printf( "�t�B�[���hOBJ �`����𕜋A���܂���\n" );
}

//==============================================================================
//	�t�B�[���hOBJ �Z�[�u
//==============================================================================
//--------------------------------------------------------------
/**
 * ���ݔ������Ă���t�B�[���hOBJ�S�Ă��Z�[�u�f�[�^�ɕۑ�
 * @param	fos		FIELD_OBJ_SYS_PTR
 * @param	save	�ۑ���FIELD_OBJ_SAVE_DATA_PTR
 * @param	max		save�̗v�f��
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJSys_DataSaveAll(
		FIELDSYS_WORK *fsys, CONST_FIELD_OBJ_SYS_PTR fos, FIELD_OBJ_SAVE_DATA_PTR save, int max )
{
	int no = 0;
	FIELD_OBJ_PTR fldobj;
	
	while( FieldOBJSys_FieldOBJSearch(fos,&fldobj,&no,FLDOBJ_STA_BIT_USE) ){
		FldOBJ_SaveDataSave( fsys, fldobj, save );
		save++; max--;
		GF_ASSERT( max > 0 && "FieldOBJSys_DataSaveAll()�ُ�" );
	}
	
	if( max ){
		memset( save, 0, max * FIELD_OBJ_SAVE_DATA_SIZE );
	}
}

//--------------------------------------------------------------
/**
 * �Z�[�u�����f�[�^�����[�h
 * @param	fos		FIELD_OBJ_SYS_PTR
 * @param	save	�ۑ������f�[�^���i�[���ꂽFIELD_OBJ_SAVE_DATA_PTR
 * @param	max		save�̗v�f��
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJSys_DataLoadAll(
		CONST_FIELD_OBJ_SYS_PTR fos, FIELD_OBJ_SAVE_DATA_PTR save, int max )
{
	int i = 0;
	FIELD_OBJ_PTR fldobj;
	
	while( max ){
		if( (save->status_bit & FLDOBJ_STA_BIT_USE) ){
			fldobj = FldOBJ_SpaceSearch( fos );
			GF_ASSERT( fldobj != NULL && "FieldOBJSys_DataLoadAll()�ُ�" );
		
			FldOBJ_SaveDataLoad( fldobj, save );
			FldOBJ_DataLoadRecover( fos, fldobj );
		}
		
		save++;
		max--;
	}
}

//--------------------------------------------------------------
/**
 * �t�B�[���hOBJ�̏����Z�[�u�f�[�^�ɃZ�b�g
 * @param	fldobj		FIELD_OBJ_PTR
 * @param	save		FIELD_OBJ_SAVE_DATA_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FldOBJ_SaveDataSave( FIELDSYS_WORK *fsys, FIELD_OBJ_PTR fldobj, FIELD_OBJ_SAVE_DATA_PTR save )
{
	save->status_bit = FieldOBJ_StatusBit_Get( fldobj );
	save->move_bit = FieldOBJ_MoveBit_Get( fldobj );
	save->obj_id = FieldOBJ_OBJIDGet( fldobj );
	save->zone_id = FieldOBJ_ZoneIDGet( fldobj );
	save->obj_code = FieldOBJ_OBJCodeGet( fldobj );
	save->move_code = FieldOBJ_MoveCodeGet( fldobj );
	save->event_type = FieldOBJ_EventTypeGet( fldobj );
	save->event_flag = FieldOBJ_EventFlagGet( fldobj );
	save->event_id = FieldOBJ_EventIDGet( fldobj );
	save->dir_head = FieldOBJ_DirHeaderGet( fldobj );
	save->dir_disp = FieldOBJ_DirDispGet( fldobj );
	save->dir_move = FieldOBJ_DirMoveGet( fldobj );
	save->param0 = FieldOBJ_ParamGet( fldobj, FLDOBJ_PARAM_0 );
	save->param1 = FieldOBJ_ParamGet( fldobj, FLDOBJ_PARAM_1 );
	save->param2 = FieldOBJ_ParamGet( fldobj, FLDOBJ_PARAM_2 );
	save->move_limit_x = FieldOBJ_MoveLimitXGet( fldobj );
	save->move_limit_z = FieldOBJ_MoveLimitZGet( fldobj );
	save->gx_init = FieldOBJ_InitPosGX_Get( fldobj );
	save->gy_init = FieldOBJ_InitPosGY_Get( fldobj );
	save->gz_init = FieldOBJ_InitPosGZ_Get( fldobj );
	save->gx_now = FieldOBJ_NowPosGX_Get( fldobj );
	save->gy_now = FieldOBJ_NowPosGY_Get( fldobj );
	save->gz_now = FieldOBJ_NowPosGZ_Get( fldobj );

	//�����̕ۑ�
#if 0
	{
		HEIGHT_TYPE flag;
		fx32 x,y,z;
		VecFx32 vec_pos;
		//�O���b�h��FX32�^�ɂ���(�O���b�h�̒��S���W)
		x = save->gx_now * 16 * FX32_ONE+(8*FX32_ONE);
		z = save->gz_now * 16 * FX32_ONE+(8*FX32_ONE);
		FieldOBJ_VecPosGet( fldobj, &vec_pos );

		y = GetHeightPack( fsys, vec_pos.y, x, z, &flag );
		
		if( flag == HEIGHT_FAIL ){
			save->fx32_y = save->gy_now * 8 * FX32_ONE;
//			OS_Printf("height_FAIL:%x\n",save->fx32_y);
		}else{
			save->fx32_y = y;
//			OS_Printf("height_SAC:%x\n",save->fx32_y);
		}
	}
#else
	{
		VecFx32 vec;
		int flag,eflag;
		
		FieldOBJTool_GridCenterPosGet( save->gx_now, save->gz_now, &vec );
		vec.y = FieldOBJ_VecPosYGet( fldobj );
		
		eflag = FieldOBJ_StatusBitCheck_HeightExpand( fldobj );
		flag = FieldOBJTool_GetHeightExpand( fsys, &vec, eflag );
		
		if( flag == FALSE ){
			#if 0
			//���ꂾ�ƍ����擾���s���A����܂Ő���Ɏ擾���Ă��������𖳎����ăO���b�h�P�ʂ���
			//�����W�ɕϊ����Ă��܂��A�΂ߓ��̒[���������ƂȂ��Ă��܂��B
			save->fx32_y = H_GRID_SIZE_FX32( save->gy_now );
			#else
			save->fx32_y = FieldOBJ_VecPosYGet( fldobj );	
			#endif
		}else{
			save->fx32_y = vec.y;
		}
	}
#endif
	
	memcpy( save->move_proc_work,
			FieldOBJ_MoveProcWorkGet(fldobj), FLDOBJ_MOVE_WORK_SIZE );
	memcpy( save->move_sub_proc_work,
			FieldOBJ_MoveSubProcWorkGet(fldobj), FLDOBJ_MOVE_SUB_WORK_SIZE );
}

//--------------------------------------------------------------
/**
 * �Z�[�u�f�[�^�̏����t�B�[���hOBJ�ɃZ�b�g
 * @param	fldobj		FIELD_OBJ_PTR
 * @param	save		FIELD_OBJ_SAVE_DATA_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FldOBJ_SaveDataLoad( FIELD_OBJ_PTR fldobj, FIELD_OBJ_SAVE_DATA_PTR save )
{
	FieldOBJ_StatusBit_Init( fldobj, save->status_bit );
	FieldOBJ_MoveBit_Init( fldobj, save->move_bit );
	FieldOBJ_OBJIDSet( fldobj,  save->obj_id );
	FieldOBJ_ZoneIDSet( fldobj, save->zone_id );
	FieldOBJ_OBJCodeSet( fldobj, save->obj_code );
	FieldOBJ_MoveCodeSet( fldobj, save->move_code );
	FieldOBJ_EventTypeSet( fldobj, save->event_type );
	FieldOBJ_EventFlagSet( fldobj, save->event_flag );
	FieldOBJ_EventIDSet( fldobj, save->event_id );
	FieldOBJ_DirHeaderSet( fldobj, save->dir_head );
	FieldOBJ_DirDispSetForce( fldobj, save->dir_disp );
	FieldOBJ_DirMoveSet( fldobj, save->dir_move );
	FieldOBJ_ParamSet( fldobj, save->param0, FLDOBJ_PARAM_0 );
	FieldOBJ_ParamSet( fldobj, save->param1, FLDOBJ_PARAM_1 );
	FieldOBJ_ParamSet( fldobj, save->param2, FLDOBJ_PARAM_2 );
	FieldOBJ_MoveLimitXSet( fldobj, save->move_limit_x );
	FieldOBJ_MoveLimitZSet( fldobj, save->move_limit_z );
	FieldOBJ_InitPosGX_Set( fldobj, save->gx_init );
	FieldOBJ_InitPosGY_Set( fldobj, save->gy_init );
	FieldOBJ_InitPosGZ_Set( fldobj, save->gz_init );
	FieldOBJ_NowPosGX_Set( fldobj, save->gx_now );
	FieldOBJ_NowPosGY_Set( fldobj, save->gy_now );
	FieldOBJ_NowPosGZ_Set( fldobj, save->gz_now );

	//�������A
	{
		VecFx32 vec = {0,0,0};
		vec.y = save->fx32_y;
		FieldOBJ_VecPosSet( fldobj, &vec );
	}
	
	memcpy( FieldOBJ_MoveProcWorkGet(fldobj),
			save->move_proc_work, FLDOBJ_MOVE_WORK_SIZE );
	memcpy( FieldOBJ_MoveSubProcWorkGet(fldobj),
			save->move_sub_proc_work, FLDOBJ_MOVE_SUB_WORK_SIZE );
}

//--------------------------------------------------------------
/**
 * �f�[�^���[�h��̕��A
 * @param	fos		FIELD_OBJ_SYS_PTR
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FldOBJ_DataLoadRecover( CONST_FIELD_OBJ_SYS_PTR fos, FIELD_OBJ_PTR fldobj )
{
	FldOBJ_DataLoadStatusBitRecover( fldobj );
	FldOBJ_DataLoadPosRecover( fldobj );
	
	FieldOBJ_FieldOBJSysSet( fldobj, fos );
	
	FldOBJ_WorkInit_MoveProcInit( fldobj );						//����֐��̏������̂�
	FieldOBJ_AcmdFree( fldobj );
	FldOBJ_DrawWorkInit( fldobj );
	
	FldOBJ_MoveTcbAdd( fos, fldobj );
	FieldOBJ_MoveReturnProcCall( fldobj );
	FldOBJSys_OBJCountInc( FldOBJ_ConstSysLocalGet(fos) );
}

//--------------------------------------------------------------
/**
 * �f�[�^���[�h��̃X�e�[�^�X�r�b�g���A
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FldOBJ_DataLoadStatusBitRecover( FIELD_OBJ_PTR fldobj )
{
	FieldOBJ_StatusBit_ON( fldobj,
			FLDOBJ_STA_BIT_USE |
//			FLDOBJ_STA_BIT_HEIGHT_GET_NEED |					//�Z�[�u���̍�����M�p����
			FLDOBJ_STA_BIT_MOVE_START );
	
	FieldOBJ_StatusBit_OFF( fldobj,
			FLDOBJ_STA_BIT_PAUSE_MOVE |
			FLDOBJ_STA_BIT_VANISH |
			FLDOBJ_STA_BIT_DRAW_PROC_INIT_COMP |
			FLDOBJ_STA_BIT_JUMP_START |
			FLDOBJ_STA_BIT_JUMP_END |
			FLDOBJ_STA_BIT_MOVE_END |
			FLDOBJ_STA_BIT_FELLOW_HIT_NON |
			FLDOBJ_STA_BIT_TALK_OFF |
			FLDOBJ_STA_BIT_DRAW_PUSH |
			FLDOBJ_STA_BIT_BLACT_ADD_PRAC |
			FLDOBJ_STA_BIT_HEIGHT_GET_OFF );
	
	FldOBJ_DrawEffectFlagInit( fldobj );
}

//--------------------------------------------------------------
/**
 * �f�[�^���[�h��̍��W���A
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FldOBJ_DataLoadPosRecover( FIELD_OBJ_PTR fldobj )
{
	int pos;
	VecFx32 vec;
	
	FieldOBJ_VecPosGet( fldobj, &vec );

//	OS_Printf("recover_y:%x\n",vec.y);
	
	pos = FieldOBJ_NowPosGX_Get( fldobj );
	vec.x = GRID_SIZE_FX32( pos ) + FLDOBJ_VEC_X_GRID_OFFS_FX32;
	FieldOBJ_OldPosGX_Set( fldobj, pos );

	pos = FieldOBJ_NowPosGY_Get( fldobj );
//	vec.y = H_GRID_SIZE_FX32( pos ) + FLDOBJ_VEC_Y_GRID_OFFS_FX32;	<<���[�h���ɒl���Z�b�g����Ă���͂�
	FieldOBJ_OldPosGY_Set( fldobj, pos );
	
	pos = FieldOBJ_NowPosGZ_Get( fldobj );
	vec.z = GRID_SIZE_FX32( pos ) + FLDOBJ_VEC_Z_GRID_OFFS_FX32;
	FieldOBJ_OldPosGZ_Set( fldobj, pos );
	
	FieldOBJ_VecPosSet( fldobj, &vec );
}

//==============================================================================
//	�t�B�[���hOBJ �����o�^
//==============================================================================
#if 0	//�p����

//--------------------------------------------------------------
///	FieldOBJ_AddFile()�Ńt�@�C�����ǂݍ��݂Ŏg�p����o�b�t�@�T�C�Y
//--------------------------------------------------------------
#define FLDOBJ_FILE_1LINE_BUF (96)

//--------------------------------------------------------------
/**
 * �t�B�[���hOBJ�@�t�@�C�����w��ɂ�镡���o�^
 * @param	sys			FIELD_OBJ_SYS_PTR 
 * @param	zone		�ǉ������]�[��ID
 * @param	name		FIELD_OBJ_H���L�q���ꂽ�t�@�C����
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_AddFile( CONST_FIELD_OBJ_SYS_PTR sys, int zone, const char *name )
{
	int i,max;
	char *file,*f_pos;
	char buf[FLDOBJ_FILE_1LINE_BUF];
	FIELD_OBJ_H *head;
	FIELD_OBJ_H_LOAD_FILE *load;
	
	if( name == NULL ){
		return;
	}
	
	file = sys_LoadFile( HEAPID_WORLD, name );
	GF_ASSERT( file != NULL && "fieldobj add file alloc error" );
	
	StrTok( file, buf, ',' );								//�o�^��
	max = AtoI( buf );
	
	OS_Printf( "fieldobj add file load %d\n", max );
	
	head = sys_AllocMemoryLo( HEAPID_WORLD, FIELD_OBJ_H_SIZE * max );
	GF_ASSERT( head != NULL && "fieldobj add file head alloc error" );
	
	f_pos = StrTok( file, buf, RETURN_CODE );				//1�s��΂�
	f_pos = StrTok( f_pos, buf, RETURN_CODE );				//�i����΂�
	
	for( i = 0; i < max; i++ ){
		f_pos = StrTok( f_pos, buf, ',' );					//ID�擾
		FieldOBJ_H_IDSet( &head[i], AtoI(buf) );
		f_pos = StrTok( f_pos, buf, RETURN_CODE );			//1�s��΂�
		
		f_pos = StrTok( f_pos, buf, ',' );					//OBJ�R�[�h�擾
		FieldOBJ_H_OBJCodeSet( &head[i], AtoI(buf) );
		f_pos = StrTok( f_pos, buf, RETURN_CODE );			//1�s��΂�
		
		f_pos = StrTok( f_pos, buf, ',' );					//����R�[�h�擾
		FieldOBJ_H_MoveCodeSet( &head[i], AtoI(buf) );
		f_pos = StrTok( f_pos, buf, RETURN_CODE );			//1�s��΂�
		
		f_pos = StrTok( f_pos, buf, ',' );					//�C�x���g�^�C�v�擾
		FieldOBJ_H_EventTypeSet( &head[i], AtoI(buf) );
		f_pos = StrTok( f_pos, buf, RETURN_CODE );			//1�s��΂�
		
		f_pos = StrTok( f_pos, buf, ',' );					//�C�x���g�t���O�擾
		FieldOBJ_H_EventFlagSet( &head[i], AtoI(buf) );
		f_pos = StrTok( f_pos, buf, RETURN_CODE );			//1�s��΂�
		
		f_pos = StrTok( f_pos, buf, ',' );					//�C�x���gID�擾
		FieldOBJ_H_EventIDSet( &head[i], AtoI(buf) );
		f_pos = StrTok( f_pos, buf, RETURN_CODE );			//1�s��΂�
		
		f_pos = StrTok( f_pos, buf, ',' );					//�����擾
		FieldOBJ_H_DirSet( &head[i], AtoI(buf) );
		f_pos = StrTok( f_pos, buf, RETURN_CODE );			//1�s��΂�
		
		f_pos = StrTok( f_pos, buf, ',' );					//�p�����^�擾
		FieldOBJ_H_ParamSet( &head[i], AtoI(buf) );
		f_pos = StrTok( f_pos, buf, RETURN_CODE );			//1�s��΂�
		
		f_pos = StrTok( f_pos, buf, ',' );					//�ړ�����X�擾
		FieldOBJ_H_MoveLimitXSet( &head[i], AtoI(buf) );
		
		f_pos = StrTok( f_pos, buf, ',' );					//�ړ�����Z�擾
		FieldOBJ_H_MoveLimitZSet( &head[i], AtoI(buf) );
		f_pos = StrTok( f_pos, buf, RETURN_CODE );			//1�s��΂�
		
		f_pos = StrTok( f_pos, buf, ',' );					//X���W�擾
		FieldOBJ_H_PosXSet( &head[i], AtoI(buf) );
		
		f_pos = StrTok( f_pos, buf, ',' );					//Z���W�擾
		FieldOBJ_H_PosZSet( &head[i], AtoI(buf) );
		f_pos = StrTok( f_pos, buf, RETURN_CODE );			//1�s��΂�
		
		f_pos = StrTok( f_pos, buf, ',' );					//Y���W�擾
		FieldOBJ_H_PosYSet( &head[i], AtoI(buf) );
		f_pos = StrTok( f_pos, buf, RETURN_CODE );			//��s��΂�
		
		f_pos = StrTok( f_pos, buf, RETURN_CODE );			//�i����΂�
	}
	
	sys_FreeMemory( HEAPID_WORLD, file );
	
	load = sys_AllocMemoryLo( HEAPID_WORLD, FIELD_OBJ_H_LOAD_FILE_SIZE );
	GF_ASSERT( load != NULL && "fieldobj add file work alloc error" );
	
	load->zone = zone;
	load->add_max = max;
	load->add_count = 0;
	load->sys = sys;
	load->head = head;
	
	FldOBJ_AddFileProc( load );
	
	OS_Printf( "fieldobj add file load OK\n" );
}
#endif

//--------------------------------------------------------------
/**
 * �t�B�[���hOBJ�@�o�C�i���w��ɂ�镡���o�^
 * @param	sys			FIELD_OBJ_SYS_PTR 
 * @param	zone		�ǉ������]�[��ID
 * @param	max			�ǉ�����ő吔
 * @param	bin			�ǉ�����FIELD_OBJ_H���z�u����Ă���o�C�i��*
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_AddBin( CONST_FIELD_OBJ_SYS_PTR sys, int zone, int max, const FIELD_OBJ_H *bin )
{
	int size;
	FIELD_OBJ_H *head;
	FIELD_OBJ_H_LOAD_FILE *load;
	
	OS_Printf( "�t�B�[���hOBJ �ꊇ�o�^�J�n �z�u�� %d\n", max );
	GF_ASSERT( max && "FieldOBJ_AddBin()�@�w��ő吔�ُ�" );
	
	size = FIELD_OBJ_H_SIZE *max;
	head = sys_AllocMemoryLo( HEAPID_WORLD, size );
	GF_ASSERT( head != NULL && "fieldobj add bin head alloc error" );
	memcpy( head, bin, size );
	
	load = sys_AllocMemoryLo( HEAPID_WORLD, FIELD_OBJ_H_LOAD_FILE_SIZE );
	GF_ASSERT( load != NULL && "fieldobj add file work alloc error" );
	
	load->zone = zone;
	load->add_max = max;
	load->add_count = 0;
	load->sys = sys;
	load->head = head;
	
	FldOBJ_AddFileProc( load );
	
	OS_Printf( "�t�B�[���hOBJ �ꊇ�o�^�I��\n" );
}

//--------------------------------------------------------------
/**
 * �t�B�[���hOBJ�ꊇ�o�^
 * @param	work	FIELD_OBJ_H_LOAD_FILE
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FldOBJ_AddFileProc( FIELD_OBJ_H_LOAD_FILE *work )
{
	FIELD_OBJ_PTR fldobj;
	FIELDSYS_WORK *fsys;
	const FIELD_OBJ_H *head;
	
	fsys = FieldOBJSys_FieldSysWorkGet( work->sys );
	head = work->head;
	
	do{
		if( FldOBJ_H_AliesCheck(head) == TRUE ||
			CheckEventFlag(fsys,head->event_flag) == FALSE ){
			fldobj = FieldOBJ_AddH( work->sys, head, work->zone );
			GF_ASSERT( fldobj != NULL && "�t�B�[���hOBJ�̈ꊇ�o�^�Ɏ��s���܂���\n" );
		}
#ifdef PM_DEBUG
		else{
			OS_Printf( "�t�B�[���hOBJ�ꊇ�o�^���c�C�x���g�t���O��FALSE�ׁ̈A" );
			OS_Printf( "OBJ ID=%d,",FieldOBJ_H_IDGet(head) );
			OS_Printf( "GIRD X=%d,",FieldOBJ_H_PosXGet(head) );
			OS_Printf( "GIRD Z=%d",FieldOBJ_H_PosZGet(head) );
			OS_Printf( "�ɔz�u����OBJ�̒ǉ��𖳎����܂���\n" );
		}
#endif
		head++;
		work->add_count++;
	}while( work->add_count < work->add_max );
	
	sys_FreeMemory( HEAPID_WORLD, work->head );
	sys_FreeMemory( HEAPID_WORLD, work );
}

#if 0	//���Ł@�G�C���A�X�ł̃o�O����
static void FldOBJ_AddFileProc( FIELD_OBJ_H_LOAD_FILE *work )
{
	FIELD_OBJ_PTR fldobj;
	FIELDSYS_WORK *fsys;
	const FIELD_OBJ_H *head;
	
	fsys = FieldOBJSys_FieldSysWorkGet( work->sys );
	head = work->head;
	
	do{
		if( CheckEventFlag(fsys,head->event_flag) == FALSE ){
			fldobj = FieldOBJ_AddH( work->sys, head, work->zone );
			GF_ASSERT( fldobj != NULL && "�t�B�[���hOBJ�̈ꊇ�o�^�Ɏ��s���܂���\n" );
		}else{
			OS_Printf( "�t�B�[���hOBJ�ꊇ�o�^���c�C�x���g�t���O��FALSE�ׁ̈A" );
			OS_Printf( "OBJ ID=%d,",FieldOBJ_H_IDGet(head) );
			OS_Printf( "GIRD X=%d,",FieldOBJ_H_PosXGet(head) );
			OS_Printf( "GIRD Z=%d",FieldOBJ_H_PosZGet(head) );
			OS_Printf( "�ɔz�u����OBJ�̒ǉ��𖳎����܂���\n" );
		}
	
		head++;
		work->add_count++;
	}while( work->add_count < work->add_max );
	
	sys_FreeMemory( HEAPID_WORLD, work->head );
	sys_FreeMemory( HEAPID_WORLD, work );
}
#endif

//==============================================================================
//	�t�B�[���hOBJ�@�p�[�c
//==============================================================================
//--------------------------------------------------------------
/**
 * �t�B�[���hOBJ�̋󂫂�T��
 * @param	sys			FIELD_OBJ_SYS_PTR 
 * @retval	FIELD_OBJ	�󂫂�FIELD_OBJ*�@�󂫂������ꍇ��NULL
 */
//--------------------------------------------------------------
static FIELD_OBJ_PTR  FldOBJ_SpaceSearch( CONST_FIELD_OBJ_SYS_PTR sys )
{
	int i,max;
	FIELD_OBJ_PTR fldobj;
	
	i = 0;
	max = FieldOBJSys_OBJMaxGet( sys );
	fldobj = FieldOBJSys_FldOBJWorkGet( sys );
	
	do{
		if( FieldOBJ_StatusBit_Check(fldobj,FLDOBJ_STA_BIT_USE) == 0 ){
			return( fldobj );
		}
		
		fldobj++;
		i++;
	}while( i < max );
	
	return( NULL );
}

//--------------------------------------------------------------
/**
 * �t�B�[���hOBJ�@�G�C���A�X��T��
 * @param	fos			FIELD_OBJ_SYS_PTR
 * @param	obj_id		��v����OBJ ID
 * @param	zone_id		��v����ZONE ID
 * @retval	FIELD_OBJ	��v����FIELD_OBJ*�@��v����=NULL
 */
//--------------------------------------------------------------
static FIELD_OBJ_PTR FldOBJ_AliesSearch( CONST_FIELD_OBJ_SYS_PTR fos, int obj_id, int zone_id )
{
	int no = 0;
	FIELD_OBJ_PTR fldobj;
	
	while( FieldOBJSys_FieldOBJSearch(fos,&fldobj,&no,FLDOBJ_STA_BIT_USE) == TRUE ){
		if( FieldOBJ_StatusBitCheck_Alies(fldobj) == TRUE ){
			if( FieldOBJ_OBJIDGet(fldobj) == obj_id ){
				if( FieldOBJ_ZoneIDGetAlies(fldobj) == zone_id ){
					return( fldobj );
				}
			}
		}
	}
	
	return( NULL );
}

//--------------------------------------------------------------
/**
 * �t�B�[���hOBJ�@TCB����֐��ǉ�
 * @param	sys		FIELD_OBJ_SYS*
 * @param	fldobj	FIELD_OBJ*
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FldOBJ_MoveTcbAdd( CONST_FIELD_OBJ_SYS_PTR sys, FIELD_OBJ_PTR fldobj )
{
	int pri,code;
	TCB_PTR tcb;
	
	pri = FieldOBJSys_TCBStandardPriorityGet( sys );
	code = FieldOBJ_MoveCodeGet( fldobj );
	
	if( code == MV_PAIR || code == MV_TR_PAIR ){
		pri += FLDOBJ_TCBPRI_OFFS_AFTER;
	}
	
	tcb = TCB_Add( FldOBJ_TCB_MoveProc, fldobj, pri );
	GF_ASSERT( tcb != NULL && "fldobj tcb not add error" );
	
	FieldOBJ_MoveTcbPtrSet( fldobj, tcb );
}

//--------------------------------------------------------------
/**
 * �t�B�[���hOBJ�@�w�b�_�[��񔽉f
 * @param	fldobj		�ݒ肷��FIELD_OBJ_PTR 
 * @param	head		���f�������Z�߂�FIELD_OBJ_H *
 * @param	fsys		FIELDSYS_WORK *
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FldOBJ_AddHeaderSet(
		FIELD_OBJ_PTR fldobj, const FIELD_OBJ_H *head, FIELDSYS_WORK *fsys )
{
	FieldOBJ_OBJIDSet( fldobj, FieldOBJ_H_IDGet(head) );
	FieldOBJ_OBJCodeSet( fldobj,FldOBJ_OBJCodeWkOBJCodeConv(fsys,FieldOBJ_H_OBJCodeGet(head)) );
	FieldOBJ_MoveCodeSet( fldobj, FieldOBJ_H_MoveCodeGet(head) );
	FieldOBJ_EventTypeSet( fldobj, FieldOBJ_H_EventTypeGet(head) );
	FieldOBJ_EventFlagSet( fldobj, FieldOBJ_H_EventFlagGet(head) );
	FieldOBJ_EventIDSet( fldobj, FieldOBJ_H_EventIDGet(head) );
	FieldOBJ_DirHeaderSet( fldobj, FieldOBJ_H_DirGet(head) );
	FieldOBJ_ParamSet( fldobj, FieldOBJ_H_ParamGet(head,FLDOBJ_PARAM_0), FLDOBJ_PARAM_0 );
	FieldOBJ_ParamSet( fldobj, FieldOBJ_H_ParamGet(head,FLDOBJ_PARAM_1), FLDOBJ_PARAM_1 );
	FieldOBJ_ParamSet( fldobj, FieldOBJ_H_ParamGet(head,FLDOBJ_PARAM_2), FLDOBJ_PARAM_2 );
	FieldOBJ_MoveLimitXSet( fldobj, FieldOBJ_H_MoveLimitXGet(head) );
	FieldOBJ_MoveLimitZSet( fldobj, FieldOBJ_H_MoveLimitZGet(head) );
	
	FldOBJ_AddHeaderPosInit( fldobj, head );
}

//--------------------------------------------------------------
/**
 * �t�B�[���hOBJ�@���W�n������
 * @param	fldobj		FIELD_OBJ_PTR 
 * @param	head		���f�������Z�߂�FIELD_OBJ_H *
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FldOBJ_AddHeaderPosInit( FIELD_OBJ_PTR fldobj, const FIELD_OBJ_H *head )
{
	int pos;
	VecFx32 vec;
	
	pos = FieldOBJ_H_PosXGet( head );
	vec.x = GRID_SIZE_FX32( pos ) + FLDOBJ_VEC_X_GRID_OFFS_FX32;
	FieldOBJ_InitPosGX_Set( fldobj, pos );
	FieldOBJ_OldPosGX_Set( fldobj, pos );
	FieldOBJ_NowPosGX_Set( fldobj, pos );
	
	pos = FieldOBJ_H_PosYGet( head );							//pos�ݒ��fx32�^�ŗ���B
	vec.y = (fx32)pos;
	pos = SIZE_H_GRID_FX32( pos );
	FieldOBJ_InitPosGY_Set( fldobj, pos );
	FieldOBJ_OldPosGY_Set( fldobj, pos );
	FieldOBJ_NowPosGY_Set( fldobj, pos );
	
	pos = FieldOBJ_H_PosZGet( head );
	vec.z = GRID_SIZE_FX32( pos ) + FLDOBJ_VEC_Z_GRID_OFFS_FX32;
	FieldOBJ_InitPosGZ_Set( fldobj, pos );
	FieldOBJ_OldPosGZ_Set( fldobj, pos );
	FieldOBJ_NowPosGZ_Set( fldobj, pos );
	
	FieldOBJ_VecPosSet( fldobj, &vec );
}

//--------------------------------------------------------------
/**
 * �t�B�[���hOBJ�@���[�N������
 * @param	fldobj		FIELD_OBJ_PTR 
 * @param	sys			FIELD_OBJ_SYS_PTR 
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FldOBJ_WorkInit( FIELD_OBJ_PTR fldobj, CONST_FIELD_OBJ_SYS_PTR sys )
{
	FieldOBJ_StatusBit_ON( fldobj,
			FLDOBJ_STA_BIT_USE |							//�g�p��
			FLDOBJ_STA_BIT_HEIGHT_GET_ERROR |				//�����擾���K�v�ł���
			FLDOBJ_STA_BIT_ATTR_GET_ERROR );				//�A�g���r���[�g�擾���K�v�ł���
	
	if( FieldOBJ_EventIDAliesCheck(fldobj) == TRUE ){
		FieldOBJ_StatusBitSet_Alies( fldobj, TRUE );
	}
	
	FieldOBJ_FieldOBJSysSet( fldobj, sys );
	FieldOBJ_DirDispSetForce( fldobj, FieldOBJ_DirHeaderGet(fldobj) );
	FieldOBJ_DirMoveSet( fldobj, FieldOBJ_DirHeaderGet(fldobj) );
	FieldOBJ_AcmdFree( fldobj );
}

//--------------------------------------------------------------
/**
 * �t�B�[���hOBJ ����֐�������
 * @param	fldobj		FIELD_OBJ_PTR 
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FldOBJ_WorkInit_MoveProcInit( FIELD_OBJ_PTR fldobj )
{
	const FIELD_OBJ_MOVE_PROC_LIST *list;
	
	list = FldOBJ_MoveProcListGet( FieldOBJ_MoveCodeGet(fldobj) );
	FieldOBJ_MoveInitProcSet( fldobj, FldOBJ_MoveProcList_InitGet(list) );
	FieldOBJ_MoveProcSet( fldobj, FldOBJ_MoveProcList_MoveGet(list) );
	FieldOBJ_MoveDeleteProcSet( fldobj, FldOBJ_MoveProcList_DeleteGet(list) );
}

//--------------------------------------------------------------
/**
 * �t�B�[���hOBJ �`��֐�������
 * @param	fldobj		FIELD_OBJ_PTR 
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FldOBJ_WorkInit_DrawProcInit( FIELD_OBJ_PTR fldobj )
{
	const FIELD_OBJ_DRAW_PROC_LIST *list;
	u32 code = FieldOBJ_OBJCodeGet( fldobj );
	
	if( code == NONDRAW ){
		list = &DATA_FieldOBJDraw_Non;
	}else{
		list = FldOBJ_DrawProcListGet( code );
	}
	
	FieldOBJ_DrawInitProcSet( fldobj, FldOBJ_DrawProcList_InitGet(list) );
	FieldOBJ_DrawProcSet( fldobj, FldOBJ_DrawProcList_DrawGet(list) );
	FieldOBJ_DrawDeleteProcSet( fldobj, FldOBJ_DrawProcList_DeleteGet(list) );
	FieldOBJ_DrawPushProcSet( fldobj, FldOBJ_DrawProcList_PushGet(list) );
	FieldOBJ_DrawPopProcSet( fldobj, FldOBJ_DrawProcList_PopGet(list) );
}

//--------------------------------------------------------------
/**
 * ���[�N����
 * @param	fldobj	FIELD_OBJ_PTR 
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FldOBJ_WorkClear( FIELD_OBJ_PTR fldobj )
{
	memset( fldobj, 0, FIELD_OBJ_SIZE );
}

//--------------------------------------------------------------
/**
 * �w�肳�ꂽ�t�B�[���hOBJ���G�C���A�X�w�肩�ǂ����`�F�b�N
 * @param	fldobj		FIELD_OBJ_PTR
 * @param	h_zone_id	head��ǂݍ��ރ]�[��ID
 * @param	max			head�v�f��
 * @param	head		FIELD_OBJ_H
 * @retval	int			RET_ALIES_NOT��
 */
//--------------------------------------------------------------
static int FldOBJ_HeaderAliesCheck(
		CONST_FIELD_OBJ_PTR fldobj, int h_zone_id, int max, const FIELD_OBJ_H *head )
{
	int obj_id;
	int zone_id;
	
	while( max ){
		obj_id = FieldOBJ_H_IDGet( head );
		
		if( FieldOBJ_OBJIDGet(fldobj) == obj_id ){					//ID��v
			if( FldOBJ_H_AliesCheck(head) == TRUE ){				//�G�C���A�X�w�b�_�[
				zone_id = FldOBJ_H_AliesZoneIDGet( head );			//�G�C���A�X�̐��K�]�[��ID
				
				if( FieldOBJ_StatusBitCheck_Alies(fldobj) == TRUE ){	//�ΏۃG�C���A�X
					if( FieldOBJ_ZoneIDGetAlies(fldobj) == zone_id ){
						return( RET_ALIES_EXIST );						//Alies�Ƃ��Ċ��ɑ���
					}
				}else if( FieldOBJ_ZoneIDGet(fldobj) == zone_id ){
					return( RET_ALIES_CHANGE );							//Alies�Ώۂł���
				}
			}else{														//�ʏ�w�b�_�[
				if( FieldOBJ_StatusBitCheck_Alies(fldobj) == TRUE ){
					if( FieldOBJ_ZoneIDGetAlies(fldobj) == h_zone_id ){	//�����G�C���A�X�ƈ�v
						return( RET_ALIES_CHANGE );
					}
				}
			}
		}
		
		max--;
		head++;
	}
	
	return( RET_ALIES_NOT );
}

//--------------------------------------------------------------
/**
 * �w�肳�ꂽ�]�[��ID��OBJ ID������FIELD_OBJ_PTR���擾�B
 * @param	fos		FIELD_OBJ_SYS_PTR
 * @param	obj_id	OBJ ID
 * @param	zone_id	�]�[��ID
 * @retval	FIELD_OBJ_PTR FIELD_OBJ_PTR
 */
//--------------------------------------------------------------
static FIELD_OBJ_PTR FldOBJ_OBJIDZoneIDSearch(
		CONST_FIELD_OBJ_SYS_PTR fos, int obj_id, int zone_id )
{
	int no = 0;
	FIELD_OBJ_PTR fldobj;
	
	while( FieldOBJSys_FieldOBJSearch(fos,&fldobj,&no,FLDOBJ_STA_BIT_USE) == TRUE ){
		if( FieldOBJ_OBJIDGet(fldobj) == obj_id && FieldOBJ_ZoneIDGet(fldobj) == zone_id ){
			return( fldobj );
		}
	}
	
	return( NULL );
}

//--------------------------------------------------------------
/**
 * �w�肳�ꂽ�]�[��ID�������̈ȊO��S�č폜
 * @param	fos			FIELD_OBJ_SYS_PTR
 * @param	zone_id		�폜���Ȃ��]�[��ID
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FldOBJ_DeleteAll_OldZoneID( FIELD_OBJ_SYS_PTR fos, u32 zone_id )
{
	u32 ret;
	int max = FieldOBJSys_OBJMaxGet( fos );
	FIELD_OBJ_PTR fldobj = FieldOBJSys_FldOBJWorkGet( fos );
	
	do{
		if( FieldOBJ_StatusBitCheck_Use(fldobj) == TRUE ){
			if( FieldOBJ_ZoneIDGet(fldobj) != zone_id ){
				if( FieldOBJ_StatusBit_CheckEasy(fldobj,FLDOBJ_STA_BIT_ZONE_DEL_NOT) == FALSE ){
					FieldOBJ_Delete( fldobj );
				}
			}
		}
		
		fldobj++;
		max--;
	}while( max );
}

//--------------------------------------------------------------
/**
 * OBJ ID�Ɉ�v����FIELD_OBJ_PTR������
 * @param	fos		FIELD_OBJ_SYS_PTR
 * @param	id		��������OBJ ID
 * @retval	FIELD_OBJ_PTR	NULL=���݂��Ȃ�
 */
//--------------------------------------------------------------
FIELD_OBJ_PTR FieldOBJSys_OBJIDSearch( CONST_FIELD_OBJ_SYS_PTR fos, int id )
{
	int max;
	FIELD_OBJ_PTR fldobj;
	
	GF_ASSERT( fos != NULL && "FieldOBJSys_OBJIDSearch() NULL�w��ł�" );
	
	max = FieldOBJSys_OBJMaxGet( fos );
	fldobj = FldOBJSys_FieldOBJWorkGet( fos );
	
	do{
		if( FieldOBJ_StatusBit_CheckEasy(fldobj,FLDOBJ_STA_BIT_USE) == TRUE ){
			if( FieldOBJ_StatusBitCheck_Alies(fldobj) == FALSE ){
				if( FieldOBJ_OBJIDGet(fldobj) == id ){
					return( fldobj );
				}
			}
		}
		
		fldobj++;
		max--;
	}while( max > 0 );
	
	return( NULL );
}

//--------------------------------------------------------------
/**
 * ����R�[�h�Ɉ�v����FIELD_OBJ_PTR������
 * @param	fos		FIELD_OBJ_SYS_PTR
 * @param	mv_code		�������铮��R�[�h
 * @retval	FIELD_OBJ_PTR	NULL=���݂��Ȃ�
 */
//--------------------------------------------------------------
FIELD_OBJ_PTR FieldOBJSys_MoveCodeSearch( CONST_FIELD_OBJ_SYS_PTR fos, int mv_code )
{
	int max;
	FIELD_OBJ_PTR fldobj;
	
	max = FieldOBJSys_OBJMaxGet( fos );
	fldobj = FldOBJSys_FieldOBJWorkGet( fos );
	
	do{
		if( FieldOBJ_StatusBit_CheckEasy(fldobj,FLDOBJ_STA_BIT_USE) == TRUE ){
			if( FieldOBJ_MoveCodeGet(fldobj) == mv_code ){
				return( fldobj );
			}
		}
		
		fldobj++;
		max--;
	}while( max > 0 );
	
	return( NULL );
}

FIELD_OBJ_PTR FieldOBJSys_OBJIDMoveCodeSearch( CONST_FIELD_OBJ_SYS_PTR fos, int o, int m )
{
	return( NULL );
}

//--------------------------------------------------------------
/**
 * �t�B�[���hOBJ���[�N����
 * @param	fos			FIELD_OBJ_SYS_PTR
 * @param	fldobj		�Y������FIELD_OBJ_PTR�i�[��
 * @param	no			�����J�n���[�Nno�B���̊֐�����߂�ہA�����ʒu+1�̒l�ɂȂ�
 * @param	check_bit	���������X�e�[�^�X�r�b�g�BFLDOBJ_STA_BIT_USE��
 * @retval	int			TRUE=��v���� FALSE=��v�Ȃ�
 */
//--------------------------------------------------------------
int FieldOBJSys_FieldOBJSearch(
	CONST_FIELD_OBJ_SYS_PTR fos, FIELD_OBJ_PTR *fldobj, int *no, u32 check_bit )
{
	int max;
	FIELD_OBJ_PTR check_obj;
	
	max = FieldOBJSys_OBJMaxGet( fos );
	
	if( (*no) >= max ){
		return( FALSE );
	}
	
	check_obj = FldOBJSys_FieldOBJWorkGet( fos );
	check_obj = &check_obj[(*no)];
	
	do{
		(*no)++;
		
		if( FieldOBJ_StatusBit_Check(check_obj,check_bit) == check_bit ){
			*fldobj = check_obj;
			return( TRUE );
		}
		
		check_obj++;
	}while( (*no) < max );
	
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * �t�B�[���hOBJ�`�揉�����ɍs������
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FldOBJ_DrawInitStatusSet( FIELD_OBJ_PTR fldobj )
{
	FieldOBJ_StatusBit_ON( fldobj, FLDOBJ_STA_BIT_MOVE_START );
	FldOBJ_DrawEffectFlagInit( fldobj );
}

//--------------------------------------------------------------
/**
 * �t�B�[���hOBJ�֘A�G�t�F�N�g�̃t���O�������B
 * �G�t�F�N�g�֘A�̃t���O���������܂Ƃ߂�
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FldOBJ_DrawEffectFlagInit( FIELD_OBJ_PTR fldobj )
{
	FieldOBJ_StatusBit_OFF( fldobj,
		FLDOBJ_STA_BIT_SHADOW_SET		|
		FLDOBJ_STA_BIT_SHADOW_VANISH	|
		FLDOBJ_STA_BIT_EFFSET_SHOAL		|
		FLDOBJ_STA_BIT_REFLECT_SET );
}

//--------------------------------------------------------------
/**
 * �t�B�[���hOBJ�`��폜���ɍs������
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FldOBJ_DrawDeleteStatusSet( FIELD_OBJ_PTR fldobj )
{
}

//--------------------------------------------------------------
/**
 * �w�肳�ꂽOBJ�R�[�h�����[�N�Q�ƌ^�Ȃ�΃��[�N��OBJ�R�[�h�ɕύX�B
 * �Ⴄ�ꍇ�͂��̂܂܂ŕԂ��B
 * @param	fsys	FIELDSYS_WORK *
 * @param	code	OBJ�R�[�h�BHERO��
 * @retval	int		�`�F�b�N���ꂽOBJ�R�[�h
 */
//--------------------------------------------------------------
static int FldOBJ_OBJCodeWkOBJCodeConv( FIELDSYS_WORK *fsys, int code )
{
	if( code >= WKOBJCODE_ORG && code <= WKOBJCODE_END ){
		code -= WKOBJCODE_ORG;
		code = GetEvDefineObjCode( fsys, code );
	}
	
	return( code );
}

//--------------------------------------------------------------
/**
 * ���ݔ������Ă���t�B�[���hOBJ��OBJ�R�[�h���Q��
 * @param	fldobj		FIELD_OBJ_PTR 
 * @param	code		�`�F�b�N����R�[�h�BHERO��
 * @retval	int			TRUE=fldobj�ȊO�ɂ�code�������Ă���z������
 */
//--------------------------------------------------------------
int FieldOBJ_OBJCodeUseSearch( CONST_FIELD_OBJ_PTR fldobj, int code )
{
	CONST_FIELD_OBJ_SYS_PTR fos = FieldOBJ_FieldOBJSysGet( fldobj );
	int check_code,i = FieldOBJSys_OBJMaxGet( fos );
	CONST_FIELD_OBJ_PTR fieldobj = FieldOBJSys_FieldOBJWorkGet( fos );
	
	do{
		if( fieldobj != fldobj ){
			if( FieldOBJ_StatusBitCheck_Use(fieldobj) == TRUE ){
				check_code = FieldOBJ_OBJCodeGet( fieldobj );
					
				if( FieldOBJ_OBJCodeSeedCheck(check_code) == TRUE ){
					check_code = FieldOBJ_OBJCodeSeedGet( fieldobj );
				}
				
				if( check_code != OBJCODEMAX && check_code == code ){
					return( TRUE );
				}
			}
		}
		
		FieldOBJSys_FieldOBJWorkInc( &fieldobj );
		i--;
	}while( i );
	
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * ���������� FLDOBJ_STA_BIT_HEIGHT_GET_ERROR��OFF�̏ꍇ�͏��������Ȃ�
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FldOBJ_HeightNeedCheckInit( FIELD_OBJ_PTR fldobj )
{
	if( FieldOBJ_StatusBit_Check(fldobj,FLDOBJ_STA_BIT_HEIGHT_GET_ERROR) ){
		FieldOBJ_VecPosNowHeightGetSet( fldobj );
	}
}

//--------------------------------------------------------------
/**
 * ���쏉�����ɍs�������Z��
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FldOBJ_MoveWorkInit( FIELD_OBJ_PTR fldobj )
{
	FldOBJ_WorkInit_MoveProcInit( fldobj );
	FieldOBJ_MoveInit( fldobj );
}

//--------------------------------------------------------------
/**
 * �`�揉�����ɍs�������Z��
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FldOBJ_DrawWorkInit( FIELD_OBJ_PTR fldobj )
{
	CONST_FIELD_OBJ_SYS_PTR fos = FieldOBJ_FieldOBJSysGet( fldobj );
	
	if( FieldOBJSys_DrawInitCompCheck(fos) == FALSE ){		//�`��V�X�e���������������Ă��Ȃ�
		return;
	}
	
	FldOBJ_HeightNeedCheckInit( fldobj );
	FieldOBJ_DrawStatusSet( fldobj, 0 );
	FieldOBJ_BlActAddPracFlagSet( fldobj, FALSE );
	
	if( FieldOBJ_StatusBitCheck_DrawProcInitComp(fldobj) == FALSE ){
		FldOBJ_WorkInit_DrawProcInit( fldobj );
		FieldOBJ_DrawInitProcCall( fldobj );
		FieldOBJ_StatusBitON_DrawProcInitComp( fldobj );
	}
}

//--------------------------------------------------------------
/**
 * �C�x���gID���G�C���A�X���ǂ����`�F�b�N
 * @param	fldobj		FIELD_OBJ_PTR 
 * @retval	int			TRUE=�G�C���A�XID�ł��� FALSE=�Ⴄ
 */
//--------------------------------------------------------------
int FieldOBJ_EventIDAliesCheck( CONST_FIELD_OBJ_PTR fldobj )
{
	u16 id = (u16)FieldOBJ_EventIDGet( fldobj );
	
	if( id == SP_SCRID_ALIES ){
		return( TRUE );
	}
	
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * �t�B�[���hOBJ�@�G�C���A�X���琳�KOBJ�ւ̕ύX
 * @param	fldobj		FIELD_OBJ_PTR 
 * @param	head		�Ώۂ�FIELD_OBJ_H
 * @param	zone_id		���K�̃]�[��ID
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FldOBJ_AliesOBJChange( FIELD_OBJ_PTR fldobj, const FIELD_OBJ_H *head, int zone_id )
{
	GF_ASSERT( FieldOBJ_StatusBitCheck_Alies(fldobj) == TRUE &&
			"FldOBJ_AliesOBJChange()alies�ł͂Ȃ�" );
	
	FieldOBJ_StatusBitSet_Alies( fldobj, FALSE );
	FieldOBJ_ZoneIDSet( fldobj, zone_id );
	FieldOBJ_EventIDSet( fldobj, FieldOBJ_H_EventIDGet(head) );
	FieldOBJ_EventFlagSet( fldobj, FieldOBJ_H_EventFlagGet(head) );
}	

//--------------------------------------------------------------
/**
 * �t�B�[���hOBJ�@���KOBJ����G�C���A�X�ւ̕ύX
 * @param	fldobj		FIELD_OBJ_PTR 
 * @param	head		�Ώۂ�FIELD_OBJ_H
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FldOBJ_OBJAliesChange( FIELD_OBJ_PTR fldobj, int zone_id, const FIELD_OBJ_H *head )
{
	GF_ASSERT( FldOBJ_H_AliesCheck(head) == TRUE && "FldOBJ_OBJAliesChange()alies�ł͂Ȃ�" );
	
	FieldOBJ_StatusBitSet_Alies( fldobj, TRUE );
	FieldOBJ_EventIDSet( fldobj, FieldOBJ_H_EventIDGet(head) );
	FieldOBJ_EventFlagSet( fldobj, FldOBJ_H_AliesZoneIDGet(head) );
	FieldOBJ_ZoneIDSet( fldobj, zone_id );
}

//--------------------------------------------------------------
/**
 * FIELD_OBJ_PTR��TCB�X�^���_�[�h�v���C�I���e�B�𒲐����Ď擾
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	offset	�X�^���_�[�h�v���C�I���e�B�ɉ��Z����l
 * @retval	int		���߂��ꂽ�v���C�I���e�B
 */
//--------------------------------------------------------------
int FieldOBJ_TCBPriGet( CONST_FIELD_OBJ_PTR fldobj, int offset )
{
	int pri;
	
	pri = FieldOBJ_TCBStandardPriorityGet( fldobj );
	pri += offset;
	
	return( pri );
}

//--------------------------------------------------------------
/**
 * �t�B�[���hOBJ�̓���`�F�b�N�B
 * ���S�A����ւ�肪�������Ă��邩�`�F�b�N����B
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	obj_id	����Ƃ݂Ȃ�OBJ ID
 * @param	zone_id	����Ƃ݂Ȃ�ZONE ID
 * @retval	int		TRUE=����BFALSE=����ł͂Ȃ�
 */
//--------------------------------------------------------------
int FieldOBJ_CheckSameID( CONST_FIELD_OBJ_PTR fldobj, int obj_id, int zone_id )
{
	if( FieldOBJ_StatusBit_CheckEasy(fldobj,FLDOBJ_STA_BIT_USE) == FALSE ){
		return( FALSE );
	}
	
	if( FieldOBJ_OBJIDGet(fldobj) != obj_id ){
		return( FALSE );
	}
	
	if( FieldOBJ_ZoneIDGet(fldobj) != zone_id ){
		if( FieldOBJ_StatusBitCheck_Alies(fldobj) == FALSE ){
			return( FALSE );
		}
		
		if( FieldOBJ_ZoneIDGetAlies(fldobj) != zone_id ){
			return( FALSE );
		}
	}
	
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * �t�B�[���hOBJ�̓���`�F�b�N�BOBJ�R�[�h�܂�
 * ���S�A����ւ�肪�������Ă��邩�`�F�b�N����B
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	code	����Ƃ݂Ȃ�OBJ�R�[�h
 * @param	obj_id	����Ƃ݂Ȃ�OBJ ID
 * @param	zone_id	����Ƃ݂Ȃ�ZONE ID
 * @retval	int		TRUE=����BFALSE=����ł͂Ȃ�
 */
//--------------------------------------------------------------
int FieldOBJ_CheckSameIDOBJCodeIn(
		CONST_FIELD_OBJ_PTR fldobj, int code, int obj_id, int zone_id )
{
	if( FieldOBJ_StatusBit_CheckEasy(fldobj,FLDOBJ_STA_BIT_USE) == FALSE ){
		return( FALSE );
	}
	
	{
		int ret = FieldOBJ_OBJCodeGetSeedIn( fldobj );
		
		if( ret != code ){
			return( FALSE );
		}
	}
	
	return( FieldOBJ_CheckSameID(fldobj,obj_id,zone_id) );
}

//==============================================================================
//	����֐�
//==============================================================================
//--------------------------------------------------------------
/**
 * �t�B�[���hOBJ TCB ����֐�
 * @param	tcb		TCB_PTR
 * @param	work	tcb work
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FldOBJ_TCB_MoveProc( TCB_PTR tcb, void *work )
{
	FIELD_OBJ_PTR fldobj = (FIELD_OBJ_PTR)work;
	
	FieldOBJ_Move( fldobj );
	
	if( FieldOBJ_StatusBitCheck_Use(fldobj) == FALSE ){
		return;
	}
	
	FldOBJ_TCB_DrawProc( fldobj );
}

//--------------------------------------------------------------
/**
 * �t�B�[���hOBJ TCB ����֐�����Ă΂��`��֐�
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FldOBJ_TCB_DrawProc( FIELD_OBJ_PTR fldobj )
{
	CONST_FIELD_OBJ_SYS_PTR fos = FieldOBJ_FieldOBJSysGet(fldobj);
	
	if( FieldOBJSys_DrawInitCompCheck(fos) == TRUE ){
		FieldOBJ_Draw( fldobj );
	}
}

//==============================================================================
//	�t�B�[���hOBJ�V�X�e���@�Q��
//==============================================================================
//--------------------------------------------------------------
/**
 * const FIELD_OBJ_SYS��FIELD_OBJ_SYS��
 * @param	sys		FIELD_OBJ_SYS_PTR 
 * @retval	FIELD_OBJ_SYS	FIELD_OBJ_SYS_PTR 
 */
//--------------------------------------------------------------
static FIELD_OBJ_SYS_PTR  FldOBJ_ConstSysLocalGet( CONST_FIELD_OBJ_SYS_PTR sys )
{
	return( (FIELD_OBJ_SYS_PTR )sys );
}

//--------------------------------------------------------------
/**
 * OBJ�o�^�\�ő吔���Z�b�g
 * @param	sys		FIELD_OBJ_SYS_PTR 
 * @param	max		�ő吔
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJSys_OBJMaxSet( FIELD_OBJ_SYS_PTR sys, int max )
{
	sys->fldobj_max = max;
}

//--------------------------------------------------------------
/**
 * OBJ�o�^�\�ő吔���擾
 * @param	sys		FIELD_OBJ_SYS_PTR 
 * @retval	int		OBJ�ő吔
 */
//--------------------------------------------------------------
int FieldOBJSys_OBJMaxGet( CONST_FIELD_OBJ_SYS_PTR sys )
{
	return( sys->fldobj_max );
}

//--------------------------------------------------------------
/**
 * ���ݑ��݂��Ă���OBJ�̐���1����
 * @param	sys		FIELD_OBJ_SYS_PTR 
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FldOBJSys_OBJCountInc( FIELD_OBJ_SYS_PTR sys )
{
	sys->fldobj_count++;
#ifdef DEBUG_PRINT_FLDOBJ_COUNT
	OS_Printf( "FIELD OBJ ADD, COUNT=0x%x\n", sys->fldobj_count );
#endif
}

//--------------------------------------------------------------
/**
 * ���ݑ��݂��Ă���OBJ�̐���1���炷
 * @param	sys		FIELD_OBJ_SYS_PTR 
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FldOBJSys_OBJCountDec( FIELD_OBJ_SYS_PTR sys )
{
	sys->fldobj_count--;
#ifdef DEBUG_PRINT_FLDOBJ_COUNT
	OS_Printf( "FIELD OBJ DEL, COUNT=0x%x\n", sys->fldobj_count );
#endif
}

//--------------------------------------------------------------
/**
 * ���ݑ��݂��Ă���OBJ�̐����Z�b�g
 * @param	sys		FIELD_OBJ_SYS_PTR 
 * @param	count	�Z�b�g���鐔
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FldOBJSys_OBJCountSet( FIELD_OBJ_SYS_PTR sys, int count )
{
	sys->fldobj_count = count;
}

//--------------------------------------------------------------
/**
 * ���ݑ��݂��Ă���OBJ�̐����擾
 * @param	fos		FIELD_OBJ_SYS_PTR
 * @retval	int		���ݑ��݂��Ă���OBJ�̐�
 */
//--------------------------------------------------------------
int FieldOBJSys_OBJCountGet( CONST_FIELD_OBJ_SYS_PTR fos )
{
	return( fos->fldobj_count );
}

//--------------------------------------------------------------
/**
 * �V�X�e���@�X�e�[�^�X�r�b�g������
 * @param	sys		FIELD_OBJ_SYS_PTR 
 * @param	bit		�������l�BFLDOBJSYS_STA_BIT_NON��
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJSys_StatusBit_Init( FIELD_OBJ_SYS_PTR sys, u32 bit )
{
	sys->status_bit = bit;
}

//--------------------------------------------------------------
/**
 * �V�X�e���@�X�e�[�^�X�r�b�g ON
 * @param	sys		FIELD_OBJ_SYS_PTR 
 * @param	bit		ON�ɂ���r�b�g�BFLDOBJSYS_STA_BIT_NON��
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJSys_StatusBit_ON( FIELD_OBJ_SYS_PTR sys, u32 bit )
{
	sys->status_bit |= bit;
}

//--------------------------------------------------------------
/**
 * �V�X�e���@�X�e�[�^�X�r�b�g OFF
 * @param	sys		FIELD_OBJ_SYS_PTR 
 * @param	bit		OFF�ɂ���r�b�g�BFLDOBJSYS_STA_BIT_NON��
 * @retval	int		�ǉ�����Ă���OBJ��
 */
//--------------------------------------------------------------
void FieldOBJSys_StatusBit_OFF( FIELD_OBJ_SYS_PTR sys, u32 bit )
{
	sys->status_bit &= ~bit;
}

//--------------------------------------------------------------
/**
 * �V�X�e���@�X�e�[�^�X�r�b�g �`�F�b�N
 * �߂�l�̓X�e�[�^�X�r�b�g�ƃ`�F�b�N����r�b�g��and�����l���Ԃ�B
 * ��F�Ώ� FIDOBJSYS_STR_BIT_DRAW_INIT_COMP�ȊO��OFF�B
 * �`�F�b�N����r�b�g��FLDOBJSYS_STA_BIT_DRAW_INIT_COMP|FLDOBJSYS_STA_BIT_MOVE_PROC_STOP
 * �߂�l��FLDOBJSYS_STA_BIT_DRAW_PROC_INIT���Ԃ�B
 * @param	sys				FIELD_OBJ_SYS_PTR 
 * @param	bit				�`�F�b�N����r�b�g�BFLDOBJ_STA_BIT_USE��
 * @retval	u32				�`�F�b�N��̃r�b�g
 */
//--------------------------------------------------------------
u32 FieldOBJSys_StatusBit_Check( CONST_FIELD_OBJ_SYS_PTR sys, u32 bit )
{
	return( (sys->status_bit&bit) );
}

//--------------------------------------------------------------
/**
 * TCB��{�v���C�I���e�B���Z�b�g
 * @param	sys				FIELD_OBJ_SYS_PTR 
 * @param	pri				TCB��{�v���C�I���e�B
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJSys_TCBStandardPrioritySet( FIELD_OBJ_SYS_PTR sys, int pri )
{
	sys->tcb_pri = pri;
}

//--------------------------------------------------------------
/**
 * TCB��{�v���C�I���e�B�擾
 * @param	sys			FIELD_OBJ_SYS_PTR 
 * @retval	u32			TCB�v���C�I���e�B
 */
//--------------------------------------------------------------
int FieldOBJSys_TCBStandardPriorityGet( CONST_FIELD_OBJ_SYS_PTR sys )
{
	return( sys->tcb_pri );
}

//--------------------------------------------------------------
/**
 * FIELD_OBJ_BLACT_CONT *�擾
 * @param	sys		FIELD_OBJ_SYS_PTR 
 * @retval	FIELD_OBJ_BLACT_CONT	FIELD_OBJ_BLACT_CONT *
 */
//--------------------------------------------------------------
FIELD_OBJ_BLACT_CONT * FieldOBJSys_BlActContGet( CONST_FIELD_OBJ_SYS_PTR sys )
{
	return( &(((FIELD_OBJ_SYS_PTR)sys)->blact_cont) );
}

//--------------------------------------------------------------
/**
 * FIELD_OBJ_RENDER_CONT_PTR�Z�b�g
 * @param	sys		FIELD_OBJ_SYS_PTR 
 * @param	render	FIELD_OBJ_RENDER_CONT_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJSys_RenderContSet( FIELD_OBJ_SYS_PTR sys, FIELD_OBJ_RENDER_CONT_PTR render )
{
	sys->render_cont = render;
}

//--------------------------------------------------------------
/**
 * FIELD_OBJ_RENDER_CONT_PTR �擾
 * @param	sys		FIELD_OBJ_SYS_PTR 
 * @retval	FIELD_OBJ_RENDER_CONT_PTR FIELD_OBJ_RENDER_CONT_PTR
 */
//--------------------------------------------------------------
FIELD_OBJ_RENDER_CONT_PTR FieldOBJSys_RenderContGet( CONST_FIELD_OBJ_SYS_PTR sys )
{
	return( sys->render_cont );
}

//--------------------------------------------------------------
/**
 * �t�B�[���hOBJ���[�N���Z�b�g
 * @param	sys		FIELD_OBJ_SYS_PTR 
 * @param	ptr		FIELD_OBJ_PTR 
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJSys_FieldOBJWorkSet( FIELD_OBJ_SYS_PTR sys, FIELD_OBJ_PTR ptr )
{
	sys->fldobj_work = ptr;
}

//--------------------------------------------------------------
/**
 * �t�B�[���hOBJ���[�N�擾
 * @param	sys			FIELD_OBJ_SYS_PTR 
 * @retval	FIELD_OBJ	FIELD_OBJ_PTR 
 */
//--------------------------------------------------------------
CONST_FIELD_OBJ_PTR  FieldOBJSys_FieldOBJWorkGet( CONST_FIELD_OBJ_SYS_PTR sys )
{
	return( sys->fldobj_work );
}

//--------------------------------------------------------------
/**
 * �t�B�[���hOBJ���[�N�擾�@���[�J��
 * @param	sys			FIELD_OBJ_SYS_PTR 
 * @retval	FIELD_OBJ	FIELD_OBJ_PTR 
 */
//--------------------------------------------------------------
static FIELD_OBJ_PTR FldOBJSys_FieldOBJWorkGet( CONST_FIELD_OBJ_SYS_PTR sys )
{
	return( sys->fldobj_work );
}

//--------------------------------------------------------------
/**
 * �t�B�[���hOBJ���[�N�擾�@FIELD OBJ���[�J���p
 * const�����B�t�B�[���hOBJ�ȊO�͎g�p�֎~
 * @param	sys			FIELD_OBJ_SYS_PTR 
 * @retval	FIELD_OBJ	FIELD_OBJ_PTR 
 */
//--------------------------------------------------------------
FIELD_OBJ_PTR  FieldOBJSys_FldOBJWorkGet( CONST_FIELD_OBJ_SYS_PTR sys )
{
	return( sys->fldobj_work );
}

//--------------------------------------------------------------
/**
 * �t�B�[���hOBJ���[�N�i�s�B
 * FieldOBJSys_FieldOBJWorkGet()�Ŏ擾�����|�C���^���P�i�߂�B
 * @param	FIELD_OBJ	FIELD_OBJ_PTR 
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJSys_FieldOBJWorkInc( CONST_FIELD_OBJ_PTR *fldobj )
{
	(*fldobj)++;
}

//--------------------------------------------------------------
/**
 * �t�B�[���hOBJ���[�N�i�s�B��const
 * FieldOBJSys_FieldOBJWorkGet()�Ŏ擾�����|�C���^���P�i�߂�B
 * @param	FIELD_OBJ	FIELD_OBJ_PTR 
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJSys_FldOBJWorkInc( FIELD_OBJ_PTR *fldobj )
{
	(*fldobj)++;
}

//--------------------------------------------------------------
/**
 * FIELDSYS_WORK *�Z�b�g
 * @param	fos		FIELD_OBJ_SYS_PTR
 * @param	fsys	FIELDSYS_WORK *
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJSys_FieldSysWorkSet( FIELD_OBJ_SYS_PTR fos, FIELDSYS_WORK *fsys )
{
	fos->fieldsys = fsys;
}

//--------------------------------------------------------------
/**
 * FIELDSYS_WORK *�擾
 * @param	fos		FIELD_OBJ_SYS_PTR
 * @retval	FIELDSYS_WORK	FIELDSYS_WORK *
 */
//--------------------------------------------------------------
FIELDSYS_WORK * FieldOBJSys_FieldSysWorkGet( CONST_FIELD_OBJ_SYS_PTR fos )
{
	return( fos->fieldsys );
}

//--------------------------------------------------------------
/**
 * �A�[�J�C�u�n���h���Z�b�g
 * @param	fos		FIELD_OBJ_SYS_PTR
 * @param	handle	ARCHANDLE *
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJSys_ArcHandleSet( FIELD_OBJ_SYS_PTR fos, ARCHANDLE *handle )
{
	fos->archandle = handle;
}

//--------------------------------------------------------------
/**
 * �A�[�J�C�u�n���h���擾
 * @param	fos		FIELD_OBJ_SYS_PTR
 * @retval	ARCHANDLE*�@ARCHANDLE *
 */
//--------------------------------------------------------------
ARCHANDLE * FieldOBJSys_ArcHandleGet( CONST_FIELD_OBJ_SYS_PTR fos )
{
	GF_ASSERT( fos->archandle != NULL && "FieldOBJSys_ArcHandleGet()�n���h������" );
	return( ((FIELD_OBJ_SYS_PTR)fos)->archandle );
}

//==============================================================================
//	�t�B�[���hOBJ�@�Q��
//==============================================================================
//--------------------------------------------------------------
/**
 * �X�e�[�^�X�r�b�g������
 * @param	fldobj			FIELD_OBJ_PTR 
 * @param	bit				�������l�BFLDOBJ_STA_BIT_USE��
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_StatusBit_Init( FIELD_OBJ_PTR fldobj, u32 bit )
{
	fldobj->status_bit = bit;
}

//--------------------------------------------------------------
/**
 * �X�e�[�^�X�r�b�g�擾
 * @param	fldobj			FIELD_OBJ_PTR 
 * @retval	u32				�X�e�[�^�X�r�b�g
 */
//--------------------------------------------------------------
u32 FieldOBJ_StatusBit_Get( CONST_FIELD_OBJ_PTR fldobj )
{
	return( fldobj->status_bit );
}

//--------------------------------------------------------------
/**
 * �X�e�[�^�X�r�b�g ON
 * @param	fldobj			FIELD_OBJ_PTR 
 * @param	bit				ON�ɂ������r�b�g�BFLDOBJ_STA_BIT_USE��
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_StatusBit_ON( FIELD_OBJ_PTR fldobj, u32 bit )
{
	fldobj->status_bit |= bit;
}

//--------------------------------------------------------------
/**
 * �X�e�[�^�X�r�b�g OFF
 * @param	fldobj			FIELD_OBJ_PTR 
 * @param	bit				OFF�ɂ������r�b�g�BFLDOBJ_STA_BIT_USE��
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_StatusBit_OFF( FIELD_OBJ_PTR fldobj, u32 bit )
{
	fldobj->status_bit &= ~bit;
}

//--------------------------------------------------------------
/**
 * �X�e�[�^�X�r�b�g �`�F�b�N
 * �߂�l�̓X�e�[�^�X�r�b�g�ƃ`�F�b�N����r�b�g��and�����l���Ԃ�B
 * 
 * ��F�Ώ�OBJ�̃X�e�[�^�X�r�b�g��FIDOBJ_STR_BIT_USE�ȊO��OFF�B
 * �`�F�b�N����r�b�g��FLDOBJ_STA_BIT_USE|FLDOBJ_STA_BIT_MOVE_START�B
 * �߂�l��FLDOBJ_STA_BIT_USE���Ԃ�B
 * 
 * @param	fldobj			FIELD_OBJ_PTR 
 * @param	bit				�`�F�b�N����r�b�g�BFLDOBJ_STA_BIT_USE��
 * @retval	u32				�`�F�b�N��̃r�b�g
 */
//--------------------------------------------------------------
u32 FieldOBJ_StatusBit_Check( CONST_FIELD_OBJ_PTR fldobj, u32 bit )
{
	return( fldobj->status_bit & bit );
}

//--------------------------------------------------------------
/**
 * �X�e�[�^�X�r�b�g �ȈՃ`�F�b�N
 * @param	fldobj			FIELD_OBJ_PTR 
 * @param	bit				�`�F�b�N����r�b�g�BFLDOBJ_STA_BIT_USE��
 * @retval	u32				TRUE=bit�̂ǂꂩ���Y���BFALSE=�Y������
 */
//--------------------------------------------------------------
u32 FieldOBJ_StatusBit_CheckEasy( CONST_FIELD_OBJ_PTR fldobj, u32 bit )
{
	if( (fldobj->status_bit&bit) ){
		return( TRUE );
	}
	
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * ����r�b�g�@������
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	bit		����������r�b�g FLDOBJ_MOVE_BIT_NON��
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_MoveBit_Init( FIELD_OBJ_PTR fldobj, u32 bit )
{
	fldobj->move_bit = bit;
}

//--------------------------------------------------------------
/**
 * ����r�b�g�@�擾
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	u32		����r�b�g
 */
//--------------------------------------------------------------
u32 FieldOBJ_MoveBit_Get( CONST_FIELD_OBJ_PTR fldobj )
{
	return( fldobj->move_bit );
}

//--------------------------------------------------------------
/**
 * ����r�b�g�@ON
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	bit		���Ă�r�b�g FLDOBJ_MOVE_BIT_NON��
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_MoveBit_ON( FIELD_OBJ_PTR fldobj, u32 bit )
{
	fldobj->move_bit |= bit;
}

//--------------------------------------------------------------
/**
 * ����r�b�g�@OFF
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	bit		���낷�r�b�g FLDOBJ_MOVE_BIT_NON��
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_MoveBit_OFF( FIELD_OBJ_PTR fldobj, u32 bit )
{
	fldobj->move_bit &= ~bit;
}

//--------------------------------------------------------------
/**
 * ����r�b�g�@�`�F�b�N
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	bit		�`�F�b�N����r�b�g FLDOBJ_MOVE_BIT_NON��
 * @retval	nothing
 */
//--------------------------------------------------------------
u32 FieldOBJ_MoveBit_Check( CONST_FIELD_OBJ_PTR fldobj, u32 bit )
{
	return( (fldobj->move_bit & bit) );
}

//--------------------------------------------------------------
/**
 * OBJ ID�Z�b�g
 * @param	fldobj	FIELD_OBJ_PTR 
 * @param	id		obj id
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_OBJIDSet( FIELD_OBJ_PTR fldobj, u32 obj_id )
{
	fldobj->obj_id = obj_id;
}

//--------------------------------------------------------------
/**
 * OBJ ID�擾
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	u32		OBJ ID
 */
//--------------------------------------------------------------
u32 FieldOBJ_OBJIDGet( CONST_FIELD_OBJ_PTR fldobj )
{
	return( fldobj->obj_id );
}

//--------------------------------------------------------------
/**
 * ZONE ID�Z�b�g
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	zone_id	�]�[��ID
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_ZoneIDSet( FIELD_OBJ_PTR fldobj, int zone_id )
{
	fldobj->zone_id = zone_id;
}

//--------------------------------------------------------------
/**
 * ZONE ID�擾
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	int		ZONE ID
 */
//--------------------------------------------------------------
int FieldOBJ_ZoneIDGet( CONST_FIELD_OBJ_PTR fldobj )
{
	return( fldobj->zone_id );
}

//--------------------------------------------------------------
/**
 * OBJ�R�[�h�Z�b�g
 * @param	fldobj			FIELD_OBJ_PTR 
 * @param	code			�Z�b�g����R�[�h
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_OBJCodeSet( FIELD_OBJ_PTR fldobj, u32 code )
{
	fldobj->obj_code = code;
}

//--------------------------------------------------------------
/**
 * OBJ�R�[�h�擾
 * @param	fldobj			FIELD_OBJ_PTR 
 * @retval	u32				OBJ�R�[�h
 */
//--------------------------------------------------------------
u32 FieldOBJ_OBJCodeGet( CONST_FIELD_OBJ_PTR fldobj )
{
	return( fldobj->obj_code );
}

//--------------------------------------------------------------
/**
 * OBJ�R�[�h�擾�@��`�F�b�N����
 * @param	fldobj			FIELD_OBJ_PTR 
 * @retval	u32				OBJ�R�[�h
 */
//--------------------------------------------------------------
u32 FieldOBJ_OBJCodeGetSeedIn( CONST_FIELD_OBJ_PTR fldobj )
{
	u32 code = FieldOBJ_OBJCodeGet( fldobj );
	
	if( FieldOBJ_OBJCodeSeedCheck(code) == TRUE ){
		code = FieldOBJ_OBJCodeSeedGet( fldobj );
	}
	
	return( code );
}

//--------------------------------------------------------------
/**
 * ����R�[�h�Z�b�g
 * @param	fldobj			FIELD_OBJ_PTR 
 * @param	code			����R�[�h
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_MoveCodeSet( FIELD_OBJ_PTR fldobj, u32 code )
{
	fldobj->move_code = code;
}

//--------------------------------------------------------------
/**
 * ����R�[�h�擾
 * @param	fldobj			FIELD_OBJ_PTR 
 * @retval	u32				����R�[�h
 */
//--------------------------------------------------------------
u32 FieldOBJ_MoveCodeGet( CONST_FIELD_OBJ_PTR fldobj )
{
	return( fldobj->move_code );
}

//--------------------------------------------------------------
/**
 * �C�x���g�^�C�v�Z�b�g
 * @param	fldobj		FIELD_OBJ_PTR 
 * @param	type		Event Type
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_EventTypeSet( FIELD_OBJ_PTR fldobj, u32 type )
{
	fldobj->event_type = type;
}

//--------------------------------------------------------------
/**
 * �C�x���g�^�C�v�擾
 * @param	fldobj		FIELD_OBJ_PTR 
 * @retval	u32			Event Type
 */
//--------------------------------------------------------------
u32 FieldOBJ_EventTypeGet( CONST_FIELD_OBJ_PTR fldobj )
{
	return( fldobj->event_type );
}

//--------------------------------------------------------------
/**
 * �C�x���g�t���O�Z�b�g
 * @param	fldobj		FIELD_OBJ_PTR 
 * @param	flag		Event Flag
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_EventFlagSet( FIELD_OBJ_PTR fldobj, u32 flag )
{
	fldobj->event_flag = flag;
}

//--------------------------------------------------------------
/**
 * �C�x���g�t���O�擾
 * @param	fldobj		FIELD_OBJ_PTR 
 * @retval	u32			Event Flag
 */
//--------------------------------------------------------------
u32 FieldOBJ_EventFlagGet( CONST_FIELD_OBJ_PTR fldobj )
{
	return( fldobj->event_flag );
}

//--------------------------------------------------------------
/**
 * �C�x���gID�Z�b�g
 * @param	fldobj		FIELD_OBJ_PTR 
 * @param	id			Event ID
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_EventIDSet( FIELD_OBJ_PTR fldobj, u32 id )
{
	fldobj->event_id = id;
}

//--------------------------------------------------------------
/**
 * �C�x���gID�擾
 * @param	fldobj		FIELD_OBJ_PTR 
 * @retval	u32			Event ID
 */
//--------------------------------------------------------------
u32 FieldOBJ_EventIDGet( CONST_FIELD_OBJ_PTR fldobj )
{
	return( fldobj->event_id );
}

//--------------------------------------------------------------
/**
 * �w�b�_�[�w������Z�b�g
 * @param	fldobj		FIELD_OBJ_PTR 
 * @param	dir			DIR_UP��
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_DirHeaderSet( FIELD_OBJ_PTR fldobj, int dir )
{
	fldobj->dir_head = dir;
}

//--------------------------------------------------------------
/**
 * �w�b�_�[�w������擾
 * @param	fldobj		FIELD_OBJ_PTR 
 * @retval	u32			DIR_UP��
 */
//--------------------------------------------------------------
u32 FieldOBJ_DirHeaderGet( CONST_FIELD_OBJ_PTR fldobj )
{
	return( fldobj->dir_head );
}

//--------------------------------------------------------------
/**
 * �\�������Z�b�g�@����
 * @param	fldobj			FIELD_OBJ_PTR 
 * @param	dir				DIR_UP��
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_DirDispSetForce( FIELD_OBJ_PTR fldobj, int dir )
{
	fldobj->dir_disp_old = fldobj->dir_disp;
	fldobj->dir_disp = dir;
}

//--------------------------------------------------------------
/**
 * �\�������Z�b�g�@FLDOBJ_STA_BIT_PAUSE_DIR�`�F�b�N����
 * @param	fldobj			FIELD_OBJ_PTR 
 * @param	dir				DIR_UP��
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_DirDispCheckSet( FIELD_OBJ_PTR fldobj, int dir )
{
	if( FieldOBJ_StatusBit_Check(fldobj,FLDOBJ_STA_BIT_PAUSE_DIR) == 0 ){
		fldobj->dir_disp_old = fldobj->dir_disp;
		fldobj->dir_disp = dir;
	}
}

//--------------------------------------------------------------
/**
 * �\�������擾
 * @param	fldobj			FIELD_OBJ_PTR 
 * @param	dir				DIR_UP��
 * @retval	nothing
 */
//--------------------------------------------------------------
int FieldOBJ_DirDispGet( CONST_FIELD_OBJ_PTR fldobj )
{
	return( fldobj->dir_disp );
}

//--------------------------------------------------------------
/**
 * �ߋ��\�������擾
 * @param	fldobj			FIELD_OBJ_PTR 
 * @param	dir				DIR_UP��
 * @retval	nothing
 */
//--------------------------------------------------------------
int FieldOBJ_DirDispOldGet( CONST_FIELD_OBJ_PTR fldobj )
{
	return( fldobj->dir_disp_old );
}

//--------------------------------------------------------------
/**
 * �ړ������Z�b�g
 * @param	fldobj			FIELD_OBJ_PTR 
 * @param	dir				DIR_UP��
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_DirMoveSet( FIELD_OBJ_PTR fldobj, int dir )
{
	fldobj->dir_move_old = fldobj->dir_move;
	fldobj->dir_move = dir;
}

//--------------------------------------------------------------
/**
 * �ړ������擾
 * @param	fldobj			FIELD_OBJ_PTR 
 * @retval	dir				DIR_UP��
 */
//--------------------------------------------------------------
int FieldOBJ_DirMoveGet( CONST_FIELD_OBJ_PTR fldobj )
{
	return( fldobj->dir_move );
}

//--------------------------------------------------------------
/**
 * �ߋ��ړ������擾
 * @param	fldobj			FIELD_OBJ_PTR 
 * @retval	dir				DIR_UP��
 */
//--------------------------------------------------------------
int FieldOBJ_DirMoveOldGet( CONST_FIELD_OBJ_PTR fldobj )
{
	return( fldobj->dir_move_old );
}

//--------------------------------------------------------------
/**
 * �\���A�ړ������Z�b�g�@FLDOBJ_STA_BIT_PAUSE_DIR�`�F�b�N����
 * @param	fldobj			FIELD_OBJ_PTR 
 * @param	dir				DIR_UP��
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_DirMoveDispCheckSet( FIELD_OBJ_PTR fldobj, int dir )
{
	FieldOBJ_DirDispCheckSet( fldobj, dir );
	FieldOBJ_DirMoveSet( fldobj, dir );
}

//--------------------------------------------------------------
/**
 * �w�b�_�[�w��p�����^�Z�b�g
 * @param	fldobj			FIELD_OBJ_PTR 
 * @param	param			�p�����^
 * @param	no				�Z�b�g����p�����^�ԍ��@FLDOBJ_PARAM_0��
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_ParamSet( FIELD_OBJ_PTR fldobj, int param, FLDOBJ_H_PARAM no )
{
	switch( no ){
	case FLDOBJ_PARAM_0: fldobj->param0 = param; break;
	case FLDOBJ_PARAM_1: fldobj->param1 = param; break;
	case FLDOBJ_PARAM_2: fldobj->param2 = param; break;
	default: GF_ASSERT( 0 && "FieldOBJ_ParamSet()�s���Ȉ���" );
	}
}

//--------------------------------------------------------------
/**
 * �w�b�_�[�w��p�����^�擾
 * @param	fldobj			FIELD_OBJ_PTR
 * @param	param			FLDOBJ_PARAM_0��
 * @retval	int				�p�����^
 */
//--------------------------------------------------------------
int FieldOBJ_ParamGet( CONST_FIELD_OBJ_PTR fldobj, FLDOBJ_H_PARAM param )
{
	switch( param ){
	case FLDOBJ_PARAM_0: return( fldobj->param0 );
	case FLDOBJ_PARAM_1: return( fldobj->param1 );
	case FLDOBJ_PARAM_2: return( fldobj->param2 );
	}
	
	GF_ASSERT( 0 && "FieldOBJ_ParamGet()�s���Ȉ���" );
	return( 0 );
}

//--------------------------------------------------------------
/**
 * �ړ�����X�Z�b�g
 * @param	fldobj			FIELD_OBJ_PTR 
 * @param	x				�ړ�����
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_MoveLimitXSet( FIELD_OBJ_PTR fldobj, int x )
{
	fldobj->move_limit_x = x;
}

//--------------------------------------------------------------
/**
 * �ړ�����X�擾
 * @param	fldobj		FIELD_OBJ_PTR 
 * @retval	int			�ړ�����X
 */
//--------------------------------------------------------------
int FieldOBJ_MoveLimitXGet( CONST_FIELD_OBJ_PTR fldobj )
{
	return( fldobj->move_limit_x );
}

//--------------------------------------------------------------
/**
 * �ړ�����Z�Z�b�g
 * @param	fldobj			FIELD_OBJ_PTR 
 * @param	y				�ړ�����
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_MoveLimitZSet( FIELD_OBJ_PTR fldobj, int z )
{
	fldobj->move_limit_z = z;
}

//--------------------------------------------------------------
/**
 * �ړ�����Z�擾
 * @param	fldobj		FIELD_OBJ_PTR 
 * @retval	int			�ړ�����z
 */
//--------------------------------------------------------------
int FieldOBJ_MoveLimitZGet( CONST_FIELD_OBJ_PTR fldobj )
{
	return( fldobj->move_limit_z );
}

//--------------------------------------------------------------
/**
 * �`��X�e�[�^�X�Z�b�g
 * @param	fldobj		FIELD_OBJ_PTR 
 * @param	st			DRAW_STA_STOP��
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_DrawStatusSet( FIELD_OBJ_PTR fldobj, u32 st )
{
	fldobj->draw_status = st;
}

//--------------------------------------------------------------
/**
 * �`��X�e�[�^�X�擾
 * @param	fldobj		FIELD_OBJ_PTR 
 * @retval	u32			DRAW_STA_STOP��
 */
//--------------------------------------------------------------
u32 FieldOBJ_DrawStatusGet( CONST_FIELD_OBJ_PTR fldobj )
{
	return( fldobj->draw_status );
}

//--------------------------------------------------------------
/**
 * ����TCB*�Z�b�g
 * @param	fldobj			FIELD_OBJ_PTR 
 * @param	tcb				TCB_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_MoveTcbPtrSet( FIELD_OBJ_PTR fldobj, TCB_PTR tcb )
{
	fldobj->tcb = tcb;
}

//--------------------------------------------------------------
/**
 * ����TCB*�擾
 * @param	fldobj			FIELD_OBJ_PTR 
 * @retval	TCB_PTR			TCB_PTR
 */
//--------------------------------------------------------------
TCB_PTR FieldOBJ_MoveTcbPtrGet( CONST_FIELD_OBJ_PTR fldobj )
{
	return( fldobj->tcb );
}

//--------------------------------------------------------------
/**
 * ����TCB*���폜
 * @param	fldobj			FIELD_OBJ_PTR 
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_MoveTcbDelete( CONST_FIELD_OBJ_PTR fldobj )
{
	TCB_Delete( FieldOBJ_MoveTcbPtrGet(fldobj) );
}

//--------------------------------------------------------------
/**
 * FIELD_OBJ_SYS_PTR �Z�b�g
 * @param	fldobj			FIELD_OBJ_PTR 
 * @param	sys				FIELD_OBJ_SYS_PTR 
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_FieldOBJSysSet( FIELD_OBJ_PTR fldobj, CONST_FIELD_OBJ_SYS_PTR sys )
{
	fldobj->fldobj_sys = sys;
}

//--------------------------------------------------------------
/**
 * FIELD_OBJ_SYS_PTR �擾
 * @param	fldobj			FIELD_OBJ_PTR 
 * @retval	FIELD_OBJ_SYS	FIELD_OBJ_SYS_PTR 
 */
//--------------------------------------------------------------
CONST_FIELD_OBJ_SYS_PTR FieldOBJ_FieldOBJSysGet( CONST_FIELD_OBJ_PTR fldobj )
{
	return( fldobj->fldobj_sys );
}

//--------------------------------------------------------------
/**
 * FIELD_OBJ_SYS_PTR  �擾 not const
 * @param	fldobj			FIELD_OBJ_PTR 
 * @retval	FIELD_OBJ_SYS	FIELD_OBJ_SYS_PTR 
 */
//--------------------------------------------------------------
static FIELD_OBJ_SYS_PTR FldOBJ_FieldOBJSysGet( CONST_FIELD_OBJ_PTR fldobj )
{
	return( FldOBJ_ConstSysLocalGet(fldobj->fldobj_sys) );
}

//--------------------------------------------------------------
/**
 * ����֐��p���[�N�������B
 * size�����[�N�T�C�Y�𒴂��Ă����ꍇ�AASSERT�B
 * ����p���[�N��size���A0�ŏ������B
 * @param	fldobj	FIELD_OBJ_PTR 
 * @param	size	�K�v�ȃ��[�N�T�C�Y
 * @retval	void*	���������ꂽ���[�N
 */
//--------------------------------------------------------------
void * FieldOBJ_MoveProcWorkInit( FIELD_OBJ_PTR fldobj, int size )
{
	void *work;
	
	GF_ASSERT( size <= FLDOBJ_MOVE_WORK_SIZE && "fldobj move work size over" );
	
	work = FieldOBJ_MoveProcWorkGet( fldobj );
	memset( work, 0, size );
	
	return( work );
}

//--------------------------------------------------------------
/**
 * ����֐��p���[�N�擾�B
 * @param	fldobj	FIELD_OBJ_PTR 
 * @retval	void*	���[�N
 */
//--------------------------------------------------------------
void * FieldOBJ_MoveProcWorkGet( FIELD_OBJ_PTR fldobj )
{
	return( fldobj->move_proc_work );
}

//--------------------------------------------------------------
/**
 * ����⏕�֐��p���[�N�������B
 * size�����[�N�T�C�Y�𒴂��Ă����ꍇ�AASSERT�B
 * @param	fldobj	FIELD_OBJ_PTR 
 * @param	size	�K�v�ȃ��[�N�T�C�Y
 * @retval	void*	���������ꂽ���[�N
 */
//--------------------------------------------------------------
void * FieldOBJ_MoveSubProcWorkInit( FIELD_OBJ_PTR fldobj, int size )
{
	u8 *work;
	
	GF_ASSERT( size <= FLDOBJ_MOVE_SUB_WORK_SIZE &&
			"�t�B�[���hOBJ ����⏕���[�N�T�C�Y���I�[�o�[" );
	
	work = FieldOBJ_MoveSubProcWorkGet( fldobj );
	memset( work, 0, size );
	
	return( work );
}

//--------------------------------------------------------------
/**
 * ����⏕�֐��p���[�N�擾
 * @param	fldobj	FIELD_OBJ_PTR 
 * @retval	void*	���[�N*
 */
//--------------------------------------------------------------
void * FieldOBJ_MoveSubProcWorkGet( FIELD_OBJ_PTR fldobj )
{
	return( fldobj->move_sub_proc_work );
}

//--------------------------------------------------------------
/**
 * ����⏕�֐��p���[�N�������B
 * size�����[�N�T�C�Y�𒴂��Ă����ꍇ�AASSERT�B
 * @param	fldobj	FIELD_OBJ_PTR 
 * @param	size	�K�v�ȃ��[�N�T�C�Y
 * @retval	void*	���������ꂽ���[�N
 */
//--------------------------------------------------------------
void * FieldOBJ_MoveCmdWorkInit( FIELD_OBJ_PTR fldobj, int size )
{
	u8 *work;
	
	GF_ASSERT( size <= FLDOBJ_MOVE_CMD_WORK_SIZE &&
			"�t�B�[���hOBJ ����R�}���h���[�N�T�C�Y���I�[�o�[" );
	
	work = FieldOBJ_MoveCmdWorkGet( fldobj );
	memset( work, 0, size );
	
	return( work );
}

//--------------------------------------------------------------
/**
 * ����R�}���h�p���[�N�擾
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	void*	���[�N*
 */
//--------------------------------------------------------------
void * FieldOBJ_MoveCmdWorkGet( FIELD_OBJ_PTR fldobj )
{
	return( fldobj->move_cmd_proc_work );
}

//--------------------------------------------------------------
/**
 * �`��֐��p���[�N�������B
 * size�����[�N�T�C�Y�𒴂��Ă����ꍇ�AASSERT�B
 * @param	fldobj	FIELD_OBJ_PTR 
 * @param	size	�K�v�ȃ��[�N�T�C�Y
 * @retval	void*	���������ꂽ���[�N
 */
//--------------------------------------------------------------
void * FieldOBJ_DrawProcWorkInit( FIELD_OBJ_PTR fldobj, int size )
{
	u8 *work;
	
	GF_ASSERT( size <= FLDOBJ_DRAW_WORK_SIZE && "fldobj draw work size over" );
	
	work = FieldOBJ_DrawProcWorkGet( fldobj );
	memset( work, 0, size );
	
	return( work );
}

//--------------------------------------------------------------
/**
 * �`��֐��p���[�N�擾
 * @param	fldobj	FIELD_OBJ_PTR 
 * @retval	void*	���[�N
 */
//--------------------------------------------------------------
void * FieldOBJ_DrawProcWorkGet( FIELD_OBJ_PTR fldobj )
{
	return( fldobj->draw_proc_work );
}

//--------------------------------------------------------------
/**
 * �������֐��Z�b�g
 * @param	fldobj	FIELD_OBJ_PTR 
 * @param	init	�������֐�
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_MoveInitProcSet( FIELD_OBJ_PTR fldobj, FIELD_OBJ_MOVE_PROC_INIT init )
{
	fldobj->move_init_proc = init;
}

//--------------------------------------------------------------
/**
 * �������֐����s
 * @param	fldobj	FIELD_OBJ_PTR 
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_MoveInitProcCall( FIELD_OBJ_PTR fldobj )
{
	fldobj->move_init_proc( fldobj );
}

//--------------------------------------------------------------
/**
 * ����֐��Z�b�g
 * @param	fldobj	FIELD_OBJ_PTR 
 * @param	move	����֐�
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_MoveProcSet( FIELD_OBJ_PTR fldobj, FIELD_OBJ_MOVE_PROC move )
{
	fldobj->move_proc = move;
}

//--------------------------------------------------------------
/**
 * ����֐����s
 * @param	fldobj	FIELD_OBJ_PTR 
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_MoveProcCall( FIELD_OBJ_PTR fldobj )
{
	fldobj->move_proc( fldobj );
}

//--------------------------------------------------------------
/**
 * �폜�֐��o�^
 * @param	fldobj	FIELD_OBJ_PTR 
 * @param	del		����֐�
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_MoveDeleteProcSet( FIELD_OBJ_PTR fldobj, FIELD_OBJ_MOVE_PROC_DEL del )
{
	fldobj->move_delete_proc = del;
}

//--------------------------------------------------------------
/**
 * �폜�֐����s
 * @param	fldobj	FIELD_OBJ_PTR 
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_MoveDeleteProcCall( FIELD_OBJ_PTR fldobj )
{
	fldobj->move_delete_proc( fldobj );
}

#if 0
//--------------------------------------------------------------
/**
 * ���A�֐��o�^
 * @param	fldobj	FIELD_OBJ_PTR 
 * @param	del		����֐�
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_MoveReturnProcSet( FIELD_OBJ_PTR fldobj, FIELD_OBJ_MOVE_PROC_RET ret )
{
	GF_ASSERT( 0 );
//	fldobj->move_return_proc = ret;
}
#endif

//--------------------------------------------------------------
/**
 * ���A�֐����s
 * @param	fldobj	FIELD_OBJ_PTR 
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_MoveReturnProcCall( FIELD_OBJ_PTR fldobj )
{
#if 0
	fldobj->move_return_proc( fldobj );
#else
	const FIELD_OBJ_MOVE_PROC_LIST *list =
		FldOBJ_MoveProcListGet( FieldOBJ_MoveCodeGet(fldobj) );
	list->return_proc( fldobj );
#endif
}

//--------------------------------------------------------------
/**
 * �`�揉�����֐��o�^
 * @param	fldobj	FIELD_OBJ_PTR 
 * @param	init	�������֐�
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_DrawInitProcSet( FIELD_OBJ_PTR fldobj, FIELD_OBJ_DRAW_PROC_INIT init )
{
	fldobj->draw_init_proc = init;
}

//--------------------------------------------------------------
/**
 * �`�揉�����֐����s
 * @param	fldobj	FIELD_OBJ_PTR 
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_DrawInitProcCall( FIELD_OBJ_PTR fldobj )
{
	fldobj->draw_init_proc( fldobj );
}

//--------------------------------------------------------------
/**
 * �`��֐��o�^
 * @param	fldobj	FIELD_OBJ_PTR 
 * @param	draw	�`��֐�
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_DrawProcSet( FIELD_OBJ_PTR fldobj, FIELD_OBJ_DRAW_PROC draw )
{
	fldobj->draw_proc = draw;
}

//--------------------------------------------------------------
/**
 * �`��֐����s
 * @param	fldobj	FIELD_OBJ_PTR 
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_DrawProcCall( FIELD_OBJ_PTR fldobj )
{
	fldobj->draw_proc( fldobj );
}

//--------------------------------------------------------------
/**
 * �`��폜�֐��o�^
 * @param	fldobj	FIELD_OBJ_PTR 
 * @param	del		�폜�֐�
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_DrawDeleteProcSet( FIELD_OBJ_PTR fldobj, FIELD_OBJ_DRAW_PROC_DEL del )
{
	fldobj->draw_delete_proc = del;
}

//--------------------------------------------------------------
/**
 * �`��폜�֐����s
 * @param	fldobj	FIELD_OBJ_PTR 
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_DrawDeleteProcCall( FIELD_OBJ_PTR fldobj )
{
	fldobj->draw_delete_proc( fldobj );
}

//--------------------------------------------------------------
/**
 * �`��ޔ��֐��o�^
 * @param	fldobj	FIELD_OBJ_PTR 
 * @param	push	�ޔ��֐�
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_DrawPushProcSet( FIELD_OBJ_PTR fldobj, FIELD_OBJ_DRAW_PROC_PUSH push )
{
	fldobj->draw_push_proc = push;
}

//--------------------------------------------------------------
/**
 * �`��ޔ��֐����s
 * @param	fldobj	FIELD_OBJ_PTR 
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_DrawPushProcCall( FIELD_OBJ_PTR fldobj )
{
	fldobj->draw_push_proc( fldobj );
}

//--------------------------------------------------------------
/**
 * �`�敜�A�֐��o�^
 * @param	fldobj	FIELD_OBJ_PTR 
 * @param	pop		�ޔ��֐�
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_DrawPopProcSet( FIELD_OBJ_PTR fldobj, FIELD_OBJ_DRAW_PROC_POP pop )
{
	fldobj->draw_pop_proc = pop;
}

//--------------------------------------------------------------
/**
 * �`�敜�A�֐����s
 * @param	fldobj	FIELD_OBJ_PTR 
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_DrawPopProcCall( FIELD_OBJ_PTR fldobj )
{
	fldobj->draw_pop_proc( fldobj );
}

//--------------------------------------------------------------
/**
 * �A�j���[�V�����R�}���h�R�[�h�Z�b�g
 * @param	fldobj	FIELD_OBJ_PTR 
 * @param	code	AC_DIR_U��
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_AcmdCodeSet( FIELD_OBJ_PTR fldobj, int code )
{
	fldobj->acmd_code = code;
}

//--------------------------------------------------------------
/**
 * �A�j���[�V�����R�}���h�R�[�h�擾
 * @param	fldobj	FIELD_OBJ_PTR 
 * @retval	int		AC_DIR_U��
 */
//--------------------------------------------------------------
int FieldOBJ_AcmdCodeGet( CONST_FIELD_OBJ_PTR fldobj )
{
	return( fldobj->acmd_code );
}

//--------------------------------------------------------------
/**
 * �A�j���[�V�����R�}���h�V�[�P���X�Z�b�g
 * @param	fldobj	FIELD_OBJ_PTR 
 * @param	no		�V�[�P���X
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_AcmdSeqSet( FIELD_OBJ_PTR fldobj, int no )
{
	fldobj->acmd_seq = no;
}

//--------------------------------------------------------------
/**
 * �A�j���[�V�����R�}���h�V�[�P���X����
 * @param	fldobj	FIELD_OBJ_PTR 
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_AcmdSeqInc( FIELD_OBJ_PTR fldobj )
{
	fldobj->acmd_seq++;
}

//--------------------------------------------------------------
/**
 * �A�j���[�V�����R�}���h�V�[�P���X�擾
 * @param	fldobj	FIELD_OBJ_PTR 
 * @retval	int		�V�[�P���X
 */
//--------------------------------------------------------------
int FieldOBJ_AcmdSeqGet( CONST_FIELD_OBJ_PTR fldobj )
{
	return( fldobj->acmd_seq );
}

//--------------------------------------------------------------
/**
 * ���݂̃}�b�v�A�g���r���[�g���Z�b�g
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	attr	�Z�b�g����A�g���r���[�g
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_NowMapAttrSet( FIELD_OBJ_PTR fldobj, u32 attr )
{
	fldobj->now_attr = attr;
}

//--------------------------------------------------------------
/**
 * ���݂̃}�b�v�A�g���r���[�g���擾
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	u32		�}�b�v�A�g���r���[�g
 */
//--------------------------------------------------------------
u32 FieldOBJ_NowMapAttrGet( CONST_FIELD_OBJ_PTR fldobj )
{
	return( fldobj->now_attr );
}

//--------------------------------------------------------------
/**
 * �ߋ��̃}�b�v�A�g���r���[�g���Z�b�g
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	attr	�Z�b�g����A�g���r���[�g
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_OldMapAttrSet( FIELD_OBJ_PTR fldobj, u32 attr )
{
	fldobj->old_attr = attr;
}

//--------------------------------------------------------------
/**
 * �ߋ��̃}�b�v�A�g���r���[�g���擾
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	u32		�}�b�v�A�g���r���[�g
 */
//--------------------------------------------------------------
u32 FieldOBJ_OldMapAttrGet( CONST_FIELD_OBJ_PTR fldobj )
{
	return( fldobj->old_attr );
}

//--------------------------------------------------------------
/**
 * FIELDSYS_WORK�擾
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	FIELDSYS_WORK	FIELDSYS_WORK *
 */
//--------------------------------------------------------------
FIELDSYS_WORK * FieldOBJ_FieldSysWorkGet( CONST_FIELD_OBJ_PTR fldobj )
{
	FIELD_OBJ_SYS_PTR fos;
	
	fos = FldOBJ_FieldOBJSysGet( fldobj );
	return( FieldOBJSys_FieldSysWorkGet(fos) );
}

//--------------------------------------------------------------
/**
 * TCB��{�v���C�I���e�B�擾
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	int		TCB��{�v���C�I���e�B
 */
//--------------------------------------------------------------
int FieldOBJ_TCBStandardPriorityGet( CONST_FIELD_OBJ_PTR fldobj )
{
	return( FieldOBJSys_TCBStandardPriorityGet(FieldOBJ_FieldOBJSysGet(fldobj)) );
}

//--------------------------------------------------------------
/**
 * �G�C���A�X���̃]�[��ID�擾�B�G�C���A�X���̓C�x���g�t���O���w��]�[��ID
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	int		�]�[��ID
 */
//--------------------------------------------------------------
int FieldOBJ_ZoneIDGetAlies( CONST_FIELD_OBJ_PTR fldobj )
{
	GF_ASSERT( FieldOBJ_StatusBitCheck_Alies(fldobj) == TRUE &&
			"FieldOBJ_ZoneIDGetAlies()alies�ł͖���" );
	return( FieldOBJ_EventFlagGet(fldobj) );
}

//==============================================================================
//	�t�B�[���hOBJ�V�X�e���@�X�e�[�^�X�r�b�g�Ȉ�
//==============================================================================
//--------------------------------------------------------------
/**
 * �t�B�[���hOBJ�S�̂̓�������S��~�B
 * ���쏈���A�`�揈�������S��~����B�A�j���[�V�����R�}���h�ɂ��������Ȃ��B
 * @param	fos		FIELD_OBJ_SYS_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJSys_MoveStopAll( FIELD_OBJ_SYS_PTR fos )
{
	FieldOBJSys_StatusBit_ON( fos,
		FLDOBJSYS_STA_BIT_MOVE_PROC_STOP | FLDOBJSYS_STA_BIT_DRAW_PROC_STOP );
	
	OS_Printf( "�t�B�[���hOBJ�S�̂̓�����~���܂���\n" );
}

//--------------------------------------------------------------
/**
 * �t�B�[���hOBJ�S�̂̓��슮�S��~������
 * @param	fos		FIELD_OBJ_SYS_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJSys_MoveStopAllClear( FIELD_OBJ_SYS_PTR fos )
{
	FieldOBJSys_StatusBit_OFF( fos,
		FLDOBJSYS_STA_BIT_MOVE_PROC_STOP | FLDOBJSYS_STA_BIT_DRAW_PROC_STOP );
	
	OS_Printf( "�t�B�[���hOBJ�S�̂̓����~���������܂���\n" );
}

//--------------------------------------------------------------
/**
 * �t�B�[���hOBJ�S�̂̓�����ꎞ��~
 * �ŗL�̓��쏈���i�����_���ړ����j���ꎞ��~����B
 * �A�j���[�V�����R�}���h�ɂ͔�������B
 * @param	fos		FIELD_OBJ_SYS_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJSys_MovePauseAll( FIELD_OBJ_SYS_PTR fos )
{
	int max = FieldOBJSys_OBJMaxGet( fos );
	FIELD_OBJ_PTR fldobj = FieldOBJSys_FldOBJWorkGet( fos );
	
	do{
		if( FieldOBJ_StatusBitCheck_Use(fldobj) ){
			FieldOBJ_MovePause( fldobj );
		}
		
		fldobj++;
		max--;
	}while( max );
	
	OS_Printf( "�t�B�[���hOBJ�S�̓�����|�[�Y���܂���\n" );
}

//--------------------------------------------------------------
/**
 * �t�B�[���hOBJ�S�̓���ꎞ��~������
 * @param	fos		FIELD_OBJ_SYS_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJSys_MovePauseAllClear( FIELD_OBJ_SYS_PTR fos )
{
	int max = FieldOBJSys_OBJMaxGet( fos );
	FIELD_OBJ_PTR fldobj = FieldOBJSys_FldOBJWorkGet( fos );
	
	do{
		if( FieldOBJ_StatusBitCheck_Use(fldobj) ){
			FieldOBJ_MovePauseClear( fldobj );
		}
		
		fldobj++;
		max--;
	}while( max );
	
	OS_Printf( "�t�B�[���hOBJ�S�̓���|�[�Y���������܂���\n" );
}

//--------------------------------------------------------------
/**
 * �`�揈��������������Ă��邩�ǂ����`�F�b�N
 * @param	fos				FIELD_OBJ_SYS_PTR
 * @retval	int				TRUE=����������Ă���
 */
//--------------------------------------------------------------
int FieldOBJSys_DrawInitCompCheck( CONST_FIELD_OBJ_SYS_PTR fos )
{
	if( FieldOBJSys_StatusBit_Check(fos,FLDOBJSYS_STA_BIT_DRAW_INIT_COMP) ){
		return( TRUE );
	}
	
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * �t�B�[���hOBJ����t�B�[���hOBJ�V�X�e���̃r�b�g�`�F�b�N
 * @param	fldobj		FIELD_OBJ_PTR
 * @param	bit			FLDOBJSYS_STA_BIT_DRAW_INIT_COMP��
 * @retval	u32			0�ȊO bit�q�b�g
 */
//--------------------------------------------------------------
u32 FieldOBJ_FieldOBJSysStatusBitCheck( CONST_FIELD_OBJ_PTR fldobj, u32 bit )
{
	CONST_FIELD_OBJ_SYS_PTR fos = FieldOBJ_FieldOBJSysGet( fldobj );
	return( FieldOBJSys_StatusBit_Check(fos,bit) );
}

//--------------------------------------------------------------
/**
 * �e��t����A�t���Ȃ��̃Z�b�g
 * @param	fos		FIELD_OBJ_SYS_PTR
 * @param	flag	TRUE=�e��t���� FALSE=�e��t���Ȃ�
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJSys_ShadowJoinSet( FIELD_OBJ_SYS_PTR fos, int flag )
{
	if( flag == FALSE ){
		FieldOBJSys_StatusBit_ON( fos, FLDOBJSYS_STA_BIT_SHADOW_JOIN_NOT );
	}else{
		FieldOBJSys_StatusBit_OFF( fos, FLDOBJSYS_STA_BIT_SHADOW_JOIN_NOT );
	}
}

//--------------------------------------------------------------
/**
 * �e��t����A�t���Ȃ��̃`�F�b�N
 * @param	fos		FIELD_OBJ_SYS_PTR
 * @retval	int		FALSE=�t���Ȃ�
 */
//--------------------------------------------------------------
int FieldOBJSys_ShadowJoinCheck( CONST_FIELD_OBJ_SYS_PTR fos )
{
	if( FieldOBJSys_StatusBit_Check(fos,FLDOBJSYS_STA_BIT_SHADOW_JOIN_NOT) ){
		return( FALSE );
	}
	
	return( TRUE );
}

//==============================================================================
//	�t�B�[���hOBJ �X�e�[�^�X�r�b�g�Ȉ�
//==============================================================================
//--------------------------------------------------------------
/**
 * �g�p�`�F�b�N
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	int		TRUE=�g�p��
 */
//--------------------------------------------------------------
int FieldOBJ_StatusBitCheck_Use( CONST_FIELD_OBJ_PTR fldobj )
{
	return( FieldOBJ_StatusBit_CheckEasy(fldobj,FLDOBJ_STA_BIT_USE) );
}

//--------------------------------------------------------------
/**
 * �ړ����쒆�ɂ���
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_StatusBitON_Move( FIELD_OBJ_PTR fldobj )
{
	FieldOBJ_StatusBit_ON( fldobj, FLDOBJ_STA_BIT_MOVE );
}

//--------------------------------------------------------------
/**
 * �ړ����쒆������
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_StatusBitOFF_Move( FIELD_OBJ_PTR fldobj )
{
	FieldOBJ_StatusBit_OFF( fldobj, FLDOBJ_STA_BIT_MOVE );
}

//--------------------------------------------------------------
/**
 * �ړ����쒆�`�F�b�N
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	int		TRUE=���쒆
 */
//--------------------------------------------------------------
int FieldOBJ_StatusBitCheck_Move( CONST_FIELD_OBJ_PTR fldobj )
{
	return( FieldOBJ_StatusBit_CheckEasy(fldobj,FLDOBJ_STA_BIT_MOVE) );
}

//--------------------------------------------------------------
/**
 * �ړ�����J�n�ɂ���
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_StatusBitON_MoveStart( FIELD_OBJ_PTR fldobj )
{
	FieldOBJ_StatusBit_ON( fldobj, FLDOBJ_STA_BIT_MOVE_START );
}

//--------------------------------------------------------------
/**
 * �ړ�����J�n������
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_StatusBitOFF_MoveStart( FIELD_OBJ_PTR fldobj )
{
	FieldOBJ_StatusBit_OFF( fldobj, FLDOBJ_STA_BIT_MOVE_START );
}

//--------------------------------------------------------------
/**
 * �ړ�����J�n�`�F�b�N
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	int		TRUE=�ړ�����J�n
 */
//--------------------------------------------------------------
int FieldOBJ_StatusBitCheck_MoveStart( CONST_FIELD_OBJ_PTR fldobj )
{
	return( FieldOBJ_StatusBit_CheckEasy(fldobj,FLDOBJ_STA_BIT_MOVE_START) );
}

//--------------------------------------------------------------
/**
 * �ړ�����I���ɂ���
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_StatusBitON_MoveEnd( FIELD_OBJ_PTR fldobj )
{
	FieldOBJ_StatusBit_ON( fldobj, FLDOBJ_STA_BIT_MOVE_END );
}

//--------------------------------------------------------------
/**
 * �ړ�����I��������
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_StatusBitOFF_MoveEnd( FIELD_OBJ_PTR fldobj )
{
	FieldOBJ_StatusBit_OFF( fldobj, FLDOBJ_STA_BIT_MOVE_END );
}

//--------------------------------------------------------------
/**
 * �ړ�����I���`�F�b�N
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	int		TRUE=�ړ��I��
 */
//--------------------------------------------------------------
int FieldOBJ_StatusBitCheck_MoveEnd( CONST_FIELD_OBJ_PTR fldobj )
{
	return( FieldOBJ_StatusBit_CheckEasy(fldobj,FLDOBJ_STA_BIT_MOVE_END) );
}

//--------------------------------------------------------------
/**
 * �`�揉���������ɂ���
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_StatusBitON_DrawProcInitComp( FIELD_OBJ_PTR fldobj )
{
	FieldOBJ_StatusBit_ON( fldobj, FLDOBJ_STA_BIT_DRAW_PROC_INIT_COMP );
}

//--------------------------------------------------------------
/**
 * �`�揉��������������
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_StatusBitOFF_DrawProcInitComp( FIELD_OBJ_PTR fldobj )
{
	FieldOBJ_StatusBit_OFF( fldobj, FLDOBJ_STA_BIT_DRAW_PROC_INIT_COMP );
}

//--------------------------------------------------------------
/**
 * �`�揉���������`�F�b�N
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	int		TRUE=�`�揉��������
 */
//--------------------------------------------------------------
int FieldOBJ_StatusBitCheck_DrawProcInitComp( CONST_FIELD_OBJ_PTR fldobj )
{
	return( FieldOBJ_StatusBit_CheckEasy(fldobj,FLDOBJ_STA_BIT_DRAW_PROC_INIT_COMP) );
}

//--------------------------------------------------------------
/**
 * ��\���t���O���`�F�b�N
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	flag	TRUE=��\���@FALSE=�\��
 * @retval	nothing
 */
//--------------------------------------------------------------
int FieldOBJ_StatusBitCheck_Vanish( CONST_FIELD_OBJ_PTR fldobj )
{
	return( FieldOBJ_StatusBit_CheckEasy(fldobj,FLDOBJ_STA_BIT_VANISH) );
}

//--------------------------------------------------------------
/**
 * ��\���t���O��ݒ�
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	flag	TRUE=��\���@FALSE=�\��
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_StatusBitSet_Vanish( FIELD_OBJ_PTR fldobj, int flag )
{
	if( flag == TRUE ){
		FieldOBJ_StatusBit_ON( fldobj, FLDOBJ_STA_BIT_VANISH );
	}else{
		FieldOBJ_StatusBit_OFF( fldobj, FLDOBJ_STA_BIT_VANISH );
	}
}

//--------------------------------------------------------------
/**
 * OBJ���m�̓����蔻��t���O��ݒ�
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	flag	TRUE=�q�b�g�A���@FALSE=�q�b�g�i�V
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_StatusBitSet_FellowHit( FIELD_OBJ_PTR fldobj, int flag )
{
	if( flag == TRUE ){
		FieldOBJ_StatusBit_OFF( fldobj, FLDOBJ_STA_BIT_FELLOW_HIT_NON );
	}else{
		FieldOBJ_StatusBit_ON( fldobj, FLDOBJ_STA_BIT_FELLOW_HIT_NON );
	}
}

//--------------------------------------------------------------
/**
 * ���쒆�t���O�̃Z�b�g
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	flag	TRUE=���쒆�@FALSE=��~��
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_StatusBitSet_Move( FIELD_OBJ_PTR fldobj, int flag )
{
	if( flag == TRUE ){
		FieldOBJ_StatusBitON_Move( fldobj );
	}else{
		FieldOBJ_StatusBitOFF_Move( fldobj );
	}
}

//--------------------------------------------------------------
/**
 * �b�������\�`�F�b�N
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	int		TRUE=�\ FALSE=�s��
 */
//--------------------------------------------------------------
int FieldOBJ_StatusBitCheck_Talk( FIELD_OBJ_PTR fldobj )
{
	if( FieldOBJ_StatusBit_CheckEasy(fldobj,FLDOBJ_STA_BIT_TALK_OFF) == TRUE ){
		return( FALSE );
	}
	
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * �b�������s�t���O���Z�b�g
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	flag	TRUE=�s�� FALSE=�\
 */
//--------------------------------------------------------------
void FieldOBJ_StatusBitSet_TalkOFF( FIELD_OBJ_PTR fldobj, int flag )
{
	if( flag == TRUE ){
		FieldOBJ_StatusBit_ON( fldobj, FLDOBJ_STA_BIT_TALK_OFF );
	}else{
		FieldOBJ_StatusBit_OFF( fldobj, FLDOBJ_STA_BIT_TALK_OFF );
	}
}

//--------------------------------------------------------------
/**
 * ����|�[�Y
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_MovePause( FIELD_OBJ_PTR fldobj )
{
	FieldOBJ_StatusBit_ON( fldobj, FLDOBJ_STA_BIT_PAUSE_MOVE );
}

//--------------------------------------------------------------
/**
 * ����|�[�Y����
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_MovePauseClear( FIELD_OBJ_PTR fldobj )
{
	FieldOBJ_StatusBit_OFF( fldobj, FLDOBJ_STA_BIT_PAUSE_MOVE );
}

//--------------------------------------------------------------
/**
 * ����|�[�Y�`�F�b�N
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	int		TRUE=����|�[�Y
 */
//--------------------------------------------------------------
int FieldOBJ_MovePauseCheck( CONST_FIELD_OBJ_PTR fldobj )
{
	if( FieldOBJ_StatusBit_CheckEasy(fldobj,FLDOBJ_STA_BIT_PAUSE_MOVE) == TRUE ){
		return( TRUE );
	}
	
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * �X�e�[�^�X�r�b�g �`�揈�������������`�F�b�N
 * @param	fldobj		FIELD_OBJ_PTR
 * @retval	int			TRUE=�����BFALSE=�܂�
 */
//--------------------------------------------------------------
int FieldOBJ_StatusBit_DrawInitCompCheck( CONST_FIELD_OBJ_PTR fldobj )
{
	CONST_FIELD_OBJ_SYS_PTR fos;
	
	fos = FieldOBJ_FieldOBJSysGet( fldobj );
	
	if( FieldOBJSys_DrawInitCompCheck(fos) == FALSE ){
		return( FALSE );
	}
	
	if( FieldOBJ_StatusBit_Check(fldobj,FLDOBJ_STA_BIT_DRAW_PROC_INIT_COMP) == 0 ){
		return( FALSE );
	}
	
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * �����擾���֎~����
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	int		TRUE=�����擾OFF FALSE=ON
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_StatusBitSet_HeightGetOFF( FIELD_OBJ_PTR fldobj, int flag )
{
	if( flag == TRUE ){
		FieldOBJ_StatusBit_ON( fldobj, FLDOBJ_STA_BIT_HEIGHT_GET_OFF );
	}else{
		FieldOBJ_StatusBit_OFF( fldobj, FLDOBJ_STA_BIT_HEIGHT_GET_OFF );
	}
}

//--------------------------------------------------------------
/**
 * �����擾���֎~����Ă��邩�`�F�b�N
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	int		TRUE=�֎~
 */
//--------------------------------------------------------------
int FieldOBJ_HeightOFFCheck( CONST_FIELD_OBJ_PTR fldobj )
{
	if( FieldOBJ_StatusBit_Check(fldobj,FLDOBJ_STA_BIT_HEIGHT_GET_OFF) ){
		return( TRUE );
	}
	
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * �]�[���؂�ւ����̍폜�֎~
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	flag	TRUE=�֎~ FALSE=�֎~���Ȃ�
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_NotZoneDeleteSet( FIELD_OBJ_PTR fldobj, int flag )
{
	if( flag == TRUE ){
		FieldOBJ_StatusBit_ON( fldobj, FLDOBJ_STA_BIT_ZONE_DEL_NOT );
	}else{
		FieldOBJ_StatusBit_OFF( fldobj, FLDOBJ_STA_BIT_ZONE_DEL_NOT );
	}
}

//--------------------------------------------------------------
/**
 * �G�C���A�X�t���O���Z�b�g
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	flag	TRUE=�G�C���A�X FALSE=�Ⴄ
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_StatusBitSet_Alies( FIELD_OBJ_PTR fldobj, int flag )
{
	if( flag == TRUE ){
		FieldOBJ_StatusBit_ON( fldobj, FLDOBJ_STA_BIT_ALIES );
	}else{
		FieldOBJ_StatusBit_OFF( fldobj, FLDOBJ_STA_BIT_ALIES );
	}
}

//--------------------------------------------------------------
/**
 * �G�C���A�X�t���O���`�F�b�N
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	flag	TRUE=�G�C���A�X FALSE=�Ⴄ
 */
//--------------------------------------------------------------
int FieldOBJ_StatusBitCheck_Alies( CONST_FIELD_OBJ_PTR fldobj )
{
	if( FieldOBJ_StatusBit_Check(fldobj,FLDOBJ_STA_BIT_ALIES) ){
		return( TRUE );
	}
	
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * �󐣃G�t�F�N�g�Z�b�g�t���O���Z�b�g
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	flag	TRUE=�Z�b�g�@FALSE=�N���A
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_StatusBitSet_ShoalEffectSet( FIELD_OBJ_PTR fldobj, int flag )
{
	if( flag == TRUE ){
		FieldOBJ_StatusBit_ON( fldobj, FLDOBJ_STA_BIT_EFFSET_SHOAL );
	}else{
		FieldOBJ_StatusBit_OFF( fldobj, FLDOBJ_STA_BIT_EFFSET_SHOAL );
	}
}

//--------------------------------------------------------------
/**
 * �󐣃G�t�F�N�g�Z�b�g�t���O���`�F�b�N
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	flag	TRUE=�Z�b�g�@FALSE=�Ⴄ
 */
//--------------------------------------------------------------
int FieldOBJ_StatusBitCheck_ShoalEffectSet( CONST_FIELD_OBJ_PTR fldobj )
{
	if( FieldOBJ_StatusBit_Check(fldobj,FLDOBJ_STA_BIT_EFFSET_SHOAL) ){
		return( TRUE );
	}
	
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * �A�g���r���[�g�I�t�Z�b�g�ݒ�OFF�Z�b�g
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	flag	TRUE=�Z�b�g�@FALSE=�N���A
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_StatusBitSet_AttrOffsOFF( FIELD_OBJ_PTR fldobj, int flag )
{
	if( flag == TRUE ){
		FieldOBJ_StatusBit_ON( fldobj, FLDOBJ_STA_BIT_ATTR_OFFS_OFF );
	}else{
		FieldOBJ_StatusBit_OFF( fldobj, FLDOBJ_STA_BIT_ATTR_OFFS_OFF );
	}
}

//--------------------------------------------------------------
/**
 * �A�g���r���[�g�I�t�Z�b�g�ݒ�OFF�`�F�b�N
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	flag	TRUE=OFF�@FALSE=�Ⴄ
 */
//--------------------------------------------------------------
int FieldOBJ_StatusBitCheck_AttrOffsOFF( CONST_FIELD_OBJ_PTR fldobj )
{
	if( FieldOBJ_StatusBit_Check(fldobj,FLDOBJ_STA_BIT_ATTR_OFFS_OFF) ){
		return( TRUE );
	}
	
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * ���ړ��t���O�Z�b�g
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	flag	TRUE=�Z�b�g�@FALSE=�N���A
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_StatusBitSet_Bridge( FIELD_OBJ_PTR fldobj, int flag )
{
	if( flag == TRUE ){
		FieldOBJ_StatusBit_ON( fldobj, FLDOBJ_STA_BIT_BRIDGE );
	}else{
		FieldOBJ_StatusBit_OFF( fldobj, FLDOBJ_STA_BIT_BRIDGE );
	}
}

//--------------------------------------------------------------
/**
 * ���ړ��t���O�`�F�b�N
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	flag	TRUE=���@FALSE=�Ⴄ
 */
//--------------------------------------------------------------
int FieldOBJ_StatusBitCheck_Bridge( CONST_FIELD_OBJ_PTR fldobj )
{
	if( FieldOBJ_StatusBit_Check(fldobj,FLDOBJ_STA_BIT_BRIDGE) ){
		return( TRUE );
	}
	
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * �f�肱�݃t���O�Z�b�g
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	flag	TRUE=�Z�b�g�@FALSE=�N���A
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_StatusBitSet_Reflect( FIELD_OBJ_PTR fldobj, int flag )
{
	if( flag == TRUE ){
		FieldOBJ_StatusBit_ON( fldobj, FLDOBJ_STA_BIT_REFLECT_SET );
	}else{
		FieldOBJ_StatusBit_OFF( fldobj, FLDOBJ_STA_BIT_REFLECT_SET );
	}
}

//--------------------------------------------------------------
/**
 * �f�肱�݃t���O�`�F�b�N
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	flag	TRUE=�Z�b�g�@FALSE=����
 */
//--------------------------------------------------------------
int FieldOBJ_StatusBitCheck_Reflect( CONST_FIELD_OBJ_PTR fldobj )
{
	if( FieldOBJ_StatusBit_Check(fldobj,FLDOBJ_STA_BIT_REFLECT_SET) ){
		return( TRUE );
	}
	
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * �A�j���[�V�����R�}���h�`�F�b�N
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	flag	TRUE=�R�}���h�A���@FALSE=����
 */
//--------------------------------------------------------------
int FieldOBJ_StatusBitCheck_Acmd( CONST_FIELD_OBJ_PTR fldobj )
{
	if( FieldOBJ_StatusBit_Check(fldobj,FLDOBJ_STA_BIT_ACMD) ){
		return( TRUE );
	}
	
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * �g�����������t���O���Z�b�g
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	flag	TRUE=�Z�b�g�@FALSE=�N���A
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_StatusBitSet_HeightExpand( FIELD_OBJ_PTR fldobj, int flag )
{
	if( flag == TRUE ){
		FieldOBJ_StatusBit_ON( fldobj, FLDOBJ_STA_BIT_HEIGHT_EXPAND );
	}else{
		FieldOBJ_StatusBit_OFF( fldobj, FLDOBJ_STA_BIT_HEIGHT_EXPAND );
	}
}

//--------------------------------------------------------------
/**
 * �g�����������t���O�`�F�b�N
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	flag	TRUE=�g�������ɔ�������@FALSE=����
 */
//--------------------------------------------------------------
int FieldOBJ_StatusBitCheck_HeightExpand( CONST_FIELD_OBJ_PTR fldobj )
{
	if( FieldOBJ_StatusBit_Check(fldobj,FLDOBJ_STA_BIT_HEIGHT_EXPAND) ){
		return( TRUE );
	}
	
	return( FALSE );
}

//==============================================================================
//	���W�n�Q��
//==============================================================================
//--------------------------------------------------------------
/**
 * �������W X���W�擾
 * @param	fldobj	FIELD_OBJ_PTR 
 * @retval	int		X���W
 */
//--------------------------------------------------------------
int FieldOBJ_InitPosGX_Get( CONST_FIELD_OBJ_PTR fldobj )
{
	return( fldobj->gx_init );
}

//--------------------------------------------------------------
/**
 * �������W X���W�Z�b�g
 * @param	fldobj	FIELD_OBJ_PTR 
 * @param	x		�Z�b�g������W
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_InitPosGX_Set( FIELD_OBJ_PTR fldobj, int x )
{
	fldobj->gx_init = x;
}

//--------------------------------------------------------------
/**
 * �������W Y���W�擾
 * @param	fldobj	FIELD_OBJ_PTR 
 * @retval	int		Y
 */
//--------------------------------------------------------------
int FieldOBJ_InitPosGY_Get( CONST_FIELD_OBJ_PTR fldobj )
{
	return( fldobj->gy_init );
}

//--------------------------------------------------------------
/**
 * �������W Y���W�Z�b�g
 * @param	fldobj	FIELD_OBJ_PTR 
 * @param	y		�Z�b�g������W
 * @retval	int		y���W
 */
//--------------------------------------------------------------
void FieldOBJ_InitPosGY_Set( FIELD_OBJ_PTR fldobj, int y )
{
	fldobj->gy_init = y;
}

//--------------------------------------------------------------
/**
 * �������W z���W�擾
 * @param	fldobj	FIELD_OBJ_PTR 
 * @retval	int		z���W
 */
//--------------------------------------------------------------
int FieldOBJ_InitPosGZ_Get( CONST_FIELD_OBJ_PTR fldobj )
{
	return( fldobj->gz_init );
}

//--------------------------------------------------------------
/**
 * �������W z���W�Z�b�g
 * @param	fldobj	FIELD_OBJ_PTR 
 * @param	z		�Z�b�g������W
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_InitPosGZ_Set( FIELD_OBJ_PTR fldobj, int z )
{
	fldobj->gz_init = z;
}

//--------------------------------------------------------------
/**
 * �ߋ����W�@X���W�擾
 * @param	fldobj	FIELD_OBJ_PTR 
 * @retval	int		X���W
 */
//--------------------------------------------------------------
int FieldOBJ_OldPosGX_Get( CONST_FIELD_OBJ_PTR fldobj )
{
	return( fldobj->gx_old );
}

//--------------------------------------------------------------
/**
 * �ߋ����W X���W�Z�b�g
 * @param	fldobj	FIELD_OBJ_PTR 
 * @param	x		�Z�b�g������W
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_OldPosGX_Set( FIELD_OBJ_PTR fldobj, int x )
{
	fldobj->gx_old = x;
}

//--------------------------------------------------------------
/**
 * �ߋ����W Y���W�擾
 * @param	fldobj	FIELD_OBJ_PTR 
 * @retval	int		Y
 */
//--------------------------------------------------------------
int FieldOBJ_OldPosGY_Get( CONST_FIELD_OBJ_PTR fldobj )
{
	return( fldobj->gy_old );
}

//--------------------------------------------------------------
/**
 * �ߋ����W Y���W�Z�b�g
 * @param	fldobj	FIELD_OBJ_PTR 
 * @param	y		�Z�b�g������W
 * @retval	int		y���W
 */
//--------------------------------------------------------------
void FieldOBJ_OldPosGY_Set( FIELD_OBJ_PTR fldobj, int y )
{
	fldobj->gy_old = y;
}

//--------------------------------------------------------------
/**
 * �ߋ����W z���W�擾
 * @param	fldobj	FIELD_OBJ_PTR 
 * @retval	int		z���W
 */
//--------------------------------------------------------------
int FieldOBJ_OldPosGZ_Get( CONST_FIELD_OBJ_PTR fldobj )
{
	return( fldobj->gz_old );
}

//--------------------------------------------------------------
/**
 * �ߋ����W z���W�Z�b�g
 * @param	fldobj	FIELD_OBJ_PTR 
 * @param	z		�Z�b�g������W
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_OldPosGZ_Set( FIELD_OBJ_PTR fldobj, int z )
{
	fldobj->gz_old = z;
}

//--------------------------------------------------------------
/**
 * ���ݍ��W X���W�擾
 * @param	fldobj	FIELD_OBJ_PTR 
 * @retval	int		X���W
 */
//--------------------------------------------------------------
int FieldOBJ_NowPosGX_Get( CONST_FIELD_OBJ_PTR fldobj )
{
	return( fldobj->gx_now );
}

//--------------------------------------------------------------
/**
 * ���ݍ��W X���W�Z�b�g
 * @param	fldobj	FIELD_OBJ_PTR 
 * @param	x		�Z�b�g������W
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_NowPosGX_Set( FIELD_OBJ_PTR fldobj, int x )
{
	fldobj->gx_now = x;
}

//--------------------------------------------------------------
/**
 * ���ݍ��W X���W����
 * @param	fldobj	FIELD_OBJ_PTR 
 * @param	x		�����l
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_NowPosGX_Add( FIELD_OBJ_PTR fldobj, int x )
{
	fldobj->gx_now += x;
}

//--------------------------------------------------------------
/**
 * ���ݍ��W Y���W�擾
 * @param	fldobj	FIELD_OBJ_PTR 
 * @retval	int		Y
 */
//--------------------------------------------------------------
int FieldOBJ_NowPosGY_Get( CONST_FIELD_OBJ_PTR fldobj )
{
	return( fldobj->gy_now );
}

//--------------------------------------------------------------
/**
 * ���ݍ��W Y���W�Z�b�g
 * @param	fldobj	FIELD_OBJ_PTR 
 * @param	y		�Z�b�g������W
 * @retval	int		y���W
 */
//--------------------------------------------------------------
void FieldOBJ_NowPosGY_Set( FIELD_OBJ_PTR fldobj, int y )
{
	fldobj->gy_now = y;
}

//--------------------------------------------------------------
/**
 * ���ݍ��W Y���W����
 * @param	fldobj	FIELD_OBJ_PTR 
 * @param	y		�����l
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_NowPosGY_Add( FIELD_OBJ_PTR fldobj, int y )
{
	fldobj->gy_now += y;
}

//--------------------------------------------------------------
/**
 * �ߋ����W z���W�擾
 * @param	fldobj	FIELD_OBJ_PTR 
 * @retval	int		z���W
 */
//--------------------------------------------------------------
int FieldOBJ_NowPosGZ_Get( CONST_FIELD_OBJ_PTR fldobj )
{
	return( fldobj->gz_now );
}

//--------------------------------------------------------------
/**
 * ���ݍ��W z���W�Z�b�g
 * @param	fldobj	FIELD_OBJ_PTR 
 * @param	z		�Z�b�g������W
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_NowPosGZ_Set( FIELD_OBJ_PTR fldobj, int z )
{
	fldobj->gz_now = z;
}

//--------------------------------------------------------------
/**
 * ���ݍ��W z���W����
 * @param	fldobj	FIELD_OBJ_PTR 
 * @param	z		�����l
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_NowPosGZ_Add( FIELD_OBJ_PTR fldobj, int z )
{
	fldobj->gz_now += z;
}

//--------------------------------------------------------------
/**
 * �����W�擾
 * @param	fldobj	FIELD_OBJ_PTR 
 * @param	vec		���W�i�[��
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_VecPosGet( CONST_FIELD_OBJ_PTR fldobj, VecFx32 *vec )
{
	*vec = fldobj->vec_pos_now;
}

//--------------------------------------------------------------
/**
 * �����W�Z�b�g
 * @param	fldobj	FIELD_OBJ_PTR 
 * @param	vec		�Z�b�g���W
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_VecPosSet( FIELD_OBJ_PTR fldobj, const VecFx32 *vec )
{
	fldobj->vec_pos_now = *vec;
}

//--------------------------------------------------------------
/**
 * �����W�|�C���^�擾
 * @param	fldobj	FIELD_OBJ_PTR 
 * @retval	VecFx32	�����W�|�C���^
 */
//--------------------------------------------------------------
const VecFx32 * FieldOBJ_VecPosPtrGet( CONST_FIELD_OBJ_PTR fldobj )
{
	return( &fldobj->vec_pos_now );
}

//--------------------------------------------------------------
/**
 * �����WY�l�擾
 * @param	fldobj	FIELD_OBJ_PTR 
 * @retval	fx32	����
 */
//--------------------------------------------------------------
fx32 FieldOBJ_VecPosYGet( CONST_FIELD_OBJ_PTR fldobj )
{
	return( fldobj->vec_pos_now.y );
}

//--------------------------------------------------------------
/**
 * �\�����W�I�t�Z�b�g�擾
 * @param	fldobj	FIELD_OBJ_PTR 
 * @param	vec		�Z�b�g���W
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_VecDrawOffsGet( CONST_FIELD_OBJ_PTR fldobj, VecFx32 *vec )
{
	*vec = fldobj->vec_draw_offs;
}

//--------------------------------------------------------------
/**
 * �\�����W�I�t�Z�b�g�Z�b�g
 * @param	fldobj	FIELD_OBJ_PTR 
 * @param	vec		�Z�b�g���W
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_VecDrawOffsSet( FIELD_OBJ_PTR fldobj, const VecFx32 *vec )
{
	fldobj->vec_draw_offs = *vec;
}

//--------------------------------------------------------------
/**
 * �\�����W�I�t�Z�b�g�|�C���^�擾
 * @param	fldobj		FIELD_OBJ_PTR 
 * @retval	VecFx32		�I�t�Z�b�g�|�C���^
 */
//--------------------------------------------------------------
VecFx32 * FieldOBJ_VecDrawOffsPtrGet( FIELD_OBJ_PTR fldobj )
{
	return( &fldobj->vec_draw_offs );
}

//--------------------------------------------------------------
/**
 * �O���w��\�����W�I�t�Z�b�g�擾
 * @param	fldobj	FIELD_OBJ_PTR 
 * @param	vec		�Z�b�g���W
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_VecDrawOffsOutSideGet( CONST_FIELD_OBJ_PTR fldobj, VecFx32 *vec )
{
	*vec = fldobj->vec_draw_offs_outside;
}

//--------------------------------------------------------------
/**
 * �O���w��\�����W�I�t�Z�b�g�Z�b�g
 * @param	fldobj	FIELD_OBJ_PTR 
 * @param	vec		�Z�b�g���W
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_VecDrawOffsOutSideSet( FIELD_OBJ_PTR fldobj, const VecFx32 *vec )
{
	fldobj->vec_draw_offs_outside = *vec;
}

//--------------------------------------------------------------
/**
 * �A�g���r���[�g�ω����W�I�t�Z�b�g�擾
 * @param	fldobj	FIELD_OBJ_PTR 
 * @param	vec		�Z�b�g���W
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_VecAttrOffsGet( CONST_FIELD_OBJ_PTR fldobj, VecFx32 *vec )
{
	*vec = fldobj->vec_attr_offs;
}

//--------------------------------------------------------------
/**
 * �A�g���r���[�g�ω����W�I�t�Z�b�g�Z�b�g
 * @param	fldobj	FIELD_OBJ_PTR 
 * @param	vec		�Z�b�g���W
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_VecAttrOffsSet( FIELD_OBJ_PTR fldobj, const VecFx32 *vec )
{
	fldobj->vec_attr_offs = *vec;
}

//--------------------------------------------------------------
/**
 * ����(�O���b�h�P��)���擾
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	int		�����BH_GRID�P��
 */
//--------------------------------------------------------------
int FieldOBJ_HeightGridGet( CONST_FIELD_OBJ_PTR fldobj )
{
	fx32 y = FieldOBJ_VecPosYGet( fldobj );
	int gy = SIZE_H_GRID_FX32( y );
	return( gy );
}

//==============================================================================
//	FIELD_OBJ_H	�Q��
//==============================================================================
//--------------------------------------------------------------
/**
 * ID �Z�b�g
 * @param	head	FIELD_OBJ_H
 * @param	id		OBJ ID
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_H_IDSet( FIELD_OBJ_H *head, int id )
{
	head->id = id;
}

//--------------------------------------------------------------
/**
 * ID �擾
 * @param	head	FIELD_OBJ_H
 * @retval	u32		ID
 */
//--------------------------------------------------------------
int FieldOBJ_H_IDGet( const FIELD_OBJ_H *head )
{
	return( head->id );
}

//--------------------------------------------------------------
/**
 * OBJ�R�[�h�Z�b�g
 * @param	head	FIELD_OBJ_H
 * @param	code	HERO��
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_H_OBJCodeSet( FIELD_OBJ_H *head, int code )
{
	head->obj_code = code;
}

//--------------------------------------------------------------
/**
 * OBJ�R�[�h�擾
 * @param	head	FIELD_OBJ_H
 * @retval	int		OBJ�R�[�h
 */
//--------------------------------------------------------------
int FieldOBJ_H_OBJCodeGet( const FIELD_OBJ_H *head )
{
	return( head->obj_code );
}

//--------------------------------------------------------------
/**
 * ����R�[�h�Z�b�g
 * @param	head	FIELD_OBJ_H
 * @param	code	MV_DIR_RND��
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_H_MoveCodeSet( FIELD_OBJ_H *head, int code )
{
	head->move_code = code;
}

//--------------------------------------------------------------
/**
 * ����R�[�h�擾
 * @param	head	FIELD_OBJ_H
 * @retval	int		����R�[�h
 */
//--------------------------------------------------------------
int FieldOBJ_H_MoveCodeGet( const FIELD_OBJ_H *head )
{
	return( head->move_code );
}

//--------------------------------------------------------------
/**
 * �C�x���g�^�C�v�Z�b�g
 * @param	head	FIELD_OBJ_H
 * @param	type	�C�x���g�^�C�v
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_H_EventTypeSet( FIELD_OBJ_H *head, int type )
{
	head->event_type = type;
}

//--------------------------------------------------------------
/**
 * �C�x���g�^�C�v�擾
 * @param	head	FIELD_OBJ_H
 * @retval	int		�C�x���g�^�C�v
 */
//--------------------------------------------------------------
int FieldOBJ_H_EventTypeGet( const FIELD_OBJ_H *head )
{
	return( head->event_type );
}

//--------------------------------------------------------------
/**
 * �C�x���g�t���O�Z�b�g
 * @param	head	FIELD_OBJ_H
 * @param	flag	�C�x���g�t���O
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_H_EventFlagSet( FIELD_OBJ_H *head, int flag )
{
	head->event_flag = flag;
}

//--------------------------------------------------------------
/**
 * �C�x���g�t���O�擾
 * @param	head	FIELD_OBJ_H
 * @retval	int		�C�x���g�t���O
 */
//--------------------------------------------------------------
int FieldOBJ_H_EventFlagGet( const FIELD_OBJ_H *head )
{
	return( head->event_flag );
}

//--------------------------------------------------------------
/**
 * �C�x���gID�Z�b�g
 * @param	head	FIELD_OBJ_H
 * @param	id		�C�x���gID
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_H_EventIDSet( FIELD_OBJ_H *head, int id )
{
	head->event_id = id;
}

//--------------------------------------------------------------
/**
 * �C�x���gID�擾
 * @param	head	FIELD_OBJ_H
 * @retval	int		�C�x���g�t���O
 */
//--------------------------------------------------------------
int FieldOBJ_H_EventIDGet( const FIELD_OBJ_H *head )
{
	return( head->event_id );
}

//--------------------------------------------------------------
/**
 * �����Z�b�g
 * @param	head	FIELD_OBJ_H
 * @param	dir		DIR_UP��
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_H_DirSet( FIELD_OBJ_H *head, int dir )
{
	head->dir = dir;
}

//--------------------------------------------------------------
/**
 * �����擾
 * @param	head	FIELD_OBJ_H
 * @retval	int		����
 */
//--------------------------------------------------------------
int FieldOBJ_H_DirGet( const FIELD_OBJ_H *head )
{
	return( head->dir );
}

//--------------------------------------------------------------
/**
 * �w��p�����^�Z�b�g
 * @param	head	FIELD_OBJ_H
 * @param	param	�w��p�����^
 * @param	no		FLDOBJ_PARAM_0��
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_H_ParamSet( FIELD_OBJ_H *head, int param, FLDOBJ_H_PARAM no )
{
	switch( no ){
	case FLDOBJ_PARAM_0: head->param0 = param; break;
	case FLDOBJ_PARAM_1: head->param1 = param; break;
	case FLDOBJ_PARAM_2: head->param2 = param; break;
	default: GF_ASSERT( 0 && "FieldOBJ_H_ParamSet()�s���Ȉ���" );
	}
}

//--------------------------------------------------------------
/**
 * �w��p�����^�擾
 * @param	head	FIELD_OBJ_H
 * @param	no		�擾����p�����^�BFLDOBJ_PARAM_0��
 * @retval	int		�p�����^
 */
//--------------------------------------------------------------
int FieldOBJ_H_ParamGet( const FIELD_OBJ_H *head, FLDOBJ_H_PARAM no )
{
	switch( no ){
	case FLDOBJ_PARAM_0: return( head->param0 );
	case FLDOBJ_PARAM_1: return( head->param1 );
	case FLDOBJ_PARAM_2: return( head->param2 );
	}
	
	GF_ASSERT( 0 && "FieldOBJ_H_ParamGet()�s���Ȉ���" );
	return( 0 );
}

//--------------------------------------------------------------
/**
 * �ړ�����X�Z�b�g
 * @param	head	FIELD_OBJ_H
 * @param	x		�ړ�����X
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_H_MoveLimitXSet( FIELD_OBJ_H *head, int x )
{
	head->move_limit_x = x;
}

//--------------------------------------------------------------
/**
 * �ړ�����X�擾
 * @param	head	FIELD_OBJ_H
 * @retval	int		�ړ�����X
 */
//--------------------------------------------------------------
int FieldOBJ_H_MoveLimitXGet( const FIELD_OBJ_H *head )
{
	return( head->move_limit_x );
}

//--------------------------------------------------------------
/**
 * �ړ�����Z�Z�b�g
 * @param	head	FIELD_OBJ_H
 * @param	z		�ړ�����Z
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_H_MoveLimitZSet( FIELD_OBJ_H *head, int z )
{
	head->move_limit_z = z;
}

//--------------------------------------------------------------
/**
 * �ړ�����Z�擾
 * @param	head	FIELD_OBJ_H
 * @retval	int		�ړ�����Y
 */
//--------------------------------------------------------------
int FieldOBJ_H_MoveLimitZGet( const FIELD_OBJ_H *head )
{
	return( head->move_limit_z );
}

//--------------------------------------------------------------
/**
 * X���W�Z�b�g
 * @param	head	FIELD_OBJ_H
 * @param	x		X���W
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_H_PosXSet( FIELD_OBJ_H *head, int x )
{
	head->gx = x;
}

//--------------------------------------------------------------
/**
 * X���W�擾
 * @param	head	FIELD_OBJ_H
 * @retval	int		X���W
 */
//--------------------------------------------------------------
int FieldOBJ_H_PosXGet( const FIELD_OBJ_H *head )
{
	return( head->gx );
}

//--------------------------------------------------------------
/**
 * Y���W�Z�b�g
 * @param	head	FIELD_OBJ_H
 * @param	y		y���W
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_H_PosYSet( FIELD_OBJ_H *head, int y )
{
	head->gy = y;
}

//--------------------------------------------------------------
/**
 * Y���W�擾
 * @param	head	FIELD_OBJ_H
 * @retval	int		Y���W
 */
//--------------------------------------------------------------
int FieldOBJ_H_PosYGet( const FIELD_OBJ_H *head )
{
	return( head->gy );
}

//--------------------------------------------------------------
/**
 * Z���W�Z�b�g
 * @param	head	FIELD_OBJ_H
 * @param	z		Z���W
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_H_PosZSet( FIELD_OBJ_H *head, int z )
{
	head->gz = z;
}

//--------------------------------------------------------------
/**
 * Z���W�擾
 * @param	head	FIELD_OBJ_H
 * @retval	int		Y���W
 */
//--------------------------------------------------------------
int FieldOBJ_H_PosZGet( const FIELD_OBJ_H *head )
{
	return( head->gz );
}

//--------------------------------------------------------------
/**
 * �t�B�[���hOBJ�w�b�_�[�z�񂩂�w��ID���������w�b�_�[������
 * @param	id		�w�b�_�[ID
 * @param	max		head�v�f��
 * @param	head	�t�B�[���hOBJ�w�b�_�[�e�[�u��
 * @retval	FIELD_OBJ_H id������head���|�C���^�BNULL=��v����
 */
//--------------------------------------------------------------
static const FIELD_OBJ_H * FldOBJ_H_OBJIDSearch( int id, int max, const FIELD_OBJ_H *head )
{
	int i = 0;
	
	do{
		if( FldOBJ_H_AliesCheck(&head[i]) == FALSE ){
			if( FieldOBJ_H_IDGet(&head[i]) == id ){
				return( &head[i] );
			}
		}
		
		i++;
	}while( i < max );
	
	return( NULL );
}

//--------------------------------------------------------------
/**
 * �t�B�[���hOBJ�w�b�_�[�@�G�C���A�X�`�F�b�N
 * @param	head	FIELD_OBJ_H
 * @retval	int		TRUE=�G�C���A�X�@FALSE=�Ⴄ
 */
//--------------------------------------------------------------
static int FldOBJ_H_AliesCheck( const FIELD_OBJ_H *head )
{
	u16 id = (u16)FieldOBJ_H_EventIDGet( head );
	if( id == SP_SCRID_ALIES ){ return( TRUE ); }
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * �t�B�[���hOBJ�w�b�_�[�@�G�C���A�X���̃]�[��ID�擾�B
 * �G�C���A�X���̓C�x���g�t���O���]�[��ID�ɂȂ�
 * @param	head	FIELD_OBJ_H
 * @retval	int		�]�[��ID
 */
//--------------------------------------------------------------
static int FldOBJ_H_AliesZoneIDGet( const FIELD_OBJ_H *head )
{
	GF_ASSERT( FldOBJ_H_AliesCheck(head) == TRUE && "FldOBJ_H_AliesZoneIDGet()alies�ł͂Ȃ�" );
	return( FieldOBJ_H_EventFlagGet(head) );
}

//==============================================================================
//	FIELD_OBJ_MOVE_PROC �Q��
//==============================================================================
//--------------------------------------------------------------
/**
 * ����e�[�u������w��̃��X�g���o��
 * @param	nothing
 * @retval	FIELD_OBJ_MOVE_PROC_LIST	FIELD_OBJ_MOVE_PROC_LIST�e�[�u��
 */
//--------------------------------------------------------------
static const FIELD_OBJ_MOVE_PROC_LIST * FldOBJ_MoveProcListGet( u32 code )
{
	GF_ASSERT( code < MV_CODE_MAX );
	return( DATA_FieldOBJMoveProcListTbl[code] );
}

//--------------------------------------------------------------
/**
 * ����R�[�h�擾
 * @param	list 		FIELD_OBJ_MOVE_PROC_LIST
 * @retval	u32			MV_PLAYER��
 */
//--------------------------------------------------------------
static u32 FldOBJ_MoveProcList_MoveCodeGet( const FIELD_OBJ_MOVE_PROC_LIST *list )
{
	return( list->move_code );
}

//--------------------------------------------------------------
/**
 * �������֐��擾
 * @param	list FIELD_OBJ_MOVE_PROC_LIST
 * @retval	FIELD_OBJ_MOVE_PROC_INIT list�̏������֐�
 */
//--------------------------------------------------------------
static FIELD_OBJ_MOVE_PROC_INIT FldOBJ_MoveProcList_InitGet(
		const FIELD_OBJ_MOVE_PROC_LIST *list )
{
	return( list->init_proc );
}

//--------------------------------------------------------------
/**
 * ����֐��擾
 * @param	list FIELD_OBJ_MOVE_PROC_LIST
 * @retval	FIELD_OBJ_MOVE_PROC list�̓���֐�
 */
//--------------------------------------------------------------
static FIELD_OBJ_MOVE_PROC FldOBJ_MoveProcList_MoveGet( const FIELD_OBJ_MOVE_PROC_LIST *list )
{
	return( list->move_proc );
}

//--------------------------------------------------------------
/**
 * �폜�֐��擾
 * @param	list FIELD_OBJ_MOVE_PROC_LIST
 * @retval	FIELD_OBJ_MOVE_PROC_DEL list�̓���֐�
 */
//--------------------------------------------------------------
static FIELD_OBJ_MOVE_PROC_DEL FldOBJ_MoveProcList_DeleteGet(
		const FIELD_OBJ_MOVE_PROC_LIST *list )
{
	return( list->delete_proc );
}

//==============================================================================
//	FIELD_OBJ_DRAW_PROC_LIST FIELD_OBJ_DRAW_PROC_LIST_REG�Q��
//==============================================================================
//--------------------------------------------------------------
/**
 * �������֐��擾
 * @param	list	FIELD_OBJ_DRAW_PROC_LIST *
 * @retval	FIELD_OBJ_DRAW_PROC_INIT	FIELD_OBJ_DRAW_PROC_INIT *
 */
//--------------------------------------------------------------
static FIELD_OBJ_DRAW_PROC_INIT FldOBJ_DrawProcList_InitGet(
	const FIELD_OBJ_DRAW_PROC_LIST *list )
{
	return( list->init_proc );
}

//--------------------------------------------------------------
/**
 * �`��֐��擾
 * @param	list	FIELD_OBJ_DRAW_PROC_LIST *
 * @retval	FIELD_OBJ_DRAW_PROC		FIELD_OBJ_DRAW_PROC *
 */
//--------------------------------------------------------------
static FIELD_OBJ_DRAW_PROC FldOBJ_DrawProcList_DrawGet( const FIELD_OBJ_DRAW_PROC_LIST *list )
{
	return( list->draw_proc );
}

//--------------------------------------------------------------
/**
 * �폜�֐��擾
 * @param	list	FIELD_OBJ_DRAW_PROC_LIST *
 * @retval	FIELD_OBJ_DRAW_PROC_DEL		FIELD_OBJ_DRAW_PROC_DEL *
 */
//--------------------------------------------------------------
static FIELD_OBJ_DRAW_PROC_DEL FldOBJ_DrawProcList_DeleteGet(
		const FIELD_OBJ_DRAW_PROC_LIST *list )
{
	return( list->delete_proc );
}

//--------------------------------------------------------------
/**
 * �ޔ��֐��擾
 * @param	list	FIELD_OBJ_DRAW_PROC_LIST *
 * @retval	FIELD_OBJ_DRAW_PROC_PUSH		FIELD_OBJ_DRAW_PROC_PUSH *
 */
//--------------------------------------------------------------
static FIELD_OBJ_DRAW_PROC_PUSH FldOBJ_DrawProcList_PushGet(
		const FIELD_OBJ_DRAW_PROC_LIST *list )
{
	return( list->push_proc );
}

//--------------------------------------------------------------
/**
 * ���A�֐��擾
 * @param	list	FIELD_OBJ_DRAW_PROC_LIST *
 * @retval	FIELD_OBJ_DRAW_PROC_PUSH		FIELD_OBJ_DRAW_PROC_PUSH *
 */
//--------------------------------------------------------------
static FIELD_OBJ_DRAW_PROC_POP FldOBJ_DrawProcList_PopGet(
		const FIELD_OBJ_DRAW_PROC_LIST *list )
{
	return( list->pop_proc );
}

//--------------------------------------------------------------
/**
 * �e�[�u������w��̃��X�g���o��
 * @param	code	HERO��
 * @retval	list	code�ɑΉ�����FIELD_OBJ_DRAW_PROC_LIST *
 */
//--------------------------------------------------------------
static const FIELD_OBJ_DRAW_PROC_LIST * FldOBJ_DrawProcListGet( u32 code )
{
	const FIELD_OBJ_DRAW_PROC_LIST_REG *tbl = DATA_FieldOBJDrawProcListRegTbl;
	
	do{
		if( tbl->code == code ){
			return( tbl->list );
		}
		
		tbl++;
	}while( tbl->code != OBJCODEMAX );
	
	GF_ASSERT( 0 && "FldOBJ_DrawProcListGet()�s���ȃR�[�h" );
	return( NULL );
}

//==============================================================================
//	�t�B�[���hOBJ �c�[��
//==============================================================================
//--------------------------------------------------------------
/**
 * �w�肳�ꂽ�O���b�hX,Z���W�ɂ���OBJ���擾
 * @param	sys			FIELD_OBJ_SYS_PTR 
 * @param	x			�����O���b�hX
 * @param	z			�����O���b�hZ
 * @retval	FIELD_OBJ	x,z�ʒu�ɂ���FIELD_OBJ_PTR �BNULL=���̍��W��OBJ�͂��Ȃ�
 */
//--------------------------------------------------------------
FIELD_OBJ_PTR  FieldOBJ_SearchGPos( CONST_FIELD_OBJ_SYS_PTR sys, int x, int z )
{
	int max;
	FIELD_OBJ_PTR fldobj;
	
	max = FieldOBJSys_OBJMaxGet( sys );
	fldobj = FieldOBJSys_FldOBJWorkGet( sys );
	
	do{
		if( FieldOBJ_StatusBit_Check(fldobj,FLDOBJ_STA_BIT_USE) ){
			if( FieldOBJ_NowPosGX_Get(fldobj) == x && FieldOBJ_NowPosGZ_Get(fldobj) == z ){
				return( fldobj );
			}
		}
		
		fldobj++;
		max--;
	}while( max );
	
	return( NULL );
}

//--------------------------------------------------------------
/**
 * ���W�A�������������Bfx32�^
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	vec		���������W
 * @param	dir		���� DIR_UP��
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_VecPosDirInit( FIELD_OBJ_PTR fldobj, const VecFx32 *vec, int dir )
{
	int gx,gy,gz;
	
	gx = SIZE_GRID_FX32( vec->x );
	FieldOBJ_NowPosGX_Set( fldobj, gx );
	
	gy = SIZE_H_GRID_FX32( vec->y );
	FieldOBJ_NowPosGY_Set( fldobj, gy );
	
	gz = SIZE_GRID_FX32( vec->z );
	FieldOBJ_NowPosGZ_Set( fldobj, gz );
	
	FieldOBJ_VecPosSet( fldobj, vec );
	FieldOBJ_GPosUpdate( fldobj );
	
	FieldOBJ_DirDispSetForce( fldobj, dir );
	
//	�Ȃ�ł���Ă��̂�
//	FldOBJ_WorkInit_MoveProcInit( fldobj );
//	FldOBJ_WorkInit_DrawProcInit( fldobj );
	
	FieldOBJ_AcmdFree( fldobj );
	FieldOBJ_StatusBit_ON( fldobj, FLDOBJ_STA_BIT_MOVE_START );
	FieldOBJ_StatusBit_OFF( fldobj, FLDOBJ_STA_BIT_MOVE | FLDOBJ_STA_BIT_MOVE_END );
}

//--------------------------------------------------------------
/**
 * ���W�A�������������B�O���b�h���W�^
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	x		�O���b�hX���W
 * @param	y		�O���b�hY���W
 * @param	z		�O���b�hZ���W
 * @param	dir		���� DIR_UP��
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_GPosDirInit( FIELD_OBJ_PTR fldobj, int x, int y, int z, int dir )
{
	VecFx32 vec;
	
	vec.x = GRID_SIZE_FX32( x ) + FLDOBJ_VEC_X_GRID_OFFS_FX32;
	FieldOBJ_NowPosGX_Set( fldobj, x );
	
	vec.y = H_GRID_SIZE_FX32( y ) + FLDOBJ_VEC_Y_GRID_OFFS_FX32;
	FieldOBJ_NowPosGY_Set( fldobj, y );
	
	vec.z = GRID_SIZE_FX32( z ) + FLDOBJ_VEC_Z_GRID_OFFS_FX32;
	FieldOBJ_NowPosGZ_Set( fldobj, z );
	
	FieldOBJ_VecPosSet( fldobj, &vec );
	FieldOBJ_GPosUpdate( fldobj );
	
	FieldOBJ_DirDispSetForce( fldobj, dir );
	
//	�Ȃ�ł���Ă��̂�
//	FldOBJ_WorkInit_MoveProcInit( fldobj );
//	FldOBJ_WorkInit_DrawProcInit( fldobj );

//	�����͈����̒l��M�p����
//	FieldOBJ_StatusBit_ON( fldobj, FLDOBJ_STA_BIT_MOVE_START | FLDOBJ_STA_BIT_HEIGHT_GET_NEED );
	FieldOBJ_StatusBit_ON( fldobj, FLDOBJ_STA_BIT_MOVE_START );
	FieldOBJ_StatusBit_OFF( fldobj, FLDOBJ_STA_BIT_MOVE | FLDOBJ_STA_BIT_MOVE_END );
	
	FieldOBJ_AcmdFree( fldobj );
}

//--------------------------------------------------------------
/**
 * ����R�[�h�ύX
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	code	MV_RND��
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_MoveCodeChange( FIELD_OBJ_PTR fldobj, u32 code )
{
	FieldOBJ_MoveDeleteProcCall( fldobj );
	FieldOBJ_MoveCodeSet( fldobj, code );
	FldOBJ_WorkInit_MoveProcInit( fldobj );
	FieldOBJ_MoveInit( fldobj );
}

//--------------------------------------------------------------
/**
 * OBJ ID��ύX
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	id		OBJ ID
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_OBJIDChange( FIELD_OBJ_PTR fldobj, int id )
{
	FieldOBJ_OBJIDSet( fldobj, id );
		
	FieldOBJ_StatusBitON_MoveStart( fldobj );
	FldOBJ_DrawEffectFlagInit( fldobj );
}

//==============================================================================
//	����֐��_�~�[
//==============================================================================
//--------------------------------------------------------------
/**
 * ���쏉�����֐��_�~�[
 * @param	FIELD_OBJ	FIELD_OBJ_PTR 
 * @retval	int			TRUE=����������
 */
//--------------------------------------------------------------
void FieldOBJ_MoveInitProcDummy( FIELD_OBJ_PTR fldobj )
{
}

//--------------------------------------------------------------
/**
 * ����֐��_�~�[
 * @param	FIELD_OBJ	FIELD_OBJ_PTR 
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_MoveProcDummy( FIELD_OBJ_PTR fldobj )
{
}

//--------------------------------------------------------------
/**
 * ����폜�֐��_�~�[
 * @param	FIELD_OBJ	FIELD_OBJ_PTR 
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_MoveDeleteProcDummy( FIELD_OBJ_PTR fldobj )
{
}

//--------------------------------------------------------------
/**
 * ���앜�A�֐��_�~�[
 * @param	FIELD_OBJ_PTR	FIELD_OBJ_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_MoveReturnProcDummy( FIELD_OBJ_PTR fldobj )
{
}

//==============================================================================
//	�`��֐��_�~�[
//==============================================================================
//--------------------------------------------------------------
/**
 * �`�揉�����֐��_�~�[
 * @param	FIELD_OBJ	FIELD_OBJ_PTR 
 * @retval	int			TRUE=����������
 */
//--------------------------------------------------------------
void FieldOBJ_DrawInitProcDummy( FIELD_OBJ_PTR fldobj )
{
}

//--------------------------------------------------------------
/**
 * �`��֐��_�~�[
 * @param	FIELD_OBJ	FIELD_OBJ_PTR 
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_DrawProcDummy( FIELD_OBJ_PTR fldobj )
{
}

//--------------------------------------------------------------
/**
 * �`��폜�֐��_�~�[
 * @param	FIELD_OBJ	FIELD_OBJ_PTR 
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_DrawDeleteProcDummy( FIELD_OBJ_PTR fldobj )
{
}

//--------------------------------------------------------------
/**
 * �`��ޔ��֐��_�~�[
 * @param	FIELD_OBJ	FIELD_OBJ_PTR 
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_DrawPushProcDummy( FIELD_OBJ_PTR fldobj )
{
}

//--------------------------------------------------------------
/**
 * �`�敜�A�֐��_�~�[
 * @param	FIELD_OBJ	FIELD_OBJ_PTR 
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_DrawPopProcDummy( FIELD_OBJ_PTR fldobj )
{
}
