//============================================================================================
/**
 * @file	div_map.c
 * @brief	分割マップ
 * @author	Nozomu Saito
 * @date	2005.05.06
 */
//============================================================================================
#include "common.h"
#include "div_map_cont_def.h"
#include "fieldsys.h"
#include "worldmap.h"	//<<20060113add
#include "fieldmap_mem.h"
//#include "sp_attribute_def.h"

#include "debug_saito.h"
#include "fld_debug.h"

#include "system/arc_tool.h"
#include "communication/communication.h" // 通信エラー関係

#define BLOCK_GRID_SIZE_X	(BLOCK_GRID_W)	//1ブロックの横グリッド数
#define BLOCK_GRID_SIZE_Z	(BLOCK_GRID_H)	//1ブロックの縦グリッド数

#define HARF_GRID_SIZE	(ONE_GRID_SIZE/2)
#define NON_BLOCK	(-1)

#define MODEL_SET_DIV_SIZE	( 0xe000 )
#define MAP_ARC_NO_DATA		( 0xffff )

#define DIV_CALL_BACK

enum {
	MODELSET_TASK_SEQ_INIT = 0,
	MODELSET_TASK_SEQ_MODEL_LOAD,
	MODELSET_TASK_SEQ_TEXTURE_BIND,
	MODELSET_TASK_SEQ_RESOUCE_SET,
	MODELSET_TASK_SEQ_RENDER_OBJ,
	MODELSET_TASK_SEQ_EXIT
};

typedef struct DIV_FUNC_LIST_tag const * DFL_CONST_PTR;

typedef struct MAP_LOAD_TASK_COUNTER_tag
{
	int BlockLoadTaskCounter;
	int BlockHeightLoadTaskCounter;
	
}MAP_LOAD_TASK_COUNTER;

//ブロックリストデータ
typedef struct BLOCK_NODE_tag{
	u16 Attribute[32*32];
	NNSG3dRenderObj		FloorData;
	NNSG3dResFileHeader	*FloorResFile;
	u8				*HeightMem;
	MHI_PTR			MapHeightInfo;
	int BlockIndex;
	BOOL DrawOKFlg;
	M3DOL_PTR	ObjDataList;
}BLOCK_NODE;

typedef struct MAP_LOAD_BLOCK_ST_tag
{
	BLOCK_NODE *Node[2];
	
	TCB_PTR	RandTask;		//地形ロードタスクポインタ
	TCB_PTR	HeightTask;		//高さロードタスクポインタ
	MAP_LOAD_TASK_COUNTER	TaskCnter;	//地形ロードタスク、高さロードタスクのカウンタ
	int Block[2];
	u8 Index[2];

	u8 TotalCount;
	BOOL BlockLoadOK;
	
}MAP_LOAD_BLOCK_ST;

typedef void (*DIV_FIRST_FUNC)(	DMC_PTR outDivMapCont,
								const int inGridX, 
								const int inGridZ,
								const int inMapGridW);
typedef void (*DIV_LOAD_FUNC)(	const u8 inCount,
								const MAP_RESOURCE_PTR inMapResource,
								const WORLD_MAP_PTR inWorld,
								const int inMapW,
								const int inMapH,
								DMC_PTR inDivMapCont,
								MAP_LOAD_BLOCK_ST *ioMLBS);


typedef struct DIV_FUNC_LIST_tag{
	DIV_FIRST_FUNC	DivFirstFunc;
	DIV_LOAD_FUNC	DivLoadFunc;
}DIV_FUNC_LIST;

typedef struct BLOCK_LOAD_tag
{
	MAP_LOAD_BLOCK_ST	MLBS;
	BOOL	Moving;		//稼動中フラグ
	u8		LoadDir;	//ロード方向
}MAP_LOAD_BLOCK_CONT;

typedef struct STOCK_LOAD_DATA_tag
{
	BLOCK_NODE *Node[2];
	BOOL	Valid;
	u8		LoadDir;	//ロード方向
	int Block[2];
	u8 Index[2];
}STOCK_LOAD_DATA;

typedef struct DIV_MAP_CHECK_tag
{
	VecFx32 OldPoint;
	VecFx32 const *TargetPoint;
	fx32 const *LargeVal;
	fx32 const *SmallVal;
	BOOL Moving;
	u8 Dir;
	BOOL Valid;
}DIV_MAP_CHECK;

typedef struct DIV_MAP_LOAD_CONT_tag
{
	FMM_PTR FldMapMem;
	MAP_LOAD_BLOCK_CONT MLBC[2];		//ロードリクエスト管理データ
	STOCK_LOAD_DATA Stock;				//ロードリクエストストック
	BOOL LocalFreeIndexTable[4];		//解放予約テーブル
	BLOCK_NODE *BlockNodeList[4];		//自機の周りの4ブロックのデータへのポインタ

	u8 MovingNum;	//稼動数
	u8 BlankNo;			//0or1			ロードリクエスト管理空き番号
	u8 NowMovingNo;		//0or1			ロードリクエスト管理番号
	u32 NowBlockIndex;		
	u32 NowGridNo;				//現0の自機グリッドナンバー
	u8 NowLocalIndex;			//現在ローカルインデックス
	u8 NowPosInBlock;	//0～3
	BOOL FreeRequest;
	int LoadSeq;
	MAP_RESOURCE_PTR MapResource;
	WORLD_MAP_PTR World;
	//下記3つの変数はworld構造体のポインタから取得可能ですが、アクセスが頻繁に発生するため、
	//初期化の段階でここに値を格納し、これを使います。
	//この変数の値はマップが切り替わらない限り変更はありません。(書き換えを行わない)
	int MapW;
	int MapH;
	int MapGridW;

	DIV_MAP_CHECK MapCheck;
	FLD_3D_ANM_MNG_PTR Field3DAnmPtr;
	DFL_CONST_PTR	FuncList;
	ARCHANDLE *ArcHandle;		//アーカイブハンドル
#ifdef DIV_CALL_BACK
	//コールバック関数
	DIV_LOAD_CALL_BACK CallBack;
	//コールバックワーク
	void *CallBackWork;
#endif	
}DIV_MAP_LOAD_CONT;

typedef struct DATA_OFS_SIZE_tsg
{
	int AttrSize;
	int MapSize;
	int HeightSize;
	int ObjSize;
}DATA_OFS_SIZE;

#ifdef PM_DEBUG
static BOOL DebugOutRangeFlg = TRUE;
#endif


//////////////////////////////////////////////////////////////////////////////////
//	前方宣言
//////////////////////////////////////////////////////////////////////////////////
static TCB_PTR Set3DModelTask(	ARCHANDLE *inHandle,
								const int inSize,
								NNSG3dRenderObj* object_p,
								NNSG3dResFileHeader** resFile,
								NNSG3dResTex* pTexture,
								BOOL *ioDrawOKFlg,
								int *inEndFlg);
static NNSG3dResMdl* Set3DModel(	ARCHANDLE *ioHandle,
									const int inSize,
									NNSG3dRenderObj* object_p,
									NNSG3dResFileHeader** resFile,
									NNSG3dResTex* pTexture);
static void StopMapLoadTaskRequest(TCB_PTR tcb);
static void InitMapLoadCont(DMC_PTR outDivMapCont);
static void LoadFirstBlock(	DMC_PTR outDivMapCont,
							const int inGridX, 
							const int inGridZ,
							const int inMapGridW);
static void LoadFirstBlockForUnder(	DMC_PTR outDivMapCont,
									const int inGridX, 
									const int inGridZ,
									const int inMapGridW);
static void AllocBlockList(DMC_PTR outDivMapCont);
static void AllocBlockListForUnder(DMC_PTR outDivMapCont);
static void	LoadStopReqest(DMC_PTR ioDivMapCont,const u8 inNo);
static BOOL BlockLoadReqest( DMC_PTR ioDivMapCont,
								const int inBlock1,
								const int inBlock2,
								const u8 inIdx1,
								const u8 inIdx2,
								const u8 inBlankNo,
								const u8 inDir);
static void GetMapArcLoadOffset(ARCHANDLE *ioHandle, const int inArcIndex, DATA_OFS_SIZE *outData);
static void LoadBlock(const u8 inCount,
		const MAP_RESOURCE_PTR inMapResource,
		const WORLD_MAP_PTR inWorld,
		const int inMapW,
		const int inMapH,
		DMC_PTR inDivMapCont,
		MAP_LOAD_BLOCK_ST *ioMLBS);
static void LoadBlockForUnder(const u8 inCount,
		const MAP_RESOURCE_PTR inMapResource,
		const WORLD_MAP_PTR inWorld,
		const int inMapW,
		const int inMapH,
		DMC_PTR inDivMapCont,
		MAP_LOAD_BLOCK_ST *ioMLBS);
static void LoadBlockQuick(	const int inBlockIndex,
							const u8 inLocalIndex,
							const MAP_RESOURCE_PTR inMapResource,
							const WORLD_MAP_PTR inWorld,
							const int inMapW,
							const int inMapH,
							const BOOL inLightValid,
							DMC_PTR outDivMapCont);
static void LoadBlockQuickForUnder(	const int inBlockIndex,
									const u8 inLocalIndex,
									const MAP_RESOURCE_PTR inMapResource,
									const WORLD_MAP_PTR inWorld,
									const int inMapW,
									const int inMapH,
									const BOOL inLightValid,
									DMC_PTR outDivMapCont);
static void UpdateBlockList(const int inBlockIndex, const u8 inDirection, DMC_PTR ioDivMapCont);
static void FreeAndMoveNode(const u8 inFreeNo1,
							const u8 inFreeNo2,
							const u8 inMoveNo1,
							const u8 inMoveNo2,
							DMC_PTR ioDivMapCont);
static void FreeBlock(const u8 inLocalIndex, DMC_PTR outDivMapCont);

static void DrawBlock(	const u8 inLocalIndex,
						DMC_CONST_PTR inDivMapCont,
						const GLST_DATA_PTR	glst_data);
static BOOL CompLoadDirection(const u8 inDir, DMC_CONST_PTR inDivMapCont, u8* outNo);
static BOOL BlockLoadReqestForStock(DMC_PTR ioDivMapCont);
static BOOL IsFinishedLoadBlock(DMC_CONST_PTR inDivMapCont);
static void ClearLocalFreeIndexTable(DMC_PTR outDivMapCont);
static void MarkLocalFreeIndexTableByDir(const u8 inDir,DMC_PTR outDivMapCont);



static u8 CalcLocalIdxFromPosInBlock(const u8 inPosInBlock);
static u32 GetNextGridNo(	const u8 inDirection,
							const int inMapH,
							const int inMapGridW,
							const int inNowGridNo);

static u8 GetNextPosInBlock(const u8 inDirection, const int inNowPosInBlock);
static void UpdateNowLocalIndexForAfterLoad(const u8 inDirection,
											const int inNowPosInBlock,
											u8 *outNowLocalIndex);

static void AddMapLoad(const int inBlock1,
					const int inBlock2,
					const u8 inIdx1,
					const u8 inIdx2,
					const u8 inDir,
					DMC_PTR ioDivMapCont);
static int CalcGridNoFromGridXZ(const int inGridX, const int inGridZ, const int inMapGridW);
static void AddMapLoadForStock(DMC_PTR ioDivMapCont);
							
static void UpdateNowData(const int inGridX, const int inGridZ, DMC_PTR outDivMapCont);
static void CalcMapOffset3D(	const int inBlockIndex,
								const int inMapW,
								const WORLD_MAP_PTR inWorld,
								VecFx32 *outTrans);

///////////////////////////////////////////////////////
//	スタティック変数
///////////////////////////////////////////////////////

static const DIV_FUNC_LIST DivGroundFunc = 
{
	LoadFirstBlock,
	LoadBlock
};

static const DIV_FUNC_LIST DivUnderFunc = 
{
	LoadFirstBlockForUnder,
	LoadBlockForUnder
};

