//==============================================================================
/**
 * @file	dance_order.h
 * @brief	�r�W���A������F���ߑ���M�̃w�b�_
 * @author	matsuda
 * @date	2005.12.13(��)
 */
//==============================================================================
#ifndef __DANCE_ORDER_H__
#define __DANCE_ORDER_H__


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
	DORDER_NO_SAMPLE,			///<�T���v��
	DORDER_NO_DONCHOU_UP,		///<�ǂ񂿂傤���グ��
	DORDER_NO_DONCHOU_DOWN,		///<�ǂ񂿂傤��������
	DORDER_NO_OPENING_EFF,		///<�I�[�v�j���O�G�t�F�N�g
	DORDER_NO_DANCE_EXIT,		///<�_���X����I��
	DORDER_NO_DANCING,			///<�_���X���s
	DORDER_NO_ROTATION,			///<���[�e�[�V����
	DORDER_NO_BEFORE,			///<�_���X�J�n�O
	DORDER_NO_AFTER,			///<�_���X�I����
	DORDER_NO_TALK,				///<��b���b�Z�[�W�\��
	DORDER_NO_GAMEPARAM,		///<�Q�[���p�����[�^�X�V
	DORDER_NO_MUSIC_START,		///<���y�J�n
	DORDER_NO_END_EFFECT,		///<�S���̃_���X�I����̃G�t�F�N�g����
};


//==============================================================================
//	�\���̒�`
//==============================================================================
///�|�P�������[�e�[�V�����A�e�u���[�_�[����\����
typedef struct{
	//TCB�������ɃZ�b�g����Ă���p�����[�^
	POKEMON_PARAM *pp;			///<�����̃|�P�����̃p�����[�^
	SOFT_SPRITE *ss;			///<�����̃|�P�����\�t�g�E�F�A�X�v���C�g�ւ̃|�C���^
	CONTEST_IMC_WORK *imcwork;	///<�����̃|�P�����C���[�W�N���b�v�ւ̃|�C���^
	u8 now_rotation_pos;		///<���݂̃��[�e�[�V�����ʒu
	u8 next_rotation_pos;		///<���̃��[�e�[�V�����ʒu
	u16 move_frame;				///<���[�e�[�V�����̈ړ��ɂ�����t���[����

	//�e�u���[�_�[����TCB���ŕύX�A�Z�b�g����p�����[�^
	s32 x;
	s32 y;
	s32 z;
	s32 add_x;
	s32 add_y;
	s32 add_z;
	u16 frame;					///<���݂̌o�߃t���[����
	u8 seq;
	u8 end;						///<TRUE:���̃��[�e�[�V�����ʒu�ɓ��B
}DOLOCAL_ROTATION_BREEDER;

///�|�P�������[�e�[�V�������[�J���\����
typedef struct{
	DANCE_PROC_WORK *dpw;
	CORDER_HEAD req_head;
	CONTEST_ORDER_WORK *cow;
	
	u8 seq;
	u8 light_fade_end[BREEDER_MAX];
	
	DOLOCAL_ROTATION_BREEDER sub_rb[BREEDER_MAX];
	DANCE_ADVANCE_PARAM dap;
}DOLOCAL_ROTATION;

///�_���X�`�F�b�N���[�N�\����
typedef struct{
	DANCE_PROC_WORK *dpw;
	u8 seq;
	u8 touch_wait;			///<�^�b�`��Ɏ��̃^�b�`�`�F�b�N���o����܂ł̃E�F�C�g�J�E���g
}DANCE_TOUCH_WORK;

///�_���X�p�����[�^���M�^�X�N���[�N
typedef struct{
	TCB_PTR tcb;			///<���M���s�^�X�N�̃|�C���^
	DANCE_PROC_WORK *dpw;
	DANCING_PARAM dancing_param;
	u8 ai;
	u8 req;			///<TRUE�F���M���N�G�X�g���������Ă���
}DANCING_SEND_WORK;

///���C���_���X���[�J���\����
typedef struct{
	DANCE_PROC_WORK *dpw;
	CORDER_HEAD req_head;
	CONTEST_ORDER_WORK *cow;
	
	u8 seq;
	u8 flash_flag;
	u8 back_dancer_light_flag;
	u16 frame;
	u8 loop;
	u8 touch_count;
	
	DANCE_ADVANCE_PARAM dap;
	DANCE_TOUCH_WORK dtw;
	
	DANCE_AI_WORK aiwork[BREEDER_MAX];		///<�_���X�pAI���[�N�ւ̃|�C���^
	DANCING_SEND_WORK *sendwork[BREEDER_MAX];	///<�_���X�p�����[�^���M�^�X�N���[�N�ւ̃|�C���^
}DOLOCAL_MAINDANCE;

