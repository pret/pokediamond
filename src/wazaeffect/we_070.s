//==============================================================================
/**
 * @file	we_070.s
 * @brief	Ç©Ç¢ÇËÇ´			70
 * @author	goto
 * @date	2005.07.13(êÖ)
 *
 * Ç±Ç±Ç…êFÅXÇ»âê‡ìôÇèëÇ¢ÇƒÇ‡ÇÊÇ¢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_KAIRIKI
	
// =============================================================================
//
//
//	Å°Ç©Ç¢ÇËÇ´			70
//
//
// =============================================================================

#define SC_MIN		(70)
#define SC_MAX		(120)
#define SC_MINS		(10)
#define SC_MAXS		(5)
#define WE070_ROTA_NUM	(3)
#define WE070_SYNC		(10)

WEST_KAIRIKI:

	LOAD_PARTICLE_DROP	0,W_004_SPA
	
	FUNC_CALL		WEST_SP_WE_070,	4, SC_MIN, SC_MAX, SC_MINS, SC_MAXS
	SE_L			SEQ_SE_DP_W036
	
	WAIT_FLAG
	
	SE_R			SEQ_SE_DP_W025B
	FUNC_CALL		WEST_SP_WE_066, 3, WE070_ROTA_NUM, WE070_SYNC, WE_TOOL_E1, 0, 0, 0, 0, 0
	ADD_PARTICLE	0,W_004_PUNCH_HIT01,	 EMTFUNC_DEFENCE_POS
	
	WAIT_FLAG
	
	SEQEND
