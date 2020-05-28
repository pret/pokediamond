//============================================================================================
/**
 * @file	b_plist_main.h
 * @brief	戦闘用ポケモンリスト画面
 * @author	Hiroyuki Nakamura
 * @date	05.02.01
 */
//============================================================================================
#ifndef B_PLIST_MAIN_H
#define B_PLIST_MAIN_H
#undef GLOBAL
#ifdef B_PLIST_MAIN_H_GLOBAL
#define GLOBAL	/*	*/
#else
#define GLOBAL	extern
#endif


//============================================================================================
//	定数定義
//============================================================================================
// パレット定義
#define	BPL_PAL_NN_PLATE	( 0 )		///< パレット00：プレート（通常）
#define	BPL_PAL_MN_PLATE	( 1 )		///< パレット01：プレート（マルチ）
#define	BPL_PAL_DN_PLATE	( 2 )		///< パレット02：プレート（瀕死）
#define	BPL_PAL_HPGAGE		( 9 )		///< パレット09：HPゲージ

#define	BPL_PAL_B_RED		( 10 )		///< パレット09：ボタン（赤）
#define	BPL_PAL_B_GREEN		( 12 )		///< パレット09：ボタン（緑）

#define	BPL_PAL_SYS_FONT	( 13 )		///< パレット13：システムフォント
#define	BPL_PAL_TALK_WIN	( 14 )		///< パレット14：会話ウィンドウ
#define	BPL_PAL_TALK_FONT	( 15 )		///< パレット15：会話フォント

#define	BPL_HP_DOTTO_MAX	( 48 )		///< HPゲージのドットサイズ

// ウィンドウインデックス
enum {
	WIN_COMMENT = 0,	///< コメント用ウィンドウ
	WIN_TALK,			///< 会話用ウィンドウ
	WIN_MAX
};

// ページ１の追加ウィンドウインデックス
enum {
	WIN_P1_POKE1 = 0,	// ポケモン１
	WIN_P1_POKE2,		// ポケモン２
	WIN_P1_POKE3,		// ポケモン３
	WIN_P1_POKE4,		// ポケモン４
	WIN_P1_POKE5,		// ポケモン５
	WIN_P1_POKE6,		// ポケモン６
	WIN_P1_MAX
};

// 入れ替えページの追加ウィンドウインデックス
enum {
	WIN_CHG_NAME = 0,	// 名前
	WIN_CHG_IREKAE,		// 「いれかえる」
	WIN_CHG_STATUS,		// 「つよさをみる」
	WIN_CHG_WAZACHECK,	// 「わざをみる」
	WIN_CHG_MAX
};

// 技選択ページの追加ウィンドウインデックス
enum {
	WIN_STW_NAME = 0,		// 名前
	WIN_STW_SKILL1,			// 技１
	WIN_STW_SKILL2,			// 技２
	WIN_STW_SKILL3,			// 技３
	WIN_STW_SKILL4,			// 技４

	WIN_STW_STATUS,			// 「つよさをみる」

	// ↓スワップ用
	WIN_STW_NAME_S,			// 名前（スワップ）
	WIN_STW_SKILL1_S,		// 技１（スワップ）
	WIN_STW_SKILL2_S,		// 技２（スワップ）
	WIN_STW_SKILL3_S,		// 技３（スワップ）
	WIN_STW_SKILL4_S,		// 技４（スワップ）

	WIN_STW_MAX
};

// ステータスメインページの追加ウィンドウインデックス
enum {
	WIN_P3_NAME = 0,	// 名前
	WIN_P3_SPANAME,		// 特性名
	WIN_P3_SPAINFO,		// 特性説明
	WIN_P3_ITEMNAME,	// 道具名
	WIN_P3_HPNUM,		// HP値
	WIN_P3_POWNUM,		// 攻撃値
	WIN_P3_DEFNUM,		// 防御値
	WIN_P3_AGINUM,		// 素早さ値
	WIN_P3_SPPNUM,		// 特攻値
	WIN_P3_SPDNUM,		// 特防値
	WIN_P3_HPGAGE,		// HPゲージ
	WIN_P3_LVNUM,		// レベル値
	WIN_P3_NEXTNUM,		// 次のレベル値

	WIN_P3_HP,			// 「HP」
	WIN_P3_POW,			// 「こうげき」
	WIN_P3_DEF,			// 「ぼうぎょ」
	WIN_P3_AGI,			// 「すばやさ」
	WIN_P3_SPP,			// 「とくこう」
	WIN_P3_SPD,			// 「とくぼう」
	WIN_P3_LV,			// 「Lv.」
	WIN_P3_NEXT,		// 「つぎのレベルまで」
	WIN_P3_WAZACHECK,	// 「わざをみる」

