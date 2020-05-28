//===================================================================
/**
 * @file	agbpokemon.c	
 * @bfief	AGBポケモンカセット→DP間のポケモンデータ移動
 * @author	Satoshi Mitsuhara
 * @date	06.05.30
 *
 * $Id: agbpokemon.c,v 1.63 2006/08/14 11:00:46 mitsuhara Exp $
 */
//===================================================================

// BG0	メッセージウィンドウ
// BG1	ポケモンステータス表示ウィンドウ
// BG2	背景
// BG3	未使用

#include "common.h"
#include "system/main.h"
#include "system/procsys.h"
#include "system/wordset.h"
#include "system/wipe.h"
#include "system/arc_util.h"
#include "system/msgdata_util.h"
#include "system/fontproc.h"
#include "system/window.h"
#include "system/snd_tool.h"
#include "system/touch_subwindow.h"
#include "system/pmfprint.h"
#include "system/agb_str.h"

#include "gflib/touchpanel.h"
#include "itemtool/item.h"

#include "system/clact_tool.h"
#include "poketool/monsno.h"
#include "poketool/pokeicon.h"
#include "poketool/poke_tool.h"
#include "../poketool/poke_tool_def.h"		/* ##### */
#include "savedata/pokepark_data.h"
#include "savedata/savedata.h"
#include "savedata/config.h"

#include "battle/battle_server.h"
#include "battle/wazano_def.h"

#include "agbpoke_access.h"
#include "agbpoke_tool.h"
#include "agbpoke_util.h"

#include "msgdata/msg.naix"
#include "msgdata/msg_pokemonpark.h"

#include "demo/title.h"

#include "comm_mystery_func.h"
#include "mystery.naix"
#include "mysterylib.h"


//============================================================================================
//	定数定義
//============================================================================================
#define SetSeq(x)		*seq = (x)

// ポケモンアイコンが始まるVRAM上でのオフセット
#define POKEICON_VRAM_OFFSET ( 0x64 )
#define POKEICON_TRANS_CHARA	(4*4)
#define POKEICON_TRANS_SIZE		(POKEICON_TRANS_CHARA*0x20)
// ポケモンアイコンのパレットを転送するオフセット
#define POKEICON_PAL_OFFSET				(  8 )
//** CharManager PlttManager用 **//
#define RECORD_CHAR_CONT_NUM				(20)
#define RECORD_CHAR_VRAMTRANS_MAIN_SIZE		(2048)
#define RECORD_CHAR_VRAMTRANS_SUB_SIZE		(2048)
#define RECORD_PLTT_CONT_NUM				(20)
// ポケモンの表示設定
#define POKEMON_WIDTH			40
#define POKEMON_HEIGHT			24
#define POKEMON_BASEX			28
#define POKEMON_BASEY			40


#define POKEMON_ICON_MAX			30
#define POKEMON_SCREEN_TOUCH_MAX		3
#define POKEMON_TOUCH_ICONMAX		(POKEMON_ICON_MAX+POKEMON_SCREEN_TOUCH_MAX+1)

#define POKEMON_SELECT_MAX			6
#define POKEMON_NOSELECT			-1

#define ICON_CANCEL			(POKEMON_ICON_MAX+0)
#define ICON_ARROWL			(POKEMON_ICON_MAX+1)
#define ICON_ARROWR			(POKEMON_ICON_MAX+2)
#define ICON_TERMINATE			(POKEMON_ICON_MAX+3)


typedef struct {
  GF_BGL_BMPWIN *win;
  int flag;
  int sx, sy;
  int width, height;
  int dx, dy;
  int base;
  int screen;
  FONT_TYPE font;
  GF_PRINTCOLOR color;
  GF_PRINTCOLOR clrcolor;
  int msgid;
  STRCODE *msgp;
  STRBUF *msg;
  WORDSET *word;
  int msgwait;

  int m_id;
} REGWIN;
#define MSG_FLAG_CENTER		0x01
#define MSG_FLAG_NOCLEAR	0x02
#define MSG_FLAG_NOREDRAW	0x04
#define MSG_FLAG_FRAME		0x08
#define MSG_FLAG_TALKWIN	0x10



typedef struct {
  CLACT_WORK_PTR clact;
  CLACT_WORK_PTR item;
  int monsno;
} POKEMON_ICON;

typedef struct {
  CLACT_WORK_PTR icon;
  int pokeno;
  int boxno;
} MARK_ICON;


typedef struct {
  int save_seq;
  int wait_frame;
  void *time_icon;

} SAVEWORK;


typedef struct {
  int vadrs;				// VRAMアドレス
  int palno;				// パレット番号
  CLACT_WORK_PTR icon;			// CLACT
  u8 chbuf[POKEICON_TRANS_SIZE];	// キャラクタバッファ
} POKEBUF;



typedef struct {
  int cartridge_type;				// VERSION_xxxx (pm_version.h参照)
  int agberror;
  int msg_flag;
  int jiffy;
  
  SAVEDATA *sv;
  MYSTATUS *mst;
  CONFIG *cfg;
  int win_type;
  
  GF_BGL_INI *bgl;

  int next_seq;

  // セルアクター関連
  CLACT_SET_PTR	clactSet;				// セルアクターセット 
  CLACT_U_EASYRENDER_DATA renddata;			// 簡易レンダーデータ
  CLACT_U_RES_MANAGER_PTR resMan[CLACT_U_RES_MAX];	// リソースマネージャ
  CLACT_U_RES_OBJ_PTR resObjTbl[CLACT_U_RES_MAX];	// リソースオブジェテーブル
  CLACT_HEADER clActHeaderMain;
  // ポケモンアイコン 30体分
  POKEMON_ICON icon[POKEMON_ICON_MAX];
  RECT_HIT_TBL iconrect[POKEMON_TOUCH_ICONMAX];

  // とじる
  CLACT_WORK_PTR cancel[4];	// ４種類
  // 右→
  CLACT_WORK_PTR arrowr[4];	// ４種類
  // 左←
  CLACT_WORK_PTR arrowl[4];	// ４種類
  // 決定マーク
  MARK_ICON mark[POKEMON_SELECT_MAX];	// ６つ分(選択できるポケモンの数)
  int selected;
  
  // 決定画面のポケモンアクター
  CLACT_WORK_PTR check_poke[POKEMON_SELECT_MAX];
  REGWIN cwin;

  // メッセージウィンドウ関連
  GF_BGL_BMPWIN	TitleWin;
  GF_BGL_BMPWIN	BoxNameWin;
  GF_BGL_BMPWIN	CheckWin;
  
  // AGBカートリッジアクセス関係
  int cartridge_status;
  int load_status;
  u32 buffer[AGBPOKE_BUFFERSIZE/sizeof(u32)];
  POKEBOX_SAVE_DATA *boxdata;
  int CurrentBox;

  int wait_seq;

  // 下画面ウインドウシステム
  TOUCH_SW_SYS *TouchSubWindowSys;

  SAVEWORK save_work;

  // ポケモンアイコンの高速表示用
  POKEBUF pokebuf[POKEMON_ICON_MAX];
  void (*DrawFunc)(void);
  
} AGBCARTRIDGE_WORK;


POKEBUF *_PokeBufPtr;


enum {

  AGBCARTRIDGE_SEQ_INIT_CARTRIDGE,	/* AGBカートリッジ初期化 */
  AGBCARTRIDGE_SEQ_PREINIT_SCREEN,	/* スクリーン初期化 */
  
  AGBCARTRIDGE_SEQ_CHECK_USER,		/* カートリッジのユーザー確認 */
  AGBCARTRIDGE_SEQ_CHECK_USER_YESNO,

  AGBCARTRIDGE_SEQ_CHECK_FINAL,
  AGBCARTRIDGE_SEQ_CHECK_FINAL_YESNO,
  AGBCARTRIDGE_SEQ_DISP_MESSAGE,
  AGBCARTRIDGE_SEQ_DISP_MESSAGE_YESNO,
  
  AGBCARTRIDGE_SEQ_ERROR_YESNO_SCREEN,
  AGBCARTRIDGE_SEQ_ERROR_YESNO_SCREEN2,
  AGBCARTRIDGE_SEQ_ERROR_YESNO_SCREEN3,
  AGBCARTRIDGE_SEQ_ERROR_SCREEN,	/* タイトルへ戻るエラー表示 */

  AGBCARTRIDGE_SEQ_INIT_SCREEN,		/* スクリーン初期化 その２ */
  AGBCARTRIDGE_SEQ_MAIN,		/* メイン処理 */
  AGBCARTRIDGE_SEQ_SELECT_WARNING,	/* 選択できないポケモンを選んだ */

  AGBCARTRIDGE_SEQ_WAIT_CHECK_SCREEN,	/* 確認画面へ行く間のちょっとの「間」 */
  AGBCARTRIDGE_SEQ_CREATE_CHECK_SCREEN,	/* 確認画面作成 */
  AGBCARTRIDGE_SEQ_CREATE_CHECK_TOUCH1,	/* 「つれていきます」のタップ待ち */
  AGBCARTRIDGE_SEQ_CREATE_CHECK_TOUCH,	/* 「ホントにいいの？」のタップ待ち */
  AGBCARTRIDGE_SEQ_CREATE_CHECK_MAIN,	/* 確認画面処理 */
  AGBCARTRIDGE_SEQ_RETURN_SELECT,	/* 選択画面に戻るための初期化 */

  AGBCARTRIDGE_SEQ_SAVE,		/* セーブ処理 */
  AGBCARTRIDGE_SEQ_SAVE_END,		/* タップ待ち */
  
  AGBCARTRIDGE_SEQ_WAIT_FADE,		/* フェードを待って次のシーケンスへ */
  AGBCARTRIDGE_SEQ_FINISH,		/* この画面の後始末＋最後 */
  AGBCARTRIDGE_SEQ_MAX
};


enum {
  SAVE_SEQ_INIT,			/* セーブ処理初期化 */

  SAVE_SEQ_WAIT_INIT_TIMING1,		/* タイミングずらし期間初期化その１ */
  SAVE_SEQ_WAIT_TIMING1,		/* タイミングずらし期間その１ */
  
  SAVE_SEQ_DSSAVE_INIT,			/* DS側のセーブ初期化 */
  SAVE_SEQ_DSSAVE_MAIN,			/* DS側のセーブメイン */

  SAVE_SEQ_AGBSAVE_CHECK,		/* AGB側のセーブテスト(ガイドラインに基づく処理) */
  SAVE_SEQ_AGBSAVE_INIT,		/* AGB側のセーブ初期化 */
  SAVE_SEQ_AGBSAVE_MAIN,		/* AGB側のセーブメイン */
#if 0
  SAVE_SEQ_WAIT_INIT_TIMING2,		/* タイミングずらし期間初期化その２ */
  SAVE_SEQ_WAIT_TIMING2,		/* タイミングずらし期間その２ */
#endif
  SAVE_SEQ_SAVE_LAST,			/* 最後のセクタをセーブ */
  SAVE_SEQ_SAVE_FINAL,			/* 最後を待つ */

  /* ↓関数の戻り値として使用↓ */
  SAVE_STATUS_WRITING,			/* 書き込み処理中 */
  SAVE_STATUS_WRITE_SUCCESS,		/* 書き込みに成功した */
  SAVE_STATUS_WRITE_ERROR,		/* 書き込みに失敗した */
  
  SAVE_SEQ_MAX
};


// ウィンドウ関連
#define	FONT_PALNO_NORMAL	15	/* ノーマルパレット */

#define	AGBPOKEMON_BLACK	(GF_PRINTCOLOR_MAKE( 1, 2, 0))
#define	AGBPOKEMON_WHITE	(GF_PRINTCOLOR_MAKE(15, 2, 0))
#define	AGBPOKEMON_WHITEBLACK	(GF_PRINTCOLOR_MAKE(15, 2, 15))
#define	AGBPOKEMON_BLACKBLACK	(GF_PRINTCOLOR_MAKE( 1, 2, 15))

#define AGBPOKEMON_CHRBASE	0
#define AGBPOKEMON_TITLEBASE	0xA0
#define AGBPOKEMON_STATUSBASE	(14*2+AGBPOKEMON_TITLEBASE)

#define AGBPOKEMON_FRAMECHR	0x3F0
#define AGBPOKEMON_FRAMECOL	14
#define AGBPOKEMON_TFRAMECHR	(AGBPOKEMON_FRAMECHR - TALK_WIN_CGX_SIZ)
#define AGBPOKEMON_TFRAMECOL	13

#define AGBPOKEMON_YESWIN	(30*4+1)
#define AGBPOKEMON_NOWIN	(8*2+30*4+1)


// 連れて行けない「ひでんわざ」のリスト
static int WazaHidenTable[] = {
  WAZANO_IAIGIRI,			// いあいぎり
  WAZANO_SORAWOTOBU,			// そらをとぶ
  WAZANO_NAMINORI,			// なみのり
  WAZANO_KAIRIKI,			// かいりき
  WAZANO_HURASSYU,			// フラッシュ
  WAZANO_IWAKUDAKI,			// いわくだき
  WAZANO_TAKINOBORI,			// たきのぼり
  WAZANO_DAIBINGU,			// ダイビング
};

// ユーザー確認用のメッセージテーブル
static int UsrCheckMsgTable[] = {
  NULL,		// unknown
  msg_pokepark_02,			// バージョン：AGBサファイア
  msg_pokepark_01,			// バージョン：AGBルビー
  msg_pokepark_03,			// バージョン：AGBエメラルド
  msg_pokepark_04,			// バージョン：AGBファイアーレッド
  msg_pokepark_05,			// バージョン：AGBリーフグリーン
};

// セーブ中のメッセージ
static int SaveMsgTable[] = {
  NULL,		// unknown
#if (PM_VERSION == VERSION_DIAMOND)
  msg_pokepark_22,			// "サファイア　と　ダイヤモンド　の\nポケモンレポートを　かいています"
  msg_pokepark_20,			// "ルビー　と　ダイヤモンド　の\nポケモンレポートを　かいています"
  msg_pokepark_24,			// "エメラルド　と　ダイヤモンド　の\nポケモンレポートを　かいています"
  msg_pokepark_26,			// "ファイアレッド　と　ダイヤモンド　の\nポケモンレポートを　かいています"
  msg_pokepark_28,			// "リーフグリーン　と　ダイヤモンド　の\nポケモンレポートを　かいています"
#elif (PM_VERSION == VERSION_PEARL)
  msg_pokepark_23,			// "サファイア　と　パール　の\nポケモンレポートを　かいています"
  msg_pokepark_21,			// "ルビー　と　パール　の\nポケモンレポートを　かいています"
  msg_pokepark_25,			// "エメラルド　と　パール　の\nポケモンレポートを　かいています"
  msg_pokepark_27,			// "ファイアレッド　と　パール　の\nポケモンレポートを　かいています"
  msg_pokepark_29,			// "リーフグリーン　と　パール　の\nポケモンレポートを　かいています"
#endif
};

