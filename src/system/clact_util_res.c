//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *@file		clact_util_res.c
 *@brief	セルアクターユーティリティシステム
 *@author	tomoya takahashi	
 *@data		2005.09.01
 *
 *
 * このシステムは、CLACTを簡単に使用できるようリソースを管理する
 * システムをまとめた物です。
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

#include "system.h"
#include "assert.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "res_manager.h"
#include "include/system/arc_tool.h"
#include "include/system/arc_util.h"

#define __CLACT_UTIL_H_RES_GLOBAL
#include "include/system/clact_util_res.h"


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
//	セルアクターリソースマネージャ
//	オブジェ
//	
//=====================================
typedef struct _CLACT_U_RES_OBJ{
	RES_OBJ_PTR		res_obj;		// リソースオブジェ
	int				type;			// リソースタイプ
	void*			res_ex;			// 拡張データ	(アンパック後のデータを格納したり、
									// それぞれのリソースに違うデータを格納)
} CLACT_U_RES_OBJ;

//-------------------------------------
//	
//	リソースマネージャー管理構造体
//	
//=====================================
typedef struct _CLACT_U_RES_MANAGER{
	RES_MANAGER_PTR res_manager;	// 使用するリソースマネージャー
	CLACT_U_RES_OBJ*	resObj;		// リソースオブジェクト
	int					tbl_num;	// テーブル数
	int					tbl_now;	// 今の登録数
	int					type;		// リソースタイプ
} CLACT_U_RES_MANAGER;

//-------------------------------------
//	
//	データ管理ヘッダー
//	
//=====================================
typedef struct _CLACT_U_RES_HEADER_SUB{
	int		id;
	char	file_path[64];
	int		ex[2];			// 拡張データ
} CLACT_U_RES_HEADER_SUB;

//-------------------------------------
//	
//	アーカイブデータ管理ヘッダー
//	
//=====================================
typedef struct _CLACT_U_RES_HEADER_SUBARC{
	int		arcFile;		// アーカイブファイルID
	int		dataIdx;		// データidx
	BOOL	compFlag;		// 圧縮フラグ
	int		id;
	int		ex[2];			// 拡張データ
} CLACT_U_RES_HEADER_SUBARC;

//-------------------------------------
//	
//	リソースマネージャーヘッダー構造体
//	
//=====================================
typedef struct _CLACT_U_RES_HEADER{
	void*			tbl;			// ヘッダーテーブル
	int				tbl_num;		// テーブル数
	int				type;			// リソースタイプ
	u8				arc_flag;		// アーカイブされたデータか
} CLACT_U_RES_HEADER;

//-----------------------------------------------
//
//	個々の拡張データ
//
//==============================================
//-------------------------------------
//	
//	キャラクタ
//	
//=====================================
typedef struct {
	NNSG2dCharacterData* pCharData;		// キャラクタデータ
	int	vram_type;						// Vramタイプ
} CLACT_U_RES_EX_CHAR;

//-------------------------------------
//	
//	パレット
//	
//=====================================
typedef struct {
	NNSG2dPaletteData* pPlttData;		// パレットデータ
	int	vram_type;						// Vramタイプ
	int	pltt_num;						// パレットナンバー
} CLACT_U_RES_EX_PLTT;

//-------------------------------------
//	
//	セル
//	
//=====================================
typedef struct {
	NNSG2dCellDataBank* pCellData;		// セルデータ
} CLACT_U_RES_EX_CELL;

//-------------------------------------
//	
//	セルアニメ
//	
//=====================================
typedef struct {
	NNSG2dAnimBankData* pCellANMData;	// セルアニメデータ
} CLACT_U_RES_EX_CELLANM;

//-------------------------------------
//	
//	マルチセル
//	
//=====================================
typedef struct {
	NNSG2dMultiCellDataBank* pMultiData;	// マルチセルデータ
} CLACT_U_RES_EX_MULTI;

//-------------------------------------
//	
//	マルチセルアニメ
//	
//=====================================
typedef struct {
	NNSG2dAnimBankData* pMultiANMData;		// マルチセルアニメデータ
} CLACT_U_RES_EX_MULTIANM;
//-----------------------------------------------------------------------------
/**
 *					プロトタイプ宣言
*/
//-----------------------------------------------------------------------------
//	テーブル用
static CLACT_U_RES_OBJ_PTR getCleanResObj(CLACT_U_RES_MANAGER_PTR resm);
static void loadOneData(CLACT_U_RES_MANAGER_PTR resm, CLACT_U_RES_OBJ_PTR resObj, const char* path, int id, int vram, int pltt_num, int type, int heap);
static void SetArcOneData(CLACT_U_RES_MANAGER_PTR resm, CLACT_U_RES_OBJ_PTR resObj, int arcFile, int dataIdx, BOOL compFlag, int id, int vram, int pltt_num, int type, int heap, u32 alloc_type);
static void SetArcOneData_ArcHandle(CLACT_U_RES_MANAGER_PTR resm, CLACT_U_RES_OBJ_PTR resObj, ARCHANDLE* arcHandle, int dataIdx, BOOL compFlag, int id, int vram, int pltt_num, int type, int heap, u32 alloc_type);
static void* ArcHandle_Load(ARCHANDLE* p_handle, u32 dataIdx, BOOL compressedFlag, u32 heapID, u32 alloc_type);


// それぞれの拡張データ作成
static void makeExData(CLACT_U_RES_OBJ_PTR resObj, int type, int vram_type, int pltt_num, int heap);
static CLACT_U_RES_EX_CHAR* makeExChar(void* res, int vram_type, int heap);
static CLACT_U_RES_EX_PLTT* makeExPltt(void* res, int vram_type, int pltt_num, int heap);
static CLACT_U_RES_EX_CELL* makeExCell(void* res, int heap);
static CLACT_U_RES_EX_CELLANM*	makeExCellAnm(void* res, int heap);
static CLACT_U_RES_EX_MULTI*	makeExMulti(void* res, int heap);
static CLACT_U_RES_EX_MULTIANM* makeExMultiAnm(void* res, int heap);

static void* getExData( CONST_CLACT_U_RES_OBJ_PTR resObj );


// それぞれの拡張データ破棄
static void delExData(CLACT_U_RES_OBJ_PTR resObj);


// ヘッダー読み込みよう
static int getHeaderType(char* buff);
static int getHeaderArc(char* buff);

static int getHeaderNum(char* buff, int type, int arcFlag);
static int getHeaderNumBinary( const CLACT_U_RES_HEADER_SUBARC* buff );
static void loadHeaderData(char* buff, int type, void* tbl, int num, int arcFlag);

static void loadHeaderCore(char* buff, char** file_path, char** id, char** vram, char** pltt, int type);
static void loadCharHeaderCore(char* buff, char** path, char** id, char** type);
static void loadPlttHeaderCore(char* buff, char** path, char** id, char** type, char** pltt_num);
static void loadKindCellHeaderCore(char* buff, char** path, char** id);
static void setDataHeader(CLACT_U_RES_HEADER_SUB* head, char* path, char* id, char* type, char* pltt_num);

static void loadHeaderCoreArc(char* buff, char** srcFile, char** dataIdx, char** compFlag, char** id, char** vram, char** pltt, int type);
static void loadCharHeaderCoreArc(char* buff, char** srcFile, char** dataIdx, char** compFlag, char** id, char** type);
static void loadPlttHeaderCoreArc(char* buff, char** srcFile, char** dataIdx, char** compFlag, char** id, char** type, char** pltt_num);
static void loadKindCellHeaderCoreArc(char* buff, char** srcFile, char** dataIdx, char** compFlag, char** id);
static void setDataHeaderArc(CLACT_U_RES_HEADER_SUBARC* head, char* arcFile, char* dataIdx, char* compFlag, char* id, char* type, char* pltt_num);

static char* makeCopyStr(const char* buff, int heap);
static void delCopyStr(char* copy);


//----------------------------------------------------------------------------
/**
 *
 *@brief	リソース管理マネージャー初期化
 *
 *@param	tbl_num			データ登録数
 *@param	res_type		リソースタイプ
 *@param	heap			使用するヒープ
 *
 *@return	CLACT_RES_MANAGER_PTR	セルアクターユーティリティリソースマネージャーポインタ
 *
 *
 */
