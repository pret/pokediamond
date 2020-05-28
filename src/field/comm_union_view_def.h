//=============================================================================
/**
 * @file	comm_union_view_def.h
 * @brief	ユニオンルームでの上画面描画処理
 *          
 * @author	Akito Mori
 * @date    2005.12.20
 */
//=============================================================================

#ifndef __COMM_UNION_VIEW_DEF_H__
#define __COMM_UNION_VIEW_DEF_H__

// ユニオンＯＢＪの数
#define UNION_BEACON_OBJ_MAX	( 50 )

// エフェクトを主人公ＯＢＪにかける時の番号
#define UNION_EFFECT_HERO_NO	( 50 )	

// ユニオンチャットの最大数
#define UNION_CHAT_MAX		( 30 )

// =======================================================================
// 定数宣言
// =======================================================================
enum{
	OBJ_NO_APPEAR=0,
	OBJ_FALL_WAIT,
	OBJ_OK,
	OBJ_RISE_WAIT,
	OBJ_RISED,
};

enum{
	OBJ_REQ_NO    =0,
	OBJ_REQ_FALL,
	OBJ_REQ_FALL_NOMOVE,
	OBJ_REQ_RISE,
};

enum{
	OBJ_MOVE_STAND=0,
	OBJ_MOVE_WALK,
};


// =======================================================================
// ＯＢＪ管理用構造体宣言
// =======================================================================
typedef struct{
	u8      request;		// 出現リクエスト
	u8		appear;			// 出現フラグ
	u8		friend;			// しりあいグループに登録されているか？
	u8 		effect;			// エフェクト開始フラグ
	u8		effect_onflag;	// エフェクト表示中の種類
	u8      arrow;			// 向いている方向
	u16		wait;			// エフェクト生存時間
	u8		view;			// 見た目番号
	u8      appearmode;     // OBJ行動モード（0:動かない	1:歩き回る)
	u32		trainerId;		// トレーナーＩＤ
	EOA_PTR effect_ptr;		// 赤い枠エフェクト管理ポインタ
	EOA_PTR shadow_ptr;		// ともだちグループマーク（足元の赤い丸・青い丸）管理ポインタ
}OBJ_VIEW_WORK;


// =======================================================================
// ユニオンチャットワーク構造体宣言
// =======================================================================
typedef struct{
	STRBUF		*name;
    STRBUF		*message;
    STRBUF		*friend;
	u32			id;
	int			sex;
	PMS_DATA	PmsData;
}UNION_CHAT;

struct UNION_CHAT_RINGBUF{
	UNION_CHAT mes[UNION_CHAT_MAX];		// メッセージが格納される（リングバッファ）
	int 		  num;					// 登録されているメッセージの数
	int			  start;				// リングバッファのスタートポイント
};


// =======================================================================
// ユニオンビュー構造体宣言
// =======================================================================
struct COMM_UNIONROOM_VIEW{
	COMM_UNIONROOM_WORK *cuw;
	TCB_PTR				viewTask;
	PLAYER_STATE_PTR    jiki;
	OBJ_VIEW_WORK 		objwork[UNION_BEACON_OBJ_MAX+1];	// FIELDOBJ50人＋主人公
	FIELDSYS_WORK		*fsys;
	FRIEND_LIST	  		*friendlist;
	UNION_CHAT_RINGBUF  *unionBoardChat;
	int 				nowobj;

	int 				vanishflag;
};

#endif