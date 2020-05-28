
//============================================================================================
/**
 * @file	arc_tool.c
 * @bfief	アーカイバ用ツールプログラム
 * @author	HisashiSogabe
 * @date	05.05.30
 */
//============================================================================================

#include "common.h"
#define	 __ARC_TOOL_DAT_TBL_	//アーカイバファイルテーブルも有効にするための定義
#include "system/arc_tool.h"
#include "arc_tool_def.h"

static	void	ArchiveDataLoadIndex(void *data,const char *name,int index,int ofs,int ofs_size);
static	void	*ArchiveDataLoadIndexMalloc(const char *name,int index,int heap_id,int ofs,int ofs_size,int flag);

void	ArchiveDataLoad(void *data,int file_kind,int index);
void	*ArchiveDataLoadMalloc(int file_kind,int index,int heap_id);
void	*ArchiveDataLoadMallocLo(int file_kind,int index,int heap_id);
void	ArchiveDataLoadOfs(void *data,int file_kind,int index,int ofs,int size);
void	*ArchiveDataLoadMallocOfs(int file_kind,int index,int heap_id,int ofs,int size);
void	*ArchiveDataLoadMallocOfsLo(int file_kind,int index,int heap_id,int ofs,int size);
u16		ArchiveDataFileCntGet(int file_kind,int index);
u32		ArchiveDataSizeGet(int file_kind,int index);

void	ArchiveDataLoadByHandleContinue( ARCHANDLE* handle, u32 size, void* buffer );

#define	ALLOC_HEAD	(0)		//領域を確保するとき先頭から確保
#define	ALLOC_TAIL	(1)		//領域を確保するとき後ろから確保

//============================================================================================
/**
 *
 *	nnsarcで作成したアーカイブファイルに対してIndexを指定して任意のデータを取り出す
 *
 * @param[in]	data		読み込んだデータを格納するワークのポインタ
 * @param[in]	name		読み込むアーカイブファイル名
 * @param[in]	index		読み込むデータのアーカイブ上のインデックスナンバー
 * @param[in]	ofs			読み込むデータの先頭からのオフセット
 * @param[in]	ofs_size	読み込むデータサイズ
 *
 */
//============================================================================================
static	void	ArchiveDataLoadIndex(void *data,const char *name,int index,int ofs,int ofs_size)
{
	FSFile		p_file;
	u32			size=0;
	u32			fat_top=0;
	u32			fnt_top=0;
	u32			img_top=0;
	u32			top=0;
	u32			bottom=0;
	u16			file_cnt=0;

	FS_InitFile(&p_file);
	FS_OpenFile(&p_file,name);
	FS_SeekFile(&p_file,ARC_HEAD_SIZE_POS,FS_SEEK_SET);				///<アーカイブヘッダのサイズ格納位置に移動
	FS_ReadFile(&p_file,&size,2);									///<アーカイブヘッダサイズをロード
	fat_top=size;
	FS_SeekFile(&p_file,fat_top+SIZE_OFFSET,FS_SEEK_SET);			///<FATのサイズ格納位置に移動
	FS_ReadFile(&p_file,&size,4);									///<FATサイズをロード
	FS_ReadFile(&p_file,&file_cnt,2);								///<FileCountをロード
	GF_ASSERT_MSG(file_cnt>index,"ServerArchiveDataLoadIndex file=%s, fileCnt=%d, index=%d", name, file_cnt, index);
	fnt_top=fat_top+size;
	FS_SeekFile(&p_file,fnt_top+SIZE_OFFSET,FS_SEEK_SET);			///<FNTのサイズ格納位置に移動
	FS_ReadFile(&p_file,&size,4);									///<FNTサイズをロード
	img_top=fnt_top+size;
	
	FS_SeekFile(&p_file,fat_top+FAT_HEAD_SIZE+index*8,FS_SEEK_SET);	///<取り出したいFATテーブルに移動
	FS_ReadFile(&p_file,&top,4);									///<FATテーブルtopをロード
	FS_ReadFile(&p_file,&bottom,4);									///<FATテーブルbottomをロード

	FS_SeekFile(&p_file,img_top+IMG_HEAD_SIZE+top+ofs,FS_SEEK_SET);	///<取り出したいIMGの先頭に移動
	
	if(ofs_size){
		size=ofs_size;
	}
	else{
		size=bottom-top;
	}

	GF_ASSERT_MSG(size!=0,"ServerArchiveDataLoadIndex:ReadDataSize=0!");
	FS_ReadFile(&p_file,data,size);									///<データをロード

	FS_CloseFile(&p_file);
}


