//==============================================================================
/**
 * @file	visual.h
 * @brief	�r�W���A������̃w�b�_
 * @author	matsuda
 * @date	2005.12.10(�y)
 */
//==============================================================================
#ifndef __VISUAL_H__
#define __VISUAL_H__

#include "system/procsys.h"
#include "battle/battle_common.h"
#include "system/buflen.h"
#include "contest/contest.h"
#include "system/softsprite.h"
#include "system/fontproc.h"
#include "system/msgdata.h"
#include "system/gra_tool.h"
#include "system/clact_tool.h"
#include "system/wordset.h"
#include "contest_order.h"
#include "visual_snd_def.h"
#include "contest/visual_ex.h"
#include "contest_type.h"



//==============================================================================
//	�萔��`
//==============================================================================
///�ϋq�������ɏo����n�[�g�̐�
#define VISUAL_AUDIENCE_HEART_MAX		(8)

///�T�u��ʂ̃T�[�t�F�[�X�ʒu
#define VISUAL_SUB_ACTOR_DISTANCE		(256 * FX32_ONE)

//--------------------------------------------------------------
//	�o�b�t�@
//--------------------------------------------------------------
///������o�b�t�@�̃T�C�Y
#define VISUAL_MESSAGE_BUF_SIZE	(2*160)		///<�b��łP�U�O������

//--------------------------------------------------------------
//	�t���[���ԍ��F���C��
//--------------------------------------------------------------
///�E�B���h�E�E�p�l���ʂ̃t���[��
#define VISUAL_FRAME_WIN				(GF_BGL_FRAME1_M)
///�G�t�F�N�g�ʂ̃t���[��
#define VISUAL_FRAME_EFF				(GF_BGL_FRAME2_M)
///�ϋq(�w�i)�ʂ̃t���[��
#define VISUAL_FRAME_BACKGROUND			(GF_BGL_FRAME3_M)

///<BG�ԍ��F�E�B���h�E
#define VISUAL_BGNO_WIN			(1)
///<BG�ԍ��F�G�t�F�N�g
#define VISUAL_BGNO_EFF			(2)
///<BG�ԍ��F�w�i
#define VISUAL_BGNO_AUDIENCE	(3)

///<3D�ʂ�BG�v���C�I���e�B
#define VISUAL_3DBG_PRIORITY		(1)
///�E�B���h�E�ʂ�BG�v���C�I���e�B
#define VISUAL_BGPRI_WIN			(0)
///�G�t�F�N�g�ʂ�BG�v���C�I���e�B
#define VISUAL_BGPRI_EFF			(2)
///�w�i�ʂ�BG�v���C�I���e�B
#define VISUAL_BGPRI_AUDIENCE		(3)

//--------------------------------------------------------------
//	�t���[���ԍ��F�T�u
//--------------------------------------------------------------
///�ϋq�ʂ̃t���[��
#define VISUAL_FRAME_SUB_AUDIENCE				(GF_BGL_FRAME0_S)

///<BG�ԍ��F�ϋq
#define VISUAL_BGNO_SUB_AUDIENCE			(0)

///�ϋq�ʂ�BG�v���C�I���e�B
#define VISUAL_BGPRI_SUB_AUDIENCE			(3)


//--------------------------------------------------------------
//	BMP�E�B���h�E
//--------------------------------------------------------------
enum{
	VISUAL_BMPWIN_TALK,		///<��b�E�B���h�E
	
	VISUAL_BMPWIN_MAX,
};


//--------------------------------------------------------------
//	��b�E�B���h�E
//--------------------------------------------------------------
///��b�E�B���h�E�̃L�����N�^�]���I�t�Z�b�g(�L�����N�^�P��)
#define VISUAL_TALKWIN_CGX_OFFSET	(1)
///��b�E�B���h�E�w�i�F
#define VISUAL_TALKWIN_BACK_COLOR	(15)
///��b�E�B���h�E�̃p���b�g�ԍ�
#define VISUAL_TALKWIN_PALNO		(14)