static u8 BgPalTable[] = {
  0,		// NULL
  2,		// サファイヤ
  1,		// ルビー
  3,		// エメラルド
  4,		// ファイアレッド
  5,		// リーフグリーン
};


static int ErrorMsgTable[] = {
  NULL,
  msg_pokepark_39,			// AGBのセーブデータが読めなかったよ
  msg_pokepark_33,			// ２４じかんたたないと…
  msg_pokepark_34,			// ほんたいがかわったかとけいがうごいたよ
  msg_pokepark_34,			// ほんたいがかわったかとけいがうごいたよ
  msg_pokepark_07,			// ボックスに６たいいません
  msg_pokepark_09,			// すでにあずかってます…
  msg_pokepark_35,			// いまから２４じかんつれてこれません
};

#if (PM_VERSION == VERSION_DIAMOND)
#define CHECK_FINAL_MSG		msg_pokepark_36
#define SAVE_SUCCESS_MSG	msg_pokepark_31
#elif (PM_VERSION == VERSION_PEARL)
#define CHECK_FINAL_MSG		msg_pokepark_37
#define SAVE_SUCCESS_MSG	msg_pokepark_32
#endif


//============================================================================================
//	プロトタイプ宣言
//============================================================================================
static void DrawBoxTitle(AGBCARTRIDGE_WORK *wk, int boxnumber);
static void CheckSelectPokemonIcon(AGBCARTRIDGE_WORK *wk);
static void InitUpMessageWindow(AGBCARTRIDGE_WORK *wk);
static void AgbCartridge_ReqYesNoIcon(AGBCARTRIDGE_WORK *wk);
static void AgbCartridgeDataUpdate(AGBCARTRIDGE_WORK *wk);
void STRBUF_SetStringCodeOrderLength( STRBUF* strbuf, const STRCODE* str, u32 len );

extern void STRBUF_SetStringCode( STRBUF* strbuf, const STRCODE* sz );

//============================================================================================
//	グローバル変数
//============================================================================================

extern void AGBPPPtoDSPPP(PokemonPasoParam *agb_ppp,POKEMON_PASO_PARAM *ds_ppp);


//------------------------------------------------------------------
/**
 * @brief	AGBではありえないポケモンの判定
 * @param	NONE
 * @return	TRUE: OK  FALSE: 不正ポケモン
 */
//------------------------------------------------------------------
#define MONSNO_AGB_END	413
static BOOL CheckInJusticePokemon(int agb_monsno)
{
  if(agb_monsno <= 0 || agb_monsno >= MONSNO_AGB_END)
    return TRUE;
  return FALSE;
}


//------------------------------------------------------------------
/**
 * @brief	wk->cartridge_type へ値を設定
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
static void AgbCartridge_SetCartridgeType(AGBCARTRIDGE_WORK *wk)
{
  switch(agbpoke_getPokemonType()){
  case CASTYPE_RUBY:	wk->cartridge_type = VERSION_RUBY;	break;
  case CASTYPE_SAPPHIRE:wk->cartridge_type = VERSION_SAPPHIRE;	break;
  case CASTYPE_GREEN:	wk->cartridge_type = VERSION_GREEN;	break;
  case CASTYPE_RED:	wk->cartridge_type = VERSION_RED;	break;
  case CASTYPE_EMERALD:	wk->cartridge_type = VERSION_EMERALD;	break;
  default:		wk->cartridge_type = -1;		break;
  }
}


//------------------------------------------------------------------
/**
 * @brief	セーブシーケンス
 * @param	NONE
 * @return	NONE
 *
 * 最悪な状態であっても増殖はするけれど欠落はしないようにする
 * 処理の順番としては以下の通り
 * １、ＤＳのラスト１セクタ以外を全てセーブ
 * ２、ＡＧＢのラスト１セクタ以外を全てセーブ
 * ３、タイミングずらし(タイミングを計って増殖されないようにするため)
 * ４、ＤＳとＡＧＢのラストセクタを一気にセーブ
 * ５、終了
*/
//------------------------------------------------------------------
static int SaveSequence(AGBCARTRIDGE_WORK *wk)
{
  int ret;
  u8 backupbuf[16];
  SAVE_RESULT result;
  POKEPARK_DATA *ppark;
  SAVEWORK *sw = &wk->save_work;

#if 0//def DEBUG_ONLY_FOR_mituhara
  OS_TPrintf("  save_seq = %d\n", sw->save_seq);
#endif
#if 0
  // セーブ失敗テスト
  return SAVE_STATUS_WRITE_SUCCESS;
#endif
  
  switch(sw->save_seq){
  case SAVE_SEQ_INIT:
    // 初期化処理
    AgbCartridgeDataUpdate(wk);
    ppark = SaveData_GetPokeParkData(wk->sv);
    // セーブ管理用データをセット
    POKEPARKDATA_SetMasterData(ppark, agbpoke_GetTrainerID());
    sw->save_seq++;
    break;

  case SAVE_SEQ_WAIT_INIT_TIMING1:
    /* タイミングずらし期間初期化その１ */
    sw->wait_frame = 1 + OS_GetTick() % 120;
    sw->save_seq++;
    break;

  case SAVE_SEQ_WAIT_TIMING1:
    /* タイミングずらし期間その１ */
    if(--sw->wait_frame == 0)
      sw->save_seq++;
    break;

  case SAVE_SEQ_DSSAVE_INIT:
    // DS側のセーブ、初期設定
    SaveData_DivSave_Init(wk->sv, SVBLK_ID_MAX);
    sw->save_seq++;
    break;

  case SAVE_SEQ_DSSAVE_MAIN:
    // DS側のセーブメイン
    result = SaveData_DivSave_Main(wk->sv);
    if(result == SAVE_RESULT_NG)	return SAVE_STATUS_WRITE_ERROR;
    if(result == SAVE_RESULT_LAST)	sw->save_seq++;
    break;

  case SAVE_SEQ_AGBSAVE_CHECK:
    // AGB側のセーブテスト(ガイドラインに基づく処理)
    CTRDG_ReadAgbFlash(0, 0, backupbuf, sizeof(backupbuf));
    sw->save_seq++;
    break;

  case SAVE_SEQ_AGBSAVE_INIT:
    // AGB側のセーブ初期化
    ret = agbpoke_saveEdit_Async();
    if(ret == FALSE){
      sys_SleepOK(SLEEPTYPE_SAVELOAD);
      return SAVE_STATUS_WRITE_ERROR;
    }
    sw->save_seq++;
    break;

  case SAVE_SEQ_AGBSAVE_MAIN:
    // AGB側のセーブメイン
    if(agbpoke_check_status() == AGBPOKE_ERROR_WRITING)
      // 書いている最中だったら１フレーム処理を待つ
      break;
    if(agbpoke_check_status() == AGBPOKE_ERROR_LAST){
      // 最後の１セクタ以外は書き込めた
      sw->save_seq++;
    } else {
      // さらにどんどん書いていく
      ret = agbpoke_saveEdit_check();
      if(ret == AGBPOKE_ERROR_WRITE){
	sys_SleepOK(SLEEPTYPE_SAVELOAD);
	return SAVE_STATUS_WRITE_ERROR;
      }
    }
    break;
#if 0
  case SAVE_SEQ_WAIT_INIT_TIMING2:
    // タイミングずらし期間初期化
    sw->wait_frame = 10 + (wk->jiffy % 60);
    sw->save_seq++;
    break;

  case SAVE_SEQ_WAIT_TIMING2:
    // タイミングずらし期間
    if(--sw->wait_frame == 0)
      sw->save_seq++;
    break;
#endif
  case SAVE_SEQ_SAVE_LAST:
    // 最後のセクタをセーブ
    // まずはDS側をセーブ
    do {
      result = SaveData_DivSave_Main(wk->sv);
      //      OS_TPrintf("----- DS : %d\n", result);
      if(result == SAVE_RESULT_NG)	return SAVE_STATUS_WRITE_ERROR;
    } while(result != SAVE_RESULT_OK);
    // 次にAGB側をセーブ(内部ではAsyncが呼ばれているので一旦mainへ処理を戻す)
    agbpoke_saveEdit_check();
    sys_SleepNG(SLEEPTYPE_SAVELOAD); // DS側でSleepONにされているので再度OFF
    sw->save_seq++;
    break;

  case SAVE_SEQ_SAVE_FINAL:
    // AGB側の終了を待つ
    ret = agbpoke_saveEdit_check();
    if(ret == AGBPOKE_ERROR_WRITE){
      sys_SleepOK(SLEEPTYPE_SAVELOAD);
      return SAVE_STATUS_WRITE_ERROR;
    }
    if(ret == AGBPOKE_ERROR_OK){
      //      OS_TPrintf("■■■セーブ終了です■■■\n");
      sys_SleepOK(SLEEPTYPE_SAVELOAD);
      return SAVE_STATUS_WRITE_SUCCESS;
    }
    break;
  }

  return SAVE_STATUS_WRITING;
}


//------------------------------------------------------------------
/**
 * @brief	ＤＳカードへのセーブ処理
 * @param	wk
 * @return	NONE
 */
//------------------------------------------------------------------
static void SaveDsCard(AGBCARTRIDGE_WORK *wk)
{
  POKEPARK_DATA *ppark;
  SAVE_RESULT result;

  ppark = SaveData_GetPokeParkData(wk->sv);
  // セーブ管理用データをセット
  POKEPARKDATA_SetMasterData(ppark, agbpoke_GetTrainerID());
  // 実際のセーブ処理
  sys_SoftResetNG(SOFTRESET_TYPE_SAVELOAD);
  result = SaveData_Save(wk->sv);
  sys_SoftResetOK(SOFTRESET_TYPE_SAVELOAD);
  //  result = SaveData_SaveParts(wk->sv, SVBLK_ID_MAX);
}


