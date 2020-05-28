//=============================================================================
/**
 * @file	worldtrade_local.h
 * @brief	���E������ʃw�b�_�t�@�C��
 *          
 * @author	Akito Mori
 * @date    	2006.04.16
 */
//=============================================================================


#ifndef __WORLDTRADE_LOCAL_H__
#define __WORLDTRADE_LOCAL_H__

#include "system/bmp_list.h"
#include "communication/wm_icon.h"
#include "savedata/zukanwork.h"
#include "savedata/wifilist.h"
#include "savedata/wifihistory.h"
#include "application/p_status.h"
#include "demo/demo_trade.h"
#include "battle/shinka.h"

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
	WORLDTRADE_ENTER=0,		// �ڑ����
	WORLDTRADE_TITLE,		// �^�C�g���E���j���[
	WORLDTRADE_MYPOKE,		// �悤�����݂�
	WORLDTRADE_PARTNER,		// �����Ẵ|�P�����̂悤�����݂�
	WORLDTRADE_SEARCH,		// �|�P��������������
	WORLDTRADE_MYBOX,		// �����̃{�b�N�X
	WORLDTRADE_DEPOSIT,		// �ق����|�P�����̏���
	WORLDTRADE_UPLOAD,		// �|�P�����f�[�^���A�b�v���[�h
	WORLDTRADE_STATUS,		// �|�P�����X�e�[�^�X�Ăяo��
	WORLDTRADE_DEMO,		// �|�P�����X�e�[�^�X�Ăяo��
};

// �T�u�v���Z�X�ɓn�����[�h�i�����T�u�v���Z�X�ł��g�������Ⴄ�������邽�߁j
enum{
	// worldtrade_title.c
	MODE_OPENING=0,				// ���߂Ă����Ƃ�
	MODE_CONTINUE,				// �p�����邽�߂ɂ���
	MODE_NOT_END,				// ����߂��I�񂾂��A��߂Ȃ�����

	// worldtrade_mypoke.c
	MODE_VIEW,					// �a�����|�P�����̂悤�����݂�
	MODE_DEPOSIT,				// ���������|�P�����ƌ�������Ƃ��ɂ݂�

	// worldtrade_box.c
	MODE_DEPOSIT_SELECT,		// ��������|�P������a����Ƃ�
	MODE_EXCHANGE_SELECT,		// ���������|�P�����ƌ�������|�P������I��
	
	// worldtrade_upload.c
	MODE_UPLOAD,				// �|�P������a�����ʂɍs��
	MODE_DOWNLOAD,				// �|�P�������������
	MODE_EXCHANGE,				// �|�P��������������
	MODE_DOWNLOAD_EX,
	MODE_SERVER_CHECK,	// �|�P��������������Ă��邩�m�F���遨���j���[��
//	MODE_SERVER_CHECK,	// �|�P��������������Ă��邩�m�F���遨�悤�����݂��
	MODE_POKEMON_EVO_SAVE,		// �����|�P�������i��������̃Z�[�u����

};

// CLACT�Œ�`���Ă���Z�����傫�����ăT�u��ʂɉe�����łĂ��܂��̂ŗ����Ă݂�
#define NAMEIN_SUB_ACTOR_DISTANCE 	(256*FX32_ONE)

// CellActor�ɏ��������郊�\�[�X�}�l�[�W���̎�ނ̐��i���}���`�Z���E�}���`�Z���A�j���͎g�p���Ȃ��j
#define CLACT_RESOURCE_NUM		(  4 )
#define NAMEIN_OAM_NUM			( 14 )

#define WORLDTRADE_MESFRAME_PAL	 ( 10 )
#define WORLDTRADE_MENUFRAME_PAL ( 11 )
#define WORLDTRADE_MESFRAME_CHR	 (  1 )
#define WORLDTRADE_MENUFRAME_CHR ( WORLDTRADE_MESFRAME_CHR + TALK_WIN_CGX_SIZ )
#define WORLDTRADE_TALKFONT_PAL	 ( 13 )

