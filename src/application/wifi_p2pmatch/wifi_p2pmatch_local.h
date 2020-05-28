//=============================================================================
/**
 * @file	wifi_note_local.h
 * @brief	WIFI�蒠���[�J����`
 * @author	k.ohno
 * @date    2006.4.5
 */
//=============================================================================


#ifndef __WIFI_P2PMATCH_LOCAL_H__
#define __WIFI_P2PMATCH_LOCAL_H__

#include "savedata/wifilist.h"

#define WIFIP2PMATCH_MEMBER_MAX  (WIFILIST_FRIEND_MAX)
#define WIFIP2PMATCH_DISP_MEMBER_MAX  (5)

// �@�\�{�^���p��`
#define FUNCBUTTON_NUM	( 7 ) 		// �@�\�{�^���̐�
#define START_WORDPANEL ( 0 )		// �ŏ��̕������̓p�l���̔ԍ��i�O���Ђ炪�ȁj

// CLACT�Œ�`���Ă���Z�����傫�����ăT�u��ʂɉe�����łĂ��܂��̂ŗ����Ă݂�
#define NAMEIN_SUB_ACTOR_DISTANCE 	(256*FX32_ONE)

// CellActor�ɏ��������郊�\�[�X�}�l�[�W���̎�ނ̐��i���}���`�Z���E�}���`�Z���A�j���͎g�p���Ȃ��j
#define CLACT_RESOURCE_NUM		(  4 )
#define _OAM_NUM			( 5 )

#define FRIENDCODE_MAXLEN     (12)

// ���b�Z�[�W�\�����WAIT
#define WIFIP2PMATCH_CORNER_MESSAGE_END_WAIT	( 60 )


// �����p�l���̑J�ڗp
enum{
  WIFIP2PMATCH_MODE_INIT  = 0,
  WIFIP2PMATCH_NORMALCONNECT_YESNO,
  WIFIP2PMATCH_NORMALCONNECT_WAIT,
  WIFIP2PMATCH_DIFFER_MACHINE_INIT,
  WIFIP2PMATCH_DIFFER_MACHINE_NEXT,
  WIFIP2PMATCH_DIFFER_MACHINE_ONEMORE,
  WIFIP2PMATCH_FIRST_YESNO,
  WIFIP2PMATCH_POWEROFF_INIT,
  WIFIP2PMATCH_POWEROFF_YESNO,
  WIFIP2PMATCH_POWEROFF_WAIT,
  WIFIP2PMATCH_RETRY_INIT,        //10
  WIFIP2PMATCH_RETRY_YESNO,
  WIFIP2PMATCH_RETRY_WAIT,
  WIFIP2PMATCH_RETRY,
  WIFIP2PMATCH_CONNECTING_INIT,
  WIFIP2PMATCH_CONNECTING,
  WIFIP2PMATCH_FIRST_ENDMSG,
  WIFIP2PMATCH_FIRST_ENDMSG_WAIT,
  WIFIP2PMATCH_FRIENDLIST_INIT,
  WIFIP2PMATCH_MODE_FRIENDLIST,
  WIFIP2PMATCH_VCHATWIN_WAIT,           //20
  WIFIP2PMATCH_MODE_VCT_CONNECT_INIT2,
  WIFIP2PMATCH_MODE_VCT_CONNECT_INIT,
  WIFIP2PMATCH_MODE_VCT_CONNECT_WAIT,
  WIFIP2PMATCH_MODE_VCT_CONNECT,
  WIFIP2PMATCH_MODE_VCT_CONNECTEND_YESNO,
  WIFIP2PMATCH_MODE_VCT_CONNECTEND_WAIT,
  WIFIP2PMATCH_MODE_VCT_DISCONNECT,
  WIFIP2PMATCH_MODE_BATTLE_DISCONNECT,
  WIFIP2PMATCH_MODE_DISCONNECT,
  WIFIP2PMATCH_MODE_BATTLE_CONNECT_INIT,  //30
  WIFIP2PMATCH_MODE_BATTLE_CONNECT_WAIT,
  WIFIP2PMATCH_MODE_BATTLE_CONNECT,
  WIFIP2PMATCH_MODE_MAIN_MENU,
  WIFIP2PMATCH_MODE_END_WAIT,
  WIFIP2PMATCH_MODE_CHECK_AND_END,
  WIFIP2PMATCH_MODE_SELECT_INIT,
  WIFIP2PMATCH_MODE_SELECT_WAIT,
  WIFIP2PMATCH_MODE_SUBBATTLE_WAIT,
  WIFIP2PMATCH_MODE_SELECT_REL_INIT,
  WIFIP2PMATCH_MODE_SELECT_REL_YESNO,       //40
  WIFIP2PMATCH_MODE_SELECT_REL_WAIT,
  WIFIP2PMATCH_MODE_MATCH_INIT,
  WIFIP2PMATCH_MODE_MATCH_WAIT,
  WIFIP2PMATCH_MODE_MATCH_LOOP,
  WIFIP2PMATCH_MODE_BCANCEL_YESNO,
  WIFIP2PMATCH_MODE_BCANCEL_WAIT,
  WIFIP2PMATCH_MODE_CALL_INIT,
  WIFIP2PMATCH_MODE_CALL_YESNO,
  WIFIP2PMATCH_MODE_CALL_SEND,
  WIFIP2PMATCH_MODE_CALL_CHECK,             //50
  WIFIP2PMATCH_MODE_MYSTATUS_WAIT,
  WIFIP2PMATCH_MODE_CALL_WAIT,
  WIFIP2PMATCH_MODE_PERSONAL_INIT,
  WIFIP2PMATCH_MODE_PERSONAL_WAIT,
  WIFIP2PMATCH_MODE_PERSONAL_END,
  WIFIP2PMATCH_MODE_EXIT_YESNO,
  WIFIP2PMATCH_MODE_EXIT_WAIT,
  WIFIP2PMATCH_MODE_EXITING,
  WIFIP2PMATCH_MODE_EXIT_END,
  WIFIP2PMATCH_NEXTBATTLE_YESNO,         //60
  WIFIP2PMATCH_NEXTBATTLE_WAIT,
  WIFIP2PMATCH_MODE_VCHAT_NEGO,
  WIFIP2PMATCH_MODE_VCHAT_NEGO_WAIT,
  WIFIP2PMATCH_RECONECTING_WAIT,
  WIFIP2PMATCH_MODE_BCANCEL_YESNO_VCT,
  WIFIP2PMATCH_MODE_BCANCEL_WAIT_VCT,
};


