//==============================================================================
/**
 * @file	eoa.h
 * @brief	エフェクトオブジェクトアクター
 * @author	kagaya
 * @data	05.07.13
 */
//==============================================================================
#ifndef EOA_H_FILE
#define EOA_H_FILE

//==============================================================================
//	define
//==============================================================================
#define EOA_LOCAL_WORK_SIZE (128)							///<EOAローカルワークサイズ(byte

//==============================================================================
//	typedef struct
//==============================================================================
//--------------------------------------------------------------
///	EOA_SYS_PTR
//--------------------------------------------------------------
typedef struct _TAG_EOA_SYS * EOA_SYS_PTR;

//--------------------------------------------------------------
///	const EOA_SYS_PTR
//--------------------------------------------------------------
typedef struct _TAG_EOA_SYS const * CONST_EOA_SYS_PTR;

//--------------------------------------------------------------
///	EOA_PTR
//--------------------------------------------------------------
typedef struct _TAG_EOA * EOA_PTR;

//--------------------------------------------------------------
///	const EOA_PTR
//--------------------------------------------------------------
typedef struct _TAG_EOA const * CONST_EOA_PTR;

//--------------------------------------------------------------
//	EOA専用関数型
//--------------------------------------------------------------
typedef int (*EOA_PROC_INIT)( EOA_PTR, void * );			///<初期化関数
typedef void (*EOA_PROC_DEL)( EOA_PTR, void * );			///<削除関数
typedef void (*EOA_PROC_MOVE)( EOA_PTR, void * );			///<動作関数
typedef void (*EOA_PROC_DRAW)( EOA_PTR, void * );			///<描画関数
typedef void (*EOA_PROC_PUSH)( EOA_PTR, void * );			///<退避関数
typedef void (*EOA_PROC_POP)( EOA_PTR, void * );			///<復帰関数

//--------------------------------------------------------------
///	EOA_H構造体
//--------------------------------------------------------------
typedef struct
{
	int work_size;	///<動作で必要とするワークサイズ EOA_LOCAL_WORK_SIZEを超えると強制終了
	EOA_PROC_INIT proc_init;	///<初期化関数　戻り値int TRUE=正常に初期化 FALSE=初期化失敗
	EOA_PROC_DEL  proc_del;		///<削除関数
	EOA_PROC_MOVE proc_move;	///<動作関数
	EOA_PROC_DRAW proc_draw;	///<描画関数
	EOA_PROC_PUSH proc_push;	///<退避関数
	EOA_PROC_POP  proc_pop;		///<復帰関数
}EOA_H;

#define EOA_H_SIZE (sizeof(EOA_H))	///<EOA_Hサイズ

//--------------------------------------------------------------
///	EOA_H_NPP構造体
///	EOA_Hから退避、復帰関数の指定を無くした構造体
//--------------------------------------------------------------
typedef struct
{
	int work_size;	///<動作で必要とするワークサイズ EOA_LOCAL_WORK_SIZEを超えると強制終了
	EOA_PROC_INIT proc_init;	///<初期化関数　戻り値int TRUE=正常に初期化 FALSE=初期化失敗
	EOA_PROC_DEL  proc_del;		///<削除関数
	EOA_PROC_MOVE proc_move;	///<動作関数
	EOA_PROC_DRAW proc_draw;	///<描画関数
}EOA_H_NPP;

#define EOA_H_NPP_SIZE (sizeof(EOA_H_NPP))

//==============================================================================
//	外部参照
//==============================================================================
extern EOA_SYS_PTR EOA_SysInit( int heap_id, int max );
extern void EOA_SysDelete( EOA_SYS_PTR es );

extern EOA_PTR EOA_Add( EOA_SYS_PTR es, const EOA_H *head,
		const VecFx32 *mtx, int prm, const void *ptr, int pri );
extern EOA_PTR EOA_Add_NPP( EOA_SYS_PTR es, const EOA_H_NPP *head,
		const VecFx32 *mtx, int prm, const void *ptr, int pri );

extern void EOA_Delete( EOA_PTR eoa );
extern void EOA_DeleteAll( EOA_SYS_PTR es );
extern void EOA_SysDeleteAll( EOA_SYS_PTR es );

extern void EOA_SysDraw( EOA_SYS_PTR es );

extern int EOA_StatusBit_UseCheck( CONST_EOA_PTR eoa );

extern void EOA_InitProcSet( EOA_PTR eoa, EOA_PROC_INIT proc );
extern int EOA_InitProcCall( EOA_PTR eoa );
extern void EOA_MoveProcSet( EOA_PTR eoa, EOA_PROC_MOVE proc );
extern void EOA_MoveProcCall( EOA_PTR eoa );
extern void EOA_DrawProcSet( EOA_PTR eoa, EOA_PROC_DRAW proc );
extern void EOA_DrawProcCall( EOA_PTR eoa );
extern void EOA_DeleteProcSet( EOA_PTR eoa, EOA_PROC_DEL proc );
extern void EOA_DeleteProcCall( EOA_PTR eoa );
extern void EOA_PushProcSet( EOA_PTR eoa, EOA_PROC_PUSH proc );
extern void EOA_PushProcCall( EOA_PTR eoa );
extern void EOA_PopProcSet( EOA_PTR eoa, EOA_PROC_POP proc );
extern void EOA_PopProcCall( EOA_PTR eoa );

extern void * EOA_LocalWorkGet( EOA_PTR eoa );
extern void EOA_LocalWorkInit( EOA_PTR eoa, int size );

extern int EOA_AddParamGet( CONST_EOA_PTR eoa );
extern const void * EOA_AddPtrGet( CONST_EOA_PTR eoa );
extern void EOA_AnswerSet( EOA_PTR eoa, int answer );
extern int EOA_AnswerGet( CONST_EOA_PTR eoa );
extern CONST_EOA_SYS_PTR EOA_EoaSysGet( EOA_PTR eoa );
extern void EOA_XSet( EOA_PTR eoa, int x );
extern int EOA_XGet( EOA_PTR eoa );
extern void EOA_YSet( EOA_PTR eoa, int y );
extern int EOA_YGet( EOA_PTR eoa );
extern void EOA_ZSet( EOA_PTR eoa, int z );
extern int EOA_ZGet( EOA_PTR eoa );
extern void EOA_MatrixSet( EOA_PTR eoa, const VecFx32 *mtx );
extern void EOA_MatrixGet( EOA_PTR eoa, VecFx32 *mtx );

extern int EOA_InitProcDummy( EOA_PTR eoa, void *wk );
extern void EOA_MoveProcDummy( EOA_PTR eoa, void *wk );
extern void EOA_DrawProcDummy( EOA_PTR eoa, void *wk );
extern void EOA_DeleteProcDummy( EOA_PTR eoa, void *wk );
extern void EOA_PushProcDummy( EOA_PTR eoa, void *wk );
extern void EOA_PopProcDummy( EOA_PTR eoa, void *wk );

#endif //EOA_H_FILE
