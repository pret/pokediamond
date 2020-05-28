/**
 *	@file	poru_oam.c
 *	@brief	ポルトアクター　OAMコントローラ
 *	@author	Miyuki Iwasawa
 *	@date	06.03.28
 */

#include "common.h"
#include "system/clact_tool.h"

#define PORUTO_OAM_H_GLOBAL
#include "poru_oam.h"
#include "poruact.naix"

#define PORUOAM_PAL_MAX	(16)

#define RES_CHRID	(NARC_poruact_poru_act_ncgr)
#define RES_CELID	(NARC_poruact_poru_act_ncer)
#define RES_ANMID	(NARC_poruact_poru_act_nanr)
#define RES_PALID	(NARC_poruact_poru_001_nclr)
#define RES_NOCOMP	(0)
#define RES_NOTRANS	(0)
#define RES_HEADID (0xe000)

enum{
 RESTYPE_CHR,
 RESTYPE_PAL,
 RESTYPE_CEL,
 RESTYPE_ANM,
};

#define PORUOAM_CHR_RES_MAX	(1)
#define PORUOAM_PAL_RES_MAX	(1)
#define PORUOAM_CEL_RES_MAX	(1)
#define PORUOAM_ANM_RES_MAX	(1)


//======================================================
//プロトタイプ
//======================================================
static void PoruOam_ResManagerInit(PORUOAM_MAN* wk);
static void PoruOam_ResManagerRelease(PORUOAM_MAN* wk);

static void poam_LoadResArc(PORUOAM_MAN* wk);
static s16 poam_GetNullWork(PORUOAM_MAN* wk,u8 flavor);

/**
 *	@brief	ポルトアクター　マネージャ初期化
 *
 *	@param	heapID	ヒープID
 *	@param	actmax	確保するセルアクター領域の個数
 *	@param	palmax	ポルト用に占有するOBJパレットの本数
 *	@param	vramType	描画画面指定(PORUOAM_DRAW_MAIN/SUB/BOTH)
 *  @param	cgx_transofs	キャラクタ転送オフセット指定
 *							(PORUOAM_CGXOFS_AREAを指定した場合、空き領域検索モードになる)	
 */
PORUOAM_MAN* PoruOam_SysInit(int heapID,u16 actmax,u16 palmax,
		u16 vramType,PORUOAM_CGXOFS cgx_transofs)
{
	PORUOAM_MAN* wk;

	wk = sys_AllocMemory(heapID,sizeof(PORUOAM_MAN));
	MI_CpuClear8(wk,sizeof(PORUOAM_MAN));

	//パラメータ保存
	wk->heapID = heapID;

	if(actmax > PORUOAM_PAL_MAX){
		wk->pal_num = PORUOAM_PAL_MAX;
	}else{
		wk->pal_num = palmax;
	}
	wk->act_max = actmax;
	wk->vramType = vramType;
	wk->cgx_transofs = cgx_transofs;
	
	PoruOam_ResManagerInit(wk);
	return wk;
}

/**
 *	@brief	ポルトアクター　マネージャ解放
 */
void PoruOam_SysRelease(PORUOAM_MAN* wk)
{
	PoruOam_ResManagerRelease(wk);
	MI_CpuClear8(wk,sizeof(PORUOAM_MAN));
	sys_FreeMemoryEz(wk);
}


/**
 *	@brief	リソースマネージャ作成
 */
static void PoruOam_ResManagerInit(PORUOAM_MAN* wk)
{
	u32 i, j;
	u8	resnum[] = {PORUOAM_CHR_RES_MAX,1,PORUOAM_CEL_RES_MAX,PORUOAM_ANM_RES_MAX};

	wk->cas  = CLACT_U_SetEasyInit(wk->act_max, &wk->renddata,wk->heapID);

	// リソースマネージャー作成&テーブル初期化
	resnum[RESTYPE_PAL] = wk->pal_num;
	for( i=0; i< PORUOAM_RESMAX; i++ ){
		wk->resMan[i] = CLACT_U_ResManagerInit(resnum[i],i, wk->heapID );
		wk->resObjTbl[i] = CLACT_U_ResManagerResObjTblMake(resnum[i],wk->heapID);
		for( j=0; j<wk->resObjTbl[i]->tbl_num; j++ ){
			wk->resObjTbl[i]->tbl[j] = NULL;
		}
	}

	//リソースロード
	poam_LoadResArc(wk);

	//パレットワーク確保
	wk->work = sys_AllocMemory(wk->heapID,sizeof(PORUOAM_ACTWORK));
	MI_CpuClear8(wk->work,sizeof(PORUOAM_ACTWORK));
}

