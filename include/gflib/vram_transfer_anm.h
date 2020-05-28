//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *	H16/11/08		Tomoya Takahashi
 *
 *	テクスチャパターンアニメーションをVram転送アニメーションで行う
 *																システム
 *
 *	利用するときの注意
 *	このシステムはVram転送マネージャーを使用しているので、
 *	このシステムを使用する前にVram転送マネージャーを初期化しておいてください。
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

#ifndef	__VRAM_TRANSFER_ANM_H__
#define	__VRAM_TRANSFER_ANM_H__

#include <nitro.h>
#include <nnsys.h>
#include "texanm_sys.h"


//-----------------------------------------------------------------------------
/**
 *					定数宣言
 */
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
/**
 *					構造体宣言
 */
//-----------------------------------------------------------------------------
//-------------------------------------
//	
//	Vramアニメオブジェデータ
//	
//=====================================
typedef struct _ITP_VRAM_ANM* ITP_VRAM_ANM_PTR;

//-------------------------------------
//	
//	Vramアニメーションシステム構造体
//	
//=====================================
typedef struct _ITP_VRAM_SYS* ITP_VRAM_SYS_PTR;

//----------------------------------------------------------------------------
/**
 *					プロトタイプ宣言
 */
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *
 *@brief	Vramアニメーションシステムオブジェクトの作成
 *
 *@param	WorkNum		作成ワーク数
 *@param	heap		使用するヒープ
 *
 *@return	ITP_VRAM_SYS_PTR		Vramアニメーションデータ
 */
//-----------------------------------------------------------------------------
extern ITP_VRAM_SYS_PTR initItpVramAnm(int WorkNum, int heap);

//----------------------------------------------------------------------------
/**
 *
 *@brief	Vramアニメーションシステムオブジェクトの破棄
 *
 *@param	pDat		Vramアニメーションデータ
 *
 *@return	none
 */
//-----------------------------------------------------------------------------
extern void destItpVramAnm(ITP_VRAM_SYS_PTR pDat);

//----------------------------------------------------------------------------
/**
 *
 *@brief	Vramアニメーションを追加
 *
 *@param	pDat		Vramアニメーションデータ
 *@param	cp_anmtbl	アニメーションテーブル
 *@param	cp_tex		転送テクスチャデータ
 *@param	texKey		テクスチャキー
 *@param	plttKey		パレットキー
 *@param	c_frame		現在フレーム値
 *
 *@return	ITP_VRAM_ANM_PTR	Vramアニメオブジェ
 */
//-----------------------------------------------------------------------------
extern ITP_VRAM_ANM_PTR addItpVramAnm( ITP_VRAM_SYS_PTR pDat, const TEXANM_DATATBL* cp_anmtbl, const NNSG3dResTex* cp_tex, NNSGfdTexKey texKey, NNSGfdPlttKey plttKey, const fx32 c_frame );

//----------------------------------------------------------------------------
/**
 *
 *@brief	Vramアニメーションを削除
 *
 *@param	pDat	Vramアニメーションデータ
 *@param	pAnmObj	削除するアニメーションのアニメーションオブジェ
 *	
 *@return	none	
 */
//-----------------------------------------------------------------------------
extern	void remItpVramAnm( ITP_VRAM_ANM_PTR pAnmObj );

//----------------------------------------------------------------------------
/**
 *
 *@brief	全Vramアニメーションを削除
 *
 *@param	pDat	Vramアニメーションデータ
 *	
 *@return	none
 *	
 */
//-----------------------------------------------------------------------------
extern	void remItpVramAnmAll( ITP_VRAM_SYS_PTR pDat );

//----------------------------------------------------------------------------
/**
 *
 *@brief	転送を実行する
 *
 *@param	obj		転送するデータ
 *@param	c_frame	現在フレーム数
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
extern void transItpVramAnm( ITP_VRAM_ANM_PTR obj, const fx32 c_frame );

//----------------------------------------------------------------------------
/**
 *
 *@brief	テクスチャリソースとテクスチャＩＤからテクセル開始アドレスを確定する
 *
 *@param	inResTex：テクスチャリソース
 *@param	inIndex ：テクスチャＩＤ
 *
 *@return	void*	: アドレス
 *
 */
//-----------------------------------------------------------------------------
extern void* GetTexStartAdr(NNSG3dResTex *inResTex, const u8 inIndex);
extern void* GetPlttStartAdr(NNSG3dResTex *inResTex, const u8 inIndex);

//----------------------------------------------------------------------------
/**
 *
 *@brief	テクスチャリソースとテクスチャＩＤからテクセル開始VRAMアドレスを確定する
 *
 *@param	inResTex：テクスチャリソース
 *@param	inIndex ：テクスチャＩＤ
 *
 *@return	void*	: アドレス
 *
 */
//-----------------------------------------------------------------------------
extern void* GetTexStartVRAMAdr(NNSG3dResTex *inResTex, const u8 inIndex);
extern void* GetTexStartVRAMAdrByName(NNSG3dResTex *inResTex, const char *name);

//----------------------------------------------------------------------------
/**
 *
 *@brief	テクスチャリソースとテクスチャＩＤからテクスチャサイズを確定する
 *
 *@param	inResTex：テクスチャリソース
 *@param	inIndex ：テクスチャＩＤ
 *
 *@return	int	: テクスチャサイズ
 *
 */
//-----------------------------------------------------------------------------
extern int GetTexByteSize(NNSG3dResTex *inResTex, const u8 inIndex);
extern int GetTexByteSizeByName(NNSG3dResTex *inResTex, const char *name);


#endif // __VRAM_TRANSFER_ANM_H__