//============================================================================================
/**
 *
 *	nnsarcで作成したアーカイブファイルに対してIndexを指定して任意のデータを取り出す
 *	読み込んだデータを格納するワークもこの関数内で確保して、ポインタを返す
 *
 * @param[in]	name		読み込むアーカイブファイル名
 * @param[in]	index		読み込むデータのアーカイブ上のインデックスナンバー
 * @param[in]	heap_id		メモリを確保するヒープ領域のID
 * @param[in]	ofs			読み込むデータの先頭からのオフセット
 * @param[in]	ofs_size	読み込むデータサイズ
 * @param[in]	flag		領域の前後どちらから確保するかフラグ
 *
 */
//============================================================================================
static	void	*ArchiveDataLoadIndexMalloc(const char *name,int index,int heap_id,int ofs,int ofs_size,int flag)
{
	FSFile		p_file;
	u32			size=0;
	u32			fat_top=0;
	u32			fnt_top=0;
	u32			img_top=0;
	u32			top=0;
	u32			bottom=0;
	void		*data;
	u16			file_cnt=0;

	FS_InitFile(&p_file);
	FS_OpenFile(&p_file,name);
	FS_SeekFile(&p_file,ARC_HEAD_SIZE_POS,FS_SEEK_SET);				///<アーカイブヘッダのサイズ格納位置に移動
	FS_ReadFile(&p_file,&size,2);									///<アーカイブヘッダサイズをロード
	fat_top=size;
	FS_SeekFile(&p_file,fat_top+SIZE_OFFSET,FS_SEEK_SET);			///<FATのサイズ格納位置に移動
	FS_ReadFile(&p_file,&size,4);									///<FATサイズをロード
	FS_ReadFile(&p_file,&file_cnt,2);								///<FileCountをロード
	GF_ASSERT_MSG(file_cnt>index,"ServerArchiveDataLoadIndex file=%s, fileCnt=%d, index=%d", name, file_cnt, index);
	fnt_top=fat_top+size;
	FS_SeekFile(&p_file,fnt_top+SIZE_OFFSET,FS_SEEK_SET);			///<FNTのサイズ格納位置に移動
	FS_ReadFile(&p_file,&size,4);									///<FNTサイズをロード
	img_top=fnt_top+size;
	
	FS_SeekFile(&p_file,fat_top+FAT_HEAD_SIZE+index*8,FS_SEEK_SET);	///<取り出したいFATテーブルに移動
	FS_ReadFile(&p_file,&top,4);									///<FATテーブルtopをロード
	FS_ReadFile(&p_file,&bottom,4);									///<FATテーブルbottomをロード

	FS_SeekFile(&p_file,img_top+IMG_HEAD_SIZE+top+ofs,FS_SEEK_SET);		///<取り出したいIMGの先頭に移動

	if(ofs_size){
		size=ofs_size;
	}
	else{
		size=bottom-top;
	}
	GF_ASSERT_MSG(size!=0,"ServerArchiveDataLoadIndex:ReadDataSize=0!");
	if(flag==ALLOC_HEAD){
		data=sys_AllocMemory(heap_id,size);
	}
	else{
		data=sys_AllocMemoryLo(heap_id,size);
	}
	FS_ReadFile(&p_file,data,size);									///<データをロード

	FS_CloseFile(&p_file);

	return data;
}

