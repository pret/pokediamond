//============================================================================
/**
 *
 *@file		be_154.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			154�@���Ԃ̃|�P�����̐��i����������čő�U��j�����G���U������A
 *				 �퓬�s�\������ԁi�ǂ��A�˂ނ蓙�j�̃|�P�����͐��ɂ���Ȃ�
 *
 *@author	HisashiSogabe
 *@data		2006.02.02
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_154:
	//�^�C�v�𖳑����ɂ���
	VALUE			VAL_BIT,BUF_PARA_SERVER_STATUS_FLAG,SERVER_STATUS_FLAG_TYPE_NONE
	CRITICAL_CHECK
	HUKURODATAKI
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND2_HUKURODATAKI|ADD_STATUS_WAZAKOUKA
	VALUE			VAL_BIT,BUF_PARA_SERVER_STATUS_FLAG,SERVER_STATUS_FLAG_NO_LOOP_HIT_MSG
	SEQ_END
