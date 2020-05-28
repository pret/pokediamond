//==============================================================================
/**
 * @file	we_085.s
 * @brief	ÇPÇOÇ‹ÇÒÉ{ÉãÉg			85
 * @author	goto
 * @date	2005.07.13(êÖ)
 *
 * Ç±Ç±Ç…êFÅXÇ»âê‡ìôÇèëÇ¢ÇƒÇ‡ÇÊÇ¢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_10MANBORUTO
	
// =============================================================================
//
//
//	Å°ÇPÇOÇ‹ÇÒÉ{ÉãÉg			85
//
//
// =============================================================================
WEST_10MANBORUTO:

	LOAD_PARTICLE_DROP	0,W_085_SPA
	
	FUNC_CALL		WEST_SP_WE_HAIKEI_PAL_FADE, 5, 0, 1, 0, 12, WE_PAL_BLACK
	WAIT_FLAG
	
	ADD_PARTICLE 	0,W_085_085_THUNDER10_LINE, 	EMTFUNC_DEFENCE_POS

	SE_R			SEQ_SE_DP_KAMI
	
	WAIT			5
	FUNC_CALL		WEST_SP_WE_SSP_POKE_PAL_FADE, 6,  WE_TOOL_E1, 0, 1, WE_PAL_BLACK, 15, 0
	
	ADD_PARTICLE 	0,W_085_085_THUNDER10_BALL01, EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_085_085_THUNDER10_BALL02, EMTFUNC_DEFENCE_POS
	FUNC_CALL		WEST_SP_WT_SHAKE, 5, SHAKE_S_X, 0, SHAKE_S_WAIT, SHAKE_S_NUM*2,  WE_TOOL_E1 | WE_TOOL_SSP,
	
	WAIT			5
	
	ADD_PARTICLE 	0,W_085_085_THUNDER_SPARK01,	EMTFUNC_DEFENCE_POS
	SE_WAITPLAY_R	SEQ_SE_DP_W063B,50
	FUNC_CALL		WEST_SP_WT_SHAKE, 5, SHAKE_S_X, 0, SHAKE_S_WAIT, SHAKE_S_NUM,  WE_TOOL_E1 | WE_TOOL_SSP,

	WAIT_PARTICLE
	EXIT_PARTICLE	0,

	FUNC_CALL		WEST_SP_WE_HAIKEI_PAL_FADE, 5, 0, 1, 12, 0, WE_PAL_BLACK
	WAIT_FLAG

	SEQEND
