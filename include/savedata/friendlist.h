//============================================================================================
/**
 * @file	friendlist.h
 * @brief	しりあいグループデータ定義（WiFI用は別。ＤＳ通信での知り合い）
 * @author	mori GAME FREAK inc.
 * @date	2006.02.10
 */
//============================================================================================
#ifndef __FRIENDLIST_H__
#define __FRIENDLIST_H__

#include "savedata/savedata_def.h"	//SAVEDATA参照のため

#include "gflib/msg_print.h"		//STRCODE参照のため
#include "gflib/strbuf.h"			//STRBUF参照のため


#define FRIENDLIST_MAX			( 16 )
#define FRIENDLIST_FRIEND_MAX	( 16 )	// 知り合いリストが持つ「友達の友達」の数


#define DIRECT_FRIEND			(  1 )	// 直接の知り合い
#define INDIRECT_FRIEND			(  2 )	// 知り合いの知り合い

#define FRIEND_LIST_SIZE		( 136 )

//============================================================================================
//============================================================================================
//----------------------------------------------------------
/**
 * @brief	しりあいグループデータ型定義
 */
//----------------------------------------------------------
typedef struct _FRIEND_LIST FRIEND_LIST;

//============================================================================================
//============================================================================================
//----------------------------------------------------------
//	セーブデータシステムが依存する関数
//----------------------------------------------------------
extern int           FriendList_GetWorkSize(void);
extern FRIEND_LIST  *FriendList_AllocWork(u32 heapID);
extern void          FriendList_Copy(const FRIEND_LIST * from, FRIEND_LIST * to);

//----------------------------------------------------------
//	FRIEND_LIST操作のための関数
//----------------------------------------------------------
extern void  FriendList_Init(FRIEND_LIST * flist);

//名前
extern void  FriendList_SetName(FRIEND_LIST * flist, int no, const STRCODE * name);
extern const STRCODE * FriendList_GetName(const FRIEND_LIST * flist, int no);
//ID
extern void FriendList_SetID(FRIEND_LIST * flist, int no, u32 id);
extern u32  FriendList_GetID(const FRIEND_LIST * flist, int no);

// 性別
extern void FriendList_SetSex(FRIEND_LIST * flist, int no, u32 sex);
extern u32 FriendList_GetSex(const FRIEND_LIST * flist, int no);

// ROMコード（0:ダイヤ 1:パール）
extern void FriendList_SetRomCode( FRIEND_LIST * flist , int no, u8 rom);
extern u8   FriendList_GetRomCode( const FRIEND_LIST * flist ,int no );


// グループリストID
extern void FriendList_SetGroupListId( FRIEND_LIST * flist , int no, u32 id );
extern u8   FriendList_GetGroupListId( const FRIEND_LIST * flist , int no );

// グループリストROMコード
extern void FriendList_SetGroupListRomCode( FRIEND_LIST * flist , int no, u8 rom );
extern u8   FriendList_GetGroupListRomCode( const FRIEND_LIST * flist , int no );

// グループリスト国コード
extern void FriendList_SetGroupListRegion( FRIEND_LIST * flist , int no, u8 code );
extern u8   FriendList_GetGroupListRegion( const FRIEND_LIST * flist , int no );

// グループリーダー性別
u8    FriendList_GetGroupListSex( const FRIEND_LIST * flist , int no );
void  FriendList_SetGroupListSex( FRIEND_LIST * flist , int no, u8 code );

// グループチェック
int   FriendList_Check( FRIEND_LIST * list, u32 id, STRCODE *name);


//--------------------------------------------------------------------------------
// 指定のIDは知り合いかを検索する(激重）
//
// 返り値は0だと知り合い無し
// DIRECT_FRIENDだと自分のしりあい
// INDIRECT_FRIENDだと友達のしりあい（INDIRECT_FRIEND + 友達の配列の添え字が返る）
//--------------------------------------------------------------------------------
extern int FriendList_IdFullCheck( FRIEND_LIST *mylist, u32 id );

// しりあいグループデータを一人分渡すと自分のしりあいグループを更新する
extern void FriendList_Update( FRIEND_LIST *mylist, FRIEND_LIST *friends, int num, int heapID);
//----------------------------------------------------------
//	セーブデータ取得のための関数
//----------------------------------------------------------
extern FRIEND_LIST * SaveData_GetFriendList(SAVEDATA * sv);


//	flistStatus同士が同じものかどうかを調べる
BOOL FriendList_Compare(const FRIEND_LIST * flist, const FRIEND_LIST * target);

//----------------------------------------------------------
//	デバッグ用データ生成のための関数
//----------------------------------------------------------
extern void Debug_FriendList_Make(FRIEND_LIST * fliststatus, const STRCODE * name, int id);
extern void Debug_FriendListAllPrint( FRIEND_LIST * flist );


#endif //__FRIEND_LIST_H__
