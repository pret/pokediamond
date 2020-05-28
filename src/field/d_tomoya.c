#ifdef PM_DEBUG

#include "common.h"

#include "system/lib_pack.h"
#include "system/bmp_list.h"
#include "system/bmp_menu.h"
#include "fld_bmp.h"
#include "fieldmap.h"
#include "fieldsys.h"
#include "fieldmap_work.h"
#include "system/fontproc.h"
#include "system/window.h"
#include "system/numfont.h"

#include "d_tomoya.h"
#include "system/touchpanel_draw.h"
#include "field_light.h"
#include "fog_sys.h"
#include "weather_sys.h"
#include "field_glb_state.h"

#include "encount_effect.h"
#include "effect_uground.h"

#include "system/clact_util.h"
#include "system/render_oam.h"
#include "field_event.h"
#include "system/wipe.h"

#include "src/system/pm_overlay.h"

#include "msgdata/msg.naix"
#include "msgdata/msg_debug_tomoya.h"

#include "include/application/imageClip/imc_playsys.h"
#include "include/application/imageClip/imc_sys.h"
#include "include/savedata/imageclip_data.h"

#include "poketool/poke_tool.h"
#include "include/application/zukanlist/zkn_sys.h"

#include "src/field/ev_time.h"

#include "d_tomoya_proc_chg.h"

#include "include/system/laster.h"
#include "include/savedata/config.h"

#include "poison_effect.h"

#include "field_demo.h"
#include "field_subscreen.h"

#include "demo_climax.naix"
#include "amaikaori_eff.h"
#include "src/fielddata/eventdata/zone_d05r0114evc.h"

#include "talk_msg.h"
#include "include/application/imageClip/imc_preview.h"

#include "field_accessory_shop.h"

#include "field_hideneff.h"

#include "system/pm_rtc.h"


static FIELDSYS_WORK* D_TomoyaFldSys;



static GF_BGL_BMPWIN* initBmpWin(int num);
static void delBmpWin(GF_BGL_BMPWIN* data);
static void PrintString( GF_BGL_BMPWIN* win, u32 fontID, MSGDATA_MANAGER* man, u32 strid, u32 xofs, u32 yofs, u32 wait, pStrPrintCallBack call_back );



//-----------------------------------------------------------------------------
/**
 *
 *
 *		デオキシスセーブデータ
 *			修正ルーチン
 *
 */
//-----------------------------------------------------------------------------
static void D_TomoDeokisisuSaveBuckUp( TCB_PTR tcb,void* work );


//-----------------------------------------------------------------------------
/**
 * 
 * 
 *		1つ前の混ぜ混ぜ料理
 *			TEAMWORK得点描画ルーチン
 *
 */
//-----------------------------------------------------------------------------
//-------------------------------------
//	1つ前の混ぜ混ぜ料理
//	TEAMWORK得点描画ルーチン
//=====================================
typedef struct {
	FIELDSYS_WORK* p_fsys;
	GF_BGL_BMPWIN* p_bmp;
} D_TOMOYA_MAZEMAZE_TEAM;
static void StartTeamWorkScore( TCB_PTR tcb,void* work );
static void MainTeamWorkScore( TCB_PTR tcb,void* work );
extern u32 D_Tomoya_MazeMaze_TeamWork;

//-----------------------------------------------------------------------------
/**
 *
 *		秘伝技エフェクト
 *
 */
//-----------------------------------------------------------------------------
//-------------------------------------
//	秘伝技エフェクト
//=====================================
typedef struct {
	FLDMAPFUNC_WORK* p_demo;
	void* work;
	u32 seq;
} DTOMOYA_HIDENEFF;
static void StartHideEff( TCB_PTR tcb,void* work );
static void MainHideEff( TCB_PTR tcb,void* work );
static void StartHideEff01( TCB_PTR tcb,void* work );
static void MainHideEff01( TCB_PTR tcb,void* work );
static void StartHideEff02( TCB_PTR tcb,void* work );



//-----------------------------------------------------------------------------
/**
 *
 *		ポケパーティー内にミノムッチいろんなフォームの
 *
 */
//-----------------------------------------------------------------------------
static void Debug_MinoMuchiSet( TCB_PTR tcb, void* work );


//-----------------------------------------------------------------------------
/**
 *
 *
 *			アクセサリー交換
 * 
 */
//-----------------------------------------------------------------------------
//-------------------------------------
//	アクセサリー交換
//=====================================
typedef struct {
	u32 seq;
	FIELD_ACCE_SHOP*  p_acce_chg;
} D_TOMO_ACCE_CHANGE;
static void StartAcceShop( TCB_PTR tcb, void* p_work );
static void MainAcceShop( TCB_PTR tcb, void* p_work );


//-----------------------------------------------------------------------------
/**
 * 
 *		レコード交換　クリップ
 * 
 */
//-----------------------------------------------------------------------------
static void Record_Clip( TCB_PTR tcb, void* p_work );

//-----------------------------------------------------------------------------
/**
 *
 *		ゲーム内交換
 *
 */
//-----------------------------------------------------------------------------

static GMEVENT_CONTROL * EventCmd_D_FldTrade(u32 trade_no);

static void StartFldTrade00( TCB_PTR tcb, void* p_work );
static void StartFldTrade01( TCB_PTR tcb, void* p_work );
static void StartFldTrade02( TCB_PTR tcb, void* p_work );
static void StartFldTrade03( TCB_PTR tcb, void* p_work );


//-----------------------------------------------------------------------------
/**
 *
 *		図鑑データ操作
 *
 */
//-----------------------------------------------------------------------------
typedef struct{
	FIELDSYS_WORK* p_fsys;
	GF_BGL_BMPWIN* p_bmp;
	ZUKAN_WORK * p_zknwork;
	MSGDATA_MANAGER* msg_data;
	s32 start;
	s32 end;
	BOOL set_chuu;
} D_TOMOYA_ZUKAN_DATACONT;

#define D_TOMOYA_ZUKAN_DRAWCOLOR	( GF_PRINTCOLOR_MAKE(1,2,15) )

static void StartZukanCont( TCB_PTR tcb, void* p_work );
static void MainZukanCont( TCB_PTR tcb, void* p_work );

static void MainZukanZenkokuFlagSet( TCB_PTR tcb, void* p_work );
static void MainZukanZenkokuSet( TCB_PTR tcb, void* p_work );
static void MainZukanShinouSet( TCB_PTR tcb, void* p_work );
static void MainZukanZenkokuSeeSet( TCB_PTR tcb, void* p_work );
static void MainZukanShinouSeeSet( TCB_PTR tcb, void* p_work );


//-----------------------------------------------------------------------------
/**
 *
 *		エンカウントエフェクト
 *
 */
//-----------------------------------------------------------------------------
//-------------------------------------
//	エンカウントエフェクト管理ワーク
//=====================================
typedef struct {
	s32 no;
	u32 seq;
	BOOL sub_end;
	s32 work[2];
} D_TOMOYA_ENCOUNT_SYS_WORK;
static void StartEncountEffectSys( u32 effect_no );
static void MainEncountEffectSys( TCB_PTR tcb, void* p_work );
// 各ｴﾌｪｸﾄ
static void EncountEffect_00( TCB_PTR tcb, void* p_work );
static void EncountEffect_01( TCB_PTR tcb, void* p_work );
static void EncountEffect_02( TCB_PTR tcb, void* p_work );
static void EncountEffect_03( TCB_PTR tcb, void* p_work );
static void EncountEffect_04( TCB_PTR tcb, void* p_work );
static void EncountEffect_05( TCB_PTR tcb, void* p_work );
static void EncountEffect_06( TCB_PTR tcb, void* p_work );
static void EncountEffect_07( TCB_PTR tcb, void* p_work );
static void EncountEffect_08( TCB_PTR tcb, void* p_work );
static void EncountEffect_09( TCB_PTR tcb, void* p_work );
static void EncountEffect_10( TCB_PTR tcb, void* p_work );
static void EncountEffect_11( TCB_PTR tcb, void* p_work );
static void EncountEffect_12( TCB_PTR tcb, void* p_work );
static void EncountEffect_13( TCB_PTR tcb, void* p_work );
static void EncountEffect_14( TCB_PTR tcb, void* p_work );
static void EncountEffect_15( TCB_PTR tcb, void* p_work );
static void EncountEffect_16( TCB_PTR tcb, void* p_work );
static void EncountEffect_17( TCB_PTR tcb, void* p_work );
static void EncountEffect_18( TCB_PTR tcb, void* p_work );
static void EncountEffect_19( TCB_PTR tcb, void* p_work );
static void EncountEffect_20( TCB_PTR tcb, void* p_work );
static void EncountEffect_21( TCB_PTR tcb, void* p_work );
static void EncountEffect_22( TCB_PTR tcb, void* p_work );
static void EncountEffect_23( TCB_PTR tcb, void* p_work );
static void EncountEffect_24( TCB_PTR tcb, void* p_work );
static void EncountEffect_25( TCB_PTR tcb, void* p_work );
static void EncountEffect_26( TCB_PTR tcb, void* p_work );
static void EncountEffect_27( TCB_PTR tcb, void* p_work );
static void EncountEffect_28( TCB_PTR tcb, void* p_work );
static void EncountEffect_29( TCB_PTR tcb, void* p_work );
static void EncountEffect_30( TCB_PTR tcb, void* p_work );

//-----------------------------------------------------------------------------
/**
 * 
 *		あまいかおり
 * 
 */
//-----------------------------------------------------------------------------
//-------------------------------------
//	甘い香りワーク
//=====================================
typedef struct {
	FLDMAPFUNC_WORK* p_work;
	u32 seq;
	TCB_PTR debug;
} DTOMOYA_DEMO_AMAIKAORI;
static void StartAmaikaoriDemo( TCB_PTR tcb,void* work );
static void MainAmaikaoriDemo( TCB_PTR tcb,void* work );




//-----------------------------------------------------------------------------
/**
 *
 *	climaxでも用
 *
 */
//-----------------------------------------------------------------------------
//-------------------------------------
//	クライマックスでもワーク
//=====================================
typedef struct {
	FLDMAPFUNC_WORK* p_demo;
	VecFx32 matrix_tmp;
	u32 work;
	u32 seq;
} DTOMOYA_DEMO_CLIMAX;
static void StartClimaxDemo( TCB_PTR tcb,void* work );
static void MainClimaxDemo( TCB_PTR tcb,void* work );
static void StartClimaxDemoLegend( TCB_PTR tcb,void* work );
static void MainClimaxDemoLegend( TCB_PTR tcb,void* work );
static void StartClimaxDemoBlackRing( TCB_PTR tcb,void* work );
static void MainClimaxDemoBlackRing( TCB_PTR tcb,void* work );
static void StartClimaxDemoAntEgg00( TCB_PTR tcb,void* work );
static void StartClimaxDemoAntEgg01( TCB_PTR tcb,void* work );
static void StartClimaxDemoAntEgg02( TCB_PTR tcb,void* work );
static void MainClimaxDemoAntEgg( TCB_PTR tcb,void* work );
static void StartClimaxDemoAntEggStart( TCB_PTR tcb,void* work );
static void MainClimaxDemoAntEggStart( TCB_PTR tcb,void* work );


//-----------------------------------------------------------------------------
/**
 *
 * 毒エフェクト
 *
 */
//-----------------------------------------------------------------------------
//-------------------------------------
//	
//	ワーク	
//	
//=====================================
typedef struct {
	int		next_count;
	int		count;
	int		num;
	int		seq;
	GF_CAMERA_PTR	camera;
	PLAYER_STATE_PTR player;
} D_TOMOYA_POISON;
static void StartPoison( TCB_PTR tcb,void* work );		//	毒
static void MainPoison( TCB_PTR tcb,void* work );		//	毒

//-------------------------------------
//	ワーク	
//=====================================
typedef struct {
	int		next_count;
	int		seq;
	PLAYER_STATE_PTR player;

} D_TOMOYA_POISON_2;
static void StartPoison2( TCB_PTR tcb,void* work );		//	毒
static void MainPoison2( TCB_PTR tcb,void* work );		//	毒


//-------------------------------------
//	
//	スプライトを表示させるために必要な物
//
//	その後プロックチェンジに必要なものになりました
//	
//	
//=====================================
typedef struct {
	GF_BGL_BMPWIN* p_bmp;
	int count;
}D_TOMOYA_TV_PRINTDATA_SELE;


static void StartSprite_Check( TCB_PTR tcb,void* work );	// ドレスアップ通常開始
static void StartSprite_Check_Contest( TCB_PTR tcb,void* work );	// ドレスアップコンテスト用開始
static void StartSprite_CheckTelevision_View( TCB_PTR tcb,void* work );	// ドレスアップ通常のビューアー開始
static void StartSprite_CheckTelevision_PrintDataSelect( TCB_PTR tcb,void* work );
static void StartZukan_Check( TCB_PTR tcb, void* work );
static void StartEvPokeSelect_Check( TCB_PTR tcb, void* work );



//-----------------------------------------------------------------------------
/**
*		テクスチャデータ転送チェックシステム
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	
//	転送データ
//	
//=====================================
typedef struct {
	
	void* tex_buff;				// テクスチャバッファ
	NNSG3dResTex*	tex_res;	// テクスチャリソース
	int		trans_num;			// 転送数
	int		trans_size;			// 転送サイズ
	int		vram;
} D_TM_TEX_TRANS;
static void StartTexTrans( TCB_PTR tcb,void* work );		// テクスチャデータ転送チェック
static void MainTexTrans( TCB_PTR tcb,void* work );			// テクスチャデータ転送チェック



//-----------------------------------------------------------------------------
/**
*		ワイプチェック
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	
//	ワイプチェックタスク構造体
//	
//=====================================
typedef struct{
	int no;		// ワイプナンバー
	int seq;
}D_TMY_WIPE;

//-----------------------------------------------------------------------------
//			プロトタイプ
//=============================================================================
static void StartWipe( TCB_PTR tcb,void* work );		// 画面切り替え開始
static void MainWipe( TCB_PTR tcb,void* work );			// 画面切り替えメイン





//============================================================================
//
//		セルアクターチェック用
//					動作開始システム
//
//
//=============================================================================
//-----------------------------------------------------------------------------
//			構造体
//=============================================================================
//-------------------------------------
//	
//	セルを表示させるために必要な物
//	
//=====================================
typedef struct {
	CLACT_SET_PTR		clactSet;		// セルアクターセット
	CLACT_HEADER_TBL_PTR	clactHeader;	// ヘッダー
	CLACT_U_RES_MANAGER_PTR	resMan[6];		// リソースマネージャ
	CLACT_U_RES_HEADER_PTR	resHeader;		// リソースヘッダ
	CLACT_U_RES_OBJ_TBL*	resObjTbl[2];	// リソースオブジェテーブル
	int						resObjNum[6];	// それぞれのリソースオブジェ数
	CLACT_U_EASYRENDER_DATA		renddata;	// 簡易レンダーデータ

	NNSG2dCellTransferState*	cellTransArray;	// セルVram転送マネージャー領域

	CLACT_WORK_PTR	clact_w[10];
	int add_num;	// 登録数
	TCB_PTR tcb;	// tcb
} DT_CLACT;

static DT_CLACT* DT_clact = NULL;

//-----------------------------------------------------------------------------
//			プロトタイプ
//=============================================================================
static void StartCLACT_Check( TCB_PTR tcb,void* work );		// セルアクター開始
static void MainCLACT_Check( TCB_PTR tcb,void* work );		// セルアクターメイン
static void EndCLACT_Check( TCB_PTR tcb,void* work );		// セルアクター終了処理
;

//============================================================================
//		ちかまっぷフェードエフェクト
//			動作開始システム
//
//
//=============================================================================
//-----------------------------------------------------------------------------
//			構造体
//=============================================================================
typedef struct{
	int	no;
	int	flag;
}D_TMY_ENC;
//-----------------------------------------------------------------------------
//			プロトタイプ
//=============================================================================
static void StartUnderGround( TCB_PTR tcb,void* work );		// 地下マップフェード
static void MainUnderGround( TCB_PTR tcb,void* work );		// ちかまっぷフェード



#define D_TOMOYA_MATERIAL_ON
#ifdef D_TOMOYA_MATERIAL_ON
//============================================================================
//		マテリアル操作
//
//			マテリアル操作の関数やデータ
//
//
//=============================================================================

//-----------------------------------------------------------------------------
//			構造体
//=============================================================================
LIGHT_CONT_DATA* DebugMaterial;

//-------------------------------------
//	
//	１日表現セット	
//	
//=====================================
typedef struct _LIGHT_CONT_SET{
	u32		DataNum;				// データ数
	LIGHT_CONT_DATA* pDataTbl;		// データテーブル
	int Light_Num;					// 今のLIGHTナンバー
	GLST_DATA_PTR	Glb;			// グローバルステートの状態保存領域
	BOOL reflect;					// 反映フラグ	TRUE反映
} LIGHT_CONT_SET;



enum{
	DEB_MATE_LIGHT_END=0,
	DEB_MATE_LIGHT_FLAG,
	DEB_MATE_LIGHT_COLOR_0,
	DEB_MATE_LIGHT_COLOR_1,
	DEB_MATE_LIGHT_COLOR_2,
	DEB_MATE_LIGHT_COLOR_3,
	DEB_MATE_LIGHT_VEC_0,
	DEB_MATE_LIGHT_VEC_1,
	DEB_MATE_LIGHT_VEC_2,
	DEB_MATE_LIGHT_VEC_3,
	DEB_MATE_DIFFUSE,
	DEB_MATE_AMBIENT,
	DEB_MATE_SPECULAR,
	DEB_MATE_EMISSION,
	DEB_WIN,					// デバックウィンドウにキーの操作を許可する
	DEB_MATE_NUM
};

#define MT_ROTA_DEF		(90*182)
#define MT_ROT_GET(x)		((0xffff/360)*(x))
//-----------------------------------------------------------------------------
//			プロトタイプ
//=============================================================================

static void StartMaterialWindow( TCB_PTR tcb,void* work );	// マテリアルのデバックウィンドウ開始
static void MainMaterialWindow( TCB_PTR tcb,void* work );	// マテリアルのデバックウィンドウメイン
static void EndMaterialWindow( TCB_PTR tcb,void* work );	// マテリアルのデバックウィンドウ終了

static void DrawMenu( u32 num );				// Menuと情報を描画
static u8 NumInput(u32* num, u32 add, u32 limit);		// 数字の入力
static u8 ColorInput( s16* num );				// 色の入力
static u8 VecInput(u16* rotaY, u16* rotaXZ);	// ベクトル入力
static void DrawRGB( GXRgb num );				// 色の描画

static void SetVecRota( u16* rotaY, u16* rotaXZ, fx32 X, fx32 Y, fx32 Z );
static void SetVecsRotas( u16* rotaY, u16* rotaXZ, LIGHT_CONT_DATA* light );


//-----------------------------------------------------------------------------
//			変数
//=============================================================================
static int	MaterialDataNo = 0;

static u8	MaterialWinFlag=0;
static TCB_PTR	materialTCBData;
static int MaterialCount;			// カウンタ
static u16 MaterialrotaY[ 4 ];					// 回転角Y
static u16 MaterialrotaXZ[ 4 ];					// 回転角XZ

static int MT_InputCount;			// 入力カウンタ
static int MT_InputNow;				// 今の入力待ち時間
static GF_BGL_BMPWIN* D_M_win;		// ウィンドウ


// タイトル郡
static const u16 pD_M_str[] = {
	D_M_str14,
	D_M_str00,
	D_M_str01,
	D_M_str02,
	D_M_str03,
	D_M_str04,
	D_M_str05,
	D_M_str06,
	D_M_str07,
	D_M_str08,
	D_M_str09,
	D_M_str10,
	D_M_str11,
	D_M_str12,
	D_M_str13
};

#endif	// D_TOMOYA_MATERIAL_ON

//-------------------------------------
//	フォグと共通
//=====================================
#define	MT_INPUT_MAX	(12)		// キー入力操作用
#define MT_INPUT_MIN	(0)
#define MT_INPUT_SUB	(4)
#define D_M_MENU_X		(8)			// 表示位置用
#define D_M_MENU_Y		(8)
#define D_M_MENU_SPACE_Y	(8)
#define D_M_MENU_SPACE_X	(16)
#define D_M_NUM_X		(64)
#define D_M_KEY_X		(128)
#define	D_M_0		(28)
#define	D_M_1		(48)
#define	D_M_2		(68)
#define	D_M_3		(88)
#define D_M_SELECT	(108)
static void DrawNum( s32 num, u32 x, u32 y, GF_BGL_BMPWIN* win );// 数字の描画





//============================================================================
//		フォグ
//
//			フォグの設定、終了
//
//
//=============================================================================
//-----------------------------------------------------------------------------
//			構造体
//=============================================================================
//-----------------------------------------------------------------------------
//			プロトタイプ
//=============================================================================
static void StartFog( TCB_PTR tcb,void* work );	// フォグを設定
static void MainFog( TCB_PTR tcb,void* work);	// フォグメイン
static void EndFog( TCB_PTR tcb,void* work );	// フォグを終了

static void InputFog( int num );
static void DrawFog( int num );

//-----------------------------------------------------------------------------
//			変数
//=============================================================================
u8	FogFlag=0;
static TCB_PTR	FogTCBData;
static u8	Fog_DrawFlag = 0;

NNSG3dResMdl* groundMdl;

static int FOG_Count = 0;			// 今操作していること
static int FOG_InputCount;			// 入力カウンタ
static int FOG_InputNow;			// 今の入力待ち時間
static GF_BGL_BMPWIN* FOG_win;		// ウィンドウ
static int FOG_TBL_Count=0;			// フォグテーブル今操作しているところ

// 文字列郡

static const u16	fog_title[]={
	fog_title00,
	fog_title01,
	fog_title02,
	D_M_str13
};

enum{
	FOG_NORMAL_SET,
	FOG_COLOR_SET,
	FOG_TBL_SET,
	FOG_D_W,
	FOG_TITLE_NUM
};
#define		FOG_OFS_ADD	(0x20)

//#define		FOG_BG_ON
#ifdef FOG_BG_ON

static void BG2Move(TCB_PTR tcb,void* work);	// BG2を動かすタスク
#define		FOG_BG_SCROLL_COUNT	(1)
#define		FOG_BG_SCROLL_PAR	(4)
static TCB_PTR	FOG_BG_TASK = NULL;
static u32	Fog_BG_Count =0;		// BG面スクロールカウンタ

static int bg2_flag = 0;
#define		SCREEN_SIZE (32 * 32)
static u16 sScrnBuf[SCREEN_SIZE];

/*---------------------- Pallet Data  ---------------------------*/
const unsigned int d_64_256_bg_sclDT[8 * 3] = {
    0x628a7ffe, 0x6f0d6acb, 0x6aec6f2f, 0x77757352,        // 0000h
    0x51e6460d, 0x66f05a27, 0x41845a8f, 0x49c53943,
    0x41c73567, 0x4e2c5668, 0x62ad41cb, 0x566c2924,        // 0010h
    0x5eb1524f, 0x45e93566, 0x1ca16f55, 0x24e26b13,
    0x31442d02, 0x10607798, 0x7bba39aa, 0x7bdc779b,        // 0020h
    0x66c90820, 0x628a7ffe, 0x628a7ffe, 0x628a7ffe, 
};


