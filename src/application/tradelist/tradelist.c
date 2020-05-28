//============================================================================================
/**
 * @file	tradelist.c
 * @bfief	ポケモン交換リスト画面
 * @author	Akito Mori
 * @date	05.12.08
 */
//============================================================================================

// コメントをはずすと「こうかんする」が一つ目の選択肢になる

#ifdef PM_DEBUG
//#define DEBUG_PAD_ON
//#define DEBUG_TIMEOUT
#endif

#include "common.h"
#include "system/procsys.h"
#include "system/arc_tool.h"
#include "system/arc_util.h"
#include "system/pm_str.h"
#include "system/clact_tool.h"
#include "system/msgdata_util.h"
#include "system/wordset.h"
#include "msgdata/msg.naix"
#include "system/wipe.h"
#include "system/brightness.h"
#include "system/fontproc.h"
#include "system/lib_pack.h"
#include "system/fontoam.h"
#include "system/softsprite.h"
#include "system/gra_tool.h"
#include "system/bmp_menu.h"
#include "system/bmp_list.h"
#include "savedata/savedata.h"
#include "system/window.h"
#include "gflib/msg_print.h"
#include "gflib/touchpanel.h"
#include "poketool/monsno.h"
#include "poketool/pokeicon.h"
#include "poketool/poke_memo.h"
#include "application/tradelist.h"
#include "system/snd_tool.h"
#include "system/snd_perap.h"
#include "poketool/monsno.h"
#include "gflib/strbuf_family.h"
#include "communication/communication.h"
#include "communication/comm_save.h"
#include "communication/wm_icon.h"
#include "poketool/poke_tool.h"
#include "poketool/pokeparty.h"
#include "itemtool/item.h"
#include "field/comm_union_beacon.h"
#include "savedata/friendlist.h"
#include "savedata/friendlist_local.h"
#include "communication/comm_wifihistory.h"
#include "savedata/get_poke.h"

#include "system/pm_rtc.h"			//GF_RTC_IsNightTime

#include "msgdata/msg_connect.h"
#include "msgdata/msg_dstrade.h"

#include "tradelist_bmp.h"

#include "comm_command_tradelist.h"
#include "itemtool/myitem.h"

#include "wifi/dwc_rapfriend.h"
#include "msgdata/msg_wifi_note.h"

#define FIRST_NATUKIDO  (70)				///交換されたポケモンに入れるなつき度


#define NAMEIN_MOVE_SE		(SEQ_SE_DP_SELECT)
#define NAMEIN_DECIDE_SE	(SEQ_SE_DP_SELECT)
#define NAMEIN_BS_SE		(SEQ_SE_DP_SELECT)

#define POKEICON_VRAM_OFFSET ( 4*32+18  )
#define POKEICON_TRANS_CELL  ( 4*4      )
#define POKEICON_TRANS_SIZE	 ( POKEICON_TRANS_CELL*0x20 )
#define POKEICON_PAL_OFFSET	 ( 10 )

#define POKEGRA_VRAM_OFFSET  ( 0 )
#define POKEGRA_VRAM_SIZE     ( 0x20*10*10 )

#define TRADELISTSTR_MAX	 ( 12*2 )		  // 交換画面で一番キャラが並ぶのは12キャラなのでその倍文字列バッファを取っておく
#define TRADELIST_CACT_MAX   ( 2+12+12+12+2+2+2+1) // カーソル２　
												   // ポケモン１２　
												   // アイテム１２　
												   // カスタムボール１２　
												   // 下ポケモン２　
												   // 矢印２
													

// nceに登録されているモンスターボールのアニメNO（この後ろに各々のモンスターボールが続く）
#define CELL_MONSTER_BALL_NO	 ( 6 )

#define CELL_SEX_ICON_NO		 ( 22 )

#define TIMEOUT_LIMIT			( 30*60 )			// タイムアウトまで2分にした

#include "tradelist.naix"			// グラフィックアーカイブ定義
//============================================================================================
//	定数定義
//============================================================================================
enum {
	SEQ_IN = 0,
	SEQ_MAIN,
	SEQ_OUT,
};

enum{
	MODE_NORMAL=0,
	MODE_TRADE_SELECT,
	MODE_END_SELECT,
	MODE_STATUS_SELECT,
};

enum{
	TRADELIST_SEQ_POKEMON_EXCHANGE,
	TRADELIST_SEQ_MAIN,
	TRADELIST_SEQ_END,
	TRADELIST_SEQ_STATUS_INFADE,
	TRADELIST_SEQ_STATUS_INFADE_WAIT,
	TRADELIST_SEQ_STATUS,
	TRADELIST_SEQ_STATUS_OUTFADE,
	TRADELIST_SEQ_STATUS_OUTFADE_WAIT,
	
};


typedef struct{
	CLACT_WORK_PTR parent;
	CLACT_WORK_PTR child;
	int dx;
	int id;
}FUNC_BUTTON_TASK_WORK;


#define TRADELIST_CURSOR_1_X (  0*8 )
#define TRADELIST_CURSOR_2_X (  8*8 )
#define TRADELIST_CURSOR_3_X ( 16*8 )
#define TRADELIST_CURSOR_4_X ( 24*8 )
#define TRADELIST_CURSOR_1_Y (  4*8 )
#define TRADELIST_CURSOR_2_Y (  9*8 )
#define TRADELIST_CURSOR_3_Y ( 14*8 )
#define TRADELIST_CURSOR_END_X	(24*8 )
#define TRADELIST_CURSOR_END_Y	(20*8 )


#define SUB_POKEMON1_POS_X	 (  63 )
#define SUB_POKEMON2_POS_X	 ( 192 )
#define SUB_POKEMON_POS_Y	 (  96-8 )
#define SUB_ARROW_POS_X		 ( 118 )
#define SUB_ARROW1_POS_Y	 ( 72 )
#define SUB_ARROW2_POS_Y	 ( 108 )
#define SUB_BALL_POS_X		 ( 2*8 )
#define SUB_BALL_POS_Y		 ( 1*8 )
#define SUB_BALL2_POS_X		 ( 18*8 )
#define SUB_SEX_ICON_X		 ( 12*8+3 )
#define SUB_SEX_ICON2_X		 ( (12+16)*8+3 )
#define SUB_SEX_ICON_Y		 (    8 )

static const main_cursor_pos[][2]={
	{TRADELIST_CURSOR_1_X,TRADELIST_CURSOR_1_Y, },
	{TRADELIST_CURSOR_2_X,TRADELIST_CURSOR_1_Y, },
	{TRADELIST_CURSOR_1_X,TRADELIST_CURSOR_2_Y, },
	{TRADELIST_CURSOR_2_X,TRADELIST_CURSOR_2_Y, },
	{TRADELIST_CURSOR_1_X,TRADELIST_CURSOR_3_Y, },
	{TRADELIST_CURSOR_2_X,TRADELIST_CURSOR_3_Y, },
	{TRADELIST_CURSOR_3_X,TRADELIST_CURSOR_1_Y, },
	{TRADELIST_CURSOR_4_X,TRADELIST_CURSOR_1_Y, },
	{TRADELIST_CURSOR_3_X,TRADELIST_CURSOR_2_Y, },
	{TRADELIST_CURSOR_4_X,TRADELIST_CURSOR_2_Y, },
	{TRADELIST_CURSOR_3_X,TRADELIST_CURSOR_3_Y, },
	{TRADELIST_CURSOR_4_X,TRADELIST_CURSOR_3_Y, },
	{TRADELIST_CURSOR_END_X,TRADELIST_CURSOR_END_Y, },

};

static const sub_icon_pos[][3]={
	{SUB_POKEMON1_POS_X, SUB_POKEMON_POS_Y, 0},						//ポケモン
	{SUB_POKEMON2_POS_X, SUB_POKEMON_POS_Y, 1},
	{SUB_BALL_POS_X,   SUB_BALL_POS_Y,      CELL_MONSTER_BALL_NO},	// モンスターボール
	{SUB_BALL2_POS_X,  SUB_BALL_POS_Y,      CELL_MONSTER_BALL_NO},
	{SUB_SEX_ICON_X, SUB_SEX_ICON_Y,CELL_SEX_ICON_NO},				// 性別
	{SUB_SEX_ICON2_X,SUB_SEX_ICON_Y,CELL_SEX_ICON_NO},
};


#define POKEICON_DIFFX	(16)
#define POKEICON_DIFFY	(-6)
#define POKEITEM_DIFFX	(16+20)
#define POKEITEM_DIFFY	(16)
#define POKECBALL_DIFFX (16+20+8)


#include "tradelist_def.h"


//============================================================================================
//	AGBから持ってきたデータ
//============================================================================================
//カーソル移動用のテーブル
//上下左右の順に定義してあります
//  ０ １    ６  ７
//  ２ ３    ８  ９
//  ４ ５  １０１１
//             １２
static const u8 movepostbl[][4][6]={
									//   0 の位置からの4方向の行きつく先の優先度ﾃｰﾌﾞﾙ(上下左右の順)
									//   少ない数字の方が優先度が高い
	{{ 4, 2,12,12},{ 2, 4,12,12},{ 7, 6, 1, 0},{ 1, 6, 7, 0},},		//0
	{{ 5, 3,12,12},{ 3, 5,12,12},{ 0, 7, 6, 1},{ 6, 7, 0, 1},},		
	{{ 0, 0, 0, 0},{ 4, 0, 0, 0},{ 9, 8, 7, 6},{ 3, 1,     },},		
	{{ 1, 1, 1, 1},{ 5, 1, 1, 1},{ 2, 9, 8, 7},{ 8, 9, 6, 6},},		
	{{ 2, 2, 2, 2},{ 0, 0, 0, 0},{11,10,9,8,7,6},{ 5,3,1,  },},		
	{{ 3, 3, 3, 3},{ 1, 1, 1, 1},{ 4, 4, 4, 4},{10, 8, 6,  },},		//5
	{{10, 8,12,  },{ 8,10,12,  },{ 1, 0,     },{ 7, 0, 1,  },},		
	{{12,        },{ 9,12,     },{ 6,        },{ 0,        },},		
	{{ 6,        },{10, 6,     },{ 3, 2, 1, 0},{ 9, 7,     },},		
	{{ 7,        },{11,12,     },{ 8,        },{ 2, 0, 1,  },},		
	{{ 8,        },{ 6,        },{ 5, 4, 3, 2,1,0},{11, 9, 7, },},	//10
	{{ 9,        },{12,        },{10,        },{ 4, 2, 0,  },},		
	{{11, 9, 7, 6},{ 7, 6,     },{12,        },{12,        },},		

};


static const int trade_msg_table[][4]=
{
	{mes_dstrade_02_01,   0, 0, },
	{mes_dstrade_02_02,   1, mes_dstrade_03_01,  3 },
	{mes_dstrade_02_02,   1, mes_dstrade_03_02,  4 },
	{mes_dstrade_04_01,   2, 0,0,   },
	{mes_dstrade_04_03,   2, 0,0,   },
	{mes_dstrade_04_04,   2, 0,0,   },
	{mes_dstrade_04_07,   2, 0,0,   },
	{mes_dstrade_04_08,   2, 0,0,   },
};


//============================================================================================
//	プロトタイプ宣言
//============================================================================================
/*** 関数プロトタイプ ***/
static void TransPokeIconCharaPal( NNSG2dCharacterData *chara, int pokeno, int form, int tamago, int no , CLACT_WORK_PTR icon);
static void TrainerNamePrint( GF_BGL_BMPWIN *win );
static void PokemonInfoSubPrint( TRADELIST_WORK *wk, int page );
static void VBlankFunc( void * work );
static void VramBankSet(void);
static void BgInit( GF_BGL_INI * ini );
static void char_pltt_manager_init(void);
static void InitWork(TRADELIST_WORK *wk, PROC * proc);
static void BgExit( GF_BGL_INI * ini );
static void TradeListMakeScreenSet(GF_BGL_INI *bgl, int mynum, int friendnum);
static void BgGraphicSet( TRADELIST_WORK * wk );
static void InitCellActor(TRADELIST_WORK *wk);
static void SetCellActor(TRADELIST_WORK *wk);
static void DebugOBJPOSGet(TRADELIST_WORK *wk);
static int AroundWork(int w, int min, int max);
static void ControlCursor(u32 *CommWork);
static void TouchFunc(TRADELIST_WORK *wk);
static void CursorColTrans(u16 *CursorCol);
static int NextCursorSearch(int pos, int arrow, POKE_INFO *info);
static void CursorPosChange(int pos, CLACT_WORK_PTR CursorAct, int side);
static int  ViewChange(u32 *Command, int *pos, CLACT_WORK_PTR CusorAct, POKE_INFO *info, int side);
static int  TransPokeGra_SubLcd(int side, POKEMON_PARAM *pp, u8 *char_work, SOFT_SPRITE_ARC *ssa);
static void SetFnoteData( FNOTE_DATA *fnote, POKEMON_PARAM *pp );
static void CommSendPerapVoice( PERAPVOICE *pv );
static void TimeIconAdd( TRADELIST_WORK *tlw );
static void TimeIconDel( TRADELIST_WORK *tlw );
static int  TradeTemochiCheck( TRADELIST_WORK *wk );
static void TimeoutStart( TRADELIST_WORK *wk );
static void TimeoutErrorCheck( TRADELIST_WORK *wk );



static void Regist_WordSetPokeName(WORDSET *wordset, POKEPARTY *party, int start );
static void Print_MainPokeName(GF_BGL_BMPWIN *win, WORDSET *wordset, MSGDATA_MANAGER *manager, POKEPARTY *party, int start );
static void TransPokeStr_SubLcd(GF_BGL_BMPWIN *win, int side, POKEPARTY *party, int pos, TRADELIST_WORK *wk);
static void PokemonDataExchange(POKEPARTY *my, POKEPARTY *your, int mysel, int yoursel, TRADELIST_PARAM *param);
static void FreeClact( TRADELIST_WORK *wk );
static void PokemonName_Get_Write( TRADELIST_WORK *wk);
static void PokeIconFree( TRADELIST_WORK *wk );
static void CursorSubLcd_Update(TRADELIST_WORK *wk);
static void PokeStr_SubLcdOff(GF_BGL_BMPWIN *win, int side, TRADELIST_WORK *wk);
static void GetPokeInfo( POKEMON_PARAM *pp, POKE_INFO* info );
static void Clact_SetPos( CLACT_WORK_PTR clact, int x, int y );
static int NidoranSpecialCheck( POKE_INFO *info, POKEPARTY *party, int pos, int sex );
static void TradeListCommSpRibbonDate(  SAVEDATA *sv );


static int TradeListPokemonExchange( TRADELIST_WORK *wk );
static int TradeListMain( TRADELIST_WORK *wk );
static void LoadPokeIcon(POKEPARTY *party, int start, TRADELIST_WORK *wk);


static int trade_seq_normal(TRADELIST_WORK *wk);
static int trade_seq_end(TRADELIST_WORK *wk );
static int trade_seq_mypoke(TRADELIST_WORK *wk );
static int trade_seq_friendpoke(TRADELIST_WORK *wk );
static int trade_seq_endyesno_wait(TRADELIST_WORK *wk);
static int trade_seq_endyesno(TRADELIST_WORK *wk );
static int trade_seq_mypoke_menu(TRADELIST_WORK *wk );
static int trade_seq_decide(TRADELIST_WORK *wk );
static int trade_seq_decide_wait(TRADELIST_WORK *wk );
static int trade_seq_friend_menu(TRADELIST_WORK *wk );
static int trade_seq_return_wait(TRADELIST_WORK *wk);
static int trade_seq_return(TRADELIST_WORK *wk);
static int trade_seq_trade_yesno(TRADELIST_WORK *wk );
static int trade_seq_trade_yesno_wait(TRADELIST_WORK *wk);
static int trade_seq_trade_yesno_result( TRADELIST_WORK *wk );
static int trade_seq_go_next( TRADELIST_WORK *wk );
static int trade_seq_save_text( TRADELIST_WORK *wk );
static int trade_seq_save_func( TRADELIST_WORK *wk );
static int trade_seq_save_wait( TRADELIST_WORK *wk );
static int trade_seq_icon_move( TRADELIST_WORK *wk );
static int trade_seq_icon_move_wait( TRADELIST_WORK *wk );
static int trade_seq_customball_yesno_wait(TRADELIST_WORK *wk);
static int trade_seq_customball_yesno(TRADELIST_WORK *wk );


static void trade_icon_reappear( TRADELIST_WORK *wk );

static void AnimePosSet(VecFx32 animpos[], int sx, int sy, int ex, int ey);
static void PokeIconPosSet( CLACT_WORK_PTR icon, CLACT_WORK_PTR item, CLACT_WORK_PTR cball, int count, VecFx32 pos[], POKE_INFO *info );
static void SubLcd_RightPanelOn( TRADELIST_WORK *wk, int pos );


static void SubLCD_ScrollFunc( TRADELIST_WORK *wk );
static void PokeNamePrint( GF_BGL_BMPWIN *win, POKEPARTY *party, int pos, int width, int print_sw );

static int trade_seq_friend_regist_del_yesno(TRADELIST_WORK* wk);
static int trade_seq_friend_regist_yesno(TRADELIST_WORK* wk);
static int trade_seq_friend_regist_init(TRADELIST_WORK* wk);
static int trade_seq_friend_regist_delmenu_init( TRADELIST_WORK* wk );
static int MainFunc( TRADELIST_WORK *wk );
static void poke_status_setup( TRADELIST_WORK *wk, int side );


static void CommSendFriendList( MYSTATUS *mystatus, FRIEND_LIST *friendlist, FRIEND_LIST *sendbuf );


static void ArcUtil_ScrnSetNoTrans(u32 fileIdx, u32 dataIdx, GF_BGL_INI* bgl, u32 frm, u32 offs, u32 transSize, BOOL compressedFlag, u32 heapID);

//============================================================================================
//	グローバル変数
//============================================================================================


#define POKE_NICKNAME_LEN	(10+1)

//============================================================================================
//	プロセス関数
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * プロセス関数：初期化
 *
 * @param	proc	プロセスデータ
 * @param	seq		シーケンス
 *
 * @return	処理状況
 */
//--------------------------------------------------------------------------------------------
PROC_RESULT TradeListProc_Init( PROC * proc, int * seq )
{
	TRADELIST_WORK * wk;

	sys_VBlankFuncChange( NULL, NULL );	// VBlankセット
	sys_HBlankIntrStop();	//HBlank割り込み停止

	GF_Disp_GX_VisibleControlInit();
	GF_Disp_GXS_VisibleControlInit();
	GX_SetVisiblePlane( 0 );
	GXS_SetVisiblePlane( 0 );

	sys_CreateHeap( HEAPID_BASE_APP, HEAPID_TRADELIST, 0x50000+0x20000+2000 );

	wk = PROC_AllocWork( proc, sizeof(TRADELIST_WORK), HEAPID_TRADELIST );
	MI_CpuClearFast( wk, sizeof(TRADELIST_WORK) );
	wk->bgl = GF_BGL_BglIniAlloc( HEAPID_TRADELIST );
	
	// 文字列マネージャー生成
	wk->PokeNameWordSet  = WORDSET_CreateEx( 12, POKE_NICKNAME_LEN*2, HEAPID_TRADELIST );
	wk->WindowStrWordSet = WORDSET_Create( HEAPID_TRADELIST );
	wk->SubLcdWordSet    = WORDSET_Create( HEAPID_TRADELIST );

	wk->MsgManager = MSGMAN_Create( MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_dstrade_dat, HEAPID_TRADELIST );
	wk->subproc    = NULL;

	// ワーク初期化
	InitWork(wk,proc);

	// キーリピート間隔変更
	sys_KeyRepeatSpeedSet( 4, 8 );

	VramBankSet();
	BgInit( wk->bgl );
	// 輝度変更セット
	WIPE_SYS_Start( WIPE_PATTERN_WMS, WIPE_TYPE_FADEIN, WIPE_TYPE_FADEIN, WIPE_FADE_BLACK, 16, 1, HEAPID_TRADELIST);



	BgGraphicSet( wk );

	// VBlank関数セット
	sys_VBlankFuncChange( VBlankFunc, wk );	



	// OBJキャラ、パレットマネージャー初期化
	char_pltt_manager_init();

	// CellActorシステム初期化
	InitCellActor(wk);
	
	// CellActro表示登録
	SetCellActor(wk);

	// BMPWIN登録・描画
	TradeList_BmpMessageSet(wk->bgl,wk->TradeListWin, wk->param->config);

	//FIELDSYS_WORKにtradelist_workを登録
	wk->fsys = wk->param->fsys;
	SetFieldSys_in_TradeWorkPtr(wk->fsys, wk);

	// 通信待機中…
	TradeListWindowPrint(
		&wk->TradeListWin[BMP_M_MES3_WIN],
		mes_dstrade_04_01,
		FONT_TALK,
		wk->MsgManager,
		wk->PokeNameWordSet
	);

	// 通信コマンドを交換リスト用に変更
	CommCommandTradeListInitialize(wk->fsys);

	// 親だったら「こうかん通信中」にビーコン書き換え
//	if(CommGetCurrentID()==0){
//		Union_BeaconChange( UNION_PARENT_MODE_TRADENOW );
//	}
		
	GF_BGL_VisibleSet( GF_BGL_FRAME0_M, VISIBLE_ON );
	GF_Disp_GX_VisibleControl(GX_PLANEMASK_OBJ, VISIBLE_ON);	//OBJ面ＯＮ
	
	CommErrorCheck(HEAPID_TRADELIST, wk->bgl);

	WirelessIconEasy();


	// サウンドデータセット(シーンが変更されない時は何もしない)
	// "再生するBGMを固定にしているので、"
	// "ポケモン交換リスト画面がユニオンルーム以外から呼ばれることがあってはダメ！"
	if( GF_RTC_IsNightTime() == FALSE ){			//FALSE=昼、TRUE=夜
		Snd_DataSetByScene( SND_SCENE_FIELD, SEQ_PC_01, 1 );
	}else{
		Snd_DataSetByScene( SND_SCENE_FIELD, SEQ_PC_02, 1 );
	}

	return PROC_RES_FINISH;
}