//--------------------------------------------------------------
//	�A�N�^�[�v���C�I���e�B
//--------------------------------------------------------------
///�ԕ��͗l��BG�v���C�I���e�B
#define V_FLOWER_BGPRI				(VISUAL_BGPRI_AUDIENCE)
///�ԕ��͗l�̃\�t�g�v���C�I���e�B
#define V_FLOWER_SOFTPRI			(200)
///�ϋq�n�[�g��BG�v���C�I���e�B
#define V_AUDIENCE_HEART_BGPRI		(1)
///�ϋq�n�[�g�̃\�t�g�v���C�I���e�B
#define V_AUDIENCE_HEART_SOFTPRI	(10)


//--------------------------------------------------------------
//	���b�Z�[�W�^�O
//--------------------------------------------------------------
///���b�Z�[�W�^�O
enum{
	VTAG_NONE,		///<�^�O�Ȃ�
	
	VTAG_OYA_NICK,
	
	VTAG_MAX,
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
}VISUAL_MESSAGE_PARAM;

///���b�Z�[�W�^�O�W�J����ꍇ�A�Q�Ƃ����p�����[�^��
typedef struct{
	u8 mine_brd;		///<MINE���w�肳��Ă������ɎQ�Ƃ���u���[�_�[�̔ԍ�
	u8 num;				///<NUM���w�肳��Ă������ɕ\�����鐔�l
	u8 judge_no;		///<JUDGE���w�肳��Ă������ɎQ�Ƃ���R���̔ԍ�
	
	u8 dummy;	//4�o�C�g���E�I�t�Z�b�g
}VTAG_PARAM;

//--------------------------------------------------------------
//	
//--------------------------------------------------------------
///���C���V�[�P���X���Ŏg�p���郍�[�J�����[�N
typedef struct{
	u16 seq;
	u16 select_seq;
	s32 work;
}VISUAL_LOCAL_WORK;

//--------------------------------------------------------------
/**
 * @brief   �r�W���A������i�s�p�����[�^(���݋Z���o���Ă���|�P�����̐i�s�p�����[�^)
 */
//--------------------------------------------------------------
typedef struct{
	u8 now_breeder;					///<���ݏ�ɏo�Ă���u���[�_�[�̔ԍ�
	u8 evaluate_heart_num_bp;		///<�ϋq���\������n�[�g�̐�(�u���[�_�[�|�C���g��)
	u8 evaluate_heart_num_clip;		///<�ϋq���\������n�[�g�̐�(�N���b�v��)

	VTAG_PARAM a_talk_tagpara;		///<�m�[�}����b�F�^�O�W�J�p�p�����[�^
	u8 a_talk_id;					///<�m�[�}����bID(A_TALK_VISUAL_???)
	u8 a_talk_bmpwin_close_wait;	///<���b�Z�[�W��\���������Ă���E�B���h�E�����܂ł�wait
	u8 a_talk_bmpwin_not_close;		///<TRUE:�E�B���h�E������ɏI��

	s8 fade_start_evy;
	s8 fade_end_evy;
	s8 fade_wait;
	u16 fade_next_rgb;
	
	u16 se_id;
}VISUAL_ADVANCE_PARAM;

