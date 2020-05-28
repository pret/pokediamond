//==============================================================================
/**
 * @file	gauge.c
 * @brief	�퓬��ʁFHP�Q�[�W
 * @author	matsuda
 * @date	2005.09.27(��)
 */
//==============================================================================
#include "common.h"
#include "gauge.h"
#include "graphic\batt_obj_def.h"
#include "system/arc_tool.h"
#include "battle/fight_tool.h"
#include "system/fontproc.h"
#include "application/app_tool.h"
#include "system/pm_str.h"
#include "system/numfont.h"
#include "battle/battle_tcb_pri.h"

#include "system/msgdata_util.h"
#include "system/wordset.h"
#include "msgdata/msg_fightmsg_dp.h"

#include "battle/battle_id.h"


//==============================================================================
//	�萔��`
//==============================================================================

//--------------------------------------------------------------
//	
//--------------------------------------------------------------
enum{
	GAUGE_REQ_HP,		///<HP�o�[�������݃��N�G�X�g
	GAUGE_REQ_EXP,		///<EXP�o�[�������݃��N�G�X�g
};

///�Q�[�W�A�N�^�[�\�t�g�v���C�I���e�B
enum{
	SOFTPRI_START = 10,
	
	SOFTPRI_NAME_AA,	///<AA�p�|�P������
	SOFTPRI_NAME_BB,
	SOFTPRI_NAME_A,
	SOFTPRI_NAME_B,
	SOFTPRI_NAME_C,
	SOFTPRI_NAME_D,

	SOFTPRI_ARROW_AA,	///<AA�p�Q�[�W���
	SOFTPRI_ARROW_BB,	///<BB�p�Q�[�W���
	SOFTPRI_ARROW_B,
	SOFTPRI_ARROW_C,
	SOFTPRI_ARROW_D,
	SOFTPRI_ARROW_A,

	SOFTPRI_GAUGE_AA,	///<AA�p�Q�[�W�{��
	SOFTPRI_GAUGE_BB,	///<BB�p�Q�[�W�{��
	SOFTPRI_GAUGE_B,
	SOFTPRI_GAUGE_C,
	SOFTPRI_GAUGE_D,
	SOFTPRI_GAUGE_A,
};

///���̃Q�[�W�{�̂̒��S����̕\���I�t�Z�b�g���WY
#define ARROW_OFFSET_Y		(0)

///�Q�[�W����ʊO�Ɏ����Ă������̃I�t�Z�b�gX
#define GAUGE_SCROLL_OUT_OFFSET_X		(160)
///�Q�[�W����ʊO�Ɏ����Ă������̃I�t�Z�b�gY
#define GAUGE_SCROLL_OUT_OFFSET_Y		(0)
///�Q�[�W�X�N���[�����̑��xX
#define GAUGE_SCROLL_SP_X		(24)	//(12)

///�Q�[�WSin�J�[�u�̕b���Z�l
#define GAUGE_SIN_SEC_ADD		(20)
///�Q�[�WSin�J�[�u�̂ӂ蕝Y(fx32)
#define GAUGE_SIN_FURIHABA_Y	(0x1800)


//==============================================================================
//	���I�t�Z�b�g���W
//==============================================================================
///���̃Q�[�W�{�̂̒��S����̕\���I�t�Z�b�g���WX
ALIGN4 static const s8 ArrowOffsetPosX[] = {
	72-8,		//AA
	0,			//BB
	72,			//A
	0,			//B
	72-8,		//C
	0,			//D
};

//==============================================================================
//	�p�[�c�`��
//==============================================================================
typedef struct{
	u16 pos;		///�]���ʒu(�o�C�g�I�t�Z�b�g)
	u16 size;		///�]���T�C�Y
}PARTS_TRANS_PARAM;

//--------------------------------------------------------------
//	���O
//--------------------------------------------------------------
///���O��X�T�C�Y(�L�����P��)�B�@��*.NCE�t�@�C���Őݒ肵�Ă��鉡�̃L���������L��
#define NAME_SIZE_X		(8)
///���O��Y�T�C�Y(�L�����P��)�B�@��*.NCE�t�@�C���Őݒ肵�Ă���c�̃L���������L��
#define NAME_SIZE_Y		(2)
///���OCGX�I�t�Z�b�g
#define NAME_CHAR_OFFSET	(0)
///���O�L�����N�^�[�̃o�C�g�T�C�Y
#define NAME_BYTE_SIZE		(NAME_SIZE_X * NAME_SIZE_Y * 0x20)

//���O�`��ʒu
static const PARTS_TRANS_PARAM NameTrans[][4] = {
	{//GAUGE_TYPE_AA
		{0x12 * 0x20, 6 * 0x20},		///<1����OAM�F��i
		{0x1a * 0x20, 6 * 0x20},		///<1����OAM�F���i
		{0x50 * 0x20, 2 * 0x20},		///<2����OAM�F��i
		{0x58 * 0x20, 2 * 0x20},		///<2����OAM�F���i
	},
	{//GAUGE_TYPE_BB
		{0x11 * 0x20, 7 * 0x20},		///<1����OAM�F��i
		{0x19 * 0x20, 7 * 0x20},		///<1����OAM�F���i
		{0x50 * 0x20, 1 * 0x20},		///<2����OAM�F��i
		{0x58 * 0x20, 1 * 0x20},		///<2����OAM�F���i
	},
	{//GAUGE_TYPE_A
		{0x12 * 0x20, 6 * 0x20},		///<1����OAM�F��i
		{0x1a * 0x20, 6 * 0x20},		///<1����OAM�F���i
		{0x50 * 0x20, 2 * 0x20},		///<2����OAM�F��i
		{0x58 * 0x20, 2 * 0x20},		///<2����OAM�F���i
	},
	{//GAUGE_TYPE_B
		{0x11 * 0x20, 7 * 0x20},		///<1����OAM�F��i
		{0x19 * 0x20, 7 * 0x20},		///<1����OAM�F���i
		{0x50 * 0x20, 1 * 0x20},		///<2����OAM�F��i
		{0x58 * 0x20, 1 * 0x20},		///<2����OAM�F���i
	},
	{//GAUGE_TYPE_C
		{0x12 * 0x20, 6 * 0x20},		///<1����OAM�F��i
		{0x1a * 0x20, 6 * 0x20},		///<1����OAM�F���i
		{0x50 * 0x20, 2 * 0x20},		///<2����OAM�F��i
		{0x58 * 0x20, 2 * 0x20},		///<2����OAM�F���i
	},
	{//GAUGE_TYPE_D
		{0x11 * 0x20, 7 * 0x20},		///<1����OAM�F��i
		{0x19 * 0x20, 7 * 0x20},		///<1����OAM�F���i
		{0x50 * 0x20, 1 * 0x20},		///<2����OAM�F��i
		{0x58 * 0x20, 1 * 0x20},		///<2����OAM�F���i
	},
};

///���O�`��ʒu�̔w�i�F�ԍ�
#define NAME_BACK_COLOR		(0xf)
///���O�̕����F
#define NAME_FONT_COLOR		(GF_PRINTCOLOR_MAKE(0xe, 2, NAME_BACK_COLOR))

//--------------------------------------------------------------
//	���x������
//--------------------------------------------------------------
//���x�������`��ʒu
static const PARTS_TRANS_PARAM LvFontTrans[][2] = {
	{//GAUGE_TYPE_AA
		{0x52 * 0x20, 2 * 0x20},		///<1����OAM
		{0x5a * 0x20, 2 * 0x20},		///<2����OAM
	},
	{//GAUGE_TYPE_BB
		{0x51 * 0x20, 2 * 0x20},		///<1����OAM
		{0x59 * 0x20, 2 * 0x20},		///<2����OAM
	},
	{//GAUGE_TYPE_A
		{0x52 * 0x20, 2 * 0x20},		///<1����OAM
		{0x5a * 0x20, 2 * 0x20},		///<2����OAM
	},
	{//GAUGE_TYPE_B
		{0x51 * 0x20, 2 * 0x20},		///<1����OAM
		{0x59 * 0x20, 2 * 0x20},		///<2����OAM
	},
	{//GAUGE_TYPE_C
		{0x52 * 0x20, 2 * 0x20},		///<1����OAM
		{0x5a * 0x20, 2 * 0x20},		///<2����OAM
	},
	{//GAUGE_TYPE_D
		{0x51 * 0x20, 2 * 0x20},		///<1����OAM
		{0x59 * 0x20, 2 * 0x20},		///<2����OAM
	},
};

//--------------------------------------------------------------
//	���x��
//--------------------------------------------------------------
//���x���`��ʒu
static const PARTS_TRANS_PARAM LvTrans[][2] = {
	{//GAUGE_TYPE_AA
		{0x54 * 0x20, 3 * 0x20},		///<1����OAM
		{0x5c * 0x20, 3 * 0x20},		///<2����OAM
	},
	{//GAUGE_TYPE_BB
		{0x53 * 0x20, 3 * 0x20},		///<1����OAM
		{0x5b * 0x20, 3 * 0x20},		///<2����OAM
	},
	{//GAUGE_TYPE_A
		{0x54 * 0x20, 3 * 0x20},		///<1����OAM
		{0x5c * 0x20, 3 * 0x20},		///<2����OAM
	},
	{//GAUGE_TYPE_B
		{0x53 * 0x20, 3 * 0x20},		///<1����OAM
		{0x5b * 0x20, 3 * 0x20},		///<2����OAM
	},
	{//GAUGE_TYPE_C
		{0x54 * 0x20, 3 * 0x20},		///<1����OAM
		{0x5c * 0x20, 3 * 0x20},		///<2����OAM
	},
	{//GAUGE_TYPE_D
		{0x53 * 0x20, 3 * 0x20},		///<1����OAM
		{0x5b * 0x20, 3 * 0x20},		///<2����OAM
	},
};

///���x���`��ʒu�̔w�i�F�ԍ�
#define LEVEL_BACK_COLOR		(NAME_BACK_COLOR)
///���x���̕����F
#define LEVEL_FONT_COLOR		(NAME_FONT_COLOR)

//--------------------------------------------------------------
//	����HP
//--------------------------------------------------------------
//����HP�`��ʒu
static const PARTS_TRANS_PARAM HPTrans[][2] = {
	{//GAUGE_TYPE_AA
		{0x68 * 0x20, 3 * 0x20},		///<2����OAM
		{0, 0 * 0x20},					///<2����OAM
	},
	{//GAUGE_TYPE_BB
		{0x31 * 0x20, 3 * 0x20},			///<1����OAM
		{0, 0 * 0x20},					///<2����OAM
	},
	{//GAUGE_TYPE_A
		{0, 0 * 0x20},		///<1����OAM
		{0x60 * 0x20, 3 * 0x20},		///<2����OAM
	},
	{//GAUGE_TYPE_B
		{0x31 * 0x20, 3 * 0x20},			///<1����OAM
		{0, 0 * 0x20},					///<2����OAM
	},
	{//GAUGE_TYPE_C
		{0 * 0x20, 0 * 0x20},		///<1����OAM
		{0x60 * 0x20, 3 * 0x20},		///<2����OAM
	},
	{//GAUGE_TYPE_D
		{0x31 * 0x20, 3 * 0x20},			///<1����OAM
		{0, 0 * 0x20},					///<2����OAM
	},
};

///����HP�`��ʒu�̔w�i�F�ԍ�
#define HP_BACK_COLOR		(0xf)
///����HP�̕����F
#define HP_FONT_COLOR		(GF_PRINTCOLOR_MAKE(0xe, 2, HP_BACK_COLOR))

//--------------------------------------------------------------
//	�ő�HP
//--------------------------------------------------------------
//�ő�HP�`��ʒu
static const PARTS_TRANS_PARAM HPMaxTrans[] = {
	//GAUGE_TYPE_AA
	{0x6c * 0x20, 3 * 0x20},		///<2����OAM
	//GAUGE_TYPE_BB
	{0x35 * 0x20, 3 * 0x20},		///<2����OAM
	//GAUGE_TYPE_A
	{0x64 * 0x20, 3 * 0x20},		///<2����OAM
	//GAUGE_TYPE_B
	{0x35 * 0x20, 3 * 0x20},		///<2����OAM
	//GAUGE_TYPE_C
	{0x64 * 0x20, 3 * 0x20},		///<2����OAM
	//GAUGE_TYPE_D
	{0x35 * 0x20, 3 * 0x20},		///<2����OAM
};

///�ő�HP�`��ʒu�̔w�i�F�ԍ�
#define HPMAX_BACK_COLOR		(HP_BACK_COLOR)
///�ő�HP�̕����F
#define HPMAX_FONT_COLOR		(HP_FONT_COLOR)

//--------------------------------------------------------------
//	�f�o�b�O���l
//--------------------------------------------------------------
#ifdef PM_DEBUG
#define DEBUG_NUM_KETA_MAX		(8)
static const PARTS_TRANS_PARAM DebugNumTrans[] = {
	//GAUGE_TYPE_AA
	{0x78 * 0x20, DEBUG_NUM_KETA_MAX * 0x20},		///<2����OAM
	//GAUGE_TYPE_BB
	{0x78 * 0x20, DEBUG_NUM_KETA_MAX * 0x20},		///<2����OAM
	//GAUGE_TYPE_A
	{0x78 * 0x20, DEBUG_NUM_KETA_MAX * 0x20},		///<2����OAM
	//GAUGE_TYPE_B
	{0x78 * 0x20, DEBUG_NUM_KETA_MAX * 0x20},		///<2����OAM
	//GAUGE_TYPE_C
	{0x78 * 0x20, DEBUG_NUM_KETA_MAX * 0x20},		///<2����OAM
	//GAUGE_TYPE_D
	{0x78 * 0x20, DEBUG_NUM_KETA_MAX * 0x20},		///<2����OAM
};
#endif

//--------------------------------------------------------------
//	HP�o�[
//--------------------------------------------------------------
//HP�o�[�`��ʒu
static const PARTS_TRANS_PARAM HPBarTrans[][2] = {
	{//GAUGE_TYPE_AA
		{0x27 * 0x20, 0 * 0x20},		///<1����OAM
		{0x60 * 0x20, 6 * 0x20},		///<2����OAM
	},
	{//GAUGE_TYPE_BB
		{0x27 * 0x20, 1 * 0x20},		///<1����OAM
		{0x60 * 0x20, 5 * 0x20},		///<2����OAM
	},
	{//GAUGE_TYPE_A
		{0x27 * 0x20, 0 * 0x20},		///<1����OAM
		{0x60 * 0x20, 6 * 0x20},		///<2����OAM
	},
	{//GAUGE_TYPE_B
		{0x27 * 0x20, 1 * 0x20},		///<1����OAM
		{0x60 * 0x20, 5 * 0x20},		///<2����OAM
	},
	{//GAUGE_TYPE_C
		{0x27 * 0x20, 0 * 0x20},		///<1����OAM
		{0x60 * 0x20, 6 * 0x20},		///<2����OAM
	},
	{//GAUGE_TYPE_D
		{0x27 * 0x20, 1 * 0x20},		///<1����OAM
		{0x60 * 0x20, 5 * 0x20},		///<2����OAM
	},
};

///HP�o�[�`��ʒu�̔w�i�F�ԍ�
#define HPBAR_BACK_COLOR		(HP_BACK_COLOR)
///HP�o�[�̕����F
#define HPBAR_FONT_COLOR		(HP_FONT_COLOR)

//--------------------------------------------------------------
//	�o���l�o�[
//--------------------------------------------------------------
//EXP�o�[�`��ʒu(�V���O���E�_�u���E�����E�G����)
enum{
	EXPBAR_FAST_HIGH = 0x34 * 0x20,		///<EXP�o�[�F1���ڂ�OAM�̕`��J�n�ʒu
	EXPBAR_SECOND_HIGH = 0x70 * 0x20,	///<EXP�o�[�F2���ڂ�OAM�̕`��J�n�ʒu
	
