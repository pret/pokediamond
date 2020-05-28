//============================================================================================ 
/**
 * @file	d_mori.c
 * @bfief	森 デバッグメニュー
 * @author	mori GAME FREAK inc.
 */
//============================================================================================

#include "common.h"
#include "gflib/strbuf.h"
#include "gflib/strbuf_family.h"
#include "system/lib_pack.h"
#include "system/bmp_list.h"
#include "fieldmap.h"
#include "worldmap.h"
#include "fieldsys.h"
#include "field_event.h"
#include "system/fontproc.h"
#include "system/arc_util.h"
#include "system/window.h"
#include "fld_bmp.h"
#include "system/pm_str.h"
#include "fld_debug.h"
#include "talk_msg.h"
#include "encount_effect.h"
#include "poketool/poke_tool.h"
#include "poketool/pokeparty.h"
#include "msgdata/msg.naix"
#include "system/snd_play.h"
#include "system/snd_tool.h"
#include "savedata/savedata.h"
#include "savedata/wifilist.h"
#include "savedata/config.h"
#include "savedata/perapvoice.h"
#include "savedata/sodateyadata.h"
#include "sodateya.h"
#include "itemtool/item.h"

#include "msgdata/msg_debug_mori.h"
#include "application/namein.h"
#include "application/tradelist.h"
#include "communication/communication.h"

#include "communication/wpb.h"
#include "communication/wpbpokemon.h"
#include "communication/wpbutil.h"
#include  "communication/wm_icon.h"

//---------------------------------------------------------------------------------------------
// 定義
//---------------------------------------------------------------------------------------------
#define	DEBUG_WK_SIZE		( 4*16 )

enum {
	WK_SEQ = 0,
	WK_WIN_INDEX,
	WK_LIST_ID,
	WK_LIST_RET,
	WK_GF_BGL_INI,
	WK_MIC_PARAM,
	WK_FIELDSYS,
	WK_TALK_INDEX,
	WK_MES_SEQ,
	WK_MES_INDEX,
	WK_MES_WAIT,
	WK_WM_ICON,
};

typedef struct{
	u32 work[DEBUG_WK_SIZE];

	MSGDATA_MANAGER		*man;
	BMP_MENULIST_DATA 	*ld;
}DEBUG_MORI_WORK;

typedef struct{
	int 			seq;
	int 			sub;
	int				flag;
	GF_BGL_INI    	*bgl;
	FIELDSYS_WORK 	*fsys;
	NAMEIN_PARAM   *NameInParam;
}TEST_PROC_WORK;


//---------------------------------------------------------------------------------------------
// 関数プロトタイプ
//---------------------------------------------------------------------------------------------
static void DebugMenuExit(GF_BGL_INI *ini);
static void DebugMenuExitSub( TCB_PTR _tcb );
static void DebugMoriMenuMain( TCB_PTR _tcb, void * work );
static void MainBmpListCB1( BMPLIST_WORK * work, u32 param, u8 mode );
static void MainBmpListCB2( BMPLIST_WORK * work, u32 param, u8 y );
void DebugMoriMenuInit(GF_BGL_INI * ini, FIELDSYS_WORK *fsys);

static void TestWorldTrade_Call( TCB_PTR tcb, void* work );
void DebugWorldTradeFuncInit(GF_BGL_INI * ini, FIELDSYS_WORK *fsys);
static TEST_PROC_WORK *CommonBTowerSetUp( GF_BGL_INI * ini, FIELDSYS_WORK *fsys );
static void DebugWifiBTowerFuncInit0( GF_BGL_INI * ini, FIELDSYS_WORK *fsys );
static void DebugWifiBTowerFuncInit1( GF_BGL_INI * ini, FIELDSYS_WORK *fsys );
static void DebugWifiBTowerFuncInit2( GF_BGL_INI * ini, FIELDSYS_WORK *fsys );
static void TestWifiBTower_Call( TCB_PTR tcb, void* work );

static void DebugSodateyaTamgoSet( GF_BGL_INI * ini, FIELDSYS_WORK *fsys );
static void DebugTamagoFuka( GF_BGL_INI * ini, FIELDSYS_WORK *fsys );
static void DebugSodateya1000Po( GF_BGL_INI * ini, FIELDSYS_WORK *fsys );
static void DebugSodateya10000Po( GF_BGL_INI * ini, FIELDSYS_WORK *fsys );
static void DebugFriendListClear( GF_BGL_INI * ini, FIELDSYS_WORK *fsys );
static void DebugLongName( GF_BGL_INI * ini, FIELDSYS_WORK *fsys );



static int SamplingDataFab( s8 *adr, int size, int divid );





//void DebugMicFuncInit(GF_BGL_INI *ini, FIELDSYS_WORK *fsys);
//void DebugMicFuncMain(TCB_PTR tcb, void *work);

void TestNameIn_Call( TCB_PTR tcb, void* work );
void DebugNameInFuncInit(GF_BGL_INI * ini, FIELDSYS_WORK *fsys);
void DebugTradeListFuncInit(GF_BGL_INI * ini, FIELDSYS_WORK *fsys);




//--------------------------------------------------------------------------------------------
// デバッグメニュー用定義
//--------------------------------------------------------------------------------------------
#define DMORI_BMPMENU_NUM	( 10 )

static const BMPLIST_HEADER d_menu_list_h = {
	NULL,
	MainBmpListCB1,			// カーソル移動ごとのコールバック関数
	MainBmpListCB2,			// 一列表示ごとのコールバック関数
	NULL,
	DMORI_BMPMENU_NUM,		// リスト項目数
	10,						// 表示最大項目数
	0,						// ラベル表示Ｘ座標
	8,						// 項目表示Ｘ座標
	0,						// カーソル表示Ｘ座標
	0,						// 表示Ｙ座標
	FBMP_COL_BLACK,			// 文字色
	FBMP_COL_WHITE,			// 背景色
	FBMP_COL_BLK_SDW,		// 文字影色
	0,						// 文字間隔Ｘ
	16,						// 文字間隔Ｙ
	BMPLIST_LRKEY_SKIP,		// ページスキップタイプ
	POKE_SYSTEM,			// 文字指定(本来は u8 だけど、そんなに作らないと思うので)
	0						// ＢＧカーソル(allow)表示フラグ(0:ON,1:OFF)
};



typedef void (*bglFunc)(GF_BGL_INI *ini, FIELDSYS_WORK* fsys);	// 関数ポインタ型

static const u8 datadata[4]={0x77,0x77,0x77,0x73,};
static const STRCODE testname[]={h_T__,h_e__,h_s__,h_t__,h_N__,h_a__,h_m__,h_e__,h_A__,h_B__,EOM_,};
static const STRCODE parentname[]={h_T__,h_e__,h_s__,h_t__,h_N__,h_a__,h_m__,EOM_,};


//==============================================================================
/**
 * デバッグメニュー初期化関数（fld_debug.cから呼ばれます)
 *
 * @param   none		
 *
 * @retval  none		
 */
