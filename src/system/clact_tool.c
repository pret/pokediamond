//==============================================================================
/**
 * @file	clact_tool.c
 * @brief	clact上位関数群
 * @author	goto
 * @date	2005.09.12(月)
 *
 * ここに色々な解説等を書いてもよい
 *
 */
//==============================================================================

#include "common.h"
#include "system/lib_pack.h"
#include "system/bmp_list.h"

#include "clact_tool.h"
#include "system/palanm.h"


//
//
//	検索用ワード
//
//	[ CATS_SINGLE ]		単体登録関数郡
//
//	[ ACTOR_TOOL ]		アクター操作系ツール
//
//
//
//


//	■新しい

// -----------------------------------------
//
//	■CLACTのシステム本体(アプリに１個用意されるもの)
//
// -----------------------------------------
typedef struct _TCATS_SYSTEM {
	
	int							heap_area;			///< ヒープ領域
	
	int							resource_num;		///< システムが管理しているリソースの数
	
	int							render_use;			///< レンダーを使うか
	
	NNSG2dCellTransferState*	cellTransArray;		///< セルVram転送マネージャー領域
	
	CLACT_U_EASYRENDER_DATA		renddata;			///< レンダラーデータ
	
} TCATS_SYSTEM;



// -----------------------------------------
//
//	■単位登録用構造体(エフェクト１つに１個用意されるもの)
//
// -----------------------------------------
typedef struct _TCATS_RESOURCE {

	CLACT_SET_PTR				ca_sp;						///< セルアクターセット
	CLACT_HEADER_TBL_PTR		ca_htp;						///< セルアクターヘッダー
	CLACT_U_RES_HEADER_PTR		resHeader;					///< リソースヘッダー

	CLACT_U_RES_MANAGER_PTR		resManager[CLACT_U_RES_MAX];///< リソースマネージャー
	CLACT_U_RES_OBJ_TBL*		resObjTbl[CLACT_U_RES_MAX];	///< リソーステーブル(種類分)

	int							resObjNum[CLACT_U_RES_MAX];	///< リソース管理数
	int							resTypeNum;					///< リソース数(4or6)
	
} TCATS_RESOURCE;


// =============================================================================
//
//
//	■プロトタイプ
//
//
// =============================================================================




// =============================================================================
//
//
//	■外部参照
//
//
// =============================================================================
// =============================================================================
//
//
//	■共通関数 単体登録 ヘッダー登録兼用
//
//
// =============================================================================
//--------------------------------------------------------------
/**
 * @brief	システムのメモリ確保
 *
 * @param	heap_area			ヒープ領域指定
 *
 * @retval	CATS_SYS_PTR		確保したメモリのポインタ
 *
 */
//--------------------------------------------------------------
CATS_SYS_PTR CATS_AllocMemory(int heap_area)
{
	CATS_SYS_PTR csp = NULL;
	
	csp = sys_AllocMemory(heap_area, sizeof(TCATS_SYSTEM));
	
	if (csp == NULL){
		return NULL;
	}
	
	csp->heap_area		= heap_area;
	
	csp->resource_num	= 0;
	
	csp->render_use		= CATS_RENDER_USE_ON;
	
	return csp;
}


//--------------------------------------------------------------
/**
 * @brief	リソース用のメモリ確保
 *
 * @param	csp					システムポインタ
 *
 * @retval	CATS_RES_PTR		確保したメモリのポインタ
 *
 */
//--------------------------------------------------------------
CATS_RES_PTR CATS_ResourceCreate(CATS_SYS_PTR csp)
{
	int i;

	CATS_RES_PTR crp = NULL;

	GF_ASSERT(csp != NULL);

	crp = sys_AllocMemory(csp->heap_area, sizeof(TCATS_RESOURCE));
	
	if (crp == NULL){
		return NULL;
	}
	
	csp->resource_num++;
	
	for (i = 0; i < CLACT_U_RES_MAX; i++){
		crp->resManager[i] = NULL;
	}
	
	return crp;
}


//--------------------------------------------------------------
/**
 * @brief	リソースの数を取得
 *
 * @param	csp					システム
 *
 * @retval	int					数
 *
 */
//--------------------------------------------------------------
int CATS_ResourceNumGet(CATS_SYS_PTR csp)
{
	return csp->resource_num;
}


//--------------------------------------------------------------
/**
 * @brief	レンダラーデータを取得
 *
 * @param	csp					システム
 *
 * @retval	int					レンダラー
 *
 */
//--------------------------------------------------------------
CLACT_U_EASYRENDER_DATA * CATS_EasyRenderGet(CATS_SYS_PTR csp)
{
	return &csp->renddata;
}


//--------------------------------------------------------------
/**
 * @brief	システムの初期化
 *
 * @param	csp					システムポインタ
 * @param	coi					OAM初期化構造体のポインタ
 * @param	ccmm				キャラマネージャメイク構造体のポインタ
 * @param	pal_num				パレットの数
 *
 * @retval	BOOL				TRUE = 正常
 *
 */
//--------------------------------------------------------------
BOOL CATS_SystemInit(CATS_SYS_PTR csp, const TCATS_OAM_INIT* coi, const TCATS_CHAR_MANAGER_MAKE* ccmm, int pal_num)
{
	///< システムのメモリが確保されていない場合
	GF_ASSERT(csp != NULL);
	if (csp == NULL){
		return FALSE;
	}

	///< キャラクタマネージャー初期化
	{
		CHAR_MANAGER_MAKE cmm;
		cmm.CharDataNum			= ccmm->num;
		cmm.VramTransAreaMain	= ccmm->m_size;
		cmm.VramTransAreaSub	= ccmm->s_size;
		cmm.heap				= csp->heap_area;

		InitCharManagerReg(&cmm, ccmm->main_mode, ccmm->sub_mode);

//		InitCharManager(&cmm);
	}
	
	///< パレットマネージャー初期化
	InitPlttManager(pal_num, csp->heap_area);
	
	///< OAM マネージャーの初期化
	NNS_G2dInitOamManagerModule();

	///< レンダラの初期化
#ifdef CATS_RENDER_USE

	if (csp->render_use == CATS_RENDER_USE_ON){

		REND_OAMInit(coi->mos, coi->moe,
					 coi->mas, coi->mae,
					 coi->sos, coi->soe,
					 coi->sas, coi->sae,
					 csp->heap_area);

	}
#endif

	///< セルVram転送マネージャ作成
	csp->cellTransArray = InitCellTransfer(32, csp->heap_area);
	
	///< 読み込み開始オフセット初期化
	CharLoadStartAll();
	PlttLoadStartAll();
	
	return TRUE;
}


//--------------------------------------------------------------
/**
 * @brief	レンダーを使うかどうか
 *
 * @param	csp	
 * @param	flag	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void CATS_RenderUseSet(CATS_SYS_PTR csp, int flag)
{
	GF_ASSERT(csp != NULL);
	
	csp->render_use = flag;
}


//--------------------------------------------------------------
/**
 * @brief	セルアクターセットの作成
 *
 * @param	csp					システムポインタ
 * @param	crp					リソースポインタ
 * @param	num					登録OBJの数
 *
 * @retval	BOOL				TRUE = 正常
 *
 */
//--------------------------------------------------------------
BOOL CATS_ClactSetInit(CATS_SYS_PTR csp, CATS_RES_PTR crp, int num)
{
	///< システム・リソースどちらかがメモリ確保されていない
	if (csp == NULL || crp == NULL){
		return FALSE;
	}
	
	///< セルアクターセットの作成
	crp->ca_sp = CLACT_U_SetEasyInit(num,
									 &csp->renddata,
									 csp->heap_area);
	return TRUE;
}


//--------------------------------------------------------------
/**
 * @brief	OBJの削除
 *
 * @param	act					OBJ
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void CATS_ObjectDel(CLACT_WORK_PTR act)
{
	CLACT_Delete(act);
}


//--------------------------------------------------------------
/**
 * @brief	描画
 *
 * @param	crp					リソースポインタ
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void CATS_Draw(CATS_RES_PTR crp)
{
	GF_ASSERT(crp != NULL);
	
	CLACT_Draw(crp->ca_sp);
}


//--------------------------------------------------------------
/**
 * @brief	OAMの転送		※VBlank期間に呼ぶ
 *
 * @param	none	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void CATS_RenderOamTrans(void)
{
#ifdef CATS_RENDER_USE

	REND_OAMTrans();

#endif
}


//--------------------------------------------------------------
/**
 * @brief	OAMの転送		※VBlank期間に呼ぶ
 *
 * @param	csp	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void CATS_RenderOamTransEx(CATS_SYS_PTR csp)
{
	if (csp->render_use == CATS_RENDER_USE_ON){
		REND_OAMTrans();
	}
}


//--------------------------------------------------------------
/**
 * @brief	Vram転送登録
 *
 * @param	none	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void CATS_UpdateTransfer(void)
{
	UpdateCellTransfer();
}


//--------------------------------------------------------------
/**
 * @brief	セルアクターセット破棄
 *
 * @param	crp					リソースポインタ
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void CATS_ClactSetDelete(CATS_RES_PTR crp)
{
	CLACT_DestSet(crp->ca_sp);
}


//--------------------------------------------------------------
/**
 * @brief	ヘッダーテーブル破棄
 *
 * @param	crp					リソースポインタ
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void CATS_HeaderTblDelete(CATS_RES_PTR crp)
{
	if (crp->ca_htp == NULL){ return; }
	
	CLACT_U_CLACT_HeaderTblDelete(crp->ca_htp);
}


//--------------------------------------------------------------
/**
 * @brief	リソースの破棄
 *
 * @param	crp					リソースポインタ
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void CATS_ResourceDelete(CATS_RES_PTR crp)
{
	int i;
	CLACT_U_RES_HEADER_PTR res_head;
	
	for (i = 0; i < crp->resTypeNum; i++){
		
		///< リソースヘッダー破棄
		res_head = CLACT_U_ResManagerGetHeaderNoData(crp->resHeader, i);
		CLACT_U_ResManagerHeaderFree(res_head);

	}
	sys_FreeMemoryEz(crp->resHeader);
	
	///< データ破棄
	CLACT_U_CharManagerDeletes(crp->resObjTbl[0]);
	CLACT_U_PlttManagerDeletes(crp->resObjTbl[1]);
	
	
	for (i = 0; i < crp->resTypeNum; i++){
		
		///< リソースオブジェテーブル破棄
		CLACT_U_ResManagerResObjTblDelete(crp->resObjTbl[i]);
		
		///< リソースマネージャー破棄
		CLACT_U_ResManagerDelete(crp->resManager[i]);
	}	
}


//--------------------------------------------------------------
/**
 * @brief	マネージャー破棄
 *
 * @param	csp					システムポインタ
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void CATS_ManagerDelete(CATS_SYS_PTR csp)
{
	DeleteCellTransfer(csp->cellTransArray);
	
	DeleteCharManager();
	
	DeletePlttManager();

#ifdef CATS_RENDER_USE

	if (csp->render_use == CATS_RENDER_USE_ON){

		REND_OAM_Delete();
		
	}

#endif
}


//--------------------------------------------------------------
/**
 * @brief	リソースのメモリ解放
 *
 * @param	crp					リソースポインタ
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void CATS_ResourceFree(CATS_SYS_PTR csp, CATS_RES_PTR crp)
{
	csp->resource_num--;
	sys_FreeMemoryEz(crp);
}


//--------------------------------------------------------------
/**
 * @brief	デストラクター 解放処理を一手に行ないます
 *
 * @param	csp					システムポインタ
 * @param	crp					リソースポインタ
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void CATS_ResourceDestructor(CATS_SYS_PTR csp, CATS_RES_PTR crp)
{
	CATS_ClactSetDelete(crp);		///< セルセット破棄
	CATS_HeaderTblDelete(crp);		///< ヘッダーテーブル破棄
	CATS_ResourceDelete(crp);		///< リソース破棄
//	CATS_ManagerDelete(csp);		///< マネージャ破棄
	CATS_ResourceFree(csp, crp);	///< リソースのメモリ破棄
//	CATS_FreeMemory(csp);			///< システム本体のメモリ破棄
}


//--------------------------------------------------------------
/**
 * @brief	システムのメモリ破棄
 *
 * @param	csp					システムのメモリ破棄
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void CATS_FreeMemory(CATS_SYS_PTR csp)
{
	GF_ASSERT(csp->resource_num == 0);
	
	CATS_ManagerDelete(csp);
	sys_FreeMemoryEz(csp);
}






// =============================================================================
//
//
//	■ヘッダー登録用
//
//
// =============================================================================
//--------------------------------------------------------------
/**
 * @brief	リソースの読み込み
 *
 * @param	csp					システムポインタ
 * @param	crp					リソースポインタ
 * @param	res_list			リソースリスト構造体ポインタ
 *
 * @retval	BOOL				TRUE = 正常
 *
 */
