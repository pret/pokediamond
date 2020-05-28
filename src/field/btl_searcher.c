//============================================================================================
/**
 * @file	btl_searcher.c
 * @bfief	バトルサーチャー
 * @author	Satoshi Nohara
 * @date	06.04.26
 */
//============================================================================================
#include "common.h"
#include "gflib/msg_print.h"

#include "system/lib_pack.h"
#include "system/snd_tool.h"

#include "fieldmap.h"
#include "fieldsys.h"
#include "zonedata.h"
#include "mapdefine.h"

#include "itemtool/itemsym.h"							//
#include "battle/trno_def.h"

#include "field/eventflag.h"							//
#include "field/evwkdef.h"								//

#include "script.h"										//
#include "syswork.h"
#include "sysflag.h"
#include "eventdata.h"
#include "fieldobj_code.h"
#include "btl_searcher.h"


//==============================================================================================
//
//	定義
//
//==============================================================================================
//#define BS_LEVEL_MAX		(5)				//再戦の最大レベル
#define BS_LEVEL_MAX		(6)				//再戦の最大レベル

#define REMATCH_DATA_END	(0)				//再戦データなし
#define REMATCH_DATA_DUMMY	(0xffff)		//再戦データダミー(次のレベルを見にいくようにする)

#define	BS_RAND_NOSET		(50)			//５０％の確率で再戦トレーナーセットしない
#define	NOT_EXIST_OFS		(-1)			//再戦データが存在しない場合

//検索範囲
#define BS_SEARCH_SX		(7)				//検索範囲
#define BS_SEARCH_TOP		(7)				//検索範囲(主人公から画面上)
#define BS_SEARCH_BOTTOM	(6)				//検索範囲(主人公から画面下)

#define	BS_FLDOBJ_MAX		(64)			//FIELD_OBJ_PTRの最大数(要確認！)

//トレーナーサーチ使用チェック
enum{
	BS_NO_BATTERY = 0,						//バッテリーが溜まっていない
	BS_NO_TRAINER,							//画面内にトレーナーがいない
	BS_OK_BATTERY,							//バッテリーが溜まっていて、画面内にトレーナーもいる
};

//シーケンスナンバー定義
enum{
	BS_SEQ_INIT = 0,
	BS_SEQ_START,
	BS_SEQ_OK_BATTERY,
	BS_SEQ_OK_BATTERY_ANM_WAIT,
	BS_SEQ_OK_BATTERY_LOTTERY,
	BS_SEQ_OK_BATTERY_LOTTERY_ANM_WAIT,
	BS_SEQ_NO_BATTERY,
	BS_SEQ_NO_TRAINER,
	BS_SEQ_EXIT,
};

//セットになっているトレーナーのポインタを取得する時のモード
#define BS_2VS2_MV_REWAR_CHK_ON		(0)		//再戦動作コードのチェックあり
#define BS_2VS2_MV_REWAR_CHK_OFF	(1)		//再戦動作コードのチェックなし


//==============================================================================================
//
//	構造体
//
//==============================================================================================
//データ構造体(btl_searcher.datで使用)
typedef struct {
	u16 id[BS_LEVEL_MAX];					//識別ID
}REMATCH_DATA;
#include "../fielddata/btl_searcher/rematch.dat"

//システム構造体
typedef struct{
	u32	seq;

	FIELDSYS_WORK* fsys;					//FIELDSYS_WORK型のポインタ
	EVENTWORK* ev;							//EVENTWORK型のポインタ

	const REMATCH_DATA* data;				//再戦データのポインタ(rematch.dat)

	FIELD_OBJ_PTR fldobj[BS_FLDOBJ_MAX];	//

	u16	fldobj_max;							//最大数
	u16 anm_count;							//アニメ登録カウント

	u16* ret_wk;							//結果を返すワークへのポインタ
	WORDSET* wordset;						//単語セット
}BS_SYS;

//アニメーション終了監視ワーク
typedef struct{
	TCB_PTR	tcb;					//TCB
	TCB_PTR	anm_tcb;				//アニメーションTCB
	BS_SYS* bs_sys;					//BS_SYSのポインタ
}BS_ANM_WORK;


//==============================================================================================
//
//	プロトタイプ宣言
//
//==============================================================================================
void EventCmd_BtlSearcher(GMEVENT_CONTROL* event,WORDSET* wordset,u16* ret_wk);	//scrcmd.c
u16 BS_TrainerIDCheck( FIELDSYS_WORK* fsys, FIELD_OBJ_PTR fldobj, u16 tr_id );	//scrcmd.c
BOOL BS_StepCountUp( FIELDSYS_WORK* fsys );										//ev_check.c
static BOOL BS_HideMoveCodeCheck( u32 code );

static BOOL GMEVENT_StartBtlSearcher( GMEVENT_CONTROL* event );
static int BS_UseChk( BS_SYS* bs_sys );
static void BS_SeqChange( BS_SYS* bs_sys, u32 seq );
static void BS_FldObjDataSet( BS_SYS* bs_sys );

//アニメ関連
static void BS_FldObjAnmSet( BS_SYS* bs_sys );
static void BS_AnmSet( BS_SYS* bs_sys, FIELD_OBJ_PTR fldobj, const FIELD_OBJ_ACMD_LIST *list );
static void BS_AnmSetTCB( BS_SYS* bs_sys, TCB_PTR anm_tcb );
static void BS_AnmMainTCB( TCB_PTR tcb, void* wk );
static BOOL BS_AnmWait( BS_SYS* bs_sys );

