//============================================================================
/**
 *
 *@file		be_008.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			008�@�G���u�˂ނ�v��Ԃ̎��������ʂ̂���Z�i�u�˂ނ�v��ԂłȂ��ƋZ�͎��s����j�A
 *				 �G�ɗ^�����_���[�W�̔����̐��l�����g�o���񕜂���
 *
 *@author	HisashiSogabe
 *@data		2005.12.06
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_008:
	//�݂������o����Ă���Ƃ��́A���s����
	MIGAWARI_CHECK	SIDE_DEFENCE,Sippai
	//���肪�Q�Ă��Ȃ��Ƃ��́A���s����
	IF_PSP			IF_FLAG_NBIT,SIDE_DEFENCE,ID_PSP_condition,CONDITION_NEMURI,Sippai

	//�Z���ʂ�ǉ����ăV�[�P���X�𔭓�
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_INDIRECT,ADD_COND2_YUMEKUI|ADD_STATUS_WAZAKOUKA
	CRITICAL_CHECK
	DAMAGE_CALC
	SEQ_END

Sippai:
	ATTACK_MESSAGE
	SERVER_WAIT
	WAIT			MSG_WAIT
	MESSAGE			SippaiMineMsg,TAG_NICK,SIDE_DEFENCE
	SERVER_WAIT
	WAIT			MSG_WAIT
	//WazaStatusMessage�𖳌��ɂ��邽�߂ɂ��̃t���O�𗧂Ă�
	//VALUE			VAL_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_SIPPAI_RENZOKU_CHECK
	VALUE			VAL_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_SIPPAI
	SEQ_END


