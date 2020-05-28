//==============================================================================================
/**
 * @file	opneing_obj.c
 * @brief	オープニング OBJ
 * @author	Satoshi Nohara
 * @date	2005.12.08
 */
//==============================================================================================
#include "common.h"
#include "system/arc_tool.h"
#include "system/arc_util.h"

#include "opening.naix"
#include "opening_obj.h"


//==============================================================================================
//
//	定義
//
//==============================================================================================
//キャラクターマネージャー
#define OP_CHAR_CONT_NUM					(2)
#define OP_CHAR_VRAMTRANS_MAIN_SIZE			(2048)
#define OP_CHAR_VRAMTRANS_SUB_SIZE			(0)

//パレットマネージャー
//#define OP_PLTT_CONT_NUM					(2)						//管理パレット数
#define OP_PLTT_CONT_NUM					(3)						//管理パレット数


//==============================================================================================
//
//	構造体宣言
//
//==============================================================================================
typedef struct _POS_tag{
	int x;
	int y;
}_POS;


//==============================================================================================
//
//	データ
//
//==============================================================================================
//リソースタイプ列挙に合わせる(include/system/clact_util_res.h)
//リソースマネージャー登録数テーブル
static const u8 ResEntryNumTbl[RESOURCE_NUM] = {
	2,			//キャラリソース
	3,			//パレットリソース
	2,			//セルリソース
	2,			//セルアニメリソース
};

static const _POS obj_pos[] = {
	{86,30},	//オーキド
	//{86,30},	//ライバル
	{86,46},	//ライバル
	{92,96},	//影
};


//==============================================================================================
//
//	プロトタイプ宣言
//
//==============================================================================================
void OpeningInitCellActor( OPENING_OBJ_WORK *wk );
void OpeningSetActor( OPENING_OBJ_WORK *wk, u32 index, u32 data_no, u32 anm_no );
static void OpeningInitCharPlttManager( void );
void OpeningRereaseCellObject( OPENING_OBJ_WORK *wk );
void OpeningClactVanish(OPENING_OBJ_WORK *wk, int no, int flag);
VecFx32 OpeningClactMove(OPENING_OBJ_WORK *wk, int no, int spd);
void OpeningClactMoveInit(OPENING_OBJ_WORK *wk, int no );
void OpeningClactPosSet(OPENING_OBJ_WORK *wk, int no, int x, int y );


//==============================================================================================
//
//	関数
//
//==============================================================================================

//--------------------------------------------------------------
/**
 * @brief	セルアクター初期化
 *
 * @param	wk		OPENING_OBJ_WORK型のポインタ
 *
 * @return	none
 */
