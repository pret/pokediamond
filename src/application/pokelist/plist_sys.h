//============================================================================================
/**
 * @file	plist_sys.h
 * @brief	ポケモンリスト関連ファイルの共通定義
 * @author	Hiroyuki Nakamura
 * @date	05.09.29
 */
//============================================================================================
#ifndef PLIST_SYS_H
#define PLIST_SYS_H


#define	PL_HP_DOTTO_MAX		( 48 )	// HPゲージのドットサイズ

#define	PL_PANEL_HPGAGE_CLEAR_CHR	( 0x17 )	// パネル内のHPゲージX位置
#define	PL_PANEL_HPGAGE_PX			( 6 )		// パネル内のHPゲージX位置
#define	PL_PANEL_HPGAGE_PY			( 3 )		// パネル内のHPゲージY位置
#define	PL_PANEL_HPGAGE_SX			( 9 )		// パネル内のHPゲージXサイズ
#define	PL_PANEL_HPGAGE_SY			( 1 )		// パネル内のHPゲージYサイズ

#define	PL_MENU_WIN_CGX		( 1 )
#define	PL_TALK_WIN_CGX		( PL_MENU_WIN_CGX + MENU_WIN_CGX_SIZ )

#define	TMP_MSG_SIZE		( 256 )		// メッセージ展開領域サイズ（文字数）
#define	MENU_STR_SIZE		( 32 )		// メニュー文字列展開領域サイズ（文字数）

// シーケンス
enum {
	SEQ_IN = 0,
	SEQ_MAIN,
	SEQ_MENU,

	SEQ_MENUWAZA_ERR,		// 技使用エラー

	SEQ_ITEMUSE_SEL,
	SEQ_ITEMUSE_WAIT,

	SEQ_WAZAMENU_SEL,		// 技選択メニュー

	SEQ_ITEMUSE_ALLDEATHRCV,	// 全体瀕死回復

	// バッグからの「持たせる」
	SEQ_ITEMSET_SEL,
	SEQ_ITEMSET_YN_INIT,
	SEQ_ITEMSET_YN_MAIN,
	SEQ_ITEMSET_WAIT,

	SEQ_MAILSET_END,

	SEQ_ITEM_MENU,
	SEQ_ITEM_MENU_SET_RET,	// バッグから戻り
	SEQ_ITEM_MENU_GET,

	SEQ_ITEMGET_END,

	SEQ_WAZASET_SEL,		// 技覚え
	SEQ_WAZASET_RET_SET,	// 技覚え：忘れて覚える

	SEQ_BTLIN_ERR,			// 戦闘参加エラー

	SEQ_MSG_WAIT,		// メッセージウェイト
	SEQ_ENDTRG_WAIT,	// トリガーウェイト -> 終了
	SEQ_YESNO_INIT,		// はい・いいえ表示
	SEQ_YESNO_MAIN,		// はい・いいえ選択

	SEQ_ROW_SEL,
	SEQ_FUNC_WAIT,

	SEQ_MILKNOMI,		// ミルクのみ・タマゴうみ

	SEQ_OUT_SET,
	SEQ_OUT,
};

// BGパレット
enum {
	PAL_FONT = 0,
	PAL_BG,

	PAL_PANEL_0 = PL_PANEL_PAL_START,
	PAL_PANEL_1,
	PAL_PANEL_2,
	PAL_PANEL_3,
	PAL_PANEL_4,
	PAL_PANEL_5,

	PAL_TALK_FONT = 13,
	PAL_MENU_WIN,
	PAL_TALK_WIN
};

// BMPウィンドウインデックス
enum {
	WIN_POKE1_NAME = 0,
	WIN_POKE1_LV,
	WIN_POKE1_HP,
	WIN_POKE1_HPBAR,
	WIN_POKE1_COMM,
	WIN_POKE2_NAME,
	WIN_POKE2_LV,
	WIN_POKE2_HP,
	WIN_POKE2_HPBAR,
	WIN_POKE2_COMM,
	WIN_POKE3_NAME,
	WIN_POKE3_LV,
	WIN_POKE3_HP,
	WIN_POKE3_HPBAR,
	WIN_POKE3_COMM,
	WIN_POKE4_NAME,
	WIN_POKE4_LV,
	WIN_POKE4_HP,
	WIN_POKE4_HPBAR,
	WIN_POKE4_COMM,
	WIN_POKE5_NAME,
	WIN_POKE5_LV,
	WIN_POKE5_HP,
	WIN_POKE5_HPBAR,
	WIN_POKE5_COMM,
	WIN_POKE6_NAME,
	WIN_POKE6_LV,
	WIN_POKE6_HP,
	WIN_POKE6_HPBAR,
	WIN_POKE6_COMM,

