//============================================================================================
/**
 * @file	wbtower_enter.c
 * @bfief	WIFI�o�g���^���[��������
 * @author	Akito Mori
 * @date	06.05.15
 */
//============================================================================================
#ifdef PM_DEBUG
// �L���ɂ���ƃ��O�C�����ɕK��FATALERROR���N����
//#define DEBUG_FATAL_TEST
#endif


#include "common.h"
#include <dwc.h>
#include "libdpw/dpw_bt.h"
#include "system/procsys.h"
#include "system/arc_tool.h"
#include "system/arc_util.h"
#include "system/clact_tool.h"
#include "system/msgdata_util.h"
#include "system/wordset.h"
#include "msgdata/msg.naix"
#include "system/wipe.h"
#include "system/fontproc.h"
#include "system/lib_pack.h"
#include "system/lib_pack.h"
#include "system/fontoam.h"
#include "system/window.h"
#include "gflib/touchpanel.h"
#include "system/bmp_menu.h"
#include "system/snd_tool.h"
#include "gflib/strbuf_family.h"
#include "savedata/savedata.h"
#include "savedata/wifilist.h"
#include "savedata/zukanwork.h"
#include "gflib/strbuf.h"
#include "communication/comm_state.h"
#include "communication/comm_def.h"

#include "application/wbtower.h"
#include "wbtower_local.h"
#include "field/b_tower_wifi.h"
#include "wifi/dwc_rap.h"

#include "msgdata/msg_wifi_lobby.h"
#include "msgdata/msg_wifi_bt.h"
#include "msgdata/msg_wifi_system.h"



#include "../wifi_worldtrade/worldtrade.naix"			// �O���t�B�b�N�A�[�J�C�u��`
#include "../wifi_p2pmatch/wifip2pmatch.naix"			// �O���t�B�b�N�A�[�J�C�u��`



//============================================================================================
//	�v���g�^�C�v�錾
//============================================================================================
/*** �֐��v���g�^�C�v ***/
static void BgInit( GF_BGL_INI * ini );
static void BgExit( GF_BGL_INI * ini );
static void BgGraphicSet( WBTOWER_WORK * wk );
static void BmpWinInit( WBTOWER_WORK *wk );
static void BmpWinDelete( WBTOWER_WORK *wk );
static void InitWork( WBTOWER_WORK *wk );
static void FreeWork( WBTOWER_WORK *wk );
static int Enter_Start( WBTOWER_WORK *wk);
static int Enter_ConnectYesNoSelect( WBTOWER_WORK *wk );
static int Enter_EndYesNoSelect( WBTOWER_WORK *wk );
static int Enter_InternetConnect( WBTOWER_WORK *wk );
static int Enter_InternetConnectWait( WBTOWER_WORK *wk );
static int Enter_WifiConnectionLogin( WBTOWER_WORK *wk );
static int Enter_WifiConnectionLoginWait( WBTOWER_WORK *wk );
static int Enter_DpwBtInit( WBTOWER_WORK *wk );
static int Enter_ServerStart( WBTOWER_WORK *wk );
static int Enter_Main( WBTOWER_WORK *wk);
static int Enter_End( WBTOWER_WORK *wk);
static int Enter_YesNo( WBTOWER_WORK *wk);
static int Enter_YesNoSelect( WBTOWER_WORK *wk);
static int Enter_MessageWait( WBTOWER_WORK *wk );
static int Enter_MessageWaitYesNoStart(WBTOWER_WORK *wk);
static int Enter_MessageWait1Second( WBTOWER_WORK *wk );
static int Enter_ServerServiceError( WBTOWER_WORK *wk );
static int Enter_ServerServiceEnd( WBTOWER_WORK *wk );
static int Enter_ServerResult( WBTOWER_WORK *wk );
static int Enter_EndStart( WBTOWER_WORK *wk );
static int Enter_ServerDownload( WBTOWER_WORK *wk );
static int Enter_ServerTradeCheckResult( WBTOWER_WORK *wk );
static int Enter_ServerTradeCheck( WBTOWER_WORK *wk );
static int Enter_DwcErrorPrint( WBTOWER_WORK *wk );
static int Enter_ErrorPadWait( WBTOWER_WORK *wk );


static void MessagePrint( WBTOWER_WORK *wk, MSGDATA_MANAGER *msgman, int msgno, int wait, u16 dat );
static void WordSetMessagePrint( WBTOWER_WORK *wk, MSGDATA_MANAGER *msgman, int msgno, int wait, u16 dat );
static void NumStringBmpWrite( GF_BGL_BMPWIN *win, STRBUF *numstr, int num, int keta );
static void _systemMessagePrint( WBTOWER_WORK *wk, int msgno );
static void errorDisp(WBTOWER_WORK* wk, int type, int code);


static int Enter_ServerGetRank( WBTOWER_WORK *wk );
static int Enter_ServerGetRankResult( WBTOWER_WORK *wk );

static int Enter_ServerRoomSelectMes( WBTOWER_WORK *wk );
static int Enter_ServerRoomSelect( WBTOWER_WORK *wk );
static int Enter_ServerRoomSelectWait( WBTOWER_WORK *wk );
static int Enter_ChallengeEndStart( WBTOWER_WORK *wk ) ;
static int Enter_ChallengeEndYesNoSelect( WBTOWER_WORK *wk );
static void SelectArrowOnOff( WBTOWER_WORK *wk, int no, int flag );
static void SelectArrowPos( CLACT_WORK_PTR act, int x, int y );
static int Enter_RoomDataDownloadMessage( WBTOWER_WORK *wk );
static int Enter_RoomDataDownLoad( WBTOWER_WORK *wk );
static int Enter_RoomDataDownLoadResult( WBTOWER_WORK *wk );
static int Enter_RoomDataDownloadSuccess( WBTOWER_WORK *wk );
static int Enter_TowerScoreUploadMessage( WBTOWER_WORK *wk );
static int Enter_TowerScoreUpload( WBTOWER_WORK *wk );
static int Enter_TowerScoreUploadResult( WBTOWER_WORK *wk );
static int Enter_TowerScoreUploadSuccess( WBTOWER_WORK *wk );
static int Enter_SelectRankMessage( WBTOWER_WORK *wk );
static int Enter_SelectRank( WBTOWER_WORK *wk );
static int Enter_SelectRankResult( WBTOWER_WORK *wk );
static int Enter_LeaderDataEndStart( WBTOWER_WORK *wk );
static int Enter_LeaderDataEndYesNoSelect( WBTOWER_WORK *wk );
static int Enter_RoomDataNotMessage( WBTOWER_WORK *wk );
static int Enter_LeaderDataDownLoadMessage( WBTOWER_WORK*wk );


static int Enter_SelectLeaderRoomMes( WBTOWER_WORK *wk );
static int Enter_SelectLeaderRoom( WBTOWER_WORK *wk );
static int Enter_SelectLeaderRoomWait( WBTOWER_WORK *wk );
static int Enter_LeaderDataDownLoad( WBTOWER_WORK *wk );
static int Enter_LeaderDataDownLoadResult( WBTOWER_WORK *wk );
static int Enter_LeaderDataDownloadSuccess( WBTOWER_WORK *wk );
static int Enter_SuccessEnd( WBTOWER_WORK *wk );
static int Enter_BtowerSave( WBTOWER_WORK *wk );
static int Enter_BtowerSaveWait( WBTOWER_WORK *wk );

static int Enter_ForceEndMessage( WBTOWER_WORK *wk );
static int Enter_ForceEnd( WBTOWER_WORK *wk );
static int Enter_ForceEndStart( WBTOWER_WORK *wk ) ;

static int printCommonFunc( GF_BGL_BMPWIN *win, STRBUF *strbuf, int x, int flag, GF_PRINTCOLOR color, int font );

static void TimeIconAdd( WBTOWER_WORK *wk );
static void TimeIconDel( WBTOWER_WORK *wk );


enum{
	ENTER_START=0,
	ENTER_CONNECT_YESNO_SELECT,
	ENTER_INTERNET_CONNECT,
	ENTER_INTERNET_CONNECT_WAIT,
	ENTER_WIFI_CONNECTION_LOGIN,
	ENTER_WIFI_CONNECTION_LOGIN_WAIT,
	ENTER_DPWBT_INIT,
	ENTER_SERVER_START,
	ENTER_SERVER_RESULT,

	// �_�E�����[�h
	ENTER_SERVER_GET_RANK,
	ENTER_SERVER_GET_RANK_RESULT,

	ENTER_SERVER_ROOM_SELECT_MES,
	ENTER_SERVER_ROOM_SELECT,
	ENTER_SERVER_ROOM_SELECT_WAIT,
	ENTER_ROOM_DATA_DOWNLOAD_MES,
    ENTER_ROOM_DATA_DOWNLOAD,
    ENTER_ROOM_DATA_DOWNLOAD_RESULT,
    ENTER_ROOM_DATA_DOWNLOAD_SUCCESS,

	ENTER_ROOM_DATA_NOT_MES,

	ENTER_CHALLENGE_END_START,
	ENTER_CHALLENGE_END_YESNO_SELECT,

	ENTER_LEADER_DATA_END_START,
    ENTER_LEADER_DATA_END_YESNO_SELECT,

	// �A�b�v���[�h
	ENTER_TOWER_SCORE_UPLOAD_MES,
    ENTER_TOWER_SCORE_UPLOAD,
    ENTER_TOWER_SCORE_UPLOAD_RESULT,
    ENTER_TOWER_SCORE_UPLOAD_SUCCESS,
	
	// ���[�_�[�f�[�^�_�E�����[�h
	ENTER_SELECT_RANK_MES,
	ENTER_SELECT_RANK,
	ENTER_SELECT_RANK_RESULT,
	ENTER_SELECT_LEADER_ROOM_MES,
	ENTER_SELECT_LEADER_ROOM,
	ENTER_SELECT_LEADER_ROOM_WAIT,

	ENTER_LEADER_DATA_DOWNLOAD_MES,
	ENTER_LEADER_DATA_DOWNLOAD,
	ENTER_LEADER_DATA_DOWNLOAD_RESULT,
    ENTER_LEADER_DATA_DOWNLOAD_SUCCESS,

	// �Z�[�u�V�[�P���X
	ENTER_BTOWER_SAVE,
	ENTER_BTOWER_SAVE_WAIT,

	// �I���V�[�P���X
	ENTER_FORCE_END_START,
	ENTER_FORCE_END,
	ENTER_FORCE_END_MES,

	ENTER_MAIN,
	ENTER_SUCCESS_END,
	ENTER_END,
	ENTER_MES_WAIT,
	ENTER_MES_WAIT_YESNO_START, 
	ENTER_MES_WAIT_1_SECOND,
	ENTER_YESNO_SELECT,
	ENTER_END_START,
	ENTER_END_YESNO_SELECT,

	ENTER_SERVER_SERVICE_ERROR,
	ENTER_SERVER_SERVICE_END,

	ENTER_DWC_ERROR_PRINT,
	ENTER_ERROR_PAD_WAIT,
};

