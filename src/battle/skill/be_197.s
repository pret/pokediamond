//============================================================================
/**
 *
 *@file		be_197.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			197�@�ʏ�̑Ō��U���ɁA�n�`�̎�ނɂ��ǉ����ʂ������܂��B
 *
 *@author	HisashiSogabe
 *@data		2006.03.02
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_197:
	CRITICAL_CHECK
	DAMAGE_CALC
	HIMITSUNOCHIKARA
	SEQ_END