//------------------------------------------------------------------
/**
 * ポケモンアイコンを転送する（ポケモンの名前の時だけ）
 *
 * @param   chara	キャラクターファイルアドレス
 * @param   pal		パレットファイルアドレス
 * @param   pokeno	ポケモンの開発NO
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void TransPokeIconCharaPal( NNSG2dCharacterData *chara, int pokeno, int form, int tamago, int no, CLACT_WORK_PTR icon)
{
	u8 *pokepal;

	// キャラクター転送
	GX_LoadOBJ(chara->pRawData, (POKEICON_VRAM_OFFSET+no*POKEICON_TRANS_CELL)*0x20, POKEICON_TRANS_SIZE);
	OS_Printf("アイコンキャラ転送NO. %d\n",no);
	
	
	// パレット設定
	CLACT_PaletteOffsetChg( icon,  PokeIconPalNumGet( pokeno, form, tamago )+POKEICON_PAL_OFFSET);

//	pokepal = (u8*)pal->pRawData;
//	GX_LoadOBJPltt((void*)(pokepal + PokeIconPaletteIDGet(pokeno)*0x20), (POKEICON_PAL_OFFSET+no)*0x20, 0x20);

}

static const STRCODE endstr[]={ya_,me_,ru_,EOM_};

//------------------------------------------------------------------
/**
 * 自分の通信相手の名前描画
 *
 * @param   bgl		
 * @param   win		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void TrainerNamePrint( GF_BGL_BMPWIN *win )
{
	STRBUF *MyNameBuf, *FriendNameBuf, *EndBuf;
	// Todo 名前の取得方法のインターフェースがはっきりした組み替える
	// 
	MYSTATUS *mystatus, *friendstatus;

	

	mystatus     = CommInfoGetMyStatus(CommGetCurrentID());
	friendstatus = CommInfoGetMyStatus(CommGetCurrentID()^1);
	
	MyNameBuf     = MyStatus_CreateNameString(mystatus,     HEAPID_TRADELIST);
	FriendNameBuf = MyStatus_CreateNameString(friendstatus, HEAPID_TRADELIST);

	EndBuf    = STRBUF_Create( TRADELISTSTR_MAX, HEAPID_TRADELIST );
	STRBUF_SetStringCode( EndBuf, endstr );
	

	// 自分の名前
	TradeListPrint(&win[BMP_M_MYNAME_WIN], MyNameBuf, TRADELIST_NAME_W, MSG_ALLPUT, CENTER_PRINT,1);
	// 相手の名前
	TradeListPrint(&win[BMP_M_FRIENDNAME_WIN], FriendNameBuf, TRADELIST_NAME_W, MSG_ALLPUT, CENTER_PRINT,1);
	// 「おわり」
	TradeListPrint(&win[BMP_M_ENDSTR_WIN], EndBuf, TRADELIST_ENDSTR_W, MSG_ALLPUT, CENTER_PRINT,1);

	STRBUF_Delete( EndBuf );
	STRBUF_Delete( FriendNameBuf );
	STRBUF_Delete( MyNameBuf);
}

static const STRCODE testname[]={HU_,SI_,GI_,DA_,NE_,EOM_};
static const STRCODE testlevel[]={L__,v__,spc_,n1_,n0_,n0_,EOM_};
static const STRCODE testmotimono[]={mo_,ti_,mo_,no_,EOM_};
static const STRCODE testitem[]={HA_,bou_,BA_,bou_,ME_,bou_,RU_,EOM_};

//------------------------------------------------------------------
/**
 * $brief   下画面文字表示
 *
 * @param   win			
 * @param   cardno		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void PokemonInfoSubPrint( TRADELIST_WORK *wk, int page )
{
	STRBUF *MotimonoBuf;

	// もちもの
	MotimonoBuf = MSGMAN_AllocString( wk->MsgManager, mes_dstrade_05_05 );

	TradeListPrint(&wk->TradeListWin[BMP_S_MOTIMONO0_WIN+page], MotimonoBuf, SUB_MOTIMONOSTR_W, MSG_ALLPUT, LEFT_PRINT,0);

	STRBUF_Delete( MotimonoBuf );
	               
}




//------------------------------------------------------------------
/**
 * @brief   ステータス画面からの復帰用処理
 *
 * @param   wk		
 *
 * @retval  none	
 */
//------------------------------------------------------------------
static void TradeListReturn( TRADELIST_WORK *wk )
{
	// VRAM設定
	VramBankSet();

	// BGバンク再設定
	BgInit( wk->bgl );

	// グラフィック転送
	BgGraphicSet( wk );

	// ポケモン名描画
	PokemonName_Get_Write( wk );

	// トレーナー名
	TrainerNamePrint( wk->TradeListWin );

	// メイン画面の会話ウインドウ処理
	TalkWinGraphicSet( wk->bgl, GF_BGL_FRAME0_M, TALKWIN_FRAME_OFFSET, 10, CONFIG_GetWindowType(wk->param->config), HEAPID_TRADELIST );           
	MenuWinGraphicSet( wk->bgl, GF_BGL_FRAME0_M, MENUWIN_FRAME_OFFSET, 11, 0, HEAPID_TRADELIST );


	// ポケモンを選んでください
	TradeListWindowPrint(
		&wk->TradeListWin[BMP_M_MES1_WIN],
		mes_dstrade_02_01,FONT_TALK,
		wk->MsgManager,
		wk->PokeNameWordSet
	);


	// 上画面ON
	GF_BGL_VisibleSet( GF_BGL_FRAME0_S, VISIBLE_ON );
	GF_BGL_VisibleSet( GF_BGL_FRAME1_S, VISIBLE_ON );
	GF_BGL_VisibleSet( GF_BGL_FRAME2_S, VISIBLE_ON );
	GF_Disp_GXS_VisibleControl(GX_PLANEMASK_OBJ, VISIBLE_ON);	//OBJ面ＯＮ

	// 下画面ON
	GF_BGL_VisibleSet( GF_BGL_FRAME0_M, VISIBLE_ON );
	GF_BGL_VisibleSet( GF_BGL_FRAME1_M, VISIBLE_ON );
	GF_BGL_VisibleSet( GF_BGL_FRAME2_M, VISIBLE_ON );
	GF_BGL_VisibleSet( GF_BGL_FRAME3_M, VISIBLE_ON );
	GF_Disp_GX_VisibleControl(GX_PLANEMASK_OBJ,  VISIBLE_ON);	//OBJ面ＯＮ



	// キャラパレットマネージャー初期化
	char_pltt_manager_init();

	// CellActorシステム初期化
	InitCellActor(wk);

	// CellActro表示登録
	SetCellActor(wk);


	// アイコンデータを読み込んで転送
	LoadPokeIcon( wk->MyPokeParty,     0, wk);
	LoadPokeIcon( wk->FriendPokeParty, 6, wk);

	// カーソル表示ON
	CLACT_SetDrawFlag(wk->clActWork[0], 1);
	CLACT_SetDrawFlag(wk->clActWork[1], 1);

	// VBlank関数セット
	sys_VBlankFuncChange( VBlankFunc, wk );	

}

//------------------------------------------------------------------
/**
 * @brief   ポケモン名前取得＆描画
 *
 * @param   wk		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void PokemonName_Get_Write( TRADELIST_WORK *wk)
{

	// ポケモン名前登録
	Regist_WordSetPokeName(wk->PokeNameWordSet, wk->MyPokeParty,     0 );
	Regist_WordSetPokeName(wk->PokeNameWordSet, wk->FriendPokeParty, 6 );
	
	// ポケモン名前Bmp描画
	Print_MainPokeName(&wk->TradeListWin[BMP_M_MYPOKENAME0_WIN],wk->PokeNameWordSet,wk->MsgManager,wk->MyPokeParty,     0);
	Print_MainPokeName(&wk->TradeListWin[BMP_M_FRIENDPOKENAME0_WIN],wk->PokeNameWordSet,wk->MsgManager,wk->FriendPokeParty, 6);

	TradeListMakeScreenSet(wk->bgl, PokeParty_GetPokeCount(wk->MyPokeParty), PokeParty_GetPokeCount(wk->FriendPokeParty));

}

//--------------------------------------------------------------------------------------------
/**
 * プロセス関数：メイン
 *
 * @param	proc	プロセスデータ
 * @param	seq		シーケンス
 *
 * @return	処理状況
 */
//--------------------------------------------------------------------------------------------

PROC_RESULT TradeListProc_Main( PROC * proc, int * seq )
{
	TRADELIST_WORK * wk  = PROC_GetWork( proc );
	PROC_RESULT    proc_result = PROC_RES_CONTINUE;

	switch( *seq ){
	case SEQ_IN:
		if( WIPE_SYS_EndCheck()){
			*seq = SEQ_MAIN;
			TrainerNamePrint( wk->TradeListWin );
			OS_Printf("ポケパーティー = %d\n",PokeParty_GetPokeCount(wk->MyPokeParty));
		}
		break;

	case SEQ_MAIN:
		switch(wk->tradeseq){
		// ポケモンデータ交換
		case TRADELIST_SEQ_POKEMON_EXCHANGE:
			wk->tradeseq = TradeListPokemonExchange(wk);
			break;
		//メインループ
		case TRADELIST_SEQ_MAIN:
			wk->tradeseq = TradeListMain(wk);
			TouchFunc(wk);
			break;
		// 交換リスト終了
		case TRADELIST_SEQ_END:
			WIPE_SYS_Start(WIPE_PATTERN_WMS, WIPE_TYPE_FADEOUT, WIPE_TYPE_FADEOUT, WIPE_FADE_BLACK, 8, 1, HEAPID_TRADELIST);
			*seq = SEQ_OUT;
			break;

		// ステータス遷移用フェード
		case TRADELIST_SEQ_STATUS_INFADE:
			WIPE_SYS_Start(WIPE_PATTERN_WMS, WIPE_TYPE_FADEOUT, WIPE_TYPE_FADEOUT, WIPE_FADE_BLACK, 8, 1, HEAPID_TRADELIST);
			wk->tradeseq = TRADELIST_SEQ_STATUS_INFADE_WAIT;
			break;
		// フェード待ち
		case TRADELIST_SEQ_STATUS_INFADE_WAIT:
			if( WIPE_SYS_EndCheck() ){	
				
				PokeIconFree( wk );
				FreeClact( wk );
				BgExit( wk->bgl );
				wk->subseqflag = 1;
				wk->tradeseq = TRADELIST_SEQ_STATUS;

				OS_Printf("CursorPos0 = %d, CursorPos1 = %d\n", wk->cursor_pos[0], wk->cursor_pos[1]);
				poke_status_setup( wk, wk->cursor_pos[0]/6 );
			}
			break;
		// ステータス画面実行
		case TRADELIST_SEQ_STATUS:
			if( ProcMain( wk->subproc ) ){
				PROC_Delete( wk->subproc );
				
				// BG･OAMシステム再構築
				TradeListReturn(wk);
				wk->subseqflag = 0;
				wk->cursor_pos[0] = wk->statusParam.pos+wk->status_side*6;

				// カーソル・下画面反映
				CursorSubLcd_Update(wk);
				CursorPosChange(wk->cursor_pos[0],wk->clActWork[0], 0);

				WirelessIconEasy();
				
				wk->tradeseq = TRADELIST_SEQ_STATUS_OUTFADE;
			}
			break;

		// 復帰フェード
		case TRADELIST_SEQ_STATUS_OUTFADE:
			WIPE_SYS_Start(WIPE_PATTERN_WMS, WIPE_TYPE_FADEIN, WIPE_TYPE_FADEIN, WIPE_FADE_BLACK, 8, 1, HEAPID_TRADELIST);
			wk->tradeseq = TRADELIST_SEQ_STATUS_OUTFADE_WAIT;
			break;

		// 復帰フェード待ち
		case TRADELIST_SEQ_STATUS_OUTFADE_WAIT:
			if( WIPE_SYS_EndCheck() ){	
				wk->tradeseq = TRADELIST_SEQ_MAIN;
			}
			break;
		}

		break;

	// メインシーケンス終了
	case SEQ_OUT:
		if( WIPE_SYS_EndCheck() ){
			proc_result = PROC_RES_FINISH;
		}
		break;
	}
	
	// ステータス画面が呼ばれているときは実行しない
	if(!wk->subseqflag){
		// サブ画面BG3面スクロール処理
		SubLCD_ScrollFunc( wk );
		// セルアクター常駐関数
		CLACT_Draw( wk->clactSet );
	}

	CommErrorCheck(HEAPID_TRADELIST, wk->bgl);					// 通信エラーチェック

	return proc_result;
}


