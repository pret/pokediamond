//=============================================================================
/**
 * @file	プロセス管理システム
 * @brief
 * @date	2005.07.25
 */
//=============================================================================

#include "common.h"
#include "system\pm_overlay.h"

#include "system/procsys.h"


//------------------------------------------------------------------
/**
 * @brief	プロセス内部の動作シーケンス
 */
//------------------------------------------------------------------
enum {
	SEQ_OVERLAY_LOAD = 0,
	SEQ_INIT,
	SEQ_MAIN,
	SEQ_END,
	SEQ_OVERLAY_UNLOAD,
};


//------------------------------------------------------------------
/**
 * @brief	プロセス構造体定義
 */
//------------------------------------------------------------------
struct _PROC{
	PROC_DATA data;				///<プロセス定義データへのポインタ
	int proc_seq;				///<プロセス内部シーケンス
	int subseq;					///<プロセス関数の動作シーケンス
	void * parent_work;			///<上位ワークへのポインタ
	void * work;				///<プロセス内部ワークへのポインタ
	PROC * parent;				///<上位プロセスへのポインタ
	PROC * child;				///<下位プロセスへのポインタ
};


//===========================================================================
//
//		関数
//
//===========================================================================
//------------------------------------------------------------------
/**
 * @brief	プロセス生成処理
 * @param	func		プロセス動作関数
 * @param	parent_work	上位から引き渡すワークへのポインタ
 * @param	heap_id	使用するヒープ
 * @return	PROC		生成したプロセスへのポインタ
 */
//------------------------------------------------------------------
PROC * PROC_Create(const PROC_DATA * data, void * parent_work, const int heap_id)
{
	PROC * proc;
	proc = sys_AllocMemory(heap_id, sizeof(PROC));
	proc->data = *data;
	proc->proc_seq = 0;
	proc->subseq = 0;
	proc->parent_work = parent_work;
	proc->work = NULL;
	proc->parent = NULL;
	proc->child = NULL;
	return proc;
}

//------------------------------------------------------------------
/**
 * @brief	子プロセスを生成する
 * @param	proc		現在の動作プロセスへのポインタ
 * @param	func		プロセス動作関数
 * @param	parent_work	上位から引き渡すワークへのポインタ
 * @param	heap_id	使用するヒープ
 * @return	PROC		生成したプロセスへのポインタ
 */
//------------------------------------------------------------------
PROC * PROC_CreateChild(PROC * proc, const PROC_DATA * data, void * parent_work, const int heap_id)
{
	PROC * child;
	child = PROC_Create(data, parent_work, heap_id);
	proc->child = child;
	child->parent = proc;
	return child;
}
//------------------------------------------------------------------
/**
 * @brief	プロセスを削除する
 * @param	proc	プロセスへのポインタ
 */
//------------------------------------------------------------------
void PROC_Delete(PROC * proc)
{
	SDK_ASSERT(proc->work == NULL);
	sys_FreeMemoryEz(proc);
}

//------------------------------------------------------------------
/**
 * @brief	プロセス内ワークの確保
 * @param	proc	プロセスへのポインタ
 * @param	size	確保するワークサイズ
 * @param	heap_id	使用するヒープ
 * @return	void *	確保したプロセス内ワークへのポインタ
 */
//------------------------------------------------------------------
void * PROC_AllocWork(PROC * proc, int size, int heap_id)
{
	proc->work = sys_AllocMemory(heap_id, size);
	return proc->work;
}

//------------------------------------------------------------------
/**
 * @brief	プロセス内ワークのポインタ取得
 * @param	proc	プロセスへのポインタ
 * @return	void *	プロセス内ワークへのポインタ
 */
//------------------------------------------------------------------
void * PROC_GetWork(PROC * proc)
{
	SDK_ASSERT(proc->work != NULL);
	return proc->work;
}

//------------------------------------------------------------------
/**
 * @brief	プロセス内ワークの解放
 * @param	proc	プロセスへのポインタ
 */
//------------------------------------------------------------------
void PROC_FreeWork(PROC * proc)
{
	SDK_ASSERT(proc->work != NULL);
	sys_FreeMemoryEz(proc->work);
	proc->work = NULL;
}

//------------------------------------------------------------------
/**
 * @brief	上位ワークへのポインタ取得
 * @param	proc	プロセスへのポインタ
 * @return	void *	上位ワークへのポインタ
 */
//------------------------------------------------------------------
void * PROC_GetParentWork(PROC * proc)
{
	SDK_ASSERT(proc->parent_work != NULL);
	return proc->parent_work;
}

//------------------------------------------------------------------
/**
 * @brief	プロセス動作処理メイン
 * @param	proc	プロセスへのポインタ
 * @retval	TRUE	プロセス動作終了
 * @retval	FALSE	プロセス動作継続中
 */
//------------------------------------------------------------------
BOOL ProcMain(PROC * proc)
{
	PROC_RESULT result;

	switch (proc->proc_seq) {
	case SEQ_OVERLAY_LOAD:
		if(proc->data.overlay_id != NO_OVERLAY_ID){
			TPRINTF("OVERLAY ID = %d\n", proc->data.overlay_id);
			Overlay_Load( proc->data.overlay_id, OVERLAY_LOAD_NOT_SYNCHRONIZE);
		}
		proc->proc_seq = SEQ_INIT;

		/* fallthru */
			
	case SEQ_INIT:
		result = proc->data.init_func(proc, &proc->subseq);
		if (result == PROC_RES_FINISH) {
			proc->proc_seq = SEQ_MAIN;
			proc->subseq = 0;
		}
		break;
	case SEQ_MAIN:
		result = proc->data.main_func(proc, &proc->subseq);
		if (result == PROC_RES_FINISH) {
			proc->proc_seq = SEQ_END;
			proc->subseq = 0;
		}
		break;
	case SEQ_END:
		result = proc->data.end_func(proc, &proc->subseq);
		if (result == PROC_RES_FINISH) {
			if(proc->data.overlay_id != NO_OVERLAY_ID){
				Overlay_UnloadID( proc->data.overlay_id );
			}
			return TRUE;
		}
		break;
	}
	return FALSE;
}


