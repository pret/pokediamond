//==============================================================================
/**
 * @file	we_def.h
 * @brief	技エフェクトマクロ定義
 * @author	goto
 * @date	2005.11.18
 *
 * ここに色々な解説等を書いてもよい
 *
 */
//==============================================================================

#ifndef	_WE_DEF_H_
#define _WE_DEF_H_


#define	WT_BF_WINDOW		(0)
#define	WT_BF_EFFECT		(1)
#define	WT_BF_BACKGROUND	(2)
#define	WT_BF_3DFRAME		(3)
#define	WT_BF_NONE			(0xFF)

// ※ xxx.s でも参照するので enum 禁止
#define EFF_ARC_ID_BASE		(5000)				///< アークIDが被らないように
#define BALL_ARC_ID_BASE	(6000)				///< アークIDが被らないように
#define OAM_DROP_ID			(55555)

#define WP_DEF_CENTER_X		(0)
#define WP_DEF_CENTER_Y		(3200)
#define WP_DEF_CENTER_Z		(0)

#define WP_AXIS_DEF_X		(3176)				///< 基本方向軸
#define WP_AXIS_DEF_Y		(1960)
#define WP_AXIS_DEF_Z		(-296)
#define WP_REVERCE_DEF_FLG	(0)
/*
	{ WP_AXIS_DEF_X, WP_AXIS_DEF_Y, WP_AXIS_DEF_Z, OPERATOR_EX_REVERCE_ON, },
	{ 3232, 1600, 1568, OPERATOR_EX_REVERCE_ON, },
	{ 5984, 2496, 6208, OPERATOR_EX_REVERCE_ON, }, A
	{ 2688, 1408, 1536, OPERATOR_EX_REVERCE_ON, }, B
	{ -896,  384,  800, OPERATOR_EX_REVERCE_ON, }, C
	{ 2336, 1440,  736, OPERATOR_EX_REVERCE_ON, }, D
	{ 1888, 1856, 1760, OPERATOR_EX_REVERCE_ON, },
	
	方向 = (5984, 2496, 3064)
*/
#define WP_POS_REVERSE_NONE	(0)					/// EX_DATA の拡張
#define WP_POS_REVERSE_X	(1)
#define WP_POS_REVERSE_Y	(2)
#define WP_POS_REVERSE_Z	(3)
#define WP_POS_REVERSE_XY	(4)
#define WP_POS_REVERSE_XZ	(5)
#define WP_POS_REVERSE_YZ	(6)
#define WP_POS_REVERSE_ALL	(7)

#define WE_CAMERA_TYPE_PERSPECTIV	(0)			///< 透視射影
#define WE_CAMERA_TYPE_ORTHO		(1)			///< 正射影

#define WE_MASK_ALL (GX_WND_PLANEMASK_BG0 | GX_WND_PLANEMASK_BG1 | \
					 GX_WND_PLANEMASK_BG2 | GX_WND_PLANEMASK_BG3 | GX_WND_PLANEMASK_OBJ)
// -----------------------------------------
//
//	□wsp_steff.cで扱う共通定義みたいな
//
// -----------------------------------------
#define STEFF_GRA_UP		(0)
#define STEFF_GRA_DOWN		(1)
#define STEFF_GRA_RECOVER	(2)
#define STEFF_GRA_METAL		(3)

// -----------------------------------------
//
//	□.sで扱う共通定義みたいな
//
// -----------------------------------------
#define WE_MOVE_X_VAL_DEF	(24)

#define SHAKE_S_X			(1)
#define SHAKE_S_Y			(1)
#define SHAKE_S_WAIT		(1)
#define SHAKE_S_NUM			(2)

#define SHAKE_M_X			(2)
#define SHAKE_M_Y			(2)
#define SHAKE_M_WAIT		(1)
#define SHAKE_M_NUM			(2)