//--------------------------------------------------------------------------------------------
/**
 * 整合性チェック縦
 *
 * @param	inBlockIdx1		ブロックインデックス1
 * @param	inBlockIdx2		ブロックインデックス2
 * @param	inMapW			マップ幅
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static BOOL CheckColumnBlockIndex(const int inBlockIdx1,
								const int inBlockIdx2,
								const int inMapW)
{
	if (inBlockIdx1%inMapW != inBlockIdx2%inMapW){
		return FALSE;
	}else{
		return TRUE;
	}
}

//--------------------------------------------------------------------------------------------
/**
 * 整合性チェック横
 *
 * @param	inBlockIdx1		ブロックインデックス1
 * @param	inBlockIdx2		ブロックインデックス2
 * @param	inMapW			マップ幅
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static BOOL CheckRowBlockIndex(const int inBlockIdx1,
								const int inBlockIdx2,
								const int inMapW)
{
	if (inBlockIdx1/inMapW != inBlockIdx2/inMapW){
		return FALSE;
	}else{
		return TRUE;
	}
}

//--------------------------------------------------------------------------------------------
/**
 * ロードタスクのナンバー(0or1)を使用したタスク停止リクエスト
 *
 * @param	ioDivMapCont	分割マップ構造体ポインタ
 * @param	inNo			中止リクエストナンバー（0ＯＲ1）
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void	LoadStopReqest(DMC_PTR ioDivMapCont,const u8 inNo)
{
	u8 idx;
	u8 i;

	if (ioDivMapCont->MLBC[inNo].MLBS.TaskCnter.BlockLoadTaskCounter != 0){
		//地形データロード中止リクエスト
		StopMapLoadTaskRequest(ioDivMapCont->MLBC[inNo].MLBS.RandTask);
#ifdef DIV_MAP_LOAD_DEBUG		
		OS_Printf("地形解放\n");
#endif		
	}
	if (ioDivMapCont->MLBC[inNo].MLBS.TaskCnter.BlockHeightLoadTaskCounter != 0){
		//高さデータロード中止リクエスト
		StopHeightLoadTaskRequest(ioDivMapCont->MLBC[inNo].MLBS.HeightTask);
#ifdef DIV_MAP_LOAD_DEBUG
		OS_Printf("高さ解放\n");
#endif
	}
	ioDivMapCont->MLBC[inNo].MLBS.BlockLoadOK = TRUE;
#if 0
	//アーカイブハンドルを解放
	if (ioDivMapCont->ArcHandle != NULL){
		ArchiveDataHandleClose( ioDivMapCont->ArcHandle );
		ioDivMapCont->ArcHandle = NULL;
	}
#endif	
}

//--------------------------------------------------------------------------------------------
/**
 * ブロックデータを使用した、タスクの停止リクエスト
 *
 * @param	*inMLBS		ロードブロックデータ
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void	LoadTaskStopReqestByMLBS(MAP_LOAD_BLOCK_ST *inMLBS)
{
	if (inMLBS->TaskCnter.BlockLoadTaskCounter != 0){
		//地形データロード中止リクエスト
		StopMapLoadTaskRequest(inMLBS->RandTask);
	}
	if (inMLBS->TaskCnter.BlockHeightLoadTaskCounter != 0){
		//高さデータロード中止リクエスト
		StopHeightLoadTaskRequest(inMLBS->HeightTask);
	}

	//次のタスクがすぐに回るように、ここでカウンタをクリアしておく
	inMLBS->TaskCnter.BlockLoadTaskCounter = 0;
	inMLBS->TaskCnter.BlockHeightLoadTaskCounter = 0;
	
	//inMLBS->StopFlg = TRUE;
}

//--------------------------------------------------------------------------------------------
/**
 * 初期ブロックをグリッドから割り出す
 *
 * @param	inGridX			グリッドＸ座標
 * @param	inGridZ			グリッドＺ座標
 * @param	inMapW			マップ横幅
 * @param	inMapH			マップ縦幅
 * @param	inMapGridW		マップグリッド幅
 * @param	*outBlockTbl	初期ブロックテーブル
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void MakeStartBlockTbl(	const int inGridX,
								const int inGridZ,
								const int inMapW,
								const int inMapH,
								const int inMapGridW,
								int *outBlockTbl)
{
	int grid_no;
	u8 pos_in_block;
	int block_index;
	int block_w, block_h;
	//4ブロックの左上のインデックスを算出
	block_w = (inGridX / BLOCK_GRID_SIZE_X);
	block_h = (inGridZ / BLOCK_GRID_SIZE_Z);

	grid_no = CalcGridNoFromGridXZ(inGridX,inGridZ,inMapGridW);
	pos_in_block = CalcPositionInBlockFromGridNo(grid_no,inMapGridW);

	block_index = (block_h*inMapW)+block_w;
	
	switch(pos_in_block){
	case 0:		//左上
		//自分はローカル3
		outBlockTbl[3] = block_index;
		outBlockTbl[0] = block_index-inMapW-1;
		outBlockTbl[1] = block_index-inMapW;
		outBlockTbl[2] = block_index-1;
		//左隣のブロックを調べる
		if(block_w-1<0){
			//左は範囲外
			//その上も範囲外のはず
			outBlockTbl[0] = NON_BLOCK;
			outBlockTbl[2] = NON_BLOCK;
		}
		//上のブロックを調べる
		if(block_h-1<0){
			//上は範囲外
			outBlockTbl[1] = NON_BLOCK;
		}
///		block_w--;
///		block_h--;
		break;
	case 1:		//右上
		//自分はローカル2
		outBlockTbl[2] = block_index;
		outBlockTbl[0] = block_index-inMapW;
		outBlockTbl[1] = block_index-inMapW+1;
		outBlockTbl[3] = block_index+1;
		//右隣のブロックを調べる
		if(block_w+1>=inMapW){
			//右は範囲外
			//その上も範囲外のはず
			outBlockTbl[1] = NON_BLOCK;
			outBlockTbl[3] = NON_BLOCK;
		}
		//上のブロックを調べる
		if(block_h-1<0){
			//上は範囲外
			outBlockTbl[0] = NON_BLOCK;
		}
///		block_h--;
		break;
	case 2:		//左下
		//自分はローカル1
		outBlockTbl[1] = block_index;
		outBlockTbl[0] = block_index-1;
		outBlockTbl[2] = block_index+inMapW-1;
		outBlockTbl[3] = block_index+inMapW;
		//左隣のブロックを調べる
		if(block_w-1<0){
			//左は範囲外
			//その下も範囲外のはず
			outBlockTbl[0] = NON_BLOCK;
			outBlockTbl[2] = NON_BLOCK;
		}
		//下のブロックを調べる
		if(block_h+1>inMapH){
			//下は範囲外
			outBlockTbl[3] = NON_BLOCK;
		}
///		block_w--;
		break;
	case 3:		//右下
		//自分はローカル0
		outBlockTbl[0] = block_index;
		outBlockTbl[1] = block_index+1;
		outBlockTbl[2] = block_index+inMapW;
		outBlockTbl[3] = block_index+inMapW+1;
		//右隣のブロックを調べる
		if(block_w+1>=inMapW){
			//右は範囲外
			//その下も範囲外のはず
			outBlockTbl[1] = NON_BLOCK;
			outBlockTbl[3] = NON_BLOCK;
		}
		//下のブロックを調べる
		if(block_h+1>inMapH){
			//下は範囲外
			outBlockTbl[0] = NON_BLOCK;
		}
		break;
	default:
		GF_ASSERT(0&&"ERROR:POS_IN_BLOCK");
	}
	
#ifdef DEBUG_ONLY_FOR_saitou
	OS_Printf("local_print block_wh=%d,%d\n",block_w,block_h);
	OS_Printf("local_print start_blocks=%d,%d,%d,%d\n",
			outBlockTbl[0],outBlockTbl[1],outBlockTbl[2],outBlockTbl[3]);
#endif //DEBUG_ONLY_FOR_saitou	
}

//--------------------------------------------------------------------------------------------
/**
 * 4ブロック分のメモリ確保
 *
 * @param	outDivMapCont	分割マップ構造体ポインタ
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void AllocBlockList(DMC_PTR outDivMapCont)
{
	u8 i;
	for (i=0;i<4;i++){
		BLOCK_NODE *node = NULL;
		node = sys_AllocMemory( HEAPID_FIELD, sizeof(BLOCK_NODE) );
		outDivMapCont->BlockNodeList[i] = node;
		outDivMapCont->BlockNodeList[i]->DrawOKFlg = FALSE;

		//確保したメモリ(地形)とポインタをバインド
		BindGroundMem(i, outDivMapCont->FldMapMem, (void**)&(outDivMapCont->BlockNodeList[i]->FloorResFile));
		BindHeightMem(i, outDivMapCont->FldMapMem, (void**)&(outDivMapCont->BlockNodeList[i]->HeightMem));

		//3DOBJのアロケーション
		outDivMapCont->BlockNodeList[i]->ObjDataList =  M3DO_AllocMap3DObjList(HEAPID_FIELD);
		outDivMapCont->BlockNodeList[i]->BlockIndex = NON_BLOCK;
		//アトリビュートクリア
		MI_CpuFillFast(outDivMapCont->BlockNodeList[i]->Attribute, 0xffffffff, 2*32*32 );
	}
	
	//BlockNodeList = sys_AllocMemory( HEAPID_FIELD, sizeof(BLOCK_NODE)*9 );
}

//--------------------------------------------------------------------------------------------
/**
 * 4ブロック分のメモリ確保（地下）
 *
 * @param	outDivMapCont	分割マップ構造体ポインタ
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void AllocBlockListForUnder(DMC_PTR outDivMapCont)
{
	u8 i;
	for (i=0;i<4;i++){
		BLOCK_NODE *node = NULL;
		node = sys_AllocMemory( HEAPID_FIELD, sizeof(BLOCK_NODE) );
		outDivMapCont->BlockNodeList[i] = node;
		outDivMapCont->BlockNodeList[i]->DrawOKFlg = FALSE;
		//確保したメモリ(地形)とポインタをバインド
		BindGroundMem(i, outDivMapCont->FldMapMem, (void**)&(outDivMapCont->BlockNodeList[i]->FloorResFile));
		///BindHeightMem(i, outDivMapCont->FldMapMem, (void**)&(outDivMapCont->BlockNodeList[i]->HeightMem));
		//3DOBJのアロケーション
		outDivMapCont->BlockNodeList[i]->ObjDataList =  M3DO_AllocMap3DObjList(HEAPID_FIELD);
		outDivMapCont->BlockNodeList[i]->BlockIndex = NON_BLOCK;
		//地下は専用にアトリビュートデータを持つので、クリア処理を省く
	}
	
	//BlockNodeList = sys_AllocMemory( HEAPID_FIELD, sizeof(BLOCK_NODE)*9 );
}

//--------------------------------------------------------------------------------------------
/**
 * アーカイブオフセット取得
 *
 * @param	ioHandle		アーカイブハンドル
 * @param	inArcIndex		アーカイブインデックス
 * @param	outData			取得データ格納バッファ
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void GetMapArcLoadOffset(ARCHANDLE *ioHandle, const int inArcIndex, DATA_OFS_SIZE *outData)
{
	void *raw_data;
	int *data;
	int size = sizeof(int)*4;	//4バイト４項目
	

	if (ioHandle != NULL){
		raw_data = sys_AllocMemoryLo(HEAPID_FIELD, size);
		ArchiveDataLoadOfsByHandle( ioHandle, inArcIndex, 0, size, raw_data );
	}else{
		GF_ASSERT(0&&"ERROR:ArcHandle is NULL!\n");
		raw_data = ArchiveDataLoadMallocOfsLo(ARC_FIELD_MAP_DATA,inArcIndex,HEAPID_FIELD,0,size);
	}
	
	data = &((int*)(raw_data))[0];
	
	outData->AttrSize = *data;
	data++;
	outData->ObjSize = *data;
	data++;
	outData->MapSize = *data;
	data++;
	outData->HeightSize = *data;
	
	
	sys_FreeMemoryEz(raw_data);
#ifdef DEBUG_ONLY_FOR_saitou
	OS_Printf("local_print arc_size = %x,%x,%x,%x\n",
			outData->AttrSize,outData->ObjSize,outData->MapSize,outData->HeightSize);
#endif
}

//--------------------------------------------------------------------------------------------
/**
 * ブロックデータロードの登録
 *
 * @param	inCount			登録場所（0ＯＲ1）
 * @param	inMapResource	マップリソース
 * @param	inWorld			ワールドポインタ
 * @param	inMapW			マップ横幅
 * @param	inMapH			マップ縦幅
 * @param	inDivMapCont	分割マップ構造体ポインタ
 * @param	*ioMLBS			ロードブロックデータ
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void LoadBlock(	const u8 inCount,
						const MAP_RESOURCE_PTR inMapResource,
						const WORLD_MAP_PTR inWorld,
						const int inMapW,
						const int inMapH,
						DMC_PTR inDivMapCont,
						MAP_LOAD_BLOCK_ST *ioMLBS)
{
	int block_index;
	u8 local_index;
	int arc_index;
	DATA_OFS_SIZE data;
	block_index = ioMLBS->Block[inCount];
	
	if (block_index<0 || block_index>=inMapW*inMapH){
#ifdef DEBUG_ONLY_FOR_saitou		
		OS_Printf("BLOCK_LOAD_ERROR:INDEX_OVER %d\n",block_index);
#endif		
		return;
	}


	//アーカイブインデックスを取得
	arc_index = GetWorldMapArcIdx(block_index, inWorld);
#ifdef DEBUG_ONLY_FOR_saitou	
	OS_Printf("local_print アーカイブ番号%d\n",arc_index);
#endif	
	if (arc_index == MAP_ARC_NO_DATA){
		return;
	}
#if 0
	GF_ASSERT(inDivMapCont->ArcHandle==NULL&&"ハンドル解放忘れ");
	//アーカイブハンドルの取得
	inDivMapCont->ArcHandle = ArchiveDataHandleOpen( ARC_FIELD_MAP_DATA, HEAPID_FIELD );
#endif	
	GetMapArcLoadOffset(inDivMapCont->ArcHandle, arc_index, &data);

	//アトリビュートロード
	{
		void *mem;
		mem = &(ioMLBS->Node[inCount]->Attribute[0]);
		ArchiveDataLoadByHandleContinue( inDivMapCont->ArcHandle, data.AttrSize, mem );
#ifdef DEBUG_ONLY_FOR_saitou
		OS_Printf("local_print アトリビュートロード\n");
#endif
	}

	//3DOBJロード
	M3DO_LoadArc3DObjData(	inDivMapCont->ArcHandle,
							data.ObjSize,
							inMapResource,
							ioMLBS->Node[inCount]->ObjDataList,
							inDivMapCont->Field3DAnmPtr);
	
	//地形ロード
	{
		//稼動タスク追加
		ioMLBS->TaskCnter.BlockLoadTaskCounter++;
#ifdef PM_DEBUG
		{
			if (data.MapSize > 0xf000){
				OS_Printf("アーカイブ%d:地形モデルがメモリサイズオーバーです:%d\n",arc_index,data.MapSize);
				GF_ASSERT(0);
			}
		}
#endif			
		ioMLBS->RandTask = Set3DModelTask(	inDivMapCont->ArcHandle,
											data.MapSize,
											&ioMLBS->Node[inCount]->FloorData,
											&(ioMLBS->Node[inCount]->FloorResFile),
											GetMapResourceTexturePTR(inMapResource),
											&(ioMLBS->Node[inCount]->DrawOKFlg),
											&ioMLBS->TaskCnter.BlockLoadTaskCounter);

		
	}

	//高さロード	
	{
		//稼動タスク追加
		ioMLBS->TaskCnter.BlockHeightLoadTaskCounter++;
		ioMLBS->HeightTask = SetupHeightDataArcTask(inDivMapCont->ArcHandle,
													data.HeightSize,
													ioMLBS->Node[inCount]->MapHeightInfo,
													&ioMLBS->TaskCnter.BlockHeightLoadTaskCounter,
													&ioMLBS->Node[inCount]->HeightMem,
													&ioMLBS->TaskCnter.BlockLoadTaskCounter);
	}
}

//--------------------------------------------------------------------------------------------
/**
 * ブロックデータロードの登録（地下）
 *
 * @param	inCount			登録場所（0ＯＲ1）
 * @param	inMapResource	マップリソース
 * @param	inWorld			ワールドポインタ
 * @param	inMapW			マップ横幅
 * @param	inMapH			マップ縦幅
 * @param	inDivMapCont	分割マップ構造体ポインタ
 * @param	*ioMLBS			ロードブロックデータ
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void LoadBlockForUnder(	const u8 inCount,
								const MAP_RESOURCE_PTR inMapResource,
								const WORLD_MAP_PTR inWorld,
								const int inMapW,
								const int inMapH,
								DMC_PTR inDivMapCont,
								MAP_LOAD_BLOCK_ST *ioMLBS)
{
	int block_index;
	u8 local_index;
	int arc_index;
	DATA_OFS_SIZE data;
	block_index = ioMLBS->Block[inCount];
	
	if (block_index<0 || block_index>=inMapW*inMapH){
#ifdef	DIV_MAP_LOAD_BORDER_PRINT_ON
		OS_Printf("BLOCK_LOAD_ERROR:INDEX_OVER %d\n",block_index);
#endif
		return;
	}

	//アーカイブインデックスを取得
	arc_index = GetWorldMapArcIdx(block_index, inWorld);
#ifdef DEBUG_ONLY_FOR_saitou	
	OS_Printf("local_print アーカイブ番号%d\n",arc_index);
#endif	
	if (arc_index == MAP_ARC_NO_DATA){
		return;
	}
#if 0	
	GF_ASSERT(inDivMapCont->ArcHandle==NULL&&"ハンドル解放忘れ");
	//アーカイブハンドルの取得
	inDivMapCont->ArcHandle = ArchiveDataHandleOpen( ARC_FIELD_MAP_DATA, HEAPID_FIELD );
#endif	
	GetMapArcLoadOffset(inDivMapCont->ArcHandle, arc_index, &data);

	{
		u8 temp[0x800];
		//アトリビュートは飛ばす
		///ArchiveDataSeekByHandle( inDivMapCont->ArcHandle, 0x800+0x10 );
		ArchiveDataLoadByHandleContinue( inDivMapCont->ArcHandle, 0x800, temp );
	}
	//3DOBJロード
	M3DO_LoadArc3DObjData(	inDivMapCont->ArcHandle,
							data.ObjSize,
							inMapResource,
							ioMLBS->Node[inCount]->ObjDataList,
							inDivMapCont->Field3DAnmPtr);
	
	//地形ロード
	{
		//稼動タスク追加
		ioMLBS->TaskCnter.BlockLoadTaskCounter++;
#ifdef PM_DEBUG
		{
			if (data.MapSize > 0xf000){
				OS_Printf("アーカイブ%d:地形モデルがメモリサイズオーバーです:%d\n",arc_index,data.MapSize);
				GF_ASSERT(0);
			}
		}
#endif			
		ioMLBS->RandTask = Set3DModelTask(	inDivMapCont->ArcHandle,
											data.MapSize,
											&ioMLBS->Node[inCount]->FloorData,
											&(ioMLBS->Node[inCount]->FloorResFile),
											GetMapResourceTexturePTR(inMapResource),
											&(ioMLBS->Node[inCount]->DrawOKFlg),
											&ioMLBS->TaskCnter.BlockLoadTaskCounter);

		
	}
	//高さは読まない		
}

//--------------------------------------------------------------------------------------------
/**
 * ブロックのロード1sync型(一括読み込みのため、ブラックアウト時に使用する)
 *
 * @param	inBlockIndex	ブロックインデックス
 * @param	inLocalIndex	0～3ローカルインデックス
 * @param	inMapResource	マップリソース
 * @param	inWorld			ワールドポインタ
 * @param	inMapW			マップ横幅
 * @param	inMapH			マップ縦幅
 * @param	inLightValid	ライトフラグ
 * @param	outDivMapCont	分割マップ構造体ポインタ
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void LoadBlockQuick(	const int inBlockIndex,
							const u8 inLocalIndex,
							const MAP_RESOURCE_PTR inMapResource,
							const WORLD_MAP_PTR inWorld,
							const int inMapW,
							const int inMapH,
							const BOOL inLightValid,
							DMC_PTR outDivMapCont)
{
	int arc_index;
	NNSG3dResMdl* model;			// モデル
	DATA_OFS_SIZE data;
	
	if (inBlockIndex<0 || inBlockIndex>=inMapW*inMapH){
#ifdef	DIV_MAP_LOAD_BORDER_PRINT_ON		
		OS_Printf("BLOCK_LOAD_ERROR:INDEX_OVER\n");
#endif		
		return;
	}

	//アーカイブインデックスを取得
	arc_index = GetWorldMapArcIdx(inBlockIndex, inWorld);
#ifdef DEBUG_ONLY_FOR_saitou
	OS_Printf("local_print アーカイブ番号%d\n",arc_index);
#endif	
	if (arc_index == MAP_ARC_NO_DATA){
		return;
	}
	//アーカイブハンドルの取得
///	outDivMapCont->ArcHandle = ArchiveDataHandleOpen( ARC_FIELD_MAP_DATA, HEAPID_FIELD );
	
	GetMapArcLoadOffset(outDivMapCont->ArcHandle, arc_index, &data);

	//アトリビュートロード
	{
		void *mem;
		mem = &(outDivMapCont->BlockNodeList[inLocalIndex]->Attribute[0]);

		ArchiveDataLoadByHandleContinue( outDivMapCont->ArcHandle, data.AttrSize, mem );
	}

	//3DOBJロード
	M3DO_LoadArc3DObjData(	outDivMapCont->ArcHandle,
							data.ObjSize,
							inMapResource,
							outDivMapCont->BlockNodeList[inLocalIndex]->ObjDataList,
							outDivMapCont->Field3DAnmPtr);
	
	//地形ロード
	{
		model = Set3DModel(	outDivMapCont->ArcHandle,
							data.MapSize,
							&outDivMapCont->BlockNodeList[inLocalIndex]->FloorData,
							&(outDivMapCont->BlockNodeList[inLocalIndex]->FloorResFile),
							GetMapResourceTexturePTR(inMapResource));

		if (inLightValid == TRUE){
			//グローバルステート使用
			SetGlbLightMdl(model);
		}

		outDivMapCont->BlockNodeList[inLocalIndex]->DrawOKFlg = TRUE;	
	}

	//高さロード
	{
		SetupHeightDataArc(	outDivMapCont->ArcHandle,
							data.HeightSize,
							outDivMapCont->BlockNodeList[inLocalIndex]->MapHeightInfo,
							outDivMapCont->BlockNodeList[inLocalIndex]->HeightMem);
	}
#if 0
	//アーカイブハンドルの解放
	ArchiveDataHandleClose( outDivMapCont->ArcHandle );
	outDivMapCont->ArcHandle = NULL;
#endif	
	outDivMapCont->BlockNodeList[inLocalIndex]->BlockIndex = inBlockIndex;

	//コールバック呼び出し
	if (outDivMapCont->CallBack!=NULL){
		outDivMapCont->CallBack(	outDivMapCont->CallBackWork,
									inBlockIndex,
									outDivMapCont->BlockNodeList[inLocalIndex]->ObjDataList);
	}
}

//--------------------------------------------------------------------------------------------
/**
 * ブロックのロード1sync型(一括読み込みのため、ブラックアウト時に使用する)地下用
 *
 * @param	inBlockIndex	ブロックインデックス
 * @param	inLocalIndex	0～3　ローカルインデックス
 * @param	inMapResource	マップリソース
 * @param	inWorld			ワールドポインタ
 * @param	inMapW			マップ横幅
 * @param	inMapH			マップ縦幅
 * @param	inLightValid	ライトフラグ
 * @param	outDivMapCont	分割マップ構造体ポインタ
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void LoadBlockQuickForUnder(	const int inBlockIndex,
									const u8 inLocalIndex,
									const MAP_RESOURCE_PTR inMapResource,
									const WORLD_MAP_PTR inWorld,
									const int inMapW,
									const int inMapH,
									const BOOL inLightValid,
									DMC_PTR outDivMapCont)
{
	int arc_index;
	DATA_OFS_SIZE data;
	NNSG3dResMdl* model;			// モデル
	if (inBlockIndex<0 || inBlockIndex>=inMapW*inMapH){
		return;
	}

	//アーカイブインデックスを取得
	arc_index = GetWorldMapArcIdx(inBlockIndex, inWorld);
#ifdef DEBUG_ONLY_FOR_saitou
	OS_Printf("local_print アーカイブ番号%d\n",arc_index);
#endif
	if (arc_index == MAP_ARC_NO_DATA){
		return;
	}
	//アーカイブハンドルの取得
///	outDivMapCont->ArcHandle = ArchiveDataHandleOpen( ARC_FIELD_MAP_DATA, HEAPID_FIELD );
	
	GetMapArcLoadOffset(outDivMapCont->ArcHandle, arc_index, &data);

	{
		u8 temp[0x800];
		//アトリビュートは飛ばす
		///ArchiveDataSeekByHandle( outDivMapCont->ArcHandle, 0x800+0x10 );
		ArchiveDataLoadByHandleContinue( outDivMapCont->ArcHandle, 0x800, temp );
	}

	//3DOBJロード
	M3DO_LoadArc3DObjData(	outDivMapCont->ArcHandle,
							data.ObjSize,
							inMapResource,
							outDivMapCont->BlockNodeList[inLocalIndex]->ObjDataList,
							outDivMapCont->Field3DAnmPtr);
	
	//地形ロード
	{
		model = Set3DModel(	outDivMapCont->ArcHandle,
							data.MapSize,
							&outDivMapCont->BlockNodeList[inLocalIndex]->FloorData,
							&(outDivMapCont->BlockNodeList[inLocalIndex]->FloorResFile),
							GetMapResourceTexturePTR(inMapResource));

		if (inLightValid == TRUE){
			//グローバルステート使用
			SetGlbLightMdl(model);
		}

		outDivMapCont->BlockNodeList[inLocalIndex]->DrawOKFlg = TRUE;	
	}

	//高さ読まない
#if 0
	//アーカイブハンドルの解放
	ArchiveDataHandleClose( outDivMapCont->ArcHandle );
	outDivMapCont->ArcHandle = NULL;
#endif	
	outDivMapCont->BlockNodeList[inLocalIndex]->BlockIndex = inBlockIndex;
}

//--------------------------------------------------------------------------------------------
/**
 * ブロックロードタスクが稼動中かをチェック
 *
 * @param	*inTaskCnter	タスクカウンタ
 *
 * @return	BOOL		TRUE:終了	FALSE:稼動中
 */
