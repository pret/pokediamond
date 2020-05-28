//==============================================================================
/**
 * @file	we_184.s
 * @brief	Ç±ÇÌÇ¢Ç©Ç®			184
 * @author	goto
 * @date	2005.07.13(êÖ)
 *
 * Ç±Ç±Ç…êFÅXÇ»âê‡ìôÇèëÇ¢ÇƒÇ‡ÇÊÇ¢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_KOWAIKAO
	
// =============================================================================
//
//
//	Å°Ç±ÇÌÇ¢Ç©Ç®			184
//
//
// =============================================================================
#define FACE_RES_NO			(0)
#define FACE_RES_NUM		(1)
#define FACE_ACT_NUM		(1)
WEST_KOWAIKAO:

	FUNC_CALL		WEST_SP_WE_HAIKEI_PAL_FADE, 5, 0, 1, 0, 12, WE_PAL_BLACK,
	SE_C			SEQ_SE_DP_W060
	WAIT_FLAG

	///<èâä˙âªèàóùÅ@ì«Ç›çûÇ›èàóù
	CATS_RES_INIT		FACE_RES_NO, FACE_ACT_NUM, FACE_RES_NUM, FACE_RES_NUM, FACE_RES_NUM, FACE_RES_NUM, 0, 0
	CATS_CAHR_RES_LOAD	FACE_RES_NO, EFFECT_184_NCGR_BIN
	CATS_PLTT_RES_LOAD	FACE_RES_NO, EFFECT_184_NCLR, 1
	CATS_CELL_RES_LOAD	FACE_RES_NO, EFFECT_184_NCER_BIN
	CATS_CELL_ANM_RES_LOAD	FACE_RES_NO, EFFECT_184_NANR_BIN
	
	///<ìÆçÏ
	CATS_ACT_ADD		FACE_RES_NO, WEST_CSP_WE_184, EFFECT_184_NCGR_BIN, EFFECT_184_NCLR, EFFECT_184_NCER_BIN, EFFECT_184_NANR_BIN, 0, 0, 0,0,

	WAIT 8
	SE_C			SEQ_SE_DP_W043D
	
	WAIT_FLAG

	///<îjä¸èàóù
	CATS_RES_FREE		FACE_RES_NO

	FUNC_CALL		WEST_SP_WE_HAIKEI_PAL_FADE, 5, 0, 1, 12, 0, WE_PAL_BLACK,
	WAIT_FLAG
	
	SEQEND