//------------------------------------------------------------------
/**
 * WordSetにポケモンの名前を登録する
 *
 * @param   wordset		
 * @param   party		
 * @param   start		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void Regist_WordSetPokeName(WORDSET *wordset, POKEPARTY *party, int start )
{
	int i;
	for(i=0;i<PokeParty_GetPokeCount(party);i++){
		WORDSET_RegisterPokeNickName( wordset, i+start, PPPPointerGet(PokeParty_GetMemberPointer(party, i)));
	}
}

//------------------------------------------------------------------
/**
 * ポケモン１２体分を転送する
 *
 * @param   win		
 * @param   wordset		
 * @param   manager		
 * @param   party		
 * @param   start		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void Print_MainPokeName(GF_BGL_BMPWIN *win, WORDSET *wordset, MSGDATA_MANAGER *manager, POKEPARTY *party, int start )
{
	int i;
	for(i=0;i<PokeParty_GetPokeCount(party);i++){
		STRBUF *name = MSGDAT_UTIL_AllocExpandString( wordset, manager, mes_dstrade_01_02+start+i, HEAPID_TRADELIST );
		TradeListPrint(&win[i], name, TRADELIST_POKENAME_W, MSG_ALLPUT, CENTER_PRINT,0);
		STRBUF_Delete( name );
	}
}

//------------------------------------------------------------------
/**
 * @brief   ポケモンアイコンの転送
 *
 * @param   party		
 * @param   start		
 * @param   wk		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void LoadPokeIcon(POKEPARTY *party, int start, TRADELIST_WORK *wk)
{
	int i;
	int pos;
	
	for(i=0;i<PokeParty_GetPokeCount(party);i++){
		pos = i+start;

		wk->PokeIconBuf[pos] = ArcUtil_CharDataGet( ARC_POKEICON, 
			PokeIconCgxArcIndexGetByMonsNumber( wk->pokeInfo[pos].exist, wk->pokeInfo[pos].tamago, wk->pokeInfo[pos].form ), 
			0, 
			&wk->PokeIconCharaDat[pos], 
			HEAPID_TRADELIST );
//		OS_Printf("pos %d: PokeIconBuf size = %d\n",pos,sys_GetMemoryBlockSize(wk->PokeIconBuf[pos]));
		DC_FlushRange(wk->PokeIconCharaDat[pos]->pRawData,0x20*4*4);
		TransPokeIconCharaPal(wk->PokeIconCharaDat[pos], wk->pokeInfo[pos].exist, 
							  wk->pokeInfo[pos].form, 
							  wk->pokeInfo[pos].tamago, 
							  pos, wk->PokeIconActWork[pos]);
		CLACT_SetDrawFlag(wk->PokeIconActWork[pos], 1);

		// アイテムアイコンの表示・メール・アイテムのどちらか
		if(wk->pokeInfo[pos].item==0){
			// アイテムは無いので非表示
			CLACT_SetDrawFlag(wk->PokeItemActWork[pos], 0);
		}else{
			// アイテムかメールにあわせて画像チェンジ
			CLACT_SetDrawFlag(wk->PokeItemActWork[pos], 1);
			CLACT_AnmChg( wk->PokeItemActWork[pos], 3+wk->pokeInfo[pos].item-1 );
		}
		
		// ボールカスタマイズをしているか？
		if(wk->pokeInfo[pos].customball==0){
			CLACT_SetDrawFlag(wk->PokeCBallActWork[pos], 0);
		}else{
			// してる（カスタムボール表示）
			CLACT_SetDrawFlag(wk->PokeCBallActWork[pos], 1);
			CLACT_AnmChg( wk->PokeCBallActWork[pos], 21 );
		}
	}
	
	// 残りは全て非表示
	for(;i<6;i++){
		CLACT_SetDrawFlag(wk->PokeIconActWork[i+start], 0);
		CLACT_SetDrawFlag(wk->PokeItemActWork[i+start], 0);
		CLACT_SetDrawFlag(wk->PokeCBallActWork[i+start], 0);
	}
}

enum{
	EXCHANGE_SEQ_BEFORE_SYNCRO=0,
	EXCHANGE_SEQ_BEFORE_SYNCRO_WAIT,
	EXCHANGE_SEQ_SAVE_WAIT_RECV,
	EXCHANGE_SEQ_SAVE_WAIT_CLEAR,
	EXCHANGE_SEQ_SAVE_START,
	EXCHANGE_SEQ_SAVE_WAIT,
	EXCHANGE_SEQ_START_PRE_SYNC,
	EXCHANGE_SEQ_START_PRE_SYNC_WAIT,
	EXCHANGE_SEQ_START,
	EXCHANGE_SEQ_WAIT,
	EXCHANGE_SEQ_FINISH,
	EXCHANGE_SEQ_DATA_SETUP,
	EXCHANGE_SEQ_FRIENDLIST,
	EXCHANGE_SEQ_FRIENDLIST_END,
	EXCHANGE_SEQ_PERAPVOICE,
	EXCHANGE_SEQ_PERAPVOICE_END,

	EXCHANGE_SEQ_IN,
	EXCHANGE_SEQ_FADE1,
	EXCHANGE_SEQ_FADE2,
	EXCHANGE_SEQ_FADE3,
	EXCHANGE_SEQ_FADE4,
};

#define TRADELIST_COMM_SYNCHRONIZE1_NO	( 80 )
#define TRADELIST_COMM_SYNCHRONIZE2_NO	( 81 )

#define TRADE_PARENT_WAIT				( 60 )
//------------------------------------------------------------------
/**
 * 交換リストポケモンデータ共有処理
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int TradeListPokemonExchange( TRADELIST_WORK *wk )
{
	// タイムアウト処理
	TimeoutErrorCheck( wk );
	
	
	switch(wk->exchangeseq){

	// 交換行う前に通信同期をする（セーブしないので、ここで交換デモを待つ）
	case EXCHANGE_SEQ_BEFORE_SYNCRO:
		CommTimingSyncStart( TRADELIST_COMM_SYNCHRONIZE1_NO );

		// ソフトリセット不可能にする
		sys.DontSoftReset = 1;
		
		// 時間アイコン表示
		TimeIconAdd( wk );

		wk->exchangeseq++;
		break;

	// 最初の通信同期待ち
	case EXCHANGE_SEQ_BEFORE_SYNCRO_WAIT:
		if(CommIsTimingSync(TRADELIST_COMM_SYNCHRONIZE1_NO)){
			OS_Printf("交換リスト呼び出し %d回目\n",wk->param->times);
			if(wk->param->times==0){
				wk->exchangeseq = EXCHANGE_SEQ_START_PRE_SYNC;
				OS_Printf("セーブ無しでデータ送信\n");
			}else{
				wk->exchangeseq = EXCHANGE_SEQ_SAVE_WAIT_RECV;
				OS_Printf("セーブへ\n");
			}

			if(CommGetCurrentID()==0){
				// １秒以内でセーブまでのズレを生成する
				TradeListCommSend( CommGetCurrentID(), CT_SAVE_WAIT_TIME, gf_p_rand(TRADE_PARENT_WAIT)+3);
				OS_Printf("親機なのでセーブずらしコマンド送信\n");
			}
			TradeListCommSpRibbonDate(  wk->savedata );
			OS_Printf("リボン情報送信\n");

			// タイムアウトカウント開始
			TimeoutStart(wk);
#ifdef DEBUG_TIMEOUT
			wk->exchangeseq = 300;
#endif

		}
		break;
	// セーブを行う時はまずは親機からセーブまでの待機時間を受信しているか確認する
	case EXCHANGE_SEQ_SAVE_WAIT_RECV:
		if(wk->savePreWait!=0){
			OS_Printf("savePreWait = %d\n", wk->savePreWait);
			wk->exchangeseq++;
		}
		break;
	case EXCHANGE_SEQ_SAVE_WAIT_CLEAR:

		// セーブまでの待機時間は親機が乱数で渡すためタイミングが来る度にズレる
		wk->savePreWait--;
		if(wk->savePreWait==0){
			wk->exchangeseq = EXCHANGE_SEQ_SAVE_START;
			OS_Printf("セーブ乱数待ち終了\n");
		}
		break;

	// 2回目以降の交換リストはセーブを行う
	case EXCHANGE_SEQ_SAVE_START:
		OS_Printf("セーブ開始\n");
		CommSyncronizeSaveInit( &wk->commSaveSeq );
		wk->exchangeseq++;
		break;
	case EXCHANGE_SEQ_SAVE_WAIT:
		if(CommSyncronizeSave( wk->savedata, SVBLK_ID_MAX, &wk->commSaveSeq )){
			wk->exchangeseq++;
		}
		break;

	// ポケモンデータ送信開始前の同期
	case EXCHANGE_SEQ_START_PRE_SYNC:
        CommSetWifiBothNet(TRUE); // wifiの通信を非同期から同期に ohno
		CommTimingSyncStart( TRADELIST_COMM_SYNCHRONIZE2_NO );
		wk->exchangeseq++;
		break;
	case EXCHANGE_SEQ_START_PRE_SYNC_WAIT:
		if(CommIsTimingSync(TRADELIST_COMM_SYNCHRONIZE2_NO)){
			wk->exchangeseq++;
		}
		break;

	// データ送受信開始
	case EXCHANGE_SEQ_START:
		wk->exchange_work         = 0;
		wk->exchange_finish       = 0;
		wk->exchange_friend_count = 0;
		if(CommGetCurrentID()==1){
			// 大容量送信開始
			TradeListCommSendPokeData(CommGetCurrentID(), wk->MyPokeParty, wk->exchange_work);
			wk->exchange_work++;
		}
		wk->exchangeseq++;
//		wk->exchangeseq = EXCHANGE_SEQ_IN;

		break;
	case EXCHANGE_SEQ_WAIT:
		if(wk->exchange_finish!=0){
//			if(CommGetCurrentID()==0){
//				TradeListCommSend(CommGetCurrentID(),CT_TRADE_START, 0);
//			}
			wk->exchangeseq = EXCHANGE_SEQ_FINISH;
		}
		break;
	case EXCHANGE_SEQ_FINISH:
//		if(wk->exchange_finish==2){
			wk->exchangeseq++;

			// ポケモンの名前取得＆BMP描画
			PokemonName_Get_Write(wk);

//		}
		break;
	// 取得したデータを下に表示用データを集める
	case EXCHANGE_SEQ_DATA_SETUP:
		{
				int i,item;
				for(i=0;i<13;i++){
					wk->pokeInfo[i].exist = 0;
				}
				for(i=0;i<PokeParty_GetPokeCount(wk->MyPokeParty);i++){
					POKEMON_PARAM *pp = PokeParty_GetMemberPointer(wk->MyPokeParty, i);

					// 自分のポケモン
					GetPokeInfo(pp, &wk->pokeInfo[i]);
//					OS_Printf("%d cball = %d\n", i, wk->pokeInfo[i].customball);
					
				}
				for(i=0;i<PokeParty_GetPokeCount(wk->FriendPokeParty);i++){
					POKEMON_PARAM *pp = PokeParty_GetMemberPointer(wk->FriendPokeParty, i);

					// 相手のポケモン
					GetPokeInfo( pp, &wk->pokeInfo[i+6] );
//					OS_Printf("%d cball = %d\n", i+6, wk->pokeInfo[i+6].customball);
				}
				wk->pokeInfo[12].exist = 1;
		}
		wk->exchangeseq++;
		break;
	case EXCHANGE_SEQ_FRIENDLIST:
		CommSendFriendList( CommInfoGetMyStatus(CommGetCurrentID()), wk->friendlist, &wk->SendList );
		wk->exchangeseq++;
		break;
	case EXCHANGE_SEQ_FRIENDLIST_END:
		if(wk->exchange_finish==3){
			wk->exchangeseq++;
		}
		break;
	case EXCHANGE_SEQ_PERAPVOICE:
		CommSendPerapVoice( SaveData_GetPerapVoice(wk->savedata) );
		wk->exchangeseq++;
		break;
	case EXCHANGE_SEQ_PERAPVOICE_END:
		if(wk->exchange_finish==4){
			wk->exchangeseq++;
			GF_Disp_GX_VisibleControl(GX_PLANEMASK_OBJ,  VISIBLE_OFF);	//OBJ面ＯＮ

			// アイコンデータを読み込んで転送
			LoadPokeIcon( wk->MyPokeParty,     0, wk);
			LoadPokeIcon( wk->FriendPokeParty, 6, wk);

			{
				int i;
				for(i=0;i<2;i++){
					CLACT_SetDrawFlag( wk->clActWork[i], 1 );
				}
			}
		}
//		TimeWaitIconDel(wk->timeWaitWork);
		break;
	case EXCHANGE_SEQ_IN:
		ChangeBrightnessRequest( 8, 0, -16, PLANEMASK_BG1|PLANEMASK_BG2|PLANEMASK_BG3|PLANEMASK_OBJ, MASK_MAIN_DISPLAY );
		GF_BGL_VisibleSet( GF_BGL_FRAME1_M, VISIBLE_ON );
		GF_BGL_VisibleSet( GF_BGL_FRAME2_M, VISIBLE_ON );
		GF_BGL_VisibleSet( GF_BGL_FRAME3_M, VISIBLE_ON );
		GF_Disp_GX_VisibleControl(GX_PLANEMASK_OBJ,  VISIBLE_ON);	//OBJ面ＯＮ
		
		wk->exchangeseq++;
		break;
	case EXCHANGE_SEQ_FADE1:
		if( IsFinishedBrightnessChg(MASK_MAIN_DISPLAY) ){
			POKEMON_PARAM *pp = PokeParty_GetMemberPointer(wk->MyPokeParty, 0);

			// 下画面用ポケモングラフィック転送
			wk->vblankreq = TransPokeGra_SubLcd(0,pp, wk->PokeGra[0], &wk->PokeGraSsa[0] );
			TransPokeStr_SubLcd(wk->TradeListWin,0,wk->MyPokeParty, 0, wk);
			wk->exchangeseq++;
		}
		break;
	case EXCHANGE_SEQ_FADE2:
		ChangeBrightnessRequest( 8, 0, -16, PLANEMASK_BG0|PLANEMASK_BG1|PLANEMASK_BG2|PLANEMASK_OBJ, MASK_SUB_DISPLAY );
		GF_BGL_VisibleSet( GF_BGL_FRAME0_S, VISIBLE_ON );
		GF_BGL_VisibleSet( GF_BGL_FRAME1_S, VISIBLE_ON );
		GF_BGL_VisibleSet( GF_BGL_FRAME2_S, VISIBLE_ON );
		GF_Disp_GXS_VisibleControl(GX_PLANEMASK_OBJ, VISIBLE_ON);	//OBJ面ＯＮ

		wk->exchangeseq++;

		// 時間アイコン表示
		TimeIconDel( wk );

		break;
	case EXCHANGE_SEQ_FADE3:
		if( IsFinishedBrightnessChg(MASK_SUB_DISPLAY) ){

			BmpTalkWinClear( &wk->TradeListWin[BMP_M_MES3_WIN], WINDOW_TRANS_ON );

			// ポケモンを選んでください
			GF_BGL_ScrFill(	wk->bgl, GF_BGL_FRAME0_M, 0, 0, 0, 32, 24,  0);
			TradeListWindowPrint(
				&wk->TradeListWin[BMP_M_MES1_WIN],
				mes_dstrade_02_01,FONT_TALK,
				wk->MsgManager,
				wk->PokeNameWordSet
			);

			OS_Printf("ポケパーティー = %d\n",PokeParty_GetPokeCount(wk->MyPokeParty));

			// ソフトリセット可能にする
			sys.DontSoftReset = 0;


			return TRADELIST_SEQ_MAIN;
		}
		break;
	}

	return TRADELIST_SEQ_POKEMON_EXCHANGE;
}


//------------------------------------------------------------------
/**
 * @brief   てもちポケモンの表示に使う情報を集める
 *
 * @param   pp		
 * @param   info		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void GetPokeInfo( POKEMON_PARAM *pp, POKE_INFO* info )
{
	int fastflag, item;

	// 高速化フラグON
	fastflag = PokeParaFastModeOn( pp );
	info->monsball   = PokeParaGet( pp, ID_PARA_get_ball,    NULL );
	info->exist      = PokeParaGet( pp, ID_PARA_monsno,      NULL );
	info->form       = PokeParaGet( pp, ID_PARA_form_no,     NULL );
	info->tamago     = PokeParaGet( pp, ID_PARA_tamago_flag, NULL );
	info->sex        = PokeParaGet( pp, ID_PARA_sex,         NULL );
	info->customball = PokeParaGet( pp, ID_PARA_cb_id,       NULL );
	item             = PokeParaGet( pp, ID_PARA_item,        NULL );

	// 高速化フラグOFF
	PokeParaFastModeOff( pp, fastflag );

	// 反転フラグ取得
	if( info->exist!=0 ){
		info->reverse = PokePersonalParaGet( info->exist, ID_PER_reverse );
	}

	// メールチェック
	if(item!=0){
		info->item = ItemMailCheck( item )+1;	// メールだったら２、itemだったら１
	}
	

}
//------------------------------------------------------------------
/**
 * @brief   右側のパネルを描画する
 *
 * @param   wk		
 *
 * @retval  static		
 */
//------------------------------------------------------------------
static void SubLcd_RightPanelOn( TRADELIST_WORK *wk, int pos )
{
	POKEMON_PARAM *pp = PokeParty_GetMemberPointer(wk->FriendPokeParty, pos%6 );

	// 10x10ポケモン画像転送
	wk->vblankreq = TransPokeGra_SubLcd(1, pp,wk->PokeGra[pos/6], &wk->PokeGraSsa[pos/6] );

	TransPokeStr_SubLcd(wk->TradeListWin,1,wk->FriendPokeParty, pos%6, wk);
	// モンスターボールチェンジ
	CLACT_AnmChg( wk->SubLCDIconActWork[3], wk->pokeInfo[pos].monsball+CELL_MONSTER_BALL_NO-1 );


}


//------------------------------------------------------------------
/**
 * @brief    下画面を転送する
 *
 * @param   wk		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void CursorSubLcd_Update(TRADELIST_WORK *wk)
{
	// カーソル反映処理（移動してたら下画面の書き換えへ）
		if(wk->cursor_pos[0]!=12){
			// ポケモン画像転送
			if(wk->cursor_pos[0]<6){
				POKEMON_PARAM *pp = PokeParty_GetMemberPointer(wk->MyPokeParty, wk->cursor_pos[0] );

				// 10x10ポケモン画像転送
				wk->vblankreq = TransPokeGra_SubLcd(0, pp, wk->PokeGra[wk->cursor_pos[0]/6], &wk->PokeGraSsa[wk->cursor_pos[0]/6] );
				TransPokeStr_SubLcd(wk->TradeListWin,0,wk->MyPokeParty,    wk->cursor_pos[0], wk);

				// 右側非表示
				PokeStr_SubLcdOff(wk->TradeListWin, 1, wk);
				CLACT_SetDrawFlag(wk->SubLCDIconActWork[3], 0);	

			}else{
				SubLcd_RightPanelOn( wk, wk->cursor_pos[0] );
				// 左側非表示
				PokeStr_SubLcdOff(wk->TradeListWin, 0, wk);
				CLACT_SetDrawFlag(wk->SubLCDIconActWork[2], 0);
			}
		}
		

}



//------------------------------------------------------------------
/**
 * 交換リストメインループ
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int TradeListMain( TRADELIST_WORK *wk )
{
	// カーソル移動
	if(wk->func!=NULL){
		wk->inputmode = wk->func(wk);
	}
	switch(wk->inputmode){
	case MODE_NORMAL:
		break;
	case MODE_END_SELECT:
		return TRADELIST_SEQ_END;
		break;
	case MODE_TRADE_SELECT:
		break;
	case MODE_STATUS_SELECT:
		return TRADELIST_SEQ_STATUS_INFADE;
		break;
	}


	// 自分のカーソル移動(カーソルが移動したら下画面のポケモン表示を変更する）
	if(ViewChange(&wk->CommWork[0], &wk->cursor_pos[0], wk->clActWork[0], wk->pokeInfo,0)){
		CursorSubLcd_Update( wk );
	}

	// 相手のカーソル移動
	ViewChange(&wk->CommWork[1], &wk->cursor_pos[1], wk->clActWork[1], wk->pokeInfo,1);
	CursorColTrans(&wk->CursorPal);


	// カーソル位置座標を送信する
	TradeListCommDiffSend( wk, CT_CURSOR_POS, wk->cursor_pos[0]);

	return TRADELIST_SEQ_MAIN;
}



//------------------------------------------------------------------
/**
 * @brief   セルアクター周りのシステム解放
 *
 * @param   wk		
 *
 * @retval  none
 */
//------------------------------------------------------------------
static void FreeClact( TRADELIST_WORK *wk )
{
	int i;
	// セルアクターリソース解放
	// キャラ転送マネージャー破棄
	CLACT_U_CharManagerDelete(wk->resObjTbl[MAIN_LCD][CLACT_U_CHAR_RES]);
	CLACT_U_CharManagerDelete(wk->resObjTbl[SUB_LCD][CLACT_U_CHAR_RES]);

	// パレット転送マネージャー破棄
	CLACT_U_PlttManagerDelete(wk->resObjTbl[MAIN_LCD][CLACT_U_PLTT_RES]);
	CLACT_U_PlttManagerDelete(wk->resObjTbl[SUB_LCD][CLACT_U_PLTT_RES]);
		
	// キャラ・パレット・セル・セルアニメのリソースマネージャー破棄
	for(i=0;i<CLACT_RESOURCE_NUM;i++){
		CLACT_U_ResManagerDelete(wk->resMan[i]);
	}
	// セルアクターセット破棄
	CLACT_DestSet(wk->clactSet);

	//OAMレンダラー破棄
	REND_OAM_Delete();

	// キャラマネージャー、パレットマネージャー削除
	DeleteCharManager();
	DeletePlttManager();

}

//------------------------------------------------------------------
/**
 * @brief   ポケモンアイコン画像の解放
 *
 * @param   wk		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void PokeIconFree( TRADELIST_WORK *wk )
{
	int i;
	
	for(i=0;i<PokeParty_GetPokeCount(wk->MyPokeParty);i++){
		sys_FreeMemoryEz( wk->PokeIconBuf[i] );
	}
	for(i=0;i<PokeParty_GetPokeCount(wk->FriendPokeParty);i++){
		sys_FreeMemoryEz( wk->PokeIconBuf[i+6] );
	}


}


//--------------------------------------------------------------------------------------------
/**
 * プロセス関数：終了
 *
 * @param	proc	プロセスデータ
 * @param	seq		シーケンス
 *
 * @return	処理状況
 */
//--------------------------------------------------------------------------------------------
PROC_RESULT TradeListProc_End( PROC * proc, int * seq )
{
	TRADELIST_WORK  *wk          = PROC_GetWork( proc );
	TRADELIST_PARAM *param = PROC_GetParentWork(proc);

	int i;


	// 交換するかしないか？
	param->result = wk->result;


	// ポケモンアイコン解放
	PokeIconFree( wk );

	// もちもの文字列解放
	STRBUF_Delete(wk->MotimonoStr);

	sys_FreeMemoryEz(wk->FriendPokeParty);

	// セルアクター周りのシステム解放
	FreeClact( wk );

	// BMPウィンドウ開放
	TradeListBmpExit(wk->TradeListWin);

	// BGL削除
	BgExit( wk->bgl );

	// BGL解放
	sys_FreeMemory( HEAPID_TRADELIST, wk->bgl );


	// メッセージマネージャー・ワードセットマネージャー解放
	MSGMAN_Delete( wk->MsgManager );
	WORDSET_Delete( wk->SubLcdWordSet );
	WORDSET_Delete( wk->WindowStrWordSet );
	WORDSET_Delete( wk->PokeNameWordSet );

	// STRBUF解放
	STRBUF_Delete(wk->MyName);

	PROC_FreeWork( proc );				// ワーク開放

	sys_VBlankFuncChange( NULL, NULL );		// VBlankセット

	sys_DeleteHeap( HEAPID_TRADELIST );

	// この関数呼び出し時の2syncだけは通信エラー画面に飛ばせない

	return PROC_RES_FINISH;
}


