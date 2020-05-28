#include "common.h"
#include "height.h"
#include "system/arc_tool.h"

#define GRID_ENTRY_HEADER_SIZE	(4)

#define DIV_HEIGHT_DATA_SIZE	(/*0x4000*/0xe000)

#define HEIGHT_HEADER_SIZE	(40)

///#define INVALIED_HEIGHT_MEM_ALOOC

typedef struct {
	int VtxNum;
	int NrmNum;
	int PolygonNum;
	int GridNum;
	int TotalPolyIDListSize;
	int TotalLineListSize;
	int LineEntryMax;
}READ_INFO;

typedef struct {
	FSFile  file;
	int DataOffset;
	READ_INFO	ReadInfo;
	BOOL    OpenIsOK;
	u8 Seq;
	char Path[40];
	u8 *HeightMem;
	MHI_PTR	HeightData;
	BOOL	StopFlg;
	int *EndFlg;
	ARCHANDLE *ArcHandle;
	int DataSize;
	int *Counter;
}HEIGHT_TASK_DATA;


//////////////////////////////////////////////////////////////////////////////
// 前方宣言
//////////////////////////////////////////////////////////////////////////////
static void* ReadData(void *buf, int len, FSFile *p_file);
static BOOL ReadFileDiv(FSFile *inFile,
						const u16 inDivSize,
						const int inTotalReadSize,
						void** outMemory,
						int *ioDataOffset);
static BOOL ReadDataDiv(FSFile *p_file,
						void** outMemory,
						const int inReadSize,
						int *ioDataOffset);
static void ReadHeaderData(FSFile *p_file, READ_INFO *outInfo);
static void AllocDataMem(MHI_PTR	outMapHeightInfo, const READ_INFO *outInfo);
static void SetDataMem(const READ_INFO *inInfo, MHI_PTR	outMapHeightInfo, void **mem);

static void ReadGridSpData(FSFile *p_file, MHI_PTR outMap3DInfo);
static void ReadVtxData(FSFile *p_file, MHI_PTR outMap3DInfo, const READ_INFO *inInfo);
static void ReadNrmData(FSFile *p_file, MHI_PTR outMap3DInfo, const READ_INFO *inInfo);
static void ReadPolygonData(FSFile *p_file, MHI_PTR outMap3DInfo, const READ_INFO *inInfo);
static void ReadGridDataTbl(FSFile *p_file, MHI_PTR outMap3DInfo, const READ_INFO *inInfo);
static void ReadLineDataTbl(FSFile *p_file, MHI_PTR outMap3DInfo, const READ_INFO *inInfo);
static void ReadGridData(FSFile *p_file, MHI_PTR outMap3DInfo, const READ_INFO *inInfo);

static void ReadGridSpDataArc(ARCHANDLE *ioHandle, MHI_PTR outMap3DInfo);
static void ReadVtxDataArc(ARCHANDLE *ioHandle, MHI_PTR outMap3DInfo, const READ_INFO *inInfo);
static void ReadNrmDataArc(ARCHANDLE *ioHandle, MHI_PTR outMap3DInfo, const READ_INFO *inInfo);
static void ReadPolygonDataArc(ARCHANDLE *ioHandle, MHI_PTR outMap3DInfo, const READ_INFO *inInfo);
static void ReadGridDataTblArc(ARCHANDLE *ioHandle, MHI_PTR outMap3DInfo, const READ_INFO *inInfo);
static void ReadLineDataTblArc(ARCHANDLE *ioHandle, MHI_PTR outMap3DInfo, const READ_INFO *inInfo);
static void ReadGridDataArc(ARCHANDLE *ioHandle, MHI_PTR outMap3DInfo, const READ_INFO *inInfo);


#ifdef PM_DEBUG
extern u32 sys_GetMemoryBlockSize( const void* memBlock );
#endif


static void* ReadData(void *buf, int len, FSFile *p_file)
{
    int ret = FS_ReadFile(p_file, buf, len);
    if(ret < 0){
		return  NULL;
	}
    return  buf;
}

static BOOL ReadFileDiv(FSFile *inFile,
						const u16 inDivSize,
						const int inTotalReadSize,
						void** outMemory,
						int *ioDataOffset)
{
	int read_size;
	void*	read_p;
	read_p = &((u8*)*outMemory)[*ioDataOffset];

	if (!( inFile && read_p && (inDivSize>=1) ) ){
		OS_Printf("ファイルエラー発生！！\n");
		if (!inFile){
			OS_Printf("ファイルポインタ異常\n");
		}
		if(!read_p){
			OS_Printf("メモリ異常\n");
		}
		if(!(inDivSize>=1)){
			OS_Printf("サイズ異常\n");
		}
	}
	read_size = FS_ReadFile(inFile, read_p, inDivSize);
	*ioDataOffset = (*ioDataOffset) + read_size;	//リードオフセット増加
	if (*ioDataOffset >= inTotalReadSize){
		*ioDataOffset = 0;
		return TRUE;
	}
	return FALSE;
}

//グリッド分割データをリード
static BOOL ReadDataDiv(FSFile *p_file,
						void** outMemory,
						const int inReadSize,
						int *ioDataOffset)
{
	int div_size;
	int rest_size;
	rest_size = inReadSize - (*ioDataOffset);
	if (rest_size < DIV_HEIGHT_DATA_SIZE){
		div_size = rest_size;
	}else{
		div_size = DIV_HEIGHT_DATA_SIZE;
	}
	return ReadFileDiv(p_file, div_size, inReadSize,outMemory,ioDataOffset);
}

