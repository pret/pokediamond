//******************************************************************************
/**
 *
 * @file	fieldobj_movedata.c
 * @brief	フィールドOBJ動作
 * @author	kagaya
 * @data	05.07.20
 *
 */
//******************************************************************************
#include "common.h"
#include "fieldsys.h"
#include "fieldobj.h"

//==============================================================================
//	extern　動作関数
//==============================================================================

//==============================================================================
//	extern	アニメーションコマンド
//==============================================================================
//--------------------------------------------------------------
//	AC_DIR_U,D,L,R
//--------------------------------------------------------------
extern int (* const DATA_AC_DirU_Tbl[])( FIELD_OBJ_PTR  );
extern int (* const DATA_AC_DirD_Tbl[])( FIELD_OBJ_PTR  );
extern int (* const DATA_AC_DirL_Tbl[])( FIELD_OBJ_PTR  );
extern int (* const DATA_AC_DirR_Tbl[])( FIELD_OBJ_PTR  );

//--------------------------------------------------------------
//	AC_WALK系
//--------------------------------------------------------------
extern int (* const DATA_AC_WalkU_32F_Tbl[])( FIELD_OBJ_PTR  );
extern int (* const DATA_AC_WalkD_32F_Tbl[])( FIELD_OBJ_PTR  );
extern int (* const DATA_AC_WalkL_32F_Tbl[])( FIELD_OBJ_PTR  );
extern int (* const DATA_AC_WalkR_32F_Tbl[])( FIELD_OBJ_PTR  );
extern int (* const DATA_AC_WalkU_16F_Tbl[])( FIELD_OBJ_PTR  );
extern int (* const DATA_AC_WalkD_16F_Tbl[])( FIELD_OBJ_PTR  );
extern int (* const DATA_AC_WalkL_16F_Tbl[])( FIELD_OBJ_PTR  );
extern int (* const DATA_AC_WalkR_16F_Tbl[])( FIELD_OBJ_PTR  );
extern int (* const DATA_AC_WalkU_8F_Tbl[])( FIELD_OBJ_PTR  );
extern int (* const DATA_AC_WalkD_8F_Tbl[])( FIELD_OBJ_PTR  );
extern int (* const DATA_AC_WalkL_8F_Tbl[])( FIELD_OBJ_PTR  );
extern int (* const DATA_AC_WalkR_8F_Tbl[])( FIELD_OBJ_PTR  );
extern int (* const DATA_AC_WalkU_4F_Tbl[])( FIELD_OBJ_PTR  );
extern int (* const DATA_AC_WalkD_4F_Tbl[])( FIELD_OBJ_PTR  );
extern int (* const DATA_AC_WalkL_4F_Tbl[])( FIELD_OBJ_PTR  );
extern int (* const DATA_AC_WalkR_4F_Tbl[])( FIELD_OBJ_PTR  );
extern int (* const DATA_AC_WalkU_2F_Tbl[])( FIELD_OBJ_PTR  );
extern int (* const DATA_AC_WalkD_2F_Tbl[])( FIELD_OBJ_PTR  );
extern int (* const DATA_AC_WalkL_2F_Tbl[])( FIELD_OBJ_PTR  );
extern int (* const DATA_AC_WalkR_2F_Tbl[])( FIELD_OBJ_PTR  );
extern int (* const DATA_AC_WalkU_1F_Tbl[])( FIELD_OBJ_PTR  );
extern int (* const DATA_AC_WalkD_1F_Tbl[])( FIELD_OBJ_PTR  );
extern int (* const DATA_AC_WalkL_1F_Tbl[])( FIELD_OBJ_PTR  );
extern int (* const DATA_AC_WalkR_1F_Tbl[])( FIELD_OBJ_PTR  );
extern int (* const DATA_AC_DashU_4F_Tbl[])( FIELD_OBJ_PTR  );
extern int (* const DATA_AC_DashD_4F_Tbl[])( FIELD_OBJ_PTR  );
extern int (* const DATA_AC_DashL_4F_Tbl[])( FIELD_OBJ_PTR  );
extern int (* const DATA_AC_DashR_4F_Tbl[])( FIELD_OBJ_PTR  );

//--------------------------------------------------------------
//	AC_STAY_WALK系
//--------------------------------------------------------------
extern int (* const DATA_AC_StayWalkU_32F_Tbl[])( FIELD_OBJ_PTR  );
extern int (* const DATA_AC_StayWalkD_32F_Tbl[])( FIELD_OBJ_PTR  );
extern int (* const DATA_AC_StayWalkL_32F_Tbl[])( FIELD_OBJ_PTR  );
extern int (* const DATA_AC_StayWalkR_32F_Tbl[])( FIELD_OBJ_PTR  );
extern int (* const DATA_AC_StayWalkU_16F_Tbl[])( FIELD_OBJ_PTR  );
extern int (* const DATA_AC_StayWalkD_16F_Tbl[])( FIELD_OBJ_PTR  );
extern int (* const DATA_AC_StayWalkL_16F_Tbl[])( FIELD_OBJ_PTR  );
extern int (* const DATA_AC_StayWalkR_16F_Tbl[])( FIELD_OBJ_PTR  );
extern int (* const DATA_AC_StayWalkU_8F_Tbl[])( FIELD_OBJ_PTR  );
extern int (* const DATA_AC_StayWalkD_8F_Tbl[])( FIELD_OBJ_PTR  );
extern int (* const DATA_AC_StayWalkL_8F_Tbl[])( FIELD_OBJ_PTR  );
extern int (* const DATA_AC_StayWalkR_8F_Tbl[])( FIELD_OBJ_PTR  );
extern int (* const DATA_AC_StayWalkU_4F_Tbl[])( FIELD_OBJ_PTR  );
extern int (* const DATA_AC_StayWalkD_4F_Tbl[])( FIELD_OBJ_PTR  );
extern int (* const DATA_AC_StayWalkL_4F_Tbl[])( FIELD_OBJ_PTR  );
extern int (* const DATA_AC_StayWalkR_4F_Tbl[])( FIELD_OBJ_PTR  );
extern int (* const DATA_AC_StayWalkU_2F_Tbl[])( FIELD_OBJ_PTR  );
extern int (* const DATA_AC_StayWalkD_2F_Tbl[])( FIELD_OBJ_PTR  );
extern int (* const DATA_AC_StayWalkL_2F_Tbl[])( FIELD_OBJ_PTR  );
extern int (* const DATA_AC_StayWalkR_2F_Tbl[])( FIELD_OBJ_PTR  );

//--------------------------------------------------------------
//	AC_JUMP系	
//--------------------------------------------------------------
extern int (* const DATA_AC_StayJumpU_16F_Tbl[])( FIELD_OBJ_PTR  );
extern int (* const DATA_AC_StayJumpD_16F_Tbl[])( FIELD_OBJ_PTR  );
extern int (* const DATA_AC_StayJumpL_16F_Tbl[])( FIELD_OBJ_PTR  );
extern int (* const DATA_AC_StayJumpR_16F_Tbl[])( FIELD_OBJ_PTR  );
 
extern int (* const DATA_AC_StayJumpU_8F_Tbl[])( FIELD_OBJ_PTR  );
extern int (* const DATA_AC_StayJumpD_8F_Tbl[])( FIELD_OBJ_PTR  );
extern int (* const DATA_AC_StayJumpL_8F_Tbl[])( FIELD_OBJ_PTR  );
extern int (* const DATA_AC_StayJumpR_8F_Tbl[])( FIELD_OBJ_PTR  );

extern int (* const DATA_AC_JumpU_1G_8F_Tbl[])( FIELD_OBJ_PTR  );
extern int (* const DATA_AC_JumpD_1G_8F_Tbl[])( FIELD_OBJ_PTR  );
extern int (* const DATA_AC_JumpL_1G_8F_Tbl[])( FIELD_OBJ_PTR  );
extern int (* const DATA_AC_JumpR_1G_8F_Tbl[])( FIELD_OBJ_PTR  );

