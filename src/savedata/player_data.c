//============================================================================================
/**
 * @file	player_data.c
 * @date	2006.06.01
 * @author	tamada
 * @brief	プレイヤー関連セーブデータ
 */
//============================================================================================

#include "savedata/savedata.h"
#include "savedata/playerdata_local.h"

#include "gflib/assert.h"

#include "gflib/msg_print.h"
#include "system/buflen.h"

#include "savedata/mystatus.h"
#include "mystatus_local.h"
#include "config_local.h"
#include "savedata/config.h"
#include "mystatus_local.h"
#include "savedata/mystatus.h"
#include "coin_local.h"
#include "savedata/coin.h"
#include "playtime_local.h"
#include "savedata/playtime.h"

//============================================================================================
//============================================================================================
//------------------------------------------------------------------
/**
 * @brief	プレイヤーセーブデータの定義
 */
//------------------------------------------------------------------
struct PLAYER_DATA {
	CONFIG config;
	MYSTATUS mystatus;
	COIN mycoin;
	PLAYTIME playtime;
};

//============================================================================================
//
//		主にセーブシステムから呼ばれる関数
//
//============================================================================================
//------------------------------------------------------------------
/**
 * @brief	セーブデータサイズの取得
 * @return	int		プレイヤーセーブデータのサイズ
 */
//------------------------------------------------------------------
int PLAYERDATA_GetWorkSize(void)
{
	return sizeof(PLAYER_DATA);
}

//------------------------------------------------------------------
/**
 * @brief	セーブデータ初期化
 * @param	pd		プレイヤーセーブデータへのポインタ
 */
//------------------------------------------------------------------
void PLAYERDATA_Init(PLAYER_DATA * pd)
{
	MI_CpuClearFast(pd, sizeof(PLAYER_DATA));
	/* 以下に個別部分の初期化処理をおく */
	CONFIG_Init(&pd->config);
	MyStatus_Init(&pd->mystatus);
	COIN_Init(&pd->mycoin);
	PLAYTIME_Init(&pd->playtime);
}

//============================================================================================
//
//	セーブデータ取得のための関数
//
//============================================================================================
//---------------------------------------------------------------------------
/**
 * @brief	自分状態データへのポインタ取得
 * @param	sv			セーブデータ保持ワークへのポインタ
 * @return	MYSTATUS	自分状態保持ワークへのポインタ
 */
//---------------------------------------------------------------------------
MYSTATUS * SaveData_GetMyStatus(SAVEDATA * sv)
{
	PLAYER_DATA * pd;
	pd = SaveData_Get(sv, GMDATA_ID_PLAYER_DATA);
	return &pd->mystatus;
}

//---------------------------------------------------------------------------
/**
 * @brief	設定情報データへのポインタ取得
 * @param	sv			セーブデータ保持ワークへのポインタ
 * @return	CONFIG		設定情報保持ワークへのポインタ
 */
//---------------------------------------------------------------------------
CONFIG * SaveData_GetConfig(SAVEDATA * sv)
{
	PLAYER_DATA * pd;
	pd = SaveData_Get(sv, GMDATA_ID_PLAYER_DATA);
	return &pd->config;
}

//---------------------------------------------------------------------------
/**
 * @brief	コインデータへのポインタを取得
 * @param	sv			セーブデータ保持ワークへのポインタ
 * @return	coin	コインデータへのポインタ
 */
//---------------------------------------------------------------------------
COIN * SaveData_GetMyCoin(SAVEDATA * sv)
{
	PLAYER_DATA * pd;
	pd = SaveData_Get(sv, GMDATA_ID_PLAYER_DATA);
	return &pd->mycoin;
}

//---------------------------------------------------------------------------
/**
 * @brief	プレイ時間データへのポインタを取得
 * @param	sv			セーブデータ保持ワークへのポインタ
 * @return	playtime	プレイ時間データへのポインタ
 */
//---------------------------------------------------------------------------
PLAYTIME * SaveData_GetPlayTime(SAVEDATA * sv)
{
	PLAYER_DATA * pd;
	pd = SaveData_Get(sv, GMDATA_ID_PLAYER_DATA);
	return &pd->playtime;
}