static BOOL ReadArcDataDiv(	ARCHANDLE *ioHandle,
							void** outMemory,
							const int inReadSize,
							int *ioDataOffset)
{
	int div_size;
	int rest_size;
	BOOL rc;
	void *mem;
	rest_size = inReadSize - (*ioDataOffset);
	if (rest_size <= DIV_HEIGHT_DATA_SIZE){
		div_size = rest_size;
		rc = TRUE;	//これ読んで終了
	}else{
		div_size = DIV_HEIGHT_DATA_SIZE;
		rc = FALSE;	//継続
	}
	mem = &((u8*)(*outMemory))[*ioDataOffset];
	ArchiveDataLoadByHandleContinue( ioHandle, div_size, mem );
	if (rc){
		(*ioDataOffset) = 0;
	}else{
		(*ioDataOffset)+=div_size;
	}
	return rc;
}

///////////////////////////////////////////////////////////////////////////////////////////////

//ヘッダーデータ8+32バイトを読む
static void ReadHeaderData(FSFile *p_file, READ_INFO *outInfo)
{	
	u16 temp[4];

	//格納先のクリーン
	MI_CpuClear32(outInfo,sizeof(READ_INFO));

	//ID、ヘッダーサイズデータ計８バイトを読み飛ばす
	ReadData(temp, 8, p_file);
	//１つの頂点データサイズ（今は読み飛ばす）
	ReadData(temp, 2, p_file);
	//頂点数
	ReadData(&outInfo->VtxNum, 2, p_file);
	//１つの法線データサイズ（今は読み飛ばす）
	ReadData(temp, 2, p_file);
	//法線数
	ReadData(&outInfo->NrmNum, 2, p_file);
	//１つのポリゴンデータサイズ（今は読み飛ばす）
	ReadData(temp, 2, p_file);
	//三角ポリゴン数
	ReadData(&outInfo->PolygonNum, 2, p_file);
	//グリッド分割データサイズ（今は読み飛ばす）
	ReadData(temp, 2, p_file);
	//グリッドデータサイズ（今は読み飛ばす）
	ReadData(temp, 2, p_file);
	//グリッド数
	ReadData(&outInfo->GridNum, 2, p_file);
	//ラインエントリデータのヘッダサイズ（今は読み飛ばす）
	ReadData(temp, 2, p_file);
	//ラインエントリ最大数
	ReadData(&outInfo->LineEntryMax, 2, p_file);
	//ダミー
	ReadData(temp, 2, p_file);
	//ライン総数
	ReadData(&outInfo->TotalLineListSize, 4, p_file);
	//ポリゴンインデックス実データ
	ReadData(&outInfo->TotalPolyIDListSize, 4, p_file);

#if 0
OS_Printf("VtxNum				%d\n", outInfo->VtxNum );
OS_Printf("NrmNum				%d\n", outInfo->NrmNum);
OS_Printf("PolygonNum			%d\n", outInfo->PolygonNum);
OS_Printf("GridNum				%d\n", outInfo->GridNum);
OS_Printf("LineEntryMax			%d\n", outInfo->LineEntryMax );
OS_Printf("TotalLineListSize	%d\n", outInfo->TotalLineListSize);
OS_Printf("TotalPolyIDListSize	%d\n", outInfo->TotalPolyIDListSize);
#endif
}

//ヘッダーデータ8+32バイトを読む
static void ReadHeaderDataArc(ARCHANDLE *ioHandle, READ_INFO *outInfo)
{	
	u16 temp[4];

	//格納先のクリーン
	MI_CpuClear32(outInfo,sizeof(READ_INFO));

	//ID、ヘッダーサイズデータ計８バイトを読み飛ばす
	ArchiveDataLoadByHandleContinue( ioHandle, 8, temp );
	//１つの頂点データサイズ（今は読み飛ばす）
	ArchiveDataLoadByHandleContinue( ioHandle, 2, temp );
	//頂点数
	ArchiveDataLoadByHandleContinue( ioHandle, 2, &outInfo->VtxNum );
	//１つの法線データサイズ（今は読み飛ばす）
	ArchiveDataLoadByHandleContinue( ioHandle, 2, temp );
	//法線数
	ArchiveDataLoadByHandleContinue( ioHandle, 2, &outInfo->NrmNum );
	//１つのポリゴンデータサイズ（今は読み飛ばす）
	ArchiveDataLoadByHandleContinue( ioHandle, 2, temp );
	//三角ポリゴン数
	ArchiveDataLoadByHandleContinue( ioHandle, 2, &outInfo->PolygonNum );
	//グリッド分割データサイズ（今は読み飛ばす）
	ArchiveDataLoadByHandleContinue( ioHandle, 2, temp );
	//グリッドデータサイズ（今は読み飛ばす）
	ArchiveDataLoadByHandleContinue( ioHandle, 2, temp );
	//グリッド数
	ArchiveDataLoadByHandleContinue( ioHandle, 2, &outInfo->GridNum );
	//ラインエントリデータのヘッダサイズ（今は読み飛ばす）
	ArchiveDataLoadByHandleContinue( ioHandle, 2, temp );
	//ラインエントリ最大数
	ArchiveDataLoadByHandleContinue( ioHandle, 2, &outInfo->LineEntryMax );
	//ダミー
	ArchiveDataLoadByHandleContinue( ioHandle, 2, temp );
	//ライン総数
	ArchiveDataLoadByHandleContinue( ioHandle, 4, &outInfo->TotalLineListSize );
	//ポリゴンインデックス実データ
	ArchiveDataLoadByHandleContinue( ioHandle, 4, &outInfo->TotalPolyIDListSize );


}