//------------------------------------------------------------------
/**
 * @brief	ＲＡＭ上のＡＧＢカセットデータを更新
 * @brief	ＲＡＭ上のＤＳカードデータを更新
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
static void AgbCartridgeDataUpdate(AGBCARTRIDGE_WORK *wk)
{
  int i, boxno, index;
  u16 monsno;

  POKEMON_PASO_PARAM *ds_ppp_ptr;
  PokemonPasoParam *ppp;
  POKEMON_PARAM ds_ppp;
  POKEPARK_DATA *ppark;

  // DS側のデータを更新
  
  ppark = SaveData_GetPokeParkData(wk->sv);
  ds_ppp_ptr = PPPPointerGet(&ds_ppp);
  // 選択した６匹をポケモンパークのワークへセット
  for(i = 0; i < POKEMON_SELECT_MAX; i++){
    index = wk->mark[i].pokeno;
    boxno = wk->mark[i].boxno;
    ppp = &wk->boxdata->PPPBox[boxno][index];
    // AGBのPPPをDSのPPPへ変換しながら書き込む
    AGBPPPtoDSPPP(ppp, ds_ppp_ptr);
    POKEPARKDATA_SetData(ppark, ds_ppp_ptr, i);
  }


  // ＡＧＢ側のデータを更新
  
  // 選択されたポケモンをボックスから消す
  monsno = 0;
  for(i = 0; i < POKEMON_SELECT_MAX; i++){
    index = wk->mark[i].pokeno;
    boxno = wk->mark[i].boxno;
    // あり得ない事だけど念のためにチェックを入れる
    if(index != POKEMON_NOSELECT && boxno != BOX_NUM){
      AgbPokePasoParaPut(&(wk->boxdata->PPPBox[boxno][index]),ID_AGB_monsno, (u8 *)&monsno);
    }
  }

#if 0
  // 主にデバッグ用に追加しておきます(poke_exist_flagが0ならばmonsnoも0にしておく)
  for(boxno = 0; boxno < BOX_NUM; boxno++){
    for(i = 0; i < POKEMON_ICON_MAX; i++){
      if(AgbPokePasoParaGet(&(wk->boxdata->PPPBox[boxno][i]),ID_AGB_poke_exist_flag, NULL) == 0)
	AgbPokePasoParaPut(&(wk->boxdata->PPPBox[boxno][i]),ID_AGB_monsno, (u8 *)&monsno);
    }
  }
#endif

#if 0//def DEBUG_ONLY_FOR_mituhara
  // ポケモン無限増殖処理(ぐふふ)
  if(sys.cont & PAD_BUTTON_B){
    MATHRandContext16 context;
    u8 name[MONS_NAME_SIZE+1] = { JP_AGB_A__, JP_AGB_B__, JP_AGB_C__, JP_AGB_D__, JP_AGB_E__,
				  JP_AGB_F__, JP_AGB_G__, JP_AGB_H__, JP_AGB_I__, JP_AGB_J__ };
    u8 oyaname[PERSON_NAME_SIZE+1] = { JP_AGB_K__, JP_AGB_L__, JP_AGB_M__, JP_AGB_N__, JP_AGB_O__, JP_AGB_P__, JP_AGB_Q__ };
    
    PokemonPasoParam ppp = wk->boxdata->PPPBox[0][0];
    MATH_InitRand16(&context, 0xabab);

    for(boxno = 0; boxno < BOX_NUM; boxno++){
      for(i = 0; i < POKEMON_ICON_MAX; i++){
	monsno = MATH_Rand16(&context, 386);
	AgbPokePasoParaPut(&ppp, ID_AGB_monsno, (u8 *)&monsno);
#if 0	// 海外版カセットテスト
	monsno = LANG_ENGLISH;
	AgbPokePasoParaPut(&ppp, ID_AGB_country_code, (u8 *)&monsno);
	AgbPokePasoParaPut(&ppp, ID_AGB_nickname, name);
	AgbPokePasoParaPut(&ppp, ID_AGB_oyaname, oyaname);
#endif
	wk->boxdata->PPPBox[boxno][i] = ppp;
      }
    }
  }
#endif
}


//------------------------------------------------------------------
/**
 * @brief	メッセージセンタリング
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
static int GetMessageStartPos(REGWIN *rwin, STRBUF *str, int flag)
{
  int len, width;
  if(flag & MSG_FLAG_CENTER){
    len = FontProc_GetPrintStrWidth(FONT_TALK, (const STRBUF *)str, 0);
    width = rwin->width * 8;
    return (width - len) / 2;
  } else {
    return rwin->dx;
  }
}

//------------------------------------------------------------------
/**
 * @brief	メッセージウィンドウの初期化
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
static void CreateMsgWindow(AGBCARTRIDGE_WORK *wk, REGWIN *rwin, int flag)
{
  STRBUF * msg;
  WORDSET *word;
  MSGDATA_MANAGER *msgman;
  int x, y, msgwait;

  if(rwin->msgwait == 0)	msgwait = MSG_NO_PUT;
  else				msgwait = rwin->msgwait;

  // ウィンドウが登録されていなければ登録
  if(rwin->win->ini == NULL){
    GF_BGL_BmpWinAdd(wk->bgl, rwin->win, rwin->screen,
		     rwin->sx, rwin->sy, rwin->width, rwin->height,
		     FONT_PALNO_NORMAL, rwin->base);
  }
  // ウィンドウ内を消去
  if(!(flag & MSG_FLAG_NOCLEAR))
    GF_BGL_BmpWinDataFill(rwin->win, rwin->clrcolor);

  // メッセージがあれば表示
  if(rwin->msgid != -1){
    // アーカイブから展開して表示
    msgman = MSGMAN_Create(MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_pokemonpark_dat, HEAPID_AGBCARTRIDGE);
    if(rwin->word)	word = rwin->word;
    else		word = WORDSET_Create(HEAPID_AGBCARTRIDGE);
    msg = MSGDAT_UTIL_AllocExpandString(word, msgman, rwin->msgid, HEAPID_AGBCARTRIDGE);
    x = GetMessageStartPos(rwin, msg, flag);
    rwin->m_id = GF_STR_PrintColor(rwin->win, rwin->font, msg, x, rwin->dy, msgwait, rwin->color, NULL);
    STRBUF_Delete(msg);
    if(rwin->word == NULL)
      WORDSET_Delete(word);
    MSGMAN_Delete(msgman);
    rwin->msgid = -1;
  }
  if(rwin->msgp){
    // 文字列を直接表示
    msg = STRBUF_Create(64, HEAPID_AGBCARTRIDGE);
    STRBUF_SetStringCodeOrderLength(msg, rwin->msgp, 64);
    x = GetMessageStartPos(rwin, msg, flag);
    rwin->m_id = GF_STR_PrintColor(rwin->win, rwin->font, msg, x, rwin->dy, msgwait, rwin->color, NULL);
    STRBUF_Delete(msg);
    rwin->msgp = NULL;
  }
  if(rwin->msg){
    // STRBUF形を表示
    x = GetMessageStartPos(rwin, rwin->msg, flag);
    rwin->m_id = GF_STR_PrintColor(rwin->win, rwin->font, rwin->msg, x, rwin->dy, msgwait, rwin->color, NULL);
    rwin->msg = NULL;
  }
  // フラグによって描画
  if(!(flag & MSG_FLAG_NOREDRAW))
    GF_BGL_BmpWinOn(rwin->win);
  // 枠をつける場合もあります
  if(flag & MSG_FLAG_FRAME){
    if(flag & MSG_FLAG_TALKWIN){
      BmpTalkWinWrite(rwin->win, WINDOW_TRANS_ON, AGBPOKEMON_TFRAMECHR, AGBPOKEMON_TFRAMECOL);
    } else {
      BmpMenuWinWrite(rwin->win, WINDOW_TRANS_ON, AGBPOKEMON_FRAMECHR, AGBPOKEMON_FRAMECOL);
    }
  }
}

//------------------------------------------------------------------
/**
 * @brief	キャラクタ、パレットのマネージャー起動
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
static void CharPlttManagerInit(void)
{
  // キャラクタマネージャー初期化
  {
    CHAR_MANAGER_MAKE cm = {
      RECORD_CHAR_CONT_NUM,
      RECORD_CHAR_VRAMTRANS_MAIN_SIZE,
      RECORD_CHAR_VRAMTRANS_SUB_SIZE,
      HEAPID_AGBCARTRIDGE,
    };
    InitCharManager(&cm);
  }
  // パレットマネージャー初期化
  InitPlttManager(RECORD_PLTT_CONT_NUM, HEAPID_AGBCARTRIDGE);
      
  // 読み込み開始位置を初期化
  CharLoadStartAll();
  PlttLoadStartAll();
}


//------------------------------------------------------------------
/**
 * @brief	セルアクターの初期化
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
static void InitCellActor(AGBCARTRIDGE_WORK *wk)
{
  int i;
  // OAMマネージャーの初期化
  NNS_G2dInitOamManagerModule();
  // 共有OAMマネージャ作成
  // レンダラ用OAMマネージャ作成
  // ここで作成したOAMマネージャをみんなで共有する
  REND_OAMInit( 
	       0, 126,		// メイン画面OAM管理領域
	       0, 32,		// メイン画面アフィン管理領域
	       0, 126,		// サブ画面OAM管理領域
	       0, 32,		// サブ画面アフィン管理領域
	       HEAPID_AGBCARTRIDGE);
	
  // セルアクター初期化
  wk->clactSet = CLACT_U_SetEasyInit( 80, &wk->renddata, HEAPID_AGBCARTRIDGE);
  CLACT_U_SetSubSurfaceMatrix( &wk->renddata, 0, (256*FX32_ONE)/*NAMEIN_SUB_ACTOR_DISTANCE*/ );

  //リソースマネージャー初期化
  for(i=0;i<CLACT_U_RES_MAX;i++){		//リソースマネージャー作成
    wk->resMan[i] = CLACT_U_ResManagerInit(3, i, HEAPID_AGBCARTRIDGE);
  }

  //---------上画面用-------------------
  //chara読み込み
  wk->resObjTbl[CLACT_U_CHAR_RES] =
    CLACT_U_ResManagerResAddArcChar(wk->resMan[CLACT_U_CHAR_RES], 
				    ARC_MYSTERY_GRA, NARC_mystery_gba_box_oam_lz_cngr,
				    1, 0, NNS_G2D_VRAM_TYPE_2DMAIN, HEAPID_AGBCARTRIDGE);
      
  //pal読み込み
  wk->resObjTbl[CLACT_U_PLTT_RES] =
    CLACT_U_ResManagerResAddArcPltt(wk->resMan[CLACT_U_PLTT_RES],
				    ARC_MYSTERY_GRA, NARC_mystery_gba_box_oam_nclr,
				    0, 0, NNS_G2D_VRAM_TYPE_2DMAIN, 4, HEAPID_AGBCARTRIDGE);

  //cell読み込み
  wk->resObjTbl[CLACT_U_CELL_RES] =
    CLACT_U_ResManagerResAddArcKindCell(wk->resMan[CLACT_U_CELL_RES],
					ARC_MYSTERY_GRA, NARC_mystery_gba_box_oam_lz_ccer,
					1, 0, CLACT_U_CELL_RES,HEAPID_AGBCARTRIDGE);

  //同じ関数でanim読み込み
  wk->resObjTbl[CLACT_U_CELLANM_RES] =
    CLACT_U_ResManagerResAddArcKindCell(wk->resMan[CLACT_U_CELLANM_RES],
					ARC_MYSTERY_GRA, NARC_mystery_gba_box_oam_lz_canr,
					1, 0, CLACT_U_CELLANM_RES,HEAPID_AGBCARTRIDGE);
  // Chara転送
  CLACT_U_CharManagerSet( wk->resObjTbl[CLACT_U_CHAR_RES] );
  // パレット転送
  CLACT_U_PlttManagerSet( wk->resObjTbl[CLACT_U_PLTT_RES] );
  // ポケモンアイコン用パレットを一気に読み込んでVRAM転送する
  ArcUtil_PalSet( ARC_POKEICON, PokeIconPalArcIndexGet(), PALTYPE_MAIN_OBJ, POKEICON_PAL_OFFSET*0x20,
		  0, HEAPID_AGBCARTRIDGE);
}


//------------------------------------------------------------------
/**
 * @brief	セルアクターヘッダの作成
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
static void SetCellActor(AGBCARTRIDGE_WORK *wk)
{
  // セルアクターヘッダ作成
  CLACT_U_MakeHeader(&wk->clActHeaderMain, 0, 0, 0, 0, CLACT_U_HEADER_DATA_NONE, CLACT_U_HEADER_DATA_NONE,
		     0, 0,
		     wk->resMan[CLACT_U_CHAR_RES],
		     wk->resMan[CLACT_U_PLTT_RES],
		     wk->resMan[CLACT_U_CELL_RES],
		     wk->resMan[CLACT_U_CELLANM_RES],
		     NULL,NULL);
  //まだ何も転送していないから
  GF_Disp_GX_VisibleControl(  GX_PLANEMASK_OBJ, VISIBLE_ON );	//メイン画面OBJ面ＯＮ
}


//------------------------------------------------------------------
/**
 * @brief	CLACT_ADDの雛形を作成
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
static void AgbPokemon_MakeCLACT(CLACT_ADD *add, AGBCARTRIDGE_WORK *wk, CLACT_HEADER *header, int param)
{
  add->ClActSet		= wk->clactSet;
  add->ClActHeader	= &wk->clActHeaderMain;
  add->mat.z		= 0;
  add->sca.x		= FX32_ONE;
  add->sca.y		= FX32_ONE;
  add->sca.z		= FX32_ONE;
  add->rot		= 0;
  add->pri		= 20;
  add->DrawArea		= param;
  add->heap		= HEAPID_AGBCARTRIDGE;
}


//------------------------------------------------------------------
/**
 * @brief	指定番号のボックスからindex番目のポケモンを返す
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
static int GetPokeBoxIndex(AGBCARTRIDGE_WORK *wk, int box, int index)
{
  // AGBの構造体専用関数を用意しています
  // DPの構造体と混ざらないよう、かなり注意してくださいませ
  return AgbPokePasoParaGet(&(wk->boxdata->PPPBox[box][index]), ID_AGB_monsno, NULL);
}

//Add by soga　ここから
//ポケモンアイコン表示で必要なパラメータを追加しました
//------------------------------------------------------------------
/**
 * @brief	指定番号のボックスからindex番目のタマゴフラグを返す
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
static int GetEggFlagBoxIndex(AGBCARTRIDGE_WORK *wk, int box, int index)
{
  // AGBの構造体専用関数を用意しています
  // DPの構造体と混ざらないよう、かなり注意してくださいませ
  return AgbPokePasoParaGet(&(wk->boxdata->PPPBox[box][index]), ID_AGB_tamago_flag, NULL);
}

//------------------------------------------------------------------
/**
 * @brief	指定番号のボックスからindex番目の個性乱数を返す
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
static int GetPersonalRndBoxIndex(AGBCARTRIDGE_WORK *wk, int box, int index)
{
  // AGBの構造体専用関数を用意しています
  // DPの構造体と混ざらないよう、かなり注意してくださいませ
  return AgbPokePasoParaGet(&(wk->boxdata->PPPBox[box][index]), ID_AGB_personal_rnd, NULL);
}

//------------------------------------------------------------------
/**
 * @brief	指定番号のボックスからindex番目のゲットバージョンを返す
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
static int GetCassetteVersionBoxIndex(AGBCARTRIDGE_WORK *wk, int box, int index)
{
  // AGBの構造体専用関数を用意しています
  // DPの構造体と混ざらないよう、かなり注意してくださいませ
  return AgbPokePasoParaGet(&(wk->boxdata->PPPBox[box][index]), ID_AGB_get_cassette, NULL);
}
//Add by soga　ここまで

//------------------------------------------------------------------
/**
 * @brief	RECT_HIT_TBLを登録
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
static void SetRectHitTable(RECT_HIT_TBL *rect, int x, int y, int sizx, int sizy)
{
  rect->rect.top    = y - sizy / 2;
  rect->rect.left   = x - sizx / 2;
  rect->rect.bottom = y + sizy / 2;
  rect->rect.right  = x + sizx / 2;
}

//------------------------------------------------------------------
/// @brief	ヒープサイズを固定にした版のArcUtrl_CahrDataGet
//------------------------------------------------------------------
static void *ArcUtil_CharDataGet2(u32 fileIdx, u32 dataIdx, NNSG2dCharacterData** charData, u32 heapID)
{
  void* arcData;

  arcData = sys_AllocMemoryLo(heapID, 4096);	/* ヒープサイズ固定 */
  if(arcData != NULL){
    ArchiveDataLoad(arcData, fileIdx, dataIdx);
    if( NNS_G2dGetUnpackedBGCharacterData( arcData, charData ) == FALSE){
      // 失敗したらNULL
      sys_FreeMemoryEz( arcData );
      return NULL;
    }
  }
  return arcData;
}
static void ArcUtil_CharDataGet3(u32 dataIdx, NNSG2dCharacterData** charData, void *arcData, ARCHANDLE* handle)
{
  ArchiveDataLoadByHandle(handle, dataIdx, arcData);
  NNS_G2dGetUnpackedBGCharacterData( arcData, charData );
}

//------------------------------------------------------------------
/**
 * @brief	ポケモンのフォルムナンバーを取得
 * @param	pokeno			取得するポケモンナンバー
 * @param	personal_rnd	取得するために必要な個性乱数
 * @param	get_cassette	取得するために必要なゲットカセットバージョン
 *
 * @return	取得したフォルムナンバー
 */
//------------------------------------------------------------------
static	u8	GetPokeFormNo(int pokeno,u32 personal_rnd,int get_cassette)
{
	u8	form_no;

	form_no=0;

#if 0//def DEBUG_ONLY_FOR_mituhara
	OS_TPrintf("MONSNO_DEOKISISU: %d - %d\n", MONSNO_DEOKISISU, pokeno);
	OS_TPrintf("get_cassette\n", get_cassette);
#endif

	switch(pokeno){
	//アンノーンのフォルムを取得
	case MONSNO_ANNOON:
		form_no=(((personal_rnd&0x03000000)>>18)|
				 ((personal_rnd&0x00030000)>>12)|
				 ((personal_rnd&0x00000300)>> 6)|
				  (personal_rnd&0x00000003))%28;
		break;
	case MONSNO_DEOKISISU:
		switch(get_cassette){
		default:
		case VERSION_RUBY:
		case VERSION_SAPPHIRE:
			//ルビー・サファイア・未知のバージョンはノーマル
			form_no=FORMNO_DEOKISISU_NORMAL;
			break;
		case VERSION_RED:
			//ファイアレッドはアタック
			form_no=FORMNO_DEOKISISU_ATTACK;
			break;
		case VERSION_GREEN:
			//リーフグリーンはディフェンス
			form_no=FORMNO_DEOKISISU_DEFENCE;
			break;
		case VERSION_EMERALD:
			//エメラルドはスピード
			form_no=FORMNO_DEOKISISU_SPEED;
			break;
		}
		break;
	}

	return form_no;
}