//==============================================================================
void DebugMoriMenuInit(GF_BGL_INI * ini, FIELDSYS_WORK *fsys)
{
	BMPLIST_HEADER	list_h;
	u8 work[4];
	u8 outwork[4];

	// タスク登録＆ワークポインタ取得
	u32 * wk             = (u32 *)TCB_GetWork( PMDS_taskAdd( DebugMoriMenuMain, sizeof(DEBUG_MORI_WORK), 0, HEAPID_BASE_DEBUG ) );
	DEBUG_MORI_WORK *dmw = (DEBUG_MORI_WORK*)wk;

	// BMP_WIN構造体確保
	GF_BGL_BMPWIN *win = GF_BGL_BmpWinAllocGet( HEAPID_BASE_DEBUG, 1 );



	// 文字列データ読み込み準備
	dmw->man = MSGMAN_Create( MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_debug_mori_dat, HEAPID_BASE_DEBUG );


	// BMP_WIN登録
	GF_BGL_BmpWinAdd( ini, win, FLD_MBGFRM_FONT, 1, 1, 15, 20, FLD_SYSFONT_PAL, 1 );

	// BMP_WIN構造体のポインタをタスクワークに保存
	wk[ WK_WIN_INDEX ] = (u32)win;


	dmw->ld = BMP_MENULIST_Create( DMORI_BMPMENU_NUM, HEAPID_WORLD );
//	BMP_MENULIST_AddArchiveString( dmw->ld, dmw->man, menu_msg00, (u32)DebugMenuCallConnectList );
	BMP_MENULIST_AddArchiveString( dmw->ld, dmw->man, menu_msg01, (u32)DebugLongName );
	BMP_MENULIST_AddArchiveString( dmw->ld, dmw->man, menu_msg02, (u32)DebugFriendListClear );
	BMP_MENULIST_AddArchiveString( dmw->ld, dmw->man, menu_msg03, (u32)DebugMenuExit );
	BMP_MENULIST_AddArchiveString( dmw->ld, dmw->man, menu_msg04, (u32)DebugNameInFuncInit );
	BMP_MENULIST_AddArchiveString( dmw->ld, dmw->man, menu_msg05, (u32)DebugTradeListFuncInit );
	BMP_MENULIST_AddArchiveString( dmw->ld, dmw->man, menu_msg19, (u32)DebugWorldTradeFuncInit );
//	BMP_MENULIST_AddArchiveString( dmw->ld, dmw->man, menu_msg20, (u32)DebugWifiBTowerFuncInit0 );
	BMP_MENULIST_AddArchiveString( dmw->ld, dmw->man, menu_msg21, (u32)DebugSodateya1000Po );
	BMP_MENULIST_AddArchiveString( dmw->ld, dmw->man, menu_msg22, (u32)DebugSodateya10000Po );
	BMP_MENULIST_AddArchiveString( dmw->ld, dmw->man, menu_msg23, (u32)DebugSodateyaTamgoSet );
	BMP_MENULIST_AddArchiveString( dmw->ld, dmw->man, menu_msg24, (u32)DebugTamagoFuka );


	// BMP_LIST構造体をセット
	list_h      = d_menu_list_h;
	list_h.win  = win;
	list_h.list = dmw->ld;


	wk[ WK_LIST_ID ]    = (u32)BmpListSet( &list_h, 0, 0 ,HEAPID_BASE_DEBUG);
	wk[ WK_GF_BGL_INI ] = (u32)ini;			// fieldsys->bglの保存
	wk[ WK_FIELDSYS ]   = (u32)fsys;		// fieldsysの保存

	// BMP表示開始
	GF_BGL_BmpWinOn( win );


	
	MSGMAN_Delete( dmw->man );

	// タスクシーケンス用変数の初期化
	wk[ WK_SEQ ] = 0;


	OS_Printf( " parent %d -> %d\n", MONSNO_MATADOGASU, PokeSearchChild( MONSNO_MATADOGASU ));
	OS_Printf( " parent %d -> %d\n", MONSNO_RAITYUU, PokeSearchChild( MONSNO_RAITYUU ));
	OS_Printf( " parent %d -> %d\n", MONSNO_PIKATYUU, PokeSearchChild( MONSNO_PIKATYUU ));
	OS_Printf( " parent %d -> %d\n", MONSNO_HANTEERU, PokeSearchChild( MONSNO_HANTEERU ));





}

#if 0

static int longitem[10][2];
static int sortstack[100];

s32 longItemCompFunc( void *elem1, void *elem2 );
static void LongNameResearch(void);

static void LongNameResearch(void)
{
	// 長いアイテム名を調べるブロック
	{
		int i;
		STRBUF *strbuf = STRBUF_Create( 20, HEAPID_BASE_DEBUG );
		int length;


		for(i=0;i<10;i++){
			longitem[i][0] = 0;
			longitem[i][1] = 0;
		}

		// 全てのアイテム名文字列を取得し長さを調べる
		for(i=1;i<ITEM_DATA_MAX;i++){
			
			GetItemName( strbuf, i, HEAPID_BASE_DEBUG );
			length = FontProc_GetPrintStrWidth( FONT_TALK, strbuf, 0 );
			
			longitem[9][0] = i;
			longitem[9][1] = length;

			// 配列の10番目に挿入し、ソートしてトップ10を決める
			MATH_QSort( (void*)longitem, 
                    10, 
                    8, 
                    longItemCompFunc, 
                    sortstack );

		}

		for(i=0;i<10;i++){
			OS_Printf("%02d: itemno = %d,  length = %d\n", i, longitem[i][0], longitem[i][1]);
		}
	}
}

// ソート用の比較関数
s32 longItemCompFunc( void *elem1, void *elem2 )
{
	int *item1, *item2;
	item1 = (int*)elem1;
	item2 = (int*)elem2;
	
	if(item1[1] == item2[1]){
		return 0;
	}
	if(item1[1] < item2[1]){
		return 1;
	}
	return -1;
}
#endif



static void MainBmpListCB1( BMPLIST_WORK * work, u32 param, u8 mode )
{
}
static void MainBmpListCB2( BMPLIST_WORK * work, u32 param, u8 y )
{
}

//------------------------------------------------------------------
/**
 * デバッグメニューBmpList解放
 *
 * @param   wk		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void DebugMoriBmpMenuExit( u32 * wk )
{
	BMPLIST_WORK    *list = (BMPLIST_WORK*)wk[WK_LIST_ID];
	DEBUG_MORI_WORK *dmw  = (DEBUG_MORI_WORK*)wk;

	// BMP_LIST解放
	BmpListExit( list, NULL, NULL );
	BMP_MENULIST_Delete( dmw->ld );

	// BMP_WIN表示OFF
	GF_BGL_BmpWinOff( (GF_BGL_BMPWIN*)wk[WK_WIN_INDEX] );

	// BMP_WIN領域削除
	GF_BGL_BmpWinDel( (GF_BGL_BMPWIN*)wk[WK_WIN_INDEX] );
}


static u16 *ChildList;

//------------------------------------------------------------------
/**
 * デバッグメニュー解放処理
 *
 * @param   tcb		
 *
 * @retval  none	
 */
//------------------------------------------------------------------
static void DebugMenuExitSub( TCB_PTR tcb )
{
	u32 *wk = (u32*)TCB_GetWork(tcb);
	u16 result;
	int different=0,i;
	
	// BMPLIST/WIN解放
	DebugMoriBmpMenuExit( wk );

	// タスク消去
	PMDS_taskDel( tcb );

	// フィールド処理ポーズ状態から復帰
	FieldSystemProc_SeqHoldEnd();
}




