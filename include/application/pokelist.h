//============================================================================================
/**
 * @file	pokelist.h
 * @brief	ポケモンリスト画面処理
 * @author	Hiroyuki Nakamura
 * @date	05.09.20
 */
//============================================================================================
#ifndef POKELIST_H
#define POKELIST_H

#include "savedata/config.h"

#undef GLOBAL
#ifdef POKELIST_H_GLOBAL
#define GLOBAL	/*	*/
#else
#define GLOBAL	extern
#endif


//============================================================================================
//	定数定義
//============================================================================================

// ポケモンリスト外部作成データ
typedef struct {
	POKEPARTY * pp;		// ポケモンデータ
	void * myitem;		// アイテムデータ
	void * mailblock;	// メールデータ
	CONFIG * cfg;		// コンフィグデータ
	void * tvwk;		// テレビワーク
	void * reg;			// レギュレーションデータ

	void * scwk;		// 技使用チェックワーク

	void * fsys;		// フィールドワーク

	u8	mode;			// リストモード
	u8	type;			// リストタイプ
	u8	ret_sel;		// 選択されたポケモン or 決定 or 戻る
	u8	ret_mode;		// 選択された処理

	u16	item;			// アイテム
	u16	waza;			// 技
	u8	waza_pos;		// 技位置

	u8	con_mode;		// コンテストモード（コンテスト/コンクール/トライアル）
	u8	con_type;		// コンテストタイプ（美しさとか賢さとか）
	u8	con_rank;		// コンテストランク

	u8	in_num[6];		// 参加番号
	u8	in_min:4;		// 参加最小数
	u8	in_max:4;		// 参加最大数
	u8	in_lv;			// 参加レベル

	int	lv_cnt;			// レベルアップカウンタ

	u16	after_mons;		// 進化後のポケモン
	int	shinka_cond;	// 進化条件ワーク

}PLIST_DATA;

// リストタイプ
enum {
	PL_TYPE_SINGLE = 0,		// シングル
	PL_TYPE_DOUBLE,			// ダブル
	PL_TYPE_MULTI,			// マルチ
};

// リストモード
enum {
	PL_MODE_FIELD = 0,			// フィールドメニュー
	PL_MODE_BATTLE,				// 戦闘
	PL_MODE_SELECT,				// 「けってい」あり
	PL_MODE_SET,				// 選択だけ（メニューなし）
	PL_MODE_IN,					// マルチバトル開始エフェクト
	PL_MODE_ITEMUSE,			// アイテム使用
	PL_MODE_WAZASET,			// 技覚え
	PL_MODE_WAZASET_RET,		// ステータス画面から技を選択して戻ってきたとき（技マシン）
	PL_MODE_LVUPWAZASET_RET,	// ステータス画面から技を選択して戻ってきたとき（不思議なアメ）
	PL_MODE_ITEMSET,			// アイテム「もたせる」
	PL_MODE_ITEMSET_RET,		// ポケモンリスト「もたせる」バッグから
	PL_MODE_MAILSET,			// メール「もたせる」終了
	PL_MODE_MAILSET_BAG,		// ポケモンリスト メール「もたせる」終了（バッグから）
	PL_MODE_CONTEST,			// コンテスト参加選択
	PL_MODE_MAILBOX,			// メールボックスからメールを持たせる
	PL_MODE_KAPSEL_SET,			// カプセルセット用
	PL_MODE_SHINKA,				// 進化アイテム使用
	PL_MODE_BATTLE_TOWER,		// バトルタワー参加選択用
	PL_MODE_SODATEYA,			// 育て屋
	PL_MODE_NPC_TRADE,			// ゲーム内交換
	PL_MODE_PORUTO,				// ポルトを使用選択用
};

#define	PL_MODE_NO_CANCEL	( 0x80 )	// キャンセル禁止

// 選択されたもの
enum {
	PL_SEL_POS_POKE1 = 0,	// ポケモン１
	PL_SEL_POS_POKE2,		// ポケモン２
	PL_SEL_POS_POKE3,		// ポケモン３
	PL_SEL_POS_POKE4,		// ポケモン４
	PL_SEL_POS_POKE5,		// ポケモン５
	PL_SEL_POS_POKE6,		// ポケモン６
	PL_SEL_POS_ENTER,		// 決定
	PL_SEL_POS_EXIT,		// 戻る
};

