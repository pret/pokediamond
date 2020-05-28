//============================================================================================
/**
 * @file	btl_searcher.c
 * @bfief	�o�g���T�[�`���[
 * @author	Satoshi Nohara
 * @date	06.04.26
 */
//============================================================================================
#include "common.h"
#include "gflib/msg_print.h"

#include "system/lib_pack.h"
#include "system/snd_tool.h"

#include "fieldmap.h"
#include "fieldsys.h"
#include "zonedata.h"
#include "mapdefine.h"

#include "itemtool/itemsym.h"							//
#include "battle/trno_def.h"

#include "field/eventflag.h"							//
#include "field/evwkdef.h"								//

#include "script.h"										//
#include "syswork.h"
#include "sysflag.h"
#include "eventdata.h"
#include "fieldobj_code.h"
#include "btl_searcher.h"


//==============================================================================================
//
//	��`
//
//==============================================================================================
//#define BS_LEVEL_MAX		(5)				//�Đ�̍ő僌�x��
#define BS_LEVEL_MAX		(6)				//�Đ�̍ő僌�x��

#define REMATCH_DATA_END	(0)				//�Đ�f�[�^�Ȃ�
#define REMATCH_DATA_DUMMY	(0xffff)		//�Đ�f�[�^�_�~�[(���̃��x�������ɂ����悤�ɂ���)

#define	BS_RAND_NOSET		(50)			//�T�O���̊m���ōĐ�g���[�i�[�Z�b�g���Ȃ�
#define	NOT_EXIST_OFS		(-1)			//�Đ�f�[�^�����݂��Ȃ��ꍇ

//�����͈�
#define BS_SEARCH_SX		(7)				//�����͈�
#define BS_SEARCH_TOP		(7)				//�����͈�(��l�������ʏ�)
#define BS_SEARCH_BOTTOM	(6)				//�����͈�(��l�������ʉ�)

#define	BS_FLDOBJ_MAX		(64)			//FIELD_OBJ_PTR�̍ő吔(�v�m�F�I)

//�g���[�i�[�T�[�`�g�p�`�F�b�N
enum{
	BS_NO_BATTERY = 0,						//�o�b�e���[�����܂��Ă��Ȃ�
	BS_NO_TRAINER,							//��ʓ��Ƀg���[�i�[�����Ȃ�
	BS_OK_BATTERY,							//�o�b�e���[�����܂��Ă��āA��ʓ��Ƀg���[�i�[������
};

//�V�[�P���X�i���o�[��`
enum{
	BS_SEQ_INIT = 0,
	BS_SEQ_START,
	BS_SEQ_OK_BATTERY,
	BS_SEQ_OK_BATTERY_ANM_WAIT,
	BS_SEQ_OK_BATTERY_LOTTERY,
	BS_SEQ_OK_BATTERY_LOTTERY_ANM_WAIT,
	BS_SEQ_NO_BATTERY,
	BS_SEQ_NO_TRAINER,
	BS_SEQ_EXIT,
};

//�Z�b�g�ɂȂ��Ă���g���[�i�[�̃|�C���^���擾���鎞�̃��[�h
#define BS_2VS2_MV_REWAR_CHK_ON		(0)		//�Đ퓮��R�[�h�̃`�F�b�N����
#define BS_2VS2_MV_REWAR_CHK_OFF	(1)		//�Đ퓮��R�[�h�̃`�F�b�N�Ȃ�


//==============================================================================================
//
//	�\����
//
//==============================================================================================
//�f�[�^�\����(btl_searcher.dat�Ŏg�p)
typedef struct {
	u16 id[BS_LEVEL_MAX];					//����ID
}REMATCH_DATA;
#include "../fielddata/btl_searcher/rematch.dat"

//�V�X�e���\����
typedef struct{
	u32	seq;

	FIELDSYS_WORK* fsys;					//FIELDSYS_WORK�^�̃|�C���^
	EVENTWORK* ev;							//EVENTWORK�^�̃|�C���^

	const REMATCH_DATA* data;				//�Đ�f�[�^�̃|�C���^(rematch.dat)

	FIELD_OBJ_PTR fldobj[BS_FLDOBJ_MAX];	//

	u16	fldobj_max;							//�ő吔
	u16 anm_count;							//�A�j���o�^�J�E���g

	u16* ret_wk;							//���ʂ�Ԃ����[�N�ւ̃|�C���^
	WORDSET* wordset;						//�P��Z�b�g
}BS_SYS;

//�A�j���[�V�����I���Ď����[�N
typedef struct{
	TCB_PTR	tcb;					//TCB
	TCB_PTR	anm_tcb;				//�A�j���[�V����TCB
	BS_SYS* bs_sys;					//BS_SYS�̃|�C���^
}BS_ANM_WORK;


//==============================================================================================
//
//	�v���g�^�C�v�錾
//
//==============================================================================================
void EventCmd_BtlSearcher(GMEVENT_CONTROL* event,WORDSET* wordset,u16* ret_wk);	//scrcmd.c
u16 BS_TrainerIDCheck( FIELDSYS_WORK* fsys, FIELD_OBJ_PTR fldobj, u16 tr_id );	//scrcmd.c
BOOL BS_StepCountUp( FIELDSYS_WORK* fsys );										//ev_check.c
static BOOL BS_HideMoveCodeCheck( u32 code );

static BOOL GMEVENT_StartBtlSearcher( GMEVENT_CONTROL* event );
static int BS_UseChk( BS_SYS* bs_sys );
static void BS_SeqChange( BS_SYS* bs_sys, u32 seq );
static void BS_FldObjDataSet( BS_SYS* bs_sys );