//------------------------------------------------------------------
/**
 * 呼び出し
 *
 * @param   none		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void DebugMenuExit( GF_BGL_INI *ini )
{
//	EncountEffectStart(1,NULL,NULL);
	FieldSystemProc_SeqHoldEnd();

}



//------------------------------------------------------------------
/**
 * デバッグメニューメイン
 *
 * @param   _tcb		
 * @param   work		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void DebugMoriMenuMain( TCB_PTR _tcb, void * work )
{
	u32 * wk = (u32 *)work;
	u32	ret;

	switch( wk[ WK_SEQ ] ){
	case 0:
		ret = BmpListMain( (BMPLIST_WORK*)wk[WK_LIST_ID] );

		switch( ret ){
		case BMPLIST_NULL:
			break;
		case BMPLIST_CANCEL:
//			NNS_GfdDumpLnkTexVramManager();
//			NNS_GfdDumpLnkPlttVramManager();
			OS_Printf("wbppokemon size = %d\n",sizeof(WPBPokemonInfo));
			DebugMenuExitSub( _tcb );

			OS_Printf( "%dの子供は %d\n",185,PokeSearchChild(185));

			break;
		default:
			wk[WK_LIST_RET] = ret;
			wk[WK_SEQ]++;
		}
		break;
	case 1:
		{
			bglFunc func = (bglFunc)wk[WK_LIST_RET];

			DebugMoriBmpMenuExit( wk );
			PMDS_taskDel( _tcb );
			func((GF_BGL_INI*)wk[WK_GF_BGL_INI], (FIELDSYS_WORK*)wk[WK_FIELDSYS]);
		}
	}
}



#if 0

//---------------------------------------------------------------------------------------
// 接続リスト処理テスト
//---------------------------------------------------------------------------------------


typedef struct{
	u8  name[10+1];
	u32 id;
	u8  sex;
	u16 time;
}CONNECT_MEMBER_ONE;


typedef struct{
	u32 wk[16];
	CONNECT_MEMBER_ONE recv[32];
	CONNECT_MEMBER_ONE put[32];

	u8 				*sWmBuffer;
	u8				*wpbBuf;
//	WPBBuf  		wpbBuf;
	WPBPokemonInfo	SendWPBInfo;
	WPBPokemonInfo	RecvWPBInfo;
	WPBPokemonInfo	StockWPBInfo[8];
	int				StockNum;
	int				OldStockNum;
	u16				*UTF16Table;
	u16				surechigai_str[32];
	STRBUF			*recv_msg;

}CONNECT_MEMBER_WORK;

//static u8 			sWmBuffer[WM_SYSTEM_BUF_SIZE] 	ATTRIBUTE_ALIGN(32);
//static WPBBuf  		wpbBuf  						ATTRIBUTE_ALIGN(32);

static CONNECT_MEMBER_WORK *pcmw = NULL;



//---------------------------------------------------------------------------------------------
// 関数プロトタイプ
//---------------------------------------------------------------------------------------------
void ConnectListMain(TCB_PTR tcb, void *work);
void ConnectListLineCB(BMPLIST_WORK * work,u32 param,u8 y);

//--------------------------------------------------------------------------------------------
// デバッグメニュー用定義
//--------------------------------------------------------------------------------------------



static const BMPLIST_HEADER connect_list_h = {
	NULL,			// 表示文字データポインタ
	MainBmpListCB1,			// カーソル移動ごとのコールバック関数
	ConnectListLineCB,		// 一列表示ごとのコールバック関数
	NULL,
	10,	// リスト項目数
	7,						// 表示最大項目数
	0,						// ラベル表示Ｘ座標
	8,						// 項目表示Ｘ座標
	0,						// カーソル表示Ｘ座標
	0,						// 表示Ｙ座標
	FBMP_COL_BLACK,			//文字色
	FBMP_COL_WHITE,			//背景色
	FBMP_COL_BLK_SDW,		//文字影色
	0,						// 文字間隔Ｘ
	16,						// 文字間隔Ｙ
	BMPLIST_LRKEY_SKIP,		// ページスキップタイプ
	POKE_SYSTEM,				// 文字指定(本来は u8 だけど、そんなに作らないと思うので)
	0						// ＢＧカーソル(allow)表示フラグ(0:ON,1:OFF)
};


//==============================================================================
/**
 * 接続テスト画面初期化
 *
 * @param   ini		
 *
 * @retval  none		
 */
//==============================================================================
static void DebugMenuCallConnectList(GF_BGL_INI *ini, FIELDSYS_WORK *fsys)
{
	BMPLIST_HEADER	list_h;

	// タスク登録＆ワークポインタ取得
	u32 * wk = (u32 *)TCB_GetWork( PMDS_taskAdd( ConnectListMain, sizeof(CONNECT_MEMBER_WORK), 0, HEAPID_BASE_DEBUG ) );
	CONNECT_MEMBER_WORK *cmw = (CONNECT_MEMBER_WORK *)wk;

	// BMP_WIN構造体確保
//	GF_BGL_BMPWIN *win =  GF_BGL_BmpWinAllocGet( HEAPID_BASE_DEBUG, 1 );
	// BMP_WIN構造体確保
	GF_BGL_BMPWIN *talkwin =  GF_BGL_BmpWinAllocGet( HEAPID_BASE_DEBUG, 2 );

	// タスクシーケンス初期化
	wk[ WK_SEQ ]        = 0;

	// BMP_WIN登録
//	GF_BGL_BmpWinAdd( ini , win,FLD_MBGFRM_FONT, 1, 1, 20, 10, FLD_SYSFONT_PAL, 1 );
//	wk[ WK_WIN_INDEX ]  = (u32)win;

	// BMP_LIST登録
//	list_h              = connect_list_h;
//	list_h.win          = win;
//	wk[ WK_LIST_ID ]    = (u32)BmpListSet( &list_h, 0, 0,HEAPID_BASE_DEBUG );
//	wk[ WK_GF_BGL_INI ] = (u32)ini;					//FieldSys->bglの保存


	// BMP_WIN構造体のポインタをタスクワークに保存
	GF_BGL_BmpWinAdd( ini, talkwin, FLD_MBGFRM_FONT, 
				FLD_MSG_WIN_PX, FLD_MSG_WIN_PY, FLD_MSG_WIN_SX, FLD_MSG_WIN_SY, FLD_SYSFONT_PAL, FLD_MSG_WIN_CGX );
	wk[ WK_TALK_INDEX ] = (u32)talkwin;
	FieldMsgPrintInit(PALTYPE_SUB_BG, MSG_PRINT_NO_INIT);				// サブ画面VRAMにフォントとパレットを転送
//	FieldTalkWinPut( talkwin );			// サブ画面メッセージウインドウ表示開始

	// BMP_WIN表示ON
//	GF_BGL_BmpWinOn( win );

	cmw->UTF16Table = sys_LoadFile(HEAPID_BASE_DEBUG, "data/UTF16.dat");
	cmw->StockNum    = 0;
	cmw->OldStockNum = 0;

	{
		SODATEYA_WORK *sodateya = SaveData_Get( fsys->savedata, GMDATA_ID_SODATEYA);
		
		PokeMakeTamago( sodateya );
//		SodateyaPlusWalk( sodateya, 1000);
	}

}


static const char *errcode[]={
	"WPB_STATECODE_START",        /* すれ違い待機開始 */
	"WPB_STATECODE_PARENT_FOUND", /* 親機を発見した */
	"WPB_STATECODE_CONNECTED",    /* 接続完了 */
	"WPB_STATECODE_EXCHANGED",    /* データ交換完了 */
	"WPB_STATECODE_DISCONNECTED", /* 切断通知 */
	"WPB_STATECODE_END",          /* すれ違い待機終了 */

};

static u16 gameinfo[2]={0,0};
static u16 testnickname[]={GE_,bou_,HU_,RI_,EOM_};
static u16 surechigairesult[]={to_,spc_,su_,re_,ti_,ga_,ttu_,ta_,EOM_};
#define TEST_GGID	0x135

// ゲーム間共通情報

static const WPBPokemonInfo TestWPBPokeInfo = {
	4,
	-1,
	-1,
	-1,
	-1,
	{0x0070, 0x006F, 0x006B, 0x0065, 0x006D, 0x006F, 0x006E, 0x0044, 0x0050,  0x0000,},	// pokemonDP
	{0,},
	{0,},
	{0,},
	1,
	0,
	0,
	{0xFF71, 0xFF77, 0xFF84, 0x0000,}, //アキト
	4,
	{0x305F, 0x3044, 0x3078, 0x3093, 0x3060, 0x3088, 0x306D, 0x306D, 0x306D,0x0000,}, // 大変だよね
	9,
};
#if 0
typedef struct WPBPokemonInfo {
	u32 version;        // ポケモンDSソフトとしてのID番号
	u32 tryTime;        // 今回すれ違うまでにかかった時間 (秒) (不明は -1)
	u32 tryCount;       // 現在までのすれ違い試行回数 (不明は -1)
	u32 successCount;   // 現在までのすれ違い成功回数 (不明は -1)
	u32 totalTime;      // 現在までの総すれ違い試行時間 (秒) (不明は -1)
	u16 gameName[128];  // ゲーム名 (UTF-16LE)
	u8  image[32*32/2]; // アイコンデータ
	u8  pltt[16*2];     // アイコンパレット
	u8  macAddress[WM_SIZE_BSSID]; // 自分のmacAddress
	u8  present;        // プレゼント
	u8  favoriteColor;  // お気に入りの色 ( 0 ～ 15 )
	u16 sex_birth;      // 性別、誕生日、年齢情報
	u16 nickName[ 10 ]; // ニックネーム (UTF16)
	u16 nickNameLength; // ニックネーム文字数( 0 ～ 10 )
	u16 comment[ 39 ];  // コメント (UTF16)
	u16 commentLength;  // コメント文字数( 0 ～ 39 )
} WPBPokemonInfo;

