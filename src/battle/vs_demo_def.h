//============================================================================================
/**
 * @file	vs_demo_def.h
 * @brief	�ʐM�ΐ�f���@�萔��`
 * @author	Hiroyuki Nakamura
 * @date	06.04.26
 */
//============================================================================================
// �m�F��ʁF�p���b�g�g�p��`
enum {
	PAL_FONT = 0,		// �t�H���g
	PAL_PANEL_0 = 3,	// �v���[�g�P
	PAL_PANEL_1,		// �v���[�g�Q
	PAL_PANEL_2,		// �v���[�g�R
	PAL_PANEL_3,		// �v���[�g�S
	PAL_PANEL_4,		// �v���[�g�T
	PAL_PANEL_5,		// �v���[�g�U
};

// BMP�E�B���h�E��`
// �j�b�N�l�[���F�P�̖�
#define	WIN_NAME1_PX	( 6 )
#define	WIN_NAME1_PY	( 1 )
#define	WIN_NAME1_SX	( 9 )
#define	WIN_NAME1_SY	( 2 )
#define	WIN_NAME1_PAL	( PAL_FONT )
#define	WIN_NAME1_CGX	( 1 )
// ���x���F�P�̖�
#define	WIN_LV1_PX		( 1 )
#define	WIN_LV1_PY		( 4 )
#define	WIN_LV1_SX		( 5 )
#define	WIN_LV1_SY		( 2 )
#define	WIN_LV1_PAL		( PAL_FONT )
#define	WIN_LV1_CGX		( WIN_NAME1_CGX + WIN_NAME1_SX * WIN_NAME1_SY )
// HP/MHP�F�P�̖�
#define	WIN_HP1_PX		( 7 )
#define	WIN_HP1_PY		( 4 )
#define	WIN_HP1_SX		( 8 )
#define	WIN_HP1_SY		( 2 )
#define	WIN_HP1_PAL		( PAL_FONT )
#define	WIN_HP1_CGX		( WIN_LV1_CGX + WIN_LV1_SX * WIN_LV1_SY )
// HP�Q�[�W�F�P�̖�
#define	WIN_HPBAR1_PX	( 8 )
#define	WIN_HPBAR1_PY	( 3 )
#define	WIN_HPBAR1_SX	( 6 )
#define	WIN_HPBAR1_SY	( 1 )
#define	WIN_HPBAR1_PAL	( PAL_PANEL_0 )
#define	WIN_HPBAR1_CGX	( WIN_HP1_CGX + WIN_HP1_SX * WIN_HP1_SY )

// �j�b�N�l�[���F�Q�̖�
#define	WIN_NAME2_PX	( 6 )
#define	WIN_NAME2_PY	( 7 )
#define	WIN_NAME2_SX	( 9 )
#define	WIN_NAME2_SY	( 2 )
#define	WIN_NAME2_PAL	( PAL_FONT )
#define	WIN_NAME2_CGX	( WIN_HPBAR1_CGX + WIN_HPBAR1_SX * WIN_HPBAR1_SY )
// ���x���F�Q�̖�
#define	WIN_LV2_PX		( 1 )
#define	WIN_LV2_PY		( 10 )
#define	WIN_LV2_SX		( 5 )
#define	WIN_LV2_SY		( 2 )
#define	WIN_LV2_PAL		( PAL_FONT )
#define	WIN_LV2_CGX		( WIN_NAME2_CGX + WIN_NAME2_SX * WIN_NAME2_SY )
// HP/MHP�F�Q�̖�
#define	WIN_HP2_PX		( 7 )
#define	WIN_HP2_PY		( 10 )
#define	WIN_HP2_SX		( 8 )
#define	WIN_HP2_SY		( 2 )
#define	WIN_HP2_PAL		( PAL_FONT )
#define	WIN_HP2_CGX		( WIN_LV2_CGX + WIN_LV2_SX * WIN_LV2_SY )
// HP�Q�[�W�F�Q�̖�
#define	WIN_HPBAR2_PX	( 8 )
#define	WIN_HPBAR2_PY	( 9 )
#define	WIN_HPBAR2_SX	( 6 )
#define	WIN_HPBAR2_SY	( 1 )
#define	WIN_HPBAR2_PAL	( PAL_PANEL_1 )
#define	WIN_HPBAR2_CGX	( WIN_HP2_CGX + WIN_HP2_SX * WIN_HP2_SY )

