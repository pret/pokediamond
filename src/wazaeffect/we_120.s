//==============================================================================
/**
 * @file	we_120.s
 * @brief	Ç∂ÇŒÇ≠			120
 * @author	goto
 * @date	2005.07.13(êÖ)
 *
 * Ç±Ç±Ç…êFÅXÇ»âê‡ìôÇèëÇ¢ÇƒÇ‡ÇÊÇ¢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_ZIBAKU
	
// =============================================================================
//
//
//	Å°Ç∂ÇŒÇ≠			120
//
//
// =============================================================================
WEST_ZIBAKU:
	LOAD_PARTICLE_DROP	0,W_120_SPA
	
	WORK_SET		WEDEF_GP_INDEX_SCREEN_R, 2
	HAIKEI_CHG		BG_ID_120, WEDEF_HAIKEI_MODE_FADE | WEDEF_HAIKEI_SBIT_NONE
	HAIKEI_CHG_WAIT
	FUNC_CALL		WEST_SP_BG_SHAKE, 5, 8, 8, 0, 20, 0
		
	SE_REPEAT_L		SEQ_SE_DP_W120,2,10

//	ADD_PARTICLE 	0,W_120_120_JIBAKU_CORE,	EMTFUNC_DEFENCE_POS
//	ADD_PARTICLE 	0,W_120_120_JIBAKU_BOMB,	EMTFUNC_DEFENCE_POS
	
	ADD_PARTICLE 	0,W_120_120_JIBAKU_CORE,	EMTFUNC_ATTACK_POS
	ADD_PARTICLE 	0,W_120_120_JIBAKU_BOMB,	EMTFUNC_ATTACK_POS
	ADD_PARTICLE 	0,W_120_120_JIBAKU_LINE,	EMTFUNC_ATTACK_POS
	
	WAIT			20
	
	SEPLAY_PAN		SEQ_SE_DP_W120, WAZA_SE_PAN_AT
	FUNC_CALL		WEST_SP_WT_SHAKE, 5, SHAKE_B_X, 0, SHAKE_B_WAIT, SHAKE_B_NUM,  WE_TOOL_OTHER | WE_TOOL_SSP


	WAIT_FLAG
	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	
	WORK_SET		WEDEF_GP_INDEX_SCREEN_R, 2
	HAIKEI_RECOVER	BG_ID_120, WEDEF_HAIKEI_RC_MODE_FADE | WEDEF_HAIKEI_SBIT_NONE
	HAIKEI_CHG_WAIT
	
	SEQEND
