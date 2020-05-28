//==============================================================================
/**
 * @file	actin_order.h
 * @brief	演技力部門：命令を各スタッフに送信のヘッダ
 * @author	matsuda
 * @date	2005.11.29(火)
 */
//==============================================================================
#ifndef __ACTIN_ORDER_H__
#define __ACTIN_ORDER_H__

#include "contest_order.h"

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
	AORDER_NO_SAMPLE,			///<サンプル
	AORDER_NO_ACTIN_EXIT,		///<演技力部門終了
	AORDER_NO_OPENING_EFFECT,	///<オープニングエフェクト
	AORDER_NO_ENDING_EFFECT,	///<エンディングエフェクト
	AORDER_NO_POKEMON_IN,		///<ポケモン登場
	AORDER_NO_POKEMON_OUT,		///<ポケモン退場
	AORDER_NO_WAZAEFFECT_BEFORE,	///<技エフェクトを出す前の処理
	AORDER_NO_WAZAEFFECT,		///<技エフェクト出す
	AORDER_NO_USER_SELECT,		///<技選択
	AORDER_NO_APPEAL_REVIEW,	///<技の評価(演出)
	AORDER_NO_APPEAL_FIRST,		///<技の評価(演出)
	AORDER_NO_APPEAL_KOUKA,		///<技の効果(演出)
	AORDER_NO_APPEAL_SPECIAL_KOUKA,	///<技の特別効果(演出)
	AORDER_NO_APPEAL_VOLTAGE,		///<技のボルテージ(演出)
	AORDER_NO_REVIEW_AFTER,			///<全員演技終了後に発生する効果(演出)
	AORDER_NO_REVIEW_END,			///<全ての演技終了後に発生する効果(演出)
	AORDER_NO_JUDGE_SUFFER,			///<審判被り(演出)
	AORDER_NO_JUDGE_WAZA,			///<審判被り技効果
	AORDER_NO_JUDGE_COMMENT,		///<審判コメント
	AORDER_NO_TURN_PARAM_UPDATE,	///<ターン終了後のパラメータ送受信
	AORDER_NO_TALK,					///<会話メッセージ表示
	AORDER_NO_TURNEND_EFF,			///<ターン終了後のエフェクト実行
};


//==============================================================================
//	構造体定義
//==============================================================================
///オープニングエフェクト：ローカル構造体
typedef struct{
	ACTIN_PROC_WORK *apw;
	CORDER_HEAD req_head;
	u16 wait;
	u8 audience_anm_end;
	u8 seq;
}AOLOCAL_OPENING_EFF;

///エンディングエフェクト：ローカル構造体
typedef struct{
	ACTIN_PROC_WORK *apw;
	CORDER_HEAD req_head;
	u8 seq;
	u16 wait;
	u8 audience_anm_end;
	
	ATAG_PARAM a_talk_tagpara;
	u8 a_talk_id;
}AOLOCAL_ENDING_EFF;

///ポケモン登場・退場ローカル構造体
typedef struct{
	ACTIN_PROC_WORK *apw;
	CORDER_HEAD req_head;
	s32 x;
	s32 y;
	u8 seq;
	u8 breeder_no;
	u8 slide_end;
	s16 wait;
}AOLOCAL_POKE_INOUT;

///技エフェクト実行前：ローカル構造体
typedef struct{
	ACTIN_PROC_WORK *apw;
	CORDER_HEAD req_head;
	u8 seq;
	u8 breeder_no;
	u8 judge_no;
	u8 reaction_end;
	u8 judge_reaction_type;
	u8 wait;
	u8 audience_anm_end;
	
	ATAG_PARAM a_talk_tagpara;
	u8 a_talk_id;
}AOLOCAL_WAZAEFF_BEFORE;

///技エフェクト：ローカル構造体
typedef struct{
	ACTIN_PROC_WORK *apw;
	CORDER_HEAD req_head;
	u8 seq;
	u8 breeder_no;
	u16 waza_no;
	u8 panel_end;

	ACTIN_ADVANCE_PARAM aap;

	ATAG_PARAM a_talk_tagpara;
	u8 a_talk_id;
	ATAG_PARAM after_a_talk_tagpara;
	u8 after_a_talk_id;
	
	CON_WAZAEFF_PARAM wazapara;
}AOLOCAL_WAZAEFF;

///ユーザーが選択した技番号、審判番号のデータ
typedef struct{
	u16 waza_no;
	u16 judge_no;
}USER_SELECT_DATA;

///技選択：ローカル構造体
typedef struct{
	ACTIN_PROC_WORK *apw;
	CORDER_HEAD req_head;
	u8 seq;
	u8 breeder_no;
	u8 final_turn_se;
	USER_SELECT_DATA usd;
}AOLOCAL_WAZASELECT;

///出した技の評価(演出)：ローカル構造体
typedef struct{
	ACTIN_PROC_WORK *apw;
	CORDER_HEAD req_head;
	u8 seq;
	u8 breeder_no;
	u8 breeder_pos;
//	u8 judge_no;
	s8 wait;
	s8 work;
	u8 audience_anm_end;
	u8 effect_count;
	
	ACTIN_ADVANCE_PARAM aap;
	s16 point;
	s16 voltage;
	s16 voltage_point;
	
	u8 reaction_end;
	
	u8 count;
	
	VOLTAGE_POINT_ANIME_WORK *vaw;
}AOLOCAL_APPEALREVIEW;

///審判被り：ローカル構造体
typedef struct{
	ACTIN_PROC_WORK *apw;
	CORDER_HEAD req_head;
	u8 seq;
	
	s8 wait;
	s8 work;
	
	ACTIN_ADVANCE_PARAM aap;
	s16 point;
	
	u8 count;
	u8 reaction_end;
	
	VOLTAGE_POINT_ANIME_WORK *vaw;
}AOLOCAL_JUDGESUFFER;

///ターン終了後のエフェクト：ローカル構造体
typedef struct{
	ACTIN_PROC_WORK *apw;
	CORDER_HEAD req_head;
	CONTEST_ORDER_WORK *cow;
	
	PANEL_FLASH_WORK *panel_flash[BREEDER_MAX];
	
	u8 seq;
	u8 wait;
	
	u8 breeder_pos;
	u8 effect_count[BREEDER_MAX];
	u8 audience_anm_end;
}AOLOCAL_TURNEND_EFF;

///会話メッセージの表示
typedef struct{
	ACTIN_PROC_WORK *apw;
	CORDER_HEAD req_head;
	CONTEST_ORDER_WORK *cow;
	
	u8 seq;
	u8 breeder_no;
	u8 close_wait;

	ATAG_PARAM a_talk_tagpara;		///<ノーマル会話：タグ展開用パラメータ
	u8 a_talk_id;					///<ノーマル会話ID(A_TALK_???)
	u8 a_talk_bmpwin_close_wait;	///<メッセージを表示しきってからウィンドウを閉じるまでのwait
	u8 a_talk_bmpwin_not_close;		///<TRUE:ウィンドウを閉じずに終了
}AOLOCAL_TALK_PUT;


//==============================================================================
//	外部関数宣言
//==============================================================================
extern void ActinOrder_WorkInit(ACTIN_PROC_WORK *apw);


#endif	//__ACTIN_ORDER_H__

