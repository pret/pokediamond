//============================================================================
/**
 *
 *@file		be_266.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			266�@����̏�ɂ����āA�o�Ă����|�P�����̂g�o�łP/�W���_���[�W�B
 *				 ����͑����{���ɂ��ω�����B1/2�Ȃ�1/16�A1/4�Ȃ�1/32�A�~�Q�Ȃ�1/4�A�~�S�Ȃ�1/2�B
 *
 *@author	HisashiSogabe
 *@data		2006.05.05
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_266:
	IF				IF_FLAG_BIT,BUF_PARA_SIDE_CONDITION_DEFENCE,SIDE_CONDITION_STEALTHROCK,Umakukimaran
	VALUE			VAL_BIT,BUF_PARA_SIDE_CONDITION_DEFENCE,SIDE_CONDITION_STEALTHROCK
	MESSAGE_PARAM	StealthrockMineMsg,TAG_NONE_DIR,SIDE_ATTACK_ENEMY
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_INDIRECT,ADD_COND2_MESSAGE_WORK|ADD_STATUS_WAZAKOUKA
	SEQ_END

Umakukimaran:
	VALUE			VAL_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_UMAKUKIMARAN
	SEQ_END
