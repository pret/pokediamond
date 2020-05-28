//============================================================================================
/**
 * @file	arc_util.h
 * @bfief	アーカイブデータを便利に使うためのユーティリティ関数群
 * @author	taya
 * @date	05.08.30
 */
//============================================================================================
#ifndef __ARC_UTIL_H__
#define __ARC_UTIL_H__

#include "gflib\bg_system.h"
#include "system\arc_tool.h"


//------------------------------------------------------------------
/**
 *  キャラデータマッピングタイプ
 */
//------------------------------------------------------------------
typedef enum {
	ALLOC_TOP = 0,			///< ヒープの先頭から
	ALLOC_BOTTOM = 1,		///< ヒープの終端から
}ALLOC_TYPE;

//------------------------------------------------------------------
/**
 *  パレット転送先タイプ指定
 */
//------------------------------------------------------------------
typedef enum {
	PALTYPE_MAIN_BG,			// メインBG
	PALTYPE_MAIN_OBJ,			// メインOBJ
	PALTYPE_MAIN_BG_EX,			// メイン拡張BG
	PALTYPE_MAIN_OBJ_EX,		// メイン拡張OBJ
	PALTYPE_SUB_BG,				// サブBG
	PALTYPE_SUB_OBJ,			// サブOBJ
	PALTYPE_SUB_BG_EX,			// サブ拡張BG
	PALTYPE_SUB_OBJ_EX,			// サブ拡張OBJ
}PALTYPE;

//------------------------------------------------------------------
/**
 *  OBJキャラデータ転送先タイプ指定
 */
//------------------------------------------------------------------
typedef enum {
	OBJTYPE_MAIN,
	OBJTYPE_SUB,
}OBJTYPE;

//------------------------------------------------------------------
/**
 *  キャラデータマッピングタイプ
 */
//------------------------------------------------------------------
typedef enum {
	CHAR_MAP_1D,		// 1D 
	CHAR_MAP_2D,		// 2D
}CHAR_MAPPING_TYPE;


//------------------------------------------------------------------
/**
 * BGｷｬﾗﾃﾞｰﾀの VRAM 転送
 *
 * @param   arcFile			アーカイブファイルインデックス
 * @param   arcIndex		アーカイブデータインデックス
 * @param   bgl				BGLﾃﾞｰﾀ
 * @param   frm				転送先ﾌﾚｰﾑﾅﾝﾊﾞ
 * @param   offs			転送ｵﾌｾｯﾄ（ｷｬﾗ単位）
 * @param	transSize		転送するｻｲｽﾞ（ﾊﾞｲﾄ単位 ==0で全転送）
 * @param   compressedFlag	圧縮されているﾃﾞｰﾀか？
 * @param   heapID			ﾃﾞｰﾀ読み込み・解凍ﾃﾝﾎﾟﾗﾘとして使うﾋｰﾌﾟID
 *
 * @return  転送したデータサイズ（バイト）
 */
//------------------------------------------------------------------
extern u32 ArcUtil_BgCharSet(u32 arcFile, u32 dataIdx, GF_BGL_INI* bgl, u32 frm, u32 offs, u32 transSize, BOOL compressedFlag, u32 heapID);


//------------------------------------------------------------------
/**
 * OBJ ｷｬﾗﾃﾞｰﾀ の VRAM 転送
 *
 * @param   fileIdx				アーカイブファイルインデックス
 * @param   dataIdx				アーカイブデータインデックス
 * @param   objType				OBJﾀｲﾌﾟ
 * @param   offs				ｵﾌｾｯﾄ（ﾊﾞｲﾄ単位）
 * @param   transSize			転送ｻｲｽﾞ（ﾊﾞｲﾄ単位 : 0 で全転送）
 * @param   compressedFlag		圧縮されたﾃﾞｰﾀか？
 * @param   heapID				読み込み・解凍ﾃﾝﾎﾟﾗﾘとして使うﾋｰﾌﾟID
 *
 * @return  転送したデータサイズ（バイト）
 */