// ��b�E�C���h�E�\���ʒu��`
#define TALK_WIN_X		(  2 )
#define TALK_WIN_Y		( 19 )
#define	TALK_WIN_SX		( 27 )
#define	TALK_WIN_SY		(  4 )


// �P�s���b�Z�[�W�E�C���h�E�\���ʒu��`
#define LINE_TEXT_X		(  2 )
#define LINE_TEXT_Y		( 21 )
#define	LINE_TEXT_SX	( 27 )
#define	LINE_TEXT_SY	(  2 )


// ��ʏ㕔�^�C�g���E�C���h�E�\���ʒu��`
#define TITLE_TEXT_X	(  1 )
#define TITLE_TEXT_Y	(  1 )
#define TITLE_TEXT_SX	( 28 )
#define TITLE_TEXT_SY	(  2 )

#define HEAD_LIST_X		( 15 )
#define HEAD_LIST_Y		(  5 )
#define HEAD_LIST_SX	(  4 )
#define HEAD_LIST_SY	( 13 )

#define NAME_LIST_X		( 21 )
#define NAME_LIST_Y		(  5 )
#define NAME_LIST_SX	( 10 )
#define NAME_LIST_SY	( 13 )


// �I�����X�g�̈ʒu�E����`(_deposit.c _search.c)
// ������
#define SELECT_MENU1_X	(  15 )
#define SELECT_MENU1_Y 	(   5 )
#define SELECT_MENU1_SX	(   4 )
#define SELECT_MENU1_SY	(  13 )

// �|�P������
#define SELECT_MENU2_X	(  21 )
#define SELECT_MENU2_Y 	(   5 )
#define SELECT_MENU2_SX	(  10 )
#define SELECT_MENU2_SY	(  13 )

// ����
#define SELECT_MENU3_X	(  21 )
#define SELECT_MENU3_Y 	(  10 )
#define SELECT_MENU3_SX	(  10 )
#define SELECT_MENU3_SY	(   8 )

// �~�������x��
#define SELECT_MENU4_X	(  15 )
#define SELECT_MENU4_Y 	(   5 )
#define SELECT_MENU4_SX	(  16 )
#define SELECT_MENU4_SY	(  13 )


// �͂��E�������E�C���h�E��Y���W
#define	WORLDTRADE_YESNO_PY2	( 13 )		// ��b�E�C���h�E���Q�s�̎�
#define	WORLDTRADE_YESNO_PY1	( 15 )		// ��b�E�C���h�E���P�s�̎�

// �^�C�g��������o�b�t�@��
#define TITLE_MESSAGE_BUF_NUM	( 20 * 2 )

// ��b�E�C���h�E������o�b�t�@��
#define TALK_MESSAGE_BUF_NUM	( 90*2 )

#define DWC_ERROR_BUF_NUM		(16*8*2)

// �{�b�N�X�g������
#define BOX_TRAY_NAME_BUF_NUM	( 9*2 )

// �㉺��ʎw���`
#define RES_NUM	( 3 )
#define MAIN_LCD	( GF_BGL_MAIN_DISP )	// �v�͂O��
#define SUB_LCD		( GF_BGL_SUB_DISP )		// �P�Ȃ�ł����B
#define CHARA_RES	( 2 )



// BMPWIN�w��
enum{
	BMP_NAME1_S_BG0,
	BMP_NAME2_S_BG0,
	BMP_NAME3_S_BG0,
	BMP_NAME4_S_BG0,
	BMP_NAME5_S_BG0,
	BMP_RECORD_MAX,
};

// �P��ʂ̃{�b�N�X�̒��̃|�P�����̐�
#define BOX_POKE_NUM		( 30 )

// �|�P�����A�C�R���̃p���b�g��]������I�t�Z�b�g
#define POKEICON_PAL_OFFSET				(  3 )

// �I���ł��Ȃ��|�P�����A�C�R���̃p���b�g
#define POKEICON_NOTSELECT_PAL_OFFSET	(  6 )

// �|�P�����A�C�R�����n�܂�VRAM��ł̃I�t�Z�b�g
#define POKEICON_VRAM_OFFSET ( 12 )

