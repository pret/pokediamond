//============================================================================================
/**
 * @file	tradelist.c
 * @bfief	ポケモン交換リスト画面
 * @author	Akito Mori
 * @date	05.12.08
 */
//============================================================================================

#include "common.h"
#include "system/procsys.h"
#include "system/arc_tool.h"
#include "system/arc_util.h"
#include "system/pm_str.h"
#include "system/clact_tool.h"
#include "system/msgdata_util.h"
#include "system/wordset.h"
#include "msgdata/msg.naix"
#include "system/brightness.h"
#include "system/fontproc.h"
#include "system/lib_pack.h"
#include "system/fontoam.h"
#include "system/window.h"
#include "system/bmp_menu.h"
#include "gflib/msg_print.h"
#include "gflib/touchpanel.h"
#include "poketool/monsno.h"
#include "poketool/pokeicon.h"
#include "application/tradelist.h"
#include "system/bmp_menu.h"
#include "system/snd_tool.h"
#include "gflib/strbuf_family.h"
#include "savedata/friendlist.h"
#include "savedata/friendlist_local.h"

#include "comm_command_tradelist.h"
#include "tradelist_def.h"
#include "tradelist_bmp.h"


static void BmpListMoveSeCall(BMPLIST_WORK * wk,u32 param,u8 mode);


//------------------------------------------------------------------
// 各データ定義
//------------------------------------------------------------------

// サブ画面BMPWIN配置情報
static const u16 sub_bmp_table[][5]={
	{SUB_MYPOKENAME_X,		SUB_POKENAME_Y,SUB_POKENAME_W,SUB_POKENAME_H,SUB_MYPOKEBMP_OFFSET},
	{SUB_FRIENDPOKENAME_X,	SUB_POKENAME_Y,SUB_POKENAME_W,SUB_POKENAME_H,SUB_FRIENDPOKEBMP_OFFSET},

	{SUB_MYPOKELEVEL_X,		SUB_POKELEVEL_Y,	SUB_POKELEVEL_W, SUB_POKELEVEL_H, SUB_MYPOKELVBMP_OFFSET },
	{SUB_FRIENDPOKELEVEL_X,	SUB_POKELEVEL_Y,	SUB_POKELEVEL_W, SUB_POKELEVEL_H, SUB_FRIENDPOKELVBMP_OFFSET },
	
	{SUB_MOTIMONOSTR_L_X, 	SUB_MOTIMONOSTR_Y,	 SUB_MOTIMONOSTR_W,	 SUB_MOTIMONOSTR_H,	 SUB_MYMOTIMONOSTRBMP_OFFSET },
	{SUB_MOTIMONOSTR_R_X,	SUB_MOTIMONOSTR_Y,	 SUB_MOTIMONOSTR_W,	 SUB_MOTIMONOSTR_H,	  SUB_FRIENDMOTIMONOSTRBMP_OFFSET},

	{SUB_MYITEM_X,			SUB_ITEM_Y,SUB_ITEM_W	,SUB_ITEM_H	,SUB_MYITEMBMP_OFFSET },
	{SUB_FRIENDITEM_X,		SUB_ITEM_Y,SUB_ITEM_W	,SUB_ITEM_H	,SUB_FRIENDITEMBMP_OFFSET },
	
};

