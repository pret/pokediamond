//============================================================================
/**
 *
 *@file		be_029.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			029 �Q�`�T��A���ōU������
 *
 *@author	HisashiSogabe
 *@data		2005.10.26
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_029:
	RENZOKU			0,RENZOKU_HIT_OFF
	//ServerWazaOutAfterMessage�̃^�C�v�����[�v�p�ɂ���
	VALUE			VAL_SET,BUF_PARA_SWOAM_TYPE,SWOAM_LOOP
	CRITICAL_CHECK
	DAMAGE_CALC
	SEQ_END