extern int (* const DATA_AC_JumpU_2G_16F_Tbl[])( FIELD_OBJ_PTR  );
extern int (* const DATA_AC_JumpD_2G_16F_Tbl[])( FIELD_OBJ_PTR  );
extern int (* const DATA_AC_JumpL_2G_16F_Tbl[])( FIELD_OBJ_PTR  );
extern int (* const DATA_AC_JumpR_2G_16F_Tbl[])( FIELD_OBJ_PTR  );

extern int (* const DATA_AC_JumpHiL_1G_16F_Tbl[])( FIELD_OBJ_PTR  );
extern int (* const DATA_AC_JumpHiR_1G_16F_Tbl[])( FIELD_OBJ_PTR  );
extern int (* const DATA_AC_JumpHiL_3G_32F_Tbl[])( FIELD_OBJ_PTR  );
extern int (* const DATA_AC_JumpHiR_3G_32F_Tbl[])( FIELD_OBJ_PTR  );

//--------------------------------------------------------------
//	AC_WAIT系
//--------------------------------------------------------------
extern int (* const DATA_AC_Wait_1F_Tbl[])( FIELD_OBJ_PTR  );
extern int (* const DATA_AC_Wait_2F_Tbl[])( FIELD_OBJ_PTR  );
extern int (* const DATA_AC_Wait_4F_Tbl[])( FIELD_OBJ_PTR  );
extern int (* const DATA_AC_Wait_8F_Tbl[])( FIELD_OBJ_PTR  );
extern int (* const DATA_AC_Wait_15F_Tbl[])( FIELD_OBJ_PTR  );
extern int (* const DATA_AC_Wait_16F_Tbl[])( FIELD_OBJ_PTR  );
extern int (* const DATA_AC_Wait_32F_Tbl[])( FIELD_OBJ_PTR  );

//--------------------------------------------------------------
///	AC_WARP系
//--------------------------------------------------------------
extern int (* const DATA_AC_WarpUp_Tbl[])( FIELD_OBJ_PTR );
extern int (* const DATA_AC_WarpDown_Tbl[])( FIELD_OBJ_PTR );

//--------------------------------------------------------------
///	AC_VANISH_ON系
//--------------------------------------------------------------
extern int (* const DATA_AC_VanishON_Tbl[])( FIELD_OBJ_PTR );
extern int (* const DATA_AC_VanishOFF_Tbl[])( FIELD_OBJ_PTR );

//--------------------------------------------------------------
///	AC_DIR_PAUSE_ON系
//--------------------------------------------------------------
extern int (* const DATA_AC_DirPauseON_Tbl[])( FIELD_OBJ_PTR );
extern int (* const DATA_AC_DirPauseOFF_Tbl[])( FIELD_OBJ_PTR );

//--------------------------------------------------------------
///	AC_ANM_PAUSE_ON系
//--------------------------------------------------------------
extern int (* const DATA_AC_AnmPauseON_Tbl[])( FIELD_OBJ_PTR );
extern int (* const DATA_AC_AnmPauseOFF_Tbl[])( FIELD_OBJ_PTR );

//--------------------------------------------------------------
///	AC_MARK_GYOE系
//--------------------------------------------------------------
extern int (* const DATA_AC_MarkGyoe_Tbl[])( FIELD_OBJ_PTR );
extern int (* const DATA_AC_MarkSaisen_Tbl[])( FIELD_OBJ_PTR );

//--------------------------------------------------------------
///	AC_WALK_6F系
//--------------------------------------------------------------
extern int (* const DATA_AC_WalkU6F_Tbl[])( FIELD_OBJ_PTR );
extern int (* const DATA_AC_WalkD6F_Tbl[])( FIELD_OBJ_PTR );
extern int (* const DATA_AC_WalkL6F_Tbl[])( FIELD_OBJ_PTR );
extern int (* const DATA_AC_WalkR6F_Tbl[])( FIELD_OBJ_PTR );

extern int (* const DATA_AC_WalkU3F_Tbl[])( FIELD_OBJ_PTR );
extern int (* const DATA_AC_WalkD3F_Tbl[])( FIELD_OBJ_PTR );
extern int (* const DATA_AC_WalkL3F_Tbl[])( FIELD_OBJ_PTR );
extern int (* const DATA_AC_WalkR3F_Tbl[])( FIELD_OBJ_PTR );

extern int (* const DATA_AC_WalkU7F_Tbl[])( FIELD_OBJ_PTR );
extern int (* const DATA_AC_WalkD7F_Tbl[])( FIELD_OBJ_PTR );
extern int (* const DATA_AC_WalkL7F_Tbl[])( FIELD_OBJ_PTR );
extern int (* const DATA_AC_WalkR7F_Tbl[])( FIELD_OBJ_PTR );

//--------------------------------------------------------------
///	AC_PC_BOW
//--------------------------------------------------------------
extern int (* const DATA_AC_PcBow_Tbl[])( FIELD_OBJ_PTR );

//--------------------------------------------------------------
///	AC_HIDE_PULLOFF
//--------------------------------------------------------------
extern int (* const DATA_AC_HidePullOFF_Tbl[])( FIELD_OBJ_PTR );

//--------------------------------------------------------------
///	AC_HERO_BANZAI
//--------------------------------------------------------------
extern int (* const DATA_AC_HeroBanzai_Tbl[])( FIELD_OBJ_PTR );
extern int (* const DATA_AC_HeroBanzaiUke_Tbl[])( FIELD_OBJ_PTR );

//==============================================================================
//	フィールドOBJ 動作関数定義
//==============================================================================
//--------------------------------------------------------------
///	ダミー
//--------------------------------------------------------------
static const FIELD_OBJ_MOVE_PROC_LIST DATA_FieldOBJMove_Dummy =
{
	MV_DMY,													///<動作コード
	FieldOBJ_MoveInitProcDummy,								///<初期化関数
	FieldOBJ_MoveProcDummy,									///<動作関数
	FieldOBJ_MoveDeleteProcDummy,							///<削除関数
	FieldOBJ_MoveReturnProcDummy,							///<復帰関数
};

//--------------------------------------------------------------
///	MV_PLAYER	
//--------------------------------------------------------------
static const FIELD_OBJ_MOVE_PROC_LIST DATA_FieldOBJMove_Player =
{
	MV_PLAYER,												///<動作コード
	FieldOBJ_MoveInitProcDummy,								///<初期化関数
	FieldOBJ_MoveProcDummy,									///<動作関数
	FieldOBJ_MoveDeleteProcDummy,							///<削除関数
	FieldOBJ_MoveReturnProcDummy,							///<復帰関数
};

//--------------------------------------------------------------
///	MV_DIR_RND
//--------------------------------------------------------------
static const FIELD_OBJ_MOVE_PROC_LIST DATA_FieldOBJMove_DirRnd =
{
	MV_DIR_RND,												///<動作コード
	FieldOBJ_MoveDirRnd_Init,								///<初期化関数
	FieldOBJ_MoveDirRnd_Move,								///<動作関数
	FieldOBJ_MoveDirRnd_Delete,								///<削除関数
	FieldOBJ_MoveReturnProcDummy,							///<復帰関数
};

//--------------------------------------------------------------
///	MV_RND
//--------------------------------------------------------------
static const FIELD_OBJ_MOVE_PROC_LIST DATA_FieldOBJMove_Rnd =
{
	MV_RND,													///<動作コード
	FieldOBJ_MoveRnd_Init,									///<初期化関数
	FieldOBJ_MvRnd_Move,									///<動作関数
	FieldOBJ_MoveDeleteProcDummy,							///<削除関数
	FieldOBJ_MoveReturnProcDummy,							///<復帰関数
};

//--------------------------------------------------------------
///	MV_RND_V
//--------------------------------------------------------------
static const FIELD_OBJ_MOVE_PROC_LIST DATA_FieldOBJMove_RndV =
{
	MV_RND,													///<動作コード
	FieldOBJ_MoveRndV_Init,									///<初期化関数
	FieldOBJ_MvRnd_Move,									///<動作関数
	FieldOBJ_MoveDeleteProcDummy,							///<削除関数
	FieldOBJ_MoveReturnProcDummy,							///<復帰関数
};

