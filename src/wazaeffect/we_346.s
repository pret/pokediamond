//==============================================================================
/**
 * @file	we_346.s
 * @brief	Ç›Ç∏Ç†ÇªÇ—			346
 * @author	goto
 * @date	2005.07.13(êÖ)
 *
 * Ç±Ç±Ç…êFÅXÇ»âê‡ìôÇèëÇ¢ÇƒÇ‡ÇÊÇ¢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_MIZUASOBI
	
// =============================================================================
//
//
//	Å°Ç›Ç∏Ç†ÇªÇ—			346
//
//
// =============================================================================
#define W346_WAIT	(10)
WEST_MIZUASOBI:

	LOAD_PARTICLE_DROP	0,W_346_SPA
	
	FUNC_CALL		WEST_SP_WE_SSP_POKE_SCALE_UPDOWN, 8, (WE_TOOL_M1 | WE_TOOL_SSP), 100, 110, 100,  80, 100, (5 << 16) | 1, (5 << 16) | 5
	WAIT_FLAG
	FUNC_CALL		WEST_SP_WE_SSP_POKE_SCALE_UPDOWN, 8, (WE_TOOL_M1 | WE_TOOL_SSP), 100, 100, 100, 120, 100, (0 << 16) | 1, (5 << 16) | 5
	WAIT			3
	
	ADD_PARTICLE 	0,W_346_346_WATER_UP1,	EMTFUNC_ATTACK_POS
	ADD_PARTICLE 	0,W_346_346_WATER_UP2,	EMTFUNC_ATTACK_POS
	
	WAIT_FLAG
	
	LOOP_LABEL		2
	
		SE_L			SEQ_SE_DP_W057

		FUNC_CALL		WEST_SP_WE_SSP_POKE_SCALE_UPDOWN, 8, (WE_TOOL_M1 | WE_TOOL_SSP), 100, 110, 100,  80, 100, (4 << 16) | 1, (4 << 16) | 4
		WAIT_FLAG
		FUNC_CALL		WEST_SP_WE_SSP_POKE_SCALE_UPDOWN, 8, (WE_TOOL_M1 | WE_TOOL_SSP), 100, 100, 100, 120, 100, (0 << 16) | 1, (4 << 16) | 4
		WAIT_FLAG
	
	LOOP

	SE_L			SEQ_SE_DP_W057
	
	SE_WAITPLAY_C	SEQ_SE_DP_NAMI,15
	WAIT			W346_WAIT
	
	ADD_PARTICLE 	0,W_346_346_WATER_DOWN,	EMTFUNC_DEFENCE_POS
	
	WAIT			10
	FUNC_CALL		WEST_SP_WT_SHAKE, 5, SHAKE_M_X, 0, SHAKE_M_WAIT, SHAKE_M_NUM*4,  WE_TOOL_E1 | WE_TOOL_SSP,

	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	
	SEQEND
