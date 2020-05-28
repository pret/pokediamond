//============================================================================================
/**
 * @file	vs_demo_def.h
 * @brief	通信対戦デモ　定数定義
 * @author	Hiroyuki Nakamura
 * @date	06.04.26
 */
//============================================================================================
// 確認画面：パレット使用定義
enum {
	PAL_FONT = 0,		// フォント
	PAL_PANEL_0 = 3,	// プレート１
	PAL_PANEL_1,		// プレート２
	PAL_PANEL_2,		// プレート３
	PAL_PANEL_3,		// プレート４
	PAL_PANEL_4,		// プレート５
	PAL_PANEL_5,		// プレート６
};

// BMPウィンドウ定義
// ニックネーム：１体目
#define	WIN_NAME1_PX	( 6 )
#define	WIN_NAME1_PY	( 1 )
#define	WIN_NAME1_SX	( 9 )
#define	WIN_NAME1_SY	( 2 )
#define	WIN_NAME1_PAL	( PAL_FONT )
#define	WIN_NAME1_CGX	( 1 )
// レベル：１体目
#define	WIN_LV1_PX		( 1 )
#define	WIN_LV1_PY		( 4 )
#define	WIN_LV1_SX		( 5 )
#define	WIN_LV1_SY		( 2 )
#define	WIN_LV1_PAL		( PAL_FONT )
#define	WIN_LV1_CGX		( WIN_NAME1_CGX + WIN_NAME1_SX * WIN_NAME1_SY )
// HP/MHP：１体目
#define	WIN_HP1_PX		( 7 )
#define	WIN_HP1_PY		( 4 )
#define	WIN_HP1_SX		( 8 )
#define	WIN_HP1_SY		( 2 )
#define	WIN_HP1_PAL		( PAL_FONT )
#define	WIN_HP1_CGX		( WIN_LV1_CGX + WIN_LV1_SX * WIN_LV1_SY )
// HPゲージ：１体目
#define	WIN_HPBAR1_PX	( 8 )
#define	WIN_HPBAR1_PY	( 3 )
#define	WIN_HPBAR1_SX	( 6 )
#define	WIN_HPBAR1_SY	( 1 )
#define	WIN_HPBAR1_PAL	( PAL_PANEL_0 )
#define	WIN_HPBAR1_CGX	( WIN_HP1_CGX + WIN_HP1_SX * WIN_HP1_SY )

// ニックネーム：２体目
#define	WIN_NAME2_PX	( 6 )
#define	WIN_NAME2_PY	( 7 )
#define	WIN_NAME2_SX	( 9 )
#define	WIN_NAME2_SY	( 2 )
#define	WIN_NAME2_PAL	( PAL_FONT )
#define	WIN_NAME2_CGX	( WIN_HPBAR1_CGX + WIN_HPBAR1_SX * WIN_HPBAR1_SY )
// レベル：２体目
#define	WIN_LV2_PX		( 1 )
#define	WIN_LV2_PY		( 10 )
#define	WIN_LV2_SX		( 5 )
#define	WIN_LV2_SY		( 2 )
#define	WIN_LV2_PAL		( PAL_FONT )
#define	WIN_LV2_CGX		( WIN_NAME2_CGX + WIN_NAME2_SX * WIN_NAME2_SY )
// HP/MHP：２体目
#define	WIN_HP2_PX		( 7 )
#define	WIN_HP2_PY		( 10 )
#define	WIN_HP2_SX		( 8 )
#define	WIN_HP2_SY		( 2 )
#define	WIN_HP2_PAL		( PAL_FONT )
#define	WIN_HP2_CGX		( WIN_LV2_CGX + WIN_LV2_SX * WIN_LV2_SY )
// HPゲージ：２体目
#define	WIN_HPBAR2_PX	( 8 )
#define	WIN_HPBAR2_PY	( 9 )
#define	WIN_HPBAR2_SX	( 6 )
#define	WIN_HPBAR2_SY	( 1 )
#define	WIN_HPBAR2_PAL	( PAL_PANEL_1 )
#define	WIN_HPBAR2_CGX	( WIN_HP2_CGX + WIN_HP2_SX * WIN_HP2_SY )

