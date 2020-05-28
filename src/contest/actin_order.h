//==============================================================================
/**
 * @file	actin_order.h
 * @brief	���Z�͕���F���߂��e�X�^�b�t�ɑ��M�̃w�b�_
 * @author	matsuda
 * @date	2005.11.29(��)
 */
//==============================================================================
#ifndef __ACTIN_ORDER_H__
#define __ACTIN_ORDER_H__

#include "contest_order.h"

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
	AORDER_NO_SAMPLE,			///<�T���v��
	AORDER_NO_ACTIN_EXIT,		///<���Z�͕���I��
	AORDER_NO_OPENING_EFFECT,	///<�I�[�v�j���O�G�t�F�N�g
	AORDER_NO_ENDING_EFFECT,	///<�G���f�B���O�G�t�F�N�g
	AORDER_NO_POKEMON_IN,		///<�|�P�����o��
	AORDER_NO_POKEMON_OUT,		///<�|�P�����ޏ�
	AORDER_NO_WAZAEFFECT_BEFORE,	///<�Z�G�t�F�N�g���o���O�̏���
	AORDER_NO_WAZAEFFECT,		///<�Z�G�t�F�N�g�o��
	AORDER_NO_USER_SELECT,		///<�Z�I��
	AORDER_NO_APPEAL_REVIEW,	///<�Z�̕]��(���o)
	AORDER_NO_APPEAL_FIRST,		///<�Z�̕]��(���o)
	AORDER_NO_APPEAL_KOUKA,		///<�Z�̌���(���o)
	AORDER_NO_APPEAL_SPECIAL_KOUKA,	///<�Z�̓��ʌ���(���o)
	AORDER_NO_APPEAL_VOLTAGE,		///<�Z�̃{���e�[�W(���o)
	AORDER_NO_REVIEW_AFTER,			///<�S�����Z�I����ɔ����������(���o)
	AORDER_NO_REVIEW_END,			///<�S�Ẳ��Z�I����ɔ����������(���o)
	AORDER_NO_JUDGE_SUFFER,			///<�R�����(���o)
	AORDER_NO_JUDGE_WAZA,			///<�R�����Z����
	AORDER_NO_JUDGE_COMMENT,		///<�R���R�����g
	AORDER_NO_TURN_PARAM_UPDATE,	///<�^�[���I����̃p�����[�^����M
	AORDER_NO_TALK,					///<��b���b�Z�[�W�\��
	AORDER_NO_TURNEND_EFF,			///<�^�[���I����̃G�t�F�N�g���s
};


//==============================================================================
//	�\���̒�`
//==============================================================================
///�I�[�v�j���O�G�t�F�N�g�F���[�J���\����
typedef struct{
	ACTIN_PROC_WORK *apw;
	CORDER_HEAD req_head;
	u16 wait;
	u8 audience_anm_end;
	u8 seq;
}AOLOCAL_OPENING_EFF;

///�G���f�B���O�G�t�F�N�g�F���[�J���\����
typedef struct{
	ACTIN_PROC_WORK *apw;
	CORDER_HEAD req_head;
	u8 seq;
	u16 wait;
	u8 audience_anm_end;
	
	ATAG_PARAM a_talk_tagpara;
	u8 a_talk_id;
}AOLOCAL_ENDING_EFF;

///�|�P�����o��E�ޏꃍ�[�J���\����
typedef struct{
	ACTIN_PROC_WORK *apw;
	CORDER_HEAD req_head;
	s32 x;
	s32 y;
	u8 seq;
	u8 breeder_no;
	u8 slide_end;
	s16 wait;
}AOLOCAL_POKE_INOUT;

///�Z�G�t�F�N�g���s�O�F���[�J���\����
typedef struct{
	ACTIN_PROC_WORK *apw;
	CORDER_HEAD req_head;
	u8 seq;
	u8 breeder_no;
	u8 judge_no;
	u8 reaction_end;
	u8 judge_reaction_type;
	u8 wait;
	u8 audience_anm_end;
	
	ATAG_PARAM a_talk_tagpara;
	u8 a_talk_id;
}AOLOCAL_WAZAEFF_BEFORE;

