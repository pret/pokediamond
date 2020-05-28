//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *@file		clact_util.c
 *@brief	セルアクターの登録を簡単に行うシステム
 *@author	tomoya takahashi
 *@data		2005.09.02
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

#include "system.h"
#include "assert.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"


#include "include/system/render_oam.h"

#include "include/communication/wm_icon.h"

#include "include/gflib/char_manager.h"
#include "include/gflib/pltt_manager.h"

#define __CLACT_UTIL_H_GLOBAL
#include "include/system/clact_util.h"


//-----------------------------------------------------------------------------
/**
 *					定数宣言
*/
//-----------------------------------------------------------------------------
#define	CLACT_U_HEADER_DATA_NONE	(0xffffffff)	// 主にマルチセルの有無にしよう

//-----------------------------------------------------------------------------
/**
 *					構造体宣言
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	
//	ロムデータ一時読み込み用テーブル
//	
//=====================================
typedef struct {
	int char_id;		// キャラクタID
	int pltt_id;		// パレットID
	int cell_id;		// セルID
	int cellanm_id;		// セルアニメID
	int multicell_id;	// マルチセルID
	int multicellanm_id;// マルチセルアニメID
	int vram_trans;		// Vram転送フラグ
	int	priority;		// BG優先順位
} CLACT_HEADER_DATA_TMP;



//-----------------------------------------------------------------------------
/**
 *					プロトタイプ宣言
*/
//-----------------------------------------------------------------------------
static int getHeaderTblNum(char* buff);
static void loadHeaderTbl(char* buff, CLACT_HEADER_DATA_TMP* tbl, int num);
static void loadHeaderOne(char* buff, char** char_id, char** pltt_id, char** cell_id, char** cellanm_id, char** multicell_id, char** multicellanm_id, char** vram_trans, char** priority);
static void setHeaderOne(CLACT_HEADER_DATA_TMP* tbl, char* char_id, char* pltt_id, char* cell_id, char* cellanm_id, char* multicell_id, char* multicellanm_id, char* vram_trans, char* priority);

static char* makeStrCopy(const char* tmp, int heap);
static void	delStrCopy(char* data);


//----------------------------------------------------------------------------
/**
 *
 *@brief	セルアクターヘッダーを作成	（単体）
 *
 *@param	tbl					ヘッダーデータ格納先
 *@param	charID				キャラクタデータID
 *@param	plttID				パレットデータID
 *@param	cellID				セルデータID
 *@param	cellAnmID			セルアニメーションID"無いときはCLACT_U_HEADER_DATA_NONE"
 *@param	MultiID				マルチセルID		"無いときはCLACT_U_HEADER_DATA_NONE"
 *@param	MultiAnmID			マルチセルアニメID	"無いときはCLACT_U_HEADER_DATA_NONE"
 *@param	vram_trans			Vram転送かフラグ
 *@param	priority			BGとの優先順位
 *@param	charResMan			キャラクタデータが格納されてるリソースマネージャ
 *@param	plttResMan			パレットデータが格納されているリソースマネージャ
 *@param	cellResMan			セルデータが格納されているリソースマネージャ
 *@param	cellAnmResMan		セルアニメデータが格納されているリソースマネージャ
 *@param	multiCellResMan		マルチセルデータが格納されているリソースマネージャ
 *@param	multiCellAnmResMan	マルチセルアニメデータが格納されているリソースマネージャ
 *
 *@return	none
 *
 *
	 */
