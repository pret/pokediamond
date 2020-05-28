//==============================================================================
/**
 *
 *@file		heapsys.c
 *@brief	ヒープ領域管理
 *@author	taya
 *@date		2005.08.25
 *
 */
//==============================================================================
#include "common.h"
#include "system.h"
#include "gflib\heapsys.h"

#ifdef PM_DEBUG
#include  "system\heapdefine.h"
//#define  ALLOCINFO_PRINT_HEAPID   HEAPID_BASE_APP	// このヒープＩＤに関してのみ詳細な情報を出力
#endif



//----------------------------------------------------------------
/**
 *	定数
 */
//----------------------------------------------------------------
#define DEFAULT_ALIGN					(4)		// メモリ確保時のアライメント値
#define MEMBLOCK_FILENAME_AREASIZE		(12)	// デバッグ用ヘッダに格納するファイル名領域サイズ
#define USER_HEAP_MAX					(24)	// 一度に作成可能なユーザーヒープの数


//----------------------------------------------------------------
/**
 *	マクロ
 */
//----------------------------------------------------------------
#define ASSERT_IRQ_ENABLED()		GF_ASSERT(OS_GetProcMode() != OS_PROCMODE_IRQ)


//----------------------------------------------------------------
/**
 *	ワーク定義
 */
//----------------------------------------------------------------
typedef struct {
	NNSFndHeapHandle*	handle;
	NNSFndHeapHandle*	parentHandle;
	void**              heapMemBlock;
	u16*				count;
	u8*					handleIdxTbl;

	u16     heapMax;
	u16     baseHeapMax;
	u16     usableHeapMax;
	u16     invalidHandleIdx;


}HEAP_SYS;


//----------------------------------------------------------------
/**
 *	メモリブロックヘッダ定義
 */
//----------------------------------------------------------------
typedef struct {
	char	filename[ MEMBLOCK_FILENAME_AREASIZE ];	///< 呼び出し先ソース名
	u32		heapID  : 8;							///< u32
	u32		lineNum : 24;							///< 呼び出しソース行番号
}MEMORY_BLOCK_HEADER;


//----------------------------------------------------------------
/**
 *	グローバル
 */
//----------------------------------------------------------------
static HEAP_SYS  HeapSys = { 0 };


//----------------------------------------------------------------
/**
 *	ハンドル取得マクロ
 */
//----------------------------------------------------------------
#define GetHeapHandle(idx)			(HeapSys.handle[ HeapSys.handleIdxTbl[ (idx) ] ])
#define GetParentHeapHandle(idx)	(HeapSys.parentHandle[ HeapSys.handleIdxTbl[ (idx) ] ])
#define GetHeapMemBlock(idx)		(HeapSys.heapMemBlock[ HeapSys.handleIdxTbl[ (idx) ] ])

#define SetHeapHandle(idx,h)		(HeapSys.handle[ HeapSys.handleIdxTbl[ (idx) ] ] = (h))
#define SetParentHeapHandle(idx,h)	(HeapSys.parentHandle[ HeapSys.handleIdxTbl[ (idx) ] ] = (h))
#define SetHeapMemBlock(idx,m)		(HeapSys.heapMemBlock[ HeapSys.handleIdxTbl[ (idx) ] ] = (m))


//==============================================================
// Prototype
//==============================================================
static int SearchEmptyHandleIndex( void );
static BOOL CreateHeapCore( u32 parentHeapID, u32 childHeapID, u32 size, s32 align );
static void* AllocMemoryCore( NNSFndHeapHandle heapHandle, u32 size, s32 alignment, u32 heapID );
static void PrintAllocInfo( const MEMORY_BLOCK_HEADER* header, NNSFndHeapHandle handle, u32 size );
static void PrintFreeInfo( const MEMORY_BLOCK_HEADER* header, NNSFndHeapHandle handle);
static void HeaderDebugParamSet( MEMORY_BLOCK_HEADER* header, const char* filename, u32 line_no );
static void PrintShortHeap( u32 heapID, u32 size, const char* filename, u32 line_num );
static void PrintExistMemoryBlocks( u32 heapID );
static void HeapConflictVisitorFunc(void* memBlock, NNSFndHeapHandle heapHandle, u32 param);
static void CopyFileName( char* dst, const MEMORY_BLOCK_HEADER* header );
static void PrintUnreleasedMemoryInfo( u32 heapID );





#ifdef PM_DEBUG
static void HeaderDebugParamSet( MEMORY_BLOCK_HEADER* header, const char* filename, u32 line_no );
static void PrintExistMemoryBlocks( u32 heapID );
static void HeapConflictVisitorFunc(void* memBlock, NNSFndHeapHandle heapHandle, u32 param);
static void CopyFileName( char* dst, const MEMORY_BLOCK_HEADER* header );
static void PrintUnreleasedMemoryInfo( u32 heapID );
#endif

//------------------------------------------------------------------------------
/**
 * Description:  システムヒープとアプリケーションヒープを作成します。両ヒープ
 * 				にはNITRO-Systemの拡張ヒープを使用しています。
 *
 * 				システムヒープ用のメモリとして、SYSTEM_HEAP_SIZE分をメインア
 * 				リーナから確保し、メインアリーナの残りを全てアプリケーション
 * 				ヒープ用のメモリに確保しています。
 *
 * 				システムヒープは、ゲームシステム等のシステムプログラムで使用
 * 				することを想定しています。アプリケーションヒープには、ゲーム
 * 				で使用するデータをロードする為に使用します。
 *
 * @param   header			初期化情報
 * @param   baseHeapMax		基本ヒープエリア数
 * @param   totalHeapMax	全ヒープエリア数
 * @param   startOffset		与えられたバイト数だけ全体の開始位置をずらす
 *
 */
