//==============================================================================
/**
 * @file	we_138.s
 * @brief	Ç‰ÇﬂÇ≠Ç¢			138
 * @author	goto
 * @date	2005.07.13(êÖ)
 *
 * Ç±Ç±Ç…êFÅXÇ»âê‡ìôÇèëÇ¢ÇƒÇ‡ÇÊÇ¢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_YUMEKUI
	
// =============================================================================
//
//
//	Å°Ç‰ÇﬂÇ≠Ç¢			138
//
//
// =============================================================================
WEST_YUMEKUI:

	LOAD_PARTICLE_DROP	1,W_409_SPA
	
	LOAD_PARTICLE_DROP	0,W_138_SPA
	FUNC_CALL		WEST_SP_WE_HAIKEI_PAL_FADE, 5, 0, 1, 0, 12, WE_PAL_BLACK,
	WAIT_FLAG

	ADD_PARTICLE 	1,W_409_409_BALL_DRAIN, EMTFUNC_FIELD_OPERATOR
	EX_DATA			OPERATOR_DEF_DATA_NUM, OPERATOR_PRI_NONE, OPERATOR_TARGET_DF, OPERATOR_POS_EP, OPERATOR_AXIS_AT, OPERATOR_FLD_MAGNET_POS, OPERATOR_CAMERA_NONE
	EX_DATA			OPERATOR_FLD_EX_DATA_NUM, OPERATOR_FLD_AT,OPERATOR_EX_REVERCE_ON,0,0,0
	WAIT			10
	
	ADD_PARTICLE 	0,W_138_138_YUMEKUI_KIRA, EMTFUNC_ATTACK_POS
	
	SE_FLOW_RL		SEQ_SE_DP_153
	SE_WAITPLAY_L	SEQ_SE_DP_W071B,75
	
	WAIT			75
	FUNC_CALL		WEST_SP_WE_SSP_POKE_PAL_FADE, 6,  WE_TOOL_M1, 0, 1, WE_PAL_WHITE, 10,0

	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	EXIT_PARTICLE	1,
	
	FUNC_CALL		WEST_SP_WE_HAIKEI_PAL_FADE, 5, 0, 1, 12, 0, WE_PAL_BLACK,
	WAIT_FLAG


	SEQEND