// �j�b�N�l�[���F�R�̖�
#define	WIN_NAME3_PX	( 6 )
#define	WIN_NAME3_PY	( 13 )
#define	WIN_NAME3_SX	( 9 )
#define	WIN_NAME3_SY	( 2 )
#define	WIN_NAME3_PAL	( PAL_FONT )
#define	WIN_NAME3_CGX	( WIN_HPBAR2_CGX + WIN_HPBAR2_SX * WIN_HPBAR2_SY )
// ���x���F�R�̖�
#define	WIN_LV3_PX		( 1 )
#define	WIN_LV3_PY		( 16 )
#define	WIN_LV3_SX		( 5 )
#define	WIN_LV3_SY		( 2 )
#define	WIN_LV3_PAL		( PAL_FONT )
#define	WIN_LV3_CGX		( WIN_NAME3_CGX + WIN_NAME3_SX * WIN_NAME3_SY )
// HP/MHP�F�R�̖�
#define	WIN_HP3_PX		( 7 )
#define	WIN_HP3_PY		( 16 )
#define	WIN_HP3_SX		( 8 )
#define	WIN_HP3_SY		( 2 )
#define	WIN_HP3_PAL		( PAL_FONT )
#define	WIN_HP3_CGX		( WIN_LV3_CGX + WIN_LV3_SX * WIN_LV3_SY )
// HP�Q�[�W�F�R�̖�
#define	WIN_HPBAR3_PX	( 8 )
#define	WIN_HPBAR3_PY	( 15 )
#define	WIN_HPBAR3_SX	( 6 )
#define	WIN_HPBAR3_SY	( 1 )
#define	WIN_HPBAR3_PAL	( PAL_PANEL_2 )
#define	WIN_HPBAR3_CGX	( WIN_HP3_CGX + WIN_HP3_SX * WIN_HP3_SY )

// �j�b�N�l�[���F�S�̖�
#define	WIN_NAME4_PX	( 22 )
#define	WIN_NAME4_PY	( 2 )
#define	WIN_NAME4_SX	( 9 )
#define	WIN_NAME4_SY	( 2 )
#define	WIN_NAME4_PAL	( PAL_FONT )
#define	WIN_NAME4_CGX	( WIN_HPBAR3_CGX + WIN_HPBAR3_SX * WIN_HPBAR3_SY )
// ���x���F�S�̖�
#define	WIN_LV4_PX		( 17 )
#define	WIN_LV4_PY		( 5 )
#define	WIN_LV4_SX		( 5 )
#define	WIN_LV4_SY		( 2 )
#define	WIN_LV4_PAL		( PAL_FONT )
#define	WIN_LV4_CGX		( WIN_NAME4_CGX + WIN_NAME4_SX * WIN_NAME4_SY )
// HP/MHP�F�S�̖�
#define	WIN_HP4_PX		( 23 )
#define	WIN_HP4_PY		( 5 )
#define	WIN_HP4_SX		( 8 )
#define	WIN_HP4_SY		( 2 )
#define	WIN_HP4_PAL		( PAL_FONT )
#define	WIN_HP4_CGX		( WIN_LV4_CGX + WIN_LV4_SX * WIN_LV4_SY )
// HP�Q�[�W�F�S�̖�
#define	WIN_HPBAR4_PX	( 24 )
#define	WIN_HPBAR4_PY	( 4 )
#define	WIN_HPBAR4_SX	( 6 )
#define	WIN_HPBAR4_SY	( 1 )
#define	WIN_HPBAR4_PAL	( PAL_PANEL_3 )
#define	WIN_HPBAR4_CGX	( WIN_HP4_CGX + WIN_HP4_SX * WIN_HP4_SY )

