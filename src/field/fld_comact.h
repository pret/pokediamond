/**
 *  @file	fld_comact.h
 *	@brief	フィールド上に共有描画されるカーソルアクターのコントロール
 *	@author	Miyuki iwasawa
 *	@date	06.03.23
 */

#ifndef __H_FLD_COMACT_H__
#define __H_FLD_COMACT_H__

/*
#include "system/procsys.h"
#include "system/bmp_menu.h"
#include "system/bmp_list.h"
#include "system/fontproc.h"
#include "system/lib_pack.h"
#include "system/pm_str.h"
#include "system/window.h"
#include "fld_bmp.h"
#include "fieldmap.h"
#include "fieldsys.h"
#include "field_event.h"
#include "field_skill.h"
#include "ev_mapchange.h"
#include "field/field.h"
*/
#include "system/clact_tool.h"
#include "field_clact.h"

typedef enum{
 FCA_UCURSOR,
 FCA_DCURSOR,
 FCA_ACTMAX,
};

///コントローラーワーク
typedef struct _FLD_COMACT_WORK{
	FIELD_CLACT	fcat;
	CATS_ACT_PTR	act[FCA_ACTMAX];
}FLD_COMACT_WORK;


/**
 *	@brief	フィールドイベント　共通セルアクター初期化
 */
extern FLD_COMACT_WORK* FComAct_Init(int heapID);

/**
 *	@brief	コントローラー破棄
 */
extern void FComAct_Delete(FLD_COMACT_WORK* wk);

/**
 *	@brief	セルアクターメインコントロール
 */
extern void FActCom_Main(FLD_COMACT_WORK* wk);

/**
 *	@brief	カーソルポジションセット
 *
 *	@param	px	カーソルX座標
 *	@param	uy	アップカーソルY座標
 *	@param	dy	ダウンカーソルY座標
 */
extern void FComAct_CursorPosSet(FLD_COMACT_WORK* wk,s16 px,s16 uy,s16 dy);

/**
 *	@brief	描画状態コントロール
 *
 *	@param	vanish	TRUE:描画,FALSE:バニッシュ
 */
extern void FComAct_SetDrawFlg(FLD_COMACT_WORK* wk,u16 idx,BOOL draw);

/**
 *	@brief	オートアニメ状態コントロール
 *
 *	@param	anm	TRUE:オートアニメ,FALSE:オートアニメOff
 */
extern void FComAct_SetAutoAnmFlg(FLD_COMACT_WORK* wk,u16 idx,BOOL anm);


#endif //__H_FLD_COMACT_H__
