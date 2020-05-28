//============================================================================================
/**
 * @file	script.h
 * @bfief	スクリプト制御メイン部分
 * @author	Satoshi Nohara
 * @date	05.08.04
 *
 * 01.03.28	Sousuke Tamada
 * 03.04.15	Satoshi Nohara
 * 05.04.25 Hiroyuki Nakamura
 */
//============================================================================================
#ifndef SCRIPT_H
#define SCRIPT_H

#include "field_common.h"
#include "field_event.h"
#include "vm.h"					//VM_CMD
#include "script_def.h"			//特殊スクリプト定義


//==============================================================================================
//
//	スクリプト制御ワークへの不完全型ポインタ
//
//==============================================================================================
typedef	struct _EV_SCRIPT_WORK EV_SCRIPT_WORK;


//============================================================================================
//	定義
//============================================================================================
//EV_SCRIPT_WORKのメンバーID定義
enum{
	ID_EVSCR_EVWIN = 0,				//イベントウィンドウワークのポインタ

	ID_EVSCR_MSGWINDAT,				//会話ウィンドウビットマップデータ
	ID_EVSCR_MENUWORK,				//ビットマップメニューワークのポインタ

	ID_EVSCR_MSGINDEX,				//会話ウィンドウメッセージインデックス
	ID_EVSCR_ANMCOUNT,				//アニメーションの数
	ID_EVSCR_COMMON_SCR_FLAG,		//共通スクリプト切り替えフラグ
	ID_EVSCR_WIN_OPEN_FLAG,			//会話ウィンドウを開いたかフラグ
	ID_EVSCR_VM_MACHINE_COUNT,		//追加した仮想マシンの数

	ID_EVSCR_SCRIPT_ID,				//メインのスクリプトID

	ID_EVSCR_PLAYER_DIR,			//イベント起動時の主人公の向き
	ID_EVSCR_TARGET_OBJ,			//話しかけ対象のOBJのポインタ
	ID_EVSCR_DUMMY_OBJ,				//透明ダミーのOBJのポインタ
	ID_EVSCR_RETURN_SCRIPT_WK,		//イベント結果を代入するワークのポインタ

	ID_EVSCR_VM_MAIN,				//VMのポインタ
	ID_EVSCR_VM_SUB1,				//VMのポインタ

	ID_EVSCR_WORDSET,				//単語セット
	ID_EVSCR_MSGBUF,				//メッセージバッファのポインタ
	ID_EVSCR_TMPBUF,				//テンポラリバッファのポインタ
	ID_EVSCR_WAITICON,				///<待機アイコンのポインタ

	ID_EVSCR_SUBPROC_WORK,			//サブプロセスのパラメータ
	ID_EVSCR_PWORK,					//ワークへの汎用ポインタ
	ID_EVSCR_EOA,					//フィールドエフェクトへのポインタ
	ID_EVSCR_PLAYER_TCB,			//自機形態TCBのポインタ

	ID_EVSCR_WIN_FLAG,

	ID_EVSCR_TR0_RANGE,				//視線
	ID_EVSCR_TR0_DIR,
	ID_EVSCR_TR0_SCR_ID,
	ID_EVSCR_TR0_ID,
	ID_EVSCR_TR0_TYPE,
	ID_EVSCR_TR0_FLDOBJ,
	ID_EVSCR_TR0_TCB,

	ID_EVSCR_TR1_RANGE,
	ID_EVSCR_TR1_DIR,
	ID_EVSCR_TR1_SCR_ID,
	ID_EVSCR_TR1_ID,
	ID_EVSCR_TR1_TYPE,
	ID_EVSCR_TR1_FLDOBJ,
	ID_EVSCR_TR1_TCB,

	//コインウインドウ
	ID_EVSCR_COINWINDAT,

	//お金ウインドウ
	ID_EVSCR_GOLDWINDAT,

	ID_EVSCR_REPORTWIN,		///<レポート情報ウィンドウ

	//スクリプトとプログラムのデータ交換用
	ID_EVSCR_WK_START,				//ワークの開始ID
	ID_EVSCR_WK_PARAM0 = ID_EVSCR_WK_START,				
	ID_EVSCR_WK_PARAM1,
	ID_EVSCR_WK_PARAM2,
	ID_EVSCR_WK_PARAM3,

	//スクリプトでのテンポラリ
	ID_EVSCR_WK_TEMP0,					
	ID_EVSCR_WK_TEMP1,
	ID_EVSCR_WK_TEMP2,
	ID_EVSCR_WK_TEMP3,

