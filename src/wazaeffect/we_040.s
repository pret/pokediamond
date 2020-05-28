//==============================================================================
/**
 * @file	we_040.s
 * @brief	Ç«Ç≠ÇŒÇË			40
 * @author	goto
 * @date	2005.07.13(êÖ)
 *
 * Ç±Ç±Ç…êFÅXÇ»âê‡ìôÇèëÇ¢ÇƒÇ‡ÇÊÇ¢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_DOKUBARI
	
// =============================================================================
//
//
//	Å°Ç«Ç≠ÇŒÇË			40
//
//
// =============================================================================
WEST_DOKUBARI:
	
	LOAD_PARTICLE_DROP	0,W_040_SPA

	FUNC_CALL		WEST_SP_WE_T10,	4, 2, +14, -8, WE_TOOL_M1 | WE_TOOL_SSP
	WAIT_FLAG
	
	ADD_PARTICLE 	0,W_040_040_NEEDLE_BEAM, EMTFUNC_FIELD_OPERATOR
	EX_DATA			OPERATOR_DEF_DATA_NUM, OPERATOR_PRI_NONE, OPERATOR_TARGET_DF, OPERATOR_POS_LSP, OPERATOR_AXIS_AT, OPERATOR_FLD_NONE, OPERATOR_CAMERA_NONE
	
	ADD_PARTICLE 	0,W_040_040_HIT_MARK,	 EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_040_040_BALL_UP,	 EMTFUNC_DEFENCE_POS
	FUNC_CALL		WEST_SP_WE_T10,	4, 2, -14, +8, WE_TOOL_M1 | WE_TOOL_SSP
	
	//SE_FLOW_LR	SEQ_SE_DP_HURU
	SE_FLOW_LR		SEQ_SE_DP_HURU2
	WAIT			5
	
	FUNC_CALL		WEST_SP_WE_SSP_POKE_PAL_FADE, 6,  WE_TOOL_E1, 0, 1, WE_PAL_POISON, 10,0
	
	FUNC_CALL		WEST_SP_WT_SHAKE, 5, 1, 0, 1, 1,  WE_TOOL_E1 | WE_TOOL_SSP,

	SE_WAITPLAY_R	SEQ_SE_DP_W004,3
	//SE_WAITPLAY_R	SEQ_SE_DP_154,6
	SE_REPEAT_R		SEQ_SE_DP_W092D,8,4

	WAIT_FLAG
	
	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	
	SEQEND
