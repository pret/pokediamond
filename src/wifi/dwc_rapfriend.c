#include "common.h"
#include "communication/communication.h"
#include "communication/comm_info.h"
#include "communication/comm_state.h"
#include "wifi/dwc_rapfriend.h"
#include "savedata/savedata.h"
#include "savedata/wifilist.h"
#include "gflib/strbuf_family.h"

// フレンドリストのサイズ
#define FRIENDLIST_MAXSIZE 32

//==============================================================================
/**
 * すでに同じ人が登録されていないか。
 * @param   pSaveData フレンド関係がはいっているセーブデータ
 * @param   index 同じデータが見つかったときの、その場所。
 * @param         見つからない場合は空いているところを返す
 * @param         どこも空いていない場合は、-1 
 * @retval  DWCFRIEND_INLIST … すでに、同じデータがリスト上にある。この場合は何もする必要なし。
 * @retval  DWCFRIEND_OVERWRITE … すでに、同じデータがリスト上にあるが、上書きすることが望ましい場合。
 * @retval  DWCFRIEND_NODATA … 同じデータはリスト上にない。
 * @retval  DWCFRIEND_INVALID … 受け取ったDWCFriendDataが異常。
 */
//==============================================================================
int dwc_checkfriendByToken(SAVEDATA* pSaveData, DWCFriendData *data, int *index)
{
	// すでに同じ人が登録していないか検索
	int i;
    DWCUserData *myUserData = WifiList_GetMyUserInfo(SaveData_GetWifiListData(pSaveData));
    DWCFriendData *keyList  = WifiList_GetDwcDataPtr(SaveData_GetWifiListData(pSaveData),0);
    *index = -1;	
    
    if( !DWC_IsValidFriendData( data ) ) return DWCFRIEND_INVALID;
    
	for( i = 0; i < FRIENDLIST_MAXSIZE; i++ )
	{

		if( DWC_IsEqualFriendData( data, keyList + i ) ) 
		{
			// 全く同じデータが発見。
			*index = i;
			return DWCFRIEND_INLIST;
		}
		else if( DWC_GetGsProfileId(myUserData,data) > 0 && DWC_GetGsProfileId(myUserData,data) == DWC_GetGsProfileId(myUserData,keyList + i) ) 
		{
			// フレンドコードで登録されているデータがある。
			// この場合は、上書きしてもらうことを推奨。
			*index = i;
			return DWCFRIEND_OVERWRITE;
		}
		else if( *index < 0 && !DWC_IsValidFriendData( keyList + i ) )
		{
			*index = i;
		}
	}
	
	// リストになし。
	return DWCFRIEND_NODATA;
}

//==============================================================================
/**
 * すでに同じ人が登録されていないか。
 * @param   pSaveData フレンド関係がはいっているセーブデータ
 * @param   index 同じデータが見つかったときの、その場所。
 * @param         見つからない場合は空いているところを返す
 * @param         どこも空いていない場合は、-1 
 * @retval  DWCFRIEND_INLIST … すでに、同じデータがリスト上にある。
 * @retval  DWCFRIEND_NODATA … 同じデータはリスト上にない。
 * @retval  DWCFRIEND_INVALID … 受け取ったfriend_keyaが正しくない。
 */
//==============================================================================
int dwc_checkFriendCodeByToken(SAVEDATA* pSaveData, u64 friend_key, int *index)
{
	// すでに同じ人が登録していないか検索
	int i;
    DWCUserData *myUserData = WifiList_GetMyUserInfo(SaveData_GetWifiListData(pSaveData));
    DWCFriendData *keyList  = WifiList_GetDwcDataPtr(SaveData_GetWifiListData(pSaveData),0);
    DWCFriendData token;

    // 友達登録鍵が正しいかどうか判定
    if( !DWC_CheckFriendKey( myUserData, friend_key ) ) return DWCFRIEND_INVALID;
    DWC_CreateFriendKeyToken( &token, friend_key );   
    if( DWC_GetGsProfileId(myUserData, &token) <= 0 ) return DWCFRIEND_INVALID;
    
    *index = -1;
	for( i = 0; i < FRIENDLIST_MAXSIZE; i++ )
	{
		if( DWC_GetGsProfileId(myUserData, &token) == DWC_GetGsProfileId(myUserData, keyList + i) ) 
		{
			// 登録されているデータがある。
			*index = i;
			return DWCFRIEND_INLIST;
		}
		else if( *index < 0 && !DWC_IsValidFriendData( keyList + i ) )
		{
			*index = i;	
		}
	}
	
	// リストになし。
	return DWCFRIEND_NODATA;	
}

