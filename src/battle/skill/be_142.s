//============================================================================
/**
 *
 *@file		be_142.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			142�@�g�p�����|�P�����̂g�o�������ɂȂ�ւ��Ɂu���������v���ő�܂ŏグ��
 *
 *@author	HisashiSogabe
 *@data		2006.02.02
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_142:
	VALUE		VAL_SET,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND2_HARADAIKO|ADD_STATUS_WAZAKOUKA
	SEQ_END
