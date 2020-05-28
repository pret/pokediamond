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
#define WE_029_MOVE_X	(14)
#define WE_029_MOVE_Y	(8)

WEST_442:
	LOAD_PARTICLE_DROP	0,W_442_SPA

	SE_L			SEQ_SE_DP_W029
	//SE_R			SEQ_SE_DP_143
	SE_R			SEQ_SE_DP_030

	FUNC_CALL		WEST_SP_WE_T10,	4, 2, +WE_029_MOVE_X, -WE_029_MOVE_Y, WE_TOOL_M1 | WE_TOOL_SSP
	WAIT_FLAG
	
	ADD_PARTICLE 	0,W_442_442_IRON_HIT,		EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_442_442_IRON_STONE,		EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_442_442_IRON_BALL,		EMTFUNC_DEFENCE_POS
	
	WAIT			5
	SE_R			SEQ_SE_DP_W088
	FUNC_CALL		WEST_SP_WT_SHAKE, 5, SHAKE_M_X, 0, SHAKE_M_WAIT, SHAKE_M_NUM,  WE_TOOL_E1 | WE_TOOL_SSP,

	FUNC_CALL		WEST_SP_WE_T10,	4, 2, -WE_029_MOVE_X, +WE_029_MOVE_Y, WE_TOOL_M1 | WE_TOOL_SSP
	WAIT_FLAG

	WAIT_PARTICLE
	EXIT_PARTICLE	0,

	SEQEND
