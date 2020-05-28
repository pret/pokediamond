//==============================================================================
/**
 * @file	dance.h
 * @brief	�_���X����̃w�b�_
 * @author	matsuda
 * @date	2005.12.10(�y)
 */
//==============================================================================
#ifndef __DANCE_H__
#define __DANCE_H__

#include "system/procsys.h"
#include "battle/battle_common.h"
#include "system/buflen.h"
#include "contest/contest.h"
#include "system/softsprite.h"
#include "system/fontproc.h"
#include "system/msgdata.h"
#include "system/gra_tool.h"
#include "system/wordset.h"
#include "system/clact_tool.h"
#include "contest_order.h"
#include "system/fontoam.h"
#include "system/particle.h"

#include "adv_tool.h"
#include "dance_snd_def.h"



//==============================================================================
//	�萔��`
//==============================================================================
///�T�u��ʂ̃T�[�t�F�[�X�ʒu
#define DANCE_SUB_ACTOR_DISTANCE		(256 * FX32_ONE)

//--------------------------------------------------------------
//	�Q�[���o�����X�p�����[�^
//--------------------------------------------------------------
///1���Ԃɂ�����t���[����
#define ONE_MIN_FRAME		(60 * 30)
///���Ă���Ȃ̃��C���̏��ߐ�
#define TEMPO_BASE_ONPU		(16)
///1���߂ɂ�����t���[���������߂鎞�ɍs���Œ菬�����̂��߂̏�Z��
#define ONE_TEMPO_CALC_DECIMAL		(10000)
///�_���X�̏��ߐ�(�����܂�)
#define DANCE_BEAT			(TEMPO_BASE_ONPU * 2)

///1�x�̃_���X�Ŏ��s�o����ő�_���X��
#define DANCING_MAX				(8)
///���C���_���T�[�̗�������鐔
#define DANCING_RECORD_MAX		(DANCING_MAX)
///�_���X�A�j���[�V�����̗\��o�b�t�@��
#define DANCE_STEP_REQUEST_MAX	(DANCE_BEAT)

///�]���p�l���̈ړ����xY
#define REVIEW_PANEL_SPEED_Y		(-4)

///4�����������tick��
#define QUARTER_NOTE_TICK			(48)

///tick��music_vcount������n�߂����A���t���[�����ꂽ��␳�����邩
///(���l��傫������قǁA�L�͈͂ɓn���Ă��ꂪ���e�����u�Ԃ�T���B
/// ���̕��A����Ă��鎞�Ԃ͎����I�ɋ��e�����܂ł͒����Ȃ�B
/// �A���A2�t���[���ȏ�̂��ꂪ����ꍇ�́A�����Ŏw�肵�Ă���t���[���Ɋ֌W�Ȃ�
/// �␳������̂ŁA����Ă���̂�1�t���[�������ł���B
/// �t�ɒl������������ƁA����n�߂Ă�������tick�̒l�ŕ␳�����̂ŁA
/// �Ȃƃ^�C�~���O�̂���Ă���t���[�����͏��Ȃ��Ȃ邪�Atick�̃J�E���^�̐�����A
/// 188tick, 188tick, 190tick... �̂悤�ɓ���������2�񑱂�����A1��΂��Đ�����
/// �オ��ꍇ������B
#define MUSIC_VCOUNT_HOSEI_COUNT	(18)


///�^�b�`��Ɏ��̃^�b�`�`�F�b�N���o����܂ł̃E�F�C�g�Ɍ��Z������E�F�C�g�l
///(4�������̒������x�̊��Ԃ������Ȃ�����ƁA����4�������̑O�オ�������炢�̂ŁA
/// ���������E�F�C�g��Z������ׂ̌��Z�l)
#define DANCE_TOUCH_WAIT_SUB_OFFSET		(2)

//--------------------------------------------------------------
//	
//--------------------------------------------------------------
///�o�b�N�_���T�[�ɑ������ރv���C�I���e�B
#define DANCE_BACK_IMC_ADD_PRI		(-100)

///�|�P������ʒuZ(���C���_���T�[)
#define DANCE_POKEPOS_Z_MAIN		(APPEAR_Z_TYPE_AA)
///�|�P������ʒuZ(�o�b�N�_���T�[)
#define DANCE_POKEPOS_Z_SUB			(DANCE_POKEPOS_Z_MAIN - 0x80)

///���C���_���T�[�̃|�P�����g�k��(XY����)
#define DANCE_POKEAFF_MAIN		(0x0100)
///�o�b�N�_���T�[�̃|�P�����g�k��(XY����)
#define DANCE_POKEAFF_BACK		(0x00c0)	//(0x0080)

///�Ȑi�s�o�[�̉�����(�L�����N�^�P��)
#define MUSIC_BAR_NUM		(32)
///�Ȑi�s�o�[1���������h�b�g��
#define MUSIC_BAR_ONE_LEN	(8)
///�Ȑi�s�o�[1���������h�b�g��
#define MUSIC_BAR_LEN		(MUSIC_BAR_ONE_LEN * MUSIC_BAR_NUM)

///�����A�N�^�[�𓯎��ɏo����ő吔(���C���_���T�[�{�o�b�N�_���T�[)
#define ONPU_ACTOR_MAX		((DANCE_BEAT / 2) * BREEDER_MAX + 4)	//+4�͕ی��ő��߂�

///�]���p�l���A�N�^�[�𓯎��ɏo����ő吔
#define REVIEW_ACTOR_MAX		(3)

///�]���^�C�v
enum{
	REVIEW_TYPE_EXCELLENT,
	REVIEW_TYPE_GOOD,
	REVIEW_TYPE_FAILED,
	
	REVIEW_TYPE_MAX,
};

///�_���X���僁�C����ʂŎg�p����t�H���gOAM�̍ő吔
#define DANCE_FONTOAM_MAX_MAIN	(REVIEW_TYPE_MAX * REVIEW_ACTOR_MAX)

