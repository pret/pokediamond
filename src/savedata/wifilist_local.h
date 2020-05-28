//============================================================================================
/**
 * @file	wifilist_local.h
 * @brief	Wifi�Ƃ������R�[�h���X�g��`�i�u���肠���O���[�v�v�͕ʁAwifi��ł̏��̂݁j
 * @author	mori GAME FREAK inc.
 * @date	2006.03.02
 */
//============================================================================================
#ifndef __WIFILIST_LOCAL_H__
#define __WIFILIST_LOCAL_H__

typedef struct{
    STRCODE         groupName[PERSON_NAME_SIZE + EOM_SIZE]; // 16
    STRCODE 		name[PERSON_NAME_SIZE + EOM_SIZE];		// 32
	u32				id;										// 36


//	u16		battle_count;							// 38
	u16		battle_win;								// 40
	u16		battle_lose;							// 42

	u16     trade_num;								// 44

    u16     year;    //�Ō�ɑΐ킵���N���� �܂��̏ꍇ�͂O�O�O  //46
    u8     month;                             
    u8     day;
    u8     sex;
    u8     unionGra;                             //50
  
}WIFI_FRIEND;

struct _WIFI_LIST{
	DWCUserData		my_dwcuser;							// 64
	DWCFriendData	friend_dwc[WIFILIST_FRIEND_MAX];	// 64+12*32 = 448

	WIFI_FRIEND	friend[WIFILIST_FRIEND_MAX];		// 448+ 50*32 = 2048 = 0x800
};



#endif