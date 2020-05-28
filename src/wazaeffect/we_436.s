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

	LOAD_PARTICLE_DROP	0,W_436_SPA
	
	SE_L			SEQ_SE_DP_W436

	ADD_PARTICLE 	0,W_436_436_HUNEN_FIRE1,	EMTFUNC_ATTACK_POS
	ADD_PARTICLE 	0,W_436_436_HUNEN_KEMURI,	EMTFUNC_ATTACK_POS
	ADD_PARTICLE 	0,W_436_436_HUNEN_BALL,		EMTFUNC_ATTACK_POS
	
	FUNC_CALL	WEST_SP_WT_SHAKE, 5, SHAKE_M_X, 0, SHAKE_M_WAIT, SHAKE_M_NUM,  WE_TOOL_OTHER | WE_TOOL_SSP
	
	WAIT		1
	
	PTAT_JP			PTAT
	
//	SIDE_JP			0, SIDE_M, SIDE_E
	
	FUNC_CALL		WEST_SP_WE_SSP_POKE_PAL_FADE, 6,  WE_TOOL_E1, 0, 1, WE_PAL_RED, 10,0
	FUNC_CALL		WEST_SP_WE_SSP_POKE_PAL_FADE, 6,  WE_TOOL_E2, 0, 1, WE_PAL_RED, 10,0
	FUNC_CALL		WEST_SP_WE_SSP_POKE_PAL_FADE, 6,  WE_TOOL_M2, 0, 1, WE_PAL_RED, 10,0
		
	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	
	SEQEND


///< PT
PTAT:

	SIDE_JP			0, SIDE_PM, SIDE_PE
	
	SEQEND

SIDE_PM:
	
	FUNC_CALL		WEST_SP_WE_SSP_POKE_PAL_FADE, 6,  WE_TOOL_E1, 0, 1, WE_PAL_RED, 10, 10
	FUNC_CALL		WEST_SP_WE_SSP_POKE_PAL_FADE, 6,  WE_TOOL_B, 0, 1, WE_PAL_RED, 10, 10
	FUNC_CALL		WEST_SP_WE_SSP_POKE_PAL_FADE, 6,  WE_TOOL_D, 0, 1, WE_PAL_RED, 10, 10

	WAIT_FLAG
	
	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	
	SEQEND
	
SIDE_PE:

	FUNC_CALL		WEST_SP_WE_SSP_POKE_PAL_FADE, 6,  WE_TOOL_E1, 0, 1, WE_PAL_RED, 10, 10
	FUNC_CALL		WEST_SP_WE_SSP_POKE_PAL_FADE, 6,  WE_TOOL_A, 0, 1, WE_PAL_RED, 10, 10
	FUNC_CALL		WEST_SP_WE_SSP_POKE_PAL_FADE, 6,  WE_TOOL_C, 0, 1, WE_PAL_RED, 10, 10

	WAIT_FLAG
	
	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	
	SEQEND

	
SIDE_M:
	
	SEQEND

SIDE_E:
	
	SEQEND