//--------------------------------------------------------------
///	MV_RND_H
//--------------------------------------------------------------
static const FIELD_OBJ_MOVE_PROC_LIST DATA_FieldOBJMove_RndH =
{
	MV_RND,													///<動作コード
	FieldOBJ_MoveRndH_Init,									///<初期化関数
	FieldOBJ_MvRnd_Move,									///<動作関数
	FieldOBJ_MoveDeleteProcDummy,							///<削除関数
	FieldOBJ_MoveReturnProcDummy,							///<復帰関数
};

//--------------------------------------------------------------
///	MV_RND_UL
//--------------------------------------------------------------
static const FIELD_OBJ_MOVE_PROC_LIST DATA_FieldOBJMove_RndUL =
{
	MV_RND,													///<動作コード
	FieldOBJ_MoveDirRndUL_Init,								///<初期化関数
	FieldOBJ_MoveDirRnd_Move,									///<動作関数
	FieldOBJ_MoveDirRnd_Delete,							///<削除関数
	FieldOBJ_MoveReturnProcDummy,							///<復帰関数
};

//--------------------------------------------------------------
///	MV_RND_UR
//--------------------------------------------------------------
static const FIELD_OBJ_MOVE_PROC_LIST DATA_FieldOBJMove_RndUR =
{
	MV_RND,													///<動作コード
	FieldOBJ_MoveDirRndUR_Init,								///<初期化関数
	FieldOBJ_MoveDirRnd_Move,									///<動作関数
	FieldOBJ_MoveDirRnd_Delete,							///<削除関数
	FieldOBJ_MoveReturnProcDummy,							///<復帰関数
};

//--------------------------------------------------------------
///	MV_RND_DL
//--------------------------------------------------------------
static const FIELD_OBJ_MOVE_PROC_LIST DATA_FieldOBJMove_RndDL =
{
	MV_RND,													///<動作コード
	FieldOBJ_MoveDirRndDL_Init,								///<初期化関数
	FieldOBJ_MoveDirRnd_Move,									///<動作関数
	FieldOBJ_MoveDirRnd_Delete,							///<削除関数
	FieldOBJ_MoveReturnProcDummy,							///<復帰関数
};

//--------------------------------------------------------------
///	MV_RND_DR
//--------------------------------------------------------------
static const FIELD_OBJ_MOVE_PROC_LIST DATA_FieldOBJMove_RndDR =
{
	MV_RND,													///<動作コード
	FieldOBJ_MoveDirRndDR_Init,								///<初期化関数
	FieldOBJ_MoveDirRnd_Move,									///<動作関数
	FieldOBJ_MoveDirRnd_Delete,							///<削除関数
	FieldOBJ_MoveReturnProcDummy,							///<復帰関数
};

//--------------------------------------------------------------
///	MV_RND_UDL
//--------------------------------------------------------------
static const FIELD_OBJ_MOVE_PROC_LIST DATA_FieldOBJMove_RndUDL =
{
	MV_RND,													///<動作コード
	FieldOBJ_MoveDirRndUDL_Init,								///<初期化関数
	FieldOBJ_MoveDirRnd_Move,									///<動作関数
	FieldOBJ_MoveDirRnd_Delete,							///<削除関数
	FieldOBJ_MoveReturnProcDummy,							///<復帰関数
};

//--------------------------------------------------------------
///	MV_RND_UDR
//--------------------------------------------------------------
static const FIELD_OBJ_MOVE_PROC_LIST DATA_FieldOBJMove_RndUDR =
{
	MV_RND,													///<動作コード
	FieldOBJ_MoveDirRndUDR_Init,								///<初期化関数
	FieldOBJ_MoveDirRnd_Move,									///<動作関数
	FieldOBJ_MoveDirRnd_Delete,							///<削除関数
	FieldOBJ_MoveReturnProcDummy,							///<復帰関数
};

//--------------------------------------------------------------
///	MV_RND_ULR
//--------------------------------------------------------------
static const FIELD_OBJ_MOVE_PROC_LIST DATA_FieldOBJMove_RndULR =
{
	MV_RND,													///<動作コード
	FieldOBJ_MoveDirRndULR_Init,								///<初期化関数
	FieldOBJ_MoveDirRnd_Move,									///<動作関数
	FieldOBJ_MoveDirRnd_Delete,							///<削除関数
	FieldOBJ_MoveReturnProcDummy,							///<復帰関数
};

//--------------------------------------------------------------
///	MV_RND_DLR
//--------------------------------------------------------------
static const FIELD_OBJ_MOVE_PROC_LIST DATA_FieldOBJMove_RndDLR =
{
	MV_RND,													///<動作コード
	FieldOBJ_MoveDirRndDLR_Init,								///<初期化関数
	FieldOBJ_MoveDirRnd_Move,									///<動作関数
	FieldOBJ_MoveDirRnd_Delete,							///<削除関数
	FieldOBJ_MoveReturnProcDummy,							///<復帰関数
};

//--------------------------------------------------------------
///	MV_RND_UD
//--------------------------------------------------------------
static const FIELD_OBJ_MOVE_PROC_LIST DATA_FieldOBJMove_RndUD =
{
	MV_RND,													///<動作コード
	FieldOBJ_MoveDirRndUD_Init,								///<初期化関数
	FieldOBJ_MoveDirRnd_Move,									///<動作関数
	FieldOBJ_MoveDirRnd_Delete,							///<削除関数
	FieldOBJ_MoveReturnProcDummy,							///<復帰関数
};

//--------------------------------------------------------------
///	MV_RND_LR
//--------------------------------------------------------------
static const FIELD_OBJ_MOVE_PROC_LIST DATA_FieldOBJMove_RndLR =
{
	MV_RND,													///<動作コード
	FieldOBJ_MoveDirRndLR_Init,								///<初期化関数
	FieldOBJ_MoveDirRnd_Move,									///<動作関数
	FieldOBJ_MoveDirRnd_Delete,							///<削除関数
	FieldOBJ_MoveReturnProcDummy,							///<復帰関数
};

//--------------------------------------------------------------
///	MV_UP
//--------------------------------------------------------------
static const FIELD_OBJ_MOVE_PROC_LIST DATA_FieldOBJMove_Up =
{
	MV_RND,													///<動作コード
	FieldOBJ_MoveUp_Init,									///<初期化関数
	FieldOBJ_MoveDir_Move,									///<動作関数
	FieldOBJ_MoveDeleteProcDummy,							///<削除関数
	FieldOBJ_MoveReturnProcDummy,							///<復帰関数
};

//--------------------------------------------------------------
///	MV_DOWN
//--------------------------------------------------------------
static const FIELD_OBJ_MOVE_PROC_LIST DATA_FieldOBJMove_Down =
{
	MV_RND,													///<動作コード
	FieldOBJ_MoveDown_Init,									///<初期化関数
	FieldOBJ_MoveDir_Move,									///<動作関数
	FieldOBJ_MoveDeleteProcDummy,							///<削除関数
	FieldOBJ_MoveReturnProcDummy,							///<復帰関数
};

//--------------------------------------------------------------
///	MV_LEFT
//--------------------------------------------------------------
static const FIELD_OBJ_MOVE_PROC_LIST DATA_FieldOBJMove_Left =
{
	MV_RND,													///<動作コード
	FieldOBJ_MoveLeft_Init,									///<初期化関数
	FieldOBJ_MoveDir_Move,									///<動作関数
	FieldOBJ_MoveDeleteProcDummy,							///<削除関数
	FieldOBJ_MoveReturnProcDummy,							///<復帰関数
};

//--------------------------------------------------------------
///	MV_RIGHT
//--------------------------------------------------------------
static const FIELD_OBJ_MOVE_PROC_LIST DATA_FieldOBJMove_Right =
{
	MV_RND,													///<動作コード
	FieldOBJ_MoveRight_Init,								///<初期化関数
	FieldOBJ_MoveDir_Move,									///<動作関数
	FieldOBJ_MoveDeleteProcDummy,							///<削除関数
	FieldOBJ_MoveReturnProcDummy,							///<復帰関数
};

