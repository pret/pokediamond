//============================================================================================
/**
 * @file	friendlist.c
 * @brief	自分状態データアクセス用ソース
 * @author	tamada GAME FREAK inc.
 * @date	2005.10.27
 */
//============================================================================================

// コメントをはずすと友達グループのＩＤを表示する
//#define FRIENDLIST_DEBUG

#include "savedata/savedata_def.h"	//SAVEDATA参照のため

#include "common.h"

#include "system/gamedata.h"
#include "savedata/savedata.h"


#include "savedata/friendlist.h"
#include "friendlist_local.h"

#include "system/pm_str.h"

#include "gflib/strbuf_family.h"

//============================================================================================
//============================================================================================


//============================================================================================
//
//	セーブデータシステムが依存する関数
//
//============================================================================================
//----------------------------------------------------------
/**
 * @brief	自分状態保持ワークのサイズ取得
 * @return	int		サイズ（バイト単位）
 */
//----------------------------------------------------------
int FriendList_GetWorkSize(void)
{
	return sizeof(FRIEND_LIST)*FRIENDLIST_MAX;
}

//----------------------------------------------------------
/**
 * @brief	自分状態保持ワークの確保
 * @param	heapID		メモリ確保をおこなうヒープ指定
 * @return	FRIEND_LIST	取得したワークへのポインタ
 */
//----------------------------------------------------------
FRIEND_LIST * FriendList_AllocWork(u32 heapID)
{
	int i;
	FRIEND_LIST * flist;
	flist = sys_AllocMemory(heapID, sizeof(FRIEND_LIST)*FRIENDLIST_MAX);
	
	FriendList_Init( flist );

	return flist;
}

//----------------------------------------------------------
/**
 * @brief	FRIEND_LISTのコピー
 * @param	from	コピー元FRIEND_LISTへのポインタ
 * @param	to		コピー先FRIEND_LISTへのポインタ
 */
//----------------------------------------------------------
void FriendList_Copy(const FRIEND_LIST * from, FRIEND_LIST * to)
{
	MI_CpuCopy8(from, to, sizeof(FRIEND_LIST));
}


//----------------------------------------------------------
/**
 * @brief	FRIEND_LISTポインタを返す
 * @param	sv				セーブデータ
 * @return  FRIEND_LIST		FRIEND_LISTへのポインタ
 */
//----------------------------------------------------------
FRIEND_LIST *SaveData_GetFriendList(SAVEDATA * sv)
{
	return SaveData_Get( sv, GMDATA_ID_FRIEND);
}
//============================================================================================
//
//	FRIEND_LIST操作のための関数
//
//============================================================================================
//----------------------------------------------------------
/**
 * @brief	友達リストデータの初期化
 * @param	my		友達リスト保持ワークへのポインタ
 */
//----------------------------------------------------------
void FriendList_Init( FRIEND_LIST * flist )
{
	int i;
	
	for(i=0;i<FRIENDLIST_MAX;i++){
		memset(&flist[i], 0, sizeof(FRIEND_LIST));
		flist[i].name[0]  = EOM_;
	}
}

//----------------------------------------------------------
/**
 * @brief	名前セット
 * @param	flist		自分状態保持ワークへのポインタ
 * @param	name	名前文字列へのポインタ
 */
//----------------------------------------------------------
extern void FriendList_SetName(FRIEND_LIST * flist, int no, const STRCODE * name)
{
	int len;

	len = PM_strlen(name);
	GF_ASSERT(len < PERSON_NAME_SIZE + EOM_SIZE);
	PM_strcpy(flist[no].name, name);
}

//----------------------------------------------------------
/**
 * @brief	名前取得
 * @param	my		自分状態保持ワークへのポインタ
 * @return	STRCODE		名前文字列へのポインタ
 */
//----------------------------------------------------------
const STRCODE * FriendList_GetName(const FRIEND_LIST * flist, int no)
{
	return flist[no].name;
}


//----------------------------------------------------------
/**
 * @brief	自分のＩＤセット
 * @param	my		自分状態保持ワークへのポインタ
 * @param	id		ＩＤ指定	
 */
//----------------------------------------------------------
extern void FriendList_SetID(FRIEND_LIST * flist, int no, u32 id)
{
	flist[no].id = id;
}
//----------------------------------------------------------
/**
 * @brief	自分のＩＤ取得
 * @param	my		自分状態保持ワークへのポインタ
 * @return	int		自分のＩＤ	
 */
