//==============================================================================
/**
 * @file	we_001.s
 * @brief	�͂���
 * @author	goto
 * @date	2005.07.13(��)
 *
 * �����ɐF�X�ȉ�����������Ă��悢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_Hataku
	
// =============================================================================
//
//
//	���͂���
//
//
// =============================================================================
WEST_445:
	LOAD_PARTICLE_DROP	0,W_445_SPA
	
	ADD_PARTICLE 	0,W_445_445_YUWAKU_HART,		EMTFUNC_ATTACK_POS
	ADD_PARTICLE 	0,W_445_445_YUWAKU_KIRA,		EMTFUNC_ATTACK_POS
	
	SE_L			SEQ_SE_DP_164
	FUNC_CALL		WEST_SP_WE_204, 0,0,0,0,0,0,0,0,0
		
	WAIT_PARTICLE
	EXIT_PARTICLE	0,


	SEQEND
