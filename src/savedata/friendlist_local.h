//============================================================================================
/**
 * @file	friendlist_local.h
 * @brief	しりあいグループデータ定義（WiFI用は別。ＤＳ通信での知り合い）
 * @author	mori GAME FREAK inc.
 * @date	2006.02.10
 */
//============================================================================================
#ifndef __FRIENDLIST_LOCAL_H__
#define __FRIENDLIST_LOCAL_H__

struct _FRIEND_LIST{
	STRCODE name[PERSON_NAME_SIZE + EOM_SIZE];		//  16		134
	u32		id;										//  +4
	u8		region;									//  +1
	u8		rom_code;								//  +1
	u8      sex;									//  +1
	u8		etc;									//  +1
	u32		group_id[FRIENDLIST_FRIEND_MAX];		//  +4*16	
	u8		group_romcode[FRIENDLIST_FRIEND_MAX];	//	+16
	u8		group_region[FRIENDLIST_FRIEND_MAX];	//  +16
	u8		group_sex[FRIENDLIST_FRIEND_MAX];		//  +16
};



#endif