static void AllocDataMem(MHI_PTR outMapHeightInfo, const READ_INFO *inInfo)
{
#ifdef HEIGHT_DATA_MEMORRY_DEBUG
	OS_Printf("Before Get Height Data:Graphic_Heap = %x\n",sys_GetHeapFreeSize(HEAPID_FIELD));
#endif	
	//頂点データ
	outMapHeightInfo->VertexArray = sys_AllocMemory(HEAPID_FIELD,sizeof(VecFx32)*inInfo->VtxNum);
	//法線データ
	outMapHeightInfo->NormalArray = sys_AllocMemory(HEAPID_FIELD,sizeof(VecFx32)*inInfo->NrmNum);
	//ポリゴンデータ
	outMapHeightInfo->PolygonData = sys_AllocMemory(HEAPID_FIELD,sizeof(POLYGON_DATA)*inInfo->PolygonNum);
	//グリッド分割データ
	outMapHeightInfo->SplitGridData = sys_AllocMemory(HEAPID_FIELD,sizeof(SPLIT_GRID_DATA));
	//グリッドテーブルデータ
	outMapHeightInfo->GridDataTbl = sys_AllocMemory(HEAPID_FIELD,GRID_ENTRY_HEADER_SIZE*inInfo->GridNum);
	//ラインテーブルデータ
	outMapHeightInfo->LineDataTbl = sys_AllocMemory(HEAPID_FIELD,inInfo->TotalLineListSize);

	//ライン内ポリゴンIDエントリデータ
	outMapHeightInfo->PolyIDList = sys_AllocMemory(HEAPID_FIELD,inInfo->TotalPolyIDListSize);

#ifdef DEBUG_ONLY_FOR_saitou
	OS_Printf("local_print height_data_toal:%x\n",
			(sizeof(VecFx32)*inInfo->VtxNum)+(sizeof(VecFx32)*inInfo->NrmNum)+ \
			sizeof(POLYGON_DATA)*inInfo->PolygonNum+sizeof(SPLIT_GRID_DATA)+ \
			(GRID_ENTRY_HEADER_SIZE*inInfo->GridNum)+inInfo->TotalLineListSize+ \
			inInfo->TotalPolyIDListSize);
#endif
	if (!outMapHeightInfo->VertexArray){
		OS_Printf("VertexArray:メモリ確保に失敗\n");
	}
	if (!outMapHeightInfo->NormalArray){
		OS_Printf("NormalArray:メモリ確保に失敗\n");
	}
	if (!outMapHeightInfo->PolygonData){
		OS_Printf("PolygonData:メモリ確保に失敗\n");
	}
	if (!outMapHeightInfo->SplitGridData){
		OS_Printf("SplitGridData:メモリ確保に失敗\n");
	}
	if (!outMapHeightInfo->GridDataTbl){
		OS_Printf("GridDataTbl:メモリ確保に失敗\n");
	}
	if (!outMapHeightInfo->LineDataTbl){
		OS_Printf("LineDataTbl:メモリ確保に失敗\n");
	}
	if (!outMapHeightInfo->PolyIDList){
		OS_Printf("PolyIDList:メモリ確保に失敗\n");
	}
}
/**
static void SetDataMem(const READ_INFO *inInfo, MHI_PTR	outMapHeightInfo, void **mem)
{
	void *p;
	u8 *data;
	int offset;
	offset = 0;
	data = *mem;
#ifdef HEIGHT_DATA_MEMORRY_DEBUG
	OS_Printf("Before Get Height Data:Graphic_Heap = %x\n",sys_GetHeapFreeSize(HEAPID_FIELD));
#endif

	//頂点データ
	p = &((u8*)*mem)[0];
	outMapHeightInfo->VertexArray = p;//(void *)&data[0];
	offset += (sizeof(VecFx32)*inInfo->VtxNum);
	//法線データ
	p = &((u8*)*mem)[offset];
	outMapHeightInfo->NormalArray = p;//(void *)&data[offset];
	offset += (sizeof(VecFx32)*inInfo->NrmNum);
	//ポリゴンデータ
	p = &((u8*)*mem)[offset];
	outMapHeightInfo->PolygonData = p;//(void *)&data[offset];
	offset += (sizeof(POLYGON_DATA)*inInfo->PolygonNum);
	//グリッド分割データ
	p = &((u8*)*mem)[offset];
	outMapHeightInfo->SplitGridData = p;//(void *)&data[offset];
	offset += (sizeof(SPLIT_GRID_DATA));
	//グリッドテーブルデータ
	p = &((u8*)*mem)[offset];
	outMapHeightInfo->GridDataTbl = p;//(void *)&data[offset];
	offset += (GRID_ENTRY_HEADER_SIZE*inInfo->GridNum);
	//ラインテーブルデータ
	p = &((u8*)*mem)[offset];
	outMapHeightInfo->LineDataTbl = p;//(void *)&data[offset];
	offset += (inInfo->TotalLineListSize);
	//ライン内ポリゴンIDエントリデータ
	p = &((u8*)*mem)[offset];
	outMapHeightInfo->PolyIDList = p;//(void *)&data[offset];
	offset += (inInfo->TotalPolyIDListSize);

///#ifdef HEIGHT_DATA_MEMORRY_DEBUG
	OS_Printf("height_data_toal:%x\n",
			(sizeof(VecFx32)*inInfo->VtxNum)+(sizeof(VecFx32)*inInfo->NrmNum)+ \
			sizeof(POLYGON_DATA)*inInfo->PolygonNum+sizeof(SPLIT_GRID_DATA)+ \
			(GRID_ENTRY_HEADER_SIZE*inInfo->GridNum)+inInfo->TotalLineListSize+ \
			inInfo->TotalPolyIDListSize);
///#endif
	
	GF_ASSERT((offset<=0x8000)&&"高さデータメモリオーバー");
}
*/
static void SetDataMem(const READ_INFO *inInfo, MHI_PTR	outMapHeightInfo, void **mem)
{
	void *p;
	int offset;
	u8 mod;
	offset = 0;
#ifdef HEIGHT_DATA_MEMORRY_DEBUG
	OS_Printf("Before Get Height Data:Graphic_Heap = %x\n",sys_GetHeapFreeSize(HEAPID_FIELD));
#endif

	//頂点データ
	p = &((u8*)(*mem))[0];
	outMapHeightInfo->VertexArray = p;//(void *)&data[0];
	offset += (sizeof(VecFx32)*inInfo->VtxNum);
	mod = offset%4;
	if (mod != 0){
		offset += mod;
	}
	//法線データ
	p = &((u8*)(*mem))[offset];
	outMapHeightInfo->NormalArray = p;//(void *)&data[offset];
	offset += (sizeof(VecFx32)*inInfo->NrmNum);
	mod = offset%4;
	if (mod != 0){
		offset += mod;
	}
	//ポリゴンデータ
	p = &((u8*)(*mem))[offset];
	outMapHeightInfo->PolygonData = p;//(void *)&data[offset];
	offset += (sizeof(POLYGON_DATA)*inInfo->PolygonNum);
	mod = offset%4;
	if (mod != 0){
		offset += mod;
	}
	//グリッド分割データ
	p = &((u8*)(*mem))[offset];
	outMapHeightInfo->SplitGridData = p;//(void *)&data[offset];
	offset += (sizeof(SPLIT_GRID_DATA));
	mod = offset%4;
	if (mod != 0){
		offset += mod;
	}
	//グリッドテーブルデータ
	p = &((u8*)(*mem))[offset];
	outMapHeightInfo->GridDataTbl = p;//(void *)&data[offset];
	offset += (GRID_ENTRY_HEADER_SIZE*inInfo->GridNum);
	mod = offset%4;
	if (mod != 0){
		offset += mod;
	}
	//ラインテーブルデータ
	p = &((u8*)(*mem))[offset];
	outMapHeightInfo->LineDataTbl = p;//(void *)&data[offset];
	offset += (inInfo->TotalLineListSize);
	mod = offset%4;
	if (mod != 0){
		offset += mod;
	}
	//ライン内ポリゴンIDエントリデータ
	p = &((u8*)(*mem))[offset];
	outMapHeightInfo->PolyIDList = p;//(void *)&data[offset];
	offset += (inInfo->TotalPolyIDListSize);
	mod = offset%4;
	if (mod != 0){
		offset += mod;
	}

#ifdef DEBUG_ONLY_FOR_saitou
	OS_Printf("local_print height_data_toal:%x\n",
			(sizeof(VecFx32)*inInfo->VtxNum)+(sizeof(VecFx32)*inInfo->NrmNum)+ \
			sizeof(POLYGON_DATA)*inInfo->PolygonNum+sizeof(SPLIT_GRID_DATA)+ \
			(GRID_ENTRY_HEADER_SIZE*inInfo->GridNum)+inInfo->TotalLineListSize+ \
			inInfo->TotalPolyIDListSize);
#endif
	
	///GF_ASSERT((offset<=0x8000)&&"高さデータメモリオーバー");
	GF_ASSERT(offset<=0x9000&&"高さデータが大きすぎです");
}

