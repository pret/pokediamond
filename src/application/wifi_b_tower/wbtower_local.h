//=============================================================================
/**
 * @file	wbtower_local.h
 * @brief	WIFI�o�g���^���[�����w�b�_�t�@�C��
 *          
 * @author	Akito Mori
 * @date    	2006.05.16
 */
//=============================================================================


#ifndef __WBTOWER_LOCAL_H__
#define __WBTOWER_LOCAL_H__

#include "communication/wm_icon.h"
#include "system/bmp_list.h"


// Proc_Main�V�[�P���X��`
enum {
	SEQ_INIT_DPW=0,
	SEQ_INIT,
	SEQ_FADEIN,
	SEQ_MAIN,
	SEQ_FADEOUT,
	SEQ_OUT,
};

// �T�u�v���Z�X����ԍ�
enum{
	WBTOWER_ENTER=0,		// �ڑ����
};

// �T�u�v���Z�X�ɓn�����[�h�i�����T�u�v���Z�X�ł��g�������Ⴄ�������邽�߁j
enum{
	MODE_DOWNLOAD=0,
	MODE_UPLOAD,
};

// CLACT�Œ�`���Ă���Z�����傫�����ăT�u��ʂɉe�����łĂ��܂��̂ŗ����Ă݂�
#define WBTOWER_SUB_ACTOR_DISTANCE 	(256*FX32_ONE)

// CellActor�ɏ��������郊�\�[�X�}�l�[�W���̎�ނ̐��i���}���`�Z���E�}���`�Z���A�j���͎g�p���Ȃ��j
#define CLACT_RESOURCE_NUM		(  4 )
#define NAMEIN_OAM_NUM			( 14 )

#define WBTOWER_MESFRAME_PAL	 ( 10 )
#define WBTOWER_MENUFRAME_PAL    ( 11 )
#define WBTOWER_MESFRAME_CHR	 (  1 )
#define WBTOWER_MENUFRAME_CHR 	 ( WBTOWER_MESFRAME_CHR + TALK_WIN_CGX_SIZ )
#define WBTOWER_TALKFONT_PAL	 ( 13 )

// ��b�E�C���h�E�\���ʒu��`
#define TALK_WIN_X		(  2 )
#define TALK_WIN_Y		( 19 )
#define	TALK_WIN_SX		( 27 )
#define	TALK_WIN_SY		(  4 )


// ��ʏ㕔�^�C�g���E�C���h�E�\���ʒu��`
#define TITLE_TEXT_X	(  4 )
#define TITLE_TEXT_Y	(  1 )
#define TITLE_TEXT_SX	( 24 )
#define TITLE_TEXT_SY	(  2 )


// �͂��E�������E�C���h�E��Y���W
#define	WBTOWER_YESNO_PY2	( 13 )		// ��b�E�C���h�E���Q�s�̎�

// �^�C�g��������o�b�t�@��
#define TITLE_MESSAGE_BUF_NUM	( 20 * 2 )

// ��b�E�C���h�E������o�b�t�@��
#define TALK_MESSAGE_BUF_NUM	( 90*2 )

// �����N�E���[���ԍ��̕�������
#define NUMBER_BUF_NUM			( 4 )
#define RANK_BUF_NUM			( 3 )

// �����N���l�̏��
#define WIFITOWER_RANK_MAX		( 10 )

// �P�b�҂p�̒�`
#define WAIT_ONE_SECONDE_NUM	( 30 )

// �㉺��ʎw���`
#define RES_NUM		( 3 )
#define MAIN_LCD	( GF_BGL_MAIN_DISP )	// �v�͂O��
#define SUB_LCD		( GF_BGL_SUB_DISP )		// �P�Ȃ�ł����B
#define CHARA_RES	( 2 )

#define DWC_ERROR_BUF_NUM		(16*8*2)

//============================================================================================
//	�\���̒�`
//============================================================================================



struct WBTOWER_WORK{
	// �N�����ɖ���Ă����
	WBTOWER_PARAM *param;								// �Ăяo�����p�����[�^
	GF_BGL_INI		*bgl;								// GF_BGL_INI
	
	
	// WIFI�o�g���^���[�V�X�e���Ɋւ�����
	int				seq;								// ���݂̐��E������ʂ̏��
	int				nextseq;							// ���݂̃V�[�P���X���I�������ۂ̑J�ڐ�

	int				sub_process;						// ���E�����T�u�v���O��������i���o�[
	int				sub_nextprocess;					// ���E�����T�uNEXT����i���o�[
	int				sub_process_mode;					// ���̉�ʂɂ������[�h�͉����H

	int				subprocess_seq;						// �T�u�v���O�����V�[�P���XNO
	int				subprocess_nextseq;					// �T�u�v���O����NEXT�V�[�P���XNO


	void 			*heapPtr;							// NitroDWC�ɓn���q�[�v���[�N�̉���p�|�C���^
	NNSFndHeapHandle heapHandle;						// heapPtr��32�o�C�g�A���C�����g�ɍ��킹���|�C���^
	DWCInetControl  stConnCtrl;							// DWC�ڑ����[�N


	// �e��ʂ��ʂ��Ă��ۑ�����Ă����
	int				Rank;
	int				NowRank;
	int				RoomNum;
	int				NowRoom;
	Dpw_Bt_Room 	roomBtData;							// �_�E�����[�h�����f�[�^���i�[����
	Dpw_Bt_Player	BtPlayer;							// ���������������̃f�[�^