//--------------------------------------------------------------
BOOL CATS_ResourceLoad(CATS_SYS_PTR csp, CATS_RES_PTR crp, const TCATS_RESOURCE_FILE_LIST* res_list)
{
	int i;
	int num = CLACT_U_RES_MAX;	
	int size;
	CLACT_U_RES_HEADER_PTR res_head;
	
	///< システム・リソースどちらかがメモリ確保されていない
	if (csp == NULL || crp == NULL){
		return FALSE;
	}
	
	///< マルチセルが無い場合
	if (res_list->resource.mcell_path == NULL){
		num = CLACT_U_RES_MAX - 2;
	}
	crp->resTypeNum = num;
	
	///< リソースマネージャー用ヘッダー領域の作成
	size = CLACT_U_ResManagerGetHeaderSize();
	crp->resHeader = sys_AllocMemory(csp->heap_area, size * num);
	
	///< リソースマネージャー用ヘッダー読み込み
	for (i = 0; i < num; i++){
		res_head = CLACT_U_ResManagerGetHeaderNoData(crp->resHeader, i);
		CLACT_U_ResManagerHeaderLoad(res_list->res_file[i], res_head, csp->heap_area);
	}

	///< リソースマネージャー作成
	for (i = 0; i < num; i++){
		res_head = CLACT_U_ResManagerGetHeaderNoData(crp->resHeader, i);
		size    		  = CLACT_U_ResManagerHeaderSetDataNum(res_head);
		crp->resManager[i] = CLACT_U_ResManagerInit(size, i, csp->heap_area);
	}

	///< リソースマネージャーに登録するデータ読み込み
	for (i = 0; i < num; i++){
		res_head		  = CLACT_U_ResManagerGetHeaderNoData(crp->resHeader, i);
		size    		  = CLACT_U_ResManagerHeaderSetDataNum(res_head);
		crp->resObjTbl[i] = CLACT_U_ResManagerResObjTblMake(size, csp->heap_area);
		crp->resObjNum[i] = CLACT_U_ResManagerResAddsHd(crp->resManager[i],
														res_head,
														crp->resObjTbl[i],
														csp->heap_area);
	}
	
	///< マネージャに登録
	CLACT_U_CharManagerSets(crp->resObjTbl[0]);
	CLACT_U_PlttManagerSets(crp->resObjTbl[1]);
	
	///< セルアクターヘッダー読み込み
	crp->ca_htp = CLACT_U_LoadHeaderTbl(res_list->resource.clact_header_path,
										csp->heap_area,
										crp->resManager[0], crp->resManager[1],
										crp->resManager[2],	crp->resManager[3],
										crp->resManager[4], crp->resManager[5]);
	return TRUE;
}

BOOL CATS_ResourceLoadBinary(
			CATS_SYS_PTR csp, CATS_RES_PTR crp, const TCATS_RESOURCE_FILE_LIST* res_list )
{
	int i;
	int num = CLACT_U_RES_MAX;	
	int size;
	CLACT_U_RES_HEADER_PTR res_head;
	void * buf;
	
	///< システム・リソースどちらかがメモリ確保されていない
	if (csp == NULL || crp == NULL){
		return FALSE;
	}
	
	///< マルチセルが無い場合
	if (res_list->resource.mcell_path == NULL){
		num = CLACT_U_RES_MAX - 2;
	}
	crp->resTypeNum = num;
	
	///< リソースマネージャー用ヘッダー領域の作成
	size = CLACT_U_ResManagerGetHeaderSize();
	crp->resHeader = sys_AllocMemory(csp->heap_area, size * num);
	
	///< リソースマネージャー用ヘッダー読み込み
	for (i = 0; i < num; i++){
		res_head = CLACT_U_ResManagerGetHeaderNoData(crp->resHeader, i);
//		CLACT_U_ResManagerHeaderLoad(res_list->res_file[i], res_head, csp->heap_area);
		buf = sys_LoadFile( csp->heap_area, res_list->res_file[i] );
		CLACT_U_ResManagerHeaderLoadBinary( buf, res_head, csp->heap_area );
		sys_FreeMemoryEz( buf );
	}

	///< リソースマネージャー作成
	for (i = 0; i < num; i++){
		res_head = CLACT_U_ResManagerGetHeaderNoData(crp->resHeader, i);
		size    		  = CLACT_U_ResManagerHeaderSetDataNum(res_head);
		crp->resManager[i] = CLACT_U_ResManagerInit(size, i, csp->heap_area);
	}

	///< リソースマネージャーに登録するデータ読み込み
	for (i = 0; i < num; i++){
		res_head		  = CLACT_U_ResManagerGetHeaderNoData(crp->resHeader, i);
		size    		  = CLACT_U_ResManagerHeaderSetDataNum(res_head);
		crp->resObjTbl[i] = CLACT_U_ResManagerResObjTblMake(size, csp->heap_area);
		crp->resObjNum[i] = CLACT_U_ResManagerResAddsHd(crp->resManager[i],
														res_head,
														crp->resObjTbl[i],
														csp->heap_area);
	}
	
	///< マネージャに登録
	CLACT_U_CharManagerSets(crp->resObjTbl[0]);
	CLACT_U_PlttManagerSets(crp->resObjTbl[1]);
	
	///< セルアクターヘッダー読み込み
/*
	crp->ca_htp = CLACT_U_LoadHeaderTbl(res_list->resource.clact_header_path,
										csp->heap_area,
										crp->resManager[0], crp->resManager[1],
										crp->resManager[2],	crp->resManager[3],
										crp->resManager[4], crp->resManager[5]);
*/
	buf = sys_LoadFile( csp->heap_area, res_list->resource.clact_header_path );
	crp->ca_htp = CLACT_U_MakeHeaderBinary(
						buf, csp->heap_area,
						crp->resManager[0], crp->resManager[1],
						crp->resManager[2],	crp->resManager[3],
						crp->resManager[4], crp->resManager[5] );
	sys_FreeMemoryEz( buf );

	return TRUE;
}

/*
GLOBAL CLACT_HEADER_TBL_PTR CLACT_U_MakeHeaderBinary(
		const CLACT_U_HEADER_MAKE_BINDATA* bindata,
		int heap,
		CLACT_U_RES_MANAGER_PTR charResMan,
		CLACT_U_RES_MANAGER_PTR plttResMan,
		CLACT_U_RES_MANAGER_PTR cellResMan,
		CLACT_U_RES_MANAGER_PTR cellAnmResMan,
		CLACT_U_RES_MANAGER_PTR multiCellResMan,
		CLACT_U_RES_MANAGER_PTR multiCellAnmResMan);
*/


//--------------------------------------------------------------
/**
 * @brief	可変引数でリソースを読み込む
 *
 * @param	csp					システムポインタ
 * @param	crp					リソースポインタ
 * @param	...					ファイルパス可変個 基本5-7
 *
 * @retval	BOOL	
 *
 */
//--------------------------------------------------------------
#ifdef CATS_CBP_RES_LOAD		///< 可変引数

BOOL CATS_ResourceLoad_FileName(CATS_SYS_PTR csp, CATS_RES_PTR crp, ...)
{
	int i;
	int num;
	va_list ap;
	char* file;
	TCATS_RESOURCE_FILE_LIST list;
	
	va_start(ap, crp);
	
	num = 0;
	for (i = 0; i < CLACT_U_RES_MAX + 1; i++){
		file = va_arg(ap, char*);
		list.res_file[i] = file;
		
		if (file == NULL){
			break;
		}
		num++;
	}
	
	if (num != 5 && num != 7){
		return FALSE;
	}
	
	if (list.resource.clact_header_path == NULL
	||	list.resource.mcell_path != NULL){
		list.resource.clact_header_path = list.resource.mcell_path;
		list.resource.mcell_path		= NULL;
	}
	
	va_end(ap);
	
	return CATS_ResourceLoad(csp, crp, &list);;
}

#endif	///< 可変引数


//--------------------------------------------------------------
/**
 * @brief	OBJ登録
 *
 * @param	csp					システムポインタ
 * @param	crp					リソースポインタ
 * @param	coap				OBJ登録用構造体ポインタ
 *
 * @retval	CLACT_WORK_PTR	登録したOBJのポインタ
 *
 */
//--------------------------------------------------------------
CLACT_WORK_PTR CATS_ObjectAdd(CATS_SYS_PTR csp, CATS_RES_PTR crp, const TCATS_OBJECT_ADD_PARAM* coap)
{
	CLACT_WORK_PTR act = NULL;
	
	act = CATS_ObjectAdd_EX(csp, crp,
							coap->no,
							coap->x, coap->y, coap->x,
							coap->anm, coap->pri, coap->pal, coap->d_area,
							coap->param1, coap->param2, coap->param3, coap->param4);
	return act;
}


//--------------------------------------------------------------
/**
 * @brief	
 *
 * @param	csp					システムポインタ
 * @param	crp					リソースポインタ
 * @param	no					ヘッダー内の登録番号
 * @param	x					座標 x
 * @param	y					座標 y
 * @param	z					座標 z
 * @param	anm					アニメ
 * @param	pri					優先度
 * @param	pal					パレット番号
 * @param	d_area				描画エリア
 * @param	param1				予備1
 * @param	param2				予備2
 * @param	param3				予備3
 * @param	param4				予備4
 *
 * @retval	CLACT_WORK_PTR	登録したOBJのポインタ
 *
 */
//--------------------------------------------------------------
CLACT_WORK_PTR CATS_ObjectAdd_EX(CATS_SYS_PTR csp, CATS_RES_PTR crp, int no,
									 s16 x, s16 y, s16 z, u16 anm, int pri, int pal, int d_area,
									 int param1, int param2, int param3, int param4)
{
	CLACT_WORK_PTR act = NULL;
	CLACT_ADD add;
	
	add.ClActSet	= crp->ca_sp;				///< セルアクターセット
	add.ClActHeader = &crp->ca_htp->tbl[no];	///< ヘッダーから取り出し
	
	add.mat.x		= FX32_CONST(x);			///< 座標
	add.mat.y		= FX32_CONST(y);
	add.mat.z		= FX32_CONST(z);
	if(d_area == NNS_G2D_VRAM_TYPE_2DSUB){
		add.mat.y += SUB_SURFACE_Y;
	}
	
	add.sca.x		= FX32_ONE;					///< 拡縮率
	add.sca.y		= FX32_ONE;
	add.sca.z		= FX32_ONE;
	
	add.rot			= 0;						///< 回転角
	add.pri			= pri;						///< 優先度
	add.DrawArea	= d_area;					///< 描画面
	add.heap		= csp->heap_area;			///< ヒープ領域
	
	act = CLACT_Add(&add);					///< 登録
	
	if (act != NULL){
		CLACT_AnmChg(act, anm);				///< アニメーション指定
		CLACT_PaletteNoChg(act, pal);		///< パレット指定
	}
	
	return act;	
}










// =============================================================================
//
//
//
//	■単体で任意のリソースを登録していく関数郡	[ CATS_SINGLE ]
//
//
//
// =============================================================================
// ----------------------------------------------------------------------------
//
//	単体で読み込む場合
//
static BOOL CATS_LoadResourceCell_Private(CATS_SYS_PTR csp, CATS_RES_PTR crp, const char* path, int type, int id);
static BOOL CATS_LoadResourceCellArc_Private(CATS_SYS_PTR csp, CATS_RES_PTR crp, int arc_id, int data_id, int comp, int type, int id);
static BOOL	CATS_LoadResourceTable_Private(CLACT_U_RES_OBJ_TBL* tbl, CLACT_U_RES_OBJ_PTR obj);
static BOOL CATS_DeleteResourceCharData_Private(CLACT_U_RES_MANAGER_PTR resm, CLACT_U_RES_OBJ_TBL* tbl, int id);
static BOOL CATS_DeleteResourcePlttData_Private(CLACT_U_RES_MANAGER_PTR resm, CLACT_U_RES_OBJ_TBL* tbl, int id);
static BOOL CATS_DeleteResourceData_Private(CLACT_U_RES_MANAGER_PTR resm, CLACT_U_RES_OBJ_TBL* tbl, int id);

//--------------------------------------------------------------
/**
 * @brief	リソースマネージャの初期化
 *
 * @param	csp					システム
 * @param	crp					リソース
 * @param	crnl				リソース管理数テーブル
 *
 * @retval	BOOL				TRUE = 成功
 *
 */