//グリッド分割データをリード
static void ReadGridSpData(FSFile *p_file, MHI_PTR outMap3DInfo)
{
	ReadData(outMap3DInfo->SplitGridData, sizeof(SPLIT_GRID_DATA), p_file);
}
//ヘッダから取得した、頂点数のデータを読む
static void ReadVtxData(FSFile *p_file, MHI_PTR outMap3DInfo, const READ_INFO *inInfo)
{
	ReadData(outMap3DInfo->VertexArray, sizeof(VecFx32)*inInfo->VtxNum, p_file);
}

static void ReadNrmData(FSFile *p_file, MHI_PTR outMap3DInfo, const READ_INFO *inInfo)
{
	ReadData(outMap3DInfo->NormalArray, sizeof(VecFx32)*inInfo->NrmNum, p_file);
}

static void ReadPolygonData(FSFile *p_file, MHI_PTR outMap3DInfo, const READ_INFO *inInfo)
{
	ReadData(outMap3DInfo->PolygonData, sizeof(POLYGON_DATA)*inInfo->PolygonNum, p_file);
}

static void ReadGridDataTbl(FSFile *p_file, MHI_PTR outMap3DInfo, const READ_INFO *inInfo)
{
	ReadData(outMap3DInfo->GridDataTbl, GRID_ENTRY_HEADER_SIZE*inInfo->GridNum, p_file);
}

static void ReadLineDataTbl(FSFile *p_file, MHI_PTR outMap3DInfo, const READ_INFO *inInfo)
{
	ReadData(outMap3DInfo->LineDataTbl, inInfo->TotalLineListSize, p_file);
}

static void ReadGridData(FSFile *p_file, MHI_PTR outMap3DInfo, const READ_INFO *inInfo)
{
	ReadData(outMap3DInfo->PolyIDList, inInfo->TotalPolyIDListSize, p_file);
}

///ARC
//グリッド分割データをリード
static void ReadGridSpDataArc(ARCHANDLE *ioHandle, MHI_PTR outMap3DInfo)
{
	ArchiveDataLoadByHandleContinue(ioHandle, sizeof(SPLIT_GRID_DATA),
									outMap3DInfo->SplitGridData );
}
//ヘッダから取得した、頂点数のデータを読む
static void ReadVtxDataArc(ARCHANDLE *ioHandle, MHI_PTR outMap3DInfo, const READ_INFO *inInfo)
{
	ArchiveDataLoadByHandleContinue(ioHandle, sizeof(VecFx32)*inInfo->VtxNum,
									outMap3DInfo->VertexArray );
}

static void ReadNrmDataArc(ARCHANDLE *ioHandle, MHI_PTR outMap3DInfo, const READ_INFO *inInfo)
{
	ArchiveDataLoadByHandleContinue(ioHandle, sizeof(VecFx32)*inInfo->NrmNum,
									outMap3DInfo->NormalArray );
}