// �T�O�����̃|�P�����̓������̐��i�A�J�T�^�i�n�}�������j
#define HEADWORD_NUM		( 10 )

// �A�C�e���E���[���A�C�R���̃Z���A�j���ԍ�
#define CELL_ITEMICON_NO	( 40 )
#define CELL_MAILICON_NO	( 41 )
#define CELL_CBALLICON_NO	( 42 )

// �{�b�N�X���̖��
#define CELL_BOXARROW_NO	( 38 )


// �|�P��������
#define SEARCH_POKE_MAX		(  7 )

#define SUB_OBJ_NUM			(  8 )

// 1�b�҂�
#define WAIT_ONE_SECONDE_NUM	( 30 )

// ���C�v�̃X�s�[�h
#define WORLDTRADE_WIPE_SPPED	( 6 )

// �T�[�o�[�m�F���ł���悤�ɂȂ�܂ł̕b���i�U�O�b�j
#define SEVER_RETRY_WAIT		( 60*30 )


//============================================================================================
//	�\���̒�`
//============================================================================================

// �|�P������a����ۂ̏��
typedef struct{

	// �|�P�����̎푰�����i�[����e�[�u���i2�d��ALLOC����j
	STRBUF **pokename;

	// �|�P�����a���E�������p
	u16		headwordPos;		// �I�𓪃J�[�\���ʒu
	u16		headwordListPos;	// �I�����X�g�ʒu
	u16		namePos;			// ���O�I���J�[�\���ʒu
	u16		nameListPos;		// ���O�I�����X�g�ʒu
	int		sexPos;				// ���ʃJ�[�\���ʒu
	int		levelPos;			// ���x���J�[�\���ʒu

	u8		*sinouTable;		// �V���I�E�}�Ӄf�[�^�i���l�͊J��NO�j
	u16		*nameSortTable;		// �|�P�������\�[�g�e�[�u���ǂݍ��݃|�C���^
	int		nameSortNum;		// ������
	int		sex_selection;		// �I�������|�P�����̐��ʕ��z��


	// �|�P����������ʗp
	int		cursorSide;			// 
	int		leftCursorPos;
	int		rightCursorPos;

}DEPOSIT_WORK;

typedef struct{
	Dpw_Tr_PokemonDataSimple	info[BOX_POKE_NUM];
}BOX_RESEARCH;

// ��x���������|�P�������i���������̂��߂ɁA2��ڂ̏������݈ʒu��ۑ����Ă����\����
typedef struct{
	int boxno;
	int pos;
}EVOLUTION_POKEMON_INFO;

#define NAME_HEAD_MAX	( 10 )	// [�A�J�T�^�i�n�}������]�̐��͂P�O��

typedef struct{
	u16 head_list,head_pos;

	u16 name_list[NAME_HEAD_MAX];
	u16 name_pos[NAME_HEAD_MAX];
}SELECT_LIST_POS;

struct WORLDTRADE_WORK{
	// �N�����ɖ���Ă����
	WORLDTRADE_PARAM *param;							// �Ăяo�����p�����[�^
	GF_BGL_INI		*bgl;								// GF_BGL_INI
	WIFI_LIST		*wifilist;							// wifi�ڑ��f�[�^�E�F�B�f�[�^
	
	
	// ���E�����V�X�e���Ɋւ�����
	int				seq;								// ���݂̐��E������ʂ̏��
	int				nextseq;							// ���݂̃V�[�P���X���I�������ۂ̑J�ڐ�

	int				sub_process;						// ���E�����T�u�v���O��������i���o�[
	int				sub_nextprocess;					// ���E�����T�uNEXT����i���o�[
	int				sub_returnprocess;					// next�v���Z�X���Ă�ŏI���������̖߂�v���Z�X
	int				old_sub_process;					// ��O�̃T�u�v���Z�X��ۑ����Ă���
	int				sub_process_mode;					// ���̉�ʂɂ������[�h�͉����H
	int				error_mes_no;

