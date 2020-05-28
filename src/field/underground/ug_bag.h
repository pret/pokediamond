//=============================================================================
/**
 * @file	ug_bag.h
 * @brief	地下道具を管理するクラス
 * @author	Katsumi Ohno
 * @date    2005.12.21
 */
//=============================================================================

#ifndef _UG_BAG_H_
#define _UG_BAG_H_

#include "../fieldsys.h"  //FIELDSYS_WORK
#include "savedata/undergrounddata.h"  //UNDERGROUNDDATA

typedef void (*pBagEndFunc)(int selectNo);

extern void CommUnderBagInitialize(UNDERGROUNDDATA* pUGData);
extern void CommUnderBagFinalize(void);
extern void CommUnderBagInit(pBagEndFunc func, FIELDSYS_WORK* pFSys);
extern void CommUnderBagDeleteTrap(int type);
extern void CommUnderBagDeleteStone(int type);

// バッグにたまを入れる
extern BOOL CommUnderBagAddStone(int no, int carat);
// おたからをバッグに入れる
extern BOOL CommUnderBagAddTreasure(int no);
// 罠をかばんに追加
extern BOOL CommUnderBagAddTrap(int no);
// お宝かタマかを分類してバッグに入れる
extern BOOL CommUnderBagAddFossil(int no);
// GOODSをかばんに入れる
extern BOOL CommUnderBagAddGoods(int no);
//GOOSメニューを開く
extern void* UgBagGoodsMenuStart(pBagEndFunc func, FIELDSYS_WORK* pFSys);
// GOODSをバッグから消す
extern void UgBagDeleteGoods(int type);

// 旗消去ウインドウ
extern void CommUnderBagFlagStart(pBagEndFunc func, FIELDSYS_WORK* pFSys);



/// お店の選択
extern int UgShopSelectMenuFuncAndCheck(void* pWork);
/// お店の選択開始
extern void* UgShopSelectMenuInit( BOOL bTrapShop, FIELDSYS_WORK* pFSys );
/// 地下のお店のメニューを開く
extern void* UgShopMenuInit(BOOL bTrapShop, FIELDSYS_WORK* pFSys);
extern void* UgShopMenuInit2(BOOL bTrapShop, FIELDSYS_WORK* pFSys,int no);
/// 地下のお店のメニューを開く
///extern void* UgShopMenuInit_New(BOOL bTrapShop, BOOL bBuy, FIELDSYS_WORK* pFSys);
/// 地下のお店のメニューの状態を得る
extern int UgShopMenuFuncAndCheck(void* pWork);

#include "ug_def.h"


/// お店の会話開始
extern int UgShopTalkStart(int messageNo);
/// お店の会話終了
extern void UgShopTalkEnd(void);
/// アイテムの名前をお店の会話に登録
extern void UgShopTalkRegisterItemName(int index,int type);
/// 罠の名前をお店の会話に登録
extern void UgShopTalkRegisterTrapName(int index,int type);
/// グッズの名前をお店の会話に登録
extern void UgShopTalkRegisterGoodsName(int index,int type);

/// 強制的に消す
extern void UgGoodsMenuForceDelete(void* work,u32 ret);
/// 強制的に消す 引数違うが中身は同じ
extern void UgGoodsMenuForceDelete2(TCB_PTR pTCB, void* work);


#endif // _UG_BAG_H_