//--------------------------------------------------------------------------------------------
static BOOL CheckBlockLoadTaskCounter(const MAP_LOAD_TASK_COUNTER *inTaskCnter)
{
	if ((inTaskCnter->BlockLoadTaskCounter == 0)&&(inTaskCnter->BlockHeightLoadTaskCounter == 0) ){
		return TRUE;
	}
	else{
		return FALSE;
	}
}

//--------------------------------------------------------------------------------------------
/**
 * マップロードリクエスト関数
 *
 * @param	inBlock1	第1ロードブロックインデックス
 * @param	inBlock2	第2ロードブロックインデックス
 * @param	inIdx1		第1ロードローカルインデックス(0～3)
 * @param	inIdx2		第2ロードローカルインデックス(0～3)
 * @param	inBlankNo	登録空き場所（0ＯＲ1）
 * @param	inDir		ロード方向
 *
 * @return	BOOL		登録成功有無	TRUE:成功	FALSE:失敗
 */
//--------------------------------------------------------------------------------------------
static BOOL BlockLoadReqest( DMC_PTR ioDivMapCont,
								const int inBlock1,
								const int inBlock2,
								const u8 inIdx1,
								const u8 inIdx2,
								const u8 inBlankNo,
								const u8 inDir)
{
	//稼動中に登録しようとしているのでエラーとする
	GF_ASSERT((ioDivMapCont->MLBC[inBlankNo].Moving == FALSE)&&"ERROR:稼動中なのに登録しようとしている");
	
	//稼動中にする
	ioDivMapCont->MLBC[inBlankNo].Moving = TRUE;

	//ロード方向保存
	ioDivMapCont->MLBC[inBlankNo].LoadDir = inDir;
	
	ioDivMapCont->MLBC[inBlankNo].MLBS.Block[0] = inBlock1;
	ioDivMapCont->MLBC[inBlankNo].MLBS.Block[1] = inBlock2;
	ioDivMapCont->MLBC[inBlankNo].MLBS.Index[0] = inIdx1;
	ioDivMapCont->MLBC[inBlankNo].MLBS.Index[1] = inIdx2;
	
	ioDivMapCont->MLBC[inBlankNo].MLBS.Node[0] = ioDivMapCont->BlockNodeList[inIdx1];
	ioDivMapCont->MLBC[inBlankNo].MLBS.Node[1] = ioDivMapCont->BlockNodeList[inIdx2];

	ioDivMapCont->MLBC[inBlankNo].MLBS.TotalCount = 0;
	ioDivMapCont->MLBC[inBlankNo].MLBS.BlockLoadOK = FALSE;

	//稼動ローダーがないならロードをリクエストする
	//稼動ローダーがあるなら、登録だけする
	if (ioDivMapCont->MovingNum == 0){		
		ioDivMapCont->LoadSeq = DML_LOAD_BLOCK;
	}

	ioDivMapCont->BlockNodeList[inIdx1]->BlockIndex = inBlock1;
	ioDivMapCont->BlockNodeList[inIdx2]->BlockIndex = inBlock2;
	
	ioDivMapCont->MovingNum++;
	ioDivMapCont->BlankNo = (ioDivMapCont->BlankNo+1)%2;
	
	return TRUE;
}

//--------------------------------------------------------------------------------------------
/**
 * メインシーケンス関数
 *
 * @param	none
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void DivMapLoadMain(FIELDSYS_WORK *fsys, DMC_PTR ioDivMapCont)
{
#ifdef DEBUG_ONLY_FOR_saitou
static test_sync_count_flg = FALSE;
static test_sync_counter = 0;
#endif
	u8 my_dir;
	MAP_LOAD_BLOCK_ST *mlbs;
	DIV_MAP_CHECK	*dmc;
	mlbs = &ioDivMapCont->MLBC[ioDivMapCont->NowMovingNo].MLBS;
	dmc = &ioDivMapCont->MapCheck;
#ifdef DEBUG_ONLY_FOR_saitou	
if (test_sync_count_flg){
	test_sync_counter++;
}
#endif
	if (dmc->Valid == TRUE){

		//現在移動中
		if (dmc->Moving){	//旧座標と現在座標の差分が、1グリッドになったかを判定
			
			GF_ASSERT((*dmc->SmallVal)<=(*dmc->LargeVal)&&"ERROR:値不正");

			if ( (*dmc->LargeVal) - (*dmc->SmallVal) >= (FX32_ONE *ONE_GRID_SIZE) ){
				int grid_x,grid_z;
				//差分は外部値を信用して行います
				//1グリッド移動完了
				GetGridXZ(dmc->TargetPoint->x, dmc->TargetPoint->z, &grid_x, &grid_z);	
				UpdateNowData(grid_x, grid_z, ioDivMapCont);//内部データ更新
				dmc->OldPoint = *dmc->TargetPoint;
                if(!(dmc->OldPoint.z%(FX32_ONE*8)==0)){  // 通信時にはエラーにする
                    if(CommStateSetError(COMM_ERROR_RESET_SAVEPOINT)){
                        return;
                    }
                }
				GF_ASSERT(dmc->OldPoint.z%(FX32_ONE*8)==0&&"グリッド単位の移動がなされていない");
				dmc->Moving = FALSE;
				dmc->LargeVal = NULL;
				dmc->SmallVal = NULL;
			}
		}else{	//バインドされている座標の動き始めを検出
			if ( (dmc->OldPoint.x != dmc->TargetPoint->x)&&
					(dmc->OldPoint.z != dmc->TargetPoint->z) ){
				//ｘ、ｚ同時変化はエラーとする
				GF_ASSERT(0&&"ERROR：XZ同時変化が発生");				
			}else if ( (dmc->OldPoint.x == dmc->TargetPoint->x)&&
						(dmc->OldPoint.z == dmc->TargetPoint->z) ){
				;//何もしない
			}else{	//XZどちらか一方の変化があった場合
				dmc->Moving = TRUE;
				if (dmc->OldPoint.x != dmc->TargetPoint->x){	//Xが変化
					if (dmc->OldPoint.x > dmc->TargetPoint->x){
						//旧座標のほうが大きい＞＞左に移動
						dmc->LargeVal = &dmc->OldPoint.x;
						dmc->SmallVal = &dmc->TargetPoint->x;
						dmc->Dir = MAP_LOAD_LEFT;
					}else{
						//右に移動
						dmc->LargeVal = &dmc->TargetPoint->x;
						dmc->SmallVal = &dmc->OldPoint.x;
						dmc->Dir = MAP_LOAD_RIGHT;
					}
                    if(!(dmc->OldPoint.x%(FX32_ONE*8)==0)){  // 通信時にはエラーにする
                        if(CommStateSetError(COMM_ERROR_RESET_SAVEPOINT)){
                            return;
                        }
                    }
                    GF_ASSERT(dmc->OldPoint.x%(FX32_ONE*8)==0&&"旧x座標がグリッド単位の移動ではない");
				}
				else{	//Zが変化
					if (ioDivMapCont->MapCheck.OldPoint.z >	ioDivMapCont->MapCheck.TargetPoint->z){
						//旧座標のほうが大きい＞＞上に移動
						dmc->LargeVal = &dmc->OldPoint.z;
						dmc->SmallVal = &dmc->TargetPoint->z;
						dmc->Dir = MAP_LOAD_UP;
					}else{
						//下に移動
						dmc->LargeVal = &dmc->TargetPoint->z;
						dmc->SmallVal = &dmc->OldPoint.z;
						dmc->Dir = MAP_LOAD_DOWN;
					}
                    if(!(dmc->OldPoint.z%(FX32_ONE*8)==0)){  // 通信時にはエラーにする
                        if(CommStateSetError(COMM_ERROR_RESET_SAVEPOINT)){
                            return;
                        }
                    }
					GF_ASSERT(dmc->OldPoint.z%(FX32_ONE*8)==0&&"旧z座標がグリッド単位の移動ではない");
				}
				//ロードリクエスト
				DivMapLoad_UpdateBlockData(dmc->Dir,ioDivMapCont);
			}
		}
	
	}//end if(dmc->Valid == TRUE)
	
	switch(ioDivMapCont->LoadSeq){
	case DML_LOAD_BLOCK:	//ブロックのロード
#ifdef DIV_MAP_LOAD_DEBUG
		OS_Printf("ロード開始\n");
#endif
		///OS_Printf("中止確認%d\n",mlbs->Index[mlbs->TotalCount]);
		//リクエスト中止がかかっていないなら、ロード
		if (ioDivMapCont->LocalFreeIndexTable[mlbs->Index[mlbs->TotalCount]] == TRUE){
#ifdef DIV_MAP_LOAD_DEBUG			
			OS_Printf("解放リクエストがかかっているので、ロードしない\n");
#endif
			;
		}else{
#ifdef DIV_MAP_LOAD_DEBUG
			OS_Printf("トータル%dつめ,ローカルインデックス%d:ロード\n",mlbs->TotalCount+1,mlbs->Index[mlbs->TotalCount]);
			OS_Printf("%d:現在読み込み位置\n",ioDivMapCont->NowMovingNo);
#endif
			ioDivMapCont->FuncList->DivLoadFunc(	mlbs->TotalCount,
												ioDivMapCont->MapResource,
												ioDivMapCont->World,
												ioDivMapCont->MapW,
												ioDivMapCont->MapH,
												ioDivMapCont,
												mlbs);
#ifdef DEBUG_ONLY_FOR_saitou			
			test_sync_count_flg = TRUE;
			test_sync_counter = 1;
#endif
		}
		mlbs->TotalCount++;
		
		ioDivMapCont->LoadSeq = DML_LOAD_WAIT;
		break;
	case DML_LOAD_WAIT:		//ブロックロード終了待ち
		if (ioDivMapCont->LocalFreeIndexTable[mlbs->Index[mlbs->TotalCount-1]] == TRUE){
#ifdef DIV_MAP_LOAD_DEBUG
			OS_Printf("%d,%d:解放リクエストがかかっているので、解放する\n",mlbs->Index[mlbs->TotalCount-1],mlbs->TotalCount);
#endif
			LoadTaskStopReqestByMLBS(mlbs);
			ioDivMapCont->LocalFreeIndexTable[mlbs->Index[mlbs->TotalCount-1]] = FALSE;
		}
		if ((mlbs->TotalCount <=2)&&(CheckBlockLoadTaskCounter(&mlbs->TaskCnter) == TRUE)){
			if (mlbs->TotalCount>=2){
#ifdef DIV_MAP_LOAD_DEBUG
				OS_Printf("%d:2つめ読み込み終わり\n",mlbs->TotalCount);
#endif
				mlbs->BlockLoadOK = TRUE;	//読み込み終了
				//2つのブロックロードが終了したので、積み込まれているブロックロードがあるかを調べる
				//積まれている場合は処理をする
///		MapLoadCont.MLBC[MapLoadCont.NowMovingTaskNo].MLBS.Node[0]->DrawOKFlg = TRUE;
///		MapLoadCont.MLBC[MapLoadCont.NowMovingTaskNo].MLBS.Node[1]->DrawOKFlg = TRUE;
				
			}else{
#ifdef DIV_MAP_LOAD_DEBUG
				OS_Printf("%d:1つめ読み込み終わり\n",mlbs->TotalCount);
#endif
				ioDivMapCont->LoadSeq = DML_LOAD_BLOCK;
#ifdef DIV_MAP_LOAD_DEBUG	
				OS_Printf("1つ目ロード！　mlbs->LoadTime = %d\n",mlbs->DebugLoadTimer);
#endif				
			}
#if 0			
			//読み込みが終了したのでアーカイブハンドルを解放
			if (ioDivMapCont->ArcHandle != NULL){
				ArchiveDataHandleClose( ioDivMapCont->ArcHandle );
				ioDivMapCont->ArcHandle = NULL;
			}
#endif			
			if (/*mlbs->Node[mlbs->TotalCount-1]->FloorResFile != NULL*/mlbs->Node[mlbs->TotalCount-1]->DrawOKFlg == TRUE){
				NNSG3dResMdlSet* pMdlSet = NNS_G3dGetMdlSet(mlbs->Node[mlbs->TotalCount-1]->FloorResFile);
				NNSG3dResMdl* model = NNS_G3dGetMdlByIdx(pMdlSet, 0);
				if (MAPRES_IsValidLight(ioDivMapCont->MapResource) == TRUE){
					//グローバルステート使用
					SetGlbLightMdl(model);
				}
			}
