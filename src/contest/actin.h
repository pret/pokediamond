//==============================================================================
/**
 * @file	actin.h
 * @brief	���Z�͕���̃w�b�_
 * @author	matsuda
 * @date	2005.11.16(��)
 */
//==============================================================================
#ifndef __ACTIN_H__
#define __ACTIN_H__

#include "system/procsys.h"
#include "battle/battle_common.h"
#include "system/buflen.h"
#include "contest/contest.h"
#include "system/softsprite.h"
#include "wazaeffect/we_mana.h"
#include "wazaeffect/we_sys.h"
#include "system/fontproc.h"
#include "system/msgdata.h"
#include "system/gra_tool.h"
#include "system/wordset.h"

#include "contest/actin_ex.h"
#include "contest_order.h"

#include "adv_tool.h"
#include "actin_param.h"
#include "actin_snd_def.h"


//==============================================================================
//	�萔��`
//==============================================================================
///�I���^�[��
#define ACTIN_END_TURN		(4)

///�T�u��ʂ̃T�[�t�F�[�X�ʒu(FX32)
#define ACTIN_SUB_ACTOR_DISTANCE	(BATTLE_SUB_ACTOR_DISTANCE)
///�T�u��ʂ̃T�[�t�F�[�X�ʒu(int)
#define ACTIN_SUB_ACTOR_DISTANCE_INTEGER	(ACTIN_SUB_ACTOR_DISTANCE >> FX32_SHIFT)

///�A�s�[���A�C�R��1�����|�C���g
#define APPEAL_ICON_ONE_POINT		(10)
///�A�s�[���������ɏo���A�A�s�[���|�C���g�A�C�R���̐�(�A�N�^�[��)
#define APPEAL_POINT_ICON_MAX		(6)
///�A�s�[���|�C���g�A�C�R���̕\�������T���邩(2�T�ڂ���̓n�[�g�A�j���̎p���Ⴄ)
#define APPEAL_POINT_ICON_LOOP		(4)

///�{���e�[�W���t���ő吔
#define VOLTAGE_MAX			(5)
///�{���e�[�W�P�̃|�C���g
#define VOLTAGE_ONE_POINT	(10)
///�{���e�[�W���ő吔�t�������̃|�C���g
#define VOLTAGE_POINT_FULL	(VOLTAGE_ONE_POINT * VOLTAGE_MAX)
///�{���e�[�W���ő�ɒB�������ɉ��Z����AP�l(�����R����)
#define VOLTAGE_FULL_ADD_AP_SPECIAL		(APPEAL_ICON_ONE_POINT * 8)
///�{���e�[�W���ő�ɒB�������ɉ��Z����AP�l(���ʂ̐R����)
#define VOLTAGE_FULL_ADD_AP				(APPEAL_ICON_ONE_POINT * 5)

///�Z�G�t�F�N�g���ɏ�ɏo�Ă���|�P�����̐�
#define ACTIN_WAZA_POKEMAX		(2)		//�Z���o���|�P�����{�U���ΏۂƂȂ铧���|�P����

///�ϋq�̊����̃{�����[���W���l
#define ACTIN_AUDIENCE_VOLUME			(70)

///�|�P������ʒuX
#define ACTIN_POKEPOS_X		(CONTEST_ATTACK_POKE_X)
///�|�P������ʒuY
#define ACTIN_POKEPOS_Y		(CONTEST_ATTACK_POKE_Y)
///�|�P������ʒuZ
#define ACTIN_POKEPOS_Z		(CONTEST_ATTACK_POKE_Z)

///�|�P�����o��ʒuX
#define ACTIN_POKEPOS_APPEAR_X	(ACTIN_POKEPOS_X + 40)
///�|�P�����o��ʒuY
#define ACTIN_POKEPOS_APPEAR_Y	(ACTIN_POKEPOS_Y + 60)

///�|�P����IN����O�̃E�F�C�g
#define ACTIN_POKEMOVE_IN_BEFORE_WAIT		(10)

///�|�P����IN���鎞�A��ʒu�܂łɂ�����ړ��t���[����
#define ACTIN_POKEMOVE_IN_FRAME	(7)	//(10)
///�|�P����IN���鎞�̈ړ����xX(����8�r�b�g����)
#define ACTIN_POKEMOVE_IN_X		(((ACTIN_POKEPOS_APPEAR_X - ACTIN_POKEPOS_X) << 8) \
									/ ACTIN_POKEMOVE_IN_FRAME)
///�|�P����IN���鎞�̈ړ����xY(����8�r�b�g����)
#define ACTIN_POKEMOVE_IN_Y		(((ACTIN_POKEPOS_APPEAR_Y - ACTIN_POKEPOS_Y) << 8) \
									/ ACTIN_POKEMOVE_IN_FRAME)

