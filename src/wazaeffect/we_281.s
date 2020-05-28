//==============================================================================
/**
 * @file	we_281.s
 * @brief	Ç†Ç≠Ç—			281
 * @author	goto
 * @date	2005.07.13(êÖ)
 *
 * Ç±Ç±Ç…êFÅXÇ»âê‡ìôÇèëÇ¢ÇƒÇ‡ÇÊÇ¢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_AKUBI
	
// =============================================================================
//
//
//	Å°Ç†Ç≠Ç—			281
//
//
// =============================================================================

#define KEEP_WAIT	(15)

#define Y_TOP		(160)
#define FWAIT		(1)
#define IWAIT		(5)
#define OWAIT		(15)
#define TWAIT		(IWAIT + OWAIT)
WEST_AKUBI:
	LOAD_PARTICLE_DROP	0,W_281_SPA
		
	SE_FLOW_LR			SEQ_SE_DP_W281

	FUNC_CALL		WEST_SP_WE_SSP_POKE_SCALE_UPDOWN, 8, (WE_TOOL_M1 | WE_TOOL_SSP), 100, 80, 100, Y_TOP, 100, 1, (IWAIT << 16) | OWAIT
	
	WAIT			5

	ADD_PARTICLE 	0,W_281_281_YAWN_BEAM,	EMTFUNC_FIELD_OPERATOR
	EX_DATA			OPERATOR_DEF_DATA_NUM, OPERATOR_PRI_NONE, OPERATOR_TARGET_DF, OPERATOR_POS_LSP, OPERATOR_AXIS_AT, OPERATOR_FLD_NONE, OPERATOR_CAMERA_NONE
	
	WAIT			20
	//SE_R			SEQ_SE_DP_W255
	SE_REPEAT_R		SEQ_SE_DP_W255,4,2

	ADD_PARTICLE 	0,W_281_281_YAWN_BUB,	EMTFUNC_DEFENCE_POS
		FUNC_CALL		WEST_SP_WE_SSP_POKE_SCALE_UPDOWN, 8, (WE_TOOL_E1 | WE_TOOL_SSP), 100, 80, 100, Y_TOP, 100, 1, (IWAIT << 16) | OWAIT

	WAIT			20
	//SE_R			SEQ_SE_DP_W281

	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	
	SEQEND
