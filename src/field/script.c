//============================================================================================
/**
 * @file	script.c
 * @bfief	�X�N���v�g���䃁�C������
 * @author	Satoshi Nohara
 * @date	05.08.04
 *
 * 01.11.07	Sousuke Tamada
 * 03.04.15	Satoshi Nohara
 * 05.04.25 Hiroyuki Nakamura
 */
//============================================================================================
#include "common.h"
#include "gflib/msg_print.h"						//STRCODE
#include "system\msgdata.h"							//MSGMAN_TYPE_DIRECT
#include "system\bmp_menu.h"
#include "system/bmp_list.h"
#include "system/pm_str.h"
#include "system/wordset.h"							//WORDSET_Create
#include "system/clact_tool.h"
#include "system/debug_flag.h"

#include "fieldsys.h"
#include "zonedata.h"
#include "sxy.h"
#include "field_clact.h"
#include "fld_menu.h"								//FieldMenuEvChg

#include "system/arc_tool.h"
#include "../fielddata/script/scr_seq.naix"
#include "msgdata\msg.naix"							//NARC_msg_??_dat

#include "field/eventflag.h"
#include "field/evwkdef.h"
#include "vm.h"
#include "scrcmd.h"
#include "script.h"
#include "script_def.h"								//SP_SCRID_SCENE_CHANGE
//#include "scr_tool.h"								//HideItemParamSet
#include "ev_win.h"
#include "report.h"

#include "itemtool/itemsym.h"						//ITEM_KIZUGUSURI
#include "eventdata.h"

#include "battle/battle_common.h"					//���C���N���[�h�ɕK�v
#include "poketool/tr_tool.h"						//TT_TrainerDataParaGet

#include "../fielddata/script/init_scr_def.h"		//SCRID_INIT_SCRIPT

#ifdef PM_DEBUG
#include "../fielddata/script/debug_scr_def.h"
#endif


//============================================================================================
//
//	�f�o�b�N
//
//============================================================================================
//VM_CODE* sp_script;


//============================================================================================
//
//	�X�N���v�gID�I�t�Z�b�g
//
//============================================================================================
#include "scr_offset.h"


//============================================================================================
//
//	��`
//
//============================================================================================
#define SCR_MSG_BUF_SIZE	(1024)					//���b�Z�[�W�o�b�t�@�T�C�Y

typedef void (*fsysFunc)(FIELDSYS_WORK* fsys);		//�֐��|�C���^�^

//�g���[�i�[�����f�[�^�\����
typedef struct {
	int range;						//��������
	int dir;						//�ړ�����
	int scr_id;						//�X�N���v�gID
	int tr_id;						//�g���[�i�[ID
	int tr_type;					//�g���[�i�[�^�C�v
	FIELD_OBJ_PTR fldobj;			//
	TCB_PTR	tcb;					//TCB
}EV_TRAINER_EYE_HITDATA;

#define TRAINER_EYE_HITMAX (2)

//�X�N���v�g���䃏�[�N�\����
struct _EV_SCRIPT_WORK{
	u32 magic_no;					//�C�x���g�̃��[�N���X�N���v�g���䃏�[�N���𔻕�
	u8 seq;							//
	u8 MsgIndex;					//���b�Z�[�W�C���f�b�N�X
	u8 anm_count;					//�A�j���[�V�������Ă��鐔
	u8 common_scr_flag;				//���[�J���E���ʃX�N���v�g�؂�ւ��t���O(0=���[�J���A1=����)
	u8 win_open_flag;				//��b�E�B���h�E���J�������t���O(0=�J���Ă��Ȃ��A1=�J����)
	u8 vm_machine_count;			//�ǉ��������z�}�V���̐�
	u16 script_id;					//���C���̃X�N���v�gID
	BOOL win_flag;					///<�퓬���ʕێ��p���[�N

	//�C�x���g�E�B���h�E
	EV_WIN_WORK* ev_win;			//�C�x���g�E�B���h�E���[�N�ւ̃|�C���^

	//��b�E�B���h�E
	GF_BGL_BMPWIN MsgWinDat;		//�r�b�g�}�b�v�E�B���h�E�f�[�^
	BMPMENU_WORK* mw;				//�r�b�g�}�b�v���j���[���[�N

	int player_dir;					//�C�x���g�N�����̎�l���̌���
	FIELD_OBJ_PTR target_obj;		//�b�������Ώۂ�OBJ�̃|�C���^
	FIELD_OBJ_PTR dummy_obj;		//�����_�~�[OBJ�̃|�C���^

	u16* ret_script_wk;				//�X�N���v�g���ʂ������郏�[�N�̃|�C���^
	VM_MACHINE *vm[VM_MACHINE_MAX];	//���z�}�V���ւ̃|�C���^

	WORDSET* wordset;				//�P��Z�b�g
	STRBUF* msg_buf;				//���b�Z�[�W�o�b�t�@�|�C���^
	STRBUF* tmp_buf;				//�e���|�����o�b�t�@�|�C���^
	void * waiticon;				///<�ҋ@�A�C�R���̃|�C���^
	
	EV_TRAINER_EYE_HITDATA eye_hitdata[TRAINER_EYE_HITMAX];	//�g���[�i�[�������

	u16 work[EVSCR_WORK_MAX];		//���[�N(ANSWORK,TMPWORK�Ȃǂ̑���)

	fsysFunc next_func;				//�X�N���v�g�I�����ɌĂяo�����֐�

	void * subproc_work;			//�T�u�v���Z�X�Ƃ̂��Ƃ�Ɏg�p���郏�[�N�ւ̃|�C���^
	void* pWork;					//���[�N�ւ̔ėp�|�C���^
	EOA_PTR eoa;					//��Ƀt�B�[���h�G�t�F�N�g�̃|�C���^�Ƃ��Ďg��

	TCB_PTR player_tcb;				//���@�`�ԃ��|�[�gTCB

	GF_BGL_BMPWIN CoinWinDat;		//�r�b�g�}�b�v�E�B���h�E�f�[�^
	GF_BGL_BMPWIN GoldWinDat;		//�r�b�g�}�b�v�E�B���h�E�f�[�^

	REPORT_INFO * riw;				///<���|�[�g���p�E�B���h�E���䃏�[�N
};

enum{
	WORDSET_SCRIPT_SETNUM = 8,		//�f�t�H���g�o�b�t�@��
	WORDSET_SCRIPT_BUFLEN = 64,		//�f�t�H���g�o�b�t�@���i�������j
};

//============================================================================================
//
//	�B���A�C�e���f�[�^
//
//============================================================================================
typedef struct{
	u16 itemno;											//�A�C�e���i���o�[
	u8	num;											//��
	u8	response;										//�����x
	u16	sp;												//����(���g�p)
	u16	index;											//�t���O�C���f�b�N
}HIDE_ITEM_DATA;
#include "../fielddata/script/hide_item.dat"			//�B���A�C�e���f�[�^


//============================================================================================
//
//	�v���g�^�C�v�錾
//
//============================================================================================
void EventSet_Script( FIELDSYS_WORK * fsys, u16 scr_id, FIELD_OBJ_PTR obj );
void EventCall_Script( GMEVENT_CONTROL* event, u16 scr_id, FIELD_OBJ_PTR obj, void* ret_script_wk );
static BOOL GMEVENT_ControlScript(GMEVENT_CONTROL * event);
static EV_SCRIPT_WORK* EvScriptWork_Alloc();
static void script_del( VM_MACHINE* core );
static void EvScriptWork_Init(FIELDSYS_WORK * fsys, EV_SCRIPT_WORK* sc, u16 scr_id, FIELD_OBJ_PTR obj, void* ret_wk);

//VM_MACHINE* VMMachineAdd(FIELDSYS_WORK* fsys, u16 scr_id, const VM_CMD* start, const VM_CMD* end);
VM_MACHINE* VMMachineAdd(FIELDSYS_WORK* fsys, u16 scr_id);

static void InitScript( FIELDSYS_WORK* fsys, VM_MACHINE* core, u16 id, u8 type );
static u16 SetScriptDataSub( FIELDSYS_WORK* fsys, VM_MACHINE* core, u16 id );
static void SetScriptData( FIELDSYS_WORK* fsys, VM_MACHINE* core, int index, u32 dat_id );
static void SetZoneScriptData( FIELDSYS_WORK* fsys, VM_MACHINE* core );

//EV_SCRIPT_WORK�̃����o�[�A�N�Z�X
void* GetEvScriptWorkMemberAdrs_Sub( EV_SCRIPT_WORK* sc, u32 id );
void* GetEvScriptWorkMemberAdrs( FIELDSYS_WORK* fsys, u32 id );
void SetEvScriptNextFunc( FIELDSYS_WORK* fsys );

static void EventDataIDJump( VM_MACHINE * core, u16 ev_id );

static void * LoadZoneScriptFile(int zone_id);
static u32 LoadZoneMsgNo(int zone_id);

//�C�x���g���[�N�A�X�N���v�g���[�N�A�N�Z�X�֐�
u16 * GetEventWorkAdrs( FIELDSYS_WORK* fsys, u16 work_no );
u16 GetEventWorkValue( FIELDSYS_WORK* fsys, u16 work_no );
BOOL SetEventWorkValue( FIELDSYS_WORK* fsys, u16 work_no, u16 value );

u16 GetEvDefineObjCode( FIELDSYS_WORK* fsys, u16 no );
BOOL SetEvDefineObjCode( FIELDSYS_WORK* fsys, u16 no, u16 obj_code );

//�C�x���g�t���O
BOOL CheckEventFlag( FIELDSYS_WORK* fsys, u16 flag_no);
void SetEventFlag( FIELDSYS_WORK* fsys, u16 flag_no);
void ResetEventFlag( FIELDSYS_WORK* fsys, u16 flag_no);

void LocalEventFlagClear( FIELDSYS_WORK* fsys );
void TimeEventFlagClear( FIELDSYS_WORK* fsys );

//�g���[�i�[�֘A
u16 GetTrainerIdByScriptId( u16 scr_id );
BOOL GetTrainerLRByScriptId( u16 scr_id );
BOOL CheckTrainer2vs2Type( u16 tr_id );
BOOL CheckEventFlagTrainer( FIELDSYS_WORK* fsys, u16 tr_id );
void SetEventFlagTrainer( FIELDSYS_WORK* fsys, u16 tr_id );
void ResetEventFlagTrainer( FIELDSYS_WORK* fsys, u16 tr_id );

