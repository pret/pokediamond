//******************************************************************************
/**
 * 
 * @file	slot_data.c
 * @brief	�~�j�Q�[���@�X���b�g�@�f�[�^
 * @author	kagaya
 * @data	05.07.13
 *
 */
//******************************************************************************
#include "common.h"
#include "slot_local.h"

//==============================================================================
//	define
//==============================================================================

//==============================================================================
//	struct
//==============================================================================

//==============================================================================
//	�v���g�^�C�v
//==============================================================================

//==============================================================================
//	data
//==============================================================================
//--------------------------------------------------------------
///	���[���G���z��@�e��A�G���̐���21
//	REEL_RED7			//�V
//	REEL_BLACK7			//���V
//	REEL_REPLAY			//���v���C
//	REEL_CHERRY			//�`�F���[
//	REEL_BELL			//�x��
//	REEL_SUIKA			//��
//--------------------------------------------------------------
const REEL_PATTERN DATA_SlotDataReelPattern[REEL_MAX][REEL_PT_MAX] =
{
	//����
	{
		REEL_SUIKA,			//0  (21)
		REEL_CHERRY,			//1
		REEL_BLACK7,			//2
		REEL_RED7,			//3
		REEL_REPLAY,			//4
		REEL_BELL,			//5
		REEL_SUIKA,			//6
		REEL_CHERRY,			//7
		REEL_BLACK7,			//8
		REEL_REPLAY,			//9
		REEL_BELL,			//10
		REEL_SUIKA,			//11
		REEL_CHERRY,			//12
		REEL_BLACK7,			//13
		REEL_REPLAY,			//14
		REEL_BELL,			//15
		REEL_SUIKA,			//16
		REEL_REPLAY,			//17
		REEL_RED7,			//18
		REEL_REPLAY,			//19
		REEL_BELL,		//20	(1)
	},
	//����
	{
		REEL_CHERRY,			//0 (21)
		REEL_RED7,			//1
		REEL_BLACK7,			//2
		REEL_SUIKA,			//3
		REEL_BELL,			//4
		REEL_REPLAY,			//5
		REEL_CHERRY,			//6
		REEL_RED7,			//7
		REEL_SUIKA,			//8
		REEL_BELL,			//9
		REEL_REPLAY,			//10
		REEL_CHERRY,			//11
		REEL_RED7,			//12
		REEL_SUIKA,			//13
		REEL_BELL,			//14
		REEL_REPLAY,			//15
		REEL_CHERRY,			//16
		REEL_BLACK7,			//17
		REEL_SUIKA,			//18
		REEL_BELL,			//19
		REEL_REPLAY,		//20 (1)
	},
	//�O���
	{
		REEL_BELL,			//0 (21)
		REEL_REPLAY,			//1
		REEL_BLACK7,			//2
		REEL_RED7,			//3
		REEL_REPLAY,			//4
		REEL_SUIKA,			//5
		REEL_BELL,			//6
		REEL_REPLAY,			//7
		REEL_BLACK7,			//8
		REEL_CHERRY,			//9
		REEL_SUIKA,			//10
		REEL_BELL,			//11
		REEL_REPLAY,			//12
		REEL_BLACK7,			//13
		REEL_CHERRY,			//14
		REEL_SUIKA,			//15
		REEL_BELL,			//16
		REEL_REPLAY,			//17
		REEL_RED7,			//18
		REEL_CHERRY,			//19
		REEL_SUIKA,		//20 (1)
	},
};

//--------------------------------------------------------------
///	�x�����@�q����
//--------------------------------------------------------------
const int DATA_SlotPayOutSmall[REEL_PATTERN_MAX] =
{
	100, 				//�ԂV
	100,				//���V
	0,					//���v���C
	2,					//�`�F���[
	10,					//�x��
	15,					//�X�C�J
};

//--------------------------------------------------------------
///	�x�����@�{�[�i�X��
//--------------------------------------------------------------
const int DATA_SlotPayOutBonus[REEL_PATTERN_MAX] =
{
	100, 				//�ԂV
	100,				//���V
	15,					//���v���C
	2,					//�`�F���[
	10,					//�x��
	15,					//�X�C�J
};

//--------------------------------------------------------------
///	��{���I A
//--------------------------------------------------------------
const u32 DATA_SlotBasicLotteryA[SLOT_HARD_MAX] =
{
	25,		//�ݒ�P
	25,		//�ݒ�Q
	30,		//�ݒ�R
	30,		//�ݒ�S
	35,		//�ݒ�T
	35,		//�ݒ�U
};

