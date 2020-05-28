//============================================================================================
/**
 * @file	wifilist.c
 * @brief	WIFI�t�����h�R�[�h�Ǘ�  > �Ƃ������蒠�̃f�[�^�Ǘ�
 * @author	mori san   >  k.ohno
 * @date	2006.03.27 ���炢
 */
//============================================================================================

#include "savedata/savedata_def.h"	//SAVEDATA�Q�Ƃ̂���

#include "common.h"
#include <dwc.h>

#include "system/gamedata.h"
#include "savedata/savedata.h"
#include "system/pm_rtc.h"
#include "battle/battle_common.h"

#include "savedata/wifilist.h"
#include "wifilist_local.h"

#include "system/pm_str.h"

#include "gflib/strbuf_family.h"
#include "wifi/dwc_rap.h"

//============================================================================================
//============================================================================================




//============================================================================================
//
//	�Z�[�u�f�[�^�V�X�e�����ˑ�����֐�
//
//============================================================================================
//----------------------------------------------------------
/**
 * @brief	������ԕێ����[�N�̃T�C�Y�擾
 * @return	int		�T�C�Y�i�o�C�g�P�ʁj
 */
//----------------------------------------------------------
int WifiList_GetWorkSize(void)
{
	return sizeof(WIFI_LIST);
}

//----------------------------------------------------------
/**
 * @brief	������ԕێ����[�N�̊m��
 * @param	heapID		�������m�ۂ������Ȃ��q�[�v�w��
 * @return	WIFI_LIST	�擾�������[�N�ւ̃|�C���^
 */
//----------------------------------------------------------
WIFI_LIST * WifiList_AllocWork(u32 heapID)
{
	int i;
	WIFI_LIST * list;
	list = sys_AllocMemory(heapID, sizeof(WIFI_LIST));
	
	WifiList_Init( list );

	return list;
}

//----------------------------------------------------------
/**
 * @brief	WIFI_LIST�̃R�s�[
 * @param	from	�R�s�[��WIFI_LIST�ւ̃|�C���^
 * @param	to		�R�s�[��WIFI_LIST�ւ̃|�C���^
 */
//----------------------------------------------------------
void WifiList_Copy(const WIFI_LIST * from, WIFI_LIST * to)
{
	MI_CpuCopy8(from, to, sizeof(WIFI_LIST));
}

//============================================================================================
//
//	WIFI_LIST����̂��߂̊֐�
//
//============================================================================================
//----------------------------------------------------------
/**
 * @brief			Wifi�p�Ƃ��������X�g�E�����p�f�[�^�̏�����
 * @param			
 */
//----------------------------------------------------------
void WifiList_Init(WIFI_LIST * list)
{
	int i;
	
	MI_CpuClearFast(list, sizeof(WIFI_LIST));

	for(i=0;i<WIFILIST_FRIEND_MAX;i++){
		list->friend[i].name[0] = EOM_;
		list->friend[i].groupName[0] = EOM_;
        list->friend[i].sex = PM_NEUTRAL;
	}
    mydwc_createUserData(list);  //GameSpy���O�C���p��user�R�[�h�̍쐬(��ΕK�v�j
}


//==============================================================================
/**
 * $brief   ������WIFI�ڑ��������̃|�C���^��Ԃ�
 *
 * @param   list	WIFI_LIST�\���̂̃|�C���^
 *
 * @retval  u8*		
 */
//==============================================================================
DWCUserData* WifiList_GetMyUserInfo( WIFI_LIST* list )
{
	return &(list->my_dwcuser);
}



//==============================================================================
/**
 * $brief   WIFI�F�B�����^�C�v���ɕԂ�
 *
 * @param   list	WIFI_LIST�\���̂̃|�C���^
 * @param   no		���Ԗڂ̗F�B��
 * @param   type	�ݒ肷����̃^�C�v�iwifilist.h��enum�錾����)
 *
 * @retval  u32		
 */