///�|�P����OUT���鎞�A��ʒu�܂łɂ�����ړ��t���[����
#define ACTIN_POKEMOVE_OUT_FRAME	(7)	//(10)
///�|�P����OUT���鎞�̈ړ����xX(����8�r�b�g����)
#define ACTIN_POKEMOVE_OUT_X		(((ACTIN_POKEPOS_APPEAR_X - ACTIN_POKEPOS_X) << 8) \
									/ ACTIN_POKEMOVE_OUT_FRAME)
///�|�P����OUT���鎞�̈ړ����xY(����8�r�b�g����)
#define ACTIN_POKEMOVE_OUT_Y		(((ACTIN_POKEPOS_APPEAR_Y - ACTIN_POKEPOS_Y) << 8) \
									/ ACTIN_POKEMOVE_OUT_FRAME)

///�u���[�_�[���p�l��1��X��(�L�����P��)
#define BREEDER_PANEL_X_LEN			(10)
///�u���[�_�[���p�l��1��Y��(�L�����P��)
#define BREEDER_PANEL_Y_LEN			(6)
///�u���[�_�[���p�l���̍���X�N���[���ʒu(�L�����N�^�P��)
#define BREEDER_PANEL_SCREEN_START_POS	(0)//(32*32 + 22)

///���Z�͕��僁�C����ʂŎg�p����t�H���gOAM�̍ő吔
#define ACTIN_FONTOAM_MAX_MAIN		(2 * BREEDER_MAX)	//(�u���[�_�[�{�j�b�N�l�[��)���Q���l��

//--------------------------------------------------------------
//	�o�b�t�@
//--------------------------------------------------------------
///������o�b�t�@�̃T�C�Y
#define ACTIN_MESSAGE_BUF_SIZE	(2*160)		///<�b��łP�U�O������

///���M�p�o�b�t�@�T�C�Y
#define TRANSMIT_BUF_SIZE		(512)
///��M�p�o�b�t�@�T�C�Y
#define RECEIVE_BUF_SIZE		(TRANSMIT_BUF_SIZE)

//--------------------------------------------------------------
//	���b�Z�[�W�^�O
//--------------------------------------------------------------
///���b�Z�[�W�^�O
enum{
	ATAG_NONE,		///<�^�O�Ȃ�
	ATAG_NOW,		///<���݉��Z���̃|�P������(�j�b�N�l�[��)
	
	ATAG_MINE,		///<�����̃j�b�N�l�[��
	ATAG_ENEMY,		///<�G�̃j�b�N�l�[��
	ATAG_WAZA,		///<�Z��
	ATAG_NUM,		///<1�����l
	ATAG_JUDGE,		///<�R����
	
	ATAG_MINE_ENEMY,
	ATAG_MINE_WAZA,
	ATAG_MINE_NUM,
	ATAG_MINE_JUDGE,
	
	ATAG_ENEMY_MINE,
	ATAG_ENEMY_WAZA,
	ATAG_ENEMY_NUM,
	ATAG_ENEMY_JUDGE,
	
	ATAG_WAZA_MINE,
	ATAG_WAZA_ENEMY,
	ATAG_WAZA_NUM,
	ATAG_WAZA_JUDGE,
	
	ATAG_NUM_MINE,
	ATAG_NUM_ENEMY,
	ATAG_NUM_WAZA,
	ATAG_NUM_JUDGE,

	ATAG_JUDGE_MINE,
	ATAG_JUDGE_ENEMY,
	ATAG_JUDGE_WAZA,
	ATAG_JUDGE_NUM,
	
	ATAG_MINE_JUDGE_WAZA,
	
	//����R�[�h
	ATAG_EXCODE_JUDGESUFFER,	///<����R�[�h�F�R�����
	
	ATAG_MAX,
};

///���b�Z�[�WID�Ȃ�
#define AMSG_ID_NONE		(0xffff)

//--------------------------------------------------------------
//	�t���[���ԍ�
//--------------------------------------------------------------
///�E�B���h�E�E�p�l���ʂ̃t���[��
#define ACTIN_FRAME_WIN				(GF_BGL_FRAME1_M)
///�G�t�F�N�g�ʂ̃t���[��
#define ACTIN_FRAME_EFF				(GF_BGL_FRAME2_M)
///�ϋq(�w�i)�ʂ̃t���[��
#define ACTIN_FRAME_AUDIENCE		(GF_BGL_FRAME3_M)

///�u���[�_�[�p�l���ʂ̃t���[��
#define ACTIN_FRAME_BRDPANEL		(ACTIN_FRAME_EFF)

///�E�B���h�E�E�p�l���ʂ̕W���X�N���[�����WX
#define FRAME_WIN_DEFAULT_X			(0)//(256 + 22*8)
///�E�B���h�E�E�p�l���ʂ̕W���X�N���[�����WY
#define FRAME_WIN_DEFAULT_Y			(0)

///�G�t�F�N�g�ʂ�BG�^�C�v
enum{
	EFF_BG_TYPE_BRDPANEL,		///<�u���[�_�[�p�l��
	EFF_BG_TYPE_EFFECT,			///<�Z�G�t�F�N�g�p
};