//------------------------------------------------------------------------------
void sys_InitHeapSystem(const HEAP_INIT_HEADER* header, u32 baseHeapMax, u32 totalHeapMax, u32 startOffset)
{
	void *mem;
	u32  usableHeapMax, i;

	usableHeapMax = baseHeapMax + USER_HEAP_MAX;
	if( totalHeapMax < usableHeapMax )
	{
		totalHeapMax = usableHeapMax;
	}

	// ヒープアドレスをずらす
	if( startOffset )
	{
		while( startOffset & 3 )
		{
			startOffset++;
		}
		OS_AllocFromMainArenaLo( startOffset, DEFAULT_ALIGN );
	}

	/*
	 * ヒープハンドル領域は、作成可能ヒープ数＋１　作成。
	 * 最後の１は無効値を入れておいて、未作成ヒープのインデックステーブルはそこを指すようにする。
	 */
	HeapSys.handle = OS_AllocFromMainArenaLo(
									sizeof(NNSFndHeapHandle) * (usableHeapMax + 1)
								+	sizeof(NNSFndHeapHandle) * (usableHeapMax)
								+	sizeof(void*) * (usableHeapMax)
								+   sizeof(u16) * (totalHeapMax)
								+	totalHeapMax, DEFAULT_ALIGN);

	HeapSys.parentHandle = HeapSys.handle + (usableHeapMax + 1);
	HeapSys.heapMemBlock = (void**)((u8*)(HeapSys.parentHandle) + (sizeof(NNSFndHeapHandle) * usableHeapMax));
	HeapSys.count = (u16*)((u8*)(HeapSys.heapMemBlock) + (sizeof(void*) * usableHeapMax));
	HeapSys.handleIdxTbl = (u8*)(HeapSys.count) + (sizeof(u16) * (totalHeapMax));

	HeapSys.heapMax = totalHeapMax;
	HeapSys.baseHeapMax = baseHeapMax;
	HeapSys.invalidHandleIdx = usableHeapMax;
	HeapSys.usableHeapMax = usableHeapMax;


	// 基本ヒープ＆インデックス作成
	for(i = 0; i < baseHeapMax; i++)
	{
        OS_TPrintf("remains of MainRAM = 0x%08x bytes.\n", (u32)(OS_GetMainArenaHi())-(u32)(OS_GetMainArenaLo()));
		switch( header[i].arenaID ){
		case OS_ARENA_MAIN:
		default:
			mem = OS_AllocFromMainArenaLo( header[i].size, DEFAULT_ALIGN );
			break;
		case OS_ARENA_MAINEX:
			mem = OS_AllocFromMainExArenaHi( header[i].size, DEFAULT_ALIGN );
			break;
		}

		if( mem != NULL )
		{
			HeapSys.handle[i] = NNS_FndCreateExpHeap( mem, header[i].size );
			HeapSys.handleIdxTbl[i] = i;
		}
		else
		{
			GF_ASSERT_MSG(0, "%xが確保できなかった size=%x\n" ,header[i].size, mem);
		}
	}

	// ユーザーヒープ領域は無効値でクリアしておく
	for(i = baseHeapMax; i < (usableHeapMax + 1); i++ )
	{
		HeapSys.handle[i] = NNS_FND_HEAP_INVALID_HANDLE;
		HeapSys.handleIdxTbl[i] = HeapSys.invalidHandleIdx;
	}
	while( i < totalHeapMax )
	{
		HeapSys.handleIdxTbl[i++] = HeapSys.invalidHandleIdx;
	}

	// Allocカウンタクリア
	for(i = 0; i < totalHeapMax; i++)
	{
		HeapSys.count[i] = 0;
	}


}


//------------------------------------------------------------------
/**
 * ハンドル領域の空きを検索
 *
 * @retval  int		空きがあればインデックスナンバー／なければ-1
 */
//------------------------------------------------------------------
static int SearchEmptyHandleIndex( void )
{
	int i;

	// 基本ヒープは解放されないハズなので…
	for( i = HeapSys.baseHeapMax; i < HeapSys.usableHeapMax; i++ )
	{
		if(HeapSys.handle[i] == NNS_FND_HEAP_INVALID_HANDLE)
		{
			return i;
		}
	}
	return -1;
}

//------------------------------------------------------------------
/**
 * ヒープ作成
 *
 * @param   parentHeapID		メモリ領域確保用ヒープＩＤ（既に有効である必要がある）
 * @param   childHeapID			新規に作成するヒープＩＤ
 * @param   size				ヒープサイズ
 *
 * @retval	BOOL				TRUEで作成成功／FALSEで失敗
 */
//------------------------------------------------------------------
BOOL sys_CreateHeap( u32 parentHeapID, u32 childHeapID, u32 size )
{
	return CreateHeapCore( parentHeapID, childHeapID, size, DEFAULT_ALIGN );
}

//------------------------------------------------------------------
/**
 * ヒープ作成（メモリ後方から確保）
 *
 * @param   parentHeapID		メモリ領域確保用ヒープＩＤ（既に有効である必要がある）
 * @param   childHeapID			新規に作成するヒープＩＤ
 * @param   size				ヒープサイズ
 *
 * @retval	BOOL				TRUEで作成成功／FALSEで失敗
 */
