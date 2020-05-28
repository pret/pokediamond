//==============================================================================
/**
 * @file	wazatype_icon.c
 * @brief	技タイプ＆分類アイコン
 * @author	matsuda
 * @date	2005.10.26(水)
 */
//==============================================================================
#include "common.h"
#include "system/clact_tool.h"
#include "system/arc_tool.h"
#include "system\arc_util.h"
#include "battle\graphic\batt_obj_def.h"
#include "battle/battle_common.h"
#include "battle/wazatype_icon.h"


//==============================================================================
//	データ
//==============================================================================
//--------------------------------------------------------------
//	技タイプ
//--------------------------------------------------------------
///技タイプ毎のCGRID
ALIGN4 static const u32 WazaTypeCgrNo[] = {
	P_ST_TYPE_NORMAL_NCGR_BIN,
	P_ST_TYPE_FIGHT_NCGR_BIN,
	P_ST_TYPE_FLIGHT_NCGR_BIN,
	P_ST_TYPE_POISON_NCGR_BIN,
	P_ST_TYPE_GROUND_NCGR_BIN,
	P_ST_TYPE_ROCK_NCGR_BIN,
	P_ST_TYPE_INSECT_NCGR_BIN,
	P_ST_TYPE_GHOST_NCGR_BIN,
	P_ST_TYPE_STEEL_NCGR_BIN,
	P_ST_TYPE_QUES_NCGR_BIN,
	P_ST_TYPE_FIRE_NCGR_BIN,
	P_ST_TYPE_WATER_NCGR_BIN,
	P_ST_TYPE_GRASS_NCGR_BIN,
	P_ST_TYPE_ELE_NCGR_BIN,
	P_ST_TYPE_ESP_NCGR_BIN,
	P_ST_TYPE_ICE_NCGR_BIN,
	P_ST_TYPE_DRAGON_NCGR_BIN,
	P_ST_TYPE_EVIL_NCGR_BIN,
	P_ST_TYPE_STYLE_NCGR_BIN,
	P_ST_TYPE_BEAUTIFUL_NCGR_BIN,
	P_ST_TYPE_CUTE_NCGR_BIN,
	P_ST_TYPE_INTELLI_NCGR_BIN,
	P_ST_TYPE_STRONG_NCGR_BIN,
};

///技タイプ毎のパレットオフセット番号
ALIGN4 static const u8 WazaTypePlttOffset[] = {
	0,	//NORMAL_TYPE
	0,	//BATTLE_TYPE
	1,	//HIKOU_TYPE
	1,	//POISON_TYPE
	0,	//JIMEN_TYPE
	0,	//IWA_TYPE
	2,	//MUSHI_TYPE
	1,	//GHOST_TYPE
	0,	//METAL_TYPE
	2,	//HATE_TYPE
	0,	//FIRE_TYPE
	1,	//WATER_TYPE
	2,	//KUSA_TYPE
	0,	//ELECTRIC_TYPE
	1,	//SP_TYPE
	1,	//KOORI_TYPE
	2,	//DRAGON_TYPE
	0,	//AKU_TYPE
	0,	//ICONTYPE_STYLE
	1,	//ICONTYPE_BEAUTIFUL
	1,	//ICONTYPE_CUTE
	2,	//ICONTYPE_INTELLI
	0,	//ICONTYPE_STRONG
};

//--------------------------------------------------------------
//	分類
//--------------------------------------------------------------
///分類毎のCGRID
ALIGN4 static const u32 WazaKindCgrNo[] = {
	P_ST_BUNRUI_BUTURI_NCGR_BIN,
	P_ST_BUNRUI_TOKUSYU_NCGR_BIN,
	P_ST_BUNRUI_HENKA_NCGR_BIN,
};

///分類毎のパレットオフセット番号
ALIGN4 static const u8 WazaKindPlttOffset[] = {
	0,		//KIND_BUTSURI
	1,		//KIND_TOKUSYU
	0,		//KIND_HENNKA
};



//==============================================================================
//
//	技タイプアイコン
//
//==============================================================================
//--------------------------------------------------------------
/**
 * @brief   指定技タイプのCGRIDを取得します
 * @param   waza_type		技タイプ(NORMAL_TYPE, FIRE_TYPE..等、又は ICONTYPE_???)
 * @retval  CGRID(ARCのデータINDEX)
 */
//--------------------------------------------------------------
u32 WazaTypeIcon_CgrIDGet(int waza_type)
{
	GF_ASSERT(waza_type < NELEMS(WazaTypeCgrNo));
	return WazaTypeCgrNo[waza_type];
}

