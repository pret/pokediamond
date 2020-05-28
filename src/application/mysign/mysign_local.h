//=============================================================================
/**
 * @file	mysign_local.h
 * @brief	�T�C����ʍ\���̒�`�i�����Q�Ɨp)
 *          
 * @author	Akito Mori
 * @date    2006.04.11
 */
//=============================================================================



#ifndef __MYSIGN_LOCAL_H__
#define __MYSIGN_LOCAL_H__

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
#define OEKAKI_BOARD_W	 	( 24 )
#define OEKAKI_BOARD_H	 	(  8 )
#define OEKAKI_GRAPHI_SIZE  ( OEKAKI_BOARD_W*OEKAKI_BOARD_H*32 )

// �����p�l���̑J�ڗp
enum{
	MYSIGN_MODE_INIT  = 0, 
    MYSIGN_MODE,
	MYSIGN_MODE_END_SELECT,
	MYSIGN_MODE_END_SELECT_WAIT,
	MYSIGN_MODE_REWRITE,
    MYSIGN_MODE_REWRITE_WAIT,
	MYSIGN_MODE_REWRITE_SELECT,
   
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
	u8 x[8];	// �ő�8�񕪂̃^�b�`���W
	u8 y[8];	// 
	u8 brush:4;	// �I�𒆂̃u���V
	u8 size:4;	// �T���v�����O������
}TOUCH_INFO;

typedef struct{
	u8   x,y;
	u16  size;
}OLD_TOUCH_INFO;

typedef struct{
	s8 OldDirX;
	s8 OldDirY;
	s8 DirX;
	s8 DirY;
	u8 Snd;
}SCRUCH_INFO;


//============================================================================================
//	�\���̒�`
//============================================================================================

struct MYSIGN_WORK{
	GF_BGL_INI		*bgl;
	BOOL			wipe_end;
	RECORD			*record;
	CONFIG			*config;

	WORDSET			*WordSet;								// ���b�Z�[�W�W�J�p���[�N�}�l�[�W���[
	MSGDATA_MANAGER *MsgManager;							// ���O���̓��b�Z�[�W�f�[�^�}�l�[�W���[
	STRBUF			*TrainerName[OEKAKI_MEMBER_MAX];		// ���O
	STRBUF			*EndString;								// ������u��߂�v
	STRBUF			*TitleString;								// ������u��߂�v
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
	CLACT_WORK_PTR			ButtonActWork[9];						// �{�^���A�N�^�[�|�C���^

	GF_BGL_BMPWIN 			TrainerNameWin[BMP_OEKAKI_MAX];			// ���G������ʗpBMP�E�C���h�E
	GF_BGL_BMPWIN			OekakiBoard;
	GF_BGL_BMPWIN			MsgWin;									// ��b�E�C���h�E
	GF_BGL_BMPWIN			EndWin;									// ��߂�
	GF_BGL_BMPWIN			TitleWin;								// �u�g���[�i�[�T�C�����������I�v
	GF_BGL_BMPWIN			*YesNoWin[2];							// �͂��E�������E�C���h�E�̃|�C���^

	int						seq;									// ���݂̕������͏�ԁi����OK/�A�j�����j�Ȃ�
	int						mode;									// ���ݍőO�ʂ̕����p�l��
	int						wait;

	u8						SendBoardGraphic[0x4000];
	u16						CursorPal;
	u8						brush_color;
	u8						brush;

	TOUCH_INFO				MyTouchResult;							// �����̃T���v�����O���ʁi����͑��M���邾��
	TOUCH_INFO				AllTouchResult[OEKAKI_MEMBER_MAX];		// �ʐM�Ŏ擾�����T���v�����O���ʁi���̃f�[�^�ŕ`�悷��
	OLD_TOUCH_INFO			OldTouch[OEKAKI_MEMBER_MAX];			// �O�񂩂�̃|�C���g����

	u8						canvas_buf[OEKAKI_GRAPHI_SIZE];
	u8						*SignBuf;								// �g���[�i�[�J�[�h�̃T�C���̈���w���|�C���^
	u8						TransWork[0x20*4*2];

	TOUCH_SW_SYS			*TouchSubWindowSys;
	SCRUCH_INFO				scruchInfo;								// �����茟�o�p���[�N
	int						BeforeX,BeforeY;

#ifdef PM_DEBUG
	int 					frame;									//
	int						framenum[9][2];							//
#endif
};


#endif