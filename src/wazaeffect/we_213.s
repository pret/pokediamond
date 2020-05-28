//==============================================================================
/**
 * @file	we_213.s
 * @brief	ÉÅÉçÉÅÉç			213
 * @author	goto
 * @date	2005.07.13(êÖ)
 *
 * Ç±Ç±Ç…êFÅXÇ»âê‡ìôÇèëÇ¢ÇƒÇ‡ÇÊÇ¢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_MEROMERO
	
// =============================================================================
//
//
//	Å°ÉÅÉçÉÅÉç			213
//
//
// =============================================================================
WEST_MEROMERO:

	LOAD_PARTICLE_DROP	0,W_213_SPA
	ADD_PARTICLE 	0,W_213_HART, EMTFUNC_DEFENCE_POS

	//SEPLAY_PAN	SEQ_SE_DP_W213, WAZA_SE_PAN_DF
	//SEPLAY_PAN	SEQ_SE_DP_W204, WAZA_SE_PAN_DF
		
	FUNC_CALL		WEST_SP_WE_204, 0,0,0,0,0,0,0,0,0

	SE_REPEAT_R		SEQ_SE_DP_W204,8,4

	WAIT_FLAG
	
	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	
	SEQEND

