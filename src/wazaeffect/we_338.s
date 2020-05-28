//==============================================================================
/**
 * @file	we_338.s
 * @brief	ハードプラント			338
 * @author	goto
 * @date	2005.07.13(水)
 *
 * ここに色々な解説等を書いてもよい
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_HAADOPURANTO
	
// =============================================================================
//
//
//	■ハードプラント			338
//
//
// =============================================================================
#define W338_OAM_MAX	(8)

WEST_HAADOPURANTO:
		
	LOAD_PARTICLE_DROP	0,W_338_SPA

	WORK_CLEAR
	WORK_SET		WEDEF_GP_INDEX_SPEED_X,  0
	WORK_SET		WEDEF_GP_INDEX_SPEED_Y,  16
	HAIKEI_CHG		BG_ID_338, WEDEF_HAIKEI_MODE_FADE | WEDEF_HAIKEI_SBIT_MOVE
	HAIKEI_CHG_WAIT

	SE_REPEAT_C		SEQ_SE_DP_W010,2,16
	
	///< OAM
	CATS_RES_INIT			0, W338_OAM_MAX, 1,1,1,1,0,0
	CATS_CAHR_RES_LOAD		0, EFFECT_275_NCGR_BIN
	CATS_PLTT_RES_LOAD		0, EFFECT_275_NCLR, 1
	CATS_CELL_RES_LOAD		0, EFFECT_275_NCER_BIN
	CATS_CELL_ANM_RES_LOAD	0, EFFECT_275_NANR_BIN

	CATS_ACT_ADD			0, WEST_CSP_WE_338,  EFFECT_275_NCGR_BIN, EFFECT_275_NCLR, EFFECT_275_NCER_BIN, EFFECT_275_NANR_BIN, 0, 0, 1, W338_OAM_MAX
	
	WAIT					96
	SE_REPEAT_R		SEQ_SE_DP_W025B,3,6
	ADD_PARTICLE 	0,W_338_338_HITMARK, EMTFUNC_DEFENCE_POS
	FUNC_CALL		WEST_SP_WT_SHAKE, 5, SHAKE_M_X, 0, SHAKE_M_WAIT, SHAKE_M_NUM*5,  WE_TOOL_E1 | WE_TOOL_SSP,
	
	WAIT_FLAG
	CATS_RES_FREE			0
	
	WAIT_PARTICLE
	EXIT_PARTICLE	0,

	WORK_CLEAR
	WORK_SET		WEDEF_GP_INDEX_SPEED_X,  0
	WORK_SET		WEDEF_GP_INDEX_SPEED_Y,  16
	HAIKEI_RECOVER	BG_ID_338, WEDEF_HAIKEI_RC_MODE_FADE | WEDEF_HAIKEI_SBIT_STOP
	HAIKEI_CHG_WAIT	
	SEQEND
