//==============================================================================
/**
 * @file	we_288.s
 * @brief	Ç®ÇÒÇÀÇÒ			288
 * @author	goto
 * @date	2005.07.13(êÖ)
 *
 * Ç±Ç±Ç…êFÅXÇ»âê‡ìôÇèëÇ¢ÇƒÇ‡ÇÊÇ¢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_ONNEN
	
// =============================================================================
//
//
//	Å°Ç®ÇÒÇÀÇÒ			288
//
//
// =============================================================================
#define ONNEN_RES_NO		(0)
#define ONNEN_RES_NUM		(1)
#define ONNEN_ACT_NUM		(10)
WEST_ONNEN:
	FUNC_CALL		WEST_SP_WE_HAIKEI_PAL_FADE, 5, 0, 1, 0, 12, WE_PAL_BLACK,
	
	SE_L			SEQ_SE_DP_W060
	
	WAIT_FLAG	
	
	///<èâä˙âªèàóùÅ@ì«Ç›çûÇ›èàóù
	CATS_RES_INIT		ONNEN_RES_NO, ONNEN_ACT_NUM, ONNEN_RES_NUM, ONNEN_RES_NUM, ONNEN_RES_NUM, ONNEN_RES_NUM, 0, 0
	CATS_CAHR_RES_LOAD	ONNEN_RES_NO, EFFECT_288_NCGR_BIN
	CATS_PLTT_RES_LOAD	ONNEN_RES_NO, EFFECT_288_NCLR, 1
	CATS_CELL_RES_LOAD	ONNEN_RES_NO, EFFECT_288_NCER_BIN
	CATS_CELL_ANM_RES_LOAD	ONNEN_RES_NO, EFFECT_288_NANR_BIN
	
	///<ìÆçÏ
	SE_REPEAT_L		SEQ_SE_DP_W052,16,3
	CATS_ACT_ADD		ONNEN_RES_NO, WEST_CSP_WE_288, EFFECT_288_NCGR_BIN, EFFECT_288_NCLR, EFFECT_288_NCER_BIN, EFFECT_288_NANR_BIN, 0, 0, 0,0,
	//SE WAZA_EFF_SE3

	WAIT_FLAG

	///<îjä¸èàóù
	CATS_RES_FREE		ONNEN_RES_NO

	FUNC_CALL		WEST_SP_WE_HAIKEI_PAL_FADE, 5, 0, 1, 12, 0, WE_PAL_BLACK,
	WAIT_FLAG

	
	SEQEND
