//============================================================================================
/**
 * @file	b_plist.h
 * @brief	戦闘用ポケモンリスト画面　外部公開ヘッダファイル
 * @author	Hiroyuki Nakamura
 * @date	05.02.01
 */
//============================================================================================
#ifndef B_PLIST_H
#define B_PLIST_H
#undef GLOBAL
#ifdef B_PLIST_H_GLOBAL
#define GLOBAL	/*	*/
#else
#define GLOBAL	extern
#endif


//============================================================================================
//	定数定義
//============================================================================================
#define	BPL_SEL_EXIT		( 6 )	// キャンセル
#define	BPL_SEL_WP_CANCEL	( 4 )	// 技忘れキャンセル（新しく覚える技位置）

// リスト処理定義
enum {
	BPL_MODE_NORMAL = 0,	// 通常のポケモン選択
	BPL_MODE_NO_CANCEL,		// キャンセル不可
	BPL_MODE_ITEMUSE,		// アイテム使用
	BPL_MODE_WAZASET,		// 技忘れ
};

// ページ定義
enum {
	BPLIST_PAGE_SELECT = 0,		// ポケモン選択ページ
	BPLIST_PAGE_POKE_CHG,		// ポケモン入れ替えページ
	BPLIST_PAGE_MAIN,			// ステータスメインページ	
	BPLIST_PAGE_WAZA_SEL,		// ステータス技選択ページ
	BPLIST_PAGE_SKILL,			// ステータス技詳細ページ
	BPLIST_PAGE_PP_RCV,			// PP回復技選択ページ
	BPLIST_PAGE_WAZASET_BS,		// ステータス技忘れ１ページ（戦闘技選択）
	BPLIST_PAGE_WAZASET_BI,		// ステータス技忘れ２ページ（戦闘技詳細）
	BPLIST_PAGE_WAZASET_CS,		// ステータス技忘れ３ページ（コンテスト技選択）
	BPLIST_PAGE_WAZASET_CI,		// ステータス技忘れ４ページ（コンテスト技詳細）
};

// リストデータ
typedef struct {
	POKEPARTY * pp;		// ポケモンデータ
	void * myitem;		// アイテムデータ

	BATTLE_WORK * bw;		// 戦闘用ワーク

	u32	heap;			// ヒープID

//	u8	fight_type;		// シングル／ダブル／マルチ
	u8	multi_pos;		// マルチの立位置
	u8	sel_poke;		// 選択されたポケモン or 戻る
	u8	double_sel;		// ダブルバトルですでに選択されているポケモン
	u8	ret_mode;		// 選択された処理

	u8	fight_poke1;	// 戦闘に出ているポケモン１
	u8	fight_poke2;	// 戦闘に出ているポケモン２

	u32	skill_item_use[2];	// 技で使用不可

	u16	hp_rcv;			// HP回復量

	u16	item;			// アイテム
	u16	chg_waza;		// いれかえ禁止技・新しく覚える技

	s32 client_no;						// クライアントNo
	u8	list_row[POKEMON_TEMOTI_MAX];	// リストロウ

	u8	cursor_flg;		// カーソル表示フラグ

	u8	bag_page;		// バッグのページ

	u8	sel_wp;			// 選択された技位置

	u8	mode;			// リストモード
	u8	end_flg;		// 終了フラグ

}BPLIST_DATA;


//============================================================================================
//	プロトタイプ宣言
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * 戦闘用ポケモンリストタスク追加
 *
 * @param	dat		リストデータ
 *
 * @return none
 */
//--------------------------------------------------------------------------------------------
GLOBAL void BattlePokeList_TaskAdd( BPLIST_DATA * dat );


#undef GLOBAL
#endif	/* B_PLIST_H */
