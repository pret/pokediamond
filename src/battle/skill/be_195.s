//============================================================================
/**
 *
 *@file		be_195.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			195�@�Ώۂ̑��肪���̃^�[���Ɏg�p�����񕜋Z�A�\�͕ω��Z�̌��ʂ�D���B
 *
 *@author	HisashiSogabe
 *@data		2006.02.09
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_195:
	YOKODORI		Umakukimaran
	MESSAGE_PARAM	YokodoriMineMsg,TAG_NICK,SIDE_ATTACK
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_INDIRECT,ADD_COND2_MESSAGE_WORK|ADD_STATUS_WAZAKOUKA
	SEQ_END

Umakukimaran:
	VALUE			VAL_SET,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_UMAKUKIMARAN
	SEQ_END