	// ↓スワップ用
	WIN_P3_NAME_S,		// 名前（スワップ）
	WIN_P3_SPANAME_S,	// 特性名（スワップ）
	WIN_P3_SPAINFO_S,	// 特性説明（スワップ）
	WIN_P3_ITEMNAME_S,	// 道具名（スワップ）
	WIN_P3_HPNUM_S,		// HP値（スワップ）
	WIN_P3_POWNUM_S,	// 攻撃値（スワップ）
	WIN_P3_DEFNUM_S,	// 防御値（スワップ）
	WIN_P3_AGINUM_S,	// 素早さ値（スワップ）
	WIN_P3_SPPNUM_S,	// 特攻値（スワップ）
	WIN_P3_SPDNUM_S,	// 特防値（スワップ）
	WIN_P3_HPGAGE_S,	// HPゲージ（スワップ）
	WIN_P3_LVNUM_S,		// レベル値（スワップ）
	WIN_P3_NEXTNUM_S,	// 次のレベル値（スワップ）
	WIN_P3_MAX
};

// ステータス技詳細ページの追加ウィンドウインデックス
enum {
	WIN_P4_SKILL = 0,	// 技名
	WIN_P4_PPNUM,		// PP/PP
	WIN_P4_HITNUM,		// 命中値
	WIN_P4_POWNUM,		// 威力値
	WIN_P4_INFO,		// 技説明
	WIN_P4_BRNAME,		// 分類名

	WIN_P4_NAME,		// 名前
	WIN_P4_PP,			// PP
	WIN_P4_HIT,			// 「めいちゅう」
	WIN_P4_POW,			// 「いりょく」
	WIN_P4_BUNRUI,		// 「ぶんるい」

	// ↓スワップ用
	WIN_P4_SKILL_S,		// 技名
	WIN_P4_PPNUM_S,		// PP/PP
	WIN_P4_HITNUM_S,	// 命中値
	WIN_P4_POWNUM_S,	// 威力値
	WIN_P4_INFO_S,		// 技説明
	WIN_P4_BRNAME_S,	// 分類名
	WIN_P4_MAX
};

// 技忘れ選択ページの追加ウィンドウインデックス
enum {
	WIN_P5_NAME = 0,	// 名前
	WIN_P5_SKILL1,		// 技１
	WIN_P5_SKILL2,		// 技２
	WIN_P5_SKILL3,		// 技３
	WIN_P5_SKILL4,		// 技４
	WIN_P5_SKILL5,		// 技５
	WIN_P5_MAX
};

// ページ６の追加ウィンドウインデックス
enum {
	WIN_P6_NAME = 0,	// 名前
	WIN_P6_SKILL,		// 技名
	WIN_P6_PP,			// PP
	WIN_P6_PPNUM,		// PP/PP
	WIN_P6_HIT,			// 「めいちゅう」
	WIN_P6_POW,			// 「いりょく」
	WIN_P6_HITNUM,		// 命中値
	WIN_P6_POWNUM,		// 威力値
	WIN_P6_INFO,		// 技説明
	WIN_P6_BUNRUI,		// 「ぶんるい」
	WIN_P6_BRNAME,		// 分類名
	WIN_P6_WASURERU,	// 「わすれる」
	WIN_P6_MAX
};

// 技回復選択ページの追加ウィンドウインデックス
enum {
	WIN_P7_NAME = 0,	// 名前
	WIN_P7_SKILL1,		// 技１
	WIN_P7_SKILL2,		// 技２
	WIN_P7_SKILL3,		// 技３
	WIN_P7_SKILL4,		// 技４
	WIN_P7_MAX
};

// ページ８の追加ウィンドウインデックス
enum {
	WIN_P8_NAME = 0,	// 名前
	WIN_P8_SKILL,		// 技名
	WIN_P8_PP,			// PP
	WIN_P8_PPNUM,		// PP/PP
	WIN_P8_APP,			// 「アピールポイント」
	WIN_P8_INFO,		// 技説明
	WIN_P8_WASURERU,	// 「わすれる」
	WIN_P8_MAX
};

enum {
	BPL_CA_ITEM1 = 0,
	BPL_CA_ITEM2,
	BPL_CA_ITEM3,
	BPL_CA_ITEM4,
	BPL_CA_ITEM5,
	BPL_CA_ITEM6,

	BPL_CA_ITEM7,

	BPL_CA_POKE1,
	BPL_CA_POKE2,
	BPL_CA_POKE3,
	BPL_CA_POKE4,
	BPL_CA_POKE5,
	BPL_CA_POKE6,

	BPL_CA_STATUS1,
	BPL_CA_STATUS2,
	BPL_CA_STATUS3,
	BPL_CA_STATUS4,
	BPL_CA_STATUS5,
	BPL_CA_STATUS6,

