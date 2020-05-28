#ifndef _TRAINER_CARD_OBJ_H_
#define _TRAINER_CARD_OBJ_H_

#include "system/clact_tool.h"

// CellActorに処理させるリソースマネージャの種類の数（＝マルチセル・マルチセルアニメは使用しない）
#define RESOURCE_NUM		(4)
#define TR_CARD_BADGE_ACT_MAX	(8)
#define TR_CARD_STAR_ACT_MAX	(8)
#define TR_CARD_GRATE_STAR_ACT_MAX	(8)
#define TR_CARD_BTNEFF_ACT_MAX	(1)

#define TR_CARD_BADGE_ACT_START	(0)
#define TR_CARD_STAR_ACT_START	( TR_CARD_BADGE_ACT_MAX )
#define TR_CARD_GRATE_STAR_ACT_START	(TR_CARD_STAR_ACT_START+TR_CARD_STAR_ACT_MAX)
#define TR_CARD_BTNEFF_ACT_START	(TR_CARD_GRATE_STAR_ACT_START+TR_CARD_GRATE_STAR_ACT_MAX)

#define TR_CARD_ACT_MAX	(TR_CARD_BADGE_ACT_MAX+TR_CARD_STAR_ACT_MAX+\
		TR_CARD_GRATE_STAR_ACT_MAX+TR_CARD_BTNEFF_ACT_MAX)

///typedef struct TR_CARD_OBJ_WORK_tag *TR_CARD_OBJ_PTR;

typedef struct TR_CARD_OBJ_WORK_tag
{
	CLACT_SET_PTR 			ClactSet;								// セルアクターセット
	CLACT_U_EASYRENDER_DATA	RendData;								// 簡易レンダーデータ
	CLACT_U_RES_MANAGER_PTR	ResMan[RESOURCE_NUM];				// リソースマネージャ
	CLACT_U_RES_OBJ_PTR 	ResObjTbl[2][RESOURCE_NUM];		// リソースオブジェテーブル(上下画面)
	///CLACT_HEADER			ClActHeader_m;							// セルアクターヘッダー(メイン)
	///CLACT_HEADER			ClActHeader_s;							// セルアクターヘッダー(サブ)
	CLACT_WORK_PTR			ClActWork[TR_CARD_ACT_MAX];				// セルアクターワークポインタ配列

	void *PalDataBuf[TR_CARD_BADGE_ACT_MAX];		//パレットデータTR_CARD_BADGE_ACT_MAX分
	NNSG2dPaletteData *PalData[TR_CARD_BADGE_ACT_MAX];	//パレットデータTR_CARD_BADGE_ACT_MAX分
}TR_CARD_OBJ_WORK;


extern void InitTRCardCellActor( TR_CARD_OBJ_WORK *wk );
extern void SetTrCardActor( TR_CARD_OBJ_WORK *wk, const u8 *inBadgeDisp );
extern void RereaseCellObject(TR_CARD_OBJ_WORK *wk);

extern void SetBadgePalette(TR_CARD_OBJ_WORK *wk,
							const u8 inBadgeNo,
							const u8 inPalNo );

#endif //_TRAINER_CARD_OBJ_H_

