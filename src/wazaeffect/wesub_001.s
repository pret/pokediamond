//==============================================================================
/**
 * @file	wesub_001.s
 * @brief	�˂ނ�
 * @author	goto
 * @date	2005.07.13(��)
 *
 * �����ɐF�X�ȉ�����������Ă��悢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_StatusNemuru
	
// =============================================================================
//
//
//	���˂ނ�
//
//
// =============================================================================
WEST_StatusNemuru:

	LOAD_PARTICLE_DROP	0, SPA_STATUS_EFF
	
	//SE_REPEAT_L		SEQ_SE_DP_W173,20,3
	SE_REPEAT_L		SEQ_SE_DP_W173B,20,1

	ADD_PARTICLE 	0, STATUS_EFF_TURN_ZZZ, EMTFUNC_ATTACK_POS
	
	WAIT_PARTICLE
	EXIT_PARTICLE	0,

	SEQEND