	BPL_CA_POKETYPE1,
	BPL_CA_POKETYPE2,

	BPL_CA_WAZATYPE1,
	BPL_CA_WAZATYPE2,
	BPL_CA_WAZATYPE3,
	BPL_CA_WAZATYPE4,
	BPL_CA_WAZATYPE5,

	BPL_CA_BUNRUI,

	BPL_CA_CND1,
	BPL_CA_CND2,
	BPL_CA_CND3,
	BPL_CA_CND4,
	BPL_CA_CND5,

	BPL_CA_CB1,
	BPL_CA_CB2,
	BPL_CA_CB3,
	BPL_CA_CB4,
	BPL_CA_CB5,
	BPL_CA_CB6,

	BPL_CA_MAX
};

typedef struct {
	u16	id;		// 技番号
	u8	pp;		// PP
	u8	mpp;	// 最大PP

	u8	type;	// タイプ
	u8	kind;	// 分類
	u8	hit;	// 命中
	u8	pow;	// 威力
}BPL_POKEWAZA;

typedef struct {
	POKEMON_PARAM * pp;		// ポケモンデータ

	u16	mons;		// ポケモン番号
	u16	pow;		// 攻撃

	u16	def;		// 防御
	u16	agi;		// 素早さ

	u16	spp;		// 特攻
	u16	spd;		// 特防

	u16	hp;			// HP
	u16	mhp;		// 最大HP

	u8	type1;		// タイプ１
	u8	type2;		// タイプ２
	u8	lv:7;		// レベル
	u8	sex_put:1;	// 性別表示（ニドラン用）0=ON, 1=OFF
	u8	sex:3;		// 性別
	u8	st:4;		// 状態異常
	u8	egg:1;		// タマゴ

	u16	spa;		// 特性
	u16	item;		// アイテム

	u32	now_exp;		// 現在の経験値
	u32	now_lv_exp;		// 現在のレベルの経験値
	u32	next_lv_exp;	// 次のレベルの経験値

	u8	style;			// かっこよさ
	u8	beautiful;		// うつくしさ
	u8	cute;			// かわいさ
	u8	clever;			// かしこさ
	u8	strong;			// たくましさ

	u8	cb;				// カスタムボール
	u8	form;			// フォルムNo

	BPL_POKEWAZA	waza[4];	// 技データ

}BPL_POKEDATA;

#define	BPL_BANM_MAX_N	( 3 )		// ボタンアニメパターン数（通常）
#define	BPL_BANM_MAX_E	( 4 )		// ボタンアニメパターン数（押せないボタンあり）
// プレートボタンサイズ
#define	BPL_BSX_PLATE	( 16 )
#define	BPL_BSY_PLATE	( 6 )
// 命令ボタンサイズ
#define	BPL_BSX_COMMAND	( 13 )
#define	BPL_BSY_COMMAND	( 5 )
// 切り替えボタンサイズ
#define	BPL_BSX_UPDOWN	( 5 )
#define	BPL_BSY_UPDOWN	( 5 )
// 戻るボタンサイズ
#define	BPL_BSX_RET		( 5 )
#define	BPL_BSY_RET		( 5 )
// 入れ替えボタン
#define	BPL_BSX_CHG		( 30 )
#define	BPL_BSY_CHG		( 17 )
// 技ボタンサイズ
#define	BPL_BSX_WAZA	( 16 )
#define	BPL_BSY_WAZA	( 6 )
// 忘れるボタンサイズ
#define	BPL_BSX_DEL		( 26 )
#define	BPL_BSY_DEL		( 5 )
// コンテスト切り替えボタンサイズ
#define	BPL_BSX_CONTEST	( 9 )
#define	BPL_BSY_CONTEST	( 4 )
// 技位置ボタン
#define	BPL_BSX_WP		( 5 )
#define	BPL_BSY_WP		( 2 )