static BOOL BS_Lottery( BS_SYS* bs_sys );
static u16 BS_TrainerIdGetByScriptId( FIELD_OBJ_PTR fldobj );

static void BS_RevengeMoveCodeClear( FIELDSYS_WORK* fsys );
static u16 BS_RevengeDataIndexGet( FIELDSYS_WORK* fsys, u16 tr_id );
static u16 BS_RevengeDataLevelGet( FIELDSYS_WORK* fsys, u16 index );
static u16 BS_RevengeDataLevelEventCheck( FIELDSYS_WORK* fsys, u16 index, u16 level );
static u16 BS_RevengeDataLevelEventCheckSub( u16 index, u16 level );
static u16 BS_RevengeTrainerIDGet( u16 index, u16 level );
static BOOL BS_RevengeMoveCodeCheck( FIELD_OBJ_PTR fldobj );
static void BS_MvSet( FIELD_OBJ_PTR fldobj, u16 code );
void BS_MvReWarClearDirMvSet( FIELDSYS_WORK* fsys, FIELD_OBJ_PTR fldobj );
static BOOL BS_StatusBitCheckMove( FIELDSYS_WORK* fsys );
static FIELD_OBJ_PTR BS_2vs2TrPtrGet( FIELDSYS_WORK* fsys, FIELD_OBJ_PTR search_obj, int mode );


//==============================================================================================
//
//	アニメーションデータ
//
//==============================================================================================
//回転アニメ
static const FIELD_OBJ_ACMD_LIST ps_anm_1[] = {
	{ AC_STAY_WALK_D_8F, 1 },
	{ AC_WAIT_4F, 1 },
	{ AC_DIR_R, 1 },
	{ AC_WAIT_4F, 1 },
	{ AC_DIR_U, 1 },
	{ AC_WAIT_4F, 1 },
	{ AC_DIR_L, 1 },
	{ AC_WAIT_4F, 1 },
	{ AC_DIR_D, 1 },
	{ AC_WAIT_4F, 1 },
	{ ACMD_END, 0 },
};

//再戦可能アニメ
static const FIELD_OBJ_ACMD_LIST ps_anm_ok[] = {
	{ AC_DIR_D, 1 },
	{ AC_MARK_SAISEN, 1 },
	{ ACMD_END, 0 },
};

//初戦がまだアニメ
static const FIELD_OBJ_ACMD_LIST ps_anm_first[] = {
	{ AC_MARK_GYOE, 1 },
	{ ACMD_END, 0 },
};

//何もしないアニメ
static const FIELD_OBJ_ACMD_LIST ps_anm_ng[] = {
	{ AC_WAIT_8F, 1 },
	{ ACMD_END, 0 },
};


//==============================================================================================
//
//	アイテム使用で呼ばれる
//
//==============================================================================================

//----------------------------------------------------------------------------------------------
/**
 * イベント呼び出し
 * 
 * @param	event		イベント制御ワークへのポインタ
 * @param	wordset		WORDSET型のポインタ
 * @param	ret_wk		結果を返すワークへのポインタ
 *
 * @retval	none
 */
//----------------------------------------------------------------------------------------------
void EventCmd_BtlSearcher( GMEVENT_CONTROL* event, WORDSET* wordset, u16* ret_wk )
{
	BS_SYS* bs_sys;
	FIELDSYS_WORK* fsys	= FieldEvent_GetFieldSysWork( event );

	//システムワーク確保
	bs_sys = sys_AllocMemory( HEAPID_FIELD, sizeof(BS_SYS) );
	if( bs_sys == NULL ){
		GF_ASSERT( (0) && "メモリ確保失敗！" );
		return;
	}

	//初期化
	memset( bs_sys, 0, sizeof(BS_SYS) );
	bs_sys->fsys	= fsys;
	bs_sys->ev		= SaveData_GetEventWork( fsys->savedata );
	bs_sys->ret_wk	= ret_wk;
	bs_sys->wordset	= wordset;

	FieldEvent_Call( event, GMEVENT_StartBtlSearcher, bs_sys );
	return;
}

//----------------------------------------------------------------------------------------------
/**
 * イベントメイン
 * 
 * @param	event		イベント制御ワークへのポインタ
 *
 * @retval	"FALSE=継続、TRUE=終了"
 */
