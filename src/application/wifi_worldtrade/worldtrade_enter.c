//============================================================================================
/**
 * @file	worldtrade_enter.c
 * @bfief	���E�������������
 * @author	Akito Mori
 * @date	06.04.16
 */
//============================================================================================
#include "common.h"
#include <dwc.h>
#include "libdpw/dpw_tr.h"
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
#include "savedata/wifilist.h"
#include "savedata/zukanwork.h"
#include "communication/communication.h"


#include "application/worldtrade.h"
#include "worldtrade_local.h"

#include "msgdata/msg_wifi_lobby.h"
#include "msgdata/msg_wifi_gtc.h"
#include "msgdata/msg_wifi_system.h"



#include "worldtrade.naix"			// �O���t�B�b�N�A�[�J�C�u��`
#include "../wifi_p2pmatch/wifip2pmatch.naix"			// �O���t�B�b�N�A�[�J�C�u��`



//============================================================================================
//	�v���g�^�C�v�錾
//============================================================================================
/*** �֐��v���g�^�C�v ***/
static void BgInit( GF_BGL_INI * ini );
static void BgExit( GF_BGL_INI * ini );
static void BgGraphicSet( WORLDTRADE_WORK * wk );
static void BmpWinInit( WORLDTRADE_WORK *wk );
static void BmpWinDelete( WORLDTRADE_WORK *wk );
static void InitWork( WORLDTRADE_WORK *wk );
static void FreeWork( WORLDTRADE_WORK *wk );
static void _systemMessagePrint( WORLDTRADE_WORK *wk, int msgno );
static void errorDisp(WORLDTRADE_WORK* wk, int type, int code);


static int Enter_Start( WORLDTRADE_WORK *wk);
static int Enter_ConnectYesNoSelect( WORLDTRADE_WORK *wk );
static int Enter_EndYesNoSelect( WORLDTRADE_WORK *wk );
static int Enter_InternetConnect( WORLDTRADE_WORK *wk );
static int Enter_InternetConnectWait( WORLDTRADE_WORK *wk );
static int Enter_DpwTrInit( WORLDTRADE_WORK *wk );
static int Enter_ServerStart( WORLDTRADE_WORK *wk );
static int Enter_End( WORLDTRADE_WORK *wk);
static int Enter_YesNo( WORLDTRADE_WORK *wk);
static int Enter_YesNoSelect( WORLDTRADE_WORK *wk);
static int Enter_MessageWait( WORLDTRADE_WORK *wk );
static int Enter_MessageWaitYesNoStart(WORLDTRADE_WORK *wk);
static int Enter_ServerServiceError( WORLDTRADE_WORK *wk );
static int Enter_ServerServiceEnd( WORLDTRADE_WORK *wk );
static int Enter_ServerResult( WORLDTRADE_WORK *wk );
static int Enter_EndStart( WORLDTRADE_WORK *wk );
static int Enter_ForceEndStart( WORLDTRADE_WORK *wk );
static int Enter_ForceEnd( WORLDTRADE_WORK *wk ) ;
static int Enter_ForceEndMessage( WORLDTRADE_WORK *wk );
static int Enter_MessageWait1Second( WORLDTRADE_WORK *wk );
static int Enter_WifiConnectionLogin( WORLDTRADE_WORK *wk );
static int Enter_WifiConnectionLoginWait( WORLDTRADE_WORK *wk );
static int Enter_DwcErrorPrint( WORLDTRADE_WORK *wk );
static int Enter_ErrorPadWait( WORLDTRADE_WORK *wk );


static int printCommonFunc( GF_BGL_BMPWIN *win, STRBUF *strbuf, int x, int flag, GF_PRINTCOLOR color, int font );

enum{
	ENTER_START=0,
	ENTER_CONNECT_YESNO_SELECT,
	ENTER_INTERNET_CONNECT,
	ENTER_INTERNET_CONNECT_WAIT,
	ENTER_WIFI_CONNECTION_LOGIN,
	ENTER_WIFI_CONNECTION_LOGIN_WAIT,
	ENTER_DPWTR_INIT,
	ENTER_SERVER_START,
	ENTER_SERVER_RESULT,
	ENTER_END,
	ENTER_MES_WAIT,
	ENTER_MES_WAIT_YESNO_START, 
	ENTER_YESNO_SELECT,
	ENTER_END_START,
	ENTER_END_YESNO_SELECT,
	ENTER_FORCE_END_START,
	ENTER_FORCE_END,
	ENTER_FORCE_END_MESSAGE,
	ENTER_MES_WAIT_1_SECOND,

	ENTER_SERVER_SERVICE_ERROR,
	ENTER_SERVER_SERVICE_END,
	
	ENTER_DWC_ERROR_PRINT,
	ENTER_ERROR_PAD_WAIT,
};