///�u���[�_�[1�l�������ɏo���鐯�G�t�F�N�g�ő吔
#define STAR_EFF_MAX			(16)
///���̐��𑝂₵�čs����̃|�C���g
#define STAR_LVUP_POINT			(2)

//--------------------------------------------------------------
//	���[�e�[�V�����ʒu
//--------------------------------------------------------------
///���[�e�[�V�����ʒu
enum{
	DANCE_ROTATION_POS_A,		///<���C��
	DANCE_ROTATION_POS_B,		///<���ɗx��|�P����
	DANCE_ROTATION_POS_C,
	DANCE_ROTATION_POS_D,
};

//--------------------------------------------------------------
//	�o�b�t�@
//--------------------------------------------------------------
///������o�b�t�@�̃T�C�Y
#define DANCE_MESSAGE_BUF_SIZE	(2*160)		///<�b��łP�U�O������

///�p���b�g���ԃo�b�t�@�̃T�C�Y
#define DANCE_MIDDLE_PALWORK_SIZE	(0x200)

//--------------------------------------------------------------
//	�t���[���ԍ�
//--------------------------------------------------------------
///�E�B���h�E�E���b�Z�[�W�ʂ̃t���[��
#define DANCE_FRAME_WIN				(GF_BGL_FRAME1_M)
///�G�t�F�N�g�ʂ̃t���[��
#define DANCE_FRAME_EFF				(GF_BGL_FRAME2_M)
///�w�i�ʂ̃t���[��
#define DANCE_FRAME_BACKGROUND		(GF_BGL_FRAME3_M)

///<BG�ԍ��F�E�B���h�E
#define DANCE_BGNO_WIN			(1)
///<BG�ԍ��F�G�t�F�N�g
#define DANCE_BGNO_EFF			(2)
///<BG�ԍ��F�w�i
#define DANCE_BGNO_BACKGROUND	(3)

///<3D�ʂ�BG�v���C�I���e�B
#define DANCE_3DBG_PRIORITY		(2)
///�E�B���h�E�ʂ�BG�v���C�I���e�B
#define DANCE_BGPRI_WIN			(0)
///�G�t�F�N�g�ʂ�BG�v���C�I���e�B
#define DANCE_BGPRI_EFF			(0)
///�w�i�ʂ�BG�v���C�I���e�B
#define DANCE_BGPRI_BACKGROUND	(3)


//--------------------------------------------------------------
//	BMP�E�B���h�E
//--------------------------------------------------------------
enum{
	DANCE_BMPWIN_TALK,		///<��b�E�B���h�E
	DANCE_BMPWIN_PANEL,		///<�Ŕ��b�Z�[�W
	
	DANCE_BMPWIN_MAX,
};

//--------------------------------------------------------------
//	��b�E�B���h�E
//--------------------------------------------------------------
///��b�E�B���h�E�̃L�����N�^�]���I�t�Z�b�g(�L�����N�^�P��)
#define DANCE_TALKWIN_CGX_OFFSET	(1)
///��b�E�B���h�E�w�i�F
#define DANCE_TALKWIN_BACK_COLOR	(15)
///��b�E�B���h�E�̃p���b�g�ԍ�
#define DANCE_TALKWIN_PALNO		(14)

//--------------------------------------------------------------
//	�G�t�F�N�g��
//--------------------------------------------------------------
///�ǂ񂿂傤�̃p���b�g�ԍ�
#define DONTYOU_PALNO			(0xc)

///�_���X�������ɔ킹�锼����BG�̃p���b�g�ԍ�
#define DANCE_ALPHA_BG_PALNO	(DONTYOU_PALNO)

//--------------------------------------------------------------
//	����
//--------------------------------------------------------------
///���ʂ̐F�^�C�v
typedef enum{
	FUMENCOLOR_MAIN,		///<���C���_���T�[�̕��ʐF
	FUMENCOLOR_BACK,		///<�o�b�N�_���T�[�̕��ʐF
	FUMENCOLOR_NULL,		///<�w��Ȃ�
}FUMENCOLOR_TYPE;

///���C���_���T�[�̕��ʂ̃J���[�ʒu
#define FUMEN_MAIN_COLOR_POS		(2 * 16 + 9)
///���C���_���T�[�̕��ʂŎg�p���Ă���J���[��
#define FUMEN_MAIN_COLOR_NUM		(2)

///���C���_���T�[�̕��ʂ̃p���b�g�ԍ�
#define FUMEN_PALNO_MAIN			(4)
///�o�b�N�_���T�[�̕��ʂ̃p���b�g�ԍ�
#define FUMEN_PALNO_BACK			(3)
///�Ȑi�s�o�[�̃p���b�g�ԍ�
#define FUMEN_PALNO_MUSICBAR		(2)

//--------------------------------------------------------------
//	�t�F�[�h
//--------------------------------------------------------------
///�_���X����J�n���ɂ������Ă���n�[�h�t�F�[�h�̑Ώۃv���[��
#define DANCE_OPENING_BRIGHTNESS_PALNE		(GX_BLEND_PLANEMASK_BG0 | GX_BLEND_PLANEMASK_BG3 | GX_BLEND_PLANEMASK_BD | GX_BLEND_PLANEMASK_OBJ)
///�_���X����J�n���ɂ������Ă���n�[�h�t�F�[�h�̋P�x(16 �` -16)
#define DANCE_OPENING_BRIGHTNESS_EVY		(-6)

///��ʑS�̃t�F�[�h�p��BG�t�F�[�h�r�b�g(��b�E�B���h�E�A�t�H���g�A���[�J���C�Y�p������)
#define DANCE_DISP_BG_FADE_BIT			(0x1fff ^ ((1<<FUMEN_PALNO_MAIN) | (1<<FUMEN_PALNO_BACK) | (1 << FUMEN_PALNO_MUSICBAR)))
///��ʑS�̃t�F�[�h�p��OBJ�t�F�[�h�r�b�g(�ʐM�A�C�R���A���[�J���C�Y�p������)
#define DANCE_DISP_OBJ_FADE_BIT			(0x3fff)
///��ʑS�̃t�F�[�h�p��BG�J���[��(��b�E�B���h�E�A�t�H���g�A���[�J���C�Y�p������)
#define DANCE_DISP_BG_COLOR_NUM		(16 * 13)
///��ʑS�̃t�F�[�h�p��OBJ�J���[��(�ʐM�A�C�R���A���[�J���C�Y�p������)
#define DANCE_DISP_OBJ_COLOR_NUM	(16 * 14)

