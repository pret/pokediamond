//==============================================================================
/**
 * @file	actin_order.c
 * @brief	���Z�͕���F���߂��e�X�^�b�t�ɑ��M
 * @author	matsuda
 * @date	2005.11.25(��)
 */
//==============================================================================
#include "common.h"
#include "contest/contest.h"
#include "actin.h"
#include "actin_tcb_pri.h"
#include "battle/battle_common.h"
#include "system/clact_tool.h"
#include "system/palanm.h"

#include "system/arc_tool.h"
#include "system/arc_util.h"

#include "system/softsprite.h"

#include "system/fontproc.h"
#include "system/msgdata.h"

#include "wazaeffect/battle_particle.h"
#include "system/particle.h"
#include "wazaeffect/we_mana.h"
#include "wazaeffect/we_sys.h"

#include "system/brightness.h"

#include "graphic/contest_bg_def.h"
#include "graphic/contest_obj_def.h"

#include "actin_tool.h"
#include "actin_order.h"
#include "actin_input.h"
#include "poketool/poke_tool.h"
#include "gflib/touchpanel.h"
#include "system/snd_tool.h"
#include "contest_order.h"
#include "battle/wazano_def.h"
#include "battle/attr_def.h"
#include "battle/battle_server.h"


//==============================================================================
//	�萔��`
//==============================================================================
///�A�s�[���A�C�R����1�_�����閈�ɑ҂E�F�C�g
#define APPEAL_ICON_LIGHT_WAIT		(2)
///�{���e�[�W�A�C�R����1�_�����閈�ɑ҂E�F�C�g
#define VOLTAGE_ICON_LIGHT_WAIT		(APPEAL_ICON_LIGHT_WAIT)
///�ϋq�A�j���J�n�܂ł̃E�F�C�g
#define AUDIENCE_ANM_START_WAIT		(0)
///�ϋq�A�j�����Z�b�g���Ă��玟�̃V�[�P���X�֐i�߂�܂ł̃E�F�C�g
#define AUDIENCE_ANM_NEXT_WAIT		(8)

///�Z�G�t�F�N�g���o���O�̐R�����A�N�V�����ŁA�G�t�F�N�g�I����̑҂�����
#define WAZABEFORE_JUDGE_REACTION_END_WAIT		(5)

///�^�[���I����̃G�t�F�N�g�FAP�n�[�g��]�G�t�F�N�g���s��A
///���̃u���[�_�[�̃G�t�F�N�g���s�܂ł̃E�F�C�g
#define TEE_APHEART_NEXT_BREEDER_WAIT		0	//(30)

///�I�[�v�j���O��̑҂�����
#define OPENING_START_WAIT		(30)	//(60)

///�G���f�B���O�̑҂�����
#define ENDING_WAIT				(30)


//==============================================================================
//	�v���g�^�C�v�錾
//==============================================================================
static int Request_Sample(CONTEST_ORDER_WORK *cow, void *syswork, int order_no, void *work);
static void Recieve_Sample(CONTEST_ORDER_WORK *cow, void *syswork, const CORDER_HEAD *req_head, void *data);
static void Answer_Sample(CONTEST_ORDER_WORK *cow, void *syswork, const CORDER_HEAD *answer_head, CO_ANSDAT *data, int net_id);
static int Request_OpeningEffect(CONTEST_ORDER_WORK *cow, void *syswork, int order_no, void *work);
static void Recieve_OpeningEffect(CONTEST_ORDER_WORK *cow, void *syswork, const CORDER_HEAD *req_head, void *data);
static void AOTCB_OpeningEffect(TCB_PTR tcb, void *work);
static int Request_PokemonIn(CONTEST_ORDER_WORK *cow, void *syswork, int order_no, void *work);
static void Recieve_PokemonIn(CONTEST_ORDER_WORK *cow, void *syswork, const CORDER_HEAD *req_head, void *data);
static void AOTCB_PokemonIn(TCB_PTR tcb, void *work);
static int Request_PokemonOut(CONTEST_ORDER_WORK *cow, void *syswork, int order_no, void *work);
static void Recieve_PokemonOut(CONTEST_ORDER_WORK *cow, void *syswork, const CORDER_HEAD *req_head, void *data);
static void AOTCB_PokemonOut(TCB_PTR tcb, void *work);
static int Request_WazaEffectBefore(CONTEST_ORDER_WORK *cow, void *syswork, int order_no, void *work);
static void Recieve_WazaEffectBefore(CONTEST_ORDER_WORK *cow, void *syswork, const CORDER_HEAD *req_head, void *data);
static void AOTCB_WazaEffectBefore(TCB_PTR tcb, void *work);
static int Request_WazaEffect(CONTEST_ORDER_WORK *cow, void *syswork, int order_no, void *work);
static void Recieve_WazaEffect(CONTEST_ORDER_WORK *cow, void *syswork, const CORDER_HEAD *req_head, void *data);
static void AOTCB_WazaEffect(TCB_PTR tcb, void *work);
static int Request_UserSelect(CONTEST_ORDER_WORK *cow, void *syswork, int order_no, void *work);
static void Recieve_UserSelect(CONTEST_ORDER_WORK *cow, void *syswork, const CORDER_HEAD *req_head, void *data);
static void Answer_UserSelect(CONTEST_ORDER_WORK *cow, void *syswork, const CORDER_HEAD *answer_head, CO_ANSDAT *ansdat, int net_id);
static void AOTCB_UserSelect(TCB_PTR tcb, void *work);
static int Request_AppealReview(CONTEST_ORDER_WORK *cow, void *syswork, int order_no, void *work);
static void Recieve_AppealReview(CONTEST_ORDER_WORK *cow, void *syswork, const CORDER_HEAD *req_head, void *data);
static void AOTCB_AppealReview(TCB_PTR tcb, void *work);
static int Request_AppealFirst(CONTEST_ORDER_WORK *cow, void *syswork, int order_no, void *work);
static void Recieve_AppealFirst(CONTEST_ORDER_WORK *cow, void *syswork, const CORDER_HEAD *req_head, void *data);
static void AOTCB_AppealFirst(TCB_PTR tcb, void *work);
static int Request_ActinExit(CONTEST_ORDER_WORK *cow, void *syswork, int order_no, void *work);
static void Recieve_ActinExit(CONTEST_ORDER_WORK *cow, void *syswork, const CORDER_HEAD *req_head, void *data);
static int Request_TurnParamUpdate(CONTEST_ORDER_WORK *cow, void *syswork, int order_no, void *work);
static void Recieve_TurnParamUpdate(CONTEST_ORDER_WORK *cow, void *syswork, const CORDER_HEAD *req_head, void *data);
static int Request_AppealKouka(CONTEST_ORDER_WORK *cow, void *syswork, int order_no, void *work);
static void Recieve_AppealKouka(CONTEST_ORDER_WORK *cow, void *syswork, const CORDER_HEAD *req_head, void *data);
static void AOTCB_AppealKouka(TCB_PTR tcb, void *work);
static int Request_AppealSpecialKouka(CONTEST_ORDER_WORK *cow, void *syswork, int order_no, void *work);
static void Recieve_AppealSpecialKouka(CONTEST_ORDER_WORK *cow, void *syswork, const CORDER_HEAD *req_head, void *data);
static void AOTCB_AppealSpecialKouka(TCB_PTR tcb, void *work);
static int Request_AppealVoltage(CONTEST_ORDER_WORK *cow, void *syswork, int order_no, 
	void *work);
static void Recieve_AppealVoltage(CONTEST_ORDER_WORK *cow, void *syswork, 
	const CORDER_HEAD *req_head, void *data);
static void AOTCB_AppealVoltage(TCB_PTR tcb, void *work);
static int Request_ReviewAfterKouka(CONTEST_ORDER_WORK *cow, void *syswork, int order_no, 
	void *work);
static void Recieve_ReviewAfterKouka(CONTEST_ORDER_WORK *cow, void *syswork, 
	const CORDER_HEAD *req_head, void *data);
static void AOTCB_ReviewAfterKouka(TCB_PTR tcb, void *work);
static int Request_JudgeSuffer(CONTEST_ORDER_WORK *cow, void *syswork, int order_no, 
	void *work);
static void Recieve_JudgeSuffer(CONTEST_ORDER_WORK *cow, void *syswork, 
	const CORDER_HEAD *req_head, void *data);
static void AOTCB_JudgeSuffer(TCB_PTR tcb, void *work);
static int Request_JudgeComment(CONTEST_ORDER_WORK *cow, void *syswork, int order_no, void *work);
static void Recieve_JudgeComment(CONTEST_ORDER_WORK *cow, void *syswork, 
	const CORDER_HEAD *req_head, void *data);
static void AOTCB_JudgeComment(TCB_PTR tcb, void *work);
static int Request_Talk(CONTEST_ORDER_WORK *cow, void *syswork, int order_no, void *work);
static void Recieve_Talk(CONTEST_ORDER_WORK *cow, void *syswork, const CORDER_HEAD *req_head, void *data);
static void AOTCB_TalkPut(TCB_PTR tcb, void *work);
static int Request_TurnEndEffect(CONTEST_ORDER_WORK *cow, void *syswork, int order_no, void *work);
static void Recieve_TurnEndEffect(CONTEST_ORDER_WORK *cow, void *syswork, const CORDER_HEAD *req_head, void *data);
static void AOTCB_TurnEndEffect(TCB_PTR tcb, void *work);
static int Request_JudgeWaza(CONTEST_ORDER_WORK *cow, void *syswork, int order_no, void *work);
static void Recieve_JudgeWaza(CONTEST_ORDER_WORK *cow, void *syswork, const CORDER_HEAD *req_head, void *data);
static void AOTCB_JudgeWaza(TCB_PTR tcb, void *work);
static int Request_EndingEffect(CONTEST_ORDER_WORK *cow, void *syswork, int order_no, void *work);
static void Recieve_EndingEffect(CONTEST_ORDER_WORK *cow, void *syswork, const CORDER_HEAD *req_head, void *data);
static void AOTCB_EndingEffect(TCB_PTR tcb, void *work);



//==============================================================================
//	�f�[�^
//==============================================================================
///���ߑ���M�p�֐��|�C���^�\���̃e�[�u��	�������ɒǉ�������K��.h��enum�ɂ��ǉ����鎖!!
static const CON_ORDER_FUNC OrderFuncTbl[] = {
	{//AORDER_NO_SAMPLE		�T���v��
		Request_Sample, 
		Recieve_Sample, 
		Answer_Sample, 
	},
	{//AORDER_NO_ACTIN_EXIT
		Request_ActinExit,
		Recieve_ActinExit,
		NULL,
	},
	{//AORDER_NO_OPENING_EFFECT
		Request_OpeningEffect, 
		Recieve_OpeningEffect, 
		NULL,
	},
	{//AORDER_NO_ENDING_EFFECT
		Request_EndingEffect, 
		Recieve_EndingEffect, 
		NULL,
	},
	{//AORDER_NO_POKEMON_IN
		Request_PokemonIn,
		Recieve_PokemonIn,
		NULL,
	},
	{//AORDER_NO_POKEMON_OUT
		Request_PokemonOut,
		Recieve_PokemonOut,
		NULL,
	},
	{//AORDER_NO_WAZAEFFECT_BEFORE
		Request_WazaEffectBefore,
		Recieve_WazaEffectBefore,
		NULL,
	},
	{//AORDER_NO_WAZAEFFECT
		Request_WazaEffect,
		Recieve_WazaEffect,
		NULL,
	},
	{//AORDER_NO_USER_SELECT
		Request_UserSelect,
		Recieve_UserSelect,
		Answer_UserSelect,
	},
	{//AORDER_NO_APPEAL_REVIEW
		Request_AppealReview,
		Recieve_AppealReview,
		NULL,
	},
	{//AORDER_NO_APPEAL_FIRST
		Request_AppealFirst,
		Recieve_AppealFirst,
		NULL,
	},
	{//AORDER_NO_APPEAL_KOUKA
		Request_AppealKouka,
		Recieve_AppealKouka,
		NULL,
	},
	{//AORDER_NO_APPEAL_SPECIAL_KOUKA
		Request_AppealSpecialKouka,
		Recieve_AppealSpecialKouka,
		NULL,
	},
	{//AORDER_NO_APPEAL_VOLTAGE
		Request_AppealVoltage,
		Recieve_AppealVoltage,
		NULL,
	},
	{//AORDER_NO_REVIEW_AFTER
		Request_ReviewAfterKouka,
		Recieve_ReviewAfterKouka,
		NULL,
	},
	{//AORDER_NO_REVIEW_END
		Request_ReviewAfterKouka,
		Recieve_ReviewAfterKouka,
		NULL,
	},
	{//AORDER_NO_JUDGE_SUFFER
		Request_JudgeSuffer,
		Recieve_JudgeSuffer,
		NULL,
	},
	{//AORDER_NO_JUDGE_WAZA
		Request_JudgeWaza,
		Recieve_JudgeWaza,
		NULL,
	},
	{//AORDER_NO_JUDGE_COMMENT
		Request_JudgeComment,
		Recieve_JudgeComment,
		NULL,
	},
	{//AORDER_NO_TURN_PARAM_UPDATE
		Request_TurnParamUpdate,
		Recieve_TurnParamUpdate,
		NULL,
	},
	{//AORDER_NO_TALK
		Request_Talk,
		Recieve_Talk,
		NULL,
	},
	{//AORDER_NO_TURNEND_EFF
		Request_TurnEndEffect,
		Recieve_TurnEndEffect,
		NULL,
	},
};



//--------------------------------------------------------------
/**
 * @brief   �_���X����F�R���e�X�g����M���[�N������
 * @param   dpw		�_���X����Ǘ����[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
void ActinOrder_WorkInit(ACTIN_PROC_WORK *apw)
{
	CO_INIT_DATA initdata;
	
	initdata.func_tbl = OrderFuncTbl;
	initdata.func_tbl_max = NELEMS(OrderFuncTbl);
	initdata.my_breeder_no = apw->consys->c_game.my_breeder_no;
	initdata.server_no = apw->consys->c_game.server_no;
	initdata.sio_flag = apw->consys->sio_flag;
	
	CO_WorkInit(&apw->cow, &initdata);
}


//==============================================================================
//
//	
//
//==============================================================================

//==============================================================================
//	
//==============================================================================
//--------------------------------------------------------------
/**
 * @brief   ���ߑ��M(���M��)�F�T���v��
 *
 * @param   apw			���Z�͕���Ǘ����[�N�ւ̃|�C���^
 * @param   work		�C�ӂ̃|�C���^
 *
 * @retval  �o�^���ꂽ���N�G�X�g�r�b�g�ԍ�
 */
//--------------------------------------------------------------
static int Request_Sample(CONTEST_ORDER_WORK *cow, void *syswork, int order_no, void *work)
{
	ACTIN_PROC_WORK *apw = syswork;
	int bit_no;
	
	bit_no = CO_REQUEST_TransmitBufferSet(&apw->cow, CSELECT_ALL, order_no, NULL, 0);
	return bit_no;
}

//--------------------------------------------------------------
/**
 * @brief   ���ߎ�M(���M��)�F�T���v��
 *
 * @param   apw			���Z�͕���Ǘ����[�N�ւ̃|�C���^
 * @param   req_head	���N�G�X�g�w�b�_�̃|�C���^
 * @param   data		��M�f�[�^�ւ̃|�C���^
 */
//--------------------------------------------------------------
static void Recieve_Sample(CONTEST_ORDER_WORK *cow, void *syswork, const CORDER_HEAD *req_head, void *data)
{
	ACTIN_PROC_WORK *apw = syswork;
	//�Ԏ���Ԃ�	�o�b�t�@�͓��ɓn�����̂��Ȃ��̂�NULL�w��
	CO_ANSWER_TransmitBufferSet(&apw->cow, req_head, NULL, 0);
}

//--------------------------------------------------------------
/**
 * @brief   �Ԏ���M(���M��)�F�T���v��
 *
 * @param   apw				���Z�͕���Ǘ����[�N�ւ̃|�C���^
 * @param   answer_head		�Ԏ��w�b�_�̃|�C���^
 * @param   ansdat			��M�f�[�^�ւ̃|�C���^
 * @param   net_id			�Ԏ����M�҂̃l�b�gID
 */
//--------------------------------------------------------------
static void Answer_Sample(CONTEST_ORDER_WORK *cow, void *syswork, const CORDER_HEAD *answer_head, CO_ANSDAT *ansdat, int net_id)
{
	ACTIN_PROC_WORK *apw = syswork;
	//�Ԏ����󂯎�邾���Ȃ̂œ��ɂ��鎖���Ȃ�
	return;
}

//==============================================================================
//	
//==============================================================================
//--------------------------------------------------------------
/**
 * @brief   ���ߑ��M(���M��)�F���Z�͕���I��
 *
 * @param   apw			���Z�͕���Ǘ����[�N�ւ̃|�C���^
 * @param   work		�C�ӂ̃|�C���^
 *
 * @retval  �o�^���ꂽ���N�G�X�g�r�b�g�ԍ�
 */
