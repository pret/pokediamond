//==============================================================================
/**
 * @file	gauge.h
 * @brief	�퓬��ʁFHP�Q�[�W�̃w�b�_
 * @author	matsuda
 * @date	2005.09.27(��)
 */
//==============================================================================
#ifndef __GAUGE_H__
#define __GAUGE_H__

#include "system/buflen.h"
#include "client_tool_def.h"



//==============================================================================
//	�萔��`
//==============================================================================
///�Q�[�W�̕W��BG�v���C�I���e�B
#define GAUGE_DEFAULT_BGPRI			(0)

//--------------------------------------------------------------
//	�Q�[�W�^�C�v
//		�N���C�A���g�^�C�v�����l���ύX����Ă��e�[�u���̕��тɉe�����o�Ȃ��悤�ɁA
//		�Q�[�W�^�C�v��ʂɒ�`�B�N���C�A���g�^�C�v����K�؂ȃQ�[�W�^�C�v�����o���悤�ɂ���
//		�e�[�u�����̓Q�[�W�^�C�v�̕��тɏ]���Ă����Έ��S�Ƀf�[�^�擾���s����
//--------------------------------------------------------------
enum{
	GAUGE_TYPE_AA,
	GAUGE_TYPE_BB,
	GAUGE_TYPE_A,
	GAUGE_TYPE_B,
	GAUGE_TYPE_C,
	GAUGE_TYPE_D,
	GAUGE_TYPE_SAFARI,
	GAUGE_TYPE_PARK,
};

///�Q�[�W�X�N���[������
enum{
	GAUGE_SCROLL_IN,		///<�X�N���[��IN
	GAUGE_SCROLL_OUT,		///<�X�N���[��OUT
};


//--------------------------------------------------------------
//	�Q�[�W�p�[�c�`��
//--------------------------------------------------------------
///�Q�[�W�p�[�c�`��t���O�FHP�o�[
#define GAUGE_DRAW_HPBAR		(1 << 0)
///�Q�[�W�p�[�c�`��t���O�F����HP(���l)
#define GAUGE_DRAW_HPNUM		(1 << 1)
///�Q�[�W�p�[�c�`��t���O�F�ő�HP(���l)
#define GAUGE_DRAW_HPNUMMAX		(1 << 2)
///�Q�[�W�p�[�c�`��t���O�F���x��
#define GAUGE_DRAW_LEVEL		(1 << 3)
///�Q�[�W�p�[�c�`��t���O�F���O
#define GAUGE_DRAW_NAME			(1 << 4)
///�Q�[�W�p�[�c�`��t���O�F�o���l
#define GAUGE_DRAW_EXP			(1 << 5)
///�Q�[�W�p�[�c�`��t���O�F����
#define GAUGE_DRAW_SEX			(1 << 6)
///�Q�[�W�p�[�c�`��t���O�F���x������
#define GAUGE_DRAW_LEVEL_FONT	(1 << 7)
///�Q�[�W�p�[�c�`��t���O�F��Ԉُ�
#define GAUGE_DRAW_STATUS		(1 << 8)
///�Q�[�W�p�[�c�`��t���O�F�Q�b�g�ς݃}�[�N
#define GAUGE_DRAW_GETBALL		(1 << 9)
///�Q�[�W�p�[�c�`��t���O�F�u�T�t�@���{�[���v
#define GAUGE_DRAW_SAFARIBALL	(1 << 10)
///�Q�[�W�p�[�c�`��t���O�F�u�̂���@�������v
#define GAUGE_DRAW_SAFARI_NOKORI	(1 << 11)
///�Q�[�W�p�[�c�`��t���O�F�u�p�[�N�{�[���v
#define GAUGE_DRAW_PARKBALL	(1 << 12)
///�Q�[�W�p�[�c�`��t���O�F�u�̂���@�������v
#define GAUGE_DRAW_PARK_NOKORI	(1 << 13)

///�Q�[�W�p�[�c�`��t���O�F�S��
#define GAUGE_DRAW_ALL			(0xffffffff)
///�Q�[�W�p�[�c�`��t���O�F�S��(�T�t�@���p�̑S�r�b�g)
#define GAUGE_DRAW_ALL_SAFARI	(GAUGE_DRAW_SAFARIBALL | GAUGE_DRAW_SAFARI_NOKORI)
///�Q�[�W�p�[�c�`��t���O�F�S��(�|�P�p�[�N�p�̑S�r�b�g)
#define GAUGE_DRAW_ALL_PARK	(GAUGE_DRAW_PARKBALL | GAUGE_DRAW_PARK_NOKORI)