//==============================================================================
u32 WifiList_GetFriendInfo( WIFI_LIST* list, int no, int type )
{
	u32 result;

	GF_ASSERT( no < WIFILIST_FRIEND_MAX );
	
	switch(type){
      case WIFILIST_FRIEND_ID:
        result = list->friend[no].id;
        break;
      case WIFILIST_FRIEND_BATTLE_WIN:
        result = list->friend[no].battle_win;
        break;
      case WIFILIST_FRIEND_BATTLE_LOSE:
        result = list->friend[no].battle_lose;
        break;
      case WIFILIST_FRIEND_TRADE_NUM:
        result = list->friend[no].trade_num;
        break;
      case WIFILIST_FRIEND_LASTBT_YEAR:
        result = list->friend[no].year;
        break;
      case WIFILIST_FRIEND_LASTBT_MONTH:
        result = list->friend[no].month;
        break;
      case WIFILIST_FRIEND_LASTBT_DAY:
        result = list->friend[no].day;
        break;
      case WIFILIST_FRIEND_SEX:
        result = list->friend[no].sex;
        break;
      case WIFILIST_FRIEND_UNION_GRA:
        result = list->friend[no].unionGra;
        break;
	}
	return result;
}


//==============================================================================
/**
 * $brief   
 *
 * @param   list	WIFI_LIST�\���̂̃|�C���^
 * @param   no		���Ԗڂ̗F�B��
 * @param   type	�ݒ肷����̃^�C�v�iwifilist.h��enum�錾����)
 * @param   value	�ݒ肷��l
 *
 * @retval  none	
 */
//==============================================================================
void WifiList_SetFriendInfo( WIFI_LIST* list, int no, int type, u32 value )
{
	GF_ASSERT( no < WIFILIST_FRIEND_MAX );

    switch(type){
      case WIFILIST_FRIEND_ID:
        list->friend[no].id = value;
        break;
      case WIFILIST_FRIEND_BATTLE_WIN:
        GF_ASSERT(0);
        break;
      case WIFILIST_FRIEND_BATTLE_LOSE:
        GF_ASSERT(0);
        break;
      case WIFILIST_FRIEND_TRADE_NUM:
        GF_ASSERT(0);
        break;
      case WIFILIST_FRIEND_LASTBT_YEAR:
        list->friend[no].year = value;
        break;
      case WIFILIST_FRIEND_LASTBT_MONTH:
        list->friend[no].month = value;
        break;
      case WIFILIST_FRIEND_LASTBT_DAY:
        list->friend[no].day = value;
        break;
      case WIFILIST_FRIEND_SEX:
        list->friend[no].sex = value;
        break;
      case WIFILIST_FRIEND_UNION_GRA:
        list->friend[no].unionGra = value;
        break;
    }
}


//==============================================================================
/**
 * $brief   �Ƃ��������X�g����F�B��WIFI�p���\���̂̃|�C���^���擾
 *
 * @param   list	WIFI_LIST�\���̂̃|�C���^
 * @param   no		���l�ڂ̗F�B��
 *
 * @retval  DWCFriendData	*		
 */
//==============================================================================
DWCFriendData	*WifiList_GetDwcDataPtr( WIFI_LIST* list, int no )
{
	GF_ASSERT( no < WIFILIST_FRIEND_MAX );

	return &(list->friend_dwc[no]);
}


//==============================================================================
/**
 * $brief   
 *
 * @param   list	WIFI_LIST�\���̂̃|�C���^
 * @param   no		���l�ڂ̗F�B��
 *
 * @retval  u8 *		
 */
//==============================================================================
STRCODE *WifiList_GetFriendNamePtr( WIFI_LIST *list, int no )
{
	GF_ASSERT( no < WIFILIST_FRIEND_MAX );

	return list->friend[no].name;
}

//==============================================================================
/**
 * $brief   
 *
 * @param   list	WIFI_LIST�\���̂̃|�C���^
 * @param   no		���l�ڂ̗F�B��
 *
 * @retval  u8 *		
 */
//==============================================================================
void WifiList_SetFriendName( WIFI_LIST *list, int no, STRBUF* pBuf )
{
	GF_ASSERT( no < WIFILIST_FRIEND_MAX );

    STRBUF_GetStringCode(pBuf, list->friend[no].name, sizeof(list->friend[no].name));
}

//==============================================================================
/**
 * $brief   
 *
 * @param   list	WIFI_LIST�\���̂̃|�C���^
 * @param   no		���l�ڂ̗F�B��
 *
 * @retval  u8 *		
 */
//==============================================================================
STRCODE *WifiList_GetFriendGroupNamePtr( WIFI_LIST *list, int no )
{
	GF_ASSERT( no < WIFILIST_FRIEND_MAX );

	return list->friend[no].groupName;
}

