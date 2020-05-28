//==============================================================================
/**
 * @file	we_211.s
 * @brief	ÇÕÇ™ÇÀÇÃÇ¬ÇŒÇ≥			211
 * @author	goto
 * @date	2005.07.13(êÖ)
 *
 * Ç±Ç±Ç…êFÅXÇ»âê‡ìôÇèëÇ¢ÇƒÇ‡ÇÊÇ¢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_HAGANENOTUBASA
	
// =============================================================================
//
//
//	Å°ÇÕÇ™ÇÀÇÃÇ¬ÇŒÇ≥			211
//
//
// =============================================================================
WEST_HAGANENOTUBASA:

	LOAD_PARTICLE_DROP	0,W_211_SPA
	
	ADD_PARTICLE 	0,W_211_211_HAGANE_HANE1,	 EMTFUNC_ATTACK_POS

	ADD_PARTICLE 	0,W_211_211_HAGANE_HANE2,	 EMTFUNC_FIELD_OPERATOR
	EX_DATA			OPERATOR_DEF_DATA_NUM, OPERATOR_PRI_NONE, OPERATOR_TARGET_DF, OPERATOR_POS_LSP, OPERATOR_AXIS_AT, OPERATOR_FLD_NONE, OPERATOR_CAMERA_NONE

	ADD_PARTICLE 	0,W_211_211_HAGANE_HIT,	 EMTFUNC_DEFENCE_POS

	WAIT			15
	SE_L			SEQ_SE_DP_W231
	WAIT			15
	SE_L			SEQ_SE_DP_W231
	WAIT			5
	SE_C			SEQ_SE_DP_W017
	WAIT			5
	SE_C			SEQ_SE_DP_W017
	WAIT			5
	SE_R			SEQ_SE_DP_W017
	WAIT			5
	SE_R			SEQ_SE_DP_W017

	FUNC_CALL		WEST_SP_WT_SHAKE, 5, SHAKE_M_X, 0, SHAKE_S_WAIT, SHAKE_S_NUM,  WE_TOOL_E1 | WE_TOOL_SSP,

	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	
	SEQEND
