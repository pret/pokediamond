//============================================================================================
/**
 * @file	opening_demo.c
 * @brief	オープニングデモ
 * @author	Nozomu Saito
 * @date	2006.05.31
 */
//============================================================================================
#include "common.h"
#include "system/palanm.h"
#include "system/lib_pack.h"
#include "system/snd_tool.h"
#include "system/brightness.h"
#include "system/arc_tool.h"
#include "system/arc_util.h"
#include "system/wipe.h"
#include "system/main.h"

#include "op_demo.naix"
#include "titledemo.naix"

#include "field/field.h"
#include "demo/title.h"
#include "opening_kira_obj.h"
#include "opening_demo_obj.h"
#include "op_poke_cutin.h"

#include "op_frame_def.h"

#ifdef PM_DEBUG
//#define COPYRIGHT_SKIP		//<<有効にすると著作権情報をスキップできます
#endif

#define PAL_ONE_SIZE	(2)		//２バイト

//シーン1
#define	COPY_LIGHT_FRAME	(GF_BGL_FRAME1_M)
#define	GAME_FREAK_LOGO_M_FRAME	(GF_BGL_FRAME2_M)
#define	GAME_FREAK_LOGO_S_FRAME	(GF_BGL_FRAME2_S)
#define	BACK_BASE_M_FRAME	(GF_BGL_FRAME3_M)
#define	BACK_BASE_S_FRAME	(GF_BGL_FRAME3_S)

#define BLD_MASK_COPY_LIGHT		(GX_BLEND_PLANEMASK_BG1)
#define BLD_MASK_GF_LOGO_M		(GX_BLEND_PLANEMASK_BG2)
#define BLD_MASK_BACK_BASE_M	(GX_BLEND_PLANEMASK_BG3)
#define BLD_MASK_GF_LOGO_S		(GX_BLEND_PLANEMASK_BG2)
#define BLD_MASK_BACK_BASE_S	(GX_BLEND_PLANEMASK_BG3)

#define COPY_LIGHT_BLD_IN_COUNT_MAX	(6)	//ブレンドする速度6フレに１回変更
#define COPY_LIGHT_BLD_COUNT_MAX	(4)	//ブレンドする速度4フレに１回変更
#define OPDEMO_BRIGHTNESS_SYNC	(18)


//シーン2
#define TITLE_LOGO_WHITE_IN_SYNC	(8)
#define BG_ON	(1)
#define BG_OFF	(2)
#define G256_FRAME		(GF_BGL_FRAME3_M)
#define TOWN_FRAME		(GF_BGL_FRAME1_M)
#define SKY_FRAME		(GF_BGL_FRAME2_M)
#define WB_TITLE_FRAME	(GF_BGL_FRAME0_S)
#define OPD_BTL_PAL_NUM	(7)	//1データ当たりの戦闘ＢＧパレット本数
#define TOWN_BG_SPEED	(-1)	//空ＢＧの移動スピード
#define SKY_BG_SPEED	(1)	//空ＢＧの移動スピード
#define BATTLE_BG_SPEED	(-16)	//バトルＢＧスクロールスピード

#define SCENE2_DISP_CHG_SYNC	(4)		//シーン2バトル面切り替えブラックインアウトスピード
#define SCENE2_TOWN_SCROLL_MARGIN	(24)
#define SCENE2_SKY_SCROLL_MARGIN	(3)
#define SCENE2_BATTLE_SCROLL_MARGIN	(1)

#define OP_MAP_BLOCK_MAX	(6)
#define SONOO_TOWN_HEIGHT	(FX32_ONE*16*5)
#define SCENE2_KIRA_MAX		(16)
#define	SCENE2_KIRA_MARGIN1	(4)
#define	SCENE2_KIRA_MARGIN2	(16)

//シーン3
#define MT_CLOUD_FRAME	(GF_BGL_FRAME1_M)
#define MT_TENGAN_FRAME	(GF_BGL_FRAME2_M)
#define MT_LAKE_FRAME	(GF_BGL_FRAME3_M)
#define MT_THUNDER_FRAME	(GF_BGL_FRAME0_M)
#define MT_CLOUD_SUB_FRAME	(GF_BGL_FRAME1_S)

#define TENGAN_WH_OUT_SYNC	(18)
#define TENGAN_AFF_VAL	(0x400)
#define TENGAN_AFF_VAL2	(0x800)
//#define LAKE_AFF_VAL	(0x40)
#define AFF_LIMIT_1	(0x3000)
//#define LAVE_AFF_LIMIT	(0xa80)

#define SCENE3_START_IN_SYNC	(120)		//シーン3開始ブラックインスピード

typedef enum {
	BTL_PAL_NAETORU,
	BTL_PAL_HIKOZARU,
	BTL_PAL_POTTYAMA,
	BTL_PAL_RIVAL,
	BTL_PAL_MAX
};

typedef enum{
	DISP_MAIN,
	DISP_SUB,
};

typedef struct BLOCK_3D_DATA_tag
{
	NNSG3dRenderObj			RenderObj;
	NNSG3dResFileHeader* ResFile;
}BLOCK_3D_DATA;

typedef struct SCENE2_3D_DATA_tag
{
	void			*TexFile;		//テクスチャーファイル実体へのポインタ
	NNSG3dResTex	*Texture;
	GF_CAMERA_PTR CameraPtr;		//カメラ
	BLOCK_3D_DATA	Block[OP_MAP_BLOCK_MAX];
}SCENE2_3D_DATA;

typedef struct SCENE3_THUNDER_DATA_tag
{
	u8 Request;
	u8 NowPalTblNo;	//パレットテーブル番号
	u8 Margin;		//パレット変更間隔
	u8 Counter;
}SCENE3_THUNDER_DATA;


//コピーライト～ゲーフリロゴまでのデータ構造体
typedef struct SCENE1_WORK_tag
{
	u8 Seq;
	u8 SceneSeq;
	u8 InitOK;			//initシーケンス通過したか？
	u8 LoadOK;			//loadシーケンス通過したか？
	u16 Wait;
	u8 Alpha;
	u8 Counter;
	u8 BlendEnd;
	GF_BGL_INI *bgl;
	TCB_PTR	BlendTcb;
	OPD_K_G_MNG_PTR KiraGeneMngPtr;
	u8 *SkipOKPtr;
}SCENE1_WORK;

//タイトル～バトルまでのデータ構造体
typedef struct SCENE2_WORK_tag
{
	u8 Seq;
	u8 SceneSeq;
	u8 InitOK;				//initシーケンス通過したか？
	u8 LoadOK;				//loadシーケンス通過したか？
	u8 Load3DOK;			//load3Dシーケンスを通過したか？
	u8 Disp3DFlg;			//空撮フラグ
	u8 KiraMargin;
	u8 KiraMarginCore;
	int BG_ScrollMargin;	//スクロールセット間隔
	GF_BGL_INI *bgl;
	OPD_OBJ_PTR	ObjWorkPtr;
	OPD_KIRA_DATLST_PTR KiraListPtr;
	OPD_SSM_PTR OpSsmPtr;
	void *PalDataBuf[BTL_PAL_MAX];		//パレットデータ４つ分
	NNSG2dPaletteData *PalData[BTL_PAL_MAX];	//パレットデータ４つ分
	SCENE2_3D_DATA Data;
}SCENE2_WORK;

//テンガンザンシーンのデータ構造体
typedef struct SCENE3_WORK_tag
{
	u8 Seq;
	u8 SceneSeq;
	u8 InitOK;			//initシーケンス通過したか？
	u8 LoadOK;			//loadシーケンス通過したか？
//	u8 TenganAffMargin;	//テンガンザンスケール変更間隔
//	u8 LakeAffMargin;	//湖スケール変更間隔
	fx32 TenganSc;		//テンガンザンスケール
	fx32 LakeSc;		//湖スケール
	
	GF_BGL_INI *bgl;
	void *PalDataBuf;		//パレットデータ
	NNSG2dPaletteData *PalData;	//パレットデータ
	SCENE3_THUNDER_DATA ThunderData;
}SCENE3_WORK;

///	タイトル全体制御用ワーク構造体
typedef struct OPENING_DEMO_WORK_tag
{
	int	heapID;
	int FrameCounter;
	BOOL SkipFlg;

	GF_BGL_INI*		bgl;	// BGマネージャ
	GF_G3DMAN*		g3Dman;	// 3Dマネージャ

	u32 RandSeed;

	SCENE1_WORK		SceneWork1;
	SCENE2_WORK		SceneWork2;
	SCENE3_WORK		SceneWork3;

	u8 SkipOK;

}OPENING_DEMO_WORK;

extern const PROC_DATA TitleProcData;
extern void		Main_SetNextProc(FSOverlayID ov_id, const PROC_DATA * proc_data);
FS_EXTERN_OVERLAY( title );

static PROC_RESULT OpDemo_Init(PROC * proc, int * seq);
static PROC_RESULT OpDemo_Main(PROC * proc, int * seq);
static PROC_RESULT OpDemo_Exit(PROC * proc, int * seq);

static BOOL GemeFreakLogoScene(OPENING_DEMO_WORK * wk);
static BOOL Title_3D_BattleScene(OPENING_DEMO_WORK * wk);
static BOOL MtTenganScene(OPENING_DEMO_WORK * wk);

static void SetUp3D(void);
static void Scene_LoadPal(	NNSG2dPaletteData *inPalData, const u8 inDispMS,
							const u8 inPalNum, const u8 inStart, const u8 inDst);

//=================================================================================================
//
// ＰＲＯＣ定義テーブル
//
//=================================================================================================
const PROC_DATA OpDemoProcData = {
	OpDemo_Init,
	OpDemo_Main,
	OpDemo_Exit,
	NO_OVERLAY_ID
};

const int ModelArcTbl[OP_MAP_BLOCK_MAX] = {
	NARC_op_demo_titlemap05_20_nsbmd,
	NARC_op_demo_titlemap05_21_nsbmd,
	NARC_op_demo_titlemap06_20_nsbmd,
	NARC_op_demo_titlemap06_19_nsbmd,
	NARC_op_demo_titlemap06_18_nsbmd,
	NARC_op_demo_titlemap06_17_nsbmd, 
};

//カメラ設定
static const GF_CAMERA_PARAM CameraData = {
	0x29aec1,
	{
		-0x29fe,0,0
	},
	GF_CAMERA_PERSPECTIV,
	0x05c1,
	0	//dummy
};

//エッジマーキングテーブル
static const GXRgb gEdgeColor[8] = {
    GX_RGB(0, 0, 0),
    GX_RGB(4, 4, 4),
    GX_RGB(4, 4, 4),
    GX_RGB(4, 4, 4),
    GX_RGB(4, 4, 4),
    GX_RGB(4, 4, 4),
    GX_RGB(4, 4, 4),
    GX_RGB(4, 4, 4)
};

//ライトパラメータ
const VecFx32 LightVec[4] = {
	{-2043,-3548,110},
	{0,0,0},
	{0,0,4096},
	{0,0,4096},
};

const GXRgb LightColor[4] = {
	GX_RGB(24,24,18),
	GX_RGB(0,0,0),
	GX_RGB(2,2,12),
	GX_RGB(31,31,31),	
};

//----------------------------------
//ＶＲＡＭ設定
//----------------------------------
static void OpDemo_VramBankSet(void)
{
	GF_BGL_DISPVRAM vramSetTable = {
		GX_VRAM_BG_128_B,				// メイン2DエンジンのBG
		GX_VRAM_BGEXTPLTT_NONE,			// メイン2DエンジンのBG拡張パレット
		GX_VRAM_SUB_BG_128_C,			// サブ2DエンジンのBG
		GX_VRAM_SUB_BGEXTPLTT_NONE,	// サブ2DエンジンのBG拡張パレット
		GX_VRAM_OBJ_80_EF,				// メイン2DエンジンのOBJ
		GX_VRAM_OBJEXTPLTT_NONE,		// メイン2DエンジンのOBJ拡張パレット
		GX_VRAM_SUB_OBJ_16_I,			// サブ2DエンジンのOBJ
		GX_VRAM_SUB_OBJEXTPLTT_NONE,	// サブ2DエンジンのOBJ拡張パレット
		GX_VRAM_TEX_0_A,				// テクスチャイメージスロット
		GX_VRAM_TEXPLTT_0_G				// テクスチャパレットスロット
	};
	GF_Disp_SetBank( &vramSetTable );
}
//----------------------------------
//ＶＲＡＭ設定（タイトル～3Ｄ～バトル）
//----------------------------------
static void OpDemo_Scene2_VramBankSet(void)
{
	GF_BGL_DISPVRAM vramSetTable = {
		GX_VRAM_BG_128_B,				// メイン2DエンジンのBG
		GX_VRAM_BGEXTPLTT_NONE,			// メイン2DエンジンのBG拡張パレット
		GX_VRAM_SUB_BG_128_C,			// サブ2DエンジンのBG
		GX_VRAM_SUB_BGEXTPLTT_NONE,	// サブ2DエンジンのBG拡張パレット
		GX_VRAM_OBJ_32_FG,				// メイン2DエンジンのOBJ
		GX_VRAM_OBJEXTPLTT_NONE,		// メイン2DエンジンのOBJ拡張パレット
		GX_VRAM_SUB_OBJ_16_I,			// サブ2DエンジンのOBJ
		GX_VRAM_SUB_OBJEXTPLTT_NONE,	// サブ2DエンジンのOBJ拡張パレット
		GX_VRAM_TEX_0_A,				// テクスチャイメージスロット
		GX_VRAM_TEXPLTT_0123_E				// テクスチャパレットスロット
	};
	GF_Disp_SetBank( &vramSetTable );
}

