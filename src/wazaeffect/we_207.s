//==============================================================================
/**
 * @file	we_207.s
 * @brief	Ç¢ÇŒÇÈ			207
 * @author	goto
 * @date	2005.07.13(êÖ)
 *
 * Ç±Ç±Ç…êFÅXÇ»âê‡ìôÇèëÇ¢ÇƒÇ‡ÇÊÇ¢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_IBARU
	
// =============================================================================
//
//
//	Å°Ç¢ÇŒÇÈ			207
//
//
// =============================================================================
#define IBARU_RES_NO			(0)
#define IBARU_RES_NUM		(1)
#define IBARU_ACT_NUM		(1)
WEST_IBARU:
	
	///<èâä˙âªèàóùÅ@ì«Ç›çûÇ›èàóù
	CATS_RES_INIT		IBARU_RES_NO, IBARU_ACT_NUM, IBARU_RES_NUM, IBARU_RES_NUM, IBARU_RES_NUM, IBARU_RES_NUM, 0, 0
	CATS_CAHR_RES_LOAD	IBARU_RES_NO, EFFECT_207_NCGR_BIN
	CATS_PLTT_RES_LOAD	IBARU_RES_NO, EFFECT_207_NCLR, 1
	CATS_CELL_RES_LOAD	IBARU_RES_NO, EFFECT_207_NCER_BIN
	CATS_CELL_ANM_RES_LOAD	IBARU_RES_NO, EFFECT_207_NANR_BIN
	
	///<ìÆçÏ
	FUNC_CALL		WEST_SP_WE_207_MAIN, 0,0,0,0,0,0,0,0,0

	//SE_L			SEQ_SE_DP_W207
	SE_L			SEQ_SE_DP_W207D
	WAIT			30
	WAIT_FLAG
	
	CATS_ACT_ADD		IBARU_RES_NO, WEST_CSP_WE_207_SUB, EFFECT_207_NCGR_BIN, EFFECT_207_NCLR, EFFECT_207_NCER_BIN, EFFECT_207_NANR_BIN, 0, 0, 0,0,

	//SE_R			SEQ_SE_DP_BASI
	SE_R			SEQ_SE_DP_W207B
	WAIT	8
	//SE_R			SEQ_SE_DP_BASI
	SE_R			SEQ_SE_DP_W207B

	WAIT_FLAG

	///<îjä¸èàóù
	CATS_RES_FREE		IBARU_RES_NO
	
	SEQEND