//--------------------------------------------------------------
void OpeningInitCellActor( OPENING_OBJ_WORK *wk )
{
	int i;

	OpeningInitCharPlttManager();

	//OAMマネージャーの初期化
	NNS_G2dInitOamManagerModule();

	//共有OAMマネージャ作成
	//レンダラ用OAMマネージャ作成
	//ここで作成したOAMマネージャをみんなで共有する
	REND_OAMInit( 
			0, 128,				//メイン画面OAM管理領域
			0, 32,				//メイン画面アフィン管理領域
			0, 128,				//サブ画面OAM管理領域
			0, 32,				//サブ画面アフィン管理領域
			HEAPID_OPENING);
	
	//セルアクターセットの簡単初期化(作成されたセルアクターセットが返る)
	wk->ClactSet = CLACT_U_SetEasyInit( OPENING_ACT_MAX, &wk->RendData, HEAPID_OPENING );
	
	//リソースマネージャー初期化
	for(i=0;i<RESOURCE_NUM;i++){		//リソースマネージャー作成
		wk->ResMan[i] = CLACT_U_ResManagerInit(ResEntryNumTbl[i], i, HEAPID_OPENING);
	}

	/***************/
	//	ハカセ	
	/***************/
	//chara読み込み
//	wk->ResObjTbl[OP_RES_OBJ_HAKASE][CLACT_U_CHAR_RES] = CLACT_U_ResManagerResAddArcChar(
//					wk->ResMan[CLACT_U_CHAR_RES],
//					ARC_OPENING_GRA, NARC_opening_op_hakase_NCGR,
//					FALSE, 0, NNS_G2D_VRAM_TYPE_2DMAIN, HEAPID_OPENING);

	//pal読み込み
	wk->ResObjTbl[OP_RES_OBJ_HAKASE][CLACT_U_PLTT_RES] = CLACT_U_ResManagerResAddArcPltt(
					wk->ResMan[CLACT_U_PLTT_RES],
					ARC_OPENING_GRA, NARC_opening_op_hakase_NCLR,
					FALSE, 0, NNS_G2D_VRAM_TYPE_2DMAIN, 2, HEAPID_OPENING);

	//cell読み込み
	wk->ResObjTbl[OP_RES_OBJ_HAKASE][CLACT_U_CELL_RES] = CLACT_U_ResManagerResAddArcKindCell(
					wk->ResMan[CLACT_U_CELL_RES],
					ARC_OPENING_GRA, NARC_opening_op_hakase_NCER,
					FALSE, 0, CLACT_U_CELL_RES, HEAPID_OPENING);

	//同じ関数でanim読み込み
	wk->ResObjTbl[OP_RES_OBJ_HAKASE][CLACT_U_CELLANM_RES] = CLACT_U_ResManagerResAddArcKindCell(
					wk->ResMan[CLACT_U_CELLANM_RES],
					ARC_OPENING_GRA, NARC_opening_op_hakase_NANR,
					FALSE, 0, CLACT_U_CELLANM_RES, HEAPID_OPENING);

	/***************/
	//	ライバル
	/***************/
	//chara読み込み
//	wk->ResObjTbl[OP_RES_OBJ_RIVAL][CLACT_U_CHAR_RES] = CLACT_U_ResManagerResAddArcChar(
//					wk->ResMan[CLACT_U_CHAR_RES],
//					ARC_OPENING_GRA, NARC_opening_op_rival_NCGR,
//					FALSE, 1, NNS_G2D_VRAM_TYPE_2DMAIN, HEAPID_OPENING);

	//pal読み込み
	wk->ResObjTbl[OP_RES_OBJ_RIVAL][CLACT_U_PLTT_RES] = CLACT_U_ResManagerResAddArcPltt(
					wk->ResMan[CLACT_U_PLTT_RES],
					ARC_OPENING_GRA, NARC_opening_op_rival_NCLR,
					FALSE, 1, NNS_G2D_VRAM_TYPE_2DMAIN, 1, HEAPID_OPENING);

	//cell読み込み
	wk->ResObjTbl[OP_RES_OBJ_RIVAL][CLACT_U_CELL_RES] = CLACT_U_ResManagerResAddArcKindCell(
					wk->ResMan[CLACT_U_CELL_RES],
					ARC_OPENING_GRA, NARC_opening_op_rival_NCER,
					FALSE, 1, CLACT_U_CELL_RES, HEAPID_OPENING);

	//同じ関数でanim読み込み
	wk->ResObjTbl[OP_RES_OBJ_RIVAL][CLACT_U_CELLANM_RES] = CLACT_U_ResManagerResAddArcKindCell(
					wk->ResMan[CLACT_U_CELLANM_RES],
					ARC_OPENING_GRA, NARC_opening_op_rival_NANR,
					FALSE, 1, CLACT_U_CELLANM_RES, HEAPID_OPENING);
	
	//リソースマネージャーから転送
	for( i=0; i < OP_RES_OBJ_MAX ;i++ ){
		CLACT_U_CharManagerSet( wk->ResObjTbl[i][CLACT_U_CHAR_RES] );	//Chara転送
		CLACT_U_PlttManagerSet( wk->ResObjTbl[i][CLACT_U_PLTT_RES] );	//パレット転送
	}

	GF_Disp_GX_VisibleControl( GX_PLANEMASK_OBJ, VISIBLE_ON );			//MAIN DISP OBJ ON

	return;
}

//--------------------------------------------------------------
/**
 * @brief	セルアクターをセット
 *
 * @param	wk		OPENING_OBJ_WORK型のポインタ
 *
 * @return	none
 */
//--------------------------------------------------------------
void OpeningSetActor( OPENING_OBJ_WORK *wk, u32 index, u32 data_no, u32 anm_no )
{
	int i;
	CLACT_HEADER			cl_act_header;
	
	// セルアクターヘッダ作成	
	CLACT_U_MakeHeader(	&cl_act_header,
						data_no, data_no, data_no, data_no,
						CLACT_U_HEADER_DATA_NONE, CLACT_U_HEADER_DATA_NONE,
						0, 1,
						wk->ResMan[CLACT_U_CHAR_RES],
						wk->ResMan[CLACT_U_PLTT_RES],
						wk->ResMan[CLACT_U_CELL_RES],
						wk->ResMan[CLACT_U_CELLANM_RES],
						NULL,NULL);

	{
		//登録情報格納
		u8 ofs;
		CLACT_ADD add;

		add.ClActSet	= wk->ClactSet;
		add.ClActHeader	= &cl_act_header;

		add.mat.x		= 0;//FX32_CONST(32) ;
		add.mat.y		= 0;//FX32_CONST(96) ;		//画面は上下連続している（MAINが上、SUBが下）
		add.mat.z		= 0;
		add.sca.x		= FX32_ONE;
		add.sca.y		= FX32_ONE;
		add.sca.z		= FX32_ONE;
		add.rot			= 0;
		add.pri			= 2;
		add.DrawArea	= NNS_G2D_VRAM_TYPE_2DMAIN;
		add.heap		= HEAPID_OPENING;

		//セルアクター表示開始

		add.mat.x = FX32_ONE * obj_pos[index].x;
		add.mat.y = FX32_ONE * obj_pos[index].y;
		wk->ClActWork[index] = CLACT_Add(&add);
		CLACT_SetAnmFlag( wk->ClActWork[index], 0 );
		CLACT_AnmChg( wk->ClActWork[index], anm_no );
	}	
}

