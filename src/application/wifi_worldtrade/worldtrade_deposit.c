//============================================================================================
/**
 * @file	worldtrade_deposit.c
 * @bfief	���E�����|�P�����a�����ʏ���
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
#include "poketool/poke_tool.h"
#include "poketool/pokeparty.h"
#include "poketool/monsno.h"

#include "savedata/wifilist.h"
#include "savedata/zukanwork.h"
#include "application/worldtrade.h"
#include "worldtrade_local.h"
#include "msgdata/msg_wifi_lobby.h"
#include "msgdata/msg_wifi_gtc.h"

#include "worldtrade.naix"			// �O���t�B�b�N�A�[�J�C�u��`
#include "../zukanlist/zkn_data/zukan_data.naix"
#include "application/zukanlist/zkn_sort_akstnhmyrw_idx.h"

//============================================================================================
//	�v���g�^�C�v�錾
//============================================================================================
/*** �֐��v���g�^�C�v ***/
static void SubSeq_MessagePrint( WORLDTRADE_WORK *wk, int msgno, int wait, int flag, u16 dat );
static void BgInit( GF_BGL_INI * ini );
static void BgExit( GF_BGL_INI * ini );
static void BgGraphicSet( WORLDTRADE_WORK * wk );
static void BmpWinInit( WORLDTRADE_WORK *wk );
static void BmpWinDelete( WORLDTRADE_WORK *wk );
static void InitWork( WORLDTRADE_WORK *wk );
static void FreeWork( WORLDTRADE_WORK *wk );
static int SubSeq_Start( WORLDTRADE_WORK *wk);
static int SubSeq_Main( WORLDTRADE_WORK *wk);
static int RoundWork( int num, int max, int move );
static int SubSeq_HeadWordSelectList( WORLDTRADE_WORK *wk );
static int SubSeq_HeadWordSelectWait( WORLDTRADE_WORK *wk );
static int SubSeq_PokeNameSelectList( WORLDTRADE_WORK *wk );
static int SubSeq_PokeNameSelectWait( WORLDTRADE_WORK *wk );
static int SubSeq_End( WORLDTRADE_WORK *wk);
static int SubSeq_YesNo( WORLDTRADE_WORK *wk);
static int SubSeq_MessageWait( WORLDTRADE_WORK *wk );
static void PokeWantPrint( MSGDATA_MANAGER *MsgManager, MSGDATA_MANAGER *MonsNameManager,WORDSET *WordSet, GF_BGL_BMPWIN win[], int monsno, int sex, int level );
static void PokeDepositPrint( MSGDATA_MANAGER *MsgManager, WORDSET *WordSet, GF_BGL_BMPWIN win[], POKEMON_PASO_PARAM *ppp, Dpw_Tr_PokemonDataSimple *post );
static int 	SubSeq_SexSelctWait( WORLDTRADE_WORK *wk );
static int 	SubSeq_SexSelctList( WORLDTRADE_WORK *wk );
static int 	SubSeq_SexSelctMessage( WORLDTRADE_WORK *wk );
static int  SubSeq_LevelSelectMessage( WORLDTRADE_WORK *wk );
static int  SubSeq_LevelSelectWait( WORLDTRADE_WORK *wk );
static int  SubSeq_LevelSelectList( WORLDTRADE_WORK *wk );
static int  SubSeq_DepositOkMessage( WORLDTRADE_WORK *wk );
static int  SubSeq_DepositOkYesNo( WORLDTRADE_WORK *wk );
static int SubSeq_DepositOkYesNoWait( WORLDTRADE_WORK *wk );
static void DepositPokemonDataMake( Dpw_Tr_Data *dtd, WORLDTRADE_WORK *wk );


static int PokeNameSortListMake( BMP_MENULIST_DATA **menulist, MSGDATA_MANAGER *monsnameman, 
									MSGDATA_MANAGER *msgman,u16 *table, u8 *sinou,
									int num, int select,ZUKAN_WORK *zukan );
static u16* ZukanSortDataGet( int heap, int idx, int* p_arry_num );
static GF_PRINTCOLOR GetSexColor( int sex, GF_PRINTCOLOR color );



enum{
	SUBSEQ_START=0,
	SUBSEQ_MAIN,
	SUBSEQ_END,

	SUBSEQ_HEADWORD_SELECT_LIST,
    SUBSEQ_HEADWORD_SELECT_WAIT,
    SUBSEQ_POKENAME_SELECT_LIST,
    SUBSEQ_POKENAME_SELECT_WAIT,
	SUBSEQ_SEX_SELECT_MES,
	SUBSEQ_SEX_SELECT_LIST,
	SUBSEQ_SEX_SELECT_WAIT,
	SUBSEQ_LEVEL_SELECT_MES,
	SUBSEQ_LEVEL_SELECT_LIST,
	SUBSEQ_LEVEL_SELECT_WAIT,
	SUBSEQ_DEPOSITOK_MESSAGE,
	SUBSEQ_DEPOSIT_YESNO,
	SUBSEQ_DEPOSIT_YESNO_WAIT,
	
	SUBSEQ_MES_WAIT,
};
static int (*Functable[])( WORLDTRADE_WORK *wk ) = {
	SubSeq_Start,				// SUBSEQ_START=0,
	SubSeq_Main,    	        // SUBSEQ_MAIN,
	SubSeq_End,         	    // SUBSEQ_END,
	SubSeq_HeadWordSelectList,	// SUBSEQ_HEADWORD_SELECT_LIST
	SubSeq_HeadWordSelectWait,	// SUBSEQ_HEADWORD_SELECT_WAIT
	SubSeq_PokeNameSelectList,	// SUBSEQ_POKENAME_SELECT_LIST
	SubSeq_PokeNameSelectWait,	// SUBSEQ_POKENAME_SELECT_WAIT
	SubSeq_SexSelctMessage,		// SUBSEQ_SEX_SELECT_MES,
	SubSeq_SexSelctList,		// SUBSEQ_SEX_SELECT_LIST,
	SubSeq_SexSelctWait,		// SUBSEQ_SEX_SELECT_WAIT,
	SubSeq_LevelSelectMessage,	// SUBSEQ_LEVEL_SELECT_MES,
    SubSeq_LevelSelectList,     // SUBSEQ_LEVEL_SELECT_LIST,
    SubSeq_LevelSelectWait,     // SUBSEQ_LEVEL_SELECT_WAIT,
	SubSeq_DepositOkMessage,
    SubSeq_DepositOkYesNo,
	SubSeq_DepositOkYesNoWait,

	SubSeq_MessageWait,			// SUBSEQ_MES_WAIT
};

#define BOX_CUROSOR_END_POS			( 30 )
#define BOX_CUROSOR_TRAYNAME_POS	( 31 )


// �ق����|�P�����E��������|�P�������
#define INFORMATION_STR_X	(  1 )
#define INFORMATION_STR_Y	(  4 )
#define INFORMATION2_STR_X	(  3 )
#define INFORMATION2_STR_Y	(  6 )
#define INFORMATION3_STR_X	(  1 )
#define INFORMATION3_STR_Y	(  8 )
#define INFORMATION_STR_SX	( 11 )
#define INFORMATION_STR_SY	(  2 )


#define TITLE_MESSAGE_OFFSET   ( WORLDTRADE_MENUFRAME_CHR + MENU_WIN_CGX_SIZ )
#define LINE_MESSAGE_OFFSET    ( TITLE_MESSAGE_OFFSET     + TITLE_TEXT_SX*TITLE_TEXT_SY )
#define INFOMATION_STR_OFFSET  ( LINE_MESSAGE_OFFSET      + LINE_TEXT_SX*LINE_TEXT_SY )
#define SELECT_MENU1_OFFSET    ( INFOMATION_STR_OFFSET    + INFORMATION_STR_SX*INFORMATION_STR_SY*6 )
#define SELECT_MENU2_OFFSET    ( SELECT_MENU1_OFFSET      + SELECT_MENU1_SX*SELECT_MENU1_SY )
#define SELECT_MENU3_OFFSET    ( SELECT_MENU1_OFFSET )
#define SELECT_MENU4_OFFSET    ( SELECT_MENU1_OFFSET )
#define YESNO_OFFSET 		   ( SELECT_MENU4_OFFSET      + SELECT_MENU4_SX*SELECT_MENU4_SY )

static const u16 infomation_bmp_table[6][2]={
	{INFORMATION_STR_X,  INFORMATION_STR_Y,   },
	{INFORMATION2_STR_X, INFORMATION2_STR_Y,  },
	{INFORMATION3_STR_X, INFORMATION3_STR_Y,  },
	{INFORMATION_STR_X,  INFORMATION_STR_Y+9, },
	{INFORMATION2_STR_X, INFORMATION2_STR_Y+9,},
	{INFORMATION3_STR_X, INFORMATION3_STR_Y+9,},

};

// �������x���w��p�\����
typedef struct{
	int msg;
	s16 min;
	s16 max;
}WT_LEVEL_TERM;

// �������x����(�Ō�̓L�����Z�������ǁj
#define LEVEL_SELECT_NUM	(13)