//--------------------------------------------------------------
//	�_���X�������ɔ킹�锼����BG
//--------------------------------------------------------------
///�_���X���s������BG�^�C�v
enum{
	DANCE_BGALPHA_TYPE_NULL,	///<�����Ȃ�(�J���[�p���b�g��0�ʒu(�����F)���̃_�~�[
	DANCE_BGALPHA_TYPE_UP,		///<������BG�F��
	DANCE_BGALPHA_TYPE_DOWN,	///<������BG�F��
	DANCE_BGALPHA_TYPE_LEFT,	///<������BG�F��
	DANCE_BGALPHA_TYPE_RIGHT,	///<������BG�F�E
	DANCE_BGALPHA_TYPE_FAILED,	///<������BG�F���s
};

///�_���X���s������BG�̑�1�Ώۖ�
#define DANCE_BGALPHA_PLANE_1		(GX_BLEND_PLANEMASK_BG2)
///�_���X���s������BG�̑�2�Ώۖ�
#define DANCE_BGALPHA_PLANE_2		(GX_BLEND_PLANEMASK_BG0 | GX_BLEND_PLANEMASK_BG1 | GX_BLEND_PLANEMASK_BG3 | GX_BLEND_PLANEMASK_OBJ | GX_BLEND_PLANEMASK_BD)

//--------------------------------------------------------------
//	�p�[�e�B�N��
//--------------------------------------------------------------
///�_���X�p�[�e�B�N���̃f�t�H���gZ�ʒu
#define DANCE_PARTICLE_DEFAULT_Z		(-5248)
///�p�[�e�B�N����΍��W�F���[
#define DANCE_PARTICLE_LEFT				(-28600)
///�p�[�e�B�N����΍��W�F�E�[
#define DANCE_PARTICLE_RIGHT			(-DANCE_PARTICLE_LEFT)

///���ʂ̒��SY���W
#define DANCE_PARTICLE_FUMEN_CENTER_Y	(-17700)

///���߃p�[�e�B�N��(Lv1)�̐�΍��W�F����
#define DANCE_PARTICLE_FINISH_LEFT_LV1		(-13000)
///���߃p�[�e�B�N��(Lv1)�̐�΍��W�F�E��
#define DANCE_PARTICLE_FINISH_RIGHT_LV1		((-DANCE_PARTICLE_FINISH_LEFT_LV1) + 7500)
///���߃p�[�e�B�N��(Lv1)�̐�΍��W�FY
#define DANCE_PARTICLE_FINISH_Y_LV1			(-6300)

///���߃p�[�e�B�N��(Lv2)�̐�΍��W�F����
#define DANCE_PARTICLE_FINISH_LEFT_LV2		(DANCE_PARTICLE_FINISH_LEFT_LV1 - 4000)
///���߃p�[�e�B�N��(Lv2)�̐�΍��W�F�E��
#define DANCE_PARTICLE_FINISH_RIGHT_LV2		(DANCE_PARTICLE_FINISH_RIGHT_LV1 - 4000)
///���߃p�[�e�B�N��(Lv2)�̐�΍��W�FY
#define DANCE_PARTICLE_FINISH_Y_LV2			(DANCE_PARTICLE_FINISH_Y_LV1)


//--------------------------------------------------------------
//	�A�N�^�[BG�v���C�I���e�B
//--------------------------------------------------------------
///�Ȑi�s�o�[�A�N�^�[��BG�v���C�I���e�B
#define DANCE_BGPRI_MUSIC_BAR	(1)
///�����A�N�^�[��BG�v���C�I���e�B
#define DANCE_BGPRI_ONPU		(DANCE_BGPRI_BACKGROUND)	//(1)
///�]���p�l���A�N�^�[��BG�v���C�I���e�B
#define DANCE_BGPRI_REVIEW		(1)
///�����J�[�\���A�N�^�[��BG�v���C�I���e�B
#define DANCE_BGPRI_MY_CURSOR		(1)
///�v�����A�N�^�[��BG�v���C�I���e�B
#define DANCE_BGPRI_PRIN		(1)
///�e�A�N�^�[��BG�v���C�I���e�B
#define DANCE_BGPRI_SHADOW		(DANCE_BGPRI_BACKGROUND)
///���A�N�^�[��BG�v���C�I���e�B
#define DANCE_BGPRI_STAR		(DANCE_BGPRI_BACKGROUND)

//--------------------------------------------------------------
//	�A�N�^�[�\�t�g�v���C�I���e�B
//--------------------------------------------------------------
enum{
	DANCE_SOFTPRI_START = 10,
	
	DANCE_PRIN,						///<�v����
	
	DANCE_SOFTPRI_REVIEW_FONT,		///<�]���p�l���A�N�^�[�̏�ɏ��t�H���gOAM
	DANCE_SOFTPRI_REVIEW,			///<�]���p�l���A�N�^�[
	
	DANCE_SOFTPRI_MUSIC_BAR,		///<�Ȑi�s�o�[�A�N�^�[
	DANCE_SOFTPRI_ONPU = DANCE_SOFTPRI_MUSIC_BAR + 30,				///<�����A�N�^�[
	DANCE_SOFTPRI_MY_CURSOR,		///<�����J�[�\���A�N�^�[
	
	DANCE_SOFTPRI_STAR,				///<��
	DANCE_SOFTPRI_SHADOW,			///<�e
};