#define SHAKE_B_X			(4)
#define SHAKE_B_Y			(4)
#define SHAKE_B_WAIT		(1)
#define SHAKE_B_NUM			(2)

#define SHAKE_NUM_LONG		(4)
#define SHAKE_NUM_LONG2		(8)

#define DISP_OUT_FRAME		(20)

// -----------------------------------------
//
//	カラーフェード用
//
// -----------------------------------------
#define WEDEF_BACKGROUND_PAL	(0xFF)
#define WEDEF_COLOR_WHITE		(0x7FFF)
#define WEDEF_COLOR_BLACK		(0x0000)
#define WEDEF_FADE_PARAM		(10)

#define WE_PAL_WHITE		(WEDEF_COLOR_WHITE)
#define WE_PAL_BLACK		(WEDEF_COLOR_BLACK)
#define WE_PAL_BLUE			(0xc30a)
#define WE_PAL_BLUE_2		(0x7fd0)
#define WE_PAL_YELLOW		(0x33ff)
#define WE_PAL_YELLOW_2		(0x031D)
#define WE_PAL_GREEN		(0x2BF4)
#define WE_PAL_GREEN_2		(0x03EB)
#define WE_PAL_PINK			(0x5A9F)
#define WE_PAL_POISON		(0x7C14)
#define WE_PAL_GRAY			(0x35ad)
#define WE_PAL_GRAY_2		(0x18c6)
#define WE_PAL_RED			(0x001F)
#define WE_PAL_BROWN		(0x10e8)
#define WE_PAL_RED_BROWN	(0x084c)
#define WE_PAL_ORANGE		(0x3aff)
#define WE_PAL_ICE_BLUE		(0x7f77)

// -----------------------------------------
//
//	よく使うものをまとめるときに、対象を指定する用
//
// -----------------------------------------
#define WE_POKE_DATA_MAX	(4)								///< ポケモン最大4匹

#define WE_TOOL_C0			(0x0002)						///< CAP-ID_0
#define WE_TOOL_C1			(0x0004)						///< CAP-ID_1
#define WE_TOOL_C2			(0x0008)						///< CAP-ID_2
#define WE_TOOL_C3			(0x0010)						///< CAP-ID_3
#define WE_TOOL_M1			(0x0002)						///< 攻撃ポケモン
#define WE_TOOL_M2			(0x0004)						///< 攻撃ポケモンの相方
#define WE_TOOL_E1			(0x0008)						///< 対象ポケモン
#define WE_TOOL_E2			(0x0010)						///< 対象ポケモンの相方
#define WE_TOOL_OTHER		(0x0020)						///< 自分以外
#define WE_TOOL_STAGE		(0x0040)						///< すべて
#define WE_TOOL_TMS			(WE_TOOL_M1 | WE_TOOL_M2)		///< 攻撃ポケモン側
#define WE_TOOL_TES			(WE_TOOL_E1 | WE_TOOL_E2)		///< 対象ポケモン側
#define WE_TOOL_TALL		(WE_TOOL_TMS | WE_TOOL_TES)		///< すべて

#define WE_TOOL_SSP			(0x0100)						///< SSPに対して
#define WE_TOOL_CAP			(0x0200)						///< CAPに対して
#define WE_TOOL_BG			(0x0400)						///< BGに対して
#define WE_TOOL_NOT_DF		(0x0800)						///< DFと一致しないものだけ

#define WE_TOOL_A			(WE_TOOL_M1 | WE_TOOL_NOT_DF)	///< 攻撃ポケモン
#define WE_TOOL_C			(WE_TOOL_M2 | WE_TOOL_NOT_DF)	///< 攻撃ポケモンの相方
#define WE_TOOL_B			(WE_TOOL_E1 | WE_TOOL_NOT_DF)	///< 対象ポケモン
#define WE_TOOL_D			(WE_TOOL_E2 | WE_TOOL_NOT_DF)	///< 対象ポケモンの相方

