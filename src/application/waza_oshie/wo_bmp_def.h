enum {
	WO_PAL_MENU_WIN = 12,	// メニューウィンドウパレット
	WO_PAL_TALK_WIN,		// 進行ウィンドウパレット
	WO_PAL_TALK_FONT,		// 進行フォントパレット
	WO_PAL_SYS_FONT,		// システムフォントパレット
};

// メニューウィンドウ転送位置
#define	WO_MENU_WIN_CGX		( 1 )
// 進行ウィンドウ転送位置
#define	WO_TALK_WIN_CGX		( WO_MENU_WIN_CGX + MENU_WIN_CGX_SIZ )

// 「たたかうわざ」
#define	WIN_STR_BATTLE_PX	( 19 )
#define	WIN_STR_BATTLE_PY	( 0 )
#define	WIN_STR_BATTLE_SX	( 11 )
#define	WIN_STR_BATTLE_SY	( 2 )
#define	WIN_STR_BATTLE_PAL	( WO_PAL_SYS_FONT )
#define	WIN_STR_BATTLE_CGX	( WO_TALK_WIN_CGX + TALK_WIN_CGX_SIZ )

// 「コンテストわざ」
#define	WIN_STR_CONTEST_PX	( 19 )
#define	WIN_STR_CONTEST_PY	( 0 )
#define	WIN_STR_CONTEST_SX	( 11 )
#define	WIN_STR_CONTEST_SY	( 2 )
#define	WIN_STR_CONTEST_PAL	( WO_PAL_SYS_FONT )
#define	WIN_STR_CONTEST_CGX	( WIN_STR_BATTLE_CGX + WIN_STR_BATTLE_SX * WIN_STR_BATTLE_SY )

// 「ぶんるい」
#define	WIN_STR_CLASS_PX	( 1 )
#define	WIN_STR_CLASS_PY	( 0 )
#define	WIN_STR_CLASS_SX	( 6 )
#define	WIN_STR_CLASS_SY	( 2 )
#define	WIN_STR_CLASS_PAL	( WO_PAL_SYS_FONT )
#define	WIN_STR_CLASS_CGX	( WIN_STR_CONTEST_CGX + WIN_STR_CONTEST_SX * WIN_STR_CONTEST_SY )

// 「いりょく」
#define	WIN_STR_ATTACK_PX	( 1 )
#define	WIN_STR_ATTACK_PY	( 2 )
#define	WIN_STR_ATTACK_SX	( 6 )
#define	WIN_STR_ATTACK_SY	( 2 )
#define	WIN_STR_ATTACK_PAL	( WO_PAL_SYS_FONT )
#define	WIN_STR_ATTACK_CGX	( WIN_STR_CLASS_CGX + WIN_STR_CLASS_SX * WIN_STR_CLASS_SY )

// 「めいちゅう」
#define	WIN_STR_HIT_PX		( 1 )
#define	WIN_STR_HIT_PY		( 4 )
#define	WIN_STR_HIT_SX		( 8 )
#define	WIN_STR_HIT_SY		( 2 )
#define	WIN_STR_HIT_PAL		( WO_PAL_SYS_FONT )
#define	WIN_STR_HIT_CGX		( WIN_STR_ATTACK_CGX + WIN_STR_ATTACK_SX * WIN_STR_ATTACK_SY )

// 「PP」
#define	WIN_STR_PP_PX		( 1 )
#define	WIN_STR_PP_PY		( 6 )
#define	WIN_STR_PP_SX		( 3 )
#define	WIN_STR_PP_SY		( 2 )
#define	WIN_STR_PP_PAL		( WO_PAL_SYS_FONT )
#define	WIN_STR_PP_CGX		( WIN_STR_HIT_CGX + WIN_STR_HIT_SX * WIN_STR_HIT_SY )

// 「アピールポイント」
#define	WIN_STR_APP_PX		( 2 )
#define	WIN_STR_APP_PY		( 2 )
#define	WIN_STR_APP_SX		( 12 )
#define	WIN_STR_APP_SY		( 2 )
#define	WIN_STR_APP_PAL		( WO_PAL_SYS_FONT )
#define	WIN_STR_APP_CGX		( WIN_STR_PP_CGX + WIN_STR_PP_SX * WIN_STR_PP_SY )