//--------------------------------------------------------------
static int Request_ActinExit(CONTEST_ORDER_WORK *cow, void *syswork, int order_no, void *work)
{
	ACTIN_PROC_WORK *apw = syswork;
	int bit_no;
	
	bit_no = CO_REQUEST_TransmitBufferSet(&apw->cow, CSELECT_ALL, order_no, NULL, 0);
	return bit_no;
}

//--------------------------------------------------------------
/**
 * @brief   ���ߎ�M(���M��)�F���Z�͕���I��
 *
 * @param   apw			���Z�͕���Ǘ����[�N�ւ̃|�C���^
 * @param   req_head	���N�G�X�g�w�b�_�̃|�C���^
 * @param   data		��M�f�[�^�ւ̃|�C���^
 */
//--------------------------------------------------------------
static void Recieve_ActinExit(CONTEST_ORDER_WORK *cow, void *syswork, const CORDER_HEAD *req_head, void *data)
{
	ACTIN_PROC_WORK *apw = syswork;
	
	apw->main_end = TRUE;
	
	//�Ԏ���Ԃ�	�o�b�t�@�͓��ɓn�����̂��Ȃ��̂�NULL�w��
	CO_ANSWER_TransmitBufferSet(&apw->cow, req_head, NULL, 0);
}


//==============================================================================
//	
//==============================================================================
//--------------------------------------------------------------
/**
 * @brief   ���ߑ��M(���M��)�F�I�[�v�j���O�G�t�F�N�g
 *
 * @param   apw			���Z�͕���Ǘ����[�N�ւ̃|�C���^
 * @param   work		�C�ӂ̃|�C���^
 *
 * @retval  �o�^���ꂽ���N�G�X�g�r�b�g�ԍ�
 */
//--------------------------------------------------------------
static int Request_OpeningEffect(CONTEST_ORDER_WORK *cow, void *syswork, int order_no, void *work)
{
	ACTIN_PROC_WORK *apw = syswork;
	int bit_no;
	
	bit_no = CO_REQUEST_TransmitBufferSet(&apw->cow, CSELECT_ALL, order_no, NULL, 0);
	return bit_no;
}

//--------------------------------------------------------------
/**
 * @brief   ���ߎ�M(���M��)�F�I�[�v�j���O�G�t�F�N�g
 *
 * @param   apw			���Z�͕���Ǘ����[�N�ւ̃|�C���^
 * @param   req_head	���N�G�X�g�w�b�_�̃|�C���^
 * @param   data		��M�f�[�^�ւ̃|�C���^
 */
//--------------------------------------------------------------
static void Recieve_OpeningEffect(CONTEST_ORDER_WORK *cow, void *syswork, const CORDER_HEAD *req_head, void *data)
{
	ACTIN_PROC_WORK *apw = syswork;
	AOLOCAL_OPENING_EFF *oe;
	
	oe = sys_AllocMemory(HEAPID_ACTIN, sizeof(AOLOCAL_OPENING_EFF));
	MI_CpuClear8(oe, sizeof(AOLOCAL_OPENING_EFF));
	
	oe->apw = apw;
	oe->req_head = *req_head;

	TCB_Add(AOTCB_OpeningEffect, oe, TCBPRI_ACTIN_ORDERSUB);
}

//--------------------------------------------------------------
/**
 * @brief   �I�[�v�j���O�G�t�F�N�g
 *
 * @param   tcb			TCB�ւ̃|�C���^
 * @param   work		AOLOCAL_OPENING_EFF�\����
 */
//--------------------------------------------------------------
static void AOTCB_OpeningEffect(TCB_PTR tcb, void *work)
{
	AOLOCAL_OPENING_EFF *oe = work;
	
	switch(oe->seq){
	case 0:
		AT_AudienceAnimeSet(oe->apw, 0, 0, ACTIN_AUDIENCE_VOLUME, FALSE, &oe->audience_anm_end);
		oe->seq++;
		break;
	case 1:
		oe->wait++;
		if(oe->wait > OPENING_START_WAIT){
			oe->wait = 0;
			oe->seq++;
		}
		break;
	case 2:
		if(oe->audience_anm_end == TRUE){
			oe->seq++;
		}
		break;
	default:
		CO_ANSWER_TransmitBufferSet(&oe->apw->cow, &oe->req_head, NULL, 0);
		
		sys_FreeMemoryEz(oe);
		TCB_Delete(tcb);
		return;
	}
}



//==============================================================================
//	
//==============================================================================
//--------------------------------------------------------------
/**
 * @brief   ���ߑ��M(���M��)�F�G���f�B���O�G�t�F�N�g
 *
 * @param   apw			���Z�͕���Ǘ����[�N�ւ̃|�C���^
 * @param   work		�C�ӂ̃|�C���^
 *
 * @retval  �o�^���ꂽ���N�G�X�g�r�b�g�ԍ�
 */
//--------------------------------------------------------------
static int Request_EndingEffect(CONTEST_ORDER_WORK *cow, void *syswork, int order_no, void *work)
{
	ACTIN_PROC_WORK *apw = syswork;
	int bit_no;
	
	bit_no = CO_REQUEST_TransmitBufferSet(&apw->cow, CSELECT_ALL, order_no, 
		work, sizeof(ACTIN_ADVANCE_PARAM));
	return bit_no;
}

//--------------------------------------------------------------
/**
 * @brief   ���ߎ�M(���M��)�F�G���f�B���O�G�t�F�N�g
 *
 * @param   apw			���Z�͕���Ǘ����[�N�ւ̃|�C���^
 * @param   req_head	���N�G�X�g�w�b�_�̃|�C���^
 * @param   data		��M�f�[�^�ւ̃|�C���^
 */
//--------------------------------------------------------------
static void Recieve_EndingEffect(CONTEST_ORDER_WORK *cow, void *syswork, const CORDER_HEAD *req_head, void *data)
{
	ACTIN_PROC_WORK *apw = syswork;
	ACTIN_ADVANCE_PARAM *aap = data;
	AOLOCAL_ENDING_EFF *ee;
	
	ee = sys_AllocMemory(HEAPID_ACTIN, sizeof(AOLOCAL_ENDING_EFF));
	MI_CpuClear8(ee, sizeof(AOLOCAL_ENDING_EFF));
	
	ee->apw = apw;
	ee->req_head = *req_head;
	ee->a_talk_id = aap->nt.a_talk_id;
	ee->a_talk_tagpara = aap->nt.a_talk_tagpara;

	TCB_Add(AOTCB_EndingEffect, ee, TCBPRI_ACTIN_ORDERSUB);
}

//--------------------------------------------------------------
/**
 * @brief   �G���f�B���O�G�t�F�N�g
 *
 * @param   tcb			TCB�ւ̃|�C���^
 * @param   work		AOLOCAL_ENDING_EFF�\����
 */
//--------------------------------------------------------------
static void AOTCB_EndingEffect(TCB_PTR tcb, void *work)
{
	AOLOCAL_ENDING_EFF *ee = work;
	
	switch(ee->seq){
	case 0:
		if(ee->a_talk_id != A_TALK_NULL){
			AT_A_TalkMessageSet(ee->apw, ee->a_talk_id, &ee->a_talk_tagpara, NULL);
		}
		Snd_SePlay(ASE_ACTIN_STOP);
		ee->seq++;
		break;
	case 1:
		if(ee->a_talk_id == A_TALK_NULL || AT_TalkMessageEndCheck(ee->apw) == 0){
			ee->seq++;
		}
		break;
	case 2:
		ee->wait++;
		if(ee->wait > ENDING_WAIT){
			ee->wait = 0;
			ee->seq++;
		}
		break;
	case 3:
		AT_AudienceAnimeSet(ee->apw, 0, 0, ACTIN_AUDIENCE_VOLUME, FALSE, &ee->audience_anm_end);
		ee->seq++;
		break;
	case 4:
		if(ee->audience_anm_end == TRUE){
			ee->seq++;
		}
		break;
	default:
		CO_ANSWER_TransmitBufferSet(&ee->apw->cow, &ee->req_head, NULL, 0);
		
		sys_FreeMemoryEz(ee);
		TCB_Delete(tcb);
		return;
	}
}




//==============================================================================
//	
//==============================================================================
//--------------------------------------------------------------
/**
 * @brief   ���ߑ��M(���M��)�F�|�P�����o��
 *
 * @param   apw			���Z�͕���Ǘ����[�N�ւ̃|�C���^
 * @param   work		�i�s�p�����[�^
 *
 * @retval  �o�^���ꂽ���N�G�X�g�r�b�g�ԍ�
 */
//--------------------------------------------------------------
static int Request_PokemonIn(CONTEST_ORDER_WORK *cow, void *syswork, int order_no, void *work)
{
	ACTIN_PROC_WORK *apw = syswork;
	int bit_no;
	
	bit_no = CO_REQUEST_TransmitBufferSet(
		&apw->cow, CSELECT_ALL, order_no, work, sizeof(ACTIN_ADVANCE_PARAM));
	return bit_no;
}

//--------------------------------------------------------------
/**
 * @brief   ���ߎ�M(���M��)�F�|�P�����o��
 *
 * @param   apw			���Z�͕���Ǘ����[�N�ւ̃|�C���^
 * @param   req_head	���N�G�X�g�w�b�_�̃|�C���^
 * @param   data		��M�f�[�^�ւ̃|�C���^
 */
//--------------------------------------------------------------
static void Recieve_PokemonIn(CONTEST_ORDER_WORK *cow, void *syswork, const CORDER_HEAD *req_head, void *data)
{
	ACTIN_PROC_WORK *apw = syswork;
	AOLOCAL_POKE_INOUT *pi;
	ACTIN_ADVANCE_PARAM *aap;
	
	aap = data;
	
	pi = sys_AllocMemory(HEAPID_ACTIN, sizeof(AOLOCAL_POKE_INOUT));
	MI_CpuClear8(pi, sizeof(AOLOCAL_POKE_INOUT));
	
	pi->apw = apw;
	pi->req_head = *req_head;
	pi->breeder_no = aap->now_breeder;
	
	//AT_TalkWinSlideTaskSet(&apw->sys, TALKWIN_SLIDE_DIR_OUT, &pi->slide_end);
	AT_BrdPanelAlphaEffectSet(apw, BRDPANEL_ALPHA_TYPE_RETIRE, &pi->slide_end);
	TCB_Add(AOTCB_PokemonIn, pi, TCBPRI_ACTIN_ORDERSUB);
	
	AT_TalkMessageWinClear(apw);
}

//--------------------------------------------------------------
/**
 * @brief   �|�P�����o��
 *
 * @param   tcb			TCB�ւ̃|�C���^
 * @param   work		AOLOCAL_POKE_INOUT�\����
 */
//--------------------------------------------------------------
static void AOTCB_PokemonIn(TCB_PTR tcb, void *work)
{
	AOLOCAL_POKE_INOUT *pi = work;
	int now, height;
	
	now = pi->breeder_no;
	height = PokeParaHeightGet(pi->apw->sys.c_game->pp[now], PARA_BACK);
	
	switch(pi->seq){
	case 0:
		pi->wait++;
		if(pi->wait > ACTIN_POKEMOVE_IN_BEFORE_WAIT){
			pi->wait = 0;
			pi->seq++;
		}
		break;
	case 1:
		{
			int now, height;
			
			now = pi->breeder_no;
			height = PokeParaHeightGet(pi->apw->sys.c_game->pp[now], PARA_BACK);
			
			SoftSpriteParaSet(pi->apw->sys.ss[now], SS_PARA_DRAW_STOP, FALSE);
			SoftSpriteParaSet(pi->apw->sys.ss[now], SS_PARA_VANISH, FALSE);
			SoftSpriteParaSet(pi->apw->sys.ss[now], SS_PARA_POS_X, ACTIN_POKEPOS_APPEAR_X);
			SoftSpriteParaSet(pi->apw->sys.ss[now], SS_PARA_POS_Y, ACTIN_POKEPOS_APPEAR_Y + height);
			
			pi->x = ACTIN_POKEPOS_APPEAR_X << 8;
			pi->y = ACTIN_POKEPOS_APPEAR_Y << 8;
		}
		pi->seq++;
		break;

	case 2:
		if(pi->breeder_no == pi->apw->consys->c_game.my_breeder_no){
			Snd_SePlay(ASE_MY_POKEMON);
		}
		pi->seq++;
		//break;
	case 3:
		pi->x -= ACTIN_POKEMOVE_IN_X;
		pi->y -= ACTIN_POKEMOVE_IN_Y;
		if((pi->x >> 8) <= ACTIN_POKEPOS_X || (pi->y >> 8) <= ACTIN_POKEPOS_Y){
			pi->x = ACTIN_POKEPOS_X << 8;
			pi->y = ACTIN_POKEPOS_Y << 8;
			pi->seq++;
		}
		SoftSpriteParaSet(pi->apw->sys.ss[pi->breeder_no], SS_PARA_POS_X, pi->x >> 8);
		SoftSpriteParaSet(pi->apw->sys.ss[pi->breeder_no], SS_PARA_POS_Y, 
			(pi->y >> 8) + height);
		break;
	default:
		if(pi->slide_end == TRUE){
			CO_ANSWER_TransmitBufferSet(&pi->apw->cow, &pi->req_head, NULL, 0);
			
			sys_FreeMemoryEz(pi);
			TCB_Delete(tcb);
			return;
		}
		break;
	}
}

//==============================================================================
//	
//==============================================================================
//--------------------------------------------------------------
/**
 * @brief   ���ߑ��M(���M��)�F�|�P�����ޏ�
 *
 * @param   apw			���Z�͕���Ǘ����[�N�ւ̃|�C���^
 * @param   work		�i�s�p�����[�^
 *
 * @retval  �o�^���ꂽ���N�G�X�g�r�b�g�ԍ�
 */
//--------------------------------------------------------------
static int Request_PokemonOut(CONTEST_ORDER_WORK *cow, void *syswork, int order_no, void *work)
{
	ACTIN_PROC_WORK *apw = syswork;
	int bit_no;
	
	bit_no = CO_REQUEST_TransmitBufferSet(
		&apw->cow, CSELECT_ALL, order_no, work, sizeof(ACTIN_ADVANCE_PARAM));
	return bit_no;
}

//--------------------------------------------------------------
/**
 * @brief   ���ߎ�M(���M��)�F�|�P�����ޏ�
 *
 * @param   apw			���Z�͕���Ǘ����[�N�ւ̃|�C���^
 * @param   req_head	���N�G�X�g�w�b�_�̃|�C���^
 * @param   data		��M�f�[�^�ւ̃|�C���^
 */
//--------------------------------------------------------------
static void Recieve_PokemonOut(CONTEST_ORDER_WORK *cow, void *syswork, const CORDER_HEAD *req_head, void *data)
{
	ACTIN_PROC_WORK *apw = syswork;
	AOLOCAL_POKE_INOUT *pi;
	ACTIN_ADVANCE_PARAM *aap;
	int height, now;
	
	aap = data;
	
	pi = sys_AllocMemory(HEAPID_ACTIN, sizeof(AOLOCAL_POKE_INOUT));
	MI_CpuClear8(pi, sizeof(AOLOCAL_POKE_INOUT));
	
	pi->apw = apw;
	pi->req_head = *req_head;
	pi->breeder_no = aap->now_breeder;

	now = pi->breeder_no;
	height = PokeParaHeightGet(apw->sys.c_game->pp[now], PARA_BACK);

	pi->x = ACTIN_POKEPOS_X << 8;
	pi->y = ACTIN_POKEPOS_Y << 8;
	
	//AT_TalkWinSlideTaskSet(&apw->sys, TALKWIN_SLIDE_DIR_IN, &pi->slide_end);
	TCB_Add(AOTCB_PokemonOut, pi, TCBPRI_ACTIN_ORDERSUB);
}

//--------------------------------------------------------------
/**
 * @brief   �|�P�����ޏ�
 *
 * @param   tcb			TCB�ւ̃|�C���^
 * @param   work		AOLOCAL_POKE_INOUT�\����
 */