//--------------------------------------------------------------------------------------------
/**
 * VBlank関数
 *
 * @param	none
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void VBlankFunc( void * work )
{
	TRADELIST_WORK *wk = (TRADELIST_WORK*)work;

	// BGL処理
	GF_BGL_VBlankFunc( wk->bgl );

	if(wk->vblankreq){
		int side = wk->vblankreq - 1;
		// OAM用VRAMに転送
		GXS_LoadOBJ( wk->PokeGra[side], POKEGRA_VRAM_OFFSET + side*POKEGRA_VRAM_SIZE, POKEGRA_VRAM_SIZE);

		// パレット転送
		ArcUtil_PalSet( wk->PokeGraSsa[side].arc_no, wk->PokeGraSsa[side].index_pal, 
						PALTYPE_SUB_OBJ, 0x20*(2+side), 32, HEAPID_TRADELIST );
		
		wk->vblankreq = 0;
	}

	// セルアクター
	// Vram転送マネージャー実行
	DoVramTransferManager();

	// レンダラ共有OAMマネージャVram転送
	REND_OAMTrans();	
	
	OS_SetIrqCheckFlag( OS_IE_V_BLANK );
}


//--------------------------------------------------------------------------------------------
/**
 * VRAM設定
 *
 * @param	none
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void VramBankSet(void)
{
	GF_BGL_DISPVRAM tbl = {
		GX_VRAM_BG_128_A,				// メイン2DエンジンのBG
		GX_VRAM_BGEXTPLTT_NONE,			// メイン2DエンジンのBG拡張パレット

		GX_VRAM_SUB_BG_128_C,			// サブ2DエンジンのBG
		GX_VRAM_SUB_BGEXTPLTT_NONE,		// サブ2DエンジンのBG拡張パレット

		GX_VRAM_OBJ_128_B,				// メイン2DエンジンのOBJ
		GX_VRAM_OBJEXTPLTT_NONE,		// メイン2DエンジンのOBJ拡張パレット

		GX_VRAM_SUB_OBJ_16_I,			// サブ2DエンジンのOBJ
		GX_VRAM_SUB_OBJEXTPLTT_NONE,	// サブ2DエンジンのOBJ拡張パレット

		GX_VRAM_TEX_NONE,				// テクスチャイメージスロット
		GX_VRAM_TEXPLTT_NONE			// テクスチャパレットスロット
	};
	GF_Disp_SetBank( &tbl );
}

//--------------------------------------------------------------------------------------------
/**
 * BG設定
 *
 * @param	ini		BGLデータ
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

	// ----------メイン画面-------------------
	// メイン画面ウインドウBG0
	{	
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xf000, GX_BG_CHARBASE_0x00000, GX_BG_EXTPLTT_01,
			0, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( ini, GF_BGL_FRAME0_M, &TextBgCntDat, GF_BGL_MODE_TEXT );
		GF_BGL_ScrClear( ini, GF_BGL_FRAME0_M );


	}

	// メイン画面ポケモン説明文字列BG1
	{	
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xf800, GX_BG_CHARBASE_0x08000, GX_BG_EXTPLTT_01,
			1, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( ini, GF_BGL_FRAME1_M, &TextBgCntDat, GF_BGL_MODE_TEXT );
		GF_BGL_ScrClear( ini, GF_BGL_FRAME1_M );
	}

	// メイン画面パネルBG2
	{	
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xe000, GX_BG_CHARBASE_0x10000, GX_BG_EXTPLTT_01,
			2, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( ini, GF_BGL_FRAME2_M, &TextBgCntDat, GF_BGL_MODE_TEXT );
		GF_BGL_ScrClear( ini, GF_BGL_FRAME2_M );
	}

	// メイン画面背景BG3
	{	
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xe800, GX_BG_CHARBASE_0x10000, GX_BG_EXTPLTT_01,
			3, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( ini, GF_BGL_FRAME3_M, &TextBgCntDat, GF_BGL_MODE_TEXT );
	}

	// -----サブ画面-------------

	// サブ画面テキストBG (CHAR)
	{	
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xf800, GX_BG_CHARBASE_0x10000, GX_BG_EXTPLTT_01,
			0, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( ini, GF_BGL_FRAME0_S, &TextBgCntDat, GF_BGL_MODE_TEXT );
		GF_BGL_ScrClear( ini, GF_BGL_FRAME0_S );
	}

	// サブ画面カードBG (CHAR)
	{	
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xf000, GX_BG_CHARBASE_0x00000, GX_BG_EXTPLTT_01,
			1, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( ini, GF_BGL_FRAME1_S, &TextBgCntDat, GF_BGL_MODE_TEXT );
	}
	// サブ画面背景BG (CHAR)
	{	
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xd800, GX_BG_CHARBASE_0x00000, GX_BG_EXTPLTT_01,
			1, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( ini, GF_BGL_FRAME2_S, &TextBgCntDat, GF_BGL_MODE_TEXT );
	}

	GF_BGL_ClearCharSet( GF_BGL_FRAME0_M, 32, 0, HEAPID_TRADELIST );
	GF_BGL_ClearCharSet( GF_BGL_FRAME1_M, 32, 0, HEAPID_TRADELIST );
	GF_BGL_ClearCharSet( GF_BGL_FRAME0_S, 32, 0, HEAPID_TRADELIST );

	// BGスクロールレジスタ初期化
	{
		int i;
		for(i=0;i<4;i++){
			GF_BGL_ScrollSet( ini, GF_BGL_FRAME0_M+i, GF_BGL_SCROLL_X_SET, 0 );
			GF_BGL_ScrollSet( ini, GF_BGL_FRAME0_M+i, GF_BGL_SCROLL_Y_SET, 0 );
			GF_BGL_ScrollSet( ini, GF_BGL_FRAME0_S+i, GF_BGL_SCROLL_X_SET, 0 );
			GF_BGL_ScrollSet( ini, GF_BGL_FRAME0_S+i, GF_BGL_SCROLL_Y_SET, 0 );
		}
	}

	GF_BGL_VisibleSet( GF_BGL_FRAME0_M, VISIBLE_OFF );
	GF_BGL_VisibleSet( GF_BGL_FRAME1_M, VISIBLE_OFF );
	GF_BGL_VisibleSet( GF_BGL_FRAME2_M, VISIBLE_OFF );
	GF_BGL_VisibleSet( GF_BGL_FRAME3_M, VISIBLE_OFF );
	GF_BGL_VisibleSet( GF_BGL_FRAME0_S, VISIBLE_OFF );
	GF_BGL_VisibleSet( GF_BGL_FRAME1_S, VISIBLE_OFF );
	GF_BGL_VisibleSet( GF_BGL_FRAME2_S, VISIBLE_OFF );

	// 上画面のハードウェアウインドウをＯFFに
	GX_SetVisibleWnd( GX_WNDMASK_NONE  );


}


//------------------------------------------------------------------
/**
 * ポケモン交換リストワーク初期化
 *
 * @param   wk		NAMEIN_WORK*
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void InitWork(TRADELIST_WORK *wk, PROC * proc)
{
	TRADELIST_PARAM *param = PROC_GetParentWork(proc);
	wk->param         = param;
	

	wk->seq           = NAMEIN_MODE;

	wk->subseqflag    = 0;
	wk->yesnoseq      = 0;
	wk->MyPokeNum     = 6;
	wk->FriendPokeNum = 6;
	wk->cursor_pos[0] = 0;
	wk->cursor_pos[1] = 6;
	wk->inputmode     = MODE_NORMAL;

	wk->tradeseq      = 0;
	wk->exchangeseq   = 0;
	wk->func          = trade_seq_normal;
	wk->end_flag[0]   = 0;
	wk->end_flag[1]   = 0;
	wk->result		  = 0;
	wk->vblankreq     = 0;
	wk->posBackup     = -1;
	wk->commandBackup = -1;
	wk->savePreWait   = 0;

	wk->timeOutFlag = 0;
	wk->timeOutWait = 0;

	// 手持ちポケモンデータ取得
	wk->MyPokeParty     = param->myparty;;
	wk->friendlist      = param->friendlist;
	wk->savedata        = param->savedata;

	// 相手のポケモンデータ用ワーク生成
	wk->FriendPokeParty = sys_AllocMemory( HEAPID_TRADELIST, PokeParty_GetWorkSize());
	PokeParty_Init(wk->FriendPokeParty, 6);
	memset(wk->FriendPokeParty,0xff,PokeParty_GetWorkSize());
	
	wk->MyName = MyStatus_CreateNameString(param->mystatus, 	HEAPID_TRADELIST);
	
	// 「もちもの」文字列確保
	wk->MotimonoStr = MSGMAN_AllocString( wk->MsgManager, mes_dstrade_05_05 );

	// 地球儀登録
	Comm_WifiHistoryCheck( param->wifihistory );
	
}

//--------------------------------------------------------------------------------------------
/**
 * BG解放
 *
 * @param	ini		BGLデータ
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void BgExit( GF_BGL_INI * ini )
{

	//会話ウインドウ用バッファ解放
	GF_BGL_BGControlExit( ini, GF_BGL_FRAME2_S);
	GF_BGL_BGControlExit( ini, GF_BGL_FRAME1_S );
	GF_BGL_BGControlExit( ini, GF_BGL_FRAME0_S );

	GF_BGL_BGControlExit( ini, GF_BGL_FRAME3_M );
	GF_BGL_BGControlExit( ini, GF_BGL_FRAME2_M );
	GF_BGL_BGControlExit( ini, GF_BGL_FRAME1_M );
	GF_BGL_BGControlExit( ini, GF_BGL_FRAME0_M );

}


//------------------------------------------------------------------
/**
 * 転送なしでスクリーンデータを読み込む
 *
 * @param   fileIdx		
 * @param   dataIdx		
 * @param   bgl		
 * @param   frm		
 * @param   offs		
 * @param   transSize		
 * @param   compressedFlag		
 * @param   heapID		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void ArcUtil_ScrnSetNoTrans(u32 fileIdx, u32 dataIdx, GF_BGL_INI* bgl, u32 frm, u32 offs, u32 transSize, BOOL compressedFlag, u32 heapID)
{
	void* arcData = ArcUtil_Load( fileIdx, dataIdx, compressedFlag, heapID, ALLOC_BOTTOM );

	if( arcData != NULL )
	{
		NNSG2dScreenData* scrnData;

		if( NNS_G2dGetUnpackedScreenData( arcData, &scrnData ) )
		{
			if( transSize == 0 )
			{
				transSize = scrnData->szByte;
			}

			if( GF_BGL_ScreenAdrsGet( bgl, frm ) != NULL )
			{
				GF_BGL_ScreenBufSet( bgl, frm, scrnData->rawData, transSize );
			}
		}
		sys_FreeMemoryEz( arcData );
	}
}

#define POKEPARTY_NUM	(  6 )

#define CARD_W			(  8 )
#define CARD_H			(  5 )

#define LEFT_CARD_SX	(  0 )
#define LEFT_CARD_SY	(  4 )
#define RIGHT_CARD_SX	( 16 )
#define RIGHT_CARD_SY	(  4 )

static const card_pos_table[][2]={
	{LEFT_CARD_SX,			LEFT_CARD_SY},
	{LEFT_CARD_SX+CARD_W,	LEFT_CARD_SY},
	{LEFT_CARD_SX,			LEFT_CARD_SY+CARD_H},
	{LEFT_CARD_SX+CARD_W,	LEFT_CARD_SY+CARD_H},
	{LEFT_CARD_SX,			LEFT_CARD_SY+CARD_H*2},
	{LEFT_CARD_SX+CARD_W,	LEFT_CARD_SY+CARD_H*2},

	{RIGHT_CARD_SX,			RIGHT_CARD_SY},
	{RIGHT_CARD_SX+CARD_W,	RIGHT_CARD_SY},
	{RIGHT_CARD_SX,			RIGHT_CARD_SY+CARD_H},
	{RIGHT_CARD_SX+CARD_W,	RIGHT_CARD_SY+CARD_H},
	{RIGHT_CARD_SX,			RIGHT_CARD_SY+CARD_H*2},
	{RIGHT_CARD_SX+CARD_W,	RIGHT_CARD_SY+CARD_H*2},
};

//------------------------------------------------------------------
/**
 * 名前表示＆カード増減
 *
 * @param   bgl		
 * @param   mynum		
 * @param   friendnum		
 *
 * @retval  void 			
 */
//------------------------------------------------------------------
static void TradeListMakeScreenSet(GF_BGL_INI *bgl, int mynum, int friendnum)
{
	int i;

#if 0
	// ポケモンの数にあわせてカードの数を変える
	for(i=mynum;i<6;i++)
	{
		GF_BGL_ScrFill(	bgl, GF_BGL_FRAME2_M, 0, card_pos_table[i][0], card_pos_table[i][1], CARD_W, CARD_H,  0);
	}
	for(i=friendnum;i<6;i++)
	{
		GF_BGL_ScrFill(	bgl, GF_BGL_FRAME2_M, 0, card_pos_table[i+6][0], card_pos_table[i+6][1], CARD_W, CARD_H,  0);
	}
#endif

	// スクリーン転送
	GF_BGL_LoadScreen( bgl, GF_BGL_FRAME2_M, GF_BGL_ScreenAdrsGet( bgl, GF_BGL_FRAME2_M ), 32*24*2, 0 );

}

//--------------------------------------------------------------------------------------------
/**
 * グラフィックデータセット
 *
 * @param	wk		ポケモンリスト画面のワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void BgGraphicSet( TRADELIST_WORK * wk )
{
	GF_BGL_INI *bgl = wk->bgl;

	// 上下画面ＢＧパレット転送
	ArcUtil_PalSet(    ARC_TRADELIST_GRA, NARC_TradeList_DsTradeList_nclr, PALTYPE_SUB_BG,  0, 16*9*2,  HEAPID_TRADELIST);
	ArcUtil_PalSet(    ARC_TRADELIST_GRA, NARC_TradeList_DsTradeList_nclr, PALTYPE_MAIN_BG, 0, 16*9*2,  HEAPID_TRADELIST);
	GF_BGL_BackGroundColorSet( GF_BGL_FRAME0_M, 0 );
	GF_BGL_BackGroundColorSet( GF_BGL_FRAME0_S, 0 );

	// 会話フォントパレット転送
	TalkFontPaletteLoad( PALTYPE_MAIN_BG, TALK_FONT_PAL * 32, HEAPID_TRADELIST );

	// 上画面BGキャラ転送
	ArcUtil_BgCharSet( ARC_TRADELIST_GRA, NARC_TradeList_chara_m_lz_ncgr, bgl, GF_BGL_FRAME2_M, 0, 16*18*0x20, 1, HEAPID_TRADELIST);

	// 上画面BG2スクリーン読み込み（のみ）
	ArcUtil_ScrnSetNoTrans(   ARC_TRADELIST_GRA, NARC_TradeList_main2_lz_nscr, bgl, GF_BGL_FRAME2_M, 0, 32*24*2, 1, HEAPID_TRADELIST);

	// 上画面BG3スクリーン転送
	ArcUtil_ScrnSet(   ARC_TRADELIST_GRA, NARC_TradeList_main3_lz_nscr, bgl, GF_BGL_FRAME3_M, 0, 32*24*2, 1, HEAPID_TRADELIST);
	
	// 上画面にフォントパレット転送
	TalkFontPaletteLoad(   PALTYPE_MAIN_BG , 2*32, HEAPID_TRADELIST );
	SystemFontPaletteLoad( PALTYPE_MAIN_BG,  3*32, HEAPID_TRADELIST );


	// 下画面BGキャラ転送
	ArcUtil_BgCharSet( ARC_TRADELIST_GRA, NARC_TradeList_chara_s_lz_ncgr, bgl, GF_BGL_FRAME1_S, 0, 16*4*0x20, 1, HEAPID_TRADELIST);

	// 下画面BGスクリーン転送
	ArcUtil_ScrnSet(   ARC_TRADELIST_GRA, NARC_TradeList_sub2_lz_nscr, bgl, GF_BGL_FRAME1_S, 0, 32*24*2, 1, HEAPID_TRADELIST);

	// 下画面BGスクリーン転送
	ArcUtil_ScrnSet(   ARC_TRADELIST_GRA, NARC_TradeList_sub3_lz_nscr, bgl, GF_BGL_FRAME2_S, 0, 32*24*2, 1, HEAPID_TRADELIST);

	// 下画面フォントパレット転送
	TalkFontPaletteLoad(   PALTYPE_SUB_BG , 2*32, HEAPID_TRADELIST );
	SystemFontPaletteLoad( PALTYPE_SUB_BG,  3*32, HEAPID_TRADELIST );

	GF_BGL_ScrClear( bgl, GF_BGL_FRAME0_S );


}


//** CharManager PlttManager用 **//
#define TRADELIST_CHAR_CONT_NUM					(20)
#define TRADELIST_CHAR_VRAMTRANS_MAIN_SIZE		(2048)
#define TRADELIST_CHAR_VRAMTRANS_SUB_SIZE		(2048)
#define TRADELIST_PLTT_CONT_NUM					(20)

//-------------------------------------
//
//	キャラクタマネージャー
//	パレットマネージャーの初期化
//
//=====================================
static void char_pltt_manager_init(void)
{
	// キャラクタマネージャー初期化
	{
		CHAR_MANAGER_MAKE cm = {
			TRADELIST_CHAR_CONT_NUM,
			TRADELIST_CHAR_VRAMTRANS_MAIN_SIZE,
			TRADELIST_CHAR_VRAMTRANS_SUB_SIZE,
			HEAPID_TRADELIST
		};
		InitCharManager(&cm);
	}
	// パレットマネージャー初期化
	InitPlttManager(TRADELIST_PLTT_CONT_NUM, HEAPID_TRADELIST);

	// 読み込み開始位置を初期化
	CharLoadStartAll();
	PlttLoadStartAll();
}


