//==============================================================================
/**
 * @file	we_259.s
 * @brief	Ç¢ÇøÇ·Ç‡ÇÒ			259
 * @author	goto
 * @date	2005.07.13(êÖ)
 *
 * Ç±Ç±Ç…êFÅXÇ»âê‡ìôÇèëÇ¢ÇƒÇ‡ÇÊÇ¢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_ITYAMON
	
// =============================================================================
//
//
//	Å°Ç¢ÇøÇ·Ç‡ÇÒ			259
//
//
// =============================================================================
#define ITYAMON_RES_NO		(0)
#define ITYAMON_RES_NUM		(2)
#define ITYAMON_ACT_NUM		(7)
WEST_ITYAMON:
	
	///<èâä˙âªèàóùÅ@ì«Ç›çûÇ›èàóù
	CATS_RES_INIT		ITYAMON_RES_NO, ITYAMON_ACT_NUM, ITYAMON_RES_NUM, ITYAMON_RES_NUM, ITYAMON_RES_NUM, ITYAMON_RES_NUM, 0, 0

	CATS_CAHR_RES_LOAD	ITYAMON_RES_NO, EFFECT_259_NCGR_BIN
	CATS_PLTT_RES_LOAD	ITYAMON_RES_NO, EFFECT_259_NCLR, 1
	CATS_CELL_RES_LOAD	ITYAMON_RES_NO, EFFECT_259_NCER_BIN
	CATS_CELL_ANM_RES_LOAD	ITYAMON_RES_NO, EFFECT_259_NANR_BIN
	
	///<ìÆçÏ
	CATS_ACT_ADD		ITYAMON_RES_NO, WEST_CSP_WE_259, EFFECT_259_NCGR_BIN, EFFECT_259_NCLR, EFFECT_259_NCER_BIN, EFFECT_259_NANR_BIN, 0, 0, 0,0,

	LOOP_LABEL	2
		SE_L			SEQ_SE_DP_W029
		WAIT 16
	LOOP
	LOOP_LABEL	2
		WAIT 4
		SE_L			SEQ_SE_DP_W029
		WAIT 4
	LOOP
	LOOP_LABEL	2
		WAIT 4
		SE_L			SEQ_SE_DP_W029
	LOOP
	WAIT_FLAG

	CATS_CAHR_RES_LOAD	ITYAMON_RES_NO, EFFECT_207_NCGR_BIN
	CATS_PLTT_RES_LOAD	ITYAMON_RES_NO, EFFECT_207_NCLR, 1
	CATS_CELL_RES_LOAD	ITYAMON_RES_NO, EFFECT_207_NCER_BIN
	CATS_CELL_ANM_RES_LOAD	ITYAMON_RES_NO, EFFECT_207_NANR_BIN
	
	CATS_ACT_ADD		ITYAMON_RES_NO, WEST_CSP_WE_207_SUB, EFFECT_207_NCGR_BIN, EFFECT_207_NCLR, EFFECT_207_NCER_BIN, EFFECT_207_NANR_BIN, 0, 0, 0,0,

	WAIT	4
	//SE_REPEAT_R		SEQ_SE_DP_050,10,2
	SE_REPEAT_R			SEQ_SE_DP_W207B,10,2
	WAIT	10
	WAIT_FLAG

	///<îjä¸èàóù
	CATS_RES_FREE		ITYAMON_RES_NO
	
	SEQEND