	//スクリプト内部での処理用
	ID_EVSCR_WK_REG0,					
	ID_EVSCR_WK_REG1,
	ID_EVSCR_WK_REG2,
	ID_EVSCR_WK_REG3,

	//スクリプトに答えを返す汎用ワーク
	ID_EVSCR_WK_ANSWER,

	//話しかけ対象のOBJID(変更不可！)
	ID_EVSCR_WK_TARGET_OBJID,

	//ここはワークの数に影響するので注意！

/*
	//手持ちがいっぱいでパソコンに転送された時
	u16 BoxNoWork = 0;			//何番のBOXか
	u16 PasoNoWork = 0;			//そのBOXの何番目か

	//ユニオンルームでのイベント状態制御用ワーク
	u16 UnionRoomWork = 0;
*/

	ID_EVSCR_WK_END,				//ワークの終了ID
};
#define EVSCR_WORK_MAX	( ID_EVSCR_WK_END - ID_EVSCR_WK_START )	//ワークの数

//仮想マシンのナンバー
enum{
	VM_MACHINE_MAIN = 0,			//メイン
	VM_MACHINE_SUB1,				//サブ

	VM_MACHINE_MAX,					//最大数
};

//隠しアイテムリスト(ポケッチ用)
typedef struct {
	u16 gx, gz;
	u8 response;	//反応
}HIDE_ITEM_LIST;

#define HIDE_LIST_SX				(7)		//検索範囲
#define HIDE_LIST_SZ				(7)		//検索範囲(未使用)
#define HIDE_LIST_SZ_2				(6)		//検索範囲(未使用)
#define HIDE_LIST_TOP				(7)		//検索範囲(主人公から画面上)
#define HIDE_LIST_BOTTOM			(6)		//検索範囲(主人公から画面下)
#define HIDE_LIST_RESPONSE_NONE		(0xff)	//終了コード


//============================================================================================
//	グローバル変数
//============================================================================================
//extern const VM_CODE * ReserveScript;


//============================================================================================
//	プロトタイプ宣言
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * スクリプトイベントセット
 *
 * @param	fsys		FIELDSYS_WORK型のポインタ
 * @param	scr_id		スクリプトID
 * @param	obj			話しかけ対象OBJのポインタ(ない時はNULL)
 *
 * @retval	none
 */
//--------------------------------------------------------------------------------------------
extern void EventSet_Script( FIELDSYS_WORK * fsys, u16 scr_id, FIELD_OBJ_PTR obj );

//----------------------------------------------------------------------------------------------
/**
 * トレーナー視線情報を格納　事前にEventSet_Script()を起動しておく事
 *
 * @param	fsys		FIELDSYS_WORK型のポインタ
 * @param	fldobj		視線がヒットしたFIELD_OBJ_PTR
 * @param	range		グリッド単位の視線距離
 * @param	dir			移動方向
 * @param	scr_id		視線ヒットしたスクリプトID
 * @param	tr_id		視線ヒットしたトレーナーID
 * @param	tr_type		トレーナータイプ　シングル、ダブル、タッグ識別
 * @param	tr_no		何番目にヒットしたトレーナーなのか
 */
//----------------------------------------------------------------------------------------------
extern void EventSet_TrainerEyeData(
		FIELDSYS_WORK* fsys, FIELD_OBJ_PTR fldobj,
		int range, int dir, int scr_id, int tr_id, int tr_type, int tr_no );

//--------------------------------------------------------------------------------------------
/**
 * スクリプトイベントコール
 *
 * @param	event		GMEVENT_CONTROL型のポインタ
 * @param	scr_id		スクリプトID
 * @param	obj			話しかけ対象OBJのポインタ(ない時はNULL)
 * @param	ret_script_wk	スクリプト結果を代入するワークのポインタ
 *
 * @retval	none
 */
//--------------------------------------------------------------------------------------------
extern void EventCall_Script( GMEVENT_CONTROL* event, u16 scr_id, FIELD_OBJ_PTR obj, void* ret_script_wk );

//--------------------------------------------------------------------------------------------
/**
 * スクリプトイベント切替
 *
 * @param	event		GMEVENT_CONTROL型のポインタ
 * @param	scr_id		スクリプトID
 * @param	obj			話しかけ対象OBJのポインタ(ない時はNULL)
 *
 * @retval	none
 *
 * 他のイベントからスクリプトへの切替を行う
 */
//--------------------------------------------------------------------------------------------
extern void EventChange_Script(GMEVENT_CONTROL* event, u16 scr_id, FIELD_OBJ_PTR obj);