	int				subprocess_seq;						// �T�u�v���O�����V�[�P���XNO
	int				subprocess_nextseq;					// �T�u�v���O����NEXT�V�[�P���XNO

	u16				OpeningFlag;						// ���E�����^�C�g�����������H
	u16				DepositFlag;						// �|�P���������ɃT�[�o�[�ɗa���Ă��邩�H�i1:�a���Ă���j
	u16				ExchangeFlag;						// �a�����|�P��������������Ă���
	u16				serverWaitTime;						// �T�[�o�[�ɃA�N�Z�X�ł��Ȃ��悤�ɂ�����^�C�}�[

	int				ConnectErrorNo;						// DWC�E�܂��̓T�[�o�[����̃G���[
	int				ErrorRet;
	int				ErrorCode;

	void 			*heapPtr;							// NitroDWC�ɓn���q�[�v���[�N�̉���p�|�C���^
	NNSFndHeapHandle heapHandle;						// heapPtr��32�o�C�g�A���C�����g�ɍ��킹���|�C���^
	DWCInetControl   stConnCtrl;							// DWC�ڑ����[�N

	PROC			*proc;								// �X�^�[�^�X�Ăяo���p�T�u�v���Z�X�f�[�^
	PSTATUS_DATA	 statusParam;						// �X�^�[�^�X�Ăяo���p�p�����[�^
	DEMO_TRADE_PARAM tradeDemoParam;					// �����f���p�����[�^
	SHINKA_WORK		 *shinkaWork;						// �ʐM�i���f���p���[�N
	int				 subprocflag;						// �X�e�[�^�X������f�����Ăяo�����߂̃t���O
	u16				listpos;				
	u16				dummy;

	// �e��ʂ��ʂ��Ă��ۑ�����Ă����
	u16				TitleCursorPos;						// �^�C�g�����j���[�̃J�[�\���ʒu
	u16				PartnerPageInfo;					// ���E�E�y�[�W�̂ǂ�����݂Ă��邩�H
	u16				BoxTrayNo;							// ���ԃ{�b�N�X�����Ă��邩�H
	u16				BoxCursorPos;						// �{�b�N�X��ł̃J�[�\���̈ʒu
	POKEMON_PASO_PARAM	*deposit_ppp;					// ��U�a����w��ɂȂ����|�P�����̃|�C���^
	int				SearchResult;						// �����̌��ʕԂ��Ă�����
	int				TouchTrainerPos;					// �������ʂ̒N���^�b�`������
	MYSTATUS		*partnerStatus;						// �����f���悤�ɂł���������MYSTATUS;
	EVOLUTION_POKEMON_INFO EvoPokeInfo;


	Dpw_Tr_Data		UploadPokemonData;					// ���M�f�[�^
	Dpw_Tr_Data		DownloadPokemonData[SEARCH_POKE_MAX];// �������ʃf�[�^
	Dpw_Tr_Data		ExchangePokemonData;				// �������ʃf�[�^
	Dpw_Tr_PokemonDataSimple Post;
	Dpw_Tr_PokemonSearchData Want;
	Dpw_Tr_PokemonSearchData Search;
	Dpw_Tr_PokemonSearchData SearchBackup;				// ���������͂ł��Ȃ��悤�ɂ��邽�߂�



	// �`��܂��̃��[�N�i���BMP�p�̕��������j
	WORDSET			*WordSet;								// ���b�Z�[�W�W�J�p���[�N�}�l�[�W���[
	MSGDATA_MANAGER *MsgManager;							// ���O���̓��b�Z�[�W�f�[�^�}�l�[�W���[
	MSGDATA_MANAGER *MonsNameManager;						// �|�P���������b�Z�[�W�f�[�^�}�l�[�W���[
	MSGDATA_MANAGER *LobbyMsgManager;						// ���O���̓��b�Z�[�W�f�[�^�}�l�[�W���[
	MSGDATA_MANAGER *SystemMsgManager;						// Wifi�V�X�e�����b�Z�[�W�f�[�^
	STRBUF			*BoxTrayNameString;						// �{�b�N�X�g���C��
	STRBUF			*EndString;								// ������u��߂�v
	STRBUF			*TalkString;							// ��b���b�Z�[�W�p
	STRBUF			*TitleString;							// �^�C�g�����b�Z�[�W�p
	STRBUF			*InfoString[10];						// �^�C�g�����b�Z�[�W�p
	STRBUF			*ErrorString;
	int				MsgIndex;								// �I�����o�p���[�N


