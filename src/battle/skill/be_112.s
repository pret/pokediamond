//============================================================================
/**
 *
 *@file		be_112.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			112�@�܂��т����܂��Ă����ƁA����̃g���[�i�[���|�P��������シ��x�ɑ���Ƀ_���[�W��^���邱�Ƃ��ł���
 *				 �g�����ɈЗ͂��傫���Ȃ��Ă����i�R�i�K�܂Łj
 *
 *@author	HisashiSogabe
 *@data		2006.01.27
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_112:
	MAKIBISI		Umakukimaran
	MESSAGE_PARAM	MakibishiMineMsg,TAG_NONE_DIR,SIDE_ATTACK_ENEMY
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_INDIRECT,ADD_COND2_MESSAGE_WORK|ADD_STATUS_WAZAKOUKA
	SEQ_END

Umakukimaran:
	VALUE			VAL_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_UMAKUKIMARAN
	SEQ_END