#ifdef DIV_CALL_BACK	
			//ここでコールバック
			if (ioDivMapCont->CallBack!=NULL){
				//マトリックスサイズを見て、オーバーしていたらコールしない
				if (0<=mlbs->Node[mlbs->TotalCount-1]->BlockIndex &&
					mlbs->Node[mlbs->TotalCount-1]->BlockIndex<ioDivMapCont->MapW*ioDivMapCont->MapH){
					ioDivMapCont->CallBack(	ioDivMapCont->CallBackWork,
											mlbs->Node[mlbs->TotalCount-1]->BlockIndex,
											mlbs->Node[mlbs->TotalCount-1]->ObjDataList);
				}
			}
#endif
#ifdef DEBUG_ONLY_FOR_saitou			
			//かかったシンク数を表示
			OS_Printf("local_print ロード所要シンク数%d\n",test_sync_counter);
			test_sync_counter = 0;
			test_sync_count_flg = FALSE;
#endif			
		}
		break;
	case DML_NONE:			//無処理状態
		break;
	case DML_FREE_WAIT:		//ブロックロード解放待ち
		if ( CheckBlockLoadTaskCounter(&mlbs->TaskCnter)==TRUE ){
			//高さロードを監視すれば、タスク終了を確認できる
			ioDivMapCont->MovingNum = 0;
#if 0			
			//読み込みが終了したのでアーカイブハンドルを解放
			if (ioDivMapCont->ArcHandle != NULL){
				ArchiveDataHandleClose( ioDivMapCont->ArcHandle );
				ioDivMapCont->ArcHandle = NULL;
			}
#endif			
		}
		break;
	}

	//稼動しているものがないならば
	if (ioDivMapCont->MovingNum == 0){
		ioDivMapCont->NowMovingNo = 0;
		ioDivMapCont->BlankNo = 0;
		ioDivMapCont->LoadSeq = DML_NONE;		//無処理シーケンス
		return;
	}

	//ブロックロード終了監視
	if ( IsFinishedLoadBlock(ioDivMapCont) == TRUE){
		//稼動フラグをおとす
		ioDivMapCont->MLBC[ioDivMapCont->NowMovingNo].Moving = FALSE;

		//解放ブロックマーキングをクリア
		ClearLocalFreeIndexTable(ioDivMapCont);
		
		ioDivMapCont->MovingNum--;		//管理数減算
	
		ioDivMapCont->NowMovingNo = (ioDivMapCont->NowMovingNo+1)%2;	//稼動番号更新

		//稼動待ちブロックロードがあるなら、ロード開始
		if (ioDivMapCont->MovingNum != 0){
#ifdef DIV_MAP_LOAD_DEBUG
			OS_Printf("次ロード開始\n");
#endif
			//MapLoadCont.MLBC[MapLoadCont.NowMovingNo].MLBS.ReadStartOK = TRUE;

			ioDivMapCont->LoadSeq = DML_LOAD_BLOCK;		//ロードシーケンス

		}else{
			ioDivMapCont->NowMovingNo = 0;
			ioDivMapCont->BlankNo = 0;
			ioDivMapCont->LoadSeq = DML_NONE;		//無処理シーケンス
		}

		//ストックがある場合は優先的に登録
		if (ioDivMapCont->Stock.Valid == TRUE){
			BOOL rc;
			ioDivMapCont->Stock.Valid = FALSE;
			//ストック方向から、読み込まなくていいローカルインデックスを決定する
			MarkLocalFreeIndexTableByDir(ioDivMapCont->Stock.LoadDir,ioDivMapCont);
			
			AddMapLoadForStock(ioDivMapCont);
		}
		
	}
}

//--------------------------------------------------------------------------------------------
/**
 * マップロード追加
 *
 * @param	inBlock1	第1ロードブロックインデックス
 * @param	inBlock2	第2ロードブロックインデックス
 * @param	inIdx1		第1ロードローカルインデックス(0～3)
 * @param	inIdx2		第2ロードローカルインデックス(0～3)
 * @param	inDir		ロード方向
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void AddMapLoad( const int inBlock1,
						const int inBlock2,
						const u8 inIdx1,
						const u8 inIdx2,
						const u8 inDir,
						DMC_PTR ioDivMapCont)
{
	int i;
	u8 no;
	BOOL rc;
	
#ifdef DEBUG_ONLY_FOR_saitou
	if (ioDivMapCont->MovingNum>=2){
		OS_Printf("local_print 3つ目\n");
	}
#endif
	GF_ASSERT((ioDivMapCont->Stock.Valid != TRUE)&&"ストックが埋まってる");
	//現在リクエストのかかっているロード方向と稼動中タスクの方向を比較
	if ( CompLoadDirection(inDir, ioDivMapCont, &no) == TRUE ){
		//ロード方向とリクエスト方向が正反対ならば、ロード中止
#ifdef DIV_MAP_LOAD_DEBUG
		OS_Printf("no:%d",no);
#endif
		LoadStopReqest(ioDivMapCont,no);
		//空きがない場合
		if (ioDivMapCont->MovingNum>=2){
			ioDivMapCont->Stock.Valid = TRUE;
			ioDivMapCont->Stock.Block[0] = inBlock1;
			ioDivMapCont->Stock.Block[1] = inBlock2;
			ioDivMapCont->Stock.Index[0] = inIdx1;
			ioDivMapCont->Stock.Index[1] = inIdx2;
			ioDivMapCont->Stock.Node[0] = ioDivMapCont->BlockNodeList[inIdx1];
			ioDivMapCont->Stock.Node[1] = ioDivMapCont->BlockNodeList[inIdx2];
			ioDivMapCont->Stock.LoadDir = inDir;
			
			ioDivMapCont->BlockNodeList[inIdx1]->BlockIndex = inBlock1;
			ioDivMapCont->BlockNodeList[inIdx2]->BlockIndex = inBlock2;

		}else{
			rc = BlockLoadReqest(ioDivMapCont,inBlock1,inBlock2,inIdx1,inIdx2,ioDivMapCont->BlankNo,inDir);
			if (rc == FALSE){
				//空きがない場合（リクエストが中止タスクを含め3つ目）、リクエスト待機状態にしとく
#ifdef DEBUG_ONLY_FOR_saitou
				OS_Printf("local_print ERROR:3つ目\n");
#endif				
			}
		}
	}else{
		//正反対でない場合、リクエスト追加
		//空いている管理タスクに登録
		rc = BlockLoadReqest(ioDivMapCont,inBlock1,inBlock2,inIdx1,inIdx2,ioDivMapCont->BlankNo,inDir);
#ifdef DIV_MAP_LOAD_DEBUG
		OS_Printf("%dにタスク登録\n",MapLoadCont.BlankNo);
#endif
		//管理タスクがいっぱいなのに、リクエストがかかった場合、エラーとしとく
		GF_ASSERT((rc==TRUE)&&"ERROR:管理タスクがいっぱい");
	}
}

//--------------------------------------------------------------------------------------------
/**
 * ブロックデータの解放(移動時)
 *
 * @param	inLocalIndex	//解放するローカルインデックス（0～3）
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void FreeBlock(const u8 inLocalIndex, DMC_PTR outDivMapCont)
{
	outDivMapCont->BlockNodeList[inLocalIndex]->DrawOKFlg = FALSE;
	SetInvalidHeightData(outDivMapCont->BlockNodeList[inLocalIndex]->MapHeightInfo);
//	ClearFldMapMem(inLocalIndex, outDivMapCont->FldMapMem);
	
	//3DOBJデータ解放(実際には、データ解放ではなく、管理情報のクリア)
	M3DO_CleanMap3DObjList(outDivMapCont->BlockNodeList[inLocalIndex]->ObjDataList);
	outDivMapCont->BlockNodeList[inLocalIndex]->BlockIndex = NON_BLOCK;

	//アトリビュートクリア
	MI_CpuFillFast(outDivMapCont->BlockNodeList[inLocalIndex]->Attribute, 0xffffffff, 2*32*32 );
	
	//解放ブロックマーキング
	outDivMapCont->LocalFreeIndexTable[inLocalIndex] = TRUE;
}

//--------------------------------------------------------------------------------------------
/**
 * ブロックデータロードの登録
 *
 * @param	inCount		登録場所（0ＯＲ1）
 * @param	*ioMLBS		ロードブロックデータ
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void FreeAndMoveNode(const u8 inFreeNo1,
							const u8 inFreeNo2,
							const u8 inMoveNo1,
							const u8 inMoveNo2,
							DMC_PTR ioDivMapCont)
{
	BLOCK_NODE *TempNode[2];
	//inFreeNo1,inFreeNo2を解放
	FreeBlock(inFreeNo1,ioDivMapCont);
	FreeBlock(inFreeNo2,ioDivMapCont);
	//解放したノードを1時退去
	TempNode[0] = ioDivMapCont->BlockNodeList[inFreeNo1];
	TempNode[1] = ioDivMapCont->BlockNodeList[inFreeNo2];
	//残りの2つのテーブルを移動
	ioDivMapCont->BlockNodeList[inFreeNo1] = ioDivMapCont->BlockNodeList[inMoveNo1];
	ioDivMapCont->BlockNodeList[inFreeNo2] = ioDivMapCont->BlockNodeList[inMoveNo2];
	//退去したノードを新読み込み位置に戻す
	ioDivMapCont->BlockNodeList[inMoveNo1] = TempNode[0];
	ioDivMapCont->BlockNodeList[inMoveNo2] = TempNode[1];
}

//--------------------------------------------------------------------------------------------
/**
 * ブロック更新
 *
 * @param	inBlockIndex	ブロックインデックス
 * @param	inDirection		更新方向
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void UpdateBlockList(const int inBlockIndex, const u8 inDirection, DMC_PTR ioDivMapCont)
{
	u8 i,j;
	int block1,block2;
	int old_block;
	int idx1,idx2;
	switch(inDirection){
	case MAP_LOAD_UP:	//自機が上に移動(2→0、3→1)
		//2,3を解放して0,1を移動
		FreeAndMoveNode(2,3,0,1,ioDivMapCont);

		//自機のいるブロックインデックスをキーにして、0,1にはいるブロックを算出
		//2→0、3→1で場合分け

		if (/*左下にいた場合*/ioDivMapCont->NowPosInBlock == 2){
			block1 = inBlockIndex - ioDivMapCont->MapW;
			block2 = inBlockIndex - ioDivMapCont->MapW - 1;
			idx1 = 1;
			idx2 = 0;
			//整合性チェック
			if (block1<0){	//範囲外
				//真上のブロックはマトリックス内にあるはず
				block1 = NON_BLOCK;
				block2 = NON_BLOCK;
			}else{
				//２つ目のブロックはマトリクス内、且つ読み込んだ２ブロックは、同じ行にあるはず
				if ( (block2<0)||(!CheckRowBlockIndex(block1,block2,ioDivMapCont->MapW)) ){	//範囲外
					block2 = NON_BLOCK;
				}
			}
		}else if(/*右下にいた場合*/ioDivMapCont->NowPosInBlock == 3){
			block1 = inBlockIndex - ioDivMapCont->MapW;
			block2 = inBlockIndex - ioDivMapCont->MapW + 1;
			idx1 = 0;
			idx2 = 1;
			//整合性チェック
			if (block1<0){	//範囲外
				//真上のブロックはマトリックス内にあるはず
				block1 = NON_BLOCK;
				block2 = NON_BLOCK;
			}else{
				//読み込んだ２ブロックは、同じ行にあるはず
				if ( !CheckRowBlockIndex(block1,block2,ioDivMapCont->MapW) ){	//範囲外
					block2 = NON_BLOCK;
				}
			}
		}else{
			GF_ASSERT(0&&"ERROR:上移動ブロック計算失敗");
		}