//�A�j���֘A
static void BS_FldObjAnmSet( BS_SYS* bs_sys );
static void BS_AnmSet( BS_SYS* bs_sys, FIELD_OBJ_PTR fldobj, const FIELD_OBJ_ACMD_LIST *list );
static void BS_AnmSetTCB( BS_SYS* bs_sys, TCB_PTR anm_tcb );
static void BS_AnmMainTCB( TCB_PTR tcb, void* wk );
static BOOL BS_AnmWait( BS_SYS* bs_sys );

static BOOL BS_Lottery( BS_SYS* bs_sys );
static u16 BS_TrainerIdGetByScriptId( FIELD_OBJ_PTR fldobj );

static void BS_RevengeMoveCodeClear( FIELDSYS_WORK* fsys );
static u16 BS_RevengeDataIndexGet( FIELDSYS_WORK* fsys, u16 tr_id );
static u16 BS_RevengeDataLevelGet( FIELDSYS_WORK* fsys, u16 index );
static u16 BS_RevengeDataLevelEventCheck( FIELDSYS_WORK* fsys, u16 index, u16 level );
static u16 BS_RevengeDataLevelEventCheckSub( u16 index, u16 level );
static u16 BS_RevengeTrainerIDGet( u16 index, u16 level );
static BOOL BS_RevengeMoveCodeCheck( FIELD_OBJ_PTR fldobj );
static void BS_MvSet( FIELD_OBJ_PTR fldobj, u16 code );
void BS_MvReWarClearDirMvSet( FIELDSYS_WORK* fsys, FIELD_OBJ_PTR fldobj );
static BOOL BS_StatusBitCheckMove( FIELDSYS_WORK* fsys );
static FIELD_OBJ_PTR BS_2vs2TrPtrGet( FIELDSYS_WORK* fsys, FIELD_OBJ_PTR search_obj, int mode );


//==============================================================================================
//
//	�A�j���[�V�����f�[�^
//
//==============================================================================================
//��]�A�j��
static const FIELD_OBJ_ACMD_LIST ps_anm_1[] = {
	{ AC_STAY_WALK_D_8F, 1 },
	{ AC_WAIT_4F, 1 },
	{ AC_DIR_R, 1 },
	{ AC_WAIT_4F, 1 },
	{ AC_DIR_U, 1 },
	{ AC_WAIT_4F, 1 },
	{ AC_DIR_L, 1 },
	{ AC_WAIT_4F, 1 },
	{ AC_DIR_D, 1 },
	{ AC_WAIT_4F, 1 },
	{ ACMD_END, 0 },
};

//�Đ�\�A�j��
static const FIELD_OBJ_ACMD_LIST ps_anm_ok[] = {
	{ AC_DIR_D, 1 },
	{ AC_MARK_SAISEN, 1 },
	{ ACMD_END, 0 },
};

//���킪�܂��A�j��
static const FIELD_OBJ_ACMD_LIST ps_anm_first[] = {
	{ AC_MARK_GYOE, 1 },
	{ ACMD_END, 0 },
};

//�������Ȃ��A�j��
static const FIELD_OBJ_ACMD_LIST ps_anm_ng[] = {
	{ AC_WAIT_8F, 1 },
	{ ACMD_END, 0 },
};


//==============================================================================================
//
//	�A�C�e���g�p�ŌĂ΂��
//
//==============================================================================================

//----------------------------------------------------------------------------------------------
/**
 * �C�x���g�Ăяo��
 * 
 * @param	event		�C�x���g���䃏�[�N�ւ̃|�C���^
 * @param	wordset		WORDSET�^�̃|�C���^
 * @param	ret_wk		���ʂ�Ԃ����[�N�ւ̃|�C���^
 *
 * @retval	none
 */
//----------------------------------------------------------------------------------------------
void EventCmd_BtlSearcher( GMEVENT_CONTROL* event, WORDSET* wordset, u16* ret_wk )
{
	BS_SYS* bs_sys;
	FIELDSYS_WORK* fsys	= FieldEvent_GetFieldSysWork( event );

	//�V�X�e�����[�N�m��
	bs_sys = sys_AllocMemory( HEAPID_FIELD, sizeof(BS_SYS) );
	if( bs_sys == NULL ){
		GF_ASSERT( (0) && "�������m�ێ��s�I" );
		return;
	}

	//������
	memset( bs_sys, 0, sizeof(BS_SYS) );
	bs_sys->fsys	= fsys;
	bs_sys->ev		= SaveData_GetEventWork( fsys->savedata );
	bs_sys->ret_wk	= ret_wk;
	bs_sys->wordset	= wordset;

	FieldEvent_Call( event, GMEVENT_StartBtlSearcher, bs_sys );
	return;
}

//----------------------------------------------------------------------------------------------
/**
 * �C�x���g���C��
 * 
 * @param	event		�C�x���g���䃏�[�N�ւ̃|�C���^
 *
 * @retval	"FALSE=�p���ATRUE=�I��"
 */
