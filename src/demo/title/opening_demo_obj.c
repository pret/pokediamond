//=============================================================================
/**
 * @file	opening_demo_obj.c
 * @brief	オープニングデモＯＢＪ
 * @author	Nozomu Saito
 * @date    2006.06.03
 */
//=============================================================================
#include "common.h"
#include "system/arc_tool.h"
#include "system/arc_util.h"
#include "op_demo.naix"
#include "opening_kira_obj.h"
#include "opening_demo_obj.h"
#include "op_frame_def.h"


#define RESOURCE_NUM	(4)
#define PERSON_ACT_MAX	(3)
#define BIRD_ACT_MAX	(6)
#define KIRA_ACT_MAX	(16)

#define OPD_CHAR_CONT_NUM				(ACT_ID_MAX)
#define OPD_CHAR_VRAMTRANS_MAIN_SIZE	(0)
#define OPD_CHAR_VRAMTRANS_SUB_SIZE		(0)
#define OPD_PLTT_CONT_NUM				(ACT_ID_MAX)


#define PALETTE_NUM	(1)		//パレット１本

#define OP_DEMO_ACT_MAX	( PERSON_ACT_MAX+BIRD_ACT_MAX+KIRA_ACT_MAX )
#define CLACT_WORK_MAX	( PERSON_ACT_MAX+BIRD_ACT_MAX )

#define HERO_POS_X		(128-48)	//男主人公のＸ位置（ドット）
#define HEROINE_POS_X	(128+48)	//女主人公のＸ位置（ドット）
#define HERO_POS_Y		(14*8)		//男主人公のＹ位置（ドット）
#define HEROINE_POS_Y	(14*8)		//女主人公のＹ位置（ドット）
#define RIVAL_POS_X		(256+64)	//ライバルのＸ位置（ドット）
#define RIVAL_POS_Y		(14*8)		//ライバルのＹ位置（ドット）
#define BIRD_1_POS_X	(256+8)		//鳥1のＸ位置（ドット）
#define BIRD_1_POS_Y	(16*8)		//鳥1のＹ位置（ドット）
#define BIRD_2_POS_X	(256+32)	//鳥2のＸ位置（ドット）
#define BIRD_2_POS_Y	(14*8)		//鳥2のＹ位置（ドット）
#define BIRD_3_POS_X	(256+32)	//鳥3のＸ位置（ドット）
#define BIRD_3_POS_Y	(18*8)		//鳥3のＹ位置（ドット）

#define BIRD_4_POS_X	(192+8)		//鳥4のＸ位置（ドット）
#define BIRD_4_POS_Y	(28*8)		//鳥4のＹ位置（ドット）
#define BIRD_5_POS_X	(192+32)	//鳥5のＸ位置（ドット）
#define BIRD_5_POS_Y	(26*8)		//鳥5のＹ位置（ドット）
#define BIRD_6_POS_X	(192+32)	//鳥6のＸ位置（ドット）
#define BIRD_6_POS_Y	(30*8)		//鳥6のＹ位置（ドット）

#define RIVAL_SLIDE_SPEED	(FX32_ONE*14)


#define RIVAL_POS_END_X	(FX32_ONE*(128+48))	//スライドイン終了時のライバル位置（ドット）
typedef enum {
	ACT_ID_HERO,
	ACT_ID_HEROINE,
	ACT_ID_RIVAL,
	ACT_ID_BIRD,
	ACT_ID_KIRA,
	ACT_ID_MAX,
};

typedef struct OP_DEMO_OBJ_WORK_tag
{
	CLACT_SET_PTR 			ClactSet;								// セルアクターセット
	CLACT_U_EASYRENDER_DATA	RendData;								// 簡易レンダーデータ
	CLACT_U_RES_MANAGER_PTR	ResMan[RESOURCE_NUM];				// リソースマネージャ
	CLACT_U_RES_OBJ_PTR 	ResObjTbl[ACT_ID_MAX][RESOURCE_NUM];		// リソースオブジェテーブル
	CLACT_WORK_PTR			ClActWork[CLACT_WORK_MAX];				// セルアクターワークポインタ配列
}OP_DEMO_OBJ_WORK;


