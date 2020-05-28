//===========================================================================
/**
 * @file	safari_scope.c
 * @brief	�T�t�@���]����
 * @author	Nozomu Saito
 * @date	2006.04.24
 * 
 */
//===========================================================================
#include "common.h"
#include "fieldsys.h"
#include "field_event.h"
#include "ev_mapchange.h"
#include "system/wipe.h"
#include "system/snd_tool.h"
#include "map_jump.h"		//for wipe
#include "field/fld_flg_init.h"
#include "sysflag.h"

#include "fieldmap.h"		//for FieldFadeWipeSet

#include "map_attr.h"		//for attribute

#include "fieldmap_work.h"	//for hblamk wipe
#include "field_hblank.h"	//for hblank wipe

#include "safari_scope_common.h"
#include "safari_scope_obj.h"
#include "safari_scope_calc.h"
#include "safari_scope.h"

#define SCOPE_DISP_TIME	(60)

typedef struct SCOPE_EVENT_WORK_tag
{
	SSO_PTR SafScpObjPtr;
	SSC_SD_PTR ScpDatPtr;
	LOCATION_WORK *Next;
	u8 Seq;
	u8 Count;
	u8 Wait;
}SCOPE_EVENT_WORK;

enum {
	SS_START,	//����t�F�[�h�A�E�g�R�[��
	SS_F_PROC_END,	//�t�B�[���h�v���Z�X���I��
	SS_MAP_CHG,		//�}�b�v�`�F���W
	SS_F_PROC_START,//�t�B�[���h�v���Z�X�J�n
	SS_SCOPE_SET,	//�]�����Z�b�g�A�b�v
	SS_SCOPE_VIEW,		//�]�����̂����Ă�
	SS_SCOPE_RESET,	//���̖]�����̏���
	SS_TASK_WAIT,	//�Z���A�N�^�[�I���҂�
	SS_END,		//�]�����I��
};

static BOOL GMEVENT_SafariScopeStart(GMEVENT_CONTROL * event);

//--------------------------------------------------------------------------------------------
/**
 * �C�x���g�R�[��
 *
 * @param	fsys	�t�B�[���h�V�X�e���|�C���^
 * 
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void CallSafariScopeEvent(FIELDSYS_WORK * fsys)
{
	SCOPE_EVENT_WORK * sew = sys_AllocMemoryLo(HEAPID_WORLD, sizeof(SCOPE_EVENT_WORK));
	sew->SafScpObjPtr = SSO_AllocMemory(HEAPID_WORLD);
	sew->ScpDatPtr = SSC_CreateScopePointList(HEAPID_WORLD, fsys);

	sew->Seq = SS_START;
	sew->Count = 0;
	
	//�}�b�v�W�����v�C�x���g���쐬
	FieldEvent_Call(fsys->event, GMEVENT_SafariScopeStart, sew);
}

//--------------------------------------------------------------------------------------------
/**
 * �]�����C�x���g
 *
 * @param	event		�C�x���g�|�C���^
 *
 * @return	BOOL		TRUE:�I���@FALSE:�p��
 */