//--------------------------------------------------------------
static void AOTCB_PokemonOut(TCB_PTR tcb, void *work)
{
	AOLOCAL_POKE_INOUT *pi = work;
	int now, height;
	
	now = pi->breeder_no;
	height = PokeParaHeightGet(pi->apw->sys.c_game->pp[now], PARA_BACK);
	
	switch(pi->seq){
	case 0:
		pi->x += ACTIN_POKEMOVE_OUT_X;
		pi->y += ACTIN_POKEMOVE_OUT_Y;
		if((pi->x >> 8) >= ACTIN_POKEPOS_APPEAR_X || (pi->y >> 8) >= ACTIN_POKEPOS_APPEAR_Y){
			SoftSpriteParaSet(pi->apw->sys.ss[now], SS_PARA_DRAW_STOP, TRUE);
			SoftSpriteParaSet(pi->apw->sys.ss[now], SS_PARA_VANISH, TRUE);
			pi->seq++;
		}
		SoftSpriteParaSet(pi->apw->sys.ss[pi->breeder_no], SS_PARA_POS_X, pi->x >> 8);
		SoftSpriteParaSet(pi->apw->sys.ss[pi->breeder_no], SS_PARA_POS_Y, 
			(pi->y >> 8) + height);
		break;
	case 1:
		if(pi->apw->hensin_flag[pi->breeder_no] == TRUE){
			AT_SoftSpriteHensinPop(&pi->apw->sys, pi->breeder_no);
			pi->apw->hensin_flag[pi->breeder_no] = FALSE;
		}
		pi->seq++;
		break;
	default:
		CO_ANSWER_TransmitBufferSet(&pi->apw->cow, &pi->req_head, NULL, 0);
		
		sys_FreeMemoryEz(pi);
		TCB_Delete(tcb);
		return;
	}
}

//==============================================================================
//	
//==============================================================================
//--------------------------------------------------------------
/**
 * @brief   ���ߑ��M(���M��)�F�Z�G�t�F�N�g���o���O�ɍs������
 *
 * @param   apw			���Z�͕���Ǘ����[�N�ւ̃|�C���^
 * @param   work		�C�ӂ̃|�C���^
 *
 * @retval  �o�^���ꂽ���N�G�X�g�r�b�g�ԍ�
 */
//--------------------------------------------------------------
static int Request_WazaEffectBefore(CONTEST_ORDER_WORK *cow, void *syswork, int order_no, void *work)
{
	ACTIN_PROC_WORK *apw = syswork;
	int bit_no;
	
	bit_no = CO_REQUEST_TransmitBufferSet(&apw->cow, CSELECT_ALL, order_no, 
		work, sizeof(ACTIN_ADVANCE_PARAM));
	return bit_no;
}

//--------------------------------------------------------------
/**
 * @brief   ���ߎ�M(���M��)�F�Z�G�t�F�N�g���o���O�ɍs������
 *
 * @param   apw			���Z�͕���Ǘ����[�N�ւ̃|�C���^
 * @param   req_head	���N�G�X�g�w�b�_�̃|�C���^
 * @param   data		��M�f�[�^�ւ̃|�C���^
 */
//--------------------------------------------------------------
static void Recieve_WazaEffectBefore(CONTEST_ORDER_WORK *cow, void *syswork, const CORDER_HEAD *req_head, void *data)
{
	ACTIN_PROC_WORK *apw = syswork;
	AOLOCAL_WAZAEFF_BEFORE *wb;
	ACTIN_ADVANCE_PARAM *aap = data;
	
	wb = sys_AllocMemory(HEAPID_ACTIN, sizeof(AOLOCAL_WAZAEFF_BEFORE));
	MI_CpuClear8(wb, sizeof(AOLOCAL_WAZAEFF_BEFORE));
	
	wb->apw = apw;
	wb->req_head = *req_head;
	wb->breeder_no = aap->now_breeder;
	wb->judge_no = aap->judge_no;
	wb->a_talk_id = aap->nt.a_talk_id;
	wb->a_talk_tagpara = aap->nt.a_talk_tagpara;
	wb->judge_reaction_type = aap->judge_reaction_type;
	
	TCB_Add(AOTCB_WazaEffectBefore, wb, TCBPRI_ACTIN_ORDERSUB);
}

//--------------------------------------------------------------
/**
 * @brief   �Z�G�t�F�N�g���o���O�ɍs������
 *
 * @param   tcb			TCB�ւ̃|�C���^
 * @param   work		AOLOCAL_WAZAEFF_BEFORE�\����
 */
//--------------------------------------------------------------
static void AOTCB_WazaEffectBefore(TCB_PTR tcb, void *work)
{
	AOLOCAL_WAZAEFF_BEFORE *wb = work;
	int transparent_no;
	enum{
		WBSEQ_AUDIENCE_INIT,
		WBSEQ_AUDIENCE_WAIT,
		WBSEQ_AUDIENCE_END,
		WBSEQ_MSG_INIT,
		WBSEQ_MSG_WAIT,
		WBSEQ_MSG_END,
		WBSEQ_JUDGE_REACTION_INIT,
		WBSEQ_JUDGE_REACTION_WAIT,
		WBSEQ_JUDGE_REACTION_END,
	};
	
	switch(wb->seq){
	case WBSEQ_AUDIENCE_INIT:
		{
			int volume;
			
			volume = AT_AudienceVolumeGet(wb->apw->a_game.app_total[wb->breeder_no]);
			if(volume > 0){
				AT_AudienceAnimeSet(wb->apw, 0, 0, volume, FALSE, &wb->audience_anm_end);
			}
			else{
				wb->seq = WBSEQ_AUDIENCE_END;
				break;
			}
		}
		wb->seq++;
		break;
	case WBSEQ_AUDIENCE_WAIT:
		if(wb->audience_anm_end == TRUE){
			wb->seq++;
		}
		break;
	case WBSEQ_AUDIENCE_END:
		wb->seq++;
		break;
	
	case WBSEQ_MSG_INIT:
		if(wb->a_talk_id != A_TALK_NULL){
			AT_A_TalkMessageSet(wb->apw, wb->a_talk_id, &wb->a_talk_tagpara, NULL);
			wb->seq++;
		}
		else{
			wb->seq = WBSEQ_MSG_END;
		}
		break;
	case WBSEQ_MSG_WAIT:
		if(AT_TalkMessageEndCheck(wb->apw) == 0){
			wb->seq++;
		}
		break;
	case WBSEQ_MSG_END:
		wb->seq++;
		break;

	case WBSEQ_JUDGE_REACTION_INIT:
		AT_JudgeReactionIconON(&wb->apw->sys, wb->judge_no, wb->judge_reaction_type);
		AT_JudgeReactionMoveTaskSet(wb->apw, wb->judge_no, wb->judge_reaction_type, 
			&wb->reaction_end);
		wb->seq++;
		break;
	case WBSEQ_JUDGE_REACTION_WAIT:
		if(wb->reaction_end == TRUE){
			wb->seq++;
		}
		break;
	case WBSEQ_JUDGE_REACTION_END:
		wb->wait++;
		if(wb->wait > WAZABEFORE_JUDGE_REACTION_END_WAIT){
			AT_JudgeReactionIconOFF(&wb->apw->sys);
			wb->seq++;
		}
		break;
	
	default:
		CO_ANSWER_TransmitBufferSet(&wb->apw->cow, &wb->req_head, NULL, 0);

		sys_FreeMemoryEz(wb);
		TCB_Delete(tcb);
		return;
	}
}

//==============================================================================
//	
//==============================================================================
//--------------------------------------------------------------
/**
 * @brief   ���ߑ��M(���M��)�F�Z�G�t�F�N�g���o��
 *
 * @param   apw			���Z�͕���Ǘ����[�N�ւ̃|�C���^
 * @param   work		�C�ӂ̃|�C���^
 *
 * @retval  �o�^���ꂽ���N�G�X�g�r�b�g�ԍ�
 */
//--------------------------------------------------------------
static int Request_WazaEffect(CONTEST_ORDER_WORK *cow, void *syswork, int order_no, void *work)
{
	ACTIN_PROC_WORK *apw = syswork;
	int bit_no;
	
	bit_no = CO_REQUEST_TransmitBufferSet(&apw->cow, CSELECT_ALL, order_no, 
		work, sizeof(ACTIN_ADVANCE_PARAM));
	return bit_no;
}

//--------------------------------------------------------------
/**
 * @brief   ���ߎ�M(���M��)�F�Z�G�t�F�N�g���o��
 *
 * @param   apw			���Z�͕���Ǘ����[�N�ւ̃|�C���^
 * @param   req_head	���N�G�X�g�w�b�_�̃|�C���^
 * @param   data		��M�f�[�^�ւ̃|�C���^
 */
//--------------------------------------------------------------
static void Recieve_WazaEffect(CONTEST_ORDER_WORK *cow, void *syswork, const CORDER_HEAD *req_head, void *data)
{
	ACTIN_PROC_WORK *apw = syswork;
	AOLOCAL_WAZAEFF *we;
	ACTIN_ADVANCE_PARAM *aap = data;
	
	we = sys_AllocMemory(HEAPID_ACTIN, sizeof(AOLOCAL_WAZAEFF));
	MI_CpuClear8(we, sizeof(AOLOCAL_WAZAEFF));
	
	we->apw = apw;
	we->req_head = *req_head;
	we->breeder_no = aap->now_breeder;
	we->waza_no = aap->wazapara.personal[aap->now_breeder].wazano;//aap->waza_no;
	we->a_talk_id = aap->nt.a_talk_id;
	we->a_talk_tagpara = aap->nt.a_talk_tagpara;
	we->after_a_talk_id = aap->nt.after_a_talk_id;
	we->after_a_talk_tagpara = aap->nt.after_a_talk_tagpara;
	we->aap = *aap;
	
	TCB_Add(AOTCB_WazaEffect, we, TCBPRI_ACTIN_WAZAEFF);
}

//--------------------------------------------------------------
/**
 * @brief   �Z�G�t�F�N�g���s
 *
 * @param   tcb			TCB�ւ̃|�C���^
 * @param   work		AOLOCAL_WAZAEFF�\����
 */
//--------------------------------------------------------------
static void AOTCB_WazaEffect(TCB_PTR tcb, void *work)
{
	AOLOCAL_WAZAEFF *we = work;
	int transparent_no;
	AWAZA_PERSONAL *my_personal;
	enum{
		WESEQ_MSG_INIT,
		WESEQ_MSG_WAIT,
		WESEQ_MSG_END,
		WESEQ_WAZAMSG_INIT,
		WESEQ_WAZAMSG_WAIT,
		WESEQ_WAZAMSG_END,
		WESEQ_AFTERMSG_INIT,
		WESEQ_AFTERMSG_WAIT,
		WESEQ_AFTERMSG_END,
		WESEQ_EFF_INIT,
		WESEQ_EFF_SET,
		WESEQ_EFF_WAIT,
		WESEQ_EFF_AFTER,
		WESEQ_PANEL_IN,
		WESEQ_PANEL_WAIT,
	};
	
	my_personal = &we->aap.wazapara.personal[we->breeder_no];
	switch(we->seq){
	case WESEQ_MSG_INIT:
		if(we->a_talk_id != A_TALK_NULL){
			AT_A_TalkMessageSet(we->apw, we->a_talk_id, &we->a_talk_tagpara, NULL);
			we->seq++;
		}
		else{
			we->seq = WESEQ_MSG_END;
		}
		break;
	case WESEQ_MSG_WAIT:
		if(AT_TalkMessageEndCheck(we->apw) == 0){
			we->seq++;
		}
		break;
	case WESEQ_MSG_END:
		we->seq++;
		break;

	case WESEQ_WAZAMSG_INIT:
		if(my_personal->msg_apno != 0){
			AT_WazaKoukaTalkMessageSet(we->apw, my_personal->msg_apno, my_personal->msg_type, 
				&my_personal->tagpara, NULL);
			we->seq++;
		}
		else{
			we->seq = WESEQ_WAZAMSG_END;
		}
		break;
	case WESEQ_WAZAMSG_WAIT:
		if(AT_TalkMessageEndCheck(we->apw) == 0){
			we->seq++;
		}
		break;
	case WESEQ_WAZAMSG_END:
		we->seq++;
		break;

	case WESEQ_AFTERMSG_INIT:
		if(we->after_a_talk_id != A_TALK_NULL){
			AT_A_TalkMessageSet(we->apw, we->after_a_talk_id, &we->a_talk_tagpara, NULL);
			we->seq++;
		}
		else{
			we->seq = WESEQ_AFTERMSG_END;
		}
		break;
	case WESEQ_AFTERMSG_WAIT:
		if(AT_TalkMessageEndCheck(we->apw) == 0){
			we->seq++;
		}
		break;
	case WESEQ_AFTERMSG_END:
		we->seq++;
		break;
	
	case WESEQ_EFF_INIT:
		AT_WazaEffParamSet(we->apw->consys, we->breeder_no, we->waza_no, &we->wazapara);
		we->seq++;
		//break;
	case WESEQ_EFF_SET:
		{
			WAZA_EFFECT_PARAM eff;
			WES_CALL_BTL_EX_PARAM exparam;
			int i;
			int monsno, sex, rare, form_no;
			int def_monsno, def_sex, def_rare, def_form_no;
			u32 personal_rnd, def_personal_rnd;
			int def_breeder_no;
			
			def_breeder_no = we->breeder_no + 1;
			if(def_breeder_no >= BREEDER_MAX){
				def_breeder_no = 0;
			}
			
			MI_CpuClear8(&eff, sizeof(WAZA_EFFECT_PARAM));
			MI_CpuClear8(&exparam, sizeof(WES_CALL_BTL_EX_PARAM));
			
			monsno = PokeParaGet(we->apw->sys.c_game->pp[we->breeder_no], ID_PARA_monsno, NULL);
			sex = PokeParaGet(we->apw->sys.c_game->pp[we->breeder_no], ID_PARA_sex, NULL);
			rare = PokeRareGet(we->apw->sys.c_game->pp[we->breeder_no]);
			form_no = PokeParaGet(we->apw->sys.c_game->pp[we->breeder_no], ID_PARA_form_no, NULL);
			personal_rnd = PokeParaGet(we->apw->sys.c_game->pp[we->breeder_no], 
				ID_PARA_personal_rnd, NULL);

			def_monsno = PokeParaGet(we->apw->sys.c_game->pp[def_breeder_no], 
				ID_PARA_monsno, NULL);
			def_sex = PokeParaGet(we->apw->sys.c_game->pp[def_breeder_no], ID_PARA_sex, NULL);
			def_rare = PokeRareGet(we->apw->sys.c_game->pp[def_breeder_no]);
			def_form_no = PokeParaGet(we->apw->sys.c_game->pp[def_breeder_no], 
				ID_PARA_form_no, NULL);
			def_personal_rnd = PokeParaGet(we->apw->sys.c_game->pp[def_breeder_no], 
				ID_PARA_personal_rnd, NULL);
			
			//WAZA_EFFECT_PARAM�f�[�^�쐬
			//power��Ȃ��x�Ȃǂ̎擾���܂����m�� 2005.11.29(��) ��check
			eff.command_code = 0;
			eff.mode = 0;
			eff.waza_no = we->wazapara.wazano;
			eff.waza_eff_damage = 1;
			eff.waza_eff_power = 10;
			eff.waza_eff_cnt = we->wazapara.counter;
			eff.waza_eff_natuki = we->wazapara.natukido;
			eff.waza_eff_weather = 0;
			eff.at_client_no = 0;
			eff.df_client_no = 1;
			eff.ground_id = GROUND_ID_FLOOR;
			for(i = 0; i < CLIENT_MAX; i++){
				eff.mons_no[i] = monsno;
			}
			eff.mons_no[1] = def_monsno;
			
			//WES_CALL_BTL_EX_PARAM�f�[�^�쐬
//			we->exchr_tbl[0] = &we->apw->sys.exchr_param[we->breeder_no];
//			we->exchr_tbl[1] = &we->apw->sys.transparent_exchr_param;
			exparam.bgl = we->apw->sys.bgl;
			exparam.pfd = we->apw->sys.pfd;
			exparam.excp[0] = &we->apw->sys.exchr_param[we->breeder_no];
			exparam.excp[1] = &we->apw->sys.transparent_exchr_param;

			for(i = 0; i < CLIENT_MAX; i++){
				exparam.client_type[i] = 0xff;
				exparam.mons_no[i] = monsno;
				exparam.sex[i] = sex;
				exparam.rare[i] = rare;
				exparam.form_no[i] = form_no;
				exparam.personal_rnd[i] = personal_rnd;
				exparam.waza_kouka[i] = 0;
			}
			exparam.waza_kouka[0] = we->wazapara.waza_kouka;
			exparam.client_type[0] = CLIENT_TYPE_AA;
			exparam.client_type[1] = CLIENT_TYPE_BB;
			exparam.mons_no[1] = def_monsno;
			exparam.sex[1] = def_sex;
			exparam.rare[1] = def_rare;
			exparam.form_no[1] = def_form_no;
			exparam.personal_rnd[1] = def_personal_rnd;

			exparam.ss[0] = we->apw->sys.ss[we->breeder_no];
			transparent_no = (we->breeder_no == 0) ? 1 : 0;
			exparam.ss[1] = we->apw->sys.ss[transparent_no];
			exparam.fight_type = 0;
			exparam.eff_arc_id = ARC_WAZA_EFF;
			exparam.haikei_data.arc_index = ARC_CONTEST_BG;
			exparam.haikei_data.chr_id = CON_BG_NCGR_BIN;
			exparam.haikei_data.pal_id = CONTEST_BG_NCLR;
			exparam.haikei_data.scr_id = CON_BG_NSCR_BIN;
			exparam.haikei_data.pal_start = ACTIN_HAIKEI_PAL_START;
			exparam.haikei_data.pal_num = ACTIN_HAIKEI_PAL_NUM;
			exparam.csp = we->apw->sys.csp;
			exparam.perap_voice = we->apw->consys->perap_voice[we->breeder_no];
			//�Z�G�t�F�N�g�Z�b�g
			WES_Call_Ex(we->apw->sys.wsp, &eff, we->wazapara.wazano, &exparam);
		}
		
		//�\�t�g�E�F�A�X�v���C�g�̐ݒ�
		{
			int height;
			
			height = PokeParaHeightGet(we->apw->sys.c_game->pp[we->breeder_no], PARA_BACK);
			
			if(we->wazapara.waza_kouka != WAZAKOUKA_KIE_OFF){	//�V���h�[�_�C�u�p
				SoftSpriteParaSet(we->apw->sys.ss[we->breeder_no], SS_PARA_VANISH, FALSE);
			}
			SoftSpriteParaSet(we->apw->sys.ss[we->breeder_no], SS_PARA_DRAW_STOP, FALSE);
			SoftSpriteParaSet(we->apw->sys.ss[we->breeder_no], 
				SS_PARA_POS_X, CONTEST_ATTACK_POKE_X);
			SoftSpriteParaSet(we->apw->sys.ss[we->breeder_no], 
				SS_PARA_POS_Y, CONTEST_ATTACK_POKE_Y + height);
			
			SoftSpriteParaSet(we->apw->sys.ss[transparent_no], SS_PARA_DRAW_STOP, TRUE);
			SoftSpriteParaSet(we->apw->sys.ss[transparent_no], 
				SS_PARA_POS_X, CONTEST_DEFENCE_POKE_X);
			SoftSpriteParaSet(we->apw->sys.ss[transparent_no], 
				SS_PARA_POS_Y, CONTEST_DEFENCE_POKE_Y);
		}
		
		we->seq++;
		break;
	case WESEQ_EFF_WAIT:	//�Z�G�t�F�N�g���s
		WES_Executed(we->apw->sys.wsp);
		if(IsWES_Executed(we->apw->sys.wsp) == FALSE){
			WES_Reset(we->apw->sys.wsp);
			if(we->wazapara.loop > 0){
				we->wazapara.loop--;
				we->wazapara.counter++;
				if(we->wazapara.waza_kouka == WAZAKOUKA_KIE){	//�V���h�[�_�C�u�p
					we->wazapara.waza_kouka = WAZAKOUKA_KIE_OFF;
				}
				we->seq = WESEQ_EFF_SET;
			}
			else{
				we->seq++;
			}
		}
		break;
	case WESEQ_EFF_AFTER:	//�Z�G�t�F�N�g�I����ɂ���K�v�̂���㏈��
		switch(we->wazapara.wazano){
		case WAZANO_HENSIN:
		case WAZANO_MIGAWARI:
			we->apw->hensin_flag[we->breeder_no] = TRUE;
			break;
		}
		we->seq++;
		break;
	
	case WESEQ_PANEL_IN:
		AT_BrdPanelAlphaEffectSet(we->apw, BRDPANEL_ALPHA_TYPE_RETURN, &we->panel_end);
		we->seq++;
		break;
	case WESEQ_PANEL_WAIT:
		if(we->panel_end == TRUE){
			we->seq++;
		}
		break;
	
	default:
		CO_ANSWER_TransmitBufferSet(&we->apw->cow, &we->req_head, NULL, 0);

		sys_FreeMemoryEz(we);
		TCB_Delete(tcb);
		return;
	}
}


