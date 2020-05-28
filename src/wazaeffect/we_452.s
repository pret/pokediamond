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

	LOAD_PARTICLE_DROP	0,W_452_SPA
/*
	WORK_CLEAR
	WORK_SET		WEDEF_GP_INDEX_SCREEN_R, 1
	HAIKEI_CHG		BG_ID_438, WEDEF_HAIKEI_MODE_FADE | WEDEF_HAIKEI_SBIT_NONE
*/	
	SE_R			SEQ_SE_DP_W452
	
	ADD_PARTICLE		0, W_452_452_WOOD_BURN, EMTFUNC_DEFENCE_POS
	ADD_PARTICLE		0, W_452_452_STAR_BURN, EMTFUNC_DEFENCE_POS
	ADD_PARTICLE		0, W_452_452_HIT_MARK,  EMTFUNC_DEFENCE_POS
	ADD_PARTICLE		0, W_452_452_RING_BIG,	EMTFUNC_DEFENCE_POS
	ADD_PARTICLE		0, W_452_452_LEAF_BURN,	EMTFUNC_DEFENCE_POS
	
	FUNC_CALL		WEST_SP_WT_SHAKE, 5, SHAKE_M_X, 0, SHAKE_M_WAIT, SHAKE_M_NUM*3,  WE_TOOL_E1 | WE_TOOL_SSP,	
	FUNC_CALL		WEST_SP_BG_SHAKE, 5, 0, 5, 1, 5, 0
	
	WAIT_PARTICLE
	EXIT_PARTICLE	0,

/*
	WORK_CLEAR
	WORK_SET		WEDEF_GP_INDEX_SCREEN_R, 1
	HAIKEI_RECOVER	BG_ID_438, WEDEF_HAIKEI_RC_MODE_FADE | WEDEF_HAIKEI_SBIT_NONE
	HAIKEI_CHG_WAIT
*/		
	SEQEND

