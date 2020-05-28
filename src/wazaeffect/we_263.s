//==============================================================================
/**
 * @file	we_263.s
 * @brief	Ç©ÇÁÇ∞ÇÒÇ´			263
 * @author	goto
 * @date	2005.07.13(êÖ)
 *
 * Ç±Ç±Ç…êFÅXÇ»âê‡ìôÇèëÇ¢ÇƒÇ‡ÇÊÇ¢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_KARAGENKI
	
// =============================================================================
//
//
//	Å°Ç©ÇÁÇ∞ÇÒÇ´			263
//
//
// =============================================================================
WEST_KARAGENKI:
	
	LOAD_PARTICLE_DROP	0,W_263_SPA
	ADD_PARTICLE 	0,W_263_263_BUB_BURN1,	EMTFUNC_ATTACK_POS
	ADD_PARTICLE 	0,W_263_263_BUB_BURN2,	EMTFUNC_ATTACK_POS
	
	SE_REPEAT_L		SEQ_SE_DP_W207,8,6
		
	FUNC_CALL	WEST_SP_WE_SSP_POKE_PAL_FADE, 6,  WE_TOOL_M1, 0, 1, WE_PAL_RED, 10,0
	FUNC_CALL	WEST_SP_WE_SSP_POKE_SCALE_UPDOWN, 8, (WE_TOOL_M1 | WE_TOOL_SSP), 100, 120, 100, 80, 100, 1, (5 << 16) | 5
	WAIT		8
	FUNC_CALL	WEST_SP_WE_SSP_POKE_SCALE_UPDOWN, 8, (WE_TOOL_M1 | WE_TOOL_SSP), 100, 80, 100, 140, 100, 1, (5 << 16) | 5
	WAIT		8
	
	FUNC_CALL	WEST_SP_WE_SSP_POKE_PAL_FADE, 6,  WE_TOOL_M1, 0, 1, WE_PAL_BLUE, 10,0
	FUNC_CALL	WEST_SP_WE_SSP_POKE_SCALE_UPDOWN, 8, (WE_TOOL_M1 | WE_TOOL_SSP), 100, 120, 100, 80, 100, 1, (5 << 16) | 5
	WAIT		8
	FUNC_CALL	WEST_SP_WE_SSP_POKE_SCALE_UPDOWN, 8, (WE_TOOL_M1 | WE_TOOL_SSP), 100, 80, 100, 140, 100, 1, (5 << 16) | 5
	WAIT		8
	
	FUNC_CALL	WEST_SP_WE_SSP_POKE_PAL_FADE, 6,  WE_TOOL_M1, 0, 1, WE_PAL_YELLOW, 10,0
	FUNC_CALL	WEST_SP_WE_SSP_POKE_SCALE_UPDOWN, 8, (WE_TOOL_M1 | WE_TOOL_SSP), 100, 120, 100, 80, 100, 1, (5 << 16) | 5
	WAIT		8
	FUNC_CALL	WEST_SP_WE_SSP_POKE_SCALE_UPDOWN, 8, (WE_TOOL_M1 | WE_TOOL_SSP), 100, 80, 100, 140, 100, 1, (5 << 16) | 5
	
	ADD_PARTICLE 	0,W_263_038_HIT_MARK1,	EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_263_413_HIT_MARK2,	EMTFUNC_DEFENCE_POS
	FUNC_CALL		WEST_SP_WT_SHAKE, 5, SHAKE_M_X, 0, SHAKE_M_WAIT, SHAKE_M_NUM,  WE_TOOL_E1 | WE_TOOL_SSP,
	
	SE_R		SEQ_SE_DP_030
	WAIT_FLAG

	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	
	SEQEND