/**
		//整合性チェック
		if ( (block1<0)||(ioDivMapCont->MapW*ioDivMapCont->MapH<=block1) ){
			//範囲外
			block1 = -1;
			block2 = -2;
		}
*/
		//0,1の新規ロード
		AddMapLoad(block1,block2,idx1,idx2,inDirection,ioDivMapCont);
		
		break;
	case MAP_LOAD_LEFT:	//自機が左に移動
		//1,3を解放して0,2を移動
		FreeAndMoveNode(1,3,0,2,ioDivMapCont);
		
		//自機のいるブロックインデックスをキーにして、0,2にはいるブロックを算出
		//1→0、3→2で場合分け

		if (/*右上にいた場合*/ioDivMapCont->NowPosInBlock == 1){
			block1 = inBlockIndex - 1;
			block2 = inBlockIndex - ioDivMapCont->MapW - 1;
			idx1 = 2;
			idx2 = 0;
			//自機のいる縦のブロックインデックスを保存(横移動のみ)
///			old_block = ioDivMapCont->BlockNodeList[3]->BlockIndex;
			//整合性チェック
			if ( (block1<0)||(!CheckRowBlockIndex(block1,inBlockIndex,ioDivMapCont->MapW)) ){
				//読み込んだ左隣のブロックは、マトリクス内、且つ今までいたブロックと同じ行のはず
				block1 = NON_BLOCK;
				block2 = NON_BLOCK;
			}
			if ( (block2<0)||
					(!CheckColumnBlockIndex(block1,block2,ioDivMapCont->MapW)) ){
				//2つ目のブロックは、マトリクス内、且つ読み込んだ２ブロックは、同じ列にあるはず
				block2 = NON_BLOCK;
			}
		}else if(/*右下にいた場合*/ioDivMapCont->NowPosInBlock == 3){
			block1 = inBlockIndex - 1;
			block2 = inBlockIndex + ioDivMapCont->MapW - 1;
			idx1 = 0;
			idx2 = 2;
			//自機のいる縦のブロックインデックスを保存(横移動のみ)
///			old_block = ioDivMapCont->BlockNodeList[1]->BlockIndex;
			//整合性チェック
			if ( (block1<0)||(!CheckRowBlockIndex(block1,inBlockIndex,ioDivMapCont->MapW)) ){
				//読み込んだ左隣のブロックは、マトリクス内、且つ今までいたブロックと同じ行のはず
				block1 = NON_BLOCK;
				block2 = NON_BLOCK;
			}
			if ( (ioDivMapCont->MapW*ioDivMapCont->MapH<=block2)||
					(!CheckColumnBlockIndex(block1,block2,ioDivMapCont->MapW)) ){
				//2つ目のブロックは、マトリクス内、且つ読み込んだ２ブロックは、同じ列にあるはず
				block2 = NON_BLOCK;
			}
		}else{
			GF_ASSERT(0&&"ERROR:左移動ブロック計算失敗");
		}
		AddMapLoad(block1,block2,idx1,idx2,inDirection,ioDivMapCont);
/**		
#ifdef DIV_MAP_LOAD_DEBUG
		OS_Printf("load_block:%d,%d\nold:%d,%d\n",block1,block2,old_block1,old_block2);
#endif
		//新規読み込みブロックの整合性をチェック(横移動のみ)
		if (CheckSideBlockIndex(block1,old_block,ioDivMapCont->MapW)==TRUE){
			AddMapLoad(block1,block2,idx1,idx2,inDirection,ioDivMapCont);
		}else{
#ifdef	DEBUG_ONLY_FOR_saitou			
			OS_Printf("local_print 画面左端なのでロードしない\n");
#endif			
			ioDivMapCont->LocalFreeIndexTable[1] = FALSE;
			ioDivMapCont->LocalFreeIndexTable[3] = FALSE;
		}
*/		
		break;
	case MAP_LOAD_RIGHT: //自機が右に移動
		//0,2を解放して1,3を移動
		FreeAndMoveNode(0,2,1,3,ioDivMapCont);
		
		//自機のいるブロックインデックスをキーにして、1,3にはいるブロックを算出
		//0→1、2→3で場合分け

		if (/*左上にいた場合*/ioDivMapCont->NowPosInBlock == 0){
			block1 = inBlockIndex + 1;
			block2 = inBlockIndex - ioDivMapCont->MapW + 1;
			idx1 = 3;
			idx2 = 1;
			//自機のいる縦のブロックインデックスを保存(横移動のみ)
///			old_block = ioDivMapCont->BlockNodeList[2]->BlockIndex;
			//整合性チェック
			if ( (ioDivMapCont->MapW*ioDivMapCont->MapH<=block1)||
					(!CheckRowBlockIndex(block1,inBlockIndex,ioDivMapCont->MapW)) ){
				//読み込んだ右隣のブロックは、マトリクス内、且つ今までいたブロックと同じ行のはず
				block1 = NON_BLOCK;
				block2 = NON_BLOCK;
			}
			if ( (ioDivMapCont->MapW*ioDivMapCont->MapH<=block2)||
					(!CheckColumnBlockIndex(block1,block2,ioDivMapCont->MapW)) ){
				//2つ目のブロックはマトリクス内、且つ読み込んだ２ブロックは、同じ列にあるはず
				block2 = NON_BLOCK;
			}
		}else if(/*左下にいた場合*/ioDivMapCont->NowPosInBlock == 2){
			block1 = inBlockIndex + 1;
			block2 = inBlockIndex + ioDivMapCont->MapW + 1;
			idx1 = 1;
			idx2 = 3;
			//自機のいる縦のブロックインデックスを保存(横移動のみ)
///			old_block = ioDivMapCont->BlockNodeList[0]->BlockIndex;
			//整合性チェック
			if ( (ioDivMapCont->MapW*ioDivMapCont->MapH<=block1)||
					(!CheckRowBlockIndex(block1,inBlockIndex,ioDivMapCont->MapW)) ){
				//読み込んだ右隣のブロックは、マトリクス内、且つ今までいたブロックと同じ行のはず
				block1 = NON_BLOCK;
				block2 = NON_BLOCK;
			}
			if ( (block2<0)||
					(!CheckColumnBlockIndex(block1,block2,ioDivMapCont->MapW)) ){
				//2つ目のブロックはマトリクス内、且つ読み込んだ２ブロックは、同じ列にあるはず
				block2 = NON_BLOCK;
			}
		}else{
			OS_Printf("ERROR:右移動ブロック計算失敗\n");
		}
		AddMapLoad(block1,block2,idx1,idx2,inDirection,ioDivMapCont);
/**		
		//新規読み込みブロックの整合性をチェック(横移動のみ)
#ifdef DIV_MAP_LOAD_DEBUG
		OS_Printf("load_block:%d,%d\nold:%d,%d\n",block1,block2,old_block1,old_block2);
#endif
		
		if (CheckSideBlockIndex(block1,old_block,ioDivMapCont->MapW)==TRUE){
			AddMapLoad(block1,block2,idx1,idx2,inDirection,ioDivMapCont);
		}else{
#ifdef	DEBUG_ONLY_FOR_saitou		
			OS_Printf("local_print 画面右端なのでロードしない\n");
#endif			
			ioDivMapCont->LocalFreeIndexTable[0] = FALSE;
			ioDivMapCont->LocalFreeIndexTable[2] = FALSE;
		}
*/		
		break;
	case MAP_LOAD_DOWN: //自機が下に移動
		//0,1を解放して2,3を移動
		FreeAndMoveNode(0,1,2,3,ioDivMapCont);
		
		//自機のいるブロックインデックスをキーにして、2,3にはいるブロックを算出
		//0→2、1→3で場合分け

		if (/*左上にいた場合*/ioDivMapCont->NowPosInBlock == 0){
			block1 = inBlockIndex + ioDivMapCont->MapW;
			block2 = inBlockIndex + ioDivMapCont->MapW - 1;
			idx1 = 3;
			idx2 = 2;
			//整合性チェック
			if (ioDivMapCont->MapW*ioDivMapCont->MapH<=block1){	//範囲外
				//真下ブロックはマトリクス内にあるはず
				block1 = NON_BLOCK;
				block2 = NON_BLOCK;
			}else{
				//読み込んだ２ブロックは、同じ行にあるはず
				if ( !CheckRowBlockIndex(block1,block2,ioDivMapCont->MapW) ){	//範囲外
					block2 = NON_BLOCK;
				}
			}
		}else if(/*右上にいた場合*/ioDivMapCont->NowPosInBlock == 1){
			block1 = inBlockIndex + ioDivMapCont->MapW;
			block2 = inBlockIndex + ioDivMapCont->MapW + 1;
			idx1 = 2;
			idx2 = 3;
			//整合性チェック
			if (ioDivMapCont->MapW*ioDivMapCont->MapH<=block1){	//範囲外
				//真下ブロックはマトリクス内にあるはず
				block1 = NON_BLOCK;
				block2 = NON_BLOCK;
			}else{
				//2つめのブロックはマトリクス内で、且つ読み込んだ２ブロックは、同じ行にあるはず
				if ( (ioDivMapCont->MapW*ioDivMapCont->MapH<=block2)||
						(!CheckRowBlockIndex(block1,block2,ioDivMapCont->MapW)) ){	//範囲外
					block2 = NON_BLOCK;
				}
			}
		}else{
			GF_ASSERT(0&&"ERROR:下移動ブロック計算失敗");
		}
/**		
		//整合性チェック
		if ( (block1<0)||(ioDivMapCont->MapW*ioDivMapCont->MapH<=block1) ){
			//範囲外
			block1 = -1;
			block2 = -2;
		}
*/
		//2,3の新規ロード
		AddMapLoad(block1,block2,idx1,idx2,inDirection,ioDivMapCont);
		break;
	default:
		GF_ASSERT(0&&"ERROR:ブロックの解放と作成に失敗");
		break;
	};
#ifdef DEBUG_ONLY_FOR_saitou
	OS_Printf("local_print_new_4_block:%d,%d,%d,%d",
			ioDivMapCont->BlockNodeList[0]->BlockIndex,
			ioDivMapCont->BlockNodeList[1]->BlockIndex,
			ioDivMapCont->BlockNodeList[2]->BlockIndex,
			ioDivMapCont->BlockNodeList[3]->BlockIndex );
#endif	
}

//--------------------------------------------------------------------------------------------
/**
 * ブロック描画
 *
 * @param	inLocalIndex	描画ローカルインデックス(0～3)
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void DrawBlock(	const u8 inLocalIndex,
						DMC_CONST_PTR inDivMapCont,
						const GLST_DATA_PTR	glst_data)
{
	VecFx32 trans = {0, 0, 0};
	CalcMapOffset3D(	inDivMapCont->BlockNodeList[inLocalIndex]->BlockIndex,
						inDivMapCont->MapW,
						inDivMapCont->World,
						&trans);

//床３Ｄ描画
	if (inDivMapCont->BlockNodeList[inLocalIndex]->DrawOKFlg == TRUE){
		VecFx32 scale = {FX32_ONE, FX32_ONE, FX32_ONE};
		MtxFx33 rot	  = {FX32_ONE,0,0,0,FX32_ONE,0,0,0,FX32_ONE};
#ifdef PM_DEBUG		
		if (DebugOutRangeFlg == TRUE){
			simple_3DModelDraw(&(inDivMapCont->BlockNodeList[inLocalIndex]->FloorData),
								&trans,
								&rot,
								&scale);
		}else{
			if (GetInvalidHeightDataFlg(inDivMapCont->BlockNodeList[inLocalIndex]->MapHeightInfo)
																						== TRUE){
				simple_3DModelDraw(&(inDivMapCont->BlockNodeList[inLocalIndex]->FloorData),
									&trans,
									&rot,
									&scale);
			}
		}
#else
		simple_3DModelDraw(&(inDivMapCont->BlockNodeList[inLocalIndex]->FloorData),
							&trans,
							&rot,
							&scale);
#endif
	}

	if(inDivMapCont->BlockNodeList[inLocalIndex]->DrawOKFlg == TRUE){
			M3DO_DrawMap3DObj(	&trans,
								inDivMapCont->MapResource,
								MAPRES_IsValidLight(inDivMapCont->MapResource),
								glst_data,
								inDivMapCont->BlockNodeList[inLocalIndex]->ObjDataList);
	}
}

//--------------------------------------------------------------------------------------------
/**
 * グリッドナンバーからブロックインデックスを取得
 *
 * @param	inGridNo	グリッドナンバー
 *
 * @return	int			ブロックインデックス
 */
//--------------------------------------------------------------------------------------------
static int GetBlockIdxFromGridNo(const u32 inGridNo, const int inMapW, const int inMapGridW)
{
	u32	grid_x,grid_z;
	u32 block_x,block_z;
	int block_index;
	
	grid_x = inGridNo%inMapGridW;
	grid_z = inGridNo/inMapGridW;
	block_x = grid_x / BLOCK_GRID_SIZE_X;
	block_z = grid_z / BLOCK_GRID_SIZE_Z;

	block_index = block_x+block_z*inMapW;
	return block_index;
}

//--------------------------------------------------------------------------------------------
/**
 * グリッド座標を元に、現在立っているグリッドナンバーを返す
 *
 * @param	inGeidX		グリッド座標Ｘ
 * @param	inGridZ		グリッド座標Ｚ
 *
 * @return	int	グリッドナンバー
 */
//--------------------------------------------------------------------------------------------
static int CalcGridNoFromGridXZ(const int inGridX, const int inGridZ, const int inMapGridW)
{
	int grid_no;
	grid_no = inGridX + (inGridZ * inMapGridW);
	return grid_no;
}

//--------------------------------------------------------------------------------------------
/**
 * エリアグリッドナンバーからエリアブロックインデックスを算出
 *
 * @param	inGridIndex		グリッドナンバー
 *
 * @return	u32				ブロックインデックス
 */
//--------------------------------------------------------------------------------------------
static u32 GetBlockIndexFromGridNo(const u32 inGridNo, const int inMapW, const int inMapGridW)
{
	u32	grid_x,grid_z;
	u32 block_x,block_z;
	u32 block_index;
	
	grid_x = inGridNo%inMapGridW;
	grid_z = inGridNo/inMapGridW;
	block_x = grid_x / BLOCK_GRID_SIZE_X;
	block_z = grid_z / BLOCK_GRID_SIZE_Z;

	block_index = block_x+block_z*inMapW;
	return block_index;
}

//--------------------------------------------------------------------------------------------
/**
 * ブロック内位置からローカルインデックスを計算（0～3）
 *
 * @param	inPosInBlock	ブロック内位置(0～3)
 *
 * @return	u8				ローカルインデックス（0～3）
 */