//------------------------------------------------------------------
/**
 * @brief	ポケモンのアイコンをＶＲＡＭへ登録
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
static void TransPokeIconCharaPal( int pokeno, int tamago_flag, u32 personal_rnd, int get_cassette, int no, CLACT_WORK_PTR icon)
{
  u8 *buf;
  u8 form_no;
  NNSG2dCharacterData *chara;

  // AGBポケモン→DPポケモンへ変換
  pokeno = ChangeAGBPoke2DPPoke(pokeno);

  // ポケモンのフォルムナンバーを取得(これはDSのmonsnoで判定)
  form_no = GetPokeFormNo(pokeno,personal_rnd,get_cassette);

  buf = ArcUtil_CharDataGet2( ARC_POKEICON, 
			      PokeIconCgxArcIndexGetByMonsNumber( pokeno, tamago_flag, form_no ), &chara, HEAPID_AGBCARTRIDGE);
  DC_FlushRange(chara->pRawData, POKEICON_TRANS_SIZE);

  // キャラクター転送
  GX_LoadOBJ(chara->pRawData, (POKEICON_VRAM_OFFSET+no*POKEICON_TRANS_CHARA)*0x20, POKEICON_TRANS_SIZE);
  // パレット設定
  CLACT_PaletteNoChg( icon,  PokeIconPalNumGet( pokeno, form_no, tamago_flag )+POKEICON_PAL_OFFSET );

  sys_FreeMemoryEz(buf);
}

static void TransPokeIconCharaPal2(int pokeno, int tamago_flag, int form_no,
				   int no, CLACT_WORK_PTR icon, void *buf, ARCHANDLE* handle)
{
  u32 dataidx;
  NNSG2dCharacterData *chara;
  POKEBUF *pbuf = _PokeBufPtr + no;

  if(icon){
#if 0
    // AGBポケモン→DPポケモンへ変換
    pokeno = ChangeAGBPoke2DPPoke(pokeno);
#else

    if(CheckInJusticePokemon(pokeno) == FALSE)
      // AGBポケモン→DPポケモンへ変換
      pokeno = ChangeAGBPoke2DPPoke(pokeno);
    else
      // 不正ポケモン
      pokeno = 0;
#endif
    // ポケモンのデータインデックス番号を取得
    dataidx = PokeIconCgxArcIndexGetByMonsNumber( pokeno, tamago_flag, form_no );
    // ポケモンキャラクタをバッファに転送
    ArcUtil_CharDataGet3(dataidx, &chara, buf, handle);
    MI_CpuCopyFast(chara->pRawData, pbuf->chbuf, POKEICON_TRANS_SIZE);
    pbuf->vadrs = (POKEICON_VRAM_OFFSET+no*POKEICON_TRANS_CHARA)*0x20;
    pbuf->icon = icon;
    pbuf->palno = PokeIconPalNumGet( pokeno, form_no, tamago_flag )+POKEICON_PAL_OFFSET;
  } else {
    pbuf->icon = NULL;
  }
}

static void TransPokeIconFinish(void)
{
  int i;
  POKEBUF *pbuf = _PokeBufPtr;
  for(i = 0; i < POKEMON_ICON_MAX; i++, pbuf++){
    if(pbuf->icon){
      // キャラクター転送
      DC_FlushRange(pbuf->chbuf, POKEICON_TRANS_SIZE);
      GX_LoadOBJ(pbuf->chbuf, pbuf->vadrs, POKEICON_TRANS_SIZE);
      // パレット設定
      CLACT_PaletteNoChg(pbuf->icon, pbuf->palno);
    }
  }
}


     
//------------------------------------------------------------------
/**
 * @brief	指定ボックスのポケモンを画面に表示
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
static void RedrawPokemonBox(AGBCARTRIDGE_WORK *wk)
{
  int i, monsno, tamago_flag, get_cassette, form_no;
  u32 personal_rnd;
  void *buf;
  ARCHANDLE* handle;

  handle = ArchiveDataHandleOpen( ARC_POKEICON, HEAPID_AGBCARTRIDGE);
  buf = sys_AllocMemoryLo(HEAPID_AGBCARTRIDGE, 4096);

  // ポケモンアイコンの表示
  for(i = 0; i < POKEMON_ICON_MAX; i++){
    if(AgbPokePasoParaGet(&(wk->boxdata->PPPBox[wk->CurrentBox][i]), ID_AGB_poke_exist_flag, NULL)){
      monsno = GetPokeBoxIndex(wk, wk->CurrentBox, i);
      //add by soga　ここから
      tamago_flag = GetEggFlagBoxIndex(wk, wk->CurrentBox, i);
      personal_rnd = GetPersonalRndBoxIndex(wk, wk->CurrentBox, i);
#if 0
      get_cassette = GetCassetteVersionBoxIndex(wk, wk->CurrentBox, i);
#else
      get_cassette = sys.AgbCasetteVersion;
#endif
      //add by soga　ここまで

      // ポケモンのフォルムナンバーを取得(これはDSのmonsnoで判定)
      form_no = GetPokeFormNo(ChangeAGBPoke2DPPoke(monsno), personal_rnd, get_cassette);
      TransPokeIconCharaPal2(monsno, tamago_flag, form_no, i, wk->icon[i].clact, buf, handle);
      CLACT_SetDrawFlag( wk->icon[i].clact, 1 );
      // アイテムアイコンの登録
      if(AgbPokePasoParaGet(&(wk->boxdata->PPPBox[wk->CurrentBox][i]), ID_AGB_item, NULL))
	CLACT_SetDrawFlag( wk->icon[i].item, 1 );
      else
	CLACT_SetDrawFlag( wk->icon[i].item, 0 );
    } else {
      TransPokeIconCharaPal2(monsno, tamago_flag, form_no, i, NULL, buf, handle);
      CLACT_SetDrawFlag( wk->icon[i].clact, 0 );
      CLACT_SetDrawFlag( wk->icon[i].item, 0 );
    }
  }
  sys_FreeMemoryEz(buf);
  ArchiveDataHandleClose( handle );

  
  // ポケモンアイコンの転送関数を定義
  wk->DrawFunc = TransPokeIconFinish;
  
  // ボックスのタイトル表示
  DrawBoxTitle(wk, wk->CurrentBox);
  // 選択アイコンを反映
  CheckSelectPokemonIcon(wk);
}


//------------------------------------------------------------------
/**
 * @brief	画面にポケモンを３０個並べる
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
static void SetPokemonIcon(AGBCARTRIDGE_WORK *wk)
{
  int index, x, y;
  CLACT_ADD add;

  AgbPokemon_MakeCLACT(&add, wk, &wk->clActHeaderMain, NNS_G2D_VRAM_TYPE_2DMAIN );

  index = 0;
  for(y = 0; y < 5; y++){
    for(x = 0; x < 6; x++){

      SetRectHitTable(&wk->iconrect[index],
		      x * POKEMON_WIDTH  + POKEMON_BASEX,
		      y * POKEMON_HEIGHT + POKEMON_BASEY,
		      28, 28);
      add.mat.x = FX32_ONE * (x * POKEMON_WIDTH  + POKEMON_BASEX);
      add.mat.y = FX32_ONE * (y * POKEMON_HEIGHT + POKEMON_BASEY);
      // ポケモンのアイコン登録
      if(wk->icon[index].clact == NULL)
	wk->icon[index].clact = CLACT_Add(&add);
      CLACT_SetAnmFlag(wk->icon[index].clact, 1);
      CLACT_AnmChg( wk->icon[index].clact, 10+index );
      CLACT_BGPriorityChg( wk->icon[index].clact, 1 );
      CLACT_SetDrawFlag( wk->icon[index].clact, 1 );
      CLACT_DrawPriorityChg( wk->icon[index].clact, 100+index);
      // アイテムのアイコン登録
      add.mat.x += FX32_ONE * 6;
      add.mat.y += FX32_ONE * 12;
      if(wk->icon[index].item == NULL)
	wk->icon[index].item = CLACT_Add(&add);
      CLACT_SetAnmFlag(wk->icon[index].item, 1);
      CLACT_AnmChg( wk->icon[index].item, 40);
      CLACT_BGPriorityChg( wk->icon[index].item, 1 );
      CLACT_SetDrawFlag( wk->icon[index].item, 0 );
      CLACT_DrawPriorityChg( wk->icon[index].item, 0+index);

      index++;
      if(index == POKEMON_ICON_MAX)	return;
    }
  }
}


//------------------------------------------------------------------
/**
 * @brief	ポケモン以外のアイコンを登録
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
static CLACT_WORK_PTR SetOamIcon(AGBCARTRIDGE_WORK *wk, int x, int y, int anim, int flag)
{
  CLACT_ADD add;
  CLACT_WORK_PTR p;
  
  AgbPokemon_MakeCLACT(&add, wk, &wk->clActHeaderMain, NNS_G2D_VRAM_TYPE_2DMAIN );
  add.mat.x = FX32_ONE * x;
  add.mat.y = FX32_ONE * y;
  add.pri   = 10;
  p = CLACT_Add(&add);
  CLACT_SetAnmFlag(p, 1);
  CLACT_AnmChg(p, anim);
  CLACT_BGPriorityChg(p, 1);
  CLACT_SetDrawFlag(p, flag);
  return p;
}
static void SetMiscIcon(AGBCARTRIDGE_WORK *wk)
{
  int i;

  SetRectHitTable(&wk->iconrect[ICON_CANCEL], 228, 176, 50, 32);
  wk->cancel[0] = SetOamIcon(wk, 228, 176, 6, 1);	// やめる

  SetRectHitTable(&wk->iconrect[ICON_ARROWR], 176, 176, 32, 32);
  wk->arrowr[0] = SetOamIcon(wk, 176, 176, 3, 1);	// 右→

  SetRectHitTable(&wk->iconrect[ICON_ARROWL],  24, 176, 32, 32);
  wk->arrowl[0] = SetOamIcon(wk,  24, 176, 0, 1);	// 左←

  wk->iconrect[ICON_TERMINATE].rect.top = RECT_HIT_END;

  // 決定アイコンの登録
  for(i = 0; i < POKEMON_SELECT_MAX; i++){
    wk->mark[i].icon = SetOamIcon(wk, 36*i, 64, 9, 0);
    wk->mark[i].pokeno = POKEMON_NOSELECT;
    wk->mark[i].boxno = BOX_NUM;
  }
  wk->selected = 0;
}


//------------------------------------------------------------------
/**
 * @brief	ポケモンのタマゴチェック
 * @param	NONE
 * @return	TRUE: たまごでした　FALSE: たまごじゃない
 */
//------------------------------------------------------------------
static BOOL CheckPokemonEgg(AGBCARTRIDGE_WORK *wk, int num)
{
  int monsno;
  PokemonPasoParam *ppp = &wk->boxdata->PPPBox[wk->CurrentBox][num];

  if(AgbPokePasoParaGet(ppp, ID_AGB_monsno_egg, NULL) == MONSNO_AGB_TAMAGO)
    return TRUE;
  return FALSE;
}

//------------------------------------------------------------------
/**
 * @brief	ひでんわざを持っているかチェック
 * @param	NONE
 * @return	TRUE: 持ってた　FALSE: 持ってない
 */
//------------------------------------------------------------------
static BOOL CheckPokemonHidenWaza(AGBCARTRIDGE_WORK *wk, int num)
{
  int w, i, waza;

  PokemonPasoParam *ppp = &wk->boxdata->PPPBox[wk->CurrentBox][num];

  for(w = 0; w < 4; w++){
    waza = AgbPokePasoParaGet(ppp, ID_AGB_waza1 + w, NULL);
    for(i = 0; i < sizeof(WazaHidenTable) / sizeof(int); i++){
      if(WazaHidenTable[i] == waza)
	return TRUE;
    }
  }
  return FALSE;
}


//------------------------------------------------------------------
/**
 * @brief	持っていけないアイテムを持っていないかチェック
 * @param	NONE
 * @return	TRUE: 持ってた　FALSE: 持ってない
 */
//------------------------------------------------------------------
#include "agbitemexist.h"
static BOOL CheckPokemonExistItem(AGBCARTRIDGE_WORK *wk, int num)
{
  PokemonPasoParam *ppp = &wk->boxdata->PPPBox[wk->CurrentBox][num];
  int item = AgbPokePasoParaGet(ppp, ID_AGB_item, NULL);
  int i;

  for(i = 0; AgbItemExistCheck[i]; i++){
    if(item == AgbItemExistCheck[i])
      return TRUE;
  }
  return FALSE;
}