//------------------------------------------------------------------
/**
 * レーダー画面用セルアクター初期化
 *
 * @param   wk		レーダー構造体のポインタ
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void InitCellActor(TRADELIST_WORK *wk)
{
	int i;
	
	
	// OAMマネージャーの初期化
	NNS_G2dInitOamManagerModule();

	// 共有OAMマネージャ作成
	// レンダラ用OAMマネージャ作成
	// ここで作成したOAMマネージャをみんなで共有する
	REND_OAMInit( 
			0, 127,		// メイン画面OAM管理領域
			0, 32,		// メイン画面アフィン管理領域
			0, 127,		// サブ画面OAM管理領域
			0, 32,		// サブ画面アフィン管理領域
			HEAPID_TRADELIST);
	
	
	
	// セルアクター初期化
	wk->clactSet = CLACT_U_SetEasyInit( TRADELIST_CACT_MAX, &wk->renddata, HEAPID_TRADELIST );
	
	//リソースマネージャー初期化
	for(i=0;i<CLACT_RESOURCE_NUM;i++){		//リソースマネージャー作成
		wk->resMan[i] = CLACT_U_ResManagerInit(2, i, HEAPID_TRADELIST);
	}


	//---------上画面用-------------------
	
	//chara読み込み
	wk->resObjTbl[MAIN_LCD][CLACT_U_CHAR_RES] = CLACT_U_ResManagerResAddArcChar(wk->resMan[CLACT_U_CHAR_RES], 
							ARC_TRADELIST_GRA, NARC_TradeList_obj_lz_ncgr, 1, 0, NNS_G2D_VRAM_TYPE_2DMAIN, HEAPID_TRADELIST);

	//pal読み込み
	wk->resObjTbl[MAIN_LCD][CLACT_U_PLTT_RES] = CLACT_U_ResManagerResAddArcPltt(wk->resMan[CLACT_U_PLTT_RES],
							ARC_TRADELIST_GRA, NARC_TradeList_DsTradeList_nclr, 0, 0, NNS_G2D_VRAM_TYPE_2DMAIN, 9, HEAPID_TRADELIST);

	//cell読み込み
	wk->resObjTbl[MAIN_LCD][CLACT_U_CELL_RES] = CLACT_U_ResManagerResAddArcKindCell(wk->resMan[CLACT_U_CELL_RES],
							ARC_TRADELIST_GRA, NARC_TradeList_obj_lz_ncer, 1, 0, CLACT_U_CELL_RES,HEAPID_TRADELIST);

	//同じ関数でanim読み込み
	wk->resObjTbl[MAIN_LCD][CLACT_U_CELLANM_RES] = CLACT_U_ResManagerResAddArcKindCell(wk->resMan[CLACT_U_CELLANM_RES],
							ARC_TRADELIST_GRA, NARC_TradeList_obj_lz_nanr, 1, 0, CLACT_U_CELLANM_RES,HEAPID_TRADELIST);


	//---------下画面用-------------------


	//chara読み込み
	wk->resObjTbl[SUB_LCD][CLACT_U_CHAR_RES] = CLACT_U_ResManagerResAddArcChar(wk->resMan[CLACT_U_CHAR_RES], 
							ARC_TRADELIST_GRA, NARC_TradeList_obj_s_lz_ncgr, 1, 1, NNS_G2D_VRAM_TYPE_2DSUB, HEAPID_TRADELIST);

	//pal読み込み
	wk->resObjTbl[SUB_LCD][CLACT_U_PLTT_RES] = CLACT_U_ResManagerResAddArcPltt(wk->resMan[CLACT_U_PLTT_RES],
							ARC_TRADELIST_GRA, NARC_TradeList_DsTradeList_nclr, 0, 1, NNS_G2D_VRAM_TYPE_2DSUB, 10, HEAPID_TRADELIST);

	//cell読み込み
	wk->resObjTbl[SUB_LCD][CLACT_U_CELL_RES] = CLACT_U_ResManagerResAddArcKindCell(wk->resMan[CLACT_U_CELL_RES],
							ARC_TRADELIST_GRA, NARC_TradeList_obj_s_lz_ncer, 1, 1, CLACT_U_CELL_RES,HEAPID_TRADELIST);

	//同じ関数でanim読み込み
	wk->resObjTbl[SUB_LCD][CLACT_U_CELLANM_RES] = CLACT_U_ResManagerResAddArcKindCell(wk->resMan[CLACT_U_CELLANM_RES],
							ARC_TRADELIST_GRA, NARC_TradeList_obj_s_lz_nanr, 1, 1, CLACT_U_CELLANM_RES,HEAPID_TRADELIST);

	// リソースマネージャーから転送

	// Chara転送
	CLACT_U_CharManagerSet( wk->resObjTbl[MAIN_LCD][CLACT_U_CHAR_RES] );
	CLACT_U_CharManagerSet( wk->resObjTbl[SUB_LCD][CLACT_U_CHAR_RES] );

	// パレット転送
	CLACT_U_PlttManagerSet( wk->resObjTbl[MAIN_LCD][CLACT_U_PLTT_RES] );
	CLACT_U_PlttManagerSet( wk->resObjTbl[SUB_LCD][CLACT_U_PLTT_RES] );

	// ポケモンアイコン用パレットを一気に読み込んでVRAM転送する
	ArcUtil_PalSet( ARC_POKEICON, PokeIconPalArcIndexGet(), PALTYPE_MAIN_OBJ, POKEICON_PAL_OFFSET*0x20, 0x20*4, HEAPID_TRADELIST );


}

//------------------------------------------------------------------
/**
 * 下画面のポケモン画像を転送する
 *
 * @param   side		左か右か(0-1)
 * @param   pokeno		ポケモンの開発NO
 * @param   char_work	ポケモン画像を読み込む領域
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static int TransPokeGra_SubLcd(int side, POKEMON_PARAM *pp, u8 *char_work, SOFT_SPRITE_ARC *ssa)
{
	// ポケモンの画像を読み込む（ただしソフトウェアスプライト用のテクスチャ状態）
	PokeGraArcDataGetPP( ssa, pp, PARA_FRONT);

	// テクスチャをOAM用の並びに変換する
	{
		int rnd    = PokeParaGet( pp, ID_PARA_personal_rnd, NULL );
		int monsno = PokeParaGet( pp, ID_PARA_monsno, NULL );
		Ex_ChangesInto_OAM_from_PokeTex(ssa->arc_no, ssa->index_chr, HEAPID_TRADELIST, 0, 0, 10, 10, char_work, 
										rnd, 0, PARA_FRONT, monsno);
	}

	DC_FlushRange( char_work, 0x20*10*10 );	// 転送前にメモリ安定
	
	return side+1;
	

}





//------------------------------------------------------------------
/**
 * @brief   ポケモンの名前を描画
 *
 * @param   win		
 * @param   party		
 * @param   pos		
 * @param   width		
 * @param   print_sw		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void PokeNamePrint( GF_BGL_BMPWIN *win, POKEPARTY *party, int pos, int width, int print_sw )
{
	STRBUF *name;
	
	name = STRBUF_Create(20,HEAPID_TRADELIST);
	PokeParaGet(PokeParty_GetMemberPointer(party, pos),ID_PARA_nickname_buf, name);

	// ポケモン名
	GF_BGL_BmpWinDataFill( win, 0 );
	TradeListPrint(win, name, width, MSG_ALLPUT, print_sw,1);
	STRBUF_Delete(name);

}

//------------------------------------------------------------------
/**
 * @brief   ニドラン♂・♀用の特別処理
 *
 * @param   info	
 * @param   party	
 * @param   pos		
 * @param   sex		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int NidoranSpecialCheck( POKE_INFO *info, POKEPARTY *party, int pos, int sex )
{
	// ニドラン♂かニドラン♀に
	if(info->exist==MONSNO_NIDORAN_F || info->exist==MONSNO_NIDORAN_M){

		// ニックネームフラグが立っていない場合は
		POKEMON_PARAM *pp = PokeParty_GetMemberPointer( party, pos );
		int flag = PokeParaGet( pp, ID_PARA_nickname_flag,NULL );
		if(flag==0){
			// 性別無し扱いにして下画面に性別アイコンを出さないようにさせる
			return PARA_UNK;
		}
	}
	
	return sex;
}


//------------------------------------------------------------------
/**
 * サブ画面に文字列描画とOAM表示ONを行う
 *
 * @param   win		
 * @param   side		
 * @param   party		
 * @param   pos		
 * @param   wk		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void TransPokeStr_SubLcd(GF_BGL_BMPWIN *win, int side, POKEPARTY *party, int pos, TRADELIST_WORK *wk)
{
	STRBUF *level, *item;
	u16 itemno,levelnum;
	int height;
	POKEMON_PARAM *pp;
	
	pp = PokeParty_GetMemberPointer(party, pos);
	
	// 足元高さ取得
	height = PokeParaHeightGet( pp, PARA_FRONT );

//	OS_Printf("足元　%d\n",height);

	// 下画面ポケモン表示
	CLACT_SetDrawFlag(wk->SubLCDIconActWork[side], 1);
	Clact_SetPos( wk->SubLCDIconActWork[side],  sub_icon_pos[side][0], 
												sub_icon_pos[side][1]+height+SUB_SURFACE_Y_INTEGER  );

	// 左右反転フラグを見て反転させないようにする
	if(side==0){
		CLACT_SetFlip( wk->SubLCDIconActWork[side], wk->pokeInfo[pos].reverse );
	}

	// モンスターボールチェンジ・表示
	CLACT_AnmChg( wk->SubLCDIconActWork[2+side], wk->pokeInfo[pos].monsball+CELL_MONSTER_BALL_NO-1 );
	CLACT_SetDrawFlag(wk->SubLCDIconActWork[2+side], 1);


	PokeNamePrint(&win[BMP_S_MYPOKENAME_WIN+side], party, pos, SUB_POKENAME_W, 6);

	// 性別アイコン表示
	{
		
		int sex = wk->pokeInfo[side*6+pos].sex;
		sex = NidoranSpecialCheck( &wk->pokeInfo[side*6+pos], party, pos, sex );
		// タマゴは表示しない
		if(wk->pokeInfo[side*6+pos].tamago){
			sex = PARA_UNK;
		}
		switch(sex){
		case PARA_UNK:
			// 性別無しならアイコン表示OFF
			CLACT_SetDrawFlag(wk->SubLCDIconActWork[4+side], 0);
			break;
		// 性別にあわせて表示
		case PARA_MALE:
			CLACT_SetDrawFlag(wk->SubLCDIconActWork[4+side], 1);
			CLACT_AnmChg(wk->SubLCDIconActWork[4+side], CELL_SEX_ICON_NO+1 );
			break;
		case PARA_FEMALE:
			CLACT_SetDrawFlag(wk->SubLCDIconActWork[4+side], 1);
			CLACT_AnmChg(wk->SubLCDIconActWork[4+side], CELL_SEX_ICON_NO );
			break;
		}
	}

	// タマゴじゃなければ
	if(!wk->pokeInfo[side*6+pos].tamago){

		// レベル「LV.」
		level = STRBUF_Create(10,HEAPID_TRADELIST);
		GF_BGL_BmpWinDataFill( &win[BMP_S_MYPOKELEVEL_WIN+side], 0 );
		MSGMAN_GetString( wk->MsgManager, mes_dstrade_05_03, level );
		TradeListPrint( &win[BMP_S_MYPOKELEVEL_WIN+side], level, SUB_POKENAME_W, MSG_NO_PUT, 6,0);
	
		// レベル数字
		levelnum = PokeParaGet(PokeParty_GetMemberPointer(party, pos),ID_PARA_level,NULL);
		STRBUF_SetNumber( level, levelnum, 3, NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );
		TradeListPrint( &win[BMP_S_MYPOKELEVEL_WIN+side], level, SUB_POKENAME_W, MSG_ALLPUT, 24+6,0);
		STRBUF_Delete(level);
	}else{
		GF_BGL_BmpWinOff( &win[BMP_S_MYPOKELEVEL_WIN+side] );
	
	}

	// 「もちもの」
	TradeListPrint(&win[BMP_S_MOTIMONO0_WIN+side], wk->MotimonoStr, SUB_MOTIMONOSTR_W, MSG_ALLPUT, 3,0);

	itemno = PokeParaGet(PokeParty_GetMemberPointer(party, pos),ID_PARA_item,NULL);
	GF_BGL_BmpWinDataFill( &win[BMP_S_MYITEM_WIN+side], 0 );

	// アイテム名（「なし」という文字列はまだ表示できない。itemname=0は「？？？」だったから）
	item = STRBUF_Create(20,HEAPID_TRADELIST);
	GetItemName( item, itemno, HEAPID_TRADELIST );
	TradeListPrint(&win[BMP_S_MYITEM_WIN+side], item, SUB_POKENAME_W, MSG_ALLPUT, 3,0);
	STRBUF_Delete(item);

}


//------------------------------------------------------------------
/**
 * @brief   下画面カード非表示処理
 *
 * @param   win		
 * @param   side		
 * @param   wk		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void PokeStr_SubLcdOff(GF_BGL_BMPWIN *win, int side, TRADELIST_WORK *wk)
{
	// 下画面ポケモン非表示
	CLACT_SetDrawFlag(wk->SubLCDIconActWork[side], 0);

	// モンスターボールチェンジ非表示
	CLACT_SetDrawFlag(wk->SubLCDIconActWork[2+side], 0);

	// 性別アイコン
	CLACT_SetDrawFlag(wk->SubLCDIconActWork[4+side], 0);

	// 名前・レベル・「もちもの」・もちもの　非表示
	GF_BGL_BmpWinOff( &win[BMP_S_MYPOKENAME_WIN+side] );
	GF_BGL_BmpWinOff( &win[BMP_S_MYPOKELEVEL_WIN+side] );
	GF_BGL_BmpWinOff( &win[BMP_S_MOTIMONO0_WIN+side] );
	GF_BGL_BmpWinOff( &win[BMP_S_MYITEM_WIN+side] );

}



//------------------------------------------------------------------
/**
 * セルアクター登録
 *
 * @param   wk			NAMEIN_WORK*
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void SetCellActor(TRADELIST_WORK *wk)
{
	// セルアクターヘッダ作成
	CLACT_U_MakeHeader(&wk->clActHeader_m, 0, 0, 0, 0, CLACT_U_HEADER_DATA_NONE, CLACT_U_HEADER_DATA_NONE,
	0, 2,
	wk->resMan[CLACT_U_CHAR_RES],
	wk->resMan[CLACT_U_PLTT_RES],
	wk->resMan[CLACT_U_CELL_RES],
	wk->resMan[CLACT_U_CELLANM_RES],
	NULL,NULL);

	CLACT_U_MakeHeader(&wk->clActHeader_s, 1, 1, 1, 1, CLACT_U_HEADER_DATA_NONE, CLACT_U_HEADER_DATA_NONE,
	0, 0,
	wk->resMan[CLACT_U_CHAR_RES],
	wk->resMan[CLACT_U_PLTT_RES],
	wk->resMan[CLACT_U_CELL_RES],
	wk->resMan[CLACT_U_CELLANM_RES],
	NULL,NULL);

	{
		//登録情報格納
		CLACT_ADD add;
		int i;

		add.ClActSet	= wk->clactSet;
		add.ClActHeader	= &wk->clActHeader_m;

		add.mat.x		= FX32_CONST(32) ;
		add.mat.y		= FX32_CONST(96) ;		//画面は上下連続している（MAINが上、SUBが下）
		add.mat.z		= 0;
		add.sca.x		= FX32_ONE;
		add.sca.y		= FX32_ONE;
		add.sca.z		= FX32_ONE;
		add.rot			= 0;
		add.pri			= 0;
		add.DrawArea	= NNS_G2D_VRAM_TYPE_2DMAIN;
		add.heap		= HEAPID_TRADELIST;

		//セルアクター表示開始

		// 上画面用カーソル
		for(i=0;i<2;i++){
			add.mat.x = FX32_ONE*main_cursor_pos[i][0];
			add.mat.y = FX32_ONE*main_cursor_pos[i][1];
			wk->clActWork[i] = CLACT_Add(&add);
			CLACT_SetAnmFlag(wk->clActWork[i],1);
			CursorPosChange(wk->cursor_pos[i],wk->clActWork[i], i);
			CLACT_DrawPriorityChg( wk->clActWork[i], 100 );		
			CLACT_SetDrawFlag( wk->clActWork[i], 0 );

		}

		// ポケモンアイコン
		for(i=0;i<TRADELIST_POKE_MAX;i++){
			add.mat.x = FX32_ONE*(main_cursor_pos[i][0]+16);
			add.mat.y = FX32_ONE*(main_cursor_pos[i][1]-6);
			wk->PokeIconActWork[i] = CLACT_Add(&add);
			CLACT_SetAnmFlag(wk->PokeIconActWork[i],1);
			CLACT_AnmChg( wk->PokeIconActWork[i], 5+i );
//			CLACT_BGPriorityChg( wk->PokeIconActWork[i], 1 );	// プライオリティをカーソルよりは上に
			CLACT_DrawPriorityChg(wk->PokeIconActWork[i], 5);	// それぞれのアクターのプライオリティ設定
			CLACT_SetDrawFlag( wk->PokeIconActWork[i], 0 );
		}

		// ポケモンのアイテム
		for(i=0;i<TRADELIST_POKE_MAX;i++){
			add.mat.x = FX32_ONE*(main_cursor_pos[i][0]+16+20);
			add.mat.y = FX32_ONE*(main_cursor_pos[i][1]+16);
			add.pri			= 0;
			wk->PokeItemActWork[i] = CLACT_Add(&add);
			CLACT_DrawPriorityChg(wk->PokeItemActWork[i], 3);	// それぞれのアクターのプライオリティ設定
			CLACT_SetDrawFlag( wk->PokeItemActWork[i], 0 );
		}

		// ポケモンのカスタムボール
		for(i=0;i<TRADELIST_POKE_MAX;i++){
			add.mat.x = FX32_ONE*(main_cursor_pos[i][0]+16+20+9);
			add.mat.y = FX32_ONE*(main_cursor_pos[i][1]+16);
			add.pri			= 0;
			wk->PokeCBallActWork[i] = CLACT_Add(&add);
			CLACT_DrawPriorityChg(wk->PokeCBallActWork[i], 3);	// それぞれのアクターのプライオリティ設定
			CLACT_SetDrawFlag( wk->PokeCBallActWork[i], 0 );
		}

		// 「交換しますか？」の矢印
		add.mat.x = FX32_ONE*( 128-4*8 );
		add.mat.y = FX32_ONE*(     8*8+2 );
		wk->ExchangeArrow = CLACT_Add(&add);
		CLACT_SetAnmFlag( wk->ExchangeArrow,1);
		CLACT_AnmChg( wk->ExchangeArrow, 20 );
		CLACT_SetDrawFlag( wk->ExchangeArrow, 0 );


		// 下画面用(ポケモン２体・矢印２個・性別アイコン）
		for(i=0;i<6;i++){
			add.ClActHeader	= &wk->clActHeader_s;
			add.mat.x = FX32_ONE*sub_icon_pos[i][0];
			add.mat.y = FX32_ONE*(sub_icon_pos[i][1]) + SUB_SURFACE_Y;
			add.DrawArea	= NNS_G2D_VRAM_TYPE_2DSUB;
			wk->SubLCDIconActWork[i] = CLACT_Add(&add);
			CLACT_SetDrawFlag(wk->SubLCDIconActWork[i], 0);
			CLACT_SetAnmFlag(wk->SubLCDIconActWork[i],0);
			CLACT_AnmChg( wk->SubLCDIconActWork[i], sub_icon_pos[i][2] );
		}
		
	}	
	
}







#ifdef PM_DEBUG
//------------------------------------------------------------------
/**
 * デバッグ表示用にOBJやBGを動かす
 *
 * @param   wk		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void DebugOBJPOSGet(TRADELIST_WORK *wk)
{
		if( sys.cont & PAD_KEY_UP){
			VecFx32 tmpVex;
			wk->framenum[wk->frame][1]--;
			tmpVex.x = FX32_ONE*wk->framenum[wk->frame][0];
			tmpVex.y = FX32_ONE*wk->framenum[wk->frame][1];
			CLACT_SetMatrix(wk->clActWork[wk->frame], &tmpVex);
			OS_Printf("frame %d x=%d, y=%d\n",wk->frame, wk->framenum[wk->frame][0],wk->framenum[wk->frame][1]);
		}
		if( sys.cont & PAD_KEY_DOWN){
			VecFx32 tmpVex;
			wk->framenum[wk->frame][1]++;
			tmpVex.x = FX32_ONE*wk->framenum[wk->frame][0];
			tmpVex.y = FX32_ONE*wk->framenum[wk->frame][1];
			CLACT_SetMatrix(wk->clActWork[wk->frame], &tmpVex);
			OS_Printf("frame %d x=%d, y=%d\n",wk->frame, wk->framenum[wk->frame][0],wk->framenum[wk->frame][1]);
			
		}
		if( sys.cont & PAD_KEY_LEFT){
			VecFx32 tmpVex;
			wk->framenum[wk->frame][0]--;
			tmpVex.x = FX32_ONE*wk->framenum[wk->frame][0];
			tmpVex.y = FX32_ONE*wk->framenum[wk->frame][1];
			CLACT_SetMatrix(wk->clActWork[wk->frame], &tmpVex);
			OS_Printf("frame %d x=%d, y=%d\n",wk->frame, wk->framenum[wk->frame][0],wk->framenum[wk->frame][1]);
			
		}
		if( sys.cont & PAD_KEY_RIGHT){
			VecFx32 tmpVex;
			wk->framenum[wk->frame][0]++;
			tmpVex.x = FX32_ONE*wk->framenum[wk->frame][0];
			tmpVex.y = FX32_ONE*wk->framenum[wk->frame][1];
			CLACT_SetMatrix(wk->clActWork[wk->frame], &tmpVex);
			OS_Printf("frame %d x=%d, y=%d\n",wk->frame, wk->framenum[wk->frame][0],wk->framenum[wk->frame][1]);
		}

}

#endif

#define MOVE_UP 	1
#define MOVE_DOWN 	2
#define MOVE_LEFT 	3
#define MOVE_RIGHT 	4

static const arrowtbl[][2]={{0,0},{0,-1},{0,1},{-1,0},{1,0}};

static int AroundWork(int w, int min, int max)
{
	if(w>=max){
		w = min;
	}
	if(w<min){
		w = max-1;
	}
	return w;
}


//------------------------------------------------------------------
/**
 * カーソル移動処理
 *
 * @param   wk		NAMEIN_WORK*
 *
 * @retval  none	
 */
//------------------------------------------------------------------
static void ControlCursor(u32 *CommWork)
{
	int move  = 0;
	int arrow = 0;

	// キー入力に対して移動する４方向のうちの一つを決定
	if( sys.repeat & PAD_KEY_UP){
		arrow = MOVE_UP;
		move++;
	}
	if( sys.repeat & PAD_KEY_DOWN){
		arrow = MOVE_DOWN;
		move++;
	}
	if( sys.repeat & PAD_KEY_LEFT){
		arrow = MOVE_LEFT;
		move++;
	}
	if( sys.repeat & PAD_KEY_RIGHT){
		arrow = MOVE_RIGHT;
		move++;
	}

	// 移動が発生したら変更
	if(move){
		*CommWork = arrow;
	}

}



// 下画面用ボタン位置定義
#define SUB_BUTTON1_POSX			( 3*8  )
#define SUB_BUTTON1_POSY			( 7*8  )
#define SUB_BUTTON2_POSX			( 19*8 )
#define SUB_BUTTON2_POSY			( 7*8  )

#define SUB_BUTTON_W			( 8*10 )
#define SUB_BUTTON_H			( 8*10 )

static const RECT_HIT_TBL sub_button_hittbl[]={
	{SUB_BUTTON1_POSY, SUB_BUTTON1_POSY+SUB_BUTTON_H, SUB_BUTTON1_POSX, SUB_BUTTON1_POSX+SUB_BUTTON_W},
//	{SUB_BUTTON2_POSY, SUB_BUTTON2_POSY+SUB_BUTTON_H, SUB_BUTTON2_POSX, SUB_BUTTON2_POSX+SUB_BUTTON_W},
	{RECT_HIT_END,0,0,0},		// 終了データ
};