//----------------------------------------------------------------------------------------------
static BOOL GMEVENT_StartBtlSearcher( GMEVENT_CONTROL* event )
{
	s32 num,keta;
	int ret;
	BS_SYS* bs_sys = FieldEvent_GetSpecialWork( event );

	switch( bs_sys->seq ){

	//グリッドに収まるまで待つ
	case BS_SEQ_INIT:
		if( BS_StatusBitCheckMove(bs_sys->fsys) == TRUE ){
			BS_SeqChange( bs_sys, BS_SEQ_START );
		}
		break;

	//開始
	case BS_SEQ_START:

		//画面内にいるトレーナーのデータをセット
		BS_FldObjDataSet( bs_sys );

		ret = BS_UseChk( bs_sys );

		//バッテリーが溜まっていて、画面内にトレーナーもいる
		if( ret == BS_OK_BATTERY ){
			*bs_sys->ret_wk = 0;
			BS_SeqChange( bs_sys, BS_SEQ_OK_BATTERY );
		}else if( ret == BS_NO_BATTERY ){
			*bs_sys->ret_wk = 1;
			BS_SeqChange( bs_sys, BS_SEQ_NO_BATTERY );
		}else{
			*bs_sys->ret_wk = 2;
			BS_SeqChange( bs_sys, BS_SEQ_NO_TRAINER );
		}
		break;

	//バッテリーが溜まっていて、画面内にトレーナーもいる
	case BS_SEQ_OK_BATTERY:
		Snd_SePlay( SE_BTL_SEARCHER );							//ピッピッピ
		SysWork_BtlSearcherBatterySet( bs_sys->ev, 0 );			//バッテリークリア
		//BS_FldObjAnmSet( bs_sys );							//回転アニメセット
		BS_SeqChange( bs_sys, BS_SEQ_OK_BATTERY_ANM_WAIT );
		break;

	//トレーナーの回転アニメ終了待ち
	case BS_SEQ_OK_BATTERY_ANM_WAIT:
		if( BS_AnmWait(bs_sys) == 0 ){
			BS_SeqChange( bs_sys, BS_SEQ_OK_BATTERY_LOTTERY );
		}
		break;

	//再戦の抽選を行う
	case BS_SEQ_OK_BATTERY_LOTTERY:
		if( BS_Lottery(bs_sys) == 0 ){
			*bs_sys->ret_wk = 3;
		}
		BS_SeqChange( bs_sys, BS_SEQ_OK_BATTERY_LOTTERY_ANM_WAIT );
		break;

	//再戦可能、初戦まだ、何もしないアニメ待ち
	case BS_SEQ_OK_BATTERY_LOTTERY_ANM_WAIT:
		if( BS_AnmWait(bs_sys) == 0 ){
			BS_SeqChange( bs_sys, BS_SEQ_EXIT );
		}
		break;

	//バッテリーが溜まっていない
	case BS_SEQ_NO_BATTERY:

		//足りないバッテリー量をバッファにセットする
		num = ( BS_BATTERY_MAX - SysWork_BtlSearcherBatteryGet(bs_sys->ev) );

		//桁数取得
		if( (num / 10) == 0 ){
			keta = 1;
		}else if( (num / 100) == 0 ){
			keta = 2;
		}else{
			keta = 3;
		}

		WORDSET_RegisterNumber( bs_sys->wordset, 0, num, keta,
								NUMBER_DISPTYPE_SPACE, NUMBER_CODETYPE_DEFAULT);

		BS_SeqChange( bs_sys, BS_SEQ_EXIT );
		break;

	//画面内にトレーナーがいない
	case BS_SEQ_NO_TRAINER:
		BS_SeqChange( bs_sys, BS_SEQ_EXIT );
		break;

	//終了
	case BS_SEQ_EXIT:
		sys_FreeMemoryEz( bs_sys );
		return TRUE;
	};

	return FALSE;
}

//----------------------------------------------------------------------------------------------
/**
 * シーケンス変更
 *
 * @param   bs_sys		BS_SYS型のポインタ
 * @param   seq			セットするシーケンス
 *
 * @retval	none
 */
//----------------------------------------------------------------------------------------------
static void BS_SeqChange( BS_SYS* bs_sys, u32 seq )
{
	bs_sys->seq = seq;
	return;
}

//----------------------------------------------------------------------------------------------
/**
 * バトルサーチャー使用チェック
 *
 * @param   bs_sys		BS_SYS型のポインタ
 *
 * @retval	BS_NO_BATTERY	バッテリーが溜まっていない
 * @retval	BS_NO_TRAINER	画面内にトレーナーがいない
 * @retval	BS_OK_BATTERY	バッテリーが溜まっていて、画面内にトレーナーもいる
 */
//----------------------------------------------------------------------------------------------
static int BS_UseChk( BS_SYS* bs_sys )
{
	//バッテリカウンターが溜まっているか	
	if( SysWork_BtlSearcherBatteryGet(bs_sys->ev) == BS_BATTERY_MAX ){

		//画面内にトレーナーいるか
		if( bs_sys->fldobj_max == 0 ){
			//画面内にトレーナーいない
			return BS_NO_TRAINER;
		}

		//バッテリーが溜まっていて、画面内にトレーナーもいる
		return BS_OK_BATTERY;
	}

	//バッテリー不足
	return BS_NO_BATTERY;
}

//----------------------------------------------------------------------------------------------
/**
 * バトルサーチャーシステムに画面内にいるトレーナーのデータをセット
 *
 * @param   bs_sys		BS_SYS型のポインタ
 *
 * @retval	none
 */