#endif

static void WpbSetUp(CONNECT_MEMBER_WORK *cmw);
static void WpbInit(CONNECT_MEMBER_WORK *cmw);
static int  ReleaseWpbWork(CONNECT_MEMBER_WORK *cmw);

void WpbCallBack(WPBCallback *arg);

//------------------------------------------------------------------
/**
 * sys_AllocMemoryから貰った値を32バイトアライメントのアドレスに補正する
 *
 * @param   adr		Allocで取得したアドレス（実際のサイズより32バイト多く確保しておく)
 *
 * @retval  u8*		32バイトアライメントに修正したアドレス
 */
//------------------------------------------------------------------
static u8* GetAlignment32Adr(u8 *adr)
{
	u32 work = (u32)adr;
	if((work&0x0000003f)==0){
		return (u8*)work;
	}

	return (u8*)work + 32-(work%32);

}

static void WpbSetUp(CONNECT_MEMBER_WORK *cmw)
{
	cmw->sWmBuffer = sys_AllocMemory( HEAPID_BASE_DEBUG, WM_SYSTEM_BUF_SIZE+64 );
	if(cmw->sWmBuffer==NULL){
		OS_Printf("cmw->sWmBufferが確保できていない\n");
	}
	// イクニューモン転送
	CommVRAMDInitialize();

	pcmw = cmw;
}
#define UTF16_TABLE_MAX	( 249 )

static void SetPokeWord2UTF16(u16 *des, const u16 *src, const u16 *UTF16)
{
	int i=0;
	while(src[i]!=EOM_){
		des[i] = UTF16[src[i]];
		i++;
	}
}

static void SetUTF162PokeWord(u16 *des, const u16 *src, const u16 *UTF16)
{
	int i=0,r;
	while(src[i]!=EOM_){
		for(r=0;r<UTF16_TABLE_MAX;r++){
			if(UTF16[r]==src[i]){
				des[i] = r;
				break;
			}
		}
		i++;
	}
}


static void WpbInit(CONNECT_MEMBER_WORK *cmw)
{
	int code;
	u8 *sWmBuffer_a,*wpbBuf_a;

	// 通信初期化
	sWmBuffer_a = GetAlignment32Adr(cmw->sWmBuffer);
	code = WM_Init( sWmBuffer_a, 2 );

	OS_Printf("errcode = %d\n",code);

	cmw->wpbBuf = sys_AllocMemory( HEAPID_BASE_DEBUG, sizeof(WPBBuf)+64 );
	if(cmw->wpbBuf==NULL){
		OS_Printf("cmw->wpbBufが確保できていない\n");
	}
	wpbBuf_a = GetAlignment32Adr(cmw->wpbBuf);
	WPB_SetBuffer((WPBBuf*)wpbBuf_a);

	WPB_SetCallback(WpbCallBack);

	cmw->SendWPBInfo = TestWPBPokeInfo;
	OS_GetMacAddress(cmw->SendWPBInfo.macAddress);
	SetPokeWord2UTF16(cmw->SendWPBInfo.nickName,testnickname,cmw->UTF16Table);
	
	WPB_SetGameInfo(gameinfo, sizeof(gameinfo), TEST_GGID);


	if(WPB_Start()==WM_ERRCODE_INVALID_PARAM){
		OS_Printf("関数に渡したパラメータが不正\n");
	}
}

static int ReleaseWpbWork(CONNECT_MEMBER_WORK *cmw)
{
//	if(WPB_Finished()){
	if(WPB_End()==WM_ERRCODE_SUCCESS){
		sys_FreeMemory(HEAPID_BASE_DEBUG, cmw->wpbBuf);
		sys_FreeMemory(HEAPID_BASE_DEBUG, cmw->sWmBuffer);

	}else{
		return 0;
	}
//	}else{
//		return 0;
//	}

//	WM_Finish();

	return 1;
}


static void WpbCallBack(WPBCallback *arg)
{
	switch(arg->state){
	case WPB_STATECODE_PARENT_FOUND:

		arg->send_ptr  = &pcmw->SendWPBInfo;
		arg->send_size = sizeof(WPBPokemonInfo);
		arg->recv_ptr  = &pcmw->RecvWPBInfo;
		arg->recv_size = sizeof(WPBPokemonInfo);
		arg->bssDesc   = WPB_TestParent(arg->bssDesc, arg->bssDescCount, TEST_GGID);
		break;
	case WPB_STATECODE_CONNECTED:
		break;
	case WPB_STATECODE_EXCHANGED:
		pcmw->StockWPBInfo[pcmw->StockNum] = pcmw->RecvWPBInfo;
		if(++pcmw->StockNum==5){
			pcmw->StockNum = 0;
		}
		break;
	}

	OS_Printf("----------すれちがいstate = %s\n",errcode[arg->state]);
}


static const u16 teststr[]={TE_,SU_,TO_,de_,su_,EOM_};


//==============================================================================
/**
 * 接続画面テストメイン
 *
 * @param   tcb		
 * @param   work		
 *
 * @retval  none		
 */
