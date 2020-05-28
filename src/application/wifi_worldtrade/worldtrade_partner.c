//============================================================================================
/**
 * @file	worldtrade_partner.c
 * @bfief	���E��������|�P�����{�����
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

#include "application/worldtrade.h"
#include "worldtrade_local.h"

#include "msgdata/msg_wifi_gtc.h"


#include "worldtrade.naix"			// �O���t�B�b�N�A�[�J�C�u��`



//============================================================================================
//	�v���g�^�C�v�錾
//============================================================================================
/*** �֐��v���g�^�C�v ***/
static void BgInit( GF_BGL_INI * ini );
static void BgExit( GF_BGL_INI * ini );
static void BgGraphicSet( WORLDTRADE_WORK *wk );
static void BmpWinInit( WORLDTRADE_WORK *wk );
static void BmpWinDelete( WORLDTRADE_WORK *wk );
static void InitWork( WORLDTRADE_WORK *wk );
static void FreeWork( WORLDTRADE_WORK *wk );
static void SetCellActor(WORLDTRADE_WORK *wk);
static void DelCellActor(WORLDTRADE_WORK *wk);

static int SubSeq_Start( WORLDTRADE_WORK *wk);
static int SubSeq_Main( WORLDTRADE_WORK *wk);
static int SubSeq_End( WORLDTRADE_WORK *wk);
static int SubSeq_MessageWait( WORLDTRADE_WORK *wk );
static int SubSeq_YesNo( WORLDTRADE_WORK *wk);
static int SubSeq_YesNoSelect( WORLDTRADE_WORK *wk);
static int SubSeq_PageChange( WORLDTRADE_WORK *wk);

static void ChangePage( WORLDTRADE_WORK *wk );
static void PokeTabLabelPrint(MSGDATA_MANAGER *MsgManager, GF_BGL_BMPWIN win[] );


static void SubSeq_MessagePrint( WORLDTRADE_WORK *wk, int msgno, int wait, int flag, u16 dat );
static void PokeInfoPrint( GF_BGL_BMPWIN win[], MSGDATA_MANAGER *gtcmsg, MSGDATA_MANAGER *monsname, Dpw_Tr_PokemonSearchData *dtp);
static void TrainerInfoPrint( GF_BGL_BMPWIN win[], STRBUF *strbuf1, STRBUF *strbuf2 );


enum{
	SUBSEQ_START=0,
	SUBSEQ_MAIN,
	SUBSEQ_END,
	SUBSEQ_MES_WAIT,
	SUBSEQ_YESNO,
	SUBSEQ_YESNO_SELECT,
	SUBSEQ_PAGE_CHANGE,
};

static int (*Functable[])( WORLDTRADE_WORK *wk ) = {
	SubSeq_Start,			// SUBSEQ_START=0,
	SubSeq_Main,             // SUBSEQ_MAIN,
	SubSeq_End,              // SUBSEQ_END,
	SubSeq_MessageWait,      // SUBSEQ_MES_WAIT
	SubSeq_YesNo,			// SUBSEQ_YESNO
	SubSeq_YesNoSelect,		// SUBSEQ_YESNO_SELECT
	SubSeq_PageChange,		// SUBSEQ_PAGE_CHANGE,
};

#define INFO_TEXT_WORD_NUM	(10*2)

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
int WorldTrade_Partner_Init(WORLDTRADE_WORK *wk, int seq)
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


	// ����̃|�P�����̏��
	WorldTrade_PokeInfoPrint( wk->MsgManager, 
							  wk->MonsNameManager, 
							  wk->WordSet, 
							  &wk->InfoWin[0], 
							  PPPPointerGet((POKEMON_PARAM*)wk->DownloadPokemonData[wk->TouchTrainerPos].postData.data),
							  &wk->DownloadPokemonData[wk->TouchTrainerPos].postSimple );

	// ��������̕\��
	WorldTrade_PokeInfoPrint2( wk->MsgManager, &wk->InfoWin[5], wk->DownloadPokemonData[wk->TouchTrainerPos].name );

	// �|�P�����摜�]��
	WorldTrade_TransPokeGraphic( (POKEMON_PARAM*)wk->DownloadPokemonData[wk->TouchTrainerPos].postData.data );

	PokeTabLabelPrint( wk->MsgManager, &wk->InfoWin[7] );

	// �u�ق����|�P�����v���u����ł���΂���v�̕`��
	ChangePage( wk );

	

	// �Q��ڈȍ~
	// ���C�v�t�F�[�h�J�n�i����ʁj
	WIPE_SYS_Start( WIPE_PATTERN_M, WIPE_TYPE_FADEIN, WIPE_TYPE_FADEIN, WIPE_FADE_BLACK, WORLDTRADE_WIPE_SPPED, 1, HEAPID_WORLDTRADE );
