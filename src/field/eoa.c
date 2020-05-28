//******************************************************************************
/**
 * 
 * @file	eoa.c
 * @brief	エフェクトオブジェクトアクター
 * @author	kagaya
 * @data	05.07.13
 *
 */
//******************************************************************************
#include "common.h"
#include "eoa.h"

//==============================================================================
//	define
//==============================================================================
//--------------------------------------------------------------
//	debug
//--------------------------------------------------------------
#ifdef PM_DEBUG
//#define DEBUG_EOA_USE_COUNT		//定義でEOA使用数をOS_Print()吐き出し
#endif

//--------------------------------------------------------------
//	EOAステータスビット
//--------------------------------------------------------------
#define EOA_STA_BIT_NON (0)									///<無し
#define EOA_STA_BIT_USE (1<<0)								///<使用中

//==============================================================================
//	typedef struct
//==============================================================================
//--------------------------------------------------------------
///	EOA構造体
//--------------------------------------------------------------
typedef struct _TAG_EOA
{
	u32 status_bit;
	int add_param;
	int answer;
	const void *add_ptr;
	TCB_PTR tcb;
	CONST_EOA_SYS_PTR es;
	int x;
	int y;
	int z;
	VecFx32 matrix;
	
	u8 work[EOA_LOCAL_WORK_SIZE];
	
	EOA_PROC_INIT proc_init;
	EOA_PROC_MOVE proc_move;
	EOA_PROC_DRAW proc_draw;
	EOA_PROC_DEL  proc_del;
	EOA_PROC_PUSH proc_push;
	EOA_PROC_POP  proc_pop;
}EOA;

#define EOA_SIZE (sizeof(EOA))	///<EOAサイズ

//--------------------------------------------------------------
///	EOA_SYS構造体
//--------------------------------------------------------------
typedef struct _TAG_EOA_SYS
{
	int max;
	int add_count;
	int heap_id;
	EOA_PTR eoa;
}EOA_SYS;

#define EOA_SYS_SIZE (sizeof(EOA_SYS))	///<EOA_SYSサイズ

//==============================================================================
//	プロトタイプ
//==============================================================================
static TCB_PTR eoa_MoveProcTCBAdd( EOA_PTR eoa, int pri );
static void eoa_MoveProcTCB( TCB_PTR tcb, void *wk );

static EOA_SYS_PTR eoa_SysAllocMemory( int heap_id );
static void eoa_SysFreeMemory( EOA_SYS_PTR es );
static EOA_PTR eoa_AllocMemory( int heap_id, int max );
static void eoa_FreeMemory( EOA_SYS_PTR es );
static void eoa_Clear( EOA_PTR eoa );

static int eoa_SysEoaMaxGet( CONST_EOA_SYS_PTR es );
static EOA_PTR eoa_SysEoaGet( CONST_EOA_SYS_PTR es );

static void eoa_StatusBit_UseSet( EOA_PTR eoa );
static void eoa_StatusBit_Set( EOA_PTR eoa, u32 bit );
static void eoa_AddParamSet( EOA_PTR eoa, int prm );
static void eoa_AddPtrSet( EOA_PTR eoa, const void *ptr );
static void eoa_TCBSet( EOA_PTR eoa, TCB_PTR tcb );
static TCB_PTR eoa_TCBGet( EOA_PTR eoa );
static void eoa_EoaSysSet( EOA_PTR eoa, CONST_EOA_SYS_PTR es );

//==============================================================================
//	eoa	システム
//==============================================================================
//--------------------------------------------------------------
/**
 * EOA初期化
 * @param	heap_id		EOAワークに使用するヒープID
 * @param	max			EOA最大数
 * @retval	EOA_SYS_PTR	追加されたEOA_SYS_PTR
 */
//--------------------------------------------------------------
EOA_SYS_PTR EOA_SysInit( int heap_id, int max )
{
	EOA_SYS_PTR es;
	
	es = eoa_SysAllocMemory( heap_id );
	es->eoa = eoa_AllocMemory( heap_id, max );
	
	es->max = max;
	es->heap_id = heap_id;
	
	return( es );
}

