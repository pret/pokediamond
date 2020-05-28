//==============================================================================
/**
 * @file	actin_waza.c
 * @brief	���Z�͕���F�Z����
 * @author	matsuda
 * @date	2006.01.26(��)
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

#include "wazaeffect/battle_particle.h"
#include "system/particle.h"
#include "wazaeffect/we_mana.h"
#include "wazaeffect/we_sys.h"

#include "system/brightness.h"

#include "graphic/contest_bg_def.h"
#include "graphic/contest_obj_def.h"

#include "actin_tool.h"
#include "actin_order.h"
#include "actin_id.h"
#include "actin_input.h"
#include "actin_calc.h"
#include "con_tool.h"

#include "poketool/waza_tool.h"


//==============================================================================
//	�萔��`
//==============================================================================
///�Z���ʂ𔭐�������^�C�~���O��`(���s���鏇��)
enum{
	//-- ���̃^�C�~���O�ł͂܂���{AP���͖��擾 --//
	SPMSG_TIMING_FIRST,		///<�Z�G�t�F�N�g���s�O�ɓ��ꃁ�b�Z�[�W
	
	KOUKA_TIMING_FIRST,		///<�����s�������(��ɃV�[���h�n��)
	KOUKA_TIMING_FIELD,		///<��ɂ��������(��ɑS�̖W�Q�Z��)
	
	//-- �����Ŋ�{AP��{���e�[�W�l�����擾 --//
	
	KOUKA_TIMING_NOW,		///<�����̃A�s�[���̎��ɔ����������
	
	//-- �����Ŏ擾AP�A�Z���ʁA�W�Q���Ŏ擾����AP�l�̉����Z���s�����v���o�� --//
	
	KOUKA_TIMING_AFTER,		///<�S���̃A�s�[���I����ɔ����������
	KOUKA_TIMING_JUDGESUFFER,	///<�R�����n�̋Z����
	
	//-- �����ŐR����蕪�̉��Z --//
	
	KOUKA_TIMING_END,		///<�S�Ă̏����̍Ō�ɔ����������
};

///���b�Z�[�W�^�O�w�肷�鎞�A�g�p���Ȃ��̂ŁA�Ӑ}�I�Ɏw��Ȃ��A�ƕ\�L����ׂ̒�`
#define TAG_NULL		(30000)

///���ꃁ�b�Z�[�W���g�p���Ȃ�
#define SPMSG_TIMING_NULL		(0xff)

//==============================================================================
//	�\���̒�`
//==============================================================================
///�Z���ʃV�[�P���X�̊֐��^��`
typedef int (*KOUKA_FUNC)(ACTIN_PROC_WORK *, AWAZA_PARAM *, int, int, int);

///�Z���ʃV�[�P���X�f�[�^�\����
typedef struct{
	KOUKA_FUNC func;		///<���s�֐��ւ̃|�C���^
	u8 timing;				///<���s�^�C�~���O
	u8 sp_msg;				///<���ꃁ�b�Z�[�W��\��������^�C�~���O
	
	u8 dummy[2];
}KOUKA_SEQ_DATA;


//==============================================================================
//	�v���g�^�C�v�錾
//==============================================================================
static void AWAZA_SaveParamUpdate(AWAZA_PARAM *wp);

static int Kouka_NextFirst(ACTIN_PROC_WORK *apw, AWAZA_PARAM *wp, int appeal_breeder, 
	int kouka_breeder, int pos);
static int Kouka_NextEnd(ACTIN_PROC_WORK *apw, AWAZA_PARAM *wp, int appeal_breeder, 
	int kouka_breeder, int pos);
static int Kouka_JudgeSufferAdd(ACTIN_PROC_WORK *apw, AWAZA_PARAM *wp, int appeal_breeder, 
	int kouka_breeder, int pos);
static int Kouka_VoltageUpAdd(ACTIN_PROC_WORK *apw, AWAZA_PARAM *wp, int appeal_breeder, 
	int kouka_breeder, int pos);
static int Kouka_Null(ACTIN_PROC_WORK *apw, AWAZA_PARAM *wp, int appeal_breeder, 
	int kouka_breeder, int pos);
static int Kouka_NoneJudgeSufferAdd(ACTIN_PROC_WORK *apw, AWAZA_PARAM *wp, int appeal_breeder, 
	int kouka_breeder, int pos);
static int Kouka_Continuation(ACTIN_PROC_WORK *apw, AWAZA_PARAM *wp, int appeal_breeder, 
	int kouka_breeder, int pos);
static int Kouka_VoltageAddAP(ACTIN_PROC_WORK *apw, AWAZA_PARAM *wp, int appeal_breeder, 
	int kouka_breeder, int pos);
static int Kouka_AllSufferAdd(ACTIN_PROC_WORK *apw, AWAZA_PARAM *wp, int appeal_breeder, 
	int kouka_breeder, int pos);
static int Kouka_AllVoltageSub(ACTIN_PROC_WORK *apw, AWAZA_PARAM *wp, int appeal_breeder, 
	int kouka_breeder, int pos);
static int Kouka_NextTurnTwice(ACTIN_PROC_WORK *apw, AWAZA_PARAM *wp, int appeal_breeder, 
	int kouka_breeder, int pos);
static int Kouka_VoltageUpStop(ACTIN_PROC_WORK *apw, AWAZA_PARAM *wp, int appeal_breeder, 
	int kouka_breeder, int pos);
static int Kouka_FrontSame(ACTIN_PROC_WORK *apw, AWAZA_PARAM *wp, int appeal_breeder, 
	int kouka_breeder, int pos);
static int Kouka_NextRandom(ACTIN_PROC_WORK *apw, AWAZA_PARAM *wp, int appeal_breeder, 
	int kouka_breeder, int pos);
static int Kouka_EndTwice(ACTIN_PROC_WORK *apw, AWAZA_PARAM *wp, int appeal_breeder, 
	int kouka_breeder, int pos);
static int Kouka_VoltageLevelAdd(ACTIN_PROC_WORK *apw, AWAZA_PARAM *wp, int appeal_breeder, 
	int kouka_breeder, int pos);
static int Kouka_FirstAdd(ACTIN_PROC_WORK *apw, AWAZA_PARAM *wp, int appeal_breeder, 
	int kouka_breeder, int pos);
static int Kouka_EndAdd(ACTIN_PROC_WORK *apw, AWAZA_PARAM *wp, int appeal_breeder, 
	int kouka_breeder, int pos);
static int Kouka_VoltageSubStop(ACTIN_PROC_WORK *apw, AWAZA_PARAM *wp, int appeal_breeder, 
	int kouka_breeder, int pos);
static int Kouka_ContinuationVoltageAdd(ACTIN_PROC_WORK *apw, AWAZA_PARAM *wp, int appeal_breeder, 
	int kouka_breeder, int pos);
static int Kouka_SortAdd(ACTIN_PROC_WORK *apw, AWAZA_PARAM *wp, int appeal_breeder, 
	int kouka_breeder, int pos);
static int Kouka_VoltageMaxAfterAdd(ACTIN_PROC_WORK *apw, AWAZA_PARAM *wp, int appeal_breeder, 
	int kouka_breeder, int pos);
static int Kouka_LowPointAdd(ACTIN_PROC_WORK *apw, AWAZA_PARAM *wp, int appeal_breeder, 
	int kouka_breeder, int pos);


//==============================================================================
//	�f�[�^
//==============================================================================
#include "actin_waza.dat"

///���Z�͕��僁�C���֐��̃V�[�P���X�e�[�u��
static const KOUKA_SEQ_DATA KoukaSeqTbl[] = {
	{Kouka_Null, 				KOUKA_TIMING_NOW, SPMSG_TIMING_NULL},      	//0 1�I���W���̈׃_�~�[
	{Kouka_NextFirst,			KOUKA_TIMING_NOW, SPMSG_TIMING_NULL},			//1
	{Kouka_NextEnd, 			KOUKA_TIMING_NOW, SPMSG_TIMING_NULL},      		//2
	{Kouka_JudgeSufferAdd, 		KOUKA_TIMING_JUDGESUFFER, SPMSG_TIMING_NULL},	//3
	{Kouka_VoltageUpAdd, 		KOUKA_TIMING_NOW, SPMSG_TIMING_NULL},      		//4
	{Kouka_Null, 				KOUKA_TIMING_NOW, SPMSG_TIMING_NULL},      		//5
	{Kouka_NoneJudgeSufferAdd, 	KOUKA_TIMING_JUDGESUFFER, SPMSG_TIMING_FIRST}, 	//6
	{Kouka_Continuation, 		KOUKA_TIMING_NOW, SPMSG_TIMING_NULL},      		//7
	{Kouka_VoltageAddAP, 		KOUKA_TIMING_NOW, SPMSG_TIMING_NULL},      		//8
	{Kouka_AllSufferAdd, 		KOUKA_TIMING_JUDGESUFFER, SPMSG_TIMING_FIRST},	//9
	{Kouka_AllVoltageSub, 		KOUKA_TIMING_NOW, SPMSG_TIMING_NULL},      		//10
	{Kouka_NextTurnTwice, 		KOUKA_TIMING_NOW, SPMSG_TIMING_NULL},      		//11
	{Kouka_FrontSame, 			KOUKA_TIMING_NOW, SPMSG_TIMING_NULL},      		//12
	{Kouka_VoltageUpStop, 		KOUKA_TIMING_NOW, SPMSG_TIMING_NULL},      		//13
	{Kouka_NextRandom, 			KOUKA_TIMING_NOW, SPMSG_TIMING_NULL},      		//14
	{Kouka_EndTwice, 			KOUKA_TIMING_NOW, SPMSG_TIMING_NULL},      		//15
	{Kouka_VoltageLevelAdd, 	KOUKA_TIMING_NOW, SPMSG_TIMING_NULL},      		//16
	{Kouka_FirstAdd, 			KOUKA_TIMING_NOW, SPMSG_TIMING_NULL},      		//17
	{Kouka_EndAdd, 				KOUKA_TIMING_NOW, SPMSG_TIMING_NULL},      		//18
	{Kouka_VoltageSubStop,		KOUKA_TIMING_NOW, SPMSG_TIMING_NULL},			//19
	{Kouka_ContinuationVoltageAdd, KOUKA_TIMING_NOW, SPMSG_TIMING_NULL},		//20
	{Kouka_SortAdd,				KOUKA_TIMING_NOW, SPMSG_TIMING_NULL},			//21
	{Kouka_VoltageMaxAfterAdd,	KOUKA_TIMING_NOW, SPMSG_TIMING_NULL},			//22
	{Kouka_LowPointAdd,			KOUKA_TIMING_END, SPMSG_TIMING_NULL},			//23
};


//--------------------------------------------------------------
/**
 * @brief   ���b�Z�[�W�p�����[�^�Z�b�g
 *
 * @param   personal		
 * @param   apno			�Z���ʔԍ�
 * @param   msg_type		�g�p���郁�b�Z�[�W�^�C�v(KOUKA_MSGID_???)
 * @param   mine			MINE�^�O�̎��Q�Ƃ���u���[�_�[�̔ԍ�
 * @param   enemy			ENEMY�^�O�̎��Q�Ƃ���u���[�_�[�̔ԍ�
 * @param   wazano			WAZA�^�O�̎��Q�Ƃ���Z�ԍ�
 * @param   num				NUM�^�O�̎��Q�Ƃ��鐔�l
 */