	EXPBAR_NEXT_OAM = 4,		///<1���ڂ�OAM������EXP�o�[�̃L������
};

//--------------------------------------------------------------
//	����
//--------------------------------------------------------------
//���ʓ]���ʒu
static const PARTS_TRANS_PARAM SexTrans[][2] = {
	{//GAUGE_TYPE_AA
		{0x52 * 0x20, 1 * 0x20},		///<��i
		{0x5a * 0x20, 1 * 0x20},		///<���i
	},
	{//GAUGE_TYPE_BB
		{0x50 * 0x20, 1 * 0x20},		///<��i
		{0x58 * 0x20, 1 * 0x20},		///<���i
	},
	{//GAUGE_TYPE_A
		{0x51 * 0x20, 1 * 0x20},		///<��i
		{0x59 * 0x20, 1 * 0x20},		///<���i
	},
	{//GAUGE_TYPE_B
		{0x51 * 0x20, 1 * 0x20},		///<��i
		{0x59 * 0x20, 1 * 0x20},		///<���i
	},
	{//GAUGE_TYPE_C
		{0x52 * 0x20, 1 * 0x20},		///<��i
		{0x5a * 0x20, 1 * 0x20},		///<���i
	},
	{//GAUGE_TYPE_D
		{0x50 * 0x20, 1 * 0x20},		///<��i
		{0x58 * 0x20, 1 * 0x20},		///<���i
	},
};

//--------------------------------------------------------------
//	�Q�b�g�ς݃}�[�N
//--------------------------------------------------------------
//�Q�b�g�ς݃}�[�N�]���ʒu
static const PARTS_TRANS_PARAM GetBallTrans[] = {
	//GAUGE_TYPE_AA
	{0x22 * 0x20, 1 * 0x20},
	//GAUGE_TYPE_BB
	{0x21 * 0x20, 1 * 0x20},
	//GAUGE_TYPE_A
	{0x22 * 0x20, 1 * 0x20},
	//GAUGE_TYPE_B
	{0x21 * 0x20, 1 * 0x20},
	//GAUGE_TYPE_C
	{0x22 * 0x20, 1 * 0x20},
	//GAUGE_TYPE_D
	{0x21 * 0x20, 1 * 0x20},
};

//--------------------------------------------------------------
//	��Ԉُ�
//--------------------------------------------------------------
//��Ԉُ�]���ʒu
static const PARTS_TRANS_PARAM StatusTrans[] = {
	//GAUGE_TYPE_AA
	{0x23 * 0x20, 3 * 0x20},
	//GAUGE_TYPE_BB
	{0x22 * 0x20, 3 * 0x20},
	//GAUGE_TYPE_A
	{0x23 * 0x20, 3 * 0x20},
	//GAUGE_TYPE_B
	{0x22 * 0x20, 3 * 0x20},
	//GAUGE_TYPE_C
	{0x23 * 0x20, 3 * 0x20},
	//GAUGE_TYPE_D
	{0x22 * 0x20, 3 * 0x20},
};


//--------------------------------------------------------------
//	�T�t�@���{�[��
//--------------------------------------------------------------
///�u�T�t�@���{�[���v��X�T�C�Y(�L�����P��)�B�@��*.NCE�t�@�C���Őݒ肵�Ă��鉡�̃L���������L��
#define SAFARIBALL_SIZE_X		(13)
///�u�T�t�@���{�[���v��Y�T�C�Y(�L�����P��)�B�@��*.NCE�t�@�C���Őݒ肵�Ă���c�̃L���������L��
#define SAFARIBALL_SIZE_Y		(2)
///�u�T�t�@���{�[���vCGX�I�t�Z�b�g
#define SAFARIBALL_CHAR_OFFSET	(0)
///�u�T�t�@���{�[���v�L�����N�^�[�̃o�C�g�T�C�Y
#define SAFARIBALL_BYTE_SIZE		(SAFARIBALL_SIZE_X * SAFARIBALL_SIZE_Y * 0x20)

//�u�T�t�@���{�[���v�`��ʒu
static const PARTS_TRANS_PARAM SafariballTrans[4] = {
	{0x12 * 0x20, 6 * 0x20},		///<1����OAM�F��i
	{0x1a * 0x20, 6 * 0x20},		///<1����OAM�F���i
	{0x50 * 0x20, 7 * 0x20},		///<2����OAM�F��i
	{0x58 * 0x20, 7 * 0x20},		///<2����OAM�F���i
};

///�u�T�t�@���{�[���v�`��ʒu�̔w�i�F�ԍ�
#define SAFARIBALL_BACK_COLOR		(0xf)
///�u�T�t�@���{�[���v�̕����F
#define SAFARIBALL_FONT_COLOR		(GF_PRINTCOLOR_MAKE(0xe, 2, SAFARIBALL_BACK_COLOR))


//--------------------------------------------------------------
//	�̂���@������
//--------------------------------------------------------------
///�u�̂���@�������v��X�T�C�Y(�L�����P��)�B�@��*.NCE�t�@�C���Őݒ肵�Ă��鉡�̃L���������L��
#define NOKORI_SIZE_X		(13)
///�u�̂���@�������v��Y�T�C�Y(�L�����P��)�B�@��*.NCE�t�@�C���Őݒ肵�Ă���c�̃L���������L��
#define NOKORI_SIZE_Y		(2)
///�u�̂���@�������vCGX�I�t�Z�b�g
#define NOKORI_CHAR_OFFSET	(0)
///�u�̂���@�������v�L�����N�^�[�̃o�C�g�T�C�Y
#define NOKORI_BYTE_SIZE		(NOKORI_SIZE_X * NOKORI_SIZE_Y * 0x20)

//�u�̂���@�������v�`��ʒu
static const PARTS_TRANS_PARAM NokoriTrans[4] = {
	{0x22 * 0x20, 6 * 0x20},		///<1����OAM�F��i
	{0x2a * 0x20, 6 * 0x20},		///<1����OAM�F���i
	{0x60 * 0x20, 7 * 0x20},		///<2����OAM�F��i
	{0x68 * 0x20, 7 * 0x20},		///<2����OAM�F���i
};

///�u�̂���@�������v�`��ʒu�̔w�i�F�ԍ�
#define NOKORI_BACK_COLOR		(0xf)
///�u�̂���@�������v�̕����F
#define NOKORI_FONT_COLOR		(GF_PRINTCOLOR_MAKE(0xe, 2, NOKORI_BACK_COLOR))

///�u�̂���@�������v�̐��l����
#define NOKORI_SAFARI_NUM_KETA		(2)

//--------------------------------------------------------------
//	2vs2�Q�[�W��HP���l�\�����[�h
//--------------------------------------------------------------
//HP�o�[�̓��`��ʒu
static const PARTS_TRANS_PARAM HPBarHeadTrans[] = {
	//GAUGE_TYPE_AA
	{0 * 0x20, 0 * 0x20},		///<1����OAM
	//GAUGE_TYPE_BB
	{0 * 0x20, 0 * 0x20},		///<1����OAM
	//GAUGE_TYPE_A
	{0x26 * 0x20, 2 * 0x20},		///<1����OAM
	//GAUGE_TYPE_B
	{0 * 0x20, 0 * 0x20},		///<1����OAM
	//GAUGE_TYPE_C
	{0x26 * 0x20, 2 * 0x20},		///<1����OAM
	//GAUGE_TYPE_D
	{0 * 0x20, 0 * 0x20},		///<1����OAM
};

//HP�o�[�̊W�`��ʒu
static const PARTS_TRANS_PARAM HPBarCapTrans[] = {
	//GAUGE_TYPE_AA
	{0 * 0x20, 0 * 0x20},		///<1����OAM
	//GAUGE_TYPE_BB
	{0 * 0x20, 0 * 0x20},		///<1����OAM
	//GAUGE_TYPE_A
	{0x66 * 0x20, 1 * 0x20},		///<1����OAM
	//GAUGE_TYPE_B
	{0 * 0x20, 0 * 0x20},		///<1����OAM
	//GAUGE_TYPE_C
	{0x66 * 0x20, 1 * 0x20},		///<1����OAM
	//GAUGE_TYPE_D
	{0 * 0x20, 0 * 0x20},		///<1����OAM
};

//HP�̃X���b�V���`��ʒu(2vs2�Q�[�W�̐��l���[�h�̎��p)
static const PARTS_TRANS_PARAM HPSlashTrans[] = {
	//GAUGE_TYPE_AA
	{0 * 0x20, 0 * 0x20},		///<1����OAM
	//GAUGE_TYPE_BB
	{0 * 0x20, 0 * 0x20},		///<1����OAM
	//GAUGE_TYPE_A
	{0x63 * 0x20, 1 * 0x20},		///<1����OAM
	//GAUGE_TYPE_B
	{0 * 0x20, 0 * 0x20},		///<1����OAM
	//GAUGE_TYPE_C
	{0x63 * 0x20, 1 * 0x20},		///<1����OAM
	//GAUGE_TYPE_D
	{0 * 0x20, 0 * 0x20},		///<1����OAM
};


//==============================================================================
//	�v���g�^�C�v�錾
//==============================================================================
static s32 GaugeOBJ(GAUGE_WORK *gauge, int req_data);
static s32 GaugeProc(s32 MaxHP, s32 NowHP, s32 beHP, s32 *HP_Work, u8 GaugeMax, u16 add_dec);
static u8 PutGaugeProc(s32 MaxHP, s32 NowHP, s32 beHP, s32 *HP_Work, u8 *gauge_chr, u8 GaugeMax);
static u32 DottoOffsetCalc(s32 nowHP, s32 beHP, s32 MaxHP, u8 GaugeMax);
static const u8 * GetGaugePartsAdrs(int parts_num);
static void PutGaugeOBJ(GAUGE_WORK *gauge, u8 req);
void MsgTool_OamSlideBuf(void *src_buf, void *dest_buf, const u8 oam_list[], int list_num);
static void GaugeParts_NameDraw(GAUGE_WORK *gauge);
static void GaugeParts_LevelFontDraw(GAUGE_WORK *gauge);
static void GaugeParts_LevelDraw(GAUGE_WORK *gauge);
static void GaugeParts_HPDraw(GAUGE_WORK *gauge, u32 hp);
static void GaugeParts_HPMaxDraw(GAUGE_WORK *gauge);
static void GaugeParts_SexDraw(GAUGE_WORK *gauge);
static void GaugeParts_GetBallDraw(GAUGE_WORK *gauge);
static void GaugeParts_StatusDraw(GAUGE_WORK *gauge, int gp_num);
static void GaugeParts_SafariballDraw(GAUGE_WORK *gauge, u32 draw_flag);
static void GaugeParts_SafariNokoriDraw(GAUGE_WORK *gauge, u32 draw_flag);
static void Gauge_ArrowResourceLoad(CATS_SYS_PTR csp, CATS_RES_PTR crp, PALETTE_FADE_PTR pfd, 
	int gauge_type);
static CATS_ACT_PTR Gauge_ArrowActorSet(CATS_SYS_PTR csp, CATS_RES_PTR crp, int gauge_type);
static void Gauge_ArrowActorDel(GAUGE_WORK *gauge);
static void Gauge_ArrowResourceFree(GAUGE_WORK *gauge);
static const TCATS_OBJECT_ADD_PARAM_S * Sub_GaugeObjHeadGet(u8 gauge_type);
static const TCATS_OBJECT_ADD_PARAM_S * Sub_ArrowObjHeadGet(u8 gauge_type);
static void Gauge_ScrollInOut(TCB_PTR tcb, void *work);
static void GaugeLevelUpEffTask(TCB_PTR tcb, void *work);
void Gauge_SinCurveSet(GAUGE_WORK *gauge);
void Gauge_SinCurveStop(GAUGE_WORK *gauge);
static void GaugeSinCurveMain(TCB_PTR tcb, void *work);
static void Gauge_ArrowEnableSet(GAUGE_WORK *gauge, int enable);


//==============================================================================
//	�f�[�^
//==============================================================================
///AA�p�Q�[�W�A�N�^�[�w�b�_
static const TCATS_OBJECT_ADD_PARAM_S GaugeObjParam_aa = {
	192+6,112 + 4, 0,		//x, y, z
	0, SOFTPRI_GAUGE_AA, 0,		//�A�j���ԍ��A�D�揇�ʁA�p���b�g�ԍ�
	NNS_G2D_VRAM_TYPE_2DMAIN,		//�`��G���A
	{	//�g�p���\�[�XID�e�[�u��
		SINGLE_GAGE2_NCGR_BIN,	//�L����
		PLTTID_GAUGE,	//�p���b�g
		SINGLE_GAGE2_NCER_BIN,	//�Z��
		SINGLE_GAGE2_NANR_BIN,	//�Z���A�j��
		CLACT_U_HEADER_DATA_NONE,		//�}���`�Z��
		CLACT_U_HEADER_DATA_NONE,		//�}���`�Z���A�j��
	},
	GAUGE_DEFAULT_BGPRI,			//BG�v���C�I���e�B
	0,			//Vram�]���t���O
};

///BB�p�Q�[�W�A�N�^�[�w�b�_
static const TCATS_OBJECT_ADD_PARAM_S GaugeObjParam_bb = {
	64-6,40-4, 0,		//x, y, z
	0, SOFTPRI_GAUGE_BB, 0,		//�A�j���ԍ��A�D�揇�ʁA�p���b�g�ԍ�
	NNS_G2D_VRAM_TYPE_2DMAIN,		//�`��G���A
	{	//�g�p���\�[�XID�e�[�u��
		SINGLE_GAGE1_NCGR_BIN,	//�L����
		PLTTID_GAUGE,	//�p���b�g
		SINGLE_GAGE1_NCER_BIN,	//�Z��
		SINGLE_GAGE1_NANR_BIN,	//�Z���A�j��
		CLACT_U_HEADER_DATA_NONE,		//�}���`�Z��
		CLACT_U_HEADER_DATA_NONE,		//�}���`�Z���A�j��
	},
	GAUGE_DEFAULT_BGPRI,			//BG�v���C�I���e�B
	0,			//Vram�]���t���O
};

///A�p�Q�[�W�A�N�^�[�w�b�_
static const TCATS_OBJECT_ADD_PARAM_S GaugeObjParam_a = {
	192,96 + 7, 0,		//x, y, z
	0, SOFTPRI_GAUGE_A, 0,		//�A�j���ԍ��A�D�揇�ʁA�p���b�g�ԍ�
	NNS_G2D_VRAM_TYPE_2DMAIN,		//�`��G���A
	{	//�g�p���\�[�XID�e�[�u��
		DOUBLE_GAGE3_NCGR_BIN,	//�L����
		PLTTID_GAUGE,	//�p���b�g
		DOUBLE_GAGE3_NCER_BIN,	//�Z��
		DOUBLE_GAGE3_NANR_BIN,	//�Z���A�j��
		CLACT_U_HEADER_DATA_NONE,		//�}���`�Z��
		CLACT_U_HEADER_DATA_NONE,		//�}���`�Z���A�j��
	},
	GAUGE_DEFAULT_BGPRI,			//BG�v���C�I���e�B
	0,			//Vram�]���t���O
};

///B�p�Q�[�W�A�N�^�[�w�b�_
static const TCATS_OBJECT_ADD_PARAM_S GaugeObjParam_b = {
	64,19-3, 0,		//x, y, z
	0, SOFTPRI_GAUGE_B, 0,		//�A�j���ԍ��A�D�揇�ʁA�p���b�g�ԍ�
	NNS_G2D_VRAM_TYPE_2DMAIN,		//�`��G���A
	{	//�g�p���\�[�XID�e�[�u��
		DOUBLE_GAGE1_NCGR_BIN,	//�L����
		PLTTID_GAUGE,	//�p���b�g
		DOUBLE_GAGE1_NCER_BIN,	//�Z��
		DOUBLE_GAGE1_NANR_BIN,	//�Z���A�j��
		CLACT_U_HEADER_DATA_NONE,		//�}���`�Z��
		CLACT_U_HEADER_DATA_NONE,		//�}���`�Z���A�j��
	},
	GAUGE_DEFAULT_BGPRI,			//BG�v���C�I���e�B
	0,			//Vram�]���t���O
};