//----------------------------------
//ＶＲＡＭ設定（テンガンザン）
//----------------------------------
static void OpDemo_Scene3_VramBankSet(void)
{
	GF_BGL_DISPVRAM vramSetTable = {
		GX_VRAM_BG_256_AB,				// メイン2DエンジンのBG
		GX_VRAM_BGEXTPLTT_NONE,			// メイン2DエンジンのBG拡張パレット
		GX_VRAM_SUB_BG_128_C,			// サブ2DエンジンのBG
		GX_VRAM_SUB_BGEXTPLTT_NONE,	// サブ2DエンジンのBG拡張パレット
		GX_VRAM_OBJ_NONE,				// メイン2DエンジンのOBJ
		GX_VRAM_OBJEXTPLTT_NONE,		// メイン2DエンジンのOBJ拡張パレット
		GX_VRAM_SUB_OBJ_NONE,			// サブ2DエンジンのOBJ
		GX_VRAM_SUB_OBJEXTPLTT_NONE,	// サブ2DエンジンのOBJ拡張パレット
		GX_VRAM_TEX_NONE,				// テクスチャイメージスロット
		GX_VRAM_TEXPLTT_NONE				// テクスチャパレットスロット
	};
	GF_Disp_SetBank( &vramSetTable );
}

//----------------------------------
//
//	２ＤＢＧ初期化＆終了
//
//----------------------------------
static void OpDemo2DBgSet( OPENING_DEMO_WORK* wk )
{
	//BGライブラリ用メモリ確保
	wk->bgl = GF_BGL_BglIniAlloc(wk->heapID);

	{	// BGシステム設定
		GF_BGL_SYS_HEADER BGsys_data = {
			GX_DISPMODE_GRAPHICS,GX_BGMODE_0,GX_BGMODE_0,GX_BG0_AS_2D
		};	
		GF_BGL_InitBG( &BGsys_data );
	}

	
	{	// コピーライト ＢＧ設定(メイン1)
		GF_BGL_BGCNT_HEADER CopyLight_Data = {
			0, 0, 0x800, 0,
			GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0x0000, GX_BG_CHARBASE_0x04000,
			GX_BG_EXTPLTT_01, 0, 0, 0, FALSE			//プライオリティ0
		};
		GF_BGL_BGControlSet( wk->bgl, COPY_LIGHT_FRAME, &CopyLight_Data, GF_BGL_MODE_TEXT );
	}

	{	// ゲーフリロゴ ＢＧ設定(メイン2)
		GF_BGL_BGCNT_HEADER GF_Logo_m_Data = {
			0, 0, 0x800, 0,
			GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0x0800, GX_BG_CHARBASE_0x08000,
			GX_BG_EXTPLTT_01, 1, 0, 0, FALSE			//プライオリティ1
		};
		GF_BGL_BGControlSet( wk->bgl, GAME_FREAK_LOGO_M_FRAME, &GF_Logo_m_Data, GF_BGL_MODE_TEXT );
	}

	{	// ベース背景 ＢＧ設定(メイン3)
		GF_BGL_BGCNT_HEADER GF_Back_m_Data = {
			0, 0, 0x800, 0,
			GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0x1000, GX_BG_CHARBASE_0x08000,
			GX_BG_EXTPLTT_01, 2, 0, 0, FALSE			//プライオリティ2
		};
		GF_BGL_BGControlSet( wk->bgl, BACK_BASE_M_FRAME, &GF_Back_m_Data, GF_BGL_MODE_TEXT );
	}

	{	// ゲーフリロゴ ＢＧ設定(サブ2)
		GF_BGL_BGCNT_HEADER GF_Logo_s_Data = {
			0, 0, 0x800, 0,
			GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0x0000, GX_BG_CHARBASE_0x04000,
			GX_BG_EXTPLTT_01, 1, 0, 0, FALSE			//プライオリティ1
		};
		GF_BGL_BGControlSet( wk->bgl, GAME_FREAK_LOGO_S_FRAME, &GF_Logo_s_Data, GF_BGL_MODE_TEXT );
	}

	{	// ベース背景 ＢＧ設定(サブ3)
		GF_BGL_BGCNT_HEADER GF_Back_s_Data = {
			0, 0, 0x800, 0,
			GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0x8000, GX_BG_CHARBASE_0x04000,
			GX_BG_EXTPLTT_01, 2, 0, 0, FALSE			//プライオリティ2
		};
		GF_BGL_BGControlSet( wk->bgl, BACK_BASE_S_FRAME, &GF_Back_s_Data, GF_BGL_MODE_TEXT );
	}

	GF_BGL_BackGroundColorSet( GF_BGL_FRAME0_M, 0x0000 );	//背景色初期化（メイン画面）
	GF_BGL_BackGroundColorSet( GF_BGL_FRAME0_S, 0x0000 );	//背景色初期化（サブ画面）
}

//----------------------------------
//
//	２ＤＢＧ初期化＆終了
//
//----------------------------------
static void OpDemo_Scene2_2DBgSet( OPENING_DEMO_WORK* wk )
{
	//BGライブラリ用メモリ確保
	wk->bgl = GF_BGL_BglIniAlloc(wk->heapID);

	{	// BGシステム設定
		GF_BGL_SYS_HEADER BGsys_data = {
			GX_DISPMODE_GRAPHICS,GX_BGMODE_0,GX_BGMODE_0,GX_BG0_AS_3D
		};	
		GF_BGL_InitBG( &BGsys_data );
	}

	//スクリーンベースオフセットを0x10000ずらす
	GX_SetBGScrOffset(GX_BGSCROFFSET_0x10000);

	{	// 256画面 ＢＧ設定(メイン3)
		GF_BGL_BGCNT_HEADER G256_Data = {
			0, 0, 0x2000, 0,
			GF_BGL_SCRSIZ_512x256, GX_BG_COLORMODE_256,
			GX_BG_SCRBASE_0x0000, GX_BG_CHARBASE_0x00000,
			GX_BG_EXTPLTT_01, 3, 0, 0, FALSE			//プライオリティ3
		};
		GF_BGL_BGControlSet( wk->bgl, G256_FRAME, &G256_Data, GF_BGL_MODE_TEXT );
	}

	{	// 街 ＢＧ設定(メイン1)
		GF_BGL_BGCNT_HEADER Town_Data = {
			0, 0, 0x800, 0,
			GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0x1000, GX_BG_CHARBASE_0x14000,		//街と空同じキャラ
			GX_BG_EXTPLTT_01, 1, 0, 0, FALSE			//プライオリティ1
		};
		GF_BGL_BGControlSet( wk->bgl, TOWN_FRAME, &Town_Data, GF_BGL_MODE_TEXT );
	}

	{	// 空 ＢＧ設定(メイン2)
		GF_BGL_BGCNT_HEADER Sky_Data = {
			0, 0, 0x800, 0,
			GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0x1800, GX_BG_CHARBASE_0x14000,		//街と空同じキャラ
			GX_BG_EXTPLTT_01, 2, 0, 0, FALSE			//プライオリティ2
		};
		GF_BGL_BGControlSet( wk->bgl, SKY_FRAME, &Sky_Data, GF_BGL_MODE_TEXT );
	}

	{	// ゲーフリロゴ ＢＧ設定(サブ0)
		GF_BGL_BGCNT_HEADER GF_Logo_Data = {
			0, 0, 0x1000, 0,
			GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_256,
			GX_BG_SCRBASE_0x0000, GX_BG_CHARBASE_0x04000,
			GX_BG_EXTPLTT_01, 0, 0, 0, FALSE			//プライオリティ0
		};
		GF_BGL_BGControlSet( wk->bgl, WB_TITLE_FRAME, &GF_Logo_Data, GF_BGL_MODE_TEXT );
	}

///	GF_BGL_BackGroundColorSet( GF_BGL_FRAME0_M, 0x0000 );	//背景色初期化（メイン画面）
	GF_BGL_BackGroundColorSet( GF_BGL_FRAME0_S, 0x0000 );	//背景色初期化（サブ画面）
}

//----------------------------------
//
//	２ＤＢＧ初期化
//
//----------------------------------
static void OpDemo_Scene3_2DBgSet( OPENING_DEMO_WORK* wk )
{
	//BGライブラリ用メモリ確保
	wk->bgl = GF_BGL_BglIniAlloc(wk->heapID);

	{	// BGシステム設定
		GF_BGL_SYS_HEADER BGsys_data = {
			GX_DISPMODE_GRAPHICS,GX_BGMODE_2,GX_BGMODE_0,GX_BG0_AS_2D
		};	
		GF_BGL_InitBG( &BGsys_data );
	}
	
	//スクリーンベースオフセットを0x10000ずらす
	GX_SetBGScrOffset(GX_BGSCROFFSET_0x10000);	
	
	{	// テンガンザン雲 ＢＧ設定(メイン1)
		GF_BGL_BGCNT_HEADER Cloud_Data = {
			0, 0, 0x800, 0,
			GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xc000, GX_BG_CHARBASE_0x00000,
			GX_BG_EXTPLTT_01, 3, 0, 0, FALSE			//プライオリティ3
		};
		GF_BGL_BGControlSet( wk->bgl, MT_CLOUD_FRAME, &Cloud_Data, GF_BGL_MODE_TEXT );
	}

	{	// テンガンザン山 ＢＧ設定(メイン2)
		GF_BGL_BGCNT_HEADER Tengan_Data = {
			0, 0, 0x1000, 0,
			GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_256,
			GX_BG_SCRBASE_0xc800, GX_BG_CHARBASE_0x04000,
			GX_BG_EXTPLTT_01, 1, 0, 0, FALSE			//プライオリティ1
		};
		GF_BGL_BGControlSet( wk->bgl, MT_TENGAN_FRAME, &Tengan_Data, GF_BGL_MODE_AFFINE );
	}

	{	// テンガンザン湖 ＢＧ設定(メイン3)
		GF_BGL_BGCNT_HEADER Lake_Data = {
			0, 0, 0x4000, 0,
			GF_BGL_SCRSIZ_512x512, GX_BG_COLORMODE_256,
			GX_BG_SCRBASE_0xd800, GX_BG_CHARBASE_0x08000,
			GX_BG_EXTPLTT_01, 0, 0, 0, FALSE			//プライオリティ0
		};
		GF_BGL_BGControlSet( wk->bgl, MT_LAKE_FRAME, &Lake_Data, GF_BGL_MODE_AFFINE );
	}
	
	{	// テンガンザン雷 ＢＧ設定(メイン0)
		GF_BGL_BGCNT_HEADER Thunder_Data = {
			0, 0, 0x800, 0,
			GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xb800, GX_BG_CHARBASE_0x0c000,
			GX_BG_EXTPLTT_01, 2, 0, 0, FALSE			//プライオリティ2
		};
		GF_BGL_BGControlSet( wk->bgl, MT_THUNDER_FRAME, &Thunder_Data, GF_BGL_MODE_TEXT );
	}

	{	// テンガンザン雲 ＢＧ設定(サブ1)
		GF_BGL_BGCNT_HEADER Cloud_SubData = {
			0, 0, 0x800, 0,
			GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0x0000, GX_BG_CHARBASE_0x04000,
			GX_BG_EXTPLTT_01, 0, 0, 0, FALSE			//プライオリティ0
		};
		GF_BGL_BGControlSet( wk->bgl, MT_CLOUD_SUB_FRAME, &Cloud_SubData, GF_BGL_MODE_TEXT );
	}

	GF_BGL_BackGroundColorSet( GF_BGL_FRAME0_S, 0x0000 );	//背景色初期化（サブ画面）
}