/*---------------------- Character Data  -------------------------*/
const unsigned int d_64_256_bg_schDT[16 * 128] = {
    0x2b2b2b2b, 0x2b2b2b2b, 0x2b2b2b2b, 0x2b2b2b2b,        // 2b2bh
    0x2b2b2b2b, 0x2b2b2b2b, 0x2b2b2b2b, 0x2b2b2b2b,
    0x2b2b2b2b, 0x2b2b2b2b, 0x2b2b2b2b, 0x2b2b2b2b,
    0x2b2b2b2b, 0x2b2b2b2b, 0x2b2b2b2b, 0x2b2b2b2b,
    0x2b2b2b2b, 0x2b2b2b2b, 0x2b2b2b2b, 0x2b2b2b2b,        // 2b01h
    0x2b2b2b2b, 0x2b2b2b2b, 0x2b2b2b2b, 0x2b2b2b2b,
    0x2b2b2b2b, 0x2b2b2b2b, 0x2b2b2b2b, 0x0f2b2b2b,
    0x2b2b2b2b, 0x090d2b2b, 0x2b2b2b2b, 0x0f0f0d0f,
    0x2b2b2b2b, 0x2b2b2b2b, 0x2b2b2b2b, 0x2b2b2b2b,        // 2b02h
    0x2b2b2b2b, 0x01012b2b, 0x092b2b2b, 0x0201010a,
    0x0f0e0d2b, 0x0101010a, 0x090f0f0f, 0x1101010a,
    0x0a090f09, 0x11010101, 0x010a090f, 0x11010109,
    0x2b2b2b2b, 0x2b2b2b2b, 0x02012b2b, 0x04030302,        // 2b03h
    0x05020201, 0x04040403, 0x03050101, 0x06040404,
    0x04121110, 0x06060604, 0x17111016, 0x0b070603,
    0x1b111a1a, 0x0815171b, 0x17131b1b, 0x08080817,
    0x2b2b2b2b, 0x2b2b2b2b, 0x04030304, 0x2b2b0304,        // 2b04h
    0x06070706, 0x06070706, 0x07060b04, 0x07070707,
    0x06151413, 0x06070b06, 0x0c080808, 0x18181318,
    0x0c180808, 0x18180c18, 0x0c18080c, 0x0c0c0c18,
    0x2b2b2b2b, 0x2b2b2b2b, 0x2b2b2b2b, 0x2b2b2b2b,        // 2b05h
    0x2b2b0808, 0x2b2b2b2b, 0x0b0c0b06, 0x2b2b2b06,
    0x0707060b, 0x2b080b07, 0x07060c18, 0x13190b07,
    0x07060c18, 0x180b1c07, 0x0b0c1919, 0x1c060707,
    0x2b2b2b2b, 0x2b2b2b2b, 0x2b2b2b2b, 0x2b2b2b2b,        // 2b06h
    0x2b2b2b2b, 0x2b2b2b2b, 0x2b2b2b2b, 0x2b2b2b2b,
    0x2b2b2b2b, 0x2b2b2b2b, 0x2b2b2b0c, 0x2b2b2b2b,
    0x2b2b0b06, 0x2b2b2b2b, 0x0b0b0707, 0x2b2b2b2b,
    0x2b2b2b2b, 0x2b2b2b2b, 0x2b2b2b2b, 0x2b2b2b2b,        // 2b07h
    0x2b2b2b2b, 0x2b2b2b2b, 0x2b2b2b2b, 0x2b2b2b2b,
    0x2b2b2b2b, 0x2b2b2b2b, 0x2b2b2b2b, 0x2b2b2b2b,
    0x2b2b2b2b, 0x2b2b2b2b, 0x2b2b2b2b, 0x2b2b2b2b,
    0x2b2b2b2b, 0x2b2b2b2b, 0x2b2b2b2b, 0x2b2b2b2b,        // 2b2bh
    0x2b2b2b2b, 0x2b2b2b2b, 0x2b2b2b2b, 0x2b2b2b2b,
    0x2b2b2b2b, 0x2b2b2b2b, 0x2b2b2b2b, 0x2b2b2b2b,
    0x2b2b2b2b, 0x2b2b2b2b, 0x2b2b2b2b, 0x2b2b2b2b,
    0x2b2b2b2b, 0x2b2b2b2b, 0x2b2b2b2b, 0x2b2b2b2b,        // 2b01h
    0x2b2b2b2b, 0x2b2b2b2b, 0x2b2b2b2b, 0x2b2b2b2b,
    0x2b2b2b2b, 0x2b2b2b2b, 0x2b2b2b2b, 0x0f2b2b2b,
    0x2b2b2b2b, 0x090d2b2b, 0x2b2b2b2b, 0x0f0f0d0f,
    0x2b2b2b2b, 0x2b2b2b2b, 0x2b2b2b2b, 0x2b2b2b2b,        // 2b02h
    0x2b2b2b2b, 0x01012b2b, 0x092b2b2b, 0x0201010a,
    0x0f0e0d2b, 0x0101010a, 0x090f0f0f, 0x1101010a,
    0x0a090f09, 0x11010101, 0x010a090f, 0x11010109,
    0x2b2b2b2b, 0x2b2b2b2b, 0x02012b2b, 0x04030302,        // 2b03h
    0x05020201, 0x04040403, 0x03050101, 0x06040404,
    0x04121110, 0x06060604, 0x17111016, 0x0b070603,
    0x1b111a1a, 0x0815171b, 0x17131b1b, 0x08080817,
    0x2b2b2b2b, 0x2b2b2b2b, 0x04030304, 0x2b2b0304,        // 2b04h
    0x06070706, 0x06070706, 0x07060b04, 0x07070707,
    0x06151413, 0x06070b06, 0x0c080808, 0x18181318,
    0x0c180808, 0x18180c18, 0x0c18080c, 0x0c0c0c18,
    0x2b2b2b2b, 0x2b2b2b2b, 0x2b2b2b2b, 0x2b2b2b2b,        // 2b05h
    0x2b2b0808, 0x2b2b2b2b, 0x0b0c0b06, 0x2b2b2b06,
    0x0707060b, 0x2b080b07, 0x07060c18, 0x13190b07,
    0x07060c18, 0x180b1c07, 0x0b0c1919, 0x1c060707,
    0x2b2b2b2b, 0x2b2b2b2b, 0x2b2b2b2b, 0x2b2b2b2b,        // 2b06h
    0x2b2b2b2b, 0x2b2b2b2b, 0x2b2b2b2b, 0x2b2b2b2b,
    0x2b2b2b2b, 0x2b2b2b2b, 0x2b2b2b0c, 0x2b2b2b2b,
    0x2b2b0b06, 0x2b2b2b2b, 0x0b0b0707, 0x2b2b2b2b,
    0x2b2b2b2b, 0x2b2b2b2b, 0x2b2b2b2b, 0x2b2b2b2b,        // 2b07h
    0x2b2b2b2b, 0x2b2b2b2b, 0x2b2b2b2b, 0x2b2b2b2b,
    0x2b2b2b2b, 0x2b2b2b2b, 0x2b2b2b2b, 0x2b2b2b2b,
    0x2b2b2b2b, 0x2b2b2b2b, 0x2b2b2b2b, 0x2b2b2b2b,
    0x2b2b2b2b, 0x2b2b2b2b, 0x2b2b2b2b, 0x2b2b2b2b,        // 2b10h
    0x2b2b2b2b, 0x2b2b2b2b, 0x2b2b2b2b, 0x2b2b2b2b,
    0x2b2b2b2b, 0x0d2b2b2b, 0x2b2b2b2b, 0x232b2b2b,
    0x2b2b2b2b, 0x1d0e2b2b, 0x2b2b2b2b, 0x0e0e0e2b,
    0x1d2b2b2b, 0x0f090d0d, 0x0f0f2b2b, 0x0a0a0f0d,        // 2b11h
    0x1f0e0f2b, 0x0a0a0d1d, 0x201d0e0f, 0x21090f0d,
    0x0f1d0e0f, 0x1622bf0f, 0x0f0e0e20, 0x201f160d,
    0x0f090f0e, 0x161f2016, 0x0d0f090d, 0x1f1f0e1f,
    0x01010a0d, 0x1b020201, 0x0101010a, 0x03030502,        // 2b12h
    0x0201010a, 0x04030201, 0x01010a21, 0x04040111,
    0x11112121, 0x1317021b, 0x1a1a2121, 0x1b241b16,
    0x16090a09, 0x1b101b10, 0x1a020201, 0x151b1b1b,
    0x0604171b, 0x0c180c06, 0x0606171b, 0x180b0b06,        // 2b13h
    0x06041313, 0x0b0c180b, 0x0c0c130b, 0x0b0c0c0c,
    0x08150b17, 0x180c1813, 0x13041314, 0x19181308,
    0x0c0c141b, 0x19181813, 0x17141b15, 0x0c181808,
    0x180c0b0b, 0x190c0c0c, 0x0c0c070b, 0x070c0c0c,        // 2b14h
    0x0c181e07, 0x0707190c, 0x0c0c0b1e, 0x0722071e,
    0x19180c18, 0x1c220707, 0x1e190c0b, 0x1c1c0707,
    0x1c070707, 0x25071c07, 0x07070707, 0x1c1c0722,
    0x190c0c1e, 0x07070706, 0x1919191e, 0x19191e1e,        // 2b15h
    0x1e19191e, 0x1919191e, 0x1c1e1e1c, 0x1e19191e,
    0x221e1e1e, 0x1e1e1e22, 0x221c1c1c, 0x1c220722,
    0x221c1c25, 0x22222225, 0x22262525, 0x25252525,
    0x0707071c, 0x2b2b2b0b, 0x071c190c, 0x2b2b0b06,        // 2b16h
    0x07061919, 0x2b0b061c, 0x1e1e1e1e, 0x0b0b0707,
    0x071e1e1e, 0x06060707, 0x07071e1c, 0x1c07071c,
    0x1e070722, 0x1c071e19, 0x1e1c2222, 0x0707070b,
    0x2b2b2b2b, 0x2b2b2b2b, 0x2b2b2b2b, 0x2b2b2b2b,        // 2b17h
    0x2b2b2b2b, 0x2b2b2b2b, 0x2b2b2b2b, 0x2b2b2b2b,
    0x2b2b2b0c, 0x2b2b2b2b, 0x2b2b2b06, 0x2b2b2b2b,
    0x2b2b0c0b, 0x2b2b2b2b, 0x2b0c0b06, 0x2b2b2b2b,
    0x2b2b2b2b, 0x2b2b2b2b, 0x2b2b2b2b, 0x2b2b2b2b,        // 2b10h
    0x2b2b2b2b, 0x2b2b2b2b, 0x2b2b2b2b, 0x2b2b2b2b,
    0x2b2b2b2b, 0x0d2b2b2b, 0x2b2b2b2b, 0x232b2b2b,
    0x2b2b2b2b, 0x1d0e2b2b, 0x2b2b2b2b, 0x0e0e0e2b,
    0x1d2b2b2b, 0x0f090d0d, 0x0f0f2b2b, 0x0a0a0f0d,        // 2b11h
    0x1f0e0f2b, 0x0a0a0d1d, 0x201d0e0f, 0x21090f0d,
    0x0f1d0e0f, 0x1622bf0f, 0x0f0e0e20, 0x201f160d,
    0x0f090f0e, 0x161f2016, 0x0d0f090d, 0x1f1f0e1f,
    0x01010a0d, 0x1b020201, 0x0101010a, 0x03030502,        // 2b12h
    0x0201010a, 0x04030201, 0x01010a21, 0x04040111,
    0x11112121, 0x1317021b, 0x1a1a2121, 0x1b241b16,
    0x16090a09, 0x1b101b10, 0x1a020201, 0x151b1b1b,
    0x0604171b, 0x0c180c06, 0x0606171b, 0x180b0b06,        // 2b13h
    0x06041313, 0x0b0c180b, 0x0c0c130b, 0x0b0c0c0c,
    0x08150b17, 0x180c1813, 0x13041314, 0x19181308,
    0x0c0c141b, 0x19181813, 0x17141b15, 0x0c181808,
    0x180c0b0b, 0x190c0c0c, 0x0c0c070b, 0x070c0c0c,        // 2b14h
    0x0c181e07, 0x0707190c, 0x0c0c0b1e, 0x0722071e,
    0x19180c18, 0x1c220707, 0x1e190c0b, 0x1c1c0707,
    0x1c070707, 0x25071c07, 0x07070707, 0x1c1c0722,
    0x190c0c1e, 0x07070706, 0x1919191e, 0x19191e1e,        // 2b15h
    0x1e19191e, 0x1919191e, 0x1c1e1e1c, 0x1e19191e,
    0x221e1e1e, 0x1e1e1e22, 0x221c1c1c, 0x1c220722,
    0x221c1c25, 0x22222225, 0x22262525, 0x25252525,
    0x0707071c, 0x2b2b2b0b, 0x071c190c, 0x2b2b0b06,        // 2b16h
    0x07061919, 0x2b0b061c, 0x1e1e1e1e, 0x0b0b0707,
    0x071e1e1e, 0x06060707, 0x07071e1c, 0x1c07071c,
    0x1e070722, 0x1c071e19, 0x1e1c2222, 0x0707070b,
    0x2b2b2b2b, 0x2b2b2b2b, 0x2b2b2b2b, 0x2b2b2b2b,        // 2b17h
    0x2b2b2b2b, 0x2b2b2b2b, 0x2b2b2b2b, 0x2b2b2b2b,
    0x2b2b2b0c, 0x2b2b2b2b, 0x2b2b2b06, 0x2b2b2b2b,
    0x2b2b0c0b, 0x2b2b2b2b, 0x2b0c0b06, 0x2b2b2b2b,
    0x2b2b2b2b, 0x2022be2b, 0x2b2b2b2b, 0x22be0e1d,        // 2b20h
    0x2b2b2b2b, 0x0d0e201d, 0x0e2b2b2b, 0x0e201f20,
    0x22b2b2b0, 0x0d0e0e0d, 0x22b2b2b0, 0x0f0f0d0e,
    0x1f22b2b0, 0x0d0f0f20, 0x22be2b2b, 0x22bd0e1d,
    0x1f0d090d, 0x0921211f, 0x22b9090d, 0x0a211621,        // 2b21h
    0x0d09090f, 0x0a201f21, 0x0909090f, 0x090d0d0f,
    0x0f090f0f, 0x1f1a090f, 0x0a0f0f09, 0x110a0909,
    0x0a0d0d09, 0x01110a01, 0x0a210f0f, 0x0a090102,
    0x1a020502, 0x0b1b101b, 0x1a120505, 0x04131010,        // 2b22h
    0x11161103, 0x0404131a, 0x1111110a, 0x04060b1a,
    0x1a1b0a21, 0x0c03151b, 0x101b020a, 0x24111a10,
    0x1b120105, 0x0b171313, 0x1b110102, 0x0b131b15,
    0x0c141506, 0x19181819, 0x0c140b06, 0x07190c0b,        // 2b23h
    0x14140b06, 0x071c1e06, 0x08081904, 0x07070618,
    0x13142414, 0x07071813, 0x130c1414, 0x1c1e1918,
    0x0c040604, 0x0c180808, 0x14080b0b, 0x0c181808,
    0x221e1e1c, 0x221c1c1c, 0x221e191e, 0x25221c22,        // 2b24h
    0x221e191e, 0x25252225, 0x221e1919, 0x25221c22,
    0x1c1e1e07, 0x25221c07, 0x1e1e1c07, 0x221c1c1e,
    0x2207071e, 0x221c1c22, 0x1e19190c, 0x22221e1e,
    0x25252525, 0x25252626, 0x27272525, 0x22262627,        // 2b25h
    0x27272725, 0x22262727, 0x27272725, 0x22262727,
    0x27272725, 0x25252727, 0x27272525, 0x25252527,
    0x25252525, 0x25252525, 0x25252522, 0x25252525,
    0x07222222, 0x07070707, 0x22222222, 0x07070722,        // 2b26h
    0x22221c1c, 0x07071e07, 0x22071c1c, 0x190c0c19,
    0x1c071c22, 0x180c191e, 0x07222222, 0x180c1e1e,
    0x07070722, 0x18191c1e, 0x071c1c22, 0x191e1c07,
    0x2b0c0c1e, 0x2b2b2b2b, 0x13131819, 0x2b2b2b2b,        // 2b27h
    0x17180c06, 0x2b2b2b2b, 0x14180b1e, 0x2b2b2b14,
    0x08130b0b, 0x2b2b2b14, 0x130c0b0b, 0x2b2b2b08,
    0x080c0b19, 0x2b2b1308, 0x080c060b, 0x2b2b1408,
    0x2b2b2b2b, 0x2022be2b, 0x2b2b2b2b, 0x22be0e1d,        // 2b20h
    0x2b2b2b2b, 0x0d0e201d, 0x0e2b2b2b, 0x0e201f20,
    0x22b2b2b0, 0x0d0e0e0d, 0x22b2b2b0, 0x0f0f0d0e,
    0x1f22b2b0, 0x0d0f0f20, 0x22be2b2b, 0x22bd0e1d,
    0x1f0d090d, 0x0921211f, 0x22b9090d, 0x0a211621,        // 2b21h
    0x0d09090f, 0x0a201f21, 0x0909090f, 0x090d0d0f,
    0x0f090f0f, 0x1f1a090f, 0x0a0f0f09, 0x110a0909,
    0x0a0d0d09, 0x01110a01, 0x0a210f0f, 0x0a090102,
    0x1a020502, 0x0b1b101b, 0x1a120505, 0x04131010,        // 2b22h
    0x11161103, 0x0404131a, 0x1111110a, 0x04060b1a,
    0x1a1b0a21, 0x0c03151b, 0x101b020a, 0x24111a10,
    0x1b120105, 0x0b171313, 0x1b110102, 0x0b131b15,
    0x0c141506, 0x19181819, 0x0c140b06, 0x07190c0b,        // 2b23h
    0x14140b06, 0x071c1e06, 0x08081904, 0x07070618,
    0x13142414, 0x07071813, 0x130c1414, 0x1c1e1918,
    0x0c040604, 0x0c180808, 0x14080b0b, 0x0c181808,
    0x221e1e1c, 0x221c1c1c, 0x221e191e, 0x25221c22,        // 2b24h
    0x221e191e, 0x25252225, 0x221e1919, 0x25221c22,
    0x1c1e1e07, 0x25221c07, 0x1e1e1c07, 0x221c1c1e,
    0x2207071e, 0x221c1c22, 0x1e19190c, 0x22221e1e,
    0x25252525, 0x25252626, 0x27272525, 0x22262627,        // 2b25h
    0x27272725, 0x22262727, 0x27272725, 0x22262727,
    0x27272725, 0x25252727, 0x27272525, 0x25252527,
    0x25252525, 0x25252525, 0x25252522, 0x25252525,
    0x07222222, 0x07070707, 0x22222222, 0x07070722,        // 2b26h
    0x22221c1c, 0x07071e07, 0x22071c1c, 0x190c0c19,
    0x1c071c22, 0x180c191e, 0x07222222, 0x180c1e1e,
    0x07070722, 0x18191c1e, 0x071c1c22, 0x191e1c07,
    0x2b0c0c1e, 0x2b2b2b2b, 0x13131819, 0x2b2b2b2b,        // 2b27h
    0x17180c06, 0x2b2b2b2b, 0x14180b1e, 0x2b2b2b14,
    0x08130b0b, 0x2b2b2b14, 0x130c0b0b, 0x2b2b2b08,
    0x080c0b19, 0x2b2b1308, 0x080c060b, 0x2b2b1408,
    0x201d2b2b, 0x090f0e23, 0x201f2b2b, 0x090f0f20,        // 2b30h
    0x0d0d22b0, 0x090f0f0d, 0x0d0d0e2b, 0x090f0f0f,
    0x0d0d22b0, 0x0f090f0d, 0x0d0e1d2b, 0x0e090f0f,
    0x0e1d1d2b, 0x22bf0f0f, 0x1d1f22b0, 0x0d0e0f0f,
    0x0f22bd09, 0x02020202, 0x0f0e0d0a, 0x0201010a,        // 2b31h
    0x090f090a, 0x020a010a, 0x0d210d0f, 0x0502010a,
    0x1f1f231d, 0x0a0a0a20, 0x20201d23, 0x1f20161d,
    0x1f201d1d, 0x201f1d1d, 0x1f1f0e0e, 0x211d1f1f,
    0x1b111102, 0x1311241b, 0x11112112, 0x1b1b1110,        // 2b32h
    0x1a111b02, 0x141b1116, 0x10111103, 0x13150b13,
    0x15101a11, 0x04040404, 0x1b1a1a1f, 0x06040415,
    0x101a1a1a, 0x04040413, 0x1b112111, 0x24241b1b,
    0x14141b14, 0x190c0c13, 0x08131414, 0x18180c08,        // 2b33h
    0x08142414, 0x180c0b0c, 0x08131713, 0x0c0b070b,
    0x17131315, 0x0b06070b, 0x15241404, 0x080c0406,
    0x13141b0b, 0x0814130c, 0x1414241b, 0x13081314,
    0x1919190c, 0x25071e19, 0x190c1818, 0x22221e19,        // 2b34h
    0x19191813, 0x22221c19, 0x0c190c0c, 0x07220719,
    0x0b18180c, 0x07070706, 0x07190c18, 0x07070707,
    0x1e181813, 0x07070707, 0x180c1813, 0x07070618,
    0x25222222, 0x22252525, 0x22072222, 0x07222222,        // 2b35h
    0x22072222, 0x1e071e1c, 0x1c070707, 0x1e071c1e,
    0x07070707, 0x07070707, 0x07070707, 0x071e061e,
    0x07070707, 0x1c1e0b1e, 0x07070707, 0x1c1e0707,
    0x07071c07, 0x06061c07, 0x071e1e07, 0x06061c1c,        // 2b36h
    0x0719191e, 0x06061c06, 0x1e1e0619, 0x1c1c060b,
    0x180c0707, 0x06071c19, 0x18181e22, 0x06061c0c,
    0x18190707, 0x0606060c, 0x06060707, 0x06060604,
    0x0b06060b, 0x2b2b1717, 0x0b0c0b0c, 0x2b2b0403,        // 2b37h
    0x1914180b, 0x2b130b04, 0x15170606, 0x2b130c0c,
    0x0b0b0606, 0x2b131b14, 0x06060606, 0x2b041413,
    0x030b0606, 0x2b0b1413, 0x24241706, 0x2b0b1414,
    0x201d2b2b, 0x090f0e23, 0x201f2b2b, 0x090f0f20,        // 2b30h
    0x0d0d22b0, 0x090f0f0d, 0x0d0d0e2b, 0x090f0f0f,
    0x0d0d22b0, 0x0f090f0d, 0x0d0e1d2b, 0x0e090f0f,
    0x0e1d1d2b, 0x22bf0f0f, 0x1d1f22b0, 0x0d0e0f0f,
    0x0f22bd09, 0x02020202, 0x0f0e0d0a, 0x0201010a,        // 2b31h
    0x090f090a, 0x020a010a, 0x0d210d0f, 0x0502010a,
    0x1f1f231d, 0x0a0a0a20, 0x20201d23, 0x1f20161d,
    0x1f201d1d, 0x201f1d1d, 0x1f1f0e0e, 0x211d1f1f,
    0x1b111102, 0x1311241b, 0x11112112, 0x1b1b1110,        // 2b32h
    0x1a111b02, 0x141b1116, 0x10111103, 0x13150b13,
    0x15101a11, 0x04040404, 0x1b1a1a1f, 0x06040415,
    0x101a1a1a, 0x04040413, 0x1b112111, 0x24241b1b,
    0x14141b14, 0x190c0c13, 0x08131414, 0x18180c08,        // 2b33h
    0x08142414, 0x180c0b0c, 0x08131713, 0x0c0b070b,
    0x17131315, 0x0b06070b, 0x15241404, 0x080c0406,
    0x13141b0b, 0x0814130c, 0x1414241b, 0x13081314,
    0x1919190c, 0x25071e19, 0x190c1818, 0x22221e19,        // 2b34h
    0x19191813, 0x22221c19, 0x0c190c0c, 0x07220719,
    0x0b18180c, 0x07070706, 0x07190c18, 0x07070707,
    0x1e181813, 0x07070707, 0x180c1813, 0x07070618,
    0x25222222, 0x22252525, 0x22072222, 0x07222222,        // 2b35h
    0x22072222, 0x1e071e1c, 0x1c070707, 0x1e071c1e,
    0x07070707, 0x07070707, 0x07070707, 0x071e061e,
    0x07070707, 0x1c1e0b1e, 0x07070707, 0x1c1e0707,
    0x07071c07, 0x06061c07, 0x071e1e07, 0x06061c1c,        // 2b36h
    0x0719191e, 0x06061c06, 0x1e1e0619, 0x1c1c060b,
    0x180c0707, 0x06071c19, 0x18181e22, 0x06061c0c,
    0x18190707, 0x0606060c, 0x06060707, 0x06060604,
    0x0b06060b, 0x2b2b1717, 0x0b0c0b0c, 0x2b2b0403,        // 2b37h
    0x1914180b, 0x2b130b04, 0x15170606, 0x2b130c0c,
    0x0b0b0606, 0x2b131b14, 0x06060606, 0x2b041413,
    0x030b0606, 0x2b0b1413, 0x24241706, 0x2b0b1414,
    0x2022be2b, 0x0f0d090f, 0x0e1d22b0, 0x2021210f,        // 2b40h
    0x0d201d2b, 0x1f0f0f0f, 0x0d0e22b0, 0x0f090d0d,
    0x0d0d0e2b, 0x090f0d0d, 0x0d0d0e2b, 0x0f090f0f,
    0x0f0e2b2b, 0x1f0f0f0f, 0x20232b2b, 0x230e0f0f,
    0x1d0e0909, 0x11211f1d, 0x0d09090d, 0x090d22bd,        // 2b41h
    0x0a0a0d1f, 0x020a090a, 0x0a09201f, 0x0201010a,
    0x09090d0e, 0x01020a0f, 0x0909090d, 0x020a0d0f,
    0x0a090f1d, 0x0922be0a, 0x090f0920, 0x161f210f,
    0x1b1b1a1a, 0x1b111010, 0x05151201, 0x17030117,        // 2b42h
    0x05030502, 0x04041701, 0x02010502, 0x04041717,
    0x05010101, 0x03151112, 0x02010102, 0x151b1112,
    0x17120a0a, 0x1b161202, 0x11111a1f, 0x12161112,
    0x1314141b, 0x08131313, 0x1314141b, 0x13140813,        // 2b43h
    0x24241013, 0x17241b1b, 0x13131504, 0x17241414,
    0x13130404, 0x04132413, 0x04040404, 0x04031703,
    0x04060404, 0x04040404, 0x04040604, 0x03030b04,
    0x0b060c08, 0x07070b0b, 0x0604060b, 0x0604060c,        // 2b44h
    0x0b040606, 0x0b0b0617, 0x0b040606, 0x0b040404,
    0x0b0b0406, 0x0b0b190b, 0x15030304, 0x0b15130b,
    0x03030304, 0x1b0b0b0b, 0x03030b0b, 0x240b0b03,
    0x071c061c, 0x06060707, 0x06060606, 0x06060606,        // 2b45h
    0x0606040b, 0x0c0b0404, 0x06060b0c, 0x170c0406,
    0x06040b03, 0x0404040b, 0x0b041513, 0x040b150b,
    0x0b040b1b, 0x15151503, 0x030b0414, 0x03170303,
    0x0606071c, 0x0b0b0b0b, 0x0604040b, 0x04030b0b,        // 2b46h
    0x0b040b15, 0x1504040b, 0x0b150b0b, 0x0b040603,
    0x0b17150b, 0x04040b04, 0x0b150b03, 0x04151503,
    0x15040404, 0x04030303, 0x15040404, 0x03121215,
    0x13241413, 0x2b051b1b, 0x04131b17, 0x2b151503,        // 2b47h
    0x040b1b17, 0x2b171704, 0x13150b17, 0x2b010117,
    0x10111504, 0x2b010512, 0x10111504, 0x2b01051b,
    0x11130504, 0x2b2b0312, 0x13111703, 0x2b2b0104,
    0x2022be2b, 0x0f0d090f, 0x0e1d22b0, 0x2021210f,        // 2b40h
    0x0d201d2b, 0x1f0f0f0f, 0x0d0e22b0, 0x0f090d0d,
    0x0d0d0e2b, 0x090f0d0d, 0x0d0d0e2b, 0x0f090f0f,
    0x0f0e2b2b, 0x1f0f0f0f, 0x20232b2b, 0x230e0f0f,
    0x1d0e0909, 0x11211f1d, 0x0d09090d, 0x090d22bd,        // 2b41h
    0x0a0a0d1f, 0x020a090a, 0x0a09201f, 0x0201010a,
    0x09090d0e, 0x01020a0f, 0x0909090d, 0x020a0d0f,
    0x0a090f1d, 0x0922be0a, 0x090f0920, 0x161f210f,
    0x1b1b1a1a, 0x1b111010, 0x05151201, 0x17030117,        // 2b42h
    0x05030502, 0x04041701, 0x02010502, 0x04041717,
    0x05010101, 0x03151112, 0x02010102, 0x151b1112,
    0x17120a0a, 0x1b161202, 0x11111a1f, 0x12161112,
    0x1314141b, 0x08131313, 0x1314141b, 0x13140813,        // 2b43h
    0x24241013, 0x17241b1b, 0x13131504, 0x17241414,
    0x13130404, 0x04132413, 0x04040404, 0x04031703,
    0x04060404, 0x04040404, 0x04040604, 0x03030b04,
    0x0b060c08, 0x07070b0b, 0x0604060b, 0x0604060c,        // 2b44h
    0x0b040606, 0x0b0b0617, 0x0b040606, 0x0b040404,
    0x0b0b0406, 0x0b0b190b, 0x15030304, 0x0b15130b,
    0x03030304, 0x1b0b0b0b, 0x03030b0b, 0x240b0b03,
    0x071c061c, 0x06060707, 0x06060606, 0x06060606,        // 2b45h
    0x0606040b, 0x0c0b0404, 0x06060b0c, 0x170c0406,
    0x06040b03, 0x0404040b, 0x0b041513, 0x040b150b,
    0x0b040b1b, 0x15151503, 0x030b0414, 0x03170303,
    0x0606071c, 0x0b0b0b0b, 0x0604040b, 0x04030b0b,        // 2b46h
    0x0b040b15, 0x1504040b, 0x0b150b0b, 0x0b040603,
    0x0b17150b, 0x04040b04, 0x0b150b03, 0x04151503,
    0x15040404, 0x04030303, 0x15040404, 0x03121215,
    0x13241413, 0x2b051b1b, 0x04131b17, 0x2b151503,        // 2b47h
    0x040b1b17, 0x2b171704, 0x13150b17, 0x2b010117,
    0x10111504, 0x2b010512, 0x10111504, 0x2b01051b,
    0x11130504, 0x2b2b0312, 0x13111703, 0x2b2b0104,
    0x1d282b2b, 0x1d231d1d, 0x23282b2b, 0x0e231d1d,        // 2b50h
    0x22b2b2b0, 0x0f1d1d0e, 0x22b2b2b0, 0x090d0d0e,
    0x0e2b2b2b, 0x090f0e0d, 0x2b2b2b2b, 0x0f0d22be,
    0x2b2b2b2b, 0x0e0d0d0e, 0x2b2b2b2b, 0x2322be2b,
    0x22bf0a0f, 0x0d201d1d, 0x0d0a0909, 0x011f1f20,        // 2b51h
    0x0a2122ba, 0x0f0d0d0f, 0x0a1f0e09, 0x0f210f01,
    0x0a0a0e0d, 0x2022b90a, 0x1d0d0d0d, 0x211d22be,
    0x231d1d1d, 0x0a1d231d, 0x23282323, 0x011f1f0f,
    0x1a1a1209, 0x03131111, 0x16120305, 0x121b101a,        // 2b52h
    0x21111209, 0x12161111, 0x1221090a, 0x1b160911,
    0x0101120f, 0x11161a01, 0x0212090a, 0x121a1101,
    0x1e180102, 0x120a1212, 0x14150202, 0x12091b16,
    0x03050303, 0x03031703, 0x0403171b, 0x15151504,        // 2b53h
    0x04030505, 0x17150304, 0x04030505, 0x03030304,
    0x03030502, 0x02020404, 0x03051201, 0x17050403,
    0x03051201, 0x05050303, 0x05021212, 0x02050305,
    0x15031515, 0x17171515, 0x03151b1b, 0x04040b15,        // 2b54h
    0x12101b17, 0x04040315, 0x1b130504, 0x03040312,
    0x03040101, 0x03030305, 0x0305171b, 0x05030303,
    0x03050502, 0x05030303, 0x03051212, 0x01050303,
    0x15050415, 0x04150517, 0x15151504, 0x04151512,        // 2b55h
    0x01050304, 0x04041513, 0x05150303, 0x04040305,
    0x05050503, 0x03040217, 0x05050502, 0x03030117,
    0x03011b02, 0x05030303, 0x03051112, 0x01050503,
    0x03040404, 0x17101715, 0x03040404, 0x121b1205,        // 2b56h
    0x05030304, 0x12020215, 0x05040403, 0x01121705,
    0x05030303, 0x01010205, 0x01050505, 0x1b05111a,
    0x1b030505, 0x12011111, 0x01121212, 0x01111205,
    0x031b1203, 0x2b2b1205, 0x05111705, 0x2b2b2111,        // 2b57h
    0x1b1b0205, 0x2b2b2b16, 0x11010502, 0x2b2b2b16,
    0x02011212, 0x2b2b2b12, 0x2912011b, 0x2b2b2b2b,
    0x12120111, 0x2b2b2b2b, 0x2b091112, 0x2b2b2b2b,
    0x1d282b2b, 0x1d231d1d, 0x23282b2b, 0x0e231d1d,        // 2b50h
    0x22b2b2b0, 0x0f1d1d0e, 0x22b2b2b0, 0x090d0d0e,
    0x0e2b2b2b, 0x090f0e0d, 0x2b2b2b2b, 0x0f0d22be,
    0x2b2b2b2b, 0x0e0d0d0e, 0x2b2b2b2b, 0x2322be2b,
    0x22bf0a0f, 0x0d201d1d, 0x0d0a0909, 0x011f1f20,        // 2b51h
    0x0a2122ba, 0x0f0d0d0f, 0x0a1f0e09, 0x0f210f01,
    0x0a0a0e0d, 0x2022b90a, 0x1d0d0d0d, 0x211d22be,
    0x231d1d1d, 0x0a1d231d, 0x23282323, 0x011f1f0f,
    0x1a1a1209, 0x03131111, 0x16120305, 0x121b101a,        // 2b52h
    0x21111209, 0x12161111, 0x1221090a, 0x1b160911,
    0x0101120f, 0x11161a01, 0x0212090a, 0x121a1101,
    0x1e180102, 0x120a1212, 0x14150202, 0x12091b16,
    0x03050303, 0x03031703, 0x0403171b, 0x15151504,        // 2b53h
    0x04030505, 0x17150304, 0x04030505, 0x03030304,
    0x03030502, 0x02020404, 0x03051201, 0x17050403,
    0x03051201, 0x05050303, 0x05021212, 0x02050305,
    0x15031515, 0x17171515, 0x03151b1b, 0x04040b15,        // 2b54h
    0x12101b17, 0x04040315, 0x1b130504, 0x03040312,
    0x03040101, 0x03030305, 0x0305171b, 0x05030303,
    0x03050502, 0x05030303, 0x03051212, 0x01050303,
    0x15050415, 0x04150517, 0x15151504, 0x04151512,        // 2b55h
    0x01050304, 0x04041513, 0x05150303, 0x04040305,
    0x05050503, 0x03040217, 0x05050502, 0x03030117,
    0x03011b02, 0x05030303, 0x03051112, 0x01050503,
    0x03040404, 0x17101715, 0x03040404, 0x121b1205,        // 2b56h
    0x05030304, 0x12020215, 0x05040403, 0x01121705,
    0x05030303, 0x01010205, 0x01050505, 0x1b05111a,
    0x1b030505, 0x12011111, 0x01121212, 0x01111205,
    0x031b1203, 0x2b2b1205, 0x05111705, 0x2b2b2111,        // 2b57h
    0x1b1b0205, 0x2b2b2b16, 0x11010502, 0x2b2b2b16,
    0x02011212, 0x2b2b2b12, 0x2912011b, 0x2b2b2b2b,
    0x12120111, 0x2b2b2b2b, 0x2b091112, 0x2b2b2b2b,
    0x2b2b2b2b, 0x23281d2b, 0x2b2b2b2b, 0x23282b2b,        // 2b60h
    0x2b2b2b2b, 0x232b2b2b, 0x2b2b2b2b, 0x232b2b2b,
    0x2b2b2b2b, 0x2b2b2b2b, 0x2b2b2b2b, 0x2b2b2b2b,
    0x2b2b2b2b, 0x2b2b2b2b, 0x2b2b2b2b, 0x2b2b2b2b,
    0x1f231d23, 0x091d0f0e, 0x1f1d1d1d, 0x201d201f,        // 2b61h
    0x1d1d1d23, 0x20231d1d, 0x1d1d2323, 0x0e201f23,
    0x1f1d201d, 0x22bf1d23, 0x1f1f232b, 0x1d0d1623,
    0x1f232b2b, 0x1d1d1f23, 0x1d2b2b2b, 0x1f1d1f1d,
    0x1f160a02, 0x1a16211d, 0x1f22be0a, 0x1f23231f,        // 2b62h
    0x1d0e0e0e, 0x1d1d1d1d, 0x1d1f1d1d, 0x1f1f1d1d,
    0x1d201d1d, 0x0d0f201f, 0x201d1d1d, 0x2902201d,
    0x1d0e2323, 0x090a0d23, 0x231d1d1f, 0x0f0a0a1d,
    0x031b1611, 0x05020503, 0x0112161f, 0x05052902,        // 2b63h
    0x12291a1f, 0x09010212, 0x09291220, 0x1f0d0a12,
    0x09290512, 0x0d1f110a, 0x29292929, 0x29090a01,
    0x29120a0a, 0x01292929, 0x2929090f, 0x01091229,
    0x05111f12, 0x12011205, 0x111f1105, 0x11011201,        // 2b64h
    0x1f1f1a09, 0x0a120511, 0x16211f1f, 0x01122911,
    0x09090a11, 0x0a290202, 0x29292929, 0x1f12091b,
    0x0d120229, 0x0d090916, 0x1d0d0a29, 0x120a0d1f,
    0x05030212, 0x01020205, 0x05030212, 0x05020205,        // 2b65h
    0x03050501, 0x03291b12, 0x02050505, 0x03011111,
    0x05050501, 0x29122929, 0x05022921, 0x01120105,
    0x02022909, 0x09090205, 0x02020229, 0x09120205,
    0x01091f21, 0x161f0d09, 0x12161601, 0x1f16111b,        // 2b66h
    0x12110504, 0x21160d01, 0x29010102, 0x12160f01,
    0x01020201, 0x021b1202, 0x12021229, 0x2b05020a,
    0x12121201, 0x2b2b2912, 0x2909110a, 0x2b2b2b29,
    0x2b201101, 0x2b2b2b2b, 0x2b2b2912, 0x2b2b2b2b,        // 2b67h
    0x2b2b2b01, 0x2b2b2b2b, 0x2b2b2b29, 0x2b2b2b2b,
    0x2b2b2b2b, 0x2b2b2b2b, 0x2b2b2b2b, 0x2b2b2b2b,
    0x2b2b2b2b, 0x2b2b2b2b, 0x2b2b2b2b, 0x2b2b2b2b,
    0x2b2b2b2b, 0x23281d2b, 0x2b2b2b2b, 0x23282b2b,        // 2b60h
    0x2b2b2b2b, 0x232b2b2b, 0x2b2b2b2b, 0x232b2b2b,
    0x2b2b2b2b, 0x2b2b2b2b, 0x2b2b2b2b, 0x2b2b2b2b,
    0x2b2b2b2b, 0x2b2b2b2b, 0x2b2b2b2b, 0x2b2b2b2b,
    0x1f231d23, 0x091d0f0e, 0x1f1d1d1d, 0x201d201f,        // 2b61h
    0x1d1d1d23, 0x20231d1d, 0x1d1d2323, 0x0e201f23,
    0x1f1d201d, 0x22bf1d23, 0x1f1f232b, 0x1d0d1623,
    0x1f232b2b, 0x1d1d1f23, 0x1d2b2b2b, 0x1f1d1f1d,
    0x1f160a02, 0x1a16211d, 0x1f22be0a, 0x1f23231f,        // 2b62h
    0x1d0e0e0e, 0x1d1d1d1d, 0x1d1f1d1d, 0x1f1f1d1d,
    0x1d201d1d, 0x0d0f201f, 0x201d1d1d, 0x2902201d,
    0x1d0e2323, 0x090a0d23, 0x231d1d1f, 0x0f0a0a1d,
    0x031b1611, 0x05020503, 0x0112161f, 0x05052902,        // 2b63h
    0x12291a1f, 0x09010212, 0x09291220, 0x1f0d0a12,
    0x09290512, 0x0d1f110a, 0x29292929, 0x29090a01,
    0x29120a0a, 0x01292929, 0x2929090f, 0x01091229,
    0x05111f12, 0x12011205, 0x111f1105, 0x11011201,        // 2b64h
    0x1f1f1a09, 0x0a120511, 0x16211f1f, 0x01122911,
    0x09090a11, 0x0a290202, 0x29292929, 0x1f12091b,
    0x0d120229, 0x0d090916, 0x1d0d0a29, 0x120a0d1f,
    0x05030212, 0x01020205, 0x05030212, 0x05020205,        // 2b65h
    0x03050501, 0x03291b12, 0x02050505, 0x03011111,
    0x05050501, 0x29122929, 0x05022921, 0x01120105,
    0x02022909, 0x09090205, 0x02020229, 0x09120205,
    0x01091f21, 0x161f0d09, 0x12161601, 0x1f16111b,        // 2b66h
    0x12110504, 0x21160d01, 0x29010102, 0x12160f01,
    0x01020201, 0x021b1202, 0x12021229, 0x2b05020a,
    0x12121201, 0x2b2b2912, 0x2909110a, 0x2b2b2b29,
    0x2b201101, 0x2b2b2b2b, 0x2b2b2912, 0x2b2b2b2b,        // 2b67h
    0x2b2b2b01, 0x2b2b2b2b, 0x2b2b2b29, 0x2b2b2b2b,
    0x2b2b2b2b, 0x2b2b2b2b, 0x2b2b2b2b, 0x2b2b2b2b,
    0x2b2b2b2b, 0x2b2b2b2b, 0x2b2b2b2b, 0x2b2b2b2b,
    0x2b2b2b2b, 0x2b2b2b2b, 0x2b2b2b2b, 0x2b2b2b2b,        // 2b70h
    0x2b2b2b2b, 0x2b2b2b2b, 0x2b2b2b2b, 0x2b2b2b2b,
    0x2b2b2b2b, 0x2b2b2b2b, 0x2b2b2b2b, 0x2b2b2b2b,
    0x2b2b2b2b, 0x2b2b2b2b, 0x2b2b2b2b, 0x2b2b2b2b,
    0x2b2b2b2b, 0x22bd2123, 0x2b2b2b2b, 0x0d0f2b2b,        // 2b71h
    0x2b2b2b2b, 0x0d2b2b2b, 0x2b2b2b2b, 0x2b2b2b2b,
    0x2b2b2b2b, 0x2b2b2b2b, 0x2b2b2b2b, 0x2b2b2b2b,
    0x2b2b2b2b, 0x2b2b2b2b, 0x2b2b2b2b, 0x2b2b2b2b,
    0x1d231d1d, 0x0d0d0f1f, 0x20201f20, 0x1d1f0a0d,        // 2b72h
    0x0909090d, 0x0e090a0a, 0x2022bd2b, 0x0a0a0a0e,
    0x232b2b2b, 0x0a091d23, 0x2b2b2b2b, 0x09092b2b,
    0x2b2b2b2b, 0x2b2b2b2b, 0x2b2b2b2b, 0x2b2b2b2b,
    0x090a090d, 0x12090d0d, 0x0e0e22bf, 0x01010e20,        // 2b73h
    0x290d1d0d, 0x0d110d0a, 0x010e231d, 0x230d0502,
    0x1d1d22be, 0x23210a0e, 0x22be090a, 0x1d231f1d,
    0x090a2b2b, 0x1d1f2020, 0x2b2b2b2b, 0x2b2b2b2b,
    0x1f1d0d29, 0x22bd201d, 0x211f2112, 0x20112120,        // 2b74h
    0x1621201f, 0x09161d0d, 0x1d21201f, 0x1d1d1d23,
    0x0d202121, 0x201f210d, 0x0f0d22bd, 0x1f1d22bf,
    0x0d201d1d, 0x2b2b1d1d, 0x2b2b2b2b, 0x2b2b2b2b,
    0x2912090f, 0x0a292929, 0x121d2021, 0x090a0912,        // 2b75h
    0x091d210a, 0x09091112, 0x0f1d1111, 0x2b090a0f,
    0x091d1d1d, 0x2b2b2b09, 0x2b2b1d1d, 0x2b2b2b2b,
    0x2b2b2b2b, 0x2b2b2b2b, 0x2b2b2b2b, 0x2b2b2b2b,
    0x0912120a, 0x2b2b2b2b, 0x2b2b1201, 0x2b2b2b2b,        // 2b76h
    0x2b2b2b0a, 0x2b2b2b2b, 0x2b2b2b2b, 0x2b2b2b2b,
    0x2b2b2b2b, 0x2b2b2b2b, 0x2b2b2b2b, 0x2b2b2b2b,
    0x2b2b2b2b, 0x2b2b2b2b, 0x2b2b2b2b, 0x2b2b2b2b,
    0x2b2b2b2b, 0x2b2b2b2b, 0x2b2b2b2b, 0x2b2b2b2b,        // 2b77h
    0x2b2b2b2b, 0x2b2b2b2b, 0x2b2b2b2b, 0x2b2b2b2b,
    0x2b2b2b2b, 0x2b2b2b2b, 0x2b2b2b2b, 0x2b2b2b2b,
    0x2b2b2b2b, 0x2b2b2b2b, 0x2b2b2b2b, 0x2b2b2b2b,
    0x2b2b2b2b, 0x2b2b2b2b, 0x2b2b2b2b, 0x2b2b2b2b,        // 2b70h
    0x2b2b2b2b, 0x2b2b2b2b, 0x2b2b2b2b, 0x2b2b2b2b,
    0x2b2b2b2b, 0x2b2b2b2b, 0x2b2b2b2b, 0x2b2b2b2b,
    0x2b2b2b2b, 0x2b2b2b2b, 0x2b2b2b2b, 0x2b2b2b2b,
    0x2b2b2b2b, 0x22bd2123, 0x2b2b2b2b, 0x0d0f2b2b,        // 2b71h
    0x2b2b2b2b, 0x0d2b2b2b, 0x2b2b2b2b, 0x2b2b2b2b,
    0x2b2b2b2b, 0x2b2b2b2b, 0x2b2b2b2b, 0x2b2b2b2b,
    0x2b2b2b2b, 0x2b2b2b2b, 0x2b2b2b2b, 0x2b2b2b2b,
    0x1d231d1d, 0x0d0d0f1f, 0x20201f20, 0x1d1f0a0d,        // 2b72h
    0x0909090d, 0x0e090a0a, 0x2022bd2b, 0x0a0a0a0e,
    0x232b2b2b, 0x0a091d23, 0x2b2b2b2b, 0x09092b2b,
    0x2b2b2b2b, 0x2b2b2b2b, 0x2b2b2b2b, 0x2b2b2b2b,
    0x090a090d, 0x12090d0d, 0x0e0e22bf, 0x01010e20,        // 2b73h
    0x290d1d0d, 0x0d110d0a, 0x010e231d, 0x230d0502,
    0x1d1d22be, 0x23210a0e, 0x22be090a, 0x1d231f1d,
    0x090a2b2b, 0x1d1f2020, 0x2b2b2b2b, 0x2b2b2b2b,
    0x1f1d0d29, 0x22bd201d, 0x211f2112, 0x20112120,        // 2b74h
    0x1621201f, 0x09161d0d, 0x1d21201f, 0x1d1d1d23,
    0x0d202121, 0x201f210d, 0x0f0d22bd, 0x1f1d22bf,
    0x0d201d1d, 0x2b2b1d1d, 0x2b2b2b2b, 0x2b2b2b2b,
    0x2912090f, 0x0a292929, 0x121d2021, 0x090a0912,        // 2b75h
    0x091d210a, 0x09091112, 0x0f1d1111, 0x2b090a0f,
    0x091d1d1d, 0x2b2b2b09, 0x2b2b1d1d, 0x2b2b2b2b,
    0x2b2b2b2b, 0x2b2b2b2b, 0x2b2b2b2b, 0x2b2b2b2b,
    0x0912120a, 0x2b2b2b2b, 0x2b2b1201, 0x2b2b2b2b,        // 2b76h
    0x2b2b2b0a, 0x2b2b2b2b, 0x2b2b2b2b, 0x2b2b2b2b,
    0x2b2b2b2b, 0x2b2b2b2b, 0x2b2b2b2b, 0x2b2b2b2b,
    0x2b2b2b2b, 0x2b2b2b2b, 0x2b2b2b2b, 0x2b2b2b2b,
    0x2b2b2b2b, 0x2b2b2b2b, 0x2b2b2b2b, 0x2b2b2b2b,        // 2b77h
    0x2b2b2b2b, 0x2b2b2b2b, 0x2b2b2b2b, 0x2b2b2b2b,
    0x2b2b2b2b, 0x2b2b2b2b, 0x2b2b2b2b, 0x2b2b2b2b,
    0x2b2b2b2b, 0x2b2b2b2b, 0x2b2b2b2b, 0x2b2b2b2b
};
#endif

