//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *@file		vram_transfer_anm.c
 *@brief	テクスチャパターンアニメーションをVram転送アニメーションで行う
 *																システム
 *@author	tomoya takahashi
 *@data		2004.11.08
 *
 *	
 *
 *	利用するときの注意
 *	このシステムはVram転送マネージャーを使用しているので、
 *	このシステムを使用する前にVram転送マネージャーを初期化しておいてください。
 *
 *	
 *	リストにセットするデータについて
 *		NNSG3dAnmObj：アニメーションデータとこのアニメーション使うテクスチャリソースをセットした状態
 *					　でセットします。（テクスチャをVramに転送しないように）
 *					　TexKeyには0x00をセットしておきます。
 *
 *		NNSG3dResTex：デフォルトのビルボードにセットされている１枚の絵のリソースです。
 *					　Vramに絵のデータを転送させてしっかりTexKeyを格納しておいてください。
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
#include "vram_transfer_anm.h"
#include "vram_transfer_manager.h"
#include "system.h"
#include "str_tool.h"
#include "gflib_os_print.h"



//-------------------------------------
//
///　Vramアニメーションリスト構造体
//
//-------------------------------------
typedef struct _ITP_VRAM_ANM
{
	const TEXANM_DATATBL* cp_anmtbl;// アニメーションデータテーブル
	const NNSG3dResTex*	cp_tex;		// 転送テクスチャデータ
	NNSGfdTexKey  texKey;			// テクスチャVramKey
	NNSGfdPlttKey plttKey;			// パレットVramKey
	
	u8			  oldTexNum;		// １つ前に転送したテクスチャナンバー
	u8			  oldPlttNum;		// １つ前に転送したパレットナンバー
	
} ITP_VRAM_ANM;


//-------------------------------------
//
//	Vramアニメーションシステム構造体
//
//=====================================
typedef struct _ITP_VRAM_SYS{
	ITP_VRAM_ANM*	pWork;		// Vramアニメーションリスト
	int				WorkNum;	// リスト数
} ITP_VRAM_SYS;

//----------------------------------------------------------------------------
/**
 *					プロトタイプ宣言
 */
//-----------------------------------------------------------------------------
// メインで呼ばれる各リストのデータから実際に絵を転送する関数
static void ItpVramAnmMainApp( ITP_VRAM_ANM* pItpData, const u16 c_frame );
// 転送する絵のデータを取得
static void* getGraphicData( ITP_VRAM_ANM* pItpData, const TEXANM_DATA* cp_texdata );
// 転送するパレットのデータを取得
static void* getPalletData( ITP_VRAM_ANM* pItpData, const TEXANM_DATA* cp_texdata );
// アニメーションデータを取得
// ワークの初期化
static void cleanItpWork(ITP_VRAM_ANM* work);
// テクスチャデータ転送
static void trans_tex(ITP_VRAM_ANM* pItpData, const TEXANM_DATA* cp_texdata);
// パレットデータ転送
static void trans_pltt(ITP_VRAM_ANM* pItpData, const TEXANM_DATA* cp_texdata);