//--------------------------------------------------------------
BOOL CATS_ResourceManagerInit(CATS_SYS_PTR csp, CATS_RES_PTR crp, const TCATS_RESOURCE_NUM_LIST* crnl)
{
	int i;
	int j;
	int num = CLACT_U_RES_MAX;
	int size;
	CLACT_U_RES_HEADER_PTR res_head;
	
	///< システム・リソースどちらかがメモリ確保されていない
	if (csp == NULL || crp == NULL){
		return FALSE;
	}
	
	///< マルチセルを利用しない場合は管理マネージャの数を減らす
	if (crnl->resource_num.mcell_num == 0
	||	crnl->resource_num.mcell_anm_num == 0){
		num = CLACT_U_RES_MAX - 2;
	}
	crp->resTypeNum = num;
	
	///< リソースマネージャー作成
	for (i = 0; i < num; i++){
		crp->resManager[i] = CLACT_U_ResManagerInit(crnl->res_num[i], i, csp->heap_area);
	}
	
	///< リソースマネージャーに登録するデータ読み込み
	for (i = 0; i < num; i++){
		size = crnl->res_num[i];
		
		if (size == 0){ continue; }
		
		crp->resObjTbl[i] = CLACT_U_ResManagerResObjTblMake(size, csp->heap_area);
		crp->resObjNum[i] = 0;
		
		for (j = 0; j < crp->resObjTbl[i]->tbl_num; j++){
			crp->resObjTbl[i]->tbl[j] = NULL;
		}
	}

	return TRUE;
}


//--------------------------------------------------------------
/**
 * @brief	キャラの登録	パス
 *
 * @param	csp	
 * @param	crp	
 * @param	path	
 * @param	id					管理ID
 *
 * @retval	BOOL	
 *
 */
//--------------------------------------------------------------
BOOL CATS_LoadResourceChar(CATS_SYS_PTR csp, CATS_RES_PTR crp, const char* path, int trans_mode, int id)
{
	CLACT_U_RES_OBJ_PTR obj;

	if (CLACT_U_ResManagerCheckID(crp->resManager[0], id) == FALSE){
		return FALSE;
	}
	
	obj = CLACT_U_ResManagerResAddChar(crp->resManager[0], path, id, trans_mode, csp->heap_area);

	if (obj != NULL){
		CLACT_U_CharManagerSetAreaCont(obj);
		
		CATS_LoadResourceTable_Private(crp->resObjTbl[0], obj);
		
		return TRUE;
	}
	
	GF_ASSERT(0);
	
	return obj == NULL ? FALSE : TRUE;
}


//--------------------------------------------------------------
/**
 * @brief	キャラの登録	アーカイブ
 *
 * @param	csp	
 * @param	crp	
 * @param	arc_id				アーカイブIndex
 * @param	data_id				データIndex
 * @param	comp				圧縮フラグ
 * @param	id					管理ID
 *
 * @retval	BOOL	
 *
 */
//--------------------------------------------------------------
BOOL CATS_LoadResourceCharArc(CATS_SYS_PTR csp, CATS_RES_PTR crp, int arc_id, int data_id, BOOL comp, int trans_mode, int id)
{
	CLACT_U_RES_OBJ_PTR obj;

	if (CLACT_U_ResManagerCheckID(crp->resManager[0], id) == FALSE){
		return FALSE;
	}
	
	obj = CLACT_U_ResManagerResAddArcChar(crp->resManager[0], arc_id, data_id, comp, id, trans_mode, csp->heap_area);

	if (obj != NULL){
		CLACT_U_CharManagerSetAreaCont(obj);
		
		CATS_LoadResourceTable_Private(crp->resObjTbl[0], obj);	
		
		return TRUE;
	}
	
	GF_ASSERT(0);
	
	return obj == NULL ? FALSE : TRUE;
}


//--------------------------------------------------------------
/**
 * @brief	パレット登録	パス
 *
 * @param	csp	
 * @param	crp	
 * @param	path				パス
 * @param	num					登録数
 * @param	id					管理ID
 *
 * @retval	登録した位置のパレット番号(失敗時はASSERTで停止します)
 *
 */
//--------------------------------------------------------------
u8 CATS_LoadResourcePltt(CATS_SYS_PTR csp, CATS_RES_PTR crp, const char* path, int num, int trans_mode, int id)
{
	CLACT_U_RES_OBJ_PTR obj;
	int ret;
	
	if (CLACT_U_ResManagerCheckID(crp->resManager[1], id) == FALSE){
		return FALSE;
	}
	
	obj = CLACT_U_ResManagerResAddPltt(crp->resManager[1], path, id, trans_mode, num, csp->heap_area);

	if (obj != NULL){
//		CLACT_U_PlttManagerSet(obj);
		ret = CLACT_U_PlttManagerSetCleanArea(obj);
		GF_ASSERT(ret == TRUE && "パレット登録失敗");
		
		CATS_LoadResourceTable_Private(crp->resObjTbl[1], obj);	
		
		return CLACT_U_PlttManagerGetPlttNo(obj, trans_mode);	//登録所のパレット番号を返す
	}
	
	GF_ASSERT(0);
	
	return 0;
}


//--------------------------------------------------------------
/**
 * @brief	パレット登録	アーカイブ
 *
 * @param	csp	
 * @param	crp	
 * @param	arc_id				アーカイブIndex
 * @param	data_id				データIndex
 * @param	comp				圧縮フラグ
 * @param	num					登録数
 * @param	id					管理ID
 *
 * @retval	登録した位置のパレット番号(失敗時はASSERTで停止します)
 *
 */
//--------------------------------------------------------------
s8 CATS_LoadResourcePlttArc(CATS_SYS_PTR csp, CATS_RES_PTR crp, int arc_id, int data_id, int comp, int num, int trans_mode, int id)
{
	CLACT_U_RES_OBJ_PTR obj;
	int ret;
	
	if (CLACT_U_ResManagerCheckID(crp->resManager[1], id) == FALSE){
		return -1;
	}
	
	obj = CLACT_U_ResManagerResAddArcPltt(crp->resManager[1], arc_id, data_id, comp, id, trans_mode, num, csp->heap_area);

	if (obj != NULL){
		//CLACT_U_PlttManagerSet(obj);
		ret = CLACT_U_PlttManagerSetCleanArea(obj);
		GF_ASSERT(ret == TRUE && "パレット登録失敗");
		
		CATS_LoadResourceTable_Private(crp->resObjTbl[1], obj);	
		return CLACT_U_PlttManagerGetPlttNo(obj, trans_mode);	//登録所のパレット番号を返す
	}
	
	GF_ASSERT(0);
	
	return -1;
}

//--------------------------------------------------------------
/**
 * @brief   パレット登録し、パレットワークにも展開を行う
 *
 * @param   PALETTE_FADE_PTR		パレットフェードシステムへのポインタ
 * @param   req						リクエストデータ番号(FADE_MAIN_BG等)
 * @param   csp						
 * @param   crp						
 * @param	arc_id					アーカイブIndex
 * @param	data_id					データIndex
 * @param	comp					圧縮フラグ
 * @param	num						登録数
 * @param   trans_mode				NNS_G2D_VRAM_TYPE_2DMAIN等
 * @param	id						管理ID
 *
 * @retval  セットしたパレット位置(失敗時はASSERTで停止します)
 */
//--------------------------------------------------------------
u8 CATS_LoadResourcePlttWork(PALETTE_FADE_PTR pfd, FADEREQ req, CATS_SYS_PTR csp, 
	CATS_RES_PTR crp, const char* path, int num, int trans_mode, int id)
{
	int pal_no;
	
	pal_no = CATS_LoadResourcePltt(csp, crp, path, num, trans_mode, id);
	PaletteWorkSet_VramCopy(pfd, req, pal_no * 16, num * 0x20);
	return pal_no;
}

//--------------------------------------------------------------
/**
 * @brief   パレット登録し、パレットワークにも展開を行う
 *
 * @param   PALETTE_FADE_PTR		パレットフェードシステムへのポインタ
 * @param   req						リクエストデータ番号(FADE_MAIN_BG等)
 * @param   csp						
 * @param   crp						
 * @param	arc_id					アーカイブIndex
 * @param	data_id					データIndex
 * @param	comp					圧縮フラグ
 * @param	num						登録数
 * @param   trans_mode				NNS_G2D_VRAM_TYPE_2DMAIN等
 * @param	id						管理ID
 *
 * @retval  セットしたパレット位置(失敗時はASSERTで停止します)
 */
//--------------------------------------------------------------
u8 CATS_LoadResourcePlttWorkArc(PALETTE_FADE_PTR pfd, FADEREQ req, CATS_SYS_PTR csp, 
	CATS_RES_PTR crp, int arc_id, int data_id, int comp, int num, int trans_mode, int id)
{
	int pal_no;

	pal_no = CATS_LoadResourcePlttArc(csp, crp, arc_id, data_id, comp, num, trans_mode, id);

	if (pal_no != -1){
		PaletteWorkSet_VramCopy(pfd, req, pal_no * 16, num * 0x20);
	}
	return pal_no;
}

//--------------------------------------------------------------
/**
 * @brief	セル登録	パス
 *
 * @param	csp	
 * @param	crp	
 * @param	path				パス
 * @param	id					管理ID
 *
 * @retval	BOOL	
 *
 */
//--------------------------------------------------------------
BOOL CATS_LoadResourceCell(CATS_SYS_PTR csp, CATS_RES_PTR crp, const char* path, int id)
{
	return CATS_LoadResourceCell_Private(csp, crp, path, 2, id);
}


//--------------------------------------------------------------
/**
 * @brief	セル登録			アーカイブ
 *
 * @param	csp	
 * @param	crp	
 * @param	arc_id				アーカイブIndex
 * @param	data_id				データIndex
 * @param	comp				圧縮フラグ
 * @param	id					管理ID
 *
 * @retval	BOOL	
 *
 */
//--------------------------------------------------------------
BOOL CATS_LoadResourceCellArc(CATS_SYS_PTR csp, CATS_RES_PTR crp, int arc_id, int data_id, int comp, int id)
{
	return CATS_LoadResourceCellArc_Private(csp, crp, arc_id, data_id, comp, 2, id);
}


//--------------------------------------------------------------
/**
 * @brief	セルアニメ登録	パス
 *
 * @param	csp	
 * @param	crp	
 * @param	path				パス
 * @param	id					管理ID
 *
 * @retval	BOOL	
 *
 */
//--------------------------------------------------------------
BOOL CATS_LoadResourceCellAnm(CATS_SYS_PTR csp, CATS_RES_PTR crp, const char* path, int id)
{
	return CATS_LoadResourceCell_Private(csp, crp, path, 3, id);
}


//--------------------------------------------------------------
/**
 * @brief	セルアニメ登録	アーカイブ
 *
 * @param	csp	
 * @param	crp	
 * @param	arc_id				アーカイブIndex
 * @param	data_id				データIndex
 * @param	comp				圧縮フラグ
 * @param	id					管理ID
 *
 * @retval	BOOL	
 *
 */
//--------------------------------------------------------------
BOOL CATS_LoadResourceCellAnmArc(CATS_SYS_PTR csp, CATS_RES_PTR crp, int arc_id, int data_id, int comp, int id)
{
	return CATS_LoadResourceCellArc_Private(csp, crp, arc_id, data_id, comp, 3, id);
}


//--------------------------------------------------------------
/**
 * @brief	マルチセル登録			アーカイブ
 *
 * @param	csp	
 * @param	crp	
 * @param	arc_id				アーカイブIndex
 * @param	data_id				データIndex
 * @param	comp				圧縮フラグ
 * @param	id					管理ID
 *
 * @retval	BOOL	
 *
 */
//--------------------------------------------------------------
BOOL CATS_LoadResourceMCell(CATS_SYS_PTR csp, CATS_RES_PTR crp, const char* path, int id)
{
	return CATS_LoadResourceCell_Private(csp, crp, path, 4, id);
}


//--------------------------------------------------------------
/**
 * @brief	マルチセル登録			アーカイブ
 *
 * @param	csp	
 * @param	crp	
 * @param	arc_id				アーカイブIndex
 * @param	data_id				データIndex
 * @param	comp				圧縮フラグ
 * @param	id					管理ID
 *
 * @retval	BOOL	
 *
 */
//--------------------------------------------------------------
BOOL CATS_LoadResourceMCellArc(CATS_SYS_PTR csp, CATS_RES_PTR crp, int arc_id, int data_id, int comp, int id)
{
	return CATS_LoadResourceCellArc_Private(csp, crp, arc_id, data_id, comp, 4, id);
}


