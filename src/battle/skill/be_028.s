//============================================================================
/**
 *
 *@file		be_028.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			028�@�G���J�E���g�퓬���͋����I�ɐ퓬���I��������A
 *				 �g���[�i�[��Ŏg�p����ƃ|�P�����������I�ɓ���ւ�������i�G�Ɍ�������|�P���������Ȃ��ꍇ�A�Z�͎��s����j
 *
 *@author	HisashiSogabe
 *@data		2006.01.26
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_028:
	VALUE		VAL_SET,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND2_HUKITOBASI|ADD_STATUS_WAZAKOUKA
	SEQ_END
