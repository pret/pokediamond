//=============================================================================
/**
 * @file	heapdefine.h
 * @brief	ポケモンＤＰ ヒープ種別指定
 * @author	taya  GAME FREAK Inc.
 */
//=============================================================================
#ifndef __HEAPDEFINE_H__
#define __HEAPDEFINE_H__



//----------------------------------------------------------------------------
/**
 *  基本ヒープ定義  
 *
 *  システム、アプリなど大まかな設定のみ行う。
 *  最初にアリーナからメモリを確保するのはこれらのヒープグループのみ。
 *
 *  各種アプリはこれらのヒープから直接メモリをアロケートするのではなく、
 *  アプリ用の大きなヒープ内にさらにヒープを作成し、そこからアロケートする。
 *
 */
//----------------------------------------------------------------------------
typedef enum {
	HEAPID_BASE_SYSTEM,
	HEAPID_BASE_SAVE,
	_HEAPID_BASE_DEBUG,
	HEAPID_BASE_APP,

	HEAPID_BASE_MAX,
}BASE_HEAPID;

#define HEAPID_BASE_DEBUG  (HEAPID_BASE_APP)

//----------------------------------------------------------------------------
/**
 *  ユーザーヒープ定義  
 *
 *  各アプリごとに固有のヒープＩＤを切る。
 *  アリーナからメモリを確保するのではなく、上記の基本ヒープの中からさらに
 *  ヒープを作成して、そのヒープからメモリブロックをアロケートする。
 */