	// �`�����̃��[�N�i���OAM)
	CLACT_SET_PTR 			clactSet;								// �Z���A�N�^�[�Z�b�g
	CLACT_U_EASYRENDER_DATA	renddata;								// �ȈՃ����_�[�f�[�^
	CLACT_U_RES_MANAGER_PTR	resMan[CLACT_RESOURCE_NUM];				// ���\�[�X�}�l�[�W��
	CLACT_U_RES_OBJ_PTR 	resObjTbl[RES_NUM][CLACT_RESOURCE_NUM];// ���\�[�X�I�u�W�F�e�[�u��
	CLACT_HEADER			clActHeader_main;							// �Z���A�N�^�[�w�b�_�[
	CLACT_HEADER			clActHeader_sub;							// �Z���A�N�^�[�w�b�_�[
	CLACT_HEADER			clActHeader_friend;						// �Z���A�N�^�[�w�b�_�[
	CLACT_WORK_PTR			CursorActWork;							// �Z���A�N�^�[���[�N�|�C���^�z��
	CLACT_WORK_PTR			FingerActWork;							// �Z���A�N�^�[���[�N�|�C���^�z��
	CLACT_WORK_PTR			PokeIconActWork[BOX_POKE_NUM];			// �|�P�����A�C�R���A�N�^�[
	CLACT_WORK_PTR			ItemIconActWork[BOX_POKE_NUM];			// �A�C�e���A�C�R���A�N�^�[
	CLACT_WORK_PTR			CBallActWork[6];						// �J�X�^���{�[���A�C�R���A�N�^�[
	CLACT_WORK_PTR			PokemonActWork;				// �Z���A�N�^�[���[�N�|�C���^�z��
	CLACT_WORK_PTR			SubActWork[SUB_OBJ_NUM];				// �T�u��ʗp�n�a�i�|�C���^
	CLACT_WORK_PTR			BoxArrowActWork[2];						// �{�b�N�X���̉��ɂ�����

	// BMPWIN�`�����
	GF_BGL_BMPWIN			MsgWin;									// ��b�E�C���h�E
	GF_BGL_BMPWIN			NumberWin;								// ��߂�
	GF_BGL_BMPWIN			TitleWin;								// �u���R�[�h�R�[�i�[�@�ڂ��イ���イ�I�v�Ȃ�
	GF_BGL_BMPWIN			SubWin;									// �u���R�[�h�R�[�i�[�@�ڂ��イ���イ�I�v�Ȃ�
	GF_BGL_BMPWIN			MenuWin[3];								// ���j���[�pBMPWIN
	GF_BGL_BMPWIN			InfoWin[11];	
	GF_BGL_BMPWIN			TalkWin;


	BMP_MENULIST_DATA		*BmpMenuList;
	BMPMENU_WORK			*YesNoMenuWork;
	BMPMENU_WORK 			*BmpMenuWork;
	BMPLIST_WORK 			*BmpListWork;
	void*					timeWaitWork;							// ��b�E�C���h�E���A�C�R�����[�N

	int						wait;



	// ��ʖ��Ɏg�����Ƃ����郏�[�N
	DEPOSIT_WORK			*dw;


	// worldtrade_upload.c�p���[�N
	u16						saveNextSeq1st;						// �Z�[�u�̑O���I�����ɔ�ԃV�[�P���X
	u16						saveNextSeq2nd;						// �Z�[�u�̌㔼�I�����ɔ�ԃV�[�P���X