static void ReadPolygonDataArc(ARCHANDLE *ioHandle, MHI_PTR outMap3DInfo, const READ_INFO *inInfo)
{
	ArchiveDataLoadByHandleContinue(ioHandle, sizeof(POLYGON_DATA)*inInfo->PolygonNum,
									outMap3DInfo->PolygonData );
}

static void ReadGridDataTblArc(ARCHANDLE *ioHandle, MHI_PTR outMap3DInfo, const READ_INFO *inInfo)
{
	ArchiveDataLoadByHandleContinue(ioHandle, GRID_ENTRY_HEADER_SIZE*inInfo->GridNum,
									outMap3DInfo->GridDataTbl );
}

static void ReadLineDataTblArc(ARCHANDLE *ioHandle, MHI_PTR outMap3DInfo, const READ_INFO *inInfo)
{
	ArchiveDataLoadByHandleContinue(ioHandle, inInfo->TotalLineListSize,
									outMap3DInfo->LineDataTbl );
}

static void ReadGridDataArc(ARCHANDLE *ioHandle, MHI_PTR outMap3DInfo, const READ_INFO *inInfo)
{
	ArchiveDataLoadByHandleContinue(ioHandle, inInfo->TotalPolyIDListSize,
									outMap3DInfo->PolyIDList );
}

static void HeightDataTask(TCB_PTR _tcb, void * work)
{
	BOOL rc;
	HEIGHT_TASK_DATA	*height_task_data;
	height_task_data = (HEIGHT_TASK_DATA	*)work;
	if (height_task_data->StopFlg == TRUE){
		height_task_data->Seq = /*4*/8;
	}

	switch(height_task_data->Seq){
	case 0:
		FS_InitFile(&height_task_data->file);
		

		height_task_data->OpenIsOK = FS_OpenFile(&height_task_data->file, height_task_data->Path);
		if(!height_task_data->OpenIsOK) {
			OS_Printf("FS_OpenFile(\"%s\") ... ERROR!\n", height_task_data->Path);
			sys_FreeMemoryEz(work);
			TCB_Delete(_tcb);
		}
		ReadHeaderData(&height_task_data->file, &height_task_data->ReadInfo);
#ifdef INVALIED_HEIGHT_MEM_ALOOC
		AllocDataMem(height_task_data->HeightData, &height_task_data->ReadInfo);
#else
#ifdef PM_DEBUG
		{
			u32	fileSize = FS_GetLength(&height_task_data->file);	//ファイルサイズ取得
			
			//サイズ＝確保メモリ-管理ヘッダ
			u32 size = sys_GetMemoryBlockSize((void*)height_task_data->HeightMem)-(0x10);
			if ((fileSize!=0)&&(fileSize<=HEIGHT_HEADER_SIZE)){
				GF_ASSERT( 0 && "HeightDataTask ERROR:ファイルが不正");
			}
			//ファイルサイズから固定ヘッダ（高さ読み込みヘッダ）を引いた分が確保したメモリを超えるかをチェック
			if ((fileSize!=0)&&(fileSize-HEIGHT_HEADER_SIZE>size)){
				OS_Printf("fileSize=%x,allocSize=%x",fileSize,size);
				GF_ASSERT( 0 && "HeightDataTask ERROR:メモリが不足してます");
			}
#ifdef DEBUG_ONLY_FOR_saitou			
			else{
				OS_Printf("local_print fileSize=%x,allocSize=%x",fileSize,size);
			}
#endif
		}
#endif
		SetDataMem(&height_task_data->ReadInfo, height_task_data->HeightData, (void**)&height_task_data->HeightMem);
#endif	//INVALIED_HEIGHT_MEM_ALOOC
		rc = TRUE;
		break;
	case 1:
		//GridSpData(グリッド分割データをリード)
		rc =ReadDataDiv(&height_task_data->file,
				(void**)&height_task_data->HeightData->SplitGridData,
				sizeof(SPLIT_GRID_DATA),
				&height_task_data->DataOffset);
		break;
	case 2:
		//VertexArray(ヘッダから取得した、頂点数のデータをリード)
		rc = ReadDataDiv(&height_task_data->file,
				(void**)&height_task_data->HeightData->VertexArray,
				sizeof(VecFx32)*height_task_data->ReadInfo.VtxNum,
				&height_task_data->DataOffset);
		break;
	case 3:
		//NormalArray(ヘッダから取得した、法線数のデータをリード)
		rc = ReadDataDiv(&height_task_data->file,
				(void**)&height_task_data->HeightData->NormalArray,
				sizeof(VecFx32)*height_task_data->ReadInfo.NrmNum,
				&height_task_data->DataOffset);	
		break;
	case 4:
		//PolygonData(ポリゴンデータをリード)
		rc = ReadDataDiv(&height_task_data->file,
				(void**)&height_task_data->HeightData->PolygonData,
				sizeof(POLYGON_DATA)*height_task_data->ReadInfo.PolygonNum,
				&height_task_data->DataOffset);
		break;
	case 5:
		//GridDataTbl(グリッドのデータをリード)
		rc = ReadDataDiv(&height_task_data->file,
				(void**)&height_task_data->HeightData->GridDataTbl,
				GRID_ENTRY_HEADER_SIZE*height_task_data->ReadInfo.GridNum,
				&height_task_data->DataOffset);
		break;
	case 6:
		//LineDataTbl(ラインデータテーブルをリード)
		rc = ReadDataDiv(&height_task_data->file,
				(void**)&height_task_data->HeightData->LineDataTbl,
				height_task_data->ReadInfo.TotalLineListSize,
				&height_task_data->DataOffset);
		break;
	case 7:
		//PolyIDList(ポリゴンのＩＤリストをリード)
		rc = ReadDataDiv(&height_task_data->file,
				(void**)&height_task_data->HeightData->PolyIDList,
				height_task_data->ReadInfo.TotalPolyIDListSize,
				&height_task_data->DataOffset);
		break;
	case 8:
		if (height_task_data->OpenIsOK == TRUE){
			(void)FS_CloseFile( &height_task_data->file );
		}

//		height_task_data->HeightData->LoadOK = TRUE;
		*height_task_data->EndFlg = 0;
	
		sys_FreeMemoryEz((void *)work);
		TCB_Delete(_tcb);
		return;
	}
	 
	if (rc == TRUE){
		height_task_data->Seq++;
		if(height_task_data->Seq == 8){
			height_task_data->HeightData->DataValid = TRUE;		//データ有効
		}
	}
}

