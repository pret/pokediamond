//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		fontoam.c
 *	@brief		OAMを使用した文字列描画システム
 *	@author		tomoya takahashi 
 *	@data		2005.10.20
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

#include <string.h>
#include "system.h"
#include "assert.h"
#include "char_manager.h"
#include "system/arc_tool.dat"
#include "system/arc_util.h"
#include "system/fontoam.naix"

#define	__FONTOAM_H_GLOBAL
#include "system/fontoam.h"

//-----------------------------------------------------------------------------
/**
 *					定数宣言
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	
//	OAM優先順位定数	
//	
//=====================================
enum{
	FONTOAM_PRI_8x8 = 0,	
	FONTOAM_PRI_8x4,
	FONTOAM_PRI_4x8,
	FONTOAM_PRI_4x4,
	FONTOAM_PRI_4x2,
	FONTOAM_PRI_4x1,
	FONTOAM_PRI_2x4,
	FONTOAM_PRI_2x2,
	FONTOAM_PRI_2x1,
	FONTOAM_PRI_1x4,
	FONTOAM_PRI_1x2,
	FONTOAM_PRI_1x1,
	FONTOAM_PRI_MAX
};
enum{
	FONTOAM_PRI_X = 0,
	FONTOAM_PRI_Y,
	FONTOAM_PRI_XY
};

//-------------------------------------
//	
//	OAM埋め尽くしデータの有無
//	
//=====================================
enum{
	FONTOAM_OAM_AREA_NONE,
	FONTOAM_OAM_AREA_RIGHT,		// 右エリアあり
};

#define FONTOAM_CHAR_BYTE	(32)	// 1charサイズ
#define FONTOAM_CHAR_SIZE	(8)		// 幅、高さ

//-----------------------------------------------------------------------------
/**
 *					構造体宣言
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	
//	セルとその座標を保存する構造体
//	
//=====================================
typedef struct _FONTOAM_OBJ_CORE{
	CLACT_WORK_PTR clact;
	int	x;		// ドット単位
	int y;		// ドット単位
} FONTOAM_OBJ_CORE;

//-------------------------------------
//	
//	1OAMフォントデータ
//	
//=====================================
typedef struct _FONTOAM_OBJ{
	// 文字列ウィンドウの形をあらわしている
	// セルのデータ
	FONTOAM_OBJ_CORE*	obj_w;
	int obj_num;

	// おやセルアクター
	CONST_CLACT_WORK_PTR parent;

	// 今の設定座標
	int x;		// ドット単位
	int y;		// ドット単位
} FONTOAM_OBJ;

//-------------------------------------
//	
//	システムデータ
//	
//=====================================
typedef struct _FONTOAM_SYSTEM{
	// OAMサイズ分のセルデータ
	void*	pCellBuff[ FONTOAM_PRI_MAX ];
	NNSG2dCellDataBank* pCellBank[ FONTOAM_PRI_MAX ];

	// 1OAMフォントデータワーク
	FONTOAM_OBJ*	fontoam_work;
	int				fontoam_num;		// ワーク数
} FONTOAM_SYSTEM;


//-------------------------------------
//	
//	OAM埋め尽くしエリア
//	１エリアデータ
//	
//=====================================
typedef struct _FONTOAM_OAM_AREA_ONE{
	// 全てキャラクタ単位
	int top;		// 上
	int left;		// 左
	int width;		// 幅
	int height;		// 高さ
} FONTOAM_OAM_AREA_ONE;

//-------------------------------------
//	
//	OAM埋め尽くしエリア
//
//	まずnowに入っているエリアからOAMを作成
//	nowが全て０になったらrightをnowに代入して
//	nowをまた全て０になるまでOAMで埋めていく
//	
//=====================================
typedef struct _FONTOAM_OAM_AREA{
	FONTOAM_OAM_AREA_ONE now;
	FONTOAM_OAM_AREA_ONE right;
	u8	tmp_flg;					// 値の有無
/*						
	FONTOAM_OAM_AREA_NONE,
	FONTOAM_OAM_AREA_RIGHT,		// 右エリアあり
	FONTOAM_OAM_AERA_MAX		// 両方*/
} FONTOAM_OAM_AREA;

//-------------------------------------
//	
//	埋め尽くしOAMデータ
//	
//=====================================
typedef struct _FONTOAM_OAM_DATA{
	int x;			// キャラクタ単位座標
	int y;			// キャラクタ単位座標
	int oam_size;	// OAMサイズ

	struct _FONTOAM_OAM_DATA* next;
	struct _FONTOAM_OAM_DATA* prev;

} FONTOAM_OAM_DATA;

//-------------------------------------
//	
//	埋め尽くしOAMデータ
//	
//=====================================
typedef struct _FONTOAM_OAM_DATA_SET{
	FONTOAM_OAM_DATA fontoamdata;
	int data_num;
} FONTOAM_OAM_DATA_SET;



//-----------------------------------------------------------------------------
/**
*		グローバル変数
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	
//	OAM優先順位定数	
//	に対応したキャラクタ単位のOAMサイズ
//	
//=====================================
static const u8 FONTOAM_PriTbl[ FONTOAM_PRI_MAX ][ FONTOAM_PRI_XY ] = {
	{8, 8},
	{8, 4},
	{4, 8},
	{4, 4},
	{4, 2},
	{4, 1},
	{2, 4},
	{2, 2},
	{2, 1},
	{1, 4},
	{1, 2},
	{1, 1},
};



//-----------------------------------------------------------------------------
/**
 *					プロトタイプ宣言
*/
//-----------------------------------------------------------------------------
static void cleanFONTOAM_OBJ( FONTOAM_OBJ* fontoam );
static FONTOAM_OBJ* getCleanFONTOAM_OBJ( const FONTOAM_SYSTEM* fontoam_sys );


static int searchOamSize( int x, int y );

static BOOL sumOamArea( FONTOAM_OAM_AREA* oam, FONTOAM_OAM_DATA* list, int heap );
static int getOamData( int x, int y, int heap,  FONTOAM_OAM_DATA* list );

static void charTransOamDataList( const GF_BGL_BMPWIN* bmp, const FONTOAM_OAM_DATA* list, NNSG2dImageProxy* img_proxy, int offs, int draw_area, int heap );
static int charTransOamDataOne( const GF_BGL_BMPWIN* bmp, const FONTOAM_OAM_DATA* oamdata, NNSG2dImageProxy* img_proxy, int char_min_num, int char_mode, int offs, int draw_arae, int heap );

static int charAreaSizeOamDataList( const FONTOAM_OAM_DATA* list, int draw_area );

static void addClActOamDataList( const FONTOAM_INIT* font_init, const FONTOAM_OAM_DATA* list, const NNSG2dImageProxy* img_proxy, FONTOAM_OBJ_PTR font_obj );
static CLACT_WORK_PTR addClActOamDataOne( const FONTOAM_INIT* font_init, const FONTOAM_OAM_DATA* oamdata, const NNSG2dImageProxy* img_proxy );

static void delClActOamDataList( FONTOAM_OBJ_PTR fontoam );