//--------------------------------------------------------------
static void AWAZA_MsgParamSet(AWAZA_PERSONAL *personal, int apno, int msg_type, int mine, int enemy, int wazano, int num)
{
	personal->msg_apno = apno;
	personal->msg_type = msg_type;

	if(mine != TAG_NULL){
		personal->tagpara.mine_brd = mine;
	}
	if(enemy != TAG_NULL){
		personal->tagpara.enemy_brd = enemy;
	}
	if(wazano != TAG_NULL){
		personal->tagpara.wazano = wazano;
	}
	if(num != TAG_NULL){
		personal->tagpara.num = num;
	}

	OS_TPrintf("�Z���ʃ��b�Z�[�W�Z�b�g�Fmsg_apno=%d, msg_type=%d\n", apno, msg_type);
}

//--------------------------------------------------------------
/**
 * @brief   �^�[���̍ŏ��ɍs���K�v�̂��鏉��������
 *
 * @param   apw		���Z�͕���Ǘ����[�N�ւ̃|�C���^
 * @param   wp		�Z���ʃp�����[�^�ւ̃|�C���^
 */
//--------------------------------------------------------------
void AWAZA_WazaParaTurnInit(ACTIN_PROC_WORK *apw, AWAZA_PARAM *wp)
{
	int breeder_no;
	
	*wp = apw->a_game.wazapara;
	
	AWAZA_SaveParamUpdate(wp);	//personal���N���A����O�ɒl�X�V
	MI_CpuClear8(wp->personal, sizeof(AWAZA_PERSONAL) * BREEDER_MAX);
	
	for(breeder_no = 0; breeder_no < BREEDER_MAX; breeder_no++){
		AT_MsgTagParaInitDataSet(apw, &wp->personal[breeder_no].tagpara, breeder_no);

		wp->personal[breeder_no].judge_no = apw->a_game.judge_no[breeder_no];
		wp->personal[breeder_no].wazano = apw->a_game.waza_no[breeder_no];
		wp->personal[breeder_no].apno = WT_WazaDataParaGet(
			wp->personal[breeder_no].wazano, ID_WTD_ap_no);
		wp->personal[breeder_no].judge_suffer = ACALC_JudgeSufferCheck(&apw->a_game, breeder_no);
	}
}

//--------------------------------------------------------------
/**
 * @brief   �e�u���[�_�[�̉��Z�J�n�O�ɍs���K�v�̂��鏉��������
 *
 * @param   apw				���Z�͕���Ǘ����[�N�ւ̃|�C���^
 * @param   breeder_no		�u���[�_�[No
 */
//--------------------------------------------------------------
void AWAZA_WazaParaBreederInit(ACTIN_PROC_WORK *apw, AWAZA_PARAM *wp, int breeder_no)
{
	int i;
	
	for(i = 0; i < BREEDER_MAX; i++){
		wp->personal[i].before_next_sort = wp->personal[i].next_sort;
		wp->personal[i].before_next_pos = wp->personal[i].next_pos;
	}

	for(i = 0; i < JUDGE_MAX; i++){
		wp->voltage_before[i] = apw->a_game.voltage_total[i];
		wp->voltage_after[i] = apw->a_game.voltage_total[i];
	}
}

//--------------------------------------------------------------
/**
 * @brief   �e�u���[�_�[�̉��Z�I����ɍs���A�Q�[���p�����[�^�ւ̃f�[�^�X�V����
 *
 * @param   apw				���Z�͕���Ǘ����[�N�ւ̃|�C���^
 * @param   breeder_no		�u���[�_�[No
 */
//--------------------------------------------------------------
void AWAZA_WazaParaBreederGameUpdate(ACTIN_PROC_WORK *apw, AWAZA_PARAM *wp, int breeder_no)
{
	int i;
	
	for(i = 0; i < JUDGE_MAX; i++){
		apw->a_game.voltage_total[i] = wp->voltage_after[i];
		if(apw->a_game.voltage_total[i] >= VOLTAGE_POINT_FULL){
			apw->a_game.voltage_total[i] = 0;
		}
	}
}

//--------------------------------------------------------------
/**
 * @brief   �^�[���I����ɍs���A�Q�[���p�����[�^�ւ̃f�[�^�X�V����
 *
 * @param   apw		���Z�͕���Ǘ����[�N�ւ̃|�C���^
 * @param   wp		�Z���ʃp�����[�^�ւ̃|�C���^
 */
//--------------------------------------------------------------
void AWAZA_WazaParaTurnGameUpdate(ACTIN_PROC_WORK *apw, AWAZA_PARAM *wp)
{
	int i;
	
	for(i = 0; i < BREEDER_MAX; i++){
		apw->a_game.app_total[i] += wp->personal[i].app_total;
		apw->a_game.app_turn[i] = wp->personal[i].app_total;
	}
	apw->a_game.wazapara = *wp;
}


//--------------------------------------------------------------
/**
 * @brief   �Z�v�Z�O�ɍs���K�v�̂���e��p�����[�^�X�V����
 *
 * @param   wp				�Z���ʃp�����[�^�ւ̃|�C���^
 * @param   breeder_no		�Z���o���Ԃ�[���[�̔ԍ�
 */
//--------------------------------------------------------------
static void AWAZA_CalcInitUpdateParam(AWAZA_PARAM *wp, int breeder_no)
{
	int i;

	wp->personal[breeder_no].app_total_before = wp->personal[breeder_no].app_total;
	wp->personal[breeder_no].my_effective_ap = 0;
	wp->personal[breeder_no].enemy_effective_ap = 0;

	//�ύX�O�̃{���e�[�W�l�擾
	for(i = 0; i < JUDGE_MAX; i++){
		wp->voltage_before[i] = wp->voltage_after[i];
	}
	
	for(i = 0; i < BREEDER_MAX; i++){
		wp->personal[i].kouka_occ = FALSE;
		wp->personal[i].msg_apno = 0;
	}
}

//--------------------------------------------------------------
/**
 * @brief   �S���̋Z���ʔ����O��AP�l���L��
 * @param   wp		�Z���ʃp�����[�^�ւ̃|�C���^
 */
//--------------------------------------------------------------
void AWAZA_TimingBeforeAppUpdate(AWAZA_PARAM *wp)
{
	int i;
	
	for(i = 0; i < BREEDER_MAX; i++){
		wp->personal[i].app_total_timing_before = wp->personal[i].app_total;
	}
}

//--------------------------------------------------------------
/**
 * @brief   �Z�G�t�F�N�g���s�O�ɕ\��������ꃁ�b�Z�[�W�̔�����s��
 *
 * @param   apw					���Z�͕���Ǘ����[�N�ւ̃|�C���^
 * @param   wp					�Z���ʃp�����[�^�ւ̃|�C���^
 * @param   breeder_no			�Z���o���Ă���u���[�_�[
 */
//--------------------------------------------------------------
void AWAZA_FirstMsg(ACTIN_PROC_WORK *apw, AWAZA_PARAM *wp, int breeder_no)
{
	u32 msg_id, msg_tag;

	AWAZA_CalcInitUpdateParam(wp, breeder_no);
	
	if(KoukaSeqTbl[wp->personal[breeder_no].apno].sp_msg == SPMSG_TIMING_FIRST){
		ConTool_GetKoukaMsgID(wp->personal[breeder_no].apno, KOUKA_MSGID_SP, &msg_id, &msg_tag);
		if(msg_id != AMSG_ID_NONE){
			AWAZA_MsgParamSet(&wp->personal[breeder_no], wp->personal[breeder_no].apno, 
				KOUKA_MSGID_SP, breeder_no, TAG_NULL, TAG_NULL, TAG_NULL);
		}
	}
}

//--------------------------------------------------------------
/**
 * @brief   �Z�̊�{AP�l�̌v�Z���s��
 *
 * @param   apw					���Z�͕���Ǘ����[�N�ւ̃|�C���^
 * @param   wp					�Z���ʃp�����[�^�ւ̃|�C���^
 * @param   breeder_no			�Z���o���Ă���u���[�_�[
 */
//--------------------------------------------------------------
void AWAZA_BaseAP(ACTIN_PROC_WORK *apw, AWAZA_PARAM *wp, int breeder_no)
{
	AWAZA_CalcInitUpdateParam(wp, breeder_no);
	
	wp->personal[breeder_no].base_ap = ConTool_GetAPWaza_App(wp->personal[breeder_no].apno);
	
	wp->personal[breeder_no].app_total = wp->personal[breeder_no].base_ap;
}

