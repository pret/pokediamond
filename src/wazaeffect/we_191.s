//==============================================================================
/**
 * @file	we_191.s
 * @brief	Ç‹Ç´Ç—Çµ			191
 * @author	goto
 * @date	2005.07.13(êÖ)
 *
 * Ç±Ç±Ç…êFÅXÇ»âê‡ìôÇèëÇ¢ÇƒÇ‡ÇÊÇ¢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_MAKIBISI
	
// =============================================================================
//
//
//	Å°Ç‹Ç´Ç—Çµ			191
//
//
// =============================================================================
WEST_MAKIBISI:
	//SE_REPEAT_R		SEQ_SE_DP_W026,2,8

	LOAD_PARTICLE_DROP	0,W_191_SPA

	SE_REPEAT_R		SEQ_SE_DP_W026,6,5
	
	ADD_PARTICLE_EMIT_SET 	0, 0, W_191_191_MAKIBISI_MAKIBISI1,	EMTFUNC_ATTACK_POS
	FUNC_CALL		WEST_SP_EMIT_PARABOLIC, 6, 0, 8, -3, 0, 12, 64,
	
	WAIT			5
	
	ADD_PARTICLE_EMIT_SET 	0, 1, W_191_191_MAKIBISI_MAKIBISI1,	EMTFUNC_ATTACK_POS
	FUNC_CALL		WEST_SP_EMIT_PARABOLIC, 6, 1, 4, -5, 0, 12, 64,

	ADD_PARTICLE 	0,W_191_191_MAKIBISI_MAKIBISI2, EMTFUNC_DF_SIDE
	
	WAIT			5

	ADD_PARTICLE_EMIT_SET 	0, 2, W_191_191_MAKIBISI_MAKIBISI1,	EMTFUNC_ATTACK_POS
	FUNC_CALL		WEST_SP_EMIT_PARABOLIC, 6, 2, 0, -6, 0, 12, 64,
	
	WAIT			5
	
	ADD_PARTICLE_EMIT_SET 	0, 3, W_191_191_MAKIBISI_MAKIBISI1,	EMTFUNC_ATTACK_POS
	FUNC_CALL		WEST_SP_EMIT_PARABOLIC, 6, 3, -8, -6, 0, 12, 64,
	
	WAIT			5
	
	ADD_PARTICLE_EMIT_SET 	0, 4, W_191_191_MAKIBISI_MAKIBISI1,	EMTFUNC_ATTACK_POS
	FUNC_CALL		WEST_SP_EMIT_PARABOLIC, 6, 4, -4, -3, 0, 12, 64,
		
	WAIT			6

	//SE_R			SEQ_SE_DP_W030

	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	
	SEQEND