//-----------------------------------------------------------------------------
CLACT_U_RES_MANAGER_PTR CLACT_U_ResManagerInit(int tbl_num, int res_type, int heap)
{
	CLACT_U_RES_MANAGER_PTR	resm;
	int	i;	// ループ用
	

	// リソース管理データ格納先を作成
	resm = sys_AllocMemory(heap, sizeof(CLACT_U_RES_MANAGER));
	
	// リソースマネージャー作成
	resm->res_manager = RESM_Init(tbl_num, heap);

	// オブジェ登録テーブル作成
	resm->resObj = sys_AllocMemory(heap, sizeof(CLACT_U_RES_OBJ)*tbl_num);
	memset(resm->resObj, 0, sizeof(CLACT_U_RES_OBJ)*tbl_num);
	
	resm->tbl_num = tbl_num;
	resm->tbl_now = 0;
	
	// リソースタイプ代入
	resm->type	= res_type;
	
	return resm;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	リソースマネージャーの破棄
 *
 *@param	resm	リソースマネージャー
 *	
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void CLACT_U_ResManagerDelete(CLACT_U_RES_MANAGER_PTR resm)
{
	GF_ASSERT(resm);
	GF_ASSERT(resm->res_manager);
	GF_ASSERT(resm->resObj);
	
	// 登録されているデータを全て破棄
	CLACT_U_ResManagerResDeleteAll(resm);
	
	// 確保したメモリを解放
	// リソースマネージャー破棄
	RESM_Delete(resm->res_manager);
	resm->res_manager = NULL;

	// オブジェ登録テーブル作成
	sys_FreeMemoryEz(resm->resObj);
	resm->resObj = NULL;
	 
	// リソース管理データ格納先を作成
	sys_FreeMemoryEz(resm);
	resm = NULL;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	リソースデータをヘッダーから読み込む（単発）
 *
 *@param	resm	リソースマネージャー
 *@param	head	ヘッダー
 *@param	no		ヘッダーの何番目を読み込むか
 *@param	heap	使用するヒープ
 *
 *@return	読み込んだデータ
 *
 *
 */
//-----------------------------------------------------------------------------
CLACT_U_RES_OBJ_PTR CLACT_U_ResManagerResAddHd(CLACT_U_RES_MANAGER_PTR resm, const CLACT_U_RES_HEADER_PTR head, int no, int heap)
{
	CLACT_U_RES_OBJ_PTR obj;
	CLACT_U_RES_HEADER_SUB*		hs;
	CLACT_U_RES_HEADER_SUBARC*	harc;
	

	GF_ASSERT(resm);
	GF_ASSERT(head);
	GF_ASSERT(head->tbl_num > no);
	GF_ASSERT_MSG(resm->type == head->type, "リソースタイプが違います" );
	
	obj = getCleanResObj(resm);
	GF_ASSERT_MSG(obj,  "もう空きのテーブルがありません" );
	if(head->arc_flag == 0){
		// 非アーカイブ用ヘッダ
		hs = (CLACT_U_RES_HEADER_SUB*)head->tbl + no;
		GF_ASSERT_MSG( (CLACT_U_ResManagerCheckID(resm, hs->id) == TRUE), "IDが重複しています")
		loadOneData(resm, obj, hs->file_path, hs->id, hs->ex[0], hs->ex[1], head->type, heap);
	}else{
		// アーカイブ用ヘッダ
		harc = (CLACT_U_RES_HEADER_SUBARC*)head->tbl + no;
		GF_ASSERT_MSG( (CLACT_U_ResManagerCheckID(resm, harc->id) == TRUE), "IDが重複しています")
		SetArcOneData(resm, obj, harc->arcFile, harc->dataIdx, harc->compFlag, harc->id, harc->ex[0], harc->ex[1], head->type, heap, ALLOC_TOP);
	}
	resm->tbl_now++;

	return obj;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	キャラクタデータの登録
 *
 *@param	resm			キャラクタ用に作成したリソースマネージャー
 *@param	path			ファイルパス
 *@param	id				管理ＩＤ
 *@param	vram			Ｖｒａｍタイプ(NNS_G2D_VRAM_TYPE_2DMAIN,NNS_G2D_VRAM_TYPE_2DSUB,NNS_G2D_VRAM_TYPE_2DMAX)
 *
 *@return	CLACT_U_RES_OBJ_PTR	リソースオブジェポインタ
 *
 *
 */
//-----------------------------------------------------------------------------
CLACT_U_RES_OBJ_PTR CLACT_U_ResManagerResAddChar(CLACT_U_RES_MANAGER_PTR resm, const char* path, int id, int vram, int heap)
{
	CLACT_U_RES_OBJ_PTR obj;

	GF_ASSERT(resm);
	GF_ASSERT_MSG((resm->type == CLACT_U_CHAR_RES), "リソースタイプが違います");
	GF_ASSERT_MSG( CLACT_U_ResManagerCheckID(resm, id) == TRUE, "IDが重複しています")
	
	obj = getCleanResObj(resm);
	GF_ASSERT_MSG(obj, "もう空きのテーブルがありません");
	loadOneData(resm, obj, path, id, vram, 0, CLACT_U_CHAR_RES, heap);
	resm->tbl_now++;

	return obj;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	パレットデータの登録
 *
 *@param	resm			パレット用に作成したリソースマネージャー
 *@param	path			ファイルパス
 *@param	id				管理ＩＤ
 *@param	vram			Ｖｒａｍタイプ(NNS_G2D_VRAM_TYPE_2DMAIN,NNS_G2D_VRAM_TYPE_2DSUB,NNS_G2D_VRAM_TYPE_2DMAX)
 *@param	pltt_num		必要なパレットナンバー
 *
 *@return	CLACT_U_RES_OBJ_PTR	リソースオブジェポインタ
 *
 *
 */
//-----------------------------------------------------------------------------
CLACT_U_RES_OBJ_PTR CLACT_U_ResManagerResAddPltt(CLACT_U_RES_MANAGER_PTR resm, const char* path, int id, int vram, int pltt_num, int heap)
{
	CLACT_U_RES_OBJ_PTR obj;

	GF_ASSERT(resm);
	GF_ASSERT_MSG(resm->type == CLACT_U_PLTT_RES , "リソースタイプが違います");
	GF_ASSERT_MSG( CLACT_U_ResManagerCheckID(resm, id) == TRUE, "IDが重複しています")
	
	obj = getCleanResObj(resm);
	GF_ASSERT_MSG(obj, "もう空きのテーブルがありません");
	loadOneData(resm, obj, path, id, vram, pltt_num, CLACT_U_PLTT_RES, heap);
	resm->tbl_now++;

	return obj;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	セル、セルアニメ、マルチセル、マルチセルアニメデータの登録
 *
 *@param	resm			パレット用に作成したリソースマネージャー
 *@param	path			ファイルパス
 *@param	id				管理ＩＤ
 *@param	type			リソースタイプ
 *@param	heap			使用ヒープ
 *
 *@return	CLACT_U_RES_OBJ_PTR	リソースオブジェポインタ
 *
 *
 */
//-----------------------------------------------------------------------------
CLACT_U_RES_OBJ_PTR CLACT_U_ResManagerResAddKindCell(CLACT_U_RES_MANAGER_PTR resm, const char* path, int id, int type, int heap)
{
	CLACT_U_RES_OBJ_PTR obj;

	GF_ASSERT(resm);
	GF_ASSERT_MSG( CLACT_U_ResManagerCheckID(resm, id) == TRUE , "IDが重複しています");
	GF_ASSERT(type == resm->type);
	
	obj = getCleanResObj(resm);
	GF_ASSERT_MSG(obj, "もう空きのテーブルがありません");
	loadOneData(resm, obj, path, id, 0, 0, type, heap);
	resm->tbl_now++;
	
	return obj;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	アーカイブされたキャラクタデータの登録
 *
 *@param	resm			キャラクタ用に作成したリソースマネージャー
 *@param	arcFile			アーカイブファイルID
 *@param	detaIdx			データインデックス
 *@param	compFlag		圧縮されているか
 *@param	id				管理ＩＤ
 *@param	vram			Ｖｒａｍタイプ(NNS_G2D_VRAM_TYPE_2DMAIN,NNS_G2D_VRAM_TYPE_2DSUB,NNS_G2D_VRAM_TYPE_2DMAX)
 *
 *@return	CLACT_U_RES_OBJ_PTR	リソースオブジェポインタ
 *
 *
 */
//-----------------------------------------------------------------------------
CLACT_U_RES_OBJ_PTR CLACT_U_ResManagerResAddArcChar(CLACT_U_RES_MANAGER_PTR resm, int arcFile, int dataIdx, BOOL compFlag, int id, int vram, int heap)
{
	CLACT_U_RES_OBJ_PTR obj;

	GF_ASSERT(resm);
	GF_ASSERT_MSG(resm->type == CLACT_U_CHAR_RES, "リソースタイプが違います");
	
	obj = getCleanResObj(resm);
	GF_ASSERT_MSG(obj, "もう空きのテーブルがありません");
	SetArcOneData(resm, obj, arcFile, dataIdx, compFlag, id, vram, 0, CLACT_U_CHAR_RES, heap, ALLOC_TOP);

	resm->tbl_now++;

	return obj;
}
CLACT_U_RES_OBJ_PTR CLACT_U_ResManagerResAddArcChar_AllocType(CLACT_U_RES_MANAGER_PTR resm, int arcFile, int dataIdx, BOOL compFlag, int id, int vram, int heap, ALLOC_TYPE alloc_type)
{
	CLACT_U_RES_OBJ_PTR obj;

	GF_ASSERT(resm);
	GF_ASSERT_MSG(resm->type == CLACT_U_CHAR_RES, "リソースタイプが違います");
	
	obj = getCleanResObj(resm);
	GF_ASSERT_MSG(obj, "もう空きのテーブルがありません");
	SetArcOneData(resm, obj, arcFile, dataIdx, compFlag, id, vram, 0, CLACT_U_CHAR_RES, heap, alloc_type);

	resm->tbl_now++;

	return obj;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	パレットデータの登録
 *
 *@param	resm			パレット用に作成したリソースマネージャー
 *@param	arcFile			アーカイブファイルID
 *@param	detaIdx			データインデックス
 *@param	compFlag		圧縮されているか
 *@param	id				管理ＩＤ
 *@param	vram			Ｖｒａｍタイプ(NNS_G2D_VRAM_TYPE_2DMAIN,NNS_G2D_VRAM_TYPE_2DSUB,NNS_G2D_VRAM_TYPE_2DMAX)
 *@param	pltt_num		必要なパレットの本数（１本＝１６色)
 *
 *@return	CLACT_U_RES_OBJ_PTR	リソースオブジェポインタ
 *
 *
 */
//-----------------------------------------------------------------------------
CLACT_U_RES_OBJ_PTR CLACT_U_ResManagerResAddArcPltt(CLACT_U_RES_MANAGER_PTR resm, int arcFile, int dataIdx, BOOL compFlag, int id, int vram, int pltt_num, int heap)
{
	CLACT_U_RES_OBJ_PTR obj;

	GF_ASSERT(resm);
	GF_ASSERT_MSG(resm->type == CLACT_U_PLTT_RES, "リソースタイプが違います");
	
	obj = getCleanResObj(resm);
	GF_ASSERT_MSG(obj, "もう空きのテーブルがありません");
	SetArcOneData(resm, obj, arcFile, dataIdx, compFlag, id, vram, pltt_num, CLACT_U_PLTT_RES, heap, ALLOC_TOP);

	resm->tbl_now++;
	return obj;
}
CLACT_U_RES_OBJ_PTR CLACT_U_ResManagerResAddArcPltt_AllocType(CLACT_U_RES_MANAGER_PTR resm, int arcFile, int dataIdx, BOOL compFlag, int id, int vram, int pltt_num, int heap, ALLOC_TYPE alloc_type)
{
	CLACT_U_RES_OBJ_PTR obj;

	GF_ASSERT(resm);
	GF_ASSERT_MSG(resm->type == CLACT_U_PLTT_RES, "リソースタイプが違います");
	
	obj = getCleanResObj(resm);
	GF_ASSERT_MSG(obj, "もう空きのテーブルがありません");
	SetArcOneData(resm, obj, arcFile, dataIdx, compFlag, id, vram, pltt_num, CLACT_U_PLTT_RES, heap, alloc_type);

	resm->tbl_now++;
	return obj;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	セル、セルアニメ、マルチセル、マルチセルアニメデータの登録
 *
 *@param	resm			パレット用に作成したリソースマネージャー
 *@param	arcFile			アーカイブファイルID
 *@param	detaIdx			データインデックス
 *@param	compFlag		圧縮されているか
 *@param	id				管理ＩＤ
 *@param	type			リソースタイプ(CLACT_U_CELL_RESかCLACT_U_CELLANM_RES)
 *@param	heap			使用ヒープ
 *
 *@return	CLACT_U_RES_OBJ_PTR	リソースオブジェポインタ
 *
 *
 */
//-----------------------------------------------------------------------------
CLACT_U_RES_OBJ_PTR CLACT_U_ResManagerResAddArcKindCell(CLACT_U_RES_MANAGER_PTR resm, int arcFile, int dataIdx, BOOL compFlag, int id, int type, int heap)
{
	CLACT_U_RES_OBJ_PTR obj;

	GF_ASSERT(resm);
	
	obj = getCleanResObj(resm);
	GF_ASSERT_MSG(obj, "もう空きのテーブルがありません");
	SetArcOneData(resm, obj, arcFile, dataIdx, compFlag, id, 0, 0, type, heap, ALLOC_TOP);

	resm->tbl_now++;
	return obj;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	アーカイブされたキャラクタデータのリソース変更
 *
 *@param	resm			キャラクタ用リソースマネージャポインタ
 *@param	resObj			変更するリソースオブジェ
 *@param	arcFile			アーカイブファイルID
 *@param	detaIdx			データインデックス
 *@param	compFlag		圧縮されているか
 *
 * @return none
 *
 *
 */
//-----------------------------------------------------------------------------
void CLACT_U_ResManagerResChgArcChar(CLACT_U_RES_MANAGER_PTR resm, CLACT_U_RES_OBJ_PTR resObj, int arcFile, int dataIdx, BOOL compFlag, int heap)
{
	int vram_type;	// Vram転送先
	int id;			// ID
	
	GF_ASSERT(resm);
	GF_ASSERT_MSG(resm->type == CLACT_U_CHAR_RES, "リソースタイプが違います");
	GF_ASSERT(resObj);
	GF_ASSERT_MSG(resObj->type == CLACT_U_CHAR_RES, "リソースタイプが違います");

	// 今までのデータ保存
	id = CLACT_U_ResManagerGetResObjID( resObj );
	vram_type =	CLACT_U_ResManagerGetResObjVramType( resObj );
	
	// 今までのデータ破棄
	CLACT_U_ResManagerResDelete( resm, resObj );

	// このデータテーブルに新しくデータ読み込み
	SetArcOneData(resm, resObj, arcFile, dataIdx, compFlag, id, vram_type, 0, CLACT_U_CHAR_RES, heap, ALLOC_TOP);
}


//----------------------------------------------------------------------------
/**
 *
 *@brief	パレットデータのリソースを変更
 *
 *@param	resm			パレット用リソースマネージャポインタ
 *@param	resObj			変更するリソースオブジェ
 *@param	arcFile			アーカイブファイルID
 *@param	detaIdx			データインデックス
 *@param	compFlag		圧縮されているか
 *@param	heap			使用するヒープ
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void CLACT_U_ResManagerResChgArcPltt(CLACT_U_RES_MANAGER_PTR resm, CLACT_U_RES_OBJ_PTR resObj, int arcFile, int dataIdx, BOOL compFlag, int heap)
{
	int vram_type;	// Vram転送先
	int pltt_num;	// パレット転送数
	int id;			// ID
	
	GF_ASSERT(resm);
	GF_ASSERT_MSG(resm->type == CLACT_U_PLTT_RES, "リソースタイプが違います");
	GF_ASSERT(resObj);
	GF_ASSERT_MSG(resObj->type == CLACT_U_PLTT_RES, "リソースタイプが違います");

	// 今までのデータ保存
	id = CLACT_U_ResManagerGetResObjID( resObj );
	vram_type =	CLACT_U_ResManagerGetResObjVramType( resObj );
	pltt_num = CLACT_U_ResManagerGetResObjPlttNum( resObj );
	
	// 今までのデータ破棄
	CLACT_U_ResManagerResDelete( resm, resObj );

	// このデータテーブルに新しくデータ読み込み
	SetArcOneData(resm, resObj, arcFile, dataIdx, compFlag, id, vram_type, pltt_num, CLACT_U_PLTT_RES, heap, ALLOC_TOP);
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	セル、セルアニメ、マルチセル、マルチセルアニメデータのリソースを変更
 *
 *@param	resm			変更するリソース用リソースマネージャポインタ
 *@param	resObj			変更するリソースオブジェ
 *@param	arcFile			アーカイブファイルID
 *@param	detaIdx			データインデックス
 *@param	compFlag		圧縮されているか
 *@param	type			リソースタイプ
 *@param	heap			使用するヒープ
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void CLACT_U_ResManagerResChgArcKindCell(CLACT_U_RES_MANAGER_PTR resm, CLACT_U_RES_OBJ_PTR resObj, int arcFile, int dataIdx, BOOL compFlag, int type, int heap)
{
	int id;			// ID
	
	GF_ASSERT(resm);
	GF_ASSERT(resObj);

	// 今までのデータ保存
	id = CLACT_U_ResManagerGetResObjID( resObj );
	
	// 今までのデータ破棄
	CLACT_U_ResManagerResDelete( resm, resObj );

	// このデータテーブルに新しくデータ読み込み
	SetArcOneData(resm, resObj, arcFile, dataIdx, compFlag, id, 0, 0, type, heap, ALLOC_TOP);
}

//----------------------------------------------------------------------------
/**
 * ■アーカイブハンドル方式
 *
 *@brief	アーカイブされたキャラクタデータの登録
 *
 *@param	resm			キャラクタ用に作成したリソースマネージャー
 *@param	arcHandle		アーカイブファイルハンドル
 *@param	detaIdx			データインデックス
 *@param	compFlag		圧縮されているか	(TRUE 圧縮  　　FALSE 非圧縮)
 *@param	id				管理ＩＤ		（重複しないようにユーザーが設定）
 *@param	vram			Ｖｒａｍタイプ
 *@param	heap			使用ヒープ
 *
 *@return	CLACT_U_RES_OBJ_PTR	リソースオブジェポインタ
 *
 * Vramタイプ
	mainに登録：NNS_G2D_VRAM_TYPE_2DMAIN
	subに登録 ：NNS_G2D_VRAM_TYPE_2DSUB
	両方に登録：NNS_G2D_VRAM_TYPE_2DMAX
 *
 */
//-----------------------------------------------------------------------------
CLACT_U_RES_OBJ_PTR CLACT_U_ResManagerResAddArcChar_ArcHandle(CLACT_U_RES_MANAGER_PTR resm, ARCHANDLE* arcHandle, int dataIdx, BOOL compFlag, int id, int vram, int heap)
{
	CLACT_U_RES_OBJ_PTR obj;

	GF_ASSERT(resm);
	GF_ASSERT_MSG(resm->type == CLACT_U_CHAR_RES, "リソースタイプが違います");
	
	obj = getCleanResObj(resm);
	GF_ASSERT_MSG(obj, "もう空きのテーブルがありません");
	
	SetArcOneData_ArcHandle(resm, obj, arcHandle, dataIdx, compFlag, id, vram, 0, CLACT_U_CHAR_RES, heap, ALLOC_TOP);

	resm->tbl_now++;

	return obj;
}
CLACT_U_RES_OBJ_PTR CLACT_U_ResManagerResAddArcChar_ArcHandle_AllocType(CLACT_U_RES_MANAGER_PTR resm, ARCHANDLE* arcHandle, int dataIdx, BOOL compFlag, int id, int vram, int heap, ALLOC_TYPE alloc_type)
{
	CLACT_U_RES_OBJ_PTR obj;

	GF_ASSERT(resm);
	GF_ASSERT_MSG(resm->type == CLACT_U_CHAR_RES, "リソースタイプが違います");
	
	obj = getCleanResObj(resm);
	GF_ASSERT_MSG(obj, "もう空きのテーブルがありません");
	
	SetArcOneData_ArcHandle(resm, obj, arcHandle, dataIdx, compFlag, id, vram, 0, CLACT_U_CHAR_RES, heap, alloc_type);

	resm->tbl_now++;

	return obj;
}

//----------------------------------------------------------------------------
/**
 * ■アーカイブハンドル方式
 *
 *@brief	パレットデータの登録
 *
 *@param	resm			パレット用に作成したリソースマネージャー
 *@param	arcHandle		アーカイブファイルハンドル
 *@param	detaIdx			データインデックス
 *@param	compFlag		圧縮されているか	(TRUE 圧縮  　　FALSE 非圧縮)
 *@param	id				管理ＩＤ		（重複しないようにユーザーが設定）
 *@param	vram			Ｖｒａｍタイプ
 *@param	pltt_num		パレット読み込み本数
 *@param	heap			使用ヒープ
 *
 *@return	CLACT_U_RES_OBJ_PTR	リソースオブジェポインタ
 *
 * Vramタイプ
	mainに登録：NNS_G2D_VRAM_TYPE_2DMAIN
	subに登録 ：NNS_G2D_VRAM_TYPE_2DSUB
	両方に登録：NNS_G2D_VRAM_TYPE_2DMAX
 *
 */
//-----------------------------------------------------------------------------
CLACT_U_RES_OBJ_PTR CLACT_U_ResManagerResAddArcPltt_ArcHandle(CLACT_U_RES_MANAGER_PTR resm, ARCHANDLE* arcHandle, int dataIdx, BOOL compFlag, int id, int vram, int pltt_num, int heap)
{
	CLACT_U_RES_OBJ_PTR obj;

	GF_ASSERT(resm);
	GF_ASSERT_MSG(resm->type == CLACT_U_PLTT_RES, "リソースタイプが違います");
	
	obj = getCleanResObj(resm);
	GF_ASSERT_MSG(obj, "もう空きのテーブルがありません");
	SetArcOneData_ArcHandle(resm, obj, arcHandle, dataIdx, compFlag, id, vram, pltt_num, CLACT_U_PLTT_RES, heap, ALLOC_TOP);

	resm->tbl_now++;
	return obj;
}
CLACT_U_RES_OBJ_PTR CLACT_U_ResManagerResAddArcPltt_ArcHandle_AllocType(CLACT_U_RES_MANAGER_PTR resm, ARCHANDLE* arcHandle, int dataIdx, BOOL compFlag, int id, int vram, int pltt_num, int heap, ALLOC_TYPE alloc_type )
{
	CLACT_U_RES_OBJ_PTR obj;

	GF_ASSERT(resm);
	GF_ASSERT_MSG(resm->type == CLACT_U_PLTT_RES, "リソースタイプが違います");
	
	obj = getCleanResObj(resm);
	GF_ASSERT_MSG(obj, "もう空きのテーブルがありません");
	SetArcOneData_ArcHandle(resm, obj, arcHandle, dataIdx, compFlag, id, vram, pltt_num, CLACT_U_PLTT_RES, heap, alloc_type);

	resm->tbl_now++;
	return obj;
}

//----------------------------------------------------------------------------
/**
 * ■アーカイブハンドル方式
 *
 *@brief	セル、セルアニメ、マルチセル、マルチセルアニメデータの登録
 *
 *@param	resm			パレット用に作成したリソースマネージャー
 *@param	arcHandle		アーカイブファイルハンドル
 *@param	detaIdx			データインデックス
 *@param	compFlag		圧縮されているか	(TRUE 圧縮  　　FALSE 非圧縮)
 *@param	id				管理ＩＤ		（重複しないようにユーザーが設定）
 *@param	type			リソースタイプ
 *@param	heap			使用ヒープ
 *
 *@return	CLACT_U_RES_OBJ_PTR	リソースオブジェポインタ
 *
 * リソースタイプ
	enum{
		CLACT_U_CHAR_RES,		// キャラクタリソースを管理
		CLACT_U_PLTT_RES,		// パレットリソースを管理
		CLACT_U_CELL_RES,		// セルリソースを管理
		CLACT_U_CELLANM_RES,	// セルアニメリソースを管理
		CLACT_U_MULTI_RES,		// マルチセルリソースを管理
		CLACT_U_MULTIANM_RES,	// マルチセルアニメリソースを管理
		CLACT_U_RES_MAX			// 最大
	};
 *
 */
//-----------------------------------------------------------------------------
CLACT_U_RES_OBJ_PTR CLACT_U_ResManagerResAddArcKindCell_ArcHandle(CLACT_U_RES_MANAGER_PTR resm, ARCHANDLE* arcHandle, int dataIdx, BOOL compFlag, int id, int type, int heap)
{
	CLACT_U_RES_OBJ_PTR obj;

	GF_ASSERT(resm);
	
	obj = getCleanResObj(resm);
	GF_ASSERT_MSG(obj, "もう空きのテーブルがありません");
	SetArcOneData_ArcHandle(resm, obj, arcHandle, dataIdx, compFlag, id, 0, 0, type, heap, ALLOC_TOP);

	resm->tbl_now++;
	return obj;
}

//----------------------------------------------------------------------------
/**
 * ■アーカイブハンドル方式
 *
 *@brief	アーカイブされたキャラクタデータのリソース変更
 *
 *@param	resm			キャラクタ用リソースマネージャポインタ
 *@param	resObj			変更するリソースオブジェ
 *@param	arcHandle		アーカイブファイルハンドル
 *@param	detaIdx			データインデックス
 *@param	compFlag		圧縮されているか	(TRUE 圧縮  　　FALSE 非圧縮)
 *@param	heap			使用ヒープ
 *
 * @return none
 *
 *
 */
//-----------------------------------------------------------------------------
void CLACT_U_ResManagerResChgArcChar_ArcHandle(CLACT_U_RES_MANAGER_PTR resm, CLACT_U_RES_OBJ_PTR resObj, ARCHANDLE* arcHandle, int dataIdx, BOOL compFlag, int heap)
{
	int vram_type;	// Vram転送先
	int id;			// ID
	
	GF_ASSERT(resm);
	GF_ASSERT_MSG(resm->type == CLACT_U_CHAR_RES, "リソースタイプが違います");
	GF_ASSERT(resObj);
	GF_ASSERT_MSG(resObj->type == CLACT_U_CHAR_RES, "リソースタイプが違います");

	// 今までのデータ保存
	id = CLACT_U_ResManagerGetResObjID( resObj );
	vram_type =	CLACT_U_ResManagerGetResObjVramType( resObj );
	
	// 今までのデータ破棄
	CLACT_U_ResManagerResDelete( resm, resObj );

	// このデータテーブルに新しくデータ読み込み
	SetArcOneData_ArcHandle(resm, resObj, arcHandle, dataIdx, compFlag, id, vram_type, 0, CLACT_U_CHAR_RES, heap, ALLOC_TOP);
}


//----------------------------------------------------------------------------
/**
 * ■アーカイブハンドル方式
 *
 *@brief	パレットデータのリソースを変更
 *
 *@param	resm			パレット用リソースマネージャポインタ
 *@param	resObj			変更するリソースオブジェ
 *@param	arcHandle		アーカイブファイルハンドル
 *@param	detaIdx			データインデックス
 *@param	compFlag		圧縮されているか	(TRUE 圧縮  　　FALSE 非圧縮)
 *@param	heap			使用するヒープ
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void CLACT_U_ResManagerResChgArcPltt_ArcHandle(CLACT_U_RES_MANAGER_PTR resm, CLACT_U_RES_OBJ_PTR resObj, ARCHANDLE* arcHandle, int dataIdx, BOOL compFlag, int heap)
{
	int vram_type;	// Vram転送先
	int pltt_num;	// パレット転送数
	int id;			// ID
	
	GF_ASSERT(resm);
	GF_ASSERT_MSG(resm->type == CLACT_U_PLTT_RES, "リソースタイプが違います");
	GF_ASSERT(resObj);
	GF_ASSERT_MSG(resObj->type == CLACT_U_PLTT_RES, "リソースタイプが違います");

	// 今までのデータ保存
	id = CLACT_U_ResManagerGetResObjID( resObj );
	vram_type =	CLACT_U_ResManagerGetResObjVramType( resObj );
	pltt_num = CLACT_U_ResManagerGetResObjPlttNum( resObj );
	
	// 今までのデータ破棄
	CLACT_U_ResManagerResDelete( resm, resObj );

	// このデータテーブルに新しくデータ読み込み
	SetArcOneData_ArcHandle(resm, resObj, arcHandle, dataIdx, compFlag, id, vram_type, pltt_num, CLACT_U_PLTT_RES, heap, ALLOC_TOP);
}

//----------------------------------------------------------------------------
/**
 * ■アーカイブハンドル方式
 *
 *@brief	セル、セルアニメ、マルチセル、マルチセルアニメデータのリソースを変更
 *
 *@param	resm			変更するリソース用リソースマネージャポインタ
 *@param	resObj			変更するリソースオブジェ
 *@param	arcHandle		アーカイブファイルハンドル
 *@param	detaIdx			データインデックス
 *@param	compFlag		圧縮されているか	(TRUE 圧縮  　　FALSE 非圧縮)
 *@param	type			リソースタイプ
 *@param	heap			使用するヒープ
 *
 *@return	none
 *
 * リソースタイプ
	enum{
		CLACT_U_CHAR_RES,		// キャラクタリソースを管理
		CLACT_U_PLTT_RES,		// パレットリソースを管理
		CLACT_U_CELL_RES,		// セルリソースを管理
		CLACT_U_CELLANM_RES,	// セルアニメリソースを管理
		CLACT_U_MULTI_RES,		// マルチセルリソースを管理
		CLACT_U_MULTIANM_RES,	// マルチセルアニメリソースを管理
		CLACT_U_RES_MAX			// 最大
	};
 *
 */
//-----------------------------------------------------------------------------
void CLACT_U_ResManagerResChgArcKindCell_ArcHandle(CLACT_U_RES_MANAGER_PTR resm, CLACT_U_RES_OBJ_PTR resObj, ARCHANDLE* arcHandle, int dataIdx, BOOL compFlag, int type, int heap)
{
	int id;			// ID
	
	GF_ASSERT(resm);
	GF_ASSERT(resObj);

	// 今までのデータ保存
	id = CLACT_U_ResManagerGetResObjID( resObj );
	
	// 今までのデータ破棄
	CLACT_U_ResManagerResDelete( resm, resObj );

	// このデータテーブルに新しくデータ読み込み
	SetArcOneData_ArcHandle(resm, resObj, arcHandle, dataIdx, compFlag, id, 0, 0, type, heap, ALLOC_TOP);
}


//----------------------------------------------------------------------------
/**
 *
 *@brief	リソースデータをヘッダーから読み込む
 *
 *@param	resm		リソースマネージャーポインタ
 *@param	head		ヘッダー
 *@param	p_ro_tbl	メモリ確保済みリソースオブジェテーブル
 *@param	heap		使用するヒープ
 *
 *@return	int			読み込み数
 *
 *
 */
//-----------------------------------------------------------------------------
int CLACT_U_ResManagerResAddsHd(CLACT_U_RES_MANAGER_PTR resm, const CLACT_U_RES_HEADER_PTR head, CLACT_U_RES_OBJ_TBL* p_ro_tbl, int heap )
{
	GF_ASSERT(resm);
	GF_ASSERT(head);

	CLACT_U_ResManagerResAddsHdEx(resm, head, 0, head->tbl_num, p_ro_tbl, heap);
	return head->tbl_num;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	リソースデータをヘッダーから読み込む(読み込む数を指定)
 *
 *@param	resm		リソースマネージャーポインタ
 *@param	head		ヘッダー
 *@param	start		読み込み開始テーブルナンバー
 *@param	num			読み込み数
 *@param	p_ro_tbl	メモリ確保済みリソースオブジェテーブル
 *@param	heap		使用するヒープ
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void CLACT_U_ResManagerResAddsHdEx(CLACT_U_RES_MANAGER_PTR resm, const CLACT_U_RES_HEADER_PTR head, int start, int num, CLACT_U_RES_OBJ_TBL* p_ro_tbl,int heap)
{
	int i;
	CLACT_U_RES_OBJ_PTR obj;

	
	for(i=start;i<start+num;i++){
		obj = CLACT_U_ResManagerResAddHd(resm, head, i, heap);

		// 読み込んだリソースを格納
		if(p_ro_tbl != NULL){
			if(p_ro_tbl->tbl_num > p_ro_tbl->tbl_now){	// 登録可能なら登録
				p_ro_tbl->tbl[ p_ro_tbl->tbl_now ] = obj;// 登録したオブジェを設定
				p_ro_tbl->tbl_now++;	// 登録数カウント
			}
		}
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	リソースオブジェテーブル作成
 *
 *@param	num		テーブル数
 *@param	heap	使用ヒープ
 *
 *@return	CLACT_U_RES_OBJ_TBL* 作成データ
 *
 *
 */
//-----------------------------------------------------------------------------
CLACT_U_RES_OBJ_TBL* CLACT_U_ResManagerResObjTblMake(int num, int heap)
{
	CLACT_U_RES_OBJ_TBL* resTbl;

	// リソースオブジェ格納領域を作成
	resTbl = sys_AllocMemory(heap, sizeof(CLACT_U_RES_OBJ_TBL));
	resTbl->tbl = sys_AllocMemory(heap, sizeof(CLACT_U_RES_OBJ_PTR)*num);
	resTbl->tbl_num = num;
	resTbl->tbl_now = 0;

	return resTbl;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	リソースオブジェテーブル破棄
 *
 *@param	tbl		破棄テーブル
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void CLACT_U_ResManagerResObjTblDelete(CLACT_U_RES_OBJ_TBL* tbl)
{
	sys_FreeMemoryEz(tbl->tbl);
	sys_FreeMemoryEz(tbl);
	tbl = NULL;
}
//----------------------------------------------------------------------------
/**
 *
 *@brief	残り登録可能数取得
 *
 *@param	resm		リソースマネージャーポインタ
 *
 *@return	int		残り登録可能数
 *
 *
 */
//-----------------------------------------------------------------------------
int CLACT_U_ResManagerRest(CLACT_U_RES_MANAGER_PTR resm)
{
	GF_ASSERT(resm);
	return resm->tbl_num - resm->tbl_now;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	IDのデータがあるかチェック
 *
 *@param	resm	リソースマネージャ
 *@param	id		チェックするID
 *
 *@retval	TRUE	IDのデータが無い
 *@retval	FALSE	IDのデータがある
 *
 *
 */
//-----------------------------------------------------------------------------
BOOL CLACT_U_ResManagerCheckID(CONST_CLACT_U_RES_MANAGER_PTR resm, int id)
{
	GF_ASSERT(resm);
	
	return RESM_CheckID(resm->res_manager, id);
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	リソースオブジェ内の読み込んできたデータのみ破棄
 *			IDやリソースタイプなどの情報は保持したまま
 *
 *	@param	res_obj		リソースオブジェ
 *
 *	@return	none
 *
 * この関数を呼ぶとVramへのリソースの転送などが行えなくなります。
 * 
 *
 */
//-----------------------------------------------------------------------------
void CLACT_U_ResManagerResOnlyDelete( CLACT_U_RES_OBJ_PTR res_obj )
{
	GF_ASSERT( res_obj );
	
	// 拡張データ破棄
	delExData(res_obj);

	// リソースの生データ破棄
	RESM_SetRes(res_obj->res_obj, NULL);
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	リソース破棄
 *
 *@param	resm		セルアクターユーティリティリソースマネージャーポインタ
 *@param	res_obj		リソースオブジェ
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void CLACT_U_ResManagerResDelete(CLACT_U_RES_MANAGER_PTR resm, CLACT_U_RES_OBJ_PTR res_obj)
{
	GF_ASSERT(resm);
	GF_ASSERT(resm->resObj);

	// 拡張データ破棄
	delExData(res_obj);

	// リソースを破棄し、データテーブルを空にする
	RESM_DeleteRes(resm->res_manager, res_obj->res_obj);
	res_obj->res_obj = NULL;
	
	resm->tbl_now--;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	リソース全破棄
 *
 *@param	resm		セルアクターユーティリティリソースマネージャーポインタ
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void CLACT_U_ResManagerResDeleteAll(CLACT_U_RES_MANAGER_PTR resm)
{
	int i;		// ループ用

	for(i=0;i<resm->tbl_num;i++){
		if(resm->resObj[i].res_obj != NULL){
			CLACT_U_ResManagerResDelete(resm, resm->resObj + i);
		}
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	IDのリソースを取得
 *
 *@param	id		取得するリソースオブジェポインタに設定されている管理ＩＤ
 *	
 *@return	CLACT_U_RES_OBJ_PTR		リソースオブジェポインタ
 *
 *
 */
//-----------------------------------------------------------------------------
CLACT_U_RES_OBJ_PTR CLACT_U_ResManagerGetIDResObjPtr(CONST_CLACT_U_RES_MANAGER_PTR resm, int id)
{
	int i;		// ループ用
	int ret_id;	// id

	GF_ASSERT(resm);

	for(i=0;i<resm->tbl_num;i++){
		if(resm->resObj[i].res_obj){
			ret_id = RESM_GetID(resm->resObj[i].res_obj);

			if(ret_id == id){
				return (resm->resObj + i);
			}
		}

	}

	return NULL;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	リソースオブジェからＩＤを取得
 *
 *@param	resObj	リソースオブジェ
 *	
 *@return	int		管理ＩＤ
 *
 *
 */
//-----------------------------------------------------------------------------
int CLACT_U_ResManagerGetResObjID(CONST_CLACT_U_RES_OBJ_PTR resObj)
{
	GF_ASSERT(resObj);
	return RESM_GetID(resObj->res_obj);
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	リソースオブジェからＩＤを設定
 *
 *@param	resm	変更するオブジェの登録されているリソースマネージャ
 *@param	resObj	リソースオブジェ
 *@param	id		設定するID
 *	
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void CLACT_U_ResManagerSetResObjID(CLACT_U_RES_MANAGER_PTR resm, CLACT_U_RES_OBJ_PTR resObj, int id)
{
	GF_ASSERT(resObj);

	RESM_SetID(resm->res_manager, resObj->res_obj, id);
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	リソースオブジェのリソースを取得
 *
 *@param	resObj	リソースオブジェ
 *	
 *@return	void*	リソースポインタ
 *
 * アンパック禁止です。
 * アンパック済みファイルを取得する関数を用意しているため、
 * そちらを使用してください。
 *
 */
//-----------------------------------------------------------------------------
void* CLACT_U_ResManagerGetResObjRes(CONST_CLACT_U_RES_OBJ_PTR resObj)
{
	void* buff;
	
	GF_ASSERT(resObj);
	buff = RESM_GetRes(resObj->res_obj);

	// CLACT_U_ResManagerResOnlyDeleteでデータを破棄した為、
	// データがありません。
	GF_ASSERT( buff );
	
	return buff;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	キャラクタデータを取得	リソースデータをアンパックしてから取得
 *
 *@param	resObj	キャラクタリソースオブジェ
 *
 *@return	キャラクタリソースデータ
 *
 *
 */
//-----------------------------------------------------------------------------
NNSG2dCharacterData* CLACT_U_ResManagerGetResObjResChar(CONST_CLACT_U_RES_OBJ_PTR resObj)
{
	CLACT_U_RES_EX_CHAR* data;
	
	GF_ASSERT(resObj->type == CLACT_U_CHAR_RES);

	data = (CLACT_U_RES_EX_CHAR*)getExData( resObj );

	return data->pCharData;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	パレットデータを取得	リソースデータをアンパックしてから取得
 *
 *@param	resObj	パレットリソースオブジェ
 *
 *@return	パレットリソースデータ
 *
 *
 */
//-----------------------------------------------------------------------------
NNSG2dPaletteData* CLACT_U_ResManagerGetResObjResPltt(CONST_CLACT_U_RES_OBJ_PTR resObj)
{
	CLACT_U_RES_EX_PLTT* data;
	
	GF_ASSERT(resObj->type == CLACT_U_PLTT_RES);

	data = (CLACT_U_RES_EX_PLTT*)getExData( resObj ); 

	return data->pPlttData;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	セルデータを取得	リソースデータをアンパックしてから取得
 *
 *@param	resObj	セルリソースオブジェ
 *
 *@return	セルリソースデータ
 *
 *
 */
//-----------------------------------------------------------------------------
NNSG2dCellDataBank* CLACT_U_ResManagerGetResObjResCell(CONST_CLACT_U_RES_OBJ_PTR resObj)
{
	CLACT_U_RES_EX_CELL* data;
	
	GF_ASSERT(resObj->type == CLACT_U_CELL_RES);

	data = (CLACT_U_RES_EX_CELL*)getExData( resObj );

	return data->pCellData;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	セルアニメデータを取得	リソースデータをアンパックしてから取得
 *
 *@param	resObj	セルアニメリソースオブジェ
 *
 *@return	セルアニメリソースデータ
 *
 *
 */
//-----------------------------------------------------------------------------
NNSG2dCellAnimBankData* CLACT_U_ResManagerGetResObjResCellAnm(CONST_CLACT_U_RES_OBJ_PTR resObj)
{
	CLACT_U_RES_EX_CELLANM* data;
	
	GF_ASSERT(resObj->type == CLACT_U_CELLANM_RES);

	data = (CLACT_U_RES_EX_CELLANM*)getExData( resObj );

	return data->pCellANMData;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	マルチセルデータを取得	リソースデータをアンパックしてから取得
 *
 *@param	resObj	マルチセルリソースオブジェ
 *
 *@return	マルチセルリソースデータ
 *
 *
 */
//-----------------------------------------------------------------------------
NNSG2dMultiCellDataBank* CLACT_U_ResManagerGetResObjResMultiCell(CONST_CLACT_U_RES_OBJ_PTR resObj)
{
	CLACT_U_RES_EX_MULTI* data;
	
	GF_ASSERT(resObj->type == CLACT_U_MULTI_RES);

	data = (CLACT_U_RES_EX_MULTI*)getExData( resObj );

	return data->pMultiData;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	マルチセルアニメデータを取得	リソースデータをアンパックしてから取得
 *
 *@param	resObj	マルチセルアニメリソースオブジェ
 *
 *@return	マルチセルアニメリソースデータ
 *
 *
 */
//-----------------------------------------------------------------------------
NNSG2dMultiCellAnimBankData* CLACT_U_ResManagerGetResObjResMultiCellAnim(CONST_CLACT_U_RES_OBJ_PTR resObj)
{
	CLACT_U_RES_EX_MULTIANM* data;
	
	GF_ASSERT(resObj->type == CLACT_U_MULTIANM_RES);

	data = (CLACT_U_RES_EX_MULTIANM*)getExData( resObj );

	return data->pMultiANMData;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	リソースオブジェに設定されているリソースのタイプを取得
 *
 *@param	resObj	リソースオブジェ
 *	
 *@return	int		リソースタイプ
 *
 *
 */
//-----------------------------------------------------------------------------
int CLACT_U_ResManagerGetResObjResType(CONST_CLACT_U_RES_OBJ_PTR resObj)
{
	GF_ASSERT(resObj);
	return resObj->type;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	リソースオブジェに設定されているVramタイプを取得
 *
 *@param	resObj	リソースオブジェ
 *	
 *@return	int		Vramタイプ（キャラクタ。パレット時のみ）
 *
 *
 */
//-----------------------------------------------------------------------------
int CLACT_U_ResManagerGetResObjVramType(CONST_CLACT_U_RES_OBJ_PTR resObj)
{
	GF_ASSERT(resObj);

	if(resObj->type == CLACT_U_CHAR_RES){
		CLACT_U_RES_EX_CHAR* chardata;
		chardata = getExData( resObj );
		return chardata->vram_type;
	}
	
	if(resObj->type == CLACT_U_PLTT_RES){
		CLACT_U_RES_EX_PLTT* plttdata;
		plttdata = getExData( resObj );
		return plttdata->vram_type;
	}
	
	return 0;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	リソースオブジェに設定されているパレット読み込み数を取得
 *
 *@param	resObj	リソースオブジェ
 *	
 *@return	int		Vramタイプ（パレット時のみ）
 *
 *
 */
//-----------------------------------------------------------------------------
int CLACT_U_ResManagerGetResObjPlttNum(CONST_CLACT_U_RES_OBJ_PTR resObj)
{
	GF_ASSERT(resObj);

	if(resObj->type == CLACT_U_PLTT_RES){
		CLACT_U_RES_EX_PLTT* plttdata;
		plttdata = getExData( resObj );
		return plttdata->pltt_num;
	}
	
	return 0;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	リソースオブジェに設定されているvramタイプを取得
 *
 *@param	resobj	リソースオブジェ
 *@param	vram	vramタイプ	メイン:1	サブ:2
 *	
 *@return	int		vramタイプ（キャラクタ。パレット時のみ）
 *
 *
 */
//-----------------------------------------------------------------------------
void CLACT_U_ResManagerSetResObjVramType(CLACT_U_RES_OBJ_PTR resObj, int vram)
{
	GF_ASSERT(resObj);

	if(resObj->type == CLACT_U_CHAR_RES){
		CLACT_U_RES_EX_CHAR* chardata;
		chardata = getExData( resObj );
		chardata->vram_type = vram;
	}
	
	if(resObj->type == CLACT_U_PLTT_RES){
		CLACT_U_RES_EX_PLTT* plttdata;
		plttdata = getExData( resObj );
		plttdata->vram_type = vram;
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	リソースオブジェに設定されているパレット読み込み数を取得
 *
 *@param	resObj	リソースオブジェ
 *@param	pltt	パレット読み込み数
 *	
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void CLACT_U_ResManagerSetResObjPlttNum(CLACT_U_RES_OBJ_PTR resObj, int pltt)
{
	GF_ASSERT(resObj);

	if(resObj->type == CLACT_U_PLTT_RES){
		CLACT_U_RES_EX_PLTT* plttdata;
		plttdata = getExData( resObj );
		plttdata->pltt_num = pltt;
	}
}






//----------------------------------------------------------------------------
/**
 *
 *@brief	ヘッダーサイズを取得
 *
 *@param	none
 *
 *@return	int		サイズ
 *
 *
 */
//-----------------------------------------------------------------------------
int CLACT_U_ResManagerGetHeaderSize(void)
{
	return sizeof(CLACT_U_RES_HEADER);
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	リソースヘッダーを配列で確保したときの各要素数のデータを
 *			取得する関数
 *
 *@param	head	ヘッダーデータ（配列）
 *@param	no		要素数
 *
 *@return	CLACT_U_RES_HEADER_PTR
 *
 * noが配列の要素数より大きい時、不当なポインタを返してしまいます。
 *
 */
//-----------------------------------------------------------------------------
CLACT_U_RES_HEADER_PTR CLACT_U_ResManagerGetHeaderNoData(CLACT_U_RES_HEADER_PTR head, int no)
{
	return (head + no);
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	セルアクターユーティリティリソースマネージャヘッダー読み込み
 *
 *@param	path		ヘッダーファイルパス
 *@param	head		ヘッダー格納先
 *@param	heap		使用するヒープ
 *
 *@return	none
 *
 */
//-----------------------------------------------------------------------------
void CLACT_U_ResManagerHeaderLoad(const char* path, CLACT_U_RES_HEADER_PTR head,int heap)
{
	char* tmp;				// 解放用
	char* buff;				// ファイルデータ
	int	i;					// ループ用

	GF_ASSERT(head);		// ヘッダー領域を確保してください


	// ファイル読み込み
	tmp = sys_LoadFile(heap, path);
	GF_ASSERT_MSG(tmp, "ヘッダー読み込み失敗");

	// ワークバッファ
	buff = makeCopyStr(tmp, heap);
	
	// リソースタイプ取得
	head->type = getHeaderType(buff);
	delCopyStr(buff);			// いったん破棄
	buff = makeCopyStr(tmp, heap);	// 再コピー

	// アーカイブタイプ取得
	head->arc_flag = getHeaderArc(buff);
	delCopyStr(buff);			// いったん破棄
	buff = makeCopyStr(tmp, heap);	// 再コピー

	// データ数の取得
	head->tbl_num = getHeaderNum(buff, head->type, head->arc_flag);
	delCopyStr(buff);			// いったん破棄
	buff = makeCopyStr(tmp, heap);	// 再コピー
	
	// データ分の流域の確保
	if(head->tbl_num > 0){
		if(head->arc_flag == 0){
			head->tbl = sys_AllocMemory(heap, sizeof(CLACT_U_RES_HEADER_SUB)*head->tbl_num);
		}else{
			head->tbl = sys_AllocMemory(heap, sizeof(CLACT_U_RES_HEADER_SUBARC)*head->tbl_num);
		}
	}else{
		head->tbl = NULL;
	}
	
	// データを格納
	if(head->tbl){
		loadHeaderData(buff, head->type, head->tbl, head->tbl_num, head->arc_flag);	
	}
	
	// 読み込みファイルを破棄
	delCopyStr(buff);
	sys_FreeMemoryEz(tmp);
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	セルアクターユーティリティリソースマネージャバイナリヘッダー読み込み
 *
 *@param	cp_bindata		バイナリデータ
 *@param	head			ヘッダー格納先
 *@param	heap			使用するヒープ
 *
 *@return	none
 *
 * Binaryデータ書式		全データ4byte区切り
 *	リソースタイプ
 *	アーカイブファイルidx
 *	データidx
 *	圧縮フラグ
 *	管理ID
 *	＊▲Vramタイプ				いらないときはダミーデータ
 *	  ▲パレット読み込み本数	いらないときはダミーデータ
 *
 * ＊キャラクタリソースの時
 * ▲パレットリソースの時
 *	
 */
//-----------------------------------------------------------------------------
void CLACT_U_ResManagerHeaderLoadBinary(const void* cp_bindata, CLACT_U_RES_HEADER_PTR head,int heap)
{
	int	i;					// ループ用
	const int* view;		// バイナリデータ内参照用

	GF_ASSERT(head);		// ヘッダー領域を確保してください

	// 参照できるようにint*型で見る
	view = cp_bindata;

	// リソースタイプ取得
	head->type = view[0];		// 先頭4byte リソースタイプ

	head->arc_flag = 1;			// アーカイブファイル固定

	// データ数の取得
	head->tbl_num = getHeaderNumBinary( (const CLACT_U_RES_HEADER_SUBARC*)(view + 1) );
	
	// データ分の領域の確保
	if(head->tbl_num > 0){
		head->tbl = sys_AllocMemory(heap, sizeof(CLACT_U_RES_HEADER_SUBARC)*head->tbl_num);
	}else{
		head->tbl = NULL;
	}
	
	// データを格納
	if(head->tbl){
		memcpy( head->tbl, view + 1, sizeof(CLACT_U_RES_HEADER_SUBARC)*head->tbl_num );
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	リソースマネージャヘッダー破棄
 *
 *@param	head		ヘッダーポインタ
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void CLACT_U_ResManagerHeaderFree(CLACT_U_RES_HEADER_PTR head)
{
	if(head->tbl){
		sys_FreeMemoryEz(head->tbl);
	}
	head->tbl = NULL;
	head->tbl_num = 0;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	リソースマネージャーヘッダーに読み込まれているデータ数取得
 *
 *@param	head		リソースヘッダ
 *
 *@return	int		読み込まれているデータ数
 *
 *
 */
//-----------------------------------------------------------------------------
int CLACT_U_ResManagerHeaderSetDataNum(CONST_CLACT_U_RES_HEADER_PTR head)
{
	GF_ASSERT(head);
	return head->tbl_num;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	リソースマネージャーヘッダーに読み込まれているデータのリソースタイプ
 *
 *@param	head		リソースヘッダ
 *
 *@return	int		リソースタイプ
 *
 *
 */
//-----------------------------------------------------------------------------
int CLACT_U_ResManagerHeaderSetDataResType(CONST_CLACT_U_RES_HEADER_PTR head)
{
	GF_ASSERT(head);
	return head->type;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	リソースマネージャーヘッダーに読み込まれているデータはアーカイブされているか
 *
 *@param	head		リソースヘッダ
 *
 *@return	int			0：されてない	1：されてる
 *
 *
 */
//-----------------------------------------------------------------------------
int CLACT_U_ResManagerHeaderSetDataArc(CONST_CLACT_U_RES_HEADER_PTR head)
{
	GF_ASSERT(head);
	return head->arc_flag;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	ヘッダに登録されているデータのIDを変更する
 *
 *	@param	head		リソースヘッダー
 *	@param	no			リソースヘッダー内に登録されているデータナンバー
 *	@param	param		設定するID
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void CLACT_U_ResManagerHeaderDataIDSet( CLACT_U_RES_HEADER_PTR head, int no, int param )
{
	GF_ASSERT( head );
	GF_ASSERT( head->tbl_num > no );
	
	if(head->arc_flag == 0){
		CLACT_U_RES_HEADER_SUB* data = head->tbl;

		data[ no ].id = param;
	}else{
		CLACT_U_RES_HEADER_SUBARC* data = head->tbl;

		data[ no ].id = param;
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	ヘッダに登録されているデータのIDを取得する
 *
 *	@param	head		リソースヘッダー
 *	@param	no			リソースヘッダー内に登録されているデータナンバー
 *
 *	@return	int		管理ID
 *
 *
 */
//-----------------------------------------------------------------------------
int CLACT_U_ResManagerHeaderDataIDGet( CONST_CLACT_U_RES_HEADER_PTR head, int no )
{
	int ret_id;		// 戻り値用
	
	GF_ASSERT( head );
	GF_ASSERT( head->tbl_num > no );
	
	if(head->arc_flag == 0){
		CLACT_U_RES_HEADER_SUB* data = head->tbl;

		ret_id = data[ no ].id;
	}else{
		CLACT_U_RES_HEADER_SUBARC* data = head->tbl;

		ret_id = data[ no ].id;
	}

	return ret_id;
}

//----------------------------------------------------------------------------
/**
 *	アーカイブファイル専用
 *
 *	@brief	ヘッダに登録されているアーカイブファイルIDを変更する
 *
 *	@param	head		リソースヘッダー
 *	@param	no			リソースヘッダー内に登録されているデータナンバー
 *	@param	param		設定するアーカイブファイルID
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void CLACT_U_ResManagerHeaderArcFileSet( CLACT_U_RES_HEADER_PTR head, int no, int param )
{
	GF_ASSERT( head );
	GF_ASSERT( head->tbl_num > no );
	
	if(head->arc_flag == 1){
		CLACT_U_RES_HEADER_SUBARC* data = head->tbl;

		data[ no ].arcFile = param;
	}
}

//----------------------------------------------------------------------------
/**
 *	アーカイブファイル専用
 *
 *	@brief	ヘッダに登録されているデータのアーカイブファイルIDを取得する
 *
 *	@param	head		リソースヘッダー
 *	@param	no			リソースヘッダー内に登録されているデータナンバー
 *
 *	@return	int		アーカイブファイルID
 *
 *
 */
//-----------------------------------------------------------------------------
int CLACT_U_ResManagerHeaderArcFileGet( CONST_CLACT_U_RES_HEADER_PTR head, int no )
{
	int ret_id;		// 戻り値用
	
	GF_ASSERT( head );
	GF_ASSERT( head->tbl_num > no );
	
	if(head->arc_flag == 1){
		CLACT_U_RES_HEADER_SUBARC* data = head->tbl;

		ret_id = data[ no ].arcFile;
	}

	return ret_id;
}

//----------------------------------------------------------------------------
/**
 *	アーカイブファイル専用
 *
 *	@brief	ヘッダに登録されているアーカイブidxを変更する
 *
 *	@param	head		リソースヘッダー
 *	@param	no			リソースヘッダー内に登録されているデータナンバー
 *	@param	param		設定するアーカイブファイルID
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void CLACT_U_ResManagerHeaderDataIdxSet( CLACT_U_RES_HEADER_PTR head, int no, int param )
{
	GF_ASSERT( head );
	GF_ASSERT( head->tbl_num > no );
	
	if(head->arc_flag == 1){
		CLACT_U_RES_HEADER_SUBARC* data = head->tbl;

		data[ no ].dataIdx = param;
	}
}

//----------------------------------------------------------------------------
/**
 *	アーカイブファイル専用
 *
 *	@brief	ヘッダに登録されているデータのデータidxを取得する
 *
 *	@param	head		リソースヘッダー
 *	@param	no			リソースヘッダー内に登録されているデータナンバー
 *
 *	@return	int			データidx
 *
 *
 */
//-----------------------------------------------------------------------------
int CLACT_U_ResManagerHeaderDataIdxGet( CONST_CLACT_U_RES_HEADER_PTR head, int no )
{
	int ret_id;		// 戻り値用
	
	GF_ASSERT( head );
	GF_ASSERT( head->tbl_num > no );
	
	if(head->arc_flag == 1){
		CLACT_U_RES_HEADER_SUBARC* data = head->tbl;

		ret_id = data[ no ].dataIdx;
	}

	return ret_id;
}

//----------------------------------------------------------------------------
/**
 *	アーカイブファイル専用
 *
 *	@brief	ヘッダに登録されている圧縮ファイルフラグを変更する
 *
 *	@param	head		リソースヘッダー
 *	@param	no			リソースヘッダー内に登録されているデータナンバー
 *	@param	param		設定するフラグ	（TRUE　FALSE）
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void CLACT_U_ResManagerHeaderCompFlagSet( CLACT_U_RES_HEADER_PTR head, int no, int param )
{
	GF_ASSERT( head );
	GF_ASSERT( head->tbl_num > no );
	
	if(head->arc_flag == 1){
		CLACT_U_RES_HEADER_SUBARC* data = head->tbl;

		data[ no ].compFlag = param;
	}
}

//----------------------------------------------------------------------------
/**
 *	アーカイブファイル専用
 *
 *	@brief	ヘッダに登録されているデータのデータidxを取得する
 *
 *	@param	head		リソースヘッダー
 *	@param	no			リソースヘッダー内に登録されているデータナンバー
 *
 *	@return	int			圧縮フラグ	（TRUE　FALSE）
 *
 *
 */
//-----------------------------------------------------------------------------
int CLACT_U_ResManagerHeaderCompFlagGet( CONST_CLACT_U_RES_HEADER_PTR head, int no )
{
	int ret_id;		// 戻り値用
	
	GF_ASSERT( head );
	GF_ASSERT( head->tbl_num > no );
	
	if(head->arc_flag == 1){
		CLACT_U_RES_HEADER_SUBARC* data = head->tbl;

		ret_id = data[ no ].compFlag;
	}

	return ret_id;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	ヘッダに登録されているVRamタイプを変更する
 *
 *	@param	head		リソースヘッダー
 *	@param	no			リソースヘッダー内に登録されているデータナンバー
 *	@param	param		設定するVRamタイプ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void CLACT_U_ResManagerHeaderVramTypeSet( CLACT_U_RES_HEADER_PTR head, int no, int param )
{
	GF_ASSERT( head );
	GF_ASSERT( head->tbl_num > no );
	
	if(head->arc_flag == 0){
		CLACT_U_RES_HEADER_SUB* data = head->tbl;

		data[ no ].ex[0]= param;
	}else{
		CLACT_U_RES_HEADER_SUBARC* data = head->tbl;

		data[ no ].ex[0] = param;
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	ヘッダに登録されているデータのVramTypeを取得する
 *
 *	@param	head		リソースヘッダー
 *	@param	no			リソースヘッダー内に登録されているデータナンバー
 *
 *	@return	int		VramType
 *
 *
 */
//-----------------------------------------------------------------------------
int CLACT_U_ResManagerHeaderVramTypeGet( CONST_CLACT_U_RES_HEADER_PTR head, int no )
{
	int ret_id;		// 戻り値用
	
	GF_ASSERT( head );
	GF_ASSERT( head->tbl_num > no );
	
	if(head->arc_flag == 0){
		CLACT_U_RES_HEADER_SUB* data = head->tbl;

		ret_id = data[ no ].ex[0];
	}else{
		CLACT_U_RES_HEADER_SUBARC* data = head->tbl;

		ret_id = data[ no ].ex[0];
	}

	return ret_id;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	ヘッダに登録されているパレット読み込み数を変更する
 *
 *	@param	head		リソースヘッダー
 *	@param	no			リソースヘッダー内に登録されているデータナンバー
 *	@param	param		設定するパレット読み込み数
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void CLACT_U_ResManagerHeaderPlttNumSet( CLACT_U_RES_HEADER_PTR head, int no, int param )
{
	GF_ASSERT( head );
	GF_ASSERT( head->tbl_num > no );
	
	if(head->arc_flag == 0){
		CLACT_U_RES_HEADER_SUB* data = head->tbl;

		data[ no ].ex[1]= param;
	}else{
		CLACT_U_RES_HEADER_SUBARC* data = head->tbl;

		data[ no ].ex[1] = param;
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	ヘッダに登録されているデータのパレット読み込み数を取得する
 *
 *	@param	head		リソースヘッダー
 *	@param	no			リソースヘッダー内に登録されているデータナンバー
 *
 *	@return	int		VramType
 *
 *
 */
//-----------------------------------------------------------------------------
int CLACT_U_ResManagerHeaderPlttNumGet( CONST_CLACT_U_RES_HEADER_PTR head, int no )
{
	int ret_id;		// 戻り値用
	
	GF_ASSERT( head );
	GF_ASSERT( head->tbl_num > no );
	
	if(head->arc_flag == 0){
		CLACT_U_RES_HEADER_SUB* data = head->tbl;

		ret_id = data[ no ].ex[1];
	}else{
		CLACT_U_RES_HEADER_SUBARC* data = head->tbl;

		ret_id = data[ no ].ex[1];
	}

	return ret_id;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	空いているリソースオブジェテーブルを取得
 *
 *@param	none
 *
 *@return	CLACT_U_RES_OBJ_PTR	リソースオブジェ
 *
 *
 */
//-----------------------------------------------------------------------------
static CLACT_U_RES_OBJ_PTR getCleanResObj(CLACT_U_RES_MANAGER_PTR resm)
{
	int i;

	for(i=0;i<resm->tbl_num;i++){
		if(resm->resObj[i].res_obj == NULL){
			return resm->resObj + i;
		}
	}

	return NULL;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	拡張データ作成
 *
 *@param	resObj		リソースオブジェ
 *@param	type		リソースタイプ
 *@param	vram_type	Vramタイプ
 *@param	pltt_num	パレット数
 *@param	heap		ヒープナンバー
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void makeExData(CLACT_U_RES_OBJ_PTR resObj, int type, int vram_type, int pltt_num, int heap)
{
	void* res;

	res = RESM_GetRes(resObj->res_obj);		// リソース取得
	
	switch(type){
	case CLACT_U_CHAR_RES:
		resObj->res_ex = makeExChar(res, vram_type, heap);
		break;
	case CLACT_U_PLTT_RES:
		resObj->res_ex = makeExPltt(res, vram_type, pltt_num, heap);
		break;
	case CLACT_U_CELL_RES:
		resObj->res_ex = makeExCell(res, heap);
		break;
	case CLACT_U_CELLANM_RES:
		resObj->res_ex = makeExCellAnm(res, heap);
		break;
	case CLACT_U_MULTI_RES:
		resObj->res_ex = makeExMulti(res, heap);
		break;
	case CLACT_U_MULTIANM_RES:
		resObj->res_ex = makeExMultiAnm(res, heap);
		break;
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	キャラクタ拡張データ作成
 *
 *@param	res			リソースポインタ
 *@param	vram_type	vramタイプ
 *@param	heap		使用ヒープ
 *
 *@return	CLACT_U_RES_EX_CHAR*	作成したデータ
 *
 *
 */
//-----------------------------------------------------------------------------
static CLACT_U_RES_EX_CHAR* makeExChar(void* res, int vram_type, int heap)
{
	CLACT_U_RES_EX_CHAR* data;

	data = sys_AllocMemory(heap, sizeof(CLACT_U_RES_EX_CHAR));
	NNS_G2dGetUnpackedCharacterData(res, &data->pCharData);
	data->vram_type = vram_type;
	
	return data;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	パレット拡張データを作成
 *
 *@param	res			リソースポインタ
 *@param	vram_type	Vramタイプ
 *@param	pltt_num	パレット数
 *@param	heap		使用ヒープ
 *
 *@return	CLACT_U_RES_EX_PLTT* 作成したデータ
 *
 *
 */
//-----------------------------------------------------------------------------
static CLACT_U_RES_EX_PLTT* makeExPltt(void* res, int vram_type, int pltt_num, int heap)
{
	CLACT_U_RES_EX_PLTT* data;

	data = sys_AllocMemory(heap, sizeof(CLACT_U_RES_EX_PLTT));
	NNS_G2dGetUnpackedPaletteData(res, &data->pPlttData);
	data->vram_type = vram_type;
	data->pltt_num	= pltt_num;

	return data;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	セル拡張データを作成
 *
 *@param	res		リソースポインタ
 *@param	heap	使用ヒープ
 *
 *@return	CLACT_U_RES_EX_CELL*	作成データ
 *
 *
 */
//-----------------------------------------------------------------------------
static CLACT_U_RES_EX_CELL* makeExCell(void* res, int heap)
{
	CLACT_U_RES_EX_CELL* data;

	data = sys_AllocMemory(heap, sizeof(CLACT_U_RES_EX_CELL));
	NNS_G2dGetUnpackedCellBank(res, &data->pCellData);

	return data;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	セルアニメ拡張データ作成
 *
 *@param	res		リソースポインタ
 *@param	heap	使用ヒープ
 *
 *@return	CLACT_U_RES_EX_CELLANM*	作成データ
 *
 *
 */
//-----------------------------------------------------------------------------
static CLACT_U_RES_EX_CELLANM*	makeExCellAnm(void* res, int heap)
{
	CLACT_U_RES_EX_CELLANM* data;

	data = sys_AllocMemory(heap, sizeof(CLACT_U_RES_EX_CELLANM));
	NNS_G2dGetUnpackedAnimBank(res, &data->pCellANMData);

	return data;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	マルチセル拡張データ作成
 *
 *@param	res		リソースポインタ
 *@param	heap	使用ヒープ
 *
 *@return	CLACT_U_RES_EX_MULTI*	作成データ
 *
 *
 */
//-----------------------------------------------------------------------------
static CLACT_U_RES_EX_MULTI*	makeExMulti(void* res, int heap)
{
	CLACT_U_RES_EX_MULTI* data;

	data = sys_AllocMemory(heap, sizeof(CLACT_U_RES_EX_MULTI));
	NNS_G2dGetUnpackedMultiCellBank(res, &data->pMultiData);

	return data;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	マルチセルアニメ拡張データ作成
 *
 *@param	res		リソースポインタ
 *@param	heap	使用ヒープ
 *
 *@return	CLACT_U_RES_EX_MULTIANM* 作成データ
 *
 *
 */
//-----------------------------------------------------------------------------
static CLACT_U_RES_EX_MULTIANM* makeExMultiAnm(void* res, int heap)
{
	CLACT_U_RES_EX_MULTIANM* data;

	data = sys_AllocMemory(heap, sizeof(CLACT_U_RES_EX_MULTIANM));
	NNS_G2dGetUnpackedMCAnimBank(res, &data->pMultiANMData);

	return data;
}


//----------------------------------------------------------------------------
/**
 *
 *@brief	それぞれの拡張データを破棄
 *
 *@param	リソースオブジェ	
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void delExData(CLACT_U_RES_OBJ_PTR resObj)
{
	if( resObj->res_ex ){
		sys_FreeMemoryEz(resObj->res_ex);
	}
	resObj->res_ex = NULL;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	拡張データ取得
 *
 *	@param	resObj	リソースオブジェ
 *
 *	@return	各拡張データ
 *
 *
 */
//-----------------------------------------------------------------------------
static void* getExData( CONST_CLACT_U_RES_OBJ_PTR resObj )
{
	GF_ASSERT( resObj );

	// CLACT_U_ResManagerResOnlyDeleteでデータを破棄した為、
	// データがありません。
	GF_ASSERT( resObj->res_ex );
	
	return resObj->res_ex;
}



//----------------------------------------------------------------------------
/**
 *
 *@brief	１つのデータを読み込む
 *
 *@param	resm	リソースマネージャー
 *@param	resObj	リソースオブジェ
 *@param	path	ファイルパス
 *@param	id		管理ID
 *@param	vram	vramタイプ
 *@param	pltt_numパレット使用量
 *@param	type	リソースタイプ
 *@param	heap	使用ヒープ
 *
 *@return	CLACT_U_RES_OBJ_PTR		リソースオブジェポインタ
 *
 *
 */
//-----------------------------------------------------------------------------
static void loadOneData(CLACT_U_RES_MANAGER_PTR resm, CLACT_U_RES_OBJ_PTR resObj, const char* path, int id, int vram, int pltt_num, int type, int heap)
{
	resObj->res_obj = RESM_AddRes(resm->res_manager, path, id, heap);	// リソース読み込み
	
	resObj->type = type;	// リソースタイプ
	
	// その他データ設定
	makeExData(resObj, type, vram, pltt_num, heap);
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	１つのアーカイブデータをリソースマネージャに設定する
 *
 *@param	resm		リソースマネージャデータ
 *@param	resObj		データ格納先リソースオブジェ
 *@param	arcFile		アーカイブファイルIｄｘ
 *@param	dataIdx		データIdx	
 *@param	compFlag	圧縮フラグ
 *@param	id			管理ID
 *@param	vram		Vramタイプ
 *@param	pltt_num	パレット読み込み数
 *@param	type		リソースタイプ
 *@param	heap		使用ヒープ
 *@param	alloc_type	アロケートタイプ
 *	ALLOC_TOP = 0,			///< ヒープの先頭から
 *	ALLOC_BOTTOM = 1,		///< ヒープの終端から
 *
 *@return	none
 *	
 *
 */
//-----------------------------------------------------------------------------
static void SetArcOneData(CLACT_U_RES_MANAGER_PTR resm, CLACT_U_RES_OBJ_PTR resObj, int arcFile, int dataIdx, BOOL compFlag, int id, int vram, int pltt_num, int type, int heap, u32 alloc_type)
{
	void* res;
	
	// リソース読み込み
	res = ArcUtil_Load(arcFile, dataIdx, compFlag, heap, alloc_type);

	// リソースマネージャーに設定
	resObj->res_obj = RESM_AddResNormal(resm->res_manager, res, id);

	// リソースタイプ
	resObj->type = type;
	
	// その他データ設定
	makeExData(resObj, type, vram, pltt_num, heap);
}

//----------------------------------------------------------------------------
/**
 *
 * ■アーカイブハンドル方式
 *
 *@brief	１つのアーカイブデータをリソースマネージャに設定する
 *
 *@param	resm		リソースマネージャデータ
 *@param	resObj		データ格納先リソースオブジェ
 *@param	arcHandle	アーカイブファイルハンドル
 *@param	dataIdx		データIdx	
 *@param	compFlag	圧縮フラグ
 *@param	id			管理ID
 *@param	vram		Vramタイプ
 *@param	pltt_num	パレット読み込み数
 *@param	type		リソースタイプ
 *@param	heap		使用ヒープ
 *@param	alloc_type	メモリ確保タイプ
 *
 *@return	none
 *	
 *
 */
//-----------------------------------------------------------------------------
static void SetArcOneData_ArcHandle(CLACT_U_RES_MANAGER_PTR resm, CLACT_U_RES_OBJ_PTR resObj, ARCHANDLE* arcHandle, int dataIdx, BOOL compFlag, int id, int vram, int pltt_num, int type, int heap, u32 alloc_type)
{
	void* res;
	
	res = ArcHandle_Load( arcHandle, dataIdx, compFlag, heap, alloc_type);

	// リソースマネージャーに設定
	resObj->res_obj = RESM_AddResNormal(resm->res_manager, res, id);

	// リソースタイプ
	resObj->type = type;
	
	// その他データ設定
	makeExData(resObj, type, vram, pltt_num, heap);
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	リソースデータタイプを取得
 *
 *@param	buff	ヘッダーデータ
 *
 *@return	int		リソースタイプ
 *
 *
 */
//-----------------------------------------------------------------------------
static int getHeaderType(char* buff)
{
	int no;
	char* tok;
	
	// 先頭にある
	tok	= strtok(buff, ",");
	
	no = atoi(tok);

	return no;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	アーカイブされたファイル用かを取得
 *
 *@param	buff	ヘッダーデータ
 *
 *@return	int		アーカイブされたデータようか
 *
 *
 */
//-----------------------------------------------------------------------------
static int getHeaderArc(char* buff)
{
	int no;
	char* tok;
	
	// 先頭から２番目
	tok	= strtok(buff, ",");
	tok	= strtok(NULL, ",");
	
	no = atoi(tok);

	return no;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	ヘッダーに登録されているデータ数を取得
 *
 *@param	buff	ヘッダーデータ
 *@param	type	ヘッダータイプ
 *@param	arcFlag	アーカイブファイルかどうかのフラグ
 *
 *@return	int		ヘッダー数
 *
 *
 */
//-----------------------------------------------------------------------------
static int getHeaderNum(char* buff, int type, int arcFlag)
{
	int count;			// データ数カウント
	char* path_or_arc;	// ファイルパスかアーカイブファイル
	char* data_idx;		// データインデックス
	char* commpFlag;	// 圧縮されたデータか
	char* id;			// ID
	char* vram;			// vram
	char* pltt;			// pltt

	// 最初の１つはリソースの種類なので飛ばす
	strtok(buff, ",");
	strtok(NULL, ",");
	strtok(NULL, "\n");
	
	count = 0;
	if(arcFlag == 0){
		loadHeaderCore(NULL, &path_or_arc,&id, &vram, &pltt, type);	// １つのデータ格納
	}else{
		loadHeaderCoreArc(NULL, &path_or_arc,&data_idx,&commpFlag,&id,&vram,&pltt,type);
	}
	
	// パスが'0'のデータが終端
	while(path_or_arc[0] != 'e'){
		count++;

		if(arcFlag == 0){
			loadHeaderCore(NULL, &path_or_arc, &id, &vram, &pltt, type);	// １回目以降はNULLでOK
		}else{
			loadHeaderCoreArc(NULL, &path_or_arc,&data_idx,&commpFlag,&id,&vram,&pltt,type);
		}

		if(path_or_arc == NULL){
			GF_ASSERT(0);		// 終端コードが無い
		}
	}

	return count;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	バイナリデータのヘッダーテーブル数を取得
 *
 *	@param	buff	バイナリデータ
 *
 *	@return	終了コードを入れないテーブル数
 *
 *
 */
//-----------------------------------------------------------------------------
static int getHeaderNumBinary( const CLACT_U_RES_HEADER_SUBARC* buff )
{
	int count;

	count = 0;
	while( buff[count].arcFile != CLACT_U_RES_HEADER_MAKE_END_CODE ){
		count++;
	}

	return count;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	ヘッダーデータを読み込み
 *
 *@param	buff	ヘッダーデータ
 *@param	type	リソースタイプ
 *@param	tbl		読み込み先
 *@param	num		読み込みすう
 *@param	arcFlag	アーカイブファイルかどうか
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void loadHeaderData(char* buff, int type, void* tbl, int num, int arcFlag)
{
	int i;		// ループ用
	char* path_or_arc;	// ファイルパスかアーカイブファイル
	char* data_idx;		// データインデックス
	char* commpFlag;	// 圧縮されたデータか
	char* id;			// ID
	char* vram;			// vram
	char* pltt;			// pltt

	// 最初の１つはリソースの種類なので飛ばす
	strtok(buff, ",");
	strtok(NULL, ",");
	strtok(NULL, "\n");

	// 読み込み
	for(i=0;i<num;i++){
		if(arcFlag == 0){
			loadHeaderCore(NULL, &path_or_arc, &id, &vram, &pltt, type);	// １つのデータ格納
			setDataHeader((CLACT_U_RES_HEADER_SUB*)tbl + i, path_or_arc, id, vram, pltt);
		}else{
			loadHeaderCoreArc(NULL, &path_or_arc,&data_idx,&commpFlag,&id,&vram,&pltt,type);
			setDataHeaderArc((CLACT_U_RES_HEADER_SUBARC*)tbl + i, path_or_arc, data_idx, commpFlag, id, vram, pltt);
		}
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	１つのデータを読み込んでくる
 *
 *@param	buff		ヘッダーデータ
 *@param	file_path	パス格納先
 *@param	id			ID格納先
 *@param	vram		Ｖｒａｍタイプ(NNS_G2D_VRAM_TYPE_2DMAIN,NNS_G2D_VRAM_TYPE_2DSUB,NNS_G2D_VRAM_TYPE_2DMAX)
 *@param	pltt		パレット格納先
 *@param	type		リソースタイプ
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void loadHeaderCore(char* buff, char** file_path, char** id, char** vram, char** pltt, int type)
{
	switch(type){
	case CLACT_U_CHAR_RES:
		loadCharHeaderCore(buff, file_path, id, vram);
		*pltt = NULL;
		break;
	case CLACT_U_PLTT_RES:
		loadPlttHeaderCore(buff, file_path, id, vram, pltt);
		break;
	case CLACT_U_CELL_RES:
	case CLACT_U_CELLANM_RES:
	case CLACT_U_MULTI_RES:
	case CLACT_U_MULTIANM_RES:
		loadKindCellHeaderCore(buff, file_path, id);
		*vram = NULL;
		*pltt = NULL;
		break;
	default:
		GF_ASSERT_MSG(0, "不正なフォーマットです\n");
		break;
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	１つのキャラクタデータを読み込む
 *
 *@param	buff	ヘッダーデータ
 *@param	path	パス格納先
 *@param	id		ID格納先
 *@param	type	Vramタイプ格納先
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void loadCharHeaderCore(char* buff, char** path, char** id, char** type)
{
	*path	= strtok(buff, ",");
	*id		= strtok(NULL, ",");
	*type	= strtok(NULL, ",");
	strtok(NULL, "\n");
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	パレットの１つのデータを取得
 *
 *@param	buff		ヘッダーデータ
 *@param	path		パス格納先
 *@param	id			ＩＤ格納先
 *@param	type		Ｖｒａｍタイプ(NNS_G2D_VRAM_TYPE_2DMAIN,NNS_G2D_VRAM_TYPE_2DSUB,NNS_G2D_VRAM_TYPE_2DMAX)
 *@param	pltt_num	パレット数
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void loadPlttHeaderCore(char* buff, char** path, char** id, char** type, char** pltt_num)
{
	*path		= strtok(buff, ",");
	*id			= strtok(NULL, ",");
	*type		= strtok(NULL, ",");
	*pltt_num	= strtok(NULL, ",");
	strtok(NULL, "\n");
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	セル類のヘッダーデータ格納
 *	
 *@param	buff	ヘッダーデータ
 *@param	path	パス格納先
 *@param	id		ＩＤ格納先
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void loadKindCellHeaderCore(char* buff, char** path, char** id)
{
	*path		= strtok(buff, ",");
	*id			= strtok(NULL, ",");
	strtok(NULL, "\n");
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	データ設定
 *
 *@param	head	設定先
 *@param	path	設定パス
 *@param	id		設定ＩＤ
 *@param	vram	設定Ｖｒａｍタイプ(NNS_G2D_VRAM_TYPE_2DMAIN,NNS_G2D_VRAM_TYPE_2DSUB,NNS_G2D_VRAM_TYPE_2DMAX)
 *@param	pltt	設定パレットナンバー
 *	
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void setDataHeader(CLACT_U_RES_HEADER_SUB* head, char* path, char* id, char* vram, char* pltt)
{
	strcpy(head->file_path, path);
	head->id = atoi(id);
	if(vram != NULL){
		head->ex[0] = atoi(vram);
	}else{
		head->ex[0] = 0;
	}
	if(pltt != NULL){
		head->ex[1] = atoi(pltt);
	}else{
		head->ex[1] = 0;
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	アーカイブファイル用ヘッダー読み込み関数
 *
 *@param	buff		ヘッダーデータ
 *@param	srcFile		アーカイブファイルID格納先
 *@param	dataIdx		データインデックス格納先
 *@param	compFlag	圧縮フラグ格納先
 *@param	id			管理ID格納先
 *@param	vram		Vramタイプ格納先
 *@param	pltt		パレット使用量格納先
 *@param	type		リソースタイプ
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void loadHeaderCoreArc(char* buff, char** srcFile, char** dataIdx, char** compFlag, char** id, char** vram, char** pltt, int type)
{
	switch(type){
	case CLACT_U_CHAR_RES:
		loadCharHeaderCoreArc(buff, srcFile, dataIdx, compFlag, id, vram);
		*pltt = NULL;
		break;
	case CLACT_U_PLTT_RES:
		loadPlttHeaderCoreArc(buff, srcFile, dataIdx, compFlag, id, vram, pltt);
		break;
	case CLACT_U_CELL_RES:
	case CLACT_U_CELLANM_RES:
	case CLACT_U_MULTI_RES:
	case CLACT_U_MULTIANM_RES:
		loadKindCellHeaderCoreArc(buff, srcFile, dataIdx, compFlag, id);
		*vram = NULL;
		*pltt = NULL;
		break;
	default:
		GF_ASSERT_MSG(0, "不正なフォーマットです\n");
		break;
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	キャラクタデータ読み込み
 *
 *@param	buff		ヘッダーデータ
 *@param	srcFile		アーカイブファイルID
 *@param	dataIdx		データインデックス
 *@param	compFlag	圧縮フラグ
 *@param	id			管理ID
 *@param	type		Vramタイプ
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void loadCharHeaderCoreArc(char* buff, char** srcFile, char** dataIdx, char** compFlag, char** id, char** type)
{
	*srcFile	= strtok(buff, ",");
	*dataIdx	= strtok(NULL, ",");
	*compFlag	= strtok(NULL, ",");
	*id			= strtok(NULL, ",");
	*type		= strtok(NULL, ",");
	strtok(NULL, "\n");
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	アーカイブ用パレットヘッダーデータ読み込み
 *
 *@param	buff		ヘッダーデータ
 *@param	srcFile		アーカイブファイルID
 *@param	dataIdx		データインデックス
 *@param	compFlag	圧縮フラグ
 *@param	id			管理ID
 *@param	type		Vramタイプ
 *@param	pltt_num	パレット使用量
 *
 *@return
 *
 *
 */
//-----------------------------------------------------------------------------
static void loadPlttHeaderCoreArc(char* buff, char** srcFile, char** dataIdx, char** compFlag, char** id, char** type, char** pltt_num)
{
	*srcFile	= strtok(buff, ",");
	*dataIdx	= strtok(NULL, ",");
	*compFlag	= strtok(NULL, ",");
	*id			= strtok(NULL, ",");
	*type		= strtok(NULL, ",");
	*pltt_num	= strtok(NULL, ",");
	strtok(NULL, "\n");
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	セル、セルアニメ、マルチセル、マルチセルアニメ
			アーカイブファイル用読み込み
 *
 *@param	buff		ヘッダーデータ
 *@param	srcFile		アーカイブファイルID
 *@param	dataIdx		データインデックス
 *@param	compFlag	圧縮フラグ
 *@param	id			管理ID
 *	
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void loadKindCellHeaderCoreArc(char* buff, char** srcFile, char** dataIdx, char** compFlag, char** id)
{
	*srcFile	= strtok(buff, ",");
	*dataIdx	= strtok(NULL, ",");
	*compFlag	= strtok(NULL, ",");
	*id			= strtok(NULL, ",");
	strtok(NULL, "\n");
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	ヘッダにデータを格納
 *
 *@param	head		格納先ヘッダ
 *@param	srcFile		アーカイブファイルID
 *@param	dataIdx		データインデックス
 *@param	compFlag	圧縮フラグ
 *@param	id			管理ID
 *@param	type		Vramタイプ
 *@param	pltt_num	パレット使用量
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void setDataHeaderArc(CLACT_U_RES_HEADER_SUBARC* head, char* arcFile, char* dataIdx, char* compFlag, char* id, char* type, char* pltt_num)
{
	head->arcFile	= atoi(arcFile);
	head->dataIdx	= atoi(dataIdx);
	head->compFlag	= atoi(compFlag);
	head->id		= atoi(id);
	if(type){
		head->ex[0]		= atoi(type);
	}else{
		head->ex[0]		= 0;
	}
	if(pltt_num){
		head->ex[1]		= atoi(pltt_num);
	}else{
		head->ex[1]		= 0;
	}
}

//------------------------------------------------------------------
/**
 * アーカイブデータの読み出し（メモリ確保する）
 *
 * @param	p_handle		アーカイブハンドル
 * @param   dataIdx			アーカイブデータインデックス
 * @param   compressedFlag	圧縮されているか？
 * @param	heapID			使用するヒープ
 * @param	alloc_type		アロックタイプ
 *
 * @retval  void*			読み出し領域ポインタ
 */
//------------------------------------------------------------------
static void* ArcHandle_Load(ARCHANDLE* p_handle, u32 dataIdx, BOOL compressedFlag, u32 heapID, u32 alloc_type)
{
	void* arcData;
	
	arcData = ArchiveDataLoadAllocByHandle( p_handle, dataIdx, heapID );

	if( arcData != NULL )
	{
		if( compressedFlag )
		{
			void* data;

			if( alloc_type == ALLOC_TOP ){
				data = sys_AllocMemory( heapID, MI_GetUncompressedSize( arcData ) );
			}else{
				data = sys_AllocMemoryLo( heapID, MI_GetUncompressedSize( arcData ) );
			}

			if( data )
			{
				MI_UncompressLZ8( arcData, data );
				sys_FreeMemoryEz( arcData );
			}
			arcData = data;
		}
	}

	return arcData;
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
char* makeCopyStr(const char* buff, int heap)
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
void delCopyStr(char* copy)
{
	sys_FreeMemoryEz(copy);
}
