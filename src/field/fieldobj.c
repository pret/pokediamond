//******************************************************************************
/**
 * 
 * @file	fieldobj.c
 * @brief	フィールドオブジェクト
 * @author	kagaya
 * @data	05.07.13
 *
 */
//******************************************************************************
#include "common.h"
#include "fieldsys.h"
#include "fieldobj.h"

#include "script.h"
#include "map_tool.h"

//==============================================================================
//	define
//==============================================================================
//--------------------------------------------------------------
//	でばっぐ
//--------------------------------------------------------------
#ifdef PM_DEBUG
//#define DEBUG_OBJID_SAM_CHECK		//定義でOBJ ID同一チェック
//#define DEBUG_PRINT_FLDOBJ_COUNT	//定義でOBJ存在数出力
#endif //PM_DEBUG

//--------------------------------------------------------------
///	エイリアスシンボル
//--------------------------------------------------------------
enum
{
	RET_ALIES_NOT = 0,	//エイリアスではない
	RET_ALIES_EXIST,	//エイリアスとして既に存在している
	RET_ALIES_CHANGE,	//エイリアス変更が必要である
};

//==============================================================================
//	struct
//==============================================================================
//--------------------------------------------------------------
///	FIELD_OBJ_SYS構造体
//--------------------------------------------------------------
typedef struct _TAG_FIELD_OBJ_SYS
{
	u32 status_bit;											///<ステータスビット
	int fldobj_max;											///<FIELD_OBJ最大数
	int fldobj_count;										///<フィールドOBJ現在数
	int tcb_pri;											///<TCBプライオリティ
	int blact_idx;											///<ビルボードアクターインデックス
	ARCHANDLE *archandle;									///<アーカイブハンドル
	FIELD_OBJ_BLACT_CONT blact_cont;						///<FIELD_OBJ_BLACT_CONT
	FIELD_OBJ_RENDER_CONT_PTR render_cont;					///<FIELD_OBJ_RENDER_CONT
	FIELD_OBJ_PTR fldobj_work;								///<FIELD_OBJワーク *
	FIELDSYS_WORK *fieldsys;								///<FIELDSYS_WORK *
}FIELD_OBJ_SYS;

#define FIELD_OBJ_SYS_SIZE (sizeof(FIELD_OBJ_SYS))			///<FIELD_OBJ_SYSサイズ

//--------------------------------------------------------------
///	FIELD_OBJ構造体
//--------------------------------------------------------------
typedef struct _TAG_FIELD_OBJ
{
	u32 status_bit;											///<ステータスビット
	u32 move_bit;											///<動作ビット
	u32 obj_id;												///<OBJ ID
	u32 zone_id;											///<ゾーン ID
	u32 obj_code;											///<OBJコード
	u32 move_code;											///<動作コード
	u32 event_type;											///<イベントタイプ
	u32 event_flag;											///<イベントフラグ
	u32 event_id;											///<イベントID
	int dir_head;											///<FIELD_OBJ_H指定方向
	int dir_disp;											///<現在向いている方向
	int dir_move;											///<現在動いている方向
	int dir_disp_old;										///<過去の動いていた方向
	int dir_move_old;										///<過去の動いていた方向
	int param0;												///<ヘッダ指定パラメタ
	int param1;												///<ヘッダ指定パラメタ
	int param2;												///<ヘッダ指定パラメタ
	int move_limit_x;										///<X方向移動制限
	int move_limit_z;										///<Z方向移動制限
	int gx_init;											///<初期グリッドX
	int gy_init;											///<初期グリッドY
	int gz_init;											///<初期グリッドZ
	int gx_old;												///<過去グリッドX
	int gy_old;												///<過去グリッドY
	int gz_old;												///<過去グリッドZ
	int gx_now;												///<現在グリッドX
	int gy_now;												///<現在グリッドY
	int gz_now;												///<現在グリッドZ
	VecFx32 vec_pos_now;									///<現在実数座標
	VecFx32 vec_draw_offs;									///<表示座標オフセット
	VecFx32 vec_draw_offs_outside;							///<外部指定表示座標オフセット
	VecFx32 vec_attr_offs;								///<アトリビュートによる座標オフセット
	u32 draw_status;										///<描画ステータス
	int acmd_code;											///<アニメーションコマンドコード
	int acmd_seq;											///<アニメーションコマンドシーケンス
	u16 now_attr;											///<現在のマップアトリビュート
	u16 old_attr;											///<過去のマップアトリビュート
	
	TCB_PTR tcb;											///<動作関数TCB*
	CONST_FIELD_OBJ_SYS_PTR fldobj_sys;						///<FIELD_OBJ_SYSへの *
	
	FIELD_OBJ_MOVE_PROC_INIT move_init_proc;				///<初期化関数
	FIELD_OBJ_MOVE_PROC move_proc;							///<動作関数
	FIELD_OBJ_MOVE_PROC_DEL move_delete_proc;				///<削除関数
	FIELD_OBJ_DRAW_PROC_INIT draw_init_proc;				///<描画初期化関数
	FIELD_OBJ_DRAW_PROC draw_proc;							///<描画関数
	FIELD_OBJ_DRAW_PROC_DEL draw_delete_proc;				///<描画削除関数
	FIELD_OBJ_DRAW_PROC_PUSH draw_push_proc;				///<描画退避関数
	FIELD_OBJ_DRAW_PROC_POP draw_pop_proc;					///<描画復帰関数
	
	u8 move_proc_work[FLDOBJ_MOVE_WORK_SIZE];				///<動作関数用ワーク
	u8 move_sub_proc_work[FLDOBJ_MOVE_SUB_WORK_SIZE];		///<動作サブ関数用ワーク
	u8 move_cmd_proc_work[FLDOBJ_MOVE_CMD_WORK_SIZE];		///<動作コマンド用ワーク
	u8 draw_proc_work[FLDOBJ_DRAW_WORK_SIZE];				///<描画関数用ワーク
}FIELD_OBJ;

#define FIELD_OBJ_SIZE (sizeof(FIELD_OBJ))					///<FIELD_OBJサイズ

//--------------------------------------------------------------
///	FIELD_OBJ_H_LOAD_FILE構造体
//--------------------------------------------------------------
typedef struct
{
	int zone;
	int add_max;											//登録最大数
	int add_count;											//追加数
	CONST_FIELD_OBJ_SYS_PTR sys;							//FIELD_OBJ_SYS_PTR 
	FIELD_OBJ_H *head;										//ヘッダー
}FIELD_OBJ_H_LOAD_FILE;
															///FIELD_OBJ_H_LOAD_FILEサイズ
#define FIELD_OBJ_H_LOAD_FILE_SIZE (sizeof(FIELD_OBJ_H_LOAD_FILE))

//==============================================================================
//	プロトタイプ
//==============================================================================
static FIELD_OBJ_SYS_PTR  FldOBJSys_AllocMemory( int max );

static void FldOBJ_SaveDataSave( FIELDSYS_WORK *fsys, FIELD_OBJ_PTR fldobj, FIELD_OBJ_SAVE_DATA_PTR save );
static void FldOBJ_SaveDataLoad( FIELD_OBJ_PTR fldobj, FIELD_OBJ_SAVE_DATA_PTR save );
static void FldOBJ_DataLoadRecover( CONST_FIELD_OBJ_SYS_PTR fos, FIELD_OBJ_PTR fldobj );
static void FldOBJ_DataLoadStatusBitRecover( FIELD_OBJ_PTR fldobj );
static void FldOBJ_DataLoadPosRecover( FIELD_OBJ_PTR fldobj );

static void FldOBJ_AddFileProc( FIELD_OBJ_H_LOAD_FILE *work );

static FIELD_OBJ_PTR  FldOBJ_SpaceSearch( CONST_FIELD_OBJ_SYS_PTR sys );
static FIELD_OBJ_PTR  FldOBJ_AliesSearch( CONST_FIELD_OBJ_SYS_PTR fos, int obj_id,int zone_id );
static void FldOBJ_MoveTcbAdd( CONST_FIELD_OBJ_SYS_PTR sys, FIELD_OBJ_PTR fldobj );
static void FldOBJ_AddHeaderSet(
		FIELD_OBJ_PTR fldobj, const FIELD_OBJ_H *head, FIELDSYS_WORK *fsys );
static void FldOBJ_AddHeaderPosInit( FIELD_OBJ_PTR fldobj, const FIELD_OBJ_H *head );
static void FldOBJ_WorkInit( FIELD_OBJ_PTR fldobj, CONST_FIELD_OBJ_SYS_PTR sys );
static void FldOBJ_WorkInit_MoveProcInit( FIELD_OBJ_PTR fldobj );
static void FldOBJ_WorkInit_DrawProcInit( FIELD_OBJ_PTR fldobj );
static void FldOBJ_WorkClear( FIELD_OBJ_PTR fldobj );
static int FldOBJ_HeaderAliesCheck(
		CONST_FIELD_OBJ_PTR fldobj, int h_zone_id, int max, const FIELD_OBJ_H *head );
static FIELD_OBJ_PTR FldOBJ_OBJIDZoneIDSearch(
		CONST_FIELD_OBJ_SYS_PTR fos, int obj_id, int zone_id );
static void FldOBJ_DeleteAll_OldZoneID( FIELD_OBJ_SYS_PTR fos, u32 zone_id );
static void FldOBJ_DrawInitStatusSet( FIELD_OBJ_PTR fldobj );
static void FldOBJ_DrawEffectFlagInit( FIELD_OBJ_PTR fldobj );
static void FldOBJ_DrawDeleteStatusSet( FIELD_OBJ_PTR fldobj );
static int FldOBJ_OBJCodeWkOBJCodeConv( FIELDSYS_WORK *fsys, int code );
static void FldOBJ_HeightNeedCheckInit( FIELD_OBJ_PTR fldobj );
static void FldOBJ_MoveWorkInit( FIELD_OBJ_PTR fldobj );
static void FldOBJ_DrawWorkInit( FIELD_OBJ_PTR fldobj );
static void FldOBJ_AliesOBJChange( FIELD_OBJ_PTR fldobj, const FIELD_OBJ_H *head, int zone_id );
static void FldOBJ_OBJAliesChange( FIELD_OBJ_PTR fldobj, int zone_id, const FIELD_OBJ_H *head );

static void FldOBJ_TCB_MoveProc( TCB_PTR tcb, void *work );
static void FldOBJ_TCB_DrawProc( FIELD_OBJ_PTR fldobj );

static FIELD_OBJ_SYS_PTR  FldOBJ_ConstSysLocalGet( CONST_FIELD_OBJ_SYS_PTR sys );
static void FldOBJSys_OBJCountInc( FIELD_OBJ_SYS_PTR sys );
static void FldOBJSys_OBJCountDec( FIELD_OBJ_SYS_PTR sys );
static void FldOBJSys_OBJCountSet( FIELD_OBJ_SYS_PTR sys, int count );
static FIELD_OBJ_PTR FldOBJSys_FieldOBJWorkGet( CONST_FIELD_OBJ_SYS_PTR sys );

static FIELD_OBJ_SYS_PTR  FldOBJ_FieldOBJSysGet( CONST_FIELD_OBJ_PTR fldobj );

static const FIELD_OBJ_H * FldOBJ_H_OBJIDSearch( int id, int max, const FIELD_OBJ_H *head );
static int FldOBJ_H_AliesCheck( const FIELD_OBJ_H *head );
static int FldOBJ_H_AliesZoneIDGet( const FIELD_OBJ_H *head );

static const FIELD_OBJ_MOVE_PROC_LIST * FldOBJ_MoveProcListGet( u32 code );
static FIELD_OBJ_MOVE_PROC_INIT FldOBJ_MoveProcList_InitGet(
		const FIELD_OBJ_MOVE_PROC_LIST *list );
static FIELD_OBJ_MOVE_PROC FldOBJ_MoveProcList_MoveGet(
		const FIELD_OBJ_MOVE_PROC_LIST *list );
static FIELD_OBJ_MOVE_PROC_DEL FldOBJ_MoveProcList_DeleteGet(
		const FIELD_OBJ_MOVE_PROC_LIST *list );
static FIELD_OBJ_DRAW_PROC_PUSH FldOBJ_DrawProcList_PushGet(
		const FIELD_OBJ_DRAW_PROC_LIST *list );
static FIELD_OBJ_DRAW_PROC_POP FldOBJ_DrawProcList_PopGet(
		const FIELD_OBJ_DRAW_PROC_LIST *list );

static FIELD_OBJ_DRAW_PROC_INIT FldOBJ_DrawProcList_InitGet(
	const FIELD_OBJ_DRAW_PROC_LIST *list );
static FIELD_OBJ_DRAW_PROC FldOBJ_DrawProcList_DrawGet( const FIELD_OBJ_DRAW_PROC_LIST *list );
static FIELD_OBJ_DRAW_PROC_DEL FldOBJ_DrawProcList_DeleteGet(
		const FIELD_OBJ_DRAW_PROC_LIST *list );
static const FIELD_OBJ_DRAW_PROC_LIST * FldOBJ_DrawProcListGet( u32 code );

//==============================================================================
//	フィールドOBJ	システム
//==============================================================================
//--------------------------------------------------------------
/**
 * FIELD OBJ システム初期化
 * @param		fsys			FIELDSYS_WORK *
 * @param		max 			処理するOBJ最大数
 * @param		pri				フィールドOBJの基本TCBプライオリティ
 * @retval		FIELD_OBJ_SYS*	追加されたフィールドOBJ*
 */
//--------------------------------------------------------------
FIELD_OBJ_SYS_PTR FieldOBJSys_Init( FIELDSYS_WORK *fsys, int max, int pri )
{
	FIELD_OBJ_SYS_PTR fos;
	
	fos = FldOBJSys_AllocMemory( max );
	FieldOBJSys_FieldSysWorkSet( fos, fsys );
	FieldOBJSys_OBJMaxSet( fos, max );
	FieldOBJSys_TCBStandardPrioritySet( fos, pri );
	
//	OS_Printf( "OLD FIELD_OBJ_SAVE_DATA_SIZE %x\n", FIELD_OBJ_SAVE_DATA_OLD_SIZE );
//	OS_Printf( "NEW FIELD_OBJ_SAVE_DATA_SIZE %x\n", FIELD_OBJ_SAVE_DATA_SIZE );
	
	return( fos );
}

//--------------------------------------------------------------
/**
 * FIELD OBJ システム削除
 * @param	fos		FIELD_OBJ_SYS_PTR 
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJSys_Delete( FIELD_OBJ_SYS_PTR fos )
{
	sys_FreeMemory( HEAPID_WORLD, FieldOBJSys_FldOBJWorkGet(fos) );
	sys_FreeMemory( HEAPID_WORLD, fos );
}

//--------------------------------------------------------------
/**
 * FIELD OBJ　全てを削除
 * @param	fos		FIELD_OBJ_SYS_PTR 
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJSys_DeleteAll( FIELD_OBJ_SYS_PTR fos )
{
	FieldOBJ_DeleteAll( fos );
	FieldOBJSys_DrawDelete( fos );
	FieldOBJSys_Delete( fos );
	
	OS_Printf( "フィールドOBJ 全てを削除しました\n" );
}

//--------------------------------------------------------------
/**
 * FIELD OBJ　ゾーン更新時の削除処理
 * @param	sys		FIELD_OBJ_SYS_PTR 
 * @param	old_zone	古いゾーンID
 * @param	new_zone	新しいゾーンID
 * @param	head_max	head要素数
 * @param	head	新しいのゾーンに配置するFIELD_OBJ_H *
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJSys_ZoneUpdateDelete( FIELD_OBJ_SYS_PTR fos,
		int old_zone, int new_zone, int head_max, const FIELD_OBJ_H *head )
{
	int ret,max = FieldOBJSys_OBJMaxGet( fos );
	FIELD_OBJ_PTR fldobj = FieldOBJSys_FldOBJWorkGet( fos );
	
	OS_Printf( "古いZoneに配置されたフィールドOBJ　削除開始\n" );
	
	while( max ){
		if( FieldOBJ_StatusBitCheck_Use(fldobj) == TRUE ){
			ret = FldOBJ_HeaderAliesCheck( fldobj, new_zone, head_max, head );
			
			switch( ret ){
			case RET_ALIES_NOT:
				if( FieldOBJ_ZoneIDGet(fldobj) != new_zone ){
					if( FieldOBJ_StatusBit_CheckEasy(
							fldobj,FLDOBJ_STA_BIT_ZONE_DEL_NOT) == FALSE ){
						FieldOBJ_Delete( fldobj );
					}
				}
				
				break;
			case RET_ALIES_CHANGE:
				OS_Printf(
					"エイリアス対象のOBJあり OBJ_ID=%d ZONE_ID=%d GRID X=%d,GRID Z=%d \n",
					FieldOBJ_OBJIDGet(fldobj),
					new_zone,
					FieldOBJ_NowPosGX_Get(fldobj), FieldOBJ_NowPosGZ_Get(fldobj) );
				break;
			case RET_ALIES_EXIST:
				OS_Printf( "エイリアス対象のOBJが既にエイリアス化しています " );
				OS_Printf( "OBJ_ID=%d ", FieldOBJ_OBJIDGet(fldobj) );
				OS_Printf( "ZONE_ID=%d ", FieldOBJ_ZoneIDGetAlies(fldobj) );
				OS_Printf( "追加中のゾーンID=%d ", new_zone );
				OS_Printf( "GRID X=%d, ", FieldOBJ_NowPosGX_Get(fldobj) );
				OS_Printf( "GRID Z=%d\n", FieldOBJ_NowPosGZ_Get(fldobj) );
				break;
			}
		}
		
		fldobj++;
		max--;
	}
	
	FieldOBJ_BlActCont_ResmGuestDeleteAll( fos, FieldOBJSys_BlActContGet(fos) );
	OS_Printf( "古いZoneに配置されたフィールドOBJ　削除完了\n" );
}

//==============================================================================
//	フィールドOBJシステム　パーツ
//==============================================================================
//--------------------------------------------------------------
/**
 * FIELD OBJ 作業領域確保
 * @param	max				処理するOBJ最大数
 * @retval	FIELD_OBJ_SYS	確保した領域*
 */
//--------------------------------------------------------------
static FIELD_OBJ_SYS_PTR FldOBJSys_AllocMemory( int max )
{
	int size;
	FIELD_OBJ_PTR fldobj;
	FIELD_OBJ_SYS_PTR fos;
	
	fos = sys_AllocMemory( HEAPID_WORLD, FIELD_OBJ_SYS_SIZE );
	
	GF_ASSERT( fos != NULL && "fldobj sys alloc memory error" );
	memset( fos, 0, FIELD_OBJ_SYS_SIZE );
	
	size = FIELD_OBJ_SIZE * max;
	fldobj = sys_AllocMemory( HEAPID_WORLD, size );
	
	GF_ASSERT( fldobj != NULL && "fldobj alloc memory error" );
	memset( fldobj, 0, size );
	
	FieldOBJSys_FieldOBJWorkSet( fos, fldobj );
	
	return( fos );
}

//==============================================================================
//	フィールドOBJ
//==============================================================================
//--------------------------------------------------------------
/**
 * フィールドOBJを追加 引数ヘッダー
 * @param	fos			FIELD_OBJ_SYS_PTR 
 * @param	head		追加する情報を纏めたFIELD_OBJ_H *
 * @param	zone_id		ゾーンID
 * @retval	FIELD_OBJ	追加されたFIELD_OBJ_PTR 。NULL=追加不可
 */
//--------------------------------------------------------------
FIELD_OBJ_PTR FieldOBJ_AddH( CONST_FIELD_OBJ_SYS_PTR fos, const FIELD_OBJ_H *head, int zone_id )
{
	FIELD_OBJ_PTR fldobj;
	
	{
		int obj_id = FieldOBJ_H_IDGet( head );
		
		if( FldOBJ_H_AliesCheck(head) == FALSE ){				//エイリアスではない
			fldobj = FldOBJ_AliesSearch( fos, obj_id, zone_id );
			
			if( fldobj != NULL ){								//エイリアスで既に存在している
				FldOBJ_AliesOBJChange( fldobj, head, zone_id );	//エイリアスからフィールドOBJへ
				OS_Printf( "エイリアス -> フィールドOBJ OBJ_ID %d ", obj_id );
				OS_Printf( "GIRD X=%d ", FieldOBJ_H_PosXGet(head) );
				OS_Printf( "GIRD Z=%d\n", FieldOBJ_H_PosZGet(head) );
				return( fldobj );
			}
		}else{													//エイリアスである
			fldobj = FldOBJ_OBJIDZoneIDSearch( fos, obj_id, FldOBJ_H_AliesZoneIDGet(head) );
			
			if( fldobj != NULL ){								//既にフィールドOBJが存在する
				FldOBJ_OBJAliesChange( fldobj, zone_id, head );	//フィールドOBJからエイリアスへ
				OS_Printf( "フィールドOBJ -> エイリアス OBJ_ID %d ", obj_id );
				OS_Printf( "GIRD X=%d ", FieldOBJ_H_PosXGet(head) );
				OS_Printf( "GIRD Z=%d\n", FieldOBJ_H_PosZGet(head) );
				return( fldobj );
			}
			
			OS_Printf( "エイリアスが配置されます " );
			OS_Printf( "ZONE_ID %d, OBJ_ID %d ", obj_id, FldOBJ_H_AliesZoneIDGet(head) );
			OS_Printf( "GIRD X=%d ", FieldOBJ_H_PosXGet(head) );
			OS_Printf( "GIRD Z=%d\n", FieldOBJ_H_PosZGet(head) );
		}
	}
	
	fldobj = FldOBJ_SpaceSearch( fos );
	
	if( fldobj == NULL ){
		return( fldobj );
	}
	
	FldOBJ_AddHeaderSet( fldobj, head, FieldOBJSys_FieldSysWorkGet(fos) );
	FldOBJ_WorkInit( fldobj, fos );
	FieldOBJ_ZoneIDSet( fldobj, zone_id );
	
	FldOBJ_MoveWorkInit( fldobj );
	FldOBJ_DrawWorkInit( fldobj );
	
	FieldOBJ_StatusBit_ON( fldobj, FLDOBJ_STA_BIT_MOVE_START );
	
	FldOBJ_MoveTcbAdd( fos, fldobj );
	FldOBJSys_OBJCountInc( FldOBJ_ConstSysLocalGet(fos) );
	
	return( fldobj );
}

//--------------------------------------------------------------
/**
 * フィールドOBJを追加。最低限必要な情報からヘッダー作成して追加。
 * 足りない情報は0でクリアされている。必要あれば追加後に各自で自由に設定。
 * @param	fos			FIELD_OBJ_SYS_PTR 
 * @param	x			初期グリッド座標X
 * @param	z			初期グリッド座標Z
 * @param	dir			初期方向。DIR_UP等
 * @param	obj			OBJコード。HERO等
 * @param	move		動作コード。MV_RND等
 * @param	zone_id		ゾーンID ZONE_ID_NOTHING等
 * @retval	FIELD_OBJ	追加されたFIELD_OBJ_PTR 。NULL=追加不可
 */