/**
 *	@brief	リソースマネージャ解放
 */
static void PoruOam_ResManagerRelease(PORUOAM_MAN* wk)
{
	u32	i;

	//パレットワーク破棄
	sys_FreeMemoryEz(wk->work);

	CLACT_DestSet( wk->cas );	// セット破棄
	CLACT_U_CharManagerDeletes( wk->resObjTbl[RESTYPE_CHR] );	// キャラデータ破棄
	CLACT_U_PlttManagerDeletes( wk->resObjTbl[RESTYPE_PAL] );	// パレットデータ破棄

	for( i=0; i<PORUOAM_RESMAX; i++ ){
		// リソースオブジェテーブル破棄
		CLACT_U_ResManagerResObjTblDelete( wk->resObjTbl[i] );
		// リソースマネージャ破棄
		CLACT_U_ResManagerDelete( wk->resMan[i] );
	}
}

/**
 *	@brief	ポルトOAM　描画メイン
 */
void PoruOam_DrawMain(PORUOAM_MAN* wk)
{
	CLACT_Draw(wk->cas);
}

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
PORUTO_OAM* PoruOam_Add(PORUOAM_MAN* wk,PORUTO_FLAVORID flavor,
		u16 x,u16 y,u16 z,u8 bg_pri,u8 spri,PORUOAM_VRAMTYPE vtype)
{
	u8	vram_type;
	s16	idx;
	u32	palid;
	PORUTO_OAM* oam;
	CATS_ACT_PTR cap = NULL;
	CLACT_ADD	 add;
	CLACT_U_RES_OBJ_PTR	obj;

	//ワークの空き領域を探す
	idx = poam_GetNullWork(wk,flavor);
	if(idx < 0){
		//空き領域がない
		GF_ASSERT(0 && "PoruOam_Add->work was full");
		return NULL;
	}

	//OAMワーク確保
	oam = sys_AllocMemory(wk->heapID,sizeof(PORUTO_OAM));
	MI_CpuClear8(oam,sizeof(PORUTO_OAM));
	oam->workID = idx;
	
	if(vtype == PORUOAM_VT_MAIN){
		vram_type = NNS_G2D_VRAM_TYPE_2DMAIN;
	}else{
		vram_type = NNS_G2D_VRAM_TYPE_2DSUB;
	}

	obj = wk->resObjTbl[RESTYPE_PAL]->tbl[idx];
	//パレットリソース読み替え
	CLACT_U_ResManagerResChgArcPltt(wk->resMan[RESTYPE_PAL],
		wk->resObjTbl[RESTYPE_PAL]->tbl[idx],
		ARC_PORUACT_GRA,RES_PALID+flavor,RES_NOCOMP,wk->heapID);
	CLACT_U_PlttManagerReTrans(wk->resObjTbl[RESTYPE_PAL]->tbl[idx]);

	//ワークメモリ確保
	cap = sys_AllocMemory(wk->heapID, sizeof(TCATS_ACT) );

	//ヘッダーメモリ確保
	cap->act_htp = sys_AllocMemory(wk->heapID,sizeof(CLACT_HEADER_TBL));
	cap->act_htp->tbl = sys_AllocMemory(wk->heapID,sizeof(CLACT_HEADER));
	cap->act_hd = cap->act_htp->tbl;

	//ヘッダー生成
	CLACT_U_MakeHeader(
		cap->act_hd,
		RES_HEADID,RES_HEADID+idx,
		RES_HEADID,RES_HEADID,
		CLACT_U_HEADER_DATA_NONE,CLACT_U_HEADER_DATA_NONE,
		RES_NOTRANS, bg_pri,
		wk->resMan[RESTYPE_CHR],wk->resMan[RESTYPE_PAL],
		wk->resMan[RESTYPE_CEL],wk->resMan[RESTYPE_ANM],
		NULL,NULL);	

	// OAM登録
	add.ClActSet	= wk->cas;
	add.ClActHeader = cap->act_hd;

	add.mat.x		= FX32_CONST(x);
	add.mat.y		= FX32_CONST(y);
	add.mat.z		= FX32_CONST(z);
	if(vram_type == NNS_G2D_VRAM_TYPE_2DSUB){
		add.mat.y += SUB_SURFACE_Y;
	}
	
	add.sca.x		= FX32_ONE;			// 拡縮率
	add.sca.y		= FX32_ONE;
	add.sca.z		= FX32_ONE;
	
	add.rot			= 0;				// 回転角
	add.pri			= spri;				// 優先度
	add.DrawArea	= vram_type;		// 描画面
	add.heap		= wk->heapID;		// ヒープID
	
	cap->act = CLACT_Add(&add);			//登録処理
	
	if (cap->act != NULL){
		CLACT_AnmChg(cap->act,0);		//アニメーション指定
		palid = CLACT_U_PlttManagerGetPlttNo(
			obj,vram_type);
		CLACT_PaletteNoChg(cap->act,palid);		//パレット指定
	}
	else{
		GF_ASSERT(0 &&"poruto oam add failed");
	}
	oam->act = cap;
	return oam;		
}