//----------------------------------------------------------------------------------------------
static BOOL GMEVENT_StartBtlSearcher( GMEVENT_CONTROL* event )
{
	s32 num,keta;
	int ret;
	BS_SYS* bs_sys = FieldEvent_GetSpecialWork( event );

	switch( bs_sys->seq ){

	//�O���b�h�Ɏ��܂�܂ő҂�
	case BS_SEQ_INIT:
		if( BS_StatusBitCheckMove(bs_sys->fsys) == TRUE ){
			BS_SeqChange( bs_sys, BS_SEQ_START );
		}
		break;

	//�J�n
	case BS_SEQ_START:

		//��ʓ��ɂ���g���[�i�[�̃f�[�^���Z�b�g
		BS_FldObjDataSet( bs_sys );

		ret = BS_UseChk( bs_sys );

		//�o�b�e���[�����܂��Ă��āA��ʓ��Ƀg���[�i�[������
		if( ret == BS_OK_BATTERY ){
			*bs_sys->ret_wk = 0;
			BS_SeqChange( bs_sys, BS_SEQ_OK_BATTERY );
		}else if( ret == BS_NO_BATTERY ){
			*bs_sys->ret_wk = 1;
			BS_SeqChange( bs_sys, BS_SEQ_NO_BATTERY );
		}else{
			*bs_sys->ret_wk = 2;
			BS_SeqChange( bs_sys, BS_SEQ_NO_TRAINER );
		}
		break;

	//�o�b�e���[�����܂��Ă��āA��ʓ��Ƀg���[�i�[������
	case BS_SEQ_OK_BATTERY:
		Snd_SePlay( SE_BTL_SEARCHER );							//�s�b�s�b�s
		SysWork_BtlSearcherBatterySet( bs_sys->ev, 0 );			//�o�b�e���[�N���A
		//BS_FldObjAnmSet( bs_sys );							//��]�A�j���Z�b�g
		BS_SeqChange( bs_sys, BS_SEQ_OK_BATTERY_ANM_WAIT );
		break;

	//�g���[�i�[�̉�]�A�j���I���҂�
	case BS_SEQ_OK_BATTERY_ANM_WAIT:
		if( BS_AnmWait(bs_sys) == 0 ){
			BS_SeqChange( bs_sys, BS_SEQ_OK_BATTERY_LOTTERY );
		}
		break;

	//�Đ�̒��I���s��
	case BS_SEQ_OK_BATTERY_LOTTERY:
		if( BS_Lottery(bs_sys) == 0 ){
			*bs_sys->ret_wk = 3;
		}
		BS_SeqChange( bs_sys, BS_SEQ_OK_BATTERY_LOTTERY_ANM_WAIT );
		break;

	//�Đ�\�A����܂��A�������Ȃ��A�j���҂�
	case BS_SEQ_OK_BATTERY_LOTTERY_ANM_WAIT:
		if( BS_AnmWait(bs_sys) == 0 ){
			BS_SeqChange( bs_sys, BS_SEQ_EXIT );
		}
		break;

	//�o�b�e���[�����܂��Ă��Ȃ�
	case BS_SEQ_NO_BATTERY:

		//����Ȃ��o�b�e���[�ʂ��o�b�t�@�ɃZ�b�g����
		num = ( BS_BATTERY_MAX - SysWork_BtlSearcherBatteryGet(bs_sys->ev) );

		//�����擾
		if( (num / 10) == 0 ){
			keta = 1;
		}else if( (num / 100) == 0 ){
			keta = 2;
		}else{
			keta = 3;
		}

		WORDSET_RegisterNumber( bs_sys->wordset, 0, num, keta,
								NUMBER_DISPTYPE_SPACE, NUMBER_CODETYPE_DEFAULT);

		BS_SeqChange( bs_sys, BS_SEQ_EXIT );
		break;

	//��ʓ��Ƀg���[�i�[�����Ȃ�
	case BS_SEQ_NO_TRAINER:
		BS_SeqChange( bs_sys, BS_SEQ_EXIT );
		break;

	//�I��
	case BS_SEQ_EXIT:
		sys_FreeMemoryEz( bs_sys );
		return TRUE;
	};

	return FALSE;
}

//----------------------------------------------------------------------------------------------
/**
 * �V�[�P���X�ύX
 *
 * @param   bs_sys		BS_SYS�^�̃|�C���^
 * @param   seq			�Z�b�g����V�[�P���X
 *
 * @retval	none
 */
//----------------------------------------------------------------------------------------------
static void BS_SeqChange( BS_SYS* bs_sys, u32 seq )
{
	bs_sys->seq = seq;
	return;
}

//----------------------------------------------------------------------------------------------
/**
 * �o�g���T�[�`���[�g�p�`�F�b�N
 *
 * @param   bs_sys		BS_SYS�^�̃|�C���^
 *
 * @retval	BS_NO_BATTERY	�o�b�e���[�����܂��Ă��Ȃ�
 * @retval	BS_NO_TRAINER	��ʓ��Ƀg���[�i�[�����Ȃ�
 * @retval	BS_OK_BATTERY	�o�b�e���[�����܂��Ă��āA��ʓ��Ƀg���[�i�[������
 */
//----------------------------------------------------------------------------------------------
static int BS_UseChk( BS_SYS* bs_sys )
{
	//�o�b�e���J�E���^�[�����܂��Ă��邩	
	if( SysWork_BtlSearcherBatteryGet(bs_sys->ev) == BS_BATTERY_MAX ){

		//��ʓ��Ƀg���[�i�[���邩
		if( bs_sys->fldobj_max == 0 ){
			//��ʓ��Ƀg���[�i�[���Ȃ�
			return BS_NO_TRAINER;
		}

		//�o�b�e���[�����܂��Ă��āA��ʓ��Ƀg���[�i�[������
		return BS_OK_BATTERY;
	}

	//�o�b�e���[�s��
	return BS_NO_BATTERY;
}

//----------------------------------------------------------------------------------------------
/**
 * �o�g���T�[�`���[�V�X�e���ɉ�ʓ��ɂ���g���[�i�[�̃f�[�^���Z�b�g
 *
 * @param   bs_sys		BS_SYS�^�̃|�C���^
 *
 * @retval	none
 */