//============================================================================================
/**
 * アーカイブファイルデータロード
 *
 * @param[in]	data		読み込んだデータを格納するワークのポインタ
 * @param[in]	arcID		読み込むアーカイブファイルの種類インデックスナンバー（arc_tool.hに記述）
 * @param[in]	datID		読み込むデータのアーカイブファイル上のインデックスナンバー
 */
//============================================================================================
void	ArchiveDataLoad(void *data, int arcID, int datID)
{
	ArchiveDataLoadIndex(data, ArchiveFileTable[arcID], datID, OFS_NO_SET, SIZE_NO_SET);
}

//============================================================================================
/**
 * アーカイブファイルデータロード（読み込んだデータを格納するワークを関数内で確保するバージョン）
 *
 * ※関数内でワークをAllocするので、自前で開放処理をする必要があります(sys_FreeMemoryEz(領域ポインタ)で開放）
 *
 * @param[in]	arcID		読み込むアーカイブファイルの種類インデックスナンバー（arc_tool.hに記述）
 * @param[in]	datID		読み込むデータのアーカイブファイル上のインデックスナンバー
 * @param[in]	heap_id		メモリを確保するヒープ領域のID
 *
 * @retval	関数内で確保したデータ格納ワークのアドレス
 */
//============================================================================================
void* ArchiveDataLoadMalloc(int arcID, int datID, int heapID)
{
	return	ArchiveDataLoadIndexMalloc(ArchiveFileTable[arcID],datID,heapID,OFS_NO_SET,SIZE_NO_SET,ALLOC_HEAD);
}

//============================================================================================
/**
 * アーカイブファイルデータロード（読み込んだデータを格納するワークを関数内で確保するバージョン（領域の後ろから確保））
 *
 * ※関数内でワークをAllocするので、自前で開放処理をする必要があります(sys_FreeMemoryEz(領域ポインタ)で開放）
 *
 * @param[in]	arcID		読み込むアーカイブファイルの種類インデックスナンバー（arc_tool.hに記述）
 * @param[in]	datID		読み込むデータのアーカイブファイル上のインデックスナンバー
 * @param[in]	heapID		メモリを確保するヒープ領域のID
 *
 * @retval	関数内で確保したデータ格納ワークのアドレス
 */
//============================================================================================
void* ArchiveDataLoadMallocLo(int arcID, int datID, int heapID)
{
	return	ArchiveDataLoadIndexMalloc(ArchiveFileTable[arcID], datID, heapID, OFS_NO_SET, SIZE_NO_SET, ALLOC_TAIL);
}

//============================================================================================
/**
 * アーカイブファイルデータロード（オフセット指定あり）
 *
 * @param[in]	data		読み込んだデータを格納するワークのポインタ
 * @param[in]	arcID		読み込むアーカイブファイルの種類インデックスナンバー（arc_tool.hに記述）
 * @param[in]	datID		読み込むデータのアーカイブファイル上のインデックスナンバー
 * @param[in]	ofs			読み込むデータの先頭からのオフセット
 * @param[in]	size		読み込むデータサイズ
 */
//============================================================================================
void ArchiveDataLoadOfs(void *data, int arcID, int datID, int ofs, int size)
{
	ArchiveDataLoadIndex(data, ArchiveFileTable[arcID], datID, ofs, size);
}

//============================================================================================
/**
 * アーカイブファイルデータロード（読み込んだデータを格納するワークを関数内で確保するバージョンとオフセット指定あり）
 *
 * ※関数内でワークをAllocするので、自前で開放処理をする必要があります(sys_FreeMemoryEz(領域ポインタ)で開放）
 *
 * @param[in]	arcID		読み込むアーカイブファイルの種類インデックスナンバー（arc_tool.hに記述）
 * @param[in]	datID		読み込むデータのアーカイブファイル上のインデックスナンバー
 * @param[in]	heapID		メモリを確保するヒープ領域のID
 * @param[in]	ofs			読み込むデータの先頭からのオフセット
 * @param[in]	size		読み込むデータサイズ
 *
 * @retval	関数内で確保したデータ格納ワークのアドレス
 */