//==============================================================================
void ConnectListMain(TCB_PTR tcb, void *work)
{
	u32	ret;
	CONNECT_MEMBER_WORK *cmw = (CONNECT_MEMBER_WORK *)work;


	switch( cmw->wk[ WK_SEQ ] ){
	case 0:		// 通信初期化
		WpbSetUp(cmw);
		cmw->wk[WK_SEQ]++;
		break;
	case 1:
		if(CommIsVRAMDInitialize()){
			WpbInit(cmw);
			cmw->wk[WK_SEQ]++;
		}
		break;
	
	case 2:
		if((sys.trg & PAD_BUTTON_B) || (sys.trg & PAD_BUTTON_A)){
			cmw->wk[WK_SEQ]++;
		}
#if 0
		ret = BmpListMain( (BMPLIST_WORK*)cmw->wk[WK_LIST_ID] );

		switch( ret ){
		case BMPLIST_NULL:
			break;
		case BMPLIST_CANCEL:
//			ReleaseWpbWork(cmw);
//			DebugMenuExitSub( tcb );
			cmw->wk[WK_SEQ]++;
			break;
		default:
			cmw->wk[WK_LIST_RET] = ret;
			cmw->wk[WK_SEQ]++;
		}
#endif
		break;
	case 3:
		if(ReleaseWpbWork(cmw)){
			cmw->wk[WK_SEQ]++;
		}
			
		break;
	case 4:
		if(FldTalkMsgEndCheck( cmw->wk[WK_MES_INDEX] )){
			BmpTalkWinClear(  (GF_BGL_BMPWIN*)cmw->wk[ WK_TALK_INDEX ], WINDOW_TRANS_OFF );
			GF_BGL_BmpWinOff( (GF_BGL_BMPWIN*)cmw->wk[ WK_TALK_INDEX ] );
			GF_BGL_BmpWinDel( (GF_BGL_BMPWIN*)cmw->wk[ WK_TALK_INDEX ] );
			cmw->wk[WK_SEQ]++;
		}
		break;
		
	case 5:
		WVR_TerminateAsync( NULL , NULL);
		sys_FreeMemoryEz( cmw->UTF16Table );
//		DebugMenuExitSub( tcb );
		// タスク消去
		PMDS_taskDel( tcb );
		// フィールド処理ポーズ状態から復帰
		FieldSystemProc_SeqHoldEnd();
		break;
	}
	
	if(cmw->wk[ WK_SEQ ]!=2){
		return;
	}
	
	// すれ違い通信でデータを受信したらウインドウに文字列が表示される
	switch(cmw->wk[WK_MES_SEQ]){
	case 0:
		if(cmw->StockNum!=cmw->OldStockNum){
			GF_BGL_BmpWinFill( (GF_BGL_BMPWIN*)pcmw->wk[WK_TALK_INDEX], 0x0f0f, 0, 0, FLD_MSG_WIN_SX*8, FLD_MSG_WIN_SY*8 );
			SetUTF162PokeWord(cmw->surechigai_str,cmw->StockWPBInfo[pcmw->StockNum].nickName,cmw->UTF16Table);
			PM_strcat(cmw->surechigai_str,surechigairesult);
			if(++pcmw->OldStockNum==5){
				pcmw->OldStockNum = 0;
			}
			cmw->wk[WK_MES_SEQ]++;
		}
		break;
	case 1:
		cmw->recv_msg         = STRBUF_Create(20,HEAPID_WORLD);
		STRBUF_SetStringCode( cmw->recv_msg, teststr );
		{
			CONFIG *cfg = SaveData_GetConfig(((FIELDSYS_WORK*)(cmw->wk[WK_FIELDSYS]))->savedata);
			cmw->wk[WK_MES_INDEX] = FieldTalkMsgStart( (GF_BGL_BMPWIN*)cmw->wk[WK_TALK_INDEX], cmw->recv_msg, cfg, 0);
		}
													
		cmw->wk[WK_MES_SEQ]++;
		break;
	case 2:
		if(FldTalkMsgEndCheck( cmw->wk[WK_MES_INDEX] )){
			STRBUF_Delete(cmw->recv_msg);
			cmw->wk[WK_MES_SEQ]++;
		}
		break;
	case 3:
		if(++cmw->wk[WK_MES_WAIT]>30){
			GF_BGL_BmpWinFill( (GF_BGL_BMPWIN*)pcmw->wk[WK_TALK_INDEX], 0x0f0f, 0, 0, FLD_MSG_WIN_SX*8, FLD_MSG_WIN_SY*8 );
			cmw->wk[WK_MES_WAIT] = 0;
			cmw->wk[WK_MES_SEQ]  = 0;
		}
		break;
	}
}

void ConnectListLineCB(BMPLIST_WORK * work,u32 param,u8 y)
{
	
}
#endif


#if	0
//--------------------------------------------------------------------------------------------
// デバッグメニュー用定義
//--------------------------------------------------------------------------------------------

static const BMPLIST_HEADER micfunc_list_h = {
	NULL,			// 表示文字データポインタ
	MainBmpListCB1,			// カーソル移動ごとのコールバック関数
	ConnectListLineCB,		// 一列表示ごとのコールバック関数
	NULL,
	10,	// リスト項目数
	10,						// 表示最大項目数
	0,						// ラベル表示Ｘ座標
	8,						// 項目表示Ｘ座標
	0,						// カーソル表示Ｘ座標
	0,						// 表示Ｙ座標
	FBMP_COL_BLACK,			//文字色
	FBMP_COL_WHITE,			//背景色
	FBMP_COL_BLK_SDW,		//文字影色
	0,						// 文字間隔Ｘ
	16,						// 文字間隔Ｙ
	BMPLIST_LRKEY_SKIP,		// ページスキップタイプ
	POKE_SYSTEM,				// 文字指定(本来は u8 だけど、そんなに作らないと思うので)
	0						// ＢＧカーソル(allow)表示フラグ(0:ON,1:OFF)
};

static const VOamAnm WM_IconAnim0[]={
	{512-16,   20},
	{512-16+4, 20},
	{512-16+8, 20},
	{512-16+12,20},
	{0xffff,0}
};

static const VOamAnm WM_IconAnim1[]={
	{512-16,   20},
	{0xffff,0}
};
static const VOamAnm WM_IconAnim2[]={
	{512-16+4,   20},
	{0xffff,0}
};
static const VOamAnm WM_IconAnim3[]={
	{512-16+8,   20},
	{0xffff,0}
};
static const VOamAnm WM_IconAnim4[]={
	{512-16+12,   20},
	{0xffff,0}
};

static const VOamAnm * WM_IconAnimTbl[]={
	WM_IconAnim0,
	WM_IconAnim1,
	WM_IconAnim2,
	WM_IconAnim3,
	WM_IconAnim4,
};


//==============================================================================
/**
 * マイクテスト用の初期化
 *
 * @param   ini		GF_BGL_INIのポインタ
 *
 * @retval  none		
 */
//==============================================================================
void DebugMicFuncInit(GF_BGL_INI *ini, FIELDSYS_WORK *fsys)
{
	BMPLIST_HEADER	  list_h;
	MSGDATA_MANAGER   *man;

	// タスク登録＆ワークポインタ取得
	u32 *wk               = (u32 *)TCB_GetWork( PMDS_taskAdd( DebugMicFuncMain, sizeof(CONNECT_MEMBER_WORK), 0, HEAPID_BASE_DEBUG ) );
	DEBUG_MORI_WORK *dmw  = (DEBUG_MORI_WORK *)wk;

	// BMP_WIN構造体確保
	GF_BGL_BMPWIN *win =  GF_BGL_BmpWinAllocGet( HEAPID_BASE_DEBUG, 1 );

	// タスクシーケンス初期化
	wk[ WK_SEQ ]        = 0;

	// BMP_WIN登録
	GF_BGL_BmpWinAdd( ini ,win,FLD_MBGFRM_FONT, 1, 1, 10, 20, FLD_SYSFONT_PAL, 1 );

	// BMP_WIN構造体のポインタをタスクワークの保存
	wk[ WK_WIN_INDEX ]  = (u32)win;

	// 文字列データ読み込み準備
	man = MSGMAN_Create( MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_debug_mori_dat, HEAPID_BASE_DEBUG );

	dmw->ld = BMP_MENULIST_Create( 10, HEAPID_BASE_DEBUG );
	BMP_MENULIST_AddArchiveString( dmw->ld, man, menu_msg06, (u32)1 );
	BMP_MENULIST_AddArchiveString( dmw->ld, man, menu_msg07, (u32)2 );
	BMP_MENULIST_AddArchiveString( dmw->ld, man, menu_msg08, (u32)3 );
	BMP_MENULIST_AddArchiveString( dmw->ld, man, menu_msg09, (u32)4 );
	BMP_MENULIST_AddArchiveString( dmw->ld, man, menu_msg10, (u32)5 );
	BMP_MENULIST_AddArchiveString( dmw->ld, man, menu_msg11, (u32)6 );
	BMP_MENULIST_AddArchiveString( dmw->ld, man, menu_msg12, (u32)7 );
	BMP_MENULIST_AddArchiveString( dmw->ld, man, menu_msg13, (u32)8 );
	BMP_MENULIST_AddArchiveString( dmw->ld, man, menu_msg14, (u32)10);
	BMP_MENULIST_AddArchiveString( dmw->ld, man, menu_msg15, (u32)11);

	MSGMAN_Delete(man);
	
	// BMP_LIST登録
	list_h              = micfunc_list_h;
	list_h.win          = win;
	list_h.list			= dmw->ld;
	wk[ WK_LIST_ID ]    = (u32)BmpListSet( &list_h, 0, 0, HEAPID_BASE_DEBUG);
	wk[ WK_GF_BGL_INI ] = (u32)ini;					//FieldSys->bglの保存
	wk[ WK_MIC_PARAM  ] = MIC_SAMPLING_RATE_8K;
	wk[ WK_FIELDSYS   ] = (u32)fsys;

	// BMP_WIN表示ＯＮ
	GF_BGL_BmpWinOn( win );

	// 波形再生用チャンネルを確保する
	Snd_WaveOutAllocChannel( WAVEOUT_CH_NORMAL );

	wk[ WK_WM_ICON ] = (u32)AddWirelessIconOAM(0,HEAPID_BASE_DEBUG,240,0,0,WM_IconAnimTbl);

	Snd_Stop();
}

