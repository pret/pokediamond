
#include "pokeanime/p_anm_sys.h"


#define	PST_PAL_SYSFONT		( 15 )
#define	PST_PAL_TALKFONT	( 14 )
#define	PST_PAL_TALKWIN		( 13 )

#define	PST_CGX_TALKWIN		( 1024-TALK_WIN_CGX_SIZ )

#define	PST_LIKE_TASTE_NONE	( 5 )		// 好きな味なし
#define	PST_KEDUYA_MAX		( 255 )		// 毛艶最大値


// OBJ ID
enum {
	PST_OBJ_TAB_INFO = 0,
	PST_OBJ_TAB_MEMO,
	PST_OBJ_TAB_PARAM,
	PST_OBJ_TAB_CONDITION,
	PST_OBJ_TAB_B_SKILL,
	PST_OBJ_TAB_C_SKILL,
	PST_OBJ_TAB_RIBBON,
	PST_OBJ_TAB_RET,

	PST_OBJ_BALL,

	PST_OBJ_WAZACURSOR1,
	PST_OBJ_WAZACURSOR2,

	PST_OBJ_TYPE_POKE1,
	PST_OBJ_TYPE_POKE2,
	PST_OBJ_TYPE_WAZA1,
	PST_OBJ_TYPE_WAZA2,
	PST_OBJ_TYPE_WAZA3,
	PST_OBJ_TYPE_WAZA4,
	PST_OBJ_TYPE_WAZA5,
	PST_OBJ_TYPE_KIND,

	PST_OBJ_POKEICON,

	PST_OBJ_STIZYO,
	PST_OBJ_ARROW_L,
	PST_OBJ_ARROW_R,

	PST_OBJ_MARK1,
	PST_OBJ_MARK2,
	PST_OBJ_MARK3,
	PST_OBJ_MARK4,
	PST_OBJ_MARK5,
	PST_OBJ_MARK6,

	PST_OBJ_FLASH1,
	PST_OBJ_FLASH2,
	PST_OBJ_FLASH3,
	PST_OBJ_FLASH4,
	PST_OBJ_FLASH5,
	PST_OBJ_FLASH6,
	PST_OBJ_FLASH7,
	PST_OBJ_FLASH8,
	PST_OBJ_FLASH9,
	PST_OBJ_FLASH10,
	PST_OBJ_FLASH11,
	PST_OBJ_FLASH12,

	PST_OBJ_BUTTON_EF,

	PST_OBJ_UP1,
	PST_OBJ_UP2,
	PST_OBJ_UP3,
	PST_OBJ_UP4,
	PST_OBJ_UP5,

	PST_OBJ_A_BUTTON,

	PST_OBJ_EZC_STYLE,
	PST_OBJ_EZC_BEAUTIFUL,
	PST_OBJ_EZC_CUTE,
	PST_OBJ_EZC_CLEVER,
	PST_OBJ_EZC_STRONG,

	PST_OBJ_RARE_MARK,
	PST_OBJ_POKERUS_MARK,

	PST_OBJ_RIBBON01,
	PST_OBJ_RIBBON02,
	PST_OBJ_RIBBON03,
	PST_OBJ_RIBBON04,
	PST_OBJ_RIBBON05,
	PST_OBJ_RIBBON06,
	PST_OBJ_RIBBON07,
	PST_OBJ_RIBBON08,
	PST_OBJ_RIBBON09,
	PST_OBJ_RIBBON10,
	PST_OBJ_RIBBON11,
	PST_OBJ_RIBBON12,
	PST_OBJ_RIBBON_CUR,

	PST_OBJ_RIBBON_AU,
	PST_OBJ_RIBBON_AD,
	PST_OBJ_RIBBON_FLASH,
	PST_OBJ_CON_FLASH1,
	PST_OBJ_CON_FLASH2,
	PST_OBJ_CON_FLASH3,
	PST_OBJ_CON_FLASH4,
	PST_OBJ_CON_FLASH5,

	PST_OBJ_CON_POKERUS,

	PST_OBJ_MAX
};