static int (*Functable[])( WBTOWER_WORK *wk ) = {
	Enter_Start,				// ENTER_START=0,
	Enter_ConnectYesNoSelect,	// ENTER_CONNECT_YESNO_SELECT,
	Enter_InternetConnect,		// ENTER_INTERNET_CONNECT
	Enter_InternetConnectWait,	// ENTER_INTERNET_CONNECT_WAIT
	Enter_WifiConnectionLogin,
	Enter_WifiConnectionLoginWait,
	Enter_DpwBtInit,			// ENTER_DPWTR_INIT
	Enter_ServerStart,			// ENTER_SERVER_START
	Enter_ServerResult,			// ENTER_SERVER_RESULT
	Enter_ServerGetRank,		// ENTER_SERVER_GET_RANK
	Enter_ServerGetRankResult,	// ENTER_SERVER_GET_RANK_RESULT

	// �_�E�����[�h
	Enter_ServerRoomSelectMes,
    Enter_ServerRoomSelect,
    Enter_ServerRoomSelectWait,

	Enter_RoomDataDownloadMessage,
    Enter_RoomDataDownLoad,
    Enter_RoomDataDownLoadResult,
    Enter_RoomDataDownloadSuccess,

	Enter_RoomDataNotMessage,	// ENTER_ROOM_DATA_NOT_MES,


    Enter_ChallengeEndStart,
    Enter_ChallengeEndYesNoSelect,

	Enter_LeaderDataEndStart,		// ENTER_LEADER_DATA_END_START,
    Enter_LeaderDataEndYesNoSelect,	// ENTER_LEADER_DATA_END_YESNO_SELECT,

	// �A�b�v���[�h
	Enter_TowerScoreUploadMessage,
    Enter_TowerScoreUpload,
    Enter_TowerScoreUploadResult,
    Enter_TowerScoreUploadSuccess,

	// ���[�_�[�f�[�^�_�E�����[�h
	Enter_SelectRankMessage,
	Enter_SelectRank,
	Enter_SelectRankResult,
	Enter_SelectLeaderRoomMes,
    Enter_SelectLeaderRoom,
    Enter_SelectLeaderRoomWait,

	Enter_LeaderDataDownLoadMessage,	// ENTER_LEADER_DATA_DOWNLOAD_MES
    Enter_LeaderDataDownLoad,
    Enter_LeaderDataDownLoadResult,
    Enter_LeaderDataDownloadSuccess,

	// �Z�[�u�V�[�P���X
	Enter_BtowerSave,
	Enter_BtowerSaveWait,

	// �I���V�[�P���X
	Enter_ForceEndStart,        // ENTER_FORCE_END_START
	Enter_ForceEnd,             // ENTER_FORCE_END,
	Enter_ForceEndMessage,		// ENTER_FORCE_END_MES,
	
	
	Enter_Main,            	 	// ENTER_MAIN,
	Enter_SuccessEnd,			
	Enter_End,             	 	// ENTER_END,
	Enter_MessageWait,     	 	// ENTER_MES_WAIT
	Enter_MessageWaitYesNoStart,// ENTER_MES_WAIT_YESNO_START
	Enter_MessageWait1Second,	// ENTER_MES_WAIT_1_SECOND
	Enter_YesNoSelect,			// ENTER_YESNO_SELECT
	Enter_EndStart,				// ENTER_END_START
	Enter_EndYesNoSelect,		// ENTER_END_YESNO_SELECT
	
	Enter_ServerServiceError,	// ENTER_SERVER_SERVICE_ERROR
	Enter_ServerServiceEnd,		// ENTER_SERVER_SERVICE_END

	Enter_DwcErrorPrint,
	Enter_ErrorPadWait,
};


//======================================x======================================================
//	�v���Z�X�֐�
//============================================================================================

//==============================================================================
/**
 * $brief   ���E�����������ʏ�����
 *
 * @param   wk		
 * @param   seq		
 *
 * @retval  int		
 */
//==============================================================================
int WBTower_EnterInit(WBTOWER_WORK *wk, int seq)
{
	// ���[�N������
	InitWork( wk );
	
	// ���C�v�t�F�[�h�J�n
	WIPE_SYS_Start( WIPE_PATTERN_WMS, WIPE_TYPE_FADEIN, WIPE_TYPE_FADEIN, WIPE_FADE_BLACK, 8, 1, HEAPID_WIFI_BATTLETOWER );

	// BG�ݒ�
	BgInit( wk->bgl );

	// BG�O���t�B�b�N�]��
	BgGraphicSet( wk );

	// BMPWIN�m��
	BmpWinInit( wk );


	// BG�ʕ\��ON
	GF_Disp_GX_VisibleControl(  GX_PLANEMASK_BG0, VISIBLE_ON );
	GF_Disp_GX_VisibleControl(  GX_PLANEMASK_BG1, VISIBLE_ON );
	GF_Disp_GXS_VisibleControl( GX_PLANEMASK_BG0, VISIBLE_ON );
	GF_Disp_GXS_VisibleControl( GX_PLANEMASK_BG1, VISIBLE_ON );

    // �ʐM�G���[�Ǘ��̂��߂ɒʐM���[�`����ON
    CommStateWifiDPWStart( wk->param->savedata );
	// Wifi�ʐM�A�C�R��
	WBTower_WifiIconAdd( wk );

	// ���݂̃����N���擾
	wk->Rank    = TowerScoreData_SetWifiRank(wk->param->btowerscore, BTWR_DATA_get);
	wk->NowRank = wk->Rank;
	wk->NowRoom = 1;

	// ���ԃA�C�R���t���O�^�X�N���[�N��������
	wk->timeWaitWork = NULL;

	if(!DWC_CheckInet()){
		if(wk->param->connect){
			MessagePrint( wk, wk->LobbyMsgManager, msg_wifilobby_002, 1, 0x0f0f );
			WBTower_SetNextSeq( wk, ENTER_MES_WAIT, ENTER_INTERNET_CONNECT );
			TimeIconAdd( wk );
		}else{
			wk->subprocess_seq = ENTER_START;
		}
	}else{
		wk->subprocess_seq = ENTER_END_START;
	}
	return SEQ_FADEIN;
}
//==============================================================================
/**
 * $brief   ���E�����������ʃ��C��
 *
 * @param   wk		
 * @param   seq		
 *
 * @retval  int		
 */
//==============================================================================
int WBTower_EnterMain(WBTOWER_WORK *wk, int seq)
{
	int ret;

	// �ʐM��Ԃ��m�F���ăA�C�R���̕\����ς���
    WirelessIconEasy_SetLevel(WBTower_WifiLinkLevel());

	// �V�[�P���X�J�ڂŎ��s
	ret = (*Functable[wk->subprocess_seq])( wk );

	return ret;
}


//==============================================================================
/**
 * $brief   ���E�����������ʏI��
 *
 * @param   wk		
 * @param   seq		
 *
 * @retval  int		
 */
//==============================================================================
int WBTower_EnterEnd(WBTOWER_WORK *wk, int seq)
{
	FreeWork( wk );
	
	BmpWinDelete( wk );
	
	BgExit( wk->bgl );

	// ���̃T�u�v���Z�X��ݒ肷��
	wk->sub_process = wk->sub_nextprocess;
	
	// ���̃T�u�v���Z�X��������̂܂܂������琢�E�����I��
	if(wk->sub_process==WBTOWER_ENTER){
		return SEQ_OUT;
	}
	// �����ݒ肳��Ă����珉������
	return SEQ_INIT;
}


