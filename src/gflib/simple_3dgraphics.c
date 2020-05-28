/*---------------------------------------------------------------------------*
  Project:  PokemonDS
  File:     simple_3dgraphics.c

  基本３Ｄグラフィックシステム

 *---------------------------------------------------------------------------*/
#include <nitro.h>
#include <nnsys.h>
#include <nnsys/g3d/binres/res_print.h>

#include "system.h"
#include "display.h"
#include "bg_system.h"
#include "g3d_system.h"

#define	__SIMPLE_3DGRAPHICS_H_GLOBAL
#include "simple_3dgraphics.h"

#include "tcb.h"

#include "gflib_os_print.h"
#include "gflib/assert.h"
#include "assert.h"

#ifdef	PM_DEBUG
#include "debug_3d_draw_count.h"
#endif	//PM_DEBUG

typedef struct VRAM_MANAGER_MEM_tag
{
	void *PalMem;
	void *TexMem;
}VRAM_MANAGER_MEM;

static VRAM_MANAGER_MEM_PTR AllocVramManegerMem(const int inPalSize,
												const int inTexSize,
												const int inHeapID);
static void FreeVramManegerMem(VRAM_MANAGER_MEM_PTR *ptr);

void simple_LoadG3DModelAlrady(NNSG3dResMdl** model, NNSG3dResFileHeader** resFile);
void simple_Setup3DParams(const G3D_SETUP_PARAM *inParam);
void simple_FreeVRAMManager(VRAM_MANAGER_MEM_PTR *ptr);
//------------------------------------------------------------------
//                      モデル読み込み関数
//------------------------------------------------------------------

void simple_LoadG3DModel(const u8 mode, const char* path, NNSG3dResMdl** model, NNSG3dResFileHeader** resFile)
{
    NNSG3dResTex*        texture = NULL;
    BOOL status;

    *resFile = sys_LoadFile(mode,path);
    NNS_G3D_NULL_ASSERT(*resFile);

	// テクスチャがVramに展開されていないかチェック
	texture = NNS_G3dGetTex(*resFile);	// テクスチャリソース取得
	if(texture != NULL){
		if(TexKeyLive(texture) == FALSE){	// テクスチャがVramに展開されていないかチェック
			///OS_Printf("テクスチャがVRAMに展開されていないので、ここで展開\n");
			//内部でDMA転送するのでフラッシュする
			DC_FlushRange(*resFile,(*resFile)->fileSize);
			// デフォルトの初期化関数をコールしてセットアップする
			status = NNS_G3dResDefaultSetup(*resFile);
			NNS_G3D_ASSERTMSG(status, "NNS_G3dResDefaultSetup failed");
		}
	}
    
    // G3D: モデルの取得
    // nsbmdはモデルを複数含むことができるので、インデックス(モデルが１つの場合は0)
    // を指定して１つのモデルへのポインタを取得する。
    // --------------------------------------------------------------------
    *model = NNS_G3dGetMdlByIdx(NNS_G3dGetMdlSet(*resFile), 0);
}

//リソース確保済み用
void simple_LoadG3DModelAlrady(NNSG3dResMdl** model, NNSG3dResFileHeader** resFile)
{
    NNSG3dResTex*        texture = NULL;
    BOOL status;

	// テクスチャがVramに展開されていないかチェック
	texture = NNS_G3dGetTex(*resFile);	// テクスチャリソース取得
	if(texture != NULL){
		if(TexKeyLive(texture) == FALSE){	// テクスチャがVramに展開されていないかチェック
			OS_Printf("事前にテクスチャが展開されていので、テクスチャをＶＲＡＭに展開します\n");
			//内部でDMA転送するのでフラッシュする
			DC_FlushRange(*resFile,(*resFile)->fileSize);
			// デフォルトの初期化関数をコールしてセットアップする
			status = NNS_G3dResDefaultSetup(*resFile);
			NNS_G3D_ASSERTMSG(status, "NNS_G3dResDefaultSetup failed");
		}
	}
    
    // G3D: モデルの取得
    // nsbmdはモデルを複数含むことができるので、インデックス(モデルが１つの場合は0)
    // を指定して１つのモデルへのポインタを取得する。
    // --------------------------------------------------------------------
    *model = NNS_G3dGetMdlByIdx(NNS_G3dGetMdlSet(*resFile), 0);
}

//------------------------------------------------------------------
//                      ３Ｄオブジェクトセット関数
//------------------------------------------------------------------