///�����^�C�v
enum{
	ONPU_TYPE_A,
	ONPU_TYPE_B,
	
	ONPU_TYPE_MAX,
};

///�_���X�^�C�v
enum{
	DANCE_STEP_NONE,
	
	DANCE_STEP_JUMP,
	DANCE_STEP_ADVANCE,
	DANCE_STEP_LEFT,
	DANCE_STEP_RIGHT,
};

///�_���T�[�^�C�v
enum{
	DANCER_MAIN,	///<���C���_���T�[
	DANCER_BACK,	///<�o�b�N�_���T�[
};

///�_���X�̃��O
enum{
	DANCE_LAG_EXCELLENT_A,
	DANCE_LAG_EXCELLENT_B,
	DANCE_LAG_GOOD_A,
	DANCE_LAG_GOOD_B,
	
	DANCE_LAG_FAILED,
	DANCE_LAG_MAX = DANCE_LAG_FAILED,
};

///�_���X�̃��O���̓��_
enum{
	DANCE_POINT_EXCELLENT_A = 2,
	DANCE_POINT_EXCELLENT_B = 2,
	DANCE_POINT_GOOD_A = 1,
	DANCE_POINT_GOOD_B = 1,
};

//--------------------------------------------------------------
//	�X�N���[���R�[�h
//--------------------------------------------------------------
///�Ȑi�s�o�[�̐擪�X�N���[���R�[�h
#define MUSIC_BAR_FAST_SCRN_CODE_BASE		(0x200c)
///�Ȑi�s�o�[�̃��[�^�[���^���̃X�N���[���R�[�h
#define MUSIC_BAR_FAST_SCRN_CODE_FULL		(MUSIC_BAR_FAST_SCRN_CODE_BASE + 8)
///�Ȑi�s�o�[�̐擪�X�N���[���R�[�h
#define MUSIC_BAR_SECOND_SCRN_CODE_BASE		(0x202c)
///�Ȑi�s�o�[�̃��[�^�[���^���̃X�N���[���R�[�h
#define MUSIC_BAR_SECOND_SCRN_CODE_FULL		(MUSIC_BAR_SECOND_SCRN_CODE_BASE + 8)
///�Ȑi�s�o�[�̐擪�X�N���[���R�[�h
#define MUSIC_BAR_THERD_SCRN_CODE_BASE		(0x204c)
///�Ȑi�s�o�[�̃��[�^�[���^���̃X�N���[���R�[�h
#define MUSIC_BAR_THERD_SCRN_CODE_FULL		(MUSIC_BAR_THERD_SCRN_CODE_BASE + 8)

//--------------------------------------------------------------
//	
//--------------------------------------------------------------
///�����̃A�j���^�C�v
enum{
	ONPU_ANMTYPE_MINE,			///<�����p����
	ONPU_ANMTYPE_ENEMY,			///<�G�p����
	ONPU_ANMTYPE_HISTORY,		///<����p����
};


///���b�Z�[�W�^�O
enum{
	DTAG_NONE,		///<�^�O�Ȃ�
	
	DTAG_NICK,		///<�j�b�N�l�[��
	DTAG_RANK,		///<�R���e�X�g�����N
	DTAG_NUM,		///<���l
	DTAG_OYA_NICK,	///<�e���A�j�b�N�l�[��
	DTAG_NICK_NUM,	///<�j�b�N�l�[���A���l
	DTAG_RANK_NUM_OYA_NICK,
	
	DTAG_MAX,
};


//==============================================================================
//	�\���̒�`
//==============================================================================
//--------------------------------------------------------------
//	
//--------------------------------------------------------------
typedef struct{
	u8 actin_sort[BREEDER_MAX];
}DANCE_EXIT_PARAM;

//--------------------------------------------------------------
//	���b�Z�[�W
//--------------------------------------------------------------
///���Z���僁�b�Z�[�W�f�[�^
typedef struct{
	u16 msg_id;				///<���b�Z�[�WID
	u8 msg_tag;				///<�^�O�R�[�h
}DANCE_MESSAGE_PARAM;

///���b�Z�[�W�^�O�W�J����ꍇ�A�Q�Ƃ����p�����[�^��
typedef struct{
	u8 mine_brd;		///<MINE���w�肳��Ă������ɎQ�Ƃ���u���[�_�[�̔ԍ�
	u8 enemy_brd;		///<ENEMY���w�肳��Ă������ɎQ�Ƃ���u���[�_�[�̔ԍ�
	u16 wazano;			///<WAZA���w�肳��Ă������ɎQ�Ƃ���Z�ԍ�
	u8 num;				///<NUM���w�肳��Ă������ɕ\�����鐔�l
	u8 judge_no;		///<JUDGE���w�肳��Ă������ɎQ�Ƃ���R���̔ԍ�
}DTAG_PARAM;

//--------------------------------------------------------------
//	
//--------------------------------------------------------------
///�]���p�l���G�t�F�N�g�^�X�N
typedef struct{
	CATS_ACT_PTR cap;
	ADV_FONTACT *fontact;
	TCB_PTR tcb;			///<����^�X�N�ւ̃|�C���^
	
	s32 work;
	u8 seq;
}REVIEW_PANEL_TASK_WORK;

///�v�������샏�[�N
typedef struct{
	TCB_PTR tcb;			///<�v�������상�C���^�X�N�ւ̃|�C���^
	CATS_ACT_PTR cap;		///<�v�����A�N�^�[�ւ̃|�C���^
	struct _DANCE_PROC_WORK *dpw;	///<�_���X����Ǘ����[�N�ւ̃|�C���^
	
	u8 seq;
}PRIN_WORK;

