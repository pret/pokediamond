//============================================================================
/**
 *
 *@file		be_118.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			118�@�G���u������v��Ԃɂ��邪�A�����Ɂu���������v���Q�i�K�グ�Ă��܂�
 *
 *@author	HisashiSogabe
 *@data		2005.10.03
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_118:
	VALUE		VAL_SET,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND2_IBARU|ADD_STATUS_WAZAKOUKA|ADD_STATUS_DEFENCE
	SEQ_END
