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

	.global		WEST_402
	
// =============================================================================
//
//
//	Å°ÇÕÇΩÇ≠
//
//
// =============================================================================
WEST_402:
	
	LOAD_PARTICLE_DROP	0,W_402_SPA

	SE_C			SEQ_SE_DP_HURU2
	ADD_PARTICLE_EMIT_SET 	0,0,W_402_402_TANE_UP, EMTFUNC_ATTACK_POS
	FUNC_CALL				WEST_SP_EMIT_PARABOLIC, 6, 0, 0, 0, 0, 18, 64,
	WAIT			2
	
	SE_C			SEQ_SE_DP_HURU2
	ADD_PARTICLE_EMIT_SET 	0,1,W_402_402_TANE_UP, EMTFUNC_ATTACK_POS
	FUNC_CALL				WEST_SP_EMIT_PARABOLIC, 6, 1, 0, 0, 0, 18, 64,
	WAIT			2
	
	SE_C			SEQ_SE_DP_HURU2
	ADD_PARTICLE_EMIT_SET 	0,2,W_402_402_TANE_UP, EMTFUNC_ATTACK_POS
	FUNC_CALL				WEST_SP_EMIT_PARABOLIC, 6, 2, 0, 0, 0, 18, 64,
	WAIT			2
	
	///< Ç±ÇÃéûì_Ç≈îöî≠
	ADD_PARTICLE 	0,W_402_402_TANE_BOMB, EMTFUNC_FIELD_OPERATOR
	EX_DATA			OPERATOR_DEF_DATA_NUM, OPERATOR_PRI_NONE, OPERATOR_TARGET_DF, OPERATOR_POS_EP, OPERATOR_AXIS_NONE, OPERATOR_FLD_NONE, OPERATOR_CAMERA_NONE
	
	SE_C			SEQ_SE_DP_HURU2
	ADD_PARTICLE_EMIT_SET	0,3,W_402_402_TANE_UP, EMTFUNC_ATTACK_POS
	FUNC_CALL				WEST_SP_EMIT_PARABOLIC, 6, 3, 0, 0, 0, 18, 64,
	WAIT			2
	
	FUNC_CALL		WEST_SP_WT_SHAKE, 5, SHAKE_S_X, 0, SHAKE_S_WAIT, SHAKE_S_NUM*6,  WE_TOOL_E1 | WE_TOOL_SSP,
		
	SE_C			SEQ_SE_DP_HURU2
	ADD_PARTICLE_EMIT_SET 	0,4,W_402_402_TANE_UP, EMTFUNC_ATTACK_POS
	FUNC_CALL				WEST_SP_EMIT_PARABOLIC, 6, 4, 0, 0, 0, 18, 64,
	
	SE_WAITPLAY_R	SEQ_SE_DP_W120,10
	SE_WAITPLAY_R	SEQ_SE_DP_W120,20
	SE_WAITPLAY_R	SEQ_SE_DP_W120,30
	
	WAIT_FLAG

	WAIT_PARTICLE
	EXIT_PARTICLE	0,
		
	SEQEND