///�Z�G�t�F�N�g�F���[�J���\����
typedef struct{
	ACTIN_PROC_WORK *apw;
	CORDER_HEAD req_head;
	u8 seq;
	u8 breeder_no;
	u16 waza_no;
	u8 panel_end;

	ACTIN_ADVANCE_PARAM aap;

	ATAG_PARAM a_talk_tagpara;
	u8 a_talk_id;
	ATAG_PARAM after_a_talk_tagpara;
	u8 after_a_talk_id;
	
	CON_WAZAEFF_PARAM wazapara;
}AOLOCAL_WAZAEFF;

///���[�U�[���I�������Z�ԍ��A�R���ԍ��̃f�[�^
typedef struct{
	u16 waza_no;
	u16 judge_no;
}USER_SELECT_DATA;

///�Z�I���F���[�J���\����
typedef struct{
	ACTIN_PROC_WORK *apw;
	CORDER_HEAD req_head;
	u8 seq;
	u8 breeder_no;
	u8 final_turn_se;
	USER_SELECT_DATA usd;
}AOLOCAL_WAZASELECT;

///�o�����Z�̕]��(���o)�F���[�J���\����
typedef struct{
	ACTIN_PROC_WORK *apw;
	CORDER_HEAD req_head;
	u8 seq;
	u8 breeder_no;
	u8 breeder_pos;
//	u8 judge_no;
	s8 wait;
	s8 work;
	u8 audience_anm_end;
	u8 effect_count;
	
	ACTIN_ADVANCE_PARAM aap;
	s16 point;
	s16 voltage;
	s16 voltage_point;
	
	u8 reaction_end;
	
	u8 count;
	
	VOLTAGE_POINT_ANIME_WORK *vaw;
}AOLOCAL_APPEALREVIEW;

///�R�����F���[�J���\����
typedef struct{
	ACTIN_PROC_WORK *apw;
	CORDER_HEAD req_head;
	u8 seq;
	
	s8 wait;
	s8 work;
	
	ACTIN_ADVANCE_PARAM aap;
	s16 point;
	
	u8 count;
	u8 reaction_end;
	
	VOLTAGE_POINT_ANIME_WORK *vaw;
}AOLOCAL_JUDGESUFFER;

///�^�[���I����̃G�t�F�N�g�F���[�J���\����
typedef struct{
	ACTIN_PROC_WORK *apw;
	CORDER_HEAD req_head;
	CONTEST_ORDER_WORK *cow;
	
	PANEL_FLASH_WORK *panel_flash[BREEDER_MAX];
	
	u8 seq;
	u8 wait;
	
	u8 breeder_pos;
	u8 effect_count[BREEDER_MAX];
	u8 audience_anm_end;
}AOLOCAL_TURNEND_EFF;

///��b���b�Z�[�W�̕\��
typedef struct{
	ACTIN_PROC_WORK *apw;
	CORDER_HEAD req_head;
	CONTEST_ORDER_WORK *cow;
	
	u8 seq;
	u8 breeder_no;
	u8 close_wait;

	ATAG_PARAM a_talk_tagpara;		///<�m�[�}����b�F�^�O�W�J�p�p�����[�^
	u8 a_talk_id;					///<�m�[�}����bID(A_TALK_???)
	u8 a_talk_bmpwin_close_wait;	///<���b�Z�[�W��\���������Ă���E�B���h�E�����܂ł�wait
	u8 a_talk_bmpwin_not_close;		///<TRUE:�E�B���h�E������ɏI��
}AOLOCAL_TALK_PUT;


//==============================================================================
//	�O���֐��錾
//==============================================================================
extern void ActinOrder_WorkInit(ACTIN_PROC_WORK *apw);


#endif	//__ACTIN_ORDER_H__