#define MIC_PLAY_TIME	(2)	// 2秒

//------------------------------------------------------------------
/**
 * マイク設定と録音開始
 *
 * @param   rate	サンプリングレート(8Khzなら8000)
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void SamplingStart(int rate)
{
	MICAutoParam		mic_param;
	mic_param.type   = MIC_SAMPLING_TYPE_SIGNED_8BIT;	// サンプリング種別
    mic_param.buffer = Snd_GetDebugWaveBufAdrs();       // 結果格納バッファへのポインタ 
    mic_param.size   = rate*MIC_PLAY_TIME;      					// バッファサイズ
	if((mic_param.size&0x1f)!=0){
		mic_param.size &= 0xffffffe0;
	}
    mic_param.rate   = HW_CPU_CLOCK_ARM7 /rate;         // サンプリング周期( ARM7のクロック数 )
    mic_param.loop_enable = FALSE;                  	// バッファフル時のループ可否
    mic_param.full_callback = NULL;     			    // バッファフル時のコールバック
    mic_param.full_arg      = NULL;                     // 上記コールバックに指定する引数

	Snd_MicStartAutoSampling(&mic_param);

}

//------------------------------------------------------------------
/**
 * $brief   音声データを指定の値で割って、また元に戻す
 *          例えば8bitデータを16で割って音声に余り変わりが無いのであれば
 *          半分の4bitに下げて記録しても良いことになる
 *
 * @param   adr		
 * @param   size		
 * @param   divid		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int SamplingDataFab( s8 *adr, int size, int divid )
{
	int i,r=0;
	for(i=0;i<size;i++){
		adr[i] = (adr[i]/divid);
		r     += adr[i];
		adr[i] = adr[i]*divid;
	}
	return r;
}


static void SamplingDataSearchDiff( s8 *adr, int size, int diff )
{
	int i,w;
	
	for(i=0;i<size;i++){
		if(i!=0){
			if( adr[i] > adr[i-1]){
				w = adr[i]-adr[i-1];
			}else{
				w = adr[i-1]-adr[i];
			}
			if(w>diff){
				OS_Printf("差が%dよりおおきい  pos=%d, 差=%d\n",diff,i,w);
			}
		}
	}
}

//==============================================================================
/**
 * マイク処理のBMP_LISTメイン巻数
 *
 * @param   tcb		タスク
 * @param   work	ワークポインタ
 *
 * @retval  none	
 */
//==============================================================================
void DebugMicFuncMain(TCB_PTR tcb, void *work)
{
	u32	ret;
	CONNECT_MEMBER_WORK *cmw = (CONNECT_MEMBER_WORK *)work;
	

	switch( cmw->wk[ WK_SEQ ] ){
	case 0:
		// BMPLISTメイン処理
		ret = BmpListMain( (BMPLIST_WORK*)cmw->wk[WK_LIST_ID] );
	switch( ret ){
		case 1:		// 録音 8Khz
			cmw->wk[WK_MIC_PARAM] = 8000;
			SamplingStart(cmw->wk[WK_MIC_PARAM]);
			break;
		case 2:		// 録音 4Khz
			cmw->wk[WK_MIC_PARAM] = 4000;
			SamplingStart(cmw->wk[WK_MIC_PARAM]);
			break;
		case 3:		// 録音 2Khz
			cmw->wk[WK_MIC_PARAM] = 2000;
			SamplingStart(cmw->wk[WK_MIC_PARAM]);
			break;

		case 4:		// 録音 1.75Khz
			cmw->wk[WK_MIC_PARAM] = 1750;
			SamplingStart(cmw->wk[WK_MIC_PARAM]);
			break;
		case 5:		// 録音 1.5Khz
			cmw->wk[WK_MIC_PARAM] = 1500;
			SamplingStart(cmw->wk[WK_MIC_PARAM]);
			break;
		case 6:		// 録音 1.25Khz
			cmw->wk[WK_MIC_PARAM] = 1250;
			SamplingStart(cmw->wk[WK_MIC_PARAM]);
			break;


		case 7:		// 録音 1Khz
			cmw->wk[WK_MIC_PARAM] = 1000;
			SamplingStart(cmw->wk[WK_MIC_PARAM]);
			break;
		case 8:		// 録音 500hz
			cmw->wk[WK_MIC_PARAM] = 512;
			SamplingStart(cmw->wk[WK_MIC_PARAM]);
			break;
		case 10:		// 再生
			{
				WAVEOUT_WORK waveout_wk;
				waveout_wk.handle			= Snd_WaveOutHandleGet(WAVEOUT_CH_NORMAL);	//波形再生ハンドル
				waveout_wk.format			= NNS_SND_WAVE_FORMAT_PCM8;	//波形データフォーマット
				waveout_wk.dataaddr			= Snd_GetDebugWaveBufAdrs();//波形データの先頭アドレス
				waveout_wk.loopFlag			= FALSE;					//ループフラグ
				waveout_wk.loopStartSample	= 0;						//ループ開始サンプル位置
				waveout_wk.samples			= cmw->wk[WK_MIC_PARAM]*MIC_PLAY_TIME;	//波形データのサンプル数
				if((waveout_wk.samples&0x1f)!=0){
					waveout_wk.samples &= 0xffffffe0;
				}
				if(sys.cont&PAD_BUTTON_R){
//					SamplingDataSearchDiff( (s8*)waveout_wk.dataaddr, waveout_wk.samples, 16 );
//					SamplingDataFab((s8*)waveout_wk.dataaddr, waveout_wk.samples,16);
					FIELDSYS_WORK *fsys = (FIELDSYS_WORK*)cmw->wk[WK_FIELDSYS];
					PERAPVOICE *pv;
					OS_Printf("fsys = %08x\n",fsys);
					pv      = SaveData_GetPerapVoice(fsys->savedata);

					PERAPVOICE_SetVoiceData( pv, waveout_wk.dataaddr );
					PERAPVOICE_ExpandVoiceData((s8*)waveout_wk.dataaddr, (s8*)PERAPVOICE_GetVoiceData(pv));
				}
				if(sys.cont&PAD_BUTTON_L){
					SamplingDataSearchDiff( (s8*)waveout_wk.dataaddr, waveout_wk.samples, 32 );
//					SamplingDataFab((s8*)waveout_wk.dataaddr, waveout_wk.samples,64);
				}
				waveout_wk.sampleRate		= cmw->wk[WK_MIC_PARAM];	//波形データのサンプリングレート
				waveout_wk.volume			= 127;						//音量
				waveout_wk.speed			= 32768;					//再生スピード
				waveout_wk.pan				= 64;						//パン(0-127)
				Snd_WaveOutStart( &waveout_wk, WAVEOUT_CH_NORMAL );
			}
			break;
		case 11:		// 再生を終了してウインドウもクローズ
			Snd_WaveOutStop(WAVEOUT_CH_NORMAL);
		case BMPLIST_NULL:
			break;
		case BMPLIST_CANCEL:
			WirelessIconEnd((VINTR_WIRELESS_ICON*)cmw->wk[ WK_WM_ICON ]);
			DebugMenuExitSub( tcb );

			// 波形再生用チャンネルを開放する
			Snd_WaveOutFreeChannel(WAVEOUT_CH_NORMAL);
			break;
		default:
			cmw->wk[WK_LIST_RET] = ret;
			cmw->wk[WK_SEQ]++;
		}
		break;
	case 1:
		{
			WirelessIconEnd((VINTR_WIRELESS_ICON*)cmw->wk[ WK_WM_ICON ]);
			FieldSystemProc_SeqHoldEnd();
			DebugMoriBmpMenuExit( work );
			PMDS_taskDel( tcb );

			// 波形再生用チャンネルを開放する
			Snd_WaveOutFreeChannel(WAVEOUT_CH_NORMAL);
		}
	}
	
}
#endif



