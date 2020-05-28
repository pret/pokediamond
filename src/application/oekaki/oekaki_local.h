//=============================================================================
/**
 * @file	oekaki_local.h
 * @brief	���G�����{�[�h�p�\���̒�`�i�����Q�Ɨp)
 *          
 * @author	Akito Mori
 * @date    	2006.02.14
 */
//=============================================================================



#ifndef __OEKAKI_LOCAL_H__
#define __OEKAKI_LOCAL_H__

#include "system/touch_subwindow.h"

// �@�\�{�^���p��`
#define FUNCBUTTON_NUM	( 7 ) 		// �@�\�{�^���̐�
#define START_WORDPANEL ( 0 )		// �ŏ��̕������̓p�l���̔ԍ��i�O���Ђ炪�ȁj

// �ڑ��l��MAX�͂T�l
#define OEKAKI_MEMBER_MAX	( 5 )


// CLACT�Œ�`���Ă���Z�����傫�����ăT�u��ʂɉe�����łĂ��܂��̂ŗ����Ă݂�
#define NAMEIN_SUB_ACTOR_DISTANCE 	(256*FX32_ONE)

// CellActor�ɏ��������郊�\�[�X�}�l�[�W���̎�ނ̐��i���}���`�Z���E�}���`�Z���A�j���͎g�p���Ȃ��j
#define CLACT_RESOURCE_NUM		(  4 )
#define NAMEIN_OAM_NUM			( 14 )


// ���b�Z�[�W�\�����WAIT
#define OEKAKI_MESSAGE_END_WAIT	( 60 )


// ���G�����{�[�h�̕��E����
#define OEKAKI_BOARD_W	 	( 30 )
#define OEKAKI_BOARD_H	 	( 15 )
#define OEKAKI_GRAPHI_SIZE  ( OEKAKI_BOARD_W*OEKAKI_BOARD_H*32 )

// �{�^���Z���A�N�^�[�̃y�����`���n�܂�ԍ�
#define CELL_BRUSH_NO		( 9 )


// �u���V�̑傫��
#define SMALL_BRUSH			( 0 )
#define MIDDLE_BRUSH		( 1 )
#define BIG_BRUSH			( 2 )


// ���G�����֎~�t���O
#define OEKAKI_BAN_NONE		( 0 )
#define OEKAKI_BAN_OFF		( 1 )
#define OEKAKI_BAN_ON		( 2 )

// ���C���V�[�P���X�̑J��
enum {
	SEQ_IN = 0,
	SEQ_MAIN,
	SEQ_LEAVE,
	SEQ_OUT,
};

// �T�u�V�[�P���X�̑J�ڗp
enum{
	OEKAKI_MODE_INIT  = 0, 

	OEKAKI_MODE_NEWMEMBER,
	OEKAKI_MODE_NEWMEMBER_WAIT,
	OEKAKI_MODE_NEWMEMBER_END,

	OEKAKI_MODE,

	OEKAKI_MODE_END_SELECT,
	OEKAKI_MODE_END_SELECT_WAIT,
	OEKAKI_MODE_END_SELECT_ANSWER_WAIT,
	OEKAKI_MODE_END_SELECT_ANSWER_OK,
	OEKAKI_MODE_END_SELECT_ANSWER_NG,

    OEKAKI_MODE_END_CHILD,
    OEKAKI_MODE_END_CHILD_WAIT,
    OEKAKI_MODE_END_CHILD_WAIT2,

	OEKAKI_MODE_END_SELECT_PARENT,
    OEKAKI_MODE_END_SELECT_PARENT_WAIT,

	OEKAKI_MODE_FORCE_END,
    OEKAKI_MODE_FORCE_END_WAIT,
    OEKAKI_MODE_FORCE_END_SYNCHRONIZE,
	OEKAKI_MODE_FORCE_END_WAIT_NOP,

	OEKAKI_MODE_END_PARENT_ONLY,
	OEKAKI_MODE_END_PARENT_ONLY_WAIT,

	OEKAKI_MODE_LOGOUT_CHILD,
    OEKAKI_MODE_LOGOUT_CHILD_WAIT,
    OEKAKI_MODE_LOGOUT_CHILD_CLOSE,
    
};


