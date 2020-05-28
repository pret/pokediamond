//******************************************************************************
/**
 *
 * @file	fieldobj_move_0.c
 * @brief	フィールドOBJ　基本動作系その0
 * @author	kagaya
 * @data	05.07.21
 *
 */
//******************************************************************************
#include "common.h"
#include "fieldsys.h"
#include "fieldobj.h"

#include "ev_trainer.h"

//==============================================================================
//	define
//==============================================================================
#define WAIT_END (-1)										///<ウェイト終端

//--------------------------------------------------------------
//	MV_RND系　移動チェック方式識別
//--------------------------------------------------------------
enum
{
	MV_RND_MOVE_CHECK_NORMAL = 0,							///<通常チェック
	MV_RND_MOVE_CHECK_RECT,									///<矩形チェックアリ
};

//--------------------------------------------------------------
///	MV_SPIN_DIR動作番号
//--------------------------------------------------------------
enum
{
	SEQNO_MV_SPIN_DIR_CMD_SET = 0,
	SEQNO_MV_SPIN_DIR_CMD_ACT,
	SEQNO_MV_SPIN_DIR_WAIT,
	SEQNO_MV_SPIN_DIR_NEXT_DIR_SET,
};

#define MV_SPIN_WAIT_FRAME (24)	//AGB 48 frame

//--------------------------------------------------------------
///	MV_REWAR動作番号
//--------------------------------------------------------------
enum
{
	SEQNO_MV_REWAR_DIR_CMD_SET = 0,
	SEQNO_MV_REWAR_DIR_CMD_ACT,
	SEQNO_MV_REWAR_DIR_WAIT,
	SEQNO_MV_REWAR_DIR_NEXT_DIR_SET,
};

//--------------------------------------------------------------
///	MV_RT2動作番号
//--------------------------------------------------------------
enum
{
	SEQNO_MV_RT2_DIR_CHECK = 0,
	SEQNO_MV_RT2_MOVE_SET,
	SEQNO_MV_RT2_MOVE,
};

//--------------------------------------------------------------
///	MV_RT3動作番号
//--------------------------------------------------------------
enum
{
	SEQNO_MV_RT3_MOVE_DIR_SET = 0,
	SEQNO_MV_RT3_MOVE,
};

#define MV_RT3_TURN_END_NO (3)	///<3点巡回終了値

enum
{
	MV_RT3_CHECK_TYPE_X = 0,
	MV_RT3_CHECK_TYPE_Z,
};

//--------------------------------------------------------------
///	サブ動作　クルクル移動　回転方向
//--------------------------------------------------------------
enum
{
	RT_KURU2_L = 0,
	RT_KURU2_R,
	RT_KURU2_MAX,
};

#define RT_KURU2_DIR_MAX (DIR_4_MAX)		///<クルクル移動最大回転数

//--------------------------------------------------------------
///	方向テーブルID
//--------------------------------------------------------------
enum
{
	DIRID_MvDirRndDirTbl = 0,
	DIRID_MvDirRndDirTbl_UL,
	DIRID_MvDirRndDirTbl_UR,
	DIRID_MvDirRndDirTbl_DL,
	DIRID_MvDirRndDirTbl_DR,
	DIRID_MvDirRndDirTbl_UDL,
	DIRID_MvDirRndDirTbl_UDR,
	DIRID_MvDirRndDirTbl_ULR,
	DIRID_MvDirRndDirTbl_DLR,
	DIRID_MvDirRndDirTbl_UD,
	DIRID_MvDirRndDirTbl_LR,
	DIRID_MV_RND_DirTbl,
	DIRID_MV_RND_V_DirTbl,
	DIRID_MV_RND_H_DirTbl,
	DIRID_MvRtURLD_DirTbl,
	DIRID_MvRtRLDU_DirTbl,
	DIRID_MvRtDURL_DirTbl,
	DIRID_MvRtLDUR_DirTbl,
	DIRID_MvRtULRD_DirTbl,
	DIRID_MvRtLRDU_DirTbl,
	DIRID_MvRtDULR_DirTbl,
	DIRID_MvRtRDUL_DirTbl,
	DIRID_MvRtLUDR_DirTbl,
	DIRID_MvRtUDRL_DirTbl,
	DIRID_MvRtRLUD_DirTbl,
	DIRID_MvRtDRLU_DirTbl,
	DIRID_MvRtRUDL_DirTbl,
	DIRID_MvRtUDLR_DirTbl,
	DIRID_MvRtLRUD_DirTbl,
	DIRID_MvRtDLRU_DirTbl,
	DIRID_MvRtUL_DirTbl,
	DIRID_MvRtDR_DirTbl,
	DIRID_MvRtLD_DirTbl,
	DIRID_MvRtRU_DirTbl,
	DIRID_MvRtUR_DirTbl,
	DIRID_MvRtDL_DirTbl,
	DIRID_MvRtLU_DirTbl,
	DIRID_MvRtRD_DirTbl,
	DIRID_MvDirSpin_DirTbl,
	DIRID_END,
	DIRID_MAX,
};

//--------------------------------------------------------------
//	debug
//--------------------------------------------------------------
#ifdef PM_DEBUG
//#define DEBUG_SEARCH	//有効で方向切り替え型動作全て自機サーチ
#endif

//==============================================================================
//	typedef
//==============================================================================
//--------------------------------------------------------------
//	DIR_TBL構造体
//--------------------------------------------------------------
typedef struct
{
	int id;
	const int *tbl;
}DIR_TBL;

//--------------------------------------------------------------
///	RECT構造体
//--------------------------------------------------------------
typedef struct
{
	int left;
	int top;
	int right;
	int bottom;
}RECT;

//--------------------------------------------------------------
///	RT_KURUKURU_WORK構造体
//--------------------------------------------------------------
typedef struct
{
	s8 origin_dir;
	s8 spin_type;
	u8 dir_pause;
	u8 dmy;
}RT_KURUKURU_WORK;

#define RT_KURUKURU_WORK_SIZE (sizeof(RT_KURUKURU_WORK))

//--------------------------------------------------------------
///	MV_DIR_RND_WORK構造体
//--------------------------------------------------------------
typedef struct
{
	u16 seq_no;												///<シーケンスナンバー
	s16 wait;												///<表示ウェイト
	int tbl_id;
}MV_DIR_RND_WORK;

#define MV_DIR_RND_WORK_SIZE (sizeof(MV_DIR_RND_WORK))		///<MV_DIR_RND_WORKサイズ

//--------------------------------------------------------------
///	MV_RND_WORK 構造体
//--------------------------------------------------------------
typedef struct
{
	s16 seq_no;
	s16 wait;
	int move_check_type;
	int acmd_code;
	int tbl_id;
}MV_RND_WORK;

#define MV_RND_WORK_SIZE (sizeof(MV_RND_WORK))

//--------------------------------------------------------------
///	MV_DIR_WORK 構造体
//--------------------------------------------------------------
typedef struct
{
	int dir;
	int seq_no;
}MV_DIR_WORK;

#define MV_DIR_WORK_SIZE (sizeof(MV_DIR_WORK))

//--------------------------------------------------------------
///	MV_SPIN_DIR_WORK構造体
//--------------------------------------------------------------
typedef struct
{
	s8 spin_dir;
	s8 set_dir;
	s8 seq_no;
	s8 tbl_no;
	int wait;
}MV_SPIN_DIR_WORK;

#define MV_SPIN_DIR_WORK_SIZE (sizeof(MV_SPIN_DIR_WORK))

//--------------------------------------------------------------
///	MV_RT2_WORK構造体
//--------------------------------------------------------------
typedef struct
{
	s16 seq_no;
	s16 turn_flag;
	RT_KURUKURU_WORK kurukuru;
}MV_RT2_WORK;

#define MV_RT2_WORK_SIZE (sizeof(MV_RT2_WORK))

//--------------------------------------------------------------
///	MV_RT3_WORK構造体
//--------------------------------------------------------------
typedef struct
{
	s16 seq_no;
	s16 turn_no;
	s16 turn_check_no;
	s16 turn_check_type;
	int tbl_id;
	RT_KURUKURU_WORK kurukuru;
}MV_RT3_WORK;

#define MV_RT3_WORK_SIZE (sizeof(MV_RT3_WORK))

//==============================================================================
//	プロトタイプ
//==============================================================================
static void DirRndWorkInit( FIELD_OBJ_PTR fldobj, int id );

static void MvRndWorkInit( FIELD_OBJ_PTR fldobj, int ac, int id, int check );

static int TblNumGet( const int *tbl, int end );
static int TblRndGet( const int *tbl, int end );
static int TblIDRndGet( int id, int end );
static const int * MoveDirTblIDSearch( int id );
static int TrJikiDashSearch( FIELD_OBJ_PTR fldobj );
static int TrJikiDashSearchTbl( FIELD_OBJ_PTR fldobj, int id, int end );

static void MvRndRectMake( FIELD_OBJ_PTR fldobj, RECT *rect );
static int MvRndRectMoveLimitCheck( FIELD_OBJ_PTR fldobj, int dir );

static void MvDirWorkInit( FIELD_OBJ_PTR fldobj, int dir );

static void MvSpinDirWorkInit( FIELD_OBJ_PTR fldobj, int dir );
int (* const DATA_MvSpinMoveTbl[])( FIELD_OBJ_PTR fldobj, MV_SPIN_DIR_WORK *work );

int (* const DATA_MvRewarMoveTbl[])( FIELD_OBJ_PTR fldobj, MV_SPIN_DIR_WORK *work );

int (* const DATA_MvRt2MoveTbl[])( FIELD_OBJ_PTR fldobj, MV_RT2_WORK *work );

static void MvRt3WorkInit( FIELD_OBJ_PTR fldobj, int check_no, int check_type, int id );
int (* const DATA_MvRt3MoveTbl[])( FIELD_OBJ_PTR fldobj, MV_RT3_WORK *work );

static const int DATA_KuruKuruTbl[RT_KURU2_MAX][RT_KURU2_DIR_MAX];
static int MoveSub_KuruKuruCheck( FIELD_OBJ_PTR fldobj );
static void MoveSub_KuruKuruInit( FIELD_OBJ_PTR fldobj, RT_KURUKURU_WORK *work );
static void MoveSub_KuruKuruSet( FIELD_OBJ_PTR fldobj, RT_KURUKURU_WORK *work );
static void MoveSub_KuruKuruEnd( FIELD_OBJ_PTR fldobj, RT_KURUKURU_WORK *work );