// ニックネーム：３体目
#define	WIN_NAME3_PX	( 6 )
#define	WIN_NAME3_PY	( 13 )
#define	WIN_NAME3_SX	( 9 )
#define	WIN_NAME3_SY	( 2 )
#define	WIN_NAME3_PAL	( PAL_FONT )
#define	WIN_NAME3_CGX	( WIN_HPBAR2_CGX + WIN_HPBAR2_SX * WIN_HPBAR2_SY )
// レベル：３体目
#define	WIN_LV3_PX		( 1 )
#define	WIN_LV3_PY		( 16 )
#define	WIN_LV3_SX		( 5 )
#define	WIN_LV3_SY		( 2 )
#define	WIN_LV3_PAL		( PAL_FONT )
#define	WIN_LV3_CGX		( WIN_NAME3_CGX + WIN_NAME3_SX * WIN_NAME3_SY )
// HP/MHP：３体目
#define	WIN_HP3_PX		( 7 )
#define	WIN_HP3_PY		( 16 )
#define	WIN_HP3_SX		( 8 )
#define	WIN_HP3_SY		( 2 )
#define	WIN_HP3_PAL		( PAL_FONT )
#define	WIN_HP3_CGX		( WIN_LV3_CGX + WIN_LV3_SX * WIN_LV3_SY )
// HPゲージ：３体目
#define	WIN_HPBAR3_PX	( 8 )
#define	WIN_HPBAR3_PY	( 15 )
#define	WIN_HPBAR3_SX	( 6 )
#define	WIN_HPBAR3_SY	( 1 )
#define	WIN_HPBAR3_PAL	( PAL_PANEL_2 )
#define	WIN_HPBAR3_CGX	( WIN_HP3_CGX + WIN_HP3_SX * WIN_HP3_SY )

// ニックネーム：４体目
#define	WIN_NAME4_PX	( 22 )
#define	WIN_NAME4_PY	( 2 )
#define	WIN_NAME4_SX	( 9 )
#define	WIN_NAME4_SY	( 2 )
#define	WIN_NAME4_PAL	( PAL_FONT )
#define	WIN_NAME4_CGX	( WIN_HPBAR3_CGX + WIN_HPBAR3_SX * WIN_HPBAR3_SY )
// レベル：４体目
#define	WIN_LV4_PX		( 17 )
#define	WIN_LV4_PY		( 5 )
#define	WIN_LV4_SX		( 5 )
#define	WIN_LV4_SY		( 2 )
#define	WIN_LV4_PAL		( PAL_FONT )
#define	WIN_LV4_CGX		( WIN_NAME4_CGX + WIN_NAME4_SX * WIN_NAME4_SY )
// HP/MHP：４体目
#define	WIN_HP4_PX		( 23 )
#define	WIN_HP4_PY		( 5 )
#define	WIN_HP4_SX		( 8 )
#define	WIN_HP4_SY		( 2 )
#define	WIN_HP4_PAL		( PAL_FONT )
#define	WIN_HP4_CGX		( WIN_LV4_CGX + WIN_LV4_SX * WIN_LV4_SY )
// HPゲージ：４体目
#define	WIN_HPBAR4_PX	( 24 )
#define	WIN_HPBAR4_PY	( 4 )
#define	WIN_HPBAR4_SX	( 6 )
#define	WIN_HPBAR4_SY	( 1 )
#define	WIN_HPBAR4_PAL	( PAL_PANEL_3 )
#define	WIN_HPBAR4_CGX	( WIN_HP4_CGX + WIN_HP4_SX * WIN_HP4_SY )