//----------------------------------------------------------------------------------------------
static void BS_FldObjDataSet( BS_SYS* bs_sys )
{
	int x,z;
	u32 event_type;

	int	hero_gx,hero_gz,i,count;
	int l,r,u,d;
	FIELD_OBJ_PTR fldobj;

	u32 obj_max = EventData_GetNpcCount( bs_sys->fsys );

	//������
	count = 0;

	for( i=0; i < obj_max ;i++ ){
		bs_sys->fldobj[i] = NULL;
	}

	//��l���̈ʒu�擾
	hero_gx = Player_NowGPosXGet( bs_sys->fsys->player );
	hero_gz = Player_NowGPosZGet( bs_sys->fsys->player );

	//�����͈͂��Z�b�g(3D�͈ӎ������̊ȈՔ�)
	l = hero_gx - BS_SEARCH_SX;
	r = hero_gx + BS_SEARCH_SX;
	u = hero_gz - BS_SEARCH_TOP;
	d = hero_gz + BS_SEARCH_BOTTOM;

	//�␳
	if( l < 0 ){ l = 0; }
	//if( r < 0 ){ 0 };
	if( u < 0 ){ u = 0; }
	//if( d < 0 ){ 0 };

	//OBJ�f�[�^���T�[�`��������
	for( i=0; i < obj_max ;i++ ){

		//�t�B�[���hOBJ�̃|�C���^�擾
		fldobj	= FieldOBJSys_OBJIDSearch( bs_sys->fsys->fldobjsys, i );
		if( fldobj == NULL ){
			continue;
		}

		//�C�x���g�^�C�v���g���[�i�[���`�F�b�N
		event_type = FieldOBJ_EventTypeGet( fldobj );

		switch( event_type ){
		case EV_TYPE_TRAINER:
		case EV_TYPE_TRAINER_EYEALL:
		case EV_TYPE_TRAINER_KYORO:
		case EV_TYPE_TRAINER_SPIN_STOP_L:
		case EV_TYPE_TRAINER_SPIN_STOP_R:
		case EV_TYPE_TRAINER_SPIN_MOVE_L:
		case EV_TYPE_TRAINER_SPIN_MOVE_R:

			//�����͈͓��ɂ��邩�`�F�b�N
			x = FieldOBJ_NowPosGX_Get( fldobj );
			z = FieldOBJ_NowPosGZ_Get( fldobj );
			if( (x >= l) && (x <= r) && (z >= u) && (z <= d) ){

				//����R�[�h���B�ꖪ���`�F�b�N
				if( BS_HideMoveCodeCheck(FieldOBJ_MoveCodeGet(fldobj)) == FALSE ){
					//OS_Printf( "id = %d\n", i );
					//OS_Printf( "event_type = %d\n", event_type );

					//�V�X�e�����[�N�ɃZ�b�g
					bs_sys->fldobj[count] = fldobj;
					count++;
				}
			}
		};
	}

	bs_sys->fldobj_max = count;
	return;
}

//----------------------------------------------------------------------------------------------
/**
 * ����R�[�h���B�ꖪ���`�F�b�N
 *
 * @param   code	����R�[�h
 *
 * @retval	"FALSE=�Ⴄ�ATRUE=�B�ꖪ"
 */
//----------------------------------------------------------------------------------------------
static BOOL BS_HideMoveCodeCheck( u32 code )
{
	switch( code ){
	case MV_HIDE_SNOW:		//�B�ꖪ�@��
	case MV_HIDE_SAND:		//�B�ꖪ�@��
	case MV_HIDE_GRND:		//�B�ꖪ�@�y
	case MV_HIDE_KUSA:		//�B�ꖪ�@��
		return TRUE;
	};

	return FALSE;
}


//==============================================================================================
//
//	����ړ��ŌĂ΂��(ev_check.c)
//
//==============================================================================================

//----------------------------------------------------------------------------------------------
/**
 * �����J�E���g
 *
 * @param   fsys	FIELDSYS_WORK�^�̃|�C���^
 *
 * @retval	"FALSE	�������Ȃ�"
 */
//----------------------------------------------------------------------------------------------
BOOL BS_StepCountUp( FIELDSYS_WORK* fsys )
{
	EVENTWORK* ev		= SaveData_GetEventWork( fsys->savedata );
	u16 battery_count	= SysWork_BtlSearcherBatteryGet( ev );
	u16 clear_count		= SysWork_BtlSearcherClearGet( ev );

	//�o�g���T�[�`���[�������Ă�����
	if( MyItem_CheckItem( SaveData_GetMyItem(fsys->savedata),
							ITEM_BATORUSAATYAA,1,HEAPID_FIELD) == TRUE ){

		//�o�b�e���[�𒙂߂�
		if( battery_count < BS_BATTERY_MAX ) {
			battery_count++;
			SysWork_BtlSearcherBatterySet( ev, battery_count );
		}
	}

	//�o�b�e���[���g�p���Ă�����
	if( SysFlag_BtlSearcherUseCheck(ev) == TRUE ){

		//�N���A�J�E���^�[���܂��Ă��Ȃ�������
		if( clear_count < BS_CLEAR_MAX ){
			clear_count++;
			SysWork_BtlSearcherClearSet( ev, clear_count );
		}
		
		//�N���A�J�E���^�[���܂��Ă�����
		if( clear_count == BS_CLEAR_MAX ){
			Sys_BtlSearcherReset( ev );					//sys_work.c
			BS_RevengeMoveCodeClear( fsys );			//�Đ퓮��R�[�h���N���A
		}
	}

	//OS_Printf( "battery_count = %d\n", battery_count );
	//OS_Printf( "clear_count = %d\n", clear_count );
	return FALSE;		//�������Ȃ�
}

//----------------------------------------------------------------------------------------------
/**
 * �Đ퓮��R�[�h���N���A����
 *
 * @param   fsys		FIELDSYS_WORK�^�̃|�C���^
 *
 * @retval  none
 */
//----------------------------------------------------------------------------------------------
static void BS_RevengeMoveCodeClear( FIELDSYS_WORK* fsys )
{
	int i;
	FIELD_OBJ_PTR fldobj;
	u32 obj_max = EventData_GetNpcCount( fsys );

	//OBJ�f�[�^���T�[�`��������
	for( i=0; i < obj_max ;i++ ){

		//�t�B�[���hOBJ�̃|�C���^�擾
		fldobj	= FieldOBJSys_OBJIDSearch( fsys->fldobjsys, i );
		if( fldobj == NULL ){
			continue;
		}

		//����R�[�h���Đ킩�`�F�b�N
		if( FieldOBJ_MoveCodeGet(fldobj) == MV_REWAR ){
			BS_MvSet( fldobj, MV_DIR_RND );		//�u�����_���ɕ����ؑցv�ɕύX
		}
	}

	return;
}