//--------------------------------------------------------------------------------------------
static BOOL GMEVENT_SafariScopeStart(GMEVENT_CONTROL * event)
{
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	SCOPE_EVENT_WORK * sew = FieldEvent_GetSpecialWork(event);

	switch (sew->Seq) {
	case SS_START:		//�]�����X�^�[�g
		//�]�������[�h�Z�b�g
		FldFlg_SetScopeMode(fsys, TRUE);
		//���P�[�V�����f�[�^�쐬
		SSC_SetNextLocation(sew->Count, sew->ScpDatPtr);
		sew->Next = SSC_GetNextLocaton(sew->ScpDatPtr);
		
		EventCmd_FieldFadeOut(event);			//�t�F�[�h�A�E�g
		sew->Seq = SS_F_PROC_END;
		break;
	case SS_F_PROC_END:	//�t�B�[���h�v���Z�X���I��
		EventCmd_FinishFieldMap(event);
		sew->Seq = SS_MAP_CHG;
		break;
	case SS_MAP_CHG:	//���ۂɃf�[�^��V�}�b�v�ɏ���������
		{
			EVENTWORK* ev = SaveData_GetEventWork( fsys->savedata );
			if (sew->Count == 0){					//�|�P�b�`���t�b�N
				SysFlag_PoketchHookSet(ev);
///				OS_Printf("�|�P�b�`���t�b�N\n");
			}else if(sew->Count == SCOPE_DISP_CNT){	//�|�P�b�`�̃t�b�N������
				SysFlag_PoketchHookReset(ev);
///				OS_Printf("�|�P�b�`�̃t�b�N������\n");
			}
		}
		//SSC_JumpMap(event, sew->ScpDatPtr);
		EventCmd_MapChangeByLocation(event, sew->Next);
		sew->Seq = SS_F_PROC_START;
		break;
	case SS_F_PROC_START:	//�t�B�[���h�v���Z�X�J�n
		EventCmd_StartFieldMap(event);
		sew->Seq = SS_SCOPE_SET;
		break;
	case SS_SCOPE_SET:
		{
			FIELD_OBJ_PTR player = Player_FieldOBJGet( fsys->player );
			sew->Count++;
			//5�񖢖��Ȃ玩�@��\��
			//�G���J�E���g����|�P�����\��
			//5�񏈗������玩�@�͕\���i�]�����̈ʒu�ɖ߂��Ă�j
			if (sew->Count<=SCOPE_DISP_CNT){
				int monsno;
				monsno = SSC_GetSafScpMons(fsys);
				//���@��\��
				FieldOBJ_StatusBitSet_Vanish( player, TRUE );
				
				SSO_SetupSafariScopeCLACT(sew->SafScpObjPtr,monsno);
				SSO_DrawStartCellAct(sew->SafScpObjPtr);
				sew->Wait = 0;
				Snd_SePlay( SEQ_SE_DP_KASYA );		//�`�����Ƃ��̉�
				MJUMP_RequestWipe( event,WIPE_PATTERN_M, WIPE_TYPE_HOLEIN,
							0xffff,0x0000,6,1,HEAPID_WORLD);
				
				sew->Seq = SS_SCOPE_VIEW;
			}else{
				//���@�\��
				FieldOBJ_StatusBitSet_Vanish( player, FALSE );
				EventCmd_FieldFadeIn(event);		//�t�F�[�h�C��
				sew->Seq = SS_END;
			}
		}
		break;
	case SS_SCOPE_VIEW:
		sew->Wait++;
		//�E�F�C�g���Ԍo�߂�����{�^�������Ŏ��̃V�[�P���X��
		if ((sew->Wait>=SCOPE_DISP_TIME)||(sys.trg & PAD_BUTTON_DECIDE)){
			//���P�[�V�����f�[�^�쐬
			SSC_SetNextLocation(sew->Count, sew->ScpDatPtr);
			sew->Next = SSC_GetNextLocaton(sew->ScpDatPtr);
			Snd_SePlay( SEQ_SE_DP_KASYA );		//�����Ƃ��̉�
			MJUMP_RequestWipe( event,WIPE_PATTERN_M, WIPE_TYPE_HOLEOUT,
								0xffff,0x0000,6,1,HEAPID_WORLD);
	
			sew->Seq = SS_SCOPE_RESET;
		}
		break;
	case SS_SCOPE_RESET:
		SSO_DrawEndCellAct(sew->SafScpObjPtr);
		sew->Seq = SS_TASK_WAIT;
		break;
	case SS_TASK_WAIT:
		if (SSO_WaitDrawCellTask(sew->SafScpObjPtr)){
			//�Z���A�N�^�[���
			SSO_RereaseSSCellObject(sew->SafScpObjPtr);
			sew->Seq = SS_F_PROC_END;
		}
		break;
	case SS_END:		//�I������
		////�]�������[�h���Z�b�g
		FldFlg_SetScopeMode(fsys, FALSE);
		
		SSC_RereaseScopePointList(sew->ScpDatPtr);
		SSO_FreeMemory(sew->SafScpObjPtr);
		sys_FreeMemoryEz(sew);
		return TRUE;
	}
	return FALSE;
}