// 基本文字列のBMPデータ
enum {
	WIN_P1_TITLE,		// 「ポケモンじょうほう」
	WIN_P2_TITLE,		// 「トレーナーメモ」
	WIN_P3_TITLE,		// 「ポケモンのうりょく」
	WIN_P4_TITLE,		// 「コンディション」
	WIN_P5_TITLE,		// 「たたかうわざ」
	WIN_P6_TITLE,		// 「コンテストわざ」
	WIN_MOTIMONO,		// 「もちもの」
	WIN_P1_ZUKANNO,		// 「ずかんNo.」
	WIN_P1_NAME,		// 「なまえ」
	WIN_P1_TYPE,		// 「タイプ」
	WIN_P1_OYA,			// 「おや」
	WIN_P1_IDNO,		// 「IDNo.」
	WIN_P1_NOWEXP,		// 「げんざいの　けいけんち」
	WIN_P1_NEXTLV,		// 「つぎのレベルまで」
	WIN_P1_ATO,			// 「あと」
	WIN_P3_HP,			// 「HP」
	WIN_P3_POW,			// 「こうげき」
	WIN_P3_DEF,			// 「ぼうぎょ」
	WIN_P3_SPP,			// 「とくこう」
	WIN_P3_SPD,			// 「とくぼう」
	WIN_P3_AGI,			// 「すばやさ」
	WIN_P3_SPA,			// 「とくせい」
	WIN_P4_KEDUYA,		// 「けづや」
	WIN_P4_SEIKAKU,		// 「せいかく」
	WIN_P5_MODORU,		// 「もどる」
	WIN_P5_BUNRUI,		// 「ぶんるい」
	WIN_P5_IRYOKU,		// 「いりょく
	WIN_P5_HIT,			// 「めいちゅう」
	WIN_P8_MODORIMASU,	// 「もどります」
	WIN_P6_AP_POINT,	// 「アピールポイント」
	WIN_P7_MOTTEIRU,	// 「もっているかず」
	WIN_P7_TITLE,		// 「きねんリボン」
	WIN_ITEMNAME,		// アイテム名
	WIN_LV,				// レベル
	WIN_NICKNAME,		// ニックネーム
	WIN_GUIDE,			// ガイドメッセージ
	WIN_MAX
};

// ページ１（ポケモン情報）
enum {
	ADD_WIN_P1_LIBNUM,	// 図鑑No.
	ADD_WIN_P1_NAME,	// 名前
	ADD_WIN_P1_OYANAME,	// 親名
	ADD_WIN_P1_IDNO,	// IDNo.
	ADD_WIN_P1_NOWEXP,	// 現在の経験値
	ADD_WIN_P1_NEXTEXP,	// 次のレベルまで@
	ADD_WIN_P1_MAX
};

// ページ２（トレーナーメモ）
enum {
	ADD_WIN_P2_TMEMO,	// トレーナーメモ
	ADD_WIN_P2_MAX
};

// ページ３（ポケモン能力）
enum {
	ADD_WIN_P3_HP,		// HP/MHP
	ADD_WIN_P3_POW,		// 攻撃
	ADD_WIN_P3_DEF,		// 防御
	ADD_WIN_P3_SPP,		// 特攻
	ADD_WIN_P3_SPD,		// 特防
	ADD_WIN_P3_AGI,		// 素早さ
	ADD_WIN_P3_SPANAME,	// 特性名
	ADD_WIN_P3_SPAINFO,	// 特性説明
	ADD_WIN_P3_MAX
};

// ページ５（戦う技）
enum {
	ADD_WIN_P5_WAZA1,		// 技名１
	ADD_WIN_P5_WAZA2,		// 技名２
	ADD_WIN_P5_WAZA3,		// 技名３
	ADD_WIN_P5_WAZA4,		// 技名４
	ADD_WIN_P5_WAZA5,		// 技名５
	ADD_WIN_P5_ATC,			// 威力
	ADD_WIN_P5_HIT,			// 命中
	ADD_WIN_P5_INFO,		// 技説明
	ADD_WIN_P5_MAX
};

// ページ６（コンテスト技）
enum {
	ADD_WIN_P6_WAZA1,	// 技名１
	ADD_WIN_P6_WAZA2,	// 技名２
	ADD_WIN_P6_WAZA3,	// 技名３
	ADD_WIN_P6_WAZA4,	// 技名４
	ADD_WIN_P6_WAZA5,	// 技名５
	ADD_WIN_P6_INFO,	// 技説明
	ADD_WIN_P6_MAX
};

// ページ７（記念リボン）
enum {
	ADD_WIN_P7_NUM,		// ???こ
	ADD_WIN_P7_MAXNUM,	// ???/???
	ADD_WIN_P7_NAME,	// リボン名
	ADD_WIN_P7_INFO,	// リボン説明
	ADD_WIN_P7_MAX
};


// ポルト関連のコンディションページ
enum {
	ADD_WIN_COND_KETTEI,	// 「けってい」
	ADD_WIN_COND_LIKE,		// 「すきなたべもの」
	ADD_WIN_COND_MSG,		// メッセージ
//	ADD_WIN_COND_MODORU,	// 「もどる」
	ADD_WIN_COND_MAX
};


typedef struct {
	GF_CAMERA_PTR	camera;		// カメラ

	void * ssm;					// ソフトウェアスプライトマネージャ
	SOFT_SPRITE_ANIME	ssanm[SS_ANM_SEQ_MAX];
	POKE_ANM_SYS_PTR	poke_anm_sys;
	SOFT_SPRITE	* ss;
	u32	flip;
}PST_3D_DATA;

