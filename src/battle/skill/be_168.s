//============================================================================
/**
 *
 *@file		be_168.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			168�@�������m���ɂȂ邪�A����̍U���́A����U���͂��Q�i�K������
 *
 *@author	HisashiSogabe
 *@data		2006.02.06
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_168:
	//�����̏���������
	VALUE			VAL_SET,BUF_PARA_CALC_WORK,SERVER_STATUS_FLAG_JIBAKU
	VALUE_WORK		VAL_LSH,BUF_PARA_CALC_WORK,BUF_PARA_ATTACK_CLIENT
	VALUE_WORK		VAL_BIT,BUF_PARA_SERVER_STATUS_FLAG,BUF_PARA_CALC_WORK
	PSP_VALUE		VAL_SET,SIDE_ATTACK,ID_PSP_hp,0
	//�Q�[�W��0�ɂ��鏈��
	VALUE			VAL_SET,BUF_PARA_HP_CALC_WORK,JIBAKU_HP
	HP_GAUGE_CALC	SIDE_ATTACK
	//�����Ă��鑊��ɂ����Ă�
	VALUE			VAL_BIT,BUF_PARA_SERVER_STATUS_FLAG,SERVER_STATUS_FLAG_KIE_HIT
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND2_OKIMIYAGE|ADD_STATUS_DEFENCE|ADD_STATUS_WAZAKOUKA
	SEQ_END
