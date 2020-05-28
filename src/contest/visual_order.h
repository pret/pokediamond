//==============================================================================
/**
 * @file	visual_order.h
 * @brief	�r�W���A������F���ߑ���M�̃w�b�_
 * @author	matsuda
 * @date	2005.12.13(��)
 */
//==============================================================================
#ifndef __VISUAL_ORDER_H__
#define __VISUAL_ORDER_H__

#include "wazaeffect/ball_effect.h"


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
	VORDER_NO_SAMPLE,			///<�T���v��
	VORDER_NO_VISUAL_EXIT,		///<�r�W���A������I��
	VORDER_NO_APPEAR,			///<�|�P�����o��
	VORDER_NO_ADVANCE,			///<�O�i
	VORDER_NO_AUDIENCE_EVALUATE_BP,	///<�ϋq�]��(BP)
	VORDER_NO_AUDIENCE_EVALUATE_CLIP,	///<�ϋq�]��(Clip)
	VORDER_NO_AUDIENCE_EVALUATE_ALL,	///<�ϋq�]��(BP & Clip)
	VORDER_NO_POKE_OUT,			///<�|�P�����ޏ�
	VORDER_NO_DONCHOU_UP,		///<�ǂ񂿂傤�グ��
	VORDER_NO_DONCHOU_DOWN,		///<�ǂ񂿂傤������
	VORDER_NO_TRAINER_IN,		///<�g���[�i�[�o��
	VORDER_NO_TRAINER_OUT,		///<�g���[�i�[�ޏ�
	VORDER_NO_APPEAR_EFFECT,	///<�o��G�t�F�N�g
	VORDER_NO_TALK,				///<��b���b�Z�[�W�\��
	VORDER_NO_FADE_INOUT,	///<�S�̃t�F�[�h�C���E�A�E�g
	VORDER_NO_DONCHOU_EFFECT_UP,	///<�ǂ񂿂傤�G�t�F�N�g�㏸
	VORDER_NO_VISUAL_FINISH,	///<�r�W���A������I���G�t�F�N�g
};


//==============================================================================
//	�\���̒�`
//==============================================================================
///�|�P�����O�i���[�J���\����
typedef struct{
	VISUAL_PROC_WORK *vpw;
	CORDER_HEAD req_head;
	CONTEST_ORDER_WORK *cow;
	
	u8 seq;
	u8 breeder_no;

	s32 x;
	s32 y;
}VOLOCAL_ADVANCE;

///�|�P�����o�ꃍ�[�J���\����
typedef struct{
	VISUAL_PROC_WORK *vpw;
	CORDER_HEAD req_head;
	CONTEST_ORDER_WORK *cow;
	
	u8 seq;
	u8 breeder_no;
	s16 wait;
}VOLOCAL_POKE_APPEAR;

///�|�P�����O�i���[�J���\����
typedef struct{
	VISUAL_PROC_WORK *vpw;
	CORDER_HEAD req_head;
	CONTEST_ORDER_WORK *cow;
	
	u8 seq;
	u8 breeder_no;

	s32 x;
	s32 y;
}VOLOCAL_POKEOUT;

///�ǂ񂿂傤���グ�郍�[�J���\����
typedef struct{
	VISUAL_PROC_WORK *vpw;
	CORDER_HEAD req_head;
	CONTEST_ORDER_WORK *cow;
	
	u8 seq;
	
	s8 anm_line;			///<�A�j�����������̊�{���C��
	u8 anm_no;				///<�A�j��No
	s8 anm_wait;			///<�A�j���E�F�C�g
	s8 anm_dansa_wait;		///<�A�j���i���E�F�C�g
}VOLOCAL_DONCHOU_UP;

///�ǂ񂿂傤���グ�郍�[�J���\����
typedef struct{
	VISUAL_PROC_WORK *vpw;
	CORDER_HEAD req_head;
	CONTEST_ORDER_WORK *cow;
	
	u8 seq;

	s8 anm_line;			///<�A�j�����������̊�{���C��
	u8 anm_no;				///<�A�j��No
	s8 anm_wait;			///<�A�j���E�F�C�g
	s8 anm_dansa_wait;		///<�A�j���i���E�F�C�g
}VOLOCAL_DONCHOU_DOWN;

///�ϋq�]�����[�J���\����
typedef struct{
	VISUAL_PROC_WORK *vpw;
	CORDER_HEAD req_head;
	CONTEST_ORDER_WORK *cow;
	
	u8 seq;
	u8 wait;
	u8 max_count;					///<�ϋq���\������n�[�g�̐��A�ő吔
	u8 put_count;					///<���܂łɕ\�������n�[�g�̐����J�E���g
	u8 bp_count;					///<BP�̃n�[�g�\���ő吔
	u8 clip_count;					///<CLIP�̃n�[�g�\���ő吔
	s16 old_x;						///<1�O�ɕ\�������n�[�g�̍��WX
	s16 old_y;						///<1�O�ɕ\�������n�[�g�̍��WY
	u8 heart_anm;					///<�n�[�g�̃A�j���^�C�v
	u8 all_type;					///<TRUE:BP�ƃN���b�v�����o��
}VOLOCAL_EVALUATE;