#if 0
//=============================================================================
//
//		ターンテーブル	
//
//=============================================================================
//-----------------------------------------------------------------------------
//			定数
//=============================================================================
#define D_SAMPLING_RATE (16000)		// レート
#define D_SAMPLING_TIME     (10)	// サンプリング(秒)

#define D_CHANNEL_NO (7)			// サウンドチャンネル

#define D_WAVE_SAMPLE ( D_SAMPLING_RATE * D_SAMPLING_TIME )	// バッファサイズ

#define	D_DJ_SPEED	(32768/2)	// tp座標が１進むときのスピード
//-----------------------------------------------------------------------------
//			構造体
//=============================================================================


//-----------------------------------------------------------------------------
//			プロトタイプ宣言
//=============================================================================
static void D_MicCallback( MICResult /**/, void* /**/ );
static void StartWaveMic( TCB_PTR tcb,void* work );	// ウェーブマイクを設定
static void MainWaveMic( TCB_PTR tcb,void* work);	// ウェーブマイクメイン
static void EndWaveMic( TCB_PTR tcb,void* work );	// ウェーブマイクを終了

static void WaveInput(u32 num);		// 入力
static void WaveStartOutPut(u32 Speed);
static void WaveDataReturn(s16* pWaveData, u32 LoopStart);

//-----------------------------------------------------------------------------
//			変数
//=============================================================================
static s16 D_WaveBuffer[ D_WAVE_SAMPLE ] ATTRIBUTE_ALIGN(32);
static MICAutoParam D_MicParam;	// オートサンプリングパラメータ
static NNSSndWaveOutHandle D_WaveOutHandle;	// サウンドハンドル

static u8	WaveMicFlag=0;		// WaveMic実行中:1
static TCB_PTR	WaveMicTCBData;	// タスクデータ
static s32	WaveNum=0;			// 実行中の処理
static u32	WaveSpeed = 32768;	// スピード
static u32	WavePan = 64;		// パン(スピーカーの左右のボリューム)
static s32	WaveNo=0;			// 今の実行中の配列位置
static TPData	WaveTP;			// タッチパネル情報保存用
static u8	WaveSndFlag=0;		// 生再生:1	逆再生:0

static u8	WaveMicDataFlag=0;	// 各所利用のフラグ

// 文字列郡
static const u16	wave_title00[] = {ro_,ku_,o_,n_,EOM_,};
static const u16	wave_title01[] = {sa_,i_,se_,i_,EOM_,};

static const u16	wave_00_comment00[] = {A__,BO_,TA_,N_,spc_,SA_,N_,PU_,RI_,N_,GU_,ka_,i_,si_,EOM_,};
static const u16	wave_01_comment00[] = {Y__,BO_,TA_,N_,spc_,sa_,i_,se_,i_,EOM_,};
static const u16	wave_01_comment01[] = {A__,BO_,TA_,N_,spc_,o_,to_,wo_,da_,su_,EOM_,};
static const u16	wave_01_comment02[] = {TA_,TTU_,TI_,PA_,NE_,RU_,spc_,SU_,KU_,RA_,TTU_,TI_,EOM_,};

static const u16*	wave_title[]={
	wave_title00,
	wave_title01,
	D_M_str13
};

enum{
	WAVE_ROKUON,
	WAVE_SAISEI,
	WAVE_D_W,
	WAVE_TITLE_NUM
};
#endif
//=============================================================================
//
//		お天気システム	
//
//=============================================================================
//-----------------------------------------------------------------------------
//			定数
//=============================================================================
#define MAP_TYPE_LIST_COUNT_SUB_OTENKI_00	(18)

//-----------------------------------------------------------------------------
//			構造体
//=============================================================================

//-----------------------------------------------------------------------------
//			プロトタイプ宣言
//=============================================================================
static void StartWeather00( TCB_PTR tcb,void* work );	// お天気を設定
static void StartWeather01( TCB_PTR tcb,void* work );	// お天気を設定
static void StartWeather02( TCB_PTR tcb,void* work );	// お天気を設定
static void StartWeather03( TCB_PTR tcb,void* work );	// お天気を設定
static void StartWeather04( TCB_PTR tcb,void* work );	// お天気を設定
static void StartWeather05( TCB_PTR tcb,void* work );	// お天気を設定
static void StartWeather06( TCB_PTR tcb,void* work );	// お天気を設定
static void StartWeather07( TCB_PTR tcb,void* work );	// お天気を設定
static void StartWeather08( TCB_PTR tcb,void* work );	// お天気を設定
static void StartWeather09( TCB_PTR tcb,void* work );	// お天気を設定
static void StartWeather10( TCB_PTR tcb,void* work );	// お天気を設定
static void StartWeather11( TCB_PTR tcb,void* work );	// お天気を設定
static void StartWeather12( TCB_PTR tcb,void* work );	// お天気を設定
static void StartWeather13( TCB_PTR tcb,void* work );	// お天気を設定
static void StartWeather14( TCB_PTR tcb,void* work );	// お天気を設定
static void StartWeather15( TCB_PTR tcb,void* work );	// お天気を設定
static void StartWeather16( TCB_PTR tcb,void* work );	// お天気を設定
static void StartWeather17( TCB_PTR tcb,void* work );	// お天気を設定
static void StopWeather( TCB_PTR tcb,void* work );		// お天気を終了
static void EndWeather( TCB_PTR tcb,void* work );	// お天気を破棄	 
//-----------------------------------------------------------------------------
//			変数
//=============================================================================



//============================================================================
//		jump
//		
//		デフォルト
//
//			デバックウィンドウの関数やデータ
//
//
//=============================================================================
#ifdef D_TOMOYA_MATERIAL_ON
	#define MAP_TYPE_LIST_COUNT_MAIN	(31)
#else
	#define MAP_TYPE_LIST_COUNT_MAIN	(30)
#endif	// D_TOMOYA_MATERIAL_ON

#define MAP_TYPE_LIST_COUNT_NO_SUB	(26)		// サブメニューがないシステム
#define MAP_TYPE_LIST_COUNT_SUB		(2)

#define MAP_TYPE_LIST_COUNT_LIGHT_SUB		(3)
		
//-----------------------------------------------------------------------------
//			構造体
//=============================================================================
typedef struct _DEBUG_WINDOW_DATA{
	u8	work;
	GF_BGL_BMPWIN*	bmplistID;
	BMPLIST_WORK*	bmplistContID;
	BMPLIST_DATA*	bmplist;


	u16 debug_list;
	u16 debug_cursor;
}DEBUG_WINDOW_DATA;

//-----------------------------------------------------------------------------
//			プロトタイプ
//=============================================================================
static void InitDebugWindow(DEBUG_WINDOW_DATA *wp);
static void DebugListFree(TCB_PTR tcb,void* work);
static void DebugWindowExit(TCB_PTR tcb,void* work);
static void DebugListControlTask(TCB_PTR tcb,void* work);
static void EndDebugWind( TCB_PTR tcb,void* work );		// デバックウィンドウしゅうりょう

// サブ用
static void StartApplication(TCB_PTR tcb,void* work);
static void ApplicationControlTask(TCB_PTR tcb,void* work);
//-----------------------------------------------------------------------------
//			変数
//=============================================================================
//----------------------------------------------------------------------------
//	リスト項目名
//----------------------------------------------------------------------------

//--------------------------------------------------------------------------
//	ウィンドウ制御データ
//--------------------------------------------------------------------------
DEBUG_WINDOW_DATA* MainWp = NULL;

//--------------------------------------------------------------------------
//	項目と実行関数のリスト
//--------------------------------------------------------------------------
//メイン用
static const BMPLIST_DATA MainDebugList[] = {
	{(void*)MSG_D_ZKN_01,(u32)StartZukanCont},
	{(void*)MSG_D_ZKN_04,(u32)MainZukanZenkokuFlagSet},
	{(void*)MSG_D_ZKN_06,(u32)MainZukanZenkokuSet},
	{(void*)MSG_D_ZKN_05,(u32)MainZukanShinouSet},
	{(void*)MSG_D_ZKN_07,(u32)MainZukanZenkokuSeeSet},
	{(void*)MSG_D_ZKN_08,(u32)MainZukanShinouSeeSet},
	{(void*)MSG_D_ZKN_09,(u32)D_TomoDeokisisuSaveBuckUp},

	{(void*)Msg01_03,(u32)StartWipe},
	{(void*)Msg01_02,(u32)StartSprite_Check},
	{(void*)Msg01_02,(u32)StartSprite_Check_Contest},
	{(void*)Msg01_02,(u32)StartSprite_CheckTelevision_View},
	{(void*)Msg01_20,(u32)Record_Clip},

	{(void*)Msg01_14,(u32)StartZukan_Check},
	
	{(void*)Msg01_15,(u32)StartEvPokeSelect_Check},
	{(void*)Msg01_16,(u32)StartPoison2},
	{(void*)Msg01_18,(u32)StartAmaikaoriDemo},
	{(void*)Msg01_13,(u32)Debug_MinoMuchiSet},
	{(void*)Msg01_25,(u32)StartTeamWorkScore},


	{ (void*)Msg01_17,(u32)StartClimaxDemoLegend },
	{ (void*)Msg01_17,(u32)StartClimaxDemoAntEgg00 },
	{ (void*)Msg01_17,(u32)StartClimaxDemoAntEgg01 },
	{ (void*)Msg01_17,(u32)StartClimaxDemoAntEgg02 },
	{ (void*)Msg01_21,(u32)StartAcceShop },
	{ (void*)Msg01_22,(u32)StartHideEff },
	{ (void*)Msg01_23,(u32)StartHideEff01 },
	{ (void*)Msg01_24,(u32)StartHideEff02 },

/*	{(void*)Msg01_19,(u32)StartFldTrade00},
	{(void*)Msg01_19,(u32)StartFldTrade01},
	{(void*)Msg01_19,(u32)StartFldTrade02},
	{(void*)Msg01_19,(u32)StartFldTrade03},//*/

#ifdef D_TOMOYA_MATERIAL_ON
	{(void*)Msg01_04,(u32)StartApplication},	
#endif	// D_TOMOYA_MATERIAL_ON
	{(void*)Msg01_05,(u32)StartApplication},
	{(void*)Msg01_07,(u32)StartApplication},
	{(void*)Msg01_10,(u32)StartApplication},
	{(void*)Msg01_11,(u32)EndDebugWind},
};


#define BMPLIST_ENDCODE	(const void*)(0xffffffff)

// サブ用
static const BMPLIST_DATA SubFogDebugList[] = {	// フォグ
	{(void*)Msg02_01,(u32)StartFog},
	{(void*)Msg02_02,(u32)EndFog},
	{BMPLIST_ENDCODE, 0},
};
static const BMPLIST_DATA SubWeatherDebugList[] = {	// 天気
	{(void*)Msg07_01,(u32)StartWeather00},	// 晴れ
	{(void*)Msg07_02,(u32)StartWeather01},	// 曇り	 
	{(void*)Msg07_03,(u32)StartWeather02},	// 雨	 
	{(void*)Msg07_04,(u32)StartWeather03},	// 大雨	 
	{(void*)Msg07_05,(u32)StartWeather04},	// 大雨	 
	{(void*)Msg07_06,(u32)StartWeather05},	// 雪	 
	{(void*)Msg07_07,(u32)StartWeather06},	// 吹雪	 
	{(void*)Msg07_08,(u32)StartWeather07},	// 猛吹雪
	{(void*)Msg07_09,(u32)StartWeather08},	// 霧小	 
	{(void*)Msg07_10,(u32)StartWeather09},	// 火山灰
	{(void*)Msg07_11,(u32)StartWeather10},	// BG使用砂嵐
	{(void*)Msg07_12,(u32)StartWeather11},	// スノーダスト
	{(void*)Msg07_13,(u32)StartWeather12},	// 霧大	霧払いの霧 
	{(void*)Msg07_13,(u32)StartWeather17},	// 霧大	霧払いの霧 
	{(void*)Msg07_14,(u32)StartWeather13},	// フラッシュ	   
	{(void*)Msg07_15,(u32)StartWeather14},	// 気合
	{(void*)Msg07_16,(u32)StartWeather15},	// 神秘
	{(void*)Msg07_18,(u32)EndWeather},
	{BMPLIST_ENDCODE, 0},                   
};
static const BMPLIST_DATA SubEncountDebugList[] = {	// エンカウントエフェクト
	{(void*)Msg08_00,(u32)EncountEffect_00},
	{(void*)Msg08_01,(u32)EncountEffect_01},
	{(void*)Msg08_02,(u32)EncountEffect_02},
	{(void*)Msg08_03,(u32)EncountEffect_03},
	{(void*)Msg08_04,(u32)EncountEffect_04},
	{(void*)Msg08_05,(u32)EncountEffect_05},
	{(void*)Msg08_06,(u32)EncountEffect_06},
	{(void*)Msg08_07,(u32)EncountEffect_07},
	{(void*)Msg08_08,(u32)EncountEffect_08},
	{(void*)Msg08_09,(u32)EncountEffect_09},
	{(void*)Msg08_10,(u32)EncountEffect_10},
	{(void*)Msg08_11,(u32)EncountEffect_11},
	{(void*)Msg08_12,(u32)EncountEffect_12},
	{(void*)Msg08_13,(u32)EncountEffect_13},
	{(void*)Msg08_14,(u32)EncountEffect_14},
	{(void*)Msg08_15,(u32)EncountEffect_15},
	{(void*)Msg08_16,(u32)EncountEffect_16},
	{(void*)Msg08_17,(u32)EncountEffect_17},
	{(void*)Msg08_18,(u32)EncountEffect_18},
	{(void*)Msg08_19,(u32)EncountEffect_19},
	{(void*)Msg08_20,(u32)EncountEffect_20},
	{(void*)Msg08_21,(u32)EncountEffect_21},
	{(void*)Msg08_22,(u32)EncountEffect_22},
	{(void*)Msg08_23,(u32)EncountEffect_23},
	{(void*)Msg08_24,(u32)EncountEffect_24},
	{(void*)Msg08_25,(u32)EncountEffect_25},
	{(void*)Msg08_26,(u32)EncountEffect_26},
	{(void*)Msg08_27,(u32)EncountEffect_27},
	{(void*)Msg08_28,(u32)EncountEffect_28},
	{(void*)Msg08_29,(u32)EncountEffect_29},
	{(void*)Msg08_30,(u32)EncountEffect_30},
	{BMPLIST_ENDCODE, 0},
};

#ifdef D_TOMOYA_MATERIAL_ON
static const BMPLIST_DATA SubMaterialDebugList[] = {	// マテリアル
	{(void*)Msg02_01,(u32)StartMaterialWindow},
	{(void*)Msg02_02,(u32)EndMaterialWindow},
	{BMPLIST_ENDCODE, 0},
};
#endif	// D_TOMOYA_MATERIAL_ON

//---------------------------------------------------------------------------
//  ウィンドウ設定
//---------------------------------------------------------------------------
//メインウィンドウ
static const BMPWIN_DAT	MainDebugListWindowData = {
	FLD_MBGFRM_FONT,
	0,0,
	16,24,
	FLD_SYSFONT_PAL,
	8
};

//サブウィンドウ
static const BMPWIN_DAT	SubDebugListWindowData = {
	FLD_MBGFRM_FONT,
	0,0,
	8,24,
	FLD_SYSFONT_PAL,
	8
};

//------------------------------------------------------------------
//	項目リストデータ
//------------------------------------------------------------------
//メイン用
static const BMPLIST_HEADER MainDebugListHeader = {
	MainDebugList,		//表示文字データポインタ
	NULL,				//カーソル移動ごとのコールバック関数
	NULL,				//１行ごとのコールバック関数
	NULL,				// ウィンドウ
	MAP_TYPE_LIST_COUNT_MAIN,//リスト項目数
	10,	//表示最大項目数
	2,					//ラベル表示Ｘ座標
	12,					//項目表示Ｘ座標
	1,					//カーソル表示Ｘ座標
	8,					//表示Ｙ座標
	FBMP_COL_WHITE,		//文字色
	FBMP_COL_BLACK,		//背景色
	FBMP_COL_BLK_SDW,	//文字影色
	0,					//文字間隔Ｘ
	1,					//文字間隔Ｙ
	BMPLIST_LRKEY_SKIP,	//ページスキップタイプ
	FONT_SYSTEM,		//文字指定
	0,					//ＢＧカーソル(allow)表示フラグ(0:ON,1:OFF)
};

//サブ用
static const BMPLIST_HEADER SubDebugListHeader[] = {
#ifdef D_TOMOYA_MATERIAL_ON
	{
		SubMaterialDebugList,	//表示文字データポインタ	
		NULL,		//カーソル移動ごとのコールバック関数
		NULL,		//１行ごとのコールバック関数
		NULL,		//ウィンドウ
		MAP_TYPE_LIST_COUNT_SUB,//リスト項目数
		MAP_TYPE_LIST_COUNT_SUB,//表示最大項目数
		2,					//ラベル表示Ｘ座標
		12,					//項目表示Ｘ座標
		1,					//カーソル表示Ｘ座標
		8,					//表示Ｙ座標
		FBMP_COL_WHITE,		//文字色
		FBMP_COL_BLACK,		//背景色
		FBMP_COL_BLK_SDW,	//文字影色
		0,					//文字間隔Ｘ
		1,					//文字間隔Ｙ
		BMPLIST_NO_SKIP,	//ページスキップタイプ
		FONT_SYSTEM,			//文字指定
		0,					//ＢＧカーソル(allow)表示フラグ(0:ON,1:OFF)
	},
#endif	// D_TOMOYA_MATERIAL_ON
	{
		SubFogDebugList,	//表示文字データポインタ	
		NULL,		//カーソル移動ごとのコールバック関数
		NULL,		//１行ごとのコールバック関数
		NULL,		//ウィンドウ
		MAP_TYPE_LIST_COUNT_SUB,//リスト項目数
		MAP_TYPE_LIST_COUNT_SUB,//表示最大項目数
		2,					//ラベル表示Ｘ座標
		12,					//項目表示Ｘ座標
		1,					//カーソル表示Ｘ座標
		8,					//表示Ｙ座標
		FBMP_COL_WHITE,		//文字色
		FBMP_COL_BLACK,		//背景色
		FBMP_COL_BLK_SDW,	//文字影色
		0,					//文字間隔Ｘ
		1,					//文字間隔Ｙ
		BMPLIST_NO_SKIP,	//ページスキップタイプ
		FONT_SYSTEM,			//文字指定
		0,					//ＢＧカーソル(allow)表示フラグ(0:ON,1:OFF)
	},
	{
		SubWeatherDebugList,	//表示文字データポインタ	
		NULL,		//カーソル移動ごとのコールバック関数
		NULL,		//１行ごとのコールバック関数
		NULL,		//ウィンドウ
		MAP_TYPE_LIST_COUNT_SUB_OTENKI_00,//リスト項目数
		8,//表示最大項目数
		2,					//ラベル表示Ｘ座標
		12,					//項目表示Ｘ座標
		1,					//カーソル表示Ｘ座標
		8,					//表示Ｙ座標
		FBMP_COL_WHITE,		//文字色
		FBMP_COL_BLACK,		//背景色
		FBMP_COL_BLK_SDW,	//文字影色
		0,					//文字間隔Ｘ
		1,					//文字間隔Ｙ
		BMPLIST_LRKEY_SKIP,	//ページスキップタイプ
		FONT_SYSTEM,		//文字指定
		0,					//ＢＧカーソル(allow)表示フラグ(0:ON,1:OFF)
	},
	{	// エンカウントエフェクト
		SubEncountDebugList,	//表示文字データポインタ	
		NULL,		//カーソル移動ごとのコールバック関数
		NULL,		//１行ごとのコールバック関数
		NULL,		//ウィンドウ
		31,//リスト項目数	// テーブル数
		8,//表示最大項目数
		2,					//ラベル表示Ｘ座標
		13,					//項目表示Ｘ座標
		1,					//カーソル表示Ｘ座標
		8,					//表示Ｙ座標
		FBMP_COL_WHITE,		//文字色
		FBMP_COL_BLACK,		//背景色
		FBMP_COL_BLK_SDW,	//文字影色
		0,					//文字間隔Ｘ
		1,					//文字間隔Ｙ
		BMPLIST_LRKEY_SKIP,	//ページスキップタイプ
		FONT_SYSTEM,		//文字指定
		0,					//ＢＧカーソル(allow)表示フラグ(0:ON,1:OFF)
	},
};


//-------------------------------------
//	キーの入力をキャンセルするフラグ
static u8	KeyNoTouchFlag = 0;

//----------------------------------------------------------------------------
/**
 *
 *@brief	Bmpウィンドウ作成
 *
 *@param	num		ウィンドウの個数
 *
 *@return	作成データ
 *
 *
 */