//----------------------------------
//
//	３Ｄ初期化＆終了
//
//----------------------------------
static void OpDemo3D_Init( OPENING_DEMO_WORK* wk )
{
	NNSGfdTexKey texKey;
	NNSGfdPlttKey plttKey;
	u32 tex_addrs, pltt_addrs;
	
	wk->g3Dman = GF_G3DMAN_Init(wk->heapID, 
			GF_G3DMAN_LNK, GF_G3DTEX_128K, GF_G3DMAN_LNK, GF_G3DPLT_64K, SetUp3D );

	
	// ポケモンデータ転送領域のVramを確保＆転送アドレスとサイズを設定	
	texKey = NNS_GfdAllocTexVram(0x2000*4, FALSE, 0);
	plttKey = NNS_GfdAllocPlttVram(0x20*4, FALSE, NNS_GFD_ALLOC_FROM_LOW);

	tex_addrs = NNS_GfdGetTexKeyAddr(texKey);
	pltt_addrs = NNS_GfdGetPlttKeyAddr(plttKey);
	OS_TPrintf("オープニングポケモン用に確保したテクスチャVramの先頭アドレス＝%d\n", tex_addrs);
	OS_TPrintf("オープニングポケモン用に確保したパレットVramの先頭アドレス＝%d\n", pltt_addrs);
}

static void SetUp3D(void)
{
	// ３Ｄ使用面の設定(表示＆プライオリティー)
    G2_SetBG0Priority(0);

	// 各種描画モードの設定(シェード＆アンチエイリアス＆半透明)
    G3X_SetShading( GX_SHADING_TOON );
    G3X_AntiAlias( TRUE );
	G3X_AlphaTest( FALSE, 0 );	// アルファテスト　　オフ
	G3X_AlphaBlend( TRUE );		// アルファブレンド　オン
	G3X_EdgeMarking( TRUE );
	G3X_SetEdgeColorTable(gEdgeColor);
	G3X_SetFog( FALSE, GX_FOGBLEND_COLOR_ALPHA, GX_FOGSLOPE_0x8000, 0 );

	// クリアカラーの設定
    G3X_SetClearColor(GX_RGB(0,0,0),0,0x7fff,63,FALSE);	//color,alpha,depth,polygonID,fog

	// ビューポートの設定
    G3_ViewPort(0, 0, 255, 191);
}

//----------------------------------
//ＶＢＬＡＮＫ関数
//----------------------------------
static void Scene1_VBlankFunc(void* work)
{
	
	OPENING_DEMO_WORK* wk = work;
//	GF_BGL_VBlankFunc(wk->bgl);

	// レンダラ共有OAMマネージャVram転送
	REND_OAMTrans();

}

//----------------------------------
//ＶＢＬＡＮＫ関数
//----------------------------------
static void Scene2_VBlankFunc(void* work)
{
	
	OPENING_DEMO_WORK* wk = work;
//	GF_BGL_VBlankFunc(wk->bgl);

	// レンダラ共有OAMマネージャVram転送
	REND_OAMTrans();

	OPD_Poke_VBlank(wk->SceneWork2.OpSsmPtr);

}