//==============================================================================================
//
//	�A�j���֘A
//
//==============================================================================================

//----------------------------------------------------------------------------------------------
/**
 * �t�B�[���hOBJ�̃A�j���Z�b�g
 *
 * @param   bs_sys		BS_SYS�^�̃|�C���^
 *
 * @retval	none
 */
//----------------------------------------------------------------------------------------------
static void BS_FldObjAnmSet( BS_SYS* bs_sys )
{
	int i;

	for( i=0; i < bs_sys->fldobj_max ;i++ ){
		BS_AnmSet( bs_sys, bs_sys->fldobj[i], ps_anm_1 );		//��]�A�j���Z�b�g
	}

	return;
}

//----------------------------------------------------------------------------------------------
/**
 * �A�j���Z�b�g
 *
 * @param   bs_sys		BS_SYS�^�̃|�C���^
 * @param   fldobj		FIELD_OBJ_PTR
 *
 * @retval	none
 */
//----------------------------------------------------------------------------------------------
static void BS_AnmSet( BS_SYS* bs_sys, FIELD_OBJ_PTR fldobj, const FIELD_OBJ_ACMD_LIST *list )
{
	TCB_PTR anm_tcb;

	//�A�j���[�V�����R�}���h���X�g�Z�b�g
	anm_tcb = FieldOBJ_AcmdListSet( fldobj, list );

	//�A�j���[�V�����̐��𑫂�
	bs_sys->anm_count++;

	BS_AnmSetTCB( bs_sys, anm_tcb );
	return;
}

//--------------------------------------------------------------------------------------------
/**
 * @brief	�A�j���I���Ď�TCB �Z�b�g
 *
 * @param	bs_sys	BS_SYS�^�̃|�C���^
 * @param	anm_tcb	TCB_PTR�^
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void BS_AnmSetTCB( BS_SYS* bs_sys, TCB_PTR anm_tcb )
{
	BS_ANM_WORK* ps_anm_wk = NULL;

	ps_anm_wk = sys_AllocMemory( HEAPID_FIELD, sizeof(BS_ANM_WORK) );
	if( ps_anm_wk == NULL ){
		GF_ASSERT( (0) && "scrcmd.c �������m�ێ��s�I" );
		return;
	}

	ps_anm_wk->bs_sys	= bs_sys;
	ps_anm_wk->anm_tcb	= anm_tcb;
	ps_anm_wk->tcb		= TCB_Add( BS_AnmMainTCB, ps_anm_wk, 0 );
	return;
}

//----------------------------------------------------------------------------------------------
/**
 * @brief	�A�j���I���Ď�TCB ���C��
 *
 * @param	tcb		TCB_PTR
 * @param	wk		���[�N�̃A�h���X
 *
 * @retval	none
 */
//----------------------------------------------------------------------------------------------
static void BS_AnmMainTCB( TCB_PTR tcb, void* wk )
{
	BS_ANM_WORK *swk = (BS_ANM_WORK *)wk;

	//�I�����Ă�����
	if( FieldOBJ_AcmdListEndCheck( swk->anm_tcb ) == TRUE ){

		//�A�j���[�V�������̊Ǘ�
		if( swk->bs_sys->anm_count == 0 ){
			GF_ASSERT( (0) && "�A�j���[�V�������̊Ǘ����s���ł��I" );
		}

		swk->bs_sys->anm_count--;

		FieldOBJ_AcmdListEnd( swk->anm_tcb );

		TCB_Delete( swk->tcb );
		sys_FreeMemory( HEAPID_FIELD, wk );
	}

	return;
}

//----------------------------------------------------------------------------------------------
/**
 * @brief	�A�j���I���`�F�b�N
 *
 * @param	tcb		TCB_PTR
 * @param	wk		���[�N�̃A�h���X
 *
 * @retval	"0=�I���A1=�p��"
 */
//----------------------------------------------------------------------------------------------
static BOOL BS_AnmWait( BS_SYS* bs_sys )
{
	return bs_sys->anm_count;
}


//==============================================================================================
//
//	���I�֘A
//
//==============================================================================================

//----------------------------------------------------------------------------------------------
/**
 * �Đ��Ԃɂ��邩�̒��I���s��
 *
 * @param   bs_sys		BS_SYS�^�̃|�C���^
 *
 * @retval	"0 = �P�l���킦���Ԃ̃g���[�i�[�����Ȃ������A1 = �킦���Ԃ̃g���[�i�[������"
 */