//--------------------------------------------------------------
///	MV_SPIN_L
//--------------------------------------------------------------
static const FIELD_OBJ_MOVE_PROC_LIST DATA_FieldOBJMove_SpinLeft =
{
	MV_RND,													///<動作コード
	FieldOBJ_MoveSpinLeft_Init,								///<初期化関数
	FieldOBJ_MoveSpin_Move,									///<動作関数
	FieldOBJ_MoveDeleteProcDummy,							///<削除関数
	FieldOBJ_MoveReturnProcDummy,							///<復帰関数
};

//--------------------------------------------------------------
///	MV_SPIN_R
//--------------------------------------------------------------
static const FIELD_OBJ_MOVE_PROC_LIST DATA_FieldOBJMove_SpinRight =
{
	MV_RND,													///<動作コード
	FieldOBJ_MoveSpinRight_Init,							///<初期化関数
	FieldOBJ_MoveSpin_Move,									///<動作関数
	FieldOBJ_MoveDeleteProcDummy,							///<削除関数
	FieldOBJ_MoveReturnProcDummy,							///<復帰関数
};

//--------------------------------------------------------------
///	MV_REWAR
//--------------------------------------------------------------
static const FIELD_OBJ_MOVE_PROC_LIST DATA_FieldOBJMove_Rewar =
{
	MV_RND,													///<動作コード
	FieldOBJ_MoveRewar_Init,								///<初期化関数
	FieldOBJ_MoveRewar_Move,								///<動作関数
	FieldOBJ_MoveDeleteProcDummy,							///<削除関数
	FieldOBJ_MoveReturnProcDummy,							///<復帰関数
};

//--------------------------------------------------------------
///	MV_RT2
//--------------------------------------------------------------
static const FIELD_OBJ_MOVE_PROC_LIST DATA_FieldOBJMove_Route2 =
{
	MV_RND,													///<動作コード
	FieldOBJ_MoveRoute2_Init,								///<初期化関数
	FieldOBJ_MoveRoute2_Move,								///<動作関数
	FieldOBJ_MoveDeleteProcDummy,							///<削除関数
	FieldOBJ_MoveReturnProcDummy,							///<復帰関数
};

//--------------------------------------------------------------
///	MV_RTURLD
//--------------------------------------------------------------
static const FIELD_OBJ_MOVE_PROC_LIST DATA_FieldOBJMove_RouteURLD =
{
	MV_RND,													///<動作コード
	FieldOBJ_MoveRouteURLD_Init,							///<初期化関数
	FieldOBJ_MoveRoute3_Move,								///<動作関数
	FieldOBJ_MoveDeleteProcDummy,							///<削除関数
	FieldOBJ_MoveReturnProcDummy,							///<復帰関数
};

//--------------------------------------------------------------
///	MV_RTRLDU
//--------------------------------------------------------------
static const FIELD_OBJ_MOVE_PROC_LIST DATA_FieldOBJMove_RouteRLDU =
{
	MV_RND,													///<動作コード
	FieldOBJ_MoveRouteRLDU_Init,							///<初期化関数
	FieldOBJ_MoveRoute3_Move,								///<動作関数
	FieldOBJ_MoveDeleteProcDummy,							///<削除関数
	FieldOBJ_MoveReturnProcDummy,							///<復帰関数
};

//--------------------------------------------------------------
///	MV_RTDURL
//--------------------------------------------------------------
static const FIELD_OBJ_MOVE_PROC_LIST DATA_FieldOBJMove_RouteDURL =
{
	MV_RND,													///<動作コード
	FieldOBJ_MoveRouteDURL_Init,							///<初期化関数
	FieldOBJ_MoveRoute3_Move,								///<動作関数
	FieldOBJ_MoveDeleteProcDummy,							///<削除関数
	FieldOBJ_MoveReturnProcDummy,							///<復帰関数
};

//--------------------------------------------------------------
///	MV_RTLDUR
//--------------------------------------------------------------
static const FIELD_OBJ_MOVE_PROC_LIST DATA_FieldOBJMove_RouteLDUR =
{
	MV_RND,													///<動作コード
	FieldOBJ_MoveRouteLDUR_Init,							///<初期化関数
	FieldOBJ_MoveRoute3_Move,								///<動作関数
	FieldOBJ_MoveDeleteProcDummy,							///<削除関数
	FieldOBJ_MoveReturnProcDummy,							///<復帰関数
};

//--------------------------------------------------------------
///	MV_RTULRD
//--------------------------------------------------------------
static const FIELD_OBJ_MOVE_PROC_LIST DATA_FieldOBJMove_RouteULRD =
{
	MV_RND,													///<動作コード
	FieldOBJ_MoveRouteULRD_Init,							///<初期化関数
	FieldOBJ_MoveRoute3_Move,								///<動作関数
	FieldOBJ_MoveDeleteProcDummy,							///<削除関数
	FieldOBJ_MoveReturnProcDummy,							///<復帰関数
};

//--------------------------------------------------------------
///	MV_RTLRDU
//--------------------------------------------------------------
static const FIELD_OBJ_MOVE_PROC_LIST DATA_FieldOBJMove_RouteLRDU =
{
	MV_RND,													///<動作コード
	FieldOBJ_MoveRouteLRDU_Init,							///<初期化関数
	FieldOBJ_MoveRoute3_Move,								///<動作関数
	FieldOBJ_MoveDeleteProcDummy,							///<削除関数
	FieldOBJ_MoveReturnProcDummy,							///<復帰関数
};

//--------------------------------------------------------------
///	MV_RTDULR
//--------------------------------------------------------------
static const FIELD_OBJ_MOVE_PROC_LIST DATA_FieldOBJMove_RouteDULR =
{
	MV_RND,													///<動作コード
	FieldOBJ_MoveRouteDULR_Init,							///<初期化関数
	FieldOBJ_MoveRoute3_Move,								///<動作関数
	FieldOBJ_MoveDeleteProcDummy,							///<削除関数
	FieldOBJ_MoveReturnProcDummy,							///<復帰関数
};

//--------------------------------------------------------------
///	MV_RTRDUL
//--------------------------------------------------------------
static const FIELD_OBJ_MOVE_PROC_LIST DATA_FieldOBJMove_RouteRDUL =
{
	MV_RND,													///<動作コード
	FieldOBJ_MoveRouteRDUL_Init,							///<初期化関数
	FieldOBJ_MoveRoute3_Move,								///<動作関数
	FieldOBJ_MoveDeleteProcDummy,							///<削除関数
	FieldOBJ_MoveReturnProcDummy,							///<復帰関数
};

//--------------------------------------------------------------
///	MV_RTLUDR
//--------------------------------------------------------------
static const FIELD_OBJ_MOVE_PROC_LIST DATA_FieldOBJMove_RouteLUDR =
{
	MV_RND,													///<動作コード
	FieldOBJ_MoveRouteLUDR_Init,							///<初期化関数
	FieldOBJ_MoveRoute3_Move,								///<動作関数
	FieldOBJ_MoveDeleteProcDummy,							///<削除関数
	FieldOBJ_MoveReturnProcDummy,							///<復帰関数
};

//--------------------------------------------------------------
///	MV_RTUDRL
//--------------------------------------------------------------
static const FIELD_OBJ_MOVE_PROC_LIST DATA_FieldOBJMove_RouteUDRL =
{
	MV_RND,													///<動作コード
	FieldOBJ_MoveRouteUDRL_Init,							///<初期化関数
	FieldOBJ_MoveRoute3_Move,								///<動作関数
	FieldOBJ_MoveDeleteProcDummy,							///<削除関数
	FieldOBJ_MoveReturnProcDummy,							///<復帰関数
};

//--------------------------------------------------------------
///	MV_RTRLUD
//--------------------------------------------------------------
static const FIELD_OBJ_MOVE_PROC_LIST DATA_FieldOBJMove_RouteRLUD =
{
	MV_RND,													///<動作コード
	FieldOBJ_MoveRouteRLUD_Init,							///<初期化関数
	FieldOBJ_MoveRoute3_Move,								///<動作関数
	FieldOBJ_MoveDeleteProcDummy,							///<削除関数
	FieldOBJ_MoveReturnProcDummy,							///<復帰関数
};