//----------------------------------------------------------------------------
/**
 *					グローバル変数宣言
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
ITP_VRAM_SYS_PTR initItpVramAnm(int WorkNum, int heap)
{
	ITP_VRAM_SYS_PTR vl_sys;
	int i;

	// Vramアニメーションシステムデータ作成
	vl_sys = sys_AllocMemory(heap, sizeof(ITP_VRAM_SYS));

	// ワーク作成
	vl_sys->pWork = sys_AllocMemory(heap, sizeof(ITP_VRAM_ANM)*WorkNum);
	vl_sys->WorkNum = WorkNum;
	for(i=0;i<vl_sys->WorkNum;i++){
		cleanItpWork(&vl_sys->pWork[i]);
	}

	return vl_sys;
}

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
void destItpVramAnm(ITP_VRAM_SYS_PTR pDat)
{
	// 全破棄
	remItpVramAnmAll(pDat);

	sys_FreeMemoryEz(pDat->pWork);
	sys_FreeMemoryEz(pDat);
}

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
ITP_VRAM_ANM_PTR addItpVramAnm( ITP_VRAM_SYS_PTR pDat, const TEXANM_DATATBL* cp_anmtbl, const NNSG3dResTex* cp_tex, NNSGfdTexKey texKey, NNSGfdPlttKey plttKey, const fx32 c_frame )
{
	ITP_VRAM_ANM_PTR	p_itp_anm;			// アニメーションデータ
	u32					pltt_size;			// パレット転送を行うかのチェック
	int					i;					// ループ用
	p_itp_anm = NULL;
	//
	// データ書き込み領域探索
	//
	for(i=0;i<pDat->WorkNum;i++){
		if(pDat->pWork[i].cp_anmtbl == NULL){
			p_itp_anm = &pDat->pWork[i];
			break;
		}
	}

	if(p_itp_anm == NULL){
		return NULL;
	}
	
	// 各データをセット
	p_itp_anm->cp_anmtbl= cp_anmtbl;		// アニメーションデータ
	p_itp_anm->cp_tex	= cp_tex;			// 転送テクスチャデータ
	p_itp_anm->texKey	= texKey;			// Vram転送で中身を書き換えるテクスチャキー
	p_itp_anm->plttKey	= plttKey;			// Vram転送で中身を書き換えるパレットキー
	p_itp_anm->oldTexNum  = -1;				// １つ前に転送したテクスチャナンバー
	p_itp_anm->oldPlttNum = -1;				// １つ前に転送したパレットナンバー
	// １回転送
	// (ここでは、パレットとテクスチャ両方転送)
	ItpVramAnmMainApp(p_itp_anm, c_frame >> FX32_SHIFT );

	return p_itp_anm;
}

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
void remItpVramAnm( ITP_VRAM_ANM_PTR pAnmObj )
{
	// 領域を削除
	cleanItpWork(pAnmObj);
}

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
void remItpVramAnmAll( ITP_VRAM_SYS_PTR pDat )
{
	int i;	

	// 全Vramアニメーションを破棄
	for(i=0;i<pDat->WorkNum;i++){
		cleanItpWork( (pDat->pWork + i) );
	}
}
	
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
void transItpVramAnm( ITP_VRAM_ANM_PTR obj, const fx32 c_frame )
{
	u16	frame_16;		// u16型にしたときのフレーム数

	// 小数点以下を切り捨てた
	// u16型のフレーム値を取得
	frame_16 = c_frame >> FX32_SHIFT;	
		
	// 転送処理
	ItpVramAnmMainApp( obj, frame_16 );
}

/*-----------------------------------------------------------------------------
 *			プライベート関数の実態部
 ----------------------------------------------------------------------------*/
// ワークの初期化
static void cleanItpWork(ITP_VRAM_ANM* work)
{
	work->cp_anmtbl		= NULL;
	work->cp_tex		= NULL;
	work->texKey		= 0;
	work->plttKey		= 0;
	work->oldTexNum		= 0;
	work->oldPlttNum	= 0;
}


//----------------------------------------------------------------------------
/**
 *
 *@brief		実際に転送処理を行う
 *			VramKeyの位置に今の絵のデータを転送する
 *		　	AnmObjから今の絵のナンバーを取得
 *		　	Vram転送タスクを登録する
 *
 *@param	pItpData：Vram転送アニメーションを行うアニメデータ
 *@param	c_frame	現在フレーム
 *
 *@return	none
 *
 */
