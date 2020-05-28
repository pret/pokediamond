//============================================================================================
/**
 * @file	worldtrade_box.c
 * @bfief	���E���������{�b�N�X��ʏ���
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
#include "poketool/pokeicon.h"
#include "poketool/pokeparty.h"
#include "itemtool/item.h"

#include "savedata/wifilist.h"
#include "savedata/zukanwork.h"

#include "application/worldtrade.h"
#include "worldtrade_local.h"

#include "msgdata/msg_wifi_lobby.h"
#include "msgdata/msg_wifi_gtc.h"


#include "worldtrade.naix"			// �O���t�B�b�N�A�[�J�C�u��`


//============================================================================================
//	�^�錾
//============================================================================================
#define POKEICON_TRANS_CHARA	(4*4)
#define POKEICON_TRANS_SIZE		(POKEICON_TRANS_CHARA*0x20)

typedef struct {
  int vadrs;				// VRAM�A�h���X
  int palno;				// �p���b�g�ԍ�
  CLACT_WORK_PTR icon;			// CLACT
  u8 chbuf[POKEICON_TRANS_SIZE];	// �L�����N�^�o�b�t�@
} WORLDTRADE_POKEBUF;



//============================================================================================
//	�v���g�^�C�v�錾
//============================================================================================
/*** �֐��v���g�^�C�v ***/
static void BgInit( GF_BGL_INI * ini );
static void BgExit( GF_BGL_INI * ini );
static void BgGraphicSet( WORLDTRADE_WORK * wk );
static void SetCellActor(WORLDTRADE_WORK *wk);
static void DelCellActor( WORLDTRADE_WORK *wk );
static void BmpWinInit( WORLDTRADE_WORK *wk );
static void BmpWinDelete( WORLDTRADE_WORK *wk );
static void InitWork( WORLDTRADE_WORK *wk );
static void FreeWork( WORLDTRADE_WORK *wk );
static int SubSeq_Start( WORLDTRADE_WORK *wk);
static int SubSeq_Main( WORLDTRADE_WORK *wk);
static int SubSeq_End( WORLDTRADE_WORK *wk);
static int SubSeq_YesNo( WORLDTRADE_WORK *wk);
static int SubSeq_YesNoSelect( WORLDTRADE_WORK *wk);
static int SubSeq_MessageWait( WORLDTRADE_WORK *wk );
static int SubSeq_MessageClearWait( WORLDTRADE_WORK *wk );
static void SubSeq_MessagePrint( WORLDTRADE_WORK *wk, int msgno, int wait, int flag, u16 dat, int winflag );
static void TransPokeIconCharaPal( int pokeno, int form, int tamago, int no, CLACT_WORK_PTR icon, ARCHANDLE* handle, WORLDTRADE_POKEBUF *pbuf );
static void NowBoxPageInfoGet( WORLDTRADE_WORK *wk, int now);
static int RoundWork( int num, int max, int move );
static void CursorControl( WORLDTRADE_WORK *wk );
static int SubSeq_SelectList( WORLDTRADE_WORK *wk );
static int SubSeq_SelectWait( WORLDTRADE_WORK *wk );
static int SubSeq_ExchangeSelectList( WORLDTRADE_WORK *wk );
static int SubSeq_ExchangeSelectWait( WORLDTRADE_WORK *wk );
static int SubSeq_CBallYesNoSelect( WORLDTRADE_WORK *wk );
static int SubSeq_CBallYesNo( WORLDTRADE_WORK *wk );
static int SubSeq_CBallYesNoMessage( WORLDTRADE_WORK *wk );
static int SubSeq_CBallDepositYesNoMessage( WORLDTRADE_WORK *wk );
static int SubSeq_CBallDepositYesNo( WORLDTRADE_WORK *wk );
static int SubSeq_CBallDepositYesNoSelect( WORLDTRADE_WORK *wk );


static int WantPokeCheck(POKEMON_PASO_PARAM *ppp, Dpw_Tr_PokemonSearchData *dtsd);
static void MakeExchangePokemonData( Dpw_Tr_Data *dtd, WORLDTRADE_WORK *wk );
//static void PokemonIconSet( POKEMON_PASO_PARAM *paso, CLACT_WORK_PTR icon, CLACT_WORK_PTR itemact, u16 *no, int pos );
static void PokemonIconSet( POKEMON_PASO_PARAM *paso, CLACT_WORK_PTR icon, CLACT_WORK_PTR itemact, u16 *no, int pos, ARCHANDLE* handle, Dpw_Tr_PokemonDataSimple *dat, WORLDTRADE_POKEBUF *pbuf );
void* CharDataGetbyHandle( ARCHANDLE *handle, u32 dataIdx, NNSG2dCharacterData** charData, u32 heapID );
static int CompareSearchData( Dpw_Tr_PokemonDataSimple *poke,  Dpw_Tr_PokemonSearchData *search );
static void PokeIconPalSet( Dpw_Tr_PokemonDataSimple *box, CLACT_WORK_PTR *icon, Dpw_Tr_PokemonSearchData *want, WORLDTRADE_POKEBUF *pbuf);
static int CheckPocket( POKEPARTY *party, BOX_DATA *box,  int  tray, int pos );
static int PokemonCheck( POKEPARTY *party, BOX_DATA *box,  int  tray, int pos  );
static int ExchangeCheck( WORLDTRADE_WORK *wk );
static int PokeRibbonCheck( POKEMON_PASO_PARAM *ppp );

#define WANT_POKE_NO		( 0 )
#define WANT_POKE_OK		( 1 )
#define WANT_POKE_TAMAGO	( 2 )

enum{
	SUBSEQ_START=0,
	SUBSEQ_MAIN,
	SUBSEQ_END,
	SUBSEQ_MES_WAIT,
	SUBSEQ_MES_CLEAR_WAIT,
	SUBSEQ_YESNO,
	SUBSEQ_YESNO_SELECT,
	SUBSEQ_SELECT_LIST,
	SUBSEQ_SELECT_WAIT,
	SUBSEQ_EXCHANGE_SELECT_LIST,
	SUBSEQ_EXCHANGE_SELECT_WAIT,

	SUBSEQ_CBALL_YESNO_MES,
	SUBSEQ_CBALL_YESNO,
	SUBSEQ_CBALL_YESNO_SELECT,

	SUBSEQ_CBALL_DEPOSIT_YESNO_MES,
	SUBSEQ_CBALL_DEPOSIT_YESNO,
	SUBSEQ_CBALL_DEPOSIT_YESNO_SELECT,
};

static int (*Functable[])( WORLDTRADE_WORK *wk ) = {
	SubSeq_Start,			// SUBSEQ_START=0,
	SubSeq_Main,            // SUBSEQ_MAIN,
	SubSeq_End,             // SUBSEQ_END,
	SubSeq_MessageWait,     // SUBSEQ_MES_WAIT
	SubSeq_MessageClearWait,// SUBSEQ_MES_CLEAR_WAIT
	SubSeq_YesNo,			// SUBSEQ_YESNO
	SubSeq_YesNoSelect,		// SUBSEQ_YESNO_SELECT
	SubSeq_SelectList,		// SUBSEQ_SELECT_LIST
	SubSeq_SelectWait,		// SUBSEQ_SELECT_WAIT
	SubSeq_ExchangeSelectList,	// SUBSEQ_EXCHANGE_SELECT_LIST
	SubSeq_ExchangeSelectWait,	// SUBSEQ_EXCHANGE_SELECT_WAIT

	SubSeq_CBallYesNoMessage,	// SUBSEQ_CBALL_YESNO_MES
	SubSeq_CBallYesNo,			// SUBSEQ_CBALL_YESNO
	SubSeq_CBallYesNoSelect,	// SUBSEQ_CBALL_YESNO_SELECT

	SubSeq_CBallDepositYesNoMessage,	// SUBSEQ_CBALL_YESNO_MES
	SubSeq_CBallDepositYesNo,			// SUBSEQ_CBALL_YESNO
	SubSeq_CBallDepositYesNoSelect,	// SUBSEQ_CBALL_YESNO_SELECT
};