// ニックネーム：５体目
#define	WIN_NAME5_PX	( 22 )
#define	WIN_NAME5_PY	( 8 )
#define	WIN_NAME5_SX	( 9 )
#define	WIN_NAME5_SY	( 2 )
#define	WIN_NAME5_PAL	( PAL_FONT )
#define	WIN_NAME5_CGX	( WIN_HPBAR4_CGX + WIN_HPBAR4_SX * WIN_HPBAR4_SY )
// レベル：５体目
#define	WIN_LV5_PX		( 17 )
#define	WIN_LV5_PY		( 11 )
#define	WIN_LV5_SX		( 5 )
#define	WIN_LV5_SY		( 2 )
#define	WIN_LV5_PAL		( PAL_FONT )
#define	WIN_LV5_CGX		( WIN_NAME5_CGX + WIN_NAME5_SX * WIN_NAME5_SY )
// HP/MHP：５体目
#define	WIN_HP5_PX		( 23 )
#define	WIN_HP5_PY		( 11 )
#define	WIN_HP5_SX		( 8 )
#define	WIN_HP5_SY		( 2 )
#define	WIN_HP5_PAL		( PAL_FONT )
#define	WIN_HP5_CGX		( WIN_LV5_CGX + WIN_LV5_SX * WIN_LV5_SY )
// HPゲージ：５体目
#define	WIN_HPBAR5_PX	( 24 )
#define	WIN_HPBAR5_PY	( 10 )
#define	WIN_HPBAR5_SX	( 6 )
#define	WIN_HPBAR5_SY	( 1 )
#define	WIN_HPBAR5_PAL	( PAL_PANEL_4 )
#define	WIN_HPBAR5_CGX	( WIN_HP5_CGX + WIN_HP5_SX * WIN_HP5_SY )

// ニックネーム：６体目
#define	WIN_NAME6_PX	( 22 )
#define	WIN_NAME6_PY	( 14 )
#define	WIN_NAME6_SX	( 9 )
#define	WIN_NAME6_SY	( 2 )
#define	WIN_NAME6_PAL	( PAL_FONT )
#define	WIN_NAME6_CGX	( WIN_HPBAR5_CGX + WIN_HPBAR5_SX * WIN_HPBAR5_SY )
// レベル：６体目
#define	WIN_LV6_PX		( 17 )
#define	WIN_LV6_PY		( 17 )
#define	WIN_LV6_SX		( 5 )
#define	WIN_LV6_SY		( 2 )
#define	WIN_LV6_PAL		( PAL_FONT )
#define	WIN_LV6_CGX		( WIN_NAME6_CGX + WIN_NAME6_SX * WIN_NAME6_SY )
// HP/MHP：６体目
#define	WIN_HP6_PX		( 23 )
#define	WIN_HP6_PY		( 17 )
#define	WIN_HP6_SX		( 8 )
#define	WIN_HP6_SY		( 2 )
#define	WIN_HP6_PAL		( PAL_FONT )
#define	WIN_HP6_CGX		( WIN_LV6_CGX + WIN_LV6_SX * WIN_LV6_SY )
// HPゲージ：６体目
#define	WIN_HPBAR6_PX	( 24 )
#define	WIN_HPBAR6_PY	( 16 )
#define	WIN_HPBAR6_SX	( 6 )
#define	WIN_HPBAR6_SY	( 1 )
#define	WIN_HPBAR6_PAL	( PAL_PANEL_5 )
#define	WIN_HPBAR6_CGX	( WIN_HP6_CGX + WIN_HP6_SX * WIN_HP6_SY )

// BMPウィンドウID
enum {
	// １体目のポケモン
	WIN_NAME1 = 0,	// 名前
	WIN_LV1,		// Lv
	WIN_HP1,		// HP/MHP
	WIN_HPBAR1,		// HPバー
	// ２体目のポケモン
	WIN_NAME2,		// 名前
	WIN_LV2,		// Lv
	WIN_HP2,		// HP/MHP
	WIN_HPBAR2,		// HPバー
	// ３体目のポケモン
	WIN_NAME3,		// 名前
	WIN_LV3,		// Lv
	WIN_HP3,		// HP/MHP
	WIN_HPBAR3,		// HPバー
	// ４体目のポケモン
	WIN_NAME4,		// 名前
	WIN_LV4,		// Lv
	WIN_HP4,		// HP/MHP
	WIN_HPBAR4,		// HPバー
	// ５体目のポケモン
	WIN_NAME5,		// 名前
	WIN_LV5,		// Lv
	WIN_HP5,		// HP/MHP
	WIN_HPBAR5,		// HPバー
	// ６体目のポケモン
	WIN_NAME6,		// 名前
	WIN_LV6,		// Lv
	WIN_HP6,		// HP/MHP
	WIN_HPBAR6,		// HPバー

