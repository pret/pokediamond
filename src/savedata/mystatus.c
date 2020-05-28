//============================================================================================
/**
 * @file	mystatus.c
 * @brief	自分状態データアクセス用ソース
 * @author	tamada GAME FREAK inc.
 * @date	2005.10.27
 */
//============================================================================================

#include "savedata/savedata_def.h"	//SAVEDATA参照のため

#include "common.h"

#include "system/gamedata.h"
#include "savedata/savedata.h"

#include "mystatus_local.h"

#include "savedata/mystatus.h"

#include "system/pm_str.h"

#include "gflib/strbuf_family.h"

#define TR_LOW_MASK		(0xffff)

//============================================================================================
//============================================================================================

enum {
	MY_GOLD_MAX	= 999999,
};



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
int MyStatus_GetWorkSize(void)
{
	return sizeof(MYSTATUS);
}

//----------------------------------------------------------
/**
 * @brief	自分状態保持ワークの確保
 * @param	heapID		メモリ確保をおこなうヒープ指定
 * @return	MYSTATUS	取得したワークへのポインタ
 */
//----------------------------------------------------------
MYSTATUS * MyStatus_AllocWork(u32 heapID)
{
	MYSTATUS * my;
	my = sys_AllocMemory(heapID, sizeof(MYSTATUS));
	MyStatus_Init(my);


	return my;
}

//----------------------------------------------------------
/**
 * @brief	MYSTATUSのコピー
 * @param	from	コピー元MYSTATUSへのポインタ
 * @param	to		コピー先MYSTATUSへのポインタ
 */
//----------------------------------------------------------
void MyStatus_Copy(const MYSTATUS * from, MYSTATUS * to)
{
	MI_CpuCopy8(from, to, sizeof(MYSTATUS));
}

//============================================================================================
//
//	MYSTATUS操作のための関数
//
//============================================================================================

//----------------------------------------------------------
/**
 * @brief		自分状態データの初期化
 * @param	my		自分状態保持ワークへのポインタ
 */
//----------------------------------------------------------
void MyStatus_Init(MYSTATUS * my)
{
	memset(my, 0, sizeof(MYSTATUS));

	// カセットの言語コードを埋め込む
	my->region_code = PM_LANG;		

#ifdef PM_DEBUG

	// デバッグで他国の人になりすませる。
	if(sys.cont&PAD_BUTTON_L){
		MyStatus_SetRegionCode(my, LANG_JAPAN );
	}else if(sys.cont&PAD_BUTTON_R){
		MyStatus_SetRegionCode(my, LANG_ENGLISH );
	}else if(sys.cont&PAD_BUTTON_SELECT){
		MyStatus_SetRegionCode(my, LANG_FRANCE	 );
	}else if(sys.cont&PAD_BUTTON_START){
		MyStatus_SetRegionCode(my, LANG_ITALY	 );
	}else if(sys.cont&PAD_KEY_UP){
		MyStatus_SetRegionCode(my, LANG_GERMANY );
	}else if(sys.cont&PAD_KEY_LEFT){
		MyStatus_SetRegionCode(my, LANG_SPAIN	 );
	}

#endif
}

//----------------------------------------------------------
/**
 * @brief	自分の名前セット
 * @param	my		自分状態保持ワークへのポインタ
 * @param	name	名前文字列へのポインタ
 */
//----------------------------------------------------------
void MyStatus_SetMyName(MYSTATUS * my, const STRCODE * name)
{
	int len;
	len = PM_strlen(name);
	GF_ASSERT(len < PERSON_NAME_SIZE + EOM_SIZE)
	PM_strcpy(my->name, name);
}

//----------------------------------------------------------
/**
 * @brief	自分の名前セット(STRBUF版）
 * @param	my		自分状態保持ワークへのポインタ
 * @param	str		名前保持バッファへのポインタ
 */
//----------------------------------------------------------
void MyStatus_SetMyNameFromString(MYSTATUS * my, const STRBUF * str)
{
	STRBUF_GetStringCode( str, my->name, PERSON_NAME_SIZE + EOM_SIZE );
}

//----------------------------------------------------------
/**
 * @brief	自分の名前取得
 * @param	my		自分状態保持ワークへのポインタ
 * @return	STRCODE		名前文字列へのポインタ
 */
//----------------------------------------------------------
const STRCODE * MyStatus_GetMyName(const MYSTATUS * my)
{
	return my->name;
}

//----------------------------------------------------------
/**
 * @brief	自分の名前取得（STRBUFにコピー）
 * @param	my		自分状態保持ワークへのポインタ
 * @param	buf		コピーする先のSTRBUFへのポインタ（各自で内容は確保してある事が前提）
 * @return	none
 */
//----------------------------------------------------------
void MyStatus_CopyNameString( const MYSTATUS * my, STRBUF *buf )
{
	STRBUF_SetStringCode( buf, my->name );
}