//--------------------------------------------------------------
///	MV_RTDRLU
//--------------------------------------------------------------
static const FIELD_OBJ_MOVE_PROC_LIST DATA_FieldOBJMove_RouteDRLU =
{
	MV_RND,													///<動作コード
	FieldOBJ_MoveRouteDRLU_Init,							///<初期化関数
	FieldOBJ_MoveRoute3_Move,								///<動作関数
	FieldOBJ_MoveDeleteProcDummy,							///<削除関数
	FieldOBJ_MoveReturnProcDummy,							///<復帰関数
};

//--------------------------------------------------------------
///	MV_RTRUDL
//--------------------------------------------------------------
static const FIELD_OBJ_MOVE_PROC_LIST DATA_FieldOBJMove_RouteRUDL =
{
	MV_RND,													///<動作コード
	FieldOBJ_MoveRouteRUDL_Init,							///<初期化関数
	FieldOBJ_MoveRoute3_Move,								///<動作関数
	FieldOBJ_MoveDeleteProcDummy,							///<削除関数
	FieldOBJ_MoveReturnProcDummy,							///<復帰関数
};

//--------------------------------------------------------------
///	MV_RTUDLR
//--------------------------------------------------------------
static const FIELD_OBJ_MOVE_PROC_LIST DATA_FieldOBJMove_RouteUDLR =
{
	MV_RND,													///<動作コード
	FieldOBJ_MoveRouteUDLR_Init,							///<初期化関数
	FieldOBJ_MoveRoute3_Move,								///<動作関数
	FieldOBJ_MoveDeleteProcDummy,							///<削除関数
	FieldOBJ_MoveReturnProcDummy,							///<復帰関数
};

//--------------------------------------------------------------
///	MV_RTLRUD
//--------------------------------------------------------------
static const FIELD_OBJ_MOVE_PROC_LIST DATA_FieldOBJMove_RouteLRUD =
{
	MV_RND,													///<動作コード
	FieldOBJ_MoveRouteLRUD_Init,							///<初期化関数
	FieldOBJ_MoveRoute3_Move,								///<動作関数
	FieldOBJ_MoveDeleteProcDummy,							///<削除関数
	FieldOBJ_MoveReturnProcDummy,							///<復帰関数
};

//--------------------------------------------------------------
///	MV_RTDLRU
//--------------------------------------------------------------
static const FIELD_OBJ_MOVE_PROC_LIST DATA_FieldOBJMove_RouteDLRU =
{
	MV_RND,													///<動作コード
	FieldOBJ_MoveRouteDLRU_Init,							///<初期化関数
	FieldOBJ_MoveRoute3_Move,								///<動作関数
	FieldOBJ_MoveDeleteProcDummy,							///<削除関数
	FieldOBJ_MoveReturnProcDummy,							///<復帰関数
};

//--------------------------------------------------------------
///	MV_RTUL
//--------------------------------------------------------------
static const FIELD_OBJ_MOVE_PROC_LIST DATA_FieldOBJMove_RouteUL =
{
	MV_RND,													///<動作コード
	FieldOBJ_MoveRouteUL_Init,								///<初期化関数
	FieldOBJ_MoveRoute3_Move,								///<動作関数
	FieldOBJ_MoveDeleteProcDummy,							///<削除関数
	FieldOBJ_MoveReturnProcDummy,							///<復帰関数
};

//--------------------------------------------------------------
///	MV_RTDR
//--------------------------------------------------------------
static const FIELD_OBJ_MOVE_PROC_LIST DATA_FieldOBJMove_RouteDR =
{
	MV_RND,													///<動作コード
	FieldOBJ_MoveRouteDR_Init,								///<初期化関数
	FieldOBJ_MoveRoute3_Move,								///<動作関数
	FieldOBJ_MoveDeleteProcDummy,							///<削除関数
	FieldOBJ_MoveReturnProcDummy,							///<復帰関数
};

//--------------------------------------------------------------
///	MV_RTLD
//--------------------------------------------------------------
static const FIELD_OBJ_MOVE_PROC_LIST DATA_FieldOBJMove_RouteLD =
{
	MV_RND,													///<動作コード
	FieldOBJ_MoveRouteLD_Init,								///<初期化関数
	FieldOBJ_MoveRoute3_Move,								///<動作関数
	FieldOBJ_MoveDeleteProcDummy,							///<削除関数
	FieldOBJ_MoveReturnProcDummy,							///<復帰関数
};

//--------------------------------------------------------------
///	MV_RTRU
//--------------------------------------------------------------
static const FIELD_OBJ_MOVE_PROC_LIST DATA_FieldOBJMove_RouteRU =
{
	MV_RND,													///<動作コード
	FieldOBJ_MoveRouteRU_Init,								///<初期化関数
	FieldOBJ_MoveRoute3_Move,								///<動作関数
	FieldOBJ_MoveDeleteProcDummy,							///<削除関数
	FieldOBJ_MoveReturnProcDummy,							///<復帰関数
};

//--------------------------------------------------------------
///	MV_RTUR
//--------------------------------------------------------------
static const FIELD_OBJ_MOVE_PROC_LIST DATA_FieldOBJMove_RouteUR =
{
	MV_RND,													///<動作コード
	FieldOBJ_MoveRouteUR_Init,								///<初期化関数
	FieldOBJ_MoveRoute3_Move,								///<動作関数
	FieldOBJ_MoveDeleteProcDummy,							///<削除関数
	FieldOBJ_MoveReturnProcDummy,							///<復帰関数
};

//--------------------------------------------------------------
///	MV_RTDL
//--------------------------------------------------------------
static const FIELD_OBJ_MOVE_PROC_LIST DATA_FieldOBJMove_RouteDL =
{
	MV_RND,													///<動作コード
	FieldOBJ_MoveRouteDL_Init,								///<初期化関数
	FieldOBJ_MoveRoute3_Move,								///<動作関数
	FieldOBJ_MoveDeleteProcDummy,							///<削除関数
	FieldOBJ_MoveReturnProcDummy,							///<復帰関数
};

//--------------------------------------------------------------
///	MV_RTLU
//--------------------------------------------------------------
static const FIELD_OBJ_MOVE_PROC_LIST DATA_FieldOBJMove_RouteLU =
{
	MV_RND,													///<動作コード
	FieldOBJ_MoveRouteLU_Init,								///<初期化関数
	FieldOBJ_MoveRoute3_Move,								///<動作関数
	FieldOBJ_MoveDeleteProcDummy,							///<削除関数
	FieldOBJ_MoveReturnProcDummy,							///<復帰関数
};

//--------------------------------------------------------------
///	MV_RTRD
//--------------------------------------------------------------
static const FIELD_OBJ_MOVE_PROC_LIST DATA_FieldOBJMove_RouteRD =
{
	MV_RND,													///<動作コード
	FieldOBJ_MoveRouteRD_Init,								///<初期化関数
	FieldOBJ_MoveRoute3_Move,								///<動作関数
	FieldOBJ_MoveDeleteProcDummy,							///<削除関数
	FieldOBJ_MoveReturnProcDummy,							///<復帰関数
};

//--------------------------------------------------------------
///	MV_SEED
//--------------------------------------------------------------
static const FIELD_OBJ_MOVE_PROC_LIST DATA_FieldOBJMove_Seed =
{
	MV_SEED,												///<動作コード
	FieldOBJ_MoveSeed_Init,									///<初期化関数
	FieldOBJ_MoveSeed_Move,									///<動作関数
	FieldOBJ_MoveSeed_Delete,								///<削除関数
	FieldOBJ_MoveReturnProcDummy,							///<復帰関数
};

//--------------------------------------------------------------
///	MV_PAIR
//--------------------------------------------------------------
static const FIELD_OBJ_MOVE_PROC_LIST DATA_FieldOBJMove_Pair =
{
	MV_RND,													///<動作コード
	FieldOBJ_MovePair_Init,									///<初期化関数
	FieldOBJ_MovePair_Move,									///<動作関数
	FieldOBJ_MovePair_Delete,							///<削除関数
	FieldOBJ_MoveReturnProcDummy,							///<復帰関数
};