//-----------------------------------------------------------------------------
void CLACT_U_MakeHeader(CLACT_HEADER_PTR tbl, int charID, int plttID, int cellID,
		int cellAnmID, int MultiID, int MultiAnmID, int vram_trans, int priority,
		CLACT_U_RES_MANAGER_PTR charResMan,
		CLACT_U_RES_MANAGER_PTR plttResMan,
		CLACT_U_RES_MANAGER_PTR cellResMan,
		CLACT_U_RES_MANAGER_PTR cellAnmResMan,
		CLACT_U_RES_MANAGER_PTR multiCellResMan,
		CLACT_U_RES_MANAGER_PTR multiCellAnmResMan)
{
	CLACT_U_RES_OBJ_PTR char_o;
	CLACT_U_RES_OBJ_PTR pltt_o;
	CLACT_U_RES_OBJ_PTR cell_o;
	CLACT_U_RES_OBJ_PTR cellanm_o = NULL;
	CLACT_U_RES_OBJ_PTR multi_o = NULL;
	CLACT_U_RES_OBJ_PTR multianm_o = NULL;
	NNSG2dImageProxy*	img_prox;

	GF_ASSERT(charResMan);		// 必須リソースマネージャー
	GF_ASSERT(plttResMan);
	GF_ASSERT(cellAnmResMan);
	GF_ASSERT(cellResMan);
	GF_ASSERT(tbl);				// テーブルオブジェは確保済みか
	
	// 各データアクセス用オブジェクト作成
	char_o = CLACT_U_ResManagerGetIDResObjPtr( charResMan, charID );
	GF_ASSERT(char_o);
	pltt_o = CLACT_U_ResManagerGetIDResObjPtr( plttResMan, plttID );
	GF_ASSERT(pltt_o);
	cell_o = CLACT_U_ResManagerGetIDResObjPtr( cellResMan, cellID );
	GF_ASSERT(cell_o);
	
	// アニメデータはあるときのみ
	if( cellAnmResMan ){
		if( cellAnmID != CLACT_U_HEADER_DATA_NONE ){
			cellanm_o = CLACT_U_ResManagerGetIDResObjPtr( cellAnmResMan, cellAnmID );
			GF_ASSERT(cellanm_o);
		}
	}

	// マルチセルはリソースマネージャーがあるときのみ設定
	if(multiCellResMan != NULL){
		if(MultiID != CLACT_U_HEADER_DATA_NONE){
			multi_o = CLACT_U_ResManagerGetIDResObjPtr( multiCellResMan, MultiID );
		}
		if(MultiAnmID != CLACT_U_HEADER_DATA_NONE){
			multianm_o = CLACT_U_ResManagerGetIDResObjPtr( multiCellAnmResMan, MultiAnmID );
		}
	}
	
	// キャラクタマネージャーからプロクシを取得
	// Vram転送かチェック
	if(vram_trans){
		img_prox = CLACT_U_CharManagerGetVramTransferProxy(char_o, cell_o);
		GF_ASSERT(img_prox);
		
		// キャラクタデータ取得
		tbl->pCharData = CLACT_U_ResManagerGetResObjResChar(char_o);
	}else{
		img_prox = CLACT_U_CharManagerGetProxy(char_o);
		GF_ASSERT(img_prox);

		tbl->pCharData = NULL;	// Vram転送以外ではいらない
	}
	// パレットプロクシを取得
	tbl->pPaletteProxy = CLACT_U_PlttManagerGetProxy(pltt_o,img_prox);
	tbl->pImageProxy = img_prox;

	// セルデータバンク
	tbl->pCellBank = CLACT_U_ResManagerGetResObjResCell(cell_o);

	// セルアニメデータバンク
	if(cellanm_o){
		tbl->pAnimBank = CLACT_U_ResManagerGetResObjResCellAnm(cellanm_o);	
	}else{
		tbl->pAnimBank = NULL;
	}

	// マルチセルデータを取得する必要があるかチェック
	if(multi_o){
		// マルチセルデータバンク
		tbl->pMCBank = CLACT_U_ResManagerGetResObjResMultiCell(multi_o);
		// マルチセルアニメデータバンク
		tbl->pMCABank = CLACT_U_ResManagerGetResObjResMultiCellAnim(multianm_o);
	}else{
		// マルチセルデータバンク
		tbl->pMCBank = NULL;
		// マルチセルアニメデータバンク
		tbl->pMCABank = NULL;
	}

	// 転送フラグ
	tbl->flag = vram_trans;

	// BG表示優先順位
	tbl->priority = priority;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	ヘッダーのメモリを解放する前に、ヘッダー内のデータで確保したメモリを破棄する
 *
 *@param	tbl		中身のデータを破棄するヘッダー
 *
 *@return	none
 *
 * Vram転送用に確保したVram領域を破棄する
 *
 */
//-----------------------------------------------------------------------------
void CLACT_U_DeleteInHeaderVramTransferArea(CLACT_HEADER_PTR tbl)
{
	// Vram転送モードの時はVram領域を開放する
	CLACT_U_CharManagerDeleteVramTransferProxy(tbl->pImageProxy);

	// テーブル内をcleanする
	memset(tbl, 0, sizeof(CLACT_HEADER));
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	セルアクターヘッダーテーブルをロムから読み込む	（複数）
 *
 *@param	path				パス
 *@param	heap				ヒープ
 *@param	charResMan			キャラクタデータが格納されてるリソースマネージャ
 *@param	plttResMan			パレットデータが格納されているリソースマネージャ
 *@param	cellResMan			セルデータが格納されているリソースマネージャ
 *@param	cellAnmResMan		セルアニメデータが格納されているリソースマネージャ
 *@param	multiCellResMan		マルチセルデータが格納されているリソースマネージャ
 *@param	multiCellAnmResMan	マルチセルアニメデータが格納されているリソースマネージャ
 *
 *@return	CLACT_HEADER_TBL_PTR	ヘッダーのテーブルを格納した構造体のポインタ
 *									アクセス関数で個々のヘッダーを取得することが出来ます。
 *
 *
 */
//-----------------------------------------------------------------------------
CLACT_HEADER_TBL_PTR CLACT_U_LoadHeaderTbl(
		const char* path, int heap,
		CLACT_U_RES_MANAGER_PTR charResMan,
		CLACT_U_RES_MANAGER_PTR plttResMan,
		CLACT_U_RES_MANAGER_PTR cellResMan,
		CLACT_U_RES_MANAGER_PTR cellAnmResMan,
		CLACT_U_RES_MANAGER_PTR multiCellResMan,
		CLACT_U_RES_MANAGER_PTR multiCellAnmResMan)
{
	int i;					// ループ用
	char* buff;				// 作業用バッファ
	char* tmp;				// 読み込み済みファイル	
	int tbl_num;			// テーブル数
	CLACT_HEADER_TBL_PTR	ret_tbl;	// セルアクターヘッダーテーブル
	CLACT_HEADER_DATA_TMP*	data_tmp;	// データ一時保存領域

	// ファイル読み込み
	tmp = sys_LoadFile(heap, path);
	GF_ASSERT(tmp);

	// テーブル数を取得
	buff = makeStrCopy(tmp, heap);
	tbl_num = getHeaderTblNum(buff);
	delStrCopy(buff);

	// セルアクターヘッダーテーブル作成
	ret_tbl = sys_AllocMemory(heap, sizeof(CLACT_HEADER_TBL));
	GF_ASSERT(ret_tbl);
	
	if(tbl_num > 0){
		ret_tbl->tbl = sys_AllocMemory(heap, sizeof(CLACT_HEADER)*tbl_num);
		GF_ASSERT(ret_tbl->tbl);
	}else{
		ret_tbl->tbl = NULL;
	}
	
	ret_tbl->tbl_num = tbl_num;	// テーブル数

	// 一時データ読み込みようテーブル作成
	if(tbl_num > 0){
		data_tmp = sys_AllocMemoryLo(heap, sizeof(CLACT_HEADER_DATA_TMP)* tbl_num);
		GF_ASSERT(data_tmp);
	}else{
		data_tmp = NULL;
	}
	
	// ROMヘッダーデータ読み込み
	if(data_tmp != NULL){
		buff = makeStrCopy(tmp, heap);
		loadHeaderTbl(buff, data_tmp, tbl_num);
		delStrCopy(buff);
	}

	// 今一時データ保存領域に読みこんだデータでセルアクターヘッダーを作成する
	for(i=0;i<ret_tbl->tbl_num;i++){
		CLACT_U_MakeHeader(ret_tbl->tbl + i, 
				data_tmp[i].char_id, data_tmp[i].pltt_id,
				data_tmp[i].cell_id, data_tmp[i].cellanm_id,
				data_tmp[i].multicell_id, data_tmp[i].multicellanm_id,
				data_tmp[i].vram_trans, data_tmp[i].priority,
				charResMan, plttResMan, cellResMan, cellAnmResMan, 
				multiCellResMan, multiCellAnmResMan);
	}

	// 	一時ファイル破棄
	if(data_tmp){
		sys_FreeMemoryEz(data_tmp);
	}

	// 読み込みファイル破棄
	sys_FreeMemoryEz(tmp);

	return ret_tbl;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	セルアクターヘッダーテーブルをバイナリデータから作成	（複数）
 *
 *@param	bindata				バイナリデータ
 *@param	p_header_tbl		ヘッダーテーブル
 *@param	heap				ヒープ
 *@param	charResMan			キャラクタデータが格納されてるリソースマネージャ
 *@param	plttResMan			パレットデータが格納されているリソースマネージャ
 *@param	cellResMan			セルデータが格納されているリソースマネージャ
 *@param	cellAnmResMan		セルアニメデータが格納されているリソースマネージャ
 *@param	multiCellResMan		マルチセルデータが格納されているリソースマネージャ
 *@param	multiCellAnmResMan	マルチセルアニメデータが格納されているリソースマネージャ
 *
 *@return	CLACT_HEADER_TBL_PTR	ヘッダーのテーブルを格納した構造体のポインタ
 *									アクセス関数で個々のヘッダーを取得することが出来ます。
 *
 * バイナリデータ書式		各データ2byteずつの配置となっています。
 *	キャラクタID,		（リソースマネージャーと関連付けされたID）
 *	パレットID,
 *	セルID,
 *	セルアニメID,
 *	マルチセルID,		（マルチセル、マルチセルアニメが無いときは'CLACT_U_HEADER_MAKE_NONE_CODE'）
 *	マルチセルアニメID,
 *	Vram転送アニメ確認フラグ,
 *	BG面との優先度
 *	次のテーブルを書く↓
 *	0x0000,0x0001,0x0000,0x0002,CLACT_U_HEADER_MAKE_NONE_CODE, CLACT_U_HEADER_MAKE_NONE_CODE, 0,0			<-１つのデータ
 *	0x0001,0x0002,0x0003,0x0002,0x0000,0x0000,0x0001,0x0002
 *	終了コード
 *	CLACT_U_HEADER_MAKE_END_CODE, CLACT_U_HEADER_MAKE_END_CODE, CLACT_U_HEADER_MAKE_END_CODE, CLACT_U_HEADER_MAKE_END_CODE, CLACT_U_HEADER_MAKE_END_CODE, CLACT_U_HEADER_MAKE_END_CODE, CLACT_U_HEADER_MAKE_END_CODE, CLACT_U_HEADER_MAKE_END_CODE			このデータが出てきたら終了	
 *
 */
//-----------------------------------------------------------------------------
CLACT_HEADER_TBL_PTR CLACT_U_MakeHeaderBinary(const CLACT_U_HEADER_MAKE_BINDATA* bindata,
		int heap,
		CLACT_U_RES_MANAGER_PTR charResMan,
		CLACT_U_RES_MANAGER_PTR plttResMan,
		CLACT_U_RES_MANAGER_PTR cellResMan,
		CLACT_U_RES_MANAGER_PTR cellAnmResMan,
		CLACT_U_RES_MANAGER_PTR multiCellResMan,
		CLACT_U_RES_MANAGER_PTR multiCellAnmResMan)
{
	int i;					// ループ用
	int tbl_num;			// テーブル数
	CLACT_HEADER_TBL_PTR p_header_tbl;	// ヘッダーテーブル
	int multicell, multicell_anm;

	// バイナリデータのテーブル数を求める
	tbl_num = 0;
	while( bindata[ tbl_num ].char_id != CLACT_U_HEADER_MAKE_END_CODE ){
		tbl_num ++;
	}

	// テーブル作成
	p_header_tbl			= sys_AllocMemory( heap, sizeof(CLACT_HEADER_TBL) );
	p_header_tbl->tbl		= sys_AllocMemory( heap, sizeof(CLACT_HEADER) * tbl_num );
	p_header_tbl->tbl_num	= tbl_num;
	

	for(i=0;i<p_header_tbl->tbl_num;i++){

		CLACT_U_MakeHeader(p_header_tbl->tbl + i, 
				bindata[i].char_id, bindata[i].pltt_id,
				bindata[i].cell_id, bindata[i].cellanime_id,
				bindata[i].multicell_id, bindata[i].multicellanime_id,
				bindata[i].vram_trans, bindata[i].bg_priority,
				charResMan, plttResMan, cellResMan, cellAnmResMan, 
				multiCellResMan, multiCellAnmResMan);
	}

	return p_header_tbl;
}


//----------------------------------------------------------------------------
/**
 *
 *@brief	ヘッダーテーブルを破棄する
 *
 *@param	data	ヘッダーテーブル
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void CLACT_U_CLACT_HeaderTblDelete(CLACT_HEADER_TBL_PTR data)
{
	GF_ASSERT(data);
	
	if(data->tbl){
		sys_FreeMemoryEz(data->tbl);
	}
	sys_FreeMemoryEz(data);
}


//----------------------------------------------------------------------------
/**
 *
 *@brief	セルアクターセットの簡単初期化
 *
 *@param	work_num	セルアクターに設定する最大アクター数
 *@param	data		セルアクター簡単設定に使用するレンダーデータ
 *						(実態のポインタ)
 *@param	heap		メモリ確保に使用するヒープ数
 *
 *@return	CLACT_SET_PTR	作成されたセルアクターセット
 *
 * 内容
 * ●レンダラの初期化、サーフェースの設定などを行う
 * ●セルアクターセット作成
 * ●セルアクターセットに初期化したレンダラを設定
 *
 * 破棄は普通のセルアクターの破棄関数で大丈夫です。
 *
 */
//-----------------------------------------------------------------------------
CLACT_SET_PTR CLACT_U_SetEasyInit( int work_num, CLACT_U_EASYRENDER_DATA* data, int heap )
{
	CLACT_SETDATA	set;
	NNSG2dViewRect rect;
	
	RNDP_InitRenderer(&data->Rend, -FX32_ONE);
	
	// サーフェース登録
	// メイン用サーフェース
	rect.posTopLeft.x	= MAIN_SURFACE_X;
	rect.posTopLeft.y	= MAIN_SURFACE_Y;
	rect.sizeView.x		= SURFACE_WIDTH;
	rect.sizeView.y		= SURFACE_HEIGHT;
	REND_OAM_SetSurface(&data->surface[0],
			&rect,
			NNS_G2D_SURFACETYPE_MAIN2D,
			&data->Rend);
	
	// サブ用サーフェース
	rect.posTopLeft.x	= SUB_SURFACE_X;
	rect.posTopLeft.y	= SUB_SURFACE_Y;
	rect.sizeView.x		= SURFACE_WIDTH;
	rect.sizeView.y		= SURFACE_HEIGHT;
	REND_OAM_SetSurface(&data->surface[1],
			&rect,
			NNS_G2D_SURFACETYPE_SUB2D,
			&data->Rend);
	set.WorkNum = work_num;
	set.pRender	= &data->Rend;
	set.heap	= heap;
	
	return CLACT_InitSet( &set );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	レンダラー内	メイン画面のサーフェース位置を設定
 *
 *	@param	data	簡単セルアクターセット用レンダラデータ
 *	@param	x		メイン画面サーフェースｘ座標
 *	@param	y		メイン画面サーフェースｙ座標
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void CLACT_U_SetMainSurfaceMatrix( CLACT_U_EASYRENDER_DATA* data, fx32 x, fx32 y )
{
	NNSG2dViewRect rect;
	
	rect.posTopLeft.x	= x;
	rect.posTopLeft.y	= y;
	rect.sizeView.x		= SURFACE_WIDTH;
	rect.sizeView.y		= SURFACE_HEIGHT;
	
	RNDP_SetSurfaceRect( &data->surface[ 0 ], &rect );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	レンダラー内	サブ画面のサーフェース位置を設定
 *
 *	@param	data	簡単セルアクターセット用レンダラデータ
 *	@param	x		サブ画面サーフェースｘ座標
 *	@param	y		サブ画面サーフェースｙ座標
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void CLACT_U_SetSubSurfaceMatrix( CLACT_U_EASYRENDER_DATA* data, fx32 x, fx32 y )
{
	NNSG2dViewRect rect;
	
	rect.posTopLeft.x	= x;
	rect.posTopLeft.y	= y;
	rect.sizeView.x		= SURFACE_WIDTH;
	rect.sizeView.y		= SURFACE_HEIGHT;
	
	RNDP_SetSurfaceRect( &data->surface[ 1 ], &rect );
}

//----------------------------------------------------------------------------
/**
 *	@brief	通信アイコンのキャラクタデータ使用領域を予約
 *
 *	@param	disp	設定画面	
 *	@param	mode	オブジェマッピングﾓｰﾄﾞ
 *	@return	none
 *
 *	disp
 *		main画面：NNS_G2D_VRAM_TYPE_2DMAIN = 1
 *		sub画面 ：NNS_G2D_VRAM_TYPE_2DSUB = 2
 *
 *	mode
 *		GX_OBJVRAMMODE_CHAR_1D_32K 
 *		GX_OBJVRAMMODE_CHAR_1D_64K 
 *
 */
//-----------------------------------------------------------------------------
void CLACT_U_WmIcon_SetReserveAreaCharManager( u32 disp, GXOBJVRamModeChar mode )
{
	switch( mode ){
	case GX_OBJVRAMMODE_CHAR_1D_32K:
        if((GX_GetBankForOBJ() == GX_VRAM_OBJ_16_G) || (GX_GetBankForOBJ() == GX_VRAM_OBJ_16_F)){
            SetReserveAreaContCharManager( WM_ICON_CHAR_OFFSET16, 16*32, disp );
        }
        else{
            SetReserveAreaContCharManager( WM_ICON_CHAR_OFFSET32, 16*32, disp );
        }
		break;

	case GX_OBJVRAMMODE_CHAR_1D_64K:
		SetReserveAreaContCharManager( WM_ICON_CHAR_OFFSET64, 16*32, disp );
		break;

	case GX_OBJVRAMMODE_CHAR_1D_128K:
        if((GX_GetBankForOBJ() == GX_VRAM_OBJ_80_EF) || (GX_GetBankForOBJ() == GX_VRAM_OBJ_80_EG)){
			SetReserveAreaContCharManager( WM_ICON_CHAR_OFFSET80, 16*32, disp );
		}else{
			SetReserveAreaContCharManager( WM_ICON_CHAR_OFFSET128, 16*32, disp );
		}
		break;

	default:
		// そのオブジェマッピングﾓｰﾄﾞには対応していません
		GF_ASSERT(0);
		break;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	通信アイコンのパレットデータ使用領域を予約
 *
 *	@param	none
 *	@return	none
 */
//-----------------------------------------------------------------------------
#define CLACT_U_WMICON_PLTT_USE_MSK		(PLTTMAN_RESERVE_PLT14|PLTTMAN_RESERVE_PLT15)
void CLACT_U_WmIcon_SetReserveAreaPlttManager( u32 disp )
{
	SetReserveCleanAreaPlttManager( CLACT_U_WMICON_PLTT_USE_MSK, disp );
}




//----------------------------------------------------------------------------
/**
 *
 *@brief	ヘッダーテーブル数を取得
 *
 *@param	buff	バッファ
 *
 *@return
 *
 *
 */
//-----------------------------------------------------------------------------
static int getHeaderTblNum(char* buff)
{
	int count;		// テーブル数カウンタ
	char* data[8];
	
	count = 0;
	loadHeaderOne(buff, &data[0], &data[1], &data[2], &data[3], &data[4], &data[5], &data[6], &data[7] );

	// 'e'が出てきたらテーブル終了
	while(data[0][0] != 'e'){
		count ++;
		loadHeaderOne(NULL, &data[0], &data[1], &data[2], &data[3], &data[4], &data[5], &data[6], &data[7] );
	}

	return count;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	ヘッダーテーブルを読み込む
 *
 *@param	buff	データ
 *@param	tbl		格納先
 *@param	num		格納数
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void loadHeaderTbl(char* buff, CLACT_HEADER_DATA_TMP* tbl, int num)
{
	int	i;			// ループ用
	char* data[8];	// 格納用データ
	
	// 読み込んでテーブルに格納
	loadHeaderOne(buff, &data[0], &data[1], &data[2], &data[3],
			&data[4], &data[5], &data[6], &data[7] );
	
	setHeaderOne(tbl, data[0], data[1], data[2], data[3],
			data[4], data[5], data[6], data[7] );

	for(i=1;i<num;i++){
		loadHeaderOne(NULL, &data[0], &data[1], &data[2], &data[3],
				&data[4], &data[5], &data[6], &data[7] );
		setHeaderOne(tbl + i, data[0], data[1], data[2], data[3],
				data[4], data[5], data[6], data[7] );
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	ヘッダー１つのデータを取得
 *
 *@param	buff			バッファ
 *@param	char_id			キャラクタID格納先
 *@param	pltt_id			パレットID格納先
 *@param	cell_id			セルID格納先
 *@param	cellanm_id		セルアニメID格納先
 *@param	multicell_id	マルチセルID格納先
 *@param	multicellanm_id	マルチセルアニメID格納先
 *@param	vram_trans		Vram転送確認フラグ格納先
 *@param	priority		BG面との表示優先順位格納先
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void loadHeaderOne(char* buff, char** char_id, char** pltt_id, char** cell_id, char** cellanm_id, char** multicell_id, char** multicellanm_id, char** vram_trans, char** priority)
{
	*char_id	= strtok(buff, ",");
	*pltt_id	= strtok(NULL, ",");
	*cell_id	= strtok(NULL, ",");
	*cellanm_id	= strtok(NULL, ",");
	*multicell_id	= strtok(NULL, ",");
	*multicellanm_id= strtok(NULL, ",");
	*vram_trans	= strtok(NULL, ",");
	*priority	= strtok(NULL, ",");
	strtok(NULL, "\n");
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	テーブルにデータを設定する
 *
 *@param	tbl					データ格納先
 *@param	char_id				キャラクタID
 *@param	pltt_id				パレットID
 *@param	cell_id				セルID
 *@param	cellanm_id			セルアニメID
 *@param	multicell_id		マルチセルID
 *@param	multicellanm_id		マルチセルアニメID
 *@param	vram_trans			Vram転送確認フラグ
 *@param	priority			BG面との表示優先順位
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void setHeaderOne(CLACT_HEADER_DATA_TMP* tbl, char* char_id, char* pltt_id, char* cell_id, char* cellanm_id, char* multicell_id, char* multicellanm_id, char* vram_trans, char* priority)
{
	tbl->char_id		= atoi(char_id);
	tbl->pltt_id		= atoi(pltt_id);
	tbl->cell_id		= atoi(cell_id);
	tbl->cellanm_id		= atoi(cellanm_id);
	if(multicell_id[0] != 'n'){
		tbl->multicell_id	= atoi(multicell_id);
		tbl->multicellanm_id = atoi(multicellanm_id);
	}else{
		tbl->multicell_id	 = CLACT_U_HEADER_DATA_NONE; 
		tbl->multicellanm_id = CLACT_U_HEADER_DATA_NONE;
	}
	tbl->vram_trans		= atoi(vram_trans);
	tbl->priority		= atoi(priority);
	
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	コピーを作成
 *
 *@param	tmp		コピーデータ
 *@param	heap	使用ヒープ
 *
 *@return	char* 作成データ
 *
 *
 */
//-----------------------------------------------------------------------------
static char* makeStrCopy(const char* tmp, int heap)
{
	int len;
	char* copy;
	
	len = strlen(tmp);
	len++;

	copy = sys_AllocMemoryLo(heap, len);
	strcpy(copy, tmp);

	return copy;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	makeStrCopyで作成したデータ破棄
 *
 *@param	data	破棄データ
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void	delStrCopy(char* data)
{
	sys_FreeMemoryEz(data);
}

