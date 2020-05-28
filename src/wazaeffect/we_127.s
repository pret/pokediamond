//==============================================================================
/**
 * @file	we_127.s
 * @brief	ÇΩÇ´ÇÃÇ⁄ÇË			127
 * @author	goto
 * @date	2005.07.13(êÖ)
 *
 * Ç±Ç±Ç…êFÅXÇ»âê‡ìôÇèëÇ¢ÇƒÇ‡ÇÊÇ¢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_TAKINOBORI
	
// =============================================================================
//
//
//	Å°ÇΩÇ´ÇÃÇ⁄ÇË			127
//
//
// =============================================================================
WEST_TAKINOBORI:
	LOAD_PARTICLE_DROP	0,W_127_SPA

	WORK_CLEAR
	WORK_SET		WEDEF_GP_INDEX_FADE_TYPE,  1
	WORK_SET		WEDEF_GP_INDEX_SPEED_X,  0
	WORK_SET		WEDEF_GP_INDEX_SPEED_Y,  -20
	HAIKEI_CHG		BG_ID_127, WEDEF_HAIKEI_MODE_FADE | WEDEF_HAIKEI_SBIT_MOVE
	HAIKEI_CHG_WAIT

//	FUNC_CALL		WEST_SP_WE_HAIKEI_PAL_FADE, 5, 0, 1, 0, 12, WE_PAL_BLUE,
//	WAIT_FLAG
			
	SE_REPEAT_L		SEQ_SE_DP_W152,2,4

	ADD_PARTICLE 	0,W_127_127_TAKI_BUBBL,		EMTFUNC_ATTACK_POS
	FUNC_CALL		WEST_SP_WT_SHAKE, 5, 1, 0, 1, 4,  WE_TOOL_M1 | WE_TOOL_SSP,
	WAIT_FLAG

	FUNC_CALL		WEST_SP_WE_T05, 3, 3, +WE_MOVE_X_VAL_DEF, WE_TOOL_M1 | WE_TOOL_SSP
	WAIT_FLAG
	FUNC_CALL		WEST_SP_WE_T05, 3, 3, -WE_MOVE_X_VAL_DEF, WE_TOOL_M1 | WE_TOOL_SSP

	ADD_PARTICLE 	0,W_127_127_TAKI_HIT,	EMTFUNC_DEFENCE_POS
//	ADD_PARTICLE 	0,W_127_127_TAKI_BOMB,		EMTFUNC_DEFENCE_POS
	
	WAIT			35
	FUNC_CALL		WEST_SP_WT_SHAKE, 5, 1, 0, 1, 6,  WE_TOOL_E1 | WE_TOOL_SSP,

	SE_R			SEQ_SE_DP_W127

	WAIT_PARTICLE
	EXIT_PARTICLE	0,

	WORK_CLEAR
	WORK_SET		WEDEF_GP_INDEX_FADE_TYPE,  1
	WORK_SET		WEDEF_GP_INDEX_SPEED_X,  0
	WORK_SET		WEDEF_GP_INDEX_SPEED_Y,  -20
	HAIKEI_RECOVER	BG_ID_127, WEDEF_HAIKEI_RC_MODE_FADE | WEDEF_HAIKEI_SBIT_STOP
	HAIKEI_CHG_WAIT

//	FUNC_CALL		WEST_SP_WE_HAIKEI_PAL_FADE, 5, 0, 1, 12, 0, WE_PAL_BLUE,
//	WAIT_FLAG
		
	SEQEND