//----------------------------------------------------------------------------------------------
static void BS_FldObjDataSet( BS_SYS* bs_sys )
{
	int x,z;
	u32 event_type;

	int	hero_gx,hero_gz,i,count;
	int l,r,u,d;
	FIELD_OBJ_PTR fldobj;

	u32 obj_max = EventData_GetNpcCount( bs_sys->fsys );

	//初期化
	count = 0;

	for( i=0; i < obj_max ;i++ ){
		bs_sys->fldobj[i] = NULL;
	}

	//主人公の位置取得
	hero_gx = Player_NowGPosXGet( bs_sys->fsys->player );
	hero_gz = Player_NowGPosZGet( bs_sys->fsys->player );

	//検索範囲をセット(3Dは意識せずの簡易版)
	l = hero_gx - BS_SEARCH_SX;
	r = hero_gx + BS_SEARCH_SX;
	u = hero_gz - BS_SEARCH_TOP;
	d = hero_gz + BS_SEARCH_BOTTOM;

	//補正
	if( l < 0 ){ l = 0; }
	//if( r < 0 ){ 0 };
	if( u < 0 ){ u = 0; }
	//if( d < 0 ){ 0 };

	//OBJデータ分サーチをかける
	for( i=0; i < obj_max ;i++ ){

		//フィールドOBJのポインタ取得
		fldobj	= FieldOBJSys_OBJIDSearch( bs_sys->fsys->fldobjsys, i );
		if( fldobj == NULL ){
			continue;
		}

		//イベントタイプがトレーナーかチェック
		event_type = FieldOBJ_EventTypeGet( fldobj );

		switch( event_type ){
		case EV_TYPE_TRAINER:
		case EV_TYPE_TRAINER_EYEALL:
		case EV_TYPE_TRAINER_KYORO:
		case EV_TYPE_TRAINER_SPIN_STOP_L:
		case EV_TYPE_TRAINER_SPIN_STOP_R:
		case EV_TYPE_TRAINER_SPIN_MOVE_L:
		case EV_TYPE_TRAINER_SPIN_MOVE_R:

			//検索範囲内にあるかチェック
			x = FieldOBJ_NowPosGX_Get( fldobj );
			z = FieldOBJ_NowPosGZ_Get( fldobj );
			if( (x >= l) && (x <= r) && (z >= u) && (z <= d) ){

				//動作コードが隠れ蓑かチェック
				if( BS_HideMoveCodeCheck(FieldOBJ_MoveCodeGet(fldobj)) == FALSE ){
					//OS_Printf( "id = %d\n", i );
					//OS_Printf( "event_type = %d\n", event_type );

					//システムワークにセット
					bs_sys->fldobj[count] = fldobj;
					count++;
				}
			}
		};
	}

	bs_sys->fldobj_max = count;
	return;
}

//----------------------------------------------------------------------------------------------
/**
 * 動作コードが隠れ蓑かチェック
 *
 * @param   code	動作コード
 *
 * @retval	"FALSE=違う、TRUE=隠れ蓑"
 */
//----------------------------------------------------------------------------------------------
static BOOL BS_HideMoveCodeCheck( u32 code )
{
	switch( code ){
	case MV_HIDE_SNOW:		//隠れ蓑　雪
	case MV_HIDE_SAND:		//隠れ蓑　砂
	case MV_HIDE_GRND:		//隠れ蓑　土
	case MV_HIDE_KUSA:		//隠れ蓑　草
		return TRUE;
	};

	return FALSE;
}


//==============================================================================================
//
//	一歩移動で呼ばれる(ev_check.c)
//
//==============================================================================================

//----------------------------------------------------------------------------------------------
/**
 * 歩数カウント
 *
 * @param   fsys	FIELDSYS_WORK型のポインタ
 *
 * @retval	"FALSE	何もしない"
 */
//----------------------------------------------------------------------------------------------
BOOL BS_StepCountUp( FIELDSYS_WORK* fsys )
{
	EVENTWORK* ev		= SaveData_GetEventWork( fsys->savedata );
	u16 battery_count	= SysWork_BtlSearcherBatteryGet( ev );
	u16 clear_count		= SysWork_BtlSearcherClearGet( ev );

	//バトルサーチャーを持っていたら
	if( MyItem_CheckItem( SaveData_GetMyItem(fsys->savedata),
							ITEM_BATORUSAATYAA,1,HEAPID_FIELD) == TRUE ){

		//バッテリーを貯める
		if( battery_count < BS_BATTERY_MAX ) {
			battery_count++;
			SysWork_BtlSearcherBatterySet( ev, battery_count );
		}
	}

	//バッテリーを使用していたら
	if( SysFlag_BtlSearcherUseCheck(ev) == TRUE ){

		//クリアカウンター溜まっていなかったら
		if( clear_count < BS_CLEAR_MAX ){
			clear_count++;
			SysWork_BtlSearcherClearSet( ev, clear_count );
		}
		
		//クリアカウンター溜まっていたら
		if( clear_count == BS_CLEAR_MAX ){
			Sys_BtlSearcherReset( ev );					//sys_work.c
			BS_RevengeMoveCodeClear( fsys );			//再戦動作コードをクリア
		}
	}

	//OS_Printf( "battery_count = %d\n", battery_count );
	//OS_Printf( "clear_count = %d\n", clear_count );
	return FALSE;		//何もしない
}

//----------------------------------------------------------------------------------------------
/**
 * 再戦動作コードをクリアする
 *
 * @param   fsys		FIELDSYS_WORK型のポインタ
 *
 * @retval  none
 */
