//============================================================================
/**
 *
 *@file		be_249.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			249�@�܂��т��̓Ńo�[�W�����B�_���[�W�̑���ɁA���񂾃|�P�������ǂ���Ԃɂ���B
 *				 �Ń|�P�������o���΁A�ł��󂯂��ɏ�����B�P��܂��ƓŁA�Q��܂��ƖғŁB�܂��т��Ɠ����ɂ܂����Ƃ͉\�B
 *
 *@author	HisashiSogabe
 *@data		2006.02.15
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_249:
	DOKUBISI		Umakukimaran
	MESSAGE_PARAM	DokubisiMineMsg,TAG_NONE_DIR,SIDE_ATTACK_ENEMY
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_INDIRECT,ADD_COND2_MESSAGE_WORK|ADD_STATUS_WAZAKOUKA
	SEQ_END

Umakukimaran:
	VALUE			VAL_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_UMAKUKIMARAN
	SEQ_END