#define HEIGHT_END_SEQ	(2)

static void HeightDataArcTask(TCB_PTR _tcb, void * work)
{
	BOOL rc;
	HEIGHT_TASK_DATA	*height_task_data;
	height_task_data = (HEIGHT_TASK_DATA	*)work;
	if (height_task_data->StopFlg == TRUE){
		height_task_data->Seq = HEIGHT_END_SEQ;
	}

	switch(height_task_data->Seq){
	case 0:
		if (*height_task_data->Counter){
			rc = FALSE;
			break;
		}

		ReadHeaderDataArc(height_task_data->ArcHandle, &height_task_data->ReadInfo);
/**		
#ifdef PM_DEBUG
		{
			u32	fileSize = FS_GetLength(&height_task_data->file);	//ファイルサイズ取得
			
			//サイズ＝確保メモリ-管理ヘッダ
			u32 size = sys_GetMemoryBlockSize((void*)height_task_data->HeightMem)-(0x10);
			if ((fileSize!=0)&&(fileSize<=HEIGHT_HEADER_SIZE)){
				GF_ASSERT( 0 && "HeightDataTask ERROR:ファイルが不正");
			}
			//ファイルサイズから固定ヘッダ（高さ読み込みヘッダ）を引いた分が確保したメモリを超えるかをチェック
			if ((fileSize!=0)&&(fileSize-HEIGHT_HEADER_SIZE>size)){
				OS_Printf("fileSize=%x,allocSize=%x",fileSize,size);
				GF_ASSERT( 0 && "HeightDataTask ERROR:メモリが不足してます");
			}
#ifdef DEBUG_ONLY_FOR_saitou			
			else{
				OS_Printf("local_print fileSize=%x,allocSize=%x",fileSize,size);
			}
#endif
		}
#endif
*/
		SetDataMem(&height_task_data->ReadInfo, height_task_data->HeightData, (void**)&height_task_data->HeightMem);

		rc = TRUE;
		break;
	case 1:
		ReadGridSpDataArc(height_task_data->ArcHandle,height_task_data->HeightData);
		ReadVtxDataArc(height_task_data->ArcHandle,height_task_data->HeightData, &height_task_data->ReadInfo);
		ReadNrmDataArc(height_task_data->ArcHandle,height_task_data->HeightData, &height_task_data->ReadInfo);
		ReadPolygonDataArc(height_task_data->ArcHandle,height_task_data->HeightData, &height_task_data->ReadInfo);
		ReadGridDataTblArc(height_task_data->ArcHandle,height_task_data->HeightData, &height_task_data->ReadInfo);
		ReadLineDataTblArc(height_task_data->ArcHandle,height_task_data->HeightData, &height_task_data->ReadInfo);
		ReadGridDataArc(height_task_data->ArcHandle,height_task_data->HeightData, &height_task_data->ReadInfo);
		rc = TRUE;
		break;
/**		
	case 1:
		//GridSpData(グリッド分割データをリード)
		rc =ReadArcDataDiv(height_task_data->ArcHandle,
				(void**)&height_task_data->HeightData->SplitGridData,
				sizeof(SPLIT_GRID_DATA),
				&height_task_data->DataOffset);
		break;
	case 2:
		//VertexArray(ヘッダから取得した、頂点数のデータをリード)
		rc = ReadArcDataDiv(height_task_data->ArcHandle,
				(void**)&height_task_data->HeightData->VertexArray,
				sizeof(VecFx32)*height_task_data->ReadInfo.VtxNum,
				&height_task_data->DataOffset);
		break;
	case 3:
		//NormalArray(ヘッダから取得した、法線数のデータをリード)
		rc = ReadArcDataDiv(height_task_data->ArcHandle,
				(void**)&height_task_data->HeightData->NormalArray,
				sizeof(VecFx32)*height_task_data->ReadInfo.NrmNum,
				&height_task_data->DataOffset);	
		break;
	case 4:
		//PolygonData(ポリゴンデータをリード)
		rc = ReadArcDataDiv(height_task_data->ArcHandle,
				(void**)&height_task_data->HeightData->PolygonData,
				sizeof(POLYGON_DATA)*height_task_data->ReadInfo.PolygonNum,
				&height_task_data->DataOffset);
		break;
	case 5:
		//GridDataTbl(グリッドのデータをリード)
		rc = ReadArcDataDiv(height_task_data->ArcHandle,
				(void**)&height_task_data->HeightData->GridDataTbl,
				GRID_ENTRY_HEADER_SIZE*height_task_data->ReadInfo.GridNum,
				&height_task_data->DataOffset);
		break;
	case 6:
		//LineDataTbl(ラインデータテーブルをリード)
		rc = ReadArcDataDiv(height_task_data->ArcHandle,
				(void**)&height_task_data->HeightData->LineDataTbl,
				height_task_data->ReadInfo.TotalLineListSize,
				&height_task_data->DataOffset);
		break;
	case 7:
		//PolyIDList(ポリゴンのＩＤリストをリード)
		rc = ReadArcDataDiv(height_task_data->ArcHandle,
				(void**)&height_task_data->HeightData->PolyIDList,
				height_task_data->ReadInfo.TotalPolyIDListSize,
				&height_task_data->DataOffset);
		break;
*/		
	case HEIGHT_END_SEQ:
		*height_task_data->EndFlg = 0;
		sys_FreeMemoryEz((void *)work);
		TCB_Delete(_tcb);
		return;
	}
	if (rc == TRUE){
		height_task_data->Seq++;
		if(height_task_data->Seq == HEIGHT_END_SEQ){
			height_task_data->HeightData->DataValid = TRUE;		//データ有効
		}
	}
}