///C�p�Q�[�W�A�N�^�[�w�b�_
static const TCATS_OBJECT_ADD_PARAM_S GaugeObjParam_c = {
	192+6,128+4, 0,		//x, y, z
	0, SOFTPRI_GAUGE_C, 0,		//�A�j���ԍ��A�D�揇�ʁA�p���b�g�ԍ�
	NNS_G2D_VRAM_TYPE_2DMAIN,		//�`��G���A
	{	//�g�p���\�[�XID�e�[�u��
		DOUBLE_GAGE4_NCGR_BIN,	//�L����
		PLTTID_GAUGE,	//�p���b�g
		DOUBLE_GAGE4_NCER_BIN,	//�Z��
		DOUBLE_GAGE4_NANR_BIN,	//�Z���A�j��
		CLACT_U_HEADER_DATA_NONE,		//�}���`�Z��
		CLACT_U_HEADER_DATA_NONE,		//�}���`�Z���A�j��
	},
	GAUGE_DEFAULT_BGPRI,			//BG�v���C�I���e�B
	0,			//Vram�]���t���O
};

///D�p�Q�[�W�A�N�^�[�w�b�_
static const TCATS_OBJECT_ADD_PARAM_S GaugeObjParam_d = {
	64-6,48-3, 0,		//x, y, z
	0, SOFTPRI_GAUGE_D, 0,		//�A�j���ԍ��A�D�揇�ʁA�p���b�g�ԍ�
	NNS_G2D_VRAM_TYPE_2DMAIN,		//�`��G���A
	{	//�g�p���\�[�XID�e�[�u��
		DOUBLE_GAGE2_NCGR_BIN,	//�L����
		PLTTID_GAUGE,	//�p���b�g
		DOUBLE_GAGE2_NCER_BIN,	//�Z��
		DOUBLE_GAGE2_NANR_BIN,	//�Z���A�j��
		CLACT_U_HEADER_DATA_NONE,		//�}���`�Z��
		CLACT_U_HEADER_DATA_NONE,		//�}���`�Z���A�j��
	},
	GAUGE_DEFAULT_BGPRI,			//BG�v���C�I���e�B
	0,			//Vram�]���t���O
};

///AA�p�Q�[�W���A�N�^�[�w�b�_
static const TCATS_OBJECT_ADD_PARAM_S ArrowParam_aa = {
	0,0, 0,		//x, y, z
	0, SOFTPRI_ARROW_AA, 0,		//�A�j���ԍ��A�D�揇�ʁA�p���b�g�ԍ�
	NNS_G2D_VRAM_TYPE_2DMAIN,		//�`��G���A
	{	//�g�p���\�[�XID�e�[�u��
		SINGLE_ARROW_ANIMATION2_NCGR_BIN,	//�L����
		PLTTID_GAUGE,	//�p���b�g
		SINGLE_ARROW_ANIMATION2_NCER_BIN,	//�Z��
		SINGLE_ARROW_ANIMATION2_NANR_BIN,	//�Z���A�j��
		CLACT_U_HEADER_DATA_NONE,		//�}���`�Z��
		CLACT_U_HEADER_DATA_NONE,		//�}���`�Z���A�j��
	},
	GAUGE_DEFAULT_BGPRI,			//BG�v���C�I���e�B
	0,			//Vram�]���t���O
};

///BB�p�Q�[�W���A�N�^�[�w�b�_
static const TCATS_OBJECT_ADD_PARAM_S ArrowParam_bb = {
	0, 0, 0,		//x, y, z
	0, SOFTPRI_ARROW_BB, 0,		//�A�j���ԍ��A�D�揇�ʁA�p���b�g�ԍ�
	NNS_G2D_VRAM_TYPE_2DMAIN,		//�`��G���A
	{	//�g�p���\�[�XID�e�[�u��
		SINGLE_ARROW_ANIMATION1_NCGR_BIN,	//�L����
		PLTTID_GAUGE,	//�p���b�g
		SINGLE_ARROW_ANIMATION1_NCER_BIN,	//�Z��
		SINGLE_ARROW_ANIMATION1_NANR_BIN,	//�Z���A�j��
		CLACT_U_HEADER_DATA_NONE,		//�}���`�Z��
		CLACT_U_HEADER_DATA_NONE,		//�}���`�Z���A�j��
	},
	GAUGE_DEFAULT_BGPRI,			//BG�v���C�I���e�B
	0,			//Vram�]���t���O
};

///�T�t�@���p�Q�[�W�A�N�^�[�w�b�_
static const TCATS_OBJECT_ADD_PARAM_S GaugeObjParam_Safari = {
	192,112 + 4, 0,		//x, y, z
	0, SOFTPRI_GAUGE_AA, 0,		//�A�j���ԍ��A�D�揇�ʁA�p���b�g�ԍ�
	NNS_G2D_VRAM_TYPE_2DMAIN,		//�`��G���A
	{	//�g�p���\�[�XID�e�[�u��
		SAFARI_GAUGE_NCGR_BIN,	//�L����
		PLTTID_GAUGE_SAFARI,	//�p���b�g
		SAFARI_GAUGE_NCER_BIN,	//�Z��
		SAFARI_GAUGE_NANR_BIN,	//�Z���A�j��
		CLACT_U_HEADER_DATA_NONE,		//�}���`�Z��
		CLACT_U_HEADER_DATA_NONE,		//�}���`�Z���A�j��
	},
	GAUGE_DEFAULT_BGPRI,			//BG�v���C�I���e�B
	0,			//Vram�]���t���O
};


//==============================================================================
//	�O���f�[�^
//==============================================================================
#include "gage_parts_txt.dat"


//--------------------------------------------------------------
/**
 * @brief   �Q�[�W�̃��\�[�X�ǂݍ���
 *
 * @param   gauge		
 */
//--------------------------------------------------------------
void Gauge_ResourceLoad(CATS_SYS_PTR csp, CATS_RES_PTR crp, PALETTE_FADE_PTR pfd, int gauge_type)
{
	const TCATS_OBJECT_ADD_PARAM_S *obj_head;
	
	//���\�[�X�ǂݍ���
	obj_head = Sub_GaugeObjHeadGet(gauge_type);
	
	CATS_LoadResourceCharArc(csp, crp, ARC_BATT_OBJ, obj_head->id[CLACT_U_CHAR_RES], 1, 
		NNS_G2D_VRAM_TYPE_2DMAIN, obj_head->id[CLACT_U_CHAR_RES]);
//	CATS_LoadResourcePlttArc(csp, crp, ARC_BATT_OBJ, obj_head->id[CLACT_U_PLTT_RES], 0, 
//		1, NNS_G2D_VRAM_TYPE_2DMAIN, obj_head->id[CLACT_U_PLTT_RES]);
	CATS_LoadResourcePlttWorkArc(pfd, FADE_MAIN_OBJ, csp, crp, 
		ARC_BATT_OBJ, GAGE_PALETTE_NCLR, 0, 
		1, NNS_G2D_VRAM_TYPE_2DMAIN, PLTTID_GAUGE);
	CATS_LoadResourceCellArc(csp, crp, ARC_BATT_OBJ, obj_head->id[CLACT_U_CELL_RES], 1, 
		obj_head->id[CLACT_U_CELL_RES]);
	CATS_LoadResourceCellAnmArc(csp, crp, ARC_BATT_OBJ, 
		obj_head->id[CLACT_U_CELLANM_RES], 1, obj_head->id[CLACT_U_CELLANM_RES]);

	//�G�t�F�N�g�p�p���b�g�Z�b�g
	CATS_LoadResourcePlttWorkArc(pfd, FADE_MAIN_OBJ, csp, crp, 
		ARC_BATT_OBJ, GAGE_PALETTE_NCLR, 0, 
		1, NNS_G2D_VRAM_TYPE_2DMAIN, PLTTID_GAUGE_EFF);
	if(gauge_type == GAUGE_TYPE_SAFARI || gauge_type == GAUGE_TYPE_PARK){
		CATS_LoadResourcePlttWorkArc(pfd, FADE_MAIN_OBJ, csp, crp, 
			ARC_BATT_OBJ, SAFARI_W_NCLR, 0, 
			1, NNS_G2D_VRAM_TYPE_2DMAIN, PLTTID_GAUGE_SAFARI);
	}
}

//--------------------------------------------------------------
/**
 * @brief   �Q�[�W���̃��\�[�X�ǂݍ���
 *
 * @param   gauge		�Q�[�W���[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
static void Gauge_ArrowResourceLoad(CATS_SYS_PTR csp, CATS_RES_PTR crp, PALETTE_FADE_PTR pfd, 
	int gauge_type)
{
	const TCATS_OBJECT_ADD_PARAM_S *obj_head;
	
	//���\�[�X�ǂݍ���
	obj_head = Sub_ArrowObjHeadGet(gauge_type);
	if(obj_head != NULL){
		CATS_LoadResourceCharArc(csp, crp, ARC_BATT_OBJ, obj_head->id[CLACT_U_CHAR_RES], 
			1, NNS_G2D_VRAM_TYPE_2DMAIN, obj_head->id[CLACT_U_CHAR_RES]);
//		CATS_LoadResourcePlttArc(csp, crp, ARC_BATT_OBJ, obj_head->id[CLACT_U_PLTT_RES], 
//			0, 1, NNS_G2D_VRAM_TYPE_2DMAIN, obj_head->id[CLACT_U_PLTT_RES]);
		CATS_LoadResourcePlttWorkArc(pfd, FADE_MAIN_OBJ, csp, crp, 
			ARC_BATT_OBJ, GAGE_PALETTE_NCLR, 
			0, 1, NNS_G2D_VRAM_TYPE_2DMAIN, PLTTID_GAUGE);
		CATS_LoadResourceCellArc(csp, crp, ARC_BATT_OBJ, obj_head->id[CLACT_U_CELL_RES], 
			1, obj_head->id[CLACT_U_CELL_RES]);
		CATS_LoadResourceCellAnmArc(csp, crp, ARC_BATT_OBJ, 
			obj_head->id[CLACT_U_CELLANM_RES], 1, 
			obj_head->id[CLACT_U_CELLANM_RES]);
	}
}

//--------------------------------------------------------------
/**
 * @brief   �Q�[�W�̃A�N�^�[�𐶐�����
 *
 * @param   gauge		
 *
 * ��Ƀ��\�[�X���ǂݍ��܂�Ă���K�v������܂��B
 */
//--------------------------------------------------------------
CATS_ACT_PTR Gauge_ActorSet(CATS_SYS_PTR csp, CATS_RES_PTR crp, int gauge_type)
{
	const TCATS_OBJECT_ADD_PARAM_S *obj_head;
	CATS_ACT_PTR cap;
	
	obj_head = Sub_GaugeObjHeadGet(gauge_type);

	cap = CATS_ObjectAdd_S(csp, crp, obj_head);
	CATS_ObjectUpdate(cap->act);
	return cap;
}

//--------------------------------------------------------------
/**
 * @brief   �Q�[�W���̃A�N�^�[�𐶐�����
 * @param   gauge		�Q�[�W���[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
static CATS_ACT_PTR Gauge_ArrowActorSet(CATS_SYS_PTR csp, CATS_RES_PTR crp, int gauge_type)
{
	const TCATS_OBJECT_ADD_PARAM_S *obj_head;
	CATS_ACT_PTR arrow_cap;
	
	obj_head = Sub_ArrowObjHeadGet(gauge_type);
	if(obj_head == NULL){
		arrow_cap = NULL;
		return arrow_cap;
	}
	
	arrow_cap = CATS_ObjectAdd_S(csp, crp, obj_head);
	CATS_ObjectUpdate(arrow_cap->act);
	return arrow_cap;
}

//--------------------------------------------------------------
/**
 * @brief   �Q�[�W�̃p�[�c(HP�o�[�A��Ԉُ퓙)��`�悷��
 *
 * @param   gauge			�Q�[�W���[�N�ւ̃|�C���^
 * @param   hp				�\������HP(Calc���œr���o�߂�\������K�v������̂�HP�����͈����w��)
 * @param   draw_flag		�`�悷��p�[�c�̃t���O(GAUGE_DRAW_???) ���r�b�g�w��(�����w���)
 *
 * ���̊֐��͍ĕ`��p�ł��BHP�����Z�����̏��������Ɏg�p������̂ł͂���܂���B
 * HP�����Z�̏����������s���ꍇ��Gauge_CalcHP�֐����g�p���Ă��������B
 * 
 * �ĕ`�悷��t���O�ɂ���Ă͍�Ɨp���[�N�̏��������s���܂�
 */