//--------------------------------------------------------------
/**
 * @brief   �r�W���A������Q�[���i�s�p�����[�^
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
	
	s16 bp[BREEDER_MAX];			///<�l�������u���[�_�[�|�C���g
}VISUAL_GAME_PARAM;

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
}VISUAL_ORDER_PARAM;

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
	SOFT_SPRITE *trainer_ss;
	CATS_SYS_PTR		csp;
	CATS_RES_PTR		crp;
	GF_BGL_INI *bgl;
	GF_BGL_BMPWIN win[VISUAL_BMPWIN_MAX];
	MSGDATA_MANAGER *visual_msg;	///<�r�W���A�����僁�b�Z�[�W�p���b�Z�[�W�}�l�[�W���̃|�C���^
	WORDSET *wordset;
	STRBUF *msg_buf;				///<Alloc����������o�b�t�@�ւ̃|�C���^
	PALETTE_FADE_PTR pfd;			///<�p���b�g�t�F�[�h�V�X�e���ւ̃|�C���^

	EXCHR_PARAM exchr_param[BREEDER_MAX];		///<�Z�G�t�F�N�g�p�L�����W�J�o�b�t�@

	CATS_ACT_PTR heart_cap[VISUAL_AUDIENCE_HEART_MAX];	///<�ϋq���o���n�[�g�A�N�^�[�̃|�C���^
	
	FLOWER_WORK flower;				///<�ԕ��͗l���䃏�[�N
	
	u8 talk_msg_index;				///<�����`�惋�[�`���̃C���f�b�N�X
}VISUAL_SYSTEM_PARAM;

//--------------------------------------------------------------
/**
 * @brief   �r�W���A������Ǘ����[�N
 *
 * �r�W���A������S�̂��Ǘ�����匳�̃��[�N�ɂȂ�܂��B
 * �ʐM���ł��S�Ẵ}�V���Ōʂɍ쐬����܂�
 */
//--------------------------------------------------------------
typedef struct{
	CONTEST_SYSTEM *consys;			///<�R���e�X�g�V�X�e�����[�N�ւ̃|�C���^
	TCB_PTR update_tcb;
	GF_G3DMAN *g3Dman;
	
	VISUAL_SYSTEM_PARAM sys;			///<�r�W���A������V�X�e���f�[�^�p�����[�^
	VISUAL_GAME_PARAM v_game;			///<�Q�[���i�s�p�����[�^
	VISUAL_ADVANCE_PARAM advance;		///<�i�s�p�����[�^
	VISUAL_ORDER_PARAM order[BREEDER_MAX];	///<���߃p�����[�^
	
	u16 seq;
	u16 tbl_seq_no;					///<���C���V�[�P���X�e�[�u���̔ԍ�
	u8 proc_mode;					///<���݂̓����
	u8 heart_count;					///<��ɏo�Ă���n�[�g�A�N�^�[�̐����J�E���g
	
#if 0
	//-- ����M�o�b�t�@ --//
	u32 request_bit;				///<���߂��o���Ă���r�b�g
	u8 transmit_buf[TRANSMIT_BUF_SIZE];	///<���M�p�o�b�t�@
	u8 receive_buf[RECEIVE_BUF_SIZE];	///<��M�p�o�b�t�@
	u8 transmit_flag;				///<TRUE�F���M�҂��B�@FALSE:�V���ȃf�[�^�Z�b�g�\
	u8 receive_flag;				///<TRUE�F�f�[�^��M����
#endif
	CONTEST_ORDER_WORK cow;			///<����M���[�N
	
	VISUAL_LOCAL_WORK local;			///<���[�J�����[�N
	u8 main_end;					///<TRUE:���C�������I��
	
	//�C���[�W�N���b�v
	CONTEST_IMC_WORK imcwork[BREEDER_MAX];	///<�C���[�W�N���b�v�֘A���[�N

	u8 wnd0_x1;						///<�E�B���h�E0��X1���W
	u8 wnd0_y1;
	u8 wnd0_x2;
	u8 wnd0_y2;

	u8 wnd1_x1;
	u8 wnd1_y1;
	u8 wnd1_x2;
	u8 wnd1_y2;
}VISUAL_PROC_WORK;


//==============================================================================
//	�O���֐��錾
//==============================================================================
extern PROC_RESULT VisualProc_Init( PROC * proc, int * seq );
extern PROC_RESULT VisualProc_Main( PROC * proc, int * seq );
extern PROC_RESULT VisualProc_End( PROC * proc, int * seq );

//==============================================================================
//	�O���f�[�^�錾
//==============================================================================
extern const PROC_DATA ContestVisualProcData;



#endif	//__VISUAL_H__

