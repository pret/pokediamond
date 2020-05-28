//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		scr_hideneff.c
 *	@brief		ヒデン技エフェクトスクリプト管理
 *	@author		tomoya takahshi
 *	@data		2006.06.27
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

#include "common.h"
#include "fieldsys.h"
#include "fieldmap_work.h"
#include "field_hideneff.h"

#define __FIELD_HIDENEFF_H_GLOBAL
#include "scr_hideneff.h"

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
//	ヒデン技管理ワーク
//=====================================
typedef struct {
	FLDMAPFUNC_WORK* p_work;
	u16* p_retwk;
	u32 seq;
	u32 effect_type;
} FLD_HIDENEFF_CONT;

typedef FLDMAPFUNC_WORK* (*pInitFunc)( FIELDSYS_WORK* fsys );
typedef void (*pDeleteFunc)( FLDMAPFUNC_WORK* p_demo );
typedef BOOL (*pEndCheckFunc)( FLDMAPFUNC_WORK* p_demo );


static const pInitFunc	HideInitFunc[ SCR_HIDENEFF_NUM ] = {
	FLD_HIDENEFF_Iaigiri_Start,
	FLD_HIDENEFF_Iwakudaki_Start,
	FLD_HIDENEFF_Iwakudaki_KuroganeL_Start,
};

static const pDeleteFunc	HideDeleteFunc[ SCR_HIDENEFF_NUM ] = {
	FLD_HIDENEFF_Iaigiri_End,
	FLD_HIDENEFF_Iwakudaki_End,
	FLD_HIDENEFF_Iwakudaki_End,
};

static const pEndCheckFunc	HideEndCheckFunc[ SCR_HIDENEFF_NUM ] = {
	FLD_HIDENEFF_Iaigiri_EndCheck,
	FLD_HIDENEFF_Iwakudaki_EndCheck,
	FLD_HIDENEFF_Iwakudaki_EndCheck,
};

//-----------------------------------------------------------------------------
/**
 *					プロトタイプ宣言
*/
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *	@brief	ヒデン技終了管理タスク
 */
//-----------------------------------------------------------------------------
static void ScrCmd_HidenEffContTask( TCB_PTR tcb, void* p_work )
{
	FLD_HIDENEFF_CONT* p_cont = p_work;

	switch( p_cont->seq ){
	case 0:
		if( HideEndCheckFunc[ p_cont->effect_type ]( p_cont->p_work ) == TRUE ){
			p_cont->seq ++;
		}
		break;
	
	case 1:
		HideDeleteFunc[ p_cont->effect_type ]( p_cont->p_work );
		*p_cont->p_retwk = 1;
		sys_FreeMemoryEz( p_cont );
		TCB_Delete( tcb );
		break;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	ヒデンエフェクト管理タスク発動
 *
 *	@param	p_retwk			完了フラグ設定先
 *	@param	effect_type		エフェクトタイプ
 *
 *	effect_type
 *		SCR_HIDENEFF_IAIGIRI
 *      SCR_HIDENEFF_IWAKUDAKI
 */
//-----------------------------------------------------------------------------
void ScrCmd_HidenEffContStart( FIELDSYS_WORK* fsys, u16* p_retwk, u32 effect_type, u32 heap )
{
	FLD_HIDENEFF_CONT* p_cont = sys_AllocMemory( heap, sizeof(FLD_HIDENEFF_CONT) );
	memset( p_cont, 0, sizeof(FLD_HIDENEFF_CONT) );
	p_cont->p_work = HideInitFunc[ effect_type ]( fsys );
	p_cont->p_retwk = p_retwk;
	p_cont->effect_type = effect_type;
	*p_retwk = 0;
	TCB_Add( ScrCmd_HidenEffContTask, p_cont, 0 );
}