void simple_3DModelSet
	(const u8 mode,
	 const char* path,NNSG3dRenderObj* object_p,
	 NNSG3dResMdl** model, NNSG3dResFileHeader** resFile) 
{
	simple_LoadG3DModel(mode,path,model,resFile);
	SDK_ASSERTMSG(model, "load failed");
	NNS_G3dRenderObjInit(object_p, *model);
}


void simple_3DModelSetResFileAlready
	(NNSG3dRenderObj* object_p,
	 NNSG3dResMdl** model, NNSG3dResFileHeader** resFile) 
{
	simple_LoadG3DModelAlrady(model,resFile);
	GF_ASSERT(model&&"load failed");
	SDK_ASSERTMSG(model, "load failed");
	NNS_G3dRenderObjInit(object_p, *model);
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	テクスチャキーが割り振られているかチェック
 *
 *@param	pTex		テクスチャリソースポインタ
 *	
 *@return	bool		true	割り振られてる
 *						false	割り振られていない
 *
 */
//-----------------------------------------------------------------------------
BOOL TexKeyLive( NNSG3dResTex* pTex )
{
	// 普通のテクスチャか4*4テクセル圧縮テクスチャ
	// でVramに展開されているかをチェック
	if((pTex->texInfo.flag & NNS_G3D_RESTEX_LOADED) ||
	   (pTex->tex4x4Info.flag & NNS_G3D_RESTEX4x4_LOADED)){
		return TRUE;
	}
	
	return FALSE;
}

//------------------------------------------------------------------
//                      ３ＤＢＧ描画関数
//------------------------------------------------------------------
void simple_3DModelDraw
(NNSG3dRenderObj* object_p,VecFx32* trans_p,MtxFx33* rot_p,VecFx32* scale_p)
{
#ifdef	PM_DEBUG
	D_3D_DC_CountNum(object_p);	//デバッグカウント
#endif
	// 位置設定
	NNS_G3dGlbSetBaseTrans(trans_p);
	// 角度設定
	NNS_G3dGlbSetBaseRot(rot_p);
	// スケール設定
	NNS_G3dGlbSetBaseScale(scale_p);

	NNS_G3dGlbFlush();
	
	NNS_G3dDraw(object_p);
//  NNS_G3dGeFlushBuffer();
}

//------------------------------------------------------------------
//                      高速３ＤＢＧ描画関数
//------------------------------------------------------------------
void simple_3DModelDraw_1mat1shape
(NNSG3dRenderObj* object_p,VecFx32* trans_p,MtxFx33* rot_p,VecFx32* scale_p)
{
#ifdef	PM_DEBUG
	D_3D_DC_CountNum(object_p);	//デバッグカウント
#endif
	// 位置設定
	NNS_G3dGlbSetBaseTrans(trans_p);
	// 角度設定
	NNS_G3dGlbSetBaseRot(rot_p);
	// スケール設定
	NNS_G3dGlbSetBaseScale(scale_p);

	NNS_G3dGlbFlush();
    
    NNS_G3dDraw1Mat1Shp(object_p->resMdl,0,0,TRUE);
    
    NNS_G3dGeFlushBuffer();
}

//------------------------------------------------------------------
//                      ３ＤＢＧ初期化関数
//------------------------------------------------------------------
static GF_G3DMAN* g3Dman = NULL;
static void simpleSetUp(void);

void simple_3DBGInit(const u8 inMode)
{
	g3Dman = GF_G3DMAN_Init
		(inMode, GF_G3DMAN_LNK, GF_G3DTEX_256K, GF_G3DMAN_LNK, GF_G3DPLT_64K, simpleSetUp );
#ifdef	PM_DEBUG
#ifdef DEBUG_3DDRAW_COUNT
	D_3D_DC_VramManPSet(g3Dman->tex_memory, g3Dman->plt_memory, 256, 64);
#endif	
#endif	
}

static void simpleSetUp(void)
{
	// ３Ｄ使用面の設定(表示＆プライオリティー)
	GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG0, VISIBLE_ON );
    G2_SetBG0Priority(1);

	// 各種描画モードの設定(シェード＆アンチエイリアス＆半透明)
    G3X_SetShading( GX_SHADING_TOON );
    G3X_AntiAlias( TRUE );
	G3X_AlphaTest( FALSE, 0 );	// アルファテスト　　オフ
	G3X_AlphaBlend( TRUE );		// アルファブレンド　オン
	G3X_EdgeMarking( FALSE );
	G3X_SetFog( FALSE, GX_FOGBLEND_COLOR_ALPHA, GX_FOGSLOPE_0x8000, 0 );

	// クリアカラーの設定
    G3X_SetClearColor(GX_RGB(0,0,0),0,0x7fff,63,FALSE);	//color,alpha,depth,polygonID,fog

	// ビューポートの設定
    G3_ViewPort(0, 0, 255, 191);
}