//--------------------------------------------------------------
void Gauge_PartsDraw(GAUGE_WORK *gauge, u32 hp, u32 draw_flag)
{
	int status_getball = FALSE;
	u32 draw_backup;
	
	GF_ASSERT(gauge->cap != NULL);
	
	draw_backup = draw_flag;
	
	//�s�v�ȃr�b�g�𗎂Ƃ�
	if(gauge->type == GAUGE_TYPE_SAFARI){
		draw_flag &= GAUGE_DRAW_ALL_SAFARI;
	}
	else if(gauge->type == GAUGE_TYPE_PARK){
		draw_flag &= GAUGE_DRAW_ALL_PARK;
	}
	else{
		draw_flag &= GAUGE_DRAW_ALL ^ (GAUGE_DRAW_ALL_SAFARI | GAUGE_DRAW_ALL_PARK);
	}
	switch(gauge->type){
	case GAUGE_TYPE_BB:
	case GAUGE_TYPE_B:
	case GAUGE_TYPE_D:
		draw_flag &= GAUGE_DRAW_ALL ^ (GAUGE_DRAW_HPNUM | GAUGE_DRAW_HPNUMMAX | GAUGE_DRAW_EXP);
		status_getball = TRUE;	//�X�e�[�^�X�\�����m�[�}���`��̎��A�Q�b�g�ς݃{�[���\������
	#ifdef PM_DEBUG
		if(gauge->debug_hp_put == TRUE){
			if(draw_backup & GAUGE_DRAW_HPNUM){
				draw_flag |= GAUGE_DRAW_HPNUM;
			}
			if(draw_backup & GAUGE_DRAW_HPNUMMAX){
				draw_flag |= GAUGE_DRAW_HPNUMMAX;
			}
		}
	#endif
		break;
	case GAUGE_TYPE_A:
	case GAUGE_TYPE_C:
		draw_flag &= GAUGE_DRAW_ALL ^ (GAUGE_DRAW_EXP | GAUGE_DRAW_GETBALL);
		if(gauge->num_mode == FALSE){	//HP�\���F�o�[
			draw_flag &= GAUGE_DRAW_ALL ^ (GAUGE_DRAW_HPNUM | GAUGE_DRAW_HPNUMMAX);
		}
		else{	//HP�\���F���l
			draw_flag &= GAUGE_DRAW_ALL ^ (GAUGE_DRAW_HPBAR);
		}
		break;
	case GAUGE_TYPE_AA:
		draw_flag &= GAUGE_DRAW_ALL ^ (GAUGE_DRAW_GETBALL);
		break;
	case GAUGE_TYPE_SAFARI:
	case GAUGE_TYPE_PARK:
		break;
	}
	if(BattleWorkFightTypeGet(gauge->bw) & FIGHT_TYPE_TRAINER){
		draw_flag &= GAUGE_DRAW_ALL ^ (GAUGE_DRAW_GETBALL);
	}
	
	
	if(draw_flag & GAUGE_DRAW_HPBAR){
		Gauge_InitCalcHP(gauge, 0);
		GaugeOBJ(gauge, GAUGE_REQ_HP);
	}
	
	if(draw_flag & GAUGE_DRAW_HPNUM){
		GaugeParts_HPDraw(gauge, hp);
	}
	
	if(draw_flag & GAUGE_DRAW_HPNUMMAX){
		GaugeParts_HPMaxDraw(gauge);
	}
	
//	if(draw_flag & GAUGE_DRAW_LEVEL_FONT){
	if((draw_flag & GAUGE_DRAW_LEVEL_FONT) || (draw_flag & GAUGE_DRAW_SEX)){
		GaugeParts_LevelFontDraw(gauge);
	}
	
	if(draw_flag & GAUGE_DRAW_LEVEL){
		GaugeParts_LevelDraw(gauge);
	}
	
	if(draw_flag & GAUGE_DRAW_NAME){
		GaugeParts_NameDraw(gauge);
	}
	
	if(draw_flag & GAUGE_DRAW_EXP){
		Gauge_InitCalcEXP(gauge, 0);
		GaugeOBJ(gauge, GAUGE_REQ_EXP);
	}
	
#if 0	//�uLV�v�����Ɠ��� 2006.04.19(��)
	if(draw_flag & GAUGE_DRAW_SEX){
		GaugeParts_SexDraw(gauge);
	}
#endif

	if(draw_flag & GAUGE_DRAW_GETBALL){
		GaugeParts_GetBallDraw(gauge);
	}
	
	if(draw_flag & GAUGE_DRAW_STATUS){
		switch(gauge->status){
		default:
		case STATUS_NORMAL:
			GaugeParts_StatusDraw(gauge, GP_NON_STATUS);
			
		#if 0	//���C�A�E�g�I�ɏ�Ԉُ�̎��ł��Q�b�g�}�[�N�������Ȃ��Ă悭�Ȃ��� 2006.04.19(��)
			if(status_getball == TRUE){
				GaugeParts_GetBallDraw(gauge);
			}
		#endif
			break;
		case STATUS_NEMURI:
			GaugeParts_StatusDraw(gauge, GP_NEMURI);
			break;
		case STATUS_DOKU:
			GaugeParts_StatusDraw(gauge, GP_DOKU);
			break;
		case STATUS_YAKEDO:
			GaugeParts_StatusDraw(gauge, GP_YAKEDO);
			break;
		case STATUS_KOORI:
			GaugeParts_StatusDraw(gauge, GP_KOORI);
			break;
		case STATUS_MAHI:
			GaugeParts_StatusDraw(gauge, GP_MAHI);
			break;
		}
	}
	
	if(draw_flag & (GAUGE_DRAW_SAFARIBALL | GAUGE_DRAW_PARKBALL)){
		GaugeParts_SafariballDraw(gauge, draw_flag);
	}
	
	if(draw_flag & (GAUGE_DRAW_SAFARI_NOKORI | GAUGE_DRAW_PARK_NOKORI)){
		GaugeParts_SafariNokoriDraw(gauge, draw_flag);
	}
}

//--------------------------------------------------------------
/**
 * @brief   �Q�[�W�̃A�N�^�[���폜����
 * @param   gauge		�Q�[�W���[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
void Gauge_ActorDel(GAUGE_WORK *gauge)
{
	if(gauge->sin_tcb != NULL){
		TCB_Delete(gauge->sin_tcb);
		gauge->sin_tcb = NULL;
	}
	
	if(gauge->cap == NULL){
		return;
	}
	CATS_ActorPointerDelete_S(gauge->cap);
	gauge->cap = NULL;
}

//--------------------------------------------------------------
/**
 * @brief   �Q�[�W���̃A�N�^�[���폜����
 * @param   gauge		�Q�[�W���[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
static void Gauge_ArrowActorDel(GAUGE_WORK *gauge)
{
	if(gauge->arrow_cap == NULL){
		return;
	}
	CATS_ActorPointerDelete_S(gauge->arrow_cap);
	gauge->arrow_cap = NULL;
}

//--------------------------------------------------------------
/**
 * @brief   �Q�[�W�̃��\�[�X���������
 * @param   gauge		�Q�[�W���[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
void Gauge_ResourceFree(GAUGE_WORK *gauge)
{
	CATS_SYS_PTR csp;
	CATS_RES_PTR crp;
	const TCATS_OBJECT_ADD_PARAM_S *obj_head;

	obj_head = Sub_GaugeObjHeadGet(gauge->type);
	
	csp = BattleWorkCATS_SYS_PTRGet(gauge->bw);
	crp = BattleWorkCATS_RES_PTRGet(gauge->bw);

	//���\�[�X���
	CATS_FreeResourceChar(crp, obj_head->id[CLACT_U_CHAR_RES]);
//	CATS_FreeResourcePltt(crp, PLTTID_GAUGE);
	CATS_FreeResourceCell(crp, obj_head->id[CLACT_U_CELL_RES]);
	CATS_FreeResourceCellAnm(crp, obj_head->id[CLACT_U_CELLANM_RES]);
}

//--------------------------------------------------------------
/**
 * @brief   �Q�[�W���̃��\�[�X���������
 * @param   gauge		�Q�[�W���[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
static void Gauge_ArrowResourceFree(GAUGE_WORK *gauge)
{
	CATS_SYS_PTR csp;
	CATS_RES_PTR crp;
	const TCATS_OBJECT_ADD_PARAM_S *obj_head;

	obj_head = Sub_ArrowObjHeadGet(gauge->type);
	if(obj_head == NULL){
		return;
	}
	
	csp = BattleWorkCATS_SYS_PTRGet(gauge->bw);
	crp = BattleWorkCATS_RES_PTRGet(gauge->bw);

	//���\�[�X���
	CATS_FreeResourceChar(crp, obj_head->id[CLACT_U_CHAR_RES]);
//	CATS_FreeResourcePltt(crp, PLTTID_GAUGE);
	CATS_FreeResourceCell(crp, obj_head->id[CLACT_U_CELL_RES]);
	CATS_FreeResourceCellAnm(crp, obj_head->id[CLACT_U_CELLANM_RES]);
}


//--------------------------------------------------------------
/**
 * @brief   �Q�[�W�̃A�N�^�[�o�^�ƃ��\�[�X�o�^���Z�b�g�ɂ�������
 * @param   gauge		�Q�[�W���[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
void Gauge_ActorResourceSet(GAUGE_WORK *gauge)
{
	const TCATS_OBJECT_ADD_PARAM_S *obj_head;
	CATS_SYS_PTR csp;
	CATS_RES_PTR crp;
	PALETTE_FADE_PTR pfd;
	
	csp = BattleWorkCATS_SYS_PTRGet(gauge->bw);
	crp = BattleWorkCATS_RES_PTRGet(gauge->bw);
	pfd = BattleWorkPfdGet(gauge->bw);
	
	obj_head = Sub_GaugeObjHeadGet(gauge->type);

	Gauge_ResourceLoad(csp, crp, pfd, gauge->type);
	gauge->cap = Gauge_ActorSet(csp, crp, gauge->type);
//	Gauge_PartsDraw(gauge, gauge->hp, GAUGE_DRAW_ALL);
	
	//���
	Gauge_ArrowResourceLoad(csp, crp, pfd, gauge->type);
//	gauge->arrow_cap = Gauge_ArrowActorSet(csp, crp, gauge->type);
	//���̍��W�Z�b�g
	if(gauge->arrow_cap != NULL){
		CATS_ObjectPosSet(gauge->arrow_cap->act, obj_head->x - ArrowOffsetPosX[gauge->type], 
			obj_head->y + ARROW_OFFSET_Y);
	}
}

//--------------------------------------------------------------
/**
 * @brief   �Q�[�W�̃A�N�^�[�폜�ƃ��\�[�X������Z�b�g�ɂ�������
 * @param   gauge		�Q�[�W���[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
void Gauge_ActorResourceDel(GAUGE_WORK *gauge)
{
	//�Q�[�W�{��
	Gauge_ActorDel(gauge);
	Gauge_ResourceFree(gauge);
	//���
	Gauge_ArrowActorDel(gauge);
	Gauge_ArrowResourceFree(gauge);
}

//--------------------------------------------------------------
/**
 * @brief   2vs2���AHP�\�����o�[�\���Ɛ��l�\���ɐ؂�ւ���
 *
 * @param   gauge			�Q�[�W���[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
void Gauge_NumModeChange(GAUGE_WORK *gauge)
{
	const u8 *parts;
	NNSG2dImageProxy * image;
	void *obj_vram;
	
	switch(gauge->type){
	case GAUGE_TYPE_A:
	case GAUGE_TYPE_C:
		break;
	default:
		return;
	}
	
	gauge->num_mode ^= 1;

	obj_vram = G2_GetOBJCharPtr();
	image = CLACT_ImageProxyGet(gauge->cap->act);

	if(gauge->num_mode == TRUE){	//���l���[�h
		//HP�o�[�̓��ƊW������
		parts = GetGaugePartsAdrs(GP_HPBAR_HEAD_CLEAR);
		MI_CpuCopy16(parts, (void*)((u32)obj_vram + HPBarHeadTrans[gauge->type].pos
			+ image->vramLocation.baseAddrOfVram[NNS_G2D_VRAM_TYPE_2DMAIN]), 
			HPBarHeadTrans[gauge->type].size);

		//����HP�ƍő�HP�̊Ԃ̃X���b�V����`��
		parts = GetGaugePartsAdrs(GP_SLASH);
		MI_CpuCopy16(parts, (void*)((u32)obj_vram + HPSlashTrans[gauge->type].pos
			+ image->vramLocation.baseAddrOfVram[NNS_G2D_VRAM_TYPE_2DMAIN]), 
			HPSlashTrans[gauge->type].size);
		
		//���l�`��
		Gauge_PartsDraw(gauge, gauge->hp, GAUGE_DRAW_HPNUM | GAUGE_DRAW_HPNUMMAX);
	}
	else{	//�o�[���[�h
		//HP�o�[�̓���`��
		parts = GetGaugePartsAdrs(GP_HPBAR_HEAD);
		MI_CpuCopy16(parts, (void*)((u32)obj_vram + HPBarHeadTrans[gauge->type].pos
			+ image->vramLocation.baseAddrOfVram[NNS_G2D_VRAM_TYPE_2DMAIN]), 
			HPBarHeadTrans[gauge->type].size);

		//HP�o�[�̊W��`��
		parts = GetGaugePartsAdrs(GP_HPBAR_CAP);
		MI_CpuCopy16(parts, (void*)((u32)obj_vram + HPBarCapTrans[gauge->type].pos
			+ image->vramLocation.baseAddrOfVram[NNS_G2D_VRAM_TYPE_2DMAIN]), 
			HPBarCapTrans[gauge->type].size);
		
		//HP�o�[�`��
		Gauge_PartsDraw(gauge, gauge->hp, GAUGE_DRAW_HPBAR);
	}
}


//--------------------------------------------------------------
/**
 * @brief   HP�o�[�̌v�Z���J�n����O�ɍ�Ɨp���[�N���̏��������s��
 *
 * @param   gauge		�Q�[�W���[�N�ւ̃|�C���^
 * @param   damage		�_���[�W(�}�C�i�X�Ń_���[�W�A�v���X�Ȃ��)
 *
 * Gauge_CalcHP�����s����O�ɕK���Ăяo���Ēu���K�v������܂��B
 */
//--------------------------------------------------------------
void Gauge_InitCalcHP(GAUGE_WORK *gauge, int damage)
{
	gauge->hp_work = HP_WORK_INIT_VALUE;
	
	if(gauge->hp + damage < 0){
		damage -= gauge->hp + damage;
	}
	if(gauge->hp + damage > gauge->hpmax){
		damage -= (gauge->hp + damage) - gauge->hpmax;
	}
	
	//-- ���Q�[�W�v�Z���[�`���ɍ��킹�邽�߁A�����̋t�]�Ȃǂ��s�� --//
	gauge->damage = -damage;
	if(gauge->hp < 0){
		gauge->hp = 0;
	}
	if(gauge->hp > gauge->hpmax){
		gauge->hp = gauge->hpmax;
	}
}

//--------------------------------------------------------------
/**
 * @brief   HP�o�[�̌v�Z�Ə������݂��s��
 *
 * @param   gauge		�Q�[�W���[�N�ւ̃|�C���^
 *
 * @retval  -1=�I���B�@-1�ȊO=�v�Z�r���̐���(��ʂɕ\�����鐔�l)
 *
 * Gauge_InitCalcHP���ɌĂ�ł���K�v������܂��B
 */
//--------------------------------------------------------------
s32 Gauge_CalcHP(GAUGE_WORK *gauge)
{
	s32 calc_hp;
	
	calc_hp = GaugeOBJ(gauge, GAUGE_REQ_HP);	//�v�Z���o�[��������
	if(calc_hp == -1){
		//�v�Z�I�����ɃQ�[�W���[�N��hp�p�����[�^���ŐV�̒l(�_���[�W�v�Z��)�ōX�V���Ă���
		gauge->hp -= gauge->damage;
		Gauge_PartsDraw(gauge, gauge->hp, GAUGE_DRAW_HPNUM);	//���l��������
	}
	else{
		Gauge_PartsDraw(gauge, calc_hp, GAUGE_DRAW_HPNUM);	//���l��������
	}
	return calc_hp;
}

//--------------------------------------------------------------
/**
 * @brief   EXP�o�[�̌v�Z���J�n����O�ɍ�Ɨp���[�N���̏��������s��
 *
 * @param   gauge		�Q�[�W���[�N�ւ̃|�C���^
 * @param   add_exp		���Z����EXP�l
 *
 * Gauge_CalcEXP�����s����O�ɕK���Ăяo���Ēu���K�v������܂��B
 */
//--------------------------------------------------------------
void Gauge_InitCalcEXP(GAUGE_WORK *gauge, int add_exp)
{
	gauge->exp_work = HP_WORK_INIT_VALUE;

	if(gauge->exp + add_exp < 0){
		add_exp -= gauge->exp + add_exp;
	}
	if(gauge->exp + add_exp > gauge->max_exp){
		add_exp -= (gauge->exp + add_exp) - gauge->max_exp;
	}

	//-- ���Q�[�W�v�Z���[�`���ɍ��킹�邽�߁A�����̋t�]�Ȃǂ��s�� --//
	gauge->add_exp = -add_exp;
	if(gauge->exp < 0){
		gauge->exp = 0;
	}
	if(gauge->exp > gauge->max_exp){
		gauge->exp = gauge->max_exp;
	}
}

//--------------------------------------------------------------
/**
 * @brief   EXP�o�[�̌v�Z�Ə������݂��s��
 *
 * @param   gauge		�Q�[�W���[�N�ւ̃|�C���^
 *
 * @retval  -1=�I���B�@-1�ȊO=�v�Z�r���̐���(��ʂɕ\�����鐔�l)
 *
 * Gauge_InitCalcEXP���ɌĂ�ł���K�v������܂��B
 */
//--------------------------------------------------------------
s32 Gauge_CalcEXP(GAUGE_WORK *gauge)
{
	s32 calc_exp;
	
	calc_exp = GaugeOBJ(gauge, GAUGE_REQ_EXP);
	if(calc_exp == -1){
		//�v�Z�I�����ɃQ�[�W���[�N��exp�p�����[�^���ŐV�̒l(�_���[�W�v�Z��)�ōX�V���Ă���
		gauge->exp -= gauge->add_exp;
	}
	return calc_exp;
}

