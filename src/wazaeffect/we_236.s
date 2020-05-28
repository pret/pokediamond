//==============================================================================
/**
 * @file	we_236.s
 * @brief	Ç¬Ç´ÇÃÇ–Ç©ÇË			236
 * @author	goto
 * @date	2005.07.13(êÖ)
 *
 * Ç±Ç±Ç…êFÅXÇ»âê‡ìôÇèëÇ¢ÇƒÇ‡ÇÊÇ¢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_TUKINOHIKARI
	
// =============================================================================
//
//
//	Å°Ç¬Ç´ÇÃÇ–Ç©ÇË			236
//
//
// =============================================================================
WEST_TUKINOHIKARI:
	LOAD_PARTICLE_DROP	0,W_236_SPA
	
	WORK_SET		WEDEF_GP_INDEX_FADE_TYPE, 0
	WORK_SET		WEDEF_GP_INDEX_SPEED_X,  0
	WORK_SET		WEDEF_GP_INDEX_SPEED_Y,  1
	HAIKEI_CHG		BG_ID_236, WEDEF_HAIKEI_MODE_FADE | WEDEF_HAIKEI_SBIT_MOVE
	
	HAIKEI_CHG_WAIT
	
	SE_C			SEQ_SE_DP_W236
	
	ADD_PARTICLE 	0,W_236_236_MOON_KIRA, EMTFUNC_DEFENCE_POS
//	WAIT			10
	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	
	WORK_SET		WEDEF_GP_INDEX_FADE_TYPE, 0
	WORK_SET		WEDEF_GP_INDEX_SPEED_X,  0
	WORK_SET		WEDEF_GP_INDEX_SPEED_Y,  1
	WORK_SET		WEDEF_GP_INDEX_FADE_TYPE, 1
	HAIKEI_RECOVER	BG_ID_236, WEDEF_HAIKEI_RC_MODE_FADE | WEDEF_HAIKEI_SBIT_STOP
	
	HAIKEI_CHG_WAIT
	
	SEQEND
