//============================================================================
/**
 *
 *@file		be_127.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			127�@�����̃|�P�����ƌ�シ��A��シ�鎞�ɍ��܂ł������Ă����⏕���ʂ����̂܂܎󂯌p�����鎖���o����
 *				�i��������|�P���������Ȃ��ꍇ�A�Z�͎��s����j
 *
 *@author	HisashiSogabe
 *@data		2006.02.02
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_127:
	VALUE		VAL_SET,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND2_BATONTOUCH|ADD_STATUS_WAZAKOUKA
	SEQ_END