//----------------------------------------------------------------------------------------------
static void BS_RevengeMoveCodeClear( FIELDSYS_WORK* fsys )
{
	int i;
	FIELD_OBJ_PTR fldobj;
	u32 obj_max = EventData_GetNpcCount( fsys );

	//OBJデータ分サーチをかける
	for( i=0; i < obj_max ;i++ ){

		//フィールドOBJのポインタ取得
		fldobj	= FieldOBJSys_OBJIDSearch( fsys->fldobjsys, i );
		if( fldobj == NULL ){
			continue;
		}

		//動作コードが再戦かチェック
		if( FieldOBJ_MoveCodeGet(fldobj) == MV_REWAR ){
			BS_MvSet( fldobj, MV_DIR_RND );		//「ランダムに方向切替」に変更
		}
	}

	return;
}


//==============================================================================================
//
//	アニメ関連
//
//==============================================================================================

//----------------------------------------------------------------------------------------------
/**
 * フィールドOBJのアニメセット
 *
 * @param   bs_sys		BS_SYS型のポインタ
 *
 * @retval	none
 */
//----------------------------------------------------------------------------------------------
static void BS_FldObjAnmSet( BS_SYS* bs_sys )
{
	int i;

	for( i=0; i < bs_sys->fldobj_max ;i++ ){
		BS_AnmSet( bs_sys, bs_sys->fldobj[i], ps_anm_1 );		//回転アニメセット
	}

	return;
}

//----------------------------------------------------------------------------------------------
/**
 * アニメセット
 *
 * @param   bs_sys		BS_SYS型のポインタ
 * @param   fldobj		FIELD_OBJ_PTR
 *
 * @retval	none
 */
//----------------------------------------------------------------------------------------------
static void BS_AnmSet( BS_SYS* bs_sys, FIELD_OBJ_PTR fldobj, const FIELD_OBJ_ACMD_LIST *list )
{
	TCB_PTR anm_tcb;

	//アニメーションコマンドリストセット
	anm_tcb = FieldOBJ_AcmdListSet( fldobj, list );

	//アニメーションの数を足す
	bs_sys->anm_count++;

	BS_AnmSetTCB( bs_sys, anm_tcb );
	return;
}

//--------------------------------------------------------------------------------------------
/**
 * @brief	アニメ終了監視TCB セット
 *
 * @param	bs_sys	BS_SYS型のポインタ
 * @param	anm_tcb	TCB_PTR型
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void BS_AnmSetTCB( BS_SYS* bs_sys, TCB_PTR anm_tcb )
{
	BS_ANM_WORK* ps_anm_wk = NULL;

	ps_anm_wk = sys_AllocMemory( HEAPID_FIELD, sizeof(BS_ANM_WORK) );
	if( ps_anm_wk == NULL ){
		GF_ASSERT( (0) && "scrcmd.c メモリ確保失敗！" );
		return;
	}

	ps_anm_wk->bs_sys	= bs_sys;
	ps_anm_wk->anm_tcb	= anm_tcb;
	ps_anm_wk->tcb		= TCB_Add( BS_AnmMainTCB, ps_anm_wk, 0 );
	return;
}

//----------------------------------------------------------------------------------------------
/**
 * @brief	アニメ終了監視TCB メイン
 *
 * @param	tcb		TCB_PTR
 * @param	wk		ワークのアドレス
 *
 * @retval	none
 */
//----------------------------------------------------------------------------------------------
static void BS_AnmMainTCB( TCB_PTR tcb, void* wk )
{
	BS_ANM_WORK *swk = (BS_ANM_WORK *)wk;

	//終了していたら
	if( FieldOBJ_AcmdListEndCheck( swk->anm_tcb ) == TRUE ){

		//アニメーション数の管理
		if( swk->bs_sys->anm_count == 0 ){
			GF_ASSERT( (0) && "アニメーション数の管理が不正です！" );
		}

		swk->bs_sys->anm_count--;

		FieldOBJ_AcmdListEnd( swk->anm_tcb );

		TCB_Delete( swk->tcb );
		sys_FreeMemory( HEAPID_FIELD, wk );
	}

	return;
}

//----------------------------------------------------------------------------------------------
/**
 * @brief	アニメ終了チェック
 *
 * @param	tcb		TCB_PTR
 * @param	wk		ワークのアドレス
 *
 * @retval	"0=終了、1=継続"
 */
//----------------------------------------------------------------------------------------------
static BOOL BS_AnmWait( BS_SYS* bs_sys )
{
	return bs_sys->anm_count;
}


//==============================================================================================
//
//	抽選関連
//
//==============================================================================================

//----------------------------------------------------------------------------------------------
/**
 * 再戦状態にするかの抽選を行う
 *
 * @param   bs_sys		BS_SYS型のポインタ
 *
 * @retval	"0 = １人も戦える状態のトレーナーがいなかった、1 = 戦える状態のトレーナーがいた"
 */
