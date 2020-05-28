//=============================================================================================
/**
 * @file	tcb.c
 * @brief	汎用タスク制御モジュール本体
 * @author	tamada(GAME FREAK Inc.)
 * @date	2005.10.06
 * @since	2003.01.20
 *
 * @data	2004.10.14 AGB -> NDS
 * @author	Hiroyuki Nakamura
 *
 * @date	2005.10.06
 */
//=============================================================================================
#include <nitro.h>
#include "tcb.h"
#include "heapsys.h"
#include "assert.h"

//=============================================================================================
//	
//=============================================================================================
#define TASK_ADDPROC_CHECK		///< このフラグが有効だと、TCB_Add 動作中に割り込みでTCB_Mainが呼ばれた時、処理を行わない。



//=============================================================================================
//	定義
//=============================================================================================
enum{
	TCB_ENABLE = 0,
	TCB_DISABLE = 1,
};

//------------------------------------------------------------------
/** @brief	TCB構造体の定義
 *
 * TCB構造体は、動作優先順位に従ってリンクされる。
 * そのため双方向リンクを構成するように前後へのポインタを持つ。
 *
 * また、それぞれの実際の処理に必要なワークエリアは持たず、
 * TCB登録時に使用するワークエリアを引数として渡す。
 *
 * ユーザーレベルでは参照する必要のないメンバへのアクセスを制限するため、
 * この構造体はモジュール内からしかアクセスできない。
 * 必要な部分はアクセス関数を経由するようになっている。
 */
//------------------------------------------------------------------
typedef struct _TCB {
	TCBSYS* sys;				///<自分を管理しているTCBシステムへのポインタ
	TCB_PTR prev;				///<前のTCBへのポインタ
	TCB_PTR next;				///<続くTCBへのポインタ
	u32 pri;					///<プライオリティ
	void * work;				///<ワークエリアへのポインタ
	TCB_FUNC func;				///<実行関数へのポインタ

	u32 sw_flag;				///<関数追加フラグ
}TCB;	// 52 bytes


typedef struct _TCBSYS {
	u16			tcb_max;		///< 登録可能なTCBの最大数
	u16			tcb_stack_ptr;	///< 自信が抱えているTCB用スタックのポインタ
	TCB			tcb_first;		///< TCB先頭実体
	TCB_PTR*	tcb_stack;		///< TCB用スタック
	TCB*		tcb_table;		///< TCB実体テーブル
	BOOL		adding_flag;	///< TCB追加処理実行中フラグ（このフラグが立っている間にMainを実行しない）


	TCB_PTR		now_chain;		///< メインループ制御内使用連結整合維持TCBポインタ
	TCB_PTR		next_chain;		///< メインループ制御内使用連結整合維持TCBポインタ
}TCBSYS;	// 68 bytes


//==============================================================
// Prototype
//==============================================================
static void TCB_WorkClear( TCBSYS* tcbsys, TCB_PTR tcb);
static void InitTCBStack( TCBSYS* tcbsys );
static TCB * PopTCB( TCBSYS* tcbsys );
static int PushTCB( TCBSYS* tcbsys, TCB * tcb );
static TCB_PTR AddTask( TCBSYS* tcbsys, TCB_FUNC func, void* work, u32 pri );


//=============================================================================================
//
//	ローカル関数
//
//=============================================================================================
//------------------------------------------------------------------
/**
 * @brief	TCB構造体の初期化
 *
 * TCBのメンバ変数を初期化する
 * ＊関数版とマクロ版があります
 *
 * @param	tcb	TCBへのポインタ
 * @return	none	
 */
//------------------------------------------------------------------
#define TCBWorkClear(psys,ptcb)			\
{										\
	(ptcb)->sys = (psys);				\
	(ptcb)->prev = 						\
	(ptcb)->next = &(psys->tcb_first);	\
										\
	(ptcb)->pri = 0;					\
	(ptcb)->work = NULL;				\
	(ptcb)->func = NULL;				\
}

static void TCB_WorkClear( TCBSYS* tcbsys, TCB_PTR tcb)
{
	tcb->sys = tcbsys;

	tcb->prev = 
	tcb->next = &(tcbsys->tcb_first);

	tcb->pri = 0;
	tcb->work = NULL;
	tcb->func = NULL;
}
//------------------------------------------------------------------
/**
 * @brief	TCBスタック初期化
 *
 * 未使用TCBを保持するスタックを初期化する
 */
//------------------------------------------------------------------
static void InitTCBStack( TCBSYS* tcbsys )
{
	int i;

	for( i=0; i<tcbsys->tcb_max; i++ )
	{
		TCB_WorkClear( tcbsys, &(tcbsys->tcb_table[i]) );
		tcbsys->tcb_stack[i] = tcbsys->tcb_table + i;
	}
	tcbsys->tcb_stack_ptr = 0;
}

