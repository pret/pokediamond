//==============================================================================
/**
 * @file	we_274.s
 * @brief	ÇÀÇ±ÇÃÇƒ			274
 * @author	goto
 * @date	2005.07.13(êÖ)
 *
 * Ç±Ç±Ç…êFÅXÇ»âê‡ìôÇèëÇ¢ÇƒÇ‡ÇÊÇ¢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_NEKONOTE
	
// =============================================================================
//
//
//	Å°ÇÀÇ±ÇÃÇƒ			274
//
//
// =============================================================================
#define W274_OAM_MAX	(12)

WEST_NEKONOTE:

	CATS_RES_INIT			0, W274_OAM_MAX, 1,1,1,1,0,0
	CATS_CAHR_RES_LOAD		0, EFFECT_274_NCGR_BIN
	CATS_PLTT_RES_LOAD		0, EFFECT_274_NCLR, 1
	CATS_CELL_RES_LOAD		0, EFFECT_274_NCER_BIN
	CATS_CELL_ANM_RES_LOAD	0, EFFECT_274_NANR_BIN
	CATS_ACT_ADD			0, WEST_CSP_WE_274,  EFFECT_274_NCGR_BIN, EFFECT_274_NCLR, EFFECT_274_NCER_BIN, EFFECT_274_NANR_BIN, 0, 0, 1, W274_OAM_MAX

	SE_REPEAT_C		SEQ_SE_DP_W010,10,4

	WAIT_FLAG
	CATS_RES_FREE			0
		
	SEQEND
