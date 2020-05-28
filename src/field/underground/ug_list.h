//=============================================================================
/**
 * @file	ug_list.h
 * @brief	SELECTボタンで BMPLIST_DATAを入れ替えてしまう機能付のbmplist
 * @author	k.ohno
 * @date    2006.06.11
 */
//=============================================================================


#ifndef __UG_LIST_H__
#define __UG_LIST_H__

#include "system/bmp_menu_list.h"
#include "system/bmp_cursor.h"
#include "system/bmp_list.h"
#include "savedata/undergrounddata.h"

typedef void (*CHANGE_UG_ITEM_FUNC)(UNDERGROUNDDATA* pUGData, int listIndex,int nextIndex);


typedef struct{
    CHANGE_UG_ITEM_FUNC pChangeFunc;
    UNDERGROUNDDATA* pUGData;
    BMP_MENULIST_DATA* pLinkMenuData;
   // BMPLIST_HEADER *pHead; //ヘッダー
    BMPLIST_WORK* pBmpList;  // BMPLISTWORK
	BMPCURSOR* pCursor;		// BMPカーソルデータ
	u16	lp;			//リスト位置
	u16	cp;			//カーソル位置
	u16	bklp;			//リスト位置
	u16	bkcp;			//カーソル位置
    u8 bPush;  //SELECTを押した状態かどうか
    u8 heapID;
    u8 bBase;  //模様替え画面かどうか
	u16 pos_bak;
} UG_BMPLIST_WORK;

extern UG_BMPLIST_WORK * Ug_BmpListSet(BMPLIST_HEADER * bmplist, u16 list_p, u16 cursor_p, u8 heapID ,
                                       CHANGE_UG_ITEM_FUNC pChangeFunc, UNDERGROUNDDATA* pUGData,BOOL bBase);
extern u32 Ug_BmpListMain( UG_BMPLIST_WORK* pUg );
extern void Ug_BmpListExit( UG_BMPLIST_WORK* pUg, u16 * list_bak, u16 * cursor_bak );


#endif //__UG_LIST_H__