//----------------------------------------------------------
/**
 * @brief	自分の名前取得（STRBUFを生成）
 * @param	my		自分状態保持ワークへのポインタ
 * @param	heapID	STRBUFを生成するヒープのID
 * @return	STRBUF	名前を格納したSTRBUFへのポインタ
 */
//----------------------------------------------------------
STRBUF * MyStatus_CreateNameString(const MYSTATUS * my, int heapID)
{
	STRBUF * tmpBuf = STRBUF_Create(PERSON_NAME_SIZE + EOM_SIZE, heapID);
//	STRBUF_SetStringCode( tmpBuf, my->name );
	MyStatus_CopyNameString( my, tmpBuf );
	return tmpBuf;
}


//----------------------------------------------------------
/**
 * @brief	自分のＩＤセット
 * @param	my		自分状態保持ワークへのポインタ
 * @param	id		ＩＤ指定	
 */
//----------------------------------------------------------
void MyStatus_SetID(MYSTATUS * my, u32 id)
{
	my->id = id;
}
//----------------------------------------------------------
/**
 * @brief	自分のＩＤ取得
 * @param	my		自分状態保持ワークへのポインタ
 * @return	int		自分のＩＤ	
 */
//----------------------------------------------------------
u32 MyStatus_GetID(const MYSTATUS * my)
{
	return my->id;
}

//----------------------------------------------------------
/**
 * @brief	自分のＩＤ取得(下位２バイト)
 * @param	my		自分状態保持ワークへのポインタ
 * @return	int		自分のＩＤ	
 */
//----------------------------------------------------------
u16 MyStatus_GetID_Low(const MYSTATUS * my)
{
	return (u16)(my->id&TR_LOW_MASK);
}

//----------------------------------------------------------
/**
 * @brief	自分の性別セット
 * @param	my		自分状態保持ワークへのポインタ
 * @param	sex		自分の性別
 */
//----------------------------------------------------------
void MyStatus_SetMySex(MYSTATUS * my, int sex)
{
	my->sex = sex;
}
//----------------------------------------------------------
/**
 * @brief	自分の性別取得
 * @param	my		自分状態保持ワークへのポインタ
 * @return	sex		自分の性別
 */
//----------------------------------------------------------
u32 MyStatus_GetMySex(const MYSTATUS * my)
{
	return my->sex;
}

//----------------------------------------------------------
/**
 * @brief	バッジ保持状態の取得
 * @param	my			自分状態保持ワークへのポインタ
 * @param	badge_id	バッジの指定
 * @return	BOOL	バッジを持っているかどうか
 */
//----------------------------------------------------------
BOOL MyStatus_GetBadgeFlag(const MYSTATUS * my, int badge_id)
{
	if (my->badge & (1 << badge_id)) {
		return TRUE;
	} else {
		return FALSE;
	}
}

//----------------------------------------------------------
/**
 * @brief	バッジ取得のセット
 * @param	my			自分状態保持ワークへのポインタ
 * @param	badge_id	バッジの指定
 */
//----------------------------------------------------------
void MyStatus_SetBadgeFlag(MYSTATUS * my, int badge_id)
{
	my->badge |= (1 << badge_id);
}

//----------------------------------------------------------
/**
 * @brief	持っているバッジの数を取得する
 * @param	my			自分状態保持ワークへのポインタ
 * @return	int		持っているバッジの数（０～８）
 */
//----------------------------------------------------------
int MyStatus_GetBadgeCount(const MYSTATUS * my)
{
	int count = 0;
	u32 badge;
	
	for (badge = my->badge; badge != 0; badge >>= 1) {
		if (badge & 1) {
			count ++;
		}
	}
	return count;
}
//----------------------------------------------------------
/**
 * @brief	持っている金額を取得する
 * @param	my		自分状態保持ワークへのポインタ
 * @return	u32		持っている金額
 */
//----------------------------------------------------------
u32 MyStatus_GetGold(const MYSTATUS * my)
{
	return my->gold;
}

//----------------------------------------------------------
/**
 * @brief
 * @param	my		自分状態保持ワークへのポインタ
 * @param	gold	セットする金額
 * @return	u32		現在の手持ち金額
 */
//----------------------------------------------------------
u32 MyStatus_SetGold(MYSTATUS * my, u32 gold)
{
	if (gold > MY_GOLD_MAX) {
		gold = MY_GOLD_MAX;
	}
	my->gold = gold;
	return my->gold;
}

//==============================================================================
/**
 * $brief   自分がトレーナーとして見られる時の番号を返す（ユニオンルーム用）
 *
 * @param   my		自分状態保持ワークへのポインタ
 *
 * @retval  u8		トレーナーとしての自分の見た目
 */
//==============================================================================
u8 MyStatus_GetTrainerView( const MYSTATUS *my )
{
	return my->trainer_view;
}