//----------------------------------------------------------------------------
/**
 *
 *	@brief 名前入力呼び出しテスト
 *
 *	@param	TCB_PTR tcb
 *	@param	work 
 *
 *	@return
 *
 *
 */
//-----------------------------------------------------------------------------
void TestNameIn_Call( TCB_PTR tcb, void* work ) 
{
	TEST_PROC_WORK* wk = work;
	
	switch( wk->seq ){
	case 0:		// フェードアウト
		FieldSystemProc_SeqHoldEnd();		
		wk->seq++;
		break;

	case 1:		// フィールド破棄
		if(wk->sub == 0){
			wk->sub++;

			// 名前入力用引数ワーク作成
			wk->NameInParam = NameIn_ParamAllocMake(HEAPID_WORLD, NAMEIN_MYNAME 
								/* NAMEIN_FRIENDNAME */ /*NAMEIN_FRIENDCODE*/ /*NAMEIN_POKEMON*/ , 
								2, NAMEIN_PERSON_LENGTH, SaveData_GetConfig(wk->fsys->savedata) );
//			wk->NameInParam = NameIn_ParamAllocMake(HEAPID_WORLD, NAMEIN_MYNAME, PM_MALE, 5);
//			PM_strcpy(wk->NameInParam->str,test_name);
			wk->NameInParam->info = MyStatus_GetMySex(SaveData_GetMyStatus(wk->fsys->savedata));
			wk->NameInParam->get_msg_id = 0;
			wk->NameInParam->sex = MyStatus_GetMySex(SaveData_GetMyStatus(wk->fsys->savedata));
			wk->NameInParam->boxdata = SaveData_GetBoxData(wk->fsys->savedata);
			OS_Printf("BOXDATA Addr = %08x\n",wk->NameInParam->boxdata);
			// 名前入力PROC作成
			NameInput_SetProc( wk->fsys, wk->NameInParam );

			GameSystem_FinishFieldProc( wk->fsys );

		}else{

			// 終了が完了したかチェック
			if( FieldEvent_Cmd_WaitMapProcStart( wk->fsys ) == FALSE ){
				wk->sub = 0;
				wk->seq++;
			}
		}
		break;

	case 2:		// 名前入力初期化
		wk->seq++;
		break;
	case 3:		// 名前入力終了待ち
		if( GameSystem_CheckSubProcExists( wk->fsys ) == FALSE ){
			{
				int i;
				OS_Printf("書いた名前は ");
				for(i=0;i<5;i++){
					OS_Printf("%x",wk->NameInParam->str[i]);
				}
				OS_Printf("\n");
				OS_Printf("キャンセル？ = %d\n",wk->NameInParam->cancel);
			}
//			sys_FreeMemory( HEAPID_WORLD, wk->NameInParam );

			// 書いた名前をMYSTATUSに反映させる
			if(!wk->NameInParam->cancel){
				MyStatus_SetMyName(SaveData_GetMyStatus(wk->fsys->savedata),wk->NameInParam->str);
			}
			NameIn_ParamDelete( wk->NameInParam );
			// フィールド復帰
			GameSystem_CreateFieldProc( wk->fsys );
			wk->seq++;

		}
		break;
	case 4:
		if( GameSystem_CheckFieldProcExists(wk->fsys) ){
			FieldFadeWipeSet( FLD_DISP_BRIGHT_BLACKIN );
			// タスク終了
			TCB_Delete( tcb );
			sys_FreeMemoryEz( work );
		}
		break;
	}
}


void DebugNameInFuncInit(GF_BGL_INI * ini, FIELDSYS_WORK *fsys)
{
	TEST_PROC_WORK *namein_test = NULL;

	// タスク生成
	namein_test = sys_AllocMemory( HEAPID_BASE_DEBUG, sizeof( TEST_PROC_WORK ) );
	// セルアクター登録数初期化
	TCB_Add(TestNameIn_Call, namein_test, 8);

	namein_test->seq  = 0;
	namein_test->sub  = 0;
	namein_test->bgl  = ini;
	namein_test->fsys = fsys;
	



	
//	FieldSystemProc_SeqHoldEnd();
//	DebugMoriBmpMenuExit( work );
//	PMDS_taskDel( tcb );
	
}

//------------------------------------------------------------------
/**
 * 交換リスト呼び出しテスト
 *
 * @param   tcb		
 * @param   work		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void TestTradeList_Call( TCB_PTR tcb, void* work ) 
{
	TEST_PROC_WORK* wk = work;
	
	switch( wk->seq ){
	case 0:		// フェードアウト
		FieldSystemProc_SeqHoldEnd();		
		wk->seq++;
		break;

	case 1:		// フィールド破棄
		if(wk->sub == 0){
			wk->sub++;

			// 交換リストPROC作成
//			TradeList_SetProc( wk->fsys );
//			OekakiBoard_SetProc( wk->fsys );
			Field_MySign_SetProc( wk->fsys );

			GameSystem_FinishFieldProc( wk->fsys );

		}else{

			// 終了が完了したかチェック
			if( FieldEvent_Cmd_WaitMapProcStart( wk->fsys ) == FALSE ){
				wk->sub = 0;
				wk->seq++;
			}
		}
		break;
	case 2:		// 名前入力終了待ち
		if( GameSystem_CheckSubProcExists( wk->fsys ) == FALSE ){
			// フィールド復帰
			GameSystem_CreateFieldProc( wk->fsys );
			wk->seq++;

		}
		break;
	case 3:
		if( GameSystem_CheckFieldProcExists(wk->fsys) ){
			FieldFadeWipeSet( FLD_DISP_BRIGHT_BLACKIN );
			// タスク終了
			TCB_Delete( tcb );
			sys_FreeMemoryEz( work );
		}
		break;
	}
}


//==============================================================================
/**
 * 交換リスト呼び出しテストタスク初期化
 *
 * @param   ini		
 * @param   fsys		
 *
 * @retval  none		
 */
//==============================================================================
void DebugTradeListFuncInit(GF_BGL_INI * ini, FIELDSYS_WORK *fsys)
{
	TEST_PROC_WORK *tradelist_proc = NULL;

	// タスク生成
	tradelist_proc = sys_AllocMemory( HEAPID_BASE_DEBUG, sizeof( TEST_PROC_WORK ) );
	// セルアクター登録数初期化
	TCB_Add(TestTradeList_Call, tradelist_proc, 8);

	tradelist_proc->seq  = 0;
	tradelist_proc->sub  = 0;
	tradelist_proc->bgl  = ini;
	tradelist_proc->fsys = fsys;
}

//------------------------------------------------------------------
/**
 * 世界交換呼び出しテスト
 *
 * @param   tcb		
 * @param   work		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void TestWorldTrade_Call( TCB_PTR tcb, void* work ) 
{
	TEST_PROC_WORK* wk = work;
	
	switch( wk->seq ){
	case 0:		// フェードアウト
		FieldSystemProc_SeqHoldEnd();		
		wk->seq++;
		break;

	case 1:		// フィールド破棄
		if(wk->sub == 0){
			wk->sub++;

			// 世界交換PROC作成
			Field_WorldTrade_SetProc( wk->fsys, 0 );

			GameSystem_FinishFieldProc( wk->fsys );

		}else{

			// 終了が完了したかチェック
			if( FieldEvent_Cmd_WaitMapProcStart( wk->fsys ) == FALSE ){
				wk->sub = 0;
				wk->seq++;
			}
		}
		break;
	case 2:		// 世界交換終了待ち
		if( GameSystem_CheckSubProcExists( wk->fsys ) == FALSE ){
			// フィールド復帰
			GameSystem_CreateFieldProc( wk->fsys );
			wk->seq++;

		}
		break;
	case 3:
		if( GameSystem_CheckFieldProcExists(wk->fsys) ){
			FieldFadeWipeSet( FLD_DISP_BRIGHT_BLACKIN );
			// タスク終了
			TCB_Delete( tcb );
			sys_FreeMemoryEz( work );
		}
		break;
	}
}


//==============================================================================
/**
 * 交換リスト呼び出しテストタスク初期化
 *
 * @param   ini		
 * @param   fsys		
 *
 * @retval  none		
 */
