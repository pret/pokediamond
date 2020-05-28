
//============================================================================================
/**
 * @file	arc_tool.h
 * @bfief	アーカイバ用ツールプログラム
 * @author	HisashiSogabe
 * @date	05.05.30
 */
//============================================================================================

#ifndef	__ARC_TOOL_H_
#define	__ARC_TOOL_H_

#include	"system/arc_tool.dat"

//============================================================================================
//		定数定義
//============================================================================================

#define	OFS_NO_SET		(0)		///<ArchiveDataLoadOfs,ArchiveDataLoadOfs用OFS値なしの定数
#define	SIZE_NO_SET		(0)		///<ArchiveDataLoadOfs,ArchiveDataLoadOfs用SIZE値なしの定数

extern	void	ArchiveDataLoad(void *data,int file_kind,int index);
extern	void	*ArchiveDataLoadMalloc(int file_kind,int index,int heap_id);
extern	void	*ArchiveDataLoadMallocLo(int file_kind,int index,int heap_id);
extern	void	ArchiveDataLoadOfs(void *data,int file_kind,int index,int ofs,int size);
extern	void	*ArchiveDataLoadMallocOfs(int file_kind,int index,int heap_id,int ofs,int size);
extern	void	*ArchiveDataLoadMallocOfsLo(int file_kind,int index,int heap_id,int ofs,int size);
extern	u16		ArchiveDataFileCntGet(int file_kind,int index);
extern	u32		ArchiveDataSizeGet(int file_kind,int index);





/*====================================================================================*/
/*
  アーカイブデータハンドル処理

    １つのアーカイブファイルから何度もデータ取得を行いたい時、ファイルの
  オープン・クローズ回数を減らすことで処理負荷を軽減させるための仕組み。
*/
/*====================================================================================*/


//--------------------------------------------------
/**
 * アーカイブデータハンドル構造体の宣言
 */
//--------------------------------------------------
typedef struct _ARCHANDLE  ARCHANDLE;

//------------------------------------------------------------------
/**
 * アーカイブデータハンドルオープン
 * （内部でファイルをオープンします）
 *
 * @param   arcId		アーカイブデータインデックス
 * @param   heapId		管理用ヒープＩＤ
 *
 * @retval  ARCHANDLE	オープンされたハンドルのポインタ（失敗ならNULL）
 */
//------------------------------------------------------------------
extern ARCHANDLE* ArchiveDataHandleOpen( u32 arcId, u32 heapId );

//------------------------------------------------------------------
/**
 * アーカイブデータハンドルクローズ
 * （内部でファイルをクローズします）
 *
 * @param   handle			ハンドルポインタ
 *
 */
//------------------------------------------------------------------
extern void ArchiveDataHandleClose( ARCHANDLE* handle );


//------------------------------------------------------------------
/**
 * アーカイブデータハンドルを使ってデータ取得
 *
 * @param   handle		ハンドルポインタ
 * @param   datId		アーカイブ内のデータインデックス
 * @param   buffer		データ読み込み先バッファ
 *
 */
//------------------------------------------------------------------
extern void ArchiveDataLoadByHandle( ARCHANDLE* handle, u32 datId, void* buffer );

//------------------------------------------------------------------
/**
 * アーカイブデータハンドルを使ってデータサイズ取得
 *
 * @param   handle		ハンドルポインタ
 * @param   datId		アーカイブ内のデータインデックス
 * @retval	u32			インデックスのデータサイズ
 *
 */
//------------------------------------------------------------------
extern u32 ArchiveDataSizeGetByHandle( ARCHANDLE* handle, u32 datId );

//------------------------------------------------------------------
/**
 * アーカイブデータハンドルを使ってデータ取得（読み込み開始オフセット＆サイズ指定）
 *
 * @param   handle		ハンドルポインタ
 * @param   datId		アーカイブ内のデータインデックス
 * @param   ofs			読み込み開始オフセット
 * @param   size		読み込みサイズ
 * @param   buffer		データ読み込み先バッファ
 *
 */
//------------------------------------------------------------------
extern void ArchiveDataLoadOfsByHandle( ARCHANDLE* handle, u32 datId, u32 ofs, u32 size, void* buffer );

//------------------------------------------------------------------
/**
 * アーカイブデータハンドルを使ってデータ取得（内部でアロケートしたメモリに）
 *
 * @param   handle			ハンドルポインタ
 * @param   datID			アーカイブ内のデータインデックス
 * @param   heapID			メモリアロケート用のヒープＩＤ
 *
 * @retval  u32				データサイズ（バイト）
 */
//------------------------------------------------------------------
extern void* ArchiveDataLoadAllocByHandle( ARCHANDLE* handle, u32 datID, u32 heapID );

//------------------------------------------------------------------
/**
 * アーカイブデータハンドルを使ってイメージデータオフセット取得
 *
 * @param   handle		ハンドルポインタ
 * @param   datId		アーカイブ内のデータインデックス
 * @param   offset		オフセット読み込み先バッファ
 *
 */
//------------------------------------------------------------------
extern void ArchiveDataLoadImgofsByHandle( ARCHANDLE* handle, u32 datId, u32* offset );

//------------------------------------------------------------------
/**
 * アーカイブデータハンドルを使ってデータ取得（ファイルハンドル内情報の続きから読み込み）
 *
 * @param   handle		ハンドルポインタ
 * @param   size		読み込みサイズ
 * @param   buffer		データ読み込み先バッファ
 *
 */
//------------------------------------------------------------------
extern	void ArchiveDataLoadByHandleContinue( ARCHANDLE* handle, u32 size, void* buffer );

//------------------------------------------------------------------
/**
 * アーカイブデータハンドルを介してファイルシーク
 *
 * @param   handle		ハンドルポインタ
 * @param   size
 *
 */
//------------------------------------------------------------------
void ArchiveDataSeekByHandle( ARCHANDLE* handle, u32 size );

//============================================================================================
/**
 * アーカイブファイルデータのファイル数を取得(ハンドル使用)
 *
 * @param	handle			ハンドルポインタ
 * @retval	u16				ファイル数	
 */
//============================================================================================
u16		ArchiveDataFileCntGetByHandle(ARCHANDLE* handle);
#endif	__ARC_TOOL_H_
