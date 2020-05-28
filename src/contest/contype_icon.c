//==============================================================================
/**
 * @file	contype_icon.c
 * @brief	コンテストタイプアイコン
 * @author	matsuda
 * @date	2005.12.02(金)
 */
//==============================================================================
#include "common.h"
#include "system/clact_tool.h"
#include "contype_icon.h"
#include "system/arc_tool.h"
#include "system/arc_util.h"

#include "contest/graphic/contest_obj_def.h"


//==============================================================================
//	定数定義
//==============================================================================
///コンテストタイプアイコンで使用するパレット本数
#define CTI_PLTT_NUM		(2)


//==============================================================================
//	データ
//==============================================================================
///コンテストタイプ毎のCGRID
ALIGN4 static const u32 ConTypeCgrNo[] = {
	CTYPE_STYLE_NCGR_BIN,			//CONTYPE_STYLE
	CTYPE_BEAUTIFUL_NCGR_BIN,		//CONTYPE_BEAUTIFUL
	CTYPE_CUTE_NCGR_BIN,			//CONTYPE_CUTE
	CTYPE_CLEVER_NCGR_BIN,			//CONTYPE_CLEVER
	CTYPE_STRONG_NCGR_BIN, 		//CONTYPE_STRONG
};

///コンテストタイプ毎のパレットオフセット番号
ALIGN4 static const u8 ConTypePlttOffset[] = {
	1,		//CONTYPE_STYLE
	1,		//CONTYPE_BEAUTIFUL
	1,		//CONTYPE_CUTE
	1,		//CONTYPE_CLEVER
	1,		//CONTYPE_STRONG
};



//==============================================================================
//
//	コンテストタイプアイコン
//
//==============================================================================
//--------------------------------------------------------------
/**
 * @brief   指定コンテストタイプのCGRIDを取得します
 * @param   con_type		コンテストタイプ(CONTYPE_???)
 * @retval  CGRID(ARCのデータINDEX)
 */
//--------------------------------------------------------------
u32 ConTypeIcon_CgrIDGet(int con_type)
{
	GF_ASSERT(con_type < NELEMS(ConTypeCgrNo));
	return ConTypeCgrNo[con_type];
}

//--------------------------------------------------------------
/**
 * @brief   コンテストタイプアイコンのパレットIDを取得します
 * @retval  パレットID(ARCのデータINDEX)
 */
//--------------------------------------------------------------
u32 ConTypeIcon_PlttIDGet(void)
{
	return CONTEST_SUB_OBJ_NCLR;
}

//--------------------------------------------------------------
/**
 * @brief   指定コンテストタイプのセルIDを取得します
 * @retval  セルID(ARCのデータINDEX)
 */
//--------------------------------------------------------------
u32 ConTypeIcon_CellIDGet(void)
{
	return CTYPE_STYLE_NCER_BIN;
}

//--------------------------------------------------------------
/**
 * @brief   指定コンテストタイプのセルアニメIDを取得します
 * @retval  セルアニメID(ARCのデータINDEX)
 */
//--------------------------------------------------------------
u32 ConTypeIcon_CellAnmIDGet(void)
{
	return CTYPE_STYLE_NANR_BIN;
}

//--------------------------------------------------------------
/**
 * @brief   指定コンテストタイプのパレット番号オフセットを取得します
 * @param   con_type		コンテストタイプ(CONTYPE_???)
 * @retval  パレット番号のオフセット
 */
//--------------------------------------------------------------
u8 ConTypeIcon_PlttOffsetGet(int con_type)
{
	GF_ASSERT(con_type < NELEMS(ConTypePlttOffset));
	return ConTypePlttOffset[con_type];
}

//--------------------------------------------------------------
/**
 * @brief   コンテストタイプアイコンのアーカイブINDEXを取得します
 * @retval  アーカイブINDEX
 */
//--------------------------------------------------------------
u32 ConTypeIcon_ArcIDGet(void)
{
	return ARC_CONTEST_OBJ;
}




//--------------------------------------------------------------
/**
 * @brief   指定コンテストタイプのキャラリソースをロードします
 *
 * @param   csp				cspへのポインタ
 * @param   crp				crpへのポインタ
 * @param   vram_type		NNS_G2D_VRAM_TYPE_2DMAIN等
 * @param   con_type		コンテストタイプ(CONTYPE_???)
 * @param   char_id			登録するキャラID
 */
//--------------------------------------------------------------
void ConTypeIcon_CharResourceLoad(CATS_SYS_PTR csp, CATS_RES_PTR crp, 
	NNS_G2D_VRAM_TYPE vram_type, int con_type, u32 char_id)
{
	CATS_LoadResourceCharArc(csp, crp, ConTypeIcon_ArcIDGet(), 
		ConTypeIcon_CgrIDGet(con_type), 1, vram_type, char_id);
}

//--------------------------------------------------------------
/**
 * @brief   コンテストタイプアイコンのパレットをロードします
 *
 * @param   csp			cspへのポインタ
 * @param   crp			crpへのポインタ
 * @param   vram_type	NNS_G2D_VRAM_TYPE_2DMAIN等
 * @param   pltt_id		登録するパレットID
 *
 * コンテストタイプアイコンで使用するパレット全てをセットします。
 */