	VSD_BMP_MAX
};

// セルアクターID
enum {
	VS_CLA_BALL01 = 0,	// VS画面：自分側ボール１
	VS_CLA_BALL02,		// VS画面：自分側ボール２
	VS_CLA_BALL03,		// VS画面：自分側ボール３
	VS_CLA_BALL04,		// VS画面：自分側ボール４
	VS_CLA_BALL05,		// VS画面：自分側ボール５
	VS_CLA_BALL06,		// VS画面：自分側ボール６

	VS_CLA_BALL11,		// VS画面：敵側ボール１
	VS_CLA_BALL12,		// VS画面：敵側ボール２
	VS_CLA_BALL13,		// VS画面：敵側ボール３
	VS_CLA_BALL14,		// VS画面：敵側ボール４
	VS_CLA_BALL15,		// VS画面：敵側ボール５
	VS_CLA_BALL16,		// VS画面：敵側ボール６

	VS_CLA_MAX,			// VS画面：セルアクター最大

	VS_CLA_RESULT1 = VS_CLA_MAX,	// 勝敗画面：勝敗１
	VS_CLA_RESULT2,					// 勝敗画面：勝敗２

	VS_CLA_END_MAX,		// 勝敗画面：セルアクター最大

	VS_CLA_POKE1 = 0,	// 確認画面：ポケモンアイコン１
	VS_CLA_ITEM1,		// 確認画面：アイテムアイコン１
	VS_CLA_CB1,			// 確認画面：カスタムボール１
	VS_CLA_ST1,			// 確認画面：状態異常アイコン１
	VS_CLA_PLBALL1,		// 確認画面：ボール１
	VS_CLA_POKE2,		// 確認画面：ポケモンアイコン２
	VS_CLA_ITEM2,		// 確認画面：アイテムアイコン２
	VS_CLA_CB2,			// 確認画面：カスタムボール２
	VS_CLA_ST2,			// 確認画面：状態異常アイコン２
	VS_CLA_PLBALL2,		// 確認画面：ボール２
	VS_CLA_POKE3,		// 確認画面：ポケモンアイコン３
	VS_CLA_ITEM3,		// 確認画面：アイテムアイコン３
	VS_CLA_CB3,			// 確認画面：カスタムボール３
	VS_CLA_ST3,			// 確認画面：状態異常アイコン３
	VS_CLA_PLBALL3,		// 確認画面：ボール３
	VS_CLA_POKE4,		// 確認画面：ポケモンアイコン４
	VS_CLA_ITEM4,		// 確認画面：アイテムアイコン４
	VS_CLA_CB4,			// 確認画面：カスタムボール４
	VS_CLA_ST4,			// 確認画面：状態異常アイコン４
	VS_CLA_PLBALL4,		// 確認画面：ボール４
	VS_CLA_POKE5,		// 確認画面：ポケモンアイコン５
	VS_CLA_ITEM5,		// 確認画面：アイテムアイコン５
	VS_CLA_CB5,			// 確認画面：カスタムボール５
	VS_CLA_ST5,			// 確認画面：状態異常アイコン５
	VS_CLA_PLBALL5,		// 確認画面：ボール５
	VS_CLA_POKE6,		// 確認画面：ポケモンアイコン６
	VS_CLA_ITEM6,		// 確認画面：アイテムアイコン６
	VS_CLA_CB6,			// 確認画面：カスタムボール６
	VS_CLA_ST6,			// 確認画面：状態異常アイコン６
	VS_CLA_PLBALL6,		// 確認画面：ボール６

	VS_CLA_PLMAX,		// 確認画面：セルアクター最大
};