#define BOX_CUROSOR_END_POS			( 30 )
#define BOX_CUROSOR_TRAYNAME_POS	( 31 )


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
int WorldTrade_Box_Init(WORLDTRADE_WORK *wk, int seq)
{
	// ���[�N������
	InitWork( wk );
	
	// BG�ݒ�
	BgInit( wk->bgl );

	// BG�O���t�B�b�N�]��
	BgGraphicSet( wk );

	// BMPWIN�m��
	BmpWinInit( wk );

	SetCellActor(wk);

	// �X�e�[�^�X��ʂ�����ǂ��Ă����Ƃ��͗���ʃt�F�[�h
	if(wk->old_sub_process==WORLDTRADE_STATUS){
		WIPE_SYS_Start( WIPE_PATTERN_WMS, WIPE_TYPE_FADEIN, WIPE_TYPE_FADEIN, WIPE_FADE_BLACK, WORLDTRADE_WIPE_SPPED, 1, HEAPID_WORLDTRADE );
#ifdef GTS_FADE_OSP
		OS_Printf( "******************** worldtrade_box.c [179] MS ********************\n" );
#endif
	}else{
		// ����ȊO�͏��ʂ����t�F�[�h
		WIPE_SYS_Start( WIPE_PATTERN_M, WIPE_TYPE_FADEIN, WIPE_TYPE_FADEIN, WIPE_FADE_BLACK, WORLDTRADE_WIPE_SPPED, 1, HEAPID_WORLDTRADE );
#ifdef GTS_FADE_OSP
		OS_Printf( "******************** worldtrade_box.c [183] M ********************\n" );
#endif
	}
	NowBoxPageInfoGet(wk, wk->BoxTrayNo);

	// �ʐM��Ԃ��m�F���ăA�C�R���̕\����ς���
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
int WorldTrade_Box_Main(WORLDTRADE_WORK *wk, int seq)
{
	int ret;

	// �ʐM��Ԃ��m�F���ăA�C�R���̕\����ς���
    WirelessIconEasy_SetLevel(WorldTrade_WifiLinkLevel());
	
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
int WorldTrade_Box_End(WORLDTRADE_WORK *wk, int seq)
{
	WirelessIconEasyEnd();

	DelCellActor(wk);

	FreeWork( wk );
	
	BmpWinDelete( wk );
	
	BgExit( wk->bgl );
	
	WorldTrade_SubProcessUpdate( wk );
	
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
			2, 0, 0, FALSE
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

	// �㉺��ʂa�f�p���b�g�]��
	ArcUtil_PalSet(    ARC_WORLDTRADE_GRA, NARC_worldtrade_mybox_nclr, PALTYPE_MAIN_BG, 0, 16*3*2,  HEAPID_WORLDTRADE);
	ArcUtil_PalSet(    ARC_WORLDTRADE_GRA, NARC_worldtrade_traderoom_nclr, PALTYPE_SUB_BG,  0, 16*8*2,  HEAPID_WORLDTRADE);
	
	// ��b�t�H���g�p���b�g�]��
	TalkFontPaletteLoad( PALTYPE_MAIN_BG, WORLDTRADE_TALKFONT_PAL*0x20, HEAPID_WORLDTRADE );
	// TalkFontPaletteLoad( PALTYPE_SUB_BG,  WORLDTRADE_TALKFONT_PAL*0x20, HEAPID_WORLDTRADE );

	// ��b�E�C���h�E�O���t�B�b�N�]��
	TalkWinGraphicSet(	bgl, GF_BGL_FRAME0_M, WORLDTRADE_MESFRAME_CHR, 
						WORLDTRADE_MESFRAME_PAL,  CONFIG_GetWindowType(wk->param->config), HEAPID_WORLDTRADE );

	MenuWinGraphicSet(	bgl, GF_BGL_FRAME0_M, WORLDTRADE_MENUFRAME_CHR,
						WORLDTRADE_MENUFRAME_PAL, 0, HEAPID_WORLDTRADE );



	// ���C�����BG1�L�����]��
	ArcUtil_BgCharSet( ARC_WORLDTRADE_GRA, NARC_worldtrade_mybox_lz_ncgr, bgl, GF_BGL_FRAME1_M, 0, 16*5*0x20, 1, HEAPID_WORLDTRADE);

	// ���C�����BG1�X�N���[���]��
	ArcUtil_ScrnSet(   ARC_WORLDTRADE_GRA, NARC_worldtrade_mybox_lz_nscr, bgl, GF_BGL_FRAME1_M, 0, 32*24*2, 1, HEAPID_WORLDTRADE);

	// ���C�����BG2�X�N���[���]��
	ArcUtil_ScrnSet(   ARC_WORLDTRADE_GRA, NARC_worldtrade_title_base_lz_nscr, bgl, GF_BGL_FRAME2_M, 0, 32*24*2, 1, HEAPID_WORLDTRADE);


}
#define BOX_SX		( 25 )
#define BOX_SY		( 60 )
#define BOX_W		( 26 )
#define BOX_H		( 24 )

static const u16 PokemonIconPosTbl[][2]={
	{BOX_SX+BOX_W*0, BOX_SY+BOX_H*0},{BOX_SX+BOX_W*1, BOX_SY+BOX_H*0},{BOX_SX+BOX_W*2, BOX_SY+BOX_H*0},
	{BOX_SX+BOX_W*3, BOX_SY+BOX_H*0},{BOX_SX+BOX_W*4, BOX_SY+BOX_H*0},{BOX_SX+BOX_W*5, BOX_SY+BOX_H*0},

	{BOX_SX+BOX_W*0, BOX_SY+BOX_H*1},{BOX_SX+BOX_W*1, BOX_SY+BOX_H*1},{BOX_SX+BOX_W*2, BOX_SY+BOX_H*1},
	{BOX_SX+BOX_W*3, BOX_SY+BOX_H*1},{BOX_SX+BOX_W*4, BOX_SY+BOX_H*1},{BOX_SX+BOX_W*5, BOX_SY+BOX_H*1},

	{BOX_SX+BOX_W*0, BOX_SY+BOX_H*2},{BOX_SX+BOX_W*1, BOX_SY+BOX_H*2},{BOX_SX+BOX_W*2, BOX_SY+BOX_H*2},
	{BOX_SX+BOX_W*3, BOX_SY+BOX_H*2},{BOX_SX+BOX_W*4, BOX_SY+BOX_H*2},{BOX_SX+BOX_W*5, BOX_SY+BOX_H*2},

	{BOX_SX+BOX_W*0, BOX_SY+BOX_H*3},{BOX_SX+BOX_W*1, BOX_SY+BOX_H*3},{BOX_SX+BOX_W*2, BOX_SY+BOX_H*3},
	{BOX_SX+BOX_W*3, BOX_SY+BOX_H*3},{BOX_SX+BOX_W*4, BOX_SY+BOX_H*3},{BOX_SX+BOX_W*5, BOX_SY+BOX_H*3},

	{BOX_SX+BOX_W*0, BOX_SY+BOX_H*4},{BOX_SX+BOX_W*1, BOX_SY+BOX_H*4},{BOX_SX+BOX_W*2, BOX_SY+BOX_H*4},
	{BOX_SX+BOX_W*3, BOX_SY+BOX_H*4},{BOX_SX+BOX_W*4, BOX_SY+BOX_H*4},{BOX_SX+BOX_W*5, BOX_SY+BOX_H*4},
	{ 224,175 },{98, 32}
};


static const u16 BoxArrowPos[][2]={
	{162, 36 },
	{ 22, 36,}
};
//------------------------------------------------------------------
/**
 * �Z���A�N�^�[�o�^
 *
 * @param   wk			WORLDTRADE_WORK*
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void SetCellActor(WORLDTRADE_WORK *wk)
{
	int i;
	//�o�^���i�[
	CLACT_ADD add;
	WorldTrade_MakeCLACT( &add,  wk, &wk->clActHeader_main, NNS_G2D_VRAM_TYPE_2DMAIN );


	// �|�P�����������w
	add.mat.x = FX32_ONE *   PokemonIconPosTbl[wk->BoxCursorPos][0];
	add.mat.y = FX32_ONE *   PokemonIconPosTbl[wk->BoxCursorPos][1];
	wk->CursorActWork = CLACT_Add(&add);
	CLACT_SetAnmFlag(wk->CursorActWork,1);
	CLACT_AnmChg( wk->CursorActWork, 4 );	
	CLACT_BGPriorityChg( wk->CursorActWork, 1 );
	
	// �|�P�����A�C�R��
	for(i=0;i<BOX_POKE_NUM;i++){
		add.mat.x = FX32_ONE *   PokemonIconPosTbl[i][0];
		add.mat.y = FX32_ONE *   PokemonIconPosTbl[i][1];
		add.pri   = 20;
		wk->PokeIconActWork[i] = CLACT_Add(&add);
		CLACT_AnmChg( wk->PokeIconActWork[i], 6+i );	
		CLACT_BGPriorityChg( wk->PokeIconActWork[i], 1 );
	}

	// �A�C�e���A�C�R��
	for(i=0;i<BOX_POKE_NUM;i++){
		add.mat.x = FX32_ONE *   ( PokemonIconPosTbl[i][0]+4);
		add.mat.y = FX32_ONE *   ( PokemonIconPosTbl[i][1]+6);
		add.pri   = 10;
		wk->ItemIconActWork[i] = CLACT_Add(&add);
		CLACT_AnmChg( wk->ItemIconActWork[i], CELL_ITEMICON_NO );	
		CLACT_BGPriorityChg( wk->ItemIconActWork[i], 1 );

	}

	// �{�[���J�v�Z���A�C�R��
	for(i=0;i<TEMOTI_POKEMAX;i++){
		add.mat.x = FX32_ONE *   ( PokemonIconPosTbl[i][0]+4+8);
		add.mat.y = FX32_ONE *   ( PokemonIconPosTbl[i][1]+6);
		add.pri   = 10;
		wk->CBallActWork[i] = CLACT_Add(&add);
		CLACT_AnmChg( wk->CBallActWork[i], CELL_CBALLICON_NO );	
		CLACT_BGPriorityChg( wk->CBallActWork[i], 1 );

	}

	// �{�b�N�X�؂�ւ��̖��
	for(i=0;i<2;i++){
		add.mat.x = FX32_ONE * BoxArrowPos[i][0];
		add.mat.y = FX32_ONE * BoxArrowPos[i][1];
		wk->BoxArrowActWork[i] = CLACT_Add(&add);
		CLACT_SetAnmFlag( wk->BoxArrowActWork[i], 1 );
		CLACT_AnmChg( wk->BoxArrowActWork[i], CELL_BOXARROW_NO+i );	
		CLACT_BGPriorityChg( wk->BoxArrowActWork[i], 1 );
	}
}


//------------------------------------------------------------------
/**
 * $brief   �\���Z���A�N�^�[�̉��
 *
 * @param   wk		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void DelCellActor( WORLDTRADE_WORK *wk )
{
	int i;

	// �{�b�N�X���̖��Q��
	for(i=0;i<2;i++){
		CLACT_Delete(wk->BoxArrowActWork[i]);
	}

	// �J�[�\���폜
	CLACT_Delete(wk->CursorActWork);

	// �|�P�����A�C�R���폜
	for(i=0;i<BOX_POKE_NUM;i++){
		CLACT_Delete(wk->PokeIconActWork[i]);
		CLACT_Delete(wk->ItemIconActWork[i]);
	}
	// �J�X�^���{�[���A�C�R���폜
	for(i=0;i<TEMOTI_POKEMAX;i++){
		CLACT_Delete(wk->CBallActWork[i]);
	}

}

#define SELECT_MENU_X	(  21 )
#define SELECT_MENU_Y 	(  13 )
#define SELECT_MENU_SX	( 5*2 )
#define SELECT_MENU_SY	(   6 )


#define BOX_TRAY_NAME_X		(  5 )
#define BOX_TRAY_NAME_Y		(  3 )
#define BOX_TRAY_NAME_SX	( 13 )
#define BOX_TRAY_NAME_SY	(  3 )

#define END_TEXT_X			( 25 )
#define END_TEXT_Y			( 21 )
#define END_TEXT_SX			(  6 )
#define END_TEXT_SY			(  2 )


#define TITLE_MESSAGE_OFFSET   ( WORLDTRADE_MENUFRAME_CHR + MENU_WIN_CGX_SIZ )
#define BOX_TRAY_NAME_OFFSET   ( TITLE_MESSAGE_OFFSET     + TITLE_TEXT_SX*TITLE_TEXT_SY )
#define LINE_MESSAGE_OFFSET    ( BOX_TRAY_NAME_OFFSET     + BOX_TRAY_NAME_SX*BOX_TRAY_NAME_SX )
#define TALK_MESSAGE_OFFSET	   ( LINE_MESSAGE_OFFSET      + LINE_TEXT_SX*LINE_TEXT_SY )
#define END_MESSAGE_OFFSET	   ( TALK_MESSAGE_OFFSET      + TALK_WIN_X*TALK_WIN_Y )
#define SELECT_MENU_OFFSET 	   ( END_MESSAGE_OFFSET       + END_TEXT_SX*END_TEXT_SY )
#define YESNO_OFFSET 		   ( SELECT_MENU_OFFSET       + SELECT_MENU_SX*SELECT_MENU_SY )

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

	// BG0��BMPWIN�^�C�g���E�C���h�E�m�ہE�`��
	
	GF_BGL_BmpWinAdd(wk->bgl, &wk->TitleWin, GF_BGL_FRAME0_M,
	TITLE_TEXT_X, TITLE_TEXT_Y, TITLE_TEXT_SX, TITLE_TEXT_SY, WORLDTRADE_TALKFONT_PAL,  TITLE_MESSAGE_OFFSET );

	GF_BGL_BmpWinDataFill( &wk->TitleWin, 0x0000 );
	
	// ��������|�P�����������ł�������
	WorldTrade_SysPrint( &wk->TitleWin, wk->TitleString, 0, 1, 0, GF_PRINTCOLOR_MAKE(15,14,0) );


	// �{�b�N�X�g���C��BMPWIN�m��
	
	GF_BGL_BmpWinAdd(wk->bgl, &wk->SubWin, GF_BGL_FRAME0_M,
	BOX_TRAY_NAME_X, BOX_TRAY_NAME_Y, BOX_TRAY_NAME_SX, BOX_TRAY_NAME_SY, WORLDTRADE_TALKFONT_PAL,  
	BOX_TRAY_NAME_OFFSET  );
	GF_BGL_BmpWinDataFill( &wk->SubWin, 0x0000 );
	GF_BGL_BmpWinOn(&wk->SubWin);
	
	// ��s�E�C���h�E
	GF_BGL_BmpWinAdd(wk->bgl, &wk->MsgWin, GF_BGL_FRAME0_M,
		LINE_TEXT_X, LINE_TEXT_Y, LINE_TEXT_SX, LINE_TEXT_SY, 
		WORLDTRADE_TALKFONT_PAL,  LINE_MESSAGE_OFFSET );

	GF_BGL_BmpWinDataFill( &wk->MsgWin, 0x0000 );

	// 2�s�E�C���h�E
	GF_BGL_BmpWinAdd(wk->bgl, &wk->TalkWin, GF_BGL_FRAME0_M,
		TALK_WIN_X, TALK_WIN_Y, TALK_WIN_SX, TALK_WIN_SY, 
		WORLDTRADE_TALKFONT_PAL,  TALK_MESSAGE_OFFSET );

	GF_BGL_BmpWinDataFill( &wk->TalkWin, 0x0000 );

	// ��߂�
	GF_BGL_BmpWinAdd(wk->bgl, &wk->MenuWin[1], GF_BGL_FRAME1_M,
		END_TEXT_X, END_TEXT_Y, END_TEXT_SX, END_TEXT_SY, 
		0,  END_MESSAGE_OFFSET );

	GF_BGL_BmpWinDataFill( &wk->MenuWin[1], 0x0606 );
	// �u���ǂ�v�`��
	WorldTrade_SysPrint( &wk->MenuWin[1], wk->EndString, 0, 1, 1, GF_PRINTCOLOR_MAKE(1,3,6) );

	// �I�����j���[�̈�
	GF_BGL_BmpWinAdd(wk->bgl, &wk->MenuWin[0], GF_BGL_FRAME0_M,
		SELECT_MENU_X, SELECT_MENU_Y, SELECT_MENU_SX, SELECT_MENU_SY, 
		WORLDTRADE_TALKFONT_PAL,  SELECT_MENU_OFFSET );	


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
	GF_BGL_BmpWinDel( &wk->TalkWin );
	GF_BGL_BmpWinDel( &wk->MenuWin[1] );
	GF_BGL_BmpWinDel( &wk->MenuWin[0] );
	GF_BGL_BmpWinDel( &wk->MsgWin );
	GF_BGL_BmpWinDel( &wk->SubWin );
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

	// �{�b�N�X�g���C��������o�b�t�@
	wk->BoxTrayNameString = STRBUF_Create( BOX_TRAY_NAME_BUF_NUM, HEAPID_WORLDTRADE );

	// ������o�b�t�@�쐬
	wk->TalkString  = STRBUF_Create( TALK_MESSAGE_BUF_NUM, HEAPID_WORLDTRADE );

	// �u��������|�P�����������ł��������v�u�����̃|�P�����������ł��������v
	if(wk->sub_process_mode==MODE_DEPOSIT_SELECT){
		wk->TitleString = MSGMAN_AllocString( wk->MsgManager, msg_gtc_01_022 );
	}else if(wk->sub_process_mode==MODE_EXCHANGE_SELECT){
		wk->TitleString = MSGMAN_AllocString( wk->MsgManager, msg_gtc_01_018 );
	}

	// ���ǂ�
	wk->EndString   = MSGMAN_AllocString( wk->MsgManager, msg_gtc_05_014 );

	if(wk->BoxCursorPos==BOX_CUROSOR_END_POS){
		wk->BoxCursorPos = 0;
	}
	
	// �{�b�N�X�p���[�N
	wk->boxWork = sys_AllocMemory(HEAPID_WORLDTRADE, sizeof(BOX_RESEARCH));

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
	sys_FreeMemoryEz(wk->boxWork);

	STRBUF_Delete( wk->BoxTrayNameString );
	STRBUF_Delete( wk->TalkString ); 
	STRBUF_Delete( wk->EndString ); 
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
 * $brief   �T�u�v���Z�X�V�[�P���X�X�^�[�g����
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
//		SubSeq_MessagePrint( wk, msg_gtc_01_018, 1, 0, 0x0f0f );
//		WorldTrade_SetNextSeq( wk, SUBSEQ_MES_WAIT, SUBSEQ_MAIN );
		wk->subprocess_seq = SUBSEQ_MAIN;
	}

	return SEQ_MAIN;
}
/* 
       31

 0  1  2  3  4  5
 6  7  8  9 10 11
12 13 14 15 16 17
18 19 20 21 22 23
24 25 26 27 28 29 30

 */

static const u8 box_pos_table[][4]={
	// �㉺���E
	{31, 6, 5, 1,},{31, 7, 0, 2,},{31, 8, 1, 3,},{31, 9, 2, 4,},{31,10, 3, 5,},{31,11, 4, 0,},
	{ 0,12,11, 7,},{ 1,13, 6, 8,},{ 2,14, 7, 9,},{ 3,15, 8,10,},{ 4,16, 9,11,},{ 5,17,10, 6,},
	{ 6,18,17,13,},{ 7,19,12,14,},{ 8,20,13,15,},{ 9,21,14,16,},{10,22,15,17,},{11,23,16,12,},
	{12,24,23,19,},{13,25,18,20,},{14,26,19,21,},{15,27,20,22,},{16,28,21,23,},{17,29,22,18,},
	{18,31,30,25,},{19,31,24,26,},{20,31,25,27,},{21,31,26,28,},{22,31,27,29,},{23,31,28,30,},{30,30,29,24},
	{ 26,2,99,101, },

};

static const s8 movetbl[][2]={
	{0,0},{0,-1},{0,1},{1,0},{-1,0},
};

//------------------------------------------------------------------
/**
 * $brief   �T�u�v���Z�X�V�[�P���X���C��
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int SubSeq_Main( WORLDTRADE_WORK *wk)
{
	CursorControl(wk);

	// �������鎞
	if(wk->sub_process_mode==MODE_DEPOSIT_SELECT){
		if(sys.trg & PAD_BUTTON_B){
			// �^�C�g�����j���[�ɂ��ǂ�
			WorldTrade_SubProcessChange( wk, WORLDTRADE_TITLE, 0 );
			wk->subprocess_seq = SUBSEQ_END;

		}else if(sys.trg & PAD_BUTTON_DECIDE){
			if(wk->BoxCursorPos == BOX_CUROSOR_END_POS){
			// �^�C�g�����j���[�ɂ��ǂ�
				WorldTrade_SubProcessChange( wk, WORLDTRADE_TITLE, 0 );
				wk->subprocess_seq = SUBSEQ_END;
				Snd_SePlay(WORLDTRADE_DECIDE_SE);
			}else{
				if(wk->BoxCursorPos!=BOX_CUROSOR_TRAYNAME_POS){
					Snd_SePlay(WORLDTRADE_DECIDE_SE);
					// ���������������܂����H
					switch(PokemonCheck( wk->param->myparty, wk->param->mybox, wk->BoxTrayNo, wk->BoxCursorPos )){
					// ������
					case WANT_POKE_OK:
						if(CheckPocket( wk->param->myparty, wk->param->mybox, wk->BoxTrayNo, wk->BoxCursorPos )){
							WORDSET_RegisterPokeNickName( wk->WordSet, 0, 
									WorldTrade_GetPokePtr(wk->param->myparty, wk->param->mybox, wk->BoxTrayNo, wk->BoxCursorPos) );
							SubSeq_MessagePrint( wk, msg_gtc_01_023, 1, 0, 0x0f0f, 0 );
							WorldTrade_SetNextSeq( wk, SUBSEQ_MES_WAIT,  SUBSEQ_SELECT_LIST);
							OS_Printf("deposit_ppp0 = %08x\n",WorldTrade_GetPokePtr(wk->param->myparty, wk->param->mybox, wk->BoxTrayNo, wk->BoxCursorPos));
						}else{
							// �Ă����̍Ō��1�C�������ꍇ�͂����Ȃ�
							SubSeq_MessagePrint( wk, msg_gtc_01_027, 1, 0, 0x0f0f, 1 );
							WorldTrade_SetNextSeq( wk, SUBSEQ_MES_CLEAR_WAIT,  SUBSEQ_MAIN);
						}
						break;
					// �^�}�S�͂����Ȃ�
					case WANT_POKE_TAMAGO:
						SubSeq_MessagePrint( wk, msg_gtc_01_028, 1, 0, 0x0f0f, 1 );
						WorldTrade_SetNextSeq( wk, SUBSEQ_MES_CLEAR_WAIT,  SUBSEQ_MAIN);
						break;
					// ���ꃊ�{�������Ă���̂Ń_��
					}
				}
			}
		}
		
	// ��������Ƃ�
	}else if(wk->sub_process_mode==MODE_EXCHANGE_SELECT){
		if(sys.trg & PAD_BUTTON_CANCEL){
			// �������ʃ|�P�����̉�ʂɂ��ǂ�
			WorldTrade_SubProcessChange( wk, WORLDTRADE_PARTNER, 0 );
			wk->subprocess_seq  = SUBSEQ_END;
			Snd_SePlay(WORLDTRADE_DECIDE_SE);
		}else if(sys.trg & PAD_BUTTON_DECIDE){
			if(wk->BoxCursorPos == BOX_CUROSOR_END_POS){
				// �T�[�o�[�`�F�b�N�̌�^�C�g�����j���[��
				WorldTrade_SubProcessChange( wk, WORLDTRADE_PARTNER, 0 );
				wk->subprocess_seq  = SUBSEQ_END;
				Snd_SePlay(WORLDTRADE_DECIDE_SE);
			}else{
				if(wk->BoxCursorPos!=BOX_CUROSOR_TRAYNAME_POS){
					// �������������ɂ����܂����H
					switch(PokemonCheck( wk->param->myparty, wk->param->mybox, wk->BoxTrayNo, wk->BoxCursorPos )){
					case WANT_POKE_OK:
						{
							POKEMON_PASO_PARAM *ppp = WorldTrade_GetPokePtr(wk->param->myparty, wk->param->mybox, wk->BoxTrayNo, wk->BoxCursorPos);

							// ���O���擾����WordSet�ɓo�^
							if(WantPokeCheck( ppp, &wk->DownloadPokemonData[wk->TouchTrainerPos].wantSimple)){
								if(CheckPocket( wk->param->myparty, wk->param->mybox, wk->BoxTrayNo, wk->BoxCursorPos )){
									WORDSET_RegisterPokeNickName( wk->WordSet, 0, ppp);
									SubSeq_MessagePrint( wk, msg_gtc_01_019, 1, 0, 0x0f0f, 0 );
									WorldTrade_SetNextSeq( wk, SUBSEQ_MES_WAIT,  SUBSEQ_EXCHANGE_SELECT_LIST);
									OS_Printf("deposit_ppp0 = %08x\n",WorldTrade_GetPokePtr(wk->param->myparty, wk->param->mybox, wk->BoxTrayNo, wk->BoxCursorPos));
									Snd_SePlay(WORLDTRADE_DECIDE_SE);
								}else{
									// �Ă����̍Ō��1�C�������ꍇ�͂����Ȃ�
									SubSeq_MessagePrint( wk, msg_gtc_01_027, 1, 0, 0x0f0f, 1 );
									WorldTrade_SetNextSeq( wk, SUBSEQ_MES_CLEAR_WAIT,  SUBSEQ_MAIN);
								}
							}else{
								Snd_SePlay(SE_CANCEL);
							}
						}
						break;
					case WANT_POKE_TAMAGO: case WANT_POKE_NO:
						Snd_SePlay(SE_CANCEL);
						break;
					}
				}
			}
		}
	}


	return SEQ_MAIN;
}


//------------------------------------------------------------------
/**
 * $brief   �J�[�\������
 *
 * @param   wk		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void CursorControl( WORLDTRADE_WORK *wk )
{
	int move=0, arrow=0, tmp=0;

	// �J�[�\������
	if(sys.trg & PAD_KEY_UP){
		arrow = 1;
	}else if(sys.trg & PAD_KEY_DOWN){
		arrow = 2;
	}else if(sys.trg & PAD_KEY_LEFT){
		arrow = 3;
	}else if(sys.trg & PAD_KEY_RIGHT){
		arrow = 4;
	}

	// �㉺���E���������H
	if(arrow!=0){
		tmp = box_pos_table[wk->BoxCursorPos][arrow-1];
		if(tmp!=wk->BoxCursorPos){
			if(tmp==99||tmp==101){
				wk->BoxTrayNo = RoundWork( wk->BoxTrayNo, 19, tmp-100);
				NowBoxPageInfoGet( wk, wk->BoxTrayNo );
				Snd_SePlay(WORLDTRADE_DECIDE_SE);
			}else{
				move = 1;
				wk->BoxCursorPos = tmp;
			}
		}
	}
	
	// �ړ������H
	if(move){
		Snd_SePlay(WORLDTRADE_MOVE_SE);
		WorldTrade_ActPos(wk->CursorActWork, 
			PokemonIconPosTbl[wk->BoxCursorPos][0],
			PokemonIconPosTbl[wk->BoxCursorPos][1]);
	}

	// �J�[�\���v���C�I���e�B����
	if(wk->BoxCursorPos==31 || (wk->BoxCursorPos>=0 && wk->BoxCursorPos<=5)){
		// �{�b�N�X�g���C���̏�ɂ���Ƃ��ƃ{�b�N�X�P��ڂɂ���Ƃ��͍ŏ�ʂ�
		CLACT_BGPriorityChg( wk->CursorActWork, 0 );
	}else{
		// ����ȊO�͂ЂƂ���
		CLACT_BGPriorityChg( wk->CursorActWork, 1 );
	}

}


//------------------------------------------------------------------
/**
 * $brief   num��move�𑫂�,0�ȉ��Ȃ�max-1�ɁAmax�Ȃ�0�ɂ��ĕԂ�
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
 * $brief   �I�����X�g�쐬
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int SubSeq_SelectList( WORLDTRADE_WORK *wk )
{
	BMPMENU_HEADER temp;

	temp.font  = FONT_SYSTEM;
	temp.x_max = 1;
	temp.y_max = 3;
	temp.line_spc = 0;
	temp.c_disp_f = 0;
	temp.loop_f   = 0;


	wk->BmpMenuList = BMP_MENULIST_Create( 3, HEAPID_WORLDTRADE );
	// �悤�����݂�
	BMP_MENULIST_AddArchiveString( wk->BmpMenuList, wk->MsgManager, msg_gtc_05_005, 1 );
	// ��������
	BMP_MENULIST_AddArchiveString( wk->BmpMenuList, wk->MsgManager, msg_gtc_05_006, 2 );
	// ��߂�
	BMP_MENULIST_AddArchiveString( wk->BmpMenuList, wk->MsgManager, msg_gtc_05_007, 3 );

	temp.menu = wk->BmpMenuList;
	temp.win  = &wk->MenuWin[0];

	// �g�`��
	BmpMenuWinWrite( &wk->MenuWin[0], WINDOW_TRANS_ON, WORLDTRADE_MENUFRAME_CHR, WORLDTRADE_MENUFRAME_PAL );

	// BMP���j���[�J�n
	wk->BmpMenuWork = BmpMenuAddEx( &temp, 9, 0, 0, HEAPID_WORLDTRADE, PAD_BUTTON_B );


	wk->subprocess_seq = SUBSEQ_SELECT_WAIT;

	return SEQ_MAIN;
	
}


//------------------------------------------------------------------
/**
 * $brief   �u�悤�����݂�v�u��������v�u��߂�v�I��҂�
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int SubSeq_SelectWait( WORLDTRADE_WORK *wk )
{
	switch(BmpMenuMain( wk->BmpMenuWork )){
	// �u�悤�����݂�v
	case 1:
		BmpMenuExit( wk->BmpMenuWork, NULL );
		BMP_MENULIST_Delete( wk->BmpMenuList );
		BmpMenuWinClear( &wk->MenuWin[0], WINDOW_TRANS_ON );
		wk->subprocess_seq  = SUBSEQ_END;
		WorldTrade_SubProcessChange( wk, WORLDTRADE_STATUS, MODE_DEPOSIT_SELECT );
		break;

	// �u��������v
	case 2:
		BmpMenuExit( wk->BmpMenuWork, NULL );
		BMP_MENULIST_Delete( wk->BmpMenuList );
		BmpMenuWinClear( &wk->MenuWin[0], WINDOW_TRANS_ON );

		if( PokeRibbonCheck( WorldTrade_GetPokePtr( wk->param->myparty, wk->param->mybox, wk->BoxTrayNo, wk->BoxCursorPos)) ){
			SubSeq_MessagePrint( wk, msg_gtc_01_038, 1, 0, 0x0f0f, 1 );
			WorldTrade_SetNextSeq( wk, SUBSEQ_MES_CLEAR_WAIT,  SUBSEQ_MAIN);
		}else{
			int flag = 0;
			// �Ă����̂Ƃ��̓J�X�^���{�[���`�F�b�N
			if(WorldTrade_GetPPorPPP( wk->BoxTrayNo )){
				POKEMON_PARAM *pp;
				pp = PokeParty_GetMemberPointer(wk->param->myparty, wk->BoxCursorPos);
				if(PokeParaGet( pp, ID_PARA_cb_id, NULL )){
					flag = 1;
					wk->subprocess_seq = SUBSEQ_CBALL_DEPOSIT_YESNO_MES;
				}
				OS_Printf("�Ă����w�� �J�X�^��=%d\n", PokeParaGet( pp, ID_PARA_cb_id, NULL ));
			}

			// ���Ȃ���΃|�P�����a����
			if(flag==0){
				wk->deposit_ppp     = WorldTrade_GetPokePtr( wk->param->myparty, wk->param->mybox, wk->BoxTrayNo, wk->BoxCursorPos );
				wk->subprocess_seq  = SUBSEQ_END;
				 WorldTrade_SubProcessChange( wk, WORLDTRADE_DEPOSIT, 0 );
				OS_Printf("deposit_ppp1 = %08x\n",WorldTrade_GetPokePtr(wk->param->myparty, wk->param->mybox, wk->BoxTrayNo, wk->BoxCursorPos));
			}
		}
		break;
		
	// �u��߂�v
	case 3:case BMPMENU_CANCEL:
		BmpMenuExit( wk->BmpMenuWork, NULL );
		BMP_MENULIST_Delete( wk->BmpMenuList );
		BmpMenuWinClear( &wk->MenuWin[0], WINDOW_TRANS_ON );
		BmpTalkWinClear( &wk->MsgWin, WINDOW_TRANS_ON );
		wk->subprocess_seq  = SUBSEQ_MAIN;

		break;
	}
	
	return SEQ_MAIN;
}

//------------------------------------------------------------------
/**
 * $brief   �I�����X�g�쐬
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int SubSeq_ExchangeSelectList( WORLDTRADE_WORK *wk )
{
	BMPMENU_HEADER temp;

	temp.font  = FONT_SYSTEM;
	temp.x_max = 1;
	temp.y_max = 3;
	temp.line_spc = 0;
	temp.c_disp_f = 0;
	temp.loop_f   = 0;


	wk->BmpMenuList = BMP_MENULIST_Create( 3, HEAPID_WORLDTRADE );
	// �悤�����݂�
	BMP_MENULIST_AddArchiveString( wk->BmpMenuList, wk->MsgManager, msg_gtc_04_018, 1 );
	// �������񂷂�
	BMP_MENULIST_AddArchiveString( wk->BmpMenuList, wk->MsgManager, msg_gtc_04_019, 2 );
	// ��߂�
	BMP_MENULIST_AddArchiveString( wk->BmpMenuList, wk->MsgManager, msg_gtc_04_020, 3 );

	temp.menu = wk->BmpMenuList;
	temp.win  = &wk->MenuWin[0];

	// �g�`��
	BmpMenuWinWrite( &wk->MenuWin[0], WINDOW_TRANS_ON, WORLDTRADE_MENUFRAME_CHR, WORLDTRADE_MENUFRAME_PAL );

	// BMP���j���[�J�n
	wk->BmpMenuWork = BmpMenuAddEx( &temp, 9, 0, 0, HEAPID_WORLDTRADE, PAD_BUTTON_B );


	wk->subprocess_seq = SUBSEQ_EXCHANGE_SELECT_WAIT;

	return SEQ_MAIN;
	
}


//------------------------------------------------------------------
/**
 * $brief   �u�悤�����݂�v�u�������񂷂�v�u��߂�v�I��҂�
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int SubSeq_ExchangeSelectWait( WORLDTRADE_WORK *wk )
{
	switch(BmpMenuMain( wk->BmpMenuWork )){
	// �u�悤�����݂�v
	case 1:
		BmpMenuExit( wk->BmpMenuWork, NULL );
		BMP_MENULIST_Delete( wk->BmpMenuList );
		BmpMenuWinClear( &wk->MenuWin[0], WINDOW_TRANS_ON );
		wk->subprocess_seq  = SUBSEQ_END;
		 WorldTrade_SubProcessChange( wk, WORLDTRADE_STATUS, MODE_EXCHANGE_SELECT );
		break;

	// �u�������񂷂�v
	case 2:
		BmpMenuExit( wk->BmpMenuWork, NULL );
		BMP_MENULIST_Delete( wk->BmpMenuList );
		BmpMenuWinClear( &wk->MenuWin[0], WINDOW_TRANS_ON );

		if( PokeRibbonCheck( WorldTrade_GetPokePtr( wk->param->myparty, wk->param->mybox, wk->BoxTrayNo, wk->BoxCursorPos))){
			SubSeq_MessagePrint( wk, msg_gtc_01_038, 1, 0, 0x0f0f, 1 );
			WorldTrade_SetNextSeq( wk, SUBSEQ_MES_CLEAR_WAIT,  SUBSEQ_MAIN);
		}else{
			int flag = 0;
			// �Ă����̂Ƃ��̓J�X�^���{�[���`�F�b�N
			if(WorldTrade_GetPPorPPP( wk->BoxTrayNo )){
				POKEMON_PARAM *pp;
				pp = PokeParty_GetMemberPointer(wk->param->myparty, wk->BoxCursorPos);
				if(PokeParaGet( pp, ID_PARA_cb_id, NULL )){
					flag = 1;
					wk->subprocess_seq = SUBSEQ_CBALL_YESNO_MES;
				}
				OS_Printf("�Ă����w�� �J�X�^��=%d\n", PokeParaGet( pp, ID_PARA_cb_id, NULL ));
			}
			
			// ���Ȃ���Ό�����
			if(flag==0){
				ExchangeCheck(wk);
			}
		}
		break;
		
	// �u��߂�v
	case 3:case BMPMENU_CANCEL:
		BmpMenuExit( wk->BmpMenuWork, NULL );
		BMP_MENULIST_Delete( wk->BmpMenuList );
		BmpMenuWinClear( &wk->MenuWin[0], WINDOW_TRANS_ON );
		BmpTalkWinClear( &wk->MsgWin, WINDOW_TRANS_ON );
		wk->subprocess_seq  = SUBSEQ_MAIN;

		break;
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
static int SubSeq_End( WORLDTRADE_WORK *wk )
{
	// �ڑ���ʂ�������A�㉺��ʂŃt�F�[�h
	if(wk->sub_nextprocess==WORLDTRADE_ENTER || wk->sub_nextprocess==WORLDTRADE_STATUS){
		WIPE_SYS_Start( WIPE_PATTERN_WMS, WIPE_TYPE_FADEOUT, WIPE_TYPE_FADEOUT, WIPE_FADE_BLACK, WORLDTRADE_WIPE_SPPED, 1, HEAPID_WORLDTRADE );
#ifdef GTS_FADE_OSP
		OS_Printf( "******************** worldtrade_box.c [1164] MS ********************\n" );
#endif
		wk->sub_out_flg = 1;
	}else{
		// �����̉�ʂɂ����ꍇ�͏��ʂ����t�F�[�h
		WIPE_SYS_Start( WIPE_PATTERN_M, WIPE_TYPE_FADEOUT, WIPE_TYPE_FADEOUT, WIPE_FADE_BLACK, WORLDTRADE_WIPE_SPPED, 1, HEAPID_WORLDTRADE );
#ifdef GTS_FADE_OSP
		OS_Printf( "******************** worldtrade_box.c [1169] M ********************\n" );
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
static int SubSeq_YesNo( WORLDTRADE_WORK *wk)
{
	wk->YesNoMenuWork = WorldTrade_BmpWinYesNoMake(wk->bgl, WORLDTRADE_YESNO_PY1, YESNO_OFFSET );
	wk->subprocess_seq = SUBSEQ_YESNO_SELECT;

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
static int SubSeq_YesNoSelect( WORLDTRADE_WORK *wk)
{
	int ret = BmpYesNoSelectMain( wk->YesNoMenuWork, HEAPID_WORLDTRADE );

	if(ret!=BMPMENU_NULL){
		if(ret==BMPMENU_CANCEL){
			// �������������g���C
			wk->subprocess_seq = SUBSEQ_START;
		}else{
			// �^�C�g�����j���[���I��
			wk->subprocess_seq  = SUBSEQ_END;
			 WorldTrade_SubProcessChange( wk, WORLDTRADE_ENTER, 0 );
		}
	}

	return SEQ_MAIN;
	
}



//------------------------------------------------------------------
/**
 * @brief   �u�{�[���J�v�Z�����O��܂����A��낵���ł����H�v
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int SubSeq_CBallYesNoMessage( WORLDTRADE_WORK *wk )
{
	SubSeq_MessagePrint( wk, msg_gtc_01_026, 1, 0, 0x0f0f, 1 );
	WorldTrade_SetNextSeq( wk, SUBSEQ_MES_WAIT,  SUBSEQ_CBALL_YESNO );

	return SEQ_MAIN;
	
}

//------------------------------------------------------------------
/**
 * $brief   �{�[���J�v�Z�����O��܂����E�E�E�͂��E������
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int SubSeq_CBallYesNo( WORLDTRADE_WORK *wk )
{
	wk->YesNoMenuWork = WorldTrade_BmpWinYesNoMake(wk->bgl, WORLDTRADE_YESNO_PY2, YESNO_OFFSET );
	wk->subprocess_seq = SUBSEQ_CBALL_YESNO_SELECT;

	return SEQ_MAIN;
	
}


//------------------------------------------------------------------
/**
 * $brief   �{�[���J�v�Z�����O��܂����E�E�E�E�E�͂��E�������I��
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int SubSeq_CBallYesNoSelect( WORLDTRADE_WORK *wk )
{
	int ret = BmpYesNoSelectMain( wk->YesNoMenuWork, HEAPID_WORLDTRADE );

	if(ret!=BMPMENU_NULL){
		if(ret==BMPMENU_CANCEL){
			// ������������
			BmpTalkWinClear( &wk->TalkWin, WINDOW_TRANS_ON );
			wk->subprocess_seq  = SUBSEQ_MAIN;
		}else{
			// ������
			ExchangeCheck(wk);
		}
	}

	return SEQ_MAIN;
	
}


//------------------------------------------------------------------
/**
 * @brief   �������邽�߂̃`�F�b�N
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int ExchangeCheck( WORLDTRADE_WORK *wk )
{
	POKEMON_PARAM *pp;
	pp = (POKEMON_PARAM*)wk->DownloadPokemonData[wk->TouchTrainerPos].postData.data;

	// �����Ẵ|�P�����Ƀ��[�������Ă��āA�����̂Ă������U�Ђ��������Ƃ��͌����ł��Ȃ��B
	if(WorldTrade_PokemonMailCheck(pp) && wk->BoxTrayNo!=18){
		if(PokeParty_GetPokeCount(wk->param->myparty)==6){
			SubSeq_MessagePrint( wk, msg_gtc_01_029, 1, 0, 0x0f0f, 1 );
			WorldTrade_SetNextSeq( wk, SUBSEQ_MES_CLEAR_WAIT,  SUBSEQ_MAIN );
			return 0;
		}
	}

	wk->deposit_ppp     = WorldTrade_GetPokePtr( wk->param->myparty, wk->param->mybox, wk->BoxTrayNo, wk->BoxCursorPos );
	wk->subprocess_seq  = SUBSEQ_END;
	wk->sub_out_flg = 1;
	WorldTrade_SubProcessChange( wk, WORLDTRADE_UPLOAD, MODE_EXCHANGE );
	OS_Printf("deposit_ppp1 = %08x\n",WorldTrade_GetPokePtr(wk->param->myparty, wk->param->mybox, wk->BoxTrayNo, wk->BoxCursorPos));

	MakeExchangePokemonData( &wk->UploadPokemonData, wk );

	// �����q�b�g�����N���A���Ă����Ȃ��ƁA�f���I����ɂn�a�i���\������Ă��܂�
	wk->SearchResult = 0;

	return 1;
}

//------------------------------------------------------------------
/**
 * @brief   �u�{�[���J�v�Z�����O��܂����A��낵���ł����H�v
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int SubSeq_CBallDepositYesNoMessage( WORLDTRADE_WORK *wk )
{
	SubSeq_MessagePrint( wk, msg_gtc_01_026, 1, 0, 0x0f0f, 1 );
	WorldTrade_SetNextSeq( wk, SUBSEQ_MES_WAIT,  SUBSEQ_CBALL_DEPOSIT_YESNO );

	return SEQ_MAIN;
	
}

//------------------------------------------------------------------
/**
 * $brief   �{�[���J�v�Z�����O��܂����E�E�E�͂��E������
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int SubSeq_CBallDepositYesNo( WORLDTRADE_WORK *wk )
{
	wk->YesNoMenuWork = WorldTrade_BmpWinYesNoMake(wk->bgl, WORLDTRADE_YESNO_PY2, YESNO_OFFSET );
	wk->subprocess_seq = SUBSEQ_CBALL_DEPOSIT_YESNO_SELECT;

	return SEQ_MAIN;
	
}


//------------------------------------------------------------------
/**
 * $brief   �{�[���J�v�Z�����O��܂����E�E�E�E�E�͂��E�������I��
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int SubSeq_CBallDepositYesNoSelect( WORLDTRADE_WORK *wk )
{
	int ret = BmpYesNoSelectMain( wk->YesNoMenuWork, HEAPID_WORLDTRADE );

	if(ret!=BMPMENU_NULL){
		if(ret==BMPMENU_CANCEL){
			// ������������
			BmpTalkWinClear( &wk->TalkWin, WINDOW_TRANS_ON );
			wk->subprocess_seq  = SUBSEQ_MAIN;
		}else{
			// ������
			wk->deposit_ppp     = WorldTrade_GetPokePtr( wk->param->myparty, wk->param->mybox, wk->BoxTrayNo, wk->BoxCursorPos );
			wk->subprocess_seq  = SUBSEQ_END;
			 WorldTrade_SubProcessChange( wk, WORLDTRADE_DEPOSIT, 0 );
			OS_Printf("deposit_ppp1 = %08x\n",WorldTrade_GetPokePtr(wk->param->myparty, wk->param->mybox, wk->BoxTrayNo, wk->BoxCursorPos));
		}
	}

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
static int SubSeq_MessageWait( WORLDTRADE_WORK *wk )
{
	if( GF_MSG_PrintEndCheck( wk->MsgIndex )==0){
		wk->subprocess_seq = wk->subprocess_nextseq;
	}
	return SEQ_MAIN;

}

//------------------------------------------------------------------
/**
 * $brief   ��b�I����҂��ăE�C���h�E���������A���̃V�[�P���X��
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int SubSeq_MessageClearWait( WORLDTRADE_WORK *wk )
{
	if( GF_MSG_PrintEndCheck( wk->MsgIndex )==0){
		BmpTalkWinClear( &wk->TalkWin, WINDOW_TRANS_ON );
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
static void SubSeq_MessagePrint( WORLDTRADE_WORK *wk, int msgno, int wait, int flag, u16 dat, int winflag )
{
	GF_BGL_BMPWIN *win;
	
	// ������擾
	STRBUF *tempbuf;
	
	// ������擾
	tempbuf = MSGMAN_AllocString(  wk->MsgManager, msgno );

	// WORDSET�W�J
	WORDSET_ExpandStr( wk->WordSet, wk->TalkString, tempbuf );
	

	if(winflag==0){
		win = &wk->MsgWin;
	}else{
		win = &wk->TalkWin;
	}
	// ��b�E�C���h�E�g�`��
	GF_BGL_BmpWinDataFill( win,  0x0f0f );
	BmpTalkWinWrite( win, WINDOW_TRANS_ON, WORLDTRADE_MESFRAME_CHR, WORLDTRADE_MESFRAME_PAL );

	// ������`��J�n
	wk->MsgIndex = GF_STR_PrintSimple( win, FONT_TALK, wk->TalkString, 0, 0, wait, NULL);

	STRBUF_Delete(tempbuf);
}


//==============================================================================
/**
 * @brief   �|�P�����A�C�R���̓ǂݍ��݂𑬂����邽�߂Ƀn���h�����J�����n���h������ǂݍ���
 *
 * @param   handle		
 * @param   dataIdx		
 * @param   charData		
 * @param   heapID		
 *
 * @retval  void*		
 */
//==============================================================================
void* CharDataGetbyHandle( ARCHANDLE *handle, u32 dataIdx, NNSG2dCharacterData** charData, u32 heapID )
{
	void* arcData = ArchiveDataLoadAllocByHandle( handle, dataIdx, heapID );

	if( arcData != NULL )
	{
		if( NNS_G2dGetUnpackedBGCharacterData( arcData, charData ) == FALSE)
		{
			// ���s������NULL
			sys_FreeMemoryEz( arcData );
			return NULL;
		}
	}
	return arcData;
}

//------------------------------------------------------------------
/**
 * $brief   �|�P�����A�C�R����]�����ăA�N�^�[�̃p���b�g�����킹��
 *
 * @param   chara		
 * @param   pokeno		
 * @param   no		
 * @param   icon		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void TransPokeIconCharaPal( int pokeno, int form, int tamago, int no, CLACT_WORK_PTR icon, ARCHANDLE* handle, WORLDTRADE_POKEBUF *pbuf )
{
	u8 *pokepal;
	u8 *buf;
	NNSG2dCharacterData *chara;

	// �|�P�����A�C�R���̃L�����f�[�^���o�b�t�@�̓ǂݍ���

	buf = CharDataGetbyHandle( handle, PokeIconCgxArcIndexGetByMonsNumber( pokeno, tamago, form ), 
								&chara, HEAPID_WORLDTRADE );
	// VBLANK���ɃL�����N�^��]�����邽�߂̏���
	MI_CpuCopyFast(chara->pRawData, pbuf->chbuf, POKEICON_TRANS_SIZE);
	pbuf->vadrs = (POKEICON_VRAM_OFFSET+no*POKEICON_TRANS_CHARA)*0x20;
	pbuf->icon = icon;
	pbuf->palno = PokeIconPalNumGet( pokeno, form, tamago )+POKEICON_PAL_OFFSET;
	sys_FreeMemoryEz(buf);
}


//------------------------------------------------------------------
/**
 * @brief   �|�P�����A�C�R���̓]���ƃZ���A�N�^�[�̕\���E��\���𐧌䂷��
 *
 * @param   paso		
 * @param   dat
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void PokemonLevelSet(POKEMON_PASO_PARAM *paso, Dpw_Tr_PokemonDataSimple *dat )
{
	dat->level = PokePasoLevelCalc( paso );
}

//------------------------------------------------------------------
/**
 * @brief   �|�P�����A�C�R���̓]��
 *
 * @param   paso		
 * @param   icon		
 * @param   no		
 * @param   pos		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void PokemonIconDraw(void *work)
{
  WORLDTRADE_WORK *wk = work;
  
  int i;
  WORLDTRADE_POKEBUF *pbuf = wk->boxicon;

  for(i = 0; i < BOX_POKE_NUM; i++, pbuf++){
    if(pbuf->icon){
      // �L�����N�^�[�]��
      DC_FlushRange(pbuf->chbuf, POKEICON_TRANS_SIZE);
      GX_LoadOBJ(pbuf->chbuf, pbuf->vadrs, POKEICON_TRANS_SIZE);
      // �p���b�g�ݒ�
      CLACT_PaletteNoChg(pbuf->icon, pbuf->palno);
    }
  }
  sys_FreeMemoryEz( wk->boxicon );
}

//------------------------------------------------------------------
/**
 * @brief   �|�P�����A�C�R���̓]���ƃZ���A�N�^�[�̕\���E��\���𐧌䂷��
 *
 * @param   paso		
 * @param   icon		
 * @param   no		
 * @param   pos		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void PokemonIconSet( POKEMON_PASO_PARAM *paso, CLACT_WORK_PTR icon, 
							CLACT_WORK_PTR itemact, u16 *no, int pos, ARCHANDLE* handle, 
							Dpw_Tr_PokemonDataSimple *dat, WORLDTRADE_POKEBUF *pbuf )
{
	int flag,itemno, tamago,form;
	
	PokePasoParaFastModeOn(paso);

	flag   = PokePasoParaGet(paso, ID_PARA_poke_exist, NULL);
	*no    = PokePasoParaGet(paso, ID_PARA_monsno,     NULL);
	form   = PokePasoParaGet(paso, ID_PARA_form_no,    NULL);
	tamago = PokePasoParaGet(paso, ID_PARA_tamago_flag,NULL);
	itemno = PokePasoParaGet(paso, ID_PARA_item,       NULL);
	dat->characterNo = *no;
	dat->gender      = PokePasoParaGet( paso, ID_PARA_sex, NULL )+1;

	// �����p�Ƀ^�}�S�̃��x�����O�Ƃ��Ă��܂��i�{���͂O����Ȃ����ǁj
	if(tamago){
		dat->level = 0;
	}

	PokePasoParaFastModeOff(paso,TRUE);
	
	if(flag){
		TransPokeIconCharaPal( *no, form, tamago, pos, icon, handle, pbuf );
		CLACT_SetDrawFlag( icon, 1 );

		// �A�C�e���������Ă��邩
		if(itemno!=0){	
			CLACT_SetDrawFlag( itemact, 1 );

			// �A�C�e���̓��[�����H
			if(ItemMailCheck( itemno )){	
				CLACT_AnmChg( itemact, CELL_MAILICON_NO );	// ���[��
			}else{
				CLACT_AnmChg( itemact, CELL_ITEMICON_NO );	// �A�C�e��
			}
		}else{
			CLACT_SetDrawFlag( itemact, 0 );
		}
	}else{
		CLACT_SetDrawFlag( icon, 0 );
		CLACT_SetDrawFlag( itemact, 0 );
		pbuf->icon = NULL;
	}
}

//------------------------------------------------------------------
/**
 * $brief   �{�b�N�X�E�Ă����̃|�P�����f�[�^��ǂݍ���
 *
 * @param   wk		
 * @param   now		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void NowBoxPageInfoGet( WORLDTRADE_WORK *wk, int now)
{
	u16 monsno[30],i,flag;
	POKEMON_PARAM      *pp;
	POKEMON_PASO_PARAM *paso;
	BOX_DATA *boxdata = wk->param->mybox;
	ARCHANDLE* handle;
	WORLDTRADE_POKEBUF *pokebuf;
	
	// �|�P�����A�C�R����]������
	wk->boxicon = pokebuf =   sys_AllocMemoryLo(HEAPID_BASE_APP, sizeof(WORLDTRADE_POKEBUF) * BOX_POKE_NUM);

	handle = ArchiveDataHandleOpen( ARC_POKEICON, HEAPID_WORLDTRADE );

	// �{�b�N�X
	if(now>=0 && now <18){
		for(i=0;i<BOX_POKE_NUM;i++){
		  PokemonLevelSet(BOXDAT_GetPokeDataAddress( boxdata, now, i ), &wk->boxWork->info[i] );
		}
		for(i=0;i<BOX_POKE_NUM;i++){
			wk->boxWork->info[i].characterNo = 0;
			PokemonIconSet(BOXDAT_GetPokeDataAddress( boxdata, now, i ), 
							wk->PokeIconActWork[i], wk->ItemIconActWork[i],
							&monsno[i], i, handle, &wk->boxWork->info[i], &pokebuf[i] );
			// �{�[���J�v�Z���̃Z���A�N�^�[�͂��ׂĉB��
			if(i<TEMOTI_POKEMAX){
				CLACT_SetDrawFlag( wk->CBallActWork[i], 0 );
			}
		}

		// �{�b�N�X�̃g���C���擾
		BOXDAT_GetBoxName( boxdata, now, wk->BoxTrayNameString );
	
	}else{
	// �Ă���
		int num = PokeParty_GetPokeCount( wk->param->myparty );

		for(i=0;i<num;i++){
			pp   = PokeParty_GetMemberPointer(wk->param->myparty, i);
			paso = PPPPointerGet(pp);
			PokemonLevelSet(paso, &wk->boxWork->info[i] );
			PokemonIconSet( paso, wk->PokeIconActWork[i], wk->ItemIconActWork[i],
							&monsno[i], i, handle, &wk->boxWork->info[i], &pokebuf[i] );

			// �{�[���J�v�Z�������Ă��邩�H
			if(PokeParaGet(pp, ID_PARA_cb_id, NULL)){
				CLACT_SetDrawFlag( wk->CBallActWork[i], 1 );
			}else{
				CLACT_SetDrawFlag( wk->CBallActWork[i], 0 );
			}
		}

		// �Ă����̃|�P������\�����I��������͑S�Ĕ�\����
		for(;i<BOX_POKE_NUM;i++){
			wk->boxWork->info[i].characterNo = 0;
			CLACT_SetDrawFlag( wk->PokeIconActWork[i], 0 );
			CLACT_SetDrawFlag( wk->ItemIconActWork[i], 0 );
			pokebuf[i].icon = NULL;
			if(i<TEMOTI_POKEMAX){
				CLACT_SetDrawFlag( wk->CBallActWork[i], 0 );
			}
		}
		MSGMAN_GetString( wk->MsgManager, msg_gtc_04_023, wk->BoxTrayNameString );
	}
	ArchiveDataHandleClose( handle );
	
	GF_BGL_BmpWinDataFill( &wk->SubWin, 0x0000 );
	WorldTrade_SysPrint( &wk->SubWin, wk->BoxTrayNameString, 0, 5, 1, GF_PRINTCOLOR_MAKE(1,2,0) );
	
	// �����|�P�����I�����[�h�̎��͏����ɍ���Ȃ��|�P�������Â�����
	if(wk->sub_process_mode==MODE_EXCHANGE_SELECT){
		PokeIconPalSet( wk->boxWork->info, wk->PokeIconActWork, &wk->DownloadPokemonData[wk->TouchTrainerPos].wantSimple, pokebuf);
	}
	
	// pokebuf�̊J����PokemonIconDraw���ōs����
	wk->vfunc = PokemonIconDraw;
}


//==============================================================================
/**
 * @brief   �w�肵���|�P�����f�[�^��POKEMON_PARAM���APOKEMON_PASO_PARAM���H
 *
 * @param   box		
 *
 * @retval  int		0:POKEMON_PASO_PARAM 1:POKEMON_PARAM
 */
//==============================================================================
int WorldTrade_GetPPorPPP( int tray )
{
	if( tray == 18 ){
		return 1;
	}else{
		return 0;
	}
}

//==============================================================================
/**
 * $brief   �ԍ�����Ă������{�b�N�X�̒���POKEMON_PASO_PARAM�ւ̍\���̂�Ԃ�
 *
 * @param   party		
 * @param   box		
 * @param   tray		
 * @param   pos		
 *
 * @retval  POKEMON_PASO_PARAM *		
 */
//==============================================================================
POKEMON_PASO_PARAM *WorldTrade_GetPokePtr( POKEPARTY *party, BOX_DATA *box,  int  tray, int pos )
{
	// �Ă���
	if(WorldTrade_GetPPorPPP( tray )){
		if(pos>(PokeParty_GetPokeCount(party)-1)){
			return NULL;
		}
		return  PPPPointerGet(PokeParty_GetMemberPointer( party, pos ));
	}

	// �{�b�N�X
	return BOXDAT_GetPokeDataAddress( box, tray, pos );
}

//==============================================================================
/**
 * @brief   �Ă����|�P�����������Ƃ��Ɏc����`�F�b�N����
 *
 * @param   party		
 * @param   box		
 * @param   tray		
 * @param   pos		
 *
 * @retval  int		
 */
//==============================================================================
static int CheckPocket( POKEPARTY *party, BOX_DATA *box,  int  tray, int pos )
{
	// �Ă������������͎c��𐔂���
	if(WorldTrade_GetPPorPPP( tray )){
		if( PokeParty_GetPokeCount(party) < 2 ){
			return 0;
		}
	}
	return 1;
}



//==============================================================================
// �g�����{���p�̒�`
//==============================================================================

#define SPECIAL_RIBBON_NUM	( 10 )				// �g�����{���̑���

static const u16 SpRibbonTbl[]={
	ID_PARA_marine_ribbon,						//�}�������{��
	ID_PARA_land_ribbon,						//�����h���{��
	ID_PARA_sky_ribbon,							//�X�J�C���{��

	ID_PARA_sinou_red_ribbon,					//�V���I�E���b�h���{��
	ID_PARA_sinou_green_ribbon,					//�V���I�E�O���[�����{��
	ID_PARA_sinou_blue_ribbon,					//�V���I�E�u���[���{��
	ID_PARA_sinou_festival_ribbon,				//�V���I�E�t�F�X�e�B�o�����{��
	ID_PARA_sinou_carnival_ribbon,				//�V���I�E�J�[�j�o�����{��
	ID_PARA_sinou_classic_ribbon,				//�V���I�E�N���V�b�N���{��
	ID_PARA_sinou_premiere_ribbon,				//�V���I�E�v���~�A���{��
};


//------------------------------------------------------------------
/**
 * @brief   ���ꃊ�{���������Ă��邩�`�F�b�N
 *
 * @param   ppp		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int PokeRibbonCheck( POKEMON_PASO_PARAM *ppp )
{
	// ���ꃊ�{���������Ă��Ȃ����H
	int i, ret = 0, flag;

	flag = PokePasoParaFastModeOn(ppp);
	for(i=0;i<SPECIAL_RIBBON_NUM;i++){
		ret += PokePasoParaGet( ppp, SpRibbonTbl[i], NULL );
	}
	PokePasoParaFastModeOff(ppp, flag);

	OS_Printf("���ꃊ�{���擾�� %d\n", ret);

	// ���ꃊ�{���������Ă���̂Ń_��
	if(ret){
		return 1;
	}
	
	return 0;
}

//==============================================================================
/**
 * $brief   �w��̃{�b�N�XNO�EPOS�ɂ̓|�P���������邩�H
 *
 * @param   party		
 * @param   box		
 * @param   tray		
 * @param   pos		
 *
 * @retval  int		
 */
//==============================================================================
static int PokemonCheck( POKEPARTY *party, BOX_DATA *box,  int  tray, int pos  )
{
	POKEMON_PASO_PARAM *ppp = WorldTrade_GetPokePtr(party, box, tray, pos );
	
	
	// NULL�`�F�b�N
	if(ppp==NULL){
		return WANT_POKE_NO;
	}

	// �|�P�����͂��邩�H
	if(!PokePasoParaGet(ppp, ID_PARA_poke_exist, NULL)){
		return WANT_POKE_NO;
	}

	// �^�}�S����Ȃ����H
	if(PokePasoParaGet(ppp, ID_PARA_tamago_exist, NULL)){
		return WANT_POKE_TAMAGO;
	}


	return WANT_POKE_OK;
}


//------------------------------------------------------------------
/**
 * @brief   ���������ɍ��v���Ă��邩��r����
 *
 * @param   poke		
 * @param   search		
 *
 * @retval  int		0:���v���Ă��Ȃ�	1:���v���Ă���
 */
//------------------------------------------------------------------
static int CompareSearchData( Dpw_Tr_PokemonDataSimple *poke,  Dpw_Tr_PokemonSearchData *search )
{
	// �|�P�������Ⴄ
	if( poke->characterNo != search->characterNo){
		return 0;
	}
	
	// ���ʎw��ƈႤ
	if( search->gender!=DPW_TR_GENDER_NONE){
		if(search->gender != poke->gender){
			return 0;
		}
	}
	
	// �|�P�������^�}�S
	if(poke->level==0){
		return 0;
	}
	
	// �w��̍Œ჌�x�������Ⴂ
	if( search->level_min!=0){
		if( search->level_min > poke->level){
			return 0;
		}
	}
	// �w��̍ō����x����������
	if( search->level_max!=0){
		if( search->level_max < poke->level){
			return 0;
		}
	}
	
	// ���v���Ă���
	return 1;

}

//------------------------------------------------------------------
/**
 * @brief   ���肪�v������|�P�����ɂ����Ă��邩�H
 *
 * @param   ppp		
 * @param   dtp		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int WantPokeCheck(POKEMON_PASO_PARAM *ppp, Dpw_Tr_PokemonSearchData *dtsd)
{
	Dpw_Tr_PokemonDataSimple temp;
	temp.characterNo = PokePasoParaGet(ppp, ID_PARA_monsno, NULL);
	temp.gender      = PokePasoParaGet( ppp, ID_PARA_sex,   NULL )+1;
	temp.level       = PokePasoLevelCalc(ppp);

	OS_Printf("want pokeno = %d, mypoke    = %d\n", dtsd->characterNo, temp.characterNo);
	OS_Printf("want sex    = %d, minesex   = %d\n", dtsd->gender     , temp.gender   );
	OS_Printf("want level_min  = %d, max  = %d, level = %d\n", dtsd->level_min,dtsd->level_max, temp.level );

	// ��r����
	return CompareSearchData( &temp, dtsd );
}

//------------------------------------------------------------------
/**
 * @brief   ���M�f�[�^�̏������s��
 *
 * @param   dtd		
 * @param   wk		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void MakeExchangePokemonData( Dpw_Tr_Data *dtd, WORLDTRADE_WORK *wk )
{
	Dpw_Tr_PokemonDataSimple post;
	Dpw_Tr_PokemonSearchData want;
	POKEMON_PASO_PARAM *ppp;

	// ���O�E���ʁE���x���擾
	post.characterNo = PokePasoParaGet( wk->deposit_ppp, ID_PARA_monsno, NULL );
	post.gender      = PokePasoParaGet( wk->deposit_ppp, ID_PARA_sex,   NULL )+1;
	post.level       = PokePasoLevelCalc( wk->deposit_ppp );

	dtd->postSimple = post;

	WorldTrade_PostPokemonBaseDataMake( dtd, wk );

	ppp = PPPPointerGet( (POKEMON_PARAM*)wk->DownloadPokemonData[wk->TouchTrainerPos].postData.data );

	want.characterNo = PokePasoParaGet( ppp, ID_PARA_monsno, NULL );
	want.gender      = PokePasoParaGet( ppp, ID_PARA_sex,   NULL )+1;
	want.level_min   = 0;
	want.level_max   = 0;
	dtd->wantSimple  = want;

	OS_Printf( "postData  No = %d,  gender = %d, level = %d\n", dtd->postSimple.characterNo, dtd->postSimple.gender, dtd->postSimple.level);

}

//------------------------------------------------------------------
/**
 * @brief   ���������ɍ���Ȃ��|�P�����A�C�R���̃J���[���Â�����
 *
 * @param   box		
 * @param   icon		
 * @param   want		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void PokeIconPalSet( Dpw_Tr_PokemonDataSimple *box, CLACT_WORK_PTR *icon, Dpw_Tr_PokemonSearchData *want, WORLDTRADE_POKEBUF *pbuf)
{
	int pal,i;
	for(i=0;i<BOX_POKE_NUM;i++){
		if(box[i].characterNo!=0){
			if(CompareSearchData( &box[i], want )==0){
				pbuf[i].palno += 3;
			}
		}
	}
}


//------------------------------------------------------------------
/**
 * @brief   ���[���������Ă��邩�H
 *
 * @param   pp		
 *
 * @retval  BOOL		
 */
//------------------------------------------------------------------
BOOL WorldTrade_PokemonMailCheck( POKEMON_PARAM *pp )
{
	int itemno = PokeParaGet( pp, ID_PARA_item,       NULL);
	// �A�C�e���̓��[�����H
	if(ItemMailCheck( itemno )){
		return TRUE;
	}
	
	return FALSE;
}
