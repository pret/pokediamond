/**
 *	@file	comm_command_nutmixer.c
 *	@brief	木の実ミキサー　通信コマンドテーブル
 *	@author	Miyuki Iwasawa
 *	@date	06.04.06
 *	@data	06.05.23	tomoya 変更
 */

#include "common.h"
#include "communication/communication.h"
#include "comm_command_nutmixer_func.h"
#include "comm_command_nutmixer.h"

#include "include/savedata/poruto_util.h"


// 対応するコールバック関数
static const CommPacketTbl _CommNutMixerPacketTbl[] = {
	//-------------------------------------
	//　ゲーム用
	//=====================================
	// 同期用	
	{ CommNutMixerGameSysStart, CommNutMixerGetZeroSize, NULL },			///< ミキサー開始			親ー＞子
	{ CommNutMixerGameEnd, CommNutMixerGetZeroSize, NULL },			///< ゲーム終了				親ー＞子
	// データ受信用
	{ CommNutMixerGameBeforeDataKo, CommNutMixerGetGameBeforeKoSize, NULL },		///< プレイヤー名		親ー＞子
	{ CommNutMixerGameBeforeData, CommNutMixerGetGameBeforeSize, NULL },		///< プレイヤー名		子ー＞親
	{ CommNutMixerGameData, CommNutMixerGetGameSize, NULL },		///< ゲームデータ		親＜ー＞子
	{ CommNutMixerGameResultData, CommNutMixerGetGameResultSize, NULL },	///< 結果データ			親ー＞子
	{ CommNutMixerPorutoData, PorutoData_GetWorkSize, NULL },	///< ポルトデータ			親ー＞子
	{ CommNutMixerGameNextDataKo, CommNutMixerGetOneSize, NULL },	///< 	ゲーム終了データ	親ー＞子
	{ CommNutMixerGameNextData, CommNutMixerGetOneSize, NULL },		///< ゲーム終了データ		子ー＞親

};

//----------------------------------------------------------------------------
/**
 *	@brief		コマンドテーブルを取得
 */
//-----------------------------------------------------------------------------
const CommPacketTbl* NutMixer_CommCommandTclGet( void )
{
	return _CommNutMixerPacketTbl;
}

//----------------------------------------------------------------------------
/**
 *	@brief	コマンドテーブル要素数を取得
 */
//-----------------------------------------------------------------------------
int NutMixer_CommCommandTblNumGet( void )
{
    return sizeof(_CommNutMixerPacketTbl)/sizeof(CommPacketTbl);
}