//==============================================================================
//	
//==============================================================================
//--------------------------------------------------------------
/**
 * @brief   ���ߑ��M(���M��)�F�Z�I��
 *
 * @param   apw			���Z�͕���Ǘ����[�N�ւ̃|�C���^
 * @param   work		�C�ӂ̃|�C���^
 *
 * @retval  �o�^���ꂽ���N�G�X�g�r�b�g�ԍ�
 */
//--------------------------------------------------------------
static int Request_UserSelect(CONTEST_ORDER_WORK *cow, void *syswork, int order_no, void *work)
{
	ACTIN_PROC_WORK *apw = syswork;
	int bit_no;
	
	bit_no = CO_REQUEST_TransmitBufferSet(&apw->cow, CSELECT_ALL, order_no, NULL, 0);
	return bit_no;
}

//--------------------------------------------------------------
/**
 * @brief   ���ߎ�M(���M��)�F�Z�I��
 *
 * @param   apw			���Z�͕���Ǘ����[�N�ւ̃|�C���^
 * @param   req_head	���N�G�X�g�w�b�_�̃|�C���^
 * @param   data		��M�f�[�^�ւ̃|�C���^
 */
//--------------------------------------------------------------
static void Recieve_UserSelect(CONTEST_ORDER_WORK *cow, void *syswork, const CORDER_HEAD *req_head, void *data)
{
	ACTIN_PROC_WORK *apw = syswork;
	AOLOCAL_WAZASELECT *ws;
	ACTIN_ADVANCE_PARAM *aap = data;
	
	ws = sys_AllocMemory(HEAPID_ACTIN, sizeof(AOLOCAL_WAZASELECT));
	MI_CpuClear8(ws, sizeof(AOLOCAL_WAZASELECT));
	
	ws->apw = apw;
	ws->req_head = *req_head;
	ws->breeder_no = apw->sys.c_game->my_breeder_no;	//aap->now_breeder;

	TCB_Add(AOTCB_UserSelect, ws, TCBPRI_ACTIN_WAZASELECT);

//	CO_ANSWER_TransmitBufferSet(&apw->cow, req_head, &waza_no, sizeof(waza_no));
}

//--------------------------------------------------------------
/**
 * @brief   �Z�I�����s
 *
 * @param   tcb			TCB�ւ̃|�C���^
 * @param   work		AOLOCAL_WAZASELECT�\����
 */
//--------------------------------------------------------------
static void AOTCB_UserSelect(TCB_PTR tcb, void *work)
{
	AOLOCAL_WAZASELECT *ws = work;
	int tp_ret;
	enum{
		SELSEQ_INIT,
		SELSEQ_WAZA_INIT,
		SELSEQ_WAZA_MSG_WAIT,
		SELSEQ_WAZA_TOUCH_WAIT,
		SELSEQ_WAZA_END_WAIT,
		SELSEQ_WAZA_END,
		SELSEQ_JUDGE_INIT,
		SELSEQ_JUDGE_MSG_WAIT,
		SELSEQ_JUDGE_TOUCH_WAIT,
		SELSEQ_JUDGE_END_WAIT,
		SELSEQ_JUDGE_END,
	};
	
	switch(ws->seq){
	case SELSEQ_INIT:
		//�����ɋZ�I����ʂ��o�����Ƃ���ƁA�����N�����̓o�j�b�V�����ꂸ�ɁA
		//���̂܂܍폜���Z���`��ƂȂ�̂ŁA���������̏u�Ԃ������Ă��܂��B
		//���̂��߁A1�t���[�������ǎ��݂̂̉�ʂ���������ŁA�����N���Ȃǂ��폜�����
		//�^�C�~���O�����B
		AINPUT_CreateBG(ws->apw->aip, AINPUT_TYPE_HEART_WALL, FALSE, NULL);
		ws->seq++;
		break;
		
	case SELSEQ_WAZA_INIT:
		AINPUT_CreateBG(ws->apw->aip, AINPUT_TYPE_WAZA, FALSE, NULL);
		{
			u32 a_talk_id;
			ATAG_PARAM tagpara;
			
			if(ws->apw->a_game.turn + 1 == ACTIN_END_TURN){
				a_talk_id = A_TALK_SELECT_WAZA_FINAL;
			}
			else{
				a_talk_id = A_TALK_SELECT_WAZA;
			}
			tagpara.num = ws->apw->a_game.turn + 1;
			AT_A_TalkMessageSet(ws->apw, a_talk_id, &tagpara, NULL);
		}
		
		if(ws->apw->a_game.turn + 1 == ACTIN_END_TURN && ws->final_turn_se == 0){
			Snd_SePlay(ASE_FINAL_TURN);
			ws->final_turn_se++;
		}
		
		ws->seq++;
		break;
	case SELSEQ_WAZA_MSG_WAIT:
		if(AT_TalkMessageEndCheck(ws->apw) != 0){
			break;
		}
		ws->seq++;
		//break;
	case SELSEQ_WAZA_TOUCH_WAIT:
		tp_ret = AINPUT_TouchCheck(ws->apw->aip);
		if(tp_ret != RECT_HIT_NONE){
			ws->usd.waza_no = PokeParaGet(ws->apw->sys.c_game->pp[ws->breeder_no], 
				ID_PARA_waza1 + tp_ret, NULL);
			Snd_SePlay(ASE_DECIDE);
			ws->seq++;
		}
		break;
	case SELSEQ_WAZA_END_WAIT:
		if(AINPUT_EffectEndCheck(ws->apw->aip) == FALSE){
			break;
		}
		ws->seq++;
		//break;
	case SELSEQ_WAZA_END:
		ws->seq++;
		//break;

	case SELSEQ_JUDGE_INIT:
		AINPUT_CreateBG(ws->apw->aip, AINPUT_TYPE_JUDGE, FALSE, NULL);

		{
			u32 a_talk_id;
			ATAG_PARAM tagpara;
			
			a_talk_id = A_TALK_SELECT_JUDGE;
			tagpara.num = ws->apw->a_game.turn + 1;
			AT_A_TalkMessageSet(ws->apw, a_talk_id, &tagpara, NULL);
		}
		ws->seq++;
		break;
	case SELSEQ_JUDGE_MSG_WAIT:
		if(AT_TalkMessageEndCheck(ws->apw) != 0){
			break;
		}
		ws->seq++;
		//break;
	case SELSEQ_JUDGE_TOUCH_WAIT:
		tp_ret = AINPUT_TouchCheck(ws->apw->aip);
		if(tp_ret != RECT_HIT_NONE){
			ws->usd.judge_no = tp_ret;
			Snd_SePlay(ASE_DECIDE);
			ws->seq++;
		}
		break;
	case SELSEQ_JUDGE_END_WAIT:
		if(AINPUT_EffectEndCheck(ws->apw->aip) == FALSE){
			break;
		}
	
		if(ws->usd.judge_no == ACTIN_TP_JUDGE_MODORU){
			ws->seq = SELSEQ_WAZA_INIT;
			break;
		}
		else{
			ws->seq++;
		}
		//break;
	case SELSEQ_JUDGE_END:
		ws->seq++;
		//break;
	
	default:
		if(ws->apw->consys->sio_flag == TRUE){
			AT_A_TalkMessageSet(ws->apw, A_TALK_SIO_WAIT, NULL, NULL);	//������@���������イ�c
		}
		
		CO_ANSWER_TransmitBufferSet(&ws->apw->cow, &ws->req_head, 
			&ws->usd, sizeof(USER_SELECT_DATA));

		AINPUT_CreateBG(ws->apw->aip, AINPUT_TYPE_WALL, FALSE, NULL);
		
		sys_FreeMemoryEz(ws);
		TCB_Delete(tcb);
		return;
	}
}

//--------------------------------------------------------------
/**
 * @brief   �Ԏ���M(���M��)�F�Z�I��
 *
 * @param   apw				���Z�͕���Ǘ����[�N�ւ̃|�C���^
 * @param   answer_head		�Ԏ��w�b�_�̃|�C���^
 * @param   data			��M�f�[�^�ւ̃|�C���^
 * @param   net_id			�Ԏ����M�҂̃l�b�gID
 */
//--------------------------------------------------------------
static void Answer_UserSelect(CONTEST_ORDER_WORK *cow, void *syswork, const CORDER_HEAD *answer_head, CO_ANSDAT *ansdat, int net_id)
{
	ACTIN_PROC_WORK *apw = syswork;
	USER_SELECT_DATA *usd;
	
	usd = ansdat->data[net_id];
	apw->a_game.waza_no[net_id] = usd->waza_no;
	apw->a_game.judge_no[net_id] = usd->judge_no;
}


//==============================================================================
//	
//==============================================================================
//--------------------------------------------------------------
/**
 * @brief   ���ߑ��M(���M��)�F�Z�̕]�����s��(���o)
 *
 * @param   apw			���Z�͕���Ǘ����[�N�ւ̃|�C���^
 * @param   work		�C�ӂ̃|�C���^
 *
 * @retval  �o�^���ꂽ���N�G�X�g�r�b�g�ԍ�
 */
//--------------------------------------------------------------
static int Request_AppealReview(CONTEST_ORDER_WORK *cow, void *syswork, int order_no, void *work)
{
	ACTIN_PROC_WORK *apw = syswork;
	int bit_no;
	
	bit_no = CO_REQUEST_TransmitBufferSet(&apw->cow, CSELECT_ALL, order_no, 
		work, sizeof(ACTIN_ADVANCE_PARAM));
	return bit_no;
}

//--------------------------------------------------------------
/**
 * @brief   ���ߎ�M(���M��)�F�Z�̕]�����s��(���o)
 *
 * @param   apw			���Z�͕���Ǘ����[�N�ւ̃|�C���^
 * @param   req_head	���N�G�X�g�w�b�_�̃|�C���^
 * @param   data		��M�f�[�^�ւ̃|�C���^
 */
//--------------------------------------------------------------
static void Recieve_AppealReview(CONTEST_ORDER_WORK *cow, void *syswork, const CORDER_HEAD *req_head, void *data)
{
#if 0
	ACTIN_PROC_WORK *apw = syswork;
	AOLOCAL_APPEALREVIEW *ae;
	ACTIN_ADVANCE_PARAM *aap = data;
	
	ae = sys_AllocMemory(HEAPID_ACTIN, sizeof(AOLOCAL_APPEALREVIEW));
	MI_CpuClear8(ae, sizeof(AOLOCAL_APPEALREVIEW));
	
	ae->apw = apw;
	ae->req_head = *req_head;
	ae->breeder_no = aap->now_breeder;
	ae->breeder_pos = aap->now_pos;
	ae->judge_no = aap->judge_no;
	ae->aap = *aap;

	ae->voltage = ae->aap.waza_personal.voltage_before[aap->judge_no];
	
	TCB_Add(AOTCB_AppealReview, ae, TCBPRI_ACTIN_ORDERSUB);
#endif
}

//--------------------------------------------------------------
/**
 * @brief   �Z�G�t�F�N�g���s
 *
 * @param   tcb			TCB�ւ̃|�C���^
 * @param   work		AOLOCAL_WAZAEFF�\����
 */