//--------------------------------------------------------------
/**
 * @brief   �Z���ʔ�������
 *
 * @param   apw					���Z�͕���Ǘ����[�N�ւ̃|�C���^
 * @param   wp					�Z���ʃp�����[�^�ւ̃|�C���^
 * @param   now_breeder			�Z���o���Ă���u���[�_�[
 * @param   now_breeder_pos		�Z���o���Ă���u���[�_�[�͉��Ԗڂ̃A�s�[����
 */
//--------------------------------------------------------------
void AWAZA_Kouka(ACTIN_PROC_WORK *apw, AWAZA_PARAM *wp, int now_breeder, int now_breeder_pos)
{
	int i;
	
	AWAZA_CalcInitUpdateParam(wp, now_breeder);
	
	//�A�s�[�������{�l�̋Z���ʔ���
	if(KoukaSeqTbl[wp->personal[now_breeder].apno].timing == KOUKA_TIMING_NOW){
		OS_TPrintf("������NOW�Z���ʔ����F%d������(�u���[�_�[No%d�Apos=%d)\n",
			wp->personal[now_breeder].apno, now_breeder, now_breeder_pos);
		KoukaSeqTbl[wp->personal[now_breeder].apno].func(apw, wp, now_breeder, 
			now_breeder, now_breeder_pos);
		wp->personal[now_breeder].kouka_occ = TRUE;
		wp->personal[now_breeder].app_total += wp->personal[now_breeder].my_effective_ap 
			+ wp->personal[now_breeder].enemy_effective_ap;
	}
	
	//���ɃA�s�[���ς݂̃u���[�_�[�B�̋Z���ʔ����`�F�b�N
	for(i = 0; i <= now_breeder_pos/*apw->a_game.breeder_end_count*/; i++){
		int kouka_breeder = apw->a_game.breeder_sort[i];
		if(KoukaSeqTbl[wp->personal[kouka_breeder].apno].timing == KOUKA_TIMING_FIELD){
			OS_TPrintf("������FIELD�Z���ʔ����F%d������(�u���[�_�[No%d�Apos=%d)\n",
				wp->personal[kouka_breeder].apno, kouka_breeder, i);
			AWAZA_CalcInitUpdateParam(wp, kouka_breeder);
			KoukaSeqTbl[wp->personal[kouka_breeder].apno].func(apw, wp, 
				now_breeder, kouka_breeder, now_breeder_pos);
			wp->personal[kouka_breeder].kouka_occ = TRUE;
			wp->personal[kouka_breeder].app_total += wp->personal[kouka_breeder].my_effective_ap;
		}
	}
}

//--------------------------------------------------------------
/**
 * @brief   �o�����Z�̋Z���ʔ�����ɔ����������Z����
 *
 * @param   apw					���Z�͕���Ǘ����[�N�ւ̃|�C���^
 * @param   wp					�Z���ʃp�����[�^�ւ̃|�C���^
 * @param   now_breeder			
 * @param   now_breeder_pos		
 */
//--------------------------------------------------------------
void AWAZA_KoukaSpecial(ACTIN_PROC_WORK *apw, AWAZA_PARAM *wp, 
	int now_breeder, int now_breeder_pos)
{
	int add_ap;

	AWAZA_CalcInitUpdateParam(wp, now_breeder);
	
	if(wp->save[now_breeder].twice_now_apno != 0){
		OS_TPrintf("���������^�[��2�{�̋Z���ʔ���������(�u���[�_�[No%d�Apos=%d)\n",
			now_breeder, now_breeder_pos);
		add_ap = wp->personal[now_breeder].app_total;
		wp->personal[now_breeder].my_effective_ap += add_ap;
		AWAZA_MsgParamSet(&wp->personal[now_breeder], wp->save[now_breeder].twice_now_apno, 
			KOUKA_MSGID_A, now_breeder, TAG_NULL, TAG_NULL, add_ap / APPEAL_ICON_ONE_POINT);
	}

	wp->personal[now_breeder].app_total += wp->personal[now_breeder].my_effective_ap 
		+ wp->personal[now_breeder].enemy_effective_ap;
}

//--------------------------------------------------------------
/**
 * @brief   �Z���ʔ�������(�S�����Z�I����)
 *
 * @param   apw					���Z�͕���Ǘ����[�N�ւ̃|�C���^
 * @param   wp					�Z���ʃp�����[�^�ւ̃|�C���^
 * @param   now_breeder			�Z���o���Ă���u���[�_�[
 * @param   now_breeder_pos		�Z���o���Ă���u���[�_�[�͉��Ԗڂ̃A�s�[����
 *
 * @retval	TRUE:�����^�C�~���O�������̂ŏ������s��ꂽ�B�@FALSE:�����͍s���Ȃ�����
 */
//--------------------------------------------------------------
BOOL AWAZA_KoukaAfterTiming(ACTIN_PROC_WORK *apw, AWAZA_PARAM *wp, int now_breeder, 
	int now_breeder_pos)
{
	int i;
	
	AWAZA_CalcInitUpdateParam(wp, now_breeder);
	
	if(KoukaSeqTbl[wp->personal[now_breeder].apno].timing == KOUKA_TIMING_AFTER){
		OS_TPrintf("������AFTER�Z���ʔ����F%d������(�u���[�_�[No%d�Apos=%d)\n",
			wp->personal[now_breeder].apno, now_breeder, now_breeder_pos);
		KoukaSeqTbl[wp->personal[now_breeder].apno].func(apw, wp, now_breeder, 
			now_breeder, now_breeder_pos);
		wp->personal[now_breeder].kouka_occ = TRUE;
		wp->personal[now_breeder].app_total += wp->personal[now_breeder].my_effective_ap;
		return TRUE;
	}
	
	return FALSE;
}

//--------------------------------------------------------------
/**
 * @brief   �R�����n�̋Z���ʔ�������(�S�����Z�I����)
 *
 * @param   apw					���Z�͕���Ǘ����[�N�ւ̃|�C���^
 * @param   wp					�Z���ʃp�����[�^�ւ̃|�C���^
 * @param   now_breeder			�Z���o���Ă���u���[�_�[
 * @param   now_breeder_pos		�Z���o���Ă���u���[�_�[�͉��Ԗڂ̃A�s�[����
 *
 * @retval	TRUE:�����^�C�~���O�������̂ŏ������s��ꂽ�B�@FALSE:�����͍s���Ȃ�����
 */
//--------------------------------------------------------------
BOOL AWAZA_KoukaJudgeSufferTiming(ACTIN_PROC_WORK *apw, AWAZA_PARAM *wp, int now_breeder, 
	int now_breeder_pos)
{
	int i;
	
	AWAZA_CalcInitUpdateParam(wp, now_breeder);
	
	if(KoukaSeqTbl[wp->personal[now_breeder].apno].timing == KOUKA_TIMING_JUDGESUFFER){
		OS_TPrintf("������JUDGE_SUFFER�Z���ʔ����F%d������(�u���[�_�[No%d�Apos=%d)\n",
			wp->personal[now_breeder].apno, now_breeder, now_breeder_pos);
		KoukaSeqTbl[wp->personal[now_breeder].apno].func(apw, wp, now_breeder, 
			now_breeder, now_breeder_pos);
		wp->personal[now_breeder].kouka_occ = TRUE;
		wp->personal[now_breeder].app_total += wp->personal[now_breeder].my_effective_ap;
		return TRUE;
	}
	
	return FALSE;
}

//--------------------------------------------------------------
/**
 * @brief   �Z���ʔ�������(�S�ẴA�s�[���I����)
 *
 * @param   apw					���Z�͕���Ǘ����[�N�ւ̃|�C���^
 * @param   wp					�Z���ʃp�����[�^�ւ̃|�C���^
 * @param   now_breeder			�Z���o���Ă���u���[�_�[
 * @param   now_breeder_pos		�Z���o���Ă���u���[�_�[�͉��Ԗڂ̃A�s�[����
 *
 * @retval	TRUE:�����^�C�~���O�������̂ŏ������s��ꂽ�B�@FALSE:�����͍s���Ȃ�����
 */
//--------------------------------------------------------------
BOOL AWAZA_KoukaEndTiming(ACTIN_PROC_WORK *apw, AWAZA_PARAM *wp, int now_breeder, 
	int now_breeder_pos)
{
	int i;
	
	AWAZA_CalcInitUpdateParam(wp, now_breeder);
	
	if(KoukaSeqTbl[wp->personal[now_breeder].apno].timing == KOUKA_TIMING_END){
		OS_TPrintf("������END�Z���ʔ����F%d������(�u���[�_�[No%d�Apos=%d)\n",
			wp->personal[now_breeder].apno, now_breeder, now_breeder_pos);
		KoukaSeqTbl[wp->personal[now_breeder].apno].func(apw, wp, now_breeder, 
			now_breeder, now_breeder_pos);
		wp->personal[now_breeder].kouka_occ = TRUE;
		wp->personal[now_breeder].app_total += wp->personal[now_breeder].my_effective_ap;
		return TRUE;
	}
	
	return FALSE;
}

//--------------------------------------------------------------
/**
 * @brief   �Z���o������̃{���e�[�W�v�Z����
 *
 * @param   apw					���Z�͕���Ǘ����[�N�ւ̃|�C���^
 * @param   wp					�Z���ʃp�����[�^�ւ̃|�C���^
 * @param   breeder_no			�Z���o���Ă���u���[�_�[�̔ԍ�
 * @param   nt					A_TALK�p�ʏ��b���b�Z�[�W�����
 */