//-----------------------------------------------------------------------------
static GF_BGL_BMPWIN* initBmpWin(int num)
{
	return GF_BGL_BmpWinAllocGet(HEAPID_FIELD, num);
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	BMPウィンドウを破棄
 *
 *@param	data	データ
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void delBmpWin(GF_BGL_BMPWIN* data)
{
	GF_BGL_BmpWinDel(data);
	sys_FreeMemoryEz(data);
}

//===============================================================================
//	ウィンドウ共通
//===============================================================================
//初期化
static void InitDebugWindow(DEBUG_WINDOW_DATA *wp)
{
	wp->debug_list = 0;
	wp->debug_cursor = 0;
	wp->bmplist = NULL;
}
//リストの開放処理
static void DebugListFree(TCB_PTR tcb,void* work)
{
	DEBUG_WINDOW_DATA	*wp;

	wp = (DEBUG_WINDOW_DATA*)work;

	//BMPウィンドウOFF
	GF_BGL_BmpWinOff(wp->bmplistID);

	//BMPリスト破棄
	if(wp->bmplist != NULL)
	{
		BMP_MENULIST_Delete(wp->bmplist);
		wp->bmplist = NULL;
	}
	BmpListExit(wp->bmplistContID,&wp->debug_list,&wp->debug_cursor);

	//BMPWindow消去
	delBmpWin(wp->bmplistID);
	wp->bmplistID = NULL;

	return;
}
//デバッグウィンドウを解放
static void FreeDebugWindow(TCB_PTR tcb,void* work)
{
	//リストの開放処理
	DebugListFree(tcb,work);
	//ワークメモリ開放
	sys_FreeMemory(HEAPID_FIELD,work);
}
//デバッグウィンドウ終了
static void DebugWindowExit(TCB_PTR tcb,void* work)
{
	//ウィンドウ解放
	FreeDebugWindow(tcb,work);
	//タスク消去
	TCB_Delete(tcb);
	//OBJ等の動作停止解除
	FieldSystemProc_SeqHoldEnd();
	return;
}

static BMPLIST_DATA* BmpListMake(const BMPLIST_DATA* list, u32 max)
{
	u32 i;
	BMPLIST_DATA* ret = BMP_MENULIST_Create(max, HEAPID_BASE_APP);
	MSGDATA_MANAGER* man = MSGMAN_Create(MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_debug_tomoya_dat, HEAPID_BASE_APP);

	for(i=0; i<max; i++)
	{
		BMP_MENULIST_AddArchiveString( ret, man, (u32)(list->str), list->param );
		list++;
	}

	MSGMAN_Delete(man);
	return ret;
}


static void mainlistStart(void)
{
	BMPLIST_HEADER bmplist_h;
	TCB_PTR	pTcb = NULL;
	
	//デバッグメニュー用変数初期化
	InitDebugWindow(MainWp);
	
	//メイン処理タスク追加
	pTcb = TCB_Add(DebugListControlTask,MainWp,0);

	//BITMAPメニュー追加
	MainWp->bmplistID = initBmpWin(1);
	GF_BGL_BmpWinAddEx(D_TomoyaFldSys->bgl, MainWp->bmplistID, &MainDebugListWindowData);

	//BMPリスト設定
	MainWp->bmplist = BmpListMake(MainDebugList, NELEMS(MainDebugList));
	bmplist_h = MainDebugListHeader;
	bmplist_h.win = MainWp->bmplistID;
	bmplist_h.list = MainWp->bmplist;

	MainWp->bmplistContID = BmpListSet(&bmplist_h,MainWp->debug_list,MainWp->debug_cursor, HEAPID_FIELD);	
}

//リストコントロール
static void DebugListControlTask(TCB_PTR tcb,void* work)
{
	s32	ret_code;
	TCB_FUNC	func;
	DEBUG_WINDOW_DATA	*wp;
	
	wp = (DEBUG_WINDOW_DATA*)work;

	// 入力キャンセル
	if(KeyNoTouchFlag == 0){
		ret_code = BmpListMain(wp->bmplistContID);

		//キー操作判定
		if(sys.trg & PAD_BUTTON_A){
			if(ret_code){
				func = (TCB_FUNC)ret_code;
				func(tcb,work);
			}
			return;
		}

		// Bボタンウィンドウを閉じる
		if(sys.trg & PAD_BUTTON_B){
			EndDebugWind(tcb, work);
			return;
		}
	}
}

// サブ画面リストコントロール
static void ApplicationControlTask(TCB_PTR tcb,void* work)
{
	s32	ret_code;
	TCB_FUNC	func;
	DEBUG_WINDOW_DATA	*wp;
	
	wp = (DEBUG_WINDOW_DATA*)work;

	ret_code = BmpListMain(wp->bmplistContID);

	//キー操作判定
	if(sys.trg & PAD_BUTTON_A){
		if(ret_code){
			func = (TCB_FUNC)ret_code;
			func(tcb,work);
		}
	return;
	}

	// Bボタンウィンドウを閉じる
	if(sys.trg & PAD_BUTTON_B){
		//ウィンドウ解放
		FreeDebugWindow(tcb,work);
		//タスク消去
		TCB_Delete(tcb);

		// メインリストスタート
		mainlistStart();
		return;
	}
}

static u32 GetListMax(const BMPLIST_DATA* list )
{
	u32 cnt = 0;

	while(list[cnt].str != BMPLIST_ENDCODE)
	{
		cnt++;
	}

	return cnt;
}

// Application開始関数
static void StartApplication(TCB_PTR tcb,void* work)
{
	DEBUG_WINDOW_DATA*	sub_wp;
	TCB_PTR	pTcb = NULL;
	DEBUG_WINDOW_DATA	*wp;
	u16					num;
	BMPLIST_HEADER bmplist_h;
	
	DT_clact = NULL;
	//-----------------------------------------------------
	//	メインウィンドウを破棄する
	//	サブ画面のウィンドウの初期化を行う
	//	サブ画面コントロールタスクを作成する
	//-----------------------------------------------------
	// メインウィンドウコントールデータ取得
	wp = (DEBUG_WINDOW_DATA*)work;
	
	// 今のカーソル位置を取得
	BmpListDirectPosGet(wp->bmplistContID, &num);

	//ウィンドウ解放
	//リストの開放処理
	DebugListFree(tcb,work);
	//タスク消去
	TCB_Delete(tcb);
	

	// サブウィンドウコントール領域を確保
	sub_wp = sys_AllocMemory(HEAPID_FIELD,sizeof(DEBUG_WINDOW_DATA));
	if(sub_wp == NULL){
		//ワークエリアが取得できなければ何もしない
		OS_Printf("map_num debug menu crate failed\n");
		return;
	}
	memset(sub_wp,0,sizeof(DEBUG_WINDOW_DATA));

	//デバッグメニュー用変数初期化
	InitDebugWindow(sub_wp);

	// そのApplicationデータをヘッダにセット
	bmplist_h = SubDebugListHeader[num - MAP_TYPE_LIST_COUNT_NO_SUB];
	sub_wp->bmplist = BmpListMake( bmplist_h.list, GetListMax(bmplist_h.list) );
	bmplist_h.list = sub_wp->bmplist;


	//サブ処理タスク追加
	pTcb = TCB_Add(ApplicationControlTask,sub_wp,0);

	//BITMAPメニュー追加
	sub_wp->bmplistID = GF_BGL_BmpWinAllocGet(HEAPID_FIELD, 1);
	GF_BGL_BmpWinAddEx(D_TomoyaFldSys->bgl, sub_wp->bmplistID, &SubDebugListWindowData);

	//BMPリスト設定
	bmplist_h.win = sub_wp->bmplistID;
	sub_wp->bmplistContID = BmpListSet(&bmplist_h,sub_wp->debug_list,sub_wp->debug_cursor, HEAPID_FIELD);
}

extern void InitDebugTouchpanel( void );
extern void D_TouchPanelSet( void );

//-----------------------------------------------------------------------------
//	アクセス関数
//-----------------------------------------------------------------------------
//デバッグメインウィンドウ構築関数
void DebugListSetOfTomoya(FIELDSYS_WORK* data)
{
	TCB_PTR	pTcb = NULL;

	D_TomoyaFldSys = data;

	MainWp = sys_AllocMemory(HEAPID_FIELD,sizeof(DEBUG_WINDOW_DATA));
	if(MainWp == NULL){
		//ワークエリアが取得できなければ何もしない
		OS_Printf("map_num debug menu crate failed\n");
		return;
	}
	memset(MainWp,0,sizeof(DEBUG_WINDOW_DATA));

	// メインリストセット
	mainlistStart();

	//イベントフック
	FieldSystemProc_SeqHold();
	return;
}


// ちかまっぷフェード
static void StartUnderGround( TCB_PTR tcb,void* work ){
	TCB_PTR tcb_ptr;
	D_TMY_ENC* data;
	
	tcb_ptr = PMDS_taskAdd(MainUnderGround, sizeof(D_TMY_ENC), 6, HEAPID_FIELD);
	data = TCB_GetWork(tcb_ptr);
	data->no = 0;
	data->flag = 1;
	
	EndDebugWind(tcb, work);
}
static void MainUnderGround( TCB_PTR tcb,void* work )
{
	D_TMY_ENC* data = (D_TMY_ENC*)work;

	
	if(data->flag){
		// 読み込み開始位置を初期化
		CharLoadStartAll();
		PlttLoadStartAll();
		
		data->flag = 0;
		StartUnderGroundEffect( D_TomoyaFldSys , data->no, &data->flag);	
		data->no++;
	}
	
	if(data->no == 4){
		// 終了
		PMDS_taskDel(tcb);
	}
}


static void EndDebugWind( TCB_PTR tcb,void* work )
{
	DebugWindowExit(tcb,work);


#ifdef D_TOMOYA_MATERIAL_ON
	// マテリアルの終了チェック
	if(MaterialWinFlag == 1){
		MaterialWinFlag = 0;
		TCB_Delete(materialTCBData);		// タスク破棄
		materialTCBData = NULL;

		
		// 描画面
		delBmpWin(D_M_win);
		D_M_win = NULL;
		
		GF_Disp_GXS_VisibleControl( GX_PLANEMASK_BG0, VISIBLE_ON );
		GF_Disp_GXS_VisibleControl( GX_PLANEMASK_BG1, VISIBLE_OFF );
		GF_BGL_BGControlExit( D_TomoyaFldSys->bgl, FLD_SBGFRM_EFFECT1 );
	}
#endif	// D_TOMOYA_MATERIAL_ON

	if(FogFlag == 1){
		FogFlag = 0;
		TCB_Delete(FogTCBData);		// タスク破棄
		FogTCBData = NULL;
		
		// 描画面
		delBmpWin(FOG_win);
		GF_Disp_GXS_VisibleControl( GX_PLANEMASK_BG0, VISIBLE_ON );
		GF_Disp_GXS_VisibleControl( GX_PLANEMASK_BG1, VISIBLE_OFF );
		GF_BGL_BGControlExit( D_TomoyaFldSys->bgl, FLD_SBGFRM_EFFECT1 );

	}

	
}


//----------------------------------------------------------------------------
/**
 *
 *	@brief	毒エフェクト
 *
 *	@param	tcb		TCBワーク
 *	@param	work	ワーク
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
#define D_TOMO_POISON_COUNT		( 8 )		// 動作ｶｳﾝﾀ
#define D_TOMO_POISON_NEXT		( 64 )		// 次動作までのｶｳﾝﾀ
#define D_TOMO_POISON_NEXT_WALK		( 4 )		// 次動作までのｶｳﾝﾀ
//#define D_TOMO_POISON_NUM		( 8 )		// 毒パラメータ計算値（１回）
static int D_TOMO_POISON_NUM = 8;
static void StartPoison( TCB_PTR tcb,void* work )
{
	TCB_PTR tcb_ptr;
	D_TOMOYA_POISON* data;
	
	tcb_ptr = PMDS_taskAdd(MainPoison, sizeof(D_TOMOYA_POISON), 6, HEAPID_FIELD);
	data = TCB_GetWork(tcb_ptr);
	memset( data, 0, sizeof(D_TOMOYA_POISON) );
	data->camera = D_TomoyaFldSys->camera_ptr;
	data->player = D_TomoyaFldSys->player;

	OS_Printf( "effect_num %d\n", D_TOMO_POISON_NUM );
	
	EndDebugWind(tcb, work);
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	メイン動作
 *
 *	@param	tcb
 *	@param	work 
 *
 *	@return
 *
 *
 */
//-----------------------------------------------------------------------------
static void MainPoison( TCB_PTR tcb,void* work )
{
	D_TOMOYA_POISON* data;
	int play_value;
	int play_state;
	
	data = work;

	if( sys.trg & PAD_BUTTON_L ){
		D_TOMO_POISON_NUM ++;
		OS_Printf( "effect_num %d\n", D_TOMO_POISON_NUM );
	}
	if( sys.trg & PAD_BUTTON_R ){
		D_TOMO_POISON_NUM --;
		OS_Printf( "effect_num %d\n", D_TOMO_POISON_NUM );
	}

	// 終了
	if( sys.trg & PAD_BUTTON_B ){
		data->seq = 5;
	}

	switch( data->seq ){
	case 0:		// 初期化
		data->count = D_TOMO_POISON_COUNT;
		data->num	= D_TOMO_POISON_NUM;
		data->seq++;
		break;

	case 1:		// 減算
		GFC_AddCameraPerspWay( -data->num, data->camera );
		data->count --;
		if( data->count <= 0 ){
			data->count = D_TOMO_POISON_COUNT;
			data->seq++;
		}
		break;

	case 2:		// 加算
		GFC_AddCameraPerspWay( data->num, data->camera );
		data->count --;
		if( data->count <= 0 ){
			data->count = D_TOMO_POISON_COUNT;
			data->seq++;
		}
		break;

	case 3:
//		data->next_count = D_TOMO_POISON_NEXT;
		data->next_count = D_TOMO_POISON_NEXT_WALK;
		data->seq ++;
		break;

	case 4:
		// プレイヤーがD_TOMO_POISON_NEXT_WALK歩歩くのを待つ
		play_value = Player_MoveValueGet( data->player );
		play_state = Player_MoveStateGet( data->player );
		if( (play_value == OBJ_MOVE_VALUE_WALK) &&
			(play_state == OBJ_MOVE_STATE_START) ){
			data->next_count --;
		}
//		data->next_count--;
		if( data->next_count <= 0 ){
			data->seq = 0;
		}
		break;
		
	case 5:
		PMDS_taskDel( tcb );
		break;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	毒テストｴﾌｪｸﾄ	２
 *
 *	@param	tcb	
 *	@param	work 
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void StartPoison2( TCB_PTR tcb,void* work )
{
	TCB_PTR tcb_ptr;
	D_TOMOYA_POISON_2* data;
	
	data = sys_AllocMemory( HEAPID_FIELD, sizeof(D_TOMOYA_POISON_2) );
	tcb_ptr = TCB_Add(MainPoison2, data, 6);
	memset( data, 0, sizeof(D_TOMOYA_POISON_2) );

	data->player = D_TomoyaFldSys->player;

	EndDebugWind(tcb, work);
}

extern void DEBUG_Poison( void );
//----------------------------------------------------------------------------
/**
 *	@brief	毒テストｴﾌｪｸﾄ２
 *
 *	@param	tcb
 *	@param	work 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void MainPoison2( TCB_PTR tcb,void* work )
{
	D_TOMOYA_POISON_2* data = work;
	int play_value;
	int play_state;

	DEBUG_Poison();
	
	// 終了
	if( sys.trg & PAD_BUTTON_B ){
		data->seq = 3;
	}

	switch( data->seq ){
	case 0:		// 初期化
		POISON_EFFE_Start( D_TomoyaFldSys->fldmap->poisoneffect );
		data->seq++;
		break;

	case 1:
		if( POISON_EFFE_GetStatus( D_TomoyaFldSys->fldmap->poisoneffect ) == POISON_EFFE_STANDBY ){
			data->next_count = D_TOMO_POISON_NEXT_WALK;
			data->seq ++;
		}
		break;

	case 2:
		// プレイヤーがD_TOMO_POISON_NEXT_WALK歩歩くのを待つ
		play_value = Player_MoveValueGet( data->player );
		play_state = Player_MoveStateGet( data->player );
		if( (play_value == OBJ_MOVE_VALUE_WALK) &&
			(play_state == OBJ_MOVE_STATE_START) ){
			data->next_count --;
		}
//		data->next_count--;
		if( data->next_count <= 0 ){
			data->seq = 0;
		}
		break;
		
	case 3:
		PMDS_taskDel( tcb );
		break;
	}


}

//-----------------------------------------------------------------------------
/**
 *		3Dテクスチャ転送実験
 */
//-----------------------------------------------------------------------------

static void StartTexTrans( TCB_PTR tcb,void* work )
{
	TCB_PTR tcb_ptr;
	D_TM_TEX_TRANS* data;
	
	tcb_ptr = PMDS_taskAdd(MainTexTrans, sizeof(D_TM_TEX_TRANS), 6, HEAPID_FIELD);
	data = TCB_GetWork(tcb_ptr);
	
//	data->tex_buff	 = sys_LoadFile( HEAPID_FIELD, "data/babyboy1.nsbtx" );
	data->tex_buff	 = sys_LoadFile( HEAPID_FIELD, "data/billboad.nsbmd" );
	data->tex_res	 = NNS_G3dGetTex( data->tex_buff );
	data->trans_num	 = 0;
	data->trans_size = data->tex_res->texInfo.sizeTex << 3;
	data->vram		 = 1;
	
	EndDebugWind(tcb, work);
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
static void getVramkey( NNSG3dResTex* res, NNSGfdTexKey* tex, NNSGfdTexKey* tex4x4, NNSGfdPlttKey* pltt )
{
	u32 tex_size;
	u32 tex_4x4_size;
	u32 pltt_size;

	tex_size = NNS_G3dTexGetRequiredSize( res );
	tex_4x4_size = NNS_G3dTex4x4GetRequiredSize(res);
	tex_size = NNS_G3dTexGetRequiredSize( res );
	pltt_size = NNS_G3dPlttGetRequiredSize( res );


	if(tex_size != 0){
		*tex = NNS_GfdAllocTexVram( tex_size, FALSE, 0 );
	}
	if(tex_4x4_size != 0){
		*tex = NNS_GfdAllocTexVram( tex_size, TRUE, 0 );
	}
	if(pltt_size != 0){
		*pltt = NNS_GfdAllocPlttVram( pltt_size, 
			res->tex4x4Info.flag & NNS_G3D_RESPLTT_USEPLTT4, 0 );
	}
}


static void MainTexTrans( TCB_PTR tcb,void* work )
{
	D_TM_TEX_TRANS* data = work;
	int i;
	NNSGfdTexKey tex;
	NNSGfdTexKey tex4x4;
	NNSGfdPlttKey pltt;
	
	for( i=0; i<data->trans_num; i++ ){

		if( data->vram ){
			AddVramTransferManager( 
					NNS_GFD_DST_3D_TEX_VRAM,
					0,
					(u8*)data->tex_res + data->tex_res->texInfo.ofsTex,
					data->trans_size );
		}else{
			getVramkey( data->tex_res, &tex, &tex4x4, &pltt );

			NNS_G3dTexSetTexKey(data->tex_res, tex, tex4x4);
			NNS_G3dPlttSetPlttKey(data->tex_res, pltt);

			// VRAMへのロード
			NNS_G3dTexLoad(data->tex_res, TRUE);
			NNS_G3dPlttLoad(data->tex_res, TRUE);

			// テクスチャキーがあるときは破棄
			NNS_GfdFreeTexVram( tex );
			// パレットキー破棄
			NNS_GfdFreePlttVram( pltt );
		
			/*
			GX_LoadTex( 
					(u8*)data->tex_res + data->tex_res->texInfo.ofsTex,
					0,
					data->trans_size);//*/
		}
	}

	if( sys.cont & PAD_BUTTON_A ) {

		if( sys.trg & PAD_KEY_UP ){
			data->trans_num ++;
			OS_Printf( "trans_data num[%d] tex_size[0x%x]\n", data->trans_num, data->trans_size );
		}else{
			if( sys.trg & PAD_KEY_DOWN ){
				data->trans_num --;
				OS_Printf( "trans_data num[%d] tex_size[0x%x]\n", data->trans_num, data->trans_size );
			}
		}
		
	}

	if( sys.trg & PAD_BUTTON_Y ){

		data->vram = (data->vram + 1) & 0x1;
		OS_Printf( "1:vram 0:now [%d]\n", data->vram );
	}

	// Bボタン	終了
	if( sys.trg & PAD_BUTTON_B ){

		sys_FreeMemoryEz( data->tex_buff );
		PMDS_taskDel( tcb );
	}
}


static void StartWipe( TCB_PTR tcb,void* work )// 画面切り替え開始
{
	TCB_PTR tcb_ptr;
	D_TMY_WIPE* data;
	
	tcb_ptr = PMDS_taskAdd(MainWipe, sizeof(D_TMY_WIPE), 6, HEAPID_FIELD);
	data = TCB_GetWork(tcb_ptr);
	data->seq = 0;	
	data->no	= 0;
//	data->no	= WIPE_TYPE_PESOCOMOUT;

	// フィールドのHブランク処理ストップ
	FLDHBLANK_SYS_Stop( D_TomoyaFldSys->fldmap->hblanksys );
	
	EndDebugWind(tcb, work);
}

//extern u16 WIPE_ROTA_LIMIT;
//extern int DEBUG_WIPE_ADD;
static void MainWipe( TCB_PTR tcb,void* work )// 画面切り替えメイン
{
	D_TMY_WIPE* data = (D_TMY_WIPE*)work;

	/*
	if( sys.trg & PAD_BUTTON_A ){
		WIPE_ROTA_LIMIT++;
		OS_Printf( "WIPE_ROTA_LIMIT %d\n", WIPE_ROTA_LIMIT );
	}else if( sys.trg & PAD_BUTTON_B ){
		WIPE_ROTA_LIMIT--;
		OS_Printf( "WIPE_ROTA_LIMIT %d\n", WIPE_ROTA_LIMIT );
	}//*/

	
	// 強制終了
	if( sys.cont & PAD_BUTTON_X ){
		//強制終了
		WIPE_SYS_ExeEnd();

		PMDS_taskDel( tcb );
		// フィールドのHブランク処理開始
		FLDHBLANK_SYS_Start( D_TomoyaFldSys->fldmap->hblanksys );
	}

	switch(data->seq){
	case 0:
		// 状態破棄
		WIPE_SYS_Start(WIPE_PATTERN_FSAM,
			data->no, data->no,
			WIPE_FADE_WHITE,
			8,1, HEAPID_FIELD);

		data->seq++;
		break;

	case 1:
		if (WIPE_SYS_EndCheck()) {
			data->seq = 0;

			data->no += 1;

			if( data->no >= WIPE_TYPE_MAX ){
				WIPE_Reset( WIPE_DISP_MAIN );
				WIPE_Reset( WIPE_DISP_SUB );
				PMDS_taskDel( tcb );
				// フィールドのHブランク処理開始
				FLDHBLANK_SYS_Start( D_TomoyaFldSys->fldmap->hblanksys );
			}else{

				if( sys.cont & PAD_BUTTON_B ){

					PMDS_taskDel( tcb );
					// フィールドのHブランク処理開始
					FLDHBLANK_SYS_Start( D_TomoyaFldSys->fldmap->hblanksys );
				}
			}
		}
		break;
	}
}


//----------------------------------------------------------------------------
/**
 *	@brief	開始ポケモン選択
 *
 *	@param	TCB_PTR tcb
 *	@param	work 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void StartEvPokeSelect_Check( TCB_PTR tcb, void* work )
{
	DT_SPRITE_CHECK* DT_sprite = NULL;
	EV_POKESELECT_PEARENT_DATA* p_pearent;

	// タスク生成
	DT_sprite = sys_AllocMemory( HEAPID_BASE_APP, sizeof( DT_SPRITE_CHECK ) );
	// セルアクター登録数初期化
	TCB_Add(MainEvPokeSelect_Check, DT_sprite, 8);

	DT_sprite->seq = 0;
	DT_sprite->sub = 0;

	// ペアレントデータ作成
	p_pearent = sys_AllocMemory( HEAPID_BASE_APP, sizeof(EV_POKESELECT_PEARENT_DATA) );
	p_pearent->cp_config = SaveData_GetConfig( D_TomoyaFldSys->savedata );
	DT_sprite->p_pearent = p_pearent;
	DT_sprite->p_fsys = D_TomoyaFldSys;
	
	EndDebugWind(tcb, work);
}


//----------------------------------------------------------------------------
/**
 *
 *	@brief	図鑑チェック
 *
 *	@param	TCB_PTR tcb
 *	@param	work 
 *
 *	@return
 *
 *
 */
//-----------------------------------------------------------------------------
static void StartZukan_Check( TCB_PTR tcb,void* work )
{
	DT_SPRITE_CHECK* DT_sprite = NULL;
	ZKN_PEARENT_DATA* p_pearent;
	ZUKAN_WORK* p_zukan;
	MYSTATUS* p_hero;
	static BOOL init_flg = 0;

	// タスク生成
	DT_sprite = sys_AllocMemory( HEAPID_BASE_APP, sizeof( DT_SPRITE_CHECK ) );
	// セルアクター登録数初期化
	TCB_Add(MainZukan_Check, DT_sprite, 8);

	DT_sprite->seq = 0;
	DT_sprite->sub = 0;

	// ペアレントデータ作成
	p_pearent = sys_AllocMemory( HEAPID_BASE_APP, sizeof(ZKN_PEARENT_DATA) );
	p_zukan = SaveData_GetZukanWork( D_TomoyaFldSys->savedata );
	p_hero = SaveData_GetMyStatus(D_TomoyaFldSys->savedata);
	p_pearent->cp_zukansave_data = p_zukan;
	p_pearent->cp_hero_data = p_hero;
	p_pearent->time_zone = EVTIME_GetTimeZone( D_TomoyaFldSys );
	p_pearent->hidemap_id_D15 = TRUE;
	p_pearent->hidemap_id_D30 = TRUE;
	p_pearent->hidemap_id_L04 = TRUE;
	p_pearent->hidemap_id_D18 = TRUE;
	p_pearent->p_zkn_work	  = D_TomoyaFldSys->p_zukandata;
	
	if( init_flg == FALSE ){
		init_flg = TRUE;

/*		// 女になる
		MyStatus_SetMySex(p_hero, 1);//*/

		
		// 全国図鑑を見つけたことにする
		ZukanWork_SetZenkokuZukanFlag( p_zukan );
		MyStatus_SetDpZenkokuFlag( p_hero );

		// ポケモン見つけたデータをもっと増やす
		Debug_ZukanWork_Make( p_zukan, 1, MONSNO_END, FALSE );
	}
	
	DT_sprite->p_pearent = p_pearent;
	DT_sprite->p_fsys = D_TomoyaFldSys;
	
	EndDebugWind(tcb, work);
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief
 *
 *	@param	TCB_PTR tcb
 *	@param	work 
 *
 *	@return
 *
 *
 */
//-----------------------------------------------------------------------------
static void StartSprite_Check( TCB_PTR tcb,void* work )
{
	DT_SPRITE_CHECK* DT_sprite = NULL;
	IMC_PROC_WORK* imc_w;
	POKEMON_PARAM* poke;
	RTCTime time;
	int poke_no;
	IMC_SAVEDATA* p_save;
	IMC_TELEVISION_SAVEDATA* p_save_one;
	IMC_ITEM_SAVEDATA* p_save_item;

	// タスク生成
	DT_sprite = sys_AllocMemory( HEAPID_BASE_APP, sizeof( DT_SPRITE_CHECK ) );
	// セルアクター登録数初期化
	TCB_Add(MainSprite_Check, DT_sprite, 8);

	DT_sprite->seq = 0;
	DT_sprite->sub = 0;

	// イメージクリップに渡すデータ作成
	imc_w = sys_AllocMemory( HEAPID_BASE_APP, sizeof( IMC_PROC_WORK ) );
	memset( imc_w, 0, sizeof( IMC_PROC_WORK ) );
	// ポケパラ		今は適当に時間によって編集するポケモンを選ぶ
	GF_RTC_GetTime( &time );
	poke_no = time.second;
	poke_no += time.hour * 20;
	poke_no =  1 + (poke_no % MONSNO_END);
	poke = PokemonParam_AllocWork( HEAPID_BASE_APP );
	PokeParaSet( poke, poke_no, 5, POW_RND, RND_NO_SET, 0, ID_NO_RARE, 0 );
	imc_w->p_poke_para = poke;
	// セーブデータ
	p_save = SaveData_GetImcSaveData( D_TomoyaFldSys->savedata );
	p_save_one = ImcSaveData_GetTelevisionSaveData( p_save, 0 );
	p_save_item = ImcSaveData_GetItemSaveData( p_save );
	ImcSaveData_ClaenTelevisionData( p_save_one );		// 編集するワークを初期化
	imc_w->p_imc_one_data = p_save_one;
	imc_w->cp_imc_item = p_save_item;					// アイテムセーブデータ
	imc_w->cp_config  = SaveData_GetConfig( D_TomoyaFldSys->savedata );
	imc_w->p_record = SaveData_GetRecord( D_TomoyaFldSys->savedata );
	imc_w->reference = FALSE;

	// デバックデータ設定
	Debug_ImcSaveData_Make( p_save, 0 );
	
	// 上位からのデータ設定
	DT_sprite->p_pearent = imc_w;

	DT_sprite->p_fsys = D_TomoyaFldSys;
	
	EndDebugWind(tcb, work);
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief		コンテスト用ドレスアップ
 *
 *	@param	TCB_PTR tcb
 *	@param	work 
 *
 *	@return
 *
 *
 */
//-----------------------------------------------------------------------------
static void StartSprite_Check_Contest( TCB_PTR tcb,void* work )
{
	DT_SPRITE_CHECK* DT_sprite = NULL;
	IMC_CONTEST_PROC_WORK* imc_w;
	POKEMON_PARAM* poke;
	int poke_no;
	IMC_SAVEDATA* p_save;
	IMC_CONTEST_SAVEDATA* p_save_one;
	IMC_ITEM_SAVEDATA* p_save_item;
	POKEPARTY* party = SaveData_GetTemotiPokemon( D_TomoyaFldSys->savedata );

	// タスク生成
	DT_sprite = sys_AllocMemory( HEAPID_BASE_APP, sizeof( DT_SPRITE_CHECK ) );
	// セルアクター登録数初期化
	TCB_Add(MainSprite_Check_Contest, DT_sprite, 8);

	DT_sprite->seq = 0;
	DT_sprite->sub = 0;

	// イメージクリップに渡すデータ作成
	imc_w = sys_AllocMemory( HEAPID_BASE_APP, sizeof( IMC_CONTEST_PROC_WORK ) );
	memset( imc_w, 0, sizeof( IMC_CONTEST_PROC_WORK ) );
	poke = PokemonParam_AllocWork( HEAPID_BASE_APP );
	PokeCopyPPtoPP( PokeParty_GetMemberPointer( party, 0 ), poke );
	imc_w->p_poke_para = poke;
	// セーブデータ
	p_save = SaveData_GetImcSaveData( D_TomoyaFldSys->savedata );
	p_save_one = ImcSaveData_GetContestSaveData( p_save, 0 );
	p_save_item = ImcSaveData_GetItemSaveData( p_save );
	ImcSaveData_ClaenContestData( p_save_one );		// 編集するワークを初期化
	imc_w->p_imc_one_data = p_save_one;
	imc_w->cp_imc_item = p_save_item;					// アイテムセーブデータ
	imc_w->theme	= 0;		// テーマ
	imc_w->rank     = CONRANK_MASTER;	// ランク
	imc_w->p_comm_data = sys_AllocMemory( HEAPID_BASE_APP, sizeof(CON_IMC_LOCAL) );
	memset( imc_w->p_comm_data, 0, sizeof(CON_IMC_LOCAL) );
	imc_w->p_comm_data->sio_flag = FALSE;
	imc_w->cp_config  = SaveData_GetConfig( D_TomoyaFldSys->savedata );
	imc_w->cp_tr  = SaveData_GetMyStatus( D_TomoyaFldSys->savedata );

	// デバックデータ設定
	Debug_ImcSaveData_Make( p_save, 0 );
	
	// 上位からのデータ設定
	DT_sprite->p_pearent = imc_w;

	DT_sprite->p_fsys = D_TomoyaFldSys;
	
	EndDebugWind(tcb, work);
}

//----------------------------------------------------------------------------
/**
 *	@brief ドレスアップ通常のビューアー開始
 *
 *	@param	TCB_PTR tcb
 *	@param	work 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
#define D_TOMO_TV_POS_CX	( 10 )
#define D_TOMO_TV_POS_CY	( 10 )
#define D_TOMO_TV_SIZ_CX	( 10 )
#define D_TOMO_TV_SIZ_CY	( 10 )
static void StartSprite_CheckTelevision_View( TCB_PTR tcb,void* work )
{
	DT_SPRITE_CHECK* DT_sprite = NULL;
	IMC_PROC_PREV_WORK* imc_w;
	D_TOMOYA_TV_PRINTDATA_SELE* p_printdata;

	// タスク生成
	DT_sprite = sys_AllocMemory( HEAPID_BASE_APP, sizeof( DT_SPRITE_CHECK ) );
	p_printdata = sys_AllocMemory( HEAPID_BASE_APP, sizeof( D_TOMOYA_TV_PRINTDATA_SELE ) );

	TCB_Add(StartSprite_CheckTelevision_PrintDataSelect, DT_sprite, 8);

	DT_sprite->seq = 0;
	DT_sprite->sub = 0;
	DT_sprite->p_work = p_printdata;

	p_printdata->p_bmp = GF_BGL_BmpWinAllocGet( HEAPID_BASE_APP, 1 );
	p_printdata->count = 0;

	GF_BGL_BmpWinAdd(
				D_TomoyaFldSys->bgl, p_printdata->p_bmp, GF_BGL_FRAME2_M,
				D_TOMO_TV_POS_CX, D_TOMO_TV_POS_CY,
				D_TOMO_TV_SIZ_CX, D_TOMO_TV_SIZ_CY, 
				13, 1 );

	GF_BGL_BmpWinDataFill( p_printdata->p_bmp, 0 );
	DrawNum( p_printdata->count, 2, 2, p_printdata->p_bmp );
	GF_BGL_BmpWinOn( p_printdata->p_bmp );

	G2_SetBG2Priority(0);
		
	// イメージクリップに渡すデータ作成
	imc_w = sys_AllocMemory( HEAPID_BASE_APP, sizeof( IMC_PROC_PREV_WORK ) );
	memset( imc_w, 0, sizeof( IMC_PROC_PREV_WORK ) );

	// 上位からのデータ設定
	DT_sprite->p_pearent = imc_w;
	DT_sprite->p_fsys = D_TomoyaFldSys;
	DT_sprite->sub = 0;
	
	EndDebugWind(tcb, work);

	//イベントフック
	FieldSystemProc_SeqHold();
}

//----------------------------------------------------------------------------
/**
 *	@brief	表示クリップナンバーを選択
 */
//-----------------------------------------------------------------------------
static void StartSprite_CheckTelevision_PrintDataSelect( TCB_PTR tcb,void* work )
{
	DT_SPRITE_CHECK* DT_sprite = work;
	IMC_SAVEDATA* p_save;
	IMC_TELEVISION_SAVEDATA* p_save_one;
	IMC_PROC_PREV_WORK* imc_w = DT_sprite->p_pearent;
	D_TOMOYA_TV_PRINTDATA_SELE* p_printdata = DT_sprite->p_work;

	if( sys.trg & PAD_KEY_LEFT ){
		p_printdata->count --;
		if( p_printdata->count < 0 ){
			p_printdata->count += IMC_SAVEDATA_TELEVISION_SAVENUM;
		}

		GF_BGL_BmpWinDataFill( p_printdata->p_bmp, 0 );
		DrawNum( p_printdata->count, 2, 2, p_printdata->p_bmp );
		GF_BGL_BmpWinOn( p_printdata->p_bmp );
	}
	if( sys.trg & PAD_KEY_RIGHT ){
		p_printdata->count ++;
		if( p_printdata->count >= IMC_SAVEDATA_TELEVISION_SAVENUM ){
			p_printdata->count -= IMC_SAVEDATA_TELEVISION_SAVENUM;
		}

		GF_BGL_BmpWinDataFill( p_printdata->p_bmp, 0 );
		DrawNum( p_printdata->count, 2, 2, p_printdata->p_bmp );
		GF_BGL_BmpWinOn( p_printdata->p_bmp );
	}

	if( sys.trg & PAD_BUTTON_START ){
		// セーブデータ
		p_save = SaveData_GetImcSaveData( D_TomoyaFldSys->savedata );
		imc_w->p_imc_data = p_save;
		imc_w->data_idx = p_printdata->count;
		imc_w->prev_type = IMC_PREV_TV;

		TCB_Add(MainSprite_CheckView, DT_sprite, 8);

		GF_BGL_BmpWinOff( p_printdata->p_bmp );
		GF_BGL_BmpWinDel( p_printdata->p_bmp );
		GF_BGL_BmpWinFree( p_printdata->p_bmp, 1 );

		G2_SetBG2Priority(3);

		sys_FreeMemoryEz( p_printdata );
		DT_sprite->p_work = NULL;

		TCB_Delete( tcb );

		FieldSystemProc_SeqHoldEnd();
	}	
}





/*[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
 *
 *
 *	セルアクターチェック用
 *					動作開始システム
 * 
 *				
 [[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[*/
//----------------------------------------------------------------------------
/**
 *
 *@brief	開始
 *
 *@param	tcb
 *@param	work 
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void StartCLACT_Check( TCB_PTR tcb,void* work )
{
	NNSG2dViewRect rect;
	int i;
	int size;
	CLACT_U_RES_HEADER_PTR res_head;
	void* buff;
	
	if(DT_clact == NULL){
		GF_Disp_GX_VisibleControl( GX_PLANEMASK_OBJ, VISIBLE_ON );
		GF_Disp_GXS_VisibleControl( GX_PLANEMASK_OBJ, VISIBLE_ON );

		// メモリ確保
		DT_clact = sys_AllocMemory(HEAPID_FIELD, sizeof(DT_CLACT));
		memset(DT_clact, 0, sizeof(DT_CLACT));

		// キャラクタマネージャ初期化
		{
			CHAR_MANAGER_MAKE init = {
				32, 0x2000, 0x2000, HEAPID_FIELD
			};

			DeleteCharManager();
			InitCharManager(&init);
		}

		// パレットマネージャ初期化
		DeletePlttManager();
		InitPlttManager(32, HEAPID_FIELD);

		
		// OAMマネージャーの初期化
		NNS_G2dInitOamManagerModule();
		

		// セルVram転送マネージャ作成
		DT_clact->cellTransArray = InitCellTransfer(32, HEAPID_FIELD);


/*		// アクターセット作成
		{
			CLACT_SETDATA	set;
			set.WorkNum = 32;
			set.pRender	= &DT_clact->rend;
			set.heap	= HEAPID_FIELD;
			
			DT_clact->clactSet = CLACT_InitSet( &set );
		}//*/

		// 簡易登録
		{
			// レンダラ用OAMマネージャ作成
			// ここで作成したOAMマネージャをみんなで共有する
/*			REND_OAMInit( 
					0, 16,		// メイン画面OAM管理領域
					0, 4,		// メイン画面アフィン管理領域
					0, 16,		// サブ画面OAM管理領域
					0, 4,		// サブ画面アフィン管理領域
					HEAPID_FIELD);//*/	// 共有OAMはfieldmap.cで作成済み

			// 簡易セルアクターセット作成
			// 上で作成した共有OAMマネージャを使用してレンダラーを作成し、
			// セルアクターセットの作成を行う
			DT_clact->clactSet = CLACT_U_SetEasyInit( 10, &DT_clact->renddata, HEAPID_FIELD );
		}

		// リソースマネージャ作成
		for(i=0; i<=CLACT_U_MULTIANM_RES;i++){
			DT_clact->resMan[i] = CLACT_U_ResManagerInit(16, i, HEAPID_FIELD);
		}

		// リソースマネージャ用ヘッダ領域を作成
		size = CLACT_U_ResManagerGetHeaderSize();
		DT_clact->resHeader = sys_AllocMemory(HEAPID_FIELD, size * 6);
		
		// リソースマネージャ用ヘッダ読み込み
		// char
		res_head = CLACT_U_ResManagerGetHeaderNoData(DT_clact->resHeader, 0);
		buff = sys_LoadFile( HEAPID_FIELD, "data/uground_char.resdat" );
		
		CLACT_U_ResManagerHeaderLoadBinary(
				buff,	// キャラクタ
				res_head, HEAPID_FIELD);
		sys_FreeMemoryEz( buff );

		// pltt
		res_head = CLACT_U_ResManagerGetHeaderNoData(DT_clact->resHeader, 1);
		buff = sys_LoadFile( HEAPID_FIELD, "data/uground_pltt.resdat" );
		CLACT_U_ResManagerHeaderLoadBinary(
				buff,	// パレット
				res_head, HEAPID_FIELD);
		sys_FreeMemoryEz( buff );
		
		// cell
		res_head = CLACT_U_ResManagerGetHeaderNoData(DT_clact->resHeader, 2);
		buff = sys_LoadFile( HEAPID_FIELD, "data/uground_cell.resdat" );
		CLACT_U_ResManagerHeaderLoadBinary(
				buff,	// セル
				res_head, HEAPID_FIELD);
		sys_FreeMemoryEz( buff );
		
		// cellanm
		res_head = CLACT_U_ResManagerGetHeaderNoData(DT_clact->resHeader, 3);
		buff = sys_LoadFile( HEAPID_FIELD, "data/uground_cellanm.resdat" );
		CLACT_U_ResManagerHeaderLoadBinary(
				buff,	// セルアニメ
				res_head, HEAPID_FIELD);
		sys_FreeMemoryEz( buff );
		
		res_head = CLACT_U_ResManagerGetHeaderNoData(DT_clact->resHeader, 4);
		CLACT_U_ResManagerHeaderLoad("data/dt_test_res_multi.txt",	// マルチセル
				res_head, HEAPID_FIELD);
		
		res_head = CLACT_U_ResManagerGetHeaderNoData(DT_clact->resHeader, 5);
		CLACT_U_ResManagerHeaderLoad("data/dt_test_res_multianm.txt",// マルチセルアニメ
				res_head, HEAPID_FIELD);//*/

		/*
		res_head = CLACT_U_ResManagerGetHeaderNoData(DT_clact->resHeader, 0);
		CLACT_U_ResManagerHeaderLoad("data/dt_test_res_char.txt",	// キャラクタ
				res_head, HEAPID_FIELD);

		res_head = CLACT_U_ResManagerGetHeaderNoData(DT_clact->resHeader, 1);
		CLACT_U_ResManagerHeaderLoad("data/dt_test_res_pltt.txt",	// パレット
				res_head, HEAPID_FIELD);
		
		res_head = CLACT_U_ResManagerGetHeaderNoData(DT_clact->resHeader, 2);
		CLACT_U_ResManagerHeaderLoad("data/dt_test_res_cell.txt",	// セル
				res_head, HEAPID_FIELD);
		
		res_head = CLACT_U_ResManagerGetHeaderNoData(DT_clact->resHeader, 3);
		CLACT_U_ResManagerHeaderLoad("data/dt_test_res_cellanm.txt",	// セルアニメ
				res_head, HEAPID_FIELD);
		
		res_head = CLACT_U_ResManagerGetHeaderNoData(DT_clact->resHeader, 4);
		CLACT_U_ResManagerHeaderLoad("data/dt_test_res_multi.txt",	// マルチセル
				res_head, HEAPID_FIELD);
		
		res_head = CLACT_U_ResManagerGetHeaderNoData(DT_clact->resHeader, 5);
		CLACT_U_ResManagerHeaderLoad("data/dt_test_res_multianm.txt",// マルチセルアニメ
				res_head, HEAPID_FIELD);//*/
		

		// リソースマネージャに登録するデータ読み込み
		//
		// リソースオブジェテーブル作成
		res_head = CLACT_U_ResManagerGetHeaderNoData(DT_clact->resHeader, 0);
		size = CLACT_U_ResManagerHeaderSetDataNum(res_head);
		DT_clact->resObjTbl[0] = CLACT_U_ResManagerResObjTblMake(size, HEAPID_FIELD);
		
		// キャラクタデータ読み込み
		DT_clact->resObjNum[0] = CLACT_U_ResManagerResAddsHd(
				DT_clact->resMan[0],
				res_head,
				DT_clact->resObjTbl[0],
				HEAPID_FIELD);
		
		// リソースオブジェテーブル作成
		res_head = CLACT_U_ResManagerGetHeaderNoData(DT_clact->resHeader, 1);
		size = CLACT_U_ResManagerHeaderSetDataNum(res_head);
		DT_clact->resObjTbl[1] = CLACT_U_ResManagerResObjTblMake(size, HEAPID_FIELD);
		
		// パレットデータ読み込み
		DT_clact->resObjNum[1] = CLACT_U_ResManagerResAddsHd(
				DT_clact->resMan[1],
				res_head,
				DT_clact->resObjTbl[1],
				HEAPID_FIELD);

		// その他リソースオブジェテーブルを作成しなくても良いリソース読み込み
		// （IDの取得、リソース取得などにリソースオブジェは必要です。）
		for(i=CLACT_U_CELL_RES;i<=CLACT_U_MULTIANM_RES;i++){
			res_head = CLACT_U_ResManagerGetHeaderNoData(DT_clact->resHeader, i);
			DT_clact->resObjNum[i] = CLACT_U_ResManagerResAddsHd(
					DT_clact->resMan[i],
					res_head,
					NULL,
					HEAPID_FIELD);
		}

		
		// キャラクタ読み込み開始オフセット設定
		CharLoadStartAll();

		// パレット読み込み開始オフセット設定
		PlttLoadStartAll();

//		GX_SetOBJVRamModeChar( GX_OBJVRAMMODE_CHAR_2D );
//		GXS_SetOBJVRamModeChar( GX_OBJVRAMMODE_CHAR_2D );
		GX_SetOBJVRamModeChar( GX_OBJVRAMMODE_CHAR_1D_32K );
		GXS_SetOBJVRamModeChar( GX_OBJVRAMMODE_CHAR_1D_32K );
		
		{
			int i;
			for(i=0; i< 5; i++){
				// キャラクタマネージャに登録
				// Vramに配置します。
				CLACT_U_CharManagerSetsCharModeAdjustAreaCont(DT_clact->resObjTbl[0]);

				CLACT_U_CharManagerDeletes(DT_clact->resObjTbl[0]);
			}
		}
		CLACT_U_CharManagerSetsCharModeAdjustAreaCont(DT_clact->resObjTbl[0]);

		// パレットマネージャに登録
		// Vramに配置します。
		{
			int i;
			for(i=0;i<10;i++){
				CLACT_U_PlttManagerSetsCleanArea(DT_clact->resObjTbl[1]);
				CLACT_U_PlttManagerDeletes(DT_clact->resObjTbl[1]);
			}
			CLACT_U_PlttManagerSetsCleanArea(DT_clact->resObjTbl[1]);
		}

		// セルアクターヘッダ読み込み
		buff = sys_LoadFile( HEAPID_FIELD, "data/uground_clact.cldat" );
		DT_clact->clactHeader = CLACT_U_MakeHeaderBinary(
				buff,HEAPID_FIELD,
				DT_clact->resMan[0], DT_clact->resMan[1], DT_clact->resMan[2],
				DT_clact->resMan[3], DT_clact->resMan[4], DT_clact->resMan[5]);
		sys_FreeMemoryEz( buff );

		// セルアクター登録数初期化
		DT_clact->tcb = TCB_Add(MainCLACT_Check, DT_clact, 8);
	
		//ウィンドウ解放
		FreeDebugWindow(tcb,work);
		//タスク消去
		TCB_Delete(tcb);

		// メインリストセット
		mainlistStart();//*/

	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	メイン関数（登録破棄）
 *
 *@param	tcb
 *@param	work 
 *
 *@return
 *
 *
 */
//-----------------------------------------------------------------------------
static void MainCLACT_Check( TCB_PTR tcb,void* work )
{
	static count;
	DT_CLACT* data = (DT_CLACT*)work;
	CLACT_ADD add;
	CLACT_HEADER_PTR head;
	int i;

	// Aで登録
	if(sys.trg & PAD_BUTTON_A){
		if(data->add_num < 10){
			
			add.ClActSet	= data->clactSet;
			add.ClActHeader	= &data->clactHeader->tbl[0];
			
			// Vram転送の時はImageProxy再取得
		/*	if(data->clactHeader->tbl[1].flag == 1){
				head = &data->clactHeader->tbl[2];
				head->pImageProxy = GetCharVramTransProxyCopy(head->pImageProxy, head->pCellBank->pVramTransferData->szByteMax);
			}//*/
			
			add.mat.x		= FX32_CONST(32) * (count + 1);
			add.mat.y		= FX32_CONST(96) + SUB_SURFACE_Y;
			add.mat.z		= 0;
			add.sca.x		= FX32_ONE;
			add.sca.y		= FX32_ONE;
			add.sca.z		= FX32_ONE;
			add.rot			= 0;
			add.pri			= 0;
			add.DrawArea	= 2;
			add.heap		= HEAPID_FIELD;
			data->clact_w[data->add_num] = CLACT_Add(&add);
			CLACT_SetAffineParam( data->clact_w[ data->add_num ], CLACT_AFFINE_NORMAL );
			data->add_num++;
			count = (count + 1) % 3;
		}
	}//*/

	// オブジェがあったらアニメさせる
	for(i=0;i<data->add_num;i++){
		static count = 0;
		CLACT_SetRotation(data->clact_w[i], count);
		count = (count + 182) % (360*182);
	}

	if(sys.trg & PAD_BUTTON_L){
		CLACT_SetFlip(data->clact_w[ 0 ], CLACT_FLIP_HV);
	}
	if(sys.trg & PAD_BUTTON_Y){
		CLACT_SetAffineParam(data->clact_w[ 0 ], CLACT_AFFINE_NORMAL);
	}
	if(sys.trg & PAD_BUTTON_B){
		CLACT_SetFlip( data->clact_w[ 0 ], CLACT_FLIP_NONE );
		CLACT_SetAffineParam( data->clact_w[ 0 ], CLACT_AFFINE_NONE );
	}
	
	// Bで破棄
/*	if(sys.trg & PAD_BUTTON_B){
		if(data->add_num > 0){
			data->add_num--;
			CLACT_Delete(data->clact_w[data->add_num]);
		}
	}//*/


	// 描画
	CLACT_Draw(data->clactSet);

	// Vram転送タスクを設定
	UpdateCellTransfer();

	// VBlank関数（本当はVブランク期間中）
	// レンダラー共有OAMマネージャのOAM転送
//	REND_OAMTrans();		共有OAMマネージャデータの転送はfieldmap.cで実行済み
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	終了処理
 *
 *@param	tcb
 *@param	work 
 *
 *@return
 *
 *
 */
//-----------------------------------------------------------------------------
static void EndCLACT_Check( TCB_PTR tcb,void* work )
{
	int i;
	CLACT_U_RES_HEADER_PTR res_head;
	
	if(DT_clact != NULL){
		// OAM描画停止
		GF_Disp_GX_VisibleControl( GX_PLANEMASK_OBJ, VISIBLE_OFF );
		
		// アクターセット破棄
		CLACT_DestSet(DT_clact->clactSet);

		// セルアクターヘッダー破棄
		CLACT_U_CLACT_HeaderTblDelete(DT_clact->clactHeader);

		// リソースヘッダー破棄
		for(i=0;i<= CLACT_U_MULTIANM_RES;i++){
			res_head = CLACT_U_ResManagerGetHeaderNoData(DT_clact->resHeader, i);
			CLACT_U_ResManagerHeaderFree(res_head);
		}
		sys_FreeMemoryEz(DT_clact->resHeader);

		// キャラクタデータ破棄
		CLACT_U_CharManagerDeletes( DT_clact->resObjTbl[0] );
		
		// パレットデータ破棄
		CLACT_U_PlttManagerDeletes( DT_clact->resObjTbl[1] );
	
		// キャラクタとパレットのリソースオブジェテーブルを破棄
		for(i=0;i<2;i++){
			CLACT_U_ResManagerResObjTblDelete(DT_clact->resObjTbl[i]);
		}
		
		// リソースマネージャ破棄
		for(i=0;i<=CLACT_U_MULTIANM_RES;i++){
			CLACT_U_ResManagerDelete(DT_clact->resMan[i]);
		}

		// セルVram転送マネージャ破棄
		DeleteCellTransfer(DT_clact->cellTransArray);


		// キャラクタマネージャ破棄
		DeleteCharManager();

		// パレットマネージャ破棄
		DeletePlttManager();
		
		// レンダラー共有OAMマネージャ破棄
//		REND_OAM_Delete();		 共有OAMの破棄はfieldmap.cが行います。

		// tcb破棄
		TCB_Delete(DT_clact->tcb);
		sys_FreeMemoryEz(DT_clact);
		DT_clact = NULL;

		//ウィンドウ解放
		FreeDebugWindow(tcb,work);
		//タスク消去
		TCB_Delete(tcb);

		// メインリストセット
		mainlistStart();//*/
	}
}

#ifdef D_TOMOYA_MATERIAL_ON
/*[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
 *				マテリアル
 [[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[*/

//----------------------------------------------------------------------------
/**
 *
 *@brief	マテリアルのデバックウィンドウスタート
 *
 *@param	タスク用
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void StartMaterialWindow( TCB_PTR tcb,void* work )
{
	int i;		// ループ用

	// タスクをセット
	if(MaterialWinFlag == 0){
		MaterialWinFlag = 1;
		if(D_TomoyaFldSys->light_cont_data->DataNum > 0){
		
			DebugMaterial = &D_TomoyaFldSys->light_cont_data->pDataTbl[0];	// 操作するテーブルセット

			SetVecsRotas( MaterialrotaY, MaterialrotaXZ, DebugMaterial );
		
			materialTCBData =  TCB_Add(MainMaterialWindow,NULL,8);

			// 入力を取るタイミング
			MT_InputNow = MT_INPUT_MAX;
			MT_InputCount = 0;

		
			GF_BGL_BGControlExit( D_TomoyaFldSys->bgl, FLD_SBGFRM_EFFECT1 );
			// 描画面を作成
			{	// SUB DISP BG1
				GF_BGL_BGCNT_HEADER SBg1_Data = {
					0, 0, 0x800, 0,
					GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
					GX_BG_SCRBASE_0x4000, GX_BG_CHARBASE_0x00000,
					GX_BG_EXTPLTT_01, 0, 0, 0, FALSE
				};
				GF_BGL_BGControlSet( D_TomoyaFldSys->bgl, FLD_SBGFRM_EFFECT1, &SBg1_Data, GF_BGL_MODE_TEXT );
			}//*/

			D_M_win = initBmpWin(1);
			GF_BGL_BmpWinAdd(D_TomoyaFldSys->bgl, D_M_win, FLD_SBGFRM_EFFECT1, 0, 0, 24, 20, 0, 1 );

			GF_Disp_GXS_VisibleControl( GX_PLANEMASK_BG0, VISIBLE_OFF );
			GF_Disp_GXS_VisibleControl( GX_PLANEMASK_BG1, VISIBLE_ON );
			GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG3, VISIBLE_OFF );

			DrawMenu(MaterialCount);
		}
		//ウィンドウ解放
		FreeDebugWindow(tcb,work);
		//タスク消去
		TCB_Delete(tcb);
	
		// メインリストセット
		mainlistStart();
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	マテリアルのデバックウィンドウ終了
 *
 *@param	タスク用
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void EndMaterialWindow( TCB_PTR tcb,void* work )
{
	int i;

	
	if(MaterialWinFlag == 1){
		MaterialWinFlag = 0;
		TCB_Delete(materialTCBData);		// タスク破棄
		materialTCBData = NULL;
			
		// 描画面
		delBmpWin(D_M_win);
		D_M_win = NULL;

		GF_BGL_BGControlExit( D_TomoyaFldSys->bgl, FLD_SBGFRM_EFFECT1 );
		
		GF_Disp_GXS_VisibleControl( GX_PLANEMASK_BG0, VISIBLE_ON );
		GF_Disp_GXS_VisibleControl( GX_PLANEMASK_BG1, VISIBLE_OFF );
		//GF_BGL_BGControlExit( FLD_SBGFRM_EFFECT1 );
		//ウィンドウ解放
		FreeDebugWindow(tcb,work);
		//タスク消去
		TCB_Delete(tcb);
	
		// メインリストセット
		mainlistStart();
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	マテリアルのデバックウィンドウメイン
 *
 *@param	タスク用
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void MainMaterialWindow( TCB_PTR tcb,void* work )
{
	int i;			// ループ用
	s16 data;		// 作業用
	u8	draw_flag = 0;	// 描画書き換えフラグ

	KeyNoTouchFlag = 1;// キーロック
	GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG3, VISIBLE_OFF );	// 表示オフ

	
	if(sys.trg & PAD_KEY_LEFT){
		MaterialCount--;
		if(MaterialCount < 0){
			MaterialCount += DEB_MATE_NUM;
		}
		draw_flag = 1;
		
	}

	if(sys.trg & PAD_KEY_RIGHT){
		MaterialCount = (MaterialCount + 1) % DEB_MATE_NUM;
		draw_flag = 1;
	}

	// 上が押されていてほかのボタンが押されていないときは最後の画面に飛ぶ
	if( (sys.cont == PAD_KEY_UP) ){
		MaterialCount = DEB_WIN;
	}


	// L,Rでデータを変更
	if(sys.trg & PAD_BUTTON_L){
		MaterialDataNo--;
		if(MaterialDataNo < 0){
			MaterialDataNo += D_TomoyaFldSys->light_cont_data->DataNum;
		}
		DebugMaterial = &D_TomoyaFldSys->light_cont_data->pDataTbl[MaterialDataNo];
		
		SetVecsRotas( MaterialrotaY, MaterialrotaXZ, DebugMaterial );
		draw_flag = 1;
	}
	if(sys.trg & PAD_BUTTON_R){
		MaterialDataNo = (MaterialDataNo + 1) % D_TomoyaFldSys->light_cont_data->DataNum;
		DebugMaterial = &D_TomoyaFldSys->light_cont_data->pDataTbl[MaterialDataNo];

		SetVecsRotas( MaterialrotaY, MaterialrotaXZ, DebugMaterial );
		draw_flag = 1;
	}

	// 入力カウント
	if(MT_InputCount > 0){
		MT_InputCount--;
	}
	// UPとDOWNの入力がなかったらMT_InputNowの値を最大にする
	if(!((sys.cont & PAD_KEY_UP) ||
	   (sys.cont & PAD_KEY_DOWN))){
		MT_InputNow = MT_INPUT_MAX;
		MT_InputCount = 0;
	}

	i = 0;
	
	// 各マテリアルの値を変更
	switch(MaterialCount){
	case DEB_MATE_LIGHT_END:		// ライト終了フレーム数
		if(sys.cont & PAD_BUTTON_B){
			draw_flag |= NumInput(&(DebugMaterial->lightEnd), 1, 0xffffffff);
		}
		if(sys.cont & PAD_BUTTON_A){
			draw_flag |= NumInput(&(DebugMaterial->lightEnd), 10, 0xffffffff);
		}
		if(sys.cont & PAD_BUTTON_X){
			draw_flag |= NumInput(&(DebugMaterial->lightEnd), 100, 0xffffffff);
		}
		if(sys.cont & PAD_BUTTON_Y){
			draw_flag |= NumInput(&(DebugMaterial->lightEnd), 1000, 0xffffffff);
		}
		
		break;
		
	case DEB_MATE_LIGHT_FLAG:		// どのライトを使用するか
		if(sys.trg & PAD_BUTTON_Y){	// 0
			DebugMaterial->lightFlag ^= 0x01;
			draw_flag = 1;
		}
		if(sys.trg & PAD_BUTTON_X){	//1
			DebugMaterial->lightFlag ^= 0x02;
			draw_flag = 1;
		}
		if(sys.trg & PAD_BUTTON_A){	//2
			DebugMaterial->lightFlag ^= 0x04;
			draw_flag = 1;
		}
		if(sys.trg & PAD_BUTTON_B){	//3
			DebugMaterial->lightFlag ^=0x08;
			draw_flag = 1;
		}
		break;
		
		
	case DEB_MATE_LIGHT_COLOR_3:
		i++;
	case DEB_MATE_LIGHT_COLOR_2:
		i++;
	case DEB_MATE_LIGHT_COLOR_1:	
		i++;
	case DEB_MATE_LIGHT_COLOR_0:	// ライトのカラー
		if(MT_InputCount == 0){
			if(sys.cont & PAD_BUTTON_Y){	// 赤
				data = DebugMaterial->lightColor[i];
				data &= 0x001f;
				draw_flag |= ColorInput(&data);				// 入力
				DebugMaterial->lightColor[i] &= 0xffe0;		// 0クリア
				DebugMaterial->lightColor[i] |= data;
			}

			if(sys.cont & PAD_BUTTON_X){
				data = DebugMaterial->lightColor[i] >> 5;
				data &= 0x001f;
				draw_flag |= ColorInput(&data);				// 入力
				DebugMaterial->lightColor[i] &= 0xfc1f;		// 0クリア
				DebugMaterial->lightColor[i] |= data << 5;
			}

			if(sys.cont & PAD_BUTTON_A){
				data = DebugMaterial->lightColor[i] >> 10;
				draw_flag |= ColorInput(&data);				// 入力
				DebugMaterial->lightColor[i] &= 0x03ff;		// 0クリア
				DebugMaterial->lightColor[i] |= data << 10;
			}
		}
		break;

	case DEB_MATE_LIGHT_VEC_3:
		i++;
	case DEB_MATE_LIGHT_VEC_2:
		i++;
	case DEB_MATE_LIGHT_VEC_1:	
		i++;
	case DEB_MATE_LIGHT_VEC_0:	// ライトのベクトル
		
		draw_flag |= VecInput(&MaterialrotaY[i], &MaterialrotaXZ[i]);

		// 今の回転角からベクトルを算出
		if(draw_flag == 1){
			DebugMaterial->lightVec[i].x = FX_Mul(FX_SinIdx(MaterialrotaXZ[i]), FX_CosIdx(MaterialrotaY[i]));
			DebugMaterial->lightVec[i].z = FX_Mul(FX_CosIdx(MaterialrotaXZ[i]), FX_CosIdx(MaterialrotaY[i]));
			DebugMaterial->lightVec[i].y = FX_SinIdx(MaterialrotaY[i]);
		}
		/*if(sys.cont & PAD_BUTTON_Y){	// X
			draw_flag |= VecInput(&DebugMaterial->lightVec[i].x);
		}

		if(sys.cont & PAD_BUTTON_X){	// Y
			draw_flag |= VecInput(&DebugMaterial->lightVec[i].y);
		}

		if(sys.cont & PAD_BUTTON_A){	// Z
			draw_flag |= VecInput(&DebugMaterial->lightVec[i].z);
		}*/
		break;

	case DEB_MATE_DIFFUSE:	// ディフューズ
		if(sys.cont & PAD_BUTTON_Y){	// 赤
			data = DebugMaterial->diffuse;
			data &= 0x001f;
			draw_flag |= ColorInput(&data);			// 入力
			DebugMaterial->diffuse &= 0xffe0;		// 0クリア
			DebugMaterial->diffuse |= data;
		}

		if(sys.cont & PAD_BUTTON_X){
			data = DebugMaterial->diffuse >> 5;
			data &= 0x001f;
			draw_flag |= ColorInput(&data);			// 入力
			DebugMaterial->diffuse &= 0xfc1f;		// 0クリア
			DebugMaterial->diffuse |= data << 5;
		}

		if(sys.cont & PAD_BUTTON_A){
			data = DebugMaterial->diffuse >> 10;
			draw_flag |= ColorInput(&data);			// 入力
			DebugMaterial->diffuse &= 0x03ff;		// 0クリア
			DebugMaterial->diffuse |= data << 10;
		}
		break;

	case DEB_MATE_AMBIENT:	// アンビエント
		if(sys.cont & PAD_BUTTON_Y){	// 赤
			data = DebugMaterial->ambient;
			data &= 0x001f;
			draw_flag |= ColorInput(&data);			// 入力
			DebugMaterial->ambient &= 0xffe0;		// 0クリア
			DebugMaterial->ambient |= data;
		}

		if(sys.cont & PAD_BUTTON_X){
			data = DebugMaterial->ambient >> 5;
			data &= 0x001f;
			draw_flag |= ColorInput(&data);			// 入力
			DebugMaterial->ambient &= 0xfc1f;		// 0クリア
			DebugMaterial->ambient |= data << 5;
		}

		if(sys.cont & PAD_BUTTON_A){
			data = DebugMaterial->ambient >> 10;
			draw_flag |= ColorInput(&data);			// 入力
			DebugMaterial->ambient &= 0x03ff;		// 0クリア
			DebugMaterial->ambient |= data << 10;
		}
		break;

	case DEB_MATE_SPECULAR:	// スペキュラー
		if(sys.cont & PAD_BUTTON_Y){	// 赤
			data = DebugMaterial->specular;
			data &= 0x001f;
			draw_flag |= ColorInput(&data);			// 入力
			DebugMaterial->specular &= 0xffe0;		// 0クリア
			DebugMaterial->specular |= data;
		}

		if(sys.cont & PAD_BUTTON_X){
			data = DebugMaterial->specular >> 5;
			data &= 0x001f;
			draw_flag |= ColorInput(&data);			// 入力
			DebugMaterial->specular &= 0xfc1f;		// 0クリア
			DebugMaterial->specular |= data << 5;
		}

		if(sys.cont & PAD_BUTTON_A){
			data = DebugMaterial->specular >> 10;
			draw_flag |= ColorInput(&data);			// 入力
			DebugMaterial->specular &= 0x03ff;		// 0クリア
			DebugMaterial->specular |= data << 10;
		}
		break;

	case DEB_MATE_EMISSION:	// 放射色
		if(sys.cont & PAD_BUTTON_Y){	// 赤
			data = DebugMaterial->emission;
			data &= 0x001f;
			draw_flag |= ColorInput(&data);			// 入力
			DebugMaterial->emission &= 0xffe0;		// 0クリア
			DebugMaterial->emission |= data;
		}

		if(sys.cont & PAD_BUTTON_X){
			data = DebugMaterial->emission >> 5;
			data &= 0x001f;
			draw_flag |= ColorInput(&data);			// 入力
			DebugMaterial->emission &= 0xfc1f;		// 0クリア
			DebugMaterial->emission |= data << 5;
		}

		if(sys.cont & PAD_BUTTON_A){
			data = DebugMaterial->emission >> 10;
			data &= 0x001f;
			draw_flag |= ColorInput(&data);			// 入力
			DebugMaterial->emission &= 0x03ff;		// 0クリア
			DebugMaterial->emission |= data << 10;
		}
		break;

	case DEB_WIN:	// デバックウィンドウに渡す
		KeyNoTouchFlag = 0;
		GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG3, VISIBLE_ON );	// 表示オフ
		break;

	default:
		break;
	}
	
	// 描画
	if(draw_flag == 1){
		DrawMenu(MaterialCount);
	}
	
	// ライト設定
	for(i=0;i<4;i++){
		if((DebugMaterial->lightFlag & (1<<i)) != 0){
			GLST_LightVector(D_TomoyaFldSys->light_cont_data->Glb, i, DebugMaterial->lightVec[i].x, DebugMaterial->lightVec[i].y, DebugMaterial->lightVec[i].z);
			GLST_LightColor(D_TomoyaFldSys->light_cont_data->Glb, i,DebugMaterial->lightColor[i]);
		}else{
			GLST_LightVector(D_TomoyaFldSys->light_cont_data->Glb, i, 0,0,0);
			GLST_LightColor(D_TomoyaFldSys->light_cont_data->Glb, i,0);
		}
	}
	// ディフューズ、アンビエント、スペキュラー、放射光
	GLST_MaterialDiff(D_TomoyaFldSys->light_cont_data->Glb, DebugMaterial->diffuse,FALSE,FALSE);
	GLST_MaterialAmb(D_TomoyaFldSys->light_cont_data->Glb, DebugMaterial->ambient,TRUE);
	GLST_MaterialSpec(D_TomoyaFldSys->light_cont_data->Glb, DebugMaterial->specular,FALSE,FALSE);
	GLST_MaterialEmi(D_TomoyaFldSys->light_cont_data->Glb, DebugMaterial->emission,TRUE);
	// ライトフラグ
	GLST_MdlLightFlag(D_TomoyaFldSys->light_cont_data->Glb, DebugMaterial->lightFlag, TRUE, TRUE);
}

// ナンバーのデータを描画
static void DrawMenu( u32 num )
{
	MSGDATA_MANAGER* man;
	int i;			// ループ用
	int work;		// 作業用

	man = MSGMAN_Create(MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_debug_tomoya_dat, HEAPID_BASE_APP);

	// クリア
	GF_BGL_BmpWinDataFill(D_M_win, 1 );

	// Menuを描画
	PrintString(D_M_win, FONT_SYSTEM, man, pD_M_str[num], D_M_MENU_X, D_M_MENU_Y, 0, NULL );

	// L,Rを描画
	PrintString(D_M_win, FONT_SYSTEM, man, D_M_TMP_CH, D_M_MENU_X, D_M_SELECT, 0, NULL );

	i=0;
	// データを描画
	switch(num){
	case DEB_MATE_LIGHT_END:		// ライト終了フレーム
		DrawNum(DebugMaterial->lightEnd, D_M_NUM_X, D_M_0, D_M_win);
		PrintString(D_M_win, FONT_SYSTEM, man, D_M_FRAME0, D_M_KEY_X, D_M_0, 0, NULL );			// key
		PrintString(D_M_win, FONT_SYSTEM, man, D_M_FRAME1, D_M_KEY_X, D_M_1, 0, NULL );			// key
		PrintString(D_M_win, FONT_SYSTEM, man, D_M_FRAME2, D_M_KEY_X, D_M_2, 0, NULL );			// key
		PrintString(D_M_win, FONT_SYSTEM, man, D_M_FRAME3, D_M_KEY_X, D_M_3, 0, NULL );			// key
		break;

	case DEB_MATE_LIGHT_FLAG:		// on off
		// ライト１
		PrintString(D_M_win, FONT_SYSTEM, man, D_M_LIGHT1, D_M_MENU_X, D_M_0, 0, NULL );
		if(DebugMaterial->lightFlag & 1){		// on/off
			PrintString(D_M_win, FONT_SYSTEM, man, D_M_on, D_M_NUM_X, D_M_0, 0, NULL );
		}else{
			PrintString(D_M_win, FONT_SYSTEM, man, D_M_off, D_M_NUM_X, D_M_0, 0, NULL );	
		}
		PrintString(D_M_win, FONT_SYSTEM, man, D_M_Y, D_M_KEY_X, D_M_0, 0, NULL );			// key
		// ライト２
		PrintString(D_M_win, FONT_SYSTEM, man, D_M_LIGHT2, D_M_MENU_X, D_M_1, 0, NULL );
		if(DebugMaterial->lightFlag & 2){		// on/off
			PrintString(D_M_win, FONT_SYSTEM, man, D_M_on, D_M_NUM_X, D_M_1, 0, NULL );
		}else{
			PrintString(D_M_win, FONT_SYSTEM, man, D_M_off, D_M_NUM_X, D_M_1, 0, NULL );	
		}
		PrintString(D_M_win, FONT_SYSTEM, man, D_M_X, D_M_KEY_X, D_M_1, 0, NULL );			// key
		// ライト３
		PrintString(D_M_win, FONT_SYSTEM, man, D_M_LIGHT3, D_M_MENU_X, D_M_2, 0, NULL );
		if(DebugMaterial->lightFlag & 4){		// on/off
			PrintString(D_M_win, FONT_SYSTEM, man, D_M_on, D_M_NUM_X, D_M_2, 0, NULL );
		}else{
			PrintString(D_M_win, FONT_SYSTEM, man, D_M_off, D_M_NUM_X, D_M_2, 0, NULL );	
		}
		PrintString(D_M_win, FONT_SYSTEM, man, D_M_A, D_M_KEY_X, D_M_2, 0, NULL );			// key
		// ライト４
		PrintString(D_M_win, FONT_SYSTEM, man, D_M_LIGHT4, D_M_MENU_X, D_M_3, 0, NULL );
		if(DebugMaterial->lightFlag & 8){		// on/off
			PrintString(D_M_win, FONT_SYSTEM, man, D_M_on, D_M_NUM_X, D_M_3, 0, NULL );
		}else{
			PrintString(D_M_win, FONT_SYSTEM, man, D_M_off, D_M_NUM_X, D_M_3, 0, NULL );	
		}
		PrintString(D_M_win, FONT_SYSTEM, man, D_M_B, D_M_KEY_X, D_M_3, 0, NULL );			// key
		break;

	case DEB_MATE_LIGHT_COLOR_3:
		i++;
	case DEB_MATE_LIGHT_COLOR_2:
		i++;
	case DEB_MATE_LIGHT_COLOR_1:	
		i++;
	case DEB_MATE_LIGHT_COLOR_0:	// ライトの色
		DrawRGB(DebugMaterial->lightColor[i]);	
		break;
		

	case DEB_MATE_LIGHT_VEC_3:
		i++;
	case DEB_MATE_LIGHT_VEC_2:
		i++;
	case DEB_MATE_LIGHT_VEC_1:	
		i++;
	case DEB_MATE_LIGHT_VEC_0:	// ライトのベクトル
		// X座標
		PrintString(D_M_win, FONT_SYSTEM, man, D_M_X, D_M_MENU_X, D_M_0, 0, NULL );
		work = FX_FX16_TO_F32(DebugMaterial->lightVec[i].x)*10;
		DrawNum(DebugMaterial->lightVec[i].x, D_M_NUM_X, D_M_0, D_M_win);
		PrintString(D_M_win, FONT_SYSTEM, man, D_M_Xb, D_M_KEY_X, D_M_0, 0, NULL );			// key
		// Y座標
		PrintString(D_M_win, FONT_SYSTEM, man, D_M_Y, D_M_MENU_X, D_M_1, 0, NULL );
		work = FX_FX16_TO_F32(DebugMaterial->lightVec[i].y)*10;
		DrawNum(DebugMaterial->lightVec[i].y, D_M_NUM_X, D_M_1, D_M_win);
		PrintString(D_M_win, FONT_SYSTEM, man, D_M_Bb, D_M_KEY_X, D_M_1, 0, NULL );			// key
		// Z座標
		PrintString(D_M_win, FONT_SYSTEM, man, D_M_Z, D_M_MENU_X, D_M_2, 0, NULL );
		work = FX_FX16_TO_F32(DebugMaterial->lightVec[i].z)*10;
		DrawNum(DebugMaterial->lightVec[i].z, D_M_NUM_X, D_M_2, D_M_win);
		PrintString(D_M_win, FONT_SYSTEM, man, D_M_Yb, D_M_KEY_X, D_M_2, 0, NULL );			// key
		PrintString(D_M_win, FONT_SYSTEM, man, D_M_Ab, D_M_KEY_X, D_M_3, 0, NULL );			// key
		break;

	case DEB_MATE_DIFFUSE:		// ディフューズ色
		DrawRGB(DebugMaterial->diffuse);	
		break;
	
	case DEB_MATE_AMBIENT:		// アンビエント色
		DrawRGB(DebugMaterial->ambient);	
		break;

	case DEB_MATE_SPECULAR:		// スペキュラー色
		DrawRGB(DebugMaterial->specular);
		break;

	case DEB_MATE_EMISSION:		// 放射色
		DrawRGB(DebugMaterial->emission);
		break;

	default:
		break;
	}

	GF_BGL_BmpWinOn(D_M_win );
	MSGMAN_Delete(man);
}

static u8 NumInput(u32* num, u32 add, u32 limit)
{
	u8 draw_flag = 0;
	
	if(MT_InputCount == 0){
		if(sys.cont & PAD_KEY_UP){
			*num = (*num + add) % limit;
			draw_flag = 1;
		}
		if(sys.cont & PAD_KEY_DOWN){
			(*num)-=add;
			if(*num < 0){
				*num += limit;
			}
			draw_flag = 1;
		}
	}

	if(draw_flag == 1){
		if((MT_InputNow - MT_INPUT_SUB) > MT_INPUT_MIN){
			MT_InputNow-= MT_INPUT_SUB;
		}
		MT_InputCount = MT_InputNow;
	}

	return draw_flag;
}

static u8 ColorInput( s16* num )				// 色の入力
{
	u8 draw_flag = 0;
	
	if(MT_InputCount == 0){
		if(sys.cont & PAD_KEY_UP){
			*num = (*num + 1) % 32;
			draw_flag = 1;
		}
		if(sys.cont & PAD_KEY_DOWN){
			(*num)--;
			if(*num < 0){
				*num += 32;
			}
			draw_flag = 1;
		}
	}

	if(draw_flag == 1){
		if((MT_InputNow - MT_INPUT_SUB) > MT_INPUT_MIN){
			MT_InputNow-= MT_INPUT_SUB;
		}
		MT_InputCount = MT_InputNow;
	}

	return draw_flag;
}

static u8 VecInput( u16* rotaY, u16* rotaXZ )				// ベクトル入力
{
	u8 draw_flag = 0;
	
	if(MT_InputCount == 0){
		if(sys.cont & PAD_BUTTON_X){		// X軸回転アップ
			*rotaY += MT_ROT_GET(2);
			draw_flag = 1;
		}
		if(sys.cont & PAD_BUTTON_B){	// X軸回転ダウン
			*rotaY -= MT_ROT_GET(2);
			draw_flag = 1;
		}
		if(sys.cont & PAD_BUTTON_A){	// Y軸回転左へ
			*rotaXZ += MT_ROT_GET(2);
			draw_flag = 1;
		}
		if(sys.cont & PAD_BUTTON_Y){	// Y軸回転右へ
			*rotaXZ -= MT_ROT_GET(2);
			draw_flag = 1;
		}
	}

	if(draw_flag == 1){
		if((MT_InputNow - MT_INPUT_SUB) > MT_INPUT_MIN){
			MT_InputNow-= MT_INPUT_SUB;
		}
		MT_InputCount = MT_InputNow;
	}

	return draw_flag;
}

static void DrawRGB( GXRgb num )
{
	MSGDATA_MANAGER* man = MSGMAN_Create(MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_debug_tomoya_dat, HEAPID_BASE_APP);
	int work;

	// 赤
	PrintString(D_M_win, FONT_SYSTEM, man, D_M_CR, D_M_MENU_X, D_M_0, 0, NULL );
	work = num;
	work &= 0x001f;
	DrawNum(work, D_M_NUM_X, D_M_0, D_M_win);
	PrintString(D_M_win, FONT_SYSTEM, man, D_M_Ya, D_M_KEY_X, D_M_0, 0, NULL );			// key
	// 緑
	PrintString(D_M_win, FONT_SYSTEM, man, D_M_CG, D_M_MENU_X, D_M_1, 0, NULL );
	work = num >> 5;
	work &= 0x001f;
	DrawNum(work, D_M_NUM_X, D_M_1, D_M_win);
	PrintString(D_M_win, FONT_SYSTEM, man, D_M_Xa, D_M_KEY_X, D_M_1, 0, NULL );			// key
	// 青
	PrintString(D_M_win, FONT_SYSTEM, man, D_M_CB, D_M_MENU_X, D_M_2, 0, NULL );
	work = num >> 10;
	work &= 0x001f;
	DrawNum(work, D_M_NUM_X, D_M_2, D_M_win);		
	PrintString(D_M_win, FONT_SYSTEM, man, D_M_Aa, D_M_KEY_X, D_M_2, 0, NULL );			// key

	MSGMAN_Delete(man);
}


static void SetVecRota( u16* rotaY, u16* rotaXZ, fx32 X, fx32 Y, fx32 Z )
{
	fx32 xz_dis;		// 平面のベクトル
	
	// 回転角取得
	xz_dis = FX_Mul(X, X);
	xz_dis += FX_Mul(Z,Z);
	xz_dis = FX_Sqrt(xz_dis);
	
	*rotaY = FX_Atan2Idx(Y, xz_dis);
	*rotaXZ = FX_Atan2Idx(X, Z);
}


static void SetVecsRotas( u16* rotaY, u16* rotaXZ, LIGHT_CONT_DATA* light )
{
	int i;		// ループ用

	for( i=0; i<4; i++ ){
		SetVecRota( rotaY + i, rotaXZ + i,
				light->lightVec[ i ].x,
				light->lightVec[ i ].y,
				light->lightVec[ i ].z );
	}
}

#endif	// D_TOMOYA_MATERIAL_ON
//-------------------------------------
//	フォグと共通
//=====================================
static void DrawNum( s32 num, u32 x, u32 y, GF_BGL_BMPWIN* win )
{
	STRBUF* str = STRBUF_Create(12, HEAPID_BASE_APP);
	STRBUF_SetNumber( str, num, 10, NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );
	GF_STR_PrintSimple(win, FONT_SYSTEM, str, x, y, 0, NULL );
	STRBUF_Delete(str);
}
static void PrintString( GF_BGL_BMPWIN* win, u32 fontID, MSGDATA_MANAGER* man, u32 strid, u32 xofs, u32 yofs, u32 wait, pStrPrintCallBack call_back )
{
	STRBUF* str = MSGMAN_AllocString(man, strid);
	GF_STR_PrintSimple( win, fontID, str, xofs, yofs, wait, call_back );
	STRBUF_Delete(str);
}







//-----------------------------------------------------------------------------
//
//			Fog関係
//
//=============================================================================
static void StartFog( TCB_PTR tcb,void* work )
{
    int i;
	
	if(FogFlag == 0){
		// 入力を取るタイミング
		FOG_InputNow = MT_INPUT_MAX;
		FOG_InputCount = 0;


#ifdef FOG_BG_ON
		/*--------------------------------------------------------
		 *	BG2に何かを描画する準備
		 =======================================================*/
		// アルファブレンディング設定
		G2_SetBlendAlpha(GX_BLEND_PLANEMASK_BG0,
						GX_BLEND_PLANEMASK_BG2,
						0, 0);

		
		GF_BGL_BGControlExit( D_TomoyaFldSys->bgl, FLD_MBGFRM_EFFECT2 );
		{	// メイン画面のＢＧ２を設定
			GF_BGL_BGCNT_HEADER BgData = {
				0,								// 初期表示Ｘ設定
				0,								// 初期表示Ｙ設定
				0x800,							// スクリーンバッファサイズ
				0,								// スクリーンバッファオフセット
				GF_BGL_SCRSIZ_256x256,			// スクリーンサイズ 256x256
				GX_BG_COLORMODE_256,			// カラーモード 256色
				GX_BG_SCRBASE_0xf000,
				GX_BG_CHARBASE_0x08000,
				GX_BG_EXTPLTT_23,				// 拡張パレットスロット
				2,								// 表示プライオリティ
				0,								// エリアオーバーフラグ
				0,								// ダミー
				FALSE							// モザイク設定
			};

			GF_BGL_BGControlSet(D_TomoyaFldSys->bgl,  FLD_MBGFRM_EFFECT2, &BgData, GF_BGL_MODE_TEXT );
		}
		
	    GX_LoadBGPltt(d_64_256_bg_sclDT, 0, sizeof(d_64_256_bg_sclDT));
	
		{
			int i, j;
			for (i = 0; i < 32; i++)
			{
				for (j = 0; j < 32; j++)
				{
					sScrnBuf[(i * 32) + j] = (u16) (((i%7) * 0x10) + j);
				}
			}
		}
		GF_BGL_LoadScreen(D_TomoyaFldSys->bgl, FLD_MBGFRM_EFFECT2, sScrnBuf, sizeof(sScrnBuf), 0 );
		GF_BGL_ScreenBufSet(D_TomoyaFldSys->bgl, FLD_MBGFRM_EFFECT2, sScrnBuf, sizeof(sScrnBuf) );

		// キャラクターデータ読み込み
		GF_BGL_LoadCharacter(D_TomoyaFldSys->bgl,  FLD_MBGFRM_EFFECT2, d_64_256_bg_schDT, sizeof(d_64_256_bg_schDT), 0 );

		if(bg2_flag == 0){
			GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG2, VISIBLE_OFF );	
		}
#endif
			
	
		// 描画面を作成
		GF_BGL_BGControlExit( D_TomoyaFldSys->bgl, FLD_SBGFRM_EFFECT1 );
		{	// SUB DISP BG1
			GF_BGL_BGCNT_HEADER SBg1_Data = {
				0, 0, 0x800, 0,
				GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
				GX_BG_SCRBASE_0x4000, GX_BG_CHARBASE_0x00000,
				GX_BG_EXTPLTT_01, 0, 0, 0, FALSE
			};
			GF_BGL_BGControlSet( D_TomoyaFldSys->bgl, FLD_SBGFRM_EFFECT1, &SBg1_Data, GF_BGL_MODE_TEXT );
		}//*/
		FOG_win = initBmpWin(1);
		GF_BGL_BmpWinAdd(D_TomoyaFldSys->bgl, FOG_win, FLD_SBGFRM_EFFECT1, 0, 0, 24, 21, 0, 0 );

		GF_Disp_GXS_VisibleControl( GX_PLANEMASK_BG0, VISIBLE_OFF );
		GF_Disp_GXS_VisibleControl( GX_PLANEMASK_BG1, VISIBLE_ON );
	
		
		// メインタスクをセット
		FogTCBData =  TCB_Add(MainFog,NULL,8);
		FogFlag = 1;

#ifdef FOG_BG_ON
		// BGを動かすタスクセット
		if(FOG_BG_TASK == NULL){
			FOG_BG_TASK = TCB_Add(BG2Move,NULL,8);
		}
#endif

		DrawFog(FOG_Count);
		//ウィンドウ解放
		FreeDebugWindow(tcb,work);
		//タスク消去
		TCB_Delete(tcb);
	
		// メインリストセット
		mainlistStart();

	}
}

static void EndFog( TCB_PTR tcb,void* work )
{
	int i;
	
	if(FogFlag == 1){
		FogFlag = 0;
		TCB_Delete(FogTCBData);		// タスク破棄
		FogTCBData = NULL;

		SetFogData(D_TomoyaFldSys->fog_data, FOG_SYS_FLAG, TRUE, 0,0,0);		// on/offフラグを設定

#ifdef FOG_BG_ON
		TCB_Delete(FOG_BG_TASK);
		FOG_BG_TASK = NULL;

		G2_BlendNone();
		GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG2, VISIBLE_OFF );
		GF_BGL_BGControlExit( D_TomoyaFldSys->bgl, FLD_MBGFRM_EFFECT2 );
		{	// MAIN DISP（エフェクト２）
			GF_BGL_BGCNT_HEADER TextBgCntDat = {
				0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
				GX_BG_SCRBASE_0xf000, GX_BG_CHARBASE_0x08000, GX_BG_EXTPLTT_23,
				3, 0, 0, FALSE
			};
			GF_BGL_BGControlSet(D_TomoyaFldSys->bgl,  FLD_MBGFRM_EFFECT2, &TextBgCntDat, GF_BGL_MODE_TEXT );
			GF_BGL_ScrClear(D_TomoyaFldSys->bgl, FLD_MBGFRM_EFFECT2 );
		}
#endif

		// 描画面
		delBmpWin(FOG_win);
		GF_BGL_BGControlExit( D_TomoyaFldSys->bgl, FLD_SBGFRM_EFFECT1 );
		
		GF_Disp_GXS_VisibleControl( GX_PLANEMASK_BG0, VISIBLE_ON );
		GF_Disp_GXS_VisibleControl( GX_PLANEMASK_BG1, VISIBLE_OFF );
		//GF_BGL_BGControlExit( FLD_SBGFRM_EFFECT1 );
	
		//ウィンドウ解放
		FreeDebugWindow(tcb,work);
		//タスク消去
		TCB_Delete(tcb);
	
		// メインリストセット
		mainlistStart();
	}
}

// BG2面を動かす
static void BG2Move(TCB_PTR tcb,void* work)
{
#ifdef FOG_BG_ON
	// BG面をSCROLL
	if(bg2_flag == 1){
		
		Fog_BG_Count = (Fog_BG_Count + FOG_BG_SCROLL_COUNT) % (256*FOG_BG_SCROLL_PAR);		// BG面スクロールカウンタ
		G2_SetBG2Offset((Fog_BG_Count / FOG_BG_SCROLL_PAR),0);
	}
#endif
}

static void MainFog( TCB_PTR tcb,void* work )
{
	int i;
	
	KeyNoTouchFlag = 1;// キーロック

	if(sys.trg & PAD_BUTTON_SELECT){
#ifdef FOG_BG_ON
		bg2_flag = (bg2_flag + 1)%2;

		if(bg2_flag){
			GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG2, VISIBLE_ON );
		}else{
			GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG2, VISIBLE_OFF );
		}
#endif
	}

	// 入力処理
	if(sys.trg & PAD_KEY_LEFT){
		FOG_Count--;
		Fog_DrawFlag = 1;
		if(FOG_Count < 0){
			FOG_Count += FOG_TITLE_NUM;
		}
	}
	if(sys.trg & PAD_KEY_RIGHT){
		FOG_Count = (FOG_Count + 1) % FOG_TITLE_NUM;
		Fog_DrawFlag = 1;
	}

	// 入力カウント
	if(FOG_InputCount > 0){
		FOG_InputCount--;
	}
	// UPとDOWNの入力がなかったらMT_InputNowの値を最大にする
	if(!((sys.cont & PAD_KEY_UP) ||
	   (sys.cont & PAD_KEY_DOWN))){
		FOG_InputNow = MT_INPUT_MAX;
		FOG_InputCount = 0;
	}
	
	InputFog(FOG_Count);


	// 描画
	if(Fog_DrawFlag == 1){
		DrawFog(FOG_Count);
		Fog_DrawFlag = 0;
	}
	
}

static void FogColorGet( FIELDSYS_WORK* D_TomoyaFldSys,int* r, int* g, int* b )
{
	*r = (GetFogColor(D_TomoyaFldSys->fog_data) >> 0) & 0x1f;
	*g = (GetFogColor(D_TomoyaFldSys->fog_data) >> 5) & 0x1f;
	*b = (GetFogColor(D_TomoyaFldSys->fog_data) >> 10) & 0x1f;
}

// 入力
static void InputFog( int num )
{
	int	fog_flag = GetFogFlag(D_TomoyaFldSys->fog_data);
	int	fog_mode = GetFogMode(D_TomoyaFldSys->fog_data);
	int	fog_slope = GetFogSlope(D_TomoyaFldSys->fog_data);
	int fog_offset = GetFogOffset(D_TomoyaFldSys->fog_data);
	int r;
	int g;
	int b;
	int alpha = GetFogAlpha(D_TomoyaFldSys->fog_data);
	char fog_tbl[32];
	const char* p_get = GetFogTbl(D_TomoyaFldSys->fog_data);
	int i;


	FogColorGet(D_TomoyaFldSys, &r, &g, &b);
	
	for(i=0;i<32;i++){
		fog_tbl[i] = p_get[i];
	}	

	switch(num){
	case FOG_NORMAL_SET:
		
		
		if(sys.trg & PAD_BUTTON_Y){		// on/off
			fog_flag = (fog_flag + 1) % 2;
			Fog_DrawFlag = 1;
		}
		if(sys.trg & PAD_BUTTON_X){		// fog mode
			fog_mode = (fog_mode + 1) % 2;
			Fog_DrawFlag = 1;
		}
		if(sys.cont & PAD_BUTTON_A){	// 係り具合
			if(sys.trg & PAD_KEY_UP){
				fog_slope = (fog_slope + 1) % 11;
				Fog_DrawFlag = 1;
			}
			if(sys.trg & PAD_KEY_DOWN){
				fog_slope--;
				Fog_DrawFlag = 1;
				if(fog_slope < 0){
					fog_slope += 11;
				}
			}
		}

		if(FOG_InputCount == 0){
			if(sys.cont & PAD_BUTTON_B){	// どの位置からかけるか
				if(sys.cont & PAD_KEY_UP){
					fog_offset += FOG_OFS_ADD;
					Fog_DrawFlag = 1;
				}
				if(sys.cont & PAD_KEY_DOWN){
					fog_offset -= FOG_OFS_ADD;
					Fog_DrawFlag = 1;
				}
			}
		}

		SetFogData(D_TomoyaFldSys->fog_data, FOG_SYS_ALL, fog_flag, fog_mode, fog_slope, fog_offset);
		break;

	case FOG_COLOR_SET:
		if(FOG_InputCount == 0){
			if(sys.cont & PAD_BUTTON_Y){
				if(sys.cont & PAD_KEY_UP){
					r = (r + 1) % 32;
					Fog_DrawFlag = 1;
				}
				if(sys.cont & PAD_KEY_DOWN){
					r--;
					Fog_DrawFlag = 1;
					if(r < 0){
						r += 32;
					}
				}
			}
			if(sys.cont & PAD_BUTTON_X){
				if(sys.cont & PAD_KEY_UP){
					g = (g + 1) % 32;
					Fog_DrawFlag = 1;
				}
				if(sys.cont & PAD_KEY_DOWN){
					g--;
					Fog_DrawFlag = 1;
					if(g < 0){
						g += 32;
					}
				}
			}
			if(sys.cont & PAD_BUTTON_A){
				if(sys.cont & PAD_KEY_UP){
					b = (b + 1) % 32;
					Fog_DrawFlag = 1;
				}
				if(sys.cont & PAD_KEY_DOWN){
					b--;
					Fog_DrawFlag = 1;
					if(b < 0){
						b += 32;
					}
				}
			}
			if(sys.cont & PAD_BUTTON_B){
				if(sys.cont & PAD_KEY_UP){
					alpha = (alpha + 1) % 32;
					Fog_DrawFlag = 1;
				}
				if(sys.cont & PAD_KEY_DOWN){
					alpha--;
					Fog_DrawFlag = 1;
					if(alpha < 0){
						alpha += 32;
					}
				}
			}
		}
		SetFogColor(D_TomoyaFldSys->fog_data, FOG_SYS_ALL, GX_RGB(r,g,b), alpha);
		break;
	
	case FOG_TBL_SET:
		
		
		if(sys.trg & PAD_BUTTON_X){
			FOG_TBL_Count = (FOG_TBL_Count + 1) % 32;
			Fog_DrawFlag = 1;
		}
		if(sys.trg & PAD_BUTTON_B){
			FOG_TBL_Count--;
			Fog_DrawFlag = 1;
			if(FOG_TBL_Count < 0){
				FOG_TBL_Count += 32;
			}
		}

		if(FOG_InputCount == 0){
			if(sys.cont & PAD_KEY_UP){
				fog_tbl[FOG_TBL_Count] = (fog_tbl[FOG_TBL_Count] + 1) % 128;
				Fog_DrawFlag = 1;
			}
			if(sys.cont & PAD_KEY_DOWN){
				fog_tbl[FOG_TBL_Count]--;
				Fog_DrawFlag = 1;
				if(fog_tbl[FOG_TBL_Count] < 0){
					fog_tbl[FOG_TBL_Count] += 128;
				}
			}
		}
		SetFogTbl(D_TomoyaFldSys->fog_data, fog_tbl);
		break;

	default:
		KeyNoTouchFlag = 0;
		break;
	}

	if(Fog_DrawFlag == 1){
		if((FOG_InputNow - MT_INPUT_SUB) > MT_INPUT_MIN){
			FOG_InputNow-= MT_INPUT_SUB;
		}
		FOG_InputCount = FOG_InputNow;
	}
}

// 描画
static void DrawFog( int num )
{
	int	fog_flag = GetFogFlag(D_TomoyaFldSys->fog_data);
	int	fog_mode = GetFogMode(D_TomoyaFldSys->fog_data);
	int	fog_slope = GetFogSlope(D_TomoyaFldSys->fog_data);
	int fog_offset = GetFogOffset(D_TomoyaFldSys->fog_data);
	int r;
	int g;
	int b;
	int alpha = GetFogAlpha(D_TomoyaFldSys->fog_data);
	char fog_tbl[32];
	const char* p_get = GetFogTbl(D_TomoyaFldSys->fog_data);
	int i,j;		// ループ用
	int work;		// 作業用
	MSGDATA_MANAGER* man = MSGMAN_Create(MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_debug_tomoya_dat, HEAPID_BASE_APP);

	FogColorGet(D_TomoyaFldSys, &r, &g, &b);
	
	for(i=0;i<32;i++){
		fog_tbl[i] = p_get[i];
	}
	
	GF_ASSERT( FOG_win );
	
	// クリア
	GF_BGL_BmpWinDataFill(FOG_win, 1 );

	// Menuを描画
	PrintString(FOG_win, FONT_SYSTEM, man, fog_title[num], D_M_MENU_X, D_M_MENU_Y, 0, NULL );

	// BG面表示
	if(num != FOG_TBL_SET){
		PrintString(FOG_win, FONT_SYSTEM, man, fog_tbl_bg, D_M_MENU_X, D_M_SELECT, 0, NULL );
	}
	

	// 描画
	switch(num){
	case FOG_NORMAL_SET:
		// on/off
		PrintString(FOG_win, FONT_SYSTEM, man, D_M_ON_OFF, D_M_MENU_X, D_M_0, 0, NULL );
		if(fog_flag){
			PrintString(FOG_win, FONT_SYSTEM, man, D_M_on, D_M_NUM_X, D_M_0, 0, NULL );
		}else{
			PrintString(FOG_win, FONT_SYSTEM, man, D_M_off, D_M_NUM_X, D_M_0, 0, NULL );
		}
		PrintString(FOG_win, FONT_SYSTEM, man, D_M_Y, D_M_KEY_X, D_M_0, 0, NULL );
		
		// mode
		PrintString(FOG_win, FONT_SYSTEM, man, D_M_MODE, D_M_MENU_X, D_M_1, 0, NULL );
		DrawNum(fog_mode, D_M_NUM_X, D_M_1, FOG_win);	
		PrintString(FOG_win, FONT_SYSTEM, man, D_M_X, D_M_KEY_X, D_M_1, 0, NULL );
		
		// かかりぐあい
		PrintString(FOG_win, FONT_SYSTEM, man, D_M_KAKARI, D_M_MENU_X, D_M_2, 0, NULL );
		DrawNum(fog_slope, D_M_NUM_X, D_M_2, FOG_win);
		PrintString(FOG_win, FONT_SYSTEM, man, D_M_Aa, D_M_KEY_X, D_M_2, 0, NULL );

		// オフセット
		PrintString(FOG_win, FONT_SYSTEM, man, D_M_OFS, D_M_MENU_X, D_M_3, 0, NULL );
		DrawNum(fog_offset, D_M_NUM_X, D_M_3, FOG_win);
		PrintString(FOG_win, FONT_SYSTEM, man, D_M_Ba, D_M_KEY_X, D_M_3, 0, NULL );
		break;

	case FOG_COLOR_SET:
		// 赤
		PrintString(FOG_win, FONT_SYSTEM, man, D_M_CR, D_M_MENU_X, D_M_0, 0, NULL );
		DrawNum(r, D_M_NUM_X, D_M_0, FOG_win);	
		PrintString(FOG_win, FONT_SYSTEM, man, D_M_Ya, D_M_KEY_X, D_M_0, 0, NULL );
		// 緑
		PrintString(FOG_win, FONT_SYSTEM, man, D_M_CG, D_M_MENU_X, D_M_1, 0, NULL );
		DrawNum(g, D_M_NUM_X, D_M_1, FOG_win);	
		PrintString(FOG_win, FONT_SYSTEM, man, D_M_Xa, D_M_KEY_X, D_M_1, 0, NULL );
		// 青
		PrintString(FOG_win, FONT_SYSTEM, man, D_M_CB, D_M_MENU_X, D_M_2, 0, NULL );
		DrawNum(b, D_M_NUM_X, D_M_2, FOG_win);	
		PrintString(FOG_win, FONT_SYSTEM, man, D_M_Aa, D_M_KEY_X, D_M_2, 0, NULL );
		// アルファ
		PrintString(FOG_win, FONT_SYSTEM, man, D_M_CA, D_M_MENU_X, D_M_3, 0, NULL );
		DrawNum(alpha, D_M_NUM_X, D_M_3, FOG_win);	
		PrintString(FOG_win, FONT_SYSTEM, man, D_M_Ba, D_M_KEY_X, D_M_3, 0, NULL );
		break;

	case FOG_TBL_SET:
		PrintString(FOG_win, FONT_SYSTEM, man, fog_tbl_tugi, D_M_MENU_X, D_M_0, 0, NULL );
		PrintString(FOG_win, FONT_SYSTEM, man, fog_tbl_mae, D_M_NUM_X + 16, D_M_0, 0, NULL );
		PrintString(FOG_win, FONT_SYSTEM, man, fog_tbl_data, D_M_NUM_X + 8, D_M_MENU_Y, 0, NULL );
		DrawNum(fog_tbl[FOG_TBL_Count], D_M_KEY_X - 24, D_M_MENU_Y, FOG_win);

		// テーブルの中身を表示
		for(i=0;i<7;i++){
			for(j=0;j<5;j++){
				if(((i*5)+j) >= 32){
					break;
				}
				DrawNum(fog_tbl[(i*5)+j], D_M_MENU_X+(j*30), D_M_1 + (i*18), FOG_win );
			}
		}
		break;

	default:
		break;
	}

	MSGMAN_Delete(man);
}


//-----------------------------------------------------------------------------
/**
 * 
 *			図鑑データ操作
 * 
 */
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *	@brief	開始
 */
//-----------------------------------------------------------------------------
#define D_TOMO_ZKN_SOUSA_DRAW_X	( 10 )
#define D_TOMO_ZKN_SOUSA_DRAW_Y	( 0 )
#define D_TOMO_ZKN_START_DRAW_X	( 10 )
#define D_TOMO_ZKN_START_DRAW_Y	( 112 )
#define D_TOMO_ZKN_END_DRAW_X	( 10 )
#define D_TOMO_ZKN_END_DRAW_Y	( 128 )

#define D_TOMO_ZKN_NUM_DRAW_X		( 128 )
#define D_TOMO_ZKN_NUM_DRAW_W		( 64 )
#define D_TOMO_ZKN_NUM_DRAW_H		( 16 )
#define D_TOMO_ZKN_SET_START_X		( 128 )
#define D_TOMO_ZKN_SET_START_Y		( 80 )
static void StartZukanCont( TCB_PTR tcb, void* p_work )
{
	D_TOMOYA_ZUKAN_DATACONT* p_data;
	STRBUF* str;
	NUMFONT* p_num = NUMFONT_Create( 1, 2, 15, HEAPID_FIELD );

	p_data = sys_AllocMemory( HEAPID_FIELD, sizeof(D_TOMOYA_ZUKAN_DATACONT) );
	memset( p_data, 0, sizeof(D_TOMOYA_ZUKAN_DATACONT) );
	
	p_data->p_fsys = D_TomoyaFldSys;
	p_data->p_bmp = GF_BGL_BmpWinAllocGet( HEAPID_FIELD, 1 );
	GF_BGL_BmpWinAdd( p_data->p_fsys->bgl, 
			p_data->p_bmp, GF_BGL_FRAME2_M, 2, 2, 28, 18, 7, MENU_WIN_CGX_SIZ + 1 );

	// メッセージマネージャ作成
	p_data->msg_data = MSGMAN_Create( MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_debug_tomoya_dat, HEAPID_FIELD );


	// クリーン
	GF_BGL_BmpWinDataFill( p_data->p_bmp, 15 );

	// 操作方法を表示
	str = MSGMAN_AllocString( p_data->msg_data, MSG_D_ZKN_00 );
	GF_STR_PrintColor( p_data->p_bmp, FONT_SYSTEM, str, D_TOMO_ZKN_SOUSA_DRAW_X, D_TOMO_ZKN_SOUSA_DRAW_Y, MSG_NO_PUT, D_TOMOYA_ZUKAN_DRAWCOLOR, NULL );

	STRBUF_Delete( str );

	// START
	str = MSGMAN_AllocString( p_data->msg_data, MSG_D_ZKN_02 );
	GF_STR_PrintColor( p_data->p_bmp, FONT_SYSTEM, str, D_TOMO_ZKN_START_DRAW_X, D_TOMO_ZKN_START_DRAW_Y, MSG_NO_PUT, D_TOMOYA_ZUKAN_DRAWCOLOR, NULL );

	STRBUF_Delete( str );

	// END
	str = MSGMAN_AllocString( p_data->msg_data, MSG_D_ZKN_03 );
	GF_STR_PrintColor( p_data->p_bmp, FONT_SYSTEM, str, D_TOMO_ZKN_END_DRAW_X, D_TOMO_ZKN_END_DRAW_Y, MSG_NO_PUT, D_TOMOYA_ZUKAN_DRAWCOLOR, NULL );
	
	STRBUF_Delete( str );

	// 枠を描画
	MenuWinGraphicSet( p_data->p_fsys->bgl, GF_BGL_FRAME2_M, 1, 6, 0, HEAPID_FIELD );

	// 会話フォントパレット読み込み
	SystemFontPaletteLoad( PALTYPE_MAIN_BG, 7 * 32, HEAPID_FIELD );

	BmpMenuWinWrite( p_data->p_bmp, WINDOW_TRANS_ON, 1, 6 );
	p_data->p_zknwork = SaveData_GetZukanWork( p_data->p_fsys->savedata );

	ZukanWork_SetZukanGetFlag( p_data->p_zknwork );
	ZukanWork_SetZenkokuZukanFlag( p_data->p_zknwork );
	MyStatus_SetDpZenkokuFlag(SaveData_GetMyStatus(p_data->p_fsys->savedata) );

	p_data->start = 1;
	p_data->end = 1;
	NUMFONT_WriteNumber( p_num, p_data->start, 3, NUMFONT_MODE_ZERO, p_data->p_bmp, D_TOMO_ZKN_NUM_DRAW_X, D_TOMO_ZKN_START_DRAW_Y );
	NUMFONT_WriteNumber( p_num, p_data->end, 3, NUMFONT_MODE_ZERO, p_data->p_bmp, D_TOMO_ZKN_NUM_DRAW_X, D_TOMO_ZKN_END_DRAW_Y );
	GF_BGL_BmpWinOn( p_data->p_bmp );
	// ナンバーフォント破棄
	NUMFONT_Delete( p_num );

	// タスク登録
	TCB_Add( MainZukanCont, p_data, 0 );

	// BG
	GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG2, VISIBLE_ON );
	G2_SetBG2Priority(0);

	EndDebugWind(tcb, p_work);

	//イベントフック
	FieldSystemProc_SeqHold();
}


