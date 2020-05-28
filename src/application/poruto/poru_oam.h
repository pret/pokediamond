/**
 *	@file	poru_oam.h
 *	@brief	ポルトOAMオブジェクトコントローラー
 *	@author	Miyuki Iwasawa
 *	@date	06.03.29
 */

#ifndef __H_PORUTO_OAM_H__
#define __H_PORUTO_OAM_H___

#undef GLOBAL
#ifndef PORUTO_OAM_H_GLOBAL
#define GLOBAL	/***/
#else
#define GLOBAL	extern
#endif

#include "savedata/poruto_def.h"

//=================================================
///構造体定義
//=================================================
#define PORUOAM_RESMAX	(4)
#define PORUOAM_DRAW_MAIN	(NNS_G2D_VRAM_TYPE_2DMAIN)
#define PORUOAM_DRAW_SUB	(NNS_G2D_VRAM_TYPE_2DSUB)
#define PORUOAM_DRAW_BOTH	(NNS_G2D_VRAM_TYPE_2DMAX)

typedef enum{
 PORUOAM_CGXOFS_AUTO,
 PORUOAM_CGXOFS_AREA,
 PORUOAM_CGXOFS_ADJUST,
}PORUOAM_CGXOFS;


typedef enum{
 PORUOAM_VT_MAIN,	//メイン画面に描画
 PORUOAM_VT_SUB,	//サブ画面に描画
}PORUOAM_VRAMTYPE;

typedef struct{
	u8	valid;
	u8	flavor;
	u16	resNo;
}PORUOAM_ACTWORK;

typedef struct{
	u16	workID;
	CATS_ACT_PTR	act;
}PORUTO_OAM;

typedef struct {
	int	heapID;
	int	cgx_transofs;	///<CGX転送オフセット
	u16	res_max;
	u16	pal_num;
	u16	act_max;
	u16	vramType;

	CLACT_SET_PTR	cas;
	CLACT_U_EASYRENDER_DATA	renddata;	// 簡易レンダーデータ
	CLACT_HEADER_TBL_PTR	clh;		// ヘッダー
	CLACT_U_RES_MANAGER_PTR	resMan[PORUOAM_RESMAX];	///< リソースマネージャ
	CLACT_U_RES_OBJ_TBL * resObjTbl[PORUOAM_RESMAX];///< リソースオブジェテーブル

	PORUOAM_ACTWORK* work;
}PORUOAM_MAN;

/**
 *	@brief	ポルトアクター　マネージャ初期化
 *
 *	@param	heapID	ヒープID
 *	@param	actmax	確保するセルアクター領域の個数
 *	@param	palmax	ポルト用に占有するOBJパレットの本数
 *	@param	vramType	描画画面指定(PORUOAM_DRAW_MAIN/SUB/BOTH)
 *  @param	cgx_transofs	キャラクタ転送オフセットモード指定
 *							(PORUOAM_CGXOFS型	PORUOAM_CGXOFS_AUTO:0から積み上げ型
 *												PORUOAM_CGXOFS_AREA:空き領域検索型
 */
GLOBAL PORUOAM_MAN* PoruOam_SysInit(int heapID,u16 actmax,u16 palmax,
		u16 vramType,PORUOAM_CGXOFS cgx_transofs);

/**
 *	@brief	ポルトアクター　マネージャ解放
 */
GLOBAL void PoruOam_SysRelease(PORUOAM_MAN* wk);


/**
 *	@brief	ポルトOAM　描画メイン
 */
GLOBAL void PoruOam_DrawMain(PORUOAM_MAN* wk);


/**
 *	@brief	ポルトOAM追加
 *
 *	@param	flavor	ポルトの種類ID
 *	@param	x		X座標
 *	@param	y		Y座標
 *	@param	z		Z座標
 *	@param	bg_pri	BGプライオリティ
 *	@param	spri	ソフトウェアプライオリティ
 *	@param	vram_type	PORUOAM_VRAMTYPE型
 *						PORUOAM_VT_MAIN:メイン画面
 *						PORUOAM_VT_SUB:サブ画面
 *
 *	＊必ずPoruOam_Del関数で破棄すること
 */
GLOBAL PORUTO_OAM* PoruOam_Add(PORUOAM_MAN* wk,PORUTO_FLAVORID flavor,
		u16 x,u16 y,u16 z,u8 bg_pri,u8 spri,PORUOAM_VRAMTYPE vtype);

/**
 *	@brief	登録済みOAMのポルトの種類を変更する
 *	
 *	@param	flavor	ポルトの種類ID
 */
GLOBAL void PoruOam_ChangeFlavor(PORUOAM_MAN*wk,PORUTO_OAM* oam,PORUTO_FLAVORID flavor);

/**
 *	@brief	ポルトOAM削除
 */
GLOBAL void PoruOam_Del(PORUOAM_MAN* wk,PORUTO_OAM* oam);


#endif	//__H_PORTO_OAM_H__