//------------------------------------------------------------------
extern u32 ArcUtil_ObjCharSet( u32 fileIdx, u32 dataIdx, OBJTYPE objType, u32 offs, u32 transSize, BOOL compressedFlag, u32 heapID );


//--------------------------------------------------------------------------------------------
/**
 * ｽｸﾘｰﾝﾃﾞｰﾀの VRAM 転送
 * ※ BGL側に ｽｸﾘｰﾝﾊﾞｯﾌｧ が用意されていれば、ｽｸﾘｰﾝﾊﾞｯﾌｧ への転送も行う
 *
 * @param   arcFile			アーカイブファイルインデックス
 * @param   arcIndex		アーカイブデータインデックス
 * @param   bgl				BGLﾃﾞｰﾀ
 * @param   frm				転送先ﾌﾚｰﾑﾅﾝﾊﾞ
 * @param   offs			転送ｵﾌｾｯﾄ（ｷｬﾗ単位）
 * @param	transSize		転送するｻｲｽﾞ（ﾊﾞｲﾄ単位 ==0で全転送）
 * @param   compressedFlag	圧縮されているﾃﾞｰﾀか？
 * @param   heapID			ﾃﾞｰﾀ読み込み・解凍ﾃﾝﾎﾟﾗﾘとして使うﾋｰﾌﾟID
 *
 */
//--------------------------------------------------------------------------------------------
extern void ArcUtil_ScrnSet(u32 arcFile, u32 dataIdx, GF_BGL_INI* bgl, u32 frm, u32 offs, u32 transSize, BOOL compressedFlag, u32 heapID);


//------------------------------------------------------------------
/**
 * ﾊﾟﾚｯﾄﾃﾞｰﾀ の VRAM 転送
 *
 * @param   arcFile		アーカイブファイルインデックス
 * @param   dataIdx		アーカイブデータインデックス
 * @param   palType		ﾊﾟﾚｯﾄ転送先ﾀｲﾌﾟ
 * @param   offs		ﾊﾟﾚｯﾄ転送先ｵﾌｾｯﾄ
 * @param   transSize	ﾊﾟﾚｯﾄ転送ｻｲｽﾞ（0 で全転送）
 * @param   heapID		ﾃﾞｰﾀ読み込みﾃﾝﾎﾟﾗﾘとして使うﾋｰﾌﾟID
 *
 */
//------------------------------------------------------------------
extern void ArcUtil_PalSet( u32 arcFile, u32 dataIdx, PALTYPE palType, u32 offs, u32 transSize, u32 heapID );


//------------------------------------------------------------------
/**
 * ﾊﾟﾚｯﾄﾃﾞｰﾀ の VRAM 転送（転送元の読み込み開始ｵﾌｾｯﾄ指定版）
 *
 * @param   fileIdx		ｱｰｶｲﾌﾞﾌｧｲﾙｲﾝﾃﾞｯｸｽ
 * @param   dataIdx		ｱｰｶｲﾌﾞﾃﾞｰﾀｲﾝﾃﾞｯｸｽ
 * @param   palType		ﾊﾟﾚｯﾄ転送先ﾀｲﾌﾟ
 * @param   srcOfs		ﾊﾟﾚｯﾄ転送元読み込み開始ｵﾌｾｯﾄ
 * @param   dstOfs		ﾊﾟﾚｯﾄ転送先ｵﾌｾｯﾄ
 * @param   transSize	ﾊﾟﾚｯﾄ転送ｻｲｽﾞ（0 で全転送）
 * @param   heapID		ﾃﾞｰﾀ読み込みﾃﾝﾎﾟﾗﾘとして使うﾋｰﾌﾟID
 *
 */
//------------------------------------------------------------------
extern void ArcUtil_PalSetEx( u32 fileIdx, u32 dataIdx, PALTYPE palType, u32 srcOfs, u32 dstOfs, u32 transSize, u32 heapID );

