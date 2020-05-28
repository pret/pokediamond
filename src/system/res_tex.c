#include <string.h>
#include "res_tex.h"
#include "system.h"
#include "str_tool.h"
#include "vram_transfer_manager.h"

//==============================================================================
/**
 * パレットリソース名比較
 *
 * @param   const NNSG3dResName* inName
 * @oaram	const char * inTargetName
 *
 * @retval  BOOL		TRUE:一致　FALSE:不一致
 */
//==============================================================================
BOOL CmpPaletteName(const NNSG3dResName* inName,const char * inTargetName)
{
	NNSG3dResName	target_name;

	SetResName(&target_name,inTargetName);
	if (inName->val[0] == target_name.val[0] &&
		inName->val[1] == target_name.val[1] &&
		inName->val[2] == target_name.val[2] &&
		inName->val[3] == target_name.val[3]){
		return TRUE;
	}
	
	return FALSE;
}

//==============================================================================
/**
 * 指定テクスチャパレットサイズの取得
 *
 * @param   const NNSG3dResTex* inResTex
 * @oaram	const NNSG3dResName *inResName
 *
 * @retval  u32		
 */
//==============================================================================
u32 GetTexPaletteSize(const NNSG3dResTex* inResTex, const NNSG3dResName *inResName)
{
	u8 idx;
	u32 size;
	NNSG3dResDict* dict;
	const NNSG3dResDictPlttData* plttData = NNS_G3dGetPlttDataByName(inResTex, inResName);
	
	size = 0;
	
	if (plttData){
		//テクスチャリソース内のパレットエントリ数を取得
		dict = (NNSG3dResDict*)((u8*)inResTex + inResTex->plttInfo.ofsDict);

		//パレット名からパレットインデックスを取得
		idx = NNS_G3dGetPlttIdxByName(inResTex, inResName);
		
		//転送サイズを計算(if分岐でのsizeは、実際のサイズを3ビット右シフトした値)
		//4colorsなら転送サイズは4色分（8バイト）でいい
		if (plttData->flag & 1){
			size = 1;
		}
		//現在エントリが最後の場合はテクスチャリソース情報が持つ
		//総パレットサイズと現在の開始アドレスとの差分で算出
		else if (idx == dict->numEntry-1){
			size = inResTex->plttInfo.sizePltt - plttData->offset;
		}
		else{
			//次のパレットエントリの開始アドレスを取得
			const NNSG3dResDictPlttData* next_plttData = NNS_G3dGetPlttDataByIdx(inResTex, idx+1);
			// テクスチャブロックからパレット名に対応するデータフィールドを得る
			//差分からサイズを計算
			size = next_plttData->offset - plttData->offset;
		}
		//3ビット左シフトした値が実際のサイズになる
		size = (size<<3);
	}
	return size;
}

//==============================================================================
/**
 * 指定テクスチャパレットの変更
 *
 * @param	const NNSG3dResTex* inResTex
 * @param   const char * inStr
 *
 * @retval  none		
 */
//==============================================================================
void ChangeTexPalette(const NNSG3dResTex* inResTex, const char * inStr, u16* inPalette)
{
	NNSG3dResName res_name;
	NNSG3dResDict* dict;
	u32 adr;
	u32 size;
    u32 i;
    BOOL result = TRUE;
	
	//名前セット
	SetResName(&res_name,inStr);
    
	//テクスチャリソース内のパレットエントリ数を取得
    dict = (NNSG3dResDict*)((u8*)inResTex + inResTex->plttInfo.ofsDict);
	
    for (i = 0; i < dict->numEntry; ++i)
    {
	    // テクスチャブロックからパレット名に対応するデータフィールドを得る
	    const NNSG3dResDictPlttData* plttData = NNS_G3dGetPlttDataByName(inResTex, &res_name);
		if (plttData){
			//パレット名が存在
			if (inResTex->plttInfo.flag & NNS_G3D_RESPLTT_LOADED){//VRAMにロードされていたら転送を実行
	        
				u16 plttBase = plttData->offset;
				u16 vramOffset = (u16)(inResTex->plttInfo.vramKey & 0xffff);
			
				adr = (u16)(plttBase + vramOffset);
			
				//転送サイズを計算
				size = GetTexPaletteSize(inResTex, &res_name);
			
				//VRAM転送リクエスト
				AddVramTransferManager(
						NNS_GFD_DST_3D_TEX_PLTT,									// パレットを転送
						NNS_GfdGetPlttKeyAddr( adr ),	// 転送先
						(void*)inPalette,														// 転送データ
						size	// 転送サイズ
						);
				return;
			}
		}//endif (plttData)
	}//end for
    return;
}