//==============================================================================
void DebugWorldTradeFuncInit(GF_BGL_INI * ini, FIELDSYS_WORK *fsys)
{
	TEST_PROC_WORK *worldtrade_proc = NULL;

	// タスク生成
	worldtrade_proc = sys_AllocMemory( HEAPID_BASE_DEBUG, sizeof( TEST_PROC_WORK ) );
	// セルアクター登録数初期化
	TCB_Add(TestWorldTrade_Call, worldtrade_proc, 8);

	worldtrade_proc->seq  = 0;
	worldtrade_proc->sub  = 0;
	worldtrade_proc->bgl  = ini;
	worldtrade_proc->fsys = fsys;
}

#if 0
//------------------------------------------------------------------
/**
 * Wifiバトルタワー呼び出しテスト
 *
 * @param   tcb		
 * @param   work		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void TestWifiBTower_Call( TCB_PTR tcb, void* work ) 
{
	TEST_PROC_WORK* wk = work;
	
	switch( wk->seq ){
	case 0:		// フェードアウト
		FieldSystemProc_SeqHoldEnd();		
		wk->seq++;
		break;

	case 1:		// フィールド破棄
		if(wk->sub == 0){
			wk->sub++;

			// WIFIバトルタワーPROC作成
			Field_WifiBattleTowerConnect_SetProc( wk->fsys, wk->flag, 0 );

			GameSystem_FinishFieldProc( wk->fsys );

		}else{

			// 終了が完了したかチェック
			if( FieldEvent_Cmd_WaitMapProcStart( wk->fsys ) == FALSE ){
				wk->sub = 0;
				wk->seq++;
			}
		}
		break;
	case 2:		// タワー終了待ち
		if( GameSystem_CheckSubProcExists( wk->fsys ) == FALSE ){
			// フィールド復帰
			GameSystem_CreateFieldProc( wk->fsys );
			wk->seq++;

		}
		break;
	case 3:
		if( GameSystem_CheckFieldProcExists(wk->fsys) ){
			FieldFadeWipeSet( FLD_DISP_BRIGHT_BLACKIN );
			// タスク終了
			TCB_Delete( tcb );
			sys_FreeMemoryEz( work );
		}
		break;
	}
}


static TEST_PROC_WORK *CommonBTowerSetUp( GF_BGL_INI * ini, FIELDSYS_WORK *fsys )
{
	// タスク用ワーク生成
	TEST_PROC_WORK *btower_proc = sys_AllocMemory( HEAPID_BASE_DEBUG, sizeof( TEST_PROC_WORK ) );

	btower_proc->seq  = 0;
	btower_proc->sub  = 0;
	btower_proc->bgl  = ini;
	btower_proc->fsys = fsys;

	return btower_proc;
}

//==============================================================================
/**
 * バトルタワー呼び出しテストタスク初期化
 *
 * @param   ini		
 * @param   fsys		
 *
 * @retval  none		
 */
//==============================================================================
static void DebugWifiBTowerFuncInit0( GF_BGL_INI * ini, FIELDSYS_WORK *fsys )
{
	TEST_PROC_WORK *btower_proc = CommonBTowerSetUp( ini, fsys );
	
	btower_proc->flag = 0;

	// セルアクター登録数初期化
	TCB_Add(TestWifiBTower_Call, btower_proc, 8);

}

static void DebugWifiBTowerFuncInit1( GF_BGL_INI * ini, FIELDSYS_WORK *fsys )
{
	TEST_PROC_WORK *btower_proc = CommonBTowerSetUp( ini, fsys );
	
	btower_proc->flag = 1;

	// セルアクター登録数初期化
	TCB_Add(TestWifiBTower_Call, btower_proc, 8);

}

static void DebugWifiBTowerFuncInit2( GF_BGL_INI * ini, FIELDSYS_WORK *fsys )
{
	TEST_PROC_WORK *btower_proc = CommonBTowerSetUp( ini, fsys );
	
	btower_proc->flag = 2;

	// セルアクター登録数初期化
	TCB_Add(TestWifiBTower_Call, btower_proc, 8);

}

#endif

static void DebugSodateya1000Po( GF_BGL_INI * ini, FIELDSYS_WORK *fsys )
{
	SODATEYA_WORK *sw;
	
	sw = SaveData_GetSodateyaWork(fsys->savedata);

	SodateyaPlusWalk( sw, 1000 );
	
	// フィールド処理ポーズ状態から復帰
	FieldSystemProc_SeqHoldEnd();
}

static void DebugSodateya10000Po( GF_BGL_INI * ini, FIELDSYS_WORK *fsys )
{
	SODATEYA_WORK *sw;
	
	sw = SaveData_GetSodateyaWork(fsys->savedata);

	SodateyaPlusWalk( sw, 1000 );
	
	// フィールド処理ポーズ状態から復帰
	FieldSystemProc_SeqHoldEnd();
}

static void DebugFriendListClear( GF_BGL_INI * ini, FIELDSYS_WORK *fsys )
{
	FRIEND_LIST *flist = SaveData_GetFriendList( fsys->savedata );
	// ともだちグループオールクリア
	FriendList_Init( flist );

	// フィールド処理ポーズ状態から復帰
	FieldSystemProc_SeqHoldEnd();
}

static void DebugLongName( GF_BGL_INI * ini, FIELDSYS_WORK *fsys )
{
	POKEPARTY     *my = SaveData_GetTemotiPokemon(fsys->savedata);
	POKEMON_PARAM *pp = PokeParty_GetMemberPointer( my, 0 );
	PokeParaPut( pp, ID_PARA_nickname, (u8*)testname );
	PokeParaPut( pp, ID_PARA_oyaname, (u8*)parentname );

	// フィールド処理ポーズ状態から復帰
	FieldSystemProc_SeqHoldEnd();
}

//------------------------------------------------------------------
/**
 * @brief   育て屋に正しいポケモンがいればタマゴフラグがセットされる
 *
 * @param   ini		
 * @param   fsys		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void DebugSodateyaTamgoSet( GF_BGL_INI * ini, FIELDSYS_WORK *fsys )
{
	SODATEYA_WORK *sw;
	
	sw = SaveData_GetSodateyaWork(fsys->savedata);
	
	if(PokeAzukeruCheck(sw)==2){			//2体いて
		if(SodateyaGetAffinity(sw) < 3){	//子供が生まれてもいい相性なら
			SodateyaWork_SetEggFlag(sw,gf_fix_rand(sys.vsync_counter));			//タマゴ乱数をセット
		}
	}
	
	// フィールド処理ポーズ状態から復帰
	FieldSystemProc_SeqHoldEnd();


}



//------------------------------------------------------------------
/**
 * @brief   てもちのタマゴが孵化するようにパラメータ変更
 *
 * @param   ini		
 * @param   fsys		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void DebugTamagoFuka( GF_BGL_INI * ini, FIELDSYS_WORK *fsys )
{
	u8 i,work;
	POKEPARTY     *temoti;
	POKEMON_PARAM *pp;
	SODATEYA_WORK *sw;
	
	sw     = SaveData_GetSodateyaWork(fsys->savedata);
	temoti = SaveData_GetTemotiPokemon(fsys->savedata);

	for(i=0;i<PokeParty_GetPokeCount(temoti);i++){
		pp = PokeParty_GetMemberPointer( temoti, i );
		if(PokeParaGet(pp,ID_PARA_tamago_flag,NULL)){
			work = 0;
			PokeParaPut(pp,ID_PARA_friend, &work);
		}
	}
	
	SodateyaWork_SetEggCount( sw, 253 );
	
	// フィールド処理ポーズ状態から復帰
	FieldSystemProc_SeqHoldEnd();
}