///�e���샏�[�N
typedef struct{
	TCB_PTR tcb;			///<�e���상�C���^�X�N�ւ̃|�C���^
	CATS_ACT_PTR cap;		///<�e�A�N�^�[�ւ̃|�C���^
	struct _DANCE_PROC_WORK *dpw;	///<�_���X����Ǘ����[�N�ւ̃|�C���^
	CONTEST_IMC_WORK *imcwork;	///<�Ώۂ̃|�P�����C���[�W�N���b�v�ւ̃|�C���^
	
	u8 seq;
	u8 homing;				///<TRUE:�ǔ�ON�AFALSE:�ǔ�OFF
	u8 homing_jump;			///<TRUE:�ǔ�ON�AFALSE:�ǔ�OFF
	u8 breeder_no;			///<�e��S������u���[�_�[�ԍ�
	s8 height;				///<�|�P�����̍���
}SHADOW_WORK;

///�X�|�b�g���C�g���샏�[�N
typedef struct{
	TCB_PTR tcb;			///<�X�|�b�g���C�g���상�C���^�X�N�ւ̃|�C���^
	CATS_ACT_PTR cap;		///<�A�N�^�[�ւ̃|�C���^
	struct _DANCE_PROC_WORK *dpw;	///<�_���X����Ǘ����[�N�ւ̃|�C���^
	
	u8 seq;
	u8 breeder_no;			///<�X�|�b�g���C�g��S������u���[�_�[�ԍ�
	s8 height;				///<�|�P�����̍���
}SPOTLIGHT_WORK;

///�����샏�[�N
typedef struct{
	TCB_PTR tcb;			///<�����상�C���^�X�N�ւ̃|�C���^
	CATS_ACT_PTR cap;		///<���A�N�^�[�ւ̃|�C���^
	
	s32 x;					///<���ݍ��WX(����8�r�b�g����)
	s32 y;					///<���ݍ��WY(����8�r�b�g����)
	s32 add_x;				///<X�������Z�l
	s32 up_power;			///<�W�����v��
	u16 life_frame;			///<�����t���[��
}STAR_WORK;

///���ʃt���b�V�����샏�[�N
typedef struct{
	struct _DANCE_PROC_WORK *dpw;	///<�_���X����Ǘ����[�N�ւ̃|�C���^
	TCB_PTR tcb;			///<���ʃt���b�V�����C������^�X�N�ւ̃|�C���^
	u16 evy;				///<EVY�l(����8�r�b�g����)
	u8 color_pos;			///<�t�F�[�h�J�n�J���[�ʒu
	u8 occ;					///<TRUE�F�G�t�F�N�g�N����
}FUMEN_FLASH_WORK;

///�|�P�����풓�A�j���p���[�N
typedef struct{
	struct _DANCE_PROC_WORK *dpw;	///<�_���X����Ǘ����[�N�ւ̃|�C���^
	TCB_PTR tcb;			///<�A�j�����s�^�X�N�ւ̃|�C���^
	SOFT_SPRITE *ss;		///<�Ώۂ̃|�P�����\�t�g�E�F�A�X�v���C�g�ւ̃|�C���^
	CONTEST_IMC_WORK *imcwork;	///<�Ώۂ̃|�P�����C���[�W�N���b�v�ւ̃|�C���^
	s32 aff_z;				///<�g�k�ׂ̈�Z���W(����8�r�b�g����)
	s32 move_sin;			///<�ړ��A�j���̌��݂�Sin�l
	
	u8 aff_loop;			///<�g�k�A�j���J��Ԃ���
	u8 rotation_pos;		///<���[�e�[�V�����ʒu
	u8 breeder_no;			///<�u���[�_�[�ԍ�
	u8 aff_seq;
	u8 move_seq;
	
	u32 move_stop_sin;		///<�ړ��A�j���F��~�������̊p�x
	
	u8 move_stop_req:1;		///<1:�ړ��A�j����~���N�G�X�g(�ʏ�ʒu�ɖ߂������~)
	u8 move_stop:1;			///<1:�ړ��A�j����~(����~)
	u8 move_start_req:1;	///<1:�ړ��A�j���J�n���N�G�X�g
	u8 move_init:1;			///<1:�����N��

	u8 aff_stop_req:1;		///<1:�g�k�A�j����~���N�G�X�g(�ʏ�Affine�T�C�Y�ɖ߂������~)
	u8 aff_stop:1;			///<1:�g�k�A�j������~
	u8 aff_dir:1;			///<�g�k�A�j���̕���(0:��O�ցA1:����)
}POKE_DEF_ANM_WORK;

///�p�[�e�B�N�������󂯓n���p�e���|�������[�N
typedef struct{
	s32 x;				///<���WX
	s32 y;				///<���WY
	s32 z;				///<���WZ
	fx32 gen_num;		///<���o���[�g
}DANCE_PARTICLE_TEMP_WORK;

///�_���X���s����̃p�����[�^(1frame�̒ʐM�őS�đ���M�o����悤��20�o�C�g�ȓ��Ɏ��߂鎖!!)
typedef struct{
	u16 frame;			///<�_���X�������̃t���[����
	u8 breeder_no;		///<�u���[�_�[�ԍ�(���̃_���X�������u���[�_�[)
	u8 dance_step;		///<�_���X�̎��(�㉺���E)
	u8 review_type;		///<�]���^�C�v(REVIEW_TYPE_EXCELLENT��)
	u8 lag_type;		///<���O�^�C�v
	u8 hit_beat;		///<�����ߖڂ�]���Ώۂɂ�����
	u8 rotation_pos;	///<���[�e�[�V�����ʒu
	
	u8 finish:1;		///<TRUE:�Ō�̃_���X�A���߃|�[�Y
	u8 button_failed:1;	///<TRUE:�������{�^�������C���_���T�[�ƈ����
	u8 occ:1;			///<�L�������t���O(TRUE:�f�[�^�L��)
	u8 :6;
}DANCING_PARAM;

///<�_���X�̂��ꋖ�e�͈�(EXCELLENT_A,B,GOOD_A,B)
typedef struct{
	u8 excellent_a;
	u8 excellent_b;
	u8 good_a;
	u8 good_b;
}DANCE_LAG_DATA;

