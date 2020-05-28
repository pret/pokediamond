//============================================================================================
/**
 * @file	randomgroup.h
 * @brief	乱数の種グループ定義ヘッダファイル
 * @author	mori GAME FREAK inc.
 * @date	2006.03.22
 */
//============================================================================================
#ifndef __RANDOMGROUP_H__
#define __RANDOMGROUP_H__


#include "savedata/savedata_def.h"	//SAVEDATA参照のため

#include "gflib/msg_print.h"		//STRCODE参照のため
#include "gflib/strbuf.h"			//STRBUF参照のため


//============================================================================================
//============================================================================================
//----------------------------------------------------------
/**
 * @brief	ランダムグループデータ型定義
 */
//----------------------------------------------------------
typedef struct _RANDOM_GROUP RANDOM_GROUP;


// RandomGroup_<Get*Set>FriendInfoで使うenum
enum{
	RANDOMGROUP_MINE=0,
	RANDOMGROUP_MYUSE,
	RANDOMGROUP_DATA0,
	RANDOMGROUP_DATA1,
	RANDOMGROUP_DATA2,
	RANDOMGROUP_DATA3,
	
	RANDOMGROUP_MAX,	///< ランダムグループの数
};


enum{
	RANDOMGROUP_NAME_GROUP=0,	///< グループ名
	RANDOMGROUP_NAME_LEADER,	///< リーダー名
};
//============================================================================================
//============================================================================================
//----------------------------------------------------------
//	セーブデータシステムが依存する関数
//----------------------------------------------------------
extern int RandomGroup_GetWorkSize(void);
extern void RandomGroup_Init(RANDOM_GROUP * randomgroup );

extern RANDOM_GROUP *SaveData_GetRandomGroup(SAVEDATA * sv);

extern void RandomGroup_Copy( RANDOM_GROUP *randomgroup, int from, int to );

//日数経過による更新処理
extern void RandomGroup_Update( RANDOM_GROUP* randomgroup, u32 days );
//ゲーム内で参照する乱数のタネ取得
extern u32  RandomGroup_GetDefaultRandom( RANDOM_GROUP* randomgroup );

//乱数のタネ設定・取得関連
extern void RandomGroup_SetRandomSeed( RANDOM_GROUP* randomgroup, int no, u32 seed );
extern u32  RandomGroup_GetRandomSeed( RANDOM_GROUP* randomgroup, int no );
extern void RandomGroup_SetRandom( RANDOM_GROUP* randomgroup, int no );
extern u32  RandomGroup_GetRandom( RANDOM_GROUP* randomgroup, int no );


//名前取得
extern const STRCODE *RandomGroup_GetNamePtr( const RANDOM_GROUP *randomgroup, int no, int type );
//名前セット
extern void  RandomGroup_SetName( RANDOM_GROUP *randomgroup, int no, int type, STRBUF *name );
//リージョンコード（国コード）セット
extern void RandomGroup_SetRegionCode( RANDOM_GROUP *randomgroup, int no, int region_code );
//リージョンコード（国コード）取得
extern int RandomGroup_GetRegionCode( const RANDOM_GROUP *randomgroup, int no);
//性別セット
extern void RandomGroup_SetSex( RANDOM_GROUP *randomgroup, int no, int sex);
//性別取得
extern int RandomGroup_GetSex( const RANDOM_GROUP *randomgroup, int no);

//存在チェック
extern BOOL RandomGroup_ExistCheck(const RANDOM_GROUP * rg, int no);
//登録チェック
extern BOOL RandomGroup_EntryCheck(const RANDOM_GROUP * rg, int no);

//同じグループ名の存在チェック
extern BOOL RandomGroup_SameGroupNameCheck(const RANDOM_GROUP * rg, const STRCODE * group_name);

//----------------------------------------------------------
//	レコード関連関数
//	※常駐領域にないためにレコード以外から呼ぶことはできない
//----------------------------------------------------------
extern u32 RandomGroup_GetDefaultDataSize(RANDOM_GROUP * rg);
extern void * RandomGroup_GetDefaultData(RANDOM_GROUP * rg);
extern void RandomGroup_RecordMix(int member, int my_id, RANDOM_GROUP * rg, const void ** darray);
extern void RandomGroup_Debug_RecordMix(SAVEDATA * sv);;

#endif