//--------------------------------------------------------------------------------------------
/**
 * ウィンドウ設定
 *
 * @param	none
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void Scene2_SetWindow(void)
{
	GX_SetVisibleWnd( GX_WNDMASK_W0 );
	G2_SetWnd0InsidePlane(	GX_WND_PLANEMASK_BG0|
							GX_WND_PLANEMASK_BG1|
							GX_WND_PLANEMASK_BG2|
							GX_WND_PLANEMASK_BG3|
							GX_WND_PLANEMASK_OBJ, 1 );
	G2_SetWndOutsidePlane( GX_WND_PLANEMASK_BG0|GX_WND_PLANEMASK_OBJ, 1 );
	G2_SetWnd0Position( 0, 32, 255, 159 );
}

//----------------------------------
//ＰＲＯＣ初期化
//----------------------------------
static PROC_RESULT OpDemo_Init(PROC * proc, int * seq)
{
	OPENING_DEMO_WORK * wk;
	int	heapID;

	heapID = HEAPID_OP_DEMO;

	BrightnessChgInit();
	
	//マスター輝度をあげておく
	WIPE_SetBrightness( WIPE_DISP_MAIN,WIPE_FADE_WHITE );
	WIPE_SetBrightness( WIPE_DISP_SUB,WIPE_FADE_WHITE );
	
	sys_VBlankFuncChange( NULL, NULL );	// VBlankセット
	sys_HBlankIntrSet( NULL,NULL );		// HBlankセット

	GF_Disp_GX_VisibleControlInit();
	GF_Disp_GXS_VisibleControlInit();
///	GX_SetVisiblePlane(0);
///	GXS_SetVisiblePlane(0);

	sys_KeyRepeatSpeedSet(4,8);
	sys_CreateHeap( HEAPID_BASE_APP, heapID, 0x60000 );

	wk = PROC_AllocWork(proc,sizeof(OPENING_DEMO_WORK),heapID);
	memset(wk,0,sizeof(OPENING_DEMO_WORK));

	wk->heapID = heapID;

	wk->SkipFlg = FALSE;

#ifdef COPYRIGHT_SKIP
	wk->SkipOK = 1;
#else
	//始めはスキップ不可
	wk->SkipOK = 0;
#endif
	//３Ｄ描画スイッチ
	sys.disp3DSW = DISP_3D_TO_MAIN;
	GF_Disp_DispSelect();

	//乱数の種退避
	wk->RandSeed = gf_get_seed();
	
	//乱数初期化
	gf_srand(0);

	return	PROC_RES_FINISH;
}

//----------------------------------
//ＰＲＯＣメイン
//----------------------------------
static PROC_RESULT OpDemo_Main(PROC * proc, int * seq)
{
	OPENING_DEMO_WORK * wk = PROC_GetWork( proc );
#if 0	
	if (sys.trg & PAD_BUTTON_X){
		OS_Printf("frame:%d\n",wk->FrameCounter);
		GF_ASSERT(0);
	}
#endif
	if ( (wk->SkipOK)&&( (sys.trg & PAD_BUTTON_A)||(sys.trg & PAD_BUTTON_START) ) )
	{
		wk->SkipFlg = TRUE;
		sys.DS_Boot_Flag = FALSE;	//ブートフラグセット
		WIPE_SetBrightness( WIPE_DISP_MAIN,WIPE_FADE_WHITE );
		WIPE_SetBrightness( WIPE_DISP_SUB,WIPE_FADE_WHITE );
	}

	switch(*seq){
	case 0:
		wk->SceneWork1.SkipOKPtr = &wk->SkipOK;
		(*seq)++;
		break;
	case 1:	
		if ( GemeFreakLogoScene(wk) ){
			//次のシーケンス
			(*seq)++;
		}
		break;
	case 2:
		if ( Title_3D_BattleScene(wk) ){
			//次のシーケンス
			(*seq)++;
		}
		break;
	case 3:
		if ( MtTenganScene(wk) ){
			//次のシーケンス
			(*seq)++;
		}
		break;
	case 4:
		if (wk->FrameCounter >= FM_END){
			return	PROC_RES_FINISH;
		}
		break;
	default:
		GF_ASSERT(0);
		break;
	}

	if (wk->SkipFlg){
		OS_Printf("スキップにより、メインプロセス終了\n");
		return	PROC_RES_FINISH;
	}

	wk->FrameCounter++;
	return	PROC_RES_CONTINUE;
}

static PROC_RESULT OpDemo_Exit(PROC * proc, int * seq)
{
	OPENING_DEMO_WORK * wk = PROC_GetWork( proc );
	//ワイプの強制終了
	WIPE_SYS_ExeEnd();

	//乱数の種復帰
	gf_srand(wk->RandSeed);
	
	PROC_FreeWork( proc );				// ワーク開放
	sys_DeleteHeap( HEAPID_OP_DEMO );
	
	Main_SetNextProc( FS_OVERLAY_ID(title), &TitleProcData);
	
	return	PROC_RES_FINISH;
}

static void Scene1_Init(OPENING_DEMO_WORK * wk);
static void Scene1_Load(SCENE1_WORK *scene_wk);
static BOOL Scene1_Main(SCENE1_WORK *scene_wk, const int inCounter);
static void Scene1_End(OPENING_DEMO_WORK * wk);
static void TCB_BlendInCopyLight( TCB_PTR tcb, void* work );
static void TCB_BlendOutCopyLight( TCB_PTR tcb, void* work );
static void TCB_BlendInGFLogoM( TCB_PTR tcb, void* work );
static void TCB_BlendInGFLogoS( TCB_PTR tcb, void* work );

//コピーライト・ゲーフリロゴの表示シーン
static BOOL GemeFreakLogoScene(OPENING_DEMO_WORK * wk)
{
	u8 *seq = &(wk->SceneWork1.Seq);
	
	if (wk->SkipFlg){
		(*seq) = 3;		//スキップ実行
	}
	
	switch(*seq){
	case 0:		//初期化
		Scene1_Init(wk);
		(*seq)++;
		break;
	case 1:			//グラフィックロード
		Scene1_Load(&wk->SceneWork1);
		(*seq)++;
		break;
	case 2:			//メイン
		if ( Scene1_Main( &wk->SceneWork1, wk->FrameCounter ) ){
			(*seq)++;
		}
		break;
	case 3:			//終了
		Scene1_End(wk);
		
		return TRUE;
	}
	return FALSE;
}

static void Scene1_Init(OPENING_DEMO_WORK * wk)
{
	OpDemo_VramBankSet();
	OpDemo2DBgSet(wk);
	wk->SceneWork1.bgl = wk->bgl;
	wk->SceneWork1.KiraGeneMngPtr = OPDKira_AllocGeneMng();

	sys_VBlankFuncChange(Scene1_VBlankFunc,(void*)wk);

	wk->SceneWork1.InitOK = 1;	//init通過
}

static void Scene1_Load(SCENE1_WORK *scene_wk)
{
	//--ゲーフリロゴデータロード
	//キャラ(１ファイルになってるので二面に送る。分けてもらったほうがいいかも)
	ArcUtil_BgCharSet(ARC_OP_DEMO, NARC_op_demo_op_demoBG0_logo_NCGR,
						scene_wk->bgl, GAME_FREAK_LOGO_M_FRAME, 0, 0, FALSE, HEAPID_OP_DEMO);
	ArcUtil_BgCharSet(ARC_OP_DEMO, NARC_op_demo_op_demoBG0_logo_NCGR,
						scene_wk->bgl, GAME_FREAK_LOGO_S_FRAME, 0, 0, FALSE, HEAPID_OP_DEMO);	
	//スクリーン
	ArcUtil_ScrnSet(ARC_OP_DEMO, NARC_op_demo_op_demoBG0_logo_m_NSCR,
						scene_wk->bgl, GAME_FREAK_LOGO_M_FRAME, 0, 0, FALSE, HEAPID_OP_DEMO);
	ArcUtil_ScrnSet(ARC_OP_DEMO, NARC_op_demo_op_demoBG0_logo_s_NSCR,
						scene_wk->bgl, GAME_FREAK_LOGO_S_FRAME, 0, 0, FALSE, HEAPID_OP_DEMO);
	//パレット
	ArcUtil_PalSet( ARC_OP_DEMO, NARC_op_demo_op_demoBG0_NCLR,
						PALTYPE_MAIN_BG, 0, 0, HEAPID_OP_DEMO );
	ArcUtil_PalSet( ARC_OP_DEMO, NARC_op_demo_op_demoBG0_NCLR,
						PALTYPE_SUB_BG, 0, 0, HEAPID_OP_DEMO );
	
	//--コピーライトデータロード
	//キャラ
	ArcUtil_BgCharSet(ARC_OP_DEMO, NARC_op_demo_cp_light_NCGR,
						scene_wk->bgl, COPY_LIGHT_FRAME, 0, 0, FALSE, HEAPID_OP_DEMO);
	//スクリーン
	ArcUtil_ScrnSet(ARC_OP_DEMO, NARC_op_demo_cp_light_NSCR,
						scene_wk->bgl, COPY_LIGHT_FRAME, 0, 0, FALSE, HEAPID_OP_DEMO);
	//パレット
	ArcUtil_PalSet( ARC_OP_DEMO, NARC_op_demo_cp_light_NCLR,
						PALTYPE_MAIN_BG, 0, PAL_ONE_SIZE*16*1, HEAPID_OP_DEMO );	//０番に１６色ロード
	
	//--ベース背景ロード
	//スクリーン
	ArcUtil_ScrnSet(ARC_OP_DEMO, NARC_op_demo_op_demoBG0_logo_back_NSCR,
						scene_wk->bgl, BACK_BASE_M_FRAME, 0, 0, FALSE, HEAPID_OP_DEMO);
	ArcUtil_ScrnSet(ARC_OP_DEMO, NARC_op_demo_op_demoBG0_logo_back_NSCR,
						scene_wk->bgl, BACK_BASE_S_FRAME, 0, 0, FALSE, HEAPID_OP_DEMO);


	//--初期ＢＧ設定
	//BG0・上下画面ゲーフリロゴ非表示
	GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG2, VISIBLE_OFF );
	GF_Disp_GXS_VisibleControl( GX_PLANEMASK_BG2, VISIBLE_OFF );
	//ベース背景とコピーライトをブレンド
	G2_SetBlendAlpha( BLD_MASK_COPY_LIGHT, BLD_MASK_BACK_BASE_M, 0, 16);

	OS_WaitIrq(TRUE, OS_IE_V_BLANK); 	// Ｖブランク待ち
	//マスター輝度を戻す
	WIPE_ResetBrightness( WIPE_DISP_MAIN );
	WIPE_ResetBrightness( WIPE_DISP_SUB );

	GF_Disp_DispOn();
}

static BOOL Scene1_Main(SCENE1_WORK *scene_wk, const int inCounter)
{
	u8 *seq = &(scene_wk->SceneSeq);

	KiraGenerateMain(scene_wk->KiraGeneMngPtr, inCounter);
	
	switch(*seq){
	case 0:	//コピーライトブレンドイン
		scene_wk->Counter = 0;
		scene_wk->Alpha = 0;
		scene_wk->BlendEnd = 0;
		scene_wk->BlendTcb = TCB_Add( TCB_BlendInCopyLight, scene_wk, 0 );
		//ＢＧＭ開始
		Snd_DataSetByScene( SND_SCENE_TITLE, SEQ_TITLE00, 1 );
		(*seq)++;
		break;
	case 1:	//よきところでコピーライトブレンドアウト
		if ( (scene_wk->BlendEnd)&&(inCounter >= FM_COPY_LIGHT_OUT) ){
			scene_wk->Counter = 0;
			scene_wk->Alpha = 16;
			scene_wk->BlendEnd = 0;
			scene_wk->BlendTcb = TCB_Add( TCB_BlendOutCopyLight, scene_wk, 0 );
			(*seq)++;
		}
		break;
	case 2:	//ゲーフリロゴブレンドイン
		if ( (scene_wk->BlendEnd)&&(inCounter>=FM_FG_LOGO_IN) ){
			//コピーライト面非表示
			GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG1, VISIBLE_OFF );
			//ブレンド初期設定
			G2_SetBlendAlpha( BLD_MASK_GF_LOGO_M, BLD_MASK_BACK_BASE_M, 0, 16);
			G2S_SetBlendAlpha( BLD_MASK_GF_LOGO_S, BLD_MASK_BACK_BASE_S, 0, 16);
			//ゲーフリロゴ面表示
			GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG2, VISIBLE_ON );
			GF_Disp_GXS_VisibleControl( GX_PLANEMASK_BG2, VISIBLE_ON );
			
			scene_wk->Counter = 0;
			scene_wk->Alpha = 0;
			scene_wk->BlendEnd = 0;
			scene_wk->BlendTcb = TCB_Add( TCB_BlendInGFLogoM, scene_wk, 0 );
			(*seq)++;
		}
		break;
	case 3:	//下場面ブレンドイン
		if ( (scene_wk->BlendEnd) ){
			scene_wk->Counter = 0;
			scene_wk->Alpha = 0;
			scene_wk->BlendEnd = 0;
			scene_wk->BlendTcb = TCB_Add( TCB_BlendInGFLogoS, scene_wk, 0 );
			(*seq)++;
		}
		break;
	case 4:	//下画面上画面の順で全部ブラックアウト
		if ( (scene_wk->BlendEnd)&&(inCounter>=FM_GF_LOGO_OUT) ){
			//ワイプスタート	ホワイトイン
			WIPE_SYS_Start(	WIPE_PATTERN_FSAM, WIPE_TYPE_FADEOUT,
							WIPE_TYPE_FADEOUT,0x0000,OPDEMO_BRIGHTNESS_SYNC,1,HEAPID_OP_DEMO );
			(*seq)++;
		}
		break;
	case 5:
		if ( WIPE_SYS_EndCheck() ){
			return TRUE;
		}
	}
	return FALSE;
}

static void Scene1_End(OPENING_DEMO_WORK * wk)
{
	sys_VBlankFuncChange( NULL, NULL );	// VBlankセット
	
	if (wk->SceneWork1.InitOK){
		//ジェネレーター解放
		OPDKira_FreeGeneMng(wk->SceneWork1.KiraGeneMngPtr);
		//ＢＧＬ解放
		GF_BGL_BGControlExit( wk->bgl, COPY_LIGHT_FRAME );
		GF_BGL_BGControlExit( wk->bgl, GAME_FREAK_LOGO_M_FRAME );
		GF_BGL_BGControlExit( wk->bgl, GAME_FREAK_LOGO_S_FRAME );
		GF_BGL_BGControlExit( wk->bgl, BACK_BASE_M_FRAME );
		GF_BGL_BGControlExit( wk->bgl, BACK_BASE_S_FRAME );
		sys_FreeMemoryEz( wk->bgl );
		wk->SceneWork1.InitOK = 0;
	}

	//タスクが動いているならば終了
	if (wk->SceneWork1.BlendTcb != NULL){
		GF_ASSERT(wk->SkipFlg);
		OS_Printf("スキップにより、TCBを外から解放しました\n");
		TCB_Delete(wk->SceneWork1.BlendTcb);
		wk->SceneWork1.BlendTcb = NULL;
	}
}

//コピーライドブレンドインＴＣＢ
static void TCB_BlendInCopyLight( TCB_PTR tcb, void* work )
{
	SCENE1_WORK *s_work = work;

	s_work->Counter++;
	if (s_work->Counter >= COPY_LIGHT_BLD_IN_COUNT_MAX){
		s_work->Counter = 0;
		s_work->Alpha++;
	}

	if (s_work->Alpha >= 16){
		TCB_Delete(tcb);
		s_work->BlendTcb = NULL;
		s_work->BlendEnd = 1;
	}

	G2_SetBlendAlpha( BLD_MASK_COPY_LIGHT, BLD_MASK_BACK_BASE_M, s_work->Alpha, 16);
}

//コピーライドブレンドアウトＴＣＢ
static void TCB_BlendOutCopyLight( TCB_PTR tcb, void* work )
{
	SCENE1_WORK *s_work = work;

	s_work->Counter++;
	if (s_work->Counter >= COPY_LIGHT_BLD_COUNT_MAX){
		s_work->Counter = 0;
		s_work->Alpha--;
	}

	if (s_work->Alpha == 0){
		TCB_Delete(tcb);
		s_work->BlendTcb = NULL;
		s_work->BlendEnd = 1;
		*(s_work->SkipOKPtr) = 1;	//スキップ許可
	}

	G2_SetBlendAlpha( BLD_MASK_COPY_LIGHT, BLD_MASK_BACK_BASE_M, s_work->Alpha, 16);

}

//メイン画面ＧＦロゴブレンドインＴＣＢ
static void TCB_BlendInGFLogoM( TCB_PTR tcb, void* work )
{
	SCENE1_WORK *s_work = work;

	s_work->Counter++;
	if (s_work->Counter >= COPY_LIGHT_BLD_COUNT_MAX){
		s_work->Counter = 0;
		s_work->Alpha++;
	}

	if (s_work->Alpha >= 16){
		TCB_Delete(tcb);
		s_work->BlendTcb = NULL;
		s_work->BlendEnd = 1;
	}

	G2_SetBlendAlpha( BLD_MASK_GF_LOGO_M, BLD_MASK_BACK_BASE_M, s_work->Alpha, 16);
}

//サブ画面ＧＦロゴブレンドインＴＣＢ
static void TCB_BlendInGFLogoS( TCB_PTR tcb, void* work )
{
	SCENE1_WORK *s_work = work;

	s_work->Counter++;
	if (s_work->Counter >= COPY_LIGHT_BLD_COUNT_MAX){
		s_work->Counter = 0;
		s_work->Alpha++;
	}

	if (s_work->Alpha >= 16){
		TCB_Delete(tcb);
		s_work->BlendTcb = NULL;
		s_work->BlendEnd = 1;
	}

	G2S_SetBlendAlpha( BLD_MASK_GF_LOGO_S, BLD_MASK_BACK_BASE_S, s_work->Alpha, 16);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//

static void Scene2_Init(OPENING_DEMO_WORK * wk);
static void Scene2_Load(SCENE2_WORK *scene_wk);
static void Scene2_Load3D(SCENE2_WORK *scene_wk);
static void Scene2_Disp3D(SCENE2_WORK *scene_wk);
static BOOL Scene2_Main(SCENE2_WORK *scene_wk, const int inCounter);
static void Scene2_ScrollTown(SCENE2_WORK *scene_wk);
static void Scene2_ScrollSky(SCENE2_WORK *scene_wk);
static void Scene2_ScrollBattle(SCENE2_WORK *scene_wk);
static void Scene2_CameraMoveMain(SCENE2_WORK *scene_wk, const int inCounter);
static void Scene2_End(OPENING_DEMO_WORK * wk);

//タイトル表示～3Ｄ～バトルのシーン
static BOOL Title_3D_BattleScene(OPENING_DEMO_WORK * wk)
{
	u8 *seq = &(wk->SceneWork2.Seq);

	if (wk->SkipFlg){
		(*seq) = 4;		//スキップ実行
	}
	
	switch(*seq){
	case 0:		//初期化
		Scene2_Init(wk);
		(*seq)++;
		break;
	case 1:			//グラフィックロード
		Scene2_Load(&wk->SceneWork2);
		(*seq)++;
		break;
	case 2:
		Scene2_Load3D(&wk->SceneWork2);
		wk->SceneWork2.Disp3DFlg = 1;	//空撮フラグオン
		(*seq)++;
		break;
	case 3:			//メイン
		if ( Scene2_Main( &wk->SceneWork2, wk->FrameCounter ) ){
			(*seq)++;
		}
		OPD_Obj_DrawActor( wk->SceneWork2.ObjWorkPtr );
		if (wk->SceneWork2.Disp3DFlg){
			Scene2_Disp3D(&wk->SceneWork2);
		}else{
			OPD_Poke_Main( wk->SceneWork2.OpSsmPtr );
		}
		break;
	case 4:			//終了
		Scene2_End(wk);
		return TRUE;
	}
	return FALSE;
}

static void Scene2_Init(OPENING_DEMO_WORK * wk)
{
	u8 i;
	int obj_work_size;
	int ssm_size;
	OpDemo_Scene2_VramBankSet();
	OpDemo_Scene2_2DBgSet(wk);
	OpDemo3D_Init(wk);

	obj_work_size = OPD_Obj_GetWorkSize();
	ssm_size = OPD_Poke_GetSSMSize();
	
	wk->SceneWork2.ObjWorkPtr = sys_AllocMemory(HEAPID_OP_DEMO, obj_work_size);
	wk->SceneWork2.KiraListPtr = OPDKira_CreateList(SCENE2_KIRA_MAX);
	wk->SceneWork2.OpSsmPtr = sys_AllocMemory(HEAPID_OP_DEMO, ssm_size);
	memset(wk->SceneWork2.ObjWorkPtr, 0, obj_work_size);
	memset(wk->SceneWork2.OpSsmPtr, 0, ssm_size);

	wk->SceneWork2.KiraMarginCore = SCENE2_KIRA_MARGIN1;
	
	OPD_Poke_Init(wk->SceneWork2.OpSsmPtr);

	wk->SceneWork2.bgl = wk->bgl;

	//３Ｄ描画スイッチ	下をメインにする
	sys.disp3DSW = DISP_3D_TO_SUB;
	GF_Disp_DispSelect();

	for(i=0;i<4;i++){
		//ライトセット
		NNS_G3dGlbLightVector(i,
							LightVec[i].x,
							LightVec[i].y,
							LightVec[i].z);
		NNS_G3dGlbLightColor(i, LightColor[i]);
	}

	//グローバルステート書き換え
	NNS_G3dGlbMaterialColorDiffAmb(
				GX_RGB(16,16,16),
				GX_RGB(10,12,12),
				FALSE);
	
	NNS_G3dGlbMaterialColorSpecEmi(
				GX_RGB(18,18,18),
				GX_RGB(14,14,14),
				FALSE);
	
	// ポリゴンアトリビュート
	NNS_G3dGlbPolygonAttr(
				13,		//<ライト1以外有効（1101）
				GX_POLYGONMODE_MODULATE,
				GX_CULL_BACK,
				0,
				31,
				GX_POLYGON_ATTR_MISC_FOG);
	
	sys_VBlankFuncChange(Scene2_VBlankFunc,(void*)wk);

	//タイトルロゴの輝度を上げておく
	SetBrightness( BRIGHTNESS_WHITE, GX_BLEND_PLANEMASK_BG0, MASK_SUB_DISPLAY );
	
	wk->SceneWork2.InitOK = 1;		//init通過
}

static void Scene2_End(OPENING_DEMO_WORK * wk)
{	
	u8 i;

	//ウィンドウオフ
	GX_SetVisibleWnd( GX_WNDMASK_NONE );

	if (wk->SceneWork2.Load3DOK){
		//カメラ削除
		GFC_PurgeCamera();
		GFC_FreeCamera(wk->SceneWork2.Data.CameraPtr);
		//モデリングデータ削除
		for (i=0;i<OP_MAP_BLOCK_MAX;i++){
			sys_FreeMemoryEz(wk->SceneWork2.Data.Block[i].ResFile);
		}
		//テクスチャ削除
		sys_FreeMemoryEz(wk->SceneWork2.Data.TexFile);
		wk->SceneWork2.Load3DOK = 0;
	}

	if (wk->SceneWork2.LoadOK){
		//アクター関連解放
		OPD_Obj_EndCellActor( wk->SceneWork2.ObjWorkPtr );
		//パレット解放
		for(i=0;i<BTL_PAL_MAX;i++){
			sys_FreeMemoryEz(wk->SceneWork2.PalDataBuf[i]);
		}
		wk->SceneWork2.LoadOK = 0;
	}

	if (wk->SceneWork2.InitOK){
		//キラエフェクト解放
		if (wk->SceneWork2.KiraListPtr != NULL){
			OPDKira_FreeList(wk->SceneWork2.KiraListPtr);
			wk->SceneWork2.KiraListPtr = NULL;
		}
		if (wk->SceneWork2.ObjWorkPtr != NULL){
			sys_FreeMemoryEz(wk->SceneWork2.ObjWorkPtr);
			wk->SceneWork2.ObjWorkPtr = NULL;
		}
		if (wk->SceneWork2.OpSsmPtr != NULL){
			//スプライト・パーティクル解放
			OPD_Poke_End(wk->SceneWork2.OpSsmPtr);
			sys_FreeMemoryEz(wk->SceneWork2.OpSsmPtr);
			wk->SceneWork2.OpSsmPtr = NULL;
		}
	
		//bgl解放
		GF_BGL_BGControlExit( wk->bgl, G256_FRAME );
		GF_BGL_BGControlExit( wk->bgl, TOWN_FRAME );
		GF_BGL_BGControlExit( wk->bgl, SKY_FRAME );
		GF_BGL_BGControlExit( wk->bgl, WB_TITLE_FRAME );
		sys_FreeMemoryEz( wk->bgl );

		//3D解放
		GF_G3D_Exit( wk->g3Dman );
		wk->SceneWork2.InitOK = 0;
	}

	sys_VBlankFuncChange( NULL, NULL );	// VBlankセット	
}

static void Scene2_Load(SCENE2_WORK *scene_wk)
{
	u8 i;
	ARCHANDLE* pal_handle;

	const int pal_arc_idx[BTL_PAL_MAX] = {
		NARC_op_demo_op_demoBG2_btl1_NCLR,
		NARC_op_demo_op_demoBG2_btl2_NCLR,
		NARC_op_demo_op_demoBG2_btl3_NCLR,
		NARC_op_demo_op_demoBG2_btl4_NCLR
	};
	
	//パレットアーカイブハンドルオープン
	pal_handle  = ArchiveDataHandleOpen( ARC_OP_DEMO, HEAPID_OP_DEMO);

	for (i=0;i<BTL_PAL_MAX;i++){
		scene_wk->PalDataBuf[i] = ArchiveDataLoadAllocByHandle( pal_handle, pal_arc_idx[i], HEAPID_OP_DEMO );
		if( scene_wk->PalDataBuf[i] != NULL )
		{
			if( NNS_G2dGetUnpackedPaletteData( scene_wk->PalDataBuf[i], &scene_wk->PalData[i] ) == FALSE ){
				sys_FreeMemoryEz( scene_wk->PalData[i] );
				GF_ASSERT(0);
			}
		}else{
			GF_ASSERT(0);
		}
	}
	
	//ハンドルクローズ
	ArchiveDataHandleClose( pal_handle );

	//--256バトル背面データロード
	//キャラ
	ArcUtil_BgCharSet(ARC_OP_DEMO, NARC_op_demo_op_demoBG2_btl_NCGR,
						scene_wk->bgl, G256_FRAME, 0, 0, FALSE, HEAPID_OP_DEMO);
	//スクリーン
	ArcUtil_ScrnSet(ARC_OP_DEMO, NARC_op_demo_op_demoBG2_btl_NSCR,
						scene_wk->bgl, G256_FRAME, 0, 0, FALSE, HEAPID_OP_DEMO);
	//パレット
	Scene_LoadPal(scene_wk->PalData[0], DISP_MAIN, 10, 0, 0);		//10本ロード

	//--256タイトルデータロード
	{
		int cgxID,palID,scrID;
#if 0		
		if( CasetteVersion == VERSION_DIAMOND ){
			cgxID = NARC_op_demo_d_logo01_NCGR;
			palID = NARC_op_demo_d_logo01_NCLR;
			scrID = NARC_op_demo_d_logo01_NSCR;
		} else {
			cgxID = NARC_op_demo_P_logo01_NCGR;
			palID = NARC_op_demo_P_logo01_NCLR;
			scrID = NARC_op_demo_p_logo01_NSCR;
		}
#endif
		cgxID = NARC_op_demo_g_logo2_NCGR;
		palID = NARC_op_demo_g_logo2_NCLR;
		scrID = NARC_op_demo_g_logo_NSCR;
		
		//キャラ
		ArcUtil_BgCharSet(ARC_OP_DEMO, cgxID,
							scene_wk->bgl, WB_TITLE_FRAME, 0, 0, FALSE, HEAPID_OP_DEMO);
		//スクリーン
		ArcUtil_ScrnSet(ARC_OP_DEMO, scrID,
							scene_wk->bgl, WB_TITLE_FRAME, 0, 0, FALSE, HEAPID_OP_DEMO);

		//パレット
		ArcUtil_PalSet(ARC_OP_DEMO, palID,
							PALTYPE_SUB_BG,0,16*2*8,HEAPID_OP_DEMO);	//８本ロード
	}
	//--空・町データロード
	//キャラ
	ArcUtil_BgCharSet(ARC_OP_DEMO, NARC_op_demo_op_demoBG1_NCGR,
						scene_wk->bgl, TOWN_FRAME, 0, 0, FALSE, HEAPID_OP_DEMO);
	//スクリーン
	ArcUtil_ScrnSet(ARC_OP_DEMO, NARC_op_demo_op_demoBG1_town_NSCR,
						scene_wk->bgl, TOWN_FRAME, 0, 0, FALSE, HEAPID_OP_DEMO);
	ArcUtil_ScrnSet(ARC_OP_DEMO, NARC_op_demo_op_demoBG1_sky_NSCR,
						scene_wk->bgl, SKY_FRAME, 0, 0, FALSE, HEAPID_OP_DEMO);
	//--アクターセット
	OPD_Obj_InitCellActor( scene_wk->ObjWorkPtr );
	OPD_Obj_SetActor( scene_wk->ObjWorkPtr );
	
	//--キラキラアクターセット
	OPD_Obj_SetKiraActor( scene_wk->ObjWorkPtr,
						  scene_wk->KiraListPtr );

	//--初期ＢＧ設定
	//全部非表示
	GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG1|GX_PLANEMASK_BG2|GX_PLANEMASK_BG3, VISIBLE_OFF );
	
	GF_Disp_GXS_VisibleControl( GX_PLANEMASK_BG0, VISIBLE_OFF );

	WIPE_ResetBrightness( WIPE_DISP_MAIN );
	WIPE_ResetBrightness( WIPE_DISP_SUB );

	scene_wk->LoadOK = 1;		//load通過
}

static void Scene2_Load3D(SCENE2_WORK *scene_wk)
{
	u8 i;
	ARCHANDLE* handle;
	BOOL status;
	NNSG3dResMdlSet* model_set;
	NNSG3dResMdl *model;
	//テクスチャロード
	scene_wk->Data.TexFile = ArchiveDataLoadMalloc(	ARC_OP_DEMO,
													NARC_op_demo_titlemap_texset_nsbtx,
													HEAPID_OP_DEMO );

	scene_wk->Data.Texture = NNS_G3dGetTex((NNSG3dResFileHeader*) scene_wk->Data.TexFile );	// テクスチャリソース取得

	{
		BOOL rc;
		rc = LoadVRAMTexture(scene_wk->Data.Texture);
		GF_ASSERT(rc && "オープニング：テクスチャのVRAM確保失敗");
	}

	//実体を破棄
	{
		u8* texImgStartAddr;
		u32 newSize;

		GF_ASSERT(scene_wk->Data.Texture->texInfo.ofsTex != 0);
		texImgStartAddr = (u8*)scene_wk->Data.Texture + scene_wk->Data.Texture->texInfo.ofsTex;
		// ヒープの先頭からテクスチャイメージまでのサイズ
		newSize = (u32)(texImgStartAddr - (u8*)scene_wk->Data.TexFile);
		sys_CutMemoryBlockSize( scene_wk->Data.TexFile, newSize );
	}

	//アーカイブハンドルオープン
	handle = ArchiveDataHandleOpen( ARC_OP_DEMO, HEAPID_OP_DEMO );
	
	for (i=0;i<OP_MAP_BLOCK_MAX;i++){
		//モデリングデータをロード
		scene_wk->Data.Block[i].ResFile = ArchiveDataLoadAllocByHandle( handle, ModelArcTbl[i], HEAPID_OP_DEMO );

		//テクスチャバインド
		status = BindTexture(scene_wk->Data.Block[i].ResFile, scene_wk->Data.Texture);
		GF_ASSERT(status&&"BindTexture failed");
	
		model_set = NNS_G3dGetMdlSet(scene_wk->Data.Block[i].ResFile);

		GF_ASSERT(model_set->dict.numEntry==1&&"モデルセットの中に複数モデルが存在");

		model = NNS_G3dGetMdlByIdx(NNS_G3dGetMdlSet(scene_wk->Data.Block[i].ResFile), 0);
		GF_ASSERT(model&&"load failed");
		NNS_G3dRenderObjInit(&scene_wk->Data.Block[i].RenderObj, model);

		//モデリングデータはグローバルステートを使用する
		NNS_G3dMdlUseGlbDiff(model);			// ディフューズ
		NNS_G3dMdlUseGlbAmb(model);				// アンビエント
		NNS_G3dMdlUseGlbSpec(model);			// スペキュラー
		NNS_G3dMdlUseGlbEmi(model);				// エミッション
	
		NNS_G3dMdlUseGlbLightEnableFlag(model);
	}
	//ハンドルクローズ
	ArchiveDataHandleClose( handle );
	
	scene_wk->Data.CameraPtr = GFC_AllocCamera(HEAPID_OP_DEMO);	//カメラ作成
	{
		VecFx32 target = {0,0,FX32_ONE*16*6};
		//カメラセット
		GFC_InitCameraTDA( &target,
			CameraData.Distance,	// 距離
			&CameraData.Angle,	//
			CameraData.PerspWay,	// 投射影の角度
			CameraData.View,
			FALSE,				//バインドしない
			scene_wk->Data.CameraPtr
			);
		GFC_SetCameraPerspWay(0x0981,scene_wk->Data.CameraPtr);

		//ソノオタウンの高さにあわせる
		{
			VecFx32 move = {0,SONOO_TOWN_HEIGHT,0};
			GFC_ShiftCamera(&move,scene_wk->Data.CameraPtr);
		}

		GFC_AttachCamera(scene_wk->Data.CameraPtr);
	}
	scene_wk->Load3DOK = 1;		//3Dload通過
	
}

static void Scene2_Disp3D(SCENE2_WORK *scene_wk)
{
	u8 i;
	MtxFx33 rotate_tmp = {FX32_ONE,0,0,0,FX32_ONE,0,0,0,FX32_ONE};
	VecFx32 scale = {FX32_ONE,FX32_ONE,FX32_ONE};
	VecFx32 trans = {0,0,0};
	GF_G3X_Reset();
	GFC_CameraLookAt();

	for(i=0;i<OP_MAP_BLOCK_MAX;i++){
		simple_3DModelDraw(	&scene_wk->Data.Block[i].RenderObj,
							&trans,
							&rotate_tmp,
							&scale);
	}
	GF_G3_RequestSwapBuffers(GX_SORTMODE_AUTO,GX_BUFFERMODE_W);
}

static BOOL Scene2_Main(SCENE2_WORK *scene_wk, const int inCounter)
{
	u8 *seq = &(scene_wk->SceneSeq);

	if (!scene_wk->KiraMargin){
		Scene2_KiraGenerateMain(scene_wk->KiraListPtr);
	}
	scene_wk->KiraMargin = (scene_wk->KiraMargin+1)%scene_wk->KiraMarginCore;
	
	switch(*seq){
	case 0:	//タイミングを取って、バーン！とポケモンロゴ
		if (inCounter >= FM_TITLE_LOGO_IN){
			GF_Disp_GXS_VisibleControl( GX_PLANEMASK_BG0, VISIBLE_ON );
			//タイトルロゴの輝度を元に戻す
			ChangeBrightnessRequest(TITLE_LOGO_WHITE_IN_SYNC, BRIGHTNESS_NORMAL, BRIGHTNESS_WHITE,
								GX_BLEND_PLANEMASK_BG0, MASK_SUB_DISPLAY);
			(*seq)++;
		}
		break;
	case 1:
/**		
		//よきところで下面ホワイトアウト
		if (inCounter >= FM_TITLE_WHITE_OUT){
			WIPE_SYS_Start(	WIPE_PATTERN_M, WIPE_TYPE_FADEOUT,
								WIPE_TYPE_FADEOUT,0x7fff,OPDEMO_BRIGHTNESS_SYNC,1,HEAPID_OP_DEMO );
			(*seq)++;
		}
*/
		//主人公アニメ開始
		OPD_Obj_OnOffHeroHeroineAnime( scene_wk->ObjWorkPtr, 1 );
		(*seq)++;
		break;
	case 2:
		if (inCounter==FM_KIRA_DISP_START){
			GF_Disp_GXS_VisibleControl( GX_PLANEMASK_OBJ, VISIBLE_ON );
		}

		if ( /*WIPE_SYS_EndCheck()&&*/(inCounter>=FM_SKY_CAMERA_START) ){
			//メイン全部・ＯＢＪ表示（実際は3Ｄ面しけ見えない
			GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG0|GX_PLANEMASK_BG1|
										GX_PLANEMASK_BG2, VISIBLE_ON );
			//ホワイトイン
			WIPE_SYS_Start(	WIPE_PATTERN_M, WIPE_TYPE_FADEIN,
							WIPE_TYPE_FADEIN,0x7fff,OPDEMO_BRIGHTNESS_SYNC,1,HEAPID_OP_DEMO );

			scene_wk->KiraMarginCore = SCENE2_KIRA_MARGIN2;
			
			(*seq)++;
		}
		break;
	case 3:	//インしたら、3Ｄカメラ移動シーン（裏で2Ｄ面の表示はしておく）
		if ( /*(inCounter>=FM_SKY_CAMERA_START)*/1 ){
			//空撮
			Scene2_CameraMoveMain(scene_wk,inCounter);
			//鳥スライド
			OPD_Obj_SlideInBird(scene_wk->ObjWorkPtr, inCounter);
			if (inCounter >= FM_3D_WHITE_OUT){
				//空撮終了ホワイトアウトリクエスト
				WIPE_SYS_Start(	WIPE_PATTERN_M, WIPE_TYPE_FADEOUT,
								WIPE_TYPE_FADEOUT,0x7fff,OPDEMO_BRIGHTNESS_SYNC,1,HEAPID_OP_DEMO );
				(*seq)++;
			}
		}
		break;
	case 4:
		//空撮
		Scene2_CameraMoveMain(scene_wk,inCounter);
		//鳥スライド
		OPD_Obj_SlideInBird(scene_wk->ObjWorkPtr, inCounter);
		//ホワイトアウト待ち
		if ( WIPE_SYS_EndCheck()&&(inCounter >= FM_HERO_WALK) ){
			//男主人公表示
			OPD_Obj_DispOnOff( scene_wk->ObjWorkPtr, ACT_WORK_HERO, 1 );
			//ウィンドウ表示
			Scene2_SetWindow();
			//3Dモデルドロー関数を無効
			scene_wk->Disp3DFlg = 0;
			//ホワイトインリクエスト
			WIPE_SYS_Start(	WIPE_PATTERN_M, WIPE_TYPE_FADEIN,
							WIPE_TYPE_FADEIN,0x7fff,OPDEMO_BRIGHTNESS_SYNC,1,HEAPID_OP_DEMO );
			(*seq)++;
		}
		break;
	case 5:	//主人公男歩き
		//町スクロール
		Scene2_ScrollTown(scene_wk);	
		//ホワイトイン待ち
		if ( WIPE_SYS_EndCheck() ){
			if (inCounter >= FM_NAETORU_SETUP){
				//よきところで、ブラックアウト速め
				WIPE_SYS_Start(	WIPE_PATTERN_M, WIPE_TYPE_FADEOUT,
							WIPE_TYPE_FADEOUT,0x0000,SCENE2_DISP_CHG_SYNC,1,HEAPID_OP_DEMO );
				(*seq)++;
			}
		}
		break;
	case 6:	//ブラックアウトしたら下記処理
		if ( WIPE_SYS_EndCheck() ){
			G2_SetBlendAlpha(GX_BLEND_PLANEMASK_NONE,
							 GX_BLEND_PLANEMASK_BG3|GX_BLEND_PLANEMASK_OBJ|GX_BLEND_PLANEMASK_BD,
					         0,0);
			//空・町ＢＧ非表示
			GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG1|GX_PLANEMASK_BG2, VISIBLE_OFF );
			//バトルＢＧ・3Ｄ面表示
			GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG3, VISIBLE_ON );
			GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG0, VISIBLE_ON );
			//ＯＢＪブライトネス落とす