//--------------------------------------------------------------
static void AOTCB_AppealReview(TCB_PTR tcb, void *work)
{
#if 0
	AOLOCAL_APPEALREVIEW *ae = work;
	int voltage_ofs;
	enum{
		AR_INIT,
		AR_AP_INIT,
		AR_AP_MAIN,
		AR_AP_WAIT,
		AR_VOL_INIT,
		AR_VOL_MAIN,
		AR_VOL_WAIT,
		AR_VOL_AP_ADD_INIT,
		AR_VOL_AP_ADD_MAIN,
		AR_VOL_AP_ADD_WAIT,
		AR_END,
	};
	
	switch(ae->seq){
	case AR_INIT:
		OS_TPrintf("�u���[�_�[�ԍ�=%d\n", ae->breeder_no);
		OS_TPrintf("��{AP=%d\n������R���̐�=%d\n�{���e�[�W����=%d\n�ŏIAP�l=%d\n\n", 
			ae->aap.waza_personal.base_app, ae->aap.waza_personal.judge_suffer, 
			ae->aap.waza_personal.voltage_after[ae->aap.waza_personal.judge_no] 
			- ae->aap.waza_personal.voltage_before[ae->aap.waza_personal.judge_no], 
			ae->aap.waza_personal.app_total);
		
		ae->seq++;
		break;
	
	case AR_AP_INIT:
		ae->seq++;
		break;
	case AR_AP_MAIN:		//�A�s�[���|�C���g
		if(ae->point < ae->aap.waza_personal.app_total - ae->aap.waza_personal.voltage_add_ap){
			ae->point += APPEAL_ICON_ONE_POINT;
			AT_AppealPointActorMadeOver(&ae->apw->sys, ae->breeder_no, ae->breeder_pos, ae->point);
		}
		ae->seq++;
		break;
	case AR_AP_WAIT:
		ae->wait++;
		if(ae->wait > APPEAL_ICON_LIGHT_WAIT){
			ae->wait = 0;
			if(ae->point >= ae->aap.waza_personal.app_total- ae->aap.waza_personal.voltage_add_ap){
				ae->seq++;
			}
			else{
				ae->seq--;
			}
		}
		break;
	
	case AR_VOL_INIT:
		ae->seq++;
		break;
	case AR_VOL_MAIN:		//�{���e�[�W
		if(ae->voltage != ae->aap.waza_personal.voltage_after[ae->judge_no]){
			voltage_ofs = ae->aap.waza_personal.voltage_after[ae->judge_no] 
				- ae->aap.waza_personal.voltage_before[ae->judge_no];
			if(voltage_ofs > 0){
				ae->voltage += VOLTAGE_ONE_POINT;
				AT_VoltagePointActorMadeOver(&ae->apw->sys, ae->judge_no, ae->voltage);
				Snd_SePlay( SEQ_SE_DP_BAG_011 );
			}
			else{
				ae->voltage -= VOLTAGE_ONE_POINT;
				AT_VoltagePointActorMadeOver(&ae->apw->sys, ae->judge_no, ae->voltage);
				Snd_SePlay( SEQ_SE_DP_BAG_006 );
			}
		}
		ae->seq++;
		break;
	case AR_VOL_WAIT:
		ae->wait++;
		if(ae->wait > VOLTAGE_ICON_LIGHT_WAIT){
			ae->wait = 0;
			if(ae->voltage == ae->aap.waza_personal.voltage_after[ae->judge_no]){
				ae->seq++;
			}
			else{
				ae->seq--;
			}
		}
		break;
	
	case AR_VOL_AP_ADD_INIT:
		if(ae->aap.waza_personal.voltage_after[ae->judge_no] < VOLTAGE_POINT_FULL){
			ae->seq = AR_END;
			break;
		}
		ae->seq++;
		break;
	case AR_VOL_AP_ADD_MAIN:
		if(ae->point < ae->aap.waza_personal.app_total){
			ae->point += APPEAL_ICON_ONE_POINT;
			AT_AppealPointActorMadeOver(&ae->apw->sys, ae->breeder_no, ae->breeder_pos, ae->point);
		}
		ae->seq++;
		break;
	case AR_VOL_AP_ADD_WAIT:
		ae->wait++;
		if(ae->wait > APPEAL_ICON_LIGHT_WAIT){
			ae->wait = 0;
			if(ae->point >= ae->aap.waza_personal.app_total){
				//�{���e�[�W�̕\���������B(���[�N�̕���NextBreeder�Őe���N���A���s���Ă���)
				AT_VoltagePointActorMadeOver(&ae->apw->sys, ae->judge_no, 0);
				ae->seq++;
			}
			else{
				ae->seq--;
			}
		}
		break;
		
	case AR_END:
	default:
		CO_ANSWER_TransmitBufferSet(&ae->apw->cow, &ae->req_head, NULL, 0);

		sys_FreeMemoryEz(ae);
		TCB_Delete(tcb);
		return;
	}
#endif
}

//==============================================================================
//	
//==============================================================================
//--------------------------------------------------------------
/**
 * @brief   ���ߑ��M(���M��)�F�Z�̕]�����s��(���o)
 *
 * @param   apw			���Z�͕���Ǘ����[�N�ւ̃|�C���^
 * @param   work		�C�ӂ̃|�C���^
 *
 * @retval  �o�^���ꂽ���N�G�X�g�r�b�g�ԍ�
 */
//--------------------------------------------------------------
static int Request_AppealFirst(CONTEST_ORDER_WORK *cow, void *syswork, int order_no, void *work)
{
	ACTIN_PROC_WORK *apw = syswork;
	int bit_no;
	
	bit_no = CO_REQUEST_TransmitBufferSet(&apw->cow, CSELECT_ALL, order_no, 
		work, sizeof(ACTIN_ADVANCE_PARAM));
	return bit_no;
}

//--------------------------------------------------------------
/**
 * @brief   ���ߎ�M(���M��)�F�Z�̕]�����s��(���o)
 *
 * @param   apw			���Z�͕���Ǘ����[�N�ւ̃|�C���^
 * @param   req_head	���N�G�X�g�w�b�_�̃|�C���^
 * @param   data		��M�f�[�^�ւ̃|�C���^
 */
//--------------------------------------------------------------
static void Recieve_AppealFirst(CONTEST_ORDER_WORK *cow, void *syswork, const CORDER_HEAD *req_head, void *data)
{
	ACTIN_PROC_WORK *apw = syswork;
	AOLOCAL_APPEALREVIEW *ae;
	ACTIN_ADVANCE_PARAM *aap = data;
	
	ae = sys_AllocMemory(HEAPID_ACTIN, sizeof(AOLOCAL_APPEALREVIEW));
	MI_CpuClear8(ae, sizeof(AOLOCAL_APPEALREVIEW));
	
	ae->apw = apw;
	ae->req_head = *req_head;
	ae->breeder_no = aap->now_breeder;
	ae->breeder_pos = aap->now_pos;
	//ae->judge_no = aap->judge_no;
	ae->aap = *aap;

//	ae->voltage = ae->aap.waza_personal.voltage_before[aap->judge_no];
	
	TCB_Add(AOTCB_AppealFirst, ae, TCBPRI_ACTIN_ORDERSUB);
}

//--------------------------------------------------------------
/**
 * @brief   �Z�]�����s
 *
 * @param   tcb			TCB�ւ̃|�C���^
 * @param   work		AOLOCAL_WAZAEFF�\����
 */
//--------------------------------------------------------------
static void AOTCB_AppealFirst(TCB_PTR tcb, void *work)
{
	AOLOCAL_APPEALREVIEW *ae = work;
	AWAZA_PERSONAL *my_personal;
	enum{
		AR_INIT,
		AR_AP_INIT,
		AR_AP_MAIN,
		AR_AP_WAIT,
		AR_AP_END,
	};
	
	my_personal = &ae->aap.wazapara.personal[ae->breeder_no];
	switch(ae->seq){
	case AR_INIT:
	#if 0
		OS_TPrintf("�u���[�_�[�ԍ�=%d\n", ae->breeder_no);
		OS_TPrintf("��{AP=%d\n������R���̐�=%d\n�{���e�[�W����=%d\n�ŏIAP�l=%d\n\n", 
			ae->aap.waza_personal.base_app, ae->aap.waza_personal.judge_suffer, 
			ae->aap.waza_personal.voltage_after[ae->aap.waza_personal.judge_no] 
			- ae->aap.waza_personal.voltage_before[ae->aap.waza_personal.judge_no], 
			ae->aap.waza_personal.app_total);
	#endif
		OS_TPrintf("\n��������M�f�[�^�F��{�l������(�u���[�_�[No%d, wazano=%d, apno=%d)\n",
			ae->breeder_no, my_personal->wazano, my_personal->apno);
		OS_TPrintf("app_total_before=%d\napp_total=%d\nmsg_apno=%d\n", 
			my_personal->app_total_before, my_personal->app_total, my_personal->msg_apno);
		
		ae->point = my_personal->app_total_before;
		ae->seq++;
		break;
	
	case AR_AP_INIT:
		ae->seq++;
		break;
	case AR_AP_MAIN:		//�A�s�[���|�C���g
		if(ae->point < my_personal->app_total){
			ae->point += APPEAL_ICON_ONE_POINT;
			AT_AppealPointActorMadeOver(&ae->apw->sys, ae->breeder_no, ae->breeder_pos, ae->point);
			ae->seq++;
		}
		else{
			ae->seq = AR_AP_END;
		}
		break;
	case AR_AP_WAIT:
		ae->wait++;
		if(ae->wait > APPEAL_ICON_LIGHT_WAIT){
			ae->wait = 0;
			ae->seq--;
		}
		break;
	
	case AR_AP_END:
	default:
		CO_ANSWER_TransmitBufferSet(&ae->apw->cow, &ae->req_head, NULL, 0);

		sys_FreeMemoryEz(ae);
		TCB_Delete(tcb);
		return;
	}
}

//==============================================================================
//	
//==============================================================================
//--------------------------------------------------------------
/**
 * @brief   ���ߑ��M(���M��)�F�Z�̌��ʂ��s��(���o)
 *
 * @param   apw			���Z�͕���Ǘ����[�N�ւ̃|�C���^
 * @param   work		�C�ӂ̃|�C���^
 *
 * @retval  �o�^���ꂽ���N�G�X�g�r�b�g�ԍ�
 */
//--------------------------------------------------------------
static int Request_AppealKouka(CONTEST_ORDER_WORK *cow, void *syswork, int order_no, void *work)
{
	ACTIN_PROC_WORK *apw = syswork;
	int bit_no;
	
	bit_no = CO_REQUEST_TransmitBufferSet(&apw->cow, CSELECT_ALL, order_no, 
		work, sizeof(ACTIN_ADVANCE_PARAM));
	return bit_no;
}

//--------------------------------------------------------------
/**
 * @brief   ���ߎ�M(���M��)�F�Z�̌��ʂ��s��(���o)
 *
 * @param   apw			���Z�͕���Ǘ����[�N�ւ̃|�C���^
 * @param   req_head	���N�G�X�g�w�b�_�̃|�C���^
 * @param   data		��M�f�[�^�ւ̃|�C���^
 */
//--------------------------------------------------------------
static void Recieve_AppealKouka(CONTEST_ORDER_WORK *cow, void *syswork, const CORDER_HEAD *req_head, void *data)
{
	ACTIN_PROC_WORK *apw = syswork;
	AOLOCAL_APPEALREVIEW *ae;
	ACTIN_ADVANCE_PARAM *aap = data;
	
	ae = sys_AllocMemory(HEAPID_ACTIN, sizeof(AOLOCAL_APPEALREVIEW));
	MI_CpuClear8(ae, sizeof(AOLOCAL_APPEALREVIEW));
	
	ae->apw = apw;
	ae->req_head = *req_head;
	ae->breeder_no = aap->now_breeder;
	ae->breeder_pos = aap->now_pos;
	//ae->judge_no = aap->judge_no;
	ae->aap = *aap;

	TCB_Add(AOTCB_AppealKouka, ae, TCBPRI_ACTIN_ORDERSUB);
}

//--------------------------------------------------------------
/**
 * @brief   �Z���ʎ��s
 *
 * @param   tcb			TCB�ւ̃|�C���^
 * @param   work		AOLOCAL_WAZAEFF�\����
 */
//--------------------------------------------------------------
static void AOTCB_AppealKouka(TCB_PTR tcb, void *work)
{
	AOLOCAL_APPEALREVIEW *ae = work;
	AWAZA_PERSONAL *my_personal;
	enum{
		AR_INIT,
		AR_MSG_INIT,
		AR_MSG_WAIT,
		AR_MSG_END,
		AR_AP_INIT,
		AR_AP_MAIN,
		AR_AP_WAIT,
		AR_AP_END,
		AR_VOLALLDOWN_INIT,
		AR_VOLALLDOWN_MAIN,
		AR_VOLALLDOWN_WAIT,
		AR_VOLALLDOWN_END,
		AR_SORT_INIT,
		AR_SORT_MAIN,
		AR_SORT_WAIT,
		AR_SORT_END,
		AR_END,
	};
	
	my_personal = &ae->aap.wazapara.personal[ae->breeder_no];
	switch(ae->seq){
	case AR_INIT:
		OS_TPrintf("��������M�f�[�^�F���ʁ�����(�u���[�_�[No%d, wazano=%d, apno=%d)\n",
			ae->breeder_no, my_personal->wazano, my_personal->apno);
		OS_TPrintf("app_total_before=%d\napp_total=%d\nmsg_apno=%d\n", 
			my_personal->app_total_before, my_personal->app_total, my_personal->msg_apno);
		
		ae->point = my_personal->app_total_before;
		ae->seq++;
		break;
	
	case AR_MSG_INIT:
		if(my_personal->msg_apno != 0){
			AT_WazaKoukaTalkMessageSet(ae->apw, my_personal->msg_apno, my_personal->msg_type, 
				&my_personal->tagpara, NULL);
			ae->seq++;
		}
		else{
			ae->seq = AR_MSG_END;
		}
		break;
	case AR_MSG_WAIT:
		if(AT_TalkMessageEndCheck(ae->apw) == 0){
			ae->seq++;
		}
		break;
	case AR_MSG_END:
		ae->seq++;
//		break;
	
	case AR_AP_INIT:
		ae->seq++;
//		break;
	case AR_AP_MAIN:		//�A�s�[���|�C���g
		if(ae->point < my_personal->app_total){
			ae->point += APPEAL_ICON_ONE_POINT;
			AT_AppealPointActorMadeOver(&ae->apw->sys, ae->breeder_no, ae->breeder_pos, ae->point);
			ae->seq++;
		}
		else{
			ae->seq = AR_AP_END;
		}
		break;
	case AR_AP_WAIT:
		ae->wait++;
		if(ae->wait > APPEAL_ICON_LIGHT_WAIT){
			ae->wait = 0;
			ae->seq--;
		}
		break;
	case AR_AP_END:
		ae->seq++;
//		break;
	
	case AR_VOLALLDOWN_INIT:
		if(my_personal->voltage_all_down == 1){
			ae->voltage = ae->aap.wazapara.voltage_before[my_personal->judge_no];
			ae->work = 0;
			ae->seq++;
		}
		else{
			ae->seq = AR_VOLALLDOWN_END;
		}
		break;
	case AR_VOLALLDOWN_MAIN:		//�{���e�[�W�|�C���g
		{
			int down_num = 0, voltage, judge_no;
			
			ae->work++;
			for(judge_no = 0; judge_no < JUDGE_MAX; judge_no++){
				voltage = ae->aap.wazapara.voltage_before[judge_no] - ae->work * VOLTAGE_ONE_POINT;
				if(ae->aap.wazapara.voltage_after[judge_no] <= voltage){
					down_num++;
					AT_VoltagePointActorMadeOver(&ae->apw->sys, judge_no, voltage);
					Snd_SePlay(ASE_VOLTAGE_DOWN);
				}
			}
			if(down_num > 0){
				ae->seq++;
			}
			else{
				ae->seq = AR_VOLALLDOWN_END;
			}
		}
		break;
	case AR_VOLALLDOWN_WAIT:
		ae->wait++;
		if(ae->wait > VOLTAGE_ICON_LIGHT_WAIT){
			ae->wait = 0;
			ae->seq--;
		}
		break;
	case AR_VOLALLDOWN_END:
		ae->seq++;
//		break;

	case AR_SORT_INIT:
		ae->seq++;
//		break;
	case AR_SORT_MAIN:
		{
			int i, breeder_no;
			
			for(i = 0; i < BREEDER_MAX; i++){
				breeder_no = ae->apw->a_game.breeder_sort[i];
				if(ae->aap.wazapara.personal[breeder_no].next_sort 
						!= ae->aap.wazapara.personal[breeder_no].before_next_sort
						|| ae->aap.wazapara.personal[breeder_no].next_pos
						!= ae->aap.wazapara.personal[breeder_no].before_next_pos){
					AT_NextIconActorAnimeSet(&ae->apw->sys, i, 
						ae->aap.wazapara.personal[breeder_no].next_pos);
					Snd_SePlay(ASE_NEXTICON);
				}
			}
		}
		ae->seq++;
//		break;
	case AR_SORT_WAIT:
		ae->seq++;
//		break;
	case AR_SORT_END:
		ae->seq++;
//		break;
	
	case AR_END:
	default:
		CO_ANSWER_TransmitBufferSet(&ae->apw->cow, &ae->req_head, NULL, 0);

		sys_FreeMemoryEz(ae);
		TCB_Delete(tcb);
		return;
	}
}

//==============================================================================
//	
//==============================================================================
//--------------------------------------------------------------
/**
 * @brief   ���ߑ��M(���M��)�F����Z�̌��ʂ��s��(���o)
 *
 * @param   apw			���Z�͕���Ǘ����[�N�ւ̃|�C���^
 * @param   work		�C�ӂ̃|�C���^
 *
 * @retval  �o�^���ꂽ���N�G�X�g�r�b�g�ԍ�
 */
//--------------------------------------------------------------
static int Request_AppealSpecialKouka(CONTEST_ORDER_WORK *cow, void *syswork, int order_no, void *work)
{
	ACTIN_PROC_WORK *apw = syswork;
	int bit_no;
	
	bit_no = CO_REQUEST_TransmitBufferSet(&apw->cow, CSELECT_ALL, order_no, 
		work, sizeof(ACTIN_ADVANCE_PARAM));
	return bit_no;
}

//--------------------------------------------------------------
/**
 * @brief   ���ߎ�M(���M��)�F����Z�̌��ʂ��s��(���o)
 *
 * @param   apw			���Z�͕���Ǘ����[�N�ւ̃|�C���^
 * @param   req_head	���N�G�X�g�w�b�_�̃|�C���^
 * @param   data		��M�f�[�^�ւ̃|�C���^
 */
