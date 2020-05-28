//=============================================================================
/**
 * @file	opening_kira_obj.c
 * @brief	オープニングデモＯＢＪ
 * @author	Nozomu Saito
 * @date    2006.06.03
 */
//=============================================================================
#include "common.h"
#include "system/arc_tool.h"
#include "system/arc_util.h"
#include "system/clact_tool.h"
#include "op_demo.naix"
#include "opening_kira_obj.h"

#include "op_frame_def.h"

#define RESOURCE_NUM	(4)
#define OPD_KIRA_ACT_MAX	(10)
#define GENERATER_MAX	(3)
#define PALETTE_NUM	(1)		//パレット１本

enum {
	ACT_ID_KIRA,
	ACT_ID_MAX,
};

enum {
	GENE_TYPE_FIRST,
	GENE_TYPE_SEC
};

#define OPD_KIRA_CHAR_CONT_NUM				(ACT_ID_MAX)
#define OPD_KIRA_CHAR_VRAMTRANS_MAIN_SIZE	(0)
#define OPD_KIRA_CHAR_VRAMTRANS_SUB_SIZE	(0)
#define OPD_KIRA_PLTT_CONT_NUM				(ACT_ID_MAX)

#define OPD_KIRA_X_BASE		(64)
#define OPD_KIRA_Y_BASE1	(64)
#define OPD_KIRA_Y_BASE2	(32)
#define OPD_KIRA_W	(128)
#define OPD_KIRA_H	(64)

#define KIRA_MOVE_MAX	(80)

#define OPD_KIRA2_X_BASE	(16-6)
#define OPD_KIRA2_Y_BASE	(64-6)
#define OPD_KIRA2_W	(224)
#define OPD_KIRA2_H	(56)
#define SCENE2_KIRA_MOVE_MAX	(8)


typedef struct OPD_KIRA_DATA_tag
{
	u8 Valid;		//データ有効フラグ
	u8 MoveCounter; //動作カウンタ
	CLACT_WORK_PTR ActWorkPtr;
	TCB_PTR	Tcb;		//制御タスクポインタ
}OPD_KIRA_DATA;

typedef struct OPD_KIRA_DATA_LIST_tag
{
	int Num;
	OPD_KIRA_DATA *Data;
}OPD_KIRA_DATA_LIST;

typedef struct KIRA_GENERATE_PARAM_tag
{
	u8 Num;
	u8 Margin;
	u8 LoopMax;
	u8 Loop;
	u8 Count;
	u8 Type;
	u8 dummy[2];
}KIRA_GENERATE_PARAM;

typedef struct OPD_KIRA_GENERATER_tag
{
	KIRA_GENERATE_PARAM GeneParam;
	TCB_PTR GeneTcb;
	OPD_KIRA_DATA *KiraDataListPtr;	//マネージャの持つキラデータのポインタ
}OPD_KIRA_GENERATER;

typedef struct OP_DEMO_OBJ_WORK_tag
{
	CLACT_SET_PTR 			ClactSet;								// セルアクターセット
	CLACT_U_EASYRENDER_DATA	RendData;								// 簡易レンダーデータ
	CLACT_U_RES_MANAGER_PTR	ResMan[RESOURCE_NUM];				// リソースマネージャ
	CLACT_U_RES_OBJ_PTR 	ResObjTbl[RESOURCE_NUM];		// リソースオブジェテーブル
	OPD_KIRA_DATA KiraData[OPD_KIRA_ACT_MAX];
}OPD_KIRA_OBJ_WORK;

typedef struct OPD_KIRA_GENERATE_MNG_tag
{
	OPD_KIRA_OBJ_WORK KiraObjWork;					//キラコントロールワーク
	OPD_KIRA_GENERATER Generater[GENERATER_MAX];	//ジェネレーター数
}OPD_KIRA_GENERATE_MNG;

//=========================================================================================
static void InitCellActor( OPD_KIRA_OBJ_WORK *wk );
static void EndCellActor( OPD_KIRA_OBJ_WORK *wk );
static void SetActor( OPD_KIRA_OBJ_WORK *wk );
static void DrawActor( OPD_KIRA_OBJ_WORK *wk );

static void CreateKiraGenerater(OPD_KIRA_GENERATER *pGenerater, OPD_K_G_MNG_PTR ptr, 
								const u8 inNum, const u8 inMargin, const u8 inLoop,
								const u8 inType);