//--------------------------------------------------------------
/**
 * @brief	仮想マシン追加
 *
 * @param	fsys		FIELDSYS_WORK型のポインタ
 * @param	scr_id		スクリプトID
 * @param	start		命令テーブル開始アドレス
 * @param	end			命令テーブル終了アドレス
 *
 * @retval	none
 */
//--------------------------------------------------------------
extern VM_MACHINE* VMMachineAddTCB(FIELDSYS_WORK* fsys, u16 scr_id, const VM_CMD* start, const VM_CMD* end);

//extern VM_MACHINE* VMMachineAdd(FIELDSYS_WORK* fsys, u16 scr_id, const VM_CMD* start, const VM_CMD* end);
extern VM_MACHINE* VMMachineAdd(FIELDSYS_WORK* fsys, u16 scr_id);


//============================================================================================
//
//	スクリプト制御ワークのメンバーアクセス
//
//============================================================================================

//--------------------------------------------------------------
/**
 * @brief	プログラムからスクリプトへパラメータを渡す
 * @param	fsys	FIELDSYS_WORK型のポインタ
 * @param	prm0	パラメータ０（SCWK_PARAM0）
 * @param	prm1	パラメータ１（SCWK_PARAM1）
 * @param	prm2	パラメータ２（SCWK_PARAM2）
 * @param	prm3	パラメータ３（SCWK_PARAM3）
 *
 * GetEvScriptWorkMemberAdrs_Subを使用してもよいが、内部構造が
 * 剥き出しになっているので４つのパラメータのみ専用関数を用意した
 */
//--------------------------------------------------------------
extern void EvScript_SetParam(FIELDSYS_WORK * fsys, u16 prm0, u16 prm1, u16 prm2, u16 prm3);

//--------------------------------------------------------------------------------------------
/**
 * スクリプト制御ワークのメンバーアドレス取得
 *
 * @param	sc		EV_SCRIPT_WORK型のポインタ
 * @param	id		取得するメンバID(script.h参照)
 *
 * @return	"アドレス"
 */
//--------------------------------------------------------------------------------------------
extern void* GetEvScriptWorkMemberAdrs_Sub( EV_SCRIPT_WORK* sc, u32 id );

//--------------------------------------------------------------------------------------------
/**
 * スクリプト制御ワークのメンバーアドレス取得
 *
 * @param	fsys	FIELDSYS_WORK型のポインタ
 * @param	id		取得するメンバID(script.h参照)
 *
 * @return	"アドレス"
 */
//--------------------------------------------------------------------------------------------
extern void* GetEvScriptWorkMemberAdrs( FIELDSYS_WORK* fsys, u32 id );

//--------------------------------------------------------------------------------------------
/**
 * スクリプト制御ワークの"next_func"にメニュー呼び出しをセット
 *
 * @param	fsys	FIELDSYS_WORK型のポインタ
 *
 * @return	none
 *
 * フィールドメニュー呼び出し限定！
 *
 * 流れが把握しずらくなるので、汎用的に使えないようにしている！
 */
//--------------------------------------------------------------------------------------------
extern void SetEvScriptNextFunc( FIELDSYS_WORK* fsys );


//============================================================================================
//
//	
//
//============================================================================================

//------------------------------------------------------------------
/**
 * @brief	イベントワークアドレスを取得
 *
 * @param	fsys		FIELDSYS_WORKへのポインタ
 * @param	work_no		ワークナンバー
 *
 * @return	"ワークのアドレス"
 *
 * @li	work_no < 0x8000	通常のセーブワーク
 * @li	work_no >= 0x8000	スクリプト制御ワークの中に確保しているワーク
 */
//------------------------------------------------------------------
extern u16 * GetEventWorkAdrs( FIELDSYS_WORK* fsys, u16 work_no );

//------------------------------------------------------------------
/**
 * @brief	イベントワークの値を取得
 *
 * @param	fsys		FIELDSYS_WORKへのポインタ
 * @param	work_no		ワークナンバー
 *
 * @return	"ワークの値"
 */
//------------------------------------------------------------------
extern u16 GetEventWorkValue( FIELDSYS_WORK* fsys, u16 work_no );

//------------------------------------------------------------------
/**
 * @brief	イベントワークの値をセット
 *
 * @param	fsys		FIELDSYS_WORKへのポインタ
 * @param	work_no		ワークナンバー
 * @param	value		セットする値
 *
 * @return	"TRUE=セット出来た、FALSE=セット出来なかった"
 */
//------------------------------------------------------------------
extern BOOL SetEventWorkValue( FIELDSYS_WORK* fsys, u16 work_no, u16 value );