//--------------------------------------------------------------
static void Recieve_AppealSpecialKouka(CONTEST_ORDER_WORK *cow, void *syswork, const CORDER_HEAD *req_head, void *data)
{
	ACTIN_PROC_WORK *apw = syswork;
	AOLOCAL_APPEALREVIEW *ae;
	ACTIN_ADVANCE_PARAM *aap = data;
	
	ae = sys_AllocMemory(HEAPID_ACTIN, sizeof(AOLOCAL_APPEALREVIEW));
	MI_CpuClear8(ae, sizeof(AOLOCAL_APPEALREVIEW));
	
	ae->apw = apw;
	ae->req_head = *req_head;
	ae->breeder_no = aap->now_breeder;
	ae->breeder_pos = aap->now_pos;
	//ae->judge_no = aap->judge_no;
	ae->aap = *aap;

	TCB_Add(AOTCB_AppealSpecialKouka, ae, TCBPRI_ACTIN_ORDERSUB);
}

//--------------------------------------------------------------
/**
 * @brief   ����Z���ʎ��s
 *
 * @param   tcb			TCB�ւ̃|�C���^
 * @param   work		AOLOCAL_WAZAEFF�\����
 */
//--------------------------------------------------------------
static void AOTCB_AppealSpecialKouka(TCB_PTR tcb, void *work)
{
	AOLOCAL_APPEALREVIEW *ae = work;
	AWAZA_PERSONAL *my_personal;
	enum{
		AR_INIT,
		AR_MSG_INIT,
		AR_MSG_WAIT,
		AR_MSG_END,
		AR_AP_INIT,
		AR_AP_MAIN,
		AR_AP_WAIT,
		AR_AP_END,
		AR_END,
	};
	
	my_personal = &ae->aap.wazapara.personal[ae->breeder_no];
	switch(ae->seq){
	case AR_INIT:
		OS_TPrintf("��������M�f�[�^�F������ʁ�����(�u���[�_�[No%d, wazano=%d, apno=%d)\n",
			ae->breeder_no, my_personal->wazano, my_personal->apno);
		OS_TPrintf("app_total_before=%d\napp_total=%d\nmsg_apno=%d\n", 
			my_personal->app_total_before, my_personal->app_total, my_personal->msg_apno);
		
		ae->point = my_personal->app_total_before;
		ae->seq++;
		break;
	
	case AR_MSG_INIT:
		if(my_personal->msg_apno != 0){
			AT_WazaKoukaTalkMessageSet(ae->apw, my_personal->msg_apno, my_personal->msg_type, 
				&my_personal->tagpara, NULL);
			ae->seq++;
		}
		else{
			ae->seq = AR_MSG_END;
		}
		break;
	case AR_MSG_WAIT:
		if(AT_TalkMessageEndCheck(ae->apw) == 0){
			ae->seq++;
		}
		break;
	case AR_MSG_END:
		ae->seq++;
//		break;
	
	case AR_AP_INIT:
		ae->seq++;
//		break;
	case AR_AP_MAIN:		//�A�s�[���|�C���g
		if(ae->point < my_personal->app_total){
			ae->point += APPEAL_ICON_ONE_POINT;
			AT_AppealPointActorMadeOver(&ae->apw->sys, ae->breeder_no, ae->breeder_pos, ae->point);
			ae->seq++;
		}
		else{
			ae->seq = AR_AP_END;
		}
		break;
	case AR_AP_WAIT:
		ae->wait++;
		if(ae->wait > APPEAL_ICON_LIGHT_WAIT){
			ae->wait = 0;
			ae->seq--;
		}
		break;
	case AR_AP_END:
		ae->seq++;
//		break;
	
	case AR_END:
	default:
		CO_ANSWER_TransmitBufferSet(&ae->apw->cow, &ae->req_head, NULL, 0);

		sys_FreeMemoryEz(ae);
		TCB_Delete(tcb);
		return;
	}
}

//==============================================================================
//	
//==============================================================================
//--------------------------------------------------------------
/**
 * @brief   ���ߑ��M(���M��)�F�{���e�[�W���s��(���o)
 *
 * @param   apw			���Z�͕���Ǘ����[�N�ւ̃|�C���^
 * @param   work		�C�ӂ̃|�C���^
 *
 * @retval  �o�^���ꂽ���N�G�X�g�r�b�g�ԍ�
 */
//--------------------------------------------------------------
static int Request_AppealVoltage(CONTEST_ORDER_WORK *cow, void *syswork, int order_no, void *work)
{
	ACTIN_PROC_WORK *apw = syswork;
	int bit_no;
	
	bit_no = CO_REQUEST_TransmitBufferSet(&apw->cow, CSELECT_ALL, order_no, 
		work, sizeof(ACTIN_ADVANCE_PARAM));
	return bit_no;
}

//--------------------------------------------------------------
/**
 * @brief   ���ߎ�M(���M��)�F�{���e�[�W���s��(���o)
 *
 * @param   apw			���Z�͕���Ǘ����[�N�ւ̃|�C���^
 * @param   req_head	���N�G�X�g�w�b�_�̃|�C���^
 * @param   data		��M�f�[�^�ւ̃|�C���^
 */
//--------------------------------------------------------------
static void Recieve_AppealVoltage(CONTEST_ORDER_WORK *cow, void *syswork, const CORDER_HEAD *req_head, void *data)
{
	ACTIN_PROC_WORK *apw = syswork;
	AOLOCAL_APPEALREVIEW *ae;
	ACTIN_ADVANCE_PARAM *aap = data;
	
	ae = sys_AllocMemory(HEAPID_ACTIN, sizeof(AOLOCAL_APPEALREVIEW));
	MI_CpuClear8(ae, sizeof(AOLOCAL_APPEALREVIEW));
	
	ae->apw = apw;
	ae->req_head = *req_head;
	ae->breeder_no = aap->now_breeder;
	ae->breeder_pos = aap->now_pos;
	//ae->judge_no = aap->judge_no;
	ae->aap = *aap;

	TCB_Add(AOTCB_AppealVoltage, ae, TCBPRI_ACTIN_ORDERSUB);
}

//--------------------------------------------------------------
/**
 * @brief   �{���e�[�W���s
 *
 * @param   tcb			TCB�ւ̃|�C���^
 * @param   work		AOLOCAL_WAZAEFF�\����
 */
//--------------------------------------------------------------
static void AOTCB_AppealVoltage(TCB_PTR tcb, void *work)
{
	AOLOCAL_APPEALREVIEW *ae = work;
	AWAZA_PERSONAL *my_personal;
	enum{
		AR_INIT,
		AR_JUDGE_REACTION_INIT,
		AR_JUDGE_REACTION_WAIT,
		AR_JUDGE_REACTION_END,
		AR_MSG_INIT,
		AR_MSG_WAIT,
		AR_MSG_END,
		AR_AUDIENCE_INIT,
		AR_AUDIENCE_WAIT,
		AR_AUDIENCE_END,
		AR_VOL_INIT,
		AR_VOL_MAIN,
		AR_VOL_MOVEEFF_WAIT,
		AR_VOL_WAIT,
		AR_VOL_END,
		AR_AFTER_MSG_INIT,
		AR_AFTER_MSG_WAIT,
		AR_AFTER_MSG_END,
		AR_VOLMAX_EFF_INIT,
		AR_VOLMAX_EFF_WAIT,
		AR_VOLMAX_EFF_END,
		AR_AP_INIT,
		AR_AP_MAIN,
		AR_AP_WAIT,
		AR_AP_END,
		AR_END,
	};
	
	my_personal = &ae->aap.wazapara.personal[ae->breeder_no];
	switch(ae->seq){
	case AR_INIT:
		OS_TPrintf("��������M�f�[�^�F�{���e�[�W������(�u���[�_�[No%d, wazano=%d, apno=%d)\n",
			ae->breeder_no, my_personal->wazano, my_personal->apno);
		OS_TPrintf("votage_before=%d\nvoltage_after=%d\na_talk_id=%d\nafter_a_talk_id=%d\n", 
			ae->aap.wazapara.voltage_before[my_personal->judge_no], 
			ae->aap.wazapara.voltage_after[my_personal->judge_no], 
			ae->aap.nt.a_talk_id, ae->aap.nt.after_a_talk_id);
		
		ae->voltage = ae->aap.wazapara.voltage_before[my_personal->judge_no];
		ae->seq++;
		break;
	
	case AR_JUDGE_REACTION_INIT:
		if(ae->aap.wazapara.voltage_after[my_personal->judge_no] >
				ae->aap.wazapara.voltage_before[my_personal->judge_no]){
			int reaction_type;
			
			if(ae->aap.wazapara.voltage_after[my_personal->judge_no] >= VOLTAGE_POINT_FULL){
				reaction_type = JUDGE_REACTION_ICON_VOLTAGE_MAX;
			}
			else{
				reaction_type = JUDGE_REACTION_ICON_VOLTAGE;
			}
			AT_JudgeReactionIconON(&ae->apw->sys, my_personal->judge_no, reaction_type);
			AT_JudgeReactionMoveTaskSet(ae->apw, my_personal->judge_no, reaction_type, 
				&ae->reaction_end);
			ae->seq++;
		}
		else{
			ae->seq = AR_JUDGE_REACTION_END;
		}
		break;
	case AR_JUDGE_REACTION_WAIT:
		if(ae->reaction_end == TRUE){
			ae->seq++;
		}
		break;
	case AR_JUDGE_REACTION_END:
		ae->seq++;
//		break;
		
	case AR_MSG_INIT:
		if(ae->aap.nt.a_talk_id != A_TALK_NULL){
			AT_A_TalkMessageSet(ae->apw, ae->aap.nt.a_talk_id, &ae->aap.nt.a_talk_tagpara, NULL);
			ae->seq++;
		}
		else{
			ae->seq = AR_MSG_END;
		}
		break;
	case AR_MSG_WAIT:
		if(AT_TalkMessageEndCheck(ae->apw) == 0){
			ae->seq++;
		}
		break;
	case AR_MSG_END:
		ae->seq++;
//		break;
	
	case AR_AUDIENCE_INIT:	//�ϋq�A�j���Z�b�g
		if(ae->aap.wazapara.voltage_after[my_personal->judge_no] >
				ae->aap.wazapara.voltage_before[my_personal->judge_no]){
			AT_AudienceAnimeSet(ae->apw, ae->aap.wazapara.voltage_after[my_personal->judge_no], 
				AUDIENCE_ANM_START_WAIT, ACTIN_AUDIENCE_VOLUME, TRUE, &ae->audience_anm_end);
		}
		else{
			ae->audience_anm_end = TRUE;
		}
		ae->seq++;
		break;
	case AR_AUDIENCE_WAIT:
		ae->wait++;
		if(ae->wait > AUDIENCE_ANM_NEXT_WAIT){
			ae->wait = 0;
			ae->seq++;
		}
		break;
	case AR_AUDIENCE_END:
		ae->seq++;
//		break;

	case AR_VOL_INIT:
		ae->seq++;
//		break;
	case AR_VOL_MAIN:		//�{���e�[�W�|�C���g
		if(ae->voltage != ae->aap.wazapara.voltage_after[my_personal->judge_no]){
			if(ae->aap.wazapara.voltage_after[my_personal->judge_no] 
					- ae->aap.wazapara.voltage_before[my_personal->judge_no] > 0){
				ae->voltage += VOLTAGE_ONE_POINT;
				AT_VoltagePointActorMadeOver(&ae->apw->sys, my_personal->judge_no, ae->voltage);
//				Snd_SePlay(ASE_VOLTAGE_UP);
			}
			else{
				ae->voltage -= VOLTAGE_ONE_POINT;
				AT_VoltagePointActorMadeOver(&ae->apw->sys, my_personal->judge_no, ae->voltage);
				Snd_SePlay(ASE_VOLTAGE_DOWN);
			}
			ae->seq++;
		}
		else{
			ae->seq = AR_VOL_END;
		}
		break;
	case AR_VOL_MOVEEFF_WAIT:
		if(AT_VoltageMoveEffectEndCheck(&ae->apw->sys, my_personal->judge_no) == TRUE){
			ae->seq++;
		}
		break;
	case AR_VOL_WAIT:
		ae->wait++;
		if(ae->wait > VOLTAGE_ICON_LIGHT_WAIT){
			ae->wait = 0;
			ae->seq = AR_VOL_MAIN;
		}
		break;
	case AR_VOL_END:
		if(ae->voltage >= VOLTAGE_POINT_FULL){
			ae->vaw = AT_VoltageAnimeSet(ae->apw, my_personal->judge_no);
		}
		ae->seq++;
		break;

	case AR_AFTER_MSG_INIT:
		if(ae->aap.nt.after_a_talk_id != A_TALK_NULL){
			AT_A_TalkMessageSet(ae->apw, ae->aap.nt.after_a_talk_id, 
				&ae->aap.nt.after_a_talk_tagpara, NULL);
			ae->seq++;
		}
		else{
			ae->seq = AR_AFTER_MSG_END;
		}
		break;
	case AR_AFTER_MSG_WAIT:
		if(AT_TalkMessageEndCheck(ae->apw) == 0){
			ae->seq++;
		}
		break;
	case AR_AFTER_MSG_END:
		ae->seq++;
//		break;

	case AR_VOLMAX_EFF_INIT:
		if(ae->voltage >= VOLTAGE_POINT_FULL){
			AT_VoltageMovePanel(ae->apw, ae->breeder_no, ae->breeder_pos, my_personal->judge_no, 
				&ae->effect_count);
			ae->seq++;
		}
		else{
			ae->seq = AR_VOLMAX_EFF_END;
		}
		break;
	case AR_VOLMAX_EFF_WAIT:
		if(ae->effect_count == 0){
			ae->seq++;
		}
		break;
	case AR_VOLMAX_EFF_END:
		ae->seq++;
//		break;
	
	case AR_AP_INIT:
		ae->point = my_personal->app_total_before;
		ae->seq++;
		break;
	case AR_AP_MAIN:		//�A�s�[���|�C���g
		if(ae->point < my_personal->app_total){
			ae->point += APPEAL_ICON_ONE_POINT;
			AT_AppealPointActorMadeOver(&ae->apw->sys, ae->breeder_no, ae->breeder_pos, ae->point);
			ae->seq++;
		}
		else{
			AT_JudgeReactionIconOFF(&ae->apw->sys);
			ae->seq = AR_AP_END;
		}
		break;
	case AR_AP_WAIT:
		ae->wait++;
		if(ae->wait > APPEAL_ICON_LIGHT_WAIT){
			ae->wait = 0;
			ae->seq--;
		}
		break;
	case AR_AP_END:
		if(ae->voltage >= VOLTAGE_POINT_FULL){	//�{���e�[�WMAX�Ȃ�\���N���A
			AT_VoltageAnimeDel(ae->vaw);
			AT_VoltagePointActorMadeOver(&ae->apw->sys, my_personal->judge_no, 0);
		}
		ae->seq++;
		break;

	case AR_END:
	default:
		if(ae->audience_anm_end == TRUE){
			CO_ANSWER_TransmitBufferSet(&ae->apw->cow, &ae->req_head, NULL, 0);

			sys_FreeMemoryEz(ae);
			TCB_Delete(tcb);
			return;
		}
		break;
	}
}

//==============================================================================
//	
//==============================================================================
//--------------------------------------------------------------
/**
 * @brief   ���ߑ��M(���M��)�F�S���A�s�[����̋Z���ʂ��s��(���o)
 *
 * @param   apw			���Z�͕���Ǘ����[�N�ւ̃|�C���^
 * @param   work		�C�ӂ̃|�C���^
 *
 * @retval  �o�^���ꂽ���N�G�X�g�r�b�g�ԍ�
 */
//--------------------------------------------------------------
static int Request_ReviewAfterKouka(CONTEST_ORDER_WORK *cow, void *syswork, int order_no, void *work)
{
	ACTIN_PROC_WORK *apw = syswork;
	int bit_no;
	
	bit_no = CO_REQUEST_TransmitBufferSet(&apw->cow, CSELECT_ALL, order_no, 
		work, sizeof(ACTIN_ADVANCE_PARAM));
	return bit_no;
}

//--------------------------------------------------------------
/**
 * @brief   ���ߎ�M(���M��)�F�S���A�s�[����̋Z���ʂ��s��(���o)
 *
 * @param   apw			���Z�͕���Ǘ����[�N�ւ̃|�C���^
 * @param   req_head	���N�G�X�g�w�b�_�̃|�C���^
 * @param   data		��M�f�[�^�ւ̃|�C���^
 */
//--------------------------------------------------------------
static void Recieve_ReviewAfterKouka(CONTEST_ORDER_WORK *cow, void *syswork, const CORDER_HEAD *req_head, void *data)
{
	ACTIN_PROC_WORK *apw = syswork;
	AOLOCAL_APPEALREVIEW *ae;
	ACTIN_ADVANCE_PARAM *aap = data;
	
	ae = sys_AllocMemory(HEAPID_ACTIN, sizeof(AOLOCAL_APPEALREVIEW));
	MI_CpuClear8(ae, sizeof(AOLOCAL_APPEALREVIEW));
	
	ae->apw = apw;
	ae->req_head = *req_head;
	ae->breeder_no = aap->now_breeder;
	ae->breeder_pos = aap->now_pos;
	//ae->judge_no = aap->judge_no;
	ae->aap = *aap;

	TCB_Add(AOTCB_ReviewAfterKouka, ae, TCBPRI_ACTIN_ORDERSUB);
}