typedef struct {
	BPLIST_DATA * dat;	// 外部参照データ

	BPL_POKEDATA	poke[6];	// ポケモンデータ

	GF_BGL_INI * bgl;		// BGデータ

	PALETTE_FADE_PTR pfd;	// パレットフェードデータ

	u16	btn_plate1[BPL_BANM_MAX_E][BPL_BSX_PLATE*BPL_BSY_PLATE];		// 戦闘中のプレートボタン
	u16	btn_plate2[BPL_BANM_MAX_E][BPL_BSX_PLATE*BPL_BSY_PLATE];		// 控えのプレートボタン
	u16	btn_command[BPL_BANM_MAX_E][BPL_BSX_COMMAND*BPL_BSY_COMMAND];	// 命令ボタン
	u16	btn_up[BPL_BANM_MAX_E][BPL_BSX_UPDOWN*BPL_BSY_UPDOWN];			// 切り替えボタン（上）
	u16	btn_down[BPL_BANM_MAX_E][BPL_BSX_UPDOWN*BPL_BSY_UPDOWN];		// 切り替えボタン（下）
	u16	btn_ret[BPL_BANM_MAX_E][BPL_BSX_RET*BPL_BSY_RET];				// 戻るボタン
	u16	btn_chg[BPL_BANM_MAX_N][BPL_BSX_CHG*BPL_BSY_CHG];				// 入れ替えボタン
	u16	btn_waza[BPL_BANM_MAX_E][BPL_BSX_WAZA*BPL_BSY_WAZA];			// 技ボタン
	u16	btn_del[BPL_BANM_MAX_N][BPL_BSX_DEL*BPL_BSY_DEL];				// 忘れるボタン
	u16	btn_contest[BPL_BANM_MAX_N][BPL_BSX_CONTEST*BPL_BSY_CONTEST];	// コンテスト切り替えボタン
	u16	btn_wp[BPL_BANM_MAX_N][BPL_BSX_WP*BPL_BSY_WP];					// 技位置ボタン

	u16	wb_pal[16*2];	// 技ボタンのパレット

	u8	btn_seq;
	u8	btn_cnt;
	u8	btn_id;
	u8	btn_mode:4;
	u8	btn_pat:3;
	u8	btn_flg:1;

	NUMFONT * nfnt;					// 8x8フォント
	MSGDATA_MANAGER * mman;			// メッセージデータマネージャ
	WORDSET * wset;					// 単語セット
	STRBUF * msg_buf;				// メッセージ用バッファ

	CATS_RES_PTR	crp;				// リソース管理
	CATS_ACT_PTR	cap[BPL_CA_MAX];	// OAMのCAP

	GF_BGL_BMPWIN	win[WIN_MAX];	// BMPウィンドウデータ（通常）
	GF_BGL_BMPWIN * add_win;		// BMPウィンドウデータ（追加）
	u8	bmp_add_max;				// 追加したBMPの数
	u8	bmp_swap;					// スワップ描画フラグ

	u8	init_poke;		// 入れ替え対象のポケモン位置

	u8	bc_put:4;			// 技の表示が戦闘かコンテストか
	u8	ev_contest:4;		// コンテスト表示許可フラグ

	u8	seq;			// メインシーケンス
	u8	ret_seq;		// 復帰シーケンス
	u8	page;			// 現在のページ
	u8	midx;			// メッセージインデックス

	u8	rcv_seq;
	u8	rcv_st;
	u16	rcv_hp;
	u16	rcv_pp[4];

	BAPP_CURSOR_MVWK * cmv_wk;	// カーソル制御ワーク
	u8	chg_page_cp;			// ポケモン入れ替えページのカーソル位置
	u8	wws_page_cp;			// ステータス技忘れ技選択ページのカーソル位置
	u8	wwm_page_cp;			// ステータス技忘れ技詳細ページのカーソル位置

	u8	multi_pos;				// マルチバトルの立ち位置
}BPLIST_WORK;




//--------------------------------------------------------------------------------------------
/**
 * 指定位置にポケモンが存在するか
 *
 * @param	wk		ワーク
 * @param	pos		位置
 *
 * @retval	"0 = いない"
 * @retval	"1 = 戦闘中"
 * @retval	"2 = 控え"
 */
//--------------------------------------------------------------------------------------------
GLOBAL u8 BattlePokeList_PokeSetCheck( BPLIST_WORK * wk, s32 pos );

//--------------------------------------------------------------------------------------------
/**
 * ダブルバトルチェック
 *
 * @param	wk		ワーク
 *
 * @retval	"TRUE = ダブルバトル"
 * @retval	"FALSE = ダブルバトル以外"
 */
//--------------------------------------------------------------------------------------------
GLOBAL u8 BattlePokeList_DoubleCheck( BPLIST_WORK * wk );

//--------------------------------------------------------------------------------------------
/**
 * マルチバトルチェック
 *
 * @param	wk		ワーク
 *
 * @retval	"TRUE = ダブルバトル"
 * @retval	"FALSE = ダブルバトル以外"
 */
//--------------------------------------------------------------------------------------------
GLOBAL u8 BattlePokeList_MultiCheck( BPLIST_WORK * wk );

//--------------------------------------------------------------------------------------------
/**
 * マルチバトルでパートナーのポケモンかチェック
 *
 * @param	wk		ワーク
 * @param	pos		位置
 *
 * @retval	"TRUE = はい"
 * @retval	"FALSE = いいえ"
 */
//--------------------------------------------------------------------------------------------
GLOBAL u8 BattlePokeList_MultiPosCheck( BPLIST_WORK * wk, u8 pos );


#undef GLOBAL
#endif	// B_PLIST_MAIN_H
