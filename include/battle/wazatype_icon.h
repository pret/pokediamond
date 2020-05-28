//==============================================================================
/**
 * @file	wazatype_icon.h
 * @brief	技タイプアイコンのヘッダ
 * @author	matsuda
 * @date	2005.10.26(水)
 */
//==============================================================================
#ifndef __WAZATYPE_ICON_H__
#define __WAZATYPE_ICON_H__

#include "system/clact_tool.h"


//==============================================================================
//	定数定義
//==============================================================================
///アイコンタイプ(技タイプ以外のタイプ)
enum{
	ICONTYPE_STYLE = 18,	///<格好よさ
	ICONTYPE_BEAUTIFUL,		///<美しさ
	ICONTYPE_CUTE,			///<可愛さ
	ICONTYPE_INTELLI,		///<賢さ
	ICONTYPE_STRONG,		///<逞しさ
};

///技タイプアイコンで使用するパレット本数
#define WTI_PLTT_NUM		(3)
///技分類アイコンで使用するパレット本数
#define WKI_PLTT_NUM		(3)

///技タイプアイコングラフィックの圧縮フラグ(キャラクタ)
#define WAZATYPEICON_COMP_CHAR		(1)
///技タイプアイコングラフィックの圧縮フラグ(パレット)
#define WAZATYPEICON_COMP_PLTT		(0)
///技タイプアイコングラフィックの圧縮フラグ(セル)
#define WAZATYPEICON_COMP_CELL		(1)
///技タイプアイコングラフィックの圧縮フラグ(セルアニメ)
#define WAZATYPEICON_COMP_CELLANM	(1)

///技分類アイコングラフィックの圧縮フラグ(キャラクタ)
#define WAZAKINDICON_COMP_CHAR		(1)
///技分類アイコングラフィックの圧縮フラグ(パレット)
#define WAZAKINDICON_COMP_PLTT		(0)
///技分類アイコングラフィックの圧縮フラグ(セル)
#define WAZAKINDICON_COMP_CELL		(1)
///技分類アイコングラフィックの圧縮フラグ(セルアニメ)
#define WAZAKINDICON_COMP_CELLANM	(1)

///技タイプアイコンのOAMタイプ定義
#define WAZATYPEICON_OAMTYPE		(OAMTYPE_32x16)


//==============================================================================
//	外部関数宣言
//==============================================================================
extern void WazaTypeIcon_CharResourceLoad(CATS_SYS_PTR csp, CATS_RES_PTR crp, 
	NNS_G2D_VRAM_TYPE vram_type, int waza_type, u32 char_id);
extern void WazaTypeIcon_PlttResourceLoad(CATS_SYS_PTR csp, CATS_RES_PTR crp, 
	NNS_G2D_VRAM_TYPE vram_type, u32 pltt_id);
extern void WazaTypeIcon_CellAnmResourceLoad(CATS_SYS_PTR csp, CATS_RES_PTR crp, 
	u32 cell_id, u32 anm_id);
extern void WazaTypeIcon_CharResourceFree(CATS_RES_PTR crp, u32 char_id);
extern void WazaTypeIcon_PlttResourceFree(CATS_RES_PTR crp, u32 pltt_id);
extern void WazaTypeIcon_CellAnmResourceFree(CATS_RES_PTR crp, u32 cell_id, u32 anm_id);
extern CATS_ACT_PTR WazaTypeIcon_ActorCreate(CATS_SYS_PTR csp, CATS_RES_PTR crp, 
	int waza_type, const TCATS_OBJECT_ADD_PARAM_S *obj_data);
extern void WazaTypeIcon_ActorDelete(CATS_ACT_PTR cap);
extern u32 WazaTypeIcon_CgrIDGet(int waza_type);
extern u32 WazaTypeIcon_PlttIDGet(void);
extern u32 WazaTypeIcon_CellIDGet(void);
extern u32 WazaTypeIcon_CellAnmIDGet(void);
extern u8 WazaTypeIcon_PlttOffsetGet(int waza_type);
extern u32 WazaTypeIcon_ArcIDGet(void);

extern u32 WazaKindIcon_CgrIDGet(int waza_kind);
extern u32 WazaKindIcon_PlttIDGet(void);
extern u32 WazaKindIcon_CellIDGet(void);
extern u32 WazaKindIcon_CellAnmIDGet(void);
extern u8 WazaKindIcon_PlttOffsetGet(int waza_kind);
extern u32 WazaKindIcon_ArcIDGet(void);
extern void WazaKindIcon_CharResourceLoad(CATS_SYS_PTR csp, CATS_RES_PTR crp, 
 	NNS_G2D_VRAM_TYPE vram_type, int waza_kind, u32 char_id);
extern void WazaKindIcon_PlttResourceLoad(CATS_SYS_PTR csp, CATS_RES_PTR crp, 
	NNS_G2D_VRAM_TYPE vram_type, u32 pltt_id);
extern void WazaKindIcon_CellAnmResourceLoad(CATS_SYS_PTR csp, CATS_RES_PTR crp, 
	u32 cell_id, u32 anm_id);
extern void WazaKindIcon_CharResourceFree(CATS_RES_PTR crp, u32 char_id);
extern void WazaKindIcon_PlttResourceFree(CATS_RES_PTR crp, u32 pltt_id);
extern void WazaKindIcon_CellAnmResourceFree(CATS_RES_PTR crp, u32 cell_id, u32 anm_id);
extern CATS_ACT_PTR WazaKindIcon_ActorCreate(CATS_SYS_PTR csp, CATS_RES_PTR crp, int waza_kind, 
	const TCATS_OBJECT_ADD_PARAM_S *obj_data);
extern void WazaKindIcon_ActorDelete(CATS_ACT_PTR cap);
extern void WazaKindIcon_PlttWorkResourceLoad(PALETTE_FADE_PTR pfd, FADEREQ req, CATS_SYS_PTR csp, 
	CATS_RES_PTR crp, NNS_G2D_VRAM_TYPE vram_type, u32 pltt_id);
extern void WazaTypeIcon_PlttWorkResourceLoad(PALETTE_FADE_PTR pfd, FADEREQ req, CATS_SYS_PTR csp, 
	CATS_RES_PTR crp, NNS_G2D_VRAM_TYPE vram_type, u32 pltt_id);


#endif	//__WAZATYPE_ICON_H__