//--------------------------------------------------------------------------------------------
/**
 * BG�ݒ�
 *
 * @param	ini		BGL�f�[�^
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void BgInit( GF_BGL_INI * ini )
{

	// ���C����ʃe�L�X�g��
	{	
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xf800, GX_BG_CHARBASE_0x00000, GX_BG_EXTPLTT_01,
			0, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( ini, GF_BGL_FRAME0_M, &TextBgCntDat, GF_BGL_MODE_TEXT );
		GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG0, VISIBLE_OFF );
		GF_BGL_ScrClear( ini, GF_BGL_FRAME0_M );
	}

	// ���C����ʔw�i��
	{	
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xf000, GX_BG_CHARBASE_0x08000, GX_BG_EXTPLTT_01,
			1, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( ini, GF_BGL_FRAME1_M, &TextBgCntDat, GF_BGL_MODE_TEXT );
		GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG1, VISIBLE_OFF );
	}

	// �T�u��ʕ�����0
	{	
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xf000, GX_BG_CHARBASE_0x10000, GX_BG_EXTPLTT_01,
			0, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( ini, GF_BGL_FRAME0_S, &TextBgCntDat, GF_BGL_MODE_TEXT );
		GF_Disp_GXS_VisibleControl( GX_PLANEMASK_BG0, VISIBLE_OFF );
		GF_BGL_ScrClear( ini, GF_BGL_FRAME0_S );

	}


	// �T�u��ʔw�i
	{	
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xd800, GX_BG_CHARBASE_0x08000, GX_BG_EXTPLTT_01,
			2, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( ini, GF_BGL_FRAME1_S, &TextBgCntDat, GF_BGL_MODE_TEXT );
		GF_Disp_GXS_VisibleControl( GX_PLANEMASK_BG1, VISIBLE_OFF );
//		GF_BGL_ScrClear( ini, GF_BGL_FRAME2_S );
	}


	GF_BGL_ClearCharSet( GF_BGL_FRAME0_M, 32, 0, HEAPID_WIFI_BATTLETOWER );
	GF_BGL_ClearCharSet( GF_BGL_FRAME0_S, 32, 0, HEAPID_WIFI_BATTLETOWER );

}

//--------------------------------------------------------------------------------------------
/**
 * BG���
 *
 * @param	ini		BGL�f�[�^
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void BgExit( GF_BGL_INI * ini )
{

	GF_BGL_BGControlExit( ini, GF_BGL_FRAME1_S );
	GF_BGL_BGControlExit( ini, GF_BGL_FRAME0_S );
	GF_BGL_BGControlExit( ini, GF_BGL_FRAME1_M );
	GF_BGL_BGControlExit( ini, GF_BGL_FRAME0_M );

}


//--------------------------------------------------------------------------------------------
/**
 * �O���t�B�b�N�f�[�^�Z�b�g
 *
 * @param	wk		�|�P�������X�g��ʂ̃��[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void BgGraphicSet( WBTOWER_WORK * wk )
{
	GF_BGL_INI *bgl = wk->bgl;

	// �㉺��ʂa�f�p���b�g�]��
    ArcUtil_PalSet(    ARC_WIFIP2PMATCH_GRA, NARC_wifip2pmatch_conect_NCLR, PALTYPE_MAIN_BG, 0, 0,  HEAPID_WIFI_BATTLETOWER);
    ArcUtil_PalSet(    ARC_WIFIP2PMATCH_GRA, NARC_wifip2pmatch_conect_NCLR, PALTYPE_SUB_BG,  0, 0,  HEAPID_WIFI_BATTLETOWER);
	
	// ��b�t�H���g�p���b�g�]��
	TalkFontPaletteLoad( PALTYPE_MAIN_BG, WBTOWER_TALKFONT_PAL*0x20, HEAPID_WIFI_BATTLETOWER );
	TalkFontPaletteLoad( PALTYPE_SUB_BG,  WBTOWER_TALKFONT_PAL*0x20, HEAPID_WIFI_BATTLETOWER );

	// ��b�E�C���h�E�O���t�B�b�N�]��
	TalkWinGraphicSet(	bgl, GF_BGL_FRAME0_M, WBTOWER_MESFRAME_CHR, 
						WBTOWER_MESFRAME_PAL, CONFIG_GetWindowType(wk->param->config), HEAPID_WIFI_BATTLETOWER );


	MenuWinGraphicSet(	bgl, GF_BGL_FRAME0_M, WBTOWER_MENUFRAME_CHR,
						WBTOWER_MENUFRAME_PAL, 0, HEAPID_WIFI_BATTLETOWER );




	// ���C�����BG1�L�����]��
	ArcUtil_BgCharSet( ARC_WIFIP2PMATCH_GRA, NARC_wifip2pmatch_conect_NCGR, bgl, GF_BGL_FRAME1_M, 0, 18*6*0x20, 0, HEAPID_WIFI_BATTLETOWER);

	// ���C�����BG1�X�N���[���]��
	ArcUtil_ScrnSet(   ARC_WIFIP2PMATCH_GRA, NARC_wifip2pmatch_conect_01_NSCR, bgl, GF_BGL_FRAME1_M, 0, 32*24*2, 0, HEAPID_WIFI_BATTLETOWER);



	// �T�u���BG1�L�����]��
	ArcUtil_BgCharSet( ARC_WIFIP2PMATCH_GRA, NARC_wifip2pmatch_conect_s_NCGR, bgl, GF_BGL_FRAME1_S, 0, 18*6*0x20, 0, HEAPID_WIFI_BATTLETOWER);

	// �T�u���BG1�X�N���[���]��
	ArcUtil_ScrnSet(   ARC_WIFIP2PMATCH_GRA, NARC_wifip2pmatch_conect_s_NSCR, bgl, GF_BGL_FRAME1_S, 0, 32*24*2, 0f, HEAPID_WIFI_BATTLETOWER);

	GF_BGL_BackGroundColorSet( GF_BGL_FRAME0_M, 0 );
	GF_BGL_BackGroundColorSet( GF_BGL_FRAME0_S, 0 );

}


#define SUB_TEXT_X		(  4 )
#define SUB_TEXT_Y		(  4 )
#define SUB_TEXT_SX		( 23 )
#define SUB_TEXT_SY		( 16 )

#define SUB_NUMBER_X	( 26 )
#define SUB_NUMBER_Y	( 14 )
#define SUB_NUMBER_SX	(  4 )
#define SUB_NUMBER_SY	(  2 )

#define SUB_RANK_X		( 26 )
#define SUB_RANK_Y		( 14 )
#define SUB_RANK_SX		(  4 )
#define SUB_RANK_SY		(  2 )



#define TALK_MESSAGE_OFFSET	 ( WBTOWER_MENUFRAME_CHR + MENU_WIN_CGX_SIZ )
#define NUMBER_WIN_OFFSET	 ( TALK_MESSAGE_OFFSET + TALK_WIN_SX*TALK_WIN_SY )
#define RANK_WIN_OFFSET		 ( NUMBER_WIN_OFFSET   + SUB_NUMBER_SX*SUB_NUMBER_SY )
#define ERROR_MESSAGE_OFFSET ( RANK_WIN_OFFSET     + SUB_RANK_SX*SUB_RANK_SY )
#define TITLE_WIN_OFFSET	 ( ERROR_MESSAGE_OFFSET + SUB_TEXT_SX*SUB_TEXT_SY )
#define YESNO_OFFSET 		 ( TITLE_WIN_OFFSET + TITLE_TEXT_SX*TITLE_TEXT_SY )
//#define TITLE_MESSAGE_OFFSET ( TALK_MESSAGE_OFFSET + SUB_TEXT_SX*SUB_TEXT_SY )
//------------------------------------------------------------------
/**
 * BMPWIN�����i�����p�l���Ƀt�H���g�`��j
 *
 * @param   wk		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void BmpWinInit( WBTOWER_WORK *wk )
{
	// ---------- ���C����� ------------------

	// BG0��BMPWIN(�G���[����)�E�C���h�E�m�ہE�`��
	GF_BGL_BmpWinAdd(wk->bgl, &wk->SubWin, GF_BGL_FRAME0_M,
	SUB_TEXT_X, SUB_TEXT_Y, SUB_TEXT_SX, SUB_TEXT_SY, WBTOWER_TALKFONT_PAL,  ERROR_MESSAGE_OFFSET );

	GF_BGL_BmpWinDataFill( &wk->SubWin, 0x0000 );

	// BG0��BMPWIN(���[���ԍ��w��)�E�C���h�E�m��
	GF_BGL_BmpWinAdd(wk->bgl, &wk->NumberWin, GF_BGL_FRAME0_M,
	SUB_NUMBER_X, SUB_NUMBER_Y, SUB_NUMBER_SX, SUB_NUMBER_SY, WBTOWER_TALKFONT_PAL,  NUMBER_WIN_OFFSET );

	GF_BGL_BmpWinDataFill( &wk->NumberWin, 0x0f0f );


	// BG0��BMPWIN(�����N�ԍ��w��)�E�C���h�E�m�ہE�`��
	GF_BGL_BmpWinAdd(wk->bgl, &wk->RankWin, GF_BGL_FRAME0_M,
	SUB_RANK_X, SUB_RANK_Y, SUB_RANK_SX, SUB_RANK_SY, WBTOWER_TALKFONT_PAL,  RANK_WIN_OFFSET );

	GF_BGL_BmpWinDataFill( &wk->RankWin, 0x0f0f );


	// WIFI�o�g���^���[�ɂ�����
	GF_BGL_BmpWinAdd(wk->bgl, &wk->TitleWin, GF_BGL_FRAME1_M,
	TITLE_TEXT_X, TITLE_TEXT_Y, TITLE_TEXT_SX, TITLE_TEXT_SY, 0,  TITLE_WIN_OFFSET );

	GF_BGL_BmpWinDataFill( &wk->TitleWin, 0x0606 );
	WBTower_TalkPrint( &wk->TitleWin, wk->TitleString, 0, 1, 1, GF_PRINTCOLOR_MAKE(1,4,6) );


	// ----------- �T�u��ʖ��O�\��BMP�m�� ------------------
	// BG0��BMP�i��b�E�C���h�E�j�m��
	GF_BGL_BmpWinAdd(wk->bgl, &wk->MsgWin, GF_BGL_FRAME0_M,
		TALK_WIN_X, 
		TALK_WIN_Y, 
		TALK_WIN_SX, 
		TALK_WIN_SY, WBTOWER_TALKFONT_PAL,  TALK_MESSAGE_OFFSET );
	GF_BGL_BmpWinDataFill( &wk->MsgWin, 0x0f0f );

}	

//------------------------------------------------------------------
/**
 * $brief   �m�ۂ���BMPWIN�����
 *
 * @param   wk		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void BmpWinDelete( WBTOWER_WORK *wk )
{
	
	GF_BGL_BmpWinDel( &wk->MsgWin );
	GF_BGL_BmpWinDel( &wk->TitleWin );
	GF_BGL_BmpWinDel( &wk->RankWin );
	GF_BGL_BmpWinDel( &wk->NumberWin );
	GF_BGL_BmpWinDel( &wk->SubWin );


}

//------------------------------------------------------------------
/**
 * ���E�������[�N������
 *
 * @param   wk		WBTOWER_WORK*
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void InitWork( WBTOWER_WORK *wk )
{

	// ������o�b�t�@�쐬
	wk->TalkString   = STRBUF_Create( TALK_MESSAGE_BUF_NUM, HEAPID_WIFI_BATTLETOWER );
	wk->RoomString   = STRBUF_Create( NUMBER_BUF_NUM, HEAPID_WIFI_BATTLETOWER );
	wk->RankString   = STRBUF_Create( RANK_BUF_NUM, HEAPID_WIFI_BATTLETOWER );
	wk->TitleString  = MSGMAN_AllocString( wk->MsgManager, msg_wifi_bt_title_001 );
	wk->ErrorString  = STRBUF_Create( DWC_ERROR_BUF_NUM,    HEAPID_WIFI_BATTLETOWER );
	

	// ���R�[�h��������ڂ��イ���I������擾
//	MSGMAN_GetString(  wk->MsgManager, msg_wifilobby_002, wk->TitleString );

}


//------------------------------------------------------------------
/**
 * $brief   ���[�N���
 *
 * @param   wk		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void FreeWork( WBTOWER_WORK *wk )
{

	STRBUF_Delete( wk->ErrorString ); 
	STRBUF_Delete( wk->TitleString ); 
	STRBUF_Delete( wk->RankString ); 
	STRBUF_Delete( wk->RoomString ); 
	STRBUF_Delete( wk->TalkString ); 

}




//--------------------------------------------------------------------
//--------------------------------------------------------------------
//--------------------------------------------------------------------
//--------------------------------------------------------------------
//--------------------------------------------------------------------
//--------------------------------------------------------------------
//--------------------------------------------------------------------
//------------------------------------------------------------------
/**
 * $brief   �T�u�v���Z�X�V�[�P���X�X�^�[�g����
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int Enter_Start( WBTOWER_WORK *wk)
{
	// WIFI�R�l�N�V�����ɐڑ����܂����H
	MessagePrint( wk, wk->SystemMsgManager, dwc_message_0002, 1, 0x0f0f );
	WBTower_SetNextSeq( wk, ENTER_MES_WAIT_YESNO_START, ENTER_CONNECT_YESNO_SELECT );

	OS_TPrintf("Enter �J�n\n");

	return SEQ_MAIN;
}



//------------------------------------------------------------------
/**
 * $brief   �ڑ����J�n���܂����H
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int Enter_ConnectYesNoSelect( WBTOWER_WORK *wk )
{
	int ret = BmpYesNoSelectMain( wk->YesNoMenuWork, HEAPID_WIFI_BATTLETOWER );

	if(ret!=BMPMENU_NULL){
		if(ret==BMPMENU_CANCEL){
			// �ڑ����I�����܂����H
//			MessagePrint( wk, wk->MsgManager, msg_gtc_01_008, 1, 0, 0x0f0f );
//			WBTower_SetNextSeq( wk, ENTER_MES_WAIT_YESNO_START, ENTER_END_YESNO_SELECT );
//			wk->subprocess_seq = ENTER_END_START;

			// �I��
		    CommStateWifiDPWEnd();
			WBTower_SubProcessChange( wk, WBTOWER_ENTER, 0 );
			wk->subprocess_seq  = ENTER_END;

		}else{
			// WIFI���������J�n
			MessagePrint( wk, wk->LobbyMsgManager, msg_wifilobby_002, 1, 0x0f0f );
			WBTower_SetNextSeq( wk, ENTER_MES_WAIT, ENTER_INTERNET_CONNECT );
			TimeIconAdd( wk );
		}
	}

	return SEQ_MAIN;
	
}

//------------------------------------------------------------------
/**
 * $brief   �ڑ����I�����܂����H
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int Enter_EndStart( WBTOWER_WORK *wk ) 
{
	// �ڑ����I�����܂����H
	MessagePrint( wk, wk->LobbyMsgManager, msg_wifilobby_009, 1, 0x0f0f );
	WBTower_SetNextSeq( wk, ENTER_MES_WAIT_YESNO_START, ENTER_END_YESNO_SELECT );

	return SEQ_MAIN;
}

//------------------------------------------------------------------
/**
 * $brief   �ڑ����I�����܂����H�iWIFI�o�g���^���[��ڑ������ɏI���j
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int Enter_EndYesNoSelect( WBTOWER_WORK *wk )
{
	int ret = BmpYesNoSelectMain( wk->YesNoMenuWork, HEAPID_WIFI_BATTLETOWER );

	if(ret!=BMPMENU_NULL){
		if(ret==BMPMENU_CANCEL){
			if(!DWC_CheckInet()){		
				// �ڑ����J�n���܂����H
				wk->subprocess_seq  = ENTER_START;
			}else{
				// ���ɐڑ��ς݂Ȃ�^�C�g����
//				WBTower_SubProcessChange( wk, WBTOWER_ENTER, 0 );
//				wk->subprocess_seq  = ENTER_END;
				wk->subprocess_seq  = ENTER_FORCE_END_START;
			}
		}else{
			// WIFI���������I��
			if(!DWC_CheckInet()){		
				WBTower_SubProcessChange( wk, WBTOWER_ENTER, 0 );
				wk->subprocess_seq  = ENTER_END;
			}else{
				wk->subprocess_seq  = ENTER_FORCE_END_START;
			}
			// �L�����Z���I����ʒm����
			wk->param->result = WIFI_BTOWER_RESULT_CANCEL;

		}
	}

	return SEQ_MAIN;
	
}

//------------------------------------------------------------------
/**
 * $brief   �C���^�[�l�b�g�ڑ��J�n
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int Enter_InternetConnect( WBTOWER_WORK *wk )
{
	DWC_InitInetEx(&wk->stConnCtrl,COMM_DMA_NO,COMM_POWERMODE,COMM_SSL_PRIORITY);
    DWC_SetAuthServer(DWC_CONNECTINET_AUTH_RELEASE);
	DWC_ConnectInetAsync();
	
	wk->subprocess_seq = ENTER_INTERNET_CONNECT_WAIT;
	OS_TPrintf("InternetConnet Start\n");

	return SEQ_MAIN;
}

//------------------------------------------------------------------
/**
 * $brief   �l�b�g�ڑ��҂�
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int Enter_InternetConnectWait( WBTOWER_WORK *wk )
{
	DWC_ProcessInet();

	if (DWC_CheckInet())
	{
		int result = DWC_GetInetStatus();
#ifdef DEBUG_FATAL_TEST
		result = DWC_CONNECTINET_STATE_FATAL_ERROR;
#endif
		switch (result)
		{
		case DWC_CONNECTINET_STATE_ERROR:
			{
				// �G���[�\��
				DWCError err;
				int errcode;
				err = DWC_GetLastError(&errcode);

				OS_TPrintf("   Error occurred %d %d.\n", err, errcode);
				wk->ErrorRet  = err;
				wk->ErrorCode = errcode;
			}
			DWC_ClearError();
			DWC_CleanupInet();

			TimeIconDel( wk );
			wk->subprocess_seq = ENTER_DWC_ERROR_PRINT;
			break;
		case DWC_CONNECTINET_STATE_FATAL_ERROR:
			{
				// �G���[�\��
				DWCError err;
				int errcode;
				err = DWC_GetLastError(&errcode);

				OS_TPrintf("   Fatal Error occurred %d %d.\n", err, errcode);
				TimeIconDel( wk );
				wk->subprocess_seq = ENTER_SERVER_SERVICE_ERROR;
				wk->ConnectErrorNo = DPW_BT_ERROR_SERVER_TIMEOUT;
			}
			break;

		case DWC_CONNECTINET_STATE_CONNECTED:
	        {	// �ڑ����\������B�X�܂̏ꍇ�͓X�܏����\������B
				DWCApInfo apinfo;
	
				DWC_GetApInfo(&apinfo);
	
	            OS_TPrintf("   Connected to AP type %d.\n", apinfo.aptype);

	            if (apinfo.aptype == DWC_APINFO_TYPE_SHOP)
	            {
					OS_TPrintf("<Shop AP Data>\n");
	                OS_TPrintf("area code: %d.\n", apinfo.area);
	                OS_TPrintf("spotinfo : %s.\n", apinfo.spotinfo);
	            }
	        }
	        // �R�l�N�g�����H
//			wk->subprocess_seq = ENTER_DPWBT_INIT;
			wk->subprocess_seq = ENTER_WIFI_CONNECTION_LOGIN;
			break;
		}

		// ���ԃA�C�R������

	}
	
	return SEQ_MAIN;
}


//------------------------------------------------------------------
/**
 * @brief   GameSpy�T�[�o�[���O�C���J�n
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int Enter_WifiConnectionLogin( WBTOWER_WORK *wk )
{
	if(DWC_NASLoginAsync()){
		wk->subprocess_seq = ENTER_WIFI_CONNECTION_LOGIN_WAIT;
		OS_Printf("GameSpy�T�[�o�[���O�C���J�n\n");
	}

	return SEQ_MAIN;
}
//------------------------------------------------------------------
/**
 * @brief   GameSpy�T�[�o�[���O�C�������҂�
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int Enter_WifiConnectionLoginWait( WBTOWER_WORK *wk )
{
	switch(DWC_NASLoginProcess()){
	case DWC_NASLOGIN_STATE_SUCCESS:
		OS_Printf("GameSpy�T�[�o�[���O�C������\n");
		wk->subprocess_seq = ENTER_DPWBT_INIT;
		break;
	case DWC_NASLOGIN_STATE_ERROR:
	case DWC_NASLOGIN_STATE_CANCELED:
		TimeIconDel( wk );
		OS_Printf("GameSpy�T�[�o�[���O�C�����s\n");
		{
			int errCode;
			DWCErrorType errType;
			DWCError dwcError;
			dwcError = DWC_GetLastErrorEx( &errCode, &errType );
			wk->ErrorRet  = dwcError;
			wk->ErrorCode = errCode;

			DWC_ClearError();
			DWC_CleanupInet();

			switch(errType){
			case DWC_ETYPE_LIGHT:
			case DWC_ETYPE_SHOW_ERROR:
				wk->subprocess_seq = ENTER_DWC_ERROR_PRINT;
				break;
			case DWC_ETYPE_SHUTDOWN_GHTTP:
				DWC_ShutdownGHTTP();
				wk->subprocess_seq = ENTER_DWC_ERROR_PRINT;
				break;
			case DWC_ETYPE_DISCONNECT:
				wk->subprocess_seq = ENTER_DWC_ERROR_PRINT;
				break;
			case DWC_ETYPE_FATAL:
				// �����ӂ��Ƃ΂�
				CommFatalErrorFunc_NoNumber();
				break;
			}

			// 20000�ԑ���L���b�`������errType�����ł��낤�ƃ��Z�b�g�G���[��
			if(errCode<-20000 && errCode >=-29999){
//				CommSetErrorReset(COMM_ERROR_RESET_TITLE);
				OS_Printf("dwcError = %d  errCode = %d, errType = %d\n", dwcError, errCode, errType);
				wk->subprocess_seq = ENTER_DWC_ERROR_PRINT;
			}
		}
		break;
	}
	
	
	return SEQ_MAIN;
}


//------------------------------------------------------------------
/**
 * $brief   ���E�����T�[�o�[�ڑ����C�u����������
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int Enter_DpwBtInit( WBTOWER_WORK *wk )
{
	s32 profileId;

	// ����FriendKey�̓v���C���[���n�߂Ď擾�������̂��H
	profileId = SYSTEMDATA_GetDpwInfo( wk->param->systemdata );
	if( profileId==0 ){
		OS_TPrintf("����擾profileId�Ȃ̂�DpwInfo�Ƃ��ēo�^���� %08x \n", wk->param->profileId);

		// ����擾FriendKey�Ȃ̂ŁADpwId�Ƃ��ĕۑ�����
		SYSTEMDATA_SetDpwInfo( wk->param->systemdata, wk->param->profileId );
	}


	// �����ȃf�[�^���擾
	profileId = SYSTEMDATA_GetDpwInfo( wk->param->systemdata );
	OS_Printf("Dpw�T�[�o�[���O�C����� profileId=%08x\n", profileId );

	// Wifi�o�g���^���[�ڑ�������
	Dpw_Bt_Init( profileId, DWC_CreateFriendKey( wk->param->MyUserData ));

	OS_TPrintf("Dpw Battle Tower ������\n");

	wk->subprocess_seq = ENTER_SERVER_START;
	
	return SEQ_MAIN;
}

//------------------------------------------------------------------
/**
 * $brief   ���E�������C�u�����ڑ��󋵎擾�J�n
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int Enter_ServerStart( WBTOWER_WORK *wk )
{
	Dpw_Bt_GetServerStateAsync();

	OS_TPrintf("Dpw Battle �T�[�o�[��Ԏ擾�J�n\n");

	// �T�[�o�[��Ԋm�F�҂���
	wk->subprocess_seq = ENTER_SERVER_RESULT;
//	WBTower_SetNextSeq( wk, ENTER_MES_WAIT, ENTER_MAIN );

	return SEQ_MAIN;
}

//------------------------------------------------------------------
/**
 * $brief   �T�[�o�[��Ԋm�F�҂�
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int Enter_ServerResult( WBTOWER_WORK *wk )
{
	if (Dpw_Bt_IsAsyncEnd()){
		s32 result = Dpw_Bt_GetAsyncResult();
		switch (result){
		case DPW_BT_STATUS_SERVER_OK:		// ����ɓ��삵�Ă���
			OS_TPrintf(" server is up!\n");
			TimeIconDel( wk );

			switch(wk->param->mode){
			// �_�E�����[�h
			case WIFI_BTOWER_MODE_DOWNLOAD:
				WBTower_SetNextSeq( wk, ENTER_SERVER_GET_RANK, ENTER_SERVER_ROOM_SELECT_MES );
				
				break;
			// �A�b�v���[�h
			case WIFI_BTOWER_MODE_UPLOAD:
				wk->subprocess_seq = ENTER_TOWER_SCORE_UPLOAD_MES;
				break;
			// ���[�_�[�f�[�^�_�E�����[�h
			case WIFI_BTOWER_MODE_LEADER:
				wk->subprocess_seq = ENTER_SELECT_RANK_MES;
				break;
			}

			break;
		case DPW_BT_STATUS_SERVER_STOP_SERVICE:	
			// �T�[�r�X��~��
			OS_TPrintf(" server stop service.\n");
			wk->ConnectErrorNo = result;
			wk->subprocess_seq = ENTER_SERVER_SERVICE_ERROR;
			TimeIconDel( wk );
			break;
		case DPW_BT_STATUS_SERVER_FULL:		
		case DPW_BT_ERROR_SERVER_FULL:		
			// �T�[�o�[�����t
			OS_TPrintf(" server full.\n");
			wk->ConnectErrorNo = result;
			wk->subprocess_seq = ENTER_SERVER_SERVICE_ERROR;
			TimeIconDel( wk );
			break;
			
  		case DPW_BT_ERROR_FAILURE:
  		case DPW_BT_ERROR_CANCEL:
			// �T�[�o�[�ƒʐM�ł��܂��񁨏I��
			OS_TPrintf(" upload error. %d \n", result);
			wk->ConnectErrorNo = result;
			wk->subprocess_seq = ENTER_SERVER_SERVICE_ERROR;
			TimeIconDel( wk );
			break;
		case DPW_BT_ERROR_SERVER_TIMEOUT:
  		case DPW_BT_ERROR_DISCONNECTED:
			// �T�[�o�[�ƒʐM�ł��܂��񁨏I��
			OS_TPrintf(" upload error. %d \n", result);
			wk->ConnectErrorNo = result;
			wk->subprocess_seq = ENTER_SERVER_SERVICE_ERROR;
			TimeIconDel( wk );
			break;
  		case DPW_BT_ERROR_FATAL:
			// �v���I�G���[�Ȃ̂œd���؂��ʂւӂ��Ƃ΂�
			CommFatalErrorFunc_NoNumber();
			break;

		
		}
		
	}
	return SEQ_MAIN;
}

//------------------------------------------------------------------
/**
 * @brief   �w��̃����N�̕��������擾����
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int Enter_ServerGetRank( WBTOWER_WORK *wk )
{
	// WIFI�o�g���^���[�����N�擾

	Dpw_Bt_GetRoomNumAsync ( wk->Rank );
	OS_Printf("GetRank = %d \n",wk->Rank);

	wk->subprocess_seq = ENTER_SERVER_GET_RANK_RESULT;
	TimeIconAdd( wk );

	return SEQ_MAIN;
}


//------------------------------------------------------------------
/**
 * @brief   �����|�P�����T�[�o�[�m�F�����҂�
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int Enter_ServerGetRankResult( WBTOWER_WORK *wk )
{
	// �T�[�o�[�₢���킹�I���҂�
	if (Dpw_Bt_IsAsyncEnd()){
		s32 result = Dpw_Bt_GetAsyncResult();
		switch (result){
		case DPW_BT_ERROR_SERVER_FULL :	
			OS_TPrintf(" no data on sever.\n");
			wk->ConnectErrorNo = result;
			wk->subprocess_seq = ENTER_SERVER_SERVICE_ERROR;
			break;
		// �^�C���A�E�g
		case DPW_BT_ERROR_SERVER_TIMEOUT :
			OS_TPrintf(" server timeout\n");
			wk->ConnectErrorNo = result;
			wk->subprocess_seq = ENTER_SERVER_SERVICE_ERROR;
			break;
		case DPW_BT_ERROR_ILLIGAL_REQUEST :
			OS_TPrintf(" server illigal request\n");
			wk->ConnectErrorNo = result;
			wk->subprocess_seq = ENTER_SERVER_SERVICE_ERROR;
			break;
		case DPW_BT_ERROR_DISCONNECTED :
			OS_TPrintf(" server disconnected \n");
			wk->ConnectErrorNo = result;
			wk->subprocess_seq = ENTER_SERVER_SERVICE_ERROR;
			break;
		// ���s�����̂Ń��g���C����
		case DPW_BT_ERROR_CANCEL :
		case DPW_BT_ERROR_FAILURE :
			OS_TPrintf(" failure ... retry\n");
			wk->ConnectErrorNo = result;
			wk->subprocess_seq = ENTER_SERVER_SERVICE_ERROR;
			break;
		case DPW_BT_ERROR_FATAL :
			// �v���I�G���[�Ȃ̂łӂ��Ƃ΂�
			OS_TPrintf(" server fatal erro  you must PowerOff\n");
			wk->ConnectErrorNo = result;
			wk->subprocess_seq = ENTER_SERVER_SERVICE_ERROR;
			CommFatalErrorFunc_NoNumber();
			break;

		// ���������擾�ł���
		default:
			// 0���Ă���́H
			if(result>0){
				wk->RoomNum = result;
				wk->subprocess_seq = wk->subprocess_nextseq;
			}
		}
		TimeIconDel( wk );
	}
	return SEQ_MAIN;
}
//------------------------------------------------------------------
/**
 * @brief   ���傤���񂵂����ւ��I��ł�������
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int Enter_ServerRoomSelectMes( WBTOWER_WORK *wk )
{
	MessagePrint( wk, wk->MsgManager, msg_wifi_bt_001, 1, 0x0f0f );
	WBTower_SetNextSeq( wk, ENTER_MES_WAIT, ENTER_SERVER_ROOM_SELECT );

	return SEQ_MAIN;
}

//------------------------------------------------------------------
/**
 * @brief   ���[���I���J�n
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int Enter_ServerRoomSelect( WBTOWER_WORK *wk )
{
//	MessagePrint( wk, wk->MsgManager, msg_wifi_bt_001, 1, 0x0f0f );
//	WBTower_SetNextSeq( wk, ENTER_MES_WAIT, ENTER_SERVER_ROOM_SELECT );
	
	BmpMenuWinWrite( &wk->NumberWin, WINDOW_TRANS_ON, WBTOWER_MENUFRAME_CHR, WBTOWER_MESFRAME_PAL );
	NumStringBmpWrite( &wk->NumberWin, wk->RoomString, wk->NowRoom, 3 );

	// ���\��
	SelectArrowOnOff( wk, 0, TRUE );
	GF_BGL_BmpWinOn( &wk->NumberWin );

	wk->subprocess_seq = ENTER_SERVER_ROOM_SELECT_WAIT;

	return SEQ_MAIN;
}

//------------------------------------------------------------------
/**
 * @brief   ���[���I��҂�
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int Enter_ServerRoomSelectWait( WBTOWER_WORK *wk )
{
	if(sys.repeat&PAD_KEY_UP){
		wk->NowRoom++;
		if(wk->NowRoom>wk->RoomNum){
			wk->NowRoom = 1;
		}
		NumStringBmpWrite( &wk->NumberWin, wk->RoomString, wk->NowRoom, 3 );
		Snd_SePlay(WBTOWER_MOVE_SE);
	}else if(sys.repeat&PAD_KEY_DOWN){
		wk->NowRoom--;
		if(wk->NowRoom<1){
			wk->NowRoom = wk->RoomNum;
		}
		NumStringBmpWrite( &wk->NumberWin, wk->RoomString, wk->NowRoom, 3 );
		Snd_SePlay(WBTOWER_MOVE_SE);
	}else if(sys.trg&PAD_BUTTON_DECIDE){
#ifdef PM_DEBUG
		if(sys.cont&PAD_BUTTON_L){
			wk->subprocess_seq = ENTER_ROOM_DATA_DOWNLOAD_MES;
		}else{
			RTCTime time;
			RTCDate date;

			// GameSpy�T�[�o�[���ԁE���t���擾
			DWC_GetDateTime( &date, &time);

			// �����͊��Ƀ_�E�����[�h���Ă��邩�H
			if(TowerWifiData_CheckRoomDataFlag( wk->param->wifitowerdata, wk->NowRank, wk->NowRoom, &date )){
				wk->subprocess_seq = ENTER_ROOM_DATA_NOT_MES;
			}else{
				wk->subprocess_seq = ENTER_ROOM_DATA_DOWNLOAD_MES;
			}
		}
#else
		{
			RTCTime time;
			RTCDate date;

			// GameSpy�T�[�o�[���ԁE���t���擾
			DWC_GetDateTime( &date, &time);

			// �����͊��Ƀ_�E�����[�h���Ă��邩�H
			if(TowerWifiData_CheckRoomDataFlag( wk->param->wifitowerdata, wk->NowRank, wk->NowRoom, &date )){
				wk->subprocess_seq = ENTER_ROOM_DATA_NOT_MES;
			}else{
				wk->subprocess_seq = ENTER_ROOM_DATA_DOWNLOAD_MES;
			}
		}
#endif
		SelectArrowOnOff( wk, 0, FALSE );
		Snd_SePlay(WBTOWER_DECIDE_SE);
	}else if(sys.trg&PAD_BUTTON_CANCEL){
		SelectArrowOnOff( wk, 0, FALSE );
		wk->subprocess_seq = ENTER_CHALLENGE_END_START;
		Snd_SePlay(WBTOWER_DECIDE_SE);
	}

	return SEQ_MAIN;
}



//------------------------------------------------------------------
/**
 * @brief   �u�����N�O�O�@���[���O�O�O���_�E�����[�h���ł��v���b�Z�[�W�\��
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int Enter_RoomDataDownloadMessage( WBTOWER_WORK *wk )
{
	WORDSET_RegisterNumber( wk->WordSet, 0, wk->NowRoom, 3, NUMBER_DISPTYPE_ZERO, NUMBER_CODETYPE_DEFAULT );
	WORDSET_RegisterNumber( wk->WordSet, 1, wk->NowRank, 2, NUMBER_DISPTYPE_ZERO, NUMBER_CODETYPE_DEFAULT );

	WordSetMessagePrint( wk, wk->MsgManager, msg_wifi_bt_002, 1, 0x0f0f );
	WBTower_SetNextSeq( wk, ENTER_MES_WAIT, ENTER_ROOM_DATA_DOWNLOAD );

	MI_CpuClearFast(&wk->roomBtData, sizeof(Dpw_Bt_Room) );

	return SEQ_MAIN;
	
}

//------------------------------------------------------------------
/**
 * @brief   ���̃o�g�����[���͂��̂�������܂ł��傤����ł��܂���
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int Enter_RoomDataNotMessage( WBTOWER_WORK *wk )
{

	WordSetMessagePrint( wk, wk->MsgManager, msg_wifi_bt_003, 1, 0x0f0f );
	WBTower_SetNextSeq( wk, ENTER_MES_WAIT, ENTER_SERVER_ROOM_SELECT_MES );

	return SEQ_MAIN;
	

}

//------------------------------------------------------------------
/**
 * @brief   �_�E�����[�h�J�n
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int Enter_RoomDataDownLoad( WBTOWER_WORK *wk )
{
	Dpw_Bt_DownloadRoomAsync( wk->Rank, wk->NowRoom, &wk->roomBtData );

	OS_Printf("GetRoom Rank = %d Room = %d RoomMax = %d\n",wk->Rank, wk->NowRoom, wk->RoomNum);

	TimeIconAdd( wk );
	
	wk->subprocess_seq = ENTER_ROOM_DATA_DOWNLOAD_RESULT;
	return SEQ_MAIN;

}


//------------------------------------------------------------------
/**
 * @brief   �����f�[�^�_�E�����[�h����
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int Enter_RoomDataDownLoadResult( WBTOWER_WORK *wk )
{
	
	if (Dpw_Bt_IsAsyncEnd()){
		s32 result = Dpw_Bt_GetAsyncResult();
		switch (result){
		// ����
		case 0:
			OS_TPrintf(" room data download success \n");

			// ���[���f�[�^���Z�[�u�f�[�^�ɔ��f
			TowerWifiData_SetPlayerData(wk->param->wifitowerdata, 
											(DPW_BT_PLAYER*)wk->roomBtData.player, wk->Rank, wk->NowRoom);
			OS_Printf("poke1 = %d\n",wk->roomBtData.player[0].pokemon[0].data[0]);
			OS_Printf("poke2 = %d\n",wk->roomBtData.player[0].pokemon[1].data[0]);
			OS_Printf("poke3 = %d\n",wk->roomBtData.player[0].pokemon[2].data[0]);
			OS_Printf("name[0] = %d\n",wk->roomBtData.player[0].playerName[0]);
			OS_Printf("result = %d\n",wk->roomBtData.player[0].result);


			WBTower_SetNextSeq( wk, ENTER_BTOWER_SAVE, ENTER_ROOM_DATA_DOWNLOAD_SUCCESS );

			// ����ς݃t���O����
			{
				RTCTime time;
				RTCDate date;

				// GameSpy�T�[�o�[���ԁE���t���擾
				DWC_GetDateTime( &date, &time);
				
				// ����ς݃t���O���Ă�
				TowerWifiData_SetRoomDataFlag( wk->param->wifitowerdata, wk->NowRank, wk->NowRoom, &date );

			}
			break;
		case DPW_BT_ERROR_SERVER_FULL :	
			OS_TPrintf(" no data on sever.\n");
			wk->ConnectErrorNo = result;
			wk->subprocess_seq = ENTER_SERVER_SERVICE_ERROR;
			TimeIconDel(wk);
			break;
		// �^�C���A�E�g
		case DPW_BT_ERROR_SERVER_TIMEOUT :
			OS_TPrintf(" server timeout\n");
			wk->ConnectErrorNo = result;
			wk->subprocess_seq = ENTER_SERVER_SERVICE_ERROR;
			TimeIconDel(wk);
			break;
		case DPW_BT_ERROR_ILLIGAL_REQUEST :
		case DPW_BT_ERROR_CANCEL :
			OS_TPrintf(" server illigal request\n");
			wk->ConnectErrorNo = result;
			wk->subprocess_seq = ENTER_SERVER_GET_RANK;
			TimeIconDel(wk);
			break;
		case DPW_BT_ERROR_DISCONNECTED :
			OS_TPrintf(" server disconnected \n");
			wk->ConnectErrorNo = result;
			wk->subprocess_seq = ENTER_SERVER_SERVICE_ERROR;
			TimeIconDel(wk);
			break;
		case DPW_BT_ERROR_FAILURE :
			// �A�N�Z�X���s
			OS_TPrintf(" failure ... retry\n");
			wk->ConnectErrorNo = result;
			wk->subprocess_seq = ENTER_SERVER_SERVICE_ERROR;
			TimeIconDel(wk);
			break;
		case DPW_BT_ERROR_FATAL :
			// �v���I�G���[�Ȃ̂łӂ��Ƃ΂�
			OS_TPrintf(" server fatal erro  you must PowerOff\n");
			wk->ConnectErrorNo = result;
			wk->subprocess_seq = ENTER_SERVER_SERVICE_ERROR;
			TimeIconDel(wk);
			CommFatalErrorFunc_NoNumber();
			break;

		}
	}

	return SEQ_MAIN;

}


//------------------------------------------------------------------
/**
 * @brief   �����f�[�^�_�E�����[�h����
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int Enter_RoomDataDownloadSuccess( WBTOWER_WORK *wk )
{
	MessagePrint( wk, wk->MsgManager, msg_wifi_bt_004, 1, 0x0f0f );
	WBTower_SetNextSeq( wk, ENTER_MES_WAIT, ENTER_SUCCESS_END );

	TimeIconDel( wk );
	wk->param->result = WIFI_BTOWER_RESULT_SUCCESS;

	return SEQ_MAIN;
	
}



//------------------------------------------------------------------
/**
 * @brief   �u�����������A�b�v���[�h���イ�v���b�Z�[�W�\��
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int Enter_TowerScoreUploadMessage( WBTOWER_WORK *wk )
{
	MessagePrint( wk, wk->MsgManager, msg_wifi_bt_008, 1, 0x0f0f );
	WBTower_SetNextSeq( wk, ENTER_MES_WAIT, ENTER_TOWER_SCORE_UPLOAD );

	TimeIconAdd( wk );

	return SEQ_MAIN;
	
}



//------------------------------------------------------------------
/**
 * @brief   �A�b�v���[�h�J�n
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int Enter_TowerScoreUpload( WBTOWER_WORK *wk )
{
	BTOWER_ROOMID roomId;

	// ���������擾
	int win = TowerScoreData_GetWifiWinNum(wk->param->btowerscore);

	// ���킵�������̃����N�ƃ��[���i���o�[���f�[�^����擾
	TowerWifiData_GetPlayerDataRoomID(wk->param->wifitowerdata, &roomId);

	// �o�g���^���[�̃A�b�v���[�h�f�[�^���쐬
	BtlTowerData_MakeUpdatePlayerData(wk->param->savedata,BTWR_SCORE_POKE_WIFI, (DPW_BT_PLAYER*)&wk->BtPlayer);
	
	OS_Printf("Upload Rank = %d Room = %d win = %d \n",roomId.rank, roomId.no, win );


	Dpw_Bt_UploadPlayerAsync  (  roomId.rank,  roomId.no,  win, &wk->BtPlayer  ) ;



	wk->subprocess_seq = ENTER_TOWER_SCORE_UPLOAD_RESULT;
	return SEQ_MAIN;

}


//------------------------------------------------------------------
/**
 * @brief   �����f�[�^�A�b�v���[�h����
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int Enter_TowerScoreUploadResult( WBTOWER_WORK *wk )
{
	
	if (Dpw_Bt_IsAsyncEnd()){
		s32 result = Dpw_Bt_GetAsyncResult();
		switch (result){
		// ����
		case 0:
			OS_TPrintf(" room data upload success \n");

			// �o�g���^���[���A�b�v���[�h�t���O���N���A
			TowerScoreData_SetFlags(wk->param->btowerscore,BTWR_SFLAG_WIFI_UPLOAD,BTWR_DATA_reset);

			WBTower_SetNextSeq( wk, ENTER_BTOWER_SAVE, ENTER_TOWER_SCORE_UPLOAD_SUCCESS );
			
			break;
		case DPW_BT_ERROR_SERVER_FULL :	
			OS_TPrintf(" no data on sever.\n");
			wk->ConnectErrorNo = result;
			wk->subprocess_seq = ENTER_SERVER_SERVICE_ERROR;
			TimeIconDel( wk );
			break;
		// �^�C���A�E�g
		case DPW_BT_ERROR_SERVER_TIMEOUT :
			OS_TPrintf(" server timeout\n");
			wk->ConnectErrorNo = result;
			wk->subprocess_seq = ENTER_SERVER_SERVICE_ERROR;
			TimeIconDel( wk );
			break;
		case DPW_BT_ERROR_ILLIGAL_REQUEST :
			OS_TPrintf(" server illigal request\n");
			wk->ConnectErrorNo = result;
			wk->subprocess_seq = ENTER_SERVER_SERVICE_ERROR;
			TimeIconDel( wk );
			break;
		case DPW_BT_ERROR_DISCONNECTED :
			OS_TPrintf(" server disconnected \n");
			wk->ConnectErrorNo = result;
			wk->subprocess_seq = ENTER_SERVER_SERVICE_ERROR;
			TimeIconDel( wk );
			break;
		// ���s�����̂Ń��g���C����
		case DPW_BT_ERROR_CANCEL :
		case DPW_BT_ERROR_FAILURE :
			OS_TPrintf(" failure ... retry\n");
			wk->ConnectErrorNo = result;
			wk->subprocess_seq = ENTER_SERVER_SERVICE_ERROR;
			TimeIconDel( wk );
			break;
		case DPW_BT_ERROR_FATAL :
			// �v���I�G���[�Ȃ̂łӂ��Ƃ΂�
			OS_TPrintf(" server fatal erro  you must PowerOff\n");
			wk->ConnectErrorNo = result;
			wk->subprocess_seq = ENTER_SERVER_SERVICE_ERROR;
			TimeIconDel( wk );
			CommFatalErrorFunc_NoNumber();
			break;

		}
	}

	return SEQ_MAIN;

}


//------------------------------------------------------------------
/**
 * @brief   �A�b�v���[�h����
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int Enter_TowerScoreUploadSuccess( WBTOWER_WORK *wk )
{
	MessagePrint( wk, wk->MsgManager, msg_wifi_bt_009, 1, 0x0f0f );
	WBTower_SetNextSeq( wk, ENTER_MES_WAIT, ENTER_SUCCESS_END );
	
	TimeIconDel( wk );
	wk->param->result = WIFI_BTOWER_RESULT_SUCCESS;

	return SEQ_MAIN;
	
}




//------------------------------------------------------------------
/**
 * @brief   �u�����N������Ă��������v���b�Z�[�W�\��
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int Enter_SelectRankMessage( WBTOWER_WORK *wk )
{
	MessagePrint( wk, wk->MsgManager, msg_wifi_bt_006, 1, 0x0f0f );
	WBTower_SetNextSeq( wk, ENTER_MES_WAIT, ENTER_SELECT_RANK );
	
	return SEQ_MAIN;
	
}
//------------------------------------------------------------------
/**
 * @brief   �����N�Z���N�g�J�n
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int Enter_SelectRank( WBTOWER_WORK *wk )
{
	wk->NowRank = 1;

	BmpMenuWinWrite( &wk->RankWin, WINDOW_TRANS_ON, WBTOWER_MENUFRAME_CHR, WBTOWER_MESFRAME_PAL );
	NumStringBmpWrite( &wk->RankWin, wk->RankString, wk->NowRank, 2 );

	// ���\��
	SelectArrowOnOff( wk, 1, TRUE );
	GF_BGL_BmpWinOn( &wk->RankWin );

	wk->subprocess_seq = ENTER_SELECT_RANK_RESULT;
	
	return SEQ_MAIN;
	
}


//------------------------------------------------------------------
/**
 * @brief   �����N�Z���N�g���ʑ҂�
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int Enter_SelectRankResult( WBTOWER_WORK *wk )
{
	if(sys.repeat&PAD_KEY_UP){
		wk->NowRank++;
		if(wk->NowRank>WIFITOWER_RANK_MAX){
			wk->NowRank = 1;
		}
		NumStringBmpWrite( &wk->RankWin, wk->RankString, wk->NowRank, 2 );
		Snd_SePlay(WBTOWER_MOVE_SE);
	}else if(sys.repeat&PAD_KEY_DOWN){
		wk->NowRank--;
		if(wk->NowRank<1){
			wk->NowRank = WIFITOWER_RANK_MAX;
		}
		NumStringBmpWrite( &wk->RankWin, wk->RankString, wk->NowRank, 2 );
		Snd_SePlay(WBTOWER_MOVE_SE);
	}else if(sys.trg&PAD_BUTTON_DECIDE){
		SelectArrowOnOff( wk, 0, FALSE );
//		wk->subprocess_seq = ENTER_ROOM_DATA_DOWNLOAD_MES;
		WBTower_SetNextSeq( wk, ENTER_SERVER_GET_RANK, ENTER_SELECT_LEADER_ROOM_MES );

		Snd_SePlay(WBTOWER_DECIDE_SE);
	}else if(sys.trg&PAD_BUTTON_CANCEL){
		SelectArrowOnOff( wk, 0, FALSE );
		wk->subprocess_seq = ENTER_LEADER_DATA_END_START;
		Snd_SePlay(WBTOWER_DECIDE_SE);
	}
	

	return SEQ_MAIN;
	
}



//------------------------------------------------------------------
/**
 * @brief   �u�o�g�����[���̂΂񂲂�������Ă��������v�\��
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int Enter_SelectLeaderRoomMes( WBTOWER_WORK *wk )
{
	MessagePrint( wk, wk->MsgManager, msg_wifi_bt_007, 1, 0x0f0f );
	WBTower_SetNextSeq( wk, ENTER_MES_WAIT, ENTER_SELECT_LEADER_ROOM );

	return SEQ_MAIN;
}

//------------------------------------------------------------------
/**
 * @brief   ���[�_�[�f�[�^�𗎂Ƃ����[���ԍ��I���J�n
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int Enter_SelectLeaderRoom( WBTOWER_WORK *wk )
{
	
	BmpMenuWinWrite( &wk->NumberWin, WINDOW_TRANS_ON, WBTOWER_MENUFRAME_CHR, WBTOWER_MESFRAME_PAL );
	NumStringBmpWrite( &wk->NumberWin, wk->RoomString, wk->NowRoom, 3 );

	// ���\��
	SelectArrowOnOff( wk, 0, TRUE );
	GF_BGL_BmpWinOn( &wk->NumberWin );

	wk->subprocess_seq = ENTER_SELECT_LEADER_ROOM_WAIT;

	return SEQ_MAIN;
}

//------------------------------------------------------------------
/**
 * @brief   ���[���I��҂�
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int Enter_SelectLeaderRoomWait( WBTOWER_WORK *wk )
{
	if(sys.repeat&PAD_KEY_UP){
		wk->NowRoom++;
		if(wk->NowRoom==wk->RoomNum+1){
			wk->NowRoom = 1;
		}
		NumStringBmpWrite( &wk->NumberWin, wk->RoomString, wk->NowRoom, 3 );
		Snd_SePlay(WBTOWER_MOVE_SE);
	}else if(sys.repeat&PAD_KEY_DOWN){
		wk->NowRoom--;
		if(wk->NowRoom<1){
			wk->NowRoom = wk->RoomNum;
		}
		NumStringBmpWrite( &wk->NumberWin, wk->RoomString, wk->NowRoom, 3 );
		Snd_SePlay(WBTOWER_MOVE_SE);
	}else if(sys.trg&PAD_BUTTON_DECIDE){
		SelectArrowOnOff( wk, 0, FALSE );
		wk->subprocess_seq = ENTER_LEADER_DATA_DOWNLOAD_MES;
		Snd_SePlay(WBTOWER_DECIDE_SE);
	}else if(sys.trg&PAD_BUTTON_CANCEL){
		SelectArrowOnOff( wk, 0, FALSE );
		wk->subprocess_seq = ENTER_SELECT_RANK_MES;
		Snd_SePlay(WBTOWER_DECIDE_SE);
	}
//	}else if(sys.trg&PAD_BUTTON_CANCEL){
//		SelectArrowOnOff( wk, 0, FALSE );
//		wk->subprocess_seq = ENTER_CHALLENGE_END_START;
//		Snd_SePlay(WBTOWER_DECIDE_SE);
//	}

	return SEQ_MAIN;
}

//------------------------------------------------------------------
/**
 * @brief   ���[�_�[�f�[�^�_�E�����[�h��
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int Enter_LeaderDataDownLoadMessage( WBTOWER_WORK*wk )
{
	WORDSET_RegisterNumber( wk->WordSet, 0, wk->NowRoom, 3, NUMBER_DISPTYPE_ZERO, NUMBER_CODETYPE_DEFAULT );
	WORDSET_RegisterNumber( wk->WordSet, 1, wk->NowRank, 2, NUMBER_DISPTYPE_ZERO, NUMBER_CODETYPE_DEFAULT );

	WordSetMessagePrint( wk, wk->MsgManager, msg_wifi_bt_002, 1, 0x0f0f );
	WBTower_SetNextSeq( wk, ENTER_MES_WAIT, ENTER_LEADER_DATA_DOWNLOAD );

	wk->subprocess_seq = ENTER_LEADER_DATA_DOWNLOAD;

	return SEQ_MAIN;
	
}

//------------------------------------------------------------------
/**
 * @brief   �_�E�����[�h�J�n
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int Enter_LeaderDataDownLoad( WBTOWER_WORK *wk )
{
	Dpw_Bt_DownloadRoomAsync( wk->NowRank, wk->NowRoom, &wk->roomBtData );

	OS_Printf("GetRoom Rank = %d Room = %d RoomMax = %d\n",wk->NowRank, wk->NowRoom, wk->RoomNum);

	wk->subprocess_seq = ENTER_LEADER_DATA_DOWNLOAD_RESULT;

	TimeIconAdd( wk );

	return SEQ_MAIN;

}


//------------------------------------------------------------------
/**
 * @brief   �����f�[�^�_�E�����[�h����
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int Enter_LeaderDataDownLoadResult( WBTOWER_WORK *wk )
{
	
	if (Dpw_Bt_IsAsyncEnd()){
		s32 result = Dpw_Bt_GetAsyncResult();
		switch (result){
		// ����
		case 0:
			OS_TPrintf(" room data download success \n");
			
			// ���[�_�[�f�[�^���Z�[�u�f�[�^�ɔ��f
			TowerWifiData_SetLeaderData(wk->param->wifitowerdata, 
											(DPW_BT_LEADER*)wk->roomBtData.leader, wk->NowRank, wk->NowRoom);

			WBTower_SetNextSeq( wk, ENTER_BTOWER_SAVE, ENTER_LEADER_DATA_DOWNLOAD_SUCCESS );
			break;
		case DPW_BT_ERROR_SERVER_FULL :	
			OS_TPrintf(" no data on sever.\n");
			wk->ConnectErrorNo = result;
			wk->subprocess_seq = ENTER_SERVER_SERVICE_ERROR;
			TimeIconDel( wk );
			break;
		// �^�C���A�E�g
		case DPW_BT_ERROR_SERVER_TIMEOUT :
			OS_TPrintf(" server timeout\n");
			wk->ConnectErrorNo = result;
			wk->subprocess_seq = ENTER_SERVER_SERVICE_ERROR;
			TimeIconDel( wk );
			break;
		case DPW_BT_ERROR_ILLIGAL_REQUEST :
			OS_TPrintf(" server illigal request\n");
			wk->ConnectErrorNo = result;
			wk->subprocess_seq = ENTER_SERVER_GET_RANK;
			TimeIconDel( wk );
			break;
		case DPW_BT_ERROR_DISCONNECTED :
			OS_TPrintf(" server disconnected \n");
			wk->ConnectErrorNo = result;
			wk->subprocess_seq = ENTER_SERVER_SERVICE_ERROR;
			TimeIconDel( wk );
			break;
		// ���s�����̂Ń��g���C����
		case DPW_BT_ERROR_FAILURE :
		case DPW_BT_ERROR_CANCEL :
			OS_TPrintf(" failure ... retry\n");
			wk->subprocess_seq = ENTER_SERVER_GET_RANK;
			wk->ConnectErrorNo = result;
			TimeIconDel( wk );
			break;
		case DPW_BT_ERROR_FATAL :
			// �v���I�G���[�Ȃ̂łӂ��Ƃ΂�
			OS_TPrintf(" server fatal erro  you must PowerOff\n");
			wk->ConnectErrorNo = result;
			wk->subprocess_seq = ENTER_SERVER_SERVICE_ERROR;
			TimeIconDel( wk );
			CommFatalErrorFunc_NoNumber();
			break;

		}
	}

	return SEQ_MAIN;

}


//------------------------------------------------------------------
/**
 * @brief   �����f�[�^�_�E�����[�h����
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int Enter_LeaderDataDownloadSuccess( WBTOWER_WORK *wk )
{
	MessagePrint( wk, wk->MsgManager, msg_wifi_bt_004, 1, 0x0f0f );
	WBTower_SetNextSeq( wk, ENTER_MES_WAIT, ENTER_SUCCESS_END );

	TimeIconDel( wk );

	// �����I����ʒm����
	wk->param->result = WIFI_BTOWER_RESULT_SUCCESS;

	return SEQ_MAIN;
	
}


//------------------------------------------------------------------
/**
 * @brief   ����I��
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int Enter_SuccessEnd( WBTOWER_WORK *wk )
{
	// WIFI���������I��
//    DWC_CleanupInet();
//	WBTower_SubProcessChange( wk, WBTOWER_ENTER, 0 );
//	wk->subprocess_seq = ENTER_END;
	wk->subprocess_seq = ENTER_FORCE_END_START;

	return SEQ_MAIN;
}


//------------------------------------------------------------------
/**
 * @brief   �Z�[�u�J�n
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int Enter_BtowerSave( WBTOWER_WORK *wk )
{
	// �Z�[�u������
	SaveData_DivSave_Init( wk->param->savedata,SVBLK_ID_MAX);
	OS_Printf("save init\n");

	wk->subprocess_seq = ENTER_BTOWER_SAVE_WAIT;

	return SEQ_MAIN;
}


//------------------------------------------------------------------
/**
 * @brief   �Z�[�u�I���҂�
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int Enter_BtowerSaveWait( WBTOWER_WORK *wk )
{
	if(SaveData_DivSave_Main(wk->param->savedata)==SAVE_RESULT_OK){
		OS_Printf("save end\n");

		wk->subprocess_seq = wk->subprocess_nextseq;

		// ���ԃA�C�R������
		TimeIconDel( wk );

	}
	
	return SEQ_MAIN;
}







//------------------------------------------------------------------
/**
 * $brief   �ڑ����I�����܂����H
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int Enter_ChallengeEndStart( WBTOWER_WORK *wk ) 
{
	// �ڑ����I�����܂����H
	MessagePrint( wk, wk->MsgManager, msg_wifi_bt_005, 1, 0x0f0f );
	WBTower_SetNextSeq( wk, ENTER_MES_WAIT_YESNO_START, ENTER_CHALLENGE_END_YESNO_SELECT );

	return SEQ_MAIN;
}

//------------------------------------------------------------------
/**
 * $brief   �ڑ����I�����܂����H�iWIFI�o�g���^���[���_�E�����[�h�����ɏI���j
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int Enter_ChallengeEndYesNoSelect( WBTOWER_WORK *wk )
{
	int ret = BmpYesNoSelectMain( wk->YesNoMenuWork, HEAPID_WIFI_BATTLETOWER );

	if(ret!=BMPMENU_NULL){
		if(ret==BMPMENU_CANCEL){	// Enter_ServerRoomSelectMes
			wk->subprocess_seq  = ENTER_SERVER_ROOM_SELECT_MES;
		}else{
			// WIFI���������I��
//		    DWC_CleanupInet();
//			WBTower_SubProcessChange( wk, WBTOWER_ENTER, 0 );
//			wk->subprocess_seq  = ENTER_END;
			wk->subprocess_seq  = ENTER_FORCE_END_START;

			// �L�����Z���I����ʒm����
			wk->param->result = WIFI_BTOWER_RESULT_CANCEL;

		}
	}

	return SEQ_MAIN;
	
}

//------------------------------------------------------------------
/**
 * $brief   �_�E�����[�h�𒆎~���܂����H
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int Enter_LeaderDataEndStart( WBTOWER_WORK *wk ) 
{
	// �u�_�E�����[�h�𒆎~���܂����H�v
	MessagePrint( wk, wk->MsgManager, msg_wifi_bt_010, 1, 0x0f0f );
	WBTower_SetNextSeq( wk, ENTER_MES_WAIT_YESNO_START, ENTER_LEADER_DATA_END_YESNO_SELECT );

	return SEQ_MAIN;
}

//------------------------------------------------------------------
/**
 * $brief   �ڑ����I�����܂����H�iWIFI�o�g���^���[���_�E�����[�h�����ɏI���j
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int Enter_LeaderDataEndYesNoSelect( WBTOWER_WORK *wk )
{
	int ret = BmpYesNoSelectMain( wk->YesNoMenuWork, HEAPID_WIFI_BATTLETOWER );

	if(ret!=BMPMENU_NULL){
		if(ret==BMPMENU_CANCEL){
			// �����N�Z���N�g�ɖ߂�
			wk->subprocess_seq  = ENTER_SELECT_RANK_MES;
		}else{
			// �I��
			wk->subprocess_seq  = ENTER_FORCE_END_START;

			// �L�����Z���I����ʒm����
			wk->param->result = WIFI_BTOWER_RESULT_CANCEL;

		}
	}

	return SEQ_MAIN;
	
}


//------------------------------------------------------------------
/**
 * $brief   ���ɑI���͏I����Ă���̂�WIFI����ڑ�����
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int Enter_ForceEndStart( WBTOWER_WORK *wk ) 
{
	// �ڑ����I�����܂�
	MessagePrint( wk, wk->SystemMsgManager, dwc_message_0011, 1, 0x0f0f );
	WBTower_SetNextSeq( wk, ENTER_MES_WAIT, ENTER_FORCE_END );

	return SEQ_MAIN;
}

//------------------------------------------------------------------
/**
 * $brief   �ڑ��I��
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int Enter_ForceEnd( WBTOWER_WORK *wk )
{
	// WIFI�ڑ����I��
    DWC_CleanupInet();
	WBTower_SubProcessChange( wk, WBTOWER_ENTER, 0 );
	wk->subprocess_seq  = ENTER_FORCE_END_MES;

	return SEQ_MAIN;
	
}

//------------------------------------------------------------------
/**
 * @brief   �ڑ��I�����b�Z�[�W
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int Enter_ForceEndMessage( WBTOWER_WORK *wk )
{
	MessagePrint( wk, wk->SystemMsgManager, dwc_message_0012, 1, 0x0f0f );
	WBTower_SetNextSeq( wk, ENTER_MES_WAIT_1_SECOND, ENTER_END );
	wk->wait = 0;

	return SEQ_MAIN;
}


//------------------------------------------------------------------
/**
 * $brief   �T�u�v���Z�X�V�[�P���X���C��
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int Enter_Main( WBTOWER_WORK *wk)
{

#if 0
	if(sys.trg & PAD_BUTTON_B){
		// DWC�l�b�g�ڑ��I��
	    DWC_CleanupInet();
		wk->subprocess_seq = ENTER_END;
	}

	if(sys.trg & PAD_BUTTON_X){
		wk->subprocess_seq  = ENTER_END;
		 WBTower_SubProcessChange( wk, WBTOWER_ENTER, 0 );
	}
#endif
	return SEQ_MAIN;
}

//------------------------------------------------------------------
/**
 * $brief   �T�u�v���Z�X�V�[�P���X�I������
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int Enter_End( WBTOWER_WORK *wk)
{
    WirelessIconEasyEnd();

    // �ʐM�G���[�Ǘ��̂��߂ɒʐM���[�`����OFF
    CommStateWifiDPWEnd();
	
	WIPE_SYS_Start( WIPE_PATTERN_WMS, WIPE_TYPE_FADEOUT, WIPE_TYPE_FADEOUT, WIPE_FADE_BLACK, 8, 1, HEAPID_WIFI_BATTLETOWER );
	wk->subprocess_seq = 0;
	
	return SEQ_FADEOUT;
}

//------------------------------------------------------------------
/**
 * $brief   �͂��E������
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int Enter_YesNo( WBTOWER_WORK *wk)
{
	wk->YesNoMenuWork = WBTower_BmpWinYesNoMake(wk->bgl, WBTOWER_YESNO_PY2, YESNO_OFFSET );
	wk->subprocess_seq = wk->subprocess_nextseq;
//	wk->subprocess_seq = ENTER_YESNO_SELECT;

	return SEQ_MAIN;
	
}


//------------------------------------------------------------------
/**
 * $brief   �͂��E�������I��
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int Enter_YesNoSelect( WBTOWER_WORK *wk)
{
	int ret = BmpYesNoSelectMain( wk->YesNoMenuWork, HEAPID_WIFI_BATTLETOWER );

	if(ret!=BMPMENU_NULL){
		if(ret==BMPMENU_CANCEL){
			// �������������g���C
			wk->subprocess_seq = ENTER_START;
		}else{
			// WIFI���������I��
//			 WBTower_SubProcessChange( wk, WBTOWER_ENTER, 0 );
//			wk->subprocess_seq = ENTER_END;
			wk->subprocess_seq = ENTER_FORCE_END_START;
		}
	}

	return SEQ_MAIN;
	
}


//==============================================================================
/**
 * $brief   �l�b�g�ɂ͌q���������ǃT�[�o�[�G���[�������\��
 *
 * @param   wk		
 *
 * @retval  none		
 */
