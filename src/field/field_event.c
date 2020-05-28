//=============================================================================
/**
 * @file	field_event.c
 * @brief	�t�B�[���h�C�x���g����
 * @author	tamada
 * @date	2005.07.22
 */
//=============================================================================

#include "common.h"
#include "fieldsys.h"

#include "field_event.h"

//=============================================================================
//=============================================================================
enum {
	HEAPID_LOCAL = HEAPID_EVENT,
};
//-----------------------------------------------------------------------------
/**
 * �Q�[�����C�x���g�R���g���[���p���[�N��`
 */
//-----------------------------------------------------------------------------
typedef struct _GMEVENT_CONTROL{
	GMEVENT_CONTROL * parent;
	GMEVENT_FUNC	func;	///<����֐��ւ̃|�C���^
	int seq;				///<�V�[�P���X���[�N
	void * work;			///<����֐����ɌŗL���[�N�ւ̃|�C���^
	int lwk_size;
	void * lwk;
	FIELDSYS_WORK * repw;	///<�t�B�[���h�S�̐��䃏�[�N�ւ̃|�C���^�i�Ȃ�ׂ��Q�Ƃ������Ȃ��j
	EVENT_WORK * event_work;	///<�C�x���g�Ŏg�p���郏�[�N
};

//=============================================================================
//=============================================================================
//------------------------------------------------------------------
/**
 * @brief	�C�x���g����
 * @param	repw
 * @param	event_func	�C�x���g����֐��ւ̃|�C���^
 * @param	work		�C�x���g����֐��̎g�p���郏�[�N�ւ̃|�C���^
 * @return	GMEVENT_CONTROL	���������C�x���g�ւ̃|�C���^
 *
 */
//------------------------------------------------------------------
static GMEVENT_CONTROL * Event_Create(FIELDSYS_WORK * repw, GMEVENT_FUNC event_func, void * work)
{
	GMEVENT_CONTROL * event;
	event = sys_AllocMemoryLo(HEAPID_LOCAL, sizeof(GMEVENT_CONTROL));
	event->parent = NULL;
	event->func = event_func;
	event->seq = 0;
	event->work = work;
	event->lwk_size = 0;
	event->lwk = NULL;
	event->repw = repw;
	event->event_work = sys_AllocMemoryLo(HEAPID_LOCAL, sizeof(EVENT_WORK));
	return event;
}

//------------------------------------------------------------------
/**
 * @brief	�C�x���g�ݒ�
 * @param	repw
 * @param	event_func	�C�x���g����֐��ւ̃|�C���^
 * @param	work		�C�x���g����֐��̎g�p���郏�[�N�ւ̃|�C���^
 * @return	GMEVENT_CONTROL	���������C�x���g
 */
//------------------------------------------------------------------
GMEVENT_CONTROL * FieldEvent_Set(FIELDSYS_WORK * repw, GMEVENT_FUNC event_func, void * work)
{
	GMEVENT_CONTROL * event;
	GF_ASSERT(repw->event == NULL);
//	GF_ASSERT((sys_GetHeapState(HEAPID_LOCAL) >> 32) == 0);
	event = Event_Create(repw, event_func, work);
	repw->event = event;
	return event;
}
//------------------------------------------------------------------
/**
 * @brief	�C�x���g�ؑ�
 * @param	event		�C�x���g���䃏�[�N�ւ̃|�C���^
 * @param	next_func	���̃C�x���g����֐��ւ̃|�C���^
 * @param	work		���̃C�x���g����֐��̎g�p���郏�[�N�ւ̃|�C���^
 */
//------------------------------------------------------------------
void FieldEvent_Change(GMEVENT_CONTROL * event, GMEVENT_FUNC next_func, void * work)
{
	event->func = next_func;
	event->seq = 0;
	event->work = work;
	if (event->lwk != 0 || event->lwk != NULL) {
		sys_FreeMemoryEz(event->lwk);
		event->lwk_size = 0;
		event->lwk = NULL;
	}
}
//------------------------------------------------------------------
/**
 * @brief	�T�u�C�x���g�Ăяo��
 * @param	parent		�e�C�x���g�ւ̃|�C���^
 * @param	event_func	�C�x���g����֐��ւ̃|�C���^
 * @param	work		�C�x���g����֐��̎g�p���郏�[�N�ւ̃|�C���^
 * @return	GMEVENT_CONTROL	���������C�x���g
 *
 * �C�x���g����T�u�C�x���g�̃R�[�����Ăяo��
 */
//------------------------------------------------------------------
GMEVENT_CONTROL * FieldEvent_Call(GMEVENT_CONTROL * parent, GMEVENT_FUNC sub_func, void * work)
{
	GMEVENT_CONTROL * event;
	event = Event_Create(parent->repw, sub_func, work);
	event->parent = parent;
	parent->repw->event = event;
	return event;
}

