//==============================================================================
/**
 * @file	we_294.s
 * @brief	ÇŸÇΩÇÈÇ—			294
 * @author	goto
 * @date	2005.07.13(êÖ)
 *
 * Ç±Ç±Ç…êFÅXÇ»âê‡ìôÇèëÇ¢ÇƒÇ‡ÇÊÇ¢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_HOTARUBI
	
// =============================================================================
//
//
//	Å°ÇŸÇΩÇÈÇ—			294
//
//
// =============================================================================
WEST_HOTARUBI:
	LOAD_PARTICLE_DROP	0,W_294_SPA
	
	FUNC_CALL		WEST_SP_WE_HAIKEI_PAL_FADE, 5, 0, 1, 0, 12, WE_PAL_BLACK,
	WAIT_FLAG
		
	ADD_PARTICLE 	0,W_294_294_LIGHT1, EMTFUNC_FIELD_OPERATOR
	EX_DATA			OPERATOR_DEF_DATA_NUM, OPERATOR_PRI_NONE, OPERATOR_TARGET_AT, OPERATOR_POS_EP_OFS, OPERATOR_AXIS_NONE, OPERATOR_FLD_NONE, OPERATOR_CAMERA_NONE
	EX_DATA			4, OPERATOR_EX_REVERCE_OFF, 0, PT_LCD_PTP_CHG(-8), 0

	SE_REPEAT_L		SEQ_SE_DP_W234,24,3

	WAIT_PARTICLE
	EXIT_PARTICLE	0,
		
	FUNC_CALL		WEST_SP_WE_HAIKEI_PAL_FADE, 5, 0, 1, 12, 0, WE_PAL_BLACK,
	WAIT_FLAG	
	
	SEQEND