enum{
	OEKAKI_SYNCHRONIZE_END=200,
};

// �㉺��ʎw���`
#define BOTH_LCD	( 2 )
#define MAIN_LCD	( GF_BGL_MAIN_DISP )	// �v�͂O��
#define SUB_LCD		( GF_BGL_SUB_DISP )		// �P�Ȃ�ł����B

// BMPWIN�w��
enum{
	BMP_NAME1_S_BG0,
	BMP_NAME2_S_BG0,
	BMP_NAME3_S_BG0,
	BMP_NAME4_S_BG0,
	BMP_NAME5_S_BG0,
	BMP_OEKAKI_MAX,
};





// �^�b�`�p�l�����\����
// ���̃f�[�^���ʐM�ő��M����܂�
typedef struct{
	u8 x[4];	// �ő�S�񕪂̃^�b�`���W
	u8 y[4];	// 
	u8 color:3;	// �I�𒆂̃J���[
	u8 size:3;	// �T���v�����O������
	u8 brush:2; // �I�𒆂̃y����
	u8 banFlag;  // ����֎~�t���O(�e�@����̂ݑ��M�j
}TOUCH_INFO;

typedef struct{
	u8   x,y;
	u16  size;
}OLD_TOUCH_INFO;

typedef struct{
	u8  chara[1000];
	u32 _xor;
	u8  no;
	u8  dummy[3];
}OEKAKIG_SPLIT_DATA;

//============================================================================================
//	�\���̒�`
//============================================================================================

struct OEKAKI_WORK{
	GF_BGL_INI		*bgl;
	BOOL			wipe_end;
	OEKAKI_PARAM	*param;

	WORDSET			*WordSet;								// ���b�Z�[�W�W�J�p���[�N�}�l�[�W���[
	MSGDATA_MANAGER *MsgManager;							// ���O���̓��b�Z�[�W�f�[�^�}�l�[�W���[
	STRBUF			*TrainerName[OEKAKI_MEMBER_MAX];		// ���O
	STRBUF			*EndString;								// ������u��߂�v
	STRBUF			*TalkString;							// ��b���b�Z�[�W�p
	int				MsgIndex;								// �I�����o�p���[�N

	CLACT_SET_PTR 			clactSet;								// �Z���A�N�^�[�Z�b�g
	CLACT_U_EASYRENDER_DATA	renddata;								// �ȈՃ����_�[�f�[�^
	CLACT_U_RES_MANAGER_PTR	resMan[CLACT_RESOURCE_NUM];				// ���\�[�X�}�l�[�W��
	CLACT_U_RES_OBJ_PTR 	resObjTbl[BOTH_LCD][CLACT_RESOURCE_NUM];// ���\�[�X�I�u�W�F�e�[�u��
	CLACT_HEADER			clActHeader_m;							// �Z���A�N�^�[�w�b�_�[
	CLACT_HEADER			clActHeader_s;							// �Z���A�N�^�[�w�b�_�[
	CLACT_WORK_PTR			MainActWork[NAMEIN_OAM_NUM];				// �Z���A�N�^�[���[�N�|�C���^�z��
	CLACT_WORK_PTR			SubActWork[NAMEIN_OAM_NUM];				// �Z���A�N�^�[���[�N�|�C���^�z��
	CLACT_WORK_PTR			ButtonActWork[12];						// �{�^���A�N�^�[�|�C���^

	GF_BGL_BMPWIN 			TrainerNameWin[BMP_OEKAKI_MAX];			// ���G������ʗpBMP�E�C���h�E
	GF_BGL_BMPWIN			OekakiBoard;
	GF_BGL_BMPWIN			MsgWin;									// ��b�E�C���h�E
	GF_BGL_BMPWIN			EndWin;									// ��߂�
	GF_BGL_BMPWIN			*YesNoWin[2];								// �͂��E�������E�C���h�E�̃|�C���^

