//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		imc_left_box.c
 *	@brief		左ボックスシステム
 *	@author		tomoya takahashi
 *	@data		2005.09.23
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]



#include <string.h>
#include "system.h"
#include "assert.h"
#include "calctool.h"
#include "tcb.h"
#include "include/system/lib_pack.h"
#include "include/application/imageClip/imc_drawdata_define.h"
#include "include/system/heapdefine.h"
#include "include/application/imageClip/imc_obj_list_func.h"

#define __IMC_LEFT_BOX_H_GLOBAL
#include "include/application/imageClip/imc_left_box.h"

//-----------------------------------------------------------------------------
/**
 *					定数宣言
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	
//	サムネイルデータ配置座標定数
//	
//=====================================
#define IMC_LBOX_THUMB_SIZE_X	(24)		// サムネイルサイズ
#define IMC_LBOX_THUMB_SIZE_Y	(32)		// サムネイルサイズ
#define IMC_LBOX_MAT_SPACE_X	(8)			// 配置するときのスペース
#define IMC_LBOX_MAT_SPACE_Y	(8)			// 配置するときのスペース

#define IMC_LBOX_MAT_LINE_NUM	(3)			// １ラインに何サムネイルおくか


//-----------------------------------------------------------------------------
/**
*		パレット変更　実験データ
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	
//	シーケンス
//	
//=====================================
enum{
	IMC_LBOX_PLTT_CHG_INIT,		// 初期化
	IMC_LBOX_PLTT_CHG_OUT_ACCE_S,// アクセサリ退場開始
	IMC_LBOX_PLTT_CHG_IN_ACCE_S,	// アクセサリ入場開始
	IMC_LBOX_PLTT_CHG_WAIT,		// 各アクセサリフェード終了待ち
	IMC_LBOX_PLTT_CHG_END,		// 終了
};

#define IMC_LBOX_PLTT_CHG_MOVE_Y	(132)		// 移動値
#define IMC_LBOX_PLTT_CHG_COUNT	(3)			// 移動回数
#define IMC_LBOX_PLTT_CHG_ADD	(IMC_LBOX_PLTT_CHG_MOVE_Y / IMC_LBOX_PLTT_CHG_COUNT)		// １回の移動数
#define IMC_LBOX_PLTT_CHG_OBJ_S_NUM	(2)		// フェードインオブジェクトの数を何分割するか
#define IMC_LBOX_PLTT_CHG_OBJ_E_NUM	(1)		// フェードアウトオブジェクトの数を何分割するか
#define IMC_LBOX_PLTT_BG_SYNC	(5)		// BGを何シンクで動かすか


//-----------------------------------------------------------------------------
/**
 *					構造体宣言
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	
//	パレットフェード個々のオブジェクト移動
//	構造体
//	
//=====================================
typedef struct {
	IMC_OBJLIST* obj;
	
	int count;
	int add_y;
} IMC_LBOX_PLTT_OBJ_MOVE;

//-------------------------------------
//	
//	パレットフェードタスク
//	
//=====================================
typedef struct {
	IMC_LEFT_BOX* lbox;	// 左ボックス

	int out_mode;		// フェードアウトするリストmode
	int out_list;		// フェードアウトするリストno
	int in_mode;		// フェードインするリストmode
	int in_list;		// フェードインするリストno
	BOOL bg_fade;		// BGフェード終了チェック
	int count;			// 汎用カウンタ

	int seq;			// シーケンス	
	int out_count;		// カウンタ
	int in_count;		// カウンタ

	IMC_LBOX_PLTT_OBJ_MOVE* move_obj;	// オブジェ移動データ
	// ↑テーブル数＝out_obj_count + in_obj_count
	int move_obj_num;		// テーブル数
} IMC_LBOX_PLTT_TASK;



//-----------------------------------------------------------------------------
/**
 *					プロトタイプ宣言
*/
//-----------------------------------------------------------------------------
static void makeAcceList( IMC_LEFT_BOX* lbox, IMC_LEFT_BOX_INIT* init );
static void drawSetList( IMC_OBJLIST* dummy, int flag );
static void listDataMake( IMC_LEFT_LIST_DATA* list, int dummy_num );
static void listDataDest( IMC_LEFT_LIST_DATA* list );
static IMC_OBJLIST* getCurrentDummy( IMC_LEFT_BOX* lbox );
static IMC_OBJLIST* getDummyTbl( IMC_LEFT_BOX* lbox, int mode, int tbl_no );
static int getListSetDataNum( IMC_LEFT_BOX* lbox, int mode, int tbl_no );
static IMC_OBJLIST* getNoListObjData( IMC_LEFT_BOX* lbox, int mode, int tbl_no, int no );
static void drawFlgCurrentDummy( IMC_LEFT_BOX* lbox, int flag );
static void drawFlgSetCheck( IMC_LEFT_BOX* lbox, IMC_ACCESSORIE_OBJ* acce_obj, int mode, int list_num );
static void getBgSndThumbMat( int no, int* x, int* y );

static void plttChgTaskStart( IMC_LEFT_BOX* lbox, int out_mode, int out_list, int in_mode, int in_list );
static void plttChgTask( TCB_PTR tcb, void* work );
static void startPlttChgObj( IMC_OBJLIST* obj, IMC_LBOX_PLTT_OBJ_MOVE* data, int num );
static IMC_LBOX_PLTT_OBJ_MOVE* getCleanPlttChgObj( IMC_LBOX_PLTT_OBJ_MOVE* data, int num );
static void movePlttChgObj( IMC_LBOX_PLTT_OBJ_MOVE* data, int num );
static void movePlttChgObjCore( IMC_LBOX_PLTT_OBJ_MOVE* data );

