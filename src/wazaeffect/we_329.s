//==============================================================================
/**
 * @file	we_329.s
 * @brief	Ç∫Ç¡ÇΩÇ¢ÇÍÇ¢Ç«			329
 * @author	goto
 * @date	2005.07.13(êÖ)
 *
 * Ç±Ç±Ç…êFÅXÇ»âê‡ìôÇèëÇ¢ÇƒÇ‡ÇÊÇ¢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_ZETTAIREIDO
	
// =============================================================================
//
//
//	Å°Ç∫Ç¡ÇΩÇ¢ÇÍÇ¢Ç«			329
//
//
// =============================================================================
WEST_ZETTAIREIDO:

	LOAD_PARTICLE_DROP	0,W_329_SPA
	
	FUNC_CALL		WEST_SP_WE_HAIKEI_PAL_FADE, 5, 0, 1, 0, 12, WE_PAL_BLACK
	WAIT_FLAG
	
	SE_REPEAT_C		SEQ_SE_DP_W258,4,12

	ADD_PARTICLE 	0,W_329_329_ICE_SMOKE, EMTFUNC_DEFENCE_POS

	ADD_PARTICLE 	0,W_329_329_ICE_BLOCK, EMTFUNC_FIELD_OPERATOR
	EX_DATA			OPERATOR_DEF_DATA_NUM, OPERATOR_PRI_NONE, OPERATOR_TARGET_DF, OPERATOR_POS_NONE, OPERATOR_AXIS_NONE, OPERATOR_FLD_NONE, OPERATOR_CAMERA_NONE

	ADD_PARTICLE 	0,W_329_329_KIRAKIRA, EMTFUNC_DEFENCE_POS
	
	WAIT			15
	FUNC_CALL		WEST_SP_WE_SSP_POKE_PAL_FADE, 6,  WE_TOOL_E1, 0, 1, WE_PAL_WHITE, WEDEF_FADE_PARAM,10
	FUNC_CALL		WEST_SP_WT_SHAKE, 5, SHAKE_S_X, 0, SHAKE_S_WAIT, SHAKE_S_NUM,  WE_TOOL_E1 | WE_TOOL_SSP,
	
	WAIT_PARTICLE
	EXIT_PARTICLE	0,

	FUNC_CALL		WEST_SP_WE_HAIKEI_PAL_FADE, 5, 0, 1, 12, 0, WE_PAL_BLACK
	WAIT_FLAG
	
	SEQEND