//------------------------------------------------------------------
BOOL sys_CreateHeapLo( u32 parentHeapID, u32 childHeapID, u32 size )
{
	return CreateHeapCore( parentHeapID, childHeapID, size, -DEFAULT_ALIGN );
}

//------------------------------------------------------------------
/**
 * ヒープ作成実処理
 *
 * @param   parentHeapID	メモリ領域確保用ヒープＩＤ（既に有効である必要がある）
 * @param   childHeapID		新規に作成するヒープＩＤ
 * @param   size			ヒープサイズ
 * @param   align			アライメント（マイナスならメモリ後方から確保）
 *
 * @retval  BOOL		TRUEで作成成功／FALSEで失敗
 */
//------------------------------------------------------------------
static BOOL CreateHeapCore( u32 parentHeapID, u32 childHeapID, u32 size, s32 align )
{
	GF_ASSERT_MSG((OS_GetProcMode() != OS_PROCMODE_IRQ), "Create Heap:%d size:%d", childHeapID, size);

	if( HeapSys.handleIdxTbl[childHeapID] == HeapSys.invalidHandleIdx )
	{
		NNSFndHeapHandle  parentHeap = GetHeapHandle(parentHeapID);
		if( parentHeap != NNS_FND_HEAP_INVALID_HANDLE )
		{
			void* mem = NNS_FndAllocFromExpHeapEx( parentHeap, size, align );
			if( mem != NULL )
			{
				int i = SearchEmptyHandleIndex();
				if( i >= 0 )
				{
					HeapSys.handle[i] = NNS_FndCreateExpHeap( mem, size );
					if( HeapSys.handle[i] != NNS_FND_HEAP_INVALID_HANDLE )
					{
						HeapSys.parentHandle[i] = parentHeap;
						HeapSys.heapMemBlock[i] = mem;
						HeapSys.handleIdxTbl[childHeapID] = i;

						#ifdef ALLOCINFO_PRINT_HEAPID
						if( ALLOCINFO_PRINT_HEAPID == childHeapID )
						{
							u32 freeSize = NNS_FndGetTotalFreeSizeForExpHeap( HeapSys.handle[i] );
							OS_TPrintf("[HEAP] CRE_C total:0x%05x, usable:0x%05x  parent's id=%d, rest=0x%05x\n",
									size, freeSize, parentHeapID, NNS_FndGetTotalFreeSizeForExpHeap( parentHeap ) );
						}
						if( ALLOCINFO_PRINT_HEAPID == parentHeapID )
						{
							u32 freeSize = NNS_FndGetTotalFreeSizeForExpHeap( parentHeap );
							OS_TPrintf("[HEAP] CRE_P parent:%d rest:%05x, child:%d size:0x%05x\n",
									parentHeapID, freeSize, childHeapID, size );
						}
						#endif
						return TRUE;
					}
					else
					{
						GF_ASSERT_MSG(0, "ヒープ作成に失敗");
					}

				}
				else
				{
					GF_ASSERT_MSG(0, "ヒープ管理テーブルに空きが無い");
				}
			}
			else
			{
				GF_ASSERT_Printf("Heap(%d) Create FAILED (size:%x bytes)\n", childHeapID, size);
				GF_ASSERT_Printf("ParentHeap(%d) %x bytes\n", parentHeapID, NNS_FndGetTotalFreeSizeForExpHeap( parentHeap ) );
				GF_ASSERT(0);
			}
		}
		else
		{
			GF_ASSERT_MSG(0, "作成元ヒープＩＤが無効");
		}
	}
	else
	{
		GF_ASSERT_MSG(0, "ヒープが２重に作られようとした");
	}
	return FALSE;
}

//------------------------------------------------------------------
/**
 * ヒープ破棄
 *
 * @param   heapID		ヒープID
 *
 */
//------------------------------------------------------------------
void sys_DeleteHeap( u32 heapID )
{
	GF_ASSERT_MSG((OS_GetProcMode() != OS_PROCMODE_IRQ), "Delete Heap:%d", heapID);

	{
		NNSFndHeapHandle  handle, parentHandle;

		handle = GetHeapHandle(heapID);


		if(handle != NNS_FND_HEAP_INVALID_HANDLE)
		{
			NNSFndHeapHandle  parentHandle;
			void* heapMemBlock;

		// デバッグ時は未解放メモリの情報を出力
			#ifdef PM_DEBUG
			if( HeapSys.count[heapID] )
			{
				PrintUnreleasedMemoryInfo( heapID );
				GF_ASSERT(0);
			}
			#endif

			NNS_FndDestroyExpHeap( handle );

			parentHandle = GetParentHeapHandle(heapID);
			heapMemBlock = GetHeapMemBlock(heapID);
			if(	(parentHandle != NNS_FND_HEAP_INVALID_HANDLE)
			&&	(heapMemBlock != NULL)
			){
				NNS_FndFreeToExpHeap( parentHandle, heapMemBlock );
			}else{
				GF_ASSERT(0);
			}

			SetHeapHandle(heapID, NNS_FND_HEAP_INVALID_HANDLE);
			SetParentHeapHandle(heapID, NNS_FND_HEAP_INVALID_HANDLE);
			SetHeapMemBlock(heapID, NULL);
			HeapSys.handleIdxTbl[ heapID ] = HeapSys.invalidHandleIdx;

			#ifdef ALLOCINFO_PRINT_HEAPID
			if( heapID == ALLOCINFO_PRINT_HEAPID )
			{
				OS_TPrintf("[HEAP] DELETE Heap(%d), parent's rest=%05x\n",
					heapID, NNS_FndGetTotalFreeSizeForExpHeap(parentHandle) );
			}
			else
			{
				u32 parentID;

				for(parentID=0; parentID<HeapSys.usableHeapMax; parentID++)
				{
					if( HeapSys.handle[parentID] == parentHandle ){ break; }
				}
				if( parentID == ALLOCINFO_PRINT_HEAPID )
				{
					OS_TPrintf("[HEAP] DELETE Heap(%d), parentHeap(%d), parent's rest=%05x\n",
						heapID, parentID, NNS_FndGetTotalFreeSizeForExpHeap(parentHandle) );
				}
			}
			#endif
		}
	}
}