#define WE_HENSIN_DF		(0)
#define WE_HENSIN_AT		(1)
#define WE_HENSIN_MIGAWARI	(2)
#define WE_HENSIN_YOKODORI	(3)


// -----------------------------------------
//
//	背景切り替え用
//
// -----------------------------------------
#define WEDEF_HAIKEI_SHIFT		(16)						///< shift用
#define WEDEF_BIT(n)			(n << 1)
#define WEDEF_BIT_SHIFT(n)		(n >> 1)
#define WEDEF_HAIKEI_SBIT(n)	(WEDEF_BIT(n) << WEDEF_HAIKEI_SHIFT)
#define WEDEF_HAIKEI_SBIT_SHIFT(n)	(WEDEF_BIT_SHIFT(n) >> WEDEF_HAIKEI_SHIFT)


// -----------------------------------------
//
//	□ 切り替え背景ID
//
// -----------------------------------------
#define BG_ID_025	(0)
#define BG_ID_223	(1)
#define BG_ID_224	(2)
#define BG_ID_276	(3)
#define BG_ID_354	(4)
#define BG_ID_416	(5)
#define BG_ID_038	(6)
#define BG_ID_438	(7)
#define BG_ID_452	(8)
#define BG_ID_056	(9)
#define BG_ID_296	(10)
#define BG_ID_396	(11)
#define BG_ID_411	(12)
#define BG_ID_441	(13)
#define BG_ID_063	(14)
#define BG_ID_076	(15)
#define BG_ID_413	(16)
#define BG_ID_308	(17)
#define BG_ID_143	(18)
#define BG_ID_087	(19)
#define BG_ID_093	(20)
#define BG_ID_120	(21)
#define BG_ID_126	(22)
#define BG_ID_127	(23)
#define BG_ID_171	(24)
#define BG_ID_177	(25)
#define BG_ID_192	(26)
#define BG_ID_344	(27)
#define BG_ID_200	(28)
#define BG_ID_221	(29)
#define BG_ID_307	(30)
#define BG_ID_264	(31)
#define BG_ID_315	(32)
#define BG_ID_394	(33)
#define BG_ID_338	(34)
#define BG_ID_352	(35)
#define BG_ID_370	(36)
#define BG_ID_434	(37)
#define BG_ID_437	(38)
#define BG_ID_439	(39)
#define BG_ID_457	(40)
#define BG_ID_460	(41)
#define BG_ID_461	(42)
#define BG_ID_463	(43)
#define BG_ID_464	(44)
#define BG_ID_465	(45)
#define BG_ID_467	(46)
#define BG_ID_097	(47)
#define BG_ID_057	(48)
#define BG_ID_330	(49)
#define BG_ID_059	(50)
#define BG_ID_069	(51)
#define BG_ID_094	(52)
#define BG_ID_090	(53)
#define BG_ID_236	(54)
#define BG_ID_327	(55)
#define BG_ID_322	(56)
#define BG_ID_433	(57)

#define BG_ID_019	( BG_ID_327 )

// 古い定義 ※ 使用禁止 ※
#define WEDEF_HAIKEI_000		(0)							///< 流線
#define WEDEF_HAIKEI_001		(1)							///< 波のり
#define WEDEF_HAIKEI_002		(2)							///< ふぶき
#define WEDEF_HAIKEI_003		(3)							///< 地球投げ
#define WEDEF_HAIKEI_004		(4)							///< サイコ
#define WEDEF_HAIKEI_005		(5)							///< 地割れ
#define WEDEF_HAIKEI_006		(6)							///< 月