//--------------------------------------------------------------
//	BMP�E�B���h�E
//--------------------------------------------------------------
enum{
	ACTIN_BMPWIN_TALK,		///<��b�E�B���h�E
#if 0	//�u���[�_�[����OBJ�ŏo���悤�ɂ����̂ł���Ȃ��Ȃ��� 2006.02.02(��)
	ACTIN_BMPWIN_BREEDER_0,	///<�u���[�_�[1�̖�
	ACTIN_BMPWIN_BREEDER_1,	///<�u���[�_�[2�̖�
	ACTIN_BMPWIN_BREEDER_2,	///<�u���[�_�[3�̖�
	ACTIN_BMPWIN_BREEDER_3,	///<�u���[�_�[4�̖�
#endif

	ACTIN_BMPWIN_MAX,
};

///�u���[�_�[���ɏ������b�Z�[�W�J���[�w��(�G�p)
#define MSGCOLOR_BREEDERPARAM		(GF_PRINTCOLOR_MAKE(5, 6, 0))
///�u���[�_�[���ɏ������b�Z�[�W�J���[�w��(�����p)
#define MSGCOLOR_BREEDERPARAM_MINE	(GF_PRINTCOLOR_MAKE(1, 2, 0))

//--------------------------------------------------------------
//	BG�v���C�I���e�B
//--------------------------------------------------------------
///�u���[�_�[���A�j�b�N�l�[���̃t�H���g�A�N�^�[BG�v���C�I���e�B
#define ACTIN_BGPRI_BREEDER_PARAM	(0)
///�R���A�N�^�[��BG�v���C�I���e�B
#define ACTIN_BGPRI_JUDGE	(3)
///�A�s�[���|�C���g�A�C�R����BG�v���C�I���e�B
#define ACTINSUB_BGPRI_APPEAL_POINT		(0)
///�{���e�[�W���o��BG�v���C�I���e�B
#define ACTIN_BGPRI_VOLTAGE_EFF			(ACTIN_BGPRI_JUDGE)
///�{���e�[�W�|�C���g�A�C�R����BG�v���C�I���e�B
#define ACTINSUB_BGPRI_VOLTAGE_POINT		(ACTIN_BGPRI_JUDGE)
///���A�C�R����BG�v���C�I���e�B
#define ACTINSUB_BGPRI_NEXT_ICON		(ACTIN_BGPRI_BREEDER_PARAM)
///�R�����A�N�V�����A�C�R����BG�v���C�I���e�B
#define ACTIN_BGPRI_JUDGE_REACTION		(ACTIN_BGPRI_JUDGE)

//--------------------------------------------------------------
//	�T�u��ʂ�BG�v���C�I���e�B
//--------------------------------------------------------------
///�����R���ɂ���n�[�g��BG�v���C�I���e�B
#define ACTINSUB_BGPRI_HEART_JUDGE	(1)
///AP�l�n�[�g��BG�v���C�I���e�B
#define ACTINSUB_BGPRI_APP_HEART	(1)

//--------------------------------------------------------------
//	�A�N�^�[�\�t�g�v���C�I���e�B
//--------------------------------------------------------------
enum{
	ACTIN_SOFTPRI_START = 10,

	ACTIN_SOFTPRI_APPEAL_POINT,	///<�A�s�[���|�C���g�A�C�R��
	ACTIN_SOFTPRI_VOLTAGE_EFF,		///<�{���e�[�W���o
	ACTIN_SOFTPRI_VOLTAGE_POINT,	///<�{���e�[�W�|�C���g�A�C�R��
	
	ACTIN_SOFTPRI_NEXT_ICON,		///<���A�C�R��
	ACTIN_SOFTPRI_BREEDER_PARAM,	///<�u���[�_�[���A�j�b�N�l�[���̃t�H���gOAM
	
	ACTIN_SOFTPRI_SPECIAL_HEART = 10000,	///<���ʐR�����ɂ���n�[�g�A�N�^�[
	ACTIN_SOFTPRI_JUDGE_REACTION,	///<�R�����A�N�V�����A�C�R���̃\�t�g�v���C�I���e�B
	ACTIN_SOFTPRI_JUDGE_BOX,	///<�R���{�b�N�X�̃A�N�^�[�\�t�g�v���C�I���e�B
	ACTIN_SOFTPRI_JUDGE,	///<�R���A�N�^�[�̃\�t�g�v���C�I���e�B
};

//--------------------------------------------------------------
//	�T�u��ʂ̃A�N�^�[�\�t�g�v���C�I���e�B
//--------------------------------------------------------------
enum{
	ACTINSUB_SOFTPRI_START = 10,
	
	ACTINSUB_SOFTPRI_HEART_JUDGE = 1000,	///<�����R���ɂ���n�[�g
	ACTINSUB_SOFTPRI_APP_HEART,		///<AP�l�n�[�g
};

