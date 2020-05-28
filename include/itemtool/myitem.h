//=============================================================================
/**
 * @file	myitem.h
 * @brief	手持ちアイテム操作用ヘッダ
 * @author	tamada
 * @author	hiroyuki nakamura
 * @date	2005.10.13
 */
//=============================================================================
#ifndef	__MYITEM_H__
#define	__MYITEM_H__

#include "system/savedata_def.h"
#include "application/bag_def.h"

//============================================================================================
//============================================================================================
//----------------------------------------------------------
/**
 * @brief	手持ちアイテム型定義
 */
//----------------------------------------------------------
typedef struct _MYITEM MYITEM;

// バッグのカーソル位置
typedef struct _BAG_CURSOR	BAG_CURSOR;

//------------------------------------------------------------------------
//	アイテムデータ
//------------------------------------------------------------------------
typedef	struct {
	u16	id;		// アイテム番号
	u16	no;		// 個数
}MINEITEM;

#define	BAG_NORMAL_ITEM_MAX		( 165 )		// 道具ポケット最大数
#define	BAG_EVENT_ITEM_MAX		( 50 )		// 大切な物ポケット最大数
#define	BAG_WAZA_ITEM_MAX		( 100 )		// 技マシンポケット最大数
#define	BAG_SEAL_ITEM_MAX		( 12 )		// シールポケット最大数
#define	BAG_DRUG_ITEM_MAX		( 40 )		// 薬ポケット最大数
#define	BAG_NUTS_ITEM_MAX		( 64 )		// 木の実ポケット最大数
#define	BAG_BALL_ITEM_MAX		( 15 )		// モンスターボールポケット最大数
#define	BAG_BATTLE_ITEM_MAX		( 30 )		// 戦闘用アイテムポケット最大数

//============================================================================================
//============================================================================================
//----------------------------------------------------------
//	セーブデータシステムが依存する関数
//----------------------------------------------------------
extern int MyItem_GetWorkSize(void);
extern MYITEM * MyItem_AllocWork(int heapID);
extern void MyItem_Copy(const MYITEM * from, MYITEM * to);

//----------------------------------------------------------
//	MYITEM操作のための関数
//----------------------------------------------------------
extern void MyItem_Init(MYITEM * item);
extern BOOL MyItem_AddCheck( MYITEM * myitem, u16 item_no, u16 num, u32 heap );
extern BOOL MyItem_AddItem(MYITEM * myitem, u16 item_no, u16 num, u32 heap);
extern BOOL MyItem_SubItem( MYITEM * myitem, u16 item_no, u16 num, u32 heap );
extern BOOL MyItem_SubItemDirect( MINEITEM * myitem, u32 max, u16 item_no, u16 num, u32 heap );
extern BOOL MyItem_CheckItem( MYITEM * myitem, u16 item_no, u16 num, u32 heap );
extern u16 MyItem_GetItemNum( MYITEM * myitem, u16 item_no, u32 heap );
extern u16 MyItem_GetItemNumDirect( MINEITEM * myitem, u32 max, u16 item_no, u32 heap );
extern void MyItem_SortSpace( MINEITEM * item, const u32 max );
extern void MyItem_SortNumber( MINEITEM * item, const u32 max );
extern BOOL MyItem_CheckItemPocket( MYITEM * myitem, u32 pocket );
extern MINEITEM * MyItem_PosItemGet( MYITEM * myitem, u16 pocket, u16 pos );
extern void MyItem_BattlePocketItemMake( MYITEM * myitem, MINEITEM * make[], u32 heap );
extern u32 MyItem_CnvButtonItemGet( const MYITEM * myitem );
extern void MyItem_CnvButtonItemSet( MYITEM * myitem, u32 item );


//----------------------------------------------------------
//	バッグ作成関数
//----------------------------------------------------------
extern void * MyItem_MakeBagData( MYITEM * myitem, const u8 * list, u32 heap );

//----------------------------------------------------------
//	セーブデータ取得のための関数
//----------------------------------------------------------
extern MYITEM * SaveData_GetMyItem(SAVEDATA * sv);

//------------------------------------------------------------------
//	バッグのカーソル位置データ
//------------------------------------------------------------------
extern BAG_CURSOR * MyItem_BagCursorAlloc( u32 heapID );

extern void MyItem_FieldBagCursorGet( BAG_CURSOR * wk, u32 pocket, u8 * pos, u8 * scr );
extern u16 MyItem_FieldBagPocketGet( BAG_CURSOR * wk );
extern void MyItem_FieldBagCursorSet( BAG_CURSOR * wk, u32 pocket, u8 pos, u8 scr );
extern void MyItem_FieldBagPocketSet( BAG_CURSOR * wk, u16 pocket );

extern void MyItem_BattleBagCursorGet( BAG_CURSOR * wk, u32 pocket, u8 * pos, u8 * scr );
extern u16 MyItem_BattleBagLastItemGet( BAG_CURSOR * wk );
extern u16 MyItem_BattleBagLastPageGet( BAG_CURSOR * wk );
extern u16 MyItem_BattleBagPocketPagePosGet( BAG_CURSOR * wk );
extern void MyItem_BattleBagCursorSet( BAG_CURSOR * wk, u32 pocket, u8 pos, u8 scr );
extern void MyItem_BattleBagLastItemSet( BAG_CURSOR * wk, u16 item, u16 page );
extern void MyItem_BattleBagPocketPagePosSet( BAG_CURSOR * wk, u16 pocket );
extern void MyItem_BattleBagCursorPosInit( BAG_CURSOR * wk );


//	デバッグ用適当に手持ちアイテム生成関数
extern void Debug_MyItem_MakeBag(MYITEM * myitem, int heapID);

#ifdef CREATE_INDEX
extern void *Index_Get_Myitem_Offset(MYITEM *item, int type);
#endif
#endif	/* __MYITEM_H__ */
