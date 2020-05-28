//==============================================================================
/**
 * @file	we_286.s
 * @brief	Ç”Ç§Ç¢ÇÒ			286
 * @author	goto
 * @date	2005.07.13(êÖ)
 *
 * Ç±Ç±Ç…êFÅXÇ»âê‡ìôÇèëÇ¢ÇƒÇ‡ÇÊÇ¢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_HUUIN
	
// =============================================================================
//
//
//	Å°Ç”Ç§Ç¢ÇÒ			286
//
//
// =============================================================================
#define HUUIN_RES_NO			(0)
#define HUUIN_RES_NUM		(1)
#define HUUIN_ACT_NUM		(3)
WEST_HUUIN:
#if 0
	///<èâä˙âªèàóùÅ@ì«Ç›çûÇ›èàóù
	CATS_RES_INIT		HUUIN_RES_NO, HUUIN_ACT_NUM, HUUIN_RES_NUM, HUUIN_RES_NUM, HUUIN_RES_NUM, HUUIN_RES_NUM, 0, 0
	CATS_CAHR_RES_LOAD	HUUIN_RES_NO, EFFECT_286_NCGR_BIN
	CATS_PLTT_RES_LOAD	HUUIN_RES_NO, EFFECT_286_NCLR, 1
	CATS_CELL_RES_LOAD	HUUIN_RES_NO, EFFECT_286_NCER_BIN
	CATS_CELL_ANM_RES_LOAD	HUUIN_RES_NO, EFFECT_286_NANR_BIN

	///<ìÆçÏ
	CATS_ACT_ADD		HUUIN_RES_NO, WEST_CSP_WE_286, EFFECT_286_NCGR_BIN, EFFECT_286_NCLR, EFFECT_286_NCER_BIN, EFFECT_286_NANR_BIN, 0, 0, 0,0,
#endif

	LOAD_PARTICLE_DROP	0,W_286_SPA

	SE_R			SEQ_SE_DP_050

	ADD_PARTICLE 	0,W_286_286_FONT_FU01, EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_286_286_FONT_FU02, EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_286_286_BATU01, EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_286_286_BATU02, EMTFUNC_DEFENCE_POS
	
	LOOP_LABEL	1
		WAIT 12
		SE_R			SEQ_SE_DP_W030
	LOOP

	WAIT_PARTICLE
	EXIT_PARTICLE	0,

	///<îjä¸èàóù
//	CATS_RES_FREE		HUUIN_RES_NO
	
	SEQEND
