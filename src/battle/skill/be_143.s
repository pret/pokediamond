//============================================================================
/**
 *
 *@file		be_143.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			143�@�G�ɂ������Ă���⏕���ʂ������ɂ�������
 *
 *@author	HisashiSogabe
 *@data		2005.10.03
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_143:
	JIKOANJI
	MESSAGE_PARAM	JikoanjiM2MMsg,TAG_NICK_NICK,SIDE_ATTACK,SIDE_DEFENCE
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_INDIRECT,ADD_COND2_MESSAGE_WORK|ADD_STATUS_WAZAKOUKA
	SEQ_END