	WIN_ENTER,			// 「けってい」
	WIN_EXIT,			// 「もどる」

	WIN_S_MSG,			// １行メッセージ
	WIN_M_MSG,			// １行メッセージ（メニュー表示時）
	WIN_L_MSG,			// ２行メッセージ（通常）
	WIN_ITEM_MENU,		// アイテムメニュー
	WIN_WAZA_MENU,		// 技メニュー

	WIN_MAX
};

// 追加BMPウィンドウインデックス
enum {
	ADD_WIN_MENU = 0,

	ADD_WIN_MAX
};

// OBJ定義
enum {
	PLIST_ACT_BALL1 = 0,
	PLIST_ACT_BALL2,
	PLIST_ACT_BALL3,
	PLIST_ACT_BALL4,
	PLIST_ACT_BALL5,
	PLIST_ACT_BALL6,
	PLIST_ACT_CURSOR1,
	PLIST_ACT_CURSOR2,
	PLIST_ACT_ENTER,
	PLIST_ACT_EXIT,

	PLIST_ACT_ST1,
	PLIST_ACT_ST2,
	PLIST_ACT_ST3,
	PLIST_ACT_ST4,
	PLIST_ACT_ST5,
	PLIST_ACT_ST6,

	PLIST_ACT_ITEM1,
	PLIST_ACT_ITEM2,
	PLIST_ACT_ITEM3,
	PLIST_ACT_ITEM4,
	PLIST_ACT_ITEM5,
	PLIST_ACT_ITEM6,

	PLIST_ACT_CB1,
	PLIST_ACT_CB2,
	PLIST_ACT_CB3,
	PLIST_ACT_CB4,
	PLIST_ACT_CB5,
	PLIST_ACT_CB6,

	PLIST_ACT_BUTTON_EF,

	PLIST_ACT_MAX
};

enum {
	MENU_ROW = 0,		// mes_pokelist_05_01	ならびかえ
	MENU_STATUS,		// mes_pokelist_05_02	つよさをみる
	MENU_ITEM,			// mes_pokelist_05_03	もちもの
	MENU_ITEM_S,		// mes_pokelist_05_03	もちものメニュー：もたせる
	MENU_ITEM_G,		// mes_pokelist_05_03	もちものメニュー：あずかる
	MENU_MAIL,			// mes_pokelist_05_04	メール
	MENU_MAIL_R,		// mes_pokelist_05_05	メールを　よむ
	MENU_MAIL_G,		// mes_pokelist_05_06	メールを　とる
	MENU_AZUKERU,		// mes_pokelist_05_07	あずける
	MENU_CANCEL,		// mes_pokelist_05_08	やめる
	MENU_CHANGE,		// mes_pokelist_05_09	いれかえる
	MENU_BATTLE_IN,		// mes_pokelist_05_10	さんかする（戦闘参加選択）
	MENU_OUT,			// mes_pokelist_05_11	さんかしない
	MENU_CONTEST_IN,	// mes_pokelist_05_10	さんかする（コンテスト参加）
	MENU_KAPSEL_SET,	// mes_pokelist_05_22	セットする

	MENU_W_IAIGIRI,		// 技：いあいぎり
	MENU_W_SORAWOTOBU,	// 技：そらをとぶ
	MENU_W_NAMINORI,	// 技：なみのり
	MENU_W_KAIRIKI,		// 技：かいりき
	MENU_W_KIRIBARAI,	// 技：きりばらい
	MENU_W_IWAKUDAKI,	// 技：いわくだき
	MENU_W_TAKINOBORI,	// 技：たきのぼり
	MENU_W_ROCKCLIMB,	// 技：ロッククライム

	MENU_W_FLASH,		// 技：フラッシュ
	MENU_W_TELEPORT,	// 技：テレポート
	MENU_W_ANAWOHORU,	// 技：あなをほる
	MENU_W_AMAIKAORI,	// 技：あまいかおり
	MENU_W_OSYABERI,	// 技：おしゃべり
	MENU_W_MILKNOMI,	// 技：ミルクのみ
	MENU_W_TAMAGOUMI,	// 技：タマゴうみ

	MENU_STR_MAX = MENU_W_IAIGIRI+4
};


typedef int (*STRCV_FUNC)(void*);
typedef int (*YESNO_FUNC)(void*);

// はい・いいえワーク
typedef struct {
	YESNO_FUNC	yes;
	YESNO_FUNC	no;
}YESNO_WORK;