static void MainZukanContKeySousa( s32* p_count, BOOL* set_flg, s32 min, s32 max )
{
	if( sys.repeat & PAD_BUTTON_A ){
		if( (*p_count + 1) <= max ){
			(*p_count)++;
			*set_flg = TRUE;
		}else{
			(*p_count) = max;
			*set_flg = TRUE;
		}
	}else if( sys.repeat & PAD_BUTTON_Y ){
		if( (*p_count - 1) >= min ){
			(*p_count)--;
			*set_flg = TRUE;
		}else{
			(*p_count) = min;
			*set_flg = TRUE;
		}
	}
	if( sys.repeat & PAD_KEY_RIGHT ){
		if( (*p_count + 10) <= max ){
			*p_count += 10;
			*set_flg = TRUE;
		}else{
			(*p_count) = max;
			*set_flg = TRUE;
		}
	}else if( sys.repeat & PAD_KEY_LEFT ){
		if( (*p_count - 10) >= min ){
			*p_count -= 10;
			*set_flg = TRUE;
		}else{
			(*p_count) = min;
			*set_flg = TRUE;
		}
	}
	if( sys.repeat & PAD_KEY_UP ){
		if( (*p_count + 100) <= max ){
			*p_count += 100;
			*set_flg = TRUE;
		}else{
			(*p_count) = max;
			*set_flg = TRUE;
		}
	}else if( sys.repeat & PAD_KEY_DOWN ){
		if( (*p_count - 100) >= min ){
			*p_count -= 100;
			*set_flg = TRUE;
		}else{
			(*p_count) = min;
			*set_flg = TRUE;
		}
	}
}


