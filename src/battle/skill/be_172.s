//============================================================================
/**
 *
 *@file		be_172.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			172�@�搧�U���@����̋Z�����ׂĎ������󂯂�
 *
 *@author	HisashiSogabe
 *@data		2005.10.03
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_172:
	KONOYUBITOMARE
	MESSAGE_PARAM	KonoyubitomareMineMsg,TAG_NICK,SIDE_ATTACK
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_INDIRECT,ADD_COND2_MESSAGE_WORK|ADD_STATUS_WAZAKOUKA
	SEQ_END