//--------------------------------------------------------------
/**
 * @brief   技タイプアイコンのパレットIDを取得します
 * @retval  パレットID(ARCのデータINDEX)
 */
//--------------------------------------------------------------
u32 WazaTypeIcon_PlttIDGet(void)
{
	return ST_TYPE_NCLR;
}

//--------------------------------------------------------------
/**
 * @brief   指定技タイプのセルIDを取得します
 * @retval  セルID(ARCのデータINDEX)
 */
//--------------------------------------------------------------
u32 WazaTypeIcon_CellIDGet(void)
{
	return P_ST_TYPE_NORMAL_NCER_BIN;
}

//--------------------------------------------------------------
/**
 * @brief   指定技タイプのセルアニメIDを取得します
 * @retval  セルアニメID(ARCのデータINDEX)
 */
//--------------------------------------------------------------
u32 WazaTypeIcon_CellAnmIDGet(void)
{
	return P_ST_TYPE_NORMAL_NANR_BIN;
}

//--------------------------------------------------------------
/**
 * @brief   指定技タイプのパレット番号オフセットを取得します
 * @param   waza_type		技タイプ(NORMAL_TYPE, FIRE_TYPE..等、又は ICONTYPE_???)
 * @retval  パレット番号のオフセット
 */
//--------------------------------------------------------------
u8 WazaTypeIcon_PlttOffsetGet(int waza_type)
{
	GF_ASSERT(waza_type < NELEMS(WazaTypePlttOffset));
	return WazaTypePlttOffset[waza_type];
}

//--------------------------------------------------------------
/**
 * @brief   技タイプアイコンのアーカイブINDEXを取得します
 * @retval  アーカイブINDEX
 */
//--------------------------------------------------------------
u32 WazaTypeIcon_ArcIDGet(void)
{
	return ARC_BATT_OBJ;
}




//--------------------------------------------------------------
/**
 * @brief   指定技タイプのキャラリソースをロードします
 *
 * @param   csp				cspへのポインタ
 * @param   crp				crpへのポインタ
 * @param   vram_type		NNS_G2D_VRAM_TYPE_2DMAIN等
 * @param   waza_type		技タイプ(NORMAL_TYPE, FIRE_TYPE..等、又は ICONTYPE_???)
 * @param   char_id			登録するキャラID
 */
//--------------------------------------------------------------
void WazaTypeIcon_CharResourceLoad(CATS_SYS_PTR csp, CATS_RES_PTR crp, 
	NNS_G2D_VRAM_TYPE vram_type, int waza_type, u32 char_id)
{
	CATS_LoadResourceCharArc(csp, crp, WazaTypeIcon_ArcIDGet(), 
		WazaTypeIcon_CgrIDGet(waza_type), WAZATYPEICON_COMP_CHAR, vram_type, char_id);
}

//--------------------------------------------------------------
/**
 * @brief   技タイプアイコンのパレットをロードします
 *
 * @param   csp			cspへのポインタ
 * @param   crp			crpへのポインタ
 * @param   vram_type	NNS_G2D_VRAM_TYPE_2DMAIN等
 * @param   pltt_id		登録するパレットID
 *
 * 技タイプアイコンで使用するパレット全てをセットします。
 */
//--------------------------------------------------------------
void WazaTypeIcon_PlttResourceLoad(CATS_SYS_PTR csp, CATS_RES_PTR crp, 
	NNS_G2D_VRAM_TYPE vram_type, u32 pltt_id)
{
	CATS_LoadResourcePlttArc(csp, crp, WazaTypeIcon_ArcIDGet(), WazaTypeIcon_PlttIDGet(), 
		WAZATYPEICON_COMP_PLTT, WTI_PLTT_NUM, vram_type, pltt_id);
}

//--------------------------------------------------------------
/**
 * @brief   技タイプアイコンのパレットをパレットワークへロードします
 *
 * @param   PALETTE_FADE_PTR		パレットフェードシステムへのポインタ
 * @param   req						リクエストデータ番号(FADE_MAIN_BG等)
 * @param   csp			cspへのポインタ
 * @param   crp			crpへのポインタ
 * @param   vram_type	NNS_G2D_VRAM_TYPE_2DMAIN等
 * @param   pltt_id		登録するパレットID
 *
 * 技タイプアイコンで使用するパレット全てをセットします。
 */