//--------------------------------------------------------------
//	���W�F���C�����
//--------------------------------------------------------------
///�u���[�_�[�p�l���̃j�b�N�l�[����{�\�����WX
#define BREEDER_PANEL_NICK_X			(1)
///�u���[�_�[�p�l���̃j�b�N�l�[����{�\�����WY
#define BREEDER_PANEL_NICK_Y			(12)
///�u���[�_�[�p�l���̃j�b�N�l�[���\�����W�̑��̃u���[�_�[�Ƌ󂯂�ԊuY
#define BREEDER_PANEL_NICK_Y_SPACE		(48)
///�u���[�_�[�p�l���̐e����{�\�����WX
#define BREEDER_PANEL_OYA_X				(BREEDER_PANEL_NICK_X)
///�u���[�_�[�p�l���̐e����{�\�����WY
#define BREEDER_PANEL_OYA_Y				(BREEDER_PANEL_NICK_Y + 16)
///�u���[�_�[�p�l���̐e���\�����W�̑��̃u���[�_�[�Ƌ󂯂�ԊuY
#define BREEDER_PANEL_OYA_Y_SPACE		(BREEDER_PANEL_NICK_Y_SPACE)

///�R��0�̍��WX
#define JUDGE_POS_X_0		(8*12)
///�R��0�̍��WY
#define JUDGE_POS_Y_0		(8*5)
///�R���Ɨׂ̐R���̊Ԃ̊ԊuX
#define JUDGE_POS_X_SPACE	(4*8)
///�R���Ɨׂ̐R���̊Ԃ̊ԊuY
#define JUDGE_POS_Y_SPACE	(0)

///�R���{�b�N�X0�̍��WX
#define JUDGE_BOX_POS_X_0		(JUDGE_POS_X_0)
///�R���{�b�N�X0�̍��WY
#define JUDGE_BOX_POS_Y_0		(8*4)
///�R���{�b�N�X�Ɨׂ̐R���{�b�N�X�̊Ԃ̊ԊuX
#define JUDGE_BOX_POS_X_SPACE	(JUDGE_POS_X_SPACE)
///�R���{�b�N�X�Ɨׂ̐R���{�b�N�X�̊Ԃ̊ԊuY
#define JUDGE_BOX_POS_Y_SPACE	(JUDGE_POS_Y_SPACE)

///���ʐR�����ɂ���n�[�g�̍��WX
#define SPECIAL_HEART_POS_X			(JUDGE_POS_X_0)
///���ʐR�����ɂ���n�[�g�̍��WX
#define SPECIAL_HEART_POS_Y			(7*8)
///���ʐR�����ɂ���n�[�g�̍��WX
#define SPECIAL_HEART_POS_X_SPACE	(JUDGE_POS_X_SPACE)

///���A�C�R���̊�{���WX
#define NEXT_ICON_POS_X			(8*8)
///���A�C�R���̊�{���WX
#define NEXT_ICON_POS_Y			(5*8 + 2)
///���A�C�R���̎��̃A�C�R���܂ł̊ԊuY
#define NEXT_ICON_POS_Y_SPACE	(6*8)

///��b�E�B���h�E�J�o�[�Ŏg�p����A�N�^�[��
#define WINCOVER_ACT_MAX			(3)

//--------------------------------------------------------------
//	���W�F�T�u���
//--------------------------------------------------------------
///�R���n�[�g�̍��WX
#define SUB_HEART_JUDGE_POS_X		(5 * 8)
///�R���n�[�g�̍��WY
#define SUB_HEART_JUDGE_POS_Y		(0xc * 8)
///�R���n�[�g�Ɨׂ̐R���n�[�g�܂ł̊ԊuX
#define SUB_HEART_JUDGE_POS_X_SPACE	(11 * 8)
///�R���n�[�g�Ɨׂ̐R���n�[�g�܂ł̊ԊuY
#define SUB_HEART_JUDGE_POS_Y_SPACE	(0)

//--------------------------------------------------------------
//	
//--------------------------------------------------------------
///���ԑ���t���O
enum{
	AWK_SORT_NONE,			///<���ԑ���Ȃ�
	AWK_SORT_SPECIFY_FIRST,	///<���Ԏw��(�ŏ��w��)
	AWK_SORT_SPECIFY_END,	///<���Ԏw��(�Ō�w��)
	AWK_SORT_RANDOM,		///<���ԃ����_��
};

///�Z���ʂŕ\�����郁�b�Z�[�W�^�C�v
enum{
	KOUKA_MSGID_A,
	KOUKA_MSGID_B,
	KOUKA_MSGID_C,
	KOUKA_MSGID_D,
	
	KOUKA_MSGID_SP,
};


//==============================================================================
//	�\���̒�`
//==============================================================================
//--------------------------------------------------------------
//	���b�Z�[�W
//--------------------------------------------------------------
///���Z���僁�b�Z�[�W�f�[�^
typedef struct{
	u16 msg_id;				///<���b�Z�[�WID
	u8 msg_tag;				///<�^�O�R�[�h
	u8 all_put;				///<TRUE:���b�Z�[�W�ꊇ�\��
}ACTIN_MESSAGE_PARAM;