//�B���A�C�e��
u16 GetHideItemFlagNoByScriptId( u16 scr_id );
u16 GetHideItemFlagIndexByScriptId( u16 scr_id );
u8 GetHideItemResponseByScriptId( u16 scr_id );
static BOOL HideItemParamSet( EV_SCRIPT_WORK* sc, u16 scr_id );

//����X�N���v�g
void GameStartScriptInit( FIELDSYS_WORK* fsys );
void SpScriptStart( FIELDSYS_WORK* fsys, u16 scr_id );
BOOL SpScriptSearch( FIELDSYS_WORK* fsys, u8 key );
static u16 SpScriptSearch_Sub( const u8 * p, u8 key );
static u16 SpScriptSearch_Sub2( FIELDSYS_WORK* fsys, const u8 * p, u8 key );


//============================================================================================
//
//	�O���[�o���ϐ�
//
//============================================================================================
//extern const VM_CMD ScriptCommand[];		//�X�N���v�g�R�}���h�֐��e�[�u��
//extern const VM_CMD ScriptCommandEnd[];	//�e�[�u���Ō�̃A�h���X

//�f�o�b�N�p
//u8 debug_script_flag = 0;				//�X�N���v�g�N�����Ă��邩�t���O
#define EV_SCRIPT_WORK_MAGIC_NO		(0x3643f)


//==============================================================================================
//
//	�X�N���v�g����
//
//	���X�N���v�g�C�x���g�Z�b�g
//		EventSet_Script(...)
//
//	�������̗���
//		EvScriptWork_Alloc(...)					���[�N�m��
//		EvScriptWork_Init(...)					�����ݒ�
//		FieldEvent_Set(...)						�C�x���g�ݒ�
//		GMEVENT_ControlScript(...)				�C�x���g����֐�
//				��
//		VMMachineAdd(...)						VM�}�V�[���ǉ�
//
//	�����z�}�V��(VM_MACHINE)
//		�E���z�}�V���ǉ�(VMMachineAdd)
//		�E���z�}�V���̐�(vm_machine_count)��ǉ�
//
//	���X�N���v�g���䃁�C��(GMEVENT_ControlScript)
//		�E���z�}�V���̐�(vm_machine_count)���`�F�b�N���ăC�x���g�I��
//
//==============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * �X�N���v�g�C�x���g�Z�b�g
 *
 * @param	fsys		FIELDSYS_WORK�^�̃|�C���^
 * @param	scr_id		�X�N���v�gID
 * @param	obj			�b�������Ώ�OBJ�̃|�C���^(�Ȃ�����NULL)
 *
 * @retval	none
 */
//--------------------------------------------------------------------------------------------
void EventSet_Script( FIELDSYS_WORK * fsys, u16 scr_id, FIELD_OBJ_PTR obj )
{
	EV_SCRIPT_WORK* sc = EvScriptWork_Alloc();			//���[�N�m��
	EvScriptWork_Init( fsys, sc, scr_id, obj, NULL );	//�����ݒ�
	FieldEvent_Set( fsys, GMEVENT_ControlScript, sc );	//�C�x���g�ݒ�(_Set)
	return;
}

//----------------------------------------------------------------------------------------------
/**
 * �g���[�i�[���������i�[�@���O��EventSet_Script()���N�����Ă�����
 *
 * @param	fsys		FIELDSYS_WORK�^�̃|�C���^
 * @param	fldobj		�������q�b�g����FIELD_OBJ_PTR
 * @param	range		�O���b�h�P�ʂ̎�������
 * @param	dir			�ړ�����
 * @param	scr_id		�����q�b�g�����X�N���v�gID
 * @param	tr_id		�����q�b�g�����g���[�i�[ID
 * @param	tr_type		�g���[�i�[�^�C�v�@�V���O���A�_�u���A�^�b�O����
 * @param	tr_no		���ԖڂɃq�b�g�����g���[�i�[�Ȃ̂�
 */
//----------------------------------------------------------------------------------------------
void EventSet_TrainerEyeData(
		FIELDSYS_WORK* fsys, FIELD_OBJ_PTR fldobj,
		int range, int dir, int scr_id, int tr_id, int tr_type, int tr_no )
{
	EV_SCRIPT_WORK* sc = FieldEvent_GetSpecialWork( fsys->event );
	EV_TRAINER_EYE_HITDATA *eye = &sc->eye_hitdata[tr_no];
	
	eye->range = range;
	eye->dir = dir;
	eye->scr_id = scr_id;
	eye->tr_id = tr_id;
	eye->tr_type = tr_type;
	eye->fldobj = fldobj;
}

#if 0
//----------------------------------------------------------------------------------------------
/**
 * �g���[�i�[�������擾
 *
 * @param	fldobj		�������q�b�g����FIELD_OBJ_PTR
 * @param	range		�O���b�h�P�ʂ̎�������
 * @param	scr_id		�����q�b�g�����X�N���v�gID
 * @param	tr_id		�����q�b�g�����g���[�i�[ID
 * @param	tr_type		�g���[�i�[�^�C�v�@�V���O���A�_�u���A�^�b�O����
 * @param	tr_no		���ԖڂɃq�b�g�����g���[�i�[�Ȃ̂�
 */
//----------------------------------------------------------------------------------------------
void GetTrainerEyeData( FIELD_OBJ_PTR flagobj, int* range, int* scr_id, int* tr_id, int* tr_type, int tr_no )
{
	EV_SCRIPT_WORK* sc = FieldEvent_GetSpecialWork( fsys->event );
	EV_TRAINER_EYE_HITDATA *eye = &sc->eye_hitdata[tr_no];
	
	*range	= eye->range;
	*scr_id	= eye->scr_id;
	*tr_id	= eye->tr_id;
	*tr_type= eye->tr_type;
	return;
}
#endif

//--------------------------------------------------------------------------------------------
/**
 * �X�N���v�g�C�x���g�R�[��
 *
 * @param	event		GMEVENT_CONTROL�^�̃|�C���^
 * @param	scr_id		�X�N���v�gID
 * @param	obj			�b�������Ώ�OBJ�̃|�C���^(�Ȃ�����NULL)
 * @param	ret_script_wk	�X�N���v�g���ʂ������郏�[�N�̃|�C���^
 *
 * @retval	none
 */
//--------------------------------------------------------------------------------------------
void EventCall_Script( GMEVENT_CONTROL* event, u16 scr_id, FIELD_OBJ_PTR obj, void* ret_script_wk )
{
	FIELDSYS_WORK* fsys = FieldEvent_GetFieldSysWork( event );
	EV_SCRIPT_WORK* sc	= EvScriptWork_Alloc();					//���[�N�m��
	EvScriptWork_Init( fsys, sc, scr_id, obj, ret_script_wk );	//�����ݒ�
	FieldEvent_Call( event, GMEVENT_ControlScript, sc );		//�C�x���g�ݒ�(_Call)
	return;
}

//--------------------------------------------------------------------------------------------
/**
 * �X�N���v�g�C�x���g�ؑ�
 *
 * @param	event		GMEVENT_CONTROL�^�̃|�C���^
 * @param	scr_id		�X�N���v�gID
 * @param	obj			�b�������Ώ�OBJ�̃|�C���^(�Ȃ�����NULL)
 *
 * @retval	none
 *
 * ���̃C�x���g����X�N���v�g�ւ̐ؑւ��s��
 */
//--------------------------------------------------------------------------------------------
void EventChange_Script(GMEVENT_CONTROL* event, u16 scr_id, FIELD_OBJ_PTR obj)
{
	FIELDSYS_WORK* fsys = FieldEvent_GetFieldSysWork( event );
	EV_SCRIPT_WORK* sc	= EvScriptWork_Alloc();					//���[�N�m��
	EvScriptWork_Init( fsys, sc, scr_id, obj, NULL );	//�����ݒ�
	FieldEvent_Change( event, GMEVENT_ControlScript, sc );		//�C�x���g�ݒ�
	return;
}


//--------------------------------------------------------------
/**
 * @brief	�X�N���v�g���䃁�C��
 *
 * @param	event		GMEVENT_CONTROL�^
 *
 * @retval	"FALSE = �X�N���v�g���s��"
 * @retval	"TRUE = �X�N���v�g���s�I��"
 */
//--------------------------------------------------------------
static BOOL GMEVENT_ControlScript(GMEVENT_CONTROL * event)
{
	int i;
	fsysFunc func;
	VM_MACHINE* core = NULL;
	EV_SCRIPT_WORK * sc = FieldEvent_GetSpecialWork( event );
	FIELDSYS_WORK* fsys = FieldEvent_GetFieldSysWork( event );

	switch(sc->seq){
	case 0:
		//���z�}�V���ǉ�
		sc->vm[VM_MACHINE_MAIN] = VMMachineAdd( fsys, sc->script_id );
		//VMMachineAdd( fsys, id, &ScriptCmdTbl[0], &ScriptCmdTbl[EVCMD_MAX] );
		sc->vm_machine_count = 1;

		//MSGMAN_Create�̌�ɏ���
		//sc->wordset = WORDSET_Create( HEAPID_WORLD );
		sc->wordset = WORDSET_CreateEx(WORDSET_SCRIPT_SETNUM, WORDSET_SCRIPT_BUFLEN, HEAPID_WORLD);
		sc->msg_buf = STRBUF_Create( SCR_MSG_BUF_SIZE, HEAPID_WORLD );
		sc->tmp_buf = STRBUF_Create( SCR_MSG_BUF_SIZE, HEAPID_WORLD );

		sc->seq++;
		/* FALL THROUGH */
		
	case 1:
		//���z�}�V���R���g���[��
		for( i=0; i < VM_MACHINE_MAX; i++ ){

			core = sc->vm[i];

			if( core != NULL ){

				if( VM_Control(core) == FALSE ){				//���䃁�C��

					script_del(core);							//�X�N���v�g�폜

					if( sc->vm_machine_count == 0 ){
						GF_ASSERT( (0) && "���z�}�V���̐����s���ł��I" );
					}

					sc->vm[i] = NULL;
					sc->vm_machine_count--;
				}
			}
		}

		//���z�}�V���̐����`�F�b�N
		if( sc->vm_machine_count <= 0 ){

			func = sc->next_func;								//�ޔ�

			WORDSET_Delete( sc->wordset );
			STRBUF_Delete( sc->msg_buf );
			STRBUF_Delete( sc->tmp_buf );

			//�f�o�b�N����
			//debug_script_flag = 0;
			sc->magic_no = 0;

			sys_FreeMemoryEz( sc );								//�X�N���v�g���[�N

			//�X�N���v�g�I�����ɌĂяo�����֐����s
			if( func != NULL ){
				func(fsys);
				return FALSE;				//FieldEvent���I�����Ȃ��悤��FALSE��Ԃ��I
			}

			return TRUE;										//FieldEvent_Set�I���I
		}
		break;
	};

	return FALSE;
}