///�_���X���y�i�s�f�[�^
typedef struct{
	u16 music_id;				///<��ID
	u16 tempo;					///<�Ȃ̃e���|
	u8 loop;					///<�J��Ԃ���
	u8 touch_count;				///<�^�b�`(�_���X)�o�����
	u8 ready_count;				///<�������Ԃ̏��ߐ�
	u8 rotation_count;			///<���[�e�[�V�����̏��ߐ�
	DANCE_LAG_DATA lag;			///<�_���X�̂��ꋖ�e�͈�(EXCELLENT_A,B,GOOD_A,B)
}DANCE_MUSIC_DATA;

///�_���X�A�j���[�V�������[�N�̃G�t�F�N�g����Ŏg�p���郏�[�N
typedef struct{
	//�ǂ̃X�e�b�v�ł����ʂŎg�p����ł��낤���[�N
	s32 start_x;		///<�A�j���J�n�O��X���W
	s32 start_y;		///<�A�j���J�n�O��Y���W
	s32 x;				///<���ݍ��WX
	s32 y;				///<���ݍ��WY
	u8 seq;
	
	//�e�X�e�b�v���ɓƎ��Ŏ����[�N
	union{
		struct{
			s16 up_power;
			s16 gravity;
		}jump;
		
		struct{
			s32 add_go_x;
			s32 add_back_x;
		}advance;
		
		struct{
			u32 theta;
			int add_theta;
			int back_theta;
			int add_x;
			int back_x;
		}lr;
	};
}MOVE_EFF_WORK;

///�_���X�A�j���[�V�������[�N
typedef struct{
	u8 dance_step[DANCE_STEP_REQUEST_MAX];	///<�_���X�̎��(DANCE_STEP_???)
	
	u8 work_pos;							///<���ݎw���Ă���dance_step���[�N�̔z��ʒu
	u8 rotation_pos;
	u8 finish;								///<TRUE:�Ō�̌��߃_���X
	u8 point;								///<�_���X�������̍��v���_
	
	MOVE_EFF_WORK eff;						///<�G�t�F�N�g����p�̃��[�N
}DANCE_MOVE_WORK;

///�_���X�pAI���[�N
typedef struct{
	union{
		//���C���_���T�[�p���[�N
		struct{
			u32 hit_frame[DANCING_MAX];			///<�_���X�����s����t���[��
			u8 tp_type[DANCING_MAX];
			u8 occ[DANCING_MAX];
		}main;

		//�o�b�N�_���T�[�p���[�N
		struct{
			u32 frame;
			u8 tp_type;
			u8 occ;
		}back;
	};

	//���p���[�N
	u32 random_seed;					///<AI�v�Z�p�̃����_���̎�
	s16 touch_wait;						///<�^�b�`�o���Ȃ��t���[�����J�E���g
	u8 touch_count;						///<�_���X�����񐔂��J�E���g
	u8 breeder_no;						///<AI���g�̃u���[�_�[�ԍ�
	u8 rotation_pos;					///<���[�e�[�V�����ʒu
	u8 character;						///<���i
}DANCE_AI_WORK;

///���C���V�[�P���X���Ŏg�p���郍�[�J�����[�N
typedef struct{
	u16 seq;
	u16 select_seq;
	s32 work;
}DANCE_LOCAL_WORK;

//--------------------------------------------------------------
/**
 * @brief   �_���X����i�s�p�����[�^(���݋Z���o���Ă���|�P�����̐i�s�p�����[�^)
 */
//--------------------------------------------------------------
typedef struct{
	u8 now_breeder;					///<���ݏ�ɏo�Ă���u���[�_�[�̔ԍ�
	u8 now_count;					///<���ݏ�ɏo�Ă���u���[�_�[�����ԖڂɃA�s�[�����Ă��邩
	
	u8 breeder_rotation[BREEDER_MAX];	///<���݂̃u���[�_�[�̃��[�e�[�V��������
										///<���C���_���T�[���珇�X�Ƀu���[�_�[�ԍ��������Ă܂�

	u32 one_tempo_frame;			///<1���ߐi�ނ̂ɕK�v�ȃt���[����
									///<(�������FONE_TEMPO_CALC_DECIMAL��Z�����A�ȉ�����)
	u32 all_tempo_frame;			///<��ʒ[����[�܂Ői�ނ̂ɕK�v�ȃt���[����(����)
	u16 tempo;						///<�_���X�Ȃ̃e���|

	u32 ai_random_seed[BREEDER_MAX];	///<AI�p�̃����_���̎�
	
	DANCE_MUSIC_DATA musicdata;		///<���y�i�s�f�[�^

	DTAG_PARAM a_talk_tagpara;		///<�m�[�}����b�F�^�O�W�J�p�p�����[�^
	u8 a_talk_id;					///<�m�[�}����bID(A_TALK_DANCE_???)
	u8 a_talk_bmpwin_close_wait;	///<���b�Z�[�W��\���������Ă���E�B���h�E�����܂ł�wait
	u8 a_talk_bmpwin_not_close;		///<TRUE:�E�B���h�E������ɏI��
}DANCE_ADVANCE_PARAM;

//--------------------------------------------------------------
/**
 * @brief   �_���X����Q�[���i�s�p�����[�^
 *
 * ���̃p�����[�^������ΑS��ʂ��č\�z�o���邾���̏�񂪓����Ă��܂��B
 * �ʐM���̓T�[�o�[����q�@�̓f�[�^���󂯎�鎖�ɂȂ�܂��B
 * ��{�I�Ƀ��j���[��ʂ���̉�ʕ��A�̂悤�Ȏ����Ȃ�����A
 * �X�̎q�@���Œl���Q�Ƃ��鎖�͂Ȃ��͂��ł��B
 */
