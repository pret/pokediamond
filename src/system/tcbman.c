//=============================================================================================
/**
 * @file	tcbman.c
 * @brief	各TCBシステムを介してタスク処理を呼び出す
 * @author	taya
 * @date	2005.10.07
 */
//=============================================================================================
#include "common.h"
#include "tcb.h"


//------------------------------------------------------------------
/**
 * TCB登録（メインループ中に呼ばれるタスク）
 *
 * @param   func		タスク実行関数
 * @param   work		タスクに関連付けるワークエリアのアドレス
 * @param   pri			タスクプライオリティ
 *
 * @retval  TCB_PTR		登録されたTCBポインタ
 */
//------------------------------------------------------------------
TCB_PTR TCB_Add(TCB_FUNC func, void* work, u32 pri)
{
	return TCBSYS_AddTask( sys.mainTCBSys, func, work, pri );
}
//------------------------------------------------------------------
/**
 * TCB登録（VBlank割り込み中に呼ばれるタスク）
 *
 * @param   func		タスク実行関数
 * @param   work		タスクに関連付けるワークエリアのアドレス
 * @param   pri			タスクプライオリティ
 *
 * @retval  TCB_PTR		登録されたTCBポインタ
 */
//------------------------------------------------------------------
TCB_PTR VIntrTCB_Add( TCB_FUNC func, void* work, u32 pri )
{
	return TCBSYS_AddTask( sys.vintrTCBSys, func, work, pri );
}

//------------------------------------------------------------------
/**
 * TCB登録（文字出力タスク=VBlank割り込み前に呼ばれる）
 *
 * @param   func		タスク実行関数
 * @param   work		タスクに関連付けるワークエリアのアドレス
 * @param   pri			タスクプライオリティ
 *
 * @retval  TCB_PTR		登録されたTCBポインタ
 */
//------------------------------------------------------------------
TCB_PTR PrintTCB_Add( TCB_FUNC func, void* work, u32 pri )
{
	return TCBSYS_AddTask( sys.printTCBSys, func, work, pri );
}

//------------------------------------------------------------------
/**
 * TCB登録（メインループ終了待ち後の同期用タスク）
 *
 * @param   func		タスク実行関数
 * @param   work		タスクに関連付けるワークエリアのアドレス
 * @param   pri			タスクプライオリティ
 *
 * @retval  TCB_PTR		登録されたTCBポインタ
 */
//------------------------------------------------------------------
TCB_PTR VWaitTCB_Add( TCB_FUNC func, void* work, u32 pri )
{
	return TCBSYS_AddTask( sys.vwaitTCBSys, func, work, pri );
}


//------------------------------------------------------------------
/**
 * TCB削除
 *
 * @param   TCB_PTR		削除するTCBポインタ
 */
//------------------------------------------------------------------
void TCB_Delete(TCB_PTR tcb)
{
	TCBSYS_DeleteTask( tcb );
}

