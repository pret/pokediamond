//============================================================================================
/**
 * @file	pst_obj.h
 * @brief	ポケモンステータス画面OBJ
 * @author	Hiroyuki Nakamura
 * @date	2005.10.27
 */
//============================================================================================
#ifndef PST_OBJ_H
#define PST_OBJ_H
#undef GLOBAL
#ifdef PST_OBJ_H_GLOBAL
#define GLOBAL	/*	*/
#else
#define GLOBAL	extern
#endif


//============================================================================================
//	定数定義
//============================================================================================


//============================================================================================
//	プロトタイプ宣言
//============================================================================================

//---------------------------------------------------------------------------------------------
/**
 * セルアクター初期化
 *
 * @param	wk		ワーク
 *
 * @return	none
 */
//---------------------------------------------------------------------------------------------
GLOBAL void PokeStatusCellActInit( PST_WORK * wk );

//---------------------------------------------------------------------------------------------
/**
 * セルアクター削除
 *
 * @param	wk		ワーク
 *
 * @return	none
 */
//---------------------------------------------------------------------------------------------
GLOBAL void PokeStatusCellActRerease( PST_WORK * wk );

GLOBAL void PokeStatus_CellActAnm( PST_WORK * wk );

GLOBAL void PokeStatusCellActSet( PST_WORK * wk );

GLOBAL void PokeStatusTabPosChg( PST_WORK * wk );

GLOBAL void PokeStatus_TabArrowPut( PST_WORK * wk );

GLOBAL void PokeStatus_TabArrowVanish( PST_WORK * wk, u8 flg );

GLOBAL void PokeStatusBallAnmChg( PST_WORK * wk );

GLOBAL void PokeStatus_StIconChg( PST_WORK * wk );

GLOBAL void PokeStatus_PageTypeIconDrow( PST_WORK * wk );
GLOBAL void PokeStatus_PokeTypeChange( PST_WORK * wk );
GLOBAL void PokeStatus_WazaTypePosChange( PST_WORK * wk, u8 pos1, u8 pos2 );
GLOBAL void PokeStatus_KindIconChange( PST_WORK * wk, u32 waza );
GLOBAL void PokeStasus_PokeIconChange( PST_WORK * wk );

GLOBAL void PokeStatus_WazaCursorMove( PST_WORK * wk );
GLOBAL void PokeStatus_SubWazaCursorSet( PST_WORK * wk );


GLOBAL void PokeStatus_KezuyaInit( PST_WORK * wk );
GLOBAL void PokeStatus_KezuyaAnm( PST_WORK * wk );

GLOBAL void PokeStatus_MarkChg( PST_WORK * wk );

GLOBAL void PokeStatus_ButtonEffInit( PST_WORK * wk );
GLOBAL void PokeStatus_ButtonEffEnd( PST_WORK * wk );

GLOBAL void PokeStatus_CondUpObjPut( PST_WORK * wk );


GLOBAL void PokeStatus_A_ButtonMarkPut( PST_WORK * wk, GF_BGL_BMPWIN * win );

GLOBAL void PokeStatus_PokeIconSet( PST_WORK * wk );



GLOBAL void PokeStatus_EzConditionPut( PST_WORK * wk );

GLOBAL void PokeStatus_EzConditionOff( PST_WORK * wk );


GLOBAL void PokeStatus_RibbonInit( PST_WORK * wk );
GLOBAL void PokeStatus_RibbonChange( PST_WORK * wk );
GLOBAL void PokeStatus_RibbonCursorMove( PST_WORK * wk );
GLOBAL void PokeStatus_RibbonFlashAnm( PST_WORK * wk );

GLOBAL void PokeStatus_ConditionFlash( PST_WORK * wk, u8 flg );
GLOBAL void PokeStatus_ConditionFlashAnm( PST_WORK * wk );


#undef GLOBAL
#endif	/* PST_OBJ_H */
