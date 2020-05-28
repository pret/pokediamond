//============================================================================================
/**
 * @file	WifiList.h
 * @brief	�Ƃ������Ă��傤�p 
 * @author	mori GAME FREAK inc.  --> k.ohno
 * @date	2006.02.10
 */
//============================================================================================
#ifndef __WIFILIST_H__
#define __WIFILIST_H__

#include <dwc.h>

#include "savedata/savedata_def.h"	//SAVEDATA�Q�Ƃ̂���

#include "gflib/msg_print.h"		//STRCODE�Q�Ƃ̂���
#include "gflib/strbuf.h"			//STRBUF�Q�Ƃ̂���


#define WIFILIST_FRIEND_MAX	( 32 )	// WIFI���X�g�����t�����h�̐�
#define WIFILIST_COUNT_RANGE_MAX  (9999)   // �����܂����̉񐔏��

//============================================================================================
//============================================================================================
//----------------------------------------------------------
/**
 * @brief	���肠���O���[�v�f�[�^�^��`
 */
//----------------------------------------------------------
typedef struct _WIFI_LIST WIFI_LIST;


// WifiList_<Get*Set>FriendInfo�Ŏg��enum
enum{
	WIFILIST_FRIEND_ID = 0,
//	WIFILIST_FRIEND_BATTLE_NUM,
	WIFILIST_FRIEND_BATTLE_WIN,
	WIFILIST_FRIEND_BATTLE_LOSE,
	WIFILIST_FRIEND_TRADE_NUM,
	WIFILIST_FRIEND_LASTBT_YEAR,
	WIFILIST_FRIEND_LASTBT_MONTH,
	WIFILIST_FRIEND_LASTBT_DAY,
	WIFILIST_FRIEND_UNION_GRA,
	WIFILIST_FRIEND_SEX,
};

//============================================================================================
//============================================================================================
//----------------------------------------------------------
//	�Z�[�u�f�[�^�V�X�e�����ˑ�����֐�
//----------------------------------------------------------
extern int WifiList_GetWorkSize(void);
extern WIFI_LIST * WifiList_AllocWork(u32 heapID);
extern void WifiList_Copy(const WIFI_LIST * from, WIFI_LIST * to);
extern void WifiList_Init(WIFI_LIST * list);
extern DWCUserData* WifiList_GetMyUserInfo( WIFI_LIST* list );
extern u32 WifiList_GetFriendInfo( WIFI_LIST* list, int no, int type );
extern void WifiList_SetFriendInfo( WIFI_LIST* list, int no, int type, u32 value );
extern DWCFriendData* WifiList_GetDwcDataPtr( WIFI_LIST* list, int no );
extern STRCODE *WifiList_GetFriendNamePtr( WIFI_LIST *list, int no );
extern void WifiList_SetFriendName( WIFI_LIST *list, int no, STRBUF* pBuf );
extern STRCODE *WifiList_GetFriendGroupNamePtr( WIFI_LIST *list, int no );
extern void WifiList_SetFriendGroupName( WIFI_LIST *list, int no, STRBUF* pBuf );
extern BOOL WifiList_IsFriendData( WIFI_LIST *list, int no );
extern int WifiList_GetFriendDataNum( WIFI_LIST *list );
extern void WifiList_SetLastPlayDate( WIFI_LIST *list, int no);

extern void WifiList_ResetData( WIFI_LIST *list, int no);
extern void WifiList_SetResult( WIFI_LIST *list, int no, int winNum, int loseNum,int trade);
extern void WifiList_DataMarge( WIFI_LIST *list, int delNo, int no);
extern void WifiList_FormUpData( WIFI_LIST *list);

//----------------------------------------------------------
//	�Z�[�u�f�[�^�擾�̂��߂̊֐�
//----------------------------------------------------------
extern WIFI_LIST* SaveData_GetWifiListData(SAVEDATA* pSave);

#endif