//--------------------------------------------------------------
/**
 * EOAシステム削除
 * @param	es		EOA_SYS_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void EOA_SysDelete( EOA_SYS_PTR es )
{
	eoa_FreeMemory( es );
	eoa_SysFreeMemory( es );
}

//--------------------------------------------------------------
/**
 * EOA全削除&EOAシステム削除
 * @param	es		EOA_SYS_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void EOA_SysDeleteAll( EOA_SYS_PTR es )
{
	EOA_DeleteAll( es );
	EOA_SysDelete( es );
}

//==============================================================================
//	eoa	追加削除
//==============================================================================
//--------------------------------------------------------------
/**
 * EOA追加
 * @param	es			EOA_SYS_PTR
 * @param	EOA_H		追加される情報が纏められたEOA_H
 * @param	mtx			初期位置
 * @param	prm			追加するEOAへ指定するパラメタ
 * @param	ptr			追加するEOAへ指定するポインタ
 * @param	pri			追加するEOAの動作プライオリティ
 * @retval	EOA_PTR		追加されたEOA_PTR NULL=追加失敗
 */
//--------------------------------------------------------------
EOA_PTR EOA_Add( EOA_SYS_PTR es, const EOA_H *head,
		const VecFx32 *mtx, int prm, const void *ptr, int pri )
{
	int i,max;
	EOA_PTR eoa;
	TCB_PTR tcb;
	
	i = 0;
	max = eoa_SysEoaMaxGet( es );
	eoa = eoa_SysEoaGet( es );
	
	do{
		if( EOA_StatusBit_UseCheck(eoa) == FALSE ){
			break;
		}
		
		i++;
		eoa++;
	}while( i < max );
	
	if( i >= max ){
		OS_Printf( "EOA MAX!! EOA USE COUNT 0x%x\n", es->add_count );
		return( NULL );
	}
	
	eoa_StatusBit_UseSet( eoa );
	eoa_AddParamSet( eoa, prm );
	eoa_AddPtrSet( eoa, ptr );
	eoa_EoaSysSet( eoa, es );
	EOA_MatrixSet( eoa, mtx );
	EOA_LocalWorkInit( eoa, head->work_size );
	
	EOA_InitProcSet( eoa, head->proc_init );
	EOA_DeleteProcSet( eoa, head->proc_del );
	EOA_MoveProcSet( eoa, head->proc_move );
	EOA_DrawProcSet( eoa, head->proc_draw );
	EOA_PushProcSet( eoa, head->proc_push );
	EOA_PopProcSet( eoa, head->proc_pop );
	
	tcb = eoa_MoveProcTCBAdd( eoa, pri );
	
	if( tcb == NULL ){
		eoa_Clear( eoa );
		return( NULL );
	}
	
	eoa_TCBSet( eoa, tcb );
	
	if( EOA_InitProcCall(eoa) == FALSE ){
		TCB_Delete( tcb );
		eoa_Clear( eoa );
		return( NULL );
	}
	
	es->add_count++;

#ifdef DEBUG_EOA_USE_COUNT
	{
		int space = es->max - es->add_count;
		OS_Printf("EOAが追加されました...");
		OS_Printf("EOA使用数=%d, EOA空き=%d, EOA最大数=%d\n",es->add_count,space,es->max);
	}
#endif
	
	return( eoa );
}

//--------------------------------------------------------------
/**
 * EOA追加 EOA_H_NPP型 退避、復帰関数はダミー関数になる
 * @param	es			EOA_SYS_PTR
 * @param	EOA_H_NPP	追加される情報が纏められたEOA_H_NPP
 * @param	mtx			初期位置
 * @param	prm			追加するEOAへ指定するパラメタ
 * @param	ptr			追加するEOAへ指定するポインタ
 * @param	pri			追加するEOAの動作プライオリティ
 * @retval	EOA_PTR		追加されたEOA_PTR NULL=追加失敗
 */
//--------------------------------------------------------------
EOA_PTR EOA_Add_NPP( EOA_SYS_PTR es, const EOA_H_NPP *head,
		const VecFx32 *mtx, int prm, const void *ptr, int pri )
{
	EOA_H eh;
	
	*(EOA_H_NPP *)&eh = *head;
	eh.proc_push = EOA_PushProcDummy;
	eh.proc_pop = EOA_PopProcDummy;
	
	return( EOA_Add(es,&eh,mtx,prm,ptr,pri) );
}

