//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *@file		res_manager.c
 *@brief	リソース管理マネージャー
 *@author	tomoya takahashi
 *@data		2005.08.29
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

#include "nnsys.h"
#include "system.h"
#include "assert.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define __RES_MANAGER_H_GLOBAL
#include "res_manager.h"

//-----------------------------------------------------------------------------
/**
 *					定数宣言
*/
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/**
 *					構造体宣言
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	
//	リソースヘッダー個々のデータ
//
//	登録データをまとめたデータです
//	
//=====================================
typedef struct _RES_HEADER_SUB{
	int		id;				// 管理ID
	char	file_path[64];	// ファイルパス
} RES_HEADER_SUB;

//-------------------------------------
//	
//	リソースヘッダーのデータ
//
//	個々のデータをまとめたデータ
//	
//=====================================
typedef struct _RES_HEADER{
	RES_HEADER_SUB* tbl;	// 個々のデータテーブル
	int				num;	// テーブル数
} RES_HEADER;


//-------------------------------------
//	
//	読み込まれたリソースのデータ
//	
//=====================================
typedef struct _RES_OBJ{
	int		id;		// 管理ID
	void*	p_res;	// リソースポインタ
} RES_OBJ;

//-------------------------------------
//	
//	リソース管理マネージャー
//	管理データ構造体
//	
//=====================================
typedef struct _RES_MANAGER{
	RES_OBJ*	p_work;		// リソース格納テーブル
	int			max;		// 可能格納数
	int			now;		// 現在格納数
} RES_MANAGER;





//-----------------------------------------------------------------------------
/**
*		テクスチャリソース限定マネージャ
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	
//	テクスチャリソースオブジェ
//	
//=====================================
typedef struct _TEXRES_OBJ{
	RES_OBJ*		resobj;		// リソースオブジェ
	NNSGfdTexKey	texKey;		// テクスチャキー
	NNSGfdTexKey	tex4x4Key;	// 4x4テクスチャキー
	NNSGfdPlttKey	plttKey;	// パレットキー
	void*			p_cutTex;	// テクスチャ実データ破棄用リソース
	u16				cut_flag;	// テクスチャ実データを破棄したか
	u16				cuttex_flag;// テクスチャカットの有無
} TEXRES_OBJ;

//-------------------------------------
//	
//	テクスチャリソースマネージャ
//	
//=====================================
typedef struct _TEXRES_MANAGER{
	RES_MANAGER*	resm;	// リソースマネージャ
	TEXRES_OBJ*		tobj;	// テクスチャオブジェデータ
} TEXRES_MANAGER;





//-----------------------------------------------------------------------------
/**
 *					プロトタイプ宣言
*/
//-----------------------------------------------------------------------------
static RES_OBJ_PTR getCleanRES_OBJ(RES_MANAGER_PTR resm);
static void clean_RES_OBJ(RES_OBJ* data);
static int getHeaderNum(char* buff);
static void getHeaderData(char* buff, RES_HEADER_SUB* data, int num);
static void getOneData(char* buff, char** file_path, char** id);
static void setOneData(char* file_path, char* id, RES_HEADER_SUB* data);
static char* makeCopyStr(const char* buff, int heap);
static void delCopyStr(char* copy);


//-----------------------------------------------------------------------------
/**
*	テクスチャ限定マネージャ
*/
//-----------------------------------------------------------------------------
static TEXRES_OBJ_PTR getCleanTEXRES_OBJ(CONST_TEXRES_MANAGER_PTR resm);
static void cleanTEXRES_OBJ(TEXRES_OBJ_PTR obj);
static void getVramkey( const NNSG3dResTex* res, NNSGfdTexKey* tex, NNSGfdTexKey* tex4x4, NNSGfdPlttKey* pltt );
static NNSG3dResTex* getTexRes( CONST_TEXRES_OBJ_PTR r_obj );
static NNSG3dResTex* getTexRes_CheckCutTex( CONST_TEXRES_OBJ_PTR r_obj );
static void loadTexRes( NNSG3dResTex* res, TEXRES_OBJ_PTR r_obj );
static void setTexkeyRes( NNSG3dResTex* res, NNSGfdTexKey tex, NNSGfdTexKey tex4x4, NNSGfdPlttKey pltt );
static void releaseTexkeyRes( NNSG3dResTex* res );

// テクスチャリソースを削除したNNSG3dResTexを作成する関数郡
static void* MakeCutTexWork( void* p_cuttex, u32 heap );
static u32 GetCutTexDataSize( const void* p_cuttex );

//----------------------------------------------------------------------------
/**
 *
 *@brief	リソース管理マネージャー実態部作成
 *
 *@param	num		データ管理テーブル数
 *
 *@return	RES_MANAGER_PTR		管理データポインタ
 *
 * ●管理テーブル領域の確保
 * ●管理テーブル領域の初期化
 *
 */
