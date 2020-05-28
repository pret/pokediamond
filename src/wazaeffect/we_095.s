//==============================================================================
/**
 * @file	we_095.s
 * @brief	Ç≥Ç¢Ç›ÇÒÇ∂Ç„Ç¬			95
 * @author	goto
 * @date	2005.07.13(êÖ)
 *
 * Ç±Ç±Ç…êFÅXÇ»âê‡ìôÇèëÇ¢ÇƒÇ‡ÇÊÇ¢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_SAIMINZYUTU
	
// =============================================================================
//
//
//	Å°Ç≥Ç¢Ç›ÇÒÇ∂Ç„Ç¬			95
//
//
// =============================================================================
WEST_SAIMINZYUTU:

	LOAD_PARTICLE_DROP	0,W_095_SPA
	ADD_PARTICLE 	0,W_095_095_SLEEP_BEAM1, EMTFUNC_FIELD_OPERATOR
	EX_DATA			OPERATOR_DEF_DATA_NUM, OPERATOR_PRI_NONE, OPERATOR_TARGET_DF, OPERATOR_POS_L095SP, OPERATOR_AXIS_AT_095, OPERATOR_FLD_NONE, OPERATOR_CAMERA_NONE
	
	ADD_PARTICLE 	0,W_095_095_SLEEP_BEAM2, EMTFUNC_FIELD_OPERATOR
	EX_DATA			OPERATOR_DEF_DATA_NUM, OPERATOR_PRI_NONE, OPERATOR_TARGET_DF, OPERATOR_POS_L095SP, OPERATOR_AXIS_AT_095, OPERATOR_FLD_NONE, OPERATOR_CAMERA_NONE
	
	SE_FLOW_LR		SEQ_SE_DP_W048

	WAIT			30
	
	ADD_PARTICLE 	0,W_095_095_SLEEP_RING1, EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_095_095_SLEEP_RING2, EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_095_095_SLEEP_ZZZ,   EMTFUNC_DEFENCE_POS
	FUNC_CALL		WEST_SP_WE_SSP_POKE_PAL_FADE, 6,  WE_TOOL_E1, 0, 1, WE_PAL_POISON, 8, 0
	
	SE_R			SEQ_SE_DP_154

	//SE_REPEAT_L		SEQ_SE_DP_W173,19,3
	//SE_WAITPLAY_R	SEQ_SE_DP_W173,5
	//SE_WAITPLAY_R	SEQ_SE_DP_W173,15
	//SE_WAITPLAY_R	SEQ_SE_DP_W173,25
	SE_WAITPLAY_R	SEQ_SE_DP_W173B,15

	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	
	SEQEND
