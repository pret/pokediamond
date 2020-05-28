//==============================================================================
/**
 * @file	west_sp_def.h
 * @brief	�Z�G�t�F�N�g�T�|�[�g�֐��pdefine.h
 * @author	goto
 * @date	2005.07.14(��)
 *
 * �����ɐF�X�ȉ�����������Ă��悢
 *
 */
//==============================================================================

// =============================================================================
//
//
//	���T�|�[�g�p�}�N������
//
//
// =============================================================================
	.macro	WEST_SP_INIT_CMD
		WEST_SP_DEF_CMD_COUNT	= 0;
	.endm
	
	.macro	WEST_SP_DEF_CMD		symname
		\symname				= WEST_SP_DEF_CMD_COUNT;
		WEST_SP_DEF_CMD_COUNT	= (WEST_SP_DEF_CMD_COUNT + 1);
	.endm
	
	.macro	WEST_SP_DEFINE		symname, data
		\symname				= \data;	
	.endm
	

// =============================================================================
//
//
//	���T�|�[�g�p�}�N��		(��`�ǉ��ʒu)
//		enum �݂����Ȋ���
//
//
// =============================================================================

	WEST_SP_INIT_CMD
	
	// ---------- �T���v���������� ----------

	WEST_SP_DEF_CMD		WEST_SP_TEST_1
	WEST_SP_DEF_CMD		WEST_SP_TEST_2
	WEST_SP_DEF_CMD		WEST_SP_TEST_3
	WEST_SP_DEF_CMD		WEST_SP_TEST_4
	
	// ---------- �T���v�������܂� ----------
	WEST_SP_DEF_CMD		WEST_SP_POKEROTA_00		///< ���Ŏg�p�@�|�P������������]������
	WEST_SP_DEF_CMD		WEST_SP_WE_070
	WEST_SP_DEF_CMD		WEST_SP_WE_339
	WEST_SP_DEF_CMD		WEST_SP_WE_104
	WEST_SP_DEF_CMD		WEST_SP_WE_098	
	WEST_SP_DEF_CMD		WEST_SP_WE_065	
	WEST_SP_DEF_CMD		WEST_SP_WE_066	
	WEST_SP_DEF_CMD		WEST_SP_WE_093	
	WEST_SP_DEF_CMD		WEST_SP_WE_151	
	WEST_SP_DEF_CMD		WEST_SP_WE_074	
	WEST_SP_DEF_CMD		WEST_SP_WE_096	
	WEST_SP_DEF_CMD		WEST_SP_WE_100	
	WEST_SP_DEF_CMD		WEST_SP_WE_148	
	WEST_SP_DEF_CMD		WEST_SP_WE_101AT	
	WEST_SP_DEF_CMD		WEST_SP_WE_101DF	
	WEST_SP_DEF_CMD		WEST_SP_WE_150	
	WEST_SP_DEF_CMD		WEST_SP_WE_180	
	WEST_SP_DEF_CMD		WEST_SP_WE_106	
	WEST_SP_DEF_CMD		WEST_SP_WE_107
	WEST_SP_DEF_CMD		WEST_SP_WE_185
	WEST_SP_DEF_CMD		WEST_SP_WE_089
	WEST_SP_DEF_CMD		WEST_SP_WE_204
	WEST_SP_DEF_CMD		WEST_SP_WE_171
	WEST_SP_DEF_CMD		WEST_SP_WE_175
	WEST_SP_DEF_CMD		WEST_SP_WE_222
	WEST_SP_DEF_CMD		WEST_SP_WE_216
	WEST_SP_DEF_CMD		WEST_SP_WE_233
	WEST_SP_DEF_CMD		WEST_SP_WE_207_MAIN
	WEST_SP_DEF_CMD		WEST_SP_WE_262
	WEST_SP_DEF_CMD		WEST_SP_WE_HAIKEI_PAL_FADE
	WEST_SP_DEF_CMD		WEST_SP_WE_SSP_POKE_PAL_FADE
	WEST_SP_DEF_CMD		WEST_SP_WE_CAP_POKE_SCALE_UPDOWN
	WEST_SP_DEF_CMD		WEST_SP_WT_SHAKE
	WEST_SP_DEF_CMD		WEST_SP_WE_326
	WEST_SP_DEF_CMD		WEST_SP_WE_CAP_ALPHA_FADE
	WEST_SP_DEF_CMD		WEST_SP_WE_316
	WEST_SP_DEF_CMD		WEST_SP_WE_SSP_POKE_VANISH
	WEST_SP_DEF_CMD		WEST_SP_WE_252_BACK
	WEST_SP_DEF_CMD		WEST_SP_WE_SSP_POKE_SCALE_UPDOWN
	WEST_SP_DEF_CMD		WEST_SP_WE_252_POKE
	WEST_SP_DEF_CMD		WEST_SP_WE_T02
	WEST_SP_DEF_CMD		WEST_SP_WE_T22
	WEST_SP_DEF_CMD		WEST_SP_WE_224
	WEST_SP_DEF_CMD		WEST_SP_WE_224AT
	WEST_SP_DEF_CMD		WEST_SP_WE_224DF
	WEST_SP_DEF_CMD		WEST_SP_WE_057
	WEST_SP_DEF_CMD		WEST_SP_WE_T03
	WEST_SP_DEF_CMD		WEST_SP_WE_T04
	WEST_SP_DEF_CMD		WEST_SP_WE_T05
	WEST_SP_DEF_CMD		WEST_SP_WE_T06
	WEST_SP_DEF_CMD		WEST_SP_WE_T07
	WEST_SP_DEF_CMD		WEST_SP_WE_293
	WEST_SP_DEF_CMD		WEST_SP_WE_T08
	WEST_SP_DEF_CMD		WEST_SP_WE_T10
	WEST_SP_DEF_CMD		WEST_SP_WE_102
	WEST_SP_DEF_CMD		WEST_SP_WE_325
	WEST_SP_DEF_CMD		WEST_SP_WE_KAITEN
	WEST_SP_DEF_CMD		WEST_SP_WE_DISP_OUT
	WEST_SP_DEF_CMD		WEST_SP_WE_DISP_DEF
	WEST_SP_DEF_CMD		WEST_SP_WE_OAM_PAL_FADE
	WEST_SP_DEF_CMD		WEST_SP_WE_VISIBLE_SET
	WEST_SP_DEF_CMD		WEST_SP_EMIT_STRAIGHT
	WEST_SP_DEF_CMD		WEST_SP_EMIT_PARABOLIC
	WEST_SP_DEF_CMD		WEST_SP_RECT_VIEW
	WEST_SP_DEF_CMD		WEST_SP_BG_SHAKE
	WEST_SP_DEF_CMD		WEST_SP_MOSAIC
	WEST_SP_DEF_CMD		WEST_SP_272
	WEST_SP_DEF_CMD		WEST_SP_289
	WEST_SP_DEF_CMD		WEST_SP_EMIT_ROTATION
	WEST_SP_DEF_CMD		WEST_SP_EMIT_SIMPLE_UD
	WEST_SP_DEF_CMD		WEST_SP_PALCOL_CHANGE
	WEST_SP_DEF_CMD		WEST_SP_POKE_OAM_VIEW
	WEST_SP_DEF_CMD		WEST_SP_LASTER
	WEST_SP_DEF_CMD		WEST_SP_DISP_MOVE
	WEST_SP_DEF_CMD		WEST_SP_ALL_DROP
	WEST_SP_DEF_CMD		WEST_SP_166
	
	// ----- �X�e�[�^�X�G�t�F�N�g -----
	WEST_SP_DEF_CMD		ST_EFF_UP
	WEST_SP_DEF_CMD		ST_EFF_DOWN
	WEST_SP_DEF_CMD		ST_EFF_RECOVER
	WEST_SP_DEF_CMD		ST_EFF_METAL