//--------------------------------------------------------------
void AWAZA_Voltage(ACTIN_PROC_WORK *apw, AWAZA_PARAM *wp, int breeder_no, NORMAL_TALK *nt)
{
	int k, judge_no, voltage_addsub;

	AWAZA_CalcInitUpdateParam(wp, breeder_no);
	nt->a_talk_id = A_TALK_NULL;
	nt->after_a_talk_id = A_TALK_NULL;
	
	judge_no = apw->a_game.judge_no[breeder_no];
	
	//�{���e�[�W�`�F�b�N
	voltage_addsub = ACALC_VoltageUpDownCheck(apw->consys->c_game.type, 
		wp->personal[breeder_no].wazano, judge_no, apw->consys->c_game.special_judge_no);
	
	if(voltage_addsub > 0 && wp->personal[breeder_no].invalid_voltage_up == 0){
		wp->voltage_after[judge_no] += voltage_addsub;
		if(wp->voltage_after[judge_no] >= VOLTAGE_POINT_FULL){
			wp->voltage_after[judge_no] = VOLTAGE_POINT_FULL;
		}
	}
	else if(voltage_addsub < 0 && wp->personal[breeder_no].invalid_voltage_down == 0
			&& wp->voltage_after[judge_no] > 0){
		wp->voltage_after[judge_no] += voltage_addsub;
		if(wp->voltage_after[judge_no] <= 0){
			wp->voltage_after[judge_no] = 0;
		}
	}
	else{
		voltage_addsub = 0;
	}
	
	//�{���e�[�W�ő�`�F�b�N
	if(wp->voltage_after[judge_no] >= VOLTAGE_POINT_FULL){
		if(judge_no == apw->consys->c_game.special_judge_no){
			wp->personal[breeder_no].voltage_add_ap = VOLTAGE_FULL_ADD_AP_SPECIAL;
		}
		else{
			wp->personal[breeder_no].voltage_add_ap = VOLTAGE_FULL_ADD_AP;
		}
	}

#if 0
	//�ő�ɒB���Ă���{���e�[�W��0�N���A
	for(k = 0; k < JUDGE_MAX; k++){
		if(apw->a_game.voltage_total[k] >= VOLTAGE_POINT_FULL){
			apw->a_game.voltage_total[k] = 0;
		}
	}
#endif

	//A_TALK���b�Z�[�W
	nt->after_a_talk_tagpara.num = wp->personal[breeder_no].voltage_add_ap / VOLTAGE_ONE_POINT;
	if(voltage_addsub > 0){
	#if 0
		if(voltage_addsub == VOLTAGE_ONE_POINT){
			nt->a_talk_id = A_TALK_VOLTAGE_UP_1;
		}
		else{
			nt->a_talk_id = A_TALK_VOLTAGE_UP_2;
		}
	#else
		nt->a_talk_id = AT_A_TalkIDGet_VoltageUp(
			WT_WazaDataParaGet(wp->personal[breeder_no].wazano, ID_WTD_contype));
	#endif
		switch(wp->voltage_after[judge_no] / VOLTAGE_ONE_POINT){
		case 2:
//			nt->after_a_talk_id = A_TALK_VOLTAGE_STATE_UP_2;
			break;
		case 3:
//			nt->after_a_talk_id = A_TALK_VOLTAGE_STATE_UP_3;
			break;
		case 4:
			nt->after_a_talk_id = A_TALK_VOLTAGE_STATE_UP_4;
			break;
		case 5:
			nt->after_a_talk_id = A_TALK_VOLTAGE_STATE_UP_5;
			break;
		}
	}
	else if(voltage_addsub < 0){
//		nt->a_talk_id = A_TALK_VOLTAGE_SUB_1;
		nt->a_talk_id = AT_A_TalkIDGet_VoltageSub(WT_WazaDataParaGet(
			wp->personal[breeder_no].wazano, ID_WTD_contype));
		switch(wp->voltage_after[judge_no] / VOLTAGE_ONE_POINT){
		case 3:
//			nt->after_a_talk_id = A_TALK_VOLTAGE_STATE_SUB_3;
			break;
		case 2:
//			nt->after_a_talk_id = A_TALK_VOLTAGE_STATE_SUB_2;
			break;
		case 1:
//			nt->after_a_talk_id = A_TALK_VOLTAGE_STATE_SUB_1;
			break;
		case 0:
			if(wp->voltage_before[judge_no] != 0){
//				nt->after_a_talk_id = A_TALK_VOLTAGE_STATE_SUB_0;
			}
			break;
		}
	}

	wp->personal[breeder_no].app_total += wp->personal[breeder_no].voltage_add_ap;
}

//--------------------------------------------------------------
/**
 * @brief   �R�����v�Z
 *
 * @param   apw					���Z�͕���Ǘ����[�N�ւ̃|�C���^
 * @param   wp					�Z���ʃp�����[�^�ւ̃|�C���^
 * @param   nt					A_TALK�p�ʏ��b���b�Z�[�W�����
 */
//--------------------------------------------------------------
void AWAZA_JudgeSuffer(ACTIN_PROC_WORK *apw, AWAZA_PARAM *wp, int now_breeder, NORMAL_TALK *nt)
{
	int add_ap;
	
	AWAZA_CalcInitUpdateParam(wp, now_breeder);
	add_ap = ACALC_JudgeSufferPointCheck(wp->personal[now_breeder].judge_suffer);
	wp->personal[now_breeder].app_total += add_ap;
//	if(wp->personal[now_breeder].judge_suffer == 0){
//		nt->after_a_talk_id = A_TALK_NO_JUDGE_SUFFER;
//	}
//	else{
//		nt->after_a_talk_id = A_TALK_JUDGE_SUFFER;
//	}
//	nt->after_a_talk_tagpara.num = add_ap / APPEAL_ICON_ONE_POINT;
	
	OS_TPrintf("�u���[�_�[No%d, �R�����l����%d, �擾�|�C���g��%d\n", 
		now_breeder, wp->personal[now_breeder].judge_suffer, add_ap);
}

//--------------------------------------------------------------
/**
 * @brief   AWAZA_SAVE�p�����[�^�X�V����
 * @param   wp		�Z���ʃp�����[�^�ւ̃|�C���^
 */
//--------------------------------------------------------------
static void AWAZA_SaveParamUpdate(AWAZA_PARAM *wp)
{
	int i;
	
	for(i = 0; i < BREEDER_MAX; i++){
		wp->save[i].waza_repeat = 0;
		wp->save[i].twice_now_apno = wp->personal[i].twice_next_apno;
	}
}


//==============================================================================
//	�Z���ʃV�[�P���X
//==============================================================================
//--------------------------------------------------------------
/**
 * @brief   ���̃^�[���ł̏��Ԃ��ŏ��ɂȂ�
 *
 * @param   apw				���Z�͕���Ǘ����[�N�ւ̃|�C���^
 * @param   wp				�Z���ʃp�����[�^�����̃|�C���^
 * @param   appeal_breeder	�A�s�[�����̃u���[�_�[�ԍ�
 * @param   kouka_breeder	���̋Z���ʂ𔭓����Ă���u���[�_�[�̔ԍ�
 * @param   pos				���Ԗڂ̃A�s�[����(appeal_breeder��)
 *
 * @retval  TRUE:���ʔ����B�@FALSE:���ʕs��
 */
//--------------------------------------------------------------
static int Kouka_NextFirst(ACTIN_PROC_WORK *apw, AWAZA_PARAM *wp, int appeal_breeder, int kouka_breeder, int pos)
{
	u8 sort[BREEDER_MAX];
	int i, t, first_breeder;
	
	first_breeder = BREEDER_MAX;
	for(i = 0; i < BREEDER_MAX; i++){
		if(wp->personal[i].next_sort == AWK_SORT_NONE){
			sort[i] = 0xff;
		}
		else{
			if(wp->personal[i].next_sort == AWK_SORT_SPECIFY_FIRST 
					&& wp->personal[i].next_pos == 0){
				first_breeder = i;	//����������ɂ��̋Z�Ŏ�1�Ԃ𔭓����Ă����u���[�_�[
			}
			sort[i] = wp->personal[i].next_pos;
		}
	}
	
	sort[kouka_breeder] = 0xff;	//�����̏��͋󔒂ɂ��Ă���
	
	for(i = 0; i < BREEDER_MAX; i++){
		for(t = 0; t < BREEDER_MAX; t++){
			if(sort[t] != 0xff){
				if(i == sort[t] && sort[t] == wp->personal[t].next_pos){
					sort[t]++;
					break;
				}
			}
		}
		if(t == BREEDER_MAX){
			break;
		}
	}

	for(i = 0; i < BREEDER_MAX; i++){
		if(sort[i] != 0xff){
			wp->personal[i].next_pos = sort[i];
			OS_TPrintf("�Z���ʂ̉e���Ńu���[�_�[%d�͎�%d��\n", i, sort[i]);
		}
	}
	wp->personal[kouka_breeder].next_sort = AWK_SORT_SPECIFY_FIRST;
	wp->personal[kouka_breeder].next_pos = 0;
	OS_TPrintf("�Z���ʂɂ��u���[�_�[%d�͎�0��\n", kouka_breeder);
	
	if(first_breeder != BREEDER_MAX){
		AWAZA_MsgParamSet(&wp->personal[kouka_breeder], wp->personal[kouka_breeder].apno, 
			KOUKA_MSGID_B, kouka_breeder, first_breeder, TAG_NULL, TAG_NULL);
	}
	else{
		AWAZA_MsgParamSet(&wp->personal[kouka_breeder], wp->personal[kouka_breeder].apno, 
			KOUKA_MSGID_A, kouka_breeder, TAG_NULL, TAG_NULL, TAG_NULL);
	}
	return TRUE;
}

//--------------------------------------------------------------
/**
 * @brief   ���̃^�[���ł̏��Ԃ��Ō�ɂȂ�
 *
 * @param   apw				���Z�͕���Ǘ����[�N�ւ̃|�C���^
 * @param   wp				�Z���ʃp�����[�^�����̃|�C���^
 * @param   appeal_breeder	�A�s�[�����̃u���[�_�[�ԍ�
 * @param   kouka_breeder	���̋Z���ʂ𔭓����Ă���u���[�_�[�̔ԍ�
 * @param   pos				���Ԗڂ̃A�s�[����(appeal_breeder��)
 *
 * @retval  TRUE:���ʔ����B�@FALSE:���ʕs��
 */
