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
WEST_446:
	LOAD_PARTICLE_DROP	0,W_446_SPA
	
	SE_FLOW_LR		SEQ_SE_DP_W070
	ADD_PARTICLE_EMIT_SET 	0, 0, W_446_446_STEALTH_STONE1,	EMTFUNC_ATTACK_POS
	FUNC_CALL		WEST_SP_EMIT_PARABOLIC, 6, 0, 8, -3, 0, 12, 64,
	
	WAIT			5
	
	SE_FLOW_LR		SEQ_SE_DP_W070
	ADD_PARTICLE_EMIT_SET 	0, 1, W_446_446_STEALTH_STONE1,	EMTFUNC_ATTACK_POS
	FUNC_CALL		WEST_SP_EMIT_PARABOLIC, 6, 1, 4, -5, 0, 12, 64,
	
	WAIT			5

	ADD_PARTICLE 	0,W_446_446_STEALTH_STONE2,		EMTFUNC_DF_SIDE
	FUNC_CALL		WEST_SP_WT_SHAKE, 5, SHAKE_S_X, 0, SHAKE_S_WAIT, SHAKE_S_NUM*3,  WE_TOOL_E1 | WE_TOOL_SSP,
	FUNC_CALL		WEST_SP_WT_SHAKE, 5, SHAKE_S_X, 0, SHAKE_S_WAIT, SHAKE_S_NUM*3,  WE_TOOL_E2 | WE_TOOL_SSP,
		
	SE_FLOW_LR		SEQ_SE_DP_W070
	ADD_PARTICLE_EMIT_SET 	0, 2, W_446_446_STEALTH_STONE1,	EMTFUNC_ATTACK_POS
	FUNC_CALL		WEST_SP_EMIT_PARABOLIC, 6, 2, 0, -6, 0, 12, 64,
	
	WAIT			5
	
	SE_FLOW_LR		SEQ_SE_DP_W070
	ADD_PARTICLE_EMIT_SET 	0, 3, W_446_446_STEALTH_STONE1,	EMTFUNC_ATTACK_POS
	FUNC_CALL		WEST_SP_EMIT_PARABOLIC, 6, 3, -8, -6, 0, 12, 64,
	
	WAIT			5
	
	SE_FLOW_LR		SEQ_SE_DP_W070
	ADD_PARTICLE_EMIT_SET 	0, 4, W_446_446_STEALTH_STONE1,	EMTFUNC_ATTACK_POS
	FUNC_CALL		WEST_SP_EMIT_PARABOLIC, 6, 4, -4, -3, 0, 12, 64,
	
	WAIT_FLAG
		
	WAIT_PARTICLE
	EXIT_PARTICLE	0,


	SEQEND