//--------------------------------------------------------------
///	�q�𒊑I A { �{�[�i�X�q���m��, �q���m�� }
//--------------------------------------------------------------
const LT_SMALLDATA DATA_SlotSmallLotteryA[SLOT_HARD_MAX] =
{
	{	//�ݒ�P
		{ 1, 4 },				//�`�F���[�{�[�i�X�A�`�F���[
		{ 2, 13 },				//�X�C�J�{�[�i�X�A�X�C�J
		{ 1, 39 },				//�x���{�[�i�X�A�x��
		{ 1, 39 },				//���v���C�{�[�i�X�A���v���C
	},
	{	//�ݒ�Q
		{ 1, 4 },				//�`�F���[�{�[�i�X�A�`�F���[
		{ 2, 13 },				//�X�C�J�{�[�i�X�A�X�C�J
		{ 1, 39 },				//�x���{�[�i�X�A�x��
		{ 1, 39 },				//���v���C�{�[�i�X�A���v���C
	},
	{	//�ݒ�R
		{ 2, 3 },				//�`�F���[�{�[�i�X�A�`�F���[
		{ 4, 11 },				//�X�C�J�{�[�i�X�A�X�C�J
		{ 2, 38 },				//�x���{�[�i�X�A�x��
		{ 2, 38 },				//���v���C�{�[�i�X�A���v���C
	},
	{	//�ݒ�S
		{ 3, 2 },				//�`�F���[�{�[�i�X�A�`�F���[
		{ 4, 11 },				//�X�C�J�{�[�i�X�A�X�C�J
		{ 2, 38 },				//�x���{�[�i�X�A�x��
		{ 2, 38 },				//���v���C�{�[�i�X�A���v���C
	},
	{	//�ݒ�T
		{ 4, 1 },				//�`�F���[�{�[�i�X�A�`�F���[
		{ 6, 9 },				//�X�C�J�{�[�i�X�A�X�C�J
		{ 3, 37 },				//�x���{�[�i�X�A�x��
		{ 3, 37 },				//���v���C�{�[�i�X�A���v���C
	},
	{	//�ݒ�U
		{ 4, 1 },				//�`�F���[�{�[�i�X�A�`�F���[
		{ 6, 9 },				//�X�C�J�{�[�i�X�A�X�C�J
		{ 3, 37 },				//�x���{�[�i�X�A�x��
		{ 3, 37 },				//���v���C�{�[�i�X�A���v���C
	},
};

//--------------------------------------------------------------
///	��{���IA�̎q�𐬗����̃i�r�����@�ʏ�i�r����������m��
//--------------------------------------------------------------
const u32 DATA_LotteryNavi[SLOT_HARD_MAX] =
{
	80,	//�ݒ�P
	80,	//�ݒ�Q
	80,	//�ݒ�R
	80,	//�ݒ�S
	80,	//�ݒ�T
	70,	//�ݒ�U
};