//--------------------------------------------------------------
void WazaTypeIcon_PlttWorkResourceLoad(PALETTE_FADE_PTR pfd, FADEREQ req, CATS_SYS_PTR csp, 
	CATS_RES_PTR crp, NNS_G2D_VRAM_TYPE vram_type, u32 pltt_id)
{
	CATS_LoadResourcePlttWorkArc(pfd, req, csp, crp, 
		WazaTypeIcon_ArcIDGet(), WazaTypeIcon_PlttIDGet(), WAZATYPEICON_COMP_PLTT, 
		WTI_PLTT_NUM, vram_type, pltt_id);
}

//--------------------------------------------------------------
/**
 * @brief   技タイプアイコンのセルとアニメをロードします
 *
 * @param   csp			cspへのポインタ
 * @param   crp			crpへのポインタ
 * @param   cell_id		登録するセルID
 * @param   anm_id		登録するアニメID
 *
 * 技タイプアイコン共通のセルとアニメをロードします。
 * 技タイプアイコンは全てセルとアニメが共通なので、1つだけ登録しておけばOKです。
 * (複数のアイコンを生成する時でも、全てここで登録したセル、アニメIDを指定するようにします)
 */
//--------------------------------------------------------------
void WazaTypeIcon_CellAnmResourceLoad(CATS_SYS_PTR csp, CATS_RES_PTR crp, u32 cell_id, u32 anm_id)
{
	CATS_LoadResourceCellArc(csp, crp, WazaTypeIcon_ArcIDGet(), WazaTypeIcon_CellIDGet(), 
		WAZATYPEICON_COMP_CELL, cell_id);
	CATS_LoadResourceCellAnmArc(csp, crp, WazaTypeIcon_ArcIDGet(), WazaTypeIcon_CellAnmIDGet(), 
		WAZATYPEICON_COMP_CELLANM, anm_id);
}

//--------------------------------------------------------------
/**
 * @brief   技タイプアイコンのキャラリソースを解放します
 * @param   crp			crpへのポインタ
 * @param   char_id		解放するキャラID
 */
//--------------------------------------------------------------
void WazaTypeIcon_CharResourceFree(CATS_RES_PTR crp, u32 char_id)
{
	CATS_FreeResourceChar(crp, char_id);
}

//--------------------------------------------------------------
/**
 * @brief   技タイプアイコンのパレットリソースを解放します
 * @param   crp			crpへのポインタ
 * @param   pltt_id		解放するパレットID
 */
//--------------------------------------------------------------
void WazaTypeIcon_PlttResourceFree(CATS_RES_PTR crp, u32 pltt_id)
{
	CATS_FreeResourcePltt(crp, pltt_id);
}

//--------------------------------------------------------------
/**
 * @brief   技タイプアイコンのセル、アニメリソースを解放します
 * @param   crp			crpへのポインタ
 * @param   char_id		解放するセルID
 * @param   char_id		解放するアニメID
 */
//--------------------------------------------------------------
void WazaTypeIcon_CellAnmResourceFree(CATS_RES_PTR crp, u32 cell_id, u32 anm_id)
{
	CATS_FreeResourceCell(crp, cell_id);
	CATS_FreeResourceCellAnm(crp, anm_id);
}


//--------------------------------------------------------------
/**
 * @brief   技タイプアイコンアクターを生成する
 *
 * @param   csp				cspへのポインタ
 * @param   crp				crpへのポインタ
 * @param   waza_type		技タイプ(NORMAL_TYPE, FIRE_TYPE..等、又は ICONTYPE_???)
 * @param   obj_data		アクターヘッダへのポインタ
 *
 * @retval  生成したアクターのポインタ
 */
//--------------------------------------------------------------
CATS_ACT_PTR WazaTypeIcon_ActorCreate(CATS_SYS_PTR csp, CATS_RES_PTR crp, int waza_type, 
	const TCATS_OBJECT_ADD_PARAM_S *obj_data)
{
	CATS_ACT_PTR cap;
	TCATS_OBJECT_ADD_PARAM_S obj_param;
	
	obj_param = *obj_data;
	obj_param.pal = WazaTypeIcon_PlttOffsetGet(waza_type);
	
	cap = CATS_ObjectAdd_S(csp, crp, &obj_param);
	return cap;
}

//--------------------------------------------------------------
/**
 * @brief   技タイプアイコンアクターを削除
 * @param   cap		アクターポインタ
 */
//--------------------------------------------------------------
void WazaTypeIcon_ActorDelete(CATS_ACT_PTR cap)
{
	CATS_ActorPointerDelete_S(cap);
}










//==============================================================================
//
//	分類アイコン
//
//==============================================================================
//--------------------------------------------------------------
/**
 * @brief   指定技分類のCGRIDを取得します
 * @param   waza_kind		技分類(KIND_BUTURI or KIND_TOKUSYU or KIND_HENNKA)
 * @retval  CGRID(ARCのデータINDEX)
 */