//------------------------------------------------------------------
void simple_3DBGExit(void)
{
	GF_G3D_Exit( g3Dman );
}

//------------------------------------------------------------------
BOOL BindTexture(void* pResData, NNSG3dResTex* pTex)
{
	//バインドする
	NNSG3dResMdlSet* mdlSet = NNS_G3dGetMdlSet((NNSG3dResFileHeader*) pResData);
	NNS_G3D_NULL_ASSERT(mdlSet);
	if (pTex){
		BOOL rc;
		// モデルセットのバインド
		rc = NNS_G3dBindMdlSet(mdlSet, pTex);
#ifdef PN_DEBUG		
		if (!rc){
			OS_Printf("テクスチャバインドに失敗\n");
		}
#endif	
#ifdef TEXTURE_BIND_PRINT_ON		
		OS_Printf("TextureBind!!\n");
#endif		
		return TRUE;
	}
	return FALSE;
}

//テクスチャのVRAMへのロード
BOOL LoadVRAMTexture(NNSG3dResTex* tex)
{
	if(tex == NULL){
		return FALSE;
	}
	
	tex->texInfo.vramKey = 0;
	{
        u32 szTex, szTex4x4, szPltt;
        BOOL sucTex    = TRUE;
        BOOL sucTex4x4 = TRUE;
        BOOL sucPltt   = TRUE;
        NNSG3dTexKey keyTex;
        NNSG3dTexKey keyTex4x4;
        NNSG3dPlttKey keyPltt;

		if (tex){
			// 必要なサイズを取得
            szTex    = NNS_G3dTexGetRequiredSize(tex);
            szTex4x4 = NNS_G3dTex4x4GetRequiredSize(tex);
            szPltt   = NNS_G3dPlttGetRequiredSize(tex);

            if (szTex > 0){
				// 存在すればテクスチャイメージスロットに確保
                keyTex = NNS_GfdAllocTexVram(szTex, FALSE, 0);
                if (keyTex == NNS_GFD_ALLOC_ERROR_TEXKEY){
                    sucTex = FALSE;
                }
            }
            else{
				keyTex = 0;
            }

			if (szTex4x4 > 0){
				// 存在すればテクスチャイメージスロットに確保
                keyTex4x4 = NNS_GfdAllocTexVram(szTex4x4, TRUE, 0);
                if (keyTex4x4 == NNS_GFD_ALLOC_ERROR_TEXKEY){
					sucTex4x4 = FALSE;
                }
            }
            else{
				keyTex4x4 = 0;
            }

            if (szPltt > 0){
                // 存在すればテクスチャパレットスロットに確保
                keyPltt = 
                    NNS_GfdAllocPlttVram(szPltt,
                                        tex->tex4x4Info.flag & NNS_G3D_RESPLTT_USEPLTT4,
                                        0);
                if (keyPltt == NNS_GFD_ALLOC_ERROR_PLTTKEY){
                    sucPltt = FALSE;
                }
            }
            else{
			     keyPltt = 0;
            }

            if (!sucTex){
                // 失敗時のロールバック処理
                int status;
#ifdef PM_DEBUG
				OS_Printf("テクスチャ取得不可%d/%d\n",szTex,D_3D_DC_VramTexSizeGet());
#endif
				status = NNS_GfdFreeTexVram(keyTex);
                NNS_G3D_ASSERTMSG(!status, "NNS_GfdFreeTexVram failed");
				GF_ASSERT(!status&&"NNS_GfdFreeTexVram failed");
				
                return FALSE;
            }
			if (!sucTex4x4){
                // 失敗時のロールバック処理
                int status;

                status = NNS_GfdFreeTexVram(keyTex4x4);
                NNS_G3D_ASSERTMSG(!status, "NNS_GfdFreeTexVram failed");
				GF_ASSERT(!status&&"NNS_GfdFree4x4TexVram failed");
				
                return FALSE;
            }
			if (!sucPltt){
                // 失敗時のロールバック処理
                int status;

                status = NNS_GfdFreePlttVram(keyPltt);
                NNS_G3D_ASSERTMSG(!status, "NNS_GfdFreePlttVram failed");
				GF_ASSERT(!status&&"NNS_GfdFreePlttVram failed");

                return FALSE;
            }

            // キーのアサイン
            NNS_G3dTexSetTexKey(tex, keyTex, keyTex4x4);
            NNS_G3dPlttSetPlttKey(tex, keyPltt);

			//DMA転送するのでフラッシュする
			DC_FlushRange( tex, tex->header.size );
            // VRAMへのロード
            NNS_G3dTexLoad(tex, TRUE);
            NNS_G3dPlttLoad(tex, TRUE);
        }
		
    }
    return TRUE;
}