static FONTOAM_OAM_DATA* makeOamList( int heap );
static void destOamList( FONTOAM_OAM_DATA* oamdata );
static void destOamListAll( FONTOAM_OAM_DATA* dummy );
static void setOamList( FONTOAM_OAM_DATA* oamdata, FONTOAM_OAM_DATA* prev );
static void resetOamList( FONTOAM_OAM_DATA* oamdata );


static void charSetOamDataList( const GF_BGL_BMPWIN* bmp, char* pbuff, const FONTOAM_OAM_DATA* list, int draw_area, int heap );
static int charSetOamDataOne( const GF_BGL_BMPWIN* bmp, const FONTOAM_OAM_DATA* oamdata, char* pbuff, int idx, int char_min_num, int char_mode, int heap );


//----------------------------------------------------------------------------
/**
 *
 *	@brief	OAMフォントシステムの作成
 *
 *	@param	workNum		管理する文字列数
 *	@param	heap		使用するヒープ
 *
 *	@return	FONTOAM_SYS_PTR		作成したOAMフォントシステムデータ
 *
 *
 */
//-----------------------------------------------------------------------------
FONTOAM_SYS_PTR FONTOAM_SysInit( int workNum, int heap )
{
	FONTOAM_SYS_PTR fntoam_sys;
	int i;			// ループ用
	
	fntoam_sys = sys_AllocMemory( heap, sizeof(FONTOAM_SYSTEM) );
	GF_ASSERT( fntoam_sys );
	

	// OAMのセルデータを読み込む
	for( i=0; i<FONTOAM_PRI_MAX; i++ ){
		fntoam_sys->pCellBuff[ i ] = ArcUtil_CellBankDataGet( 
				ARC_FONTOAM,
				i, FALSE,
				&fntoam_sys->pCellBank[ i ],
				heap );

		GF_ASSERT( fntoam_sys->pCellBuff[ i ] );
	}
	
	// workNum分の1OAMフォントデータを作成
	fntoam_sys->fontoam_work = sys_AllocMemory( heap, sizeof(FONTOAM_OBJ) * workNum );
	GF_ASSERT( fntoam_sys->fontoam_work );
	fntoam_sys->fontoam_num	= workNum;
	memset( fntoam_sys->fontoam_work, 0, sizeof(FONTOAM_OBJ) * workNum );

	return fntoam_sys;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	OAMフォントシステムの破棄
 *
 *	@param	fntoam_sys	OAMフォントシステムデータ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void FONTOAM_SysDelete( FONTOAM_SYS_PTR fntoam_sys )
{
	int i;

	GF_ASSERT( fntoam_sys );
	
	for( i=0; i<FONTOAM_PRI_MAX; i++ ){
		sys_FreeMemoryEz(fntoam_sys->pCellBuff[ i ]);
	}
	sys_FreeMemoryEz( fntoam_sys->fontoam_work );
	sys_FreeMemoryEz( fntoam_sys );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	OAMフォント作成
 *
 *	@param	fontoam_init	OAMフォント作成データ
 *
 *	@return	FONTOAM_OBJ_PTR	OAMフォントデータ
 *
 *
 */
//-----------------------------------------------------------------------------
FONTOAM_OBJ_PTR FONTOAM_Init( const FONTOAM_INIT* fontoam_init )
{
	FONTOAM_OBJ_PTR fontoam;
	FONTOAM_OAM_DATA list_dummy;
	int oam_num;
	NNSG2dImageProxy* img_proxy;

	GF_ASSERT( fontoam_init );

	// 空のテーブルを取得
	fontoam = getCleanFONTOAM_OBJ( fontoam_init->fontoam_sys );
	GF_ASSERT_MSG( fontoam, "空のOAMフォントテーブルがありません" );
	fontoam->parent	= fontoam_init->parent;	// 親データ代入

	fontoam->x	= fontoam_init->x;
	fontoam->y	= fontoam_init->y;

	// OAMデータ作成
	list_dummy.next = &list_dummy;
	list_dummy.prev = &list_dummy;
	oam_num = getOamData( fontoam_init->bmp->sizx, 
			fontoam_init->bmp->sizy,
			fontoam_init->heap, 
			&list_dummy );

	// oam_num分のイメージプロクシと、セルアクター登録領域を作成
	img_proxy = sys_AllocMemoryLo( fontoam_init->heap,
			sizeof(NNSG2dImageProxy) * oam_num );
	fontoam->obj_w = sys_AllocMemory( fontoam_init->heap,
			sizeof(FONTOAM_OBJ_CORE) * oam_num );
	fontoam->obj_num = oam_num;

	// キャラクタデータ転送
	charTransOamDataList( fontoam_init->bmp, 
			&list_dummy,
			img_proxy,
			fontoam_init->char_ofs,
			fontoam_init->draw_area,
			fontoam_init->heap );

	// セルアクター登録
	addClActOamDataList( fontoam_init,
			&list_dummy,
			img_proxy,
			fontoam );

	// プロクシの破棄
	sys_FreeMemoryEz( img_proxy );

	// OAMデータ破棄
	destOamListAll( &list_dummy );

	return fontoam;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	OAMフォント破棄
 *
 *	@param	fontoam 
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void FONTOAM_Delete( FONTOAM_OBJ_PTR fontoam )
{
	GF_ASSERT( fontoam );
	GF_ASSERT( fontoam->obj_w );
	
	delClActOamDataList( fontoam );
	
	sys_FreeMemoryEz( fontoam->obj_w );
	cleanFONTOAM_OBJ( fontoam );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	ビットマップウィンドウをOAMフォントシステムで表示するために必要なキャラクタデータサイズを取得
 *
 *	@param	bmp			ビットマップデータ
 *	@param	draw_area	描画エリア
 *	@param	heap		使用するヒープ
 *
 *	@return	表示するために必要なキャラクタサイズ
 *	
 *	char_managerを使用しているときは、このサイズ分
 *	先にVram領域を確保しておく必要があるため作成
 *
 *
 */
//-----------------------------------------------------------------------------
int FONTOAM_NeedCharSize( const GF_BGL_BMPWIN* bmp, int draw_area,  int heap )
{
	FONTOAM_OAM_DATA list_dummy;
	int offs;

	// OAMデータ作成
	list_dummy.next = &list_dummy;
	list_dummy.prev = &list_dummy;
	getOamData( bmp->sizx, 
			bmp->sizy,
			heap, 
			&list_dummy );

	offs = charAreaSizeOamDataList( &list_dummy, draw_area );

	// OAMデータ破棄
	destOamListAll( &list_dummy );

	return offs;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	OAMフォント座標を設定
 *
 *	@param	fontoam		OAMフォント
 *	@param	x			ｘ座標		親アクターがいるときはオフセット座標
 *	@param	y			ｙ座標		親アクターがいるときはオフセット座標
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void FONTOAM_SetMat( FONTOAM_OBJ_PTR fontoam, int x, int y )
{
	int i;		// ループ用
	VecFx32	set_mat;	// 設定座標
	const VecFx32* parent_mat;

	GF_ASSERT( fontoam );
	
	fontoam->x = x;
	fontoam->y = y;

	x *= FX32_ONE;
	y *= FX32_ONE;

	// 親がいるときは親からのオフセットになる
	if( fontoam->parent ){

		parent_mat = CLACT_GetMatrix( fontoam->parent );

		x += parent_mat->x;
		y += parent_mat->y;
	}
	
		
	set_mat.z = 0;
	// 全セルアクターに座標を設定
	for(i=0; i<fontoam->obj_num; i++ ){
		set_mat.x = x + (fontoam->obj_w[ i ].x << FX32_SHIFT);
		set_mat.y = y + (fontoam->obj_w[ i ].y << FX32_SHIFT);
		CLACT_SetMatrix( fontoam->obj_w[ i ].clact, &set_mat );
	}
}

//----------------------------------------------------------------------------
/**
 * ●親セルアクターを設定していない場合は使用しても意味がありません。
 *	
 *	@brief	親アクターの座標位置に位置を合わせる
 *
 *	@param	fontoam 
 *
 *	@return
 *
 * ■親セルアクターの位置を変更したときに呼んでください。
 *	　親に合わせて文字も動きます
 *
 */
//-----------------------------------------------------------------------------
void FONTOAM_ReflectParentMat( FONTOAM_OBJ_PTR fontoam )
{
	int i;		// ループ用
	VecFx32	set_mat;	// 設定座標
	const VecFx32* parent_mat;
	fx32 x, y;

	GF_ASSERT( fontoam );

	// 親がいるときは親からのオフセットになる
	if( fontoam->parent ){
		
		x = fontoam->x << FX32_SHIFT;
		y = fontoam->y << FX32_SHIFT;

		parent_mat = CLACT_GetMatrix( fontoam->parent );

		x += parent_mat->x;
		y += parent_mat->y;
			
		set_mat.z = 0;
		// 全セルアクターに座標を設定
		for(i=0; i<fontoam->obj_num; i++ ){
			set_mat.x = x + (fontoam->obj_w[ i ].x << FX32_SHIFT);
			set_mat.y = y + (fontoam->obj_w[ i ].y << FX32_SHIFT);
			CLACT_SetMatrix( fontoam->obj_w[ i ].clact, &set_mat );
		}
	}
}


//----------------------------------------------------------------------------
/**
 *
 *	@brief	OAMフォント座標を取得
 *
 *	@param	fontoam		OAMフォント
 *	@param	x			ｘ座標		親アクターがいるときはオフセット座標
 *	@param	y			ｙ座標		親アクターがいるときはオフセット座標
 *
 *	@return
 *
 *
 */
//-----------------------------------------------------------------------------
void FONTOAM_GetMat( CONST_FONTOAM_OBJ_PTR fontoam, int* x, int* y )
{
	GF_ASSERT( fontoam );
	GF_ASSERT( x );
	GF_ASSERT( y );

	*x = fontoam->x;
	*y = fontoam->y;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	表示/非表示設定
 *
 *	@param	fontoam		OAMフォントオブジェ
 *	@param	flag		表示/非表示フラグ
 *
 *	@return	none
 *
 * flag
 *	TRUE	表示
 *	FALSE	非表示
 *
 */
//-----------------------------------------------------------------------------
void FONTOAM_SetDrawFlag( FONTOAM_OBJ_PTR fontoam, BOOL flag )
{
	int i;		// ループ用

	GF_ASSERT( fontoam );
	// 全セルアクターに座標を設定
	for(i=0; i<fontoam->obj_num; i++ ){

		CLACT_SetDrawFlag( fontoam->obj_w[ i ].clact, flag );
	}
}


//----------------------------------------------------------------------------
/**
 *
 *	@brief	表示/非表示を取得
 *
 *	@param	fontoam		OAMフォントオブジェ
 *
 *	@retval	TRUE	表示中
 *	@retval	FALSE	非表示中
 *
 *
 */
//-----------------------------------------------------------------------------
BOOL FONTOAM_GetDrawFlag( CONST_FONTOAM_OBJ_PTR fontoam )
{
	GF_ASSERT( fontoam );
	
	return CLACT_GetDrawFlag( fontoam->obj_w[0].clact );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	BG面との優先順位を設定
 *
 *	@param	fontoam	OAMフォントデータ
 *	@param	pri		BGとの優先順位
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void FONTOAM_SetBGPriority( FONTOAM_OBJ_PTR fontoam, u8 pri )
{
	int i;		// ループ用

	GF_ASSERT( fontoam );
	// 全セルアクターに座標を設定
	for(i=0; i<fontoam->obj_num; i++ ){

		CLACT_BGPriorityChg( fontoam->obj_w[ i ].clact, pri );
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	BG面との描画優先順位を取得
 *
 *	@param	fontoam		OAMフォントオブジェ
 *
 *	@return	BG面との優先順位
 *
 *
 */
//-----------------------------------------------------------------------------
int FONTOAM_GetBGPriority( CONST_FONTOAM_OBJ_PTR fontoam )
{
	GF_ASSERT( fontoam );
	
	return CLACT_BGPriorityGet( fontoam->obj_w[0].clact );
}

//-----------------------------------------------------------------------------
/**
 *	@brief	描画優先順位を設定
 *
 *	@param	fontoam		OAMフォントデータ
 *	@param	pri			表示優先順位
 *				
 * 
 *	@return	none
 */
 //----------------------------------------------------------------------------
void FONTOAM_SetDrawPriority( FONTOAM_OBJ_PTR fontoam, u32 pri )
{
	int i;		// ループ用

	GF_ASSERT( fontoam );
	// 全セルアクターに座標を設定
	for(i=0; i<fontoam->obj_num; i++ ){

		CLACT_DrawPriorityChg( fontoam->obj_w[ i ].clact, pri );
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	描画優先順位を取得
 *
 *	@param	fontoam		OAMフォントオブジェ
 *
 *	@return	u32			描画優先順位
 *
 *
 */
//-----------------------------------------------------------------------------
u32 FONTOAM_GetDrawPriority( CONST_FONTOAM_OBJ_PTR fontoam )
{
	GF_ASSERT( fontoam );
	
	return CLACT_DrawPriorityGet( fontoam->obj_w[0].clact );
}

//-----------------------------------------------------------------------------
/**
 * ●OAMがこのパレットナンバーを見るようになります。
 *
 *	@brief				パレットナンバーを変更
 *
 *	@param	fontoam		OAMフォントオブジェ
 *	@param	pltt_no		設定パレットナンバー
 * 
 *	@return	none
 *
 * ■パレットナンバー設定とパレットオフセット設定は同居しません。
 *　　●パレットナンバーを設定するとオフセットの値は反映されなくなります。
 *	　●オフセット値を設定したときはパレットナンバーが反映されなくなります。
 * 
 */
 //----------------------------------------------------------------------------
void FONTOAM_SetPaletteNo( FONTOAM_OBJ_PTR fontoam, u32 pltt_no )
{
	int i;		// ループ用

	GF_ASSERT( fontoam );
	// 全セルアクターに座標を設定
	for(i=0; i<fontoam->obj_num; i++ ){

		CLACT_PaletteNoChg( fontoam->obj_w[ i ].clact, pltt_no );
	}
}
void FONTOAM_SetPaletteNoAddTransPlttNo( FONTOAM_OBJ_PTR fontoam, u32 pltt_no )
{
	int i;		// ループ用

	GF_ASSERT( fontoam );
	// 全セルアクターに座標を設定
	for(i=0; i<fontoam->obj_num; i++ ){

		CLACT_PaletteNoChgAddTransPlttNo( fontoam->obj_w[ i ].clact, pltt_no );
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	パレットナンバー取得
 *
 *	@param	fontoam		OAMフォントオブジェ
 *
 *	@return	u32			今のパレットナンバー
 *
 *
 */
//-----------------------------------------------------------------------------
u32 FONTOAM_GetPaletteNo( CONST_FONTOAM_OBJ_PTR fontoam )
{
	GF_ASSERT( fontoam );
	
	return CLACT_PaletteNoGet( fontoam->obj_w[0].clact );
}

//-----------------------------------------------------------------------------
/**
 * ●OAMアトリビュートに設定されているパレットナンバーに加算されます。
 *	 もし、OAMアトリビュートのカラーパレットNoが２でオフセットに２を
 *	 設定すると、４のカラーパレットを参照するようになります
 * 
 *	@brief	パレットオフセットを設定
 *
 *	@param	fontoam		OAMフォントオブジェ
 *	@param	pltt_ofs	パレットオフセット
 * 
 *	@return	none
 *
 * ■パレットナンバー設定とパレットオフセット設定は同居しません。
 *　　●パレットナンバーを設定するとオフセットの値は反映されなくなります。
 *	　●オフセット値を設定したときはパレットナンバーが反映されなくなります。
 * 
 */
 //----------------------------------------------------------------------------
void FONTOAM_SetPaletteOffset( FONTOAM_OBJ_PTR fontoam, u32 pltt_ofs )
{
	int i;		// ループ用

	GF_ASSERT( fontoam );
	// 全セルアクターに座標を設定
	for(i=0; i<fontoam->obj_num; i++ ){

		CLACT_PaletteOffsetChg( fontoam->obj_w[ i ].clact, pltt_ofs );
	}
}
void FONTOAM_SetPaletteOffsetAddTransPlttNo( FONTOAM_OBJ_PTR fontoam, u32 pltt_ofs )
{
	int i;		// ループ用

	GF_ASSERT( fontoam );
	// 全セルアクターに座標を設定
	for(i=0; i<fontoam->obj_num; i++ ){

		CLACT_PaletteOffsetChgAddTransPlttNo( fontoam->obj_w[ i ].clact, pltt_ofs );
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	パレットオフセット値取得
 *
 *	@param	fontoam	OAMフォントオブジェ
 *
 *	@return	u32		今のパレットオフセット値
 *
 */
//-----------------------------------------------------------------------------
u32 FONTOAM_GetPaletteOffset( CONST_FONTOAM_OBJ_PTR fontoam )
{
	GF_ASSERT( fontoam );
	
	return CLACT_PaletteOffsetGet( fontoam->obj_w[0].clact );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	モザイク設定
 *
 *	@param	fontoam	OAMフォントオブジェ
 *	@param	flag	フラグ	TRUE＝モザイクON	FALSE＝モザイクOFF
 *
 *	@return	none
 *
 * モザイクOFFの時でも、ニトロキャラクタでモザイクONにしたOAMは
 * モザイクがかかって描画されます。
 *
 */
//-----------------------------------------------------------------------------
void FONTOAM_SetMosaic( FONTOAM_OBJ_PTR fontoam, BOOL flag )
{
	int i;		// ループ用

	GF_ASSERT( fontoam );
	// 全セルアクターに座標を設定
	for(i=0; i<fontoam->obj_num; i++ ){

		CLACT_MosaicSet( fontoam->obj_w[ i ].clact, flag );
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	モザイク設定状態を取得
 *
 *	@param	fontoam	OAMフォントオブジェ
 *
 *	@retval	TRUE	モザイク＝ON
 *	@retval	FALSE	モザイク＝OFF	（ニトロキャラクタで設定してるときは反映される）
 *
 *
 */
//-----------------------------------------------------------------------------
BOOL FONTOAM_GetMosaic( CONST_FONTOAM_OBJ_PTR fontoam )
{
	GF_ASSERT( fontoam );
	
	return CLACT_MosaicGet( fontoam->obj_w[0].clact );
}

//----------------------------------------------------------------------------
/**
 *	@brief	オブジェクトモードの設定
 *
 *	@param	fontoam		フォントOAM
 *	@param	objmode		オブジェモード
 *
 *	@return	none
 *
	GX_OAM_MODE_NORMAL		ノーマルOBJ 
	GX_OAM_MODE_XLU			半透明OBJ 
	GX_OAM_MODE_OBJWND		OBJウィンドウ 
	GX_OAM_MODE_BITMAPOBJ	ビットマップOBJ 
 */
//-----------------------------------------------------------------------------
void FONTOAM_ObjModeSet( FONTOAM_OBJ_PTR fontoam, GXOamMode objmode )
{
	int i;		// ループ用

	GF_ASSERT( fontoam );
	// 全セルアクターに座標を設定
	for(i=0; i<fontoam->obj_num; i++ ){

		CLACT_ObjModeSet( fontoam->obj_w[ i ].clact, objmode );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	オブジェモードの取得
 *
 *	@param	fontoam		FONTOAM
 *	@param	objmode		オブジェモード
 *
 *	@retval	GX_OAM_MODE_NORMAL		ノーマルOBJ 
 *	@retval	GX_OAM_MODE_XLU			半透明OBJ 
 *	@retval	GX_OAM_MODE_OBJWND		OBJウィンドウ 
 *	@retval	GX_OAM_MODE_BITMAPOBJ	ビットマップOBJ 
 */
//-----------------------------------------------------------------------------
GXOamMode FONTOAM_ObjModeGet( CONST_FONTOAM_OBJ_PTR fontoam, GXOamMode objmode )
{
	GF_ASSERT( fontoam );
	
	return CLACT_ObjModeGet( fontoam->obj_w[0].clact );
}



//-----------------------------------------------------------------------------
/**
 *		FONTOAM	細か処理分岐バージョン
 */
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *	@brief	フォントOAM分割データ作成
 *
 *	@param	bmp		データ作成元ビットマップ
 *	@param	heap	ヒープ
 *
 *	@return	分割データ
 */
//-----------------------------------------------------------------------------
FONTOAM_OAM_DATA_PTR FONTOAM_OAMDATA_Make( const GF_BGL_BMPWIN* bmp, int heap )
{
	FONTOAM_OAM_DATA_PTR fontoam_data;

	fontoam_data = sys_AllocMemory( heap, sizeof(FONTOAM_OAM_DATA_SET) );
	fontoam_data->fontoamdata.next = &fontoam_data->fontoamdata;
	fontoam_data->fontoamdata.prev = &fontoam_data->fontoamdata;

	// OAMデータ作成
	fontoam_data->data_num = getOamData( bmp->sizx, 
			bmp->sizy,
			heap, 
			&fontoam_data->fontoamdata );

	return fontoam_data;
}

//----------------------------------------------------------------------------
/**
 *	@brief	フォントOAM分割データの破棄
 *
 *	@param	oamdata	フォントOAM分割データ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void FONTOAM_OAMDATA_Free( FONTOAM_OAM_DATA_PTR oamdata )
{
	// OAMデータ破棄
	destOamListAll( &oamdata->fontoamdata );

	sys_FreeMemoryEz( oamdata );
}

//----------------------------------------------------------------------------
/**
 *	@brief	フォントOAM分割データから転送に必要がキャラクタサイズを取得
 *
 *	@param	oamdata		フォントOAM分割データ
 *	@param	draw_area	描画エリア
 *
 *	@return	必要がキャラクタサイズ
 */
//-----------------------------------------------------------------------------
int FONTOAM_OAMDATA_NeedCharSize( CONST_FONTOAM_OAM_DATA_PTR oamdata, int draw_area )
{
	return charAreaSizeOamDataList( &oamdata->fontoamdata, draw_area );
}

//----------------------------------------------------------------------------
/**
 *	@brief	フォントOAM分割データを使用してフォントOAMの作成
 *
 *	@param	fontoam_init		ふぉんとOAM 作成データ
 *	@param	oamdata				OAM分割データ
 *
 *	@return	作成されたフォントOAM
 */
//-----------------------------------------------------------------------------
FONTOAM_OBJ_PTR FONTOAM_OAMDATA_Init( const FONTOAM_INIT* fontoam_init, CONST_FONTOAM_OAM_DATA_PTR oamdata )
{
	FONTOAM_OBJ_PTR fontoam;
	NNSG2dImageProxy* img_proxy;

	GF_ASSERT( fontoam_init );

	// 空のテーブルを取得
	fontoam = getCleanFONTOAM_OBJ( fontoam_init->fontoam_sys );
	GF_ASSERT_MSG( fontoam, "空のOAMフォントテーブルがありません" );
	fontoam->parent	= fontoam_init->parent;	// 親データ代入

	fontoam->x	= fontoam_init->x;
	fontoam->y	= fontoam_init->y;

	// oam_num分のイメージプロクシと、セルアクター登録領域を作成
	img_proxy = sys_AllocMemoryLo( fontoam_init->heap,
			sizeof(NNSG2dImageProxy) * oamdata->data_num );
	fontoam->obj_w = sys_AllocMemory( fontoam_init->heap,
			sizeof(FONTOAM_OBJ_CORE) * oamdata->data_num );
	fontoam->obj_num = oamdata->data_num;

	// キャラクタデータ転送
	charTransOamDataList( fontoam_init->bmp, 
			&oamdata->fontoamdata,
			img_proxy,
			fontoam_init->char_ofs,
			fontoam_init->draw_area,
			fontoam_init->heap );

	// セルアクター登録
	addClActOamDataList( fontoam_init,
			&oamdata->fontoamdata,
			img_proxy,
			fontoam );

	// プロクシの破棄
	sys_FreeMemoryEz( img_proxy );

	return fontoam;
}

//----------------------------------------------------------------------------
/**
 *	@brief	OAMフォント破棄
 *
 *	@param	fontoam 
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void FONTOAM_OAMDATA_Delete( FONTOAM_OBJ_PTR fontoam )
{
	FONTOAM_Delete( fontoam );
}

//----------------------------------------------------------------------------
/**
 *	@brief	フォントOAMのビットマップデータを変更する
 *
 *	@param	fontoam		変更するFONTOAM
 *	@param	oamdata		OAM分割データ
 *	@param	bmp			ビットマップ 
 *	@param	heap		ヒープ
 *
 *	@return	none
 *
 *	＊注意点
 *		ビットマップの大きさが等しい必要があります。
 */
//-----------------------------------------------------------------------------
void FONTOAM_OAMDATA_ResetBmp( FONTOAM_OBJ_PTR fontoam, CONST_FONTOAM_OAM_DATA_PTR oamdata, const GF_BGL_BMPWIN* bmp, int heap )
{
	int need_char;
	char* pbuff;
	NNSG2dImageProxy* p_prox;
	CLACT_WORK_PTR start_act = fontoam->obj_w[0].clact;
	int draw_area;

	// 描画エリア
	draw_area = CLACT_VramTypeGet( start_act );


	// 必要キャラクタバッファ作成
	need_char = FONTOAM_OAMDATA_NeedCharSize( oamdata, draw_area );

	// キャラクタバッファ作成
	pbuff = (char*)sys_AllocMemoryLo( heap, need_char );
	memset( pbuff, 0, need_char );

	// 転送キャラクタデータ作成
	charSetOamDataList( bmp, pbuff, &oamdata->fontoamdata, draw_area, heap );

    DC_FlushRange(pbuff, need_char);

	// Vramに転送
	p_prox = CLACT_ImageProxyGet( start_act );
	if( draw_area == NNS_G2D_VRAM_TYPE_2DMAIN ){
		GX_LoadOBJ( pbuff, NNS_G2dGetImageLocation(	p_prox, NNS_G2D_VRAM_TYPE_2DMAIN ), need_char );	
	}else{
		GXS_LoadOBJ( pbuff, NNS_G2dGetImageLocation(	p_prox, NNS_G2D_VRAM_TYPE_2DSUB ), need_char );	
	}

	// キャラクタバッファ破棄
	sys_FreeMemoryEz( pbuff );
}



//-----------------------------------------------------------------------------
/**
 *		FONTOAMとは無関係ですが、汎用的に使用できる関数
 */
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *
 *	@brief	BMPのキャラクタデータをOAMのサイズで切り取る
 *
 *	@param	bmp				ビットマップデータ
 *	@param	oam_csx			OAMの横サイズ	（キャラクタ単位）
 *	@param	oam_csy			OAMの縦サイズ	（キャラクタ単位）
 *	@param	bmp_cmx			ビットマップ切り取り左上ｘ座標	（キャラクタ単位）
 *	@param	bmp_cmy			ビットマップ切り取り左上ｙ座標	（キャラクタ単位）
 *	@param	char_buff		出力先キャラクタバッファ (oam_csx * oam_csy)*32byte　サイズ以上の領域
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void FONTOAM_BmpCutOamSize( const GF_BGL_BMPWIN* cp_bmp, int oam_csx, int oam_csy, int bmp_cmx, int bmp_cmy, char* char_buff )
{
	int i;				// ループ用
	int buff_out;		// バッファ書き込み先
	int buff_in;		// バッファ読み込み先
	
	// bmpデータのサイズが足りるかチェック
	GF_ASSERT( cp_bmp->sizx >= (oam_csx + bmp_cmx) );
	GF_ASSERT( cp_bmp->sizy >= (oam_csy + bmp_cmy) );
	
	// ローカルバッファにデータ代入
	for( i=0; i<oam_csy; i++ ){
		
		buff_out = i * oam_csx;
		buff_out *= FONTOAM_CHAR_BYTE;
		buff_in =  ((i + bmp_cmy) * cp_bmp->sizx);
		buff_in += bmp_cmx;
		buff_in *= FONTOAM_CHAR_BYTE;
		memcpy( char_buff + buff_out, (char*)(cp_bmp->chrbuf) + buff_in , FONTOAM_CHAR_BYTE * oam_csx );
	}
}

//-----------------------------------------------------------------------------
/**
*		プライベート関数
*/
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *
 *	@brief	テーブルを初期化
 *
 *	@param	fontoam		OAMフォント
 *	
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void cleanFONTOAM_OBJ( FONTOAM_OBJ* fontoam )
{
	memset( fontoam, 0, sizeof(FONTOAM_OBJ) );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	空のテーブルを取得
 *
 *	@param	fontoam_sys		OAMフォントシステム
 *
 *	@return	FONTOAM_OBJ*	OAMフォント
 *
 *
 */
//-----------------------------------------------------------------------------
static FONTOAM_OBJ* getCleanFONTOAM_OBJ( const FONTOAM_SYSTEM* fontoam_sys )
{
	int i;		// ループ用

	for( i=0; i<fontoam_sys->fontoam_num; i++ ){

		if( fontoam_sys->fontoam_work[ i ].obj_w == NULL ){
			return fontoam_sys->fontoam_work  + i;
		}
	}


	return NULL;
}




//----------------------------------------------------------------------------
/**
 *
 *	@brief	幅と高さから最適なOAMサイズを取得する
 *
 *	@param	x		幅		キャラクタ単位
 *	@param	y		高さ	キャラクタ単位
 *
 *		
 *	@retval		FONTOAM_PRI_8x8 = 0,	
 * 	@retval		FONTOAM_PRI_8x4,
 *	@retval		FONTOAM_PRI_4x8,
 *	@retval		FONTOAM_PRI_4x4,
 *	@retval		FONTOAM_PRI_4x2,
 *	@retval		FONTOAM_PRI_4x1,
 *	@retval		FONTOAM_PRI_2x4,
 *	@retval		FONTOAM_PRI_2x2,
 *	@retval		FONTOAM_PRI_2x1,
 *	@retval		FONTOAM_PRI_1x4,
 *	@retval		FONTOAM_PRI_1x2,
 *	@retval		FONTOAM_PRI_1x1,
 *
 */
//-----------------------------------------------------------------------------
static int searchOamSize( int x, int y )
{
	int i;	// ループ用

	for( i = 0; i < FONTOAM_PRI_MAX; i++ ){
		
		// 両方が入りきる値かチェック
		if( (FONTOAM_PriTbl[ i ][ FONTOAM_PRI_X ] <= x) &&
			(FONTOAM_PriTbl[ i ][ FONTOAM_PRI_Y ] <= y) ){
			return i;
		}
	}

	return FONTOAM_PRI_MAX;		//<-ここに来ることはない
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	OAM埋め尽くしデータ作成
 *
 *	@param	oam		エリアデータ
 *	@param	list	リスト先頭ダミーデータ
 *	@param	heap	使用するヒープ
 *
 *	@retval	TRUE	埋め尽くしデータ完成
 *	@retval FALSE	埋め尽くしデータ作成中
 *
 * ここに渡してくる値の高さは8キャラ　4キャラ 2キャラ 1キャラのいずれか
 * にしてください。
 * 
 *
 */
//-----------------------------------------------------------------------------
static BOOL sumOamArea( FONTOAM_OAM_AREA* oam, FONTOAM_OAM_DATA* list, int heap )
{
	FONTOAM_OAM_DATA* oam_data;
	int rest_height;	// あまり高さ
	int rest_width;		// あまり幅

	
	// OAMデータメモリ確保
	oam_data = makeOamList( heap );
	setOamList( oam_data, list->prev );		// 最後尾に登録
	
	// サイズからOAMサイズを取得
	oam_data->oam_size = searchOamSize( oam->now.width, oam->now.height );

	// 今の位置を設定
	oam_data->x = oam->now.left;
	oam_data->y = oam->now.top;

	// 今のOAM埋め尽くしエリアから埋めたOAMサイズを減らす
	rest_width	= oam->now.width - FONTOAM_PriTbl[ oam_data->oam_size ][ FONTOAM_PRI_X ];
	rest_height = oam->now.height - FONTOAM_PriTbl[ oam_data->oam_size ][ FONTOAM_PRI_Y ];

	// 幅にあまりがあるときは
	// 縦にはあまりがないはず
	if( rest_width > 0 ){
		oam->right.height	= oam->now.height;
		oam->right.width	= rest_width;
		oam->right.top		= oam->now.top;
		oam->right.left		= oam->now.left + FONTOAM_PriTbl[ oam_data->oam_size ][ FONTOAM_PRI_X ];

		GF_ASSERT( (oam->tmp_flg != FONTOAM_OAM_AREA_RIGHT) );
		oam->tmp_flg = FONTOAM_OAM_AREA_RIGHT;
	}

	// 高さにあまりがあるときは、幅にはあまりはない
	// 高さあまりのあるときは今エリアを再設定
	// 高さにあまりの無いときは右エリアを今エリアにする
	if( rest_height > 0 ){
		oam->now.top = oam->now.top + FONTOAM_PriTbl[ oam_data->oam_size ][ FONTOAM_PRI_Y ];
		oam->now.height = rest_height;
	}else{
		

		// 右があるかチェック
		if( oam->tmp_flg == FONTOAM_OAM_AREA_RIGHT ){
			oam->now = oam->right;
			oam->tmp_flg = FONTOAM_OAM_AREA_NONE;
		}else{
			// 終わり
			return TRUE;
		}
	}

	return FALSE;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	データを書き出すOAMのデータを作成する
 *
 *	@param	x		OAM書き出しビットマップｘサイズ
 *	@param	y		OAM書き出しビットマップｙサイズ
 *	@param	heap	使用するヒープ
 *	@param	list	OAMデータリスト先頭データ
 *
 *	@return	必要セルアクター数
 *
 *
 */
//-----------------------------------------------------------------------------
static int getOamData( int x, int y, int heap,  FONTOAM_OAM_DATA* list )
{
	FONTOAM_OAM_AREA_ONE next_area;		// 次チェックするエリア
	FONTOAM_OAM_AREA	now_area;		// 今からチェックするエリア
	int in_oam_size;					// エリアに入るOAMサイズ
	int count;							// 必要セルアクター数
	
	// サイズ０チェック
	GF_ASSERT( x );
	GF_ASSERT( y );

	count = 0;
	now_area.now.top	= 0;
	now_area.now.left	= 0;
	now_area.now.width	= x;
	now_area.now.height	= y;
	now_area.tmp_flg	= FONTOAM_OAM_AREA_NONE;
	next_area.left		= 0;
	next_area.width		= x;
	
	// エリア情報がある限り
	while( now_area.now.height != 0 ){

		// 今のエリアの高さからチェックするエリアの高さを検索
		in_oam_size			= searchOamSize( now_area.now.width, now_area.now.height );
		next_area.top		= now_area.now.top + FONTOAM_PriTbl[ in_oam_size ][ FONTOAM_PRI_Y ];
		next_area.height	= now_area.now.height - FONTOAM_PriTbl[ in_oam_size ][ FONTOAM_PRI_Y ];
		now_area.now.height = FONTOAM_PriTbl[ in_oam_size ][ FONTOAM_PRI_Y ];

		// 入るOAMを作成
		do{
			count ++;
		}while( sumOamArea( &now_area, list, heap ) == FALSE );

		// nextをnowに代入
		now_area.now = next_area;
	}

	return count;
}


//----------------------------------------------------------------------------
/**
 *	
 *	@brief	OAMデータリスト分のキャラクタデータを転送し、イメージプロクシを作成
 *
 *	@param	bmp			ビットマップウィンドウデータ
 *	@param	list		OAMデータリスト
 *	@param	img_proxy	イメージプロクシ
 *	@param	offs		オフセット値
 *	@param	draw_area	描画先
 *	@param	heap		使用するヒープ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void charTransOamDataList( const GF_BGL_BMPWIN* bmp, const FONTOAM_OAM_DATA* list, NNSG2dImageProxy* img_proxy, int offs, int draw_area, int heap )
{
	FONTOAM_OAM_DATA* work;
	int count;		// カウンタ
	int char_min;	// キャラクタデータの最小単位
	GXOBJVRamModeChar  map_mode;
	
	// キャラクタデータの最小単位を計算
	if( draw_area == NNS_G2D_VRAM_TYPE_2DMAIN ){
		map_mode = GX_GetOBJVRamModeChar();
	}else{
		map_mode = GXS_GetOBJVRamModeChar();
	}
	char_min = CharModeMinNum( map_mode );

	count = 0;
	work = list->next;
	while( work != list ){

		NNS_G2dInitImageProxy( img_proxy + count );
		offs = charTransOamDataOne( bmp, work, img_proxy + count, char_min, map_mode, offs, draw_area, heap );
		work = work->next;
		count++;
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	OAMデータ１つ分のキャラクタデータを作成し、転送
 *
 *	@param	bmp			ビットマップウィンドウデータ
 *	@param	oamdata		OAMデータ
 *	@param	img_proxy	設定イメージプロクシ
 *	@param	char_min_numキャラクタモードで設定されている最低のキャラクタサイズ
 *	@param	char_mode	マッピングモード
 *	@param	offs		オフセット値
 *	@param	draw_area	描画先
 *	@param	heap		使用するヒープ
 *
 *	@return	転送した分ずらしたオフセット
 *
 *
 */
//-----------------------------------------------------------------------------
static int charTransOamDataOne( const GF_BGL_BMPWIN* bmp, const FONTOAM_OAM_DATA* oamdata, NNSG2dImageProxy* img_proxy, int char_min_num, int char_mode, int offs, int draw_arae, int heap )
{
	char* local_buff;		// OAM１つ分のキャラクタデータ
	int buff_size;
	int oam_x, oam_y;	// oamサイズ

	oam_x = FONTOAM_PriTbl[ oamdata->oam_size ][ FONTOAM_PRI_X ];
	oam_y = FONTOAM_PriTbl[ oamdata->oam_size ][ FONTOAM_PRI_Y ]; 
	
	// oamサイズからキャラクタデータバッファを作成
	buff_size =  oam_x;
	buff_size *= oam_y;
	if( buff_size < char_min_num ){
		buff_size = char_min_num;
	}
	buff_size *= FONTOAM_CHAR_BYTE;
	local_buff = sys_AllocMemoryLo( heap, buff_size );
	
	// ローカルバッファにデータ代入
	FONTOAM_BmpCutOamSize( bmp, oam_x, oam_y, oamdata->x, oamdata->y, local_buff );

    DC_FlushRange(local_buff, buff_size);

	
	// 転送
	if( draw_arae == NNS_G2D_VRAM_TYPE_2DMAIN ){
		GX_LoadOBJ( local_buff, offs, buff_size );	
		img_proxy->vramLocation.baseAddrOfVram[ NNS_G2D_VRAM_TYPE_2DMAIN ] = offs;
		img_proxy->attr.mappingType = GX_GetOBJVRamModeChar();	  // メイン
	}else{
		GXS_LoadOBJ( local_buff, offs, buff_size );	
		img_proxy->vramLocation.baseAddrOfVram[ NNS_G2D_VRAM_TYPE_2DSUB ] = offs;
		img_proxy->attr.mappingType = GXS_GetOBJVRamModeChar();   // サブ
	}
	img_proxy->attr.sizeS         = NNS_G2D_1D_MAPPING_CHAR_SIZE;
    img_proxy->attr.sizeT         = NNS_G2D_1D_MAPPING_CHAR_SIZE;
    img_proxy->attr.fmt           = GX_TEXFMT_PLTT16;
    img_proxy->attr.bExtendedPlt  = FALSE;                
    img_proxy->attr.plttUse       = GX_TEXPLTTCOLOR0_TRNS;
    img_proxy->attr.mappingType   = char_mode;

	sys_FreeMemoryEz( local_buff );

	return (offs + buff_size);
}

//----------------------------------------------------------------------------
/**
 *	
 *	@brief	OAMデータリスト分のキャラクタデータを作成
 *
 *	@param	bmp			ビットマップウィンドウデータ
 *	@param	pbuff		キャラクタデータバッファ
 *	@param	list		OAMデータリスト
 *	@param	draw_area	描画エリア
 *	@param	heap		使用するヒープ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void charSetOamDataList( const GF_BGL_BMPWIN* bmp, char* pbuff, const FONTOAM_OAM_DATA* list, int draw_area, int heap )
{
	FONTOAM_OAM_DATA* work;
	int count;		// カウンタ
	int char_min;	// キャラクタデータの最小単位
	int offs;
	GXOBJVRamModeChar  map_mode;
	
	// キャラクタデータの最小単位を計算
	if( draw_area == NNS_G2D_VRAM_TYPE_2DMAIN ){
		map_mode = GX_GetOBJVRamModeChar();
	}else{
		map_mode = GXS_GetOBJVRamModeChar();
	}
	char_min = CharModeMinNum( map_mode );

	offs = 0;
	work = list->next;
	while( work != list ){

		offs = charSetOamDataOne( bmp, work, pbuff, offs, char_min, map_mode, heap );
		work = work->next;
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	OAMデータ１つ分のキャラクタデータを作成
 *
 *	@param	bmp			ビットマップウィンドウデータ
 *	@param	oamdata		OAMデータ
 *	@param	pbuff		キャラクタバッファ
 *	@param	idx			インデックス
 *	@param	char_min_numキャラクタモードで設定されている最低のキャラクタサイズ
 *	@param	char_mode	マッピングモード
 *	@param	heap		使用するヒープ
 *
 *	@return	idx	次の格納先インデックス
 *
 *
 */
//-----------------------------------------------------------------------------
static int charSetOamDataOne( const GF_BGL_BMPWIN* bmp, const FONTOAM_OAM_DATA* oamdata, char* pbuff, int idx, int char_min_num, int char_mode, int heap )
{
	int buff_size;
	int oam_x, oam_y;	// oamサイズ

	oam_x = FONTOAM_PriTbl[ oamdata->oam_size ][ FONTOAM_PRI_X ];
	oam_y = FONTOAM_PriTbl[ oamdata->oam_size ][ FONTOAM_PRI_Y ]; 
	
	// oamサイズからキャラクタデータバッファを作成
	buff_size =  oam_x;
	buff_size *= oam_y;
	if( buff_size < char_min_num ){
		buff_size = char_min_num;
	}
	buff_size *= FONTOAM_CHAR_BYTE;
	
	// ローカルバッファにデータ代入
	FONTOAM_BmpCutOamSize( bmp, oam_x, oam_y, oamdata->x, oamdata->y, &pbuff[idx] );

	return (idx + buff_size);
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	このOAM郡を表示するのに必要なキャラクタデータサイズを取得
 *
 *	@param	list 
 *
 *	@return
 *
 *
 */
//-----------------------------------------------------------------------------
static int charAreaSizeOamDataList( const FONTOAM_OAM_DATA* list, int draw_area )
{
	FONTOAM_OAM_DATA* work;
	int char_min;	// キャラクタデータの最小単位
	GXOBJVRamModeChar  map_mode;
	int offs;
	int char_num;
	int oam_x, oam_y;	// oamサイズ
	
	// キャラクタデータの最小単位を計算
	if( draw_area == NNS_G2D_VRAM_TYPE_2DMAIN ){
		map_mode = GX_GetOBJVRamModeChar();
	}else{
		map_mode = GXS_GetOBJVRamModeChar();
	}
	char_min = CharModeMinNum( map_mode );

	offs = 0;
	work = list->next;
	while( work != list ){

		// キャラクタoamサイズからキャラクタ数を計算
		oam_x = FONTOAM_PriTbl[ work->oam_size ][ FONTOAM_PRI_X ];
		oam_y = FONTOAM_PriTbl[ work->oam_size ][ FONTOAM_PRI_Y ]; 
		
		char_num = oam_x * oam_y;
		if( char_num < char_min ){
			char_num = char_min;
		}
		
		offs += char_num * FONTOAM_CHAR_BYTE;
		
		work = work->next;
	}

	return offs;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	OAMデータリストのセルアクターを作成する
 *
 *	@param	font_init		フォント作成データ
 *	@param	list			OAMデータリスト先頭データ
 *	@param	img_proxy		イメージプロクシ配列データ
 *	@param	font_obj		フォントオブジェ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void addClActOamDataList( const FONTOAM_INIT* font_init, const FONTOAM_OAM_DATA* list, const NNSG2dImageProxy* img_proxy, FONTOAM_OBJ_PTR font_obj )
{
	FONTOAM_OAM_DATA* work;
	int count;

	count = 0;
	work = list->next;
	while( work != list ){
		
		font_obj->obj_w[ count ].clact = addClActOamDataOne( font_init, work, img_proxy + count );
		GF_ASSERT( font_obj->obj_w[ count ].clact );
		font_obj->obj_w[ count ].x = work->x * FONTOAM_CHAR_SIZE;
		font_obj->obj_w[ count ].y = work->y * FONTOAM_CHAR_SIZE;
		
		work = work->next;
		count++;
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	リストのセルアクター破棄
 *
 *	@param	fontoam 
 *
 *	@return
 *
 *
 */
//-----------------------------------------------------------------------------
static void delClActOamDataList( FONTOAM_OBJ_PTR fontoam )
{
	int i;		// ループ用

	for( i=0; i<fontoam->obj_num; i++ ){

		CLACT_Delete( fontoam->obj_w[ i ].clact );
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	１OAMのアクターを作成
 *
 *	@param	font_init	フォント作成データ
 *	@param	oamdata		OAMデータ
 *	@param	img_proxy	使用するイメージプロクシ
 *
 *	@return	作成したアクターポインタ
 *
 *
 */
//-----------------------------------------------------------------------------
static CLACT_WORK_PTR addClActOamDataOne( const FONTOAM_INIT* font_init, const FONTOAM_OAM_DATA* oamdata, const NNSG2dImageProxy* img_proxy )
{
	CLACT_ADD_SIMPLE	add;		// 登録データ
	CLACT_HEADER		head;		// ヘッダー

	// セルアクターヘッダー作成
	head.pImageProxy	= img_proxy;
	head.pCharData		= NULL;
	head.pPaletteProxy	= font_init->pltt;
	head.pCellBank		= font_init->fontoam_sys->pCellBank[ oamdata->oam_size ];
	head.pAnimBank		= NULL;
	head.pMCBank		= NULL;
	head.pMCABank		= NULL;

	head.flag			= 0;
	head.priority		= font_init->bg_pri;
	
	// 登録データ作成
	add.ClActSet		= font_init->clact_set;
	add.ClActHeader		= &head;
	add.pri				= font_init->soft_pri;
	add.DrawArea		= font_init->draw_area;
	add.heap			= font_init->heap;

	// 登録座標計算
	add.mat.x = 0;
	add.mat.y = 0;
	add.mat.z = 0;
	
	if( font_init->parent ){
		const VecFx32* parent_mat;			// 親座標
		parent_mat = CLACT_GetMatrix( font_init->parent );

		add.mat = *parent_mat;
	}
	add.mat.x	+= (font_init->x << FX32_SHIFT) + ((oamdata->x * FONTOAM_CHAR_SIZE) << FX32_SHIFT);
	add.mat.y	+= (font_init->y << FX32_SHIFT) + ((oamdata->y * FONTOAM_CHAR_SIZE) << FX32_SHIFT);

	// 登録
	return CLACT_AddSimple( &add );
}







//----------------------------------------------------------------------------
/**
 *
 *	@brief	OAMデータを作成
 *
 *	@param	heap	使用するヒープ
 *
 *	@return	OAMデータ
 *
 *
 */
//-----------------------------------------------------------------------------
static FONTOAM_OAM_DATA* makeOamList( int heap )
{
	FONTOAM_OAM_DATA* oamdata;

	oamdata = sys_AllocMemoryLo( heap, sizeof(FONTOAM_OAM_DATA) );
	GF_ASSERT_MSG( oamdata, "メモリオーバー" );

	oamdata->next = NULL;
	oamdata->prev = NULL;

	return oamdata;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	OAMデータメモリ解放
 *
 *	@param	oamdata OAMデータ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void destOamList( FONTOAM_OAM_DATA* oamdata )
{
	GF_ASSERT( oamdata );

	sys_FreeMemoryEz( oamdata );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	リストの全データ破棄
 *
 *	@param	dummy	ダミーデータ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void destOamListAll( FONTOAM_OAM_DATA* dummy )
{
	FONTOAM_OAM_DATA* work;
	FONTOAM_OAM_DATA* next;

	work = dummy->next;
	while( work != dummy ){
		next = work->next;
		destOamList( work );
		work = next;
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	リストに設定
 *
 *	@param	oamdata	OAMデータ
 *	@param	prev	前のデータ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void setOamList( FONTOAM_OAM_DATA* oamdata, FONTOAM_OAM_DATA* prev )
{
	oamdata->next		= prev->next;
	oamdata->prev		= prev;
	prev->next->prev	= oamdata;
	prev->next			= oamdata;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	oamデータをリストからはずす
 *
 *	@param	oamdata	OAMデータ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void resetOamList( FONTOAM_OAM_DATA* oamdata )
{
	oamdata->prev->next	= oamdata->next;
	oamdata->next->prev	= oamdata->prev;
}