//==============================================================================
/**
 * $brief   
 * @param   list	WIFI_LIST�\���̂̃|�C���^
 * @param   no		���l�ڂ̗F�B��
 * @retval  u8 *		
 */
//==============================================================================
void WifiList_SetFriendGroupName( WIFI_LIST *list, int no, STRBUF* pBuf )
{
	GF_ASSERT( no < WIFILIST_FRIEND_MAX );

    STRBUF_GetStringCode(pBuf, list->friend[no].groupName, sizeof(list->friend[no].groupName));
}

//==============================================================================
/**
 * $brief   �f�[�^�������Ă��邩�ǂ���
 * @param   list	WIFI_LIST�\���̂̃|�C���^
 * @param   no		���l�ڂ̗F�B��
 * @retval  BOOL
 */
//==============================================================================
BOOL WifiList_IsFriendData( WIFI_LIST *list, int no )
{
	GF_ASSERT( no < WIFILIST_FRIEND_MAX );
    // �t�����h�R�[�h�����������ǂ����Ŕ��f
    return DWC_IsValidFriendData(&list->friend_dwc[no]);
}

//==============================================================================
/**
 * $brief   �����Ă���l����������
 * @param   list	WIFI_LIST�\���̂̃|�C���^
 * @param   no		���l�ڂ̗F�B��
 * @retval  BOOL
 */
//==============================================================================
int WifiList_GetFriendDataNum( WIFI_LIST *list )
{
    int i,num = 0;

    for(i = 0; i < WIFILIST_FRIEND_MAX;i++){
        if(WifiList_IsFriendData(list,i)){
            num++;
        }
    }
    return num;
}

//==============================================================================
/**
 * $brief   �t�����h�̖��O������
 * @param   list	WIFI_LIST�\���̂̃|�C���^
 * @param   no		���l�ڂ̗F�B��
 * @retval  none
 */
//==============================================================================
void WifiList_ResetData( WIFI_LIST *list, int no)
{
    int i;

    GF_ASSERT_RETURN( no < WIFILIST_FRIEND_MAX, );
    for(i = no; i < (WIFILIST_FRIEND_MAX-1); i++){
        MI_CpuCopy8(&list->friend[i+1], &list->friend[i], sizeof(WIFI_FRIEND));
        MI_CpuCopy8(&list->friend_dwc[i+1], &list->friend_dwc[i], sizeof(DWCFriendData));
    }
    i = WIFILIST_FRIEND_MAX-1;
	MI_CpuClearFast(&list->friend[i], sizeof(WIFI_FRIEND));
	MI_CpuClearFast(&list->friend_dwc[i],sizeof(DWCFriendData));
    list->friend[i].name[0] = EOM_;
    list->friend[i].groupName[0] = EOM_;
    list->friend[i].sex = PM_NEUTRAL;
}


//==============================================================================
/**
 * $brief   �t�����h�̖��O���ړ�����
 * @param   list	WIFI_LIST�\���̂̃|�C���^
 * @param   no		    �����Ɉړ�
 * @param   moveNo		�ړ�������f�[�^
 * @retval  none
 */
//==============================================================================
static void WifiList_MoveData( WIFI_LIST *list, int no, int moveNo)
{
    int i;

    MI_CpuCopy8(&list->friend[moveNo], &list->friend[no], sizeof(WIFI_FRIEND));
    MI_CpuCopy8(&list->friend_dwc[moveNo], &list->friend_dwc[no], sizeof(DWCFriendData));
	MI_CpuClearFast(&list->friend[moveNo], sizeof(WIFI_FRIEND));
	MI_CpuClearFast(&list->friend_dwc[moveNo],sizeof(DWCFriendData));
    list->friend[moveNo].name[0] = EOM_;
    list->friend[moveNo].groupName[0] = EOM_;
    list->friend[moveNo].sex = PM_NEUTRAL;
}

//==============================================================================
/**
 * $brief   �t�����h���߂�
 * @param   list	WIFI_LIST�\���̂̃|�C���^
 * @param   no		���l�ڂ̗F�B��
 * @retval  none
 */
