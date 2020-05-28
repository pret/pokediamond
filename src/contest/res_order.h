//==============================================================================
/**
 * @file	res_order.h
 * @brief	�R���e�X�g���ʔ��\��ʁF���ߑ���M�̃w�b�_
 * @author	matsuda
 * @date	2006.03.17(��)
 */
//==============================================================================
#ifndef __RES_ORDER_H__
#define __RES_ORDER_H__


//==============================================================================
//	�萔��`
//==============================================================================
//--------------------------------------------------------------
/**
 *     ���߃R�[�h
 * 					��OrderFuncTbl�ƕK�����т𓯂��ɂ��Ă������ƁI
 */
//--------------------------------------------------------------
enum{
	RORDER_NO_SAMPLE,			///<�T���v��
	RORDER_NO_GAMEPARAM_UPDATE,	///<�Q�[���p�����[�^�X�V
	RORDER_NO_DONCHOU_UP,		///<�ǂ񂿂傤���グ��
	RORDER_NO_DONCHOU_DOWN,		///<�ǂ񂿂傤��������
	RORDER_NO_CONRES_EXIT,		///<�_���X����I��
	RORDER_NO_TALK,				///<��b���b�Z�[�W�\��
	RORDER_NO_RESULT_CHANGE,	///<��I��ʂ��猋�ʔ��\��ʂɐ؂�ւ���
	RORDER_NO_RANKING_ANNOUNCE,	///<���ʔ��\
	RORDER_NO_VICTORY_APPEAR,	///<�D�������|�P�����̓o�ꉉ�o
	RORDER_NO_METER_UPDATE,		///<���[�^�[��L�΂�
	RORDER_NO_RESULT_FADEOUT,	///<���ʔ��\��ʂ��t�F�[�h�A�E�g����
};


//==============================================================================
//	�\���̒�`
//==============================================================================
///�ǂ񂿂傤���グ�郍�[�J���\����
typedef struct{
	CONRES_PROC_WORK *rpw;
	CORDER_HEAD req_head;
	CONTEST_ORDER_WORK *cow;
	
	u8 seq;

	s8 anm_line;			///<�A�j�����������̊�{���C��
	u8 anm_no;				///<�A�j��No
	s8 anm_wait;			///<�A�j���E�F�C�g
	s8 anm_dansa_wait;		///<�A�j���i���E�F�C�g
}ROLOCAL_DONCHOU_UP;

///�ǂ񂿂傤�������郍�[�J���\����
typedef struct{
	CONRES_PROC_WORK *rpw;
	CORDER_HEAD req_head;
	CONTEST_ORDER_WORK *cow;
	
	u8 seq;

	s8 anm_line;			///<�A�j�����������̊�{���C��
	u8 anm_no;				///<�A�j��No
	s8 anm_wait;			///<�A�j���E�F�C�g
	s8 anm_dansa_wait;		///<�A�j���i���E�F�C�g
}ROLOCAL_DONCHOU_DOWN;

///��b���b�Z�[�W�̕\��
typedef struct{
	CONRES_PROC_WORK *rpw;
	CORDER_HEAD req_head;
	CONTEST_ORDER_WORK *cow;
	
	u8 seq;
	u8 breeder_no;
	u8 close_wait;
	
	CRTAG_PARAM a_talk_tagpara;		///<�m�[�}����b�F�^�O�W�J�p�p�����[�^
	u8 a_talk_id;					///<�m�[�}����bID(A_TALK_CONRES_???)
	u8 a_talk_bmpwin_close_wait;	///<���b�Z�[�W��\���������Ă���E�B���h�E�����܂ł�wait
	u8 a_talk_bmpwin_not_close;		///<TRUE:�E�B���h�E������ɏI��
	u8 a_talk_bmpwin_not_open;		///<TRUE:�E�B���h�E�`����s��Ȃ�
}ROLOCAL_TALK_PUT;

///���ʔ��\��ʂɐ؂�ւ�
typedef struct{
	CONRES_PROC_WORK *rpw;
	CORDER_HEAD req_head;
	CONTEST_ORDER_WORK *cow;
	
	u8 seq;
}ROLOCAL_RESULT_CHANGE;

///���ʔ��\
typedef struct{
	CONRES_PROC_WORK *rpw;
	CORDER_HEAD req_head;
	CONTEST_ORDER_WORK *cow;

	u8 seq;
	u8 ranking[BREEDER_MAX];		///<����(1�ʂ��珇�Ƀu���[�_�[�ԍ�������܂�)
	u8 end_count;					///<���\���ς񂾃u���[�_�[�̐����J�E���g
	s16 wait;
}ROLOCAL_RANKING_ANNOUNCE;

///�D�������|�P�����̓o�ꉉ�o
typedef struct{
	CONRES_PROC_WORK *rpw;
	CORDER_HEAD req_head;
	CONTEST_ORDER_WORK *cow;
	
	u8 seq;
	u8 victory_breeder;			///<�D�������u���[�_�[�̔ԍ�
	u8 wnd_end_flag;			///<�E�B���h�E�J�����G�t�F�N�g�I���󂯎��p���[�N
	u8 poke_end_flag;			///<�|�P�����o��G�t�F�N�g�I���󂯎��p���[�N
	s16 wait;
}ROLOCAL_VICTORY_EFF;

///���[�^�[��L�΂�
typedef struct{
	CONRES_PROC_WORK *rpw;
	CORDER_HEAD req_head;
	CONTEST_ORDER_WORK *cow;
	
	u8 seq;
	u8 meter_type;				///<�L�΂����[�^�[�̎��(CONGAME_???)
	s16 wait;
	s16 max_meter_dot[BREEDER_MAX];	///<�L�΂��ő�h�b�g��
	s16 now_dot[BREEDER_MAX];		///<���݂̃h�b�g��
}ROLOCAL_METER;

///���ʔ��\��ʃt�F�[�h�A�E�g
typedef struct{
	CONRES_PROC_WORK *rpw;
	CORDER_HEAD req_head;
	CONTEST_ORDER_WORK *cow;
	
	u8 seq;
	s16 wait;
}ROLOCAL_FADEOUT;


//==============================================================================
//	�O���֐��錾
//==============================================================================
extern void ConresOrder_WorkInit(CONRES_PROC_WORK *rpw);


#endif	//__RES_ORDER_H__

