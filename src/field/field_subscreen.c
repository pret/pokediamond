//============================================================================================
/**
 * @file	field_subscreen.c
 * @brief
 * @author	tamada
 * @date	2006.02.03
 */
//============================================================================================

#include "common.h"
#include "system/pm_overlay.h"


#include "fieldsys.h"

#include "field_subscreen.h"

#include "comm_union.h"
#include "comm_union_view.h"
#include "comm_union_view_def.h"
#include "union_board.h"
#include "comm_field_state.h"
#include "field_poketch.h"



//============================================================================================
//============================================================================================
//------------------------------------------------------------------
/**
 * @brief	サブ画面処理ツールのまとめ
 */
//------------------------------------------------------------------
typedef struct SUBSCRN_FUNCLIST{
	void (*set_init)(FIELDSYS_WORK *);		///<サブ画面初期化処理リクエスト関数
	BOOL (*wait_init)(FIELDSYS_WORK *);		///<サブ画面初期化処理待ち関数
	void (*set_quit)(FIELDSYS_WORK *);		///<サブ画面終了処理リクエスト関数
	BOOL (*wait_quit)(FIELDSYS_WORK *);		///<サブ画面終了処理待ち関数
}SUBSCRN_FUNCLIST;



FS_EXTERN_OVERLAY(unionroom_board);

//============================================================================================
//============================================================================================
static void FieldSubScreen_Init_Normal(FIELDSYS_WORK * fsys);
static void FieldSubScreen_Init_Under(FIELDSYS_WORK * fsys);
static void FieldSubScreen_Init_Union(FIELDSYS_WORK * fsys);
static void FieldSubScreen_Quit_Normal(FIELDSYS_WORK * fsys);
static void FieldSubScreen_Quit_Under(FIELDSYS_WORK * fsys);
static void FieldSubScreen_Quit_Union(FIELDSYS_WORK * fsys);
static BOOL FieldSubScreen_WaitQuit_Normal(FIELDSYS_WORK * fsys);
static BOOL FieldSubScreen_WaitQuit_Under(FIELDSYS_WORK * fsys);
static BOOL FieldSubScreen_WaitQuit_Union(FIELDSYS_WORK * fsys);

//------------------------------------------------------------------
/**
 * @brief	サブ画面制御用関数郡
 *
 * サブ画面に関する初期化処理や終了処理をまとめたもの。
 * ここにまとめることでフィールドマップ本体から詳細処理を
 * 分離している。
 */
//------------------------------------------------------------------
static const SUBSCRN_FUNCLIST SubScreenFuncList[] = {
	{	///通常フィールド用定義
		FieldSubScreen_Init_Normal,			// 初期化
		NULL,								// 初期化処理終了待ち
		FieldSubScreen_Quit_Normal,			// 終了処理リクエスト
		FieldSubScreen_WaitQuit_Normal,		// 終了処理待ち
	},
	{	///炭鉱用定義
		FieldSubScreen_Init_Under,
		NULL,
		FieldSubScreen_Quit_Under,
		FieldSubScreen_WaitQuit_Under,
	},

	{	/// ユニオンルーム用定義
		FieldSubScreen_Init_Union,			// 初期化
		NULL,								// 初期化処理終了待ち
		FieldSubScreen_Quit_Union,			// 終了処理リクエスト
		FieldSubScreen_WaitQuit_Union,	// 終了処理待ち
	
	},
	{
		FieldBeforePoketch_Init,			// 初期化
		NULL,								// 初期化処理終了待ち
		FieldBeforePoketch_QuitReq,			// 終了処理リクエスト
		FieldBeforePoketch_QuitWait,		// 終了処理待ち
	},
};

//============================================================================================
//============================================================================================
//------------------------------------------------------------------
//------------------------------------------------------------------
static int GetType(FIELDSYS_WORK * fsys)
{
	FIELD_SUBSCRN_TYPE type = fsys->subscreen;
	GF_ASSERT(type != 0);
	GF_ASSERT(type < FIELD_SUBSCRN_MAX);
	return type - 1;
}

//============================================================================================
//
//
//		フィールドマップから呼ばれるサブ画面処理関数
//
//
//============================================================================================
//------------------------------------------------------------------
/**
 * @brief	サブ画面処理：初期化リクエスト
 * @param	fsys	ゲームシステムへのポインタ
 */
//------------------------------------------------------------------
void FieldSubScreen_Init(FIELDSYS_WORK * fsys)
{
	SubScreenFuncList[GetType(fsys)].set_init(fsys);
}

//------------------------------------------------------------------
/**
 * @brief	サブ画面処理：初期化待ち
 * @param	fsys	ゲームシステムへのポインタ
 * @return	BOOL	TRUEのとき、処理終了
 */