#ifdef GTS_FADE_OSP
	OS_Printf( "******************** worldtrade_partner.c [148] M ********************\n" );
#endif
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
int WorldTrade_Partner_Main(WORLDTRADE_WORK *wk, int seq)
{
	int ret;
	
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
int WorldTrade_Partner_End(WORLDTRADE_WORK *wk, int seq)
{
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
//	{	
//		GF_BGL_BGCNT_HEADER TextBgCntDat = {
//			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
//			GX_BG_SCRBASE_0xe800, GX_BG_CHARBASE_0x08000, GX_BG_EXTPLTT_01,
//			1, 0, 0, FALSE
//		};
//		GF_BGL_BGControlSet( ini, GF_BGL_FRAME2_M, &TextBgCntDat, GF_BGL_MODE_TEXT );
//	}



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

	
	// ��b�t�H���g�p���b�g�]��
	TalkFontPaletteLoad( PALTYPE_MAIN_BG, WORLDTRADE_TALKFONT_PAL*0x20, HEAPID_WORLDTRADE );
 //	TalkFontPaletteLoad( PALTYPE_SUB_BG,  WORLDTRADE_TALKFONT_PAL*0x20, HEAPID_WORLDTRADE );

	// ��b�E�C���h�E�O���t�B�b�N�]��
	TalkWinGraphicSet(	bgl, GF_BGL_FRAME0_M, WORLDTRADE_MESFRAME_CHR, 
						WORLDTRADE_MESFRAME_PAL,  CONFIG_GetWindowType(wk->param->config), HEAPID_WORLDTRADE );

	MenuWinGraphicSet(	bgl, GF_BGL_FRAME0_M, WORLDTRADE_MENUFRAME_CHR,
						WORLDTRADE_MENUFRAME_PAL, 0, HEAPID_WORLDTRADE );



	// ���C�����BG1�L�����]��
	ArcUtil_BgCharSet( ARC_WORLDTRADE_GRA, NARC_worldtrade_poke_view_lz_ncgr, bgl, GF_BGL_FRAME1_M, 0, 16*5*0x20, 1, HEAPID_WORLDTRADE);

	// ���ʂa�f�p���b�g�]��
	ArcUtil_PalSet(    ARC_WORLDTRADE_GRA, NARC_worldtrade_poke_view_nclr, PALTYPE_MAIN_BG, 0, 16*3*2,  HEAPID_WORLDTRADE);

	// �X�N���[����_Init�̉��̕��ōs��
}


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
	//�o�^���i�[
	CLACT_ADD add;
	WorldTrade_MakeCLACT( &add,  wk, &wk->clActHeader_main, NNS_G2D_VRAM_TYPE_2DMAIN );

	// ����̃|�P�����\��
	add.mat.x = FX32_ONE *   200;
	add.mat.y = FX32_ONE *    58;
	wk->PokemonActWork = CLACT_Add(&add);
	CLACT_SetAnmFlag(wk->PokemonActWork,1);
	CLACT_AnmChg( wk->PokemonActWork, 37 );
	
	WirelessIconEasy();
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
	CLACT_Delete(wk->PokemonActWork);
}

#define NAME_TEXT_X		(  8 )
#define NAME_TEXT_Y		(  5 )
#define NAME_TEXT_SX	( 10 )
#define NAME_TEXT_SY	(  2 )

#define MENU_MAX_NUM	(  3 )

#define SELECT_MENU_X	(  21 )
#define SELECT_MENU_Y 	(  15 )
#define SELECT_MENU_SX	( 5*2 )
#define SELECT_MENU_SY	(   4 )

