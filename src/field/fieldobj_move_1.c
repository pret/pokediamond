//******************************************************************************
/**
 *
 * @file	fieldobj_move_1.c
 * @brief	フィールドOBJ　基本動作系その1　サブ動作
 * @author	kagaya
 * @data	05.07.21
 *
 */
//******************************************************************************
#include "common.h"
#include "fieldsys.h"
#include "fieldobj.h"

//==============================================================================
//	define
//==============================================================================
//#define DEBUG_IDO_ASSERT

//==============================================================================
//	struct
//==============================================================================

//==============================================================================
//	プロトタイプ
//==============================================================================
static void MoveSub_InitProcCall( FIELD_OBJ_PTR fldobj );
static int MoveSub_StartCheckProcCall( FIELD_OBJ_PTR fldobj );
static int MoveSub_MoveProcCall( FIELD_OBJ_PTR fldobj );

static int MoveSub_PosUpdateStartCheck( FIELD_OBJ_PTR fldobj );
static int MoveSub_PosUpdateEndCheck( FIELD_OBJ_PTR fldobj );

static void SubMoveNon_Init( FIELD_OBJ_PTR fldobj );
static int SubMoveNon_StartCheck( FIELD_OBJ_PTR fldobj );
static int SubMoveNon_Move( FIELD_OBJ_PTR fldobj );

static void SubMoveKyoro_Init( FIELD_OBJ_PTR fldobj );
static int SubMoveKyoro_StartCheck( FIELD_OBJ_PTR fldobj );
static int SubMoveKyoro_Move( FIELD_OBJ_PTR fldobj );

static void SubMoveSpinStop_Init( FIELD_OBJ_PTR fldobj );
static int SubMoveSpinStop_StartCheck( FIELD_OBJ_PTR fldobj );
static int SubMoveSpinStop_Move( FIELD_OBJ_PTR fldobj );

void (* const DATA_FldOBJ_EventTypeInitProcTbl[])( FIELD_OBJ_PTR );
int (* const DATA_FldOBJ_EventTypeStartCheckProcTbl[])( FIELD_OBJ_PTR );
int (* const DATA_FldOBJ_EventTypeMoveProcTbl[])( FIELD_OBJ_PTR );

//==============================================================================
//	サブ動作
//==============================================================================
//--------------------------------------------------------------
/**
 * サブ動作初期化
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_MoveSubProcInit( FIELD_OBJ_PTR fldobj )
{
	MoveSub_InitProcCall( fldobj );
}

//--------------------------------------------------------------
/**
 * サブ動作
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	int		TRUE=サブ動作による移動アリ
 */
//--------------------------------------------------------------
int FieldOBJ_MoveSub( FIELD_OBJ_PTR fldobj )
{
	if( MoveSub_StartCheckProcCall(fldobj) == FALSE ){
		return( FALSE );
	}
	
	if( MoveSub_MoveProcCall(fldobj) == FALSE ){
		return( FALSE );
	}
	
	return( TRUE );
}

//==============================================================================
//	サブ動作処理　パーツ
//==============================================================================
//--------------------------------------------------------------
/**
 * 初期化関数呼び出し
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void MoveSub_InitProcCall( FIELD_OBJ_PTR fldobj )
{
	int type = FieldOBJ_EventTypeGet( fldobj );
	DATA_FldOBJ_EventTypeInitProcTbl[type]( fldobj );
}

//--------------------------------------------------------------
/**
 * チェック関数呼び出し
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	int		TRUE=チェックに引っかかった
 */
//--------------------------------------------------------------
static int MoveSub_StartCheckProcCall( FIELD_OBJ_PTR fldobj )
{
	int type = FieldOBJ_EventTypeGet( fldobj );
	return( DATA_FldOBJ_EventTypeStartCheckProcTbl[type](fldobj) );
}

//--------------------------------------------------------------
/**
 * 動作関数呼び出し
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	int		TRUE=動作中
 */
//--------------------------------------------------------------
static int MoveSub_MoveProcCall( FIELD_OBJ_PTR fldobj )
{
	int type = FieldOBJ_EventTypeGet( fldobj );
	return( DATA_FldOBJ_EventTypeMoveProcTbl[type](fldobj) );
}

