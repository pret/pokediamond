//============================================================================
/**
 *
 *@file		be_224.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			224�@���肪�؂̎��������Ă���Ƃ��A�U������Ǝ����ɖ؂̎��̌��ʂ𔭊�������B
 *				 �_���[�W������A�؂̎����`�F�b�N���Ď��s�B�ʃV�[�g�y����ǉ��Z�z�̎Q�ƁB
 *
 *@author	HisashiSogabe
 *@data		2006.02.14
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_224:
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_INDIRECT,ADD_COND2_TSUIBAMU|ADD_STATUS_WAZAKOUKA
	CRITICAL_CHECK
	DAMAGE_CALC
	SEQ_END
