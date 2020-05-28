//=============================================================================================
/**
 * @file	debug_3d_draw_count.c
 * @brief	デバッグ用描画関連カウント（ポリゴン数とか）
 */
//=============================================================================================
#ifdef PM_DEBUG

#include <nitro.h>
#include <nnsys.h>
#include "debug_3d_draw_count.h"

//----- ポリゴン描画の回数を調べるためのDEBUG処理
typedef struct{
	int NNS_AddVertexNum;
	int NNS_AddPolygonNum;
	int NNS_AddDrawNum;
	int VertexNum;
	int PolygonNum;
	int DrawNum;

	int TexBlock;
	int PlttBlock;

	NNSiGfdLnkVramBlock *texture_p;
	NNSiGfdLnkVramBlock *pal_p;
}DEBUG_DRAW_COUNT;

static DEBUG_DRAW_COUNT DebugDrawCount;

//------------------------------------------------------------------
/**
 * 3D描画のために調べた数値を退避
 *
*/
//------------------------------------------------------------------
void D_3D_DC_DrawPolygonCountUp(void)
{
	DebugDrawCount.NNS_AddVertexNum  = DebugDrawCount.VertexNum;
	DebugDrawCount.NNS_AddPolygonNum = DebugDrawCount.PolygonNum;
	DebugDrawCount.NNS_AddDrawNum       = DebugDrawCount.DrawNum;

	DebugDrawCount.VertexNum  = 0;
	DebugDrawCount.PolygonNum = 0;
	DebugDrawCount.DrawNum    = 0;
}

//------------------------------------------------------------------
/**
 * NITROSYSTEMに渡したポリゴンの数を返す
 *
 * @param	int ポリゴン数
*/
//------------------------------------------------------------------
int D_3D_DC_DrawPolygonGet(void)
{
	return DebugDrawCount.NNS_AddPolygonNum;
}

//------------------------------------------------------------------
/**
 * NITROSYSTEMに渡した頂点の数を返す
 *
 * @param	int	頂点数
*/
//------------------------------------------------------------------
int D_3D_DC_DrawVertexGet(void)
{
	return DebugDrawCount.NNS_AddVertexNum;
} 

//------------------------------------------------------------------
/**
 * NITROSYSTEMからポリゴン描画した回数を返す
 *
 * @return	int	描画数
*/
//------------------------------------------------------------------
int D_3D_DC_DrawNumGet(void)
{
	return DebugDrawCount.NNS_AddDrawNum;
}

//==============================================================================
/**
 * リンクドＶＲＡＭマネージャーとパレットマネージャーのポインタを保存
 *
 * @param   texp		テクスチャマネージャー
 * @param   palp		パレットマネージャー
 * @param	inTexBlock	テクスチャブロックサイズ
 * @param	inPlttBlockSize	パレットブロックサイズ
 *
 * @retval  none		
 */
//==============================================================================
void D_3D_DC_VramManPSet(NNSiGfdLnkVramBlock *texp, NNSiGfdLnkVramBlock *palp,
						const int inTexBlock, const int inPlttBlock)
{
	DebugDrawCount.texture_p = texp;
	DebugDrawCount.pal_p     = palp;
	DebugDrawCount.TexBlock  = inTexBlock;
	DebugDrawCount.PlttBlock  = inPlttBlock;
}

//==============================================================================
/**
 * VRAMへのテクスチゃ転送状態を取得する
 *
 *
 * @retval  int		使用しているＶＲＡＭ容量
 */
//==============================================================================
int  D_3D_DC_VramTexSizeGet(void)
{
	int size = 0;
	int i;
	
	NNSiGfdLnkVramBlock *tex = DebugDrawCount.texture_p;
	
	
	for(i=0;i<DebugDrawCount.TexBlock;i++){
		//リンクドVRAMマネージャーの先頭を探す
		if((tex->pBlkPrev==0 && tex->pBlkNext!=0) || (tex->pBlkPrev==0 && tex->pBlkNext==0)){		
			break;
		}
		tex++;
	}

	while(tex->pBlkNext!=0){	// リンクが続く限り足して次へ渡っていく
		size += tex->szByte;
		tex = (NNSiGfdLnkVramBlock *)tex->pBlkNext;
	}
	size += tex->szByte;		//最後のリンク先のVRAM転送数も足す

	// VRAMマネージャーが保存しているのは「使用していない量」なので総量から引いて返す
	return (DebugDrawCount.TexBlock*1024)-size;	
}


//==============================================================================
/**
 * リンクドPALマネージャーの転送状態を取得する
 *
 *
 * @retval  int		リンクドPALマネージャーの転送バイト数
 */
//==============================================================================
int  D_3D_DC_VramPalSizeGet(void)
{
	int size = 0;
	int i;
	
	NNSiGfdLnkVramBlock *tex = DebugDrawCount.pal_p;
	
	
	for(i=0;i<DebugDrawCount.PlttBlock;i++){
		//リンクドPALLマネージャーの先頭を探す
		if((tex->pBlkPrev==0 && tex->pBlkNext!=0) || (tex->pBlkPrev==0 && tex->pBlkNext==0)){		
			break;
		}
		tex++;
	}

	while(tex->pBlkNext!=0){	// リンクが続く限り足して次へ渡っていく
		size += tex->szByte;
		tex = (NNSiGfdLnkVramBlock *)tex->pBlkNext;
	}
	size += tex->szByte;		//最後のリンク先のVRAM転送数も足す

	// PALマネージャーが保存しているのは「使用していない量」なので総量から引いて返す
	return (DebugDrawCount.PlttBlock*1024)-size;	
}

//==============================================================================
/**
 * カウントアップ
 *
 * @param   object_p		レンダーＯＢＪ		
 *
 * @retval  none
 */
//==============================================================================
void D_3D_DC_CountNum(NNSG3dRenderObj* object_p)
{
	//モデリングデータリソースから頂点数を取得して足す
	DebugDrawCount.VertexNum  += object_p->resMdl->info.numVertex;
	//モデリングデータリソースからポリゴン数を取得して足す
	DebugDrawCount.PolygonNum += object_p->resMdl->info.numPolygon;		
	DebugDrawCount.DrawNum++;
}

#endif	//PM_DEBUG

