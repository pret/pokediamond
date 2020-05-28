//==============================================================================
/**
 * @file	actin_snd_def.h
 * @brief	コンテスト：ビジュアル部門　SE定義ファイル
 * @author	matsuda
 * @date	2006.03.01(水)
 */
//==============================================================================
#ifndef __ACTIN_SND_DEF_H__
#define __ACTIN_SND_DEF_H__

#include "system/snd_tool.h"


///カーソル決定
#define ASE_DECIDE			(SEQ_SE_DP_DECIDE)
///入力画面カーソル移動音
#define ASE_CCURSOR_MOVE_SE			(SEQ_SE_DP_SELECT)

///ボルテージ上昇SE
#define ASE_VOLTAGE_UP		(SEQ_SE_DP_CON_002)	//(SEQ_SE_DP_CON_006)
///ボルテージ下降SE
#define ASE_VOLTAGE_DOWN		(SEQ_SE_DP_CON_001)	//(SEQ_SE_DP_CON_005)
///AP上昇SE
#define ASE_AP_UP			(SEQ_SE_DP_CON_003)	//(SEQ_SE_DP_CON_004)
///次アイコンを貼り付けた時のSE
#define ASE_NEXTICON			(SEQ_SE_DP_CON_004)
///観客盛り上がり時のSE
#define ASE_AUDIENCE			(SEQ_SE_DP_CON_007)

//審判リアクションアイコン点灯時になるSE：指名
#define ASE_ICON_NOMINATION		(SEQ_SE_DP_CON_003)
//審判リアクションアイコン点灯時になるSE：被り
#define ASE_ICON_WEAR			(SEQ_SE_DP_CON_001)
//審判リアクションアイコン点灯時になるSE：ボルテージ
#define ASE_ICON_VOLTAGE		(SEQ_SE_DP_DECIDE)
//審判リアクションアイコン点灯時になるSE：ボルテージMAX
#define ASE_ICON_VOLTAGE_MAX	(SEQ_SE_DP_DECIDE)

///審判被りの審判の反応時：+0
#define ASE_JUDGE_SUFFER_FAILED		(SEQ_SE_DP_CON_001)
///審判被りの審判の反応時：+1
#define ASE_JUDGE_SUFFER_SMALL		(SEQ_SE_DP_CON_021)
///審判被りの審判の反応時：+2
#define ASE_JUDGE_SUFFER_MIDDLE		(SEQ_SE_DP_CON_022)
///審判被りの審判の反応時：+3
#define ASE_JUDGE_SUFFER_BIG		(SEQ_SE_DP_CON_023)

///APハートがパネルに飲み込まれる時の音
#define ASE_APHEART_PANEL_IN	(SEQ_SE_DP_SELECT5)
///ボルテージがパネルに飲み込まれる時の音
#define ASE_VOLTAGE_PANEL_IN	(SEQ_SE_DP_SELECT5)
///ボルテージMAXでエフェクト起動時審判ボックスから☆が出てくる時に鳴らす音
#define ASE_VOLTAGE_EFF_START	(SEQ_SE_DP_W234)
///下降しきったボルテージがパネルに直進して飛んでいく時に鳴らす音
#define ASE_VOLTAGE_STRAIGHT_MOVE	(SEQ_SE_DP_CON_013)

///最終ターンを知らせる音
#define ASE_FINAL_TURN			(SEQ_SE_DP_CON_029)
///自分のポケモンが登場
#define ASE_MY_POKEMON			(SEQ_SE_DP_CON_031)
///審判の「そこまでー！」の時
#define ASE_ACTIN_STOP			(SEQ_SE_DP_CON_032)


#endif	//__ACTIN_SND_DEF_H__