//==============================================================================
/**
 * $brief   自分がトレーナーとして見られる時の番号をセット（ユニオンルーム用）
 *
 * @param   my		自分状態保持ワークへのポインタ
 * @param   view	トレーナー見た目番号
 *
 * @retval  none
 */
//==============================================================================
void MyStatus_SetTrainerView( MYSTATUS *my, u8 view )
{
	my->trainer_view = view;
}

//----------------------------------------------------------
/**
 * @brief
 * @param	my		自分状態保持ワークへのポインタ
 * @param	add		加える金額
 * @return	u32		現在の手持ち金額
 */
//----------------------------------------------------------
u32 Mystatus_AddGold(MYSTATUS * my, u32 add)
{
	if (add > MY_GOLD_MAX) {
		my->gold = MY_GOLD_MAX;
	} else {
		my->gold += add;
	}
	if (my->gold > MY_GOLD_MAX) {
		my->gold = MY_GOLD_MAX;
	}
	return my->gold;
}

//----------------------------------------------------------
/**
 * @brief
 * @param	my		自分状態保持ワークへのポインタ
 * @param	sub		引き出す金額
 * @return	u32		現在の手持ち金額
 */
//----------------------------------------------------------
u32 Mystatus_SubGold(MYSTATUS * my, u32 sub)
{
	if (my->gold < sub) {
		my->gold = 0;
	} else {
		my->gold -= sub;
	}
	return my->gold;
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
u8  MyStatus_GetRomCode( const MYSTATUS * my )
{
	return my->rom_code;
}

//==============================================================================
/**
 * $brief   ＲＯＭバージョンコードを設定する
 *
 * @param   my		自分状態保持ワークへのポインタ
 *
 * @param  rom_code		0:ダイヤ 1:パール
 */
//==============================================================================
void  MyStatus_SetRomCode( MYSTATUS * my, u8 rom_code )
{
	my->rom_code = rom_code;
}

//==============================================================================
/**
 * $brief   リージョンコードを返す
 *
 * @param   my		自分状態保持ワークへのポインタ
 *
 * @retval  u8		リージョンコード
 */
//==============================================================================
u8  MyStatus_GetRegionCode( const MYSTATUS * my )
{
	return my->region_code;
}

//==============================================================================
/**
 * $brief   リージョンコードを設定する
 *
 * @param   my		自分状態保持ワークへのポインタ
 *
 * @param  region_code		
 */
//==============================================================================
void  MyStatus_SetRegionCode( MYSTATUS * my, u8 region_code )
{
	my->region_code = region_code;
}

//==============================================================================
/**
 * @brief   DPクリアしているかフラグのセット
 *
 * @param   my		
 * @param   flag	0:してない	1:クリアしている
 *
 * @retval  none		
 */
//==============================================================================
void MyStatus_SetDpClearFlag( MYSTATUS * my )
{
	my->dp_clear = 1;
}

int MyStatus_GetDpClearFlag( MYSTATUS * my )
{
	return my->dp_clear;
}

//==============================================================================
/**
 * @brief   DP全国図鑑だしているフラグのセット
 *
 * @param   my		
 * @param   flag	0:シンオウ図鑑	1:全国図鑑
 *
 * @retval  none		
 */
//==============================================================================
void MyStatus_SetDpZenkokuFlag( MYSTATUS * my )
{
	my->dp_zenkoku = 1;
}

int MyStatus_GetDpZenkokuFlag( MYSTATUS * my )
{
	return my->dp_zenkoku;
}





//----------------------------------------------------------
/**
 * @brief	myStatus同士が同じものかどうかを調べる
 * @param	my		自分状態保持ワークへのポインタ
 * @param	target	相手の自分状態保持ワークへのポインタ
 * @return	一致したらTRUE
 */
//----------------------------------------------------------
BOOL MyStatus_Compare(const MYSTATUS * my, const MYSTATUS * target)
{
    if(0 == PM_strncmp(my->name, target->name, PERSON_NAME_SIZE)){
        if(my->id == target->id){
            return TRUE;
        }
    }
    return FALSE;
}



//============================================================================================
//	デバッグ用
//============================================================================================
//----------------------------------------------------------
/**
 * @brief	デバッグ用：自分状態セット
 * @param	my		自分状態保持ワークへのポインタ
 * @param	name	名前文字列へのポインタ
 * @param	sex		性別指定
 */
//----------------------------------------------------------
void Debug_MyStatus_Make(MYSTATUS * mystatus, const STRCODE * name, int sex)
{
	MyStatus_SetMyName(mystatus, name);
	MyStatus_SetMySex(mystatus, sex);
}

// 外部参照インデックスを作る時のみ有効(ゲーム中は無効)
#ifdef CREATE_INDEX
void *Index_Get_Mystatus_Name_Offset(MYSTATUS *my){ return &my->name; }
void *Index_Get_Mystatus_Id_Offset(MYSTATUS *my){ return &my->id; }
void *Index_Get_Mystatus_Sex_Offset(MYSTATUS *my){ return &my->sex; }
#endif
