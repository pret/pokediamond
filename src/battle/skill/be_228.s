//============================================================================
/**
 *
 *@file		be_228.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			228�@�U��������A�T���|�P�����Ɠ���ւ��B�T�������Ȃ��ꍇ�́A����ւ����������Ȃ��ŏI���B�����������󂯂�B
 *
 *@author	HisashiSogabe
 *@data		2006.02.16
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_228:
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_INDIRECT,ADD_COND2_TONBOGAERI|ADD_STATUS_WAZAKOUKA
	CRITICAL_CHECK
	DAMAGE_CALC
	SEQ_END
