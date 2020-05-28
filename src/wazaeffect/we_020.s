//==============================================================================
/**
 * @file	we_020.s
 * @brief	ÇµÇﬂÇ¬ÇØÇÈ			20
 * @author	goto
 * @date	2005.07.13(êÖ)
 *
 * Ç±Ç±Ç…êFÅXÇ»âê‡ìôÇèëÇ¢ÇƒÇ‡ÇÊÇ¢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_SIMETUKERU
	
// =============================================================================
//
//
//	Å°ÇµÇﬂÇ¬ÇØÇÈ			20
//
//
// =============================================================================
WEST_SIMETUKERU:

	LOAD_PARTICLE_DROP	0,W_020_SPA
//	CAMERA_CHG		0,WE_CAMERA_TYPE_PERSPECTIV
	
//	ADD_PARTICLE 	0,W_020_020_RING1, EMTFUNC_FIELD_OPERATOR
//	EX_DATA			OPERATOR_DEF_DATA_NUM, OPERATOR_PRI_NONE, OPERATOR_TARGET_NONE, OPERATOR_POS_NONE, OPERATOR_AXIS_NONE, OPERATOR_FLD_NONE, OPERATOR_CAMERA_DF
	
//	ADD_PARTICLE 	0,W_020_020_RING2, EMTFUNC_FIELD_OPERATOR
//	EX_DATA			OPERATOR_DEF_DATA_NUM, OPERATOR_PRI_NONE, OPERATOR_TARGET_NONE, OPERATOR_POS_NONE, OPERATOR_AXIS_NONE, OPERATOR_FLD_NONE, OPERATOR_CAMERA_DF
	
	ADD_PARTICLE 	0,W_020_020_RING1, EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_020_020_RING2, EMTFUNC_DEFENCE_POS
	
	LOOP_LABEL		2

		//SE_L			SEQ_SE_DP_W104

		FUNC_CALL		WEST_SP_WE_T05, 3, 3, +WE_MOVE_X_VAL_DEF, WE_TOOL_M1 | WE_TOOL_SSP
		WAIT_FLAG
		FUNC_CALL		WEST_SP_WE_T05, 3, 3, -WE_MOVE_X_VAL_DEF, WE_TOOL_M1 | WE_TOOL_SSP
		WAIT			1	
		FUNC_CALL		WEST_SP_WE_SSP_POKE_SCALE_UPDOWN, 8, (WE_TOOL_E1 | WE_TOOL_SSP), 100, 70, 100, 100, 100, 1, (5 << 16) | 5
		WAIT_FLAG
		SE_R			SEQ_SE_DP_W020B
		
	LOOP

	WAIT_PARTICLE
	EXIT_PARTICLE	0,	
	SEQEND