//------------------------------------------------------------------
/**
 * メモリアロケート本体（デバッグ版、製品版ともコイツを呼び出す）
 *
 * @param   heapHandle		拡張ヒープハンドル
 * @param   size			アロケートサイズ
 * @param   alignment		アライメント
 * @param   heapID			ヘッダに保存するヒープID
 *
 * @retval  void*			確保したメモリ（ヘッダ分は飛ばしてある）
 */
//------------------------------------------------------------------
static void* AllocMemoryCore( NNSFndHeapHandle heapHandle, u32 size, s32 alignment, u32 heapID )
{
	void* mem;
    OSIntrMode old;

	GF_ASSERT_MSG(heapHandle != NNS_FND_HEAP_INVALID_HANDLE, "heapID=%d", heapID);
    old = OS_DisableInterrupts();
	mem = NNS_FndAllocFromExpHeapEx( heapHandle, size + sizeof(MEMORY_BLOCK_HEADER), alignment );
    OS_RestoreInterrupts( old );

	if( mem != NULL )
	{
		((MEMORY_BLOCK_HEADER*)mem)->heapID = heapID;
		(u8*)mem += sizeof(MEMORY_BLOCK_HEADER);
	}

	return mem;
}



#ifndef PM_DEBUG

#include "system\assert_warning_reset.h"
#include "communication\comm_state.h"

//------------------------------------------------------------------
/**
 * 通信中にメモリ確保に失敗した場合、強制的にエラー画面へ飛ばす
 *
 */
//------------------------------------------------------------------
static void WarningResetCall(void)
{
	if( CommStateIsInitialize() )
	{
		AssertWarningResetCall();
	}
}


//------------------------------------------------------------------
/**
 * ヒープからメモリを確保する
 *
 * @param   heapID		ヒープＩＤ
 * @param   size		確保サイズ
 *
 * @retval  void*		確保した領域アドレス（失敗ならNULL）
 */
//------------------------------------------------------------------
void* sys_AllocMemory( u32 heapID, u32 size )
{
	void* ret = NULL;

	if( heapID < HeapSys.heapMax )
	{
		NNSFndHeapHandle  h = GetHeapHandle( heapID );
		ret = AllocMemoryCore( h, size, DEFAULT_ALIGN, heapID );
	}

	if( ret != NULL )
	{
		HeapSys.count[heapID]++;
	}
	else
	{
		WarningResetCall();
	}

	return ret;
}
//------------------------------------------------------------------
/**
 * ヒープ後方からメモリを確保する（テンポラリ領域用）
 *
 * @param   heapID		ヒープＩＤ
 * @param   size		確保サイズ
 *
 * @retval  void*		確保した領域アドレス（失敗ならNULL）
 */
//------------------------------------------------------------------
void* sys_AllocMemoryLo( u32 heapID, u32 size )
{
	void* ret = NULL;

	if( heapID < HeapSys.heapMax )
	{
		NNSFndHeapHandle  h = GetHeapHandle( heapID );
		ret = AllocMemoryCore( h, size, -DEFAULT_ALIGN, heapID );
	}

	if( ret != NULL )
	{
		HeapSys.count[heapID]++;
	}
	else
	{
		WarningResetCall();
	}

	return ret;
}
#else	// #ifndef PM_DEBUG

//------------------------------------------------------------------
/**
 * メモリ確保時の詳細情報表示
 *
 * @param   header		メモリブロックヘッダ
 * @param   handle		メモリブロックが含まれるヒープのハンドル
 * @param   size		確保サイズ（リクエストされたサイズ）
 *
 */
//------------------------------------------------------------------
static void PrintAllocInfo( const MEMORY_BLOCK_HEADER* header, NNSFndHeapHandle handle, u32 size )
{
	char filename[MEMBLOCK_FILENAME_AREASIZE+1];

	CopyFileName( filename, header );

	OS_TPrintf("[HEAP] ALLOC count=%3d rest=0x%08x adrs:0x%08x size:0x%05x %s(%d)\n",
				HeapSys.count[header->heapID], NNS_FndGetTotalFreeSizeForExpHeap(handle), 
				(u32)header, size+sizeof(MEMORY_BLOCK_HEADER), filename, header->lineNum );
}

//------------------------------------------------------------------
/**
 * メモリ解放時の詳細情報表示
 *
 * @param   heapID			ヒープID
 * @param   size			確保したサイズ
 * @param   handle			ヒープハンドル
 * @param   filename		呼び出し元ソースファイル名
 * @param   line			呼び出し元ソースファイル行番号
 *
 */
