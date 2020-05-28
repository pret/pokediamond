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

#define Y_TOP		(160)
#define FWAIT		(1)
#define IWAIT		(5)
#define OWAIT		(5)
#define TWAIT		(IWAIT + OWAIT)

WEST_Hataku:

	LOAD_PARTICLE_DROP	0,W_379_SPA
	
	ADD_PARTICLE 	0,W_379_379_PTRICK_HAND1, EMTFUNC_FIELD_OPERATOR
	EX_DATA			OPERATOR_DEF_DATA_NUM, OPERATOR_PRI_NONE, OPERATOR_TARGET_AT, OPERATOR_POS_EP, OPERATOR_AXIS_AT, OPERATOR_FLD_NONE, OPERATOR_CAMERA_NONE
	
	ADD_PARTICLE 	0,W_379_379_PTRICK_HAND2, EMTFUNC_FIELD_OPERATOR
	EX_DATA			OPERATOR_DEF_DATA_NUM, OPERATOR_PRI_NONE, OPERATOR_TARGET_AT, OPERATOR_POS_EP, OPERATOR_AXIS_AT, OPERATOR_FLD_NONE, OPERATOR_CAMERA_NONE
	
	ADD_PARTICLE 	0,W_379_379_PTRICK_BALL, EMTFUNC_FIELD_OPERATOR
	EX_DATA			OPERATOR_DEF_DATA_NUM, OPERATOR_PRI_NONE, OPERATOR_TARGET_AT, OPERATOR_POS_EP, OPERATOR_AXIS_AT, OPERATOR_FLD_NONE, OPERATOR_CAMERA_NONE

	LOOP_LABEL		2

		SE_L		SEQ_SE_DP_W379

		FUNC_CALL	WEST_SP_WE_SSP_POKE_SCALE_UPDOWN, 8, (WE_TOOL_M1 | WE_TOOL_SSP), 100,  80, 100, 140, 100, 1, (IWAIT << 16) | OWAIT
		WAIT		TWAIT
		FUNC_CALL	WEST_SP_WE_SSP_POKE_SCALE_UPDOWN, 8, (WE_TOOL_M1 | WE_TOOL_SSP), 100, 120, 100,  80, 100, 1, (IWAIT << 16) | OWAIT
		WAIT		TWAIT
	LOOP
		
	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	SEQEND