//--------------------------------------------------------------
/**
 * @brief   ���A�j���J�n
 * @param   gauge		�Q�[�W���[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
void Gauge_AnimeStart(GAUGE_WORK *gauge)
{
	if(gauge->arrow_cap != NULL){
		CLACT_SetAnmFlag(gauge->arrow_cap->act, 1);
		Gauge_ArrowEnableSet(gauge, CATS_ENABLE_TRUE);
	}
	
	if((BattleWorkFightTypeGet(gauge->bw) & FIGHT_TYPE_NO_ARROW_ANIME) == 0){
		Gauge_SinCurveSet(gauge);
	}
}

//--------------------------------------------------------------
/**
 * @brief   ���A�j����~
 * @param   gauge		�Q�[�W���[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
void Gauge_AnimeStop(GAUGE_WORK *gauge)
{
	if(gauge->arrow_cap != NULL){
		CLACT_SetAnmFlag(gauge->arrow_cap->act, 0);
		CLACT_AnmFrameSet(gauge->arrow_cap->act, 0);
		Gauge_ArrowEnableSet(gauge, CATS_ENABLE_FALSE);
	}
	
	Gauge_SinCurveStop(gauge);
}

//--------------------------------------------------------------
/**
 * @brief   �Q�[�W��BG�v���C�I���e�B�ύX
 *
 * @param   gauge		�Q�[�W���[�N�ւ̃|�C���^
 * @param   bg_pri		BG�v���C�I���e�B
 */
//--------------------------------------------------------------
void Gauge_BGPriSet(GAUGE_WORK *gauge, int bg_pri)
{
	if(gauge->cap == NULL){
		return;
	}
	CATS_ObjectBGPriSetCap(gauge->cap, bg_pri);
	if(gauge->arrow_cap != NULL){
		CATS_ObjectBGPriSetCap(gauge->arrow_cap, bg_pri);
	}
}

//--------------------------------------------------------------
/**
 * @brief   �Q�[�W���̕\���E��\���Z�b�g
 *
 * @param   gauge		�Q�[�W���[�N�ւ̃|�C���^
 * @param   enable		CATS_ENABLE_TRUE(�\��) or CATS_ENABLE_FALSE(��\��)
 */
//--------------------------------------------------------------
static void Gauge_ArrowEnableSet(GAUGE_WORK *gauge, int enable)
{
	if(gauge->arrow_cap != NULL){
		if((BattleWorkFightTypeGet(gauge->bw) & FIGHT_TYPE_NO_ARROW_ANIME) && enable == CATS_ENABLE_TRUE){
			;		//�T�t�@���A�|�P�p�[�N�Ȃ���\����Ԃɂ͂��Ȃ�
		}
		else{
			CATS_ObjectEnableCap(gauge->arrow_cap, enable);
		}
	}
}

//--------------------------------------------------------------
/**
 * @brief   �Q�[�W�̕\���E��\���Z�b�g
 *
 * @param   gauge		�Q�[�W���[�N�ւ̃|�C���^
 * @param   enable		CATS_ENABLE_TRUE(�\��) or CATS_ENABLE_FALSE(��\��)
 */
//--------------------------------------------------------------
void Gauge_EnableSet(GAUGE_WORK *gauge, int enable)
{
	if(gauge->cap == NULL){
		return;
	}
	
	CATS_ObjectEnableCap(gauge->cap, enable);
	Gauge_ArrowEnableSet(gauge, enable);
}

//--------------------------------------------------------------
/**
 * @brief   �Q�[�W�ɃI�t�Z�b�g�|�W�V�������Z�b�g����
 *
 * @param   gauge		�Q�[�W���[�N�ւ̃|�C���^
 * @param   x			�I�t�Z�b�gX
 * @param   y			�I�t�Z�b�gY
 *
 * �ʏ�̒�ʒu����̃I�t�Z�b�g�ɂȂ�܂��B
 */
//--------------------------------------------------------------
void Gauge_OffsetPosSet(GAUGE_WORK *gauge, int x, int y)
{
	const TCATS_OBJECT_ADD_PARAM_S *obj_head;
	
	GF_ASSERT(gauge->cap != NULL);

	obj_head = Sub_GaugeObjHeadGet(gauge->type);
	
	CATS_ObjectPosSet(gauge->cap->act, obj_head->x + x, obj_head->y + y);
	if(gauge->arrow_cap != NULL){
		CATS_ObjectPosSet(gauge->arrow_cap->act, 
			obj_head->x + x - ArrowOffsetPosX[gauge->type], obj_head->y + y + ARROW_OFFSET_Y);
	}
}

//--------------------------------------------------------------
/**
 * @brief   �Q�[�W�X�N���[��IN�EOUT�G�t�F�N�g���N������
 *
 * @param   gauge		�Q�[�W���[�N�ւ̃|�C���^
 * @param   in_out		�X�N���[������(GAUGE_SCROLL_IN or GAUGE_SCROLL_OUT)
 *
 * �G�t�F�N�g�I�����ɁAgauge->eff_wait_in_out��TRUE���Z�b�g����܂�
 */
//--------------------------------------------------------------
void Gauge_ScrollEffectSet(GAUGE_WORK *gauge, int in_out)
{
	GF_ASSERT(gauge != NULL);
	GF_ASSERT(gauge->cap != NULL);
	
	gauge->eff_wait_in_out = FALSE;
	
	gauge->in_out_dir = in_out;
	if(in_out == GAUGE_SCROLL_IN){
		switch(gauge->type){
		case GAUGE_TYPE_AA:
		case GAUGE_TYPE_A:
		case GAUGE_TYPE_C:
		case GAUGE_TYPE_SAFARI:
		case GAUGE_TYPE_PARK:
			Gauge_OffsetPosSet(gauge, GAUGE_SCROLL_OUT_OFFSET_X, GAUGE_SCROLL_OUT_OFFSET_Y);
			break;
		default:
			Gauge_OffsetPosSet(gauge, -GAUGE_SCROLL_OUT_OFFSET_X, GAUGE_SCROLL_OUT_OFFSET_Y);
			break;
		}
	}
	else{
		Gauge_OffsetPosSet(gauge, 0, 0);
	}
	TCB_Add(Gauge_ScrollInOut, gauge, TCBPRI_HP_GAUGE_IN_TASK);
}

//--------------------------------------------------------------
/**
 * @brief   �Q�[�W�X�N���[��������^�X�N
 *
 * @param   tcb			TCB�ւ̃|�C���^
 * @param   work		GAUGE_WORK�ւ̃|�C���^
 */
//--------------------------------------------------------------
static void Gauge_ScrollInOut(TCB_PTR tcb, void *work)
{
	GAUGE_WORK *gauge = work;
	s16 x, y;
	const TCATS_OBJECT_ADD_PARAM_S *obj_head;
	int end;
	
	end = 0;
	obj_head = Sub_GaugeObjHeadGet(gauge->type);
	CATS_ObjectPosGetCap(gauge->cap, &x, &y);
	switch(gauge->type){
	case GAUGE_TYPE_AA:
	case GAUGE_TYPE_A:
	case GAUGE_TYPE_C:
	case GAUGE_TYPE_SAFARI:
	case GAUGE_TYPE_PARK:
		if(gauge->in_out_dir == GAUGE_SCROLL_IN){
			x -= GAUGE_SCROLL_SP_X;
			if(x < obj_head->x){
				x = obj_head->x;
				end++;
			}
		}
		else{
			x += GAUGE_SCROLL_SP_X;
			if(x > obj_head->x + GAUGE_SCROLL_OUT_OFFSET_X){
				x = obj_head->x + GAUGE_SCROLL_OUT_OFFSET_X;
				end++;
			}
		}
		break;
	default:
		if(gauge->in_out_dir == GAUGE_SCROLL_IN){
			x += GAUGE_SCROLL_SP_X;
			if(x > obj_head->x){
				x = obj_head->x;
				end++;
			}
		}
		else{
			x -= GAUGE_SCROLL_SP_X;
			if(x < obj_head->x - GAUGE_SCROLL_SP_X){
				x = obj_head->x - GAUGE_SCROLL_SP_X;
				end++;
			}
		}
		break;
	}
	CATS_ObjectPosSetCap(gauge->cap, x, y);
	if(gauge->arrow_cap != NULL){
		CATS_ObjectPosSetCap(gauge->arrow_cap, x - ArrowOffsetPosX[gauge->type], 
			y + ARROW_OFFSET_Y);
	}
	
	if(end > 0){
		gauge->eff_wait_in_out = TRUE;
		TCB_Delete(tcb);
		return;
	}
}

//--------------------------------------------------------------
/**
 * @brief   �Q�[�W�̃f�o�b�OHP�\���t���O�𔽓]����
 *
 * @param   gauge		�Q�[�W�[���[�N�ւ̃|�C���^
 * @param   put			TRUE:�\���B�@FALSE:��\��
 *
 * PM_DEBUG���L���łȂ��ꍇ�͉����������܂���B
 */
//--------------------------------------------------------------
void Gauge_DebugHPPutFlagFlip(GAUGE_WORK *gauge)
{
#ifdef PM_DEBUG
	gauge->debug_hp_put ^= TRUE;
#endif
}




//==============================================================================
//
//	�p�[�c�`��
//
//==============================================================================
//--------------------------------------------------------------
/**
 * @brief   �Q�[�W�p�[�c�`��F���O
 * @param   gauge		�Q�[�W���[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
static void GaugeParts_NameDraw(GAUGE_WORK *gauge)
{
	GF_BGL_INI *bgl;
	u8 *buf;
	NNSG2dImageProxy * image;
	GF_BGL_BMPWIN bmpwin;
	MSGDATA_MANAGER *msg_man;
	STRBUF *monsname_p, *monsname_src;
	POKEMON_PARAM *pp;
	POKEMON_PASO_PARAM *ppp;
	WORDSET *wordset;
	
	bgl = BattleWorkGF_BGL_INIGet(gauge->bw);
	msg_man = BattleWorkFightMsgGet(gauge->bw);
	wordset = BattleWorkWORDSETGet(gauge->bw);
	
	//������W�J
	monsname_p = STRBUF_Create(BUFLEN_GAUGE_POKESELENAME, HEAPID_BATTLE);
	monsname_src = MSGMAN_AllocString(msg_man, TargetPokemonMsg);
	pp = BattleWorkPokemonParamGet(gauge->bw, gauge->client_no, gauge->sel_mons_no);
	ppp = PPPPointerGet(pp);
	WORDSET_RegisterPokeNickName(wordset, 0, ppp);
	WORDSET_ExpandStr(wordset, monsname_p, monsname_src);
	
	//�o�b�t�@��BMP�f�[�^�W�J
	GF_BGL_BmpWinObjAdd(bgl, &bmpwin, NAME_SIZE_X, NAME_SIZE_Y, 
		NAME_CHAR_OFFSET, NAME_BACK_COLOR);
	GF_STR_PrintExpand(&bmpwin, FONT_SYSTEM, monsname_p, 0, 0, MSG_NO_PUT, NAME_FONT_COLOR, GAUGE_FONT_MARGIN, 0, NULL);
	buf = bmpwin.chrbuf;
	
	//�`�����ꂽ�����o�b�t�@��VRAM�ɒ�����
	{
		void *obj_vram;
		u8 *high, *low;
		
		obj_vram = G2_GetOBJCharPtr();
		image = CLACT_ImageProxyGet(gauge->cap->act);
		high = buf;
		low = &buf[NAME_SIZE_X * 0x20];
		//����
		MI_CpuCopy16(high, (void*)((u32)obj_vram + NameTrans[gauge->type][0].pos
			+ image->vramLocation.baseAddrOfVram[NNS_G2D_VRAM_TYPE_2DMAIN]), 
			NameTrans[gauge->type][0].size);
		MI_CpuCopy16(low, (void*)((u32)obj_vram + NameTrans[gauge->type][1].pos
			+ image->vramLocation.baseAddrOfVram[NNS_G2D_VRAM_TYPE_2DMAIN]), 
			NameTrans[gauge->type][1].size);
		//�E��
		MI_CpuCopy16(&high[NameTrans[gauge->type][0].size], 
			(void*)((u32)obj_vram + NameTrans[gauge->type][2].pos
			+ image->vramLocation.baseAddrOfVram[NNS_G2D_VRAM_TYPE_2DMAIN]), 
			NameTrans[gauge->type][2].size);
		MI_CpuCopy16(&low[NameTrans[gauge->type][1].size], 
			(void*)((u32)obj_vram + NameTrans[gauge->type][3].pos
			+ image->vramLocation.baseAddrOfVram[NNS_G2D_VRAM_TYPE_2DMAIN]), 
			NameTrans[gauge->type][3].size);
	}
	
	//BMP�f�[�^���
	GF_BGL_BmpWinDel(&bmpwin);
	//������o�b�t�@���
	STRBUF_Delete(monsname_p);
	STRBUF_Delete(monsname_src);
	
#if 0
	//�]��
	image = CLACT_ImageProxyGet(gauge->cap->act);
	AddVramTransferManager(
		NNS_GFD_DST_2D_OBJ_CHAR_MAIN,
		image->vramLocation.baseAddrOfVram[NNS_G2D_VRAM_TYPE_2DMAIN],
		buf,
		NAME_BYTE_SIZE
		);
#endif
}

//--------------------------------------------------------------
/**
 * @brief   �Q�[�W�p�[�c�`��F���x��
 * @param   gauge		�Q�[�W���[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
static void GaugeParts_LevelFontDraw(GAUGE_WORK *gauge)
{
	u8 *dest_buf;
	NNSG2dImageProxy * image;
	int numfont_size, i, t, k;
	const u8 *level_buf;
	int gp;
	
	numfont_size = 0x20 * 2;
	if(gauge->sex == PARA_MALE){
		gp = GP_SEX_MALE;
	}
	else if(gauge->sex == PARA_FEMALE){
		gp = GP_SEX_FEMALE;
	}
	else{
		gp = GP_SEX_UNK;
	}
	level_buf = GetGaugePartsAdrs(gp);
	dest_buf = sys_AllocMemory(HEAPID_BATTLE, numfont_size * 2);
	
	//�`�����ꂽ�����o�b�t�@��VRAM�ɒ�����
	{
		void *obj_vram;
		u8 *high, *low;
		
		obj_vram = G2_GetOBJCharPtr();
		image = CLACT_ImageProxyGet(gauge->cap->act);
		
		//Vram���烁�����̈�Ɉ�x�R�s�[
		MI_CpuCopy16((void*)((u32)obj_vram + LvFontTrans[gauge->type][0].pos
			+ image->vramLocation.baseAddrOfVram[NNS_G2D_VRAM_TYPE_2DMAIN]), 
			dest_buf, LvFontTrans[gauge->type][0].size);
		MI_CpuCopy16((void*)((u32)obj_vram + LvFontTrans[gauge->type][1].pos
			+ image->vramLocation.baseAddrOfVram[NNS_G2D_VRAM_TYPE_2DMAIN]), 
			&dest_buf[numfont_size], LvFontTrans[gauge->type][1].size);
		
		//�������̈�ɃR�s�[�������̂ɐ����t�H���g����������
		k = 0;
		for(t = 0; t < numfont_size; t += 32){
			for(i = 0; i < 16; i++){
				dest_buf[t + 16 + i] = level_buf[k];
				dest_buf[t + i + numfont_size] = level_buf[k + 16];
				k++;
			}
			k += 16;
		}
		
		//�o���オ�������̂�Vram�֏����߂�
		high = dest_buf;
		low = &dest_buf[numfont_size];
		MI_CpuCopy16(high, (void*)((u32)obj_vram + LvFontTrans[gauge->type][0].pos
			+ image->vramLocation.baseAddrOfVram[NNS_G2D_VRAM_TYPE_2DMAIN]), 
			LvFontTrans[gauge->type][0].size);
		MI_CpuCopy16(low, (void*)((u32)obj_vram + LvFontTrans[gauge->type][1].pos
			+ image->vramLocation.baseAddrOfVram[NNS_G2D_VRAM_TYPE_2DMAIN]), 
			LvFontTrans[gauge->type][1].size);
	}
	
	//�W�J�̈���
	sys_FreeMemoryEz(dest_buf);
}

//--------------------------------------------------------------
/**
 * @brief   �Q�[�W�p�[�c�`��F���x��
 * @param   gauge		�Q�[�W���[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
static void GaugeParts_LevelDraw(GAUGE_WORK *gauge)
{
	u8 *level_buf, *dest_buf;
	NNSG2dImageProxy * image;
	int size, i, t, k;
	
	//�W�J�̈�m��
	size = LEVEL_KETA_MAX * 0x20;
	level_buf = sys_AllocMemory(HEAPID_BATTLE, size);
	dest_buf = sys_AllocMemory(HEAPID_BATTLE, size * 2);
	MI_CpuFill8(level_buf, LEVEL_BACK_COLOR | (LEVEL_BACK_COLOR << 4), size);
	
	NUMFONT_WriteNumberCGXOnly(BattleWorkGF_BGL_NumFontLVGet(gauge->bw),
		gauge->level, LEVEL_KETA_MAX, NUMFONT_MODE_LEFT, level_buf);
	
	//�`�����ꂽ�����o�b�t�@��VRAM�ɒ�����
	{
		void *obj_vram;
		u8 *high, *low;
		
		obj_vram = G2_GetOBJCharPtr();
		image = CLACT_ImageProxyGet(gauge->cap->act);

		//Vram���烁�����̈�Ɉ�x�R�s�[
		MI_CpuCopy16((void*)((u32)obj_vram + LvTrans[gauge->type][0].pos
			+ image->vramLocation.baseAddrOfVram[NNS_G2D_VRAM_TYPE_2DMAIN]), 
			dest_buf, LvTrans[gauge->type][0].size);
		MI_CpuCopy16((void*)((u32)obj_vram + LvTrans[gauge->type][1].pos
			+ image->vramLocation.baseAddrOfVram[NNS_G2D_VRAM_TYPE_2DMAIN]), 
			&dest_buf[size], LvTrans[gauge->type][1].size);

		//�������̈�ɃR�s�[�������̂ɐ����t�H���g����������
		k = 0;
		for(t = 0; t < size; t += 32){
			for(i = 0; i < 16; i++){
				dest_buf[t + 16 + i] = level_buf[k];
				dest_buf[t + i + size] = level_buf[k + 16];
				k++;
			}
			k += 16;
		}
		//�o���オ�������̂�Vram�֏����߂�
		high = dest_buf;
		low = &dest_buf[size];
		MI_CpuCopy16(high, (void*)((u32)obj_vram + LvTrans[gauge->type][0].pos
			+ image->vramLocation.baseAddrOfVram[NNS_G2D_VRAM_TYPE_2DMAIN]), 
			LvTrans[gauge->type][0].size);
		MI_CpuCopy16(low, (void*)((u32)obj_vram + LvTrans[gauge->type][1].pos
			+ image->vramLocation.baseAddrOfVram[NNS_G2D_VRAM_TYPE_2DMAIN]), 
			LvTrans[gauge->type][1].size);
	}
	
	//�W�J�̈���
	sys_FreeMemoryEz(level_buf);
	sys_FreeMemoryEz(dest_buf);
}

//--------------------------------------------------------------
/**
 * @brief   �Q�[�W�p�[�c�`��F����HP
 * @param   gauge		�Q�[�W���[�N�ւ̃|�C���^
 * @param   hp			�\������HP
 */