//============================================================================================
void* ArchiveDataLoadMallocOfs(int arcID, int datID, int heapID, int ofs, int size)
{
	return	ArchiveDataLoadIndexMalloc(ArchiveFileTable[arcID],datID,heapID,ofs,size,ALLOC_HEAD);
}

//============================================================================================
/**
 * アーカイブファイルデータロード（読み込んだデータを格納するワークを関数内で確保するバージョンとオフセット指定あり）
 *
 * ※関数内でワークをAllocするので、自前で開放処理をする必要があります(sys_FreeMemoryEz(領域ポインタ)で開放）
 *
 * @param[in]	arcID		読み込むアーカイブファイルの種類インデックスナンバー（arc_tool.hに記述）
 * @param[in]	datID		読み込むデータのアーカイブファイル上のインデックスナンバー
 * @param[in]	heapID		メモリを確保するヒープ領域のID
 * @param[in]	ofs			読み込むデータの先頭からのオフセット
 * @param[in]	size		読み込むデータサイズ
 *
 * @retval	関数内で確保したデータ格納ワークのアドレス
 */
//============================================================================================
void	*ArchiveDataLoadMallocOfsLo(int arcID, int datID, int heapID, int ofs, int size)
{
	return	ArchiveDataLoadIndexMalloc(ArchiveFileTable[arcID],datID,heapID,ofs,size,ALLOC_TAIL);
}

//============================================================================================
/**
 * アーカイブファイルデータのファイル数を取得
 *
 * @param[in]	arcID	読み込むアーカイブファイルの種類インデックスナンバー（arc_tool.hに記述）
 * @param[in]	datID		読み込むデータのアーカイブファイル上のインデックスナンバー
 */
//============================================================================================
u16		ArchiveDataFileCntGet(int arcID, int datID)
{
	FSFile		p_file;
	u32			size=0;
	u32			fat_top=0;
	u16			file_cnt=0;

	FS_InitFile(&p_file);
	FS_OpenFile(&p_file,ArchiveFileTable[arcID]);
	FS_SeekFile(&p_file,ARC_HEAD_SIZE_POS,FS_SEEK_SET);				///<アーカイブヘッダのサイズ格納位置に移動
	FS_ReadFile(&p_file,&size,2);									///<アーカイブヘッダサイズをロード
	fat_top=size;
	FS_SeekFile(&p_file,fat_top+SIZE_OFFSET,FS_SEEK_SET);			///<FATのサイズ格納位置に移動
	FS_ReadFile(&p_file,&size,4);									///<FATサイズをロード
	FS_ReadFile(&p_file,&file_cnt,2);								///<FileCountをロード

	return	file_cnt;
}

//============================================================================================
/**
 * アーカイブファイルデータのサイズを取得
 *
 *	ArchiveDataLoadを使用する時、確保するメモリサイズを取得するのに使用します
 *
 * @param[in]	arcID		読み込むアーカイブファイルの種類インデックスナンバー（arc_tool.hに記述）
 * @param[in]	datID		読み込むデータのアーカイブファイル上のインデックスナンバー
 */