	// worldtrade_sublcd.c�p���[�N
	TCB_PTR					demotask;							// ��l���f���p�^�X�N�|�C���^
	u16						demo_end;							// �f���I���t���O
	u16						SubLcdTouchOK;						// �l��OBJ���łĂ��Ă���G���悤�ɂȂ�t���O
	void*					FieldObjCharaBuf;					// �l��OBJ�L�����t�@�C���f�[�^
	NNSG2dCharacterData*	FieldObjCharaData;					// �l��OBJ�L�����f�[�^�̎��|�C���^				
	void*					FieldObjPalBuf;						// �l��OBJ�p���b�g�@�C���f�[�^
	NNSG2dPaletteData*		FieldObjPalData;					// �l��OBJ�p���b�g�t�@�C���f�[�^

	// worldtrade_demo.c�p���[�N
	POKEMON_PARAM *demoPokePara;


	// worldtrade_box.c�p���[�N
	BOX_RESEARCH			*boxWork;
	u16						boxPokeNum;								// �{�b�N�X�ɂ���|�P�����̑���
	u16						boxSearchFlag;							// �{�b�N�X�̑������擾���邽�߂̃t���O
	u32	sub_out_flg;		// ����ʃt�F�[�h�R���g���[��
	
	void *boxicon;
	void (*vfunc)(void *);

	// worldtrade_deposit.c worldtrade_search.c�Ō��p
	SELECT_LIST_POS			selectListPos;
	
#ifdef PM_DEBUG
	int 					frame;									//
	int						framenum[9][2];							//
#endif
};


//============================================================================================
// SE�p��`
//============================================================================================
#define WORLDTRADE_MOVE_SE		(SEQ_SE_DP_SELECT)
#define WORLDTRADE_DECIDE_SE	(SEQ_SE_DP_SELECT)


//============================================================================================
//	�f�o�b�O�p
//============================================================================================
//#define	GTS_FADE_OSP	// �t�F�[�h�ꏊ�\���p��`


//============================================================================================
// extern�錾
//============================================================================================
// worldtrade.c
extern void WorldTrade_MakeCLACT(CLACT_ADD *add, WORLDTRADE_WORK *wk, CLACT_HEADER *header, int param);
extern BMPMENU_WORK *WorldTrade_BmpWinYesNoMake( GF_BGL_INI *bgl, int y, int yesno_bmp_cgx );
extern void WorldTrade_SetNextSeq( WORLDTRADE_WORK *wk, int to_seq, int next_seq );
extern void WorldTrade_SetNextProcess( WORLDTRADE_WORK *wk, int next_process );
extern void WorldTrade_ActPos( CLACT_WORK_PTR act, int x, int y );
extern  int WorldTrade_WifiLinkLevel( void );
extern void WorldTrade_BmpWinPrint( GF_BGL_BMPWIN *win, MSGDATA_MANAGER *msgman, int msgno, u16 dat );
extern void WorldTrade_SysPrint( GF_BGL_BMPWIN *win, STRBUF *strbuf, int x, int y, int flag, GF_PRINTCOLOR color );
extern void WorldTrade_TalkPrint( GF_BGL_BMPWIN *win, STRBUF *strbuf, int x, int y, int flag, GF_PRINTCOLOR color );

extern void WorldTrade_WifiIconAdd( WORLDTRADE_WORK *wk );
extern void Enter_MessagePrint( WORLDTRADE_WORK *wk, MSGDATA_MANAGER *msgman, int msgno, int wait, u16 dat );
extern void WorldTrade_SubProcessChange( WORLDTRADE_WORK *wk, int subprccess, int mode );
extern WINTYPE WorldTrade_GetMesWinType( WORLDTRADE_WORK *wk );
extern int WorldTrade_GetTalkSpeed( WORLDTRADE_WORK *wk );
extern void FreeFieldObjData( WORLDTRADE_WORK *wk );
extern void WorldTrade_BoxPokeNumGetStart( WORLDTRADE_WORK *wk );
extern void WorldTrade_SubProcessUpdate( WORLDTRADE_WORK *wk );
extern void WorldTrade_TimeIconAdd( WORLDTRADE_WORK *wk );
extern void WorldTrade_TimeIconDel( WORLDTRADE_WORK *wk );