//--------------------------------------------------------------
static void GaugeParts_HPDraw(GAUGE_WORK *gauge, u32 hp)
{
	u8 *alloc_buf;
	NNSG2dImageProxy * image;
	
	//�W�J�̈�m��
	alloc_buf = sys_AllocMemory(HEAPID_BATTLE, HP_KETA_MAX * 0x20);
	MI_CpuFill8(alloc_buf, HP_BACK_COLOR | (HP_BACK_COLOR << 4), HP_KETA_MAX * 0x20);
	
	NUMFONT_WriteNumberCGXOnly(BattleWorkGF_BGL_NumFontHPGet(gauge->bw),
		hp, HP_KETA_MAX, NUMFONT_MODE_SPACE, alloc_buf);
	
	//�`�����ꂽ�����o�b�t�@��VRAM�ɒ�����
	{
		void *obj_vram;
		u8 *high;
		
		obj_vram = G2_GetOBJCharPtr();
		image = CLACT_ImageProxyGet(gauge->cap->act);
		high = alloc_buf;
		//1���ڏ�������
		MI_CpuCopy16(high, (void*)((u32)obj_vram + HPTrans[gauge->type][0].pos
			+ image->vramLocation.baseAddrOfVram[NNS_G2D_VRAM_TYPE_2DMAIN]), 
			HPTrans[gauge->type][0].size);
		//2���ڏ�������
		MI_CpuCopy16(&high[HPTrans[gauge->type][0].size], 
			(void*)((u32)obj_vram + HPTrans[gauge->type][1].pos
			+ image->vramLocation.baseAddrOfVram[NNS_G2D_VRAM_TYPE_2DMAIN]), 
			HPTrans[gauge->type][1].size);
	}
	
	//�W�J�̈���
	sys_FreeMemoryEz(alloc_buf);
}

//--------------------------------------------------------------
/**
 * @brief   �Q�[�W�p�[�c�`��F����HP
 * @param   gauge		�Q�[�W���[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
static void GaugeParts_HPMaxDraw(GAUGE_WORK *gauge)
{
	u8 *alloc_buf;
	NNSG2dImageProxy * image;
	
	//�W�J�̈�m��
	alloc_buf = sys_AllocMemory(HEAPID_BATTLE, HP_KETA_MAX * 0x20);
	MI_CpuFill8(alloc_buf, HPMAX_BACK_COLOR | (HPMAX_BACK_COLOR << 4), HP_KETA_MAX * 0x20);
	
	NUMFONT_WriteNumberCGXOnly(BattleWorkGF_BGL_NumFontHPGet(gauge->bw),
		gauge->hpmax, HP_KETA_MAX, NUMFONT_MODE_LEFT, alloc_buf);
	
	//�`�����ꂽ�����o�b�t�@��VRAM�ɒ�����
	{
		void *obj_vram;
		u8 *high;
		
		obj_vram = G2_GetOBJCharPtr();
		image = CLACT_ImageProxyGet(gauge->cap->act);
		high = alloc_buf;
		//��������
		MI_CpuCopy16(high, (void*)((u32)obj_vram + HPMaxTrans[gauge->type].pos
			+ image->vramLocation.baseAddrOfVram[NNS_G2D_VRAM_TYPE_2DMAIN]), 
			HPMaxTrans[gauge->type].size);
	}
	
	//�W�J�̈���
	sys_FreeMemoryEz(alloc_buf);
}

//--------------------------------------------------------------
/**
 * @brief   �Q�[�W�p�[�c�`��F����
 * @param   gauge		�Q�[�W���[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
static void GaugeParts_SexDraw(GAUGE_WORK *gauge)
{
	NNSG2dImageProxy * image;
	const u8 *parts_sex;
	
	if(gauge->sex == PARA_MALE){
		parts_sex = GetGaugePartsAdrs(GP_SEX_MALE);
	}
	else if(gauge->sex == PARA_FEMALE){
		parts_sex = GetGaugePartsAdrs(GP_SEX_FEMALE);
	}
	else{
		parts_sex = GetGaugePartsAdrs(GP_SEX_UNK);
	}
	
	//�`�����ꂽ�����o�b�t�@��VRAM�ɒ�����
	{
		void *obj_vram;
		
		obj_vram = G2_GetOBJCharPtr();
		image = CLACT_ImageProxyGet(gauge->cap->act);
		
		//��������
		MI_CpuCopy16(parts_sex, (void*)((u32)obj_vram + SexTrans[gauge->type][0].pos
			+ image->vramLocation.baseAddrOfVram[NNS_G2D_VRAM_TYPE_2DMAIN]), 
			SexTrans[gauge->type][0].size);
		MI_CpuCopy16(&parts_sex[0x20], (void*)((u32)obj_vram + SexTrans[gauge->type][1].pos
			+ image->vramLocation.baseAddrOfVram[NNS_G2D_VRAM_TYPE_2DMAIN]), 
			SexTrans[gauge->type][1].size);
	}
}

//--------------------------------------------------------------
/**
 * @brief   �Q�[�W�p�[�c�`��F�Q�b�g�ς݃}�[�N
 * @param   gauge		�Q�[�W���[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
static void GaugeParts_GetBallDraw(GAUGE_WORK *gauge)
{
	NNSG2dImageProxy * image;
	const u8 *parts_ball;
	
	if(gauge->getball == TRUE){
		parts_ball = GetGaugePartsAdrs(GP_GETBALL);
	}
	else{
		parts_ball = GetGaugePartsAdrs(GP_NON_GETBALL);
	}
	
	//�`�����ꂽ�����o�b�t�@��VRAM�ɒ�����
	{
		void *obj_vram;
		
		obj_vram = G2_GetOBJCharPtr();
		image = CLACT_ImageProxyGet(gauge->cap->act);
		
		//��������
		MI_CpuCopy16(parts_ball, (void*)((u32)obj_vram + GetBallTrans[gauge->type].pos
			+ image->vramLocation.baseAddrOfVram[NNS_G2D_VRAM_TYPE_2DMAIN]), 
			GetBallTrans[gauge->type].size);
	}
}

//--------------------------------------------------------------
/**
 * @brief   �Q�[�W�p�[�c�`��F���
 * @param   gauge		�Q�[�W���[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
static void GaugeParts_StatusDraw(GAUGE_WORK *gauge, int gp_num)
{
	NNSG2dImageProxy * image;
	const u8 *parts_status;
	
	parts_status = GetGaugePartsAdrs(gp_num);
	
	//�`�����ꂽ�����o�b�t�@��VRAM�ɒ�����
	{
		void *obj_vram;
		
		obj_vram = G2_GetOBJCharPtr();
		image = CLACT_ImageProxyGet(gauge->cap->act);
		
		//��������
		MI_CpuCopy16(parts_status, (void*)((u32)obj_vram + StatusTrans[gauge->type].pos
			+ image->vramLocation.baseAddrOfVram[NNS_G2D_VRAM_TYPE_2DMAIN]), 
			StatusTrans[gauge->type].size);
	}
}

//--------------------------------------------------------------
/**
 * @brief   �Q�[�W�p�[�c�`��F�u�T�t�@���{�[���v
 * @param   gauge		�Q�[�W���[�N�ւ̃|�C���^
 * @param   draw_flag
 */
//--------------------------------------------------------------
static void GaugeParts_SafariballDraw(GAUGE_WORK *gauge, u32 draw_flag)
{
	GF_BGL_INI *bgl;
	u8 *buf;
	NNSG2dImageProxy * image;
	GF_BGL_BMPWIN bmpwin;
	MSGDATA_MANAGER *msg_man;
	STRBUF *str_src;
	
	bgl = BattleWorkGF_BGL_INIGet(gauge->bw);
	msg_man = BattleWorkFightMsgGet(gauge->bw);
	
	//������W�J
	if(draw_flag & GAUGE_DRAW_SAFARIBALL){
		str_src = MSGMAN_AllocString(msg_man, SafariBallMsg);
	}
	else{
		str_src = MSGMAN_AllocString(msg_man, ParkBallMsg);
	}
	
	//�o�b�t�@��BMP�f�[�^�W�J
	GF_BGL_BmpWinObjAdd(bgl, &bmpwin, SAFARIBALL_SIZE_X, SAFARIBALL_SIZE_Y, 
		SAFARIBALL_CHAR_OFFSET, SAFARIBALL_BACK_COLOR);
	GF_STR_PrintExpand(&bmpwin, FONT_SYSTEM, str_src, 0, 0, MSG_NO_PUT, SAFARIBALL_FONT_COLOR, GAUGE_FONT_MARGIN, 0, NULL);
	buf = bmpwin.chrbuf;
	
	//�`�����ꂽ�����o�b�t�@��VRAM�ɒ�����
	{
		void *obj_vram;
		u8 *high, *low;
		
		obj_vram = G2_GetOBJCharPtr();
		image = CLACT_ImageProxyGet(gauge->cap->act);
		high = buf;
		low = &buf[SAFARIBALL_SIZE_X * 0x20];
		//����
		MI_CpuCopy16(high, (void*)((u32)obj_vram + SafariballTrans[0].pos
			+ image->vramLocation.baseAddrOfVram[NNS_G2D_VRAM_TYPE_2DMAIN]), 
			SafariballTrans[0].size);
		MI_CpuCopy16(low, (void*)((u32)obj_vram + SafariballTrans[1].pos
			+ image->vramLocation.baseAddrOfVram[NNS_G2D_VRAM_TYPE_2DMAIN]), 
			SafariballTrans[1].size);
		//�E��
		MI_CpuCopy16(&high[SafariballTrans[0].size], 
			(void*)((u32)obj_vram + SafariballTrans[2].pos
			+ image->vramLocation.baseAddrOfVram[NNS_G2D_VRAM_TYPE_2DMAIN]), 
			SafariballTrans[2].size);
		MI_CpuCopy16(&low[SafariballTrans[1].size], 
			(void*)((u32)obj_vram + SafariballTrans[3].pos
			+ image->vramLocation.baseAddrOfVram[NNS_G2D_VRAM_TYPE_2DMAIN]), 
			SafariballTrans[3].size);
	}
	
	//BMP�f�[�^���
	GF_BGL_BmpWinDel(&bmpwin);
	//������o�b�t�@���
	STRBUF_Delete(str_src);
}

//--------------------------------------------------------------
/**
 * @brief   �Q�[�W�p�[�c�`��F�u�̂���@�������v
 * @param   gauge		�Q�[�W���[�N�ւ̃|�C���^
 * @param   draw_flag
 */
