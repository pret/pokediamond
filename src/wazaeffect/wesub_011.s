//==============================================================================
/**
 * @file	wesub_011.s
 * @brief	�ꂠ
 * @author	goto
 * @date	2005.07.13(��)
 *
 * �����ɐF�X�ȉ�����������Ă��悢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_StatusKonran
	
// =============================================================================
//
//
//	���ꂠ
//
//
// =============================================================================
WEST_Rea:

	LOAD_PARTICLE_DROP	0, SPA_STATUS_EFF
	
	SE_L			SEQ_SE_DP_REAPOKE
	
	ADD_PARTICLE 	0, STATUS_EFF_KIRA_ROLL01, EMTFUNC_ATTACK_POS	
	ADD_PARTICLE 	0, STATUS_EFF_KIRA_ROLL02, EMTFUNC_ATTACK_POS

	WAIT_PARTICLE
	EXIT_PARTICLE	0,

	SEQEND