//--------------------------------------------------------------
/**
 * @brief	マルチセルアニメ	パス
 *
 * @param	csp	
 * @param	crp	
 * @param	path				パス
 * @param	id					管理ID
 *
 * @retval	BOOL	
 *
 */
//--------------------------------------------------------------
BOOL CATS_LoadResourceMCellAnm(CATS_SYS_PTR csp, CATS_RES_PTR crp, const char* path, int id)
{
	return CATS_LoadResourceCell_Private(csp, crp, path, 5, id);
}


//--------------------------------------------------------------
/**
 * @brief	マルチセルアニメ	アーカイブ
 *
 * @param	csp	
 * @param	crp	
 * @param	arc_id				アーカイブIndex
 * @param	data_id				データIndex
 * @param	comp				圧縮フラグ
 * @param	id					管理ID
 *
 * @retval	BOOL	
 *
 */
//--------------------------------------------------------------
BOOL CATS_LoadResourceMCellAnmArc(CATS_SYS_PTR csp, CATS_RES_PTR crp, int arc_id, int data_id, int comp, int id)
{
	return CATS_LoadResourceCellArc_Private(csp, crp, arc_id, data_id, comp, 5, id);
}


//--------------------------------------------------------------
/**
 * @brief	アクター登録	リソースID指定
 *
 * @param	csp					システム
 * @param	crp					リソース
 * @param	coap_s				登録パラメーター
 *
 * @retval	CATS_ACT_PTR		アクター管理ワークポインタ
 *
 */
//--------------------------------------------------------------
CATS_ACT_PTR CATS_ObjectAdd_S(CATS_SYS_PTR csp, CATS_RES_PTR crp, const TCATS_OBJECT_ADD_PARAM_S* coap_s)
{
	int i;
	int def_palno;
	CATS_ACT_PTR cap = NULL;
	CLACT_ADD	 add;
	int id_list[CLACT_U_RES_MAX];
	
	cap = sys_AllocMemory(csp->heap_area, sizeof(TCATS_ACT));
	
	if (cap == NULL){
		return NULL;
	}
	
#if 1

	///< ヘッダーのメモリ確保
	cap->act_htp = sys_AllocMemory(csp->heap_area, sizeof(CLACT_HEADER_TBL));
	
	if (cap->act_htp == NULL){
		return NULL;
	}
	
	cap->act_htp->tbl = sys_AllocMemory(csp->heap_area, sizeof(CLACT_HEADER));
	cap->act_hd = cap->act_htp->tbl;
	
	if (cap->act_htp->tbl == NULL){
		if (cap->act_htp){
			sys_FreeMemoryEz(cap->act_htp);
		}
		return NULL;
	}

#else
	
	cap->act_hd = sys_AllocMemory(csp->heap_area, sizeof(CLACT_HEADER));
	
#endif

	///< リソースIDを書き換える
	for (i = 0; i < CLACT_U_RES_MAX; i++){
		id_list[i] = coap_s->id[i];
	}
	
	if (crp->resManager[4] == NULL
	||	crp->resManager[5] == NULL){
		///< マネージャーが無い場合は、データ指定無し
		id_list[4] = CLACT_U_HEADER_DATA_NONE;
		id_list[5] = CLACT_U_HEADER_DATA_NONE;
	}
	else {	
		///< データ指定されていても、指定IDのリソースが無い場合もデータ無し
		if (id_list[4] != CLACT_U_HEADER_DATA_NONE
		&&  CLACT_U_ResManagerCheckID(crp->resManager[4], id_list[4]) == FALSE){
			id_list[4] = CLACT_U_HEADER_DATA_NONE;
		}

		if (id_list[5] != CLACT_U_HEADER_DATA_NONE
		&&  CLACT_U_ResManagerCheckID(crp->resManager[5], id_list[5]) == FALSE){
			id_list[5] = CLACT_U_HEADER_DATA_NONE;
		}	
	}
	
	///< 実際にヘッダーを作成
	CLACT_U_MakeHeader(cap->act_hd,
					   id_list[0], id_list[1],
					   id_list[2], id_list[3],
					   id_list[4], id_list[5],
					   coap_s->vram_trans,
					   coap_s->bg_pri,
					   crp->resManager[0], crp->resManager[1],
					   crp->resManager[2], crp->resManager[3],
					   crp->resManager[4], crp->resManager[5]);
	
	///< OBJ の登録
	add.ClActSet	= crp->ca_sp;					///< セルアクターセット
	add.ClActHeader = cap->act_hd;					///< ヘッダーから取り出し
	
	add.mat.x		= FX32_CONST(coap_s->x);		///< 座標
	add.mat.y		= FX32_CONST(coap_s->y);
	add.mat.z		= FX32_CONST(coap_s->z);
	if(coap_s->d_area == NNS_G2D_VRAM_TYPE_2DSUB){
		add.mat.y += SUB_SURFACE_Y;
	}
	
	add.sca.x		= FX32_ONE;						///< 拡縮率
	add.sca.y		= FX32_ONE;
	add.sca.z		= FX32_ONE;
	
	add.rot			= 0;							///< 回転角
	add.pri			= coap_s->pri;					///< 優先度
	add.DrawArea	= coap_s->d_area;				///< 描画面
	add.heap		= csp->heap_area;				///< ヒープ領域
	
	cap->act = CLACT_Add(&add);						///< 登録
	
	cap->vram_trans = coap_s->vram_trans;
	
	if (cap->act != NULL){
		def_palno = CLACT_PaletteNoGet(cap->act);				///< 基本パレット番号取得
		CLACT_AnmChg(cap->act, coap_s->anm);					///< アニメーション指定
		CLACT_PaletteNoChg(cap->act, def_palno + coap_s->pal);	///< パレット指定
	}
	else{
		GF_ASSERT(0 && "アクター登録失敗");
	}
	return cap;		
}


//--------------------------------------------------------------
/**
 * @brief   登録済みのパレットのImageProxyを取得
 *
 * @param   crp			
 * @param   pltt_id		
 *
 * @retval  
 */
//--------------------------------------------------------------
const NNSG2dImagePaletteProxy* CATS_PlttProxy( CATS_RES_PTR crp, int pltt_id )
{
	CLACT_U_RES_OBJ_PTR res = CLACT_U_ResManagerGetIDResObjPtr( crp->resManager[1], pltt_id );
	return CLACT_U_PlttManagerGetProxy( res, NULL );
}

//--------------------------------------------------------------
/**
 * @brief   登録済みのパレット管理IDから、転送先のパレット番号を逆引きする
 *
 * @param   crp			
 * @param   pltt_id		パレット管理ID
 * @param   vram_type	VRAM転送タイプ(NNS_G2D_VRAM_TYPE_2DMAIN or NNS_G2D_VRAM_TYPE_2DSUB)
 *
 * @retval  パレット番号
 */
//--------------------------------------------------------------
u32 CATS_PlttID_NoGet(CATS_RES_PTR crp, int pltt_id, NNS_G2D_VRAM_TYPE vram_type)
{
	CLACT_U_RES_OBJ_PTR res = CLACT_U_ResManagerGetIDResObjPtr( crp->resManager[1], pltt_id );
	return CLACT_U_PlttManagerGetPlttNo(res, vram_type );
}


//--------------------------------------------------------------
/**
 * @brief	リソース解放
 *
 * @param	crp	
 * @param	id	
 *
 * @retval	BOOL	
 *
 */
//--------------------------------------------------------------
BOOL CATS_FreeResourceChar(CATS_RES_PTR crp, int id)
{
	return CATS_DeleteResourceCharData_Private(crp->resManager[0], crp->resObjTbl[0], id);		
}


//--------------------------------------------------------------
/**
 * @brief	リソース解放
 *
 * @param	crp	
 * @param	id	
 *
 * @retval	BOOL	
 *
 */
//--------------------------------------------------------------
BOOL CATS_FreeResourcePltt(CATS_RES_PTR crp, int id)
{
	return CATS_DeleteResourcePlttData_Private(crp->resManager[1], crp->resObjTbl[1], id);
}


//--------------------------------------------------------------
/**
 * @brief	リソース解放
 *
 * @param	crp	
 * @param	id	
 *
 * @retval	BOOL	
 *
 */
//--------------------------------------------------------------
BOOL CATS_FreeResourceCell(CATS_RES_PTR crp, int id)
{
	return CATS_DeleteResourceData_Private(crp->resManager[2], crp->resObjTbl[2], id);
}


//--------------------------------------------------------------
/**
 * @brief	リソース解放
 *
 * @param	crp	
 * @param	id	
 *
 * @retval	BOOL	
 *
 */
//--------------------------------------------------------------
BOOL CATS_FreeResourceCellAnm(CATS_RES_PTR crp, int id)
{
	return CATS_DeleteResourceData_Private(crp->resManager[3], crp->resObjTbl[3], id);
}


//--------------------------------------------------------------
/**
 * @brief	リソース解放
 *
 * @param	crp	
 * @param	id	
 *
 * @retval	BOOL	
 *
 */
//--------------------------------------------------------------
BOOL CATS_FreeResourceMCell(CATS_RES_PTR crp, int id)
{
	return CATS_DeleteResourceData_Private(crp->resManager[4], crp->resObjTbl[4], id);
}


//--------------------------------------------------------------
/**
 * @brief	リソース解放
 *
 * @param	crp	
 * @param	id	
 *
 * @retval	BOOL	
 *
 */
//--------------------------------------------------------------
BOOL CATS_FreeResourceMCellAnm(CATS_RES_PTR crp, int id)
{
	return CATS_DeleteResourceData_Private(crp->resManager[5], crp->resObjTbl[5], id);
}


//--------------------------------------------------------------
/**
 * @brief	リソースの破棄
 *
 * @param	csp					システム
 * @param	crp					リソース
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void CATS_ResourceDestructor_S(CATS_SYS_PTR csp, CATS_RES_PTR crp)
{
	int i;
	
	CATS_ClactSetDelete(crp);		///< セルセット破棄

	///< データ破棄
	CLACT_U_CharManagerDeletes(crp->resObjTbl[0]);
	CLACT_U_PlttManagerDeletes(crp->resObjTbl[1]);
	
	for (i = 0; i < crp->resTypeNum; i++){
		
		///< リソースオブジェテーブル破棄
		CLACT_U_ResManagerResObjTblDelete(crp->resObjTbl[i]);
		
		///< リソースマネージャー破棄
		CLACT_U_ResManagerDelete(crp->resManager[i]);
	}

	CATS_ResourceFree(csp, crp);	///< リソースのメモリ破棄
}


//--------------------------------------------------------------
/**
 * @brief	アクターポインタの削除
 *
 * @param	cap	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void CATS_ActorPointerDelete_S(CATS_ACT_PTR cap)
{
	if (cap->vram_trans){
		CLACT_U_CharManagerDeleteVramTransferProxy(cap->act_hd->pImageProxy);
	}
	
	CLACT_Delete(cap->act);
	CLACT_U_CLACT_HeaderTblDelete(cap->act_htp);
	
	sys_FreeMemoryEz(cap);
}






// =============================================================================
//
//
//	■内部参照関数郡
//
//
// =============================================================================
//--------------------------------------------------------------
/**
 * @brief	セルの登録	パス
 *
 * @param	csp	
 * @param	crp	
 * @param	path		パス
 * @param	type		セルの種類
 * @param	id			管理ID
 *
 * @retval	BOOL	
 *
 */
//--------------------------------------------------------------
static BOOL CATS_LoadResourceCell_Private(CATS_SYS_PTR csp, CATS_RES_PTR crp, const char* path, int type, int id)
{
	CLACT_U_RES_OBJ_PTR obj;
	int ret;
	
	obj = CLACT_U_ResManagerResAddKindCell(crp->resManager[type], path, id, type, csp->heap_area);

	if (obj != NULL){		
		ret = CATS_LoadResourceTable_Private(crp->resObjTbl[type], obj);
		
		GF_ASSERT(ret == TRUE && "セル登録失敗");
		
		return ret;
	}
	
	return obj == NULL ? FALSE : TRUE;
}


//--------------------------------------------------------------
/**
 * @brief	セルの登録		アーカイブ
 *
 * @param	csp	
 * @param	crp	
 * @param	arc_id				アーカイブIndex
 * @param	data_id				データIndex
 * @param	comp				圧縮フラグ
 * @param	type				セルの種類
 * @param	id					管理ID
 *
 * @retval	BOOL	
 *
 */
