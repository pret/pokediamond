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
	
	LOAD_PARTICLE_DROP	0,W_378_SPA
	
	ADD_PARTICLE 	0,W_378_378_SIBORI_KAITEN, EMTFUNC_FIELD_OPERATOR
	EX_DATA			OPERATOR_DEF_DATA_NUM, OPERATOR_PRI_NONE, OPERATOR_TARGET_DF, OPERATOR_POS_EP, OPERATOR_AXIS_NONE, OPERATOR_FLD_NONE, OPERATOR_CAMERA_NONE
	
	ADD_PARTICLE 	0,W_378_378_SIBORI_HAND, EMTFUNC_FIELD_OPERATOR
	EX_DATA			OPERATOR_DEF_DATA_NUM, OPERATOR_PRI_NONE, OPERATOR_TARGET_DF, OPERATOR_POS_EP, OPERATOR_AXIS_NONE, OPERATOR_FLD_NONE, OPERATOR_CAMERA_NONE

	SE_REPEAT_R		SEQ_SE_DP_021,10,5

	LOOP_LABEL		3

		//SE_R		SEQ_SE_DP_021

		FUNC_CALL	WEST_SP_WE_SSP_POKE_SCALE_UPDOWN, 8, (WE_TOOL_E1 | WE_TOOL_SSP), 100,  80, 100, 140, 100, 1, (IWAIT << 16) | OWAIT
		WAIT		TWAIT
		FUNC_CALL	WEST_SP_WE_SSP_POKE_SCALE_UPDOWN, 8, (WE_TOOL_E1 | WE_TOOL_SSP), 100, 120, 100,  80, 100, 1, (IWAIT << 16) | OWAIT
		WAIT		TWAIT
	LOOP
	
	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	SEQEND

