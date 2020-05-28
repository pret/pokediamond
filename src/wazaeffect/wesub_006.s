//==============================================================================
/**
 * @file	wesub_006.s
 * @brief	Ç±ÇÒÇÁÇÒ
 * @author	goto
 * @date	2005.07.13(êÖ)
 *
 * Ç±Ç±Ç…êFÅXÇ»âê‡ìôÇèëÇ¢ÇƒÇ‡ÇÊÇ¢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_StatusKonran
	
// =============================================================================
//
//
//	Å°Ç±ÇÒÇÁÇÒ
//
//
// =============================================================================
WEST_StatusKonran:

	LOAD_PARTICLE_DROP	0, SPA_STATUS_EFF
	
	SE_REPEAT_L		SEQ_SE_DP_W146,4,4

	ADD_PARTICLE 	0, STATUS_EFF_TURN_HIYOKO, EMTFUNC_FIELD_OPERATOR
	EX_DATA			OPERATOR_DEF_DATA_NUM, OPERATOR_PRI_NONE, OPERATOR_TARGET_AT, OPERATOR_POS_EP_OFS, OPERATOR_AXIS_NONE, OPERATOR_FLD_NONE, OPERATOR_CAMERA_NONE
	EX_DATA			4, OPERATOR_EX_REVERCE_OFF, 0, PT_LCD_PTP_CHG(+48), 0

	WAIT_PARTICLE
	EXIT_PARTICLE	0,

	SEQEND