//------------------------------------------------------------------
static void PrintFreeInfo( const MEMORY_BLOCK_HEADER* header, NNSFndHeapHandle handle)
{
	char filename[MEMBLOCK_FILENAME_AREASIZE+1];
	u32  blockSize, restSize;

	CopyFileName( filename, header );

	blockSize = NNS_FndGetSizeForMBlockExpHeap(header) + sizeof(NNSiFndExpHeapMBlockHead);

	// 残りサイズは現サイズ＋これから解放しようとするメモリブロックのサイズになるはず
	restSize = NNS_FndGetTotalFreeSizeForExpHeap(handle) + blockSize;

	OS_TPrintf("[HEAP] FREE  count=%3d rest=0x%08x adrs:0x%08x size:0x%05x %s(%d)\n",
				HeapSys.count[header->heapID], restSize, (u32)header, blockSize,
				filename, header->lineNum );
}



//------------------------------------------------------------------
/**
 * sys_AllocMemoryのデバッグ用ラッパー関数
 *
 * @param   heapID			ヒープID
 * @param   size			確保サイズ
 * @param   filename		呼び出しソースのファイル名
 * @param   line_num		呼び出しソースの行番号
 *
 * @retval  void*			確保した領域アドレス（失敗ならNULL）
 */
//------------------------------------------------------------------
void* sys_AllocMemoryDebug( u32 heapID, u32 size, const char* filename, u32 line_num )
{
	GF_ASSERT_MSG((OS_GetProcMode() != OS_PROCMODE_IRQ), "Alloc in IRQ\n %s(%d)", filename, line_num);

	if( heapID < HeapSys.heapMax )
	{
		NNSFndHeapHandle  h = GetHeapHandle( heapID );
		void* mem = AllocMemoryCore( h, size, DEFAULT_ALIGN, heapID );

		if( mem != NULL )
		{
			HeaderDebugParamSet((MEMORY_BLOCK_HEADER*)( (u8*)mem - sizeof(MEMORY_BLOCK_HEADER) ),
									filename, line_num);
			HeapSys.count[heapID]++;

			#ifdef ALLOCINFO_PRINT_HEAPID
			if( ALLOCINFO_PRINT_HEAPID == heapID )
			{
				const MEMORY_BLOCK_HEADER* mh = (const MEMORY_BLOCK_HEADER*)((u8*)mem - sizeof(MEMORY_BLOCK_HEADER));
				PrintAllocInfo( mh, h, size );
				GF_ASSERT( sys_CheckHeapSafe( heapID ) );
			}
			#endif
		}
		else
		{
			PrintShortHeap( heapID, size, filename, line_num );
			GF_ASSERT(0);
		}

		return mem;
	}
	else
	{
		GF_ASSERT_MSG(0, "heapID = %d\n", heapID);
		return NULL;
	}
}
//------------------------------------------------------------------
/**
 * sys_AllocMemoryLoのデバッグ用ラッパー関数
 *
 * @param   heapID			ヒープID
 * @param   size			確保サイズ
 * @param   filename		呼び出しソースのファイル名
 * @param   line_num		呼び出しソースの行番号
 *
 * @retval  void*			確保した領域アドレス（失敗ならNULL）
 */
//------------------------------------------------------------------
void* sys_AllocMemoryLoDebug( u32 heapID, u32 size, const char* filename, u32 line_num )
{
	GF_ASSERT_MSG((OS_GetProcMode() != OS_PROCMODE_IRQ), "Alloc in IRQ\n %s(%d)", filename, line_num);

	if( heapID < HeapSys.heapMax )
	{
		NNSFndHeapHandle  h = GetHeapHandle( heapID );
		void* mem = AllocMemoryCore( h, size, -DEFAULT_ALIGN, heapID );

		if( mem != NULL )
		{
			HeaderDebugParamSet((MEMORY_BLOCK_HEADER*)( (u8*)mem - sizeof(MEMORY_BLOCK_HEADER) ),
									filename, line_num);
			HeapSys.count[heapID]++;

			#ifdef ALLOCINFO_PRINT_HEAPID
			if( ALLOCINFO_PRINT_HEAPID == heapID )
			{
				const MEMORY_BLOCK_HEADER* mh = (const MEMORY_BLOCK_HEADER*)((u8*)mem - sizeof(MEMORY_BLOCK_HEADER));
				PrintAllocInfo( mh, h, size );
				GF_ASSERT( sys_CheckHeapSafe( heapID ) );
			}
			#endif
		}
		else
		{
			PrintShortHeap( heapID, size, filename, line_num );
			GF_ASSERT(0);
		}
		return mem;
	}
	else
	{
		GF_ASSERT(0);
		return NULL;
	}
}
//------------------------------------------------------------------
/**
 * ブロックヘッダにデバッグ情報を書き込む
 *
 * @param   header		ヘッダアドレス
 * @param   filename	ファイル名
 * @param   line_no		行番号
 *
 */
//------------------------------------------------------------------
static void HeaderDebugParamSet( MEMORY_BLOCK_HEADER* header, const char* filename, u32 line_no )
{
	int i;
	for(i = 0; i < MEMBLOCK_FILENAME_AREASIZE; i++)
	{
		header->filename[i] = filename[i];
		if( filename[i] == '\0' ){ break; }
	}
	header->lineNum = line_no;
}

//------------------------------------------------------------------
/**
 * 残りメモリが不足して確保できないメッセージ取得
 *
 * @param   heapID		ヒープＩＤ
 * @param   size		確保しようとしたサイズ
 *
 */