static int (*Functable[])( WORLDTRADE_WORK *wk ) = {
	Enter_Start,				// ENTER_START=0,
	Enter_ConnectYesNoSelect,	// ENTER_CONNECT_YESNO_SELECT,
	Enter_InternetConnect,		// ENTER_INTERNET_CONNECT
	Enter_InternetConnectWait,	// ENTER_INTERNET_CONNECT_WAIT
	Enter_WifiConnectionLogin,  // ENTER_WIFI_CONNECTION_LOGIN
	Enter_WifiConnectionLoginWait, // ENTER_WIFI_CONNECTION_LOGIN_WAIT
	Enter_DpwTrInit,			// ENTER_DPWTR_INIT
	Enter_ServerStart,			// ENTER_SERVER_START
	Enter_ServerResult,			// ENTER_SERVER_RESULT
	Enter_End,             	 	// ENTER_END,
	Enter_MessageWait,     	 	// ENTER_MES_WAIT
	Enter_MessageWaitYesNoStart,// ENTER_MES_WAIT_YESNO_START
	Enter_YesNoSelect,			// ENTER_YESNO_SELECT
	Enter_EndStart,				// ENTER_END_START
	Enter_EndYesNoSelect,		// ENTER_END_YESNO_SELECT
	Enter_ForceEndStart,		// ENTER_FORCE_END_START
	Enter_ForceEnd,				// ENTER_FORCE_END
	Enter_ForceEndMessage,		// ENTER_FORCE_END_MESSAGE
	Enter_MessageWait1Second,	// ENTER_MES_WAIT_1_SECOND
	
	Enter_ServerServiceError,	// ENTER_SERVER_SERVICE_ERROR
	Enter_ServerServiceEnd,		// ENTER_SERVER_SERVICE_END

	Enter_DwcErrorPrint,		// ENTER_DWC_ERROR_PRINT
	Enter_ErrorPadWait,			// ENTER_ERROR_PAD_WAIT
};