// �j�b�N�l�[���F�T�̖�
#define	WIN_NAME5_PX	( 22 )
#define	WIN_NAME5_PY	( 8 )
#define	WIN_NAME5_SX	( 9 )
#define	WIN_NAME5_SY	( 2 )
#define	WIN_NAME5_PAL	( PAL_FONT )
#define	WIN_NAME5_CGX	( WIN_HPBAR4_CGX + WIN_HPBAR4_SX * WIN_HPBAR4_SY )
// ���x���F�T�̖�
#define	WIN_LV5_PX		( 17 )
#define	WIN_LV5_PY		( 11 )
#define	WIN_LV5_SX		( 5 )
#define	WIN_LV5_SY		( 2 )
#define	WIN_LV5_PAL		( PAL_FONT )
#define	WIN_LV5_CGX		( WIN_NAME5_CGX + WIN_NAME5_SX * WIN_NAME5_SY )
// HP/MHP�F�T�̖�
#define	WIN_HP5_PX		( 23 )
#define	WIN_HP5_PY		( 11 )
#define	WIN_HP5_SX		( 8 )
#define	WIN_HP5_SY		( 2 )
#define	WIN_HP5_PAL		( PAL_FONT )
#define	WIN_HP5_CGX		( WIN_LV5_CGX + WIN_LV5_SX * WIN_LV5_SY )
// HP�Q�[�W�F�T�̖�
#define	WIN_HPBAR5_PX	( 24 )
#define	WIN_HPBAR5_PY	( 10 )
#define	WIN_HPBAR5_SX	( 6 )
#define	WIN_HPBAR5_SY	( 1 )
#define	WIN_HPBAR5_PAL	( PAL_PANEL_4 )
#define	WIN_HPBAR5_CGX	( WIN_HP5_CGX + WIN_HP5_SX * WIN_HP5_SY )

// �j�b�N�l�[���F�U�̖�
#define	WIN_NAME6_PX	( 22 )
#define	WIN_NAME6_PY	( 14 )
#define	WIN_NAME6_SX	( 9 )
#define	WIN_NAME6_SY	( 2 )
#define	WIN_NAME6_PAL	( PAL_FONT )
#define	WIN_NAME6_CGX	( WIN_HPBAR5_CGX + WIN_HPBAR5_SX * WIN_HPBAR5_SY )
// ���x���F�U�̖�
#define	WIN_LV6_PX		( 17 )
#define	WIN_LV6_PY		( 17 )
#define	WIN_LV6_SX		( 5 )
#define	WIN_LV6_SY		( 2 )
#define	WIN_LV6_PAL		( PAL_FONT )
#define	WIN_LV6_CGX		( WIN_NAME6_CGX + WIN_NAME6_SX * WIN_NAME6_SY )
// HP/MHP�F�U�̖�
#define	WIN_HP6_PX		( 23 )
#define	WIN_HP6_PY		( 17 )
#define	WIN_HP6_SX		( 8 )
#define	WIN_HP6_SY		( 2 )
#define	WIN_HP6_PAL		( PAL_FONT )
#define	WIN_HP6_CGX		( WIN_LV6_CGX + WIN_LV6_SX * WIN_LV6_SY )
// HP�Q�[�W�F�U�̖�
#define	WIN_HPBAR6_PX	( 24 )
#define	WIN_HPBAR6_PY	( 16 )
#define	WIN_HPBAR6_SX	( 6 )
#define	WIN_HPBAR6_SY	( 1 )
#define	WIN_HPBAR6_PAL	( PAL_PANEL_5 )
#define	WIN_HPBAR6_CGX	( WIN_HP6_CGX + WIN_HP6_SX * WIN_HP6_SY )

// BMP�E�B���h�EID
enum {
	// �P�̖ڂ̃|�P����
	WIN_NAME1 = 0,	// ���O
	WIN_LV1,		// Lv
	WIN_HP1,		// HP/MHP
	WIN_HPBAR1,		// HP�o�[
	// �Q�̖ڂ̃|�P����
	WIN_NAME2,		// ���O
	WIN_LV2,		// Lv
	WIN_HP2,		// HP/MHP
	WIN_HPBAR2,		// HP�o�[
	// �R�̖ڂ̃|�P����
	WIN_NAME3,		// ���O
	WIN_LV3,		// Lv
	WIN_HP3,		// HP/MHP
	WIN_HPBAR3,		// HP�o�[
	// �S�̖ڂ̃|�P����
	WIN_NAME4,		// ���O
	WIN_LV4,		// Lv
	WIN_HP4,		// HP/MHP
	WIN_HPBAR4,		// HP�o�[
	// �T�̖ڂ̃|�P����
	WIN_NAME5,		// ���O
	WIN_LV5,		// Lv
	WIN_HP5,		// HP/MHP
	WIN_HPBAR5,		// HP�o�[
	// �U�̖ڂ̃|�P����
	WIN_NAME6,		// ���O
	WIN_LV6,		// Lv
	WIN_HP6,		// HP/MHP
	WIN_HPBAR6,		// HP�o�[

	VSD_BMP_MAX
};