//------------------------------------------------------------------
BOOL FieldSubScreen_WaitInit(FIELDSYS_WORK * fsys)
{
	BOOL (*func)(FIELDSYS_WORK *);
	func = SubScreenFuncList[GetType(fsys)].wait_init;
	if (func == NULL) {
		return TRUE;
	}
	return func(fsys);
}

//------------------------------------------------------------------
/**
 * @brief	サブ画面処理：終了リクエスト
 * @param	fsys	ゲームシステムへのポインタ
 */
//------------------------------------------------------------------
void FieldSubScreen_Quit(FIELDSYS_WORK * fsys)
{
	SubScreenFuncList[GetType(fsys)].set_quit(fsys);
}

//------------------------------------------------------------------
/**
 * @brief	サブ画面処理：終了待ち
 * @param	fsys	ゲームシステムへのポインタ
 * @return	BOOL	TRUEのとき、処理終了
 */
//------------------------------------------------------------------
BOOL FieldSubScreen_WaitQuit(FIELDSYS_WORK * fsys)
{
	return SubScreenFuncList[GetType(fsys)].wait_quit(fsys);
}


//============================================================================================
//
//
//		サブ画面ごとの個別関数
//
//
//============================================================================================
//------------------------------------------------------------------
/**
 * @brief	サブ画面処理：初期化リクエスト：通常フィールド用
 * @param	fsys	ゲームシステムへのポインタ
 */
//------------------------------------------------------------------
static void FieldSubScreen_Init_Normal(FIELDSYS_WORK * fsys)
{
	FieldPoketch_Init(fsys);
}

//------------------------------------------------------------------
/**
 * @brief	サブ画面処理：初期化リクエスト：炭鉱用
 * @param	fsys	ゲームシステムへのポインタ
 */
//------------------------------------------------------------------
static void FieldSubScreen_Init_Under(FIELDSYS_WORK * fsys)
{
	CommStateFieldUnderOptionReboot();  // 地下用通信のオプションを復帰
}

//------------------------------------------------------------------
/**
 * @brief	サブ画面処理：初期化リクエスト：ユニオンルーム用用
 * @param	fsys	ゲームシステムへのポインタ
 */
//------------------------------------------------------------------
static void FieldSubScreen_Init_Union(FIELDSYS_WORK * fsys)
{

	Overlay_Load( FS_OVERLAY_ID( unionroom_board ), OVERLAY_LOAD_NOT_SYNCHRONIZE );
	fsys->union_board = UnionRoom_BoardInit( fsys );
}

//------------------------------------------------------------------
/**
 * @brief	サブ画面処理：終了リクエスト：通常フィールド用
 * @param	fsys	ゲームシステムへのポインタ
 */
//------------------------------------------------------------------
static void FieldSubScreen_Quit_Normal(FIELDSYS_WORK * fsys)
{
	FieldPoketch_QuitReq( fsys );
}

//------------------------------------------------------------------
/**
 * @brief	サブ画面処理：終了リクエスト：炭坑用
 * @param	fsys	ゲームシステムへのポインタ
 */
//------------------------------------------------------------------
static void FieldSubScreen_Quit_Under(FIELDSYS_WORK * fsys)
{
	CommStateFieldUnderOptionReset();  // 地下用通信のオプションを破棄
}

//------------------------------------------------------------------
/**
 * @brief	サブ画面処理：終了リクエスト：炭坑用
 * @param	fsys	ゲームシステムへのポインタ
 */
//------------------------------------------------------------------
static void FieldSubScreen_Quit_Union(FIELDSYS_WORK * fsys)
{
	UnionRoom_BoardEnd( fsys->union_board );
	Overlay_UnloadID( FS_OVERLAY_ID( unionroom_board ) );

}

//------------------------------------------------------------------
/**
 * @brief	サブ画面処理：終了待ち：通常フィールド用
 * @param	fsys	ゲームシステムへのポインタ
 * @return	BOOL	TRUEのとき、処理終了
 */
//------------------------------------------------------------------
static BOOL FieldSubScreen_WaitQuit_Normal(FIELDSYS_WORK * fsys)
{
	return FieldPoketch_QuitWait( fsys );
}

//------------------------------------------------------------------
/**
 * @brief	サブ画面処理：終了待ち：ユニオン用
 * @param	fsys	ゲームシステムへのポインタ
 * @return	BOOL	TRUEのとき、処理終了
 */
//------------------------------------------------------------------
static BOOL FieldSubScreen_WaitQuit_Union(FIELDSYS_WORK * fsys)
{
	return TRUE;
}

//------------------------------------------------------------------
/**
 * @brief	サブ画面処理：終了待ち：炭鉱用
 * @param	fsys	ゲームシステムへのポインタ
 * @return	BOOL	TRUEのとき、処理終了
 */
//------------------------------------------------------------------
static BOOL FieldSubScreen_WaitQuit_Under(FIELDSYS_WORK * fsys)
{
	//終了条件梨、無条件でTRUEを返す
	return TRUE;
}