//--------------------------------------------------------------------------------------------
static u8 CalcLocalIdxFromPosInBlock(const u8 inPosInBlock)
{
	//
	if (inPosInBlock == 0){
		return 3;
	}else if (inPosInBlock == 1){
		return 2;
	}else if(inPosInBlock == 2){
		return 1;
	}else if (inPosInBlock == 3){
		return 0;
	}else{
		GF_ASSERT(0&&"ERROR:ブロック内位置が不正");
	}
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * 進もうとしている方向の1グリッド先のグリッドナンバーを取得する
 *
 * @param	inDirection		方向
 *
 * @return	u32				グリッドナンバー
 */
//--------------------------------------------------------------------------------------------
static u32 GetNextGridNo(	const u8 inDirection,
							const int inMapH,
							const int inMapGridW,
							const int inNowGridNo)
{
	u32 grid_next;
	u32 next_block;
	int check;
	
	//現在グリッドから方向にあわせて、次グリッドを計算
	switch(inDirection){
	case  MAP_LOAD_RIGHT:		//右
		check = (inNowGridNo%inMapGridW)+1;
		if ( check >= inMapGridW ){
			OS_Printf("ERROR:EREA_RIGHT_OVER!!\n");
			return inNowGridNo;
		}
		grid_next = inNowGridNo + 1;	
		break;
	case MAP_LOAD_DOWN:			//下
		check = inNowGridNo+inMapGridW;
		if (check >= inMapH*BLOCK_GRID_SIZE_Z*inMapGridW){
			OS_Printf("ERROR:EREA_DOWN_OVER!!\n");
			return inNowGridNo;
		}
		grid_next = inNowGridNo + inMapGridW;
		break;
	case MAP_LOAD_LEFT:			//左
		check = (inNowGridNo%inMapGridW)-1;
		if ( check < 0 ){
			OS_Printf("ERROR:EREA_LEFT_OVER!!\n");
			return inNowGridNo;
		}
		grid_next = inNowGridNo - 1;
		break;
	case MAP_LOAD_UP:			//上
		check = inNowGridNo-inMapGridW;
		if (check < 0 ){
			OS_Printf("ERROR:EREA_UP_OVER!!\n");
			return inNowGridNo;
		}
		grid_next = inNowGridNo - inMapGridW;
		break;
	default:
		GF_ASSERT(0&&"ERROR:NO_DIRECTION!!");
		return 0;
	}
	
	return  grid_next;
}


//--------------------------------------------------------------------------------------------
/**
 * 進行方向から未来のブロック内位置を取得(ブロック以内にいるときのみ使用)
 *
 * @param	inDirection		方向
 *
 * @return	u8				ブロック内位置(0～3)
 */
//--------------------------------------------------------------------------------------------
static u8 GetNextPosInBlock(const u8 inDirection, const int inNowPosInBlock)
{
	u8 pos;
	switch(inDirection){
	case MAP_LOAD_UP:
		pos = inNowPosInBlock-2;
		break;
	case MAP_LOAD_DOWN:
		pos = inNowPosInBlock+2;
		break;
	case MAP_LOAD_LEFT:
		pos = inNowPosInBlock-1;
		break;
	case MAP_LOAD_RIGHT:
		pos = inNowPosInBlock+1;
		break;
	}
	return pos;
}

//--------------------------------------------------------------------------------------------
/**
 * ローカルインデックスを更新
 *
 * @param	inDirection		更新方向
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void UpdateNowLocalIndexForAfterLoad(const u8 inDirection,
											const int inNowPosInBlock,
											u8 *outNowLocalIndex)
{
	u8 pos;
	u8 local_index;
	
	pos = GetNextPosInBlock(inDirection,inNowPosInBlock);
	
	if (inNowPosInBlock<pos){
		if (pos - inNowPosInBlock == 1){
			local_index = (*outNowLocalIndex)-1;			//右
		}else if(pos - inNowPosInBlock == 2){
			local_index = (*outNowLocalIndex)-2;			//下
		}else{
			GF_ASSERT(0&&"ERROR:LOCAL_INDEX_ERROR!");
		}
	}else if(inNowPosInBlock>pos){
		if (inNowPosInBlock - pos == 1){
			local_index = (*outNowLocalIndex)+1;			//右
		}else if(inNowPosInBlock - pos == 2){
			local_index = (*outNowLocalIndex)+2;			//下
		}else{
			GF_ASSERT(0&&"ERROR:LOCAL_INDEX_ERROR!");
		}
	}else{
		//ローカルインデックスの更新なし;
		GF_ASSERT(0&&"ERROR:LOCAL_INDEX_NO_UPDATE!");
	}

	(*outNowLocalIndex) = local_index;
}

//--------------------------------------------------------------------------------------------
/**
 * 正反対の方向を返す
 *
 * @param	inDir	指定方向
 *
 * @return	u8		指定の逆方向
 */
//--------------------------------------------------------------------------------------------
static u8 GetRevDir(const u8 inDir)
{
	switch(inDir){
	case MAP_LOAD_UP:
		return MAP_LOAD_DOWN;
	case MAP_LOAD_DOWN:
		return MAP_LOAD_UP;
	case MAP_LOAD_RIGHT:
		return MAP_LOAD_LEFT;
	case MAP_LOAD_LEFT:
		return MAP_LOAD_RIGHT;
	default:
		GF_ASSERT(0&&"ERROR:方向は識別できない");
		return 0;
	}
}

//--------------------------------------------------------------------------------------------
/**
 * ロード方向と稼動中ローダの方向を比較
 *
 * @param	inDir	方向
 * @param	*outNo	登録番号（0ＯＲ1）
 *
 * @return	BOOL	対方向の有無
 */
//--------------------------------------------------------------------------------------------
static BOOL CompLoadDirection(const u8 inDir, DMC_CONST_PTR inDivMapCont, u8* outNo)
{
	int i;
#ifdef DIV_MAP_LOAD_DEBUG	
	OS_Printf("比較方向%d\n",inDir);
#endif	
	//現在リクエストのかかっているロード方向と稼動中タスクの方向を比較
	for (i=0;i<2;i++){
#ifdef DIV_MAP_LOAD_DEBUG		
		OS_Printf("タスク管理方向%d",inDivMapCont->MLBC[i].LoadDir);
#endif
		//タスク稼動中？
		if (inDivMapCont->MLBC[i].Moving == TRUE){
			if (GetRevDir(inDir) == inDivMapCont->MLBC[i].LoadDir){
				*outNo = i;
				return TRUE;	//対方向があった
			}
		}
	}

	//対方向がなかった
	return FALSE;
}

//--------------------------------------------------------------------------------------------
/**
 * ストック用ブロックロードリクエスト
 * ロード境界でブロックデータを登録した際、処理が積まれていて、ロードがすぐにできないときデータがストックされます
 * そのストックされたデータを処理する処理
 * 
 *
 * @param	*inStock	ストックデータ
 * @param	inBlankNo	登録空き番号
 *
 * @return	BOOL	登録成功有無	TRUE:成功　FALSE:失敗
 */
//--------------------------------------------------------------------------------------------
static BOOL BlockLoadReqestForStock(DMC_PTR ioDivMapCont)
{
	STOCK_LOAD_DATA *stock = &ioDivMapCont->Stock;
	
	if (ioDivMapCont->MLBC[ioDivMapCont->BlankNo].Moving != FALSE){
		//稼動中タスクに登録しようとしているのでエラーとする
		GF_ASSERT(0&&"ERROR:稼動中なのに登録しようとしている");
	}

	//稼動中にする
	ioDivMapCont->MLBC[ioDivMapCont->BlankNo].Moving = TRUE;

	//ロード方向保存
	ioDivMapCont->MLBC[ioDivMapCont->BlankNo].LoadDir = stock->LoadDir;
	
	ioDivMapCont->MLBC[ioDivMapCont->BlankNo].MLBS.Block[0] = stock->Block[0];
	ioDivMapCont->MLBC[ioDivMapCont->BlankNo].MLBS.Block[1] = stock->Block[1];
	ioDivMapCont->MLBC[ioDivMapCont->BlankNo].MLBS.Index[0] = stock->Index[0];
	ioDivMapCont->MLBC[ioDivMapCont->BlankNo].MLBS.Index[1] = stock->Index[1];
	
	ioDivMapCont->MLBC[ioDivMapCont->BlankNo].MLBS.Node[0] = stock->Node[0];
	ioDivMapCont->MLBC[ioDivMapCont->BlankNo].MLBS.Node[1] = stock->Node[1];

	ioDivMapCont->MLBC[ioDivMapCont->BlankNo].MLBS.TotalCount = 0;
	ioDivMapCont->MLBC[ioDivMapCont->BlankNo].MLBS.BlockLoadOK = FALSE;
	
	return TRUE;
}

//--------------------------------------------------------------------------------------------
/**
 * ストック用マップロード
 *
 * @param	*inStock
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void AddMapLoadForStock(DMC_PTR ioDivMapCont)
{
	int i;
	BOOL rc;
	STOCK_LOAD_DATA *stock = &ioDivMapCont->Stock;
	if (ioDivMapCont->MovingNum>=2){
		GF_ASSERT(0&&"ERROR:3つ目");
	}
	rc = BlockLoadReqestForStock(ioDivMapCont/*stock,ioDivMapCont->BlankNo*/);
#ifdef DIV_MAP_LOAD_DEBUG	
	OS_Printf("ストックを%dにタスク登録\n",ioDivMapCont->BlankNo);
#endif
	//管理タスクがいっぱいなのに、リクエストがかかった場合、エラーとしとく
	GF_ASSERT((rc == TRUE)&&"ERROR:管理タスクがいっぱい");
	
	stock->Node[0]->BlockIndex = stock->Block[0];
	stock->Node[1]->BlockIndex = stock->Block[1];
		
	ioDivMapCont->MovingNum++;
	ioDivMapCont->BlankNo = (ioDivMapCont->BlankNo+1)%2;
}

//--------------------------------------------------------------------------------------------
/**
 * ロード終了監視関数
 *
 * @param	inNo		登録番号(0ＯＲ1)
 *
 * @return	BOOL		TRUE:終了　FALSE:ロード継続
 */
//--------------------------------------------------------------------------------------------
static BOOL IsFinishedLoadBlock(DMC_CONST_PTR inDivMapCont)
{
	return inDivMapCont->MLBC[inDivMapCont->NowMovingNo].MLBS.BlockLoadOK;
}

//--------------------------------------------------------------------------------------------
/**
 * フリーブロック管理テーブルをクリアする
 *
 * @param	none
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void ClearLocalFreeIndexTable(DMC_PTR outDivMapCont)
{
	u8 i;
	for(i=0;i<4;i++){
		outDivMapCont->LocalFreeIndexTable[i] = FALSE;
	}
}

//--------------------------------------------------------------------------------------------
/**
 * 方向からフリーブロックをマーキングする
 *
 * @param	inDir	方向
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void MarkLocalFreeIndexTableByDir(const u8 inDir, DMC_PTR outDivMapCont)
{
	switch(inDir){
	case MAP_LOAD_UP:
		outDivMapCont->LocalFreeIndexTable[2] = TRUE;
		outDivMapCont->LocalFreeIndexTable[3] = TRUE;
		break;
	case MAP_LOAD_RIGHT:
		outDivMapCont->LocalFreeIndexTable[0] = TRUE;
		outDivMapCont->LocalFreeIndexTable[2] = TRUE;
		break;
	case MAP_LOAD_DOWN:
		outDivMapCont->LocalFreeIndexTable[0] = TRUE;
		outDivMapCont->LocalFreeIndexTable[1] = TRUE;
		break;
	case MAP_LOAD_LEFT:
		outDivMapCont->LocalFreeIndexTable[1] = TRUE;
		outDivMapCont->LocalFreeIndexTable[3] = TRUE;
		break;
	}
}

//==============================================================================
/**
 * エリアデータのロード
 *
 * @param   inGridX		グリッド座標Ｘ
 * @param	inGridZ		グリッド座標Ｚ
 * 
 * @retval  none		
 */
//==============================================================================
static void LoadFirstBlock(	DMC_PTR outDivMapCont,
							const int inGridX, 
							const int inGridZ,
							const int inMapGridW)
{
	u8 i;
	int start_block[4];

	//4ブロックのデータ読込先を確保
	AllocBlockList(outDivMapCont);

	//初期ブロックをグリッドから割り出す
	MakeStartBlockTbl(	inGridX, inGridZ,
						outDivMapCont->MapW,
						outDivMapCont->MapH,
						inMapGridW, start_block	);

	for(i=0;i<4;i++){
		//高さデータ管理構造体メモリ確保
		outDivMapCont->BlockNodeList[i]->MapHeightInfo = AllocMapHeightInfo();
		InitHeightData(outDivMapCont->BlockNodeList[i]->MapHeightInfo);	//高さデータ管理構造体初期化
		LoadBlockQuick(	start_block[i],
						i,
						outDivMapCont->MapResource,
						outDivMapCont->World,
						outDivMapCont->MapW,
						outDivMapCont->MapH,
						MAPRES_IsValidLight(outDivMapCont->MapResource),
						outDivMapCont);//4ブロック分のデータ読み込み
		/**
		//コールバック呼び出し
		if (outDivMapCont->CallBack!=NULL){
			outDivMapCont->CallBack(	outDivMapCont->CallBackWork,
										start_block[i],
										outDivMapCont->BlockNodeList[i]->ObjDataList);
		}*/
	}
}

//==============================================================================
/**
 * エリアデータのロード
 *
 * @param   inGridX		グリッド座標Ｘ
 * @param	inGridZ		グリッド座標Ｚ
 * 
 * @retval  none		
 */
//==============================================================================
static void LoadFirstBlockForUnder(	DMC_PTR outDivMapCont,
									const int inGridX, 
									const int inGridZ,
									const int inMapGridW)
{
	u8 i;
	int start_block[4];
	
	//4ブロックのデータ読込先を確保
	AllocBlockListForUnder(outDivMapCont);

	//初期ブロックをグリッドから割り出す
	MakeStartBlockTbl(	inGridX, inGridZ,
						outDivMapCont->MapW,
						outDivMapCont->MapH,
						inMapGridW, start_block);

	for(i=0;i<4;i++){
		//高さデータ管理構造体NULLセット
		outDivMapCont->BlockNodeList[i]->MapHeightInfo = NULL;
		LoadBlockQuickForUnder(	start_block[i],
								i,
								outDivMapCont->MapResource,
								outDivMapCont->World,
								outDivMapCont->MapW,
								outDivMapCont->MapH,
								MAPRES_IsValidLight(outDivMapCont->MapResource),
								outDivMapCont);//4ブロック分のデータ読み込み
	}
}


//==============================================================================
/**
 * 初期化
 *
 * @param	outDivMapCont	分割マップ構造体ポインタ
 *
 * @return	none
 */
//==============================================================================
static void InitMapLoadCont(DMC_PTR outDivMapCont)
{
	int i;

	outDivMapCont->NowMovingNo = 0;
	outDivMapCont->BlankNo = 0;
	outDivMapCont->MovingNum = 0;
	for(i=0;i<2;i++){
		outDivMapCont->MLBC[i].Moving = FALSE;
		outDivMapCont->MLBC[i].MLBS.BlockLoadOK = TRUE;
	}
	ClearLocalFreeIndexTable(outDivMapCont);
}

//==============================================================================
/**
 * 座標で現在情報を更新
 *
 * @param   inGridX		グリッド座標Ｘ
 * @param	inGridZ		グリッド座標Ｚ
 *
 * @return	none
 */
//==============================================================================
static void UpdateNowData(const int inGridX, const int inGridZ, DMC_PTR outDivMapCont)
{
	outDivMapCont->NowGridNo = CalcGridNoFromGridXZ(inGridX,inGridZ,outDivMapCont->MapGridW);
	outDivMapCont->NowPosInBlock = CalcPositionInBlockFromGridNo(outDivMapCont->NowGridNo,
													outDivMapCont->MapGridW);
	outDivMapCont->NowLocalIndex = CalcLocalIdxFromPosInBlock(outDivMapCont->NowPosInBlock);
	outDivMapCont->NowBlockIndex = GetBlockIndexFromGridNo(outDivMapCont->NowGridNo,
															outDivMapCont->MapW,
															outDivMapCont->MapGridW);
#ifdef DIV_MAP_LOAD_DEBUG
	OS_Printf("Now=%d,%d,%d,%d\n",	outDivMapCont->NowGridNo,
									outDivMapCont->NowPosInBlock,
									outDivMapCont->NowLocalIndex,
									outDivMapCont->NowBlockIndex);
#endif
}

//==============================================================================
/**
 * ブロックインデックスから地形オフセットを計算(高さベースも求める)
 *
 * @param   inBlockIndex	ブロックインデックス
 * @param	inMapW			マップ幅
 * @param	inWorld			ワールド構造体へのポインタ
 * @param	outTrans		格納座標
 * 
 * @return	none
 */
//==============================================================================
static void CalcMapOffset3D(	const int inBlockIndex,
								const int inMapW,
								const WORLD_MAP_PTR inWorld,
								VecFx32 *outTrans)
{
	u16 x_ofs;
	u16 z_ofs;
	outTrans->x = (BLOCK_GRID_SIZE_X/2)*ONE_GRID_SIZE*FX32_ONE;
	outTrans->z = (BLOCK_GRID_SIZE_Z/2)*ONE_GRID_SIZE*FX32_ONE;

	if (inBlockIndex == NON_BLOCK){
		return ;
	}
	
	x_ofs = inBlockIndex % inMapW;
	z_ofs = inBlockIndex / inMapW;
	{
		int height_base;
		int w;
		u16 matrix_id;
		w = GetWorldMapMatrixW(inWorld);
		matrix_id = GetWorldMatrixID(inWorld);
		height_base = GetHeightBaseFromMatrixID(inWorld, matrix_id, x_ofs, z_ofs, w);
		outTrans->y = height_base*HARF_GRID_SIZE*FX32_ONE;
	}
	outTrans->x += x_ofs*BLOCK_GRID_SIZE_X*ONE_GRID_SIZE*FX32_ONE;
	outTrans->z += z_ofs*BLOCK_GRID_SIZE_Z*ONE_GRID_SIZE*FX32_ONE;
}


