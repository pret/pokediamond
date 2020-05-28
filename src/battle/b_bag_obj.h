//============================================================================================
/**
 * @file	b_bag_obj.h
 * @brief	戦闘用バッグ画面 OBJ関連
 * @author	Hiroyuki Nakamura
 * @date	05.02.15
 */
//============================================================================================
#ifndef B_BAG_OBJ_H
#define B_BAG_OBJ_H
#undef GLOBAL
#ifdef B_BAG_OBJ_H_GLOBAL
#define GLOBAL	/*	*/
#else
#define GLOBAL	extern
#endif


//============================================================================================
//	プロトタイプ宣言
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * 戦闘用バッグOBJ初期化
 *
 * @param	wk		ワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
GLOBAL void BattleBag_ObjInit( BBAG_WORK * wk );

//--------------------------------------------------------------------------------------------
/**
 * 戦闘用ポケリストOBJ削除
 *
 * @param	wk		ワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
GLOBAL void BattleBag_ObjFree( BBAG_WORK * wk );

//--------------------------------------------------------------------------------------------
/**
 * ページごとにOBJをセット
 *
 * @param	wk		ワーク
 * @param	page	ページ
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
GLOBAL void BattleBag_PageObjSet( BBAG_WORK * wk, u32 page );


GLOBAL void BBAG_P2CursorMvTblMake( BBAG_WORK * wk );

GLOBAL void BattleBag_CursorMoveSet( BBAG_WORK * wk, u8 page );

GLOBAL void BattleBag_CursorOff( BBAG_WORK * wk );


//GLOBAL void BattleBag_GetDemoCursorAnm( BBAG_WORK * wk );
//GLOBAL void BattleBag_GetDemoCursorPush( BBAG_WORK * wk );

GLOBAL void BBAG_GetDemoCursorSet( BBAG_WORK * wk, u8 page );


#undef GLOBAL
#endif	// B_BAG_OBJ_H