//data
const int DATA_MvDirRndWaitTbl[];
const int DATA_MvDirRndDirTbl[];
const int DATA_MvDirRndDirTbl_UL[];
const int DATA_MvDirRndDirTbl_UR[];
const int DATA_MvDirRndDirTbl_DL[];
const int DATA_MvDirRndDirTbl_DR[];
const int DATA_MvDirRndDirTbl_UDL[];
const int DATA_MvDirRndDirTbl_UDR[];
const int DATA_MvDirRndDirTbl_ULR[];
const int DATA_MvDirRndDirTbl_DLR[];
const int DATA_MvDirRndDirTbl_UD[];
const int DATA_MvDirRndDirTbl_LR[];

const int DATA_MV_RND_DirTbl[];
const int DATA_MV_RND_V_DirTbl[];
const int DATA_MV_RND_H_DirTbl[];

const int DATA_MvRtURLD_DirTbl[];
const int DATA_MvRtRLDU_DirTbl[];
const int DATA_MvRtDURL_DirTbl[];
const int DATA_MvRtLDUR_DirTbl[];
const int DATA_MvRtULRD_DirTbl[];
const int DATA_MvRtLRDU_DirTbl[];
const int DATA_MvRtDULR_DirTbl[];
const int DATA_MvRtRDUL_DirTbl[];
const int DATA_MvRtLUDR_DirTbl[];
const int DATA_MvRtUDRL_DirTbl[];
const int DATA_MvRtRLUD_DirTbl[];
const int DATA_MvRtDRLU_DirTbl[];
const int DATA_MvRtRUDL_DirTbl[];
const int DATA_MvRtUDLR_DirTbl[];
const int DATA_MvRtLRUD_DirTbl[];
const int DATA_MvRtDLRU_DirTbl[];

const int DATA_MvRtUL_DirTbl[];
const int DATA_MvRtDR_DirTbl[];
const int DATA_MvRtLD_DirTbl[];
const int DATA_MvRtRU_DirTbl[];
const int DATA_MvRtUR_DirTbl[];
const int DATA_MvRtDL_DirTbl[];
const int DATA_MvRtLU_DirTbl[];
const int DATA_MvRtRD_DirTbl[];

static const DIR_TBL DATA_MoveDirTbl[DIRID_MAX];

const int JikiDashSensorMoveCodeTbl[];

//==============================================================================
//	デバッグ
//==============================================================================

//==============================================================================
//	MV_DIR_RND	ランダムに方向切り替え
//==============================================================================
//--------------------------------------------------------------
/**
 * MV_DIR_RND_WORK初期化
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	id		方向テーブルID
 * @retval	nothing
 */
//--------------------------------------------------------------
static void DirRndWorkInit( FIELD_OBJ_PTR fldobj, int id )
{
	MV_DIR_RND_WORK *work;
	
	work = FieldOBJ_MoveProcWorkInit( fldobj, MV_DIR_RND_WORK_SIZE );	//動作ワーク初期化
	work->wait = TblRndGet( DATA_MvDirRndWaitTbl, WAIT_END );			//待ち時間セット
	work->tbl_id = id;
	
	FieldOBJ_DrawStatusSet( fldobj, DRAW_STA_STOP );					//描画ステータス　停止
	FieldOBJ_StatusBitOFF_Move( fldobj );								//常に停止中
}

//--------------------------------------------------------------
/**
 * MV_DIR_RND 初期化
 * @param	fldobj		FIELD_OBJ_PTR 
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_MoveDirRnd_Init( FIELD_OBJ_PTR fldobj )
{
	DirRndWorkInit( fldobj, DIRID_MvDirRndDirTbl );
}

//--------------------------------------------------------------
/**
 * MV_RND_UL 初期化
 * @param	fldobj		FIELD_OBJ_PTR 
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_MoveDirRndUL_Init( FIELD_OBJ_PTR fldobj )
{
	DirRndWorkInit( fldobj, DIRID_MvDirRndDirTbl_UL );
}

//--------------------------------------------------------------
/**
 * MV_RND_UR 初期化
 * @param	fldobj		FIELD_OBJ_PTR 
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_MoveDirRndUR_Init( FIELD_OBJ_PTR fldobj )
{
	DirRndWorkInit( fldobj, DIRID_MvDirRndDirTbl_UR );
}

//--------------------------------------------------------------
/**
 * MV_RND_DL 初期化
 * @param	fldobj		FIELD_OBJ_PTR 
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_MoveDirRndDL_Init( FIELD_OBJ_PTR fldobj )
{
	DirRndWorkInit( fldobj, DIRID_MvDirRndDirTbl_DL );
}

//--------------------------------------------------------------
/**
 * MV_RND_DR 初期化
 * @param	fldobj		FIELD_OBJ_PTR 
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_MoveDirRndDR_Init( FIELD_OBJ_PTR fldobj )
{
	DirRndWorkInit( fldobj, DIRID_MvDirRndDirTbl_DR );
}

//--------------------------------------------------------------
/**
 * MV_RND_UDL 初期化
 * @param	fldobj		FIELD_OBJ_PTR 
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_MoveDirRndUDL_Init( FIELD_OBJ_PTR fldobj )
{
	DirRndWorkInit( fldobj, DIRID_MvDirRndDirTbl_UDL );
}

//--------------------------------------------------------------
/**
 * MV_RND_UDR 初期化
 * @param	fldobj		FIELD_OBJ_PTR 
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_MoveDirRndUDR_Init( FIELD_OBJ_PTR fldobj )
{
	DirRndWorkInit( fldobj, DIRID_MvDirRndDirTbl_UDR );
}

//--------------------------------------------------------------
/**
 * MV_RND_ULR 初期化
 * @param	fldobj		FIELD_OBJ_PTR 
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_MoveDirRndULR_Init( FIELD_OBJ_PTR fldobj )
{
	DirRndWorkInit( fldobj, DIRID_MvDirRndDirTbl_ULR );
}

//--------------------------------------------------------------
/**
 * MV_RND_DLR 初期化
 * @param	fldobj		FIELD_OBJ_PTR 
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_MoveDirRndDLR_Init( FIELD_OBJ_PTR fldobj )
{
	DirRndWorkInit( fldobj, DIRID_MvDirRndDirTbl_DLR );
}

//--------------------------------------------------------------
/**
 * MV_RND_UD 初期化
 * @param	fldobj		FIELD_OBJ_PTR 
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_MoveDirRndUD_Init( FIELD_OBJ_PTR fldobj )
{
	DirRndWorkInit( fldobj, DIRID_MvDirRndDirTbl_UD );
}

//--------------------------------------------------------------
/**
 * MV_RND_LR 初期化
 * @param	fldobj		FIELD_OBJ_PTR 
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_MoveDirRndLR_Init( FIELD_OBJ_PTR fldobj )
{
	DirRndWorkInit( fldobj, DIRID_MvDirRndDirTbl_LR );
}

//--------------------------------------------------------------
/**
 * MV_DIR_RND 動作
 * @param	fldobj		FIELD_OBJ_PTR 
 * @retval	int			TRUE=初期化成功
 */
//--------------------------------------------------------------
void FieldOBJ_MoveDirRnd_Move( FIELD_OBJ_PTR fldobj )
{
	MV_DIR_RND_WORK *work = FieldOBJ_MoveProcWorkGet( fldobj );
	int dir = TrJikiDashSearchTbl( fldobj, work->tbl_id, DIR_NOT );
	
	if( dir != DIR_NOT ){
		FieldOBJ_DirDispCheckSet( fldobj, dir );
	}else{
		switch( work->seq_no ){
		case 0:
			work->wait--;
		
			if( work->wait <= 0 ){									//待ち時間 0
				work->wait = TblRndGet( DATA_MvDirRndWaitTbl, WAIT_END );
				FieldOBJ_DirDispCheckSet( fldobj, TblIDRndGet(work->tbl_id,DIR_NOT) );
			}
		}
	}
	
	FieldOBJ_GPosUpdate( fldobj );
}

//--------------------------------------------------------------
/**
 * MV_DIR_RND 削除関数
 * @param	fldobj	FIELD_OBJ_PTR 
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_MoveDirRnd_Delete( FIELD_OBJ_PTR fldobj )
{
}

//==============================================================================
//	MV_RND系	ランダムに移動
//==============================================================================
//--------------------------------------------------------------
/**
 * MV_RND 初期化
 * @param	fldobj		FIELD_OBJ_PTR 
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_MoveRnd_Init( FIELD_OBJ_PTR fldobj )
{
	MvRndWorkInit( fldobj, AC_WALK_U_8F, DIRID_MV_RND_DirTbl, MV_RND_MOVE_CHECK_NORMAL );
}

//--------------------------------------------------------------
/**
 * MV_RND_V 初期化
 * @param	fldobj		FIELD_OBJ_PTR 
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_MoveRndV_Init( FIELD_OBJ_PTR fldobj )
{
	MvRndWorkInit( fldobj, AC_WALK_U_8F, DIRID_MV_RND_V_DirTbl, MV_RND_MOVE_CHECK_NORMAL );
}

//--------------------------------------------------------------
/**
 * MV_RND_H 初期化
 * @param	fldobj		FIELD_OBJ_PTR 
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_MoveRndH_Init( FIELD_OBJ_PTR fldobj )
{
	MvRndWorkInit( fldobj, AC_WALK_U_8F, DIRID_MV_RND_H_DirTbl, MV_RND_MOVE_CHECK_NORMAL );
}

//--------------------------------------------------------------
/**
 * MV_RND_UL系 初期化
 * @param	fldobj		FIELD_OBJ_PTR 
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_MoveRndRect_Init( FIELD_OBJ_PTR fldobj )
{
	MvRndWorkInit( fldobj, AC_WALK_U_8F, DIRID_MV_RND_DirTbl, MV_RND_MOVE_CHECK_RECT );
}

//==============================================================================
//	MV_RND系　パーツ
//==============================================================================
//--------------------------------------------------------------
/**
 * MV_RND_WORK初期化
 * @param	fldobj		FIELD_OBJ_PTR
 * @param	ac			移動する際に使用するアニメーションコマンド。
 * FieldOBJ_AcmdCodeDirChange()で変換対象となる。AC_WALK_U_32F等
 * @param	tbl_id		方向テーブルID
 * @param	check		MV_RND_MOVE_CHECK_NORMAL等
 * @retval	nothing
 */