// �Z���A�N�^�[ID
enum {
	VS_CLA_BALL01 = 0,	// VS��ʁF�������{�[���P
	VS_CLA_BALL02,		// VS��ʁF�������{�[���Q
	VS_CLA_BALL03,		// VS��ʁF�������{�[���R
	VS_CLA_BALL04,		// VS��ʁF�������{�[���S
	VS_CLA_BALL05,		// VS��ʁF�������{�[���T
	VS_CLA_BALL06,		// VS��ʁF�������{�[���U

	VS_CLA_BALL11,		// VS��ʁF�G���{�[���P
	VS_CLA_BALL12,		// VS��ʁF�G���{�[���Q
	VS_CLA_BALL13,		// VS��ʁF�G���{�[���R
	VS_CLA_BALL14,		// VS��ʁF�G���{�[���S
	VS_CLA_BALL15,		// VS��ʁF�G���{�[���T
	VS_CLA_BALL16,		// VS��ʁF�G���{�[���U

	VS_CLA_MAX,			// VS��ʁF�Z���A�N�^�[�ő�

	VS_CLA_RESULT1 = VS_CLA_MAX,	// ���s��ʁF���s�P
	VS_CLA_RESULT2,					// ���s��ʁF���s�Q

	VS_CLA_END_MAX,		// ���s��ʁF�Z���A�N�^�[�ő�

	VS_CLA_POKE1 = 0,	// �m�F��ʁF�|�P�����A�C�R���P
	VS_CLA_ITEM1,		// �m�F��ʁF�A�C�e���A�C�R���P
	VS_CLA_CB1,			// �m�F��ʁF�J�X�^���{�[���P
	VS_CLA_ST1,			// �m�F��ʁF��Ԉُ�A�C�R���P
	VS_CLA_PLBALL1,		// �m�F��ʁF�{�[���P
	VS_CLA_POKE2,		// �m�F��ʁF�|�P�����A�C�R���Q
	VS_CLA_ITEM2,		// �m�F��ʁF�A�C�e���A�C�R���Q
	VS_CLA_CB2,			// �m�F��ʁF�J�X�^���{�[���Q
	VS_CLA_ST2,			// �m�F��ʁF��Ԉُ�A�C�R���Q
	VS_CLA_PLBALL2,		// �m�F��ʁF�{�[���Q
	VS_CLA_POKE3,		// �m�F��ʁF�|�P�����A�C�R���R
	VS_CLA_ITEM3,		// �m�F��ʁF�A�C�e���A�C�R���R
	VS_CLA_CB3,			// �m�F��ʁF�J�X�^���{�[���R
	VS_CLA_ST3,			// �m�F��ʁF��Ԉُ�A�C�R���R
	VS_CLA_PLBALL3,		// �m�F��ʁF�{�[���R
	VS_CLA_POKE4,		// �m�F��ʁF�|�P�����A�C�R���S
	VS_CLA_ITEM4,		// �m�F��ʁF�A�C�e���A�C�R���S
	VS_CLA_CB4,			// �m�F��ʁF�J�X�^���{�[���S
	VS_CLA_ST4,			// �m�F��ʁF��Ԉُ�A�C�R���S
	VS_CLA_PLBALL4,		// �m�F��ʁF�{�[���S
	VS_CLA_POKE5,		// �m�F��ʁF�|�P�����A�C�R���T
	VS_CLA_ITEM5,		// �m�F��ʁF�A�C�e���A�C�R���T
	VS_CLA_CB5,			// �m�F��ʁF�J�X�^���{�[���T
	VS_CLA_ST5,			// �m�F��ʁF��Ԉُ�A�C�R���T
	VS_CLA_PLBALL5,		// �m�F��ʁF�{�[���T
	VS_CLA_POKE6,		// �m�F��ʁF�|�P�����A�C�R���U
	VS_CLA_ITEM6,		// �m�F��ʁF�A�C�e���A�C�R���U
	VS_CLA_CB6,			// �m�F��ʁF�J�X�^���{�[���U
	VS_CLA_ST6,			// �m�F��ʁF��Ԉُ�A�C�R���U
	VS_CLA_PLBALL6,		// �m�F��ʁF�{�[���U

	VS_CLA_PLMAX,		// �m�F��ʁF�Z���A�N�^�[�ő�
};

// ���C���V�[�P���X
enum {
	SEQ_VSD_INIT = 0,	// ������
	SEQ_VSD_MAIN,		// ���C��
	SEQ_VSD_END			// �I��
};

// �����R�}���h
enum {
	VSD_FUNC_LOOP = 0,		// ���s��
	VSD_FUNC_NEXT,			// ���̏�����
	VSD_FUNC_REPEAT,		// ���̏����𑦎��s
};


