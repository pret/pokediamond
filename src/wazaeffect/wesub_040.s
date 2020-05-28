//==============================================================================
/**
 * @file	we_275.s
 * @brief	ÇÀÇÇÕÇÈ			275
 * @author	goto
 * @date	2005.07.13(êÖ)
 *
 * Ç±Ç±Ç…êFÅXÇ»âê‡ìôÇèëÇ¢ÇƒÇ‡ÇÊÇ¢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_NEWOHARU
	
// =============================================================================
//
//
//	Å°ÇÀÇÇÕÇÈ			275
//
//
// =============================================================================
#define W275_OAM_MAX	(4)
WEST_NEWOHARU:

	LOAD_PARTICLE_DROP			0, W_275_SPA
	
	///< OAM
	CATS_RES_INIT			0, W275_OAM_MAX, 1,1,1,1,0,0
	CATS_CAHR_RES_LOAD		0, EFFECT_275_NCGR_BIN
	CATS_PLTT_RES_LOAD		0, EFFECT_275_NCLR, 1
	CATS_CELL_RES_LOAD		0, EFFECT_275_NCER_BIN
	CATS_CELL_ANM_RES_LOAD	0, EFFECT_275_NANR_BIN
	CATS_ACT_ADD			0, WEST_CSP_WE_275,  EFFECT_275_NCGR_BIN, EFFECT_275_NCLR, EFFECT_275_NCER_BIN, EFFECT_275_NANR_BIN, 0, 0, 1, W275_OAM_MAX

	SE_WAITPLAY_L	SEQ_SE_DP_W010,10
	SE_WAITPLAY_L	SEQ_SE_DP_W010,28
	SE_WAITPLAY_L	SEQ_SE_DP_W010,98
	SE_WAITPLAY_L	SEQ_SE_DP_W010,108
	WAIT			35
	SE_REPEAT_L		SEQ_SE_DP_W145C,2,12

	ADD_PARTICLE 	0,W_275_TURN_DRAIN1, EMTFUNC_ATTACK_POS

	WAIT_FLAG
	CATS_RES_FREE			0
	
	SEQEND