//--------------------------------------------------------------
static int Kouka_NextEnd(ACTIN_PROC_WORK *apw, AWAZA_PARAM *wp, int appeal_breeder, int kouka_breeder, int pos)
{
	s8 i, t;
	u8 sort[BREEDER_MAX];
	int before_end_breeder;
	
	before_end_breeder = BREEDER_MAX;
	for(i = 0; i < BREEDER_MAX; i++){
		if(wp->personal[i].next_sort == AWK_SORT_NONE){
			sort[i] = 0xff;
		}
		else{
			if(wp->personal[i].next_sort == AWK_SORT_SPECIFY_END
					&& wp->personal[i].next_pos == BREEDER_MAX - 1){
				before_end_breeder = i;	//����������ɂ��̋Z�Ŏ��Ō�𔭓����Ă����u���[�_�[
			}
			sort[i] = wp->personal[i].next_pos;
		}
	}

	sort[kouka_breeder] = 0xff;	//�����̏��͋󔒂ɂ��Ă���

	for(i = BREEDER_MAX-1; i > -1; i--){
		for(t = 0; t < BREEDER_MAX; t++){
			if(sort[t] != 0xff){
				if(i == sort[t] && sort[t] == wp->personal[t].next_pos){
					sort[t]--;
					break;
				}
			}
		}
		if(t == BREEDER_MAX){
			break;
		}
	}

	for(i = 0; i < BREEDER_MAX; i++){
		if(sort[i] != 0xff){
			wp->personal[i].next_pos = sort[i];
			OS_TPrintf("�Z���ʂ̉e���Ńu���[�_�[%d�͎�%d��\n", i, sort[i]);
		}
	}
	wp->personal[kouka_breeder].next_sort = AWK_SORT_SPECIFY_END;
	wp->personal[kouka_breeder].next_pos = BREEDER_MAX - 1;
	OS_TPrintf("�Z���ʂɂ��u���[�_�[%d�͎��Ō�\n", kouka_breeder);

	if(before_end_breeder == BREEDER_MAX){
		AWAZA_MsgParamSet(&wp->personal[kouka_breeder], wp->personal[kouka_breeder].apno, 
			KOUKA_MSGID_A, kouka_breeder, TAG_NULL, TAG_NULL, TAG_NULL);
	}
	else{
		AWAZA_MsgParamSet(&wp->personal[kouka_breeder], wp->personal[kouka_breeder].apno, 
			KOUKA_MSGID_B, kouka_breeder, before_end_breeder, TAG_NULL, TAG_NULL);
	}

	return TRUE;
}

//--------------------------------------------------------------
/**
 * @brief   �R���̎w������閈�Ɂ{�Q
 *
 * @param   apw				���Z�͕���Ǘ����[�N�ւ̃|�C���^
 * @param   wp				�Z���ʃp�����[�^�����̃|�C���^
 * @param   appeal_breeder	�A�s�[�����̃u���[�_�[�ԍ�
 * @param   kouka_breeder	���̋Z���ʂ𔭓����Ă���u���[�_�[�̔ԍ�
 * @param   pos				���Ԗڂ̃A�s�[����(appeal_breeder��)
 *
 * @retval  TRUE:���ʔ����B�@FALSE:���ʕs��
 */
//--------------------------------------------------------------
static int Kouka_JudgeSufferAdd(ACTIN_PROC_WORK *apw, AWAZA_PARAM *wp, int appeal_breeder, int kouka_breeder, int pos)
{
	int msg_type;
	
	wp->personal[kouka_breeder].my_effective_ap += 
		wp->personal[kouka_breeder].judge_suffer * KOUKA_JUDGE_SUFFER_ADD;
	
	switch(wp->personal[kouka_breeder].judge_suffer){
	case 0:
		msg_type = KOUKA_MSGID_A;
		break;
	case 1:
		msg_type = KOUKA_MSGID_B;
		break;
	case 2:
		msg_type = KOUKA_MSGID_C;
		break;
	default:
		msg_type = KOUKA_MSGID_D;
		break;
	}
	AWAZA_MsgParamSet(&wp->personal[kouka_breeder], wp->personal[kouka_breeder].apno, 
		msg_type, kouka_breeder, TAG_NULL, TAG_NULL, TAG_NULL);
	
	OS_TPrintf("�R���̔��l����%d, ���Z�|�C���g��%d\n", wp->personal[kouka_breeder].judge_suffer,
		wp->personal[kouka_breeder].judge_suffer * APPEAL_ICON_ONE_POINT);
	return TRUE;
}

//--------------------------------------------------------------
/**
 * @brief   ����オ������{2
 *
 * @param   apw				���Z�͕���Ǘ����[�N�ւ̃|�C���^
 * @param   wp				�Z���ʃp�����[�^�����̃|�C���^
 * @param   appeal_breeder	�A�s�[�����̃u���[�_�[�ԍ�
 * @param   kouka_breeder	���̋Z���ʂ𔭓����Ă���u���[�_�[�̔ԍ�
 * @param   pos				���Ԗڂ̃A�s�[����(appeal_breeder��)
 *
 * @retval  TRUE:���ʔ����B�@FALSE:���ʕs��
 */
//--------------------------------------------------------------
static int Kouka_VoltageUpAdd(ACTIN_PROC_WORK *apw, AWAZA_PARAM *wp, int appeal_breeder, int kouka_breeder, int pos)
{
	int judge_no;
	int voltage_addsub;
	
	judge_no = wp->personal[kouka_breeder].judge_no;
	voltage_addsub = ACALC_VoltageUpDownCheck(apw->consys->c_game.type, 
		wp->personal[kouka_breeder].wazano, judge_no, apw->consys->c_game.special_judge_no);
//	if(wp->voltage_before[judge_no] > wp->voltage_after[judge_no]){
	if(voltage_addsub > 0 && wp->personal[kouka_breeder].invalid_voltage_up == 0){
		wp->personal[kouka_breeder].my_effective_ap += KOUKA_VOLTAGE_UP_ADD;

		AWAZA_MsgParamSet(&wp->personal[kouka_breeder], wp->personal[kouka_breeder].apno, 
			KOUKA_MSGID_A, kouka_breeder, TAG_NULL, wp->personal[kouka_breeder].wazano, TAG_NULL);
		
		OS_TPrintf("����オ�����̂Ō��ʔ���\n");
		return TRUE;
	}

	OS_TPrintf("����オ��Ȃ������̂Ŏ��s\n");
	return FALSE;
}

//--------------------------------------------------------------
/**
 * @brief   ������ʂȂ�
 *
 * @param   apw				���Z�͕���Ǘ����[�N�ւ̃|�C���^
 * @param   wp				�Z���ʃp�����[�^�����̃|�C���^
 * @param   appeal_breeder	�A�s�[�����̃u���[�_�[�ԍ�
 * @param   kouka_breeder	���̋Z���ʂ𔭓����Ă���u���[�_�[�̔ԍ�
 * @param   pos				���Ԗڂ̃A�s�[����(appeal_breeder��)
 *
 * @retval  TRUE:���ʔ����B�@FALSE:���ʕs��
 */
//--------------------------------------------------------------
static int Kouka_Null(ACTIN_PROC_WORK *apw, AWAZA_PARAM *wp, int appeal_breeder, int kouka_breeder, int pos)
{
	OS_TPrintf("������ʉ����Ȃ�\n");
	return TRUE;
}

//--------------------------------------------------------------
/**
 * @brief   �R���̎w�������Ȃ�������{3
 *
 * @param   apw				���Z�͕���Ǘ����[�N�ւ̃|�C���^
 * @param   wp				�Z���ʃp�����[�^�����̃|�C���^
 * @param   appeal_breeder	�A�s�[�����̃u���[�_�[�ԍ�
 * @param   kouka_breeder	���̋Z���ʂ𔭓����Ă���u���[�_�[�̔ԍ�
 * @param   pos				���Ԗڂ̃A�s�[����(appeal_breeder��)
 *
 * @retval  TRUE:���ʔ����B�@FALSE:���ʕs��
 */
//--------------------------------------------------------------
static int Kouka_NoneJudgeSufferAdd(ACTIN_PROC_WORK *apw, AWAZA_PARAM *wp, int appeal_breeder, int kouka_breeder, int pos)
{
	if(wp->personal[kouka_breeder].judge_suffer == 0){
		wp->personal[kouka_breeder].my_effective_ap += KOUKA_NONE_JUDGE_SUFFER_ADD;
		AWAZA_MsgParamSet(&wp->personal[kouka_breeder], wp->personal[kouka_breeder].apno, 
			KOUKA_MSGID_A, kouka_breeder, TAG_NULL, TAG_NULL, TAG_NULL);

		OS_TPrintf("�w�������Ȃ������̂Ō��ʔ���\n");
	}
	else{
		AWAZA_MsgParamSet(&wp->personal[kouka_breeder], wp->personal[kouka_breeder].apno, 
			KOUKA_MSGID_B, kouka_breeder, TAG_NULL, TAG_NULL, TAG_NULL);
		
		OS_TPrintf("�w��������Ă���̂Ŏ��s\n");
	}
	return TRUE;
}

//--------------------------------------------------------------
/**
 * @brief   2��A���g�p�\
 *
 * @param   apw				���Z�͕���Ǘ����[�N�ւ̃|�C���^
 * @param   wp				�Z���ʃp�����[�^�����̃|�C���^
 * @param   appeal_breeder	�A�s�[�����̃u���[�_�[�ԍ�
 * @param   kouka_breeder	���̋Z���ʂ𔭓����Ă���u���[�_�[�̔ԍ�
 * @param   pos				���Ԗڂ̃A�s�[����(appeal_breeder��)
 *
 * @retval  TRUE:���ʔ����B�@FALSE:���ʕs��
 */
