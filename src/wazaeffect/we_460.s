//==============================================================================
/**
 * @file	we_001.s
 * @brief	ÇÕÇΩÇ≠
 * @author	goto
 * @date	2005.07.13(êÖ)
 *
 * Ç±Ç±Ç…êFÅXÇ»âê‡ìôÇèëÇ¢ÇƒÇ‡ÇÊÇ¢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_Hataku
	
// =============================================================================
//
//
//	Å°ÇÕÇΩÇ≠
//
//
// =============================================================================
WEST_Hataku:

	LOAD_PARTICLE_DROP	0,W_460_SPA

	SE_L			SEQ_SE_DP_W460
	
	ADD_PARTICLE	0, W_460_460_WAVE_BURN01,	EMTFUNC_ATTACK_POS
	ADD_PARTICLE	0, W_460_460_LINE_BURN01,	EMTFUNC_ATTACK_POS
	ADD_PARTICLE	0, W_460_460_RING_SMALL,	EMTFUNC_ATTACK_POS
	ADD_PARTICLE	0, W_460_460_DUST01,		EMTFUNC_ATTACK_POS
	
	WAIT			50
	WORK_CLEAR
	WORK_SET		WEDEF_GP_INDEX_SCREEN_R, 1
	HAIKEI_CHG		BG_ID_460, WEDEF_HAIKEI_MODE_FADE | WEDEF_HAIKEI_SBIT_NONE
	WAIT			10
	FUNC_CALL		WEST_SP_BG_SHAKE, 5, 0, 3, 0, 10, 0
	
	SE_L			SEQ_SE_DP_W460
	
	ADD_PARTICLE	0, W_460_460_HIT_SLASH01,	EMTFUNC_DEFENCE_POS
	ADD_PARTICLE	0, W_460_460_HIT_SLASH02,	EMTFUNC_DEFENCE_POS	
	FUNC_CALL		WEST_SP_WT_SHAKE, 5, SHAKE_M_X, 0, SHAKE_M_WAIT, SHAKE_M_NUM*2,  WE_TOOL_E1 | WE_TOOL_SSP,
	FUNC_CALL		WEST_SP_WE_SSP_POKE_PAL_FADE, 6,  WE_TOOL_E1, 0, 1, WE_PAL_WHITE, WEDEF_FADE_PARAM,0
	
	WAIT_FLAG
		
	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	
	WORK_CLEAR
	WORK_SET		WEDEF_GP_INDEX_SCREEN_R, 1
	HAIKEI_RECOVER	BG_ID_460, WEDEF_HAIKEI_RC_MODE_FADE | WEDEF_HAIKEI_SBIT_NONE
	HAIKEI_CHG_WAIT
	
	SEQEND