//--------------------------------------------------------------
///	�p��������U�� {�m��,�q�b�g�����p����,�p�������}
//--------------------------------------------------------------
const LT_CONT_BONUS DATA_LotteryContinueBonus[SLOT_HARD_MAX][CONT_BONUS_TYPE_MAX] =
{
	{	//�ݒ�P
		{ 5, CONT_GGG_50, CONT_BONUS_50 },
		{ 10, CONT_777_70, CONT_BONUS_70 },
		{ 10, CONT_GGG_90, CONT_BONUS_90 },
		{ 10, CONT_777_90, CONT_BONUS_90 },
		{ 15, CONT_GGG_70, CONT_BONUS_70 },
		{ 50, CONT_777_50, CONT_BONUS_50 },
	},
	{	//�ݒ�Q
		{ 5, CONT_GGG_50, CONT_BONUS_50 },
		{ 10, CONT_777_70, CONT_BONUS_70 },
		{ 10, CONT_GGG_90, CONT_BONUS_90 },
		{ 10, CONT_777_90, CONT_BONUS_90 },
		{ 15, CONT_GGG_70, CONT_BONUS_70 },
		{ 50, CONT_777_50, CONT_BONUS_50 },
	},
	{	//�ݒ�R
		{ 5, CONT_GGG_50, CONT_BONUS_50 },
		{ 15, CONT_777_70, CONT_BONUS_70 },
		{ 10, CONT_GGG_90, CONT_BONUS_90 },
		{ 15, CONT_777_90, CONT_BONUS_90 },
		{ 15, CONT_GGG_70, CONT_BONUS_70 },
		{ 40, CONT_777_50, CONT_BONUS_50 },
	},
	{	//�ݒ�S
		{ 5, CONT_GGG_50, CONT_BONUS_50 },
		{ 15, CONT_777_70, CONT_BONUS_70 },
		{ 15, CONT_GGG_90, CONT_BONUS_90 },
		{ 15, CONT_777_90, CONT_BONUS_90 },
		{ 10, CONT_GGG_70, CONT_BONUS_70 },
		{ 40, CONT_777_50, CONT_BONUS_50 },
	},
	{	//�ݒ�T
		{ 5, CONT_GGG_50, CONT_BONUS_50 },
		{ 20, CONT_777_70, CONT_BONUS_70 },
		{ 15, CONT_GGG_90, CONT_BONUS_90 },
		{ 20, CONT_777_90, CONT_BONUS_90 },
		{ 10, CONT_GGG_70, CONT_BONUS_70 },
		{ 30, CONT_777_50, CONT_BONUS_50 },
	},
	{	//�ݒ�U
		{ 5, CONT_GGG_50, CONT_BONUS_50 },
		{ 20, CONT_777_70, CONT_BONUS_70 },
		{ 15, CONT_GGG_90, CONT_BONUS_90 },
		{ 20, CONT_777_90, CONT_BONUS_90 },
		{ 10, CONT_GGG_70, CONT_BONUS_70 },
		{ 30, CONT_777_50, CONT_BONUS_50 },
	},
};

//--------------------------------------------------------------
///	�p�������->���p����
//--------------------------------------------------------------
const u32 DATA_ContinueBonusTypeParam[CONT_BONUS_TYPE_MAX] =
{
	50,		//CONT_777_50
	70,		//CONT_777_70
	90,		//CONT_777_90
	50,		//CONT_GGG_50
	70,		//CONT_GGG_70
	90,		//CONT_GGG_90
};

//--------------------------------------------------------------
///	�o��|�P�����I���@{ �m��, �o��|�P���� }
//	PIP_RARE	���A�s�b�s
//	PIP_NORMAL	�s�b�s�@
//	PIP_META	���^��
//--------------------------------------------------------------
const LT_POKE_ENTRY DATA_LotteryPokeEntry[SLOT_HARD_MAX][CONT_BONUS_MAX][PIP_MAX] =
{
	{	//�ݒ�P
		{	//�p�����T�O��
			{ 5, PIP_RARE },{ 20, PIP_NORMAL },{ 75, PIP_META },
		},
		{	//�p�����V�O��
			{ 20, PIP_RARE },{ 60, PIP_NORMAL },{ 20, PIP_META },
		},
		{	//�p�����X�O��
			{ 75, PIP_RARE },{ 20, PIP_NORMAL },{ 5, PIP_META },
		},
	},
	{	//�ݒ�Q
		{	//�p�����T�O��
			{ 5, PIP_RARE },{ 20, PIP_NORMAL },{ 75, PIP_META },
		},
		{	//�p�����V�O��
			{ 20, PIP_RARE },{ 60, PIP_NORMAL },{ 20, PIP_META },
		},
		{	//�p�����X�O��
			{ 75, PIP_RARE },{ 20, PIP_NORMAL },{ 5, PIP_META },
		},
	},
	{	//�ݒ�R
		{	//�p�����T�O��
			{ 5, PIP_RARE },{ 20, PIP_NORMAL },{ 75, PIP_META },
		},
		{	//�p�����V�O��
			{ 20, PIP_RARE },{ 60, PIP_NORMAL },{ 20, PIP_META },
		},
		{	//�p�����X�O��
			{ 75, PIP_RARE },{ 20, PIP_NORMAL },{ 5, PIP_META },
		},
	},
	{	//�ݒ�S
		{	//�p�����T�O��
			{ 5, PIP_RARE },{ 20, PIP_NORMAL },{ 75, PIP_META },
		},
		{	//�p�����V�O��
			{ 20, PIP_RARE },{ 60, PIP_NORMAL },{ 20, PIP_META },
		},
		{	//�p�����X�O��
			{ 75, PIP_RARE },{ 20, PIP_NORMAL },{ 5, PIP_META },
		},
	},
	{	//�ݒ�T
		{	//�p�����T�O��
			{ 5, PIP_RARE },{ 20, PIP_NORMAL },{ 75, PIP_META },
		},
		{	//�p�����V�O��
			{ 20, PIP_RARE },{ 60, PIP_NORMAL },{ 20, PIP_META },
		},
		{	//�p�����X�O��
			{ 75, PIP_RARE },{ 20, PIP_NORMAL },{ 5, PIP_META },
		},
	},
	{	//�ݒ�U
		{	//�p�����T�O��
			{ 5, PIP_RARE },{ 20, PIP_NORMAL },{ 75, PIP_META },
		},
		{	//�p�����V�O��
			{ 20, PIP_RARE },{ 60, PIP_NORMAL },{ 20, PIP_META },
		},
		{	//�p�����X�O��
			{ 75, PIP_RARE },{ 20, PIP_NORMAL },{ 5, PIP_META },
		},
	},
};

