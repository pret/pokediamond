//=============================================================================
/**
 * @file	wifi_note_local.h
 * @brief	WIFI�蒠���[�J����`
 * @author	k.ohno
 * @date    2006.4.5
 */
//=============================================================================


#ifndef __WIFI_NOTE_LOCAL_H__
#define __WIFI_NOTE_LOCAL_H__

#include "savedata/wifilist.h"
#include "communication/communication.h"

#define WIFINOTE_MEMBER_MAX  (WIFILIST_FRIEND_MAX)
#define WIFINOTE_DISP_MEMBER_MAX  (8)

// �@�\�{�^���p��`
#define FUNCBUTTON_NUM	( 7 ) 		// �@�\�{�^���̐�
#define START_WORDPANEL ( 0 )		// �ŏ��̕������̓p�l���̔ԍ��i�O���Ђ炪�ȁj

// CLACT�Œ�`���Ă���Z�����傫�����ăT�u��ʂɉe�����łĂ��܂��̂ŗ����Ă݂�
#define NAMEIN_SUB_ACTOR_DISTANCE 	(256*FX32_ONE)

// CellActor�ɏ��������郊�\�[�X�}�l�[�W���̎�ނ̐��i���}���`�Z���E�}���`�Z���A�j���͎g�p���Ȃ��j
#define CLACT_RESOURCE_NUM		(  4 )
#define _OAM_NUM			( 10 )  // �W�̂̃g���[�i�[�{���E���
#define _LEFT_ARROW       (8)
#define _RIGHT_ARROW       (9)
#define _UNION_CREATURE  (1)
#define _LIST_ARROW  (0)


#define FRIENDCODE_MAXLEN     (12)

// ���b�Z�[�W�\�����WAIT
#define WIFINOTE_CORNER_MESSAGE_END_WAIT	( 60 )


// �����p�l���̑J�ڗp
enum{
  WIFINOTE_MODE_INIT  = 0, 
  WIFINOTE_MODE,
  WIFINOTE_MODE_FRIENDLIST_INIT,
  WIFINOTE_MODE_FRIENDLIST,
  WIFINOTE_MODE_PERSONAL_MENU,
  WIFINOTE_MODE_PERSONAL_MENU_WAIT,
  WIFINOTE_MODE_MAIN_MENU,
  WIFINOTE_MODE_CODEINPUT_INIT,
  WIFINOTE_MODE_CODEINPUT_INIT_WAIT,
  WIFINOTE_MODE_CODEINPUT_LOOP,
  WIFINOTE_MODE_CODEINPUT_LOOPNEXT,
  WIFINOTE_MODE_CODEINPUT_LOOP2,
  WIFINOTE_MODE_CODEINPUT_END_WAIT,
  WIFINOTE_MODE_CODEINPUT_YESNO,
  WIFINOTE_MODE_CODEINPUT_YESNO_WAIT,
  WIFINOTE_MODE_FRIENDCODE_DIFFER,
  WIFINOTE_MODE_FRIENDCODE_DIFFER_WAIT,
  WIFINOTE_MODE_END_WAIT,
  WIFINOTE_MODE_MYCODE_DISP_INIT,
  WIFINOTE_MODE_MYCODE_DISP,
  WIFINOTE_MODE_INFO_INIT,
  WIFINOTE_MODE_INFO_DISP,
  WIFINOTE_MODE_INFO_END,
  WIFINOTE_MODE_RENAME_INIT,   // �Ȃ܂���������
  WIFINOTE_MODE_RENAME_OPEN_WINDOW,
  WIFINOTE_MODE_RENAME_WAIT,
  WIFINOTE_MODE_RENAME_ENTRY,
  WIFINOTE_MODE_DELETE_INIT,   // ����
  WIFINOTE_MODE_DELETE_YESNO,
  WIFINOTE_MODE_DELETE_CHECK,
  WIFINOTE_MODE_CODE_INIT,
};


enum{
	WIFINOTE_SYNCHRONIZE_END=201,
};

// �㉺��ʎw���`
#define BOTH_LCD	( 2 )

// BMPWIN�w��
enum{
	BMP_NAME1_S_BG0,
	BMP_NAME2_S_BG0,
	BMP_NAME3_S_BG0,
	BMP_NAME4_S_BG0,
	BMP_NAME5_S_BG0,
	BMP_WIFINOTE_MAX,
};


#define WIFINOTE_SEND_DATASIZE	( 3000 )

