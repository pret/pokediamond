/**
 *	@file	nmix_game.h
 *	@brief	ナッツミキサー　ゲームプロセスヘッダ
 *	@author	Miyuki Iwasawa
 *	@date	06.07.08
 *	@data		2006.05.23		tomoya 更新
 */

#ifndef __H_NMIX_GAME_H__
#define __H_NMIX_GAME_H__

#include "nutmixer_def.h"
#include "nutmix_comm_pack.h"
#include "nmix_game_comm.h"
#include "nmix_game_demo.h"
#include "nmix_game_data.h"
#include "nmix_stdata.h"

#include "common.h"
#include "system/clact_util.h"
#include "system/swsprite.h"

//-----------------------------------------------------------------------------
/**
 *
 *					定数
 *
 */
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/**
 *					構造体宣言
*/
//-----------------------------------------------------------------------------
// 方向エフェクト出している値
#define NMIX_GAME_WAY_FLAG_RIGHT	( 1 )
#define NMIX_GAME_WAY_FLAG_LEFT	( 2 )


//-------------------------------------
//	木の実ミキサーワーク
//=====================================
typedef struct {
	// システム管理
	int	heapID;
	BOOL seqend_f;		///<ゲームシーケンス終了フラグ
	int	synchroID;		///<通信同期ID
	int	main_seq;		///<ゲームメインシーケンス制御
	int	sub_seq;		///<ゲームサブシーケンス制御
	BOOL main_seq_chg_req;///<通信コールバックからのシーケンス変更お願いがあったかフラグ
	int main_seq_req;	///<通信コールバックからのシーケンス変更お願い

	int wait;

#ifdef PM_DEBUG
	int comm_err_count;
#endif
	
	// BG
	GF_BGL_INI* bgl;
	int wnd_type;
	int msg_speed;

	// OAM
	NMIXGAME_CLACT_SYS	clact;
	NMIXGAME_CLACT_RES_WORK def_clact_res[ NMIX_GAME_DEF_OAM_RES_NUM ];
	BOOL clact_draw;

	// ソフトウェアスプライト
	SWSP_SYS_PTR	swsp_sys;


	// 画面管理データ
	u32 houkou_draw_flg;	// 方向切り替え表示中
	u32 gyaku_draw_flg;		// 逆回転表示中
	BOOL kogeru_draw_flg;	// こげる表示中
	BOOL kobore_draw_flg;	// こぼれる表示中

	// 動さワーク
	NMIX_DATA_KO	ko_data;	// 通信子データ
	NMIX_DATA_OYA	oya_data;
	u32 game_next;				// ゲームを続けたいか
	s32 last_rota;				// １つ前の親から来た回転角
	u32 last_count_down;		// カウントダウンデータ

	// 描画ワーク
	NMIX_DEMO_NUTS_IN nuts_in;	// 木の実投入
	NMIX_DEMO_SUB_WIN sub_win;	// サブウィンドウ操作
	NMIX_DEMO_COUNTDOWN countdown;	// カウントダウン
	NMIX_DEMO_COUNTDOWN end_mark;	// 終了MARK
	NMIX_DEMO_COUNTDOWN pen;		// ペン
	NMIX_DEMO_NABE_GRA nabe_gra;	// 鍋グラフィック動さ制御
	NMIX_DEMO_OTHER_MARK other_mark;	// 他の人の位置
	NMIX_DEMO_MAIN_WIN main_win;		// メイン画面BG管理
	NMIX_DEMO_SOOP_EFFECT soop_effect;	// スープエフェクト
	NMIX_DEMO_YAZIRUSI	yazirusi;	// 矢印オブジェクト
	NMIX_DEMO_HOSI_KIRAKIRA hosi_kira;	// 星キラキラ
	NMIX_DEMO_PORUTO_DRAW poruto_draw;	// ポルト描画
	NMIX_DEMO_YESNO_WND	yes_no;		// YESNOウィンドウ
	

	//通信関連データ領域
	int				comm_count;	// 通信メンバー数
	NUTMIX_COMMPACK_WORK* comm_work;// 通信ワーク
	int				commpack_flg;	// 通信パックフラグ
									// NUTMIX_COMM_PACK_ONE	( 0 )	// 一人用
									// NUTMIX_COMM_PACK_COMM	( 1 )	// 通信

	// 通信データ
	NUTMIX_GAME_COMM_PACK game_comm_pack;

	// メッセージデータ
	NMIXER_MSG	msgDat;

} NMIX_GAMEWORK;

extern void NMIX_SetMainSeq( NMIX_GAMEWORK* p_work, int seq );
extern void NMIX_SetSubSeq( NMIX_GAMEWORK* p_work, int seq );
extern void NMIX_SetEndReq( NMIX_GAMEWORK* p_work );


#endif	//__H_NMIX_GAME_H__