// 選択された処理
enum {
	PL_RET_NORMAL = 0,		// 通常
	PL_RET_STATUS,			// メニュー「つよさをみる」
	PL_RET_CHANGE,			// メニュー「いれかえる」
	PL_RET_ITEMSET,			// メニュー「もたせる」

	PL_RET_WAZASET,			// 技選択へ（技マシン）
	PL_RET_LVUP_WAZASET,	// 技選択へ（不思議なアメ）
	PL_RET_MAILSET,			// メール入力へ
	PL_RET_MAILREAD,		// メールを読む画面へ

	PL_RET_ITEMSHINKA,		// 進化画面へ（アイテム進化）
	PL_RET_LVUPSHINKA,		// 進化画面へ（レベル進化）

	PL_RET_BAG,				// バッグから呼ばれた場合で、バッグへ戻る

/** ↓↓↓ field_skillや冒険ノートと同じ並びで！ ↓↓↓ **/
	PL_RET_IAIGIRI,			// メニュー 技：いあいぎり
	PL_RET_SORAWOTOBU,		// メニュー 技：そらをとぶ
	PL_RET_NAMINORI,		// メニュー 技：なみのり
	PL_RET_KAIRIKI,			// メニュー 技：かいりき
	PL_RET_KIRIBARAI,		// メニュー 技：きりばらい
	PL_RET_IWAKUDAKI,		// メニュー 技：いわくだき
	PL_RET_TAKINOBORI,		// メニュー 技：たきのぼり
	PL_RET_ROCKCLIMB,		// メニュー 技：ロッククライム

	PL_RET_FLASH,			// メニュー 技：フラッシュ
	PL_RET_TELEPORT,		// メニュー 技：テレポート
	PL_RET_ANAWOHORU,		// メニュー 技：あなをほる
	PL_RET_AMAIKAORI,		// メニュー 技：あまいかおり
	PL_RET_OSYABERI,		// メニュー 技：おしゃべり
	PL_RET_MILKNOMI,		// メニュー 技：ミルクのみ
	PL_RET_TAMAGOUMI,		// メニュー 技：タマゴうみ
};

#define	PL_PANEL_SX			( 16 )
#define	PL_PANEL_SY			( 6 )

#define	PL_PANEL_PAL_START	( 3 )


//============================================================================================
//	グローバル変数
//============================================================================================
#ifndef POKELIST_H_GLOBAL
GLOBAL const PROC_DATA PokeListProcData;	// プロセス定義データ
#endif


//============================================================================================
//	プロトタイプ宣言
//============================================================================================

GLOBAL u16 PokeList_WazaNumGet( u8 menu_id );
GLOBAL u8 PokeList_WazaMenuIDGet( u16 waza );


//--------------------------------------------------------------------------------------------
/**
 * フィールド技使用可能フラグを立てる
 *
 * @param	dat		ポケモンリストデータ
 * @param	waza	技ID
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
//GLOBAL void PokeList_SkillUseFlagSet( PLIST_DATA * dat, u16 waza );


//--------------------------------------------------------------------------------------------
/**
 * アイテムアイコンのキャラのアーカイブインデックス取得
 *
 * @param	none
 *
 * @return	キャラのアーカイブインデックス
 */
//--------------------------------------------------------------------------------------------
GLOBAL u32 Pokelist_ItemIconCgxArcGet(void);

//--------------------------------------------------------------------------------------------
/**
 * アイテムアイコンのパレットのアーカイブインデックス取得
 *
 * @param	none
 *
 * @return	パレットのアーカイブインデックス
 */
//--------------------------------------------------------------------------------------------
GLOBAL u32 Pokelist_ItemIconPalArcGet(void);

//--------------------------------------------------------------------------------------------
/**
 * アイテムアイコンのセルのアーカイブインデックス取得
 *
 * @param	none
 *
 * @return	セルのアーカイブインデックス
 */
//--------------------------------------------------------------------------------------------
GLOBAL u32 Pokelist_ItemIconCellArcGet(void);

//--------------------------------------------------------------------------------------------
/**
 * アイテムアイコンのセルアニメのアーカイブインデックス取得
 *
 * @param	none
 *
 * @return	セルアニメのアーカイブインデックス
 */
//--------------------------------------------------------------------------------------------
GLOBAL u32 Pokelist_ItemIconCAnmArcGet(void);


GLOBAL void PoleList_PokePlateScreenGet( u32 heap, u16 * top, u16 * normal, u16 * none );



#undef GLOBAL
#endif	/* POKELIST_H */