//----------------------------------------------------------
u32 FriendList_GetID(const FRIEND_LIST * flist, int no)
{
	return flist[no].id;
}


//==============================================================================
/**
 * $brief   ＲＯＭバージョンコードを返す
 *
 * @param   my		自分状態保持ワークへのポインタ
 *
 * @retval  u8		0:ダイヤ 1:パール
 */
//==============================================================================
u8  FriendList_GetRomCode( const FRIEND_LIST * flist, int no )
{
	return flist[no].rom_code;
}
//==============================================================================
/**
 * $brief   ＲＯＭバージョンコードを返す
 *
 * @param   my		自分状態保持ワークへのポインタ
 *
 * @retval  u8		0:ダイヤ 1:パール
 */
//==============================================================================
void  FriendList_SetRomCode( FRIEND_LIST * flist, int no, u8 rom )
{
	flist[no].rom_code = rom;
}

//----------------------------------------------------------
/**
 * @brief	性別セット
 * @param	my		自分状態保持ワークへのポインタ
 * @param	id		性別	
 */
//----------------------------------------------------------
void FriendList_SetSex(FRIEND_LIST * flist, int no, u32 sex)
{
	flist[no].sex = sex;
}
//----------------------------------------------------------
/**
 * @brief	性別取得
 * @param	my		自分状態保持ワークへのポインタ
 * @return	int		自分の性別
 */
//----------------------------------------------------------
u32 FriendList_GetSex(const FRIEND_LIST * flist, int no)
{
	return flist[no].sex;
}



//==============================================================================
/**
 * $brief   グループリストIDセット
 */
//==============================================================================
void  FriendList_SetGroupListId( FRIEND_LIST * flist , int no, u32 id )
{
	flist->group_id[no] = id;
}

//==============================================================================
/**
 * $brief   グループリストIDゲット
 */
//==============================================================================
u8  FriendList_GetGroupListId( const FRIEND_LIST * flist , int no )
{
	return flist->group_id[no];
}

//==============================================================================
/**
 * $brief   ロムコード取得
 */
//==============================================================================
void  FriendList_SetGroupListRomCode( FRIEND_LIST * flist , int no, u8 rom )
{
	flist->group_romcode[no] = rom;
}

//==============================================================================
/**
 * $brief   グループロムコードセット
 */
//==============================================================================
u8  FriendList_GetGroupListRomCode( const FRIEND_LIST * flist , int no )
{
	return flist->group_romcode[no];
}

//==============================================================================
/**
 * $brief   グループ海外コードセット
 */
//==============================================================================
void  FriendList_SetGroupListRegion( FRIEND_LIST * flist , int no, u8 code )
{
	flist->group_region[no] = code;
}

//==============================================================================
/**
 * $brief   グループ海外コード取得
 */
//==============================================================================
u8  FriendList_GetGroupListRegion( const FRIEND_LIST * flist , int no )
{
	return flist->group_region[no];
}
//==============================================================================
/**
 * $brief   グループ性別セット
 */
//==============================================================================
void  FriendList_SetGroupListSex( FRIEND_LIST * flist , int no, u8 code )
{
	flist->group_sex[no] = code;
}

//==============================================================================
/**
 * $brief   グループ性別取得
 */
//==============================================================================
u8  FriendList_GetGroupListSex( const FRIEND_LIST * flist , int no )
{
	return flist->group_sex[no];
}


//--------------------------------------------------------------------------
/**
 * 指定のデータはしりあいグループに登録されているか
 *
 * @param   id		トレーナーＩＤ
 * @param   name	名前（ポケモン文字列)
 *
 * @retval  int		1:一致した	0:なかった（もしくは打ち切った）
 *
 *
 */
//--------------------------------------------------------------------------
int FriendList_Check( FRIEND_LIST * list, u32 id, STRCODE *name)
{
	int i;
	for(i=0;i<FRIENDLIST_MAX;i++){
	    if(0 == PM_strcmp(list->name, name) && (list->id == id)){
			return 1;
		}
	}
	return 0;
}


//----------------------------------------------------------
/**
 * @brief	FriendList同士が同じものかどうかを調べる
 * @param	my		自分状態保持ワークへのポインタ
 * @param	target	相手の自分状態保持ワークへのポインタ
 * @return	一致したらTRUE
 */