//--------------------------------------------------------------
FIELD_OBJ_PTR FieldOBJ_AddHMake(
		CONST_FIELD_OBJ_SYS_PTR fos, int x, int z, int dir, int obj, int move, int zone_id )
{
	FIELD_OBJ_H head;
	FIELD_OBJ_PTR fldobj;
	
	FieldOBJ_H_IDSet( &head, 0 );
	FieldOBJ_H_OBJCodeSet( &head, obj );
	FieldOBJ_H_MoveCodeSet( &head, move );
	FieldOBJ_H_EventTypeSet( &head, 0 );
	FieldOBJ_H_EventFlagSet( &head, 0 );
	FieldOBJ_H_EventIDSet( &head, 0 );
	FieldOBJ_H_DirSet( &head, dir );
	FieldOBJ_H_ParamSet( &head, 0, FLDOBJ_PARAM_0 );
	FieldOBJ_H_ParamSet( &head, 0, FLDOBJ_PARAM_1 );
	FieldOBJ_H_ParamSet( &head, 0, FLDOBJ_PARAM_2 );
	FieldOBJ_H_MoveLimitXSet( &head, 0 );
	FieldOBJ_H_MoveLimitZSet( &head, 0 );
	FieldOBJ_H_PosXSet( &head, x );
	FieldOBJ_H_PosZSet( &head, z );
	FieldOBJ_H_PosYSet( &head, 0 );
	
	fldobj = FieldOBJ_AddH( fos, &head, zone_id );
	
	return( fldobj );
}

//--------------------------------------------------------------
/**
 * FIELD_OBJ_Hテーブルより指定のIDを持ったOBJを追加
 * @param	fos		FIELD_OBJ_SYS_PTR
 * @param	id		追加するhead検索ID
 * @param	zone	追加の際に指定するゾーンID
 * @param	max		head要素数
 * @param	head	FIELD_OBJ_H *
 * @retval	FIELD_OBJ_PTR	追加されたFIELD_OBJ_PTR NULL=id該当無し
 */
//--------------------------------------------------------------
FIELD_OBJ_PTR FieldOBJ_AddHEvent(
		CONST_FIELD_OBJ_SYS_PTR fos, int id, int max, int zone, const FIELD_OBJ_H *head )
{
	FIELD_OBJ_PTR fldobj = NULL;
	const FIELD_OBJ_H *hit_head = FldOBJ_H_OBJIDSearch( id, max, head );
	
	if( hit_head != NULL ){
		int flag = FieldOBJ_H_EventFlagGet( hit_head );
		FIELDSYS_WORK *fsys = FieldOBJSys_FieldSysWorkGet( fos );
		
		if( CheckEventFlag(fsys,flag) == FALSE ){
			fldobj = FieldOBJ_AddH( fos, hit_head, zone );
		}
	}
	
	return( fldobj );
}

//--------------------------------------------------------------
/**
 * FIELD OBJ　表示系のみ再設定　削除は行わない
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	code	OBJコード HERO等
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_DrawResetAlone( FIELD_OBJ_PTR fldobj, int code )
{
#ifdef PM_DEBUG
	{	//描画システム初期化完了していない
		CONST_FIELD_OBJ_SYS_PTR fos = FieldOBJ_FieldOBJSysGet( fldobj );
		GF_ASSERT( FieldOBJSys_DrawInitCompCheck(fos) != FALSE &&
			"FieldOBJ_DrawReset() DRAW SYS NOT INIT" );
	}
#endif
	
	FieldOBJ_OBJCodeSet( fldobj, code );
	FldOBJ_DrawInitStatusSet( fldobj );
	FieldOBJ_StatusBit_OFF( fldobj, FLDOBJ_STA_BIT_DRAW_PROC_INIT_COMP );
	FldOBJ_DrawWorkInit( fldobj );
}

//--------------------------------------------------------------
/**
 * FIELD OBJ　現在の描画関数を削除して再設定
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	code	OBJコード HERO等
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_DrawReset( FIELD_OBJ_PTR fldobj, int code )
{
	if( FieldOBJ_StatusBit_DrawInitCompCheck(fldobj) == TRUE ){
		FieldOBJ_DrawDelete( fldobj );
	}
	
	FieldOBJ_DrawResetAlone( fldobj, code );
}

//--------------------------------------------------------------
/**
 * フィールドOBJを削除
 * @param	fldobj		削除するFIELD_OBJ_PTR 
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_Delete( FIELD_OBJ_PTR fldobj )
{
	CONST_FIELD_OBJ_SYS_PTR fos;
	
	fos = FieldOBJ_FieldOBJSysGet( fldobj );
	
	if( FieldOBJSys_DrawInitCompCheck(fos) == TRUE ){
		FieldOBJ_DrawDeleteProcCall( fldobj );
	}
	
	FieldOBJ_MoveDeleteProcCall( fldobj );
	FieldOBJ_MoveTcbDelete( fldobj );
	FldOBJSys_OBJCountDec( FldOBJ_FieldOBJSysGet(fldobj) );
	FldOBJ_WorkClear( fldobj );
}

//--------------------------------------------------------------
/**
 * フィールドOBJを削除　スクリプトのOBJ削除フラグをONにする
 * @param	fldobj		削除するFIELD_OBJ_PTR 
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_DeleteEvent( FIELD_OBJ_PTR fldobj )
{
	int ev;
	
	ev = FieldOBJ_EventFlagGet( fldobj );
	SetEventFlag( FieldOBJ_FieldSysWorkGet(fldobj), ev );
	FieldOBJ_Delete( fldobj );
}

//--------------------------------------------------------------
/**
 * FIELD OBJ　表示系のみ削除
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_DrawDelete( FIELD_OBJ_PTR fldobj )
{
	CONST_FIELD_OBJ_SYS_PTR fos;
	
	fos = FieldOBJ_FieldOBJSysGet( fldobj );
	
	if( FieldOBJSys_DrawInitCompCheck(fos) == TRUE ){
		if( FieldOBJ_StatusBit_Check(fldobj,FLDOBJ_STA_BIT_DRAW_PROC_INIT_COMP) ){
			FieldOBJ_DrawDeleteProcCall( fldobj );
		}
		
		FieldOBJ_StatusBit_OFF( fldobj, FLDOBJ_STA_BIT_DRAW_PROC_INIT_COMP );
	}
	
	FieldOBJ_OBJCodeSet( fldobj, OBJCODEMAX );
	
	FieldOBJ_DrawInitProcSet( fldobj, FieldOBJ_DrawInitProcDummy );
	FieldOBJ_DrawProcSet( fldobj, FieldOBJ_DrawProcDummy );
	FieldOBJ_DrawDeleteProcSet( fldobj, FieldOBJ_DrawProcDummy );
	FieldOBJ_DrawPushProcSet( fldobj, FieldOBJ_DrawPushProcDummy );
	FieldOBJ_DrawPopProcSet( fldobj, FieldOBJ_DrawPopProcDummy );
}

//--------------------------------------------------------------
/**
 * 現在発生しているフィールドOBJを全て削除
 * @param	fldobj		削除するFIELD_OBJ_PTR 
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_DeleteAll( FIELD_OBJ_SYS_PTR fos )
{
	int i,max;
	FIELD_OBJ_PTR fldobj;
	
	i = 0;
	max = FieldOBJSys_OBJMaxGet( fos );
	fldobj = FieldOBJSys_FldOBJWorkGet( fos );
	
	do{
		if( FieldOBJ_StatusBit_Check(fldobj,FLDOBJ_STA_BIT_USE) ){
			FieldOBJ_Delete( fldobj );
		}
		
		fldobj++;
		i++;
	}while( i < max );
}

//--------------------------------------------------------------
/**
 * 現在発生しているフィールドOBJ全てを退避
 * @param	fldobj		削除するFIELD_OBJ_PTR 
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_PushAll( FIELD_OBJ_SYS_PTR fos )
{
	int i,max;
	FIELD_OBJ_PTR fldobj;
	
	i = 0;
	max = FieldOBJSys_OBJMaxGet( fos );
	fldobj = FieldOBJSys_FldOBJWorkGet( fos );
	
	do{
		if( FieldOBJ_StatusBit_Check(fldobj,FLDOBJ_STA_BIT_USE) ){
			if( FieldOBJ_StatusBitCheck_DrawProcInitComp(fldobj) == TRUE ){
				FieldOBJ_DrawPushProcCall( fldobj );
			}
		}
		
		fldobj++;
		i++;
	}while( i < max );
}

//--------------------------------------------------------------
/**
 * 現在発生しているフィールドOBJ全てにたいして描画処理の退避を行う
 * @param	fos		FIELD_OBJ_SYS_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_DrawProcPushAll( FIELD_OBJ_SYS_PTR fos )
{
	GF_ASSERT( FieldOBJSys_DrawInitCompCheck(fos) == TRUE &&
		"FLDOBJ 描画処理が存在していないのにFieldOBJ_DrawProcPushAll()が呼ばれています" );
	
	{
		int i,max;
		FIELD_OBJ_PTR fldobj;
	
		i = 0;
		max = FieldOBJSys_OBJMaxGet( fos );
		fldobj = FieldOBJSys_FldOBJWorkGet( fos );
	
		do{
			if( FieldOBJ_StatusBit_Check(fldobj,FLDOBJ_STA_BIT_USE) ){
				if( FieldOBJ_StatusBit_Check(fldobj,FLDOBJ_STA_BIT_DRAW_PROC_INIT_COMP) ){
					FieldOBJ_DrawPushProcCall( fldobj );
					FldOBJ_DrawDeleteStatusSet( fldobj );
				}
			}
		
			fldobj++;
			i++;
		}while( i < max );
	}
	
	OS_Printf( "フィールドOBJ 描画情報を退避しました\n" );
}

//--------------------------------------------------------------
/**
 * 現在発生しているフィールドOBJ全てを復帰
 * @param	fldobj		削除するFIELD_OBJ_PTR 
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_PopAll( FIELD_OBJ_SYS_PTR fos )
{
	int i,max;
	FIELD_OBJ_PTR fldobj;
	
	i = 0;
	max = FieldOBJSys_OBJMaxGet( fos );
	fldobj = FieldOBJSys_FldOBJWorkGet( fos );
	
	do{
		if( FieldOBJ_StatusBitCheck_Use(fldobj) == TRUE ){
			if( FieldOBJ_StatusBitCheck_DrawProcInitComp(fldobj) == TRUE ){
				FieldOBJ_DrawPopProcCall( fldobj );
			}
		}
	
		fldobj++;
		i++;
	}while( i < max );
}

//--------------------------------------------------------------
/**
 * 現在発生しているフィールドOBJ全てに対して描画処理復帰
 * @param	fldobj		削除するFIELD_OBJ_PTR 
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_DrawProcPopAll( FIELD_OBJ_SYS_PTR fos )
{
	GF_ASSERT( FieldOBJSys_DrawInitCompCheck(fos) == TRUE &&
		"FLDOBJ 描画処理未初期化で描画復帰処理が呼ばれています" );
	
	{
		int i = 0;
		int max = FieldOBJSys_OBJMaxGet( fos );
		FIELD_OBJ_PTR fldobj = FieldOBJSys_FldOBJWorkGet( fos );
	
		do{
			if( FieldOBJ_StatusBitCheck_Use(fldobj) == TRUE ){
				if( FieldOBJ_StatusBitCheck_DrawProcInitComp(fldobj) == TRUE ){
					FieldOBJ_DrawPopProcCall( fldobj );
				}else{
					FldOBJ_DrawWorkInit( fldobj );
				}
				
				FldOBJ_DrawInitStatusSet( fldobj );
			}
		
			fldobj++;
			i++;
		}while( i < max );
	}
	
	OS_Printf( "フィールドOBJ 描画情報を復帰しました\n" );
}

//==============================================================================
//	フィールドOBJ セーブ
//==============================================================================
//--------------------------------------------------------------
/**
 * 現在発生しているフィールドOBJ全てをセーブデータに保存
 * @param	fos		FIELD_OBJ_SYS_PTR
 * @param	save	保存先FIELD_OBJ_SAVE_DATA_PTR
 * @param	max		saveの要素数
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJSys_DataSaveAll(
		FIELDSYS_WORK *fsys, CONST_FIELD_OBJ_SYS_PTR fos, FIELD_OBJ_SAVE_DATA_PTR save, int max )
{
	int no = 0;
	FIELD_OBJ_PTR fldobj;
	
	while( FieldOBJSys_FieldOBJSearch(fos,&fldobj,&no,FLDOBJ_STA_BIT_USE) ){
		FldOBJ_SaveDataSave( fsys, fldobj, save );
		save++; max--;
		GF_ASSERT( max > 0 && "FieldOBJSys_DataSaveAll()異常" );
	}
	
	if( max ){
		memset( save, 0, max * FIELD_OBJ_SAVE_DATA_SIZE );
	}
}

//--------------------------------------------------------------
/**
 * セーブしたデータをロード
 * @param	fos		FIELD_OBJ_SYS_PTR
 * @param	save	保存したデータが格納されたFIELD_OBJ_SAVE_DATA_PTR
 * @param	max		saveの要素数
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJSys_DataLoadAll(
		CONST_FIELD_OBJ_SYS_PTR fos, FIELD_OBJ_SAVE_DATA_PTR save, int max )
{
	int i = 0;
	FIELD_OBJ_PTR fldobj;
	
	while( max ){
		if( (save->status_bit & FLDOBJ_STA_BIT_USE) ){
			fldobj = FldOBJ_SpaceSearch( fos );
			GF_ASSERT( fldobj != NULL && "FieldOBJSys_DataLoadAll()異常" );
		
			FldOBJ_SaveDataLoad( fldobj, save );
			FldOBJ_DataLoadRecover( fos, fldobj );
		}
		
		save++;
		max--;
	}
}

//--------------------------------------------------------------
/**
 * フィールドOBJの情報をセーブデータにセット
 * @param	fldobj		FIELD_OBJ_PTR
 * @param	save		FIELD_OBJ_SAVE_DATA_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FldOBJ_SaveDataSave( FIELDSYS_WORK *fsys, FIELD_OBJ_PTR fldobj, FIELD_OBJ_SAVE_DATA_PTR save )
{
	save->status_bit = FieldOBJ_StatusBit_Get( fldobj );
	save->move_bit = FieldOBJ_MoveBit_Get( fldobj );
	save->obj_id = FieldOBJ_OBJIDGet( fldobj );
	save->zone_id = FieldOBJ_ZoneIDGet( fldobj );
	save->obj_code = FieldOBJ_OBJCodeGet( fldobj );
	save->move_code = FieldOBJ_MoveCodeGet( fldobj );
	save->event_type = FieldOBJ_EventTypeGet( fldobj );
	save->event_flag = FieldOBJ_EventFlagGet( fldobj );
	save->event_id = FieldOBJ_EventIDGet( fldobj );
	save->dir_head = FieldOBJ_DirHeaderGet( fldobj );
	save->dir_disp = FieldOBJ_DirDispGet( fldobj );
	save->dir_move = FieldOBJ_DirMoveGet( fldobj );
	save->param0 = FieldOBJ_ParamGet( fldobj, FLDOBJ_PARAM_0 );
	save->param1 = FieldOBJ_ParamGet( fldobj, FLDOBJ_PARAM_1 );
	save->param2 = FieldOBJ_ParamGet( fldobj, FLDOBJ_PARAM_2 );
	save->move_limit_x = FieldOBJ_MoveLimitXGet( fldobj );
	save->move_limit_z = FieldOBJ_MoveLimitZGet( fldobj );
	save->gx_init = FieldOBJ_InitPosGX_Get( fldobj );
	save->gy_init = FieldOBJ_InitPosGY_Get( fldobj );
	save->gz_init = FieldOBJ_InitPosGZ_Get( fldobj );
	save->gx_now = FieldOBJ_NowPosGX_Get( fldobj );
	save->gy_now = FieldOBJ_NowPosGY_Get( fldobj );
	save->gz_now = FieldOBJ_NowPosGZ_Get( fldobj );

	//高さの保存
#if 0
	{
		HEIGHT_TYPE flag;
		fx32 x,y,z;
		VecFx32 vec_pos;
		//グリッドをFX32型にする(グリッドの中心座標)
		x = save->gx_now * 16 * FX32_ONE+(8*FX32_ONE);
		z = save->gz_now * 16 * FX32_ONE+(8*FX32_ONE);
		FieldOBJ_VecPosGet( fldobj, &vec_pos );

		y = GetHeightPack( fsys, vec_pos.y, x, z, &flag );
		
		if( flag == HEIGHT_FAIL ){
			save->fx32_y = save->gy_now * 8 * FX32_ONE;
//			OS_Printf("height_FAIL:%x\n",save->fx32_y);
		}else{
			save->fx32_y = y;
//			OS_Printf("height_SAC:%x\n",save->fx32_y);
		}
	}
#else
	{
		VecFx32 vec;
		int flag,eflag;
		
		FieldOBJTool_GridCenterPosGet( save->gx_now, save->gz_now, &vec );
		vec.y = FieldOBJ_VecPosYGet( fldobj );
		
		eflag = FieldOBJ_StatusBitCheck_HeightExpand( fldobj );
		flag = FieldOBJTool_GetHeightExpand( fsys, &vec, eflag );
		
		if( flag == FALSE ){
			#if 0
			//これだと高さ取得失敗時、それまで正常に取得していた高さを無視してグリッド単位から
			//実座標に変換してしまい、斜め等の端数が無効となってしまう。
			save->fx32_y = H_GRID_SIZE_FX32( save->gy_now );
			#else
			save->fx32_y = FieldOBJ_VecPosYGet( fldobj );	
			#endif
		}else{
			save->fx32_y = vec.y;
		}
	}
#endif
	
	memcpy( save->move_proc_work,
			FieldOBJ_MoveProcWorkGet(fldobj), FLDOBJ_MOVE_WORK_SIZE );
	memcpy( save->move_sub_proc_work,
			FieldOBJ_MoveSubProcWorkGet(fldobj), FLDOBJ_MOVE_SUB_WORK_SIZE );
}

//--------------------------------------------------------------
/**
 * セーブデータの情報をフィールドOBJにセット
 * @param	fldobj		FIELD_OBJ_PTR
 * @param	save		FIELD_OBJ_SAVE_DATA_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FldOBJ_SaveDataLoad( FIELD_OBJ_PTR fldobj, FIELD_OBJ_SAVE_DATA_PTR save )
{
	FieldOBJ_StatusBit_Init( fldobj, save->status_bit );
	FieldOBJ_MoveBit_Init( fldobj, save->move_bit );
	FieldOBJ_OBJIDSet( fldobj,  save->obj_id );
	FieldOBJ_ZoneIDSet( fldobj, save->zone_id );
	FieldOBJ_OBJCodeSet( fldobj, save->obj_code );
	FieldOBJ_MoveCodeSet( fldobj, save->move_code );
	FieldOBJ_EventTypeSet( fldobj, save->event_type );
	FieldOBJ_EventFlagSet( fldobj, save->event_flag );
	FieldOBJ_EventIDSet( fldobj, save->event_id );
	FieldOBJ_DirHeaderSet( fldobj, save->dir_head );
	FieldOBJ_DirDispSetForce( fldobj, save->dir_disp );
	FieldOBJ_DirMoveSet( fldobj, save->dir_move );
	FieldOBJ_ParamSet( fldobj, save->param0, FLDOBJ_PARAM_0 );
	FieldOBJ_ParamSet( fldobj, save->param1, FLDOBJ_PARAM_1 );
	FieldOBJ_ParamSet( fldobj, save->param2, FLDOBJ_PARAM_2 );
	FieldOBJ_MoveLimitXSet( fldobj, save->move_limit_x );
	FieldOBJ_MoveLimitZSet( fldobj, save->move_limit_z );
	FieldOBJ_InitPosGX_Set( fldobj, save->gx_init );
	FieldOBJ_InitPosGY_Set( fldobj, save->gy_init );
	FieldOBJ_InitPosGZ_Set( fldobj, save->gz_init );
	FieldOBJ_NowPosGX_Set( fldobj, save->gx_now );
	FieldOBJ_NowPosGY_Set( fldobj, save->gy_now );
	FieldOBJ_NowPosGZ_Set( fldobj, save->gz_now );

	//高さ復帰
	{
		VecFx32 vec = {0,0,0};
		vec.y = save->fx32_y;
		FieldOBJ_VecPosSet( fldobj, &vec );
	}
	
	memcpy( FieldOBJ_MoveProcWorkGet(fldobj),
			save->move_proc_work, FLDOBJ_MOVE_WORK_SIZE );
	memcpy( FieldOBJ_MoveSubProcWorkGet(fldobj),
			save->move_sub_proc_work, FLDOBJ_MOVE_SUB_WORK_SIZE );
}

//--------------------------------------------------------------
/**
 * データロード後の復帰
 * @param	fos		FIELD_OBJ_SYS_PTR
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FldOBJ_DataLoadRecover( CONST_FIELD_OBJ_SYS_PTR fos, FIELD_OBJ_PTR fldobj )
{
	FldOBJ_DataLoadStatusBitRecover( fldobj );
	FldOBJ_DataLoadPosRecover( fldobj );
	
	FieldOBJ_FieldOBJSysSet( fldobj, fos );
	
	FldOBJ_WorkInit_MoveProcInit( fldobj );						//動作関数の初期化のみ
	FieldOBJ_AcmdFree( fldobj );
	FldOBJ_DrawWorkInit( fldobj );
	
	FldOBJ_MoveTcbAdd( fos, fldobj );
	FieldOBJ_MoveReturnProcCall( fldobj );
	FldOBJSys_OBJCountInc( FldOBJ_ConstSysLocalGet(fos) );
}

//--------------------------------------------------------------
/**
 * データロード後のステータスビット復帰
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FldOBJ_DataLoadStatusBitRecover( FIELD_OBJ_PTR fldobj )
{
	FieldOBJ_StatusBit_ON( fldobj,
			FLDOBJ_STA_BIT_USE |
//			FLDOBJ_STA_BIT_HEIGHT_GET_NEED |					//セーブ時の高さを信用する
			FLDOBJ_STA_BIT_MOVE_START );
	
	FieldOBJ_StatusBit_OFF( fldobj,
			FLDOBJ_STA_BIT_PAUSE_MOVE |
			FLDOBJ_STA_BIT_VANISH |
			FLDOBJ_STA_BIT_DRAW_PROC_INIT_COMP |
			FLDOBJ_STA_BIT_JUMP_START |
			FLDOBJ_STA_BIT_JUMP_END |
			FLDOBJ_STA_BIT_MOVE_END |
			FLDOBJ_STA_BIT_FELLOW_HIT_NON |
			FLDOBJ_STA_BIT_TALK_OFF |
			FLDOBJ_STA_BIT_DRAW_PUSH |
			FLDOBJ_STA_BIT_BLACT_ADD_PRAC |
			FLDOBJ_STA_BIT_HEIGHT_GET_OFF );
	
	FldOBJ_DrawEffectFlagInit( fldobj );
}

//--------------------------------------------------------------
/**
 * データロード後の座標復帰
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FldOBJ_DataLoadPosRecover( FIELD_OBJ_PTR fldobj )
{
	int pos;
	VecFx32 vec;
	
	FieldOBJ_VecPosGet( fldobj, &vec );

//	OS_Printf("recover_y:%x\n",vec.y);
	
	pos = FieldOBJ_NowPosGX_Get( fldobj );
	vec.x = GRID_SIZE_FX32( pos ) + FLDOBJ_VEC_X_GRID_OFFS_FX32;
	FieldOBJ_OldPosGX_Set( fldobj, pos );

	pos = FieldOBJ_NowPosGY_Get( fldobj );
//	vec.y = H_GRID_SIZE_FX32( pos ) + FLDOBJ_VEC_Y_GRID_OFFS_FX32;	<<ロード時に値がセットされているはず
	FieldOBJ_OldPosGY_Set( fldobj, pos );
	
	pos = FieldOBJ_NowPosGZ_Get( fldobj );
	vec.z = GRID_SIZE_FX32( pos ) + FLDOBJ_VEC_Z_GRID_OFFS_FX32;
	FieldOBJ_OldPosGZ_Set( fldobj, pos );
	
	FieldOBJ_VecPosSet( fldobj, &vec );
}

//==============================================================================
//	フィールドOBJ 複数登録
//==============================================================================
#if 0	//用無し

//--------------------------------------------------------------
///	FieldOBJ_AddFile()でファイル名読み込みで使用するバッファサイズ
//--------------------------------------------------------------
#define FLDOBJ_FILE_1LINE_BUF (96)

//--------------------------------------------------------------
/**
 * フィールドOBJ　ファイル名指定による複数登録
 * @param	sys			FIELD_OBJ_SYS_PTR 
 * @param	zone		追加されるゾーンID
 * @param	name		FIELD_OBJ_Hが記述されたファイル名
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_AddFile( CONST_FIELD_OBJ_SYS_PTR sys, int zone, const char *name )
{
	int i,max;
	char *file,*f_pos;
	char buf[FLDOBJ_FILE_1LINE_BUF];
	FIELD_OBJ_H *head;
	FIELD_OBJ_H_LOAD_FILE *load;
	
	if( name == NULL ){
		return;
	}
	
	file = sys_LoadFile( HEAPID_WORLD, name );
	GF_ASSERT( file != NULL && "fieldobj add file alloc error" );
	
	StrTok( file, buf, ',' );								//登録数
	max = AtoI( buf );
	
	OS_Printf( "fieldobj add file load %d\n", max );
	
	head = sys_AllocMemoryLo( HEAPID_WORLD, FIELD_OBJ_H_SIZE * max );
	GF_ASSERT( head != NULL && "fieldobj add file head alloc error" );
	
	f_pos = StrTok( file, buf, RETURN_CODE );				//1行飛ばし
	f_pos = StrTok( f_pos, buf, RETURN_CODE );				//段落飛ばし
	
	for( i = 0; i < max; i++ ){
		f_pos = StrTok( f_pos, buf, ',' );					//ID取得
		FieldOBJ_H_IDSet( &head[i], AtoI(buf) );
		f_pos = StrTok( f_pos, buf, RETURN_CODE );			//1行飛ばし
		
		f_pos = StrTok( f_pos, buf, ',' );					//OBJコード取得
		FieldOBJ_H_OBJCodeSet( &head[i], AtoI(buf) );
		f_pos = StrTok( f_pos, buf, RETURN_CODE );			//1行飛ばし
		
		f_pos = StrTok( f_pos, buf, ',' );					//動作コード取得
		FieldOBJ_H_MoveCodeSet( &head[i], AtoI(buf) );
		f_pos = StrTok( f_pos, buf, RETURN_CODE );			//1行飛ばし
		
		f_pos = StrTok( f_pos, buf, ',' );					//イベントタイプ取得
		FieldOBJ_H_EventTypeSet( &head[i], AtoI(buf) );
		f_pos = StrTok( f_pos, buf, RETURN_CODE );			//1行飛ばし
		
		f_pos = StrTok( f_pos, buf, ',' );					//イベントフラグ取得
		FieldOBJ_H_EventFlagSet( &head[i], AtoI(buf) );
		f_pos = StrTok( f_pos, buf, RETURN_CODE );			//1行飛ばし
		
		f_pos = StrTok( f_pos, buf, ',' );					//イベントID取得
		FieldOBJ_H_EventIDSet( &head[i], AtoI(buf) );
		f_pos = StrTok( f_pos, buf, RETURN_CODE );			//1行飛ばし
		
		f_pos = StrTok( f_pos, buf, ',' );					//方向取得
		FieldOBJ_H_DirSet( &head[i], AtoI(buf) );
		f_pos = StrTok( f_pos, buf, RETURN_CODE );			//1行飛ばし
		
		f_pos = StrTok( f_pos, buf, ',' );					//パラメタ取得
		FieldOBJ_H_ParamSet( &head[i], AtoI(buf) );
		f_pos = StrTok( f_pos, buf, RETURN_CODE );			//1行飛ばし
		
		f_pos = StrTok( f_pos, buf, ',' );					//移動制限X取得
		FieldOBJ_H_MoveLimitXSet( &head[i], AtoI(buf) );
		
		f_pos = StrTok( f_pos, buf, ',' );					//移動制限Z取得
		FieldOBJ_H_MoveLimitZSet( &head[i], AtoI(buf) );
		f_pos = StrTok( f_pos, buf, RETURN_CODE );			//1行飛ばし
		
		f_pos = StrTok( f_pos, buf, ',' );					//X座標取得
		FieldOBJ_H_PosXSet( &head[i], AtoI(buf) );
		
		f_pos = StrTok( f_pos, buf, ',' );					//Z座標取得
		FieldOBJ_H_PosZSet( &head[i], AtoI(buf) );
		f_pos = StrTok( f_pos, buf, RETURN_CODE );			//1行飛ばし
		
		f_pos = StrTok( f_pos, buf, ',' );					//Y座標取得
		FieldOBJ_H_PosYSet( &head[i], AtoI(buf) );
		f_pos = StrTok( f_pos, buf, RETURN_CODE );			//一行飛ばし
		
		f_pos = StrTok( f_pos, buf, RETURN_CODE );			//段落飛ばし
	}
	
	sys_FreeMemory( HEAPID_WORLD, file );
	
	load = sys_AllocMemoryLo( HEAPID_WORLD, FIELD_OBJ_H_LOAD_FILE_SIZE );
	GF_ASSERT( load != NULL && "fieldobj add file work alloc error" );
	
	load->zone = zone;
	load->add_max = max;
	load->add_count = 0;
	load->sys = sys;
	load->head = head;
	
	FldOBJ_AddFileProc( load );
	
	OS_Printf( "fieldobj add file load OK\n" );
}
#endif

//--------------------------------------------------------------
/**
 * フィールドOBJ　バイナリ指定による複数登録
 * @param	sys			FIELD_OBJ_SYS_PTR 
 * @param	zone		追加されるゾーンID
 * @param	max			追加する最大数
 * @param	bin			追加するFIELD_OBJ_Hが配置されているバイナリ*
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_AddBin( CONST_FIELD_OBJ_SYS_PTR sys, int zone, int max, const FIELD_OBJ_H *bin )
{
	int size;
	FIELD_OBJ_H *head;
	FIELD_OBJ_H_LOAD_FILE *load;
	
	OS_Printf( "フィールドOBJ 一括登録開始 配置数 %d\n", max );
	GF_ASSERT( max && "FieldOBJ_AddBin()　指定最大数異常" );
	
	size = FIELD_OBJ_H_SIZE *max;
	head = sys_AllocMemoryLo( HEAPID_WORLD, size );
	GF_ASSERT( head != NULL && "fieldobj add bin head alloc error" );
	memcpy( head, bin, size );
	
	load = sys_AllocMemoryLo( HEAPID_WORLD, FIELD_OBJ_H_LOAD_FILE_SIZE );
	GF_ASSERT( load != NULL && "fieldobj add file work alloc error" );
	
	load->zone = zone;
	load->add_max = max;
	load->add_count = 0;
	load->sys = sys;
	load->head = head;
	
	FldOBJ_AddFileProc( load );
	
	OS_Printf( "フィールドOBJ 一括登録終了\n" );
}

//--------------------------------------------------------------
/**
 * フィールドOBJ一括登録
 * @param	work	FIELD_OBJ_H_LOAD_FILE
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FldOBJ_AddFileProc( FIELD_OBJ_H_LOAD_FILE *work )
{
	FIELD_OBJ_PTR fldobj;
	FIELDSYS_WORK *fsys;
	const FIELD_OBJ_H *head;
	
	fsys = FieldOBJSys_FieldSysWorkGet( work->sys );
	head = work->head;
	
	do{
		if( FldOBJ_H_AliesCheck(head) == TRUE ||
			CheckEventFlag(fsys,head->event_flag) == FALSE ){
			fldobj = FieldOBJ_AddH( work->sys, head, work->zone );
			GF_ASSERT( fldobj != NULL && "フィールドOBJの一括登録に失敗しました\n" );
		}
#ifdef PM_DEBUG
		else{
			OS_Printf( "フィールドOBJ一括登録中…イベントフラグがFALSEの為、" );
			OS_Printf( "OBJ ID=%d,",FieldOBJ_H_IDGet(head) );
			OS_Printf( "GIRD X=%d,",FieldOBJ_H_PosXGet(head) );
			OS_Printf( "GIRD Z=%d",FieldOBJ_H_PosZGet(head) );
			OS_Printf( "に配置するOBJの追加を無視しました\n" );
		}
#endif
		head++;
		work->add_count++;
	}while( work->add_count < work->add_max );
	
	sys_FreeMemory( HEAPID_WORLD, work->head );
	sys_FreeMemory( HEAPID_WORLD, work );
}

#if 0	//旧版　エイリアスでのバグあり
static void FldOBJ_AddFileProc( FIELD_OBJ_H_LOAD_FILE *work )
{
	FIELD_OBJ_PTR fldobj;
	FIELDSYS_WORK *fsys;
	const FIELD_OBJ_H *head;
	
	fsys = FieldOBJSys_FieldSysWorkGet( work->sys );
	head = work->head;
	
	do{
		if( CheckEventFlag(fsys,head->event_flag) == FALSE ){
			fldobj = FieldOBJ_AddH( work->sys, head, work->zone );
			GF_ASSERT( fldobj != NULL && "フィールドOBJの一括登録に失敗しました\n" );
		}else{
			OS_Printf( "フィールドOBJ一括登録中…イベントフラグがFALSEの為、" );
			OS_Printf( "OBJ ID=%d,",FieldOBJ_H_IDGet(head) );
			OS_Printf( "GIRD X=%d,",FieldOBJ_H_PosXGet(head) );
			OS_Printf( "GIRD Z=%d",FieldOBJ_H_PosZGet(head) );
			OS_Printf( "に配置するOBJの追加を無視しました\n" );
		}
	
		head++;
		work->add_count++;
	}while( work->add_count < work->add_max );
	
	sys_FreeMemory( HEAPID_WORLD, work->head );
	sys_FreeMemory( HEAPID_WORLD, work );
}
#endif

//==============================================================================
//	フィールドOBJ　パーツ
//==============================================================================
//--------------------------------------------------------------
/**
 * フィールドOBJの空きを探す
 * @param	sys			FIELD_OBJ_SYS_PTR 
 * @retval	FIELD_OBJ	空きのFIELD_OBJ*　空きが無い場合はNULL
 */
