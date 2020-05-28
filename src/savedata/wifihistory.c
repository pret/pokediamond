//============================================================================================
/**
 * @file	wifihistory_local.h
 * @brief
 * @date	2006.03.25
 */
//============================================================================================


#include "savedata/savedata.h"
#include "savedata/wifihistory.h"
#include "wifihistory_local.h"

#include "gflib/assert.h"

//============================================================================================
//============================================================================================


//============================================================================================
//
//	セーブデータシステムが依存する関数
//
//============================================================================================
//----------------------------------------------------------
/**
 * @brief	WiFi通信履歴ワークのサイズ取得
 * @return	int		サイズ（バイト単位）
 */
//----------------------------------------------------------
int WIFIHISTORY_GetWorkSize(void)
{
	return sizeof(WIFI_HISTORY);
}

//----------------------------------------------------------
/**
 * @brief	WiFi通信履歴ワークの初期化
 * @param	hist
 * @return	WIFI_HISTORY	取得したワークへのポインタ
 */
//----------------------------------------------------------
void WIFIHISTORY_Init(WIFI_HISTORY * hist)
{
	MI_CpuClear32(hist, sizeof(WIFI_HISTORY));
}

//============================================================================================
//============================================================================================
//----------------------------------------------------------
/**
 * @brief	WiFi通信履歴セーブデータの取得
 * @param	sv		セーブデータへのポインタ
 * @return	WIFI_HISTORYデータへのポインタ
 */
//----------------------------------------------------------
WIFI_HISTORY * SaveData_GetWifiHistory(SAVEDATA * sv)
{
	return (WIFI_HISTORY*)SaveData_Get(sv, GMDATA_ID_WIFIHISTORY);
}

//============================================================================================
//============================================================================================
//----------------------------------------------------------
/**
 * @brief	自分の国、地域をセット
 * @param	wh			WIFI履歴データへのポインタ
 * @param	nation		国指定コード
 * @param	area		地域指定コード
 */
//----------------------------------------------------------
void WIFIHISTORY_SetMyNationArea(WIFI_HISTORY * wh, int nation, int area)
{
	GF_ASSERT(nation < WIFI_NATION_MAX);
	GF_ASSERT(area < WIFI_AREA_MAX);
	wh->my_nation = nation;
	wh->my_area = area;
	WIFIHISTORY_SetStat(wh, nation, area, WIFIHIST_STAT_MINE);
}

//----------------------------------------------------------
/**
 * @brief	自分の国コードを取得
 * @param	wh			WIFI履歴データへのポインタ
 * @return	int			国指定コード
 */
//----------------------------------------------------------
int WIFIHISTORY_GetMyNation(const WIFI_HISTORY * wh)
{
	return wh->my_nation;
}

//----------------------------------------------------------
/**
 * @brief	自分の地域コードを取得
 * @param	wh			WIFI履歴データへのポインタ
 * @return	int			地域指定コード
 */
//----------------------------------------------------------
int WIFIHISTORY_GetMyArea(const WIFI_HISTORY * wh)
{
	return wh->my_area;
}

//----------------------------------------------------------
/**
 * @brief	状態コードの取得
 * @param	wh			WIFI履歴データへのポインタ
 * @param	nation		国指定コード
 * @param	area		地域指定コード
 * @return	WIFIHIST_STAT	状態指定ID
 */
//----------------------------------------------------------
WIFIHIST_STAT WIFIHISTORY_GetStat(const WIFI_HISTORY * wh, int nation, int area)
{
	WIFIHIST_STAT stat;
	GF_ASSERT(nation < WIFI_NATION_MAX);
	GF_ASSERT(area < WIFI_AREA_MAX);

	if (nation == 0) {
		return WIFIHIST_STAT_NODATA;
	}
	stat = (wh->data[(nation - 1) * NATION_DATA_SIZE + area / 4] >> ((area % 4) * 2)) & 3;

	return stat;
}

//----------------------------------------------------------
/**
 * @param	wh			WIFI履歴データへのポインタ
 * @param	nation		国指定コード
 * @param	area		地域指定コード
 * @param	stat		状態指定ID
 */
//----------------------------------------------------------
void WIFIHISTORY_SetStat(WIFI_HISTORY * wh, int nation, int area, WIFIHIST_STAT stat)
{
	u8 * p;
	u8 mask = 3;
	u8 data;

	GF_ASSERT(stat < WIFIHIST_STAT_MAX);
	GF_ASSERT(nation < WIFI_NATION_MAX);
	GF_ASSERT(area < WIFI_AREA_MAX);

	if (nation == 0) {
		return;
	}
	p = &wh->data[(nation - 1) * NATION_DATA_SIZE + area / 4];

	*p &= ((mask << ((area % 4) * 2))^0xff);
	*p |= stat << ((area % 4) * 2);
	
	if (nation != WIFI_NATION_JAPAN) {
		WIFIHISTORY_SetWorldFlag(wh, TRUE);
	}
}


//----------------------------------------------------------
/**
 * @brief	世界モードかどうかのフラグ取得
 * @param	wh			WIFI履歴データへのポインタ
 * @return	BOOL		TRUEのとき、世界モード
 */
//----------------------------------------------------------
BOOL WIFIHISTORY_GetWorldFlag(const WIFI_HISTORY * wh)
{
	return wh->world_flag;
}


//----------------------------------------------------------
/**
 * @brief	世界モードのフラグセット
 * @param	wh			WIFI履歴データへのポインタ
 * @param	flag		設定する値（TRUE/FALSE）
 */
//----------------------------------------------------------
void WIFIHISTORY_SetWorldFlag(WIFI_HISTORY * wh, BOOL flag)
{
	wh->world_flag = flag;
}


//----------------------------------------------------------
/**
 * @brief	日付更新で内容更新
 * @param	wh			WIFI履歴データへのポインタ
 */
//----------------------------------------------------------
void WIFIHISTORY_Update(WIFI_HISTORY * wh)
{
	int i, j;
	u8 data;
	for (i = 0; i < (WIFI_NATION_MAX - 1) * NATION_DATA_SIZE; i++) {
		data = wh->data[i];
		for (j = 0; j < 8; j+=2) {
			if (((data >> j) & 3) == WIFIHIST_STAT_NEW) {
				data &= ((3 << j)^0xff);
				data |= (WIFIHIST_STAT_EXIST << j);
			}
		}
		wh->data[i] = data;
	}
}