//----------------------------------------------------------
BOOL FriendList_Compare(const FRIEND_LIST * src, const FRIEND_LIST * des)
{
    if(0 == PM_strcmp(src->name, des->name)){
        if(src->id == des->id){
            return TRUE;
        }
    }
    return FALSE;
}




//--------------------------------------------------------------------------
/**
 * 現在接続中のメンバーをしりあいグループに登録する
 *
 * @param  none
 *
 * @retval  none	
 *
 *
 */
//--------------------------------------------------------------------------
void FriendList_Update( FRIEND_LIST *mylist, FRIEND_LIST *friends, int num, int heapID)
{
	int i,r,count;
	int search[5];
	FRIEND_LIST *tmp;
	
	// テンポラリ確保＆初期化	
	tmp = sys_AllocMemory(heapID, sizeof(FRIEND_LIST)*FRIENDLIST_MAX);
	FriendList_Init( tmp );

	//今回のメンバーは既に登録すみか？
	for(i=0;i<num;i++){
		search[i] = -1;
		for(r=0;r<FRIENDLIST_MAX;r++){		//配列searchに自分のしりあいグループと比較した結果を格納する(-1：無し,0～:有り)
			if(FriendList_Compare(&mylist[r], &friends[i])){
				search[i] = r;
			}
		}
	}
	
	//今回通信しているメンバーを登録する
	count=0;
	for(i=0;i<num;i++){
		tmp[count] = friends[i];
		if(search[i]>=0){
			mylist[search[i]].name[0] = EOM_;			//登録済みの場合は元のテーブルから名前を消してしまう
		}
		count++;
	}
	
	//既存メンバーを更新する
	for(i=0;i<FRIENDLIST_MAX;i++){
		if(mylist[i].name[0]!=EOM_){			//項目無しじゃなければ更新
			tmp[count] = mylist[i];
			count++;
			if(count>=FRIENDLIST_MAX){
				break;							//MAXを超えたら登録終了
			}
		}
	}
	memcpy(mylist,tmp,sizeof(FRIEND_LIST)*FRIENDLIST_MAX);		//テンポラリから元の場所に更新
	
	
	sys_FreeMemoryEz(tmp);		//テンポラリ解放
}



//==============================================================================
/**
 * $brief   指定のIDは知り合いのIDか総チェックする
 *
 * @param   mylist		
 * @param   id		
 *
 * @retval  int		自分の知り合いだったらDIRECT_FRIEND + (何番目の知り合いか<<16)
 *					ともだちの知り合いINDIRECT_FRIEND + (何番目の知り合いか<<16)
 *
 */
//==============================================================================
int FriendList_IdFullCheck( FRIEND_LIST *mylist, u32 id )
{
	int i,r;

	for(i=0;i<FRIENDLIST_MAX;i++){
		// 直接の知り合いか？
		if(mylist[i].id==id){
			return DIRECT_FRIEND;
		}
	}

	// 間接的な知り合いか？
	for(i=0;i<FRIENDLIST_MAX;i++){
		for(r=0;r<FRIENDLIST_FRIEND_MAX;r++){
			if(mylist[i].group_id[r]==id){
				return INDIRECT_FRIEND + i;
			}
		}
	}
	return 0;	// 知り合いじゃない
}


//============================================================================================
//	デバッグ用
//============================================================================================
//----------------------------------------------------------
/**
 * @brief	デバッグ用：自分状態セット
 * @param	my		自分状態保持ワークへのポインタ
 * @param	name	名前文字列へのポインタ
 * @param	id		ID指定
 */
//----------------------------------------------------------
void Debug_FriendList_Make(FRIEND_LIST * flist, const STRCODE * name, int id )
{
	FriendList_SetName( flist, 0, name);
	FriendList_SetID( flist, 0, id);
}

void Debug_FriendListAllPrint( FRIEND_LIST * mylist )
{
	int i,r;
	for(i=0;i<FRIENDLIST_MAX;i++){
		OS_TPrintf("%02d: id = %08x\n", i, mylist[i].id);
		OS_TPrintf("    ");
		for(r=0;r<FRIENDLIST_FRIEND_MAX/2;r++){
			OS_TPrintf("%02d: = %08x ", r, mylist[i].group_id[r]);
		}
		OS_TPrintf("\n    ");
		for(r=FRIENDLIST_FRIEND_MAX/2;r<FRIENDLIST_FRIEND_MAX;r++){
			OS_TPrintf("%02d: = %08x ", r, mylist[i].group_id[r]);
		}
		OS_TPrintf("\n");
	}
}