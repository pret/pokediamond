//==============================================================================
/**
 * @file	we_351.s
 * @brief	Ç≈ÇÒÇ∞Ç´ÇÕ			351
 * @author	goto
 * @date	2005.07.13(êÖ)
 *
 * Ç±Ç±Ç…êFÅXÇ»âê‡ìôÇèëÇ¢ÇƒÇ‡ÇÊÇ¢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_DENGEKIHA
	
// =============================================================================
//
//
//	Å°Ç≈ÇÒÇ∞Ç´ÇÕ			351
//
//
// =============================================================================
WEST_DENGEKIHA:
	
	LOAD_PARTICLE_DROP	0,W_351_SPA

	FUNC_CALL		WEST_SP_WE_HAIKEI_PAL_FADE, 5, 0, 1, 0, 12, WE_PAL_BLACK
	WAIT_FLAG

	ADD_PARTICLE 	0,W_351_351_ELE_CHARGE1, EMTFUNC_ATTACK_POS
	ADD_PARTICLE 	0,W_351_351_ELE_CHARGE2, EMTFUNC_ATTACK_POS
	ADD_PARTICLE 	0,W_351_351_ELE_CHARGE3, EMTFUNC_ATTACK_POS
	
	WAIT			5
	SE_REPEAT_L		SEQ_SE_DP_W082,8,2

	WAIT			40
	ADD_PARTICLE 	0,W_351_351_ELE_CHARGE3, EMTFUNC_DEFENCE_POS
	WAIT			13
	SE_L			SEQ_SE_DP_W085B
	WAIT			24
	SE_L			SEQ_SE_DP_W085B
	WAIT			8
	
	ADD_PARTICLE 	0,W_351_351_ELE_BURN,	 EMTFUNC_ATTACK_POS	
	ADD_PARTICLE 	0,W_351_351_ELE_BURN2,	 EMTFUNC_ATTACK_POS
	
	FUNC_CALL		WEST_SP_WE_SSP_POKE_PAL_FADE, 6,  WE_TOOL_E1, 0, 2, WE_PAL_YELLOW, WEDEF_FADE_PARAM, 10
	FUNC_CALL		WEST_SP_WT_SHAKE, 5, SHAKE_M_X, 0, SHAKE_M_WAIT, SHAKE_M_NUM*3,  WE_TOOL_E1 | WE_TOOL_SSP,

	SE_FLOW_LR		SEQ_SE_DP_W172B
	SE_WAITPLAY_R	SEQ_SE_DP_W085B,15

	WAIT_PARTICLE
	EXIT_PARTICLE	0,

	FUNC_CALL		WEST_SP_WE_HAIKEI_PAL_FADE, 5, 0, 1, 12, 0, WE_PAL_BLACK
	WAIT_FLAG
	
	SEQEND