static void TCB_GenerateFunc( TCB_PTR tcb, void* work );
static OPD_KIRA_DATA *GetInvalidKiraData(OPD_KIRA_DATA *pKiraDataList, const int inMax);
static void TCB_KiraFunc( TCB_PTR tcb, void* work );

static void Scene2_GenerateKira( OPD_KIRA_DATLST_PTR pKiraDataListPtr, const u8 inNum);
static void TCB_Scene2KiraFunc( TCB_PTR tcb, void* work );

//リソースマネージャー登録数テーブル
static const u8 ResEntryNumTbl[RESOURCE_NUM] = {
	ACT_ID_MAX,			//キャラリソース
	ACT_ID_MAX,			//パレットリソース
	ACT_ID_MAX,			//セルリソース
	ACT_ID_MAX,			//セルアニメリソース
};

//-------------------------------------
//
//	キャラクタマネージャー
//	パレットマネージャーの初期化
//
//=====================================
static void OpdKira_InitCharPlttManager()
{
	const int heapid = HEAPID_OP_DEMO;
	// キャラクタマネージャー初期化
	{
		CHAR_MANAGER_MAKE cm = {
			OPD_KIRA_CHAR_CONT_NUM,
			OPD_KIRA_CHAR_VRAMTRANS_MAIN_SIZE,
			OPD_KIRA_CHAR_VRAMTRANS_SUB_SIZE,
			heapid
		};
		InitCharManager(&cm);
	}
	// パレットマネージャー初期化
	InitPlttManager(OPD_KIRA_PLTT_CONT_NUM, heapid);

	// 読み込み開始位置を初期化
	CharLoadStartAll();
	PlttLoadStartAll();

}

//--------------------------------------------------------------------------------------------
/**
 * セルアクターヘッダ作成
 *
 * @param	wk				オープニングＯＢＪデータポインタ
 * @param	outAdd			アクターヘッダ格納場所
 * @param	outClActHeader	アクターヘッダーポインタ
 * 
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void MakeClActHeader( OPD_KIRA_OBJ_WORK *wk,
								CLACT_ADD *outAdd, CLACT_HEADER *outClActHeader  )
{
	// セルアクターヘッダ作成	
	CLACT_U_MakeHeader(	outClActHeader,
						ACT_ID_KIRA, ACT_ID_KIRA, ACT_ID_KIRA, ACT_ID_KIRA,
						CLACT_U_HEADER_DATA_NONE, CLACT_U_HEADER_DATA_NONE,
						0, 0,
						wk->ResMan[CLACT_U_CHAR_RES],
						wk->ResMan[CLACT_U_PLTT_RES],
						wk->ResMan[CLACT_U_CELL_RES],
						wk->ResMan[CLACT_U_CELLANM_RES],
						NULL,NULL);

	{
		outAdd->ClActSet	= wk->ClactSet;
		outAdd->ClActHeader	= outClActHeader;

		outAdd->mat.x		= 0;//FX32_CONST(32) ;
		outAdd->mat.y		= 0;//FX32_CONST(96) ;		//画面は上下連続している
		outAdd->mat.z		= 0;
		outAdd->sca.x		= FX32_ONE;
		outAdd->sca.y		= FX32_ONE;
		outAdd->sca.z		= FX32_ONE;
		outAdd->rot			= 0;
		outAdd->pri			= 1;
		outAdd->DrawArea	= NNS_G2D_VRAM_TYPE_2DMAIN;
		outAdd->heap		= HEAPID_OP_DEMO;
	}	
}

//--------------------------------------------------------------------------------------------
/**
 * ジェネレーターマネージャデータ作成関数
 *
 * @param	void
 *
 * @return	int		サイズ
 */
//--------------------------------------------------------------------------------------------
OPD_K_G_MNG_PTR OPDKira_AllocGeneMng( void )
{
	int size = sizeof(OPD_KIRA_GENERATE_MNG);
	OPD_K_G_MNG_PTR ptr = sys_AllocMemory(HEAPID_OP_DEMO, size);
	memset(ptr, 0, size);
	
	InitCellActor( &ptr->KiraObjWork );
	SetActor( &ptr->KiraObjWork );
	return ptr;
}

//--------------------------------------------------------------------------------------------
/**
 * キラデータリストアロケーション
 *
 * @param	inNum		確保数
 *
 * @return	OPD_KIRA_DATLST_PTR	リストポインタ
 */
