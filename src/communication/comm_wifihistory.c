//============================================================================================
/**
 * @file	comm_wifihistory.c
 * @bfief	地球儀登録処理
 * @author	Akito Mori
 * @date	06.05.02
 */
//============================================================================================

#include "common.h"
#include "communication/communication.h"
#include "communication/comm_wifihistory.h"

//==============================================================================
/**
 * $brief   地球儀情報を登録
 *
 * @param   wifiHistory		
 *
 * @retval  none		
 */
//==============================================================================
void Comm_WifiHistoryCheck( WIFI_HISTORY *wifiHistory )
{
	int i;
	int Nation,Area,region;
	MYSTATUS *status;
	int num = CommGetConnectNum();

	// デバッグバトルの時だとMYSTATUSが入っていないので登録処理はすべてとばすようにする
	if(CommInfoGetMyStatus(0)==NULL){
		return;
	}

	// 接続している人数分まわす
	for(i=0;i<num;i++){
		if(CommGetCurrentID()!=i){
			Nation = CommInfoGetMyNation(i);
			Area   = CommInfoGetMyArea(i);
			status = CommInfoGetMyStatus( i );
			region = MyStatus_GetRegionCode( status );

			// 国・地域コードを登録（ただし日本カートリッジ専用チェックあり）
			Comm_WifiHistoryDataSet( wifiHistory, Nation, Area, region );
		}
	}
}

//==============================================================================
/**
 * @brief   相手のカートリッジリージョン・国・地域コードから地球儀情報を登録する
 *
 * @param   wifiHistory		
 * @param   Nation		
 * @param   Area		
 * @param   langCode		
 *
 * @retval  none		
 */
//==============================================================================
void Comm_WifiHistoryDataSet( WIFI_HISTORY *wifiHistory, int Nation, int Area, int langCode )
{
	
#if (PM_LANG == LANG_JAPAN)
	// 相手のカートリッジが日本なのに
	if(langCode==LANG_JAPAN){
		// 違う国の地球儀コードを入れてきたら登録しない
		if(Nation!=WIFI_NATION_JAPAN){
			return;
		}
	}
#endif
	
	// 国・地域を登録
//	OS_Printf("no=%d\n", WIFIHISTORY_GetStat(wifiHistory, Nation, Area ));
	if(WIFIHISTORY_GetStat( wifiHistory, Nation, Area )==WIFIHIST_STAT_NODATA){
		WIFIHISTORY_SetStat( wifiHistory, Nation, Area, WIFIHIST_STAT_NEW );
	}
	

}