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

	LOAD_PARTICLE_DROP	0,W_388_SPA
	
	ADD_PARTICLE 	0,W_388_388_NAYAMI_TANE1, EMTFUNC_DEFENCE_POS
	FUNC_CALL		WEST_SP_EMIT_PARABOLIC, 6, 0, 0, 0, 0, 19, 64,

	SE_FLOW_LR		SEQ_SE_DP_001

	WAIT			15
	
	ADD_PARTICLE 	0,W_388_388_NAYAMI_KEMURI, EMTFUNC_FIELD_OPERATOR
	EX_DATA			OPERATOR_DEF_DATA_NUM, OPERATOR_PRI_NONE, OPERATOR_TARGET_DF, OPERATOR_POS_EP, OPERATOR_AXIS_NONE, OPERATOR_FLD_NONE, OPERATOR_CAMERA_NONE

	FUNC_CALL		WEST_SP_WT_SHAKE, 5, SHAKE_M_X, 0, SHAKE_M_WAIT, SHAKE_M_NUM,  WE_TOOL_E1 | WE_TOOL_SSP,
	
	SE_R			SEQ_SE_DP_112

	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	
	SEQEND
