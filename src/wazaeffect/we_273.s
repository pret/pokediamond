//==============================================================================
/**
 * @file	we_273.s
 * @brief	ÇÀÇ™Ç¢Ç≤Ç∆			273
 * @author	goto
 * @date	2005.07.13(êÖ)
 *
 * Ç±Ç±Ç…êFÅXÇ»âê‡ìôÇèëÇ¢ÇƒÇ‡ÇÊÇ¢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_NEGAIGOTO
	
// =============================================================================
//
//
//	Å°ÇÀÇ™Ç¢Ç≤Ç∆			273
//
//
// =============================================================================
WEST_NEGAIGOTO:
	
	LOAD_PARTICLE_DROP	0,W_273_SPA

	WORK_SET		WEDEF_GP_INDEX_FADE_TYPE, 0
	WORK_SET		WEDEF_GP_INDEX_SPEED_X,  0
	WORK_SET		WEDEF_GP_INDEX_SPEED_Y,  1
	HAIKEI_CHG		BG_ID_322, WEDEF_HAIKEI_MODE_FADE | WEDEF_HAIKEI_SBIT_MOVE
	HAIKEI_CHG_WAIT
	
	SE_FLOW_LR		SEQ_SE_DP_W115

	ADD_PARTICLE 	0,W_273_273_SHOOTING_STAR1, EMTFUNC_DUMMY
	ADD_PARTICLE 	0,W_273_273_SHOOTING_STAR2, EMTFUNC_DUMMY
	
	WAIT			30
	
	ADD_PARTICLE 	0,W_273_273_STAR_BURN1, EMTFUNC_ATTACK_POS
	ADD_PARTICLE 	0,W_273_273_STAR_BURN2, EMTFUNC_ATTACK_POS

	SE_REPEAT_R		SEQ_SE_DP_W215,16,3
	
	WAIT			20
	FUNC_CALL		WEST_SP_WE_SSP_POKE_PAL_FADE, 6,  WE_TOOL_M1, 0, 1, WE_PAL_WHITE, 10,0

	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	
	WORK_CLEAR
	WORK_SET		WEDEF_GP_INDEX_FADE_TYPE, 0
	WORK_SET		WEDEF_GP_INDEX_SPEED_X,  0
	WORK_SET		WEDEF_GP_INDEX_SPEED_Y,  1
	HAIKEI_RECOVER	BG_ID_322, WEDEF_HAIKEI_RC_MODE_FADE | WEDEF_HAIKEI_SBIT_STOP
	HAIKEI_CHG_WAIT
	SEQEND