//------------------------------------------------------------------
static void PrintShortHeap( u32 heapID, u32 size, const char* filename, u32 line_num )
{
	NNSFndHeapHandle h;
	u32 freeAreaSize, allocatableMaxSize;

	h = GetHeapHandle(heapID);
	freeAreaSize = NNS_FndGetTotalFreeSizeForExpHeap( h );
	allocatableMaxSize = NNS_FndGetAllocatableSizeForExpHeapEx( h, DEFAULT_ALIGN );

	GF_ASSERT_Printf("Can't alloc %ldbytes memory from Heap(%d)\n", size, heapID);
	GF_ASSERT_Printf("This Heap have %ldbytes Free Area\n", freeAreaSize );
	GF_ASSERT_Printf("and %ldbytes Allocatable Area\n", allocatableMaxSize );
	GF_ASSERT_Printf("%s(%d)\n", filename, line_num);

	GF_ASSERT_Printf("these Memoryblocks haven't released\n");
	PrintExistMemoryBlocks( heapID );
}
#endif	// #ifndef PM_DEBUG #else


//------------------------------------------------------------------
/**
 * ヒープから確保したメモリを解放する
 *
 * @param   memory		確保したメモリアドレス
 *
 */
//------------------------------------------------------------------
void sys_FreeMemoryEz( void* memory )
{
	#ifdef PM_DEBUG
	if( OS_GetProcMode() == OS_PROCMODE_IRQ )
	{
		char filename[MEMBLOCK_FILENAME_AREASIZE+1];
		MEMORY_BLOCK_HEADER* header;

		header = (MEMORY_BLOCK_HEADER*)((u8*)memory - sizeof(MEMORY_BLOCK_HEADER));
		CopyFileName( filename, header );
		GF_ASSERT_MSG(0, "Free in IRQ\n %s(%d) siz:%x", filename, header->lineNum, 
						NNS_FndGetSizeForMBlockExpHeap(header) );
	}
	#endif

	{
		u32 heapID;

		(u8*)memory -= sizeof(MEMORY_BLOCK_HEADER);
		heapID = ((MEMORY_BLOCK_HEADER*)memory)->heapID;

		if( heapID < HeapSys.heapMax )
		{
			NNSFndHeapHandle  h = HeapSys.handle[ HeapSys.handleIdxTbl[ heapID ] ];

			GF_ASSERT(h != NNS_FND_HEAP_INVALID_HANDLE);
			if( HeapSys.count[heapID] == 0 )
			{
				sys_CheckHeapSafe(heapID);
			}
			GF_ASSERT_MSG( HeapSys.count[heapID], "heapID = %d", heapID );

			HeapSys.count[ heapID ]--;

			#ifdef ALLOCINFO_PRINT_HEAPID
			if( ALLOCINFO_PRINT_HEAPID == heapID )
			{
				GF_ASSERT( sys_CheckHeapSafe(heapID) );
				PrintFreeInfo( (const MEMORY_BLOCK_HEADER*)memory, h );
			}
			#endif

			{
				OSIntrMode old;
				old = OS_DisableInterrupts();
				NNS_FndFreeToExpHeap( h, memory );
				OS_RestoreInterrupts( old );
			}

		}
		else
		{
			GF_ASSERT_MSG(0, "heapID = %d\n", heapID);
		}
	}
}
//------------------------------------------------------------------
/**
 * ヒープから確保したメモリを解放する（ヒープID指定版）
 *
 * ※もしかしたらヒープIDを指定する合理的な理由があるかもしれないので
 *   残しておく。普通は FreeMemoryEz を使えば問題ないはず。
 *
 * @param   heapID		ヒープID
 * @param   memory		確保したメモリポインタ
 *
 */
//------------------------------------------------------------------
void sys_FreeMemory( u32 heapID, void* memory )
{
	ASSERT_IRQ_ENABLED();

	if( heapID < HeapSys.heapMax )
	{
		NNSFndHeapHandle h = GetHeapHandle(heapID);

		GF_ASSERT(h != NNS_FND_HEAP_INVALID_HANDLE);

		(u8*)memory -= sizeof(MEMORY_BLOCK_HEADER);
		if( ((MEMORY_BLOCK_HEADER*)memory)->heapID != heapID )
		{
			GF_ASSERT_MSG(0, "確保時と違うヒープIDで解放されようとしている\n");
		}
		NNS_FndFreeToExpHeap( h, memory );

		GF_ASSERT( HeapSys.count[ heapID ] );
		HeapSys.count[ heapID ]--;

		#ifdef ALLOCINFO_PRINT_HEAPID
		if( ALLOCINFO_PRINT_HEAPID == heapID )
		{
			GF_ASSERT( sys_CheckHeapSafe( heapID ) );
			PrintFreeInfo( (const MEMORY_BLOCK_HEADER*)memory, h );
		}
		#endif

	}
	else
	{
		GF_ASSERT(0);
	}
}
//------------------------------------------------------------------
/**
 * ヒープの空き領域サイズを返す
 *
 * @param   heapID	ヒープID
 *
 * @retval  u32		空き領域サイズ（バイト単位）
 */
//------------------------------------------------------------------
u32 sys_GetHeapFreeSize( u32 heapID )
{
	if( heapID < HeapSys.heapMax )
	{
		NNSFndHeapHandle h = GetHeapHandle(heapID);
		return NNS_FndGetTotalFreeSizeForExpHeap( h );
	}
	GF_ASSERT(0);
	return 0;
}
//------------------------------------------------------------------
/**
 * NitroSystem ライブラリ系関数が要求するアロケータを作成する
 *
 * @param   pAllocator		NNSFndAllocator構造体のアドレス
 * @param   heapID			ヒープID
 * @param   alignment		確保するメモリブロックに適用するアライメント
 *
 */