//----------------------------------------------------------------------------------------------
static BOOL BS_Lottery( BS_SYS* bs_sys )
{
	EVENTWORK* ev = SaveData_GetEventWork( bs_sys->fsys->savedata );
	FIELD_OBJ_PTR tr_2vs2;
	u16 tr_id;
	int i,flag;

	flag = 0;	//�Đ�ɂȂ����g���[�i�[���������t���O

	for( i=0; i < bs_sys->fldobj_max ;i++ ){

		//����g���[�i�[ID�ɏ������Ă��邩�`�F�b�N
		tr_id = BS_TrainerIdGetByScriptId( bs_sys->fldobj[i] );
		if( CheckEventFlagTrainer(bs_sys->fsys, tr_id) == FALSE ){		//�������Ă��Ȃ�
			BS_AnmSet( bs_sys, bs_sys->fldobj[i], ps_anm_first );		//����܂��A�j���Z�b�g
			//Snd_SePlay( SE_MARK_GYOE );
			flag = 1;
		}else{

			//�T�O���̊m���ōĐ�g���[�i�[�ɂȂ�
			//����R�[�h���Đ�ɂȂ��Ă��Ȃ�������(2vs2�͍Đ�ɂȂ��Ă��邱�Ƃ�����)
			//gf_srand( sys.vsync_counter );
			if( ((gf_rand() % 100) < BS_RAND_NOSET) && 
				(BS_RevengeMoveCodeCheck(bs_sys->fldobj[i]) == FALSE) ){

				BS_MvSet( bs_sys->fldobj[i], MV_REWAR );				//�Đ퓮��R�[�h�ɕύX
				BS_AnmSet( bs_sys, bs_sys->fldobj[i], ps_anm_ok );		//�Đ�\�A�j���Z�b�g

#if 1
				//�Z�b�g�ɂȂ��Ă���g���[�i�[�̃|�C���^���擾���čĐ�Z�b�g
				tr_2vs2 = BS_2vs2TrPtrGet(bs_sys->fsys, bs_sys->fldobj[i], BS_2VS2_MV_REWAR_CHK_ON);
				if( tr_2vs2 != NULL ){
					BS_MvSet( tr_2vs2, MV_REWAR );						//�Đ퓮��R�[�h�ɕύX
					BS_AnmSet( bs_sys, tr_2vs2, ps_anm_ok );			//�Đ�\�A�j���Z�b�g
				}
#endif

				//Snd_SePlay( SE_MARK_GYOE );
				flag = 1;
				SysFlag_BtlSearcherUseSet( ev );
			
			//�Đ�g���[�i�[�ɂȂ�Ȃ�����
			}else{
				//BS_MvSet( bs_sys->fldobj[i], MV_DOWN );				//���ʌ����Œ�ɕύX
				//BS_AnmSet( bs_sys, bs_sys->fldobj[i], ps_anm_ng );	//�������Ȃ��A�j���Z�b�g
			}
		}
	}

	return flag;
}

//----------------------------------------------------------------------------------------------
/**
 * �X�N���v�gID����A�g���[�i�[ID���擾
 *
 * @param   fldobj		FIELD_OBJ_PTR
 *
 * @retval  "�g���[�i�[ID"
 */
//----------------------------------------------------------------------------------------------
static u16 BS_TrainerIdGetByScriptId( FIELD_OBJ_PTR fldobj )
{
	u32 script_id = FieldOBJ_EventIDGet( fldobj );
	return GetTrainerIdByScriptId( script_id );
}


//==============================================================================================
//
//	�g���[�i�[�b�������֘A(trainer.ev)
//
//==============================================================================================

//----------------------------------------------------------------------------------------------
/**
 * FIELD_OBJ_PTR�̍Đ�g���[�i�[ID���擾
 *
 * @param   fsys		FIELDSYS_WORK�^�̃|�C���^
 * @param   fldobj		FIELD_OBJ_PTR
 * @param   tr_id		��������g���[�i�[ID
 *
 * @retval  "0 = �f�[�^�Ȃ��A0�ȊO = �g���[�i�[ID"
 *
 * @li		"�g���[�i�[ID = 0 = ����"�Ƃ��Ĉ����Ă���(�Đ�f�[�^�e�[�u���Ɋ܂܂�Ă��Ȃ��̂�OK)
 */
//----------------------------------------------------------------------------------------------
u16 BS_TrainerIDCheck( FIELDSYS_WORK* fsys, FIELD_OBJ_PTR fldobj, u16 tr_id )
{
	u16 index,level,ret;

	//�Đ퓮��R�[�h���`�F�b�N
	if( BS_RevengeMoveCodeCheck(fldobj) == FALSE ){
		return 0;
	}

	//�f�[�^�C���f�b�N�X�擾
	index = BS_RevengeDataIndexGet( fsys, tr_id );
	if( index == 0xff ){
		return 0;
	}

	//�f�[�^���x���擾
	level = BS_RevengeDataLevelGet( fsys, index );
	//OS_Printf( "level = %d\n", level );

	//�C�x���g�i�s�`�F�b�N�ɂ���čĐ탌�x���𒲐�
	level = BS_RevengeDataLevelEventCheck( fsys, index, level );
	//OS_Printf( "level = %d\n", level );

	//�Đ�g���[�i�[ID�擾
	ret = BS_RevengeTrainerIDGet( index, level );
	//OS_Printf( "ret = %d\n", ret );

	return ret;
}

//----------------------------------------------------------------------------------------------
/**
 * �Đ�f�[�^�e�[�u���̃C���f�b�N�X���擾
 *
 * @param   fsys		FIELDSYS_WORK�^�̃|�C���^
 * @param   tr_id		��������g���[�i�[ID
 *
 * @retval  "0xff�ȊO = �C���f�b�N�X�A0xff = ������Ȃ�����"
 */
//----------------------------------------------------------------------------------------------
static u16 BS_RevengeDataIndexGet( FIELDSYS_WORK* fsys, u16 tr_id )
{
	int i,level;
	//REMATCH_DATA* data = bs_sys->data;
	const REMATCH_DATA* data = RematchDataTbl;

	//�Đ�g���[�i�[�f�[�^������
	for( i=0; i < REMATCH_DATA_MAX; i++ ){

		//�����g���[�i�[ID��T��
		if( data[i].id[0] != tr_id ){
			continue;
		}

		//�����g���[�i�[ID��������
		return i;
	}

	return 0xff;
}

//----------------------------------------------------------------------------------------------
/**
 * �Đ탌�x�����擾
 *
 * @param   fsys		FIELDSYS_WORK�^�̃|�C���^
 * @param   index		�Đ�f�[�^�e�[�u���̃C���f�b�N�X
 *
 * @retval  "���x��"
 */
