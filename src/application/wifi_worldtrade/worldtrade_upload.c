//============================================================================================
/**
 * @file	worldtrade_upload.c
 * @bfief	���E�����|�P�����f�[�^�A�b�v���[�h�f��
 * @author	Akito Mori
 * @date	06.05.04
 */
//============================================================================================

//#define TEST_DEMO_OFF	// ���̓f���ɍs���Ǝ~�܂�̂Ń^�C�g���ɖ߂�悤�ɂ��Ă���

#ifdef PM_DEBUG
// �R�����g���͂����ƕK���A�b�v���[�h�Ŏ��s����
//#define DEBUG_UPLOAD_ERROR
#endif

// �T�[�o�[�m�F����_�E�����[�h�ɗ���鎞��̪��ޱ�Ă��Ȃ��悤�ɂ����
#define REPAIR_060804

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
#include "savedata/savedata.h"
#include "savedata/wifilist.h"
#include "savedata/worldtrade_data.h"
#include "savedata/zukanwork.h"
#include "savedata/perapvoice.h"
#include "poketool/pokeparty.h"
#include "poketool/boxdata.h"
#include "itemtool/itemsym.h"
#include "communication/comm_state.h"
#include "communication/comm_wifihistory.h"
#include "savedata/get_poke.h"

#include "application/worldtrade.h"
#include "worldtrade_local.h"

#include "msgdata/msg_wifi_lobby.h"
#include "msgdata/msg_wifi_gtc.h"
#include "msgdata/msg_wifi_system.h"

#include "libdpw/dpw_tr.h"


#include "worldtrade.naix"			// �O���t�B�b�N�A�[�J�C�u��`

#define FIRST_NATUKIDO  (70)		///�������ꂽ�|�P�����ɓ����Ȃ��x



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
static void SetFnoteData( FNOTE_DATA *fnote,  Dpw_Tr_Data *trData );
static void AfterTradeCheck_ProcessControl( WORLDTRADE_WORK *wk );
static void WifiHistoryDataSet( WIFI_HISTORY *wifiHistory, Dpw_Tr_Data *trData );
static void ExchangePokemonDataAdd( WORLDTRADE_WORK *wk, POKEMON_PARAM *pp, int boxno);
static void TradeDateUpDate( WORLDTRADE_DATA *worldtrade_data );
static int MyPokemonPocketFullCheck( WORLDTRADE_WORK *wk, Dpw_Tr_Data *trData);
static void PrintError( WORLDTRADE_WORK *wk );
static void SetSaveNextSequence( WORLDTRADE_WORK *wk, int nextSeq1st, int nextSeq2nd );


static int Subseq_Start( WORLDTRADE_WORK *wk);
static int Subseq_UploadStart( WORLDTRADE_WORK *wk );
static int Subseq_UploadResult( WORLDTRADE_WORK *wk );
static int Subseq_UploadFinish( WORLDTRADE_WORK *wk );
static int Subseq_UploadFinishResult( WORLDTRADE_WORK *wk );
static int Subseq_Main( WORLDTRADE_WORK *wk);
static int Subseq_UploadSuccessMessage( WORLDTRADE_WORK *wk);
static int Subseq_DownloadSuccessMessage( WORLDTRADE_WORK *wk);
static int Subseq_ErrorMessage( WORLDTRADE_WORK *wk );
static int Subseq_ReturnTitleMessage( WORLDTRADE_WORK *wk );
static int Subseq_End( WORLDTRADE_WORK *wk);
static int Subseq_YesNo( WORLDTRADE_WORK *wk);
static int Subseq_ServerServiceError( WORLDTRADE_WORK *wk );
static int Subseq_ServerServiceEnd( WORLDTRADE_WORK *wk );
static int Subseq_MessageWait( WORLDTRADE_WORK *wk );
static int Subseq_DownloadStart( WORLDTRADE_WORK *wk );
static int Subseq_DownloadResult( WORLDTRADE_WORK *wk );
static int Subseq_DownloadFinish( WORLDTRADE_WORK *wk );
static int Subseq_DownloadFinishResult( WORLDTRADE_WORK *wk );
static int Subseq_ExchangeStart( WORLDTRADE_WORK *wk );			
static int Subseq_ExchangeResult( WORLDTRADE_WORK *wk );
static int Subseq_ExchangeFinish( WORLDTRADE_WORK *wk );
static int Subseq_ExchangeFinishResult( WORLDTRADE_WORK *wk );
static int Subseq_ExchangeSuccessMessage( WORLDTRADE_WORK *wk );
static int Subseq_ExchangeFailedMessage( WORLDTRADE_WORK *wk);
static void UploadPokemonDataDelete( WORLDTRADE_WORK *wk, int flag );
static void DownloadPokemonDataAdd( WORLDTRADE_WORK *wk, POKEMON_PARAM *pp, int boxno, int flag );
static int SubSeq_Save( WORLDTRADE_WORK *wk );
static int SubSeq_NowSaveMessage( WORLDTRADE_WORK *wk );
static int SubSeq_SaveLast( WORLDTRADE_WORK *wk );
static int Subseq_ServerDownloadResult( WORLDTRADE_WORK *wk );
static int Subseq_ServerDownload( WORLDTRADE_WORK *wk );
static int Subseq_ServerTradeCheckResult( WORLDTRADE_WORK *wk );
static int Subseq_ServerTradeCheck( WORLDTRADE_WORK *wk );
static int Subseq_DownloadExStart( WORLDTRADE_WORK *wk );
static int Subseq_DownloadExFinishResult( WORLDTRADE_WORK *wk );
static int Subseq_DownloadExSuccessMessage( WORLDTRADE_WORK *wk );
static int SubSeq_SaveWait( WORLDTRADE_WORK *wk );
static int SubSeq_SaveRandomWait( WORLDTRADE_WORK *wk );
static int Subseq_ServerTradeCheckEnd( WORLDTRADE_WORK *wk );
static int SubSeq_TimeoutSave( WORLDTRADE_WORK *wk );
static int SubSeq_TimeoutSaveWait( WORLDTRADE_WORK *wk );
static int Subseq_DownloadExFinish( WORLDTRADE_WORK *wk );




enum{
	SUBSEQ_START=0,
	SUBSEQ_MAIN,
	SUBSEQ_UPLOAD_START,
	SUBSEQ_UPLOAD_RESULT,
	SUBSEQ_UPLOAD_FINISH,
	SUBSEQ_UPLOAD_FINISH_RESULT,
	SUBSEQ_UPLOAD_SUCCESS_MESSAGE,

	SUBSEQ_DOWNLOAD_START,
	SUBSEQ_DOWNLOAD_RESULT,
	SUBSEQ_DOWNLOAD_FINISH,
	SUBSEQ_DOWNLOAD_FINISH_RESULT,
	SUBSEQ_DOWNLOAD_SUCCESS_MESSAGE,

	SUBSEQ_EXCHANGE_START,
	SUBSEQ_EXCHANGE_RESULT,
	SUBSEQ_EXCHANGE_FINISH,
	SUBSEQ_EXCHANGE_FINISH_RESULT,
	SUBSEQ_EXCHANGE_SUCCESS_MESSAGE,
	SUBSEQ_EXCHANGE_FAILED_MESSAGE,

	SUBSEQ_DOWNLOAD_EX_START,
	SUBSEQ_DOWNLOAD_EX_FINISH,
	SUBSEQ_DOWNLOAD_EX_FINISH_RESULT,
	SUBSEQ_DOWNLOAD_EX_SUCCESS_MESSAGE,
	

	SUBSEQ_SERVER_TRADE_CHECK,	
    SUBSEQ_SERVER_TRADECHECK_RESULT,
    SUBSEQ_SERVER_DOWNLOAD,		
    SUBSEQ_SERVER_DOWNLOAD_RESULT,	
	SUBSEQ_SERVER_TRADE_CHECK_END,


	SUBSEQ_NOW_SAVE_MES,
	SUBSEQ_SAVE,
	SUBSEQ_SAVE_RANDOM_WAIT,
	SUBSEQ_SAVE_WAIT,
	SUBSEQ_SAVE_LAST,

	SUBSEQ_TIMEOUT_SAVE,
    SUBSEQ_TIMEOUT_SAVE_WAIT,

	SUBSEQ_END,
	SUBSEQ_MES_WAIT,
	SUBSEQ_ERROR_MESSAGE,
	
	SUBSEQ_RETURN_TITLE_MESSAGE,

};



static int (*Functable[])( WORLDTRADE_WORK *wk ) = {
	Subseq_Start,				// SUBSEQ_START=0,
	Subseq_Main,             	// SUBSEQ_MAIN,
	Subseq_UploadStart,			// SUBSEQ_UPLOAD_START,
	Subseq_UploadResult,		// SUBSEQ_UPLOAD_RESULT,
	Subseq_UploadFinish,		// SUBSEQ_UPLOAD_FINISH,
	Subseq_UploadFinishResult,	// SUBSEQ_UPLOAD_FINISH_RESULT,
	Subseq_UploadSuccessMessage,// SUBSEQ_UPLOAD_SUCCESS_MESSAGE

	Subseq_DownloadStart,			// SUBSEQ_DOWNLOAD_START,
	Subseq_DownloadResult,			// SUBSEQ_DOWNLOAD_RESULT,
	Subseq_DownloadFinish,			// SUBSEQ_DOWNLOAD_FINISH,
	Subseq_DownloadFinishResult,	// SUBSEQ_DOWNLOAD_FINISH_RESULT,
	Subseq_DownloadSuccessMessage,	// SUBSEQ_DOWNLOAD_SUCCESS_MESSAGE

	Subseq_ExchangeStart,			// SUBSEQ_EXCHANGE_START,
	Subseq_ExchangeResult,			// SUBSEQ_EXCHANGE_RESULT,
	Subseq_ExchangeFinish,			// SUBSEQ_EXCHANGE_FINISH,
	Subseq_ExchangeFinishResult,	// SUBSEQ_EXCHANGE_FINISH_RESULT,
	Subseq_ExchangeSuccessMessage,	// SUBSEQ_EXCHANGE_SUCCESS_MESSAGE
	Subseq_ExchangeFailedMessage,	// SUBSEQ_EXCHANGE_FAILED_MESSAGE

	Subseq_DownloadExStart,			// SUBSEQ_DOWNLOAD_EX_START
	Subseq_DownloadExFinish,		// SUBSEQ_DOWNLOAD_EX_FINISH
	Subseq_DownloadExFinishResult,	// SUBSEQ_DOWNLOAD_EX_FINISH_RESULT
	Subseq_DownloadExSuccessMessage,// 


	Subseq_ServerTradeCheck,		// SUBSEQ_SERVER_TRADE_CHECK,	
	Subseq_ServerTradeCheckResult,	// 
	Subseq_ServerDownload,			// 
	Subseq_ServerDownloadResult,		// 
	Subseq_ServerTradeCheckEnd,		// SUBSEQ_SERVER_TRADE_CHECK_END,	

	SubSeq_NowSaveMessage,			// SUBSEQ_NOW_SAVE_MES,
	SubSeq_Save,					// SUBSEQ_SAVE,
	SubSeq_SaveRandomWait,			// SUBSEQ_SAVE_RANDOM_WAIT
	SubSeq_SaveWait,				// SUBSEQ_SAVE_WAIT,
	SubSeq_SaveLast,				// SUBSEQ_SAVE_LAST

	SubSeq_TimeoutSave,				// SUBSEQ_TIMEOUT_SAVE,
	SubSeq_TimeoutSaveWait,			// SUBSEQ_TIMEOUT_SAVE_WAIT


	Subseq_End,             	// SUBSEQ_END,
	Subseq_MessageWait,     	// SUBSEQ_MES_WAIT
	Subseq_ErrorMessage,		// SUBSEQ_ERROR_MES,
	Subseq_ReturnTitleMessage,	// SUBSEQ_RETURN_TITLE_MESSAGE,
};


