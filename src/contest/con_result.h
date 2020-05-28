//==============================================================================
/**
 * @file	con_result.h
 * @brief	�R���e�X�g���ʔ��\��ʂ̃w�b�_
 * @author	matsuda
 * @date	2006.03.17(��)
 */
//==============================================================================
#ifndef __CON_RESULT_H__
#define __CON_RESULT_H__

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

#include "adv_tool.h"
#include "res_snd_def.h"



//==============================================================================
//	�萔��`
//==============================================================================
//--------------------------------------------------------------
//	���ʔ��\��ʂ̉�ʃ��[�h
//--------------------------------------------------------------
///���݂̉�ʃ��[�h
enum{
	RESDISP_MODE_ANNOUNCE,		///<�A�i�E���X���
	RESDISP_MODE_RESULT,		///<���ʔ��\���
};

//--------------------------------------------------------------
//	
//--------------------------------------------------------------
///�|�P������ʒuZ(���C���_���T�[)
#define CONRES_POKEPOS_Z_MAIN		(APPEAR_Z_TYPE_AA)
///�|�P������ʒuZ(�o�b�N�_���T�[)
#define CONRES_POKEPOS_Z_SUB			(CONRES_POKEPOS_Z_MAIN - 0x80)

///���C���_���T�[�̃|�P�����g�k��(XY����)
#define CONRES_POKEAFF_MAIN		(0x0100)
///�o�b�N�_���T�[�̃|�P�����g�k��(XY����)
#define CONRES_POKEAFF_BACK		(0x00c0)	//(0x0080)

///�_���X���僁�C����ʂŎg�p����t�H���gOAM�̍ő吔
#define CONRES_FONTOAM_MAX_MAIN	(10)	// 10 = �Ƃ肠�����K��

//--------------------------------------------------------------
//	�o�b�t�@
//--------------------------------------------------------------
///������o�b�t�@�̃T�C�Y
#define CONRES_MESSAGE_BUF_SIZE	(2*160)		///<�b��łP�U�O������

//--------------------------------------------------------------
//	�t���[���ԍ�
//--------------------------------------------------------------
///�E�B���h�E�E���b�Z�[�W�ʂ̃t���[��
#define CONRES_FRAME_WIN				(GF_BGL_FRAME1_M)
///�G�t�F�N�g�ʂ̃t���[��
#define CONRES_FRAME_EFF				(GF_BGL_FRAME2_M)
///�w�i�ʂ̃t���[��
#define CONRES_FRAME_BACKGROUND			(GF_BGL_FRAME3_M)

///�T�u��ʁF�ϋq�ʂ̃t���[��
#define CONRES_FRAME_SUB_AUDIENCE		(GF_BGL_FRAME0_S)

///BG�ԍ��F�E�B���h�E
#define CONRES_BGNO_WIN			(1)
///BG�ԍ��F�G�t�F�N�g
#define CONRES_BGNO_EFF			(2)
///BG�ԍ��F�w�i
#define CONRES_BGNO_BACKGROUND	(3)

///GX_WND�ԍ��F�G�t�F�N�g
#define CONRES_GX_WND_EFF			(GX_WND_PLANEMASK_BG2)

///<3D�ʂ�BG�v���C�I���e�B
#define CONRES_3DBG_PRIORITY		(1)
///�E�B���h�E�ʂ�BG�v���C�I���e�B
#define CONRES_BGPRI_WIN			(2)
///�G�t�F�N�g�ʂ�BG�v���C�I���e�B
#define CONRES_BGPRI_EFF			(1)
///�w�i�ʂ�BG�v���C�I���e�B
#define CONRES_BGPRI_BACKGROUND		(3)

///<�T�u��ʁF�w�i�ʂ�BG�v���C�I���e�B
///�ϋq�ʂ�BG�v���C�I���e�B
#define CONRES_BGPRI_SUB_AUDIENCE	(3)

//--------------------------------------------------------------
//	��b�E�B���h�E
//--------------------------------------------------------------
///��b�E�B���h�E�̃L�����N�^�]���I�t�Z�b�g(�L�����N�^�P��)
#define CONRES_TALKWIN_CGX_OFFSET	(1)
///��b�E�B���h�E�w�i�F
#define CONRES_TALKWIN_BACK_COLOR	(15)
///��b�E�B���h�E�̃p���b�g�ԍ�
#define CONRES_TALKWIN_PALNO		(14)