//-----------------------------------------------------------------------------
RES_MANAGER_PTR RESM_Init(int num, int heap)
{
	RES_MANAGER_PTR resm;
	int i;		// ループ用

	// リソース管理マネージャー作成
	resm = sys_AllocMemory(heap, sizeof(RES_MANAGER));
	GF_ASSERT(resm);
	
	// 管理テーブル作成
	resm->p_work = sys_AllocMemory(heap, sizeof(RES_OBJ)*num);
	GF_ASSERT(resm->p_work);
	for(i=0;i<num;i++){
		clean_RES_OBJ( (resm->p_work + i) );
	}


	resm->max	= num;		// 最大数
	resm->now	= 0;		// 現在登録数

	return resm;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	リソース管理データ破棄
 *
 *@param	resm	リソース管理データ
 *
 *@return	none
 *
 *	●読み込んだリソースを破棄
 *	●管理テーブル領域を破棄
 */
//-----------------------------------------------------------------------------
void RESM_Delete(RES_MANAGER_PTR resm)
{
	GF_ASSERT(resm);
	
	// 登録されているリソースを全て破棄
	RESM_DeleteAllRes(resm);

	// メモリ破棄
	sys_FreeMemoryEz(resm->p_work);
	sys_FreeMemoryEz(resm);
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	残り登録可能数を取得
 *
 *@param	resm	取得するリソース管理データ
 *
 *@return	int		残り登録可能数
 *
 *
 */
//-----------------------------------------------------------------------------
int RESM_GetRest(RES_MANAGER_PTR resm)
{
	GF_ASSERT(resm);

	return ( resm->max - resm->now );
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	IDが重複しないかを取得
 *
 *@param	resm	取得するリソース管理データ
 *@param	id		チェックするID
 *
 *@retval	TRUE	重複しない
 *@retval	FALSE	重複する
 *
 *
 */
//-----------------------------------------------------------------------------
BOOL RESM_CheckID(RES_MANAGER_PTR resm, int id)
{
	int i;		// ループ用
	
	GF_ASSERT(resm);

	// IDが同じテーブルがあるかチェック
	if( RESM_GetResObj(resm, id) == NULL ){
		// 同じテーブルが無いので,重複しない
		return TRUE;
	}

	return FALSE;
}

//----------------------------------------------------------------------------
/**
 *	
 *@brief	リソースの登録
 *
 *@param	resm	登録するリソース管理データポインタ
 *@param	res		リソース
 *@param	id		登録ID	（＊重複注意）
 *
 *@retval	RES_OBJ_PTR	登録成功
 *@retval	NULL		登録失敗	登録テーブルが満杯
 *
 * ●パスのリソースを読み込んで、管理データに設定
 *
 */
//-----------------------------------------------------------------------------
RES_OBJ_PTR RESM_AddResNormal(RES_MANAGER_PTR resm, void* res, int id)
{
	RES_OBJ_PTR r_obj;
	
	GF_ASSERT(resm);

	// 空いているテーブルを取得
	r_obj = getCleanRES_OBJ(resm);
	GF_ASSERT(r_obj && ("テーブルに空きが無い"));

	// IDが重複しないかチェック
	GF_ASSERT( (RESM_CheckID(resm, id) == TRUE) );

	// リソース読み込み
	r_obj->p_res = res;

	r_obj->id = id;	// 登録ID

	resm->now++;	// テーブル登録数追加

	return r_obj;
}

//----------------------------------------------------------------------------
/**
 *	
 *@brief	リソースの登録
 *
 *@param	resm	登録するリソース管理データポインタ
 *@param	p_path	リソースのパス
 *@param	id		登録ID	（＊重複注意）
 *@param	heap	リソース読み込みに使用するヒープ
 *
 *@retval	RES_OBJ_PTR	登録成功
 *
 * ●パスのリソースを読み込んで、管理データに設定
 *
 */
//-----------------------------------------------------------------------------
RES_OBJ_PTR RESM_AddRes(RES_MANAGER_PTR resm, const char* p_path, int id, int heap)
{
	RES_OBJ_PTR r_obj;
	
	GF_ASSERT(resm);
	GF_ASSERT(p_path);

	// 空いているテーブルを取得
	r_obj = getCleanRES_OBJ(resm);
	GF_ASSERT(r_obj && ("テーブルに空きが無い"));

	// IDが重複しないかチェック
	GF_ASSERT( (RESM_CheckID(resm, id) == TRUE) );

	// リソース読み込み
	r_obj->p_res = sys_LoadFile(heap, p_path);
	GF_ASSERT(r_obj->p_res && ("パスが間違っています"));

	r_obj->id = id;	// 登録ID

	resm->now++;	// テーブル登録数追加

	return r_obj;
}

//----------------------------------------------------------------------------
/**
 *	
 *@brief	ヘッダーを使用したリソースの登録（単発）
 *
 *@param	resm	登録するリソース管理データポインタ
 *@param	header	リソースヘッダーポインタ
 *@param	no		何番目を登録するか
 *@param	heap	リソース読み込みに使用するヒープ
 *
 *@retval	RES_OBJ_PTR	登録成功
 *
 * ●パスのリソースを読み込んで、管理データに設定
 *
 */
//-----------------------------------------------------------------------------
RES_OBJ_PTR RESM_AddResHd(RES_MANAGER_PTR resm, const RES_HEADER_PTR header, int no, int heap)
{
	GF_ASSERT(resm);
	GF_ASSERT(header);

	// 要素数以下かチェック
	GF_ASSERT(header->num > no);
	
	return RESM_AddRes(resm, header->tbl[no].file_path, header->tbl[no].id, heap);
}

//----------------------------------------------------------------------------
/**
 *	
 *@brief	ヘッダーを使用したリソースの登録（複数）
 *
 *@param	resm	登録するリソース管理データポインタ
 *@param	header	リソースヘッダーポインタ
 *@param	heap	リソース読み込みに使用するヒープ
 *
 *@return	none
 *
 * ●パスのリソースを読み込んで、管理データに設定
 *
 */
//-----------------------------------------------------------------------------
void RESM_AddResHds(RES_MANAGER_PTR resm, const RES_HEADER_PTR header, int heap)
{
	GF_ASSERT(resm);
	GF_ASSERT(header);
	
	RESM_AddResHdsEx(resm, header, 0, header->num, heap);
}

//----------------------------------------------------------------------------
/**
 *	
 *@brief	ヘッダーを使用したリソースの登録（複数）
 *			ヘッダーの開始要素、終了要素を指定
 *
 *@param	resm	登録するリソース管理データポインタ
 *@param	header	リソースヘッダーポインタ
 *@param	start	開始要素数
 *@param	num		登録要素数
 *@param	heap	リソース読み込みに使用するヒープ
 *
 *@return	noen
 *
 * ●パスのリソースを読み込んで、管理データに設定
 *
 */
//-----------------------------------------------------------------------------
void RESM_AddResHdsEx(RES_MANAGER_PTR resm, const RES_HEADER_PTR header, int start, int num, int heap)
{
	int i;
	
	GF_ASSERT(resm);
	GF_ASSERT(header);

	// 要素数オーバーしないかチェック
	GF_ASSERT((start+num) <= header->num)

	for(i=start;i<(start+num);i++){
		RESM_AddResHd(resm, header, i, heap);
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	リソースの破棄
 *
 *@param	resm	破棄するリソースが登録されている管理データポインタ
 *@param	r_obj	破棄するリソースオブジェ
 *
 * ●読み込んだリソースを破棄し、管理データを初期化
 */
//-----------------------------------------------------------------------------
void RESM_DeleteRes(RES_MANAGER_PTR resm, RES_OBJ_PTR r_obj)
{
	GF_ASSERT(resm);
	GF_ASSERT(r_obj);

	if( r_obj->p_res ){
		sys_FreeMemoryEz(r_obj->p_res);
		r_obj->p_res = NULL;
	}
	r_obj->id = RES_MANAGER_ID_NONE;

	resm->now--;	// テーブル登録数減算
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	IDでリソースの破棄
 *
 *@param	resm	破棄するリソースが登録されている管理データポインタ
 *@param	id		破棄するリソースのID
 *
 * ●読み込んだリソースを破棄し、管理データを初期化
 */
//-----------------------------------------------------------------------------
void RESM_DeleteResID(RES_MANAGER_PTR resm, int id)
{
	RES_OBJ_PTR	data;

	GF_ASSERT(resm);
	data = RESM_GetResObj(resm, id);
	GF_ASSERT( data && ("IDのデータはありません。"));

	// 破棄
	RESM_DeleteRes(resm, data);
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	全リソースの破棄
 *
 *@param	resm	破棄するリソースが登録されている管理データポインタ
 *
 * ●読み込んだリソースを破棄し、管理データを初期化
 */
//-----------------------------------------------------------------------------
void RESM_DeleteAllRes(RES_MANAGER_PTR resm)
{
	int i;	// ループ用
	
	GF_ASSERT(resm);
	GF_ASSERT(resm->p_work);
	
	for(i=0; i<resm->max;i++){
		if( resm->p_work[i].id != RES_MANAGER_ID_NONE ){
			RESM_DeleteRes(resm, (resm->p_work + i));
		}
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	リソースオブジェクトデータポインタを取得
 *
 *@param	resm		リソース管理データ
 *@param	id			リソースのID
 *
 *@retval	NULL		登録されていない
 *@retval	RES_OBJ_PTR	登録されているリソースオブジェポインタ
 *
 *
 */
//-----------------------------------------------------------------------------
RES_OBJ_PTR RESM_GetResObj(RES_MANAGER_PTR resm, int id)
{
	int i;	// ループ用
	GF_ASSERT(resm);

	for(i = 0;i < resm->max; i++){
		if(resm->p_work[i].id == id){
			return (resm->p_work + i);
		}
	}

	return NULL;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	登録されているリソースデータを取得
 *
 *@param	r_obj		リソースオブジェ
 *
 *@retval	NULL		登録されていない
 *@retval	NULL以外	登録されているリソースポインタ
 *
 *
 */
//-----------------------------------------------------------------------------
void* RESM_GetRes(RES_OBJ_PTR r_obj)
{
	GF_ASSERT(r_obj);

	return r_obj->p_res;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	登録されているリソースデータを変更
 *
 *@param	r_obj		リソースオブジェ
 *
 *@param	登録されているリソースデータ変更
 *
 */
//-----------------------------------------------------------------------------
void RESM_SetRes(RES_OBJ_PTR r_obj, void* res)
{
	GF_ASSERT(r_obj);

	if( r_obj->p_res ){
		sys_FreeMemoryEz(r_obj->p_res);
	}
	r_obj->p_res = res;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	登録されているIDを取得
 *
 *@param	r_obj		リソースオブジェ
 *
 *@retval	int			ID
 *
 *
 */
//-----------------------------------------------------------------------------
int RESM_GetID(RES_OBJ_PTR r_obj)
{
	GF_ASSERT(r_obj);

	return r_obj->id;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	登録されているIDを設定
 *
 *@param	r_obj		リソースオブジェ
 *@param	id			設定するID
 *
 *@retval	none
 *
 *
 */
//-----------------------------------------------------------------------------
void RESM_SetID(RES_MANAGER_PTR resm, RES_OBJ_PTR r_obj, int id)
{
	GF_ASSERT(resm);
	GF_ASSERT(r_obj);
	GF_ASSERT( RESM_CheckID(resm, id) );	// 重複しないかチェック

	r_obj->id = id;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	空いているオブジェを取得
 *	
 *@param	none
 *
 *@retval	RES_OBJ_PTR	空いているオブジェ
 *@retval	NULL		空いていない
 *
 *
 */
//-----------------------------------------------------------------------------
static RES_OBJ_PTR getCleanRES_OBJ(RES_MANAGER_PTR resm)
{
	int i;
	GF_ASSERT(resm);

	for(i=0;i<resm->max;i++){
		if(resm->p_work[i].id == RES_MANAGER_ID_NONE){
			return resm->p_work + i;
		}
	}

	return NULL;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	リソースオブジェの初期化
 *
 *@param	data	データ
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void clean_RES_OBJ(RES_OBJ* data)
{
	GF_ASSERT(data);
	data->id	= RES_MANAGER_ID_NONE;
	data->p_res = NULL;
}

//-----------------------------------------------------------------------------
//
//		*********** ヘッダー用関数 **************
//
//=============================================================================
//----------------------------------------------------------------------------
/**
 *
 *@brief	ヘッダーサイズを取得
 *
 *@param	none	
 *
 *@return	int		ヘッダーのバイトサイズ
 *
 *
 */
//-----------------------------------------------------------------------------
int RESM_GetHeaderSize(void)
{
	return sizeof(RES_HEADER);
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	ヘッダー配列から要素数のデータを返す
 *
 *@param	tbl		配列になっているヘッダー
 *@param	no		要素数
 *
 *@return	RES_HEADER_PTR data[no] のアドレス
 *
 *
 */
//-----------------------------------------------------------------------------
RES_HEADER_PTR RESM_GetTbl(RES_HEADER_PTR tbl, int no)
{
	GF_ASSERT(tbl);
	return ( tbl + no );
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	リソースヘッダーの読み込み
 *
 *@param	header			ヘッダーデータ格納先
 *@param	rom_path		ヘッダーファイルパス
 *@param	heap			ひーぷID 
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void RESM_HeaderLoad(RES_HEADER_PTR header, const char* rom_path, int heap)
{
	char* tmp;				// 解放用
	char* buff;				// ファイルデータ
	int	i;					// ループ用

	GF_ASSERT(header);		// ヘッダー領域を確保してください
	GF_ASSERT(rom_path);


	// ファイルオープン
	tmp = sys_LoadFile(heap, rom_path);
	GF_ASSERT(tmp&&("ヘッダー読み込み失敗"))

	// ワークバッファ
	buff = makeCopyStr(tmp, heap);
	
	// ファイル数を取得
	header->num = getHeaderNum(buff);

	// メモリ確保
	header->tbl = sys_AllocMemory(heap, sizeof(RES_HEADER_SUB)*header->num);
	GF_ASSERT(header->tbl);

	// ワークバッファに代入
	delCopyStr(buff);	// いったん破棄
	buff = makeCopyStr(tmp, heap);

	// データ読み込み
	getHeaderData(buff, header->tbl, header->num);

	// 読み込みファイル破棄
	delCopyStr(buff);
	sys_FreeMemoryEz(tmp);
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	リソースヘッダーの破棄
 *
 *@param	header			ヘッダーデータデータ
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void RESM_HeaderFree(RES_HEADER_PTR header)
{
	GF_ASSERT(header);
	GF_ASSERT(header->tbl);
	
	sys_FreeMemoryEz(header->tbl);
	header->tbl = NULL;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	登録データ数を取得
 *
 *@param	buff	バッファ
 *
 *@return	int		データ数
 *
 *
 */
//-----------------------------------------------------------------------------
static int getHeaderNum(char* buff)
{
	int count;			// データ数カウント
	char* file_path;	// ファイルパス
	char* id;			// ファイルパス


	count = 0;
	getOneData(buff, &file_path, &id);	// １つのデータ格納
	// パスが'0'のデータが終端
	while(file_path[0] != '0'){
		count++;

		getOneData(NULL, &file_path, &id);	// １回目以降はNULLでOK

		if(file_path == NULL){
			GF_ASSERT(0);		// 終端コードが無い
		}
	}

	return count;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	データ格納
 *
 *@param	buff	現在のファイルポインタ
 *@param	data	データ格納先
 *@param	num		数
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void getHeaderData(char* buff, RES_HEADER_SUB* data, int num)
{
	int i;		// ループ用
	char* file_path;	// ファイルパス
	char* id;			// ファイルパス

	getOneData(buff, &file_path, &id);	// １つのデータ格納
	setOneData(file_path, id, &data[0]);
	for(i=1;i<num;i++){
		getOneData(NULL, &file_path, &id);	// １つのデータ格納
		setOneData(file_path, id, &data[i]);
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	１つのデータ取得
 *
 *@param	buff		最初以外はNULL
 *@param	file_path	ファイルパス
 *@param	id			ID
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void getOneData(char* buff, char** file_path, char** id)
{
	*file_path	= strtok(buff, ", \n");
	*id			= strtok(NULL, ", \n");
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	１つのデータを設定
 *
 *@param	fiel_path	ファイルパス
 *@param	id			id
 *@param	data		格納先
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void setOneData(char* file_path, char* id, RES_HEADER_SUB* data)
{
	data->id		= atoi(id);
	strcpy(data->file_path, file_path);
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	バッファのコピーを作成
 *
 *@param	buff	コピーするバッファ
 *@param	heap	使用するヒープ
 *
 *@return
 *
 *
 */
//-----------------------------------------------------------------------------
static char* makeCopyStr(const char* buff, int heap)
{
	int size;
	char* copy;

	size = strlen(buff);
	size++;

	copy = sys_AllocMemoryLo(heap, size);
	strcpy(copy, buff);

	return copy;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	コピーを破棄
 *
 *@param	copy	コピー
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void delCopyStr(char* copy)
{
	sys_FreeMemoryEz(copy);
}






//-----------------------------------------------------------------------------
/**
*
*	テクスチャ管理リソースマネージャ
* 
*/
//-----------------------------------------------------------------------------

//----------------------------------------------------------------------------
/**
 *
 *@brief	リソース管理マネージャー実態部作成
 *
 *@param	num		データ管理テーブル数
 *
 *@return	TEXRES_MANAGER_PTR		管理データポインタ
 *
 * ●管理テーブル領域の確保
 * ●管理テーブル領域の初期化
 *
 */
	//-----------------------------------------------------------------------------
TEXRES_MANAGER_PTR TEXRESM_Init(int num, int heap)
{
	TEXRES_MANAGER_PTR resm;
	int i;
	
	resm		= sys_AllocMemory( heap, sizeof(TEXRES_MANAGER) );
	
	resm->resm	= RESM_Init( num, heap );

	resm->tobj	= sys_AllocMemory( heap, sizeof(TEXRES_OBJ) * num );

	for(i=0;i<num;i++){
		cleanTEXRES_OBJ( resm->tobj + i );
	}

	return resm;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	リソース管理データ破棄
 *
 *@param	resm	リソース管理データ
 *
 *@return	none
 *
 *	●読み込んだリソースを破棄
 *	●管理テーブル領域を破棄
 */
//-----------------------------------------------------------------------------
void TEXRESM_Delete(TEXRES_MANAGER_PTR resm)
{
	GF_ASSERT(resm);
	
	// 登録されているリソース破棄
	TEXRESM_DeleteAllRes( resm );
	
	// 使用していたリソースマネージャ破棄
	RESM_Delete( resm->resm );
	
	sys_FreeMemoryEz( resm->tobj );
	sys_FreeMemoryEz( resm );
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	残り登録可能数を取得
 *
 *@param	resm	取得するリソース管理データ
 *
 *@return	int		残り登録可能数
 *
 *
 */
//-----------------------------------------------------------------------------
int TEXRESM_GetRest(CONST_TEXRES_MANAGER_PTR resm)
{
	GF_ASSERT(resm);

	return RESM_GetRest( resm->resm );
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	IDが重複しないかを取得
 *
 *@param	resm	取得するリソース管理データ
 *@param	id		チェックするID
 *
 *@retval	TRUE	重複しない
 *@retval	FALSE	重複する
 *
 *
 */
//-----------------------------------------------------------------------------
BOOL TEXRESM_CheckID(CONST_TEXRES_MANAGER_PTR resm, int id)
{
	GF_ASSERT(resm);

	return RESM_CheckID( resm->resm, id );
}

//----------------------------------------------------------------------------
/**
 *	
 *@brief	リソースの登録
 *
 *@param	resm	登録するリソース管理データポインタ
 *@param	res		リソース
 *@param	id		登録ID	（＊重複注意）
 *@param	texcut_flg	テクスチャカット　有無　フラグ
 *@param	heap		テクスチャカットワーク　ヒープ
 *
 *@retval	TEXRES_OBJ_PTR	登録成功
 *@retval	NULL		登録失敗	登録テーブルが満杯
 *
 * ●パスのリソースを読み込んで、管理データに設定
 *
 */
//-----------------------------------------------------------------------------
TEXRES_OBJ_PTR TEXRESM_AddResNormal(CONST_TEXRES_MANAGER_PTR resm, void* res, int id, u32 texcut_flg, u32 heap)
{
	TEXRES_OBJ_PTR tobj;
	void * buff;

	GF_ASSERT(resm);	
	tobj = getCleanTEXRES_OBJ( resm );

	// テクスチャ実データ破棄有無フラグ
	tobj->cuttex_flag = texcut_flg;
	
	// テクスチャ実データ破棄の有無から
	// テクスチャ実データ破棄後のデータサイズのワークを作成
	if( tobj->cuttex_flag == TEXRESM_TEX_CUT_TRUE ){
		// テクスチャ実データ破棄されたテクスチャリソースデータを作成
		buff = MakeCutTexWork( res, heap );
		tobj->p_cutTex = res;
	}else{
		// テクスチャ破棄しないときはresをそのまま設定
		buff = res;
		tobj->p_cutTex = NULL;
	}
	tobj->resobj = RESM_AddResNormal( resm->resm, buff, id );

	return tobj;
}

//----------------------------------------------------------------------------
/**
 *	
 *@brief	リソースの登録とVramKeyの取得を行う
 *
 *@param	resm	登録するリソース管理データポインタ
 *@param	res		リソース
 *@param	id		登録ID	（＊重複注意）
 *@param	texcut_flg	テクスチャカット　有無　フラグ
 *@param	heap	リソース読み込みに使用するヒープ
 *
 *@retval	TEXRES_OBJ_PTR	登録成功
 *@retval	NULL		登録失敗	登録テーブルが満杯
 *
 * ●処理の流れ
 *	１：パスのリソースを読み込む
 *	２：VramKeyを取得
 */
//-----------------------------------------------------------------------------
TEXRES_OBJ_PTR TEXRESM_AddAndAllocVramKeyResNormal(TEXRES_MANAGER_PTR resm, void* res, int id, u32 texcut_flg, int heap)
{
	TEXRES_OBJ_PTR tobj;

	// リソースマネージャに登録
	tobj = TEXRESM_AddResNormal( resm, res, id, texcut_flg, heap );

	// VramKeyの取得
	TEXRESM_AllocVramKeyPTR( tobj );
	
	return tobj;
}


//----------------------------------------------------------------------------
/**
 *
 *@brief	リソースの破棄
 *
 *@param	resm	破棄するリソースが登録されている管理データポインタ
 *@param	r_obj	破棄するリソースオブジェ
 *
 * ●読み込んだリソースを破棄し、管理データを初期化
 */
//-----------------------------------------------------------------------------
void TEXRESM_DeleteRes(TEXRES_MANAGER_PTR resm, TEXRES_OBJ_PTR r_obj)
{
	int check;
	
	GF_ASSERT(resm);	
	GF_ASSERT(r_obj);

	// テクスチャカット用のリソースなのにテクスチャカットされていないとき
	// の処理
	if( (r_obj->cuttex_flag == TEXRESM_TEX_CUT_TRUE) &&
		(r_obj->cut_flag == FALSE) ){
		sys_FreeMemoryEz( r_obj->p_cutTex );
		r_obj->cuttex_flag = NULL;
	}
	
	if(r_obj->resobj){
		RESM_DeleteRes( resm->resm, r_obj->resobj );
	}

	// テクスチャキーがあるときは破棄
	if(r_obj->texKey != NNS_GFD_ALLOC_ERROR_TEXKEY){
		check = NNS_GfdFreeTexVram( r_obj->texKey );
		GF_ASSERT_MSG(check == 0, "テクスチャキー破棄失敗");
	}
	if(r_obj->tex4x4Key != NNS_GFD_ALLOC_ERROR_TEXKEY){
		check = NNS_GfdFreeTexVram( r_obj->tex4x4Key );
		GF_ASSERT_MSG(check == 0, "テクスチャキー破棄失敗");
	}
	// パレットキー破棄
	if(r_obj->plttKey != NNS_GFD_ALLOC_ERROR_PLTTKEY){
		check = NNS_GfdFreePlttVram( r_obj->plttKey );
		GF_ASSERT_MSG(check == 0, "パレットキー破棄失敗");
	}

	cleanTEXRES_OBJ( r_obj );
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	IDでリソースの破棄
 *
 *@param	resm	破棄するリソースが登録されている管理データポインタ
 *@param	id		破棄するリソースのID	(管理ID)
 *
 * ●読み込んだリソースを破棄し、管理データを初期化
 */
//-----------------------------------------------------------------------------
void TEXRESM_DeleteResID(TEXRES_MANAGER_PTR resm, int id)
{
	TEXRES_OBJ_PTR tobj;
	GF_ASSERT( resm );

	tobj = TEXRESM_GetResObj( resm, id );

	TEXRESM_DeleteRes( resm, tobj );
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	全リソースの破棄
 *
 *@param	resm	破棄するリソースが登録されている管理データポインタ
 *
 * ●読み込んだリソースを破棄し、管理データを初期化
 */
//-----------------------------------------------------------------------------
void TEXRESM_DeleteAllRes(TEXRES_MANAGER_PTR resm)
{
	int i;		// ループ用
	GF_ASSERT(resm);
	GF_ASSERT(resm->tobj);
	
	for( i = 0; i < resm->resm->max; i++ ){
		if(resm->tobj[ i ].resobj){
			TEXRESM_DeleteRes( resm, resm->tobj + i );
		}
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	リソースオブジェクトデータポインタを取得
 *
 *@param	resm		リソース管理データ
 *@param	id			リソースのID	(管理ID)
 *
 *@retval	NULL		登録されていない
 *@retval	TEXRES_OBJ_PTR	登録されているリソースオブジェポインタ
 *
 *
 */
//-----------------------------------------------------------------------------
TEXRES_OBJ_PTR TEXRESM_GetResObj(CONST_TEXRES_MANAGER_PTR resm, int id)
{
	int i;
	int res_id;
	
	GF_ASSERT( resm );

	for(i=0;i<resm->resm->max;i++){
		
		if( resm->tobj[ i ].resobj ){
			res_id = TEXRESM_GetID( resm->tobj + i );
			if( res_id == id ){
				return resm->tobj + i;
			}
		}
	}

	return NULL;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	登録されているIDを取得
 *
 *@param	r_obj		リソースオブジェ
 *
 *@retval	int			管理ID
 *
 *
 */
//-----------------------------------------------------------------------------
int TEXRESM_GetID(CONST_TEXRES_OBJ_PTR r_obj)
{
	GF_ASSERT( r_obj );

	return RESM_GetID( r_obj->resobj );
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	登録されているIDを設定
 *
 *@param	resm		リソースマネージャ
 *@param	r_obj		リソースオブジェ
 *@param	id			設定するID
 *
 *@retval	none
 *
 *
 */
//-----------------------------------------------------------------------------
void TEXRESM_SetID(TEXRES_MANAGER_PTR resm, TEXRES_OBJ_PTR r_obj, int id)
{
	GF_ASSERT( resm );
	GF_ASSERT( r_obj );

	RESM_SetID( resm->resm, r_obj->resobj, id );
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	登録されているテクスチャリソースデータを取得
 *
 *@param	r_obj		テクスチャリソースオブジェ
 *
 *@retval	NULL		登録されていない
 *@retval	NULL以外	登録されているテクスチャリソースポインタ
 *
 *
 */
//-----------------------------------------------------------------------------
NNSG3dResTex* TEXRESM_GetResPTR(CONST_TEXRES_OBJ_PTR r_obj)
{
	GF_ASSERT( r_obj );

	return getTexRes( r_obj );
}

//----------------------------------------------------------------------------
/**
 * IDで取得
 *
 *@brief	登録されているテクスチャリソースデータを取得
 *
 *@param	resm		テクスチャリソースマネージャ
 *@param	id			登録ID
 *
 *@retval	NULL		登録されていない
 *@retval	NULL以外	登録されているテクスチャリソースポインタ
 *
 *
 */
//-----------------------------------------------------------------------------
NNSG3dResTex* TEXRESM_GetResID(CONST_TEXRES_MANAGER_PTR resm, int id)
{
	TEXRES_OBJ_PTR resobj;
	resobj = TEXRESM_GetResObj( resm, id );

	return getTexRes( resobj );
}

//----------------------------------------------------------------------------
/**
 * ●オブジェクトポインタ
 *
 *	@brief	テクスチャリソースをVramに転送
 *
 *	@param	r_obj	テクスチャリソースオブジェ
 *
 *	@return	none
 *
 * この関数を呼ぶとVramKeyが作成されます。
 * 確保したVramKeyはTEXRESM_DeleteRes系関数でリソースと一緒に破棄されます
 *
 */
//-----------------------------------------------------------------------------
void TEXRESM_TexLoadPTR( TEXRES_OBJ_PTR r_obj )
{
	NNSG3dResTex* tex_res;
	
	GF_ASSERT(r_obj);
	GF_ASSERT_MSG( r_obj->cut_flag == FALSE, "テクスチャ実データ破棄済みなので転送はできません。" );
	
	// VramKeyを取得したデータかチェック
	if( r_obj->plttKey == NNS_GFD_ALLOC_ERROR_PLTTKEY ){
		GF_ASSERT_MSG(0, "VramKeyを取得していないのに転送しようとしています。TEXRESM_AllocVramKey関数を実行してからTEXRESM_TexLoad関数を実行してください。");
		return ;
	}

	// TexCutが無いときはそのままリソースを取得
	// TexCutするときは,p_cutTexを取得
	tex_res = getTexRes_CheckCutTex( r_obj );
	
	// Vram領域に転送
	loadTexRes( tex_res, r_obj );
}

//----------------------------------------------------------------------------
/**
 * ●ID
 *
 *	@brief	テクスチャリソースをVramに転送
 *
 *	@param	resm		テクスチャリソースマネージャ
 *	@param	id			登録ID
 *
 *	@return	none
 *
 * この関数を呼ぶとVramKeyが作成されます。
 * 確保したVramKeyはTEXRESM_DeleteRes系関数でリソースと一緒に破棄されます
 *
 */
//-----------------------------------------------------------------------------
void TEXRESM_TexLoadID( TEXRES_MANAGER_PTR resm, int id )
{
	TEXRES_OBJ_PTR resobj;
	
	GF_ASSERT( resm );
	resobj = TEXRESM_GetResObj( resm, id );


	TEXRESM_TexLoadPTR( resobj );
}

//----------------------------------------------------------------------------
/**
 * ●オブジェクトポインタ
 *
 *	@brief	テクスチャリソースの実データを破棄
 *
 *	@param	r_obj	テクスチャリソースオブジェ
 *
 *	@return	none
 *
 */
//-----------------------------------------------------------------------------
void TEXRESM_CutTexPTR( TEXRES_OBJ_PTR r_obj )
{
	void* buff;
	
	GF_ASSERT(r_obj);

	// カットして良いオブジェクトかチェック
	if( r_obj->cuttex_flag == TEXRESM_TEX_CUT_FALSE ){
		// "テクスチャ実データ破棄できないオブジェクトです"
		GF_ASSERT(0);
		return ;
	}
	
	//  破棄済みでないかチェック
	if( r_obj->cut_flag ){
		// "破棄済みです"
		GF_ASSERT(0);
		return ;
	}

	// テクスチャリソースから
	// テクスチャキーを破棄
	releaseTexkeyRes( getTexRes_CheckCutTex( r_obj ) );
	setTexkeyRes( getTexRes( r_obj ), r_obj->texKey, r_obj->tex4x4Key, r_obj->plttKey );

	// メモリ破棄
	sys_FreeMemoryEz( r_obj->p_cutTex );
	r_obj->p_cutTex = NULL;
	
	// テクスチャ実データ破棄完了
	r_obj->cut_flag = TRUE;
}

//----------------------------------------------------------------------------
/**
 * ●ID
 *
 *	@brief	テクスチャリソースの実データを破棄
 *
 *	@param	resm		テクスチャリソースマネージャ
 *	@param	id			登録ID
 *
 *	@return	none
 *
 */
//-----------------------------------------------------------------------------
void TEXRESM_CutTexID( TEXRES_MANAGER_PTR resm, int id )
{
	TEXRES_OBJ_PTR resobj;
	GF_ASSERT( resm );
	resobj = TEXRESM_GetResObj( resm, id );

	TEXRESM_CutTexPTR( resobj );
}

//----------------------------------------------------------------------------
/**
 * ●オブジェクトポインタで確保
 *
 *	@brief	テクスチャキーをVramManagerから確保します
 *
 *	@param	r_obj		リソースオブジェ
 *
 *	@return none
 *
 * 確保したVramKey（テクスチャキー　パレットキー）
 * はTEXRESM_Delete～関数で破棄されます。
 *
 *
 */
//-----------------------------------------------------------------------------
void TEXRESM_AllocVramKeyPTR( TEXRES_OBJ_PTR r_obj )
{
	NNSG3dResTex* tex_res;

	GF_ASSERT( r_obj );
	GF_ASSERT_MSG( r_obj->cut_flag == FALSE, "テクスチャ実データ破棄済みなのでVramKey確保できません。" );
	
	// VramKey取得済みでないかチェック
	if( r_obj->plttKey != NNS_GFD_ALLOC_ERROR_PLTTKEY ){
		GF_ASSERT_MSG(0, "VramKey取得済みです");
		return ;
	}

	// TexCutが無いときはそのままリソースを取得
	// TexCutするときは,p_cutTexを取得
	tex_res = getTexRes_CheckCutTex( r_obj );
	
	// Vramkeyの取得
	getVramkey( tex_res, &r_obj->texKey, &r_obj->tex4x4Key, &r_obj->plttKey );
}

//----------------------------------------------------------------------------
/**
 * ●IDで確保
 *
 *	@brief	テクスチャキーをVramManagerから確保します
 *
 *	@param	resm		テクスチャリソースマネージャ
 *	@param	id			登録ID
 *
 *	@return none
 *
 * 確保したVramKey（テクスチャキー　パレットキー）
 * はTEXRESM_Delete～関数で破棄されます。
 *
 *
 */
//-----------------------------------------------------------------------------
void TEXRESM_AllocVramKeyID( CONST_TEXRES_MANAGER_PTR resm, int id )
{
	TEXRES_OBJ_PTR resobj;
	
	GF_ASSERT( resm );
	resobj = TEXRESM_GetResObj( resm, id );


	TEXRESM_AllocVramKeyPTR( resobj );
}


//----------------------------------------------------------------------------
/**
 *
 *	@brief	テクスチャリソースをVramに転送
 *
 *	@param	r_obj		テクスチャリソースオブジェ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void TEXRESM_TexLoadAndCutTexPTR( TEXRES_OBJ_PTR r_obj )
{
	TEXRESM_TexLoadPTR( r_obj );
	TEXRESM_CutTexPTR( r_obj );
}

//----------------------------------------------------------------------------
/**
 * IDで取得
 *
 *	@brief	テクスチャリソースをVramに転送
 *
 *	@param	resm		テクスチャリソースマネージャ
 *	@param	id			登録ID
 *
 *	@return	none
 *
 */
//-----------------------------------------------------------------------------
void TEXRESM_TexLoadAndCutTexID( TEXRES_MANAGER_PTR resm, int id )
{
	TEXRES_OBJ_PTR resobj;
	GF_ASSERT( resm );
	resobj = TEXRESM_GetResObj( resm, id );

	TEXRESM_TexLoadAndCutTexPTR( resobj );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	テクスチャキーの取得
 *
 *	@param	r_obj	テクスチャリソースオブジェ
 *
 *	@return	テクスチャキー
 *
 *
 */
//-----------------------------------------------------------------------------
NNSGfdTexKey TEXRESM_GetTexKeyPTR( CONST_TEXRES_OBJ_PTR r_obj )
{
	GF_ASSERT(r_obj);

	return r_obj->texKey;
}

//----------------------------------------------------------------------------
/**
 * IDで取得
 *
 *	@brief	テクスチャキーの取得
 *
 *	@param	resm		テクスチャリソースマネージャ
 *	@param	id			登録ID
 *
 *	@return	テクスチャキー
 *
 *
 */
//-----------------------------------------------------------------------------
NNSGfdTexKey TEXRESM_GetTexKeyID( CONST_TEXRES_MANAGER_PTR resm, int id )
{
	TEXRES_OBJ_PTR resobj;
	GF_ASSERT( resm );
	resobj = TEXRESM_GetResObj( resm, id );

	return TEXRESM_GetTexKeyPTR( resobj );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	テクスチャ4x4キーの取得
 *
 *	@param	r_obj	テクスチャリソースオブジェ
 *
 *	@return	テクスチャキー
 *
 *
 */
//-----------------------------------------------------------------------------
NNSGfdTexKey TEXRESM_GetTex4x4KeyPTR( CONST_TEXRES_OBJ_PTR r_obj )
{
	GF_ASSERT(r_obj);

	return r_obj->tex4x4Key;
}

//----------------------------------------------------------------------------
/**
 * IDで取得
 *
 *	@brief	テクスチャ4x4キーの取得
 *
 *	@param	resm		テクスチャリソースマネージャ
 *	@param	id			登録ID
 *
 *	@return	テクスチャキー
 *
 *
 */
//-----------------------------------------------------------------------------
NNSGfdTexKey TEXRESM_GetTex4x4KeyID( CONST_TEXRES_MANAGER_PTR resm, int id )
{
	TEXRES_OBJ_PTR resobj;
	GF_ASSERT( resm );
	resobj = TEXRESM_GetResObj( resm, id );

	return TEXRESM_GetTex4x4KeyPTR( resobj );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	パレットキーの取得
 *
 *	@param	r_obj	テクスチャリソースオブジェ
 *
 *	@return	パレットキー
 *
 *
 */
//-----------------------------------------------------------------------------
NNSGfdPlttKey TEXRESM_GetPlttKeyPTR( CONST_TEXRES_OBJ_PTR r_obj )
{
	GF_ASSERT(r_obj);

	return r_obj->plttKey;
}

//----------------------------------------------------------------------------
/**
 * IDで取得
 *
 *	@brief	パレットキーの取得
 *
 *	@param	resm		テクスチャリソースマネージャ
 *	@param	id			登録ID
 *
 *	@return	パレットキー
 *
 *
 */
//-----------------------------------------------------------------------------
NNSGfdPlttKey TEXRESM_GetPlttKeyID( CONST_TEXRES_MANAGER_PTR resm, int id )
{
	TEXRES_OBJ_PTR resobj;
	GF_ASSERT( resm );
	resobj = TEXRESM_GetResObj( resm, id );

	return TEXRESM_GetPlttKeyPTR( resobj );
}

//----------------------------------------------------------------------------
/**
 * ●オブジェクトポインタ
 *
 *	@brief	指定されたVramKey位置にテクスチャを転送します。
 *
 *	@param	r_obj		テクスチャリソースオブジェ
 *	@param	texkey		テクスチャキー
 *	@param	tex4x4key	テクスチャ4x4キー
 *	@param	plttkey		パレットキー
 *
 *	@return	none
 *
 * 引数のtexkey・plttkeyデータはテクスチャリソースマネージャでは
 * 管理しませんので、各自確保、破棄してください。
 *
 */
//-----------------------------------------------------------------------------
void TEXRESM_TexLoadOfKeyPTR( TEXRES_OBJ_PTR r_obj, NNSGfdTexKey texkey, NNSGfdTexKey tex4x4key, NNSGfdPlttKey plttkey )
{
	NNSG3dResTex* res;
	
	GF_ASSERT( r_obj );
	GF_ASSERT_MSG( r_obj->cut_flag == FALSE, "テクスチャ実データが削除されているので転送できません。" );

	// TexCutが無いときはそのままリソースを取得
	// TexCutするときは,p_cutTexを取得
	res = getTexRes_CheckCutTex( r_obj );
	
	NNS_G3dTexSetTexKey(res, texkey, tex4x4key);
	NNS_G3dPlttSetPlttKey(res, plttkey);

	DC_FlushRange( res, res->header.size );
	// VRAMへのロード
	NNS_G3dTexLoad(res, TRUE);
	NNS_G3dPlttLoad(res, TRUE);
}

//----------------------------------------------------------------------------
/**
 *	●ID
 * 
 *	@brief	指定されたVramKey位置にテクスチャを転送します。
 *
 *	@param	resm		テクスチャリソースマネージャ
 *	@param	id			登録ID
 *	@param	texkey		テクスチャキー
 *	@param	tex4x4key	テクスチャ4x4キー
 *	@param	plttkey		パレットキー
 *
 *	@return	none
 *
 * 引数のtexkey・plttkeyデータはテクスチャリソースマネージャでは
 * 管理しませんので、各自確保、破棄してください。
 *
 */
//-----------------------------------------------------------------------------
void TEXRESM_TexLoadOfKeyID( TEXRES_MANAGER_PTR resm, int id, NNSGfdTexKey texkey, NNSGfdTexKey tex4x4key, NNSGfdPlttKey plttkey )
{
	TEXRES_OBJ_PTR resobj;
	GF_ASSERT( resm );
	resobj = TEXRESM_GetResObj( resm, id );

	TEXRESM_TexLoadOfKeyPTR( resobj, texkey, tex4x4key, plttkey );
}


//----------------------------------------------------------------------------
/**
 *
 *	@brief	空いているテクスチャリソースオブジェの取得
 *
 *	@param	resm	リソースマネージャ
 *
*	@return	空いているテクスチャリソースオブジェ
 *
 *
 */
//-----------------------------------------------------------------------------
static TEXRES_OBJ_PTR getCleanTEXRES_OBJ(CONST_TEXRES_MANAGER_PTR resm)
{
	int i;

	for(i=0;i<resm->resm->max;i++){
		if(resm->tobj[i].resobj == NULL){
			return resm->tobj + i;
		}
	}

	return NULL;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	テクスチャリソースオブジェを初期化
 *
 *	@param	obj		テクスチャリソースオブジェ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void cleanTEXRES_OBJ(TEXRES_OBJ_PTR obj)
{
	obj->resobj		= NULL;
	obj->texKey		= NNS_GFD_ALLOC_ERROR_TEXKEY;
	obj->tex4x4Key	= NNS_GFD_ALLOC_ERROR_TEXKEY;
	obj->plttKey	= NNS_GFD_ALLOC_ERROR_PLTTKEY;
	obj->cut_flag	= FALSE;
	obj->p_cutTex	= NULL;
	obj->cut_flag	= FALSE;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	テクスチャリソースの取得
 *
 *	@param	r_obj	テクスチャリソースオブジェ
 *
 *	@return	テクスチャリソース
 *
 *
 */
//-----------------------------------------------------------------------------
static NNSG3dResTex* getTexRes( CONST_TEXRES_OBJ_PTR r_obj )
{
	void* buff;
	NNSG3dResTex* o_tex;

	buff = RESM_GetRes( r_obj->resobj );

	o_tex = NNS_G3dGetTex(buff);

	return o_tex;
}

//----------------------------------------------------------------------------
/**
 *	@brief	テクスチャ実データの入っている　テクスチャリソース取得
 *
 *	@param	r_obj	テクスチャリソースオブジェ
 *
 *	@return	テクスチャリソース
 */
//-----------------------------------------------------------------------------
static NNSG3dResTex* getTexRes_CheckCutTex( CONST_TEXRES_OBJ_PTR r_obj )
{
	void* buff;
	NNSG3dResTex* o_tex;

	// TexCutが無いときはそのままリソースを取得
	// TexCutするときは,p_cutTexを取得
	if( r_obj->cuttex_flag == TEXRESM_TEX_CUT_FALSE ){
		// テクスチャリソースの取得
		buff = RESM_GetRes( r_obj->resobj );
	}else{
		buff = r_obj->p_cutTex;
	}
	o_tex = NNS_G3dGetTex(buff);
	return o_tex;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	テクスチャリソースデータ用のVramkeyを取得
 *
 *	@param	res		テクスチャリソース
 *	@param	tex		テクスチャキー
 *	@param	tex4x4	4x4圧縮テクスチャ
 *	@param	pltt	パレットキー
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void getVramkey( const NNSG3dResTex* res, NNSGfdTexKey* tex, NNSGfdTexKey* tex4x4, NNSGfdPlttKey* pltt )
{
	u32 tex_size;
	u32 tex_4x4_size;
	u32 pltt_size;

	tex_size = NNS_G3dTexGetRequiredSize( res );
	tex_4x4_size = NNS_G3dTex4x4GetRequiredSize(res);
	pltt_size = NNS_G3dPlttGetRequiredSize( res );


	if(tex_size != 0){
		*tex = NNS_GfdAllocTexVram( tex_size, FALSE, 0 );
		// テクスチャキー確保失敗
//		GF_ASSERT(*tex != NNS_GFD_ALLOC_ERROR_TEXKEY );
	}
	if(tex_4x4_size != 0){
		*tex4x4 = NNS_GfdAllocTexVram( tex_4x4_size, TRUE, 0 );
		// テクスチャキー確保失敗
//		GF_ASSERT(*tex4x4 != NNS_GFD_ALLOC_ERROR_TEXKEY );
	}
	if(pltt_size != 0){
		*pltt = NNS_GfdAllocPlttVram( pltt_size, 
			res->tex4x4Info.flag & NNS_G3D_RESPLTT_USEPLTT4, 0 );
		// パレットキー確保失敗
//		GF_ASSERT(*pltt != NNS_GFD_ALLOC_ERROR_PLTTKEY );
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	テクスチャリソース読み込み
 *
 *	@param	res		テクスチャリソース
 *	@param	r_obj	テクスチャリソースオブジェ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void loadTexRes( NNSG3dResTex* res, TEXRES_OBJ_PTR r_obj )
{
	setTexkeyRes( res, r_obj->texKey, r_obj->tex4x4Key, r_obj->plttKey );

	DC_FlushRange( res, res->header.size );
	// VRAMへのロード
	NNS_G3dTexLoad(res, TRUE);
	NNS_G3dPlttLoad(res, TRUE);
}

//----------------------------------------------------------------------------
/**
 *	@brief	テクスチャキーをテクスチャリソースに設定
 *
 *	@param	res			テクスチャリソース
 *	@param	tex			テクスチャキー
 *	@param	tex4x4		テクスチャキー	4x4
 *	@param	pltt		パレットキー
 */
//-----------------------------------------------------------------------------
static void setTexkeyRes( NNSG3dResTex* res, NNSGfdTexKey tex, NNSGfdTexKey tex4x4, NNSGfdPlttKey pltt )
{
	NNS_G3dTexSetTexKey(res, tex, tex4x4);
	NNS_G3dPlttSetPlttKey(res, pltt);
}

//----------------------------------------------------------------------------
/**
 *	@brief	テクスチャキーをテクスチャリソースから取る
 *
 *	@param	res		テクスチャリソース
 */
//-----------------------------------------------------------------------------
static void releaseTexkeyRes( NNSG3dResTex* res )
{
	NNSGfdTexKey	texKey;		// テクスチャキー
	NNSGfdTexKey	tex4x4Key;	// 4x4テクスチャキー
	NNSGfdPlttKey	plttKey;	// パレットキー

	// VramKeyを付け替える
	NNS_G3dTexReleaseTexKey( res, &texKey, &tex4x4Key );
	plttKey = NNS_G3dPlttReleasePlttKey( res );	
}

// テクスチャリソースを削除したNNSG3dResTexを作成する関数郡
//----------------------------------------------------------------------------
/**
 *
 *	@brief	テクスチャ実データを破棄したサイズのテクスチャリソース作成
 *
 *	@param	p_cuttex	テクスチャ実データを破棄するテクスチャリソース
 *
 *	@return	none	
 *
 *
 */
//-----------------------------------------------------------------------------
static void* MakeCutTexWork( void* p_cuttex, u32 heap )
{
	u32	data_size;		// テクスチャ実データを入れないテクスチャリソースサイズ
	void* buff;
	// テクスチャ実データを入れないテクスチャリソースサイズ取得
	data_size = GetCutTexDataSize( p_cuttex );

	buff = sys_AllocMemory( heap, data_size );

	// 先頭からbuff分コピーする
	memcpy( buff, p_cuttex, data_size );
	return buff;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	テクスチャ実データを入れないテクスチャリソースサイズの計算
 *
 *	@param	p_cuttex	計算するテクスチャリソースデータ
 *
 *	@return	テクスチャ実データを入れないテクスチャリソースのサイズ
 *
 *
 */
//-----------------------------------------------------------------------------
static u32 GetCutTexDataSize( const void* p_cuttex )
{
	NNSG3dResTex* p_tex;
	u8* tex_top;		// テクスチャデータ先頭データ
	u32 new_size;		// 新しいデータサイズ

	p_tex = NNS_G3dGetTex( p_cuttex );
	GF_ASSERT_MSG( p_tex, "このリソースにはテクスチャデータがありません。" );

	// テクスチャの先頭アドレス計算
	tex_top = (u8*)p_tex + p_tex->texInfo.ofsTex;

	// ヒープの先頭からテクスチャイメージまでのサイズ
    new_size = (u32)(tex_top - (u8*)p_cuttex);

	return new_size;
}
