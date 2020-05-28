//==============================================================================
/**
 * @file	we_202.s
 * @brief	ギガドレイン			202
 * @author	goto
 * @date	2005.07.13(水)
 *
 * ここに色々な解説等を書いてもよい
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_GIGADOREIN
	
// =============================================================================
//
//
//	■ギガドレイン			202
//
//
// =============================================================================
WEST_GIGADOREIN:

	LOAD_PARTICLE_DROP	0,W_202_SPA
	
	//SE_FLOW_RL	SEQ_SE_DP_W071
	//SE_REPEAT_C	SEQ_SE_DP_W145C,2,24
	SE_REPEAT_C		SEQ_SE_DP_W202,2,18

	ADD_PARTICLE 	0,W_202_202_GIGADRAIN_BALL1, EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_202_202_GIGADRAIN_BALL2, EMTFUNC_FIELD_OPERATOR
	EX_DATA			OPERATOR_DEF_DATA_NUM, OPERATOR_PRI_NONE, OPERATOR_TARGET_DF, OPERATOR_POS_EP, OPERATOR_AXIS_AT, OPERATOR_FLD_MAGNET_POS, OPERATOR_CAMERA_NONE
	EX_DATA			OPERATOR_FLD_EX_DATA_NUM, OPERATOR_FLD_AT,OPERATOR_EX_REVERCE_ON,0,0,0
	
	ADD_PARTICLE 	0,W_202_202_GIGADRAIN_KIRA, EMTFUNC_ATTACK_POS
	
	WAIT			60
	FUNC_CALL		WEST_SP_WE_SSP_POKE_PAL_FADE, 6,  WE_TOOL_M1, 0, 1, WE_PAL_WHITE, 10,0

	SE_L			SEQ_SE_DP_W071B

	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	
	SEQEND