///			G2_SetBlendBrightnessExt(PLANEMASK_OBJ, GX_BLEND_PLANEMASK_BG3, 0,0,BRIGHTNESS_BLACK);
			//男主人公パレット変更（黒）
			OPD_Obj_ChangeCollor(scene_wk->ObjWorkPtr, ACT_WORK_HERO, CHG_MODE_BLACK);
			//ブラックイン速め
			WIPE_SYS_Start(	WIPE_PATTERN_M, WIPE_TYPE_FADEIN,
							WIPE_TYPE_FADEIN,0x0000,SCENE2_DISP_CHG_SYNC,1,HEAPID_OP_DEMO );
			(*seq)++;
		}
		break;
	case 7:	//ナエトルカットイン
		//バトルＢＧスクロール
		Scene2_ScrollBattle(scene_wk);
		if ( WIPE_SYS_EndCheck() ){
			if ( OPD_Poke_CutIn(scene_wk->OpSsmPtr, CUT_IN_NAETORU, inCounter) ){
				//ブラックアウト速め
				WIPE_SYS_Start(	WIPE_PATTERN_M, WIPE_TYPE_FADEOUT,
							WIPE_TYPE_FADEOUT,0x0000,SCENE2_DISP_CHG_SYNC,1,HEAPID_OP_DEMO );
				(*seq)++;
			}
		}
		break;

	case 8:
		if ( WIPE_SYS_EndCheck() ){
			if (inCounter >= FM_RIVAL_SETUP){
				//主人公アニメ開始
				OPD_Obj_OnOffHeroHeroineAnime( scene_wk->ObjWorkPtr, 1 );
				//男主人公非表示
				OPD_Obj_DispOnOff( scene_wk->ObjWorkPtr, ACT_WORK_HERO, 0 );
				//女主人公表示
				OPD_Obj_DispOnOff( scene_wk->ObjWorkPtr, ACT_WORK_HEROINE, 1 );
				//ＯＢＪブライトネス戻す
///				G2_SetBlendBrightnessExt(PLANEMASK_OBJ, GX_BLEND_PLANEMASK_BG3, 0,0,BRIGHTNESS_NORMAL);
				//男主人公パレット変更（元に戻す）
				OPD_Obj_ChangeCollor(scene_wk->ObjWorkPtr, ACT_WORK_HERO, CHG_MODE_NORMAL);
				//戦闘パレット変更（ライバル）
				Scene_LoadPal(scene_wk->PalData[BTL_PAL_RIVAL], DISP_MAIN, OPD_BTL_PAL_NUM, 0, 0);
				//ライバル表示
				OPD_Obj_DispOnOff( scene_wk->ObjWorkPtr, ACT_WORK_RIVAL, 1 );
				//ブラックイン速め
				WIPE_SYS_Start(	WIPE_PATTERN_M, WIPE_TYPE_FADEIN,
								WIPE_TYPE_FADEIN,0x0000,SCENE2_DISP_CHG_SYNC,1,HEAPID_OP_DEMO );
				(*seq)++;
			}
		}
		break;
	case 9:	//ライバルスライドイン
		//バトルＢＧスクロール
		Scene2_ScrollBattle(scene_wk);
		if ( WIPE_SYS_EndCheck()&&(inCounter >= FM_RIVAL_SLIDE_IN) ){
			if ( OPD_Obj_SlideInRival(scene_wk->ObjWorkPtr) ){
				if (inCounter>=FM_HIKOZARU_SETUP){
					//ブラックアウト速め
					WIPE_SYS_Start(	WIPE_PATTERN_M, WIPE_TYPE_FADEOUT,
								WIPE_TYPE_FADEOUT,0x0000,SCENE2_DISP_CHG_SYNC,1,HEAPID_OP_DEMO );
					(*seq)++;
				}
			}
		}
		break;

	case 10:
		if ( WIPE_SYS_EndCheck() ){
			//ＯＢＪブライトネス落とす
///			G2_SetBlendBrightnessExt(PLANEMASK_OBJ, GX_BLEND_PLANEMASK_BG3, 0,0,BRIGHTNESS_BLACK);
			//女主人公パレット変更（黒）
			OPD_Obj_ChangeCollor(scene_wk->ObjWorkPtr, ACT_WORK_HEROINE, CHG_MODE_BLACK);
			//戦闘パレット変更(ヒコザル)
			Scene_LoadPal(scene_wk->PalData[BTL_PAL_HIKOZARU], DISP_MAIN, OPD_BTL_PAL_NUM, 0, 0);
			//ライバル非表示
			OPD_Obj_DispOnOff( scene_wk->ObjWorkPtr, ACT_WORK_RIVAL, 0 );
			//ブラックイン速め
			WIPE_SYS_Start(	WIPE_PATTERN_M, WIPE_TYPE_FADEIN,
							WIPE_TYPE_FADEIN,0x0000,SCENE2_DISP_CHG_SYNC,1,HEAPID_OP_DEMO );
			(*seq)++;
		}
		break;
	case 11:	//ヒコザルカットイン
		//バトルＢＧスクロール
		Scene2_ScrollBattle(scene_wk);
		if ( WIPE_SYS_EndCheck() ){
			if ( OPD_Poke_CutIn(scene_wk->OpSsmPtr, CUT_IN_HIKOZARU, inCounter) ){
				//ブラックアウト速め
				WIPE_SYS_Start(	WIPE_PATTERN_M, WIPE_TYPE_FADEOUT,
							WIPE_TYPE_FADEOUT,0x0000,SCENE2_DISP_CHG_SYNC,1,HEAPID_OP_DEMO );
				(*seq)++;
			}
		}
		break;
	case 12:
		if ( WIPE_SYS_EndCheck() ){
			if (inCounter>FM_HEROINE_SETUP){			
				//ＯＢＪブライトネス戻す
///				G2_SetBlendBrightnessExt(PLANEMASK_OBJ, GX_BLEND_PLANEMASK_BG3, 0,0,BRIGHTNESS_NORMAL);
				//女主人公パレット変更（元に戻す）
				OPD_Obj_ChangeCollor(scene_wk->ObjWorkPtr, ACT_WORK_HEROINE, CHG_MODE_NORMAL);
				//空ＢＧ表示
				GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG2, VISIBLE_ON );
				//男主人公表示
				OPD_Obj_DispOnOff( scene_wk->ObjWorkPtr, ACT_WORK_HERO, 1 );
				//女主人公位置変更
				OPD_Obj_ChangeHeroinePos( scene_wk->ObjWorkPtr );
				//アニメ変更
				OPD_Obj_ChangeHeroHeroineAnime(scene_wk->ObjWorkPtr, 4);
				//ブラックイン速め
				WIPE_SYS_Start(	WIPE_PATTERN_M, WIPE_TYPE_FADEIN,
								WIPE_TYPE_FADEIN,0x0000,SCENE2_DISP_CHG_SYNC,1,HEAPID_OP_DEMO );
				scene_wk->BG_ScrollMargin = 0;	//スクロールに備え初期化
				(*seq)++;
			}
		}
		break;		
	case 13:	//しばし歩く
		//BGスクロール
		Scene2_ScrollSky(scene_wk);
		if ( WIPE_SYS_EndCheck() ){
			if (inCounter>FM_POTTYAMA_SETUP){
				//ブラックアウト速め
				WIPE_SYS_Start(	WIPE_PATTERN_M, WIPE_TYPE_FADEOUT,
							WIPE_TYPE_FADEOUT,0x0000,SCENE2_DISP_CHG_SYNC,1,HEAPID_OP_DEMO );
				scene_wk->BG_ScrollMargin = 0;	//スクロールに備え初期化
				(*seq)++;
			}
		}
		break;
	case 14:
		if ( WIPE_SYS_EndCheck() ){
			//主人公パレット変更
			OPD_Obj_ChangeCollor(scene_wk->ObjWorkPtr, ACT_WORK_HERO, CHG_MODE_BLACK);
			OPD_Obj_ChangeCollor(scene_wk->ObjWorkPtr, ACT_WORK_HEROINE, CHG_MODE_BLACK);
			//戦闘パレット変更(ポッチャマ)
			Scene_LoadPal(scene_wk->PalData[BTL_PAL_POTTYAMA], DISP_MAIN, OPD_BTL_PAL_NUM, 0, 0);
			//女主人公非表示
			///OPD_Obj_DispOnOff( scene_wk->ObjWorkPtr, ACT_WORK_HEROINE, 0 );
			//空ＢＧ非表示
			GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG2, VISIBLE_OFF );
			//ブラックイン速め
			WIPE_SYS_Start(	WIPE_PATTERN_M, WIPE_TYPE_FADEIN,
							WIPE_TYPE_FADEIN,0x0000,SCENE2_DISP_CHG_SYNC,1,HEAPID_OP_DEMO );
			(*seq)++;
		}
		break;
	case 15:	//ポチャマカットイン
		//バトルＢＧスクロール
		Scene2_ScrollBattle(scene_wk);
		if ( WIPE_SYS_EndCheck() ){
			if ( OPD_Poke_CutIn(scene_wk->OpSsmPtr, CUT_IN_POTTYAMA, inCounter) ){
				//チョーゆっくりブラックアウト
///				ChangeBrightnessRequest(SCENE2_END_OUT_SYNC, BRIGHTNESS_BLACK, BRIGHTNESS_NORMAL,
///						PLANEMASK_ALL, MASK_DOUBLE_DISPLAY);
				WIPE_SYS_Start(	WIPE_PATTERN_WMS, WIPE_TYPE_FADEOUT,
							WIPE_TYPE_FADEOUT,0x0000,OPDEMO_BRIGHTNESS_SYNC,1,HEAPID_OP_DEMO );
				(*seq)++;
			}
		}
		break;
	case 16:
		//バトルＢＧスクロール
		Scene2_ScrollBattle(scene_wk);
		//ブラックアウト待ち
		if ( WIPE_SYS_EndCheck() ){
			(*seq)++;
		}
		break;
	case 17:	//終了
		return TRUE;
		break;
	}	
	return FALSE;
}