// �������x���w��e�[�u��
static const WT_LEVEL_TERM level_minmax_table[]={
	{ msg_gtc_12_001, 0,   0, },	// ���ɂ��Ȃ�
	{ msg_gtc_12_002, 0,   9, },	// ���x���P�O�݂܂�
	{ msg_gtc_12_003,10,   0, },	// ���x���P�O�ȏ�
	{ msg_gtc_12_004,20,   0, },	// ���x���Q�O�ȏ�
	{ msg_gtc_12_005,30,   0, },	// ���x���R�O�ȏ�
	{ msg_gtc_12_006,40,   0, },	// ���x���S�O�ȏ�
	{ msg_gtc_12_007,50,   0, },	// ���x���T�O�ȏ�
	{ msg_gtc_12_008,60,   0, },	// ���x���U�O�ȏ�
	{ msg_gtc_12_009,70,   0, },	// ���x���V�O�ȏ�
	{ msg_gtc_12_010,80,   0, },	// ���x���W�O�ȏ�
	{ msg_gtc_12_011,90,   0, },	// ���x���X�O�ȏ�
	{ msg_gtc_12_012,100,100, },	// ���x���P�O�O
    { msg_gtc_12_013, 0,  0, }, // �L�����Z��
};




//============================================================================================
//	�v���Z�X�֐�
//============================================================================================

//==============================================================================
/**
 * @brief   ���E�����������ʏ�����
 *
 * @param   wk		
 * @param   seq		
 *
 * @retval  int		
 */
//==============================================================================
int WorldTrade_Deposit_Init(WORLDTRADE_WORK *wk, int seq)
{
	// ���[�N������
	InitWork( wk );
	
	// BG�ݒ�
	BgInit( wk->bgl );

	// BG�O���t�B�b�N�]��
	BgGraphicSet( wk );

	// BMPWIN�m��
	BmpWinInit( wk );

//	SetCellActor(wk);


	WIPE_SYS_Start( WIPE_PATTERN_M, WIPE_TYPE_FADEIN, WIPE_TYPE_FADEIN, WIPE_FADE_BLACK, WORLDTRADE_WIPE_SPPED, 1, HEAPID_WORLDTRADE );
#ifdef GTS_FADE_OSP
	OS_Printf( "******************** worldtrade_deposit.c [226] M ********************\n" );
#endif

	// �ʐM��Ԃ��m�F���ăA�C�R���̕\����ς���
    WorldTrade_WifiIconAdd( wk );
   
    // �ق����|�P�����E��������|�P�����`��
	WodrldTrade_PokeWantPrint( wk->MsgManager, wk->MonsNameManager, 
				wk->WordSet, &wk->InfoWin[0], 0,DPW_TR_GENDER_NONE,-1);
	PokeDepositPrint( wk->MsgManager, wk->WordSet, &wk->InfoWin[3], wk->deposit_ppp, &wk->Post );

	OS_TPrintf("�}�ӑ��� = %d\n",wk->dw->nameSortNum);


	wk->subprocess_seq = SUBSEQ_START;
	
	
	return SEQ_FADEIN;
}

//==============================================================================
/**
 * @brief   ���E�����������ʃ��C��
 *
 * @param   wk		
 * @param   seq		
 *
 * @retval  int		
 */
//==============================================================================
int WorldTrade_Deposit_Main(WORLDTRADE_WORK *wk, int seq)
{
	int ret;

	// �ʐM��Ԃ��m�F���ăA�C�R���̕\����ς���
    WirelessIconEasy_SetLevel(WorldTrade_WifiLinkLevel());
	
	ret = (*Functable[wk->subprocess_seq])( wk );

	return ret;
}


//==============================================================================
/**
 * @brief   ���E�����������ʏI��
 *
 * @param   wk		
 * @param   seq		
 *
 * @retval  int		
 */
//==============================================================================
int WorldTrade_Deposit_End(WORLDTRADE_WORK *wk, int seq)
{
	WirelessIconEasyEnd();

//	DelCellActor(wk);

	FreeWork( wk );
	
	BmpWinDelete( wk );
	
	BgExit( wk->bgl );
	
	WorldTrade_SubProcessUpdate( wk );
	
	return SEQ_INIT;
}


