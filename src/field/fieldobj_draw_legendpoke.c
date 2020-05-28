//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		fieldobj_draw_legendpoke.c
 *	@brief		伝説ポケモン描画関係
 *	@author		tomoya takahashi
 *	@data		2006.04.18	
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
#include "common.h"
#include "fieldsys.h"

#define	__FIELDOBJ_DRAW_LEGENDPOKE_H_GLOBAL
#include "fieldobj_draw_legendpoke.h"

//-----------------------------------------------------------------------------
/**
 *					コーディング規約
 *		●関数名
 *				１文字目は大文字それ以降は小文字にする
 *		●変数名
 *				・変数共通
 *						constには c_ を付ける
 *						staticには s_ を付ける
 *						ポインタには p_ を付ける
 *						全て合わさると csp_ となる
 *				・グローバル変数
 *						１文字目は大文字
 *				・関数内変数
 *						小文字と”＿”と数字を使用する 関数の引数もこれと同じ
*/
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
/**
 *					定数宣言
*/
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/**
 *					構造体宣言
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	LEGENDPOKE_WORK構造体
//=====================================
typedef struct _LEGENDPOKE_WORK{
	BLACT_WORK_PTR act;
	FIELD_OBJ_BLACTANM_PUSH act_push;
};

#define LEGENDPOKE_WORK_SIZE (sizeof(LEGENDPOKE_WORK))


// 伝説ポケモンイアエアYオフセット
#define LEGENDPOKE_Y_OFS	( FX32_CONST( 0 ) )

// 伝説ポケモン　レイアイハイ　Yオフセット
#define LEGENDPOKE_RE_A_HA_I_Y_OFS	( FX32_CONST( 24 ) )

//-----------------------------------------------------------------------------
/**
 *					プロトタイプ宣言
*/
//-----------------------------------------------------------------------------
static void FldObj_LegendInit( FIELD_OBJ_PTR fldobj );
static void FldObj_LegendDraw( FIELD_OBJ_PTR fldobj );
static void FldObj_LegendDrawVanish( FIELD_OBJ_PTR fldobj, BLACT_WORK_PTR act );
static void FldObj_LegendDelete( FIELD_OBJ_PTR fldobj );

//--------------------------------------------------------------
/**
 * LEGENDPOKE　初期化。
 * 描画の為の初期化を行う。
 * @param	fldobj		FIELD_OBJ_PTR 
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_DrawLegend_Init( FIELD_OBJ_PTR fldobj )
{
	VecFx32 ofs;
	
	// 初期化処理
	FldObj_LegendInit( fldobj );

	// Yオフセット設定
	ofs.x = 0;
	ofs.y = LEGENDPOKE_Y_OFS;
	ofs.z = 0;
	FieldOBJ_VecDrawOffsOutSideSet( fldobj, &ofs );
}

//--------------------------------------------------------------
/**
 * LEGENDPOKE 描画。
 * フィールドOBJから描画に必要な情報を取得し、描画する。
 * @param	fldobj		FIELD_OBJ_PTR 
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_DrawLegend_Draw( FIELD_OBJ_PTR fldobj )
{
	LEGENDPOKE_WORK *work = FieldOBJ_DrawProcWorkGet( fldobj );
	BLACT_WORK_PTR act = work->act;

	if( FieldOBJ_BlActAddPracFlagCheck(fldobj) == TRUE ){		//追加中
		return;
	}
	
	if( act == NULL ){
		return;
	}

	FldObj_LegendDraw( fldobj );

	// アニメーション
	BLACT_AnmFrameChg( act, FX32_ONE );		
}

//--------------------------------------------------------------
/**
 * LEGENDPOKE 削除関数。
 * 描画で使用したモノを削除
 * @param	fldobj	FIELD_OBJ_PTR 
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_DrawLegend_Delete( FIELD_OBJ_PTR fldobj )
{
	// 破棄処理
	FldObj_LegendDelete( fldobj );
}

//----------------------------------------------------------------------------
/**
 *	@brief	LEGENDPOKE 退避
 *	@param	fldobj ワーク
 */
//-----------------------------------------------------------------------------
void FieldOBJ_DrawLegend_Push( FIELD_OBJ_PTR fldobj )
{
	LEGENDPOKE_WORK *work;
	
	work = FieldOBJ_DrawProcWorkGet( fldobj );
	
	if( work->act != NULL ){
		FieldOBJ_BlActAnmPush( work->act, &work->act_push );
	}
	
	FieldOBJ_BlActDelete( fldobj, &work->act );
	FieldOBJ_StatusBit_ON( fldobj, FLDOBJ_STA_BIT_DRAW_PUSH );
}

//----------------------------------------------------------------------------
/**
 *	@brief	LEGENDPOKE 復帰
 *	@param	fldobj	ワーク
 */
//-----------------------------------------------------------------------------
void FieldOBJ_DrawLegend_Pop( FIELD_OBJ_PTR fldobj )
{
	LEGENDPOKE_WORK *work;
	
	work = FieldOBJ_DrawProcWorkGet( fldobj );
	
	if( FieldOBJ_BlActAddPracFlagCheck(fldobj) == TRUE ){
		return;
	}
	
	if( work->act == NULL ){
		FieldOBJ_BlActAddRegularGuest( fldobj, &work->act );
	}
	
	if( work->act != NULL ){
		FieldOBJ_BlActAnmPop( work->act, &work->act_push );
		FieldOBJ_BlActPosSet( fldobj, work->act );
		FieldOBJ_StatusBit_OFF( fldobj, FLDOBJ_STA_BIT_DRAW_PUSH );
	}
}

