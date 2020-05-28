//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *	H16/11/08		Tomoya Takahashi
 *
 *		Vram転送マネージャーのタスクを管理する
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
#include <nitro.h>
#include <nnsys.h>
#include "system.h"
#include "vram_transfer_manager.h"
#include "assert.h"


//-------------------------------------
//	Vram転送マネージャ
//=====================================
typedef struct _VRAM_TRANSFER_MANAGER{
	u32						tasksNum;			// 登録可能タスク数
	u32						add_task_num;		// タスク登録数
	NNSGfdVramTransferTask*	pTaskArray;			// タスク変数
} VRAM_TRANSFER_MANAGER;


//----------------------------------------------------------------------------
/**
 *					グローバル変数宣言
 */
//-----------------------------------------------------------------------------
static VRAM_TRANSFER_MANAGER* pVramTransferManager;

static BOOL CallbackRegistTransferTask( NNS_GFD_DST_TYPE type, u32 dstAddr, void* pSrc, u32 szByte );

//----------------------------------------------------------------------------
/**
 *
 *@brief	Vram転送マネージャーの初期化
 *
 *@param	tasks_num：登録可能タスク数
 *@param	heap		使用するヒープ
 *
 *@return	none
 *
 *これ以外はデフォルトの関数を使用してください。
 *
 */
//-----------------------------------------------------------------------------
void initVramTransferManagerHeap( u32 tasks_num, int heap )
{
	// 初期済み
	GF_ASSERT( pVramTransferManager == NULL );


	// 実体作成
	pVramTransferManager = sys_AllocMemory( heap, sizeof(VRAM_TRANSFER_MANAGER) );
	// メモリ確保失敗
	GF_ASSERT( pVramTransferManager );
	
	//
	// タスク領域を確保し、Vram転送マネージャーを初期化 
	//
	// 領域を確保
	pVramTransferManager->pTaskArray = (NNSGfdVramTransferTask*)sys_AllocMemory( heap, sizeof(NNSGfdVramTransferTask) * tasks_num );

	// タスク数を代入
	pVramTransferManager->tasksNum = tasks_num;
	pVramTransferManager->add_task_num = 0;

	// Vram転送マネージャーを初期化
	NNS_GfdInitVramTransferManager( pVramTransferManager->pTaskArray, pVramTransferManager->tasksNum );
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	Vram転送マネージャーの破棄
 *
 *@param	none
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void DellVramTransferManager( void )
{
	// 破棄済み
	GF_ASSERT( pVramTransferManager != NULL );
	//
	//タスク領域を破棄 
	//
	// 領域を破棄
	sys_FreeMemoryEz( pVramTransferManager->pTaskArray );

	sys_FreeMemoryEz( pVramTransferManager );
	pVramTransferManager = NULL;
}


//----------------------------------------------------------------------------
/**
 *
 *@brief	Vram転送マネージャータスクを登録
 *
 *@param	type		データ転送先の種類
 *@param	dstAddr		転送先アドレス
 *@param	pSrc		転送元データへのポインタ
 *@param	szByte		転送サイズ
 *
 *@retval	TRUE		成功	
 *@retval	FALSE		失敗
 *
 *
 */
//-----------------------------------------------------------------------------
BOOL AddVramTransferManager( NNS_GFD_DST_TYPE type, u32 dstAddr, void* pSrc, u32 szByte )
{	
	// 初期化されていない
	GF_ASSERT( pVramTransferManager );
	pVramTransferManager->add_task_num++;		// タスク数加算

	if(pVramTransferManager->add_task_num >= pVramTransferManager->tasksNum){	// タスクオーバーチェック
		GF_ASSERT(0&&("VramTransferManagerタスクオーバー"));
		return FALSE;
	}

	return NNS_GfdRegisterNewVramTransferTask(type, dstAddr, pSrc, szByte);
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	実際に転送する
 *
 *@param	none
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void DoVramTransferManager( void )
{
	if(pVramTransferManager){
		NNS_GfdDoVramTransfer();
		pVramTransferManager->add_task_num = 0;
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	今のタスク登録数を取得
 *
 *@param	none
 *
 *@return	int		タスク登録数
 *
 *
 */
//-----------------------------------------------------------------------------
int GetVramTransferManagerAddNum( void )
{
	// 初期化されていない
	GF_ASSERT( pVramTransferManager );
	return pVramTransferManager->add_task_num;
}


//----------------------------------------------------------------------------
/**
 *
 *@brief	セル転送マネージャの初期化
 *
 *@param	num		最大セル登録数
 *@param	heap	使用ヒープ
 *	
 *@return	NNSG2dCellTransferState*	確保したセル転送バッファ
 *
 *
 */
//-----------------------------------------------------------------------------
NNSG2dCellTransferState* InitCellTransfer(int num, int heap)
{
	NNSG2dCellTransferState* buff;

	// CellVram転送初期化
	buff = sys_AllocMemory(heap, sizeof(NNSG2dCellTransferState)*num);
	
	NNS_G2dInitCellTransferStateManager(
				buff,
				num,
				CallbackRegistTransferTask          // <- (1)
			);

	return buff;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	セルのデータをVram転送タスクに設定する
 *
 *@param	none
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void UpdateCellTransfer(void)
{
	// Vram転送タスクを設定
	NNS_G2dUpdateCellTransferStateManager();
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	セル転送マネージャを破棄
 *
 *@param	data		セル転送データバッファ
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void DeleteCellTransfer(NNSG2dCellTransferState* data)
{
	sys_FreeMemoryEz(data);
}

//-----------------------------------------------------------------------------
/**
 *@brief				NNS_G2dDraw関数内部でキャラクタデータの転送タスクを
 *							登録するために呼ばれる関数
 *
 *@param	type：転送先Vram領域種別
 *@param	dstAddr：転送先オフセット
 *@param	pStr：転送元データへのポインタ
 *@param	szByte：転送サイズ
 *
 *@retval	成功：TRUE
 *@retval	失敗：FALSE
 *
 */
 //----------------------------------------------------------------------------
static BOOL CallbackRegistTransferTask( NNS_GFD_DST_TYPE type, u32 dstAddr, void* pSrc, u32 szByte )
{
	// VRAM 転送マネージャにそのまま渡す
    return AddVramTransferManager(
                type,
                dstAddr,
                pSrc,
                szByte );
}