//============================================================================================
u32		ArchiveDataSizeGet(int arcID,int datID)
{
	FSFile		p_file;
	u32			size=0;
	u32			fat_top=0;
	u32			fnt_top=0;
	u32			img_top=0;
	u32			top=0;
	u32			bottom=0;
	void		*data;
	u16			file_cnt=0;

	FS_InitFile(&p_file);
	FS_OpenFile(&p_file,ArchiveFileTable[arcID]);
	FS_SeekFile(&p_file,ARC_HEAD_SIZE_POS,FS_SEEK_SET);				///<アーカイブヘッダのサイズ格納位置に移動
	FS_ReadFile(&p_file,&size,2);									///<アーカイブヘッダサイズをロード
	fat_top=size;
	FS_SeekFile(&p_file,fat_top+SIZE_OFFSET,FS_SEEK_SET);			///<FATのサイズ格納位置に移動
	FS_ReadFile(&p_file,&size,4);									///<FATサイズをロード
	FS_ReadFile(&p_file,&file_cnt,2);								///<FileCountをロード
	GF_ASSERT_MSG(file_cnt>datID,"ServerArchiveDataLoadIndex:FileCnt<Index");
	fnt_top=fat_top+size;
	FS_SeekFile(&p_file,fnt_top+SIZE_OFFSET,FS_SEEK_SET);			///<FNTのサイズ格納位置に移動
	FS_ReadFile(&p_file,&size,4);									///<FNTサイズをロード
	img_top=fnt_top+size;
	
	FS_SeekFile(&p_file,fat_top+FAT_HEAD_SIZE+datID*8,FS_SEEK_SET);	///<取り出したいFATテーブルに移動
	FS_ReadFile(&p_file,&top,4);									///<FATテーブルtopをロード
	FS_ReadFile(&p_file,&bottom,4);									///<FATテーブルbottomをロード

	FS_SeekFile(&p_file,img_top+IMG_HEAD_SIZE+top,FS_SEEK_SET);		///<取り出したいIMGの先頭に移動
	size=bottom-top;
	GF_ASSERT_MSG(size!=0,"ServerArchiveDataLoadIndex:ReadDataSize=0!");

	return	size;
}




//--------------------------------------------------------
/**
 * アーカイブファイルのハンドル管理構造体
 */
//--------------------------------------------------------
struct _ARCHANDLE{
	FSFile  file;
	u32     fat_top;
	u32     img_top;
	u16		file_cnt;
};


//------------------------------------------------------------------
/**
 * アーカイブデータのファイルハンドルオープン
 *
 * @param   arcId		アーカイブデータインデックス
 * @param   heapId		管理用ヒープＩＤ
 *
 * @retval  ARCHANDLE	オープンされたハンドルのポインタ（失敗ならNULL）
 */
//------------------------------------------------------------------
ARCHANDLE* ArchiveDataHandleOpen( u32 arcId, u32 heapId )
{
	ARCHANDLE* handle = sys_AllocMemory( heapId, sizeof(ARCHANDLE) );
	if( handle )
	{
		u32 fnt_top, tmp;

		// ２バイトを読み込んだ時にゴミが入らないようにしておく
		handle->fat_top = 0;

		FS_InitFile( &(handle->file) );
		FS_OpenFile( &(handle->file), ArchiveFileTable[arcId] );
		FS_SeekFile( &(handle->file), ARC_HEAD_SIZE_POS, FS_SEEK_SET );
		FS_ReadFile( &(handle->file), &(handle->fat_top), 2 );
		FS_SeekFile( &(handle->file), handle->fat_top+SIZE_OFFSET, FS_SEEK_SET );
		FS_ReadFile( &(handle->file), &tmp, 4 );
		FS_ReadFile( &(handle->file), &(handle->file_cnt), 2 );
		fnt_top = handle->fat_top + tmp;
		FS_SeekFile( &(handle->file), fnt_top+SIZE_OFFSET, FS_SEEK_SET );
		FS_ReadFile( &(handle->file), &tmp, 4 );
		handle->img_top = fnt_top + tmp;

	}
	return handle;
}

//------------------------------------------------------------------
/**
 * アーカイブデータのハンドルクローズ
 *
 * @param   handle			ハンドルポインタ
 *
 */