//============================================================================================
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
int WorldTrade_Enter_Init(WORLDTRADE_WORK *wk, int seq)
{
	// ���[�N������
	InitWork( wk );
	
	// ���C�v�t�F�[�h�J�n
	WIPE_SYS_Start( WIPE_PATTERN_WMS, WIPE_TYPE_FADEIN, WIPE_TYPE_FADEIN, WIPE_FADE_BLACK, WORLDTRADE_WIPE_SPPED, 1, HEAPID_WORLDTRADE );
#ifdef GTS_FADE_OSP
	OS_Printf( "******************** worldtrade_enter.c [172] MS ********************\n" );
#endif

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
	WorldTrade_WifiIconAdd( wk );

	if(!DWC_CheckInet()){
		// ����wifi�ڑ��̍ۂ͖������Őڑ���
		if(wk->param->connect){
			// WIFI���������J�n
			Enter_MessagePrint( wk, wk->LobbyMsgManager, msg_wifilobby_002, 1, 0x0f0f );
			WorldTrade_SetNextSeq( wk, ENTER_MES_WAIT, ENTER_INTERNET_CONNECT );
			WorldTrade_TimeIconAdd(wk);
		}else{
			wk->subprocess_seq = ENTER_START;
		}
	}else{
		wk->subprocess_seq = ENTER_FORCE_END_START;
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
int WorldTrade_Enter_Main(WORLDTRADE_WORK *wk, int seq)
{
	int ret;

	// �ʐM��Ԃ��m�F���ăA�C�R���̕\����ς���
    WirelessIconEasy_SetLevel( WorldTrade_WifiLinkLevel());

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
int WorldTrade_Enter_End(WORLDTRADE_WORK *wk, int seq)
{
	FreeWork( wk );
	
	BmpWinDelete( wk );
	
	BgExit( wk->bgl );

	// ���̃T�u�v���Z�X��ݒ肷��
	WorldTrade_SubProcessUpdate( wk );
	
	// ���̃T�u�v���Z�X��������̂܂܂������琢�E�����I��
	if(wk->sub_process==WORLDTRADE_ENTER){
		OS_TPrintf("���E�����I��\n");
		return SEQ_OUT;
	}
	
	OS_TPrintf("WorldTrade_Enter end\n");
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


	GF_BGL_ClearCharSet( GF_BGL_FRAME0_M, 32, 0, HEAPID_WORLDTRADE );
	GF_BGL_ClearCharSet( GF_BGL_FRAME0_S, 32, 0, HEAPID_WORLDTRADE );
	GF_Disp_GXS_VisibleControl( GX_PLANEMASK_OBJ, VISIBLE_OFF );	//�T�u���OBJ�ʂn�m

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
static void BgGraphicSet( WORLDTRADE_WORK * wk )
{
	GF_BGL_INI *bgl = wk->bgl;

	// �㉺��ʂa�f�p���b�g�]��
	ArcUtil_PalSet(    ARC_WIFIP2PMATCH_GRA, NARC_wifip2pmatch_conect_NCLR, PALTYPE_MAIN_BG, 0, 0,  HEAPID_WORLDTRADE);
	ArcUtil_PalSet(    ARC_WIFIP2PMATCH_GRA, NARC_wifip2pmatch_conect_NCLR, PALTYPE_SUB_BG,  0, 0,  HEAPID_WORLDTRADE);
	
	// ��b�t�H���g�p���b�g�]��
	TalkFontPaletteLoad( PALTYPE_MAIN_BG, WORLDTRADE_TALKFONT_PAL*0x20, HEAPID_WORLDTRADE );
	TalkFontPaletteLoad( PALTYPE_SUB_BG,  WORLDTRADE_TALKFONT_PAL*0x20, HEAPID_WORLDTRADE );

	// ��b�E�C���h�E�O���t�B�b�N�]��
	TalkWinGraphicSet(	bgl, GF_BGL_FRAME0_M, WORLDTRADE_MESFRAME_CHR, 
						WORLDTRADE_MESFRAME_PAL,  CONFIG_GetWindowType(wk->param->config), HEAPID_WORLDTRADE );

	MenuWinGraphicSet(	bgl, GF_BGL_FRAME0_M, WORLDTRADE_MENUFRAME_CHR,
						WORLDTRADE_MENUFRAME_PAL, 0, HEAPID_WORLDTRADE );




	// ���C�����BG1�L�����]��
	ArcUtil_BgCharSet( ARC_WIFIP2PMATCH_GRA, NARC_wifip2pmatch_conect_NCGR, bgl, GF_BGL_FRAME1_M, 0, 18*6*0x20, 0, HEAPID_WORLDTRADE);

	// ���C�����BG1�X�N���[���]��
	ArcUtil_ScrnSet(   ARC_WIFIP2PMATCH_GRA, NARC_wifip2pmatch_conect_01_NSCR, bgl, GF_BGL_FRAME1_M, 0, 32*24*2, 0, HEAPID_WORLDTRADE);



	// �T�u���BG1�L�����]��
	ArcUtil_BgCharSet( ARC_WIFIP2PMATCH_GRA, NARC_wifip2pmatch_conect_s_NCGR, bgl, GF_BGL_FRAME1_S, 0, 18*6*0x20, 0, HEAPID_WORLDTRADE);

	// �T�u���BG1�X�N���[���]��
	ArcUtil_ScrnSet(   ARC_WIFIP2PMATCH_GRA, NARC_wifip2pmatch_conect_s_NSCR, bgl, GF_BGL_FRAME1_S, 0, 32*24*2, 0, HEAPID_WORLDTRADE);

	GF_BGL_BackGroundColorSet( GF_BGL_FRAME0_M, 0 );
	GF_BGL_BackGroundColorSet( GF_BGL_FRAME0_S, 0 );

}

#define SUB_TEXT_X		(  4 )
#define SUB_TEXT_Y		(  4 )
#define SUB_TEXT_SX		( 23 )
#define SUB_TEXT_SY		( 16 )


#define SUB_NUMBER_X	( 20 )
#define SUB_NUMBER_Y	( 21 )
#define SUB_NUMBER_SX	( 10 )
#define SUB_NUMBER_SY	(  2 )

#define CONNECT_TEXT_X	(  4 )
#define CONNECT_TEXT_Y	(  1 )
#define CONNECT_TEXT_SX	( 24 )
#define CONNECT_TEXT_SY	(  2 )

#define TALK_MESSAGE_OFFSET	 ( WORLDTRADE_MENUFRAME_CHR + MENU_WIN_CGX_SIZ )
#define ERROR_MESSAGE_OFFSET ( TALK_MESSAGE_OFFSET   + TALK_WIN_SX*TALK_WIN_SY )
#define TITLE_MESSAGE_OFFSET ( ERROR_MESSAGE_OFFSET  + SUB_TEXT_SX*SUB_TEXT_SY )
#define YESNO_OFFSET 		 ( TITLE_MESSAGE_OFFSET  + CONNECT_TEXT_SX*CONNECT_TEXT_SY )
//------------------------------------------------------------------
/**
 * BMPWIN�����i�����p�l���Ƀt�H���g�`��j
 *
 * @param   wk		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void BmpWinInit( WORLDTRADE_WORK *wk )
{
	// ---------- ���C����� ------------------

	// BG0��BMPWIN(�G���[����)�E�C���h�E�m�ہE�`��
	GF_BGL_BmpWinAdd(wk->bgl, &wk->SubWin, GF_BGL_FRAME0_M,
	SUB_TEXT_X, SUB_TEXT_Y, SUB_TEXT_SX, SUB_TEXT_SY, WORLDTRADE_TALKFONT_PAL,  ERROR_MESSAGE_OFFSET );

	GF_BGL_BmpWinDataFill( &wk->SubWin, 0x0000 );

	// BG0��BMPWIN(�^�C�g��)�E�C���h�E�m�ہE�`��
	GF_BGL_BmpWinAdd(wk->bgl, &wk->TitleWin, GF_BGL_FRAME0_M,
	CONNECT_TEXT_X, CONNECT_TEXT_Y, CONNECT_TEXT_SX, CONNECT_TEXT_SY, WORLDTRADE_TALKFONT_PAL, TITLE_MESSAGE_OFFSET );

	GF_BGL_BmpWinDataFill( &wk->TitleWin, 0x0000 );
	WorldTrade_TalkPrint( &wk->TitleWin, wk->TitleString, 0, 1, 1, GF_PRINTCOLOR_MAKE(15,14,0) );

	// ----------- �T�u��ʖ��O�\��BMP�m�� ------------------
	// BG0��BMP�i��b�E�C���h�E�j�m��
	GF_BGL_BmpWinAdd(wk->bgl, &wk->MsgWin, GF_BGL_FRAME0_M,
		TALK_WIN_X, 
		TALK_WIN_Y, 
		TALK_WIN_SX, 
		TALK_WIN_SY, WORLDTRADE_TALKFONT_PAL,  TALK_MESSAGE_OFFSET );
	GF_BGL_BmpWinDataFill( &wk->MsgWin, 0x0000 );

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
static void BmpWinDelete( WORLDTRADE_WORK *wk )
{
	
	GF_BGL_BmpWinDel( &wk->MsgWin );
	GF_BGL_BmpWinDel( &wk->TitleWin );
	GF_BGL_BmpWinDel( &wk->SubWin );


}

//------------------------------------------------------------------
/**
 * ���E�������[�N������
 *
 * @param   wk		WORLDTRADE_WORK*
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void InitWork( WORLDTRADE_WORK *wk )
{

	// ������o�b�t�@�쐬
	wk->TalkString  = STRBUF_Create( TALK_MESSAGE_BUF_NUM, HEAPID_WORLDTRADE );
	wk->ErrorString = STRBUF_Create( DWC_ERROR_BUF_NUM,    HEAPID_WORLDTRADE );
	wk->TitleString = MSGMAN_AllocString( wk->MsgManager, msg_gtc_01_032 );


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
static void FreeWork( WORLDTRADE_WORK *wk )
{

	STRBUF_Delete( wk->TitleString ); 
	STRBUF_Delete( wk->ErrorString ); 
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
static int Enter_Start( WORLDTRADE_WORK *wk)
{
	// WIFI�R�l�N�V�����ɐڑ����܂����H
	Enter_MessagePrint( wk, wk->SystemMsgManager, dwc_message_0002, 1, 0x0f0f );
	WorldTrade_SetNextSeq( wk, ENTER_MES_WAIT_YESNO_START, ENTER_CONNECT_YESNO_SELECT );

	wk->boxSearchFlag = 1;

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
static int Enter_ConnectYesNoSelect( WORLDTRADE_WORK *wk )
{
	int ret = BmpYesNoSelectMain( wk->YesNoMenuWork, HEAPID_WORLDTRADE );

	if(ret!=BMPMENU_NULL){
		if(ret==BMPMENU_CANCEL){
			// �ڑ����I�����܂����H
//			Enter_MessagePrint( wk, wk->MsgManager, msg_gtc_01_008, 1, 0, 0x0f0f );
//			WorldTrade_SetNextSeq( wk, ENTER_MES_WAIT_YESNO_START, ENTER_END_YESNO_SELECT );
//			wk->subprocess_seq = ENTER_END_START;

			// �I��
		    CommStateWifiDPWEnd();
			WorldTrade_SubProcessChange( wk, WORLDTRADE_ENTER, 0 );
			wk->subprocess_seq  = ENTER_END;

		}else{
			// WIFI���������J�n
			Enter_MessagePrint( wk, wk->LobbyMsgManager, msg_wifilobby_002, 1, 0x0f0f );
			WorldTrade_SetNextSeq( wk, ENTER_MES_WAIT, ENTER_INTERNET_CONNECT );
			WorldTrade_TimeIconAdd(wk);

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
static int Enter_EndStart( WORLDTRADE_WORK *wk ) 
{
	// �ڑ����I�����܂����H
	Enter_MessagePrint( wk, wk->MsgManager, msg_gtc_01_008, 1, 0x0f0f );
	WorldTrade_SetNextSeq( wk, ENTER_MES_WAIT_YESNO_START, ENTER_END_YESNO_SELECT );

	return SEQ_MAIN;
}

//------------------------------------------------------------------
/**
 * $brief   �ڑ����I�����܂����H�i���E�����̏I���j
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int Enter_EndYesNoSelect( WORLDTRADE_WORK *wk )
{
	int ret = BmpYesNoSelectMain( wk->YesNoMenuWork, HEAPID_WORLDTRADE );

	if(ret!=BMPMENU_NULL){
		if(ret==BMPMENU_CANCEL){
			if(!DWC_CheckInet()){		
				// �ڑ����J�n���܂����H
				wk->subprocess_seq  = ENTER_START;
			}else{
//				 WorldTrade_SubProcessChange( wk, WORLDTRADE_TITLE, 0 );
//				wk->subprocess_seq  = ENTER_END;

				// ���ɐڑ��ς݂Ȃ�
				// �T�[�o�[�`�F�b�N�̌�^�C�g�����j���[��
				WorldTrade_SubProcessChange( wk, WORLDTRADE_UPLOAD, MODE_SERVER_CHECK );
				wk->sub_returnprocess = WORLDTRADE_TITLE;
				wk->subprocess_seq    = ENTER_END;

			}
		}else{
			// WIFI���������I��
			if(DWC_CheckInet()){		
			    DWC_CleanupInet();
			}
		    // �ʐM�G���[�Ǘ��̂��߂ɒʐM���[�`����OFF
		    CommStateWifiDPWEnd();
			WorldTrade_SubProcessChange( wk, WORLDTRADE_ENTER, 0 );
			wk->subprocess_seq  = ENTER_END;
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
static int Enter_ForceEndStart( WORLDTRADE_WORK *wk ) 
{
	// �ڑ����I�����܂�
	Enter_MessagePrint( wk, wk->SystemMsgManager, dwc_message_0011, 1, 0x0f0f );
	WorldTrade_SetNextSeq( wk, ENTER_MES_WAIT, ENTER_FORCE_END );

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
static int Enter_ForceEnd( WORLDTRADE_WORK *wk )
{
    // �ʐM�G���[�Ǘ��̂��߂ɒʐM���[�`����OFF
    CommStateWifiDPWEnd();
	// WIFI���������I��
    DWC_CleanupInet();
	WorldTrade_SubProcessChange( wk, WORLDTRADE_ENTER, 0 );
	wk->subprocess_seq  = ENTER_FORCE_END_MESSAGE;

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
static int Enter_ForceEndMessage( WORLDTRADE_WORK *wk )
{
	Enter_MessagePrint( wk, wk->SystemMsgManager, dwc_message_0012, 1, 0x0f0f );
	WorldTrade_SetNextSeq( wk, ENTER_MES_WAIT_1_SECOND, ENTER_END );
		
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
static int Enter_InternetConnect( WORLDTRADE_WORK *wk )
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
static int Enter_InternetConnectWait( WORLDTRADE_WORK *wk )
{
	DWC_ProcessInet();

	if (DWC_CheckInet())
	{
		switch (DWC_GetInetStatus())
		{
		case DWC_CONNECTINET_STATE_ERROR:
			{
				// �G���[�\��
				DWCError err;
				int errcode;
				err = DWC_GetLastError(&errcode);
				wk->ErrorRet  = err;
				wk->ErrorCode = errcode;

				OS_TPrintf("   Error occurred %d %d.\n", err, errcode);
			}
			DWC_ClearError();
			DWC_CleanupInet();

			WorldTrade_TimeIconDel( wk );
			wk->subprocess_seq = ENTER_DWC_ERROR_PRINT;

			break;
		case DWC_CONNECTINET_STATE_FATAL_ERROR:
			{
				// �G���[�\��
				DWCError err;
				int errcode;
				err = DWC_GetLastError(&errcode);

				OS_TPrintf("   Error occurred %d %d.\n", err, errcode);
				WorldTrade_TimeIconDel(wk);
				wk->subprocess_seq = ENTER_SERVER_SERVICE_ERROR;
				wk->ConnectErrorNo = DPW_TR_ERROR_SERVER_TIMEOUT;
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
static int Enter_WifiConnectionLogin( WORLDTRADE_WORK *wk )
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
static int Enter_WifiConnectionLoginWait( WORLDTRADE_WORK *wk )
{
	switch(DWC_NASLoginProcess()){
	case DWC_NASLOGIN_STATE_SUCCESS:
		OS_Printf("GameSpy�T�[�o�[���O�C������\n");
		wk->subprocess_seq = ENTER_DPWTR_INIT;
		break;
	case DWC_NASLOGIN_STATE_ERROR:
	case DWC_NASLOGIN_STATE_CANCELED:
		WorldTrade_TimeIconDel(wk);
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
static int Enter_DpwTrInit( WORLDTRADE_WORK *wk )
{
	// ���E�����ڑ�������
	DWCUserData		*MyUserData;		// �F�؍ς݂�DWCUSER�f�[�^�������Ȃ��͂�
	s32 profileId;

	// DWCUser�\���̎擾
	MyUserData = WifiList_GetMyUserInfo(wk->param->wifilist);


	// ����FriendKey�̓v���C���[���n�߂Ď擾�������̂��H
	profileId = SYSTEMDATA_GetDpwInfo( wk->param->systemdata );
	if( profileId==0 ){
		OS_TPrintf("����擾profileId�Ȃ̂�DpwInfo�Ƃ��ēo�^���� %08x \n", wk->param->profileId);

		// ����擾FriendKey�Ȃ̂ŁADpwId�Ƃ��ĕۑ�����
		SYSTEMDATA_SetDpwInfo( wk->param->systemdata, wk->param->profileId );
	}

	
	// �����ȃf�[�^���擾
	profileId = SYSTEMDATA_GetDpwInfo( wk->param->systemdata );
	OS_Printf("Dpw�T�[�o�[���O�C����� profileId=%08x\n", profileId);

	// DPW_TR������
	Dpw_Tr_Init( profileId, DWC_CreateFriendKey( MyUserData ) );

	OS_TPrintf("Dpw Trade ������\n");

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
static int Enter_ServerStart( WORLDTRADE_WORK *wk )
{
	Dpw_Tr_GetServerStateAsync();

	OS_TPrintf("Dpw Trade �T�[�o�[��Ԏ擾�J�n\n");

	// �T�[�o�[��Ԋm�F�҂���
	wk->subprocess_seq = ENTER_SERVER_RESULT;

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
static int Enter_ServerResult( WORLDTRADE_WORK *wk )
{
	if (Dpw_Tr_IsAsyncEnd()){
		s32 result = Dpw_Tr_GetAsyncResult();
		switch (result){
		case DPW_TR_STATUS_SERVER_OK:		// ����ɓ��삵�Ă���
			OS_TPrintf(" server is up!\n");

			// �|�P�����m�F�T�u�v���Z�X�ֈڍs
			WorldTrade_SubProcessChange( wk, WORLDTRADE_TITLE, 0 );
			wk->subprocess_seq  = ENTER_END;
			break;
		case DPW_TR_STATUS_SERVER_STOP_SERVICE:	// �T�[�r�X��~��
			OS_TPrintf(" server stop service.\n");
			wk->ConnectErrorNo = result;
			wk->subprocess_seq = ENTER_SERVER_SERVICE_ERROR;
			break;
		case DPW_TR_STATUS_SERVER_FULL:			// �T�[�o�[�����t
		case DPW_TR_ERROR_SERVER_FULL:
			OS_TPrintf(" server full.\n");
			wk->ConnectErrorNo = result;
			wk->subprocess_seq = ENTER_SERVER_SERVICE_ERROR;
			break;

		case DPW_TR_ERROR_CANCEL :
		case DPW_TR_ERROR_FAILURE :
			// �uGTS�̂����ɂ�ɂ����ς����܂����v���^�C�g����
			wk->ConnectErrorNo = result;
			wk->subprocess_seq = ENTER_SERVER_SERVICE_ERROR;
			break;

		case DPW_TR_ERROR_SERVER_TIMEOUT :
		case DPW_TR_ERROR_DISCONNECTED:	
			// �T�[�o�[�ƒʐM�ł��܂��񁨏I��
			OS_TPrintf(" upload error. %d \n", result);
			wk->ConnectErrorNo = result;
			wk->subprocess_seq = ENTER_SERVER_SERVICE_ERROR;
			break;
		case DPW_TR_ERROR_FATAL:			//!< �ʐM�v���I�G���[�B�d���̍ē������K�v�ł�
			// ���ӂ��Ƃ΂�
			WorldTrade_TimeIconDel(wk);
			CommFatalErrorFunc_NoNumber();
			break;

		}
		
	}
	WorldTrade_TimeIconDel(wk);
	return SEQ_MAIN;
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
static int Enter_DwcErrorPrint( WORLDTRADE_WORK *wk )
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
static int Enter_ErrorPadWait( WORLDTRADE_WORK *wk )
{
	if(sys.trg & PAD_BUTTON_DECIDE || sys.trg & PAD_BUTTON_CANCEL){
		BmpMenuWinClear( &wk->SubWin, WINDOW_TRANS_ON );
		wk->subprocess_seq = ENTER_START;
	}
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
static int Enter_End( WORLDTRADE_WORK *wk)
{
    WirelessIconEasyEnd();

	// ���ԃA�C�R�������Q�d����ɂȂ�Ȃ��悤��NULL�`�F�b�N����
	WorldTrade_TimeIconDel( wk );

	
	WIPE_SYS_Start( WIPE_PATTERN_WMS, WIPE_TYPE_FADEOUT, WIPE_TYPE_FADEOUT, WIPE_FADE_BLACK, WORLDTRADE_WIPE_SPPED, 1, HEAPID_WORLDTRADE );
#ifdef GTS_FADE_OSP
	OS_Printf( "******************** worldtrade_enter.c [1037] MS ********************\n" );
#endif
	wk->subprocess_seq = 0;
	wk->sub_out_flg = 1;
	
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
static int Enter_YesNo( WORLDTRADE_WORK *wk)
{
	wk->YesNoMenuWork = WorldTrade_BmpWinYesNoMake(wk->bgl, WORLDTRADE_YESNO_PY2, YESNO_OFFSET );
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
static int Enter_YesNoSelect( WORLDTRADE_WORK *wk)
{
	int ret = BmpYesNoSelectMain( wk->YesNoMenuWork, HEAPID_WORLDTRADE );

	if(ret!=BMPMENU_NULL){
		if(ret==BMPMENU_CANCEL){
			// �������������g���C
			wk->subprocess_seq = ENTER_START;
		}else{
			// WIFI���������I��
			 WorldTrade_SubProcessChange( wk, WORLDTRADE_ENTER, 0 );
			wk->subprocess_seq = ENTER_END;
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
static int Enter_ServerServiceError( WORLDTRADE_WORK *wk )
{
	int msgno =0;

	switch(wk->ConnectErrorNo){
	case DPW_TR_STATUS_SERVER_STOP_SERVICE:
		msgno = msg_gtc_error_001;
		break;
	case DPW_TR_STATUS_SERVER_FULL:
	case DPW_TR_ERROR_SERVER_FULL:
		msgno = msg_gtc_error_002;
		break;
	case DPW_TR_ERROR_SERVER_TIMEOUT:
	case DPW_TR_ERROR_DISCONNECTED:
		// �f�s�r�Ƃ̂�����������܂����B�������ɂ��ǂ�܂�
		msgno = msg_gtc_error_006;
		break;
	case DPW_TR_ERROR_CANCEL  :
	case DPW_TR_ERROR_FAILURE :
	case DPW_TR_ERROR_NO_DATA:
	case DPW_TR_ERROR_ILLIGAL_REQUEST :
		//�@������G���[���������܂����B
		msgno = msg_gtc_error_005;
		break;
	}
	// �G���[�\��
	Enter_MessagePrint( wk, wk->MsgManager, msgno, 1, 0x0f0f );
	WorldTrade_SetNextSeq( wk, ENTER_MES_WAIT, ENTER_SERVER_SERVICE_END );

	OS_TPrintf("Error����\n");

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
static int Enter_ServerServiceEnd( WORLDTRADE_WORK *wk )
{

    // �ʐM�G���[�Ǘ��̂��߂ɒʐM���[�`����OFF
    CommStateWifiDPWEnd();
    DWC_CleanupInet();
	WorldTrade_SubProcessChange( wk, WORLDTRADE_ENTER, 0 );
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
static int Enter_MessageWait( WORLDTRADE_WORK *wk )
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
static int Enter_MessageWait1Second( WORLDTRADE_WORK *wk )
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
static int Enter_MessageWaitYesNoStart(WORLDTRADE_WORK *wk)
{
	if( GF_MSG_PrintEndCheck( wk->MsgIndex )==0){
		wk->YesNoMenuWork = WorldTrade_BmpWinYesNoMake(wk->bgl, WORLDTRADE_YESNO_PY2, YESNO_OFFSET );
		wk->subprocess_seq = wk->subprocess_nextseq;
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
void Enter_MessagePrint( WORLDTRADE_WORK *wk, MSGDATA_MANAGER *msgman, int msgno, int wait, u16 dat )
{
	// ������擾
	STRBUF *tempbuf;

	// ������擾
	tempbuf = MSGMAN_AllocString(  msgman, msgno );

	// WORDSET�W�J
	WORDSET_ExpandStr( wk->WordSet, wk->TalkString, tempbuf );

	STRBUF_Delete(tempbuf);

	// ��b�E�C���h�E�g�`��
	GF_BGL_BmpWinDataFill( &wk->MsgWin,  0x0f0f );
	BmpTalkWinWrite( &wk->MsgWin, WINDOW_TRANS_ON, WORLDTRADE_MESFRAME_CHR, WORLDTRADE_MESFRAME_PAL );

	// ������`��J�n
	wk->MsgIndex = GF_STR_PrintSimple( &wk->MsgWin, FONT_TALK, wk->TalkString, 0, 0, wait, NULL);

	wk->wait = 0;
}


	



//------------------------------------------------------------------
/**
 * @brief   
 *
 * @param   win		
 * @param   strbuf		
 * @param   flag		1���ƃZ���^�����O�A�Q���ƉE�悹
 * @param   color		
 * @param   font		�t�H���g�w��iFONT_TALK��FONT_SYSTEM
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int printCommonFunc( GF_BGL_BMPWIN *win, STRBUF *strbuf, int x, int flag, GF_PRINTCOLOR color, int font )
{
	int length=0,ground;
	switch(flag){
	// �Z���^�����O
	case 1:
		length = FontProc_GetPrintStrWidth( font, strbuf, 0 );
		x          = ((win->sizx*8)-length)/2;
		break;

	// �E��
	case 2:
		length = FontProc_GetPrintStrWidth( font, strbuf, 0 );
		x          = (win->sizx*8)-length;
		break;
	}
	return x;
}


//------------------------------------------------------------------
/**
 * $brief   BMPWIN���̕\���ʒu���w�肵��FONT_TALK�Ńv�����g(�`��̂݁j
 *
 * @param   win		GF_BGL_BMPWIN
 * @param   strbuf	
 * @param   x		X���W���炷�l
 * @param   y		Y���W���炷�l
 * @param   flag	0���ƍ��񂹁A1���ƃZ���^�����O�A2���ƉE��
 * @param   color	�����F�w��i�w�i�F��BMP��h��Ԃ��܂��j
 *
 * @retval  none
 */
//------------------------------------------------------------------
void WorldTrade_TalkPrint( GF_BGL_BMPWIN *win, STRBUF *strbuf, int x, int y, int flag, GF_PRINTCOLOR color )
{
	x = printCommonFunc( win, strbuf, x, flag, color, FONT_TALK );

	GF_STR_PrintColor( win, FONT_TALK, strbuf, x, y, MSG_ALLPUT, color,NULL);
	
}

//==============================================================================
/**
 * @brief   BMPWIN���̕\���ʒu���w�肵��FONT_SYSTEM�Ńv�����g(�`��̂݁j
 *
 * @param   win		
 * @param   strbuf		
 * @param   x		
 * @param   y		
 * @param   flag		
 * @param   color		
 *
 * @retval  none		
 */
//==============================================================================
void WorldTrade_SysPrint( GF_BGL_BMPWIN *win, STRBUF *strbuf, int x, int y, int flag, GF_PRINTCOLOR color )
{
	x = printCommonFunc( win, strbuf, x, flag, color, FONT_SYSTEM );

	GF_STR_PrintColor( win, FONT_SYSTEM, strbuf, x, y, MSG_ALLPUT, color,NULL);
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
void WorldTrade_WifiIconAdd( WORLDTRADE_WORK *wk )
{
    WirelessIconEasy();
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
static void _systemMessagePrint( WORLDTRADE_WORK *wk, int msgno )
{
	STRBUF *tmpString = STRBUF_Create( DWC_ERROR_BUF_NUM, HEAPID_WORLDTRADE );
    MSGMAN_GetString(  wk->SystemMsgManager, msgno, tmpString );
    WORDSET_ExpandStr( wk->WordSet, wk->ErrorString, tmpString );

    // ��b�E�C���h�E�g�`��
    GF_BGL_BmpWinDataFill(&wk->SubWin, 15 );
    BmpMenuWinWrite(&wk->SubWin, WINDOW_TRANS_OFF, WORLDTRADE_MENUFRAME_CHR, WORLDTRADE_MENUFRAME_PAL );
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
static void errorDisp(WORLDTRADE_WORK* wk, int type, int code)
{
    int msgno;

    if(type != -1){
        msgno = dwc_error_0001 + type;
    }
    else{
        msgno = dwc_error_0012;
    }
//    EndMessageWindowOff(wk);
    WORDSET_RegisterNumber(wk->WordSet, 0, code,
                           5, NUMBER_DISPTYPE_ZERO, NUMBER_CODETYPE_DEFAULT);

	BmpTalkWinClear( &wk->MsgWin, WINDOW_TRANS_OFF );
    _systemMessagePrint(wk, msgno);

#if 0
    switch(type){
      case 1:
      case 4:
      case 5:
        wk->seq = WIFIP2PMATCH_RETRY_INIT;  // �Đڑ����t�B�[���h��
        break;
      case 6:
      case 7:
      case 8:
      case 9:
        wk->seq = WIFIP2PMATCH_RETRY_INIT;//WIFIP2PMATCH_POWEROFF_INIT;  // �d����؂邩�t�B�[���h
        break;
      case 10:
        wk->seq = WIFIP2PMATCH_RETRY_INIT;  // ���j���[�ꗗ��
        break;
      case 0:
      case 2:
      case 3:
      case 11:
      default:
        wk->seq = WIFIP2PMATCH_MODE_CHECK_AND_END;  // �t�B�[���h
        break;
    }
#endif
}