//--------------------------------------------------------------
typedef struct{
	u8 breeder_sort[BREEDER_MAX];	///<�Z���o������(�o�鏇�Ƀu���[�_�[�ԍ��������Ă܂�)
	u8 breeder_end_count;			///<�s�����I�������u���[�_�[�̐����J�E���g

	u8 breeder_rotation[BREEDER_MAX];	///<���݂̃u���[�_�[�̃��[�e�[�V��������
										///<���C���_���T�[���珇�X�Ƀu���[�_�[�ԍ��������Ă܂�
	
	s16 dance_point[BREEDER_MAX];	///<�l�������_���X�|�C���g
	
	u32 music_id;					///<�_���X�̋�ID

	u32 one_tempo_frame;			///<1���ߐi�ނ̂ɕK�v�ȃt���[����
									///<(�������FONE_TEMPO_CALC_DECIMAL��Z�����A�ȉ�����)
	u32 all_tempo_frame;			///<��ʒ[����[�܂Ői�ނ̂ɕK�v�ȃt���[����(����)
	u32 ready_frame;				///<�������Ԃ̃t���[����(�������FONE_TEMPO_CALC_DECIMAL��Z)
	u32 rotation_frame;		///<���[�e�[�V�������Ԃ̃t���[����(�������FONE_TEMPO_CALC_DECIMAL��Z)
	u32 tick_frame;			///<1�t���[������tick �Ȃ̂�(�������FONE_TEMPO_CALC_DECIMAL��Z)
	u16 tempo;						///<�_���X�Ȃ̃e���|
	
	u8 touch_count;					///<�^�b�`�o����ő��
}DANCE_GAME_PARAM;

//--------------------------------------------------------------
/**
 * @brief   ���ߑ���M�p�p�����[�^
 * 
 * �T�[�o�[�Ƃ̖��߂̑���M�Ɏg�p���܂�
 */
//--------------------------------------------------------------
typedef struct{
	u8 breeder_no;
	
	u8 buffer[255];					///<�e���߂Ōʂɓn���f�[�^���ς��ꍇ�A�������g�p
}DANCE_ORDER_PARAM;

///�p���b�g���ԃo�b�t�@
typedef struct{
	u16 *buf;			///<���ԃo�b�t�@�ւ̃|�C���^
	u16 evy;			///<EVY�l(����8�r�b�g����)
	u16 fade_bit;		///<�t�F�[�hBIT
	u16 now_evy;		///<���݂�EVY�l(����8�r�b�g����)
	u16 end_evy;		///<�I��EVY�l(����8�r�b�g����)
	s16 add_evy;		///<EVY���Z�l
	u16 next_rgb;		///<�ύX��̃J���[
	u8 req;				///<TRUE:�t�F�[�h���N�G�X�g��
	u8 occ;				///<TRUE:���ԃo�b�t�@���g�p����
}DANCE_MIDDLE_FADE;

//--------------------------------------------------------------
/**
 * @brief   �Q�[����ʂ��\�����邽�߂ɕK�v�ȃV�X�e���f�[�^�ނ����\����
 *
 * �ʐM���ł��S�Ẵ}�V���Ōʂɍ쐬����܂�
 * �e�X�^�b�t�����ߎ�M���A���̃}�V���X�Ő����������̃��[�N�o�b�t�@��n�����ɂȂ�܂�
 */
//--------------------------------------------------------------
typedef struct{
	CONTEST_GAME_PARAM *c_game;		///<�R���e�X�g�i�s�p�����[�^(��t�Ŋ��ɒʐM�ς݂̃f�[�^�ւ̃|�C���^���������B�Q�Ɨp)
	
	//�C���[�W�N���b�v
	CONTEST_IMC_WORK imcwork[BREEDER_MAX];	///<�C���[�W�N���b�v�֘A���[�N

	SOFT_SPRITE_MANAGER	*soft_sprite;
	SOFT_SPRITE *ss[BREEDER_MAX];
	CATS_SYS_PTR		csp;
	CATS_RES_PTR		crp;
	GF_BGL_INI *bgl;
	GF_BGL_BMPWIN win[DANCE_BMPWIN_MAX];
	MSGDATA_MANAGER *dance_msg;	///<�_���X���僁�b�Z�[�W�p���b�Z�[�W�}�l�[�W���̃|�C���^
	WORDSET *wordset;
	STRBUF *msg_buf;				///<Alloc����������o�b�t�@�ւ̃|�C���^
	PALETTE_FADE_PTR pfd;			///<�p���b�g�t�F�[�h�V�X�e���ւ̃|�C���^
	FONTOAM_SYS_PTR fontoam_sys;	///<�t�H���gOAM�V�X�e���ւ̃|�C���^
	
	EXCHR_PARAM exchr_param[BREEDER_MAX];		///<�Z�G�t�F�N�g�p�L�����W�J�o�b�t�@

	CATS_ACT_PTR onpu_cap[ONPU_ACTOR_MAX];		///<�����A�N�^�[�̃|�C���^
	
	CATS_ACT_PTR my_cursor_cap;		///<�����J�[�\���A�N�^�[�̃|�C���^
	TCB_PTR my_cursor_tcb;			///<�����J�[�\���^�X�N��TCB�|�C���^
	
	FUMEN_FLASH_WORK fumen_flash;	///<���ʃt���b�V�����샏�[�N
	PRIN_WORK *prin_sys;			///<�v�������샏�[�N
	SHADOW_WORK shadow[BREEDER_MAX];	///<�e���샏�[�N
	SPOTLIGHT_WORK spotlight[BREEDER_MAX];	///<�X�|�b�g���C�g���샏�[�N
	STAR_WORK star[BREEDER_MAX][STAR_EFF_MAX];	///<�����샏�[�N
	
	REVIEW_PANEL_TASK_WORK rptw[REVIEW_ACTOR_MAX];	///<�]���p�l������^�X�N�̃��[�N
	CATS_ACT_PTR review_cap[REVIEW_ACTOR_MAX];		///<�]���p�l���A�N�^�[�̃|�C���^
	ADV_FONTACT fontact[REVIEW_TYPE_MAX][REVIEW_ACTOR_MAX];	///<�]���p�l����̃t�H���g�A�N�^�[

	const DANCE_MUSIC_DATA *musicdata;		///<���y�i�s�f�[�^�ւ̃|�C���^

	u8 jump_up[BREEDER_MAX];		///<TRUE:�W�����vOK�B�@FALSE:�W�����v�֎~("��"����)
	
	u8 talk_msg_index;				///<�����`�惋�[�`���̃C���f�b�N�X
	
	u8 excellent_count[BREEDER_MAX];		///<Excellent�A���擾��(�S�Ẵ_���X�p��)
	u8 now_excellent_count[BREEDER_MAX];	///<Excellent�A���擾��(���̕��ʂ̃_���X�̂�)
	u8 now_failed_count[BREEDER_MAX];		///<FAILED�擾��(���̕��ʂ̃_���X�̂�)
	u8 now_back_excellent_all_count;		///<�o�b�N�_���T�[��Excellent�擾��
	u8 now_back_good_all_count;				///<�o�b�N�_���T�[��Good�擾��
	u8 now_back_failed_all_count;			///<�o�b�N�_���T�[��Failed�擾��
	u8 succession_count[BREEDER_MAX];		///<�A���_���X��(�S�Ẵ_���X�p��)
	u8 my_dancing_rotation_pos;				///<�_���X���̎����̃��[�e�[�V�����ʒu
}DANCE_SYSTEM_PARAM;