//==============================================================================
//	サブ動作用パーツ
//==============================================================================
//--------------------------------------------------------------
/**
 * 座標更新開始をチェック
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	int		TRUE=更新
 */
//--------------------------------------------------------------
static int MoveSub_PosUpdateStartCheck( FIELD_OBJ_PTR fldobj )
{
	int now = FieldOBJ_NowPosGX_Get( fldobj );
	int old = FieldOBJ_OldPosGX_Get( fldobj );
	
	if( now != old ){
		return( TRUE );
	}
	
	now = FieldOBJ_NowPosGZ_Get( fldobj );
	old = FieldOBJ_OldPosGZ_Get( fldobj );
	
	if( now != old ){
		return( TRUE );
	}
	
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * 座標更新終了をチェック
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	int		TRUE=終了
 */
//--------------------------------------------------------------
static int MoveSub_PosUpdateEndCheck( FIELD_OBJ_PTR fldobj )
{
	int now = FieldOBJ_NowPosGX_Get( fldobj );
	int old = FieldOBJ_OldPosGX_Get( fldobj );
	
	if( now != old ){
		return( FALSE );
	}
	
	now = FieldOBJ_NowPosGZ_Get( fldobj );
	old = FieldOBJ_OldPosGZ_Get( fldobj );
	
	if( now != old ){
		return( FALSE );
	}
	
	return( TRUE );
}

//==============================================================================
//	サブ動作　無し
//==============================================================================
//--------------------------------------------------------------
/**
 * サブ動作初期化　無し
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void SubMoveNon_Init( FIELD_OBJ_PTR fldobj )
{
}

//--------------------------------------------------------------
/**
 * サブ動作スタートチェック　無し
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	int		FALSE
 */
//--------------------------------------------------------------
static int SubMoveNon_StartCheck( FIELD_OBJ_PTR fldobj )
{
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * サブ動作　無し
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	int		TRUE=動作中
 */
//--------------------------------------------------------------
static int SubMoveNon_Move( FIELD_OBJ_PTR fldobj )
{
	return( FALSE );
}

//==============================================================================
//	サブ動作　止まってきょろきょろ
//==============================================================================
//--------------------------------------------------------------
///	SUBWORK_KYORO構造体
//--------------------------------------------------------------
typedef struct
{
	u8 check_seq_no;
	u8 move_seq_no;
	s8 walk_count;
	s8 max_count;
	
	s8 origin_dir;
	s8 dir_type;
	s8 dir_no;
	s8 dir_count;
	s8 wait;
}SUBWORK_KYORO;

#define SUBWORK_KYORO_SIZE (sizeof(SUBWORK_KYORO))

//--------------------------------------------------------------
///	きょろきょろ向き
//--------------------------------------------------------------
enum
{
	DIR_H_TYPE = 0,		///<横方向きょろきょろ
	DIR_V_TYPE,			///<縦方向きょろきょろ
};

#define KYORO_WAIT_FRAME (8)		///<きょろきょろの合間
#define KYORO_COUNT_MAX (4)			///<きょろきょろ回数最大

//--------------------------------------------------------------
/**
 * 止まってきょろきょろ　初期化
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void SubMoveKyoro_Init( FIELD_OBJ_PTR fldobj )
{
	SUBWORK_KYORO *work;
	
	work = FieldOBJ_MoveSubProcWorkInit( fldobj, SUBWORK_KYORO_SIZE );
	work->max_count = FieldOBJ_ParamGet( fldobj, FLDOBJ_PARAM_1 );
}

//--------------------------------------------------------------
/**
 * 止まってきょろきょろ　スタートチェック
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	int		TRUE=動作アリ
 */
//--------------------------------------------------------------
static int SubMoveKyoro_StartCheck( FIELD_OBJ_PTR fldobj )
{
	SUBWORK_KYORO *work;
	
	work = FieldOBJ_MoveSubProcWorkGet( fldobj );
	
	switch( work->check_seq_no ){
	case 0:														//移動開始監視
		if( MoveSub_PosUpdateStartCheck(fldobj) == TRUE ){
			work->check_seq_no++;
		}
		
		break;
	case 1:														//移動終了監視
		if( MoveSub_PosUpdateEndCheck(fldobj) == FALSE ){
			break;
		}
		
		work->walk_count++;
		
		if( work->walk_count < work->max_count ){
			work->check_seq_no = 0;
			break;
		}
		
		work->check_seq_no++;
	case 2:														//移動完了監視
		if( FieldOBJ_StatusBitCheck_Move(fldobj) == TRUE ){
#ifdef DEBUG_IDO_ASSERT
			GF_ASSERT( MoveSub_PosUpdateStartCheck(fldobj) == TRUE &&
					"SubMoveKyoro_StartCheck()ERROR" );
#endif
			break;
		}
		
		work->check_seq_no++;
		work->walk_count = 0;
		work->move_seq_no = 0;
	case 3:														//サブ動作中
		return( TRUE );
	}
	
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * 止まってきょろきょろ　動作
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	int		TRUE=動作中
 */
//--------------------------------------------------------------
static int SubMoveKyoro_Move( FIELD_OBJ_PTR fldobj )
{
	SUBWORK_KYORO *work;
	
	work = FieldOBJ_MoveSubProcWorkGet( fldobj );
	
	switch( work->move_seq_no ){
	case 0:														//初期化
		{
			int type_tbl[4] = {DIR_H_TYPE,DIR_H_TYPE,DIR_V_TYPE,DIR_V_TYPE};
			int dir = FieldOBJ_DirDispGet( fldobj );
			work->origin_dir = dir;
			work->dir_type = type_tbl[dir];
			work->move_seq_no++;
		}
	case 1:														//方向セット	
		{
			int dir_tbl[2][2] = { {DIR_LEFT,DIR_RIGHT},{DIR_UP,DIR_DOWN} };
			int dir = dir_tbl[work->dir_type][work->dir_no];
			int code = FieldOBJ_AcmdCodeDirChange( dir, AC_DIR_U );
			FieldOBJ_CmdSet( fldobj, code );
			work->move_seq_no++;
		}
	case 2:
		{
			if( FieldOBJ_CmdAction(fldobj) == FALSE ){
				return( TRUE );
			}
			
			work->move_seq_no++;
		}
	case 3:
		{
			work->wait++;
			
			if( work->wait < KYORO_WAIT_FRAME ){
				return( TRUE );
			}
			
			work->wait = 0;
			work->dir_count++;
			
			if( work->dir_count < KYORO_COUNT_MAX ){
				work->dir_no = (work->dir_no + 1) & 0x01;
				work->move_seq_no = 1;
				return( TRUE );
			}
			
			FieldOBJ_DirDispCheckSet( fldobj, work->origin_dir );
			work->move_seq_no++;
			work->dir_count = 0;
			work->check_seq_no = 0;
		}
	}
	
	return( FALSE );
}

//==============================================================================
//	サブ動作　止まってクルクル
//==============================================================================
//--------------------------------------------------------------
///	SUBWORK_SPIN_STOP構造体
//--------------------------------------------------------------
typedef struct
{
	u8 check_seq_no;
	u8 move_seq_no;
	s8 walk_count;
	s8 max_count;
	
	s8 origin_dir;
	s8 dir_type;
	s8 dir_no;
	s8 dir_count;
	s8 wait;
}SUBWORK_SPIN_STOP;

#define SUBWORK_SPIN_STOP_SIZE (sizeof(SUBWORK_SPIN_STOP))

//--------------------------------------------------------------
///	回転方向
//--------------------------------------------------------------
enum
{
	SPIN_STOP_L_TYPE = 0,		///<左回転
	SPIN_STOP_R_TYPE,			///<右回転
};

#define SPIN_STOP_WAIT_FRAME (8)	///<回転の間
#define SPIN_STOP_COUNT_MAX (4)		///<回転最大数

//--------------------------------------------------------------
/**
 * 止まってクルクル　初期化
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void SubMoveSpinStop_Init( FIELD_OBJ_PTR fldobj )
{
	int type;
	SUBWORK_SPIN_STOP *work;
	
	work = FieldOBJ_MoveSubProcWorkInit( fldobj, SUBWORK_SPIN_STOP_SIZE );
	work->max_count = FieldOBJ_ParamGet( fldobj, FLDOBJ_PARAM_1 );
	
	type = FieldOBJ_EventTypeGet( fldobj );
	
	if( type == EV_TYPE_TRAINER_SPIN_STOP_L ){
		type = SPIN_STOP_L_TYPE;
	}else{
		type = SPIN_STOP_R_TYPE;
	}
	
	work->dir_type = type;
}

//--------------------------------------------------------------
/**
 * 止まってクルクル　スタートチェック
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	int		TRUE=動作アリ
 */
//--------------------------------------------------------------
static int SubMoveSpinStop_StartCheck( FIELD_OBJ_PTR fldobj )
{
	SUBWORK_SPIN_STOP *work;
	
	work = FieldOBJ_MoveSubProcWorkGet( fldobj );
	
	switch( work->check_seq_no ){
	case 0:														//移動開始監視
		if( MoveSub_PosUpdateStartCheck(fldobj) == TRUE ){
			work->check_seq_no++;
		}
		
		break;
	case 1:														//移動終了監視
		if( MoveSub_PosUpdateEndCheck(fldobj) == FALSE ){
			break;
		}
		
		work->walk_count++;
		
		if( work->walk_count < work->max_count ){
			work->check_seq_no = 0;
			break;
		}
		
		work->check_seq_no++;
	case 2:														//移動完了監視
		if( FieldOBJ_StatusBitCheck_Move(fldobj) == TRUE ){
#ifdef DEBUG_IDO_ASSERT
			GF_ASSERT( MoveSub_PosUpdateStartCheck(fldobj) == TRUE &&
				"SubMoveKyoro_StartCheck()対象の移動方法が異常" );
#endif
			break;
		}
		
		work->check_seq_no++;
		work->walk_count = 0;
		work->move_seq_no = 0;
	case 3:														//サブ動作中
		return( TRUE );
	}
	
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * 止まってクルクル　動作
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	int		TRUE=動作中
 */
//--------------------------------------------------------------
static int SubMoveSpinStop_Move( FIELD_OBJ_PTR fldobj )
{
	SUBWORK_KYORO *work;
	int spin_tbl[2][4] =
	{ {DIR_UP,DIR_LEFT,DIR_DOWN,DIR_RIGHT},{DIR_UP,DIR_RIGHT,DIR_DOWN,DIR_LEFT} };
	
	work = FieldOBJ_MoveSubProcWorkGet( fldobj );
	
	switch( work->move_seq_no ){
	case 0:														//初期化
		{
			int i,dir = FieldOBJ_DirDispGet( fldobj );
			
			for( i = 0; (i < DIR_4_MAX && dir != spin_tbl[work->dir_type][i]); i++ ){}
			GF_ASSERT( i < DIR_4_MAX && "SubMoveKyoro_Move()方向異常" );
			
			work->origin_dir = dir;
			work->dir_no = (i + 1) % SPIN_STOP_COUNT_MAX;		//+1=1つ先
			work->move_seq_no++;
		}
	case 1:														//方向セット	
		{
			int dir = spin_tbl[work->dir_type][work->dir_no];
			int code = FieldOBJ_AcmdCodeDirChange( dir, AC_DIR_U );
			FieldOBJ_CmdSet( fldobj, code );
			work->move_seq_no++;
		}
	case 2:
		{
			if( FieldOBJ_CmdAction(fldobj) == FALSE ){
				return( TRUE );
			}
			
			work->move_seq_no++;
		}
	case 3:
		{
			work->wait++;
			
			if( work->wait < SPIN_STOP_WAIT_FRAME ){
				return( TRUE );
			}
			
			work->wait = 0;
			work->dir_count++;
			
			if( work->dir_count < SPIN_STOP_COUNT_MAX ){
				work->dir_no = (work->dir_no + 1) % SPIN_STOP_COUNT_MAX;
				work->move_seq_no = 1;
				return( TRUE );
			}
			
			FieldOBJ_DirDispCheckSet( fldobj, work->origin_dir );
			work->move_seq_no++;
			work->dir_count = 0;
			work->check_seq_no = 0;
		}
	}
	
	return( FALSE );
}

//==============================================================================
//	data
//==============================================================================
//--------------------------------------------------------------
//	イベントタイプ別初期化関数 EV_TYPE_NORMAL等の値に一致
//--------------------------------------------------------------
static void (* const DATA_FldOBJ_EventTypeInitProcTbl[])( FIELD_OBJ_PTR ) =
{
	SubMoveNon_Init, //EV_TYPE_NORMAL
	SubMoveNon_Init, //EV_TYPE_TRAINER
	SubMoveNon_Init, //EV_TYPE_TRAINER_EYEALL
	SubMoveNon_Init, //EV_TYPE_ITEM
	SubMoveKyoro_Init, //EV_TYPE_TRAINER_KYORO
	SubMoveSpinStop_Init, //EV_TYPE_TRAINER_SPIN_STOP_L
	SubMoveSpinStop_Init, //EV_TYPE_TRAINER_SPIN_STOP_R
	SubMoveNon_Init, //EV_TYPE_TRAINER_SPIN_MOVE_L
	SubMoveNon_Init, //EV_TYPE_TRAINER_SPIN_MOVE_R
	SubMoveNon_Init, //EV_TYPE_MSG
	
	SubMoveNon_Init, //EV_TYPE_TRAINER_ESCAPE
	SubMoveNon_Init, //EV_TYPE_TRAINER_SWIM_H
};

//--------------------------------------------------------------
//	イベントタイプ別スタートチェック関数　EV_TYPE_NORMAL等の値に一致
//--------------------------------------------------------------
static int (* const DATA_FldOBJ_EventTypeStartCheckProcTbl[])( FIELD_OBJ_PTR ) =
{
	SubMoveNon_StartCheck, //EV_TYPE_NORMAL
	SubMoveNon_StartCheck, //EV_TYPE_TRAINER
	SubMoveNon_StartCheck, //EV_TYPE_TRAINER_EYEALL
	SubMoveNon_StartCheck, //EV_TYPE_ITEM
	SubMoveKyoro_StartCheck, //EV_TYPE_TRAINER_KYORO
	SubMoveSpinStop_StartCheck, //EV_TYPE_TRAINER_SPIN_STOP_L
	SubMoveSpinStop_StartCheck, //EV_TYPE_TRAINER_SPIN_STOP_R
	SubMoveNon_StartCheck, //EV_TYPE_TRAINER_SPIN_MOVE_L
	SubMoveNon_StartCheck, //EV_TYPE_TRAINER_SPIN_MOVE_R
	SubMoveNon_StartCheck, //EV_TYPE_MSG
	
	SubMoveNon_StartCheck, //EV_TYPE_TRAINER_ESCAPE
	SubMoveNon_StartCheck, //EV_TYPE_TRAINER_SWIM_H
};

//--------------------------------------------------------------
//	イベントタイプ別動作関数 EV_TYPE_NORMAL等の値に一致
//--------------------------------------------------------------
static int (* const DATA_FldOBJ_EventTypeMoveProcTbl[])( FIELD_OBJ_PTR ) =
{
	SubMoveNon_Move, //EV_TYPE_NORMAL
	SubMoveNon_Move, //EV_TYPE_TRAINER
	SubMoveNon_Move, //EV_TYPE_TRAINER_EYEALL
	SubMoveNon_Move, //EV_TYPE_ITEM
	SubMoveKyoro_Move, //EV_TYPE_TRAINER_KYORO
	SubMoveSpinStop_Move, //EV_TYPE_TRAINER_SPIN_STOP_L
	SubMoveSpinStop_Move, //EV_TYPE_TRAINER_SPIN_STOP_R
	SubMoveNon_Move, //EV_TYPE_TRAINER_SPIN_MOVE_L
	SubMoveNon_Move, //EV_TYPE_TRAINER_SPIN_MOVE_R
	SubMoveNon_Move, //EV_TYPE_MSG
	
	SubMoveNon_Move, //EV_TYPE_TRAINER_ESCAPE
	SubMoveNon_Move, //EV_TYPE_TRAINER_SWIM_H
};
