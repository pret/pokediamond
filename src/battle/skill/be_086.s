
//============================================================================
/**
 *
 *@file		be_086.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			086�@���肪���O�ɏo�����Z�𐔃^�[���g���Ȃ�����i�ϐg�̕ύX��Y�ꂸ�Ɂj
 *
 *@author	HisashiSogabe
 *@data		2006.01.19
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_086:
	VALUE	VAL_BIT,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND2_KANASIBARI|ADD_STATUS_DEFENCE|ADD_STATUS_WAZAKOUKA
	SEQ_END