//--------------------------------------------------------------
///	MV_TR_PAIR
//--------------------------------------------------------------
static const FIELD_OBJ_MOVE_PROC_LIST DATA_FieldOBJMove_PairTr =
{
	MV_RND,													///<動作コード
	FieldOBJ_MovePairTr_Init,								///<初期化関数
	FieldOBJ_MovePairTr_Move,								///<動作関数
	FieldOBJ_MovePairTr_Delete,								///<削除関数
	FieldOBJ_MovePairTr_Return,								///<復帰関数
};

//--------------------------------------------------------------
///	MV_HIDE_SNOW
//--------------------------------------------------------------
static const FIELD_OBJ_MOVE_PROC_LIST DATA_FieldOBJMove_HideSnow =
{
	MV_HIDE_SNOW,												///<動作コード
	FieldOBJ_MoveHideSnow_Init,								///<初期化関数
	FieldOBJ_MoveHide_Move,								///<動作関数
	FieldOBJ_MoveHide_Delete,								///<削除関数
	FieldOBJ_MoveHide_Return,							///<復帰関数
};

//--------------------------------------------------------------
///	MV_HIDE_SAND
//--------------------------------------------------------------
static const FIELD_OBJ_MOVE_PROC_LIST DATA_FieldOBJMove_HideSand =
{
	MV_HIDE_SAND,												///<動作コード
	FieldOBJ_MoveHideSand_Init,								///<初期化関数
	FieldOBJ_MoveHide_Move,								///<動作関数
	FieldOBJ_MoveHide_Delete,								///<削除関数
	FieldOBJ_MoveHide_Return,							///<復帰関数
};

//--------------------------------------------------------------
///	MV_HIDE_GRND
//--------------------------------------------------------------
static const FIELD_OBJ_MOVE_PROC_LIST DATA_FieldOBJMove_HideGround =
{
	MV_HIDE_GRND,												///<動作コード
	FieldOBJ_MoveHideGround_Init,								///<初期化関数
	FieldOBJ_MoveHide_Move,								///<動作関数
	FieldOBJ_MoveHide_Delete,								///<削除関数
	FieldOBJ_MoveHide_Return,							///<復帰関数
};

//--------------------------------------------------------------
///	MV_HIDE_KUSA
//--------------------------------------------------------------
static const FIELD_OBJ_MOVE_PROC_LIST DATA_FieldOBJMove_HideKusa =
{
	MV_HIDE_KUSA,												///<動作コード
	FieldOBJ_MoveHideKusa_Init,								///<初期化関数
	FieldOBJ_MoveHide_Move,								///<動作関数
	FieldOBJ_MoveHide_Delete,								///<削除関数
	FieldOBJ_MoveHide_Return,							///<復帰関数
};

//==============================================================================
//	フィールドOBJ 動作関数まとめ
//==============================================================================
//--------------------------------------------------------------
///	動作関数まとめ
///	並びはfieldobj_code.h MV_DMY等のコードと一致
//--------------------------------------------------------------
const FIELD_OBJ_MOVE_PROC_LIST * const DATA_FieldOBJMoveProcListTbl[] =
{
	&DATA_FieldOBJMove_Dummy,								//MV_DMY
	&DATA_FieldOBJMove_Player,								//MV_PLAYER
	&DATA_FieldOBJMove_DirRnd,								//MV_DIR_RND
	&DATA_FieldOBJMove_Rnd,									//MV_RND
	&DATA_FieldOBJMove_RndV,								//MV_RND_V
	&DATA_FieldOBJMove_RndH,								//MV_RND_H
	&DATA_FieldOBJMove_RndUL,								//MV_RND_UL
	&DATA_FieldOBJMove_RndUR,								//MV_RND_UR
	&DATA_FieldOBJMove_RndDL,								//MV_RND_DL
	&DATA_FieldOBJMove_RndDR,								//MV_RND_DR
	&DATA_FieldOBJMove_RndUDL,								//MV_RND_UDL
	&DATA_FieldOBJMove_RndUDR,								//MV_RND_UDR
	&DATA_FieldOBJMove_RndULR,								//MV_RND_ULR
	&DATA_FieldOBJMove_RndDLR,								//MV_RND_DLR
	&DATA_FieldOBJMove_Up,									//MV_UP
	&DATA_FieldOBJMove_Down,								//MV_DOWN
	&DATA_FieldOBJMove_Left,								//MV_LEFT
	&DATA_FieldOBJMove_Right,								//MV_RIGHT
	&DATA_FieldOBJMove_SpinLeft,							//MV_SPIN_L
	&DATA_FieldOBJMove_SpinRight,							//MV_SPIN_R
	&DATA_FieldOBJMove_Route2,								//MV_RT2
	&DATA_FieldOBJMove_RouteURLD,							//MV_RTURLD
	&DATA_FieldOBJMove_RouteRLDU,							//MV_RTRLDU
	&DATA_FieldOBJMove_RouteDURL,							//MV_RTDURL
	&DATA_FieldOBJMove_RouteLDUR,							//MV_RTLDUR
	&DATA_FieldOBJMove_RouteULRD,							//MV_RTULRD
	&DATA_FieldOBJMove_RouteLRDU,							//MV_RTLRDU
	&DATA_FieldOBJMove_RouteDULR,							//MV_RTDULR
	&DATA_FieldOBJMove_RouteRDUL,							//MV_RTRDUL
	&DATA_FieldOBJMove_RouteLUDR,							//MV_RTLUDR
	&DATA_FieldOBJMove_RouteUDRL,							//MV_RTUDRL
	&DATA_FieldOBJMove_RouteRLUD,							//MV_RTRLUD
	&DATA_FieldOBJMove_RouteDRLU,							//MV_RTDRLU
	&DATA_FieldOBJMove_RouteRUDL,							//MV_RTRUDL
	&DATA_FieldOBJMove_RouteUDLR,							//MV_RTUDLR
	&DATA_FieldOBJMove_RouteLRUD,							//MV_RTLRUD
	&DATA_FieldOBJMove_RouteDLRU,							//MV_RTDLRU
	&DATA_FieldOBJMove_RouteUL,								//MV_UL
	&DATA_FieldOBJMove_RouteDR,								//MV_DR
	&DATA_FieldOBJMove_RouteLD,								//MV_LD
	&DATA_FieldOBJMove_RouteRU,								//MV_RU
	&DATA_FieldOBJMove_RouteUR,								//MV_UR
	&DATA_FieldOBJMove_RouteDL,								//MV_DL
	&DATA_FieldOBJMove_RouteLU,								//MV_LU
	&DATA_FieldOBJMove_RouteRD,								//MV_RD
	&DATA_FieldOBJMove_RndUD,								//MV_RND_UD
	&DATA_FieldOBJMove_RndLR,								//MV_RND_LR
	&DATA_FieldOBJMove_Seed,								//MV_SEED
	&DATA_FieldOBJMove_Pair,								//MV_PAIR
	&DATA_FieldOBJMove_Rewar,								//MV_REWAR
	&DATA_FieldOBJMove_PairTr,								//MV_TR_PAIR
	&DATA_FieldOBJMove_HideSnow,							//MV_HIDE_SNOW
	&DATA_FieldOBJMove_HideSand,							//MV_HIDE_SAND
	&DATA_FieldOBJMove_HideGround,							//MV_HIDE_GRND
	&DATA_FieldOBJMove_HideKusa,							//MV_HIDE_KUSA
};