//------------------------------------------------------------------
/**
 * ﾊﾟﾚｯﾄﾃﾞｰﾀ の VRAM 転送＆ NITRO System ﾊﾟﾚｯﾄﾌﾟﾛｷｼ を作成
 *（3D, OBJ 用にのみ対応。BG には使いません）
 *
 * @param   fileIdx		ｱｰｶｲﾌﾞﾌｧｲﾙｲﾝﾃﾞｯｸｽ
 * @param   dataIdx		ｱｰｶｲﾌﾞﾃﾞｰﾀｲﾝﾃﾞｯｸｽ
 * @param   type		転送先ﾀｲﾌﾟ
 * @param   offs		転送ｵﾌｾｯﾄ
 * @param   heapID		ﾋｰﾌﾟID
 * @param   proxy		作成するﾌﾟﾛｷｼのｱﾄﾞﾚｽ
 *
 *	[ type ]
 *		NNS_G2D_VRAM_TYPE_3DMAIN = 0,
 *		NNS_G2D_VRAM_TYPE_2DMAIN = 1,
 *		NNS_G2D_VRAM_TYPE_2DSUB  = 2,
 *
 */
//------------------------------------------------------------------
extern void ArcUtil_PalSysLoad( u32 fileIdx, u32 dataIdx, NNS_G2D_VRAM_TYPE type, u32 offs, u32 heapID, NNSG2dImagePaletteProxy* proxy );

//------------------------------------------------------------------
/**
 * ｷｬﾗﾃﾞｰﾀ の VRAM 転送＆ NITRO System ｲﾒｰｼﾞﾌﾟﾛｷｼ を作成
 *（3D, OBJ 用にのみ対応。BG には使いません）
 *
 *
 * @param   fileIdx			ｱｰｶｲﾌﾞﾌｧｲﾙｲﾝﾃﾞｯｸｽ
 * @param   dataIdx			ｱｰｶｲﾌﾞﾃﾞｰﾀｲﾝﾃﾞｯｸｽ
 * @param   compressedFlag	圧縮されているか
 * @param   mapType			ﾏｯﾋﾟﾝｸﾞﾀｲﾌﾟ
 * @param   transSize		転送ｻｲｽﾞ（0なら全転送）
 * @param   vramType		転送先ﾀｲﾌﾟ
 * @param   offs			転送ｵﾌｾｯﾄ
 * @param   heapID			ﾃﾝﾎﾟﾗﾘに使うﾋｰﾌﾟID
 * @param   proxy			作成するﾌﾟﾛｷｼのｱﾄﾞﾚｽ
 *
 * @retval  転送されたﾃﾞｰﾀｻｲｽﾞ（ﾊﾞｲﾄ単位）
 *
 *	[ mapType ]
 *		MAP_TYPE_1D = 0,
 *		MAP_TYPE_2D = 1,
 *
 *	※ VRAM転送型は別関数 ArcUtil_TranCharSysLoad を使う
 *
 *	[ vramType ]
 *		NNS_G2D_VRAM_TYPE_3DMAIN = 0,
 *		NNS_G2D_VRAM_TYPE_2DMAIN = 1,
 *		NNS_G2D_VRAM_TYPE_2DSUB  = 2,
 *
 */
//------------------------------------------------------------------
extern u32 ArcUtil_CharSysLoad( u32 fileIdx, u32 dataIdx, BOOL compressedFlag, CHAR_MAPPING_TYPE mapType,
	u32 transSize, NNS_G2D_VRAM_TYPE vramType, u32 offs, u32 heapID, NNSG2dImageProxy* proxy );