static void Scene_LoadPal(NNSG2dPaletteData *inPalData, const u8 inDispMS,
						  const u8 inPalNum, const u8 inStart, const u8 inDst)
{
	u16 * adr;
	DC_FlushRange( inPalData->pRawData, 2*16*inPalNum );	//inPalNum本分をフラッシュ
	adr = inPalData->pRawData;
	//16パレットinStart番目からinPalNum本分ロード
	if (inDispMS == DISP_MAIN){
		GX_LoadBGPltt( &adr[inStart], inDst, 2*16*inPalNum );
	}else{
		GXS_LoadBGPltt( &adr[inStart], inDst, 2*16*inPalNum );
	}
}

static void Scene2_ScrollTown(SCENE2_WORK *scene_wk)
{
	if (scene_wk->BG_ScrollMargin++ > SCENE2_TOWN_SCROLL_MARGIN){
		GF_BGL_ScrollSet( scene_wk->bgl, TOWN_FRAME, GF_BGL_SCROLL_Y_INC, TOWN_BG_SPEED );
		scene_wk->BG_ScrollMargin = 0;
	}
}

static void Scene2_ScrollSky(SCENE2_WORK *scene_wk)
{
	if (scene_wk->BG_ScrollMargin++ > SCENE2_SKY_SCROLL_MARGIN){
		GF_BGL_ScrollSet( scene_wk->bgl, SKY_FRAME, GF_BGL_SCROLL_X_INC, SKY_BG_SPEED );
		scene_wk->BG_ScrollMargin = 0;
	}
}