//==============================================================================
//	フィールドOBJ アニメーションコマンド
//==============================================================================
//--------------------------------------------------------------
///	アニメーションコマンドテーブル。
///	並びはfieldobj_code.h AC_DIR_U等のコードと一致。
//--------------------------------------------------------------
int (* const * const DATA_AcmdActionTbl[ACMD_MAX])( FIELD_OBJ_PTR  ) =
{
	DATA_AC_DirU_Tbl,										//AC_DIR_U
	DATA_AC_DirD_Tbl,										//AC_DIR_D
	DATA_AC_DirL_Tbl,										//AC_DIR_L
	DATA_AC_DirR_Tbl,										//AC_DIR_R
	DATA_AC_WalkU_32F_Tbl,									//AC_WALK_U_32F
	DATA_AC_WalkD_32F_Tbl,									//AC_WALK_D_32F
	DATA_AC_WalkL_32F_Tbl,									//AC_WALK_L_32F
	DATA_AC_WalkR_32F_Tbl,									//AC_WALK_R_32F
	DATA_AC_WalkU_16F_Tbl,									//AC_WALK_U_16F
	DATA_AC_WalkD_16F_Tbl,									//AC_WALK_D_16F
	DATA_AC_WalkL_16F_Tbl,									//AC_WALK_L_16F
	DATA_AC_WalkR_16F_Tbl,									//AC_WALK_R_16F
	DATA_AC_WalkU_8F_Tbl,									//AC_WALK_U_8F
	DATA_AC_WalkD_8F_Tbl,									//AC_WALK_D_8F
	DATA_AC_WalkL_8F_Tbl,									//AC_WALK_L_8F
	DATA_AC_WalkR_8F_Tbl,									//AC_WALK_R_8F
	DATA_AC_WalkU_4F_Tbl,									//AC_WALK_U_4F
	DATA_AC_WalkD_4F_Tbl,									//AC_WALK_D_4F
	DATA_AC_WalkL_4F_Tbl,									//AC_WALK_L_4F
	DATA_AC_WalkR_4F_Tbl,									//AC_WALK_R_4F
	DATA_AC_WalkU_2F_Tbl,									//AC_WALK_U_2F
	DATA_AC_WalkD_2F_Tbl,									//AC_WALK_D_2F
	DATA_AC_WalkL_2F_Tbl,									//AC_WALK_L_2F
	DATA_AC_WalkR_2F_Tbl,									//AC_WALK_R_2F
	DATA_AC_StayWalkU_32F_Tbl,								//AC_STAY_WALK_U_32F
	DATA_AC_StayWalkD_32F_Tbl,								//AC_STAY_WALK_D_32F
	DATA_AC_StayWalkL_32F_Tbl,								//AC_STAY_WALK_L_32F
	DATA_AC_StayWalkR_32F_Tbl,								//AC_STAY_WALK_R_32F
	DATA_AC_StayWalkU_16F_Tbl,								//AC_STAY_WALK_U_16F
	DATA_AC_StayWalkD_16F_Tbl,								//AC_STAY_WALK_D_16F
	DATA_AC_StayWalkL_16F_Tbl,								//AC_STAY_WALK_L_16F
	DATA_AC_StayWalkR_16F_Tbl,								//AC_STAY_WALK_R_16F
	DATA_AC_StayWalkU_8F_Tbl,								//AC_STAY_WALK_U_8F
	DATA_AC_StayWalkD_8F_Tbl,								//AC_STAY_WALK_D_8F
	DATA_AC_StayWalkL_8F_Tbl,								//AC_STAY_WALK_L_8F
	DATA_AC_StayWalkR_8F_Tbl,								//AC_STAY_WALK_R_8F
	DATA_AC_StayWalkU_4F_Tbl,								//AC_STAY_WALK_U_4F
	DATA_AC_StayWalkD_4F_Tbl,								//AC_STAY_WALK_D_4F
	DATA_AC_StayWalkL_4F_Tbl,								//AC_STAY_WALK_L_4F
	DATA_AC_StayWalkR_4F_Tbl,								//AC_STAY_WALK_R_4F
	DATA_AC_StayWalkU_2F_Tbl,								//AC_STAY_WALK_U_2F
	DATA_AC_StayWalkD_2F_Tbl,								//AC_STAY_WALK_D_2F
	DATA_AC_StayWalkL_2F_Tbl,								//AC_STAY_WALK_L_2F
	DATA_AC_StayWalkR_2F_Tbl,								//AC_STAY_WALK_R_2F
	DATA_AC_StayJumpU_16F_Tbl,								//AC_STAY_JUMP_U_16F
	DATA_AC_StayJumpD_16F_Tbl,								//AC_STAY_JUMP_D_16F
	DATA_AC_StayJumpL_16F_Tbl,								//AC_STAY_JUMP_L_16F
	DATA_AC_StayJumpR_16F_Tbl,								//AC_STAY_JUMP_R_16F
	DATA_AC_StayJumpU_8F_Tbl,								//AC_STAY_JUMP_U_8F
	DATA_AC_StayJumpD_8F_Tbl,								//AC_STAY_JUMP_D_8F
	DATA_AC_StayJumpL_8F_Tbl,								//AC_STAY_JUMP_L_8F
	DATA_AC_StayJumpR_8F_Tbl,								//AC_STAY_JUMP_R_8F
	DATA_AC_JumpU_1G_8F_Tbl,								//AC_JUMP_U_1G_8F
	DATA_AC_JumpD_1G_8F_Tbl,								//AC_JUMP_D_1G_8F
	DATA_AC_JumpL_1G_8F_Tbl,								//AC_JUMP_L_1G_8F
	DATA_AC_JumpR_1G_8F_Tbl,								//AC_JUMP_R_1G_8F
	DATA_AC_JumpU_2G_16F_Tbl,								//AC_JUMP_U_2G_16F
	DATA_AC_JumpD_2G_16F_Tbl,								//AC_JUMP_D_2G_16F
	DATA_AC_JumpL_2G_16F_Tbl,								//AC_JUMP_L_2G_16F
	DATA_AC_JumpR_2G_16F_Tbl,								//AC_JUMP_R_2G_16F
	DATA_AC_Wait_1F_Tbl,									//AC_WAIT_1F
	DATA_AC_Wait_2F_Tbl,									//AC_WAIT_2F
	DATA_AC_Wait_4F_Tbl,									//AC_WAIT_4F
	DATA_AC_Wait_8F_Tbl,									//AC_WAIT_8F
	DATA_AC_Wait_15F_Tbl,									//AC_WAIT_15F
	DATA_AC_Wait_16F_Tbl,									//AC_WAIT_16F
	DATA_AC_Wait_32F_Tbl,									//AC_WAIT_32F
	DATA_AC_WarpUp_Tbl,										//AC_WARP_UP
	DATA_AC_WarpDown_Tbl,									//AC_WARP_DOWN
	DATA_AC_VanishON_Tbl,									//AC_VANISH_ON
	DATA_AC_VanishOFF_Tbl,									//AC_VANISH_OFF
	DATA_AC_DirPauseON_Tbl,									//AC_DIR_PAUSE_ON
	DATA_AC_DirPauseOFF_Tbl,								//AC_DIR_PAUSE_OFF
	DATA_AC_AnmPauseON_Tbl,									//AC_ANM_PAUSE_ON
	DATA_AC_AnmPauseOFF_Tbl,								//AC_ANM_PAUSE_OFF
	DATA_AC_MarkGyoe_Tbl,									//AC_MARK_GYOE
	DATA_AC_WalkU6F_Tbl,									//AC_WALK_U_6F
	DATA_AC_WalkD6F_Tbl,									//AC_WALK_D_6F
	DATA_AC_WalkL6F_Tbl,									//AC_WALK_L_6F
	DATA_AC_WalkR6F_Tbl,									//AC_WALK_R_6F
	DATA_AC_WalkU3F_Tbl,									//AC_WALK_U_3F
	DATA_AC_WalkD3F_Tbl,									//AC_WALK_D_3F
	DATA_AC_WalkL3F_Tbl,									//AC_WALK_L_3F
	DATA_AC_WalkR3F_Tbl,									//AC_WALK_R_3F
	DATA_AC_WalkU_1F_Tbl,									//AC_WALK_U_1F
	DATA_AC_WalkD_1F_Tbl,									//AC_WALK_D_1F
	DATA_AC_WalkL_1F_Tbl,									//AC_WALK_L_1F
	DATA_AC_WalkR_1F_Tbl,									//AC_WALK_R_1F
	DATA_AC_DashU_4F_Tbl,									//AC_DASH_U_4F
	DATA_AC_DashD_4F_Tbl,									//AC_DASH_D_4F
	DATA_AC_DashL_4F_Tbl,									//AC_DASH_L_4F
	DATA_AC_DashR_4F_Tbl,									//AC_DASH_R_4F
	DATA_AC_JumpHiL_1G_16F_Tbl,								//AC_JUMPHI_L_1G_16F
	DATA_AC_JumpHiR_1G_16F_Tbl,								//AC_JUMPHI_R_1G_16F
	DATA_AC_JumpHiL_3G_32F_Tbl,								//AC_JUMPHI_L_3G_32F
	DATA_AC_JumpHiR_3G_32F_Tbl,								//AC_JUMPHI_R_3G_32F
	DATA_AC_WalkU7F_Tbl,									//AC_WALK_U_7F
	DATA_AC_WalkD7F_Tbl,									//AC_WALK_D_7F
	DATA_AC_WalkL7F_Tbl,									//AC_WALK_L_7F
	DATA_AC_WalkR7F_Tbl,									//AC_WALK_R_7F
	DATA_AC_PcBow_Tbl,										//AC_PC_BOW
	DATA_AC_HidePullOFF_Tbl,								//AC_HIDE_PULLOFF
	DATA_AC_HeroBanzai_Tbl,									//AC_HERO_BANZAI
	DATA_AC_MarkSaisen_Tbl,									//AC_MARK_SAISEN
	DATA_AC_HeroBanzaiUke_Tbl,								//AC_HERO_BANZAI_UKE
};