//==============================================================================
void WifiList_FormUpData( WIFI_LIST *list)
{
    int i,blank = -1;

    for(i = 0; i < WIFILIST_FRIEND_MAX; i++){
        if(WifiList_IsFriendData(list, i)){
            if(blank != -1){
                WifiList_MoveData(list, blank, i);  // �󂫂Ɉړ�
                OS_TPrintf("friend move %d < %d\n",blank,i);
                i = -1;  // ������񌟍�
                blank = -1;
            }
        }
        else{
            if(blank == -1){
                blank = i;  // �󂫂��L��
            }
        }
    }
}

//==============================================================================
/**
 * $brief   �����̋L�^������
 * @param   list	WIFI_LIST�\���̂̃|�C���^
 * @param   no		���l�ڂ̗F�B��
 * @retval  none
 */
//==============================================================================
void WifiList_SetLastPlayDate( WIFI_LIST *list, int no)
{
    RTCDate	rtc;
    GF_RTC_GetDate(&rtc);
    list->friend[no].year = rtc.year+2000;
    list->friend[no].month = rtc.month;
    list->friend[no].day = rtc.day;
}

//==============================================================================
/**
 * $brief   ���������̋L�^������
 * @param   list	WIFI_LIST�\���̂̃|�C���^
 * @param   no		���l�ڂ̗F�B��
 * @param   winNum  ������
 * @param   loseNum ������
 * @param   trade   ������
 * @retval  none
 */
//==============================================================================
void WifiList_SetResult( WIFI_LIST *list, int no, int winNum, int loseNum,int trade)
{
    list->friend[no].battle_win += winNum;
    if(list->friend[no].battle_win > WIFILIST_COUNT_RANGE_MAX){
        list->friend[no].battle_win = WIFILIST_COUNT_RANGE_MAX;
    }
    list->friend[no].battle_lose += loseNum;
    if(list->friend[no].battle_lose > WIFILIST_COUNT_RANGE_MAX){
        list->friend[no].battle_lose = WIFILIST_COUNT_RANGE_MAX;
    }
    list->friend[no].trade_num += trade;
    if(list->friend[no].trade_num > WIFILIST_COUNT_RANGE_MAX){
        list->friend[no].trade_num = WIFILIST_COUNT_RANGE_MAX;
    }
    OS_TPrintf("list->friend[  %d ].trade_num  %d\n",no,list->friend[no].trade_num);
    WifiList_SetLastPlayDate(list, no);
}




//==============================================================================
/**
 * $brief   A�̐l�̃f�[�^��B�̐l�Ƀ}�[�W����
 * @param   list	WIFI_LIST�\���̂̃|�C���^
 * @param   no		���l�ڂ̗F�B��
 * @param   winNum  ������
 * @param   loseNum ������
 * @param   trade   ������
 * @retval  none
 */
//==============================================================================
void WifiList_DataMarge( WIFI_LIST *list, int delNo, int no)
{
    list->friend[no].battle_win += list->friend[delNo].battle_win;
    if(list->friend[no].battle_win > WIFILIST_COUNT_RANGE_MAX){
        list->friend[no].battle_win = WIFILIST_COUNT_RANGE_MAX;
    }
    list->friend[no].battle_lose += list->friend[delNo].battle_lose;
    if(list->friend[no].battle_lose > WIFILIST_COUNT_RANGE_MAX){
        list->friend[no].battle_lose = WIFILIST_COUNT_RANGE_MAX;
    }
    list->friend[no].trade_num += list->friend[delNo].trade_num;
    if(list->friend[no].trade_num > WIFILIST_COUNT_RANGE_MAX){
        list->friend[no].trade_num = WIFILIST_COUNT_RANGE_MAX;
    }
	MI_CpuClearFast(&list->friend[delNo], sizeof(WIFI_FRIEND));
    list->friend[delNo].name[0] = EOM_;
    list->friend[delNo].groupName[0] = EOM_;
    list->friend[delNo].sex = PM_NEUTRAL;
}



//---------------------------------------------------------------------------
/**
 * @brief	WIFI���X�g���Z�[�u�f�[�^��������o��
 * @param	sv			�Z�[�u�f�[�^�ێ����[�N�ւ̃|�C���^
 * @return	WIFI_LIST	WIFI���X�g
 */
//---------------------------------------------------------------------------
WIFI_LIST* SaveData_GetWifiListData(SAVEDATA * sv)
{
	WIFI_LIST* pData;
	pData = SaveData_Get(sv, GMDATA_ID_WIFILIST);
	return pData;
}