// worldtrade_sublcd.c
extern void WorldTrade_HeroDemo( WORLDTRADE_WORK *wk, int sex );
extern int  WorldTrade_SubLcdObjHitCheck( int max );
void WorldTrade_SubLcdMatchObjAppear( WORLDTRADE_WORK *wk, int num, int flag );
extern void WorldTrade_SubLcdMatchObjHide( WORLDTRADE_WORK *wk );
extern void WorldTrade_SubLcdActorAdd( WORLDTRADE_WORK *wk, int sex );
extern void WorldTrade_ReturnHeroDemo( WORLDTRADE_WORK *wk, int sex );


// worldtrade_enter.c
extern int  WorldTrade_Enter_End( WORLDTRADE_WORK *wk, int seq);
extern int  WorldTrade_Enter_Main(WORLDTRADE_WORK *wk, int seq);
extern int  WorldTrade_Enter_Init(WORLDTRADE_WORK *wk, int seq);

// worldtrade_title.c
extern int  WorldTrade_Title_End( WORLDTRADE_WORK *wk, int seq);
extern int  WorldTrade_Title_Main(WORLDTRADE_WORK *wk, int seq);
extern int  WorldTrade_Title_Init(WORLDTRADE_WORK *wk, int seq);
extern void WorldTrade_SubLcdBgGraphicSet( WORLDTRADE_WORK *wk );



// worldtrade_mypoke.c
extern int  WorldTrade_MyPoke_Init(WORLDTRADE_WORK *wk, int seq);
extern int  WorldTrade_MyPoke_Main(WORLDTRADE_WORK *wk, int seq);
extern int  WorldTrade_MyPoke_End(WORLDTRADE_WORK *wk, int seq);
extern void WorldTrade_PokeInfoPrint( 	MSGDATA_MANAGER *MsgManager,
							MSGDATA_MANAGER *MonsNameManager, 	
							WORDSET *WordSet, 
							GF_BGL_BMPWIN win[], 	
							POKEMON_PASO_PARAM *ppp,
							Dpw_Tr_PokemonDataSimple *post );
extern void WorldTrade_PokeInfoPrint2( MSGDATA_MANAGER *MsgManager, GF_BGL_BMPWIN win[], STRCODE *name );
extern void WorldTrade_TransPokeGraphic( POKEMON_PARAM *pp );


// worldtrade_partner.c
extern int WorldTrade_Partner_Init(WORLDTRADE_WORK *wk, int seq);
extern int WorldTrade_Partner_Main(WORLDTRADE_WORK *wk, int seq);
extern int WorldTrade_Partner_End(WORLDTRADE_WORK *wk, int seq);

// worldtrade_search.c
extern int WorldTrade_Search_Init(WORLDTRADE_WORK *wk, int seq);
extern int WorldTrade_Search_Main(WORLDTRADE_WORK *wk, int seq);
extern int WorldTrade_Search_End(WORLDTRADE_WORK *wk, int seq);

// worldtrade_box.c
extern int WorldTrade_Box_Init(WORLDTRADE_WORK *wk, int seq);
extern int WorldTrade_Box_Main(WORLDTRADE_WORK *wk, int seq);
extern int WorldTrade_Box_End(WORLDTRADE_WORK *wk, int seq);
extern POKEMON_PASO_PARAM *WorldTrade_GetPokePtr( POKEPARTY *party, BOX_DATA *box,  int  tray, int pos );
extern int WorldTrade_GetPPorPPP( int tray );
extern BOOL WorldTrade_PokemonMailCheck( POKEMON_PARAM *pp );

// workdtrade_deposit.c
extern int WorldTrade_Deposit_Init(WORLDTRADE_WORK *wk, int seq);
extern int WorldTrade_Deposit_Main(WORLDTRADE_WORK *wk, int seq);
extern int WorldTrade_Deposit_End(WORLDTRADE_WORK *wk, int seq);
extern void WodrldTrade_PokeWantPrint( MSGDATA_MANAGER *MsgManager, MSGDATA_MANAGER *MonsNameManager,
		WORDSET *WordSet, GF_BGL_BMPWIN win[], int monsno, int sex, int level );