// メインシーケンス
enum {
	SEQ_VSD_INIT = 0,	// 初期化
	SEQ_VSD_MAIN,		// メイン
	SEQ_VSD_END			// 終了
};

// 処理コマンド
enum {
	VSD_FUNC_LOOP = 0,		// 実行中
	VSD_FUNC_NEXT,			// 次の処理へ
	VSD_FUNC_REPEAT,		// 次の処理を即実行
};


#define	INIT_WAIT	( 8 )	// 初期ウェイト

#define	POKECHECK_INIT_WAIT	( 32 )	// ポケモン確認画面：初期ウェイト
#define	POKECHECK_END_WAIT	( 64 )	// ポケモン確認画面：終了ウェイト

#define	SCROLL_SPEED	( 16 )		// VS画面：スクロール速度
#define	SCROLL_INIT		( 256 )		// VS画面：初期スクロールカウンタ
#define	SCROLL_END		( 24 )		// VS画面：スクロール終了位置

#define	END_SCROLL_SPEED	( 12 )	// 勝敗画面：スクロール速度

#define	VS_CLA_BALL_SX		( 19 )	// VS画面：ボールXサイズ
#define	VS_CLA_BALL_M_SX	( 4 )	// VS画面：マルチ用のX補正サイズ

#define	VS_CLA_BALL00_PX	( 24 )	// VS画面：自分側前半３つのボール表示X座標（通常）
#define	VS_CLA_BALL00_PY	( 160 )	// VS画面：自分側前半３つのボール表示Y座標（通常）

// VS画面：自分側後半３つのボール表示X座標（通常）
#define	VS_CLA_BALL03_PX	( VS_CLA_BALL00_PX + VS_CLA_BALL_SX * 3 )
// VS画面：自分側後半３つのボール表示Y座標（通常）
#define	VS_CLA_BALL03_PY	( VS_CLA_BALL00_PY )

#define	VS_CLA_BALL10_PX	( 136 )	// VS画面：敵側前半３つのボール表示X座標（通常）
#define	VS_CLA_BALL10_PY	( 48 )	// VS画面：敵側前半３つのボール表示Y座標（通常）

// VS画面：敵側後半３つのボール表示X座標（通常）
#define	VS_CLA_BALL13_PX	( VS_CLA_BALL10_PX + VS_CLA_BALL_SX * 3 )
// VS画面：敵側後半３つのボール表示Y座標（通常）
#define	VS_CLA_BALL13_PY	( VS_CLA_BALL10_PY )

#define	VS_CLA_BALL00M_PX	( 24 )	// VS画面：自分側前半３つのボール表示X座標（マルチ）
#define	VS_CLA_BALL00M_PY	( 140 )	// VS画面：自分側前半３つのボール表示Y座標（マルチ）

// VS画面：自分側後半３つのボール表示X座標（マルチ）
#define	VS_CLA_BALL03M_PX	( VS_CLA_BALL00M_PX + VS_CLA_BALL_SX * 3 + VS_CLA_BALL_M_SX )
// VS画面：自分側後半３つのボール表示Y座標（マルチ）
#define	VS_CLA_BALL03M_PY	( 164 )

// VS画面：敵側前半３つのボール表示X座標（マルチ）
#define	VS_CLA_BALL10M_PX	( 136 - VS_CLA_BALL_M_SX )
// VS画面：敵側前半３つのボール表示Y座標（マルチ）
#define	VS_CLA_BALL10M_PY	( 44 )

// VS画面：敵側後半３つのボール表示X座標（マルチ）
#define	VS_CLA_BALL13M_PX	( VS_CLA_BALL10M_PX + VS_CLA_BALL_SX * 3 + VS_CLA_BALL_M_SX )
// VS画面：敵側後半３つのボール表示Y座標（マルチ）
#define	VS_CLA_BALL13M_PY	( 68 )

#define	VS_FOAM_NAME00_PX	( 15 )		// VS画面：自分側のプレイヤー名X座標（通常）
#define	VS_FOAM_NAME00_PY	( 134 )		// VS画面：自分側のプレイヤー名Y座標（通常）

