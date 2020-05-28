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
WEST_440:
	LOAD_PARTICLE_DROP	0,W_440_SPA
	
	ADD_PARTICLE 	0,W_440_440_POI_LINE1,		EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_440_440_POI_LINE2,		EMTFUNC_DEFENCE_POS
	
	SE_R			SEQ_SE_DP_W015

	FUNC_CALL		WEST_SP_WE_SSP_POKE_PAL_FADE, 6,  WE_TOOL_E1, 0, 1, WE_PAL_POISON, 10,0
	ADD_PARTICLE 	0,W_440_440_POI_POI,		EMTFUNC_DEFENCE_POS
	
	WAIT			5
	SE_REPEAT_R		SEQ_SE_DP_W092D,4,3

	FUNC_CALL		WEST_SP_WT_SHAKE, 5, SHAKE_S_X, 0, SHAKE_S_WAIT, SHAKE_S_NUM,  WE_TOOL_E1 | WE_TOOL_SSP,
		
	WAIT_PARTICLE
	EXIT_PARTICLE	0,


	SEQEND
	
