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

	LOAD_PARTICLE_DROP	0,W_412_SPA

FUNC_CALL		WEST_SP_WE_HAIKEI_PAL_FADE, 5, 0, 1, 0, 12, WE_PAL_BLACK,
WAIT_FLAG

	//SE_L			SEQ_SE_DP_412

	///< ó≠Çﬂ
	ADD_PARTICLE 	0,W_412_412_BALL_BIG1, EMTFUNC_FIELD_OPERATOR
	EX_DATA			OPERATOR_DEF_DATA_NUM, OPERATOR_PRI_NONE, OPERATOR_TARGET_AT, OPERATOR_POS_EP, OPERATOR_AXIS_NONE, OPERATOR_FLD_NONE, OPERATOR_CAMERA_NONE

	SE_L			SEQ_SE_DP_211
	WAIT			30
	SE_FLOW_LR		SEQ_SE_DP_W145

	///< 
	ADD_PARTICLE 	0,W_412_412_BALL_BEAM, EMTFUNC_ATTACK_POS
	FUNC_CALL		WEST_SP_EMIT_STRAIGHT, 6, 0, 0, 0, 0, 17, 64,
	
	WAIT			16
	//SE_R			SEQ_SE_DP_W145C
	SE_R			SEQ_SE_DP_402

	///< 
	ADD_PARTICLE 	0,W_412_412_HIT_MARK, EMTFUNC_DEFENCE_POS

	FUNC_CALL		WEST_SP_WT_SHAKE, 5, SHAKE_S_X, 0, SHAKE_S_WAIT, SHAKE_S_NUM,  WE_TOOL_E1 | WE_TOOL_SSP,

	WAIT_PARTICLE
	EXIT_PARTICLE	0,

FUNC_CALL		WEST_SP_WE_HAIKEI_PAL_FADE, 5, 0, 1, 12, 0, WE_PAL_BLACK,
WAIT_FLAG
	
	SEQEND

