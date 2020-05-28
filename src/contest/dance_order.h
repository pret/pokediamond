//==============================================================================
/**
 * @file	dance_order.h
 * @brief	ビジュアル部門：命令送受信のヘッダ
 * @author	matsuda
 * @date	2005.12.13(火)
 */
//==============================================================================
#ifndef __DANCE_ORDER_H__
#define __DANCE_ORDER_H__


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
	DORDER_NO_SAMPLE,			///<サンプル
	DORDER_NO_DONCHOU_UP,		///<どんちょうを上げる
	DORDER_NO_DONCHOU_DOWN,		///<どんちょうを下げる
	DORDER_NO_OPENING_EFF,		///<オープニングエフェクト
	DORDER_NO_DANCE_EXIT,		///<ダンス部門終了
	DORDER_NO_DANCING,			///<ダンス実行
	DORDER_NO_ROTATION,			///<ローテーション
	DORDER_NO_BEFORE,			///<ダンス開始前
	DORDER_NO_AFTER,			///<ダンス終了後
	DORDER_NO_TALK,				///<会話メッセージ表示
	DORDER_NO_GAMEPARAM,		///<ゲームパラメータ更新
	DORDER_NO_MUSIC_START,		///<音楽開始
	DORDER_NO_END_EFFECT,		///<全員のダンス終了後のエフェクト処理
};


//==============================================================================
//	構造体定義
//==============================================================================
///ポケモンローテーション、各ブリーダー動作構造体
typedef struct{
	//TCB生成時にセットされているパラメータ
	POKEMON_PARAM *pp;			///<自分のポケモンのパラメータ
	SOFT_SPRITE *ss;			///<自分のポケモンソフトウェアスプライトへのポインタ
	CONTEST_IMC_WORK *imcwork;	///<自分のポケモンイメージクリップへのポインタ
	u8 now_rotation_pos;		///<現在のローテーション位置
	u8 next_rotation_pos;		///<次のローテーション位置
	u16 move_frame;				///<ローテーションの移動にかけるフレーム数

	//各ブリーダー動作TCB内で変更、セットするパラメータ
	s32 x;
	s32 y;
	s32 z;
	s32 add_x;
	s32 add_y;
	s32 add_z;
	u16 frame;					///<現在の経過フレーム数
	u8 seq;
	u8 end;						///<TRUE:次のローテーション位置に到達
}DOLOCAL_ROTATION_BREEDER;

///ポケモンローテーションローカル構造体
typedef struct{
	DANCE_PROC_WORK *dpw;
	CORDER_HEAD req_head;
	CONTEST_ORDER_WORK *cow;
	
	u8 seq;
	u8 light_fade_end[BREEDER_MAX];
	
	DOLOCAL_ROTATION_BREEDER sub_rb[BREEDER_MAX];
	DANCE_ADVANCE_PARAM dap;
}DOLOCAL_ROTATION;

///ダンスチェックワーク構造体
typedef struct{
	DANCE_PROC_WORK *dpw;
	u8 seq;
	u8 touch_wait;			///<タッチ後に次のタッチチェックが出来るまでのウェイトカウント
}DANCE_TOUCH_WORK;

///ダンスパラメータ送信タスクワーク
typedef struct{
	TCB_PTR tcb;			///<送信実行タスクのポインタ
	DANCE_PROC_WORK *dpw;
	DANCING_PARAM dancing_param;
	u8 ai;
	u8 req;			///<TRUE：送信リクエストがかかっている
}DANCING_SEND_WORK;

///メインダンスローカル構造体
typedef struct{
	DANCE_PROC_WORK *dpw;
	CORDER_HEAD req_head;
	CONTEST_ORDER_WORK *cow;
	
	u8 seq;
	u8 flash_flag;
	u8 back_dancer_light_flag;
	u16 frame;
	u8 loop;
	u8 touch_count;
	
	DANCE_ADVANCE_PARAM dap;
	DANCE_TOUCH_WORK dtw;
	
	DANCE_AI_WORK aiwork[BREEDER_MAX];		///<ダンス用AIワークへのポインタ
	DANCING_SEND_WORK *sendwork[BREEDER_MAX];	///<ダンスパラメータ送信タスクワークへのポインタ
}DOLOCAL_MAINDANCE;