//------------------------------------------------------------------
/**
 * @brief	TCBスタックからの取り出し
 *
 * @retval	NULL以外	TCBへのポインタ
 * @retval	NULL		取り出しに失敗（スタックが空だった場合）
 */
//------------------------------------------------------------------
static TCB * PopTCB( TCBSYS* tcbsys )
{
	TCB_PTR tcb;
	if(tcbsys->tcb_stack_ptr == tcbsys->tcb_max)
	{
		return NULL;
	}
	tcb = tcbsys->tcb_stack[ tcbsys->tcb_stack_ptr ];
	tcbsys->tcb_stack_ptr++;
	return tcb;
}

//------------------------------------------------------------------
/**
	@brief	TCBスタックへのプッシュ

	@param	tcb		プッシュするTCBのポインタ
	@retval	TRUE	成功
	@retval	FALSE	失敗（スタックがいっぱいの場合）
*/
//------------------------------------------------------------------
static int PushTCB( TCBSYS* tcbsys, TCB * tcb )
{
	if(tcbsys->tcb_stack_ptr == 0)
	{
		return FALSE;
	}
	TCBWorkClear( tcbsys, tcb );	//値をクリアしてからスタックに積む
	tcbsys->tcb_stack_ptr--;
	tcbsys->tcb_stack[ tcbsys->tcb_stack_ptr ] = tcb;
	return TRUE;
}


//=============================================================================================
//
//	公開関数
//
//=============================================================================================

//------------------------------------------------------------------
/**
 * TCB システムを構築するのに必要なメモリ量を計算
 *
 * @param   task_max		稼働できる最大タスク数
 *
 * @retval  u32		メモリサイズ（バイト単位）
 */
//------------------------------------------------------------------
u32 TCBSYS_CalcSystemWorkSize( u32 task_max )
{
	return sizeof(TCBSYS) + (sizeof(TCB_PTR)+sizeof(TCB)) * task_max;
}

//------------------------------------------------------------------
/**
 * TCBシステムを作成
 *
 * @param   task_max		稼働できる最大タスク数
 * @param   work_area		システム作成に必要充分なサイズのワークエリアアドレス
 *
 * @retval  TCBSYS*		作成されたTCBシステムポインタ
 *
 * work_area に必要なサイズは、TCBSYS_CalcSystemWorkSize で計算する。
 */
//------------------------------------------------------------------
TCBSYS*  TCBSYS_Create( u32 task_max, void* work_area )
{
	TCBSYS* tcbsys;

	GF_ASSERT( work_area );

	tcbsys = work_area;

	tcbsys->tcb_stack = (TCB_PTR*) ((u8*)(tcbsys) + sizeof(TCBSYS));
	tcbsys->tcb_table = (TCB*) ((u8*)(tcbsys->tcb_stack) + sizeof(TCB_PTR)*task_max);

	tcbsys->tcb_max = task_max;
	tcbsys->tcb_stack_ptr = 0;
	tcbsys->adding_flag = FALSE;

	TCBSYS_Init( tcbsys );

	return tcbsys;
}

//------------------------------------------------------------------
/**
 *	システム使用前の初期化
 */
//------------------------------------------------------------------
void TCBSYS_Init( TCBSYS* tcbsys )
{
	//スタックの初期化
	InitTCBStack( tcbsys );
	//先頭ブロックの初期化
	TCBWorkClear( tcbsys, &tcbsys->tcb_first );

	tcbsys->now_chain = tcbsys->tcb_first.next;
}

//------------------------------------------------------------------
//	TCBメイン
//------------------------------------------------------------------
void TCBSYS_Main( TCBSYS* tcbsys )
{
	#ifdef TASK_ADDPROC_CHECK
	if( tcbsys->adding_flag )
	{
		return;
	}
	#endif

	tcbsys->now_chain = tcbsys->tcb_first.next;	//ここが実行の始めの場所
	while (tcbsys->now_chain != &(tcbsys->tcb_first))
	{
		//実行関数内でブロックが削除された時用にアドレスを保存
		tcbsys->next_chain = tcbsys->now_chain->next;

		if(tcbsys->now_chain->sw_flag == TCB_ENABLE){//登録直後の動作を避ける
			if(tcbsys->now_chain->func != NULL){
				tcbsys->now_chain->func(tcbsys->now_chain, tcbsys->now_chain->work);
			}
		}else{
			tcbsys->now_chain->sw_flag = TCB_ENABLE;
		}
		tcbsys->now_chain = tcbsys->next_chain;	//次の連結へ
	}
	tcbsys->now_chain->func = NULL;
}