//--------------------------------------------------------------
//	BMP�E�B���h�E
//--------------------------------------------------------------
///BMP�E�B���h�ECGX�G���A�J�n�ʒu(�I�t�Z�b�g)
#define RES_BMPWIN_CGX_START			(TALK_WIN_CGX_SIZ + CONRES_TALKWIN_CGX_OFFSET)

#define RES_BMPWIN_TALK_COLOR			(13)
#define RES_BMPWIN_TALK_CGX_OFFSET		(RES_BMPWIN_CGX_START)
#define RES_BMPWIN_TALK_POS_X			(0x2)
#define RES_BMPWIN_TALK_POS_Y			(0x13)
#define RES_BMPWIN_TALK_SIZE_X			(27)
#define RES_BMPWIN_TALK_SIZE_Y			(4)
#define RES_BMPWIN_TALK_CGX_SIZE		(RES_BMPWIN_TALK_SIZE_X * RES_BMPWIN_TALK_SIZE_Y)

#define RES_BMPWIN_NAME_COLOR			(RES_BMPWIN_TALK_COLOR)
#define RES_BMPWIN_NAME_GF_COLOR		(GF_PRINTCOLOR_MAKE(1, 2, 0))
#define RES_BMPWIN_NAME_DOT_OFFSET		(3)

#define RES_BMPWIN_NICK_SIZE_X			(8)
#define RES_BMPWIN_NICK_SIZE_Y			(3)		//�\���ʒu�𐔃h�b�g���ɂ��炷�̂�3�L�����ɂ܂���
#define RES_BMPWIN_NICK_CGX_SIZE		(RES_BMPWIN_NICK_SIZE_X * RES_BMPWIN_NICK_SIZE_Y)
#define RES_BMPWIN_POS_X_NICK			(6)
#define RES_BMPWIN_POS_Y_NICK			(1)
#define RES_BMPWIN_POS_Y_SPACE_NICK		(4)

#define RES_BMPWIN_OYA_SIZE_X			(8)
#define RES_BMPWIN_OYA_SIZE_Y			(3)		//�\���ʒu�𐔃h�b�g���ɂ��炷�̂�3�L�����ɂ܂���
#define RES_BMPWIN_OYA_CGX_SIZE			(RES_BMPWIN_OYA_SIZE_X * RES_BMPWIN_OYA_SIZE_Y)
#define RES_BMPWIN_POS_X_OYA			(0x10)
#define RES_BMPWIN_POS_Y_OYA			(RES_BMPWIN_POS_Y_NICK)
#define RES_BMPWIN_POS_Y_SPACE_OYA		(RES_BMPWIN_POS_Y_SPACE_NICK)

#define RES_BMPWIN_NICK_CGX_OFFSET_0	(RES_BMPWIN_TALK_CGX_OFFSET + RES_BMPWIN_TALK_CGX_SIZE)
#define RES_BMPWIN_NICK_CGX_OFFSET_1	(RES_BMPWIN_NICK_CGX_OFFSET_0 + RES_BMPWIN_NICK_CGX_SIZE)
#define RES_BMPWIN_NICK_CGX_OFFSET_2	(RES_BMPWIN_NICK_CGX_OFFSET_1 + RES_BMPWIN_NICK_CGX_SIZE)
#define RES_BMPWIN_NICK_CGX_OFFSET_3	(RES_BMPWIN_NICK_CGX_OFFSET_2 + RES_BMPWIN_NICK_CGX_SIZE)

#define RES_BMPWIN_OYA_CGX_OFFSET_0	(RES_BMPWIN_NICK_CGX_OFFSET_3 + RES_BMPWIN_NICK_CGX_SIZE)
#define RES_BMPWIN_OYA_CGX_OFFSET_1	(RES_BMPWIN_OYA_CGX_OFFSET_0 + RES_BMPWIN_OYA_CGX_SIZE)
#define RES_BMPWIN_OYA_CGX_OFFSET_2	(RES_BMPWIN_OYA_CGX_OFFSET_1 + RES_BMPWIN_OYA_CGX_SIZE)
#define RES_BMPWIN_OYA_CGX_OFFSET_3	(RES_BMPWIN_OYA_CGX_OFFSET_2 + RES_BMPWIN_OYA_CGX_SIZE)