///���b�Z�[�W�^�O�W�J����ꍇ�A�Q�Ƃ����p�����[�^��
typedef struct{
	u8 mine_brd;		///<MINE���w�肳��Ă������ɎQ�Ƃ���u���[�_�[�̔ԍ�
	u8 enemy_brd;		///<ENEMY���w�肳��Ă������ɎQ�Ƃ���u���[�_�[�̔ԍ�
	u16 wazano;			///<WAZA���w�肳��Ă������ɎQ�Ƃ���Z�ԍ�
	u8 num;				///<NUM���w�肳��Ă������ɕ\�����鐔�l
	u8 judge_no;		///<JUDGE���w�肳��Ă������ɎQ�Ƃ���R���̔ԍ�
}ATAG_PARAM;

//--------------------------------------------------------------
//	�Z����
//--------------------------------------------------------------
///�Z���ʂɂ���Ĕ��������l�p�����[�^
typedef struct{
	u16 wazano;				///<�Z�ԍ�
	u8 apno;				///<�A�s�[���ԍ�
	u8 judge_no;			///<�w�������R���ԍ�
	u8 base_ap;				///<��{AP�l
	s16 effective_ap;		///<�Z���ʂɂ���Ĕ�������AP�����Z�l
	
	s8 voltage_add_ap;					///<�{���e�[�W�ɂ���Ĕ�������AP�����Z�l
	
	u8 judge_suffer;					///<������R���̐l��
	
	u8 str_target_no;	///<�����W�J�F�Z���ʂ̃^�[�Q�b�g�ΏۂɂȂ����u���[�_�[�̔ԍ�(�����ȊO)
	u8 str_number;		///<�����W�J�F��������p�����[�^�̐��l
	
	ATAG_PARAM tagpara;					///<���b�Z�[�W�^�O�p�����[�^
	u8 msg_apno;						///<�Z���ʃ��b�Z�[�W���o���ꍇ�A���̋Z��APNo������
	u8 msg_type;						///<�Z���ʃ��b�Z�[�W�^�C�v(KOUKA_MSGID_???)
	
	u8 kouka_occ;
	
	
	s16 base_calc;						///<��{�l�̍��v
	s16 app_total;						///<�ŏI�I�ȍ��vAP�l
	s16 app_total_before;				///<�v�Z�O��AP
	s16 app_total_timing_before;		///<�S���̋Z���ʔ����O��AP�l
	
	
	
	s16 my_effective_ap;				///<�����̋Z���ʂɂ���Ĕ�������AP�����Z�l
	s16 enemy_effective_ap;				///<�G�̋Z���ʂɂ���Ĕ�������AP�����Z�l
	u8 obstruct_apno[BREEDER_MAX];		///<�W�Q�����Ă����u���[�_�[�̕����ɖW�Q�Z�̌��ʔԍ�������



	//-- ������ʃt���O --//
	u32 invalid_special:1;				///<1:������ʖ���
	u32 invalid_voltage_up:1;			///<1:�{���e�[�W�̑�������
	u32 invalid_voltage_down:1;			///<1:�{���e�[�W�̌�������
	u32 voltage_all_down:1;				///<1:�S���̃{���e�[�W��������
	u32 next_sort:2;					///<���ԑ���t���O(AWK_SORT_???)
	u32 next_pos:2;						///<���ԑ��삪�L���Ȏ��A�����ɏ��Ԃ�����
	u32 before_next_sort:2;				///<�Z���ʔ����O�̏��ԑ���t���O(AWK_SORT_???)
	u32 before_next_pos:2;				///<�Z���ʔ����O�̏��ԑ��삪�L���Ȏ��A�����ɏ��Ԃ�����
	u32 twice_next_apno:8;				///<�u���̃^�[��2�{�v���ʔ������A���ʔԍ�������
}AWAZA_PERSONAL;

///�Z���ʂɂ���Ď��̃^�[���Ɍ��ʂ𔭐�����p�����[�^
typedef struct{
	u32 waza_repeat:16;					///<�J��Ԃ��o����Z�ԍ�
	u32 twice_now_apno:8;					///<2�{���ʂ̌��ʔԍ�
}AWAZA_SAVE;

///�Z���ʂɂ���Ĕ�������p�����[�^
typedef struct{
	AWAZA_PERSONAL personal[BREEDER_MAX];	///<�l�p�����[�^
	AWAZA_SAVE save[BREEDER_MAX];			///<���̃^�[���ɂ��e������p�����[�^
	s8 voltage_before[JUDGE_MAX];		///<�A�s�[���O�̃{���e�[�W�l
	s8 voltage_after[JUDGE_MAX];		///<�A�s�[����̃{���e�[�W�l
}AWAZA_PARAM;

//--------------------------------------------------------------
//	
//--------------------------------------------------------------
///AI�̌��ʎ擾�p���[�N
typedef struct{
	u16 wazano[BREEDER_MAX];	///<�Z�ԍ�(!!�莝���̋Z�ʒu�ł͂���܂���!!)
	u8 judge_no[BREEDER_MAX];	///<�R���ԍ�
}ACTIN_AI_ANSWER;