extern void WodrldTrade_MyPokeWantPrint( MSGDATA_MANAGER *MsgManager, MSGDATA_MANAGER *MonsNameManager,
	WORDSET *WordSet, GF_BGL_BMPWIN win[], int monsno, int sex, int level );

extern BMPLIST_WORK *WorldTrade_WordheadBmpListMake( WORLDTRADE_WORK *wk, BMP_MENULIST_DATA **menulist, 
													GF_BGL_BMPWIN *win, MSGDATA_MANAGER *MsgManager );
extern BMPLIST_WORK *WorldTrade_PokeNameListMake( WORLDTRADE_WORK *wk, BMP_MENULIST_DATA **menulist, GF_BGL_BMPWIN *win, 
			MSGDATA_MANAGER *MsgManager, MSGDATA_MANAGER *MonsNameManager, DEPOSIT_WORK* dw, ZUKAN_WORK *zukan);
extern BMPLIST_WORK *WorldTrade_SexSelectListMake( BMP_MENULIST_DATA **menulist, GF_BGL_BMPWIN *win, MSGDATA_MANAGER *MsgManager  );
extern BMPLIST_WORK *WorldTrade_LevelListMake(BMP_MENULIST_DATA **menulist, GF_BGL_BMPWIN *win, MSGDATA_MANAGER *MsgManager  );
extern const int WorldTrade_WantLevelTable[];
extern const int WorldTrade_SexStringTable[];
extern u16* WorldTrade_ZukanSortDataGet( int heap, int idx, int* p_arry_num );

void WorldTrade_PokeNamePrint( GF_BGL_BMPWIN *win, MSGDATA_MANAGER *nameman, int monsno, int flag, int y, GF_PRINTCOLOR color );
void WorldTrade_SexPrint( GF_BGL_BMPWIN *win, MSGDATA_MANAGER *msgman, int sex, int flag, int y, int printflag, GF_PRINTCOLOR color );
void WorldTrade_WantLevelPrint( GF_BGL_BMPWIN *win, MSGDATA_MANAGER *msgman, int level, int flag, int y, GF_PRINTCOLOR color );
extern void WorldTrade_PostPokemonBaseDataMake( Dpw_Tr_Data *dtd, WORLDTRADE_WORK *wk );
extern int WorldTrade_SexSelectionCheck( Dpw_Tr_PokemonSearchData *dtp, int sex_selection );
extern int WorldTrade_LevelTermGet( int min, int max );
extern void WorldTrade_LevelMinMaxSet( Dpw_Tr_PokemonSearchData *dtps, int index );
extern u8 *WorldTrade_SinouZukanDataGet( int heap  );
extern u32 WorldTrade_BmpListMain( BMPLIST_WORK * lw, u16 *posbackup );
extern void WorldTrade_SelectListPosInit( SELECT_LIST_POS *slp);
extern void WorldTrade_SelectNameListBackup( SELECT_LIST_POS *slp, int head, int list, int pos );


// workdtrade_uploade.c
extern int WorldTrade_Upload_Init(WORLDTRADE_WORK *wk, int seq);
extern int WorldTrade_Upload_Main(WORLDTRADE_WORK *wk, int seq);
extern int WorldTrade_Upload_End(WORLDTRADE_WORK *wk, int seq);

// workdtrade_status.c
extern int WorldTrade_Status_Init(WORLDTRADE_WORK *wk, int seq);
extern int WorldTrade_Status_Main(WORLDTRADE_WORK *wk, int seq);
extern int WorldTrade_Status_End(WORLDTRADE_WORK *wk, int seq);

// workdtrade_demo.c
extern int WorldTrade_Demo_Init(WORLDTRADE_WORK *wk, int seq);
extern int WorldTrade_Demo_Main(WORLDTRADE_WORK *wk, int seq);
extern int WorldTrade_Demo_End(WORLDTRADE_WORK *wk, int seq);


#endif
