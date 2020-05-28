/**
 *	@file	tmap_sub.h
 *	@brief	タウンマップ　サブツール群
 *	@author	Miyuki Iwasawa
 *	@date	06.04.01
 */

#ifndef __H_TMAP_SUB_H__
#define __H_TMAP_SUB_H__

////////////////////////////////////////////////////////////////
///タウンView用データ構造体
typedef struct _TOWN_VIEW{
	int		zoneID;	//<ゾーンID
	int		sysflag;	//<システムフラグ参照ID
	u8		ptn;	//<画像パターン	
	u8		typ;	//<画像パターン	
	u16		r;	//<回転角
	fx32	x;	//<x座標
	fx32	z;	//<y座標
}TOWN_VIEW;

typedef struct _TMAP_VIEW_OBJ{
	TOWN_VIEW	prm;
	int		flag;
	CLACT_WORK_PTR	pAct;
}TMAP_VIEW_OBJ;

typedef struct _TMAP_VIEW_DAT{
	u16	dat_num;
	u8	selCount;
	u8	selFrame;

	TMAP_VIEW_OBJ *selPos;
	TMAP_VIEW_OBJ *pDat;
}TMAP_VIEW_DAT;

//////////////////////////////////////////////////////////////
///タウンマップ用データ型
typedef struct _TMAP_GDAT{
	u16	x;			//<グリッド座標X
	u16	z;			//<グリッド座標Z
	u16	kType;		//<看板タイプ定義
	u16 kIdx;		//<看板IndexNo
	u16	gmes01;		//<ガイドメッセージ01インデックス
	u16	gmes02;		//<ガイドメッセージ02インデックス
	u16	gmes01_ox;	//<ガイドメッセージ01表示オフセットX
	u16	gmes01_oy;	//<ガイドメッセージ01表示オフセットY
	u16	gmes02_ox;	//<ガイドメッセージ02表示オフセットX
	u16	gmes02_oy;	//<ガイドメッセージ02表示オフセットY
	u16	view;		//<Viewフラグ
	u16	id;			//<ID
}TMAP_GDAT;

typedef struct _TMAP_GDAT_LIST{
	int	num;	///<データ数
	TMAP_GDAT *pDat;	//データ配列
}TMAP_GDAT_LIST;


//========================================================================
//サブツール群外部参照定義エリア
//

/**
 *	@brief	タウンViewリソース作成
 *
 *	@param	actSys	初期化済みセルアクターシステム
 *	@param	actRes	初期化済みセルアクターリソース
 *
 *	@param	dat_num	データ数
 *	@param	heapID	ヒープID
 */
extern TMAP_VIEW_DAT* TownViewDataCreate(CATS_SYS_PTR actSys,CATS_RES_PTR actRes,
		u8 *arrive,short dat_num,int heapID);

/**
 *	@brief	タウンViewリソース解放
 */
extern void TownViewDataRelease(TMAP_VIEW_DAT* wp);

/**
 *	@brief	タウンView 基本描画
 */
extern void TownViewDataDraw(TMAP_VIEW_DAT* wp,int mode);

/**
 *	タウンView データ中から特定のZoneIDを持つものを探す
 */
extern TMAP_VIEW_OBJ* TownViewDataSearchPos(TMAP_VIEW_DAT* wp,int zoneID,int x,int z);

/**
 *	@brief	タウンView
 */
extern int TownViewDataSelectPos(TMAP_VIEW_DAT* wp,int zoneID,int x,int z);

//============================================================
//マップブロックデータ参照関連
//============================================================
/**
 *	@brief	マップブロックデータロード
 */
extern TMAP_GDAT_LIST* TMapBlockDataLoad(const char* path,int heapID);

/**
 *	@brief	マップブロックデータ解放
 */
extern void TMapBlockDataRelease(TMAP_GDAT_LIST* pWork);

/**
 *	@brief	マップブロックデータ　ブロックデータ取得
 *
 *	@param	pWork	データリスト配列の先頭ポインタ
 *	@param	x		検索するブロックのX座標
 *	@param	z		検索するブロックのZ座標
 *	@param	mapView	配布マップ描画フラグ
 *	ブロックのx,z座標からブロックデータへのポインタを取得する
 *	見つからなかった場合NULLを返す
 */
extern TMAP_GDAT* TMapBlockDataGet(TMAP_GDAT_LIST* pWork,int x,int z,u16 mapView);


#endif	//__H_TMAP_SUB_H__