//--------------------------------------------------------------
//	�Q�[�W�̃p�[�c�O���t�B�b�N�̔z�u�ԍ�
//--------------------------------------------------------------
enum{
	GP_HPBAR_GREEN = 2,			///<HP�o�[��
	GP_HPBAR_YELLOW = 0x0b,		///<HP�o�[���F
	GP_HPBAR_RED = 0x14,		///<HP�o�[��
	
	GP_EXP = 0x1d,				///<�o���l
	
	GP_NON_GETBALL = 0x38,		///<�Q�b�g�ς݃}�[�N�Ȃ�
	GP_GETBALL = 0x3b,			///<�Q�b�g�ς݃}�[�N
	
	GP_SEX_FEMALE = 0x3c,		///<���ʁF��
	GP_SEX_MALE = 0x3e,			///<���ʁF�Y
	GP_SEX_UNK = 0x40,			///<���ʁF�Ȃ�
	
	GP_MAHI = 0x29,				///<���
	GP_KOORI = 0x2c,			///<�X
	GP_NEMURI = 0x2f,			///<����
	GP_DOKU = 0x32,				///<��
	GP_YAKEDO = 0x35,			///<�₯��
	GP_NON_STATUS = 0x38,		///<��Ԉُ�Ȃ�
	
	GP_HPBAR_HEAD = 0x42,		///<HP�o�[�̃^�C�g��
	GP_HPBAR_CAP = 0x44,		///<HP�o�[�̊W
	GP_HPBAR_HEAD_CLEAR = GP_NON_STATUS,	///<HP�o�[�̃^�C�g���Ȃ�
	GP_HPBAR_CAP_CLEAR = GP_NON_STATUS,		///<HP�o�[�̊W�Ȃ�
	GP_SLASH = 0x45,			///<HP���l�̃X���b�V��
};


//--------------------------------------------------------------
//	���F�Q�[�W�v�Z���[�`���Ŏg�p
//--------------------------------------------------------------
///�|�P�������̕����ԊuX
#define GAUGE_FONT_MARGIN	(0)

///1�L�����̒��ɓ����Ă���Q�[�W�̃h�b�g��
#define GAUGE_DOTTO			(8)

///HP�o�[�̃L������
#define BAR_HP_CHARMAX		(6)
///EXP�o�[�̃L������
#define BAR_EXP_CHARMAX		(11)
///�Q�[�W�o�[�ň�ԑ傫���Q�[�W�̃L������
#define BAR_ALL_MAX			(BAR_EXP_CHARMAX)

///HP�Q�[�W�̃h�b�g��
#define GAUGE_HP_DOTTOMAX	(GAUGE_DOTTO * BAR_HP_CHARMAX)

///��Ɨp���[�N�̏����l�Ƃ��Ďg�p
#define HP_WORK_INIT_VALUE	(-2147483648)



//==============================================================================
//	�\���̒�`
//==============================================================================
//--------------------------------------------------------------
/**
 * @brief   HP�Q�[�W�F�T�u�p�����[�^
 *
 * �N���C�A���g���疽�߂��󂯂閈�ɁA�N���A�A�X�V�����p�����[�^�Q
 */
//--------------------------------------------------------------
typedef struct{
	u8			seq_no;
}GAUGE_SUB_PARAM;

//--------------------------------------------------------------
/**
 * @brief   HP�Q�[�W�\����
 */