//--------------------------------------------------------------
/**
 * EOA削除
 * @param	eoa			削除するEOA_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void EOA_Delete( EOA_PTR eoa )
{
	GF_ASSERT( eoa != NULL && "EOA_Delete()eoa==NULLが渡されました" );
	
	if( EOA_StatusBit_UseCheck(eoa) == FALSE ){
		return;
	}
	
	EOA_DeleteProcCall( eoa );
	
	{
		EOA_SYS_PTR es = (EOA_SYS_PTR)eoa->es;
		es->add_count--;
	}
	
#ifdef DEBUG_EOA_USE_COUNT
	{
		EOA_SYS_PTR es = (EOA_SYS_PTR)eoa->es;
		int space = es->max - es->add_count;
		OS_Printf("EOAが削除されました...");
		OS_Printf("EOA使用数=%d, EOA空き=%d, EOA最大数=%d\n",es->add_count,space,es->max);
	}
#endif
	
	{
		TCB_PTR tcb = eoa_TCBGet( eoa );
		
		if( tcb != NULL ){
			TCB_Delete( tcb );
		}
	}
	
	eoa_Clear( eoa );
}

//old eoaの値をそのまま信用
#if 0
void EOA_Delete( EOA_PTR eoa )
{
	GF_ASSERT( eoa != NULL && "EOA_Delete()eoa==NULLが渡されました" );
	
	EOA_DeleteProcCall( eoa );
	
	{
		EOA_SYS_PTR es = (EOA_SYS_PTR)eoa->es;
		es->add_count--;
	}
	
#ifdef DEBUG_EOA_USE_COUNT
	{
		EOA_SYS_PTR es = (EOA_SYS_PTR)eoa->es;
		int space = es->max - es->add_count;
		OS_Printf("EOAが削除されました...");
		OS_Printf("EOA使用数=%d, EOA空き=%d, EOA最大数=%d\n",es->add_count,space,es->max);
	}
#endif
	
	TCB_Delete( eoa_TCBGet(eoa) );
	eoa_Clear( eoa );
}
#endif

//--------------------------------------------------------------
/**
 * 発生している全てのEOAに削除命令
 * @param	es		EOA_SYS_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void EOA_DeleteAll( EOA_SYS_PTR es )
{
	int max;
	EOA_PTR eoa;
	
	max = eoa_SysEoaMaxGet( es );
	eoa = eoa_SysEoaGet( es );
	
	do{
		if( EOA_StatusBit_UseCheck(eoa) == TRUE ){
			EOA_Delete( eoa );
		}
		
		eoa++; max--;
	}while( max );
}

//==============================================================================
//	eoa 描画
//==============================================================================
//--------------------------------------------------------------
/**
 * EOA 描画関数呼び出し
 * @param	es		EOA_SYS_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void EOA_SysDraw( EOA_SYS_PTR es )
{
	int max;
	EOA_PTR eoa;
	
	max = eoa_SysEoaMaxGet( es );
	eoa = eoa_SysEoaGet( es );
	
	do{
		if( EOA_StatusBit_UseCheck(eoa) == TRUE ){
			EOA_DrawProcCall( eoa );
		}
		
		eoa++;
		max--;
	}while( max );
}

//==============================================================================
//	eoa	TCB動作
//==============================================================================
//--------------------------------------------------------------
/**
 * EOA TCB動作関数セット
 * @param	eoa		EOA_PTR
 * @param	pri		TCBプライオリティ
 * @retval	nothing
 */
//--------------------------------------------------------------
static TCB_PTR eoa_MoveProcTCBAdd( EOA_PTR eoa, int pri )
{
	TCB_PTR tcb;
	
	tcb = TCB_Add( eoa_MoveProcTCB, eoa, pri );
	GF_ASSERT( tcb != NULL && "eoa_MoveProcTCBAdd TCB一杯" );
	
	return( tcb );
}

//--------------------------------------------------------------
/**
 * EOA TCB動作関数
 * @param	tcb	TCB_PTR
 * @param	wk	tcb work *
 * @retval	nothing
 */
//--------------------------------------------------------------
static void eoa_MoveProcTCB( TCB_PTR tcb, void *wk )
{
	EOA_PTR eoa;
	
	eoa = wk;
	EOA_MoveProcCall( eoa );
}