//------------------------------------------------------------------------------
/**
	@brief	TCBを追加する
	@param	tcbsys	TCBシステムポインタ
	@param	func	TCB_FUNC:関連付ける実行関数ポインタ
	@param	work	void*:関連付けるワークエリアへのvoid型ポインタ
	@param	pri		u32:タスクプライオリティ

	@return	TCB_PTR	追加したTCBを示すポインタ
*/
//------------------------------------------------------------------------------
TCB_PTR TCBSYS_AddTask( TCBSYS* tcbsys, TCB_FUNC func, void* work, u32 pri )
{
	TCB_PTR  ret;

	tcbsys->adding_flag = TRUE;
	ret = AddTask( tcbsys, func, work, pri );
	tcbsys->adding_flag = FALSE;
	return ret;

}
//------------------------------------------------------------------
/**
 * TCB追加処理
 *
 * @param   tcbsys		TCBシステムポインタ
 * @param   func		TCBに関連付ける関数ポインタ
 * @param   work		TCBに関連付けるワークエリアへのポインタ
 * @param   pri			タスクプライオリティ
 *
 * @retval  TCB_PTR		追加したTCBポインタ
 */
//------------------------------------------------------------------
static TCB_PTR AddTask( TCBSYS* tcbsys, TCB_FUNC func, void* work, u32 pri )
{
	TCB_PTR get;
	TCB_PTR find;

	get = PopTCB( tcbsys );	//空いているTCBを拾う
	if(get == NULL)
	{
		//登録しようとしたがタスクがなかった
		OS_TPrintf("ERR : TCB wasn't get!");
		return NULL;
	}

	//パラメータをセット
	get->pri = pri;
	get->work = work;
	get->func = func;
	//動作フラグ設定
	if(tcbsys->now_chain->func != NULL){
		//動作フラグ設定(別のタスクから追加されようとしている場合、登録直後の動作を避ける処理)
		if(tcbsys->now_chain->pri <= pri){
			get->sw_flag = TCB_DISABLE;
		}else{
			get->sw_flag = TCB_ENABLE;
		}
	}
	else{
		//本タスク外からの登録
		get->sw_flag = TCB_ENABLE;
	}

	//実行リストに接続(同じプライオリティの時には、先に登録したほうが先)
	for(find = tcbsys->tcb_first.next; find != &(tcbsys->tcb_first); find = find->next)
	{
		if(find->pri > get->pri){	//findの前にgetをつなげる
			get->prev = find->prev;
			get->next = find;
			find->prev->next = get;
			find->prev = get;
			if(find == tcbsys->next_chain){
				tcbsys->next_chain = get;
			}
			return get;
		}
	}
	//最後まで繋ぐところが見つからなければ最後に繋ぐ
	if(tcbsys->next_chain == &(tcbsys->tcb_first)){
		tcbsys->next_chain = get;
	}
	get->prev = tcbsys->tcb_first.prev;	//今までの最後
	get->next = &(tcbsys->tcb_first);	//自分が最後
	tcbsys->tcb_first.prev->next = get;	//今まで最後だったブロックの次は自分
	tcbsys->tcb_first.prev = get;		//リストの最後を更新
	return get;
}

//------------------------------------------------------------------------------
/**
	@brief	TCBを消去する
	@param	tcb		TCBポインタ
*/
//------------------------------------------------------------------------------
void TCBSYS_DeleteTask( TCB_PTR tcb )
{
	//連結システムの次のリンク先が削除対象の場合の処理
	if(tcb->sys->next_chain == tcb){
		tcb->sys->next_chain = tcb->next;	//削除対象TCBの次TCBへ連結情報を移動
	}
	//リストから削除
	tcb->prev->next = tcb->next;
	tcb->next->prev = tcb->prev;

	PushTCB( tcb->sys, tcb );
}


//==================================================================
//	TCBアクセス関数
//==================================================================

//------------------------------------------------------------------
//TCBの動作関数を切り替える
//------------------------------------------------------------------
void TCB_ChangeFunc(TCB_PTR tcb, TCB_FUNC func)
{
	tcb->func = func;
}

//------------------------------------------------------------------
//TCBのワークアドレス取得
//------------------------------------------------------------------
void * TCB_GetWork(TCB_PTR tcb)
{
	return tcb->work;
}

//------------------------------------------------------------------
//TCBプライオリティの取得
//------------------------------------------------------------------
u32 TCB_GetPriority(TCB_PTR tcb)
{
	return tcb->pri;
}







