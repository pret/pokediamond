//==============================================================================
/**
 * @file	we_151.s
 * @brief	�Ƃ���			151
 * @author	goto
 * @date	2005.07.13(��)
 *
 * �����ɐF�X�ȉ�����������Ă��悢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_TOKERU
	
// =============================================================================
//
//
//	���Ƃ���			151
//
//
// =============================================================================
WEST_TOKERU:
	POKEBG_DROP		0,	WEDEF_POKE_AUTO_OFF
	
	LOAD_PARTICLE_DROP	0,W_151_SPA
	
	
	ADD_PARTICLE 	0,W_151_151_TOKERU_BUB, EMTFUNC_ATTACK_POS
	FUNC_CALL		WEST_SP_WE_151, 0,0,0,0,0,0,0,0
	SE_L			SEQ_SE_DP_154

	WAIT_FLAG
	
	POKEBG_DROP_RESET 0
	
	SEQEND