//-----------------------------------------------------------------------------------------
//	アクセス関数
//-----------------------------------------------------------------------------------------
//==============================================================================
/**
 * 初期化
 *
 * @param   world	ワールド構造体ポインタ	
 * @retval  none		
 */
//==============================================================================
DMC_PTR InitDivMap(	WORLD_MAP_PTR world,
					MAP_RESOURCE_PTR mapresource,
					FLD_3D_ANM_MNG_PTR inFld3DAnmPtr,
					const DIV_MAP_MODE inMode )
///					DFL_CONST_PTR ioFuncList,
///					const int inGroundMemSize,
///					const int inHeightMemSize)
{
	DMC_PTR map_cont_ptr;
	BOOL height_data_valid;

	//マップコントロールデータ確保
	map_cont_ptr = sys_AllocMemory( HEAPID_FIELD, sizeof(DIV_MAP_LOAD_CONT) );
	//確保領域のクリーン
	MI_CpuClear8( map_cont_ptr, sizeof(DIV_MAP_LOAD_CONT));

	//モード分岐
	if (inMode == DIV_MAP_MODE_GROUND){				//地上
		map_cont_ptr->FuncList = &DivGroundFunc;
		height_data_valid = TRUE;
	}else if(inMode == DIV_MAP_MODE_UNDER){			//地下
		map_cont_ptr->FuncList = &DivUnderFunc;
		height_data_valid = FALSE;
	}else{
		GF_ASSERT(0&&"ERROR:マップが特定できない");
	}
	
	//マップが使用するメモリ（地形データ等）を確保
	map_cont_ptr->FldMapMem = AllocFldMapMem(height_data_valid);
	//フィールド共通リソースのポインタをセット
	map_cont_ptr->MapResource = mapresource;
	map_cont_ptr->World = world;
	
	//マップ縦横情報セット
	map_cont_ptr->MapW = GetWorldMapMatrixW(world);
	map_cont_ptr->MapH = GetWorldMapMatrixH(world);
	map_cont_ptr->MapGridW = map_cont_ptr->MapW*BLOCK_GRID_W;

	//フィールド3Ｄアニメマネージャポインタセット
	map_cont_ptr->Field3DAnmPtr = inFld3DAnmPtr;

	map_cont_ptr->MapCheck.Valid = TRUE;
		
	//マップ管理タスク初期化
	InitMapLoadCont(map_cont_ptr);
/**
	//分割マップセットアップ、ロード方式をｆｓｙｓからもらう
	map_cont_ptr->FuncList = ioFuncList;
*/	

	map_cont_ptr->FreeRequest = FALSE;

	map_cont_ptr->LoadSeq = DML_NONE;
	//アーカイブハンドルの取得
	map_cont_ptr->ArcHandle = ArchiveDataHandleOpen( ARC_FIELD_MAP_DATA, HEAPID_FIELD );

#ifdef DIV_CALL_BACK
	//コールバック初期化
	map_cont_ptr->CallBack = NULL;
#endif
	
#ifdef PM_DEBUG
	DebugOutRangeFlg = TRUE;
#endif
	
	return map_cont_ptr; 
}

//==============================================================================
/**
 * マップ読み込み
 *
 * @param   none		
 * @retval  none		
 */
//==============================================================================
void LoadDivMap(DMC_PTR outDivMapCont, const int x, const int z)
{
	//4つブロックロード
/*
	DivMapLoad_LoadErea(outDivMapCont,
						x,
						z,
						outDivMapCont->MapW,
						outDivMapCont->MapGridW,
						inLightValid);<<table_func	
*/
	outDivMapCont->FuncList->DivFirstFunc(	outDivMapCont,
											x,
											z,
											outDivMapCont->MapGridW);
	//自機の初期グリッドを登録
	UpdateNowData(x,z,outDivMapCont);
}

//==============================================================================
/**
 * ブロックデータの更新（自機が、動き出したときに呼ぶ）
 *
 * @param	inDirection		方向
 *
 * @return	none
 */
//==============================================================================
void DivMapLoad_UpdateBlockData(const u8 inDirection, DMC_PTR ioDivMapCont)
{
	int next_block;
	u32 next_grid;
	u8 pos;
	
	next_grid = GetNextGridNo(	inDirection,
								ioDivMapCont->MapH,
								ioDivMapCont->MapGridW,
								ioDivMapCont->NowGridNo);

	next_block = GetBlockIdxFromGridNo(next_grid,ioDivMapCont->MapW, ioDivMapCont->MapGridW);
	pos = CalcPositionInBlockFromGridNo(next_grid,ioDivMapCont->MapGridW);
	//ブロック間移動が行われるかをチェック
	if (ioDivMapCont->NowBlockIndex != next_block){
		return;	//ブロック間移動の場合はロードなし
	}else{	//ブロック内移動
		if (ioDivMapCont->NowPosInBlock != pos){	//ブロック内位置が異なる
			//ブロックロード
			UpdateBlockList(next_block, inDirection, ioDivMapCont);
			//ブロック更新が行われるので、ローカルインデックスを更新する
			UpdateNowLocalIndexForAfterLoad(inDirection,
											ioDivMapCont->NowPosInBlock,
											&(ioDivMapCont->NowLocalIndex));
		}
	}
}

//==============================================================================
/**
 * ブロック描画関数
 *
 * @param	none
 *
 * @return	none
 */
//==============================================================================
void DrawAroundBlock(	DMC_CONST_PTR inDivMapCont,
						const GLST_DATA_PTR glst_data)
{
	static u8 debug_trg_alias = 0;
	
	u8 i;
	u8 draw = 0;	//描画するローカルブロックインデックスを配列として持つテーブルの参照インデックス

	//4ブロックの描画
	for(i=0;i<4;i++){
		///debag_count_b[i] = 0;
		if (inDivMapCont->BlockNodeList[i]->BlockIndex != NON_BLOCK){
			DrawBlock(i,inDivMapCont,glst_data);
		}
	}
	
#ifdef DEBUG_ONLY_FOR_saitou	
	
	if (sys.trg & PAD_BUTTON_L){
/**		
		OS_Printf("ALL_MODEL:%d\n",debag_all_count);
		OS_Printf("DRAW_MODEL:%d\n",debag_draw_count);		
		OS_Printf("DRAW_MODEL_B:%d,%d,%d,%d\n",
				debag_count_b[0],debag_count_b[1],debag_count_b[2],debag_count_b[3]);
*/
//デバッグ用プリント
		OS_Printf("0:WorldHeap = %ld\n",sys_GetHeapFreeSize(HEAPID_WORLD));
		OS_Printf("1:FieldHeap = %ld\n",sys_GetHeapFreeSize(HEAPID_FIELD));
	}

#endif
}

//==============================================================================
/**
 * 進もうとしている方向の1グリッド先のグリッドがエリア内かを判定する
 *
 * @param	inDirction	方向
 * @param	*outGrid	進もうとしている方向の1グリッド先のグリッド
 * @return	none
 */
//==============================================================================
BOOL CheckNextGridIO(const u8 inDirection, DMC_CONST_PTR inDivMapCont, int *outGrid)
{
	int next_grid;
	
	//現在グリッドから方向にあわせて、次グリッドを計算
	switch(inDirection){
	case  MAP_LOAD_RIGHT:		//右
		next_grid = (inDivMapCont->NowGridNo%inDivMapCont->MapGridW)+1;
		if ( next_grid >= inDivMapCont->MapGridW ){
			return FALSE;
		}
		*outGrid = inDivMapCont->NowGridNo+1;
		break;
	case MAP_LOAD_DOWN:			//下
		*outGrid = inDivMapCont->NowGridNo+inDivMapCont->MapGridW;
		if (*outGrid >= inDivMapCont->MapH*BLOCK_GRID_SIZE_Z*inDivMapCont->MapGridW){
			return FALSE;
		}
		break;
	case MAP_LOAD_LEFT:			//左
		next_grid = (inDivMapCont->NowGridNo%inDivMapCont->MapGridW)-1;
		if ( next_grid < 0 ){
			return FALSE;
		}
		*outGrid = inDivMapCont->NowGridNo-1;
		break;
	case MAP_LOAD_UP:			//上
		*outGrid = inDivMapCont->NowGridNo-inDivMapCont->MapGridW;
		if (*outGrid < 0 ){
			return FALSE;
		}
		break;
	default:
		GF_ASSERT(0&&"ERROR:NO_DIRECTION!!");
	}
	return  TRUE;
}

//==============================================================================
/**
 * 座標を元に、現在立っているグリッドXZを返す
 *
 * @param   inX				座標Ｘ
 * @param	inZ				座標Ｚ
 * @param   outGridX		グリッド座標Ｘ
 * @param	outGridZ		グリッド座標Ｚ
 *
 * @return	none
 */
//==============================================================================
void GetGridXZ(fx32 inX, fx32 inZ, int *outGridX, int *outGridZ)
{
	*outGridX = inX/(ONE_GRID_SIZE*FX32_ONE);
	*outGridZ = inZ/(ONE_GRID_SIZE*FX32_ONE);
}

//==============================================================================
/**
 * 確保メモリの解放
 *
 * @param	none
 *
 * @return	none
 */
//==============================================================================
void DivMapLoad_FreeMap(DMC_PTR ioDivMapCont)
{
	u8 i;

	//キャッシュクリア
	ClearFileCache();
	
#ifdef LINK_VRAM_MANAGER
	NNS_GfdResetLnkTexVramState();
	NNS_GfdResetLnkPlttVramState();
#else
	//テクスチャ、パレット開放
	NNS_GfdResetFrmTexVramState();
	NNS_GfdResetFrmPlttVramState();
#endif

	//ロードタスク中止リクエスト
	for(i=0;i<2;i++){
		LoadTaskStopReqestByMLBS(&ioDivMapCont->MLBC[i].MLBS);
	}
#if 0
	//アーカイブハンドルを解放
	if (ioDivMapCont->ArcHandle != NULL){
		ArchiveDataHandleClose( ioDivMapCont->ArcHandle );
		ioDivMapCont->ArcHandle = NULL;
	}
#endif
	//ブロックデータ解放(地形データの解放、マップ高さデータ開放を含む)
	for (i=0;i<4;i++){
		ioDivMapCont->BlockNodeList[i]->DrawOKFlg = FALSE;

		FreeMapHeightInfo(ioDivMapCont->BlockNodeList[i]->MapHeightInfo);
		//3DOBJ解放
		M3DO_FreeMap3DObjList(ioDivMapCont->BlockNodeList[i]->ObjDataList );
		sys_FreeMemoryEz( ioDivMapCont->BlockNodeList[i] );
		ioDivMapCont->BlockNodeList[i] = NULL;
	}

	ioDivMapCont->LoadSeq = DML_FREE_WAIT;
	ioDivMapCont->FreeRequest = TRUE;

	ioDivMapCont->MapCheck.Valid = FALSE;
}

//==============================================================================
/**
 * 確保メモリの解放
 *
 * @param	none
 *
 * @return	none
 */
//==============================================================================
void FreeDivMapCont(DMC_PTR outDivMapCont)
{
	//アーカイブハンドルクローズ
	ArchiveDataHandleClose( outDivMapCont->ArcHandle );	
	//マップメモリ解放
	FreeFldMapMem(outDivMapCont->FldMapMem);
	//マップ管理データ解放
	sys_FreeMemoryEz( (void *)outDivMapCont );
	///outDivMapCont = NULL;
}

//==============================================================================
/**
 * 確保メモリの解放待ち
 *
 * @param	none
 *
 * @return	none
 */
//==============================================================================
BOOL WaitMapFree(DMC_CONST_PTR inDivMapCont)
{
	if ( (inDivMapCont->FreeRequest == TRUE) && (inDivMapCont->MovingNum == 0) ){
		return TRUE;
	}else{
		return FALSE;
	}
}

//==============================================================================
/**
 * 座標のバインド
 *
 * @param	*inTarget	座標
 * @param   outDivMapCont　分割マップ構造体
 *
 * @return	none
 */
//==============================================================================
void DivMapBindTarget(VecFx32 const *inTarget, DMC_PTR outDivMapCont)
{
	outDivMapCont->MapCheck.OldPoint = *inTarget;
	outDivMapCont->MapCheck.TargetPoint = inTarget;
}

//==============================================================================
/**
 * 座標の切り離し
 *
 * @param   outDivMapCont　分割マップ構造体
 *
 * @return	none
 */
//==============================================================================
void DivMapPurgeTarget(DMC_PTR outDivMapCont)
{
	outDivMapCont->MapCheck.TargetPoint = NULL;
}

//==============================================================================
/**
 * 指定ローカルブロックインデックスからオブジェクト構造体リストを返す
 *
 * @param   outDivMapCont　分割マップ構造体
 *
 * @return	none
 */
//==============================================================================
void Get3DObjListFromLocalIdx(const u8 inIdx, DMC_CONST_PTR inDivMapCont, M3DOL_PTR *outObjList)
{
	*outObjList = inDivMapCont->BlockNodeList[inIdx]->ObjDataList;
}

//==============================================================================
/**
 * 現在のブロックローカルインデックスを取得
 *
 * @param   outDivMapCont　分割マップ構造体
 *
 * @return	none
 */
//==============================================================================
u8 GetNowLocalIndex(DMC_CONST_PTR inDivMapCont)
{
	return inDivMapCont->NowLocalIndex;
}

//==============================================================================
/**
 * 現在のブロックインデックスを取得
 *
 * @param   outDivMapCont　分割マップ構造体
 *
 * @return	none
 */
//==============================================================================
int GetNowBlockIndex(DMC_CONST_PTR inDivMapCont)
{
	return inDivMapCont->NowBlockIndex;
}

//--------------------------------------------------------------------------------------------
/**
 * 現在グリッドインデックスから、ブロックのどの位置（4分割したとき）にいるかを計算
 *
 * @param	inGridNo	グリッドナンバー
 *
 * @return	u8			ブロック内位置(0～3)
 */
//--------------------------------------------------------------------------------------------
u8 CalcPositionInBlockFromGridNo(const u32 inGridNo, const int inMapGridW)
{
	u8 pos;
	int pos_x,pos_z;
	int line_z;
	pos_x = inGridNo%BLOCK_GRID_SIZE_X;
	line_z = inGridNo/inMapGridW;
	pos_z = line_z%BLOCK_GRID_SIZE_Z;
	if (pos_x < BLOCK_GRID_SIZE_X/2){
		if (pos_z < BLOCK_GRID_SIZE_Z/2){
			pos = 0;	//ブロック左上
		}else{
			pos = 2;	//ブロック左下
		}
	}else{
		if (pos_z < BLOCK_GRID_SIZE_Z/2){
			pos = 1;	//ブロック右上
		}else{
			pos = 3;	//ブロック右下
		}
	}
	return pos;
}

//--------------------------------------------------------------------------------------------
/**
 * ブロックインデックスからローカルインデックスを計算（上下左右のみ）
 *
 * @param	inBlockIndex		ブロックインデックス
 * @param	inPosInBlock		ブロック内位置(0～3)
 *
 * @return	u8					ローカルインデックス
 */