// 新しい定義
#define WEDEF_HAIKEI_STREAM		(0)							///< 流線
#define WEDEF_HAIKEI_SURFIN		(1)							///< 波のり
#define WEDEF_HAIKEI_BLIZZARD	(2)							///< ふぶき
#define WEDEF_HAIKEI_EARTH		(3)							///< 地球投げ
#define WEDEF_HAIKEI_PSY		(4)							///< サイコ
#define WEDEF_HAIKEI_CRACK		(5)							///< 地割れ
#define WEDEF_HAIKEI_MOON		(6)							///< 月			236
#define WEDEF_HAIKEI_BLUESKY	(7)							///< そら		288
#define WEDEF_HAIKEI_COSMOS		(8)							///< 宇宙		322
#define WEDEF_HAIKEI_WIREROOM	(9)							///< ワイヤー	433
#define WEDEF_HAIKEI_434		(10)	// o
#define WEDEF_HAIKEI_344		(11)
#define WEDEF_HAIKEI_370		(12)
#define WEDEF_HAIKEI_338		(13)
#define WEDEF_HAIKEI_192		(14)	// o
#define WEDEF_HAIKEI_200		(15)
#define WEDEF_HAIKEI_126		(16)	// o
#define WEDEF_HAIKEI_177		(17)
#define WEDEF_HAIKEI_120		(18)	// o
#define WEDEF_HAIKEI_025		(19)	// o
#define WEDEF_HAIKEI_038		(20)	// o
#define WEDEF_HAIKEI_063		(21)	///< 
#define WEDEF_HAIKEI_087		(22)	///< 
#define WEDEF_HAIKEI_352		(23)	///< 
#define WEDEF_HAIKEI_330		(24)	///< 
#define WEDEF_HAIKEI_416		(25)	///< ギガインパクト
#define WEDEF_HAIKEI_438		(26)	///< パワーウィップ
#define WEDEF_HAIKEI_452		(27)	///< ウッドハンマー
#define WEDEF_HAIKEI_076		(28)	///< ソーラービーム
#define WEDEF_HAIKEI_143		(29)	///< ゴッドバード
#define WEDEF_HAIKEI_308		(30)	///< ハイドロカノン
#define WEDEF_HAIKEI_413		(31)	///< ブレイブバード
#define WEDEF_HAIKEI_264		(32)	///< きあいパンチとか
#define WEDEF_HAIKEI_171		(33)	///< あくむ
#define WEDEF_HAIKEI_093		(34)	///< ねんりき
#define WEDEF_HAIKEI_127		(35)	///< たきのぼり
#define WEDEF_HAIKEI_056		(36)	///< ハイドロポンプ
#define WEDEF_HAIKEI_296		(37)	///< ミストボール
#define WEDEF_HAIKEI_396		(38)	///< はどうだん
#define WEDEF_HAIKEI_411		(39)	///< きあいだま
#define WEDEF_HAIKEI_441		(40)	///< ダストシュート
#define WEDEF_HAIKEI_437		(41)	///< リーフストーム
#define WEDEF_HAIKEI_439		(42)	///< がんせきほう
#define WEDEF_HAIKEI_457		(43)	///< もろはのずつき
#define WEDEF_HAIKEI_460		(44)	///< バーストエコー
#define WEDEF_HAIKEI_461		(45)	///< みかづきのまい
#define WEDEF_HAIKEI_463		(46)	///< マグマストーム
#define WEDEF_HAIKEI_464		(47)	///< ダークホール
#define WEDEF_HAIKEI_465		(48)	///< シードフレア
#define WEDEF_HAIKEI_467		(49)	///< シャドーダイブ
#define WEDEF_HAIKEI_AAA		(41)	///< 
#define WEDEF_HAIKEI_BBB		(41)	///< 
#define WEDEF_HAIKEI_CCC		(41)	///< 
#define WEDEF_HAIKEI_DDD		(41)	///< 



// -----------------------------------------
//
//	□ 切り替え動作モード		(下位16bit)
//
// -----------------------------------------
#define WEDEF_HAIKEI_MODE_BLEND		(0)						///< ブレンド
#define WEDEF_HAIKEI_MODE_FADE		(1)						///< フェード
#define WEDEF_HAIKEI_MODE_NONE		(2)						///< なし
#define WEDEF_HAIKEI_MODE_END		(3)						///< END定義 増えたら更新！