//--------------------------------------------------------------
/**
 * @brief	�X�N���v�g���䃏�[�N�m��
 *
 * @param	fsys		FIELDSYS_WORK�^�̃|�C���^
 *
 * @retval	"�X�N���v�g���䃏�[�N�̃A�h���X"
 */
//--------------------------------------------------------------
static EV_SCRIPT_WORK* EvScriptWork_Alloc()
{
	EV_SCRIPT_WORK* sc;

	sc = sys_AllocMemory( HEAPID_WORLD, sizeof(EV_SCRIPT_WORK) );		//�X�N���v�g���䃏�[�N�m��
	if( sc == NULL ){
		GF_ASSERT( (0) && "�������m�ۂɎ��s���܂����I" );
	}
	memset( sc, 0, sizeof(EV_SCRIPT_WORK) );

	//�f�o�b�N����
	//debug_script_flag = 1;
	sc->magic_no = EV_SCRIPT_WORK_MAGIC_NO;

	return sc;
}

//--------------------------------------------------------------
/**
 * @brief	�X�N���v�g���ʍ폜����
 *
 * @param	core		VM_MACHINE�^�̃|�C���^
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void script_del( VM_MACHINE* core )
{
	MSGMAN_Delete( core->msgman );
	sys_FreeMemoryEz( core->pScript );			//�X�N���v�g�f�[�^
	sys_FreeMemoryEz( core );
	return;
}

//--------------------------------------------------------------
/**
 * @brief	�X�N���v�g���䃏�[�N�����ݒ�
 *
 * @param	fsys		FIELDSYS_WORK�^�̃|�C���^
 * @param	sc			EV_SCRIPT_WORK�^�̃|�C���^
 * @param	scr_id		�X�N���v�gID
 * @param	obj			�b�������Ώ�OBJ�̃|�C���^
 * @param	ret_wk		�X�N���v�g���ʂ������郏�[�N�̃|�C���^
 *
 * @retval	"�X�N���v�g���䃏�[�N�̃A�h���X"
 */
//--------------------------------------------------------------
static void EvScriptWork_Init( FIELDSYS_WORK * fsys, EV_SCRIPT_WORK* sc, u16 scr_id, FIELD_OBJ_PTR obj, void* ret_wk )
{
	u16* objid = GetEvScriptWorkMemberAdrs_Sub( sc, ID_EVSCR_WK_TARGET_OBJID );

	//DIR_NOT = -1
	sc->player_dir = Player_DirGet(fsys->player);	//�C�x���g�N�����̎�l���̌����Z�b�g
	sc->target_obj = obj;							//�b�������Ώ�OBJ�̃|�C���^�Z�b�g
	sc->script_id  = scr_id;						//���C���̃X�N���v�gID
	sc->ret_script_wk = ret_wk;						//�X�N���v�g���ʂ������郏�[�N

	if( obj != NULL ){
		*objid = FieldOBJ_OBJIDGet(obj);			//�b�������Ώ�OBJID�̃Z�b�g
	}

	//�B���A�C�e���̃X�N���v�gID��������(���Ƃňړ�����\��)
	if( (scr_id >= ID_HIDE_ITEM_OFFSET) && (scr_id <= ID_HIDE_ITEM_OFFSET_END) ){
		HideItemParamSet( sc, scr_id );
	}

#ifdef	PM_DEBUG
	OS_Printf("ZONE:%s SCRID:%d\n",ZoneData_GetZoneName(fsys->location->zone_id), scr_id);
#endif

	return;
}

//--------------------------------------------------------------
/**
 * @brief	���z�}�V���ǉ�
 *
 * @param	fsys		FIELDSYS_WORK�^�̃|�C���^
 * @param	id			�X�N���v�gID
 * @param	start		���߃e�[�u���J�n�A�h���X
 * @param	end			���߃e�[�u���I���A�h���X
 *
 * @retval	none
 */
//--------------------------------------------------------------
//VM_MACHINE* VMMachineAdd(FIELDSYS_WORK* fsys, u16 scr_id, const VM_CMD* start, const VM_CMD* end)
VM_MACHINE* VMMachineAdd(FIELDSYS_WORK* fsys, u16 scr_id)
{
	VM_MACHINE* core = NULL;

	core = sys_AllocMemory( HEAPID_WORLD, sizeof(VM_MACHINE) );
	if( core == NULL ){
		GF_ASSERT( (0) && "�������m�ۂɎ��s���܂����I" );
	}

	//���z�}�V��������
	VM_Init( core, ScriptCmdTbl, ScriptCmdMax );
	//VM_Init( core, start, end );

	InitScript( fsys, core, scr_id, 0 );							//���[�J���X�N���v�g������

	return core;
}

//--------------------------------------------------------------
/**
 * @brief	�X�N���v�g�ݒ菉����
 *
 * @param	fsys		FIELDSYS_WORK�^�̃|�C���^
 * @param	core		VM_MACHINE�^�̃|�C���^
 * @param	id			�X�N���v�gID
 * @param	type		"���g�p"
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void InitScript( FIELDSYS_WORK* fsys, VM_MACHINE* core, u16 id, u8 type )
{
	u16 scr_id;

	core->fsys = fsys;
	scr_id = SetScriptDataSub( fsys, core, id );	//�X�N���v�g�f�[�^�A���b�Z�[�W�f�[�^�ǂݍ���
	VM_Start( core, core->pScript );				//���z�}�V���ɃR�[�h�ݒ�
	EventDataIDJump( core, scr_id );
	VM_SetWork( core, (void *)fsys->event );		//�R�}���h�ȂǂŎQ�Ƃ��郏�[�N�Z�b�g
	return;
}

//--------------------------------------------------------------
/**
 * @brief	�X�N���v�gID����X�N���v�g�f�[�^�A���b�Z�[�W�f�[�^��ǂݍ���
 *
 * @param	fsys		FIELDSYS_WORK�^�̃|�C���^
 * @param	core		VM_MACHINE�^�̃|�C���^
 * @param	id			�X�N���v�gID
 *
 * @retval	"�X�N���v�gID����I�t�Z�b�g���������l"
 */