/**
 *	@brief	登録済みOAMのポルトの種類を変更する
 *	
 *	@param	flavor	ポルトの種類ID
 */
void PoruOam_ChangeFlavor(PORUOAM_MAN*wk,PORUTO_OAM* oam,PORUTO_FLAVORID flavor)
{
	CLACT_U_RES_OBJ_PTR	obj;

	obj = wk->resObjTbl[RESTYPE_PAL]->tbl[oam->workID];

	//パレットリソース読み替え
	CLACT_U_ResManagerResChgArcPltt(wk->resMan[RESTYPE_PAL],
		obj,ARC_PORUACT_GRA,RES_PALID+flavor,RES_NOCOMP,wk->heapID);
	CLACT_U_PlttManagerReTrans(obj);
}

/**
 *	@brief	ポルトOAM削除
 */
void PoruOam_Del(PORUOAM_MAN* wk,PORUTO_OAM* oam)
{
	//アクター削除
	CATS_ActorPointerDelete_S(oam->act);
	
	//ワーク解放
	wk->work[oam->workID].valid = 0;
	wk->work[oam->workID].resNo = 0;
	wk->work[oam->workID].flavor = 0;

	sys_FreeMemoryEz(oam);
}

/**
 *	@brief	リソース初期設定
 */
static void poam_LoadResArc(PORUOAM_MAN* wk)
{
	int i;
	CLACT_U_RES_MANAGER_PTR	res;
	CLACT_U_RES_OBJ_TBL* obj;
	CLACT_U_RES_OBJ_PTR tmp;

	//キャラクタリソース取得
	obj = wk->resObjTbl[RESTYPE_CHR];
	obj->tbl[0] = CLACT_U_ResManagerResAddArcChar(wk->resMan[RESTYPE_CHR],
		ARC_PORUACT_GRA,RES_CHRID,RES_NOCOMP,RES_HEADID,wk->vramType,wk->heapID);
	
	GF_ASSERT((obj->tbl[0]!=NULL)&&"poam char resload failed");

	switch(wk->cgx_transofs){
	case PORUOAM_CGXOFS_AREA:
		CLACT_U_CharManagerSetAreaCont(obj->tbl[0]);
		break;
	case PORUOAM_CGXOFS_ADJUST:
		CLACT_U_CharManagerSetCharModeAdjustAreaCont(obj->tbl[0]);
		break;
	case PORUOAM_CGXOFS_AUTO:
	default:
		CLACT_U_CharManagerSet(obj->tbl[0]);
		break;
	}

	//セル&セルアニメリソース取得
	for(i = 0;i < 2;i++){
		obj = wk->resObjTbl[RESTYPE_CEL+i];
		obj->tbl[0] = CLACT_U_ResManagerResAddArcKindCell(wk->resMan[RESTYPE_CEL+i],
			ARC_PORUACT_GRA,RES_CELID+i,RES_NOCOMP,RES_HEADID,RESTYPE_CEL+i,wk->heapID);
	
		GF_ASSERT((obj->tbl[0]!=NULL)&&"poam cell&canm resload failed");
	}

	//初期パレットリソース取得(No.001で全部を初期化する)
	obj = wk->resObjTbl[RESTYPE_PAL];
	for(i = 0;i < wk->pal_num;i++){
		obj->tbl[i] = CLACT_U_ResManagerResAddArcPltt(wk->resMan[RESTYPE_PAL],
			ARC_PORUACT_GRA,RES_PALID+1,RES_NOCOMP,RES_HEADID+i,wk->vramType,1,wk->heapID);
		
		GF_ASSERT((obj->tbl[i]!=NULL)&&"poam pal resload failed");
//		CLACT_U_PlttManagerSetCleanArea(obj->tbl[i]);
		CLACT_U_PlttManagerSet(obj->tbl[i]);
	}
}

/**
 *	@brief	空きワークを探す
 */
static s16 poam_GetNullWork(PORUOAM_MAN* wk,u8 flavor)
{
	u16 i = 0;

	for(i = 0;i < wk->pal_num;i++){
		if(!wk->work[i].valid){
			wk->work[i].resNo = i;
			wk->work[i].flavor = flavor;
			wk->work[i].valid = 1;
			return i;
		}
	}
	return -1;
}
