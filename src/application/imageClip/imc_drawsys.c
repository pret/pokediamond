//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		imc_drawsys.c
 *	@brief		イメージクリップ描画システムデータ管理システム
 *				このシステムを使用すれば、すべて描画出来るようにします。
 *	@author		tomoya takahashi
 *	@data		2005.09.21
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

#include <string.h>
#include "system.h"
#include "assert.h"
#include "display.h"
#include "include/system/heapdefine.h"
#include "include/system/arc_util.h"
#include "include/system/arc_tool.dat"
#include "include/system/render_oam.h"
#include "char_manager.h"
#include "pltt_manager.h"
#include "include/gflib/gf_gx.h"


#define	__IMC_DRAWSYS_H_GLOBAL
#include "include/application/imageClip/imc_drawsys.h"

//-----------------------------------------------------------------------------
/**
 *					定数宣言
*/
//-----------------------------------------------------------------------------
#define IMC_DRAW_MAIN_PLANE	(GX_PLANEMASK_BG0 | GX_PLANEMASK_BG1 | GX_PLANEMASK_BG2 | GX_PLANEMASK_BG3 | GX_PLANEMASK_OBJ)
#define IMC_DRAW_SUB_PLANE	(GX_PLANEMASK_BG0 | GX_PLANEMASK_BG1 | GX_PLANEMASK_OBJ)


#define IMC_POKE_OBJ_TEX_SIZE	(0x2800)
#define IMC_POKE_OBJ_PLTT_SIZE	(0x20)


//-------------------------------------
//	
//	セルアクター初期化用
//	
//=====================================
#define	IMC_CHAR_NUM	(8)
#define IMC_PLTT_NUM	(5)
#define IMC_CELL_NUM	(48)

//-----------------------------------------------------------------------------
/**
 *					構造体宣言
*/
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
/**
*		グローバル
*/
//-----------------------------------------------------------------------------
/*
//	パレットオフセット対応表
static u8 plttOfs[ IMC_ACCE_MAX ] = {
	0,0,1,1,0,0,0,0,0,0,		// 1~
	0,0,0,0,0,0,0,0,0,0,		// 11~
	0,0,0,0,0,0,0,0,0,0,		// 21~
	0,1,0,0,0,0,0,0,0,0,		// 31~
	0,0,0,0,0,0,0,0,0,0,		// 41~
	0,0,0,0,2,0,0,1,0,0,		// 51~
	0,0,0,0,0,0,0,0,0,0,		// 61~
	0,0,0,0,0,0,1,0,0,0,		// 71~
	0,0,0,0,0,0,0,0,0,0,		// 81~
	0,0,0,0,0,0,0,0,0,0,		// 91~
};
//*/

//-----------------------------------------------------------------------------
/**
 *					プロトタイプ宣言
*/
//-----------------------------------------------------------------------------
static void vram_bank_set( void );
static void setup_3d( void );
static void setup_2d_imgClip( void );

static void putback_3d( void );
static void putback_2d_imgClip( void );


static void initSWSP( IMC_DRAW_DATA* data, const SWSP_SYSDATA* cp_sys );
static void deleteSWSP( IMC_DRAW_DATA* data );
static void drawSWSP( IMC_DRAW_DATA* data );

static void initSoftSprite( IMC_DRAW_DATA* drawData, int heap, int tex_size, int pltt_size );
static void deleteSoftSprite( IMC_DRAW_DATA* drawData );

static void initAccePlttOfs( IMC_DRAW_DATA* data, int heap );
static void deleteAccePlttOfs( IMC_DRAW_DATA* data );

static void initCLACT( IMC_DRAW_DATA* data );
static void deleteCLACT( IMC_DRAW_DATA* data );
static void drawCLACT( IMC_DRAW_DATA* data );

static void initCharRes( IMC_DRAW_DATA* data );
static void deleteCharRes( IMC_DRAW_DATA* data );


static void loadSWSPChar( IMC_DRAW_DATA* data, SWSP_CHARDATA* char_data, int num );
static void loadSWSPPltt( IMC_DRAW_DATA* data, SWSP_PLTTDATA* pltt_data, int num );

static void setBg( IMC_DRAW_DATA* data );
static void delBg( IMC_DRAW_DATA* data );

static void getCharSize( NNSG2dCharacterData* char_data, int* x, int* y );

static void loadSWSPResDataAllocMemory( IMC_DRAW_LOADRES_DATA* loadData, int char_num, int pltt_num, int heap );
static void loadSWSPResDataDeleteMemory( IMC_DRAW_LOADRES_DATA* loadData );
static void loadAcceData( IMC_DRAW_DATA* drawData, IMC_DRAW_LOADRES_DATA* loadData );
static void loadBGThumData( IMC_DRAW_DATA* drawData, IMC_DRAW_LOADRES_DATA* loadData );


//----------------------------------------------------------------------------
//
/**
 *
 *	@brief	描画システムを描画出来るように環境を設定します
 *
 *	@param	none
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_DRAW_SetUp( void )
{
	// バンク設定
	vram_bank_set();
	
	// ３D設定
	setup_3d();
	
	// ２D設定
	setup_2d_imgClip();

	// 描画先を変更
	sys.disp3DSW = DISP_3D_TO_SUB;
	GF_Disp_DispSelect();
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	設定した環境データを破棄します
 *
 *	@param	none
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_DRAW_PutBack( void )
{
	// 描画先を変更
	sys.disp3DSW = DISP_3D_TO_MAIN;
	GF_Disp_DispSelect();
	
	// 2d設定を破棄
	putback_2d_imgClip();

	// 3d設定を破棄
	putback_3d();

	GX_ResetBankForTex();
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	描画用システムの設定を行います。
 *
 *	@param	drawData	描画データ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_DRAW_InitSys( IMC_DRAW_DATA* drawData )
{
	// スプライトデータ作成
	SWSP_SYSDATA swsp = {
		IMC_SPRITE_OBJ_NUM,
		IMC_SPRITE_CHAR_NUM,
		IMC_SPRITE_PLTT_NUM,
		HEAPID_IMAGECLIP_DRAW
	};//*/
	initSWSP( drawData, &swsp );

	// ポケモン描画スプライトデータ作成
	initSoftSprite( drawData, HEAPID_IMAGECLIP_DRAW, IMC_POKE_OBJ_TEX_SIZE, IMC_POKE_OBJ_PLTT_SIZE );


	// キャラクタリソースマネージャ作成	登録最大数　=　IMC_SPRITE_OBJ_CHAR_NUM
	initCharRes( drawData );

	// アクセサリ用パレットオフセットテーブル作成
	initAccePlttOfs( drawData, HEAPID_IMAGECLIP_DATA );

	// セルアクター作成
	initCLACT( drawData );

	// BGシステムデータ作成
	drawData->BG_Ini = GF_BGL_BglIniAlloc( HEAPID_IMAGECLIP_DRAW );
	setBg( drawData );

}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	描画システムデータを破棄する
 *
 *	@param	drawData	描画データ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_DRAW_DeleteSys( IMC_DRAW_DATA* drawData )
{
	// パレットオフセットテーブル破棄
	deleteAccePlttOfs( drawData );
	
	// スプライトデータ破棄
	deleteSWSP( drawData );

	// BGシステムデータ破棄
	delBg( drawData );
	sys_FreeMemoryEz( drawData->BG_Ini );
	
	// ポケモン描画システム破棄
	deleteSoftSprite( drawData );

	// セルアクター破棄
	deleteCLACT( drawData );

	// キャラクタデータ破棄
	deleteCharRes( drawData );

	// キャラクタデータ保存領域破棄
	sys_FreeMemoryEz( drawData->SWSP_charData );
	drawData->SWSP_charData = NULL;
	
	// パレットデータ保存領域破棄
	sys_FreeMemoryEz( drawData->SWSP_plttData );
	drawData->SWSP_plttData = NULL;
	
}