// ポケモンデータ
typedef struct {
	STRBUF * name;			// ニックネーム

	u16	mons;			// ポケモン番号
	u16	hp;				// HP
	u16	mhp;			// 最大HP
	u16	lv;				// レベル
	u16	item;			// アイテム番号
	u16	st:12;			// 状態異常
	u16	sex_put:1;		// 性別表示（ニドラン用）0=ON, 1=OFF
	u16	sex:2;			// 性別
	u16	contest:1;		// コンテストに参加できるか
	u8	egg;			// タマゴフラグ
	u8	form;			// フォルムNo
	u16	cb;				// カスタムボール

	s8	plate_px;
	s8	plate_py;

	s16	mons_px;
	s16	mons_py;

	s16	st_px;
	s16	st_py;

	s16	item_px;
	s16	item_py;

	CLACT_WORK_PTR	icon_cwp;
//	CLACT_WORK_PTR	item_cwp;
	u8	anm_cnt;
	u8	flg;
}PL_PANEL_DATA;

// ならびかえ用ワーク
typedef struct {
	u16	plate_bg[2][PL_PANEL_SX*PL_PANEL_SY];
	u16	str_bg[2][PL_PANEL_SX*PL_PANEL_SY];
	u8	pos[2];
	u8	mv[2];
	u8	flg;
	u8	seq;
	u8	cnt;
}MENU_NARABIKAE_WORK;

// ポケモンリストワーク
typedef struct {
	GF_BGL_INI * bgl;						// BGLデータ

	GF_BGL_BMPWIN	win[WIN_MAX];			// BMPウィンドウデータ（通常）
	GF_BGL_BMPWIN	add_win[ADD_WIN_MAX];	// BMPウィンドウデータ（追加）

	u16	plate_top[PL_PANEL_SX*PL_PANEL_SY];
	u16	plate_normal[PL_PANEL_SX*PL_PANEL_SY];
	u16	plate_none[PL_PANEL_SX*PL_PANEL_SY];

	u16	pal[16*8];							// パレット保存

	PLIST_DATA * dat;

	CATS_SYS_PTR	csp;
	CATS_RES_PTR	crp;
	CLACT_WORK_PTR	act_work[PLIST_ACT_MAX];
	CATS_ACT_PTR	cap[PLIST_ACT_MAX];

	NUMFONT * num_font;					// 8x8フォント
	MSGDATA_MANAGER * msg_man;			// メッセージデータマネージャ
	WORDSET * wset;						// 単語セット
	STRBUF * msg_buf;					// メッセージ展開領域
	STRBUF * str_buf;					// メッセージ展開領域
	STRBUF * menu_str[MENU_STR_MAX];	// メニュー文字列展開領域

	BMP_MENULIST_DATA * md;			// BMPメニューデータ
	BMPMENU_WORK * mw;				// BMPメニューワーク

	PL_PANEL_DATA	panel[6];

	const POINTER_WORK * mv_tbl;

	MENU_NARABIKAE_WORK	chg_wk;

//	TCB_PTR		vtask;
//	INTR_FUNC	vblank_func;

	STRCV_FUNC	strcv_func;

	YESNO_WORK	yesno;

	u8	sub_button_seq;	// サブボタンアニメシーケンス
	u8	sub_button_pos;	// サブボタンアニメ位置

	u8	next_seq;		// 次のシーケンス

	u8	chg_pos:6;
	u8	chg_flg:1;

	u8	cancel_flg:1;

	u8	msg_index;

	u8	pos;
	u8	old_pos;

	u8	lv_seq;			// レベルアップシーケンス
	u16	tmp[6];			// テンポラリワーク

	ZKN_HEIGHT_GRAM_PTR	zkn;	// 図鑑データ（レギュレーションで必要）

}PLIST_WORK;



//---------------------------------------------------------------------------------------------
/**
 * ポケモンがいるかチェック
 *
 * @param	wk		ポケモンリストワーク
 * @param	pos		位置
 *
 * @retval	"TRUE = いる"
 * @retval	"FALSE = いない"
 */
//---------------------------------------------------------------------------------------------
extern u8 PokeListDataCheck( PLIST_WORK * wk, u8 pos );

//---------------------------------------------------------------------------------------------
/**
 * ポケモンパラメータ取得
 *
 * @param	wk		ポケモンリストワーク
 *
 * @retval	"TRUE = いる"
 * @retval	"FALSE = いない"
 */
//---------------------------------------------------------------------------------------------
extern u8 PokeList_PanelPPDataMake( PLIST_WORK * wk, u8 pos );


extern void PokeListPanelPaletteSet( PLIST_WORK * wk, u8 num );

extern u8 PokeListSelCursorCheck( u8 type, u8 pos );

extern const u16 * PokeList_HPGageCharGet( PLIST_WORK * wk );

extern u8 PokeList_BattleInCheck( PLIST_WORK * wk, u8 num );

extern void PokeList_CursorMoveAuto( PLIST_WORK * wk, u8 mv_pos );


#endif	/* PLIST_SYS_H */