#define	VS_FOAM_NAME00M_PX	( 15 )		// VS画面：自分側のプレイヤー名１X座標（マルチ）
#define	VS_FOAM_NAME00M_PY	( 114 )		// VS画面：自分側のプレイヤー名１Y座標（マルチ）
#define	VS_FOAM_NAME03M_PX	( 76 )		// VS画面：自分側のプレイヤー名２X座標（マルチ）
#define	VS_FOAM_NAME03M_PY	( 138 )		// VS画面：自分側のプレイヤー名２Y座標（マルチ）

#define	VS_FOAM_NAME10_PX	( 128 )		// VS画面：敵側のプレイヤー名X座標（通常）
#define	VS_FOAM_NAME10_PY	( 22 )		// VS画面：敵側のプレイヤー名Y座標（通常）

#define	VS_FOAM_NAME10M_PX	( 123 )		// VS画面：敵側のプレイヤー名１X座標（マルチ）
#define	VS_FOAM_NAME10M_PY	( 18 )		// VS画面：敵側のプレイヤー名１Y座標（マルチ）
#define	VS_FOAM_NAME13M_PX	( 184 )		// VS画面：敵側のプレイヤー名２X座標（マルチ）
#define	VS_FOAM_NAME13M_PY	( 42 )		// VS画面：敵側のプレイヤー名２Y座標（マルチ）

#define	CLACT_ID_COMMON		( 47111 )	// この画面で使用するセルアクターのID

// キャラリソースID
enum {
	VS_CHR_ID_BALL = CLACT_ID_COMMON,	// ボール
	VS_CHR_ID_RESULT,					// 勝敗
	VS_CHR_ID_MAX = VS_CHR_ID_RESULT - CLACT_ID_COMMON + 1,	// VS画面、勝敗画面の最大

	VS_CHR_ID_POKE1 = VS_CHR_ID_RESULT + 1,	// ポケモンアイコン１
	VS_CHR_ID_POKE2,						// ポケモンアイコン２
	VS_CHR_ID_POKE3,						// ポケモンアイコン３
	VS_CHR_ID_POKE4,						// ポケモンアイコン４
	VS_CHR_ID_POKE5,						// ポケモンアイコン５
	VS_CHR_ID_POKE6,						// ポケモンアイコン６
	VS_CHR_ID_ITEM,							// アイテムアイコン
	VS_CHR_ID_ST,							// 状態異常アイコン
	VS_CHR_ID_PLBALL,						// ボール
	VS_CHR_ID_MV_MAX = VS_CHR_ID_PLBALL - VS_CHR_ID_POKE1 + 1	// 確認画面の最大
};

// パレットリソースID
enum {
	VS_PAL_ID_BALL = CLACT_ID_COMMON,	// ボール
	VS_PAL_ID_MAX = VS_PAL_ID_BALL - CLACT_ID_COMMON + 1,	// VS画面、勝敗画面の最大

	VS_PAL_ID_POKE = VS_PAL_ID_BALL + 1,	// ポケモンアイコン
	VS_PAL_ID_ITEM,							// アイテムアイコン
	VS_PAL_ID_ST,							// 状態異常アイコン
	VS_PAL_ID_PLBALL,						// ボール
	VS_PAL_ID_MV_MAX = VS_PAL_ID_PLBALL - VS_PAL_ID_POKE + 1	// 確認画面の最大
};

// セルリソースID
enum {
	VS_CEL_ID_BALL = CLACT_ID_COMMON,	// ボール
	VS_CEL_ID_RESULT,					// 勝敗
	VS_CEL_ID_MAX = VS_CEL_ID_RESULT - CLACT_ID_COMMON + 1,	// VS画面、勝敗画面の最大

	VS_CEL_ID_POKE = VS_CEL_ID_RESULT + 1,	// ポケモンアイコン
	VS_CEL_ID_ITEM,							// アイテムアイコン
	VS_CEL_ID_ST,							// 状態異常アイコン
	VS_CEL_ID_PLBALL,						// ボール
	VS_CEL_ID_MV_MAX = VS_CEL_ID_PLBALL - VS_CEL_ID_POKE + 1	// 確認画面の最大
};