#define	INIT_WAIT	( 8 )	// �����E�F�C�g

#define	POKECHECK_INIT_WAIT	( 32 )	// �|�P�����m�F��ʁF�����E�F�C�g
#define	POKECHECK_END_WAIT	( 64 )	// �|�P�����m�F��ʁF�I���E�F�C�g

#define	SCROLL_SPEED	( 16 )		// VS��ʁF�X�N���[�����x
#define	SCROLL_INIT		( 256 )		// VS��ʁF�����X�N���[���J�E���^
#define	SCROLL_END		( 24 )		// VS��ʁF�X�N���[���I���ʒu

#define	END_SCROLL_SPEED	( 12 )	// ���s��ʁF�X�N���[�����x

#define	VS_CLA_BALL_SX		( 19 )	// VS��ʁF�{�[��X�T�C�Y
#define	VS_CLA_BALL_M_SX	( 4 )	// VS��ʁF�}���`�p��X�␳�T�C�Y

#define	VS_CLA_BALL00_PX	( 24 )	// VS��ʁF�������O���R�̃{�[���\��X���W�i�ʏ�j
#define	VS_CLA_BALL00_PY	( 160 )	// VS��ʁF�������O���R�̃{�[���\��Y���W�i�ʏ�j

// VS��ʁF�������㔼�R�̃{�[���\��X���W�i�ʏ�j
#define	VS_CLA_BALL03_PX	( VS_CLA_BALL00_PX + VS_CLA_BALL_SX * 3 )
// VS��ʁF�������㔼�R�̃{�[���\��Y���W�i�ʏ�j
#define	VS_CLA_BALL03_PY	( VS_CLA_BALL00_PY )

#define	VS_CLA_BALL10_PX	( 136 )	// VS��ʁF�G���O���R�̃{�[���\��X���W�i�ʏ�j
#define	VS_CLA_BALL10_PY	( 48 )	// VS��ʁF�G���O���R�̃{�[���\��Y���W�i�ʏ�j

// VS��ʁF�G���㔼�R�̃{�[���\��X���W�i�ʏ�j
#define	VS_CLA_BALL13_PX	( VS_CLA_BALL10_PX + VS_CLA_BALL_SX * 3 )
// VS��ʁF�G���㔼�R�̃{�[���\��Y���W�i�ʏ�j
#define	VS_CLA_BALL13_PY	( VS_CLA_BALL10_PY )

#define	VS_CLA_BALL00M_PX	( 24 )	// VS��ʁF�������O���R�̃{�[���\��X���W�i�}���`�j
#define	VS_CLA_BALL00M_PY	( 140 )	// VS��ʁF�������O���R�̃{�[���\��Y���W�i�}���`�j

// VS��ʁF�������㔼�R�̃{�[���\��X���W�i�}���`�j
#define	VS_CLA_BALL03M_PX	( VS_CLA_BALL00M_PX + VS_CLA_BALL_SX * 3 + VS_CLA_BALL_M_SX )
// VS��ʁF�������㔼�R�̃{�[���\��Y���W�i�}���`�j
#define	VS_CLA_BALL03M_PY	( 164 )

// VS��ʁF�G���O���R�̃{�[���\��X���W�i�}���`�j
#define	VS_CLA_BALL10M_PX	( 136 - VS_CLA_BALL_M_SX )
// VS��ʁF�G���O���R�̃{�[���\��Y���W�i�}���`�j
#define	VS_CLA_BALL10M_PY	( 44 )

// VS��ʁF�G���㔼�R�̃{�[���\��X���W�i�}���`�j
#define	VS_CLA_BALL13M_PX	( VS_CLA_BALL10M_PX + VS_CLA_BALL_SX * 3 + VS_CLA_BALL_M_SX )
// VS��ʁF�G���㔼�R�̃{�[���\��Y���W�i�}���`�j
#define	VS_CLA_BALL13M_PY	( 68 )

#define	VS_FOAM_NAME00_PX	( 15 )		// VS��ʁF�������̃v���C���[��X���W�i�ʏ�j
#define	VS_FOAM_NAME00_PY	( 134 )		// VS��ʁF�������̃v���C���[��Y���W�i�ʏ�j