//--------------------------------------------------------------------------------------------
OPD_KIRA_DATLST_PTR OPDKira_CreateList(const int inNum)
{
	int data_size;
	OPD_KIRA_DATLST_PTR lst_ptr;
	lst_ptr = sys_AllocMemory(HEAPID_OP_DEMO, sizeof(OPD_KIRA_DATA_LIST));
	data_size = sizeof(OPD_KIRA_DATA)*inNum;
	lst_ptr->Data = sys_AllocMemory( HEAPID_OP_DEMO, data_size );
	memset(lst_ptr->Data , 0, data_size);
	lst_ptr->Num = inNum;

	return lst_ptr;
}

//--------------------------------------------------------------------------------------------
/**
 * キラデータリスト解放
 *
 * @param	
 *
 * @return	OPD_KIRA_DATLST_PTR	リストポインタ
 */
//--------------------------------------------------------------------------------------------
void OPDKira_FreeList(OPD_KIRA_DATLST_PTR pKiraDataListPtr)
{
	int i;
	for(i=0;i<pKiraDataListPtr->Num;i++){
		if ( pKiraDataListPtr->Data[i].Tcb != NULL ){
			TCB_Delete(pKiraDataListPtr->Data[i].Tcb);
		}
	}
	sys_FreeMemoryEz(pKiraDataListPtr->Data);
	sys_FreeMemoryEz(pKiraDataListPtr);
}

//--------------------------------------------------------------------------------------------
/**
 * キラデータリストの指定インデックスのアクターワークを返す
 *
 * @param	pKiraDataListPtr	データリストポインタ
 * @param	inIndex				指定インデックス
 *
 * @return	CLACT_WORK_PTR		アクターワークポインタ
 */
//--------------------------------------------------------------------------------------------
CLACT_WORK_PTR *OPDKira_GetActWorkPtrFromList( OPD_KIRA_DATLST_PTR pKiraDataListPtr,
											  const int inIndex)
{
	GF_ASSERT(inIndex<pKiraDataListPtr->Num);

	return &pKiraDataListPtr->Data[inIndex].ActWorkPtr;
}