//--------------------------------------------------------------
/**
 * LEGENDPOKE　初期化。		レイ　アイ　ハイ
 * 描画の為の初期化を行う。
 * @param	fldobj		FIELD_OBJ_PTR 
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_DrawReiAiHai_Init( FIELD_OBJ_PTR fldobj )
{
	VecFx32 ofs;
	
	// 初期化処理
	FldObj_LegendInit( fldobj );

	// Yオフセット設定
	ofs.x = 0;
	ofs.y = LEGENDPOKE_RE_A_HA_I_Y_OFS;
	ofs.z = 0;
	FieldOBJ_VecDrawOffsOutSideSet( fldobj, &ofs );
}

//--------------------------------------------------------------
/**
 * LEGENDPOKE 描画。		レイ　アイ　ハイ
 * フィールドOBJから描画に必要な情報を取得し、描画する。
 * @param	fldobj		FIELD_OBJ_PTR 
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_DrawReiAiHai_Draw( FIELD_OBJ_PTR fldobj )
{
	LEGENDPOKE_WORK *work = FieldOBJ_DrawProcWorkGet( fldobj );
	BLACT_WORK_PTR act = work->act;

	if( FieldOBJ_BlActAddPracFlagCheck(fldobj) == TRUE ){		//追加中
		return;
	}
	
	if( act == NULL ){
		return;
	}

	FldObj_LegendDraw( fldobj );
}

//--------------------------------------------------------------
/**
 * LEGENDPOKE 削除関数。
 * 描画で使用したモノを削除
 * @param	fldobj	FIELD_OBJ_PTR 
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_DrawReiAiHai_Delete( FIELD_OBJ_PTR fldobj )
{
	FldObj_LegendDelete( fldobj );
}



//----------------------------------------------------------------------------
/**
 *	@brief	伝説ポケモンワークの取得
 *
 *	@param	fldobj	フィールドオブジェワーク
 *
 *	@return	伝説ポケモンワークポインタ
 */
//-----------------------------------------------------------------------------
LEGENDPOKE_WORK* FieldOBJ_DrawLegend_GetWrokPtr( FIELD_OBJ_PTR fldobj )
{
	return FieldOBJ_DrawProcWorkGet( fldobj );
}

//----------------------------------------------------------------------------
/**
 *	@brief	伝説ポケモンのビルボード取得
 *
 *	@param	fldobj	フィールドオブジェワーク
 *
 *	@return	BLACT_WORK_PTR
 */
//-----------------------------------------------------------------------------
BLACT_WORK_PTR FieldOBJ_DrawLegend_GetBlActWorkPtr( FIELD_OBJ_PTR fldobj )
{
	LEGENDPOKE_WORK *work = FieldOBJ_DrawProcWorkGet( fldobj );
	return( FieldOBJ_DrawLegend_GetBlactPtr(work) );
}

//----------------------------------------------------------------------------
/**
 *	@brief	ビルボードアクターワーク取得関数
 *
 *	@param	伝説ポケモンワーク
 *
 *	@return	ワークポインタ
 */
//-----------------------------------------------------------------------------
BLACT_WORK_PTR FieldOBJ_DrawLegend_GetBlactPtr( LEGENDPOKE_WORK* p_obj )
{
	return p_obj->act;
}


//-----------------------------------------------------------------------------
/**
 *		ローカル関数
 */
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *	@brief	伝説ポケモン　初期化処理
 *
 *	@param	fldobj 
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void FldObj_LegendInit( FIELD_OBJ_PTR fldobj )
{
	LEGENDPOKE_WORK *work;
	// ワーク作成
	work = FieldOBJ_DrawProcWorkInit( fldobj, LEGENDPOKE_WORK_SIZE );

	// アクター登録
	FieldOBJ_BlActAddRegularGuest( fldobj, &work->act );
}

//----------------------------------------------------------------------------
/**
 *	@brief	伝説ポケモン描画処理
 *
 *	@param	fldobj	ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void FldObj_LegendDraw( FIELD_OBJ_PTR fldobj )
{
	LEGENDPOKE_WORK *work = FieldOBJ_DrawProcWorkGet( fldobj );
	BLACT_WORK_PTR act = work->act;
	
	FieldOBJ_BlActPosSet( fldobj, act );
	FldObj_LegendDrawVanish( fldobj, act );
}

//----------------------------------------------------------------------------
/**
 *	@brief	伝説ポケモン表示・非表示設定
 *
 *	@param	fldobj	フィールドオブジェ
 *	@param	act		アクター
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void FldObj_LegendDrawVanish( FIELD_OBJ_PTR fldobj, BLACT_WORK_PTR act )
{
	int vanish = TRUE;
	if( FieldOBJ_StatusBit_CheckEasy(fldobj,FLDOBJ_STA_BIT_VANISH) == TRUE ){
		vanish = FALSE;
	}
	
	if( FieldOBJ_StatusBit_CheckEasy(fldobj,FLDOBJ_STA_BIT_HEIGHT_GET_ERROR) == TRUE ){
		if( FieldOBJ_StatusBit_CheckEasy(fldobj,FLDOBJ_STA_BIT_HEIGHT_VANISH_OFF) == FALSE){
			vanish = FALSE;
		}
	}
	BLACT_ObjDrawFlagSet( act, vanish );
}


//----------------------------------------------------------------------------
/**
 *	@brief	伝説ポケモン破棄処理
 *
 *	@param	fldobj	ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void FldObj_LegendDelete( FIELD_OBJ_PTR fldobj )
{
	LEGENDPOKE_WORK *work;
	
	//アクター破棄処理
	work = FieldOBJ_DrawProcWorkGet( fldobj );
	FieldOBJ_BlActDelete( fldobj, &work->act );
}