//--------------------------------------------------------------
//	
//--------------------------------------------------------------
///���C���V�[�P���X���Ŏg�p���郍�[�J�����[�N
typedef struct{
	u16 seq;
	u16 select_seq;
	s32 work;
}ACTIN_LOCAL_WORK;

///�ʏ탁�b�Z�[�W(�Z���ʈȊO)
typedef struct{
	ATAG_PARAM a_talk_tagpara;				///<�m�[�}����b�F�^�O�W�J�p�p�����[�^
	ATAG_PARAM after_a_talk_tagpara;		///<�m�[�}����b�F�^�O�W�J�p�p�����[�^
	u8 a_talk_id;					///<�m�[�}����bID(A_TALK_???)
	u8 after_a_talk_id;				///<�|�C���g�����Z��ɍs���m�[�}����bID(A_TALK_???)

	u8 a_talk_bmpwin_close_wait;	///<���b�Z�[�W��\���������Ă���E�B���h�E�����܂ł�wait
	u8 a_talk_bmpwin_not_close;		///<TRUE:�E�B���h�E������ɏI��
}NORMAL_TALK;

///�R����胁�b�Z�[�W�\�����Ɏg�p����p�����[�^
typedef struct{
	u8 judge_no;		///�ΏېR���ԍ�
	u8 suffer_breeder[BREEDER_MAX];		///<�ΏېR�����w�����Ă���u���[�_�[(�ԕ���BREEDER_MAX)
	
	u16 dummy;
	u8 dummy2;
}JUDGE_SUFFER_REVIEW;

//--------------------------------------------------------------
/**
 * @brief   ���Z�͕���i�s�p�����[�^(���݋Z���o���Ă���|�P�����̐i�s�p�����[�^)
 */
//--------------------------------------------------------------
typedef struct{
	u8 now_breeder;					///<���ݏ�ɏo�Ă���u���[�_�[�̔ԍ�
	u8 now_pos;						///<���ݏ�ɏo�Ă���u���[�_�[�����ԖڂɃA�s�[�����Ă��邩
	u8 judge_no;					///<�I�񂾐R���̔ԍ�
	u8 judge_reaction_type;			///<�R���̃��A�N�V�����^�C�v
	
	u8 judge_select_breeder[JUDGE_MAX][BREEDER_MAX];	///���̐R�����w�������u���[�_�[No������
	
//	u16 waza_no;					///<�Z�ԍ�
//	u8 now_sort[BREEDER_MAX];	///<���݂̃^�[���̃A�s�[����(�A�s�[�����Ƀu���[�_�[No�������Ă�)
	
	//�Z���ʌv�Z����
//	s8 ap_point;			///<�J��o�����Z�̊�{AP�l
//	s8 ap_point_calc;		///<�J��o�����Z�̌v�Z��̍ŏI�I��AP�l
//	s8 voltage_now;			///<�{���e�[�W�v�Z�O�̒l
//	s8 voltage_calc;		///<�o�����Z�ɂ���ĕύX���ꂽ�{���e�[�W�l�A�v�Z��̒l
//	s8 voltage_add_ap;		///<�{���e�[�W�ɂ���đ�������AP�l
//	u8 judge_suffer;		///<�w�������R����������l��
	
	AWAZA_PARAM wazapara;			///<�Z���ʌv�Z����
//	u8 next_sort[BREEDER_MAX];		///<���ԑ���t���O(AWK_SORT_???)
//	u8 next_pos[BREEDER_MAX];		///<���ԑ��삪�L���Ȏ��A�����ɏ��Ԃ�����
	
	NORMAL_TALK nt;			//�ʏ탁�b�Z�[�W(�Z���ʈȊO)
	
	union{
		JUDGE_SUFFER_REVIEW jsr;	//�R����胁�b�Z�[�W�\�����Ɏg�p����p�����[�^
	};
}ACTIN_ADVANCE_PARAM;

//--------------------------------------------------------------
/**
 * @brief   ���Z�͕���Q�[���i�s�p�����[�^
 *
 * ���̃p�����[�^������ΑS��ʂ��č\�z�o���邾���̏�񂪓����Ă��܂��B
 * �ʐM���̓T�[�o�[����q�@�̓f�[�^���󂯎�鎖�ɂȂ�܂��B
 * ��{�I�Ƀ��j���[��ʂ���̉�ʕ��A�̂悤�Ȏ����Ȃ�����A
 * �X�̎q�@���Œl���Q�Ƃ��鎖�͂Ȃ��͂��ł��B
 */
