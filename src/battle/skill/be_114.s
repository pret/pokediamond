//============================================================================
/**
 *
 *@file		be_114.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			114�@���̋Z���g�p�������ɐ퓬�ɏo�Ă����|�P�����͂R�^�[����ɐ퓬�s�\�ɂȂ�
 *				 �i�P�x�|�P�������������߂�ƌ��ʂ͉��������j
 *
 *@author	HisashiSogabe
 *@data		2006.01.27
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_114:
	VALUE		VAL_SET,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND2_HOROBINOUTA|ADD_STATUS_WAZAKOUKA
	SEQ_END