//------------------------------------------------------------------
/**
 * $brief   接続している人のフレンドコード検査  登録する人が見つかったら登録
            WIFINOTE_MODE_AUTOINPUT_CHECK
 * @param   wk		
 * @param   seq		
 * @retval  int 	
 */
//------------------------------------------------------------------

BOOL dwc_friendAutoInputCheck( SAVEDATA* pSaveData, int* netIDList, int heapID)
{
    int i,hit = FALSE,pos;
    DWCFriendData *keyList  = WifiList_GetDwcDataPtr(SaveData_GetWifiListData(pSaveData),0);
    DWCFriendData* pFriend;

    for(i = 0; i < CommGetConnectNum(); i++){
        if(CommGetCurrentID() == i){
            continue;
        }
        pFriend = CommInfoGetDWCFriendCode(i);
        if(pFriend == NULL){
            continue;
        }
        netIDList[i] = dwc_checkfriendByToken(pSaveData, pFriend, &pos);

        OHNO_PRINT("%d check  \n",netIDList[i]);

        GF_ASSERT_RETURN(netIDList[i] != DWCFRIEND_INVALID, FALSE);  // 受け取りデータに異常がある

        if(netIDList[i] == DWCFRIEND_INLIST){ //同一
            dwc_friendWrite(pSaveData, i, pos, heapID, 2);
            CommInfoWriteResult( pSaveData );
        }
        else if(netIDList[i] == DWCFRIEND_OVERWRITE){ //上書き
            if(!CommStateIsWifiConnect()){
                dwc_friendWrite(pSaveData, i, pos, heapID, 1);
                MI_CpuCopy8(pFriend, &keyList[pos], sizeof(DWCFriendData));
                OHNO_PRINT("FriendData上書きしました %d \n",pos);
                CommInfoWriteResult( pSaveData );
            }
        }
        else if(netIDList[i] == DWCFRIEND_NODATA){
            hit = TRUE;
            OHNO_PRINT("登録開始\n");
        }
    }
    return  hit;
}

//------------------------------------------------------------------
/**
 * $brief   無線用登録関数
 * @param   wk		
 * @param   seq		
 * @retval  int 	
 */
//------------------------------------------------------------------

void dwc_friendWrite(SAVEDATA* pSaveData, int netID, int addListIndex, int heapID, int overWrite)
{
    WIFI_LIST* pList = SaveData_GetWifiListData(pSaveData);
    DWCFriendData *keyList  = WifiList_GetDwcDataPtr(pList, addListIndex);
    MYSTATUS* pMyStatus = CommInfoGetMyStatus(netID);
    DWCFriendData* pFriend;
    STRBUF* pBuf;

    if(overWrite != 2){
        pFriend = CommInfoGetDWCFriendCode(netID);
        MI_CpuCopy8(pFriend, keyList, sizeof(DWCFriendData));
    }
    if(overWrite == 0){  // 上書き時には名前を書き換えない
        pBuf = MyStatus_CreateNameString(pMyStatus, heapID);
        WifiList_SetFriendName(pList, addListIndex, pBuf);
        STRBUF_Delete(pBuf);
        WifiList_SetFriendInfo(pList, addListIndex, WIFILIST_FRIEND_SEX, MyStatus_GetMySex(pMyStatus));
        WifiList_SetFriendInfo(pList, addListIndex, WIFILIST_FRIEND_ID, MyStatus_GetID(pMyStatus));
    }
    else if(overWrite == 1){
        // 上書きだけど性別がまだ無い状態の場合書く
        if(WifiList_GetFriendInfo(pList,addListIndex,WIFILIST_FRIEND_SEX) == PM_NEUTRAL){
            WifiList_SetFriendInfo(pList, addListIndex, WIFILIST_FRIEND_SEX, MyStatus_GetMySex(pMyStatus));
            WifiList_SetFriendInfo(pList, addListIndex, WIFILIST_FRIEND_ID, MyStatus_GetID(pMyStatus));
        }
    }
    pBuf =  STRBUF_Create(120, heapID );
    STRBUF_SetStringCode(pBuf, CommInfoGetGroupName(netID));
    WifiList_SetFriendGroupName(pList, addListIndex, pBuf);
    STRBUF_Delete(pBuf);
    WifiList_SetFriendInfo(pList, addListIndex, WIFILIST_FRIEND_UNION_GRA, MyStatus_GetTrainerView(pMyStatus));
    CommInfoWriteResult( pSaveData );

}