//----------------------------------------------------------------------------
/**
 *	@brief	メイン
 */
//-----------------------------------------------------------------------------
static void MainZukanCont( TCB_PTR tcb, void* p_work )
{
	D_TOMOYA_ZUKAN_DATACONT* p_data = p_work;
	BOOL start_draw_set = FALSE;
	BOOL end_draw_set = FALSE;
	NUMFONT* p_num = NUMFONT_Create( 1, 2, 15, HEAPID_FIELD );
	int i;
	STRBUF* str;

	if( p_data->set_chuu == TRUE ){
		p_data->set_chuu = FALSE;

		GF_BGL_BmpWinFill( p_data->p_bmp, 15, D_TOMO_ZKN_SET_START_X, D_TOMO_ZKN_SET_START_Y, D_TOMO_ZKN_NUM_DRAW_W, D_TOMO_ZKN_NUM_DRAW_H );
		GF_BGL_BmpWinOn( p_data->p_bmp );
	}

	if( sys.cont & PAD_BUTTON_L ){
		MainZukanContKeySousa( &p_data->start, &start_draw_set, 1, MONSNO_END );
		if( p_data->start > p_data->end ){
			p_data->end = p_data->start;
			end_draw_set = TRUE;
		}
	}
	if( sys.cont & PAD_BUTTON_R ){
		MainZukanContKeySousa( &p_data->end, &end_draw_set, 1, MONSNO_END );

		if( p_data->start > p_data->end ){
			p_data->start = p_data->end;
			start_draw_set = TRUE;
		}
	}

	if( start_draw_set == TRUE ){
		GF_BGL_BmpWinFill( p_data->p_bmp, 15, D_TOMO_ZKN_NUM_DRAW_X, D_TOMO_ZKN_START_DRAW_Y, D_TOMO_ZKN_NUM_DRAW_W, D_TOMO_ZKN_NUM_DRAW_H );
		NUMFONT_WriteNumber( p_num, p_data->start, 3, NUMFONT_MODE_ZERO, p_data->p_bmp, D_TOMO_ZKN_NUM_DRAW_X, D_TOMO_ZKN_START_DRAW_Y );
		GF_BGL_BmpWinOn( p_data->p_bmp );
	}

	if( end_draw_set == TRUE ){
		GF_BGL_BmpWinFill( p_data->p_bmp, 15, D_TOMO_ZKN_NUM_DRAW_X, D_TOMO_ZKN_END_DRAW_Y, D_TOMO_ZKN_NUM_DRAW_W, D_TOMO_ZKN_NUM_DRAW_H );
		NUMFONT_WriteNumber( p_num, p_data->end, 3, NUMFONT_MODE_ZERO, p_data->p_bmp, D_TOMO_ZKN_NUM_DRAW_X, D_TOMO_ZKN_END_DRAW_Y );
		GF_BGL_BmpWinOn( p_data->p_bmp );
	}
	
	// 図鑑に反映
	if( sys.trg & PAD_BUTTON_START ){
		p_data->set_chuu = TRUE;

		// START
		str = MSGMAN_AllocString( p_data->msg_data, MSG_D_ZKN_02 );
		GF_STR_PrintColor( p_data->p_bmp, FONT_SYSTEM, str, D_TOMO_ZKN_SET_START_X, D_TOMO_ZKN_SET_START_Y, MSG_NO_PUT, D_TOMOYA_ZUKAN_DRAWCOLOR, NULL );
		STRBUF_Delete( str );
		GF_BGL_BmpWinOn( p_data->p_bmp );

		Debug_ZukanWork_Make( p_data->p_zknwork, p_data->start, p_data->end, FALSE );
	}

	// 全クリア
	if( sys.trg & PAD_BUTTON_SELECT ){
		ZukanWork_Init( p_data->p_zknwork );
		ZukanWork_SetZukanGetFlag( p_data->p_zknwork );
		ZukanWork_SetZenkokuZukanFlag( p_data->p_zknwork );
		MyStatus_SetDpZenkokuFlag(SaveData_GetMyStatus( p_data->p_fsys->savedata) );
	}

	if( sys.trg & PAD_BUTTON_B ){
		// BG
		GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG2, VISIBLE_OFF );

		// メッセージマネージャ破棄
		MSGMAN_Delete( p_data->msg_data );

		// ビットマップ破棄
		GF_BGL_BmpWinDel( p_data->p_bmp );
		GF_BGL_BmpWinFree( p_data->p_bmp, 1 );
		FieldSystemProc_SeqHoldEnd();
		TCB_Delete( tcb );
		sys_FreeMemoryEz( p_data );
	}

	// ナンバーフォント破棄
	NUMFONT_Delete( p_num );
}