//==============================================================================
/**
 * 指定テクスチャパレットの取得　内部でメモリ確保している
 *
 * @param   const NNSG3dResTex* inResTex
 *
 * @param   const char *inName
 *
 * @retval  u16*		
 */
//==============================================================================
u16* GetTexPalette(const NNSG3dResTex* inResTex, const char *inName, const int inHeapID)
{
	u8 idx;
	u8 entry;
	void *data;
	u16 *palette;
	u32 size;
	const NNSG3dResDictPlttData* plttData;
	NNSG3dResName res_name;
	NNSG3dResDict* dict;
    NNS_G3D_NULL_ASSERT(inResTex);

	//名前セット
	SetResName(&res_name,inName);
	//テクスチャリソース内のパレットエントリ数を取得
    dict = (NNSG3dResDict*)((u8*)inResTex + inResTex->plttInfo.ofsDict);
	entry = dict->numEntry;

	// テクスチャブロックからパレット名に対応するデータフィールドを得る
	plttData = NNS_G3dGetPlttDataByName(inResTex, &res_name);
	if (plttData){
		//パレット名からインデックスを取得
		idx = NNS_G3dGetPlttIdxByName(inResTex,&res_name);
		if (idx < entry){
			//サイズ取得
			size = GetTexPaletteSize(inResTex,&res_name);
			//size分メモリ確保
			palette = sys_AllocMemory( inHeapID, size );
			//テクスチャパレットデータ
			data = (u8*)inResTex + inResTex->plttInfo.ofsPlttData;
			//データをコピー
			MI_CpuCopy16(data,palette,size);
			return palette;
		}
	}//end if (plttData)
	return NULL;
}

//==============================================================================
/**
 * 指定テクスチャパレットのVRAMアドレスとサイズを取得
 *
 * @param   const NNSG3dResTex* inResTex
 *
 * @param   const char *inName
 *
 * @param	void *outAdr				取得したＶＲＡＭアドレス
 *
 * @retval  u32							パレットサイズ
 */
//==============================================================================
u32 GetTexPaletteAdr(const NNSG3dResTex* inResTex, const char *inName, void *outAdr)
{
	NNSG3dResName res_name;
	NNSG3dResDict* dict;
	u32 adr;
	u32 size;
    u32 i;
    BOOL result = TRUE;
	
	size = 0;
	//名前セット
	SetResName(&res_name,inName);
    
	//テクスチャリソース内のパレットエントリ数を取得
    dict = (NNSG3dResDict*)((u8*)inResTex + inResTex->plttInfo.ofsDict);
	
    for (i = 0; i < dict->numEntry; ++i)
    {
	    // テクスチャブロックからパレット名に対応するデータフィールドを得る
	    const NNSG3dResDictPlttData* plttData = NNS_G3dGetPlttDataByName(inResTex, &res_name);
		if (plttData){
			//パレット名が存在
			if (inResTex->plttInfo.flag & NNS_G3D_RESPLTT_LOADED){//VRAMにロードされていたら取得
	        
				u16 plttBase = plttData->offset;
				u16 vramOffset = (u16)(inResTex->plttInfo.vramKey & 0xffff);
			
				adr = (u16)(plttBase + vramOffset);
			
				//サイズを計算
				size = GetTexPaletteSize(inResTex, &res_name);
			
				outAdr = (void*)adr;
				return size;
			}
		}//endif (plttData)
	}//end for
	outAdr = NULL;
    return size;
}