//--------------------------------------------------------------
///	��{���I B
//--------------------------------------------------------------
const u32 DATA_SlotBasicLotteryB[SLOT_HARD_MAX] =
{
	25,		//�ݒ�P
	25,		//�ݒ�Q
	30,		//�ݒ�R
	30,		//�ݒ�S
	35,		//�ݒ�T
	35,		//�ݒ�U
};

//--------------------------------------------------------------
///	�q�𒊑I B
//--------------------------------------------------------------
const u32 DATA_SlotSmallLotteryB[SLOT_HARD_MAX][4] =
{
	{	//�ݒ�P
		5,		//�`�F���[
		15,		//�X�C�J
		30,		//�x��
		50,		//���v���C
	},
	{	//�ݒ�Q
		5,		//�`�F���[
		15,		//�X�C�J
		30,		//�x��
		50,		//���v���C
	},
	{	//�ݒ�R
		5,		//�`�F���[
		15,		//�X�C�J
		30,		//�x��
		50,		//���v���C
	},
	{	//�ݒ�S
		5,		//�`�F���[
		15,		//�X�C�J
		30,		//�x��
		50,		//���v���C
	},
	{	//�ݒ�T
		5,		//�`�F���[
		15,		//�X�C�J
		30,		//�x��
		50,		//���v���C
	},
	{	//�ݒ�U
		5,		//�`�F���[
		15,		//�X�C�J
		30,		//�x��
		50,		//���v���C
	},
};

//--------------------------------------------------------------
///	�����t���b�V�����I
//--------------------------------------------------------------
const u32 DATA_LotteryMoonLight[SLOT_HARD_MAX] =
{
	1,	//�ݒ�P
	1,	//�ݒ�Q
	3,	//�ݒ�R
	3,	//�ݒ�S
	5,	//�ݒ�T
	5,	//�ݒ�U
};

//--------------------------------------------------------------
///	�Ԃ������I
//--------------------------------------------------------------
const u32 DATA_LotteryMoonLightRed[SLOT_HARD_MAX] =
{
	3,	//�ݒ�P
	3,	//�ݒ�Q
	5,	//�ݒ�R
	5,	//�ݒ�S
	7,	//�ݒ�T
	7,	//�ݒ�U
};

//--------------------------------------------------------------
///	�p�����_�E�����I { 10%�_�E��, 5%�_�E�� }
//--------------------------------------------------------------
const u32 DATA_LotteryBonusContinue[SLOT_HARD_MAX][CONT_BONUS_DOWN_MAX] =
{
	{ 25, 20 },	//�ݒ�P
	{ 20, 15 },	//�ݒ�Q
	{ 15, 15 },	//�ݒ�R
	{ 15, 15 },	//�ݒ�S
	{ 10, 15 },	//�ݒ�T
	{ 5, 10 },	//�ݒ�U
};