//----------------------------------------------------------------------------
/**
 *
 *	@brief	描画関数のある描画システムの描画
 *
 *	@param	drawData	描画データ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_DRAW_DrawSys( IMC_DRAW_DATA* drawData )
{
	//３Ｄ描画開始
	GF_G3X_Reset();

	NNS_G2dSetupSoftwareSpriteCamera();

	// スプライト描画
	if( drawData->SWSP_DrawFlag ){
		drawSWSP( drawData );	
	}
	
	// ポケモン描画
	if( drawData->SSM_DrawFlag ){
		SoftSpriteMain( drawData->SSM_drawSys );
	}
	
	/* ジオメトリ＆レンダリングエンジン関連メモリのスワップ */
	GF_G3_RequestSwapBuffers(GX_SORTMODE_AUTO, GX_BUFFERMODE_Z);

	// ２D描画
	// セルアクター描画
	drawCLACT( drawData );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	リソースの読み込みを行います	個々でVram上に展開します
 *
 *	@param	drawData	描画データ格納領域
 *	@param	loadData	読み込むリソースデータ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_DRAW_LoadResource( IMC_DRAW_DATA* drawData, IMC_DRAW_LOADRES_DATA* loadData )
{
	// キャラクタデータ読み込み
	loadSWSPChar( drawData, loadData->SWSP_charTbl, loadData->SWSP_charNum );
	
	// パレットデータ読み込み
	loadSWSPPltt( drawData, loadData->SWSP_plttTbl, loadData->SWSP_plttNum );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	リソースの破棄を行います
 *
 *	@param	drawData	描画データ格納領域
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_DRAW_DeleteResource( IMC_DRAW_DATA* drawData )
{
	// スプライトデータ完全破棄
	SWSP_CharDeleteAll( drawData->SWSP_drawSys );
	SWSP_PlttDeleteAll( drawData->SWSP_drawSys );
}


//----------------------------------------------------------------------------
/**
 *	@brief	アクター登録
 *
 *	@param	drawData	ワーク
 *	@param	contid		管理ID
 *	@param	x			ｘ座標
 *	@param	y			ｙ座標
 *	@param	pri			優先順位
 *	@param	draw_area	描画エリア
 *
 *	@return	アクターワーク
 */
//-----------------------------------------------------------------------------
CLACT_WORK_PTR IMC_DRAW_AddClact( IMC_DRAW_DATA* drawData, int contid, int x, int y, int pri, int draw_area )
{
	CLACT_HEADER head;
	CLACT_ADD_SIMPLE add;

	CLACT_U_MakeHeader( &head,
			contid, contid, contid, contid,
			CLACT_U_HEADER_DATA_NONE, CLACT_U_HEADER_DATA_NONE,
			0, 0,
			drawData->resMan[ CLACT_U_CHAR_RES ],
			drawData->resMan[ CLACT_U_PLTT_RES ],
			drawData->resMan[ CLACT_U_CELL_RES ],
			drawData->resMan[ CLACT_U_CELLANM_RES ],
			NULL, NULL );

	add.ClActSet = drawData->clactSet;
	add.ClActHeader = &head;
	add.mat.x	= x << FX32_SHIFT;
	add.mat.y	= y << FX32_SHIFT;
	add.mat.z	= 0;
	add.pri		= pri;
	add.DrawArea = draw_area;
	add.heap	= HEAPID_IMAGECLIP_DRAW;

	return CLACT_AddSimple( &add );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	キャラクタデータ読み込み
 *
 *	@param	drawData		描画システムデータ
 *	@param	fileIdx			ファイルインデックス
 *	@param	dataIdx			データインデックス
 *	@param	comp			圧縮フラグ
 *	@param	vramType		Vramタイプ
 *	@param	id				管理ID
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_DRAW_CLACT_LoadCharData( IMC_DRAW_DATA* drawData, int fileIdx, int dataIdx, BOOL comp, int vramType, int id )
{
	CLACT_U_RES_OBJ_PTR res;
	
	// データ読み込み
	res = CLACT_U_ResManagerResAddArcChar( 
			drawData->resMan[ CLACT_U_CHAR_RES ],
			fileIdx, dataIdx, comp, id, vramType,
			HEAPID_IMAGECLIP_DRAW);

	// データ転送
	CLACT_U_CharManagerSetAreaCont( res );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	パレットデータ読み込み
 *
 *	@param	drawData		描画システムデータ
 *	@param	fileIdx			ファイルインデックス
 *	@param	dataIdx			データインデックス
 *	@param	comp			圧縮フラグ
 *	@param	vramType		Vramタイプ
 *	@param	load_num		パレット読み込み数
 *	@param	id				管理ID
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_DRAW_CLACT_LoadPlttData( IMC_DRAW_DATA* drawData, int fileIdx, int dataIdx, BOOL comp, int vramType, int load_num, int id )
{
	CLACT_U_RES_OBJ_PTR	res;
	
	// データ読み込み
	res = CLACT_U_ResManagerResAddArcPltt( 
			drawData->resMan[ CLACT_U_PLTT_RES ],
			fileIdx, dataIdx, comp, id, vramType,
			load_num, HEAPID_IMAGECLIP_DRAW);

	// データ転送
	CLACT_U_PlttManagerSetCleanArea( res );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	セルデータ読み込み
 *
 *	@param	drawData		描画システムデータ
 *	@param	fileIdx			ファイルインデックス
 *	@param	dataIdx			データインデックス
 *	@param	comp			圧縮フラグ
 *	@param	id				管理ID
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_DRAW_CLACT_LoadCellData( IMC_DRAW_DATA* drawData, int fileIdx, int dataIdx, BOOL comp, int id )
{
	// データ読み込み
	CLACT_U_ResManagerResAddArcKindCell( 
			drawData->resMan[ CLACT_U_CELL_RES ],
			fileIdx, dataIdx, comp, id, CLACT_U_CELL_RES,
			HEAPID_IMAGECLIP_DRAW);
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	セルアニメデータ読み込み
 *
 *	@param	drawData		描画システムデータ
 *	@param	fileIdx			ファイルインデックス
 *	@param	dataIdx			データインデックス
 *	@param	comp			圧縮フラグ
 *	@param	id				管理ID
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_DRAW_CLACT_LoadCellAnmData( IMC_DRAW_DATA* drawData, int fileIdx, int dataIdx, BOOL comp, int id )
{
	// データ読み込み
	CLACT_U_ResManagerResAddArcKindCell( 
			drawData->resMan[ CLACT_U_CELLANM_RES ],
			fileIdx, dataIdx, comp, id, CLACT_U_CELLANM_RES,
			HEAPID_IMAGECLIP_DRAW);
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	キャラクタリソースデータのみの破棄
 *
 *	@param	drawData	描画システムデータ
 *	@param	id			管理ID
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_DRAW_CLACT_DeleteCharRes( IMC_DRAW_DATA* drawData, int id )
{
	CLACT_U_RES_OBJ_PTR	res;

	res = CLACT_U_ResManagerGetIDResObjPtr(
			drawData->resMan[ CLACT_U_CHAR_RES ], id);

	// リソース破棄
	CLACT_U_ResManagerResDelete( 
			drawData->resMan[ CLACT_U_CHAR_RES ], res );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	パレットリソースデータのみの破棄
 *
 *	@param	drawData	描画システムデータ
 *	@param	id			管理ID
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_DRAW_CLACT_DeletePlttRes( IMC_DRAW_DATA* drawData, int id )
{
	CLACT_U_RES_OBJ_PTR	res;

	res = CLACT_U_ResManagerGetIDResObjPtr(
			drawData->resMan[ CLACT_U_PLTT_RES ], id);

	CLACT_U_ResManagerResDelete( 
			drawData->resMan[ CLACT_U_PLTT_RES ], res );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	セルリソースデータのみの破棄
 *
 *	@param	drawData	描画システムデータ
 *	@param	id			管理ID
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_DRAW_CLACT_DeleteCellRes( IMC_DRAW_DATA* drawData, int id )
{
	CLACT_U_RES_OBJ_PTR	res;

	res = CLACT_U_ResManagerGetIDResObjPtr(
			drawData->resMan[ CLACT_U_CELL_RES ], id);

	// リソース破棄
	CLACT_U_ResManagerResDelete( 
			drawData->resMan[ CLACT_U_CELL_RES ], res );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	セルアニメデータのみの破棄
 *
 *	@param	drawData	描画システムデータ
 *	@param	id			管理ID
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_DRAW_CLACT_DeleteCellAnmRes( IMC_DRAW_DATA* drawData, int id )
{
	CLACT_U_RES_OBJ_PTR	res;

	res = CLACT_U_ResManagerGetIDResObjPtr(
			drawData->resMan[ CLACT_U_CELLANM_RES ], id);

	CLACT_U_ResManagerResDelete( 
			drawData->resMan[ CLACT_U_CELLANM_RES ], res );
}



//----------------------------------------------------------------------------
/**
 *
 *	@brief	スプライト用の読み込むファイルを作成	今だけ
 *
 *	@param	loadData	作成先
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_DRAW_MakeLoadSWSP_samp( IMC_DRAW_DATA* drawData, IMC_DRAW_LOADRES_DATA* loadData )
{
	// SWSPのリソース登録データメモリを確保
	loadSWSPResDataAllocMemory( loadData, IMC_SPRITE_CHAR_NUM, IMC_SPRITE_PLTT_NUM, HEAPID_IMAGECLIP_DRAW );
	
	// アクセサリ用リソース
	loadAcceData( drawData, loadData );

	// BGサムネイル用リソース
	loadBGThumData( drawData, loadData );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	スプライト用の読み込みファイルを破棄する
 *
 *	@param	loadData	読み込みデータ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_DRAW_DestLoadSWSP( IMC_DRAW_LOADRES_DATA* loadData )
{
	loadSWSPResDataDeleteMemory( loadData );
}


//----------------------------------------------------------------------------
/**
 *
 *	@brief	キャラクタデータの登録
 *
 *	@param	drawData	描画データ構造体
 *	@param	buff		キャラクタデータバッファ
 *	@param	char_no		登録キャラクタナンバー（アクセサリナンバーとLink）
 *
 *	@return	アンパック後のキャラクタデータ
 *
 *
 */
//-----------------------------------------------------------------------------
NNSG2dCharacterData* IMC_DRAW_SetCharData( IMC_DRAW_DATA* drawData, void* buff, int char_no )
{
	// リソースマネージャに登録
	RESM_AddResNormal( drawData->SWSP_charRes, buff, char_no );
	NNS_G2dGetUnpackedCharacterData( buff, &drawData->SWSP_UPchar[ char_no ] );
	return drawData->SWSP_UPchar[ char_no ];
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	通常時のウィンドウマスク設定
 *
 *	@param	none	
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_DRAW_WndMaskNormalSet( void )
{
/*	GX_SetVisibleWnd(GX_WNDMASK_W0 | GX_WNDMASK_W1);

	G2_SetWnd0InsidePlane( GX_WND_PLANEMASK_BG0 | GX_WND_PLANEMASK_BG2, FALSE );
	G2_SetWnd1InsidePlane( GX_WND_PLANEMASK_BG0 | GX_WND_PLANEMASK_BG3, FALSE );
	G2_SetWndOutsidePlane( GX_WND_PLANEMASK_BG1, FALSE );
	
	G2_SetWnd0Position( IMC_LBOX_AREA_X,
						IMC_LBOX_AREA_Y,
						IMC_LBOX_AREA_X + IMC_LBOX_AREA_WIDTH,
						IMC_LBOX_AREA_Y + IMC_LBOX_AREA_HEIGHT);
	
	G2_SetWnd1Position( IMC_RBOX_AREA_X,
						IMC_RBOX_AREA_Y,
						IMC_RBOX_AREA_X + IMC_RBOX_AREA_WIDTH,
						IMC_RBOX_AREA_Y + IMC_RBOX_AREA_HEIGHT);//*/
	GX_SetVisibleWnd(GX_WNDMASK_NONE);
	// BG優先順位の変更
	G2_SetBG0Priority( 1 );
	G2_SetBG1Priority( 0 );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	オブジェクトを動かしているときのウィンドウマスクを設定
 *
 *	@param	none	
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_DRAW_WndMaskObjMoveSet( void )
{
	GX_SetVisibleWnd(GX_WNDMASK_W0);

	G2_SetWnd0InsidePlane( GX_WND_PLANEMASK_BG0 | GX_WND_PLANEMASK_BG1 | GX_WND_PLANEMASK_BG2 | GX_WND_PLANEMASK_BG3 | GX_WND_PLANEMASK_OBJ, FALSE );
	G2_SetWndOutsidePlane( GX_WND_PLANEMASK_BG1 | GX_WND_PLANEMASK_OBJ, FALSE );

	// ポジション設定
	// フレームの幅を考慮した値を設定
	G2_SetWnd0Position( IMC_LBOX_AREA_X_MOVEOK,
						IMC_LBOX_AREA_Y_MOVEOK,
						IMC_RBOX_AREA_X_MOVEOK + IMC_RBOX_AREA_WIDTH_MOVEOK,
						IMC_RBOX_AREA_Y_MOVEOK + IMC_RBOX_AREA_HEIGHT_MOVEOK );
	// BG優先順位の変更
	G2_SetBG0Priority( 0 );
	G2_SetBG1Priority( 1 );//*/
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	終了チェック時の表示優先順位設定
 *
 *	@param	none	
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_DRAW_EndCheckBGPri( void )
{
	G2_SetBG1Priority( 3 );
}


//----------------------------------------------------------------------------
/**
 *
 *	@brief	描画システム用Vブランク関数
 *
 *	@param	drawData	描画システムデータ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_DRAW_VBlank( IMC_DRAW_DATA* drawData )
{
	// BGシステムのVblank関数
	GF_BGL_VBlankFunc( drawData->BG_Ini );

	// ソフトウェアスプライト
	SoftSpriteTextureTrans( drawData->SSM_drawSys );

	// レンダラー共有OAMマネージャのOAM転送
	REND_OAMTrans();
}

//----------------------------------------------------------------------------
/**
 *	@brief	アクセサリ用ソフトウェアスプライトデータメモリ確保
 *
 *	@param	drawData	読み込みデータワーク	
 *	@param	heap		ヒープ
 *		
 *	@return	none
 */
//-----------------------------------------------------------------------------
void IMC_DRAW_SWSPResDataAllocMemory( IMC_DRAW_LOADRES_DATA* loadData, int heap )
{
	// SWSPのリソース登録データメモリを確保
	loadSWSPResDataAllocMemory( loadData, IMC_SPRITE_CHAR_NUM, IMC_SPRITE_PLTT_NUM, heap );
}



//-----------------------------------------------------------------------------
/**
*		キャラクタデータを見て、ほんとにその位置に抜き色以外の色になって
*		いるかをチェックする
*/
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *
 *	@brief	キャラクタデータの指定位置に色がparamで無いかチェック
 *
 *	@param	char_data		チェックに使うキャラクタデータ
 *	@param	offs_x			xオフセット
 *	@param	offs_y			yオフセット
 *	@param	param			チェック色ナンバー
 *
 *	@retval	IMC_DRAW_CHAR_CHECK_TRUE	paramの色
 *	@retval	IMC_DRAW_CHAR_CHECK_FALSE	paramの色じゃない
 *	@retval	IMC_DRAW_CHAR_CHECK_ERR		エラー
 *
 * １６色限定
 *
 */
//-----------------------------------------------------------------------------
int IMC_DRAW_CharCheck( NNSG2dCharacterData* char_data, int offs_x, int offs_y, int param )
{
	u32* char_res;				// キャラクタ実データ
	int char_x, char_y;			// キャラクタデータサイズ
	int char_px;				// チェックするデータナンバー
	int char_px_offs;			// チェックするデータ内オフセット


		
	// キャラクタデータサイズを計算
	char_x = char_data->W;
	char_y = char_data->H;
	char_x *= 8;		// ピクセル単位にする
	char_y *= 8;		// ピクセル単位にする

	// サイズoverチェック
	if( (offs_x < 0) || (offs_y < 0) ||
		(offs_x >= char_x) || (offs_y >= char_y) ){

		return IMC_DRAW_CHAR_CHECK_ERR;
	}

//	OS_Printf( "char_x %d, char_y %d\n", char_data->W, char_data->H );

	// キャラクタデータ取得
	char_res = char_data->pRawData;

	// オフセット位置のキャラクタナンバー
	char_px = (offs_y * char_x) + offs_x;
	char_px_offs = (char_px % 8);	// u32に8ピクセル分入るため
	char_px /= 8;

//	OS_Printf( "char_px %d char_px_offs %d \n",char_px, char_px_offs );

//	OS_Printf( "%x \n", char_res[ char_px ] );
	
//	OS_Printf( " %d \n", (char_res[ char_px ] & (0xf << (char_px_offs * 4))) );

//	OS_Printf( " %d \n", ((param << (char_px_offs * 4))) );
	
	// そのキャラクタデータをチェック
	if( (char_res[ char_px ] & (0xf << (char_px_offs * 4))) == (param << (char_px_offs * 4)) ){
		return IMC_DRAW_CHAR_CHECK_TRUE;
	}
	return IMC_DRAW_CHAR_CHECK_FALSE;
}


//-----------------------------------------------------------------------------
/**
 * 
 *	イメージクリッププレイヤーシステム用関数郡
 * 
 */
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *
 *	@brief	描画システム	イメージクリッププレイヤー用初期化設定
 *
 *	@param	drawData	描画システムデータ格納先
 *	@param	cp_swsp		ソフトウェアシステム初期化データ
 *	@param	BG_Ini		BGシステム
 *	@param	heap		使用ヒープID
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_DRAW_InitSysPlayer( IMC_DRAW_DATA* drawData, const SWSP_SYSDATA* cp_swsp, int heap )
{

	// スプライトデータ作成
	initSWSP( drawData, cp_swsp );

	// ポケモン描画スプライトデータ作成
	initSoftSprite( drawData, heap, IMC_POKE_OBJ_TEX_SIZE, IMC_POKE_OBJ_PLTT_SIZE );

	// ポケモン描画ルーチン
	// 描画モード設定
	SoftSpriteDrawModeSet( drawData->SSM_drawSys, SS_DRAW_MODE_NO_IDENTITY );

	// アクセサリ用パレットオフセットテーブル作成
	initAccePlttOfs( drawData, heap );

}

//----------------------------------------------------------------------------
/**
 *	@brief	プレイヤーのBG部分の初期化
 *
 *	@param	BG_Ini		BGコントロール
 *	@param	heap		ヒープ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void IMC_DRAW_InitSysPlayerBG( IMC_DRAW_DATA* drawData, GF_BGL_INI* BG_Ini, int heap )
{
	// BGIniは外部から受け取る
	drawData->BG_Ini = BG_Ini;

	{	// メイン面フレーム2
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xf000, GX_BG_CHARBASE_0x04000, GX_BG_EXTPLTT_01,
			2, 0, 0, FALSE
		};
		GF_BGL_BGControlExit( drawData->BG_Ini, GF_BGL_FRAME2_M );
		GF_BGL_BGControlSet( drawData->BG_Ini, GF_BGL_FRAME2_M, &TextBgCntDat, GF_BGL_MODE_TEXT );
		GF_BGL_ClearCharSet( GF_BGL_FRAME2_M, 32, 0, heap );
		GF_BGL_ScrClear( drawData->BG_Ini, GF_BGL_FRAME2_M );
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	描画システムデータを破棄する
 *
 *	@param	drawData	描画データ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_DRAW_DeleteSysPlayer( IMC_DRAW_DATA* drawData )
{
	// パレットオフセットテーブル破棄
	deleteAccePlttOfs( drawData );
	
	// スプライトデータ破棄
	deleteSWSP( drawData );

	// ポケモン描画システム破棄
	deleteSoftSprite( drawData );

	// キャラクタデータ保存領域破棄
	sys_FreeMemoryEz( drawData->SWSP_charData );
	drawData->SWSP_charData = NULL;
	
	// パレットデータ保存領域破棄
	sys_FreeMemoryEz( drawData->SWSP_plttData );
	drawData->SWSP_plttData = NULL;

}

//----------------------------------------------------------------------------
/**
 *	@brief	プレイヤー　描画グローバル	BG部分の破棄
 *
 *	@param	drawData	
 *		
 *	@return	none
 */
//-----------------------------------------------------------------------------
void IMC_DRAW_DeleteSysPlayerBG( IMC_DRAW_DATA* drawData )
{
	//BG破棄
	GF_BGL_BGControlExit( drawData->BG_Ini, GF_BGL_FRAME2_M );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	描画システム用Vブランク関数
 *
 *	@param	drawData	描画システムデータ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_DRAW_VBlankPlayer( IMC_DRAW_DATA* drawData )
{
	// ソフトウェアスプライト
	SoftSpriteTextureTrans( drawData->SSM_drawSys );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	描画関数のある描画システムの描画
 *
 *	@param	drawData	描画データ
 *	@param	center_x	中心ｘ
 *	@param	center_y	中心ｙ
 *	@param	rota_num	回転角
 *	@param	scale		スケールベクトル
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_DRAW_DrawSysPlayer( IMC_DRAW_DATA* drawData, int center_x, int center_y, u16 rota_num, const VecFx32* p_scale )
{
	//３Ｄ描画開始
//	GF_G3X_Reset();
	G3_Identity();

	G3_PushMtx();
	{
		NNS_G2dSetupSoftwareSpriteCamera();

		// 全体にかけたい行列設定
		G3_Translate( center_x*FX32_ONE, center_y*FX32_ONE, 0 );
		{
			G3_RotZ( FX_SinIdx( rota_num ), FX_CosIdx( rota_num ) );
			G3_Scale( p_scale->x, p_scale->y, p_scale->z );
		}
		G3_Translate( -center_x*FX32_ONE, -center_y*FX32_ONE, 0 );//*/
		
		G3_PushMtx();
		{	
			if( drawData->SWSP_DrawFlag ){
				// スプライト描画
				drawSWSP( drawData );	
			}
			
			// ポケモン描画
			if( drawData->SSM_DrawFlag ){
				SoftSpriteMain( drawData->SSM_drawSys );
			}
		}
		G3_PopMtx(1);
		
		/* ジオメトリ＆レンダリングエンジン関連メモリのスワップ */
	//	GF_G3_RequestSwapBuffers(GX_SORTMODE_AUTO, GX_BUFFERMODE_Z);
	}
	G3_PopMtx(1);
}




//----------------------------------------------------------------------------
/**
 *	@brief	preview初期化
 *
 *	@param	drawData	ワーク
 *	@param	heap		ヒープ
 */
//-----------------------------------------------------------------------------
void IMC_DRAW_InitSysPrev( IMC_DRAW_DATA* drawData, int heap )
{
	// セルアクター作成
	initCLACT( drawData );

	// BGシステムデータ作成
	drawData->BG_Ini = GF_BGL_BglIniAlloc( HEAPID_IMAGECLIP_DRAW );
	setBg( drawData );

}

//----------------------------------------------------------------------------
/**
 *	@brief	preview用描画ワーク破棄
 *
 *	@param	drawData	ワーク
 */
//-----------------------------------------------------------------------------
void IMC_DRAW_DeleteSysPrev( IMC_DRAW_DATA* drawData )
{
	// BGシステムデータ破棄
	delBg( drawData );
	sys_FreeMemoryEz( drawData->BG_Ini );

	// セルアクター破棄
	deleteCLACT( drawData );
}

//----------------------------------------------------------------------------
/**
 *	@brief	previewVブランク処理
 *
 *	@param	drawData	ワーク
 */
//-----------------------------------------------------------------------------
void IMC_DRAW_VBlankPrev( IMC_DRAW_DATA* drawData )
{
	// BGシステムのVblank関数
	GF_BGL_VBlankFunc( drawData->BG_Ini );

	// レンダラー共有OAMマネージャのOAM転送
	REND_OAMTrans();
}

//----------------------------------------------------------------------------
/**
 *	@brief	描画処理
 *
 *	@param	drawData 
 */
//-----------------------------------------------------------------------------
void IMC_DRAW_DrawSysPrev( IMC_DRAW_DATA* drawData )
{
	// ２D描画
	// セルアクター描画
	drawCLACT( drawData );
}




//-----------------------------------------------------------------------------
/**
*	プライベート関数
*/
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *
 *	@brief	バンク設定
 *
 *	@param	none
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void vram_bank_set( void )
{
	GF_BGL_DISPVRAM vramSetTable = {
		GX_VRAM_BG_128_C,				// メイン2DエンジンのBG
		GX_VRAM_BGEXTPLTT_NONE,			// メイン2DエンジンのBG拡張パレット
		GX_VRAM_SUB_BG_32_H,			// サブ2DエンジンのBG
		GX_VRAM_SUB_BGEXTPLTT_NONE,		// サブ2DエンジンのBG拡張パレット
		GX_VRAM_OBJ_32_FG,				// メイン2DエンジンのOBJ
		GX_VRAM_OBJEXTPLTT_NONE,		// メイン2DエンジンのOBJ拡張パレット
		GX_VRAM_SUB_OBJ_16_I,			// サブ2DエンジンのOBJ
		GX_VRAM_SUB_OBJEXTPLTT_NONE,	// サブ2DエンジンのOBJ拡張パレット
		GX_VRAM_TEX_01_AB,				// テクスチャイメージスロット
		GX_VRAM_TEXPLTT_0123_E			// テクスチャパレットスロット
	};
	GF_Disp_SetBank( &vramSetTable );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	3D面設定
 *
 *	@param	none
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void setup_3d( void )
{
	// NitroSystem:３Ｄエンジンの初期化
	NNS_G3dInit();
	// マトリクススタックの初期化
    G3X_InitMtxStack();

	GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG0, VISIBLE_ON );
    G2_SetBG0Priority(1);

	// 各種描画モードの設定(シェード＆アンチエイリアス＆半透明)
    G3X_SetShading(GX_SHADING_TOON);
    G3X_AntiAlias(TRUE);
	G3X_AlphaTest(FALSE, 0);	// アルファテスト　　オフ
	G3X_AlphaBlend(TRUE);		// アルファブレンド　オン

	// クリアカラーの設定
    G3X_SetClearColor(GX_RGB(0, 0, 0),	// clear color
                      0,				// clear alpha
                      0x7fff,			// clear depth
                      63,				// clear polygon ID
                      FALSE				// fog
                      );

	// ジオメトリエンジン起動後必ず呼ばれなければならない
    G3_SwapBuffers(GX_SORTMODE_AUTO, GX_BUFFERMODE_W);

	// ビューポートの設定
    G3_ViewPort(0, 0, 255, 191);

	// マネージャがテクスチャイメージスロットを指定スロット分管理できるようにして
	// デフォルトマネージャにする。
	NNS_GfdInitFrmTexVramManager(2, TRUE);
		
	// マネージャがパレットを16KB分管理できるようにして
	// デフォルトマネージャにする。
	NNS_GfdInitFrmPlttVramManager(0x4000, TRUE);
	
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	イメージクリップ画面用2D面設定
 *
 *	@param	none
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void setup_2d_imgClip( void )
{
	// BG設定
	{
		GF_BGL_SYS_HEADER bg_head = {
			GX_DISPMODE_GRAPHICS,
			GX_BGMODE_0,
			GX_BGMODE_0,
			GX_BG0_AS_3D
		};
		GF_BGL_InitBG( &bg_head );
	}
	
	// OBJ設定
	// マッピングモード32K
	GX_SetOBJVRamModeChar( GX_OBJVRAMMODE_CHAR_1D_32K );
	// OAMマネージャ初期化
	NNS_G2dInitOamManagerModule();

	// 描画面設定
	GF_Disp_GX_VisibleControlInit();
	GF_Disp_GXS_VisibleControlInit();
	GF_Disp_GX_VisibleControl( IMC_DRAW_MAIN_PLANE, VISIBLE_ON );
	GF_Disp_GXS_VisibleControl( IMC_DRAW_SUB_PLANE, VISIBLE_ON );

}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	３D設定で使用したメモリを破棄
 *
 *	@param	none 
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void putback_3d( void )
{
	NNS_GfdResetFrmTexVramState();
	NNS_GfdResetFrmPlttVramState();
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	２ｄ設定で使用したメモリを破棄
 *
 *	@param	none
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void putback_2d_imgClip( void )
{
	GF_Disp_GX_VisibleControlInit();
	GF_Disp_GXS_VisibleControlInit();
	// OAMマネージャ初期化
	NNS_G2dInitOamManagerModule();
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	ソフトウェアスプライト初期化
 *
 *	@param	data	描画データ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void initSWSP( IMC_DRAW_DATA* data, const SWSP_SYSDATA* cp_sys )
{
/*	SWSP_SYSDATA sys = {
		IMC_SPRITE_OBJ_NUM,
		IMC_SPRITE_CHAR_NUM,
		IMC_SPRITE_PLTT_NUM,
		HEAPID_IMAGECLIP_DRAW
	};//*/

	data->SWSP_drawSys = SWSP_SysInit( cp_sys );

	// キャラクタデータ格納用領域を作成
	data->SWSP_charData = sys_AllocMemory( cp_sys->heap, sizeof(SWSP_CHAR_PTR) * IMC_SPRITE_CHAR_NUM );
	
	data->SWSP_charNum = IMC_SPRITE_CHAR_NUM;
	data->SWSP_charNow = 0;

	// パレットデータ格納領域を作成
	data->SWSP_plttData = sys_AllocMemory( cp_sys->heap, sizeof(SWSP_PLTT_PTR) * IMC_SPRITE_PLTT_NUM );
	data->SWSP_plttNum = IMC_SPRITE_PLTT_NUM;
	data->SWSP_plttNow = 0;

	data->SWSP_DrawFlag = TRUE;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	ソフトウェアスプライト破棄
 *
 *	@param	data	描画データ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void deleteSWSP( IMC_DRAW_DATA* data )
{
	SWSP_SysDelete( data->SWSP_drawSys );
	data->SWSP_drawSys = NULL;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	スプライトシステムの描画
 *
 *	@param	data	描画データ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void drawSWSP( IMC_DRAW_DATA* data )
{
	SWSP_SysDraw( data->SWSP_drawSys );
	
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	キャラクタデータ転送
 *
 *	@param	data		描画システムデータ
 *	@param	char_data	キャラクタデータ
 *	@param	num			転送キャラクタデータ数
 *
 *	@return	none
 *
 * char_dataの要素数＝キャラクタデータ管理IDとなります
 *
 */
//-----------------------------------------------------------------------------
static void loadSWSPChar( IMC_DRAW_DATA* data, SWSP_CHARDATA* char_data, int num )
{
	int i;		// ループ用

	for(i=0; i<num; i++){

		GF_ASSERT( data->SWSP_charNow < data->SWSP_charNum );

		// アクセサリ　サムネイルの対応した位置に入れる必要があるため、
		// 格納を飛ばすこともある
		if(char_data[i].res_file != NULL){
			data->SWSP_charData[ data->SWSP_charNow ] = SWSP_CharLoad( char_data + i );
		}else{
			data->SWSP_charData[ data->SWSP_charNow ] = NULL;
		}
		data->SWSP_charNow++;
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	パレットデータを転送する
 *
 *	@param	data			描画システムデータ
 *	@param	pltt_data		パレット転送データ
 *	@param	num				パレット数	
 *		
 *	@return	none
 *
 * pltt_dataの要素数＝パレット管理IDとなります
 *
 */
//-----------------------------------------------------------------------------
static void loadSWSPPltt( IMC_DRAW_DATA* data, SWSP_PLTTDATA* pltt_data, int num )
{
	int i;		// ループ用

	for(i=0; i<num; i++){

		GF_ASSERT( data->SWSP_plttNow < data->SWSP_plttNum );
		
		// アクセサリ　サムネイルの対応した位置に入れる必要があるため、
		// 格納を飛ばすこともある
		if(pltt_data[i].res_file != NULL){
			data->SWSP_plttData[ data->SWSP_plttNow ] = SWSP_PlttLoad( pltt_data + i );
		}else{
			data->SWSP_plttData[ data->SWSP_plttNow ] = NULL;
		}

		data->SWSP_plttNow++;
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	BG面設定を行う
 *
 *	@param	data	描画システムデータ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void setBg( IMC_DRAW_DATA* data )
{
	
	{	// メイン面フレーム1
		GF_BGL_BGCNT_HEADER  TextBgCntDat = {
			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xf800, GX_BG_CHARBASE_0x00000, GX_BG_EXTPLTT_01,
			0, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( data->BG_Ini, GF_BGL_FRAME1_M, &TextBgCntDat, GF_BGL_MODE_TEXT );
		GF_BGL_ClearCharSet( GF_BGL_FRAME1_M, 32, 0, HEAPID_IMAGECLIP_DRAW );
		GF_BGL_ScrClear( data->BG_Ini, GF_BGL_FRAME1_M );
	}
	
	{	// メイン面フレーム2
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xf000, GX_BG_CHARBASE_0x04000, GX_BG_EXTPLTT_01,
			2, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( data->BG_Ini, GF_BGL_FRAME2_M, &TextBgCntDat, GF_BGL_MODE_TEXT );
		GF_BGL_ClearCharSet( GF_BGL_FRAME2_M, 32, 0, HEAPID_IMAGECLIP_DRAW );
		GF_BGL_ScrClear( data->BG_Ini, GF_BGL_FRAME2_M );
	}

	{	// メイン面フレーム3
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, -(IMC_LBOX_AREA_Y + IMC_LBOX_AREA_HEIGHT), 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xe800, GX_BG_CHARBASE_0x08000, GX_BG_EXTPLTT_01,
			3, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( data->BG_Ini, GF_BGL_FRAME3_M, &TextBgCntDat, GF_BGL_MODE_TEXT );
		GF_BGL_ClearCharSet( GF_BGL_FRAME3_M, 32, 0, HEAPID_IMAGECLIP_DRAW );
		GF_BGL_ScrClear( data->BG_Ini, GF_BGL_FRAME3_M );
	}

	// サブ面設定
	{	// サブ面フレーム0
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0x7800, GX_BG_CHARBASE_0x00000, GX_BG_EXTPLTT_01,
			1, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( data->BG_Ini, GF_BGL_FRAME0_S, &TextBgCntDat, GF_BGL_MODE_TEXT );
		GF_BGL_ClearCharSet( GF_BGL_FRAME0_S, 32, 0, HEAPID_IMAGECLIP_DRAW );
		GF_BGL_ScrClear( data->BG_Ini, GF_BGL_FRAME0_S );
	}

	{	// メイン面フレーム3
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0x7000, GX_BG_CHARBASE_0x04000, GX_BG_EXTPLTT_01,
			0, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( data->BG_Ini, GF_BGL_FRAME1_S, &TextBgCntDat, GF_BGL_MODE_TEXT );
		GF_BGL_ClearCharSet( GF_BGL_FRAME1_S, 32, 0, HEAPID_IMAGECLIP_DRAW );
		GF_BGL_ScrClear( data->BG_Ini, GF_BGL_FRAME1_S );
	}
	// ウィンドウマスクBGの設定
//	IMC_DRAW_WndMaskNormalSet();
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	BG面設定を破棄する
 *
 *	@param	data	描画システムデータ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void delBg( IMC_DRAW_DATA* data )
{
	GF_BGL_BGControlExit( data->BG_Ini, GF_BGL_FRAME1_M );
	GF_BGL_BGControlExit( data->BG_Ini, GF_BGL_FRAME2_M );
	GF_BGL_BGControlExit( data->BG_Ini, GF_BGL_FRAME3_M );
	GF_BGL_BGControlExit( data->BG_Ini, GF_BGL_FRAME0_S );
	GF_BGL_BGControlExit( data->BG_Ini, GF_BGL_FRAME1_S );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	キャラクタリソースデータ作成
 *
 *	@param	data	描画データ構造体
 *
 *	@return	none
 *
 * タッチパネルあたり判定に使用します
 *
 */
//-----------------------------------------------------------------------------
static void initCharRes( IMC_DRAW_DATA* data )
{
	data->SWSP_charRes = RESM_Init( IMC_SPRITE_OBJ_CHAR_NUM, HEAPID_IMAGECLIP_DRAW );
	data->SWSP_UPchar = sys_AllocMemory( HEAPID_IMAGECLIP_DRAW,
			sizeof(NNSG2dCharacterData*) * IMC_SPRITE_OBJ_CHAR_NUM );

	memset( data->SWSP_UPchar, 0, sizeof(NNSG2dCharacterData*) * IMC_SPRITE_OBJ_CHAR_NUM );
	
	data->SWSP_UPcharNum = IMC_SPRITE_OBJ_CHAR_NUM;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	キャラクタリソースデータ破棄
 *
 *	@param	data 
 *
 *	@return
 *
 *
 */
//-----------------------------------------------------------------------------
static void deleteCharRes( IMC_DRAW_DATA* data )
{
	sys_FreeMemoryEz( data->SWSP_UPchar );
	RESM_Delete( data->SWSP_charRes );	
	data->SWSP_UPcharNum = 0;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	セルアクター初期化
 *
 *	@param	data	描画システムデータ 
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void initCLACT( IMC_DRAW_DATA* data )
{
	// キャラクタマネージャ初期化
	{
		CHAR_MANAGER_MAKE init = {
			IMC_CHAR_NUM, 0x8000, 0x4000, HEAPID_IMAGECLIP_DRAW
		};

		InitCharManagerReg(&init, 
				GX_OBJVRAMMODE_CHAR_1D_32K,
				GX_OBJVRAMMODE_CHAR_1D_32K);
	}

	// パレットマネージャ初期化
	InitPlttManager(IMC_PLTT_NUM, HEAPID_IMAGECLIP_DRAW);

	// キャラクタ読み込み開始オフセット設定
	CharLoadStartAll();

	// パレット読み込み開始オフセット設定
	PlttLoadStartAll();

	
	// OAMマネージャーの初期化
	NNS_G2dInitOamManagerModule();


	// レンダラ用OAMマネージャ作成
	REND_OAMInit( 
	0, 124,		// メイン画面OAM管理領域
	0, 31,		// メイン画面アフィン管理領域
	0, 124,		// サブ画面OAM管理領域
	0, 31,		// サブ画面アフィン管理領域
	HEAPID_IMAGECLIP_DRAW);
	
	// セルアクターセット作成
	data->clactSet = CLACT_U_SetEasyInit( IMC_CELL_NUM, 
			&data->renddata,
			HEAPID_IMAGECLIP_DRAW );
	CLACT_U_SetSubSurfaceMatrix( &data->renddata, MAIN_SURFACE_X, IMC_CLACT_SUB_SURFACE_Y );

	// リソースマネージャの作成
	// キャラクタ
	data->resMan[ CLACT_U_CHAR_RES ] = CLACT_U_ResManagerInit( 
			IMC_CHAR_NUM,
			CLACT_U_CHAR_RES,
			HEAPID_IMAGECLIP_DRAW );
	// パレット
	data->resMan[ CLACT_U_PLTT_RES ] = CLACT_U_ResManagerInit( 
			IMC_PLTT_NUM,
			CLACT_U_PLTT_RES,
			HEAPID_IMAGECLIP_DRAW );
	// セル
	data->resMan[ CLACT_U_CELL_RES ] = CLACT_U_ResManagerInit( 
			IMC_CELL_NUM,
			CLACT_U_CELL_RES,
			HEAPID_IMAGECLIP_DRAW );
	// セルアニメ
	data->resMan[ CLACT_U_CELLANM_RES ] = CLACT_U_ResManagerInit( 
			IMC_CELL_NUM,
			CLACT_U_CELLANM_RES,
			HEAPID_IMAGECLIP_DRAW );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	セルアクター破棄
 *
 *	@param	data	描画システムデータ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void deleteCLACT( IMC_DRAW_DATA* data )
{
	// アクターセット破棄
	CLACT_DestSet(data->clactSet);

	// リソースマネージャ破棄
	{
		int i;
		for(i=0; i<IMC_DRAW_USE_RES_NUM; i++){
			CLACT_U_ResManagerDelete(data->resMan[i]);
		}
	}
	// キャラクタマネージャ破棄
	DeleteCharManager();

	// パレットマネージャ破棄
	DeletePlttManager();
	
	// レンダラー共有OAMマネージャ破棄
	REND_OAM_Delete();	
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	セルアクター描画
 *
 *	@param	data 
 *
 *	@return
 *
 *
 */
//-----------------------------------------------------------------------------
static void drawCLACT( IMC_DRAW_DATA* data )
{
	// 描画
	CLACT_Draw(data->clactSet);
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	アクセサリリソースファイル読み込み
 *
 *	@param	drawData	描画システムデータ
 *	@param	loadData	読み込みデータ格納先
 *
 *	@return	none
 *
 * パレットは固定の要素数位置に登録するので一番最初に必ず
 * アクセサリのデータを読み込んでください
 * 
 *
 */
//-----------------------------------------------------------------------------
static void loadAcceData( IMC_DRAW_DATA* drawData, IMC_DRAW_LOADRES_DATA* loadData )
{
	int i;			// ループ用
	int cont_id;	// データ登録先ID
	void* buff;

	// アクセサリ用データ読み込み
	for(i=0; i<IMC_ACCE_MAX; i++ ){
		// キャラクタデータ取得
		buff = ArcUtil_Load(ARC_IMAGECLIP_GRA,
				IMC_ACCE_ARC_NO_GET( i ),
				FALSE, HEAPID_IMAGECLIP_DRAW, ALLOC_BOTTOM);

		GF_ASSERT( buff );

		// 管理ID取得
		cont_id = IMC_ACCE_CHAR_CONT_ID(i);

		// リソースマネージャに登録
		// アンパック後のデータを登録
		loadData->SWSP_charTbl[ cont_id ].res_file = IMC_DRAW_SetCharData( drawData, buff, i );
		
		// スプライト描画システムポインタ設定
		loadData->SWSP_charTbl[ cont_id ].s_sys = drawData->SWSP_drawSys;
	}

	// パレットデータ登録
	buff = ArcUtil_Load(ARC_IMAGECLIP_GRA,
			IMC_DRAW_ACCESSORIE_PLTT_ARC, FALSE, HEAPID_IMAGECLIP_DRAW, ALLOC_BOTTOM);
	
	// リソースマネージャに登録
	RESM_AddResNormal( loadData->SWSP_plttRes, buff, IMC_DRAW_ACCESSORIE_PLTT_ID );		
	
	// アンパック
	NNS_G2dGetUnpackedPaletteData( buff,
			&loadData->SWSP_plttTbl[ IMC_DRAW_ACCESSORIE_PLTT_ID ].res_file );

	// 描画システムデータ
	loadData->SWSP_plttTbl[ IMC_DRAW_ACCESSORIE_PLTT_ID ].s_sys = drawData->SWSP_drawSys;

	// 読み込みすう
	loadData->SWSP_plttTbl[ IMC_DRAW_ACCESSORIE_PLTT_ID ].load_num = IMC_DRAW_ACCESSORIE_PLTT_NUM;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	BGサムネイル用リソースデータ読み込み
 *
 *	@param	drawData	描画システムデータ
 *	@param	loadData	読み込みデータ格納先
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void loadBGThumData( IMC_DRAW_DATA* drawData, IMC_DRAW_LOADRES_DATA* loadData )
{
	int i;		// ループ用
	void* buff;
	int num;		// 登録先

	// アクセサリ用データ読み込み
	for(i=0; i<IMC_BG_RIGHT_MAX; i++ ){
		// キャラクタデータ取得
		buff = ArcUtil_Load(ARC_IMAGECLIP_GRA,
				IMC_BG_THUMB_CG_ARC_GET( i ),
				FALSE, HEAPID_IMAGECLIP_DRAW, ALLOC_BOTTOM);

		num = IMC_BG_THUMB_CHAR_CONT_ID(i);

		// アンパック後のデータを登録
		loadData->SWSP_charTbl[ num ].res_file = IMC_DRAW_SetCharData( drawData, buff, num );
		
		// スプライト描画システムポインタ設定
		loadData->SWSP_charTbl[ num ].s_sys = drawData->SWSP_drawSys;

		
		num = IMC_BG_THUMB_PLTT_CONT_ID(i);
		
		// パレットデータ登録
		buff = ArcUtil_Load(ARC_IMAGECLIP_GRA,
				IMC_BG_RIGHT_CL_ARC_GET(i), FALSE, HEAPID_IMAGECLIP_DRAW, ALLOC_BOTTOM);

		// リソースマネージャに登録
		RESM_AddResNormal( loadData->SWSP_plttRes, buff, num );				

		// アンパック
		NNS_G2dGetUnpackedPaletteData( buff,
				&loadData->SWSP_plttTbl[ num ].res_file );
		GF_ASSERT_MSG( loadData->SWSP_plttTbl[ num ].res_file, "thum %d", IMC_BG_RIGHT_CL_ARC_GET(i) );

		// 描画システムデータ
		loadData->SWSP_plttTbl[ num ].s_sys = drawData->SWSP_drawSys;

		// 読み込みすう
		loadData->SWSP_plttTbl[ num ].load_num = IMC_BG_COLOR_NUM;
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	アクセサリパレットオフセットテーブル作成
 *
 *	@param	data	描画システムデータ
 *	@param	heap	ヒープID
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void initAccePlttOfs( IMC_DRAW_DATA* data, int heap )
{
//	data->accePlttOfsTbl = plttOfs;
	data->accePlttOfsTbl = ArcUtil_Load( ARC_IMAGECLIP_GRA, IMC_ACCESSORIE_PLTT_LINK, FALSE, heap, ALLOC_TOP );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	アクセサリパレットオフセットデータ破棄
 *
 *	@param	data	描画システムデータ
 *
 *	@return
 *
 *
 */
//-----------------------------------------------------------------------------
static void deleteAccePlttOfs( IMC_DRAW_DATA* data )
{
	sys_FreeMemoryEz( data->accePlttOfsTbl );
	data->accePlttOfsTbl = NULL;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	ポケモン描画システムの初期化
 *
 *	@param	drawData		格納先
 *	@param	heap			ヒープID
 *	@param	tex_size		テクスチャサイズ
 *	@param	pltt_size		パレットサイズ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void initSoftSprite( IMC_DRAW_DATA* drawData, int heap, int tex_size, int pltt_size )
{
	NNSGfdTexKey	texKey;
	NNSGfdPlttKey	plttKey;

	// ポケモンデータ転送領域のVramを確保＆転送アドレスとサイズを設定
	drawData->SSM_drawSys = SoftSpriteInit( heap );	
	texKey = NNS_GfdAllocTexVram(tex_size, FALSE, 0);
	plttKey = NNS_GfdAllocPlttVram(pltt_size, FALSE, NNS_GFD_ALLOC_FROM_LOW);
	SoftSpriteTextureTransParamSet( 
			drawData->SSM_drawSys,
			NNS_GfdGetTexKeyAddr(texKey),
			NNS_GfdGetTexKeySize(texKey) );
	SoftSpritePaletteTransParamSet( 
			drawData->SSM_drawSys,
			NNS_GfdGetPlttKeyAddr(plttKey),
			NNS_GfdGetPlttKeySize(plttKey) );

	drawData->SSM_DrawFlag = TRUE;
/*
	OS_Printf( 
			" addr %x size %x \n",
			NNS_GfdGetTexKeyAddr(texKey),
			NNS_GfdGetTexKeySize(texKey) );
	OS_Printf( 
			" addr %x size %x \n ",
			NNS_GfdGetPlttKeyAddr(plttKey),
			NNS_GfdGetPlttKeySize(plttKey) );
//*/
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	ポケモン描画システムの破棄
 *
 *	@param	drawData	
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void deleteSoftSprite( IMC_DRAW_DATA* drawData )
{
	// ポケモン描画スプライトデータ破棄
	SoftSpriteEnd( drawData->SSM_drawSys );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	SWSPのリソース登録データメモリを確保
 *
 *	@param	loadData		登録データのメモリ確保先
 *	@param	char_num		キャラクタデータ数
 *	@param	pltt_num		パレットデータ数
 *	@param	heap			使用ヒープ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void loadSWSPResDataAllocMemory( IMC_DRAW_LOADRES_DATA* loadData, int char_num, int pltt_num, int heap )
{
	// 登録データ領域を作成
	// キャラクタ
	loadData->SWSP_charTbl = sys_AllocMemory( heap, sizeof(SWSP_CHARDATA) * char_num );
	memset( loadData->SWSP_charTbl, 0, sizeof(SWSP_CHARDATA) * char_num );
	loadData->SWSP_charRes = RESM_Init( char_num, heap );	// アンパック前のデータ格納先
	loadData->SWSP_charNum = char_num;

	// パレット
	loadData->SWSP_plttTbl = sys_AllocMemory( heap, sizeof(SWSP_PLTTDATA) * pltt_num );
	memset( loadData->SWSP_plttTbl, 0, sizeof(SWSP_PLTTDATA) * pltt_num );
	loadData->SWSP_plttRes = RESM_Init( pltt_num, heap );	// アンパック前のデータ格納先
	loadData->SWSP_plttNum = pltt_num;
	
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	SWSPのリソース登録データメモリを破棄
 *
 *	@param	loadData		破棄するデータ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void loadSWSPResDataDeleteMemory( IMC_DRAW_LOADRES_DATA* loadData )
{
	// 作成データ破棄
	// リソース破棄
	if(loadData->SWSP_charRes){
		RESM_Delete( loadData->SWSP_charRes );
		loadData->SWSP_charRes = NULL;
	}
	if(loadData->SWSP_plttRes){
		RESM_Delete( loadData->SWSP_plttRes );
		loadData->SWSP_plttRes = NULL;
	}
	
	// 登録データ破棄
	sys_FreeMemoryEz( loadData->SWSP_charTbl );
	loadData->SWSP_charTbl = NULL;
	sys_FreeMemoryEz( loadData->SWSP_plttTbl );
	loadData->SWSP_plttTbl = NULL;
}
