//==============================================================================
/**
 * @file	we_212.s
 * @brief	Ç≠ÇÎÇ¢Ç‹Ç»Ç¥Çµ			212
 * @author	goto
 * @date	2005.07.13(êÖ)
 *
 * Ç±Ç±Ç…êFÅXÇ»âê‡ìôÇèëÇ¢ÇƒÇ‡ÇÊÇ¢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_KUROIMANAZASI
	
// =============================================================================
//
//
//	Å°Ç≠ÇÎÇ¢Ç‹Ç»Ç¥Çµ			212
//
//
// =============================================================================
#define KUROIMANAZASI_RES_NO			(0)
#define KUROIMANAZASI_RES_NUM		(1)
#define KUROIMANAZASI_ACT_NUM		(1)
WEST_KUROIMANAZASI:

	FUNC_CALL		WEST_SP_WE_HAIKEI_PAL_FADE, 5, 0, 1, 0, 12, WE_PAL_POISON,
	WAIT_FLAG
	
	///<èâä˙âªèàóùÅ@ì«Ç›çûÇ›èàóù
	CATS_RES_INIT		KUROIMANAZASI_RES_NO, KUROIMANAZASI_ACT_NUM, KUROIMANAZASI_RES_NUM, KUROIMANAZASI_RES_NUM, KUROIMANAZASI_RES_NUM, KUROIMANAZASI_RES_NUM, 0, 0
	CATS_CAHR_RES_LOAD	KUROIMANAZASI_RES_NO, EFFECT_212_NCGR_BIN
	CATS_PLTT_RES_LOAD	KUROIMANAZASI_RES_NO, EFFECT_212_NCLR, 1
	CATS_CELL_RES_LOAD	KUROIMANAZASI_RES_NO, EFFECT_212_NCER_BIN
	CATS_CELL_ANM_RES_LOAD	KUROIMANAZASI_RES_NO, EFFECT_212_NANR_BIN
	
	///<ìÆçÏ
	CATS_ACT_ADD		KUROIMANAZASI_RES_NO, WEST_CSP_WE_212, EFFECT_212_NCGR_BIN, EFFECT_212_NCLR, EFFECT_212_NCER_BIN, EFFECT_212_NANR_BIN, 0, 0, 0,0,

	LOOP_LABEL	8
		SE_R			SEQ_SE_DP_W060
		WAIT 6
	LOOP

	WAIT 6
	SE_R				SEQ_SE_DP_W109

	
	WAIT_FLAG

	///<îjä¸èàóù
	CATS_RES_FREE		KUROIMANAZASI_RES_NO

	FUNC_CALL		WEST_SP_WE_HAIKEI_PAL_FADE, 5, 0, 1, 12, 0, WE_PAL_POISON,
	WAIT_FLAG
	
	SEQEND
