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

	LOAD_PARTICLE_DROP	0,W_438_SPA

	WORK_CLEAR
	WORK_SET		WEDEF_GP_INDEX_SCREEN_R, 1
	HAIKEI_CHG		BG_ID_438, WEDEF_HAIKEI_MODE_FADE | WEDEF_HAIKEI_SBIT_NONE
	
	SE_R			SEQ_SE_DP_W104
	SE_WAITPLAY_R	SEQ_SE_DP_MUCHI,10

	ADD_PARTICLE 	0,W_438_438_POW_LINE1,		EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_438_438_POW_LINE2,		EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_438_438_POW_HIT,		EMTFUNC_DEFENCE_POS
	
	WAIT			10	
	FUNC_CALL		WEST_SP_WT_SHAKE, 5, SHAKE_S_X, 0, SHAKE_S_WAIT, SHAKE_S_NUM,  WE_TOOL_E1 | WE_TOOL_SSP,	
	SE_R			SEQ_SE_DP_186
		
	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	
	WORK_CLEAR
	WORK_SET		WEDEF_GP_INDEX_SCREEN_R, 1
	HAIKEI_RECOVER	BG_ID_438, WEDEF_HAIKEI_RC_MODE_FADE | WEDEF_HAIKEI_SBIT_NONE
	HAIKEI_CHG_WAIT	
	
	SEQEND