//----------------------------------------------------------------------------------------------
static BOOL BS_Lottery( BS_SYS* bs_sys )
{
	EVENTWORK* ev = SaveData_GetEventWork( bs_sys->fsys->savedata );
	FIELD_OBJ_PTR tr_2vs2;
	u16 tr_id;
	int i,flag;

	flag = 0;	//再戦になったトレーナーがいたかフラグ

	for( i=0; i < bs_sys->fldobj_max ;i++ ){

		//初回トレーナーIDに勝利しているかチェック
		tr_id = BS_TrainerIdGetByScriptId( bs_sys->fldobj[i] );
		if( CheckEventFlagTrainer(bs_sys->fsys, tr_id) == FALSE ){		//勝利していない
			BS_AnmSet( bs_sys, bs_sys->fldobj[i], ps_anm_first );		//初戦まだアニメセット
			//Snd_SePlay( SE_MARK_GYOE );
			flag = 1;
		}else{

			//５０％の確率で再戦トレーナーになる
			//動作コードが再戦になっていなかったら(2vs2は再戦になっていることがある)
			//gf_srand( sys.vsync_counter );
			if( ((gf_rand() % 100) < BS_RAND_NOSET) && 
				(BS_RevengeMoveCodeCheck(bs_sys->fldobj[i]) == FALSE) ){

				BS_MvSet( bs_sys->fldobj[i], MV_REWAR );				//再戦動作コードに変更
				BS_AnmSet( bs_sys, bs_sys->fldobj[i], ps_anm_ok );		//再戦可能アニメセット

#if 1
				//セットになっているトレーナーのポインタを取得して再戦セット
				tr_2vs2 = BS_2vs2TrPtrGet(bs_sys->fsys, bs_sys->fldobj[i], BS_2VS2_MV_REWAR_CHK_ON);
				if( tr_2vs2 != NULL ){
					BS_MvSet( tr_2vs2, MV_REWAR );						//再戦動作コードに変更
					BS_AnmSet( bs_sys, tr_2vs2, ps_anm_ok );			//再戦可能アニメセット
				}
#endif

				//Snd_SePlay( SE_MARK_GYOE );
				flag = 1;
				SysFlag_BtlSearcherUseSet( ev );
			
			//再戦トレーナーにならなかった
			}else{
				//BS_MvSet( bs_sys->fldobj[i], MV_DOWN );				//正面向き固定に変更
				//BS_AnmSet( bs_sys, bs_sys->fldobj[i], ps_anm_ng );	//何もしないアニメセット
			}
		}
	}

	return flag;
}

//----------------------------------------------------------------------------------------------
/**
 * スクリプトIDから、トレーナーIDを取得
 *
 * @param   fldobj		FIELD_OBJ_PTR
 *
 * @retval  "トレーナーID"
 */
//----------------------------------------------------------------------------------------------
static u16 BS_TrainerIdGetByScriptId( FIELD_OBJ_PTR fldobj )
{
	u32 script_id = FieldOBJ_EventIDGet( fldobj );
	return GetTrainerIdByScriptId( script_id );
}


//==============================================================================================
//
//	トレーナー話しかけ関連(trainer.ev)
//
//==============================================================================================

//----------------------------------------------------------------------------------------------
/**
 * FIELD_OBJ_PTRの再戦トレーナーIDを取得
 *
 * @param   fsys		FIELDSYS_WORK型のポインタ
 * @param   fldobj		FIELD_OBJ_PTR
 * @param   tr_id		検索するトレーナーID
 *
 * @retval  "0 = データなし、0以外 = トレーナーID"
 *
 * @li		"トレーナーID = 0 = 自分"として扱われている(再戦データテーブルに含まれていないのでOK)
 */
//----------------------------------------------------------------------------------------------
u16 BS_TrainerIDCheck( FIELDSYS_WORK* fsys, FIELD_OBJ_PTR fldobj, u16 tr_id )
{
	u16 index,level,ret;

	//再戦動作コードかチェック
	if( BS_RevengeMoveCodeCheck(fldobj) == FALSE ){
		return 0;
	}

	//データインデックス取得
	index = BS_RevengeDataIndexGet( fsys, tr_id );
	if( index == 0xff ){
		return 0;
	}

	//データレベル取得
	level = BS_RevengeDataLevelGet( fsys, index );
	//OS_Printf( "level = %d\n", level );

	//イベント進行チェックによって再戦レベルを調整
	level = BS_RevengeDataLevelEventCheck( fsys, index, level );
	//OS_Printf( "level = %d\n", level );

	//再戦トレーナーID取得
	ret = BS_RevengeTrainerIDGet( index, level );
	//OS_Printf( "ret = %d\n", ret );

	return ret;
}

//----------------------------------------------------------------------------------------------
/**
 * 再戦データテーブルのインデックスを取得
 *
 * @param   fsys		FIELDSYS_WORK型のポインタ
 * @param   tr_id		検索するトレーナーID
 *
 * @retval  "0xff以外 = インデックス、0xff = 見つからなかった"
 */
//----------------------------------------------------------------------------------------------
static u16 BS_RevengeDataIndexGet( FIELDSYS_WORK* fsys, u16 tr_id )
{
	int i,level;
	//REMATCH_DATA* data = bs_sys->data;
	const REMATCH_DATA* data = RematchDataTbl;

	//再戦トレーナーデータ分検索
	for( i=0; i < REMATCH_DATA_MAX; i++ ){

		//同じトレーナーIDを探す
		if( data[i].id[0] != tr_id ){
			continue;
		}

		//同じトレーナーIDがあった
		return i;
	}

	return 0xff;
}

//----------------------------------------------------------------------------------------------
/**
 * 再戦レベルを取得
 *
 * @param   fsys		FIELDSYS_WORK型のポインタ
 * @param   index		再戦データテーブルのインデックス
 *
 * @retval  "レベル"
 */