///�ǂ񂿂傤���グ�郍�[�J���\����
typedef struct{
	DANCE_PROC_WORK *dpw;
	CORDER_HEAD req_head;
	CONTEST_ORDER_WORK *cow;
	
	u8 seq;

	s8 anm_line;			///<�A�j�����������̊�{���C��
	u8 anm_no;				///<�A�j��No
	s8 anm_wait;			///<�A�j���E�F�C�g
	s8 anm_dansa_wait;		///<�A�j���i���E�F�C�g
}DOLOCAL_DONCHOU_UP;

///�ǂ񂿂傤�������郍�[�J���\����
typedef struct{
	DANCE_PROC_WORK *dpw;
	CORDER_HEAD req_head;
	CONTEST_ORDER_WORK *cow;
	
	u8 seq;

	s8 anm_line;			///<�A�j�����������̊�{���C��
	u8 anm_no;				///<�A�j��No
	s8 anm_wait;			///<�A�j���E�F�C�g
	s8 anm_dansa_wait;		///<�A�j���i���E�F�C�g
}DOLOCAL_DONCHOU_DOWN;

///�ǂ񂿂傤�������郍�[�J���\����
typedef struct{
	DANCE_PROC_WORK *dpw;
	CORDER_HEAD req_head;
	CONTEST_ORDER_WORK *cow;
	
	u8 seq;
	
	u8 end_flag;
	s16 wait;
}DOLOCAL_OPENING_EFF;

///�_���X�J�n�O�����̃��[�J���\����
typedef struct{
	DANCE_PROC_WORK *dpw;
	CORDER_HEAD req_head;
	CONTEST_ORDER_WORK *cow;
	
	DANCE_ADVANCE_PARAM dap;
	u8 seq;
}DOLOCAL_BEFORE;

///�_���X�I���㏈���̃��[�J���\����
typedef struct{
	DANCE_PROC_WORK *dpw;
	CORDER_HEAD req_head;
	CONTEST_ORDER_WORK *cow;
	
	DANCE_ADVANCE_PARAM dap;
	u8 seq;
}DOLOCAL_AFTER;

///��b���b�Z�[�W�̕\��
typedef struct{
	DANCE_PROC_WORK *dpw;
	CORDER_HEAD req_head;
	CONTEST_ORDER_WORK *cow;
	
	u8 seq;
	u8 breeder_no;
	u8 close_wait;
	
	DTAG_PARAM a_talk_tagpara;		///<�m�[�}����b�F�^�O�W�J�p�p�����[�^
	u8 a_talk_id;					///<�m�[�}����bID(A_TALK_DANCE_???)
	u8 a_talk_bmpwin_close_wait;	///<���b�Z�[�W��\���������Ă���E�B���h�E�����܂ł�wait
	u8 a_talk_bmpwin_not_close;		///<TRUE:�E�B���h�E������ɏI��
}DOLOCAL_TALK_PUT;

///�S���̃_���X�I����̃G�t�F�N�g�Ȃǂ̃��[�J���\����
typedef struct{
	DANCE_PROC_WORK *dpw;
	CORDER_HEAD req_head;
	CONTEST_ORDER_WORK *cow;

	DANCE_ADVANCE_PARAM dap;
	
	u32 wait;
	u8 seq;
}DOLOCAL_END_EFFECT;


//==============================================================================
//	�O���֐��錾
//==============================================================================
extern void DanceOrder_WorkInit(DANCE_PROC_WORK *dpw);
extern int DanceTP_to_DanceStep(int dance_tp);
extern int DanceStep_to_TP(int dance_step);
extern void DancerReactionSet(int breeder_no, int reaction, u32 frame, u32 one_tempo_frame, 
	const DANCE_LAG_DATA *dld, DANCING_PARAM *param, const DANCING_PARAM *maindancer_record,
	int rotation_pos, int touch_count, int max_touch);
extern void DancingParamSendReqSet(DANCING_SEND_WORK *sendwork, const DANCING_PARAM *param);

//-- dance_ai.c --//
extern void DanceAI_Init(DANCE_AI_WORK *aiwork, int breeder_no, int rotation_pos, u32 random_seed, 
	int character);
extern void DanceAI_ParamClear(DANCE_AI_WORK *aiwork);
extern void DancdAI_MainDancerCalc(DANCE_PROC_WORK *dpw, DANCE_AI_WORK *aiwork, 
	u32 all_tempo_frame, u32 one_tempo_frame);
extern void DanceAI_Main(int now_frame_dancer, DANCE_PROC_WORK *dpw, DANCE_AI_WORK *aiwork, 
	u32 frame, u32 all_tempo_frame, u32 one_tempo_frame, const DANCE_MUSIC_DATA *musicdata,
	DANCING_SEND_WORK *sendwork);


#endif	//__DANCE_ORDER_H__