//--------------------------------------------------------------
static FIELD_OBJ_PTR  FldOBJ_SpaceSearch( CONST_FIELD_OBJ_SYS_PTR sys )
{
	int i,max;
	FIELD_OBJ_PTR fldobj;
	
	i = 0;
	max = FieldOBJSys_OBJMaxGet( sys );
	fldobj = FieldOBJSys_FldOBJWorkGet( sys );
	
	do{
		if( FieldOBJ_StatusBit_Check(fldobj,FLDOBJ_STA_BIT_USE) == 0 ){
			return( fldobj );
		}
		
		fldobj++;
		i++;
	}while( i < max );
	
	return( NULL );
}

//--------------------------------------------------------------
/**
 * フィールドOBJ　エイリアスを探す
 * @param	fos			FIELD_OBJ_SYS_PTR
 * @param	obj_id		一致するOBJ ID
 * @param	zone_id		一致するZONE ID
 * @retval	FIELD_OBJ	一致するFIELD_OBJ*　一致無し=NULL
 */
//--------------------------------------------------------------
static FIELD_OBJ_PTR FldOBJ_AliesSearch( CONST_FIELD_OBJ_SYS_PTR fos, int obj_id, int zone_id )
{
	int no = 0;
	FIELD_OBJ_PTR fldobj;
	
	while( FieldOBJSys_FieldOBJSearch(fos,&fldobj,&no,FLDOBJ_STA_BIT_USE) == TRUE ){
		if( FieldOBJ_StatusBitCheck_Alies(fldobj) == TRUE ){
			if( FieldOBJ_OBJIDGet(fldobj) == obj_id ){
				if( FieldOBJ_ZoneIDGetAlies(fldobj) == zone_id ){
					return( fldobj );
				}
			}
		}
	}
	
	return( NULL );
}

//--------------------------------------------------------------
/**
 * フィールドOBJ　TCB動作関数追加
 * @param	sys		FIELD_OBJ_SYS*
 * @param	fldobj	FIELD_OBJ*
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FldOBJ_MoveTcbAdd( CONST_FIELD_OBJ_SYS_PTR sys, FIELD_OBJ_PTR fldobj )
{
	int pri,code;
	TCB_PTR tcb;
	
	pri = FieldOBJSys_TCBStandardPriorityGet( sys );
	code = FieldOBJ_MoveCodeGet( fldobj );
	
	if( code == MV_PAIR || code == MV_TR_PAIR ){
		pri += FLDOBJ_TCBPRI_OFFS_AFTER;
	}
	
	tcb = TCB_Add( FldOBJ_TCB_MoveProc, fldobj, pri );
	GF_ASSERT( tcb != NULL && "fldobj tcb not add error" );
	
	FieldOBJ_MoveTcbPtrSet( fldobj, tcb );
}

//--------------------------------------------------------------
/**
 * フィールドOBJ　ヘッダー情報反映
 * @param	fldobj		設定するFIELD_OBJ_PTR 
 * @param	head		反映する情報を纏めたFIELD_OBJ_H *
 * @param	fsys		FIELDSYS_WORK *
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FldOBJ_AddHeaderSet(
		FIELD_OBJ_PTR fldobj, const FIELD_OBJ_H *head, FIELDSYS_WORK *fsys )
{
	FieldOBJ_OBJIDSet( fldobj, FieldOBJ_H_IDGet(head) );
	FieldOBJ_OBJCodeSet( fldobj,FldOBJ_OBJCodeWkOBJCodeConv(fsys,FieldOBJ_H_OBJCodeGet(head)) );
	FieldOBJ_MoveCodeSet( fldobj, FieldOBJ_H_MoveCodeGet(head) );
	FieldOBJ_EventTypeSet( fldobj, FieldOBJ_H_EventTypeGet(head) );
	FieldOBJ_EventFlagSet( fldobj, FieldOBJ_H_EventFlagGet(head) );
	FieldOBJ_EventIDSet( fldobj, FieldOBJ_H_EventIDGet(head) );
	FieldOBJ_DirHeaderSet( fldobj, FieldOBJ_H_DirGet(head) );
	FieldOBJ_ParamSet( fldobj, FieldOBJ_H_ParamGet(head,FLDOBJ_PARAM_0), FLDOBJ_PARAM_0 );
	FieldOBJ_ParamSet( fldobj, FieldOBJ_H_ParamGet(head,FLDOBJ_PARAM_1), FLDOBJ_PARAM_1 );
	FieldOBJ_ParamSet( fldobj, FieldOBJ_H_ParamGet(head,FLDOBJ_PARAM_2), FLDOBJ_PARAM_2 );
	FieldOBJ_MoveLimitXSet( fldobj, FieldOBJ_H_MoveLimitXGet(head) );
	FieldOBJ_MoveLimitZSet( fldobj, FieldOBJ_H_MoveLimitZGet(head) );
	
	FldOBJ_AddHeaderPosInit( fldobj, head );
}

//--------------------------------------------------------------
/**
 * フィールドOBJ　座標系初期化
 * @param	fldobj		FIELD_OBJ_PTR 
 * @param	head		反映する情報を纏めたFIELD_OBJ_H *
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FldOBJ_AddHeaderPosInit( FIELD_OBJ_PTR fldobj, const FIELD_OBJ_H *head )
{
	int pos;
	VecFx32 vec;
	
	pos = FieldOBJ_H_PosXGet( head );
	vec.x = GRID_SIZE_FX32( pos ) + FLDOBJ_VEC_X_GRID_OFFS_FX32;
	FieldOBJ_InitPosGX_Set( fldobj, pos );
	FieldOBJ_OldPosGX_Set( fldobj, pos );
	FieldOBJ_NowPosGX_Set( fldobj, pos );
	
	pos = FieldOBJ_H_PosYGet( head );							//pos設定はfx32型で来る。
	vec.y = (fx32)pos;
	pos = SIZE_H_GRID_FX32( pos );
	FieldOBJ_InitPosGY_Set( fldobj, pos );
	FieldOBJ_OldPosGY_Set( fldobj, pos );
	FieldOBJ_NowPosGY_Set( fldobj, pos );
	
	pos = FieldOBJ_H_PosZGet( head );
	vec.z = GRID_SIZE_FX32( pos ) + FLDOBJ_VEC_Z_GRID_OFFS_FX32;
	FieldOBJ_InitPosGZ_Set( fldobj, pos );
	FieldOBJ_OldPosGZ_Set( fldobj, pos );
	FieldOBJ_NowPosGZ_Set( fldobj, pos );
	
	FieldOBJ_VecPosSet( fldobj, &vec );
}

//--------------------------------------------------------------
/**
 * フィールドOBJ　ワーク初期化
 * @param	fldobj		FIELD_OBJ_PTR 
 * @param	sys			FIELD_OBJ_SYS_PTR 
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FldOBJ_WorkInit( FIELD_OBJ_PTR fldobj, CONST_FIELD_OBJ_SYS_PTR sys )
{
	FieldOBJ_StatusBit_ON( fldobj,
			FLDOBJ_STA_BIT_USE |							//使用中
			FLDOBJ_STA_BIT_HEIGHT_GET_ERROR |				//高さ取得が必要である
			FLDOBJ_STA_BIT_ATTR_GET_ERROR );				//アトリビュート取得が必要である
	
	if( FieldOBJ_EventIDAliesCheck(fldobj) == TRUE ){
		FieldOBJ_StatusBitSet_Alies( fldobj, TRUE );
	}
	
	FieldOBJ_FieldOBJSysSet( fldobj, sys );
	FieldOBJ_DirDispSetForce( fldobj, FieldOBJ_DirHeaderGet(fldobj) );
	FieldOBJ_DirMoveSet( fldobj, FieldOBJ_DirHeaderGet(fldobj) );
	FieldOBJ_AcmdFree( fldobj );
}

//--------------------------------------------------------------
/**
 * フィールドOBJ 動作関数初期化
 * @param	fldobj		FIELD_OBJ_PTR 
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FldOBJ_WorkInit_MoveProcInit( FIELD_OBJ_PTR fldobj )
{
	const FIELD_OBJ_MOVE_PROC_LIST *list;
	
	list = FldOBJ_MoveProcListGet( FieldOBJ_MoveCodeGet(fldobj) );
	FieldOBJ_MoveInitProcSet( fldobj, FldOBJ_MoveProcList_InitGet(list) );
	FieldOBJ_MoveProcSet( fldobj, FldOBJ_MoveProcList_MoveGet(list) );
	FieldOBJ_MoveDeleteProcSet( fldobj, FldOBJ_MoveProcList_DeleteGet(list) );
}

//--------------------------------------------------------------
/**
 * フィールドOBJ 描画関数初期化
 * @param	fldobj		FIELD_OBJ_PTR 
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FldOBJ_WorkInit_DrawProcInit( FIELD_OBJ_PTR fldobj )
{
	const FIELD_OBJ_DRAW_PROC_LIST *list;
	u32 code = FieldOBJ_OBJCodeGet( fldobj );
	
	if( code == NONDRAW ){
		list = &DATA_FieldOBJDraw_Non;
	}else{
		list = FldOBJ_DrawProcListGet( code );
	}
	
	FieldOBJ_DrawInitProcSet( fldobj, FldOBJ_DrawProcList_InitGet(list) );
	FieldOBJ_DrawProcSet( fldobj, FldOBJ_DrawProcList_DrawGet(list) );
	FieldOBJ_DrawDeleteProcSet( fldobj, FldOBJ_DrawProcList_DeleteGet(list) );
	FieldOBJ_DrawPushProcSet( fldobj, FldOBJ_DrawProcList_PushGet(list) );
	FieldOBJ_DrawPopProcSet( fldobj, FldOBJ_DrawProcList_PopGet(list) );
}

//--------------------------------------------------------------
/**
 * ワーク消去
 * @param	fldobj	FIELD_OBJ_PTR 
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FldOBJ_WorkClear( FIELD_OBJ_PTR fldobj )
{
	memset( fldobj, 0, FIELD_OBJ_SIZE );
}

//--------------------------------------------------------------
/**
 * 指定されたフィールドOBJがエイリアス指定かどうかチェック
 * @param	fldobj		FIELD_OBJ_PTR
 * @param	h_zone_id	headを読み込むゾーンID
 * @param	max			head要素数
 * @param	head		FIELD_OBJ_H
 * @retval	int			RET_ALIES_NOT等
 */
//--------------------------------------------------------------
static int FldOBJ_HeaderAliesCheck(
		CONST_FIELD_OBJ_PTR fldobj, int h_zone_id, int max, const FIELD_OBJ_H *head )
{
	int obj_id;
	int zone_id;
	
	while( max ){
		obj_id = FieldOBJ_H_IDGet( head );
		
		if( FieldOBJ_OBJIDGet(fldobj) == obj_id ){					//ID一致
			if( FldOBJ_H_AliesCheck(head) == TRUE ){				//エイリアスヘッダー
				zone_id = FldOBJ_H_AliesZoneIDGet( head );			//エイリアスの正規ゾーンID
				
				if( FieldOBJ_StatusBitCheck_Alies(fldobj) == TRUE ){	//対象エイリアス
					if( FieldOBJ_ZoneIDGetAlies(fldobj) == zone_id ){
						return( RET_ALIES_EXIST );						//Aliesとして既に存在
					}
				}else if( FieldOBJ_ZoneIDGet(fldobj) == zone_id ){
					return( RET_ALIES_CHANGE );							//Alies対象である
				}
			}else{														//通常ヘッダー
				if( FieldOBJ_StatusBitCheck_Alies(fldobj) == TRUE ){
					if( FieldOBJ_ZoneIDGetAlies(fldobj) == h_zone_id ){	//生存エイリアスと一致
						return( RET_ALIES_CHANGE );
					}
				}
			}
		}
		
		max--;
		head++;
	}
	
	return( RET_ALIES_NOT );
}

//--------------------------------------------------------------
/**
 * 指定されたゾーンIDとOBJ IDを持つFIELD_OBJ_PTRを取得。
 * @param	fos		FIELD_OBJ_SYS_PTR
 * @param	obj_id	OBJ ID
 * @param	zone_id	ゾーンID
 * @retval	FIELD_OBJ_PTR FIELD_OBJ_PTR
 */
//--------------------------------------------------------------
static FIELD_OBJ_PTR FldOBJ_OBJIDZoneIDSearch(
		CONST_FIELD_OBJ_SYS_PTR fos, int obj_id, int zone_id )
{
	int no = 0;
	FIELD_OBJ_PTR fldobj;
	
	while( FieldOBJSys_FieldOBJSearch(fos,&fldobj,&no,FLDOBJ_STA_BIT_USE) == TRUE ){
		if( FieldOBJ_OBJIDGet(fldobj) == obj_id && FieldOBJ_ZoneIDGet(fldobj) == zone_id ){
			return( fldobj );
		}
	}
	
	return( NULL );
}

