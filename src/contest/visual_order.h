//==============================================================================
/**
 * @file	visual_order.h
 * @brief	ビジュアル部門：命令送受信のヘッダ
 * @author	matsuda
 * @date	2005.12.13(火)
 */
//==============================================================================
#ifndef __VISUAL_ORDER_H__
#define __VISUAL_ORDER_H__

#include "wazaeffect/ball_effect.h"


//==============================================================================
//	定数定義
//==============================================================================
//--------------------------------------------------------------
/**
 *     命令コード
 * 					※OrderFuncTblと必ず並びを同じにしておくこと！
 */
//--------------------------------------------------------------
enum{
	VORDER_NO_SAMPLE,			///<サンプル
	VORDER_NO_VISUAL_EXIT,		///<ビジュアル部門終了
	VORDER_NO_APPEAR,			///<ポケモン登場
	VORDER_NO_ADVANCE,			///<前進
	VORDER_NO_AUDIENCE_EVALUATE_BP,	///<観客評価(BP)
	VORDER_NO_AUDIENCE_EVALUATE_CLIP,	///<観客評価(Clip)
	VORDER_NO_AUDIENCE_EVALUATE_ALL,	///<観客評価(BP & Clip)
	VORDER_NO_POKE_OUT,			///<ポケモン退場
	VORDER_NO_DONCHOU_UP,		///<どんちょう上げる
	VORDER_NO_DONCHOU_DOWN,		///<どんちょう下げる
	VORDER_NO_TRAINER_IN,		///<トレーナー登場
	VORDER_NO_TRAINER_OUT,		///<トレーナー退場
	VORDER_NO_APPEAR_EFFECT,	///<登場エフェクト
	VORDER_NO_TALK,				///<会話メッセージ表示
	VORDER_NO_FADE_INOUT,	///<全体フェードイン・アウト
	VORDER_NO_DONCHOU_EFFECT_UP,	///<どんちょうエフェクト上昇
	VORDER_NO_VISUAL_FINISH,	///<ビジュアル部門終了エフェクト
};


//==============================================================================
//	構造体定義
//==============================================================================
///ポケモン前進ローカル構造体
typedef struct{
	VISUAL_PROC_WORK *vpw;
	CORDER_HEAD req_head;
	CONTEST_ORDER_WORK *cow;
	
	u8 seq;
	u8 breeder_no;

	s32 x;
	s32 y;
}VOLOCAL_ADVANCE;

///ポケモン登場ローカル構造体
typedef struct{
	VISUAL_PROC_WORK *vpw;
	CORDER_HEAD req_head;
	CONTEST_ORDER_WORK *cow;
	
	u8 seq;
	u8 breeder_no;
	s16 wait;
}VOLOCAL_POKE_APPEAR;

///ポケモン前進ローカル構造体
typedef struct{
	VISUAL_PROC_WORK *vpw;
	CORDER_HEAD req_head;
	CONTEST_ORDER_WORK *cow;
	
	u8 seq;
	u8 breeder_no;

	s32 x;
	s32 y;
}VOLOCAL_POKEOUT;

///どんちょうを上げるローカル構造体
typedef struct{
	VISUAL_PROC_WORK *vpw;
	CORDER_HEAD req_head;
	CONTEST_ORDER_WORK *cow;
	
	u8 seq;
	
	s8 anm_line;			///<アニメ書き換えの基本ライン
	u8 anm_no;				///<アニメNo
	s8 anm_wait;			///<アニメウェイト
	s8 anm_dansa_wait;		///<アニメ段差ウェイト
}VOLOCAL_DONCHOU_UP;

///どんちょうを上げるローカル構造体
typedef struct{
	VISUAL_PROC_WORK *vpw;
	CORDER_HEAD req_head;
	CONTEST_ORDER_WORK *cow;
	
	u8 seq;

	s8 anm_line;			///<アニメ書き換えの基本ライン
	u8 anm_no;				///<アニメNo
	s8 anm_wait;			///<アニメウェイト
	s8 anm_dansa_wait;		///<アニメ段差ウェイト
}VOLOCAL_DONCHOU_DOWN;

///観客評価ローカル構造体
typedef struct{
	VISUAL_PROC_WORK *vpw;
	CORDER_HEAD req_head;
	CONTEST_ORDER_WORK *cow;
	
	u8 seq;
	u8 wait;
	u8 max_count;					///<観客が表示するハートの数、最大数
	u8 put_count;					///<今までに表示したハートの数をカウント
	u8 bp_count;					///<BPのハート表示最大数
	u8 clip_count;					///<CLIPのハート表示最大数
	s16 old_x;						///<1つ前に表示したハートの座標X
	s16 old_y;						///<1つ前に表示したハートの座標Y
	u8 heart_anm;					///<ハートのアニメタイプ
	u8 all_type;					///<TRUE:BPとクリップ両方出す
}VOLOCAL_EVALUATE;