//----------------------------------------------------------------------------------------------
static u16 BS_RevengeDataLevelGet( FIELDSYS_WORK* fsys, u16 index )
{
	int i,level;
	//REMATCH_DATA* data = bs_sys->data;
	const REMATCH_DATA* data = RematchDataTbl;

	//再戦レベルを検索
	for( level = 1; level < BS_LEVEL_MAX; level++ ){

		//再戦データがないかチェック
		if( data[index].id[level] == REMATCH_DATA_END ){
			return (level - 1);
		}

		//再戦データがダミーかチェック
		if( data[index].id[level] != REMATCH_DATA_DUMMY ){

			//そのレベルは対戦していないかチェック
			if( CheckEventFlagTrainer(fsys, data[index].id[level]) == FALSE ){
				return (level);
			}
		}
	}

	//レベルが最高
	return (level - 1);
}

//----------------------------------------------------------------------------------------------
/**
 * イベント進行チェックによって再戦レベルを調整
 *
 * @param   fsys	FIELDSYS_WORK型のポインタ
 * @param   index	再戦データテーブルのインデックス
 * @param   level	再戦レベル
 *
 * @retval	"調整後の再生レベル"
 *
 * 進行チェックはまだ未定なので仮です！
 */
//----------------------------------------------------------------------------------------------
static u16 BS_RevengeDataLevelEventCheck( FIELDSYS_WORK* fsys, u16 index, u16 level )
{
	EVENTWORK* ev = SaveData_GetEventWork( fsys->savedata );
	u16 ret = level;

	switch( level ){

	case 0:
		break;

	default:

		if( SysFlag_BsLvCheck(ev,level) == FALSE ){
			ret = BS_RevengeDataLevelEventCheckSub( index, level );
		}
		break;

	};

	return ret;
}

//----------------------------------------------------------------------------------------------
/**
 * REMATCH_DATA_DUMMYをチェックして再戦レベルを下げる
 *
 * @param   index	再戦データテーブルのインデックス
 * @param   level	再戦レベル
 *
 * @retval	"調整後の再生レベル"
 */
//----------------------------------------------------------------------------------------------
static u16 BS_RevengeDataLevelEventCheckSub( u16 index, u16 level )
{
	u16 i;
	const REMATCH_DATA* data = RematchDataTbl;

	//再戦データがダミーかチェック
	for( i=(level-1); i > 0; i-- ){

		if( data[index].id[i] != REMATCH_DATA_DUMMY ){
			return i;
		}
	}

	return 0;			//レベル0
}

//----------------------------------------------------------------------------------------------
/**
 * 再戦トレーナーIDを取得
 *
 * @param   index			再戦データテーブルのインデックス
 * @param   level			再戦データテーブルのレベル
 *
 * @retval  "再戦トレーナーID"
 */
//----------------------------------------------------------------------------------------------
static u16 BS_RevengeTrainerIDGet( u16 index, u16 level )
{
	//REMATCH_DATA* data = bs_sys->data;
	const REMATCH_DATA* data = RematchDataTbl;
	return data[index].id[level];
}

//----------------------------------------------------------------------------------------------
/**
 * 再戦動作コードがチェック
 *
 * @param   fldobj		FIELD_OBJ_PTR
 *
 * @retval  "TRUE = 再戦動作コードだった、FALSE = ちがう"
 */
//----------------------------------------------------------------------------------------------
static BOOL BS_RevengeMoveCodeCheck( FIELD_OBJ_PTR fldobj )
{
	//OS_Printf( "mv_code = %d\n", FieldOBJ_MoveCodeGet(fldobj) );
	//OS_Printf( "obj_id = %d\n", FieldOBJ_OBJIDGet(fldobj) );

	if( FieldOBJ_MoveCodeGet(fldobj) == MV_REWAR ){
		return TRUE;
	}

	return FALSE;
}

//----------------------------------------------------------------------------------------------
/**
 * 動作コードセット
 *
 * @param   fldobj		FIELD_OBJ_PTR
 * @param   code		動作コード
 *
 * @retval  none
 */
//----------------------------------------------------------------------------------------------
static void BS_MvSet( FIELD_OBJ_PTR fldobj, u16 code )
{
	//FieldOBJ_MoveCodeSet( fldobj, code );
	FieldOBJ_MoveCodeChange( fldobj, code );
	return;
}

//----------------------------------------------------------------------------------------------
/**
 * 再戦動作コードだったら、現在向いている方向固定の動作コードをセットする(戦闘後に呼ばれる)
 *
 * @param   fldobj		FIELD_OBJ_PTR
 *
 * @retval  none
 */
//----------------------------------------------------------------------------------------------
void BS_MvReWarClearDirMvSet( FIELDSYS_WORK* fsys, FIELD_OBJ_PTR fldobj )
{
	FIELD_OBJ_PTR tr_2vs2;
	u32 code;
	int dir;
	
	//不正チェック
	if( fldobj == NULL ){
		return;
	}

#if 0
	//動作コードが再戦かチェック
	if( FieldOBJ_MoveCodeGet(fldobj) != MV_REWAR ){
		return;
	}
#endif

	//表示方向取得
	dir = FieldOBJ_DirDispGet( fldobj );

	if( dir == DIR_UP ){
		code = MV_UP;
	}else if( dir == DIR_DOWN ){
		code = MV_DOWN;
	}else if( dir == DIR_LEFT ){
		code = MV_LEFT;
	}else{
		code = MV_RIGHT;
	}

#if 1
	//2vs2の時はセットになっているトレーナーの動作コードも落とす必要がある！
	tr_2vs2 = BS_2vs2TrPtrGet( fsys, fldobj, BS_2VS2_MV_REWAR_CHK_OFF );
	if( tr_2vs2 != NULL ){
		BS_MvSet( tr_2vs2, code );
	}
#endif

	BS_MvSet( fldobj, code );
	return;
}


