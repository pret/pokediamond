//============================================================================
/**
 *
 *@file		be_077.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			077�@�A���łQ��U�����A�ǉ����ʂő�����ǂ���Ԃɂ���
 *
 *@author	HisashiSogabe
 *@data		2006.01.19
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_077:
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_INDIRECT,ADD_COND_DOKU|ADD_STATUS_DEFENCE
	RENZOKU			2,RENZOKU_HIT_OFF
	//ServerWazaOutAfterMessage�̃^�C�v�����[�v�p�ɂ���
	VALUE			VAL_SET,BUF_PARA_SWOAM_TYPE,SWOAM_LOOP
	CRITICAL_CHECK
	DAMAGE_CALC
	SEQ_END