//--------------------------------------------------------------------------------------------
/**
 * ジェネレーター解放
 *
 * @param	ptr		キラジェネレーターマネージャ
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void OPDKira_FreeGeneMng(OPD_K_G_MNG_PTR ptr)
{
	u8 i;
	
	//アクター終了
	EndCellActor(&ptr->KiraObjWork);
	
	//稼動中のＴＣＢを削除
	for(i=0;i<GENERATER_MAX;i++){
		if (ptr->Generater[i].GeneTcb != NULL){
			TCB_Delete(ptr->Generater[i].GeneTcb);
		}
	}
	for(i=0;i<OPD_KIRA_ACT_MAX;i++){
		if (ptr->KiraObjWork.KiraData[i].Tcb != NULL){
			TCB_Delete(ptr->KiraObjWork.KiraData[i].Tcb);
		}
	}
	sys_FreeMemoryEz(ptr);
}

//--------------------------------------------------------------------------------------------
/**
 * セルアクター初期化
 *
 * @param	wk	OBJワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void InitCellActor( OPD_KIRA_OBJ_WORK *wk )
{
	int i;
	const int heapid = HEAPID_OP_DEMO;

	//マッピングモード設定
	GX_SetOBJVRamModeChar(GX_OBJVRAMMODE_CHAR_1D_32K);
	GXS_SetOBJVRamModeChar(GX_OBJVRAMMODE_CHAR_1D_32K);	
	
	OpdKira_InitCharPlttManager();
	// OAMマネージャーの初期化
	NNS_G2dInitOamManagerModule();

	// 共有OAMマネージャ作成
	// レンダラ用OAMマネージャ作成
	REND_OAMInit( 
			0, 128,		// メイン画面OAM管理領域
			0, 32,		// メイン画面アフィン管理領域
			0, 128,		// サブ画面OAM管理領域
			0, 32,		// サブ画面アフィン管理領域
			heapid);
	
	// セルアクター初期化
	wk->ClactSet = CLACT_U_SetEasyInit( OPD_KIRA_ACT_MAX, &wk->RendData, heapid );
	
	//リソースマネージャー初期化
	for(i=0;i<RESOURCE_NUM;i++){		//リソースマネージャー作成
		wk->ResMan[i] = CLACT_U_ResManagerInit(ResEntryNumTbl[i], i, heapid);
	}

	//--chara読み込み
										
	wk->ResObjTbl[CLACT_U_CHAR_RES] = CLACT_U_ResManagerResAddArcChar(
										wk->ResMan[CLACT_U_CHAR_RES],
										ARC_OP_DEMO, NARC_op_demo_op_demoBG0_obj_NCGR,
										FALSE, ACT_ID_KIRA, NNS_G2D_VRAM_TYPE_MAX, heapid);
	
	//--pal読み込み

	wk->ResObjTbl[CLACT_U_PLTT_RES] = CLACT_U_ResManagerResAddArcPltt(
										wk->ResMan[CLACT_U_PLTT_RES],
										ARC_OP_DEMO, NARC_op_demo_op_demoBG_obj_NCLR,
										FALSE, ACT_ID_KIRA, NNS_G2D_VRAM_TYPE_MAX, PALETTE_NUM, heapid);
		
	//--cell読み込み
										
	wk->ResObjTbl[CLACT_U_CELL_RES] = CLACT_U_ResManagerResAddArcKindCell(
										wk->ResMan[CLACT_U_CELL_RES],
										ARC_OP_DEMO, NARC_op_demo_op_demoBG0_obj_NCER,
										FALSE, ACT_ID_KIRA, CLACT_U_CELL_RES, heapid);
	
	//--同じ関数でanim読み込み
										
	wk->ResObjTbl[CLACT_U_CELLANM_RES] = CLACT_U_ResManagerResAddArcKindCell(
										wk->ResMan[CLACT_U_CELLANM_RES],
										ARC_OP_DEMO, NARC_op_demo_op_demoBG0_obj_NANR,
										FALSE, ACT_ID_KIRA, CLACT_U_CELLANM_RES, heapid);
	// リソースマネージャーから転送
	
	// Chara転送
	CLACT_U_CharManagerSet( wk->ResObjTbl[CLACT_U_CHAR_RES] );
	// パレット転送
	CLACT_U_PlttManagerSet( wk->ResObjTbl[CLACT_U_PLTT_RES] );

	GF_Disp_GX_VisibleControl( GX_PLANEMASK_OBJ, VISIBLE_ON );		// MAIN DISP OBJ ON
	GF_Disp_GXS_VisibleControl( GX_PLANEMASK_OBJ, VISIBLE_ON );		// MAIN DISP OBJ ON
}

//--------------------------------------------------------------------------------------------
/**
 * セルアクターを終了
 *
 * @param	wk	OBJワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void EndCellActor( OPD_KIRA_OBJ_WORK *wk )
{
	u8 i;
	// キャラ転送マネージャー破棄
	CLACT_U_CharManagerDelete(wk->ResObjTbl[CLACT_U_CHAR_RES]);
	// パレット転送マネージャー破棄
	CLACT_U_PlttManagerDelete(wk->ResObjTbl[CLACT_U_PLTT_RES]);
	
	// キャラ・パレット・セル・セルアニメのリソースマネージャー破棄
	for(i=0;i<RESOURCE_NUM;i++){
		CLACT_U_ResManagerDelete(wk->ResMan[i]);
	}
	// セルアクターセット破棄
	CLACT_DestSet(wk->ClactSet);

	//OAMレンダラー破棄
	REND_OAM_Delete();

	DeleteCharManager();
	DeletePlttManager();
}

//--------------------------------------------------------------------------------------------
/**
 * セルアクターをセット
 *
 * @param	wk	OBJワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void SetActor( OPD_KIRA_OBJ_WORK *wk )
{
	int i;
	CLACT_HEADER			cl_act_header;
	CLACT_ADD add;

	for(i=0;i<OPD_KIRA_ACT_MAX;i++){
		MakeClActHeader( wk, &add, &cl_act_header );
		add.mat.x = FX32_ONE * i*2;
		add.mat.y = FX32_ONE * i*2;
		wk->KiraData[i].ActWorkPtr = CLACT_Add(&add);
		
		CLACT_SetAnmFlag(wk->KiraData[i].ActWorkPtr, 0);
		CLACT_SetDrawFlag(wk->KiraData[i].ActWorkPtr, 0);	//非表示
	}	
}

//--------------------------------------------------------------------------------------------
/**
 * セルアクター描画
 *
 * @param	wk	OBJワーク	
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void DrawActor( OPD_KIRA_OBJ_WORK *wk )
{
	CLACT_Draw( wk->ClactSet );
}

//--------------------------------------------------------------------------------------------
/**
 * ジェネレーターメイン
 *
 * @param	ptr			マネージャポインタ
 * @param	inCounter	フレームカウンタ
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void KiraGenerateMain(OPD_K_G_MNG_PTR ptr, const int inCounter)
{
	if (inCounter == FM_KIRA_SATRT1){
		//ジェネレーター生成
		CreateKiraGenerater(&ptr->Generater[0], ptr, 3, 3, 3, GENE_TYPE_FIRST);
	}else if (inCounter == FM_KIRA_SATRT2){
		//ジェネレーター生成
		CreateKiraGenerater(&ptr->Generater[1], ptr, 3, 3, 3, GENE_TYPE_SEC);
	}

	DrawActor( &ptr->KiraObjWork );
}

//--------------------------------------------------------------------------------------------
/**
 * ジェネレーター生成
 *
 * @param	pGenerater	ジェネレーター
 * @param	ptr			マネージャポインタ
 * @param	inNum		生成数
 * @param	inMargin	生成間隔
 * @param	inLoop		ループ数
 * @param	inType		生成タイプ
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void CreateKiraGenerater(OPD_KIRA_GENERATER *pGenerater, OPD_K_G_MNG_PTR ptr, 
								const u8 inNum, const u8 inMargin, const u8 inLoop,
								const u8 inType)
{
	pGenerater->GeneParam.Num = inNum;
	pGenerater->GeneParam.Margin = inMargin;
	pGenerater->GeneParam.LoopMax = inLoop;
	pGenerater->GeneParam.Count = 0;
	pGenerater->GeneParam.Loop = 0;
	pGenerater->KiraDataListPtr = ptr->KiraObjWork.KiraData;
	pGenerater->GeneParam.Type = inType;
	
	pGenerater->GeneTcb = TCB_Add(TCB_GenerateFunc, pGenerater, 10);
}

//--------------------------------------------------------------------------------------------
/**
 * キラエフェクト生成
 *
 * @param	pKiraDataListPtr	データリスト
 * @param	inNum				生成数
 * @param	intype				生成タイプ
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void GenerateKira( OPD_KIRA_DATA *pKiraDataListPtr, const u8 inNum, const u8 inType)
{
	u8 i;
	OPD_KIRA_DATA *kira_data;
	int base_y;

	if(inType == GENE_TYPE_FIRST){
		base_y = OPD_KIRA_Y_BASE1;
	}else{
		base_y = OPD_KIRA_Y_BASE2;
	}
	
	for(i=0;i<inNum;i++){
		//未使用データ検索
		kira_data = GetInvalidKiraData(pKiraDataListPtr, OPD_KIRA_ACT_MAX);
		
		//座標決定
		{
			VecFx32 vec;
			vec =  *CLACT_GetMatrix( kira_data->ActWorkPtr );
			vec.x = FX32_ONE * ( OPD_KIRA_X_BASE+(gf_rand()%OPD_KIRA_W) );
			vec.y = FX32_ONE * ( base_y+(gf_rand()%OPD_KIRA_H) );
			CLACT_SetMatrix( kira_data->ActWorkPtr, &vec );
		}
		//バニッシュオフ
		CLACT_SetAnmFlag(kira_data->ActWorkPtr, 1);
		CLACT_SetDrawFlag(kira_data->ActWorkPtr, 1);
		//マネージャの持つ空きタスクを取得
		kira_data->Tcb = TCB_Add(TCB_KiraFunc, kira_data, 20);
	}
}

//--------------------------------------------------------------------------------------------
/**
 * 空いているキラデータを返す
 *
 * @param	pKiraDataList	データリスト
 * @param	inMax			リスト項目最大数
 *
 * @return	OPD_KIRA_DATA *	キラデータポインタ
 */