//--------------------------------------------------------------
//	BMP�E�B���h�E
//--------------------------------------------------------------
enum{
	CONRES_BMPWIN_TALK,		///<��b�E�B���h�E
	
	CONRES_BMPWIN_NICK_0,	///<�j�b�N�l�[��
	CONRES_BMPWIN_NICK_1,	///<�j�b�N�l�[��
	CONRES_BMPWIN_NICK_2,	///<�j�b�N�l�[��
	CONRES_BMPWIN_NICK_3,	///<�j�b�N�l�[��

	CONRES_BMPWIN_OYA_0,	///<�e��
	CONRES_BMPWIN_OYA_1,	///<�e��
	CONRES_BMPWIN_OYA_2,	///<�e��
	CONRES_BMPWIN_OYA_3,	///<�e��
	
	CONRES_BMPWIN_MAX,
};

//--------------------------------------------------------------
//	���b�Z�[�W
//--------------------------------------------------------------
///���b�Z�[�W�^�O
enum{
	CRTAG_NONE,		///<�^�O�Ȃ�
	
	CRTAG_RANK,		///<�R���e�X�g�����N
	CRTAG_OYA_NICK,	///<�e���A�j�b�N�l�[��
	CRTAG_NUM_OYA_NICK,	///<���l�A�e���A�j�b�N�l�[��
	
	CRTAG_MAX,
};

//--------------------------------------------------------------
//	�A�N�^�[�v���C�I���e�B
//--------------------------------------------------------------
///�ԕ��͗l��BG�v���C�I���e�B
#define R_FLOWER_BGPRI				(CONRES_BGPRI_BACKGROUND)
///�ԕ��͗l�̃\�t�g�v���C�I���e�B
#define R_FLOWER_SOFTPRI			(200)

///�|�P�����A�C�R����BG�v���C�I���e�B
#define R_POKEICON_BGPRI			(CONRES_BGPRI_BACKGROUND)
///�|�P�����A�C�R���̃\�t�g�v���C�I���e�B
#define R_POKEICON_SOFTPRI			(100)

///���ӂԂ���BG�v���C�I���e�B
#define R_CONFETTI_BGPRI			(CONRES_BGPRI_EFF)
///���ӂԂ��̃\�t�g�v���C�I���e�B
#define R_CONFETTI_SOFTPRI			(20)

///���ʃA�C�R����BG�v���C�I���e�B
#define R_RANKING_BGPRI				(CONRES_BGPRI_BACKGROUND)
///���ʃA�C�R���̃\�t�g�v���C�I���e�B
#define R_RANKING_SOFTPRI			(100)

///���[�^�[��BG�v���C�I���e�B
#define R_METER_BGPRI				(CONRES_BGPRI_BACKGROUND)
///���[�^�[�̃\�t�g�v���C�I���e�B
#define R_METER_SOFTPRI				(110)

//--------------------------------------------------------------
//	���_�擾�֘A
//--------------------------------------------------------------
///1�ʂ̓��_����Ɋe�u���[�_�[�������[�^�[�̃p�[�Z���e�[�W���擾����ۂ�MAX�p�[�Z���e�[�W
#define RES_METER_PERCENT_MAX		(100)
///���_���[�^�[�ő�L������
#define RES_METER_CHAR_MAX			(24)
///���_���[�^�[�ő�h�b�g��
#define RES_METER_DOT_MAX			(RES_METER_CHAR_MAX * 8)

///���[�^�[�̃A�N�^�[�P�̉����h�b�g��
#define RES_METER_ACT_SIZE_X		(16)
///���[�^�[�A�N�^�[��
#define RES_METER_CAP_MAX			(RES_METER_DOT_MAX / RES_METER_ACT_SIZE_X)


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
}CONRES_MESSAGE_PARAM;

///���b�Z�[�W�^�O�W�J����ꍇ�A�Q�Ƃ����p�����[�^��
typedef struct{
	u8 mine_brd;		///<MINE���w�肳��Ă������ɎQ�Ƃ���u���[�_�[�̔ԍ�
	u8 enemy_brd;		///<ENEMY���w�肳��Ă������ɎQ�Ƃ���u���[�_�[�̔ԍ�
	u16 wazano;			///<WAZA���w�肳��Ă������ɎQ�Ƃ���Z�ԍ�
	u8 num;				///<NUM���w�肳��Ă������ɕ\�����鐔�l
	u8 judge_no;		///<JUDGE���w�肳��Ă������ɎQ�Ƃ���R���̔ԍ�
}CRTAG_PARAM;