//--------------------------------------------------------------
/**
 * @brief	キャラクター・パレットマネージャー初期化
 *
 * @param	none
 *
 * @return	none
 */
//--------------------------------------------------------------
static void OpeningInitCharPlttManager(void)
{
	//キャラクタマネージャー初期化
	{
		CHAR_MANAGER_MAKE cm = {
			OP_CHAR_CONT_NUM,					//キャラクタ制御数
			OP_CHAR_VRAMTRANS_MAIN_SIZE,		//メイン画面のVram転送用に用意するVramサイズ
			OP_CHAR_VRAMTRANS_SUB_SIZE,			//サブ画面のVram転送用に用意するVramサイズ
			HEAPID_OPENING						//使用するヒープ
		};
		InitCharManager(&cm);
	}

	//パレットマネージャー初期化
	InitPlttManager( OP_PLTT_CONT_NUM, HEAPID_OPENING );

	//読み込み開始位置を初期化
	CharLoadStartAll();
	PlttLoadStartAll();

	return;
}

//--------------------------------------------------------------
/**
 * @brief	2Dセルオブジェクト解放
 *
 * @param	wk		OPENING_OBJ_WORK型のポインタ
 *
 * @return	none
 */
//--------------------------------------------------------------
void OpeningRereaseCellObject(OPENING_OBJ_WORK *wk)
{
	u8 i;

	//セルアクターリソース解放
	for( i=0; i < OP_RES_OBJ_MAX ;i++ ){
		CLACT_U_CharManagerDelete( wk->ResObjTbl[i][CLACT_U_CHAR_RES] );//char転送マネージャー破棄
		CLACT_U_PlttManagerDelete( wk->ResObjTbl[i][CLACT_U_PLTT_RES] );//pltt転送マネージャー破棄
	}
		
	//キャラ・パレット・セル・セルアニメのリソースマネージャー破棄
	for( i=0; i < RESOURCE_NUM ;i++ ){
		CLACT_U_ResManagerDelete( wk->ResMan[i] );
	}

	//セルアクターセット破棄
	CLACT_DestSet(wk->ClactSet);

	//OAMレンダラー破棄
	REND_OAM_Delete();

	DeleteCharManager();
	DeletePlttManager();

	return;
}

//--------------------------------------------------------------
/**
 * @brief	バニッシュ操作
 *
 * @param	wk		OPENING_OBJ_WORK型のポインタ
 * @param	flag	描画フラグ	0:非描画	1:レンダラ描画	
 *
 * @return	none
 */
//--------------------------------------------------------------
void OpeningClactVanish(OPENING_OBJ_WORK *wk, int no, int flag)
{
	CLACT_SetDrawFlag( wk->ClActWork[no], flag );
	return;
}

//--------------------------------------------------------------
/**
 * @brief	移動
 *
 * @param	wk		OPENING_OBJ_WORK型のポインタ
 *
 * @return	none
 */
//--------------------------------------------------------------
VecFx32 OpeningClactMove(OPENING_OBJ_WORK *wk, int no, int spd)
{
	VecFx32	vec;

	vec = *( CLACT_GetMatrix(wk->ClActWork[no]) );
	vec.x += (spd * FX32_ONE);
	CLACT_SetMatrix( wk->ClActWork[no], &vec );
	return *( CLACT_GetMatrix(wk->ClActWork[no]) );
}

//--------------------------------------------------------------
/**
 * @brief	初期座標セット
 *
 * @param	wk		OPENING_OBJ_WORK型のポインタ
 *
 * @return	none
 */
//--------------------------------------------------------------
void OpeningClactMoveInit(OPENING_OBJ_WORK *wk, int no )
{
	VecFx32	vec;

	vec.x = (obj_pos[no].x * FX32_ONE);
	vec.y = (obj_pos[no].y * FX32_ONE);
	CLACT_SetMatrix( wk->ClActWork[no], &vec );
	return;
}

//--------------------------------------------------------------
/**
 * @brief	座標セット
 *
 * @param	wk		OPENING_OBJ_WORK型のポインタ
 *
 * @return	none
 */
//--------------------------------------------------------------
void OpeningClactPosSet(OPENING_OBJ_WORK *wk, int no, int x, int y )
{
	VecFx32	vec;

	vec.x = (x * FX32_ONE);
	vec.y = (y * FX32_ONE);
	CLACT_SetMatrix( wk->ClActWork[no], &vec );
	return;
}