//==============================================================================
static int Enter_ServerServiceError( WBTOWER_WORK *wk )
{
	int msgno =0;

	switch(wk->ConnectErrorNo){
	case DPW_BT_ERROR_SERVER_TIMEOUT:
	case DPW_BT_ERROR_DISCONNECTED:
		msgno = msg_wifi_bt_error_003;
		break;
	case DPW_BT_STATUS_SERVER_STOP_SERVICE:
		msgno = msg_wifi_bt_error_001;
		break;
	case DPW_BT_STATUS_SERVER_FULL:
	case DPW_BT_ERROR_SERVER_FULL:
		msgno = msg_wifi_bt_error_002;
		break;
	case DPW_BT_ERROR_FAILURE:
	case DPW_BT_ERROR_CANCEL:
		msgno = msg_wifi_bt_error_004;
		break;
	case DPW_BT_ERROR_ILLIGAL_REQUEST:
		msgno = msg_wifi_bt_error_005;
		break;
	}
	// �G���[�\��
	
	TimeIconDel( wk );

	MessagePrint( wk, wk->MsgManager, msgno, 1, 0x0f0f );
	WBTower_SetNextSeq( wk, ENTER_MES_WAIT, ENTER_SERVER_SERVICE_END );

	OS_TPrintf("�T�[�o�[ERROR\n");

	return SEQ_MAIN;
}