//--------------------------------------------------------------
//	
//--------------------------------------------------------------

///���C���V�[�P���X���Ŏg�p���郍�[�J�����[�N
typedef struct{
	u16 seq;
	u16 select_seq;
	s32 work;
}CONRES_LOCAL_WORK;

//--------------------------------------------------------------
/**
 * @brief   �_���X����i�s�p�����[�^(���݋Z���o���Ă���|�P�����̐i�s�p�����[�^)
 */
//--------------------------------------------------------------
typedef struct{
	u8 now_breeder;					///<���ݏ�ɏo�Ă���u���[�_�[�̔ԍ�
	u8 now_pos;						///<���ݏ�ɏo�Ă���u���[�_�[�����ԖڂɃA�s�[�����Ă��邩
	
	u8 victory_breeder;				///<�D�������u���[�_�[�̔ԍ�
	u8 ranking[BREEDER_MAX];		///<����(1�ʂ��珇�Ƀu���[�_�[�ԍ�������܂�)
	
	u8 meter_type;					///<�L�΂����[�^�[�^�C�v(CONGAME_???)
	
	CRTAG_PARAM a_talk_tagpara;		///<�m�[�}����b�F�^�O�W�J�p�p�����[�^
	u8 a_talk_id;					///<�m�[�}����bID(A_TALK_CONRES_???)
	u8 a_talk_bmpwin_close_wait;	///<���b�Z�[�W��\���������Ă���E�B���h�E�����܂ł�wait
	u8 a_talk_bmpwin_not_close;		///<TRUE:�E�B���h�E������ɏI��
	u8 a_talk_bmpwin_not_open;		///<TRUE:�E�B���h�E�`����s��Ȃ�
}CONRES_ADVANCE_PARAM;

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
	CONTEST_SCORE score[BREEDER_MAX];	///<���_
	
	u8 breeder_sort[BREEDER_MAX];	///<�Z���o������(�o�鏇�Ƀu���[�_�[�ԍ��������Ă܂�)
	u8 breeder_end_count;			///<�s�����I�������u���[�_�[�̐����J�E���g

	u8 ranking[BREEDER_MAX];		///<����(1�ʂ��珇�Ƀu���[�_�[�ԍ�������܂�)
	s16 visual_revise[BREEDER_MAX];	///<�r�W���A���Q�[���F�C���l
	s16 dance_revise[BREEDER_MAX];	///<�_���X�Q�[���F�C���l
	s16 actin_revise[BREEDER_MAX];	///<���Z�Q�[���F�C���l
	s16 total_revise[BREEDER_MAX];	///<�����C���l
	s16 visual_percent[BREEDER_MAX];	///<�r�W���A���Q�[���F�C���l
	s16 dance_percent[BREEDER_MAX];	///<�_���X�Q�[���F�C���l
	s16 actin_percent[BREEDER_MAX];	///<���Z�Q�[���F�C���l
	s16 total_percent[BREEDER_MAX];	///<�����C���l��1�ʂ�100%�����ꍇ�̕ϊ���������
	s16 gauge_dot[BREEDER_MAX];		///<total_percent���h�b�g���ɕϊ���������
	s16 visual_dot[BREEDER_MAX];	///<�r�W���A�������Q�[�W�h�b�g��
	s16 dance_dot[BREEDER_MAX];		///<�_���X�����Q�[�W�h�b�g��
	s16 actin_dot[BREEDER_MAX];		///<���Z�����Q�[�W�h�b�g��
}CONRES_GAME_PARAM;

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
}CONRES_ORDER_PARAM;

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
	GF_BGL_INI *bgl;
	GF_BGL_BMPWIN win[CONRES_BMPWIN_MAX];
	MSGDATA_MANAGER *conres_msg;	///<�_���X���僁�b�Z�[�W�p���b�Z�[�W�}�l�[�W���̃|�C���^
	WORDSET *wordset;
	STRBUF *msg_buf;				///<Alloc����������o�b�t�@�ւ̃|�C���^
	PALETTE_FADE_PTR pfd;			///<�p���b�g�t�F�[�h�V�X�e���ւ̃|�C���^
	FONTOAM_SYS_PTR fontoam_sys;	///<�t�H���gOAM�V�X�e���ւ̃|�C���^
	
	EXCHR_PARAM exchr_param[BREEDER_MAX];		///<�Z�G�t�F�N�g�p�L�����W�J�o�b�t�@

	FLOWER_WORK flower;				///<�ԕ��͗l���䃏�[�N

	TCB_PTR pokeicon_tcb;							///<�|�P�����A�C�R���A�j���X�V�����^�X�N
	CATS_ACT_PTR pokeicon_cap[BREEDER_MAX];			///<�|�P�����A�C�R���A�N�^�[�ւ̃|�C���^
	CATS_ACT_PTR ranking_cap[BREEDER_MAX];			///<���ʃA�N�^�[�ւ̃|�C���^
	CATS_ACT_PTR visual_meter_cap[BREEDER_MAX][RES_METER_CAP_MAX];	///<�r�W���A�����[�^�[
	CATS_ACT_PTR dance_meter_cap[BREEDER_MAX][RES_METER_CAP_MAX];	///<�_���X���[�^�[
	CATS_ACT_PTR actin_meter_cap[BREEDER_MAX][RES_METER_CAP_MAX];	///<���Z���[�^�[
	
	u8 talk_msg_index;				///<�����`�惋�[�`���̃C���f�b�N�X
}CONRES_SYSTEM_PARAM;

