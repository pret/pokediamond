//============================================================================================
/**
 * @file	mystatus.h
 * @brief	自分状態データアクセス用ヘッダ
 * @author	tamada GAME FREAK inc.
 * @date	2005.10.27
 */
//============================================================================================
#ifndef __MYSTATUS_H__
#define __MYSTATUS_H__

#include "savedata/savedata_def.h"	//SAVEDATA参照のため

#include "gflib/msg_print.h"		//STRCODE参照のため
#include "gflib/strbuf.h"			//STRBUF参照のため

//============================================================================================
//============================================================================================
//----------------------------------------------------------
/**
 * @brief	自分状態データ型定義
 */
//----------------------------------------------------------
typedef struct _MYSTATUS MYSTATUS;

//============================================================================================
//============================================================================================
//----------------------------------------------------------
//	セーブデータシステムが依存する関数
//----------------------------------------------------------
extern int MyStatus_GetWorkSize(void);
extern MYSTATUS * MyStatus_AllocWork(u32 heapID);
extern void MyStatus_Copy(const MYSTATUS * from, MYSTATUS * to);

//----------------------------------------------------------
//	MYSTATUS操作のための関数
//----------------------------------------------------------
extern void MyStatus_Init(MYSTATUS * my);

//名前
extern void MyStatus_SetMyName(MYSTATUS * my, const STRCODE * name);
extern const STRCODE * MyStatus_GetMyName(const MYSTATUS * my);
extern STRBUF * MyStatus_CreateNameString(const MYSTATUS * my, int heapID);
extern void MyStatus_CopyNameString( const MYSTATUS * my, STRBUF *buf );
extern void MyStatus_SetMyNameFromString(MYSTATUS * my, const STRBUF * str);

//ID
extern void MyStatus_SetID(MYSTATUS * my, u32 id);
extern u32 MyStatus_GetID(const MYSTATUS * my);
extern u16 MyStatus_GetID_Low(const MYSTATUS * my);
//性別
extern void MyStatus_SetMySex(MYSTATUS * my, int sex);
extern u32 MyStatus_GetMySex(const MYSTATUS * my);
//バッジ
extern BOOL MyStatus_GetBadgeFlag(const MYSTATUS * my, int badge_id);
extern void MyStatus_SetBadgeFlag(MYSTATUS * my, int badge_id);
extern int MyStatus_GetBadgeCount(const MYSTATUS * my);
//お金
extern u32 MyStatus_GetGold(const MYSTATUS * my);
extern u32 MyStatus_SetGold(MYSTATUS * my, u32 gold);
extern u32 Mystatus_AddGold(MYSTATUS * my, u32 add);
extern u32 Mystatus_SubGold(MYSTATUS * my, u32 sub);

// ユニオンルームで使う自分の見た目
extern void MyStatus_SetTrainerView( MYSTATUS *my, u8 view );
extern u8 MyStatus_GetTrainerView( const MYSTATUS *my );

// ROMコード（0:ダイヤ 1:パール）
extern u8  MyStatus_GetRomCode( const MYSTATUS * my );
extern void  MyStatus_SetRomCode( MYSTATUS * my, u8 rom_code );

// リージョンコード
extern u8  MyStatus_GetRegionCode( const MYSTATUS * my );
extern void  MyStatus_SetRegionCode( MYSTATUS * my, u8 region_code );

// ゲームクリア
void MyStatus_SetDpClearFlag( MYSTATUS * my );
int MyStatus_GetDpClearFlag( MYSTATUS * my );

// 全国図鑑
void MyStatus_SetDpZenkokuFlag( MYSTATUS * my );
int MyStatus_GetDpZenkokuFlag( MYSTATUS * my );


//----------------------------------------------------------
//	セーブデータ取得のための関数
//----------------------------------------------------------
extern MYSTATUS * SaveData_GetMyStatus(SAVEDATA * sv);


//	myStatus同士が同じものかどうかを調べる
BOOL MyStatus_Compare(const MYSTATUS * my, const MYSTATUS * target);

//----------------------------------------------------------
//	デバッグ用データ生成のための関数
//----------------------------------------------------------
extern void Debug_MyStatus_Make(MYSTATUS * mystatus, const STRCODE * name, int sex);

#ifdef CREATE_INDEX
extern void *Index_Get_Mystatus_Name_Offset(MYSTATUS *my);
extern void *Index_Get_Mystatus_Id_Offset(MYSTATUS *my);
extern void *Index_Get_Mystatus_Sex_Offset(MYSTATUS *my);
#endif

#endif //__MYSTATUS_H__