#define	VS_FOAM_NAME00M_PX	( 15 )		// VS��ʁF�������̃v���C���[���PX���W�i�}���`�j
#define	VS_FOAM_NAME00M_PY	( 114 )		// VS��ʁF�������̃v���C���[���PY���W�i�}���`�j
#define	VS_FOAM_NAME03M_PX	( 76 )		// VS��ʁF�������̃v���C���[���QX���W�i�}���`�j
#define	VS_FOAM_NAME03M_PY	( 138 )		// VS��ʁF�������̃v���C���[���QY���W�i�}���`�j

#define	VS_FOAM_NAME10_PX	( 128 )		// VS��ʁF�G���̃v���C���[��X���W�i�ʏ�j
#define	VS_FOAM_NAME10_PY	( 22 )		// VS��ʁF�G���̃v���C���[��Y���W�i�ʏ�j

#define	VS_FOAM_NAME10M_PX	( 123 )		// VS��ʁF�G���̃v���C���[���PX���W�i�}���`�j
#define	VS_FOAM_NAME10M_PY	( 18 )		// VS��ʁF�G���̃v���C���[���PY���W�i�}���`�j
#define	VS_FOAM_NAME13M_PX	( 184 )		// VS��ʁF�G���̃v���C���[���QX���W�i�}���`�j
#define	VS_FOAM_NAME13M_PY	( 42 )		// VS��ʁF�G���̃v���C���[���QY���W�i�}���`�j

#define	CLACT_ID_COMMON		( 47111 )	// ���̉�ʂŎg�p����Z���A�N�^�[��ID

// �L�������\�[�XID
enum {
	VS_CHR_ID_BALL = CLACT_ID_COMMON,	// �{�[��
	VS_CHR_ID_RESULT,					// ���s
	VS_CHR_ID_MAX = VS_CHR_ID_RESULT - CLACT_ID_COMMON + 1,	// VS��ʁA���s��ʂ̍ő�

	VS_CHR_ID_POKE1 = VS_CHR_ID_RESULT + 1,	// �|�P�����A�C�R���P
	VS_CHR_ID_POKE2,						// �|�P�����A�C�R���Q
	VS_CHR_ID_POKE3,						// �|�P�����A�C�R���R
	VS_CHR_ID_POKE4,						// �|�P�����A�C�R���S
	VS_CHR_ID_POKE5,						// �|�P�����A�C�R���T
	VS_CHR_ID_POKE6,						// �|�P�����A�C�R���U
	VS_CHR_ID_ITEM,							// �A�C�e���A�C�R��
	VS_CHR_ID_ST,							// ��Ԉُ�A�C�R��
	VS_CHR_ID_PLBALL,						// �{�[��
	VS_CHR_ID_MV_MAX = VS_CHR_ID_PLBALL - VS_CHR_ID_POKE1 + 1	// �m�F��ʂ̍ő�
};

// �p���b�g���\�[�XID
enum {
	VS_PAL_ID_BALL = CLACT_ID_COMMON,	// �{�[��
	VS_PAL_ID_MAX = VS_PAL_ID_BALL - CLACT_ID_COMMON + 1,	// VS��ʁA���s��ʂ̍ő�

	VS_PAL_ID_POKE = VS_PAL_ID_BALL + 1,	// �|�P�����A�C�R��
	VS_PAL_ID_ITEM,							// �A�C�e���A�C�R��
	VS_PAL_ID_ST,							// ��Ԉُ�A�C�R��
	VS_PAL_ID_PLBALL,						// �{�[��
	VS_PAL_ID_MV_MAX = VS_PAL_ID_PLBALL - VS_PAL_ID_POKE + 1	// �m�F��ʂ̍ő�
};

// �Z�����\�[�XID
enum {
	VS_CEL_ID_BALL = CLACT_ID_COMMON,	// �{�[��
	VS_CEL_ID_RESULT,					// ���s
	VS_CEL_ID_MAX = VS_CEL_ID_RESULT - CLACT_ID_COMMON + 1,	// VS��ʁA���s��ʂ̍ő�

	VS_CEL_ID_POKE = VS_CEL_ID_RESULT + 1,	// �|�P�����A�C�R��
	VS_CEL_ID_ITEM,							// �A�C�e���A�C�R��
	VS_CEL_ID_ST,							// ��Ԉُ�A�C�R��
	VS_CEL_ID_PLBALL,						// �{�[��
	VS_CEL_ID_MV_MAX = VS_CEL_ID_PLBALL - VS_CEL_ID_POKE + 1	// �m�F��ʂ̍ő�
};