///トレーナー登場・退場ローカル構造体
typedef struct{
	VISUAL_PROC_WORK *vpw;
	CORDER_HEAD req_head;
	CONTEST_ORDER_WORK *cow;
	
	u8 seq;
	u8 breeder_no;

	s32 x;
	s32 y;
}VOLOCAL_TRAINER_INOUT;

///ボールエフェクト(爆発)
typedef struct{
	TBALL_CUSTOM_PARAM bcp;
	BES_PTR bes;
	POKEMON_PARAM *pp;
	u8 seq;
	u8 end;				///<1:エフェクト終了
}VOLOCAL_SUB_BALL_EFF;

///ボール移動エフェクト
typedef struct{
	VISUAL_PROC_WORK *vpw;
	BMS_PTR bms;
	u8 seq;
	u8 end;				///<1:エフェクト終了
	u8 wait;
}VOLOCAL_SUB_BALL_MOVE;

///ポケモン縮小から登場エフェクト
typedef struct{
	VISUAL_PROC_WORK *vpw;
	fx32 aff_x;
	fx32 aff_y;
	u8 seq;
	u8 end;				///<1:エフェクト終了
	u8 breeder_no;
}VOLOCAL_SUB_POKE_EFF;

///トレーナー退場エフェクト
typedef struct{
	VISUAL_PROC_WORK *vpw;

	s32 x;
	s32 y;

	u8 seq;
	u8 end;				///<1:エフェクト終了
	u8 loop;
	u8 wait;
}VOLOCAL_SUB_TRAINER_EFF;

///登場エフェクト
typedef struct{
	VISUAL_PROC_WORK *vpw;
	CORDER_HEAD req_head;
	CONTEST_ORDER_WORK *cow;
	
	u8 seq;
	u8 breeder_no;

	VOLOCAL_SUB_BALL_EFF ball_eff;
	VOLOCAL_SUB_BALL_MOVE ball_move;
	VOLOCAL_SUB_POKE_EFF poke_eff;
	VOLOCAL_SUB_TRAINER_EFF tr_eff;
}VOLOCAL_APPEAR_EFF;

///会話メッセージの表示
typedef struct{
	VISUAL_PROC_WORK *vpw;
	CORDER_HEAD req_head;
	CONTEST_ORDER_WORK *cow;
	
	u8 seq;
	u8 breeder_no;
	u8 close_wait;

	VTAG_PARAM a_talk_tagpara;		///<ノーマル会話：タグ展開用パラメータ
	u8 a_talk_id;					///<ノーマル会話ID(A_TALK_VISUAL_???)
	u8 a_talk_bmpwin_close_wait;	///<メッセージを表示しきってからウィンドウを閉じるまでのwait
	u8 a_talk_bmpwin_not_close;		///<TRUE:ウィンドウを閉じずに終了
}VOLOCAL_TALK_PUT;

///どんちょうフェードアウトローカル構造体
typedef struct{
	VISUAL_PROC_WORK *vpw;
	CORDER_HEAD req_head;
	CONTEST_ORDER_WORK *cow;
	
	u8 seq;

	s8 fade_start_evy;
	s8 fade_end_evy;
	s8 fade_wait;
	u16 fade_next_rgb;
}VOLOCAL_DFO;	//DonchouFadeOut

///どんちょうエフェクト上昇ローカル構造体
typedef struct{
	VISUAL_PROC_WORK *vpw;
	CORDER_HEAD req_head;
	CONTEST_ORDER_WORK *cow;
	
	u8 seq;
	
	s8 anm_line;			///<アニメ書き換えの基本ライン
	u8 anm_no;				///<アニメNo
	s8 anm_wait;			///<アニメウェイト
	s8 anm_dansa_wait;		///<アニメ段差ウェイト
	
	u8 lvup_se_req;			///<TRUE:LVUP SE再生リクエスト
	
	s32 lvup_wait;
}VOLOCAL_DONCHOU_EFFECT_UP;

///ビジュアル部門終了ローカル構造体
typedef struct{
	VISUAL_PROC_WORK *vpw;
	CORDER_HEAD req_head;
	CONTEST_ORDER_WORK *cow;
	
	u8 seq;
}VOLOCAL_FINISH;


//==============================================================================
//	外部関数宣言
//==============================================================================
extern void VisualOrder_WorkInit(VISUAL_PROC_WORK *vpw);


#endif	//__VISUAL_ORDER_H__