#define WEDEF_HAIKEI_RC_MODE_BLEND	(0)						///< 復帰ブレンド
#define WEDEF_HAIKEI_RC_MODE_FADE	(1)						///< 復帰フェード
#define WEDEF_HAIKEI_RC_MODE_NONE	(2)						///< なし


// -----------------------------------------
//
//	□ 切り替え時のサブシステム	(上位16bit)
//
//	[ I/O ] 開始・復帰どちらでも指定可能
//	[  I  ] 開始用
//	[  O  ] 終了用
//
//	[  I  ] と [  O  ] の混在は動作保障なし
//
//
//	WORK_SET と組み合わせて使用
//	index	値の意味
//	  0		Xスピード
//	  1		Yスピード
//	  6		敵味方でスピード反転するか 			する 	!= 0
//	  7		敵味方でスクリーンが切り替わるか	変わる	!= 0
//
// -----------------------------------------
#define WEDEF_HAIKEI_SBIT_MAX			(7)						///< 上位Bitの最大数

#define WEDEF_HAIKEI_SBIT_NONE			(0x0000)<<WEDEF_HAIKEI_SHIFT	///< [ I/O ] 何もなし
#define WEDEF_HAIKEI_SBIT_MOVE			(0x0002)<<WEDEF_HAIKEI_SHIFT	///< [  I  ] 背景が動く
#define WEDEF_HAIKEI_SBIT_STOP			(0x0004)<<WEDEF_HAIKEI_SHIFT	///< [  O  ] 背景が止まる
#define WEDEF_HAIKEI_SBIT_EXIT			(0x0008)<<WEDEF_HAIKEI_SHIFT	///< [  O  ] サブシステムの停止
#define WEDEF_HAIKEI_SBIT_NONE_DROP		(0x0010)<<WEDEF_HAIKEI_SHIFT	///< [ I/0 ] ドロップなし
#define WEDEF_HAIKEI_SBIT_LASTER		(0x0020)<<WEDEF_HAIKEI_SHIFT	///< [  I  ] ラスター
#define WEDEF_HAIKEI_SBIT_LASTER_STOP	(0x0040)<<WEDEF_HAIKEI_SHIFT	///< [  0  ] ラスター停止

///< 特殊スクロール
#define WEDEF_HAIKEI_SBIT_DEF_BG_MOVE	(0x0080)<<WEDEF_HAIKEI_SHIFT	///< [  I  ] 背景先行スクロール

#define WEDEF_HAIKEI_SBIT_END	WEDEF_HAIKEI_SBIT(WEDEF_HAIKEI_SBIT_MAX)///< END定義

///< 値変更用index
#define WEDEF_GP_INDEX_SPEED_X		(0)
#define WEDEF_GP_INDEX_SPEED_Y		(1)
#define WEDEF_GP_INDEX_BGPOS_X		(2)
#define WEDEF_GP_INDEX_BGPOS_Y		(3)
#define WEDEF_GP_INDEX_FADE_TYPE	(4)
#define WEDEF_GP_INDEX_FADE_VALUE	(5)
#define WEDEF_GP_INDEX_SPEED_R		(6)
#define WEDEF_GP_INDEX_SCREEN_R		(7)		///< 0 = 無し 1 = 攻撃対象 2 = 自分

// --------------------
// デフォスクロールパラメーター
// --------------------
#define WEDEF_HAIKEI_HI_SPEED_X		(-64)	/// +64
#define WEDEF_HAIKEI_SPEED_X		(-32)	/// +32
#define WEDEF_HAIKEI_SPEED_Y		(0)
#define WEDEF_HAIKEI_BGPOS_X		(0)
#define WEDEF_HAIKEI_BGPOS_Y		(0)