//--------------------------------------------------------------
static void MvRndWorkInit( FIELD_OBJ_PTR fldobj, int ac, int tbl_id, int check )
{
	MV_RND_WORK *work;
	
	work = FieldOBJ_MoveProcWorkInit( fldobj, MV_RND_WORK_SIZE );
	work->move_check_type = check;
	work->acmd_code = ac;
	work->tbl_id = tbl_id;
	
	FieldOBJ_DrawStatusSet( fldobj, DRAW_STA_STOP );
	FieldOBJ_StatusBitOFF_Move( fldobj );
}

//--------------------------------------------------------------
/**
 * MV_RND系　動作
 * @param	fldobj		FIELD_OBJ_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_MvRnd_Move( FIELD_OBJ_PTR fldobj )
{
	int ret;
	MV_RND_WORK *work;
	
	work = FieldOBJ_MoveProcWorkGet( fldobj );
	
	switch( work->seq_no ){
	case 0:
		FieldOBJ_StatusBitOFF_Move( fldobj );
		FieldOBJ_StatusBitOFF_MoveEnd( fldobj );
		
		ret = FieldOBJ_DirDispGet( fldobj );
		ret = FieldOBJ_AcmdCodeDirChange( ret, AC_DIR_U );
		FieldOBJ_CmdSet( fldobj, ret );
		
		work->seq_no++;
		break;
	case 1:
		if( FieldOBJ_CmdAction(fldobj) == FALSE ){
			break;
		}
		
		work->wait = TblRndGet( DATA_MvDirRndWaitTbl, WAIT_END );
		work->seq_no++;
	case 2:
		work->wait--;
		
		if( work->wait ){
			break;
		}
		
		work->seq_no++;
	case 3:
		ret = TblIDRndGet( work->tbl_id, DIR_NOT );
		FieldOBJ_DirMoveDispCheckSet( fldobj, ret );
		
		if( work->move_check_type == MV_RND_MOVE_CHECK_RECT ){
			if( MvRndRectMoveLimitCheck(fldobj,ret) == FALSE ){
				work->seq_no = 0;
				break;
			}
		}
		
		if( FieldOBJ_MoveHitCheckDir(fldobj,ret) != FLDOBJ_MOVE_HIT_BIT_NON ){
			work->seq_no = 0;
			break;
		}
		
		ret = FieldOBJ_AcmdCodeDirChange( ret, work->acmd_code );
		FieldOBJ_CmdSet( fldobj, ret );
			
		FieldOBJ_StatusBitON_Move( fldobj );
		work->seq_no++;
	case 4:
		if( FieldOBJ_CmdAction(fldobj) == FALSE ){
			break;
		}
		
		FieldOBJ_StatusBitOFF_Move( fldobj );
		work->seq_no = 0;
	}
}

//==============================================================================
//	MV_RND_UL等パーツ
//==============================================================================
//--------------------------------------------------------------
/**
 * 移動可能範囲矩形作成
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	rect	矩形格納先
 * @retval	nothing
 */
//--------------------------------------------------------------
static void MvRndRectMake( FIELD_OBJ_PTR fldobj, RECT *rect )
{
	int code,ix,iz,lx,lz;
	
	ix = FieldOBJ_InitPosGX_Get( fldobj );
	iz = FieldOBJ_InitPosGZ_Get( fldobj );
	lx = FieldOBJ_MoveLimitXGet( fldobj );
	lz = FieldOBJ_MoveLimitZGet( fldobj );
	
	code = FieldOBJ_MoveCodeGet( fldobj );
	
	switch( code ){
	case MV_RND_UL:
		rect->left = ix - lx; rect->right = ix;
		rect->top = iz - lz; rect->bottom = iz;
		break;
	case MV_RND_UR:
		rect->left = ix; rect->right = ix + lx;
		rect->top = iz - lz; rect->bottom = iz;
		break;
	case MV_RND_DL:
		rect->left = ix - lx; rect->right = ix;
		rect->top = iz; rect->bottom = iz + lz;
		break;
	case MV_RND_DR:
		rect->left = ix; rect->right = ix + lx;
		rect->top = iz; rect->bottom = iz + lz;
		break;
	case MV_RND_UDL:
		rect->left = ix - lx; rect->right = ix;
		rect->top = iz - lz; rect->bottom = iz + lz;
		break;
	case MV_RND_UDR:
		rect->left = ix; rect->right = ix + lx;
		rect->top = iz - lz; rect->bottom = iz + lz;
		break;
	case MV_RND_ULR:
		rect->left = ix - lx; rect->right = ix + lx;
		rect->top = iz - lz; rect->bottom = iz;
		break;
	case MV_RND_DLR:
		rect->left = ix - lx; rect->right = ix + lx;
		rect->top = iz; rect->bottom = iz + lz;
		break;
	default:
		GF_ASSERT( 0 && "MvRndRectMake()未対応動作コー" );
	}
}

//--------------------------------------------------------------
/**
 * 移動可能範囲チェック　方向指定
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	dir		移動方向
 * @retval	int		TRUE=可能
 */
//--------------------------------------------------------------
static int MvRndRectMoveLimitCheck( FIELD_OBJ_PTR fldobj, int dir )
{
	int gx,gz;
	RECT rect;
	
	MvRndRectMake( fldobj, &rect );
	gx = FieldOBJ_NowPosGX_Get( fldobj ) + FieldOBJ_DirAddValueGX( dir );
	gz = FieldOBJ_NowPosGZ_Get( fldobj ) + FieldOBJ_DirAddValueGZ( dir );
	
	if( rect.left > gx || rect.right < gx ){
		return( FALSE );
	}
	
	if( rect.top > gz || rect.bottom < gz ){
		return( FALSE );
	}
	
	return( TRUE );
}

//==============================================================================
//	MV_UP系　常に指定方向を向く
//==============================================================================
//--------------------------------------------------------------
/**
 * MV_UP系　初期化
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	dir		向く方向
 * @retval	nothing
 */
//--------------------------------------------------------------
static void MvDirWorkInit( FIELD_OBJ_PTR fldobj, int dir )
{
	MV_DIR_WORK *work;
	
	work = FieldOBJ_MoveProcWorkInit( fldobj, MV_DIR_WORK_SIZE );
	work->dir = dir;
	
	FieldOBJ_DrawStatusSet( fldobj, DRAW_STA_STOP );
	FieldOBJ_StatusBitOFF_Move( fldobj );
	FieldOBJ_GPosUpdate( fldobj );
}

//--------------------------------------------------------------
/**
 * MV_UP系　動作
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_MoveDir_Move( FIELD_OBJ_PTR fldobj )
{
	MV_DIR_WORK *work;
	
	work = FieldOBJ_MoveProcWorkGet( fldobj );
	
	switch( work->seq_no ){
	case 0:
		FieldOBJ_DirDispCheckSet( fldobj, work->dir );
		work->seq_no++;
		break;
	case 1:
		break;
	}
}

//--------------------------------------------------------------
/**
 * MV_UP 初期化
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_MoveUp_Init( FIELD_OBJ_PTR fldobj )
{
	MvDirWorkInit( fldobj, DIR_UP );
}

//--------------------------------------------------------------
/**
 * MV_DOWN 初期化
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_MoveDown_Init( FIELD_OBJ_PTR fldobj )
{
	MvDirWorkInit( fldobj, DIR_DOWN );
}

//--------------------------------------------------------------
/**
 * MV_LEFT 初期化
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_MoveLeft_Init( FIELD_OBJ_PTR fldobj )
{
	MvDirWorkInit( fldobj, DIR_LEFT );
}

//--------------------------------------------------------------
/**
 * MV_RIGHT 初期化
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_MoveRight_Init( FIELD_OBJ_PTR fldobj )
{
	MvDirWorkInit( fldobj, DIR_RIGHT );
}

//==============================================================================
//	MV_SPIN系　方向回転
//==============================================================================
//--------------------------------------------------------------
/**
 * MV_SPIN_DIR_WORK初期化
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	dir		DIR_LEFT=左周り、DIR_RIGHT=右周り
 * @retval	nothing
 */
//--------------------------------------------------------------
static void MvSpinDirWorkInit( FIELD_OBJ_PTR fldobj, int dir )
{
	MV_SPIN_DIR_WORK *work;
	
	work = FieldOBJ_MoveProcWorkInit( fldobj, MV_SPIN_DIR_WORK_SIZE );
	work->spin_dir = dir;
	
	FieldOBJ_DrawStatusSet( fldobj, DRAW_STA_STOP );
	FieldOBJ_StatusBitOFF_Move( fldobj );
	FieldOBJ_GPosUpdate( fldobj );
}

//--------------------------------------------------------------
/**
 * MV_SPIN_L　初期化
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_MoveSpinLeft_Init( FIELD_OBJ_PTR fldobj )
{
	MvSpinDirWorkInit( fldobj, DIR_LEFT );
}

//--------------------------------------------------------------
/**
 * MV_SPIN_R　初期化
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_MoveSpinRight_Init( FIELD_OBJ_PTR fldobj )
{
	MvSpinDirWorkInit( fldobj, DIR_RIGHT );
}

//--------------------------------------------------------------
/**
 * MV_SPIN系　動作
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_MoveSpin_Move( FIELD_OBJ_PTR fldobj )
{
	MV_SPIN_DIR_WORK *work;
	
	work = FieldOBJ_MoveProcWorkGet( fldobj );
	while( DATA_MvSpinMoveTbl[work->seq_no](fldobj,work) == TRUE ){};
}

//--------------------------------------------------------------
/**
 * MV_SPIN系　動作　現在方向コマンドセット
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	work	MV_SPIN_DIR_WORK
 * @retval	int		TRUE=再帰
 */
