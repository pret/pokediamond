//==============================================================================
/**
 * @file	we_292.s
 * @brief	Ç¬Ç¡ÇœÇË			292
 * @author	goto
 * @date	2005.07.13(êÖ)
 *
 * Ç±Ç±Ç…êFÅXÇ»âê‡ìôÇèëÇ¢ÇƒÇ‡ÇÊÇ¢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_TUPPARI
	
// =============================================================================
//
//
//	Å°Ç¬Ç¡ÇœÇË			292
//
//
// =============================================================================
WEST_TUPPARI:
	
	LOAD_PARTICLE_DROP	0,W_292_SPA
//	ADD_PARTICLE 	0,W_292_292_HAND, EMTFUNC_DEFENCE_POS
	
	SIDE_JP			0,WEST_292_SIDE_MINE, WEST_292_SIDE_ENEMY
	
	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	
	SEQEND

WEST_292_SIDE_MINE:
	ADD_PARTICLE 	0,W_292_292_HAND_BEAM1, EMTFUNC_DEFENCE_POS
	
	WAIT			5
	SE_WAITPLAY_R	SEQ_SE_DP_030,3

	ADD_PARTICLE 	0,W_292_292_HITMARK1,	EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_292_292_BALL_BURN1, EMTFUNC_DEFENCE_POS
	
	WAIT			10
	FUNC_CALL		WEST_SP_WT_SHAKE, 5, SHAKE_M_X, 0, SHAKE_M_WAIT, SHAKE_M_NUM,  WE_TOOL_E1 | WE_TOOL_SSP,

	SEQEND

WEST_292_SIDE_ENEMY:
	ADD_PARTICLE 	0,W_292_292_HAND_BEAM2, EMTFUNC_DEFENCE_POS
	
	WAIT			5
	SE_WAITPLAY_R	SEQ_SE_DP_030,3

	ADD_PARTICLE 	0,W_292_292_HITMARK1,	EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_292_292_BALL_BURN1, EMTFUNC_DEFENCE_POS
	
	WAIT			10
	FUNC_CALL		WEST_SP_WT_SHAKE, 5, SHAKE_M_X, 0, SHAKE_M_WAIT, SHAKE_M_NUM,  WE_TOOL_E1 | WE_TOOL_SSP,

	SEQEND
