//==============================================================================
/**
 * @file	wesub_006.s
 * @brief	アイテム袋　ぽいっと
 * @author	goto
 * @date	2005.07.13(水)
 *
 * ここに色々な解説等を書いてもよい
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_ItemPouch
	
// =============================================================================
//
//
//	■アイテム袋　ぽいっと
//
//
// =============================================================================
#define ITEM_RES_NO			(0)
#define ITEM_RES_NUM		(1)
#define ITEM_ACT_NUM		(1)

WEST_ItemPouch:

	CATS_RES_INIT	ITEM_RES_NO, ITEM_ACT_NUM, ITEM_RES_NUM, ITEM_RES_NUM, ITEM_RES_NUM, ITEM_RES_NUM, 0, 0
	
	CATS_CAHR_RES_LOAD		ITEM_RES_NO, ITEM_OAM_NCGR_BIN
	CATS_PLTT_RES_LOAD		ITEM_RES_NO, ITEM_OAM_NCLR, 1
	CATS_CELL_RES_LOAD		ITEM_RES_NO, ITEM_OAM_NCER_BIN
	CATS_CELL_ANM_RES_LOAD	ITEM_RES_NO, ITEM_OAM_NANR_BIN
	
	SE_L				SEQ_SE_DP_W104

	CATS_ACT_ADD	ITEM_RES_NO, WEST_CSP_WE_ITEM, ITEM_OAM_NCGR_BIN, ITEM_OAM_NCLR, ITEM_OAM_NCER_BIN, ITEM_OAM_NANR_BIN, 0, 0, 0

	WAIT_FLAG

	SEQEND