//--------------------------------------------------------------------------------------------
static OPD_KIRA_DATA *GetInvalidKiraData(OPD_KIRA_DATA *pKiraDataList, const int inMax)
{
	u8 i;
	OPD_KIRA_DATA *data;
	for (i=0;i<OPD_KIRA_ACT_MAX;i++){
		if (!pKiraDataList[i].Valid){
			data = &pKiraDataList[i];
			data->Valid = 1;
			data->MoveCounter = 0;
			return data;
		}
	}
	GF_ASSERT(0&&"no_acter");
	return NULL;
}

//--------------------------------------------------------------------------------------------
/**
 * キラエフェクトジェネレータータスク
 *
 * @param	tcb		タスクポインタ
 * @param	work	ワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void TCB_GenerateFunc( TCB_PTR tcb, void* work )
{
	OPD_KIRA_GENERATER * generater = work;
	KIRA_GENERATE_PARAM* param = &generater->GeneParam;
	//生成タイミングが来たら、生成開始
	if(param->Count++ >= param->Margin){
		GenerateKira(generater->KiraDataListPtr, param->Num, param->Type);
		param->Count = 0;
		if (++param->Loop >= param->LoopMax){
			//タスク終了
			TCB_Delete(tcb);
			generater->GeneTcb = NULL;
		}
	}
}

//--------------------------------------------------------------------------------------------
/**
 * キラエフェクト動作タスク
 *
 * @param	tcb		タスクポインタ
 * @param	work	ワーク	
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void TCB_KiraFunc( TCB_PTR tcb, void* work )
{
	OPD_KIRA_DATA *kira_data = work;
	//等速で下に移動して、消える
	{
		VecFx32 vec;
		vec =  *CLACT_GetMatrix( kira_data->ActWorkPtr );
		vec.y += (FX32_ONE*3);
		CLACT_SetMatrix( kira_data->ActWorkPtr, &vec );
	}

	kira_data->MoveCounter++;

	if (kira_data->MoveCounter >= KIRA_MOVE_MAX){
		TCB_Delete(tcb);
		kira_data->Tcb = NULL;
		kira_data->Valid = 0;
		//アクターバニッシュ
		CLACT_SetAnmFlag(kira_data->ActWorkPtr, 0);
		CLACT_SetDrawFlag(kira_data->ActWorkPtr, 0);
	}
}

//--------------------------------------------------------------------------------------------
/**
 * サブ画面常駐キラエフェクトメイン
 *
 * @param	pKiraDataListPtr	データリストポインタ	
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void Scene2_KiraGenerateMain(OPD_KIRA_DATLST_PTR pKiraDataListPtr)
{
	Scene2_GenerateKira( pKiraDataListPtr, 2);
}


//--------------------------------------------------------------------------------------------
/**
 * サブ画面常駐キラエフェクト生成
 *
 * @param	pKiraDataListPtr	データリストポインタ	
 * @param	inNum	生成数
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void Scene2_GenerateKira( OPD_KIRA_DATLST_PTR pKiraDataListPtr, const u8 inNum)
{
	u8 i;
	OPD_KIRA_DATA *list_top;
	OPD_KIRA_DATA *kira_data;

	list_top = pKiraDataListPtr->Data;

	for(i=0;i<inNum;i++){
		//未使用データ検索
		kira_data = GetInvalidKiraData(list_top, pKiraDataListPtr->Num);
		
		//座標決定
		{
			VecFx32 vec;
			vec =  *CLACT_GetMatrix( kira_data->ActWorkPtr );
			vec.x = FX32_ONE * ( OPD_KIRA2_X_BASE+(gf_rand()%OPD_KIRA2_W) );
			vec.y = FX32_ONE * ( 192+OPD_KIRA2_Y_BASE+(gf_rand()%OPD_KIRA2_H) );
			CLACT_SetMatrix( kira_data->ActWorkPtr, &vec );
		}
		//バニッシュオフ
		CLACT_SetAnmFlag(kira_data->ActWorkPtr, 1);
		CLACT_SetDrawFlag(kira_data->ActWorkPtr, 1);
		//マネージャの持つ空きタスクを取得
		kira_data->Tcb = TCB_Add(TCB_Scene2KiraFunc, kira_data, 20);
	}
}

//--------------------------------------------------------------------------------------------
/**
 * キラエフェクト動作タスク
 *
 * @param	tcb		タスクポインタ
 * @param	work	ワーク	
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void TCB_Scene2KiraFunc( TCB_PTR tcb, void* work )
{
	OPD_KIRA_DATA *kira_data = work;

	kira_data->MoveCounter++;

	if (kira_data->MoveCounter >= SCENE2_KIRA_MOVE_MAX){
		TCB_Delete(tcb);
		kira_data->Tcb = NULL;
		kira_data->Valid = 0;
		//アクターバニッシュ
		CLACT_SetAnmFlag(kira_data->ActWorkPtr, 0);
		CLACT_SetDrawFlag(kira_data->ActWorkPtr, 0);
	}
}
