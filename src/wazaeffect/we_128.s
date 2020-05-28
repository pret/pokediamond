//==============================================================================
/**
 * @file	we_128.s
 * @brief	����ł͂���			128
 * @author	goto
 * @date	2005.07.13(��)
 *
 * �����ɐF�X�ȉ�����������Ă��悢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_KARADEHASAMU
	
// =============================================================================
//
//
//	������ł͂���			128
//
//
// =============================================================================
WEST_KARADEHASAMU:
	
	LOAD_PARTICLE_DROP	0,W_128_SPA
	ADD_PARTICLE 	0,W_128_128_KARA_GIZAL, EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_128_128_KARA_GIZAR, EMTFUNC_DEFENCE_POS

	SE_R			SEQ_SE_DP_050
	WAIT	10	

	ADD_PARTICLE 	0,W_128_128_KARA_HIT, EMTFUNC_DEFENCE_POS

	SE_R			SEQ_SE_DP_W011
	SE_WAITPLAY_R	SEQ_SE_DP_030,13
	FUNC_CALL		WEST_SP_WT_SHAKE, 5, SHAKE_S_X, 0, SHAKE_S_WAIT, SHAKE_S_NUM,  WE_TOOL_E1 | WE_TOOL_SSP,

	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	
	SEQEND