//--------------------------------------------------------------
static BOOL CATS_LoadResourceCellArc_Private(CATS_SYS_PTR csp, CATS_RES_PTR crp, int arc_id, int data_id, int comp, int type, int id)
{
	CLACT_U_RES_OBJ_PTR obj;
	int ret;

	if (CLACT_U_ResManagerCheckID(crp->resManager[type], id) == FALSE){
		return FALSE;
	}
	
	obj = CLACT_U_ResManagerResAddArcKindCell(crp->resManager[type], arc_id, data_id, comp, id, type, csp->heap_area);

	if (obj != NULL){
		ret = CATS_LoadResourceTable_Private(crp->resObjTbl[type], obj);
		
		GF_ASSERT(ret == TRUE && "セル登録失敗");
		
		return ret;
	}
	
	GF_ASSERT(0);
	
	return obj == NULL ? FALSE : TRUE;
}


//--------------------------------------------------------------
/**
 * @brief	リソーステーブルの開いている場所に、リソースオブジェのロード
 *
 * @param	tbl					リソーステーブルのポインタ
 * @param	obj					リソースOBJのポインタ
 *
 * @retval	BOOL				TRUE = 成功
 *
 */
//--------------------------------------------------------------
static BOOL CATS_LoadResourceTable_Private(CLACT_U_RES_OBJ_TBL* tbl, CLACT_U_RES_OBJ_PTR obj)
{
	int i;
	
	for (i = 0; i < tbl->tbl_num; i++){
		
		if (tbl->tbl[i] != NULL){ continue; }
		
		tbl->tbl[i] = obj;
		tbl->tbl_now++;
		
		return TRUE;
	}
	
	return FALSE;
}


//--------------------------------------------------------------
/**
 * @brief	リソーステーブルから、リソースIDを検索して一致したリソースを破棄
 *
 * @param	tbl					リソーステーブルのポインタ
 * @param	id					削除ID
 *
 * @retval	BOOL				TRUE = 成功	
 *
 */
//--------------------------------------------------------------
static BOOL CATS_DeleteResourceData_Private(CLACT_U_RES_MANAGER_PTR resm, CLACT_U_RES_OBJ_TBL* tbl, int id)
{
	int i;
	int hid;
	
	for (i = 0; i < tbl->tbl_num; i++){
		
		if (tbl->tbl[i] == NULL){ continue; }
		
		hid = CLACT_U_ResManagerGetResObjID(tbl->tbl[i]);
		
		if (hid == id){
			CLACT_U_ResManagerResDelete(resm, tbl->tbl[i]);
			tbl->tbl[i] = NULL;
			tbl->tbl_now--;
						
			return TRUE;
		}
	}
	
	return FALSE;
}


//--------------------------------------------------------------
/**
 * @brief	リソーステーブルから、リソースIDを検索して一致したリソースを破棄
 *
 * @param	resm	
 * @param	tbl	
 * @param	id	
 *
 * @retval	static BOOL	
 *
 */
//--------------------------------------------------------------
static BOOL CATS_DeleteResourceCharData_Private(CLACT_U_RES_MANAGER_PTR resm, CLACT_U_RES_OBJ_TBL* tbl, int id)
{
	int i;
	int hid;
	
	for (i = 0; i < tbl->tbl_num; i++){
		
		if (tbl->tbl[i] == NULL){ continue; }
		
		hid = CLACT_U_ResManagerGetResObjID(tbl->tbl[i]);
		
		if (hid == id){
			DelChar(id);
			CLACT_U_ResManagerResDelete(resm, tbl->tbl[i]);
			tbl->tbl[i] = NULL;
			tbl->tbl_now--;
						
			return TRUE;
		}
	}
	
	return FALSE;
}


//--------------------------------------------------------------
/**
 * @brief	リソーステーブルから、リソースIDを検索して一致したリソースを破棄
 *
 * @param	resm	
 * @param	tbl	
 * @param	id	
 *
 * @retval	static BOOL	
 *
 */
//--------------------------------------------------------------
static BOOL CATS_DeleteResourcePlttData_Private(CLACT_U_RES_MANAGER_PTR resm, CLACT_U_RES_OBJ_TBL* tbl, int id)
{

	int i;
	int hid;
	
	for (i = 0; i < tbl->tbl_num; i++){
		
		if (tbl->tbl[i] == NULL){ continue; }
		
		hid = CLACT_U_ResManagerGetResObjID(tbl->tbl[i]);
		
		if (hid == id){
			DelPltt(id);
			CLACT_U_ResManagerResDelete(resm, tbl->tbl[i]);
			tbl->tbl[i] = NULL;
			tbl->tbl_now--;
						
			return TRUE;
		}
	}
	
	return FALSE;
}

















// =============================================================================
//
//
//	■OBJ操作関連まとめ			[ ACTOR_TOOL ]
//
//
// =============================================================================
// =============================================================================
//
//	■表示操作
//
// =============================================================================
//--------------------------------------------------------------
/**
 * @brief	OBJのアニメ更新
 *
 * @param	act					OBJ
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void CATS_ObjectUpdate(CLACT_WORK_PTR act)
{
	CLACT_AnmFrameChg(act, FX32_ONE);
}

//--------------------------------------------------------------
/**
 * @brief	OBJのアニメ更新
 *
 * @param	cap	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void CATS_ObjectUpdateCap(CATS_ACT_PTR cap)
{
	CATS_ObjectUpdate(cap->act);
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	フレームを進める
 *
 *	@param	cap
 *	@param	frame	進める値
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void CATS_ObjectUpdateNumCap(CATS_ACT_PTR cap, fx32 frame)
{
	CLACT_AnmFrameChg(cap->act, frame);
}


//----------------------------------------------------------------------------
/**
 *
 *	@brief	アニメーションシーケンス設定　アニメの切り替え
 *
 *	@param	cap
 *	@param	seq		シーケンス
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void CATS_ObjectAnimeSeqSetCap( CATS_ACT_PTR cap, u32 seq )
{
	CLACT_AnmChg( cap->act, seq );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	アニメーションシーケンス取得
 *
 *	@param	cap 
 *
 *	@return	シーケンス
 *
 *
 */
//-----------------------------------------------------------------------------
u32 CATS_ObjectAnimeSeqGetCap( CATS_ACT_PTR cap )
{
	return CLACT_AnmGet( cap->act );
}


//--------------------------------------------------------------
/**
 * @brief	オートアニメ設定
 *
 * @param	act	
 * @param	flag				CATS_ANM_AUTO_ON / CATS_ANM_AUTO_OFF
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void CATS_ObjectAutoAnimeSet(CLACT_WORK_PTR act, int flag)
{
	CLACT_SetAnmFlag(act, flag);
}

//--------------------------------------------------------------
/**
 * @brief	オートアニメ設定
 *
 * @param	cap	
 * @param	flag	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void CATS_ObjectAutoAnimeSetCap(CATS_ACT_PTR cap, int flag)
{
	CATS_ObjectAutoAnimeSet(cap->act, flag);
}


//--------------------------------------------------------------
/**
 * @brief	オートアニメ取得
 *
 * @param	act	
 *
 * @retval	int	
 *
 */
//--------------------------------------------------------------
int CATS_ObjectAutoAnimeGet(CLACT_WORK_PTR act)
{
	return CLACT_GetAnmFlag(act);
}


//--------------------------------------------------------------
/**
 * @brief	オートアニメ取得
 *
 * @param	cap	
 *
 * @retval	int	
 *
 */
//--------------------------------------------------------------
int CATS_ObjectAutoAnimeGetCap(CATS_ACT_PTR cap)
{
	return CATS_ObjectAutoAnimeGet(cap->act);
}


//----------------------------------------------------------------------------
/**
 *
 *	@brief	オートアニメスピード設定
 *
 *	@param	act			
 *	@param	speed	アニメスピード
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void CATS_ObjectAutoAnimeSpeedSet(CLACT_WORK_PTR act, fx32 speed)
{
	CLACT_SetAnmFrame( act, speed );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	オートアニメスピード設定
 *
 *	@param	cap
 *	@param	speed	アニメスピード
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void CATS_ObjectAutoAnimeSpeedSetCap(CATS_ACT_PTR cap, fx32 speed)
{
	CATS_ObjectAutoAnimeSpeedSet( cap->act, speed );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	オートアニメスピード取得
 *
 *	@param	act	
 *
 *	@return	アニメスピード
 *
 *
 */