//=============================================================================
//=============================================================================
//------------------------------------------------------------------
/**
 * @brief	�C�x���g����
 * @param	repw
 * @retval	TRUE	�C�x���g�I��
 * @retval	FALSE	�C�x���g�p����
 */
//------------------------------------------------------------------
BOOL FieldEvent_Control(FIELDSYS_WORK * fsys)
{
	if (fsys->event == NULL) {
		return FALSE;
	}
	while (fsys->event->func(fsys->event) == TRUE) {
		GMEVENT_CONTROL * parent;
		parent = fsys->event->parent;
		if (fsys->event->lwk) {
			sys_FreeMemoryEz(fsys->event->lwk);
		}
		sys_FreeMemoryEz(fsys->event->event_work);
		sys_FreeMemoryEz(fsys->event);
		fsys->event = parent;
		if (parent == NULL) {
//			GF_ASSERT((sys_GetHeapState(HEAPID_LOCAL) >> 32) == 0);
			return TRUE;
		}
	}
	return FALSE;
}

//------------------------------------------------------------------
/**
 * @brief	�C�x���g�N�����`�F�b�N
 * @param	fsys	�t�B�[���h���䃏�[�N�ւ̃|�C���^
 * @retval	TRUE	�C�x���g�N����
 * @retval	FALSE	�C�x���g�Ȃ�
 */
//------------------------------------------------------------------
BOOL FieldEvent_Check(FIELDSYS_WORK * fsys)
{
	return (fsys->event != NULL);
}

//=============================================================================
//
//	�C�x���g�R�}���h
//
//=============================================================================
//------------------------------------------------------------------
//------------------------------------------------------------------

//------------------------------------------------------------------
/**
 * @brief	�T�u�v���Z�X����I���҂�
 * @param	fsys	�t�B�[���h���䃏�[�N�ւ̃|�C���^
 * @retval	TRUE	�T�u�v���Z�X���쒆
 * @retval	FALSE	�T�u�v���Z�X�I��
 */
//------------------------------------------------------------------
BOOL FieldEvent_Cmd_WaitSubProcEnd(FIELDSYS_WORK * fsys)
{
	if (GameSystem_CheckFieldProcExists(fsys) || GameSystem_CheckSubProcExists(fsys)) {
		return TRUE;
	} else {
		return FALSE;
	}
}

//------------------------------------------------------------------
//------------------------------------------------------------------
void FieldEvent_Cmd_SetMapProc(FIELDSYS_WORK * fsys)
{
	GameSystem_CreateFieldProc(fsys);
}

//------------------------------------------------------------------
//------------------------------------------------------------------
BOOL FieldEvent_Cmd_WaitMapProcStart(FIELDSYS_WORK * fsys)
{
	if (GameSystem_CheckFieldMain(fsys)) {
		return TRUE;
	} else {
		return FALSE;
	}
}

//=============================================================================
//
//=============================================================================
//------------------------------------------------------------------
//------------------------------------------------------------------
typedef struct {
	int seq;
	const PROC_DATA * proc_data;
	void * param;
}EV_SUBPROC_WORK;
//------------------------------------------------------------------
/**
 * @brief	�T�u�C�x���g�F�T�u�v���Z�X�Ăяo��
 * @param	event		�C�x���g���䃏�[�N�ւ̃|�C���^
 * @retval	TRUE		�T�u�C�x���g�I��
 * @retval	FALSE		�T�u�C�x���g�p����
 */
//------------------------------------------------------------------
static BOOL GMEVENT_Sub_CallSubProc(GMEVENT_CONTROL * event)
{
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	EV_SUBPROC_WORK * esw = FieldEvent_GetSpecialWork(event);
	switch (esw->seq) {
	case 0:
		GameSystem_StartSubProc(fsys, esw->proc_data, esw->param);
		esw->seq ++;
		break;
	case 1:
		if (FieldEvent_Cmd_WaitSubProcEnd(fsys)) {
			break;
		}
		sys_FreeMemoryEz(esw);
		return TRUE;
	}
	return FALSE;
}
//------------------------------------------------------------------
/**
 * @brief	�C�x���g�[���R�}���h�F�T�u�v���Z�X�Ăяo��
 * @param	event		�C�x���g���䃏�[�N�ւ̃|�C���^
 * @param	proc_data	�v���Z�X��`�f�[�^�ւ̃|�C���^
 * @param	param		�p�����[�^�ւ̃|�C���^
 *
 * �T�u�v���Z�X���Ăяo���ďI����҂�
 */
//------------------------------------------------------------------
void EventCmd_CallSubProc(GMEVENT_CONTROL * event, const PROC_DATA * proc_data, void * param)
{
	EV_SUBPROC_WORK * esw = sys_AllocMemoryLo(HEAPID_LOCAL, sizeof(EV_SUBPROC_WORK));
	esw->seq = 0;
	esw->proc_data = proc_data;
	esw->param = param;
	FieldEvent_Call(event, GMEVENT_Sub_CallSubProc, esw);
}