//------------------------------------------------------------------
/**
 * @brief   ��b�E�C���h�E�\��
 *
 * @param   wk		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void SubSeq_MessagePrint( WORLDTRADE_WORK *wk, int msgno, int wait, int flag, u16 dat )
{
	// ������擾
	STRBUF *tempbuf;
	
	// ������擾
	tempbuf = MSGMAN_AllocString(  wk->MsgManager, msgno );

	// WORDSET�W�J
	WORDSET_ExpandStr( wk->WordSet, wk->TalkString, tempbuf );
	

	// ��b�E�C���h�E�g�`��
	GF_BGL_BmpWinDataFill( &wk->MsgWin,  0x0f0f );
	BmpTalkWinWrite( &wk->MsgWin, WINDOW_TRANS_ON, WORLDTRADE_MESFRAME_CHR, WORLDTRADE_MESFRAME_PAL );

	// ������`��J�n
	wk->MsgIndex = GF_STR_PrintSimple( &wk->MsgWin, FONT_TALK, wk->TalkString, 0, 0, wait, NULL);

	STRBUF_Delete(tempbuf);
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
		GF_BGL_ScrClear( ini, GF_BGL_FRAME0_M );
	}

	// ���C����ʃ��j���[��
	{	
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xf000, GX_BG_CHARBASE_0x08000, GX_BG_EXTPLTT_01,
			1, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( ini, GF_BGL_FRAME1_M, &TextBgCntDat, GF_BGL_MODE_TEXT );
	}

	// ���C����ʔw�i��
	{	
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xe800, GX_BG_CHARBASE_0x08000, GX_BG_EXTPLTT_01,
			1, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( ini, GF_BGL_FRAME2_M, &TextBgCntDat, GF_BGL_MODE_TEXT );
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


	// �T�u��ʔw�iBG1( ���̖ʂ�256�F )
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

	// �㉺��ʂa�f�p���b�g�]��
	ArcUtil_PalSet(    ARC_WORLDTRADE_GRA, NARC_worldtrade_deposit_nclr, PALTYPE_MAIN_BG, 0, 16*3*2,  HEAPID_WORLDTRADE);
	
	// ��b�t�H���g�p���b�g�]��
	TalkFontPaletteLoad( PALTYPE_MAIN_BG, WORLDTRADE_TALKFONT_PAL*0x20, HEAPID_WORLDTRADE );

	// ��b�E�C���h�E�O���t�B�b�N�]��
	TalkWinGraphicSet(	bgl, GF_BGL_FRAME0_M, WORLDTRADE_MESFRAME_CHR, 
						WORLDTRADE_MESFRAME_PAL,  CONFIG_GetWindowType(wk->param->config), HEAPID_WORLDTRADE );


	MenuWinGraphicSet(	bgl, GF_BGL_FRAME0_M, WORLDTRADE_MENUFRAME_CHR,
						WORLDTRADE_MENUFRAME_PAL, 0, HEAPID_WORLDTRADE );


	// ���C�����BG1�L�����]��
	ArcUtil_BgCharSet( ARC_WORLDTRADE_GRA, NARC_worldtrade_deposit_lz_ncgr, bgl, GF_BGL_FRAME1_M, 0, 16*5*0x20, 1, HEAPID_WORLDTRADE);

	// ���C�����BG1�X�N���[���]��
	ArcUtil_ScrnSet(   ARC_WORLDTRADE_GRA, NARC_worldtrade_deposit_lz_nscr, bgl, GF_BGL_FRAME1_M, 0, 32*24*2, 1, HEAPID_WORLDTRADE);


}






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
	int i;
	// ---------- ���C����� ------------------

	// BG0��BMPWIN�^�C�g���E�C���h�E�m�ہE�`��
	
	GF_BGL_BmpWinAdd(wk->bgl, &wk->TitleWin, GF_BGL_FRAME0_M,
	TITLE_TEXT_X, TITLE_TEXT_Y, TITLE_TEXT_SX, TITLE_TEXT_SY, WORLDTRADE_TALKFONT_PAL,  TITLE_MESSAGE_OFFSET );

	GF_BGL_BmpWinDataFill( &wk->TitleWin, 0x0000 );
	
	// �u�|�P��������������v�`��
	WorldTrade_TalkPrint( &wk->TitleWin, wk->TitleString, 0, 1, 0, GF_PRINTCOLOR_MAKE(15,14,0) );


	// ��s�E�C���h�E
	GF_BGL_BmpWinAdd(wk->bgl, &wk->MsgWin, GF_BGL_FRAME0_M,
		LINE_TEXT_X, LINE_TEXT_Y, LINE_TEXT_SX, LINE_TEXT_SY, 
		WORLDTRADE_TALKFONT_PAL,  LINE_MESSAGE_OFFSET );

	GF_BGL_BmpWinDataFill( &wk->MsgWin, 0x0000 );
//	Enter_MessagePrint( wk, wk->MsgManager, msg_gtc_05_001, MSG_ALLPUT, 0 );


	// ��������|�P�����E�ق����|�P�������BMPWIN�m��
	for(i=0;i<6;i++){
		GF_BGL_BmpWinAdd(wk->bgl, &wk->InfoWin[i], GF_BGL_FRAME0_M,
			infomation_bmp_table[i][0], infomation_bmp_table[i][1], 
			INFORMATION_STR_SX, INFORMATION_STR_SY, WORLDTRADE_TALKFONT_PAL,  
			INFOMATION_STR_OFFSET+(INFORMATION_STR_SX*INFORMATION_STR_SY)*i  );
		GF_BGL_BmpWinDataFill( &wk->InfoWin[i], 0x0000 );
		GF_BGL_BmpWinOn(&wk->InfoWin[i]);
	}

	OS_Printf("WORLDTRADE heap�c�� = %d\n",sys_GetHeapFreeSize( HEAPID_WORLDTRADE ));
}	

//------------------------------------------------------------------
/**
 * @brief   �m�ۂ���BMPWIN�����
 *
 * @param   wk		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void BmpWinDelete( WORLDTRADE_WORK *wk )
{
	int i;
	
	for(i=0;i<6;i++){
		GF_BGL_BmpWinDel( &wk->InfoWin[i] );
	}
	GF_BGL_BmpWinDel( &wk->MsgWin );
	GF_BGL_BmpWinDel( &wk->TitleWin );


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

	// �|�P��������������
	wk->TitleString = MSGMAN_AllocString( wk->MsgManager, msg_gtc_05_001 );

	// �|�P�������e�[�u���쐬�p�̃��[�N�m��
	wk->dw = sys_AllocMemory(HEAPID_WORLDTRADE, sizeof(DEPOSIT_WORK));
	MI_CpuClearFast( wk->dw, sizeof(DEPOSIT_WORK) );

	// �}�Ӄ\�[�g�f�[�^(�S���}�ӂƁA�V���I�E�}�ӂ̕��򂪕K�v���Ƃ������j
	wk->dw->nameSortTable = WorldTrade_ZukanSortDataGet( HEAPID_WORLDTRADE, 0, &wk->dw->nameSortNum );

	// �V���I�E�}�Ӄe�[�u��
	wk->dw->sinouTable    = WorldTrade_SinouZukanDataGet( HEAPID_WORLDTRADE );

	// �J�[�\���ʒu������
	WorldTrade_SelectListPosInit( &wk->selectListPos );
}


//------------------------------------------------------------------
/**
 * @brief   ���[�N���
 *
 * @param   wk		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void FreeWork( WORLDTRADE_WORK *wk )
{

	sys_FreeMemoryEz( wk->dw->sinouTable );
	sys_FreeMemoryEz(wk->dw->nameSortTable);
	sys_FreeMemoryEz(wk->dw);

	STRBUF_Delete( wk->TalkString ); 
	STRBUF_Delete( wk->TitleString ); 

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
 * @brief   �T�u�v���Z�X�V�[�P���X�X�^�[�g����
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int SubSeq_Start( WORLDTRADE_WORK *wk)
{
	// 
	if(WIPE_SYS_EndCheck()){
		SubSeq_MessagePrint( wk, msg_gtc_01_010, 1, 0, 0x0f0f );
		WorldTrade_SetNextSeq( wk, SUBSEQ_MES_WAIT, SUBSEQ_MAIN );

		// �ق����|�P�����E��������|�P�����`��
		
//		 wk->subprocess_seq = SUBSEQ_MAIN;
	}

	return SEQ_MAIN;
}

//------------------------------------------------------------------
/**
 * @brief   �T�u�v���Z�X�V�[�P���X���C��
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int SubSeq_Main( WORLDTRADE_WORK *wk)
{

	if(sys.trg & PAD_BUTTON_B){
		 WorldTrade_SubProcessChange( wk, WORLDTRADE_MYBOX, MODE_DEPOSIT_SELECT );
		wk->subprocess_seq = SUBSEQ_END;
	}

	// �A�C�E�G�I�I���E�C���h�E�m��
	GF_BGL_BmpWinAdd(wk->bgl, &wk->MenuWin[0], GF_BGL_FRAME0_M,
		SELECT_MENU1_X,		SELECT_MENU1_Y,		SELECT_MENU1_SX, 		SELECT_MENU1_SY, 
		WORLDTRADE_TALKFONT_PAL,  SELECT_MENU1_OFFSET );
	GF_BGL_BmpWinDataFill( &wk->MenuWin[0], 0x0000 );


	// �|�P�������I���E�C���h�E�m��
	GF_BGL_BmpWinAdd(wk->bgl, &wk->MenuWin[1], GF_BGL_FRAME0_M,
		SELECT_MENU2_X,		SELECT_MENU2_Y,		SELECT_MENU2_SX, 		SELECT_MENU2_SY, 
		WORLDTRADE_TALKFONT_PAL,  SELECT_MENU2_OFFSET );
	GF_BGL_BmpWinDataFill( &wk->MenuWin[1], 0x0000 );

	wk->subprocess_seq = SUBSEQ_HEADWORD_SELECT_LIST;

	return SEQ_MAIN;
}




//------------------------------------------------------------------
/**
 * @brief   num��move�𑫂�,0�ȉ��Ȃ�max-1�ɁAmax�Ȃ�0�ɂ��ĕԂ�
 *
 * @param   num		���̒l
 * @param   max		�ő�l
 * @param   move	�����l�i�{�|����j
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int RoundWork( int num, int max, int move )
{
	num += move;
	if(num < 0) {
		return max-1;
	}
	if(num==max){
		return 0;
	}
	return num;
}


//------------------------------------------------------------------
/**
 * @brief   �������I�����X�g�쐬
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int SubSeq_HeadWordSelectList( WORLDTRADE_WORK *wk )
{
	// �������I�����j���[�쐬
	wk->BmpListWork = WorldTrade_WordheadBmpListMake( wk, &wk->BmpMenuList, &wk->MenuWin[0], wk->MsgManager );
	wk->listpos = 0xffff;
	wk->subprocess_seq = SUBSEQ_HEADWORD_SELECT_WAIT;

	return SEQ_MAIN;
	
}


//------------------------------------------------------------------
/**
 * @brief   �������I��҂�
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int SubSeq_HeadWordSelectWait( WORLDTRADE_WORK *wk )
{
	switch(WorldTrade_BmpListMain( wk->BmpListWork, &wk->listpos )){
	case 1: case 2: case 3: case 4: case 5:	case 6: case 7: case 8: case 9: case 10:
		BmpListExit( wk->BmpListWork, &wk->dw->headwordListPos, &wk->dw->headwordPos );
		BMP_MENULIST_Delete( wk->BmpMenuList );
		wk->subprocess_seq  = SUBSEQ_POKENAME_SELECT_LIST;
		Snd_SePlay(WORLDTRADE_DECIDE_SE);

		break;

	// �L�����Z��
	case BMPMENU_CANCEL:
		BmpListExit( wk->BmpListWork, &wk->dw->headwordListPos, &wk->dw->headwordPos );
		BMP_MENULIST_Delete( wk->BmpMenuList );
		BmpMenuWinClear( &wk->MenuWin[0], WINDOW_TRANS_ON );
		BmpTalkWinClear( &wk->MsgWin, WINDOW_TRANS_ON );
		GF_BGL_BmpWinDel( &wk->MenuWin[0] );
		GF_BGL_BmpWinDel( &wk->MenuWin[1] );

		WorldTrade_SubProcessChange( wk, WORLDTRADE_MYBOX, MODE_DEPOSIT_SELECT );
		wk->subprocess_seq = SUBSEQ_END;
		Snd_SePlay(WORLDTRADE_DECIDE_SE);
		break;
	}
	
	return SEQ_MAIN;
}


//------------------------------------------------------------------
/**
 * @brief   �|�P�������O�I�����X�g�쐬
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int SubSeq_PokeNameSelectList( WORLDTRADE_WORK *wk )
{
	// �|�P���������X�g�쐬
	wk->BmpListWork = WorldTrade_PokeNameListMake( wk,
						&wk->BmpMenuList, &wk->MenuWin[1], 
						wk->MsgManager, wk->MonsNameManager,wk->dw,
						wk->param->zukanwork );
	wk->listpos = 0xffff;

	OS_Printf("in trade �}�Ӄt���O = %d\n", ZukanWork_GetZenkokuZukanFlag(wk->param->zukanwork));


	wk->subprocess_seq = SUBSEQ_POKENAME_SELECT_WAIT;

	return SEQ_MAIN;
	
}

//------------------------------------------------------------------
/**
 * @brief   �|�P�����̐��ʕ��z���琫�ʂ͌��肷�邩�H���͂��K�v���H
 *
 * @param   dtp		
 * @param   sex_selection		
 *
 * @retval  int		0:���ʂ̓��͂��K�v	1:���肵�Ă���̂ŕK�v�Ȃ�
 */