// �Z���A�j�����\�[�XID
enum {
	VS_ANM_ID_BALL = CLACT_ID_COMMON,	// �{�[��
	VS_ANM_ID_RESULT,					// ���s
	VS_ANM_ID_MAX = VS_ANM_ID_RESULT - CLACT_ID_COMMON + 1,	// VS��ʁA���s��ʂ̍ő�

	VS_ANM_ID_POKE = VS_ANM_ID_RESULT + 1,	// �|�P�����A�C�R��
	VS_ANM_ID_ITEM,							// �A�C�e���A�C�R��
	VS_ANM_ID_ST,							// ��Ԉُ�A�C�R��
	VS_ANM_ID_PLBALL,						// �{�[��
	VS_ANM_ID_MV_MAX = VS_ANM_ID_PLBALL - VS_ANM_ID_POKE + 1	// �m�F��ʂ̍ő�
};


#define	PCOL_N_WHITE	( GF_PRINTCOLOR_MAKE( 15, 14, 0 ) )		// �t�H���g�J���[�F��
#define	PCOL_N_BLUE		( GF_PRINTCOLOR_MAKE( 3, 4, 0 ) )		// �t�H���g�J���[�F��
#define	PCOL_N_RED		( GF_PRINTCOLOR_MAKE( 5, 6, 0 ) )		// �t�H���g�J���[�F��

#define	MULTI_SCROLL_INIT	( 16 )		// �m�F��ʁFOBJ�̏����X�N���[���l

#define	STR_LV_PX		( 0 )			// �m�F��ʁF���x���\��X�ʒu
#define	STR_LV_PY		( 5 )			// �m�F��ʁF���x���\��Y�ʒu
#define	STR_SLASH_PX	( 28 )			// �m�F��ʁFHP�̃X���b�V���\��X�ʒu
#define	STR_SLASH_PY	( 0 )			// �m�F��ʁFHP�̃X���b�V���\��Y�ʒu
#define	PRM_NICKNAME_PX	( 0 )			// �m�F��ʁF�j�b�N�l�[���\��X�ʒu
#define	PRM_NICKNAME_PY	( 0 )			// �m�F��ʁF�j�b�N�l�[���\��Y�ʒu
#define	PRM_SEX_PX		( 64 )			// �m�F��ʁF���ʕ\��X�ʒu
#define	PRM_SEX_PY		( 0 )			// �m�F��ʁF���ʕ\��Y�ʒu

#define	HPGAUGE_DOTTO_MAX	( 48 )		// �m�F��ʁFHP�Q�[�W�̃h�b�g��
#define	HPGAUGE_COL1		( 9 )		// �m�F��ʁFHP�Q�[�W�̃J���[�P�̈ʒu
#define	HPGAUGE_COL2		( 10 )		// �m�F��ʁFHP�Q�[�W�̃J���[�Q�̈ʒu
#define	PALPOS_GREEN		( HPGAUGE_COL1 )	// �m�F��ʁFHP�Q�[�W�΂̃J���[�̈ʒu
#define	PALPOS_YELLOW		( HPGAUGE_COL1+16 )	// �m�F��ʁFHP�Q�[�W���̃J���[�̈ʒu
#define	PALPOS_RED			( HPGAUGE_COL1+32 )	// �m�F��ʁFHP�Q�[�W�Ԃ̃J���[�̈ʒu


#define	START_SHAKE_X	( 8 )	// VS��ʁFX�h�ꕝ
#define	START_SHAKE_Y	( 4 )	// VS��ʁFY�h�ꕝ

#define	END_SHAKE_X	( 4 )	// ���s��ʁFX�h�ꕝ
#define	END_SHAKE_Y	( 2 )	// ���s��ʁFY�h�ꕝ

#define	SHAKE_CNT	( 24 )	// VS��ʁF�h��J�E���g

#define	SHAKE_WAIT	( 16 )	// ���s��ʁF�h�炵����̃E�F�C�g

#define	PUSH_WAIT	( 16 )	// ���s��ʁF�v���[�g�����o����̃E�F�C�g

#define	RESULT_OPEN_CNT		( 16 )	// ���s��ʁF���s�E�B���h�E�I�[�v���J�E���g
#define	RESULT_WAIT			( 32 )	// ���s��ʁF���s�E�B���h�E�I�[�v����̃E�F�C�g

#define	RESULT_END_WAIT		( 64 )	// ���s��ʁF���s�\����̃E�F�C�g
#define	RESULT_WIN_CHG_PAL	( 2 )	// ���s��ʁF�t�F�[�h�ŕύX����p���b�g�i�����j
#define	RESULT_LOSE_CHG_PAL	( 1 )	// ���s��ʁF�t�F�[�h�ŕύX����p���b�g�i�����j