// =============================================================================
//
//
//	���Z���A�N�^�[�T�|�[�g�p�}�N��		(��`�ǉ��ʒu)
//		enum �݂����Ȋ���
//
//
// =============================================================================

	WEST_SP_INIT_CMD
	
	// ---------- �T���v���������� ----------
	
	WEST_SP_DEF_CMD		CLACT_SP_TEST_1
	
	// ---------- �T���v�������܂� ----------
	WEST_SP_DEF_CMD		WEST_CSP_WE_081
	WEST_SP_DEF_CMD		CLACT_SP_WE_134
	WEST_SP_DEF_CMD		WEST_CSP_WE_271
	WEST_SP_DEF_CMD		WEST_CSP_WE_118
	WEST_SP_DEF_CMD		WEST_CSP_WE_132
	WEST_SP_DEF_CMD		WEST_CSP_WE_155
	WEST_SP_DEF_CMD		WEST_CSP_WE_184
	WEST_SP_DEF_CMD		WEST_CSP_WE_193
	WEST_SP_DEF_CMD		WEST_CSP_WE_199
	WEST_SP_DEF_CMD		WEST_CSP_WE_207_SUB
	WEST_SP_DEF_CMD		WEST_CSP_WE_212
	WEST_SP_DEF_CMD		WEST_CSP_WE_259
	WEST_SP_DEF_CMD		WEST_CSP_WE_226
	WEST_SP_DEF_CMD		WEST_CSP_WE_286
	WEST_SP_DEF_CMD		WEST_CSP_WE_288
	WEST_SP_DEF_CMD		WEST_CSP_WE_320
	WEST_SP_DEF_CMD		WEST_CSP_WE_333
	WEST_SP_DEF_CMD		WEST_CSP_WE_252
	WEST_SP_DEF_CMD		WEST_CSP_WE_269
	WEST_SP_DEF_CMD		WEST_CSP_WE_270
	WEST_SP_DEF_CMD		WEST_CSP_WE_274
	WEST_SP_DEF_CMD		WEST_CSP_WE_232
	WEST_SP_DEF_CMD		WEST_CSP_WE_275
	WEST_SP_DEF_CMD		WEST_CSP_WE_338
	WEST_SP_DEF_CMD		WEST_CSP_FREE
	WEST_SP_DEF_CMD		WEST_CSP_WE_266
	WEST_SP_DEF_CMD		WEST_CSP_WE_090
	WEST_SP_DEF_CMD		WEST_CSP_WE_ITEM

	/**** �X�e�[�^�X�G�t�F�N�g ****/
	WEST_SP_DEF_CMD		WEST_CSP_ST_001
	WEST_SP_DEF_CMD		WEST_CSP_ST_003
	WEST_SP_DEF_CMD		WEST_CSP_ST_004
	WEST_SP_DEF_CMD		WEST_CSP_ST_006
	