//==============================================================================
//	eoa	パーツ
//==============================================================================
//--------------------------------------------------------------
/**
 * EOAシステムメモリ確保
 * @param	heap_id			HEAP ID
 * @retval	EOA_SYS_PTR		確保したEOA_SYS_PTR
 */
//--------------------------------------------------------------
static EOA_SYS_PTR eoa_SysAllocMemory( int heap_id )
{
	EOA_SYS_PTR es;
	
	es = sys_AllocMemory( heap_id, EOA_SYS_SIZE );
	GF_ASSERT( es != NULL && "eoa_SysAllocMemoryメモリ確保エラー" );
	
	memset( es, 0, EOA_SYS_SIZE );
	return( es );
}

//--------------------------------------------------------------
/**
 * EOAシステムメモリ開放
 * @param	es			EOA_SYS_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void eoa_SysFreeMemory( EOA_SYS_PTR es )
{
	sys_FreeMemory( es->heap_id, es );
}

//--------------------------------------------------------------
/**
 * EOAメモリ確保
 * @param	heap_id		HEAP ID
 * @param	max			EOA最大数
 * @retval	eoa			確保したEOA_PTR
 */
//--------------------------------------------------------------
static EOA_PTR eoa_AllocMemory( int heap_id, int max )
{
	EOA_PTR eoa;
	
	max *= EOA_SIZE;
	eoa = sys_AllocMemory( heap_id, max );
	GF_ASSERT( eoa != NULL && "eoa_AllocMemoryメモリ確保エラー" );
	
	memset( eoa, 0, max );
	return( eoa );
}

//--------------------------------------------------------------
/**
 * EOAメモリ開放
 * @param	es			EOA_SYS_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void eoa_FreeMemory( EOA_SYS_PTR es )
{
	sys_FreeMemory( es->heap_id, es->eoa );
}

//--------------------------------------------------------------
/**
 * EOAクリア
 * @param	eoa			EOA_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void eoa_Clear( EOA_PTR eoa )
{
	memset( eoa, 0, EOA_SIZE );
	EOA_InitProcSet( eoa, EOA_InitProcDummy );
	EOA_DeleteProcSet( eoa, EOA_DeleteProcDummy );
	EOA_MoveProcSet( eoa, EOA_MoveProcDummy );
	EOA_DrawProcSet( eoa, EOA_DrawProcDummy );
	EOA_PushProcSet( eoa, EOA_PushProcDummy );
	EOA_PopProcSet( eoa, EOA_PopProcDummy );
}

//old 0 clearのみ
#if 0
static void eoa_Clear( EOA_PTR eoa )
{
	memset( eoa, 0, EOA_SIZE );
}
#endif

//==============================================================================
//	EOA_SYS参照
//==============================================================================
//--------------------------------------------------------------
/**
 * EOA最大数取得
 * @param	es		EOA_SYS_PTR
 * @retval	int		最大数
 */
//--------------------------------------------------------------
static int eoa_SysEoaMaxGet( CONST_EOA_SYS_PTR es )
{
	return( es->max );
}

//--------------------------------------------------------------
/**
 * EOAワークポインタ取得
 * @param	es		EOA_SYS_PTR
 * @retval	EOA_PTR	EOA_PTR
 */
//--------------------------------------------------------------
static EOA_PTR eoa_SysEoaGet( CONST_EOA_SYS_PTR es )
{
	return( es->eoa );
}

//==============================================================================
//	eoa	参照
//==============================================================================
//--------------------------------------------------------------
/**
 * eoa 使用中チェック
 * @param	eoa		EOA_PTR
 * @retval	int		TRUE=使用中。FALSE=未使用
 */