//==============================================================================
//	フィールドOBJ アニメーションコマンドコード　方向まとめ
//==============================================================================
//--------------------------------------------------------------
///	コード別対応方行テーブル作成。
/// 並びはDIR_UP,DIR_DOWN,DIR_LEFT,DIR_RIGHT
//--------------------------------------------------------------
static const int DATA_CodeTbl_AC_DIR_U[] =
{AC_DIR_U,AC_DIR_D,AC_DIR_L,AC_DIR_R};

static const int DATA_CodeTbl_AC_WALK_U_32F[] =
{AC_WALK_U_32F,AC_WALK_D_32F,AC_WALK_L_32F,AC_WALK_R_32F };

static const int DATA_CodeTbl_AC_WALK_U_16F[] =
{AC_WALK_U_16F,AC_WALK_D_16F,AC_WALK_L_16F,AC_WALK_R_16F };

static const int DATA_CodeTbl_AC_WALK_U_8F[] =
{AC_WALK_U_8F,AC_WALK_D_8F,AC_WALK_L_8F,AC_WALK_R_8F };

static const int DATA_CodeTbl_AC_WALK_U_4F[] =
{AC_WALK_U_4F,AC_WALK_D_4F,AC_WALK_L_4F,AC_WALK_R_4F };

static const int DATA_CodeTbl_AC_WALK_U_2F[] =
{AC_WALK_U_2F,AC_WALK_D_2F,AC_WALK_L_2F,AC_WALK_R_2F };

static const int DATA_CodeTbl_AC_STAY_WALK_U_32F[] =
{AC_STAY_WALK_U_32F,AC_STAY_WALK_D_32F,AC_STAY_WALK_L_32F,AC_STAY_WALK_R_32F };

static const int DATA_CodeTbl_AC_STAY_WALK_U_16F[] =
{AC_STAY_WALK_U_16F,AC_STAY_WALK_D_16F,AC_STAY_WALK_L_16F,AC_STAY_WALK_R_16F };

static const int DATA_CodeTbl_AC_STAY_WALK_U_8F[] =
{AC_STAY_WALK_U_8F,AC_STAY_WALK_D_8F,AC_STAY_WALK_L_8F,AC_STAY_WALK_R_8F };

static const int DATA_CodeTbl_AC_STAY_WALK_U_4F[] =
{AC_STAY_WALK_U_4F,AC_STAY_WALK_D_4F,AC_STAY_WALK_L_4F,AC_STAY_WALK_R_4F };

static const int DATA_CodeTbl_AC_STAY_WALK_U_2F[] =
{AC_STAY_WALK_U_2F,AC_STAY_WALK_D_2F,AC_STAY_WALK_L_2F,AC_STAY_WALK_R_2F };

static const int DATA_CodeTbl_AC_STAY_JUMP_U_16F[] =
{AC_STAY_JUMP_U_16F,AC_STAY_JUMP_D_16F,AC_STAY_JUMP_L_16F,AC_STAY_JUMP_R_16F };

static const int DATA_CodeTbl_AC_STAY_JUMP_U_8F[] =
{AC_STAY_JUMP_U_8F,AC_STAY_JUMP_D_8F,AC_STAY_JUMP_L_8F,AC_STAY_JUMP_R_8F };

static const int DATA_CodeTbl_AC_JUMP_U_1G_8F[] =
{AC_JUMP_U_1G_8F,AC_JUMP_D_1G_8F,AC_JUMP_L_1G_8F,AC_JUMP_R_1G_8F };

static const int DATA_CodeTbl_AC_JUMP_U_2G_16F[] =
{AC_JUMP_U_2G_16F,AC_JUMP_D_2G_16F,AC_JUMP_L_2G_16F,AC_JUMP_R_2G_16F };

static const int DATA_CodeTbl_AC_WALK_U_6F[] =
{AC_WALK_U_6F,AC_WALK_D_6F,AC_WALK_L_6F,AC_WALK_R_6F };

static const int DATA_CodeTbl_AC_WALK_U_3F[] =
{AC_WALK_U_3F,AC_WALK_D_3F,AC_WALK_L_3F,AC_WALK_R_3F };

static const int DATA_CodeTbl_AC_WALK_U_1F[] =
{AC_WALK_U_1F,AC_WALK_D_1F,AC_WALK_L_1F,AC_WALK_R_1F };

static const int DATA_CodeTbl_AC_DASH_U_4F[] =
{AC_DASH_U_4F,AC_DASH_D_4F,AC_DASH_L_4F,AC_DASH_R_4F };

static const int DATA_CodeTbl_AC_JUMPHI_L_1G_16F[] =
{AC_JUMPHI_L_1G_16F,AC_JUMPHI_R_1G_16F,AC_JUMPHI_L_1G_16F,AC_JUMPHI_R_1G_16F};

static const int DATA_CodeTbl_AC_JUMPHI_L_3G_32F[] =
{AC_JUMPHI_L_3G_32F,AC_JUMPHI_R_3G_32F,AC_JUMPHI_L_3G_32F,AC_JUMPHI_R_3G_32F};

static const int DATA_CodeTbl_AC_WALK_U_7F[] =
{AC_WALK_U_7F,AC_WALK_D_7F,AC_WALK_L_7F,AC_WALK_R_7F };

//--------------------------------------------------------------
///	FieldOBJ_AcmdCodeDirChange()で対応するコード。
/// 並びは不順。
//--------------------------------------------------------------
const int * const DATA_AcmdCodeDirChangeTbl[] =
{
	DATA_CodeTbl_AC_DIR_U,
	DATA_CodeTbl_AC_WALK_U_32F,
	DATA_CodeTbl_AC_WALK_U_16F,
	DATA_CodeTbl_AC_WALK_U_8F,
	DATA_CodeTbl_AC_WALK_U_4F,
	DATA_CodeTbl_AC_WALK_U_2F,
	DATA_CodeTbl_AC_STAY_WALK_U_32F,
	DATA_CodeTbl_AC_STAY_WALK_U_16F,
	DATA_CodeTbl_AC_STAY_WALK_U_8F,
	DATA_CodeTbl_AC_STAY_WALK_U_4F,
	DATA_CodeTbl_AC_STAY_WALK_U_2F,
	DATA_CodeTbl_AC_STAY_JUMP_U_16F,
	DATA_CodeTbl_AC_STAY_JUMP_U_8F,
	DATA_CodeTbl_AC_JUMP_U_1G_8F,
	DATA_CodeTbl_AC_JUMP_U_2G_16F,
	DATA_CodeTbl_AC_WALK_U_6F,
	DATA_CodeTbl_AC_WALK_U_3F,
	DATA_CodeTbl_AC_WALK_U_1F,
	DATA_CodeTbl_AC_DASH_U_4F,
	DATA_CodeTbl_AC_JUMPHI_L_1G_16F,
	DATA_CodeTbl_AC_JUMPHI_L_3G_32F,
	DATA_CodeTbl_AC_WALK_U_7F,
	
	NULL,	//終端識別
};