#ifdef	INVALIED_HEIGHT_MEM_ALOOC

static void FreeMHIMember(MHI_PTR outMap3DInfo)
{
	//頂点データ
	if (outMap3DInfo->VertexArray != NULL){
		sys_FreeMemoryEz(outMap3DInfo->VertexArray);
		outMap3DInfo->VertexArray = NULL;
	}
	//法線データ
	if (outMap3DInfo->NormalArray != NULL){
		sys_FreeMemoryEz(outMap3DInfo->NormalArray);
		outMap3DInfo->NormalArray = NULL;
	}
	//ポリゴンデータ
	if (outMap3DInfo->PolygonData != NULL){
		sys_FreeMemoryEz(outMap3DInfo->PolygonData);
		outMap3DInfo->PolygonData = NULL;
	}
	//グリッド分割データ
	if (outMap3DInfo->SplitGridData != NULL){
		sys_FreeMemoryEz(outMap3DInfo->SplitGridData);
		outMap3DInfo->SplitGridData = NULL;	
	}
	//グリッドテーブルデータ
	if (outMap3DInfo->GridDataTbl != NULL){
		sys_FreeMemoryEz(outMap3DInfo->GridDataTbl);
		outMap3DInfo->GridDataTbl = NULL;
	}
	//ラインテーブルデータ
	if (outMap3DInfo->LineDataTbl != NULL){
		sys_FreeMemoryEz(outMap3DInfo->LineDataTbl);
		outMap3DInfo->LineDataTbl = NULL;
	}
	//グリッド実データ
	if (outMap3DInfo->PolyIDList != NULL){
		sys_FreeMemoryEz(outMap3DInfo->PolyIDList);
		outMap3DInfo->PolyIDList = NULL;
	}
}
#endif //INVALIED_HEIGHT_MEM_ALOOC

////////////////////////////////////////////////////////////////////////////////////////
MHI_PTR	AllocMapHeightInfo(void)
{
	MHI_PTR ptr;
	ptr = sys_AllocMemory(HEAPID_FIELD,sizeof(MAP_HEIGHT_INFO));
	ptr->VertexArray = NULL;
	ptr->NormalArray = NULL;
	ptr->PolygonData = NULL;
	ptr->SplitGridData = NULL;	
	ptr->GridDataTbl = NULL;
	ptr->LineDataTbl = NULL;
	ptr->PolyIDList = NULL;
	return ptr;
}

void SetupHeightData(const char  *path, MHI_PTR outMapHeightInfo, u8 * inHeightMem)
{
	FSFile  file;
    BOOL    open_is_ok;
    FS_InitFile(&file);
    open_is_ok = FS_OpenFile(&file, path);
    if(open_is_ok) {
        char    buf[256];
		READ_INFO *read_info;
		//一時メモリ確保
		read_info = sys_AllocMemory(HEAPID_FIELD,sizeof(READ_INFO));
		ReadHeaderData(&file,read_info);
#ifdef INVALIED_HEIGHT_MEM_ALOOC
		AllocDataMem(outMapHeightInfo, read_info);

#else
#ifdef PM_DEBUG
		{
			u32	fileSize = FS_GetLength(&file);	//ファイルサイズ取得
			//サイズ＝確保メモリ-管理ヘッダ
			u32 size = sys_GetMemoryBlockSize((void*)inHeightMem)-(0x10);
			if ((fileSize!=0)&&(fileSize<=HEIGHT_HEADER_SIZE)){
				GF_ASSERT( 0 && "SetupHeightData ERROR:ファイルが不正");
			}
			//ファイルサイズから固定ヘッダ（高さ読み込みヘッダ）を引いた分が確保したメモリを超えるかをチェック
			if ((fileSize!=0)&&(fileSize-HEIGHT_HEADER_SIZE>size)){
				OS_Printf("fileSize=%x,allocSize=%x",fileSize,size);
				GF_ASSERT( 0 && "SetupHeightData ERROR:メモリが不足してます");
			}

		}
#endif
		SetDataMem(read_info, outMapHeightInfo, (void **)&inHeightMem);
#endif	//#ifdef INVALIED_HEIGHT_MEM_ALOOC
		
		ReadGridSpData(&file,outMapHeightInfo);
		ReadVtxData(&file,outMapHeightInfo, read_info);
		ReadNrmData(&file,outMapHeightInfo, read_info);
		ReadPolygonData(&file,outMapHeightInfo, read_info);
		ReadGridDataTbl(&file,outMapHeightInfo, read_info);
		ReadLineDataTbl(&file,outMapHeightInfo, read_info);
		ReadGridData(&file,outMapHeightInfo, read_info);

		//一時メモリ解放
		sys_FreeMemoryEz(read_info);

		(void)FS_CloseFile( &file );

//		outMapHeightInfo->LoadOK = TRUE;
		outMapHeightInfo->DataValid = TRUE;		//データ有効
	}else{
		OS_Printf("FS_OpenFile(\"%s\") ... ERROR!\n", path);
	}
}

