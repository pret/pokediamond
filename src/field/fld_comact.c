/**
 *  @file	fld_comact.c
 *	@brief	フィールド上に共有描画されるカーソルアクターのコントロール
 *	@author	Miyuki iwasawa
 *	@date	06.03.23
 */

#include "common.h"
#include "field/fld_comact.h"
#include "field/fld_comact.naix"

#define FCOMACT_CHR_RES_MAX	(1)
#define FCOMACT_PAL_RES_MAX	(1)
#define FCOMACT_CEL_RES_MAX	(1)
#define FCOMACT_ANM_RES_MAX	(1)

enum {
	FCOMACT_CHR_H_ID_CURSOR	= 13528,
};
enum {
	FCOMACT_PAL_H_ID = 13528,
};
enum {
	FCOMACT_CEL_H_ID_CURSOR	= 13528,
};
enum {
	FCOMACT_ANM_H_ID_CURSOR	= 13528,
};

#define CURSOR_PX	(80)
#define CURSOR_PRI	(0)
#define CURSOR_SPRI	(0)
#define CURSOR_PAL	(0)

#define UPCUR_PY	(16)
#define UPCUR_ANMNO	(0)
#define DOWNCUR_PY	(224)
#define DOWNCUR_ANMNO	(1)

static const TCATS_RESOURCE_FILE_LIST FCA_ResFileList = {
	"data/fcomact_chr.resdat",	// キャラクタ
	"data/fcomact_pal.resdat",	// パレット
	"data/fcomact_cell.resdat",	// セル
	"data/fcomact_canm.resdat",	// セルアニメ
	NULL,						// マルチセル
	NULL,						// マルチセルアニメ
	"data/fcomact_h.cldat"		// ヘッダー
};

static const TCATS_OBJECT_ADD_PARAM_S ActAddParam_S[] =
{
	{	// アップカーソル
		CURSOR_PX, UPCUR_PY, 0,
		UPCUR_ANMNO, CURSOR_SPRI, CURSOR_PAL, NNS_G2D_VRAM_TYPE_2DMAIN,
		{
			FCOMACT_CHR_H_ID_CURSOR, FCOMACT_PAL_H_ID,
			FCOMACT_CEL_H_ID_CURSOR, FCOMACT_ANM_H_ID_CURSOR, 0, 0,
		},
		CURSOR_PRI, 0
	},
	{	//ダウンカーソル 
		CURSOR_PX, DOWNCUR_PY, 0,
		DOWNCUR_ANMNO, CURSOR_SPRI, CURSOR_PAL, NNS_G2D_VRAM_TYPE_2DMAIN,
		{
			FCOMACT_CHR_H_ID_CURSOR, FCOMACT_PAL_H_ID,
			FCOMACT_CEL_H_ID_CURSOR, FCOMACT_ANM_H_ID_CURSOR, 0, 0,
		},
		CURSOR_PRI, 0
	},
};

/**
 *	@brief	フィールドイベント　共通セルアクター初期化
 */
FLD_COMACT_WORK* FComAct_Init(int heapID)
{
	TCATS_RESOURCE_NUM_LIST	crnl = {
		FCOMACT_CHR_RES_MAX, FCOMACT_PAL_RES_MAX,
		FCOMACT_CEL_RES_MAX, FCOMACT_ANM_RES_MAX, 0, 0
	};
	
	u32	i;
	FLD_COMACT_WORK* wk;
	
	wk = sys_AllocMemory(heapID,sizeof(FLD_COMACT_WORK));
	MI_CpuClear8(wk,sizeof(FLD_COMACT_WORK));

	//フィールドセルアクター初期化
	FieldCellActSet_S( &wk->fcat, &crnl, FCA_ACTMAX, HEAPID_WORLD );

	FldClact_LoadResPlttArc(
		&wk->fcat, ARC_FLDCOMACT_GRA,NARC_fld_comact_fld_comact_nclr,
		0, 2, NNS_G2D_VRAM_TYPE_2DMAIN, FCOMACT_PAL_H_ID );

	FldClact_LoadResCellArc(
		&wk->fcat, ARC_FLDCOMACT_GRA, NARC_fld_comact_fld_comact_ncer,
		0, FCOMACT_CEL_H_ID_CURSOR );

	FldClact_LoadResCellAnmArc(
		&wk->fcat, ARC_FLDCOMACT_GRA, NARC_fld_comact_fld_comact_nanr,
		0, FCOMACT_ANM_H_ID_CURSOR );

	FldClact_LoadResourceCharArc(
		&wk->fcat, ARC_FLDCOMACT_GRA, NARC_fld_comact_fld_comact_ncgr,
		0, NNS_G2D_VRAM_TYPE_2DMAIN, FCOMACT_CHR_H_ID_CURSOR );

	for(i = 0;i < FCA_ACTMAX;i++){
		wk->act[i] = FieldCellActAdd_S( &wk->fcat, &ActAddParam_S[i] );
	}
	return wk;
}

/**
 *	@brief	コントローラー破棄
 */
void FComAct_Delete(FLD_COMACT_WORK* wk)
{
	int i;

	for(i = 0;i < FCA_ACTMAX;i++){
		if(wk->act[i] != NULL){
			CATS_ActorPointerDelete_S(wk->act[i]);
		}
	}
	FieldCellActDelete_S(&wk->fcat);

	sys_FreeMemoryEz(wk);
}

/**
 *	@brief	セルアクターコントロール
 */
void FActCom_Main(FLD_COMACT_WORK* wk)
{
	int i = 0;

	for(i = 0;i < FCA_ACTMAX;i++){
		if(wk->act[i] != NULL){
			CLACT_AnmFrameChg(wk->act[i]->act,FX32_ONE);
		}
	}
	CLACT_Draw(wk->fcat.cas);
}

/**
 *	@brief	カーソルポジションセット
 *
 *	@param	px	カーソルX座標
 *	@param	uy	アップカーソルY座標
 *	@param	dy	ダウンカーソルY座標
 */
void FComAct_CursorPosSet(FLD_COMACT_WORK* wk,s16 px,s16 uy,s16 dy)
{
	CATS_ObjectPosSetCap(wk->act[FCA_UCURSOR],px,uy);
	CATS_ObjectPosSetCap(wk->act[FCA_DCURSOR],px,dy);
}

/**
 *	@brief	描画状態コントロール
 *
 *	@param	vanish	TRUE:描画,FALSE:バニッシュ
 */
void FComAct_SetDrawFlg(FLD_COMACT_WORK* wk,u16 idx,BOOL draw)
{
	if(idx >= FCA_ACTMAX){
		return;
	}
	CATS_ObjectEnableCap(wk->act[idx],draw);
}

/**
 *	@brief	オートアニメ状態コントロール
 *
 *	@param	anm	TRUE:オートアニメ,FALSE:オートアニメOff
 */
void FComAct_SetAutoAnmFlg(FLD_COMACT_WORK* wk,u16 idx,BOOL anm)
{
	if(idx >= FCA_ACTMAX){
		return;
	}
	CATS_ObjectAutoAnimeSetCap(wk->act[idx],anm);
}