#define WEDEF_NAMINORI_SPEED_X		(+12)
#define WEDEF_NAMINORI_SPEED_Y		(+12)
#define WEDEF_NAMINORI_BGPOS_X		(0)
#define WEDEF_NAMINORI_BGPOS_Y		(256)

// -----------------------------------------
//
//	OAM用の定義
//
// -----------------------------------------
#define WEDEF_OAM_CAP_ID_0	(0)				///< OAMのCAP-ID
#define WEDEF_OAM_CAP_ID_1	(1)
#define WEDEF_OAM_CAP_ID_2	(2)
#define WEDEF_OAM_CAP_ID_3	(3)
#define WEDEF_OAM_CAP_ID_4	(4)
#define WEDEF_OAM_CAP_ID_5	(5)
#define WEDEF_OAM_CAP_ID_6	(6)
#define WEDEF_OAM_CAP_ID_7	(7)
#define WEDEF_OAM_CAP_ID_8	(8)
#define WEDEF_OAM_CAP_ID_9	(9)

// -----------------------------------------
//
//	ポケモンOAMドロップなどに利用
//
// -----------------------------------------

#define WEDEF_DROP_M1		(0)				///< 攻撃ポケモン
#define WEDEF_DROP_E1		(1)				///< 対象ポケモン
#define WEDEF_DROP_M2		(2)				///< 攻撃ポケモンの相方
#define WEDEF_DROP_E2		(3)				///< 対象ポケモンの相方
#define WEDEF_DROP_A		(4)
#define WEDEF_DROP_B		(5)
#define WEDEF_DROP_C		(6)
#define WEDEF_DROP_D		(7)

#define WEDEF_POKE_RES_0	(0)				///< 使用ポケモンリソース番号
#define WEDEF_POKE_RES_1	(1)
#define WEDEF_POKE_RES_2	(2)
#define WEDEF_POKE_RES_3	(3)
#define WEDEF_POKE_RES_EX	(4)

#define WEDEF_POKE_AUTO_ON	(1)				///< スプライトを追従する
#define WEDEF_POKE_AUTO_OFF	(0)

#define WEDEF_POKE_CAP_ID_0	(0)				///< ポケモンのCAP-ID
#define WEDEF_POKE_CAP_ID_1	(1)
#define WEDEF_POKE_CAP_ID_2	(2)
#define WEDEF_POKE_CAP_ID_3	(3)
#define WEDEF_POKE_CAP_ID_EX	(4)

#define WEDEF_AM_STOP_CAP_0	(0)				///< 自動追尾をONにしたCAP-IDフラグ
#define WEDEF_AM_STOP_CAP_1	(1)
#define WEDEF_AM_STOP_CAP_2	(2)
#define WEDEF_AM_STOP_CAP_3	(3)
#define WEDEF_AM_STOP_BG	(4)				///< BGの自動追尾停止フラグ
#define WEDEF_AUTO_MOVE_MAX	(5)

#define WEDEF_BG_POKE_COL_POS	(BATTLE_PAL_EFF_0*16)		///< ポケモンのパレット
#define WEDEF_BG_DATA_COL_POS	(BATTLE_PAL_EFF_1*16)		///< 背景のパレット

// -----------------------------------------
//
//	□ LCD座標 と パーティクル用のLCD座標
//
// -----------------------------------------

///< パーティクル用の LCD サイズ
///< x = 44032 y = 33024
#define PT_LCD_L		(-22016)				///< left
#define PT_LCD_R		(+22016)				///< right
#define PT_LCD_T		(+16512)				///< top
#define PT_LCD_B		(-16512)				///< buttom
#define PT_LCD_DOT		(172)					///< 1dot あたり 1pt pos

#define PT_LCD_PTP_CHG(x)	(x * PT_LCD_DOT)	///< 1ドットをおよそパーティクル座標に直す

#endif