//------------------------------------------------------------------
/**
 * @brief	不正なポケモンチェック
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
static BOOL CheckPokemonFusei(AGBCARTRIDGE_WORK *wk, int num)
{
  PokemonPasoParam *ppp = &wk->boxdata->PPPBox[wk->CurrentBox][num];
  int monsno = AgbPokePasoParaGet(ppp, ID_AGB_monsno, NULL);
  return CheckInJusticePokemon(monsno);
}


//------------------------------------------------------------------
/**
 * @brief	指定したアイコンの横に決定アイコンを制御
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
#define SELECT_POKEMON_FULL	0		// すでにいっぱい
#define SELECT_POKEMON_SELECT	1		// 選択した
#define SELECT_POKEMON_CANCEL	2		// 解除した
#define SELECT_POKEMON_NOMONS	3		// そもそもそこにいない
#define SELECT_POKEMON_EGG	4		// 実はたまごだった
#define SELECT_POKEMON_WAZA	5		// ひでんわざを持っていた
#define SELECT_POKEMON_ITEM	6		// 持っていけないアイテムを持ってた
#define SELECT_POKEMON_FUSEI	7		// 不正なポケモン番号だった

static int SelectPokemon(AGBCARTRIDGE_WORK *wk, int num)
{
  int i, sel;

  // 空白のチェック
  if(wk->icon[num].clact && CLACT_GetDrawFlag(wk->icon[num].clact) == FALSE)
    return SELECT_POKEMON_NOMONS;
  
  // すでに選択済みなのかを調べる
  for(sel = -1, i = 0; sel == -1 && i < POKEMON_SELECT_MAX; i++){
    if(wk->mark[i].boxno == wk->CurrentBox &&
       wk->mark[i].pokeno == num)
      sel = i;
  }
#if 0	// the 実験君
  return SELECT_POKEMON_ITEM;
#endif
  
  // たまごチェック
  if(CheckPokemonEgg(wk, num) == TRUE)
    return SELECT_POKEMON_EGG;

  // ひでんわざを持っているかチェック
  if(CheckPokemonHidenWaza(wk, num) == TRUE)
    return SELECT_POKEMON_WAZA;

  // 持っていけないアイテムを持っているかチェック
  if(CheckPokemonExistItem(wk, num) == TRUE)
    return SELECT_POKEMON_ITEM;

  // 不正なポケモンかチェック
  if(CheckPokemonFusei(wk, num) == TRUE)
    return SELECT_POKEMON_FUSEI;
  
  if(sel == -1){
    // 選択されていなかった場合
    const VecFx32 *vec;
    VecFx32 nvec;

    // すでに６匹が選択されていたら何もしない
    if(wk->selected == POKEMON_SELECT_MAX)
      return SELECT_POKEMON_FULL;

    for(i = 0; i < POKEMON_SELECT_MAX; i++)
      if(wk->mark[i].pokeno == POKEMON_NOSELECT){
	// 元のポケモンから座標情報を得て(ポインタを得るだけ)
	vec = CLACT_GetMatrix(wk->icon[num].clact);
	// その情報をアイコンへコピーする
	CLACT_SetMatrix(wk->mark[i].icon, vec);
	// そのコピーした情報のポインタを得て…
	vec = CLACT_GetMatrix(wk->mark[i].icon);
	// 座標をポケモンの左上にオフセット移動
	nvec = *vec;
	nvec.x -= FX32_ONE * 8;
	nvec.y -= FX32_ONE * 4;
	CLACT_SetMatrix(wk->mark[i].icon, &nvec);
	// アイコンの表示フラグをON
  	CLACT_SetDrawFlag(wk->mark[i].icon, 1);
	wk->mark[i].pokeno = num;
	wk->mark[i].boxno = wk->CurrentBox;
	wk->selected++;
	return SELECT_POKEMON_SELECT;
      }

  } else {
    // 選択されていた場合
    CLACT_SetDrawFlag(wk->mark[sel].icon, 0);
    wk->mark[sel].pokeno = POKEMON_NOSELECT;
    wk->selected--;
    return SELECT_POKEMON_CANCEL;
  }
  return SELECT_POKEMON_FULL;
}


//------------------------------------------------------------------
/**
 * @brief	同じボックスならばアイコン表示
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
static void CheckSelectPokemonIcon(AGBCARTRIDGE_WORK *wk)
{
  int i;
  for(i = 0; i < POKEMON_SELECT_MAX; i++){
    if(wk->mark[i].pokeno != POKEMON_NOSELECT && wk->mark[i].boxno == wk->CurrentBox){
      CLACT_SetDrawFlag(wk->mark[i].icon, 1);
    } else {
      CLACT_SetDrawFlag(wk->mark[i].icon, 0);
    }
  }
}



//------------------------------------------------------------------
/**
 * @brief	ボックスタイトルの表示
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
static void DrawBoxTitle(AGBCARTRIDGE_WORK *wk, int boxnumber)
{
  REGWIN rwin;
  STRCODE title[BOXNAME_MAX+EOM_SIZE];

  memset(&rwin, 0, sizeof(REGWIN));
  rwin.win = &wk->TitleWin;
  rwin.sx = 6;
  rwin.sy = 21;
  rwin.width = 13;
  rwin.height = 2;
  rwin.msgid = -1;
  rwin.dx = 0;
  rwin.dy = 0;
  rwin.screen = GF_BGL_FRAME1_M;
  rwin.font = FONT_TALK;
  rwin.color = AGBPOKEMON_BLACK;
  rwin.base = AGBPOKEMON_TITLEBASE;
  AGBSTR_to_DSSTR(wk->boxdata->BoxName[boxnumber], title, BOXNAME_MAX+EOM_SIZE, agbpoke_getPokemonLanguage());
  rwin.msgp = title;
  CreateMsgWindow(wk, &rwin, MSG_FLAG_CENTER);
}


//------------------------------------------------------------------
/**
 * @brief	ポケモンのマーク情報を表示
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
static void DrawStatusPokeMark(AGBCARTRIDGE_WORK *wk, PokemonPasoParam *ppp)
{
  u16 *scrn = GF_BGL_ScreenAdrsGet(wk->bgl, GF_BGL_FRAME2_M);
  u8 mark;
  int i;

  if(ppp)	mark = AgbPokePasoParaGet(ppp, ID_AGB_mark, NULL);
  else		mark = 0;

  for(i = 0; i < 4; i++){
    if(mark & 1)	scrn[32*3 + 11 + i] = 0x0080 + i;
    else		scrn[32*3 + 11 + i] = 0x0060 + i;
    mark >>= 1;
  }
  GF_BGL_LoadScreenReq(wk->bgl, GF_BGL_FRAME2_M);
}


//------------------------------------------------------------------
/**
 * @brief	情報ウィンドウを表示
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
#define SetRWin(msg, x, y)	rwin.msgid = (msg), rwin.dx = (x), rwin.dy = (y);
static void DrawStatusWindow(AGBCARTRIDGE_WORK *wk, PokemonPasoParam *ppp)
{
  int monsno, level;
  int agb_item, dp_item;
  REGWIN rwin;
  MSGDATA_MANAGER* man;
  u8 agb_name[MONS_NAME_SIZE+AGB_EOM_SIZE];
  STRCODE ds_name[MONS_NAME_SIZE+AGB_EOM_SIZE];
  STRBUF *msg;

  memset(&rwin, 0, sizeof(REGWIN));
  rwin.win = &wk->BoxNameWin;
  rwin.sx = 0;
  rwin.sy = 0;
  rwin.width = 32;
  rwin.height = 4;
  rwin.screen = GF_BGL_FRAME1_M;
  rwin.font = FONT_TALK;
  rwin.base = AGBPOKEMON_STATUSBASE;
  rwin.color = AGBPOKEMON_WHITE;
  rwin.msgp = NULL;

  // 「もちもの」
  SetRWin(msg_pokepark__status_02, 18*8, 0);
  CreateMsgWindow(wk, &rwin, MSG_FLAG_NOREDRAW);
  // 「Lv.」
  SetRWin(msg_pokepark__status_01, 10*8, 8);
  CreateMsgWindow(wk, &rwin, MSG_FLAG_NOREDRAW|MSG_FLAG_NOCLEAR);
  // マーク
  DrawStatusPokeMark(wk, ppp);

  // PPPの指定がなければこれ以降は処理しない
  if(ppp == NULL){
    GF_BGL_BmpWinOn(rwin.win);
    return;
  }

  // ニックネーム(他言語のポケモンが入っている可能性がある)
  AgbPokePasoParaGet(ppp, ID_AGB_nickname, agb_name);
  AGBSTR_to_DSSTR(agb_name, ds_name, MONS_NAME_SIZE+AGB_EOM_SIZE, AgbPokePasoParaGet(ppp, ID_AGB_country_code, NULL));
  rwin.msgp = ds_name;
  SetRWin(-1, 1*8, 0);
  CreateMsgWindow(wk, &rwin, MSG_FLAG_NOREDRAW|MSG_FLAG_NOCLEAR);

  // ポケモン名
  msg = STRBUF_Create(64, HEAPID_AGBCARTRIDGE);
  man = MSGMAN_Create( MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_monsname_dat, HEAPID_AGBCARTRIDGE);
  // [[[ここでポケモンの性別等をチェックできる]]]
  monsno = ChangeAGBPoke2DPPoke(AgbPokePasoParaGet(ppp, ID_AGB_monsno, NULL));
  MSGMAN_GetString(man, monsno, msg);
  rwin.msg = msg;
  SetRWin(-1, 2*8, 2*8);
  CreateMsgWindow(wk, &rwin, MSG_FLAG_NOREDRAW|MSG_FLAG_NOCLEAR);
  MSGMAN_Delete(man);
  STRBUF_Delete(msg);

  // 持っているアイテム名
  agb_item = AgbPokePasoParaGet(ppp, ID_AGB_item, NULL);
  if(agb_item){
    dp_item = ITEM_AgbItemCnv(agb_item);
    msg = STRBUF_Create(64, HEAPID_AGBCARTRIDGE);
    GetItemName(msg, dp_item, HEAPID_AGBCARTRIDGE);
    rwin.msg = msg;
    SetRWin(-1, 19*8, 2*8);
    CreateMsgWindow(wk, &rwin, MSG_FLAG_NOREDRAW|MSG_FLAG_NOCLEAR);
    STRBUF_Delete(msg);
  }
  
  // レベル
  level = AgbPokePasoLevelCalc(ppp);
  msg = STRBUF_Create(10, HEAPID_AGBCARTRIDGE);
  STRBUF_SetNumber(msg, level,  3, NUMBER_DISPTYPE_SPACE, NUMBER_CODETYPE_DEFAULT);
  rwin.msg = msg;
  SetRWin(-1, 12*8+4, 1*8);
  CreateMsgWindow(wk, &rwin, MSG_FLAG_NOCLEAR);
  STRBUF_Delete(msg);

  // ポケモンボイスを鳴らす
  Snd_PMVoicePlay(monsno);
}

//------------------------------------------------------------------
/**
 * @brief	フェード処理
 *
 * @param	none
 * @return	none
 */
//------------------------------------------------------------------
static void RequestFade(AGBCARTRIDGE_WORK *wk, int type, int next_seq, int *seq)
{
  WIPE_SYS_Start(WIPE_PATTERN_WMS, type, type, WIPE_FADE_BLACK,WIPE_DEF_DIV,WIPE_DEF_SYNC,HEAPID_AGBCARTRIDGE);
  if(seq)
    SetSeq(AGBCARTRIDGE_SEQ_WAIT_FADE);
  wk->next_seq = next_seq;
}
static void RequestFadeW(AGBCARTRIDGE_WORK *wk, int type, int next_seq, int *seq)
{
  WIPE_SYS_Start(WIPE_PATTERN_WMS, type, type, WIPE_FADE_WHITE,WIPE_DEF_DIV,WIPE_DEF_SYNC,HEAPID_AGBCARTRIDGE);
  if(seq)
    SetSeq(AGBCARTRIDGE_SEQ_WAIT_FADE);
  wk->next_seq = next_seq;
}


//--------------------------------------------------------------------------------------------
/**
 * @brief	BG初期化
 * @param	none
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void BgInit(GF_BGL_INI * ini)
{
  {	/* BG SYSTEM */
    GF_BGL_SYS_HEADER BGsys_data = {
      GX_DISPMODE_GRAPHICS, GX_BGMODE_0, GX_BGMODE_0, GX_BG0_AS_2D,
    };
    GF_BGL_InitBG( &BGsys_data );
  }

  {	/* MAIN DISP BG0 */
    GF_BGL_BGCNT_HEADER MBg0_Data = {
      0, 0, 0x800, 0,
      GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
      GX_BG_SCRBASE_0xe000, GX_BG_CHARBASE_0x00000,
      GX_BG_EXTPLTT_01, 0, 0, 0, FALSE
    };
    GF_BGL_BGControlSet( ini, GF_BGL_FRAME0_M, &MBg0_Data, GF_BGL_MODE_TEXT );
    GF_BGL_ScrClear( ini, GF_BGL_FRAME0_M );
  }

  {	/* MAIN DISP BG1 */
    GF_BGL_BGCNT_HEADER MBg1_Data = {
      0, 0, 0x800, 0,
      GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
      GX_BG_SCRBASE_0xe800, GX_BG_CHARBASE_0x08000,
      GX_BG_EXTPLTT_01, 1, 0, 0, FALSE
    };
    GF_BGL_BGControlSet( ini, GF_BGL_FRAME1_M, &MBg1_Data, GF_BGL_MODE_TEXT );
    GF_BGL_ScrClear( ini, GF_BGL_FRAME1_M );
  }

  {	/* MAIN DISP BG2 */
    GF_BGL_BGCNT_HEADER MBg2_Data = {
      0, 0, 0x800, 0,
      GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
      GX_BG_SCRBASE_0xf000, GX_BG_CHARBASE_0x08000,
      GX_BG_EXTPLTT_23, 2, 0, 0, FALSE
    };
    GF_BGL_BGControlSet( ini, GF_BGL_FRAME2_M, &MBg2_Data, GF_BGL_MODE_TEXT );
    GF_BGL_ScrClear( ini, GF_BGL_FRAME2_M );
  }

  {	/* MAIN DISP BG3 */
    GF_BGL_BGCNT_HEADER MBg3_Data = {
      0, 0, 0x800, 0,
      GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
      GX_BG_SCRBASE_0xf800, GX_BG_CHARBASE_0x08000,
      GX_BG_EXTPLTT_23, 3, 0, 0, FALSE
    };
    GF_BGL_BGControlSet( ini, GF_BGL_FRAME3_M, &MBg3_Data, GF_BGL_MODE_TEXT );
    GF_BGL_ScrClear( ini, GF_BGL_FRAME3_M );
  }
}