// 威力値
#define	WIN_PRM_ATTACK_PX	( 13 )
#define	WIN_PRM_ATTACK_PY	( 2 )
#define	WIN_PRM_ATTACK_SX	( 3 )
#define	WIN_PRM_ATTACK_SY	( 2 )
#define	WIN_PRM_ATTACK_PAL	( WO_PAL_SYS_FONT )
#define	WIN_PRM_ATTACK_CGX	( WIN_STR_APP_CGX + WIN_STR_APP_SX * WIN_STR_APP_SY )

// 命中値
#define	WIN_PRM_HIT_PX		( 13 )
#define	WIN_PRM_HIT_PY		( 4 )
#define	WIN_PRM_HIT_SX		( 3 )
#define	WIN_PRM_HIT_SY		( 2 )
#define	WIN_PRM_HIT_PAL		( WO_PAL_SYS_FONT )
#define	WIN_PRM_HIT_CGX		( WIN_PRM_ATTACK_CGX + WIN_PRM_ATTACK_SX * WIN_PRM_ATTACK_SY )

// PP値
#define	WIN_PRM_PP_PX		( 11 )
#define	WIN_PRM_PP_PY		( 6 )
#define	WIN_PRM_PP_SX		( 5 )
#define	WIN_PRM_PP_SY		( 2 )
#define	WIN_PRM_PP_PAL		( WO_PAL_SYS_FONT )
#define	WIN_PRM_PP_CGX		( WIN_PRM_HIT_CGX + WIN_PRM_HIT_SX * WIN_PRM_HIT_SY )

// 戦闘説明
#define	WIN_BTL_INFO_PX		( 1 )
#define	WIN_BTL_INFO_PY		( 8 )
#define	WIN_BTL_INFO_SX		( 15 )
#define	WIN_BTL_INFO_SY		( 10 )
#define	WIN_BTL_INFO_PAL	( WO_PAL_SYS_FONT )
#define	WIN_BTL_INFO_CGX	( WIN_PRM_PP_CGX + WIN_PRM_PP_SX * WIN_PRM_PP_SY )

// コンテスト説明
#define	WIN_CON_INFO_PX		( 1 )
#define	WIN_CON_INFO_PY		( 9 )
#define	WIN_CON_INFO_SX		( 15 )
#define	WIN_CON_INFO_SY		( 6 )
#define	WIN_CON_INFO_PAL	( WO_PAL_SYS_FONT )
#define	WIN_CON_INFO_CGX	( WIN_BTL_INFO_CGX + WIN_BTL_INFO_SX * WIN_BTL_INFO_SY )

// メッセージウィンドウ
#define	WIN_MSG_PX		( 2 )
#define	WIN_MSG_PY		( 19 )
#define	WIN_MSG_SX		( 27 )
#define	WIN_MSG_SY		( 4 )
#define	WIN_MSG_PAL		( WO_PAL_TALK_FONT )
#define	WIN_MSG_CGX		( WIN_CON_INFO_CGX + WIN_CON_INFO_SX * WIN_CON_INFO_SY )

// 技リスト
#define	WIN_LIST_PX		( 21 )
#define	WIN_LIST_PY		( 3 )
#define	WIN_LIST_SX		( 11 )
#define	WIN_LIST_SY		( 14 )
#define	WIN_LIST_PAL	( WO_PAL_SYS_FONT )
#define	WIN_LIST_CGX	( WIN_MSG_CGX + WIN_MSG_SX * WIN_MSG_SY )

// はい/いいえ
#define	WIN_YESNO_PX	( 23 )
#define	WIN_YESNO_PY	( 13 )
#define	WIN_YESNO_SX	( 7 )
#define	WIN_YESNO_SY	( 4 )
#define	WIN_YESNO_PAL	( WO_PAL_TALK_FONT )
#define	WIN_YESNO_CGX	( WIN_LIST_CGX + WIN_LIST_SX * WIN_LIST_SY )



