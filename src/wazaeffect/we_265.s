//==============================================================================
/**
 * @file	we_265.s
 * @brief	Ç´Ç¬ÇØ			265
 * @author	goto
 * @date	2005.07.13(êÖ)
 *
 * Ç±Ç±Ç…êFÅXÇ»âê‡ìôÇèëÇ¢ÇƒÇ‡ÇÊÇ¢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_265
	
// =============================================================================
//
//
//	Å°Ç´Ç¬ÇØ			265
//
//
// =============================================================================
#define W265_RES_NO			(0)
#define W265_RES_NUM		(2)
#define W265_ACT_NUM		(1)
WEST_265:
		
	// --- oam
	LOAD_PARTICLE_DROP	0,W_265_SPA		
	CATS_RES_INIT			W265_RES_NO, W265_ACT_NUM, W265_RES_NUM, W265_RES_NUM, W265_RES_NUM, W265_RES_NUM, 0, 0

	CATS_CAHR_RES_LOAD		W265_RES_NO, EFFECT_265_NCGR_BIN
	CATS_PLTT_RES_LOAD		W265_RES_NO, EFFECT_265_NCLR, 1
	CATS_CELL_RES_LOAD		W265_RES_NO, EFFECT_265_NCER_BIN
	CATS_CELL_ANM_RES_LOAD	W265_RES_NO, EFFECT_265_NANR_BIN
	
	
	CATS_ACT_ADD		W265_RES_NO, WEST_CSP_FREE, EFFECT_265_NCGR_BIN, EFFECT_265_NCLR, EFFECT_265_NCER_BIN, EFFECT_265_NANR_BIN, 0, 0, 3, 0, +24, 0
	// ----------------------------------

	WAIT				30
	//SE_R			SEQ_SE_DP_W003
	SE_REPEAT_R		SEQ_SE_DP_030C,4,2

	ADD_PARTICLE 	0,W_265_265_HITMARK_L, EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_265_265_HITBURN_L, EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_265_265_HITMARK_R, EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_265_265_HITBURN_R, EMTFUNC_DEFENCE_POS
	
	FUNC_CALL		WEST_SP_WT_SHAKE, 5, SHAKE_S_X, 0, SHAKE_S_WAIT, SHAKE_S_NUM*3,  WE_TOOL_E1 | WE_TOOL_SSP,

	WAIT_FLAG

	WAIT_PARTICLE
	EXIT_PARTICLE	0,

	CATS_RES_FREE		W265_RES_NO
	SEQEND
