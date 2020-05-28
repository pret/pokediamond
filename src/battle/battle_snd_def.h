//==============================================================================
/**
 * @file	battle_snd_def.h
 * @brief	戦闘の効果音設定ファイル
 * @author	matsuda
 * @date	2006.03.28(火)
 */
//==============================================================================
#ifndef __BATTLE_SND_DEF_H__
#define __BATTLE_SND_DEF_H__

///戦闘入力画面カーソル移動音
#define BCURSOR_MOVE_SE			(SEQ_SE_DP_SELECT)
///先頭入力画面：コマンド選択ウィンドウスライドイン
#define BCOMMAND_SLIDEIN		(SEQ_SE_DP_SLIDEIN)

///< エンカウントエフェクト
#define BECEFF_GRASS_01			(SEQ_SE_DP_PASA2)
#define BECEFF_GRASS_02			(SEQ_SE_DP_PASA3)

///<技の威力SE
#define	BSE_HIT_NORMAL			(SEQ_SE_DP_KOUKA_M)
#define	BSE_HIT_BATSUGUN		(SEQ_SE_DP_KOUKA_H)
#define	BSE_HIT_IMAHITOTSU		(SEQ_SE_DP_KOUKA_L)

///<タッチパネルプッシュ音
#define	BSE_TP_DECIDE			(SEQ_SE_DP_DECIDE)

///<経験値取得音
#define	BSE_EXP_GET				(SEQ_SE_DP_EXP)

///<経験値MAX音
#define	BSE_EXP_MAX				(SEQ_SE_DP_EXPMAX)

///<ポケモン気絶
//#define	BSE_POKE_DEAD		(SEQ_SE_DP_POKE_DEAD)
//#define	BSE_POKE_DEAD		(SEQ_SE_DP_POKE_DEAD2)
#define	BSE_POKE_DEAD		(SEQ_SE_DP_POKE_DEAD3)

///<ボール開く
#define	BSE_BALL_OPEN			(SEQ_SE_DP_BOWA2)

///<ボール投げる
#define	BSE_BALL_THROW			(SEQ_SE_DP_NAGERU)

///<ボールHIT
//#define	BSE_BALL_HIT		(SEQ_SE_DP_KON)
//#define	BSE_BALL_HIT		(SEQ_SE_DP_BOWA2)
#define	BSE_BALL_HIT			(SEQ_SE_DP_KON)
#define	BSE_BALL_HIT_OPEN		(SEQ_SE_DP_BOWA4)		//KON + BOWA2 + SUIKOMU

///<ポケモンボールに吸い込み
#define	BSE_BALL_INHALE			(SEQ_SE_DP_SUIKOMU)

///<ポケモンボールに吸い込み
#define	BSE_POKEMON_GET			(SEQ_SE_DP_GETTING)

///<ポケモンボールゆれ
#define	BSE_BALL_SHAKE			(SEQ_SE_DP_BOWA)

///<HP少
#define	BSE_PINCH				(SEQ_SE_DP_HINSI)

///<にげる
#define	BSE_ESCAPE				(SEQ_SE_DP_NIGERU2)

///<回復
#define	BSE_KAIHUKU				(SEQ_SE_DP_KAIFUKU)

///<送り音
#define	BSE_OKURI				(SEQ_SE_DP_SELECT)

///<サファリ終了音
#define	BSE_SAFARI_END			(SEQ_SE_DP_PINPON)

///<サファリゾーンでボール以外を投げる
#define	BSE_SAFARI_THROW		(SEQ_SE_DP_NAGERU)

///<フォルムチェンジエフェクトのモザイクオン
#define	BSE_MOSAIC_ON			(SEQ_SE_DP_W100)

///<フォルムチェンジエフェクトのモザイクオフ
#define	BSE_MOSAIC_OFF			(SEQ_SE_DP_W107)

//--------------------------------------------------------------
//	手持ちゲージ
//--------------------------------------------------------------
///手持ちゲージ：手持ちゲージIN
#define BSE_TB_START			(SEQ_SE_DP_TB_START)
///手持ちゲージ：中身が入っているボール
#define BSE_TB_KON				(SEQ_SE_DP_TB_KON)
///手持ちゲージ：中身が空のボール
#define BSE_TB_KARA				(SEQ_SE_DP_TB_KARA)



#ifndef __ASM_NO_DEF_

#include "system/snd_tool.h"

#endif __ASM_NO_DEF_

#endif	//__BATTLE_SND_DEF_H__