static const u16 main_pokename_table[][2]={
	{TRADELIST_POKENAME_X + TRADELIST_POKENAME_OFSX*0, TRADELIST_POKENAME_Y + TRADELIST_POKENAME_OFSY*0,},
	{TRADELIST_POKENAME_X + TRADELIST_POKENAME_OFSX*1, TRADELIST_POKENAME_Y + TRADELIST_POKENAME_OFSY*0,},
	{TRADELIST_POKENAME_X + TRADELIST_POKENAME_OFSX*0, TRADELIST_POKENAME_Y + TRADELIST_POKENAME_OFSY*1,},
	{TRADELIST_POKENAME_X + TRADELIST_POKENAME_OFSX*1, TRADELIST_POKENAME_Y + TRADELIST_POKENAME_OFSY*1,},
	{TRADELIST_POKENAME_X + TRADELIST_POKENAME_OFSX*0, TRADELIST_POKENAME_Y + TRADELIST_POKENAME_OFSY*2,},
	{TRADELIST_POKENAME_X + TRADELIST_POKENAME_OFSX*1, TRADELIST_POKENAME_Y + TRADELIST_POKENAME_OFSY*2,},

	{TRADELIST_POKENAME_X + TRADELIST_POKENAME_OFSX*2, TRADELIST_POKENAME_Y + TRADELIST_POKENAME_OFSY*0,},
	{TRADELIST_POKENAME_X + TRADELIST_POKENAME_OFSX*3, TRADELIST_POKENAME_Y + TRADELIST_POKENAME_OFSY*0,},
	{TRADELIST_POKENAME_X + TRADELIST_POKENAME_OFSX*2, TRADELIST_POKENAME_Y + TRADELIST_POKENAME_OFSY*1,},
	{TRADELIST_POKENAME_X + TRADELIST_POKENAME_OFSX*3, TRADELIST_POKENAME_Y + TRADELIST_POKENAME_OFSY*1,},
	{TRADELIST_POKENAME_X + TRADELIST_POKENAME_OFSX*2, TRADELIST_POKENAME_Y + TRADELIST_POKENAME_OFSY*2,},
	{TRADELIST_POKENAME_X + TRADELIST_POKENAME_OFSX*3, TRADELIST_POKENAME_Y + TRADELIST_POKENAME_OFSY*2,},

	{ TRADE_EX_MYPOKENAME_X, TRADE_EX_MYPOKENAME_Y, },
	{ TRADE_EX_F_POKENAME_X, TRADE_EX_F_POKENAME_Y, },

};

//------------------------------------------------------------------
/**
 * BMPWIN処理（文字パネルにフォント描画）
 *
 * @param   wk		
 *
 * @retval  none	
 */
