//============================================================================
/**
 *
 *@file		be_104.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			104�@�R��A���œG���U������A�U������������x�Ƀ_���[�W�͑傫���Ȃ�i�P�O�A�Q�O�A�R�O�j�A
 *				 �P�x�U�����O���ƋZ�͂����Ŏ~�܂�
 *
 *@author	HisashiSogabe
 *@data		2006.01.24
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_104:
	RENZOKU			3,TRIPLEKICK_HIT_OFF
	//ServerWazaOutAfterMessage�̃^�C�v�����[�v�p�ɂ���
	VALUE			VAL_SET,BUF_PARA_SWOAM_TYPE,SWOAM_LOOP
	//�P�O�������Ă���
	VALUE			VAL_ADD,BUF_PARA_DAMAGE_POWER,10
	CRITICAL_CHECK
	DAMAGE_CALC
	SEQ_END