//--------------------------------------------------------------
int EOA_StatusBit_UseCheck( CONST_EOA_PTR eoa )
{
	if( (eoa->status_bit & EOA_STA_BIT_USE) ){
		return( TRUE );
	}
	
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * eoa ステータスビット　使用中セット
 * @param	eoa		EOA_PTR
 * @retval	int		TRUE=使用中。FALSE=未使用
 */
//--------------------------------------------------------------
static void eoa_StatusBit_UseSet( EOA_PTR eoa )
{
	eoa->status_bit |= EOA_STA_BIT_USE;
}

//--------------------------------------------------------------
/**
 * eoa ステータスビット　セット
 * @param	eoa		EOA_PTR
 * @param	bit		EOA_STA_BIT_NON等
 * @retval	int		TRUE=使用中。FALSE=未使用
 */
//--------------------------------------------------------------
static void eoa_StatusBit_Set( EOA_PTR eoa, u32 bit )
{
	eoa->status_bit = bit;
}

//--------------------------------------------------------------
/**
 * 初期化関数セット
 * @param	eoa		EOA_PTR
 * @param	proc	EOA_PROC_INIT
 * @retval	nothing
 */
//--------------------------------------------------------------
void EOA_InitProcSet( EOA_PTR eoa, EOA_PROC_INIT proc )
{
	eoa->proc_init = proc;
}

//--------------------------------------------------------------
/**
 * 初期化関数呼び出し
 * @param	eoa		EOA_PTR
 * @retval	int		TRUE=正常初期化　FALSE=初期化失敗
 */
//--------------------------------------------------------------
int EOA_InitProcCall( EOA_PTR eoa )
{
	void *work = EOA_LocalWorkGet( eoa );
	return( eoa->proc_init(eoa,work) );
}

//--------------------------------------------------------------
/**
 * 動作関数セット
 * @param	eoa		EOA_PTR
 * @param	proc	EOA_PROC_MOVE
 * @retval	nothing
 */
//--------------------------------------------------------------
void EOA_MoveProcSet( EOA_PTR eoa, EOA_PROC_MOVE proc )
{
	eoa->proc_move = proc;
}

//--------------------------------------------------------------
/**
 * 動作関数呼び出し
 * @param	eoa		EOA_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void EOA_MoveProcCall( EOA_PTR eoa )
{
	void *work = EOA_LocalWorkGet( eoa );
	eoa->proc_move( eoa, work );
}

//--------------------------------------------------------------
/**
 * 描画関数セット
 * @param	eoa		EOA_PTR
 * @param	proc	EOA_PROC_MOVE
 * @retval	nothing
 */
//--------------------------------------------------------------
void EOA_DrawProcSet( EOA_PTR eoa, EOA_PROC_DRAW proc )
{
	eoa->proc_draw = proc;
}

//--------------------------------------------------------------
/**
 * 描画関数呼び出し
 * @param	eoa		EOA_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void EOA_DrawProcCall( EOA_PTR eoa )
{
	void *work = EOA_LocalWorkGet( eoa );
	eoa->proc_draw( eoa, work );
}

//--------------------------------------------------------------
/**
 * 削除関数セット
 * @param	eoa		EOA_PTR
 * @param	proc	EOA_PROC_DEL
 * @retval	nothing
 */
//--------------------------------------------------------------
void EOA_DeleteProcSet( EOA_PTR eoa, EOA_PROC_DEL proc )
{
	eoa->proc_del = proc;
}

//--------------------------------------------------------------
/**
 * 削除関数呼び出し
 * @param	eoa		EOA_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void EOA_DeleteProcCall( EOA_PTR eoa )
{
	void *work = EOA_LocalWorkGet( eoa );
	eoa->proc_del( eoa, work );
}

//--------------------------------------------------------------
/**
 * 退避関数セット
 * @param	eoa		EOA_PTR
 * @param	proc	EOA_PROC_PUSH
 * @retval	nothing
 */
//--------------------------------------------------------------
void EOA_PushProcSet( EOA_PTR eoa, EOA_PROC_PUSH proc )
{
	eoa->proc_push = proc;
}

//--------------------------------------------------------------
/**
 * 退避関数呼び出し
 * @param	eoa		EOA_PTR
 * @param	proc	EOA_PROC_PUSH
 * @retval	nothing
 */
//--------------------------------------------------------------
void EOA_PushProcCall( EOA_PTR eoa )
{
	void *work = EOA_LocalWorkGet( eoa );
	eoa->proc_push( eoa, work );
}

//--------------------------------------------------------------
/**
 * 復帰関数セット
 * @param	eoa		EOA_PTR
 * @param	proc	EOA_PROC_POP
 * @retval	nothing
 */
//--------------------------------------------------------------
void EOA_PopProcSet( EOA_PTR eoa, EOA_PROC_POP proc )
{
	eoa->proc_pop = proc;
}

//--------------------------------------------------------------
/**
 * 退避関数呼び出し
 * @param	eoa		EOA_PTR
 * @param	proc	EOA_PROC_POP
 * @retval	nothing
 */
//--------------------------------------------------------------
void EOA_PopProcCall( EOA_PTR eoa )
{
	void *work = EOA_LocalWorkGet( eoa );
	eoa->proc_pop( eoa, work );
}

//--------------------------------------------------------------
/**
 * ローカルワーク取得
 * @param	eoa		EOA_PTR
 * @retval	void*	ワーク*
 */
//--------------------------------------------------------------
void * EOA_LocalWorkGet( EOA_PTR eoa )
{
	return( eoa->work );
}

//--------------------------------------------------------------
/**
 * ローカルワーク初期化
 * @param	eoa		EOA_PTR
 * @param	size	初期化サイズ　EOA_LOCAL_WORK_SIZE以上=ASSERT
 * @retval	nothing
 */
//--------------------------------------------------------------
void EOA_LocalWorkInit( EOA_PTR eoa, int size )
{
	void *work;
	
#ifdef PM_DEBUG
	if( size > EOA_LOCAL_WORK_SIZE ){
		OS_Printf( "EOA ワークサイズオーバー" );
		OS_Printf( "最大サイズ=0x%x, 指定サイズ=0x%x\n", EOA_LOCAL_WORK_SIZE, size );
		GF_ASSERT( 0 );
	}
#endif
	
	work = EOA_LocalWorkGet( eoa );
	memset( work, 0, size );
}

//--------------------------------------------------------------
/**
 * 追加指定パラメタセット
 * @param	eoa		EOA_PTR
 * @param	prm		パラメタ
 * @retval	nothing
 */
//--------------------------------------------------------------
static void eoa_AddParamSet( EOA_PTR eoa, int prm )
{
	eoa->add_param = prm;
}

//--------------------------------------------------------------
/**
 * 追加指定パラメタ取得 
 * @param	eoa		EOA_PTR
 * @retval	int		EOA_Add()時に指定されたパラメタ
 */
//--------------------------------------------------------------
int EOA_AddParamGet( CONST_EOA_PTR eoa )
{
	return( eoa->add_param );
}

//--------------------------------------------------------------
/**
 * 追加指定ポインタセット
 * @param	eoa		EOA_PTR
 * @param	ptr		ポインタ
 * @retval	nothing
 */
//--------------------------------------------------------------
static void eoa_AddPtrSet( EOA_PTR eoa, const void *ptr )
{
	eoa->add_ptr = ptr;
}

//--------------------------------------------------------------
/**
 * 追加指定ポインタ取得
 * @param	eoa		EOA_PTR
 * @retval	void*	EOA_Add()時に指定されたポインタ
 */
//--------------------------------------------------------------
const void * EOA_AddPtrGet( CONST_EOA_PTR eoa )
{
	return( eoa->add_ptr );
}

//--------------------------------------------------------------
/**
 * 回答セット
 * @param	eoa			EOA_PTR
 * @param	answer		答え
 * @retval	nothing
 */
//--------------------------------------------------------------
void EOA_AnswerSet( EOA_PTR eoa, int answer )
{
	eoa->answer = answer;
}

//--------------------------------------------------------------
/**
 * 回答取得
 * @param	eoa			EOA_PTR
 * @retval	int			回答
 */
//--------------------------------------------------------------
int EOA_AnswerGet( CONST_EOA_PTR eoa )
{
	return( eoa->answer );
}

//--------------------------------------------------------------
/**
 * tcbポインタセット
 * @param	eoa			EOA_PTR
 * @param	tcb			TCB_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void eoa_TCBSet( EOA_PTR eoa, TCB_PTR tcb )
{
	eoa->tcb = tcb;
}

//--------------------------------------------------------------
/**
 * tcbポインタ取得
 * @param	eoa			EOA_PTR
 * @retval	tcb			TCB_PTR
 */
//--------------------------------------------------------------
static TCB_PTR eoa_TCBGet( EOA_PTR eoa )
{
	return( eoa->tcb );
}

//--------------------------------------------------------------
/**
 * EOA_SYS_PTRセット
 * @param	eoa		EOA_PTR
 * @param	es		EOA_SYS_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void eoa_EoaSysSet( EOA_PTR eoa, CONST_EOA_SYS_PTR es )
{
	eoa->es = es;
}

//--------------------------------------------------------------
/**
 * EOA_SYS_PTR取得
 * @param	eoa		EOA_PTR
 * @retval	es		EOA_SYS_PTR
 */
//--------------------------------------------------------------
CONST_EOA_SYS_PTR EOA_EoaSysGet( EOA_PTR eoa )
{
	return( eoa->es );
}

//--------------------------------------------------------------
/**
 * X座標セット
 * @param	eoa		EOA_PTR
 * @param	x		座標
 * @retval	nothing
 */
//--------------------------------------------------------------
void EOA_XSet( EOA_PTR eoa, int x )
{
	eoa->x = x;
}

//--------------------------------------------------------------
/**
 * X座標取得
 * @param	eoa		EOA_PTR
 * @retval	int		座標
 */
//--------------------------------------------------------------
int EOA_XGet( EOA_PTR eoa )
{
	return( eoa->x );
}

//--------------------------------------------------------------
/**
 * Y座標セット
 * @param	eoa		EOA_PTR
 * @param	y		座標
 * @retval	nothing
 */
//--------------------------------------------------------------
void EOA_YSet( EOA_PTR eoa, int y )
{
	eoa->y = y;
}

//--------------------------------------------------------------
/**
 * Y座標取得
 * @param	eoa		EOA_PTR
 * @retval	int		座標
 */
//--------------------------------------------------------------
int EOA_YGet( EOA_PTR eoa )
{
	return( eoa->y );
}

//--------------------------------------------------------------
/**
 * Z座標セット
 * @param	eoa		EOA_PTR
 * @param	z		座標
 * @retval	nothing
 */
//--------------------------------------------------------------
void EOA_ZSet( EOA_PTR eoa, int z )
{
	eoa->z = z;
}

//--------------------------------------------------------------
/**
 * Z座標取得
 * @param	eoa		EOA_PTR
 * @retval	int		座標
 */
//--------------------------------------------------------------
int EOA_ZGet( EOA_PTR eoa )
{
	return( eoa->z );
}

//--------------------------------------------------------------
/**
 * マトリクス座標セット
 * @param	eoa		EOA_PTR
 * @param	mtx		セットする座標
 * @retval	nothing
 */
//--------------------------------------------------------------
void EOA_MatrixSet( EOA_PTR eoa, const VecFx32 *mtx )
{
	eoa->matrix = *mtx;
}

//--------------------------------------------------------------
/**
 * マトリクス座標取得
 * @param	eoa		EOA_PTR
 * @param	mtx		セットする座標
 * @retval	nothing
 */
//--------------------------------------------------------------
void EOA_MatrixGet( EOA_PTR eoa, VecFx32 *mtx )
{
	*mtx = eoa->matrix;
}

//==============================================================================
//	ダミー関数
//==============================================================================
//--------------------------------------------------------------
/**
 * 初期化関数　ダミー
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work *
 * @retval	int		TRUE
 */
//--------------------------------------------------------------
int EOA_InitProcDummy( EOA_PTR eoa, void *wk )
{
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * 動作関数　ダミー
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work *
 * @retval	nothing
 */
//--------------------------------------------------------------
void EOA_MoveProcDummy( EOA_PTR eoa, void *wk )
{
}

//--------------------------------------------------------------
/**
 * 描画関数　ダミー
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work *
 * @retval	nothing
 */
//--------------------------------------------------------------
void EOA_DrawProcDummy( EOA_PTR eoa, void *wk )
{
}

//--------------------------------------------------------------
/**
 * 削除関数　ダミー
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work *
 * @retval	nothing
 */
//--------------------------------------------------------------
void EOA_DeleteProcDummy( EOA_PTR eoa, void *wk )
{
}

//--------------------------------------------------------------
/**
 * 退避関数　ダミー
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work *
 * @retval	nothing
 */
//--------------------------------------------------------------
void EOA_PushProcDummy( EOA_PTR eoa, void *wk )
{
}

//--------------------------------------------------------------
/**
 * 復帰関数　ダミー
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work *
 * @retval	nothing
 */
//--------------------------------------------------------------
void EOA_PopProcDummy( EOA_PTR eoa, void *wk )
{
}

