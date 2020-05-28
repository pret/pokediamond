#include "common.h"
#include "communication/communication.h"
#include "communication/comm_info.h"
#include "communication/comm_state.h"
#include "wifi/dwc_rapfriend.h"
#include "savedata/savedata.h"
#include "savedata/wifilist.h"
#include "gflib/strbuf_family.h"

// �t�����h���X�g�̃T�C�Y
#define FRIENDLIST_MAXSIZE 32

//==============================================================================
/**
 * ���łɓ����l���o�^����Ă��Ȃ����B
 * @param   pSaveData �t�����h�֌W���͂����Ă���Z�[�u�f�[�^
 * @param   index �����f�[�^�����������Ƃ��́A���̏ꏊ�B
 * @param         ������Ȃ��ꍇ�͋󂢂Ă���Ƃ����Ԃ�
 * @param         �ǂ����󂢂Ă��Ȃ��ꍇ�́A-1 
 * @retval  DWCFRIEND_INLIST �c ���łɁA�����f�[�^�����X�g��ɂ���B���̏ꍇ�͉�������K�v�Ȃ��B
 * @retval  DWCFRIEND_OVERWRITE �c ���łɁA�����f�[�^�����X�g��ɂ��邪�A�㏑�����邱�Ƃ��]�܂����ꍇ�B
 * @retval  DWCFRIEND_NODATA �c �����f�[�^�̓��X�g��ɂȂ��B
 * @retval  DWCFRIEND_INVALID �c �󂯎����DWCFriendData���ُ�B
 */
//==============================================================================
int dwc_checkfriendByToken(SAVEDATA* pSaveData, DWCFriendData *data, int *index)
{
	// ���łɓ����l���o�^���Ă��Ȃ�������
	int i;
    DWCUserData *myUserData = WifiList_GetMyUserInfo(SaveData_GetWifiListData(pSaveData));
    DWCFriendData *keyList  = WifiList_GetDwcDataPtr(SaveData_GetWifiListData(pSaveData),0);
    *index = -1;	
    
    if( !DWC_IsValidFriendData( data ) ) return DWCFRIEND_INVALID;
    
	for( i = 0; i < FRIENDLIST_MAXSIZE; i++ )
	{

		if( DWC_IsEqualFriendData( data, keyList + i ) ) 
		{
			// �S�������f�[�^�������B
			*index = i;
			return DWCFRIEND_INLIST;
		}
		else if( DWC_GetGsProfileId(myUserData,data) > 0 && DWC_GetGsProfileId(myUserData,data) == DWC_GetGsProfileId(myUserData,keyList + i) ) 
		{
			// �t�����h�R�[�h�œo�^����Ă���f�[�^������B
			// ���̏ꍇ�́A�㏑�����Ă��炤���Ƃ𐄏��B
			*index = i;
			return DWCFRIEND_OVERWRITE;
		}
		else if( *index < 0 && !DWC_IsValidFriendData( keyList + i ) )
		{
			*index = i;
		}
	}
	
	// ���X�g�ɂȂ��B
	return DWCFRIEND_NODATA;
}

//==============================================================================
/**
 * ���łɓ����l���o�^����Ă��Ȃ����B
 * @param   pSaveData �t�����h�֌W���͂����Ă���Z�[�u�f�[�^
 * @param   index �����f�[�^�����������Ƃ��́A���̏ꏊ�B
 * @param         ������Ȃ��ꍇ�͋󂢂Ă���Ƃ����Ԃ�
 * @param         �ǂ����󂢂Ă��Ȃ��ꍇ�́A-1 
 * @retval  DWCFRIEND_INLIST �c ���łɁA�����f�[�^�����X�g��ɂ���B
 * @retval  DWCFRIEND_NODATA �c �����f�[�^�̓��X�g��ɂȂ��B
 * @retval  DWCFRIEND_INVALID �c �󂯎����friend_keya���������Ȃ��B
 */
//==============================================================================
int dwc_checkFriendCodeByToken(SAVEDATA* pSaveData, u64 friend_key, int *index)
{
	// ���łɓ����l���o�^���Ă��Ȃ�������
	int i;
    DWCUserData *myUserData = WifiList_GetMyUserInfo(SaveData_GetWifiListData(pSaveData));
    DWCFriendData *keyList  = WifiList_GetDwcDataPtr(SaveData_GetWifiListData(pSaveData),0);
    DWCFriendData token;

    // �F�B�o�^�������������ǂ�������
    if( !DWC_CheckFriendKey( myUserData, friend_key ) ) return DWCFRIEND_INVALID;
    DWC_CreateFriendKeyToken( &token, friend_key );   
    if( DWC_GetGsProfileId(myUserData, &token) <= 0 ) return DWCFRIEND_INVALID;
    
    *index = -1;
	for( i = 0; i < FRIENDLIST_MAXSIZE; i++ )
	{
		if( DWC_GetGsProfileId(myUserData, &token) == DWC_GetGsProfileId(myUserData, keyList + i) ) 
		{
			// �o�^����Ă���f�[�^������B
			*index = i;
			return DWCFRIEND_INLIST;
		}
		else if( *index < 0 && !DWC_IsValidFriendData( keyList + i ) )
		{
			*index = i;	
		}
	}
	
	// ���X�g�ɂȂ��B
	return DWCFRIEND_NODATA;	
}

//------------------------------------------------------------------
/**
 * $brief   �ڑ����Ă���l�̃t�����h�R�[�h����  �o�^����l������������o�^
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

        GF_ASSERT_RETURN(netIDList[i] != DWCFRIEND_INVALID, FALSE);  // �󂯎��f�[�^�Ɉُ킪����

        if(netIDList[i] == DWCFRIEND_INLIST){ //����
            dwc_friendWrite(pSaveData, i, pos, heapID, 2);
            CommInfoWriteResult( pSaveData );
        }
        else if(netIDList[i] == DWCFRIEND_OVERWRITE){ //�㏑��
            if(!CommStateIsWifiConnect()){
                dwc_friendWrite(pSaveData, i, pos, heapID, 1);
                MI_CpuCopy8(pFriend, &keyList[pos], sizeof(DWCFriendData));
                OHNO_PRINT("FriendData�㏑�����܂��� %d \n",pos);
                CommInfoWriteResult( pSaveData );
            }
        }
        else if(netIDList[i] == DWCFRIEND_NODATA){
            hit = TRUE;
            OHNO_PRINT("�o�^�J�n\n");
        }
    }
    return  hit;
}

//------------------------------------------------------------------
/**
 * $brief   �����p�o�^�֐�
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
    if(overWrite == 0){  // �㏑�����ɂ͖��O�����������Ȃ�
        pBuf = MyStatus_CreateNameString(pMyStatus, heapID);
        WifiList_SetFriendName(pList, addListIndex, pBuf);
        STRBUF_Delete(pBuf);
        WifiList_SetFriendInfo(pList, addListIndex, WIFILIST_FRIEND_SEX, MyStatus_GetMySex(pMyStatus));
        WifiList_SetFriendInfo(pList, addListIndex, WIFILIST_FRIEND_ID, MyStatus_GetID(pMyStatus));
    }
    else if(overWrite == 1){
        // �㏑�������ǐ��ʂ��܂�������Ԃ̏ꍇ����
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