//==============================================================================
/**
 * 3D関連パラメータの設定
 *
 * @param   inParam		セットアップパラメータ		
 *
 * @retval  none		
 */
//==============================================================================
void simple_Setup3DParams(const G3D_SETUP_PARAM *inParam)
{
	// NitroSystem:３Ｄエンジンの初期化
	NNS_G3dInit();
	// マトリクススタックの初期化
    G3X_InitMtxStack();

	// ３Ｄ使用面の設定(表示＆プライオリティー)
	GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG0, VISIBLE_ON );
	GF_ASSERT(inParam->Priority<=3&&"値が不正");
    G2_SetBG0Priority(inParam->Priority);

	// 各種描画モードの設定(シェード＆アンチエイリアス＆半透明)
    G3X_SetShading(inParam->ShadeMode);					//シェーディング
    G3X_AntiAlias(inParam->AntiAlias);					//アンチエイリアス
    //G2_BlendNone(); 
	G3X_AlphaTest(inParam->AlphaTest, inParam->Ref);	// アルファテスト
	G3X_AlphaBlend(inParam->AlphaBlend);				// アルファブレンド

	{
		const G3D_CLEAR_COLOR *col;
		col = &(inParam->ClearColor);
		// クリアカラーの設定
		G3X_SetClearColor(col->RGB,	// clear color
			              col->Alpha,				// clear alpha
				          col->Depth,			// clear depth
					      col->PolygonID,				// clear polygon ID
						  col->Fog				// fog
						 );
	}

	// ジオメトリエンジン起動後必ず呼ばれなければならない
    G3_SwapBuffers(GX_SORTMODE_AUTO, GX_BUFFERMODE_W);

	// ビューポートの設定
    G3_ViewPort(0, 0, 255, 191);
}

//==============================================================================
/**
 * VRAMマネージャーメモリの解放
 *
 * @param   inParam		セットアップパラメータ		
 *
 * @retval  none		
 */
//==============================================================================
void simple_FreeVRAMManager(VRAM_MANAGER_MEM_PTR *ptr)
{
	if ((*ptr) != NULL){
		FreeVramManegerMem(ptr);
	}
}

//==============================================================================
/**
 * VRAMマネージャーの設定
 *
 * @param   inPalSize		パレットサイズ
 * @param   inTexSize		テクスチャサイズ
 * @param   inHeapID		ヒープID
 *
 * @retval  VRAM_MANAGER_MEM_PTR	確保したメモリポインタ
 */
//==============================================================================
static VRAM_MANAGER_MEM_PTR AllocVramManegerMem(const int inPalSize,
												const int inTexSize,
												const int inHeapID)
{
	VRAM_MANAGER_MEM_PTR ptr;

	ptr = sys_AllocMemory( inHeapID, sizeof(VRAM_MANAGER_MEM) );
	ptr->PalMem = sys_AllocMemory( inHeapID, inPalSize );
	ptr->TexMem = sys_AllocMemory( inHeapID, inTexSize );

	return ptr;
}

//==============================================================================
/**
 * VRAMマネージャーの設定
 *
 * @param   inPalSize		パレットサイズ
 * @param   inTexSize		テクスチャサイズ
 * @param   inHeapID		ヒープID
 *
 * @retval  VRAM_MANAGER_MEM_PTR	確保したメモリポインタ
 */
//==============================================================================
static void FreeVramManegerMem(VRAM_MANAGER_MEM_PTR *ptr)
{
	sys_FreeMemoryEz((*ptr)->PalMem);
	sys_FreeMemoryEz((*ptr)->TexMem);
	sys_FreeMemoryEz(*ptr);
	*ptr = NULL;
}