// =============================================================================
//
//
//	������͓��������ǁA���O�����킩��₷����������
//
//
// =============================================================================

	// -------------------------------------
	// �h�䑤��SS��h�炷
	// ���� �v�f��, 1, �ӂ蕝x, �ӂ蕝y, �Ԋu, ��
	// -------------------------------------
	WEST_SP_DEFINE		WEST_SP_SHAKE,	WEST_SP_WE_175
	
	// -------------------------------------
	// �h�䑤�ɂނ��ނ��}�[�N���o��
	// -------------------------------------
	WEST_SP_DEFINE		WEST_SP_MARK_MUKAMUKA,	WEST_CSP_WE_207_SUB

	// -------------------------------------
	// �|�P�����������Ă񂳂���
	// �����@�J�n�p�x, �I���p�x, �V���N��
	// -------------------------------------
	WEST_SP_DEFINE		WEST_SP_POKE_ROTA,	WEST_SP_POKEROTA_00

	// -------------------------------------
	// �|�P�������f�t�H���g��]�ʂŉ�]�ړ�������
	// �����@��]�񐔁@�P��]�V���N���@�Ώۃ|�P�����i�P�́jWE_TOOL_M1...
	// -------------------------------------
	WEST_SP_DEFINE		WEST_SP_DEFROTA_MOVE,	WEST_SP_WE_066


// =============================================================================
//
//
//	��OLDACT�T�|�[�g�p�}�N��		(��`�ǉ��ʒu)
//		enum �݂����Ȋ���
//
//
// =============================================================================

	WEST_SP_INIT_CMD
	
	WEST_SP_DEF_CMD		OLDACT_WAZA_IAIGIRI_INIT