static void Scene2_ScrollBattle(SCENE2_WORK *scene_wk)
{
///	if (scene_wk->BG_ScrollMargin++ > SCENE2_BATTLE_SCROLL_MARGIN){
		GF_BGL_ScrollSet( scene_wk->bgl, G256_FRAME, GF_BGL_SCROLL_X_INC, BATTLE_BG_SPEED );
		scene_wk->BG_ScrollMargin = 0;
///	}
}

#define ANGLE_MOVE	(-0x980)

static void Scene2_CameraMoveMain(SCENE2_WORK *scene_wk, const int inCounter)
{
	VecFx32 move = {0,0,0};
	if (inCounter<=FM_CAMEA1_END){
		//カメラズーム
		{
			u16 persp_way;
			persp_way = GFC_GetCameraPerspWay(scene_wk->Data.CameraPtr);
			if (persp_way-32>0x05c1){
				GFC_AddCameraPerspWay(-32,scene_wk->Data.CameraPtr);
			}else{
				GFC_SetCameraPerspWay(0x05c1,scene_wk->Data.CameraPtr);
			}
		}
		//上に平行移動
		move.z -= FX32_ONE*2;
		GFC_ShiftCamera(&move, scene_wk->Data.CameraPtr);
		if (inCounter == FM_CAMEA1_END){
			VecFx32 target = {-(FX32_ONE*16*8),0,-(FX32_ONE*16*(32-4))};
			//カメラセット
			GFC_InitCameraTDA( &target,
				CameraData.Distance,	// 距離
				&CameraData.Angle,	//
				CameraData.PerspWay,	// 投射影の角度
				CameraData.View,
				FALSE,				//バインドしない
				scene_wk->Data.CameraPtr
			);
			//ソノオタウンの高さにあわせる
			{
				VecFx32 move = {0,SONOO_TOWN_HEIGHT,0};
				GFC_ShiftCamera(&move,scene_wk->Data.CameraPtr);
			}
			//角度つける
			{
				CAMERA_ANGLE angle = {0,ANGLE_MOVE,0,0};
				GFC_AddCameraAngleRot(&angle,scene_wk->Data.CameraPtr);
			}
		}
	}else if(inCounter<=FM_CAMEA2_END){
		//右に平行移動
		move.x += FX32_ONE;
		GFC_ShiftCamera(&move, scene_wk->Data.CameraPtr);
		if (inCounter == FM_CAMEA2_END){
			VecFx32 target = {FX32_ONE*16*32,0,-(FX32_ONE*16*32*4)+(FX32_ONE*16*16)};
			//カメラセット
			GFC_InitCameraTDA( &target,
				CameraData.Distance,	// 距離
				&CameraData.Angle,	//
				CameraData.PerspWay,	// 投射影の角度
				CameraData.View,
				FALSE,				//バインドしない
				scene_wk->Data.CameraPtr
			);
			GFC_SetCameraPerspWay(0x05c1,scene_wk->Data.CameraPtr);
			//ソノオタウンの高さにあわせる
			{
				VecFx32 move = {0,SONOO_TOWN_HEIGHT,0};
				GFC_ShiftCamera(&move,scene_wk->Data.CameraPtr);
			}
		}
	}else {
		//下に平行移動（よきところで、カメラ引く）
		if (inCounter>=FM_CAM_ZOOM_OUT_START){
			u16 persp_way;
			persp_way = GFC_GetCameraPerspWay(scene_wk->Data.CameraPtr);
			if (persp_way+32<0x4000){
				GFC_AddCameraPerspWay(32,scene_wk->Data.CameraPtr);
			}
		}
		move.z += 4*FX32_ONE;
		GFC_ShiftCamera(&move, scene_wk->Data.CameraPtr);
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////
//
//シーン3（テンガンザン）
static void Scene3_Init(OPENING_DEMO_WORK * wk);
static void Scene3_Load(SCENE3_WORK *scene_wk);
static BOOL Scene3_Main(SCENE3_WORK *scene_wk, const int inCounter);
static void Scene3_End(OPENING_DEMO_WORK * wk);
static void Scene3_Affine(SCENE3_WORK *scene_wk);
static void Scene3_Affine2(SCENE3_WORK *scene_wk);
static void RequestThunder(SCENE3_THUNDER_DATA *outData);
static void ThunderMain(SCENE3_WORK *scene_wk);

static BOOL MtTenganScene(OPENING_DEMO_WORK * wk)
{
	u8 *seq = &(wk->SceneWork3.Seq);
	if (wk->SkipFlg){
		(*seq) = 3;		//スキップ実行
	}
	
	switch(*seq){
	case 0:		//初期化
		Scene3_Init(wk);
		(*seq)++;
		break;
	case 1:			//グラフィックロード
		Scene3_Load(&wk->SceneWork3);
		(*seq)++;
		break;
	case 2:			//メイン
		if ( Scene3_Main( &wk->SceneWork3, wk->FrameCounter ) ){
			(*seq)++;
		}
		break;
	case 3:			//終了
		Scene3_End(wk);
		return TRUE;
	}
	return FALSE;
}

static void Scene3_Init(OPENING_DEMO_WORK * wk)
{
	int obj_work_size;
	int ssm_size;
	OpDemo_Scene3_VramBankSet();
	OpDemo_Scene3_2DBgSet(wk);

	wk->SceneWork3.bgl = wk->bgl;

	//マスター輝度を０にする
	WIPE_SetBrightness( WIPE_DISP_MAIN,WIPE_FADE_BLACK );
	WIPE_SetBrightness( WIPE_DISP_SUB,WIPE_FADE_BLACK );
	//カラー特殊効果無効
	G2_BlendNone();

	wk->SceneWork3.InitOK = 1;	//init通過
}

static void Scene3_Load(SCENE3_WORK *scene_wk)
{
	ARCHANDLE* pal_handle;
/**
	const int pal_arc_idx[BTL_PAL_MAX] = {
		NARC_op_demo_op_demoBG2_btl1_NCLR,
		NARC_op_demo_op_demoBG2_btl2_NCLR,
		NARC_op_demo_op_demoBG2_btl3_NCLR,
		NARC_op_demo_op_demoBG2_btl4_NCLR
	};
*/	
	//パレットアーカイブハンドルオープン
	pal_handle  = ArchiveDataHandleOpen( ARC_OP_DEMO, HEAPID_OP_DEMO);

	scene_wk->PalDataBuf = ArchiveDataLoadAllocByHandle( pal_handle, NARC_op_demo_op_demoBG3_NCLR, HEAPID_OP_DEMO );
	if( scene_wk->PalDataBuf != NULL )
	{
		if( NNS_G2dGetUnpackedPaletteData( scene_wk->PalDataBuf, &scene_wk->PalData ) == FALSE ){
			sys_FreeMemoryEz( scene_wk->PalData );
			GF_ASSERT(0);
		}
	}else{
		GF_ASSERT(0);
	}
	
	//ハンドルクローズ
	ArchiveDataHandleClose( pal_handle );

	//パレット
	Scene_LoadPal(scene_wk->PalData, DISP_MAIN, 9, 0, 0);		//9本ロード
	Scene_LoadPal(scene_wk->PalData, DISP_SUB, 9, 0, 0);		//9本ロード
	
	//--雲データロード
	//キャラ
	ArcUtil_BgCharSet(ARC_OP_DEMO, NARC_op_demo_op_demoBG_cloud_NCGR,
						scene_wk->bgl, MT_CLOUD_FRAME, 0, 0, FALSE, HEAPID_OP_DEMO);
	//スクリーン
	ArcUtil_ScrnSet(ARC_OP_DEMO, NARC_op_demo_op_demoBG3_cloud_NSCR,
						scene_wk->bgl, MT_CLOUD_FRAME, 0, 0, FALSE, HEAPID_OP_DEMO);
		
	//--山データロード
	//キャラ
	ArcUtil_BgCharSet(ARC_OP_DEMO, NARC_op_demo_op_demoBG3_tengan_NCGR,
						scene_wk->bgl, MT_TENGAN_FRAME, 0, 0, FALSE, HEAPID_OP_DEMO);
	//スクリーン
	ArcUtil_ScrnSet(ARC_OP_DEMO, NARC_op_demo_op_demoBG3_tengan_NSCR,
						scene_wk->bgl, MT_TENGAN_FRAME, 0, 0, FALSE, HEAPID_OP_DEMO);
		
	//--湖データロード
	//キャラ
	ArcUtil_BgCharSet(ARC_OP_DEMO, NARC_op_demo_op_demoBG3_lake_NCGR,
						scene_wk->bgl, MT_LAKE_FRAME, 0, 0, FALSE, HEAPID_OP_DEMO);
	//スクリーン
	ArcUtil_ScrnSet(ARC_OP_DEMO, NARC_op_demo_op_demoBG3_lake_NSCR,
						scene_wk->bgl, MT_LAKE_FRAME, 0, 0, FALSE, HEAPID_OP_DEMO);

	//--雷データロード
	//キャラ
	ArcUtil_BgCharSet(ARC_OP_DEMO, NARC_op_demo_op_demoBG3_thunder_NCGR,
						scene_wk->bgl, MT_THUNDER_FRAME, 0, 0, FALSE, HEAPID_OP_DEMO);
	//スクリーン
	ArcUtil_ScrnSet(ARC_OP_DEMO, NARC_op_demo_op_demoBG3_thunder_NSCR,
						scene_wk->bgl, MT_THUNDER_FRAME, 0, 0, FALSE, HEAPID_OP_DEMO);

	//--サブ雲データロード
	//キャラ
	ArcUtil_BgCharSet(ARC_OP_DEMO, NARC_op_demo_op_demoBG_cloud_m_NCGR,
						scene_wk->bgl, MT_CLOUD_SUB_FRAME, 0, 0, FALSE, HEAPID_OP_DEMO);
	//スクリーン
	ArcUtil_ScrnSet(ARC_OP_DEMO, NARC_op_demo_op_demoBG3_cloud_m_NSCR,
						scene_wk->bgl, MT_CLOUD_SUB_FRAME, 0, 0, FALSE, HEAPID_OP_DEMO);
		
	//--初期ＢＧ設定
	GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG1|
							   GX_PLANEMASK_BG2 | GX_PLANEMASK_BG3, VISIBLE_ON );
	GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG0, VISIBLE_OFF   );
	
	GF_Disp_GXS_VisibleControl( GX_PLANEMASK_BG1, VISIBLE_ON );

	//湖ＢＧは横48キャラあるので中央そろえする
	GF_BGL_ScrollSet( scene_wk->bgl, MT_LAKE_FRAME, GF_BGL_SCROLL_X_INC, ((48-32)*8/2) );
	//affine初期化
	{
		MtxFx22 mtx;
		fx32 rScale_x,rScale_y;
	
		rScale_x = FX_Inv(0x1000);
		rScale_y = FX_Inv(0x1000);
		mtx._00 = rScale_x;
		mtx._01 = 0;
	    mtx._10 = 0;
		mtx._11 = rScale_y;
		
		SVC_WaitVBlankIntr();          // Waiting the end of VBlank interrup
		GF_BGL_AffineSet( scene_wk->bgl, MT_TENGAN_FRAME, &mtx, 128, 96 );
		GF_BGL_AffineSet( scene_wk->bgl, MT_LAKE_FRAME, &mtx, 192, 96 );
	}
	
	scene_wk->LoadOK = 1;		//load通過
}