//------------------------------------------------------------------
/**
 * @brief	スクリプトから指定するOBJコードを取得
 *
 * @param	fsys		FIELDSYS_WORKへのポインタ
 * @param	no			0-15
 *
 * @return	"OBJキャラコード"
 */
//------------------------------------------------------------------
extern u16 GetEvDefineObjCode( FIELDSYS_WORK* fsys, u16 no );

//------------------------------------------------------------------
/**
 * @brief	スクリプトから指定するOBJコードをセット
 *
 * @param	fsys		FIELDSYS_WORKへのポインタ
 * @param	no			0-15
 * @param	obj_code	OBJコード
 *
 * @return	"TRUE=セット出来た、FALSE=セット出来なかった"
 */
//------------------------------------------------------------------
extern BOOL SetEvDefineObjCode( FIELDSYS_WORK* fsys, u16 no, u16 obj_code );


//============================================================================================
//
//	フラグ関連
//
//============================================================================================

//------------------------------------------------------------------
/**
 * @brief	イベントフラグをチェックする
 *
 * @param	fsys		FIELDSYS_WORKのポインタ
 * @param	flag_no		フラグナンバー
 *
 * @retval	"1 = フラグON"
 * @retval	"0 = フラグOFF"
 */
//------------------------------------------------------------------
extern BOOL CheckEventFlag( FIELDSYS_WORK* fsys, u16 flag_no);

//------------------------------------------------------------------
/**
 * @brief	イベントフラグをセットする
 *
 * @param	fsys		FIELDSYS_WORKのポインタ
 * @param	flag_no		フラグナンバー
 *
 * @return	none
 */
//------------------------------------------------------------------
extern void SetEventFlag( FIELDSYS_WORK* fsys, u16 flag_no);

//------------------------------------------------------------------
/**
 * @brief	イベントフラグをリセットする
 *
 * @param	fsys		FIELDSYS_WORKのポインタ
 * @param	flag_no		フラグナンバー
 *
 * @return	none
 */
//------------------------------------------------------------------
extern void ResetEventFlag( FIELDSYS_WORK* fsys, u16 flag_no);

//------------------------------------------------------------------
/**
 * @brief	マップ内限定のセーブフラグをクリアする
 *
 * @param	fsys		FIELDSYS_WORKのポインタ
 *
 * @return	none
 */
//------------------------------------------------------------------
extern void LocalEventFlagClear( FIELDSYS_WORK* fsys );

//------------------------------------------------------------------
/**
 * @brief	1日経過ごとにクリアされるフラグをクリアする
 *
 * @param	fsys		FIELDSYS_WORKのポインタ
 *
 * @return	none
 */
//------------------------------------------------------------------
extern void TimeEventFlagClear( FIELDSYS_WORK* fsys );


//============================================================================================
//
//	トレーナーフラグ関連
//
//	・スクリプトIDから、トレーナーIDを取得して、フラグチェック
//	BOOL CheckEventFlagTrainer( fsys, GetTrainerIdByScriptId(scr_id) );
//
//============================================================================================

//--------------------------------------------------------------
/**
 * スクリプトIDから、トレーナーIDを取得
 *
 * @param   scr_id		スクリプトID
 *
 * @retval  "トレーナーID = フラグインデックス"
 */
//--------------------------------------------------------------
extern u16 GetTrainerIdByScriptId( u16 scr_id );

//--------------------------------------------------------------
/**
 * スクリプトIDから、左右どちらのトレーナーか取得
 *
 * @param   scr_id		スクリプトID
 *
 * @retval  "0=左、1=右"
 */
//--------------------------------------------------------------
extern BOOL GetTrainerLRByScriptId( u16 scr_id );

//--------------------------------------------------------------
/**
 * トレーナーIDから、ダブルバトルタイプか取得
 *
 * @param   tr_id		トレーナーID
 *
 * @retval  "0=シングルバトル、1=ダブルバトル"
 */
//--------------------------------------------------------------
extern BOOL CheckTrainer2vs2Type( u16 tr_id );

//------------------------------------------------------------------
/**
 * @brief	トレーナーイベントフラグをチェックする
 *
 * @param	fsys		FIELDSYS_WORKのポインタ
 * @param	tr_id		トレーナーID
 *
 * @retval	"1 = フラグON"
 * @retval	"0 = フラグOFF"
 */
//------------------------------------------------------------------
extern BOOL CheckEventFlagTrainer( FIELDSYS_WORK* fsys, u16 tr_id );

//------------------------------------------------------------------
/**
 * @brief	トレーナーイベントフラグをセットする
 *
 * @param	fsys		FIELDSYS_WORKのポインタ
 * @param	tr_id		トレーナーID
 *
 * @return	none
 */