//------------------------------------------------------------------
/**
 * タッチパネルで押したボタンがへこむ
 *
 * @param   wk		NAMEIN_WORKのポインタ
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void TouchFunc(TRADELIST_WORK *wk)
{
	u16 monsno;
	int button=-1,i;

	// 自分の側にカーソルがいるなら
	if( wk->cursor_pos[0]>=6){
		return;
	}

	// タッチパネル入力処理
	button=GF_TP_RectHitTrg( sub_button_hittbl );

	// 下画面で自分のポケモンをタッチした
	if( button != RECT_HIT_NONE ){

		// タマゴは無視
		if(wk->pokeInfo[wk->cursor_pos[0]].tamago){
			return;
		}

		// 泣き声（ペラップボイス対応）
		monsno = wk->pokeInfo[wk->cursor_pos[0]].exist;
		//ぺラップかチェック
		if( monsno == MONSNO_PERAPPU ){

			//自分のペラップデータ固定にしているので後で変更する！
			//Snd_PerapVoicePlay( CommGetCurrentID(), PM_MALE, PV_VOL_DEFAULT, 0 );
			Snd_PerapVoicePlay( SaveData_GetPerapVoice(wk->savedata), 
								PM_MALE, PV_VOL_DEFAULT, 0 );
		}else{
			Snd_PMVoicePlay( monsno );
		}
		
		// ポケモンがジャンプする
		CLACT_SetAnmFlag(wk->SubLCDIconActWork[button],1);
		CLACT_AnmChg( wk->SubLCDIconActWork[button], 4+button );
		OS_Printf("ジャンプ！\n");
	}


}


//------------------------------------------------------------------
/**
 * カーソルのパレット変更（点滅）
 *
 * @param   CursorCol	sinに渡すパラメータ（360まで）
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void CursorColTrans(u16 *CursorCol)
{
	fx32  sin;
	GXRgb tmp;
	int   r,g,b;

	*CursorCol+=20;
	if(*CursorCol>360){
		*CursorCol = 0;
	}

	sin = Sin360R(*CursorCol);
	g   = 15 +( sin * 10 ) / FX32_ONE;
	tmp = GX_RGB(29,g,0);


	GX_LoadOBJPltt((u16*)&tmp, (16+13)*2, 2);
}




//--------------------------------------------------------------------------
/**
 * ｶｰｿﾙの次の移動先は存在しているかを最高6個まで探す
 *
 * @param   pos		現在の位置番号
 * @param   arrow	移動方向
 *
 * @retval  u8		移動結果
 */
//--------------------------------------------------------------------------
static int NextCursorSearch(int pos, int arrow, POKE_INFO *info)
{
	int i,w;
	w = 0;
	for(i=0;i<6;i++){
		if(info[movepostbl[pos][arrow][i]].exist!=0){
			w = movepostbl[pos][arrow][i];
			break;
		}
	}
	return w;
}


static const CursorAnmTable[][3]={
	{ 0, 1, 2},
	{17,18,19},
};
//--------------------------------------------------------------------------
/**
 * ｶｰｿﾙ移動処理
 *
 * @param   pos		カーソル位置を格納しているワークのポインタ
 * @param   arrow	移動方向
 *
 * @retval  none		
 *
 *
 */
//--------------------------------------------------------------------------
static void CursorPosChange(int pos, CLACT_WORK_PTR CursorAct,int side)
{
	VecFx32 tmpVex;
	GF_ASSERT(pos<13);

	tmpVex.x = FX32_ONE*main_cursor_pos[pos][0];
	tmpVex.y = FX32_ONE*main_cursor_pos[pos][1];

	if(pos==CURSOR_END_POS){
		CLACT_SetMatrix(CursorAct, &tmpVex);
		CLACT_AnmChg( CursorAct, CursorAnmTable[side][2] );	// おわり用カーソルにアクター変更
	}else{
		CLACT_SetMatrix(CursorAct, &tmpVex);
		if(pos<6){
			CLACT_AnmChg( CursorAct, CursorAnmTable[side][0] );	// 左用にアクター変更
		}else{
			CLACT_AnmChg( CursorAct, CursorAnmTable[side][1] );	// 右用にアクター変更
		}
	}

}


//------------------------------------------------------------------
/**
 * カーソルが移動した場合に座標・形状の変更を行う
 *
 * @param   Command		
 * @param   pos		
 * @param   CursorAct		
 * @param   existtbl		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int ViewChange(u32 *Command, int *pos, CLACT_WORK_PTR CursorAct, POKE_INFO *info, int side)
{
	int arrow  = *Command - 1;
	int w      = 0;
	int result = 0;
	
	if(side==0){
		if(*Command){
			w = NextCursorSearch(*pos,arrow,info);
			CursorPosChange(w,CursorAct,side);
			if(*pos!=w){					//移動していればSE鳴らす
				Snd_SePlay(NAMEIN_MOVE_SE);
				*pos = w;					//座標更新
				result = 1;
			}
		}
		*Command = 0;	//コマンドクリア
	}else{
		CursorPosChange(*pos,CursorAct,side);
	}

	return result;
}


//------------------------------------------------------------------
/**
 * 随時送信データを送る（主にカーソルの位置を送信する）
 *
 * @param   netID		
 * @param   pos		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
void TradeListCommSend(int netID, int command, int pos)
{
	
	u8 data = pos;

	CommSendData(command,&data,1);
}


//==============================================================================
/**
 * @brief   送信データが前回の送信データと違うときだけ送信する
 *
 * @param   wk		
 * @param   command		
 * @param   pos		
 *
 * @retval  none		
 */
//==============================================================================
void TradeListCommDiffSend( TRADELIST_WORK *wk, int command, int pos)
{
	if(pos != wk->posBackup || command != wk->commandBackup){
		TradeListCommSend( CommGetCurrentID(), command, pos );
		wk->posBackup     = pos;
		wk->commandBackup = command;

		OS_Printf("Id:%d command=%d pos=%dを送信\n", CommGetCurrentID(), command, pos);
	}
}


//------------------------------------------------------------------
/**
 * 
 *
 * @param   party		
 * @param   no		
 *
 * @retval  void *		
 */
//------------------------------------------------------------------
static void *GetPartyAdrs(POKEPARTY *party, int no)
{
	u32 adrs = (u32)party;
	
	return (void*)(adrs+no*POKEPARTY_SEND_ONCE_SIZE);
}


//==============================================================================
/**
 * ポケモンデータを送信する（通信の親子で関数を替える）
 *
 * @param   netID		
 * @param   party		
 * @param   no		
 *
 * @retval  none		
 */
//==============================================================================
void TradeListCommSendPokeData(int netID, POKEPARTY *party, int no)
{
	if(CommIsConnect(netID)){			// デバッグで一人用を動かすかもしれないので念のため
		u8 data = no;
		CommSendHugeData(CT_POKEDATA,GetPartyAdrs(party,no),POKEPARTY_SEND_ONCE_SIZE);
	}
}

//==============================================================================
/**
 * @brief   リボン情報送信
 *
 * @param   sv		
 * @param   no		
 *
 * @retval  none		
 */
//==============================================================================
static void TradeListCommSpRibbonDate(  SAVEDATA *sv )
{
	u8 *p = SaveData_GetSpRibbon( sv );
	int i;
	
	CommSendData( CT_SP_RIBBON_INFO, p, HAIFU_RIBBON_MAX);

}

//------------------------------------------------------------------
/**
 * $brief   しりあいグループデータの送信
 *
 * @param   mystatus		
 * @param   friendlist		
 * @param   sendbuf		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void CommSendFriendList( MYSTATUS *mystatus, FRIEND_LIST *friendlist, FRIEND_LIST *sendbuf )
{
	int i;

	// 送信データの作成
	PM_strcpy( sendbuf->name, MyStatus_GetMyName( mystatus ));	// 名前
	sendbuf->id       = MyStatus_GetID(mystatus);				// ID
	sendbuf->region   = MyStatus_GetRegionCode(mystatus);		// リージョン
	sendbuf->rom_code = MyStatus_GetRomCode(mystatus);			// ROM
	sendbuf->sex      = MyStatus_GetMySex(mystatus);			// 性別
	
	for(i=0;i<FRIENDLIST_FRIEND_MAX;i++){						// 自分の知り合いのIDを
		sendbuf->group_id[i]      = friendlist[i].id;			// 知り合いの知り合いとしては渡すために整形
		sendbuf->group_romcode[i] = friendlist[i].rom_code;
		sendbuf->group_region[i]  = friendlist[i].region;
		sendbuf->group_sex[i]     = friendlist[i].sex;
	}


	// 送信
	CommSendHugeData( CT_FRINEDLIST, sendbuf, sizeof(FRIEND_LIST) );
	
}

//------------------------------------------------------------------
/**
 * @brief   ペラップボイス送信
 *
 * @param   pv		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void CommSendPerapVoice( PERAPVOICE *pv )
{
	CommSendHugeData( CT_PERAPVOICE, pv, PERAPVOICE_LENGTH );
}

//------------------------------------------------------------------
/**
 * 通常移動
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int trade_seq_normal(TRADELIST_WORK *wk)
{
	ControlCursor(&wk->CommWork[0]);

	if(sys.trg & PAD_BUTTON_A){
		if(wk->CommWork[0]==0){
			if(wk->cursor_pos[0]==CURSOR_END_POS){
				wk->func = trade_seq_endyesno;
			}else if(wk->cursor_pos[0]<6){
				wk->func = trade_seq_mypoke;
			}else if(wk->cursor_pos[0]>=6 && wk->cursor_pos[0]<CURSOR_END_POS){
				wk->func = trade_seq_friendpoke;
			}
		}
	}
	return MODE_NORMAL;
}

// ステータス画面で表示するフラグの列（ビットテーブルにすればいいのに…）
static const u8 StatusPageTable[]={
	PST_PAGE_INFO,			// 「ポケモンじょうほう」
	PST_PAGE_MEMO,			// 「トレーナーメモ」
	PST_PAGE_PARAM,			// 「ポケモンのうりょく」
	PST_PAGE_CONDITION,		// 「コンディション」
	PST_PAGE_B_SKILL,		// 「たたかうわざ」
	PST_PAGE_C_SKILL,		// 「コンテストわざ」
	PST_PAGE_RIBBON,		// 「きねんリボン」
	PST_PAGE_RET,			// 「もどる」
	PST_PAGE_MAX

};


//------------------------------------------------------------------
/**
 * @brief   ステータスが呼ばれたので全て破棄してステータス呼び出し
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static void poke_status_setup( TRADELIST_WORK *wk, int side )
{

	if(side==0){
		// 自分のてもち
		wk->statusParam.ppd        = wk->MyPokeParty;
		wk->statusParam.max        = PokeParty_GetPokeCount(wk->param->myparty);
//		wk->statusParam.perap      = (PERAPVOICE*)wk->perap_buf[CommGetCurrentID()];
		wk->statusParam.perap      = NULL;
		PokeStatus_PlayerSet( &wk->statusParam, CommInfoGetMyStatus(CommGetCurrentID()) );

	}else{
		// 相手のてもち（ペラップボイスもセットする）
		wk->statusParam.ppd        = wk->FriendPokeParty;
		wk->statusParam.max        = PokeParty_GetPokeCount(wk->FriendPokeParty);
		wk->statusParam.perap      = (PERAPVOICE*)wk->perap_buf[CommGetCurrentID()^1];
		PokeStatus_PlayerSet( &wk->statusParam, CommInfoGetMyStatus(CommGetCurrentID()^1) );
	}
	wk->statusParam.ppt        = PST_PP_TYPE_POKEPARTY;
	wk->statusParam.pos        = wk->cursor_pos[0]%6;
	wk->statusParam.mode       = PST_MODE_NO_WAZACHG;	// 技入れ替え禁止にする
	wk->statusParam.waza       = 0;
	wk->statusParam.ev_contest = PokeStatus_ContestFlagGet(wk->param->savedata);
	wk->statusParam.zukan_mode = wk->param->zukanmode;
	wk->statusParam.cfg        = wk->param->config;
	wk->statusParam.ribbon     = SaveData_GetSpRibbon(wk->param->savedata);
	PokeStatus_PageSet( &wk->statusParam, StatusPageTable );
	
	wk->subproc = PROC_Create( &PokeStatusProcData, &wk->statusParam, HEAPID_TRADELIST );
	
	wk->status_side            = side;
}
//------------------------------------------------------------------
/**
 * 終了ＹＥＳＮＯ
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int trade_seq_endyesno(TRADELIST_WORK *wk )
{
	GF_BGL_ScrFill(	wk->bgl, GF_BGL_FRAME0_M, 0, 0, 0, 32, 24,  0);
	TradeListWindowPrint(
		&wk->TradeListWin[BMP_M_MES3_WIN],
		mes_dstrade_04_04,FONT_TALK,
		wk->MsgManager,
		wk->PokeNameWordSet
	);
	wk->func = trade_seq_endyesno_wait;

	return MODE_NORMAL;
	
}

//------------------------------------------------------------------
/**
 * 終了ＹＥＳＮＯ待ち
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int trade_seq_endyesno_wait(TRADELIST_WORK *wk)
{
	switch(TradeListYesNoFunc(wk->bgl, &wk->YesNoMenu, &wk->yesnoseq)){
	case 0:
		GF_BGL_ScrFill(	wk->bgl, GF_BGL_FRAME0_M, 0, 0, 0, 32, 24,  0);
		TradeListWindowPrint(
			&wk->TradeListWin[BMP_M_MES3_WIN],
			mes_dstrade_04_07,FONT_TALK,
			wk->MsgManager,
			wk->PokeNameWordSet
		);
		// やめる事を決定
		TradeListCommDiffSend( wk, CT_TRADE_DECIDE, DECIDE_COMMAND_END);
		wk->func   = trade_seq_end;
		wk->result = TRADELIST_END_FINISH;
		break;
	case BMPMENU_CANCEL:
		GF_BGL_ScrFill(	wk->bgl, GF_BGL_FRAME0_M, 0, 0, 0, 32, 24,  0);
		TradeListWindowPrint(
			&wk->TradeListWin[BMP_M_MES1_WIN],
			mes_dstrade_02_01,FONT_TALK,
			wk->MsgManager,
			wk->PokeNameWordSet
		);
		wk->func = trade_seq_normal;
		break;
	default:
		break;
	}

	return MODE_NORMAL;
}



//------------------------------------------------------------------
/**
 * @brief   キャンセルした
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int trade_seq_return(TRADELIST_WORK *wk)
{
	GF_BGL_ScrFill(	wk->bgl, GF_BGL_FRAME0_M, 0, 0, 0, 32, 24,  0);
	TradeListWindowPrint(
		&wk->TradeListWin[BMP_M_MES3_WIN],
		wk->fail_reason,FONT_TALK,
		wk->MsgManager,
		wk->PokeNameWordSet
	);
	wk->func = trade_seq_return_wait;
	
	return MODE_NORMAL;
}

//------------------------------------------------------------------
/**
 * @brief   キャンセル後のボタン待ち
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int trade_seq_return_wait(TRADELIST_WORK *wk)
{
	if(sys.trg & PAD_BUTTON_A){
		GF_BGL_ScrFill(	wk->bgl, GF_BGL_FRAME0_M, 0, 0, 0, 32, 24,  0);
		TradeListWindowPrint(
			&wk->TradeListWin[BMP_M_MES1_WIN],
			mes_dstrade_02_01,FONT_TALK,
			wk->MsgManager,
			wk->PokeNameWordSet
		);
		wk->func=trade_seq_normal;
		trade_icon_reappear( wk );
	}

	return MODE_NORMAL;
}



//------------------ここからともだち手帳

#define _FRIENDNOTE_END_TIMING   (19)    // ともだち手帳入力完了同期

// 手帳登録のメッセージの表示
static void _friendMessagePrint(TRADELIST_WORK* wk, int msgNo)
{
    TradeListWindowPrint(
        &wk->TradeListWin[BMP_M_MES3_WIN],
        msgNo,
        FONT_TALK,
        wk->friendMsgManager,
        wk->friendWordSet
        );
}


//------------------------------------------------------------------
/**
 * 削除はやめとく？YESNO
 * @param   wk		
 * @retval  int		
 */
//------------------------------------------------------------------
static int trade_seq_friend_endyesno( TRADELIST_WORK* wk )
{
    int i;
    switch(TradeListYesNoFunc(wk->bgl, &wk->YesNoMenu, &wk->yesnoseq)){
	case 0:
		wk->func = trade_seq_friend_regist_init;
		break;
	case BMPMENU_CANCEL:
        _friendMessagePrint(wk,msg_wifi_note_add_02);
        wk->func = trade_seq_friend_regist_del_yesno;
		break;
	default:
        break;
	}
	return MODE_NORMAL;
}