//------------------------------------------------------------------
void sys_InitAllocator( NNSFndAllocator* pAllocator, u32 heapID, int alignment)
{
	if( heapID < HeapSys.heapMax )
	{
		NNSFndHeapHandle h = GetHeapHandle(heapID);
		NNS_FndInitAllocatorForExpHeap( pAllocator, h, alignment );
	}
	else
	{
		GF_ASSERT(0);
	}
}

//------------------------------------------------------------------
/**
 * 確保したメモリブロックのサイズを縮小する。
 *
 * @param   memBlock		メモリブロックポインタ
 * @param   newSize			縮小後のサイズ（バイト単位）
 *
 *
 * 縮小は、メモリブロックの後ろ方向からメモリを解放することで行う。
 * 解放された分はシステムに返還され、新たなアロケート領域として使用できる。
 *
 * 例えば【ヘッダ＋実体】のような形式のグラフィックバイナリをＲＡＭに読み込み、
 * 実体部をVRAMに転送した後、ヘッダのみを残したいというケースなどで使用することを
 * 想定している。使用は慎重に。
 *
 */
//------------------------------------------------------------------
void sys_CutMemoryBlockSize( void* memBlock, u32 newSize )
{
	ASSERT_IRQ_ENABLED();

	{
		u32 oldSize;

		(u8*)memBlock -= sizeof(MEMORY_BLOCK_HEADER);
		oldSize = NNS_FndGetSizeForMBlockExpHeap( memBlock );
		newSize += sizeof(MEMORY_BLOCK_HEADER);	// 呼び出し側はヘッダを意識していないので

		if( oldSize >= newSize )
		{
			u32 heapID;
			NNSFndHeapHandle handle;

			heapID = ((MEMORY_BLOCK_HEADER*)memBlock)->heapID;
			handle = GetHeapHandle(heapID);

			NNS_FndResizeForMBlockExpHeap( handle, memBlock, newSize );
		}
		else
		{
			GF_ASSERT(0);
		}
	}
}



//------------------------------------------------------------------
/**
 * ヒープ領域が破壊されていないかチェック（デバッグ用）
 *
 * @param   heapID		ヒープID
 *
 * @retval  BOOL		破壊されていなければTRUEが返る
 */
//------------------------------------------------------------------
BOOL sys_CheckHeapSafe( u32 heapID )
{
	#ifdef PM_DEBUG
	if( heapID < HeapSys.heapMax )
	{
		NNSFndHeapHandle h = GetHeapHandle(heapID);
		if( h != NNS_FND_HEAP_INVALID_HANDLE )
		{
			return NNS_FndCheckExpHeap( h, NNS_FND_HEAP_ERROR_PRINT );
		}
	}
	return TRUE;
	#else

	// 本来製品版には存在しないはずの関数だが、
	// GF_ASSERTを製品版でも有効にしたため、ASSERTチェック中に呼ばれることのある
	// この関数を削除できなくなった。そのため、常にASSERTをスルーできるように
	// TRUEを返す関数として残しておく。
	return TRUE;
	#endif
}

#ifdef PM_DEBUG
//------------------------------------------------------------------
/**
 * 全メモリブロックを解放してあるかチェック（デバッグ用）
 *（※この関数が呼ばれた時にまだ使用メモリが残っているとASSERTで止まる）
 *
 * @param   heapID		ヒープＩＤ
 *
 */
//------------------------------------------------------------------
void sys_CheckHeapFullReleased( u32 heapID )
{
	if( HeapSys.count[heapID] )
	{
		PrintUnreleasedMemoryInfo( heapID );
		GF_ASSERT(0);
	}
}
//------------------------------------------------------------------
/**
 * ヒープから確保したメモリブロックの実サイズ取得（デバッグ用）
 *
 * @param   memBlock		
 *
 * @retval  u32		メモリブロックサイズ
 */
//------------------------------------------------------------------
u32 sys_GetMemoryBlockSize( const void* memBlock )
{
	((u8*)memBlock) -= sizeof(MEMORY_BLOCK_HEADER);
	return NNS_FndGetSizeForMBlockExpHeap( memBlock );
}

//------------------------------------------------------------------
/**
 * 指定ヒープのメモリアロケート回数＆空き領域サイズを64bitにパックして返す
 *（ヒープ破棄時とは別にリークチェックを行うため）
 *
 * @param   heapID		ヒープID
 *
 * @retval  u64		
 */
//------------------------------------------------------------------
u64 sys_GetHeapState( u32 heapID )
{
	if( heapID < HeapSys.heapMax )
	{
		u64  ret;
		NNSFndHeapHandle h;

		h = GetHeapHandle(heapID);
		ret = (HeapSys.count[heapID] << 32) | NNS_FndGetTotalFreeSizeForExpHeap(h);
		return ret;
	}
	GF_ASSERT(0);
	return 0;
}

/*---------------------------------------------------------------------------*
 * @brief	デバッグ用メモリ状況表示
*---------------------------------------------------------------------------*/

//------------------------------------------------------------------
/**
 * 特定ヒープのメモリ空き容量合計を表示
 *
 * @param   heapID		
 *
 */
//------------------------------------------------------------------
void sys_PrintHeapFreeSize( u32 heapID )
{
	if( heapID < HeapSys.heapMax )
	{
		NNSFndHeapHandle h = GetHeapHandle(heapID);
		OS_TPrintf("HEAP(ID :%d) FreeArea = %ld bytes\n", heapID, NNS_FndGetTotalFreeSizeForExpHeap(h) );
	}
}
//------------------------------------------------------------------
/**
 * 特定ヒープの使用中メモリブロック情報を表示
 *
 * @param   heapID		
 *
 */