///どんちょうを上げるローカル構造体
typedef struct{
	DANCE_PROC_WORK *dpw;
	CORDER_HEAD req_head;
	CONTEST_ORDER_WORK *cow;
	
	u8 seq;

	s8 anm_line;			///<アニメ書き換えの基本ライン
	u8 anm_no;				///<アニメNo
	s8 anm_wait;			///<アニメウェイト
	s8 anm_dansa_wait;		///<アニメ段差ウェイト
}DOLOCAL_DONCHOU_UP;

///どんちょうを下げるローカル構造体
typedef struct{
	DANCE_PROC_WORK *dpw;
	CORDER_HEAD req_head;
	CONTEST_ORDER_WORK *cow;
	
	u8 seq;

	s8 anm_line;			///<アニメ書き換えの基本ライン
	u8 anm_no;				///<アニメNo
	s8 anm_wait;			///<アニメウェイト
	s8 anm_dansa_wait;		///<アニメ段差ウェイト
}DOLOCAL_DONCHOU_DOWN;

///どんちょうを下げるローカル構造体
typedef struct{
	DANCE_PROC_WORK *dpw;
	CORDER_HEAD req_head;
	CONTEST_ORDER_WORK *cow;
	
	u8 seq;
	
	u8 end_flag;
	s16 wait;
}DOLOCAL_OPENING_EFF;

///ダンス開始前処理のローカル構造体
typedef struct{
	DANCE_PROC_WORK *dpw;
	CORDER_HEAD req_head;
	CONTEST_ORDER_WORK *cow;
	
	DANCE_ADVANCE_PARAM dap;
	u8 seq;
}DOLOCAL_BEFORE;

///ダンス終了後処理のローカル構造体
typedef struct{
	DANCE_PROC_WORK *dpw;
	CORDER_HEAD req_head;
	CONTEST_ORDER_WORK *cow;
	
	DANCE_ADVANCE_PARAM dap;
	u8 seq;
}DOLOCAL_AFTER;

///会話メッセージの表示
typedef struct{
	DANCE_PROC_WORK *dpw;
	CORDER_HEAD req_head;
	CONTEST_ORDER_WORK *cow;
	
	u8 seq;
	u8 breeder_no;
	u8 close_wait;
	
	DTAG_PARAM a_talk_tagpara;		///<ノーマル会話：タグ展開用パラメータ
	u8 a_talk_id;					///<ノーマル会話ID(A_TALK_DANCE_???)
	u8 a_talk_bmpwin_close_wait;	///<メッセージを表示しきってからウィンドウを閉じるまでのwait
	u8 a_talk_bmpwin_not_close;		///<TRUE:ウィンドウを閉じずに終了
}DOLOCAL_TALK_PUT;

///全員のダンス終了後のエフェクトなどのローカル構造体
typedef struct{
	DANCE_PROC_WORK *dpw;
	CORDER_HEAD req_head;
	CONTEST_ORDER_WORK *cow;

	DANCE_ADVANCE_PARAM dap;
	
	u32 wait;
	u8 seq;
}DOLOCAL_END_EFFECT;


//==============================================================================
//	外部関数宣言
//==============================================================================
extern void DanceOrder_WorkInit(DANCE_PROC_WORK *dpw);
extern int DanceTP_to_DanceStep(int dance_tp);
extern int DanceStep_to_TP(int dance_step);
extern void DancerReactionSet(int breeder_no, int reaction, u32 frame, u32 one_tempo_frame, 
	const DANCE_LAG_DATA *dld, DANCING_PARAM *param, const DANCING_PARAM *maindancer_record,
	int rotation_pos, int touch_count, int max_touch);
extern void DancingParamSendReqSet(DANCING_SEND_WORK *sendwork, const DANCING_PARAM *param);

//-- dance_ai.c --//
extern void DanceAI_Init(DANCE_AI_WORK *aiwork, int breeder_no, int rotation_pos, u32 random_seed, 
	int character);
extern void DanceAI_ParamClear(DANCE_AI_WORK *aiwork);
extern void DancdAI_MainDancerCalc(DANCE_PROC_WORK *dpw, DANCE_AI_WORK *aiwork, 
	u32 all_tempo_frame, u32 one_tempo_frame);
extern void DanceAI_Main(int now_frame_dancer, DANCE_PROC_WORK *dpw, DANCE_AI_WORK *aiwork, 
	u32 frame, u32 all_tempo_frame, u32 one_tempo_frame, const DANCE_MUSIC_DATA *musicdata,
	DANCING_SEND_WORK *sendwork);


#endif	//__DANCE_ORDER_H__