//------------------------------------------------------------------
/**
 * ｷｬﾗﾃﾞｰﾀ の VRAM 転送＆ NITRO System ｲﾒｰｼﾞﾌﾟﾛｷｼ を作成
 *（3D, OBJ 用にのみ対応。BG には使いません）
 *
 * ｷｬﾗﾃﾞｰﾀのﾏｯﾋﾟﾝｸﾞﾓｰﾄﾞ値を、現在のﾚｼﾞｽﾀ設定に合わせて書き換えます
 *
 * @param   fileIdx			ｱｰｶｲﾌﾞﾌｧｲﾙｲﾝﾃﾞｯｸｽ
 * @param   dataIdx			ｱｰｶｲﾌﾞﾃﾞｰﾀｲﾝﾃﾞｯｸｽ
 * @param   compressedFlag	圧縮されているか
 * @param   mapType			ﾏｯﾋﾟﾝｸﾞﾀｲﾌﾟ
 * @param   transSize		転送サイズ。０なら全転送。
 * @param   vramType		転送先ﾀｲﾌﾟ
 * @param   offs			転送ｵﾌｾｯﾄ
 * @param   heapID			ﾃﾝﾎﾟﾗﾘに使うﾋｰﾌﾟID
 * @param   proxy			作成するﾌﾟﾛｷｼｱﾄﾞﾚｽ
 *
 *
 *	[ mapType ]
 *		CHAR_MAP_1D = 0,
 *		CHAR_MAP_2D = 1,
 *
 *	※ VRAM転送型は別関数 ArcUtil_TranCharSysLoad を使う
 *
 *	[ vramType ]
 *		NNS_G2D_VRAM_TYPE_3DMAIN = 0,
 *		NNS_G2D_VRAM_TYPE_2DMAIN = 1,
 *		NNS_G2D_VRAM_TYPE_2DSUB  = 2,
 *
 */
//------------------------------------------------------------------
extern void ArcUtil_CharSysLoadSyncroMappingMode( u32 fileIdx, u32 dataIdx, BOOL compressedFlag, CHAR_MAPPING_TYPE mapType, u32 transSize,
	NNS_G2D_VRAM_TYPE vramType, u32 offs, u32 heapID, NNSG2dImageProxy* proxy );

//------------------------------------------------------------------
/**
 * ｷｬﾗﾃﾞｰﾀ の VRAM 転送＆ NITRO System ｲﾒｰｼﾞﾌﾟﾛｷｼ を作成。VRAM転送型の画像素材用。
 *
 * ※ この関数を使っても、VRAMに画像は転送されません
 *    この関数でﾛｰﾄﾞしたﾃﾞｰﾀは解放されません。戻り値のconst void*を管理して、
 *    不要になったら解放処理を行ってください。
 *
 * @param   fileIdx			ｱｰｶｲﾌﾞﾌｧｲﾙｲﾝﾃﾞｯｸｽ
 * @param   dataIdx			ｱｰｶｲﾌﾞﾃﾞｰﾀｲﾝﾃﾞｯｸｽ
 * @param   compressedFlag	圧縮されているか
 * @param   vramType		転送先ﾀｲﾌﾟ
 * @param   offs			転送ｵﾌｾｯﾄ
 * @param   heapID			ﾃﾝﾎﾟﾗﾘに使うﾋｰﾌﾟID
 * @param   proxy			作成するﾌﾟﾛｷｼのｱﾄﾞﾚｽ
 * @param   charData		ｷｬﾗﾃﾞｰﾀｱﾄﾞﾚｽを保持するﾎﾟｲﾝﾀのｱﾄﾞﾚｽ
 *
 * @retval  const void*		ﾛｰﾄﾞしたﾃﾞｰﾀのｱﾄﾞﾚｽ
 *
 *	[ vramType ]
 *		NNS_G2D_VRAM_TYPE_3DMAIN = 0,
 *		NNS_G2D_VRAM_TYPE_2DMAIN = 1,
 *		NNS_G2D_VRAM_TYPE_2DSUB  = 2,
 *
 */
//------------------------------------------------------------------
extern const void* ArcUtil_TransTypeCharSysLoad( u32 fileIdx, u32 dataIdx, BOOL compressedFlag, 
	NNS_G2D_VRAM_TYPE vramType, u32 offs, u32 heapID, NNSG2dImageProxy* proxy, NNSG2dCharacterData** charData );


