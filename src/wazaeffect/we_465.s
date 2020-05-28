//==============================================================================
/**
 * @file	we_001.s
 * @brief	ÇÕÇΩÇ≠
 * @author	goto
 * @date	2005.07.13(êÖ)
 *
 * Ç±Ç±Ç…êFÅXÇ»âê‡ìôÇèëÇ¢ÇƒÇ‡ÇÊÇ¢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_Hataku
	
// =============================================================================
//
//
//	Å°ÇÕÇΩÇ≠
//
//
// =============================================================================
WEST_Hataku:

	LOAD_PARTICLE_DROP	0, W_465_SPA

	SE_L			SEQ_SE_DP_SHUSHU		
	
	ADD_PARTICLE 	0, W_465_465_SEED_BALL1,	 EMTFUNC_ATTACK_POS
	ADD_PARTICLE 	0, W_465_465_SEED_BOMB,		 EMTFUNC_ATTACK_POS
	ADD_PARTICLE 	0, W_465_465_SEED_BALL2,	 EMTFUNC_ATTACK_POS
	
	FUNC_CALL		WEST_SP_WE_HAIKEI_PAL_FADE, 5, 0, 0, 0, 13, WE_PAL_WHITE,
	WAIT_FLAG

	
	WAIT			40
	SE_C			SEQ_SE_DP_W465
	
	FUNC_CALL		WEST_SP_WE_HAIKEI_PAL_FADE, 5, 0, 0, 13, 0, WE_PAL_WHITE,
			
//	WORK_CLEAR
//	WORK_SET		WEDEF_GP_INDEX_SCREEN_R, 1
//	HAIKEI_CHG		BG_ID_465, WEDEF_HAIKEI_MODE_FADE | WEDEF_HAIKEI_SBIT_NONE
	
	FUNC_CALL		WEST_SP_BG_SHAKE, 5, 4, 4, 0, 10, 0

	
	FUNC_CALL		WEST_SP_WT_SHAKE, 5, SHAKE_M_X, 0, SHAKE_M_WAIT, SHAKE_M_NUM*3,  WE_TOOL_E1 | WE_TOOL_SSP,
	
	WAIT_FLAG
	
	WAIT_PARTICLE
	EXIT_PARTICLE	0,

//	WORK_CLEAR
//	WORK_SET		WEDEF_GP_INDEX_SCREEN_R, 1
//	HAIKEI_RECOVER	BG_ID_465, WEDEF_HAIKEI_RC_MODE_FADE | WEDEF_HAIKEI_SBIT_NONE
//	HAIKEI_CHG_WAIT
	
	SEQEND