//--------------------------------------------------------------
/**
 * 指定されたゾーンIDを持つもの以外を全て削除
 * @param	fos			FIELD_OBJ_SYS_PTR
 * @param	zone_id		削除しないゾーンID
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FldOBJ_DeleteAll_OldZoneID( FIELD_OBJ_SYS_PTR fos, u32 zone_id )
{
	u32 ret;
	int max = FieldOBJSys_OBJMaxGet( fos );
	FIELD_OBJ_PTR fldobj = FieldOBJSys_FldOBJWorkGet( fos );
	
	do{
		if( FieldOBJ_StatusBitCheck_Use(fldobj) == TRUE ){
			if( FieldOBJ_ZoneIDGet(fldobj) != zone_id ){
				if( FieldOBJ_StatusBit_CheckEasy(fldobj,FLDOBJ_STA_BIT_ZONE_DEL_NOT) == FALSE ){
					FieldOBJ_Delete( fldobj );
				}
			}
		}
		
		fldobj++;
		max--;
	}while( max );
}

//--------------------------------------------------------------
/**
 * OBJ IDに一致するFIELD_OBJ_PTRを検索
 * @param	fos		FIELD_OBJ_SYS_PTR
 * @param	id		検索するOBJ ID
 * @retval	FIELD_OBJ_PTR	NULL=存在しない
 */
//--------------------------------------------------------------
FIELD_OBJ_PTR FieldOBJSys_OBJIDSearch( CONST_FIELD_OBJ_SYS_PTR fos, int id )
{
	int max;
	FIELD_OBJ_PTR fldobj;
	
	GF_ASSERT( fos != NULL && "FieldOBJSys_OBJIDSearch() NULL指定です" );
	
	max = FieldOBJSys_OBJMaxGet( fos );
	fldobj = FldOBJSys_FieldOBJWorkGet( fos );
	
	do{
		if( FieldOBJ_StatusBit_CheckEasy(fldobj,FLDOBJ_STA_BIT_USE) == TRUE ){
			if( FieldOBJ_StatusBitCheck_Alies(fldobj) == FALSE ){
				if( FieldOBJ_OBJIDGet(fldobj) == id ){
					return( fldobj );
				}
			}
		}
		
		fldobj++;
		max--;
	}while( max > 0 );
	
	return( NULL );
}

//--------------------------------------------------------------
/**
 * 動作コードに一致するFIELD_OBJ_PTRを検索
 * @param	fos		FIELD_OBJ_SYS_PTR
 * @param	mv_code		検索する動作コード
 * @retval	FIELD_OBJ_PTR	NULL=存在しない
 */
//--------------------------------------------------------------
FIELD_OBJ_PTR FieldOBJSys_MoveCodeSearch( CONST_FIELD_OBJ_SYS_PTR fos, int mv_code )
{
	int max;
	FIELD_OBJ_PTR fldobj;
	
	max = FieldOBJSys_OBJMaxGet( fos );
	fldobj = FldOBJSys_FieldOBJWorkGet( fos );
	
	do{
		if( FieldOBJ_StatusBit_CheckEasy(fldobj,FLDOBJ_STA_BIT_USE) == TRUE ){
			if( FieldOBJ_MoveCodeGet(fldobj) == mv_code ){
				return( fldobj );
			}
		}
		
		fldobj++;
		max--;
	}while( max > 0 );
	
	return( NULL );
}

FIELD_OBJ_PTR FieldOBJSys_OBJIDMoveCodeSearch( CONST_FIELD_OBJ_SYS_PTR fos, int o, int m )
{
	return( NULL );
}

//--------------------------------------------------------------
/**
 * フィールドOBJワーク検索
 * @param	fos			FIELD_OBJ_SYS_PTR
 * @param	fldobj		該当するFIELD_OBJ_PTR格納先
 * @param	no			検索開始ワークno。この関数から戻る際、検索位置+1の値になる
 * @param	check_bit	検索条件ステータスビット。FLDOBJ_STA_BIT_USE等
 * @retval	int			TRUE=一致あり FALSE=一致なし
 */