//--------------------------------------------------------------
typedef struct{
	GAUGE_SUB_PARAM param;	///<�T�u�p�����[�^
	CATS_ACT_PTR cap;		///<�Q�[�W�{�̂̃w�b�_�[�t���A�N�^�[�|�C���^
	CATS_ACT_PTR arrow_cap;	///<���̃w�b�_�[�t���A�N�^�[�|�C���^
	BATTLE_WORK	*bw;		///<�퓬�V�X�e�����[�N�\����
	TCB_PTR tcb;			///<���쒆��TCB
	GF_BGL_BMPWIN name_bmpwin;	///<���OBITMAP�`���p

	u8			client_no;
	u8 			type;		///<�Q�[�W�^�C�v(GAUGE_TYPE_???)
	u8			sel_mons_no;	///<���Ԗڂ̃|�P�������I������Ă��邩

	u8			safari_nokori;		///<�T�t�@���F�c��{�[����
	
	s32			hp;			///<����HP(be_hp�v�Z�O�B�@�����m�ɂ� hp+be_hp ���ŐV�̌���HP�ƌ�����)
	s32			hpmax;		///<�ő�HP
	s32			damage;		///<�󂯂��_���[�W(-�Ń_���[�W�A+�Ȃ��)
	s32			hp_work;	///<�Q�[�W������Ɨp���[�N
	
	s32			exp;		///<���݂�EXP(add_exp�v�Z�O) �����݂̃��x���̊J�nEXP���������l
	s32			max_exp;	///<���̃��x���A�b�v�܂ł�EXP �����݂̃��x���̊J�nEXP���������l
	s32			add_exp;	///<���Z����EXP
	s32			exp_work;	///<�Q�[�W������Ɨp���[�N
	
	u8			level;		///<���x��
	u8			sex;		///<����
	u8			status;		///<��Ԉُ�
	u8			getball;	///<�Q�b�g�ς݃}�[�N
	
	u8			command_code;
	u8			in_wait;			///<IN�G�t�F�N�g������O�̃E�F�C�g
	u8			se_wait;			///<SE�E�F�C�g
	
	u8			in_out_dir:1;		///<�X�N���[������(GAUGE_SCROLL_IN or GAUGE_SCROLL_OUT)
	u8			eff_wait_in_out:1;	///<�G�t�F�N�g�҂��t���O(TRUE=�I��)�F�X�N���[��IN or OUT
	u8			eff_wait_lvup:1;	///<�G�t�F�N�g�҂��t���O(TRUE=�I��)�F���x���A�b�v
	u8			num_mode:1;			///<TRUE:HP���l�\�����[�h(2vs2�Q�[�W�Ŏ��@���̂�)
	
	TCB_PTR		sin_tcb;		///<Sin�J�[�u�F�G�t�F�N�g���s�^�X�N
	u16			sin_sec;		///<Sin�J�[�u�F�b
	
#ifdef PM_DEBUG
	u8			debug_hp_put;	///<TRUE:�G��HP�𐔒l�ł��\��
#endif
}GAUGE_WORK;



//==============================================================================
//	�O���֐��錾
//==============================================================================
extern void Gauge_ResourceLoad(CATS_SYS_PTR csp, CATS_RES_PTR crp, PALETTE_FADE_PTR pfd, 
	int gauge_type);
extern CATS_ACT_PTR Gauge_ActorSet(CATS_SYS_PTR csp, CATS_RES_PTR crp, int gauge_type);
extern void Gauge_InitCalcHP(GAUGE_WORK *gauge, int damage);
extern s32 Gauge_CalcHP(GAUGE_WORK *gauge);
extern void Gauge_InitCalcEXP(GAUGE_WORK *gauge, int add_exp);
extern s32 Gauge_CalcEXP(GAUGE_WORK *gauge);
extern void Gauge_ActorDel(GAUGE_WORK *gauge);
extern void Gauge_ResourceFree(GAUGE_WORK *gauge);
extern void Gauge_ActorResourceSet(GAUGE_WORK *gauge);
extern void Gauge_ActorResourceDel(GAUGE_WORK *gauge);
extern void Gauge_PartsDraw(GAUGE_WORK *gauge, u32 hp, u32 draw_flag);
extern void Gauge_AnimeStart(GAUGE_WORK *gauge);
extern void Gauge_AnimeStop(GAUGE_WORK *gauge);
extern u8 Gauge_TypeGet(int client_type, u32 fight_type);
extern void Gauge_BGPriSet(GAUGE_WORK *gauge, int bg_pri);
extern void Gauge_OffsetPosSet(GAUGE_WORK *gauge, int x, int y);
extern void Gauge_ScrollEffectSet(GAUGE_WORK *gauge, int in_out);
extern void Gauge_EnableSet(GAUGE_WORK *gauge, int enable);
extern void Gauge_LevelUpEffectStart(GAUGE_WORK *gauge, u8 *end_flag);
extern void Gauge_ColorBlackSet(GAUGE_WORK *gauge);
extern void Gauge_ColorNormalSet(GAUGE_WORK *gauge);
extern void Gauge_SinCurveSet(GAUGE_WORK *gauge);
extern void Gauge_SinCurveStop(GAUGE_WORK *gauge);
extern void Gauge_NumModeChange(GAUGE_WORK *gauge);

extern void Gauge_DebugHPPutFlagFlip(GAUGE_WORK *gauge);
extern void GaugeParts_DebugNumDraw(GAUGE_WORK *gauge, u32 num);


#endif	//__GAUGE_H__