//==============================================================================
/**
 * 指定テクスチャサイズの取得
 *
 * @param   const NNSG3dResTex* inResTex
 * @oaram	const NNSG3dResName *inResName
 *
 * @retval  u32		
 */
//==============================================================================
u32 GetTexSize(const NNSG3dResTex* inResTex, const NNSG3dResName *inResName)
{
	u8 idx;
	u32 size;
	NNSG3dResDict* dict;
	const NNSG3dResDictTexData* texData = NNS_G3dGetTexDataByName(inResTex, inResName);
	
	size = 0;
	
	if (texData){
		//テクスチャリソース内のテクスチャエントリ数を取得
		dict = (NNSG3dResDict*)((u8*)inResTex + inResTex->texInfo.ofsDict);

		//パレット名からパレットインデックスを取得
		idx = NNS_G3dGetTexIdxByName(inResTex, inResName);
		
		//転送サイズを計算(if分岐でのsizeは、実際のサイズを3ビット右シフトした値)
		//現在エントリが最後の場合はテクスチャリソース情報が持つ
		//総パレットサイズと現在の開始アドレスとの差分で算出
		if (idx == dict->numEntry-1){
			size = inResTex->texInfo.sizeTex - (texData->texImageParam & NNS_G3D_TEXIMAGE_PARAM_TEX_ADDR_MASK);
		}
		else{
			//次のパレットエントリの開始アドレスを取得
			const NNSG3dResDictTexData* next_texData = NNS_G3dGetTexDataByIdx(inResTex, idx+1);
			// テクスチャブロックからパレット名に対応するデータフィールドを得る
			//差分からサイズを計算
			size = (next_texData->texImageParam&NNS_G3D_TEXIMAGE_PARAM_TEX_ADDR_MASK) - (texData->texImageParam&NNS_G3D_TEXIMAGE_PARAM_TEX_ADDR_MASK);
		}
		//3ビット左シフトした値が実際のサイズになる
		size = (size<<3);
	}
	return size;
}


//テクスチャリソースから指定テクスチャ名のテクスチャのＶＲＡＭアドレスとサイズを取得
u32 GetResTexAdr(const NNSG3dResTex* inResTex, const char *inName, void *outAdr)
{
	NNSG3dResName res_name;
	NNSG3dResDict* dict;
	u32 adr;
	u32 size;
    u32 i;
    BOOL result = TRUE;
	
	size = 0;
	//名前セット
	SetResName(&res_name,inName);
    
	//テクスチャリソース内のパレットエントリ数を取得
    dict = (NNSG3dResDict*)((u8*)inResTex + inResTex->texInfo.ofsDict);
	
    for (i = 0; i < dict->numEntry; ++i)
    {
	    // テクスチャブロックからパレット名に対応するデータフィールドを得る
	    const NNSG3dResDictTexData* texData = NNS_G3dGetTexDataByName(inResTex, &res_name);
		if (texData){
			//テクスチャ名が存在
			if (inResTex->texInfo.flag & NNS_G3D_RESTEX_LOADED){//VRAMにロードされていたら取得
	        
				u16 texBase = (texData->texImageParam & NNS_G3D_TEXIMAGE_PARAM_TEX_ADDR_MASK);
				u16 vramOffset = (u16)(inResTex->texInfo.vramKey & 0xffff);
			
				adr = (u16)(texBase + vramOffset);
			
				//サイズを計算
				size = GetTexSize(inResTex, &res_name);
			
				outAdr = (void*)adr;
				return size;
			}
		}//endif (plttData)
	}//end for
	outAdr = NULL;
    return size;
}
