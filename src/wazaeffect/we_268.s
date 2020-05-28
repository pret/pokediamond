//==============================================================================
/**
 * @file	we_268.s
 * @brief	Ç∂Ç„Ç§Ç≈ÇÒ			268
 * @author	goto
 * @date	2005.07.13(êÖ)
 *
 * Ç±Ç±Ç…êFÅXÇ»âê‡ìôÇèëÇ¢ÇƒÇ‡ÇÊÇ¢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_ZYUUDEN
	
// =============================================================================
//
//
//	Å°Ç∂Ç„Ç§Ç≈ÇÒ			268
//
//
// =============================================================================
WEST_ZYUUDEN:
	
	LOAD_PARTICLE_DROP	0,W_268_SPA

	FUNC_CALL		WEST_SP_WE_HAIKEI_PAL_FADE, 5, 0, 1, 0, 12, WE_PAL_BLACK,
	WAIT_FLAG

	ADD_PARTICLE 	0,W_268_268_ELE_CHARGE1, EMTFUNC_ATTACK_POS
	ADD_PARTICLE 	0,W_268_268_ELE_CHARGE2, EMTFUNC_ATTACK_POS
	ADD_PARTICLE 	0,W_268_268_ELE_CHARGE3, EMTFUNC_ATTACK_POS
	ADD_PARTICLE 	0,W_268_268_ELE_CHARGE4, EMTFUNC_ATTACK_POS

	WAIT			15
	//SE_REPEAT_L		SEQ_SE_DP_W085B,8,9
	SE_REPEAT_L		SEQ_SE_DP_W360,12,5
	WAIT			77
	SE_L			SEQ_SE_DP_W085C

	WAIT_PARTICLE
	EXIT_PARTICLE	0,

FUNC_CALL		WEST_SP_WE_HAIKEI_PAL_FADE, 5, 0, 1, 12, 0, WE_PAL_BLACK,
WAIT_FLAG
	
	SEQEND