//==============================================================================================
//
//	チェック
//
//==============================================================================================

//----------------------------------------------------------------------------------------------
/**
 * グリッドに収まるまで待つ
 *
 * @param   fsys		FIELDSYS_WORK型のポインタ
 *
 * @retval  "TRUE = 動作終了、FALSE = 移動中"
 */
//----------------------------------------------------------------------------------------------
static BOOL BS_StatusBitCheckMove( FIELDSYS_WORK* fsys )
{
	int i,flag;
	FIELD_OBJ_PTR fldobj;
	u32 obj_max = EventData_GetNpcCount( fsys );

	flag = 0;	//クリア

	//OS_Printf( "*******＜グリッドチェック＞*******\n" );

	//OBJデータ分サーチをかける
	for( i=0; i < obj_max ;i++ ){

		//フィールドOBJのポインタ取得
		fldobj	= FieldOBJSys_OBJIDSearch( fsys->fldobjsys, i );
		if( fldobj == NULL ){
			continue;
		}

		//移動動作中かチェック
		if( FieldOBJ_StatusBitCheck_Move(fldobj) == TRUE ){
			//OS_Printf( "no = %d = 動作中\n", i );
			FieldOBJ_MovePauseClear( fldobj );
			flag = 1;							//動作終了していないのでフラグON
		}else{
			//OS_Printf( "no = %d = 動作終了\n", i );
			FieldOBJ_MovePause( fldobj );		//動作ポーズ
		}
	}

	if( flag == 0 ){
		return TRUE;
	}else{
		return FALSE;
	}
}

//----------------------------------------------------------------------------------------------
/**
 * セットになっているトレーナーのポインタを取得
 *
 * @param   fsys			FIELDSYS_WORK型のポインタ
 * @param   search_scr_id	サーチするスクリプトID
 * @param   search_tr_id	サーチするトレーナーID
 *
 * @retval "NULL=見つからなかった、NULL以外=セットのトレーナーのFIELD_OBJ_PTR"
 *
 * モード
 * BS_2VS2_MV_REWAR_CHK_ON		(0)		//再戦動作コードのチェックあり
 * BS_2VS2_MV_REWAR_CHK_OFF		(1)		//再戦動作コードのチェックなし
 */
//----------------------------------------------------------------------------------------------
static FIELD_OBJ_PTR BS_2vs2TrPtrGet( FIELDSYS_WORK* fsys, FIELD_OBJ_PTR search_obj, int mode )
{
	FIELD_OBJ_PTR fldobj;
	u32 i,event_type,scr_id,tr_id;
	u32 obj_max			= EventData_GetNpcCount( fsys );
	u16 search_scr_id	= FieldOBJ_EventIDGet( search_obj );			//スクリプトIDを取得
	u16 search_tr_id	= GetTrainerIdByScriptId( search_scr_id );		//トレーナーIDを取得

	//シングルバトルタイプの時は何もしない！
	if( CheckTrainer2vs2Type(search_tr_id) == 0 ){
		return NULL;
	}

	//双子ちゃんの片方しか範囲に入っていない時があるので、ゾーン内を全サーチする！
	for( i=0; i < obj_max ;i++ ){

		//フィールドOBJのポインタ取得
		fldobj	= FieldOBJSys_OBJIDSearch( fsys->fldobjsys, i );
		if( fldobj == NULL ){
			continue;
		}

#if 1
		if(  mode == BS_2VS2_MV_REWAR_CHK_ON ){			//再戦動作コードのチェックあり

			//動作コードが再戦になっているOBJは何もしない
			if( FieldOBJ_MoveCodeGet(fldobj) == MV_REWAR ){
				continue;
			}
		}
#endif

		//イベントタイプがトレーナーかチェック
		event_type = FieldOBJ_EventTypeGet( fldobj );

		switch( event_type ){
		case EV_TYPE_TRAINER:
		case EV_TYPE_TRAINER_EYEALL:
		case EV_TYPE_TRAINER_KYORO:
		case EV_TYPE_TRAINER_SPIN_STOP_L:
		case EV_TYPE_TRAINER_SPIN_STOP_R:
		case EV_TYPE_TRAINER_SPIN_MOVE_L:
		case EV_TYPE_TRAINER_SPIN_MOVE_R:

			//OS_Printf( "id = %d\n", i );
			//OS_Printf( "event_type = %d\n", event_type );

			scr_id	= FieldOBJ_EventIDGet( fldobj );			//スクリプトIDを取得
			tr_id	= GetTrainerIdByScriptId( scr_id );			//トレーナーIDを取得

			//スクリプトIDが同じではなく、トレーナーIDが同じになっているトレーナーを探す
			if( (search_scr_id != scr_id) && (search_tr_id == tr_id) ){
				return fldobj;	//見つけた！
			}
		};
	}

	return NULL;
}