//------------------------------------------------------------------
int WorldTrade_SexSelectionCheck( Dpw_Tr_PokemonSearchData *dtsd, int sex_selection ) 
{
	switch(sex_selection){
	case MONS_MALE:
		dtsd->gender = PARA_MALE+1;
		return 1;
		break;
	case MONS_FEMALE:
		dtsd->gender = PARA_FEMALE+1;
		return 1;
		break;
	case MONS_UNKNOWN:
		dtsd->gender = PARA_UNK+1;
		return 1;
		break;
	}
	
	return 0;
}


//------------------------------------------------------------------
/**
 * @brief   �|�P�������O�I��
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int SubSeq_PokeNameSelectWait( WORLDTRADE_WORK *wk )
{
	u32 result;
	int sex;
	
	switch((result=WorldTrade_BmpListMain( wk->BmpListWork, &wk->listpos ))){
	case BMPLIST_NULL:
		break;

	// �L�����Z��
	case BMPMENU_CANCEL:
		BmpListExit( wk->BmpListWork, &wk->dw->nameListPos, &wk->dw->namePos );
		BMP_MENULIST_Delete( wk->BmpMenuList );
		BmpMenuWinClear( &wk->MenuWin[1], WINDOW_TRANS_ON );
		GF_BGL_BmpWinDel( &wk->MenuWin[0] );
		GF_BGL_BmpWinDel( &wk->MenuWin[1] );		
		wk->subprocess_seq  = SUBSEQ_START;
		Snd_SePlay(WORLDTRADE_DECIDE_SE);
		
		WorldTrade_SelectNameListBackup( &wk->selectListPos, wk->dw->headwordListPos+wk->dw->headwordPos, wk->dw->nameListPos, wk->dw->namePos );

		break;
	// �I��
	default:
		BmpListExit( wk->BmpListWork, &wk->dw->nameListPos, &wk->dw->namePos );
		BMP_MENULIST_Delete( wk->BmpMenuList );
		BmpMenuWinClear( &wk->MenuWin[0], WINDOW_TRANS_ON );
		BmpMenuWinClear( &wk->MenuWin[1], WINDOW_TRANS_ON );
		GF_BGL_BmpWinDel( &wk->MenuWin[0] );
		GF_BGL_BmpWinDel( &wk->MenuWin[1] );
		wk->Want.characterNo = result;
		Snd_SePlay(WORLDTRADE_DECIDE_SE);

		// ���ʕ��z���擾 
		wk->dw->sex_selection = PokePersonalParaGet(result,ID_PER_sex);
		// ���ʂ͌Œ肩�H�i�Œ�̏ꍇ�͐��ʂ�Want�Ɋi�[�����j
		if(WorldTrade_SexSelectionCheck( &wk->Want, wk->dw->sex_selection )){
			// ���ʂ͌��肵�Ă���̂ŁA���͂���K�v������
			wk->subprocess_seq  = SUBSEQ_LEVEL_SELECT_MES;
			sex                 = wk->Want.gender;
		}else{
			// ���ʂ͌��肵�Ă��Ȃ��̂œ��͂��K�v
			wk->subprocess_seq  = SUBSEQ_SEX_SELECT_MES;
			sex = DPW_TR_GENDER_NONE;
		}

		// ���O����(���ʂ����܂邱�Ƃ�����j
		WodrldTrade_PokeWantPrint( wk->MsgManager, wk->MonsNameManager, wk->WordSet, 
							&wk->InfoWin[0], wk->Want.characterNo,sex,-1);

		WorldTrade_SelectNameListBackup( &wk->selectListPos, wk->dw->headwordListPos+wk->dw->headwordPos, wk->dw->nameListPos, wk->dw->namePos );

		break;

	}
	
	return SEQ_MAIN;
}



//------------------------------------------------------------------
/**
 * @brief   ���ʂ�I��ł����������b�Z�[�W
 *
 * @param   wk		
 *
 * @retval  int 			
 */
//------------------------------------------------------------------
static int 	SubSeq_SexSelctMessage( WORLDTRADE_WORK *wk )
{
	// �|�P�����̐��ʂ�I��ł�������
	SubSeq_MessagePrint( wk, msg_gtc_01_011, 1, 0, 0x0f0f );
	WorldTrade_SetNextSeq( wk, SUBSEQ_MES_WAIT, SUBSEQ_SEX_SELECT_LIST );

	// ���ʑI���E�C���h�E�m��
	GF_BGL_BmpWinAdd(wk->bgl, &wk->MenuWin[0], GF_BGL_FRAME0_M,
		SELECT_MENU3_X,		SELECT_MENU3_Y,		SELECT_MENU3_SX, 		SELECT_MENU3_SY, 
		WORLDTRADE_TALKFONT_PAL,  SELECT_MENU3_OFFSET );
	GF_BGL_BmpWinDataFill( &wk->MenuWin[0], 0x0000 );
	
	return SEQ_MAIN;
}

//------------------------------------------------------------------
/**
 * @brief   ���ʑI�����X�g�쐬�E�\��
 *
 * @param   wk		
 *
 * @retval  int 			
 */
//------------------------------------------------------------------
static int 	SubSeq_SexSelctList( WORLDTRADE_WORK *wk )
{
	wk->BmpListWork = WorldTrade_SexSelectListMake( &wk->BmpMenuList, &wk->MenuWin[0], wk->MsgManager );
	wk->listpos = 0xffff;

	wk->subprocess_seq = SUBSEQ_SEX_SELECT_WAIT;

	
	return SEQ_MAIN;
}


//------------------------------------------------------------------
/**
 * @brief   ���ʑI�����X�g�I��҂�
 *
 * @param   wk		
 *
 * @retval  int 			
 */
//------------------------------------------------------------------
static int 	SubSeq_SexSelctWait( WORLDTRADE_WORK *wk )
{
	u32 result;
	switch((result=WorldTrade_BmpListMain( wk->BmpListWork, &wk->listpos ))){
	// �L�����Z��
	case BMPMENU_CANCEL:
		BmpListExit( wk->BmpListWork, NULL, NULL );
		BMP_MENULIST_Delete( wk->BmpMenuList );
		BmpMenuWinClear( &wk->MenuWin[0], WINDOW_TRANS_ON );
		BmpTalkWinClear( &wk->MsgWin, WINDOW_TRANS_ON );
		GF_BGL_BmpWinDel( &wk->MenuWin[0] );
		Snd_SePlay(WORLDTRADE_DECIDE_SE);

		wk->subprocess_seq = SUBSEQ_START;
		break;
	// �I��
	case PARA_MALE: case PARA_FEMALE: case PARA_UNK: 
		BmpListExit( wk->BmpListWork, NULL, NULL );
		BMP_MENULIST_Delete( wk->BmpMenuList );
		BmpMenuWinClear( &wk->MenuWin[0], WINDOW_TRANS_ON );
		GF_BGL_BmpWinDel( &wk->MenuWin[0] );
		Snd_SePlay(WORLDTRADE_DECIDE_SE);

		wk->Want.gender			= result+1;
		wk->subprocess_seq  = SUBSEQ_LEVEL_SELECT_MES;

		// ���ʌ���
		WodrldTrade_PokeWantPrint( wk->MsgManager, wk->MonsNameManager, wk->WordSet, 
							&wk->InfoWin[0], wk->Want.characterNo,wk->Want.gender,-1);

		break;
	}

	return SEQ_MAIN;
}


//------------------------------------------------------------------
/**
 * @brief   ���x����I��ł����������b�Z�[�W�\��
 *
 * @param   wk		
 *
 * @retval  static		
 */
//------------------------------------------------------------------
static int SubSeq_LevelSelectMessage( WORLDTRADE_WORK *wk )
{
	// �|�P�����̃��x�������߂Ă�������
	SubSeq_MessagePrint( wk, msg_gtc_01_012, 1, 0, 0x0f0f );
	WorldTrade_SetNextSeq( wk, SUBSEQ_MES_WAIT, SUBSEQ_LEVEL_SELECT_LIST );

	// ���ʑI���E�C���h�E�m��
	GF_BGL_BmpWinAdd(wk->bgl, &wk->MenuWin[0], GF_BGL_FRAME0_M,
		SELECT_MENU4_X,		SELECT_MENU4_Y,		SELECT_MENU4_SX, 		SELECT_MENU4_SY, 
		WORLDTRADE_TALKFONT_PAL,  SELECT_MENU4_OFFSET );
	GF_BGL_BmpWinDataFill( &wk->MenuWin[0], 0x0000 );

	return SEQ_MAIN;
}



//------------------------------------------------------------------
/**
 * @brief   ���x���I�����X�g�쐬�E�\��
 *
 * @param   wk		
 *
 * @retval  static		
 */
//------------------------------------------------------------------
static int SubSeq_LevelSelectList( WORLDTRADE_WORK *wk )
{
	// ���x���I�����X�g�쐬
	wk->BmpListWork = WorldTrade_LevelListMake(&wk->BmpMenuList, &wk->MenuWin[0], wk->MsgManager );
	wk->listpos = 0xffff;

	wk->subprocess_seq = SUBSEQ_LEVEL_SELECT_WAIT;

	return SEQ_MAIN;
}


//------------------------------------------------------------------
/**
 * @brief   ���x���I��҂�
 *
 * @param   wk		
 *
 * @retval  static		
 */