//-----------------------------------------------------------------------------
fx32 CATS_ObjectAutoAnimeSpeedGet(CLACT_WORK_PTR act)
{
	return CLACT_GetAnmFrame( act );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	オートアニメスピード取得
 *
 *	@param	cap
 *
 *	@return	アニメスピード
 *
 *
 */
//-----------------------------------------------------------------------------
fx32 CATS_ObjectAutoAnimeSpeedGetCap(CATS_ACT_PTR cap)
{
	return CATS_ObjectAutoAnimeSpeedGet( cap->act );
}


//--------------------------------------------------------------
/**
 * @brief	アニメ動作チェック
 *
 * @param	act	
 *
 * @retval	TRUE	アニメーション中
 * @retval	FALSE	停止中
 *
 */
//--------------------------------------------------------------
BOOL CATS_ObjectAnimeActiveCheck(CLACT_WORK_PTR act)
{
	return CLACT_AnmActiveCheck(act);
}

//--------------------------------------------------------------
/**
 * @brief	オートアニメ取得
 *
 * @param	cap	
 *
 * @retval	TRUE	アニメーション中
 * @retval	FALSE	停止中
 *
 */
//--------------------------------------------------------------
BOOL CATS_ObjectAnimeActiveCheckCap(CATS_ACT_PTR cap)
{
	return CATS_ObjectAnimeActiveCheck(cap->act);
}


//----------------------------------------------------------------------------
/**
 *
 *	@brief	アニメーションフレーム設定
 *
 *	@param	act		アクター
 *	@param	frame	設定フレーム
 *
 *	@retval	none
 *
 *
 */
//-----------------------------------------------------------------------------
void CATS_ObjectAnimeFrameSet(CLACT_WORK_PTR act, u16 frame)
{
	CLACT_AnmFrameSet( act, frame );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	アニメーションフレーム設定　コマを進める
 *
 *	@param	cap
 *	@param	frame	設定フレーム
 *
 *	@retval	none	
 *
 *
 */
//-----------------------------------------------------------------------------
void CATS_ObjectAnimeFrameSetCap(CATS_ACT_PTR cap, u16 frame)
{
	CATS_ObjectAnimeFrameSet( cap->act, frame );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	アニメーションフレームを取得
 *
 *	@param	act	アクター
 *
 *	@return	フレーム
 *
 *
 */
//-----------------------------------------------------------------------------
u16 CATS_ObjectAnimeFrameGet(CLACT_WORK_PTR act)
{
	return CLACT_AnmFrameGet( act );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	アニメーションフレームを取得
 *
 *	@param	cap	アクター
 *
 *	@return	フレーム
 *
 *
 */
//-----------------------------------------------------------------------------
u16 CATS_ObjectAnimeFrameGetCap(CATS_ACT_PTR cap)
{
	return CATS_ObjectAnimeFrameGet( cap->act );
}


//--------------------------------------------------------------
/**
 * @brief	OBJの表示設定
 *
 * @param	act					OBJ
 * @param	enable				CATS_ENABLE_TRUE	= 表示
 *								CATS_ENABLE_FALSE	= 非表示
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void CATS_ObjectEnable(CLACT_WORK_PTR act, int enable)
{
	CLACT_SetDrawFlag(act, enable);
}

//--------------------------------------------------------------
/**
 * @brief	OBJの表示設定
 *
 * @param	cap	
 * @param	enable	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void CATS_ObjectEnableCap(CATS_ACT_PTR cap, int enable)
{
	CATS_ObjectEnable(cap->act, enable);
}


//--------------------------------------------------------------
/**
 * @brief	OBJの表示設定取得
 *
 * @param	act	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
int	CATS_ObjectEnableGet(CLACT_WORK_PTR act)
{
	return CLACT_GetDrawFlag(act);
}


//--------------------------------------------------------------
/**
 * @brief	OBJの表示設定取得
 *
 * @param	cap	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
int	CATS_ObjectEnableGetCap(CATS_ACT_PTR cap)
{
	return CATS_ObjectEnableGet(cap->act);
}


//--------------------------------------------------------------
/**
 * @brief	パレット変更
 *
 * @param	act	
 * @param	pal	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void CATS_ObjectPaletteSet(CLACT_WORK_PTR act, int pal)
{
	CLACT_PaletteNoChg(act, pal);
}

//--------------------------------------------------------------
/**
 * @brief	パレット変更
 *
 * @param	cap	
 * @param	pal	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void CATS_ObjectPaletteSetCap(CATS_ACT_PTR cap, int pal)
{
	CATS_ObjectPaletteSet(cap->act, pal);	
}

//--------------------------------------------------------------
/**
 * @brief   パレットオフセット変更
 *
 * @param   act			
 * @param   pal_ofs		
 */
//--------------------------------------------------------------
void CATS_ObjectPaletteOffsetSet(CLACT_WORK_PTR act, int pal_ofs)
{
	CLACT_PaletteOffsetChg(act, pal_ofs);
}

//--------------------------------------------------------------
/**
 * @brief   パレットオフセット変更
 *
 * @param   cap		
 * @param   pal_ofs		
 *
 * @retval  
 *
 *
 */
//--------------------------------------------------------------
void CATS_ObjectPaletteOffsetSetCap(CATS_ACT_PTR cap, int pal_ofs)
{
	CATS_ObjectPaletteOffsetSet(cap->act, pal_ofs);	
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	パレットオフセットの取得
 *
 *	@param	cap		ワーク
 *
 *	@return	パレットオフセット
 *
 *
 */
//-----------------------------------------------------------------------------
int CATS_ObjectPaletteOffsetGetCap(CATS_ACT_PTR cap)
{
	return CLACT_PaletteOffsetGet(cap->act);
}


//--------------------------------------------------------------
/**
 * @brief	BGとの優先度の変更
 *
 * @param	act	
 * @param	pri	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void CATS_ObjectBGPriSet(CLACT_WORK_PTR act, int pri)
{
	CLACT_BGPriorityChg(act, pri);
}


//--------------------------------------------------------------
/**
 * @brief	BG との優先度
 *
 * @param	cap	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
int	CATS_ObjectBGPriGetCap(CATS_ACT_PTR cap)
{
	return CLACT_BGPriorityGet(cap->act);
}


//--------------------------------------------------------------
/**
 * @brief	BGとの優先度の変更
 *
 * @param	cap	
 * @param	pri	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void CATS_ObjectBGPriSetCap(CATS_ACT_PTR cap, int pri)
{
	CATS_ObjectBGPriSet(cap->act, pri);
}


//--------------------------------------------------------------
/**
 * @brief	優先度の変更
 *
 * @param	act	
 * @param	pri	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void CATS_ObjectPriSet(CLACT_WORK_PTR act, int pri)
{
	CLACT_DrawPriorityChg(act, pri);
}

//--------------------------------------------------------------
/**
 * @brief	優先度の変更
 *
 * @param	cap	
 * @param	pri	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void CATS_ObjectPriSetCap(CATS_ACT_PTR cap, int pri)
{
	CATS_ObjectPriSet(cap->act, pri);
}

//--------------------------------------------------------------
/**
 * @brief	優先度取得
 *
 * @param	act	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
u32 CATS_ObjectPriGet(CLACT_WORK_PTR act)
{
	return CLACT_DrawPriorityGet(act);
}

//--------------------------------------------------------------
/**
 * @brief	優先度取得
 *
 * @param	cap	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
u32 CATS_ObjectPriGetCap(CATS_ACT_PTR cap)
{
	return CATS_ObjectPriGet(cap->act);
}


// =============================================================================
//
//	■座標操作
//
// =============================================================================
//--------------------------------------------------------------
/**
 * @brief	OBJの座標変更
 *
 * @param	act					OBJ
 * @param	x	
 * @param	y	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void CATS_ObjectPosSet(CLACT_WORK_PTR act, s16 x, s16 y)
{
	VecFx32 vec;
		
	vec.x = x * FX32_ONE;
	vec.y = y * FX32_ONE;
	if(CLACT_VramTypeGet(act) == NNS_G2D_VRAM_TYPE_2DSUB){
		vec.y += SUB_SURFACE_Y;
	}
	vec.z = 0;
	
	CLACT_SetMatrix(act, &vec);	
}

//--------------------------------------------------------------
/**
 * @brief	OBJの座標変更
 *
 * @param	cap	
 * @param	x	
 * @param	y	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void CATS_ObjectPosSetCap(CATS_ACT_PTR cap, s16 x, s16 y)
{
	CATS_ObjectPosSet(cap->act, x, y);
}

//--------------------------------------------------------------
/**
 * @brief	OBJの座標変更(SUB_SURFACE_Yに足しこむ値を外側から指定)
 *
 * @param	act					OBJ
 * @param	x	
 * @param	y	
 * @param   sub_surface_y		サブ画面に出るOBJの場合、足しこむSURFACE値
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void CATS_ObjectPosSet_SubSurface(CLACT_WORK_PTR act, s16 x, s16 y, fx32 sub_surface_y)
{
	VecFx32 vec;
		
	vec.x = x * FX32_ONE;
	vec.y = y * FX32_ONE;
	if(CLACT_VramTypeGet(act) == NNS_G2D_VRAM_TYPE_2DSUB){
		vec.y += sub_surface_y;
	}
	vec.z = 0;
	
	CLACT_SetMatrix(act, &vec);	
}

//--------------------------------------------------------------
/**
 * @brief	OBJの座標変更(SUB_SURFACE_Yに足しこむ値を外側から指定)
 *
 * @param	cap	
 * @param	x	
 * @param	y	
 * @param   sub_surface_y		サブ画面に出るOBJの場合、足しこむSURFACE値
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void CATS_ObjectPosSetCap_SubSurface(CATS_ACT_PTR cap, s16 x, s16 y, fx32 sub_surface_y)
{
	CATS_ObjectPosSet_SubSurface(cap->act, x, y, sub_surface_y);
}

//--------------------------------------------------------------
/**
 * @brief	OBJの座標取得
 *
 * @param	act					OBJ
 * @param	x					取得X座標代入先
 * @param	y					取得Y座標代入先
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void CATS_ObjectPosGet(CLACT_WORK_PTR act, s16 *x, s16 *y)
{
	const VecFx32 *p_vec;
	
	p_vec = CLACT_GetMatrix(act);
	*x = p_vec->x / FX32_ONE;
	if(CLACT_VramTypeGet(act) == NNS_G2D_VRAM_TYPE_2DSUB){
		*y = (p_vec->y - SUB_SURFACE_Y) / FX32_ONE;
	}
	else {
		*y = p_vec->y / FX32_ONE;
	}
}

//--------------------------------------------------------------
/**
 * @brief	OBJの座標取得
 *
 * @param	cap	
 * @param	x	
 * @param	y	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void CATS_ObjectPosGetCap(CATS_ACT_PTR cap, s16 *x, s16 *y)
{
	CATS_ObjectPosGet(cap->act, x, y);
}

//--------------------------------------------------------------
/**
 * @brief	OBJの座標取得(SUB_SURFACE_Yを外側から指定)
 *
 * @param	act					OBJ
 * @param	x					取得X座標代入先
 * @param	y					取得Y座標代入先
 * @param   sub_surface_y		サブ画面に出るOBJの場合、足しこむSURFACE値
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void CATS_ObjectPosGet_SubSurface(CLACT_WORK_PTR act, s16 *x, s16 *y, fx32 sub_surface_y)
{
	const VecFx32 *p_vec;
	
	p_vec = CLACT_GetMatrix(act);
	*x = p_vec->x / FX32_ONE;
	if(CLACT_VramTypeGet(act) == NNS_G2D_VRAM_TYPE_2DSUB){
		*y = (p_vec->y - sub_surface_y) / FX32_ONE;
	}
	else {
		*y = p_vec->y / FX32_ONE;
	}
}

//--------------------------------------------------------------
/**
 * @brief	OBJの座標取得(SUB_SURFACE_Yを外側から指定)
 *
 * @param	cap	
 * @param	x	
 * @param	y	
 * @param   sub_surface_y		サブ画面に出るOBJの場合、足しこむSURFACE値
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void CATS_ObjectPosGetCap_SubSurface(CATS_ACT_PTR cap, s16 *x, s16 *y, fx32 sub_surface_y)
{
	CATS_ObjectPosGet_SubSurface(cap->act, x, y, sub_surface_y);
}


//--------------------------------------------------------------
/**
 * @brief	OBJの移動
 *
 * @param	act					OBJ
 * @param	x	
 * @param	y	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void CATS_ObjectPosMove(CLACT_WORK_PTR act, s16 x, s16 y)
{
	const VecFx32* p_vec;
	VecFx32 p_vec2;
	
	p_vec = CLACT_GetMatrix(act);
	
	p_vec2.x = p_vec->x + (x * FX32_ONE);
	p_vec2.y = p_vec->y + (y * FX32_ONE);
	p_vec2.z = p_vec->z;
	
	CLACT_SetMatrix(act, &p_vec2);
}

//--------------------------------------------------------------
/**
 * @brief	OBJの移動
 *
 * @param	cap	
 * @param	x	
 * @param	y	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void CATS_ObjectPosMoveCap(CATS_ACT_PTR cap, s16 x, s16 y)
{
	CATS_ObjectPosMove(cap->act, x, y);
}


// =============================================================================
//
//	■アフィン操作 フリップ操作
//
// =============================================================================
//--------------------------------------------------------------
/**
 * @brief	OBJのアフィンパラメーター設定
 *
 * @param	act					OBJ
 * @param	affine				アフィンパラメーター
 *		CLACT_AFFINE_NONE,		// アフィン変換なし
 *		CLACT_AFFINE_NORMAL,	// アフィン変換
 *		CLACT_AFFINE_DOUBLE,	// 倍角アフィン変換
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void CATS_ObjectAffineSet(CLACT_WORK_PTR act, int affine)
{
	CLACT_SetAffineParam(act, affine);
}

//--------------------------------------------------------------
/**
 * @brief	OBJのアフィンパラメーター設定
 *
 * @param	cap	
 * @param	affine	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void CATS_ObjectAffineSetCap(CATS_ACT_PTR cap, int affine)
{
	CATS_ObjectAffineSet(cap->act, affine);
}


//--------------------------------------------------------------
/**
 * @brief	OBJのアフィンパラメーター取得
 *
 * @param	act					OBJ
 *
 * @retval	int
 *
 */
//--------------------------------------------------------------
int CATS_ObjectAffineGet(CLACT_WORK_PTR act)
{
	return CLACT_GetAffineParam(act);
}

//--------------------------------------------------------------
/**
 * @brief	OBJのアフィンパラメーター取得
 *
 * @param	cap	
 *
 * @retval	int	
 *
 */
//--------------------------------------------------------------
int CATS_ObjectAffineGetCap(CATS_ACT_PTR cap)
{
	return CATS_ObjectAffineGet(cap->act);
}


//--------------------------------------------------------------
/**
 * @brief	OBJの拡縮率の変更
 *
 * @param	act					OBJ
 * @param	sx	
 * @param	sy	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void CATS_ObjectScaleSet(CLACT_WORK_PTR act, f32 sx, f32 sy)
{
	const VecFx32* p_vec;
	VecFx32* p_vec2;
	
	p_vec = CLACT_GetScale(act);
	
	p_vec2 = (VecFx32*)p_vec;
	
	p_vec2->x = (sx * FX32_ONE);
	p_vec2->y = (sy * FX32_ONE);
	
	CLACT_SetScale(act, p_vec2);
}

//--------------------------------------------------------------
/**
 * @brief	OBJの拡縮率の変更
 *
 * @param	cap	
 * @param	sx	
 * @param	sy	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void CATS_ObjectScaleSetCap(CATS_ACT_PTR cap, f32 sx, f32 sy)
{
	CATS_ObjectScaleSet(cap->act, sx, sy);
}


//--------------------------------------------------------------
/**
 * @brief	OBJの拡縮率の加算
 *
 * @param	act					OBJ
 * @param	sx	
 * @param	sy	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void CATS_ObjectScaleAdd(CLACT_WORK_PTR act, f32 sx, f32 sy)
{
	const VecFx32* p_vec;
	VecFx32* p_vec2;
	
	p_vec = CLACT_GetScale(act);
	
	p_vec2 = (VecFx32*)p_vec;
	
	p_vec2->x = p_vec->x + (sx * FX32_ONE);
	p_vec2->y = p_vec->y + (sy * FX32_ONE);
	
	CLACT_SetScale(act, p_vec2);
}

//--------------------------------------------------------------
/**
 * @brief	OBJの拡縮率の加算
 *
 * @param	cap	
 * @param	sx	
 * @param	sy	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void CATS_ObjectScaleAddCap(CATS_ACT_PTR cap, f32 sx, f32 sy)
{
	CATS_ObjectScaleAdd(cap->act, sx, sy);
}


//--------------------------------------------------------------
/**
 * @brief	OBJの拡縮率を取得
 *
 * @param	act	
 * @param	sx	
 * @param	sy	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void CATS_ObjectScaleGet(CLACT_WORK_PTR act, f32* sx, f32* sy)
{
	const VecFx32* p_vec;
	VecFx32* p_vec2;
	
	p_vec = CLACT_GetScale(act);
	
	*sx = p_vec->x / FX32_ONE;
	*sy = p_vec->y / FX32_ONE;
}

//--------------------------------------------------------------
/**
 * @brief	OBJの拡縮率を取得
 *
 * @param	cap	
 * @param	sx	
 * @param	sy	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void CATS_ObjectScaleGetCap(CATS_ACT_PTR cap, f32* sx, f32* sy)
{
	CATS_ObjectScaleGet(cap->act, sx, sy);
}


//--------------------------------------------------------------
/**
 * @brief	OBJの回転各設定
 *
 * @param	act	
 * @param	rot	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void CATS_ObjectRotationSet(CLACT_WORK_PTR act, u16 rot)
{
	CLACT_SetRotation(act, rot);
}

//--------------------------------------------------------------
/**
 * @brief	OBJの回転各設定
 *
 * @param	cap	
 * @param	rot	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void CATS_ObjectRotationSetCap(CATS_ACT_PTR cap, u16 rot)
{
	CATS_ObjectRotationSet(cap->act, rot);
}


//--------------------------------------------------------------
/**
 * @brief	OBJの回転率加減算
 *
 * @param	act					OBJ
 * @param	rot	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void CATS_ObjectRotationAdd(CLACT_WORK_PTR act, s32 rot)
{
	u16 nrot;
	
	nrot = CLACT_GetRotation(act);
	
	nrot += rot;
	
	CLACT_SetRotation(act, nrot);
}

//--------------------------------------------------------------
/**
 * @brief	OBJの回転率加減算
 *
 * @param	cap	
 * @param	rot	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void CATS_ObjectRotationAddCap(CATS_ACT_PTR cap, s32 rot)
{
	CATS_ObjectRotationAdd(cap->act, rot);
}


//--------------------------------------------------------------
/**
 * @brief	回転率取得
 *
 * @param	act					OBJ
 *
 * @retval	u16
 *
 */
//--------------------------------------------------------------
u16	CATS_ObjectRotationGet(CLACT_WORK_PTR act)
{
	return CLACT_GetRotation(act);
}

//--------------------------------------------------------------
/**
 * @brief	回転率取得
 *
 * @param	cap	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
u16	CATS_ObjectRotationGetCap(CATS_ACT_PTR cap)
{
	return CATS_ObjectRotationGet(cap->act);
}


//--------------------------------------------------------------
/**
 * @brief	フリップ操作
 *
 * @param	act					OBJ
 * @param	flip				フリップ操作
 * 		CLACT_FLIP_NONE,		// フリップなし
 * 		CLACT_FLIP_H,			// フリップ水平方向
 *		CLACT_FLIP_V,			// フリップ垂直方向
 *		CLACT_FLIP_HV,			// 両方向フリップ
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void CATS_ObjectFlipSet(CLACT_WORK_PTR act, int flip)
{
	CLACT_SetFlip(act, flip);
}

//--------------------------------------------------------------
/**
 * @brief	フリップ操作
 *
 * @param	cap	
 * @param	flip	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void CATS_ObjectFlipSetCap(CATS_ACT_PTR cap, int flip)
{
	CATS_ObjectFlipSet(cap->act, flip);
}


//--------------------------------------------------------------
/**
 * @brief	フリップ取得
 *
 * @param	act					OBJ
 *
 * @retval	int					フリップ状態
 *
 */
//--------------------------------------------------------------
int CATS_ObjectFlipGet(CLACT_WORK_PTR act)
{
	return CLACT_GetFlip(act);
}

//--------------------------------------------------------------
/**
 * @brief	フリップ取得
 *
 * @param	cap	
 *
 * @retval	int	
 *
 */
//--------------------------------------------------------------
int CATS_ObjectFlipGetCap(CATS_ACT_PTR cap)
{
	return CATS_ObjectFlipGet(cap->act);
}


//----------------------------------------------------------------------------
/**
 *
 *	@brief	アフィン座標を設定
 *
 *	@param	cap		アクター
 *	@param	x		X座標
 *	@param	y		Y座標
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void CATS_ObjectAffinePosSetCap(CATS_ACT_PTR cap, s16 x, s16 y)
{
	VecFx32	matrix;

	matrix.x = x << FX32_SHIFT;
	matrix.y = y << FX32_SHIFT;
	matrix.z = 0;

	CLACT_SetAffineMatrix( cap->act, &matrix );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	アフィン変換座標を取得
 *
 *	@param	cap		アクター
 *	@param	x		x座標格納先
 *	@param	y		y座標格納先
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void CATS_ObjectAffinePosGetCap(CATS_ACT_PTR cap, s16 *x, s16 *y)
{
	const VecFx32* cp_matrix;

	cp_matrix = CLACT_GetAffineMatrix( cap->act );
	*x = cp_matrix->x >> FX32_SHIFT;
	*y = cp_matrix->y >> FX32_SHIFT;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	アフィン変換座標を動かす
 *
 *	@param	cap		アクター
 *	@param	x		動かすx値
 *	@param	y		動かすy値
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void CATS_ObjectAffinePosMoveCap(CATS_ACT_PTR cap, s16 x, s16 y)
{
	const VecFx32* cp_matrix;
	VecFx32 matrix;
	
	cp_matrix = CLACT_GetAffineMatrix( cap->act );
	matrix = *cp_matrix;

	matrix.x += x << FX32_SHIFT;
	matrix.y += y << FX32_SHIFT;

	CLACT_SetAffineMatrix( cap->act, &matrix );
}


//--------------------------------------------------------------
/**
 * @brief	モザイク設定
 *
 * @param	cap	
 * @param	flag	TRUE = ON
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void CATS_ObjectMosaicSet(CATS_ACT_PTR cap, BOOL flag)
{
	CLACT_MosaicSet(cap->act, flag);
}

//--------------------------------------------------------------
/**
 * @brief	OBJモード設定
 *
 * @param	act		OBJ
 * @param	objmode	OBJモード
 *
 * @return	none
 *
 * objmode
 *	GX_OAM_MODE_NORMAL		ノーマルOBJ 
 * 	GX_OAM_MODE_XLU			半透明OBJ 
 *	GX_OAM_MODE_OBJWND		OBJウィンドウ 
 *	GX_OAM_MODE_BITMAPOBJ	ビットマップOBJ 
 *
 */
//--------------------------------------------------------------
void CATS_ObjectObjModeSet(CLACT_WORK_PTR act, GXOamMode objmode)
{
	CLACT_ObjModeSet( act, objmode );
}

//--------------------------------------------------------------
/**
 * @brief	OBJモード設定
 *
 * @param	cap		
 * @param	objmode	OBJモード
 *
 * @return	none
 *
 * objmode
 *	GX_OAM_MODE_NORMAL		ノーマルOBJ 
 * 	GX_OAM_MODE_XLU			半透明OBJ 
 *	GX_OAM_MODE_OBJWND		OBJウィンドウ 
 *	GX_OAM_MODE_BITMAPOBJ	ビットマップOBJ 
 *
 */
//--------------------------------------------------------------
void CATS_ObjectObjModeSetCap(CATS_ACT_PTR cap, GXOamMode objmode)
{
	CATS_ObjectObjModeSet( cap->act, objmode );
}

//--------------------------------------------------------------
/**
 * @brief	OBJモード取得
 *
 * @param	act					OBJ
 *
 *	@retval	GX_OAM_MODE_NORMAL		ノーマルOBJ 
 *	@retval	GX_OAM_MODE_XLU			半透明OBJ 
 *	@retval	GX_OAM_MODE_OBJWND		OBJウィンドウ 
 *	@retval	GX_OAM_MODE_BITMAPOBJ	ビットマップOBJ 
 *
 *	OBJモードがGX_OAM_MODE_NORMALの時はNitroCharacterで設定した
 *	OBJモードで描画されます。
 *
 */
//--------------------------------------------------------------
GXOamMode CATS_ObjectObjModeGet(CLACT_WORK_PTR act)
{
	return CLACT_ObjModeGet( act );
}

//--------------------------------------------------------------
/**
 * @brief	OBJモード取得
 *
 * @param	cap
 *
 *	@retval	GX_OAM_MODE_NORMAL		ノーマルOBJ 
 *	@retval	GX_OAM_MODE_XLU			半透明OBJ 
 *	@retval	GX_OAM_MODE_OBJWND		OBJウィンドウ 
 *	@retval	GX_OAM_MODE_BITMAPOBJ	ビットマップOBJ 
 *
 *	OBJモードがGX_OAM_MODE_NORMALの時はNitroCharacterで設定した
 *	OBJモードで描画されます。
 *
 */
//--------------------------------------------------------------
GXOamMode CATS_ObjectObjModeGetCap(CATS_ACT_PTR cap)
{
	return CATS_ObjectObjModeGet( cap->act );
}




//--------------------------------------------------------------
/**
 * @brief	キャラの登録	アーカイブ
 *
 * @param	csp	
 * @param	crp	
 * @param	arc_id				アーカイブIndex
 * @param	data_id				データIndex
 * @param	comp				圧縮フラグ
 * @param	id					管理ID
 *
 * @retval	BOOL	
 *
 *	マッピングモードを今の状態に変更する
 */
//--------------------------------------------------------------
BOOL CATS_LoadResourceCharArcModeAdjust(
		CATS_SYS_PTR csp, CATS_RES_PTR crp, int arc_id, int data_id, BOOL comp, int trans_mode, int id)
{
	CLACT_U_RES_OBJ_PTR obj;

	if (CLACT_U_ResManagerCheckID(crp->resManager[0], id) == FALSE){
		return FALSE;
	}
	
	obj = CLACT_U_ResManagerResAddArcChar(crp->resManager[0], arc_id, data_id, comp, id, trans_mode, csp->heap_area);

	if (obj != NULL){
//		CLACT_U_CharManagerSetAreaCont(obj);
//		CLACT_U_CharManagerSetCharModeAdjustAreaCont( obj );
		CLACT_U_CharManagerSetCharModeAdjust( obj );
//		CLACT_U_CharManagerSetCharModeAdjustAreaCont( obj );
		
		CATS_LoadResourceTable_Private(crp->resObjTbl[0], obj);	
		
		return TRUE;
	}
	
	GF_ASSERT(0);
	
	return obj == NULL ? FALSE : TRUE;
}

BOOL CATS_LoadResourceCharArcModeAdjustAreaCont(
		CATS_SYS_PTR csp, CATS_RES_PTR crp, int arc_id, int data_id, BOOL comp, int trans_mode, int id)
{
	CLACT_U_RES_OBJ_PTR obj;

	if (CLACT_U_ResManagerCheckID(crp->resManager[0], id) == FALSE){
		return FALSE;
	}
	
	obj = CLACT_U_ResManagerResAddArcChar(crp->resManager[0], arc_id, data_id, comp, id, trans_mode, csp->heap_area);

	if (obj != NULL){
//		CLACT_U_CharManagerSetAreaCont(obj);
//		CLACT_U_CharManagerSetCharModeAdjustAreaCont( obj );
		CLACT_U_CharManagerSetCharModeAdjustAreaCont( obj );
		
		CATS_LoadResourceTable_Private(crp->resObjTbl[0], obj);	
		
		return TRUE;
	}
	
	GF_ASSERT(0);
	
	return obj == NULL ? FALSE : TRUE;
}

//--------------------------------------------------------------
/**
 * @brief	キャラのリーソースを変更する	アーカイブ
 *
 * @param	csp	
 * @param	crp	
 * @param	arc_id				アーカイブIndex
 * @param	data_id				データIndex
 * @param	comp				圧縮フラグ
 * @param	id					管理ID
 *
 * @retval	BOOL	
 */
//--------------------------------------------------------------
void CATS_ChangeResourceCharArc(
		CATS_SYS_PTR csp, CATS_RES_PTR crp, int arc_id, int data_id, BOOL comp, int id )
{
	CLACT_U_RES_OBJ_PTR	obj;
	
	obj = CLACT_U_ResManagerGetIDResObjPtr( crp->resManager[0], id );

	CLACT_U_ResManagerResChgArcChar(
		crp->resManager[0], obj, arc_id, data_id, comp, csp->heap_area );

	CLACT_U_CharManagerReTrans( obj );
}


//--------------------------------------------------------------
/**
 * @brief	パレットのリーソースを変更する	アーカイブ
 *
 * @param	csp	
 * @param	crp	
 * @param	arc_id				アーカイブIndex
 * @param	data_id				データIndex
 * @param	comp				圧縮フラグ
 * @param	id					管理ID
 *
 * @retval	BOOL	
 */
//--------------------------------------------------------------
void CATS_ChangeResourcePlttArc(
		CATS_SYS_PTR csp, CATS_RES_PTR crp, int arc_id, int data_id, BOOL comp, int id )
{
	CLACT_U_RES_OBJ_PTR	obj;
	
	obj = CLACT_U_ResManagerGetIDResObjPtr( crp->resManager[1], id );

	CLACT_U_ResManagerResChgArcPltt(
		crp->resManager[1], obj, arc_id, data_id, comp, csp->heap_area );

	CLACT_U_PlttManagerReTrans( obj );
}

//--------------------------------------------------------------
/**
 * @brief	CLACT_SET_PTRを取得する
 *
 * @param	crp					リソースポインタ
 *
 * @retval	CLACT_SET_PTR
 */
//--------------------------------------------------------------
CLACT_SET_PTR CATS_GetClactSetPtr(CATS_RES_PTR crp)
{
	return crp->ca_sp;
}


#if 0
// =============================================================================
//
//
//	■画像変換
//
//
// =============================================================================
#include "system/arc_tool.h"

static void CharCopy1(const u8* src, u8* dst, int* ofs, int* bofs, int cs, int len);

//--------------------------------------------------------------
/**
 * @brief	2D→1Dに1キャラ変換
 *
 * @param	src			元データ
 * @param	dst			展開先
 * @param	ofs			元データのコピー開始位置
 * @param	bofs		展開先バッファの書き込み位置
 * @param	cs			コピーサイズ
 * @param	len			2Dデータの幅
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void CharCopy1(const u8* src, u8* dst, int* ofs, int* bofs, int cs, int len)
{
	int i;
	u32 dat;
	
	for (i = 0; i < 8; i++){
		memcpy(&dst[ *bofs ], &src[ *ofs ], cs);
		*ofs  += len;
		*bofs += cs;
	}
}


//--------------------------------------------------------------
/**
 * @brief	2D→1Dに変換する
 *
 * @param	arc_id				アーカイブインデックス
 * @param	index_no			ファイルインデックス
 * @param	heap_id				ヒープID
 * @param	x					変換対象矩形:x
 * @param	y					変換対象矩形:y
 * @param	w					変換対象矩形:w
 * @param	h					変換対象矩形:h
 * @param	buff				展開先バッファ
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void ChangesInto_1D_from_2D(int arc_id, int index_no, int heap_id, int x, int y, int w, int h, void* buff)
{
	void* aw = NULL;
	u8* p_data = NULL;
	u8* p_buff = NULL;
	NNSG2dCharacterData* ch_data = NULL;

	int size;
	int cs;
	int ofs;
	int bofs;
	int len;
	BOOL res;
	
	///< データの展開
	aw = ArchiveDataLoadMalloc(arc_id, index_no, heap_id);
	
	GF_ASSERT(aw != NULL);
	
	///< キャラデータの取得
	res = NNS_G2dGetUnpackedCharacterData(aw, &ch_data);
	
	GF_ASSERT(res != FALSE);

	GF_ASSERT(ch_data->W >= (x + w));		///< サイズチェック
	GF_ASSERT(ch_data->H >= (y + h));
	
	///< 準備
	cs     = (sizeof(u8) * 4);				///< コピーサイズ 8dot = 4Byte
	p_data = ch_data->pRawData;				///< キャラデータ
	p_buff = (u8*)buff;						///< 展開バッファ
	
	len = (ch_data->W * cs);				///< 長さ(元画像の幅)
	ofs = (x * cs) + (y * len);				///< 開始位置
	bofs = 0;								///< バッファの書き込み位置
	
	//全体ｺﾋﾟｰ
	{
		int i;
		int j;

		for (j = y; j < (y + h); j++){
			for (i = x; i < (x + w); i++){
				ofs = (i * cs) + (j * len * CHAR_DOT_Y);			///< 開始位置
				CharCopy1(p_data, p_buff, &ofs, &bofs, cs, len);	///< 1キャラコピー
			}
		}
	}
	
	sys_FreeMemoryEz(aw);
}


//--------------------------------------------------------------
/**
 * @brief	2D→1Dに変換する
 *
 * @param	arc_id				アーカイブインデックス
 * @param	index_no			ファイルインデックス
 * @param	heap_id				ヒープID
 * @param	rc					矩形
 * @param	buff				バッファ
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void  ChangesInto_1D_from_2D_RC(int arc_id, int index_no, int heap_id, CHANGES_INTO_DATA_RECT* rc, void* buff)
{
	ChangesInto_1D_from_2D(arc_id, index_no, heap_id, rc->x, rc->y, rc->h, rc->w, buff);
}


//--------------------------------------------------------------
/**
 * @brief	2D→1Dに展開バッファをAllocして変換する
 *
 * @param	arc_id				アーカイブインデックス
 * @param	index_no			ファイルインデックス
 * @param	heap_id				ヒープID
 * @param	x					変換対象矩形:x
 * @param	y					変換対象矩形:y
 * @param	w					変換対象矩形:w
 * @param	h					変換対象矩形:h
 *
 * @retval	void*				展開したバッファのポインタ
 *
 */
//--------------------------------------------------------------
void* ChangesInto_1D_from_2D_Alloc(int arc_id, int index_no, int heap_id, int x, int y, int w, int h)
{
	void* buff;
	
	int size;
	
	size = ((w-x)*(h-y)*CHAR_BYTE);
	
	buff = sys_AllocMemory(heap_id, size);
	
	ChangesInto_1D_from_2D(arc_id, index_no, heap_id, x, y, w, h, buff);
	
	return buff;	
}


//--------------------------------------------------------------
/**
 * @brief	2D→1Dに展開バッファをAllocして変換する
 *
 * @param	arc_id				アーカイブインデックス
 * @param	index_no			ファイルインデックス
 * @param	heap_id				ヒープID
 * @param	rc					矩形
 *
 * @retval	void*				展開したバッファのポインタ
 *
 */
//--------------------------------------------------------------
void* ChangesInto_1D_from_2D_Alloc_RC(int arc_id, int index_no, int heap_id, CHANGES_INTO_DATA_RECT* rc)
{
	return ChangesInto_1D_from_2D_Alloc(arc_id, index_no, heap_id, rc->x, rc->y, rc->w, rc->h);
}


//--------------------------------------------------------------
/**
 * @brief	1D→OAM形状に変換
 *
 * @param	sx				変換対象データのサイズ X	
 * @param	sy				変換対象データのサイズ Y
 * @param	x				切り抜き開始 X
 * @param	y				切り抜き開始 Y
 * @param	w				切り抜きサイズ W
 * @param	h				切り抜きサイズ H
 * @param	bofs			オフセット
 * @param	src				元データ
 * @param	dst				展開先
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void ChangesInto_OAM_from_1D(int sx, int sy, int x, int y, int w, int h, int* bofs, const void* src, void* dst)
{
	int i, j;
	u8* p_data;
	u8* p_buff;
	int ofs;
	
	int lx;
	int ly;
	
	p_data = (u8*)src;
	p_buff = (u8*)dst;
	
	lx = x + w;
	ly = y + h;

	for (j = y; j < ly; j++){
		for (i = x; i < lx; i++){
			ofs = (i * CHAR_BYTE) + (j * CHAR_BYTE * sx);
			memcpy(&p_buff[ *bofs ], &p_data[ ofs ], CHAR_BYTE);
			*bofs += CHAR_BYTE;
		}
	}
}


//--------------------------------------------------------------
/**
 * @brief	1D→OAM形状に変換 矩形でサイズ指定
 *
 * @param	sx				変換対象データのサイズ X	
 * @param	sy				変換対象データのサイズ Y
 * @param	rc				矩形
 * @param	bofs			オフセット
 * @param	src				データ
 * @param	dst				展開先
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void  ChangesInto_OAM_from_1D_RC(int sx, int sy, CHANGES_INTO_DATA_RECT* rc, int* bofs, const void* src, void* dst)
{
	ChangesInto_OAM_from_1D(sx, sy, rc->x, rc->y, rc->w, rc->h, bofs, src, dst);
}


//--------------------------------------------------------------
/**
 * @brief	ポケモンのデータを2D→1D→OAMに変換
 *
 * @param	arc_id			アーカイブID
 * @param	index_no		インデックス番号
 * @param	heap_id			ヒープID
 * @param	x
 * @param	y
 * @param	w
 * @param	h
 * @param	buff			展開先バッファ
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void ChangesInto_OAM_from_PokeTex(int arc_id, int index_no, int heap_id, int x, int y, int w, int h, void* buff)
{
	int i;
	int num;
	int ofs;
	void* temp = NULL;
	
	CHANGES_INTO_DATA_RECT rc[] = {
		{ 0, 0, 8, 8 },
		{ 8, 0, 2, 4 },
		{ 8, 4, 2, 4 },
		{ 0, 8, 4, 2 },
		{ 4, 8, 4, 2 },
		{ 8, 8, 2, 2 },
	};
	
	num = NELEMS(rc);
	ofs = 0;
	
	temp = ChangesInto_1D_from_2D_Alloc(arc_id, index_no, heap_id, x, y, w, h);		///< 1Dから2Dへ変換

	for (i = 0; i < num; i++){
		ChangesInto_OAM_from_1D_RC(w, h, &rc[i], &ofs, temp, buff);
	}
	
	sys_FreeMemoryEz(temp);
}


//--------------------------------------------------------------
/**
 * @brief	ポケモンのデータを2D→1D→OAMに変換
 *
 * @param	arc_id			アーカイブID
 * @param	index_no		インデックス番号
 * @param	heap_id			ヒープID
 * @param	rc				矩形
 * @param	buff			バッファ
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void  ChangesInto_OAM_from_PokeTex_RC(int arc_id, int index_no, int heap_id, CHANGES_INTO_DATA_RECT* rc, void* buff)
{
	ChangesInto_OAM_from_PokeTex(arc_id, index_no, heap_id, rc->x, rc->y, rc->w, rc->h, buff);
}


//--------------------------------------------------------------
/**
 * @brief	ポケモンのデータを2D→1D→OAMに変換
 *
 * @param	arc_id			アーカイブID
 * @param	index_no		インデックス番号
 * @param	heap_id			ヒープID
 * @param	x
 * @param	y
 * @param	w
 * @param	h
 *
 * @retval	void*	
 *
 */
//--------------------------------------------------------------
void* ChangesInto_OAM_from_PokeTex_Alloc(int arc_id, int index_no, int heap_id, int x, int y, int w, int h)
{
	void* buff = NULL;
	
	int size;
	
	size = ((w-x)*(h-y)*CHAR_BYTE);

	buff = sys_AllocMemory(heap_id, size);
	
	ChangesInto_OAM_from_PokeTex(arc_id, index_no, heap_id, x, y, w, h, buff);
	
	return buff;
}


//--------------------------------------------------------------
/**
 * @brief	ポケモンのデータを2D→1D→OAMに変換
 *
 * @param	arc_id			アーカイブID
 * @param	index_no		インデックス番号
 * @param	heap_id			ヒープID
 * @param	rc				矩形
 *
 * @retval	void*	
 *
 */
//--------------------------------------------------------------
void* ChangesInto_OAM_from_PokeTex_Alloc_RC(int arc_id, int index_no, int heap_id, CHANGES_INTO_DATA_RECT* rc)
{
	return ChangesInto_OAM_from_PokeTex_Alloc(arc_id, index_no, heap_id, rc->x, rc->y, rc->w, rc->h);
}


//--------------------------------------------------------------
/**
 * @brief	ポケモンデータを戦闘用に変換
 *
 * @param	arc_id	
 * @param	index_no	
 * @param	heap_id	
 * @param	buff	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void  ChangesInto_BattlePokeData(int arc_id, int index_no, int heap_id, void* buff)
{
	CHANGES_INTO_DATA_RECT rc = {
		POKE_TEX_SX,
		POKE_TEX_SY,
		POKE_TEX_EX,
		POKE_TEX_EY
	};
	
	ChangesInto_OAM_from_PokeTex_RC(arc_id, index_no, heap_id, &rc, buff);
}


//--------------------------------------------------------------
/**
 * @brief	ポケモンデータを戦闘用に変換
 *
 * @param	arc_id	
 * @param	index_no	
 * @param	heap_id	
 *
 * @retval	void*	
 *
 */
//--------------------------------------------------------------
void* ChangesInto_BattlePokeData_Alloc(int arc_id, int index_no, int heap_id)
{
	void* buff = NULL;
	
	int size;
	
	size = POKE_TEX_SIZE;
	
	buff = sys_AllocMemory(heap_id, size);
	
	ChangesInto_BattlePokeData(arc_id, index_no, heap_id, buff);
	
	return buff;	
}
#endif