//--------------------------------------------------------------
static int Kouka_Continuation(ACTIN_PROC_WORK *apw, AWAZA_PARAM *wp, int appeal_breeder, int kouka_breeder, int pos)
{
	if(wp->personal[kouka_breeder].wazano != apw->a_game.waza_history[kouka_breeder]){
		wp->save[kouka_breeder].waza_repeat = wp->personal[kouka_breeder].wazano;
		AWAZA_MsgParamSet(&wp->personal[kouka_breeder], wp->personal[kouka_breeder].apno, 
			KOUKA_MSGID_A, kouka_breeder, TAG_NULL, TAG_NULL, TAG_NULL);
		OS_TPrintf("���^�[���������Z�g�pOK\n");
		return TRUE;
	}
	
	OS_TPrintf("���ɘA���œ����Z���o���Ă���̂ŘA���Z���ʎ��s\n");
	return FALSE;
}

//--------------------------------------------------------------
/**
 * @brief   �{���e�[�W���́����ǉ�
 *
 * @param   apw				���Z�͕���Ǘ����[�N�ւ̃|�C���^
 * @param   wp				�Z���ʃp�����[�^�����̃|�C���^
 * @param   appeal_breeder	�A�s�[�����̃u���[�_�[�ԍ�
 * @param   kouka_breeder	���̋Z���ʂ𔭓����Ă���u���[�_�[�̔ԍ�
 * @param   pos				���Ԗڂ̃A�s�[����(appeal_breeder��)
 *
 * @retval  TRUE:���ʔ����B�@FALSE:���ʕs��
 */
//--------------------------------------------------------------
static int Kouka_VoltageAddAP(ACTIN_PROC_WORK *apw, AWAZA_PARAM *wp, int appeal_breeder, int kouka_breeder, int pos)
{
	int judge_no, add_ap;
	
	judge_no = wp->personal[kouka_breeder].judge_no;
	if(1){	//�{���e�[�W0�ł����b�Z�[�W�o���悤�ɂ���	wp->voltage_before[judge_no] > 0){
		add_ap = wp->voltage_before[judge_no];
		wp->personal[kouka_breeder].my_effective_ap += add_ap;
		AWAZA_MsgParamSet(&wp->personal[kouka_breeder], wp->personal[kouka_breeder].apno, 
			KOUKA_MSGID_A, TAG_NULL, TAG_NULL, TAG_NULL, add_ap / VOLTAGE_ONE_POINT);
//		OS_TPrintf("�{���e�[�W1�ȏ�Ȃ̂Ō��ʔ���\n");
		return TRUE;
	}

	OS_TPrintf("�{���e�[�W0�Ȃ̂Ŏ��s\n");
	return FALSE;
}

//--------------------------------------------------------------
/**
 * @brief   �S����������灙���{3
 *
 * @param   apw				���Z�͕���Ǘ����[�N�ւ̃|�C���^
 * @param   wp				�Z���ʃp�����[�^�����̃|�C���^
 * @param   appeal_breeder	�A�s�[�����̃u���[�_�[�ԍ�
 * @param   kouka_breeder	���̋Z���ʂ𔭓����Ă���u���[�_�[�̔ԍ�
 * @param   pos				���Ԗڂ̃A�s�[����(appeal_breeder��)
 *
 * @retval  TRUE:���ʔ����B�@FALSE:���ʕs��
 */
//--------------------------------------------------------------
static int Kouka_AllSufferAdd(ACTIN_PROC_WORK *apw, AWAZA_PARAM *wp, int appeal_breeder, int kouka_breeder, int pos)
{
	if(wp->personal[kouka_breeder].judge_suffer == BREEDER_MAX - 1){
		wp->personal[kouka_breeder].my_effective_ap += KOUKA_ALL_SUFFER_ADD;
		AWAZA_MsgParamSet(&wp->personal[kouka_breeder], wp->personal[kouka_breeder].apno, 
			KOUKA_MSGID_A, kouka_breeder, TAG_NULL, TAG_NULL, TAG_NULL);

		OS_TPrintf("�S���̎w����������̂Ō��ʔ���\n");
	}
	else{
		AWAZA_MsgParamSet(&wp->personal[kouka_breeder], wp->personal[kouka_breeder].apno, 
			KOUKA_MSGID_B, kouka_breeder, TAG_NULL, TAG_NULL, TAG_NULL);

		OS_TPrintf("�S�����̎w��������Ȃ������̂Ŏ��s�B������l��(��������)��%d\n", 
			wp->personal[kouka_breeder].judge_suffer);
	}
	return TRUE;
}

//--------------------------------------------------------------
/**
 * @brief   �S���̃{���e�[�W��1������
 *
 * @param   apw				���Z�͕���Ǘ����[�N�ւ̃|�C���^
 * @param   wp				�Z���ʃp�����[�^�����̃|�C���^
 * @param   appeal_breeder	�A�s�[�����̃u���[�_�[�ԍ�
 * @param   kouka_breeder	���̋Z���ʂ𔭓����Ă���u���[�_�[�̔ԍ�
 * @param   pos				���Ԗڂ̃A�s�[����(appeal_breeder��)
 *
 * @retval  TRUE:���ʔ����B�@FALSE:���ʕs��
 */
//--------------------------------------------------------------
static int Kouka_AllVoltageSub(ACTIN_PROC_WORK *apw, AWAZA_PARAM *wp, int appeal_breeder, int kouka_breeder, int pos)
{
	int judge_no;
	
	if(wp->personal[kouka_breeder].invalid_voltage_down == 1){
		OS_TPrintf("�{���e�[�W���������̌��ʔ������ׁ̈A���s\n");
		return FALSE;
	}
	for(judge_no = 0; judge_no < JUDGE_MAX; judge_no++){
		if(wp->voltage_after[judge_no] != 0){
			break;
		}
	}
	if(judge_no == JUDGE_MAX){
		OS_TPrintf("�R���S���̃{���e�[�W���Ȃ����߁A���ʎ��s\n");
		return FALSE;
	}
	
	wp->personal[kouka_breeder].voltage_all_down = 1;
	for(judge_no = 0; judge_no < JUDGE_MAX; judge_no++){
		if(wp->voltage_after[judge_no] > 0){
			wp->voltage_after[judge_no] += KOUKA_VOLTAGE_ALL_DOWN;
		}
	}
	
	AWAZA_MsgParamSet(&wp->personal[kouka_breeder], wp->personal[kouka_breeder].apno, 
		KOUKA_MSGID_A, TAG_NULL, TAG_NULL, TAG_NULL, TAG_NULL);
	
	OS_TPrintf("�R���S���̃{���e�[�W����������ʔ���\n");
	return TRUE;
}

//--------------------------------------------------------------
/**
* @brief   ���̃^�[���Ł���2�{
 *
 * @param   apw				���Z�͕���Ǘ����[�N�ւ̃|�C���^
 * @param   wp				�Z���ʃp�����[�^�����̃|�C���^
 * @param   appeal_breeder	�A�s�[�����̃u���[�_�[�ԍ�
 * @param   kouka_breeder	���̋Z���ʂ𔭓����Ă���u���[�_�[�̔ԍ�
 * @param   pos				���Ԗڂ̃A�s�[����(appeal_breeder��)
 *
 * @retval  TRUE:���ʔ����B�@FALSE:���ʕs��
 */
//--------------------------------------------------------------
static int Kouka_NextTurnTwice(ACTIN_PROC_WORK *apw, AWAZA_PARAM *wp, int appeal_breeder, int kouka_breeder, int pos)
{
	wp->personal[kouka_breeder].twice_next_apno = wp->personal[kouka_breeder].apno;
	OS_TPrintf("���̃^�[��2�{�t���O�Z�b�g����\n");
	return TRUE;
}

//--------------------------------------------------------------
/**
 * @brief   �{���e�[�W�̑�������~
 *
 * @param   apw				���Z�͕���Ǘ����[�N�ւ̃|�C���^
 * @param   wp				�Z���ʃp�����[�^�����̃|�C���^
 * @param   appeal_breeder	�A�s�[�����̃u���[�_�[�ԍ�
 * @param   kouka_breeder	���̋Z���ʂ𔭓����Ă���u���[�_�[�̔ԍ�
 * @param   pos				���Ԗڂ̃A�s�[����(appeal_breeder��)
 *
 * @retval  TRUE:���ʔ����B�@FALSE:���ʕs��
 */
//--------------------------------------------------------------
static int Kouka_VoltageUpStop(ACTIN_PROC_WORK *apw, AWAZA_PARAM *wp, int appeal_breeder, int kouka_breeder, int pos)
{
	int i;
	
	for(i = pos; i < BREEDER_MAX; i++){
		wp->personal[apw->a_game.breeder_sort[i]].invalid_voltage_up = 1;
		OS_TPrintf("%d�ԃu���[�_�[�̃{���e�[�W�����Ȃ�\n", apw->a_game.breeder_sort[i]);
	}
	AWAZA_MsgParamSet(&wp->personal[kouka_breeder], wp->personal[kouka_breeder].apno, 
		KOUKA_MSGID_A, TAG_NULL, TAG_NULL, TAG_NULL, TAG_NULL);
	return TRUE;
}

//--------------------------------------------------------------
/**
 * @brief   �����̑O�ɉ��Z�����|�P�����̃{���e�[�W���}�b�N�X�ɂȂ������A�{���e�[�W���݂̂��炦��
 *
 * @param   apw				���Z�͕���Ǘ����[�N�ւ̃|�C���^
 * @param   wp				�Z���ʃp�����[�^�����̃|�C���^
 * @param   appeal_breeder	�A�s�[�����̃u���[�_�[�ԍ�
 * @param   kouka_breeder	���̋Z���ʂ𔭓����Ă���u���[�_�[�̔ԍ�
 * @param   pos				���Ԗڂ̃A�s�[����(appeal_breeder��)
 *
 * @retval  TRUE:���ʔ����B�@FALSE:���ʕs��
 */
