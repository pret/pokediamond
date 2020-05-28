//==============================================================================
/**
 * @file	we_023.s
 * @brief	Ç”Ç›Ç¬ÇØ			23
 * @author	goto
 * @date	2005.07.13(êÖ)
 *
 * Ç±Ç±Ç…êFÅXÇ»âê‡ìôÇèëÇ¢ÇƒÇ‡ÇÊÇ¢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_HUMITUKE
	
// =============================================================================
//
//
//	Å°Ç”Ç›Ç¬ÇØ			23
//
//
// =============================================================================
WEST_HUMITUKE:
	
	LOAD_PARTICLE_DROP	0,W_023_SPA
	ADD_PARTICLE 	0,W_023_023_FOOT_MARK,	EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_023_023_HIT_MARK,	EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_023_001_BALL_BURN,	EMTFUNC_DEFENCE_POS

	WAIT			5
	FUNC_CALL		WEST_SP_WE_SSP_POKE_SCALE_UPDOWN, 8, (WE_TOOL_E1 | WE_TOOL_SSP), 100, 130, 100, 70, 100, (20 << 16) | 1, (4 << 16) | 4

	SE_R			SEQ_SE_DP_W036
	SE_WAITPLAY_R	SEQ_SE_DP_030,5

	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	
	SEQEND
