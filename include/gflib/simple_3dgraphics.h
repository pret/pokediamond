//=============================================================================================
/**
 * @file	simple_3dgraphic.h
 * @brief	基本３Ｄグラフィックシステム
 */
//=============================================================================================
#ifndef __SIMPLE_3DGRAPHIC_H__
#define __SIMPLE_3DGRAPHIC_H__

#include "system.h"


#undef GLOBAL
#ifdef __SIMPLE_3DGRAPHICS_H_GLOBAL__
#define GLOBAL /*	*/
#else
#define GLOBAL extern
#endif

#define LINK_VRAM_MANAGER	//リンクドVRAMマネージャーを使用

#include "tcb.h"

typedef void (*pCallBackFunc)(void *);	// 関数ポインタ型
typedef void (*pSetTexAnmCallBackFunc)(NNSG3dRenderObj* ,
		NNSG3dAnmObj* ,
		NNSG3dResMdl* ,
		NNSG3dResTex* );	// 関数ポインタ型

typedef struct VRAM_MANAGER_MEM_tag * VRAM_MANAGER_MEM_PTR;

typedef struct G3D_CLEAR_COLOR_tag
{
	GXRgb RGB;		//クリアカラーのRGB成分
	int Alpha;		//0 <= alpha <= 31
	int Depth;		//クリアデプス値
	int PolygonID;	//アトリビュートバッファのポリゴンID初期値
	BOOL Fog;		//アトリビュートバッファのフォグを有効にするかどうかの選択
}G3D_CLEAR_COLOR;

typedef enum{
	GF_SHADING_TOON = GX_SHADING_TOON,
	GF__SHADING_HIGHLIGHT = GX_SHADING_HIGHLIGHT,
}GF_SHADE_MODE;

typedef struct G3D_SETUP_PARAM_tag
{
	GF_SHADE_MODE ShadeMode;		//シェーディングモード
	int Priority;		//3D面プライオリティ(0～3)
	int Ref;			//αテストを行う場合の比較値
	BOOL AntiAlias;		//アンチエイリアス有無
	BOOL EdgeMarking;	//エッジマーキング有無
	BOOL AlphaTest;		//αテスト有無
	BOOL AlphaBlend;	//αブレンド有無
	//クリアカラー情報
	G3D_CLEAR_COLOR ClearColor;
}G3D_SETUP_PARAM;

typedef enum{
	LINKED_VRAM_MANAGER,
	FRM_VRAM_MANAGER,
}VRAM_MANAGER_TYPE;

typedef struct VRAM_MAN_PARAM_tag
{
	VRAM_MANAGER_TYPE Type;
	union {
		struct{
			u32 TexSzByte;
			u32	TexSzByteFor4x4;
		};
		struct{
			u16 TexSlot;
			u16 dummy[3];
		};
	};
	u32 PalSzByte;
}VRAM_MAN_PARAM;

/*---------------------------------------------------------------------------*
	グローバル関数
 *---------------------------------------------------------------------------*/
GLOBAL BOOL TexKeyLive( NNSG3dResTex* pTex );	// テクスチャキーが割り振られているかチェック

GLOBAL void simple_3DModelSetResFileAlready
	(NNSG3dRenderObj* object_p,
	 NNSG3dResMdl** model, NNSG3dResFileHeader** resFile);

GLOBAL void simple_3DBGInit(const u8 inMode);
GLOBAL void simple_3DBGExit(void);

GLOBAL void simple_LoadG3DModel
	(const u8 mode,
	 const char* path,
	 NNSG3dResMdl** model,
	 NNSG3dResFileHeader** resFile);

GLOBAL void simple_3DModelDraw
		(NNSG3dRenderObj* object_p,VecFx32* trans_p,MtxFx33* rot_p,VecFx32* scale_p);
GLOBAL void simple_3DModelDraw_1mat1shape
        (NNSG3dRenderObj* object_p,VecFx32* trans_p,MtxFx33* rot_p,VecFx32* scale_p);

GLOBAL void simple_3DModelSet
	(const u8 mode,
	 const char* path,NNSG3dRenderObj* object_p,
	 NNSG3dResMdl** model,NNSG3dResFileHeader** resFile);

GLOBAL BOOL LoadVRAMTexture(NNSG3dResTex* tex);
GLOBAL BOOL BindTexture(void* pResData, NNSG3dResTex* pTex);

#undef GLOBAL



#endif