	u16				TitleCursorPos;						// �^�C�g�����j���[�̃J�[�\���ʒu
	u16				PartnerPageInfo;					// ���E�E�y�[�W�̂ǂ�����݂Ă��邩�H
	u16				BoxTrayNo;							// ���ԃ{�b�N�X�����Ă��邩�H
	u16				BoxCursorPos;						// �{�b�N�X��ł̃J�[�\���̈ʒu
	POKEMON_PASO_PARAM	*deposit_ppp;					// ��U�a����w��ɂȂ����|�P�����̃|�C���^
	int				SearchResult;						// �����̌��ʕԂ��Ă�����
	int				TouchTrainerPos;					// �������ʂ̒N���^�b�`������


	// �`��܂��̃��[�N�i���BMP�p�̕��������j
	WORDSET			*WordSet;								// ���b�Z�[�W�W�J�p���[�N�}�l�[�W���[
	MSGDATA_MANAGER *MsgManager;							// ���O���̓��b�Z�[�W�f�[�^�}�l�[�W���[
	MSGDATA_MANAGER *LobbyMsgManager;						// ���O���̓��b�Z�[�W�f�[�^�}�l�[�W���[
	MSGDATA_MANAGER *SystemMsgManager;						// Wifi�V�X�e�����b�Z�[�W�f�[�^
	STRBUF			*TalkString;							// ��b���b�Z�[�W�p
	STRBUF			*TitleString;							// �^�C�g�����b�Z�[�W�p
	STRBUF			*RoomString;							// �����ԍ��I��p
	STRBUF			*RankString;							// �����N�I��p
	STRBUF			*ErrorString;							// �����N�I��p
	int				MsgIndex;								// �I�����o�p���[�N


	// �`�����̃��[�N�i���OAM)
	CLACT_SET_PTR 			clactSet;								// �Z���A�N�^�[�Z�b�g
	CLACT_U_EASYRENDER_DATA	renddata;								// �ȈՃ����_�[�f�[�^
	CLACT_U_RES_MANAGER_PTR	resMan[CLACT_RESOURCE_NUM];				// ���\�[�X�}�l�[�W��
	CLACT_U_RES_OBJ_PTR 	resObjTbl[RES_NUM][CLACT_RESOURCE_NUM]; // ���\�[�X�I�u�W�F�e�[�u��
	CLACT_HEADER			clActHeader_main;						// �Z���A�N�^�[�w�b�_�[
	CLACT_HEADER			clActHeader_sub;						// �Z���A�N�^�[�w�b�_�[
	CLACT_HEADER			clActHeader_friend;						// �Z���A�N�^�[�w�b�_�[
	CLACT_WORK_PTR			ArrowActWork[2];						// �Z���A�N�^�[���[�N�|�C���^�z��

	// BMPWIN�`�����
	GF_BGL_BMPWIN			MsgWin;									// ��b�E�C���h�E
	GF_BGL_BMPWIN			RankWin;								// �����N�w��p�E�C���h�E
	GF_BGL_BMPWIN			NumberWin;								// �����i���o�[�w��p�E�C���h�E
	GF_BGL_BMPWIN			TitleWin;								// �u���R�[�h�R�[�i�[�@�ڂ��イ���イ�I�v�Ȃ�
	GF_BGL_BMPWIN			SubWin;									// �u���R�[�h�R�[�i�[�@�ڂ��イ���イ�I�v�Ȃ�
	GF_BGL_BMPWIN			MenuWin[3];								// ���j���[�pBMPWIN
	GF_BGL_BMPWIN			InfoWin[11];	


	BMPMENU_WORK			*YesNoMenuWork;
	void*					timeWaitWork;							// ��b�E�C���h�E���A�C�R�����[�N

	int						ErrorRet;
	int						ErrorCode;
	int						ConnectErrorNo;

	int						wait;

};


//============================================================================================
// SE�p��`
//============================================================================================
#define WBTOWER_MOVE_SE		(SEQ_SE_DP_SELECT)
#define WBTOWER_DECIDE_SE	(SEQ_SE_DP_SELECT)


//============================================================================================
// extern�錾
//============================================================================================
// worldtrade.c
extern void WBTower_MakeCLACT(CLACT_ADD *add, WBTOWER_WORK *wk, CLACT_HEADER *header, int param);
extern BMPMENU_WORK *WBTower_BmpWinYesNoMake( GF_BGL_INI *bgl, int y, int yesno_bmp_cgx );
extern void WBTower_SetNextSeq( WBTOWER_WORK *wk, int to_seq, int next_seq );
extern void WBTower_SetNextProcess( WBTOWER_WORK *wk, int next_process );
extern void WBTower_ActPos( CLACT_WORK_PTR act, int x, int y );
extern  int WBTower_WifiLinkLevel( void );
extern void WBTower_BmpWinPrint( GF_BGL_BMPWIN *win, MSGDATA_MANAGER *msgman, int msgno, u16 dat );
extern void WBTower_SysPrint( GF_BGL_BMPWIN *win, STRBUF *strbuf, int x, int y, int flag, GF_PRINTCOLOR color );
extern void WBTower_TalkPrint( GF_BGL_BMPWIN *win, STRBUF *strbuf, int x, int y, int flag, GF_PRINTCOLOR color );

extern void WBTower_WifiIconAdd( WBTOWER_WORK *wk );
extern void WBTower_SubProcessChange( WBTOWER_WORK *wk, int subprccess, int mode );


// worldtrade_enter.c
extern int WBTower_EnterEnd( WBTOWER_WORK *wk, int seq);
extern int WBTower_EnterMain(WBTOWER_WORK *wk, int seq);
extern int WBTower_EnterInit(WBTOWER_WORK *wk, int seq);


// workdtrade_uploadf.c
extern int WBTower_Upload_Init(WBTOWER_WORK *wk, int seq);
extern int WBTower_Upload_Main(WBTOWER_WORK *wk, int seq);
extern int WBTower_Upload_End(WBTOWER_WORK *wk, int seq);


#endif /* __WBTOWER_LOCAL_H__ */