//------------------------------------------------------------------
static int SubSeq_LevelSelectWait( WORLDTRADE_WORK *wk )
{
	u32 result;
	switch((result=WorldTrade_BmpListMain( wk->BmpListWork, &wk->listpos ))){
	case BMPLIST_NULL:
		break;
	// �L�����Z��
	case BMPMENU_CANCEL:
	case 12:
		BmpListExit( wk->BmpListWork, NULL, NULL );
		BMP_MENULIST_Delete( wk->BmpMenuList );
		BmpMenuWinClear( &wk->MenuWin[0], WINDOW_TRANS_ON );
		BmpTalkWinClear( &wk->MsgWin, WINDOW_TRANS_ON );
		GF_BGL_BmpWinDel( &wk->MenuWin[0] );
		Snd_SePlay(WORLDTRADE_DECIDE_SE);
		
		// �|�P�����̐��ʂ��Œ肩�ǂ������`�F�b�N���Ė߂�
		if(WorldTrade_SexSelectionCheck( &wk->Want, wk->dw->sex_selection )){
			// ���ʂ͌Œ薳���̂ŁA�|�P�����I���܂Ŗ߂�
			wk->subprocess_seq = SUBSEQ_START;
		}else{
			// ���ʓ��͂��K�v
			wk->subprocess_seq = SUBSEQ_SEX_SELECT_MES;
		}
		break;
	// ���x���w�茈��
	default: 
		Snd_SePlay(WORLDTRADE_DECIDE_SE);
		BmpListExit( wk->BmpListWork, NULL, NULL );
		BMP_MENULIST_Delete( wk->BmpMenuList );
		BmpMenuWinClear( &wk->MenuWin[0], WINDOW_TRANS_ON );
		GF_BGL_BmpWinDel( &wk->MenuWin[0] );

		WorldTrade_LevelMinMaxSet(&wk->Want, result);
		wk->subprocess_seq  = SUBSEQ_DEPOSITOK_MESSAGE;

		// ���x���w�茈��
		WodrldTrade_PokeWantPrint( wk->MsgManager, wk->MonsNameManager, wk->WordSet, 
						&wk->InfoWin[0], wk->Want.characterNo,wk->Want.gender,
						WorldTrade_LevelTermGet(wk->Want.level_min,wk->Want.level_max));

		break;
	}

	return SEQ_MAIN;
}


//------------------------------------------------------------------
/**
 * @brief   ���̏����ł悢�H���b�Z�[�W�\��
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int SubSeq_DepositOkMessage( WORLDTRADE_WORK *wk )
{
	// ���̂��傤����ł�낵���ł����H
	SubSeq_MessagePrint( wk, msg_gtc_01_024, 1, 0, 0x0f0f );
	WorldTrade_SetNextSeq( wk, SUBSEQ_MES_WAIT, SUBSEQ_DEPOSIT_YESNO );
	
	return SEQ_MAIN;
}

//------------------------------------------------------------------
/**
 * @brief   ����ŏ����ł������܂��H�͂��E������
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int SubSeq_DepositOkYesNo( WORLDTRADE_WORK *wk )
{

	wk->YesNoMenuWork = WorldTrade_BmpWinYesNoMake(wk->bgl, WORLDTRADE_YESNO_PY1, YESNO_OFFSET );
	wk->subprocess_seq = SUBSEQ_DEPOSIT_YESNO_WAIT;

	return SEQ_MAIN;
}

//------------------------------------------------------------------
/**
 * @brief   �͂��E�������҂�
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int SubSeq_DepositOkYesNoWait( WORLDTRADE_WORK *wk )
{
	int ret = BmpYesNoSelectMain( wk->YesNoMenuWork, HEAPID_WORLDTRADE );

	if(ret!=BMPMENU_NULL){
		if(ret==BMPMENU_CANCEL){
			// ���������|�P�����I�������蒼��
			WorldTrade_SubProcessChange( wk, WORLDTRADE_MYBOX, MODE_DEPOSIT_SELECT );
			wk->subprocess_seq  = SUBSEQ_END;
		}else{
			// �͂����|�P��������������
		 	WorldTrade_SubProcessChange( wk, WORLDTRADE_UPLOAD, MODE_UPLOAD );
			wk->subprocess_seq  = SUBSEQ_END;
			wk->sub_out_flg = 1;

			// �T�[�o�[�A�b�v���[�h�p�̃f�[�^���쐬
			DepositPokemonDataMake( &wk->UploadPokemonData, wk );
		}
	}

	return SEQ_MAIN;
	
}














//------------------------------------------------------------------
/**
 * @brief   �T�u�v���Z�X�V�[�P���X�I������
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int SubSeq_End( WORLDTRADE_WORK *wk )
{
	// �ڑ���ʂ�������A�㉺��ʂŃt�F�[�h
	if(wk->sub_nextprocess==WORLDTRADE_ENTER ){
		WIPE_SYS_Start( WIPE_PATTERN_WMS, WIPE_TYPE_FADEOUT, WIPE_TYPE_FADEOUT, WIPE_FADE_BLACK, WORLDTRADE_WIPE_SPPED, 1, HEAPID_WORLDTRADE );
#ifdef GTS_FADE_OSP
		OS_Printf( "******************** worldtrade_deposit.c [1165] MS ********************\n" );
#endif
		wk->sub_out_flg = 1;
	}else{
		// �����̉�ʂɂ����ꍇ�͏��ʂ����t�F�[�h
		WIPE_SYS_Start( WIPE_PATTERN_M, WIPE_TYPE_FADEOUT, WIPE_TYPE_FADEOUT, WIPE_FADE_BLACK, WORLDTRADE_WIPE_SPPED, 1, HEAPID_WORLDTRADE );
#ifdef GTS_FADE_OSP
		OS_Printf( "******************** worldtrade_deposit.c [1171] M ********************\n" );
#endif
	}
	wk->subprocess_seq = 0;
	
	return SEQ_FADEOUT;
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
static int SubSeq_MessageWait( WORLDTRADE_WORK *wk )
{
	if( GF_MSG_PrintEndCheck( wk->MsgIndex )==0){
		wk->subprocess_seq = wk->subprocess_nextseq;
	}
	return SEQ_MAIN;

}













// ���ʃA�C�R����\�����邽�߂̃J���[�w��
static GF_PRINTCOLOR sex_mark_col[]={
	GF_PRINTCOLOR_MAKE(5,6,0),
	GF_PRINTCOLOR_MAKE(3,4,0),
};


//==============================================================================
/**
 * @brief   
 *
 * @param   win		
 * @param   nameman		
 * @param   monsno		
 * @param   flag		
 * @param   color		
 *
 * @retval  none		
 */
//==============================================================================
void WorldTrade_PokeNamePrint( GF_BGL_BMPWIN *win, MSGDATA_MANAGER *nameman, int monsno, int flag, int y, GF_PRINTCOLOR color )
{
	STRBUF *namebuf;

	// ���O
	if(monsno!=0){
		namebuf = MSGMAN_AllocString( nameman, monsno );
		WorldTrade_SysPrint( win, namebuf, 0, y, flag, color );
		STRBUF_Delete(namebuf);
	}

}




//------------------------------------------------------------------
/**
 * @brief   
 *
 * @param   sex		
 * @param   color		
 *
 * @retval  GF_PRINTCOLOR		
 */
//------------------------------------------------------------------
static GF_PRINTCOLOR GetSexColor( int sex, GF_PRINTCOLOR color )
{

	if(sex==DPW_TR_GENDER_MALE){
		return sex_mark_col[0];
	}else if(sex==DPW_TR_GENDER_FEMALE){
		return sex_mark_col[1];
	}
	return color;
}

// ���ʕ�����̃e�[�u���u���ɂ��Ȃ��E���E���E���ɂ��Ȃ��v
const int WorldTrade_SexStringTable[]={
	msg_gtc_11_001,
	msg_gtc_11_002,
	msg_gtc_11_003,
	msg_gtc_11_001,
	
};

//==============================================================================
/**
 * @brief   ���ʂ�\������
 *
 * @param   win		
 * @param   msgman		
 * @param   sex		
 * @param   flag	�u���ɂ��Ȃ��v��\�����邩�ǂ���
 * @param   color	
 *
 * @retval  none		
 */
//==============================================================================
void WorldTrade_SexPrint( GF_BGL_BMPWIN *win, MSGDATA_MANAGER *msgman, int sex, int flag, int y, int printflag, GF_PRINTCOLOR color )
{
	STRBUF *sexbuf;

	OS_Printf("SEX Print flag = %d, sex = %d\n", flag, sex);

	if(flag==0 && sex==DPW_TR_GENDER_NONE){
		// ���ʖ�����\�����Ȃ��Ă��������͕\�����Ȃ�
		return;
	}
	
	sexbuf = MSGMAN_AllocString( msgman, WorldTrade_SexStringTable[sex]  );
	// flag��3�ȓ��̏ꍇ�̓Z���^�����O�w��E�ȏ�̏ꍇ�͂w���W�w��
	if(printflag > 3){
		WorldTrade_SysPrint( win, sexbuf,   printflag, y, 0, GetSexColor( sex, color ) );
	}else{
		WorldTrade_SysPrint( win, sexbuf,   0, y, printflag, GetSexColor( sex, color ) );
	}
	STRBUF_Delete(sexbuf);
}

