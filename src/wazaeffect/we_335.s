//==============================================================================
/**
 * @file	we_335.s
 * @brief	�Ƃ�����ڂ�			335
 * @author	goto
 * @date	2005.07.13(��)
 *
 * �����ɐF�X�ȉ�����������Ă��悢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_TOOSENBOU
	
// =============================================================================
//
//
//	���Ƃ�����ڂ�			335
//
//
// =============================================================================
WEST_TOOSENBOU:

	LOAD_PARTICLE_DROP	0,W_286_SPA

	SE_R			SEQ_SE_DP_050

//	ADD_PARTICLE 	0,W_286_286_FONT_FU01, EMTFUNC_DEFENCE_POS
//	ADD_PARTICLE 	0,W_286_286_FONT_FU02, EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_286_286_BATU01, EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_286_286_BATU02, EMTFUNC_DEFENCE_POS
	
	LOOP_LABEL	1
		WAIT 12
		SE_R			SEQ_SE_DP_W030
	LOOP

	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	
	SEQEND