//-----------------------------------------------------------------------------
static void ItpVramAnmMainApp( ITP_VRAM_ANM* pItpData, const u16 c_frame )
{	
	TEXANM_DATA	texdata;	// 今のフレームのテクスチャIDとパレットID


	// 今のアニメーションデータを取得
	texdata = TEXANM_GetFrameData( pItpData->cp_anmtbl, c_frame );
	
	// ひとつ前に転送したテクスチャナンバーと違うかチェック
	if( pItpData->oldTexNum != texdata.tex_idx )
	{
		trans_tex(pItpData, &texdata);
	}

	// １つ前に転送したパレットナンバーと違うかチェック
	if( pItpData->oldPlttNum != texdata.pltt_idx )
	{
		trans_pltt(pItpData, &texdata);
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	テクスチャデータ転送
 *
 *@param	pItpData	転送データ
 *@param	cp_texdata	今のテクスチャno
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void trans_tex(ITP_VRAM_ANM* pItpData, const TEXANM_DATA* cp_texdata)
{
	void*		p_buff;				// 絵のデータのバッファ
	//
	// 今の絵のナンバー、絵のサイズを取得
	//
	p_buff = getGraphicData( pItpData, cp_texdata );


	//
	// 転送タスクをセット
	//
	AddVramTransferManager(
			NNS_GFD_DST_3D_TEX_VRAM,					// テクスチャを転送
			NNS_GfdGetTexKeyAddr( pItpData->texKey ),	// 転送先
			p_buff,										// 転送データ
			NNS_GfdGetTexKeySize( pItpData->texKey )	// 転送サイズ
			);

	// 転送したテクスチャナンバー保存
	pItpData->oldTexNum = cp_texdata->tex_idx;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	パレットデータ転送
 *
 *@param	pItpData	転送データ
 *@param	cp_texdata	今のパレットno
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void trans_pltt(ITP_VRAM_ANM* pItpData, const TEXANM_DATA* cp_texdata)
{
	void*		p_buff;				// 絵のデータのバッファ
	
	// 今のパレットデータを取得
	p_buff = getPalletData( pItpData, cp_texdata );

	// 転送タスクをセット
	AddVramTransferManager(
			NNS_GFD_DST_3D_TEX_PLTT,					// パレットを転送
			NNS_GfdGetPlttKeyAddr( pItpData->plttKey ),	// 転送先
			p_buff,										// 転送データ
			NNS_GfdGetPlttKeySize( pItpData->plttKey )	// 転送サイズ
			);

	// 転送したパレットナンバー保存
	pItpData->oldPlttNum = cp_texdata->pltt_idx;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	今のフレームの絵のデータを取得
 *
 *@param	pItpData：アニメーションデータ
 *@param	cp_texdata	今のフレームのテクスチャIDとパレットID
 *
 *@return	転送するデータのバッファ
 *
 */
//-----------------------------------------------------------------------------
static void* getGraphicData( ITP_VRAM_ANM* pItpData, const TEXANM_DATA* cp_texdata )
{
	/*
	//
	// 今のフレームの絵が何番目かを取得し、絵の大きさから
	// 絵のデータの先頭からのオフセットを計算しバッファに
	// そのポインタをセットする
	//
	
	//
	// 今のフレームの絵のナンバーと絵のサイズを取得する
	//
	// このテクスチャIDの絵のデータを取得
	const NNSG3dResDictTexData* pData = NNS_G3dGetTexDataByIdx( pItpData->cp_tex, cp_texdata->tex_idx );

	// オフセット値
	u32 offset = (pData->texImageParam & NNS_G3D_TEXIMAGE_PARAM_TEX_ADDR_MASK);
//	u32 offset = (pData->texImageParam & NNS_G3D_TEXIMAGE_PARAM_TEX_ADDR_MASK) + pItpData->pAnmObj->resTex->texInfo.vramKey;
		
	
	// 書き込むデータのポインタをかえす
	return (void*)((u8*)pItpData->cp_tex + pItpData->cp_tex->texInfo.ofsTex + (offset << 3) );//*/

	// コンストがたのリソースですが、メモリ有効利用のためこの関数をしよう
	return GetTexStartAdr( (NNSG3dResTex*)pItpData->cp_tex, cp_texdata->tex_idx );
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	今のフレームのパレットデータを取得
 *
 *@param	pItpData：アニメーションデータ
 *@param	cp_texdata	今のフレームのテクスチャIDとパレットID
 *
 *@return	書き込むデータのポインタ
 *
 */
//-----------------------------------------------------------------------------
static void* getPalletData( ITP_VRAM_ANM* pItpData, const TEXANM_DATA* cp_texdata )
{
/*
	//
	// 今のフレームのパレットが何番目かを取得し、パレットの大きさから
	// パレットのデータの先頭からのオフセットを計算しバッファに
	// そのポインタをセットする
	//
	
	//
	// 今のフレームのパレットのナンバーを取得する
	//
	const NNSG3dResDictPlttData* pPlttData = NNS_G3dGetPlttDataByIdx( pItpData->cp_tex, cp_texdata->pltt_idx );
	
	
	//
	// オフセット値の位置からのデータを転送
	//
	return (void*)((u8*)pItpData->cp_tex + pItpData->cp_tex->plttInfo.ofsPlttData + (pPlttData->offset << 3));
//*/
	// コンストがたのリソースですが、メモリ有効利用のためこの関数をしよう
	return GetPlttStartAdr( (NNSG3dResTex*)pItpData->cp_tex, cp_texdata->pltt_idx );
}

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
void* GetTexStartAdr(NNSG3dResTex *inResTex, const u8 inIndex)
{
	u32 offset;
	const NNSG3dResDictTexData* pData = NNS_G3dGetTexDataByIdx( inResTex, inIndex );
	
	if (pData == NULL){
		return NULL;
	}

	// オフセット値
	offset = (pData->texImageParam & NNS_G3D_TEXIMAGE_PARAM_TEX_ADDR_MASK) + inResTex->texInfo.vramKey;

	return (void*)((u8*)inResTex + inResTex->texInfo.ofsTex + (offset << 3) );
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	テクスチャリソースとパレットＩＤからパレット開始アドレスを確定する
 *
 *@param	inResTex：テクスチャリソース
 *@param	inIndex ：パレットＩＤ
 *
 *@return	void*	: アドレス
 *
 */
//-----------------------------------------------------------------------------
void* GetPlttStartAdr(NNSG3dResTex *inResTex, const u8 inIndex)
{
	const NNSG3dResDictPlttData* pPlttData = NNS_G3dGetPlttDataByIdx( inResTex, inIndex );
	
	if (pPlttData == NULL){
		return NULL;
	}
	
	// オフセット値の位置からのデータを転送
	return (void*)((u8*)inResTex + inResTex->plttInfo.ofsPlttData + (pPlttData->offset << 3));
}


//------------------------------------------------------------------
/**
 * テクセル開始VRAMアドレスを確定するための算出関数
 *
 * @param   pData		テクスチャアドレス解決のための情報
 *
 * @retval  void*		テクスチャアドレス
 */
//------------------------------------------------------------------
static void* GetTexStartVRAMAdrSub(NNSG3dResTex *inResTex,const NNSG3dResDictTexData* pData)
{
	// オフセット値
	u32 offset = (pData->texImageParam & NNS_G3D_TEXIMAGE_PARAM_TEX_ADDR_MASK)<<3;
	offset += NNS_GfdGetTexKeyAddr( inResTex->texInfo.vramKey );
	return (void*)(offset);

}
//----------------------------------------------------------------------------
/**
 *
 *@brief	テクスチャリソースとテクスチャ名からテクセル開始VRAMアドレスを確定する
 *
 *@param	inResTex：テクスチャリソース
 *@param	name    ：テクスチャ名
 *
 *@return	void*	: アドレス
 *
 */
//-----------------------------------------------------------------------------
void* GetTexStartVRAMAdrByName(NNSG3dResTex *inResTex, const char *name)
{
	NNSG3dResName tmpResName;
	const NNSG3dResDictTexData* pData;

	//テクスチャの実体をサーチ
	SetResName(&tmpResName,name);	//文字列をNNSG3dResNameに変換
	pData = NNS_G3dGetTexDataByName( inResTex, &tmpResName );

	if (pData == NULL){
		return NULL;
	}

	//アドレスを算出
	return GetTexStartVRAMAdrSub(inResTex, pData);
}


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
void* GetTexStartVRAMAdr(NNSG3dResTex *inResTex, const u8 inIndex)
{
	//テクスチャの実体をサーチ
	const NNSG3dResDictTexData* pData = NNS_G3dGetTexDataByIdx( inResTex, inIndex );
	if (pData == NULL){
		return NULL;
	}
	//アドレスを算出
	return GetTexStartVRAMAdrSub(inResTex, pData);
}



//----------------------------------------------------------------------------
/**
 *
 *@brief	テクスチャサイズを確定する算出関数
 *
 *@param	inResTex：テクスチャリソース
 *@param	inIndex ：GetTexByteSize & GetTexByteSizeByNameから渡されるポインタ
 *
 *@return	int	: テクスチャサイズ
 *
 */
//-----------------------------------------------------------------------------
static int GetTexByteSizeSub(NNSG3dResTex *inResTex, const NNSG3dResDictTexData* pData)
{
	u32 byte_size;
	u32 format;
	u32 t_size,s_size;
	u32 texel_size;
	
	//フォーマットを調べる
	format = (pData->texImageParam & NNS_G3D_TEXIMAGE_PARAM_TEXFMT_MASK)>>NNS_G3D_TEXIMAGE_PARAM_TEXFMT_SHIFT;
#ifdef VRAM_TRANSFER_ANM_OS_PRINT_ON
	OS_Printf("TEX_FORMAT_IS:%d\n",format);	
#endif
	
	//フォーマットに従い、1テクセル分のデータ量を決定
	switch(format){
	case GX_TEXFMT_PLTT4:
		//4テクセル1バイト
		texel_size = 4;
		break;
	case GX_TEXFMT_PLTT16:
		//2テクセル1バイト
		texel_size = 2;
		break;
	case GX_TEXFMT_PLTT256:
		//1テクセル1バイト
		texel_size = 1;
		break;
	case GX_TEXFMT_A3I5:
		//1テクセル1バイト
		texel_size = 1;
		break;
	default:
#ifdef VRAM_TRANSFER_ANM_OS_PRINT_ON
		OS_Printf("ERROR:NO_SUPPORT_TEX_FORMAT\n");
#endif
		return 0;
	}
	
	//テクスチャの横サイズを取得
	s_size = (pData->texImageParam & NNS_G3D_TEXIMAGE_PARAM_S_SIZE_MASK)>>NNS_G3D_TEXIMAGE_PARAM_S_SIZE_SHIFT;
	s_size <<= 4;
#ifdef VRAM_TRANSFER_ANM_OS_PRINT_ON
	OS_Printf("TEX_S_SIZE_IS:%d\n",s_size);
#endif
	//テクスチャの縦サイズを取得
	t_size = (pData->texImageParam & NNS_G3D_TEXIMAGE_PARAM_T_SIZE_MASK)>>NNS_G3D_TEXIMAGE_PARAM_T_SIZE_SHIFT;
	t_size <<= 4;
#ifdef VRAM_TRANSFER_ANM_OS_PRINT_ON
	OS_Printf("TEX_T_SIZE_IS:%d\n",t_size);
#endif
	//バイトサイズを計算
	byte_size = (s_size*t_size)/texel_size;
#ifdef VRAM_TRANSFER_ANM_OS_PRINT_ON
	OS_Printf("TEX_BYTE_SIZE_IS:%d\n",byte_size);
#endif
	
	return byte_size;
}




//==============================================================================
/**
 * テクスチャリソースとテクスチャＩＤから確定する
 *
 * @param   inResTex	テクスチャリソース
 * @param   inIndex		テクスチャＩＤ
 *
 * @retval  int			テクスチャサイズ
 */
//==============================================================================
int GetTexByteSize(NNSG3dResTex *inResTex, const u8 inIndex)
{
	
	//テクスチャの実体をサーチ
	const NNSG3dResDictTexData* pData = NNS_G3dGetTexDataByIdx( inResTex, inIndex );

	//サイズを算出
	return GetTexByteSizeSub(inResTex, pData);

}

//==============================================================================
/**
 * テクスチャリソースとテクスチャ名から確定する
 *
 * @param   inResTex	テクスチャリソース	
 * @param   name		テクスチャ名
 *
 * @retval  int			テクスチャサイズ
 */
//==============================================================================
int GetTexByteSizeByName(NNSG3dResTex *inResTex, const char *name)
{
	const NNSG3dResDictTexData* pData;
	NNSG3dResName tmpResName;		
	
	SetResName(&tmpResName,name);		//文字列をNNSG3dResNameに変換

	//テクスチャの実体をサーチ
	pData = NNS_G3dGetTexDataByName( inResTex, &tmpResName );

	//サイズを算出
	return GetTexByteSizeSub(inResTex, pData);

}