	int						proc_seq;								// MainProc�̃V�[�P���X���Ď����邽�߂����ɂ���
																	// �i�T�u�V�[�P���X�͏��������Ȃ��j
	int						seq;									// ���݂̃T�u�V�[�P���X���
	int						next_seq;								// ���̃V�[�P���X�͉����H
	int						mode;									// ���ݍőO�ʂ̕����p�l��
	int						wait;
	int						connectBackup;							// ���O�̐ڑ��l��
	int						shareNum;								// �摜���M�ς݂̐l��
	int						shareBit;								// �摜���M�ς݂̐l��(�r�b�g)
	int						newMemberId;							// �������Ă����l��ID
	
	u8						ConnectCheck[8][2];
	MYSTATUS				*TrainerStatus[8][2];

	u8						SendBoardGraphic[0x4000];
	u16						CursorPal;
	u8						brush_color;
	u8						brush;

	TOUCH_INFO				MyTouchResult;							// �����̃T���v�����O���ʁi����͑��M���邾��
	TOUCH_INFO				AllTouchResult[OEKAKI_MEMBER_MAX];		// �ʐM�Ŏ擾�����T���v�����O���ʁi���̃f�[�^�ŕ`�悷��
	OLD_TOUCH_INFO			OldTouch[OEKAKI_MEMBER_MAX];			// �O�񂩂�̃|�C���g����

	u8						*lz_buf;								// ���k�摜�i�[�̈�
	int						send_num;
	u8						canvas_buf[OEKAKI_GRAPHI_SIZE];
	OEKAKIG_SPLIT_DATA		send_buf;
	OEKAKIG_SPLIT_DATA		split_temp[OEKAKI_MEMBER_MAX];

	s32 					err_num;								// �ʐM�I�����݂邽�߂̃��[�N
	u32						ridatu_bit;								// ���E���悤�Ƃ��Ă���q��Bit
	u16						oya_share_num;			// �e�������Ă���shareNum�����炤
	s16						ridatu_wait;			// ���E�p�̃E�F�C�g
	u8						status_end;								// TRUE:�I���V�[�P���X�ֈڍs

	// ----�e�������K�v�ȃ��[�N

	TOUCH_INFO				ParentTouchResult[5];
	TOUCH_SW_SYS			*TouchSubWindowSys;
	int						banFlag;
	int						yesno_flag;								// ���݁u�͂��E�������v��ʂ��Ăяo����
	int						firstChild;								// ��ԍŏ��ɂ���Ă����Ƃ��Ɏq�@���痐���錾����Ă�����
	int						ireagalJoin;							//���G�����I�����ɗ������ꂽ��
	int						bookJoin;								//�����\��t���O
	int						joinBit;								//�����҃r�b�g
#ifdef PM_DEBUG
	int 					frame;									//
	int						framenum[9][2];							//
#endif
};

//--------------------------------------------------------------
/**
 * @brief   ���̍\���̂̒��g��ւ�����A�K���ʐM�֐��e�[�u����
 *          CommRecordCornerEndChild���g�p���Ă���ӏ��̑���M�T�C�Y��ύX���邱�ƁI�I
 *			�t�@�C���Fcomm_command_record.c, comm_command_oekaki.c, comm_command_field.c
 */
//--------------------------------------------------------------
typedef struct{
	u8 ridatu_id;			///<���E�҂�ID
	u8 oya_share_num;		///<�e�̎���shareNum
	u8 request;				///<���߃R�[�h
	u8 ridatu_kyoka;		///<TRUE:���EOK�AFALSE:���ENG
}COMM_OEKAKI_END_CHILD_WORK;

enum{
	COEC_REQ_RIDATU_CHECK,		///<���E�m�F
	COEC_REQ_RIDATU_EXE,		///<���E���s
};


extern void OekakiBoardCommSendPokeData(int netID, POKEPARTY *party, int no);
extern void OekakiBoardCommSend(int netID, int command, int pos);
extern void OekakiBoard_MainSeqCheckChange( OEKAKI_WORK *wk, int seq, u8 id );
extern void OekakiBoard_MainSeqForceChange( OEKAKI_WORK *wk, int seq, u8 id  );
extern int OekakiBoard_MyStatusGetNum(void);


#endif