///�g���[�i�[�o��E�ޏꃍ�[�J���\����
typedef struct{
	VISUAL_PROC_WORK *vpw;
	CORDER_HEAD req_head;
	CONTEST_ORDER_WORK *cow;
	
	u8 seq;
	u8 breeder_no;

	s32 x;
	s32 y;
}VOLOCAL_TRAINER_INOUT;

///�{�[���G�t�F�N�g(����)
typedef struct{
	TBALL_CUSTOM_PARAM bcp;
	BES_PTR bes;
	POKEMON_PARAM *pp;
	u8 seq;
	u8 end;				///<1:�G�t�F�N�g�I��
}VOLOCAL_SUB_BALL_EFF;

///�{�[���ړ��G�t�F�N�g
typedef struct{
	VISUAL_PROC_WORK *vpw;
	BMS_PTR bms;
	u8 seq;
	u8 end;				///<1:�G�t�F�N�g�I��
	u8 wait;
}VOLOCAL_SUB_BALL_MOVE;

///�|�P�����k������o��G�t�F�N�g
typedef struct{
	VISUAL_PROC_WORK *vpw;
	fx32 aff_x;
	fx32 aff_y;
	u8 seq;
	u8 end;				///<1:�G�t�F�N�g�I��
	u8 breeder_no;
}VOLOCAL_SUB_POKE_EFF;

///�g���[�i�[�ޏ�G�t�F�N�g
typedef struct{
	VISUAL_PROC_WORK *vpw;

	s32 x;
	s32 y;

	u8 seq;
	u8 end;				///<1:�G�t�F�N�g�I��
	u8 loop;
	u8 wait;
}VOLOCAL_SUB_TRAINER_EFF;

///�o��G�t�F�N�g
typedef struct{
	VISUAL_PROC_WORK *vpw;
	CORDER_HEAD req_head;
	CONTEST_ORDER_WORK *cow;
	
	u8 seq;
	u8 breeder_no;

	VOLOCAL_SUB_BALL_EFF ball_eff;
	VOLOCAL_SUB_BALL_MOVE ball_move;
	VOLOCAL_SUB_POKE_EFF poke_eff;
	VOLOCAL_SUB_TRAINER_EFF tr_eff;
}VOLOCAL_APPEAR_EFF;

///��b���b�Z�[�W�̕\��
typedef struct{
	VISUAL_PROC_WORK *vpw;
	CORDER_HEAD req_head;
	CONTEST_ORDER_WORK *cow;
	
	u8 seq;
	u8 breeder_no;
	u8 close_wait;

	VTAG_PARAM a_talk_tagpara;		///<�m�[�}����b�F�^�O�W�J�p�p�����[�^
	u8 a_talk_id;					///<�m�[�}����bID(A_TALK_VISUAL_???)
	u8 a_talk_bmpwin_close_wait;	///<���b�Z�[�W��\���������Ă���E�B���h�E�����܂ł�wait
	u8 a_talk_bmpwin_not_close;		///<TRUE:�E�B���h�E������ɏI��
}VOLOCAL_TALK_PUT;

///�ǂ񂿂傤�t�F�[�h�A�E�g���[�J���\����
typedef struct{
	VISUAL_PROC_WORK *vpw;
	CORDER_HEAD req_head;
	CONTEST_ORDER_WORK *cow;
	
	u8 seq;

	s8 fade_start_evy;
	s8 fade_end_evy;
	s8 fade_wait;
	u16 fade_next_rgb;
}VOLOCAL_DFO;	//DonchouFadeOut

///�ǂ񂿂傤�G�t�F�N�g�㏸���[�J���\����
typedef struct{
	VISUAL_PROC_WORK *vpw;
	CORDER_HEAD req_head;
	CONTEST_ORDER_WORK *cow;
	
	u8 seq;
	
	s8 anm_line;			///<�A�j�����������̊�{���C��
	u8 anm_no;				///<�A�j��No
	s8 anm_wait;			///<�A�j���E�F�C�g
	s8 anm_dansa_wait;		///<�A�j���i���E�F�C�g
	
	u8 lvup_se_req;			///<TRUE:LVUP SE�Đ����N�G�X�g
	
	s32 lvup_wait;
}VOLOCAL_DONCHOU_EFFECT_UP;

///�r�W���A������I�����[�J���\����
typedef struct{
	VISUAL_PROC_WORK *vpw;
	CORDER_HEAD req_head;
	CONTEST_ORDER_WORK *cow;
	
	u8 seq;
}VOLOCAL_FINISH;


//==============================================================================
//	�O���֐��錾
//==============================================================================
extern void VisualOrder_WorkInit(VISUAL_PROC_WORK *vpw);


#endif	//__VISUAL_ORDER_H__

