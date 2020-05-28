//==============================================================================
/**
 * @file	we_256.s
 * @brief	ÇÃÇ›Ç±Çﬁ			256
 * @author	goto
 * @date	2005.07.13(êÖ)
 *
 * Ç±Ç±Ç…êFÅXÇ»âê‡ìôÇèëÇ¢ÇƒÇ‡ÇÊÇ¢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_NOMIKOMU
	
// =============================================================================
//
//
//	Å°ÇÃÇ›Ç±Çﬁ			256
//
//
// =============================================================================

#define KEEP_WAIT	(15)

#define Y_TOP		(160)
#define FWAIT		(1)
#define IWAIT		(5)
#define OWAIT		(15)
#define TWAIT		(IWAIT + OWAIT)

WEST_NOMIKOMU:

	LOAD_PARTICLE_DROP	0,W_256_SPA
	
	SE_L			SEQ_SE_DP_W036
	
	FUNC_CALL		WEST_SP_WE_SSP_POKE_SCALE_UPDOWN, 8, (WE_TOOL_M1 | WE_TOOL_SSP), 100, 80, 100, Y_TOP, 100, 1, (IWAIT << 16) | OWAIT
	
	WAIT			5
	
	ADD_PARTICLE 	0,W_256_256_BALL_UP,	EMTFUNC_ATTACK_POS
	ADD_PARTICLE 	0,W_256_256_BALL_DOWN,	EMTFUNC_ATTACK_POS
	ADD_PARTICLE 	0,W_256_256_KIRA_BURN,	EMTFUNC_ATTACK_POS
	
	//SE_L			SEQ_SE_DP_W255
	SE_L			SEQ_SE_DP_W255F
	
	WAIT			55
	SE_L			SEQ_SE_DP_W071B
	WAIT			5
	FUNC_CALL		WEST_SP_WE_SSP_POKE_PAL_FADE, 6,  WE_TOOL_M1, 0, 1, WE_PAL_WHITE, 10,0

	WAIT_FLAG

	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	
	SEQEND