//------------------------------------------------------------------
/**
 * @brief	スクリーン作成
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
static void CreateAgbCartridgeScreen(AGBCARTRIDGE_WORK *wk)
{
  GF_BGL_DISPVRAM tbl = {
    GX_VRAM_BG_128_A,				// メイン2DエンジンのBG
    GX_VRAM_BGEXTPLTT_NONE,			// メイン2DエンジンのBG拡張パレット

    GX_VRAM_SUB_BG_128_C,			// サブ2DエンジンのBG
    GX_VRAM_SUB_BGEXTPLTT_NONE,		// サブ2DエンジンのBG拡張パレット

    GX_VRAM_OBJ_64_E,				// メイン2DエンジンのOBJ
    GX_VRAM_OBJEXTPLTT_NONE,		// メイン2DエンジンのOBJ拡張パレット

    GX_VRAM_SUB_OBJ_16_I,			// サブ2DエンジンのOBJ
    GX_VRAM_SUB_OBJEXTPLTT_NONE,	// サブ2DエンジンのOBJ拡張パレット

    GX_VRAM_TEX_0_B,				// テクスチャイメージスロット
    GX_VRAM_TEXPLTT_01_FG			// テクスチャパレットスロット
  };
  GF_Disp_SetBank( &tbl );

  BgInit(wk->bgl);

  // 上下画面をひっくり返す
  sys.disp3DSW = DISP_3D_TO_SUB;
  GF_Disp_DispSelect();
  
  MSG_PrintInit();

  /* メッセージのフォントカラーを設定 */
  SystemFontPaletteLoad( PALTYPE_MAIN_BG, FONT_PALNO_NORMAL * 32, HEAPID_AGBCARTRIDGE);

  // メイン画面ＢＧパレット転送
  ArcUtil_PalSet(ARC_MYSTERY_GRA, NARC_mystery_gba_box_bg_nclr, PALTYPE_MAIN_BG, 0, 32*6, HEAPID_AGBCARTRIDGE);
  // メイン画面BG1キャラ転送
  ArcUtil_BgCharSet(ARC_MYSTERY_GRA, NARC_mystery_gba_box_main_lz_cngr, wk->bgl,
		    GF_BGL_FRAME2_M, 0, 10*16*0x20, 1, HEAPID_AGBCARTRIDGE);

  // ボタン用フォントの読み込み
  FontProc_LoadFont(FONT_BUTTON, HEAPID_AGBCARTRIDGE);
}
static void CreateAgbCartridgeScreen2(AGBCARTRIDGE_WORK *wk)
{
  // メイン画面スクリーン１
  ArcUtil_ScrnSet(ARC_MYSTERY_GRA, NARC_mystery_gba_box_main1_lz_cscr, wk->bgl,
		  GF_BGL_FRAME2_M, 0, 32*24*2, 1, HEAPID_AGBCARTRIDGE);
  // 刺さっているＡＧＢカセットによってＢＧのパレットを変える
  GF_BGL_ScrPalChange(wk->bgl, GF_BGL_FRAME2_M, 0, 0, 32, 24, BgPalTable[wk->cartridge_type]);
  GF_BGL_LoadScreenReq(wk->bgl, GF_BGL_FRAME2_M);
}


//------------------------------------------------------------------
/**
 * @brief	上ウィンドウの初期化
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
static void InitUpMessageWindow(AGBCARTRIDGE_WORK *wk)
{
  // ウィンドウ枠とパレットをＶＲＡＭへロード
  SystemFontPaletteLoad( PALTYPE_MAIN_BG, AGBPOKEMON_FRAMECOL * 32, HEAPID_AGBCARTRIDGE);
  MenuWinGraphicSet(wk->bgl, GF_BGL_FRAME0_M, AGBPOKEMON_FRAMECHR, AGBPOKEMON_FRAMECOL, 0, HEAPID_AGBCARTRIDGE);
  TalkWinGraphicSet(wk->bgl, GF_BGL_FRAME0_M, AGBPOKEMON_TFRAMECHR, AGBPOKEMON_TFRAMECOL, wk->win_type, HEAPID_AGBCARTRIDGE);

  memset(&wk->cwin, 0, sizeof(REGWIN));
  wk->cwin.win = &wk->CheckWin;
  wk->cwin.sx = 2;
  wk->cwin.sy = 1;
  wk->cwin.width = 27;
  wk->cwin.height = 4;
  wk->cwin.screen = GF_BGL_FRAME0_M;
  wk->cwin.font = FONT_TALK;
  wk->cwin.base = AGBPOKEMON_CHRBASE + 1;
  wk->cwin.color = AGBPOKEMON_BLACKBLACK;
  wk->cwin.clrcolor = AGBPOKEMON_WHITEBLACK;
  wk->cwin.msgp = NULL;
  wk->cwin.msg = NULL;
}

//------------------------------------------------------------------
/**
 * @brief	確認画面のスクリーンを作成
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
static void CreateCheckScreen(AGBCARTRIDGE_WORK *wk)
{
  int i, monsno, tamago_flag, get_cassette;
  u32 personal_rnd;
  CLACT_ADD add;

  // 画面中のオブジェクトは抹消(ただし登録は残しておく)
  for(i = 0; i < POKEMON_ICON_MAX; i++){
    CLACT_SetDrawFlag( wk->icon[i].clact, 0 );
    CLACT_SetDrawFlag( wk->icon[i].item, 0 );
  }
  for(i = 0; i < POKEMON_SELECT_MAX; i++)
    CLACT_SetDrawFlag( wk->mark[i].icon, 0 );
  CLACT_SetDrawFlag(wk->cancel[0], 0);
  CLACT_SetDrawFlag(wk->arrowl[0], 0);
  CLACT_SetDrawFlag(wk->arrowr[0], 0);
  
  // 新たに６体分のアクターを登録
  AgbPokemon_MakeCLACT(&add, wk, &wk->clActHeaderMain, NNS_G2D_VRAM_TYPE_2DMAIN );
  for(i = 0; i < POKEMON_SELECT_MAX; i++){
    add.mat.x = FX32_ONE * (i * POKEMON_WIDTH  + POKEMON_BASEX);
    add.mat.y = FX32_ONE * 142;
    wk->check_poke[i] = CLACT_Add(&add);
    
    CLACT_SetAnmFlag(wk->check_poke[i], 1);
    CLACT_AnmChg( wk->check_poke[i], 10+i );
    CLACT_BGPriorityChg( wk->check_poke[i], 1 );
    CLACT_SetDrawFlag( wk->check_poke[i], 1 );
    monsno = GetPokeBoxIndex(wk, wk->mark[i].boxno, wk->mark[i].pokeno);
	//add by soga　ここから
    tamago_flag = GetEggFlagBoxIndex(wk, wk->mark[i].boxno, wk->mark[i].pokeno);
    personal_rnd = GetPersonalRndBoxIndex(wk, wk->mark[i].boxno, wk->mark[i].pokeno);
#if 0
    get_cassette = GetCassetteVersionBoxIndex(wk, wk->mark[i].boxno, wk->mark[i].pokeno);
#else
    get_cassette = sys.AgbCasetteVersion;
#endif
	//add by soga　ここまで
    TransPokeIconCharaPal(monsno, tamago_flag, personal_rnd, get_cassette, i, wk->check_poke[i]);
  }
  
  // スクリーンデータ転送(キャラクタは同一のものを使う)
  ArcUtil_ScrnSet(ARC_MYSTERY_GRA, NARC_mystery_gba_box_main2_lz_cscr, wk->bgl,
		  GF_BGL_FRAME2_M, 0, 32*24*2, 1, HEAPID_AGBCARTRIDGE);
  // 刺さっているＡＧＢカセットによってＢＧのパレットを変える
  GF_BGL_ScrPalChange(wk->bgl, GF_BGL_FRAME2_M, 0, 0, 32, 24, BgPalTable[wk->cartridge_type]);
  GF_BGL_LoadScreenReq(wk->bgl, GF_BGL_FRAME2_M);
  // ポケモンステータス表示ＢＧは消してしまう
  GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG1, VISIBLE_OFF );

  // ウィンドウ枠とパレットをＶＲＡＭへロード
  SystemFontPaletteLoad( PALTYPE_MAIN_BG, AGBPOKEMON_FRAMECOL * 32, HEAPID_AGBCARTRIDGE);
  MenuWinGraphicSet(wk->bgl, GF_BGL_FRAME0_M, AGBPOKEMON_FRAMECHR, AGBPOKEMON_FRAMECOL, 0, HEAPID_AGBCARTRIDGE);
  TalkWinGraphicSet(wk->bgl, GF_BGL_FRAME0_M, AGBPOKEMON_TFRAMECHR, AGBPOKEMON_TFRAMECOL, wk->win_type, HEAPID_AGBCARTRIDGE);
  
  // メッセージウィンドウを作成
  InitUpMessageWindow(wk);
  wk->cwin.msgid = msg_pokepark_12;	// えらんだ　６ひきの　ポケモンを\nつれて　いきます
  CreateMsgWindow(wk, &wk->cwin, MSG_FLAG_FRAME|MSG_FLAG_TALKWIN);
}


//------------------------------------------------------------------
/**
 * @brief	ウィンドウを消す
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
static void DeleteWindow(GF_BGL_BMPWIN *win)
{
  if(win->ini){
    BmpTalkWinClear(win, WINDOW_TRANS_ON);
    GF_BGL_BmpWinOff(win);
    GF_BGL_BmpWinDel(win);
  }
}


//------------------------------------------------------------------
/**
 * @brief	選択画面を復活させる
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
static void ReviveSelectScreen(AGBCARTRIDGE_WORK *wk)
{
  int i;
  // 選択画面に戻る処理


  // 表示していたアクターを抹消
  for(i = 0; i < POKEMON_SELECT_MAX; i++)
    CLACT_Delete(wk->check_poke[i]);
    
  // ポケモンステータス表示ＢＧを復活
  GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG1, VISIBLE_ON );

  /* メッセージウィンドウを消す */
  DeleteWindow(&wk->CheckWin);
  // その他アイコンを復活させる
  CLACT_SetDrawFlag(wk->cancel[0], 1);
  CLACT_SetDrawFlag(wk->arrowl[0], 1);
  CLACT_SetDrawFlag(wk->arrowr[0], 1);
  for(i = 0; i < POKEMON_SELECT_MAX; i++){
    wk->mark[i].pokeno = POKEMON_NOSELECT;
    wk->mark[i].boxno = BOX_NUM;
  }
  wk->selected = 0;
}