//--------------------------------------------------------------
static int MvSpinMove_DirCmdSet( FIELD_OBJ_PTR fldobj, MV_SPIN_DIR_WORK *work )
{
	int ret = TrJikiDashSearchTbl( fldobj, DIRID_MvDirSpin_DirTbl, DIR_NOT );
	
	if( ret == DIR_NOT ){
		ret = FieldOBJ_DirDispGet( fldobj );
	}
	
	ret = FieldOBJ_AcmdCodeDirChange( ret, AC_DIR_U );
	FieldOBJ_CmdSet( fldobj, ret );
	
	work->seq_no = SEQNO_MV_SPIN_DIR_CMD_ACT;
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * MV_SPIN系　動作　コマンドアクション
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	work	MV_SPIN_DIR_WORK
 * @retval	int		TRUE=再帰
 */
//--------------------------------------------------------------
static int MvSpinMove_CmdAction( FIELD_OBJ_PTR fldobj, MV_SPIN_DIR_WORK *work )
{
	if( FieldOBJ_CmdAction(fldobj) == FALSE ){
		return( FALSE );
	}
	
	work->wait = 0;
	work->seq_no = SEQNO_MV_SPIN_DIR_WAIT;
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * MV_SPIN系　動作　ウェイト
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	work	MV_SPIN_DIR_WORK
 * @retval	int		TRUE=再帰
 */
//--------------------------------------------------------------
static int MvSpinMove_Wait( FIELD_OBJ_PTR fldobj, MV_SPIN_DIR_WORK *work )
{
	if( work->wait ){
		if( TrJikiDashSearchTbl(fldobj,DIRID_MvDirSpin_DirTbl,DIR_NOT) != DIR_NOT ){
			work->seq_no = SEQNO_MV_SPIN_DIR_CMD_SET;
			return( TRUE );
		}
	}
	
	work->wait++;
	
	if( work->wait < MV_SPIN_WAIT_FRAME ){
		return( FALSE );
	}
	
	work->seq_no = SEQNO_MV_SPIN_DIR_NEXT_DIR_SET;
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * MV_SPIN系　動作　次方向セット
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	work	MV_SPIN_DIR_WORK
 * @retval	int		TRUE=再帰
 */
//--------------------------------------------------------------
static int MvSpinMove_NextDirSet( FIELD_OBJ_PTR fldobj, MV_SPIN_DIR_WORK *work )
{
	int i,ret,*tbl;
	int left[5] = { DIR_UP, DIR_LEFT, DIR_DOWN, DIR_RIGHT, DIR_NOT };
	int right[5] = { DIR_UP, DIR_RIGHT, DIR_DOWN, DIR_LEFT, DIR_NOT };
	
	if( work->spin_dir == DIR_LEFT ){
		tbl = left;
	}else{
		tbl = right;
	}
	
	ret = FieldOBJ_DirDispGet( fldobj );
	
	for( i = 0; tbl[i] != DIR_NOT; i++ ){
		if( ret == tbl[i] ){
			break;
		}
	}
	
	GF_ASSERT( tbl[i] != DIR_NOT && "FieldOBJ MV_SPIN初期方向エラー" );
	
	i++;
	
	if( tbl[i] == DIR_NOT ){
		i = 0;
	}
	
	ret = tbl[i];
	
	FieldOBJ_DirDispCheckSet( fldobj, ret );
	
	work->seq_no = SEQNO_MV_SPIN_DIR_CMD_SET;
	return( TRUE );
}

//--------------------------------------------------------------
///	MV_SPIN動作テーブル
//--------------------------------------------------------------
static int (* const DATA_MvSpinMoveTbl[])( FIELD_OBJ_PTR fldobj, MV_SPIN_DIR_WORK *work ) =
{
	MvSpinMove_DirCmdSet,
	MvSpinMove_CmdAction,
	MvSpinMove_Wait,
	MvSpinMove_NextDirSet,
};

//==============================================================================
//	MV_REWAR　右回転<->左回転
//==============================================================================
//--------------------------------------------------------------
/**
 * MV_REWAR 初期化
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_MoveRewar_Init( FIELD_OBJ_PTR fldobj )
{
	MvSpinDirWorkInit( fldobj, DIR_RIGHT );
}

//--------------------------------------------------------------
/**
 * MV_REWAR系　動作
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_MoveRewar_Move( FIELD_OBJ_PTR fldobj )
{
	MV_SPIN_DIR_WORK *work;
	
	work = FieldOBJ_MoveProcWorkGet( fldobj );
	while( DATA_MvRewarMoveTbl[work->seq_no](fldobj,work) == TRUE ){};
}

//--------------------------------------------------------------
/**
 * MV_REWAR　動作　現在方向コマンドセット
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	work	MV_SPIN_DIR_WORK
 * @retval	int		TRUE=再帰
 */
//--------------------------------------------------------------
static int MvRewarMove_DirCmdSet( FIELD_OBJ_PTR fldobj, MV_SPIN_DIR_WORK *work )
{
	int ret = FieldOBJ_DirDispGet( fldobj );
	ret = FieldOBJ_AcmdCodeDirChange( ret, AC_DIR_U );
	FieldOBJ_CmdSet( fldobj, ret );
	
	work->seq_no = SEQNO_MV_REWAR_DIR_CMD_ACT;
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * MV_REWAR　動作　コマンドアクション
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	work	MV_SPIN_DIR_WORK
 * @retval	int		TRUE=再帰
 */
//--------------------------------------------------------------
static int MvRewarMove_CmdAction( FIELD_OBJ_PTR fldobj, MV_SPIN_DIR_WORK *work )
{
	if( FieldOBJ_CmdAction(fldobj) == FALSE ){
		return( FALSE );
	}
	
	work->wait = 0;
	work->seq_no = SEQNO_MV_REWAR_DIR_WAIT;
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * MV_REWAR系　動作　ウェイト
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	work	MV_SPIN_DIR_WORK
 * @retval	int		TRUE=再帰
 */
//--------------------------------------------------------------
static int MvRewarMove_Wait( FIELD_OBJ_PTR fldobj, MV_SPIN_DIR_WORK *work )
{
	work->wait++;
	
	if( work->wait < MV_SPIN_WAIT_FRAME ){
		return( FALSE );
	}
	
	work->seq_no = SEQNO_MV_REWAR_DIR_NEXT_DIR_SET;
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * MV_REWAR　動作　次方向セット
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	work	MV_SPIN_DIR_WORK
 * @retval	int		TRUE=再帰
 */
//--------------------------------------------------------------
static int MvRewarMove_NextDirSet( FIELD_OBJ_PTR fldobj, MV_SPIN_DIR_WORK *work )
{
	int i,ret,*tbl;
	int left[5] = { DIR_UP, DIR_LEFT, DIR_DOWN, DIR_RIGHT, DIR_NOT };
	int right[5] = { DIR_UP, DIR_RIGHT, DIR_DOWN, DIR_LEFT, DIR_NOT };
	
	if( work->spin_dir == DIR_LEFT ){
		tbl = left;
	}else{
		tbl = right;
	}
	
	ret = FieldOBJ_DirDispGet( fldobj );
	
	for( i = 0; tbl[i] != DIR_NOT; i++ ){
		if( ret == tbl[i] ){
			break;
		}
	}
	
	GF_ASSERT( tbl[i] != DIR_NOT && "FieldOBJ MV_REWAR初期方向エラー" );
	
	i++;
	
	if( tbl[i] == DIR_NOT ){
		i = 0;
	}
	
	ret = tbl[i];
	
	FieldOBJ_DirDispCheckSet( fldobj, ret );
	
	{
		int dir = FieldOBJ_DirDispGet( fldobj );
		int sdir = FieldOBJ_DirHeaderGet( fldobj );
		
		if( dir == sdir ){
			work->spin_dir = FieldOBJTool_DirFlip( work->spin_dir );
		}
	}
	
	work->seq_no = SEQNO_MV_REWAR_DIR_CMD_SET;
	return( TRUE );
}

//--------------------------------------------------------------
///	MV_SPIN動作テーブル
//--------------------------------------------------------------
static int (* const DATA_MvRewarMoveTbl[])( FIELD_OBJ_PTR fldobj, MV_SPIN_DIR_WORK *work ) =
{
	MvRewarMove_DirCmdSet,
	MvRewarMove_CmdAction,
	MvRewarMove_Wait,
	MvRewarMove_NextDirSet,
};

//==============================================================================
//	MV_RT2　一方向を往復	
//==============================================================================
//--------------------------------------------------------------
/**
 * MV_RT2 初期化
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_MoveRoute2_Init( FIELD_OBJ_PTR fldobj )
{
	MV_RT2_WORK *work;
	
	work = FieldOBJ_MoveProcWorkInit( fldobj, MV_RT2_WORK_SIZE );
	
	if( MoveSub_KuruKuruCheck(fldobj) == TRUE ){
		MoveSub_KuruKuruInit( fldobj, &work->kurukuru );
	}
}

//--------------------------------------------------------------
/**
 * MV_RT2 動作
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_MoveRoute2_Move( FIELD_OBJ_PTR fldobj )
{
	MV_RT2_WORK *work = FieldOBJ_MoveProcWorkGet( fldobj );
	
	while( DATA_MvRt2MoveTbl[work->seq_no](fldobj,work) == TRUE ){};
}

//--------------------------------------------------------------
/**
 * MV_RT2 動作　方向チェック
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	work	MV_RT2_WORK
 * @retval	int		TRUE=再帰
 */
//--------------------------------------------------------------
static int MvRt2_DirCheck( FIELD_OBJ_PTR fldobj, MV_RT2_WORK *work )
{
	int dir;
	
	dir = FieldOBJ_DirHeaderGet( fldobj );						//ヘッダ指定方向
	
	if( work->turn_flag == TRUE ){
		dir = FieldOBJTool_DirFlip( dir );
	}
	
	FieldOBJ_DirMoveSet( fldobj, dir );
	
	if( MoveSub_KuruKuruCheck(fldobj) == FALSE ){
		FieldOBJ_DirDispCheckSet( fldobj, dir );
	}
	
	work->seq_no = SEQNO_MV_RT2_MOVE_SET;
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * MV_RT2 動作　動作セット
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	work	MV_RT2_WORK
 * @retval	int		TRUE=再帰
 */
//--------------------------------------------------------------
static int MvRt2_MoveSet( FIELD_OBJ_PTR fldobj, MV_RT2_WORK *work )
{
	if( work->turn_flag ){
		int ix,iz,gx,gz;
		
		ix = FieldOBJ_InitPosGX_Get( fldobj );
		iz = FieldOBJ_InitPosGZ_Get( fldobj );
		gx = FieldOBJ_NowPosGX_Get( fldobj );
		gz = FieldOBJ_NowPosGZ_Get( fldobj );
		
		if( ix == gx && iz == gz ){
			int dir = FieldOBJTool_DirFlip( FieldOBJ_DirMoveGet(fldobj) );
			
			FieldOBJ_DirMoveSet( fldobj, dir );
			
			if( MoveSub_KuruKuruCheck(fldobj) == FALSE ){
				FieldOBJ_DirDispCheckSet( fldobj, dir );
			}
			
			work->turn_flag = FALSE;
		}
	}
	
	{
		int dir,ac;
		u32 ret;
		
		dir = FieldOBJ_DirMoveGet( fldobj );
		ret = FieldOBJ_MoveHitCheckDir( fldobj, dir );
		
		if( (ret & FLDOBJ_MOVE_HIT_BIT_LIM) ){
			work->turn_flag = TRUE;
			dir = FieldOBJTool_DirFlip( dir );
			ret = FieldOBJ_MoveHitCheckDir( fldobj, dir );
		}
		
		ac = AC_WALK_U_8F;
		
		if( ret != FLDOBJ_MOVE_HIT_BIT_NON ){
			ac = AC_STAY_WALK_U_8F;
		}
		
		ac = FieldOBJ_AcmdCodeDirChange( dir, ac );
		FieldOBJ_CmdSet( fldobj, ac );
		
		if( MoveSub_KuruKuruCheck(fldobj) == TRUE ){
			MoveSub_KuruKuruSet( fldobj, &work->kurukuru );
		}
	}
	
	FieldOBJ_StatusBitON_Move( fldobj );
	work->seq_no = SEQNO_MV_RT2_MOVE;
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * MV_RT2 動作　動作中
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	work	MV_RT2_WORK
 * @retval	int		TRUE=再帰
 */
//--------------------------------------------------------------
static int MvRt2_Move( FIELD_OBJ_PTR fldobj, MV_RT2_WORK *work )
{
	if( FieldOBJ_CmdAction(fldobj) == TRUE ){
		FieldOBJ_StatusBitOFF_Move( fldobj );
		
		if( MoveSub_KuruKuruCheck(fldobj) == TRUE ){
			MoveSub_KuruKuruEnd( fldobj, &work->kurukuru );
		}
		
		work->seq_no = SEQNO_MV_RT2_DIR_CHECK;
	}
	
	return( FALSE );
}

//--------------------------------------------------------------
///	MV_RT2動作テーブル
//--------------------------------------------------------------
static int (* const DATA_MvRt2MoveTbl[])( FIELD_OBJ_PTR fldobj, MV_RT2_WORK *work ) =
{
	MvRt2_DirCheck,
	MvRt2_MoveSet,
	MvRt2_Move,
};

//==============================================================================
//	MV_RTURLD等　3,4箇所往復
//==============================================================================
//--------------------------------------------------------------
/**
 * MV_RT3_WORK初期化
 * @param	fldobj		FIELD_OBJ_PTR
 * @param	check_no	3点移動で特定分岐とする点
 * @param	check_type	MV_RT3_CHECK_TYPE_X等
 * @param	tbl_id		テーブルID
 * @retval	nothing
 */
//--------------------------------------------------------------
static void MvRt3WorkInit( FIELD_OBJ_PTR fldobj, int check_no, int check_type, int tbl_id )
{
	MV_RT3_WORK *work;
	
	work = FieldOBJ_MoveProcWorkInit( fldobj, MV_RT3_WORK_SIZE );
	work->turn_check_no = check_no;
	work->turn_check_type = check_type;
	work->tbl_id = tbl_id;
	
	if( MoveSub_KuruKuruCheck(fldobj) == TRUE ){
		MoveSub_KuruKuruInit( fldobj, &work->kurukuru );
	}
}

//--------------------------------------------------------------
/**
 * MV_RTURLD 初期化
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_MoveRouteURLD_Init( FIELD_OBJ_PTR fldobj )
{
	MvRt3WorkInit( fldobj, 2, MV_RT3_CHECK_TYPE_X, DIRID_MvRtURLD_DirTbl );
}

//--------------------------------------------------------------
/**
 * MV_RTRLDU 初期化
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_MoveRouteRLDU_Init( FIELD_OBJ_PTR fldobj )
{
	MvRt3WorkInit( fldobj, 2, MV_RT3_CHECK_TYPE_X, DIRID_MvRtRLDU_DirTbl );
}

//--------------------------------------------------------------
/**
 * MV_RTDURL初期化
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_MoveRouteDURL_Init( FIELD_OBJ_PTR fldobj )
{
	MvRt3WorkInit( fldobj, 2, MV_RT3_CHECK_TYPE_Z, DIRID_MvRtDURL_DirTbl );
}

//--------------------------------------------------------------
/**
 * MV_RTLDUR初期化
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_MoveRouteLDUR_Init( FIELD_OBJ_PTR fldobj )
{
	MvRt3WorkInit( fldobj, 2, MV_RT3_CHECK_TYPE_Z, DIRID_MvRtLDUR_DirTbl );
}

//--------------------------------------------------------------
/**
 * MV_RTULRD初期化
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_MoveRouteULRD_Init( FIELD_OBJ_PTR fldobj )
{
	MvRt3WorkInit( fldobj, 2, MV_RT3_CHECK_TYPE_X, DIRID_MvRtULRD_DirTbl );
}

//--------------------------------------------------------------
/**
 * MV_RTLRDU初期化
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_MoveRouteLRDU_Init( FIELD_OBJ_PTR fldobj )
{
	MvRt3WorkInit( fldobj, 2, MV_RT3_CHECK_TYPE_X, DIRID_MvRtLRDU_DirTbl );
}

//--------------------------------------------------------------
/**
 * MV_RTDULR初期化
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_MoveRouteDULR_Init( FIELD_OBJ_PTR fldobj )
{
	MvRt3WorkInit( fldobj, 2, MV_RT3_CHECK_TYPE_Z, DIRID_MvRtDULR_DirTbl );
}

//--------------------------------------------------------------
/**
 * MV_RTRDUL初期化
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_MoveRouteRDUL_Init( FIELD_OBJ_PTR fldobj )
{
	MvRt3WorkInit( fldobj, 2, MV_RT3_CHECK_TYPE_Z, DIRID_MvRtRDUL_DirTbl );
}

//--------------------------------------------------------------
/**
 * MV_RTLUDR初期化
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_MoveRouteLUDR_Init( FIELD_OBJ_PTR fldobj )
{
	MvRt3WorkInit( fldobj, 2, MV_RT3_CHECK_TYPE_Z, DIRID_MvRtLUDR_DirTbl );
}

//--------------------------------------------------------------
/**
 * MV_RTUDRL初期化
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_MoveRouteUDRL_Init( FIELD_OBJ_PTR fldobj )
{
	MvRt3WorkInit( fldobj, 2, MV_RT3_CHECK_TYPE_Z, DIRID_MvRtUDRL_DirTbl );
}

//--------------------------------------------------------------
/**
 * MV_RTRLUD初期化
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_MoveRouteRLUD_Init( FIELD_OBJ_PTR fldobj )
{
	MvRt3WorkInit( fldobj, 2, MV_RT3_CHECK_TYPE_X, DIRID_MvRtRLUD_DirTbl );
}

//--------------------------------------------------------------
/**
 * MV_RTDRLU初期化
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_MoveRouteDRLU_Init( FIELD_OBJ_PTR fldobj )
{
	MvRt3WorkInit( fldobj, 2, MV_RT3_CHECK_TYPE_X, DIRID_MvRtDRLU_DirTbl );
}

//--------------------------------------------------------------
/**
 * MV_RTRUDL初期化
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_MoveRouteRUDL_Init( FIELD_OBJ_PTR fldobj )
{
	MvRt3WorkInit( fldobj, 2, MV_RT3_CHECK_TYPE_Z, DIRID_MvRtRUDL_DirTbl );
}

//--------------------------------------------------------------
/**
 * MV_RTUDLR初期化
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_MoveRouteUDLR_Init( FIELD_OBJ_PTR fldobj )
{
	MvRt3WorkInit( fldobj, 2, MV_RT3_CHECK_TYPE_Z, DIRID_MvRtUDLR_DirTbl );
}

//--------------------------------------------------------------
/**
 * MV_RTLRUD初期化
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_MoveRouteLRUD_Init( FIELD_OBJ_PTR fldobj )
{
	MvRt3WorkInit( fldobj, 2, MV_RT3_CHECK_TYPE_X, DIRID_MvRtLRUD_DirTbl );
}

//--------------------------------------------------------------
/**
 * MV_RTDLRU初期化
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_MoveRouteDLRU_Init( FIELD_OBJ_PTR fldobj )
{
	MvRt3WorkInit( fldobj, 2, MV_RT3_CHECK_TYPE_X, DIRID_MvRtDLRU_DirTbl );
}

//--------------------------------------------------------------
/**
 * MV_RTUL初期化
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_MoveRouteUL_Init( FIELD_OBJ_PTR fldobj )
{
	MvRt3WorkInit( fldobj, 2, MV_RT3_CHECK_TYPE_Z, DIRID_MvRtUL_DirTbl );
}

//--------------------------------------------------------------
/**
 * MV_RTDR初期化
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_MoveRouteDR_Init( FIELD_OBJ_PTR fldobj )
{
	MvRt3WorkInit( fldobj, 2, MV_RT3_CHECK_TYPE_Z, DIRID_MvRtDR_DirTbl );
}

//--------------------------------------------------------------
/**
 * MV_RTLD初期化
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_MoveRouteLD_Init( FIELD_OBJ_PTR fldobj )
{
	MvRt3WorkInit( fldobj, 2, MV_RT3_CHECK_TYPE_X, DIRID_MvRtLD_DirTbl );
}

//--------------------------------------------------------------
/**
 * MV_RTRU初期化
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_MoveRouteRU_Init( FIELD_OBJ_PTR fldobj )
{
	MvRt3WorkInit( fldobj, 2, MV_RT3_CHECK_TYPE_X, DIRID_MvRtRU_DirTbl );
}

//--------------------------------------------------------------
/**
 * MV_RTUR初期化
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_MoveRouteUR_Init( FIELD_OBJ_PTR fldobj )
{
	MvRt3WorkInit( fldobj, 2, MV_RT3_CHECK_TYPE_Z, DIRID_MvRtUR_DirTbl );
}

//--------------------------------------------------------------
/**
 * MV_RTDL初期化
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_MoveRouteDL_Init( FIELD_OBJ_PTR fldobj )
{
	MvRt3WorkInit( fldobj, 2, MV_RT3_CHECK_TYPE_Z, DIRID_MvRtDL_DirTbl );
}

//--------------------------------------------------------------
/**
 * MV_RTLU初期化
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_MoveRouteLU_Init( FIELD_OBJ_PTR fldobj )
{
	MvRt3WorkInit( fldobj, 2, MV_RT3_CHECK_TYPE_X, DIRID_MvRtLU_DirTbl );
}

//--------------------------------------------------------------
/**
 * MV_RTRD初期化
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_MoveRouteRD_Init( FIELD_OBJ_PTR fldobj )
{
	MvRt3WorkInit( fldobj, 2, MV_RT3_CHECK_TYPE_X, DIRID_MvRtRD_DirTbl );
}

//--------------------------------------------------------------
/**
 * MV_RT3動作　
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_MoveRoute3_Move( FIELD_OBJ_PTR fldobj )
{
	MV_RT3_WORK *work;
	
	work = FieldOBJ_MoveProcWorkGet( fldobj );
	while( DATA_MvRt3MoveTbl[work->seq_no](fldobj,work) == TRUE ){};
}

//--------------------------------------------------------------
/**
 * MV_RT3動作　移動方向セット
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	work	MV_RT3_WORK
 * @retval	int		TRUE=再帰
 */
//--------------------------------------------------------------
static int MvRt3Move_MoveDirSet( FIELD_OBJ_PTR fldobj, MV_RT3_WORK *work )
{
	if( work->turn_no == work->turn_check_no  ){
		if( work->turn_check_type == MV_RT3_CHECK_TYPE_X ){
			int ix = FieldOBJ_InitPosGX_Get( fldobj );
			int gx = FieldOBJ_NowPosGX_Get( fldobj );
			
			if( ix == gx ){
				work->turn_no++;
			}
		}else{
			int iz = FieldOBJ_InitPosGZ_Get( fldobj );
			int gz = FieldOBJ_NowPosGZ_Get( fldobj );
			
			if( iz == gz ){
				work->turn_no++;
			}
		}
	}
	
	if( work->turn_no == MV_RT3_TURN_END_NO ){
		int ix = FieldOBJ_InitPosGX_Get( fldobj );
		int iz = FieldOBJ_InitPosGZ_Get( fldobj );
		int gx = FieldOBJ_NowPosGX_Get( fldobj );
		int gz = FieldOBJ_NowPosGZ_Get( fldobj );
		
		if( ix == gx && iz == gz ){
			work->turn_no = 0;
		}
	}
	
	{
		const int *tbl;
		int dir,ac;
		u32 ret;
		
		tbl = MoveDirTblIDSearch( work->tbl_id );
		dir = tbl[work->turn_no];
		
		FieldOBJ_DirMoveSet( fldobj, dir );
		
		if( MoveSub_KuruKuruCheck(fldobj) == FALSE ){
			FieldOBJ_DirDispCheckSet( fldobj, dir );
		}
		
		ret = FieldOBJ_MoveHitCheckDir( fldobj, dir );
		
		if( (ret & FLDOBJ_MOVE_HIT_BIT_LIM) ){
			work->turn_no++;
			dir = tbl[work->turn_no];
			
			FieldOBJ_DirMoveSet( fldobj, dir );
			
			if( MoveSub_KuruKuruCheck(fldobj) == FALSE ){
				FieldOBJ_DirDispCheckSet( fldobj, dir );
			}
			
			ret = FieldOBJ_MoveHitCheckDir( fldobj, dir );
		}
		
		ac = AC_WALK_U_8F;
		
		if( (ret != FLDOBJ_MOVE_HIT_BIT_NON) ){
			ac = AC_STAY_WALK_U_8F;
		}
		
		ac = FieldOBJ_AcmdCodeDirChange( dir, ac );
		FieldOBJ_CmdSet( fldobj, ac );
		
		if( MoveSub_KuruKuruCheck(fldobj) == TRUE ){
			MoveSub_KuruKuruSet( fldobj, &work->kurukuru );
		}
	}
	
	FieldOBJ_StatusBitON_Move( fldobj );
	work->seq_no = SEQNO_MV_RT3_MOVE;
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * MV_RT3動作　移動
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	work	MV_RT3_WORK
 * @retval	int		TRUE=再帰
 */
//--------------------------------------------------------------
static int MvRt3Move_MoveDir( FIELD_OBJ_PTR fldobj, MV_RT3_WORK *work )
{
	if( FieldOBJ_CmdAction(fldobj) == TRUE ){
		FieldOBJ_StatusBitOFF_Move( fldobj );
		
		if( MoveSub_KuruKuruCheck(fldobj) == TRUE ){
			MoveSub_KuruKuruEnd( fldobj, &work->kurukuru );
		}
		
		work->seq_no = SEQNO_MV_RT3_MOVE_DIR_SET;
	}
	
	return( FALSE );
}

//--------------------------------------------------------------
///	MV_RT3動作テーブル
//--------------------------------------------------------------
static int (* const DATA_MvRt3MoveTbl[])( FIELD_OBJ_PTR fldobj, MV_RT3_WORK *work ) =
{
	MvRt3Move_MoveDirSet,
	MvRt3Move_MoveDir,
};

//==============================================================================
//	パーツ
//==============================================================================
//--------------------------------------------------------------
/**
 * 方向テーブル要素数取得
 * @param	tbl		データテーブル。終端にend
 * @param	end		テーブル終端とする値
 * @retval	int		tbl要素数
 */
//--------------------------------------------------------------
static int TblNumGet( const int *tbl, int end )
{
	int i=0; while(tbl[i]!=end){i++;} GF_ASSERT(i&&"TblNumGet()要素数0"); return(i);
}

//--------------------------------------------------------------
/**
 * テーブルデータからランダムで値取得
 * @param	tbl		データテーブル。終端にend
 * @param	end		テーブル終端とする値
 * @retval	int		tbl内部の値
 */
//--------------------------------------------------------------
static int TblRndGet( const int *tbl, int end )
{
	return( tbl[gf_rand()%TblNumGet(tbl,end)] );
}

//--------------------------------------------------------------
/**
 * 方向IDからテーブルデータを取得しランダムで値取得
 * @param	tbl		データテーブル。終端にend
 * @param	end		テーブル終端とする値
 * @retval	int		tbl内部の値
 */
//--------------------------------------------------------------
static int TblIDRndGet( int id, int end )
{
	const int *tbl = MoveDirTblIDSearch( id );
	return( tbl[gf_rand()%TblNumGet(tbl,end)] );
}

//--------------------------------------------------------------
/**
 * DATA_MoveDirTbl検索
 * @param	id		検索ID
 * @retval	int		ヒットしたテーブル*
 */
//--------------------------------------------------------------
static const int * MoveDirTblIDSearch( int id )
{
	const DIR_TBL *tbl = DATA_MoveDirTbl;
	
	while( tbl->id != DIRID_END ){
		if( tbl->id == id ){ return( tbl->tbl ); }
		tbl++;
	}
	
	GF_ASSERT( 0 && "MoveDirTblIDSearch()ID異常" );
	return( NULL );
}

//--------------------------------------------------------------
/**
 * 自機が指定範囲内でダッシュしているか
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	int		DIR_NOT=範囲内、方向切り替え型では無い。その他DIR_UP等
 */
//--------------------------------------------------------------
static int TrJikiDashSearch( FIELD_OBJ_PTR fldobj )
{
	int ret = FieldOBJ_EventTypeGet( fldobj );
	
#ifndef DEBUG_SEARCH	
	if( ret != EV_TYPE_TRAINER && ret != EV_TYPE_TRAINER_EYEALL ){
		return( DIR_NOT );
	}
#endif
	
	{
		FIELDSYS_WORK *fsys = FieldOBJ_FieldSysWorkGet( fldobj );
		PLAYER_STATE_PTR jiki = Player_FieldSysWorkPlayerGet( fsys );
		
#ifndef DEBUG_SEARCH		
		if( Player_AcmdCodeDashCheck(jiki) == FALSE ){
			return( DIR_NOT );
		}
#endif		
		{
			int code,i = 0;
			ret = FieldOBJ_MoveCodeGet( fldobj );
			
			do{
				code = JikiDashSensorMoveCodeTbl[i++];
				if( code == ret ){ break; }
			}while( code != MV_CODE_NOT );
			
			if( ret != code ){
				return( DIR_NOT );
			}
		}
		
		{
			CONST_FIELD_OBJ_PTR jikiobj = Player_FieldOBJGet( jiki );
			int jy = FieldOBJ_HeightGridGet( jikiobj );
			int y = FieldOBJ_HeightGridGet( fldobj );
			
			if( jy != y ){
				return( DIR_NOT );
			}
		}
		
		{
			int jx = Player_NowGPosXGet( jiki );
			int jz = Player_NowGPosZGet( jiki );
#ifndef DEBUG_SEARCH
			int range = FieldOBJ_ParamGet( fldobj, FLDOBJ_PARAM_0 );
#else
			int range = 4;
#endif
			int x = FieldOBJ_NowPosGX_Get( fldobj );
			int z = FieldOBJ_NowPosGZ_Get( fldobj );
			int sx = x - range;
			int ex = x + range;
			int sz = z - range;
			int ez = z + range;
			
			if( sz <= jz && ez >= jz ){
				if( sx <= jx && ex >= jx ){
					return( FieldOBJTool_DirRange(x,z,jx,jz) );
				}
			}
		}
	}
	
	return( DIR_NOT );
}

//--------------------------------------------------------------
/**
 * 自機が指定範囲内でダッシュしていればその方向を返す。方向テーブルアリ
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	int		DIR_NOT=範囲内、方向切り替え型では無い。その他DIR_UP等
 */
//--------------------------------------------------------------
static int TrJikiDashSearchTbl( FIELD_OBJ_PTR fldobj, int id, int end )
{
	const int *tbl = MoveDirTblIDSearch( id );
	int num = TblNumGet( tbl, end );
	
	if( num == 1 ){			//一方向のみ
		return( DIR_NOT );
	}
	
	{
		int dir;
		dir = TrJikiDashSearch( fldobj );
		
		if( dir == DIR_NOT ){
			return( dir );
		}
		
		{
			int i = 0;
			
			do{ if(tbl[i]==dir){return(dir);} i++; }while( i < num );
			
			{
				int dirx = DIR_NOT,dirz = DIR_NOT;
				int x = FieldOBJ_NowPosGX_Get( fldobj );
				int z = FieldOBJ_NowPosGZ_Get( fldobj );
				FIELDSYS_WORK *fsys = FieldOBJ_FieldSysWorkGet( fldobj );
				PLAYER_STATE_PTR jiki = Player_FieldSysWorkPlayerGet( fsys );
				int jx = Player_NowGPosXGet( jiki );
				int jz = Player_NowGPosZGet( jiki );
				
				if( x > jx ){ dirx = DIR_LEFT; }
				else if( x < jx ){ dirx = DIR_RIGHT; }
				
				if( z > jz ){ dirz = DIR_UP; }
				else if( z < jz ){ dirz = DIR_DOWN; }
				
				i = 0;
				
				if( dirx == DIR_NOT ){
					do{ if(tbl[i]==dirz){return(dirz);} i++; }while( i < num );
				}else if( dirz == DIR_NOT ){ 
					do{ if(tbl[i]==dirx){return(dirx);} i++; }while( i < num );
				}else{
					do{ if(tbl[i]==dirx){return(dirx);}
						if(tbl[i]==dirz){return(dirz);} i++; }while( i < num );
				}
			}	
		}
	}
	
	return( DIR_NOT );
}

//==============================================================================
//	ルート型　クルクル移動パーツ
//==============================================================================
//--------------------------------------------------------------
///	クルクルテーブル
//--------------------------------------------------------------
static const int DATA_KuruKuruTbl[RT_KURU2_MAX][RT_KURU2_DIR_MAX] =
{
	{DIR_UP,DIR_LEFT,DIR_DOWN,DIR_RIGHT},
	{DIR_UP,DIR_RIGHT,DIR_DOWN,DIR_LEFT},
};

//--------------------------------------------------------------
/**
 * クルクルタイプチェック
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	int		TRUE=クルクル回れ
 */
//--------------------------------------------------------------
static int MoveSub_KuruKuruCheck( FIELD_OBJ_PTR fldobj )
{
	int type = FieldOBJ_EventTypeGet( fldobj );
	
	if( type == EV_TYPE_TRAINER_SPIN_MOVE_L	||
		type == EV_TYPE_TRAINER_SPIN_MOVE_R	){
		return( TRUE );
	}
	
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * くるくるタイプ初期化
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	work	RT_KURUKURU_WORK *
 * @retval	nothing
 */
//--------------------------------------------------------------
static void MoveSub_KuruKuruInit( FIELD_OBJ_PTR fldobj, RT_KURUKURU_WORK *work )
{
	if( FieldOBJ_EventTypeGet(fldobj) == EV_TYPE_TRAINER_SPIN_MOVE_L ){
		work->spin_type = RT_KURU2_L;
	}else{
		work->spin_type = RT_KURU2_R;
	}
}

//--------------------------------------------------------------
/**
 * くるくるタイプ方向セット。
 * 注意：方向が固定される
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	work	RT_KURUKURU_WORK *
 * @retval	nothing
 */
//--------------------------------------------------------------
static void MoveSub_KuruKuruSet( FIELD_OBJ_PTR fldobj, RT_KURUKURU_WORK *work )
{
	int i,dir = FieldOBJ_DirDispGet( fldobj );
	
#if 0	
	{
		switch( dir ){
		case DIR_UP: OS_Printf( "くるくる移動 0 方向は上　" ); break;
		case DIR_DOWN: OS_Printf( "くるくる移動 0 方向は下　" ); break;
		case DIR_LEFT: OS_Printf( "くるくる移動 0 方向は左　" ); break;
		case DIR_RIGHT: OS_Printf( "くるくる移動 0 方向は右　" ); break;
		}
	}
#endif
	
	for( i = 0; (i < RT_KURU2_DIR_MAX && dir != DATA_KuruKuruTbl[work->spin_type][i]); i++ ){}
	GF_ASSERT( i < RT_KURU2_DIR_MAX && "MoveSub_KuruKuruInit()方向異常" );
	
	work->origin_dir = dir;
	i = (i + 1) % RT_KURU2_DIR_MAX;								//+1=1つ先
	dir = DATA_KuruKuruTbl[work->spin_type][i];
	
	if( FieldOBJ_StatusBit_Check(fldobj,FLDOBJ_STA_BIT_PAUSE_DIR) ){
		work->dir_pause = TRUE;
	}else{
		work->dir_pause = FALSE;
	}
	
	FieldOBJ_DirDispCheckSet( fldobj, dir );
	FieldOBJ_StatusBit_ON( fldobj, FLDOBJ_STA_BIT_PAUSE_DIR );
#if 0	
	{
		switch( dir ){
		case DIR_UP: OS_Printf( "1方向は上\n" ); break;
		case DIR_DOWN: OS_Printf( "1方向は下\n" ); break;
		case DIR_LEFT: OS_Printf( "1方向は左\n" ); break;
		case DIR_RIGHT: OS_Printf(  " 1方向は右\n" ); break;
		}
	}
#endif
}

//--------------------------------------------------------------
/**
 * くるくるタイプ方向終了
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	work	RT_KURUKURU_WORK *
 * @retval	nothing
 */
//--------------------------------------------------------------
static void MoveSub_KuruKuruEnd( FIELD_OBJ_PTR fldobj, RT_KURUKURU_WORK *work )
{
	if( work->dir_pause == FALSE ){
		FieldOBJ_StatusBit_OFF( fldobj, FLDOBJ_STA_BIT_PAUSE_DIR );
	}
}

//==============================================================================
//	data
//==============================================================================
//--------------------------------------------------------------
///	DIR_RND ウェイトテーブル
//--------------------------------------------------------------
static const int DATA_MvDirRndWaitTbl[] =
{ 16, 32, 48, 64, WAIT_END };

//--------------------------------------------------------------
///	DIR_RND 方向テーブル
//--------------------------------------------------------------
static const int DATA_MvDirRndDirTbl[] =
{ DIR_UP, DIR_DOWN, DIR_LEFT, DIR_RIGHT, DIR_NOT };

//--------------------------------------------------------------
/// RND_UL 方向テーブル
//--------------------------------------------------------------
static const int DATA_MvDirRndDirTbl_UL[] =
{ DIR_UP, DIR_LEFT, DIR_NOT };

//--------------------------------------------------------------
/// RND_UR 方向テーブル
//--------------------------------------------------------------
static const int DATA_MvDirRndDirTbl_UR[] =
{ DIR_UP, DIR_RIGHT, DIR_NOT };

//--------------------------------------------------------------
/// RND_DL 方向テーブル
//--------------------------------------------------------------
static const int DATA_MvDirRndDirTbl_DL[] =
{ DIR_DOWN, DIR_LEFT, DIR_NOT };

//--------------------------------------------------------------
/// RND_DR 方向テーブル
//--------------------------------------------------------------
static const int DATA_MvDirRndDirTbl_DR[] =
{ DIR_DOWN, DIR_RIGHT, DIR_NOT };

//--------------------------------------------------------------
/// RND_UDL 方向テーブル
//--------------------------------------------------------------
static const int DATA_MvDirRndDirTbl_UDL[] =
{ DIR_UP, DIR_DOWN, DIR_LEFT, DIR_NOT };

//--------------------------------------------------------------
/// RND_UDR 方向テーブル
//--------------------------------------------------------------
static const int DATA_MvDirRndDirTbl_UDR[] =
{ DIR_UP, DIR_DOWN, DIR_RIGHT, DIR_NOT };

//--------------------------------------------------------------
/// RND_ULR 方向テーブル
//--------------------------------------------------------------
static const int DATA_MvDirRndDirTbl_ULR[] =
{ DIR_UP, DIR_LEFT, DIR_RIGHT, DIR_NOT };

//--------------------------------------------------------------
/// RND_DLR 方向テーブル
//--------------------------------------------------------------
static const int DATA_MvDirRndDirTbl_DLR[] =
{ DIR_DOWN, DIR_LEFT, DIR_RIGHT, DIR_NOT };

//--------------------------------------------------------------
/// RND_UD 方向テーブル
//--------------------------------------------------------------
static const int DATA_MvDirRndDirTbl_UD[] =
{ DIR_UP, DIR_DOWN, DIR_NOT };

//--------------------------------------------------------------
/// RND_LR 方向テーブル
//--------------------------------------------------------------
static const int DATA_MvDirRndDirTbl_LR[] =
{ DIR_LEFT, DIR_RIGHT, DIR_NOT };

//--------------------------------------------------------------
///	MV_RND 移動可能方向
//--------------------------------------------------------------
static const int DATA_MV_RND_DirTbl[] =
{ DIR_UP, DIR_DOWN, DIR_LEFT, DIR_RIGHT, DIR_NOT };

//--------------------------------------------------------------
///	MV_RND_V 移動可能方向
//--------------------------------------------------------------
static const int DATA_MV_RND_V_DirTbl[] =
{ DIR_UP, DIR_DOWN, DIR_NOT };

//--------------------------------------------------------------
///	MV_RND_H 移動可能方向
//--------------------------------------------------------------
static const int DATA_MV_RND_H_DirTbl[] =
{ DIR_LEFT, DIR_RIGHT, DIR_NOT };

//--------------------------------------------------------------
///	MV_RTURLD方向テーブル
//--------------------------------------------------------------
static const int DATA_MvRtURLD_DirTbl[] = {DIR_UP,DIR_RIGHT,DIR_LEFT,DIR_DOWN};

//--------------------------------------------------------------
///	MV_RTRLDU方向テーブル
//--------------------------------------------------------------
static const int DATA_MvRtRLDU_DirTbl[] = {DIR_RIGHT,DIR_LEFT,DIR_DOWN,DIR_UP};

//--------------------------------------------------------------
///	MV_RTDURL方向テーブル
//--------------------------------------------------------------
static const int DATA_MvRtDURL_DirTbl[] = {DIR_DOWN,DIR_UP,DIR_RIGHT,DIR_LEFT};

//--------------------------------------------------------------
///	MV_RTLDUR方向テーブル
//--------------------------------------------------------------
static const int DATA_MvRtLDUR_DirTbl[] = {DIR_LEFT,DIR_DOWN,DIR_UP,DIR_RIGHT};

//--------------------------------------------------------------
///	MV_RTULRD方向テーブル
//--------------------------------------------------------------
static const int DATA_MvRtULRD_DirTbl[] = {DIR_LEFT,DIR_RIGHT,DIR_DOWN,DIR_UP};

//--------------------------------------------------------------
///	MV_RTLRDU方向テーブル
//--------------------------------------------------------------
static const int DATA_MvRtLRDU_DirTbl[] = {DIR_LEFT,DIR_RIGHT,DIR_DOWN,DIR_UP};

//--------------------------------------------------------------
///	MV_RTDULR方向テーブル
//--------------------------------------------------------------
static const int DATA_MvRtDULR_DirTbl[] = {DIR_DOWN,DIR_UP,DIR_LEFT,DIR_RIGHT};

//--------------------------------------------------------------
///	MV_RTRDUL方向テーブル
//--------------------------------------------------------------
static const int DATA_MvRtRDUL_DirTbl[] = {DIR_RIGHT,DIR_DOWN,DIR_UP,DIR_LEFT};

//--------------------------------------------------------------
///	MV_RTLUDR方向テーブル
//--------------------------------------------------------------
static const int DATA_MvRtLUDR_DirTbl[] = {DIR_LEFT,DIR_UP,DIR_DOWN,DIR_RIGHT};

//--------------------------------------------------------------
///	MV_RTUDRL方向テーブル
//--------------------------------------------------------------
static const int DATA_MvRtUDRL_DirTbl[] = {DIR_UP,DIR_DOWN,DIR_RIGHT,DIR_LEFT};

//--------------------------------------------------------------
///	MV_RTRLUD方向テーブル
//--------------------------------------------------------------
static const int DATA_MvRtRLUD_DirTbl[] = {DIR_RIGHT,DIR_LEFT,DIR_UP,DIR_DOWN};

//--------------------------------------------------------------
///	MV_RTDRLU方向テーブル
//--------------------------------------------------------------
static const int DATA_MvRtDRLU_DirTbl[] = {DIR_DOWN,DIR_RIGHT,DIR_LEFT,DIR_UP};

//--------------------------------------------------------------
///	MV_RTRUDL方向テーブル
//--------------------------------------------------------------
static const int DATA_MvRtRUDL_DirTbl[] = {DIR_RIGHT,DIR_UP,DIR_DOWN,DIR_LEFT};

//--------------------------------------------------------------
///	MV_RTUDLR方向テーブル
//--------------------------------------------------------------
static const int DATA_MvRtUDLR_DirTbl[] = {DIR_UP,DIR_DOWN,DIR_LEFT,DIR_RIGHT};

//--------------------------------------------------------------
///	MV_RTLRUD方向テーブル
//--------------------------------------------------------------
static const int DATA_MvRtLRUD_DirTbl[] = {DIR_LEFT,DIR_RIGHT,DIR_UP,DIR_DOWN};

//--------------------------------------------------------------
///	MV_RTDLRU方向テーブル
//--------------------------------------------------------------
static const int DATA_MvRtDLRU_DirTbl[] = {DIR_DOWN,DIR_LEFT,DIR_RIGHT,DIR_UP};

//--------------------------------------------------------------
///	MV_RTUL方向テーブル
//--------------------------------------------------------------
static const int DATA_MvRtUL_DirTbl[] = {DIR_UP,DIR_LEFT,DIR_DOWN,DIR_RIGHT};

//--------------------------------------------------------------
///	MV_RTDR方向テーブル
//--------------------------------------------------------------
static const int DATA_MvRtDR_DirTbl[] = {DIR_DOWN,DIR_RIGHT,DIR_UP,DIR_LEFT};

//--------------------------------------------------------------
///	MV_RTLD方向テーブル
//--------------------------------------------------------------
static const int DATA_MvRtLD_DirTbl[] = {DIR_LEFT,DIR_DOWN,DIR_RIGHT,DIR_UP};

//--------------------------------------------------------------
///	MV_RTRU方向テーブル
//--------------------------------------------------------------
static const int DATA_MvRtRU_DirTbl[] = {DIR_RIGHT,DIR_UP,DIR_LEFT,DIR_DOWN};

//--------------------------------------------------------------
///	MV_RTUR方向テーブル
//--------------------------------------------------------------
static const int DATA_MvRtUR_DirTbl[] = {DIR_UP,DIR_RIGHT,DIR_DOWN,DIR_LEFT};

//--------------------------------------------------------------
///	MV_RTDL方向テーブル
//--------------------------------------------------------------
static const int DATA_MvRtDL_DirTbl[] = {DIR_DOWN,DIR_LEFT,DIR_UP,DIR_RIGHT};

//--------------------------------------------------------------
///	MV_RTLU方向テーブル
//--------------------------------------------------------------
static const int DATA_MvRtLU_DirTbl[] = {DIR_LEFT,DIR_UP,DIR_RIGHT,DIR_DOWN};

//--------------------------------------------------------------
///	MV_RTRD方向テーブル
//--------------------------------------------------------------
static const int DATA_MvRtRD_DirTbl[] = {DIR_RIGHT,DIR_DOWN,DIR_LEFT,DIR_UP};

//--------------------------------------------------------------
///	MV_SPIN系方向テーブル
//--------------------------------------------------------------
static const int DATA_MvDirSpin_DirTbl[] = {DIR_UP,DIR_DOWN,DIR_LEFT,DIR_RIGHT,DIR_NOT};

//--------------------------------------------------------------
///	テーブルデータ
//--------------------------------------------------------------
static const DIR_TBL DATA_MoveDirTbl[DIRID_MAX] =
{
	{DIRID_MvDirRndDirTbl,DATA_MvDirRndDirTbl},
	{DIRID_MvDirRndDirTbl_UL,DATA_MvDirRndDirTbl_UL},
	{DIRID_MvDirRndDirTbl_UR,DATA_MvDirRndDirTbl_UR},
	{DIRID_MvDirRndDirTbl_DL,DATA_MvDirRndDirTbl_DL},
	{DIRID_MvDirRndDirTbl_DR,DATA_MvDirRndDirTbl_DR},
	{DIRID_MvDirRndDirTbl_UDL,DATA_MvDirRndDirTbl_UDL},
	{DIRID_MvDirRndDirTbl_UDR,DATA_MvDirRndDirTbl_UDR},
	{DIRID_MvDirRndDirTbl_ULR,DATA_MvDirRndDirTbl_ULR},
	{DIRID_MvDirRndDirTbl_DLR,DATA_MvDirRndDirTbl_DLR},
	{DIRID_MvDirRndDirTbl_UD,DATA_MvDirRndDirTbl_UD},
	{DIRID_MvDirRndDirTbl_LR,DATA_MvDirRndDirTbl_LR},
	{DIRID_MV_RND_DirTbl,DATA_MV_RND_DirTbl},
	{DIRID_MV_RND_V_DirTbl,DATA_MV_RND_V_DirTbl},
	{DIRID_MV_RND_H_DirTbl,DATA_MV_RND_H_DirTbl},
	{DIRID_MvRtURLD_DirTbl,DATA_MvRtURLD_DirTbl},
	{DIRID_MvRtRLDU_DirTbl,DATA_MvRtRLDU_DirTbl},
	{DIRID_MvRtDURL_DirTbl,DATA_MvRtDURL_DirTbl},
	{DIRID_MvRtLDUR_DirTbl,DATA_MvRtLDUR_DirTbl},
	{DIRID_MvRtULRD_DirTbl,DATA_MvRtULRD_DirTbl},
	{DIRID_MvRtLRDU_DirTbl,DATA_MvRtLRDU_DirTbl},
	{DIRID_MvRtDULR_DirTbl,DATA_MvRtDULR_DirTbl},
	{DIRID_MvRtRDUL_DirTbl,DATA_MvRtRDUL_DirTbl},
	{DIRID_MvRtLUDR_DirTbl,DATA_MvRtLUDR_DirTbl},
	{DIRID_MvRtUDRL_DirTbl,DATA_MvRtUDRL_DirTbl},
	{DIRID_MvRtRLUD_DirTbl,DATA_MvRtRLUD_DirTbl},
	{DIRID_MvRtDRLU_DirTbl,DATA_MvRtDRLU_DirTbl},
	{DIRID_MvRtRUDL_DirTbl,DATA_MvRtRUDL_DirTbl},
	{DIRID_MvRtUDLR_DirTbl,DATA_MvRtUDLR_DirTbl},
	{DIRID_MvRtLRUD_DirTbl,DATA_MvRtLRUD_DirTbl},
	{DIRID_MvRtDLRU_DirTbl,DATA_MvRtDLRU_DirTbl},
	{DIRID_MvRtUL_DirTbl,DATA_MvRtUL_DirTbl},
	{DIRID_MvRtDR_DirTbl,DATA_MvRtDR_DirTbl},
	{DIRID_MvRtLD_DirTbl,DATA_MvRtLD_DirTbl},
	{DIRID_MvRtRU_DirTbl,DATA_MvRtRU_DirTbl},
	{DIRID_MvRtUR_DirTbl,DATA_MvRtUR_DirTbl},
	{DIRID_MvRtDL_DirTbl,DATA_MvRtDL_DirTbl},
	{DIRID_MvRtLU_DirTbl,DATA_MvRtLU_DirTbl},
	{DIRID_MvRtRD_DirTbl,DATA_MvRtRD_DirTbl},
	{DIRID_MvDirSpin_DirTbl,DATA_MvDirSpin_DirTbl},
	{DIRID_END,NULL},
};

//--------------------------------------------------------------
///	自機ダッシュ感知動作コード
//--------------------------------------------------------------
static const int JikiDashSensorMoveCodeTbl[] =
{
	MV_DIR_RND,
	MV_RND_UL,MV_RND_UR,
	MV_RND_DL,MV_RND_DR,MV_RND_UDL,MV_RND_UDR,MV_RND_ULR,MV_RND_DLR,
	MV_RND_UD,MV_RND_LR,
	MV_SPIN_L,MV_SPIN_R,
	MV_CODE_NOT
};
	