//----------------------------------------------------------------------------------------------
static u16 BS_RevengeDataLevelGet( FIELDSYS_WORK* fsys, u16 index )
{
	int i,level;
	//REMATCH_DATA* data = bs_sys->data;
	const REMATCH_DATA* data = RematchDataTbl;

	//�Đ탌�x��������
	for( level = 1; level < BS_LEVEL_MAX; level++ ){

		//�Đ�f�[�^���Ȃ����`�F�b�N
		if( data[index].id[level] == REMATCH_DATA_END ){
			return (level - 1);
		}

		//�Đ�f�[�^���_�~�[���`�F�b�N
		if( data[index].id[level] != REMATCH_DATA_DUMMY ){

			//���̃��x���͑ΐ킵�Ă��Ȃ����`�F�b�N
			if( CheckEventFlagTrainer(fsys, data[index].id[level]) == FALSE ){
				return (level);
			}
		}
	}

	//���x�����ō�
	return (level - 1);
}

//----------------------------------------------------------------------------------------------
/**
 * �C�x���g�i�s�`�F�b�N�ɂ���čĐ탌�x���𒲐�
 *
 * @param   fsys	FIELDSYS_WORK�^�̃|�C���^
 * @param   index	�Đ�f�[�^�e�[�u���̃C���f�b�N�X
 * @param   level	�Đ탌�x��
 *
 * @retval	"������̍Đ����x��"
 *
 * �i�s�`�F�b�N�͂܂�����Ȃ̂ŉ��ł��I
 */
//----------------------------------------------------------------------------------------------
static u16 BS_RevengeDataLevelEventCheck( FIELDSYS_WORK* fsys, u16 index, u16 level )
{
	EVENTWORK* ev = SaveData_GetEventWork( fsys->savedata );
	u16 ret = level;

	switch( level ){

	case 0:
		break;

	default:

		if( SysFlag_BsLvCheck(ev,level) == FALSE ){
			ret = BS_RevengeDataLevelEventCheckSub( index, level );
		}
		break;

	};

	return ret;
}

//----------------------------------------------------------------------------------------------
/**
 * REMATCH_DATA_DUMMY���`�F�b�N���čĐ탌�x����������
 *
 * @param   index	�Đ�f�[�^�e�[�u���̃C���f�b�N�X
 * @param   level	�Đ탌�x��
 *
 * @retval	"������̍Đ����x��"
 */
//----------------------------------------------------------------------------------------------
static u16 BS_RevengeDataLevelEventCheckSub( u16 index, u16 level )
{
	u16 i;
	const REMATCH_DATA* data = RematchDataTbl;

	//�Đ�f�[�^���_�~�[���`�F�b�N
	for( i=(level-1); i > 0; i-- ){

		if( data[index].id[i] != REMATCH_DATA_DUMMY ){
			return i;
		}
	}

	return 0;			//���x��0
}

//----------------------------------------------------------------------------------------------
/**
 * �Đ�g���[�i�[ID���擾
 *
 * @param   index			�Đ�f�[�^�e�[�u���̃C���f�b�N�X
 * @param   level			�Đ�f�[�^�e�[�u���̃��x��
 *
 * @retval  "�Đ�g���[�i�[ID"
 */
//----------------------------------------------------------------------------------------------
static u16 BS_RevengeTrainerIDGet( u16 index, u16 level )
{
	//REMATCH_DATA* data = bs_sys->data;
	const REMATCH_DATA* data = RematchDataTbl;
	return data[index].id[level];
}

//----------------------------------------------------------------------------------------------
/**
 * �Đ퓮��R�[�h���`�F�b�N
 *
 * @param   fldobj		FIELD_OBJ_PTR
 *
 * @retval  "TRUE = �Đ퓮��R�[�h�������AFALSE = ������"
 */
//----------------------------------------------------------------------------------------------
static BOOL BS_RevengeMoveCodeCheck( FIELD_OBJ_PTR fldobj )
{
	//OS_Printf( "mv_code = %d\n", FieldOBJ_MoveCodeGet(fldobj) );
	//OS_Printf( "obj_id = %d\n", FieldOBJ_OBJIDGet(fldobj) );

	if( FieldOBJ_MoveCodeGet(fldobj) == MV_REWAR ){
		return TRUE;
	}

	return FALSE;
}

//----------------------------------------------------------------------------------------------
/**
 * ����R�[�h�Z�b�g
 *
 * @param   fldobj		FIELD_OBJ_PTR
 * @param   code		����R�[�h
 *
 * @retval  none
 */
//----------------------------------------------------------------------------------------------
static void BS_MvSet( FIELD_OBJ_PTR fldobj, u16 code )
{
	//FieldOBJ_MoveCodeSet( fldobj, code );
	FieldOBJ_MoveCodeChange( fldobj, code );
	return;
}

//----------------------------------------------------------------------------------------------
/**
 * �Đ퓮��R�[�h��������A���݌����Ă�������Œ�̓���R�[�h���Z�b�g����(�퓬��ɌĂ΂��)
 *
 * @param   fldobj		FIELD_OBJ_PTR
 *
 * @retval  none
 */
//----------------------------------------------------------------------------------------------
void BS_MvReWarClearDirMvSet( FIELDSYS_WORK* fsys, FIELD_OBJ_PTR fldobj )
{
	FIELD_OBJ_PTR tr_2vs2;
	u32 code;
	int dir;
	
	//�s���`�F�b�N
	if( fldobj == NULL ){
		return;
	}

#if 0
	//����R�[�h���Đ킩�`�F�b�N
	if( FieldOBJ_MoveCodeGet(fldobj) != MV_REWAR ){
		return;
	}
#endif

	//�\�������擾
	dir = FieldOBJ_DirDispGet( fldobj );

	if( dir == DIR_UP ){
		code = MV_UP;
	}else if( dir == DIR_DOWN ){
		code = MV_DOWN;
	}else if( dir == DIR_LEFT ){
		code = MV_LEFT;
	}else{
		code = MV_RIGHT;
	}

#if 1
	//2vs2�̎��̓Z�b�g�ɂȂ��Ă���g���[�i�[�̓���R�[�h�����Ƃ��K�v������I
	tr_2vs2 = BS_2vs2TrPtrGet( fsys, fldobj, BS_2VS2_MV_REWAR_CHK_OFF );
	if( tr_2vs2 != NULL ){
		BS_MvSet( tr_2vs2, code );
	}
#endif

	BS_MvSet( fldobj, code );
	return;
}


