//==============================================================================
/**
 * @file	we_195.s
 * @brief	ÇŸÇÎÇ—ÇÃÇ§ÇΩ			195
 * @author	goto
 * @date	2005.07.13(êÖ)
 *
 * Ç±Ç±Ç…êFÅXÇ»âê‡ìôÇèëÇ¢ÇƒÇ‡ÇÊÇ¢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_HOROBINOUTA
	
// =============================================================================
//
//
//	Å°ÇŸÇÎÇ—ÇÃÇ§ÇΩ			195
//
//
// =============================================================================
#define W195_BG_PAL_FADE	( 0 )
#define W195_BG_PAL_FADE_WAIT	(1)
#define W195_BG_PAL_FADE_COL	(WE_PAL_BLACK)

#define W195_SSP_PAL_FADE_AT	(WE_TOOL_M1)
#define W195_SSP_PAL_FADE_NUM	(1)
#define W195_SSP_PAL_RGB		(WE_PAL_GRAY)
#define W195_SSP_PAL_FADE_MAX	(16)

WEST_HOROBINOUTA:
	
	LOAD_PARTICLE_DROP	0,W_195_SPA
	ADD_PARTICLE 	0,W_195_195_HOROBIUTA_ONPU1, EMTFUNC_DUMMY
	ADD_PARTICLE 	0,W_195_195_HOROBIUTA_ONPU2, EMTFUNC_DUMMY
	ADD_PARTICLE 	0,W_195_195_HOROBIUTA_BALL,	 EMTFUNC_DUMMY
	ADD_PARTICLE 	0,W_195_195_HOROBIUTA_LINE,	 EMTFUNC_DUMMY
	
	SE_C			SEQ_SE_DP_W195
	WAIT			10
	FUNC_CALL		WEST_SP_WE_HAIKEI_PAL_FADE, 5, W195_BG_PAL_FADE, W195_BG_PAL_FADE_WAIT, 0, 16, W195_BG_PAL_FADE_COL,
	
	WAIT			15
	FUNC_CALL		WEST_SP_WE_SSP_POKE_PAL_FADE, 5, WE_TOOL_M1, 1, W195_SSP_PAL_FADE_NUM, W195_SSP_PAL_RGB, W195_SSP_PAL_FADE_MAX, 0,0,0
	FUNC_CALL		WEST_SP_WE_SSP_POKE_PAL_FADE, 5, WE_TOOL_M2, 1, W195_SSP_PAL_FADE_NUM, W195_SSP_PAL_RGB, W195_SSP_PAL_FADE_MAX, 0,0,0
	FUNC_CALL		WEST_SP_WE_SSP_POKE_PAL_FADE, 5, WE_TOOL_E1, 1, W195_SSP_PAL_FADE_NUM, W195_SSP_PAL_RGB, W195_SSP_PAL_FADE_MAX, 0,0,0
	FUNC_CALL		WEST_SP_WE_SSP_POKE_PAL_FADE, 5, WE_TOOL_E2, 1, W195_SSP_PAL_FADE_NUM, W195_SSP_PAL_RGB, W195_SSP_PAL_FADE_MAX, 0,0,0



	WAIT_PARTICLE
	EXIT_PARTICLE	0,

	FUNC_CALL	WEST_SP_WE_HAIKEI_PAL_FADE, 5, W195_BG_PAL_FADE, W195_BG_PAL_FADE_WAIT, 16, 0, W195_BG_PAL_FADE_COL, 0, 0, 0
	WAIT_FLAG

	SEQEND