void SetupHeightDataArc(ARCHANDLE *ioHandle,
						const int inDataSize,
						MHI_PTR outMapHeightInfo, u8 * inHeightMem)
{
    if(1) {
        char    buf[256];
		READ_INFO *read_info;
		//一時メモリ確保
		read_info = sys_AllocMemoryLo(HEAPID_FIELD,sizeof(READ_INFO));

		//アーカイブデータ取得
		ReadHeaderDataArc(ioHandle, read_info);
#ifdef PM_DEBUG
		{
			//サイズ＝確保メモリ-管理ヘッダ
			u32 size = sys_GetMemoryBlockSize((void*)inHeightMem)-(0x10);
			if ((inDataSize!=0)&&(inDataSize<=HEIGHT_HEADER_SIZE)){
				GF_ASSERT( 0 && "SetupHeightData ERROR:ファイルが不正");
			}
			//ファイルサイズから固定ヘッダ（高さ読み込みヘッダ）を引いた分が確保したメモリを超えるかをチェック
			if ((inDataSize!=0)&&(inDataSize-HEIGHT_HEADER_SIZE>size)){
				OS_Printf("fileSize=%x,allocSize=%x",inDataSize,size);
				GF_ASSERT( 0 && "SetupHeightData ERROR:メモリが不足してます");
			}

		}
#endif
		SetDataMem(read_info, outMapHeightInfo, (void **)&inHeightMem);
		
		ReadGridSpDataArc(ioHandle,outMapHeightInfo);
		ReadVtxDataArc(ioHandle,outMapHeightInfo, read_info);
		ReadNrmDataArc(ioHandle,outMapHeightInfo, read_info);
		ReadPolygonDataArc(ioHandle,outMapHeightInfo, read_info);
		ReadGridDataTblArc(ioHandle,outMapHeightInfo, read_info);
		ReadLineDataTblArc(ioHandle,outMapHeightInfo, read_info);
		ReadGridDataArc(ioHandle,outMapHeightInfo, read_info);

		//一時メモリ解放
		sys_FreeMemoryEz(read_info);

		outMapHeightInfo->DataValid = TRUE;		//データ有効
	}
}



void FreeMapHeightInfo(MHI_PTR outMap3DInfo)
{
	if (outMap3DInfo == NULL)
	{
		return;
	}
#ifdef	INVALIED_HEIGHT_MEM_ALOOC
	FreeMHIMember(outMap3DInfo);
#endif //INVALIED_HEIGHT_MEM_ALOOC
	sys_FreeMemoryEz(outMap3DInfo);
	outMap3DInfo = NULL;
}

void SetInvalidHeightData(MHI_PTR outMap3DInfo)
{
	if (outMap3DInfo == NULL){
		return;
	}
	outMap3DInfo->DataValid = FALSE;		//データ無効
#ifdef	INVALIED_HEIGHT_MEM_ALOOC
	FreeMHIMember(outMap3DInfo);
#else
	//頂点データ
	outMap3DInfo->VertexArray = NULL;
	//法線データ
	outMap3DInfo->NormalArray = NULL;
	//ポリゴンデータ
	outMap3DInfo->PolygonData = NULL;
	//グリッド分割データ
	outMap3DInfo->SplitGridData = NULL;	
	//グリッドテーブルデータ
	outMap3DInfo->GridDataTbl = NULL;
	//ラインテーブルデータ
	outMap3DInfo->LineDataTbl = NULL;
	//グリッド実データ
	outMap3DInfo->PolyIDList = NULL;
#endif //INVALIED_HEIGHT_MEM_ALOOC
}
/*
TCB_PTR SetupHeightDataTask(const char  *path,
		MHI_PTR ioMap3DInfo,
		int *inEndFlg,
		u8 **inHeightMem)
{
	TCB_PTR _tcb;
	HEIGHT_TASK_DATA *height_task_data;
	height_task_data = sys_AllocMemory(HEAPID_FIELD,sizeof(HEIGHT_TASK_DATA));
	if (height_task_data == NULL){
		OS_Printf("No_mem\n");
	}
	height_task_data->Seq = 0;
	sprintf(height_task_data->Path,path);
	height_task_data->HeightData = ioMap3DInfo;
	height_task_data->EndFlg = inEndFlg;
	height_task_data->StopFlg = FALSE;
	height_task_data->OpenIsOK = FALSE;
//	ioMap3DInfo->LoadOK = FALSE;
	height_task_data->DataOffset = 0;
	height_task_data->HeightMem = *inHeightMem;

	_tcb = TCB_Add(HeightDataTask,(void*)height_task_data,1);
	return _tcb;
}
*/
TCB_PTR SetupHeightDataArcTask(	ARCHANDLE *inHandle,
								const int inDataSize,
								MHI_PTR ioMap3DInfo,
								int *inEndFlg,
								u8 **inHeightMem,
								int *inCounter)
{
	TCB_PTR _tcb;
	HEIGHT_TASK_DATA *height_task_data;
	height_task_data = sys_AllocMemoryLo(HEAPID_FIELD,sizeof(HEIGHT_TASK_DATA));
	if (height_task_data == NULL){
		OS_Printf("No_mem\n");
	}
	height_task_data->Seq = 0;
	height_task_data->ArcHandle = inHandle;
	height_task_data->DataSize = inDataSize;
	height_task_data->HeightData = ioMap3DInfo;
	height_task_data->EndFlg = inEndFlg;
	height_task_data->StopFlg = FALSE;
	height_task_data->OpenIsOK = FALSE;
	height_task_data->DataOffset = 0;
	height_task_data->HeightMem = *inHeightMem;
	height_task_data->Counter = inCounter;
	
	_tcb = TCB_Add(HeightDataArcTask,(void*)height_task_data,1);
	return _tcb;
}

void StopHeightLoadTaskRequest(TCB_PTR tcb)
{
	HEIGHT_TASK_DATA *height_task_data;
	height_task_data = (HEIGHT_TASK_DATA*)TCB_GetWork(tcb);
	height_task_data->StopFlg = TRUE;
}



void InitHeightData(MHI_PTR outData)
{
//	outData->LoadOK = FALSE;
	outData->DataValid = FALSE;
}

BOOL GetInvalidHeightDataFlg(MHI_CONST_PTR inMap3DInfo)
{
	return inMap3DInfo->DataValid;
}