typedef struct {
	STRBUF * monsname;		// ポケモン名
	STRBUF * nickname;		// ニックネーム
	STRBUF * oya;			// 親名

	u16	mons;				// ポケモン番号
	u16	item;				// アイテム番号

	u8	type1;				// タイプ１
	u8	type2;				// タイプ２
	u8	lv:7;				// レベル
	u8	sex_put:1;			// 性別表示（ニドラン用）0=ON, 1=OFF
	u8	sex:2;				// 性別
	u8	ball:6;				// 捕獲ボール

	u32	id;					// IDNo
	u32	now_exp;			// 現在の経験値
//	u32	next_exp;			// レベルアップまでの経験値
	u32	now_lv_exp;
	u32	next_lv_exp;

	u16	hp;					// HP
	u16	mhp;				// 最大HP

	u16	atc;				// 攻撃
	u16	def;				// 防御

	u16	spa;				// 特攻
	u16	spd;				// 特防

	u16	agi;				// 素早さ
	u8	tokusei;			// 特性
	u8	seikaku;			// 性格

	u16	waza[4];			// 技

	u8	wpp[4];				// 現在のPP

	u8	mpp[4];				// 最大PP

	u8	oya_sex;			// 親の性別
	u8	style;				// かっこよさ
	u8	beautiful;			// うつくしさ
	u8	cute;				// かわいさ
	u8	clever;				// かしこさ
	u8	strong;				// たくましさ
	u8	fur;				// 毛艶
	u8	like;				// 好きな味

	u16	mark;				// ボックスマーク
	u16	form;				// フォルムNo

	u32	st:28;				// 状態異常
	u32	tamago:1;			// タマゴフラグ
	u32	rare:1;				// レアフラグ
	u32	pokerus:2;			// ポケルス 0=感染なし, 1=感染している, 2=抗体あり

	u32	ribbon[4];			// リボン

}PST_POKEDATA;

typedef struct {
	VecFx16	lt;		// 左上
	VecFx16	rt;		// 右上
	VecFx16	lu;		// 左下
	VecFx16	ru;		// 右下
}PST_CONDISION_VTX;

typedef struct {
	GF_BGL_INI * bgl;						// BGLデータ

	GF_BGL_BMPWIN	def_win[WIN_MAX];	// BMPウィンドウデータ（通常）
	GF_BGL_BMPWIN * add_win;			// BMPウィンドウデータ（追加）
	u32	add_win_max;

	PSTATUS_DATA * dat;

	PST_POKEDATA	pp;		// ポケモンデータ

	PST_3D_DATA		p3d;	// 3Dデータ

	PST_CONDISION_VTX	cvtx[4];	// 表示座標
	PST_CONDISION_VTX	pvtx[4];	// プラス値
	PST_CONDISION_VTX	mvtx[4];	// 最大値
	u32	con_mv_cnt;

	CATS_SYS_PTR	csp;
	CATS_RES_PTR	crp;
	CLACT_WORK_PTR	awp[PST_OBJ_MAX];
	CATS_ACT_PTR	cap[PST_OBJ_MAX];

	NUMFONT * num_font;			// 8x8フォント
	MSGDATA_MANAGER * msg_man;	// メッセージデータマネージャ
	MSGDATA_MANAGER * rbn_man;	// メッセージデータマネージャ
	WORDSET * wset;				// 単語セット
	STRBUF * msg_buf;			// テンポラリメッセージバッファ
	STRBUF * player_name;		// 見ている人の名前展開場所

	MSGDATA_MANAGER * wman;		// 技名メッセージデータマネージャ

//	BOOL	wipe_flg;

	s8	page;		// 現在のページ
	u8	cur_pos:4;	// カーソル位置
	u8	sub_cur:4;	// カーソル位置（いれかえ位置）
	u8	sub_seq;	// サブシーケンス
	u8	sub_type:4;	// サブ画面のタイプ
	u8	sub_end:4;	// サブ画面ので「とじる」

	u8	flash_seq;
	u8	flash_max;
	u8	flash_pos;
	u8	flash_cnt;

	u8	btn_cnt;
	u8	btn_seq;
	u8	btn_pos;

	u8	ribbon_pos;		// リボンカーソル位置
	u8	ribbon_scr;		// リボンスクロールカウンタ
	u8	ribbon_max;		// リボン所持数
	u8	ribbon_num;		// カーソル位置のリボンID

}PST_WORK;




extern u8 PokeStatus_PageCheck( PST_WORK * wk, u32 pos );

extern u8 PokeStatus_PageNumGet( PST_WORK * wk );

extern void * PokeStatusPokeParamGet( PST_WORK * wk );

extern u8 PokeStatus_RibbonPosIDGet( PST_WORK * wk, u8 cur_pos );





