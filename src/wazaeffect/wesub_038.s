//==============================================================================
/**
 * @file	we_250.s
 * @brief	Ç§Ç∏ÇµÇ®			250
 * @author	goto
 * @date	2005.07.13(êÖ)
 *
 * Ç±Ç±Ç…êFÅXÇ»âê‡ìôÇèëÇ¢ÇƒÇ‡ÇÊÇ¢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_UZUSIO
	
// =============================================================================
//
//
//	Å°Ç§Ç∏ÇµÇ®			250
//
//
// =============================================================================
WEST_UZUSIO:
	LOAD_PARTICLE_DROP	0,W_250_SPA
	
	WORK_CLEAR
	WORK_SET		WEDEF_GP_INDEX_SCREEN_R, 1
	HAIKEI_CHG		BG_ID_352, WEDEF_HAIKEI_MODE_FADE | WEDEF_HAIKEI_SBIT_MOVE
	
	HAIKEI_HALF_WAIT
	
	FUNC_CALL			WEST_SP_LASTER,		1,		100
	
	HAIKEI_CHG_WAIT
	
	ADD_PARTICLE 	0,W_250_250_WATERBUB1, EMTFUNC_ATTACK_POS
	ADD_PARTICLE 	0,W_250_250_WATERBUB2, EMTFUNC_ATTACK_POS
	ADD_PARTICLE 	0,W_250_250_WATERBUB3, EMTFUNC_ATTACK_POS
	ADD_PARTICLE 	0,W_250_250_WATERBUB4, EMTFUNC_ATTACK_POS

	SE_L			SEQ_SE_DP_W250
	
	WAIT			5
	FUNC_CALL		WEST_SP_WT_SHAKE, 5, SHAKE_M_X, 0, SHAKE_M_WAIT, SHAKE_M_NUM*5,  WE_TOOL_M1 | WE_TOOL_SSP,

	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	
	WORK_CLEAR
	WORK_SET		WEDEF_GP_INDEX_SCREEN_R, 1
	HAIKEI_RECOVER	BG_ID_352, WEDEF_HAIKEI_RC_MODE_FADE | WEDEF_HAIKEI_SBIT_STOP
	
	WAIT_FLAG
	
	HAIKEI_CHG_WAIT
	
	SEQEND