//------------------------------------------------------------------
/**
 * ｷｬﾗﾃﾞｰﾀを ﾛｰﾄﾞして Unpack するだけです。解放は各自で。
 *
 * @param   fileIdx				ｱｰｶｲﾌﾞﾌｧｲﾙｲﾝﾃﾞｯｸｽ
 * @param   dataIdx				ﾃﾞｰﾀｲﾝﾃﾞｯｸｽ
 * @param   compressedFlag		圧縮されているか
 * @param   charData			ｷｬﾗﾃﾞｰﾀｱﾄﾞﾚｽを保持するﾎﾟｲﾝﾀのｱﾄﾞﾚｽ
 * @param   heapID				ﾋｰﾌﾟID
 *
 * @retval  void*		ﾛｰﾄﾞしたﾃﾞｰﾀの先頭ﾎﾟｲﾝﾀ
 */
//------------------------------------------------------------------
extern void* ArcUtil_CharDataGet( u32 fileIdx, u32 dataIdx, BOOL compressedFlag, NNSG2dCharacterData** charData, u32 heapID );

//--------------------------------------------------------------------------------------------
/**
 * ｽｸﾘｰﾝﾃﾞｰﾀを ﾛｰﾄﾞして Unpack するだけです。解放は各自で。
 *
 * @param   fileIdx			ｱｰｶｲﾌﾞﾌｧｲﾙｲﾝﾃﾞｯｸｽ
 * @param   arcIndex		ｱｰｶｲﾌﾞﾃﾞｰﾀｲﾝﾃﾞｯｸｽ
 * @param   compressedFlag	圧縮されているﾃﾞｰﾀか？
 * @param   scrnData		ｽｸﾘｰﾝﾃﾞｰﾀｱﾄﾞﾚｽを保持するﾎﾟｲﾝﾀのｱﾄﾞﾚｽ
 * @param   heapID			ﾃﾞｰﾀ読み込み・解凍ﾃﾝﾎﾟﾗﾘとして使うﾋｰﾌﾟID
 *
 * @retval  void*		ﾛｰﾄﾞしたﾃﾞｰﾀの先頭ﾎﾟｲﾝﾀ
 */
//--------------------------------------------------------------------------------------------
extern void* ArcUtil_ScrnDataGet(u32 fileIdx, u32 dataIdx, BOOL compressedFlag, NNSG2dScreenData** scrnData, u32 heapID);

//------------------------------------------------------------------
/**
 * ﾊﾟﾚｯﾄﾃﾞｰﾀをﾛｰﾄﾞして Unpack するだけです。解放は各自で。
 *
 * @param   fileIdx			ｱｰｶｲﾌﾞﾌｧｲﾙｲﾝﾃﾞｯｸｽ
 * @param   arcIndex		ｱｰｶｲﾌﾞﾃﾞｰﾀｲﾝﾃﾞｯｸｽ
 * @param   palData			ﾊﾟﾚｯﾄﾃﾞｰﾀｱﾄﾞﾚｽを保持するﾎﾟｲﾝﾀのｱﾄﾞﾚｽ
 * @param   heapID			ﾋｰﾌﾟID
 *
 * @retval  void*		ﾛｰﾄﾞしたﾃﾞｰﾀの先頭ﾎﾟｲﾝﾀ
 */
//------------------------------------------------------------------
extern void* ArcUtil_PalDataGet( u32 fileIdx, u32 dataIdx, NNSG2dPaletteData** palData, u32 heapID );

//--------------------------------------------------------------------------------------------
/**
 * ｾﾙﾊﾞﾝｸﾃﾞｰﾀを ﾛｰﾄﾞして Unpack するだけです。解放は各自で。
 *
 * @param   fileIdx			ｱｰｶｲﾌﾞﾌｧｲﾙｲﾝﾃﾞｯｸｽ
 * @param   arcIndex		ｱｰｶｲﾌﾞﾃﾞｰﾀｲﾝﾃﾞｯｸｽ
 * @param   compressedFlag	圧縮されているﾃﾞｰﾀか？
 * @param   cellBank		ｾﾙﾊﾞﾝｸﾃﾞｰﾀｱﾄﾞﾚｽを保持するﾎﾟｲﾝﾀのｱﾄﾞﾚｽ
 * @param   heapID			ﾋｰﾌﾟID
 *
 * @retval  void*		ﾛｰﾄﾞしたﾃﾞｰﾀの先頭ﾎﾟｲﾝﾀ
 */