//リソースマネージャー登録数テーブル
static const u8 ResEntryNumTbl[RESOURCE_NUM] = {
	ACT_ID_MAX,			//キャラリソース
	ACT_ID_MAX,			//パレットリソース
	ACT_ID_MAX,			//セルリソース
	ACT_ID_MAX,			//セルアニメリソース
};

//アクターＩＤとアクターワークの対応表
static int ActIDTbl[CLACT_WORK_MAX] = {
	ACT_ID_HERO,			//主人公男
	ACT_ID_HEROINE,			//主人公女
	ACT_ID_RIVAL,			//ライバル
	ACT_ID_BIRD,			//鳥
	ACT_ID_BIRD,			//鳥
	ACT_ID_BIRD,			//鳥
	ACT_ID_KIRA,			//キラキラ
};

static u16 BlackPalette[16] = {
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
};

static fx32 BirdXSpeed1[3] = {
	(FX32_ONE/2)*12,(FX32_ONE/2)*11,(FX32_ONE/2)*10,
};

static fx32 BirdXSpeed2[3] = {
	(FX32_ONE/2)*8,(FX32_ONE/2)*10,(FX32_ONE/2)*11,
};

//-------------------------------------
//
//	キャラクタマネージャー
//	パレットマネージャーの初期化
//
//=====================================
static void OpdInitCharPlttManager()
{
	const int heapid = HEAPID_OP_DEMO;
	// キャラクタマネージャー初期化
	{
		CHAR_MANAGER_MAKE cm = {
			OPD_CHAR_CONT_NUM,
			OPD_CHAR_VRAMTRANS_MAIN_SIZE,
			OPD_CHAR_VRAMTRANS_SUB_SIZE,
			heapid
		};
		InitCharManager(&cm);
	}
	// パレットマネージャー初期化
	InitPlttManager(OPD_PLTT_CONT_NUM, heapid);

	// 読み込み開始位置を初期化
	CharLoadStartAll();
	PlttLoadStartAll();

}

//--------------------------------------------------------------------------------------------
/**
 * セルアクターヘッダ作成
 *
 * @param	inActID		登録ＩＤ
 * @param	wk			オープニングＯＢＪデータポインタ
 * @param	outAdd		アクターヘッダ格納場所
 * 
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void MakeClActHeader(const int inActID, OPD_OBJ_PTR wk,
							const int inPriority,
							CLACT_ADD *outAdd, CLACT_HEADER *outClActHeader)
{
	// セルアクターヘッダ作成	
	CLACT_U_MakeHeader(	outClActHeader,
						inActID, inActID, inActID, inActID,
						CLACT_U_HEADER_DATA_NONE, CLACT_U_HEADER_DATA_NONE,
						0, inPriority,
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
 * オープニングＯＢＪデータ構造体サイズ取得関数
 *
 * @param	void
 *
 * @return	int		サイズ
 */