#define LINE_MESSAGE_OFFSET   ( WORLDTRADE_MENUFRAME_CHR + MENU_WIN_CGX_SIZ )
#define SELECT_MENU_OFFSET    ( LINE_MESSAGE_OFFSET + LINE_TEXT_SX*LINE_TEXT_SY )
#define INFO_TEXT_OFFSET	  ( SELECT_MENU_OFFSET + SELECT_MENU_SX*SELECT_MENU_SY )
static const info_bmpwin_table[][4]={
	{  2,  2, 10,  2, },	// �|�P�����̃j�b�N�l�[��
	{  3,  4,  8,  2, },	// �|�P�����̎푰��
	{  12, 4,  7,  2, },	// ���x������
	{  2,  7,  5,  2, },	// �u�������́v
	{  8,  7, 11,  2, },	// �����A�C�e����
	{  4, 10,  6,  2, },	// �u�����ʂ��v
	{ 11, 10,  8,  2, },	// �g���[�i�[��
	{  3, 13,  9,  2, },	// �u�ق����|�P�����v
	{ 16, 13, 13,  2, },	// �u����ł���΂���v//154
	{  2, 15, 27,  2, },	// ���1
	{  3, 17, 27,  2, },	// ���2
};

// �͂��E��������BMPWIN�̈�͍Ō�ɂ����Ă������̂����A
// ���E�C���h�E�̑�������߂Ȃ��̂ŁA204�L�������炵�Ă���
// �i�͂��Ă��܂����̂�204�L�����ɕς��� by Mori (06.05.09)
#define YESNO_OFFSET 		   ( SELECT_MENU_OFFSET + SELECT_MENU_SX*SELECT_MENU_SY+262 )

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

	GF_BGL_BmpWinAdd(wk->bgl, &wk->MsgWin, GF_BGL_FRAME0_M,
		LINE_TEXT_X, LINE_TEXT_Y, LINE_TEXT_SX, LINE_TEXT_SY, 
		WORLDTRADE_TALKFONT_PAL,  LINE_MESSAGE_OFFSET );

	GF_BGL_BmpWinDataFill( &wk->MsgWin, 0x0000 );

	// BMPMENU�p�̗̈悪�����ɂ���
	GF_BGL_BmpWinAdd(wk->bgl, &wk->MenuWin[0], GF_BGL_FRAME0_M,
		SELECT_MENU_X, SELECT_MENU_Y, SELECT_MENU_SX, SELECT_MENU_SY, 
		WORLDTRADE_TALKFONT_PAL,  SELECT_MENU_OFFSET );	

	// BG0��BMPWIN���E�C���h�E�m��
	{
		int i, offset;

		offset = INFO_TEXT_OFFSET;
		for(i=0;i<11;i++){
			GF_BGL_BmpWinAdd(wk->bgl, &wk->InfoWin[i], GF_BGL_FRAME0_M,
					info_bmpwin_table[i][0], 
					info_bmpwin_table[i][1], 
					info_bmpwin_table[i][2], 
					info_bmpwin_table[i][3], 
					WORLDTRADE_TALKFONT_PAL,  offset );
			GF_BGL_BmpWinDataFill( &wk->InfoWin[i], 0x0000 );
			offset += info_bmpwin_table[i][2]*info_bmpwin_table[i][3];
		}
	}


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
	GF_BGL_BmpWinDel( &wk->MenuWin[0] );
	{
		int i;
		for(i=0;i<11;i++){
			GF_BGL_BmpWinDel( &wk->InfoWin[i] );
		}
	}


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
	int i;
	MSGDATA_MANAGER *man;
	Dpw_Tr_Data     *dtp = &wk->DownloadPokemonData[wk->TouchTrainerPos];

	// ������o�b�t�@�쐬
	wk->TalkString  = STRBUF_Create( TALK_MESSAGE_BUF_NUM, HEAPID_WORLDTRADE );

	WORDSET_ClearAllBuffer( wk->WordSet );
	// ���ԍ������݂��Ă���ꍇ�͕�������Z�b�g
	if(dtp->countryCode!=0){
		WORDSET_RegisterCountryName( wk->WordSet, 8, dtp->countryCode );
	}
	// �n��ԍ������݂��Ă���ꍇ�͕�������Z�b�g
	if(dtp->localCode!=0){
		WORDSET_RegisterLocalPlaceName( wk->WordSet, 9, dtp->countryCode, dtp->localCode );
	}

	// ���E�n�敶����擾
	wk->InfoString[0] = MSGDAT_UTIL_AllocExpandString( wk->WordSet, wk->MsgManager, msg_gtc_04_013, HEAPID_WORLDTRADE );
	wk->InfoString[1] = MSGDAT_UTIL_AllocExpandString( wk->WordSet, wk->MsgManager, msg_gtc_04_014, HEAPID_WORLDTRADE );
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
	int i;

	STRBUF_Delete(wk->InfoString[0]);
	STRBUF_Delete(wk->InfoString[1]);

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
static int SubSeq_Start( WORLDTRADE_WORK *wk)
{
	// 
//	SubSeq_MessagePrint( wk, msg_wifilobby_028, 1, 0, 0x0f0f );
//	WorldTrade_SetNextSeq( wk, SUBSEQ_MES_WAIT, SUBSEQ_MAIN );

//	ChangePage( wk );
	
	wk->subprocess_seq = SUBSEQ_MAIN;

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
static int SubSeq_Main( WORLDTRADE_WORK *wk)
{
	if(sys.trg & PAD_BUTTON_A){
		SubSeq_MessagePrint( wk, msg_gtc_01_017, 1, 0, 0x0f0f );
		WorldTrade_SetNextSeq( wk, SUBSEQ_MES_WAIT, SUBSEQ_YESNO );
		Snd_SePlay(WORLDTRADE_DECIDE_SE);
	}else if(sys.trg & PAD_BUTTON_B){
		wk->subprocess_seq  = SUBSEQ_END;
		WorldTrade_SubProcessChange( wk, WORLDTRADE_SEARCH, 0 );
		Snd_SePlay(WORLDTRADE_DECIDE_SE);
	}else if(sys.trg & PAD_KEY_RIGHT){
		if(wk->PartnerPageInfo==0){
			wk->PartnerPageInfo = 1;
			wk->subprocess_seq = SUBSEQ_PAGE_CHANGE;
			Snd_SePlay(WORLDTRADE_DECIDE_SE);
		}
	}else if(sys.trg & PAD_KEY_LEFT){
		if(wk->PartnerPageInfo!=0){
			wk->PartnerPageInfo = 0;
			wk->subprocess_seq = SUBSEQ_PAGE_CHANGE;
			Snd_SePlay(WORLDTRADE_DECIDE_SE);
		}
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
static int SubSeq_End( WORLDTRADE_WORK *wk)
{
	// �͂��E�������\���ŉ�ʂ�����Ă���̂Łu�ق����|�P�v�u�Z��ł�ꏊ�v�����ĕ`��
	PokeTabLabelPrint( wk->MsgManager, &wk->InfoWin[7] );
	ChangePage( wk );

	WIPE_SYS_Start( WIPE_PATTERN_M, WIPE_TYPE_FADEOUT, WIPE_TYPE_FADEOUT, WIPE_FADE_BLACK, WORLDTRADE_WIPE_SPPED, 1, HEAPID_WORLDTRADE );
#ifdef GTS_FADE_OSP
	OS_Printf( "******************** worldtrade_partner.c [607] M ********************\n" );
#endif
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
			// ����������������
			wk->subprocess_seq  = SUBSEQ_END;
			WorldTrade_SubProcessChange( wk, WORLDTRADE_SEARCH, 0 );
		}else{
			// �������o���|�P�����̑I����
			wk->subprocess_seq  = SUBSEQ_END;
			WorldTrade_SubProcessChange( wk, WORLDTRADE_MYBOX, MODE_EXCHANGE_SELECT );
		}
	}

	return SEQ_MAIN;
	
}

//------------------------------------------------------------------
/**
 * $brief   ���E�ŏ��y�[�W��؂�ւ���
 *
 * @param   wk		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void ChangePage( WORLDTRADE_WORK *wk )
{
	if(wk->PartnerPageInfo==0){
		// �ق����|�P�����̏��
		ArcUtil_ScrnSet(   
			ARC_WORLDTRADE_GRA, 
			NARC_worldtrade_searchpoke0_lz_nscr, 
			wk->bgl, GF_BGL_FRAME1_M, 0, 32*24*2, 1, HEAPID_WORLDTRADE);

		PokeInfoPrint( &wk->InfoWin[9], wk->MsgManager, wk->MonsNameManager, 
						&wk->DownloadPokemonData[wk->TouchTrainerPos].wantSimple);
	}else{
		// ����ł���΂���
		ArcUtil_ScrnSet(   
			ARC_WORLDTRADE_GRA, 
			NARC_worldtrade_searchpoke1_lz_nscr, 
			wk->bgl, GF_BGL_FRAME1_M, 0, 32*24*2, 1, HEAPID_WORLDTRADE);

		TrainerInfoPrint( &wk->InfoWin[9], wk->InfoString[0], wk->InfoString[1] );
	}
	
	// BMPWIN�̓��e�ύX�������ōs��

}	



//------------------------------------------------------------------
/**
 * $brief   ���y�[�W��؂�ւ���
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int SubSeq_PageChange( WORLDTRADE_WORK *wk)
{
	ChangePage( wk );
	wk->subprocess_seq = SUBSEQ_MAIN;

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
 * $brief   ��b�E�C���h�E�\��
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
	
//	tempbuf = STRBUF_Create( TALK_MESSAGE_BUF_NUM, HEAPID_WORLDTRADE );
	MSGMAN_GetString(  wk->MsgManager, msgno, wk->TalkString );
//	WORDSET_ExpandStr( wk->WordSet, wk->TalkString, tempbuf );
//	STRBUF_Delete(tempbuf);

	// ��b�E�C���h�E�g�`��
	GF_BGL_BmpWinDataFill( &wk->MsgWin,  0x0f0f );
	BmpTalkWinWrite( &wk->MsgWin, WINDOW_TRANS_ON, WORLDTRADE_MESFRAME_CHR, WORLDTRADE_MESFRAME_PAL );

	// ������`��J�n
	wk->MsgIndex = GF_STR_PrintSimple( &wk->MsgWin, FONT_TALK, wk->TalkString, 0, 0, wait, NULL);


}


//------------------------------------------------------------------
/**
 * @brief   �u�ق����ۂ�����v�E�u����ł���ꏊ�v�`��
 *
 * @param   win[]		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void PokeTabLabelPrint( MSGDATA_MANAGER *MsgManager, GF_BGL_BMPWIN win[] )
{
	STRBUF *strbuf1,*strbuf2;
	
	strbuf1 = MSGMAN_AllocString( MsgManager, msg_gtc_04_008  );
	strbuf2 = MSGMAN_AllocString( MsgManager, msg_gtc_04_012  );

	WorldTrade_SysPrint( &win[0], strbuf1, 0, 2, 0, GF_PRINTCOLOR_MAKE(15,2,0) );
	WorldTrade_SysPrint( &win[1], strbuf2, 0, 2, 1, GF_PRINTCOLOR_MAKE(15,2,0) );
	
	STRBUF_Delete( strbuf1 );
	STRBUF_Delete( strbuf2 );
	
}

//------------------------------------------------------------------
/**
 * @brief   �ق����|�P�����̕`��
 *
 * @param   win[]		
 * @param   gtcmsg		
 * @param   monsname		
 * @param   dtp		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void PokeInfoPrint( GF_BGL_BMPWIN win[], MSGDATA_MANAGER *gtcmsg, MSGDATA_MANAGER *monsname, Dpw_Tr_PokemonSearchData *dtsd)
{
	//�u�ق����|�P�����v�`��
	GF_BGL_BmpWinDataFill( &win[0], 0x0000 );
	WorldTrade_PokeNamePrint(&win[0], monsname, dtsd->characterNo, 0, 3,GF_PRINTCOLOR_MAKE(15,2,0) );

	// ����
	WorldTrade_SexPrint( &win[0], gtcmsg, dtsd->gender, 0, 3, 70, GF_PRINTCOLOR_MAKE(15,2,0) );


	// ���x���w��
	GF_BGL_BmpWinDataFill( &win[1], 0x0000 );
	WorldTrade_WantLevelPrint( &win[1], gtcmsg, 
		WorldTrade_LevelTermGet(dtsd->level_min, dtsd->level_max), 
		0, 3, GF_PRINTCOLOR_MAKE(15,2,0) );
	
}

//------------------------------------------------------------------
/**
 * @brief   �g���[�i�[�̍��E�n���`��
 *
 * @param   win[]		
 * @param   strbuf1		
 * @param   strbuf2		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void TrainerInfoPrint( GF_BGL_BMPWIN win[], STRBUF *strbuf1, STRBUF *strbuf2 )
{
	
	GF_BGL_BmpWinDataFill( &win[0], 0x0000 );
	GF_BGL_BmpWinDataFill( &win[1], 0x0000 );

	if(strbuf1!=NULL){
		WorldTrade_SysPrint( &win[0], strbuf1, 0, 3, 0, GF_PRINTCOLOR_MAKE(15,2,0) );
	}
	if(strbuf2!=NULL){
		WorldTrade_SysPrint( &win[1], strbuf2, 0, 3, 0, GF_PRINTCOLOR_MAKE(15,2,0) );
	}
	
}