static BOOL Scene3_Main(SCENE3_WORK *scene_wk, const int inCounter)
{
	u8 *seq = &(scene_wk->SceneSeq);
	
	switch(*seq){
	case 0:	//ゆっくりブラックイン
		if (inCounter>=FM_TENGAN_IN){
			WIPE_SYS_Start(	WIPE_PATTERN_WMS, WIPE_TYPE_FADEIN,
								WIPE_TYPE_FADEIN,0x0000,SCENE3_START_IN_SYNC,1,HEAPID_OP_DEMO );
			(*seq)++;
		}
		break;
	case 1:
		if ( WIPE_SYS_EndCheck() ){
			(*seq)++;
			scene_wk->TenganSc = 0x1000;
			scene_wk->LakeSc = 0x1000;
		}
		break;
	case 2://よきところで両面ホワイトアウト
		//ＢＧスクロール・拡縮メイン
		if (inCounter==FM_THUNDER1){
			RequestThunder(&scene_wk->ThunderData);
		}
		if (inCounter==FM_THUNDER2){
			RequestThunder(&scene_wk->ThunderData);
		}
		if (inCounter==FM_THUNDER3){
			RequestThunder(&scene_wk->ThunderData);
		}
		if (inCounter==FM_THUNDER4){
			RequestThunder(&scene_wk->ThunderData);
		}

		if (inCounter>=FM_MT_AFFINE){
			Scene3_Affine(scene_wk);
		}
		
		if ( (inCounter>=FM_TENGAN_OUT) ){
			WIPE_SYS_Start(	WIPE_PATTERN_WMS, WIPE_TYPE_FADEOUT,
							WIPE_TYPE_FADEOUT,0x7fff,TENGAN_WH_OUT_SYNC,1,HEAPID_OP_DEMO );
			Scene3_Affine2(scene_wk);
			(*seq)++;
		}
		break;
	case 3:	//ホワイトアウト待ち
		Scene3_Affine2(scene_wk);
		if( WIPE_SYS_EndCheck() ){
			return TRUE;
		}
	}

	ThunderMain(scene_wk);
	
	return FALSE;
}

static void Scene3_End(OPENING_DEMO_WORK * wk)
{
	if (wk->SceneWork3.InitOK){
		//bgl解放
		GF_BGL_BGControlExit( wk->bgl, MT_CLOUD_FRAME );
		GF_BGL_BGControlExit( wk->bgl, MT_TENGAN_FRAME );
		GF_BGL_BGControlExit( wk->bgl, MT_LAKE_FRAME );
		GF_BGL_BGControlExit( wk->bgl, MT_THUNDER_FRAME );
		GF_BGL_BGControlExit( wk->bgl, MT_CLOUD_SUB_FRAME );
		sys_FreeMemoryEz( wk->bgl );
		wk->SceneWork3.InitOK = 0;
	}
	if (wk->SceneWork3.LoadOK){		//load通過
		//パレット解放
		sys_FreeMemoryEz(wk->SceneWork3.PalDataBuf);
		wk->SceneWork3.LoadOK = 0;
	}
}

static void Scene3_Affine(SCENE3_WORK *scene_wk)
{
	MtxFx22 tengan_mtx, lake_mtx;
    fx32 rScale_x,rScale_y;
	
	rScale_x = FX_Inv(scene_wk->TenganSc);
	rScale_y = FX_Inv(scene_wk->TenganSc);
    tengan_mtx._00 = rScale_x;
    tengan_mtx._01 = 0;
    tengan_mtx._10 = 0;
    tengan_mtx._11 = rScale_y;
	
	rScale_x = FX_Inv(scene_wk->LakeSc);
	rScale_y = FX_Inv(scene_wk->LakeSc);
    lake_mtx._00 = rScale_x;
    lake_mtx._01 = 0;
    lake_mtx._10 = 0;
    lake_mtx._11 = rScale_y;
	
    SVC_WaitVBlankIntr();          // Waiting the end of VBlank interrup

	
	if (scene_wk->TenganSc + TENGAN_AFF_VAL <= AFF_LIMIT_1){
		scene_wk->TenganSc += TENGAN_AFF_VAL;
		GF_BGL_AffineScrollSet( scene_wk->bgl, MT_TENGAN_FRAME, GF_BGL_SCROLL_Y_INC, 1,
									&tengan_mtx, 128, 90 );
		scene_wk->LakeSc += TENGAN_AFF_VAL;
		GF_BGL_AffineScrollSet( scene_wk->bgl, MT_LAKE_FRAME, GF_BGL_SCROLL_Y_INC, 1,
								&lake_mtx, 192, 90 );
	}
	
/**	
	if (++scene_wk->LakeAffMargin>=AFF_MARGIN){
		if (scene_wk->LakeSc-LAKE_AFF_VAL > LAVE_AFF_LIMIT){
			scene_wk->LakeSc -= LAKE_AFF_VAL;
			GF_BGL_AffineScrollSet( scene_wk->bgl, MT_LAKE_FRAME, GF_BGL_SCROLL_Y_INC, -1,
									&lake_mtx, 192, 144 );
		}
		scene_wk->LakeAffMargin = 0;
	}
*/	
}

static void Scene3_Affine2(SCENE3_WORK *scene_wk)
{
	MtxFx22 tengan_mtx, lake_mtx;
    fx32 rScale_x,rScale_y;
	
	rScale_x = FX_Inv(scene_wk->TenganSc);
	rScale_y = FX_Inv(scene_wk->TenganSc);
    tengan_mtx._00 = rScale_x;
    tengan_mtx._01 = 0;
    tengan_mtx._10 = 0;
    tengan_mtx._11 = rScale_y;
	
	rScale_x = FX_Inv(scene_wk->LakeSc);
	rScale_y = FX_Inv(scene_wk->LakeSc);
    lake_mtx._00 = rScale_x;
    lake_mtx._01 = 0;
    lake_mtx._10 = 0;
    lake_mtx._11 = rScale_y;
	
    SVC_WaitVBlankIntr();          // Waiting the end of VBlank interrup

	
	scene_wk->TenganSc += TENGAN_AFF_VAL2;
	GF_BGL_AffineScrollSet( scene_wk->bgl, MT_TENGAN_FRAME, GF_BGL_SCROLL_Y_INC, 1,
							&tengan_mtx, 128, 90 );
	scene_wk->LakeSc += TENGAN_AFF_VAL2;
	GF_BGL_AffineScrollSet( scene_wk->bgl, MT_LAKE_FRAME, GF_BGL_SCROLL_Y_INC, 1,
							&lake_mtx, 192, 90 );	
}

static u8 MtThunder[4] = {8,7,6,0};
static u8 CloudThunder[4] = {5,4,3,1};
static u8 ThunderWait[4] = {8,6,6,4};

static void RequestThunder(SCENE3_THUNDER_DATA *outData)
{
	outData->Request = 1;
	outData->Counter = 6;
	outData->NowPalTblNo = 0;
	//雷ＢＧオン
	GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG0, VISIBLE_ON );
}

static void ThunderMain(SCENE3_WORK *scene_wk)
{
	SCENE3_THUNDER_DATA *data = &scene_wk->ThunderData;
	if (data->Request){

		if (data->Counter >= ThunderWait[data->NowPalTblNo]){
			//パレット変更
			Scene_LoadPal(scene_wk->PalData, DISP_MAIN, 1, 16*MtThunder[data->NowPalTblNo], 0);		//山
			Scene_LoadPal(scene_wk->PalData, DISP_MAIN, 1, 16*CloudThunder[data->NowPalTblNo], 16*2);	//雲
			Scene_LoadPal(scene_wk->PalData, DISP_SUB, 1, 16*CloudThunder[data->NowPalTblNo], 16*2);	//雲
			data->Counter = 0;
			data->NowPalTblNo++;
			if (data->NowPalTblNo >= 4){
				data->Request = 0;
			}
		}else{
			data->Counter++;
		}

		if ( (data->NowPalTblNo==0)&&(data->Counter >= ThunderWait[0]) ){
			//雷ＢＧオフ
			GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG0, VISIBLE_OFF );
		}
	}
}
