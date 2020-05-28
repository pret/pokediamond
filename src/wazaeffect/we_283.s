//==============================================================================
/**
 * @file	we_283.s
 * @brief	Ç™ÇﬁÇµÇ·ÇÁ			283
 * @author	goto
 * @date	2005.07.13(êÖ)
 *
 * Ç±Ç±Ç…êFÅXÇ»âê‡ìôÇèëÇ¢ÇƒÇ‡ÇÊÇ¢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_GAMUSYARA
	
// =============================================================================
//
//
//	Å°Ç™ÇﬁÇµÇ·ÇÁ			283
//
//
// =============================================================================
WEST_GAMUSYARA:

	LOAD_PARTICLE_DROP	1,W_001_SPA
	LOAD_PARTICLE_DROP	0,W_283_SPA

	SE_REPEAT_L		SEQ_SE_DP_W039,20,4

	ADD_PARTICLE 	0,W_283_283_SWEAT_BURN, EMTFUNC_ATTACK_POS
	
	LOOP_LABEL		4
		
		FUNC_CALL	WEST_SP_WE_SSP_POKE_PAL_FADE, 5, WE_TOOL_M1, 0, 1, WE_PAL_YELLOW_2, 6

		FUNC_CALL	WEST_SP_WE_SSP_POKE_SCALE_UPDOWN, 8, (WE_TOOL_M1 | WE_TOOL_SSP), 100, 120, 100, 80, 100, 1, (4 << 16) | 4
		WAIT		7
		ADD_PARTICLE 	1,W_001_001_HIT_MARK, EMTFUNC_DEFENCE_POS
		ADD_PARTICLE 	1,W_001_001_HIT_MARK, EMTFUNC_DEFENCE_POS
		FUNC_CALL	WEST_SP_WE_SSP_POKE_SCALE_UPDOWN, 8, (WE_TOOL_M1 | WE_TOOL_SSP), 100, 80, 100, 140, 100, 1, (4 << 16) | 4
		FUNC_CALL		WEST_SP_WT_SHAKE, 5, SHAKE_S_X, 0, SHAKE_S_WAIT, SHAKE_S_NUM,  WE_TOOL_E1 | WE_TOOL_SSP,
		WAIT		3
		SE_R			SEQ_SE_DP_030
		WAIT		4
	
	LOOP

	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	
	SEQEND
