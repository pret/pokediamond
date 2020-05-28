//==============================================================================
/**
 * @file	we_047.s
 * @brief	Ç§ÇΩÇ§			47
 * @author	goto
 * @date	2005.07.13(êÖ)
 *
 * Ç±Ç±Ç…êFÅXÇ»âê‡ìôÇèëÇ¢ÇƒÇ‡ÇÊÇ¢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_UTAU
	
// =============================================================================
//
//
//	Å°Ç§ÇΩÇ§			47
//
//
// =============================================================================
WEST_UTAU:
	
	LOAD_PARTICLE_DROP	0,W_047_SPA
	
	FUNC_CALL		WEST_SP_WE_HAIKEI_PAL_FADE, 5, 0, 1, 0, 12, WE_PAL_WHITE,
	WAIT_FLAG

	ADD_PARTICLE 	0,W_047_047_RING_BIG1, EMTFUNC_ATTACK_POS
	ADD_PARTICLE 	0,W_047_047_RING_BIG2, EMTFUNC_ATTACK_POS
	ADD_PARTICLE 	0,W_047_047_TONE_BEAM, EMTFUNC_FIELD_OPERATOR
	EX_DATA			OPERATOR_DEF_DATA_NUM, OPERATOR_PRI_NONE, OPERATOR_TARGET_DF, OPERATOR_POS_LSP, OPERATOR_AXIS_AT, OPERATOR_FLD_NONE, OPERATOR_CAMERA_NONE
	
	SE_FLOW_LR		SEQ_SE_DP_W047

	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	
	FUNC_CALL		WEST_SP_WE_HAIKEI_PAL_FADE, 5, 0, 1, 12, 0, WE_PAL_WHITE,
	WAIT_FLAG

	SEQEND
