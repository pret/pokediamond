
//============================================================================================
/**
 * @file	server.h
 * @bfief	戦闘サーバプログラム
 * @author	HisashiSogabe
 * @date	05.05.24
 */
//============================================================================================

#ifndef __SERVER_H_
#define __SERVER_H_

#include	"battle/battle_common.h"

#define	SERVER_QUE_TIME_OUT		(60*30)	///<ServerQueCheck時のタイムアウトカウント（60秒）

//ServerSequenceTblのシーケンスナンバー
enum{
	SERVER_POKEMON_PARAM_GET_NO,		///<ポケモンパラメータをサーバワークにゲット
	SERVER_ENCOUNT_SET_NO,				///<エンカウント処理
	SERVER_TRAINER_MESSAGE_NO,			///<戦闘中にトレーナーが出てきてメッセージ表示
	SERVER_POKE_APPEAR_CHECK_NO,		///<ポケモン登場時にチェックする項目
	SERVER_COMMAND_SELECT_INIT_NO,		///<コマンド選択処理初期化
	SERVER_COMMAND_SELECT_NO,			///<コマンド選択処理
	SERVER_AGI_CALC_NO,					///<素早さ計算処理
	SERVER_BEFORE_ACT_NO,				///<動作前処理
	SERVER_ACTION_BRANCH_NO,			///<動作分岐処理
	SERVER_FIELD_CONDITION_CHECK_NO,	///<場にかかっている戦闘効果チェック
	SERVER_POKE_CONDITION_CHECK_NO,		///<ポケモンにかかっている戦闘効果チェック
	SERVER_SIDE_CONDITION_CHECK_NO,		///<ポケモンにかかっている戦闘効果チェック（側にかかっている効果）
	SERVER_TURN_END_NO,					///<戦闘ターン終了処理

	SERVER_FIGHT_COMMAND_NO,			///<たたかう動作処理
	SERVER_ITEM_COMMAND_NO,				///<道具使用処理
	SERVER_POKEMON_COMMAND_NO,			///<ポケモン選択処理
	SERVER_ESCAPE_COMMAND_NO,			///<にげる動作処理

	SERVER_SAFARI_BALL_NO,				///<サファリボール投げる処理
	SERVER_SAFARI_ESA_NO,				///<サファリエサ投げる処理
	SERVER_SAFARI_DORO_NO,				///<サファリドロ投げる処理
	SERVER_SAFARI_YOUSUMI_NO,			///<サファリ様子見処理

	SERVER_WAZA_SEQUENCE_NO,			///<技シーケンス実行
	SERVER_WAZA_BEFORE_NO,				///<技前処理
	SERVER_WAZA_OUT_CHECK_NO,			///<技発動チェック
	SERVER_ADD_STATUS_DIRECT_CHECK_NO,	///<追加効果チェック（直接追加のみ）
	SERVER_WAZA_HAZURE_MESSAGE_NO,		///<当たらなかった系メッセージ表示
	SERVER_WAZA_OUT_NO,					///<技発動処理
	SERVER_HP_CALC_NO,					///<HP計算
	SERVER_WAZA_OUT_AFTER_MESSAGE_NO,	///<技がでた後のいろいろなメッセージ表示
	SERVER_ADD_STATUS_CHECK_NO,			///<追加効果チェック（直接追加以外）
	SERVER_WAZA_OUT_AFTER_KOUKA_NO,		///<技がでた後のいろいろな効果チェック
	SERVER_RENZOKU_CHECK_NO,			///<連続攻撃のチェック
	SERVER_SINKURO_CHECK_NO,			///<シンクロチェック
	SERVER_KIZETSU_EFFECT_NO,			///<気絶エフェクト
	SERVER_LOOP_CHECK_NO,				///<複数体当たる技のチェック
	SERVER_JIBAKU_EFFECT_NO,			///<じばくによる気絶エフェクト
	SERVER_WAZA_HIT_AFTER_CHECK_NO,		///<技がヒットした後のチェック
	SERVER_GET_EXP_EFFECT_NO,			///<経験値取得チェック
	SERVER_WAZA_NO_BUFFER_SET_NO,		///<技ナンバーをバッファへ格納
	SERVER_WAZA_END_NO,					///<技シーケンス終了

	SERVER_POKE_RESHUFFLE_AFTER_NO,		///<ポケモンいれかえ後シーケンス

	SERVER_WIN_LOSE_NO,					///<戦闘勝敗シーケンス

//	SERVER_QUE_CHECK_NO,				///<サーバキューをチェックして終了を待つ

	SERVER_FIGHT_END_NO,				///<戦闘終了
	SERVER_FIGHT_END_WAIT_NO			///<戦闘終了（通信対戦時の待ち）
};

extern	void	*ServerInit(BATTLE_WORK *bw);
extern	int		ServerMain(BATTLE_WORK *battle_work,SERVER_PARAM *server_param);
extern	void	ServerEnd(SERVER_PARAM *server_param);

extern	void	ServerHitCheckAct(BATTLE_WORK *bw,SERVER_PARAM *sp,int attack,int defence,int waza_no);

#endif __SERVER_H_
