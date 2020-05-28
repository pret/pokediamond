//==============================================================================
/**
 * @file	we_266.s
 * @brief	Ç±ÇÃÇ‰Ç—Ç∆Ç‹ÇÍ			266
 * @author	goto
 * @date	2005.07.13(êÖ)
 *
 * Ç±Ç±Ç…êFÅXÇ»âê‡ìôÇèëÇ¢ÇƒÇ‡ÇÊÇ¢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_KONOYUBITOMARE
	
// =============================================================================
//
//
//	Å°Ç±ÇÃÇ‰Ç—Ç∆Ç‹ÇÍ			266
//
//
// =============================================================================
#define W266_RES_NO			(0)
#define W266_RES_NUM		(2)
#define W266_ACT_NUM		(1)

WEST_KONOYUBITOMARE:
	
		
	// --- oam
	CATS_RES_INIT			W266_RES_NO, W266_ACT_NUM, W266_RES_NUM, W266_RES_NUM, W266_RES_NUM, W266_RES_NUM, 0, 0

	CATS_CAHR_RES_LOAD		W266_RES_NO, EFFECT_266_NCGR_BIN
	CATS_PLTT_RES_LOAD		W266_RES_NO, EFFECT_266_NCLR, 1
	CATS_CELL_RES_LOAD		W266_RES_NO, EFFECT_266_NCER_BIN
	CATS_CELL_ANM_RES_LOAD	W266_RES_NO, EFFECT_266_NANR_BIN
	
	//SE_WAITPLAY_R		SEQ_SE_DP_W039,1
	//SE_WAITPLAY_R		SEQ_SE_DP_W213,10
	SE_WAITPLAY_R		SEQ_SE_DP_W213,2
	
	CATS_ACT_ADD		W266_RES_NO, WEST_CSP_WE_266, EFFECT_266_NCGR_BIN, EFFECT_266_NCLR, EFFECT_266_NCER_BIN, EFFECT_266_NANR_BIN, 0, 0, 3, 0, +24, 0
	// ----------------------------------

	WAIT				30
	SE_WAITPLAY_R		SEQ_SE_DP_W039,15
	//SE_WAITPLAY_R		SEQ_SE_DP_W039,25
	SE_WAITPLAY_R		SEQ_SE_DP_W039,32

	WAIT_FLAG

//	WAIT_PARTICLE
//	EXIT_PARTICLE	0,

	CATS_RES_FREE		W266_RES_NO
	SEQEND
	
	SEQEND