//------------------------------------------------------------------
void TradeList_BmpMessageSet(GF_BGL_INI *bgl, GF_BGL_BMPWIN *TradeListWin, CONFIG *config)
{
	int i;

	// メイン画面の自分の名前
	GF_BGL_BmpWinAdd(bgl, &TradeListWin[BMP_M_MYNAME_WIN], GF_BGL_FRAME1_M,
				TRADELIST_MYNAME_X, TRADELIST_NAME_Y, TRADELIST_NAME_W, TRADELIST_NAME_H, 8,  MAIN_MYNAMEBMP_OFFSET);
	GF_BGL_BmpWinDataFill( &TradeListWin[BMP_M_MYNAME_WIN], 0 );

	GF_BGL_BmpWinAdd(bgl, &TradeListWin[BMP_M_FRIENDNAME_WIN], GF_BGL_FRAME1_M,
				TRADELIST_FRIENDNAME_X, TRADELIST_NAME_Y, TRADELIST_NAME_W, TRADELIST_NAME_H, 8,  MAIN_FRIENDNAMEBMP_OFFSET);
	GF_BGL_BmpWinDataFill( &TradeListWin[BMP_M_FRIENDNAME_WIN], 0 );

	// 「おわり」
	GF_BGL_BmpWinAdd(bgl, &TradeListWin[BMP_M_ENDSTR_WIN], GF_BGL_FRAME1_M,
				TRADELIST_ENDSTR_X,	TRADELIST_ENDSTR_Y,TRADELIST_ENDSTR_W,TRADELIST_ENDSTR_H,8,	MAIN_ENDSTRBMP_OFFSET);
	GF_BGL_BmpWinDataFill( &TradeListWin[BMP_M_ENDSTR_WIN], 0 );


	// メイン画面の会話ウインドウ処理
	TalkWinGraphicSet( bgl, GF_BGL_FRAME0_M, TALKWIN_FRAME_OFFSET, 10, CONFIG_GetWindowType(config), HEAPID_TRADELIST );           
	MenuWinGraphicSet( bgl, GF_BGL_FRAME0_M, MENUWIN_FRAME_OFFSET, 11, 0, HEAPID_TRADELIST );

	GF_BGL_BmpWinAdd(bgl, &TradeListWin[BMP_M_MES1_WIN], GF_BGL_FRAME0_M,
			TRADELIST_TALKWIN1_X, TRADELIST_TALKWIN1_Y, TRADELIST_TALKWIN1_W, TRADELIST_TALKWIN1_H, TALK_FONT_PAL,  MAIN_TALKWIN1_OFFSET);
	GF_BGL_BmpWinDataFill( &TradeListWin[BMP_M_MES1_WIN], 0 );
	GF_BGL_BmpWinAdd(bgl, &TradeListWin[BMP_M_MES2_WIN], GF_BGL_FRAME0_M,
			TRADELIST_TALKWIN2_X, TRADELIST_TALKWIN2_Y, TRADELIST_TALKWIN2_W, TRADELIST_TALKWIN2_H, TALK_FONT_PAL,  MAIN_TALKWIN2_OFFSET);
	GF_BGL_BmpWinDataFill( &TradeListWin[BMP_M_MES2_WIN], 0 );
	GF_BGL_BmpWinAdd(bgl, &TradeListWin[BMP_M_MES3_WIN], GF_BGL_FRAME0_M,
			TRADELIST_TALKWIN3_X, TRADELIST_TALKWIN3_Y, TRADELIST_TALKWIN3_W, TRADELIST_TALKWIN3_H, TALK_FONT_PAL,  MAIN_TALKWIN3_OFFSET);
	GF_BGL_BmpWinDataFill( &TradeListWin[BMP_M_MES3_WIN], 0 );

	GF_BGL_BmpWinAdd(bgl, &TradeListWin[BMP_M_SELECT1_WIN], GF_BGL_FRAME0_M,
			TRADELIST_SELECT1_X, TRADELIST_SELECT1_Y, TRADELIST_SELECT1_W, TRADELIST_SELECT1_H, 13,  MAIN_SELECT1_OFFSET);
	GF_BGL_BmpWinDataFill( &TradeListWin[BMP_M_SELECT1_WIN], 0 );
	GF_BGL_BmpWinAdd(bgl, &TradeListWin[BMP_M_SELECT2_WIN], GF_BGL_FRAME0_M,
			TRADELIST_SELECT2_X, TRADELIST_SELECT2_Y, TRADELIST_SELECT2_W, TRADELIST_SELECT2_H, 13,  MAIN_SELECT2_OFFSET);
	GF_BGL_BmpWinDataFill( &TradeListWin[BMP_M_SELECT2_WIN], 0 );


	// ポケモンの名前
	for(i=0;i<14;i++){
		GF_BGL_BmpWinAdd(bgl, &TradeListWin[BMP_M_MYPOKENAME0_WIN+i], GF_BGL_FRAME1_M,
				main_pokename_table[i][0],
				main_pokename_table[i][1],
				TRADELIST_POKENAME_W,
				TRADELIST_POKENAME_H,
				8,  
				MAIN_POKENAME_OFFSET+i*(TRADELIST_POKENAME_W*TRADELIST_POKENAME_H));
		GF_BGL_BmpWinDataFill( &TradeListWin[BMP_M_MYPOKENAME0_WIN+i], 0 );
	}

	// サブ画面の文字情報
	for(i=0;i<8;i++){
		GF_BGL_BmpWinAdd(bgl, &TradeListWin[BMP_S_MYPOKENAME_WIN+i], GF_BGL_FRAME0_S,
				sub_bmp_table[i][0], sub_bmp_table[i][1],sub_bmp_table[i][2],sub_bmp_table[i][3], 8,  sub_bmp_table[i][4]);
		GF_BGL_BmpWinDataFill( &TradeListWin[BMP_S_MYPOKENAME_WIN+i], 0 );

	}


}	



//==============================================================================
/**
 * BMP解放
 *
 * @param   TradeListWin		
 *
 * @retval  none		
 */