enum{
	WIFIP2PMATCH_SYNCHRONIZE_END=201,
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
	BMP_WIFIP2PMATCH_MAX,
};


//---------------WIFISTATUS�f�[�^

typedef enum{
  WIFI_STATUS_NONE,   // ��������
  WIFI_STATUS_VCT,      // VCT��
  WIFI_STATUS_SBATTLE50,      // �V���O���ΐ풆
  WIFI_STATUS_SBATTLE100,      // �V���O���ΐ풆
  WIFI_STATUS_SBATTLE_FREE,      // �V���O���ΐ풆
  WIFI_STATUS_DBATTLE50,      // �_�u���ΐ풆
  WIFI_STATUS_DBATTLE100,      // �_�u���ΐ풆
  WIFI_STATUS_DBATTLE_FREE,      // �_�u���ΐ풆
  WIFI_STATUS_TRADE,          // ������
  WIFI_STATUS_SBATTLE50_WAIT,   // �V���O��Lv50�ΐ��W��
  WIFI_STATUS_SBATTLE100_WAIT,   // �V���O��Lv100�ΐ��W��
  WIFI_STATUS_SBATTLE_FREE_WAIT,   // �V���O��Lv100�ΐ��W��
  WIFI_STATUS_DBATTLE50_WAIT,   // �_�u��Lv50�ΐ��W��
  WIFI_STATUS_DBATTLE100_WAIT,   // �_�u��Lv100�ΐ��W��
  WIFI_STATUS_DBATTLE_FREE_WAIT,   // �_�u��Lv100�ΐ��W��
  WIFI_STATUS_TRADE_WAIT,    // ������W��
  WIFI_STATUS_LOGIN_WAIT,    // �ҋ@���@���O�C������͂���
  WIFI_STATUS_UNKNOWN,   // �V���ɍ�����炱�̔ԍ��ȏ�ɂȂ�
};

typedef enum{
  _REGULATION_BATTLE_TOWER     // �o�g���^���[�ΐ����
};


//�g�[�^��189�o�C�g���M�ł��邪�Ƃ肠�������ʃv���O�����͔͈͕���������
#define _POKEMON_NUM   (6)


typedef struct{
  u16 pokemonType[_POKEMON_NUM];
  u16 hasItemType[_POKEMON_NUM];
  u8 version;
  u8 regionCode;
  u8 pokemonZukan;
  u8 status;
  u8 regulation;
  u8 trainer_view;
  u8 sex;
  u8 nation;
  u8 area;
  u8 vchat;
  u8 vchat_org;
} _WIFI_MACH_STATUS;

#define _WIFI_STATUS_MAX_SIZE  (sizeof(_WIFI_MACH_STATUS))

//============================================================================================
//	�\���̒�`
//============================================================================================

