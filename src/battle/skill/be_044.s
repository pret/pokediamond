//============================================================================
/**
 *
 *@file		be_044.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			044 �Q��A���ōU������
 *
 *@author	HisashiSogabe
 *@data		2005.10.03
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_044:
	RENZOKU			2,RENZOKU_HIT_OFF
	//ServerWazaOutAfterMessage�̃^�C�v�����[�v�p�ɂ���
	VALUE			VAL_SET,BUF_PARA_SWOAM_TYPE,SWOAM_LOOP
	CRITICAL_CHECK
	DAMAGE_CALC
	SEQ_END