static int movePlttChgGetObjAddNum( int obj_num, int div );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	左ボックス用領域作成
 *
 *	@param	lbox		左ボックス用データ
 *	@param	init		左ボックス初期化データ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_LBOX_InitSys( IMC_LEFT_BOX* lbox, IMC_LEFT_BOX_INIT* init )
{
	// 描画データ設定
	lbox->boxDraw.SWSP_drawSys		= init->SWSP_drawSys;
	lbox->boxDraw.SWSP_charData		= init->SWSP_charData;
	lbox->boxDraw.SWSP_plttData		= init->SWSP_plttData;
	lbox->boxDraw.accePlttOfsTbl	= init->accePlttOfsTbl;
	lbox->boxDraw.BG_Ini			= init->BG_Ini;
	lbox->boxDraw.acce		= init->acce;
	
	// オブジェクトリストテーブル
	lbox->boxData.objListTbl = init->objListTbl;
	lbox->boxData.p_item_buff = init->p_item_buff;

	// 背景ナンバ
	IMC_LBOX_BGSet( lbox, 0 );
	
	// アクセサリリスト作成
	makeAcceList( lbox, init );

}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	左ボック用領域破棄
 *
 *	@param	lbox		破棄する左ボックスデータ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_LBOX_DeleteSys( IMC_LEFT_BOX* lbox )
{
	int i;
	
	IMC_LBOX_DeleteAccessorieAll( lbox );

	for( i=0; i<IMC_LBOX_LIST_NUM; i++ ){
		listDataDest( &lbox->boxData.acce_list[ i ] );
	}
	
	memset( lbox, 0, sizeof( IMC_LEFT_BOX ) );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	アクセサリーナンバーからリストナンバーを取得
 *
 *	@param	mode			モード
 *	@param	accessorie_no	アクセサリナンバー
 *
 *	@return	int		アクセサリーリストナンバー
 *
 *
 */
//-----------------------------------------------------------------------------
int IMC_LBOX_GetListNo( int mode, int accessorie_no, IMC_ITEM_BUFF* p_item_buff )
{
	int list_no;
	
	switch(mode){
	case IMC_OBJLIST_ACCE:
		if( accessorie_no <= IMC_LBOX_ACCE_LIST00_END ){
			list_no = 0;
		}else if( accessorie_no <= IMC_LBOX_ACCE_LIST01_END ){
			list_no = 1;
		}else if( accessorie_no <= IMC_LBOX_ACCE_LIST02_END ){
			list_no = 2;
		}else if( accessorie_no <= IMC_LBOX_ACCE_LIST03_END ){
			list_no = 3;
		}else if( accessorie_no <= IMC_LBOX_ACCE_LIST04_END ){
			list_no = 4;
		}else if( accessorie_no <= IMC_LBOX_ACCE_LIST05_END ){
			list_no = 5;
		}else if( accessorie_no <= IMC_LBOX_ACCE_LIST06_END ){
			list_no = 6;
		}else if( accessorie_no <= IMC_LBOX_ACCE_LIST07_END ){
			list_no = 7;
		}else if( accessorie_no <= IMC_LBOX_ACCE_LIST08_END ){
			list_no = 8;
		}else if( accessorie_no <= IMC_LBOX_ACCE_LIST09_END ){
			list_no = 9;
		}else if( accessorie_no <= IMC_LBOX_ACCE_LIST10_END ){
			list_no = 10;
		}else if( accessorie_no <= IMC_LBOX_ACCE_LIST11_END ){
			list_no = 11;
		}else if( accessorie_no <= IMC_LBOX_ACCE_LIST12_END ){
			list_no = 12;
		}else if( accessorie_no <= IMC_LBOX_ACCE_LIST13_END ){
			list_no = 13;
		}
		break;

	case IMC_OBJLIST_BG:
		accessorie_no = IMC_ITEM_BUFF_BgNoTurnGet( p_item_buff, accessorie_no );
		list_no = accessorie_no / IMC_LBOX_BG_ONE_LIST_NUM;
		break;

	case IMC_OBJLIST_SND:
		accessorie_no = IMC_ITEM_BUFF_BgNoTurnGet( p_item_buff, accessorie_no );
		list_no = accessorie_no / IMC_LBOX_SND_ONE_LIST_NUM;
		break;
	}
	
	return list_no;
}


//----------------------------------------------------------------------------
/**
 *
 *	@brief	モードとアクセサリナンバーから登録されておくべき座標を取得
 *
 *	@param	mode			モード
 *	@param	accessorie_no	アクセサリナンバー
 *	@param	x				ｘ座標格納先
 *	@param	y				ｙ座標格納先
 *	@param	size_x			ｘサイズ
 *	@param	size_y			ｙサイズ
 *
 *	@return	none
 *	
 *
 */
//-----------------------------------------------------------------------------
void IMC_LBOX_GetMat( int mode, int accessorie_no, int* x, int* y, int size_x, int size_y, IMC_ITEM_BUFF* p_item_buff )
{
	switch(mode){
	case IMC_OBJLIST_ACCE:
		// アクセサリ初期座標は乱数
		*x = IMC_LBOX_AREA_X_MOVEOK;
		*y = IMC_LBOX_AREA_Y_MOVEOK;
		*x += ( gf_mtRand() % (IMC_LBOX_AREA_WIDTH_MOVEOK - size_x) );
		*y += ( gf_mtRand() % (IMC_LBOX_AREA_HEIGHT_MOVEOK - size_y) );
		break;

	case IMC_OBJLIST_BG:
	case IMC_OBJLIST_SND:
		accessorie_no = IMC_ITEM_BUFF_BgNoTurnGet( p_item_buff, accessorie_no );
		getBgSndThumbMat( accessorie_no, x, y );
		break;
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	アクセサリの新規追加
 *
 *	@param	lbox				左ボックス用データ
 *	@param	list_num			追加するアクセサリリスト数
 *	@param	mode				アクセサリモード
 *	@param	accessorie_no		追加するアクセサリナンバー
 *
 *	@return	none
 *
 * mode
	IMC_OBJLIST_ACCE,		// アクセサリ変更モード
	IMC_OBJLIST_BG,			// BG変更モード
	IMC_OBJLIST_SND,		// サウンド変更モード
	IMC_OBJLIST_ACCE_MAX	// モード最大数
 *
 */
//-----------------------------------------------------------------------------
void IMC_LBOX_AddAccessorie( IMC_LEFT_BOX* lbox, int mode, int accessorie_no )
{
	IMC_ACCE_ADD acce_add;
	IMC_ACCESSORIE_OBJ* acce_obj;
	IMC_OBJLIST* objList;
	int list_num;
	int char_no, pltt_no;
	int set_x, set_y;
	int size_x, size_y;
	
	// アクセサリを登録し、リストに登録
	// アクセサリ登録データ作成
	acce_add.objTbl = lbox->boxDraw.acce;
	acce_add.accessorie_no = accessorie_no;
	acce_add.SWSPsys	= lbox->boxDraw.SWSP_drawSys;
	acce_add.m_x	= 0;
	acce_add.m_y	= 0;

	// mode	にあわせて登録する
	switch( mode ){
	case IMC_OBJLIST_ACCE:
		char_no = IMC_ACCE_CHAR_CONT_ID( accessorie_no );
		pltt_no = IMC_ACCE_PLTT_CONT_ID( accessorie_no );
		acce_add.pltt_offs	= lbox->boxDraw.accePlttOfsTbl[ accessorie_no ];
		break;
	case IMC_OBJLIST_BG:
		char_no = IMC_BG_THUMB_CHAR_CONT_ID( accessorie_no );
		pltt_no = IMC_BG_THUMB_PLTT_CONT_ID( accessorie_no );
		acce_add.pltt_offs = 0;
		break;
	case IMC_OBJLIST_SND:
		char_no = IMC_SND_THUMB_CHAR_CONT_ID( accessorie_no );
		pltt_no = IMC_SND_THUMB_PLTT_CONT_ID( accessorie_no );
		acce_add.pltt_offs = 0;
		break;
	default:
		GF_ASSERT_MSG( 0, "modeが不正な値です" );
		break;
	}
	acce_add.SWSPchar	= lbox->boxDraw.SWSP_charData[ char_no ];
	acce_add.SWSPpltt	= lbox->boxDraw.SWSP_plttData[ pltt_no ];
	GF_ASSERT( acce_add.SWSPchar );
	GF_ASSERT_MSG( acce_add.SWSPpltt, "pltt_no %d", pltt_no );

	// リストナンバー取得
	list_num = IMC_LBOX_GetListNo( mode, accessorie_no, lbox->boxData.p_item_buff );


	// 登録
	acce_obj = IMC_ACCE_ObjAdd( &acce_add );

	// オブジェリストの作成
	objList = IMC_OBJLIST_MakeObjList( lbox->boxData.objListTbl, acce_obj, mode );
	
	// リストの後ろに登録
	IMC_OBJLIST_Set( objList,
					lbox->boxData.acce_list[ mode ].dummyTbl[ list_num ].prev );

	// 座標を設定
	IMC_OBJLIST_ACCEPOKE_SizeGet( objList, &size_x, &size_y );
	IMC_LBOX_GetMat( mode, accessorie_no, &set_x, &set_y, size_x, size_y, lbox->boxData.p_item_buff );
	IMC_OBJLIST_ACCEPOKE_Mat( objList, set_x, set_y );

	// 表示/非表示設定
	drawFlgSetCheck( lbox, acce_obj, mode, list_num );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	アクセサリの移動追加
 *
 *	@param	lbox		左ボックス用データ
 *	@param	acce_obj	アクセサリデータ
 *	@param	mode		アクセサリモード
 *	@param	list_num	登録するリスト
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_LBOX_AddAccessorieMove( IMC_LEFT_BOX* lbox, int mode, int list_num, IMC_OBJLIST* acce_obj )
{
	// リストの先頭に登録
	IMC_OBJLIST_Set(acce_obj, lbox->boxData.acce_list[ mode ].dummyTbl + list_num);


	// 表示/非表示設定
	drawFlgSetCheck( lbox, acce_obj->obj_data, mode, list_num );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	アクセサリオブジェ破棄
 *
 *	@param	acce_obj	破棄するアクセサリ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_LBOX_DeleteAccessorie( IMC_OBJLIST* acce_obj )
{
	// リストから破棄
	IMC_OBJLIST_Delete( acce_obj );
	
	// アクセサリ破棄
	IMC_ACCE_ObjDelete( (IMC_ACCESSORIE_OBJ*)acce_obj->obj_data );

	// リストを破棄
	IMC_OBJLIST_DeleteObjList( acce_obj );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	移動させるためのリストからの削除
 *
 *	@param	acce_obj	移動させるためにリストから削除するアクセサリデータ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_LBOX_DeleteAccessorieMove( IMC_OBJLIST* acce_obj )
{
	// リストから破棄
	IMC_OBJLIST_Delete( acce_obj );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	登録されているアクセサリ全てをはき
 *
 *	@param	lbox	左ボックス
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_LBOX_DeleteAccessorieAll( IMC_LEFT_BOX* lbox )
{
	int i, j;
	
	// リスト破棄
	for( i=0; i<IMC_OBJLIST_ACCE_MAX; i++ ){
		for( j=0; j<lbox->boxData.acce_list[ i ].dummyNum; j++ ){
	
			IMC_OBJLIST_DeleteAll( lbox->boxData.acce_list[ i ].dummyTbl + j );
		}
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	左ボックスアクセサリの表示優先順を設定
 *
 *	@param	lbox	左ブロック
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_LBOX_SetAccessoriePriority( IMC_LEFT_BOX* lbox )
{
	IMC_OBJLIST* work;
	IMC_OBJLIST* dummyTbl;
	BOOL	ret;
	
	int	priority = IMC_LBOX_ACCE_PRIORITY_START;

	dummyTbl = getCurrentDummy( lbox );
	
	work = dummyTbl->next;
	while( work != dummyTbl ){

		if( (work->flag == IMC_OBJLIST_ACCE) ||
			(work->flag == IMC_OBJLIST_BG) ||
			(work->flag == IMC_OBJLIST_SND)){

			IMC_ACCE_ObjDrawPrioritySet( work->obj_data, priority );	
		}

		priority --;
		
		work = work->next;
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	カレントアクセサリリストを変更
 *
 *	@param	lbox			左ボックスデータ
 *	@param	mode			アクセサリモード
 *	@param	list_num		設定するカレントアクセサリリスト
 *
 *	@retval	TRUE			成功
 *	@retval	FALSE			失敗
 *
 * mode
	IMC_OBJLIST_ACCE,		// アクセサリ変更モード
	IMC_OBJLIST_BG,		// BG変更モード
	IMC_OBJLIST_SND,		// サウンド変更モード
	IMC_OBJLIST_ACCE_MAX		// モード最大数
 *
 */
//-----------------------------------------------------------------------------
BOOL IMC_LBOX_ChangeCurrentAccessorie( IMC_LEFT_BOX* lbox, int mode, int list_num )
{
	// 通常状態の時にだけ変更する
	if( lbox->boxData.state == IMC_LBOX_STATE_NORM ){
		
		// パレット変更タスクスタート
		plttChgTaskStart( lbox,
				lbox->boxData.mode, 
				lbox->boxData.acce_list[ lbox->boxData.mode ].dummyCurrent,
				mode,
				list_num );

			
		// 新しいモードとカレントリスト番号を設定
		lbox->boxData.mode		= mode;
		lbox->boxData.acce_list[ mode ].dummyCurrent = list_num;

		// 優先順位の設定
		IMC_LBOX_SetAccessoriePriority( lbox );

		return TRUE;
	}

	return FALSE;
}

//----------------------------------------------------------------------------
/**
 * ●自動でエフェクトを行います。
 *
 *	@brief	カレントアクセサリリストの足し算
 *
 *	@param	lbox			左ボックスデータ
 *	@param	mode			アクセサリモード
 *	@param	add_mode		足すモード
 *
 *	@retval	TRUE			成功
 *	@retval	FALSE			失敗
 *
 * mode
	IMC_OBJLIST_ACCE,		// アクセサリタイプ
	IMC_OBJLIST_BG,			// BGサムネイルタイプ
	IMC_OBJLIST_SND,		// サウンドサムネイルタイプ
	IMC_LBOX_FADELIST_MODE	// フェード時用リスト	list_numは０固定
 */
//-----------------------------------------------------------------------------
BOOL IMC_LBOX_AddCurrentAccessorie( IMC_LEFT_BOX* lbox, int mode, int add_mode )
{
	IMC_OBJLIST* dummy;
	int currentno;
	int work;
	int i;
	int check_list;
	BOOL ret;
	
	// 現在のカレントナンバー
	currentno = IMC_LBOX_GetCurrentNo( lbox, mode );

	// リスト分まわして、どこか、アクセサリが入っているテーブルを探す　今と同じものになったら何もしない
	for( i=1; i<lbox->boxData.acce_list[mode].dummyNum; i++ ){

		if( add_mode == IMC_LBOX_ADD_ONE ){
			check_list = (i + currentno) % lbox->boxData.acce_list[mode].dummyNum;
		}else{
			check_list = currentno - i;
			if( check_list < 0 ){
				check_list += lbox->boxData.acce_list[mode].dummyNum;
			}
		}
		
		// アクセサリが1つでも入っているパレットを選ぶ
		dummy = getDummyTbl( lbox, mode, check_list );
		if( dummy->next != dummy ){

			// リスト設定して抜ける
			ret = IMC_LBOX_ChangeCurrentAccessorie( lbox, mode, check_list );
			return ret; 
		}
	}
	return FALSE;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	カレントアクセサリリストを設定
 *
 *	@param	lbox			左ボックスデータ
 *	@param	mode			アクセサリモード
 *	@param	list_num		設定するカレントアクセサリリスト
 *
 *	@return	none
 *
 * mode
	IMC_OBJLIST_ACCE,		// アクセサリタイプ
	IMC_OBJLIST_BG,			// BGサムネイルタイプ
	IMC_OBJLIST_SND,		// サウンドサムネイルタイプ
	IMC_OBJLIST_ACCE_MAX	// モード最大数
 *
 */
//-----------------------------------------------------------------------------
void IMC_LBOX_SetCurrentAccessorie( IMC_LEFT_BOX* lbox, int mode, int list_num )
{
	// カレントダミーリスト非表示設定
	drawFlgCurrentDummy( lbox, FALSE );
	
	// 新しいモードとカレントリスト番号を設定
	lbox->boxData.mode		= mode;
	lbox->boxData.acce_list[ mode ].dummyCurrent = list_num;

	// カレントダミーリスト表示設定
	drawFlgCurrentDummy( lbox, TRUE );
	
	IMC_LBOX_SetAccessoriePriority( lbox );
}


//----------------------------------------------------------------------------
/**
 *
 *	@brief	タッチパネルが左ボックスに当たってるかチェック
 *
 *	@param	lbox		左ボックスデータ
 *
 *	@retval	TRUE		ヒット
 *	@retval	FALSE		非ヒット
 *
 *
 */
//-----------------------------------------------------------------------------
BOOL IMC_LBOX_TPHit( IMC_LEFT_BOX* lbox )
{
	// 当たり判定矩形データ
	TP_HIT_TBL	tp_hit;
	
	// 当たり判定用データ作成
	tp_hit.rect.top		= IMC_LBOX_AREA_Y_MOVEOK;
	tp_hit.rect.bottom	= IMC_LBOX_AREA_Y_MOVEOK + IMC_LBOX_AREA_HEIGHT_MOVEOK;
	tp_hit.rect.left	= IMC_LBOX_AREA_X_MOVEOK;
	tp_hit.rect.right	= IMC_LBOX_AREA_X_MOVEOK + IMC_LBOX_AREA_WIDTH_MOVEOK;
	return GF_TP_SingleHitCont( &tp_hit );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	指定座標が左ボックスに当たってるかチェック
 *
 *	@param	lbox		左ボックスデータ
 *	@param	x			判定ｘ座標
 *	@param	y			判定ｙ座標
 *
 *	@retval	TRUE		ヒット
 *	@retval	FALSE		非ヒット
 *
 *
 */
//-----------------------------------------------------------------------------
BOOL IMC_LBOX_TPHitSelf( IMC_LEFT_BOX* lbox, int x, int y )
{
	// 当たり判定矩形データ
	TP_HIT_TBL	tp_hit;
	
	// 当たり判定用データ作成
	tp_hit.rect.top		= IMC_LBOX_AREA_Y_MOVEOK;
	tp_hit.rect.bottom	= IMC_LBOX_AREA_Y_MOVEOK + IMC_LBOX_AREA_HEIGHT_MOVEOK;
	tp_hit.rect.left	= IMC_LBOX_AREA_X_MOVEOK;
	tp_hit.rect.right	= IMC_LBOX_AREA_X_MOVEOK + IMC_LBOX_AREA_WIDTH_MOVEOK;
	return GF_TP_SingleHitSelf( &tp_hit, x, y );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	アクセサリごとの当たり判定を行う
 *
 *	@param	lbox	左ボックス
 *
 *	@return	none
 *
 *	カレントアクセサリリストをチェックします。
 *
 */
//-----------------------------------------------------------------------------
IMC_OBJLIST* IMC_LBOX_TPHitAccessorie( IMC_LEFT_BOX* lbox )
{
	IMC_OBJLIST* work;
	IMC_OBJLIST* dummyTbl;
	BOOL	ret;
	
	// 今のカレントダミーテーブル取得
	dummyTbl = getCurrentDummy( lbox );
	
	work = dummyTbl->next;
	while( work != dummyTbl ){

		ret = FALSE;

		if( (work->flag == IMC_OBJLIST_ACCE) ||
			(work->flag == IMC_OBJLIST_BG) ||
			(work->flag == IMC_OBJLIST_SND)){
			
			ret = IMC_ACCE_ObjTpHit( work->obj_data );
		}

		if(ret == TRUE){

			return work;
		}
		
		work = work->next;
	}

	return NULL;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	アクセサリごとの当たり判定を細かく行う
 *
 *	@param	lbox	左ボックス
 *	@param	offset_x	オフセットｘ座標
 *	@param	offset_y	オフセットｙ座標
 *	@param	SWSP_UPchar	キャラクタリソーステーブル
 *
 *	@return	none
 *
 *	カレントアクセサリリストをチェックします。
 *
 */
//-----------------------------------------------------------------------------
IMC_OBJLIST* IMC_LBOX_TPHitAccessorieEx( IMC_LEFT_BOX* lbox, int* offset_x, int* offset_y, NNSG2dCharacterData** SWSP_UPchar )
{
	IMC_OBJLIST* work;
	IMC_OBJLIST* dummyTbl;
	BOOL	ret;
	
	// 今のカレントダミーテーブル取得
	dummyTbl = getCurrentDummy( lbox );

	work = dummyTbl->next;
	while( work != dummyTbl ){

		ret = FALSE;

		ret = IMC_OBJLIST_ACCEPOKE_HitEx( work, offset_x, offset_y, SWSP_UPchar );

		if(ret == TRUE){

			return work;
		}
		
		work = work->next;
	}

	return NULL;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	BGを表示
 *
 *	@param	lbox		左ボックス
 *	@param	bg_num		左ボックスBGナンバー
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_LBOX_BGSet( IMC_LEFT_BOX* lbox, int bg_num )
{
	IMC_BG_ADD add;
	
	// 登録データ設定
	add.bg_ini		= lbox->boxDraw.BG_Ini;
	add.arc_file	= ARC_IMAGECLIP_GRA;
	add.char_arc	= IMC_BG_LEFT_CG_ARC_GET(bg_num);
	add.pltt_arc	= IMC_BG_LEFT_FRAME_CL;
	add.scrn_arc	= IMC_BG_LEFT_SC_ARC_GET(bg_num);
	add.x			= IMC_LBOX_AREA_X;
	add.y			= IMC_LBOX_AREA_HEIGHT;
	add.frame		= GF_BGL_FRAME3_M;
	add.pltt_num	= IMC_LBOX_BG_PLTT_NUM;
	add.pltt_offs	= IMC_LBOX_BG_PLTT_OFFS;
	add.char_offs	= 0;
	add.heap		= HEAPID_IMAGECLIP_DRAW;

	IMC_BG_MakaObj( &lbox->boxDraw.bg, &add );

	lbox->boxData.back_no = bg_num;
}

//----------------------------------------------------------------------------
/**
 * ●エフェクト付き
 *
 *	@brief	左ボックス背景を変更
 *
 *	@param	lbox		左ボックデータ
 *	@param	bg_num		変更後のBGナンバー
 *	@param	fade_way	フェード方向
 *	@param	sync		何シンクで行うか
 *	@param	end_flg		終了検知フラグ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_LBOX_BGChange( IMC_LEFT_BOX* lbox, int bg_num, int fade_way, int sync, BOOL* end_flg )
{
	IMC_BG_ADD add;
	int fade_x, fade_y;
	
	// 登録データ設定
	add.bg_ini		= lbox->boxDraw.BG_Ini;
	add.arc_file	= ARC_IMAGECLIP_GRA;
	add.char_arc	= IMC_BG_LEFT_CG_ARC_GET(bg_num);
	add.pltt_arc	= IMC_BG_LEFT_FRAME_CL;
	add.scrn_arc	= IMC_BG_LEFT_SC_ARC_GET(bg_num);
	add.x			= IMC_LBOX_AREA_X;
	add.y			= IMC_LBOX_AREA_HEIGHT;
	add.frame		= GF_BGL_FRAME3_M;
	add.pltt_num	= IMC_LBOX_BG_PLTT_NUM;
	add.pltt_offs	= IMC_LBOX_BG_PLTT_OFFS;
	add.char_offs	= 0;
	add.heap		= HEAPID_IMAGECLIP_DRAW;

	if( fade_way & IMC_LBOX_FADE_X ){
		fade_x = IMC_LBOX_AREA_WIDTH;
	}else{
		fade_x = 0;
	}

	if( fade_way & IMC_LBOX_FADE_Y ){
		fade_y = IMC_LBOX_AREA_HEIGHT;
	}else{
		fade_y = 0;
	}

	IMC_BG_ScrollReq( &lbox->boxDraw.bg, &add, fade_x, fade_y, sync, end_flg );

	lbox->boxData.back_no = bg_num;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	BGをクリーンする
 *
 *	@param	lbox		左ボックス
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_LBOX_BGClean( IMC_LEFT_BOX* lbox )
{
	IMC_BG_DeleteObj( &lbox->boxDraw.bg );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	現在のモード
 *
 *	@param	lbox	左ボックス
 *
 *	@return	アクセサリモード
 *
 * mode
	IMC_OBJLIST_ACCE,		// アクセサリタイプ
	IMC_OBJLIST_BG,			// BGサムネイルタイプ
	IMC_OBJLIST_SND,		// サウンドサムネイルタイプ
	IMC_OBJLIST_ACCE_MAX	// モード最大数
 *
 */
//-----------------------------------------------------------------------------
int IMC_LBOX_GetMode( IMC_LEFT_BOX* lbox )
{
	GF_ASSERT( lbox );
	return lbox->boxData.mode;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	現在のカレントダミーテーブルナンバーを取得
 *
 *	@param	lbox	左ボックスデータ
 *	@param	mode	調べたいモード
 *	
 *	@return	カレントダミーテーブルナンバー
 *
 *
 */
//-----------------------------------------------------------------------------
int IMC_LBOX_GetCurrentNo( IMC_LEFT_BOX* lbox, int mode  )
{
	IMC_LEFT_LIST_DATA mode_list;
	
	GF_ASSERT( lbox );

	mode_list = lbox->boxData.acce_list[ mode ];
	return mode_list.dummyCurrent;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	ダミーテーブル数を取得
 *
 *	@param	lbox		左ボックスオブジェ
 *	@param	mode		アクセサリモード
 *
 *	@return	ダミーテーブル数
 *
 *
 */
//-----------------------------------------------------------------------------
int IMC_LBOX_GetDummyTblNum( IMC_LEFT_BOX* lbox, int mode )
{
	IMC_LEFT_LIST_DATA mode_list;
	
	GF_ASSERT( lbox );

	mode_list = lbox->boxData.acce_list[ mode ];
	return mode_list.dummyNum;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	アクセサリリスト全ての座標を動かす
 *
 *	@param	lbox		左ボックス
 *	@param	mode		モード
 *	@param	list_no		リストナンバー
 *	@param	x			動かすｘ座標
 *	@param	y			動かすｙ座標
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_LBOX_AccessorieListMove( IMC_LEFT_BOX* lbox, int mode, int list_no, int x, int y )
{
	IMC_OBJLIST* dummyTbl;
	
	// modeとリストから先頭ダミーデータ取得
	dummyTbl = getDummyTbl( lbox, mode, list_no );
	
	IMC_OBJLIST_ACCEPOKE_ListMove( dummyTbl, x, y );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	今左ボックを壊してよい状態なのかをチェック
 *
 *	@param	lbox	左ボックスデータ
 *
 *	@retval	TRUE	OK
 *	@retval FALSE	NG		フェード中です
 *
 *
 */
//-----------------------------------------------------------------------------
BOOL IMC_LBOX_ENDCheck( IMC_LEFT_BOX* lbox )
{
	if( lbox->boxData.state == IMC_LBOX_STATE_NORM ){
		return TRUE;
	}

	return FALSE;
}

//-----------------------------------------------------------------------------
/**
*		プライベート関数
*/
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *
 *	@brief	アクセサリリスト作成
 *
 *	@param	lbox	左ボックスデータ
 *	@param	init	初期化データ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void makeAcceList( IMC_LEFT_BOX* lbox, IMC_LEFT_BOX_INIT* init )
{
	// アクセサリリスト作成
	listDataMake( &lbox->boxData.acce_list[ IMC_OBJLIST_ACCE ], init->accelist_num );

	// カレントに設定
	lbox->boxData.mode	= IMC_OBJLIST_ACCE;
	drawSetList( lbox->boxData.acce_list[ IMC_OBJLIST_ACCE ].dummyTbl, TRUE );

	// BGサムネイルリスト作成
	listDataMake( &lbox->boxData.acce_list[ IMC_OBJLIST_BG ], init->bglist_num );
	
	// 音声サムネイルリスト作成
	listDataMake( &lbox->boxData.acce_list[ IMC_OBJLIST_SND ], init->sndlist_num );

	// フェード用リスト
	listDataMake( &lbox->boxData.acce_list[ IMC_LBOX_FADELIST_MODE ], IMC_LBOX_FADELIST_LISTNUM );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	オブジェクトリストの表示非表示設定
 *
 *	@param	dummy		ダミーデータ
 *	@param	flag		表示非表示フラグ
 *
 *	@return
 *
 *
 */
//-----------------------------------------------------------------------------
static void drawSetList( IMC_OBJLIST* dummy, int flag )
{
	IMC_OBJLIST* work;
	
	work = dummy->next;
	while( work != (dummy) ){


		if( (work->flag == IMC_OBJLIST_ACCE) ||
			(work->flag == IMC_OBJLIST_BG) ||
			(work->flag == IMC_OBJLIST_SND)){
			
			IMC_ACCE_ObjListDrawSet( work->obj_data, flag );
		}

		work = work->next;
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	表示非表示設定上位関数
 *
 *	@param	lbox		左ボックス
 *	@param	mode		アクセサリモード
 *	@param	list		リスト番号
 *	@param	flag		表示非表示
 *
 *	@return	none
 *	
 *
 */
//-----------------------------------------------------------------------------
static void drawSetListPack( IMC_LEFT_BOX* lbox, int mode, int list, int flag )
{
	IMC_OBJLIST* dummytbl;
	dummytbl = getDummyTbl( lbox, mode, list );

	drawSetList( dummytbl, flag );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	カレントダミーリストの表示非表示の設定
 *
 *	@param	lbox		左ボックスオブジェ
 *	@param	flag		表示/非表示フラグ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void drawFlgCurrentDummy( IMC_LEFT_BOX* lbox, int flag )
{
	IMC_OBJLIST* dummyTbl;
	
	// カレントダミーリスト取得
	dummyTbl = getCurrentDummy( lbox );

	// これからのカレント描画ON
	drawSetList( 
			dummyTbl,
			flag );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	ダミーリストテーブルの作成	
 *
 *	@param	list		ダミーリストテーブル
 *	@param	dummy_num	作成する先頭ダミーデータ数
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void listDataMake( IMC_LEFT_LIST_DATA* list, int dummy_num )
{
	int i;
	
	list->dummyTbl	= sys_AllocMemory( HEAPID_IMAGECLIP_DRAW, sizeof(IMC_OBJLIST) * dummy_num );
	list->dummyNum	= dummy_num;
	list->dummyCurrent	= 0;

	for( i=0; i<list->dummyNum; i++ ){
		list->dummyTbl[ i ].next = list->dummyTbl + i;
		list->dummyTbl[ i ].prev = list->dummyTbl + i;

		drawSetList( 
				list->dummyTbl + i,
				FALSE );
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	アクセサリリストデータ破棄
 *
 *	@param	list	アクセサリリスト
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void listDataDest( IMC_LEFT_LIST_DATA* list )
{
	sys_FreeMemoryEz( list->dummyTbl );
	list->dummyTbl	= NULL;

	memset( list, 0, sizeof(IMC_LEFT_LIST_DATA) );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	今のカレントダミーリストを取得
 *
 *	@param	lbox	左ボックスオブジェ
 *
 *	@return	カレントのダミーリスト
 *
 *
 */
//-----------------------------------------------------------------------------
static IMC_OBJLIST* getCurrentDummy( IMC_LEFT_BOX* lbox )
{
	IMC_LEFT_LIST_DATA mode_list;
		
	mode_list = lbox->boxData.acce_list[ lbox->boxData.mode ];
	return &mode_list.dummyTbl[ mode_list.dummyCurrent ];
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	ダミーリストを選択して取得
 *
 *	@param	lbox		左ボックスオブジェ
 *	@param	mode		モード
 *	@param	tbl_no		テーブル番号
 *
 *	@return	ダミーリスト
 *
 *
 */
//-----------------------------------------------------------------------------
static IMC_OBJLIST* getDummyTbl( IMC_LEFT_BOX* lbox, int mode, int tbl_no )
{
	IMC_LEFT_LIST_DATA mode_list;
		
	mode_list = lbox->boxData.acce_list[ mode ];
	return &mode_list.dummyTbl[ tbl_no ];
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	リストに登録されているアクセサリ数を取得する
 *
 *	@param	lbox		左ボックス
 *	@param	mode		リストモード
 *	@param	tbl_no		ダミーデータナンバー
 *
 *	@return	登録されているオブジェクト数
 *
 *
 */
//-----------------------------------------------------------------------------
static int getListSetDataNum( IMC_LEFT_BOX* lbox, int mode, int tbl_no )
{
	IMC_OBJLIST* dummy;
	IMC_OBJLIST* work;
	int count = 0;

	// ダミーテーブル
	dummy = getDummyTbl( lbox, mode, tbl_no );
	work = dummy->next;

	while( work != dummy ){
		
		count++;
		work = work->next;
	}

	return count;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	オブジェクトリストの指定数目のデータを取得
 *
 *	@param	lbox		左ボックス
 *	@param	mode		リストモード
 *	@param	tbl_no		リストナンバー
 *	@param	no			指定数
 *
 *	@retval	NULL		指定数が多いか少なすぎ
 *	@retval	その他		取得成功
 *
 *
 */
//-----------------------------------------------------------------------------
static IMC_OBJLIST* getNoListObjData( IMC_LEFT_BOX* lbox, int mode, int tbl_no, int no )
{
	IMC_OBJLIST* dummy;
	IMC_OBJLIST* work;
	int count = 0;

	// ダミーテーブル
	dummy = getDummyTbl( lbox, mode, tbl_no );
	work = dummy->next;

	while( work != dummy ){
		
		if( count == no ){

			return work;
		}

		count++;
		work = work->next;
	}

	return NULL;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	表示/非表示判断を判定して表示非表示を設定する
 *
 *	@param	lbox		左ボックスオブジェ
 *	@param	acce_obj	アクセサリオブジェ
 *	@param	mode		モード
 *	@param	list_num	ダミーデータナンバー
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void drawFlgSetCheck( IMC_LEFT_BOX* lbox, IMC_ACCESSORIE_OBJ* acce_obj, int mode, int list_num )
{
	// 追加先がカレントのリストでなければ非表示にする
	if( (lbox->boxData.mode != mode) || 
		(lbox->boxData.acce_list[ mode ].dummyCurrent != list_num) ){

		IMC_ACCE_ObjListDrawSet( acce_obj, FALSE );
	}else{

		IMC_ACCE_ObjListDrawSet( acce_obj, TRUE );
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	サムネイル座標を取得する
 *
 *	@param	no		アクセサリNo
 *	@param	x		X座標格納先
 *	@param	y		ｙ座標格納先
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void getBgSndThumbMat( int no, int* x, int* y )
{
	int step_y;		// 縦何段目か
	int step_x;		// 横何段目か
	
	// リスト内ナンバーにする
	no %= IMC_LBOX_BG_ONE_LIST_NUM;
	
	// 段数を計算
	step_y = no / IMC_LBOX_MAT_LINE_NUM;
	step_x = no % IMC_LBOX_MAT_LINE_NUM;

	// まず高決定
	*y = IMC_LBOX_MAT_SPACE_Y * (step_y + 1);
	*y += IMC_LBOX_THUMB_SIZE_Y * step_y;
	*y += IMC_LBOX_AREA_Y;

	// 幅決定
	*x = IMC_LBOX_MAT_SPACE_X * (step_x + 1);
	*x += IMC_LBOX_THUMB_SIZE_X * step_x;
	*x += IMC_LBOX_AREA_X;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	パレットフェード開始
 *
 *	@param	lbox			左ボックス
 *	@param	out_mode		フェードアウトパレットmode
 *	@param	out_list		フェードアウトパレットno
 *	@param	in_mode			フェードインパレットmode
 *	@param	in_list			フェードインパレットno
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void plttChgTaskStart( IMC_LEFT_BOX* lbox, int out_mode, int out_list, int in_mode, int in_list )
{
	TCB_PTR tcb;
	IMC_LBOX_PLTT_TASK* pltt_tsk;
	
	// タスク生成
	tcb = PMDS_taskAdd( plttChgTask, sizeof(IMC_LBOX_PLTT_TASK), 0, HEAPID_IMAGECLIP_DATA );

	// ワークに値を設定
	pltt_tsk = TCB_GetWork( tcb );

	// データ設定
	pltt_tsk->lbox		= lbox;
	pltt_tsk->out_mode	= out_mode;
	pltt_tsk->out_list	= out_list;
	pltt_tsk->in_mode	= in_mode;
	pltt_tsk->in_list	= in_list;
	pltt_tsk->seq		= IMC_LBOX_PLTT_CHG_INIT;
	pltt_tsk->out_count	= getListSetDataNum( lbox, out_mode, out_list );
	pltt_tsk->in_count	= getListSetDataNum( lbox, in_mode, in_list );
	pltt_tsk->move_obj_num = pltt_tsk->out_count + pltt_tsk->in_count;

	pltt_tsk->move_obj = sys_AllocMemory( HEAPID_IMAGECLIP_DATA, sizeof(IMC_LBOX_PLTT_OBJ_MOVE) * pltt_tsk->move_obj_num );
	GF_ASSERT( pltt_tsk->move_obj );
	memset( pltt_tsk->move_obj, 0, 
			sizeof(IMC_LBOX_PLTT_OBJ_MOVE) * pltt_tsk->move_obj_num );

	// 左パレット状態をフェード中にする
	lbox->boxData.state = IMC_LBOX_STATE_FADE;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	パレットフェード
 *
 *	@param	tcb		tcbタスク
 *	@param	work	ワーク
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void plttChgTask( TCB_PTR tcb, void* work )
{
	IMC_LBOX_PLTT_TASK* tsk_w = work;
	int i;
	int bg_no;
	
	switch( tsk_w->seq ){
	case IMC_LBOX_PLTT_CHG_INIT:
		
		// フェードインするリストの座標を設定
		IMC_LBOX_AccessorieListMove( tsk_w->lbox, tsk_w->in_mode, tsk_w->in_list, 0, -IMC_LBOX_PLTT_CHG_MOVE_Y );
		
		// フェードインするリストを表示させる
		drawSetListPack( tsk_w->lbox, tsk_w->in_mode, tsk_w->in_list, TRUE );

		// BGフェードアウト開始
		tsk_w->bg_fade = FALSE;
		bg_no = (tsk_w->lbox->boxData.back_no + 1) % IMC_BG_LEFT_MAX;
		IMC_LBOX_BGChange( tsk_w->lbox, bg_no, IMC_LBOX_FADE_Y, IMC_LBOX_PLTT_BG_SYNC, &tsk_w->bg_fade );

		// 一度に足す数を求める
		tsk_w->count = movePlttChgGetObjAddNum( tsk_w->out_count, IMC_LBOX_PLTT_CHG_OBJ_E_NUM );

		tsk_w->seq++;
		break;
		
	case IMC_LBOX_PLTT_CHG_OUT_ACCE_S:
		
		// 今いるBGとアクセサリを画面外へ
		for( i=0; i<tsk_w->count; i++ ){
			
			// 登録
			if( (tsk_w->out_count - 1) >= 0 ){
				IMC_OBJLIST* obj;	

				tsk_w->out_count --;
				obj = getNoListObjData( tsk_w->lbox, tsk_w->out_mode, tsk_w->out_list, tsk_w->out_count );
				startPlttChgObj( obj, tsk_w->move_obj, tsk_w->move_obj_num );
			}
		}
		if(tsk_w->out_count == 0){

			// 一度に足す数を求める
			tsk_w->count = movePlttChgGetObjAddNum( tsk_w->in_count, IMC_LBOX_PLTT_CHG_OBJ_S_NUM );

			// 次へ
			tsk_w->seq ++;
		}
		break;

	case IMC_LBOX_PLTT_CHG_IN_ACCE_S:
		// 新アクセサリを画面へ
		for( i=0; i<tsk_w->count; i++ ){
			
			// 登録
			if( (tsk_w->in_count - 1) >= 0 ){
				IMC_OBJLIST* obj;	

				tsk_w->in_count --;
				obj = getNoListObjData( tsk_w->lbox, tsk_w->in_mode, tsk_w->in_list, tsk_w->in_count );
				startPlttChgObj( obj, tsk_w->move_obj, tsk_w->move_obj_num );
			}
		}
		if(tsk_w->in_count == 0){
			// 次へ
			tsk_w->seq ++;
			tsk_w->count = 0;
		}
		break;
		
	case IMC_LBOX_PLTT_CHG_WAIT:
		// 全てが動き終わるのを待つ
		tsk_w->count ++;

		// オブジェクトの動き
		if( tsk_w->count > IMC_LBOX_PLTT_CHG_COUNT ){
				
			// BGフェード
			if( tsk_w->bg_fade ){

				tsk_w->seq ++;
			}
		}
		break;

	case IMC_LBOX_PLTT_CHG_END:
		// 座標を再設定して終わり
		// フェードアウトするリストを非表示にする
		drawSetListPack( tsk_w->lbox, tsk_w->out_mode, tsk_w->out_list, FALSE );
		
		// フェードアウトリストの座標を設定
		IMC_LBOX_AccessorieListMove( tsk_w->lbox, tsk_w->out_mode, tsk_w->out_list, 0, -IMC_LBOX_PLTT_CHG_MOVE_Y );

		// 左パレット状態を通常にする
		tsk_w->lbox->boxData.state = IMC_LBOX_STATE_NORM;

		// 確保したメモリ破棄
		sys_FreeMemoryEz( tsk_w->move_obj );
	
		// タスク終了
		PMDS_taskDel( tcb );
		
		return ;

	default:
		GF_ASSERT(0);
		break;
	}

	// オブジェクト動作
	movePlttChgObj( tsk_w->move_obj, tsk_w->move_obj_num );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	フェードパターンオブジェクト動作タスクに設定
 *
 *	@param	obj		オブジェデータ
 *	@param	data	動作データテーブル
 *	@param	num		テーブル数
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void startPlttChgObj( IMC_OBJLIST* obj, IMC_LBOX_PLTT_OBJ_MOVE* data, int num )
{
	IMC_LBOX_PLTT_OBJ_MOVE* obj_move;

	// 空のオブジェ動作テーブル取得
	obj_move = getCleanPlttChgObj( data, num );


	obj_move->obj		= obj;
	obj_move->count		= IMC_LBOX_PLTT_CHG_COUNT;
	obj_move->add_y		= IMC_LBOX_PLTT_CHG_ADD;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	クリーン状態のテーブルを取得
 *
 *	@param	data	テーブル
 *
 *	@return	何も設定されていないテーブル
 *
 *
 */
//-----------------------------------------------------------------------------
static IMC_LBOX_PLTT_OBJ_MOVE* getCleanPlttChgObj( IMC_LBOX_PLTT_OBJ_MOVE* data, int num )
{
	int i;	// ループ用

	for( i=0; i<num; i++ ){

		if( data[i].obj == NULL ){
			return data + i;
		}
	}

	return NULL;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	パレットフェード個々オブジェ動作関数を実行
 *
 *	@param	data	動作テーブル
 *	@param	num		テーブル数
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void movePlttChgObj( IMC_LBOX_PLTT_OBJ_MOVE* data, int num )
{
	int i;		// ループ用

	for( i=0; i<num; i++ ){
		if( data[i].obj ){

			movePlttChgObjCore( data + i );
		}
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	パレットフェード個々オブジェ動作関数
 *
 *	@param	data	動作テーブル
 *
 *	@return none
 *
 */
//-----------------------------------------------------------------------------
static void movePlttChgObjCore( IMC_LBOX_PLTT_OBJ_MOVE* data )
{
	int x, y;
	
	IMC_OBJLIST_ACCEPOKE_MatGet( data->obj, &x, &y );

	y += data->add_y;

	IMC_OBJLIST_ACCEPOKE_Mat( data->obj, x, y );

	data->count --;

	// 終了チェック
	if( data->count <= 0 ){

		memset( data, 0, sizeof(IMC_LBOX_PLTT_OBJ_MOVE) );
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	一度に動かすアクセサリ数を取得
 *
 *	@param	obj_num		アクセサリ総数
 *	@param	div			何シンクに分けるか
 *
 *	@return	一度に動かす数
 *
 *
 */
//-----------------------------------------------------------------------------
static int movePlttChgGetObjAddNum( int obj_num, int div )
{
	// 割り切れる値にする
	obj_num += div - (obj_num % div);

	return obj_num / div;
}
