//============================================================================================
/**
 * @file	bag_obj.h
 * @brief	バッグ画面OBJ処理
 * @author	Hiroyuki Nakamura
 * @date	05.10.31
 */
//============================================================================================
#ifndef BAG_OBJ_H
#define BAG_OBJ_H
#undef GLOBAL
#ifdef BAG_OBJ_H_GLOBAL
#define GLOBAL	/*	*/
#else
#define GLOBAL	extern
#endif



#define	CURSOR_ACT_PX	( 177 )
#define	CURSOR_ACT_PY	( 24 )

enum {
	ACT_OFF = 0,
	ACT_ON
};



//--------------------------------------------------------------------------------------------
/**
 * セルアクター初期化
 *
 * @param	wk		バッグ画面のワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
GLOBAL void BagCellActorInit( BAG_WORK * wk );

GLOBAL void BAGOBJ_ClactFree( BAG_WORK * wk );

//--------------------------------------------------------------------------------------------
/**
 * アイテムアイコン変更
 *
 * @param	wk		バッグ画面のワーク
 * @param	item	アイテム番号
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
GLOBAL void BagItemIconChange( BAG_WORK * wk, u16 item );

GLOBAL void BagObj_CursorPalChg( BAG_WORK * wk, u8 num );

GLOBAL void Bag_ObjAnmMain( BAG_WORK * wk );


GLOBAL u8 BagPocketCursorMoveCheck( BAG_WORK * wk );
GLOBAL void BagPocketCursorMoveInit( BAG_WORK * wk );
GLOBAL void BagPocketCursorMoveMain( BAG_WORK * wk );

GLOBAL void Bag_NumArrowSet( BAG_WORK * wk, u8 mode );
GLOBAL void Bag_NumArrowPut( BAG_WORK * wk, u8 flg );

GLOBAL void BagObj_WazaIconPut( BAG_WORK * wk, u16 item, u8 flg );

GLOBAL void BagObj_SubButtonEffInit( BAG_WORK * wk, s16 x, s16 y );
GLOBAL void BagObj_SubButtonEffMain( BAG_WORK * wk );



#undef GLOBAL
#endif	/* BAG_OBJ_H */
