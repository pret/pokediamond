//******************************************************************************
/**
 *
 * @file	fieldobj_acmd.c
 * @brief	フィールドOBJアニメーションコマンド
 * @author	kagaya
 * @data	05.08.05
 *
 */
//******************************************************************************
#include "common.h"
#include "fieldsys.h"
#include "fieldobj.h"

#include "..\system/snd_tool.h"

//==============================================================================
//	define
//==============================================================================
//--------------------------------------------------------------
///	整数２桁 小数点2桁 u16
//--------------------------------------------------------------
#define UX16_ONE (0x0100)
#define UX16_NUM(a) ((a)/UX16_ONE)
#define NUM_UX16(a) (UX16_ONE*(a))

//--------------------------------------------------------------
///	アニメーションコマンドリストシーケンス
//--------------------------------------------------------------
enum
{
	SEQNO_AL_ACMD_COUNT_INIT = 0,								///<回数初期化
	SEQNO_AL_ACMD_SET_CHECK,									///<セット可能チェック
	SEQNO_AL_ACMD_SET,											///<セット
	SEQNO_AL_ACMD_END_CHECK,									///<アニメコマンド終了チェック
	SEQNO_AL_ACMD_SET_COUNT,									///<アニメコマンドセットカウント
	SEQNO_AL_END,												///<終了
};

//--------------------------------------------------------------
///	AC_JUMP_WORKで指定する高さ。
///	DATA_AcJumpOffsetTbl[]の要素数に一致
//--------------------------------------------------------------
enum
{
	AC_JUMP_HEIGHT_12 = 0,										///<高さ12
	AC_JUMP_HEIGHT_8,											///<高さ8
	AC_JUMP_HEIGHT_6,											///<高さ6
};

#define AC_JUMP_H_TBL_MAX (16)									///<高さテーブル要素数
#define AC_JUMP_H_TBL_FRAME_MAX (AC_JUMP_H_TBL_MAX-1)			///<高さテーブル要素数
#define AC_JUMP_H_TBL_FRAME_MAX_UX16 (NUM_UX16(AC_JUMP_H_TBL_FRAME_MAX))

//--------------------------------------------------------------
///	AC_JUMP_WORKで指定する上昇速度
//--------------------------------------------------------------
#define AC_JUMP_SPEED_UX16_1 (NUM_UX16(1))							///<速度1
#define	AC_JUMP_SPEED_UX16_2 (NUM_UX16(2))							///<速度2
#define AC_JUMP_SPEED_UX16_4 (NUM_UX16(4))							///<速度4
#define AC_JUMP_SPEED_UX16_TBL(a) (AC_JUMP_H_TBL_FRAME_MAX_UX16/a)

//==============================================================================
//	typedef struct
//==============================================================================
//--------------------------------------------------------------
///	ACMD_LIST_WORK構造体
//--------------------------------------------------------------
typedef struct
{
	int seq_no;													///<処理番号
	int end_flag;												///<終了フラグ
	int acmd_count;												///<アニメ実行回数を記録
	FIELD_OBJ_PTR fldobj;										///<アニメ対象FIELD_OBJ_PTR
	const FIELD_OBJ_ACMD_LIST *list;							///<実行するコマンドリスト
}ACMD_LIST_WORK;

#define ACMD_LIST_WORK_SIZE (sizeof(ACMD_LIST_WORK))			///<ACMD_LIST_WORKサイズ

//--------------------------------------------------------------
///	AC_WALK_WORK構造体。歩き系で共通使用するワーク
//--------------------------------------------------------------
typedef struct
{
	u16 draw_state;												///<描画ステータス
	s16 wait;													///<ウェイト
	int dir;													///<移動方向
	fx32 val;													///<移動量
}AC_WALK_WORK;

#define AC_WALK_WORK_SIZE (sizeof(AC_WALK_WORK))				///<AC_WALK_WORKサイズ

//--------------------------------------------------------------
///	AC_STAY_WALK_WORK構造体。その場歩きで共通使用する
//--------------------------------------------------------------
typedef struct
{
	u16 draw_state;												///<描画ステータス
	s16 wait;													///<ウェイト
}AC_STAY_WALK_WORK;

#define AC_STAY_WALK_WORK_SIZE (sizeof(AC_STAY_WALK_WORK))		///<AC_STAY_WALKサイズ

//--------------------------------------------------------------
///	AC_JUMP_WORK構造体。ジャンプで使用する
//--------------------------------------------------------------
typedef struct
{
	fx32 val;													///<移動量
	fx32 dest_val;												///<移動
	u16 h_speed;
	u16 h_frame;
	s8 dir;														///<移動方向
	s8 wait;													///<ウェイト
	u8 draw_state;												///<描画ステータス
	s8 h_type;													///<高さ
}AC_JUMP_WORK;

#define AC_JUMP_WORK_SIZE (sizeof(AC_JUMP_WORK))				///<AC_JUMP_WORKサイズ

//--------------------------------------------------------------
///	AC_WAIT構造体 待機で使用する
//--------------------------------------------------------------
typedef struct
{
	int wait;
}AC_WAIT_WORK;

#define AC_WAIT_WORK_SIZE (sizeof(AC_WAIT_WORK))				///<AC_WAIT_WORKサイズ

//--------------------------------------------------------------
///	AC_WARP_WORK構造体 上下ワープで使用する
//--------------------------------------------------------------
typedef struct
{
	fx32 total_offset;
	fx32 value;
}AC_WARP_WORK;

#define AC_WARP_WORK_SIZE (sizeof(AC_WARP_WORK))

//--------------------------------------------------------------
///	AC_MARK_WORK構造体 !マーク等で使用する
//--------------------------------------------------------------
typedef struct
{
	int type;
	EOA_PTR eoa_mark;
}AC_MARK_WORK;

#define AC_MARK_WORK_SIZE (sizeof(AC_MARK_WORK))

//--------------------------------------------------------------
///	AC_WALK_ODD_WORK構造体。歩き系で共通使用するワーク
//--------------------------------------------------------------
typedef struct
{
	s16 dir;													///<移動方向
	u16 draw_state;												///<描画ステータス
	s16 max_frame;												///<最大フレーム
	s16 frame;													///<ウェイト
}AC_WALK_ODD_WORK;

#define AC_WALK_ODD_WORK_SIZE (sizeof(AC_WALK_ODD_WORK))
#define AC_WALK_7F_FRAME (7)
#define AC_WALK_6F_FRAME (6)
#define AC_WALK_3F_FRAME (3)

//==============================================================================
//	static
//==============================================================================
static void FldOBJ_AcmdListProcTCB( TCB_PTR tcb, void *wk );
int (* const DATA_AcmdListProcTbl[])( ACMD_LIST_WORK *work );

static int FldOBJ_AcmdAction( FIELD_OBJ_PTR fldobj, int code, int seq );

static int AC_End( FIELD_OBJ_PTR fldobj );

static void AcDirSet( FIELD_OBJ_PTR fldobj, int dir );

static void AcWalkWorkInit( FIELD_OBJ_PTR fldobj, int dir, fx32 val, s16 wait, u16 draw );
static int AC_Walk_1( FIELD_OBJ_PTR fldobj );

static void AcStayWalkWorkInit( FIELD_OBJ_PTR fldobj, int dir, s16 wait, u16 draw );
static int AC_StayWalk_1( FIELD_OBJ_PTR fldobj );

static void AcMarkWorkInit( FIELD_OBJ_PTR fldobj, GYOE_TYPE type );
static int AC_Mark_1( FIELD_OBJ_PTR fldobj );

const fx32 * DATA_AcJumpOffsetTbl[];

static const fx32 DATA_AcWalk7FMoveValueTbl[AC_WALK_7F_FRAME];
static const fx32 DATA_AcWalk6FMoveValueTbl[AC_WALK_6F_FRAME];
static const fx32 DATA_AcWalk3FMoveValueTbl[AC_WALK_3F_FRAME];

//==============================================================================
//	アニメーションコマンド
//==============================================================================
//--------------------------------------------------------------
/**
 * アニメーションコマンドが可能かチェック
 * @param	fldobj		対象となるFIELD_OBJ_PTR 
 * @retval	int			TRUE=可能。FALSE=無理
 */