//=============================================================================
//
//
//
//=============================================================================
//------------------------------------------------------------------
/**
 * @brief	�t�B�[���h���䃏�[�N�ւ̃|�C���^�擾
 * @param	event		�C�x���g���䃏�[�N�ւ̃|�C���^
 * @return	FIELDSYS_WORK	�t�B�[���h���䃏�[�N�ւ̃|�C���^
 *
 * �t�B�[���h���䃏�[�N�̓t�B�[���h�ł͍ŏ�ʂ̃��[�N�G���A�ƂȂ�B
 * ���̗̈�ɒ��ڎQ�Ƃ��邱�Ƃ́u�t�B�[���h���ł̃O���[�o���ϐ��ւ̃A�N�Z�X�v��
 * �������B�O���[�o���ϐ��ւ̃A�N�Z�X�͂Ȃ�ׂ�������ׂ��Ȃ̂ŁA���̊֐���
 * �Ȃ�ׂ��g�p���Ȃ��悤�ɂ������B
 *
 * �܂��̓v���O�����\�����T�O�I�ɐ؂蕪���邱�Ƃ�D�悷�邽�߁A
 * ��{�I�ɕK�v�ȕϐ��Ȃǂւ̃A�N�Z�X�͊֐��o�R�ɂ���B
 * ���̏�ŕs�v�Ȃ��͍̂폜���Ă����A���x�I�Ȗ�肪����ꍇ�̓|�C���^���ڎQ�Ƃ�
 * �l����B
 *
 */
//------------------------------------------------------------------
FIELDSYS_WORK * FieldEvent_GetFieldSysWork(GMEVENT_CONTROL * event)
{
	return event->repw;
}

//------------------------------------------------------------------
/**
 * @brief	�t�B�[���h�C�x���g�ʂ̃��[�N�ւ̃|�C���^
 * @param	event		�C�x���g���䃏�[�N�ւ̃|�C���^
 * @return	�e�C�x���g�p���[�N
 */
//------------------------------------------------------------------
void * FieldEvent_GetSpecialWork(GMEVENT_CONTROL * event)
{
	return event->work;
}

//------------------------------------------------------------------
/**
 * @brief	�V�[�P���X���[�N�̎擾
 * @param	event		�C�x���g���䃏�[�N�ւ̃|�C���^
 * @return	�V�[�P���X���[�N�ւ̃|�C���^
 */
//------------------------------------------------------------------
int * FieldEvent_GetSeqWork(GMEVENT_CONTROL * event)
{
	return &event->seq;
}
//------------------------------------------------------------------
/**
 * @brief	���[�J�����[�N�̎擾
 * @param	event		�C�x���g���䃏�[�N�ւ̃|�C���^
 * @param	size		���[�J�����[�N�̃T�C�Y�w��	
 * @return	void*		���[�J�����[�N�ւ̃|�C���^
 *
 * ���̃C�x���g���甲�����Ƃ��Ɏ����������郏�[�N���擾�ł���B
 * �C�x���g�I�����A����уC�x���g�ؑցiFieldEvent_Change�j�̃^�C�~���O��
 * ��������B
 */
//------------------------------------------------------------------
void * FieldEvent_GetLocalWork(GMEVENT_CONTROL * event, int size)
{
	if (event->lwk == NULL && event->lwk_size == 0) {
		event->lwk_size = size;
		event->lwk = sys_AllocMemoryLo(HEAPID_LOCAL, size);
		MI_CpuClear8(event->lwk, size);
	} else {
		GF_ASSERT(event->lwk_size == size);
	}
	return event->lwk;
}

//------------------------------------------------------------------
/**
 * @brief	�C�x���g�Ŏg�p���郏�[�N���擾
 * @param	fsys	�t�B�[���V�X�e��
 * @return	�C�x���g�p���[�N
 */
//------------------------------------------------------------------
EVENT_WORK * Event_GetEventWork(FIELDSYS_WORK * fsys)
{
	return fsys->event->event_work;
}


//------------------------------------------------------------------
/**
 * @brief	�b����OBJ���擾
 * @param	event		�C�x���g���䃏�[�N�ւ̃|�C���^
 * @return	�b����OBJ
 */
//------------------------------------------------------------------
#if 0
FIELD_OBJ_PTR Event_GetTargetObj( GMEVENT_CONTROL * event )
{
	return event->event_work->targetobj;
}
#endif

//------------------------------------------------------------------
/**
 * @brief	�b����BG���擾
 * @param	event		�C�x���g���䃏�[�N�ւ̃|�C���^
 * @return	�b����BG
 */
//------------------------------------------------------------------
u32 Event_GetTargetBg( GMEVENT_CONTROL * event )
{
	return event->event_work->targetbg;
}