//--------------------------------------------------------------------------------------------
const int OPD_Obj_GetWorkSize( void )
{
	return sizeof(OP_DEMO_OBJ_WORK);
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
void OPD_Obj_InitCellActor( OPD_OBJ_PTR wk )
{
	int i;
	const int heapid = HEAPID_OP_DEMO;

	//マッピングモード設定
	GX_SetOBJVRamModeChar(GX_OBJVRAMMODE_CHAR_1D_32K);
	
	OpdInitCharPlttManager();
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
	wk->ClactSet = CLACT_U_SetEasyInit( OP_DEMO_ACT_MAX, &wk->RendData, heapid );
	
	//リソースマネージャー初期化
	for(i=0;i<RESOURCE_NUM;i++){		//リソースマネージャー作成
		wk->ResMan[i] = CLACT_U_ResManagerInit(ResEntryNumTbl[i], i, heapid);
	}

	//--chara読み込み
										
	//主人公　男
	wk->ResObjTbl[ACT_ID_HERO][CLACT_U_CHAR_RES] = CLACT_U_ResManagerResAddArcChar(
										wk->ResMan[CLACT_U_CHAR_RES],
										ARC_OP_DEMO, NARC_op_demo_title_hero_NCGR,
										FALSE, ACT_ID_HERO, NNS_G2D_VRAM_TYPE_2DMAIN, heapid);
	//主人公　女
	wk->ResObjTbl[ACT_ID_HEROINE][CLACT_U_CHAR_RES] = CLACT_U_ResManagerResAddArcChar(
										wk->ResMan[CLACT_U_CHAR_RES],
										ARC_OP_DEMO, NARC_op_demo_title_heroine_NCGR,
										FALSE, ACT_ID_HEROINE, NNS_G2D_VRAM_TYPE_2DMAIN, heapid);
	//ライバル
	wk->ResObjTbl[ACT_ID_RIVAL][CLACT_U_CHAR_RES] = CLACT_U_ResManagerResAddArcChar(
										wk->ResMan[CLACT_U_CHAR_RES],
										ARC_OP_DEMO, NARC_op_demo_title_rivel_NCGR,
										FALSE, ACT_ID_RIVAL, NNS_G2D_VRAM_TYPE_2DMAIN, heapid);

	//鳥
	wk->ResObjTbl[ACT_ID_BIRD][CLACT_U_CHAR_RES] = CLACT_U_ResManagerResAddArcChar(
										wk->ResMan[CLACT_U_CHAR_RES],
										ARC_OP_DEMO, NARC_op_demo_title_bird_NCGR,
										FALSE, ACT_ID_BIRD, NNS_G2D_VRAM_TYPE_2DMAIN, heapid);

	//キラキラ
	wk->ResObjTbl[ACT_ID_KIRA][CLACT_U_CHAR_RES] = CLACT_U_ResManagerResAddArcChar(
										wk->ResMan[CLACT_U_CHAR_RES],
										ARC_OP_DEMO, NARC_op_demo_logo_kira_NCGR,
										FALSE, ACT_ID_KIRA, NNS_G2D_VRAM_TYPE_2DSUB, heapid);	
	//--pal読み込み

	//主人公　男
	wk->ResObjTbl[ACT_ID_HERO][CLACT_U_PLTT_RES] = CLACT_U_ResManagerResAddArcPltt(
										wk->ResMan[CLACT_U_PLTT_RES],
										ARC_OP_DEMO, NARC_op_demo_title_hero_NCLR,
										FALSE, ACT_ID_HERO, NNS_G2D_VRAM_TYPE_2DMAIN, PALETTE_NUM, heapid);
	//主人公　女
	wk->ResObjTbl[ACT_ID_HEROINE][CLACT_U_PLTT_RES] = CLACT_U_ResManagerResAddArcPltt(
										wk->ResMan[CLACT_U_PLTT_RES],
										ARC_OP_DEMO, NARC_op_demo_title_heroine_NCLR,
										FALSE, ACT_ID_HEROINE, NNS_G2D_VRAM_TYPE_2DMAIN, PALETTE_NUM, heapid);
	//ライバル
	wk->ResObjTbl[ACT_ID_RIVAL][CLACT_U_PLTT_RES] = CLACT_U_ResManagerResAddArcPltt(
										wk->ResMan[CLACT_U_PLTT_RES],
										ARC_OP_DEMO, NARC_op_demo_title_rivel_NCLR,
										FALSE, ACT_ID_RIVAL, NNS_G2D_VRAM_TYPE_2DMAIN, PALETTE_NUM, heapid);

	//鳥
	wk->ResObjTbl[ACT_ID_BIRD][CLACT_U_PLTT_RES] = CLACT_U_ResManagerResAddArcPltt(
										wk->ResMan[CLACT_U_PLTT_RES],
										ARC_OP_DEMO, NARC_op_demo_title_bird_NCLR,
										FALSE, ACT_ID_BIRD, NNS_G2D_VRAM_TYPE_2DMAIN, PALETTE_NUM, heapid);

	//キラキラ
	wk->ResObjTbl[ACT_ID_KIRA][CLACT_U_PLTT_RES] = CLACT_U_ResManagerResAddArcPltt(
										wk->ResMan[CLACT_U_PLTT_RES],
										ARC_OP_DEMO, NARC_op_demo_logo_kira_NCLR,
										FALSE, ACT_ID_KIRA, NNS_G2D_VRAM_TYPE_2DSUB, PALETTE_NUM, heapid);
	//--cell読み込み
										
	//主人公　男
	wk->ResObjTbl[ACT_ID_HERO][CLACT_U_CELL_RES] = CLACT_U_ResManagerResAddArcKindCell(
										wk->ResMan[CLACT_U_CELL_RES],
										ARC_OP_DEMO, NARC_op_demo_title_hero_NCER,
										FALSE, ACT_ID_HERO, CLACT_U_CELL_RES, heapid);
	//主人公　女
	wk->ResObjTbl[ACT_ID_HEROINE][CLACT_U_CELL_RES] = CLACT_U_ResManagerResAddArcKindCell(
										wk->ResMan[CLACT_U_CELL_RES],
										ARC_OP_DEMO, NARC_op_demo_title_heroine_NCER,
										FALSE, ACT_ID_HEROINE, CLACT_U_CELL_RES, heapid);
	//ライバル
	wk->ResObjTbl[ACT_ID_RIVAL][CLACT_U_CELL_RES] = CLACT_U_ResManagerResAddArcKindCell(
										wk->ResMan[CLACT_U_CELL_RES],
										ARC_OP_DEMO, NARC_op_demo_title_rivel_NCER,
										FALSE, ACT_ID_RIVAL, CLACT_U_CELL_RES, heapid);

	//鳥
	wk->ResObjTbl[ACT_ID_BIRD][CLACT_U_CELL_RES] = CLACT_U_ResManagerResAddArcKindCell(
										wk->ResMan[CLACT_U_CELL_RES],
										ARC_OP_DEMO, NARC_op_demo_title_bird_NCER,
										FALSE, ACT_ID_BIRD, CLACT_U_CELL_RES, heapid);

	//キラキラ
	wk->ResObjTbl[ACT_ID_KIRA][CLACT_U_CELL_RES] = CLACT_U_ResManagerResAddArcKindCell(
										wk->ResMan[CLACT_U_CELL_RES],
										ARC_OP_DEMO, NARC_op_demo_logo_kira_NCER,
										FALSE, ACT_ID_KIRA, CLACT_U_CELL_RES, heapid);
	//--同じ関数でanim読み込み
										
	//主人公　男
	wk->ResObjTbl[ACT_ID_HERO][CLACT_U_CELLANM_RES] = CLACT_U_ResManagerResAddArcKindCell(
										wk->ResMan[CLACT_U_CELLANM_RES],
										ARC_OP_DEMO, NARC_op_demo_title_hero_NANR,
										FALSE, ACT_ID_HERO, CLACT_U_CELLANM_RES, heapid);
	//主人公　女
	wk->ResObjTbl[ACT_ID_HEROINE][CLACT_U_CELLANM_RES] = CLACT_U_ResManagerResAddArcKindCell(
										wk->ResMan[CLACT_U_CELLANM_RES],
										ARC_OP_DEMO, NARC_op_demo_title_heroine_NANR,
										FALSE, ACT_ID_HEROINE, CLACT_U_CELLANM_RES, heapid);
	//ライバル
	wk->ResObjTbl[ACT_ID_RIVAL][CLACT_U_CELLANM_RES] = CLACT_U_ResManagerResAddArcKindCell(
										wk->ResMan[CLACT_U_CELLANM_RES],
										ARC_OP_DEMO, NARC_op_demo_title_rivel_NANR,
										FALSE, ACT_ID_RIVAL, CLACT_U_CELLANM_RES, heapid);

	//鳥
	wk->ResObjTbl[ACT_ID_BIRD][CLACT_U_CELLANM_RES] = CLACT_U_ResManagerResAddArcKindCell(
										wk->ResMan[CLACT_U_CELLANM_RES],
										ARC_OP_DEMO, NARC_op_demo_title_bird_NANR,
										FALSE, ACT_ID_BIRD, CLACT_U_CELLANM_RES, heapid);

	//キラキラ
	wk->ResObjTbl[ACT_ID_KIRA][CLACT_U_CELLANM_RES] = CLACT_U_ResManagerResAddArcKindCell(
										wk->ResMan[CLACT_U_CELLANM_RES],
										ARC_OP_DEMO, NARC_op_demo_logo_kira_NANR,
										FALSE, ACT_ID_KIRA, CLACT_U_CELLANM_RES, heapid);
	
	// リソースマネージャーから転送

	for (i=0;i<ACT_ID_MAX;i++){
		// Chara転送
		CLACT_U_CharManagerSet( wk->ResObjTbl[i][CLACT_U_CHAR_RES] );
		// パレット転送
		CLACT_U_PlttManagerSet( wk->ResObjTbl[i][CLACT_U_PLTT_RES] );
	}

	GF_Disp_GX_VisibleControl( GX_PLANEMASK_OBJ, VISIBLE_ON );		// MAIN DISP OBJ ON
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
void OPD_Obj_EndCellActor( OPD_OBJ_PTR wk )
{
	u8 i;
	// セルアクターリソース解放

	for (i=0;i<ACT_ID_MAX;i++){
		// キャラ転送マネージャー破棄
		CLACT_U_CharManagerDelete(wk->ResObjTbl[i][CLACT_U_CHAR_RES]);
		// パレット転送マネージャー破棄
		CLACT_U_PlttManagerDelete(wk->ResObjTbl[i][CLACT_U_PLTT_RES]);
	}
	
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
void OPD_Obj_SetActor( OPD_OBJ_PTR wk )
{
	int i;
	CLACT_HEADER			cl_act_header;
	CLACT_ADD add;

	const int bird_act[BIRD_ACT_MAX] = {
		ACT_WORK_BIRD_1,
		ACT_WORK_BIRD_2,
		ACT_WORK_BIRD_3,
		ACT_WORK_BIRD_4,
		ACT_WORK_BIRD_5,
		ACT_WORK_BIRD_6,
	};

	const int bird_pos_x[BIRD_ACT_MAX] = {
		BIRD_1_POS_X,
		BIRD_2_POS_X,
		BIRD_3_POS_X,
		BIRD_4_POS_X,
		BIRD_5_POS_X,
		BIRD_6_POS_X,
	};

	const int bird_pos_y[BIRD_ACT_MAX] = {
		BIRD_1_POS_Y,
		BIRD_2_POS_Y,
		BIRD_3_POS_Y,
		BIRD_4_POS_Y,
		BIRD_5_POS_Y,
		BIRD_6_POS_Y,
	};

	{
		//セルアクター表示開始
		// 下画面(メイン画面)
		
		//主人公　男
		MakeClActHeader( ACT_ID_HERO, wk, 1, &add, &cl_act_header );
		add.mat.x = FX32_ONE * HERO_POS_X;
		add.mat.y = FX32_ONE * HERO_POS_Y;
		wk->ClActWork[ACT_WORK_HERO] = CLACT_Add(&add);
		CLACT_SetAnmFlag(wk->ClActWork[ACT_WORK_HERO],0);
		CLACT_SetDrawFlag(wk->ClActWork[ACT_WORK_HERO], 0);	//非表示
		
		//主人公　女
		MakeClActHeader( ACT_ID_HEROINE, wk, 1, &add, &cl_act_header );
		add.mat.x = FX32_ONE * HERO_POS_X/*HEROINE_POS_X*/;
		add.mat.y = FX32_ONE * HERO_POS_Y/*HEROINE_POS_Y*/;
		wk->ClActWork[ACT_WORK_HEROINE] = CLACT_Add(&add);
		CLACT_SetAnmFlag(wk->ClActWork[ACT_WORK_HEROINE],0);
		CLACT_SetDrawFlag(wk->ClActWork[ACT_WORK_HEROINE], 0);	//非表示

		//主人公アニメ
		OPD_Obj_ChangeHeroHeroineAnime(wk, 3);
		
		//ライバル
		MakeClActHeader( ACT_ID_RIVAL, wk, 1, &add, &cl_act_header );
		add.mat.x = FX32_ONE * RIVAL_POS_X;
		add.mat.y = FX32_ONE * RIVAL_POS_Y;
		wk->ClActWork[ACT_WORK_RIVAL] = CLACT_Add(&add);
		CLACT_SetAnmFlag(wk->ClActWork[ACT_WORK_RIVAL],1);
		CLACT_SetDrawFlag(wk->ClActWork[ACT_WORK_RIVAL], 0);	//非表示

		//鳥
		for(i=0;i<BIRD_ACT_MAX;i++){
			MakeClActHeader( ACT_ID_BIRD, wk, 0, &add, &cl_act_header );
			add.mat.x = FX32_ONE * bird_pos_x[i];
			add.mat.y = FX32_ONE * bird_pos_y[i];
			wk->ClActWork[ bird_act[i] ] = CLACT_Add(&add);
			CLACT_SetAnmFlag(wk->ClActWork[ bird_act[i] ],1);
			CLACT_SetDrawFlag(wk->ClActWork[ bird_act[i] ], 1);	//非表示
		}
	}	
}

//--------------------------------------------------------------------------------------------
/**
 * セルアクターをセット(キラキラ)
 *
 * @param	wk		OBJワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void OPD_Obj_SetKiraActor( OPD_OBJ_PTR wk, OPD_KIRA_DATLST_PTR pKiraDataListPtr )
{
	int i;
	CLACT_HEADER			cl_act_header;
	CLACT_ADD add;

	CLACT_WORK_PTR *act_work;

	{
		//セルアクター表示開始
		// 上画面(サブ画面)
		
		//キラキラ
		MakeClActHeader( ACT_ID_KIRA, wk, 0, &add, &cl_act_header);
		add.DrawArea	= NNS_G2D_VRAM_TYPE_2DSUB;

		for (i=0;i<KIRA_ACT_MAX;i++){
///			add.mat.x = FX32_ONE * (gf_rand()%256);
///			add.mat.y = FX32_ONE * (192+gf_rand()%192);
			
			act_work = OPDKira_GetActWorkPtrFromList( pKiraDataListPtr, i );
			(*act_work) = CLACT_Add(&add);
			CLACT_SetAnmFlag(*act_work,0);
			CLACT_SetDrawFlag(*act_work, 0);	//非表示
		}
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
void OPD_Obj_DrawActor( OPD_OBJ_PTR wk )
{
	CLACT_Draw( wk->ClactSet );
}

//--------------------------------------------------------------------------------------------
/**
 * OBJの表示・非表示
 *
 * @param	wk				OBJワーク
 * @param	inActWorkNo		アクターワークナンバー
 * @param	inFlg			表示フラグ
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void OPD_Obj_DispOnOff( OPD_OBJ_PTR wk, const u8 inActWorkNo, const u8 inFlg )
{
	CLACT_SetDrawFlag(wk->ClActWork[inActWorkNo], inFlg);
}

//--------------------------------------------------------------------------------------------
/**
 * OBJの位置変更
 *
 * @param	wk				OBJワーク
 * @param	inActWorkNo		アクターワークナンバー
 * @param	inFlg			表示フラグ
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void OPD_Obj_ChangePos( OPD_OBJ_PTR wk, const u8 inActWorkNo, const int inX, const int inY )
{
	VecFx32 vec;
	
	vec =  *CLACT_GetMatrix( wk->ClActWork[inActWorkNo] );
	vec.x = inX;
	vec.y = inY;
	CLACT_SetMatrix( wk->ClActWork[inActWorkNo], &vec );
}

//--------------------------------------------------------------------------------------------
/**
 * ヒロインOBJの位置変更
 *
 * @param	wk				OBJワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void OPD_Obj_ChangeHeroinePos( OPD_OBJ_PTR wk )
{
	OPD_Obj_ChangePos( wk, ACT_WORK_HEROINE, FX32_ONE*HEROINE_POS_X, FX32_ONE*HEROINE_POS_Y );
}

//--------------------------------------------------------------------------------------------
/**
 * ヒーロー・ヒロインOBJのアニメ変更
 *
 * @param	wk				OBJワーク
 * @param	inNo			アニメナンバー
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void OPD_Obj_ChangeHeroHeroineAnime( OPD_OBJ_PTR wk, const u8 inNo )
{
	CLACT_AnmChg( wk->ClActWork[ACT_WORK_HERO], inNo );
	CLACT_AnmChg( wk->ClActWork[ACT_WORK_HEROINE], inNo );
}

//--------------------------------------------------------------------------------------------
/**
 * ヒーロー・ヒロインOBJのアニメ開始・停止
 *
 * @param	wk				OBJワーク
 * @param	inNo			アニメナンバー
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void OPD_Obj_OnOffHeroHeroineAnime( OPD_OBJ_PTR wk, const u8 inAnime )
{
	CLACT_SetAnmFlag(wk->ClActWork[ACT_WORK_HERO],inAnime);
	CLACT_SetAnmFlag(wk->ClActWork[ACT_WORK_HEROINE],inAnime);
}

//--------------------------------------------------------------------------------------------
/**
 * ライバルスライドイン
 *
 * @param	wk	OBJワーク	
 *
 * @return	BOOL	TRUEでスライド終了
 */
//--------------------------------------------------------------------------------------------
BOOL OPD_Obj_SlideInRival(OPD_OBJ_PTR wk)
{
	VecFx32 vec;
	
	vec =  *CLACT_GetMatrix( wk->ClActWork[ACT_WORK_RIVAL] );
	vec.x -= RIVAL_SLIDE_SPEED;

	if (vec.x <= RIVAL_POS_END_X){
		vec.x = RIVAL_POS_END_X;
		CLACT_SetMatrix( wk->ClActWork[ACT_WORK_RIVAL], &vec );
		return TRUE;
	}
	CLACT_SetMatrix( wk->ClActWork[ACT_WORK_RIVAL], &vec );
	return FALSE;
}

//--------------------------------------------------------------------------------------------
/**
 * OBJの色変更（黒＜==＞元の色）
 *
 * @param	wk				OBJワーク
 * @param	inActWorkNo		アクターワークナンバー
 * @param	inColChgMode	色変更モード
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void OPD_Obj_ChangeCollor(OPD_OBJ_PTR wk, const int inActWorkNo, const u8 inColChgMode)
{
	NNSG2dImagePaletteProxy *proxy = CLACT_PaletteProxyGet( wk->ClActWork[inActWorkNo] );
	u32 palette_vram = NNS_G2dGetImagePaletteLocation( proxy, NNS_G2D_VRAM_TYPE_2DMAIN );
	if (inColChgMode == CHG_MODE_BLACK){	
		GX_LoadOBJPltt( BlackPalette, palette_vram, 16*2 );	//32byte 1Palette
	}else{
		NNSG2dPaletteData *data;
		data = CLACT_U_ResManagerGetResObjResPltt(wk->ResObjTbl[ ActIDTbl[inActWorkNo] ][CLACT_U_PLTT_RES]);
		GX_LoadOBJPltt( data->pRawData, palette_vram, 16*2 );	//32byte 1Palette
	}
}

//--------------------------------------------------------------------------------------------
/**
 * 鳥スライドイン
 *
 * @param	wk				OBJワーク
 * @param	inCounter		フレームカウンタ
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void  OPD_Obj_SlideInBird(OPD_OBJ_PTR wk, const int inCounter)
{	
	u8 i;
	VecFx32 vec;

	const int bird_act1[3] = {
		ACT_WORK_BIRD_1,
		ACT_WORK_BIRD_2,
		ACT_WORK_BIRD_3,
	};
	const int bird_act2[3] = {
		ACT_WORK_BIRD_4,
		ACT_WORK_BIRD_5,
		ACT_WORK_BIRD_6,
	};

	if (inCounter >= FM_BIRD_IN_1){
		for (i=0;i<3;i++){
			vec =  *CLACT_GetMatrix( wk->ClActWork[ bird_act1[i] ] );
			vec.x -= BirdXSpeed1[i];
			vec.y -= (FX32_ONE*4);
			CLACT_SetMatrix( wk->ClActWork[ bird_act1[i] ], &vec );
		}
	}

	if (inCounter >= FM_BIRD_IN_2){
		for (i=0;i<3;i++){
			vec =  *CLACT_GetMatrix( wk->ClActWork[ bird_act2[i] ] );
			vec.x -= BirdXSpeed2[i];
			vec.y -= (FX32_ONE*4);
			CLACT_SetMatrix( wk->ClActWork[ bird_act2[i] ], &vec );
		}
	}
}