typedef struct {
  _WIFI_MACH_STATUS myMatchStatus;   // �����̃}�b�`���O��ԃf�[�^
  _WIFI_MACH_STATUS friendMatchStatus[WIFIP2PMATCH_MEMBER_MAX]; // ����̃}�b�`���O��ԃf�[�^
} TEST_MATCH_WORK;


struct _WIFIP2PMATCH_WORK{
  WIFI_LIST* pList;
  TEST_MATCH_WORK* pMatch;
  int friendMatchReadCount;
  u8 index2No[WIFIP2PMATCH_MEMBER_MAX];
  int matchStatusBackup[WIFIP2PMATCH_MEMBER_MAX];
  NAMEIN_PARAM*		nameinParam;
  BMPLIST_DATA*   menulist;
  BMPLIST_WORK* lw;		// BMP���j���[���[�N
  BMPLIST_DATA*   submenulist;
  BMPLIST_WORK* sublw;		// BMP���j���[���[�N
  GF_BGL_INI		*bgl;									// GF_BGL_INI
  SAVEDATA*  pSaveData;
  WORDSET			*WordSet;								// ���b�Z�[�W�W�J�p���[�N�}�l�[�W���[
  MSGDATA_MANAGER *MsgManager;							// ���O���̓��b�Z�[�W�f�[�^�}�l�[�W���[
  MSGDATA_MANAGER *SysMsgManager;  //
  STRBUF			*TrainerName[WIFIP2PMATCH_MEMBER_MAX];		// ���O
  STRBUF			*MsgString;								// ���b�Z�[�W
  STRBUF*         pExpStrBuf;
  STRBUF			*TalkString;							// ��b���b�Z�[�W�p
  STRBUF			*TitleString;							// �^�C�g�����b�Z�[�W�p
  STRBUF			*MenuString[4];							// ���j���[���b�Z�[�W�p
  STRBUF*         pTemp;        // ���͓o�^���̈ꎞ�o�b�t�@
  
  int				MsgIndex;								// �I�����o�p���[�N
  BMPMENU_WORK* pYesNoWork;
  void* timeWaitWork;
  CLACT_SET_PTR 			clactSet;								// �Z���A�N�^�[�Z�b�g
  CLACT_U_EASYRENDER_DATA	renddata;								// �ȈՃ����_�[�f�[�^
  CLACT_U_RES_MANAGER_PTR	resMan[CLACT_RESOURCE_NUM];				// ���\�[�X�}�l�[�W��
  CLACT_U_RES_OBJ_PTR 	resObjTbl[BOTH_LCD][CLACT_RESOURCE_NUM];// ���\�[�X�I�u�W�F�e�[�u��
  CLACT_HEADER			clActHeader_m;							// �Z���A�N�^�[�w�b�_�[
  CLACT_HEADER			clActHeader_s;							// �Z���A�N�^�[�w�b�_�[
  CLACT_WORK_PTR			MainActWork[_OAM_NUM];				// �Z���A�N�^�[���[�N�|�C���^�z��
	//CLACT_WORK_PTR			SubActWork[_OAM_NUM];				// �Z���A�N�^�[���[�N�|�C���^�z��

  GF_BGL_BMPWIN			MsgWin;									// ��b�E�C���h�E
  //   GF_BGL_BMPWIN           MenuWin[4];
  GF_BGL_BMPWIN			MyInfoWin;									// ��߂�
  GF_BGL_BMPWIN			TitleWin;								// �u���R�[�h�R�[�i�[�@�ڂ��イ���イ�I�v�Ȃ�
  GF_BGL_BMPWIN			SysMsgWin;								// �u���R�[�h�R�[�i�[�@�ڂ��イ���イ�I�v�Ȃ�
  GF_BGL_BMPWIN			ListWin;									// ��߂�
  GF_BGL_BMPWIN			SubListWin;									// ��߂�
  GF_BGL_BMPWIN			MyWin;									// ��߂�

  int localTime;
  int seq;									// ���݂̕������͏�ԁi����OK/�A�j�����j�Ȃ�
  int       endSeq;
  int						nextseq;
  int initSeq;
  int						mode;									// ���ݍőO�ʂ̕����p�l��
  int						timer;
  MYSTATUS                *pMyStatus;
  u8     mainCur;
  u8     subCur;
  BOOL bInitMessage;
  PROC*		subProc;
  int preConnect;
  u16 battleCur;
  u16 singleCur[2];
  u16 bSingle;
  u16 keepStatus;
  u16 keepVChat;
  u16 friendNo;
  BOOL bRetryBattle;
};




#endif  //__WIFI_P2PMATCH_LOCAL_H__

