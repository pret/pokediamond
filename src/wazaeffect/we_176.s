//==============================================================================
/**
 * @file	we_176.s
 * @brief	テクスチャー２			176
 * @author	goto
 * @date	2005.07.13(水)
 *
 * ここに色々な解説等を書いてもよい
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_TEKUSUTYAA2
	
// =============================================================================
//
//
//	■テクスチャー２			176
//
//
// =============================================================================
WEST_TEKUSUTYAA2:
	

	LOAD_PARTICLE_DROP	0,W_176_SPA
	ADD_PARTICLE 	0,W_176_176_TEX2_DUST1, EMTFUNC_DEFENCE_POS

	ADD_PARTICLE 	0,W_176_176_TEX2_DUST2, EMTFUNC_FIELD_OPERATOR
	EX_DATA			OPERATOR_DEF_DATA_NUM, OPERATOR_PRI_NONE, OPERATOR_TARGET_AT, OPERATOR_POS_SP, OPERATOR_AXIS_AT, OPERATOR_FLD_NONE, OPERATOR_CAMERA_NONE
	
	SE_REPEAT_R		SEQ_SE_DP_W112,5,4
	
	ADD_PARTICLE 	0,W_176_176_TEX2_DUST3, EMTFUNC_ATTACK_POS
	//SE_WAITPLAY_R	SEQ_SE_DP_HURU2,45
	SE_WAITPLAY_R	SEQ_SE_DP_W104,45

	SE_WAITPLAY_L	SEQ_SE_DP_351,65

	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	
	SEQEND