//--------------------------------------------------------------
u32 WazaKindIcon_CgrIDGet(int waza_kind)
{
	GF_ASSERT(waza_kind < NELEMS(WazaKindCgrNo));
	return WazaKindCgrNo[waza_kind];
}

//--------------------------------------------------------------
/**
 * @brief   技分類アイコンのパレットIDを取得します
 * @retval  パレットID(ARCのデータINDEX)
 */
//--------------------------------------------------------------
u32 WazaKindIcon_PlttIDGet(void)
{
	return ST_TYPE_NCLR;
}

//--------------------------------------------------------------
/**
 * @brief   指定技分類のセルIDを取得します
 * @retval  セルID(ARCのデータINDEX)
 */
//--------------------------------------------------------------
u32 WazaKindIcon_CellIDGet(void)
{
	return P_ST_TYPE_NORMAL_NCER_BIN;
}

//--------------------------------------------------------------
/**
 * @brief   指定技分類のセルアニメIDを取得します
 * @retval  セルアニメID(ARCのデータINDEX)
 */
//--------------------------------------------------------------
u32 WazaKindIcon_CellAnmIDGet(void)
{
	return P_ST_TYPE_NORMAL_NANR_BIN;
}

//--------------------------------------------------------------
/**
 * @brief   指定技分類のパレット番号オフセットを取得します
 * @param   waza_kind		技分類(KIND_BUTURI or KIND_TOKUSYU or KIND_HENNKA)
 * @retval  パレット番号のオフセット
 */
//--------------------------------------------------------------
u8 WazaKindIcon_PlttOffsetGet(int waza_kind)
{
	GF_ASSERT(waza_kind < NELEMS(WazaKindPlttOffset));
	return WazaKindPlttOffset[waza_kind];
}

//--------------------------------------------------------------
/**
 * @brief   技分類アイコンのアーカイブINDEXを取得します
 * @retval  アーカイブINDEX
 */
//--------------------------------------------------------------
u32 WazaKindIcon_ArcIDGet(void)
{
	return ARC_BATT_OBJ;
}




//--------------------------------------------------------------
/**
 * @brief   指定技分類のキャラリソースをロードします
 *
 * @param   csp				cspへのポインタ
 * @param   crp				crpへのポインタ
 * @param   vram_type		NNS_G2D_VRAM_TYPE_2DMAIN等
 * @param   waza_kind		技分類(KIND_BUTURI or KIND_TOKUSYU or KIND_HENNKA)
 * @param   char_id			登録するキャラID
 */
//--------------------------------------------------------------
void WazaKindIcon_CharResourceLoad(CATS_SYS_PTR csp, CATS_RES_PTR crp, 
	NNS_G2D_VRAM_TYPE vram_type, int waza_kind, u32 char_id)
{
	CATS_LoadResourceCharArc(csp, crp, WazaKindIcon_ArcIDGet(), 
		WazaKindIcon_CgrIDGet(waza_kind), WAZAKINDICON_COMP_CHAR, vram_type, char_id);
}

//--------------------------------------------------------------
/**
 * @brief   技分類アイコンのパレットをロードします
 *
 * @param   csp			cspへのポインタ
 * @param   crp			crpへのポインタ
 * @param   vram_type	NNS_G2D_VRAM_TYPE_2DMAIN等
 * @param   pltt_id		登録するパレットID
 *
 * 技分類アイコンで使用するパレット全てをセットします。
 */
//--------------------------------------------------------------
void WazaKindIcon_PlttResourceLoad(CATS_SYS_PTR csp, CATS_RES_PTR crp, 
	NNS_G2D_VRAM_TYPE vram_type, u32 pltt_id)
{
	CATS_LoadResourcePlttArc(csp, crp, WazaKindIcon_ArcIDGet(), WazaKindIcon_PlttIDGet(), 
		WAZAKINDICON_COMP_PLTT, WKI_PLTT_NUM, vram_type, pltt_id);
}

//--------------------------------------------------------------
/**
 * @brief   技分類アイコンのパレットをパレットワークへロードします
 *
 * @param   PALETTE_FADE_PTR		パレットフェードシステムへのポインタ
 * @param   req						リクエストデータ番号(FADE_MAIN_BG等)
 * @param   csp			cspへのポインタ
 * @param   crp			crpへのポインタ
 * @param   vram_type	NNS_G2D_VRAM_TYPE_2DMAIN等
 * @param   pltt_id		登録するパレットID
 *
 * 技分類アイコンで使用するパレット全てをセットします。
 */