//==============================================================================
/**
 * @brief   ���x�������̕�����`����s��
 *
 * @param   win		
 * @param   msgman		
 * @param   sex		
 * @param   flag		
 * @param   color		
 *
 * @retval  none		
 */
//==============================================================================
void WorldTrade_WantLevelPrint( GF_BGL_BMPWIN *win, MSGDATA_MANAGER *msgman, int level, int flag, int y, GF_PRINTCOLOR color )
{
	STRBUF *levelbuf;

	if(level!=-1){
		levelbuf = MSGMAN_AllocString( msgman, level_minmax_table[level].msg );
		WorldTrade_SysPrint( win, levelbuf,  0, y, flag, color );
		STRBUF_Delete(levelbuf);
	}
}
//------------------------------------------------------------------
/**
 * @brief   �������ė~�����|�P�����̏�����`�悷��
 *
 * @param   MsgManager		
 * @param   MonsNameManager
 * @param   WordSet		
 * @param   win[]		
 * @param   monsno		
 * @param   sex		
 * @param   level		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
void WodrldTrade_PokeWantPrint( MSGDATA_MANAGER *MsgManager, MSGDATA_MANAGER *MonsNameManager,
	WORDSET *WordSet, GF_BGL_BMPWIN win[], int monsno, int sex, int level )
{
	STRBUF *strbuf;
	int i;

	//�u�ق����|�P�����v�`��
	strbuf = MSGMAN_AllocString( MsgManager, msg_gtc_05_008 );
	WorldTrade_SysPrint( &win[0], strbuf,    0, 0, 0, GF_PRINTCOLOR_MAKE(15,2,0) );

	// ���O�E���ʁE���x���̗��̓N���A����
	for(i=1;i<3;i++){
		GF_BGL_BmpWinDataFill( &win[i], 0x0000 );
	}

	// ���O
	WorldTrade_PokeNamePrint(&win[1], MonsNameManager, monsno, 0, 0,GF_PRINTCOLOR_MAKE(15,2,0) );

	// ����
	if( sex==DPW_TR_GENDER_MALE || sex==DPW_TR_GENDER_FEMALE ){
		OS_Printf("���ʕ`�悵�� %d\n", sex);
		WorldTrade_SexPrint( &win[1], MsgManager, sex, 0, 0, 70, GF_PRINTCOLOR_MAKE(15,2,0) );
	}else{
		OS_Printf("���ʕ`�悵�ĂȂ� %d\n");
	
	}

	// ���x���w��
	WorldTrade_WantLevelPrint( &win[2], MsgManager, level, 2, 0, GF_PRINTCOLOR_MAKE(15,2,0) );
	
	

	STRBUF_Delete(strbuf);
}

//------------------------------------------------------------------
/**
 * @brief   �������ė~�����|�P�����̏�����`�悷��
 *
 * @param   MsgManager		
 * @param   MonsNameManager
 * @param   WordSet		
 * @param   win[]		
 * @param   monsno		
 * @param   sex		
 * @param   level		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
void WodrldTrade_MyPokeWantPrint( MSGDATA_MANAGER *MsgManager, MSGDATA_MANAGER *MonsNameManager,
	WORDSET *WordSet, GF_BGL_BMPWIN win[], int monsno, int sex, int level )
{
	STRBUF *strbuf;
	int i;

	//�u�ق����|�P�����v�`��
	strbuf = MSGMAN_AllocString( MsgManager, msg_gtc_05_008 );
	WorldTrade_SysPrint( &win[0], strbuf,    0, 0, 0, GF_PRINTCOLOR_MAKE(15,2,0) );

	// ���O�E���ʁE���x���̗��̓N���A����
	for(i=1;i<3;i++){
		GF_BGL_BmpWinDataFill( &win[i], 0x0000 );
	}

	// ���O
	WorldTrade_PokeNamePrint(&win[1], MonsNameManager, monsno, 0, 0,GF_PRINTCOLOR_MAKE(15,2,0) );

	// ����
	if( sex==DPW_TR_GENDER_MALE || sex==DPW_TR_GENDER_FEMALE ){
		OS_Printf("���ʕ`�悵�� %d\n", sex);
		WorldTrade_SexPrint( &win[1], MsgManager, sex, 0, 0, 70, GF_PRINTCOLOR_MAKE(15,2,0) );
	}else{
		OS_Printf("���ʕ`�悵�ĂȂ�\n");
	}

	// ���x���w��
	WorldTrade_WantLevelPrint( &win[2], MsgManager, level, 2, 0, GF_PRINTCOLOR_MAKE(15,2,0) );
	
	

	STRBUF_Delete(strbuf);
}

//------------------------------------------------------------------
/**
 * @brief   ������a���悤�Ƃ���|�P�����̏���`�悷��
 *
 * @param   MsgManager		
 * @param   WordSet		
 * @param   win[]		
 * @param   ppp		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void PokeDepositPrint( 
	MSGDATA_MANAGER *MsgManager, 
	WORDSET *WordSet, 
	GF_BGL_BMPWIN win[], 
	POKEMON_PASO_PARAM *ppp,
	Dpw_Tr_PokemonDataSimple *post )
{
	STRBUF *strbuf,	*levelbuf;
	STRBUF *namebuf = STRBUF_Create( MONS_NAME_SIZE+EOM_SIZE, HEAPID_WORLDTRADE );
	STRBUF *sexbuf = STRBUF_Create( MONS_NAME_SIZE+EOM_SIZE, HEAPID_WORLDTRADE );
	int sex, level,i;
	
	OS_TPrintf("deposit_ppp3 = %08x", ppp);
	
	// ��������|�P����

	// ���O�E���ʁE���x���擾
	PokePasoParaGet(ppp, ID_PARA_nickname_buf, namebuf );
	sex   = PokePasoParaGet( ppp, ID_PARA_sex,   NULL )+1;
	level = PokePasoLevelCalc(ppp);
	
	OS_Printf("sex=%d, level=%d\n",sex, level);
	
	// �u��������|�P�����v�E���ʃA�C�R��������擾
	strbuf = MSGMAN_AllocString( MsgManager, msg_gtc_05_011  );
	WORDSET_RegisterNumber( WordSet, 3, level, 3, NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );
	levelbuf = MSGDAT_UTIL_AllocExpandString( WordSet, MsgManager, msg_gtc_05_013, HEAPID_WORLDTRADE );
	if(sex!=DPW_TR_GENDER_NONE){
		MSGMAN_GetString( MsgManager, WorldTrade_SexStringTable[sex], sexbuf );
	}

	// �`��̑O�ɃN���A
	for(i=0;i<3;i++){
		GF_BGL_BmpWinDataFill( &win[i], 0x0000 );
	}

	// �`��
	WorldTrade_SysPrint( &win[0], strbuf,    0, 0, 0, GF_PRINTCOLOR_MAKE(15,2,0) );
	WorldTrade_SysPrint( &win[1], namebuf,   0, 0, 0, GF_PRINTCOLOR_MAKE(15,2,0) );
	WorldTrade_SysPrint( &win[2], levelbuf,  0, 0, 2, GF_PRINTCOLOR_MAKE(15,2,0) );
	if(sex!=DPW_TR_GENDER_NONE){
		WorldTrade_SysPrint( &win[1], sexbuf,   70, 0, 0, sex_mark_col[sex-1] );
	}

	post->characterNo = PokePasoParaGet(ppp, ID_PARA_monsno, NULL);
	post->gender      = sex;
	post->level       = level;

	STRBUF_Delete( levelbuf );
	STRBUF_Delete( sexbuf   );
	STRBUF_Delete( namebuf  );
	STRBUF_Delete( strbuf   );
}

#define ZKN_SORTDATA_ONESIZE	( sizeof(u16) )

//------------------------------------------------------------------
/**
 * @brief   ������\�[�g�f�[�^�擾�i�������������j�B����͂��Ԃ�ŁB
 *			
 * @param   heap		
 * @param   idx		
 * @param   p_arry_num		
 *
 * @retval  u16*		
 */
//------------------------------------------------------------------
u16* WorldTrade_ZukanSortDataGet( int heap, int idx, int* p_arry_num )
{
	u32 size;
	u16* p_buf;
	
	// �ǂݍ���
	p_buf = ArcUtil_LoadEx( ARC_ZUKAN_DATA, NARC_zukan_data_zkn_sort_aiueo_dat, FALSE, heap, ALLOC_TOP, &size );

	*p_arry_num = size / ZKN_SORTDATA_ONESIZE;

	return p_buf;
	
	// �|�P�����̖��O���擾����
	//STRBUF* MSGDAT_UTIL_GetMonsName( u32 monsno, u32 heapID )
}

