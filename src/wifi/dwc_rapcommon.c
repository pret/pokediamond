//=============================================================================
/**
 * @file	dwc_rapcommon.c
 * @bfief	DWCラッパー。常駐モジュールに置くもの
 * @author	kazuki yoshihara  -> k.ohno改造
 * @date	06/02/23
 */
//=============================================================================

#include "common.h"
#include <dwc.h>
#include "wifi/dwc_rap.h"

//==============================================================================
/**
 * DWCライブラリ初期化
 * @param   WIFI_LIST  ユーザーデータがない場合作成
 * @retval  DS本体に保存するユーザIDのチェック・作成結果。
 */
//==============================================================================
int mydwc_init(int heapID)
{
	int ret;
    u8* pWork;
    u8* pTemp;

    pWork = sys_AllocMemory(heapID, DWC_INIT_WORK_SIZE+32);
    pTemp = (u8 *)( ((u32)pWork + 31) / 32 * 32 );
    // DWCライブラリ初期化
    ret = DWC_Init( pTemp );
    sys_FreeMemoryEz(pWork);

	return ret;
}


//==============================================================================
/**
 * DWC  UserDataを作る
 * @param   WIFI_LIST  ユーザーデータがない場合作成
 * @retval  DS本体に保存するユーザIDのチェック・作成結果。
 */
//==============================================================================
void mydwc_createUserData( WIFI_LIST *pWifiList )
{
    // ユーザデータ作成をする。    
    DWCUserData *userdata = WifiList_GetMyUserInfo(pWifiList);
    if( !DWC_CheckUserData( userdata ) ){
        DWC_CreateUserData( userdata, 'ADAJ' );
        DWC_ClearDirtyFlag( userdata );
        OS_TPrintf("WIFIユーザデータを作成\n");
    }
}

//==============================================================================
/**
 * 自分のGSIDを取得する
 * @param   WIFI_LIST  
 * @retval  ０と－１は失敗   正の値は成功
 */
//==============================================================================

int mydwc_getMyGSID(WIFI_LIST *pWifiList)
{
    DWCUserData *userdata = WifiList_GetMyUserInfo(pWifiList);
    DWCFriendData friendData;

    DWC_CreateExchangeToken(userdata,&friendData);
    return DWC_GetGsProfileId( userdata,&friendData);
}

//==============================================================================
/**
 * 自分のGSIDが正しいのか検査する
 * @param   WIFI_LIST  
 * @retval  TRUEが成功
 */
//==============================================================================

BOOL mydwc_checkMyGSID(SAVEDATA *pSV)
{
    WIFI_LIST* pList = SaveData_GetWifiListData(pSV);
    DWCUserData *userdata = WifiList_GetMyUserInfo(pList);

    if( DWC_CheckHasProfile( userdata )
       && DWC_CheckValidConsole( userdata ) ){
       return TRUE;
   }
   return FALSE;
}