//--------------------------------------------------------------
void WazaKindIcon_PlttWorkResourceLoad(PALETTE_FADE_PTR pfd, FADEREQ req, CATS_SYS_PTR csp, 
	CATS_RES_PTR crp, NNS_G2D_VRAM_TYPE vram_type, u32 pltt_id)
{
	CATS_LoadResourcePlttWorkArc(pfd, req, csp, crp, 
		WazaKindIcon_ArcIDGet(), WazaKindIcon_PlttIDGet(), WAZAKINDICON_COMP_PLTT, 
		WKI_PLTT_NUM, vram_type, pltt_id);
}

//--------------------------------------------------------------
/**
 * @brief   技分類アイコンのセルとアニメをロードします
 *
 * @param   csp			cspへのポインタ
 * @param   crp			crpへのポインタ
 * @param   cell_id		登録するセルID
 * @param   anm_id		登録するアニメID
 *
 * 技分類アイコン共通のセルとアニメをロードします。
 * 技分類アイコンは全てセルとアニメが共通なので、1つだけ登録しておけばOKです。
 * (複数のアイコンを生成する時でも、全てここで登録したセル、アニメIDを指定するようにします)
 */
//--------------------------------------------------------------
void WazaKindIcon_CellAnmResourceLoad(CATS_SYS_PTR csp, CATS_RES_PTR crp, u32 cell_id, u32 anm_id)
{
	CATS_LoadResourceCellArc(csp, crp, WazaKindIcon_ArcIDGet(), WazaKindIcon_CellIDGet(), 
		WAZAKINDICON_COMP_CELL, cell_id);
	CATS_LoadResourceCellAnmArc(csp, crp, WazaKindIcon_ArcIDGet(), WazaKindIcon_CellAnmIDGet(), 
		WAZAKINDICON_COMP_CELLANM, anm_id);
}

//--------------------------------------------------------------
/**
 * @brief   技分類アイコンのキャラリソースを解放します
 * @param   crp			crpへのポインタ
 * @param   char_id		解放するキャラID
 */
//--------------------------------------------------------------
void WazaKindIcon_CharResourceFree(CATS_RES_PTR crp, u32 char_id)
{
	CATS_FreeResourceChar(crp, char_id);
}

//--------------------------------------------------------------
/**
 * @brief   技分類アイコンのパレットリソースを解放します
 * @param   crp			crpへのポインタ
 * @param   pltt_id		解放するパレットID
 */
//--------------------------------------------------------------
void WazaKindIcon_PlttResourceFree(CATS_RES_PTR crp, u32 pltt_id)
{
	CATS_FreeResourcePltt(crp, pltt_id);
}

//--------------------------------------------------------------
/**
 * @brief   技分類アイコンのセル、アニメリソースを解放します
 * @param   crp			crpへのポインタ
 * @param   char_id		解放するセルID
 * @param   char_id		解放するアニメID
 */
//--------------------------------------------------------------
void WazaKindIcon_CellAnmResourceFree(CATS_RES_PTR crp, u32 cell_id, u32 anm_id)
{
	CATS_FreeResourceCell(crp, cell_id);
	CATS_FreeResourceCellAnm(crp, anm_id);
}


//--------------------------------------------------------------
/**
 * @brief   技分類アイコンアクターを生成する
 *
 * @param   csp				cspへのポインタ
 * @param   crp				crpへのポインタ
 * @param   waza_kind		技分類(KIND_BUTURI or KIND_TOKUSYU or KIND_HENNKA)
 * @param   obj_data		アクターヘッダへのポインタ
 *
 * @retval  生成したアクターのポインタ
 */
//--------------------------------------------------------------
CATS_ACT_PTR WazaKindIcon_ActorCreate(CATS_SYS_PTR csp, CATS_RES_PTR crp, int waza_kind, 
	const TCATS_OBJECT_ADD_PARAM_S *obj_data)
{
	CATS_ACT_PTR cap;
	TCATS_OBJECT_ADD_PARAM_S obj_param;
	
	obj_param = *obj_data;
	obj_param.pal = WazaKindIcon_PlttOffsetGet(waza_kind);
	
	cap = CATS_ObjectAdd_S(csp, crp, &obj_param);
	return cap;
}

//--------------------------------------------------------------
/**
 * @brief   技分類アイコンアクターを削除
 * @param   cap		アクターポインタ
 */
//--------------------------------------------------------------
void WazaKindIcon_ActorDelete(CATS_ACT_PTR cap)
{
	CATS_ActorPointerDelete_S(cap);
}

