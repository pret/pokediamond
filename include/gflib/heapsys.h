//==============================================================================
/**
 *
 *@file		heapsys.h
 *@brief	ヒープ領域管理
 *@author	taya
 *@data		2005.08.25
 *
 */
//==============================================================================
#ifndef __HEAPSYS_H__
#define __HEAPSYS_H__

#include <nnsys.h>

//==============================================================
/**
 *	基本ヒープ作成パラメータ構造体
 */
//==============================================================
typedef struct {
	u32        size;		///< ヒープサイズ
	OSArenaId  arenaID;		///< 作成先アリーナID
}HEAP_INIT_HEADER;



//------------------------------------------------------------------
/**
 * ヒープシステム初期化（プログラム起動時に１度だけ呼ばれる）
 *
 * @param   header			基本ヒープ初期化構造体へのポインタ
 * @param   baseHeapMax		基本ヒープ総数
 * @param   heapMax			基本ヒープ・ユーザーヒープ合計数
 * @param   startOffset		ヒープ領域開始オフセット（要４バイトアライン）
 *
 */
//------------------------------------------------------------------
extern void sys_InitHeapSystem(const HEAP_INIT_HEADER* header, u32 baseHeapMax, u32 totalHeapMax, u32 startOffset);


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
extern BOOL sys_CreateHeap( u32 parentHeapID, u32 childHeapID, u32 size );


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
extern BOOL sys_CreateHeapLo( u32 parentHeapID, u32 childHeapID, u32 size );

//------------------------------------------------------------------
/**
 * ヒープ破棄
 *
 * @param   heapID		ヒープID
 *
 */
//------------------------------------------------------------------
extern void sys_DeleteHeap( u32 heapID );


//------------------------------------------------------------------
/*
 * 	メモリ確保
 *
 *	sys_AllocMemory はヒープの先頭から空き領域を探してメモリを割り当てる。
 *	sys_AllocMemoryLo はヒープの後方から空き領域を探してメモリを割り当てる。
 *
 *	VRAM転送前のグラフィックデータ一時的読み込み領域など、すぐに解放する領域は
 *	sys_AllocMemoryLo で確保すれば領域の断片化が起こりづらくなるはず。
 */
//------------------------------------------------------------------

#ifndef PM_DEBUG
extern void* sys_AllocMemory( u32 heap, u32 size );
extern void* sys_AllocMemoryLo( u32 heap, u32 size );
#else


// デバッグビルド時にはマクロでラップして呼び出しソース情報を渡している

extern void* sys_AllocMemoryDebug( u32 heap, u32 size, const char* filename, u32 line_num );
extern void* sys_AllocMemoryLoDebug( u32 heap, u32 size, const char* filename, u32 line_num );
#define sys_AllocMemory(h,s)	sys_AllocMemoryDebug((h),(s),__FILE__,__LINE__);
#define sys_AllocMemoryLo(h,s)	sys_AllocMemoryLoDebug((h),(s),__FILE__,__LINE__);

#endif


//------------------------------------------------------------------
/*
 * 	メモリ解放
 *
 *  確保時にu32をヘッダに保存するため、解放時には不要。
 *  通常は sys_FreeMemoryEz を使えば問題ない。
 *
 *  sys_FreeMemory の方は、一応そのままのインターフェースで残してある
 *
 */
//------------------------------------------------------------------
extern void sys_FreeMemoryEz( void* memory );
extern void sys_FreeMemory( u32 heap, void* memory );


//------------------------------------------------------------------
/*
 * 	ヒープ情報取得
 */
//------------------------------------------------------------------
extern u32 sys_GetHeapFreeSize( u32 heap );
extern u32 sys_GetHeapAllocatedSize( u32 heap );

//------------------------------------------------------------------
/*
 * 	アロケーター作成（NitroSystem ライブラリ系関数が要求する場合がある）
 */
//------------------------------------------------------------------
extern void sys_InitAllocator( NNSFndAllocator* pAllocator, u32 heap, int alignment);


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
extern void sys_CutMemoryBlockSize( void* memBlock, u32 newSize );


//------------------------------------------------------------------
/*
 * 	ヒープ情報取得（デバッグ時のみ有効）
 */
//------------------------------------------------------------------
extern BOOL sys_CheckHeapSafe( u32 heap );

#ifdef PM_DEBUG
extern void sys_PrintHeapFreeSize( u32 heapID );
extern void sys_PrintHeapExistMemoryInfo( u32 heapID );
extern u64 sys_GetHeapState( u32 heapID );
extern void sys_PrintHeapConflict( u32 heap, u32 assertionMemSize ); 
extern u32 sys_GetMemoryBlockSize( const void* memBlock );
extern void sys_CheckHeapFullReleased( u32 heapID );
#else
#define sys_PrintHeapFreeSize(h)		/* */
#define sys_PrintHeapExistMemoryInfo(h)	/* */
#define sys_GetHeapState(h)				/* */
#define sys_PrintHeapConflict(h, s)		/* */
#define sys_GetMemoryBlockSize(b)		/* */
#define sys_CheckHeapFullReleased(h)	/* */
#endif


//------------------------------------------------------------------
/*
 * 	ヒープ情報取得（デバッグ時のみ有効）
 */
//------------------------------------------------------------------
typedef struct _HEAP_STATE_STACK	HEAP_STATE_STACK;

#ifdef PM_DEBUG
extern HEAP_STATE_STACK*  HSS_Create( u32 heapID, u32 stackNum );
extern void HSS_Push( HEAP_STATE_STACK* hss );
extern void HSS_Pop( HEAP_STATE_STACK* hss );
extern void HSS_Delete( HEAP_STATE_STACK* hss );
#else
#define HSS_Create(a,b,c)	((void)0);
#define HSS_Push(p)			((void)0);
#define HSS_Pop(p)			((void)0);
#define HSS_Delete(p)		((void)0);
#endif



//------------------------------------------------------------------
/*
 * 	簡単メモリリークチェック（現在は無効）
 */
//------------------------------------------------------------------
#define HeapStatePush()		/* */
#define HeapStatePop()		/* */
#define HeapStateCheck(h)	/* */




#endif	// __HEAPSYS_H__