//--------------------------------------------------------------------------------------------
u8 CalcLocalIdxFromBlockIdx(const int inBlockIndex, const u8 inPosInBlock, DMC_CONST_PTR inDivMapCont)
{
	u8 local_index;
#ifdef DIV_MAP_LOAD_DEBUG	
	OS_Printf("inPosInBlock=%d\n",inPosInBlock);
#endif
	if (inDivMapCont->NowBlockIndex == inBlockIndex){
		return inDivMapCont->NowLocalIndex;
	}

	GF_ASSERT(inBlockIndex!=NON_BLOCK);
	
	switch (inDivMapCont->NowLocalIndex){
	case 0:															//自機が左上にいるとき
		//MapWが１のときを考え優先して判定する
		if(inBlockIndex - inDivMapCont->NowBlockIndex == inDivMapCont->MapW){
			local_index = inDivMapCont->NowLocalIndex+2;			//下
		}else if ( (inBlockIndex - inDivMapCont->NowBlockIndex == 1) &&
				(CheckRowBlockIndex( inDivMapCont->NowBlockIndex, inBlockIndex, inDivMapCont->MapW)) ){
			//横並びであれば、ＯＫ
			local_index = inDivMapCont->NowLocalIndex+1;			//右
		}else if ( (inBlockIndex - inDivMapCont->NowBlockIndex == inDivMapCont->MapW+1) &&
				(!CheckRowBlockIndex( inDivMapCont->NowBlockIndex, inBlockIndex, inDivMapCont->MapW)) ){
			//横並びでなければ　ＯＫ
			local_index = inDivMapCont->NowLocalIndex+3;			//右下
		}else{
			local_index = 4;		//識別不可
		}
		break;
	case 1:															//自機が右上にいるとき
		//MapWが１のときを考え優先して判定する
		if(inBlockIndex - inDivMapCont->NowBlockIndex == inDivMapCont->MapW){
			local_index = inDivMapCont->NowLocalIndex+2;			//下
		}else if ( (inDivMapCont->NowBlockIndex - inBlockIndex == 1) &&
				(CheckRowBlockIndex( inDivMapCont->NowBlockIndex, inBlockIndex, inDivMapCont->MapW)) ){
			//横並びであれば、ＯＫ
			local_index = inDivMapCont->NowLocalIndex-1;			//左
		}else if ( (inBlockIndex - inDivMapCont->NowBlockIndex == inDivMapCont->MapW-1) &&
				(!CheckRowBlockIndex( inDivMapCont->NowBlockIndex, inBlockIndex, inDivMapCont->MapW)) ){
			//横並びでなければ　ＯＫ
			local_index = inDivMapCont->NowLocalIndex+1;			//左下
		}else{
			local_index = 4;		//識別不可

		}
		break;
	case 2:															//自機が左下にいるとき
		//MapWが１のときを考え優先して判定する
		if (inDivMapCont->NowBlockIndex - inBlockIndex == inDivMapCont->MapW){
			local_index = inDivMapCont->NowLocalIndex-2;			//上
		}else if( (inDivMapCont->NowBlockIndex - inBlockIndex == inDivMapCont->MapW-1) &&
				(!CheckRowBlockIndex( inDivMapCont->NowBlockIndex, inBlockIndex, inDivMapCont->MapW)) ){
			//横並びでなければ、ＯＫ
			local_index = inDivMapCont->NowLocalIndex-1;			//右上
		}else if ( (inBlockIndex - inDivMapCont->NowBlockIndex == 1) &&
				(CheckRowBlockIndex( inDivMapCont->NowBlockIndex, inBlockIndex, inDivMapCont->MapW)) ){
			//横並びであればＯＫ
			local_index = inDivMapCont->NowLocalIndex+1;			//右
		}else{
			local_index = 4;		//識別不可

		}
		break;
	case 3:															//自機が右下にいるとき
		//MapWが１のときを考え優先して判定する
		if(inDivMapCont->NowBlockIndex - inBlockIndex == inDivMapCont->MapW){
			local_index = inDivMapCont->NowLocalIndex-2;			//上
		}else if ( (inDivMapCont->NowBlockIndex - inBlockIndex == inDivMapCont->MapW+1) &&
				(!CheckRowBlockIndex( inDivMapCont->NowBlockIndex, inBlockIndex, inDivMapCont->MapW)) ){
			//横並びでなければ、ＯＫ
			local_index = inDivMapCont->NowLocalIndex-3;			//左上
		}else if ( (inDivMapCont->NowBlockIndex- inBlockIndex == 1) &&
				(CheckRowBlockIndex( inDivMapCont->NowBlockIndex, inBlockIndex, inDivMapCont->MapW)) ){
			//横並びであればＯＫ
			local_index = inDivMapCont->NowLocalIndex-1;			//左
		}else{
			local_index = 4;		//識別不可

		}
		break;
	default:
		local_index = 4;		//識別不可

	}
	
	return local_index;
}

//==============================================================================
/**
 * ローカルインデックスからブロックインデックスを取得
 *
 * @param   inDivMapCont　分割マップ構造体
 *
 * @return	int		ブロックインデックス
 */
//==============================================================================
int GetBlockIndexFromLocalIndex(DMC_CONST_PTR inDivMapCont, const u8 inLocalIndex)
{
	GF_ASSERT(inLocalIndex<4);
	return inDivMapCont->BlockNodeList[inLocalIndex]->BlockIndex;
}

//==============================================================================
/**
 * ブロック内外判定
 *
 * @param   outDivMapCont　分割マップ構造体
 *
 * @return	none
 */
//==============================================================================
BOOL CheckFourBlockIO(DMC_CONST_PTR inDivMapCont, const int inGridX, const int inGridZ, u8 *outLocalIndex)
{
	u32 block_x,block_z;
	u32 block_index;
	u32 local_index;

	u32 grid_no;
	u8 pos_in_block;
	
	block_x = inGridX / BLOCK_GRID_W;
	block_z = inGridZ / BLOCK_GRID_H;
	block_index = block_x+(block_z*inDivMapCont->MapW);

    if(!(block_index < inDivMapCont->MapW*inDivMapCont->MapH)){
        if(CommStateSetError(COMM_ERROR_RESET_SAVEPOINT)){
            return FALSE;
        }
    }
	GF_ASSERT(block_index < inDivMapCont->MapW*inDivMapCont->MapH);
	
	grid_no = inGridX+(inGridZ*inDivMapCont->MapGridW);
	pos_in_block = CalcPositionInBlockFromGridNo(grid_no,inDivMapCont->MapGridW);
	local_index = CalcLocalIdxFromBlockIdx(block_index,pos_in_block,inDivMapCont);

	if (outLocalIndex != NULL){
		*outLocalIndex = local_index;
	}
	
	if (local_index>3){
		return FALSE;
	}else{
		return TRUE;
	}
}

//==============================================================================
/**
 * 分割マップ構造体を介して、高さ情報取得
 *
 * @param   outDivMapCont　分割マップ構造体
 *
 * @return	none
 */
//==============================================================================
MHI_CONST_PTR GetDivMapHeightInfo(DMC_CONST_PTR inDivMapCont, const u8 inLocalIndex)
{
	return inDivMapCont->BlockNodeList[inLocalIndex]->MapHeightInfo;
}

//==============================================================================
/**
 * 分割マップ構造体を介して、アトリビュート取得
 *
 * @param   outDivMapCont　分割マップ構造体
 *
 * @return	none
 */
//==============================================================================
u16 const *GetDivMapAttribute(DMC_CONST_PTR inDivMapCont, const u8 inLocalIndex)
{
	return inDivMapCont->BlockNodeList[inLocalIndex]->Attribute;
}

/**
void SetUpDivFuncList(FIELDSYS_WORK *fsys, const u8 inMode)
{
	if (inMode == DIV_MAP_MODE_GROUND){
		fsys->div_func_list = &DivGroundFunc;
	}else if (inMode == DIV_MAP_MODE_UNDER){
		fsys->div_func_list = &DivUnderFunc;
	}else{
		GF_ASSERT( 0 && "Mapmode unknown " );
	}
}
*/
#ifdef DIV_CALL_BACK
void DIVM_SetLoadCallBack( DMC_PTR outDivMapCont, DIV_LOAD_CALL_BACK call_back, void *work )
{
	outDivMapCont->CallBack = call_back;
	outDivMapCont->CallBackWork = work;
}
#endif

typedef struct MODEL_SET_DAT_tsg
{
	ARCHANDLE *ArcHandle;
	int DataSize;
	NNSG3dRenderObj* Object_p;
	NNSG3dResFileHeader** ResFile;
	NNSG3dResTex*        Texture;
	u8 SetSeq;
	BOOL	*DrawOK;
	BOOL	StopFlg;
	int * EndFlg;

	u32 data_trans_offset;
}MODEL_SET_DAT;

static void StopMapLoadTaskRequest(TCB_PTR tcb)
{
	MODEL_SET_DAT *model_set_dat;
	model_set_dat = (MODEL_SET_DAT*)TCB_GetWork(tcb);
	model_set_dat->StopFlg = TRUE;
}


static void SetModel(TCB_PTR tcb,void* work)
{
	int i;
	MODEL_SET_DAT *model_set_dat;
	BOOL status;
	int read_size;
	void *mem;
	
	model_set_dat = (MODEL_SET_DAT*)work;
	

	if (model_set_dat->StopFlg == TRUE){
		//強制中断
		model_set_dat->SetSeq = MODELSET_TASK_SEQ_EXIT;
	}
	switch(model_set_dat->SetSeq){

	case MODELSET_TASK_SEQ_INIT:

		model_set_dat->data_trans_offset = 0;
		if (model_set_dat->DataSize<=MODEL_SET_DIV_SIZE){
			//分割量以下の場合
			read_size = model_set_dat->DataSize;
			model_set_dat->SetSeq = MODELSET_TASK_SEQ_TEXTURE_BIND;
		}else{
			//分割量より大きい場合
			read_size = MODEL_SET_DIV_SIZE;
			model_set_dat->SetSeq = MODELSET_TASK_SEQ_MODEL_LOAD;
		}

		mem = &((u8*)(*model_set_dat->ResFile))[model_set_dat->data_trans_offset];
		ArchiveDataLoadByHandleContinue( model_set_dat->ArcHandle, read_size, mem );
		model_set_dat->data_trans_offset+=read_size;
		
		break;

	case MODELSET_TASK_SEQ_MODEL_LOAD:
		{
			int end;
			read_size = model_set_dat->DataSize-model_set_dat->data_trans_offset;
			if (read_size>MODEL_SET_DIV_SIZE){
				//分割量より大きい場合
				read_size = MODEL_SET_DIV_SIZE;
				//処理を継続
				end = 0;
			}else{
				//読み込んで終了
				end = 1;
			}
			mem = &((u8*)(*model_set_dat->ResFile))[model_set_dat->data_trans_offset];
			ArchiveDataLoadByHandleContinue( model_set_dat->ArcHandle, read_size, mem );

			if (end){
				model_set_dat->SetSeq = MODELSET_TASK_SEQ_TEXTURE_BIND;
			}else{
				model_set_dat->data_trans_offset+=read_size;
			}
		}
		
		break;

	case MODELSET_TASK_SEQ_TEXTURE_BIND:
		if(model_set_dat->Texture != NULL){
			// テクスチャがVramに展開されているかチェック
			if(TexKeyLive(model_set_dat->Texture) == TRUE){	
				//テクスチャバインド
				status = BindTexture(*model_set_dat->ResFile, model_set_dat->Texture);
				NNS_G3D_ASSERTMSG(status, "BindTexture failed");
			}else{
				OS_Printf("テクスチャが展開されていない");
			}
		}
		model_set_dat->SetSeq = MODELSET_TASK_SEQ_RESOUCE_SET;
		break;

	case MODELSET_TASK_SEQ_RESOUCE_SET:
		{
#if 0			
			NNSG3dResMdlSet* pMdlSet = NNS_G3dGetMdlSet(*model_set_dat->ResFile);
			model_set_dat->EntryModelNum = pMdlSet->dict.numEntry; 
			for(i=0;i<model_set_dat->EntryModelNum;i++){
				model_set_dat->Model = NNS_G3dGetMdlByIdx(pMdlSet, i);
				SDK_ASSERTMSG(model_set_dat->Model, "load failed");
				NNS_G3dRenderObjInit(&model_set_dat->Object_p[i], model_set_dat->Model);
			}
#else
			NNSG3dResMdlSet* pMdlSet = NNS_G3dGetMdlSet(*model_set_dat->ResFile);
			NNSG3dResMdl *model;
			
			GF_ASSERT(pMdlSet->dict.numEntry==1&&"モデルセットの中に複数モデルが存在");
			
			model = NNS_G3dGetMdlByIdx(pMdlSet, 0);
			GF_ASSERT(model&&"load failed");
			NNS_G3dRenderObjInit(model_set_dat->Object_p, model);
#endif			
		}
		*model_set_dat->DrawOK = TRUE;

		model_set_dat->SetSeq = MODELSET_TASK_SEQ_EXIT;
		break;
	case MODELSET_TASK_SEQ_EXIT:
		*model_set_dat->EndFlg = 0;
		sys_FreeMemoryEz( (void*)(work) );
		TCB_Delete(tcb);
		return;
	}
}

//マップロードタスク
TCB_PTR Set3DModelTask(	ARCHANDLE *inHandle,
						const int inSize,
						NNSG3dRenderObj* object_p,
						NNSG3dResFileHeader** resFile,
						NNSG3dResTex* pTexture,
						BOOL *ioDrawOKFlg,
						int *inEndFlg) 
{
	TCB_PTR	_tcb;
	MODEL_SET_DAT *work;
	work = (MODEL_SET_DAT *)sys_AllocMemoryLo( HEAPID_FIELD, sizeof(MODEL_SET_DAT) );
	
	work->ArcHandle = inHandle;
	work->DataSize = inSize;
	
	work->Object_p = &object_p[0];
	work->ResFile = resFile;
	work->Texture = pTexture;
	work->SetSeq = 0;
	work->DrawOK = ioDrawOKFlg;
	*work->DrawOK = FALSE;
	work->EndFlg = inEndFlg;
	work->StopFlg = FALSE;
	
	_tcb = TCB_Add(SetModel, work, 1);
	return _tcb;
}

//デフォルトセットアップを行わないモデル読み込み関数
NNSG3dResMdl* Set3DModel(	ARCHANDLE *ioHandle,
							const int inSize,
							NNSG3dRenderObj* object_p,
							NNSG3dResFileHeader** resFile,
							NNSG3dResTex* pTexture)
{
	BOOL status;
	NNSG3dResMdl* model;

	ArchiveDataLoadByHandleContinue( ioHandle, inSize, *(resFile) );
	
	if(pTexture != NULL){
		if(TexKeyLive(pTexture) == TRUE){	// テクスチャがVramに展開されているかチェック
			//テクスチャバインド
			status = BindTexture(*resFile, pTexture);
			NNS_G3D_ASSERTMSG(status, "BindTexture failed");
			GF_ASSERT(status&&"BindTexture failed");
		}else{
			OS_Printf("テクスチャが展開されていない");
		}
	}

	{
		u8 i;
		u16 entry_model_num;
		NNSG3dResMdlSet* pMdlSet = NNS_G3dGetMdlSet(*resFile);

		GF_ASSERT(pMdlSet->dict.numEntry==1&&"モデルセットの中に複数モデルが存在");

		model = NNS_G3dGetMdlByIdx(NNS_G3dGetMdlSet(*resFile), 0);
		GF_ASSERT(model&&"load failed");
		NNS_G3dRenderObjInit(object_p, model);
/**		
		entry_model_num = pMdlSet->dict.numEntry;
		for(i=0;i<entry_model_num;i++){
			model = NNS_G3dGetMdlByIdx(NNS_G3dGetMdlSet(*resFile), i);
			SDK_ASSERTMSG(model, "load failed");
			GF_ASSERT(model&&"load failed");
			NNS_G3dRenderObjInit(&object_p[i], model);
		}
*/		
	}

	return model;
}

#ifdef PM_DEBUG
void SetDebugOutRangeFlg(void)
{
	DebugOutRangeFlg = (DebugOutRangeFlg+1)%2;
}
#endif
