/**
 *	@file	d_iwast.c
 *	@brief	�f�o�b�O�p���V�풓���\�[�X
 *	@author	Miyuki Iwasawa
 *	@date	06.06.01
 */

#ifdef PM_DEBUG

#include "common.h"
#include "fld_bmp.h"
#include "fntsys.h"
#include "talk_msg.h"
#include "system/bmp_list.h"
#include "system/bmp_menu.h"
#include "system/brightness.h"
#include "system/fontproc.h"
#include "system/wipe.h"
#include "gflib/strbuf.h"
#include "gflib/strbuf_family.h"
#include "field/fieldsys.h"
#include "field/field.h"
#include "field/ev_mapchange.h"
#include "field/fieldmap.h"
#include "field/zonedata.h"
#include "field/field_event.h"
#include "field/field_matrix.h"
#include "field/fld_mailbox.h"
#include "fielddata/maptable/zone_id.h"
#include "application/townmap.h"
#include "application/mailtool.h"
#include "application/poru_tool.h"
#include "application/nutmixer.h"
#include "field/fld_nmixer.h"
#include "script.h"
#include "fielddata/script/poruto_scr_def.h"
#include "fielddata/script/d31r0201_def.h"
#include "msgdata/msg.naix"
#include "msgdata/msg_debug_miyuki.h"

#include "field/d_iwa.h"

void DebugMiyukiFuncCall(TCB_PTR tcb,void* work)
{
	_DebugIwaWork	*wp = (_DebugIwaWork*)work;
	TOWNMAP_PARAM	*twork;

	switch(wp->seq){
	case DMSEQ_FADEOUT:
		wp->wipe_f = 0;
		WIPE_SYS_Start(WIPE_PATTERN_WMS,
				WIPE_TYPE_FADEOUT,
				WIPE_TYPE_FADEOUT,0x0000,COMM_BRIGHTNESS_SYNC,1,HEAPID_BASE_DEBUG
				);

		wp->seq = DMSEQ_FADEOUTWAIT;
		break;
	case DMSEQ_FADEOUTWAIT:
		if(!WIPE_SYS_EndCheck()){
			break;
		}
		DebugMiyukiViewEnd(wp);
		//�t�@���N�V�������s�A�v���Z�X�o�^
		{
			void (*dproc_call)(void*);
			dproc_call = wp->UserFunc;
			(*dproc_call)(wp);
			FieldSystemProc_SeqHoldEnd();
		}
		wp->seq = DMSEQ_FUNC;
		break;
	case DMSEQ_FUNC:
		//�v���Z�X�I���҂�
		if(FieldEvent_Cmd_WaitSubProcEnd(wp->fsys)){
			break;
		}
		//���������m�ۂ��Ă���Ή��
		if(wp->subWork != NULL){
			switch(wp->func_mode){
			case 1:
				twork = (TOWNMAP_PARAM*)wp->subWork;
				if(twork->retval){
					wp->ret_x = twork->ret_x;
					wp->ret_z = twork->ret_z;
					wp->ret_zone = twork->ret_zone;
					wp->ret_val = twork->retval;
					wp->seq = DMSEQ_JUMPIN;
				}else{
					wp->ret_x = 0;
					wp->ret_z = 0;
					wp->seq = DMSEQ_FADEIN;
				}
				sys_FreeMemoryEz(wp->subWork);
				break;
			case 2:
				wp->seq = DMSEQ_FADEIN;
				PorutoSys_ReleaseCallWork(wp->subWork);
				break;
			default:
				wp->seq = DMSEQ_FADEIN;
				sys_FreeMemoryEz(wp->subWork);
				break;
			}
			wp->subWork = NULL;
		}else{
			wp->seq = DMSEQ_FADEIN;
		}
		//�t�B�[���h�}�b�v�v���Z�X���A
		FieldEvent_Cmd_SetMapProc(wp->fsys);
		break;
	case DMSEQ_FADEIN:
		//�t�B�[���h�v���Z�X�J�n�I���҂�
		if(FieldEvent_Cmd_WaitMapProcStart(wp->fsys)){
			//�f�o�b�O���j���[���A
			DebugMiyukiViewInit(wp,wp->fsys,wp->List,wp->Cursor);
			//�u���b�N�C�����N�G�X�g
			wp->wipe_f = 0;
			WIPE_SYS_Start(WIPE_PATTERN_WMS,
				WIPE_TYPE_FADEIN,
				WIPE_TYPE_FADEIN,0x0000,COMM_BRIGHTNESS_SYNC,1,HEAPID_BASE_DEBUG
				);
			wp->seq = DMSEQ_FADEINWAIT;
			break;
		}
		break;
	case DMSEQ_FADEINWAIT:
		if(!WIPE_SYS_EndCheck()){
			break;
		}
		FieldSystemProc_SeqHold();
		TCB_ChangeFunc(tcb,DebugMiyukiMain);
		wp->seq = DMSEQ_FADEOUT;
		break;
	case DMSEQ_JUMPIN:
		//�t�B�[���h�v���Z�X�J�n�I���҂�
		if(FieldEvent_Cmd_WaitMapProcStart(wp->fsys)){
			wp->wipe_f = 0;
			WIPE_SYS_Start(WIPE_PATTERN_WMS,
				WIPE_TYPE_FADEIN,
				WIPE_TYPE_FADEIN,0x0000,COMM_BRIGHTNESS_SYNC,1,HEAPID_BASE_DEBUG
				);
			GF_BGL_ScrFill(wp->pBglIni,GF_BGL_FRAME3_M,0x0000,0,0,32,32,GF_BGL_SCRWRT_PALIN);
			GF_BGL_LoadScreenV_Req(wp->pBglIni,GF_BGL_FRAME3_M);
			wp->seq = DMSEQ_JUMPWAIT;
			break;
		}
		break;
	case DMSEQ_JUMPWAIT:
		if(!WIPE_SYS_EndCheck()){
			break;
		}
		EventSet_EasyMapChange(wp->fsys,
			wp->ret_zone,DOOR_ID_JUMP_CODE,
			wp->ret_x*32+16,wp->ret_z*32+16, DIR_DOWN);
		
		//�f�o�b�O���[�N�������J��
		sys_FreeMemoryEz(work);
		TCB_Delete(tcb);

		//OBJ���̓����~����
		FieldSystemProc_SeqHoldEnd();
		break;
	}
}

//�f�o�b�O���[���{�b�N�X�I���҂�
void DebugMiyukiSubMenuWait(TCB_PTR tcb,void* work)
{
	_DebugIwaWork	*wp = (_DebugIwaWork*)work;
	
	if(!wp->ret_val){
		return;
	}
	wp->ret_val = 0;
	//�f�o�b�O���j���[���A
	DebugMiyukiViewInit(wp,wp->fsys,wp->List,wp->Cursor);
	TCB_ChangeFunc(tcb,DebugMiyukiMain);
}


#endif	//ifdef PM_DEBUG