//--------------------------------------------------------------
static void GaugeParts_SafariNokoriDraw(GAUGE_WORK *gauge, u32 draw_flag)
{
	GF_BGL_INI *bgl;
	u8 *buf;
	NNSG2dImageProxy * image;
	GF_BGL_BMPWIN bmpwin;
	MSGDATA_MANAGER *msg_man;
	STRBUF *nokori_p, *nokori_src;
	WORDSET *wordset;
	
	bgl = BattleWorkGF_BGL_INIGet(gauge->bw);
	msg_man = BattleWorkFightMsgGet(gauge->bw);
	wordset = BattleWorkWORDSETGet(gauge->bw);
	
	//������W�J
	nokori_p = STRBUF_Create(BUFLEN_GAUGE_SAFARI_NOKORI, HEAPID_BATTLE);
	if(draw_flag & GAUGE_DRAW_SAFARIBALL){
		nokori_src = MSGMAN_AllocString(msg_man, SafariNokoriMsg);
	}
	else{
		nokori_src = MSGMAN_AllocString(msg_man, ParkNokoriMsg);
	}
	WORDSET_RegisterNumber(wordset, 0, gauge->safari_nokori, NOKORI_SAFARI_NUM_KETA, 
		NUMBER_DISPTYPE_SPACE, NUMBER_CODETYPE_DEFAULT);
	WORDSET_ExpandStr(wordset, nokori_p, nokori_src);
	
	//�o�b�t�@��BMP�f�[�^�W�J
	GF_BGL_BmpWinObjAdd(bgl, &bmpwin, NOKORI_SIZE_X, NOKORI_SIZE_Y, 
		NOKORI_CHAR_OFFSET, NOKORI_BACK_COLOR);
	GF_STR_PrintExpand(&bmpwin, FONT_SYSTEM, nokori_p, 0, 0, MSG_NO_PUT, NOKORI_FONT_COLOR, GAUGE_FONT_MARGIN, 0, NULL);
	buf = bmpwin.chrbuf;
	
	//�`�����ꂽ�����o�b�t�@��VRAM�ɒ�����
	{
		void *obj_vram;
		u8 *high, *low;
		
		obj_vram = G2_GetOBJCharPtr();
		image = CLACT_ImageProxyGet(gauge->cap->act);
		high = buf;
		low = &buf[NOKORI_SIZE_X * 0x20];
		//����
		MI_CpuCopy16(high, (void*)((u32)obj_vram + NokoriTrans[0].pos
			+ image->vramLocation.baseAddrOfVram[NNS_G2D_VRAM_TYPE_2DMAIN]), 
			NokoriTrans[0].size);
		MI_CpuCopy16(low, (void*)((u32)obj_vram + NokoriTrans[1].pos
			+ image->vramLocation.baseAddrOfVram[NNS_G2D_VRAM_TYPE_2DMAIN]), 
			NokoriTrans[1].size);
		//�E��
		MI_CpuCopy16(&high[NokoriTrans[0].size], 
			(void*)((u32)obj_vram + NokoriTrans[2].pos
			+ image->vramLocation.baseAddrOfVram[NNS_G2D_VRAM_TYPE_2DMAIN]), 
			NokoriTrans[2].size);
		MI_CpuCopy16(&low[NokoriTrans[1].size], 
			(void*)((u32)obj_vram + NokoriTrans[3].pos
			+ image->vramLocation.baseAddrOfVram[NNS_G2D_VRAM_TYPE_2DMAIN]), 
			NokoriTrans[3].size);
	}
	
	//BMP�f�[�^���
	GF_BGL_BmpWinDel(&bmpwin);
	//������o�b�t�@���
	STRBUF_Delete(nokori_p);
	STRBUF_Delete(nokori_src);
	
#if 0
	//�]��
	image = CLACT_ImageProxyGet(gauge->cap->act);
	AddVramTransferManager(
		NNS_GFD_DST_2D_OBJ_CHAR_MAIN,
		image->vramLocation.baseAddrOfVram[NNS_G2D_VRAM_TYPE_2DMAIN],
		buf,
		NOKORI_BYTE_SIZE
		);
#endif
}

//--------------------------------------------------------------
/**
 * @brief   �Q�[�W�p�[�c�`��F�f�o�b�O�p�̐��l�`��
 * @param   gauge		�Q�[�W���[�N�ւ̃|�C���^
 * @param   num			�\�����鐔�l
 */
//--------------------------------------------------------------
void GaugeParts_DebugNumDraw(GAUGE_WORK *gauge, u32 num)
{
#ifdef PM_DEBUG
	u8 *alloc_buf;
	NNSG2dImageProxy * image;
	
	if(gauge->cap == NULL){
		return;
	}
	
	//�W�J�̈�m��
	alloc_buf = sys_AllocMemory(HEAPID_BATTLE, DEBUG_NUM_KETA_MAX * 0x20);
	MI_CpuFill8(alloc_buf, HP_BACK_COLOR | (HP_BACK_COLOR << 4), DEBUG_NUM_KETA_MAX * 0x20);
	
	NUMFONT_WriteNumberCGXOnly(BattleWorkGF_BGL_NumFontHPGet(gauge->bw),
		num, DEBUG_NUM_KETA_MAX, NUMFONT_MODE_LEFT, alloc_buf);
	
	//�`�����ꂽ�����o�b�t�@��VRAM�ɒ�����
	{
		void *obj_vram;
		u8 *high;
		
		obj_vram = G2_GetOBJCharPtr();
		image = CLACT_ImageProxyGet(gauge->cap->act);
		high = alloc_buf;
		//1���ڏ�������
		MI_CpuCopy16(high, (void*)((u32)obj_vram + DebugNumTrans[gauge->type].pos
			+ image->vramLocation.baseAddrOfVram[NNS_G2D_VRAM_TYPE_2DMAIN]), 
			DebugNumTrans[gauge->type].size);
	}
	
	//�W�J�̈���
	sys_FreeMemoryEz(alloc_buf);
#endif
}







//==============================================================================
//
//	���F�Q�[�W�v�Z���[�`��	(�G�������h����ڐA)
//
//==============================================================================

//--------------------------------------------------------------
/**
 * @brief   HP�Q�[�W�̃o�[�̕�������������
 *
 * @param   gauge			�Q�[�W���[�N�ւ̃|�C���^
 * @param   req_data		GAUGE_REQ_???
 *
 * @retval  -1=�I���B�@-1�ȊO=�v�Z�r���̐���(��ʂɕ\�����鐔�l)
 */
//--------------------------------------------------------------
static s32 GaugeOBJ(GAUGE_WORK *gauge, int req_data)
{
	s32 temp;
	s32 dotto_offset;
	
	//�Q�[�W�v�Z
	if(req_data == GAUGE_REQ_HP){
		temp = GaugeProc(gauge->hpmax, gauge->hp, gauge->damage, 
			&gauge->hp_work, BAR_HP_CHARMAX, 1);
	}
	else{	//GAUGE_REQ_EXP
		//EXP�ް�ނ͌v�Z���l���傫���̂ŁA�ޯĂ̵̾�Ă��牽Sync�ŏI��点�邩�����߂�
		dotto_offset = DottoOffsetCalc(gauge->exp, gauge->add_exp, gauge->max_exp,
				BAR_EXP_CHARMAX);
		if(dotto_offset == 0)
			dotto_offset = 1;
		dotto_offset = abs(gauge->add_exp / dotto_offset);
		temp = GaugeProc(gauge->max_exp, gauge->exp, gauge->add_exp,
				&gauge->exp_work, BAR_EXP_CHARMAX, dotto_offset);
	}
	
	//�Q�[�W�`��
	if(req_data == GAUGE_REQ_HP && gauge->num_mode == TRUE){
		;	//HP�����\�����[�h�Ȃ�΃Q�[�W�`��͍s��Ȃ�
	}
	else{
		PutGaugeOBJ(gauge, req_data);
	}
	
	if(temp == -1){
		if(req_data == GAUGE_REQ_HP){
			gauge->hp_work = 0;
		}
		else{
			gauge->exp_work = 0;
		}
	}
	return temp;
}


//--------------------------------------------------------------
/**
 * @brief   �Q�[�W�o�[�`��
 *
 * @param   gauge		�Q�[�W���[�N�ւ̃|�C���^
 * @param   req			GAUGE_REQ_???
 */
//--------------------------------------------------------------
static void PutGaugeOBJ(GAUGE_WORK *gauge, u8 req)
{
	u8 i;
	u8 gauge_chr[BAR_ALL_MAX];
	u8 parts, parts_num;
	u8 put_dot;
	u8 level;
	const u8 *parts_address;
	void *obj_vram;
	NNSG2dImageProxy * image;
	int one_loop;
	
	obj_vram = G2_GetOBJCharPtr();
	image = CLACT_ImageProxyGet(gauge->cap->act);
	
	switch(req){
	case GAUGE_REQ_HP:
		put_dot = PutGaugeProc(gauge->hpmax, gauge->hp, gauge->damage,
			 &gauge->hp_work, gauge_chr, BAR_HP_CHARMAX);

		//�Q�[�W�̕\���h�b�g������F�ƃp�[�c�A�h���X���擾
		{
			int dotto_color;
			
			dotto_color = GetGaugeDottoColor(put_dot, GAUGE_HP_DOTTOMAX);
			switch(dotto_color){
			case HP_DOTTO_GREEN:
				parts_num = GP_HPBAR_GREEN;
				break;
			case HP_DOTTO_YELLOW:
				parts_num = GP_HPBAR_YELLOW;
				break;
			case HP_DOTTO_RED:
			default:
				parts_num = GP_HPBAR_RED;
				break;
			}
		}
		parts_address = GetGaugePartsAdrs(parts_num);
		
		one_loop = HPBarTrans[gauge->type][0].size / 0x20;
		for(i = 0; i < BAR_HP_CHARMAX; i++){
			if(i < one_loop){
				MI_CpuCopy16(parts_address + (gauge_chr[i] << 5),
					(void*)((u32)obj_vram + HPBarTrans[gauge->type][0].pos + (i * 0x20)
					+ image->vramLocation.baseAddrOfVram[NNS_G2D_VRAM_TYPE_2DMAIN]),
					0x20);
			}
			else{
				MI_CpuCopy16(parts_address + (gauge_chr[i] << 5),
					(void*)((u32)obj_vram + HPBarTrans[gauge->type][1].pos + ((i-one_loop) * 0x20)
					+ image->vramLocation.baseAddrOfVram[NNS_G2D_VRAM_TYPE_2DMAIN]),
					0x20);
			}
		}
		break;
	
	case GAUGE_REQ_EXP:
		PutGaugeProc(gauge->max_exp, gauge->exp, gauge->add_exp,
				&gauge->exp_work, gauge_chr, BAR_EXP_CHARMAX);
		level = gauge->level;
		if(level == 100){
			for(i = 0; i < BAR_EXP_CHARMAX; i++){
				gauge_chr[i] = 0;
			}
		}
		
		parts_address = GetGaugePartsAdrs(GP_EXP);
		for(i = 0; i < BAR_EXP_CHARMAX; i++){
			if(i < EXPBAR_NEXT_OAM){
				MI_CpuCopy16(parts_address + (gauge_chr[i] << 5),
					(void*)((u32)obj_vram + EXPBAR_FAST_HIGH + (i * 0x20)
					+ image->vramLocation.baseAddrOfVram[NNS_G2D_VRAM_TYPE_2DMAIN]),
					0x20);
			}
			else{
				MI_CpuCopy16(parts_address + (gauge_chr[i] << 5),
					(void*)((u32)obj_vram + EXPBAR_SECOND_HIGH + ((i-EXPBAR_NEXT_OAM) * 0x20)
					+ image->vramLocation.baseAddrOfVram[NNS_G2D_VRAM_TYPE_2DMAIN]),
					0x20);
			}
		}
	#if 0
		for(i = 0; i < BAR_EXP_CHARMAX; i++){
			if(i < 4){
				CpuCopy(
					(void*)(GetGaugePartsAdrs(GP_EXPBAR) + (gauge_chr[i] << 5)),
					((ActWork[gwork[client_no].actno].oamData.CharNo +0x24 + i) << 5)
					+ OBJ_MODE0_VRAM, 0x20, 32);
			}
			else{
				CpuCopy(
					(void*)(GetGaugePartsAdrs(GP_EXPBAR) + (gauge_chr[i] << 5)),
					((ActWork[gwork[client_no].actno].oamData.CharNo +0x60 + i-4) << 5)
					+ OBJ_MODE0_VRAM, 0x20, 32);
			}
		}
	#endif
		break;
	}
}

//--------------------------------------------------------------
/**
 * @brief   �Q�[�W�o�[�v�Z
 *
 * @param   MaxHP		�ő�HP
 * @param   NowHP		����HP(�v�Z�O��HP)
 * @param   beHP		�_���[�W(-�Ń_���[�W�A+�Ȃ��)
 * @param   HP_Work		��Ɨp���[�N
 * @param   GaugeMax	�Q�[�W�̃L�����N�^��
 * @param   add_dec		�ް�ނ������Z���Ă����l GaugeDotto��GaugeMax�ȉ��̏ꍇ�͖�������
 *
 * @retval  -1 = �I��	����ȊO�F�v�Z�r���̐���(��ʂɏo�����l)
 */
//--------------------------------------------------------------
static s32 GaugeProc(s32 MaxHP, s32 NowHP, s32 beHP, s32 *HP_Work, u8 GaugeMax, u16 add_dec)
{
	s32 endHP;	//2002.09.14(�y)
	s32 ret;
	u8 GaugeMaxDot;
	s32 add_hp;
	
	GaugeMaxDot = GaugeMax * GAUGE_DOTTO;
	
	//-- HP_Work��HP_WORK_INIT_VALUE�̎��͏���Ȃ̂Ń��[�N�������� --//
	if(*HP_Work == HP_WORK_INIT_VALUE){
		if(MaxHP < GaugeMaxDot){
			*HP_Work = NowHP << 8;
		}
		else{
			*HP_Work = NowHP;
		}
	}

	//-- �I������ --//
	endHP = NowHP - beHP;
	if(endHP < 0)
		endHP = 0;
	else if(endHP > MaxHP)
		endHP = MaxHP;
	
	if(MaxHP < GaugeMaxDot){			//����������������
		if(endHP == (*HP_Work >> 8) && (*HP_Work & 0xff) == 0)
			return (-1);
	}
	else{
		if(endHP == *HP_Work)
			return (-1);
	}
	//-- �I�������I�� --//
	
	if(MaxHP < GaugeMaxDot){
		add_hp = MaxHP * 0x100 / GaugeMaxDot;
		if(beHP < 0){	//�ް�މ�
			*HP_Work += add_hp;
			ret = *HP_Work >> 8;
			if(ret >= endHP){	//�����������Ă���̂ŵ��ް�۰����
				*HP_Work = endHP << 8;
				ret = endHP;
			}
		}
		else{					//�ް�ތ���
			*HP_Work -= add_hp;
			ret = *HP_Work >> 8;
			if((*HP_Work & 0xff) > 0)	//��������������Ȃ班���J��グ�ŕ\��
				ret++;
			if(ret <= endHP){	//�����������Ă���̂ŵ��ް�۰����
				*HP_Work = endHP << 8;
				ret = endHP;
			}
		}
	}
	else{
		if(beHP < 0){		//�ް�މ�
			*HP_Work += add_dec;
			if(*HP_Work > endHP)
				*HP_Work = endHP;
		}
		else{				//�ް�ތ���
			*HP_Work -= add_dec;
			if(*HP_Work < endHP)
				*HP_Work = endHP;
		}
		ret = *HP_Work;
	}
	return ret;
}

//--------------------------------------------------------------
/**
 * @brief   �Q�[�W�\���v�Z
 *
 * @param   MaxHP		�ő�HP
 * @param   NowHP		����HP(�v�Z�O��HP)
 * @param   beHP		�_���[�W(-�Ń_���[�W�A+�Ȃ��)
 * @param   HP_Work		��Ɨp���[�N
 * @param   gauge_chr	�Q�[�W�\�����ʑ����(GaugeMax���̔z��v�f�����K�v)
 * @param   GaugeMax	�Q�[�W�̃L�����N�^��
 *
 * @retval  �\������h�b�g��
 *
 * gauge_chr�ɓ���l�́A0:����ۂ̹ް��  1:1�ޯĂ̹ް�� 2:2�ޯĂ̹ް�� ��� 8:8�ޯ�(����)�̹ް��
 */
//--------------------------------------------------------------
static u8 PutGaugeProc(s32 MaxHP, s32 NowHP, s32 beHP, s32 *HP_Work, u8 *gauge_chr, u8 GaugeMax)
{
	int i;
	u32 GaugeMaxDot;
	u32 put_dot, dot_ret;		//�\�������ޯĐ�
	s32 AfterHP;
	
	AfterHP = NowHP - beHP;
	if(AfterHP < 0){
		AfterHP = 0;
	}
	else if(AfterHP > MaxHP){
		AfterHP = MaxHP;
	}

	GaugeMaxDot = GAUGE_DOTTO * GaugeMax;
	for(i = 0; i < GaugeMax; i++){	//�󔒹ް�ނŏ�����
		gauge_chr[i] = 0;
	}

	//���������̃h�b�g�擾�̌v�Z����ύX������GetNumDotto�̌v�Z�����ύX���邱��!!
	if(MaxHP < GaugeMaxDot){	// by 2002.07.11(��) matsuda
		put_dot = (*HP_Work * GaugeMaxDot / MaxHP) >> 8;
	}
	else{
		put_dot = *HP_Work * GaugeMaxDot / MaxHP;
	}
	dot_ret = put_dot;
	//�ޯČv�Z�ł�0�ł��A���ۂ�HP��1�ȏ゠��Ȃ�1�ޯĂ̹ް�ނ�\������
	if(put_dot == 0 && AfterHP > 0){
		gauge_chr[0] = 1;
		dot_ret = 1;
	}else{
		for(i = 0; i < GaugeMax; i++){
			if(put_dot >= GAUGE_DOTTO){
				gauge_chr[i] = 8;
				put_dot -= GAUGE_DOTTO;
			}
			else{
				gauge_chr[i] = put_dot;
				break;	//�ޯĂ��s�����̂Ŕ�����
			}
		}
	}
	return dot_ret;
}