//--------------------------------------------------------------
void ConTypeIcon_PlttResourceLoad(CATS_SYS_PTR csp, CATS_RES_PTR crp, 
	NNS_G2D_VRAM_TYPE vram_type, u32 pltt_id)
{
	CATS_LoadResourcePlttArc(csp, crp, ConTypeIcon_ArcIDGet(), ConTypeIcon_PlttIDGet(), 1, 
		CTI_PLTT_NUM, vram_type, pltt_id);
}

//--------------------------------------------------------------
/**
 * @brief   コンテストタイプアイコンのパレットをパレットワークへロードします
 *
 * @param   PALETTE_FADE_PTR		パレットフェードシステムへのポインタ
 * @param   req						リクエストデータ番号(FADE_MAIN_BG等)
 * @param   csp			cspへのポインタ
 * @param   crp			crpへのポインタ
 * @param   vram_type	NNS_G2D_VRAM_TYPE_2DMAIN等
 * @param   pltt_id		登録するパレットID
 *
 * コンテストタイプアイコンで使用するパレット全てをセットします。
 */
//--------------------------------------------------------------
void ConTypeIcon_PlttWorkResourceLoad(PALETTE_FADE_PTR pfd, FADEREQ req, CATS_SYS_PTR csp, 
	CATS_RES_PTR crp, NNS_G2D_VRAM_TYPE vram_type, u32 pltt_id)
{
	CATS_LoadResourcePlttWorkArc(pfd, req, csp, crp, 
		ConTypeIcon_ArcIDGet(), ConTypeIcon_PlttIDGet(), 0, 
		CTI_PLTT_NUM, vram_type, pltt_id);
}

//--------------------------------------------------------------
/**
 * @brief   コンテストタイプアイコンのセルとアニメをロードします
 *
 * @param   csp			cspへのポインタ
 * @param   crp			crpへのポインタ
 * @param   cell_id		登録するセルID
 * @param   anm_id		登録するアニメID
 *
 * コンテストタイプアイコン共通のセルとアニメをロードします。
 * コンテストタイプアイコンは全てセルとアニメが共通なので、1つだけ登録しておけばOKです。
 * (複数のアイコンを生成する時でも、全てここで登録したセル、アニメIDを指定するようにします)
 */
//--------------------------------------------------------------
void ConTypeIcon_CellAnmResourceLoad(CATS_SYS_PTR csp, CATS_RES_PTR crp, u32 cell_id, u32 anm_id)
{
	CATS_LoadResourceCellArc(csp, crp, ConTypeIcon_ArcIDGet(), ConTypeIcon_CellIDGet(), 
		1, cell_id);
	CATS_LoadResourceCellAnmArc(csp, crp, ConTypeIcon_ArcIDGet(), ConTypeIcon_CellAnmIDGet(), 
		1, anm_id);
}

//--------------------------------------------------------------
/**
 * @brief   コンテストタイプアイコンのキャラリソースを解放します
 * @param   crp			crpへのポインタ
 * @param   char_id		解放するキャラID
 */
//--------------------------------------------------------------
void ConTypeIcon_CharResourceFree(CATS_RES_PTR crp, u32 char_id)
{
	CATS_FreeResourceChar(crp, char_id);
}

//--------------------------------------------------------------
/**
 * @brief   コンテストタイプアイコンのパレットリソースを解放します
 * @param   crp			crpへのポインタ
 * @param   pltt_id		解放するパレットID
 */
//--------------------------------------------------------------
void ConTypeIcon_PlttResourceFree(CATS_RES_PTR crp, u32 pltt_id)
{
	CATS_FreeResourcePltt(crp, pltt_id);
}

//--------------------------------------------------------------
/**
 * @brief   コンテストタイプアイコンのセル、アニメリソースを解放します
 * @param   crp			crpへのポインタ
 * @param   char_id		解放するセルID
 * @param   char_id		解放するアニメID
 */
//--------------------------------------------------------------
void ConTypeIcon_CellAnmResourceFree(CATS_RES_PTR crp, u32 cell_id, u32 anm_id)
{
	CATS_FreeResourceCell(crp, cell_id);
	CATS_FreeResourceCellAnm(crp, anm_id);
}


//--------------------------------------------------------------
/**
 * @brief   コンテストタイプアイコンアクターを生成する
 *
 * @param   csp				cspへのポインタ
 * @param   crp				crpへのポインタ
 * @param   con_type		コンテストタイプ(CONTYPE_???)
 * @param   obj_data		アクターヘッダへのポインタ
 *
 * @retval  生成したアクターのポインタ
 */
//--------------------------------------------------------------
CATS_ACT_PTR ConTypeIcon_ActorCreate(CATS_SYS_PTR csp, CATS_RES_PTR crp, int con_type, 
	const TCATS_OBJECT_ADD_PARAM_S *obj_data)
{
	CATS_ACT_PTR cap;
	TCATS_OBJECT_ADD_PARAM_S obj_param;
	
	obj_param = *obj_data;
	obj_param.pal = ConTypeIcon_PlttOffsetGet(con_type);
	
	cap = CATS_ObjectAdd_S(csp, crp, &obj_param);
	return cap;
}

//--------------------------------------------------------------
/**
 * @brief   コンテストタイプアイコンアクターを削除
 * @param   cap		アクターポインタ
 */
//--------------------------------------------------------------
void ConTypeIcon_ActorDelete(CATS_ACT_PTR cap)
{
	CATS_ActorPointerDelete_S(cap);
}


