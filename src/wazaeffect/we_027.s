//==============================================================================
/**
 * @file	we_027.s
 * @brief	�܂킵����			27
 * @author	goto
 * @date	2005.07.13(��)
 *
 * �����ɐF�X�ȉ�����������Ă��悢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_MAWASIGERI
	
// =============================================================================
//
//
//	���܂킵����			27
//
//
// =============================================================================
#define WE098_SHAKE_W_X	(2)		// �ӂ蕝
#define WE098_SHAKE_NUM	(1)		// �ӂ��
#define WE098_SHAKE_SYNC (1)	// �V���N��
WEST_MAWASIGERI:

	LOAD_PARTICLE_DROP	0,W_027_SPA

	// �|�P����OAM����
	POKEOAM_RES_INIT

	POKEOAM_RES_LOAD	0,
	POKEOAM_RES_LOAD	1,

	// �`��J�n
	POKEOAM_DROP		WEDEF_DROP_M1, WEDEF_POKE_AUTO_OFF, WEDEF_POKE_CAP_ID_0, WEDEF_POKE_RES_0,
	POKEOAM_DROP		WEDEF_DROP_M1, WEDEF_POKE_AUTO_OFF, WEDEF_POKE_CAP_ID_1, WEDEF_POKE_RES_1,
	PT_DROP_EX			WEDEF_DROP_M2, WEDEF_DROP_M2,

	FUNC_CALL		WEST_SP_WE_098, 0,0,0,0,0,0,0,0,0
	ADD_PARTICLE 	0,W_027_FOOT_TURN01,	EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_027_RING_TURN01,	EMTFUNC_DEFENCE_POS
	FUNC_CALL		WEST_SP_WT_SHAKE, 5, 1, 0, 1, 2,  WE_TOOL_E1 | WE_TOOL_SSP,	
	//SE_R			SEQ_SE_DP_030
	//SE_WAITPLAY_R	SEQ_SE_DP_050,10
	SE_R			SEQ_SE_DP_050
	WAIT 20

	// �|�P����OAM�j�� PT�A�^�b�N��OAM�̂܂܂��ƃq�b�g�}�[�N���o�Ȃ�����B
	POKEOAM_RES_FREE
	POKEOAM_DROP_RESET	WEDEF_POKE_CAP_ID_0
	POKEOAM_DROP_RESET	WEDEF_POKE_CAP_ID_1
	PT_DROP_RESET_EX
	
	FUNC_CALL		WEST_SP_WT_SHAKE, 5, WE098_SHAKE_W_X, 0,WE098_SHAKE_SYNC, WE098_SHAKE_NUM, WE_TOOL_E1 | WE_TOOL_SSP, 0, 0
	ADD_PARTICLE 	0,W_027_001_HIT_MARK,	EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_027_001_BALL_BURN,	EMTFUNC_DEFENCE_POS
	SE_R			SEQ_SE_DP_030

	WAIT_PARTICLE
	EXIT_PARTICLE	0,

	WAIT_FLAG	///<TCB�҂�

	SEQEND