//--------------------------------------------------------------
int FieldOBJ_AcmdSetCheck( CONST_FIELD_OBJ_PTR fldobj )
{
	if( FieldOBJ_StatusBit_CheckEasy(fldobj,FLDOBJ_STA_BIT_USE) == FALSE ){
		return( FALSE );
	}
	
	if( FieldOBJ_StatusBit_CheckEasy(fldobj,FLDOBJ_STA_BIT_MOVE) == TRUE ){
		return( FALSE );
	}
	
	if( FieldOBJ_StatusBit_CheckEasy(fldobj,FLDOBJ_STA_BIT_ACMD) == TRUE &&
		FieldOBJ_StatusBit_CheckEasy(fldobj,FLDOBJ_STA_BIT_ACMD_END) == FALSE ){
		return( FALSE );
	}
	
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * アニメーションコマンドセット
 * @param	fldobj		対象となるFIELD_OBJ_PTR 
 * @param	code		実行するコード。AC_DIR_U等
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_AcmdSet( FIELD_OBJ_PTR fldobj, int code )
{
	GF_ASSERT( code < ACMD_MAX && "FieldOBJ_AcmdSet() アニメーションコード不正" );
	
	FieldOBJ_AcmdCodeSet( fldobj, code );
	FieldOBJ_AcmdSeqSet( fldobj, 0 );
	FieldOBJ_StatusBit_ON( fldobj, FLDOBJ_STA_BIT_ACMD );
	FieldOBJ_StatusBit_OFF( fldobj, FLDOBJ_STA_BIT_ACMD_END );
}

//--------------------------------------------------------------
/**
 * コマンドセット
 * @param	fldobj		対象となるFIELD_OBJ_PTR 
 * @param	code		実行するコード。AC_DIR_U等
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_CmdSet( FIELD_OBJ_PTR fldobj, int code )
{
	FieldOBJ_AcmdCodeSet( fldobj, code );
	FieldOBJ_AcmdSeqSet( fldobj, 0 );
	FieldOBJ_StatusBit_OFF( fldobj, FLDOBJ_STA_BIT_ACMD_END );
}

//--------------------------------------------------------------
/**
 * アニメーションコマンド終了チェック。
 * @param	fldobj		対象となるFIELD_OBJ_PTR 
 * @retval	int			TRUE=終了
 */
//--------------------------------------------------------------
int FieldOBJ_AcmdEndCheck( CONST_FIELD_OBJ_PTR fldobj )
{
	if( FieldOBJ_StatusBit_CheckEasy(fldobj,FLDOBJ_STA_BIT_ACMD) == FALSE ){
		return( TRUE );
	}
	
	if( FieldOBJ_StatusBit_CheckEasy(fldobj,FLDOBJ_STA_BIT_ACMD_END) == FALSE ){
		return( FALSE );
	}
	
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * アニメーションコマンド終了チェックと開放
 * @param	fldobj		対象となるFIELD_OBJ_PTR 
 * @retval	int			TRUE=終了
 */
//--------------------------------------------------------------
int FieldOBJ_AcmdEnd( FIELD_OBJ_PTR fldobj )
{
	if( FieldOBJ_StatusBit_CheckEasy(fldobj,FLDOBJ_STA_BIT_ACMD) == FALSE ){
		return( TRUE );
	}
	
	if( FieldOBJ_StatusBit_CheckEasy(fldobj,FLDOBJ_STA_BIT_ACMD_END) == FALSE ){
		return( FALSE );
	}
	
	FieldOBJ_StatusBit_OFF( fldobj, FLDOBJ_STA_BIT_ACMD|FLDOBJ_STA_BIT_ACMD_END );
	
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * アニメーションコマンド開放
 * @param	fldobj		対象となるFIELD_OBJ_PTR 
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_AcmdFree( FIELD_OBJ_PTR fldobj )
{
	FieldOBJ_StatusBit_OFF( fldobj, FLDOBJ_STA_BIT_ACMD );
	FieldOBJ_StatusBit_ON( fldobj, FLDOBJ_STA_BIT_ACMD_END );	//ローカルコマンドフラグ
	FieldOBJ_AcmdCodeSet( fldobj, ACMD_NOT );
	FieldOBJ_AcmdSeqSet( fldobj, 0 );
}

//==============================================================================
//	アニメーションコマンドリスト
//==============================================================================
//--------------------------------------------------------------
/**
 * フィールドOBJアニメーションコマンドリストセット
 * @param	fldobj		アニメを行うFIELD_OBJ_PTR
 * @param	list		コマンドがまとめられたFIELD_OBJ_ACMD_LIST *
 * @retval	TCB_PTR		アニメーションコマンドを実行するTCB_PTR
 */
//--------------------------------------------------------------
TCB_PTR FieldOBJ_AcmdListSet( FIELD_OBJ_PTR fldobj, const FIELD_OBJ_ACMD_LIST *list )
{
	TCB_PTR tcb;
	ACMD_LIST_WORK *work;
	
	work = sys_AllocMemoryLo( HEAPID_FIELD, ACMD_LIST_WORK_SIZE );
	GF_ASSERT( work != NULL && "FLDOBJ アニメコマンド用ワーク確保失敗" );
	
	memset( work, 0, ACMD_LIST_WORK_SIZE );
	
	{
		int pri;
		
		pri = FieldOBJSys_TCBStandardPriorityGet( FieldOBJ_FieldOBJSysGet(fldobj) ) - 1;
		tcb = TCB_Add( FldOBJ_AcmdListProcTCB, work, pri );
		GF_ASSERT( tcb != NULL && "FLDOBJ アニメコマンド用TCB追加失敗" );
	}
	
	work->fldobj = fldobj;
	work->list = list;
	
	return( tcb );
}

//--------------------------------------------------------------
/**
 * アニメーションコマンドリスト終了チェック
 * @param	tcb		チェックするアニメをセットしたFieldOBJ_AcmdListSet()の戻り値TCB_PTR
 * @retval	int		TRUE=終了 FALSE=実行中
 */
//--------------------------------------------------------------
int FieldOBJ_AcmdListEndCheck( TCB_PTR tcb )
{
	ACMD_LIST_WORK *work;
	
	work = TCB_GetWork( tcb );
	return( work->end_flag );
}

//--------------------------------------------------------------
/**
 * アニメーションコマンドリスト終了
 * @param	tcb		終了するアニメをセットしたFieldOBJ_AcmdListSet()の戻り値TCB_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_AcmdListEnd( TCB_PTR tcb )
{
	ACMD_LIST_WORK *work;
	
	work = TCB_GetWork( tcb );
	
	GF_ASSERT( FieldOBJ_AcmdEndCheck(work->fldobj) == TRUE &&
			"FLDOBJ アニメコマンド実行中にアニメコマンド終了" );
	
	FieldOBJ_AcmdEnd( work->fldobj );
	
	sys_FreeMemory( HEAPID_FIELD, work );
	TCB_Delete( tcb );
}

//--------------------------------------------------------------
/**
 * アニメーションコマンドリスト処理
 * @param	tcb		TCB_PTR
 * @param	wk		TCB work *
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FldOBJ_AcmdListProcTCB( TCB_PTR tcb, void *wk )
{
	ACMD_LIST_WORK *work;
	
	work = wk;
	
	while( DATA_AcmdListProcTbl[work->seq_no](work) == TRUE ){};
}

//--------------------------------------------------------------
/**
 * リスト処理　回数初期化
 * @param	work	ACMD_LIST_WORK *
 * @retval	int		TRUE=再帰要求
 */
//--------------------------------------------------------------
static int AcmdListProc_Init( ACMD_LIST_WORK *work )
{
	work->acmd_count = 0;
	work->seq_no = SEQNO_AL_ACMD_SET_CHECK;
	
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * リスト処理　コマンドセット可能チェック
 * @param	work	ACMD_LIST_WORK *
 * @retval	int		TRUE=再帰要求
 */
//--------------------------------------------------------------
static int AcmdListProc_AcmdSetCheck( ACMD_LIST_WORK *work )
{
	if( FieldOBJ_AcmdSetCheck(work->fldobj) == FALSE ){
		return( FALSE );
	}
	
	work->seq_no = SEQNO_AL_ACMD_SET;
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * リスト処理　コマンドセット
 * @param	work	ACMD_LIST_WORK *
 * @retval	int		TRUE=再帰要求
 */
//--------------------------------------------------------------
static int AcmdListProc_AcmdSet( ACMD_LIST_WORK *work )
{
	const FIELD_OBJ_ACMD_LIST *list;
		
	list = work->list;
	FieldOBJ_AcmdSet( work->fldobj, list->code );
		
	work->seq_no = SEQNO_AL_ACMD_END_CHECK;
	
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * リスト処理　コマンド終了チェック
 * @param	work	ACMD_LIST_WORK *
 * @retval	int		TRUE=再帰要求
 */
//--------------------------------------------------------------
static int AcmdListProc_AcmdEndCheck( ACMD_LIST_WORK *work )
{
	if( FieldOBJ_AcmdEndCheck(work->fldobj) == FALSE ){
		return( FALSE );
	}
	
	work->seq_no = SEQNO_AL_ACMD_SET_COUNT;
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * リスト処理　コマンドカウント
 * @param	work	ACMD_LIST_WORK *
 * @retval	int		TRUE=再帰要求
 */
//--------------------------------------------------------------
static int AcmdListProc_AcmdSetCount( ACMD_LIST_WORK *work )
{
	const FIELD_OBJ_ACMD_LIST *list;
	
	list = work->list;
	work->acmd_count++;
		
	if( work->acmd_count < list->num ){
		work->seq_no = SEQNO_AL_ACMD_SET_CHECK;
		return( TRUE );
	}
		
	list++;
	work->list = list;
		
	if( list->code != ACMD_END ){
		work->seq_no = SEQNO_AL_ACMD_COUNT_INIT;
		return( TRUE );
	}
		
	work->end_flag = TRUE;
	work->seq_no = SEQNO_AL_END;
	
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * リスト処理　終了
 * @param	work	ACMD_LIST_WORK *
 * @retval	int		TRUE=再帰要求
 */
//--------------------------------------------------------------
static int AcmdListProc_End( ACMD_LIST_WORK *work )
{
	return( FALSE );
}

//--------------------------------------------------------------
///	アニメーションコマンドリスト処理テーブル
//--------------------------------------------------------------
static int (* const DATA_AcmdListProcTbl[])( ACMD_LIST_WORK *work ) =
{
	AcmdListProc_Init,
	AcmdListProc_AcmdSetCheck,
	AcmdListProc_AcmdSet,
	AcmdListProc_AcmdEndCheck,
	AcmdListProc_AcmdSetCount,
	AcmdListProc_End,
};

//==============================================================================
//	アニメーションコマンド　コード取得
//==============================================================================
//--------------------------------------------------------------
/**
 * 方向によるアニメーションコマンドコード変更
 * @param	dir		引数codeを変換する方向。DIR_UP等
 * @param	code	変更したいコード。AC_DIR_U等
 * @retval	int		dir別に変更されたcode　例：dir=DIR_LEFT,code=AC_DIR_U = return(AC_DIR_L)
 */
//--------------------------------------------------------------
int FieldOBJ_AcmdCodeDirChange( int dir, int code )
{
	int i;
	const int * const *tbl;
	const int *dir_tbl;
	
	GF_ASSERT( dir < DIR_4_MAX && "FieldOBJ_AcmdCodeDirChange(未対応方向)" );
	
	tbl = DATA_AcmdCodeDirChangeTbl;
	
	while( (*tbl) != NULL ){
		i = 0;
		dir_tbl = *tbl;
		
		do{
			if( dir_tbl[i] == code ){ return( dir_tbl[dir] ); }
			i++;
		}while( i < DIR_4_MAX );
		
		tbl++;
	}
	
	GF_ASSERT( 0 && "FieldOBJ_AcmdCodeDirChange(未対応コード)" );
	
	return( code );
}

//--------------------------------------------------------------
/**
 * アニメーションコマンドコードによる方向取得
 * @param	code	方向を取得したいコード。AC_DIR_U等
 * @retval	int		codeから得られた方向
 */
//--------------------------------------------------------------
int FieldOBJ_AcmdCodeDirGet( int code )
{
	int dir;
	const int * const *tbl;
	const int *dir_tbl;
	
	tbl = DATA_AcmdCodeDirChangeTbl;
	
	while( (*tbl) != NULL ){
		dir = DIR_UP;
		dir_tbl = *tbl;
		
		do{
			if( dir_tbl[dir] == code ){ return( dir ); }
			dir++;
		}while( dir < DIR_4_MAX );
		
		tbl++;
	}
	
	return( DIR_NOT );
}

//==============================================================================
//	アニメーションコマンド　動作
//==============================================================================
//--------------------------------------------------------------
/**
 * アニメーションコマンドアクション
 * @param	fldobj		FIELD_OBJ_PTR 
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_AcmdAction( FIELD_OBJ_PTR fldobj )
{
	int code,seq;
	
	do{
		code = FieldOBJ_AcmdCodeGet( fldobj );
		
		if( code == ACMD_NOT ){
			break;
		}
		
		seq = FieldOBJ_AcmdSeqGet( fldobj );
	}while( FldOBJ_AcmdAction(fldobj,code,seq) );
}

//--------------------------------------------------------------
/**
 * コマンドアクション。
 * フィールドOBJ内部動作用コマンド動作。
 * AcmdAction()との違いはコマンド終了時に
 * ステータスビット、コマンドワークの初期化がある事と
 * 戻り値で終了判定が返る事。
 * @param	fldobj		FIELD_OBJ_PTR 
 * @retval	int			TRUE=終了
 */
//--------------------------------------------------------------
int FieldOBJ_CmdAction( FIELD_OBJ_PTR fldobj )
{
	FieldOBJ_AcmdAction( fldobj );
	
	if( FieldOBJ_StatusBit_CheckEasy(fldobj,FLDOBJ_STA_BIT_ACMD_END) == FALSE ){
		return( FALSE );
	}
	
	FieldOBJ_StatusBit_OFF( fldobj, FLDOBJ_STA_BIT_ACMD_END );
	FieldOBJ_AcmdCodeSet( fldobj, ACMD_NOT );
	FieldOBJ_AcmdSeqSet( fldobj, 0 );
	
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * アニメーションコマンドアクション
 * @param	fldobj		FIELD_OBJ_PTR 
 * @retval	int			TRUE=再帰
 */
//--------------------------------------------------------------
static int FldOBJ_AcmdAction( FIELD_OBJ_PTR fldobj, int code, int seq )
{
	return( DATA_AcmdActionTbl[code][seq](fldobj) );
}

//==============================================================================
//	アニメーションコマンド　共通パーツ
//==============================================================================
//--------------------------------------------------------------
/**
 * AC系　コマンド終了
 * 常にFLDOBJ_STA_BIT_ACMD_ENDをセット
 * @param	fldobj	FIELD_OBJ_PTR 
 * @retval	int		FALSE
 */
//--------------------------------------------------------------
static int AC_End( FIELD_OBJ_PTR fldobj )
{
	FieldOBJ_StatusBit_ON( fldobj, FLDOBJ_STA_BIT_ACMD_END );
	
	return( FALSE );
}

//==============================================================================
//	アニメーションコマンド AC_DIR_U-AC_DIR_R
//==============================================================================
//--------------------------------------------------------------
/**
 * AC_DIR系共通処理
 * @param	fldobj	FIELD_OBJ_PTR 
 * @param	dir		表示方向。DIR_UP
 * @retval	nothing
 */
//--------------------------------------------------------------
static void AcDirSet( FIELD_OBJ_PTR fldobj, int dir )
{
	FieldOBJ_DirDispCheckSet( fldobj, dir );
	FieldOBJ_DrawStatusSet( fldobj, DRAW_STA_STOP );
	FieldOBJ_GPosUpdate( fldobj );
	FieldOBJ_AcmdSeqInc( fldobj );
}

//--------------------------------------------------------------
/**
 * AC_DIR_U 0
 * @param	fldobj	FIELD_OBJ_PTR 
 * @retval	int		TRUE=再帰
 */
//--------------------------------------------------------------
static int AC_DirU_0( FIELD_OBJ_PTR fldobj )
{
	AcDirSet( fldobj, DIR_UP );
	
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * AC_DIR_D 0
 * @param	fldobj	FIELD_OBJ_PTR 
 * @retval	int		TRUE=再帰
 */
//--------------------------------------------------------------
static int AC_DirD_0( FIELD_OBJ_PTR fldobj )
{
	AcDirSet( fldobj, DIR_DOWN );
	
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * AC_DIR_L 0
 * @param	fldobj	FIELD_OBJ_PTR 
 * @retval	int		TRUE=再帰
 */
//--------------------------------------------------------------
static int AC_DirL_0( FIELD_OBJ_PTR fldobj )
{
	AcDirSet( fldobj, DIR_LEFT );
	
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * AC_DIR_R 0
 * @param	fldobj	FIELD_OBJ_PTR 
 * @retval	int		TRUE=再帰
 */
//--------------------------------------------------------------
static int AC_DirR_0( FIELD_OBJ_PTR fldobj )
{
	AcDirSet( fldobj, DIR_RIGHT );
	
	return( TRUE );
}

//==============================================================================
//	AC_WALK系　共通
//==============================================================================
//--------------------------------------------------------------
/**
 * AC_WALK_WORK初期化
 * @param	fldobj	FIELD_OBJ_PTR 
 * @param	dir		移動方向
 * @param	val		移動量
 * @param	wait	移動フレーム
 * @param	draw	描画ステータス
 * @retval	nothing
 */
//--------------------------------------------------------------
static void AcWalkWorkInit( FIELD_OBJ_PTR fldobj, int dir, fx32 val, s16 wait, u16 draw )
{
	AC_WALK_WORK *work;
	
	work = FieldOBJ_MoveCmdWorkInit( fldobj, AC_WALK_WORK_SIZE );
	work->draw_state = draw;
	work->wait = wait;
	work->dir = dir;
	work->val = val;
	
	FieldOBJ_NowGPosDirAdd( fldobj, dir );
	FieldOBJ_DirMoveDispCheckSet( fldobj, dir );
	FieldOBJ_DrawStatusSet( fldobj, draw );
	FieldOBJ_StatusBit_ON( fldobj, FLDOBJ_STA_BIT_MOVE_START );
	FieldOBJ_AcmdSeqInc( fldobj );
}

//--------------------------------------------------------------
/**
 * AC_WALK系　移動
 * @param	fldobj	FIELD_OBJ_PTR 
 * @retval	int		TRUE=再帰
 */
//--------------------------------------------------------------
static int AC_Walk_1( FIELD_OBJ_PTR fldobj )
{
	AC_WALK_WORK *work;
	
	work = FieldOBJ_MoveCmdWorkGet( fldobj );
	FieldOBJ_VecPosDirAdd( fldobj, work->dir, work->val );
	FieldOBJ_VecPosNowHeightGetSet( fldobj );
	
	work->wait--;
	
	if( work->wait > 0 ){
		return( FALSE );
	}
	
	FieldOBJ_StatusBit_ON( fldobj, FLDOBJ_STA_BIT_MOVE_END|FLDOBJ_STA_BIT_ACMD_END );
	FieldOBJ_GPosUpdate( fldobj );
	FieldOBJ_DrawProcCall( fldobj );						//1フレーム進める
	FieldOBJ_DrawStatusSet( fldobj, DRAW_STA_STOP );
	FieldOBJ_AcmdSeqInc( fldobj );
	
	return( TRUE );
}

//==============================================================================
//	AC_WALK_系
//==============================================================================
//--------------------------------------------------------------
/**
 * AC_WALK_U_32F 0
 * @param	fldobj	FIELD_OBJ_PTR 
 * @retval	int		TRUE=再帰
 */
//--------------------------------------------------------------
static int AC_WalkU32F_0( FIELD_OBJ_PTR fldobj )
{
	AcWalkWorkInit( fldobj, DIR_UP, GRID_VALUE_SPEED_32, GRID_FRAME_32, DRAW_STA_WALK_32F ); 
	
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * AC_WALK_D_32F 0
 * @param	fldobj	FIELD_OBJ_PTR 
 * @retval	int		TRUE=再帰
 */
//--------------------------------------------------------------
static int AC_WalkD32F_0( FIELD_OBJ_PTR fldobj )
{
	AcWalkWorkInit( fldobj, DIR_DOWN, GRID_VALUE_SPEED_32, GRID_FRAME_32, DRAW_STA_WALK_32F ); 
	
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * AC_WALK_L_32F 0
 * @param	fldobj	FIELD_OBJ_PTR 
 * @retval	int		TRUE=再帰
 */
//--------------------------------------------------------------
static int AC_WalkL32F_0( FIELD_OBJ_PTR fldobj )
{
	AcWalkWorkInit( fldobj, DIR_LEFT, GRID_VALUE_SPEED_32, GRID_FRAME_32, DRAW_STA_WALK_32F ); 
	
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * AC_WALK_R_32F 0
 * @param	fldobj	FIELD_OBJ_PTR 
 * @retval	int		TRUE=再帰
 */
//--------------------------------------------------------------
static int AC_WalkR32F_0( FIELD_OBJ_PTR fldobj )
{
	AcWalkWorkInit( fldobj, DIR_RIGHT, GRID_VALUE_SPEED_32, GRID_FRAME_32, DRAW_STA_WALK_32F ); 
	
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * AC_WALK_U_16F 0
 * @param	fldobj	FIELD_OBJ_PTR 
 * @retval	int		TRUE=再帰
 */
//--------------------------------------------------------------
static int AC_WalkU16F_0( FIELD_OBJ_PTR fldobj )
{
	AcWalkWorkInit( fldobj, DIR_UP, GRID_VALUE_SPEED_16, GRID_FRAME_16, DRAW_STA_WALK_16F ); 
	
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * AC_WALK_D_16F 0
 * @param	fldobj	FIELD_OBJ_PTR 
 * @retval	int		TRUE=再帰
 */
//--------------------------------------------------------------
static int AC_WalkD16F_0( FIELD_OBJ_PTR fldobj )
{
	AcWalkWorkInit( fldobj, DIR_DOWN, GRID_VALUE_SPEED_16, GRID_FRAME_16, DRAW_STA_WALK_16F ); 
	
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * AC_WALK_L_16F 0
 * @param	fldobj	FIELD_OBJ_PTR 
 * @retval	int		TRUE=再帰
 */
//--------------------------------------------------------------
static int AC_WalkL16F_0( FIELD_OBJ_PTR fldobj )
{
	AcWalkWorkInit( fldobj, DIR_LEFT, GRID_VALUE_SPEED_16, GRID_FRAME_16, DRAW_STA_WALK_16F ); 
	
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * AC_WALK_R_16F 0
 * @param	fldobj	FIELD_OBJ_PTR 
 * @retval	int		TRUE=再帰
 */
//--------------------------------------------------------------
static int AC_WalkR16F_0( FIELD_OBJ_PTR fldobj )
{
	AcWalkWorkInit( fldobj, DIR_RIGHT, GRID_VALUE_SPEED_16, GRID_FRAME_16, DRAW_STA_WALK_16F ); 
	
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * AC_WALK_U_8F 0
 * @param	fldobj	FIELD_OBJ_PTR 
 * @retval	int		TRUE=再帰
 */
//--------------------------------------------------------------
static int AC_WalkU8F_0( FIELD_OBJ_PTR fldobj )
{
	AcWalkWorkInit( fldobj, DIR_UP, GRID_VALUE_SPEED_8, GRID_FRAME_8, DRAW_STA_WALK_8F ); 
	
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * AC_WALK_D_8F 0
 * @param	fldobj	FIELD_OBJ_PTR 
 * @retval	int		TRUE=再帰
 */
//--------------------------------------------------------------
static int AC_WalkD8F_0( FIELD_OBJ_PTR fldobj )
{
	AcWalkWorkInit( fldobj, DIR_DOWN, GRID_VALUE_SPEED_8, GRID_FRAME_8, DRAW_STA_WALK_8F ); 
	
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * AC_WALK_L_8F 0
 * @param	fldobj	FIELD_OBJ_PTR 
 * @retval	int		TRUE=再帰
 */
//--------------------------------------------------------------
static int AC_WalkL8F_0( FIELD_OBJ_PTR fldobj )
{
	AcWalkWorkInit( fldobj, DIR_LEFT, GRID_VALUE_SPEED_8, GRID_FRAME_8, DRAW_STA_WALK_8F ); 
	
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * AC_WALK_R_8F 0
 * @param	fldobj	FIELD_OBJ_PTR 
 * @retval	int		TRUE=再帰
 */
//--------------------------------------------------------------
static int AC_WalkR8F_0( FIELD_OBJ_PTR fldobj )
{
	AcWalkWorkInit( fldobj, DIR_RIGHT, GRID_VALUE_SPEED_8, GRID_FRAME_8, DRAW_STA_WALK_8F ); 
	
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * AC_WALK_U_4F 0
 * @param	fldobj	FIELD_OBJ_PTR 
 * @retval	int		TRUE=再帰
 */
//--------------------------------------------------------------
static int AC_WalkU4F_0( FIELD_OBJ_PTR fldobj )
{
	AcWalkWorkInit( fldobj, DIR_UP, GRID_VALUE_SPEED_4, GRID_FRAME_4, DRAW_STA_WALK_4F ); 
	
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * AC_WALK_D_4F 0
 * @param	fldobj	FIELD_OBJ_PTR 
 * @retval	int		TRUE=再帰
 */
//--------------------------------------------------------------
static int AC_WalkD4F_0( FIELD_OBJ_PTR fldobj )
{
	AcWalkWorkInit( fldobj, DIR_DOWN, GRID_VALUE_SPEED_4, GRID_FRAME_4, DRAW_STA_WALK_4F ); 
	
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * AC_WALK_L_4F 0
 * @param	fldobj	FIELD_OBJ_PTR 
 * @retval	int		TRUE=再帰
 */
//--------------------------------------------------------------
static int AC_WalkL4F_0( FIELD_OBJ_PTR fldobj )
{
	AcWalkWorkInit( fldobj, DIR_LEFT, GRID_VALUE_SPEED_4, GRID_FRAME_4, DRAW_STA_WALK_4F ); 
	
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * AC_WALK_R_4F 0
 * @param	fldobj	FIELD_OBJ_PTR 
 * @retval	int		TRUE=再帰
 */
//--------------------------------------------------------------
static int AC_WalkR4F_0( FIELD_OBJ_PTR fldobj )
{
	AcWalkWorkInit( fldobj, DIR_RIGHT, GRID_VALUE_SPEED_4, GRID_FRAME_4, DRAW_STA_WALK_4F ); 
	
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * AC_WALK_U_2F 0
 * @param	fldobj	FIELD_OBJ_PTR 
 * @retval	int		TRUE=再帰
 */
//--------------------------------------------------------------
static int AC_WalkU2F_0( FIELD_OBJ_PTR fldobj )
{
	AcWalkWorkInit( fldobj, DIR_UP, GRID_VALUE_SPEED_2, GRID_FRAME_2, DRAW_STA_WALK_2F ); 
	
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * AC_WALK_D_2F 0
 * @param	fldobj	FIELD_OBJ_PTR 
 * @retval	int		TRUE=再帰
 */
//--------------------------------------------------------------
static int AC_WalkD2F_0( FIELD_OBJ_PTR fldobj )
{
	AcWalkWorkInit( fldobj, DIR_DOWN, GRID_VALUE_SPEED_2, GRID_FRAME_2, DRAW_STA_WALK_2F ); 
	
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * AC_WALK_L_2F 0
 * @param	fldobj	FIELD_OBJ_PTR 
 * @retval	int		TRUE=再帰
 */
//--------------------------------------------------------------
static int AC_WalkL2F_0( FIELD_OBJ_PTR fldobj )
{
	AcWalkWorkInit( fldobj, DIR_LEFT, GRID_VALUE_SPEED_2, GRID_FRAME_2, DRAW_STA_WALK_2F ); 
	
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * AC_WALK_R_2F 0
 * @param	fldobj	FIELD_OBJ_PTR 
 * @retval	int		TRUE=再帰
 */
//--------------------------------------------------------------
static int AC_WalkR2F_0( FIELD_OBJ_PTR fldobj )
{
	AcWalkWorkInit( fldobj, DIR_RIGHT, GRID_VALUE_SPEED_2, GRID_FRAME_2, DRAW_STA_WALK_2F ); 
	
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * AC_WALK_U_1F 0
 * @param	fldobj	FIELD_OBJ_PTR 
 * @retval	int		TRUE=再帰
 */
//--------------------------------------------------------------
static int AC_WalkU1F_0( FIELD_OBJ_PTR fldobj )
{
	AcWalkWorkInit( fldobj, DIR_UP, GRID_VALUE_SPEED_1, GRID_FRAME_1, DRAW_STA_STOP ); 
	
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * AC_WALK_D_1F 0
 * @param	fldobj	FIELD_OBJ_PTR 
 * @retval	int		TRUE=再帰
 */
//--------------------------------------------------------------
static int AC_WalkD1F_0( FIELD_OBJ_PTR fldobj )
{
	AcWalkWorkInit( fldobj, DIR_DOWN, GRID_VALUE_SPEED_1, GRID_FRAME_1, DRAW_STA_STOP ); 
	
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * AC_WALK_L_1F 0
 * @param	fldobj	FIELD_OBJ_PTR 
 * @retval	int		TRUE=再帰
 */
//--------------------------------------------------------------
static int AC_WalkL1F_0( FIELD_OBJ_PTR fldobj )
{
	AcWalkWorkInit( fldobj, DIR_LEFT, GRID_VALUE_SPEED_1, GRID_FRAME_1, DRAW_STA_STOP );
	
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * AC_WALK_R_1F 0
 * @param	fldobj	FIELD_OBJ_PTR 
 * @retval	int		TRUE=再帰
 */
//--------------------------------------------------------------
static int AC_WalkR1F_0( FIELD_OBJ_PTR fldobj )
{
	AcWalkWorkInit( fldobj, DIR_RIGHT, GRID_VALUE_SPEED_1, GRID_FRAME_1, DRAW_STA_STOP ); 
	
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * AC_DASH_U_4F 0
 * @param	fldobj	FIELD_OBJ_PTR 
 * @retval	int		TRUE=再帰
 */
//--------------------------------------------------------------
static int AC_DashU4F_0( FIELD_OBJ_PTR fldobj )
{
	AcWalkWorkInit( fldobj, DIR_UP, GRID_VALUE_SPEED_4, GRID_FRAME_4, DRAW_STA_DASH_4F ); 
	
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * AC_DASH_D_4F 0
 * @param	fldobj	FIELD_OBJ_PTR 
 * @retval	int		TRUE=再帰
 */
//--------------------------------------------------------------
static int AC_DashD4F_0( FIELD_OBJ_PTR fldobj )
{
	AcWalkWorkInit( fldobj, DIR_DOWN, GRID_VALUE_SPEED_4, GRID_FRAME_4, DRAW_STA_DASH_4F ); 
	
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * AC_DASH_L_4F 0
 * @param	fldobj	FIELD_OBJ_PTR 
 * @retval	int		TRUE=再帰
 */
//--------------------------------------------------------------
static int AC_DashL4F_0( FIELD_OBJ_PTR fldobj )
{
	AcWalkWorkInit( fldobj, DIR_LEFT, GRID_VALUE_SPEED_4, GRID_FRAME_4, DRAW_STA_DASH_4F ); 
	
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * AC_DASH_R_4F 0
 * @param	fldobj	FIELD_OBJ_PTR 
 * @retval	int		TRUE=再帰
 */
//--------------------------------------------------------------
static int AC_DashR4F_0( FIELD_OBJ_PTR fldobj )
{
	AcWalkWorkInit( fldobj, DIR_RIGHT, GRID_VALUE_SPEED_4, GRID_FRAME_4, DRAW_STA_DASH_4F ); 
	
	return( TRUE );
}

//==============================================================================
//	AC_STAY_WALK系	共通
//==============================================================================
//--------------------------------------------------------------
/**
 * AC_STAY_WALK_WORK初期化
 * @param	fldobj	FIELD_OBJ_PTR 
 * @param	dir		移動方向
 * @param	wait	表示フレーム
 * @param	draw	描画ステータス
 * @retval	nothing
 */
//--------------------------------------------------------------
static void AcStayWalkWorkInit( FIELD_OBJ_PTR fldobj, int dir, s16 wait, u16 draw )
{
	AC_STAY_WALK_WORK *work;
	
	work = FieldOBJ_MoveCmdWorkInit( fldobj, AC_WALK_WORK_SIZE );
	
	work->draw_state = draw;
	work->wait = wait + FRAME_1;	//FRAME_1=動作->アニメへの1フレーム
	
	FieldOBJ_DirDispCheckSet( fldobj, dir );
	FieldOBJ_DrawStatusSet( fldobj, draw );
	FieldOBJ_GPosUpdate( fldobj );
	FieldOBJ_AcmdSeqInc( fldobj );
}

//--------------------------------------------------------------
/**
 * AC_STAY_WALK系　動作
 * @param	fldobj	FIELD_OBJ_PTR 
 * @retval	nothing
 */
//--------------------------------------------------------------
static int AC_StayWalk_1( FIELD_OBJ_PTR fldobj )
{
	AC_STAY_WALK_WORK *work;
	
	work = FieldOBJ_MoveCmdWorkGet( fldobj );
	
	work->wait--;
	
	if( work->wait > 0 ){
		return( FALSE );
	}
	
	FieldOBJ_StatusBit_ON( fldobj, FLDOBJ_STA_BIT_ACMD_END );
	FieldOBJ_DrawStatusSet( fldobj, DRAW_STA_STOP );
	FieldOBJ_AcmdSeqInc( fldobj );
	
	return( TRUE );
}

//==============================================================================
//	AC_STAY_WALK系
//==============================================================================
//--------------------------------------------------------------
/**
 * AC_STAY_WALK_U_32F 0
 * @param	fldobj	FIELD_OBJ_PTR 
 * @retval	int		TRUE=再帰
 */
//--------------------------------------------------------------
static int AC_StayWalkU32F_0( FIELD_OBJ_PTR fldobj )
{
	AcStayWalkWorkInit( fldobj, DIR_UP, GRID_FRAME_32, DRAW_STA_WALK_32F ); 
	
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * AC_STAY_WALK_D_32F 0
 * @param	fldobj	FIELD_OBJ_PTR 
 * @retval	int		TRUE=再帰
 */
//--------------------------------------------------------------
static int AC_StayWalkD32F_0( FIELD_OBJ_PTR fldobj )
{
	AcStayWalkWorkInit( fldobj, DIR_DOWN, GRID_FRAME_32, DRAW_STA_WALK_32F ); 
	
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * AC_STAY_WALK_L_32F 0
 * @param	fldobj	FIELD_OBJ_PTR 
 * @retval	int		TRUE=再帰
 */
//--------------------------------------------------------------
static int AC_StayWalkL32F_0( FIELD_OBJ_PTR fldobj )
{
	AcStayWalkWorkInit( fldobj, DIR_LEFT, GRID_FRAME_32, DRAW_STA_WALK_32F ); 
	
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * AC_STAY_WALK_R_32F 0
 * @param	fldobj	FIELD_OBJ_PTR 
 * @retval	int		TRUE=再帰
 */
//--------------------------------------------------------------
static int AC_StayWalkR32F_0( FIELD_OBJ_PTR fldobj )
{
	AcStayWalkWorkInit( fldobj, DIR_RIGHT, GRID_FRAME_32, DRAW_STA_WALK_32F ); 
	
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * AC_STAY_WALK_U_16F 0
 * @param	fldobj	FIELD_OBJ_PTR 
 * @retval	int		TRUE=再帰
 */
//--------------------------------------------------------------
static int AC_StayWalkU16F_0( FIELD_OBJ_PTR fldobj )
{
	AcStayWalkWorkInit( fldobj, DIR_UP, GRID_FRAME_16, DRAW_STA_WALK_16F ); 
	
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * AC_STAY_WALK_D_16F 0
 * @param	fldobj	FIELD_OBJ_PTR 
 * @retval	int		TRUE=再帰
 */
//--------------------------------------------------------------
static int AC_StayWalkD16F_0( FIELD_OBJ_PTR fldobj )
{
	AcStayWalkWorkInit( fldobj, DIR_DOWN, GRID_FRAME_16, DRAW_STA_WALK_16F ); 
	
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * AC_STAY_WALK_L_16F 0
 * @param	fldobj	FIELD_OBJ_PTR 
 * @retval	int		TRUE=再帰
 */
//--------------------------------------------------------------
static int AC_StayWalkL16F_0( FIELD_OBJ_PTR fldobj )
{
	AcStayWalkWorkInit( fldobj, DIR_LEFT, GRID_FRAME_16, DRAW_STA_WALK_16F ); 
	
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * AC_STAY_WALK_R_16F 0
 * @param	fldobj	FIELD_OBJ_PTR 
 * @retval	int		TRUE=再帰
 */
//--------------------------------------------------------------
static int AC_StayWalkR16F_0( FIELD_OBJ_PTR fldobj )
{
	AcStayWalkWorkInit( fldobj, DIR_RIGHT, GRID_FRAME_16, DRAW_STA_WALK_16F ); 
	
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * AC_STAY_WALK_U_8F 0
 * @param	fldobj	FIELD_OBJ_PTR 
 * @retval	int		TRUE=再帰
 */
//--------------------------------------------------------------
static int AC_StayWalkU8F_0( FIELD_OBJ_PTR fldobj )
{
	AcStayWalkWorkInit( fldobj, DIR_UP, GRID_FRAME_8, DRAW_STA_WALK_8F ); 
	
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * AC_STAY_WALK_D_8F 0
 * @param	fldobj	FIELD_OBJ_PTR 
 * @retval	int		TRUE=再帰
 */
//--------------------------------------------------------------
static int AC_StayWalkD8F_0( FIELD_OBJ_PTR fldobj )
{
	AcStayWalkWorkInit( fldobj, DIR_DOWN, GRID_FRAME_8, DRAW_STA_WALK_8F ); 
	
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * AC_STAY_WALK_L_8F 0
 * @param	fldobj	FIELD_OBJ_PTR 
 * @retval	int		TRUE=再帰
 */
//--------------------------------------------------------------
static int AC_StayWalkL8F_0( FIELD_OBJ_PTR fldobj )
{
	AcStayWalkWorkInit( fldobj, DIR_LEFT, GRID_FRAME_8, DRAW_STA_WALK_8F ); 
	
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * AC_STAY_WALK_R_8F 0
 * @param	fldobj	FIELD_OBJ_PTR 
 * @retval	int		TRUE=再帰
 */
//--------------------------------------------------------------
static int AC_StayWalkR8F_0( FIELD_OBJ_PTR fldobj )
{
	AcStayWalkWorkInit( fldobj, DIR_RIGHT, GRID_FRAME_8, DRAW_STA_WALK_8F ); 
	
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * AC_STAY_WALK_U_4F 0
 * @param	fldobj	FIELD_OBJ_PTR 
 * @retval	int		TRUE=再帰
 */
//--------------------------------------------------------------
static int AC_StayWalkU4F_0( FIELD_OBJ_PTR fldobj )
{
	AcStayWalkWorkInit( fldobj, DIR_UP, GRID_FRAME_4, DRAW_STA_WALK_4F ); 
	
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * AC_STAY_WALK_D_4F 0
 * @param	fldobj	FIELD_OBJ_PTR 
 * @retval	int		TRUE=再帰
 */
//--------------------------------------------------------------
static int AC_StayWalkD4F_0( FIELD_OBJ_PTR fldobj )
{
	AcStayWalkWorkInit( fldobj, DIR_DOWN, GRID_FRAME_4, DRAW_STA_WALK_4F ); 
	
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * AC_STAY_WALK_L_4F 0
 * @param	fldobj	FIELD_OBJ_PTR 
 * @retval	int		TRUE=再帰
 */
//--------------------------------------------------------------
static int AC_StayWalkL4F_0( FIELD_OBJ_PTR fldobj )
{
	AcStayWalkWorkInit( fldobj, DIR_LEFT, GRID_FRAME_4, DRAW_STA_WALK_4F ); 
	
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * AC_STAY_WALK_R_4F 0
 * @param	fldobj	FIELD_OBJ_PTR 
 * @retval	int		TRUE=再帰
 */
//--------------------------------------------------------------
static int AC_StayWalkR4F_0( FIELD_OBJ_PTR fldobj )
{
	AcStayWalkWorkInit( fldobj, DIR_RIGHT, GRID_FRAME_4, DRAW_STA_WALK_4F ); 
	
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * AC_STAY_WALK_U_2F 0
 * @param	fldobj	FIELD_OBJ_PTR 
 * @retval	int		TRUE=再帰
 */
//--------------------------------------------------------------
static int AC_StayWalkU2F_0( FIELD_OBJ_PTR fldobj )
{
	AcStayWalkWorkInit( fldobj, DIR_UP, GRID_FRAME_2, DRAW_STA_WALK_2F ); 
	
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * AC_STAY_WALK_D_2F 0
 * @param	fldobj	FIELD_OBJ_PTR 
 * @retval	int		TRUE=再帰
 */
//--------------------------------------------------------------
static int AC_StayWalkD2F_0( FIELD_OBJ_PTR fldobj )
{
	AcStayWalkWorkInit( fldobj, DIR_DOWN, GRID_FRAME_2, DRAW_STA_WALK_2F ); 
	
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * AC_STAY_WALK_L_2F 0
 * @param	fldobj	FIELD_OBJ_PTR 
 * @retval	int		TRUE=再帰
 */
//--------------------------------------------------------------
static int AC_StayWalkL2F_0( FIELD_OBJ_PTR fldobj )
{
	AcStayWalkWorkInit( fldobj, DIR_LEFT, GRID_FRAME_2, DRAW_STA_WALK_2F ); 
	
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * AC_STAY_WALK_R_2F 0
 * @param	fldobj	FIELD_OBJ_PTR 
 * @retval	int		TRUE=再帰
 */
//--------------------------------------------------------------
static int AC_StayWalkR2F_0( FIELD_OBJ_PTR fldobj )
{
	AcStayWalkWorkInit( fldobj, DIR_RIGHT, GRID_FRAME_2, DRAW_STA_WALK_2F ); 
	
	return( TRUE );
}

//==============================================================================
//	アニメーションコマンド　AC_STAY_JUMP_U系
//==============================================================================
//--------------------------------------------------------------
/**
 * AC_JUMP_WORK初期化
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	dir		移動方向 DIR_UP等
 * @param	val		移動量
 * @param	wait	移動フレーム
 * @param	draw	描画ステータス
 * @param	h_type	高さ。AC_JUMP_HEIGHT_12等
 * @param	h_speed	上昇速度 AC_JUMP_SPEED_1等
 * @retval	nothing
 */
//--------------------------------------------------------------
static void AcJumpWorkInit(
		FIELD_OBJ_PTR fldobj, int dir, fx32 val, s16 wait, u16 draw, s16 h_type, u16 h_speed )
{
	AC_JUMP_WORK *work;
	
	work = FieldOBJ_MoveCmdWorkInit( fldobj, AC_JUMP_WORK_SIZE );
	work->dir = dir;
	work->val = val;
	work->wait = wait;
	work->draw_state = draw;
	work->h_type = h_type;
	work->h_speed = h_speed;
	
	if( val == 0 ){												//その場
		FieldOBJ_GPosUpdate( fldobj );
	}else{
		FieldOBJ_NowGPosDirAdd( fldobj, dir );					//移動
	}
	
	FieldOBJ_StatusBit_ON( fldobj,
			FLDOBJ_STA_BIT_MOVE_START |
			FLDOBJ_STA_BIT_JUMP_START );
	
	FieldOBJ_DirMoveDispCheckSet( fldobj, dir );
	FieldOBJ_DrawStatusSet( fldobj, draw );
	FieldOBJ_AcmdSeqInc( fldobj );
	
	Snd_SePlay( SE_JUMP );
}

//--------------------------------------------------------------
/**
 * AC_JUMP系　移動
 * @param	fldobj	FIELD_OBJ_PTR 
 * @retval	int		TRUE=再帰
 */
//--------------------------------------------------------------
static int AC_Jump_1( FIELD_OBJ_PTR fldobj )
{
	AC_JUMP_WORK *work;
	
	work = FieldOBJ_MoveCmdWorkGet( fldobj );
	
	if( work->val ){
		FieldOBJ_VecPosDirAdd( fldobj, work->dir, work->val );
		FieldOBJ_VecPosNowHeightGetSet( fldobj );
			
		if( work->dest_val >= GRID_FX32 ){						//１グリッド移動
			work->dest_val = 0;
			FieldOBJ_NowGPosDirAdd( fldobj, work->dir );
			FieldOBJ_StatusBit_ON( fldobj, FLDOBJ_STA_BIT_MOVE_START );
		}
			
		{
			fx32 val = work->val;
			if( val < 0 ){ val = -val; }
			work->dest_val += val;
		}
	}
	
	{
		
		work->h_frame += work->h_speed;
		
		if( work->h_frame > AC_JUMP_H_TBL_FRAME_MAX_UX16 ){
			work->h_frame = AC_JUMP_H_TBL_FRAME_MAX_UX16;
		}
		
		{
			VecFx32 vec;
			u16 frame = UX16_NUM( work->h_frame );
			const fx32 *tbl = DATA_AcJumpOffsetTbl[work->h_type];
//			OS_Printf( " JUMP=%x ", work->h_frame );
//			OS_Printf( " SPEED=%x ", work->h_speed );
//			OS_Printf( " FRAME=%x \n", frame );
			vec.x = 0;
			vec.y = tbl[frame];
			vec.z = 0;
			FieldOBJ_VecDrawOffsSet( fldobj, &vec );
		}
	}
	
	work->wait--;
	
	if( work->wait > 0 ){
		return( FALSE );
	}
	
	{
		VecFx32 vec = { 0, 0, 0 };								//オフセットクリア
		FieldOBJ_VecDrawOffsSet( fldobj, &vec );
	}
	
	FieldOBJ_StatusBit_ON( fldobj,
			FLDOBJ_STA_BIT_MOVE_END |
			FLDOBJ_STA_BIT_JUMP_END |
			FLDOBJ_STA_BIT_ACMD_END );
	
	FieldOBJ_GPosUpdate( fldobj );
	FieldOBJ_DrawProcCall( fldobj );						//1フレーム進める
	FieldOBJ_DrawStatusSet( fldobj, DRAW_STA_STOP );
	FieldOBJ_AcmdSeqInc( fldobj );
	
	Snd_SePlay( SE_SUTYA2 );

	return( TRUE );
}

//--------------------------------------------------------------
/**
 * AC_STAY_JUMP_U_16F 0
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	int		TRUE=再帰
 */
//--------------------------------------------------------------
static int AC_StayJumpU16F_0( FIELD_OBJ_PTR fldobj )
{
	AcJumpWorkInit( fldobj, DIR_UP, 0,
		GRID_FRAME_16, DRAW_STA_WALK_16F, AC_JUMP_HEIGHT_12, AC_JUMP_SPEED_UX16_1 );
	
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * AC_STAY_JUMP_D_16F 0
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	int		TRUE=再帰
 */
//--------------------------------------------------------------
static int AC_StayJumpD16F_0( FIELD_OBJ_PTR fldobj )
{
	AcJumpWorkInit( fldobj, DIR_DOWN, 0,
		GRID_FRAME_16, DRAW_STA_WALK_16F, AC_JUMP_HEIGHT_12, AC_JUMP_SPEED_UX16_1 );
	
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * AC_STAY_JUMP_L_16F 0
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	int		TRUE=再帰
 */
//--------------------------------------------------------------
static int AC_StayJumpL16F_0( FIELD_OBJ_PTR fldobj )
{
	AcJumpWorkInit( fldobj, DIR_LEFT, 0,
		GRID_FRAME_16, DRAW_STA_WALK_16F, AC_JUMP_HEIGHT_12, AC_JUMP_SPEED_UX16_1 );
	
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * AC_STAY_JUMP_R_16F 0
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	int		TRUE=再帰
 */
//--------------------------------------------------------------
static int AC_StayJumpR16F_0( FIELD_OBJ_PTR fldobj )
{
	AcJumpWorkInit( fldobj, DIR_RIGHT, 0,
		GRID_FRAME_16, DRAW_STA_WALK_16F, AC_JUMP_HEIGHT_12, AC_JUMP_SPEED_UX16_1 );
	
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * AC_STAY_JUMP_U_8F 0
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	int		TRUE=再帰
 */
//--------------------------------------------------------------
static int AC_StayJumpU8F_0( FIELD_OBJ_PTR fldobj )
{
	AcJumpWorkInit( fldobj, DIR_UP, 0,
		GRID_FRAME_8, DRAW_STA_WALK_8F, AC_JUMP_HEIGHT_12, AC_JUMP_SPEED_UX16_2 );
	
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * AC_STAY_JUMP_D_8F 0
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	int		TRUE=再帰
 */
//--------------------------------------------------------------
static int AC_StayJumpD8F_0( FIELD_OBJ_PTR fldobj )
{
	AcJumpWorkInit( fldobj, DIR_DOWN, 0,
		GRID_FRAME_8, DRAW_STA_WALK_8F, AC_JUMP_HEIGHT_12, AC_JUMP_SPEED_UX16_2 );
	
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * AC_STAY_JUMP_L_8F 0
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	int		TRUE=再帰
 */
//--------------------------------------------------------------
static int AC_StayJumpL8F_0( FIELD_OBJ_PTR fldobj )
{
	AcJumpWorkInit( fldobj, DIR_LEFT, 0,
		GRID_FRAME_8, DRAW_STA_WALK_8F, AC_JUMP_HEIGHT_12, AC_JUMP_SPEED_UX16_2 );
	
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * AC_STAY_JUMP_R_8F 0
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	int		TRUE=再帰
 */
//--------------------------------------------------------------
static int AC_StayJumpR8F_0( FIELD_OBJ_PTR fldobj )
{
	AcJumpWorkInit( fldobj, DIR_RIGHT, 0,
		GRID_FRAME_8, DRAW_STA_WALK_8F, AC_JUMP_HEIGHT_12, AC_JUMP_SPEED_UX16_2 );
	
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * AC_JUMP_U_1G_8F 0
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	int		TRUE=再帰
 */
//--------------------------------------------------------------
static int AC_JumpU1G8F_0( FIELD_OBJ_PTR fldobj )
{
	AcJumpWorkInit( fldobj, DIR_UP, GRID_VALUE_SPEED_8,
		GRID_FRAME_8, DRAW_STA_WALK_8F, AC_JUMP_HEIGHT_12, AC_JUMP_SPEED_UX16_2 );
	
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * AC_JDMP_D_1G_8F 0
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	int		TRUE=再帰
 */
//--------------------------------------------------------------
static int AC_JumpD1G8F_0( FIELD_OBJ_PTR fldobj )
{
	AcJumpWorkInit( fldobj, DIR_DOWN, GRID_VALUE_SPEED_8,
		GRID_FRAME_8, DRAW_STA_WALK_8F, AC_JUMP_HEIGHT_12, AC_JUMP_SPEED_UX16_2 );
	
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * AC_JDMP_L_1G_8F 0
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	int		TRUE=再帰
 */
//--------------------------------------------------------------
static int AC_JumpL1G8F_0( FIELD_OBJ_PTR fldobj )
{
	AcJumpWorkInit( fldobj, DIR_LEFT, GRID_VALUE_SPEED_8,
		GRID_FRAME_8, DRAW_STA_WALK_8F, AC_JUMP_HEIGHT_12, AC_JUMP_SPEED_UX16_2 );
	
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * AC_JDMP_R_1G_8F 0
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	int		TRUE=再帰
 */
//--------------------------------------------------------------
static int AC_JumpR1G8F_0( FIELD_OBJ_PTR fldobj )
{
	AcJumpWorkInit( fldobj, DIR_RIGHT, GRID_VALUE_SPEED_8,
		GRID_FRAME_8, DRAW_STA_WALK_8F, AC_JUMP_HEIGHT_12, AC_JUMP_SPEED_UX16_2 );
	
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * AC_JUMP_U_2G_16F 0
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	int		TRUE=再帰
 */
//--------------------------------------------------------------
static int AC_JumpU2G8F_0( FIELD_OBJ_PTR fldobj )
{
	AcJumpWorkInit( fldobj, DIR_UP, GRID_VALUE_SPEED_8,
		GRID_FRAME_8*2, DRAW_STA_WALK_8F, AC_JUMP_HEIGHT_12, AC_JUMP_SPEED_UX16_1 );
	
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * AC_JUMP_D_2G_16F 0
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	int		TRUE=再帰
 */
//--------------------------------------------------------------
static int AC_JumpD2G8F_0( FIELD_OBJ_PTR fldobj )
{
	AcJumpWorkInit( fldobj, DIR_DOWN, GRID_VALUE_SPEED_8,
		GRID_FRAME_16, DRAW_STA_WALK_8F, AC_JUMP_HEIGHT_12, AC_JUMP_SPEED_UX16_1 );
	
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * AC_JUMP_L_2G_16F 0
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	int		TRUE=再帰
 */
//--------------------------------------------------------------
static int AC_JumpL2G8F_0( FIELD_OBJ_PTR fldobj )
{
	AcJumpWorkInit( fldobj, DIR_LEFT, GRID_VALUE_SPEED_8,
		GRID_FRAME_16, DRAW_STA_WALK_8F, AC_JUMP_HEIGHT_12, AC_JUMP_SPEED_UX16_1 );
	
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * AC_JUMP_R_2G_16F 0
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	int		TRUE=再帰
 */
//--------------------------------------------------------------
static int AC_JumpR2G8F_0( FIELD_OBJ_PTR fldobj )
{
	AcJumpWorkInit( fldobj, DIR_RIGHT, GRID_VALUE_SPEED_8,
		GRID_FRAME_16, DRAW_STA_WALK_8F, AC_JUMP_HEIGHT_12, AC_JUMP_SPEED_UX16_1 );
	
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * AC_JUMPHI_L_1G_16F 0
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	int		TRUE=再帰
 */
//--------------------------------------------------------------
static int AC_JumpHiL1G16F_0( FIELD_OBJ_PTR fldobj )
{
	AcJumpWorkInit( fldobj, DIR_LEFT, GRID_VALUE_SPEED_16,
		GRID_FRAME_16, DRAW_STA_TAKE_OFF_16F, AC_JUMP_HEIGHT_12,
		AC_JUMP_SPEED_UX16_TBL(GRID_FRAME_16) );
	
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * AC_JUMPHI_R_1G_16F 0
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	int		TRUE=再帰
 */
//--------------------------------------------------------------
static int AC_JumpHiR1G16F_0( FIELD_OBJ_PTR fldobj )
{
	AcJumpWorkInit( fldobj, DIR_RIGHT, GRID_VALUE_SPEED_16,
		GRID_FRAME_16, DRAW_STA_TAKE_OFF_16F, AC_JUMP_HEIGHT_12,
		AC_JUMP_SPEED_UX16_TBL(GRID_FRAME_16) );
	
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * AC_JUMPHI_L_3G_32F 0
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	int		TRUE=再帰
 */
//--------------------------------------------------------------
static int AC_JumpHiL3G32F_0( FIELD_OBJ_PTR fldobj )
{
	AcJumpWorkInit( fldobj, DIR_LEFT,
		GRID_VALUE_SPEED_4,
		12, DRAW_STA_TAKE_OFF_8F, AC_JUMP_HEIGHT_12,
		AC_JUMP_SPEED_UX16_TBL(12) );
	
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * AC_JUMPHI_R_3G_32F 0
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	int		TRUE=再帰
 */
//--------------------------------------------------------------
static int AC_JumpHiR3G32F_0( FIELD_OBJ_PTR fldobj )
{
	AcJumpWorkInit( fldobj, DIR_RIGHT,
		GRID_VALUE_SPEED_4,
		12, DRAW_STA_TAKE_OFF_8F, AC_JUMP_HEIGHT_12,
		AC_JUMP_SPEED_UX16_TBL(12) );
	
	return( TRUE );
}

//==============================================================================
//	アニメーションコマンド　AC_WAIT系
//==============================================================================
//--------------------------------------------------------------
/**
 * AC_WAIT_WORK初期化
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	wait	ウェイトフレーム
 * @retval	nothing
 */
//--------------------------------------------------------------
static void AcWaitWorkInit( FIELD_OBJ_PTR fldobj, int wait )
{
	AC_WAIT_WORK *work;
	
	work = FieldOBJ_MoveCmdWorkInit( fldobj, AC_WAIT_WORK_SIZE );
	work->wait = wait;
	
	FieldOBJ_AcmdSeqInc( fldobj );
}

//--------------------------------------------------------------
/**
 * AC_WAIT系　待ち
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	int		TRUE=再帰
 */
//--------------------------------------------------------------
static int AC_Wait_1( FIELD_OBJ_PTR fldobj )
{
	AC_WAIT_WORK *work;
	
	work = FieldOBJ_MoveCmdWorkGet( fldobj );
	
	if( work->wait ){
		work->wait--;
		return( FALSE );
	}
	
	FieldOBJ_AcmdSeqInc( fldobj );
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * AC_WAIT_1F 0
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	int		TRUE=再帰
 */
//--------------------------------------------------------------
static int AC_Wait1F_0( FIELD_OBJ_PTR fldobj )
{
	AcWaitWorkInit( fldobj, 1 );
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * AC_WAIT_2F 0
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	int		TRUE=再帰
 */
//--------------------------------------------------------------
static int AC_Wait2F_0( FIELD_OBJ_PTR fldobj )
{
	AcWaitWorkInit( fldobj, 2 );
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * AC_WAIT_4F 0
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	int		TRUE=再帰
 */
//--------------------------------------------------------------
static int AC_Wait4F_0( FIELD_OBJ_PTR fldobj )
{
	AcWaitWorkInit( fldobj, 4 );
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * AC_WAIT_8F 0
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	int		TRUE=再帰
 */
//--------------------------------------------------------------
static int AC_Wait8F_0( FIELD_OBJ_PTR fldobj )
{
	AcWaitWorkInit( fldobj, 8 );
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * AC_WAIT_15F 0
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	int		TRUE=再帰
 */
//--------------------------------------------------------------
static int AC_Wait15F_0( FIELD_OBJ_PTR fldobj )
{
	AcWaitWorkInit( fldobj, 15 );
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * AC_WAIT_16F 0
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	int		TRUE=再帰
 */
//--------------------------------------------------------------
static int AC_Wait16F_0( FIELD_OBJ_PTR fldobj )
{
	AcWaitWorkInit( fldobj, 16 );
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * AC_WAIT_32F 0
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	int		TRUE=再帰
 */
//--------------------------------------------------------------
static int AC_Wait32F_0( FIELD_OBJ_PTR fldobj )
{
	AcWaitWorkInit( fldobj, 32 );
	return( TRUE );
}

//==============================================================================
//	アニメーションコマンド　AC_WARP_UP DOWN
//==============================================================================
//--------------------------------------------------------------
/**
 * AC_WARP_UP 0
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	int		TRUE=再帰
 */
//--------------------------------------------------------------
static int AC_WarpUp_0( FIELD_OBJ_PTR fldobj )
{
	AC_WARP_WORK *work;
	
	work = FieldOBJ_MoveCmdWorkInit( fldobj, AC_WARP_WORK_SIZE );
	work->value = FX32_ONE * 16;
	
	FieldOBJ_DrawStatusSet( fldobj, DRAW_STA_STOP );
	FieldOBJ_AcmdSeqInc( fldobj );
	
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * AC_WARP_UP 1
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	int		TRUE=再帰
 */
//--------------------------------------------------------------
static int AC_WarpUp_1( FIELD_OBJ_PTR fldobj )
{
	int grid;
	AC_WARP_WORK *work;
	
	work = FieldOBJ_MoveCmdWorkGet( fldobj );
	
	work->total_offset += work->value;
	
	{
		VecFx32 vec = {0,0,0};
		vec.y = work->total_offset;
		FieldOBJ_VecDrawOffsSet( fldobj, &vec );
	}
	
	grid = work->total_offset / GRID_HALF_FX32;
	
	if( grid < 40 ){
		return( FALSE );
	}
	
	FieldOBJ_AcmdSeqInc( fldobj );
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * AC_WARP_DOWN 0
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	int		TRUE=再帰
 */
//--------------------------------------------------------------
static int AC_WarpDown_0( FIELD_OBJ_PTR fldobj )
{
	AC_WARP_WORK *work;
	
	work = FieldOBJ_MoveCmdWorkInit( fldobj, AC_WARP_WORK_SIZE );
	work->total_offset = GRID_HALF_FX32 * 40;
	work->value = -(FX32_ONE * 16);
	
	FieldOBJ_DrawStatusSet( fldobj, DRAW_STA_STOP );
	FieldOBJ_AcmdSeqInc( fldobj );
	
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * AC_WARP_DOWN 1
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	int		TRUE=再帰
 */
//--------------------------------------------------------------
static int AC_WarpDown_1( FIELD_OBJ_PTR fldobj )
{
	AC_WARP_WORK *work;
	
	work = FieldOBJ_MoveCmdWorkGet( fldobj );
	
	work->total_offset += work->value;
	
	if( work->total_offset < 0 ){
		work->total_offset = 0;
	}
	
	{
		VecFx32 vec = {0,0,0};
		vec.y = work->total_offset;
		
		FieldOBJ_VecDrawOffsSet( fldobj, &vec );
	}
	
	if( work->total_offset > 0 ){
		return( FALSE );
	}
	
	
	FieldOBJ_AcmdSeqInc( fldobj );
	return( TRUE );
}

//==============================================================================
//	アニメーションコマンド　AC_VANISH_ON OFF
//==============================================================================
//--------------------------------------------------------------
/**
 * AC_VANISH_ON 0
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	int		TRUE=再帰
 */
//--------------------------------------------------------------
static int AC_VanishON_0( FIELD_OBJ_PTR fldobj )
{
	FieldOBJ_StatusBit_ON( fldobj, FLDOBJ_STA_BIT_VANISH );
	FieldOBJ_AcmdSeqInc( fldobj );
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * AC_VANISH_OFF 0
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	int		TRUE=再帰
 */
//--------------------------------------------------------------
static int AC_VanishOFF_0( FIELD_OBJ_PTR fldobj )
{
	FieldOBJ_StatusBit_OFF( fldobj, FLDOBJ_STA_BIT_VANISH );
	FieldOBJ_AcmdSeqInc( fldobj );
	return( TRUE );
}

//==============================================================================
//	アニメーションコマンド　AC_DIR_PAUSE_ON OFF
//==============================================================================
//--------------------------------------------------------------
/**
 * AC_DIR_PAUSE_ON 0
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	int		TRUE=再帰
 */
//--------------------------------------------------------------
static int AC_DirPauseON_0( FIELD_OBJ_PTR fldobj )
{
	FieldOBJ_StatusBit_ON( fldobj, FLDOBJ_STA_BIT_PAUSE_DIR );
	FieldOBJ_AcmdSeqInc( fldobj );
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * AC_DIR_PAUSE_OFF 0
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	int		TRUE=再帰
 */
//--------------------------------------------------------------
static int AC_DirPauseOFF_0( FIELD_OBJ_PTR fldobj )
{
	FieldOBJ_StatusBit_OFF( fldobj, FLDOBJ_STA_BIT_PAUSE_DIR );
	FieldOBJ_AcmdSeqInc( fldobj );
	return( TRUE );
}

//==============================================================================
//	アニメーションコマンド　AC_ANM_PAUSE_ON OFF
//==============================================================================
//--------------------------------------------------------------
/**
 * AC_ANM_PAUSE_ON 0
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	int		TRUE=再帰
 */
//--------------------------------------------------------------
static int AC_AnmPauseON_0( FIELD_OBJ_PTR fldobj )
{
	FieldOBJ_StatusBit_ON( fldobj, FLDOBJ_STA_BIT_PAUSE_ANM );
	FieldOBJ_AcmdSeqInc( fldobj );
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * AC_ANM_PAUSE_OFF 0
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	int		TRUE=再帰
 */
//--------------------------------------------------------------
static int AC_AnmPauseOFF_0( FIELD_OBJ_PTR fldobj )
{
	FieldOBJ_StatusBit_OFF( fldobj, FLDOBJ_STA_BIT_PAUSE_ANM );
	FieldOBJ_AcmdSeqInc( fldobj );
	return( TRUE );
}

//==============================================================================
//	アニメーションコマンド　マーク
//==============================================================================
//--------------------------------------------------------------
/**
 * AC_MARK_WORK初期化
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	type	マーク種類
 * @retval	nothing
 */
//--------------------------------------------------------------
static void AcMarkWorkInit( FIELD_OBJ_PTR fldobj, GYOE_TYPE type )
{
	AC_MARK_WORK *work;
	
	work = FieldOBJ_MoveCmdWorkInit( fldobj, AC_MARK_WORK_SIZE );
	work->type = type;
	work->eoa_mark = FE_FldOBJGyoe_Add( fldobj, type, TRUE );
	FieldOBJ_AcmdSeqInc( fldobj );
}

//--------------------------------------------------------------
/**
 * AC_MARK系　動作
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	int		TRUE=再帰
 */
//--------------------------------------------------------------
static int AC_Mark_1( FIELD_OBJ_PTR fldobj )
{
	AC_MARK_WORK *work;
	
	work = FieldOBJ_MoveCmdWorkGet( fldobj );
	
	if( FE_Gyoe_EndCheck(work->eoa_mark) == TRUE ){
		EOA_Delete( work->eoa_mark );
		FieldOBJ_AcmdSeqInc( fldobj );
		return( TRUE );
	}
	
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * AC_MARK_GYOE 0
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	int		TRUE=再帰
 */
//--------------------------------------------------------------
static int AC_MarkGyoe_0( FIELD_OBJ_PTR fldobj )
{
	AcMarkWorkInit( fldobj, GYOE_GYOE );
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * AC_MARK_SAISEN 1
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	int		TRUE=再帰
 */
//--------------------------------------------------------------
static int AC_MarkSaisen_0( FIELD_OBJ_PTR fldobj )
{
	AcMarkWorkInit( fldobj, GYOE_SAISEN );
	return( FALSE );
}

//==============================================================================
//	AC_WALK_ODD系
//==============================================================================
//--------------------------------------------------------------
/**
 * AC_WALK_ODD_WORK初期化
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	dir			移動方向
 * @param	max_frame	移動最大フレーム
 * @param	draw		描画ステータス
 * @retval	nothing
 */
//--------------------------------------------------------------
static void AcWalkOddWorkInit( FIELD_OBJ_PTR fldobj, int dir, s16 max_frame, u16 draw )
{
	AC_WALK_ODD_WORK *work;
	
	work = FieldOBJ_MoveCmdWorkInit( fldobj, AC_WALK_ODD_WORK_SIZE );
	work->dir = dir;
	work->draw_state = draw;
	work->max_frame = max_frame;
	
	FieldOBJ_NowGPosDirAdd( fldobj, dir );
	FieldOBJ_DirMoveDispCheckSet( fldobj, dir );
	FieldOBJ_DrawStatusSet( fldobj, draw );
	FieldOBJ_StatusBit_ON( fldobj, FLDOBJ_STA_BIT_MOVE_START );
	FieldOBJ_AcmdSeqInc( fldobj );
}

//--------------------------------------------------------------
/**
 * AC_WALK_ODD_WORK系　移動
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	tbl		移動量が格納されているテーブル
 * @retval	int		TRUE=終了
 */
//--------------------------------------------------------------
static int AC_WalkOdd_Walk( FIELD_OBJ_PTR fldobj, const fx32 *tbl )
{
	AC_WALK_ODD_WORK *work;
	
	work = FieldOBJ_MoveCmdWorkGet( fldobj );
	FieldOBJ_VecPosDirAdd( fldobj, work->dir, tbl[work->frame] );
	FieldOBJ_VecPosNowHeightGetSet( fldobj );
	
	work->frame++;
	
	if( work->frame < work->max_frame ){
		return( FALSE );
	}
	
	FieldOBJ_StatusBit_ON( fldobj, FLDOBJ_STA_BIT_MOVE_END|FLDOBJ_STA_BIT_ACMD_END );
	FieldOBJ_GPosUpdate( fldobj );
	FieldOBJ_DrawProcCall( fldobj );						//1フレーム進める
	FieldOBJ_DrawStatusSet( fldobj, DRAW_STA_STOP );
	FieldOBJ_AcmdSeqInc( fldobj );
	
	return( TRUE );
}

//==============================================================================
//	AC_WALK フレーム奇数系
//==============================================================================
//--------------------------------------------------------------
/**
 * AC_WALK_U_6F 0
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	int		TRUE=再帰
 */
//--------------------------------------------------------------
static int AC_WalkU6F_0( FIELD_OBJ_PTR fldobj )
{
	AcWalkOddWorkInit( fldobj, DIR_UP, AC_WALK_6F_FRAME, DRAW_STA_WALK_6F );
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * AC_WALK_D_6F 0
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	int		TRUE=再帰
 */
//--------------------------------------------------------------
static int AC_WalkD6F_0( FIELD_OBJ_PTR fldobj )
{
	AcWalkOddWorkInit( fldobj, DIR_DOWN, AC_WALK_6F_FRAME, DRAW_STA_WALK_6F );
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * AC_WALK_L_6F 0
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	int		TRUE=再帰
 */
//--------------------------------------------------------------
static int AC_WalkL6F_0( FIELD_OBJ_PTR fldobj )
{
	AcWalkOddWorkInit( fldobj, DIR_LEFT, AC_WALK_6F_FRAME, DRAW_STA_WALK_6F );
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * AC_WALK_R_6F 0
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	int		TRUE=再帰
 */
//--------------------------------------------------------------
static int AC_WalkR6F_0( FIELD_OBJ_PTR fldobj )
{
	AcWalkOddWorkInit( fldobj, DIR_RIGHT, AC_WALK_6F_FRAME, DRAW_STA_WALK_6F );
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * AC_WALK_*_6F 1
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	int		TRUE=再帰
 */
//--------------------------------------------------------------
static int AC_Walk6F_1( FIELD_OBJ_PTR fldobj )
{
	if( AC_WalkOdd_Walk(fldobj,DATA_AcWalk6FMoveValueTbl) == TRUE ){
		return( TRUE );
	}
	
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * AC_WALK_U_3F 0
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	int		TRUE=再帰
 */
//--------------------------------------------------------------
static int AC_WalkU3F_0( FIELD_OBJ_PTR fldobj )
{
	AcWalkOddWorkInit( fldobj, DIR_UP, AC_WALK_3F_FRAME, DRAW_STA_WALK_3F );
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * AC_WALK_D_3F 0
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	int		TRUE=再帰
 */
//--------------------------------------------------------------
static int AC_WalkD3F_0( FIELD_OBJ_PTR fldobj )
{
	AcWalkOddWorkInit( fldobj, DIR_DOWN, AC_WALK_3F_FRAME, DRAW_STA_WALK_3F );
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * AC_WALK_L_3F 0
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	int		TRUE=再帰
 */
//--------------------------------------------------------------
static int AC_WalkL3F_0( FIELD_OBJ_PTR fldobj )
{
	AcWalkOddWorkInit( fldobj, DIR_LEFT, AC_WALK_3F_FRAME, DRAW_STA_WALK_3F );
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * AC_WALK_R_3F 0
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	int		TRUE=再帰
 */
//--------------------------------------------------------------
static int AC_WalkR3F_0( FIELD_OBJ_PTR fldobj )
{
	AcWalkOddWorkInit( fldobj, DIR_RIGHT, AC_WALK_3F_FRAME, DRAW_STA_WALK_3F );
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * AC_WALK_*_3F 1
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	int		TRUE=再帰
 */
//--------------------------------------------------------------
static int AC_Walk3F_1( FIELD_OBJ_PTR fldobj )
{
	if( AC_WalkOdd_Walk(fldobj,DATA_AcWalk3FMoveValueTbl) == TRUE ){
		return( TRUE );
	}
	
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * AC_WALK_U_7F 0
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	int		TRUE=再帰
 */
//--------------------------------------------------------------
static int AC_WalkU7F_0( FIELD_OBJ_PTR fldobj )
{
	AcWalkOddWorkInit( fldobj, DIR_UP, AC_WALK_7F_FRAME, DRAW_STA_WALK_7F );
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * AC_WALK_D_7F 0
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	int		TRUE=再帰
 */
//--------------------------------------------------------------
static int AC_WalkD7F_0( FIELD_OBJ_PTR fldobj )
{
	AcWalkOddWorkInit( fldobj, DIR_DOWN, AC_WALK_7F_FRAME, DRAW_STA_WALK_7F );
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * AC_WALK_L_7F 0
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	int		TRUE=再帰
 */
//--------------------------------------------------------------
static int AC_WalkL7F_0( FIELD_OBJ_PTR fldobj )
{
	AcWalkOddWorkInit( fldobj, DIR_LEFT, AC_WALK_7F_FRAME, DRAW_STA_WALK_7F );
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * AC_WALK_R_7F 0
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	int		TRUE=再帰
 */
//--------------------------------------------------------------
static int AC_WalkR7F_0( FIELD_OBJ_PTR fldobj )
{
	AcWalkOddWorkInit( fldobj, DIR_RIGHT, AC_WALK_7F_FRAME, DRAW_STA_WALK_7F );
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * AC_WALK_*_7F 1
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	int		TRUE=再帰
 */
//--------------------------------------------------------------
static int AC_Walk7F_1( FIELD_OBJ_PTR fldobj )
{
	if( AC_WalkOdd_Walk(fldobj,DATA_AcWalk7FMoveValueTbl) == TRUE ){
		return( TRUE );
	}
	
	return( FALSE );
}

//==============================================================================
//	AC_PC_BOW PCWOMANお辞儀
//==============================================================================
//--------------------------------------------------------------
///	AC_PC_BOW_WORK
//--------------------------------------------------------------
typedef struct
{
	int frame;
}AC_PC_BOW_WORK;

#define AC_PC_BOW_WORK_SIZE (sizeof(AC_PC_BOW_WORK))

//--------------------------------------------------------------
/**
 * AC_PC_BOW	0
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	int		TRUE=再起
 */
//--------------------------------------------------------------
static int AC_PcBow_0( FIELD_OBJ_PTR fldobj )
{
	AC_PC_BOW_WORK *work = FieldOBJ_MoveCmdWorkInit( fldobj, AC_PC_BOW_WORK_SIZE );
	FieldOBJ_DrawStatusSet( fldobj, DRAW_STA_PC_BOW );
	FieldOBJ_AcmdSeqInc( fldobj );
	
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * AC_PC_BOW	1
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	int		TRUE=再起
 */
//--------------------------------------------------------------
static int AC_PcBow_1( FIELD_OBJ_PTR fldobj )
{
	AC_PC_BOW_WORK *work = FieldOBJ_MoveCmdWorkGet( fldobj );
	
	work->frame++;
	
	if( work->frame >= 8 ){
		FieldOBJ_DirDispCheckSet( fldobj, DIR_DOWN );
		FieldOBJ_DrawStatusSet( fldobj, DRAW_STA_STOP );
		FieldOBJ_AcmdSeqInc( fldobj );
	}
	
	return( FALSE );
}

//==============================================================================
//	AC_HIDE_PULLOFF 隠れ蓑脱ぎ
//==============================================================================
//--------------------------------------------------------------
///	AC_HIDE_PULLOFF
//--------------------------------------------------------------
typedef struct
{
	u32 frame;
}AC_HIDE_PULLOFF_WORK;

#define AC_HIDE_PULLOFF_WORK_SIZE (sizeof(AC_HIDE_PULLOFF_WORK))

//--------------------------------------------------------------
/**
 * AC_HIDE_PULLOFF 0
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	int		TRUE=再帰
 */
//--------------------------------------------------------------
static int AC_HidePullOFF_0( FIELD_OBJ_PTR fldobj )
{
	AC_HIDE_PULLOFF_WORK *work = FieldOBJ_MoveCmdWorkInit( fldobj, AC_HIDE_PULLOFF_WORK_SIZE );
	
	{
		EOA_PTR eoa = FieldOBJ_MoveHideEoaPtrGet( fldobj );
		if( eoa != NULL ){ EOA_Delete( eoa ); }
	}
	
	{
		VecFx32 offs = { 0, 0, 0 };
		FieldOBJ_VecDrawOffsSet( fldobj, &offs );
	}
	
	FE_FldOBJHKemuri_Add( fldobj );
	
	FieldOBJ_StatusBit_ON( fldobj, FLDOBJ_STA_BIT_MOVE_START|FLDOBJ_STA_BIT_JUMP_START );
	FieldOBJ_StatusBit_OFF( fldobj, FLDOBJ_STA_BIT_SHADOW_VANISH );
	
	FieldOBJ_AcmdSeqInc( fldobj );
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * AC_HIDE_PULLOFF 1
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	int		TRUE=再帰
 */
//--------------------------------------------------------------
static int AC_HidePullOFF_1( FIELD_OBJ_PTR fldobj )
{
	AC_HIDE_PULLOFF_WORK *work = FieldOBJ_MoveCmdWorkGet( fldobj );
	const fx32 *tbl = DATA_AcJumpOffsetTbl[AC_JUMP_HEIGHT_12];
	VecFx32 offs = { 0, 0, 0 };
	
	offs.y = tbl[work->frame];
	FieldOBJ_VecDrawOffsSet( fldobj, &offs );
	
	work->frame += 2;
 	
	if( work->frame < AC_JUMP_H_TBL_MAX ){
		return( FALSE );
	}
	
	offs.y = 0;
	FieldOBJ_VecDrawOffsSet( fldobj, &offs );
	
	FieldOBJ_StatusBit_ON( fldobj,
			FLDOBJ_STA_BIT_MOVE_END | FLDOBJ_STA_BIT_JUMP_END | FLDOBJ_STA_BIT_ACMD_END );
	
	FieldOBJ_MoveHidePullOffFlagSet( fldobj );
	FieldOBJ_AcmdSeqInc( fldobj );
	return( TRUE );
}

//==============================================================================
//	AC_HERO_BANZAI 自機万歳
//==============================================================================
//--------------------------------------------------------------
///	AC_HERO_BANZAI
//--------------------------------------------------------------
typedef struct
{
	u32 frame;
}AC_HERO_BANZAI_WORK;

#define AC_HERO_BANZAI_WORK_SIZE (sizeof(AC_HERO_BANZAI_WORK))

//--------------------------------------------------------------
/**
 * AC_HERO_BANZAI	0
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	int		TRUE=再起
 */
//--------------------------------------------------------------
static int AC_HeroBanzai_0( FIELD_OBJ_PTR fldobj )
{
	AC_HERO_BANZAI_WORK *work = FieldOBJ_MoveCmdWorkInit( fldobj, AC_HERO_BANZAI_WORK_SIZE );
	FieldOBJ_DrawStatusSet( fldobj, DRAW_STA_BANZAI );
	FieldOBJ_AcmdSeqInc( fldobj );
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * AC_HERO_BANZAI_UKE	0
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	int		TRUE=再起
 */
//--------------------------------------------------------------
static int AC_HeroBanzaiUke_0( FIELD_OBJ_PTR fldobj )
{
	AC_HERO_BANZAI_WORK *work = FieldOBJ_MoveCmdWorkInit( fldobj, AC_HERO_BANZAI_WORK_SIZE );
	FieldOBJ_DrawStatusSet( fldobj, DRAW_STA_BANZAI_UKE );
	FieldOBJ_AcmdSeqInc( fldobj );
	
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * AC_HERO_BANZAI 1
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	int		TRUE=再帰
 */
//--------------------------------------------------------------
static int AC_HeroBanzai_1( FIELD_OBJ_PTR fldobj )
{
	AC_HERO_BANZAI_WORK *work = FieldOBJ_MoveCmdWorkGet( fldobj );
	
	work->frame++;
 	
	if( work->frame < (21) ){
		return( FALSE );
	}
	
//	FieldOBJ_DrawStatusSet( fldobj, DRAW_STA_BANZAI_STOP );
	FieldOBJ_AcmdSeqInc( fldobj );
	return( TRUE );
}

//==============================================================================
//	data	アニメーションコマンドテーブル
//==============================================================================
//--------------------------------------------------------------
///	AC_DIR_U
//--------------------------------------------------------------
int (* const DATA_AC_DirU_Tbl[])( FIELD_OBJ_PTR  ) =
{
	AC_DirU_0,
	AC_End,
};

//--------------------------------------------------------------
///	AC_DIR_D
//--------------------------------------------------------------
int (* const DATA_AC_DirD_Tbl[])( FIELD_OBJ_PTR  ) =
{
	AC_DirD_0,
	AC_End,
};

//--------------------------------------------------------------
///	AC_DIR_L
//--------------------------------------------------------------
int (* const DATA_AC_DirL_Tbl[])( FIELD_OBJ_PTR  ) =
{
	AC_DirL_0,
	AC_End,
};

//--------------------------------------------------------------
///	AC_DIR_R
//--------------------------------------------------------------
int (* const DATA_AC_DirR_Tbl[])( FIELD_OBJ_PTR  ) =
{
	AC_DirR_0,
	AC_End,
};

//--------------------------------------------------------------
///	AC_WALK_U_32F
//--------------------------------------------------------------
int (* const DATA_AC_WalkU_32F_Tbl[])( FIELD_OBJ_PTR  ) =
{
	AC_WalkU32F_0,
	AC_Walk_1,
	AC_End,
};

//--------------------------------------------------------------
///	AC_WALK_D_32F
//--------------------------------------------------------------
int (* const DATA_AC_WalkD_32F_Tbl[])( FIELD_OBJ_PTR  ) =
{
	AC_WalkD32F_0,
	AC_Walk_1,
	AC_End,
};

//--------------------------------------------------------------
///	AC_WALK_L_32F
//--------------------------------------------------------------
int (* const DATA_AC_WalkL_32F_Tbl[])( FIELD_OBJ_PTR  ) =
{
	AC_WalkL32F_0,
	AC_Walk_1,
	AC_End,
};

//--------------------------------------------------------------
///	AC_WALK_R_32F
//--------------------------------------------------------------
int (* const DATA_AC_WalkR_32F_Tbl[])( FIELD_OBJ_PTR  ) =
{
	AC_WalkR32F_0,
	AC_Walk_1,
	AC_End,
};

//--------------------------------------------------------------
///	AC_WALK_U_16F
//--------------------------------------------------------------
int (* const DATA_AC_WalkU_16F_Tbl[])( FIELD_OBJ_PTR  ) =
{
	AC_WalkU16F_0,
	AC_Walk_1,
	AC_End,
};

//--------------------------------------------------------------
///	AC_WALK_D_16F
//--------------------------------------------------------------
int (* const DATA_AC_WalkD_16F_Tbl[])( FIELD_OBJ_PTR  ) =
{
	AC_WalkD16F_0,
	AC_Walk_1,
	AC_End,
};

//--------------------------------------------------------------
///	AC_WALK_L_16F
//--------------------------------------------------------------
int (* const DATA_AC_WalkL_16F_Tbl[])( FIELD_OBJ_PTR  ) =
{
	AC_WalkL16F_0,
	AC_Walk_1,
	AC_End,
};

//--------------------------------------------------------------
///	AC_WALK_R_16F
//--------------------------------------------------------------
int (* const DATA_AC_WalkR_16F_Tbl[])( FIELD_OBJ_PTR  ) =
{
	AC_WalkR16F_0,
	AC_Walk_1,
	AC_End,
};

//--------------------------------------------------------------
///	AC_WALK_U_8F
//--------------------------------------------------------------
int (* const DATA_AC_WalkU_8F_Tbl[])( FIELD_OBJ_PTR  ) =
{
	AC_WalkU8F_0,
	AC_Walk_1,
	AC_End,
};

//--------------------------------------------------------------
///	AC_WALK_D_8F
//--------------------------------------------------------------
int (* const DATA_AC_WalkD_8F_Tbl[])( FIELD_OBJ_PTR  ) =
{
	AC_WalkD8F_0,
	AC_Walk_1,
	AC_End,
};

//--------------------------------------------------------------
///	AC_WALK_L_8F
//--------------------------------------------------------------
int (* const DATA_AC_WalkL_8F_Tbl[])( FIELD_OBJ_PTR  ) =
{
	AC_WalkL8F_0,
	AC_Walk_1,
	AC_End,
};

//--------------------------------------------------------------
///	AC_WALK_R_8F
//--------------------------------------------------------------
int (* const DATA_AC_WalkR_8F_Tbl[])( FIELD_OBJ_PTR  ) =
{
	AC_WalkR8F_0,
	AC_Walk_1,
	AC_End,
};

//--------------------------------------------------------------
///	AC_WALK_U_4F
//--------------------------------------------------------------
int (* const DATA_AC_WalkU_4F_Tbl[])( FIELD_OBJ_PTR  ) =
{
	AC_WalkU4F_0,
	AC_Walk_1,
	AC_End,
};

//--------------------------------------------------------------
///	AC_WALK_D_4F
//--------------------------------------------------------------
int (* const DATA_AC_WalkD_4F_Tbl[])( FIELD_OBJ_PTR  ) =
{
	AC_WalkD4F_0,
	AC_Walk_1,
	AC_End,
};

//--------------------------------------------------------------
///	AC_WALK_L_4F
//--------------------------------------------------------------
int (* const DATA_AC_WalkL_4F_Tbl[])( FIELD_OBJ_PTR  ) =
{
	AC_WalkL4F_0,
	AC_Walk_1,
	AC_End,
};

//--------------------------------------------------------------
///	AC_WALK_R_4F
//--------------------------------------------------------------
int (* const DATA_AC_WalkR_4F_Tbl[])( FIELD_OBJ_PTR  ) =
{
	AC_WalkR4F_0,
	AC_Walk_1,
	AC_End,
};

//--------------------------------------------------------------
///	AC_WALK_U_2F
//--------------------------------------------------------------
int (* const DATA_AC_WalkU_2F_Tbl[])( FIELD_OBJ_PTR  ) =
{
	AC_WalkU2F_0,
	AC_Walk_1,
	AC_End,
};

//--------------------------------------------------------------
///	AC_WALK_D_2F
//--------------------------------------------------------------
int (* const DATA_AC_WalkD_2F_Tbl[])( FIELD_OBJ_PTR  ) =
{
	AC_WalkD2F_0,
	AC_Walk_1,
	AC_End,
};

//--------------------------------------------------------------
///	AC_WALK_L_2F
//--------------------------------------------------------------
int (* const DATA_AC_WalkL_2F_Tbl[])( FIELD_OBJ_PTR  ) =
{
	AC_WalkL2F_0,
	AC_Walk_1,
	AC_End,
};

//--------------------------------------------------------------
///	AC_WALK_R_2F
//--------------------------------------------------------------
int (* const DATA_AC_WalkR_2F_Tbl[])( FIELD_OBJ_PTR  ) =
{
	AC_WalkR2F_0,
	AC_Walk_1,
	AC_End,
};

//--------------------------------------------------------------
///	AC_WALK_U_1F
//--------------------------------------------------------------
int (* const DATA_AC_WalkU_1F_Tbl[])( FIELD_OBJ_PTR  ) =
{
	AC_WalkU1F_0,
	AC_Walk_1,
	AC_End,
};

//--------------------------------------------------------------
///	AC_WALK_D_1F
//--------------------------------------------------------------
int (* const DATA_AC_WalkD_1F_Tbl[])( FIELD_OBJ_PTR  ) =
{
	AC_WalkD1F_0,
	AC_Walk_1,
	AC_End,
};

//--------------------------------------------------------------
///	AC_WALK_L_1F
//--------------------------------------------------------------
int (* const DATA_AC_WalkL_1F_Tbl[])( FIELD_OBJ_PTR  ) =
{
	AC_WalkL1F_0,
	AC_Walk_1,
	AC_End,
};

//--------------------------------------------------------------
///	AC_WALK_R_1F
//--------------------------------------------------------------
int (* const DATA_AC_WalkR_1F_Tbl[])( FIELD_OBJ_PTR  ) =
{
	AC_WalkR1F_0,
	AC_Walk_1,
	AC_End,
};

//--------------------------------------------------------------
///	AC_STAY_WALK_U_32F
//--------------------------------------------------------------
int (* const DATA_AC_StayWalkU_32F_Tbl[])( FIELD_OBJ_PTR  ) =
{
	AC_StayWalkU32F_0,
	AC_StayWalk_1,
	AC_End,
};

//--------------------------------------------------------------
///	AC_STAY_WALK_D_32F
//--------------------------------------------------------------
int (* const DATA_AC_StayWalkD_32F_Tbl[])( FIELD_OBJ_PTR  ) =
{
	AC_StayWalkD32F_0,
	AC_StayWalk_1,
	AC_End,
};

//--------------------------------------------------------------
///	AC_STAY_WALK_L_32F
//--------------------------------------------------------------
int (* const DATA_AC_StayWalkL_32F_Tbl[])( FIELD_OBJ_PTR  ) =
{
	AC_StayWalkL32F_0,
	AC_StayWalk_1,
	AC_End,
};

//--------------------------------------------------------------
///	AC_STAY_WALK_R_32F
//--------------------------------------------------------------
int (* const DATA_AC_StayWalkR_32F_Tbl[])( FIELD_OBJ_PTR  ) =
{
	AC_StayWalkR32F_0,
	AC_StayWalk_1,
	AC_End,
};

//--------------------------------------------------------------
///	AC_STAY_WALK_U_16F
//--------------------------------------------------------------
int (* const DATA_AC_StayWalkU_16F_Tbl[])( FIELD_OBJ_PTR  ) =
{
	AC_StayWalkU16F_0,
	AC_StayWalk_1,
	AC_End,
};

//--------------------------------------------------------------
///	AC_STAY_WALK_D_16F
//--------------------------------------------------------------
int (* const DATA_AC_StayWalkD_16F_Tbl[])( FIELD_OBJ_PTR  ) =
{
	AC_StayWalkD16F_0,
	AC_StayWalk_1,
	AC_End,
};

//--------------------------------------------------------------
///	AC_STAY_WALK_L_16F
//--------------------------------------------------------------
int (* const DATA_AC_StayWalkL_16F_Tbl[])( FIELD_OBJ_PTR  ) =
{
	AC_StayWalkL16F_0,
	AC_StayWalk_1,
	AC_End,
};

//--------------------------------------------------------------
///	AC_STAY_WALK_R_16F
//--------------------------------------------------------------
int (* const DATA_AC_StayWalkR_16F_Tbl[])( FIELD_OBJ_PTR  ) =
{
	AC_StayWalkR16F_0,
	AC_StayWalk_1,
	AC_End,
};

//--------------------------------------------------------------
///	AC_STAY_WALK_U_8F
//--------------------------------------------------------------
int (* const DATA_AC_StayWalkU_8F_Tbl[])( FIELD_OBJ_PTR  ) =
{
	AC_StayWalkU8F_0,
	AC_StayWalk_1,
	AC_End,
};

//--------------------------------------------------------------
///	AC_STAY_WALK_D_8F
//--------------------------------------------------------------
int (* const DATA_AC_StayWalkD_8F_Tbl[])( FIELD_OBJ_PTR  ) =
{
	AC_StayWalkD8F_0,
	AC_StayWalk_1,
	AC_End,
};

//--------------------------------------------------------------
///	AC_STAY_WALK_L_8F
//--------------------------------------------------------------
int (* const DATA_AC_StayWalkL_8F_Tbl[])( FIELD_OBJ_PTR  ) =
{
	AC_StayWalkL8F_0,
	AC_StayWalk_1,
	AC_End,
};

//--------------------------------------------------------------
///	AC_STAY_WALK_R_8F
//--------------------------------------------------------------
int (* const DATA_AC_StayWalkR_8F_Tbl[])( FIELD_OBJ_PTR  ) =
{
	AC_StayWalkR8F_0,
	AC_StayWalk_1,
	AC_End,
};

//--------------------------------------------------------------
///	AC_STAY_WALK_U_4F
//--------------------------------------------------------------
int (* const DATA_AC_StayWalkU_4F_Tbl[])( FIELD_OBJ_PTR  ) =
{
	AC_StayWalkU4F_0,
	AC_StayWalk_1,
	AC_End,
};

//--------------------------------------------------------------
///	AC_STAY_WALK_D_4F
//--------------------------------------------------------------
int (* const DATA_AC_StayWalkD_4F_Tbl[])( FIELD_OBJ_PTR  ) =
{
	AC_StayWalkD4F_0,
	AC_StayWalk_1,
	AC_End,
};

//--------------------------------------------------------------
///	AC_STAY_WALK_L_4F
//--------------------------------------------------------------
int (* const DATA_AC_StayWalkL_4F_Tbl[])( FIELD_OBJ_PTR  ) =
{
	AC_StayWalkL4F_0,
	AC_StayWalk_1,
	AC_End,
};

//--------------------------------------------------------------
///	AC_STAY_WALK_R_4F
//--------------------------------------------------------------
int (* const DATA_AC_StayWalkR_4F_Tbl[])( FIELD_OBJ_PTR  ) =
{
	AC_StayWalkR4F_0,
	AC_StayWalk_1,
	AC_End,
};

//--------------------------------------------------------------
///	AC_STAY_WALK_U_2F
//--------------------------------------------------------------
int (* const DATA_AC_StayWalkU_2F_Tbl[])( FIELD_OBJ_PTR  ) =
{
	AC_StayWalkU2F_0,
	AC_StayWalk_1,
	AC_End,
};

//--------------------------------------------------------------
///	AC_STAY_WALK_D_2F
//--------------------------------------------------------------
int (* const DATA_AC_StayWalkD_2F_Tbl[])( FIELD_OBJ_PTR  ) =
{
	AC_StayWalkD2F_0,
	AC_StayWalk_1,
	AC_End,
};

//--------------------------------------------------------------
///	AC_STAY_WALK_L_2F
//--------------------------------------------------------------
int (* const DATA_AC_StayWalkL_2F_Tbl[])( FIELD_OBJ_PTR  ) =
{
	AC_StayWalkL2F_0,
	AC_StayWalk_1,
	AC_End,
};

//--------------------------------------------------------------
///	AC_STAY_WALK_R_2F
//--------------------------------------------------------------
int (* const DATA_AC_StayWalkR_2F_Tbl[])( FIELD_OBJ_PTR  ) =
{
	AC_StayWalkR2F_0,
	AC_StayWalk_1,
	AC_End,
};

//--------------------------------------------------------------
///	AC_STAY_JUMP_U_16F
//--------------------------------------------------------------
int (* const DATA_AC_StayJumpU_16F_Tbl[])( FIELD_OBJ_PTR  ) =
{
	AC_StayJumpU16F_0,
	AC_Jump_1,
	AC_End,
};

//--------------------------------------------------------------
///	AC_STAY_JUMP_D_16F
//--------------------------------------------------------------
int (* const DATA_AC_StayJumpD_16F_Tbl[])( FIELD_OBJ_PTR  ) =
{
	AC_StayJumpD16F_0,
	AC_Jump_1,
	AC_End,
};

//--------------------------------------------------------------
///	AC_STAY_JUMP_L_16F
//--------------------------------------------------------------
int (* const DATA_AC_StayJumpL_16F_Tbl[])( FIELD_OBJ_PTR  ) =
{
	AC_StayJumpL16F_0,
	AC_Jump_1,
	AC_End,
};

//--------------------------------------------------------------
///	AC_STAY_JUMP_R_16F
//--------------------------------------------------------------
int (* const DATA_AC_StayJumpR_16F_Tbl[])( FIELD_OBJ_PTR  ) =
{
	AC_StayJumpR16F_0,
	AC_Jump_1,
	AC_End,
};

//--------------------------------------------------------------
///	AC_STAY_JUMP_U_8F
//--------------------------------------------------------------
int (* const DATA_AC_StayJumpU_8F_Tbl[])( FIELD_OBJ_PTR  ) =
{
	AC_StayJumpU8F_0,
	AC_Jump_1,
	AC_End,
};

//--------------------------------------------------------------
///	AC_STAY_JUMP_D_8F
//--------------------------------------------------------------
int (* const DATA_AC_StayJumpD_8F_Tbl[])( FIELD_OBJ_PTR  ) =
{
	AC_StayJumpD8F_0,
	AC_Jump_1,
	AC_End,
};

//--------------------------------------------------------------
///	AC_STAY_JUMP_L_8F
//--------------------------------------------------------------
int (* const DATA_AC_StayJumpL_8F_Tbl[])( FIELD_OBJ_PTR  ) =
{
	AC_StayJumpL8F_0,
	AC_Jump_1,
	AC_End,
};

//--------------------------------------------------------------
///	AC_STAY_JUMP_R_8F
//--------------------------------------------------------------
int (* const DATA_AC_StayJumpR_8F_Tbl[])( FIELD_OBJ_PTR  ) =
{
	AC_StayJumpR8F_0,
	AC_Jump_1,
	AC_End,
};

//--------------------------------------------------------------
///	AC_JUMP_U_1G_8F
//--------------------------------------------------------------
int (* const DATA_AC_JumpU_1G_8F_Tbl[])( FIELD_OBJ_PTR  ) =
{
	AC_JumpU1G8F_0,
	AC_Jump_1,
	AC_End,
};

//--------------------------------------------------------------
///	AC_JUMP_D_1G_8F
//--------------------------------------------------------------
int (* const DATA_AC_JumpD_1G_8F_Tbl[])( FIELD_OBJ_PTR  ) =
{
	AC_JumpD1G8F_0,
	AC_Jump_1,
	AC_End,
};

//--------------------------------------------------------------
///	AC_JUMP_L_1G_8F
//--------------------------------------------------------------
int (* const DATA_AC_JumpL_1G_8F_Tbl[])( FIELD_OBJ_PTR  ) =
{
	AC_JumpL1G8F_0,
	AC_Jump_1,
	AC_End,
};

//--------------------------------------------------------------
///	AC_JUMP_R_1G_8F
//--------------------------------------------------------------
int (* const DATA_AC_JumpR_1G_8F_Tbl[])( FIELD_OBJ_PTR  ) =
{
	AC_JumpR1G8F_0,
	AC_Jump_1,
	AC_End,
};

//--------------------------------------------------------------
///	AC_JUMP_U_2G_16F
//--------------------------------------------------------------
int (* const DATA_AC_JumpU_2G_16F_Tbl[])( FIELD_OBJ_PTR  ) =
{
	AC_JumpU2G8F_0,
	AC_Jump_1,
	AC_End,
};

//--------------------------------------------------------------
///	AC_JUMP_D_2G_16F
//--------------------------------------------------------------
int (* const DATA_AC_JumpD_2G_16F_Tbl[])( FIELD_OBJ_PTR  ) =
{
	AC_JumpD2G8F_0,
	AC_Jump_1,
	AC_End,
};

//--------------------------------------------------------------
///	AC_JUMP_L_2G_16F
//--------------------------------------------------------------
int (* const DATA_AC_JumpL_2G_16F_Tbl[])( FIELD_OBJ_PTR  ) =
{
	AC_JumpL2G8F_0,
	AC_Jump_1,
	AC_End,
};

//--------------------------------------------------------------
///	AC_JUMP_R_2G_16F
//--------------------------------------------------------------
int (* const DATA_AC_JumpR_2G_16F_Tbl[])( FIELD_OBJ_PTR  ) =
{
	AC_JumpR2G8F_0,
	AC_Jump_1,
	AC_End,
};

//--------------------------------------------------------------
///	AC_JUMPHI_L_1G_16F
//--------------------------------------------------------------
int (* const DATA_AC_JumpHiL_1G_16F_Tbl[])( FIELD_OBJ_PTR  ) =
{
	AC_JumpHiL1G16F_0,
	AC_Jump_1,
	AC_End,
};

//--------------------------------------------------------------
///	AC_JUMPHI_R_1G_16F
//--------------------------------------------------------------
int (* const DATA_AC_JumpHiR_1G_16F_Tbl[])( FIELD_OBJ_PTR  ) =
{
	AC_JumpHiR1G16F_0,
	AC_Jump_1,
	AC_End,
};

//--------------------------------------------------------------
///	AC_JUMPHI_L_3G_32F
//--------------------------------------------------------------
int (* const DATA_AC_JumpHiL_3G_32F_Tbl[])( FIELD_OBJ_PTR  ) =
{
	AC_JumpHiL3G32F_0,
	AC_Jump_1,
	AC_End,
};

//--------------------------------------------------------------
///	AC_JUMPHI_R_3G_32F
//--------------------------------------------------------------
int (* const DATA_AC_JumpHiR_3G_32F_Tbl[])( FIELD_OBJ_PTR  ) =
{
	AC_JumpHiR3G32F_0,
	AC_Jump_1,
	AC_End,
};

//--------------------------------------------------------------
///	AC_WAIT_1F
//--------------------------------------------------------------
int (* const DATA_AC_Wait_1F_Tbl[])( FIELD_OBJ_PTR  ) =
{
	AC_Wait1F_0,
	AC_Wait_1,
	AC_End,
};

//--------------------------------------------------------------
///	AC_WAIT_2F
//--------------------------------------------------------------
int (* const DATA_AC_Wait_2F_Tbl[])( FIELD_OBJ_PTR  ) =
{
	AC_Wait2F_0,
	AC_Wait_1,
	AC_End,
};

//--------------------------------------------------------------
///	AC_WAIT_4F
//--------------------------------------------------------------
int (* const DATA_AC_Wait_4F_Tbl[])( FIELD_OBJ_PTR  ) =
{
	AC_Wait4F_0,
	AC_Wait_1,
	AC_End,
};

//--------------------------------------------------------------
///	AC_WAIT_8F
//--------------------------------------------------------------
int (* const DATA_AC_Wait_8F_Tbl[])( FIELD_OBJ_PTR  ) =
{
	AC_Wait8F_0,
	AC_Wait_1,
	AC_End,
};

//--------------------------------------------------------------
///	AC_WAIT_15F
//--------------------------------------------------------------
int (* const DATA_AC_Wait_15F_Tbl[])( FIELD_OBJ_PTR  ) =
{
	AC_Wait15F_0,
	AC_Wait_1,
	AC_End,
};

//--------------------------------------------------------------
///	AC_WAIT_16F
//--------------------------------------------------------------
int (* const DATA_AC_Wait_16F_Tbl[])( FIELD_OBJ_PTR  ) =
{
	AC_Wait16F_0,
	AC_Wait_1,
	AC_End,
};

//--------------------------------------------------------------
///	AC_WAIT_32F
//--------------------------------------------------------------
int (* const DATA_AC_Wait_32F_Tbl[])( FIELD_OBJ_PTR  ) =
{
	AC_Wait32F_0,
	AC_Wait_1,
	AC_End,
};

//--------------------------------------------------------------
///	AC_WARP_UP
//--------------------------------------------------------------
int (* const DATA_AC_WarpUp_Tbl[])( FIELD_OBJ_PTR ) =
{
	AC_WarpUp_0,
	AC_WarpUp_1,
	AC_End,
};

//--------------------------------------------------------------
///	AC_WARP_DOWN
//--------------------------------------------------------------
int (* const DATA_AC_WarpDown_Tbl[])( FIELD_OBJ_PTR ) =
{
	AC_WarpDown_0,
	AC_WarpDown_1,
	AC_End,
};

//--------------------------------------------------------------
///	AC_VANISH_ON
//--------------------------------------------------------------
int (* const DATA_AC_VanishON_Tbl[])( FIELD_OBJ_PTR ) =
{
	AC_VanishON_0,
	AC_End,
};

//--------------------------------------------------------------
///	AC_VANISH_OFF
//--------------------------------------------------------------
int (* const DATA_AC_VanishOFF_Tbl[])( FIELD_OBJ_PTR ) =
{
	AC_VanishOFF_0,
	AC_End,
};

//--------------------------------------------------------------
///	AC_DIR_PAUSE_ON
//--------------------------------------------------------------
int (* const DATA_AC_DirPauseON_Tbl[])( FIELD_OBJ_PTR ) =
{
	AC_DirPauseON_0,
	AC_End,
};

//--------------------------------------------------------------
///	AC_DIR_PAUSE_OFF
//--------------------------------------------------------------
int (* const DATA_AC_DirPauseOFF_Tbl[])( FIELD_OBJ_PTR ) =
{
	AC_DirPauseOFF_0,
	AC_End,
};

//--------------------------------------------------------------
///	AC_ANM_PAUSE_ON
//--------------------------------------------------------------
int (* const DATA_AC_AnmPauseON_Tbl[])( FIELD_OBJ_PTR ) =
{
	AC_AnmPauseON_0,
	AC_End,
};

//--------------------------------------------------------------
///	AC_ANM_PAUSE_OFF
//--------------------------------------------------------------
int (* const DATA_AC_AnmPauseOFF_Tbl[])( FIELD_OBJ_PTR ) =
{
	AC_AnmPauseOFF_0,
	AC_End,
};

//--------------------------------------------------------------
///	AC_MARK_GYOE 0
//--------------------------------------------------------------
int (* const DATA_AC_MarkGyoe_Tbl[])( FIELD_OBJ_PTR ) =
{
	AC_MarkGyoe_0,
	AC_Mark_1,
	AC_End,
};

//--------------------------------------------------------------
///	AC_MARK_SAISEN 0
//--------------------------------------------------------------
int (* const DATA_AC_MarkSaisen_Tbl[])( FIELD_OBJ_PTR ) =
{
	AC_MarkSaisen_0,
	AC_Mark_1,
	AC_End,
};

//--------------------------------------------------------------
///	AC_WALK_U_6F
//--------------------------------------------------------------
int (* const DATA_AC_WalkU6F_Tbl[])( FIELD_OBJ_PTR ) =
{
	AC_WalkU6F_0,
	AC_Walk6F_1,
	AC_End,
};

//--------------------------------------------------------------
///	AC_WALK_D_6F
//--------------------------------------------------------------
int (* const DATA_AC_WalkD6F_Tbl[])( FIELD_OBJ_PTR ) =
{
	AC_WalkD6F_0,
	AC_Walk6F_1,
	AC_End,
};

//--------------------------------------------------------------
///	AC_WALK_L_6F
//--------------------------------------------------------------
int (* const DATA_AC_WalkL6F_Tbl[])( FIELD_OBJ_PTR ) =
{
	AC_WalkL6F_0,
	AC_Walk6F_1,
	AC_End,
};

//--------------------------------------------------------------
///	AC_WALK_R_6F
//--------------------------------------------------------------
int (* const DATA_AC_WalkR6F_Tbl[])( FIELD_OBJ_PTR ) =
{
	AC_WalkR6F_0,
	AC_Walk6F_1,
	AC_End,
};

//--------------------------------------------------------------
///	AC_WALK_U_3F
//--------------------------------------------------------------
int (* const DATA_AC_WalkU3F_Tbl[])( FIELD_OBJ_PTR ) =
{
	AC_WalkU3F_0,
	AC_Walk3F_1,
	AC_End,
};

//--------------------------------------------------------------
///	AC_WALK_D_3F
//--------------------------------------------------------------
int (* const DATA_AC_WalkD3F_Tbl[])( FIELD_OBJ_PTR ) =
{
	AC_WalkD3F_0,
	AC_Walk3F_1,
	AC_End,
};

//--------------------------------------------------------------
///	AC_WALK_L_3F
//--------------------------------------------------------------
int (* const DATA_AC_WalkL3F_Tbl[])( FIELD_OBJ_PTR ) =
{
	AC_WalkL3F_0,
	AC_Walk3F_1,
	AC_End,
};

//--------------------------------------------------------------
///	AC_WALK_R_3F
//--------------------------------------------------------------
int (* const DATA_AC_WalkR3F_Tbl[])( FIELD_OBJ_PTR ) =
{
	AC_WalkR3F_0,
	AC_Walk3F_1,
	AC_End,
};

//--------------------------------------------------------------
///	AC_DASH_U_4F
//--------------------------------------------------------------
int (* const DATA_AC_DashU_4F_Tbl[])( FIELD_OBJ_PTR  ) =
{
	AC_DashU4F_0,
	AC_Walk_1,
	AC_End,
};

//--------------------------------------------------------------
///	AC_DASH_D_4F
//--------------------------------------------------------------
int (* const DATA_AC_DashD_4F_Tbl[])( FIELD_OBJ_PTR  ) =
{
	AC_DashD4F_0,
	AC_Walk_1,
	AC_End,
};

//--------------------------------------------------------------
///	AC_DASH_L_4F
//--------------------------------------------------------------
int (* const DATA_AC_DashL_4F_Tbl[])( FIELD_OBJ_PTR  ) =
{
	AC_DashL4F_0,
	AC_Walk_1,
	AC_End,
};

//--------------------------------------------------------------
///	AC_DASH_R_4F
//--------------------------------------------------------------
int (* const DATA_AC_DashR_4F_Tbl[])( FIELD_OBJ_PTR  ) =
{
	AC_DashR4F_0,
	AC_Walk_1,
	AC_End,
};

//--------------------------------------------------------------
///	AC_WALK_U_7F
//--------------------------------------------------------------
int (* const DATA_AC_WalkU7F_Tbl[])( FIELD_OBJ_PTR ) =
{
	AC_WalkU7F_0,
	AC_Walk7F_1,
	AC_End,
};

//--------------------------------------------------------------
///	AC_WALK_D_7F
//--------------------------------------------------------------
int (* const DATA_AC_WalkD7F_Tbl[])( FIELD_OBJ_PTR ) =
{
	AC_WalkD7F_0,
	AC_Walk7F_1,
	AC_End,
};

//--------------------------------------------------------------
///	AC_WALK_L_7F
//--------------------------------------------------------------
int (* const DATA_AC_WalkL7F_Tbl[])( FIELD_OBJ_PTR ) =
{
	AC_WalkL7F_0,
	AC_Walk7F_1,
	AC_End,
};

//--------------------------------------------------------------
///	AC_WALK_R_7F
//--------------------------------------------------------------
int (* const DATA_AC_WalkR7F_Tbl[])( FIELD_OBJ_PTR ) =
{
	AC_WalkR7F_0,
	AC_Walk7F_1,
	AC_End,
};

//--------------------------------------------------------------
///	AC_PC_BOW
//--------------------------------------------------------------
int (* const DATA_AC_PcBow_Tbl[])( FIELD_OBJ_PTR ) =
{
	AC_PcBow_0,
	AC_PcBow_1,
	AC_End,
};

//--------------------------------------------------------------
///	AC_HIDE_PULLOFF
//--------------------------------------------------------------
int (* const DATA_AC_HidePullOFF_Tbl[])( FIELD_OBJ_PTR ) =
{
	AC_HidePullOFF_0,
	AC_HidePullOFF_1,
	AC_End,
};

//--------------------------------------------------------------
///	AC_HERO_BANZAI
//--------------------------------------------------------------
int (* const DATA_AC_HeroBanzai_Tbl[])( FIELD_OBJ_PTR ) =
{
	AC_HeroBanzai_0,
	AC_HeroBanzai_1,
	AC_End,
};

//--------------------------------------------------------------
///	AC_HERO_BANZAI
//--------------------------------------------------------------
int (* const DATA_AC_HeroBanzaiUke_Tbl[])( FIELD_OBJ_PTR ) =
{
	AC_HeroBanzaiUke_0,
	AC_HeroBanzai_1,
	AC_End,
};

//==============================================================================
//	data
//==============================================================================
//--------------------------------------------------------------
///	AC_JUMP系　高さYオフセット その0
//--------------------------------------------------------------
static const fx32 DATA_AcJumpOffsTblType0[AC_JUMP_H_TBL_MAX] =			// 12
{
	4*FX32_ONE,6*FX32_ONE,8*FX32_ONE,10*FX32_ONE,
	11*FX32_ONE,12*FX32_ONE,12*FX32_ONE,12*FX32_ONE,
	11*FX32_ONE,10*FX32_ONE,9*FX32_ONE,8*FX32_ONE,
	6*FX32_ONE,4*FX32_ONE,0*FX32_ONE,0*FX32_ONE
};

//--------------------------------------------------------------
///	AC_JUMP系　高さYオフセット その1
//--------------------------------------------------------------
static const fx32 DATA_AcJumpOffsTblType1[AC_JUMP_H_TBL_MAX] =			// 6
{
	 0*FX32_ONE,2*FX32_ONE,3*FX32_ONE,4*FX32_ONE,
	 5*FX32_ONE,6*FX32_ONE,6*FX32_ONE,6*FX32_ONE,
	 5*FX32_ONE,5*FX32_ONE,4*FX32_ONE,3*FX32_ONE,
	 2*FX32_ONE,0*FX32_ONE,0*FX32_ONE,0*FX32_ONE,
};

//--------------------------------------------------------------
///	AC_JUMP系　高さYオフセット その2
//--------------------------------------------------------------
static const fx32 DATA_AcJumpOffsTblType2[AC_JUMP_H_TBL_MAX] =			// 8
{
	 2*FX32_ONE,4*FX32_ONE,6*FX32_ONE,8*FX32_ONE,
	 9*FX32_ONE,10*FX32_ONE,10*FX32_ONE,10*FX32_ONE,
	 9*FX32_ONE,8*FX32_ONE,6*FX32_ONE,5*FX32_ONE,
	 3*FX32_ONE,2*FX32_ONE,0*FX32_ONE,0*FX32_ONE,
};

//--------------------------------------------------------------
///	AC_JUMP系　高さYオフセット その3
//--------------------------------------------------------------
static const fx32 DATA_AcJumpOffsTblType3[AC_JUMP_H_TBL_MAX] =			// 12
{
	4*FX32_ONE,6*FX32_ONE,8*FX32_ONE,10*FX32_ONE,
	11*FX32_ONE,12*FX32_ONE,12*FX32_ONE,12*FX32_ONE,
	11*FX32_ONE,10*FX32_ONE,9*FX32_ONE,8*FX32_ONE,
	6*FX32_ONE,4*FX32_ONE,0*FX32_ONE,0*FX32_ONE
};

//--------------------------------------------------------------
///	AC_JUMP系　種類別高さYオフセットテーブル
//--------------------------------------------------------------
static const fx32 * DATA_AcJumpOffsetTbl[] =
{
	DATA_AcJumpOffsTblType0,
	DATA_AcJumpOffsTblType1,
	DATA_AcJumpOffsTblType2,
};

//--------------------------------------------------------------
///	AC_WALK_*_7F　移動テーブル
//--------------------------------------------------------------
static const fx32 DATA_AcWalk7FMoveValueTbl[AC_WALK_7F_FRAME] =
{
	NUM_FX32(2)+0x500, NUM_FX32(2)+0x480, NUM_FX32(2)+0x480,NUM_FX32(2)+0x480,
	NUM_FX32(2)+0x480, NUM_FX32(2)+0x480, NUM_FX32(2)+0x480
};

#if 0
static const fx32 DATA_AcWalk7FMoveValueTbl[AC_WALK_7F_FRAME] =
{
	FX32_ONE*3, FX32_ONE*2, FX32_ONE*2,FX32_ONE*2,
	FX32_ONE*3, FX32_ONE*2, FX32_ONE*2
};
#endif

//--------------------------------------------------------------
///	AC_WALK_*_6F　移動テーブル
//--------------------------------------------------------------
static const fx32 DATA_AcWalk6FMoveValueTbl[AC_WALK_6F_FRAME] =
{
	FX32_ONE*2, FX32_ONE*3, FX32_ONE*3,
	FX32_ONE*2, FX32_ONE*3, FX32_ONE*3
};

//--------------------------------------------------------------
///	AC_WALK_*_3F　移動テーブル
//--------------------------------------------------------------
static const fx32 DATA_AcWalk3FMoveValueTbl[AC_WALK_3F_FRAME] =
{
	FX32_ONE*5, FX32_ONE*6, FX32_ONE*5,
};