//--------------------------------------------------------------
/**
 * @brief   �_���X����Ǘ����[�N
 *
 * �_���X����S�̂��Ǘ�����匳�̃��[�N�ɂȂ�܂��B
 * �ʐM���ł��S�Ẵ}�V���Ōʂɍ쐬����܂�
 */
//--------------------------------------------------------------
typedef struct _CONRES_PROC_WORK{
	CONTEST_SYSTEM *consys;			///<�R���e�X�g�V�X�e�����[�N�ւ̃|�C���^
	TCB_PTR update_tcb;				///<�V�X�e���X�V����
	TCB_PTR vintr_tcb;				///<V�u�����N���荞�݃^�X�N
	GF_G3DMAN *g3Dman;
	
	CONRES_SYSTEM_PARAM sys;			///<�_���X����V�X�e���f�[�^�p�����[�^
	CONRES_GAME_PARAM r_game;			///<�Q�[���i�s�p�����[�^
	CONRES_ADVANCE_PARAM advance;		///<�i�s�p�����[�^
	CONRES_ORDER_PARAM order[BREEDER_MAX];	///<���߃p�����[�^
	
	void *flash_eff;				///<�J�����̃t���b�V���G�t�F�N�g���[�N
	
	u16 seq;
	u16 tbl_seq_no;					///<���C���V�[�P���X�e�[�u���̔ԍ�
	u8 proc_mode;					///<���݂̓����

	u8 wnd0_x1;						///<�E�B���h�E0��X1���W
	u8 wnd0_y1;
	u8 wnd0_x2;
	u8 wnd0_y2;

	u8 wnd1_x1;
	u8 wnd1_y1;
	u8 wnd1_x2;
	u8 wnd1_y2;
	
	CONTEST_ORDER_WORK cow;			///<����M���[�N

	CONRES_LOCAL_WORK local;			///<���[�J�����[�N
	u8 main_end;					///<TRUE:���C�������I��
	
	u8 confetti_end;				///<TRUE:���ӂԂ��A�N�^�[�폜���N�G�X�g
	u8 confetti_count;				///<���ӂԂ�����������Ă��鐔���J�E���g
	
	u8 disp_mode;					///<RESDISP_MODE_???
}CONRES_PROC_WORK;


//==============================================================================
//	�O���֐��錾
//==============================================================================
extern PROC_RESULT ConresProc_Init( PROC * proc, int * seq );
extern PROC_RESULT ConresProc_Main( PROC * proc, int * seq );
extern PROC_RESULT ConresProc_End( PROC * proc, int * seq );

//==============================================================================
//	�O���f�[�^�錾
//==============================================================================
extern const PROC_DATA ContestResultProcData;



#endif	//__CON_RESULT_H__