//--------------------------------------------------------------
/**
 * @brief   �ް�ތv�Z�O�ƌv�Z��̍ŏI�I���ޯĂ̍��������߂�
 *
 * @param   nowHP		����HP(�v�Z�O��HP)
 * @param   beHP		�_���[�W(-�Ń_���[�W�A+�Ȃ��)
 * @param   MaxHP		�ő�HP
 * @param   GaugeMax	�Q�[�W�̃L�����N�^��
 *
 * @retval  �h�b�g����
 */
//--------------------------------------------------------------
static u32 DottoOffsetCalc(s32 nowHP, s32 beHP, s32 MaxHP, u8 GaugeMax)
{
	s8 now_dotto, end_dotto;
	u8 GaugeMaxDot;
	s32 endHP;
	
	GaugeMaxDot = GaugeMax * GAUGE_DOTTO;

	endHP = nowHP - beHP;
	if(endHP < 0)
		endHP = 0;
	else if(endHP > MaxHP)
		endHP = MaxHP;
	now_dotto = nowHP * GaugeMaxDot / MaxHP;
	end_dotto = endHP * GaugeMaxDot / MaxHP;
	return (abs(now_dotto - end_dotto));
}

//--------------------------------------------------------------
/**
 * @brief   �w��p�[�c�̃O���t�B�b�N�A�h���X���擾����
 * @param   parts_num		�p�[�c�ԍ�
 * @retval  �p�[�c�̃O���t�B�b�N�A�h���X
 */
//--------------------------------------------------------------
static const u8 * GetGaugePartsAdrs(int parts_num)
{
	return &gage_parts[parts_num * 0x20];
}

//--------------------------------------------------------------
/**
 * @brief   �N���C�A���g�^�C�v����Q�[�W�^�C�v�����o��
 * @param   client_type		�N���C�A���g�^�C�v
 * @retval  �Q�[�W�^�C�v
 */
//--------------------------------------------------------------
u8 Gauge_TypeGet(int client_type, u32 fight_type)
{
	switch(client_type){
	case CLIENT_TYPE_AA:
		if(fight_type & FIGHT_TYPE_POKE_PARK){
			return GAUGE_TYPE_PARK;
		}
		if(fight_type & FIGHT_TYPE_SAFARI){
			return GAUGE_TYPE_SAFARI;
		}
		return GAUGE_TYPE_AA;
	case CLIENT_TYPE_BB:
		return GAUGE_TYPE_BB;
	case CLIENT_TYPE_A:
		return GAUGE_TYPE_A;
	case CLIENT_TYPE_B:
		return GAUGE_TYPE_B;
	case CLIENT_TYPE_C:
		return GAUGE_TYPE_C;
	case CLIENT_TYPE_D:
		return GAUGE_TYPE_D;
	default:
		GF_ASSERT(0 && "�p�ӂ���Ă��Ȃ��N���C�A���g�^�C�v���n����Ă��܂�");
		return NULL;
	}
	return 0;
}

//--------------------------------------------------------------
/**
 * @brief   �Q�[�W�^�C�v����Q�[�W�{�̂̃A�N�^�[�w�b�_�|�C���^���擾����
 * @param   gauge_type		�Q�[�W�^�C�v
 * @retval  �A�N�^�[�w�b�_�|�C���^
 */
//--------------------------------------------------------------
static const TCATS_OBJECT_ADD_PARAM_S * Sub_GaugeObjHeadGet(u8 gauge_type)
{
	const TCATS_OBJECT_ADD_PARAM_S *obj_head;

	//���\�[�X�ǂݍ���
	switch(gauge_type){
	case GAUGE_TYPE_AA:
		obj_head = &GaugeObjParam_aa;
		break;
	case GAUGE_TYPE_BB:
		obj_head = &GaugeObjParam_bb;
		break;
	case GAUGE_TYPE_A:
		obj_head = &GaugeObjParam_a;
		break;
	case GAUGE_TYPE_B:
		obj_head = &GaugeObjParam_b;
		break;
	case GAUGE_TYPE_C:
		obj_head = &GaugeObjParam_c;
		break;
	case GAUGE_TYPE_D:
		obj_head = &GaugeObjParam_d;
		break;
	case GAUGE_TYPE_SAFARI:
	case GAUGE_TYPE_PARK:
		obj_head = &GaugeObjParam_Safari;
		break;
	default:
		GF_ASSERT(0 && "�p�ӂ���Ă��Ȃ��Q�[�W�^�C�v���n����Ă��܂�");
		return NULL;
	}
	return obj_head;
}

//--------------------------------------------------------------
/**
 * @brief   �Q�[�W�^�C�v������̃A�N�^�[�w�b�_�|�C���^���擾����
 * @param   gauge_type		�Q�[�W�^�C�v
 * @retval  �A�N�^�[�w�b�_�|�C���^(��󂪕K�v�Ȃ��^�C�v�̏ꍇ��NULL)
 */
//--------------------------------------------------------------
static const TCATS_OBJECT_ADD_PARAM_S * Sub_ArrowObjHeadGet(u8 gauge_type)
{
	const TCATS_OBJECT_ADD_PARAM_S *obj_head;

	//���\�[�X�ǂݍ���
	switch(gauge_type){
	case GAUGE_TYPE_AA:
	case GAUGE_TYPE_A:
	case GAUGE_TYPE_C:
	case GAUGE_TYPE_SAFARI:
	case GAUGE_TYPE_PARK:
		obj_head = &ArrowParam_aa;
		break;
	case GAUGE_TYPE_BB:		//�G���͖��K�v�Ȃ�
	case GAUGE_TYPE_B:
	case GAUGE_TYPE_D:
		return NULL;
	default:
		GF_ASSERT(0 && "�p�ӂ���Ă��Ȃ��Q�[�W�^�C�v���n����Ă��܂�");
		return NULL;
	}
	return obj_head;
}





//==============================================================================
//
//	�G�t�F�N�g�֘A�F���x���A�b�v
//
//==============================================================================
///�Q�[�W���x���A�b�v�FEVY���Z�l
#define GAUGE_LEVELUP_ADD_EVY		(4)
///�Q�[�W���x���A�b�v�F�J���[�ύX�J�n�ʒu(�J���[�P��)
#define GAUGE_LEVELUP_COLOR_NO		(0xf)
///�Q�[�W���x���A�b�v�F�J���[�ύX����F�̐�
#define GAUGE_LEVELUP_COLOR_NUM		(1)
///�Q�[�W���x���A�b�v�F�ύX��̃J���[
#define GAUGE_LEVELUP_COLOR			(0x73a5)

///�Q�[�W���x���A�b�v�G�t�F�N�g�p�\����
typedef struct{
	GAUGE_WORK *gauge;		///<�Q�[�W���[�N�ւ̃|�C���^
	u8 *end_flag;			///<�I����̃t���O���Z�b�g���郏�[�N�ւ̃|�C���^
	u8 seq;					///<�V�[�P���X�ԍ�
	u8 pal_no;				///<�p���b�g�ԍ�
	s8 evy;					///<����EVY�l
}GAUGE_LEVELUP_EFF_WORK;

//--------------------------------------------------------------
/**
 * @brief   �Q�[�W���x���A�b�v�G�t�F�N�g�J�n
 *
 * @param   gauge			�Q�[�W���[�N�ւ̃|�C���^
 * @param   end_flag		�I���t���O���Z�b�g���郏�[�N�ւ̃|�C���^
 *
 * �G�t�F�N�g���I�������end_flag�ɓn�������[�N��TRUE���Z�b�g����܂�
 */
//--------------------------------------------------------------
void Gauge_LevelUpEffectStart(GAUGE_WORK *gauge, u8 *end_flag)
{
	GAUGE_LEVELUP_EFF_WORK *level_eff;
	
	*end_flag = FALSE;
	
	level_eff = sys_AllocMemory(HEAPID_BATTLE, sizeof(GAUGE_LEVELUP_EFF_WORK));
	MI_CpuClear8(level_eff, sizeof(GAUGE_LEVELUP_EFF_WORK));
	
	level_eff->gauge = gauge;
	level_eff->end_flag = end_flag;
	
	TCB_Add(GaugeLevelUpEffTask, level_eff, TCBPRI_GAUGE_LEVELUP_EFF);
}

//--------------------------------------------------------------
/**
 * @brief   �Q�[�W���x���A�b�v�G�t�F�N�g�F���C���^�X�N
 * @param   tcb			TCB�ւ̃|�C���^
 * @param   work		GAUGE_LEVELUP_EFF_WORK
 */
//--------------------------------------------------------------
static void GaugeLevelUpEffTask(TCB_PTR tcb, void *work)
{
	GAUGE_LEVELUP_EFF_WORK *level_eff = work;
	CATS_RES_PTR crp;
	int pal_no;
	PALETTE_FADE_PTR pfd;
	
	crp = BattleWorkCATS_RES_PTRGet(level_eff->gauge->bw);
	pfd = BattleWorkPfdGet(level_eff->gauge->bw);
	
	switch(level_eff->seq){
	case 0:
		pal_no = CATS_PlttID_NoGet(crp, PLTTID_GAUGE_EFF, NNS_G2D_VRAM_TYPE_2DMAIN);
		CATS_ObjectPaletteSetCap(level_eff->gauge->cap, pal_no);
		level_eff->pal_no = pal_no;
		
		level_eff->seq++;
		//break;
		
	case 1:
		level_eff->evy += GAUGE_LEVELUP_ADD_EVY;
		if(level_eff->evy >= 16){
			level_eff->evy = 16;
			level_eff->seq++;
		}
		SoftFadePfd(pfd, FADE_MAIN_OBJ, level_eff->pal_no * 16 + GAUGE_LEVELUP_COLOR_NO, 
			GAUGE_LEVELUP_COLOR_NUM, level_eff->evy, GAUGE_LEVELUP_COLOR);
		break;
	case 2:
		level_eff->evy -= GAUGE_LEVELUP_ADD_EVY;
		if(level_eff->evy <= 0){
			level_eff->evy = 0;
			level_eff->seq++;
		}
		SoftFadePfd(pfd, FADE_MAIN_OBJ, level_eff->pal_no * 16 + GAUGE_LEVELUP_COLOR_NO, 
			GAUGE_LEVELUP_COLOR_NUM, level_eff->evy, GAUGE_LEVELUP_COLOR);
		break;
	
	default:
		pal_no = CATS_PlttID_NoGet(crp, PLTTID_GAUGE, NNS_G2D_VRAM_TYPE_2DMAIN);
		CATS_ObjectPaletteSetCap(level_eff->gauge->cap, pal_no);

		(*(level_eff->end_flag)) = TRUE;

		sys_FreeMemoryEz(work);
		TCB_Delete(tcb);
		return;
	}
}





//==============================================================================
//
//	�G�t�F�N�g�֘A�F����̃Q�[�W�̃J���[���Â�����
//
//==============================================================================
///�Q�[�W�̐F�����F�ɂ�������EVY�l
#define GAUGE_COLOR_BACK_EVY		(8)

//--------------------------------------------------------------
/**
 * @brief   �Q�[�W�̐F�����F�ɂ���
 * @param   gauge		�Q�[�W���[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
void Gauge_ColorBlackSet(GAUGE_WORK *gauge)
{
#if 1		//�F�ς��͂��Ȃ��Ȃ��� 2006.04.11(��)
	return;
#else
	CATS_RES_PTR crp;
	int pal_no;
	PALETTE_FADE_PTR pfd;
	
	if(gauge == NULL){
		return;
	}
	
	crp = BattleWorkCATS_RES_PTRGet(gauge->bw);
	pfd = BattleWorkPfdGet(gauge->bw);
	
	pal_no = CATS_PlttID_NoGet(crp, PLTTID_GAUGE_EFF, NNS_G2D_VRAM_TYPE_2DMAIN);
	SoftFadePfd(pfd, FADE_MAIN_OBJ, pal_no * 16, 16, GAUGE_COLOR_BACK_EVY, 0x0000);
	CATS_ObjectPaletteSetCap(gauge->cap, pal_no);
#endif
}

//--------------------------------------------------------------
/**
 * @brief   �Q�[�W�̐F�����ɖ߂���
 * @param   gauge		�Q�[�W���[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
void Gauge_ColorNormalSet(GAUGE_WORK *gauge)
{
#if 1	//�F�ς��͂��Ȃ��Ȃ��� 2006.04.11(��)
	return;
#else
	CATS_RES_PTR crp;
	int pal_no;
	PALETTE_FADE_PTR pfd;

	if(gauge == NULL){
		return;
	}
	
	crp = BattleWorkCATS_RES_PTRGet(gauge->bw);
	pfd = BattleWorkPfdGet(gauge->bw);
	
	pal_no = CATS_PlttID_NoGet(crp, PLTTID_GAUGE_EFF, NNS_G2D_VRAM_TYPE_2DMAIN);
	SoftFadePfd(pfd, FADE_MAIN_OBJ, pal_no * 16, 16, 0, 0x0000);
	
	pal_no = CATS_PlttID_NoGet(crp, PLTTID_GAUGE, NNS_G2D_VRAM_TYPE_2DMAIN);
	CATS_ObjectPaletteSetCap(gauge->cap, pal_no);
#endif
}

//--------------------------------------------------------------
/**
 * @brief   �Q�[�W��Sin�J�[�u�G�t�F�N�g���Z�b�g����
 * @param   gauge		�Q�[�W���[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
void Gauge_SinCurveSet(GAUGE_WORK *gauge)
{
	if(gauge->sin_tcb != NULL){
		return;
	}
	
	gauge->sin_sec = 0;
	gauge->sin_tcb = TCB_Add(GaugeSinCurveMain, gauge, TCBPRI_HP_GAUGE_SIN_CURVE);
}

//--------------------------------------------------------------
/**
 * @brief   �Q�[�W��Sin�J�[�u�G�t�F�N�g���~������
 * @param   gauge		�Q�[�W���[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
void Gauge_SinCurveStop(GAUGE_WORK *gauge)
{
	if(gauge->sin_tcb != NULL){
		TCB_Delete(gauge->sin_tcb);
		gauge->sin_tcb = NULL;
	}
	gauge->sin_sec = 0;
	Gauge_OffsetPosSet(gauge, 0, 0);
}

//--------------------------------------------------------------
/**
 * @brief   �Q�[�W��Sin�J�[�u���C������
 * @param   tcb			TCB�ւ̃|�C���^
 * @param   work		�Q�[�W���[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
static void GaugeSinCurveMain(TCB_PTR tcb, void *work)
{
	GAUGE_WORK *gauge = work;
	int offset_y;
	
	gauge->sin_sec += GAUGE_SIN_SEC_ADD;
	if(gauge->sin_sec >= 360){
		gauge->sin_sec -= 360;
	}
	
	offset_y = FX_Mul(Sin360(gauge->sin_sec), GAUGE_SIN_FURIHABA_Y) / FX32_ONE;
	Gauge_OffsetPosSet(gauge, 0, offset_y);//MATH_ABS(offset_y));
}