//--------------------------------------------------------------
/**
 * @brief   �_���X����Ǘ����[�N
 *
 * �_���X����S�̂��Ǘ�����匳�̃��[�N�ɂȂ�܂��B
 * �ʐM���ł��S�Ẵ}�V���Ōʂɍ쐬����܂�
 */
//--------------------------------------------------------------
typedef struct _DANCE_PROC_WORK{
	CONTEST_SYSTEM *consys;			///<�R���e�X�g�V�X�e�����[�N�ւ̃|�C���^
	TCB_PTR update_tcb;				///<�V�X�e���X�V����
	TCB_PTR move_tcb;				///<�|�P�����_���X�G�t�F�N�g���s�^�X�N�ւ̃|�C���^
	PTC_PTR ptc;					///<�풓�p�[�e�B�N���V�X�e��
	GF_G3DMAN *g3Dman;
	
	DANCE_SYSTEM_PARAM sys;			///<�_���X����V�X�e���f�[�^�p�����[�^
	DANCE_GAME_PARAM d_game;			///<�Q�[���i�s�p�����[�^
	DANCE_ADVANCE_PARAM advance;		///<�i�s�p�����[�^
	DANCE_ORDER_PARAM order[BREEDER_MAX];	///<���߃p�����[�^
	DANCE_MOVE_WORK move[BREEDER_MAX];		///<�_���X�A�j���[�V�������[�N
	POKE_DEF_ANM_WORK pda[BREEDER_MAX];		///<�|�P�����풓�A�j���p���[�N

	DANCE_MIDDLE_FADE middle_fade;	///<�p���b�g���ԃo�b�t�@

	DANCE_PARTICLE_TEMP_WORK particle_temp;	///<�p�[�e�B�N�������󂯓n���p�e���|�������[�N
	
	void *dip;						///<�T�u��ʐ���V�X�e���\���̂ւ̃|�C���^
	
	u8 music_vcount_flag;			///<TRUE�F�Ȑi�s�t���[���J�E���g�A�b�v
	u64 music_vcount;				///<�Ȑi�s�̃t���[���m�F(�ȂƂ���Ȃ��悤��Vblank��++����)
	u64 music_vcount_start;			///<�_���X���J�n��������V�J�E���^���L��
	u32 music_vcount_hosei_count;	///<�␳���Ȃ���΂����Ȃ��t���[�������܂��Ă��鐔
	u32 tick_temp;					///<tick�̒l��ۑ�
	
	u16 seq;
	u16 tbl_seq_no;					///<���C���V�[�P���X�e�[�u���̔ԍ�
	u8 proc_mode;					///<���݂̓����

#if 0
	//-- ����M�o�b�t�@ --//
	u32 request_bit;				///<���߂��o���Ă���r�b�g
	u8 transmit_buf[TRANSMIT_BUF_SIZE];	///<���M�p�o�b�t�@
	u8 receive_buf[RECEIVE_BUF_SIZE];	///<��M�p�o�b�t�@
	u8 transmit_flag;				///<TRUE�F���M�҂��B�@FALSE:�V���ȃf�[�^�Z�b�g�\
	u8 receive_flag;				///<TRUE�F�f�[�^��M����
#endif
	CONTEST_ORDER_WORK cow;			///<����M���[�N

	DANCING_PARAM dancing[BREEDER_MAX];		///<�_���X���s����̃p�����[�^
	DANCING_PARAM maindancer_record[DANCING_RECORD_MAX];	///<���C���_���T�[�̃_���X����(�ʐM���A�f�[�^�͌X�̂��̏ꏊ�Ɏ�M����鎖�ɂȂ�A�N���C�A���g���ꂼ�ꂪ�������g��DANCE_PROC_WORK�̂��̏ꏊ���Q�Ƃ��鎖�ɂȂ�܂�)

	DANCE_LOCAL_WORK local;			///<���[�J�����[�N
	u8 main_end;					///<TRUE:���C�������I��
	
	u8 bord_msg_flag;				///<TRUE:�Ŕ��b�Z�[�W�\����
}DANCE_PROC_WORK;


//==============================================================================
//	�O���֐��錾
//==============================================================================
extern PROC_RESULT DanceProc_Init( PROC * proc, int * seq );
extern PROC_RESULT DanceProc_Main( PROC * proc, int * seq );
extern PROC_RESULT DanceProc_End( PROC * proc, int * seq );

#ifdef PM_DEBUG
extern void TestParticleDance(DANCE_PROC_WORK *dpw);
#endif

//==============================================================================
//	�O���f�[�^�錾
//==============================================================================
extern const PROC_DATA ContestDanceProcData;



#endif	//__DANCE_H__