//--------------------------------------------------------------
typedef struct{
	u8 turn;						///<���݂̌o�߃^�[��
	u8 breeder_sort[BREEDER_MAX];	///<�Z���o������(�o�鏇�Ƀu���[�_�[�ԍ��������Ă܂�)
	u8 breeder_end_count;			///<�s�����I�������u���[�_�[�̐����J�E���g
	u16 waza_no[BREEDER_MAX];		///<���݂̃^�[���A�e�u���[�_�[���o���Z
	u8 judge_no[BREEDER_MAX];		///<���݂̃^�[���A�e�u���[�_�[���I�������R��NO
	s16 app_total[BREEDER_MAX];		///<���vAP�l
	s16 app_turn[BREEDER_MAX];		///<���̃^�[���ŉ҂���AP�l
	s8 voltage_total[JUDGE_MAX];	///<�{���e�[�W���v
	u16 waza_history[BREEDER_MAX];	///<�O�̃^�[���ŏo�����Z�̗���
	AWAZA_PARAM wazapara;			///<�Z���ʌv�Z���ʃp�����[�^
}ACTIN_GAME_PARAM;

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
}ACTIN_ORDER_PARAM;

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
	
	SOFT_SPRITE_MANAGER	*soft_sprite;
	SOFT_SPRITE *ss[BREEDER_MAX];
	CATS_SYS_PTR		csp;
	CATS_RES_PTR		crp;
	WE_SYS_PTR			wsp;
	GF_BGL_INI *bgl;
	GF_BGL_BMPWIN win[ACTIN_BMPWIN_MAX];
	MSGDATA_MANAGER *actin_msg;		///<���Z�͕��僁�b�Z�[�W�p���b�Z�[�W�f�[�^�}�l�[�W���̃|�C���^
	MSGDATA_MANAGER *breeder_msg;	///<�u���[�_�[���b�Z�[�W�f�[�^�}�l�[�W���̃|�C���^
	MSGDATA_MANAGER *explain_msg;	///<�Z�������b�Z�[�W�f�[�^�}�l�[�W���̃|�C���^
	MSGDATA_MANAGER *wazakouka_msg;	///<�Z���ʃ��b�Z�[�W�f�[�^�}�l�[�W���̃|�C���^
	WORDSET *wordset;				///<Alloc�������b�Z�[�W�p�P��o�b�t�@�ւ̃|�C���^
	STRBUF *msg_buf;				///<Alloc����������o�b�t�@�ւ̃|�C���^
	PALETTE_FADE_PTR pfd;			///<�p���b�g�t�F�[�h�V�X�e���ւ̃|�C���^
	FONTOAM_SYS_PTR fontoam_sys;	///<�t�H���gOAM�V�X�e���ւ̃|�C���^

	EXCHR_PARAM exchr_param[BREEDER_MAX];		///<�Z�G�t�F�N�g�p�L�����W�J�o�b�t�@
	EXCHR_PARAM transparent_exchr_param;		///<�����\�t�g�E�F�A�X�v���C�g�p�̓W�J�o�b�t�@
	
	CATS_ACT_PTR judge_cap[JUDGE_MAX];			///<�R���A�N�^�[�ւ̃|�C���^
	CATS_ACT_PTR judge_box_cap[JUDGE_MAX];		///<�R���{�b�N�X�A�N�^�[�ւ̃|�C���^
	CATS_ACT_PTR special_heart_cap;				///<���ʐR�����ɂ���n�[�g
	CATS_ACT_PTR appeal_point_cap[BREEDER_MAX][APPEAL_POINT_ICON_MAX];
	CATS_ACT_PTR voltage_point_cap[JUDGE_MAX][VOLTAGE_MAX];
	CATS_ACT_PTR nexticon_cap[BREEDER_MAX];			///<���A�C�R���A�N�^�[�ւ̃|�C���^
	CATS_ACT_PTR wincover_cap[WINCOVER_ACT_MAX];	///<��b�E�B���h�E�X�N���[�����̃J�o�[
	CATS_ACT_PTR judge_reaction_icon_cap;		///<�R�����A�N�V�����A�C�R���A�N�^�[
	
	ADV_FONTACT fontact_oya[BREEDER_MAX];		///<�e���̃t�H���g�A�N�^�[
	ADV_FONTACT fontact_nickname[BREEDER_MAX];	///<�j�b�N�l�[���̃t�H���g�A�N�^�[
	
	u8 talk_msg_index;				///<�����`�惋�[�`���̃C���f�b�N�X
}ACTIN_SYSTEM_PARAM;

//--------------------------------------------------------------
/**
 * �f�o�b�O�ł̂ݎg�p���郏�[�N
 */
//--------------------------------------------------------------
typedef struct{
	GF_BGL_BMPWIN win;
	s16 wazano;
	u8 sub_seq;
}ACTIN_DEBUG_WORK;

//--------------------------------------------------------------
/**
 * @brief   ���Z�͕���Ǘ����[�N
 *
 * ���Z�͕���S�̂��Ǘ�����匳�̃��[�N�ɂȂ�܂��B
 * �ʐM���ł��S�Ẵ}�V���Ōʂɍ쐬����܂�
 */