#define POKEMON_RECV_OK						( 0 )
#define	POKEMON_ALL_FULL					( 1 )
#define POKEMON_NOT_FULL_BUT_MAIL_NORECV	( 2 )


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
int WorldTrade_Upload_Init(WORLDTRADE_WORK *wk, int seq)
{
	// ���[�N������
	InitWork( wk );
	
	// BG�ݒ�
	BgInit( wk->bgl );

	// BG�O���t�B�b�N�]��
	BgGraphicSet( wk );

	// BMPWIN�m��
	BmpWinInit( wk );

	// ���C�v�t�F�[�h�J�n
	WIPE_SYS_Start( WIPE_PATTERN_M, WIPE_TYPE_FADEIN, WIPE_TYPE_FADEIN, WIPE_FADE_BLACK, WORLDTRADE_WIPE_SPPED, 1, HEAPID_WORLDTRADE );
#ifdef GTS_FADE_OSP
	OS_Printf( "******************** worldtrade_upload.c [250] M ********************\n" );
#endif

	// Wifi�ʐM�A�C�R��
	WorldTrade_WifiIconAdd( wk );

	wk->subprocess_seq = SUBSEQ_START;



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
int WorldTrade_Upload_Main(WORLDTRADE_WORK *wk, int seq)
{
	int ret;

	// �ʐM��Ԃ��m�F���ăA�C�R���̕\����ς���
    WirelessIconEasy_SetLevel(WorldTrade_WifiLinkLevel());

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
int WorldTrade_Upload_End(WORLDTRADE_WORK *wk, int seq)
{
	FreeWork( wk );
	
	BmpWinDelete( wk );
	
	BgExit( wk->bgl );

	// ���̃T�u�v���Z�X��ݒ肷��
	WorldTrade_SubProcessUpdate( wk );
	
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

	// BG SYSTEM
	{	
		GF_BGL_SYS_HEADER BGsys_data = {
			GX_DISPMODE_GRAPHICS, GX_BGMODE_0, GX_BGMODE_0, GX_BG0_AS_2D,
		};
		GF_BGL_InitBG( &BGsys_data );
	}

	// ���C����ʃe�L�X�g��
	{	
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xf800, GX_BG_CHARBASE_0x00000, GX_BG_EXTPLTT_01,
			0, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( ini, GF_BGL_FRAME0_M, &TextBgCntDat, GF_BGL_MODE_TEXT );
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
		GF_BGL_ScrClear( ini, GF_BGL_FRAME1_M );
	}

	// ���C����ʔw�i��2
	{	
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xe800, GX_BG_CHARBASE_0x08000, GX_BG_EXTPLTT_01,
			1, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( ini, GF_BGL_FRAME2_M, &TextBgCntDat, GF_BGL_MODE_TEXT );
		GF_BGL_ScrClear( ini, GF_BGL_FRAME2_M );
	}



	// �T�u��ʕ�����0
	{	
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xf000, GX_BG_CHARBASE_0x10000, GX_BG_EXTPLTT_01,
			0, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( ini, GF_BGL_FRAME0_S, &TextBgCntDat, GF_BGL_MODE_TEXT );
		GF_BGL_ScrClear( ini, GF_BGL_FRAME0_S );

	}


	// �T�u��ʔw�i( ���̖ʂ�256�F )
	{	
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_256,
			GX_BG_SCRBASE_0xe000, GX_BG_CHARBASE_0x00000, GX_BG_EXTPLTT_01,
			2, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( ini, GF_BGL_FRAME1_S, &TextBgCntDat, GF_BGL_MODE_TEXT );
	}


	GF_BGL_ClearCharSet( GF_BGL_FRAME0_M, 32, 0, HEAPID_WORLDTRADE );
	GF_BGL_ClearCharSet( GF_BGL_FRAME0_S, 32, 0, HEAPID_WORLDTRADE );

	GF_Disp_GX_VisibleControl(  GX_PLANEMASK_OBJ, VISIBLE_ON );	//���C�����OBJ�ʂn�m
	GF_Disp_GXS_VisibleControl( GX_PLANEMASK_OBJ, VISIBLE_ON );	//�T�u���OBJ�ʂn�m

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
	GF_BGL_BGControlExit( ini, GF_BGL_FRAME2_M );
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

	// ���ʂa�f�p���b�g�]��
	ArcUtil_PalSet(    ARC_WORLDTRADE_GRA, NARC_worldtrade_conect_nclr, PALTYPE_MAIN_BG, 0, 16*3*2,  HEAPID_WORLDTRADE);
	
	// ��b�t�H���g�p���b�g�]��
	TalkFontPaletteLoad( PALTYPE_MAIN_BG, WORLDTRADE_TALKFONT_PAL*0x20, HEAPID_WORLDTRADE );
//	TalkFontPaletteLoad( PALTYPE_SUB_BG,  WORLDTRADE_TALKFONT_PAL*0x20, HEAPID_WORLDTRADE );

	// ��b�E�C���h�E�O���t�B�b�N�]��
	TalkWinGraphicSet(	bgl, GF_BGL_FRAME0_M, WORLDTRADE_MESFRAME_CHR, 
						WORLDTRADE_MESFRAME_PAL,  CONFIG_GetWindowType(wk->param->config), HEAPID_WORLDTRADE );

	MenuWinGraphicSet(	bgl, GF_BGL_FRAME0_M, WORLDTRADE_MENUFRAME_CHR,
						WORLDTRADE_MENUFRAME_PAL, 0, HEAPID_WORLDTRADE );

	// ��l�����o�ꂵ�ĂȂ��Ƃ��̓T�u��ʂ�\�����Ȃ�
	if(wk->demo_end==0){
		GF_BGL_VisibleSet( GF_BGL_FRAME0_S, VISIBLE_OFF );
		GF_BGL_VisibleSet( GF_BGL_FRAME1_S, VISIBLE_OFF );
		GF_Disp_GXS_VisibleControl( GX_PLANEMASK_OBJ, VISIBLE_OFF );	//�T�u���OBJ�ʂn�m
	}

	// �f������J�ڂ��Ă������͔w�i�����Ă���̂ōē]��
	if(wk->old_sub_process==WORLDTRADE_DEMO){
		WorldTrade_SubLcdBgGraphicSet( wk );
	}

}

#define SUB_TEXT_X		(  2 )
#define SUB_TEXT_Y		(  1 )
#define SUB_TEXT_SX		( 28 )
#define SUB_TEXT_SY		( 16 )

#define SUB_NUMBER_X	( 20 )
#define SUB_NUMBER_Y	( 21 )
#define SUB_NUMBER_SX	( 10 )
#define SUB_NUMBER_SY	(  2 )


#define TALK_MESSAGE_OFFSET	 ( WORLDTRADE_MENUFRAME_CHR + MENU_WIN_CGX_SIZ )
#define YESNO_OFFSET 		 ( TALK_MESSAGE_OFFSET + SUB_TEXT_SX*SUB_TEXT_SY )
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
static void BmpWinInit( WORLDTRADE_WORK *wk )
{
	// ---------- ���C����� ------------------

	// BG0��BMP�i��b�E�C���h�E�j�m��
	GF_BGL_BmpWinAdd(wk->bgl, &wk->MsgWin, GF_BGL_FRAME0_M,
		TALK_WIN_X, TALK_WIN_Y, TALK_WIN_SX, TALK_WIN_SY, WORLDTRADE_TALKFONT_PAL,  TALK_MESSAGE_OFFSET );
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
	wk->TalkString   = STRBUF_Create( TALK_MESSAGE_BUF_NUM, HEAPID_WORLDTRADE );

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
static void FreeWork( WORLDTRADE_WORK *wk )
{

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
static int Subseq_Start( WORLDTRADE_WORK *wk)
{
	// �a����̂��H�������̂��H�������͌������H

	switch(wk->sub_process_mode){
	case MODE_UPLOAD:
		// �������Ă��܂�
		Enter_MessagePrint( wk, wk->MsgManager, msg_gtc_01_025, 1, 0x0f0f );
		WorldTrade_SetNextSeq( wk, SUBSEQ_MES_WAIT, SUBSEQ_UPLOAD_START );
		break;
	case MODE_DOWNLOAD:
		// �����Ƃ��Ă��܂��B
		Enter_MessagePrint( wk, wk->MsgManager, msg_gtc_01_025, 1, 0x0f0f );
		WorldTrade_SetNextSeq( wk, SUBSEQ_MES_WAIT, SUBSEQ_DOWNLOAD_START );
		break;
	case MODE_EXCHANGE:
		// �������܂�
 		Enter_MessagePrint( wk, wk->MsgManager, msg_gtc_01_025, 1, 0x0f0f );
 		WorldTrade_SetNextSeq( wk, SUBSEQ_MES_WAIT, SUBSEQ_EXCHANGE_START );
		break;

		// �������I������|�P�������󂯎��܂�
	case MODE_DOWNLOAD_EX:
 		Enter_MessagePrint( wk, wk->MsgManager, msg_gtc_01_025, 1, 0x0f0f );
 		WorldTrade_SetNextSeq( wk, SUBSEQ_MES_WAIT, SUBSEQ_DOWNLOAD_EX_START );
		wk->sub_out_flg = 1;
		break;
		
	case MODE_SERVER_CHECK:	
		Enter_MessagePrint( wk, wk->MsgManager, msg_gtc_01_025, MSG_ALLPUT, 0x0f0f );
		// �u�悤�����݂�v�ɍs���O�ɃT�[�o�[�`�F�b�N���s��
		wk->subprocess_seq = SUBSEQ_SERVER_TRADE_CHECK;
		break;
	case MODE_POKEMON_EVO_SAVE:
		// �u�|�P�������|�[�g�������Ă��܂��B�ł񂰂������Ȃ��ł��������v
		Enter_MessagePrint( wk, wk->MsgManager, msg_gtc_15_004, 1, 0x0f0f );
		wk->sub_nextprocess = WORLDTRADE_TITLE;

		// �u�Z�[�u���Ă��܂��v�ƕ\�����Ă���Z�[�u
		wk->subprocess_seq  = SUBSEQ_NOW_SAVE_MES;
		break;
	default:
		OS_TPrintf("���[�h�w�肪�Ȃ�\n");
		GF_ASSERT(0);
	}
	// �K�����ԃA�C�R����ǉ�(upload.c�̒��ł͂P�񂵂���΂Ȃ��͂��j
	WorldTrade_TimeIconAdd(wk);

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
static int Subseq_UploadStart( WORLDTRADE_WORK *wk )
{
	
	// �J�X�^���{�[���̈���N���A
	PokePara_CustomBallDataInit( (POKEMON_PARAM*)wk->UploadPokemonData.postData.data );
	
	// �|�P�����f�[�^�A�b�v���[�h�J�n
	Dpw_Tr_UploadAsync( &wk->UploadPokemonData );

	OS_TPrintf("Dpw Trade �f�[�^�A�b�v���[�h�J�n\n");

	// �T�[�o�[��Ԋm�F�҂���
	wk->subprocess_seq = SUBSEQ_UPLOAD_RESULT;
	
	SetSaveNextSequence( wk, SUBSEQ_UPLOAD_FINISH, SUBSEQ_UPLOAD_SUCCESS_MESSAGE);

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
static int Subseq_UploadResult( WORLDTRADE_WORK *wk )
{
	int result;
	if ((result=Dpw_Tr_IsAsyncEnd())){
		s32 result = Dpw_Tr_GetAsyncResult();
		switch (result){
		case 0:		// ����ɓ��삵�Ă���
			OS_TPrintf(" upload is right!\n");

			// �f�[�^�ޔ�
			UploadPokemonDataDelete( wk, 1 );

			wk->subprocess_seq = SUBSEQ_SAVE;
			break;
		case DPW_TR_ERROR_SERVER_FULL:
			// �T�[�o�[�����t�Ȃ̂ŃA�N�Z�X�ł��܂��񁨏I��
			OS_TPrintf(" server full.\n");
			wk->ConnectErrorNo = result;
			wk->subprocess_seq = SUBSEQ_ERROR_MESSAGE;
			break;
		case DPW_TR_ERROR_ILLEGAL_DATA:
		case DPW_TR_ERROR_CHEAT_DATA:
		case DPW_TR_ERROR_NG_POKEMON_NAME :
		case DPW_TR_ERROR_NG_PARENT_NAME :
		case DPW_TR_ERROR_NG_MAIL_NAME :
		case DPW_TR_ERROR_NG_OWNER_NAME:
		case DPW_TR_ERROR_ILLIGAL_REQUEST :
			// �u���̃|�P�����͂������鎖���ł��܂���v���^�C�g����
			wk->ConnectErrorNo = result;
			wk->subprocess_seq = SUBSEQ_RETURN_TITLE_MESSAGE;
			break;		
		case DPW_TR_ERROR_CANCEL :
		case DPW_TR_ERROR_DATA_TIMEOUT :
			// ������ŗa���邩�m�F���Ă��炱���R�O���O�|�P�����͂���Ȃ̂��H
			wk->ConnectErrorNo = result;
			wk->subprocess_seq = SUBSEQ_RETURN_TITLE_MESSAGE;
			break;

		case DPW_TR_ERROR_SERVER_TIMEOUT :
		case DPW_TR_ERROR_DISCONNECTED:	
			// �uGTS�̂����ɂ�ɂ����ς����܂����v
		case DPW_TR_ERROR_FAILURE :
			// �T�[�o�[�ƒʐM�ł��܂��񁨏I��
			OS_TPrintf(" upload error. %d \n", result);
			wk->ConnectErrorNo = result;
			wk->subprocess_seq = SUBSEQ_ERROR_MESSAGE;
			break;
		case DPW_TR_ERROR_FATAL:			//!< �ʐM�v���I�G���[�B�d���̍ē������K�v�ł�
			// ���ӂ��Ƃ΂�
			CommFatalErrorFunc_NoNumber();
			break;
		}
		
	}
	return SEQ_MAIN;
}


//------------------------------------------------------------------
/**
 * @brief   �T�[�o�[�ɃA�b�v���[�h�����f�[�^��L���ɂ���
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int Subseq_UploadFinish( WORLDTRADE_WORK *wk )
{
	Dpw_Tr_UploadFinishAsync();
	
	wk->subprocess_seq = SUBSEQ_UPLOAD_FINISH_RESULT;
	
	// �����ɗ��Ă��鎞�_�ŃZ�[�u�ɂ͐������Ă���̂ŁADepsitFlag�𗧂ĂĂ����Ȃ���
	// �ʐM�G���[�ɂȂ������ɂ�����x�u�a����v���\������Ă��܂�
	wk->DepositFlag = 1;
	
	return SEQ_MAIN;
}


//------------------------------------------------------------------
/**
 * $brief   �f�[�^�L�������҂�
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int Subseq_UploadFinishResult( WORLDTRADE_WORK *wk )
{
	if (Dpw_Tr_IsAsyncEnd()){
		s32 result = Dpw_Tr_GetAsyncResult();
#ifdef DEBUG_UPLOAD_ERROR
		result = DPW_TR_ERROR_FAILURE;
#endif
		switch(result){
		case 0:		// ����ɓ��삵�Ă���
			// �A�b�v���[�h�����B�Z�[�u����B
			OS_TPrintf(" upload success.\n");
			wk->subprocess_seq = SUBSEQ_SAVE_LAST;
			break;

		case DPW_TR_ERROR_CANCEL :
		case DPW_TR_ERROR_DATA_TIMEOUT :
			// ������ŗa���邩�m�F���Ă��炱���R�O���O�|�P�����͂���Ȃ̂��H
			wk->ConnectErrorNo = result;
			wk->subprocess_seq = SUBSEQ_RETURN_TITLE_MESSAGE;
			break;

		case DPW_TR_ERROR_SERVER_FULL:
			// �T�[�o�[�����t�Ȃ̂ŃA�N�Z�X�ł��܂��񁨏I��
			// �i��������́H�j
			OS_TPrintf(" server full.\n");
		case DPW_TR_ERROR_NO_DATA:
		case DPW_TR_ERROR_ILLIGAL_REQUEST :
			// �u���̃|�P�����͂������鎖���ł��܂���v���^�C�g����
		case DPW_TR_ERROR_SERVER_TIMEOUT :
		case DPW_TR_ERROR_DISCONNECTED:	
		case DPW_TR_ERROR_FAILURE :
			// �uGTS�̂����ɂ�ɂ����ς����܂����v
			// �T�[�o�[�ƒʐM�ł��܂��񁨏I��
			OS_TPrintf(" upload error. %d \n", result);
//			wk->ConnectErrorNo = result;
//			wk->subprocess_seq = SUBSEQ_ERROR_MESSAGE;
			// �����͂������ɖ߂��Ă͂����Ȃ��B������ʐM�G���[
			CommStateSetError(COMM_ERROR_RESET_OTHER);
			break;

		case DPW_TR_ERROR_FATAL:			//!< �ʐM�v���I�G���[�B�d���̍ē������K�v�ł�
			// ���ӂ��Ƃ΂�
			CommFatalErrorFunc_NoNumber();
			break;
		}

	}
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
static int Subseq_DownloadStart( WORLDTRADE_WORK *wk )
{
	
	// �|�P�����f�[�^�_�E�����[�h�J�n

	Dpw_Tr_DownloadAsync( &wk->UploadPokemonData );
	OS_TPrintf("Dpw Trade �f�[�^�_�E�����[�h�J�n\n");

	// �T�[�o�[��Ԋm�F�҂���
	wk->subprocess_seq = SUBSEQ_DOWNLOAD_RESULT;

	// �Z�[�u���݃V�[�P���X�\��
	SetSaveNextSequence( wk, SUBSEQ_DOWNLOAD_FINISH, SUBSEQ_DOWNLOAD_SUCCESS_MESSAGE);


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
static int Subseq_DownloadResult( WORLDTRADE_WORK *wk )
{
	if (Dpw_Tr_IsAsyncEnd()){
		s32 result = Dpw_Tr_GetAsyncResult();
		switch (result){
		case 0:		// ����ɓ��삵�Ă���

			// ����������|�P�����������������Ă�����Ђ��Ƃ����|�P�����f�[�^�͊Ԉ���Ă���̂ŕ���
			// ������x�T�[�o�[�`�F�b�N�ɖ߂�
			if(wk->UploadPokemonData.isTrade){
				OS_TPrintf(" download is right! but traded\n");

				wk->subprocess_seq = SUBSEQ_SERVER_TRADE_CHECK;
			}else{
				OS_TPrintf(" download is right!\n");
				// �f�[�^����
				DownloadPokemonDataAdd( wk, (POKEMON_PARAM*)wk->UploadPokemonData.postData.data,
										WorldTradeData_GetBoxNo( wk->param->worldtrade_data ), 
										wk->UploadPokemonData.isTrade );
				wk->subprocess_seq = SUBSEQ_SAVE;
			}


			break;

		// �f�[�^�������i���Ȃ肨�������󋵁A�������͗��Ƃ����̂Ɂj
		case DPW_TR_ERROR_NO_DATA :	
			OS_TPrintf(" download server stop service.\n");
			wk->subprocess_seq = SUBSEQ_ERROR_MESSAGE;
			break;

		// 1�����߂��Ă��܂���
		case DPW_TR_ERROR_DATA_TIMEOUT :
			OS_TPrintf(" server full.\n");
			wk->subprocess_seq = SUBSEQ_ERROR_MESSAGE;
			break;

	// -----------------------------------------
	// ���ʃG���[����
	// -----------------------------------------
		case DPW_TR_ERROR_CANCEL :
			wk->ConnectErrorNo = result;
			wk->subprocess_seq = SUBSEQ_RETURN_TITLE_MESSAGE;
			break;

		case DPW_TR_ERROR_FAILURE :
			// �uGTS�̂����ɂ�ɂ����ς����܂����v
		case DPW_TR_ERROR_SERVER_TIMEOUT :
		case DPW_TR_ERROR_DISCONNECTED:	
			// �T�[�o�[�ƒʐM�ł��܂��񁨏I��
			OS_TPrintf(" upload error. %d \n", result);
			wk->ConnectErrorNo = result;
			wk->subprocess_seq = SUBSEQ_ERROR_MESSAGE;
			break;
		case DPW_TR_ERROR_FATAL:			//!< �ʐM�v���I�G���[�B�d���̍ē������K�v�ł�
			// ���ӂ��Ƃ΂�
			CommFatalErrorFunc_NoNumber();
			break;
	// -----------------------------------------
		}
		
	}
	return SEQ_MAIN;
}


//------------------------------------------------------------------
/**
 * @brief   �T�[�o�[����f�[�^���폜����
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int Subseq_DownloadFinish( WORLDTRADE_WORK *wk )
{
	Dpw_Tr_ReturnAsync();
	OS_TPrintf("-------------------------------------Dpw_Tr_ReturnAsync��т���\n");
	
	wk->subprocess_seq = SUBSEQ_DOWNLOAD_FINISH_RESULT;
	
	return SEQ_MAIN;
}


//------------------------------------------------------------------
/**
 * $brief   �f�[�^�L�������҂�
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int Subseq_DownloadFinishResult( WORLDTRADE_WORK *wk )
{
	if (Dpw_Tr_IsAsyncEnd()){
		s32 result = Dpw_Tr_GetAsyncResult();
		switch(result){
		case 0:
			// �T�[�o�[����_�E�����[�h�����B�Z�[�u����B
			OS_TPrintf(" download success.\n");
			wk->subprocess_seq = SUBSEQ_SAVE_LAST;

			break;
		// �f�[�^�������i���Ȃ肨�������󋵁A�������͗��Ƃ����̂Ɂj
		case DPW_TR_ERROR_NO_DATA :	
			OS_TPrintf(" download server stop service.\n");

		// 1�����߂��Ă��܂���(���Ȃ��悤�ȋC������j
		case DPW_TR_ERROR_DATA_TIMEOUT :
			OS_TPrintf(" server full.\n");

		// �Ō�̂߂��s�����Ƃ�����������������Ă��܂����B
		// �G���[���N�������ɂ��ĊO�ɂ����Ă��܂������ǂ��Ă���Ό������������Ă܂��B
		case DPW_TR_ERROR_ILLIGAL_REQUEST:
			CommStateSetError(COMM_ERROR_RESET_GTS);
			break;
	// -----------------------------------------
	// ���ʃG���[����
	// -----------------------------------------
		case DPW_TR_ERROR_CANCEL :

		case DPW_TR_ERROR_FAILURE :
			// �uGTS�̂����ɂ�ɂ����ς����܂����v
		case DPW_TR_ERROR_SERVER_TIMEOUT :
		case DPW_TR_ERROR_DISCONNECTED:	
			// �T�[�o�[�ƒʐM�ł��܂��񁨏I��
			OS_TPrintf(" upload error. %d \n", result);

			// �Z�[�u���قƂ�Ǐ������܂�Ă���󋵂ł̓f�[�^�����ɖ߂��Ȃ�
			// ������ʐM�G���[��
			CommStateSetError(COMM_ERROR_RESET_OTHER);
			break;
		case DPW_TR_ERROR_FATAL:			//!< �ʐM�v���I�G���[�B�d���̍ē������K�v�ł�
			// ���ӂ��Ƃ΂�
			CommFatalErrorFunc_NoNumber();
			break;
	// -----------------------------------------

		}

	}
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
static int Subseq_ExchangeStart( WORLDTRADE_WORK *wk )
{

	// �J�X�^���{�[���̈���N���A
	PokePara_CustomBallDataInit( (POKEMON_PARAM*)wk->UploadPokemonData.postData.data );

	
	// �|�P�����f�[�^�����J�n
	Dpw_Tr_TradeAsync ( wk->DownloadPokemonData[wk->TouchTrainerPos].id,
						&wk->UploadPokemonData,
						&wk->ExchangePokemonData );

	OS_TPrintf("Dpw Trade �f�[�^�����J�n id = %08x\n", wk->DownloadPokemonData[wk->TouchTrainerPos].id);


	// �Z�[�u���݃V�[�P���X�\��
	SetSaveNextSequence( wk, SUBSEQ_EXCHANGE_FINISH, SUBSEQ_EXCHANGE_SUCCESS_MESSAGE);

	// �T�[�o�[��Ԋm�F�҂���
	wk->subprocess_seq = SUBSEQ_EXCHANGE_RESULT;

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
static int Subseq_ExchangeResult( WORLDTRADE_WORK *wk )
{
	int result;
	if ((result=Dpw_Tr_IsAsyncEnd())){
		s32 result = Dpw_Tr_GetAsyncResult();
		switch (result){
		case 0:		// ����ɓ��삵�Ă���
			OS_TPrintf(" exchange is right!\n");
			wk->subprocess_seq = SUBSEQ_SAVE;

			UploadPokemonDataDelete( wk, 0 );
			ExchangePokemonDataAdd(  wk, (POKEMON_PARAM*)wk->ExchangePokemonData.postData.data,
										wk->BoxTrayNo);

			// �n���V���o�^
			WifiHistoryDataSet( wk->param->wifihistory, &wk->ExchangePokemonData );

			// �X�R�A���Z
			RECORD_Score_Add( wk->param->record, SCORE_ID_WORLD_TRADE );

			// �`���m�[�g�f�[�^�o�^����
			SetFnoteData( wk->param->fnote,  &wk->ExchangePokemonData );

			// ���R�[�h�p����
			RECORD_Inc( wk->param->record, RECID_WIFI_TRADE );


			break;

		// �g���[�h���s���s
		case DPW_TR_ERROR_ILLIGAL_REQUEST :	
			OS_TPrintf(" exchange is failed.\n");
			wk->ConnectErrorNo = result;
			wk->subprocess_seq = SUBSEQ_EXCHANGE_FAILED_MESSAGE;
			break;

		// �s���f�[�^������
		case DPW_TR_ERROR_ILLEGAL_DATA:
		case DPW_TR_ERROR_CHEAT_DATA:
		case DPW_TR_ERROR_NG_POKEMON_NAME :
		case DPW_TR_ERROR_NG_PARENT_NAME :
		case DPW_TR_ERROR_NG_MAIL_NAME :
		case DPW_TR_ERROR_NG_OWNER_NAME:
			// �u���̃|�P�����͂������鎖���ł��܂���v���^�C�g����
			wk->ConnectErrorNo = result;
			wk->subprocess_seq = SUBSEQ_RETURN_TITLE_MESSAGE;
			break;		
	// -----------------------------------------
	// ���ʃG���[����
	// -----------------------------------------
		case DPW_TR_ERROR_CANCEL :
			// �uGTS�̂����ɂ�ɂ����ς����܂����v���^�C�g����
			wk->ConnectErrorNo = result;
			wk->subprocess_seq = SUBSEQ_RETURN_TITLE_MESSAGE;
			break;

		case DPW_TR_ERROR_SERVER_TIMEOUT :
		case DPW_TR_ERROR_DISCONNECTED:	
		case DPW_TR_ERROR_FAILURE :
			// �T�[�o�[�ƒʐM�ł��܂��񁨏I��
			OS_TPrintf(" upload error. %d \n", result);
			wk->ConnectErrorNo = result;
			wk->subprocess_seq = SUBSEQ_ERROR_MESSAGE;
			break;
		case DPW_TR_ERROR_FATAL:			//!< �ʐM�v���I�G���[�B�d���̍ē������K�v�ł�
			// ���ӂ��Ƃ΂�
			CommFatalErrorFunc_NoNumber();
			break;
	// -----------------------------------------
		}
		
	}
	return SEQ_MAIN;
}


//------------------------------------------------------------------
/**
 * @brief   �T�[�o�[����f�[�^���폜����
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int Subseq_ExchangeFinish( WORLDTRADE_WORK *wk )
{
	Dpw_Tr_TradeFinishAsync();
	OS_TPrintf("�����I�������J�n\n");
	
	wk->subprocess_seq = SUBSEQ_EXCHANGE_FINISH_RESULT;
	
	return SEQ_MAIN;
}


//------------------------------------------------------------------
/**
 * $brief   �f�[�^�L�������҂�
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int Subseq_ExchangeFinishResult( WORLDTRADE_WORK *wk )
{
	if (Dpw_Tr_IsAsyncEnd()){
		s32 result = Dpw_Tr_GetAsyncResult();
		switch(result){
		case 0:
			OS_TPrintf(" exchange success.\n");
			wk->subprocess_seq = SUBSEQ_SAVE_LAST;

			break;

		// ��������Ă��܂���
		case DPW_TR_ERROR_ILLIGAL_REQUEST:
			CommStateSetError(COMM_ERROR_RESET_GTS);
			break;
	// -----------------------------------------
	// ���ʃG���[����
	// -----------------------------------------
		case DPW_TR_ERROR_CANCEL :
			// �uGTS�̂����ɂ�ɂ����ς����܂����v���^�C�g����

		case DPW_TR_ERROR_SERVER_TIMEOUT :
		case DPW_TR_ERROR_DISCONNECTED:	
		case DPW_TR_ERROR_FAILURE :
			// �T�[�o�[�ƒʐM�ł��܂��񁨏I��
			OS_TPrintf(" upload error. %d \n", result);
	
			// �X�X���܂ŃZ�[�u���������܂ꂽ�󋵂ł͌��ɖ߂��Ȃ��̂�
			// ������ʐM�G���[��
			CommStateSetError(COMM_ERROR_RESET_OTHER);
			break;

			break;
		case DPW_TR_ERROR_FATAL:			//!< �ʐM�v���I�G���[�B�d���̍ē������K�v�ł�
			// ���ӂ��Ƃ΂�
			CommFatalErrorFunc_NoNumber();
			break;
	// -----------------------------------------
		}

	}
	return SEQ_MAIN;
}




//------------------------------------------------------------------
/**
 * @brief   �������������Ă��邩�m�F����
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int Subseq_ServerTradeCheck( WORLDTRADE_WORK *wk )
{
	Dpw_Tr_GetUploadResultAsync( &wk->UploadPokemonData );

	OS_Printf("�T�[�o�[��Ԋm�F�J�n\n");

	wk->subprocess_seq  = SUBSEQ_SERVER_TRADECHECK_RESULT;

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
static int Subseq_ServerTradeCheckResult( WORLDTRADE_WORK *wk )
{
	// �T�[�o�[�₢���킹�I���҂�
	if (Dpw_Tr_IsAsyncEnd()){
		s32 result = Dpw_Tr_GetAsyncResult();
		switch (result){
		// �����͐������Ă��Ȃ������̂ŁA�����̃f�[�^�擾��
		case 0:
//			OS_TPrintf(" no exchange.\n");
			wk->subprocess_seq = SUBSEQ_SERVER_DOWNLOAD;

#ifdef PM_DEBUG
			{
				Dpw_Tr_Data *dtd = &wk->UploadPokemonData;

				OS_Printf( "TrainerId = %05d,  nation = %d, area = %d\n", dtd->trainerID, dtd->countryCode, dtd->localCode);
				OS_Printf( "Version   = %d,  language = %d, \n", dtd->versionCode, dtd->langCode);
				OS_Printf( "postData  No = %d,  gender = %d, level = %d\n", dtd->postSimple.characterNo, dtd->postSimple.gender, dtd->postSimple.level);
				OS_Printf( "WantData  No = %d,  gender = %d, level min = %d max = %d\n", 
						dtd->wantSimple.characterNo, dtd->wantSimple.gender, dtd->wantSimple.level_min,dtd->wantSimple.level_max);
			}
#endif
			// �a���Ă��邩�H
			break;

		// �����͐������Ă���
		case 1:
			OS_TPrintf(" download exchange pokemon on sever.\n");
			// �T�[�o�[�Ƀ|�P������a���Ă���̂͊m���B
			wk->DepositFlag = 1;

#ifdef PM_DEBUG
			{
				Dpw_Tr_Data *dtd = &wk->UploadPokemonData;
	
				OS_Printf( "TrainerId = %05d,  nation = %d, area = %d\n", dtd->trainerID, dtd->countryCode, dtd->localCode);
				OS_Printf( "Version   = %d,  language = %d, \n", dtd->versionCode, dtd->langCode);
				OS_Printf( "postData  No = %d,  gender = %d, level = %d\n", dtd->postSimple.characterNo, dtd->postSimple.gender, dtd->postSimple.level);
				OS_Printf( "WantData  No = %d,  gender = %d, level min = %d max = %d\n", 
						dtd->wantSimple.characterNo, dtd->wantSimple.gender, dtd->wantSimple.level_min,dtd->wantSimple.level_max);
			}
#endif
			switch(MyPokemonPocketFullCheck(wk, &wk->UploadPokemonData)){
			// �󂫂�����
			case POKEMON_ALL_FULL:
				WorldTrade_TimeIconDel(wk);
		 		Enter_MessagePrint( wk, wk->MsgManager, msg_gtc_01_030, 1, 0x0f0f );
 				WorldTrade_SetNextSeq( wk, SUBSEQ_MES_WAIT, SUBSEQ_SERVER_TRADE_CHECK_END );
				break;
			// ���[�����󂯎��Ȃ�
			case POKEMON_NOT_FULL_BUT_MAIL_NORECV:
				WorldTrade_TimeIconDel(wk);
		 		Enter_MessagePrint( wk, wk->MsgManager, msg_gtc_01_036, 1, 0x0f0f );
 				WorldTrade_SetNextSeq( wk, SUBSEQ_MES_WAIT, SUBSEQ_SERVER_TRADE_CHECK_END );
				break;
			// �󂯎���
			case POKEMON_RECV_OK:
#ifdef REPAIR_060804
				// ���������o�O�C�����Ă���ق�
				wk->subprocess_seq   = SUBSEQ_DOWNLOAD_EX_START;
				wk->sub_out_flg = 1;
#else
				WorldTrade_SubProcessChange( wk, WORLDTRADE_UPLOAD, MODE_DOWNLOAD_EX );
				wk->subprocess_seq  = SUBSEQ_END;
#endif

				break;
			}
			break;
		// �|�P�������������Ă���ꍇ�̓^�C���A�E�g���������Ă��܂��Ă���i�Ă����ɖ߂��j
		case DPW_TR_ERROR_NO_DATA :	
			OS_TPrintf(" no data on sever.\n");
			wk->DepositFlag = 0;
			if(WorldTradeData_GetFlag(wk->param->worldtrade_data)){
				POKEMON_PARAM *pp = PokemonParam_AllocWork(HEAPID_WORLDTRADE);
				WorldTradeData_GetPokemonData( wk->param->worldtrade_data, pp );
				WORDSET_RegisterPokeNickName( wk->WordSet, 0, PPPPointerGet(pp) );

				wk->error_mes_no   = msg_gtc_01_003;
				wk->subprocess_seq = SUBSEQ_TIMEOUT_SAVE;
				
				// �ۑ����Ă������|�P������߂�
				DownloadPokemonDataAdd( wk, pp, WorldTradeData_GetBoxNo( wk->param->worldtrade_data ), 0 );
				// �a���Ă���t���O������
				WorldTradeData_SetFlag(wk->param->worldtrade_data, 0);
				sys_FreeMemoryEz(pp);
			}else{
				// �T�[�o�[�m�F�����I����̍s�����ݒ�
				AfterTradeCheck_ProcessControl( wk );
			}
			break;

		// �a�����|�P����������������Ƀ^�C���A�E�g�����B���̂܂܍폜
		case DPW_TR_ERROR_DATA_TIMEOUT :
			OS_TPrintf(" your data on server is timeout.\n");

			// �T�[�o�[�m�F�����I����̍s�����ݒ�
//			AfterTradeCheck_ProcessControl( wk );

			wk->DepositFlag = 0;
			// ��Ηa���Ă���͂������ǔO�̂��߁A�t���O�m�F
			if(WorldTradeData_GetFlag(wk->param->worldtrade_data)){
				POKEMON_PARAM *pp = PokemonParam_AllocWork(HEAPID_WORLDTRADE);
				WorldTradeData_GetPokemonData( wk->param->worldtrade_data, pp );
				WORDSET_RegisterPokeNickName( wk->WordSet, 0, PPPPointerGet(pp) );

				wk->error_mes_no   = msg_gtc_01_004;
				wk->subprocess_seq = SUBSEQ_TIMEOUT_SAVE;
				
				// �a���Ă���t���O������
				WorldTradeData_SetFlag(wk->param->worldtrade_data, 0);

				sys_FreeMemoryEz(pp);
			}
			break;
	// -----------------------------------------
	// ���ʃG���[����
	// -----------------------------------------
		case DPW_TR_ERROR_CANCEL :
		case DPW_TR_ERROR_FAILURE :
			// ���̏ꍇ�̓^�C�g���ɖ߂����A�����Ŏ��s�����
			// ���̌�̑�������s����\���������̂ŁB
		case DPW_TR_ERROR_SERVER_TIMEOUT :
		case DPW_TR_ERROR_DISCONNECTED:	
			// �T�[�o�[�ƒʐM�ł��܂��񁨏I��
			OS_TPrintf(" upload error. %d \n", result);
			wk->ConnectErrorNo = result;
			wk->subprocess_seq = SUBSEQ_ERROR_MESSAGE;
			break;
		case DPW_TR_ERROR_FATAL:			//!< �ʐM�v���I�G���[�B�d���̍ē������K�v�ł�
			// ���ӂ��Ƃ΂�
			ComErrorWarningResetCall(HEAPID_BASE_APP,COMM_ERRORTYPE_POWEROFF,0);
			break;
	// -----------------------------------------
		}
		

	}
	return SEQ_MAIN;
}

//------------------------------------------------------------------
/**
 * @brief   �󂯎�邱�Ƃ��ł��Ȃ������̂Ń^�C�g���ɂ��ǂ�
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int Subseq_ServerTradeCheckEnd( WORLDTRADE_WORK *wk )
{
	// �|�P�������󂯎�邱�Ƃ��ł��Ȃ��̂ŁA�^�C�g���ɂ��ǂ�
	WorldTrade_SubProcessChange( wk, WORLDTRADE_TITLE, 0 );
	wk->subprocess_seq = SUBSEQ_END;

	return SEQ_MAIN;
}


//------------------------------------------------------------------
/**
 * @brief   ���ɃT�[�o�[�ɗa���Ă��邩�m�F
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int Subseq_ServerDownload( WORLDTRADE_WORK *wk )
{
	Dpw_Tr_DownloadAsync( &wk->UploadPokemonData );

	wk->subprocess_seq  = SUBSEQ_SERVER_DOWNLOAD_RESULT;

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
static int Subseq_ServerDownloadResult( WORLDTRADE_WORK *wk )
{
	// �T�[�o�[�₢���킹�I���҂�
	if (Dpw_Tr_IsAsyncEnd()){
		s32 result = Dpw_Tr_GetAsyncResult();
		switch (result){
		// �a���Ă���|�P�����̃f�[�^���擾����
		case 0:
			OS_TPrintf(" download data on sever.\n");
			wk->DepositFlag = 1;

			{
				Dpw_Tr_Data *dtd = &wk->UploadPokemonData;

				OS_Printf( "TrainerId = %05d,  nation = %d, area = %d\n", dtd->trainerID, dtd->countryCode, dtd->localCode);
				OS_Printf( "Version   = %d,  language = %d, \n", dtd->versionCode, dtd->langCode);
				OS_Printf( "postData  No = %d,  gender = %d, level = %d\n", dtd->postSimple.characterNo, dtd->postSimple.gender, dtd->postSimple.level);
				OS_Printf( "WantData  No = %d,  gender = %d, level min = %d max = %d\n", 
						dtd->wantSimple.characterNo, dtd->wantSimple.gender, dtd->wantSimple.level_min,dtd->wantSimple.level_max);

			}
			break;
		// �|�P�����͗a�����Ă��Ȃ�
		case DPW_TR_ERROR_NO_DATA :	
			OS_TPrintf(" no data on sever.\n");
			wk->DepositFlag = 0;
			break;
		// �a�����|�P�������^�C���A�E�g���Ă��܂����̂ŁA�B���Ă���|�P�����𕜊�������
		case DPW_TR_ERROR_DATA_TIMEOUT :
			OS_TPrintf(" your data on server is timeout.\n");
			break;
	// -----------------------------------------
	// ���ʃG���[����
	// -----------------------------------------
		case DPW_TR_ERROR_CANCEL :
			wk->ConnectErrorNo = result;
			wk->subprocess_seq = SUBSEQ_RETURN_TITLE_MESSAGE;
			break;

		case DPW_TR_ERROR_FAILURE :
			// �uGTS�̂����ɂ�ɂ����ς����܂����v
		case DPW_TR_ERROR_SERVER_TIMEOUT :
		case DPW_TR_ERROR_DISCONNECTED:	
			// �T�[�o�[�ƒʐM�ł��܂��񁨏I��
			OS_TPrintf(" upload error. %d \n", result);
			wk->ConnectErrorNo = result;
			wk->subprocess_seq = SUBSEQ_ERROR_MESSAGE;
			break;
		case DPW_TR_ERROR_FATAL:			//!< �ʐM�v���I�G���[�B�d���̍ē������K�v�ł�
			// ���ӂ��Ƃ΂�
			CommFatalErrorFunc_NoNumber();
			break;
	// -----------------------------------------

		}

		// �T�[�o�[�m�F�����I����̍s�����ݒ�
		AfterTradeCheck_ProcessControl( wk );

	}
	return SEQ_MAIN;
}



//------------------------------------------------------------------
/**
 * @brief   �T�[�o�[�m�F�����I����̖߂���ݒ�
 *
 * @param   wk		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void AfterTradeCheck_ProcessControl( WORLDTRADE_WORK *wk )
{
	switch( wk->sub_returnprocess ){
	case WORLDTRADE_TITLE:
		// GTC�������ʂ�
		WorldTrade_SubProcessChange( wk, WORLDTRADE_TITLE, 0 );
		wk->subprocess_seq  = SUBSEQ_END;
		break;

	// �����̃|�P�����m�F��ʂ�	
	case WORLDTRADE_MYPOKE:
		WorldTrade_SubProcessChange( wk, WORLDTRADE_MYPOKE, MODE_VIEW );
		wk->subprocess_seq  = SUBSEQ_END;
		break;
	}

}


//------------------------------------------------------------------
/**
 * @brief   �����ς݃|�P�������T�[�o�[����폜����
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int Subseq_DownloadExStart( WORLDTRADE_WORK *wk)
{

	// �f�[�^����
	DownloadPokemonDataAdd( wk, (POKEMON_PARAM*)wk->UploadPokemonData.postData.data,
							WorldTradeData_GetBoxNo( wk->param->worldtrade_data ), 
							wk->UploadPokemonData.isTrade );

	// �n���V���o�^
	WifiHistoryDataSet( wk->param->wifihistory, &wk->UploadPokemonData );

	// �X�R�A���Z
	RECORD_Score_Add( wk->param->record, SCORE_ID_WORLD_TRADE );

	// �`���m�[�g�f�[�^�o�^����
	SetFnoteData( wk->param->fnote,  &wk->UploadPokemonData );

	// ���R�[�h�p����
	RECORD_Inc( wk->param->record, RECID_WIFI_TRADE );

	// ������������ɂ���
	WorldTradeData_SetFlag( wk->param->worldtrade_data, 0 );

	// �Z�[�u��
	wk->subprocess_seq = SUBSEQ_SAVE;

	// �Z�[�u���݃V�[�P���X�\��
	SetSaveNextSequence( wk, SUBSEQ_DOWNLOAD_EX_FINISH, SUBSEQ_DOWNLOAD_SUCCESS_MESSAGE);
	
	return SEQ_MAIN;
	
}

//------------------------------------------------------------------
/**
 * @brief   �����ς݃f�[�^���菈���J�n
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int Subseq_DownloadExFinish( WORLDTRADE_WORK *wk )
{

	// �����ς݃|�P�����T�[�o�[����폜����
	Dpw_Tr_DeleteAsync();
	OS_TPrintf("-------------------------------------Dpw_Tr_DeleteAsync��т���\n");
	OS_TPrintf("�_�E�����[�h�I�������J�n\n");

	// �Z�[�u��
	wk->subprocess_seq = SUBSEQ_DOWNLOAD_EX_FINISH_RESULT;
	
	return SEQ_MAIN;
}


//------------------------------------------------------------------
/**
 * @brief   ���ʑ҂�
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int Subseq_DownloadExFinishResult( WORLDTRADE_WORK *wk)
{
	if (Dpw_Tr_IsAsyncEnd()){
		s32 result = Dpw_Tr_GetAsyncResult();
		switch (result){
		case 0:		// ����ɓ��삵�Ă���

			// ����������|�P�����������������Ă�����Ђ��Ƃ����|�P�����f�[�^�͊Ԉ���Ă���̂ŕ���
			// ������x�T�[�o�[�`�F�b�N�ɖ߂�
			OS_TPrintf(" downloadEx is right!\n");

			wk->subprocess_seq = SUBSEQ_SAVE_LAST;
			break;

		// �f�[�^�������i���Ȃ肨�������󋵁A�������͗��Ƃ����̂Ɂj
		case DPW_TR_ERROR_NO_DATA :	
			OS_TPrintf(" download server stop service.\n");
			CommStateSetError(COMM_ERROR_RESET_GTS);
			break;

		// 1�����߂��Ă��܂���
		case DPW_TR_ERROR_DATA_TIMEOUT :
			OS_TPrintf(" server full.\n");


	// -----------------------------------------
	// ���ʃG���[����
	// -----------------------------------------
		case DPW_TR_ERROR_CANCEL :
			wk->ConnectErrorNo = result;

		case DPW_TR_ERROR_FAILURE :
			// �uGTS�̂����ɂ�ɂ����ς����܂����v
		case DPW_TR_ERROR_SERVER_TIMEOUT :
		case DPW_TR_ERROR_DISCONNECTED:	
			// �T�[�o�[�ƒʐM�ł��܂��񁨏I��
			OS_TPrintf(" upload error. %d \n", result);

			// �X�X���܂ŃZ�[�u���������܂ꂽ�󋵂ł͌��ɖ߂��Ȃ��̂�
			// ������ʐM�G���[��
			CommStateSetError(COMM_ERROR_RESET_OTHER);

			break;
		case DPW_TR_ERROR_FATAL:			//!< �ʐM�v���I�G���[�B�d���̍ē������K�v�ł�
			// ���ӂ��Ƃ΂�
			CommFatalErrorFunc_NoNumber();
			break;
	// -----------------------------------------
		}
		
	}
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
static int Subseq_Main( WORLDTRADE_WORK *wk)
{


	return SEQ_MAIN;
}



//------------------------------------------------------------------
/**
 * @brief   ��������̂ɐ������܂������b�Z�[�W
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int Subseq_UploadSuccessMessage( WORLDTRADE_WORK *wk )
{
//	Enter_MessagePrint( wk, wk->MsgManager,msg_gtc_13_002, 1, 0x0f0f );
//	WorldTrade_SetNextSeq( wk, SUBSEQ_MES_WAIT, SUBSEQ_NOW_SAVE_MES );
	
	// ���������t���O�𗧂Ă�
	wk->DepositFlag     = 1;

	// �f���֍s���\������Ă���
	WorldTrade_SubProcessChange( wk, WORLDTRADE_DEMO, MODE_UPLOAD );
	
	wk->subprocess_seq = SUBSEQ_END;
	
	return SEQ_MAIN;
}

//------------------------------------------------------------------
/**
 * @brief   �Ђ��Ƃ�̂ɐ������܂������b�Z�[�W
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int Subseq_DownloadSuccessMessage( WORLDTRADE_WORK *wk)
{
//	Enter_MessagePrint( wk, wk->MsgManager, msg_gtc_14_002, 1, 0x0f0f );
//	WorldTrade_SetNextSeq( wk, SUBSEQ_MES_WAIT, SUBSEQ_NOW_SAVE_MES );
	
	// ���������t���O�𗎂Ƃ�
	 wk->DepositFlag     = 0;


	// �f���֍s���\������Ă���
	WorldTrade_SubProcessChange( wk, WORLDTRADE_DEMO, MODE_DOWNLOAD );
	
	wk->subprocess_seq = SUBSEQ_END;

	return SEQ_MAIN;
}

//------------------------------------------------------------------
/**
 * @brief   �����ɐ������܂������b�Z�[�W
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int Subseq_ExchangeSuccessMessage( WORLDTRADE_WORK *wk)
{
//	Enter_MessagePrint( wk, wk->MsgManager, msg_gtc_15_002, 1, 0x0f0f );
//	WorldTrade_SetNextSeq( wk, SUBSEQ_MES_WAIT, SUBSEQ_NOW_SAVE_MES );
	
	// �f���֍s���\������Ă���
	WorldTrade_SubProcessChange( wk, WORLDTRADE_DEMO, MODE_EXCHANGE );

	wk->subprocess_seq = SUBSEQ_END;

	
	return SEQ_MAIN;
}


//------------------------------------------------------------------
/**
 * @brief   �����炵���|�P����������Ă��܂���
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int Subseq_DownloadExSuccessMessage( WORLDTRADE_WORK *wk)
{
//	Enter_MessagePrint( wk, wk->MsgManager, msg_gtc_14_002, 1, 0x0f0f );
//	WorldTrade_SetNextSeq( wk, SUBSEQ_MES_WAIT, SUBSEQ_NOW_SAVE_MES );
	
	// ���������t���O�𗎂Ƃ�
	 wk->DepositFlag     = 0;

	// �f���֍s���\������Ă���
	WorldTrade_SubProcessChange( wk, WORLDTRADE_DEMO, MODE_DOWNLOAD_EX );
	
	wk->subprocess_seq = SUBSEQ_SAVE;

	return SEQ_MAIN;
	
}

//------------------------------------------------------------------
/**
 * @brief   �������悤�Ƃ����|�P���������Ɍ�������Ă��܂���
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int Subseq_ExchangeFailedMessage( WORLDTRADE_WORK *wk)
{
	Enter_MessagePrint( wk, wk->MsgManager, msg_gtc_15_003, 1, 0x0f0f );
	WorldTrade_SetNextSeq( wk, SUBSEQ_MES_WAIT, SUBSEQ_END );
	
	WorldTrade_SubProcessChange( wk, WORLDTRADE_TITLE, 0 );

	// ���ԃA�C�R������(�Q�d����ɂȂ�̂�NULL�`�F�b�N�͂���j
	WorldTrade_TimeIconDel( wk );

	// �������s�Ȃ̂ŉ���ʂ̂n�a�i���B��
	WorldTrade_SubLcdMatchObjHide( wk );
	
	return SEQ_MAIN;
}


//------------------------------------------------------------------
/**
 * @brief   �G���[�ɑΉ��������b�Z�[�W�Ńv�����g
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static void PrintError( WORLDTRADE_WORK *wk )
{
	int msgno = msg_gtc_error_004_01;

	// �G���[���������܂����B
	switch(wk->ConnectErrorNo){
	case DPW_TR_ERROR_ILLEGAL_DATA :
	case DPW_TR_ERROR_CHEAT_DATA:		//!< �A�b�v���[�h���ꂽ�f�[�^���s��
	case DPW_TR_ERROR_NG_POKEMON_NAME:	//!< �A�b�v���[�h���ꂽ�|�P�����̖��O��NG���[�h���܂�ł���
	case DPW_TR_ERROR_NG_PARENT_NAME:	//!< �A�b�v���[�h���ꂽ�|�P�����̐e�̖��O��NG���[�h���܂�ł���
	case DPW_TR_ERROR_NG_MAIL_NAME:	//!< �A�b�v���[�h���ꂽ���[���̖��O��NG���[�h���܂�ł���
	case DPW_TR_ERROR_NG_OWNER_NAME:	//!< �A�b�v���[�h���ꂽ��l������NG���[�h���܂�ł���

		// ���̃|�P�����͗a���邱�Ƃ��ł��܂���I
		msgno = msg_gtc_01_027;
		break;
	case DPW_TR_ERROR_SERVER_FULL:
		// �T�[�o�[�������ς��ł��B���΂炭���Ă��炫�Ă�������
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
		msgno = msg_gtc_error_004_01;
		break;
	
	}

	OS_TPrintf("error %d\n", wk->ConnectErrorNo);
	// �G���[�ɑΉ������v�����g
	Enter_MessagePrint( wk, wk->MsgManager, msgno, 1, 0x0f0f );

	
}


//------------------------------------------------------------------
/**
 * @brief   GTS�I���G���[�̃��b�Z�[�W�\���i���̌㋭���I���j
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int Subseq_ErrorMessage( WORLDTRADE_WORK *wk )
{

	// �G���[�ɑΉ������v�����g
	PrintError(wk);
	WorldTrade_SetNextSeq( wk, SUBSEQ_MES_WAIT, SUBSEQ_END );
	WorldTrade_SubProcessChange( wk, WORLDTRADE_ENTER, 0 );
	
	// ���ԃA�C�R������(�Q�d����ɂȂ�̂��C������j
	WorldTrade_TimeIconDel(wk);

	return SEQ_MAIN;
}


//------------------------------------------------------------------
/**
 * @brief   �A�N�Z�X�Ɏ��s���āA�G���[��\�����ă^�C�g����
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int Subseq_ReturnTitleMessage( WORLDTRADE_WORK *wk )
{	
	// �G���[�ɑΉ������v�����g
	PrintError(wk);
	WorldTrade_SetNextSeq( wk, SUBSEQ_MES_WAIT, SUBSEQ_END );
	WorldTrade_SubProcessChange( wk, WORLDTRADE_TITLE, 0 );
	
	// ���ԃA�C�R������(SUBSEQ_END�ƂQ�d����ɂȂ�̂�NULL�`�F�b�N�͕K�v
	WorldTrade_TimeIconDel(wk);

	return SEQ_MAIN;
	
}

//------------------------------------------------------------------
/**
 * @brief   �i����Ɂu�Z�[�u���v�\�����ďI�����闬��̍ŏ�
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int SubSeq_NowSaveMessage( WORLDTRADE_WORK *wk )
{
	WorldTrade_SetNextSeq( wk, SUBSEQ_MES_WAIT, SUBSEQ_SAVE );

	// �i����Z�[�u�̓T�[�o�[�A�N�Z�X�͂Ȃ��̂ŁA�f���ɃZ�[�u���ďI���
	SetSaveNextSequence( wk, SUBSEQ_SAVE_LAST, SUBSEQ_END);
	
	return SEQ_MAIN;
}



//------------------------------------------------------------------
/**
 * @brief   �Z�[�u�����Ăяo��
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int SubSeq_Save( WORLDTRADE_WORK *wk )
{

	// �K���S�̃Z�[�u�ɂ���
	SaveData_RequestTotalSave();
	
	// �Z�[�u������
	SaveData_DivSave_Init( wk->param->savedata,SVBLK_ID_MAX);

	wk->subprocess_seq = SUBSEQ_SAVE_RANDOM_WAIT;
	wk->wait           = gf_p_rand(60)+2;

	OS_TPrintf("�Z�[�u�J�n wait=%d\n", wk->wait);

	return SEQ_MAIN;

}



//------------------------------------------------------------------
/**
 * @brief   �Z�[�u�J�n�܂ł̃����_���I���҂�
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int SubSeq_SaveRandomWait( WORLDTRADE_WORK *wk )
{
	wk->wait--;
	if(wk->wait==0){
		wk->subprocess_seq = SUBSEQ_SAVE_WAIT;
	}
	
	return SEQ_MAIN;
}

//------------------------------------------------------------------
/**
 * @brief   �Z�[�u�����I���҂�
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int SubSeq_SaveWait( WORLDTRADE_WORK *wk )
{
	if(SaveData_DivSave_Main(wk->param->savedata)==SAVE_RESULT_LAST){

		// �Z�[�u�V�[�P���X�ɂ���܂łɎ��̐ݒ�͏I���Ă���̂ŁASUBSEQ_END�����ł悢
		wk->subprocess_seq = wk->saveNextSeq1st;
		OS_TPrintf("�Z�[�u�X�X���I��\n");

	}
	
	
	return SEQ_MAIN;
	
}


//------------------------------------------------------------------
/**
 * @brief   �Z�[�u�Ō�̂P�Z�N�^�������݌Ăяo������
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int SubSeq_SaveLast( WORLDTRADE_WORK *wk )
{
	if(SaveData_DivSave_Main(wk->param->savedata)==SAVE_RESULT_OK){
		wk->subprocess_seq = wk->saveNextSeq2nd;

		OS_TPrintf("�Z�[�u100���I��\n");
		// ���ԃA�C�R������
		WorldTrade_TimeIconDel(wk);
	}
	
	
	return SEQ_MAIN;
	
}

//------------------------------------------------------------------
/**
 * @brief   �Z�[�u�����Ăяo��
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int SubSeq_TimeoutSave( WORLDTRADE_WORK *wk )
{

	// �K���S�̃Z�[�u�ɂ���
	SaveData_RequestTotalSave();

	
	// �Z�[�u������
	SaveData_DivSave_Init( wk->param->savedata,SVBLK_ID_MAX);
	wk->subprocess_seq = SUBSEQ_TIMEOUT_SAVE_WAIT;

	return SEQ_MAIN;

}



//------------------------------------------------------------------
/**
 * @brief   �Z�[�u�����I���҂�
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int SubSeq_TimeoutSaveWait( WORLDTRADE_WORK *wk )
{
	if(SaveData_DivSave_Main(wk->param->savedata)==SAVE_RESULT_OK){

		// �^�C�g����ʂɖ߂�ݒ�
		WorldTrade_SubProcessChange( wk, WORLDTRADE_TITLE, 0 );

		// ���ԃA�C�R������(�Q�d����ɂȂ�̂��C������j
		WorldTrade_TimeIconDel(wk);

		// �������͂������񂳂�܂���ł����c
		Enter_MessagePrint( wk, wk->MsgManager, wk->error_mes_no, 1, 0x0f0f );
		WorldTrade_SetNextSeq( wk, SUBSEQ_MES_WAIT, SUBSEQ_SERVER_TRADE_CHECK_END );

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
static int Subseq_End( WORLDTRADE_WORK *wk)
{
	// �K�����ԃA�C�R��������(�Q�d����΍�͂��Ă����j
	WorldTrade_TimeIconDel(wk);
	
	WirelessIconEasyEnd();

	if( wk->sub_out_flg == 1 ){
		WIPE_SYS_Start( WIPE_PATTERN_WMS, WIPE_TYPE_FADEOUT, WIPE_TYPE_FADEOUT, WIPE_FADE_BLACK, WORLDTRADE_WIPE_SPPED, 1, HEAPID_WORLDTRADE );
#ifdef GTS_FADE_OSP
		OS_Printf( "******************** worldtrade_upload.c [1737] MS ********************\n" );
#endif
	}else{
		WIPE_SYS_Start( WIPE_PATTERN_M, WIPE_TYPE_FADEOUT, WIPE_TYPE_FADEOUT, WIPE_FADE_BLACK, WORLDTRADE_WIPE_SPPED, 1, HEAPID_WORLDTRADE );
#ifdef GTS_FADE_OSP
		OS_Printf( "******************** worldtrade_upload.c [1741] M ********************\n" );
#endif
	}
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
static int Subseq_YesNo( WORLDTRADE_WORK *wk)
{
	wk->YesNoMenuWork = WorldTrade_BmpWinYesNoMake(wk->bgl, WORLDTRADE_YESNO_PY2, YESNO_OFFSET );
	wk->subprocess_seq = wk->subprocess_nextseq;
//	wk->subprocess_seq = SUBSEQ_YESNO_SELECT;

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
static int Subseq_MessageWait( WORLDTRADE_WORK *wk )
{
	if( GF_MSG_PrintEndCheck( wk->MsgIndex )==0){
		wk->subprocess_seq = wk->subprocess_nextseq;
	}
	return SEQ_MAIN;

}




//------------------------------------------------------------------
/**
 * @brief   �a�����|�P�����f�[�^��BOX���Ă��������������
 *
 * @param   pp		
 * @param   flag	�i�[�t���O�𗧂Ă邩?(1:���Ă� 0:���ĂȂ��j
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void UploadPokemonDataDelete( WORLDTRADE_WORK *wk, int flag )
{
//	BOXDAT_PutPokemonBox( BOX_DATA* box, u32 boxNum, POKEMON_PASO_PARAM* poke );

	// �莝������łȂ����BOX�̃|�P��������������
	if(wk->BoxTrayNo!=18){
		POKEMON_PARAM *pp = PokemonParam_AllocWork(HEAPID_WORLDTRADE);
		PokeReplace(
			BOXDAT_GetPokeDataAddress( wk->param->mybox, wk->BoxTrayNo, wk->BoxCursorPos ),
			pp
		);

		WorldTradeData_SetPokemonData( wk->param->worldtrade_data, pp, wk->BoxTrayNo );

		// �{�b�N�X�������
		BOXDAT_ClearPokemon( wk->param->mybox, wk->BoxTrayNo, wk->BoxCursorPos );
		OS_Printf("box %d, %d �̃|�P�����������\n", wk->BoxTrayNo, wk->BoxCursorPos);

		sys_FreeMemoryEz(pp);
	}else{
	// �Ă���

		POKEMON_PARAM *pp = PokeParty_GetMemberPointer(wk->param->myparty, wk->BoxCursorPos);
		OS_Printf("�Ă���������� pos = %d\n", wk->BoxCursorPos);

		// �J�X�^���{�[���̈���N���A
		PokePara_CustomBallDataInit( pp );

		// �Z�[�u�̈�ɕۑ�
		WorldTradeData_SetPokemonData( wk->param->worldtrade_data, pp, wk->BoxTrayNo );

		// �莝���������
		PokeParty_Delete( wk->param->myparty, wk->BoxCursorPos );

		// �Ă�������y���b�v�����Ȃ��Ȃ����琺�f�[�^����������
		if(PokeParty_PokemonCheck( wk->param->myparty, MONSNO_PERAPPU )==0){
			PERAPVOICE *pv = SaveData_GetPerapVoice( wk->param->savedata );
			PERAPVOICE_ClearExistFlag( pv );
		}
		
	}
	
	if(flag){
		// �a�����t���O
		WorldTradeData_SetFlag( wk->param->worldtrade_data, 1 );
	}
}

//------------------------------------------------------------------
/**
 * @brief   ������鏈��
 *
 * @param   wk		
 * @param   pp		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void DownloadPokemonDataAdd( WORLDTRADE_WORK *wk, POKEMON_PARAM *pp, int boxno, int flag )
{
	int itemno = PokeParaGet(pp, ID_PARA_item, NULL);

	// �}�ӓ��̓o�^����
	SaveData_GetPokeRegister( wk->param->savedata, pp );

	// �Ȃɂ͂Ƃ�����Ă����ɓ���悤�Ƃ���
	// �{�b�N�X�ɓ���悤�Ƃ��Ă��鎞�Ƀ|�P�����Ƀ��[�������Ă���ꍇ��
	// �Ă����ɓ����悤�ɂ���
	boxno = 18;

	if(PokeParty_GetPokeCount(wk->param->myparty)==6){
		// �Ă����������ς���������{�b�N�X��
		boxno = 0;
	}

	// �������������Ă���
	if(flag){
		u8 friend = FIRST_NATUKIDO;

		// �Ȃ��x�������l�V�O�ɂ���
		PokeParaPut( pp, ID_PARA_friend, &friend );

		// �|�P�����̌��������ŏI�����Z�[�u����
		TradeDateUpDate( wk->param->worldtrade_data );
	}

	// �Ă���(�Ă�������t�͂��̎��_���Ƃǂ����悤���Ȃ��̂ł��Ȃ��悤�ɂ��Ȃ��Ɓj
	if(boxno==18){
		int num;

		// ���[�������Ă���̂ŁA�莝���ɂ����󂯎��Ȃ�
		PokeParty_Add(wk->param->myparty, pp);
		num = PokeParty_GetPokeCount( wk->param->myparty );

		wk->EvoPokeInfo.boxno = 18;
		wk->EvoPokeInfo.pos   = num-1;

	}else{
	// �{�b�N�X
		
		int boxpos=0;
		// ���[�����������BOX�ɓ����

		// �{�b�N�X�̋󂢂Ă���Ƃ����T��
		BOXDAT_GetEmptyTrayNumberAndPos( wk->param->mybox, &boxno, &boxpos );

		// �󂯎�����|�P�������i�[����
		BOXDAT_PutPokemonBox( wk->param->mybox, boxno, PPPPointerGet(pp) );

		wk->EvoPokeInfo.boxno = boxno;
		wk->EvoPokeInfo.pos   = boxpos;
	}

	// ���E�������[�N����a���Ă�t���O�𗎂Ƃ�
	WorldTradeData_SetFlag( wk->param->worldtrade_data, 0 );



}


//------------------------------------------------------------------
/**
 * @brief   �������Ă݂����|�P�����ƌ������鎞�̏���
 *
 * @param   wk		
 * @param   pp		
 * @param   boxno		
 * @param   flag		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void ExchangePokemonDataAdd( WORLDTRADE_WORK *wk, POKEMON_PARAM *pp, int boxno )
{

	// �}�ӓo�^����
	SaveData_GetPokeRegister( wk->param->savedata, pp );

	boxno = 18;
	if(PokeParty_GetPokeCount(wk->param->myparty)==6){
		// �Ă����������ς���������i�[����{�b�N�X��
		OS_Printf("�i�[���BOX\n");
		boxno = 0;
	}

	{
		// �������ꂽ�|�P�����ɓ����Ȃ��x
		u8 friend = FIRST_NATUKIDO;
		PokeParaPut(pp, ID_PARA_friend, &friend);
	}

	// �Ă���(�Ă�������t�͂��̎��_���Ƃǂ����悤���Ȃ��̂Łj
	if(boxno==18){
		int num;

		// ���[�������Ă���̂ŁA�莝���ɂ����󂯎��Ȃ�
		PokeParty_Add(wk->param->myparty, pp);
		num = PokeParty_GetPokeCount( wk->param->myparty );

		wk->EvoPokeInfo.boxno = 18;
		wk->EvoPokeInfo.pos   = num-1;
		OS_Printf("�Ă����ɒǉ�����\n");

	}else{
	// �{�b�N�X
		
		int boxpos=0;
		// ���[�����������BOX�ɓ����

		// �{�b�N�X�̋󂢂Ă���Ƃ����T��
		BOXDAT_GetEmptyTrayNumberAndPos( wk->param->mybox, &boxno, &boxpos );

		// �󂯎�����|�P�������i�[����
		BOXDAT_PutPokemonBox( wk->param->mybox, boxno, PPPPointerGet(pp) );

		wk->EvoPokeInfo.boxno = boxno;
		wk->EvoPokeInfo.pos   = boxpos;

		OS_Printf("BOX�� %d �g���C�ɒǉ�����\n", boxno);

	}

	WorldTradeData_SetFlag( wk->param->worldtrade_data, 0 );


	// �|�P�����̌��������ŏI�����Z�[�u����
	TradeDateUpDate( wk->param->worldtrade_data );
	
}

//------------------------------------------------------------------
/**
 * @brief   �ŏI�������t���X�V
 *
 * @param   worldtrade_data		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void TradeDateUpDate( WORLDTRADE_DATA *worldtrade_data )
{
	RTCDate date;
	RTCTime time;
	GF_DATE gfDate;

	// �T�[�o�[��̌��ݎ������擾
	DWC_GetDateTime( &date, &time);

	// �ŏI�������t�Ƃ��ĕۑ�
	gfDate = RTCDate2GFDate( &date );
	WorldTradeData_SetLastDate( worldtrade_data, gfDate );
	OS_Printf(" %d�N %d�� %d���Ɍ�������\n",
				GFDate_GetYear( gfDate ),GFDate_GetMonth( gfDate ),GFDate_GetDay( gfDate ));

}

//------------------------------------------------------------------
/**
 * @brief   ����̌��������Q�Ƃ��Ēn���V����o�^����
 *
 * @param   wifiHistory		
 * @param   trData		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void WifiHistoryDataSet( WIFI_HISTORY *wifiHistory, Dpw_Tr_Data *trData )
{

	Comm_WifiHistoryDataSet( wifiHistory, trData->countryCode, trData->localCode, trData->langCode );
	
}

//------------------------------------------------------------------
/**
 * @brief   �`���m�[�g�f�[�^�o�^����
 *
 * @param   fnote		
 * @param   trData		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void SetFnoteData( FNOTE_DATA *fnote,  Dpw_Tr_Data *trData )
{
	void *fnoteWork;
	STRCODE  MonsName[MONS_NAME_SIZE+EOM_SIZE];
	POKEMON_PARAM *pp = (POKEMON_PARAM*)trData->postData.data;

	PokeParaGet( pp, ID_PARA_nickname, MonsName );

	fnoteWork = FNOTE_SioGTCDataMake( trData->name, trData->gender, 
									MonsName, PokeSexGet(pp), HEAPID_WORLDTRADE );

	FNOTE_DataSave( fnote, fnoteWork, FNOTE_TYPE_SIO );
}

#define BOX_MAX_NUM	(BOX_MAX_RAW*BOX_MAX_COLUMN*BOX_MAX_TRAY)

//------------------------------------------------------------------
/**
 * @brief   �����̓|�P�������󂯎��邩�H���[�������Ă��Ă��󂯎���H
 *
 * @param   wk		
 * @param   trData		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int MyPokemonPocketFullCheck( WORLDTRADE_WORK *wk, Dpw_Tr_Data *trData)
{
	
	// �����Ƃ�|�P���������[���������Ă��鎞�͂Ă����ɋ󂫖����Ƃ����Ȃ�
	if( WorldTrade_PokemonMailCheck( (POKEMON_PARAM*)trData->postData.data ) 
		&&  PokeParty_GetPokeCount(wk->param->myparty) == 6){
		return POKEMON_NOT_FULL_BUT_MAIL_NORECV;
	}

	OS_Printf("boxnum = %d, temochi = %d\n", wk->boxPokeNum, PokeParty_GetPokeCount(wk->param->myparty));
	// �Ƃɂ����Ă������{�b�N�X���󂫂��Ȃ�
	if(wk->boxPokeNum == BOX_MAX_NUM && PokeParty_GetPokeCount(wk->param->myparty) == 6){
		return POKEMON_ALL_FULL;
	}

	// OK
	return POKEMON_RECV_OK;
}


//------------------------------------------------------------------
/**
 * @brief   �Z�[�u�V�[�P���X��Ɉړ�������\�񂷂�
 *
 * @param   nextSeq1st		�Z�[�u�O���I����ɑJ�ڂ���V�[�P���X
 * @param   nextSeq2nd		�Z�[�u�㔼�I����ɑJ�ڂ���V�[�P���X
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void SetSaveNextSequence( WORLDTRADE_WORK *wk, int nextSeq1st, int nextSeq2nd )
{
	wk->saveNextSeq1st = nextSeq1st;
	wk->saveNextSeq2nd = nextSeq2nd;
	
}