//==============================================================================
/**
 * $brief   �T�[�o�[�T�[�r�X�̖��ŏI��
 *
 * @param   wk		
 *
 * @retval  none		
 */
//==============================================================================
static int Enter_ServerServiceEnd( WBTOWER_WORK *wk )
{

    CommStateWifiDPWEnd();
    DWC_CleanupInet();
	WBTower_SubProcessChange( wk, WBTOWER_ENTER, 0 );
	wk->subprocess_seq  = ENTER_END;
	
	return SEQ_MAIN;
}

//------------------------------------------------------------------
/**
 * $brief   ��b�I����҂��Ď��̃V�[�P���X��
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int Enter_MessageWait( WBTOWER_WORK *wk )
{
	if( GF_MSG_PrintEndCheck( wk->MsgIndex )==0){
		wk->subprocess_seq = wk->subprocess_nextseq;
	}
	return SEQ_MAIN;

}

//------------------------------------------------------------------
/**
 * @brief   ��b�\����1�b�҂�
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int Enter_MessageWait1Second( WBTOWER_WORK *wk )
{
	if( GF_MSG_PrintEndCheck( wk->MsgIndex )==0){
		if(wk->wait > WAIT_ONE_SECONDE_NUM){
			wk->subprocess_seq = wk->subprocess_nextseq;
		}
		wk->wait++;
	}
	return SEQ_MAIN;
	
}

//------------------------------------------------------------------
/**
 * $brief   ��b�\����҂�����Łu�͂��E�������v���J�n����
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int Enter_MessageWaitYesNoStart(WBTOWER_WORK *wk)
{
	if( GF_MSG_PrintEndCheck( wk->MsgIndex )==0){
		wk->YesNoMenuWork = WBTower_BmpWinYesNoMake(wk->bgl, WBTOWER_YESNO_PY2, YESNO_OFFSET );
		wk->subprocess_seq = wk->subprocess_nextseq;
	}
	return SEQ_MAIN;
	
}

static void WordSetMessagePrint( WBTOWER_WORK *wk, MSGDATA_MANAGER *msgman, int msgno, int wait, u16 dat )
{
	STRBUF *strbuf = MSGMAN_AllocString( msgman, msgno );
	WORDSET_ExpandStr( wk->WordSet, wk->TalkString, strbuf );

	GF_BGL_BmpWinDataFill( &wk->MsgWin,  0x0f0f );
	BmpTalkWinWrite( &wk->MsgWin, WINDOW_TRANS_ON, WBTOWER_MESFRAME_CHR, WBTOWER_MESFRAME_PAL );

	// ������`��J�n
	wk->MsgIndex = GF_STR_PrintSimple( &wk->MsgWin, FONT_TALK, wk->TalkString, 0, 0, wait, NULL);


	STRBUF_Delete(strbuf);



}

//------------------------------------------------------------------
/**
 * @brief   Wifi�ڑ��G���[��\��
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int Enter_DwcErrorPrint( WBTOWER_WORK *wk )
{
	int type;
	
    type =  mydwc_errorType(-wk->ErrorCode);


	OS_Printf("error code = %d, type = %d\n", wk->ErrorCode, type);

    errorDisp(wk, type, -wk->ErrorCode);


	wk->subprocess_seq = ENTER_ERROR_PAD_WAIT;
	
	return SEQ_MAIN;
}
//------------------------------------------------------------------
/**
 * @brief   �v�����g��L�[�҂�
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int Enter_ErrorPadWait( WBTOWER_WORK *wk )
{
	if(sys.trg & PAD_BUTTON_DECIDE || sys.trg & PAD_BUTTON_CANCEL){
		BmpMenuWinClear( &wk->SubWin, WINDOW_TRANS_ON );
		wk->subprocess_seq = ENTER_START;
	}
	return SEQ_MAIN;
}












//------------------------------------------------------------------
/**
 * $brief   ��b�E�C���h�E�\��
 *
 * @param   wk		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void MessagePrint( WBTOWER_WORK *wk, MSGDATA_MANAGER *msgman, int msgno, int wait, u16 dat )
{

	//������擾
	MSGMAN_GetString(  msgman, msgno, wk->TalkString );

	// ��b�E�C���h�E�g�`��
	GF_BGL_BmpWinDataFill( &wk->MsgWin,  0x0f0f );
	BmpTalkWinWrite( &wk->MsgWin, WINDOW_TRANS_ON, WBTOWER_MESFRAME_CHR, WBTOWER_MESFRAME_PAL );

	// ������`��J�n
	wk->MsgIndex = GF_STR_PrintSimple( &wk->MsgWin, FONT_TALK, wk->TalkString, 0, 0, wait, NULL);


}

//------------------------------------------------------------------
/**
 * @brief   �����\�����ʏ����i�w���W�w��A���E�E�񂹁A�Z���^�����O�j
 *
 * @param   win		
 * @param   strbuf		
 * @param   flag		0:����	1:�Z���^�����O	2:�E��
 * @param   color		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int printCommonFunc( GF_BGL_BMPWIN *win, STRBUF *strbuf, int x, int flag, GF_PRINTCOLOR color, int font )
{
	int length=0,ground;
	switch(flag){
	case 1:
		length = FontProc_GetPrintStrWidth( font, strbuf, 0 );
		x          = ((win->sizx*8)-length)/2;
		break;
	case 2:
		length = FontProc_GetPrintStrWidth( font, strbuf, 0 );
		x          = (win->sizx*8)-length;
		break;
	}
	return x;
}


//------------------------------------------------------------------
/**
 * $brief   �Z���^�����O���ăv�����g(�`��̂݁j
 *
 * @param   win		GF_BGL_BMPWIN
 * @param   strbuf	
 * @param   flag	0���ƍ��񂹁A1���ƃZ���^�����O�A2���ƉE��
 * @param   y		Y���W���炷�l
 * @param   color	�����F�w��i�w�i�F��BMP��h��Ԃ��܂��j
 *
 * @retval  none
 */