//------------------------------------------------------------------
/**
 * @brief	すべてのリソースを開放して処理を終了させる
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
static void FinishScreen(AGBCARTRIDGE_WORK *wk)
{
  int i;

  sys_VBlankFuncChange( NULL, NULL );

  // ポケモンアイコン
  for(i = 0; i < POKEMON_ICON_MAX; i++){
    if(wk->icon[i].clact)
      CLACT_Delete(wk->icon[i].clact);
    if(wk->icon[i].item)
      CLACT_Delete(wk->icon[i].item);
  }
  // 選択マーク
  for(i = 0; i < POKEMON_SELECT_MAX; i++){
    if(wk->mark[i].icon)
      CLACT_Delete(wk->mark[i].icon);
  }
  // やじるしとか「やめる」とか
  if(wk->cancel[0])	CLACT_Delete(wk->cancel[0]);
  if(wk->arrowl[0])	CLACT_Delete(wk->arrowl[0]);
  if(wk->arrowr[0])	CLACT_Delete(wk->arrowr[0]);
  // ウィンドウを削除
  DeleteWindow(&wk->TitleWin);
  DeleteWindow(&wk->BoxNameWin);
  DeleteWindow(&wk->CheckWin);
  
  //フォント削除
  FontProc_UnloadFont(FONT_BUTTON);

  // キャラ転送マネージャー破棄
  CLACT_U_CharManagerDelete(wk->resObjTbl[CLACT_U_CHAR_RES]);
  // パレット転送マネージャー破棄
  CLACT_U_PlttManagerDelete(wk->resObjTbl[CLACT_U_PLTT_RES]);
  // キャラ・パレット・セル・セルアニメのリソースマネージャー破棄
  for(i=0;i<CLACT_U_RES_MAX;i++)
    CLACT_U_ResManagerDelete(wk->resMan[i]);

  // セルアクターセット破棄
  CLACT_DestSet(wk->clactSet);
  wk->clactSet = NULL;
  //OAMレンダラー破棄
  REND_OAM_Delete();
  // リソース解放
  DeleteCharManager();
  DeletePlttManager();
  // タッチシステムの開放
  TOUCH_SW_FreeWork(wk->TouchSubWindowSys);
  
  // 上下画面を元に戻しておく
  sys.disp3DSW = DISP_3D_TO_MAIN;
  GF_Disp_DispSelect();

  GF_BGL_BGControlExit(wk->bgl, GF_BGL_FRAME0_M);
  GF_BGL_BGControlExit(wk->bgl, GF_BGL_FRAME1_M);
  GF_BGL_BGControlExit(wk->bgl, GF_BGL_FRAME2_M);
  GF_BGL_BGControlExit(wk->bgl, GF_BGL_FRAME3_M);
}


//------------------------------------------------------------------
/**
 * @brief	はい／いいえアイコンを登録
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
static void AgbCartridge_ReqYesNoIcon(AGBCARTRIDGE_WORK *wk)
{
  // はい／いいえ選択
  TOUCH_SW_PARAM param;
  param.p_bgl		= wk->bgl;
  param.bg_frame	= GF_BGL_FRAME0_M;
  param.char_offs	= 512;
  param.pltt_offs 	= 8;
  param.x		= 25;
  param.y		= 7;
  TOUCH_SW_Init(wk->TouchSubWindowSys, &param );
}


//------------------------------------------------------------------
/**
 * @brief	カートリッジのユーザー確認
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
static void AgbCartridge_CreateCheckUser(AGBCARTRIDGE_WORK *wk)
{
  REGWIN rwin;
  WORDSET *word;
  STRBUF *strbuf;
  STRCODE dsname[AGB_PERSON_NAME_SIZE+AGB_EOM_SIZE];

  AGBSTR_to_DSSTR(agbpoke_GetTrainerName(), dsname, AGB_PERSON_NAME_SIZE+AGB_EOM_SIZE, agbpoke_getPokemonLanguage());
  word = WORDSET_Create(HEAPID_AGBCARTRIDGE);
  strbuf = STRBUF_Create(AGB_PERSON_NAME_SIZE+AGB_EOM_SIZE, HEAPID_AGBCARTRIDGE);
  STRBUF_SetStringCode(strbuf, dsname);
  WORDSET_RegisterWord(word, 1, strbuf, PM_MALE, TRUE, PM_LANG);

  // [トレーナー名]の　[カセット名] から\nポケモンを　つれてきますか？
  InitUpMessageWindow(wk);
  wk->cwin.msgid = UsrCheckMsgTable[wk->cartridge_type];
  wk->cwin.word = word;
  CreateMsgWindow(wk, &wk->cwin, MSG_FLAG_FRAME|MSG_FLAG_TALKWIN);
  STRBUF_Delete(strbuf);
  WORDSET_Delete(word);
  AgbCartridge_ReqYesNoIcon(wk);
}

static void VBlankFunc( void * work )
{
  AGBCARTRIDGE_WORK *wk = (AGBCARTRIDGE_WORK *)work;

  if(wk->DrawFunc){
    wk->DrawFunc();
    wk->DrawFunc = NULL;
  }
  
  // セルアクターVram転送マネージャー実行
  DoVramTransferManager();
  // レンダラ共有OAMマネージャVram転送
  REND_OAMTrans();	
  GF_BGL_VBlankFunc(wk->bgl);
  OS_SetIrqCheckFlag( OS_IE_V_BLANK );
}


//------------------------------------------------------------------
/**
 * @brief	エラーチェックをしまくる関数
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
enum {
  AGBPOKEMON_ERROR_NONE,		// エラーなし
  AGBPOKEMON_ERROR_LOAD_FAILD,		// セーブデータのロードに失敗した
  AGBPOKEMON_ERROR_FEW_24HOUR,		// まだ２４時間立っていない
  AGBPOKEMON_ERROR_MACADDRESS,		// DS本体のMacAddressが変わってる
  AGBPOKEMON_ERROR_MOVE_TIME,		// DS本体の時計が動かされた
  AGBPOKEMON_ERROR_PCBOX_NOPOKE,	// ボックスに６匹存在しない
  AGBPOKEMON_ERROR_POKEPARK_FULL,	// ポケパークに存在している
  AGBPOKEMON_ERROR_IMAKARA_24HOUR,	// 今から２４時間連れてこれない
  AGBPOKEMON_ERROR_MAX
};

#define AGBPOKEMON_24HOUR		(60*60*24)	// 60秒×60分×24時間

static int AgbCartridge_CheckAgbError(AGBCARTRIDGE_WORK *wk)
{
  int time;
  u32 AgbTrainerID;
  POKEPARK_DATA *ppark;

#if 0
  return AGBPOKEMON_ERROR_MOVE_TIME;		// DS本体の時計が動かされた
#endif


#if 0//def DEBUG_ONLY_FOR_mituhara
  return AGBPOKEMON_ERROR_NONE;
#endif
  
  ppark = SaveData_GetPokeParkData(wk->sv);
  // 新規セーブならばいくつかのエラーチェックはすっ飛ばす
  if(POKEPARKDATA_isNewSave(ppark) == FALSE){

    // MACアドレスチェック
    if(POKEPARKDATA_CheckMacAddress(ppark) == FALSE)
      return AGBPOKEMON_ERROR_MACADDRESS;	// MACアドレス不一致

    // 時計不正変更チェック
    if(POKEPARKDATA_CheckRTCOffset(ppark) == FALSE)
      return AGBPOKEMON_ERROR_MOVE_TIME;	// 時計ずらした

    // AGBカセットのトレーナーIDを得る
    AgbTrainerID = agbpoke_GetTrainerID();
    time = POKEPARKDATA_CheckHistoryID(ppark, AgbTrainerID);
    // まだ１度も連れてきていなければ連れていける
    if(time == 0)	time = AGBPOKEMON_24HOUR * 2;
#ifdef DEBUG_ONLY_FOR_mituhara
    OS_TPrintf("前回連れてきてからの経過時間: %2d分 %2d秒\n", time / 60, time % 60);
    //    time = AGBPOKEMON_24HOUR * 2;
#endif
    if(time < AGBPOKEMON_24HOUR)
      return AGBPOKEMON_ERROR_FEW_24HOUR;	// まだ24時間経ってない

  }
  // ボックスのポケモン数チェック
  {
    PokemonPasoParam *ppp;
    int i, box, max = 0;
    for(box = 0; box < BOX_NUM; box++){
      for(i = 0; i < POKEMON_ICON_MAX; i++){
	ppp = &wk->boxdata->PPPBox[box][i];
	if(AgbPokePasoParaGet(ppp, ID_AGB_poke_exist_flag, NULL))
	  max++;
      }
    }
#ifdef DEBUG_ONLY_FOR_mituhara
    OS_TPrintf("PCBOXにいるポケモンの数: %d\n", max);
#endif    
    if(max < POKEPARK_MONS_MAX)	// include/savedata/pokepark_data.h
      return AGBPOKEMON_ERROR_PCBOX_NOPOKE; // ボックスに６匹いなかった
  }
  
  // ポケパーク用ボックスが空いているか調べる
  if(POKEPARKDATA_CountPokemon(ppark))
    return AGBPOKEMON_ERROR_POKEPARK_FULL;
  return AGBPOKEMON_ERROR_NONE;
}


//------------------------------------------------------------------
/**
 * @brief	復帰不可能なエラーを表示する
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
static BOOL AgbCartridge_DisplayError(AGBCARTRIDGE_WORK *wk, int errno)
{
  if(wk->agberror){
    InitUpMessageWindow(wk);
    MsgPrintTouchPanelFlagSet(MSG_TP_ON);
    wk->cwin.msgid = ErrorMsgTable[errno];
    wk->cwin.msgwait = 1;
    CreateMsgWindow(wk, &wk->cwin, MSG_FLAG_FRAME|MSG_FLAG_TALKWIN);
    wk->agberror = 0;
  } else {
    if(GF_MSG_PrintEndCheck(wk->cwin.m_id) == 0){
      MsgPrintTouchPanelFlagSet(MSG_TP_OFF);
      return TRUE;
    }
  }
  return FALSE;
}


//------------------------------------------------------------------
/**
 * @brief	選択が必要なエラー表示
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
static BOOL AgbCartridge_DispYesNoError(AGBCARTRIDGE_WORK *wk, int errno)
{
  if(wk->agberror){
    InitUpMessageWindow(wk);
    MsgPrintTouchPanelFlagSet(MSG_TP_ON);
    wk->cwin.msgid = ErrorMsgTable[errno];
    wk->cwin.msgwait = 1;
    CreateMsgWindow(wk, &wk->cwin, MSG_FLAG_FRAME|MSG_FLAG_TALKWIN);
    wk->agberror = 0;
  } else {
    if(GF_MSG_PrintEndCheck(wk->cwin.m_id) == 0){
       AgbCartridge_ReqYesNoIcon(wk);
       MsgPrintTouchPanelFlagSet(MSG_TP_OFF);
       return TRUE;
    }
  }
  return FALSE;
}


//------------------------------------------------------------------
/**
 * @brief	スクロールが必要なメッセージの表示
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
static BOOL AgbCartridge_DisplayMessage(AGBCARTRIDGE_WORK *wk, int frame)
{
  if(wk->msg_flag != -1){
    InitUpMessageWindow(wk);
    MsgPrintTouchPanelFlagSet(MSG_TP_ON);
    wk->cwin.msgid = wk->msg_flag;
    wk->cwin.msgwait = frame;
    CreateMsgWindow(wk, &wk->cwin, MSG_FLAG_FRAME|MSG_FLAG_TALKWIN);
    wk->msg_flag = -1;
    Snd_SePlay(SEQ_SE_DP_SELECT);
  } else {
    if(frame){
      if(GF_MSG_PrintEndCheck(wk->cwin.m_id) == 0){
	MsgPrintTouchPanelFlagSet(MSG_TP_OFF);
	return TRUE;
      }
    } else {
      if(sys.tp_trg || sys.trg){
	MsgPrintTouchPanelFlagSet(MSG_TP_OFF);
	Snd_SePlay(SEQ_SE_DP_SELECT);
	return TRUE;
      }
    }
  }
  return FALSE;
}


//--------------------------------------------------------------------------------------------
/**
 * @brief	ＡＧＢカセットからもってくる：初期化
 * @param	proc	プロセスへのポインタ
 * @param	seq		シーケンス用ワークへのポインタ
 * @return	PROC_RES_CONTINUE	動作継続中
 * @return	PROC_RES_FINISH		動作終了
 */
//--------------------------------------------------------------------------------------------
static PROC_RESULT AgbCartridgeProc_Init(PROC * proc, int * seq)
{
  AGBCARTRIDGE_WORK *wk;

  sys_CreateHeap( HEAPID_BASE_APP, HEAPID_AGBCARTRIDGE, 0x28000);
  sys_PrintHeapFreeSize(HEAPID_AGBCARTRIDGE);
  wk = PROC_AllocWork(proc, sizeof(AGBCARTRIDGE_WORK), HEAPID_AGBCARTRIDGE);
  /* 初期化不良が怖いのでワークはゼロクリア */
  memset(wk, 0, sizeof(AGBCARTRIDGE_WORK));

  /* 各種変数の初期化 */
  wk->bgl = GF_BGL_BglIniAlloc(HEAPID_AGBCARTRIDGE);

  /* 下画面ウインドウシステム初期化 */
  wk->TouchSubWindowSys = TOUCH_SW_AllocWork(HEAPID_AGBCARTRIDGE);

  /* 画面の初期設定 */
  WIPE_SetBrightness( WIPE_DISP_MAIN, WIPE_FADE_BLACK );
  WIPE_SetBrightness( WIPE_DISP_SUB, WIPE_FADE_BLACK );

  /* 変数初期化 */
  wk->sv = ((MAINWORK *)PROC_GetParentWork(proc))->savedata;
  wk->mst = SaveData_GetMyStatus(wk->sv);
  wk->cfg = SaveData_GetConfig(wk->sv);
  wk->win_type = CONFIG_GetWindowType(wk->cfg);

  /* サウンドデータロード */
  Snd_DataSetByScene( SND_SCENE_AGB, SEQ_PRESENT, 1 );

  /* 同期セーブ用のTick初期化 */
  if(OS_IsTickAvailable() == FALSE)
    OS_InitTick();
  
  /* AGBカートリッジの抜け検出ON */
  MysteryLib_SetAgbCartridgeIntr2();

  _PokeBufPtr = wk->pokebuf;
  
  return PROC_RES_FINISH;
}



//--------------------------------------------------------------------------------------------
/**
 * @brief	ＡＧＢカセットからもってくる：メイン
 * @param	proc	プロセスへのポインタ
 * @param	seq		シーケンス用ワークへのポインタ
 * @return	PROC_RES_CONTINUE	動作継続中
 * @return	PROC_RES_FINISH		動作終了
 */