//------------------------------------------------------------------
/**
 * 削除メニュー表示
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------

static int trade_seq_friend_regist_erase_yesno( TRADELIST_WORK* wk )
{
    MYSTATUS* pMyStatus;
    int i;
    switch(TradeListYesNoFunc(wk->bgl, &wk->YesNoMenu, &wk->yesnoseq)){
	case 0:
        // 消す+追加
        WifiList_ResetData(wk->pWifiList, wk->erasePos);
        dwc_friendWrite(wk->savedata, wk->addFriendNo,WIFILIST_FRIEND_MAX-1,HEAPID_TRADELIST, FALSE);
		wk->func = trade_seq_friend_regist_init;
		break;
	case BMPMENU_CANCEL:
        pMyStatus = CommInfoGetMyStatus(wk->addFriendNo);
        WORDSET_RegisterPlayerName(wk->friendWordSet, 0, pMyStatus);
        _friendMessagePrint(wk,msg_wifi_note_add_03);
        wk->func = trade_seq_friend_endyesno;
		break;
	default:
        break;
	}
	return MODE_NORMAL;
}

//------------------------------------------------------------------
/**
 * 削除メニュー表示
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------

static int trade_seq_friend_regist_delmenu_wait( TRADELIST_WORK* wk )
{
    int ret;
    MYSTATUS* pMyStatus;

    ret = BmpListMain(wk->lw);
    switch(ret){
    case BMPLIST_NULL:
        return MODE_NORMAL;
    case BMPLIST_CANCEL:
		Snd_SePlay( SEQ_SE_DP_SELECT );
        pMyStatus = CommInfoGetMyStatus(wk->addFriendNo);
        WORDSET_RegisterPlayerName(wk->friendWordSet, 0, pMyStatus);
        _friendMessagePrint(wk,msg_wifi_note_add_03);
        wk->func = trade_seq_friend_endyesno;
        break;
    default:
		Snd_SePlay( SEQ_SE_DP_SELECT );
        wk->erasePos = ret;
        {
            MYSTATUS* pMy = MyStatus_AllocWork(HEAPID_TRADELIST);
            MyStatus_SetMyName(pMy,WifiList_GetFriendNamePtr(wk->pWifiList,ret));
            WORDSET_RegisterPlayerName(wk->friendWordSet, 0, pMy);
            sys_FreeMemoryEz(pMy);
        }
        _friendMessagePrint(wk,msg_wifi_note_add_04);
        wk->func = trade_seq_friend_regist_erase_yesno;
        break;
    }

    BmpMenuWinClear(&wk->listWin, WINDOW_TRANS_ON );
    GF_BGL_BmpWinDel(&wk->listWin);
    BmpListExit(wk->lw, NULL, NULL);
    BMP_MENULIST_Delete( wk->menulist );
	return MODE_NORMAL;
}

//------------------------------------------------------------------
/**
 * 削除メニュー表示
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------

static int trade_seq_friend_regist_delmenu_init( TRADELIST_WORK* wk )
{
    BMPLIST_HEADER list_h;
    int count = WifiList_GetFriendDataNum(wk->pWifiList);
    int line = 5;

    //BMPウィンドウ生成
    wk->menulist = BMP_MENULIST_Create( count+1, HEAPID_TRADELIST );
	{
		MSGDATA_MANAGER* msgman;
        STRBUF* pExpStrBuf = STRBUF_Create(100,HEAPID_TRADELIST);
		int i=0;

        for(i=0; i < WIFILIST_FRIEND_MAX ; i++){
            if(WifiList_IsFriendData( wk->pWifiList, i )){
                STRBUF_SetStringCode(pExpStrBuf, WifiList_GetFriendNamePtr(wk->pWifiList, i));
                BMP_MENULIST_AddString( wk->menulist, pExpStrBuf, i);
            }
		}
        BMP_MENULIST_AddArchiveString( wk->menulist, wk->friendMsgManager,
                                       msg_wifi_note_12, BMPLIST_CANCEL);
        STRBUF_Delete(pExpStrBuf);
    }
    wk->lw = TradeListMenuInit(wk->menulist, count, &wk->listWin, wk->bgl);
    
    wk->func = trade_seq_friend_regist_delmenu_wait;
	return MODE_NORMAL;
}

//------------------------------------------------------------------
/**
 * ともだち手帳削除確認
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int trade_seq_friend_regist_del_yesno(TRADELIST_WORK* wk)
{
    MYSTATUS* pMyStatus;
    int i;
    switch(TradeListYesNoFunc(wk->bgl, &wk->YesNoMenu, &wk->yesnoseq)){
	case 0:
		wk->func = trade_seq_friend_regist_delmenu_init;
		break;
	case BMPMENU_CANCEL:
        pMyStatus = CommInfoGetMyStatus(wk->addFriendNo);
        WORDSET_RegisterPlayerName(wk->friendWordSet, 0, pMyStatus);
        _friendMessagePrint(wk,msg_wifi_note_add_03);
        wk->func = trade_seq_friend_endyesno;
		break;
	default:
		break;
	}
	return MODE_NORMAL;
}

//------------------------------------------------------------------
/**
 * ともだち手帳登録選択
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int trade_seq_friend_regist_yesno(TRADELIST_WORK* wk)
{
    int i;

    switch(TradeListYesNoFunc(wk->bgl, &wk->YesNoMenu, &wk->yesnoseq)){
	case 0:
		wk->func = trade_seq_friend_regist_init;
        // 登録
        for(i = 0; i < WIFILIST_FRIEND_MAX;i++){
            if( !WifiList_IsFriendData( wk->pWifiList, i ) ){
                dwc_friendWrite(wk->savedata, wk->addFriendNo,i,HEAPID_TRADELIST, FALSE);
                break;
            }
        }
        if(i == WIFILIST_FRIEND_MAX){
            // 書き込めない場合
            _friendMessagePrint(wk,msg_wifi_note_add_02);
            wk->func = trade_seq_friend_regist_del_yesno;
            return FALSE;
        }
		break;
	case BMPMENU_CANCEL:
        wk->func = trade_seq_friend_regist_init;
		break;
	default:
		break;
	}
	return MODE_NORMAL;
}

//------------------------------------------------------------------
/**
 * ともだち手帳終了同期待ち
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------

static int trade_seq_friend_regist_timing(TRADELIST_WORK* wk)
{
    if(CommIsTimingSync(_FRIENDNOTE_END_TIMING)){
		return MODE_END_SELECT;
    }
	return MODE_NORMAL;
}


//------------------------------------------------------------------
/**
 * ともだち手帳登録開始
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int trade_seq_friend_regist_init(TRADELIST_WORK* wk)
{
    int i;
    MYSTATUS* pMyStatus;

    wk->addFriendNo = -1;
    for(i = 0; i < CommGetConnectNum(); i++){
        if(wk->friendNetID[i] == DWCFRIEND_NODATA){
            wk->addFriendNo = i;
            wk->friendNetID[i] = DWCFRIEND_INLIST;
            break;
        }
    }
    if(wk->addFriendNo == -1){  // 登録完了
        MSGMAN_Delete( wk->friendMsgManager );
        WORDSET_Delete( wk->friendWordSet );
        CommTimingSyncStart( _FRIENDNOTE_END_TIMING );
		TradeListWindowPrint(
			&wk->TradeListWin[BMP_M_MES3_WIN],
			mes_dstrade_04_07,FONT_TALK,
			wk->MsgManager,
			wk->PokeNameWordSet
		);

        wk->func = trade_seq_friend_regist_timing;
        return MODE_NORMAL;
    }
	//手帳を持っていたら
	if( MyItem_CheckItem( SaveData_GetMyItem(wk->savedata),
							ITEM_TOMODATITETYOU,1,HEAPID_TRADELIST) == TRUE ){
        pMyStatus = CommInfoGetMyStatus(wk->addFriendNo);
        WORDSET_RegisterPlayerName(wk->friendWordSet, 0, pMyStatus);
        _friendMessagePrint(wk,msg_wifi_note_add_01);
        wk->func = trade_seq_friend_regist_yesno;
        return MODE_NORMAL;
    }
    // 持ってないならAUTO
    {
        WIFI_LIST* pList = SaveData_GetWifiListData(wk->savedata);
        for(i = 0; i < WIFILIST_FRIEND_MAX;i++){
            if( !WifiList_IsFriendData( pList, i ) ){
                dwc_friendWrite(wk->savedata, wk->addFriendNo,
                                i, HEAPID_TRADELIST, FALSE);
                break;
            }
        }
    }
    wk->func = trade_seq_friend_regist_init;
    return MODE_NORMAL;
}

//------------------------------------------------------------------
/**
 * ともだち手帳登録検査    k.ohno
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int trade_seq_friend_regist(TRADELIST_WORK* wk)
{
    if(FALSE == dwc_friendAutoInputCheck(wk->savedata, wk->friendNetID, HEAPID_TRADELIST)){
        OHNO_PRINT("今回の登録は無い\n");
        CommTimingSyncStart( _FRIENDNOTE_END_TIMING );

		TradeListWindowPrint(
			&wk->TradeListWin[BMP_M_MES3_WIN],
			mes_dstrade_04_07,FONT_TALK,
			wk->MsgManager,
			wk->PokeNameWordSet
		);

        wk->func = trade_seq_friend_regist_timing;
        return MODE_NORMAL;  // 今回の登録は無い
    }
    wk->friendWordSet    = WORDSET_Create( HEAPID_TRADELIST );
    wk->friendMsgManager = MSGMAN_Create( MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_wifi_note_dat, HEAPID_TRADELIST );
    wk->pWifiList = SaveData_GetWifiListData(wk->savedata);

    wk->func = trade_seq_friend_regist_init;
	return MODE_NORMAL;
}
//------------------ここまでともだち手帳

//------------------------------------------------------------------
/**
 * 終了
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int trade_seq_end(TRADELIST_WORK *wk)
{
	if(wk->end_flag[0]!=0 && wk->end_flag[1]!=0){
		if(wk->end_flag[0]==1 && wk->end_flag[1]==1){
            wk->func = trade_seq_friend_regist;
		}else{
			wk->func = trade_seq_return;
		}
		wk->end_flag[0] = 0;
		wk->end_flag[1] = 0;
		wk->fail_reason = mes_dstrade_04_08;	// 交換はキャンセルされました。
	}
	return MODE_NORMAL;
}


//------------------------------------------------------------------
/**
 * 自分のポケモンを選んだ
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int trade_seq_mypoke(TRADELIST_WORK *wk )
{
	BMPMENU_HEADER temp;

	temp.font  = FONT_SYSTEM;
	temp.x_max = 1;
	temp.y_max = 3;
	temp.line_spc = 0;
	temp.c_disp_f = 0;
	temp.loop_f   = 0;
	
	WORDSET_RegisterPokeNickName(wk->WindowStrWordSet, 0, 
		PPPPointerGet(PokeParty_GetMemberPointer(wk->MyPokeParty, wk->cursor_pos[0])));
	
	GF_BGL_ScrFill(	wk->bgl, GF_BGL_FRAME0_M, 0, 0, 0, 32, 24,  0);
	TradeListWindowPrint(
		&wk->TradeListWin[BMP_M_MES2_WIN],
		mes_dstrade_02_02,FONT_TALK,
		wk->MsgManager,
		wk->WindowStrWordSet
	);
	
	wk->BmpMenuList = BMP_MENULIST_Create( 3, HEAPID_TRADELIST );
	BMP_MENULIST_AddArchiveString( wk->BmpMenuList, wk->MsgManager, mes_dstrade_03_01, 0 );		// 「つよさをみる」
	BMP_MENULIST_AddArchiveString( wk->BmpMenuList, wk->MsgManager, mes_dstrade_03_02, 1 );		// 「こうかんする」
	BMP_MENULIST_AddArchiveString( wk->BmpMenuList, wk->MsgManager, mes_dstrade_03_03, 2 );
	
	temp.menu = wk->BmpMenuList;
	temp.win  = &wk->TradeListWin[BMP_M_SELECT1_WIN];

	TradeListWinWrite( &wk->TradeListWin[BMP_M_SELECT1_WIN] );
	wk->BmpMenuWork = BmpMenuAddEx( &temp, 8, 0, 0, HEAPID_TRADELIST, PAD_BUTTON_B );
	

	wk->func = trade_seq_mypoke_menu;
	
	return MODE_NORMAL;
}

#ifdef DEBUG_PAD_ON
	#define SELECT_STATUS	( 1 )
	#define SELECT_TRADE	( 0 )
	#define SELECT_MODORU	( 2 )
#else
	#define SELECT_STATUS	( 0 )
	#define SELECT_TRADE	( 1 )
	#define SELECT_MODORU	( 2 )
#endif

//------------------------------------------------------------------
/**
 * $brief   自分のポケモンの時の選択
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int trade_seq_mypoke_menu(TRADELIST_WORK *wk )
{
	switch(BmpMenuMain( wk->BmpMenuWork )){
	case SELECT_STATUS:		// つよさをみる
		GF_BGL_ScrFill(	wk->bgl, GF_BGL_FRAME0_M, 0, 0, 0, 32, 24,  0);
		TradeListWindowPrint(
			&wk->TradeListWin[BMP_M_MES1_WIN],
			mes_dstrade_02_01,FONT_TALK,
			wk->MsgManager,
			wk->PokeNameWordSet
		);
		BmpMenuExit( wk->BmpMenuWork, NULL );
		BMP_MENULIST_Delete( wk->BmpMenuList );
		wk->func = trade_seq_normal;
		return MODE_STATUS_SELECT;
		break;
	case SELECT_TRADE:		// こうかんする
		GF_BGL_ScrFill(	wk->bgl, GF_BGL_FRAME0_M, 0, 0, 0, 32, 24,  0);
		TradeListWindowPrint(
			&wk->TradeListWin[BMP_M_MES3_WIN],
			mes_dstrade_04_01,FONT_TALK,
			wk->MsgManager,
			wk->PokeNameWordSet
		);
		BmpMenuExit( wk->BmpMenuWork, NULL );
		BMP_MENULIST_Delete( wk->BmpMenuList );
		wk->func = trade_seq_decide;
		break;
	case SELECT_MODORU: case BMPMENU_CANCEL:	// キャンセル
		GF_BGL_ScrFill(	wk->bgl, GF_BGL_FRAME0_M, 0, 0, 0, 32, 24,  0);
		TradeListWindowPrint(
			&wk->TradeListWin[BMP_M_MES1_WIN],
			mes_dstrade_02_01,FONT_TALK,
			wk->MsgManager,
			wk->PokeNameWordSet
		);
		BmpMenuExit( wk->BmpMenuWork, NULL );
		BMP_MENULIST_Delete( wk->BmpMenuList );
		wk->func = trade_seq_normal;
		break;
	}
	return MODE_NORMAL;

}



//------------------------------------------------------------------
/**
 * $brief   交換ポケモン決定
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int trade_seq_decide(TRADELIST_WORK *wk )
{
	GF_BGL_ScrFill(	wk->bgl, GF_BGL_FRAME0_M, 0, 0, 0, 32, 24,  0);
	TradeListWindowPrint(
		&wk->TradeListWin[BMP_M_MES3_WIN],
		mes_dstrade_04_01,FONT_TALK,
		wk->MsgManager,
		wk->PokeNameWordSet
	);

	// 交換するポケモンを決定したことを通知
	TradeListCommDiffSend( wk, CT_TRADE_DECIDE, DECIDE_COMMAND_NEXT);
	
	wk->func = trade_seq_decide_wait;
	
	return MODE_NORMAL;
}

//------------------------------------------------------------------
/**
 * $brief   決定待ち
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int trade_seq_decide_wait(TRADELIST_WORK *wk )
{
	if(wk->end_flag[0]!=0 && wk->end_flag[1]!=0){
		if(wk->end_flag[0]==DECIDE_COMMAND_NEXT && wk->end_flag[1]==DECIDE_COMMAND_NEXT){
			wk->func = trade_seq_icon_move;
		}else{
			wk->func = trade_seq_return;
		}
		wk->fail_reason = mes_dstrade_04_03;	// 交換はキャンセルされました。
		wk->end_flag[0] = 0;
		wk->end_flag[1] = 0;


	}

	return MODE_NORMAL;
}


//------------------------------------------------------------------
/**
 * @brief   交換することにしたポケモンアイコンが中央に移動する
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int trade_seq_icon_move( TRADELIST_WORK *wk )
{
	int i;

	// 選択したポケモン以外は隠す
	for(i=0;i<6;i++){
		if(i!=wk->cursor_pos[0]){
			CLACT_SetDrawFlag(wk->PokeIconActWork[i],0);
			if(wk->pokeInfo[i].item){
				CLACT_SetDrawFlag(wk->PokeItemActWork[i],0);
			}
			if(wk->pokeInfo[i].customball){
				CLACT_SetDrawFlag(wk->PokeCBallActWork[i],0);
			}
		}
		GF_BGL_BmpWinOffVReq(&wk->TradeListWin[BMP_M_MYPOKENAME0_WIN+i]);
		if(i!=(wk->cursor_pos[1]-6)){
			CLACT_SetDrawFlag(wk->PokeIconActWork[i+6],0);
			if(wk->pokeInfo[i+6].item){
				CLACT_SetDrawFlag(wk->PokeItemActWork[i+6],0);
			}
			if(wk->pokeInfo[i+6].customball){
				CLACT_SetDrawFlag(wk->PokeCBallActWork[i+6],0);
			}
		}
		GF_BGL_BmpWinOffVReq(&wk->TradeListWin[BMP_M_FRIENDPOKENAME0_WIN+i]);
	}
	
	// カーソルを隠す
	CLACT_SetDrawFlag(wk->clActWork[0],0);
	CLACT_SetDrawFlag(wk->clActWork[1],0);

	// 移動初期設定
	AnimePosSet(wk->myanimpos, main_cursor_pos[wk->cursor_pos[0]][0]+POKEICON_DIFFX, 
							   main_cursor_pos[wk->cursor_pos[0]][1]+POKEICON_DIFFY,
							   6*8, 6*8);
	AnimePosSet(wk->f_animpos, main_cursor_pos[wk->cursor_pos[1]][0]+POKEICON_DIFFX, 
							   main_cursor_pos[wk->cursor_pos[1]][1]+POKEICON_DIFFY,
							   22*8, 6*8);

	wk->animcount = 0;
	wk->func      = trade_seq_icon_move_wait;

	return MODE_NORMAL;
}

//------------------------------------------------------------------
/**
 * @brief   移動アニメ用始点・終点指定
 *
 * @param   animpos[]		
 * @param   sx		
 * @param   sy		
 * @param   ex		
 * @param   ey		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void AnimePosSet(VecFx32 animpos[], int sx, int sy, int ex, int ey)
{
	animpos[0].x = FX32_ONE*sx;
	animpos[0].y = FX32_ONE*sy;
	animpos[1].x = FX32_ONE*ex;
	animpos[1].y = FX32_ONE*ey;
	
}

#define ICON_MOVE_MAX	(20)

//------------------------------------------------------------------
/**
 * @brief   アイコン移動
 *
 * @param   icon		
 * @param   item		
 * @param   count		
 * @param   pos[]		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void PokeIconPosSet( CLACT_WORK_PTR icon, CLACT_WORK_PTR item, CLACT_WORK_PTR cball, int count, VecFx32 pos[], POKE_INFO *info )
{
	VecFx32 pokeVex,itemVex,cballVex;

	// ポケモンアイコン座標
	pokeVex.x = pos[0].x + ((pos[1].x-pos[0].x)/ICON_MOVE_MAX)*count;
	pokeVex.y = pos[0].y + ((pos[1].y-pos[0].y)/ICON_MOVE_MAX)*count;

	CLACT_SetMatrix(icon, &pokeVex);

	// アイテム座標
	if(info->item){
		itemVex.x = pokeVex.x+20*FX32_ONE;
		itemVex.y = pokeVex.y+(16+6)*FX32_ONE;
		CLACT_SetMatrix(item, &itemVex);
	}

	if(info->customball){
		cballVex.x = pokeVex.x+(20+8)*FX32_ONE;
		cballVex.y = pokeVex.y+(16+6)*FX32_ONE;
		CLACT_SetMatrix(cball, &cballVex);
	}
}

//------------------------------------------------------------------
/**
 * @brief   アイコン移動終了待ち
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int trade_seq_icon_move_wait( TRADELIST_WORK *wk )
{
	wk->animcount++;

	// アイコン移動アニメ
	PokeIconPosSet( wk->PokeIconActWork[wk->cursor_pos[0]],
					wk->PokeItemActWork[wk->cursor_pos[0]],
					wk->PokeCBallActWork[wk->cursor_pos[0]],
					wk->animcount, wk->myanimpos, &wk->pokeInfo[wk->cursor_pos[0]] );
	PokeIconPosSet( wk->PokeIconActWork[wk->cursor_pos[1]],
					wk->PokeItemActWork[wk->cursor_pos[1]],
					wk->PokeCBallActWork[wk->cursor_pos[1]],
					wk->animcount, wk->f_animpos, &wk->pokeInfo[wk->cursor_pos[1]] );
	if(wk->animcount==ICON_MOVE_MAX+1){
		// 中央に２体の名前を表示
		PokeNamePrint(&wk->TradeListWin[BMP_M_EX_MYPOKENAME_WIN], 
						wk->MyPokeParty, wk->cursor_pos[0], TRADELIST_POKENAME_W, CENTER_PRINT);
		PokeNamePrint(&wk->TradeListWin[BMP_M_EX_F_POKENAME_WIN], 
						wk->FriendPokeParty, wk->cursor_pos[1]-6, TRADELIST_POKENAME_W, CENTER_PRINT);

		// 下画面右パネルを表示する
		SubLcd_RightPanelOn(wk, wk->cursor_pos[1]);
		wk->func = trade_seq_trade_yesno;
		CLACT_SetDrawFlag( wk->ExchangeArrow, 1 );

	}	

	return MODE_NORMAL;
}

//------------------------------------------------------------------
/**
 * @brief   元の位置に戻して表示も戻す
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static void trade_icon_reappear( TRADELIST_WORK *wk )
{
	int i;
	VecFx32 tmpVex;

	// 中央に表示したポケモンの名前を隠す
	GF_BGL_BmpWinOffVReq(&wk->TradeListWin[BMP_M_EX_MYPOKENAME_WIN]);
	GF_BGL_BmpWinOffVReq(&wk->TradeListWin[BMP_M_EX_F_POKENAME_WIN]);

	// 隠したポケモンを全て戻す
	for(i=0;i<TRADELIST_POKE_MAX;i++){
		if(wk->pokeInfo[i].exist!=0){

			Clact_SetPos( wk->PokeIconActWork[i],
							main_cursor_pos[i][0] + POKEICON_DIFFX,
							main_cursor_pos[i][1] + POKEICON_DIFFY );


			CLACT_SetDrawFlag(wk->PokeIconActWork[i],1);

			if(wk->pokeInfo[i].item){
				Clact_SetPos(wk->PokeItemActWork[i],
								main_cursor_pos[i][0] + POKEITEM_DIFFX,
								main_cursor_pos[i][1] + POKEITEM_DIFFY );

				CLACT_SetDrawFlag(wk->PokeItemActWork[i],1);
			}

			if(wk->pokeInfo[i].customball){
				Clact_SetPos( wk->PokeCBallActWork[i], 
								main_cursor_pos[i][0] + POKECBALL_DIFFX, 
								main_cursor_pos[i][1] + POKEITEM_DIFFY );
				CLACT_SetDrawFlag(wk->PokeCBallActWork[i],1);
			}

			GF_BGL_BmpWinOnVReq(&wk->TradeListWin[BMP_M_MYPOKENAME0_WIN+i]);
		}
	}
	
	// カーソル表示復活
	CLACT_SetDrawFlag(wk->clActWork[0],1);
	CLACT_SetDrawFlag(wk->clActWork[1],1);

	// 下画面右側非表示
	PokeStr_SubLcdOff(wk->TradeListWin, 1, wk);
	CLACT_SetDrawFlag(wk->SubLCDIconActWork[3], 0);	

	// 交換矢印隠す
	CLACT_SetDrawFlag( wk->ExchangeArrow, 0 );


}
//------------------------------------------------------------------
/**
 * $brief   お互いのポケモンで交換するかを質問する
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int trade_seq_trade_yesno(TRADELIST_WORK *wk )
{
	
	GF_BGL_ScrFill(	wk->bgl, GF_BGL_FRAME0_M, 0, 0, 0, 32, 24,  0);
	WORDSET_RegisterPokeNickName(wk->WindowStrWordSet, 0, 
		PPPPointerGet(PokeParty_GetMemberPointer(wk->MyPokeParty,     wk->cursor_pos[0])));
	WORDSET_RegisterPokeNickName(wk->WindowStrWordSet, 1, 
		PPPPointerGet(PokeParty_GetMemberPointer(wk->FriendPokeParty, wk->cursor_pos[1]-6)));

	TradeListWindowPrint(
		&wk->TradeListWin[BMP_M_MES3_WIN],
		mes_dstrade_04_02,FONT_TALK,
		wk->MsgManager,
		wk->WindowStrWordSet
	);
	
	
	wk->func = trade_seq_trade_yesno_wait;
	return MODE_NORMAL;
}

//------------------------------------------------------------------
/**
 * $brief   「交換しますか？」はい・いいえ
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int trade_seq_trade_yesno_wait(TRADELIST_WORK *wk)
{
	switch(TradeListYesNoFunc(wk->bgl, &wk->YesNoMenu, &wk->yesnoseq)){
	case 0:
		// 交換する
		if(wk->pokeInfo[wk->cursor_pos[0]].customball==0){
			// てもちが無くならない？
			if(TradeTemochiCheck( wk )){
				GF_BGL_ScrFill(	wk->bgl, GF_BGL_FRAME0_M, 0, 0, 0, 32, 24,  0);
				TradeListWindowPrint(
					&wk->TradeListWin[BMP_M_MES3_WIN],
					mes_dstrade_04_01,FONT_TALK,
					wk->MsgManager,
					wk->PokeNameWordSet
				);
				wk->func = trade_seq_trade_yesno_result;
				TradeListCommDiffSend( wk, CT_TRADE_DECIDE, DECIDE_COMMAND_YES);
				wk->result = TRADELIST_END_DEMO;
			}else{
				// てもちがなくなるから交換してはいけない
				wk->func = trade_seq_trade_yesno_result;
				TradeListCommDiffSend( wk, CT_TRADE_DECIDE, DECIDE_COMMAND_NO);
			}
		}else{
			// カスタムボールがついているなら
			wk->func = trade_seq_customball_yesno;
		}
		break;
	case BMPMENU_CANCEL:
		// やめる事を決定
		GF_BGL_ScrFill(	wk->bgl, GF_BGL_FRAME0_M, 0, 0, 0, 32, 24,  0);
		TradeListWindowPrint(
			&wk->TradeListWin[BMP_M_MES3_WIN],
			mes_dstrade_04_01,FONT_TALK,
			wk->MsgManager,
			wk->PokeNameWordSet
		);
		wk->func = trade_seq_trade_yesno_result;
		TradeListCommDiffSend( wk, CT_TRADE_DECIDE, DECIDE_COMMAND_NO);
		break;
	default:
		break;
	}

	return MODE_NORMAL;
}



//------------------------------------------------------------------
/**
 * $brief   カスタムボールがついている時ははずれる事を聞く
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int trade_seq_customball_yesno(TRADELIST_WORK *wk )
{
	
	GF_BGL_ScrFill(	wk->bgl, GF_BGL_FRAME0_M, 0, 0, 0, 32, 24,  0);

	// ボールカスタマイズが外れますがよろしいですか？
	TradeListWindowPrint(
		&wk->TradeListWin[BMP_M_MES3_WIN],
		mes_dstrade_04_15,FONT_TALK,
		wk->MsgManager,
		wk->WindowStrWordSet
	);
	
	
	wk->func = trade_seq_customball_yesno_wait;
	return MODE_NORMAL;
}

//------------------------------------------------------------------
/**
 * $brief   「カスタムボールが外れますがよろしいですか？」はい・いいえ
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int trade_seq_customball_yesno_wait(TRADELIST_WORK *wk)
{
	switch(TradeListYesNoFunc(wk->bgl, &wk->YesNoMenu, &wk->yesnoseq)){
	case 0:
		GF_BGL_ScrFill(	wk->bgl, GF_BGL_FRAME0_M, 0, 0, 0, 32, 24,  0);
		TradeListWindowPrint(
			&wk->TradeListWin[BMP_M_MES3_WIN],
			mes_dstrade_04_01,FONT_TALK,
			wk->MsgManager,
			wk->PokeNameWordSet
		);
		wk->func = trade_seq_trade_yesno_result;
		// 交換する
		TradeListCommDiffSend( wk, CT_TRADE_DECIDE, DECIDE_COMMAND_YES);
		wk->result = TRADELIST_END_DEMO;
		break;
	case BMPMENU_CANCEL:
		GF_BGL_ScrFill(	wk->bgl, GF_BGL_FRAME0_M, 0, 0, 0, 32, 24,  0);
		TradeListWindowPrint(
			&wk->TradeListWin[BMP_M_MES3_WIN],
			mes_dstrade_04_01,FONT_TALK,
			wk->MsgManager,
			wk->PokeNameWordSet
		);
		wk->func = trade_seq_trade_yesno_result;
		// やめる事を決定
		TradeListCommDiffSend( wk, CT_TRADE_DECIDE, DECIDE_COMMAND_NO);
		break;
	default:
		break;
	}

	return MODE_NORMAL;
}


//------------------------------------------------------------------
/**
 * $brief   交換しますか？の決定待ち
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int trade_seq_trade_yesno_result( TRADELIST_WORK *wk )
{
	if(wk->end_flag[0]!=0 && wk->end_flag[1]!=0){
		if(wk->end_flag[0]==DECIDE_COMMAND_YES && wk->end_flag[1]==DECIDE_COMMAND_YES){
            wk->tradeNum++;
			wk->func = trade_seq_go_next;
		}else{
			wk->func = trade_seq_return;
		}
		wk->end_flag[0] = 0;
		wk->end_flag[1] = 0;
		if(TradeTemochiCheck(wk)){
			wk->fail_reason = mes_dstrade_04_03;	// 交換はキャンセルされました。
		}else{
			wk->fail_reason = mes_dstrade_04_13;	// てもちがなくなってしまう
		}

	}

	return MODE_NORMAL;
	
}


//------------------------------------------------------------------
/**
 * $brief   ポケモン交換
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static  int trade_seq_go_next( TRADELIST_WORK *wk )
{

    CommInfoSetTradeResult(wk->savedata, 1); // 交換回数の記録 k.ohno
	// ポケモンデータ入れ替え
	PokemonDataExchange(wk->MyPokeParty, wk->FriendPokeParty, wk->cursor_pos[0], wk->cursor_pos[1]-6, wk->param);

	wk->func = trade_seq_return;
	return MODE_END_SELECT;

}


//#ifdef PM_DEBUG	
//	// セーブテスト用に呼び出し
//	wk->func = trade_seq_save_text;
//	return MODE_NORMAL;
//#else
//	// こっちが正しい
//	wk->func = trade_seq_return;
//	return MODE_END_SELECT;
//#endif


static int trade_seq_save_text( TRADELIST_WORK *wk )
{


	// ともだちを待っています。
	TradeListWindowPrint(
			&wk->TradeListWin[BMP_M_MES3_WIN],
			mes_dstrade_04_01,FONT_TALK,
			wk->MsgManager,
			wk->PokeNameWordSet
		);

	wk->func = trade_seq_save_func;
	wk->saveseq = 0;
	
	return MODE_NORMAL;
}

int CommSaveSequence( SAVEDATA *savedata, int *seq, int *wait );

static int trade_seq_save_func( TRADELIST_WORK *wk )
{
	
//	SaveData_Save(wk->savedata);
//	CommTimingSyncStart( 5 );

	if(CommSaveSequence(wk->savedata, &wk->saveseq, &wk->savewait)){
		wk->func = trade_seq_save_wait;
	}

	return MODE_NORMAL;

}


static int trade_seq_save_wait( TRADELIST_WORK *wk )
{
//	if(CommIsTimingSync(5)){
	
		wk->func = trade_seq_return;
		return MODE_END_SELECT;
//	}
//	return MODE_NORMAL;
	
}


//==============================================================================
/**
 * $brief   通信中セーブシーケンス
 *			
 *
 * @param   savedata	セーブデータへのポインタ
 * @param   seq			シーケンス管理ワーク（かならず0に初期化してから呼び始めてください）
 * @param   wait		ウェイト管理ワーク
 *
 * @retval  int			0:終了してない	1が返ってくるまで呼び続けてください
 */