//==============================================================================================
//
//	�`�F�b�N
//
//==============================================================================================

//----------------------------------------------------------------------------------------------
/**
 * �O���b�h�Ɏ��܂�܂ő҂�
 *
 * @param   fsys		FIELDSYS_WORK�^�̃|�C���^
 *
 * @retval  "TRUE = ����I���AFALSE = �ړ���"
 */
//----------------------------------------------------------------------------------------------
static BOOL BS_StatusBitCheckMove( FIELDSYS_WORK* fsys )
{
	int i,flag;
	FIELD_OBJ_PTR fldobj;
	u32 obj_max = EventData_GetNpcCount( fsys );

	flag = 0;	//�N���A

	//OS_Printf( "*******���O���b�h�`�F�b�N��*******\n" );

	//OBJ�f�[�^���T�[�`��������
	for( i=0; i < obj_max ;i++ ){

		//�t�B�[���hOBJ�̃|�C���^�擾
		fldobj	= FieldOBJSys_OBJIDSearch( fsys->fldobjsys, i );
		if( fldobj == NULL ){
			continue;
		}

		//�ړ����쒆���`�F�b�N
		if( FieldOBJ_StatusBitCheck_Move(fldobj) == TRUE ){
			//OS_Printf( "no = %d = ���쒆\n", i );
			FieldOBJ_MovePauseClear( fldobj );
			flag = 1;							//����I�����Ă��Ȃ��̂Ńt���OON
		}else{
			//OS_Printf( "no = %d = ����I��\n", i );
			FieldOBJ_MovePause( fldobj );		//����|�[�Y
		}
	}

	if( flag == 0 ){
		return TRUE;
	}else{
		return FALSE;
	}
}

//----------------------------------------------------------------------------------------------
/**
 * �Z�b�g�ɂȂ��Ă���g���[�i�[�̃|�C���^���擾
 *
 * @param   fsys			FIELDSYS_WORK�^�̃|�C���^
 * @param   search_scr_id	�T�[�`����X�N���v�gID
 * @param   search_tr_id	�T�[�`����g���[�i�[ID
 *
 * @retval "NULL=������Ȃ������ANULL�ȊO=�Z�b�g�̃g���[�i�[��FIELD_OBJ_PTR"
 *
 * ���[�h
 * BS_2VS2_MV_REWAR_CHK_ON		(0)		//�Đ퓮��R�[�h�̃`�F�b�N����
 * BS_2VS2_MV_REWAR_CHK_OFF		(1)		//�Đ퓮��R�[�h�̃`�F�b�N�Ȃ�
 */
//----------------------------------------------------------------------------------------------
static FIELD_OBJ_PTR BS_2vs2TrPtrGet( FIELDSYS_WORK* fsys, FIELD_OBJ_PTR search_obj, int mode )
{
	FIELD_OBJ_PTR fldobj;
	u32 i,event_type,scr_id,tr_id;
	u32 obj_max			= EventData_GetNpcCount( fsys );
	u16 search_scr_id	= FieldOBJ_EventIDGet( search_obj );			//�X�N���v�gID���擾
	u16 search_tr_id	= GetTrainerIdByScriptId( search_scr_id );		//�g���[�i�[ID���擾

	//�V���O���o�g���^�C�v�̎��͉������Ȃ��I
	if( CheckTrainer2vs2Type(search_tr_id) == 0 ){
		return NULL;
	}

	//�o�q�����̕Е������͈͂ɓ����Ă��Ȃ���������̂ŁA�]�[������S�T�[�`����I
	for( i=0; i < obj_max ;i++ ){

		//�t�B�[���hOBJ�̃|�C���^�擾
		fldobj	= FieldOBJSys_OBJIDSearch( fsys->fldobjsys, i );
		if( fldobj == NULL ){
			continue;
		}

#if 1
		if(  mode == BS_2VS2_MV_REWAR_CHK_ON ){			//�Đ퓮��R�[�h�̃`�F�b�N����

			//����R�[�h���Đ�ɂȂ��Ă���OBJ�͉������Ȃ�
			if( FieldOBJ_MoveCodeGet(fldobj) == MV_REWAR ){
				continue;
			}
		}
#endif

		//�C�x���g�^�C�v���g���[�i�[���`�F�b�N
		event_type = FieldOBJ_EventTypeGet( fldobj );

		switch( event_type ){
		case EV_TYPE_TRAINER:
		case EV_TYPE_TRAINER_EYEALL:
		case EV_TYPE_TRAINER_KYORO:
		case EV_TYPE_TRAINER_SPIN_STOP_L:
		case EV_TYPE_TRAINER_SPIN_STOP_R:
		case EV_TYPE_TRAINER_SPIN_MOVE_L:
		case EV_TYPE_TRAINER_SPIN_MOVE_R:

			//OS_Printf( "id = %d\n", i );
			//OS_Printf( "event_type = %d\n", event_type );

			scr_id	= FieldOBJ_EventIDGet( fldobj );			//�X�N���v�gID���擾
			tr_id	= GetTrainerIdByScriptId( scr_id );			//�g���[�i�[ID���擾

			//�X�N���v�gID�������ł͂Ȃ��A�g���[�i�[ID�������ɂȂ��Ă���g���[�i�[��T��
			if( (search_scr_id != scr_id) && (search_tr_id == tr_id) ){
				return fldobj;	//�������I
			}
		};
	}

	return NULL;
}