//--------------------------------------------------------------------------------------------
static PROC_RESULT AgbCartridgeProc_Main(PROC * proc, int * seq)
{
  int selno, seltype, ret;
  AGBCARTRIDGE_WORK *wk = PROC_GetWork(proc);

  // AGBカートリッジが抜けた場合は処理停止
  CTRDG_IsExisting();
  if(CTRDG_IsPulledOut() == TRUE)
    CTRDG_TerminateForPulledOut();
  
  wk->jiffy++;
  
  switch(*seq){

  case AGBCARTRIDGE_SEQ_INIT_CARTRIDGE:
    // カートリッジの初期化
#if 0//def DEBUG_ONLY_FOR_mituhara
    OS_Printf("ポケモンカセットのセーブデータの大きさ = %d\n", AGBPOKE_BUFFERSIZE);
#endif
    agbpoke_preinit();
    wk->cartridge_status = agbpoke_init(wk->buffer);
    if(wk->cartridge_status == AGBPOKE_ERROR_OK){
      wk->load_status = agbpoke_LoadDATA();
      if(wk->load_status == AGBPOKE_ERROR_OK){
	wk->boxdata = agbpoke_getPCdata();
	wk->CurrentBox = wk->boxdata->CurrentBoxNo;
      } else {
	// 例えばボックスに１匹もいないとか、
	// ずかんをもらっていないとか
#if 0//def DEBUG_ONLY_FOR_mituhara
	OS_Printf("AGBカセットデータのロードに失敗しました: %d\n", wk->load_status);
#endif
	wk->agberror = AGBPOKEMON_ERROR_LOAD_FAILD;
      }
    } else {
      // AGBカセットが抜かれた場合には、そもそも処理が停止するため、
      // ここまで処理が来ないはずです。
    }
    // カセットのタイプを設定
    AgbCartridge_SetCartridgeType(wk);
    SetSeq(AGBCARTRIDGE_SEQ_PREINIT_SCREEN);
    break;

  case AGBCARTRIDGE_SEQ_PREINIT_SCREEN:
    // 画面作成
    CreateAgbCartridgeScreen(wk);

    CharPlttManagerInit();
    InitCellActor(wk);
    SetCellActor(wk);
    SetMiscIcon(wk);
    sys_VBlankFuncChange( VBlankFunc, wk );
    GF_Disp_GX_VisibleControl(  GX_PLANEMASK_OBJ, VISIBLE_OFF );	//メイン画面OBJ面OFF

    if(wk->agberror == AGBPOKEMON_ERROR_LOAD_FAILD)
      RequestFade(wk, WIPE_TYPE_FADEIN, AGBCARTRIDGE_SEQ_ERROR_SCREEN, seq);
    else
      SetSeq(AGBCARTRIDGE_SEQ_CHECK_USER);
    break;

  case AGBCARTRIDGE_SEQ_CHECK_USER:
    // カートリッジのユーザー確認
    AgbCartridge_CreateCheckUser(wk);
    RequestFade(wk, WIPE_TYPE_FADEIN, AGBCARTRIDGE_SEQ_CHECK_USER_YESNO, seq);
    break;

  case AGBCARTRIDGE_SEQ_CHECK_USER_YESNO:
    // 確認画面処理
    selno = TOUCH_SW_Main( wk->TouchSubWindowSys );
    switch(selno){
    case TOUCH_SW_RET_YES:		// はい
      TOUCH_SW_Reset( wk->TouchSubWindowSys );
      wk->msg_flag = CHECK_FINAL_MSG;
      SetSeq(AGBCARTRIDGE_SEQ_CHECK_FINAL);
      break;
    case TOUCH_SW_RET_NO:		// いいえ
      TOUCH_SW_Reset( wk->TouchSubWindowSys );
      RequestFadeW(wk, WIPE_TYPE_FADEOUT, AGBCARTRIDGE_SEQ_FINISH, seq);
      break;
    }
    break;

  case AGBCARTRIDGE_SEQ_CHECK_FINAL:
    // 最終確認
    // "つれてきた　ポケモンは　ＧＢＡには\nもどすことが　できません▼
    // ポケモンを　ダイヤモンドに\nつれてきますか？"
    if(AgbCartridge_DisplayMessage(wk, 1)){
      // はい／いいえ選択の登録
      AgbCartridge_ReqYesNoIcon(wk);
      SetSeq(AGBCARTRIDGE_SEQ_CHECK_FINAL_YESNO);
    }
    break;

  case AGBCARTRIDGE_SEQ_CHECK_FINAL_YESNO:
    // 確認画面処理
    selno = TOUCH_SW_Main( wk->TouchSubWindowSys );
    switch(selno){
    case TOUCH_SW_RET_YES:		// はい
      TOUCH_SW_Reset( wk->TouchSubWindowSys );
      // エラーチェックしまくりのすけ
      wk->agberror = AgbCartridge_CheckAgbError(wk);
      if(wk->agberror){
	if(wk->agberror == AGBPOKEMON_ERROR_MACADDRESS || wk->agberror == AGBPOKEMON_ERROR_MOVE_TIME)
	  SetSeq(AGBCARTRIDGE_SEQ_ERROR_YESNO_SCREEN);
	else
	  SetSeq(AGBCARTRIDGE_SEQ_ERROR_SCREEN);
      } else {
	wk->msg_flag = msg_pokepark_08;
	SetSeq(AGBCARTRIDGE_SEQ_DISP_MESSAGE);
      //	RequestFade(wk, WIPE_TYPE_FADEOUT, AGBCARTRIDGE_SEQ_INIT_SCREEN, seq);
      }
      break;
    case TOUCH_SW_RET_NO:		// いいえ
      TOUCH_SW_Reset( wk->TouchSubWindowSys );
      RequestFadeW(wk, WIPE_TYPE_FADEOUT, AGBCARTRIDGE_SEQ_FINISH, seq);
      break;
    }
    break;

  case AGBCARTRIDGE_SEQ_DISP_MESSAGE:
    // "つれていく　ポケモンを\n６ひき　えらんで　ください"
    if(AgbCartridge_DisplayMessage(wk, 1)){
      // はい／いいえ選択の登録
      //      AgbCartridge_ReqYesNoIcon(wk);
      SetSeq(AGBCARTRIDGE_SEQ_DISP_MESSAGE_YESNO);
    }
    break;

  case AGBCARTRIDGE_SEQ_DISP_MESSAGE_YESNO:
    // 確認のタップまたはキー入力を待つ
    if(sys.tp_trg || sys.trg)
      RequestFade(wk, WIPE_TYPE_FADEOUT, AGBCARTRIDGE_SEQ_INIT_SCREEN, seq);
    break;
    
  case AGBCARTRIDGE_SEQ_ERROR_YESNO_SCREEN:
    // 選択が必要なエラー表示[いいえ] → AGBCARTRIDGE_SEQ_ERROR_SCREEN
    // MACアドレスか時間をずらした場合のセーブ処理
    if(AgbCartridge_DispYesNoError(wk, wk->agberror))
      SetSeq(AGBCARTRIDGE_SEQ_ERROR_YESNO_SCREEN2);
    break;

  case AGBCARTRIDGE_SEQ_ERROR_YESNO_SCREEN2:
    selno = TOUCH_SW_Main( wk->TouchSubWindowSys );
    switch(selno){
    case TOUCH_SW_RET_YES:		// はい
      TOUCH_SW_Reset( wk->TouchSubWindowSys );

      wk->cwin.msgwait = 0;
      wk->cwin.msgid = msg_pokepark_42;	// へんこうちゅう　です\nでんげんを　きらないで　ください
      CreateMsgWindow(wk, &wk->cwin, 0);


      wk->save_work.time_icon = TimeWaitIconAdd(&wk->CheckWin, AGBPOKEMON_TFRAMECHR);
      SetSeq(AGBCARTRIDGE_SEQ_ERROR_YESNO_SCREEN3);
      break;
    case TOUCH_SW_RET_NO:		// いいえ
      TOUCH_SW_Reset( wk->TouchSubWindowSys );
      RequestFadeW(wk, WIPE_TYPE_FADEOUT, AGBCARTRIDGE_SEQ_FINISH, seq);
      break;
    }
    break;

  case AGBCARTRIDGE_SEQ_ERROR_YESNO_SCREEN3:
    // ここではセーブが終わるまで戻ってこない
    SaveDsCard(wk);
    TimeWaitIconDel(wk->save_work.time_icon);
    wk->agberror = AGBPOKEMON_ERROR_IMAKARA_24HOUR;
    SetSeq(AGBCARTRIDGE_SEQ_ERROR_SCREEN);
    break;

  case AGBCARTRIDGE_SEQ_ERROR_SCREEN:
    // エラー表示→タイトルへ戻る
    if(AgbCartridge_DisplayError(wk, wk->agberror))
      SetSeq(AGBCARTRIDGE_SEQ_SAVE_END);
    break;

    
  case AGBCARTRIDGE_SEQ_INIT_SCREEN:
    // 画面作成　その２
    DeleteWindow(&wk->CheckWin);
    CreateAgbCartridgeScreen2(wk);
    SetPokemonIcon(wk);
    RedrawPokemonBox(wk);

    // VBlank関数セット
    sys_VBlankFuncChange( VBlankFunc, wk );
    GF_Disp_GX_VisibleControl(  GX_PLANEMASK_OBJ, VISIBLE_ON );	//メイン画面OBJ面ON
    // 「Lv」と「もちもの」だけ表示させる
    DrawStatusWindow(wk, NULL);
    RequestFade(wk, WIPE_TYPE_FADEIN, AGBCARTRIDGE_SEQ_MAIN, seq);

    sys_PrintHeapFreeSize(HEAPID_AGBCARTRIDGE);
    
    break;

  case AGBCARTRIDGE_SEQ_MAIN:
    // 選択メイン
    selno = GF_TP_RectHitTrg((const RECT_HIT_TBL *)wk->iconrect);
    if(selno != RECT_HIT_NONE){
      if(selno < POKEMON_ICON_MAX){
	seltype = SelectPokemon(wk, selno);
	if(seltype == SELECT_POKEMON_SELECT){
	  // ポケモンを選択しました
	  DrawStatusWindow(wk, &(wk->boxdata->PPPBox[wk->CurrentBox][selno]));
	  // 選択したポケモンがMAXに達していたら確認画面へ
	  if(wk->selected == POKEMON_SELECT_MAX){
	    wk->wait_seq = 45;	// 45 * 2で90frameの待ち時間
	    SetSeq(AGBCARTRIDGE_SEQ_WAIT_CHECK_SCREEN);
	  }
	} else if(seltype == SELECT_POKEMON_CANCEL){
	  // 選択を解除しました
	  DrawStatusWindow(wk, NULL);		// 情報ウィンドウの「情報」を消す
	} else if(seltype == SELECT_POKEMON_EGG){
	  // 選択したポケモンがたまごでした
	  wk->msg_flag = msg_pokepark_10;
	  SetSeq(AGBCARTRIDGE_SEQ_SELECT_WARNING);
	} else if(seltype == SELECT_POKEMON_WAZA){
	  // 選択したポケモンがひでんわざを持っていた
	  wk->msg_flag = msg_pokepark_11;
	  SetSeq(AGBCARTRIDGE_SEQ_SELECT_WARNING);
	} else if(seltype == SELECT_POKEMON_ITEM){
	  // 選択したポケモンが持っていけないアイテムを持っていた
	  wk->msg_flag = msg_pokepark_40;
	  SetSeq(AGBCARTRIDGE_SEQ_SELECT_WARNING);
	} else if(seltype == SELECT_POKEMON_FUSEI){
	  // 不正な番号のポケモンだった
	  wk->msg_flag = msg_pokepark_40;
	  SetSeq(AGBCARTRIDGE_SEQ_SELECT_WARNING);
	}
      } else {
	switch(selno){
	case ICON_ARROWL:
	  if(wk->CurrentBox == 0)
	    wk->CurrentBox = BOX_NUM - 1;
	  else
	    wk->CurrentBox--;
	  RedrawPokemonBox(wk);
	  Snd_SePlay(SEQ_SE_DP_SELECT);
	  break;
	case ICON_ARROWR:
	  if(++wk->CurrentBox == BOX_NUM)
	    wk->CurrentBox = 0;
	  RedrawPokemonBox(wk);
	  Snd_SePlay(SEQ_SE_DP_SELECT);
	  break;
	case ICON_CANCEL:
	  RequestFadeW(wk, WIPE_TYPE_FADEOUT, AGBCARTRIDGE_SEQ_FINISH, seq);
	  Snd_SePlay(SEQ_SE_DP_SELECT);
	  break;
	}
      }
    }
    break;

  case AGBCARTRIDGE_SEQ_SELECT_WARNING:
    // 警告表示
    if(AgbCartridge_DisplayMessage(wk, 0)){
      DeleteWindow(&wk->CheckWin);
      SetSeq(AGBCARTRIDGE_SEQ_MAIN);
    }
    break;


  case AGBCARTRIDGE_SEQ_WAIT_CHECK_SCREEN:
    // 確認画面へ行く前の一瞬の間を作る
    if(--wk->wait_seq == 0){
      RequestFade(wk, WIPE_TYPE_FADEOUT, AGBCARTRIDGE_SEQ_CREATE_CHECK_SCREEN, seq);
    }
    break;
    
  case AGBCARTRIDGE_SEQ_CREATE_CHECK_SCREEN:
    // 確認画面の作成
    CreateCheckScreen(wk);
    RequestFade(wk, WIPE_TYPE_FADEIN, AGBCARTRIDGE_SEQ_CREATE_CHECK_TOUCH1, seq);
    // はい／いいえ選択
    AgbCartridge_ReqYesNoIcon(wk);
    break;

  case AGBCARTRIDGE_SEQ_CREATE_CHECK_TOUCH1:
    // 「えらんだ６ひきの　ぽけもんを　つれていきます」確認画面処理
    selno = TOUCH_SW_Main( wk->TouchSubWindowSys );
    switch(selno){
    case TOUCH_SW_RET_YES:		// はい
      TOUCH_SW_Reset( wk->TouchSubWindowSys );
      SetSeq(AGBCARTRIDGE_SEQ_CREATE_CHECK_TOUCH);
      break;
    case TOUCH_SW_RET_NO:		// いいえ
      TOUCH_SW_Reset( wk->TouchSubWindowSys );
      RequestFade(wk, WIPE_TYPE_FADEOUT, AGBCARTRIDGE_SEQ_RETURN_SELECT, seq);
      break;
    }
    break;
    
  case AGBCARTRIDGE_SEQ_CREATE_CHECK_TOUCH:
    // 確認タップ待ち
    //    if(sys.tp_trg)
    {
      REGWIN rwin;
      // メッセージウィンドウの内容を変更する
      wk->cwin.msgid = msg_pokepark_13;	// ルビー　に　もどすことは\nできませんが　よろしい　ですか？
      CreateMsgWindow(wk, &wk->cwin, 0);
      // はい／いいえ選択
      AgbCartridge_ReqYesNoIcon(wk);
      Snd_SePlay(SEQ_SE_DP_SELECT);
      SetSeq(AGBCARTRIDGE_SEQ_CREATE_CHECK_MAIN);
    }
    break;

  case AGBCARTRIDGE_SEQ_CREATE_CHECK_MAIN:
    // 確認画面処理
    selno = TOUCH_SW_Main( wk->TouchSubWindowSys );
    switch(selno){
    case TOUCH_SW_RET_YES:		// はい
      // ××　と　○○の\nポケモンレポートを　かいています
      wk->cwin.msgid = SaveMsgTable[wk->cartridge_type];
      CreateMsgWindow(wk, &wk->cwin, 0);
      //      wk->wait_seq = 60;
      TOUCH_SW_Reset( wk->TouchSubWindowSys );
      wk->save_work.save_seq = SAVE_SEQ_INIT;
      wk->save_work.time_icon = TimeWaitIconAdd(&wk->CheckWin, AGBPOKEMON_TFRAMECHR);

      SetSeq(AGBCARTRIDGE_SEQ_SAVE);
      sys_SoftResetNG(SOFTRESET_TYPE_SAVELOAD);
      break;
    case TOUCH_SW_RET_NO:		// いいえ
      TOUCH_SW_Reset( wk->TouchSubWindowSys );
      RequestFade(wk, WIPE_TYPE_FADEOUT, AGBCARTRIDGE_SEQ_RETURN_SELECT, seq);
      break;
    }
    break;
    
  case AGBCARTRIDGE_SEQ_RETURN_SELECT:
    // 選択画面を復活させる
    ReviveSelectScreen(wk);
    SetSeq(AGBCARTRIDGE_SEQ_INIT_SCREEN);
    break;

  case AGBCARTRIDGE_SEQ_SAVE:
    // 非同期セーブ処理
    ret = SaveSequence(wk);

    if(ret != SAVE_STATUS_WRITING){

      TimeWaitIconDel(wk->save_work.time_icon);

      Snd_SePlay(SEQ_SE_DP_SAVE);

#if 0//def DEBUG_ONLY_FOR_mituhara
      OS_TPrintf("セーブ結果: %d\n", ret);
#endif
      if(ret == SAVE_STATUS_WRITE_SUCCESS)
	wk->cwin.msgid = SAVE_SUCCESS_MSG;	// ６ひきを　ぶじ　[○○]　に\nつれていく　ことが　できました
      else
	wk->cwin.msgid = msg_pokepark_38;	// ポケモンレポートを　かくのに　しっぱい　しました

      CreateMsgWindow(wk, &wk->cwin, 0);
      SetSeq(AGBCARTRIDGE_SEQ_SAVE_END);
      sys_SoftResetOK(SOFTRESET_TYPE_SAVELOAD);
    }
    break;

  case AGBCARTRIDGE_SEQ_SAVE_END:
    // 確認タップ待ち
    if(sys.tp_trg){
      RequestFadeW(wk, WIPE_TYPE_FADEOUT, AGBCARTRIDGE_SEQ_FINISH, seq);
      Snd_SePlay(SEQ_SE_DP_SELECT);
    }
    break;
    
    
  case AGBCARTRIDGE_SEQ_WAIT_FADE:
    // フェードが終了するまで待って次のシーケンスへ
    if(WIPE_SYS_EndCheck()){
      *seq = wk->next_seq;
    }
    break;

  case AGBCARTRIDGE_SEQ_FINISH:
    FinishScreen(wk);
    return PROC_RES_FINISH;
    break;
  }

  // アイコンを表示するために必要な駆動処理
  if(wk->clactSet!=NULL)
    CLACT_Draw( wk->clactSet );

  return PROC_RES_CONTINUE;
}


//--------------------------------------------------------------------------------------------
/**
 * @brief	ＡＧＢカセットからもってくる：終了
 * @param	proc	プロセスへのポインタ
 * @param	seq		シーケンス用ワークへのポインタ
 * @return	PROC_RES_CONTINUE	動作継続中
 * @return	PROC_RES_FINISH		動作終了
 */
//--------------------------------------------------------------------------------------------
static PROC_RESULT AgbCartridgeProc_End(PROC * proc, int * seq)
{
  FS_EXTERN_OVERLAY( title );
  AGBCARTRIDGE_WORK *wk = PROC_GetWork(proc);

  sys_FreeMemoryEz(wk->bgl);
  Main_SetNextProc( FS_OVERLAY_ID(title), &TitleProcData);
  PROC_FreeWork(proc);
  sys_DeleteHeap(HEAPID_AGBCARTRIDGE);
  /* AGBカートリッジの抜け検出OFF */
  MysteryLib_SetAgbCartridgeIntr(FALSE);

  return PROC_RES_FINISH;
}

const PROC_DATA AgbCartridgeProcData = {
  AgbCartridgeProc_Init,
  AgbCartridgeProc_Main,
  AgbCartridgeProc_End,
  NO_OVERLAY_ID,
};

/*  */
