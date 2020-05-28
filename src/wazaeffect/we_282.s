//==============================================================================
/**
 * @file	we_282.s
 * @brief	ÇÕÇΩÇ´Ç®Ç∆Ç∑			282
 * @author	goto
 * @date	2005.07.13(êÖ)
 *
 * Ç±Ç±Ç…êFÅXÇ»âê‡ìôÇèëÇ¢ÇƒÇ‡ÇÊÇ¢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_HATAKIOTOSU
	
// =============================================================================
//
//
//	Å°ÇÕÇΩÇ´Ç®Ç∆Ç∑			282
//
//
// =============================================================================
WEST_HATAKIOTOSU:

	LOAD_PARTICLE_DROP	0,W_282_SPA
	
	FUNC_CALL		WEST_SP_WE_T10,	4, 2, +14, -8, WE_TOOL_M1 | WE_TOOL_SSP
	WAIT_FLAG
	
	SE_R			SEQ_SE_DP_W233
	
	ADD_PARTICLE 	0,W_282_282_HAND_DOWN,	EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_282_282_HITMARK, 	EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_282_282_BALL_BURN,	EMTFUNC_DEFENCE_POS
	
	FUNC_CALL		WEST_SP_WE_T10,	4, 2, -14, +8, WE_TOOL_M1 | WE_TOOL_SSP
	
	WAIT			5
	FUNC_CALL		WEST_SP_WT_SHAKE, 5, 0, 4, 1, 1,  WE_TOOL_E1 | WE_TOOL_SSP,
	
	WAIT_FLAG

	SE_R			SEQ_SE_DP_W004

	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	
	SEQEND
