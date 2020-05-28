//==============================================================================
/**
 * @file	we_216.s
 * @brief	Ç®ÇÒÇ™Ç¶Çµ			216
 * @author	goto
 * @date	2005.07.13(êÖ)
 *
 * Ç±Ç±Ç…êFÅXÇ»âê‡ìôÇèëÇ¢ÇƒÇ‡ÇÊÇ¢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_ONGAESI
	
// =============================================================================
//
//
//	Å°Ç®ÇÒÇ™Ç¶Çµ			216
//
//
// =============================================================================
WEST_ONGAESI:
	
	LOAD_PARTICLE_DROP	0,W_216_SPA
	
	FUNC_CALL		WEST_SP_WE_216, 0,0,0,0,0,0,0,0,0
	LOOP_LABEL	2
		SE_L			SEQ_SE_DP_W039
		WAIT 16
	LOOP
	
	WAIT_FLAG

	ADD_PARTICLE 	0,W_216_216_ON_HIT1, EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_216_216_ON_HIT2, EMTFUNC_DEFENCE_POS
	FUNC_CALL		WEST_SP_WT_SHAKE, 5, SHAKE_S_X, 0, SHAKE_S_WAIT, SHAKE_S_NUM,  WE_TOOL_E1 | WE_TOOL_SSP,
	SE_R			SEQ_SE_DP_W025B

	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	
	SEQEND