//------------------------------------------------------------------
void WBTower_TalkPrint( GF_BGL_BMPWIN *win, STRBUF *strbuf, int x, int y, int flag, GF_PRINTCOLOR color )
{
	x = printCommonFunc( win, strbuf, x, flag, color, FONT_TALK );

	GF_STR_PrintColor( win, FONT_TALK, strbuf, x, y, MSG_ALLPUT, color,NULL);
	
}

void WBTower_SysPrint( GF_BGL_BMPWIN *win, STRBUF *strbuf, int x, int y, int flag, GF_PRINTCOLOR color )
{
	x = printCommonFunc( win, strbuf, x, flag, color, FONT_SYSTEM );

	GF_STR_PrintColor( win, FONT_SYSTEM, strbuf, x, y, MSG_ALLPUT, color,NULL);
}


//------------------------------------------------------------------
/**
 * @brief   ���l��BMPWIN�ɏ�������
 *
 * @param   win			
 * @param   numstr		�o�͗pSTRBUF
 * @param   num			���l
 * @param   keta		����
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void NumStringBmpWrite( GF_BGL_BMPWIN *win, STRBUF *numstr, int num, int keta )
{
	GF_BGL_BmpWinDataFill( win, 0x0f0f );
	STRBUF_SetNumber( numstr, num, keta, NUMBER_DISPTYPE_ZERO, NUMBER_CODETYPE_DEFAULT );
	WBTower_SysPrint( win, numstr, 0, 1, 1, GF_PRINTCOLOR_MAKE(1,2,0) );
}

//------------------------------------------------------------------
/**
 * $brief   WIFI�A�C�R����\���o�^����
 *
 * @param   wk		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
void WBTower_WifiIconAdd( WBTOWER_WORK *wk )
{
    WirelessIconEasy();
}


//------------------------------------------------------------------
/**
 * @brief   ���n�m�E�n�e�e
 *
 * @param   wk		
 * @param   flag		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void SelectArrowOnOff( WBTOWER_WORK *wk, int no, int flag )
{
	if(no==0 || no==1){
		CLACT_SetDrawFlag( wk->ArrowActWork[0], flag );
		CLACT_SetDrawFlag( wk->ArrowActWork[1], flag );
	}
}

//------------------------------------------------------------------
/**
 * @brief   ���W�w��
 *
 * @param   act		�A�N�^�[�̃|�C���^
 * @param   x		
 * @param   y		
 *
 * @retval  static		
 */
