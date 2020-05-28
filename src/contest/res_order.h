//==============================================================================
/**
 * @file	res_order.h
 * @brief	コンテスト結果発表画面：命令送受信のヘッダ
 * @author	matsuda
 * @date	2006.03.17(金)
 */
//==============================================================================
#ifndef __RES_ORDER_H__
#define __RES_ORDER_H__


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
	RORDER_NO_SAMPLE,			///<サンプル
	RORDER_NO_GAMEPARAM_UPDATE,	///<ゲームパラメータ更新
	RORDER_NO_DONCHOU_UP,		///<どんちょうを上げる
	RORDER_NO_DONCHOU_DOWN,		///<どんちょうを下げる
	RORDER_NO_CONRES_EXIT,		///<ダンス部門終了
	RORDER_NO_TALK,				///<会話メッセージ表示
	RORDER_NO_RESULT_CHANGE,	///<披露画面から結果発表画面に切り替える
	RORDER_NO_RANKING_ANNOUNCE,	///<順位発表
	RORDER_NO_VICTORY_APPEAR,	///<優勝したポケモンの登場演出
	RORDER_NO_METER_UPDATE,		///<メーターを伸ばす
	RORDER_NO_RESULT_FADEOUT,	///<結果発表画面をフェードアウトする
};


//==============================================================================
//	構造体定義
//==============================================================================
///どんちょうを上げるローカル構造体
typedef struct{
	CONRES_PROC_WORK *rpw;
	CORDER_HEAD req_head;
	CONTEST_ORDER_WORK *cow;
	
	u8 seq;

	s8 anm_line;			///<アニメ書き換えの基本ライン
	u8 anm_no;				///<アニメNo
	s8 anm_wait;			///<アニメウェイト
	s8 anm_dansa_wait;		///<アニメ段差ウェイト
}ROLOCAL_DONCHOU_UP;

///どんちょうを下げるローカル構造体
typedef struct{
	CONRES_PROC_WORK *rpw;
	CORDER_HEAD req_head;
	CONTEST_ORDER_WORK *cow;
	
	u8 seq;

	s8 anm_line;			///<アニメ書き換えの基本ライン
	u8 anm_no;				///<アニメNo
	s8 anm_wait;			///<アニメウェイト
	s8 anm_dansa_wait;		///<アニメ段差ウェイト
}ROLOCAL_DONCHOU_DOWN;

///会話メッセージの表示
typedef struct{
	CONRES_PROC_WORK *rpw;
	CORDER_HEAD req_head;
	CONTEST_ORDER_WORK *cow;
	
	u8 seq;
	u8 breeder_no;
	u8 close_wait;
	
	CRTAG_PARAM a_talk_tagpara;		///<ノーマル会話：タグ展開用パラメータ
	u8 a_talk_id;					///<ノーマル会話ID(A_TALK_CONRES_???)
	u8 a_talk_bmpwin_close_wait;	///<メッセージを表示しきってからウィンドウを閉じるまでのwait
	u8 a_talk_bmpwin_not_close;		///<TRUE:ウィンドウを閉じずに終了
	u8 a_talk_bmpwin_not_open;		///<TRUE:ウィンドウ描画を行わない
}ROLOCAL_TALK_PUT;

///結果発表画面に切り替え
typedef struct{
	CONRES_PROC_WORK *rpw;
	CORDER_HEAD req_head;
	CONTEST_ORDER_WORK *cow;
	
	u8 seq;
}ROLOCAL_RESULT_CHANGE;

///順位発表
typedef struct{
	CONRES_PROC_WORK *rpw;
	CORDER_HEAD req_head;
	CONTEST_ORDER_WORK *cow;

	u8 seq;
	u8 ranking[BREEDER_MAX];		///<順位(1位から順にブリーダー番号が入ります)
	u8 end_count;					///<発表が済んだブリーダーの数をカウント
	s16 wait;
}ROLOCAL_RANKING_ANNOUNCE;

///優勝したポケモンの登場演出
typedef struct{
	CONRES_PROC_WORK *rpw;
	CORDER_HEAD req_head;
	CONTEST_ORDER_WORK *cow;
	
	u8 seq;
	u8 victory_breeder;			///<優勝したブリーダーの番号
	u8 wnd_end_flag;			///<ウィンドウ開け閉じエフェクト終了受け取り用ワーク
	u8 poke_end_flag;			///<ポケモン登場エフェクト終了受け取り用ワーク
	s16 wait;
}ROLOCAL_VICTORY_EFF;

///メーターを伸ばす
typedef struct{
	CONRES_PROC_WORK *rpw;
	CORDER_HEAD req_head;
	CONTEST_ORDER_WORK *cow;
	
	u8 seq;
	u8 meter_type;				///<伸ばすメーターの種類(CONGAME_???)
	s16 wait;
	s16 max_meter_dot[BREEDER_MAX];	///<伸ばす最大ドット数
	s16 now_dot[BREEDER_MAX];		///<現在のドット数
}ROLOCAL_METER;

///結果発表画面フェードアウト
typedef struct{
	CONRES_PROC_WORK *rpw;
	CORDER_HEAD req_head;
	CONTEST_ORDER_WORK *cow;
	
	u8 seq;
	s16 wait;
}ROLOCAL_FADEOUT;


//==============================================================================
//	外部関数宣言
//==============================================================================
extern void ConresOrder_WorkInit(CONRES_PROC_WORK *rpw);


#endif	//__RES_ORDER_H__

