//==============================================================================
/**
 * @file	we_310.s
 * @brief	Ç®Ç«ÇÎÇ©Ç∑			310
 * @author	goto
 * @date	2005.07.13(êÖ)
 *
 * Ç±Ç±Ç…êFÅXÇ»âê‡ìôÇèëÇ¢ÇƒÇ‡ÇÊÇ¢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_ODOROKASU
	
// =============================================================================
//
//
//	Å°Ç®Ç«ÇÎÇ©Ç∑			310
//
//
// =============================================================================
WEST_ODOROKASU:
	
	LOAD_PARTICLE_DROP	0,W_310_SPA

	FUNC_CALL		WEST_SP_WE_T05, 3, 3, +WE_MOVE_X_VAL_DEF, WE_TOOL_M1 | WE_TOOL_SSP
	WAIT_FLAG
	//SE_R			SEQ_SE_DP_W227
	SE_R			SEQ_SE_DP_W280B

	FUNC_CALL		WEST_SP_WE_SSP_POKE_SCALE_UPDOWN, 8, (WE_TOOL_E1 | WE_TOOL_SSP), 100, 90, 100, 140, 100, 1, (5 << 16) | 5
	WAIT			1
	
	FUNC_CALL		WEST_SP_WE_T05, 3, 3, -WE_MOVE_X_VAL_DEF, WE_TOOL_M1 | WE_TOOL_SSP

	ADD_PARTICLE 	0,W_310_310_BUB_BURN1, EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_310_310_BUB_BURN2, EMTFUNC_DEFENCE_POS
	
	WAIT_FLAG
	SE_R			SEQ_SE_DP_W166

	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	
	SEQEND