//==============================================================================
void TradeListBmpExit(GF_BGL_BMPWIN *TradeListWin)
{
	int i;

	// ポケモンの名前
	for(i=0;i<14;i++){
		GF_BGL_BmpWinDel( &TradeListWin[BMP_M_MYPOKENAME0_WIN+i] );
	}


	// サブ画面の文字情報
	for(i=0;i<8;i++){
		GF_BGL_BmpWinDel( &TradeListWin[BMP_S_MYPOKENAME_WIN+i] );
	}

	GF_BGL_BmpWinDel( &TradeListWin[BMP_M_MYNAME_WIN]		);
	GF_BGL_BmpWinDel( &TradeListWin[BMP_M_FRIENDNAME_WIN]	);
	GF_BGL_BmpWinDel( &TradeListWin[BMP_M_ENDSTR_WIN]		);

	GF_BGL_BmpWinDel(  &TradeListWin[BMP_M_MES1_WIN] );
	GF_BGL_BmpWinDel(  &TradeListWin[BMP_M_MES2_WIN] );
	GF_BGL_BmpWinDel(  &TradeListWin[BMP_M_MES3_WIN] );
	GF_BGL_BmpWinDel(  &TradeListWin[BMP_M_SELECT1_WIN] );
	GF_BGL_BmpWinDel(  &TradeListWin[BMP_M_SELECT2_WIN] );
	


	
}


//------------------------------------------------------------------
/**
 * 交換リスト内での文字列表示処理
 *
 * @param   win		
 * @param   strbuf		
 * @param   bmp_width	センタリングするときのBMPWINの横幅（キャラ単位)
 * @param   wait		
 * @param   print_sw	LEFT_PRINTで左詰め,CENTER_PRINTでセンタリング
 *
 * @retval  none		
 */
//------------------------------------------------------------------
void TradeListPrint(GF_BGL_BMPWIN *win, STRBUF *strbuf, int bmp_width, u32 wait, int print_sw, int y)
{
	int sx = 0;
	
	// センタリングを行うか？
	if(print_sw==CENTER_PRINT){
		int strlen;

		strlen = FontProc_GetPrintStrWidth( FONT_SYSTEM, strbuf, 0 );
		sx = ((win->sizx*8)-strlen)/2;
//		sx = (bmp_width*8-strlen) / 2;
	}else{
		// LEFT_PRINT以外の場合は横移動オフセットになる
		sx = print_sw;
	}

	GF_STR_PrintColor( win, FONT_SYSTEM, strbuf, sx, y, wait, GF_PRINTCOLOR_MAKE(11, 12, 0), NULL );
}

//==============================================================================
/**
 * 会話ウインドウ描画処理
 *
 * @param   win		
 * @param   strbuf	
 * @param   msg		
 *
 * @retval  none		
 */
//==============================================================================
int TradeListWindowPrint(GF_BGL_BMPWIN *win, int msg, int font, MSGDATA_MANAGER *Man, WORDSET *WordSet)
{
	STRBUF *temp;
    int index;
	
	temp = MSGDAT_UTIL_AllocExpandString( WordSet, Man, msg, HEAPID_TRADELIST );

	if(font==FONT_TALK){
		BmpTalkWinWrite( win, WINDOW_TRANS_ON, TALKWIN_FRAME_OFFSET, 10 );
	}else{
		BmpMenuWinWrite( win, WINDOW_TRANS_ON, MENUWIN_FRAME_OFFSET, 11 );
	}

	GF_BGL_BmpWinDataFill( win, 15 );
	index = GF_STR_PrintColor( win, font, temp, 0, 0, MSG_ALLPUT, GF_PRINTCOLOR_MAKE(1, 2, 15), NULL );
	
	STRBUF_Delete( temp );
    return index;
}

static const BMPWIN_DAT TradeYesNoBmpDat={
	GF_BGL_FRAME0_M,25,13,6,4,3,MAIN_YESNO_OFFSET,
};

//==============================================================================
/**
 * $brief   はい・いいえ処理
 *
 * @param   bgl		
 * @param   menu		
 * @param   seq		
 *
 * @retval  u32		
 */