//--------------------------------------------------------------------------------------------
extern void* ArcUtil_CellBankDataGet(u32 fileIdx, u32 dataIdx, BOOL compressedFlag, NNSG2dCellDataBank** cellBank, u32 heapID );

//--------------------------------------------------------------------------------------------
/**
 * ｱﾆﾒﾊﾞﾝｸﾃﾞｰﾀを ﾛｰﾄﾞして Unpack するだけです。解放は各自で。
 *
 * @param   fileIdx			ｱｰｶｲﾌﾞﾌｧｲﾙｲﾝﾃﾞｯｸｽ
 * @param   arcIndex		ｱｰｶｲﾌﾞﾃﾞｰﾀｲﾝﾃﾞｯｸｽ
 * @param   compressedFlag	圧縮されているﾃﾞｰﾀか？
 * @param   anmBank			ｱﾆﾒﾊﾞﾝｸﾃﾞｰﾀｱﾄﾞﾚｽを保持するﾎﾟｲﾝﾀのｱﾄﾞﾚｽ
 * @param   heapID			ﾋｰﾌﾟID
 *
 * @retval  void*		ﾛｰﾄﾞしたﾃﾞｰﾀの先頭ﾎﾟｲﾝﾀ
 */
//--------------------------------------------------------------------------------------------
extern void* ArcUtil_AnimBankDataGet(u32 fileIdx, u32 dataIdx, BOOL compressedFlag, NNSG2dAnimBankData** anmBank, u32 heapID);


//------------------------------------------------------------------
/**
 * LZ圧縮後アーカイブされているデータを読み出し、解凍して返す
 *
 * @param   fileIdx		アーカイブファイルインデックス
 * @param   dataIdx		アーカイブデータインデックス
 * @param   heapID		読み出し・解凍に使うヒープＩＤ
 *
 * @retval  void*		解凍後のデータ保存先アドレス
 */
//------------------------------------------------------------------
extern void* ArcUtil_UnCompress(u32 fileIdx, u32 dataIdx, u32 heapID);


//------------------------------------------------------------------
/**
 * アーカイブデータの読み出し
 *
 * @param   fileIdx			アーカイブファイルインデックス
 * @param   dataIdx			アーカイブデータインデックス
 * @param   compressedFlag	圧縮されているか？
 * @param   heapID			メモリ確保に使うヒープＩＤ
 * @param   allocType		ヒープのどの位置からメモリ確保するか
 *
 * [allocType]
 *		ALLOC_TOP		ヒープ先頭から確保
 *		ALLOC_BOTTOM	ヒープ後方から確保
 *
 * @retval  void*			読み出し領域ポインタ
 */
//------------------------------------------------------------------
extern void* ArcUtil_Load(u32 fileIdx, u32 dataIdx, BOOL compressedFlag, u32 heapID, ALLOC_TYPE allocType);

//------------------------------------------------------------------
/**
 * アーカイブデータの読み出し＆データサイズ取得（圧縮されていたら解凍後のサイズを取得する）
 *
 * @param   fileIdx			アーカイブファイルインデックス
 * @param   dataIdx			アーカイブデータインデックス
 * @param   compressedFlag	圧縮されているか？
 * @param   heapID			メモリ確保に使うヒープＩＤ
 * @param   allocType		ヒープのどの位置からメモリ確保するか
 * @param   pSize			実データのバイトサイズを受け取る変数のポインタ
 *
 * [allocType]
 *		ALLOC_TOP		ヒープ先頭から確保
 *		ALLOC_BOTTOM	ヒープ後方から確保
 *
 * @retval  void*			読み出し領域ポインタ
 */
//------------------------------------------------------------------
extern void* ArcUtil_LoadEx(u32 fileIdx, u32 dataIdx, BOOL compressedFlag, u32 heapID, ALLOC_TYPE allocType, u32* pSize);



#endif