//----------------------------------------------------------------------------
/**
 *	@brief	ゼンコクフラグ設定
 */
//-----------------------------------------------------------------------------
static void MainZukanZenkokuFlagSet( TCB_PTR tcb, void* p_work )
{
	ZUKAN_WORK * p_zknwork;
	p_zknwork = SaveData_GetZukanWork( D_TomoyaFldSys->savedata );

	ZukanWork_SetZukanGetFlag( p_zknwork );
	ZukanWork_SetZenkokuZukanFlag( p_zknwork );
	MyStatus_SetDpZenkokuFlag(SaveData_GetMyStatus(D_TomoyaFldSys->savedata) );
	EndDebugWind(tcb, p_work);
}

//----------------------------------------------------------------------------
/**
 *	@brief	ゼンコク図鑑を埋める
 */
//-----------------------------------------------------------------------------
static void MainZukanZenkokuSet( TCB_PTR tcb, void* p_work )
{
	ZUKAN_WORK * p_zknwork;
	p_zknwork = SaveData_GetZukanWork( D_TomoyaFldSys->savedata );
	
	ZukanWork_SetZukanGetFlag(p_zknwork );
	ZukanWork_SetZenkokuZukanFlag( p_zknwork );
	MyStatus_SetDpZenkokuFlag(SaveData_GetMyStatus(D_TomoyaFldSys->savedata) );
	Debug_ZukanWork_Make( p_zknwork, 1, MONSNO_END, FALSE );
	EndDebugWind(tcb, p_work);
}

//----------------------------------------------------------------------------
/**
 *	@brief	シンオウ図鑑を埋める
 */
//-----------------------------------------------------------------------------
static void MainZukanShinouSet( TCB_PTR tcb, void* p_work )
{
	ZUKAN_WORK * p_zknwork;
	int i;
	
	p_zknwork = SaveData_GetZukanWork( D_TomoyaFldSys->savedata );
	
	ZukanWork_SetZukanGetFlag(p_zknwork );

	for( i=1; i<=MONSNO_END; i++ ){
		if( PokeZenkokuNo2ShinouNo( i ) > 0 ){
			Debug_ZukanWork_Make( p_zknwork, i, i, FALSE );
		}
	}
	EndDebugWind(tcb, p_work);
}

//----------------------------------------------------------------------------
/**
 *	@brief	ゼンコクポケモン全部見
 */
//-----------------------------------------------------------------------------
static void MainZukanZenkokuSeeSet( TCB_PTR tcb, void* p_work )
{
	ZUKAN_WORK * p_zknwork;
	p_zknwork = SaveData_GetZukanWork( D_TomoyaFldSys->savedata );
	
	ZukanWork_SetZukanGetFlag(p_zknwork );
	ZukanWork_SetZenkokuZukanFlag( p_zknwork );
	MyStatus_SetDpZenkokuFlag(SaveData_GetMyStatus(D_TomoyaFldSys->savedata) );
	Debug_ZukanWork_Make( p_zknwork, 1, MONSNO_END, TRUE );
	EndDebugWind(tcb, p_work);
}

//----------------------------------------------------------------------------
/**
 *	@brief	シンオウポケモン全部見
 */
//-----------------------------------------------------------------------------
static void MainZukanShinouSeeSet( TCB_PTR tcb, void* p_work )
{
	ZUKAN_WORK * p_zknwork;
	int i;
	
	p_zknwork = SaveData_GetZukanWork( D_TomoyaFldSys->savedata );
	
	for( i=1; i<=MONSNO_END; i++ ){
		if( PokeZenkokuNo2ShinouNo( i ) > 0 ){
			Debug_ZukanWork_Make( p_zknwork, i, i, TRUE );
		}
	}
	EndDebugWind(tcb, p_work);
}

//-----------------------------------------------------------------------------
//
//		お天気システム
//	
//=============================================================================
// 雨
static void StartWeather00( TCB_PTR tcb,void* work )
{

	WEATHER_ChengeReq( D_TomoyaFldSys->fldmap->weather_data, WEATHER_SYS_SUNNY );

	//ウィンドウ解放
	FreeDebugWindow(tcb,work);
	//タスク消去
	TCB_Delete(tcb);

	// メインリストセット
	mainlistStart();
}

// くもり
static void StartWeather01( TCB_PTR tcb,void* work )
{

	WEATHER_ChengeReq( D_TomoyaFldSys->fldmap->weather_data, WEATHER_SYS_CLOUDINESS );

	//ウィンドウ解放
	FreeDebugWindow(tcb,work);
	//タスク消去
	TCB_Delete(tcb);
	
	// メインリストセット
	mainlistStart();
}

// 雨
static void StartWeather02( TCB_PTR tcb,void* work )
{

	WEATHER_ChengeReq( D_TomoyaFldSys->fldmap->weather_data, WEATHER_SYS_RAIN );

	//ウィンドウ解放
	FreeDebugWindow(tcb,work);
	//タスク消去
	TCB_Delete(tcb);
	// メインリストセット
	mainlistStart();
}

// 大雨
static void StartWeather03( TCB_PTR tcb,void* work )
{
	WEATHER_ChengeReq( D_TomoyaFldSys->fldmap->weather_data, WEATHER_SYS_STRAIN );

	//ウィンドウ解放
	FreeDebugWindow(tcb,work);
	//タスク消去
	TCB_Delete(tcb);
	
	// メインリストセット
	mainlistStart();
}

// 大雨＋雷
static void StartWeather04( TCB_PTR tcb,void* work )
{
	WEATHER_ChengeReq( D_TomoyaFldSys->fldmap->weather_data, WEATHER_SYS_SPARK );
	//ウィンドウ解放
	FreeDebugWindow(tcb,work);
	//タスク消去
	TCB_Delete(tcb);
	
	// メインリストセット
	mainlistStart();
}

// 雪
static void StartWeather05( TCB_PTR tcb,void* work )
{
	WEATHER_ChengeReq( D_TomoyaFldSys->fldmap->weather_data, WEATHER_SYS_SNOW );
	//ウィンドウ解放
	FreeDebugWindow(tcb,work);
	//タスク消去
	TCB_Delete(tcb);
	
	// メインリストセット
	mainlistStart();
}

// 吹雪
static void StartWeather06( TCB_PTR tcb,void* work )
{
	WEATHER_ChengeReq( D_TomoyaFldSys->fldmap->weather_data, WEATHER_SYS_SNOWSTORM );
	
	//ウィンドウ解放
	FreeDebugWindow(tcb,work);
	//タスク消去
	TCB_Delete(tcb);
	
	// メインリストセット
	mainlistStart();
}

// 猛吹雪
static void StartWeather07( TCB_PTR tcb,void* work )
{

	WEATHER_ChengeReq( D_TomoyaFldSys->fldmap->weather_data, WEATHER_SYS_SNOWSTORM_H );

	//ウィンドウ解放
	FreeDebugWindow(tcb,work);
	//タスク消去
	TCB_Delete(tcb);
	
	// メインリストセット
	mainlistStart();
}

// きり
static void StartWeather08( TCB_PTR tcb,void* work )
{

	WEATHER_ChengeReq( D_TomoyaFldSys->fldmap->weather_data, WEATHER_SYS_FOG );

	//ウィンドウ解放
	FreeDebugWindow(tcb,work);
	//タスク消去
	TCB_Delete(tcb);
	
	// メインリストセット
	mainlistStart();
}

// 火山灰
static void StartWeather09( TCB_PTR tcb,void* work )
{
	WEATHER_ChengeReq( D_TomoyaFldSys->fldmap->weather_data, WEATHER_SYS_VOLCANO );

	//ウィンドウ解放
	FreeDebugWindow(tcb,work);
	//タスク消去
	TCB_Delete(tcb);
	
	// メインリストセット
	mainlistStart();
}

// 砂嵐
static void StartWeather10( TCB_PTR tcb,void* work )
{

 	WEATHER_ChengeReq( D_TomoyaFldSys->fldmap->weather_data, WEATHER_SYS_SANDSTORM );

	//ウィンドウ解放
	FreeDebugWindow(tcb,work);
	//タスク消去
	TCB_Delete(tcb);
	
	// メインリストセット
	mainlistStart();
}

// スノーダスト
static void StartWeather11( TCB_PTR tcb,void* work )
{

	WEATHER_ChengeReq( D_TomoyaFldSys->fldmap->weather_data, WEATHER_SYS_DIAMONDDUST );

	//ウィンドウ解放
	FreeDebugWindow(tcb,work);
	//タスク消去
	TCB_Delete(tcb);
	
	// メインリストセット
	mainlistStart();
}

// きりはらい
static void StartWeather12( TCB_PTR tcb,void* work )
{

	WEATHER_ChengeReq( D_TomoyaFldSys->fldmap->weather_data, WEATHER_SYS_MIST2 );

	//ウィンドウ解放
	FreeDebugWindow(tcb,work);
	//タスク消去
	TCB_Delete(tcb);
	
	// メインリストセット
	mainlistStart();
}

// フラッシュ
static void StartWeather13( TCB_PTR tcb,void* work )
{
	WEATHER_ChengeReq( D_TomoyaFldSys->fldmap->weather_data, WEATHER_SYS_FLASH );

	//ウィンドウ解放
	FreeDebugWindow(tcb,work);
	//タスク消去
	TCB_Delete(tcb);
	
	// メインリストセット
	mainlistStart();
}

// 気合
static void StartWeather14( TCB_PTR tcb,void* work )
{

	WEATHER_ChengeReq( D_TomoyaFldSys->fldmap->weather_data, WEATHER_SYS_SPIRIT );

	//ウィンドウ解放
	FreeDebugWindow(tcb,work);
	//タスク消去
	TCB_Delete(tcb);
	
	// メインリストセット
	mainlistStart();
}

// 神秘
static void StartWeather15( TCB_PTR tcb,void* work )
{

	WEATHER_ChengeReq( D_TomoyaFldSys->fldmap->weather_data, WEATHER_SYS_MYSTIC );

	//ウィンドウ解放
	FreeDebugWindow(tcb,work);
	//タスク消去
	TCB_Delete(tcb);
	
	// メインリストセット
	mainlistStart();
}

static void StartWeather16( TCB_PTR tcb,void* work )
{
	WEATHER_ChengeReq( D_TomoyaFldSys->fldmap->weather_data, WEATHER_SYS_RAINBOW );

	//ウィンドウ解放
	FreeDebugWindow(tcb,work);
	//タスク消去
	TCB_Delete(tcb);
	
	// メインリストセット
	mainlistStart();
}

// きりはらい　白
static void StartWeather17( TCB_PTR tcb,void* work )
{
	WEATHER_ChengeReq( D_TomoyaFldSys->fldmap->weather_data, WEATHER_SYS_MIST1 );

	//ウィンドウ解放
	FreeDebugWindow(tcb,work);
	//タスク消去
	TCB_Delete(tcb);
	
	// メインリストセット
	mainlistStart();
}


// 全停止
static void StopWeather( TCB_PTR tcb,void* work )
{
	WEATHER_ChengeReq( D_TomoyaFldSys->fldmap->weather_data, WEATHER_SYS_SUNNY );

	//ウィンドウ解放
	FreeDebugWindow(tcb,work);
	//タスク消去
	TCB_Delete(tcb);
	
	// メインリストセット
	mainlistStart();
}

// 破棄
static void EndWeather( TCB_PTR tcb,void* work )
{
	WEATHER_ChengeReq( D_TomoyaFldSys->fldmap->weather_data, WEATHER_SYS_SUNNY );
	
	//ウィンドウ解放
	FreeDebugWindow(tcb,work);
	//タスク消去
	TCB_Delete(tcb);
	
	// メインリストセット
	mainlistStart();	
}

//----------------------------------------------------------------------------
/**
 *	@brief	クライマックスデモ	開始
 *
 *	@param	tcb		TCBワーク
 *	@param	work	ワーク 
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void StartClimaxDemo( TCB_PTR tcb,void* work )
{
	TCB_PTR tcb_ptr;
	DTOMOYA_DEMO_CLIMAX* data;
	
	data = sys_AllocMemory( HEAPID_FIELD, sizeof(DTOMOYA_DEMO_CLIMAX) );
	tcb_ptr = TCB_Add(MainClimaxDemo, data, 6);
	memset( data, 0, sizeof(DTOMOYA_DEMO_CLIMAX) );

	// 銀河デモ
	data->p_demo = FLDMAP_DEMO_Ginga_Start( D_TomoyaFldSys );

	EndDebugWind(tcb, work);
}

//----------------------------------------------------------------------------
/**
 *	@brief	クライマックスデモ　メイン
 *	
 *	@param	tcb		TCBワーク
 *	@param	work	ワーク
 *
 *	@return
 *
 */
//-----------------------------------------------------------------------------
static void MainClimaxDemo( TCB_PTR tcb,void* work )
{
	DTOMOYA_DEMO_CLIMAX* p_data = work;

	switch( p_data->seq ){
	case 0:	// 初期化
		if( FLDMAP_DEMO_Ginga_GetState( p_data->p_demo ) == FLDMAP_DEMO_GINGA_SEQ_ENDREQ_WAIT ){
			p_data->seq ++;
		}
		break;

	case 1:	// メイン
		// Xで破棄
		if( sys.trg & PAD_BUTTON_X ){
			 FLDMAP_DEMO_Ginga_EndReq( p_data->p_demo );
			p_data->seq ++;
		}
		break;

	case 2:	// 終了待ち
		if( FLDMAP_DEMO_Ginga_GetState( p_data->p_demo ) == FLDMAP_DEMO_GINGA_SEQ_END ){
			p_data->seq ++;
		}
		break;

	case 3:	// 終了
		FLDMAP_DEMO_Ginga_End( p_data->p_demo );
		p_data->seq ++;
		break;

	case 4:	// 完全終了
		sys_FreeMemoryEz( work );
		TCB_Delete( tcb );
		break;
	}
}


//----------------------------------------------------------------------------
/**
 *	@brief	伝説ポケモン　登場デモ
 *
 *	@param	tcb		TCBワーク
 *	@param	work	ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void StartClimaxDemoLegend( TCB_PTR tcb,void* work )
{
	TCB_PTR tcb_ptr;
	DTOMOYA_DEMO_CLIMAX* data;
	
	data = sys_AllocMemory( HEAPID_FIELD, sizeof(DTOMOYA_DEMO_CLIMAX) );
	tcb_ptr = TCB_Add(MainClimaxDemoLegend, data, 6);
	memset( data, 0, sizeof(DTOMOYA_DEMO_CLIMAX) );

	EndDebugWind(tcb, work);
}

//----------------------------------------------------------------------------
/**
 *	@brief	伝説ポケモン登場
 *
 *	@param	tcb
 *	@param	work 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void MainClimaxDemoLegend( TCB_PTR tcb,void* work )
{
	DTOMOYA_DEMO_CLIMAX* data = work;
	FIELD_OBJ_PTR fldobj;

	switch( data->seq ){
	case 0:
		// 登場デモ
		data->p_demo = FLDMAP_DEMO_LegendPokeApp_Start( D_TomoyaFldSys );
		data->seq ++;
		break;
		
	case 1:
		//ゲスト登録
		fldobj = FieldOBJ_AddHMake(
		D_TomoyaFldSys->fldobjsys,		//fsys->fldobjsys
		D_TomoyaFldSys->location->grid_x,
		D_TomoyaFldSys->location->grid_z,//グリッド単位で指定
		DIR_UP,							//src\field\fieldobj_code.h DIR_UP-DIR_RIGHT 
		SPPOKE4,							//src\field\fieldobj_code.h HERO等
		MV_DMY,							// src\field\fieldobj_code.h MV_MDY等
		D_TomoyaFldSys->location->zone_id );// fsys->location->zone_id 追加する際のゾーンID
		FieldOBJ_OBJIDSet( fldobj, D05R0114_SPPOKE_01 ); //便利かも
	
//		FieldOBJ_StatusBitSet_Vanish( fldobj, TRUE );

		// オブジェ非表示に
		data->seq++;
		break;

	case 2:	// メイン
		if( FLDMAP_DEMO_LegendPokeApp_EndCheck( data->p_demo ) ){
			data->seq ++;
		}
		break;

	case 3:	// 終了
		FLDMAP_DEMO_LegendPokeApp_End( data->p_demo );
		sys_FreeMemoryEz( work );
		TCB_Delete( tcb );
		return;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	デモ黒リング　開始
 *
 *	@param	tcb		TCBタスク
 *	@param	work	ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void StartClimaxDemoBlackRing( TCB_PTR tcb,void* work )
{
	TCB_PTR tcb_ptr;
	DTOMOYA_DEMO_CLIMAX* data;
	FIELD_OBJ_PTR fldobj;
	
	data = sys_AllocMemory( HEAPID_FIELD, sizeof(DTOMOYA_DEMO_CLIMAX) );
	tcb_ptr = TCB_Add(MainClimaxDemoBlackRing, data, 6);
	memset( data, 0, sizeof(DTOMOYA_DEMO_CLIMAX) );

	//ゲスト登録
	fldobj = FieldOBJ_AddHMake(
	D_TomoyaFldSys->fldobjsys,		//fsys->fldobjsys
	D_TomoyaFldSys->location->grid_x,
	D_TomoyaFldSys->location->grid_z,//グリッド単位で指定
	DIR_UP,							//src\field\fieldobj_code.h DIR_UP-DIR_RIGHT 
	SPPOKE4,							//src\field\fieldobj_code.h HERO等
	MV_DMY,							// src\field\fieldobj_code.h MV_MDY等
	D_TomoyaFldSys->location->zone_id );// fsys->location->zone_id 追加する際のゾーンID
	FieldOBJ_OBJIDSet( fldobj, D05R0114_SPPOKE_01 ); //便利かも

	// 黒いわっかデモ
	data->p_demo = FLDMAP_DEMO_BlackRing_Start( D_TomoyaFldSys );	

	
	EndDebugWind(tcb, work);
}

//----------------------------------------------------------------------------
/**
 *	@brief	黒リング　動作メイン
 *
 *	@param	tcb		TCBワーク
 *	@param	work	ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void MainClimaxDemoBlackRing( TCB_PTR tcb,void* work )
{
	DTOMOYA_DEMO_CLIMAX* data = work;

	// Bで破棄
	if( sys.trg & PAD_BUTTON_START ){
		FLDMAP_DEMO_BlackRing_End( data->p_demo );
		TCB_Delete( tcb );
		sys_FreeMemoryEz( work );
	}
}

static void StartClimaxDemoAntEgg00( TCB_PTR tcb,void* work )
{
	TCB_PTR tcb_ptr;
	DTOMOYA_DEMO_CLIMAX* data;

	data = sys_AllocMemory( HEAPID_FIELD, sizeof(DTOMOYA_DEMO_CLIMAX) );
	tcb_ptr = TCB_Add(MainClimaxDemoAntEgg, data, 6);
	memset( data, 0, sizeof(DTOMOYA_DEMO_CLIMAX) );

	data->matrix_tmp = GFC_GetLookTarget( D_TomoyaFldSys->camera_ptr );
	data->p_demo = FLDMAP_DEMO_AntEgg_Start( D_TomoyaFldSys, FLDMAP_DEMO_ANTEGG_CUT00 );
	
	EndDebugWind(tcb, work);
}
static void StartClimaxDemoAntEgg01( TCB_PTR tcb,void* work )
{
	TCB_PTR tcb_ptr;
	DTOMOYA_DEMO_CLIMAX* data;

	data = sys_AllocMemory( HEAPID_FIELD, sizeof(DTOMOYA_DEMO_CLIMAX) );
	tcb_ptr = TCB_Add(MainClimaxDemoAntEgg, data, 6);
	memset( data, 0, sizeof(DTOMOYA_DEMO_CLIMAX) );

	data->matrix_tmp = GFC_GetLookTarget( D_TomoyaFldSys->camera_ptr );
	data->p_demo = FLDMAP_DEMO_AntEgg_Start( D_TomoyaFldSys, FLDMAP_DEMO_ANTEGG_CUT01 );
	
	EndDebugWind(tcb, work);
}

static void StartClimaxDemoAntEgg02( TCB_PTR tcb,void* work )
{
	TCB_PTR tcb_ptr;
	DTOMOYA_DEMO_CLIMAX* data;

	data = sys_AllocMemory( HEAPID_FIELD, sizeof(DTOMOYA_DEMO_CLIMAX) );
	tcb_ptr = TCB_Add(MainClimaxDemoAntEgg, data, 6);
	memset( data, 0, sizeof(DTOMOYA_DEMO_CLIMAX) );

	data->matrix_tmp = GFC_GetLookTarget( D_TomoyaFldSys->camera_ptr );
	data->p_demo = FLDMAP_DEMO_AntEgg_Start( D_TomoyaFldSys, FLDMAP_DEMO_ANTEGG_CUT02 );
	
	EndDebugWind(tcb, work);
}

//----------------------------------------------------------------------------
/**
 *	@brief	ありの卵でもメイン
 *
 *	@param	tcb		TCBワーク
 *	@param	work	ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void MainClimaxDemoAntEgg( TCB_PTR tcb,void* work )
{
	DTOMOYA_DEMO_CLIMAX* data = work;
	CAMERA_ANGLE angle;

	// Bで破棄
	if( sys.trg & PAD_BUTTON_SELECT ){
		// カメラパラメータ設定
		GFC_SetCameraPerspWay( 0x5C1, D_TomoyaFldSys->camera_ptr );	
		GFC_SetCameraDistance( 0x29AEC1, D_TomoyaFldSys->camera_ptr );
		GFC_SetLookTarget( &data->matrix_tmp, D_TomoyaFldSys->camera_ptr );
		angle.x = 0xD602;
		angle.y = 0;
		angle.z = 0;
		GFC_SetCameraAngleRev( &angle, D_TomoyaFldSys->camera_ptr );

		FLDMAP_DEMO_AntEgg_End( data->p_demo );
		TCB_Delete( tcb );
		sys_FreeMemoryEz( work );
	}
}


//----------------------------------------------------------------------------
/**
 *	@brief	甘い香り
 *
 *	@param	tcb
 *	@param	work 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void StartAmaikaoriDemo( TCB_PTR tcb,void* work )
{
	TCB_PTR tcb_ptr;
	DTOMOYA_DEMO_AMAIKAORI* data;

	data = sys_AllocMemory( HEAPID_FIELD, sizeof(DTOMOYA_DEMO_AMAIKAORI) );
	tcb_ptr = TCB_Add(MainAmaikaoriDemo, data, 6);
	memset( data, 0, sizeof(DTOMOYA_DEMO_AMAIKAORI) );

	data->p_work = FLDMAP_Amaikaori_Start( D_TomoyaFldSys );

#ifdef FIELD_AMAIKAORI_DEBUG
	data->debug = TCB_Add( AmaikaoriDebugMain, NULL, 0 );
#endif
	
	EndDebugWind(tcb, work);
}

//----------------------------------------------------------------------------
/**
 *	@brief	甘い香り
 *
 *	@param	tcb
 *	@param	work 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void MainAmaikaoriDemo( TCB_PTR tcb,void* work )
{
	DTOMOYA_DEMO_AMAIKAORI* data = work;

	switch( data->seq ){
	case 0:
		if( FLDMAP_Amaikaori_EndCheck( data->p_work ) ){
			FLDMAP_Amaikaori_End( data->p_work );

			data->p_work = FLDMAP_AmaikaoriEndEff_Start( D_TomoyaFldSys );
			data->seq++;
		}
		break;

	case 1:
		if( FLDMAP_Amaikaori_EndCheck( data->p_work ) ){
			FLDMAP_Amaikaori_End( data->p_work );
			data->seq++;

		}
		break;

	case 2:
		if( sys.trg & PAD_BUTTON_START ){
			data->seq ++;
		}else if( sys.trg & PAD_BUTTON_B ){
			data->seq = 0;
			data->p_work = FLDMAP_Amaikaori_Start( D_TomoyaFldSys );
		}
		break;

	case 3:
#ifdef FIELD_AMAIKAORI_DEBUG
		TCB_Delete( data->debug );
#endif
		sys_FreeMemoryEz( work );
		TCB_Delete( tcb );
		break;
	}
	
}


//----------------------------------------------------------------------------
/**
 *	@brief	エンカウントエフェクト開始
 */