typedef struct{
	u8  data[WIFINOTE_SEND_DATASIZE];		// ���R�[�h�����f�[�^
	u32 _xor;							// �f�[�^�������m�F�pXOR
	u32 seed;							// �e���痈�����̐��l�����ɗ����𔭐������ăf�[�^�����ւ���
}WIFINOTE_DATA;

//============================================================================================
//	�\���̒�`
//============================================================================================

struct _WIFINOTE_WORK{
	NAMEIN_PARAM*		nameinParam;
	GF_BGL_INI		*bgl;									// GF_BGL_INI
    SAVEDATA*  pSaveData;
	WORDSET			*WordSet;								// ���b�Z�[�W�W�J�p���[�N�}�l�[�W���[
	MSGDATA_MANAGER *MsgManager;							// ���O���̓��b�Z�[�W�f�[�^�}�l�[�W���[
	BMPLIST_DATA*   menulist;
    u8              index2No[WIFINOTE_MEMBER_MAX];     // wifilist�������o���ׂ̔ԍ�
    STRBUF			*TrainerName[WIFINOTE_MEMBER_MAX];		// ���O
    STRBUF*         pExpStrBuf;
	STRBUF			*TalkString;							// ��b���b�Z�[�W�p
	STRBUF			*TitleString;							// �^�C�g�����b�Z�[�W�p
	STRBUF			*MenuString[4];							// ���j���[���b�Z�[�W�p
    STRBUF*         pTempTrainerName;        // ���͓o�^���̈ꎞ�o�b�t�@
    STRBUF*       pTempFriendCode;        // ���͓o�^���̈ꎞ�o�b�t�@

  SOFT_SPRITE_MANAGER* spriteManager;
  SOFT_SPRITE*			sprite;
  
	int				MsgIndex;								// �I�����o�p���[�N
    BMPMENU_WORK* pYesNoWork;

	CLACT_SET_PTR 			clactSet;								// �Z���A�N�^�[�Z�b�g
	CLACT_U_EASYRENDER_DATA	renddata;								// �ȈՃ����_�[�f�[�^
	CLACT_U_RES_MANAGER_PTR	resMan[CLACT_RESOURCE_NUM];				// ���\�[�X�}�l�[�W��
	CLACT_U_RES_OBJ_PTR 	resObjTbl[BOTH_LCD][CLACT_RESOURCE_NUM];// ���\�[�X�I�u�W�F�e�[�u��
	CLACT_HEADER			clActHeader_m;							// �Z���A�N�^�[�w�b�_�[
	CLACT_HEADER			clActHeader_s;							// �Z���A�N�^�[�w�b�_�[
	CLACT_WORK_PTR			MainActWork[_OAM_NUM];				// �Z���A�N�^�[���[�N�|�C���^�z��
//	CLACT_WORK_PTR			SubActWork[_OAM_NUM];				// �Z���A�N�^�[���[�N�|�C���^�z��

	GF_BGL_BMPWIN 			TrainerNameWin[WIFINOTE_DISP_MEMBER_MAX];			// ���G������ʗpBMP�E�C���h�E
	GF_BGL_BMPWIN			MsgWin;									// ��b�E�C���h�E
    GF_BGL_BMPWIN           MenuWin[4];
	GF_BGL_BMPWIN			ListWin;									// ��߂�
	GF_BGL_BMPWIN			TitleWin;								// �u���R�[�h�R�[�i�[�@�ڂ��イ���イ�I�v�Ȃ�
    BMPLIST_WORK* lw;		// BMP���j���[���[�N
	u16						*ObjPaletteTable;
	int						seq;									// ���݂̕������͏�ԁi����OK/�A�j�����j�Ȃ�
	int						nextseq;
	int						mode;									// ���ݍőO�ʂ̕����p�l��
	int						wait;
    MYSTATUS                *pMyStatus;
	u16						CursorPal;
	u8						brush_color;
	u8						brush;
    u8     mainCur;
    u8     horizontalCur;
    u8     verticalCur;
    u8     subCur;
  u8 friendTrg;
  
  PROC*		subProc;

  int checkFriend[COMM_MACHINE_MAX];
  int indexFriend[COMM_MACHINE_MAX];
  int addFriendNo;

  u16 pos_bak;

};


// SE�p��`
#define WIFINOTE_MOVE_SE		(SEQ_SE_DP_SELECT)
#define WIFINOTE_DECIDE_SE	(SEQ_SE_DP_SELECT)
#define WIFINOTE_BS_SE		(SEQ_SE_DP_SELECT)


#endif  //__WIFI_NOTE_LOCAL_H__