//==============================================================================
/**
 * @brief   �V���I�E�}�Ӄf�[�^��ǂݍ���			����͂��Ԃ��
 *			�V���I�E�}�ӂ̏��ɊJ��NO�������Ă���̂ŁA
 *			�V���Ƀe�[�u�����m�ۂ��āu���̊J��NO�̓V���I�E���H�v�̍쐬������
 *
 * @param   heap		
 * @param   p_arry_num	MONS_END+1
 *
 * @retval  u16 *		494���̃V���I�E�}�ӂ��ǂ����̃t���O���������e�[�u��
 */
//==============================================================================
u8 *WorldTrade_SinouZukanDataGet( int heap  )
{
	u32 size,num,i;
	u16* p_buf;

	// �e�[�u���m�ہE������
	u8 *sinouData = sys_AllocMemory( HEAPID_WORLDTRADE, MONSNO_END+1 );
	MI_CpuClearFast( sinouData, MONSNO_END+1 );

	// �V���I�E�}�Ӄe�[�u��
	p_buf = ArcUtil_LoadEx( ARC_ZUKAN_DATA, NARC_zukan_data_zkn_sort_shinoh_dat, FALSE, heap, ALLOC_TOP, &size );
	
	num = size / ZKN_SORTDATA_ONESIZE;

	// �t���O�e�[�u���ɍ�蒼��
	for(i=0;i<num;i++){
		if(p_buf[i]<MONSNO_END+1){
			sinouData[p_buf[i]] = 1;
		}
	}

	sys_FreeMemoryEz(p_buf);

	return sinouData;
	
}


//==============================================================================
/**
 * @brief   �T�[�o�[�ɑ��M�����{�����i�[����
 *
 * @param   dtd		
 * @param   wk		
 *
 * @retval  none		
 */
//==============================================================================
void WorldTrade_PostPokemonBaseDataMake( Dpw_Tr_Data *dtd, WORLDTRADE_WORK *wk )
{
	STRCODE *name;
	// �|�P�����\���̂���
	
	if(WorldTrade_GetPPorPPP( wk->BoxTrayNo )){
		// POKEMON_PARAM�Ƃ��ăR�s�[
		MI_CpuCopyFast( wk->deposit_ppp, dtd->postData.data,  PokemonParam_GetWorkSize() );
	}else{
		// POKEMON_PASO_PARAM�Ȃ̂�Replace�֐���POKEMON_PARAM�ɓ��t������
		PokeReplace(wk->deposit_ppp,(POKEMON_PARAM *)dtd->postData.data);
	}

	// �g���[�i�[���R�s�[
	PM_strncpy( dtd->name, MyStatus_GetMyName(wk->param->mystatus), DPW_TR_NAME_SIZE );

	
	// ID
	dtd->trainerID   = MyStatus_GetID_Low( wk->param->mystatus );

	// ���E�n��
	dtd->countryCode = WIFIHISTORY_GetMyNation( wk->param->wifihistory );
	dtd->localCode   = WIFIHISTORY_GetMyArea( wk->param->wifihistory );

	// ������
	dtd->trainerType = MyStatus_GetTrainerView( wk->param->mystatus );

	// ����
	dtd->gender      = MyStatus_GetMySex( wk->param->mystatus );

	// �o�[�W�����E���R�[�h
	dtd->versionCode = PM_VERSION;
	dtd->langCode    = PM_LANG;
	
}


//------------------------------------------------------------------
/**
 * @brief   �|�P������a����̂ɕK�v�ȃf�[�^���쐬����
 *
 * @param   dtd		
 * @param   wk		
 *
 * @retval  none	
 */
//------------------------------------------------------------------
static void DepositPokemonDataMake( Dpw_Tr_Data *dtd, WORLDTRADE_WORK *wk )
{

	// ��{�����i�[�i�|�P�����E�g���[�i�[���E���E�n��E�����ڂȂǁj
	WorldTrade_PostPokemonBaseDataMake( dtd, wk );
	
	// �ق����|�P���������i�[
	dtd->postSimple = wk->Post;
	dtd->wantSimple = wk->Want;

	OS_Printf( "postData  No = %d,  gender = %d, level min= %d\n", wk->Post.characterNo, wk->Post.gender, wk->Post.level);
	OS_Printf( "WantData  No = %d,  gender = %d, level min= %d\n", wk->Want.characterNo, wk->Want.gender, wk->Want.level_min);


	OS_Printf( "TrainerId = %05d,  nation = %d, area = %d\n", dtd->trainerID, dtd->countryCode, dtd->localCode);
	OS_Printf( "Version   = %d,  language = %d, \n", dtd->versionCode, dtd->langCode);


}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// BMPLIST�֌W
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------

#define DEPOSIT_HEADWORD_NUM	( 10 )
#define DEPOSIT_Y_NUM			(  6 )

///BMPLIST�p��`
static const BMPLIST_HEADER MenuListHeader = {
    NULL,			// �\�������f�[�^�|�C���^
    NULL,					// �J�[�\���ړ����Ƃ̃R�[���o�b�N�֐�
    NULL,					// ���\�����Ƃ̃R�[���o�b�N�֐�
    NULL,					// 
    DEPOSIT_HEADWORD_NUM,	// ���X�g���ڐ�
    DEPOSIT_Y_NUM,			// �\���ő區�ڐ�
    4,						// ���x���\���w���W
    8,						// ���ڕ\���w���W
    0,						// �J�[�\���\���w���W
    2,						// �\���x���W
    FBMP_COL_BLACK,			// �����F
    FBMP_COL_WHITE,			// �w�i�F
    FBMP_COL_BLK_SDW,		// �����e�F
    0,						// �����Ԋu�w
    16,						// �����Ԋu�x
    BMPLIST_LRKEY_SKIP,		// �y�[�W�X�L�b�v�^�C�v
    FONT_SYSTEM,			// �����w��
    0,						// �a�f�J�[�\��(allow)�\���t���O(0:ON,1:OFF)
    NULL,                   // ���[�N
};



//==============================================================================
/**
 * @brief   �������I�����j���[�쐬
 *
 * @param  none
 *
 * @retval  none		
 */
//==============================================================================
BMPLIST_WORK *WorldTrade_WordheadBmpListMake( WORLDTRADE_WORK *wk, BMP_MENULIST_DATA **menulist, GF_BGL_BMPWIN *win, MSGDATA_MANAGER *MsgManager )
{
	BMPLIST_HEADER list_h;
	int i;

	*menulist = BMP_MENULIST_Create( 10, HEAPID_WORLDTRADE );
	for(i=0;i<10;i++){
		BMP_MENULIST_AddArchiveString( *menulist, MsgManager, msg_gtc_10_001+i, i+1 );
	}

    list_h       = MenuListHeader;
    list_h.list  = *menulist;
    list_h.win   = win;

	// �g�`��
	BmpMenuWinWrite( win, WINDOW_TRANS_ON, WORLDTRADE_MENUFRAME_CHR, WORLDTRADE_MENUFRAME_PAL );

	// BMP���j���[�J�n
    return BmpListSet(&list_h, wk->dw->headwordListPos, wk->dw->headwordPos, HEAPID_WORLDTRADE);

}

// �������e�[�u���i�\�[�g���ꂽ�|�P�����̉��ԖڂɁu�A�E�J�E�T�c�v���o�ꂷ�邩�H
static u16 NameHeadTable[]={
	ZKN_AKSTNHMYRW_IDX_A,
	ZKN_AKSTNHMYRW_IDX_K,
	ZKN_AKSTNHMYRW_IDX_S,
	ZKN_AKSTNHMYRW_IDX_T,
	ZKN_AKSTNHMYRW_IDX_N,
	ZKN_AKSTNHMYRW_IDX_H,
	ZKN_AKSTNHMYRW_IDX_M,
	ZKN_AKSTNHMYRW_IDX_Y,
	ZKN_AKSTNHMYRW_IDX_R,
	ZKN_AKSTNHMYRW_IDX_W,
	ZKN_AKSTNHMYRW_IDX_END,
};