//--------------------------------------------------------------
static int Kouka_FrontSame(ACTIN_PROC_WORK *apw, AWAZA_PARAM *wp, int appeal_breeder, int kouka_breeder, int pos)
{
	int front_breeder;
	
	if(pos == 0){
		OS_TPrintf("�擪�ׁ̈A�Z���s\n");
		return FALSE;
	}

	front_breeder = apw->a_game.breeder_sort[pos - 1];

	if(wp->personal[front_breeder].voltage_add_ap == 0){
		OS_TPrintf("�O�̐l���{���e�[�W�|�C���g���擾���Ă��Ȃ��̂Ŏ��s\n");
		return FALSE;
	}
	
	wp->personal[kouka_breeder].my_effective_ap += wp->personal[front_breeder].voltage_add_ap;
	AWAZA_MsgParamSet(&wp->personal[kouka_breeder], wp->personal[kouka_breeder].apno, 
		KOUKA_MSGID_A, kouka_breeder, front_breeder, TAG_NULL, TAG_NULL);
	OS_TPrintf("�u���[�_�[No%d�̌��ʂ��R�s�[���܂����B���ZAP��%d\n", 
		front_breeder, wp->personal[kouka_breeder].my_effective_ap);
	return TRUE;
}

//--------------------------------------------------------------
/**
 * @brief   ���̃^�[���ŏ��Ԃ������_��
 *
 * @param   apw				���Z�͕���Ǘ����[�N�ւ̃|�C���^
 * @param   wp				�Z���ʃp�����[�^�����̃|�C���^
 * @param   appeal_breeder	�A�s�[�����̃u���[�_�[�ԍ�
 * @param   kouka_breeder	���̋Z���ʂ𔭓����Ă���u���[�_�[�̔ԍ�
 * @param   pos				���Ԗڂ̃A�s�[����(appeal_breeder��)
 *
 * @retval  TRUE:���ʔ����B�@FALSE:���ʕs��
 */
//--------------------------------------------------------------
static int Kouka_NextRandom(ACTIN_PROC_WORK *apw, AWAZA_PARAM *wp, int appeal_breeder, int kouka_breeder, int pos)
{
	s8 i, t;
	u8 sort[BREEDER_MAX];
	u8 brdno[BREEDER_MAX];
	u8 temp, temp2;
	
	for(i = 0; i < BREEDER_MAX; i++){
		sort[i] = i;
		brdno[i] = i;
	}

	for(i = 0; i < BREEDER_MAX; i++){
		temp = contest_rand(apw->consys) % (BREEDER_MAX - i);
		temp2 = temp;
		for(t = 0; t < BREEDER_MAX; t++){
			if(brdno[t] != 0xff){
				if(temp2 == 0){
					sort[t] = i;
					brdno[t] = 0xff;
					break;
				}
				else
					temp2--;
			}
		}
	}

	for(i = 0; i < BREEDER_MAX; i++){
		wp->personal[i].next_sort = AWK_SORT_RANDOM;
		wp->personal[i].next_pos = sort[i];
		OS_TPrintf("�u���[�_�[%d�́A��%d�Ԗ�\n", i, sort[i]);
	}
	
	AWAZA_MsgParamSet(&wp->personal[kouka_breeder], wp->personal[kouka_breeder].apno, 
		KOUKA_MSGID_A, TAG_NULL, TAG_NULL, TAG_NULL, TAG_NULL);
	return TRUE;
}

//--------------------------------------------------------------
/**
 * @brief   �Ō�̃A�s�[���Ő���2�{
 *
 * @param   apw				���Z�͕���Ǘ����[�N�ւ̃|�C���^
 * @param   wp				�Z���ʃp�����[�^�����̃|�C���^
 * @param   appeal_breeder	�A�s�[�����̃u���[�_�[�ԍ�
 * @param   kouka_breeder	���̋Z���ʂ𔭓����Ă���u���[�_�[�̔ԍ�
 * @param   pos				���Ԗڂ̃A�s�[����(appeal_breeder��)
 *
 * @retval  TRUE:���ʔ����B�@FALSE:���ʕs��
 */
//--------------------------------------------------------------
static int Kouka_EndTwice(ACTIN_PROC_WORK *apw, AWAZA_PARAM *wp, int appeal_breeder, int kouka_breeder, int pos)
{
	if(pos == BREEDER_MAX - 1){
		//��{�v�ZAP�l���Z���ʑ����Ƃ��đ�������
		wp->personal[kouka_breeder].my_effective_ap += wp->personal[kouka_breeder].app_total;
		AWAZA_MsgParamSet(&wp->personal[kouka_breeder], wp->personal[kouka_breeder].apno, 
			KOUKA_MSGID_A, TAG_NULL, TAG_NULL, TAG_NULL, 
			wp->personal[kouka_breeder].app_total / APPEAL_ICON_ONE_POINT);
		OS_TPrintf("2�{���ʔ����B��{�v�ZAP�l��%d\n", 
			wp->personal[kouka_breeder].app_total / APPEAL_ICON_ONE_POINT);
		return TRUE;
	}
	
	OS_TPrintf("���Ԃ��Ō�ł͂Ȃ��ׁA���s�B�A�s�[�����ԁ�%d\n", pos);
	return FALSE;
}

//--------------------------------------------------------------
/**
 * @brief   �{���e�[�W���Ⴂ�قǁ������炦��
 *
 * @param   apw				���Z�͕���Ǘ����[�N�ւ̃|�C���^
 * @param   wp				�Z���ʃp�����[�^�����̃|�C���^
 * @param   appeal_breeder	�A�s�[�����̃u���[�_�[�ԍ�
 * @param   kouka_breeder	���̋Z���ʂ𔭓����Ă���u���[�_�[�̔ԍ�
 * @param   pos				���Ԗڂ̃A�s�[����(appeal_breeder��)
 *
 * @retval  TRUE:���ʔ����B�@FALSE:���ʕs��
 */
//--------------------------------------------------------------
static int Kouka_VoltageLevelAdd(ACTIN_PROC_WORK *apw, AWAZA_PARAM *wp, int appeal_breeder, int kouka_breeder, int pos)
{
	int voltage_level, judge_no;
	static const u8 VoltageAddData[] = {
		VOLTAGE_ONE_POINT * 4,
		VOLTAGE_ONE_POINT * 3,
		VOLTAGE_ONE_POINT * 2,
		VOLTAGE_ONE_POINT * 1,
		VOLTAGE_ONE_POINT * 0,
		VOLTAGE_ONE_POINT * 0,	//�{���e�[�W�T�̎�(���肦�Ȃ����ǈꉞ�f�[�^�͖��߂Ƃ�)
	};
	
	judge_no = wp->personal[kouka_breeder].judge_no;
	voltage_level = wp->voltage_before[judge_no] / VOLTAGE_ONE_POINT;
	wp->personal[kouka_breeder].my_effective_ap += VoltageAddData[voltage_level];
	
	AWAZA_MsgParamSet(&wp->personal[kouka_breeder], wp->personal[kouka_breeder].apno, 
		KOUKA_MSGID_A, TAG_NULL, TAG_NULL, TAG_NULL, 
		VoltageAddData[voltage_level] / VOLTAGE_ONE_POINT);
	
	OS_TPrintf("���݂̃{���e�[�W=%d, ���ZAP=%d\n", voltage_level, VoltageAddData[voltage_level]);
	return TRUE;
}

//--------------------------------------------------------------
/**
 * @brief   �ŏ��̃A�s�[���Ő����{�Q
 *
 * @param   apw				���Z�͕���Ǘ����[�N�ւ̃|�C���^
 * @param   wp				�Z���ʃp�����[�^�����̃|�C���^
 * @param   appeal_breeder	�A�s�[�����̃u���[�_�[�ԍ�
 * @param   kouka_breeder	���̋Z���ʂ𔭓����Ă���u���[�_�[�̔ԍ�
 * @param   pos				���Ԗڂ̃A�s�[����(appeal_breeder��)
 *
 * @retval  TRUE:���ʔ����B�@FALSE:���ʕs��
 */
//--------------------------------------------------------------
static int Kouka_FirstAdd(ACTIN_PROC_WORK *apw, AWAZA_PARAM *wp, int appeal_breeder, int kouka_breeder, int pos)
{
	if(pos == 0){
		wp->personal[kouka_breeder].my_effective_ap += APPEAL_ICON_ONE_POINT * 2;
		AWAZA_MsgParamSet(&wp->personal[kouka_breeder], wp->personal[kouka_breeder].apno, 
			KOUKA_MSGID_A, TAG_NULL, TAG_NULL, TAG_NULL, TAG_NULL);
		OS_TPrintf("�ŏ��̃A�s�[���Ȃ̂Ō��ʔ����B�A�s�[�����ԁ�%d\n", pos);
		return TRUE;
	}

	OS_TPrintf("�ŏ��ł͂Ȃ��̂ŁA���s�B�A�s�[�����ԁ�%d\n", pos);
	return FALSE;
}

//--------------------------------------------------------------
/**
 * @brief   �Ō�̃A�s�[���Ő����{�Q
 *
 * @param   apw				���Z�͕���Ǘ����[�N�ւ̃|�C���^
 * @param   wp				�Z���ʃp�����[�^�����̃|�C���^
 * @param   appeal_breeder	�A�s�[�����̃u���[�_�[�ԍ�
 * @param   kouka_breeder	���̋Z���ʂ𔭓����Ă���u���[�_�[�̔ԍ�
 * @param   pos				���Ԗڂ̃A�s�[����(appeal_breeder��)
 *
 * @retval  TRUE:���ʔ����B�@FALSE:���ʕs��
 */
//--------------------------------------------------------------
static int Kouka_EndAdd(ACTIN_PROC_WORK *apw, AWAZA_PARAM *wp, int appeal_breeder, int kouka_breeder, int pos)
{
	if(pos == BREEDER_MAX - 1){
		wp->personal[kouka_breeder].my_effective_ap += APPEAL_ICON_ONE_POINT * 2;
		AWAZA_MsgParamSet(&wp->personal[kouka_breeder], wp->personal[kouka_breeder].apno, 
			KOUKA_MSGID_A, TAG_NULL, TAG_NULL, TAG_NULL, TAG_NULL);
		OS_TPrintf("�Ō�̃A�s�[���Ȃ̂Ō��ʔ����B�A�s�[�����ԁ�%d\n", pos);
		return TRUE;
	}

	OS_TPrintf("�Ō�ł͂Ȃ��̂ŁA���s�B�A�s�[�����ԁ�%d\n", pos);
	return FALSE;
}