//--------------------------------------------------------------
static u16 SetScriptDataSub( FIELDSYS_WORK* fsys, VM_MACHINE* core, u16 id )
{
	u16 scr_id = id;

	//�T�|�[�g�X�N���v�g��ID���n���ꂽ��
	if( scr_id >= ID_SUPPORT_OFFSET ){
		SetScriptData( fsys, core, NARC_scr_seq_support_bin, NARC_msg_support_dat );
		scr_id -= ID_SUPPORT_OFFSET;

	//�z�B���X�N���v�g��ID���n���ꂽ��
	}else if( scr_id >= ID_HAITATU_OFFSET ){
		SetScriptData( fsys, core, NARC_scr_seq_haitatu_bin, NARC_msg_haitatu_dat );
		scr_id -= ID_HAITATU_OFFSET;

	//TV�C���^�r���[�X�N���v�g��ID���n���ꂽ��
	}else if( scr_id >= ID_TV_INTERVIEW_OFFSET ){
		SetScriptData( fsys, core, NARC_scr_seq_tv_interview_bin, NARC_msg_tv_interview_dat );
		scr_id -= ID_TV_INTERVIEW_OFFSET;

	//TV�X�N���v�g��ID���n���ꂽ��
	}else if( scr_id >= ID_TV_OFFSET ){
		SetScriptData( fsys, core, NARC_scr_seq_tv_bin, NARC_msg_tv_program_dat );
		scr_id -= ID_TV_OFFSET;

	//��`�X�N���v�g��ID���n���ꂽ��
	}else if( scr_id >= ID_HIDEN_OFFSET ){
		SetScriptData( fsys, core, NARC_scr_seq_hiden_bin, NARC_msg_hiden_dat );
		scr_id -= ID_HIDEN_OFFSET;

	//�]���X�N���v�g��ID���n���ꂽ��
	}else if( scr_id >= ID_HYOUKA_SCR_OFFSET ){
		SetScriptData( fsys, core, NARC_scr_seq_hyouka_scr_bin, NARC_msg_hyouka_dat );
		scr_id -= ID_HYOUKA_SCR_OFFSET;

	//�f�o�b�N�X�N���v�g��ID���n���ꂽ��
	}else if( scr_id >= ID_DEBUG_SCR_OFFSET ){
		SetScriptData( fsys, core, NARC_scr_seq_debug_scr_bin, NARC_msg_common_scr_dat );
		scr_id -= ID_DEBUG_SCR_OFFSET;

	//�R���e�X�g��t�X�N���v�g��ID���n���ꂽ��
	}else if( scr_id >= ID_CON_RECEPTION_OFFSET ){
		SetScriptData( fsys, core, NARC_scr_seq_con_reception_bin, NARC_msg_con_reception_dat );
		scr_id -= ID_CON_RECEPTION_OFFSET;

	//�A������X�N���v�g��ID���n���ꂽ��
	}else if( scr_id >= ID_PAIR_SCR_OFFSET ){
		SetScriptData( fsys, core, NARC_scr_seq_pair_scr_bin, NARC_msg_pair_scr_dat );
		scr_id -= ID_PAIR_SCR_OFFSET;

	//�Q�[���J�n�X�N���v�g��ID���n���ꂽ��
	}else if( scr_id >= ID_INIT_SCR_OFFSET ){
		SetScriptData( fsys, core, NARC_scr_seq_init_scr_bin, NARC_msg_common_scr_dat );
		scr_id -= ID_INIT_SCR_OFFSET;

	//��ĉ��X�N���v�g��ID���n���ꂽ��
	}else if( scr_id >= ID_SODATEYA_OFFSET ){
		SetScriptData( fsys, core, NARC_scr_seq_sodateya_bin, NARC_msg_sodateya_dat );
		scr_id -= ID_SODATEYA_OFFSET;

	//�|���g�~�j�Q�[���X�N���v�g��ID���n���ꂽ��
	}else if( scr_id >= ID_PORUTO_SCR_OFFSET ){
		SetScriptData( fsys, core, NARC_scr_seq_poruto_scr_bin, NARC_msg_pgamestart_dat );
		scr_id -= ID_PORUTO_SCR_OFFSET;

	//�O���[�v�X�N���v�g��ID���n���ꂽ��
	}else if( scr_id >= ID_GROUP_OFFSET ){
		SetScriptData( fsys, core, NARC_scr_seq_group_bin, NARC_msg_group_dat );
		scr_id -= ID_GROUP_OFFSET;

	//�|�P�Z���n���X�N���v�g��ID���n���ꂽ��
	}else if( scr_id >= ID_PC_UG_OFFSET ){
		SetScriptData( fsys, core, NARC_scr_seq_pc_ug_bin, NARC_msg_pc_ug_dat );
		scr_id -= ID_PC_UG_OFFSET;

	//�R���V�A���X�N���v�g��ID���n���ꂽ��
	}else if( scr_id >= ID_BATTLE_ROOM_OFFSET ){
		SetScriptData( fsys, core, NARC_scr_seq_battle_room_bin, NARC_msg_battle_room_dat );
		scr_id -= ID_BATTLE_ROOM_OFFSET;

	//�ʐM�X�N���v�g��ID���n���ꂽ��
	}else if( scr_id >= ID_CONNECT_OFFSET ){
		SetScriptData( fsys, core, NARC_scr_seq_connect_bin, NARC_msg_connect_dat );
		scr_id -= ID_CONNECT_OFFSET;

	//�|�P�T�[�`���[�X�N���v�g��ID���n���ꂽ��
	}else if( scr_id >= ID_POKESEARCHER_OFFSET ){
		SetScriptData( fsys, core, NARC_scr_seq_pokesearcher_bin, NARC_msg_bag_dat );
		scr_id -= ID_POKESEARCHER_OFFSET;

	//�Đ�X�N���v�g��ID���n���ꂽ��
	}else if( scr_id >= ID_SAISEN_OFFSET ){
		SetScriptData( fsys, core, NARC_scr_seq_saisen_bin, NARC_msg_saisen_dat );
		scr_id -= ID_SAISEN_OFFSET;

	//�y���b�v�X�N���v�g��ID���n���ꂽ��
	}else if( scr_id >= ID_PERAP_OFFSET ){
		SetScriptData( fsys, core, NARC_scr_seq_perap_bin, NARC_msg_perap_dat );
		scr_id -= ID_PERAP_OFFSET;

	//�T�t�@���X�N���v�g��ID���n���ꂽ��
	}else if( scr_id >= ID_SAFARI_OFFSET ){
		SetScriptData( fsys, core, NARC_scr_seq_safari_bin, NARC_msg_safari_dat );
		scr_id -= ID_SAFARI_OFFSET;

	//�B���A�C�e���X�N���v�g��ID���n���ꂽ��
	}else if( scr_id >= ID_HIDE_ITEM_OFFSET ){
		SetScriptData( fsys, core, NARC_scr_seq_hide_item_bin, NARC_msg_hide_item_dat );
		scr_id -= ID_HIDE_ITEM_OFFSET;

	//�t�B�[���h�A�C�e���X�N���v�g��ID���n���ꂽ��
	}else if( scr_id >= ID_FLD_ITEM_OFFSET ){
		SetScriptData( fsys, core, NARC_scr_seq_fld_item_bin, NARC_msg_fld_item_dat );
		scr_id -= ID_FLD_ITEM_OFFSET;

	//2vs2�g���[�i�[�X�N���v�g��ID���n���ꂽ��
	}else if( scr_id >= ID_TRAINER_2VS2_OFFSET ){
		SetScriptData( fsys, core, NARC_scr_seq_trainer_bin, NARC_msg_common_scr_dat );
		scr_id -= ID_TRAINER_2VS2_OFFSET;

	//�g���[�i�[�X�N���v�g��ID���n���ꂽ��
	}else if( scr_id >= ID_TRAINER_OFFSET ){
		SetScriptData( fsys, core, NARC_scr_seq_trainer_bin, NARC_msg_common_scr_dat );
		scr_id -= ID_TRAINER_OFFSET;

	//���̂݃X�N���v�g��ID���n���ꂽ��
	}else if( scr_id >= ID_KINOMI_OFFSET ){
		SetScriptData( fsys, core, NARC_scr_seq_kinomi_bin, NARC_msg_kinomi_dat );
		scr_id -= ID_KINOMI_OFFSET;

	//BG�X�N���v�g��ID���n���ꂽ��
	}else if( scr_id >= ID_BG_ATTR_OFFSET ){
		SetScriptData( fsys, core, NARC_scr_seq_bg_attr_bin, NARC_msg_bg_attr_dat );
		scr_id -= ID_BG_ATTR_OFFSET;

	//���ʃX�N���v�g��ID���n���ꂽ��
	}else if( scr_id >= ID_COMMON_SCR_OFFSET ){
		SetScriptData( fsys, core, NARC_scr_seq_common_scr_bin, NARC_msg_common_scr_dat );
		scr_id -= ID_COMMON_SCR_OFFSET;

	//���[�J���X�N���v�g��ID���n���ꂽ��
	}else if( scr_id >= ID_START_SCR_OFFSET ){
		SetZoneScriptData( fsys, core );						//�]�[���X�N���v�g�f�[�^�Z�b�g
		scr_id -= ID_START_SCR_OFFSET;

	//SCRID_NULL(0)���n���ꂽ��
	}else{
		SetScriptData( fsys, core, NARC_scr_seq_dummy_scr_bin, NARC_msg_dummy_scr_dat );
		scr_id = 0;
	}

	return scr_id;
}

//----------------------------------------------------------------------------------------------
/**
 * �X�N���v�g�f�[�^�Z�b�g
 *
 * @param	fsys		FIELDSYS_WORK�^�̃|�C���^
 * @param	core		VM_MACHINE�^�̃|�C���^
 * @param	index		�X�N���v�g�f�[�^��ID
 * @param	dat_id		���b�Z�[�W�f�[�^��ID
 */
//----------------------------------------------------------------------------------------------
static void SetScriptData( FIELDSYS_WORK* fsys, VM_MACHINE* core, int index, u32 dat_id )
{
	//���ʃX�N���v�g�f�[�^���[�h
	VM_CODE* script = ArchiveDataLoadMalloc(ARC_SCRIPT, index , HEAPID_WORLD);
	core->pScript = (VM_CODE *)script;

	//���b�Z�[�W�f�[�^�}�l�[�W���[�쐬
	core->msgman = MSGMAN_Create( MSGMAN_TYPE_DIRECT, ARC_MSG, dat_id, HEAPID_WORLD );
	
	return;
}

//----------------------------------------------------------------------------------------------
/**
 * �]�[���X�N���v�g�f�[�^�Z�b�g
 *
 * @param	ID		�X�N���v�g�f�[�^ID
 */
//----------------------------------------------------------------------------------------------
static void SetZoneScriptData( FIELDSYS_WORK* fsys, VM_MACHINE* core )
{
	//�]�[��ID���烍�[�h����X�N���v�g�o�C�i�����擾
	VM_CODE* script = LoadZoneScriptFile(fsys->location->zone_id);
	core->pScript	= (VM_CODE*)script;

	//���b�Z�[�W�f�[�^�}�l�[�W���[�쐬
	core->msgman = MSGMAN_Create( MSGMAN_TYPE_DIRECT, ARC_MSG, 
									LoadZoneMsgNo(fsys->location->zone_id), HEAPID_WORLD );
	
	return;
}