//------------------------------------------------------------------
static void SelectArrowPos( CLACT_WORK_PTR act, int x, int y )
{
	VecFx32 mat;

	mat.x = FX32_CONST( x );
	mat.y = FX32_CONST( y );
	mat.z = 0;
	CLACT_SetMatrix( act, &mat);

}


//------------------------------------------------------------------
/**
 * @brief   ���ԃA�C�R����\������
 *
 * @param   wk		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void TimeIconAdd( WBTOWER_WORK *wk )
{
	if(wk->timeWaitWork==NULL){
		wk->timeWaitWork = TimeWaitIconAdd( &wk->MsgWin, WBTOWER_MESFRAME_CHR );
	}
	
}

//------------------------------------------------------------------
/**
 * @brief   ���ԃA�C�R��������
 *
 * @param   wk		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void TimeIconDel( WBTOWER_WORK *wk )
{
	if(wk->timeWaitWork!=NULL){
		TimeWaitIconDel(wk->timeWaitWork);
		wk->timeWaitWork = NULL;
	}
}

//------------------------------------------------------------------
/**
 * @brief   ���������G���[�\��
 *
 * @param   wk		
 * @param   msgno		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void _systemMessagePrint( WBTOWER_WORK *wk, int msgno )
{
	STRBUF *tmpString = STRBUF_Create( DWC_ERROR_BUF_NUM, HEAPID_WIFI_BATTLETOWER );
    MSGMAN_GetString(  wk->SystemMsgManager, msgno, tmpString );
    WORDSET_ExpandStr( wk->WordSet, wk->ErrorString, tmpString );

    // ��b�E�C���h�E�g�`��
    GF_BGL_BmpWinDataFill(&wk->SubWin, 15 );
    BmpMenuWinWrite(&wk->SubWin, WINDOW_TRANS_OFF, WBTOWER_MENUFRAME_CHR, WBTOWER_MENUFRAME_PAL );
    // ������`��J�n
    wk->MsgIndex = GF_STR_PrintSimple( &wk->SubWin, FONT_TALK,
                                       wk->ErrorString, 0, 0, MSG_ALLPUT, NULL);

	STRBUF_Delete(tmpString);
}

//------------------------------------------------------------------
/**
 * @brief   Wifi�R�l�N�V�����G���[�̕\��
 *
 * @param   wk		
 * @param   type	
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void errorDisp(WBTOWER_WORK* wk, int type, int code)
{
    int msgno;

    if(type != -1){
        msgno = dwc_error_0001 + type;
    }
    else{
        msgno = dwc_error_0012;
    }

    WORDSET_RegisterNumber(wk->WordSet, 0, code,
                           5, NUMBER_DISPTYPE_ZERO, NUMBER_CODETYPE_DEFAULT);

	BmpTalkWinClear( &wk->MsgWin, WINDOW_TRANS_OFF );
    _systemMessagePrint(wk, msgno);

}