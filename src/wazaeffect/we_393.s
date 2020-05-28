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

	LOAD_PARTICLE_DROP	0,W_393_SPA

	ADD_PARTICLE 	0,W_393_393_DENJI_BALL1, EMTFUNC_FIELD_OPERATOR
	EX_DATA			OPERATOR_DEF_DATA_NUM, OPERATOR_PRI_NONE, OPERATOR_TARGET_AT, OPERATOR_POS_EP, OPERATOR_AXIS_NONE, OPERATOR_FLD_NONE, OPERATOR_CAMERA_NONE

	ADD_PARTICLE 	0,W_393_393_DENJI_BALL2, EMTFUNC_FIELD_OPERATOR
	EX_DATA			OPERATOR_DEF_DATA_NUM, OPERATOR_PRI_NONE, OPERATOR_TARGET_AT, OPERATOR_POS_EP, OPERATOR_AXIS_NONE, OPERATOR_FLD_NONE, OPERATOR_CAMERA_NONE

	SIDE_JP			0, SIDE_MINE, SIDE_ENEMY
	
	SEQEND

SIDE_MINE:

	LOOP_LABEL		2
		SE_L		SEQ_SE_DP_W085B
		FUNC_CALL		WEST_SP_WE_T10, 4,  8, 0,  -8, WE_TOOL_M1 | WE_TOOL_SSP
		WAIT		8
		FUNC_CALL		WEST_SP_WE_T10, 4, 16, 0, +16, WE_TOOL_M1 | WE_TOOL_SSP
		SE_L		SEQ_SE_DP_203
		WAIT		16
		FUNC_CALL		WEST_SP_WE_T10, 4,  8, 0,  -8, WE_TOOL_M1 | WE_TOOL_SSP
		WAIT		8
	LOOP
	
	WAIT_PARTICLE
	EXIT_PARTICLE	0,

	SEQEND
	
SIDE_ENEMY:

	LOOP_LABEL		2
		SE_L		SEQ_SE_DP_W085B
		FUNC_CALL		WEST_SP_WE_T10, 4,  8, 0,  +8, WE_TOOL_M1 | WE_TOOL_SSP
		WAIT		8
		FUNC_CALL		WEST_SP_WE_T10, 4, 16, 0, -16, WE_TOOL_M1 | WE_TOOL_SSP
		SE_L		SEQ_SE_DP_203
		WAIT		16
		FUNC_CALL		WEST_SP_WE_T10, 4,  8, 0,  +8, WE_TOOL_M1 | WE_TOOL_SSP
		WAIT		8
	LOOP
	
	WAIT_PARTICLE
	EXIT_PARTICLE	0,

	SEQEND