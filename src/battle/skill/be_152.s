//============================================================================
/**
 *
 *@file		be_152.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			152�@�܂Ђ̒ǉ����ʁ{�V�C���u���߁v��Ԃ̂Ƃ��Ɏg�p����ƕK�������B
 *				�u�͂�v���Ɩ�������50���B�����ł���G�ɍU���ł��܂��B
 *
 *@author	HisashiSogabe
 *@data		2006.02.02
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_152:
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_INDIRECT,ADD_COND_MAHI|ADD_STATUS_DEFENCE
	VALUE			VAL_BIT,BUF_PARA_SERVER_STATUS_FLAG,SERVER_STATUS_FLAG_SORAWOTOBU_HIT
	CRITICAL_CHECK
	DAMAGE_CALC
	SEQ_END