//------------------------------------------------------------------
void sys_PrintHeapExistMemoryInfo( u32 heapID )
{
	PrintExistMemoryBlocks( heapID );
}
//------------------------------------------------------------------
/**
 * 特定ヒープの全メモリブロック情報を表示
 *
 * @param   heapID				ヒープID
 *
 */
//------------------------------------------------------------------
static void PrintExistMemoryBlocks( u32 heapID )
{
	NNSFndHeapHandle h = GetHeapHandle(heapID);
	NNS_FndVisitAllocatedForExpHeap( h, HeapConflictVisitorFunc, 0 );
}
//------------------------------------------------------------------
/**
 * sys_PrintHeapConflictのチェック結果がエラーなら、
 * 全メモリブロック情報を引数にしてこの関数が呼ばれる
 *
 * @param   memBlock		
 * @param   heapHandle		
 * @param   param		
 *
 */
//------------------------------------------------------------------
static void HeapConflictVisitorFunc(void* memBlock, NNSFndHeapHandle heapHandle, u32 param)
{
	char  filename[MEMBLOCK_FILENAME_AREASIZE + 1];
	int i;

	MEMORY_BLOCK_HEADER* head = (MEMORY_BLOCK_HEADER*)memBlock;

	CopyFileName( filename, head );

	GF_ASSERT_Printf(filename);
	GF_ASSERT_Printf(" (%d)", head->lineNum );
	GF_ASSERT_Printf(" adr:%08x", (u8*)memBlock + sizeof(MEMORY_BLOCK_HEADER));
	GF_ASSERT_Printf(" siz:%05x\n", NNS_FndGetSizeForMBlockExpHeap(head));
}

//------------------------------------------------------------------
/**
 * メモリブロックヘッダに保存されているファイル名をバッファにコピー
 *
 * @param   dst			コピー先バッファ
 * @param   header		メモリブロックヘッダ
 *
 */
//------------------------------------------------------------------
static void CopyFileName( char* dst, const MEMORY_BLOCK_HEADER* header )
{
	int i;

	// 終端コードナシで領域めいっぱいファイル名に使ってるため
	// こういう処理が必要...
	for(i = 0; i < MEMBLOCK_FILENAME_AREASIZE; i++)
	{
		if( header->filename[i] == '\0' ){ break; }
		dst[i] = header->filename[i];
	}
	dst[i] = '\0';

}

//------------------------------------------------------------------
/**
 * 未解放メモリの情報をプリント
 *
 * @param   heapID		
 *
 */
//------------------------------------------------------------------
static void PrintUnreleasedMemoryInfo( u32 heapID )
{
	GF_ASSERT_Printf("these Memoryblocks haven't released\n");
	GF_ASSERT_Printf("HeapID:%d  restcnt = %d .....\n", heapID, HeapSys.count[heapID]);
	#ifdef PM_DEBUG
	{
		NNSFndHeapHandle  handle = GetHeapHandle(heapID);
		u32  siz = NNS_FndGetTotalFreeSizeForExpHeap( handle );
		GF_ASSERT_Printf(" ID %d  freesize = 0x%x bytes \n", heapID, siz );
	}
	#endif
	PrintExistMemoryBlocks( heapID );
}

//==============================================================================================
// デバッグ用ヒープ状態スタック
//==============================================================================================

struct _HEAP_STATE_STACK {
	u16   sp;
	u16   stackNum;
	u32   heapID;
	u64   stack[0];
};

//------------------------------------------------------------------
/**
 * ヒープ状態スタックを新規作成
 *
 * @param   heapID			チェックするヒープID
 * @param   stackNum		スタック要素数
 *
 * @retval  HEAP_STATE_STACK*		作成したスタックへのポインタ
 */
//------------------------------------------------------------------
HEAP_STATE_STACK*  HSS_Create( u32 heapID, u32 stackNum )
{
	HEAP_STATE_STACK* hss;
	u32 size;

	size = sizeof(HEAP_STATE_STACK) + sizeof(u64)*stackNum;
	hss = sys_AllocMemoryLo( HEAPID_BASE_DEBUG, size );
	hss->sp = 0;
	hss->heapID = heapID;
	return hss;
}

//------------------------------------------------------------------
/**
 * ヒープ状態 Push
 *
 * @param   hss		スタックへのポインタ
 *
 */
//------------------------------------------------------------------
void HSS_Push( HEAP_STATE_STACK* hss )
{
	GF_ASSERT( hss->sp < hss->stackNum );
	hss->stack[hss->sp++] = sys_GetHeapState( hss->heapID );
}

//------------------------------------------------------------------
/**
 * ヒープ状態 Pop
 *
 * @param   hss		スタックへのポインタ
 *
 */
//------------------------------------------------------------------
void HSS_Pop( HEAP_STATE_STACK* hss )
{
	GF_ASSERT( hss->sp );
	hss->sp--;
	GF_ASSERT( hss->stack[hss->sp] == sys_GetHeapState(hss->heapID) );
}


//------------------------------------------------------------------
/**
 * ヒープ状態スタックを破棄する
 *
 * @param   hss		スタックへのポインタ
 *
 */
//------------------------------------------------------------------
void HSS_Delete( HEAP_STATE_STACK* hss )
{
	sys_FreeMemoryEz( hss );
}


#endif	// PM_DEBUG


