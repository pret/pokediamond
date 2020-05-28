//==============================================================================
/**
 * @file	we_348.s
 * @brief	リーフブレード			348
 * @author	goto
 * @date	2005.07.13(水)
 *
 * ここに色々な解説等を書いてもよい
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_RIIHUBUREEDO
	
// =============================================================================
//
//
//	■リーフブレード			348
//
//
// =============================================================================
WEST_RIIHUBUREEDO:
	
	LOAD_PARTICLE_DROP	0,W_348_SPA
	ADD_PARTICLE 	0,W_348_348_SWORD_SLASH1, EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_348_348_SWORD_SLASH2, EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_348_348_SWORD_SLASH3, EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_348_348_SLASH_HIT, EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_348_348_LEAF_BURN, EMTFUNC_DEFENCE_POS

	SE_REPEAT		SEQ_SE_DP_W015, WAZA_SE_PAN_DF, 2, 7
	
	WAIT			30
	FUNC_CALL		WEST_SP_WT_SHAKE, 5, SHAKE_M_X, 0, SHAKE_M_WAIT, SHAKE_M_NUM,  WE_TOOL_E1 | WE_TOOL_SSP,
	
	WAIT_FLAG

	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	
	SEQEND