//--------------------------------------------------------------
int FieldOBJSys_FieldOBJSearch(
	CONST_FIELD_OBJ_SYS_PTR fos, FIELD_OBJ_PTR *fldobj, int *no, u32 check_bit )
{
	int max;
	FIELD_OBJ_PTR check_obj;
	
	max = FieldOBJSys_OBJMaxGet( fos );
	
	if( (*no) >= max ){
		return( FALSE );
	}
	
	check_obj = FldOBJSys_FieldOBJWorkGet( fos );
	check_obj = &check_obj[(*no)];
	
	do{
		(*no)++;
		
		if( FieldOBJ_StatusBit_Check(check_obj,check_bit) == check_bit ){
			*fldobj = check_obj;
			return( TRUE );
		}
		
		check_obj++;
	}while( (*no) < max );
	
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * フィールドOBJ描画初期化に行う処理
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FldOBJ_DrawInitStatusSet( FIELD_OBJ_PTR fldobj )
{
	FieldOBJ_StatusBit_ON( fldobj, FLDOBJ_STA_BIT_MOVE_START );
	FldOBJ_DrawEffectFlagInit( fldobj );
}

//--------------------------------------------------------------
/**
 * フィールドOBJ関連エフェクトのフラグ初期化。
 * エフェクト関連のフラグ初期化をまとめる
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FldOBJ_DrawEffectFlagInit( FIELD_OBJ_PTR fldobj )
{
	FieldOBJ_StatusBit_OFF( fldobj,
		FLDOBJ_STA_BIT_SHADOW_SET		|
		FLDOBJ_STA_BIT_SHADOW_VANISH	|
		FLDOBJ_STA_BIT_EFFSET_SHOAL		|
		FLDOBJ_STA_BIT_REFLECT_SET );
}

//--------------------------------------------------------------
/**
 * フィールドOBJ描画削除時に行う処理
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FldOBJ_DrawDeleteStatusSet( FIELD_OBJ_PTR fldobj )
{
}

//--------------------------------------------------------------
/**
 * 指定されたOBJコードがワーク参照型ならばワーク内OBJコードに変更。
 * 違う場合はそのままで返す。
 * @param	fsys	FIELDSYS_WORK *
 * @param	code	OBJコード。HERO等
 * @retval	int		チェックされたOBJコード
 */
//--------------------------------------------------------------
static int FldOBJ_OBJCodeWkOBJCodeConv( FIELDSYS_WORK *fsys, int code )
{
	if( code >= WKOBJCODE_ORG && code <= WKOBJCODE_END ){
		code -= WKOBJCODE_ORG;
		code = GetEvDefineObjCode( fsys, code );
	}
	
	return( code );
}

//--------------------------------------------------------------
/**
 * 現在発生しているフィールドOBJのOBJコードを参照
 * @param	fldobj		FIELD_OBJ_PTR 
 * @param	code		チェックするコード。HERO等
 * @retval	int			TRUE=fldobj以外にもcodeを持っている奴がいる
 */
//--------------------------------------------------------------
int FieldOBJ_OBJCodeUseSearch( CONST_FIELD_OBJ_PTR fldobj, int code )
{
	CONST_FIELD_OBJ_SYS_PTR fos = FieldOBJ_FieldOBJSysGet( fldobj );
	int check_code,i = FieldOBJSys_OBJMaxGet( fos );
	CONST_FIELD_OBJ_PTR fieldobj = FieldOBJSys_FieldOBJWorkGet( fos );
	
	do{
		if( fieldobj != fldobj ){
			if( FieldOBJ_StatusBitCheck_Use(fieldobj) == TRUE ){
				check_code = FieldOBJ_OBJCodeGet( fieldobj );
					
				if( FieldOBJ_OBJCodeSeedCheck(check_code) == TRUE ){
					check_code = FieldOBJ_OBJCodeSeedGet( fieldobj );
				}
				
				if( check_code != OBJCODEMAX && check_code == code ){
					return( TRUE );
				}
			}
		}
		
		FieldOBJSys_FieldOBJWorkInc( &fieldobj );
		i--;
	}while( i );
	
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * 高さ初期化 FLDOBJ_STA_BIT_HEIGHT_GET_ERRORがOFFの場合は初期化しない
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FldOBJ_HeightNeedCheckInit( FIELD_OBJ_PTR fldobj )
{
	if( FieldOBJ_StatusBit_Check(fldobj,FLDOBJ_STA_BIT_HEIGHT_GET_ERROR) ){
		FieldOBJ_VecPosNowHeightGetSet( fldobj );
	}
}

//--------------------------------------------------------------
/**
 * 動作初期化に行う処理纏め
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FldOBJ_MoveWorkInit( FIELD_OBJ_PTR fldobj )
{
	FldOBJ_WorkInit_MoveProcInit( fldobj );
	FieldOBJ_MoveInit( fldobj );
}

//--------------------------------------------------------------
/**
 * 描画初期化に行う処理纏め
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FldOBJ_DrawWorkInit( FIELD_OBJ_PTR fldobj )
{
	CONST_FIELD_OBJ_SYS_PTR fos = FieldOBJ_FieldOBJSysGet( fldobj );
	
	if( FieldOBJSys_DrawInitCompCheck(fos) == FALSE ){		//描画システム初期化完了していない
		return;
	}
	
	FldOBJ_HeightNeedCheckInit( fldobj );
	FieldOBJ_DrawStatusSet( fldobj, 0 );
	FieldOBJ_BlActAddPracFlagSet( fldobj, FALSE );
	
	if( FieldOBJ_StatusBitCheck_DrawProcInitComp(fldobj) == FALSE ){
		FldOBJ_WorkInit_DrawProcInit( fldobj );
		FieldOBJ_DrawInitProcCall( fldobj );
		FieldOBJ_StatusBitON_DrawProcInitComp( fldobj );
	}
}

//--------------------------------------------------------------
/**
 * イベントIDがエイリアスかどうかチェック
 * @param	fldobj		FIELD_OBJ_PTR 
 * @retval	int			TRUE=エイリアスIDである FALSE=違う
 */
//--------------------------------------------------------------
int FieldOBJ_EventIDAliesCheck( CONST_FIELD_OBJ_PTR fldobj )
{
	u16 id = (u16)FieldOBJ_EventIDGet( fldobj );
	
	if( id == SP_SCRID_ALIES ){
		return( TRUE );
	}
	
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * フィールドOBJ　エイリアスから正規OBJへの変更
 * @param	fldobj		FIELD_OBJ_PTR 
 * @param	head		対象のFIELD_OBJ_H
 * @param	zone_id		正規のゾーンID
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FldOBJ_AliesOBJChange( FIELD_OBJ_PTR fldobj, const FIELD_OBJ_H *head, int zone_id )
{
	GF_ASSERT( FieldOBJ_StatusBitCheck_Alies(fldobj) == TRUE &&
			"FldOBJ_AliesOBJChange()aliesではない" );
	
	FieldOBJ_StatusBitSet_Alies( fldobj, FALSE );
	FieldOBJ_ZoneIDSet( fldobj, zone_id );
	FieldOBJ_EventIDSet( fldobj, FieldOBJ_H_EventIDGet(head) );
	FieldOBJ_EventFlagSet( fldobj, FieldOBJ_H_EventFlagGet(head) );
}	

//--------------------------------------------------------------
/**
 * フィールドOBJ　正規OBJからエイリアスへの変更
 * @param	fldobj		FIELD_OBJ_PTR 
 * @param	head		対象のFIELD_OBJ_H
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FldOBJ_OBJAliesChange( FIELD_OBJ_PTR fldobj, int zone_id, const FIELD_OBJ_H *head )
{
	GF_ASSERT( FldOBJ_H_AliesCheck(head) == TRUE && "FldOBJ_OBJAliesChange()aliesではない" );
	
	FieldOBJ_StatusBitSet_Alies( fldobj, TRUE );
	FieldOBJ_EventIDSet( fldobj, FieldOBJ_H_EventIDGet(head) );
	FieldOBJ_EventFlagSet( fldobj, FldOBJ_H_AliesZoneIDGet(head) );
	FieldOBJ_ZoneIDSet( fldobj, zone_id );
}

//--------------------------------------------------------------
/**
 * FIELD_OBJ_PTRのTCBスタンダードプライオリティを調整して取得
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	offset	スタンダードプライオリティに加算する値
 * @retval	int		調節されたプライオリティ
 */
//--------------------------------------------------------------
int FieldOBJ_TCBPriGet( CONST_FIELD_OBJ_PTR fldobj, int offset )
{
	int pri;
	
	pri = FieldOBJ_TCBStandardPriorityGet( fldobj );
	pri += offset;
	
	return( pri );
}

//--------------------------------------------------------------
/**
 * フィールドOBJの同一チェック。
 * 死亡、入れ替わりが発生しているかチェックする。
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	obj_id	同一とみなすOBJ ID
 * @param	zone_id	同一とみなすZONE ID
 * @retval	int		TRUE=同一。FALSE=同一ではない
 */
//--------------------------------------------------------------
int FieldOBJ_CheckSameID( CONST_FIELD_OBJ_PTR fldobj, int obj_id, int zone_id )
{
	if( FieldOBJ_StatusBit_CheckEasy(fldobj,FLDOBJ_STA_BIT_USE) == FALSE ){
		return( FALSE );
	}
	
	if( FieldOBJ_OBJIDGet(fldobj) != obj_id ){
		return( FALSE );
	}
	
	if( FieldOBJ_ZoneIDGet(fldobj) != zone_id ){
		if( FieldOBJ_StatusBitCheck_Alies(fldobj) == FALSE ){
			return( FALSE );
		}
		
		if( FieldOBJ_ZoneIDGetAlies(fldobj) != zone_id ){
			return( FALSE );
		}
	}
	
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * フィールドOBJの同一チェック。OBJコード含み
 * 死亡、入れ替わりが発生しているかチェックする。
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	code	同一とみなすOBJコード
 * @param	obj_id	同一とみなすOBJ ID
 * @param	zone_id	同一とみなすZONE ID
 * @retval	int		TRUE=同一。FALSE=同一ではない
 */
//--------------------------------------------------------------
int FieldOBJ_CheckSameIDOBJCodeIn(
		CONST_FIELD_OBJ_PTR fldobj, int code, int obj_id, int zone_id )
{
	if( FieldOBJ_StatusBit_CheckEasy(fldobj,FLDOBJ_STA_BIT_USE) == FALSE ){
		return( FALSE );
	}
	
	{
		int ret = FieldOBJ_OBJCodeGetSeedIn( fldobj );
		
		if( ret != code ){
			return( FALSE );
		}
	}
	
	return( FieldOBJ_CheckSameID(fldobj,obj_id,zone_id) );
}

//==============================================================================
//	動作関数
//==============================================================================
//--------------------------------------------------------------
/**
 * フィールドOBJ TCB 動作関数
 * @param	tcb		TCB_PTR
 * @param	work	tcb work
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FldOBJ_TCB_MoveProc( TCB_PTR tcb, void *work )
{
	FIELD_OBJ_PTR fldobj = (FIELD_OBJ_PTR)work;
	
	FieldOBJ_Move( fldobj );
	
	if( FieldOBJ_StatusBitCheck_Use(fldobj) == FALSE ){
		return;
	}
	
	FldOBJ_TCB_DrawProc( fldobj );
}

//--------------------------------------------------------------
/**
 * フィールドOBJ TCB 動作関数から呼ばれる描画関数
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FldOBJ_TCB_DrawProc( FIELD_OBJ_PTR fldobj )
{
	CONST_FIELD_OBJ_SYS_PTR fos = FieldOBJ_FieldOBJSysGet(fldobj);
	
	if( FieldOBJSys_DrawInitCompCheck(fos) == TRUE ){
		FieldOBJ_Draw( fldobj );
	}
}

//==============================================================================
//	フィールドOBJシステム　参照
//==============================================================================
//--------------------------------------------------------------
/**
 * const FIELD_OBJ_SYSをFIELD_OBJ_SYSに
 * @param	sys		FIELD_OBJ_SYS_PTR 
 * @retval	FIELD_OBJ_SYS	FIELD_OBJ_SYS_PTR 
 */
//--------------------------------------------------------------
static FIELD_OBJ_SYS_PTR  FldOBJ_ConstSysLocalGet( CONST_FIELD_OBJ_SYS_PTR sys )
{
	return( (FIELD_OBJ_SYS_PTR )sys );
}

//--------------------------------------------------------------
/**
 * OBJ登録可能最大数をセット
 * @param	sys		FIELD_OBJ_SYS_PTR 
 * @param	max		最大数
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJSys_OBJMaxSet( FIELD_OBJ_SYS_PTR sys, int max )
{
	sys->fldobj_max = max;
}

//--------------------------------------------------------------
/**
 * OBJ登録可能最大数を取得
 * @param	sys		FIELD_OBJ_SYS_PTR 
 * @retval	int		OBJ最大数
 */
//--------------------------------------------------------------
int FieldOBJSys_OBJMaxGet( CONST_FIELD_OBJ_SYS_PTR sys )
{
	return( sys->fldobj_max );
}

//--------------------------------------------------------------
/**
 * 現在存在しているOBJの数を1増加
 * @param	sys		FIELD_OBJ_SYS_PTR 
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FldOBJSys_OBJCountInc( FIELD_OBJ_SYS_PTR sys )
{
	sys->fldobj_count++;
#ifdef DEBUG_PRINT_FLDOBJ_COUNT
	OS_Printf( "FIELD OBJ ADD, COUNT=0x%x\n", sys->fldobj_count );
#endif
}

//--------------------------------------------------------------
/**
 * 現在存在しているOBJの数を1減らす
 * @param	sys		FIELD_OBJ_SYS_PTR 
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FldOBJSys_OBJCountDec( FIELD_OBJ_SYS_PTR sys )
{
	sys->fldobj_count--;
#ifdef DEBUG_PRINT_FLDOBJ_COUNT
	OS_Printf( "FIELD OBJ DEL, COUNT=0x%x\n", sys->fldobj_count );
#endif
}

//--------------------------------------------------------------
/**
 * 現在存在しているOBJの数をセット
 * @param	sys		FIELD_OBJ_SYS_PTR 
 * @param	count	セットする数
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FldOBJSys_OBJCountSet( FIELD_OBJ_SYS_PTR sys, int count )
{
	sys->fldobj_count = count;
}

//--------------------------------------------------------------
/**
 * 現在存在しているOBJの数を取得
 * @param	fos		FIELD_OBJ_SYS_PTR
 * @retval	int		現在存在しているOBJの数
 */
//--------------------------------------------------------------
int FieldOBJSys_OBJCountGet( CONST_FIELD_OBJ_SYS_PTR fos )
{
	return( fos->fldobj_count );
}

//--------------------------------------------------------------
/**
 * システム　ステータスビット初期化
 * @param	sys		FIELD_OBJ_SYS_PTR 
 * @param	bit		初期化値。FLDOBJSYS_STA_BIT_NON等
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJSys_StatusBit_Init( FIELD_OBJ_SYS_PTR sys, u32 bit )
{
	sys->status_bit = bit;
}

//--------------------------------------------------------------
/**
 * システム　ステータスビット ON
 * @param	sys		FIELD_OBJ_SYS_PTR 
 * @param	bit		ONにするビット。FLDOBJSYS_STA_BIT_NON等
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJSys_StatusBit_ON( FIELD_OBJ_SYS_PTR sys, u32 bit )
{
	sys->status_bit |= bit;
}

//--------------------------------------------------------------
/**
 * システム　ステータスビット OFF
 * @param	sys		FIELD_OBJ_SYS_PTR 
 * @param	bit		OFFにするビット。FLDOBJSYS_STA_BIT_NON等
 * @retval	int		追加されているOBJ数
 */
//--------------------------------------------------------------
void FieldOBJSys_StatusBit_OFF( FIELD_OBJ_SYS_PTR sys, u32 bit )
{
	sys->status_bit &= ~bit;
}

//--------------------------------------------------------------
/**
 * システム　ステータスビット チェック
 * 戻り値はステータスビットとチェックするビットをandした値が返る。
 * 例：対象 FIDOBJSYS_STR_BIT_DRAW_INIT_COMP以外はOFF。
 * チェックするビットはFLDOBJSYS_STA_BIT_DRAW_INIT_COMP|FLDOBJSYS_STA_BIT_MOVE_PROC_STOP
 * 戻り値はFLDOBJSYS_STA_BIT_DRAW_PROC_INITが返る。
 * @param	sys				FIELD_OBJ_SYS_PTR 
 * @param	bit				チェックするビット。FLDOBJ_STA_BIT_USE等
 * @retval	u32				チェック後のビット
 */
//--------------------------------------------------------------
u32 FieldOBJSys_StatusBit_Check( CONST_FIELD_OBJ_SYS_PTR sys, u32 bit )
{
	return( (sys->status_bit&bit) );
}

//--------------------------------------------------------------
/**
 * TCB基本プライオリティをセット
 * @param	sys				FIELD_OBJ_SYS_PTR 
 * @param	pri				TCB基本プライオリティ
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJSys_TCBStandardPrioritySet( FIELD_OBJ_SYS_PTR sys, int pri )
{
	sys->tcb_pri = pri;
}

//--------------------------------------------------------------
/**
 * TCB基本プライオリティ取得
 * @param	sys			FIELD_OBJ_SYS_PTR 
 * @retval	u32			TCBプライオリティ
 */
//--------------------------------------------------------------
int FieldOBJSys_TCBStandardPriorityGet( CONST_FIELD_OBJ_SYS_PTR sys )
{
	return( sys->tcb_pri );
}

//--------------------------------------------------------------
/**
 * FIELD_OBJ_BLACT_CONT *取得
 * @param	sys		FIELD_OBJ_SYS_PTR 
 * @retval	FIELD_OBJ_BLACT_CONT	FIELD_OBJ_BLACT_CONT *
 */
//--------------------------------------------------------------
FIELD_OBJ_BLACT_CONT * FieldOBJSys_BlActContGet( CONST_FIELD_OBJ_SYS_PTR sys )
{
	return( &(((FIELD_OBJ_SYS_PTR)sys)->blact_cont) );
}

//--------------------------------------------------------------
/**
 * FIELD_OBJ_RENDER_CONT_PTRセット
 * @param	sys		FIELD_OBJ_SYS_PTR 
 * @param	render	FIELD_OBJ_RENDER_CONT_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJSys_RenderContSet( FIELD_OBJ_SYS_PTR sys, FIELD_OBJ_RENDER_CONT_PTR render )
{
	sys->render_cont = render;
}

//--------------------------------------------------------------
/**
 * FIELD_OBJ_RENDER_CONT_PTR 取得
 * @param	sys		FIELD_OBJ_SYS_PTR 
 * @retval	FIELD_OBJ_RENDER_CONT_PTR FIELD_OBJ_RENDER_CONT_PTR
 */
//--------------------------------------------------------------
FIELD_OBJ_RENDER_CONT_PTR FieldOBJSys_RenderContGet( CONST_FIELD_OBJ_SYS_PTR sys )
{
	return( sys->render_cont );
}

//--------------------------------------------------------------
/**
 * フィールドOBJワークをセット
 * @param	sys		FIELD_OBJ_SYS_PTR 
 * @param	ptr		FIELD_OBJ_PTR 
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJSys_FieldOBJWorkSet( FIELD_OBJ_SYS_PTR sys, FIELD_OBJ_PTR ptr )
{
	sys->fldobj_work = ptr;
}

//--------------------------------------------------------------
/**
 * フィールドOBJワーク取得
 * @param	sys			FIELD_OBJ_SYS_PTR 
 * @retval	FIELD_OBJ	FIELD_OBJ_PTR 
 */
//--------------------------------------------------------------
CONST_FIELD_OBJ_PTR  FieldOBJSys_FieldOBJWorkGet( CONST_FIELD_OBJ_SYS_PTR sys )
{
	return( sys->fldobj_work );
}

//--------------------------------------------------------------
/**
 * フィールドOBJワーク取得　ローカル
 * @param	sys			FIELD_OBJ_SYS_PTR 
 * @retval	FIELD_OBJ	FIELD_OBJ_PTR 
 */
//--------------------------------------------------------------
static FIELD_OBJ_PTR FldOBJSys_FieldOBJWorkGet( CONST_FIELD_OBJ_SYS_PTR sys )
{
	return( sys->fldobj_work );
}

//--------------------------------------------------------------
/**
 * フィールドOBJワーク取得　FIELD OBJローカル用
 * const無し。フィールドOBJ以外は使用禁止
 * @param	sys			FIELD_OBJ_SYS_PTR 
 * @retval	FIELD_OBJ	FIELD_OBJ_PTR 
 */
//--------------------------------------------------------------
FIELD_OBJ_PTR  FieldOBJSys_FldOBJWorkGet( CONST_FIELD_OBJ_SYS_PTR sys )
{
	return( sys->fldobj_work );
}

//--------------------------------------------------------------
/**
 * フィールドOBJワーク進行。
 * FieldOBJSys_FieldOBJWorkGet()で取得したポインタを１つ進める。
 * @param	FIELD_OBJ	FIELD_OBJ_PTR 
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJSys_FieldOBJWorkInc( CONST_FIELD_OBJ_PTR *fldobj )
{
	(*fldobj)++;
}

//--------------------------------------------------------------
/**
 * フィールドOBJワーク進行。非const
 * FieldOBJSys_FieldOBJWorkGet()で取得したポインタを１つ進める。
 * @param	FIELD_OBJ	FIELD_OBJ_PTR 
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJSys_FldOBJWorkInc( FIELD_OBJ_PTR *fldobj )
{
	(*fldobj)++;
}

//--------------------------------------------------------------
/**
 * FIELDSYS_WORK *セット
 * @param	fos		FIELD_OBJ_SYS_PTR
 * @param	fsys	FIELDSYS_WORK *
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJSys_FieldSysWorkSet( FIELD_OBJ_SYS_PTR fos, FIELDSYS_WORK *fsys )
{
	fos->fieldsys = fsys;
}

//--------------------------------------------------------------
/**
 * FIELDSYS_WORK *取得
 * @param	fos		FIELD_OBJ_SYS_PTR
 * @retval	FIELDSYS_WORK	FIELDSYS_WORK *
 */
//--------------------------------------------------------------
FIELDSYS_WORK * FieldOBJSys_FieldSysWorkGet( CONST_FIELD_OBJ_SYS_PTR fos )
{
	return( fos->fieldsys );
}

//--------------------------------------------------------------
/**
 * アーカイブハンドルセット
 * @param	fos		FIELD_OBJ_SYS_PTR
 * @param	handle	ARCHANDLE *
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJSys_ArcHandleSet( FIELD_OBJ_SYS_PTR fos, ARCHANDLE *handle )
{
	fos->archandle = handle;
}

//--------------------------------------------------------------
/**
 * アーカイブハンドル取得
 * @param	fos		FIELD_OBJ_SYS_PTR
 * @retval	ARCHANDLE*　ARCHANDLE *
 */
//--------------------------------------------------------------
ARCHANDLE * FieldOBJSys_ArcHandleGet( CONST_FIELD_OBJ_SYS_PTR fos )
{
	GF_ASSERT( fos->archandle != NULL && "FieldOBJSys_ArcHandleGet()ハンドル無し" );
	return( ((FIELD_OBJ_SYS_PTR)fos)->archandle );
}

//==============================================================================
//	フィールドOBJ　参照
//==============================================================================
//--------------------------------------------------------------
/**
 * ステータスビット初期化
 * @param	fldobj			FIELD_OBJ_PTR 
 * @param	bit				初期化値。FLDOBJ_STA_BIT_USE等
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_StatusBit_Init( FIELD_OBJ_PTR fldobj, u32 bit )
{
	fldobj->status_bit = bit;
}

//--------------------------------------------------------------
/**
 * ステータスビット取得
 * @param	fldobj			FIELD_OBJ_PTR 
 * @retval	u32				ステータスビット
 */
//--------------------------------------------------------------
u32 FieldOBJ_StatusBit_Get( CONST_FIELD_OBJ_PTR fldobj )
{
	return( fldobj->status_bit );
}

//--------------------------------------------------------------
/**
 * ステータスビット ON
 * @param	fldobj			FIELD_OBJ_PTR 
 * @param	bit				ONにしたいビット。FLDOBJ_STA_BIT_USE等
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_StatusBit_ON( FIELD_OBJ_PTR fldobj, u32 bit )
{
	fldobj->status_bit |= bit;
}

//--------------------------------------------------------------
/**
 * ステータスビット OFF
 * @param	fldobj			FIELD_OBJ_PTR 
 * @param	bit				OFFにしたいビット。FLDOBJ_STA_BIT_USE等
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_StatusBit_OFF( FIELD_OBJ_PTR fldobj, u32 bit )
{
	fldobj->status_bit &= ~bit;
}

//--------------------------------------------------------------
/**
 * ステータスビット チェック
 * 戻り値はステータスビットとチェックするビットをandした値が返る。
 * 
 * 例：対象OBJのステータスビットはFIDOBJ_STR_BIT_USE以外はOFF。
 * チェックするビットはFLDOBJ_STA_BIT_USE|FLDOBJ_STA_BIT_MOVE_START。
 * 戻り値はFLDOBJ_STA_BIT_USEが返る。
 * 
 * @param	fldobj			FIELD_OBJ_PTR 
 * @param	bit				チェックするビット。FLDOBJ_STA_BIT_USE等
 * @retval	u32				チェック後のビット
 */
//--------------------------------------------------------------
u32 FieldOBJ_StatusBit_Check( CONST_FIELD_OBJ_PTR fldobj, u32 bit )
{
	return( fldobj->status_bit & bit );
}

//--------------------------------------------------------------
/**
 * ステータスビット 簡易チェック
 * @param	fldobj			FIELD_OBJ_PTR 
 * @param	bit				チェックするビット。FLDOBJ_STA_BIT_USE等
 * @retval	u32				TRUE=bitのどれかが該当。FALSE=該当無し
 */
//--------------------------------------------------------------
u32 FieldOBJ_StatusBit_CheckEasy( CONST_FIELD_OBJ_PTR fldobj, u32 bit )
{
	if( (fldobj->status_bit&bit) ){
		return( TRUE );
	}
	
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * 動作ビット　初期化
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	bit		初期化するビット FLDOBJ_MOVE_BIT_NON等
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_MoveBit_Init( FIELD_OBJ_PTR fldobj, u32 bit )
{
	fldobj->move_bit = bit;
}

//--------------------------------------------------------------
/**
 * 動作ビット　取得
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	u32		動作ビット
 */
//--------------------------------------------------------------
u32 FieldOBJ_MoveBit_Get( CONST_FIELD_OBJ_PTR fldobj )
{
	return( fldobj->move_bit );
}

//--------------------------------------------------------------
/**
 * 動作ビット　ON
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	bit		立てるビット FLDOBJ_MOVE_BIT_NON等
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_MoveBit_ON( FIELD_OBJ_PTR fldobj, u32 bit )
{
	fldobj->move_bit |= bit;
}

//--------------------------------------------------------------
/**
 * 動作ビット　OFF
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	bit		下ろすビット FLDOBJ_MOVE_BIT_NON等
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_MoveBit_OFF( FIELD_OBJ_PTR fldobj, u32 bit )
{
	fldobj->move_bit &= ~bit;
}

//--------------------------------------------------------------
/**
 * 動作ビット　チェック
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	bit		チェックするビット FLDOBJ_MOVE_BIT_NON等
 * @retval	nothing
 */
//--------------------------------------------------------------
u32 FieldOBJ_MoveBit_Check( CONST_FIELD_OBJ_PTR fldobj, u32 bit )
{
	return( (fldobj->move_bit & bit) );
}

//--------------------------------------------------------------
/**
 * OBJ IDセット
 * @param	fldobj	FIELD_OBJ_PTR 
 * @param	id		obj id
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_OBJIDSet( FIELD_OBJ_PTR fldobj, u32 obj_id )
{
	fldobj->obj_id = obj_id;
}

//--------------------------------------------------------------
/**
 * OBJ ID取得
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	u32		OBJ ID
 */
//--------------------------------------------------------------
u32 FieldOBJ_OBJIDGet( CONST_FIELD_OBJ_PTR fldobj )
{
	return( fldobj->obj_id );
}

//--------------------------------------------------------------
/**
 * ZONE IDセット
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	zone_id	ゾーンID
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_ZoneIDSet( FIELD_OBJ_PTR fldobj, int zone_id )
{
	fldobj->zone_id = zone_id;
}

//--------------------------------------------------------------
/**
 * ZONE ID取得
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	int		ZONE ID
 */
//--------------------------------------------------------------
int FieldOBJ_ZoneIDGet( CONST_FIELD_OBJ_PTR fldobj )
{
	return( fldobj->zone_id );
}

//--------------------------------------------------------------
/**
 * OBJコードセット
 * @param	fldobj			FIELD_OBJ_PTR 
 * @param	code			セットするコード
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_OBJCodeSet( FIELD_OBJ_PTR fldobj, u32 code )
{
	fldobj->obj_code = code;
}

//--------------------------------------------------------------
/**
 * OBJコード取得
 * @param	fldobj			FIELD_OBJ_PTR 
 * @retval	u32				OBJコード
 */
//--------------------------------------------------------------
u32 FieldOBJ_OBJCodeGet( CONST_FIELD_OBJ_PTR fldobj )
{
	return( fldobj->obj_code );
}

//--------------------------------------------------------------
/**
 * OBJコード取得　種チェックあり
 * @param	fldobj			FIELD_OBJ_PTR 
 * @retval	u32				OBJコード
 */
//--------------------------------------------------------------
u32 FieldOBJ_OBJCodeGetSeedIn( CONST_FIELD_OBJ_PTR fldobj )
{
	u32 code = FieldOBJ_OBJCodeGet( fldobj );
	
	if( FieldOBJ_OBJCodeSeedCheck(code) == TRUE ){
		code = FieldOBJ_OBJCodeSeedGet( fldobj );
	}
	
	return( code );
}

//--------------------------------------------------------------
/**
 * 動作コードセット
 * @param	fldobj			FIELD_OBJ_PTR 
 * @param	code			動作コード
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_MoveCodeSet( FIELD_OBJ_PTR fldobj, u32 code )
{
	fldobj->move_code = code;
}

//--------------------------------------------------------------
/**
 * 動作コード取得
 * @param	fldobj			FIELD_OBJ_PTR 
 * @retval	u32				動作コード
 */
//--------------------------------------------------------------
u32 FieldOBJ_MoveCodeGet( CONST_FIELD_OBJ_PTR fldobj )
{
	return( fldobj->move_code );
}

//--------------------------------------------------------------
/**
 * イベントタイプセット
 * @param	fldobj		FIELD_OBJ_PTR 
 * @param	type		Event Type
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_EventTypeSet( FIELD_OBJ_PTR fldobj, u32 type )
{
	fldobj->event_type = type;
}

//--------------------------------------------------------------
/**
 * イベントタイプ取得
 * @param	fldobj		FIELD_OBJ_PTR 
 * @retval	u32			Event Type
 */
//--------------------------------------------------------------
u32 FieldOBJ_EventTypeGet( CONST_FIELD_OBJ_PTR fldobj )
{
	return( fldobj->event_type );
}

//--------------------------------------------------------------
/**
 * イベントフラグセット
 * @param	fldobj		FIELD_OBJ_PTR 
 * @param	flag		Event Flag
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_EventFlagSet( FIELD_OBJ_PTR fldobj, u32 flag )
{
	fldobj->event_flag = flag;
}

//--------------------------------------------------------------
/**
 * イベントフラグ取得
 * @param	fldobj		FIELD_OBJ_PTR 
 * @retval	u32			Event Flag
 */
//--------------------------------------------------------------
u32 FieldOBJ_EventFlagGet( CONST_FIELD_OBJ_PTR fldobj )
{
	return( fldobj->event_flag );
}

//--------------------------------------------------------------
/**
 * イベントIDセット
 * @param	fldobj		FIELD_OBJ_PTR 
 * @param	id			Event ID
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_EventIDSet( FIELD_OBJ_PTR fldobj, u32 id )
{
	fldobj->event_id = id;
}

//--------------------------------------------------------------
/**
 * イベントID取得
 * @param	fldobj		FIELD_OBJ_PTR 
 * @retval	u32			Event ID
 */
//--------------------------------------------------------------
u32 FieldOBJ_EventIDGet( CONST_FIELD_OBJ_PTR fldobj )
{
	return( fldobj->event_id );
}

//--------------------------------------------------------------
/**
 * ヘッダー指定方向セット
 * @param	fldobj		FIELD_OBJ_PTR 
 * @param	dir			DIR_UP等
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_DirHeaderSet( FIELD_OBJ_PTR fldobj, int dir )
{
	fldobj->dir_head = dir;
}

//--------------------------------------------------------------
/**
 * ヘッダー指定方向取得
 * @param	fldobj		FIELD_OBJ_PTR 
 * @retval	u32			DIR_UP等
 */
//--------------------------------------------------------------
u32 FieldOBJ_DirHeaderGet( CONST_FIELD_OBJ_PTR fldobj )
{
	return( fldobj->dir_head );
}

//--------------------------------------------------------------
/**
 * 表示方向セット　強制
 * @param	fldobj			FIELD_OBJ_PTR 
 * @param	dir				DIR_UP等
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_DirDispSetForce( FIELD_OBJ_PTR fldobj, int dir )
{
	fldobj->dir_disp_old = fldobj->dir_disp;
	fldobj->dir_disp = dir;
}

//--------------------------------------------------------------
/**
 * 表示方向セット　FLDOBJ_STA_BIT_PAUSE_DIRチェックあり
 * @param	fldobj			FIELD_OBJ_PTR 
 * @param	dir				DIR_UP等
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_DirDispCheckSet( FIELD_OBJ_PTR fldobj, int dir )
{
	if( FieldOBJ_StatusBit_Check(fldobj,FLDOBJ_STA_BIT_PAUSE_DIR) == 0 ){
		fldobj->dir_disp_old = fldobj->dir_disp;
		fldobj->dir_disp = dir;
	}
}

//--------------------------------------------------------------
/**
 * 表示方向取得
 * @param	fldobj			FIELD_OBJ_PTR 
 * @param	dir				DIR_UP等
 * @retval	nothing
 */
//--------------------------------------------------------------
int FieldOBJ_DirDispGet( CONST_FIELD_OBJ_PTR fldobj )
{
	return( fldobj->dir_disp );
}

//--------------------------------------------------------------
/**
 * 過去表示方向取得
 * @param	fldobj			FIELD_OBJ_PTR 
 * @param	dir				DIR_UP等
 * @retval	nothing
 */
//--------------------------------------------------------------
int FieldOBJ_DirDispOldGet( CONST_FIELD_OBJ_PTR fldobj )
{
	return( fldobj->dir_disp_old );
}

//--------------------------------------------------------------
/**
 * 移動方向セット
 * @param	fldobj			FIELD_OBJ_PTR 
 * @param	dir				DIR_UP等
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_DirMoveSet( FIELD_OBJ_PTR fldobj, int dir )
{
	fldobj->dir_move_old = fldobj->dir_move;
	fldobj->dir_move = dir;
}

//--------------------------------------------------------------
/**
 * 移動方向取得
 * @param	fldobj			FIELD_OBJ_PTR 
 * @retval	dir				DIR_UP等
 */
//--------------------------------------------------------------
int FieldOBJ_DirMoveGet( CONST_FIELD_OBJ_PTR fldobj )
{
	return( fldobj->dir_move );
}

//--------------------------------------------------------------
/**
 * 過去移動方向取得
 * @param	fldobj			FIELD_OBJ_PTR 
 * @retval	dir				DIR_UP等
 */
//--------------------------------------------------------------
int FieldOBJ_DirMoveOldGet( CONST_FIELD_OBJ_PTR fldobj )
{
	return( fldobj->dir_move_old );
}

//--------------------------------------------------------------
/**
 * 表示、移動方向セット　FLDOBJ_STA_BIT_PAUSE_DIRチェックあり
 * @param	fldobj			FIELD_OBJ_PTR 
 * @param	dir				DIR_UP等
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_DirMoveDispCheckSet( FIELD_OBJ_PTR fldobj, int dir )
{
	FieldOBJ_DirDispCheckSet( fldobj, dir );
	FieldOBJ_DirMoveSet( fldobj, dir );
}

//--------------------------------------------------------------
/**
 * ヘッダー指定パラメタセット
 * @param	fldobj			FIELD_OBJ_PTR 
 * @param	param			パラメタ
 * @param	no				セットするパラメタ番号　FLDOBJ_PARAM_0等
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_ParamSet( FIELD_OBJ_PTR fldobj, int param, FLDOBJ_H_PARAM no )
{
	switch( no ){
	case FLDOBJ_PARAM_0: fldobj->param0 = param; break;
	case FLDOBJ_PARAM_1: fldobj->param1 = param; break;
	case FLDOBJ_PARAM_2: fldobj->param2 = param; break;
	default: GF_ASSERT( 0 && "FieldOBJ_ParamSet()不正な引数" );
	}
}

//--------------------------------------------------------------
/**
 * ヘッダー指定パラメタ取得
 * @param	fldobj			FIELD_OBJ_PTR
 * @param	param			FLDOBJ_PARAM_0等
 * @retval	int				パラメタ
 */
//--------------------------------------------------------------
int FieldOBJ_ParamGet( CONST_FIELD_OBJ_PTR fldobj, FLDOBJ_H_PARAM param )
{
	switch( param ){
	case FLDOBJ_PARAM_0: return( fldobj->param0 );
	case FLDOBJ_PARAM_1: return( fldobj->param1 );
	case FLDOBJ_PARAM_2: return( fldobj->param2 );
	}
	
	GF_ASSERT( 0 && "FieldOBJ_ParamGet()不正な引数" );
	return( 0 );
}

//--------------------------------------------------------------
/**
 * 移動制限Xセット
 * @param	fldobj			FIELD_OBJ_PTR 
 * @param	x				移動制限
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_MoveLimitXSet( FIELD_OBJ_PTR fldobj, int x )
{
	fldobj->move_limit_x = x;
}

//--------------------------------------------------------------
/**
 * 移動制限X取得
 * @param	fldobj		FIELD_OBJ_PTR 
 * @retval	int			移動制限X
 */
//--------------------------------------------------------------
int FieldOBJ_MoveLimitXGet( CONST_FIELD_OBJ_PTR fldobj )
{
	return( fldobj->move_limit_x );
}

//--------------------------------------------------------------
/**
 * 移動制限Zセット
 * @param	fldobj			FIELD_OBJ_PTR 
 * @param	y				移動制限
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_MoveLimitZSet( FIELD_OBJ_PTR fldobj, int z )
{
	fldobj->move_limit_z = z;
}

//--------------------------------------------------------------
/**
 * 移動制限Z取得
 * @param	fldobj		FIELD_OBJ_PTR 
 * @retval	int			移動制限z
 */
//--------------------------------------------------------------
int FieldOBJ_MoveLimitZGet( CONST_FIELD_OBJ_PTR fldobj )
{
	return( fldobj->move_limit_z );
}

//--------------------------------------------------------------
/**
 * 描画ステータスセット
 * @param	fldobj		FIELD_OBJ_PTR 
 * @param	st			DRAW_STA_STOP等
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_DrawStatusSet( FIELD_OBJ_PTR fldobj, u32 st )
{
	fldobj->draw_status = st;
}

//--------------------------------------------------------------
/**
 * 描画ステータス取得
 * @param	fldobj		FIELD_OBJ_PTR 
 * @retval	u32			DRAW_STA_STOP等
 */
//--------------------------------------------------------------
u32 FieldOBJ_DrawStatusGet( CONST_FIELD_OBJ_PTR fldobj )
{
	return( fldobj->draw_status );
}

//--------------------------------------------------------------
/**
 * 動作TCB*セット
 * @param	fldobj			FIELD_OBJ_PTR 
 * @param	tcb				TCB_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_MoveTcbPtrSet( FIELD_OBJ_PTR fldobj, TCB_PTR tcb )
{
	fldobj->tcb = tcb;
}

//--------------------------------------------------------------
/**
 * 動作TCB*取得
 * @param	fldobj			FIELD_OBJ_PTR 
 * @retval	TCB_PTR			TCB_PTR
 */
//--------------------------------------------------------------
TCB_PTR FieldOBJ_MoveTcbPtrGet( CONST_FIELD_OBJ_PTR fldobj )
{
	return( fldobj->tcb );
}

//--------------------------------------------------------------
/**
 * 動作TCB*を削除
 * @param	fldobj			FIELD_OBJ_PTR 
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_MoveTcbDelete( CONST_FIELD_OBJ_PTR fldobj )
{
	TCB_Delete( FieldOBJ_MoveTcbPtrGet(fldobj) );
}

//--------------------------------------------------------------
/**
 * FIELD_OBJ_SYS_PTR セット
 * @param	fldobj			FIELD_OBJ_PTR 
 * @param	sys				FIELD_OBJ_SYS_PTR 
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_FieldOBJSysSet( FIELD_OBJ_PTR fldobj, CONST_FIELD_OBJ_SYS_PTR sys )
{
	fldobj->fldobj_sys = sys;
}

//--------------------------------------------------------------
/**
 * FIELD_OBJ_SYS_PTR 取得
 * @param	fldobj			FIELD_OBJ_PTR 
 * @retval	FIELD_OBJ_SYS	FIELD_OBJ_SYS_PTR 
 */
//--------------------------------------------------------------
CONST_FIELD_OBJ_SYS_PTR FieldOBJ_FieldOBJSysGet( CONST_FIELD_OBJ_PTR fldobj )
{
	return( fldobj->fldobj_sys );
}

//--------------------------------------------------------------
/**
 * FIELD_OBJ_SYS_PTR  取得 not const
 * @param	fldobj			FIELD_OBJ_PTR 
 * @retval	FIELD_OBJ_SYS	FIELD_OBJ_SYS_PTR 
 */
//--------------------------------------------------------------
static FIELD_OBJ_SYS_PTR FldOBJ_FieldOBJSysGet( CONST_FIELD_OBJ_PTR fldobj )
{
	return( FldOBJ_ConstSysLocalGet(fldobj->fldobj_sys) );
}

//--------------------------------------------------------------
/**
 * 動作関数用ワーク初期化。
 * sizeがワークサイズを超えていた場合、ASSERT。
 * 動作用ワークはsize分、0で初期化。
 * @param	fldobj	FIELD_OBJ_PTR 
 * @param	size	必要なワークサイズ
 * @retval	void*	初期化されたワーク
 */
//--------------------------------------------------------------
void * FieldOBJ_MoveProcWorkInit( FIELD_OBJ_PTR fldobj, int size )
{
	void *work;
	
	GF_ASSERT( size <= FLDOBJ_MOVE_WORK_SIZE && "fldobj move work size over" );
	
	work = FieldOBJ_MoveProcWorkGet( fldobj );
	memset( work, 0, size );
	
	return( work );
}

//--------------------------------------------------------------
/**
 * 動作関数用ワーク取得。
 * @param	fldobj	FIELD_OBJ_PTR 
 * @retval	void*	ワーク
 */
//--------------------------------------------------------------
void * FieldOBJ_MoveProcWorkGet( FIELD_OBJ_PTR fldobj )
{
	return( fldobj->move_proc_work );
}

//--------------------------------------------------------------
/**
 * 動作補助関数用ワーク初期化。
 * sizeがワークサイズを超えていた場合、ASSERT。
 * @param	fldobj	FIELD_OBJ_PTR 
 * @param	size	必要なワークサイズ
 * @retval	void*	初期化されたワーク
 */
//--------------------------------------------------------------
void * FieldOBJ_MoveSubProcWorkInit( FIELD_OBJ_PTR fldobj, int size )
{
	u8 *work;
	
	GF_ASSERT( size <= FLDOBJ_MOVE_SUB_WORK_SIZE &&
			"フィールドOBJ 動作補助ワークサイズがオーバー" );
	
	work = FieldOBJ_MoveSubProcWorkGet( fldobj );
	memset( work, 0, size );
	
	return( work );
}

//--------------------------------------------------------------
/**
 * 動作補助関数用ワーク取得
 * @param	fldobj	FIELD_OBJ_PTR 
 * @retval	void*	ワーク*
 */
//--------------------------------------------------------------
void * FieldOBJ_MoveSubProcWorkGet( FIELD_OBJ_PTR fldobj )
{
	return( fldobj->move_sub_proc_work );
}

//--------------------------------------------------------------
/**
 * 動作補助関数用ワーク初期化。
 * sizeがワークサイズを超えていた場合、ASSERT。
 * @param	fldobj	FIELD_OBJ_PTR 
 * @param	size	必要なワークサイズ
 * @retval	void*	初期化されたワーク
 */
//--------------------------------------------------------------
void * FieldOBJ_MoveCmdWorkInit( FIELD_OBJ_PTR fldobj, int size )
{
	u8 *work;
	
	GF_ASSERT( size <= FLDOBJ_MOVE_CMD_WORK_SIZE &&
			"フィールドOBJ 動作コマンドワークサイズがオーバー" );
	
	work = FieldOBJ_MoveCmdWorkGet( fldobj );
	memset( work, 0, size );
	
	return( work );
}

//--------------------------------------------------------------
/**
 * 動作コマンド用ワーク取得
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	void*	ワーク*
 */
//--------------------------------------------------------------
void * FieldOBJ_MoveCmdWorkGet( FIELD_OBJ_PTR fldobj )
{
	return( fldobj->move_cmd_proc_work );
}

//--------------------------------------------------------------
/**
 * 描画関数用ワーク初期化。
 * sizeがワークサイズを超えていた場合、ASSERT。
 * @param	fldobj	FIELD_OBJ_PTR 
 * @param	size	必要なワークサイズ
 * @retval	void*	初期化されたワーク
 */
//--------------------------------------------------------------
void * FieldOBJ_DrawProcWorkInit( FIELD_OBJ_PTR fldobj, int size )
{
	u8 *work;
	
	GF_ASSERT( size <= FLDOBJ_DRAW_WORK_SIZE && "fldobj draw work size over" );
	
	work = FieldOBJ_DrawProcWorkGet( fldobj );
	memset( work, 0, size );
	
	return( work );
}

//--------------------------------------------------------------
/**
 * 描画関数用ワーク取得
 * @param	fldobj	FIELD_OBJ_PTR 
 * @retval	void*	ワーク
 */
//--------------------------------------------------------------
void * FieldOBJ_DrawProcWorkGet( FIELD_OBJ_PTR fldobj )
{
	return( fldobj->draw_proc_work );
}

//--------------------------------------------------------------
/**
 * 初期化関数セット
 * @param	fldobj	FIELD_OBJ_PTR 
 * @param	init	初期化関数
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_MoveInitProcSet( FIELD_OBJ_PTR fldobj, FIELD_OBJ_MOVE_PROC_INIT init )
{
	fldobj->move_init_proc = init;
}

//--------------------------------------------------------------
/**
 * 初期化関数実行
 * @param	fldobj	FIELD_OBJ_PTR 
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_MoveInitProcCall( FIELD_OBJ_PTR fldobj )
{
	fldobj->move_init_proc( fldobj );
}

//--------------------------------------------------------------
/**
 * 動作関数セット
 * @param	fldobj	FIELD_OBJ_PTR 
 * @param	move	動作関数
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_MoveProcSet( FIELD_OBJ_PTR fldobj, FIELD_OBJ_MOVE_PROC move )
{
	fldobj->move_proc = move;
}

//--------------------------------------------------------------
/**
 * 動作関数実行
 * @param	fldobj	FIELD_OBJ_PTR 
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_MoveProcCall( FIELD_OBJ_PTR fldobj )
{
	fldobj->move_proc( fldobj );
}

//--------------------------------------------------------------
/**
 * 削除関数登録
 * @param	fldobj	FIELD_OBJ_PTR 
 * @param	del		動作関数
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_MoveDeleteProcSet( FIELD_OBJ_PTR fldobj, FIELD_OBJ_MOVE_PROC_DEL del )
{
	fldobj->move_delete_proc = del;
}

//--------------------------------------------------------------
/**
 * 削除関数実行
 * @param	fldobj	FIELD_OBJ_PTR 
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_MoveDeleteProcCall( FIELD_OBJ_PTR fldobj )
{
	fldobj->move_delete_proc( fldobj );
}

#if 0
//--------------------------------------------------------------
/**
 * 復帰関数登録
 * @param	fldobj	FIELD_OBJ_PTR 
 * @param	del		動作関数
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_MoveReturnProcSet( FIELD_OBJ_PTR fldobj, FIELD_OBJ_MOVE_PROC_RET ret )
{
	GF_ASSERT( 0 );
//	fldobj->move_return_proc = ret;
}
#endif

//--------------------------------------------------------------
/**
 * 復帰関数実行
 * @param	fldobj	FIELD_OBJ_PTR 
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_MoveReturnProcCall( FIELD_OBJ_PTR fldobj )
{
#if 0
	fldobj->move_return_proc( fldobj );
#else
	const FIELD_OBJ_MOVE_PROC_LIST *list =
		FldOBJ_MoveProcListGet( FieldOBJ_MoveCodeGet(fldobj) );
	list->return_proc( fldobj );
#endif
}

//--------------------------------------------------------------
/**
 * 描画初期化関数登録
 * @param	fldobj	FIELD_OBJ_PTR 
 * @param	init	初期化関数
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_DrawInitProcSet( FIELD_OBJ_PTR fldobj, FIELD_OBJ_DRAW_PROC_INIT init )
{
	fldobj->draw_init_proc = init;
}

//--------------------------------------------------------------
/**
 * 描画初期化関数実行
 * @param	fldobj	FIELD_OBJ_PTR 
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_DrawInitProcCall( FIELD_OBJ_PTR fldobj )
{
	fldobj->draw_init_proc( fldobj );
}

//--------------------------------------------------------------
/**
 * 描画関数登録
 * @param	fldobj	FIELD_OBJ_PTR 
 * @param	draw	描画関数
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_DrawProcSet( FIELD_OBJ_PTR fldobj, FIELD_OBJ_DRAW_PROC draw )
{
	fldobj->draw_proc = draw;
}

//--------------------------------------------------------------
/**
 * 描画関数実行
 * @param	fldobj	FIELD_OBJ_PTR 
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_DrawProcCall( FIELD_OBJ_PTR fldobj )
{
	fldobj->draw_proc( fldobj );
}

//--------------------------------------------------------------
/**
 * 描画削除関数登録
 * @param	fldobj	FIELD_OBJ_PTR 
 * @param	del		削除関数
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_DrawDeleteProcSet( FIELD_OBJ_PTR fldobj, FIELD_OBJ_DRAW_PROC_DEL del )
{
	fldobj->draw_delete_proc = del;
}

//--------------------------------------------------------------
/**
 * 描画削除関数実行
 * @param	fldobj	FIELD_OBJ_PTR 
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_DrawDeleteProcCall( FIELD_OBJ_PTR fldobj )
{
	fldobj->draw_delete_proc( fldobj );
}

//--------------------------------------------------------------
/**
 * 描画退避関数登録
 * @param	fldobj	FIELD_OBJ_PTR 
 * @param	push	退避関数
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_DrawPushProcSet( FIELD_OBJ_PTR fldobj, FIELD_OBJ_DRAW_PROC_PUSH push )
{
	fldobj->draw_push_proc = push;
}

//--------------------------------------------------------------
/**
 * 描画退避関数実行
 * @param	fldobj	FIELD_OBJ_PTR 
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_DrawPushProcCall( FIELD_OBJ_PTR fldobj )
{
	fldobj->draw_push_proc( fldobj );
}

//--------------------------------------------------------------
/**
 * 描画復帰関数登録
 * @param	fldobj	FIELD_OBJ_PTR 
 * @param	pop		退避関数
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_DrawPopProcSet( FIELD_OBJ_PTR fldobj, FIELD_OBJ_DRAW_PROC_POP pop )
{
	fldobj->draw_pop_proc = pop;
}

//--------------------------------------------------------------
/**
 * 描画復帰関数実行
 * @param	fldobj	FIELD_OBJ_PTR 
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_DrawPopProcCall( FIELD_OBJ_PTR fldobj )
{
	fldobj->draw_pop_proc( fldobj );
}

//--------------------------------------------------------------
/**
 * アニメーションコマンドコードセット
 * @param	fldobj	FIELD_OBJ_PTR 
 * @param	code	AC_DIR_U等
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_AcmdCodeSet( FIELD_OBJ_PTR fldobj, int code )
{
	fldobj->acmd_code = code;
}

//--------------------------------------------------------------
/**
 * アニメーションコマンドコード取得
 * @param	fldobj	FIELD_OBJ_PTR 
 * @retval	int		AC_DIR_U等
 */
//--------------------------------------------------------------
int FieldOBJ_AcmdCodeGet( CONST_FIELD_OBJ_PTR fldobj )
{
	return( fldobj->acmd_code );
}

//--------------------------------------------------------------
/**
 * アニメーションコマンドシーケンスセット
 * @param	fldobj	FIELD_OBJ_PTR 
 * @param	no		シーケンス
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_AcmdSeqSet( FIELD_OBJ_PTR fldobj, int no )
{
	fldobj->acmd_seq = no;
}

//--------------------------------------------------------------
/**
 * アニメーションコマンドシーケンス増加
 * @param	fldobj	FIELD_OBJ_PTR 
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_AcmdSeqInc( FIELD_OBJ_PTR fldobj )
{
	fldobj->acmd_seq++;
}

//--------------------------------------------------------------
/**
 * アニメーションコマンドシーケンス取得
 * @param	fldobj	FIELD_OBJ_PTR 
 * @retval	int		シーケンス
 */
//--------------------------------------------------------------
int FieldOBJ_AcmdSeqGet( CONST_FIELD_OBJ_PTR fldobj )
{
	return( fldobj->acmd_seq );
}

//--------------------------------------------------------------
/**
 * 現在のマップアトリビュートをセット
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	attr	セットするアトリビュート
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_NowMapAttrSet( FIELD_OBJ_PTR fldobj, u32 attr )
{
	fldobj->now_attr = attr;
}

//--------------------------------------------------------------
/**
 * 現在のマップアトリビュートを取得
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	u32		マップアトリビュート
 */
//--------------------------------------------------------------
u32 FieldOBJ_NowMapAttrGet( CONST_FIELD_OBJ_PTR fldobj )
{
	return( fldobj->now_attr );
}

//--------------------------------------------------------------
/**
 * 過去のマップアトリビュートをセット
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	attr	セットするアトリビュート
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_OldMapAttrSet( FIELD_OBJ_PTR fldobj, u32 attr )
{
	fldobj->old_attr = attr;
}

//--------------------------------------------------------------
/**
 * 過去のマップアトリビュートを取得
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	u32		マップアトリビュート
 */
//--------------------------------------------------------------
u32 FieldOBJ_OldMapAttrGet( CONST_FIELD_OBJ_PTR fldobj )
{
	return( fldobj->old_attr );
}

//--------------------------------------------------------------
/**
 * FIELDSYS_WORK取得
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	FIELDSYS_WORK	FIELDSYS_WORK *
 */
//--------------------------------------------------------------
FIELDSYS_WORK * FieldOBJ_FieldSysWorkGet( CONST_FIELD_OBJ_PTR fldobj )
{
	FIELD_OBJ_SYS_PTR fos;
	
	fos = FldOBJ_FieldOBJSysGet( fldobj );
	return( FieldOBJSys_FieldSysWorkGet(fos) );
}

//--------------------------------------------------------------
/**
 * TCB基本プライオリティ取得
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	int		TCB基本プライオリティ
 */
//--------------------------------------------------------------
int FieldOBJ_TCBStandardPriorityGet( CONST_FIELD_OBJ_PTR fldobj )
{
	return( FieldOBJSys_TCBStandardPriorityGet(FieldOBJ_FieldOBJSysGet(fldobj)) );
}

//--------------------------------------------------------------
/**
 * エイリアス時のゾーンID取得。エイリアス時はイベントフラグが指定ゾーンID
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	int		ゾーンID
 */
//--------------------------------------------------------------
int FieldOBJ_ZoneIDGetAlies( CONST_FIELD_OBJ_PTR fldobj )
{
	GF_ASSERT( FieldOBJ_StatusBitCheck_Alies(fldobj) == TRUE &&
			"FieldOBJ_ZoneIDGetAlies()aliesでは無い" );
	return( FieldOBJ_EventFlagGet(fldobj) );
}

//==============================================================================
//	フィールドOBJシステム　ステータスビット簡易
//==============================================================================
//--------------------------------------------------------------
/**
 * フィールドOBJ全体の動作を完全停止。
 * 動作処理、描画処理を完全停止する。アニメーションコマンドにも反応しない。
 * @param	fos		FIELD_OBJ_SYS_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJSys_MoveStopAll( FIELD_OBJ_SYS_PTR fos )
{
	FieldOBJSys_StatusBit_ON( fos,
		FLDOBJSYS_STA_BIT_MOVE_PROC_STOP | FLDOBJSYS_STA_BIT_DRAW_PROC_STOP );
	
	OS_Printf( "フィールドOBJ全体の動作を停止しました\n" );
}

//--------------------------------------------------------------
/**
 * フィールドOBJ全体の動作完全停止を解除
 * @param	fos		FIELD_OBJ_SYS_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJSys_MoveStopAllClear( FIELD_OBJ_SYS_PTR fos )
{
	FieldOBJSys_StatusBit_OFF( fos,
		FLDOBJSYS_STA_BIT_MOVE_PROC_STOP | FLDOBJSYS_STA_BIT_DRAW_PROC_STOP );
	
	OS_Printf( "フィールドOBJ全体の動作停止を解除しました\n" );
}

//--------------------------------------------------------------
/**
 * フィールドOBJ全体の動作を一時停止
 * 固有の動作処理（ランダム移動等）を一時停止する。
 * アニメーションコマンドには反応する。
 * @param	fos		FIELD_OBJ_SYS_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJSys_MovePauseAll( FIELD_OBJ_SYS_PTR fos )
{
	int max = FieldOBJSys_OBJMaxGet( fos );
	FIELD_OBJ_PTR fldobj = FieldOBJSys_FldOBJWorkGet( fos );
	
	do{
		if( FieldOBJ_StatusBitCheck_Use(fldobj) ){
			FieldOBJ_MovePause( fldobj );
		}
		
		fldobj++;
		max--;
	}while( max );
	
	OS_Printf( "フィールドOBJ全体動作をポーズしました\n" );
}

//--------------------------------------------------------------
/**
 * フィールドOBJ全体動作一時停止を解除
 * @param	fos		FIELD_OBJ_SYS_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJSys_MovePauseAllClear( FIELD_OBJ_SYS_PTR fos )
{
	int max = FieldOBJSys_OBJMaxGet( fos );
	FIELD_OBJ_PTR fldobj = FieldOBJSys_FldOBJWorkGet( fos );
	
	do{
		if( FieldOBJ_StatusBitCheck_Use(fldobj) ){
			FieldOBJ_MovePauseClear( fldobj );
		}
		
		fldobj++;
		max--;
	}while( max );
	
	OS_Printf( "フィールドOBJ全体動作ポーズを解除しました\n" );
}

//--------------------------------------------------------------
/**
 * 描画処理が初期化されているかどうかチェック
 * @param	fos				FIELD_OBJ_SYS_PTR
 * @retval	int				TRUE=初期化されている
 */
//--------------------------------------------------------------
int FieldOBJSys_DrawInitCompCheck( CONST_FIELD_OBJ_SYS_PTR fos )
{
	if( FieldOBJSys_StatusBit_Check(fos,FLDOBJSYS_STA_BIT_DRAW_INIT_COMP) ){
		return( TRUE );
	}
	
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * フィールドOBJからフィールドOBJシステムのビットチェック
 * @param	fldobj		FIELD_OBJ_PTR
 * @param	bit			FLDOBJSYS_STA_BIT_DRAW_INIT_COMP等
 * @retval	u32			0以外 bitヒット
 */
//--------------------------------------------------------------
u32 FieldOBJ_FieldOBJSysStatusBitCheck( CONST_FIELD_OBJ_PTR fldobj, u32 bit )
{
	CONST_FIELD_OBJ_SYS_PTR fos = FieldOBJ_FieldOBJSysGet( fldobj );
	return( FieldOBJSys_StatusBit_Check(fos,bit) );
}

//--------------------------------------------------------------
/**
 * 影を付ける、付けないのセット
 * @param	fos		FIELD_OBJ_SYS_PTR
 * @param	flag	TRUE=影を付ける FALSE=影を付けない
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJSys_ShadowJoinSet( FIELD_OBJ_SYS_PTR fos, int flag )
{
	if( flag == FALSE ){
		FieldOBJSys_StatusBit_ON( fos, FLDOBJSYS_STA_BIT_SHADOW_JOIN_NOT );
	}else{
		FieldOBJSys_StatusBit_OFF( fos, FLDOBJSYS_STA_BIT_SHADOW_JOIN_NOT );
	}
}

//--------------------------------------------------------------
/**
 * 影を付ける、付けないのチェック
 * @param	fos		FIELD_OBJ_SYS_PTR
 * @retval	int		FALSE=付けない
 */
//--------------------------------------------------------------
int FieldOBJSys_ShadowJoinCheck( CONST_FIELD_OBJ_SYS_PTR fos )
{
	if( FieldOBJSys_StatusBit_Check(fos,FLDOBJSYS_STA_BIT_SHADOW_JOIN_NOT) ){
		return( FALSE );
	}
	
	return( TRUE );
}

//==============================================================================
//	フィールドOBJ ステータスビット簡易
//==============================================================================
//--------------------------------------------------------------
/**
 * 使用チェック
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	int		TRUE=使用中
 */
//--------------------------------------------------------------
int FieldOBJ_StatusBitCheck_Use( CONST_FIELD_OBJ_PTR fldobj )
{
	return( FieldOBJ_StatusBit_CheckEasy(fldobj,FLDOBJ_STA_BIT_USE) );
}

//--------------------------------------------------------------
/**
 * 移動動作中にする
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_StatusBitON_Move( FIELD_OBJ_PTR fldobj )
{
	FieldOBJ_StatusBit_ON( fldobj, FLDOBJ_STA_BIT_MOVE );
}

//--------------------------------------------------------------
/**
 * 移動動作中を解除
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_StatusBitOFF_Move( FIELD_OBJ_PTR fldobj )
{
	FieldOBJ_StatusBit_OFF( fldobj, FLDOBJ_STA_BIT_MOVE );
}

//--------------------------------------------------------------
/**
 * 移動動作中チェック
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	int		TRUE=動作中
 */
//--------------------------------------------------------------
int FieldOBJ_StatusBitCheck_Move( CONST_FIELD_OBJ_PTR fldobj )
{
	return( FieldOBJ_StatusBit_CheckEasy(fldobj,FLDOBJ_STA_BIT_MOVE) );
}

//--------------------------------------------------------------
/**
 * 移動動作開始にする
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_StatusBitON_MoveStart( FIELD_OBJ_PTR fldobj )
{
	FieldOBJ_StatusBit_ON( fldobj, FLDOBJ_STA_BIT_MOVE_START );
}

//--------------------------------------------------------------
/**
 * 移動動作開始を解除
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_StatusBitOFF_MoveStart( FIELD_OBJ_PTR fldobj )
{
	FieldOBJ_StatusBit_OFF( fldobj, FLDOBJ_STA_BIT_MOVE_START );
}

//--------------------------------------------------------------
/**
 * 移動動作開始チェック
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	int		TRUE=移動動作開始
 */
//--------------------------------------------------------------
int FieldOBJ_StatusBitCheck_MoveStart( CONST_FIELD_OBJ_PTR fldobj )
{
	return( FieldOBJ_StatusBit_CheckEasy(fldobj,FLDOBJ_STA_BIT_MOVE_START) );
}

//--------------------------------------------------------------
/**
 * 移動動作終了にする
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_StatusBitON_MoveEnd( FIELD_OBJ_PTR fldobj )
{
	FieldOBJ_StatusBit_ON( fldobj, FLDOBJ_STA_BIT_MOVE_END );
}

//--------------------------------------------------------------
/**
 * 移動動作終了を解除
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_StatusBitOFF_MoveEnd( FIELD_OBJ_PTR fldobj )
{
	FieldOBJ_StatusBit_OFF( fldobj, FLDOBJ_STA_BIT_MOVE_END );
}

//--------------------------------------------------------------
/**
 * 移動動作終了チェック
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	int		TRUE=移動終了
 */
//--------------------------------------------------------------
int FieldOBJ_StatusBitCheck_MoveEnd( CONST_FIELD_OBJ_PTR fldobj )
{
	return( FieldOBJ_StatusBit_CheckEasy(fldobj,FLDOBJ_STA_BIT_MOVE_END) );
}

//--------------------------------------------------------------
/**
 * 描画初期化完了にする
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_StatusBitON_DrawProcInitComp( FIELD_OBJ_PTR fldobj )
{
	FieldOBJ_StatusBit_ON( fldobj, FLDOBJ_STA_BIT_DRAW_PROC_INIT_COMP );
}

//--------------------------------------------------------------
/**
 * 描画初期化完了を解除
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_StatusBitOFF_DrawProcInitComp( FIELD_OBJ_PTR fldobj )
{
	FieldOBJ_StatusBit_OFF( fldobj, FLDOBJ_STA_BIT_DRAW_PROC_INIT_COMP );
}

//--------------------------------------------------------------
/**
 * 描画初期化完了チェック
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	int		TRUE=描画初期化完了
 */
//--------------------------------------------------------------
int FieldOBJ_StatusBitCheck_DrawProcInitComp( CONST_FIELD_OBJ_PTR fldobj )
{
	return( FieldOBJ_StatusBit_CheckEasy(fldobj,FLDOBJ_STA_BIT_DRAW_PROC_INIT_COMP) );
}

//--------------------------------------------------------------
/**
 * 非表示フラグをチェック
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	flag	TRUE=非表示　FALSE=表示
 * @retval	nothing
 */
//--------------------------------------------------------------
int FieldOBJ_StatusBitCheck_Vanish( CONST_FIELD_OBJ_PTR fldobj )
{
	return( FieldOBJ_StatusBit_CheckEasy(fldobj,FLDOBJ_STA_BIT_VANISH) );
}

//--------------------------------------------------------------
/**
 * 非表示フラグを設定
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	flag	TRUE=非表示　FALSE=表示
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_StatusBitSet_Vanish( FIELD_OBJ_PTR fldobj, int flag )
{
	if( flag == TRUE ){
		FieldOBJ_StatusBit_ON( fldobj, FLDOBJ_STA_BIT_VANISH );
	}else{
		FieldOBJ_StatusBit_OFF( fldobj, FLDOBJ_STA_BIT_VANISH );
	}
}

//--------------------------------------------------------------
/**
 * OBJ同士の当たり判定フラグを設定
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	flag	TRUE=ヒットアリ　FALSE=ヒットナシ
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_StatusBitSet_FellowHit( FIELD_OBJ_PTR fldobj, int flag )
{
	if( flag == TRUE ){
		FieldOBJ_StatusBit_OFF( fldobj, FLDOBJ_STA_BIT_FELLOW_HIT_NON );
	}else{
		FieldOBJ_StatusBit_ON( fldobj, FLDOBJ_STA_BIT_FELLOW_HIT_NON );
	}
}

//--------------------------------------------------------------
/**
 * 動作中フラグのセット
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	flag	TRUE=動作中　FALSE=停止中
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_StatusBitSet_Move( FIELD_OBJ_PTR fldobj, int flag )
{
	if( flag == TRUE ){
		FieldOBJ_StatusBitON_Move( fldobj );
	}else{
		FieldOBJ_StatusBitOFF_Move( fldobj );
	}
}

//--------------------------------------------------------------
/**
 * 話しかけ可能チェック
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	int		TRUE=可能 FALSE=不可
 */
//--------------------------------------------------------------
int FieldOBJ_StatusBitCheck_Talk( FIELD_OBJ_PTR fldobj )
{
	if( FieldOBJ_StatusBit_CheckEasy(fldobj,FLDOBJ_STA_BIT_TALK_OFF) == TRUE ){
		return( FALSE );
	}
	
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * 話しかけ不可フラグをセット
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	flag	TRUE=不可 FALSE=可能
 */
//--------------------------------------------------------------
void FieldOBJ_StatusBitSet_TalkOFF( FIELD_OBJ_PTR fldobj, int flag )
{
	if( flag == TRUE ){
		FieldOBJ_StatusBit_ON( fldobj, FLDOBJ_STA_BIT_TALK_OFF );
	}else{
		FieldOBJ_StatusBit_OFF( fldobj, FLDOBJ_STA_BIT_TALK_OFF );
	}
}

//--------------------------------------------------------------
/**
 * 動作ポーズ
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_MovePause( FIELD_OBJ_PTR fldobj )
{
	FieldOBJ_StatusBit_ON( fldobj, FLDOBJ_STA_BIT_PAUSE_MOVE );
}

//--------------------------------------------------------------
/**
 * 動作ポーズ解除
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_MovePauseClear( FIELD_OBJ_PTR fldobj )
{
	FieldOBJ_StatusBit_OFF( fldobj, FLDOBJ_STA_BIT_PAUSE_MOVE );
}

//--------------------------------------------------------------
/**
 * 動作ポーズチェック
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	int		TRUE=動作ポーズ
 */
//--------------------------------------------------------------
int FieldOBJ_MovePauseCheck( CONST_FIELD_OBJ_PTR fldobj )
{
	if( FieldOBJ_StatusBit_CheckEasy(fldobj,FLDOBJ_STA_BIT_PAUSE_MOVE) == TRUE ){
		return( TRUE );
	}
	
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * ステータスビット 描画処理初期化完了チェック
 * @param	fldobj		FIELD_OBJ_PTR
 * @retval	int			TRUE=完了。FALSE=まだ
 */
//--------------------------------------------------------------
int FieldOBJ_StatusBit_DrawInitCompCheck( CONST_FIELD_OBJ_PTR fldobj )
{
	CONST_FIELD_OBJ_SYS_PTR fos;
	
	fos = FieldOBJ_FieldOBJSysGet( fldobj );
	
	if( FieldOBJSys_DrawInitCompCheck(fos) == FALSE ){
		return( FALSE );
	}
	
	if( FieldOBJ_StatusBit_Check(fldobj,FLDOBJ_STA_BIT_DRAW_PROC_INIT_COMP) == 0 ){
		return( FALSE );
	}
	
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * 高さ取得を禁止する
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	int		TRUE=高さ取得OFF FALSE=ON
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_StatusBitSet_HeightGetOFF( FIELD_OBJ_PTR fldobj, int flag )
{
	if( flag == TRUE ){
		FieldOBJ_StatusBit_ON( fldobj, FLDOBJ_STA_BIT_HEIGHT_GET_OFF );
	}else{
		FieldOBJ_StatusBit_OFF( fldobj, FLDOBJ_STA_BIT_HEIGHT_GET_OFF );
	}
}

//--------------------------------------------------------------
/**
 * 高さ取得が禁止されているかチェック
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	int		TRUE=禁止
 */
//--------------------------------------------------------------
int FieldOBJ_HeightOFFCheck( CONST_FIELD_OBJ_PTR fldobj )
{
	if( FieldOBJ_StatusBit_Check(fldobj,FLDOBJ_STA_BIT_HEIGHT_GET_OFF) ){
		return( TRUE );
	}
	
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * ゾーン切り替え時の削除禁止
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	flag	TRUE=禁止 FALSE=禁止しない
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_NotZoneDeleteSet( FIELD_OBJ_PTR fldobj, int flag )
{
	if( flag == TRUE ){
		FieldOBJ_StatusBit_ON( fldobj, FLDOBJ_STA_BIT_ZONE_DEL_NOT );
	}else{
		FieldOBJ_StatusBit_OFF( fldobj, FLDOBJ_STA_BIT_ZONE_DEL_NOT );
	}
}

//--------------------------------------------------------------
/**
 * エイリアスフラグをセット
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	flag	TRUE=エイリアス FALSE=違う
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_StatusBitSet_Alies( FIELD_OBJ_PTR fldobj, int flag )
{
	if( flag == TRUE ){
		FieldOBJ_StatusBit_ON( fldobj, FLDOBJ_STA_BIT_ALIES );
	}else{
		FieldOBJ_StatusBit_OFF( fldobj, FLDOBJ_STA_BIT_ALIES );
	}
}

//--------------------------------------------------------------
/**
 * エイリアスフラグをチェック
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	flag	TRUE=エイリアス FALSE=違う
 */
//--------------------------------------------------------------
int FieldOBJ_StatusBitCheck_Alies( CONST_FIELD_OBJ_PTR fldobj )
{
	if( FieldOBJ_StatusBit_Check(fldobj,FLDOBJ_STA_BIT_ALIES) ){
		return( TRUE );
	}
	
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * 浅瀬エフェクトセットフラグをセット
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	flag	TRUE=セット　FALSE=クリア
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_StatusBitSet_ShoalEffectSet( FIELD_OBJ_PTR fldobj, int flag )
{
	if( flag == TRUE ){
		FieldOBJ_StatusBit_ON( fldobj, FLDOBJ_STA_BIT_EFFSET_SHOAL );
	}else{
		FieldOBJ_StatusBit_OFF( fldobj, FLDOBJ_STA_BIT_EFFSET_SHOAL );
	}
}

//--------------------------------------------------------------
/**
 * 浅瀬エフェクトセットフラグをチェック
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	flag	TRUE=セット　FALSE=違う
 */
//--------------------------------------------------------------
int FieldOBJ_StatusBitCheck_ShoalEffectSet( CONST_FIELD_OBJ_PTR fldobj )
{
	if( FieldOBJ_StatusBit_Check(fldobj,FLDOBJ_STA_BIT_EFFSET_SHOAL) ){
		return( TRUE );
	}
	
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * アトリビュートオフセット設定OFFセット
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	flag	TRUE=セット　FALSE=クリア
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_StatusBitSet_AttrOffsOFF( FIELD_OBJ_PTR fldobj, int flag )
{
	if( flag == TRUE ){
		FieldOBJ_StatusBit_ON( fldobj, FLDOBJ_STA_BIT_ATTR_OFFS_OFF );
	}else{
		FieldOBJ_StatusBit_OFF( fldobj, FLDOBJ_STA_BIT_ATTR_OFFS_OFF );
	}
}

//--------------------------------------------------------------
/**
 * アトリビュートオフセット設定OFFチェック
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	flag	TRUE=OFF　FALSE=違う
 */
//--------------------------------------------------------------
int FieldOBJ_StatusBitCheck_AttrOffsOFF( CONST_FIELD_OBJ_PTR fldobj )
{
	if( FieldOBJ_StatusBit_Check(fldobj,FLDOBJ_STA_BIT_ATTR_OFFS_OFF) ){
		return( TRUE );
	}
	
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * 橋移動フラグセット
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	flag	TRUE=セット　FALSE=クリア
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_StatusBitSet_Bridge( FIELD_OBJ_PTR fldobj, int flag )
{
	if( flag == TRUE ){
		FieldOBJ_StatusBit_ON( fldobj, FLDOBJ_STA_BIT_BRIDGE );
	}else{
		FieldOBJ_StatusBit_OFF( fldobj, FLDOBJ_STA_BIT_BRIDGE );
	}
}

//--------------------------------------------------------------
/**
 * 橋移動フラグチェック
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	flag	TRUE=橋　FALSE=違う
 */
//--------------------------------------------------------------
int FieldOBJ_StatusBitCheck_Bridge( CONST_FIELD_OBJ_PTR fldobj )
{
	if( FieldOBJ_StatusBit_Check(fldobj,FLDOBJ_STA_BIT_BRIDGE) ){
		return( TRUE );
	}
	
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * 映りこみフラグセット
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	flag	TRUE=セット　FALSE=クリア
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_StatusBitSet_Reflect( FIELD_OBJ_PTR fldobj, int flag )
{
	if( flag == TRUE ){
		FieldOBJ_StatusBit_ON( fldobj, FLDOBJ_STA_BIT_REFLECT_SET );
	}else{
		FieldOBJ_StatusBit_OFF( fldobj, FLDOBJ_STA_BIT_REFLECT_SET );
	}
}

//--------------------------------------------------------------
/**
 * 映りこみフラグチェック
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	flag	TRUE=セット　FALSE=無し
 */
//--------------------------------------------------------------
int FieldOBJ_StatusBitCheck_Reflect( CONST_FIELD_OBJ_PTR fldobj )
{
	if( FieldOBJ_StatusBit_Check(fldobj,FLDOBJ_STA_BIT_REFLECT_SET) ){
		return( TRUE );
	}
	
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * アニメーションコマンドチェック
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	flag	TRUE=コマンドアリ　FALSE=無し
 */
//--------------------------------------------------------------
int FieldOBJ_StatusBitCheck_Acmd( CONST_FIELD_OBJ_PTR fldobj )
{
	if( FieldOBJ_StatusBit_Check(fldobj,FLDOBJ_STA_BIT_ACMD) ){
		return( TRUE );
	}
	
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * 拡張高さ反応フラグをセット
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	flag	TRUE=セット　FALSE=クリア
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_StatusBitSet_HeightExpand( FIELD_OBJ_PTR fldobj, int flag )
{
	if( flag == TRUE ){
		FieldOBJ_StatusBit_ON( fldobj, FLDOBJ_STA_BIT_HEIGHT_EXPAND );
	}else{
		FieldOBJ_StatusBit_OFF( fldobj, FLDOBJ_STA_BIT_HEIGHT_EXPAND );
	}
}

//--------------------------------------------------------------
/**
 * 拡張高さ反応フラグチェック
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	flag	TRUE=拡張高さに反応する　FALSE=無し
 */
//--------------------------------------------------------------
int FieldOBJ_StatusBitCheck_HeightExpand( CONST_FIELD_OBJ_PTR fldobj )
{
	if( FieldOBJ_StatusBit_Check(fldobj,FLDOBJ_STA_BIT_HEIGHT_EXPAND) ){
		return( TRUE );
	}
	
	return( FALSE );
}

//==============================================================================
//	座標系参照
//==============================================================================
//--------------------------------------------------------------
/**
 * 初期座標 X座標取得
 * @param	fldobj	FIELD_OBJ_PTR 
 * @retval	int		X座標
 */
//--------------------------------------------------------------
int FieldOBJ_InitPosGX_Get( CONST_FIELD_OBJ_PTR fldobj )
{
	return( fldobj->gx_init );
}

//--------------------------------------------------------------
/**
 * 初期座標 X座標セット
 * @param	fldobj	FIELD_OBJ_PTR 
 * @param	x		セットする座標
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_InitPosGX_Set( FIELD_OBJ_PTR fldobj, int x )
{
	fldobj->gx_init = x;
}

//--------------------------------------------------------------
/**
 * 初期座標 Y座標取得
 * @param	fldobj	FIELD_OBJ_PTR 
 * @retval	int		Y
 */
//--------------------------------------------------------------
int FieldOBJ_InitPosGY_Get( CONST_FIELD_OBJ_PTR fldobj )
{
	return( fldobj->gy_init );
}

//--------------------------------------------------------------
/**
 * 初期座標 Y座標セット
 * @param	fldobj	FIELD_OBJ_PTR 
 * @param	y		セットする座標
 * @retval	int		y座標
 */
//--------------------------------------------------------------
void FieldOBJ_InitPosGY_Set( FIELD_OBJ_PTR fldobj, int y )
{
	fldobj->gy_init = y;
}

//--------------------------------------------------------------
/**
 * 初期座標 z座標取得
 * @param	fldobj	FIELD_OBJ_PTR 
 * @retval	int		z座標
 */
//--------------------------------------------------------------
int FieldOBJ_InitPosGZ_Get( CONST_FIELD_OBJ_PTR fldobj )
{
	return( fldobj->gz_init );
}

//--------------------------------------------------------------
/**
 * 初期座標 z座標セット
 * @param	fldobj	FIELD_OBJ_PTR 
 * @param	z		セットする座標
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_InitPosGZ_Set( FIELD_OBJ_PTR fldobj, int z )
{
	fldobj->gz_init = z;
}

//--------------------------------------------------------------
/**
 * 過去座標　X座標取得
 * @param	fldobj	FIELD_OBJ_PTR 
 * @retval	int		X座標
 */
//--------------------------------------------------------------
int FieldOBJ_OldPosGX_Get( CONST_FIELD_OBJ_PTR fldobj )
{
	return( fldobj->gx_old );
}

//--------------------------------------------------------------
/**
 * 過去座標 X座標セット
 * @param	fldobj	FIELD_OBJ_PTR 
 * @param	x		セットする座標
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_OldPosGX_Set( FIELD_OBJ_PTR fldobj, int x )
{
	fldobj->gx_old = x;
}

//--------------------------------------------------------------
/**
 * 過去座標 Y座標取得
 * @param	fldobj	FIELD_OBJ_PTR 
 * @retval	int		Y
 */
//--------------------------------------------------------------
int FieldOBJ_OldPosGY_Get( CONST_FIELD_OBJ_PTR fldobj )
{
	return( fldobj->gy_old );
}

//--------------------------------------------------------------
/**
 * 過去座標 Y座標セット
 * @param	fldobj	FIELD_OBJ_PTR 
 * @param	y		セットする座標
 * @retval	int		y座標
 */
//--------------------------------------------------------------
void FieldOBJ_OldPosGY_Set( FIELD_OBJ_PTR fldobj, int y )
{
	fldobj->gy_old = y;
}

//--------------------------------------------------------------
/**
 * 過去座標 z座標取得
 * @param	fldobj	FIELD_OBJ_PTR 
 * @retval	int		z座標
 */
//--------------------------------------------------------------
int FieldOBJ_OldPosGZ_Get( CONST_FIELD_OBJ_PTR fldobj )
{
	return( fldobj->gz_old );
}

//--------------------------------------------------------------
/**
 * 過去座標 z座標セット
 * @param	fldobj	FIELD_OBJ_PTR 
 * @param	z		セットする座標
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_OldPosGZ_Set( FIELD_OBJ_PTR fldobj, int z )
{
	fldobj->gz_old = z;
}

//--------------------------------------------------------------
/**
 * 現在座標 X座標取得
 * @param	fldobj	FIELD_OBJ_PTR 
 * @retval	int		X座標
 */
//--------------------------------------------------------------
int FieldOBJ_NowPosGX_Get( CONST_FIELD_OBJ_PTR fldobj )
{
	return( fldobj->gx_now );
}

//--------------------------------------------------------------
/**
 * 現在座標 X座標セット
 * @param	fldobj	FIELD_OBJ_PTR 
 * @param	x		セットする座標
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_NowPosGX_Set( FIELD_OBJ_PTR fldobj, int x )
{
	fldobj->gx_now = x;
}

//--------------------------------------------------------------
/**
 * 現在座標 X座標増加
 * @param	fldobj	FIELD_OBJ_PTR 
 * @param	x		足す値
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_NowPosGX_Add( FIELD_OBJ_PTR fldobj, int x )
{
	fldobj->gx_now += x;
}

//--------------------------------------------------------------
/**
 * 現在座標 Y座標取得
 * @param	fldobj	FIELD_OBJ_PTR 
 * @retval	int		Y
 */
//--------------------------------------------------------------
int FieldOBJ_NowPosGY_Get( CONST_FIELD_OBJ_PTR fldobj )
{
	return( fldobj->gy_now );
}

//--------------------------------------------------------------
/**
 * 現在座標 Y座標セット
 * @param	fldobj	FIELD_OBJ_PTR 
 * @param	y		セットする座標
 * @retval	int		y座標
 */
//--------------------------------------------------------------
void FieldOBJ_NowPosGY_Set( FIELD_OBJ_PTR fldobj, int y )
{
	fldobj->gy_now = y;
}

//--------------------------------------------------------------
/**
 * 現在座標 Y座標増加
 * @param	fldobj	FIELD_OBJ_PTR 
 * @param	y		足す値
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_NowPosGY_Add( FIELD_OBJ_PTR fldobj, int y )
{
	fldobj->gy_now += y;
}

//--------------------------------------------------------------
/**
 * 過去座標 z座標取得
 * @param	fldobj	FIELD_OBJ_PTR 
 * @retval	int		z座標
 */
//--------------------------------------------------------------
int FieldOBJ_NowPosGZ_Get( CONST_FIELD_OBJ_PTR fldobj )
{
	return( fldobj->gz_now );
}

//--------------------------------------------------------------
/**
 * 現在座標 z座標セット
 * @param	fldobj	FIELD_OBJ_PTR 
 * @param	z		セットする座標
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_NowPosGZ_Set( FIELD_OBJ_PTR fldobj, int z )
{
	fldobj->gz_now = z;
}

//--------------------------------------------------------------
/**
 * 現在座標 z座標増加
 * @param	fldobj	FIELD_OBJ_PTR 
 * @param	z		足す値
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_NowPosGZ_Add( FIELD_OBJ_PTR fldobj, int z )
{
	fldobj->gz_now += z;
}

//--------------------------------------------------------------
/**
 * 実座標取得
 * @param	fldobj	FIELD_OBJ_PTR 
 * @param	vec		座標格納先
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_VecPosGet( CONST_FIELD_OBJ_PTR fldobj, VecFx32 *vec )
{
	*vec = fldobj->vec_pos_now;
}

//--------------------------------------------------------------
/**
 * 実座標セット
 * @param	fldobj	FIELD_OBJ_PTR 
 * @param	vec		セット座標
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_VecPosSet( FIELD_OBJ_PTR fldobj, const VecFx32 *vec )
{
	fldobj->vec_pos_now = *vec;
}

//--------------------------------------------------------------
/**
 * 実座標ポインタ取得
 * @param	fldobj	FIELD_OBJ_PTR 
 * @retval	VecFx32	実座標ポインタ
 */
//--------------------------------------------------------------
const VecFx32 * FieldOBJ_VecPosPtrGet( CONST_FIELD_OBJ_PTR fldobj )
{
	return( &fldobj->vec_pos_now );
}

//--------------------------------------------------------------
/**
 * 実座標Y値取得
 * @param	fldobj	FIELD_OBJ_PTR 
 * @retval	fx32	高さ
 */
//--------------------------------------------------------------
fx32 FieldOBJ_VecPosYGet( CONST_FIELD_OBJ_PTR fldobj )
{
	return( fldobj->vec_pos_now.y );
}

//--------------------------------------------------------------
/**
 * 表示座標オフセット取得
 * @param	fldobj	FIELD_OBJ_PTR 
 * @param	vec		セット座標
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_VecDrawOffsGet( CONST_FIELD_OBJ_PTR fldobj, VecFx32 *vec )
{
	*vec = fldobj->vec_draw_offs;
}

//--------------------------------------------------------------
/**
 * 表示座標オフセットセット
 * @param	fldobj	FIELD_OBJ_PTR 
 * @param	vec		セット座標
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_VecDrawOffsSet( FIELD_OBJ_PTR fldobj, const VecFx32 *vec )
{
	fldobj->vec_draw_offs = *vec;
}

//--------------------------------------------------------------
/**
 * 表示座標オフセットポインタ取得
 * @param	fldobj		FIELD_OBJ_PTR 
 * @retval	VecFx32		オフセットポインタ
 */
//--------------------------------------------------------------
VecFx32 * FieldOBJ_VecDrawOffsPtrGet( FIELD_OBJ_PTR fldobj )
{
	return( &fldobj->vec_draw_offs );
}

//--------------------------------------------------------------
/**
 * 外部指定表示座標オフセット取得
 * @param	fldobj	FIELD_OBJ_PTR 
 * @param	vec		セット座標
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_VecDrawOffsOutSideGet( CONST_FIELD_OBJ_PTR fldobj, VecFx32 *vec )
{
	*vec = fldobj->vec_draw_offs_outside;
}

//--------------------------------------------------------------
/**
 * 外部指定表示座標オフセットセット
 * @param	fldobj	FIELD_OBJ_PTR 
 * @param	vec		セット座標
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_VecDrawOffsOutSideSet( FIELD_OBJ_PTR fldobj, const VecFx32 *vec )
{
	fldobj->vec_draw_offs_outside = *vec;
}

//--------------------------------------------------------------
/**
 * アトリビュート変化座標オフセット取得
 * @param	fldobj	FIELD_OBJ_PTR 
 * @param	vec		セット座標
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_VecAttrOffsGet( CONST_FIELD_OBJ_PTR fldobj, VecFx32 *vec )
{
	*vec = fldobj->vec_attr_offs;
}

//--------------------------------------------------------------
/**
 * アトリビュート変化座標オフセットセット
 * @param	fldobj	FIELD_OBJ_PTR 
 * @param	vec		セット座標
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_VecAttrOffsSet( FIELD_OBJ_PTR fldobj, const VecFx32 *vec )
{
	fldobj->vec_attr_offs = *vec;
}

//--------------------------------------------------------------
/**
 * 高さ(グリッド単位)を取得
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	int		高さ。H_GRID単位
 */
//--------------------------------------------------------------
int FieldOBJ_HeightGridGet( CONST_FIELD_OBJ_PTR fldobj )
{
	fx32 y = FieldOBJ_VecPosYGet( fldobj );
	int gy = SIZE_H_GRID_FX32( y );
	return( gy );
}

//==============================================================================
//	FIELD_OBJ_H	参照
//==============================================================================
//--------------------------------------------------------------
/**
 * ID セット
 * @param	head	FIELD_OBJ_H
 * @param	id		OBJ ID
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_H_IDSet( FIELD_OBJ_H *head, int id )
{
	head->id = id;
}

//--------------------------------------------------------------
/**
 * ID 取得
 * @param	head	FIELD_OBJ_H
 * @retval	u32		ID
 */
//--------------------------------------------------------------
int FieldOBJ_H_IDGet( const FIELD_OBJ_H *head )
{
	return( head->id );
}

//--------------------------------------------------------------
/**
 * OBJコードセット
 * @param	head	FIELD_OBJ_H
 * @param	code	HERO等
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_H_OBJCodeSet( FIELD_OBJ_H *head, int code )
{
	head->obj_code = code;
}

//--------------------------------------------------------------
/**
 * OBJコード取得
 * @param	head	FIELD_OBJ_H
 * @retval	int		OBJコード
 */
//--------------------------------------------------------------
int FieldOBJ_H_OBJCodeGet( const FIELD_OBJ_H *head )
{
	return( head->obj_code );
}

//--------------------------------------------------------------
/**
 * 動作コードセット
 * @param	head	FIELD_OBJ_H
 * @param	code	MV_DIR_RND等
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_H_MoveCodeSet( FIELD_OBJ_H *head, int code )
{
	head->move_code = code;
}

//--------------------------------------------------------------
/**
 * 動作コード取得
 * @param	head	FIELD_OBJ_H
 * @retval	int		動作コード
 */
//--------------------------------------------------------------
int FieldOBJ_H_MoveCodeGet( const FIELD_OBJ_H *head )
{
	return( head->move_code );
}

//--------------------------------------------------------------
/**
 * イベントタイプセット
 * @param	head	FIELD_OBJ_H
 * @param	type	イベントタイプ
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_H_EventTypeSet( FIELD_OBJ_H *head, int type )
{
	head->event_type = type;
}

//--------------------------------------------------------------
/**
 * イベントタイプ取得
 * @param	head	FIELD_OBJ_H
 * @retval	int		イベントタイプ
 */
//--------------------------------------------------------------
int FieldOBJ_H_EventTypeGet( const FIELD_OBJ_H *head )
{
	return( head->event_type );
}

//--------------------------------------------------------------
/**
 * イベントフラグセット
 * @param	head	FIELD_OBJ_H
 * @param	flag	イベントフラグ
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_H_EventFlagSet( FIELD_OBJ_H *head, int flag )
{
	head->event_flag = flag;
}

//--------------------------------------------------------------
/**
 * イベントフラグ取得
 * @param	head	FIELD_OBJ_H
 * @retval	int		イベントフラグ
 */
//--------------------------------------------------------------
int FieldOBJ_H_EventFlagGet( const FIELD_OBJ_H *head )
{
	return( head->event_flag );
}

//--------------------------------------------------------------
/**
 * イベントIDセット
 * @param	head	FIELD_OBJ_H
 * @param	id		イベントID
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_H_EventIDSet( FIELD_OBJ_H *head, int id )
{
	head->event_id = id;
}

//--------------------------------------------------------------
/**
 * イベントID取得
 * @param	head	FIELD_OBJ_H
 * @retval	int		イベントフラグ
 */
//--------------------------------------------------------------
int FieldOBJ_H_EventIDGet( const FIELD_OBJ_H *head )
{
	return( head->event_id );
}

//--------------------------------------------------------------
/**
 * 方向セット
 * @param	head	FIELD_OBJ_H
 * @param	dir		DIR_UP等
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_H_DirSet( FIELD_OBJ_H *head, int dir )
{
	head->dir = dir;
}

//--------------------------------------------------------------
/**
 * 方向取得
 * @param	head	FIELD_OBJ_H
 * @retval	int		方向
 */
//--------------------------------------------------------------
int FieldOBJ_H_DirGet( const FIELD_OBJ_H *head )
{
	return( head->dir );
}

//--------------------------------------------------------------
/**
 * 指定パラメタセット
 * @param	head	FIELD_OBJ_H
 * @param	param	指定パラメタ
 * @param	no		FLDOBJ_PARAM_0等
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_H_ParamSet( FIELD_OBJ_H *head, int param, FLDOBJ_H_PARAM no )
{
	switch( no ){
	case FLDOBJ_PARAM_0: head->param0 = param; break;
	case FLDOBJ_PARAM_1: head->param1 = param; break;
	case FLDOBJ_PARAM_2: head->param2 = param; break;
	default: GF_ASSERT( 0 && "FieldOBJ_H_ParamSet()不正な引数" );
	}
}

//--------------------------------------------------------------
/**
 * 指定パラメタ取得
 * @param	head	FIELD_OBJ_H
 * @param	no		取得するパラメタ。FLDOBJ_PARAM_0等
 * @retval	int		パラメタ
 */
//--------------------------------------------------------------
int FieldOBJ_H_ParamGet( const FIELD_OBJ_H *head, FLDOBJ_H_PARAM no )
{
	switch( no ){
	case FLDOBJ_PARAM_0: return( head->param0 );
	case FLDOBJ_PARAM_1: return( head->param1 );
	case FLDOBJ_PARAM_2: return( head->param2 );
	}
	
	GF_ASSERT( 0 && "FieldOBJ_H_ParamGet()不正な引数" );
	return( 0 );
}

//--------------------------------------------------------------
/**
 * 移動制限Xセット
 * @param	head	FIELD_OBJ_H
 * @param	x		移動制限X
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_H_MoveLimitXSet( FIELD_OBJ_H *head, int x )
{
	head->move_limit_x = x;
}

//--------------------------------------------------------------
/**
 * 移動制限X取得
 * @param	head	FIELD_OBJ_H
 * @retval	int		移動制限X
 */
//--------------------------------------------------------------
int FieldOBJ_H_MoveLimitXGet( const FIELD_OBJ_H *head )
{
	return( head->move_limit_x );
}

//--------------------------------------------------------------
/**
 * 移動制限Zセット
 * @param	head	FIELD_OBJ_H
 * @param	z		移動制限Z
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_H_MoveLimitZSet( FIELD_OBJ_H *head, int z )
{
	head->move_limit_z = z;
}

//--------------------------------------------------------------
/**
 * 移動制限Z取得
 * @param	head	FIELD_OBJ_H
 * @retval	int		移動制限Y
 */
//--------------------------------------------------------------
int FieldOBJ_H_MoveLimitZGet( const FIELD_OBJ_H *head )
{
	return( head->move_limit_z );
}

//--------------------------------------------------------------
/**
 * X座標セット
 * @param	head	FIELD_OBJ_H
 * @param	x		X座標
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_H_PosXSet( FIELD_OBJ_H *head, int x )
{
	head->gx = x;
}

//--------------------------------------------------------------
/**
 * X座標取得
 * @param	head	FIELD_OBJ_H
 * @retval	int		X座標
 */
//--------------------------------------------------------------
int FieldOBJ_H_PosXGet( const FIELD_OBJ_H *head )
{
	return( head->gx );
}

//--------------------------------------------------------------
/**
 * Y座標セット
 * @param	head	FIELD_OBJ_H
 * @param	y		y座標
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_H_PosYSet( FIELD_OBJ_H *head, int y )
{
	head->gy = y;
}

//--------------------------------------------------------------
/**
 * Y座標取得
 * @param	head	FIELD_OBJ_H
 * @retval	int		Y座標
 */
//--------------------------------------------------------------
int FieldOBJ_H_PosYGet( const FIELD_OBJ_H *head )
{
	return( head->gy );
}

//--------------------------------------------------------------
/**
 * Z座標セット
 * @param	head	FIELD_OBJ_H
 * @param	z		Z座標
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_H_PosZSet( FIELD_OBJ_H *head, int z )
{
	head->gz = z;
}

//--------------------------------------------------------------
/**
 * Z座標取得
 * @param	head	FIELD_OBJ_H
 * @retval	int		Y座標
 */
//--------------------------------------------------------------
int FieldOBJ_H_PosZGet( const FIELD_OBJ_H *head )
{
	return( head->gz );
}

//--------------------------------------------------------------
/**
 * フィールドOBJヘッダー配列から指定IDを持ったヘッダーを検索
 * @param	id		ヘッダーID
 * @param	max		head要素数
 * @param	head	フィールドOBJヘッダーテーブル
 * @retval	FIELD_OBJ_H idを持つhead内ポインタ。NULL=一致無し
 */
//--------------------------------------------------------------
static const FIELD_OBJ_H * FldOBJ_H_OBJIDSearch( int id, int max, const FIELD_OBJ_H *head )
{
	int i = 0;
	
	do{
		if( FldOBJ_H_AliesCheck(&head[i]) == FALSE ){
			if( FieldOBJ_H_IDGet(&head[i]) == id ){
				return( &head[i] );
			}
		}
		
		i++;
	}while( i < max );
	
	return( NULL );
}

//--------------------------------------------------------------
/**
 * フィールドOBJヘッダー　エイリアスチェック
 * @param	head	FIELD_OBJ_H
 * @retval	int		TRUE=エイリアス　FALSE=違う
 */
//--------------------------------------------------------------
static int FldOBJ_H_AliesCheck( const FIELD_OBJ_H *head )
{
	u16 id = (u16)FieldOBJ_H_EventIDGet( head );
	if( id == SP_SCRID_ALIES ){ return( TRUE ); }
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * フィールドOBJヘッダー　エイリアス時のゾーンID取得。
 * エイリアス時はイベントフラグがゾーンIDになる
 * @param	head	FIELD_OBJ_H
 * @retval	int		ゾーンID
 */
//--------------------------------------------------------------
static int FldOBJ_H_AliesZoneIDGet( const FIELD_OBJ_H *head )
{
	GF_ASSERT( FldOBJ_H_AliesCheck(head) == TRUE && "FldOBJ_H_AliesZoneIDGet()aliesではない" );
	return( FieldOBJ_H_EventFlagGet(head) );
}

//==============================================================================
//	FIELD_OBJ_MOVE_PROC 参照
//==============================================================================
//--------------------------------------------------------------
/**
 * 動作テーブルから指定のリスト取り出し
 * @param	nothing
 * @retval	FIELD_OBJ_MOVE_PROC_LIST	FIELD_OBJ_MOVE_PROC_LISTテーブル
 */
//--------------------------------------------------------------
static const FIELD_OBJ_MOVE_PROC_LIST * FldOBJ_MoveProcListGet( u32 code )
{
	GF_ASSERT( code < MV_CODE_MAX );
	return( DATA_FieldOBJMoveProcListTbl[code] );
}

//--------------------------------------------------------------
/**
 * 動作コード取得
 * @param	list 		FIELD_OBJ_MOVE_PROC_LIST
 * @retval	u32			MV_PLAYER等
 */
//--------------------------------------------------------------
static u32 FldOBJ_MoveProcList_MoveCodeGet( const FIELD_OBJ_MOVE_PROC_LIST *list )
{
	return( list->move_code );
}

//--------------------------------------------------------------
/**
 * 初期化関数取得
 * @param	list FIELD_OBJ_MOVE_PROC_LIST
 * @retval	FIELD_OBJ_MOVE_PROC_INIT listの初期化関数
 */
//--------------------------------------------------------------
static FIELD_OBJ_MOVE_PROC_INIT FldOBJ_MoveProcList_InitGet(
		const FIELD_OBJ_MOVE_PROC_LIST *list )
{
	return( list->init_proc );
}

//--------------------------------------------------------------
/**
 * 動作関数取得
 * @param	list FIELD_OBJ_MOVE_PROC_LIST
 * @retval	FIELD_OBJ_MOVE_PROC listの動作関数
 */
//--------------------------------------------------------------
static FIELD_OBJ_MOVE_PROC FldOBJ_MoveProcList_MoveGet( const FIELD_OBJ_MOVE_PROC_LIST *list )
{
	return( list->move_proc );
}

//--------------------------------------------------------------
/**
 * 削除関数取得
 * @param	list FIELD_OBJ_MOVE_PROC_LIST
 * @retval	FIELD_OBJ_MOVE_PROC_DEL listの動作関数
 */
//--------------------------------------------------------------
static FIELD_OBJ_MOVE_PROC_DEL FldOBJ_MoveProcList_DeleteGet(
		const FIELD_OBJ_MOVE_PROC_LIST *list )
{
	return( list->delete_proc );
}

//==============================================================================
//	FIELD_OBJ_DRAW_PROC_LIST FIELD_OBJ_DRAW_PROC_LIST_REG参照
//==============================================================================
//--------------------------------------------------------------
/**
 * 初期化関数取得
 * @param	list	FIELD_OBJ_DRAW_PROC_LIST *
 * @retval	FIELD_OBJ_DRAW_PROC_INIT	FIELD_OBJ_DRAW_PROC_INIT *
 */
//--------------------------------------------------------------
static FIELD_OBJ_DRAW_PROC_INIT FldOBJ_DrawProcList_InitGet(
	const FIELD_OBJ_DRAW_PROC_LIST *list )
{
	return( list->init_proc );
}

//--------------------------------------------------------------
/**
 * 描画関数取得
 * @param	list	FIELD_OBJ_DRAW_PROC_LIST *
 * @retval	FIELD_OBJ_DRAW_PROC		FIELD_OBJ_DRAW_PROC *
 */
//--------------------------------------------------------------
static FIELD_OBJ_DRAW_PROC FldOBJ_DrawProcList_DrawGet( const FIELD_OBJ_DRAW_PROC_LIST *list )
{
	return( list->draw_proc );
}

//--------------------------------------------------------------
/**
 * 削除関数取得
 * @param	list	FIELD_OBJ_DRAW_PROC_LIST *
 * @retval	FIELD_OBJ_DRAW_PROC_DEL		FIELD_OBJ_DRAW_PROC_DEL *
 */
//--------------------------------------------------------------
static FIELD_OBJ_DRAW_PROC_DEL FldOBJ_DrawProcList_DeleteGet(
		const FIELD_OBJ_DRAW_PROC_LIST *list )
{
	return( list->delete_proc );
}

//--------------------------------------------------------------
/**
 * 退避関数取得
 * @param	list	FIELD_OBJ_DRAW_PROC_LIST *
 * @retval	FIELD_OBJ_DRAW_PROC_PUSH		FIELD_OBJ_DRAW_PROC_PUSH *
 */
//--------------------------------------------------------------
static FIELD_OBJ_DRAW_PROC_PUSH FldOBJ_DrawProcList_PushGet(
		const FIELD_OBJ_DRAW_PROC_LIST *list )
{
	return( list->push_proc );
}

//--------------------------------------------------------------
/**
 * 復帰関数取得
 * @param	list	FIELD_OBJ_DRAW_PROC_LIST *
 * @retval	FIELD_OBJ_DRAW_PROC_PUSH		FIELD_OBJ_DRAW_PROC_PUSH *
 */
//--------------------------------------------------------------
static FIELD_OBJ_DRAW_PROC_POP FldOBJ_DrawProcList_PopGet(
		const FIELD_OBJ_DRAW_PROC_LIST *list )
{
	return( list->pop_proc );
}

//--------------------------------------------------------------
/**
 * テーブルから指定のリスト取り出し
 * @param	code	HERO等
 * @retval	list	codeに対応したFIELD_OBJ_DRAW_PROC_LIST *
 */
//--------------------------------------------------------------
static const FIELD_OBJ_DRAW_PROC_LIST * FldOBJ_DrawProcListGet( u32 code )
{
	const FIELD_OBJ_DRAW_PROC_LIST_REG *tbl = DATA_FieldOBJDrawProcListRegTbl;
	
	do{
		if( tbl->code == code ){
			return( tbl->list );
		}
		
		tbl++;
	}while( tbl->code != OBJCODEMAX );
	
	GF_ASSERT( 0 && "FldOBJ_DrawProcListGet()不正なコード" );
	return( NULL );
}

//==============================================================================
//	フィールドOBJ ツール
//==============================================================================
//--------------------------------------------------------------
/**
 * 指定されたグリッドX,Z座標にいるOBJを取得
 * @param	sys			FIELD_OBJ_SYS_PTR 
 * @param	x			検索グリッドX
 * @param	z			検索グリッドZ
 * @retval	FIELD_OBJ	x,z位置にいるFIELD_OBJ_PTR 。NULL=その座標にOBJはいない
 */
//--------------------------------------------------------------
FIELD_OBJ_PTR  FieldOBJ_SearchGPos( CONST_FIELD_OBJ_SYS_PTR sys, int x, int z )
{
	int max;
	FIELD_OBJ_PTR fldobj;
	
	max = FieldOBJSys_OBJMaxGet( sys );
	fldobj = FieldOBJSys_FldOBJWorkGet( sys );
	
	do{
		if( FieldOBJ_StatusBit_Check(fldobj,FLDOBJ_STA_BIT_USE) ){
			if( FieldOBJ_NowPosGX_Get(fldobj) == x && FieldOBJ_NowPosGZ_Get(fldobj) == z ){
				return( fldobj );
			}
		}
		
		fldobj++;
		max--;
	}while( max );
	
	return( NULL );
}

//--------------------------------------------------------------
/**
 * 座標、方向を初期化。fx32型
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	vec		初期化座標
 * @param	dir		方向 DIR_UP等
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_VecPosDirInit( FIELD_OBJ_PTR fldobj, const VecFx32 *vec, int dir )
{
	int gx,gy,gz;
	
	gx = SIZE_GRID_FX32( vec->x );
	FieldOBJ_NowPosGX_Set( fldobj, gx );
	
	gy = SIZE_H_GRID_FX32( vec->y );
	FieldOBJ_NowPosGY_Set( fldobj, gy );
	
	gz = SIZE_GRID_FX32( vec->z );
	FieldOBJ_NowPosGZ_Set( fldobj, gz );
	
	FieldOBJ_VecPosSet( fldobj, vec );
	FieldOBJ_GPosUpdate( fldobj );
	
	FieldOBJ_DirDispSetForce( fldobj, dir );
	
//	なんでいれてたのか
//	FldOBJ_WorkInit_MoveProcInit( fldobj );
//	FldOBJ_WorkInit_DrawProcInit( fldobj );
	
	FieldOBJ_AcmdFree( fldobj );
	FieldOBJ_StatusBit_ON( fldobj, FLDOBJ_STA_BIT_MOVE_START );
	FieldOBJ_StatusBit_OFF( fldobj, FLDOBJ_STA_BIT_MOVE | FLDOBJ_STA_BIT_MOVE_END );
}

//--------------------------------------------------------------
/**
 * 座標、方向を初期化。グリッド座標型
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	x		グリッドX座標
 * @param	y		グリッドY座標
 * @param	z		グリッドZ座標
 * @param	dir		方向 DIR_UP等
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_GPosDirInit( FIELD_OBJ_PTR fldobj, int x, int y, int z, int dir )
{
	VecFx32 vec;
	
	vec.x = GRID_SIZE_FX32( x ) + FLDOBJ_VEC_X_GRID_OFFS_FX32;
	FieldOBJ_NowPosGX_Set( fldobj, x );
	
	vec.y = H_GRID_SIZE_FX32( y ) + FLDOBJ_VEC_Y_GRID_OFFS_FX32;
	FieldOBJ_NowPosGY_Set( fldobj, y );
	
	vec.z = GRID_SIZE_FX32( z ) + FLDOBJ_VEC_Z_GRID_OFFS_FX32;
	FieldOBJ_NowPosGZ_Set( fldobj, z );
	
	FieldOBJ_VecPosSet( fldobj, &vec );
	FieldOBJ_GPosUpdate( fldobj );
	
	FieldOBJ_DirDispSetForce( fldobj, dir );
	
//	なんでいれてたのか
//	FldOBJ_WorkInit_MoveProcInit( fldobj );
//	FldOBJ_WorkInit_DrawProcInit( fldobj );

//	高さは引数の値を信用する
//	FieldOBJ_StatusBit_ON( fldobj, FLDOBJ_STA_BIT_MOVE_START | FLDOBJ_STA_BIT_HEIGHT_GET_NEED );
	FieldOBJ_StatusBit_ON( fldobj, FLDOBJ_STA_BIT_MOVE_START );
	FieldOBJ_StatusBit_OFF( fldobj, FLDOBJ_STA_BIT_MOVE | FLDOBJ_STA_BIT_MOVE_END );
	
	FieldOBJ_AcmdFree( fldobj );
}

//--------------------------------------------------------------
/**
 * 動作コード変更
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	code	MV_RND等
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_MoveCodeChange( FIELD_OBJ_PTR fldobj, u32 code )
{
	FieldOBJ_MoveDeleteProcCall( fldobj );
	FieldOBJ_MoveCodeSet( fldobj, code );
	FldOBJ_WorkInit_MoveProcInit( fldobj );
	FieldOBJ_MoveInit( fldobj );
}

//--------------------------------------------------------------
/**
 * OBJ IDを変更
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	id		OBJ ID
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_OBJIDChange( FIELD_OBJ_PTR fldobj, int id )
{
	FieldOBJ_OBJIDSet( fldobj, id );
		
	FieldOBJ_StatusBitON_MoveStart( fldobj );
	FldOBJ_DrawEffectFlagInit( fldobj );
}

//==============================================================================
//	動作関数ダミー
//==============================================================================
//--------------------------------------------------------------
/**
 * 動作初期化関数ダミー
 * @param	FIELD_OBJ	FIELD_OBJ_PTR 
 * @retval	int			TRUE=初期化成功
 */
//--------------------------------------------------------------
void FieldOBJ_MoveInitProcDummy( FIELD_OBJ_PTR fldobj )
{
}

//--------------------------------------------------------------
/**
 * 動作関数ダミー
 * @param	FIELD_OBJ	FIELD_OBJ_PTR 
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_MoveProcDummy( FIELD_OBJ_PTR fldobj )
{
}

//--------------------------------------------------------------
/**
 * 動作削除関数ダミー
 * @param	FIELD_OBJ	FIELD_OBJ_PTR 
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_MoveDeleteProcDummy( FIELD_OBJ_PTR fldobj )
{
}

//--------------------------------------------------------------
/**
 * 動作復帰関数ダミー
 * @param	FIELD_OBJ_PTR	FIELD_OBJ_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_MoveReturnProcDummy( FIELD_OBJ_PTR fldobj )
{
}

//==============================================================================
//	描画関数ダミー
//==============================================================================
//--------------------------------------------------------------
/**
 * 描画初期化関数ダミー
 * @param	FIELD_OBJ	FIELD_OBJ_PTR 
 * @retval	int			TRUE=初期化成功
 */
//--------------------------------------------------------------
void FieldOBJ_DrawInitProcDummy( FIELD_OBJ_PTR fldobj )
{
}

//--------------------------------------------------------------
/**
 * 描画関数ダミー
 * @param	FIELD_OBJ	FIELD_OBJ_PTR 
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_DrawProcDummy( FIELD_OBJ_PTR fldobj )
{
}

//--------------------------------------------------------------
/**
 * 描画削除関数ダミー
 * @param	FIELD_OBJ	FIELD_OBJ_PTR 
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_DrawDeleteProcDummy( FIELD_OBJ_PTR fldobj )
{
}

//--------------------------------------------------------------
/**
 * 描画退避関数ダミー
 * @param	FIELD_OBJ	FIELD_OBJ_PTR 
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_DrawPushProcDummy( FIELD_OBJ_PTR fldobj )
{
}

//--------------------------------------------------------------
/**
 * 描画復帰関数ダミー
 * @param	FIELD_OBJ	FIELD_OBJ_PTR 
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_DrawPopProcDummy( FIELD_OBJ_PTR fldobj )
{
}
