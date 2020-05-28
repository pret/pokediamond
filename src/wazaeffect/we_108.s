//==============================================================================
/**
 * @file	we_108.s
 * @brief	Ç¶ÇÒÇ‹Ç≠			108
 * @author	goto
 * @date	2005.07.13(êÖ)
 *
 * Ç±Ç±Ç…êFÅXÇ»âê‡ìôÇèëÇ¢ÇƒÇ‡ÇÊÇ¢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_ENMAKU
	
// =============================================================================
//
//
//	Å°Ç¶ÇÒÇ‹Ç≠			108
//
//
// =============================================================================
WEST_ENMAKU:
	
	LOAD_PARTICLE_DROP	0,W_108_SPA
	LOAD_PARTICLE_DROP	1,W_108_SPA

	ADD_PARTICLE 	1,W_108_108_ENMAK_KEMU,  EMTFUNC_DEFENCE_POS
	WAIT	1
		
	ADD_PARTICLE_EMIT_SET 	0,1,W_108_108_ENMAK_BALL, EMTFUNC_ATTACK_POS
	FUNC_CALL		WEST_SP_EMIT_PARABOLIC, 6, 1, 0, 0, 0, 13, 64,
	
	SE_FLOW_LR		SEQ_SE_DP_W104

	WAIT			13
	//SE_REPEAT_R	SEQ_SE_DP_W028,3,6
	SE_REPEAT_R		SEQ_SE_DP_W028B,3,6

	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	EXIT_PARTICLE	1,
	
	SEQEND