//==============================================================================
u32 TradeListYesNoFunc(GF_BGL_INI * bgl, BMPMENU_WORK **menu, int *seq)
{
	u32 result=BMPMENU_NULL;
	
	switch(*seq){
	case 0:
		*menu = BmpYesNoSelectInit(	bgl, &TradeYesNoBmpDat, MENUWIN_FRAME_OFFSET, 11, HEAPID_TRADELIST );
		(*seq)++;
		break;
	case 1:
		result=BmpYesNoSelectMain( *menu, HEAPID_TRADELIST);
		if(result!=BMPMENU_NULL){
//			BmpYesNoWinDel( *menu, HEAPID_TRADELIST );
			(*seq)=0;
		}
	}

	return result;
}

void TradeListWinWrite(GF_BGL_BMPWIN *win)
{

	BmpMenuWinWrite( win, WINDOW_TRANS_ON, MENUWIN_FRAME_OFFSET, 11 );
	
}

//==============================================================================
/**
 * $brief   LISTWINDOW
 * @param   bgl		
 * @param   menu		
 * @param   seq		
 * @retval  u32		
 */
//==============================================================================

#define _MENU_POSX    (19)
#define _MENU_POSY    (1)
#define _MENU_SIZE_X  (12)
#define FLD_SYSFONT_PAL	     ( 13 )         //  システムフォント
#define FLD_MENUFRAME_PAL    ( 11 )         //  メニューウインドウ

///汎用選択メニューのリスト
static const BMPLIST_HEADER MenuListHeader = {
    NULL,			// 表示文字データポインタ
    NULL,					// カーソル移動ごとのコールバック関数
    NULL,					// 一列表示ごとのコールバック関数
    NULL,					// 
    WIFILIST_FRIEND_MAX,	// リスト項目数
    WIFILIST_FRIEND_MAX,	// 表示最大項目数
    0,						// ラベル表示Ｘ座標
    8,						// 項目表示Ｘ座標
    0,						// カーソル表示Ｘ座標
    0,						// 表示Ｙ座標
    1,						// 文字色
    15,						// 背景色
    2,						// 文字影色
    0,						// 文字間隔Ｘ
    16,						// 文字間隔Ｙ
    BMPLIST_LRKEY_SKIP,		// ページスキップタイプ
    FONT_SYSTEM,			// 文字指定
    0,						// ＢＧカーソル(allow)表示フラグ(0:ON,1:OFF)
    NULL,                   // ワーク
};


//==============================================================================
/**
 * @brief   選択リスト初期化
 *
 * @param   menulist		
 * @param   count		
 * @param   pWin		
 * @param   bgl		
 *
 * @retval  BMPLIST_WORK*		
 */
//==============================================================================
BMPLIST_WORK* TradeListMenuInit(BMPLIST_DATA* menulist, int count,GF_BGL_BMPWIN* pWin,GF_BGL_INI* bgl )
{
    BMPLIST_WORK* lw;
    BMPLIST_HEADER list_h;
    int line = 5;

    //BMPウィンドウ生成
    GF_BGL_BmpWinAdd(bgl, pWin,
                GF_BGL_FRAME0_M, _MENU_POSX, _MENU_POSY,
                _MENU_SIZE_X, line * 2, 13,
                TALKWIN_FRAME_OFFSET - (10 * (line+2) * 2));
    BmpMenuWinWrite(pWin, WINDOW_TRANS_ON, MENUWIN_FRAME_OFFSET, FLD_MENUFRAME_PAL );

    list_h       = MenuListHeader;
    list_h.count = count + 1;
    list_h.line  = line;
    list_h.list  = menulist;
    list_h.win   = pWin;
	list_h.call_back = BmpListMoveSeCall;
    lw           = BmpListSet(&list_h, 0, 0, HEAPID_TRADELIST);

    return lw;
}

//リスト表示用コールバック
static void BmpListMoveSeCall(BMPLIST_WORK * wk,u32 param,u8 mode)
{
	if( mode == 0 ){	//初期化時
		Snd_SePlay( SEQ_SE_DP_SELECT );
	}
}

