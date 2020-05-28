//==============================================================================
/**
 * @file	we_302.s
 * @brief	�j�[�h���A�[��			302
 * @author	goto
 * @date	2005.07.13(��)
 *
 * �����ɐF�X�ȉ�����������Ă��悢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_NIIDORUAAMU
	
// =============================================================================
//
//
//	���j�[�h���A�[��			302
//
//
// =============================================================================
WEST_NIIDORUAAMU:
	
	LOAD_PARTICLE_DROP	0,W_302_SPA
	ADD_PARTICLE 	0,W_302_302_PUNCH1,	 EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_302_302_PUNCH2,	 EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_302_302_NEEDLE_BURN, EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_302_302_NEEDLE_RUSH, EMTFUNC_DEFENCE_POS

	WAIT			2
	SE_REPEAT_R		SEQ_SE_DP_W030,2,8
	WAIT			13

	FUNC_CALL		WEST_SP_WT_SHAKE, 5, 2, 0, 1, 4,  WE_TOOL_E1 | WE_TOOL_SSP,
	SE_WAITPLAY_R	SEQ_SE_DP_186,5
	WAIT_FLAG


	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	
	SEQEND