// セルアニメリソースID
enum {
	VS_ANM_ID_BALL = CLACT_ID_COMMON,	// ボール
	VS_ANM_ID_RESULT,					// 勝敗
	VS_ANM_ID_MAX = VS_ANM_ID_RESULT - CLACT_ID_COMMON + 1,	// VS画面、勝敗画面の最大

	VS_ANM_ID_POKE = VS_ANM_ID_RESULT + 1,	// ポケモンアイコン
	VS_ANM_ID_ITEM,							// アイテムアイコン
	VS_ANM_ID_ST,							// 状態異常アイコン
	VS_ANM_ID_PLBALL,						// ボール
	VS_ANM_ID_MV_MAX = VS_ANM_ID_PLBALL - VS_ANM_ID_POKE + 1	// 確認画面の最大
};


#define	PCOL_N_WHITE	( GF_PRINTCOLOR_MAKE( 15, 14, 0 ) )		// フォントカラー：白
#define	PCOL_N_BLUE		( GF_PRINTCOLOR_MAKE( 3, 4, 0 ) )		// フォントカラー：青
#define	PCOL_N_RED		( GF_PRINTCOLOR_MAKE( 5, 6, 0 ) )		// フォントカラー：赤

#define	MULTI_SCROLL_INIT	( 16 )		// 確認画面：OBJの初期スクロール値

#define	STR_LV_PX		( 0 )			// 確認画面：レベル表示X位置
#define	STR_LV_PY		( 5 )			// 確認画面：レベル表示Y位置
#define	STR_SLASH_PX	( 28 )			// 確認画面：HPのスラッシュ表示X位置
#define	STR_SLASH_PY	( 0 )			// 確認画面：HPのスラッシュ表示Y位置
#define	PRM_NICKNAME_PX	( 0 )			// 確認画面：ニックネーム表示X位置
#define	PRM_NICKNAME_PY	( 0 )			// 確認画面：ニックネーム表示Y位置
#define	PRM_SEX_PX		( 64 )			// 確認画面：性別表示X位置
#define	PRM_SEX_PY		( 0 )			// 確認画面：性別表示Y位置

#define	HPGAUGE_DOTTO_MAX	( 48 )		// 確認画面：HPゲージのドット数
#define	HPGAUGE_COL1		( 9 )		// 確認画面：HPゲージのカラー１の位置
#define	HPGAUGE_COL2		( 10 )		// 確認画面：HPゲージのカラー２の位置
#define	PALPOS_GREEN		( HPGAUGE_COL1 )	// 確認画面：HPゲージ緑のカラーの位置
#define	PALPOS_YELLOW		( HPGAUGE_COL1+16 )	// 確認画面：HPゲージ黄のカラーの位置
#define	PALPOS_RED			( HPGAUGE_COL1+32 )	// 確認画面：HPゲージ赤のカラーの位置


#define	START_SHAKE_X	( 8 )	// VS画面：X揺れ幅
#define	START_SHAKE_Y	( 4 )	// VS画面：Y揺れ幅

#define	END_SHAKE_X	( 4 )	// 勝敗画面：X揺れ幅
#define	END_SHAKE_Y	( 2 )	// 勝敗画面：Y揺れ幅

#define	SHAKE_CNT	( 24 )	// VS画面：揺れカウント

#define	SHAKE_WAIT	( 16 )	// 勝敗画面：揺らした後のウェイト

#define	PUSH_WAIT	( 16 )	// 勝敗画面：プレート押し出し後のウェイト

#define	RESULT_OPEN_CNT		( 16 )	// 勝敗画面：勝敗ウィンドウオープンカウント
#define	RESULT_WAIT			( 32 )	// 勝敗画面：勝敗ウィンドウオープン後のウェイト

#define	RESULT_END_WAIT		( 64 )	// 勝敗画面：勝敗表示後のウェイト
#define	RESULT_WIN_CHG_PAL	( 2 )	// 勝敗画面：フェードで変更するパレット（勝ち）
#define	RESULT_LOSE_CHG_PAL	( 1 )	// 勝敗画面：フェードで変更するパレット（負け）

