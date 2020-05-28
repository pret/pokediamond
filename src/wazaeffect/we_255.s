//==============================================================================
/**
 * @file	we_255.s
 * @brief	ÇÕÇ´ÇæÇ∑			255
 * @author	goto
 * @date	2005.07.13(êÖ)
 *
 * Ç±Ç±Ç…êFÅXÇ»âê‡ìôÇèëÇ¢ÇƒÇ‡ÇÊÇ¢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_HAKIDASU
	
// =============================================================================
//
//
//	Å°ÇÕÇ´ÇæÇ∑			255
//
//
// =============================================================================

#define KEEP_WAIT	(15)
#define KEEP_WAIT_2	(15 + 10)

WEST_HAKIDASU:

	LOAD_PARTICLE_DROP	0,W_255_SPA
	
	SE_L			SEQ_SE_DP_W036
	
	FUNC_CALL		WEST_SP_WE_T06, 5, 70,120,10,5,KEEP_WAIT
	WAIT			KEEP_WAIT_2
	//SE_L			SEQ_SE_DP_W255
	SE_REPEAT_L		SEQ_SE_DP_W255E,5,2
	
	ADD_PARTICLE 	0,W_255_255_BURN, EMTFUNC_ATTACK_POS
	
	WAIT_FLAG
	ADD_PARTICLE 	0,W_255_255_HIT_MARK, EMTFUNC_DEFENCE_POS
	
	WAIT			15
	SE_REPEAT_R		SEQ_SE_DP_W025B,2,3
	FUNC_CALL		WEST_SP_WT_SHAKE, 5, SHAKE_M_X, 0, SHAKE_M_WAIT, SHAKE_M_NUM*2,  WE_TOOL_E1 | WE_TOOL_SSP,

	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	
	SEQEND