//-----------------------------------------------------------------------------
static void StartEncountEffectSys( u32 effect_no )
{
	D_TOMOYA_ENCOUNT_SYS_WORK* p_data;

	p_data = sys_AllocMemory( HEAPID_FIELD, sizeof(D_TOMOYA_ENCOUNT_SYS_WORK) );
	memset( p_data, 0, sizeof(D_TOMOYA_ENCOUNT_SYS_WORK) );
	
	p_data->no = effect_no;

	TCB_Add( MainEncountEffectSys, p_data, 0 );
}


//----------------------------------------------------------------------------
/**
 *	@brief	エンカウントエフェクト開始
 *
 *	@param	tcb		TCBワーク
 *	@param	p_work	ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void MainEncountEffectSys( TCB_PTR tcb, void* p_work )
{
	D_TOMOYA_ENCOUNT_SYS_WORK* p_data = p_work;

	switch( p_data->seq ){
	case 0:
		p_data->work[0] = GFC_GetCameraDistance( D_TomoyaFldSys->camera_ptr );

		EncountEffectStart( p_data->no, D_TomoyaFldSys, &p_data->sub_end );
		p_data->seq ++;
		break;

	case 1:
		if( p_data->sub_end ){
			p_data->seq ++;
			//カメラ戻す
			GFC_SetCameraDistance( p_data->work[0], D_TomoyaFldSys->camera_ptr );
			G2_SetBG0Offset(0, 0);
			G2_SetBG1Offset(0, 0);
			G2_SetBG2Offset(0, 0);
			G2_SetBG3Offset(0, 0);

			// BGLを再作成
			Fieldmap_BgExit( D_TomoyaFldSys->bgl );
			Fieldmap_BgSet( D_TomoyaFldSys->bgl );
			FieldMsgPrintInit( PALTYPE_MAIN_BG, MSG_PRINT_INIT_ON );

			GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG0, VISIBLE_ON );
		}
		break;

	case 2:
		// フィールドHブランクOFF
		FLDHBLANK_SYS_Stop( D_TomoyaFldSys->fldmap->hblanksys );

		WIPE_SYS_Start( WIPE_PATTERN_WMS,
				WIPE_TYPE_DOORIN,
				WIPE_TYPE_DOORIN,
				WIPE_FADE_OUTCOLOR,
				WIPE_DEF_DIV,
				WIPE_DEF_SYNC,
				HEAPID_FIELD );
		p_data->seq ++;
		break;

	case 3:
		if( WIPE_SYS_EndCheck() ){
			sys_FreeMemoryEz( p_data );
			TCB_Delete( tcb );
			// フィールドHブランクON
			FLDHBLANK_SYS_Start( D_TomoyaFldSys->fldmap->hblanksys );

		}
		break;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	草　レベル低
 */
//-----------------------------------------------------------------------------
static void EncountEffect_00( TCB_PTR tcb, void* p_work )
{
	StartEncountEffectSys( ENCOUNT_FIELD_GRASS_LEVEL_LOW );
	//ウィンドウ解放
	FreeDebugWindow(tcb,p_work);
	//タスク消去
	TCB_Delete(tcb);
	// メインリストセット
	mainlistStart();
}
//----------------------------------------------------------------------------
/**
 *	@brief	草　レベル高
 */
//-----------------------------------------------------------------------------
static void EncountEffect_01( TCB_PTR tcb, void* p_work )
{
	StartEncountEffectSys( ENCOUNT_FIELD_GRASS_LEVEL_HIGH );
	//ウィンドウ解放
	FreeDebugWindow(tcb,p_work);
	//タスク消去
	TCB_Delete(tcb);
	// メインリストセット
	mainlistStart();
}
//----------------------------------------------------------------------------
/**
 *	@brief	水　レベル低
 */
//-----------------------------------------------------------------------------
static void EncountEffect_02( TCB_PTR tcb, void* p_work )
{
	StartEncountEffectSys( ENCOUNT_FIELD_WATER_LEVEL_LOW );
	//ウィンドウ解放
	FreeDebugWindow(tcb,p_work);
	//タスク消去
	TCB_Delete(tcb);
	// メインリストセット
	mainlistStart();
}
//----------------------------------------------------------------------------
/**
 *	@brief	水　レベル高
 */
//-----------------------------------------------------------------------------
static void EncountEffect_03( TCB_PTR tcb, void* p_work )
{
	StartEncountEffectSys( ENCOUNT_FIELD_WATER_LEVEL_HIGH );
	//ウィンドウ解放
	FreeDebugWindow(tcb,p_work);
	//タスク消去
	TCB_Delete(tcb);
	// メインリストセット
	mainlistStart();
}
//----------------------------------------------------------------------------
/**
 *	@brief	ダンジョン　レベル低
 */
//-----------------------------------------------------------------------------
static void EncountEffect_04( TCB_PTR tcb, void* p_work )
{
	StartEncountEffectSys( ENCOUNT_FIELD_DAN_LEVEL_LOW );

	//ウィンドウ解放
	FreeDebugWindow(tcb,p_work);
	//タスク消去
	TCB_Delete(tcb);
	// メインリストセット
	mainlistStart();
}
//----------------------------------------------------------------------------
/**
 *	@brief	ダンジョン　レベル高
 */
//-----------------------------------------------------------------------------
static void EncountEffect_05( TCB_PTR tcb, void* p_work )
{
	StartEncountEffectSys( ENCOUNT_FIELD_DAN_LEVEL_HIGH );
	//ウィンドウ解放
	FreeDebugWindow(tcb,p_work);
	//タスク消去
	TCB_Delete(tcb);
	// メインリストセット
	mainlistStart();
}

//----------------------------------------------------------------------------
/**
 *	@brief	TRAINER　草　レベル低
 */
//-----------------------------------------------------------------------------
static void EncountEffect_06( TCB_PTR tcb, void* p_work )
{
	StartEncountEffectSys( ENCOUNT_TRAINER_GRASS_LEVEL_LOW );
	//ウィンドウ解放
	FreeDebugWindow(tcb,p_work);
	//タスク消去
	TCB_Delete(tcb);
	// メインリストセット
	mainlistStart();
}

//----------------------------------------------------------------------------
/**
 *	@brief	TRAINER　草　レベル高
 */
//-----------------------------------------------------------------------------
static void EncountEffect_07( TCB_PTR tcb, void* p_work )
{
	StartEncountEffectSys( ENCOUNT_TRAINER_GRASS_LEVEL_HIGH );
	//ウィンドウ解放
	FreeDebugWindow(tcb,p_work);
	//タスク消去
	TCB_Delete(tcb);
	// メインリストセット
	mainlistStart();
}

//----------------------------------------------------------------------------
/**
 *	@brief	TRAINER　水　レベル低
 */
//-----------------------------------------------------------------------------
static void EncountEffect_08( TCB_PTR tcb, void* p_work )
{
	StartEncountEffectSys( ENCOUNT_TRAINER_WATER_LEVEL_LOW );
	//ウィンドウ解放
	FreeDebugWindow(tcb,p_work);
	//タスク消去
	TCB_Delete(tcb);
	// メインリストセット
	mainlistStart();
}

//----------------------------------------------------------------------------
/**
 *	@brief	TRAINER　水　レベル高い
 */
//-----------------------------------------------------------------------------
static void EncountEffect_09( TCB_PTR tcb, void* p_work )
{
	StartEncountEffectSys( ENCOUNT_TRAINER_WATER_LEVEL_HIGH );
	//ウィンドウ解放
	FreeDebugWindow(tcb,p_work);
	//タスク消去
	TCB_Delete(tcb);
	// メインリストセット
	mainlistStart();
}

//----------------------------------------------------------------------------
/**
 *	@brief	TRAINER　ダン　レベル低
 */
//-----------------------------------------------------------------------------
static void EncountEffect_10( TCB_PTR tcb, void* p_work )
{
	StartEncountEffectSys( ENCOUNT_TRAINER_DAN_LEVEL_LOW );
	//ウィンドウ解放
	FreeDebugWindow(tcb,p_work);
	//タスク消去
	TCB_Delete(tcb);
	// メインリストセット
	mainlistStart();
}

//----------------------------------------------------------------------------
/**
 *	@brief	TRAINER　ダン　レベル高い
 */
//-----------------------------------------------------------------------------
static void EncountEffect_11( TCB_PTR tcb, void* p_work )
{
	StartEncountEffectSys( ENCOUNT_TRAINER_DAN_LEVEL_HIGH );
	//ウィンドウ解放
	FreeDebugWindow(tcb,p_work);
	//タスク消去
	TCB_Delete(tcb);
	// メインリストセット
	mainlistStart();
}


//----------------------------------------------------------------------------
/**
 *	@brief	特殊　バトルタワー　ファクトリー
 */
//-----------------------------------------------------------------------------
static void EncountEffect_12( TCB_PTR tcb, void* p_work )
{
	StartEncountEffectSys( ENCOUNT_SPECIAL_TOWER );
	//ウィンドウ解放
	FreeDebugWindow(tcb,p_work);
	//タスク消去
	TCB_Delete(tcb);
	// メインリストセット
	mainlistStart();
}

//----------------------------------------------------------------------------
/**
 *	@brief	特殊	ダブルバトル
 */
//-----------------------------------------------------------------------------
static void EncountEffect_13( TCB_PTR tcb, void* p_work )
{
	StartEncountEffectSys( ENCOUNT_SPECIAL_DOUBLE );
	//ウィンドウ解放
	FreeDebugWindow(tcb,p_work);
	//タスク消去
	TCB_Delete(tcb);
	// メインリストセット
	mainlistStart();
}

//----------------------------------------------------------------------------
/**
 *	@brief	銀河団　通常
 */
//-----------------------------------------------------------------------------
static void EncountEffect_14( TCB_PTR tcb, void* p_work )
{
	StartEncountEffectSys( ENCOUNT_GINGA_NORMAL );
	//ウィンドウ解放
	FreeDebugWindow(tcb,p_work);
	//タスク消去
	TCB_Delete(tcb);
	// メインリストセット
	mainlistStart();
}

//----------------------------------------------------------------------------
/**
 *	@brief	銀河団　幹部
 */
//-----------------------------------------------------------------------------
static void EncountEffect_15( TCB_PTR tcb, void* p_work )
{
	StartEncountEffectSys( ENCOUNT_GINGA_SPECIAL );
	//ウィンドウ解放
	FreeDebugWindow(tcb,p_work);
	//タスク消去
	TCB_Delete(tcb);
	// メインリストセット
	mainlistStart();
}

//----------------------------------------------------------------------------
/**
 *	@brief	伝説ポケモン
 */
//-----------------------------------------------------------------------------
static void EncountEffect_16( TCB_PTR tcb, void* p_work )
{
	StartEncountEffectSys( ENCOUNT_LEGEND_NORMAL );
	//ウィンドウ解放
	FreeDebugWindow(tcb,p_work);
	//タスク消去
	TCB_Delete(tcb);
	// メインリストセット
	mainlistStart();
}

//----------------------------------------------------------------------------
/**
 *	@brief	PACKAGEポケモン
 */
//-----------------------------------------------------------------------------
static void EncountEffect_17( TCB_PTR tcb, void* p_work )
{
	StartEncountEffectSys( ENCOUNT_LEGEND_PACKAGE );
	//ウィンドウ解放
	FreeDebugWindow(tcb,p_work);
	//タスク消去
	TCB_Delete(tcb);
	// メインリストセット
	mainlistStart();
}

//----------------------------------------------------------------------------
/**
 *	@brief	ジム　クロガネ
 */
//-----------------------------------------------------------------------------
static void EncountEffect_18( TCB_PTR tcb, void* p_work )
{
	StartEncountEffectSys( ENCOUNT_SPTR_KUROGANE_GYM );
	//ウィンドウ解放
	FreeDebugWindow(tcb,p_work);
	//タスク消去
	TCB_Delete(tcb);
	// メインリストセット
	mainlistStart();
}

//----------------------------------------------------------------------------
/**
 *	@brief	ジム　ハクタイ
 */
//-----------------------------------------------------------------------------
static void EncountEffect_19( TCB_PTR tcb, void* p_work )
{
	StartEncountEffectSys( ENCOUNT_SPTR_HAKUTAI_GYM );
	//ウィンドウ解放
	FreeDebugWindow(tcb,p_work);
	//タスク消去
	TCB_Delete(tcb);
	// メインリストセット
	mainlistStart();
}

//----------------------------------------------------------------------------
/**
 *	@brief	ジム　ノモセ
 */
//-----------------------------------------------------------------------------
static void EncountEffect_20( TCB_PTR tcb, void* p_work )
{
	StartEncountEffectSys( ENCOUNT_SPTR_NOMOSE_GYM );
	//ウィンドウ解放
	FreeDebugWindow(tcb,p_work);
	//タスク消去
	TCB_Delete(tcb);
	// メインリストセット
	mainlistStart();
}

//----------------------------------------------------------------------------
/**
 *	@brief	ジム　トバリ
 */
//-----------------------------------------------------------------------------
static void EncountEffect_21( TCB_PTR tcb, void* p_work )
{
	StartEncountEffectSys( ENCOUNT_SPTR_TOBARI_GYM );
	//ウィンドウ解放
	FreeDebugWindow(tcb,p_work);
	//タスク消去
	TCB_Delete(tcb);
	// メインリストセット
	mainlistStart();
}

//----------------------------------------------------------------------------
/**
 *	@brief	ジム　ヨスガ
 */
//-----------------------------------------------------------------------------
static void EncountEffect_22( TCB_PTR tcb, void* p_work )
{
	StartEncountEffectSys( ENCOUNT_SPTR_YOSUGA_GYM );
	//ウィンドウ解放
	FreeDebugWindow(tcb,p_work);
	//タスク消去
	TCB_Delete(tcb);
	// メインリストセット
	mainlistStart();
}

//----------------------------------------------------------------------------
/**
 *	@brief	ジム　キッサキ
 */
//-----------------------------------------------------------------------------
static void EncountEffect_23( TCB_PTR tcb, void* p_work )
{
	StartEncountEffectSys( ENCOUNT_SPTR_KISSAKI_GYM );
	//ウィンドウ解放
	FreeDebugWindow(tcb,p_work);
	//タスク消去
	TCB_Delete(tcb);
	// メインリストセット
	mainlistStart();
}

//----------------------------------------------------------------------------
/**
 *	@brief	ジム　ミオ
 */
//-----------------------------------------------------------------------------
static void EncountEffect_24( TCB_PTR tcb, void* p_work )
{
	StartEncountEffectSys( ENCOUNT_SPTR_MIO_GYM );
	//ウィンドウ解放
	FreeDebugWindow(tcb,p_work);
	//タスク消去
	TCB_Delete(tcb);
	// メインリストセット
	mainlistStart();
}

//----------------------------------------------------------------------------
/**
 *	@brief	ジム　ナギサ
 */
//-----------------------------------------------------------------------------
static void EncountEffect_25( TCB_PTR tcb, void* p_work )
{
	StartEncountEffectSys( ENCOUNT_SPTR_NAGISA_GYM );
	//ウィンドウ解放
	FreeDebugWindow(tcb,p_work);
	//タスク消去
	TCB_Delete(tcb);
	// メインリストセット
	mainlistStart();
}

//----------------------------------------------------------------------------
/**
 *	@brief	四天王００
 */
//-----------------------------------------------------------------------------
static void EncountEffect_26( TCB_PTR tcb, void* p_work )
{
	StartEncountEffectSys( ENCOUNT_SPTR_SITEN_00 );
	//ウィンドウ解放
	FreeDebugWindow(tcb,p_work);
	//タスク消去
	TCB_Delete(tcb);
	// メインリストセット
	mainlistStart();
}

//----------------------------------------------------------------------------
/**
 *	@brief	四天王０１
 */
//-----------------------------------------------------------------------------
static void EncountEffect_27( TCB_PTR tcb, void* p_work )
{
	StartEncountEffectSys( ENCOUNT_SPTR_SITEN_01 );
	//ウィンドウ解放
	FreeDebugWindow(tcb,p_work);
	//タスク消去
	TCB_Delete(tcb);
	// メインリストセット
	mainlistStart();
}

//----------------------------------------------------------------------------
/**
 *	@brief	四天王02
 */
//-----------------------------------------------------------------------------
static void EncountEffect_28( TCB_PTR tcb, void* p_work )
{
	StartEncountEffectSys( ENCOUNT_SPTR_SITEN_02 );
	//ウィンドウ解放
	FreeDebugWindow(tcb,p_work);
	//タスク消去
	TCB_Delete(tcb);
	// メインリストセット
	mainlistStart();
}

//----------------------------------------------------------------------------
/**
 *	@brief	四天王03
 */
//-----------------------------------------------------------------------------
static void EncountEffect_29( TCB_PTR tcb, void* p_work )
{
	StartEncountEffectSys( ENCOUNT_SPTR_SITEN_03 );
	//ウィンドウ解放
	FreeDebugWindow(tcb,p_work);
	//タスク消去
	TCB_Delete(tcb);
	// メインリストセット
	mainlistStart();
}

//----------------------------------------------------------------------------
/**
 *	@brief	チャンピオン
 */
//-----------------------------------------------------------------------------
static void EncountEffect_30( TCB_PTR tcb, void* p_work )
{
	StartEncountEffectSys( ENCOUNT_SPTR_CHANPION );
	//ウィンドウ解放
	FreeDebugWindow(tcb,p_work);
	//タスク消去
	TCB_Delete(tcb);
	// メインリストセット
	mainlistStart();
}







//-----------------------------------------------------------------------------
/**
 *
 *		ゲーム内交換
 *
 */
//-----------------------------------------------------------------------------
static GMEVENT_CONTROL * EventCmd_D_FldTrade(u32 trade_no)
{
	D_TOMOYA_EVENT_WORK* p_work = sys_AllocMemory( HEAPID_BASE_APP, sizeof(D_TOMOYA_EVENT_WORK) );
	p_work->p_work= FLD_TradeAlloc( HEAPID_BASE_APP, trade_no );
	p_work->seq = 0;
	return FieldEvent_Set(D_TomoyaFldSys, EventScr_D_FldTrade, p_work);
}


static void StartFldTrade00( TCB_PTR tcb, void* p_work )
{
	EventCmd_D_FldTrade( FLD_TRADE_KEESHI );
	EndDebugWind(tcb, p_work);
}

static void StartFldTrade01( TCB_PTR tcb, void* p_work )
{
	EventCmd_D_FldTrade( FLD_TRADE_PERAPPU );
	EndDebugWind(tcb, p_work);
}

static void StartFldTrade02( TCB_PTR tcb, void* p_work )
{
	EventCmd_D_FldTrade( FLD_TRADE_GHOST );
	EndDebugWind(tcb, p_work);
}

static void StartFldTrade03( TCB_PTR tcb, void* p_work )
{
	EventCmd_D_FldTrade( FLD_TRADE_KOIKING );
	EndDebugWind(tcb, p_work);
}


//----------------------------------------------------------------------------
/**
 *	@brief	レコードコーナークリップデバック
 *
 */
//-----------------------------------------------------------------------------
#define RECORD_TRADE_NUM	( 1 )
static void Record_Clip( TCB_PTR tcb, void* p_work )
{
	IMC_SAVEDATA* iw = SaveData_GetImcSaveData( D_TomoyaFldSys->savedata );
	const void* p_television[6] = { NULL, };
	int i;
	POKEMON_PARAM* pp;
	IMC_TELEVISION_SAVEDATA* p_tv[2];
	int monsno;
	RTCTime time;
	
	// レコード交換実験
	pp = PokemonParam_AllocWork( HEAPID_BASE_APP );
	GF_RTC_GetTime( &time );
	monsno = time.second + 1;
	for( i=0; i<RECORD_TRADE_NUM; i++ ){
		p_tv[i] = ImcSaveData_TelevisionAllocWork( HEAPID_BASE_APP );
		p_television[i]	 = p_tv[i];

		PokeParaSet( pp, monsno+1, 5, POW_RND, RND_NO_SET, 0, ID_NO_SET, 0 );
		Debug_ImcSaveData_MakeTelevisionDummyData( p_tv[i], pp, 2 );
	}
	sys_FreeMemoryEz( pp );
	// 3には、自分のデータを入れる
	p_television[3] = ImcSaveData_GetTelevisionSaveData( iw, 0 );


	// 交換
	// 交換後の予想
	// 自分 ふしぎだね　ふしぎそう　ふしぎだね　ふしぎそう
	ImcSaveData_RecordMix( 6, 3, iw, p_television );

	// ワーク破棄
	for( i=0; i<RECORD_TRADE_NUM; i++ ){
		sys_FreeMemoryEz( p_tv[i] );
	}
}



//----------------------------------------------------------------------------
/**
 *	@brief	アクセサリー交換　開始
 */
//-----------------------------------------------------------------------------
static void StartAcceShop( TCB_PTR tcb, void* p_work )
{
	D_TOMO_ACCE_CHANGE* p_data = sys_AllocMemory( HEAPID_FIELD, sizeof(D_TOMO_ACCE_CHANGE) );

	memset( p_data, 0, sizeof(D_TOMO_ACCE_CHANGE) );
	
	TCB_Add( MainAcceShop, p_data, 0 );


	EndDebugWind(tcb, p_work);

	//イベントフック
	FieldSystemProc_SeqHold();
	
}

//----------------------------------------------------------------------------
/**
 *	@brief	アクセサリー交換　終了
 */
//-----------------------------------------------------------------------------
static void MainAcceShop( TCB_PTR tcb, void* p_work )
{
	D_TOMO_ACCE_CHANGE* p_data = p_work;
	BOOL result;

	switch( p_data->seq ){
	case 0:
		p_data->p_acce_chg = FIELD_AcceShop_Alloc( HEAPID_FIELD, D_TomoyaFldSys->savedata, D_TomoyaFldSys->bgl );
		p_data->seq ++;
		break;

	case 1:
		result = FIELD_AcceShop_Main( p_data->p_acce_chg );
		if( result == TRUE ){

			FieldSystemProc_SeqHoldEnd();
			FIELD_AcceShop_Free( p_data->p_acce_chg );
			sys_FreeMemoryEz( p_data );
			TCB_Delete( tcb );
		}
		break;
	}
	
}


//----------------------------------------------------------------------------
/**
 *	@brief	ミノムッチの設定
 *
 *	@param	tcb		タスクワーク
 *	@param	work	ワーク
 */
//-----------------------------------------------------------------------------
static void Debug_MinoMuchiSet( TCB_PTR tcb, void* work )
{
	POKEPARTY * party = SaveData_GetTemotiPokemon( D_TomoyaFldSys->savedata );
	POKEMON_PARAM* p_pp = PokemonParam_AllocWork( HEAPID_FIELD );
	int i;
	int poke_num = PokeParty_GetPokeCount( party );
	
	// 後ろの3つをミノムッチにする
	for( i=poke_num-1; i>2; i-- ){
		PokeParty_Delete( party, i );
	}

	PokeParaSet( p_pp, MONSNO_MINOMUTTI, 15, POW_RND, RND_NO_SET, 0, ID_NO_SET, 0 );

	for( i=0; i<3; i++ ){
		PokeParaPut( p_pp, ID_PARA_form_no, &i );
		PokeParty_Add( party, p_pp );
	}
	sys_FreeMemoryEz( p_pp );

	EndDebugWind(tcb, work);
}



//----------------------------------------------------------------------------
/**
 *	@brief	秘伝技エフェクト	開始
 */
//-----------------------------------------------------------------------------
static void StartHideEff( TCB_PTR tcb,void* work )
{
	TCB_PTR tcb_ptr;
	DTOMOYA_HIDENEFF* data;
	
	data = sys_AllocMemory( HEAPID_FIELD, sizeof(DTOMOYA_HIDENEFF) );
	tcb_ptr = TCB_Add(MainHideEff, data, 6);
	memset( data, 0, sizeof(DTOMOYA_HIDENEFF) );

	EndDebugWind(tcb, work);
}

//----------------------------------------------------------------------------
/**
 *	@brief	秘伝技エフェクト　メイン
 */
//-----------------------------------------------------------------------------
static void MainHideEff( TCB_PTR tcb,void* work )
{
	DTOMOYA_HIDENEFF* data = work;

	switch( data->seq ){
	case 0:
		data->p_demo = FLD_HIDENEFF_Iaigiri_Start( D_TomoyaFldSys );
		data->seq ++;
		break;

	case 1:	// 終了待ち
		if( FLD_HIDENEFF_Iaigiri_EndCheck( data->p_demo ) == TRUE ){
			data->seq ++;
		}
		break;

	case 2:	// 終了
		FLD_HIDENEFF_Iaigiri_End( data->p_demo );
		sys_FreeMemoryEz( data );
		TCB_Delete( tcb );
		break;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	秘伝技エフェクト	開始
 */
//-----------------------------------------------------------------------------
static void StartHideEff01( TCB_PTR tcb,void* work )
{
	TCB_PTR tcb_ptr;
	DTOMOYA_HIDENEFF* data;
	
	data = sys_AllocMemory( HEAPID_FIELD, sizeof(DTOMOYA_HIDENEFF) );
	tcb_ptr = TCB_Add(MainHideEff01, data, 6);
	memset( data, 0, sizeof(DTOMOYA_HIDENEFF) );

	EndDebugWind(tcb, work);
}

//----------------------------------------------------------------------------
/**
 *	@brief	秘伝技エフェクト　メイン
 */
//-----------------------------------------------------------------------------
static void MainHideEff01( TCB_PTR tcb,void* work )
{
	DTOMOYA_HIDENEFF* data = work;

	switch( data->seq ){
	case 0:
		data->p_demo = FLD_HIDENEFF_Iwakudaki_Start( D_TomoyaFldSys );
		data->seq ++;
		break;

	case 1:	// 終了待ち
		if( FLD_HIDENEFF_Iwakudaki_EndCheck( data->p_demo ) == TRUE ){
			data->seq ++;
		}
		break;

	case 2:	// 終了
		FLD_HIDENEFF_Iwakudaki_End( data->p_demo );
		sys_FreeMemoryEz( data );
		TCB_Delete( tcb );
		break;
	}
}


static BOOL DEBUG_TakinoboriEvent( GMEVENT_CONTROL * event )
{
	DTOMOYA_HIDENEFF* p_work = FieldEvent_GetSpecialWork(event);

	switch( p_work->seq ){
	case 0:	
		EventCmd_TakiNoboriCall( event, 
			Player_DirGet(D_TomoyaFldSys->player), 0 );
		p_work->seq ++;
		break;

	case 1:
		sys_FreeMemoryEz( p_work );
		return TRUE;
	}
	return FALSE;
}


//----------------------------------------------------------------------------
/**
 *	@brief	秘伝技エフェクト	開始
 */
//-----------------------------------------------------------------------------
static void StartHideEff02( TCB_PTR tcb,void* work )
{
	TCB_PTR tcb_ptr;
	DTOMOYA_HIDENEFF* data;

	data = sys_AllocMemory( HEAPID_FIELD, sizeof(DTOMOYA_HIDENEFF) );
	memset( data, 0, sizeof(DTOMOYA_HIDENEFF) );
	
	FieldEvent_Set( D_TomoyaFldSys, DEBUG_TakinoboriEvent, data );

	EndDebugWind(tcb, work);
}


//----------------------------------------------------------------------------
/**
 *	@brief	TEAMWORK得点描画
 */
//-----------------------------------------------------------------------------
static void StartTeamWorkScore( TCB_PTR tcb,void* work )
{
	D_TOMOYA_MAZEMAZE_TEAM* p_data;
	NUMFONT* p_num = NUMFONT_Create( 1, 2, 15, HEAPID_FIELD );

	p_data = sys_AllocMemory( HEAPID_FIELD, sizeof(D_TOMOYA_MAZEMAZE_TEAM) );
	memset( p_data, 0, sizeof(D_TOMOYA_MAZEMAZE_TEAM) );

	p_data->p_fsys = D_TomoyaFldSys;
	p_data->p_bmp = GF_BGL_BmpWinAllocGet( HEAPID_FIELD, 1 );
	GF_BGL_BmpWinAdd( p_data->p_fsys->bgl, 
			p_data->p_bmp, GF_BGL_FRAME2_M, 2, 2, 28, 18, 7, MENU_WIN_CGX_SIZ + 1 );

	// クリーン
	GF_BGL_BmpWinDataFill( p_data->p_bmp, 15 );

	NUMFONT_WriteNumber( p_num, D_Tomoya_MazeMaze_TeamWork, 3, NUMFONT_MODE_ZERO, p_data->p_bmp, 0, 0 );
	GF_BGL_BmpWinOn( p_data->p_bmp );

	// ナンバーフォント破棄
	NUMFONT_Delete( p_num );

	// BG
	GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG2, VISIBLE_ON );
	G2_SetBG2Priority(0);

	// タスク登録
	TCB_Add( MainTeamWorkScore, p_data, 0 );

	EndDebugWind(tcb, work);
	//イベントフック
	FieldSystemProc_SeqHold();

}

//----------------------------------------------------------------------------
/**
 *	@brief	TEAMWORK得点描画
 */
//-----------------------------------------------------------------------------
static void MainTeamWorkScore( TCB_PTR tcb,void* work )
{
	D_TOMOYA_MAZEMAZE_TEAM* p_data = work;

	if( sys.trg & PAD_BUTTON_B ){
		// BG
		GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG2, VISIBLE_OFF );

		// ビットマップ破棄
		GF_BGL_BmpWinDel( p_data->p_bmp );
		GF_BGL_BmpWinFree( p_data->p_bmp, 1 );
		FieldSystemProc_SeqHoldEnd();
		TCB_Delete( tcb );
		sys_FreeMemoryEz( p_data );
	}
}


//----------------------------------------------------------------------------
/**
 *	@brief	デオキシスセーブデータバックアップ
 */	
//-----------------------------------------------------------------------------
static void D_TomoDeokisisuSaveBuckUp( TCB_PTR tcb,void* work )
{
	ZUKAN_WORK* zw = SaveData_GetZukanWork( D_TomoyaFldSys->savedata );
	// デオキシスセーブワークバックアップ
	Debug_ZukanWork_DeokisisuBuckUp( zw );
	EndDebugWind(tcb, work);
}

#endif // PM_DEBUG