//==============================================================================
int CommSaveSequence( SAVEDATA *savedata, int *seq, int *wait )
{	
	switch(*seq){
	case 0:
		// セーブ開始同期
		CommTimingSyncStart( 252 );
		(*seq)++;
		break;
	case 1:
		// 親機の所持金額をウェイトに利用する
		if(CommIsTimingSync(252)){
//			*wait = CommInfoGetMacAddress( 0 )[3] % 90;
			MYSTATUS *mystatus = CommInfoGetMyStatus(0);
			*wait = MyStatus_GetGold(mystatus) % 90;
			(*seq)++;
			OS_TPrintf("セーブシーケンス：１回目同期");
		}
		break;

	case 2:
		// ウェイトが0になったらセーブ開始
		if(*wait==0){
//			SaveData_Save(savedata);
			(*seq)++;
		}
		(*wait)--;
		break;
	case 3:
		// セーブ終了後に同期
		CommTimingSyncStart( 253 );
		(*seq)++;
		break;
	case 4:
		// 同期したら終了
		if(CommIsTimingSync(253)){
			OS_TPrintf("セーブシーケンス：２回目同期");
			(*seq)=0;
			return 1;
		}
		break;
	}
	return 0;
}
//------------------------------------------------------------------
/**
 * 相手のポケモンを選んだ→メニュー
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int trade_seq_friendpoke(TRADELIST_WORK *wk )
{

	BMPMENU_HEADER temp;

	temp.font  = FONT_SYSTEM;
	temp.x_max = 1;
	temp.y_max = 2;
	temp.line_spc = 0;
	temp.c_disp_f = 0;
	temp.loop_f   = 0;
	
	WORDSET_RegisterPokeNickName(wk->WindowStrWordSet, 0, 
		PPPPointerGet(PokeParty_GetMemberPointer(wk->FriendPokeParty, wk->cursor_pos[0]-6)));
	
	GF_BGL_ScrFill(	wk->bgl, GF_BGL_FRAME0_M, 0, 0, 0, 32, 24,  0);
	TradeListWindowPrint(
		&wk->TradeListWin[BMP_M_MES2_WIN],
		mes_dstrade_02_02,FONT_TALK,
		wk->MsgManager,
		wk->WindowStrWordSet
	);
	
	wk->BmpMenuList = BMP_MENULIST_Create( 2, HEAPID_TRADELIST );
	BMP_MENULIST_AddArchiveString( wk->BmpMenuList, wk->MsgManager, mes_dstrade_03_01, 0 );
	BMP_MENULIST_AddArchiveString( wk->BmpMenuList, wk->MsgManager, mes_dstrade_03_03, 1 );
	
	temp.menu = wk->BmpMenuList;
	temp.win  = &wk->TradeListWin[BMP_M_SELECT2_WIN];

	TradeListWinWrite( &wk->TradeListWin[BMP_M_SELECT2_WIN] );
	wk->BmpMenuWork = BmpMenuAddEx( &temp, 8, 0, 0, HEAPID_TRADELIST, PAD_BUTTON_B );
	

	wk->func = trade_seq_friend_menu;

	return MODE_NORMAL;
	
}

//------------------------------------------------------------------
/**
 * $brief   相手のポケモンを選択しているときのメニュー待ち
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int trade_seq_friend_menu(TRADELIST_WORK *wk )
{
	switch(BmpMenuMain( wk->BmpMenuWork )){
	// つよさをみる
	case 0:
		GF_BGL_ScrFill(	wk->bgl, GF_BGL_FRAME0_M, 0, 0, 0, 32, 24,  0);
		TradeListWindowPrint(
			&wk->TradeListWin[BMP_M_MES1_WIN],
			mes_dstrade_02_01,FONT_TALK,
			wk->MsgManager,
			wk->PokeNameWordSet
		);
		wk->func = trade_seq_normal;
		BmpMenuExit( wk->BmpMenuWork, NULL );
		BMP_MENULIST_Delete( wk->BmpMenuList );
		return MODE_STATUS_SELECT;
		break;

	// もどる
	case 1:case BMPMENU_CANCEL:
		GF_BGL_ScrFill(	wk->bgl, GF_BGL_FRAME0_M, 0, 0, 0, 32, 24,  0);
		TradeListWindowPrint(
			&wk->TradeListWin[BMP_M_MES1_WIN],
			mes_dstrade_02_01,FONT_TALK,
			wk->MsgManager,
			wk->PokeNameWordSet
		);
		BmpMenuExit( wk->BmpMenuWork, NULL );
		BMP_MENULIST_Delete( wk->BmpMenuList );
		wk->func = trade_seq_normal;
		break;
	}
	return MODE_NORMAL;

}



//------------------------------------------------------------------
/**
 * $brief   ポケモンデータ交換ルーチン
 *
 * @param   my		
 * @param   your		
 * @param   mysel		
 * @param   yoursel		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void PokemonDataExchange(POKEPARTY *my, POKEPARTY *your, int mysel, int yoursel, TRADELIST_PARAM *param)
{
	POKEMON_PARAM *pp,*pp2;
	
	pp  = PokemonParam_AllocWork(HEAPID_TRADELIST);
	pp2 = PokemonParam_AllocWork(HEAPID_TRADELIST);
	
	//一旦コピー
	PokeCopyPPtoPP(PokeParty_GetMemberPointer(  my,   mysel), pp  );
	PokeCopyPPtoPP(PokeParty_GetMemberPointer(your, yoursel), pp2 );

	// 交換デモ用にパラメータ渡し
	PokeCopyPPtoPP( pp  ,param->result_sendPoke);		// 出すポケモン
	PokeCopyPPtoPP( pp2 ,param->result_recvPoke);		// もらうポケモン
	MyStatus_Copy(  CommInfoGetMyStatus(CommGetCurrentID()^1),  param->result_partner );	// 相手の情報
	param->exchangepos = mysel;


	// たまごで無ければ、なつき度設定（７０に）
	if(PokeParaGet(pp2, ID_PARA_tamago_flag, NULL)==0){
		u8 natsuki = FIRST_NATUKIDO;
		PokeParaPut( pp2, ID_PARA_friend, &natsuki );

	}

	// トレーナーメモ情報埋め込み
	TrainerMemoSetPP( pp2,	CommInfoGetMyStatus(CommGetCurrentID()),TRMEMO_ONTRADE_PLACESET, 0, HEAPID_WORLD);

	// 自分が受け取るポケモンのカスタムボール情報をクリア
	PokePara_CustomBallDataInit( pp2 );

	// てもちからペラップがいなくなったら声データを消去する(このタイミングだと相手からペラップをもらっても声が消える）
	if(PokeParty_PokemonCheck( my, MONSNO_PERAPPU )==0){
		PERAPVOICE *pv = SaveData_GetPerapVoice( param->savedata );
		PERAPVOICE_ClearExistFlag( pv );
	}

	// 図鑑等の登録処理
	SaveData_GetPokeRegister( param->savedata, pp2 );

	// もらったポケモンを追加
	PokeCopyPPtoPP( pp2, PokeParty_GetMemberPointer(  my,   mysel) );
	PokeCopyPPtoPP(  pp, PokeParty_GetMemberPointer(your, yoursel) );

	// 冒険ノート用データ作成
	SetFnoteData( param->fnote, pp2 );

	// レコードデータ処理
	RECORD_Inc( param->record, RECID_COMM_TRADE );


	sys_FreeMemoryEz(pp);
	sys_FreeMemoryEz(pp2);
}


//------------------------------------------------------------------
/**
 * @brief   冒険ノート用のデータを書き込む
 *
 * @param   fnote		
 * @param   pp		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void SetFnoteData( FNOTE_DATA *fnote, POKEMON_PARAM *pp )
{
	void *FnoteWork;
	MYSTATUS *friend = CommInfoGetMyStatus(CommGetCurrentID()^1);
	STRCODE  MonsName[MONS_NAME_SIZE+EOM_SIZE];

	PokeParaGet(pp, ID_PARA_nickname, MonsName);

	FnoteWork = FNOTE_SioUnionChangeDataMake( (STRCODE*)MyStatus_GetMyName(friend), 
												MyStatus_GetMySex(friend), 
												MonsName, 
												PokeSexGet(pp), 
												HEAPID_TRADELIST );

	FNOTE_DataSave( fnote, FnoteWork, FNOTE_TYPE_SIO );


}

//------------------------------------------------------------------
/**
 * $brief   下画面の背景を横スクロールさせる
 *
 * @param   wk		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void SubLCD_ScrollFunc( TRADELIST_WORK *wk )
{
	wk->sub_bg2_scroll += 2;
	GF_BGL_ScrollSet( wk->bgl, GF_BGL_FRAME2_S, GF_BGL_SCROLL_X_SET, wk->sub_bg2_scroll );
	GF_BGL_ScrollSet( wk->bgl, GF_BGL_FRAME3_M, GF_BGL_SCROLL_X_SET, wk->sub_bg2_scroll );
}

//------------------------------------------------------------------
/**
 * @brief   セルアクターに整数XYで座標を渡す
 *
 * @param   clact		
 * @param   x		
 * @param   y		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void Clact_SetPos( CLACT_WORK_PTR clact, int x, int y )
{
	VecFx32 tmpVex;

	tmpVex.x = FX32_ONE*x;
	tmpVex.y = FX32_ONE*y;

	CLACT_SetMatrix( clact, &tmpVex);
	
}


//------------------------------------------------------------------
/**
 * @brief   時間アイコン追加
 *
 * @param   wk		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void TimeIconAdd( TRADELIST_WORK *tlw )
{
	tlw->timeWaitWork = TimeWaitIconAdd( &tlw->TradeListWin[BMP_M_MES3_WIN], TALKWIN_FRAME_OFFSET );
}

//------------------------------------------------------------------
/**
 * @brief   時間アイコン消去（NULLチェックする）
 *
 * @param   wk		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void TimeIconDel( TRADELIST_WORK *tlw )
{
	if(tlw->timeWaitWork!=NULL){
		TimeWaitIconDel(tlw->timeWaitWork);
		tlw->timeWaitWork = NULL;
	}
}


//------------------------------------------------------------------
/**
 * @brief   そのポケモンを交換するとてもちがいなくならないか？
 *
 * @param   wk		
 *
 * @retval  int		1:大丈夫	0:ダメ
 */
//------------------------------------------------------------------
static int TradeTemochiCheck( TRADELIST_WORK *wk )
{
	int i;
	int tamagoNum = 0;
	int pokeNum   = PokeParty_GetPokeCount(wk->MyPokeParty);

	// 今選択しているポケモン以外でタマゴはいくつあるか
	for(i=0;i<pokeNum;i++){
		if(i!=wk->cursor_pos[0]){
			tamagoNum += wk->pokeInfo[i].tamago;
		}
	}
	
	// タマゴの数とてもちの数-1なら交換ダメ
	if(tamagoNum==(pokeNum-1)){
		return 0;
	}
	
	return 1;
}


//------------------------------------------------------------------
/**
 * @brief   タイムアウト処理開始
 *
 * @param   wk		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void TimeoutStart( TRADELIST_WORK *wk )
{
	wk->timeOutFlag = 1;
	wk->timeOutWait = 0;
}


//------------------------------------------------------------------
/**
 * @brief   タイムアウト処理
 *
 * @param   wk		
 *
 * @retval  none
 */
//------------------------------------------------------------------
static void TimeoutErrorCheck( TRADELIST_WORK *wk )
{
	// タイムアウトフラグがＯＮで
	if(wk->timeOutFlag){
		wk->timeOutWait++;

		// タイムアウト期間を過ぎたら（ここでは２分）
		if(wk->timeOutWait > TIMEOUT_LIMIT){
			// 通信エラー設定
			CommStateSetError(COMM_ERROR_RESET_OTHER);
			OS_Printf("Timeout...\n");
		}
	}

}