//============================================================================================
//
//	�X�N���v�g���䃏�[�N�̃����o�[�A�N�Z�X
//
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * �X�N���v�g���䃏�[�N�̃����o�[�A�h���X�擾
 *
 * @param	sc		EV_SCRIPT_WORK�^�̃|�C���^
 * @param	id		�擾���郁���oID(script.h�Q��)
 *
 * @return	"�A�h���X"
 */
//--------------------------------------------------------------------------------------------
void* GetEvScriptWorkMemberAdrs_Sub( EV_SCRIPT_WORK* sc, u32 id )
{
	EV_TRAINER_EYE_HITDATA *eye;

	switch( id ){
	//�C�x���g�E�B���h�E���[�N�̃|�C���^
	case ID_EVSCR_EVWIN:
		return &sc->ev_win;

	//��b�E�B���h�E�r�b�g�}�b�v�f�[�^�̃|�C���^
	case ID_EVSCR_MSGWINDAT:
		return &sc->MsgWinDat;

	//�r�b�g�}�b�v���j���[���[�N�̃|�C���^
	case ID_EVSCR_MENUWORK:
		return &sc->mw;

	//��b�E�B���h�E���b�Z�[�W�C���f�b�N�X�̃|�C���^
	case ID_EVSCR_MSGINDEX:
		return &sc->MsgIndex;

	//�A�j���[�V�����̐��̃|�C���^
	case ID_EVSCR_ANMCOUNT:
		return &sc->anm_count;

	//���ʃX�N���v�g�؂�ւ��t���O�̃|�C���^
	case ID_EVSCR_COMMON_SCR_FLAG:
		return &sc->common_scr_flag;

	//��b�E�B���h�E���J�������t���O�̃|�C���^
	case ID_EVSCR_WIN_OPEN_FLAG:
		return &sc->win_open_flag;

	//�ǉ��������z�}�V���̐��̃|�C���^
	case ID_EVSCR_VM_MACHINE_COUNT:
		return &sc->vm_machine_count;

	//���C���̃X�N���v�gID
	case ID_EVSCR_SCRIPT_ID:
		return &sc->script_id;

	//�C�x���g�N�����̎�l���̌���
	case ID_EVSCR_PLAYER_DIR:
		return &sc->player_dir;

	//�b�������Ώۂ�OBJ�̃|�C���^
	case ID_EVSCR_TARGET_OBJ:
		return &sc->target_obj;

	//�����_�~�[OBJ�̃|�C���^
	case ID_EVSCR_DUMMY_OBJ:
		return &sc->dummy_obj;

	//���ʂ������郏�[�N�̃|�C���^
	case ID_EVSCR_RETURN_SCRIPT_WK:
		return &sc->ret_script_wk;

	//���z�}�V��(���C��)�̃|�C���^
	case ID_EVSCR_VM_MAIN:
		return &sc->vm[VM_MACHINE_MAIN];

	//���z�}�V��(�T�u)�̃|�C���^
	case ID_EVSCR_VM_SUB1:
		return &sc->vm[VM_MACHINE_SUB1];

	//�P��Z�b�g
	case ID_EVSCR_WORDSET:
		return &sc->wordset;

	//���b�Z�[�W�o�b�t�@�̃|�C���^
	case ID_EVSCR_MSGBUF:
		return &sc->msg_buf;

	//�e���|�����o�b�t�@�̃|�C���^
	case ID_EVSCR_TMPBUF:
		return &sc->tmp_buf;

	//�ҋ@�A�C�R���̃|�C���^
	case ID_EVSCR_WAITICON:
		return &sc->waiticon;

	//�T�u�v���Z�X�Ƃ̂��Ƃ胏�[�N�ւ̃|�C���^
	case ID_EVSCR_SUBPROC_WORK:
		return &sc->subproc_work;

	//���[�N�ւ̔ėp�|�C���^
	case ID_EVSCR_PWORK:
		return &sc->pWork;

	//�t�B�[���h�G�t�F�N�g�ւ̃|�C���^
	case ID_EVSCR_EOA:
		return &sc->eoa;

	//���@�`�ԃ��|�[�gTCB�̃|�C���^
	case ID_EVSCR_PLAYER_TCB:
		return &sc->player_tcb;

	//�퓬���ʃt���O
	case ID_EVSCR_WIN_FLAG:
		return &sc->win_flag;

	//����(0)�F��������
	case ID_EVSCR_TR0_RANGE:
		eye = &sc->eye_hitdata[0];
		return &eye->range;

	//����(0)�F����
	case ID_EVSCR_TR0_DIR:
		eye = &sc->eye_hitdata[0];
		return &eye->dir;

	//����(0)�F�X�N���v�gID
	case ID_EVSCR_TR0_SCR_ID:
		eye = &sc->eye_hitdata[0];
		return &eye->scr_id;

	//����(0)�F�g���[�i�[ID
	case ID_EVSCR_TR0_ID:
		eye = &sc->eye_hitdata[0];
		return &eye->tr_id;

	//����(0)�F�g���[�i�[�^�C�v
	case ID_EVSCR_TR0_TYPE:
		eye = &sc->eye_hitdata[0];
		return &eye->tr_type;

	//����(0)�F�g���[�i�[OBJ
	case ID_EVSCR_TR0_FLDOBJ:
		eye = &sc->eye_hitdata[0];
		return &eye->fldobj;

	//����(0)�FTCB
	case ID_EVSCR_TR0_TCB:
		eye = &sc->eye_hitdata[0];
		return &eye->tcb;

	//����(1)�F��������
	case ID_EVSCR_TR1_RANGE:
		eye = &sc->eye_hitdata[1];
		return &eye->range;

	//����(1)�F����
	case ID_EVSCR_TR1_DIR:
		eye = &sc->eye_hitdata[1];
		return &eye->dir;

	//����(1)�F�X�N���v�gID
	case ID_EVSCR_TR1_SCR_ID:
		eye = &sc->eye_hitdata[1];
		return &eye->scr_id;

	//����(1)�F�g���[�i�[ID
	case ID_EVSCR_TR1_ID:
		eye = &sc->eye_hitdata[1];
		return &eye->tr_id;

	//����(1)�F�g���[�i�[�^�C�v
	case ID_EVSCR_TR1_TYPE:
		eye = &sc->eye_hitdata[1];
		return &eye->tr_type;

	//����(1)�F�g���[�i�[OBJ
	case ID_EVSCR_TR1_FLDOBJ:
		eye = &sc->eye_hitdata[1];
		return &eye->fldobj;

	//����(1)�FTCB
	case ID_EVSCR_TR1_TCB:
		eye = &sc->eye_hitdata[1];
		return &eye->tcb;

	//�R�C���E�B���h�E�r�b�g�}�b�v�f�[�^�̃|�C���^
	case ID_EVSCR_COINWINDAT:
		return &sc->CoinWinDat;

	//�����E�B���h�E�r�b�g�}�b�v�f�[�^�̃|�C���^
	case ID_EVSCR_GOLDWINDAT:
		return &sc->GoldWinDat;

	//���|�[�g���\���E�B���h�E���䃏�[�N�ւ̃|�C���^
	case ID_EVSCR_REPORTWIN:
		return &sc->riw;

	//���[�N(ANSWORK,TMPWORK�Ȃǂ̑���)�̃|�C���^
	//�X�N���v�g�ƃv���O�����̃f�[�^�����p
	case ID_EVSCR_WK_PARAM0:				
	case ID_EVSCR_WK_PARAM1:
	case ID_EVSCR_WK_PARAM2:
	case ID_EVSCR_WK_PARAM3:
	//�X�N���v�g�ł̃e���|����
	case ID_EVSCR_WK_TEMP0:					
	case ID_EVSCR_WK_TEMP1:
	case ID_EVSCR_WK_TEMP2:
	case ID_EVSCR_WK_TEMP3:
	//�X�N���v�g�����ł̏����p
	case ID_EVSCR_WK_REG0:					
	case ID_EVSCR_WK_REG1:
	case ID_EVSCR_WK_REG2:
	case ID_EVSCR_WK_REG3:
	//�X�N���v�g�ɓ�����Ԃ��ėp���[�N
	case ID_EVSCR_WK_ANSWER:
	//�b�������Ώ�OBJID
	case ID_EVSCR_WK_TARGET_OBJID:
		return &sc->work[ id - ID_EVSCR_WK_START ];

	};

	//�G���[
	GF_ASSERT( (0) && "�����o�[ID���s���ł��I" );

	return NULL;
}

//--------------------------------------------------------------------------------------------
/**
 * �X�N���v�g���䃏�[�N�̃����o�[�A�h���X�擾
 *
 * @param	fsys	FIELDSYS_WORK�^�̃|�C���^
 * @param	id		�擾���郁���oID(script.h�Q��)
 *
 * @return	"�A�h���X"
 */
//--------------------------------------------------------------------------------------------
void* GetEvScriptWorkMemberAdrs( FIELDSYS_WORK* fsys, u32 id )
{
	EV_SCRIPT_WORK* sc = FieldEvent_GetSpecialWork( fsys->event );

	if( sc->magic_no != EV_SCRIPT_WORK_MAGIC_NO ){
		GF_ASSERT( (0) && "�N��(�m��)���Ă��Ȃ��X�N���v�g�̃��[�N�ɃA�N�Z�X���Ă��܂��I" );
	}

	return GetEvScriptWorkMemberAdrs_Sub( sc, id );
}

//--------------------------------------------------------------------------------------------
/**
 * �X�N���v�g���䃏�[�N��"next_func"�Ƀ��j���[�Ăяo�����Z�b�g
 *
 * @param	fsys	FIELDSYS_WORK�^�̃|�C���^
 *
 * @return	none
 *
 * �t�B�[���h���j���[�Ăяo������I
 *
 * ���ꂪ�c�������炭�Ȃ�̂ŁA�ėp�I�Ɏg���Ȃ��悤�ɂ��Ă���I
 */
//--------------------------------------------------------------------------------------------
void SetEvScriptNextFunc( FIELDSYS_WORK* fsys )
{
	EV_SCRIPT_WORK* sc	= FieldEvent_GetSpecialWork( fsys->event );
	sc->next_func		= FieldMenuEvChg;
	return;
}

//--------------------------------------------------------------------------------------------
/**
 * ID�W�����v
 *
 * @param	core	VM_MACHINE�^�̃|�C���^
 * @param	id		�X�N���v�gID
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void EventDataIDJump( VM_MACHINE * core, u16 ev_id )
{
	core->PC += (ev_id * 4);			//ID���i�߂�(adrs��long�Ȃ̂�*4)
	core->PC += VMGetU32( core );		//���x���I�t�Z�b�g���i�߂�
	return;
}

//--------------------------------------------------------------------------------------------
/**
 * 
 *
 * @param	zone_id		�]�[��ID
 *
 * @retval	""
 */
//--------------------------------------------------------------------------------------------
static void * LoadZoneScriptFile(int zone_id)
{
	return ArchiveDataLoadMalloc(ARC_SCRIPT, ZoneData_GetScriptArchiveID(zone_id), HEAPID_WORLD);
}

#if 0
void * LoadZoneMsgFile(int zone_id);
void * LoadZoneMsgFile(int zone_id)
{
	return ArchiveDataLoadMalloc(ARC_SCRIPT_MSG, ZoneData_GetMsgArchiveID(zone_id), HEAPID_WORLD);
}
#endif

//--------------------------------------------------------------------------------------------
/**
 * �}�b�v�Ǘ��\�ɓo�^����Ă���A���b�Z�[�W�t�@�C���̃A�[�J�C�uID���擾
 *
 * @param	zone_id		�]�[��ID
 *
 * @retval	"�A�[�J�C�uID"
 */
//--------------------------------------------------------------------------------------------
static u32 LoadZoneMsgNo(int zone_id)
{
	return ZoneData_GetMsgArchiveID(zone_id);
}


//============================================================================================
//
//
//
//============================================================================================

//------------------------------------------------------------------
/**
 * @brief	�C�x���g���[�N�A�h���X���擾
 *
 * @param	ev			�C�x���g���[�N�ւ̃|�C���^
 * @param	fsys		FIELDSYS_WORK�ւ̃|�C���^
 * @param	work_no		���[�N�i���o�[
 *
 * @return	"���[�N�̃A�h���X"
 *
 * @li	work_no < 0x8000	�ʏ�̃Z�[�u���[�N
 * @li	work_no >= 0x8000	�X�N���v�g���䃏�[�N�̒��Ɋm�ۂ��Ă��郏�[�N
 */
//------------------------------------------------------------------
u16 * GetEventWorkAdrs( FIELDSYS_WORK* fsys, u16 work_no )
{
	EVENTWORK* ev;
	ev = SaveData_GetEventWork(fsys->savedata);

	if( work_no < SVWK_START ){ return NULL; }
	if( work_no < SCWK_START ){ return EventWork_GetEventWorkAdrs(ev,work_no); }

	//�X�N���v�g���䃏�[�N�̒��ŁAANSWORK�Ȃǂ̃��[�N���m�ۂ��Ă��܂�
	return GetEvScriptWorkMemberAdrs( fsys, (ID_EVSCR_WK_START + work_no - SCWK_START) );
}

//------------------------------------------------------------------
/**
 * @brief	�C�x���g���[�N�̒l���擾
 *
 * @param	fsys		FIELDSYS_WORK�ւ̃|�C���^
 * @param	work_no		���[�N�i���o�[
 *
 * @return	"���[�N�̒l"
 */
//------------------------------------------------------------------
u16 GetEventWorkValue( FIELDSYS_WORK* fsys, u16 work_no )
{
	u16* res = GetEventWorkAdrs( fsys, work_no );
	if( res == NULL ){ return work_no; }
	return *res;
}

//------------------------------------------------------------------
/**
 * @brief	�C�x���g���[�N�̒l���Z�b�g
 *
 * @param	fsys		FIELDSYS_WORK�ւ̃|�C���^
 * @param	work_no		���[�N�i���o�[
 * @param	value		�Z�b�g����l
 *
 * @return	"TRUE=�Z�b�g�o�����AFALSE=�Z�b�g�o���Ȃ�����"
 */
//------------------------------------------------------------------
BOOL SetEventWorkValue( FIELDSYS_WORK* fsys, u16 work_no, u16 value )
{
	u16* res = GetEventWorkAdrs( fsys, work_no );
	if( res == NULL ){ return FALSE; }
	*res = value;
	return TRUE;
}

//------------------------------------------------------------------
/**
 * @brief	�X�N���v�g����w�肷��OBJ�R�[�h���擾
 *
 * @param	fsys		FIELDSYS_WORK�ւ̃|�C���^
 * @param	no			0-15
 *
 * @return	"OBJ�L�����R�[�h"
 */
//------------------------------------------------------------------
u16 GetEvDefineObjCode( FIELDSYS_WORK* fsys, u16 no )
{
	GF_ASSERT( (no < OBJCHR_WORK_MAX) && "�������s���ł��I" );
	return GetEventWorkValue( fsys, (OBJCHR_WORK_START+no) );
}

//------------------------------------------------------------------
/**
 * @brief	�X�N���v�g����w�肷��OBJ�R�[�h���Z�b�g
 *
 * @param	fsys		FIELDSYS_WORK�ւ̃|�C���^
 * @param	no			0-15
 * @param	obj_code	OBJ�R�[�h
 *
 * @return	"TRUE=�Z�b�g�o�����AFALSE=�Z�b�g�o���Ȃ�����"
 */
//------------------------------------------------------------------
BOOL SetEvDefineObjCode( FIELDSYS_WORK* fsys, u16 no, u16 obj_code )
{
	GF_ASSERT( (no < OBJCHR_WORK_MAX) && "�������s���ł��I" );
	return SetEventWorkValue( fsys, (OBJCHR_WORK_START+no), obj_code );
}


//============================================================================================
//
//	�t���O�֘A
//
//============================================================================================

//------------------------------------------------------------------
/**
 * @brief	�C�x���g�t���O���`�F�b�N����
 *
 * @param	fsys		FIELDSYS_WORK�̃|�C���^
 * @param	flag_no		�t���O�i���o�[
 *
 * @retval	"1 = �t���OON"
 * @retval	"0 = �t���OOFF"
 */
//------------------------------------------------------------------
BOOL CheckEventFlag( FIELDSYS_WORK* fsys, u16 flag_no)
{
	return EventWork_CheckEventFlag( SaveData_GetEventWork(fsys->savedata),	flag_no );
}

//------------------------------------------------------------------
/**
 * @brief	�C�x���g�t���O���Z�b�g����
 *
 * @param	fsys		FIELDSYS_WORK�̃|�C���^
 * @param	flag_no		�t���O�i���o�[
 *
 * @return	none
 */
//------------------------------------------------------------------
void SetEventFlag( FIELDSYS_WORK* fsys, u16 flag_no)
{
	EventWork_SetEventFlag( SaveData_GetEventWork(fsys->savedata),flag_no );
	return;
}

//------------------------------------------------------------------
/**
 * @brief	�C�x���g�t���O�����Z�b�g����
 *
 * @param	fsys		FIELDSYS_WORK�̃|�C���^
 * @param	flag_no		�t���O�i���o�[
 *
 * @return	none
 */
//------------------------------------------------------------------
void ResetEventFlag( FIELDSYS_WORK* fsys, u16 flag_no)
{
	EventWork_ResetEventFlag( SaveData_GetEventWork(fsys->savedata), flag_no );
	return;
}

//------------------------------------------------------------------
/**
 * @brief	�}�b�v������̃Z�[�u�t���O���N���A����
 *
 * @param	fsys		FIELDSYS_WORK�̃|�C���^
 *
 * @return	none
 */
//------------------------------------------------------------------
void LocalEventFlagClear( FIELDSYS_WORK* fsys )
{
	int i;
	EVENTWORK* event;

#if 0
	//�N���A�O
	for( i=0; i < 80 ;i++ ){
		OS_Printf( "flag %d= %d\n", i, CheckEventFlag(fsys,i) );
	}
	for( i=0x4000; i < 0x4020 ;i++ ){
		OS_Printf( "work %d= %d\n", i, GetEventWorkValue(fsys,i) );
	}
#endif

	//�C�x���g���[�N�̃|�C���^�擾
	event = SaveData_GetEventWork(fsys->savedata);

	//���[�J���t���O�̃N���A"8bit * 8 = 64��"
	//"0"�͖����ȃi���o�[�Ȃ̂�1��n���Ď擾���Ă���
	memset( EventWork_GetEventFlagAdrs(event,1), 0, LOCAL_FLAG_AREA_MAX );

	//���[�J�����[�N�̃N���A"32��"
	memset( EventWork_GetEventWorkAdrs(event,LOCAL_WORK_START), 0, 2*LOCAL_WORK_MAX );

#if 0
	//�N���A��
	for( i=0; i < 80 ;i++ ){
		OS_Printf( "flag %d= %d\n", i, CheckEventFlag(fsys,i) );
	}
	for( i=0x4000; i < 0x4020 ;i++ ){
		OS_Printf( "work %d= %d\n", i, GetEventWorkValue(fsys,i) );
	}
#endif

	return;
}

//------------------------------------------------------------------
/**
 * @brief	1���o�߂��ƂɃN���A�����t���O���N���A����
 *
 * @param	fsys		FIELDSYS_WORK�̃|�C���^
 *
 * @return	none
 */
//------------------------------------------------------------------
void TimeEventFlagClear( FIELDSYS_WORK* fsys )
{
	EVENTWORK* event;

	//�C�x���g���[�N�̃|�C���^�擾
	event = SaveData_GetEventWork(fsys->savedata);

	memset( EventWork_GetEventFlagAdrs(event,TIMEFLAG_START), 0, TIMEFLAG_AREA_MAX );

	return;
}

//============================================================================================
//
//		�v���O�������X�N���v�g�ėp
//
//
//
//============================================================================================
//--------------------------------------------------------------
/**
 * @brief	�v���O��������X�N���v�g�փp�����[�^��n��
 * @param	event	�X�N���v�g���N�����Ă���C�x���g�ւ̃|�C���^
 * @param	prm0	�p�����[�^�O�iSCWK_PARAM0�j
 * @param	prm1	�p�����[�^�P�iSCWK_PARAM1�j
 * @param	prm2	�p�����[�^�Q�iSCWK_PARAM2�j
 * @param	prm3	�p�����[�^�R�iSCWK_PARAM3�j
 */
//--------------------------------------------------------------
void EvScript_SetParam(FIELDSYS_WORK * fsys, u16 prm0, u16 prm1, u16 prm2, u16 prm3)
{
	*(u16*)GetEvScriptWorkMemberAdrs( fsys, ID_EVSCR_WK_PARAM0 ) = prm0;
	*(u16*)GetEvScriptWorkMemberAdrs( fsys, ID_EVSCR_WK_PARAM1 ) = prm1;
	*(u16*)GetEvScriptWorkMemberAdrs( fsys, ID_EVSCR_WK_PARAM2 ) = prm2;
	*(u16*)GetEvScriptWorkMemberAdrs( fsys, ID_EVSCR_WK_PARAM3 ) = prm3;
}

//============================================================================================
//
//	�g���[�i�[�t���O�֘A
//
//	�E�X�N���v�gID����A�g���[�i�[ID���擾���āA�t���O�`�F�b�N
//	BOOL CheckEventFlagTrainer( fsys, GetTrainerIdByScriptId(scr_id) );
//
//============================================================================================
#define GET_TRAINER_FLAG(id)	( TR_FLAG_START+(id) )

//--------------------------------------------------------------
/**
 * �X�N���v�gID����A�g���[�i�[ID���擾
 *
 * @param   scr_id		�X�N���v�gID
 *
 * @retval  "�g���[�i�[ID = �t���O�C���f�b�N�X"
 */
//--------------------------------------------------------------
u16 GetTrainerIdByScriptId( u16 scr_id )
{
	if( scr_id < ID_TRAINER_2VS2_OFFSET ){
		return (scr_id - ID_TRAINER_OFFSET + 1);		//1�I���W��
	}else{
		return (scr_id - ID_TRAINER_2VS2_OFFSET + 1);		//1�I���W��
	}
}

//--------------------------------------------------------------
/**
 * �X�N���v�gID����A���E�ǂ���̃g���[�i�[���擾
 *
 * @param   scr_id		�X�N���v�gID
 *
 * @retval  "0=���A1=�E"
 */
//--------------------------------------------------------------
BOOL GetTrainerLRByScriptId( u16 scr_id )
{
	if( scr_id < ID_TRAINER_2VS2_OFFSET ){
		return 0;
	}else{
		return 1;
	}
}

//--------------------------------------------------------------
/**
 * �g���[�i�[ID����A�_�u���o�g���^�C�v���擾
 *
 * @param   tr_id		�g���[�i�[ID
 *
 * @retval  "0=�V���O���o�g���A1=�_�u���o�g��"
 */
//--------------------------------------------------------------
BOOL CheckTrainer2vs2Type( u16 tr_id )
{
	if( TT_TrainerDataParaGet(tr_id, ID_TD_fight_type) == FIGHT_TYPE_1vs1 ){	//1vs1
		OS_Printf( "trainer_type = 1vs1 " );
		return 0;
		//return SCR_EYE_TR_TYPE_SINGLE;
	}

	OS_Printf( "trainer_type = 2vs2 " );
	return 1;
	//return SCR_EYE_TR_TYPE_DOUBLE;
}

//------------------------------------------------------------------
/**
 * @brief	�g���[�i�[�C�x���g�t���O���`�F�b�N����
 *
 * @param	fsys		FIELDSYS_WORK�̃|�C���^
 * @param	tr_id		�g���[�i�[ID
 *
 * @retval	"1 = �t���OON"
 * @retval	"0 = �t���OOFF"
 */
//------------------------------------------------------------------
BOOL CheckEventFlagTrainer( FIELDSYS_WORK* fsys, u16 tr_id )
{
	return EventWork_CheckEventFlag( 
				SaveData_GetEventWork(fsys->savedata), GET_TRAINER_FLAG(tr_id) );
}

//------------------------------------------------------------------
/**
 * @brief	�g���[�i�[�C�x���g�t���O���Z�b�g����
 *
 * @param	fsys		FIELDSYS_WORK�̃|�C���^
 * @param	tr_id		�g���[�i�[ID
 *
 * @return	none
 */
//------------------------------------------------------------------
void SetEventFlagTrainer( FIELDSYS_WORK* fsys, u16 tr_id )
{
	EventWork_SetEventFlag( SaveData_GetEventWork(fsys->savedata), GET_TRAINER_FLAG(tr_id) );
	return;
}

//------------------------------------------------------------------
/**
 * @brief	�g���[�i�[�C�x���g�t���O�����Z�b�g����
 *
 * @param	fsys		FIELDSYS_WORK�̃|�C���^
 * @param	tr_id		�g���[�i�[ID
 *
 * @return	none
 */
//------------------------------------------------------------------
void ResetEventFlagTrainer( FIELDSYS_WORK* fsys, u16 tr_id )
{
	EventWork_ResetEventFlag( SaveData_GetEventWork(fsys->savedata), GET_TRAINER_FLAG(tr_id) );
	return;
}


//============================================================================================
//
//	�B���A�C�e���֘A
//
//	�E�X�N���v�gID����A�B���A�C�e���t���O���擾���āA�t���O�`�F�b�N
//	BOOL CheckEventFlag( fsys, GetHideItemFlagNoByScriptId(scr_id) );
//
//============================================================================================

//--------------------------------------------------------------
/**
 * �X�N���v�gID����A�B���A�C�e���t���O�i���o�[���擾
 *
 * @param   scr_id		�X�N���v�gID
 *
 * @retval  "�t���O�i���o�["
 */
//--------------------------------------------------------------
u16 GetHideItemFlagNoByScriptId( u16 scr_id )
{
	return (scr_id - ID_HIDE_ITEM_OFFSET + FH_FLAG_START);
}

//--------------------------------------------------------------
/**
 * �X�N���v�gID����A�B���A�C�e���t���O�C���f�b�N�X���擾
 *
 * @param   scr_id		�X�N���v�gID
 *
 * @retval  "�t���O�C���f�b�N�X"
 */
//--------------------------------------------------------------
u16 GetHideItemFlagIndexByScriptId( u16 scr_id )
{
	return (scr_id - ID_HIDE_ITEM_OFFSET);
}

//--------------------------------------------------------------
/**
 * �X�N���v�gID����A�B���A�C�e���̔������擾
 *
 * @param   scr_id		�X�N���v�gID
 *
 * @retval  "����"
 *
 * �B���A�C�e���̃X�N���v�g����������ĂԂ悤�ɂ���I
 */
//--------------------------------------------------------------
u8 GetHideItemResponseByScriptId( u16 scr_id )
{
	int i;
	u8	index;
	const HIDE_ITEM_DATA* data;

	data	= &hide_item_data[0];
	index	= GetHideItemFlagIndexByScriptId(scr_id);			//�t���O�C���f�b�N�X�擾

	//�T�[�`����
	for( i=0; i < HIDE_ITEM_DATA_MAX ;i++ ){
		if( data[i].index == index ){
			break;
		}
	}

	//������Ȃ�����
	if( i >= HIDE_ITEM_DATA_MAX ){
		GF_ASSERT( (0) && "�B���A�C�e���f�[�^�ɊY������f�[�^������܂���I" );
		return 0;
	}

	return data[i].response;
}

//--------------------------------------------------------------
/**
 * �B���A�C�e���p�����[�^�����[�N�ɃZ�b�g
 *
 * @param   sc			EV_SCRIPT_WORK�^�̃|�C���^
 * @param   scr_id		�X�N���v�gID
 *
 * @retval  "0=�Z�b�g���s�A1=�Z�b�g����"
 *
 * �g�p���Ă���I
 * SCWK_PARAM0
 * SCWK_PARAM1
 * SCWK_PARAM2
 */
//--------------------------------------------------------------
static BOOL HideItemParamSet( EV_SCRIPT_WORK* sc, u16 scr_id )
{
	int i;
	u8	index;
	const HIDE_ITEM_DATA* data;
	u16* param0 = GetEvScriptWorkMemberAdrs_Sub( sc, ID_EVSCR_WK_PARAM0 );
	u16* param1 = GetEvScriptWorkMemberAdrs_Sub( sc, ID_EVSCR_WK_PARAM1 );
	u16* param2 = GetEvScriptWorkMemberAdrs_Sub( sc, ID_EVSCR_WK_PARAM2 );

	data	= &hide_item_data[0];
	index	= GetHideItemFlagIndexByScriptId(scr_id);		//�t���O�C���f�b�N�X�擾

	//�T�[�`����
	for( i=0; i < HIDE_ITEM_DATA_MAX ;i++ ){
		if( data[i].index == index ){
			break;
		}
	}

	//������Ȃ�����
	if( i >= HIDE_ITEM_DATA_MAX ){
		GF_ASSERT( (0) && "�B���A�C�e���f�[�^�ɊY������f�[�^������܂���I" );
		return 0;
	}

	*param0 = data[i].itemno;						//�A�C�e���i���o�[
	*param1 = data[i].num;							//��
	*param2 = GetHideItemFlagNoByScriptId(scr_id);	//�t���O�i���o�[

	return 1;
}

#define DEBUG_HIDE_ITEM_LIST	//�f�o�b�N�L��
//--------------------------------------------------------------
/**
 * ��ʓ��ɂ���B���A�C�e�����������Ċm�ۂ������X�g�ɓo�^
 *
 * @param   fsys		FIELDSYS_WORK�^�̃|�C���^
 * @param   heapid		�q�[�vID
 *
 * @retval  "���X�g�̃A�h���X"
 *
 * ���������Y�ꂸ�ɁI
 */
//--------------------------------------------------------------
HIDE_ITEM_LIST* HideItem_CreateList( FIELDSYS_WORK * fsys, int heapid );
HIDE_ITEM_LIST* HideItem_CreateList( FIELDSYS_WORK * fsys, int heapid )
{
	HIDE_ITEM_LIST* list;
	const BG_TALK_DATA* bg;
	int	hero_gx,hero_gz,i,max,count,tmp;
	int l,r,u,d;

	count = 0;

	//BG�f�[�^���擾
	max = EventData_GetNowBgTalkDataSize( fsys );
	max++;		//�I���R�[�h������̂�+1

	//�������m��
	list = sys_AllocMemory( heapid, sizeof(HIDE_ITEM_LIST) * max );

	//BG�f�[�^�����݂��Ă��Ȃ�������
	if( max == 1 ){
		//�I���R�[�h�Z�b�g
		list[0].response= HIDE_LIST_RESPONSE_NONE;
		list[0].gx		= 0xffff;
		list[0].gz		= 0xffff;
		return list;
	}

	//BG�f�[�^�擾
	bg	= EventData_GetNowBgTalkData( fsys );
	if( bg == NULL ){
		//�I���R�[�h�Z�b�g
		list[0].response= HIDE_LIST_RESPONSE_NONE;
		list[0].gx		= 0xffff;
		list[0].gz		= 0xffff;
		return list;
	}

	//��l���̈ʒu�擾
	hero_gx = Player_NowGPosXGet( fsys->player );
	hero_gz = Player_NowGPosZGet( fsys->player );

	//�����͈͂��Z�b�g(3D�͈ӎ������̊ȈՔ�)
	l = hero_gx - HIDE_LIST_SX;
	r = hero_gx + HIDE_LIST_SX;
	u = hero_gz - HIDE_LIST_TOP;
	d = hero_gz + HIDE_LIST_BOTTOM;

	//�␳
	if( l < 0 ){ l = 0; }
	//if( r < 0 ){ 0 };
	if( u < 0 ){ u = 0; }
	//if( d < 0 ){ 0 };

#ifdef DEBUG_HIDE_ITEM_LIST
	OS_Printf( "\n�������͈́�\n" );
	OS_Printf( "l = %d\n", l );
	OS_Printf( "r = %d\n", r );
	OS_Printf( "u = %d\n", u );
	OS_Printf( "d = %d\n", d );
#endif

	//BG�f�[�^���T�[�`��������
	for( i=0; i < max ;i++ ){

		//�B���A�C�e���^�C�v�ŁA�܂����肵�Ă��Ȃ�������
		if( (bg[i].type == BG_TALK_TYPE_HIDE) &&
			(CheckEventFlag(fsys, GetHideItemFlagNoByScriptId(bg[i].id)) == 0) ){

			//�����͈͓��ɂ��邩�`�F�b�N
			if( (bg[i].gx >= l) &&
				(bg[i].gx <= r) &&
				(bg[i].gz >= u) &&
				(bg[i].gz <= d) ){

				//�X�N���v�gID����A�B���A�C�e���̔������擾
				list[count].response= GetHideItemResponseByScriptId( bg[i].id );

#if 0
				//���������W�����̂܂ܑ��
				list[count].gx		= bg[i].gx;
				list[count].gz		= bg[i].gz;

				//���[�J�����W
				list[count].gx		= (bg[i].gx % 32);
				list[count].gz		= (bg[i].gz % 32);
#endif	

				//�����0,0�Ƃ��Ď擾�������W
				//(��l���̈ʒu����̍��������߂�)
				tmp = ( hero_gx - bg[i].gx );
				list[count].gx = abs(HIDE_LIST_SX - tmp);
				tmp = ( hero_gz - bg[i].gz );
				list[count].gz = abs(HIDE_LIST_TOP - tmp);

#ifdef DEBUG_HIDE_ITEM_LIST
				OS_Printf( "\n����l���̈ʒu��\n" );
				OS_Printf( "hero_gx = %d\n", hero_gx );
				OS_Printf( "hero_gz = %d\n", hero_gz );

				OS_Printf( "\n���������B���A�C�e���̈ʒu��\n" );
				OS_Printf( "bg[i].gx = %d\n", bg[i].gx );
				OS_Printf( "bg[i].gz = %d\n", bg[i].gz );

				OS_Printf( "\n�������0,0�Ƃ��Ď擾�������W��\n" );
				OS_Printf( "list[count].gx = %d\n", list[count].gx );
				OS_Printf( "list[count].gz = %d\n", list[count].gz );
#endif

				count++;
			}
		}
	}

	//�I���R�[�h�Z�b�g
	list[count].response= HIDE_LIST_RESPONSE_NONE;
	list[count].gx		= 0xffff;
	list[count].gz		= 0xffff;

	return list;
}


//============================================================================================
//
//	����X�N���v�g�֘A
//
//============================================================================================

//------------------------------------------------------------------
/**
 * @brief	�Q�[���J�n �X�N���v�g�����ݒ�̎��s
 *
 * @param	fsys		FIELDSYS_WORK�^�̃|�C���^
 *
 * @return	none
 */
//------------------------------------------------------------------
void GameStartScriptInit( FIELDSYS_WORK* fsys )
{
	SpScriptStart( fsys, SCRID_INIT_SCRIPT );

#ifdef PM_DEBUG

	//�u�f�o�b�N�������v��I�����Ă�����
	if( DebugFlagData.debug_mode == TRUE ){

		//�|�P�Z���n���X�g�b�p�[�폜�A�Ƃ������蒠�C�x���g����
		SpScriptStart( fsys, SCRID_DEBUG_PC_UG );
	}
#endif

	return;
}

//------------------------------------------------------------------
/**
 * @brief	EVENT�ł͂Ȃ�����X�N���v�g���s
 *
 * @param	fsys		FIELDSYS_WORK�^�̃|�C���^
 * @param	scr_id		�X�N���v�gID
 *
 * @return	none
 *
 * ���ӁI
 * EV_SCRIPT_WORK���m�ۂ��Ă��Ȃ��̂ŁA
 * SCWK_ANSWER�Ȃǂ̃��[�N�͎g�p���邱�Ƃ��o���Ȃ��I
 * LOCALWORK0�Ȃǂ��g�p����悤�ɂ���I
 *
 * ���ʃX�N���v�g�ɂ��Ă͌���g�p�s�I
 * �Ή��\�肾���A�]�[�����܂��������ɏ����������邩���H
 * ���܂����Ȃ������H
 *
 * �t���O�`�F���W���x���ŋ��ʃX�N���v�g���g�������Ƃ��́A
 * ��t���O�`�F���W���x�����������ƂɂȂ邩���H
 * �Е��́A�]�[���ł��Ƃ������́A�Е��́A���ʃX�N���v�g��ID���w��H�B�B�B
 */
//------------------------------------------------------------------
void SpScriptStart( FIELDSYS_WORK* fsys, u16 scr_id )
{
	VM_MACHINE*core = VMMachineAdd( fsys, scr_id );
	while( VM_Control( core ) == TRUE );
	script_del(core);	//�X�N���v�g�폜
	return;
}

//------------------------------------------------------------------
/**
 * @brief	����X�N���v�g�������Ď��s
 *
 * @param	fsys		FIELDSYS_WORK�^�̃|�C���^
 * @param	key			����X�N���v�gID
 *
 * @return	"TRUE=����X�N���v�g���s�AFALSE=�������Ȃ�"
 */
//------------------------------------------------------------------
BOOL SpScriptSearch( FIELDSYS_WORK* fsys, u8 key )
{
	u16 scr_id;
	const u8 * p;

	p = EventData_GetSpecialScript(fsys);
	if (p == NULL) {
		return FALSE;
	}
	//����X�N���v�g����
	if( key == SP_SCRID_SCENE_CHANGE ){
		scr_id = SpScriptSearch_Sub2( fsys, p, key );	//�����`�F�b�N�L��
	}else{
		scr_id = SpScriptSearch_Sub( p, key );			//�����`�F�b�N����
	}

	//OS_Printf( "scr_id = %d\n", scr_id );
	if( scr_id == 0xffff ){
		return FALSE;
	}

	//����X�N���v�g���s
	if( key == SP_SCRID_SCENE_CHANGE ){
		EventSet_Script( fsys, scr_id, NULL );
	}else{
		SpScriptStart( fsys, scr_id );
	}
	return TRUE;
}

//------------------------------------------------------------------
/**
 * @brief	�w�b�_�[�f�[�^����w��^�C�v�̂��̂�����
 *
 * @param	key			����X�N���v�gID
 *
 * @return	"�X�N���v�gID"
 */
//------------------------------------------------------------------
static u16 SpScriptSearch_Sub(const u8 * p, u8 key )
{

	while( 1 ){
		//�I���L�q�`�F�b�N(SP_EVENT_DATA_END)
		if( *p == SP_SCRID_NONE ){
			return 0xffff;
		}

		//�w��^�C�v�̓���X�N���v�g����
		if( *p == key ){
			p++;								//����X�N���v�gID������
			return ( *p + ( *(p+1)<<8 ) );		//�X�N���v�gID��Ԃ�
		}

		p += (1 + 2 + 2);						//����X�N���v�gID+�X�N���v�gID+�_�~�[������
	}

	return 0xffff;								//����������Ȃ�����
}

//------------------------------------------------------------------
/**
 * @brief	�w�b�_�[�f�[�^����w��^�C�v�̂��̂���������(�V�[���C�x���g)
 *
 * @param	key			����X�N���v�gID
 *
 * @return	"�X�N���v�gID"
 */
//------------------------------------------------------------------
static u16 SpScriptSearch_Sub2( FIELDSYS_WORK* fsys, const u8 * p, u8 key )
{
	u16 work1,work2;
	u32 pos;

	pos = 0;

	while( 1 ){
		//�I���L�q�`�F�b�N(SP_EVENT_DATA_END)
		if( *p == SP_SCRID_NONE ){
			return 0xffff;
		}

		//�w��^�C�v�̓���X�N���v�g����
		if( (*p) == key ){
			p++;								//����X�N���v�gID������
			pos = ( *p + ( *(p+1)<<8 ) + ( *(p+2)<<16 ) + ( *(p+3)<<24 ) );
			p += 4;								//�A�h���X������
			break;
		}

		p += (1 + 4);							//����X�N���v�gID+�A�h���X������
	}

	//������Ȃ�������
	if( pos == 0 ){
		return 0xffff;
	}

	//����X�N���v�g�e�[�u�����Z�b�g
	p = (p + pos);

	while ( TRUE ) {
		//�I���L�q�`�F�b�N(SP_SCRIPT_END)
		if( *p == 0 ){
			return 0xffff;
		}

		//��r�����[�N�擾
		work1 = ( *p + ( *(p+1)<<8 ) );
		if( work1 == 0 ){
			return 0xffff;
		};
		p += 2;									//���[�N������
		//OS_Printf( "work1 = %d\n", work1 );

		//��r���l(���[�N��)�擾
		work2 = ( *p + ( *(p+1)<<8 ) );
		p += 2;									//��r����l������(���[�N��)
		//OS_Printf( "work2 = %d\n", work2 );

		//�����`�F�b�N
		if( GetEventWorkValue(fsys,work1) == GetEventWorkValue(fsys,work2) ){
			return ( *p + ( *(p+1)<<8 ) );
		}

		p += 2;									//�X�N���v�gID������
	}

	return 0xffff;								//����������Ȃ�����
}


//============================================================================================
//
//	���g�p
//
//============================================================================================
#if 0
static void FieldScriptLoad( u16 map, u16 id );
static void FieldScriptFileNameMake( char * path, u16 map, u16 id );

static VM_MACHINE field_script;			// ���z�}�V���p����\����
static u8 field_script_status;			// �X�N���v�g��ԕϐ�
//static u8 ForceEventFlag;				// �����C�x���g����t���O
static VM_CODE * pScript = NULL;		// �ʏ�X�N���v�g
//static u16 * ScriptWork = NULL;		// �X�N���v�g���[�N

//	�X�N���v�g��Ԓ�`
enum{
	SCRIPT_ON,
	SCRIPT_WAIT,
	SCRIPT_OFF,
};

static void FieldScriptFileNameMake( char * path, u16 map, u16 id )
{
	strcpy( path, "/data/script/script_map" );

	StrNumSet( &path[23], map, 3 );		// "/data/script/script_map"
	strcat( path, "_" );
	StrNumSet( &path[27], id, 2 );		// "/data/script/script_map000_"
	strcat( path, ".dat" );
}

static void FieldScriptLoad( u16 map, u16 id )
{
	char * path;

	path = (char *)sys_AllocMemory( APP_W_HEAP_AREA, 48 );
	FieldScriptFileNameMake( path, map, id );
	pScript = (VM_CODE *)sys_LoadFile( APP_W_HEAP_AREA, path );
	sys_FreeMemory( APP_W_HEAP_AREA, path );
}

//--------------------------------------------------------------------------------------------
/**
 * �X�N���v�g�N���`�F�b�N
 *
 * @param	none
 *
 * @retval	"TRUE = �N�����Ă���"
 * @retval	"FALSE = �N�����Ă��Ȃ�"
 */
//--------------------------------------------------------------------------------------------
u8 CheckScriptStatus(void)
{
	if( field_script_status == SCRIPT_ON ){
		return TRUE;
	}
	return FALSE;
}

#endif


//============================================================================================
//
//	VMMachine��TCB��ǉ�
//
//============================================================================================

#if 0
//--------------------------------------------------------------
/**
 * @brief	���z�}�V���ǉ�
 *
 * @param	fsys		FIELDSYS_WORK�^�̃|�C���^
 * @param	id			�X�N���v�gID
 * @param	start		���߃e�[�u���J�n�A�h���X
 * @param	end			���߃e�[�u���I���A�h���X
 *
 * @retval	none
 */
//--------------------------------------------------------------
void VMMachineAddTCB(FIELDSYS_WORK* fsys, u16 id, const VM_CMD* start, const VM_CMD* end)
{
	EV_SCRIPT_WORK * sc;
	VM_MACHINE* core = NULL;

	sc = FieldEvent_GetSpecialWork( fsys->event );

	//core = sys_AllocMemory( HEAPID_FIELD, sizeof(VM_MACHINE) );
	core = sys_AllocMemory( HEAPID_WORLD, sizeof(VM_MACHINE) );
	if( core == NULL ){
		GF_ASSERT( (0) && "�������m�ۂɎ��s���܂����I" );
	}

	//���z�}�V��������
	//VM_Init( core, &ScriptCmdTbl[0], &ScriptCmdTbl[EVCMD_MAX] );
	VM_Init( core, start, end );

	InitScript( fsys, core, id, 0 );							//���[�J���X�N���v�g������
	
	TCB_Add( VMMachineControlTCB, core, 0 );
	sc->vm_machine_count++;
	return;
}

//--------------------------------------------------------------
/**
 * @brief	TCB���C��
 *
 * @param	tcb		TCB_PTR
 * @param	wk		���[�N�̃A�h���X
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void VMMachineControlTCB( TCB_PTR tcb, void* wk )
{
	VM_MACHINE *core;
	FIELDSYS_WORK* fsys;
	EV_SCRIPT_WORK * sc;

	core = (VM_MACHINE *)wk;
	fsys = FieldEvent_GetFieldSysWork( core->event_work );
	sc = FieldEvent_GetSpecialWork( fsys->event );

	if( VM_Control( core ) == FALSE ){

		MSGMAN_Delete( core->msgman );

		sys_FreeMemoryEz( core->pScript );			//�X�N���v�g�f�[�^

		TCB_Delete( tcb );
		sys_FreeMemoryEz( core );

		if( sc->vm_machine_count == 0 ){
			GF_ASSERT( (0) && "���z�}�V���̐����s���ł��I" );
		}

		sc->vm_machine_count--;
	};

	return;
}
#endif