//--------------------------------------------------------------
/**
 * @brief   �S���A�s�[����̋Z���ʎ��s
 *
 * @param   tcb			TCB�ւ̃|�C���^
 * @param   work		AOLOCAL_WAZAEFF�\����
 */
//--------------------------------------------------------------
static void AOTCB_ReviewAfterKouka(TCB_PTR tcb, void *work)
{
	AOLOCAL_APPEALREVIEW *ae = work;
	AWAZA_PERSONAL *my_personal;
	enum{
		AR_INIT,
		AR_MSG_INIT,
		AR_MSG_WAIT,
		AR_MSG_END,
		AR_AP_INIT,
		AR_AP_MAIN,
		AR_AP_WAIT,
		AR_AP_END,
		AR_END,
	};
	
	my_personal = &ae->aap.wazapara.personal[ae->breeder_no];
	switch(ae->seq){
	case AR_INIT:
		OS_TPrintf("��������M�f�[�^�F�S���A�s�[����̋Z���ʁ�����(�u���[�_�[No%d, wazano=%d, apno=%d)\n",
			ae->breeder_no, my_personal->wazano, my_personal->apno);
		OS_TPrintf("app_total_before=%d\napp_total=%d\nmsg_apno=%d\n", 
			my_personal->app_total_before, my_personal->app_total, my_personal->msg_apno);
		
		ae->point = my_personal->app_total_before;
		ae->seq++;
		break;
	
	case AR_MSG_INIT:
		if(my_personal->msg_apno != 0){
			AT_WazaKoukaTalkMessageSet(ae->apw, my_personal->msg_apno, my_personal->msg_type, 
				&my_personal->tagpara, NULL);
			ae->seq++;
		}
		else{
			ae->seq = AR_MSG_END;
		}
		break;
	case AR_MSG_WAIT:
		if(AT_TalkMessageEndCheck(ae->apw) == 0){
			ae->seq++;
		}
		break;
	case AR_MSG_END:
		ae->seq++;
//		break;
	
	case AR_AP_INIT:
		ae->seq++;
//		break;
	case AR_AP_MAIN:		//�A�s�[���|�C���g
		if(ae->point < my_personal->app_total){
			ae->point += APPEAL_ICON_ONE_POINT;
			AT_AppealPointActorMadeOver(&ae->apw->sys, ae->breeder_no, ae->breeder_pos, ae->point);
		}
		else{
			ae->seq = AR_AP_END;
		}
		ae->seq++;
		break;
	case AR_AP_WAIT:
		ae->wait++;
		if(ae->wait > APPEAL_ICON_LIGHT_WAIT){
			ae->wait = 0;
			ae->seq--;
		}
		break;
	case AR_AP_END:
		ae->seq++;
//		break;
	
	case AR_END:
	default:
		CO_ANSWER_TransmitBufferSet(&ae->apw->cow, &ae->req_head, NULL, 0);

		sys_FreeMemoryEz(ae);
		TCB_Delete(tcb);
		return;
	}
}

//==============================================================================
//	
//==============================================================================
//--------------------------------------------------------------
/**
 * @brief   ���ߑ��M(���M��)�F�R�������s��(���o)
 *
 * @param   apw			���Z�͕���Ǘ����[�N�ւ̃|�C���^
 * @param   work		�C�ӂ̃|�C���^
 *
 * @retval  �o�^���ꂽ���N�G�X�g�r�b�g�ԍ�
 */
//--------------------------------------------------------------
static int Request_JudgeSuffer(CONTEST_ORDER_WORK *cow, void *syswork, int order_no, void *work)
{
	ACTIN_PROC_WORK *apw = syswork;
	int bit_no;
	
	bit_no = CO_REQUEST_TransmitBufferSet(&apw->cow, CSELECT_ALL, order_no, 
		work, sizeof(ACTIN_ADVANCE_PARAM));
	return bit_no;
}

//--------------------------------------------------------------
/**
 * @brief   ���ߎ�M(���M��)�F�R�������s��(���o)
 *
 * @param   apw			���Z�͕���Ǘ����[�N�ւ̃|�C���^
 * @param   req_head	���N�G�X�g�w�b�_�̃|�C���^
 * @param   data		��M�f�[�^�ւ̃|�C���^
 */
//--------------------------------------------------------------
static void Recieve_JudgeSuffer(CONTEST_ORDER_WORK *cow, void *syswork, const CORDER_HEAD *req_head, void *data)
{
	ACTIN_PROC_WORK *apw = syswork;
	AOLOCAL_JUDGESUFFER *aj;
	ACTIN_ADVANCE_PARAM *aap = data;
	
	aj = sys_AllocMemory(HEAPID_ACTIN, sizeof(AOLOCAL_JUDGESUFFER));
	MI_CpuClear8(aj, sizeof(AOLOCAL_JUDGESUFFER));
	
	aj->apw = apw;
	aj->req_head = *req_head;
//	aj->breeder_no = aap->now_breeder;
//	aj->breeder_pos = aap->now_pos;
	//aj->judge_no = aap->judge_no;
	aj->aap = *aap;

	TCB_Add(AOTCB_JudgeSuffer, aj, TCBPRI_ACTIN_ORDERSUB);
}

//--------------------------------------------------------------
/**
 * @brief   �R�������s
 *
 * @param   tcb			TCB�ւ̃|�C���^
 * @param   work		AOLOCAL_WAZAEFF�\����
 */
//--------------------------------------------------------------
static void AOTCB_JudgeSuffer(TCB_PTR tcb, void *work)
{
	AOLOCAL_JUDGESUFFER *aj = work;
	AWAZA_PERSONAL *my_personal;
	int now_breeder, now_pos, i;
	enum{
		AR_INIT,
		AR_JUDGE_REACTION_INIT,
		AR_JUDGE_REACTION_WAIT,
		AR_JUDGE_REACTION_END,
		AR_MSG_INIT,
		AR_MSG_WAIT,
		AR_MSG_END,
		AR_A_TALK_INIT,
		AR_A_TALK_WAIT,
		AR_A_TALK_END,
		AR_AFTER_A_TALK_INIT,
		AR_AFTER_A_TALK_WAIT,
		AR_AFTER_A_TALK_END,
		AR_AP_INIT,
		AR_AP_MAIN,
		AR_AP_WAIT,
		AR_AP_END,
		AR_END,
	};
	
//	my_personal = &aj->aap.wazapara.personal[aj->breeder_no];
	now_breeder = aj->aap.jsr.suffer_breeder[aj->count];
	now_pos = 0;
	if(now_breeder != BREEDER_MAX){
		my_personal = &aj->aap.wazapara.personal[now_breeder];
		for(i = 0; i < BREEDER_MAX; i++){
			if(aj->apw->a_game.breeder_sort[i] == now_breeder){
				now_pos = i;
				break;
			}
		}
	}
	else{
		my_personal = NULL;
	}
	
	switch(aj->seq){
	case AR_INIT:
		aj->point = my_personal->app_total_before;
		aj->seq++;
//		break;
	
	case AR_JUDGE_REACTION_INIT:
		{
			int reaction_type;
			
			if(my_personal->judge_suffer == 0){
				reaction_type = JUDGE_REACTION_ICON_SUFFER_BIG;
				Snd_SePlay(ASE_JUDGE_SUFFER_BIG);
			}
			else if(my_personal->judge_suffer == 1){
				reaction_type = JUDGE_REACTION_ICON_SUFFER_MIDDLE;
				Snd_SePlay(ASE_JUDGE_SUFFER_MIDDLE);
			}
			else if(my_personal->judge_suffer == 2){
				reaction_type = JUDGE_REACTION_ICON_SUFFER_SMALL;
				Snd_SePlay(ASE_JUDGE_SUFFER_SMALL);
			}
			else{
				aj->seq = AR_JUDGE_REACTION_END;
				Snd_SePlay(ASE_JUDGE_SUFFER_FAILED);
				break;
			}
			AT_JudgeReactionMoveTaskSet(aj->apw, my_personal->judge_no, reaction_type, 
				&aj->reaction_end);
		}
		aj->seq++;
		break;
	case AR_JUDGE_REACTION_WAIT:
		if(aj->reaction_end == TRUE){
			aj->seq++;
		}
		break;
	case AR_JUDGE_REACTION_END:
		aj->seq++;
//		break;
		
	case AR_MSG_INIT:
		if(my_personal->msg_apno != 0){
			AT_WazaKoukaTalkMessageSet(aj->apw, my_personal->msg_apno, my_personal->msg_type, 
				&my_personal->tagpara, NULL);
			aj->seq++;
		}
		else{
			aj->seq = AR_MSG_END;
		}
		break;
	case AR_MSG_WAIT:
		if(AT_TalkMessageEndCheck(aj->apw) == 0){
			aj->seq++;
		}
		break;
	case AR_MSG_END:
		aj->seq++;
//		break;
	
	case AR_A_TALK_INIT:
		if(aj->aap.nt.a_talk_id != A_TALK_NULL){
			AT_A_TalkMessageSet(aj->apw, aj->aap.nt.a_talk_id, &aj->aap.nt.a_talk_tagpara, 
				&aj->aap.jsr);
			aj->seq++;
		}
		else{
			aj->seq = AR_A_TALK_END;
		}
		break;
	case AR_A_TALK_WAIT:
		if(AT_TalkMessageEndCheck(aj->apw) == 0){
			aj->seq++;
		}
		break;
	case AR_A_TALK_END:
		aj->seq++;
//		break;

	case AR_AFTER_A_TALK_INIT:
		if(aj->aap.nt.after_a_talk_id != A_TALK_NULL){
			AT_A_TalkMessageSet(aj->apw, aj->aap.nt.after_a_talk_id, 
				&aj->aap.nt.after_a_talk_tagpara, NULL);
			aj->seq++;
		}
		else{
			aj->seq = AR_AFTER_A_TALK_END;
		}
		break;
	case AR_AFTER_A_TALK_WAIT:
		if(AT_TalkMessageEndCheck(aj->apw) == 0){
			aj->seq++;
		}
		break;
	case AR_AFTER_A_TALK_END:
		aj->seq++;
//		break;
	
	case AR_AP_INIT:
		aj->point = my_personal->app_total_before;
		aj->seq++;
		break;
	case AR_AP_MAIN:		//�A�s�[���|�C���g
		if(aj->point < my_personal->app_total){
			aj->point += APPEAL_ICON_ONE_POINT;
			AT_AppealPointActorMadeOver(&aj->apw->sys, now_breeder, now_pos, aj->point);
		}
		else{
			aj->seq = AR_AP_END;
			break;
		}
		aj->seq++;
		break;
	case AR_AP_WAIT:
		aj->wait++;
		if(aj->wait > APPEAL_ICON_LIGHT_WAIT){
			aj->wait = 0;
			aj->seq--;
		}
		break;
	case AR_AP_END:
		aj->count++;
		if(aj->count < BREEDER_MAX && aj->aap.jsr.suffer_breeder[aj->count] != BREEDER_MAX){
			aj->seq = AR_AP_INIT;
		}
		else{
			aj->seq++;
		}
		break;
	
	case AR_END:
	default:
		CO_ANSWER_TransmitBufferSet(&aj->apw->cow, &aj->req_head, NULL, 0);

		sys_FreeMemoryEz(aj);
		TCB_Delete(tcb);
		return;
	}
}


//==============================================================================
//	
//==============================================================================
//--------------------------------------------------------------
/**
 * @brief   ���ߑ��M(���M��)�F�R�����Z���ʂ��s��(���o)
 *
 * @param   apw			���Z�͕���Ǘ����[�N�ւ̃|�C���^
 * @param   work		�C�ӂ̃|�C���^
 *
 * @retval  �o�^���ꂽ���N�G�X�g�r�b�g�ԍ�
 */
//--------------------------------------------------------------
static int Request_JudgeWaza(CONTEST_ORDER_WORK *cow, void *syswork, int order_no, void *work)
{
	ACTIN_PROC_WORK *apw = syswork;
	int bit_no;
	
	bit_no = CO_REQUEST_TransmitBufferSet(&apw->cow, CSELECT_ALL, order_no, 
		work, sizeof(ACTIN_ADVANCE_PARAM));
	return bit_no;
}

//--------------------------------------------------------------
/**
 * @brief   ���ߎ�M(���M��)�F�R�����Z���ʂ��s��(���o)
 *
 * @param   apw			���Z�͕���Ǘ����[�N�ւ̃|�C���^
 * @param   req_head	���N�G�X�g�w�b�_�̃|�C���^
 * @param   data		��M�f�[�^�ւ̃|�C���^
 */
//--------------------------------------------------------------
static void Recieve_JudgeWaza(CONTEST_ORDER_WORK *cow, void *syswork, const CORDER_HEAD *req_head, void *data)
{
	ACTIN_PROC_WORK *apw = syswork;
	AOLOCAL_APPEALREVIEW *ae;
	ACTIN_ADVANCE_PARAM *aap = data;
	
	ae = sys_AllocMemory(HEAPID_ACTIN, sizeof(AOLOCAL_APPEALREVIEW));
	MI_CpuClear8(ae, sizeof(AOLOCAL_APPEALREVIEW));
	
	ae->apw = apw;
	ae->req_head = *req_head;
	ae->breeder_no = aap->now_breeder;
	ae->breeder_pos = aap->now_pos;
	//ae->judge_no = aap->judge_no;
	ae->aap = *aap;

	TCB_Add(AOTCB_JudgeWaza, ae, TCBPRI_ACTIN_ORDERSUB);
}

//--------------------------------------------------------------
/**
 * @brief   �R�����Z���ʎ��s
 *
 * @param   tcb			TCB�ւ̃|�C���^
 * @param   work		AOLOCAL_WAZAEFF�\����
 */
//--------------------------------------------------------------
static void AOTCB_JudgeWaza(TCB_PTR tcb, void *work)
{
	AOLOCAL_APPEALREVIEW *ae = work;
	AWAZA_PERSONAL *my_personal;
	enum{
		AR_INIT,
		AR_MSG_INIT,
		AR_MSG_WAIT,
		AR_MSG_END,
		AR_A_TALK_INIT,
		AR_A_TALK_WAIT,
		AR_A_TALK_END,
		AR_AFTER_A_TALK_INIT,
		AR_AFTER_A_TALK_WAIT,
		AR_AFTER_A_TALK_END,
		AR_AP_INIT,
		AR_AP_MAIN,
		AR_AP_WAIT,
		AR_AP_END,
		AR_END,
	};
	
	my_personal = &ae->aap.wazapara.personal[ae->breeder_no];
	switch(ae->seq){
	case AR_INIT:
		OS_TPrintf("��������M�f�[�^�F�R����聁����(�u���[�_�[No%d, wazano=%d, apno=%d)\n",
			ae->breeder_no, my_personal->wazano, my_personal->apno);
		OS_TPrintf("app_total_before=%d\napp_total=%d\nmsg_apno=%d\na_talk_id=%d\n", 
			my_personal->app_total_before, my_personal->app_total, my_personal->msg_apno,
			ae->aap.nt.a_talk_id);
		
		ae->point = my_personal->app_total_before;
		ae->seq++;
		break;
	
	case AR_MSG_INIT:
		if(my_personal->msg_apno != 0){
			AT_WazaKoukaTalkMessageSet(ae->apw, my_personal->msg_apno, my_personal->msg_type, 
				&my_personal->tagpara, NULL);
			ae->seq++;
		}
		else{
			ae->seq = AR_MSG_END;
		}
		break;
	case AR_MSG_WAIT:
		if(AT_TalkMessageEndCheck(ae->apw) == 0){
			ae->seq++;
		}
		break;
	case AR_MSG_END:
		ae->seq++;
//		break;
	
	case AR_A_TALK_INIT:
		if(ae->aap.nt.a_talk_id != A_TALK_NULL){
			AT_A_TalkMessageSet(ae->apw, ae->aap.nt.a_talk_id, &ae->aap.nt.a_talk_tagpara, NULL);
			ae->seq++;
		}
		else{
			ae->seq = AR_A_TALK_END;
		}
		break;
	case AR_A_TALK_WAIT:
		if(AT_TalkMessageEndCheck(ae->apw) == 0){
			ae->seq++;
		}
		break;
	case AR_A_TALK_END:
		ae->seq++;
//		break;

	case AR_AFTER_A_TALK_INIT:
		if(ae->aap.nt.after_a_talk_id != A_TALK_NULL){
			AT_A_TalkMessageSet(ae->apw, ae->aap.nt.after_a_talk_id, 
				&ae->aap.nt.after_a_talk_tagpara, NULL);
			ae->seq++;
		}
		else{
			ae->seq = AR_AFTER_A_TALK_END;
		}
		break;
	case AR_AFTER_A_TALK_WAIT:
		if(AT_TalkMessageEndCheck(ae->apw) == 0){
			ae->seq++;
		}
		break;
	case AR_AFTER_A_TALK_END:
		ae->seq++;
//		break;
	
	case AR_AP_INIT:
		ae->seq++;
//		break;
	case AR_AP_MAIN:		//�A�s�[���|�C���g
		if(ae->point < my_personal->app_total){
			ae->point += APPEAL_ICON_ONE_POINT;
			AT_AppealPointActorMadeOver(&ae->apw->sys, ae->breeder_no, ae->breeder_pos, ae->point);
		}
		else{
			ae->seq = AR_AP_END;
		}
		ae->seq++;
		break;
	case AR_AP_WAIT:
		ae->wait++;
		if(ae->wait > APPEAL_ICON_LIGHT_WAIT){
			ae->wait = 0;
			ae->seq--;
		}
		break;
	case AR_AP_END:
		ae->seq++;
//		break;
	
	case AR_END:
	default:
		CO_ANSWER_TransmitBufferSet(&ae->apw->cow, &ae->req_head, NULL, 0);

		sys_FreeMemoryEz(ae);
		TCB_Delete(tcb);
		return;
	}
}


