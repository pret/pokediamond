//============================================================================
/**
 *
 *@file		be_183.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			183�@�ǂ��A�܂ЁA�˂ނ�A������A��ǂ肬���̋Z��Ԃ��B�i�}�W�b�N�R�[�g�t���O�Q�Ɓj
 *
 *@author	HisashiSogabe
 *@data		2005.10.03
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_183:
	MAGIC_CORT		Umakukimaran
	MESSAGE_PARAM	MagicCortMineMsg,TAG_NICK,SIDE_ATTACK
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_INDIRECT,ADD_COND2_MESSAGE_WORK|ADD_STATUS_WAZAKOUKA
	SEQ_END

Umakukimaran:
	VALUE			VAL_SET,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_UMAKUKIMARAN
	SEQ_END