//------------------------------------------------------------------
/**
 * @brief   �|�P�������A�T�O�����\�[�g���X�g�쐬
 *
 * @param   menulist	���X�g�f�[�^�i�����ɓo�^����j
 * @param   msgman		�|�P���������b�Z�[�W�f�[�^
 * @param   table		�T�O���������X�^�[�i���o�[�e�[�u��
 * @param   num			�|�P�����̑���
 * @param   select		�A�J�T�^�i�n�}�������̂ǂ��I���������H�i�A: 0�`9�܂Łj
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int PokeNameSortListMake( BMP_MENULIST_DATA **menulist, MSGDATA_MANAGER *monsnameman, 
									MSGDATA_MANAGER *msgman,u16 *table, u8 *sinou,
									int num, int select,ZUKAN_WORK *zukan )
{
	int i,index,see_count=0;
	int pokenum = NameHeadTable[select+1]-NameHeadTable[select];
	int flag    = ZukanWork_GetZenkokuZukanFlag(zukan);

	OS_TPrintf("select = %d, num = %d\n",select, pokenum);
	
	// �}�ӂƔ�ׂĉ��̌��Ă��邩���m�F
	index = NameHeadTable[select];
	for(i=0;i<pokenum;i++){
		// �S���}�ӂ��H
		if(flag){
			if(ZukanWork_GetPokeSeeFlag( zukan, table[index+i] )){
				OS_Printf(" SeeCheck i = %d, table[index+i] = %d\n", i, table[index+i]);
				see_count++;
			}
		}else{
			// �V���I�E�}�ӂɂ��邱�Ƃ��m�F������Ő}�Ӄ`�F�b�N
			if(sinou[table[index+i]]){
				if(ZukanWork_GetPokeSeeFlag( zukan, table[index+i] )){
					see_count++;
				}
			}
		
		}
	}

	// ���ڃ��X�g�̍쐬
	*menulist = BMP_MENULIST_Create( see_count+1, HEAPID_WORLDTRADE );


	// �|�P�������̓o�^
	for(i=0;i<pokenum;i++){
		// �S���}�ӂ��H
		if(flag){
			if(ZukanWork_GetPokeSeeFlag( zukan, table[index+i] )){
				OS_Printf(" ListAdd i = %d, table[index+i] = %d\n", i, table[index+i]);
				BMP_MENULIST_AddArchiveString( *menulist, monsnameman, table[index+i], table[index+i] );
			}
		}else{
			// �V���I�E�}�ӂɂ��邱�Ƃ��m�F������Ő}�Ӄ`�F�b�N
			if(sinou[table[index+i]]){
				if(ZukanWork_GetPokeSeeFlag( zukan, table[index+i] )){
					BMP_MENULIST_AddArchiveString( *menulist, monsnameman, table[index+i], table[index+i] );
				}
			}
		}
	}
	// �u���ǂ�v��o�^
	BMP_MENULIST_AddArchiveString( *menulist, msgman, msg_gtc_11_004, BMPMENU_CANCEL );

	return see_count+1;
}


//==============================================================================
/**
 * @brief   �|�P�������I�����X�g�쐬
 *
 * @param   menulist		
 * @param   win		
 * @param   MsgManager		
 * @param   MonsNameManager		
 * @param   dw		
 *
 * @retval  BMPLIST_WORK *		
 */
//==============================================================================
BMPLIST_WORK *WorldTrade_PokeNameListMake( WORLDTRADE_WORK *wk, BMP_MENULIST_DATA **menulist, GF_BGL_BMPWIN *win, 
			MSGDATA_MANAGER *MsgManager, MSGDATA_MANAGER *MonsNameManager, DEPOSIT_WORK* dw, ZUKAN_WORK *zukan)
{
	BMPLIST_HEADER list_h;
	int i,listnum,head;

	GF_BGL_BmpWinDataFill( win, 0x0f0f );

	head = dw->headwordListPos+dw->headwordPos;
	listnum = PokeNameSortListMake( menulist, MonsNameManager, MsgManager, 
									dw->nameSortTable, dw->sinouTable, 
									dw->nameSortNum, head, zukan );
	
	
    list_h       = MenuListHeader;
    list_h.count = listnum;
    list_h.list  = *menulist;
    list_h.win   = win;

	// �g�`��
	BmpMenuWinWrite( win, WINDOW_TRANS_ON, WORLDTRADE_MENUFRAME_CHR, WORLDTRADE_MENUFRAME_PAL );

	// BMP���j���[�J�n
    return BmpListSet(&list_h, wk->selectListPos.name_list[head],
    						   wk->selectListPos.name_pos[head], HEAPID_WORLDTRADE);

}


// �I�����X�g�p���ʃA�C�R����
static sex_select_table[][2]={
	{msg_gtc_11_001, PARA_UNK,},
	{msg_gtc_11_002, PARA_MALE,},
	{msg_gtc_11_003, PARA_FEMALE,} ,
	{msg_gtc_11_004, BMPMENU_CANCEL},
};

//==============================================================================
/**
 * @brief   �|�P�������ʑI�����X�g�쐬
 *
 * @param   menulist		
 * @param   win		
 * @param   MsgManager		
 *
 * @retval  BMPLIST_MENU *		
 */
//==============================================================================
BMPLIST_WORK *WorldTrade_SexSelectListMake( BMP_MENULIST_DATA **menulist, GF_BGL_BMPWIN *win, MSGDATA_MANAGER *MsgManager  )
{
	BMPLIST_HEADER list_h;
	int i;

	*menulist = BMP_MENULIST_Create( 4, HEAPID_WORLDTRADE );
	for(i=0;i<4;i++){
		BMP_MENULIST_AddArchiveString( *menulist, MsgManager, sex_select_table[i][0], sex_select_table[i][1] );
	}

    list_h       = MenuListHeader;
    list_h.count = 4;
    list_h.list  = *menulist;
    list_h.win   = win;

	// �g�`��
	BmpMenuWinWrite( win, WINDOW_TRANS_ON, WORLDTRADE_MENUFRAME_CHR, WORLDTRADE_MENUFRAME_PAL );

	// BMP���j���[�J�n
    return BmpListSet(&list_h, 0, 0, HEAPID_WORLDTRADE);
	
}



//==============================================================================
/**
 * @brief   ���x���I�����X�g�쐬
 *
 * @param   menulist		
 * @param   win		
 * @param   MsgManager		
 *
 * @retval  BMPLIST_WORK *		
 */
//==============================================================================
BMPLIST_WORK *WorldTrade_LevelListMake(BMP_MENULIST_DATA **menulist, GF_BGL_BMPWIN *win, MSGDATA_MANAGER *MsgManager  )
{
	BMPLIST_HEADER list_h;
	int i;

	*menulist = BMP_MENULIST_Create( LEVEL_SELECT_NUM, HEAPID_WORLDTRADE );
	for(i=0;i<LEVEL_SELECT_NUM;i++){
		BMP_MENULIST_AddArchiveString( *menulist, MsgManager, level_minmax_table[i].msg, i );
	}

    list_h       = MenuListHeader;
    list_h.count = LEVEL_SELECT_NUM;
    list_h.list  = *menulist;
    list_h.win   = win;

	// �g�`��
	BmpMenuWinWrite( win, WINDOW_TRANS_ON, WORLDTRADE_MENUFRAME_CHR, WORLDTRADE_MENUFRAME_PAL );

	// BMP���j���[�J�n
    return BmpListSet(&list_h, 0, 0, HEAPID_WORLDTRADE);

}


//==============================================================================
/**
 * @brief   ���x���w�������������
 *
 * @param   dtps		���������\����
 * @param   index		���������̓Y����
 *
 * @retval  none		
 */
//==============================================================================
void WorldTrade_LevelMinMaxSet( Dpw_Tr_PokemonSearchData *dtps, int index )
{
	GF_ASSERT(index<(LEVEL_SELECT_NUM-1));// ���x���w��̔z����ゾ����
	
	dtps->level_min = level_minmax_table[index].min;
	dtps->level_max = level_minmax_table[index].max;
}

//==============================================================================
/**
 * @brief   �w��̃��x�������̃C���f�b�N�X���擾����
 *
 * @param   min		�Œ�
 * @param   max		�ő僌�x��
 *
 * @retval  int		
 */
//==============================================================================
int WorldTrade_LevelTermGet( int min, int max )
{
	int i;
	
	for(i=0;i<LEVEL_SELECT_NUM;i++){
		if(level_minmax_table[i].min==min && level_minmax_table[i].max==max){
			return i;
		}
	}

	// ���x������������Ȃ���������Ƃ�����ASSERT�ɂ���ƁA��X���|���̂�
	// �u�Ȃ�ł�����v�ɂ��Ă���
	return 0;
}


//==============================================================================
/**
 * @brief   ���ʉ��ɑΉ�����BMPLISTMAIN�֐�
 *
 * @param   lw		
 * @param   posbackup		
 *
 * @retval  u32		
 */
//==============================================================================
u32 WorldTrade_BmpListMain( BMPLIST_WORK * lw, u16 *posbackup )
{
	u16 listpos;
	u32 result = BmpListMain( lw );

	BmpListDirectPosGet( lw, &listpos );

	if(*posbackup != listpos){
		if(*posbackup!=0xffff){
			Snd_SePlay(WORLDTRADE_MOVE_SE);
		}
		*posbackup = listpos;
		
	}

	return result;
}

//==============================================================================
/**
 * @brief   �I���ʒu�J�[�\�����̃N���A
 *
 * @param   slp		
 *
 * @retval  none		
 */
//==============================================================================
void WorldTrade_SelectListPosInit( SELECT_LIST_POS *slp)
{
	int i;
	
	for(i=0;i<NAME_HEAD_MAX;i++){
		slp->name_list[i] = 0;
		slp->name_pos[i]  = 0;
	}
	
	slp->head_list = 0;
	slp->head_pos  = 0;

	
}


//==============================================================================
/**
 * @brief   �J�[�\���ʒu�ۑ�
 *
 * @param   SELECT_LIST_POS		
 * @param   slp		
 * @param   head		
 * @param   list		
 * @param   pos		
 *
 * @retval  none		
 */
//==============================================================================
void WorldTrade_SelectNameListBackup( SELECT_LIST_POS *slp, int head, int list, int pos )
{
	slp->name_list[head] = list;
	slp->name_pos[head]  = pos;
}