//==============================================================================
//	
//==============================================================================
//--------------------------------------------------------------
/**
 * @brief   ���ߑ��M(���M��)�F�R���R�����g���s��(���o)
 *
 * @param   apw			���Z�͕���Ǘ����[�N�ւ̃|�C���^
 * @param   work		�C�ӂ̃|�C���^
 *
 * @retval  �o�^���ꂽ���N�G�X�g�r�b�g�ԍ�
 */
//--------------------------------------------------------------
static int Request_JudgeComment(CONTEST_ORDER_WORK *cow, void *syswork, int order_no, void *work)
{
	ACTIN_PROC_WORK *apw = syswork;
	int bit_no;
	
	bit_no = CO_REQUEST_TransmitBufferSet(&apw->cow, CSELECT_ALL, order_no, 
		work, sizeof(ACTIN_ADVANCE_PARAM));
	return bit_no;
}

//--------------------------------------------------------------
/**
 * @brief   ���ߎ�M(���M��)�F�R���R�����g���s��(���o)
 *
 * @param   apw			���Z�͕���Ǘ����[�N�ւ̃|�C���^
 * @param   req_head	���N�G�X�g�w�b�_�̃|�C���^
 * @param   data		��M�f�[�^�ւ̃|�C���^
 */
//--------------------------------------------------------------
static void Recieve_JudgeComment(CONTEST_ORDER_WORK *cow, void *syswork, const CORDER_HEAD *req_head, void *data)
{
	ACTIN_PROC_WORK *apw = syswork;
	AOLOCAL_APPEALREVIEW *ae;
	ACTIN_ADVANCE_PARAM *aap = data;
	
	ae = sys_AllocMemory(HEAPID_ACTIN, sizeof(AOLOCAL_APPEALREVIEW));
	MI_CpuClear8(ae, sizeof(AOLOCAL_APPEALREVIEW));
	
	ae->apw = apw;
	ae->req_head = *req_head;
	ae->breeder_no = apw->sys.c_game->my_breeder_no;//aap->now_breeder;
	ae->breeder_pos = aap->now_pos;
	//ae->judge_no = aap->judge_no;
	ae->aap = *aap;

	TCB_Add(AOTCB_JudgeComment, ae, TCBPRI_ACTIN_ORDERSUB);
}

//--------------------------------------------------------------
/**
 * @brief   �R���R�����g���s
 *
 * @param   tcb			TCB�ւ̃|�C���^
 * @param   work		AOLOCAL_WAZAEFF�\����
 */
//--------------------------------------------------------------
static void AOTCB_JudgeComment(TCB_PTR tcb, void *work)
{
	AOLOCAL_APPEALREVIEW *ae = work;
	AWAZA_PERSONAL *my_personal;
	
	my_personal = &ae->aap.wazapara.personal[ae->breeder_no];
	switch(ae->seq){
	case 0:
		{
			u32 a_talk_id;
			ATAG_PARAM tagpara;
			
			a_talk_id = AT_MsgTagJudgeCommentCreate(ae->breeder_no, 
				my_personal->app_total, &tagpara);
			AT_A_TalkMessageSet(ae->apw, a_talk_id, &tagpara, NULL);
			ae->seq++;
		}
		break;
	case 1:
		if(AT_TalkMessageEndCheck(ae->apw) == 0){
			ae->seq++;
		}
		break;
	case 2:
		ae->seq++;
		break;

	default:
		CO_ANSWER_TransmitBufferSet(&ae->apw->cow, &ae->req_head, NULL, 0);

		sys_FreeMemoryEz(ae);
		TCB_Delete(tcb);
		return;
	}
}


//==============================================================================
//	
//==============================================================================
//--------------------------------------------------------------
/**
 * @brief   ���ߑ��M(���M��)�F�^�[���I����̃G�t�F�N�g���s����
 *
 * @param   apw			���Z�͕���Ǘ����[�N�ւ̃|�C���^
 * @param   work		�C�ӂ̃|�C���^
 *
 * @retval  �o�^���ꂽ���N�G�X�g�r�b�g�ԍ�
 */
//--------------------------------------------------------------
static int Request_TurnEndEffect(CONTEST_ORDER_WORK *cow, void *syswork, int order_no, void *work)
{
	ACTIN_PROC_WORK *apw = syswork;
	int bit_no;
	
	bit_no = CO_REQUEST_TransmitBufferSet(cow, CSELECT_ALL, order_no, 
		work, sizeof(ACTIN_ADVANCE_PARAM));
	return bit_no;
}

//--------------------------------------------------------------
/**
 * @brief   ���ߎ�M(���M��)�F�^�[���I����̃G�t�F�N�g���s����
 *
 * @param   apw			���Z�͕���Ǘ����[�N�ւ̃|�C���^
 * @param   req_head	���N�G�X�g�w�b�_�̃|�C���^
 * @param   data		��M�f�[�^�ւ̃|�C���^
 */
//--------------------------------------------------------------
static void Recieve_TurnEndEffect(CONTEST_ORDER_WORK *cow, void *syswork, const CORDER_HEAD *req_head, void *data)
{
	ACTIN_PROC_WORK *apw = syswork;
	ACTIN_ADVANCE_PARAM *aap = data;
	AOLOCAL_TURNEND_EFF *tee;
	
	tee = sys_AllocMemory(HEAPID_ACTIN, sizeof(AOLOCAL_TURNEND_EFF));
	MI_CpuClear8(tee, sizeof(AOLOCAL_TURNEND_EFF));
	
	tee->apw = apw;
	tee->req_head = *req_head;
	tee->cow = cow;
	
	TCB_Add(AOTCB_TurnEndEffect, tee, TCBPRI_ACTIN_ORDERSUB);
}

//--------------------------------------------------------------
/**
 * @brief   �^�[���I����̃G�t�F�N�g���s����
 * @param   tcb			TCB�ւ̃|�C���^
 * @param   work		AOLOCAL_TURNEND_EFF�\����
 */
//--------------------------------------------------------------
static void AOTCB_TurnEndEffect(TCB_PTR tcb, void *work)
{
	AOLOCAL_TURNEND_EFF *tee = work;
	enum{
		TEESEQ_INIT,
		
		TEESEQ_APHEART_INIT,
//		TEESEQ_APHEART_WAIT,
		TEESEQ_APHEART_ALL_END_WAIT,
		
		TEESEQ_END,
	};
	int i, end_count;
	
	switch(tee->seq){
	case TEESEQ_INIT:
		AT_AudienceAnimeSet(tee->apw, 0, 0, ACTIN_AUDIENCE_VOLUME, FALSE, &tee->audience_anm_end);
		tee->seq++;
		break;
	
#if 0
	case TEESEQ_APHEART_INIT:
		AT_APHeartMovePanel(tee->apw, tee->apw->a_game.breeder_sort[tee->breeder_pos], 
			tee->breeder_pos, &tee->effect_count[tee->breeder_pos]);
		tee->seq++;
		break;
	case TEESEQ_APHEART_WAIT:
		tee->wait++;
		if(tee->wait > TEE_APHEART_NEXT_BREEDER_WAIT){
			tee->wait = 0;
			
			tee->breeder_pos++;
			if(tee->breeder_pos >= BREEDER_MAX){
				tee->seq++;
			}
			else{
				tee->seq = TEESEQ_APHEART_INIT;
			}
		}
		break;
#else
	case TEESEQ_APHEART_INIT:
		{
			int i;
			
			for(i = 0; i < BREEDER_MAX; i++){
				tee->panel_flash[i] = BreederPanel_FlashTaskSet(tee->apw, 
					tee->apw->a_game.breeder_sort[i]);
				AT_APHeartMovePanel(tee->apw, tee->apw->a_game.breeder_sort[i], 
					i, &tee->effect_count[i], tee->panel_flash[i]);
			}
		}
		tee->seq++;
		break;
#endif
	case TEESEQ_APHEART_ALL_END_WAIT:
		end_count = 0;
		for(i = 0; i < BREEDER_MAX; i++){
			if(tee->effect_count[i] == 0 
					&& BreederPanel_FlashReqCheck(tee->panel_flash[i]) == FALSE){
				end_count++;
			}
		}
		
		if(end_count == BREEDER_MAX){
			for(i = 0; i < BREEDER_MAX; i++){
				BreederPanel_FlashTaskDelete(tee->panel_flash[i]);
			}
			tee->seq++;
		}
		break;
	
	case TEESEQ_END:
	default:
		if(tee->audience_anm_end == TRUE){
			CO_ANSWER_TransmitBufferSet(tee->cow, &tee->req_head, NULL, 0);

			sys_FreeMemoryEz(tee);
			TCB_Delete(tcb);
			return;
		}
		break;
	}
}


//==============================================================================
//	
//==============================================================================
//--------------------------------------------------------------
/**
 * @brief   ���ߑ��M(���M��)�F�^�[���I����̃p�����[�^�X�V
 *
 * @param   apw			���Z�͕���Ǘ����[�N�ւ̃|�C���^
 * @param   work		�C�ӂ̃|�C���^
 *
 * @retval  �o�^���ꂽ���N�G�X�g�r�b�g�ԍ�
 */
//--------------------------------------------------------------
static int Request_TurnParamUpdate(CONTEST_ORDER_WORK *cow, void *syswork, int order_no, void *work)
{
	ACTIN_PROC_WORK *apw = syswork;
	int bit_no;
	
	bit_no = CO_REQUEST_TransmitBufferSet(&apw->cow, CSELECT_ALL, order_no, 
		work, sizeof(ACTIN_GAME_PARAM));
	OS_TPrintf("�^�[���I����̃p�����[�^�f�[�^�S���M�B�T�C�Y��%dbyte\n", sizeof(ACTIN_GAME_PARAM));
	return bit_no;
}

//--------------------------------------------------------------
/**
 * @brief   ���ߎ�M(���M��)�F�^�[���I����̃p�����[�^�X�V
 *
 * @param   apw			���Z�͕���Ǘ����[�N�ւ̃|�C���^
 * @param   req_head	���N�G�X�g�w�b�_�̃|�C���^
 * @param   data		��M�f�[�^�ւ̃|�C���^
 */
//--------------------------------------------------------------
static void Recieve_TurnParamUpdate(CONTEST_ORDER_WORK *cow, void *syswork, const CORDER_HEAD *req_head, void *data)
{
	ACTIN_PROC_WORK *apw = syswork;
	ACTIN_GAME_PARAM *a_game;
	
	a_game = data;
	apw->a_game = *a_game;

	
	//-- ��M�����f�[�^�ɏ]���ď����������� --//
	//�A�s�[���|�C���g�A�C�R���폜
	AT_AppealPointActorDelAll(&apw->sys);
	//���A�C�R���폜
	AT_NextIconActorDelAll(&apw->sys);
	//�p�l����������
	//BreederParamBmpWriteAll(apw);
	AT_BreederPanelFontOamPosUpdate(apw);
	BreederPanelColorChangeAll(apw);
	
	//�Ԏ���Ԃ�	�o�b�t�@�͓��ɓn�����̂��Ȃ��̂�NULL�w��
	CO_ANSWER_TransmitBufferSet(&apw->cow, req_head, NULL, 0);
}


//==============================================================================
//	
//==============================================================================
//--------------------------------------------------------------
/**
 * @brief   ���ߑ��M(���M��)�F��b���b�Z�[�W�̕\��
 *
 * @param   apw			���Z�͕���Ǘ����[�N�ւ̃|�C���^
 * @param   work		�C�ӂ̃|�C���^
 *
 * @retval  �o�^���ꂽ���N�G�X�g�r�b�g�ԍ�
 */
//--------------------------------------------------------------
static int Request_Talk(CONTEST_ORDER_WORK *cow, void *syswork, int order_no, void *work)
{
	ACTIN_PROC_WORK *apw = syswork;
	int bit_no;
	
	bit_no = CO_REQUEST_TransmitBufferSet(cow, CSELECT_ALL, order_no, 
		work, sizeof(ACTIN_ADVANCE_PARAM));
	return bit_no;
}

//--------------------------------------------------------------
/**
 * @brief   ���ߎ�M(���M��)�F��b���b�Z�[�W�̕\��
 *
 * @param   apw			���Z�͕���Ǘ����[�N�ւ̃|�C���^
 * @param   req_head	���N�G�X�g�w�b�_�̃|�C���^
 * @param   data		��M�f�[�^�ւ̃|�C���^
 */
//--------------------------------------------------------------
static void Recieve_Talk(CONTEST_ORDER_WORK *cow, void *syswork, const CORDER_HEAD *req_head, void *data)
{
	ACTIN_PROC_WORK *apw = syswork;
	ACTIN_ADVANCE_PARAM *aap = data;
	AOLOCAL_TALK_PUT *talk;
	
	talk = sys_AllocMemory(HEAPID_ACTIN, sizeof(AOLOCAL_TALK_PUT));
	MI_CpuClear8(talk, sizeof(AOLOCAL_TALK_PUT));
	
	talk->apw = apw;
	talk->req_head = *req_head;
	talk->cow = cow;
	talk->breeder_no = aap->now_breeder;
	
	talk->a_talk_tagpara = aap->nt.a_talk_tagpara;
	talk->a_talk_id = aap->nt.a_talk_id;
	talk->a_talk_bmpwin_not_close = aap->nt.a_talk_bmpwin_not_close;
	talk->a_talk_bmpwin_close_wait = aap->nt.a_talk_bmpwin_close_wait;
	
	TCB_Add(AOTCB_TalkPut, talk, TCBPRI_ACTIN_ORDERSUB);
}

//--------------------------------------------------------------
/**
 * @brief   ��b���b�Z�[�W�̕\��
 * @param   tcb			TCB�ւ̃|�C���^
 * @param   work		AOLOCAL_TALK_PUT�\����
 */
//--------------------------------------------------------------
static void AOTCB_TalkPut(TCB_PTR tcb, void *work)
{
	AOLOCAL_TALK_PUT *talk = work;
	
	switch(talk->seq){
	case 0:
		if(talk->a_talk_id != A_TALK_NULL){
//			BmpTalkWinWrite(&talk->vpw->sys.win[ACTIN_BMPWIN_TALK], WINDOW_TRANS_OFF,
//				ACTIN_TALKWIN_CGX_OFFSET, ACTIN_TALKWIN_PALNO);
//			GF_BGL_LoadScreenV_Req(talk->apw->sys.bgl, ACTIN_FRAME_WIN);
			
			AT_A_TalkMessageSet(talk->apw, talk->a_talk_id, &talk->a_talk_tagpara, NULL);
			talk->seq++;
		}
		else{
			talk->seq = 100;
		}
		break;
	case 1:
		if(AT_TalkMessageEndCheck(talk->apw) == 0){
			talk->seq++;
		}
		break;
	case 2:
		talk->close_wait++;
		if(talk->a_talk_bmpwin_not_close == TRUE){
			talk->seq++;
		}
		else if(talk->close_wait >= talk->a_talk_bmpwin_close_wait){
//			BmpTalkWinClear(&talk->apw->sys.win[ACTIN_BMPWIN_TALK], WINDOW_TRANS_OFF);
//			GF_BGL_LoadScreenV_Req(talk->apw->sys.bgl, ACTIN_FRAME_WIN);
			talk->seq++;
		}
		break;
	default:
		CO_ANSWER_TransmitBufferSet(talk->cow, &talk->req_head, NULL, 0);

		sys_FreeMemoryEz(talk);
		TCB_Delete(tcb);
		return;
	}
}

