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
#define WE_457_MOVE_X	(14)
#define WE_457_MOVE_Y	(8)
WEST_Hataku:
	
	LOAD_PARTICLE_DROP	0,W_457_SPA


	WORK_CLEAR
	WORK_SET		WEDEF_GP_INDEX_SCREEN_R, 1
	HAIKEI_CHG		BG_ID_457, WEDEF_HAIKEI_MODE_FADE | WEDEF_HAIKEI_SBIT_NONE
	
	
	SE_R			SEQ_SE_DP_143

	FUNC_CALL		WEST_SP_WE_T10,	4, 2, +WE_457_MOVE_X, -WE_457_MOVE_Y, WE_TOOL_M1 | WE_TOOL_SSP
	WAIT_FLAG
	FUNC_CALL		WEST_SP_BG_SHAKE, 5, 4, 4, 0, 10, 0
	
	ADD_PARTICLE		0, W_457_457_STONE_BURN,	EMTFUNC_DEFENCE_POS
	ADD_PARTICLE		0, W_457_457_KEMURI_BURN,	EMTFUNC_DEFENCE_POS
	ADD_PARTICLE		0, W_457_457_HIT_MARK,		EMTFUNC_DEFENCE_POS
	ADD_PARTICLE		0, W_457_457_RING_BIG,		EMTFUNC_DEFENCE_POS
	ADD_PARTICLE		0, W_457_457_STAR_BURN,		EMTFUNC_DEFENCE_POS
	
	SE_R			SEQ_SE_DP_186
	FUNC_CALL		WEST_SP_WT_SHAKE, 5, SHAKE_M_X, 0, SHAKE_M_WAIT, SHAKE_M_NUM,  WE_TOOL_E1 | WE_TOOL_SSP,
	FUNC_CALL		WEST_SP_WE_T10,	4, 2, -WE_457_MOVE_X, +WE_457_MOVE_Y, WE_TOOL_M1 | WE_TOOL_SSP
	WAIT_FLAG
	
	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	
	WORK_CLEAR
	WORK_SET		WEDEF_GP_INDEX_SCREEN_R, 1
	HAIKEI_RECOVER	BG_ID_457, WEDEF_HAIKEI_RC_MODE_FADE | WEDEF_HAIKEI_SBIT_NONE
	HAIKEI_CHG_WAIT
	
	SEQEND