//----------------------------------------------------------------------------
typedef enum {
	HEAPID_FIELD = HEAPID_BASE_MAX,		// フィールド
	HEAPID_BATTLE,						// 戦闘
	HEAPID_BAG,							// バッグ
	HEAPID_POKETCH_MAIN,				// ポケッチ（メイン）
	HEAPID_POKETCH_APP,					// ポケッチ（アプリ）
	HEAPID_BOX_SYSTEM,					// ボックス（システム制御）
	HEAPID_BOX_VIEW,					// ボックス（描画ワーク）
	HEAPID_WORLD,						//ワールド
	HEAPID_POKELIST,					// ポケモンリスト
	HEAPID_IMAGECLIP_DATA,				// イメージクリップデータワーク
	HEAPID_IMAGECLIP_DRAW,				// イメージクリップ描画ワーク
    HEAPID_COMMUNICATION,               // 通信
	HEAPID_TITLE,						// タイトル画面
	HEAPID_TOWNMAP,						// タウンマップ
	HEAPID_NAMEIN,						// 名前入力
	HEAPID_POKESTATUS,					// ポケモンステータス画面
	HEAPID_CONTEST,						// コンテスト全体システム
	HEAPID_ACTIN,						// コンテスト：演技力部門
	HEAPID_VISUAL,						// コンテスト：ビジュアル部門
	HEAPID_DANCE,						// コンテスト：ダンス部門
	HEAPID_CONRES,						// コンテスト：結果発表画面
	HEAPID_TR_CARD,						// トレーナーカード
	HEAPID_TRADELIST,					// ポケモン交換リスト画面
	HEAPID_DEBUG_APPLICATION,			// デバッグアプリケーション用
	HEAPID_OPENING,						// オープニング
    HEAPID_DIGFOSSIL,                   // 化石掘り
    HEAPID_TITLE_DEMO,                  // タイトルデモ30
	HEAPID_UNIONROOM,					// ユニオンルーム用
	HEAPID_EVENT,						// イベント用
	HEAPID_UNDERGROUND,					// 地下での会話用
	HEAPID_PMS_INPUT_SYSTEM,			// 簡易会話入力画面（システム制御）
	HEAPID_PMS_INPUT_VIEW,				// 簡易会話入力画面（描画ワーク）
	HEAPID_NUTSTAG,						// 木の実タグ画面
	HEAPID_ZUKAN,						// 図鑑用
	HEAPID_CONFIG,						// コンフィグ用
	HEAPID_OEKAKI,						// お絵かきボード用
	HEAPID_MAILSYS,						// メール用
	HEAPID_MAILVIEW,					// メール閲覧用
	HEAPID_FANTASYNOTE,					// 冒険ノート用
	HEAPID_MAILBOX,						// メールボックス用
	HEAPID_PORUTO,						// ポルトコントローラ用
	HEAPID_PORUTO_CASE,					// ポルトケース用
	HEAPID_PORUTO_DEMO,					// ポルトデモ用
	HEAPID_EV_POKESELECT,				// 開始ポケモンセレクト用
	HEAPID_MYSIGN,						// トレーナーサイン用
    HEAPID_WIFIMENU,                    // WIFIメニュー
    HEAPID_WIFIEARTH,                   // 世界通信履歴
	HEAPID_RECORD,						// レコードコーナー用
    HEAPID_WIFINOTE,                    // WIFI友達手帳
	HEAPID_CUSTOM_BALL,					// カスタムボール
    HEAPID_WIFIP2PMATCH,                // WIFI P2P マッチング画面用
	HEAPID_NUT_MIXER,					// 木の実まぜまぜシステム
	HEAPID_NMIXER_GM,					// 木の実まぜまぜ本体
	HEAPID_DEMO_TRADE_MAIN,				// ポケモン交換デモ（メイン）
	HEAPID_DEMO_TRADE_SUB,				// ポケモン交換デモ（サブ）
	HEAPID_BTLTOWER_SCR,				// バトルタワースクリプト
	HEAPID_DENDOU_PC,					// 殿堂入りPC画面（システム）
	HEAPID_DENDOU_PC_VIEW,				// 殿堂入りPC画面（描画）
	HEAPID_WORLDTRADE,					// wifi世界交換画面
	HEAPID_DENDOU_DEMO,					// 殿堂入りデモ
	HEAPID_FIELD_FLDOBJ_MDL,			// フィールド　フィールドOBJ　モデル
	HEAPID_FIELD_FLDOBJ_ANM,			// フィールド　フィールドOBJ　アニメ
	HEAPID_FIELD_FE,					// フィールド　フィールドエフェクト
	HEAPID_WAZAOSHIE,					// 技教え/思い出し画面
	HEAPID_WIFI_BATTLETOWER,			// WIFIバトルタワー接続画面
	HEAPID_FIELD_FE_BLACT_MDL,			// フィールド　フィールドエフェクト　モデル
	HEAPID_FIELD_FE_BLACT_ANM,			// フィールド　フィールドエフェクト　アニメ
	HEAPID_EGG_DEMO,					// たまご孵化デモ
	HEAPID_SHIPDEMO,					// 船デモ
	HEAPID_ITEMSHINKA,					// アイテム進化用
	HEAPID_BTOWER_APP,					// タワー関連アプリ
	HEAPID_ENDING_DEMO,					// エンディングデモ
	HEAPID_OP_DEMO,						// オープニングデモ
	HEAPID_GAMEINIT,					// ゲーム初期化処理
	HEAPID_AGBCARTRIDGE,					// ＡＧＢカートリッジからもってくる画面
	HEAPID_SLOT,						// スロット
	HEAPID_RANKING_VIEW,				// ギネスホールランキング画面
	HEAPID_STARTMENU,					// スタートメニュー画面
	HEAPID_INTRO,						// 導入デモ
	HEAPID_INTRO_TV,					// 導入デモＴＶ
	HEAPID_SYOUJYOU,					// 表彰状
	HEAPID_POKEMONRANGER,					// ポケモンレンジャーとの接続画面
	HEAPID_MYSTERYGIFT,					// ふしぎなおくりもの画面
	HEAPID_MYSTERYCARD,					// ふしぎなおくりもの カードを見る画面
	HEAPID_BACKUPCONT,					// バックアップコントロール用
	HEAPID_UNIONBOARD,
	HEAPID_GAMECLEAR,					// ゲームクリア時のデータセーブ画面
    HEAPID_COMMICON,                    // 通信アイコン
	HEAPID_MAX,
}HEAPID;


#endif
