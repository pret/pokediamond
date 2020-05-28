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
	//SE_REPEAT_R		SEQ_SE_DP_W026,2,8
	//SE_REPEAT_R		SEQ_SE_DP_W026,4,8

	LOAD_PARTICLE_DROP	0,W_390_SPA

	SE_REPEAT_R		SEQ_SE_DP_W026,6,5

	ADD_PARTICLE_EMIT_SET 	0, 0, W_390_390_DOKUB_MAKI1,	EMTFUNC_ATTACK_POS
	FUNC_CALL		WEST_SP_EMIT_PARABOLIC, 6, 0, 8, -3, 0, 12, 64,
	
	WAIT			5
	
	ADD_PARTICLE_EMIT_SET 	0, 1, W_390_390_DOKUB_MAKI1,	EMTFUNC_ATTACK_POS
	FUNC_CALL		WEST_SP_EMIT_PARABOLIC, 6, 1, 4, -5, 0, 12, 64,
	
	WAIT			5

	ADD_PARTICLE_EMIT_SET 	0, 2, W_390_390_DOKUB_MAKI1,	EMTFUNC_ATTACK_POS
	FUNC_CALL		WEST_SP_EMIT_PARABOLIC, 6, 2, 0, -6, 0, 12, 64,
	
	ADD_PARTICLE 	0,W_390_390_DOKUB_MAKI2, EMTFUNC_DF_SIDE
	
	WAIT			5
	
	ADD_PARTICLE_EMIT_SET 	0, 3, W_390_390_DOKUB_MAKI1,	EMTFUNC_ATTACK_POS
	FUNC_CALL		WEST_SP_EMIT_PARABOLIC, 6, 3, -8, -6, 0, 12, 64,
	
	WAIT			5
	
	ADD_PARTICLE_EMIT_SET 	0, 4, W_390_390_DOKUB_MAKI1,	EMTFUNC_ATTACK_POS
	FUNC_CALL		WEST_SP_EMIT_PARABOLIC, 6, 4, -8, -6, 0, 12, 64,
	
	WAIT			5

	ADD_PARTICLE 	0,W_390_390_DOKUB_BALL, EMTFUNC_DF_SIDE

	WAIT			10
	//SE_R			SEQ_SE_DP_154
	SE_REPEAT_R		SEQ_SE_DP_W092D,4,3
	FUNC_CALL		WEST_SP_WE_SSP_POKE_PAL_FADE, 6,  WE_TOOL_E1, 0, 1, WE_PAL_POISON, 10,0
	FUNC_CALL		WEST_SP_WE_SSP_POKE_PAL_FADE, 6,  WE_TOOL_E2, 0, 1, WE_PAL_POISON, 10,0
		
	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	
	SEQEND