//--------------------------------------------------------------
typedef struct{
	CONTEST_SYSTEM *consys;			///<�R���e�X�g�V�X�e�����[�N�ւ̃|�C���^
	TCB_PTR update_tcb;
	GF_G3DMAN *g3Dman;
	
	ACTIN_SYSTEM_PARAM sys;			///<���Z�͕���V�X�e���f�[�^�p�����[�^
	ACTIN_GAME_PARAM a_game;			///<�Q�[���i�s�p�����[�^
	ACTIN_ADVANCE_PARAM advance;	///<�i�s�p�����[�^
	ACTIN_ORDER_PARAM order[BREEDER_MAX];	///<���߃p�����[�^
	
	void *aip;						///<�T�u��ʐ���V�X�e���\���̂ւ̃|�C���^
	
	u16 seq;
	u16 tbl_seq_no;					///<���C���V�[�P���X�e�[�u���̔ԍ�
	u8 proc_mode;					///<���݂̓����

	//-- ����M�o�b�t�@ --//
	u32 request_bit;				///<���߂��o���Ă���r�b�g
	u8 transmit_buf[TRANSMIT_BUF_SIZE];	///<���M�p�o�b�t�@
	u8 receive_buf[RECEIVE_BUF_SIZE];	///<��M�p�o�b�t�@
	u8 transmit_flag;				///<TRUE�F���M�҂��B�@FALSE:�V���ȃf�[�^�Z�b�g�\
	u8 receive_flag;				///<TRUE�F�f�[�^��M����
	
	CONTEST_ORDER_WORK cow;			///<����M���[�N

	ACTIN_LOCAL_WORK local;			///<���[�J�����[�N
	u8 main_end;					///<TRUE:���C�������I��
	
	u8 effect_count;				///<�ėp�G�t�F�N�g�J�E���^���[�N
	
	u8  hensin_flag[BREEDER_MAX];	///<TRUE�F�ϐg���
	
#ifdef PM_DEBUG
	ACTIN_DEBUG_WORK debug;			///<�f�o�b�O�p���[�N
#endif
}ACTIN_PROC_WORK;


//==============================================================================
//	�O���f�[�^�錾
//==============================================================================
extern const PROC_DATA ContestActinProcData;

//==============================================================================
//	�O���֐��錾
//==============================================================================
extern PROC_RESULT ActinProc_Init( PROC * proc, int * seq );
extern PROC_RESULT ActinProc_Main( PROC * proc, int * seq );
extern PROC_RESULT ActinProc_End( PROC * proc, int * seq );
extern void ActinBG_BrdPanelSet(ACTIN_PROC_WORK *apw, int eff_bg_type, int disp_set);

//--------------------------------------------------------------
//	actin_waza.c
//--------------------------------------------------------------
extern void AWAZA_WazaParaTurnInit(ACTIN_PROC_WORK *apw, AWAZA_PARAM *wp);
extern void AWAZA_WazaParaBreederInit(ACTIN_PROC_WORK *apw, AWAZA_PARAM *wp, int breeder_no);
extern void AWAZA_WazaParaBreederGameUpdate(ACTIN_PROC_WORK *apw, AWAZA_PARAM *wp, int breeder_no);
extern void AWAZA_WazaParaTurnGameUpdate(ACTIN_PROC_WORK *apw, AWAZA_PARAM *wp);
extern void AWAZA_FirstMsg(ACTIN_PROC_WORK *apw, AWAZA_PARAM *wp, int breeder_no);
extern void AWAZA_BaseAP(ACTIN_PROC_WORK *apw, AWAZA_PARAM *wp, int breeder_no);
extern void AWAZA_Kouka(ACTIN_PROC_WORK *apw, AWAZA_PARAM *wp, 
	int now_breeder, int now_breeder_pos);
extern void AWAZA_KoukaSpecial(ACTIN_PROC_WORK *apw, AWAZA_PARAM *wp, 
	int now_breeder, int now_breeder_pos);
extern BOOL AWAZA_KoukaAfterTiming(ACTIN_PROC_WORK *apw, AWAZA_PARAM *wp, int now_breeder, 
	int now_breeder_pos);
extern BOOL AWAZA_KoukaJudgeSufferTiming(ACTIN_PROC_WORK *apw, AWAZA_PARAM *wp, int now_breeder, 
	int now_breeder_pos);
extern BOOL AWAZA_KoukaEndTiming(ACTIN_PROC_WORK *apw, AWAZA_PARAM *wp, int now_breeder, 
	int now_breeder_pos);
extern void AWAZA_Voltage(ACTIN_PROC_WORK *apw, AWAZA_PARAM *wp, int breeder_no, NORMAL_TALK *nt);
extern void AWAZA_JudgeSuffer(ACTIN_PROC_WORK *apw, AWAZA_PARAM *wp, int now_breeder, 
	NORMAL_TALK *nt);
extern void AWAZA_TimingBeforeAppUpdate(AWAZA_PARAM *wp);

//--------------------------------------------------------------
//	actin_ai.c
//--------------------------------------------------------------
extern void ActinAI_Main(ACTIN_PROC_WORK *apw, ACTIN_AI_ANSWER *answer);


#endif	//__ACTIN_H__

