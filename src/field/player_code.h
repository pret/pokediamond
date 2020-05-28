//******************************************************************************
/**
 *
 * @file	player_code.h
 * @brief	自機シンボル参照　※スクリプト参照アリ　故にenum禁止
 * @author	kagaya
 * @data	05.08.03
 *
 */
//******************************************************************************
#ifndef PLAYER_CODE_H_FILE
#define PLAYER_CODE_H_FILE

//==============================================================================
//	define
//==============================================================================
//--------------------------------------------------------------
///	自機形態
//--------------------------------------------------------------
#define HERO_FORM_NORMAL 		(0x00)							///<2足
#define HERO_FORM_CYCLE			(0x01)							///<自転車
#define HERO_FORM_SWIM			(0x02)							///<波乗り
//以下描画識別 実際には設定されない
#define HERO_DRAWFORM_SP		(0x03)							///<秘伝技
#define HERO_DRAWFORM_WATER		(0x04)							///<水遣り
#define HERO_DRAWFORM_CONTEST	(0x05)							///<コンテスト
#define HERO_DRAWFORM_FISHING	(0x06)							///<釣り
#define HERO_DRAWFORM_POKETCH	(0x07)							///<ポケッチ
#define HERO_DRAWFORM_SAVE		(0x08)							///<セーブ
#define HERO_DRAWFORM_BANZAI	(0x09)							///<万歳

#define HERO_FORM_MAX (HERO_FORM_SWIM+1)

//自転車は一種類になりました
#define HERO_FORM_CYCLE_R (HERO_FORM_CYCLE)
#define HERO_FORM_CYCLE_D (HERO_FORM_CYCLE)

//--------------------------------------------------------------
///	リクエスト
//--------------------------------------------------------------
#define HERO_REQBIT_NON			(0)							///<リクエストなし
#define HERO_REQBIT_NORMAL		(1<<0)						///<２足移動に変更
#define HERO_REQBIT_CYCLE		(1<<1)						///<自転車移動に変更
#define HERO_REQBIT_SWIM		(1<<2)						///<波乗り移動に変更
#define HERO_REQBIT_UNDER_OFF	(1<<3)						///<足元判定を無効にする
#define HERO_REQBIT_WATER		(1<<4)						///<水遣り自機に変更する
#define HERO_REQBIT_FISHING		(1<<5)						///<釣り自機へ表示変更
#define HERO_REQBIT_POKETCH		(1<<6)						///<ポケッチ自機へ表示変更
#define HERO_REQBIT_SAVE		(1<<7)						///<セーブ自機へ表示変更
#define HERO_REQBIT_BANZAI		(1<<8)						///<万歳自機へ表示変更

#define HERO_REQBIT_MAX			(9)							///<リクエスト総数

#endif //PLAYER_CODE_H_FILE