//------------------------------------------------------------------
void ArchiveDataHandleClose( ARCHANDLE* handle )
{
	FS_CloseFile( &(handle->file) );
	sys_FreeMemoryEz( handle );
}

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
void* ArchiveDataLoadAllocByHandle( ARCHANDLE* handle, u32 datId, u32 heapID )
{
	u32 top, bottom;
	void* buf;

	GF_ASSERT_MSG(handle->file_cnt>datId, "DatCount=%d, DatID=%d", handle->file_cnt, datId);

	FS_SeekFile( &(handle->file), handle->fat_top+FAT_HEAD_SIZE+datId*8, FS_SEEK_SET );
	FS_ReadFile( &(handle->file), &top, 4 );
	FS_ReadFile( &(handle->file), &bottom, 4 );
	FS_SeekFile( &(handle->file), handle->img_top+IMG_HEAD_SIZE+top, FS_SEEK_SET );

	buf = sys_AllocMemory(heapID, bottom-top);
	if( buf )
	{
		FS_ReadFile( &(handle->file), buf, bottom-top );
	}

	return buf;
}

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
void ArchiveDataLoadByHandle( ARCHANDLE* handle, u32 datId, void* buffer )
{
	u32 top, bottom;
	
	GF_ASSERT_MSG(handle->file_cnt>datId, "DatCount=%d, DatID=%d", handle->file_cnt, datId);
	
	FS_SeekFile( &(handle->file), handle->fat_top+FAT_HEAD_SIZE+datId*8, FS_SEEK_SET );
	FS_ReadFile( &(handle->file), &top, 4 );
	FS_ReadFile( &(handle->file), &bottom, 4 );
	FS_SeekFile( &(handle->file), handle->img_top+IMG_HEAD_SIZE+top, FS_SEEK_SET );
	
	FS_ReadFile( &(handle->file), buffer, bottom-top );
}

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
u32 ArchiveDataSizeGetByHandle( ARCHANDLE* handle, u32 datId )
{
	u32 top, bottom;
	
	GF_ASSERT_MSG(handle->file_cnt>datId, "DatCount=%d, DatID=%d", handle->file_cnt, datId);
	
	FS_SeekFile( &(handle->file), handle->fat_top+FAT_HEAD_SIZE+datId*8, FS_SEEK_SET );
	FS_ReadFile( &(handle->file), &top, 4 );
	FS_ReadFile( &(handle->file), &bottom, 4 );
	
	return( bottom-top );
}

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
void ArchiveDataLoadOfsByHandle( ARCHANDLE* handle, u32 datId, u32 ofs, u32 size, void* buffer )
{
	u32 top;

	GF_ASSERT_MSG(handle->file_cnt>datId, "DatCount=%d, DatID=%d", handle->file_cnt, datId);

	FS_SeekFile( &(handle->file), handle->fat_top+FAT_HEAD_SIZE+datId*8, FS_SEEK_SET );
	FS_ReadFile( &(handle->file), &top, 4 );
	FS_SeekFile( &(handle->file), handle->img_top+IMG_HEAD_SIZE+top+ofs, FS_SEEK_SET );

	FS_ReadFile( &(handle->file), buffer, size );
}

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
void ArchiveDataLoadImgofsByHandle( ARCHANDLE* handle, u32 datId, u32* offset )
{
	u32 top;

	GF_ASSERT_MSG(handle->file_cnt>datId, "DatCount=%d, DatID=%d", handle->file_cnt, datId);

	FS_SeekFile( &(handle->file), handle->fat_top+FAT_HEAD_SIZE+datId*8, FS_SEEK_SET );
	FS_ReadFile( &(handle->file), &top, 4 );
	
	*offset = handle->img_top+IMG_HEAD_SIZE+top;
}

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
void ArchiveDataLoadByHandleContinue( ARCHANDLE* handle, u32 size, void* buffer )
{
	FS_ReadFile( &(handle->file), buffer, size );
}

//------------------------------------------------------------------
/**
 * アーカイブデータハンドルを介してファイルシーク
 *
 * @param   handle		ハンドルポインタ
 * @param   size
 *
 */
//------------------------------------------------------------------
void ArchiveDataSeekByHandle( ARCHANDLE* handle, u32 size )
{
	FS_SeekFile( &(handle->file), size, FS_SEEK_SET );
}

//============================================================================================
/**
 * アーカイブファイルデータのファイル数を取得(ハンドル使用)
 *
 * @param	handle			ハンドルポインタ
 * @retval	u16				ファイル数	
 */
//============================================================================================
u16		ArchiveDataFileCntGetByHandle(ARCHANDLE* handle)
{
	return	handle->file_cnt;
}