#define	WL_ICON_CGX_SIZ		( 4*4 )		// �ʐM�A�C�R���̃T�C�Y

#define	VS_FOAM00_PX	( 48 )				// VS��ʁF�������g���[�i�[���P�\��X���W
#define	VS_FOAM00_PY	( 144 )				// VS��ʁF�������g���[�i�[���P�\��Y���W
#define	VS_FOAM01_PX	( 48 + 19 * 3 )		// VS��ʁF�������g���[�i�[���Q�\��X���W
#define	VS_FOAM01_PY	( 144 )				// VS��ʁF�������g���[�i�[���Q�\��Y���W
#define	VS_FOAM02_PX	( 48 )				// VS��ʁF�G���g���[�i�[���P�\��X���W
#define	VS_FOAM02_PY	( 144 )				// VS��ʁF�G���g���[�i�[���P�\��Y���W
#define	VS_FOAM03_PX	( 48 )				// VS��ʁF�G���g���[�i�[���Q�\��X���W
#define	VS_FOAM03_PY	( 144 )				// VS��ʁF�G���g���[�i�[���Q�\��Y���W

#define	VSD_BMP_PNAME_SX	( 8 )		// �t�H���gOAM��X�T�C�Y
#define	VSD_BMP_PNAME_SY	( 2 )		// �t�H���gOAM��Y�T�C�Y
#define	VSD_BMP_PNAME_SIZ	( VSD_BMP_PNAME_SX * VSD_BMP_PNAME_SY )	// �t�H���gOAM�̃L�����T�C�Y
#define	VSD_BMP_PNAME1_CGX	( 1024-VSD_BMP_PNAME_SIZ-WL_ICON_CGX_SIZ )	// �t�H���gOAM�쐬�ʒu

#define	RESULT_OBJ_PY	( 96 )		// ���sOBJ�\��Y���W
#define	RESULT_OBJ_PX1	( 48 )		// ���sOBJ�P�\��X���W
#define	RESULT_OBJ_PX2	( 208 )		// ���sOBJ�Q�\��X���W
#define	RESULT_DRAW_PX	( 128 )		// �u�Ђ��킯�vOBJ�\��X���W

#define BP_NEAR		( FX32_ONE )		// �p�[�e�B�N���̃J�����j�A�ݒ�
#define BP_FAR		( FX32_ONE * 900 )	// �p�[�e�B�N���̃J�����t�@�[�ݒ�

#define	TMP_MSG_SIZ		( 32 )		// �m�F��ʁF���b�Z�[�W�T�C�Y


//--------------------------------------------------------------------------------------------
//	SE��`
//--------------------------------------------------------------------------------------------
#define	VSD_SE_VS_PLATE_BREAK	( SEQ_SE_DP_VSDEMO01 )		// VS��ʁF�v���[�g�Փ�SE

#define	VSD_SE_VS_PLATE_OUT		( SEQ_SE_DP_VSDEMO05 )		// VS��ʁF�v���[�g�X���C�h�A�E�gSE

#define	VSD_SE_MULTI_POKE_IN	( SEQ_SE_DP_VSDEMO05 )		// �m�F��ʁF�p�[�g�i�[�X���C�h�C��SE

#define	VSD_SE_RESULT_PLATE_BREAK	( SEQ_SE_DP_GASHIN )	// ���s��ʁF�v���[�g�Փ�SE

//#define	VSD_SE_RESULT_PLATE_MOVE	( SEQ_SE_DP_VSDEMO02 )	// ���s��ʁF�v���[�g�����o��SE
#define	VSD_SE_RESULT_PLATE_MOVE	( SEQ_SE_DP_DODON )		// ���s��ʁF�v���[�g�����o��SE

//#define	VSD_SE_RESULT_PUT		( SEQ_SE_DP_VSDEMO03 )	// ���s��ʁF���s�\��SE
#define	VSD_SE_RESULT_PUT			( SEQ_SE_DP_VSDEMO06 )	// ���s��ʁF���s�\��SE

//#define	VSD_SE_RESULT_FADE		( SEQ_SE_DP_VSDEMO04 )	// ���s��ʁF�����v���[�g�t�F�[�hSE
#define	VSD_SE_RESULT_FADE			( SEQ_SE_DP_VSDEMO07 )	// ���s��ʁF�����v���[�g�t�F�[�hSE