#define	WL_ICON_CGX_SIZ		( 4*4 )		// 通信アイコンのサイズ

#define	VS_FOAM00_PX	( 48 )				// VS画面：自分側トレーナー名１表示X座標
#define	VS_FOAM00_PY	( 144 )				// VS画面：自分側トレーナー名１表示Y座標
#define	VS_FOAM01_PX	( 48 + 19 * 3 )		// VS画面：自分側トレーナー名２表示X座標
#define	VS_FOAM01_PY	( 144 )				// VS画面：自分側トレーナー名２表示Y座標
#define	VS_FOAM02_PX	( 48 )				// VS画面：敵側トレーナー名１表示X座標
#define	VS_FOAM02_PY	( 144 )				// VS画面：敵側トレーナー名１表示Y座標
#define	VS_FOAM03_PX	( 48 )				// VS画面：敵側トレーナー名２表示X座標
#define	VS_FOAM03_PY	( 144 )				// VS画面：敵側トレーナー名２表示Y座標

#define	VSD_BMP_PNAME_SX	( 8 )		// フォントOAMのXサイズ
#define	VSD_BMP_PNAME_SY	( 2 )		// フォントOAMのYサイズ
#define	VSD_BMP_PNAME_SIZ	( VSD_BMP_PNAME_SX * VSD_BMP_PNAME_SY )	// フォントOAMのキャラサイズ
#define	VSD_BMP_PNAME1_CGX	( 1024-VSD_BMP_PNAME_SIZ-WL_ICON_CGX_SIZ )	// フォントOAM作成位置

#define	RESULT_OBJ_PY	( 96 )		// 勝敗OBJ表示Y座標
#define	RESULT_OBJ_PX1	( 48 )		// 勝敗OBJ１表示X座標
#define	RESULT_OBJ_PX2	( 208 )		// 勝敗OBJ２表示X座標
#define	RESULT_DRAW_PX	( 128 )		// 「ひきわけ」OBJ表示X座標

#define BP_NEAR		( FX32_ONE )		// パーティクルのカメラニア設定
#define BP_FAR		( FX32_ONE * 900 )	// パーティクルのカメラファー設定

#define	TMP_MSG_SIZ		( 32 )		// 確認画面：メッセージサイズ


//--------------------------------------------------------------------------------------------
//	SE定義
//--------------------------------------------------------------------------------------------
#define	VSD_SE_VS_PLATE_BREAK	( SEQ_SE_DP_VSDEMO01 )		// VS画面：プレート衝突SE

#define	VSD_SE_VS_PLATE_OUT		( SEQ_SE_DP_VSDEMO05 )		// VS画面：プレートスライドアウトSE

#define	VSD_SE_MULTI_POKE_IN	( SEQ_SE_DP_VSDEMO05 )		// 確認画面：パートナースライドインSE

#define	VSD_SE_RESULT_PLATE_BREAK	( SEQ_SE_DP_GASHIN )	// 勝敗画面：プレート衝突SE

//#define	VSD_SE_RESULT_PLATE_MOVE	( SEQ_SE_DP_VSDEMO02 )	// 勝敗画面：プレート押し出しSE
#define	VSD_SE_RESULT_PLATE_MOVE	( SEQ_SE_DP_DODON )		// 勝敗画面：プレート押し出しSE

//#define	VSD_SE_RESULT_PUT		( SEQ_SE_DP_VSDEMO03 )	// 勝敗画面：勝敗表示SE
#define	VSD_SE_RESULT_PUT			( SEQ_SE_DP_VSDEMO06 )	// 勝敗画面：勝敗表示SE

//#define	VSD_SE_RESULT_FADE		( SEQ_SE_DP_VSDEMO04 )	// 勝敗画面：負けプレートフェードSE
#define	VSD_SE_RESULT_FADE			( SEQ_SE_DP_VSDEMO07 )	// 勝敗画面：負けプレートフェードSE