//------------------------------------------------------------------
extern void SetEventFlagTrainer( FIELDSYS_WORK* fsys, u16 tr_id );

//------------------------------------------------------------------
/**
 * @brief	トレーナーイベントフラグをリセットする
 *
 * @param	fsys		FIELDSYS_WORKのポインタ
 * @param	tr_id		トレーナーID
 *
 * @return	none
 */
//------------------------------------------------------------------
extern void ResetEventFlagTrainer( FIELDSYS_WORK* fsys, u16 tr_id );


//============================================================================================
//
//	隠しアイテム関連
//
//	・スクリプトIDから、隠しアイテムフラグを取得して、フラグチェック
//	BOOL CheckEventFlag( fsys, GetHideItemFlagNoByScriptId(scr_id) );
//
//============================================================================================

//--------------------------------------------------------------
/**
 * スクリプトIDから、隠しアイテムフラグナンバーを取得
 *
 * @param   scr_id		スクリプトID
 *
 * @retval  "フラグナンバー"
 */
//--------------------------------------------------------------
extern u16 GetHideItemFlagNoByScriptId( u16 scr_id );

//--------------------------------------------------------------
/**
 * スクリプトIDから、隠しアイテムフラグインデックスを取得
 *
 * @param   scr_id		スクリプトID
 *
 * @retval  "フラグインデックス"
 */
//--------------------------------------------------------------
extern u16 GetHideItemFlagIndexByScriptId( u16 scr_id );

//--------------------------------------------------------------
/**
 * スクリプトIDから、隠しアイテムの反応を取得
 *
 * @param   scr_id		スクリプトID
 *
 * @retval  "反応"
 *
 * 隠しアイテムのスクリプトを見つけたら呼ぶようにする！
 */
//--------------------------------------------------------------
extern u8 GetHideItemResponseByScriptId( u16 scr_id );

//--------------------------------------------------------------
/**
 * 画面内にある隠しアイテムを検索して確保したリストに登録
 *
 * @param   fsys		FIELDSYS_WORK型のポインタ
 * @param   heapid		ヒープID
 *
 * @retval  "リストのアドレス"
 *
 * 解放処理を忘れずに！
 */
//--------------------------------------------------------------
extern HIDE_ITEM_LIST* HideItem_CreateList( FIELDSYS_WORK * fsys, int heapid );

//------------------------------------------------------------------
/**
 * @brief	ゲーム開始 スクリプト初期設定の実行
 *
 * @param	fsys		FIELDSYS_WORK型のポインタ
 *
 * @return	none
 */
//------------------------------------------------------------------
extern void GameStartScriptInit( FIELDSYS_WORK* fsys );

//------------------------------------------------------------------
/**
 * @brief	EVENTではなく特殊スクリプト実行
 *
 * @param	fsys		FIELDSYS_WORK型のポインタ
 * @param	scr_id		スクリプトID
 *
 * @return	none
 *
 * 注意！
 * EV_SCRIPT_WORKを確保していないので、
 * SCWK_ANSWERなどのワークは使用することが出来ない！
 * LOCALWORK0などを使用するようにする！
 *
 * 共通スクリプトについては現状使用不可！
 * 対応予定だが、ゾーンをまたいだ時に処理落ちするかも？
 * あまりつかわないかも？
 *
 * フラグチェンジラベルで共通スクリプトを使いたいときは、
 * 二つフラグチェンジラベルを書くことになるかも？
 * 片方は、ゾーンでことたりるもの、片方は、共通スクリプトのIDを指定？。。。
 */
//------------------------------------------------------------------
extern void SpScriptStart( FIELDSYS_WORK* fsys, u16 scr_id );

//------------------------------------------------------------------
/**
 * @brief	特殊スクリプト検索して実行
 *
 * @param	fsys		FIELDSYS_WORK型のポインタ
 * @param	key			特殊スクリプトID
 *
 * @return	"TRUE=特殊スクリプト実行、FALSE=何もしない"
 */
//------------------------------------------------------------------
extern BOOL SpScriptSearch( FIELDSYS_WORK* fsys, u8 key );



/***************/
/***************/
/***************/
/***************/
/***************/
/***************/
/***************/


extern void InitControlScriptCheck( void * p );

extern u16 * GetEventWorkAdrs( FIELDSYS_WORK* fsys, u16 work_no );
extern u16 GetEventWorkValue( FIELDSYS_WORK* fsys, u16 work_no );


#endif	/* SCRIPT_H */