//--------------------------------------------------------------
///	�I�����p�����o {�ΏۂƂȂ�p����, �{�[���߂�, �ʏ�, �A���R�[�� },
//--------------------------------------------------------------
const LT_CONTBONUSEND DATA_LotteryContinueBonusEnd[SLOT_HARD_MAX][CONT_BONUSEND_NUM_MAX] =
{
	{	//�ݒ�P
		{CONT_BONUSEND_100_75, 10, 10, 80 },	//�`75%
		{CONT_BONUSEND_65, 10, 30, 60 },		//�`65%
		{CONT_BONUSEND_55, 10, 40, 50 },		//�`55%
		{CONT_BONUSEND_45, 20, 50, 30 },		//�`45%
		{CONT_BONUSEND_35, 30, 50, 20 },		//�`35%
		{CONT_BONUSEND_25, 50, 40, 10 },		//�`25%
		{CONT_BONUSEND_15, 60, 30, 10 },		//�`15%
		{CONT_BONUSEND_5, 80, 10, 10 },			//�`5%
		{CONT_BONUSEND_0, 90, 5, 5 },			//�`0% �O�ׁ̈@�{�������ɂ͗��Ȃ�
	},
	{	//�ݒ�Q
		{CONT_BONUSEND_100_75, 10, 10, 80 },	//�`75%
		{CONT_BONUSEND_65, 10, 30, 60 },		//�`65%
		{CONT_BONUSEND_55, 10, 40, 50 },		//�`55%
		{CONT_BONUSEND_45, 20, 50, 30 },		//�`45%
		{CONT_BONUSEND_35, 30, 50, 20 },		//�`35%
		{CONT_BONUSEND_25, 50, 40, 10 },		//�`25%
		{CONT_BONUSEND_15, 60, 30, 10 },		//�`15%
		{CONT_BONUSEND_5, 80, 10, 10 },			//�`5%
		{CONT_BONUSEND_0, 90, 5, 5 },			//�`0%
	},
	{	//�ݒ�R
		{CONT_BONUSEND_100_75, 10, 10, 80 },	//�`75%
		{CONT_BONUSEND_65, 10, 30, 60 },		//�`65%
		{CONT_BONUSEND_55, 10, 40, 50 },		//�`55%
		{CONT_BONUSEND_45, 20, 50, 30 },		//�`45%
		{CONT_BONUSEND_35, 30, 50, 20 },		//�`35%
		{CONT_BONUSEND_25, 50, 40, 10 },		//�`25%
		{CONT_BONUSEND_15, 60, 30, 10 },		//�`15%
		{CONT_BONUSEND_5, 80, 10, 10 },			//�`5%
		{CONT_BONUSEND_0, 90, 5, 5 },			//�`0%
	},
	{	//�ݒ�S
		{CONT_BONUSEND_100_75, 10, 10, 80 },	//�`75%
		{CONT_BONUSEND_65, 10, 30, 60 },		//�`65%
		{CONT_BONUSEND_55, 10, 40, 50 },		//�`55%
		{CONT_BONUSEND_45, 20, 50, 30 },		//�`45%
		{CONT_BONUSEND_35, 30, 50, 20 },		//�`35%
		{CONT_BONUSEND_25, 50, 40, 10 },		//�`25%
		{CONT_BONUSEND_15, 60, 30, 10 },		//�`15%
		{CONT_BONUSEND_5, 80, 10, 10 },			//�`5%
		{CONT_BONUSEND_0, 90, 5, 5 },			//�`0%
	},
	{	//�ݒ�T
		{CONT_BONUSEND_100_75, 10, 10, 80 },	//�`75%
		{CONT_BONUSEND_65, 10, 30, 60 },		//�`65%
		{CONT_BONUSEND_55, 10, 40, 50 },		//�`55%
		{CONT_BONUSEND_45, 20, 50, 30 },		//�`45%
		{CONT_BONUSEND_35, 30, 50, 20 },		//�`35%
		{CONT_BONUSEND_25, 50, 40, 10 },		//�`25%
		{CONT_BONUSEND_15, 60, 30, 10 },		//�`15%
		{CONT_BONUSEND_5, 80, 10, 10 },			//�`5%
		{CONT_BONUSEND_0, 90, 5, 5 },			//�`0%
	},
	{	//�ݒ�U
		{CONT_BONUSEND_100_75, 10, 10, 80 },	//�`75%
		{CONT_BONUSEND_65, 10, 30, 60 },		//�`65%
		{CONT_BONUSEND_55, 10, 40, 50 },		//�`55%
		{CONT_BONUSEND_45, 20, 50, 30 },		//�`45%
		{CONT_BONUSEND_35, 30, 50, 20 },		//�`35%
		{CONT_BONUSEND_25, 50, 40, 10 },		//�`25%
		{CONT_BONUSEND_15, 60, 30, 10 },		//�`15%
		{CONT_BONUSEND_5, 80, 10, 10 },			//�`5%
		{CONT_BONUSEND_0, 90, 5, 5 },			//�`0%
	},
};