//--------------------------------------------------------------
/**
 * @brief   �{���e�[�W�̒ቺ����~
 *
 * @param   apw				���Z�͕���Ǘ����[�N�ւ̃|�C���^
 * @param   wp				�Z���ʃp�����[�^�����̃|�C���^
 * @param   appeal_breeder	�A�s�[�����̃u���[�_�[�ԍ�
 * @param   kouka_breeder	���̋Z���ʂ𔭓����Ă���u���[�_�[�̔ԍ�
 * @param   pos				���Ԗڂ̃A�s�[����(appeal_breeder��)
 *
 * @retval  TRUE:���ʔ����B�@FALSE:���ʕs��
 */
//--------------------------------------------------------------
static int Kouka_VoltageSubStop(ACTIN_PROC_WORK *apw, AWAZA_PARAM *wp, int appeal_breeder, int kouka_breeder, int pos)
{
	int i;
	
	for(i = pos; i < BREEDER_MAX; i++){
		wp->personal[apw->a_game.breeder_sort[i]].invalid_voltage_down = 1;
		OS_TPrintf("%d�ԃu���[�_�[�̃{���e�[�W�����Ȃ�\n", apw->a_game.breeder_sort[i]);
	}
	AWAZA_MsgParamSet(&wp->personal[kouka_breeder], wp->personal[kouka_breeder].apno, 
		KOUKA_MSGID_A, TAG_NULL, TAG_NULL, TAG_NULL, TAG_NULL);
	return TRUE;
}

//--------------------------------------------------------------
/**
 * @brief   �Q�C�����ă{���e�[�W���オ��Ɓ����u+�R�v
 *
 * @param   apw				���Z�͕���Ǘ����[�N�ւ̃|�C���^
 * @param   wp				�Z���ʃp�����[�^�����̃|�C���^
 * @param   appeal_breeder	�A�s�[�����̃u���[�_�[�ԍ�
 * @param   kouka_breeder	���̋Z���ʂ𔭓����Ă���u���[�_�[�̔ԍ�
 * @param   pos				���Ԗڂ̃A�s�[����(appeal_breeder��)
 *
 * @retval  TRUE:���ʔ����B�@FALSE:���ʕs��
 */
//--------------------------------------------------------------
static int Kouka_ContinuationVoltageAdd(ACTIN_PROC_WORK *apw, AWAZA_PARAM *wp, int appeal_breeder, int kouka_breeder, int pos)
{
	int front_breeder, my_up, front_up;
	
	if(pos == 0){
		OS_TPrintf("�擪�ׁ̈A�Z���s\n");
		return FALSE;
	}
	
	front_breeder = apw->a_game.breeder_sort[pos - 1];
	
	if(wp->personal[kouka_breeder].invalid_voltage_up != 0
			|| wp->personal[front_breeder].invalid_voltage_up != 0){
		OS_TPrintf("�{���e�[�W���������̈׎��s\n");
		return FALSE;
	}
	
	my_up = ACALC_VoltageUpDownCheck(apw->consys->c_game.type, 
		wp->personal[kouka_breeder].wazano, wp->personal[kouka_breeder].judge_no, 
		apw->consys->c_game.special_judge_no);
	front_up = ACALC_VoltageUpDownCheck(apw->consys->c_game.type, 
		wp->personal[front_breeder].wazano, wp->personal[front_breeder].judge_no, 
		apw->consys->c_game.special_judge_no);
	
	if(front_up > 0 && my_up > 0){
		wp->personal[kouka_breeder].my_effective_ap += KOUKA_CONTINUATION_VOLTAGE_ADD;
		AWAZA_MsgParamSet(&wp->personal[kouka_breeder], wp->personal[kouka_breeder].apno, 
			KOUKA_MSGID_A, kouka_breeder, front_breeder, TAG_NULL, TAG_NULL);
		
		OS_TPrintf("�A���{���e�[�WUP�Ȃ̂Ō��ʔ���\n");
		return TRUE;
	}

	OS_TPrintf("�A��UP���Ȃ������̂Ŏ��s\n");
	return FALSE;
}

//--------------------------------------------------------------
/**
 * @brief   ���Ԗڂɉ��Z���邩�ŕ]�����ς��
 *
 * @param   apw				���Z�͕���Ǘ����[�N�ւ̃|�C���^
 * @param   wp				�Z���ʃp�����[�^�����̃|�C���^
 * @param   appeal_breeder	�A�s�[�����̃u���[�_�[�ԍ�
 * @param   kouka_breeder	���̋Z���ʂ𔭓����Ă���u���[�_�[�̔ԍ�
 * @param   pos				���Ԗڂ̃A�s�[����(appeal_breeder��)
 *
 * @retval  TRUE:���ʔ����B�@FALSE:���ʕs��
 */
//--------------------------------------------------------------
static int Kouka_SortAdd(ACTIN_PROC_WORK *apw, AWAZA_PARAM *wp, int appeal_breeder, int kouka_breeder, int pos)
{
	int msg_type;
	
	wp->personal[kouka_breeder].my_effective_ap += Kouka_SortAddPoint[pos];
	switch(pos){
	case 0:
		msg_type = KOUKA_MSGID_A;
		break;
	case 1:
		msg_type = KOUKA_MSGID_B;
		break;
	case 2:
		msg_type = KOUKA_MSGID_C;
		break;
	case 3:
	default:
		msg_type = KOUKA_MSGID_D;
		break;
	}
	AWAZA_MsgParamSet(&wp->personal[kouka_breeder], wp->personal[kouka_breeder].apno, 
		msg_type, kouka_breeder, TAG_NULL, TAG_NULL, TAG_NULL);
	
	OS_TPrintf("���ԁ�%d, ���Z�|�C���g��%d\n", pos, Kouka_SortAddPoint[pos]);
	return TRUE;
}

//--------------------------------------------------------------
/**
 * @brief   �{���e�[�W���}�b�N�X�ɂȂ�����g���Ɓu+�R�v
 *
 * @param   apw				���Z�͕���Ǘ����[�N�ւ̃|�C���^
 * @param   wp				�Z���ʃp�����[�^�����̃|�C���^
 * @param   appeal_breeder	�A�s�[�����̃u���[�_�[�ԍ�
 * @param   kouka_breeder	���̋Z���ʂ𔭓����Ă���u���[�_�[�̔ԍ�
 * @param   pos				���Ԗڂ̃A�s�[����(appeal_breeder��)
 *
 * @retval  TRUE:���ʔ����B�@FALSE:���ʕs��
 */
//--------------------------------------------------------------
static int Kouka_VoltageMaxAfterAdd(ACTIN_PROC_WORK *apw, AWAZA_PARAM *wp, int appeal_breeder, int kouka_breeder, int pos)
{
	int front_breeder;
	
	if(pos == 0){
		OS_TPrintf("�擪�ׁ̈A�Z���s\n");
		return FALSE;
	}
	
	front_breeder = apw->a_game.breeder_sort[pos - 1];
	if(wp->personal[front_breeder].voltage_add_ap >= VOLTAGE_FULL_ADD_AP
			|| wp->personal[front_breeder].voltage_add_ap >= VOLTAGE_FULL_ADD_AP_SPECIAL){
		wp->personal[kouka_breeder].my_effective_ap += KOUKA_VOLTAGE_MAX_AFTER_ADD;
		AWAZA_MsgParamSet(&wp->personal[kouka_breeder], wp->personal[kouka_breeder].apno, 
			KOUKA_MSGID_A, kouka_breeder, TAG_NULL, TAG_NULL, TAG_NULL);
		
		OS_TPrintf("���O���{���e�[�WMax�������̂Ō��ʔ���\n");
		return TRUE;
	}
	OS_TPrintf("���O�̓{���e�[�WMax�ł͂Ȃ������̂Ŏ��s\n");
	return FALSE;
}

//--------------------------------------------------------------
/**
 * @brief   ��������ԕ]�����Ⴂ�Ɓ����u+�R�v
 *
 * @param   apw				���Z�͕���Ǘ����[�N�ւ̃|�C���^
 * @param   wp				�Z���ʃp�����[�^�����̃|�C���^
 * @param   appeal_breeder	�A�s�[�����̃u���[�_�[�ԍ�
 * @param   kouka_breeder	���̋Z���ʂ𔭓����Ă���u���[�_�[�̔ԍ�
 * @param   pos				���Ԗڂ̃A�s�[����(appeal_breeder��)
 *
 * @retval  TRUE:���ʔ����B�@FALSE:���ʕs��
 */
//--------------------------------------------------------------
static int Kouka_LowPointAdd(ACTIN_PROC_WORK *apw, AWAZA_PARAM *wp, int appeal_breeder, int kouka_breeder, int pos)
{
	int i;
	
	OS_TPrintf("kouka_breeder %d = %d\n", kouka_breeder, wp->personal[kouka_breeder].app_total_timing_before);
	for(i = 0; i < BREEDER_MAX; i++){
		if(i == kouka_breeder){
			continue;
		}
		OS_TPrintf("app_total_timing_before breeder %d = %d\n", i, wp->personal[i].app_total_timing_before);
		if(wp->personal[i].app_total_before < wp->personal[kouka_breeder].app_total_timing_before){
			break;
		}
	}
	if(i != BREEDER_MAX){
		OS_TPrintf("�u���[�_�[No%d�̕����_�����Ⴂ�̂Ŏ��s\n", i);
		return FALSE;
	}
	
	wp->personal[kouka_breeder].my_effective_ap += KOUKA_LOW_POINT_ADD;
	AWAZA_MsgParamSet(&wp->personal[kouka_breeder], wp->personal[kouka_breeder].apno, 
		KOUKA_MSGID_A, kouka_breeder, TAG_NULL, TAG_NULL, TAG_NULL);
	
	OS_TPrintf("��ԃ|�C���g���Ⴂ�̂Ō��ʔ���\n");
	return TRUE;
}

