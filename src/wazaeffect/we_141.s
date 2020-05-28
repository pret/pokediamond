//==============================================================================
/**
 * @file	we_141.s
 * @brief	Ç´Ç„Ç§ÇØÇ¬			141
 * @author	goto
 * @date	2005.07.13(êÖ)
 *
 * Ç±Ç±Ç…êFÅXÇ»âê‡ìôÇèëÇ¢ÇƒÇ‡ÇÊÇ¢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_KYUUKETU
	
// =============================================================================
//
//
//	Å°Ç´Ç„Ç§ÇØÇ¬			141
//
//
// =============================================================================
WEST_KYUUKETU:
	
	LOAD_PARTICLE_DROP	0,W_141_SPA

	SE_FLOW_LR		SEQ_SE_DP_HURU

	ADD_PARTICLE 	0,W_141_141_KYUUKETU_NEEDL, EMTFUNC_FIELD_OPERATOR
	EX_DATA			OPERATOR_DEF_DATA_NUM, OPERATOR_PRI_NONE, OPERATOR_TARGET_DF, OPERATOR_POS_SP, OPERATOR_AXIS_AT, OPERATOR_FLD_NONE, OPERATOR_CAMERA_NONE
	
	WAIT			8
	
	ADD_PARTICLE 	0,W_141_141_KYUUKETU_HIT, EMTFUNC_DEFENCE_POS

	ADD_PARTICLE 	0,W_141_141_KYUUKETU_BALL, EMTFUNC_FIELD_OPERATOR
	EX_DATA			OPERATOR_DEF_DATA_NUM, OPERATOR_PRI_NONE, OPERATOR_TARGET_DF, OPERATOR_POS_EP, OPERATOR_AXIS_AT, OPERATOR_FLD_MAGNET_POS, OPERATOR_CAMERA_NONE
	EX_DATA			OPERATOR_FLD_EX_DATA_NUM, OPERATOR_FLD_AT,OPERATOR_EX_REVERCE_ON,0,0,0

	SE_R			SEQ_SE_DP_W071
	WAIT			10
	SE_FLOW_RL		SEQ_SE_DP_W080B
	
	ADD_PARTICLE 	0,W_141_141_KYUUKETU_KIRA, EMTFUNC_ATTACK_POS
	
	WAIT			75
	SE_L			SEQ_SE_DP_W071B
	FUNC_CALL		WEST_SP_WE_SSP_POKE_PAL_FADE, 6,  WE_TOOL_M1, 0, 1, WE_PAL_WHITE, 10,0

	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	
	SEQEND
