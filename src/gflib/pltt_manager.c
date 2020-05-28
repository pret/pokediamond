//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *	@file		pltt_manager.c
 *	@brief		パレットマネージャーの実態部
 *	@author		tomoya takahashi
 *	@data		2004.11.22
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]*/

#include "system.h"
#define PLTT_MANAGER_H_GLOBAL
#include "pltt_manager.h"
#include "gflib_os_print.h"
#include "assert.h"
#include "vram_transfer_manager.h"
#include <string.h>


//-----------------------------------------------------------------------------
/**
 *					定数宣言
 */
//-----------------------------------------------------------------------------

#define		PLTT_ONE_SIZE	(32)			// １６色パレット１つのサイズ
#define		PLTT_AREA_NONE	(0xffffffff)	// パレット用エリアなし

#define		PLTT_EX_SIZE	(32*16*16)		// 拡張パレットサイズ
#define		PLTT_NORMAL_SIZE (32*16)		// 標準パレットサイズ

#define		PLT_DATA_ID_NONE	(0xffffffff)

//----------------------------------------------------------------------------
/**
 *					構造体宣言
 */
//----------------------------------------------------------------------------
//-------------------------------------
///	パレットデータテーブル
//
typedef struct
{
	NNSG2dPaletteData*	pPlttData;			// パレットデータ構造体(大本データの保持)
	NNS_G2D_VRAM_TYPE	type;				// VramType
											// mainに登録：NNS_G2D_VRAM_TYPE_2DMAIN = 1
											// subに登録 ：NNS_G2D_VRAM_TYPE_2DSUB = 2
											// 両方に登録：NNS_G2D_VRAM_TYPE_2DMAX = 3
	u32			load_size;					// 読み込みサイズ
	u32			act_num;					// 登録　識別ID
	NNSG2dImagePaletteProxy	PaletteProxy;	// イメージプロクシ	
	u32			offset;						// 自分のベースアドレス
	u32			sub_offset;					// 自分のベースアドレス
	u8			flag;						// 使用しているかのフラグ
} PLTT_DATA_TBL;


//-------------------------------------
//
//	パレットマネージャー構造体	
//
//=====================================
typedef struct{
	PLTT_DATA_TBL*	plttDataTbl;					// パレットデータテーブル
	int				plttDataNum;					// パレットデータ数
	int				plttDataNow;					// 今のパレット読み込み数
	u32				Offset;							// 読み込み時のオフセット
	u32				SubOffset;						// サブVramのオフセット
	u32				OffsetEx;						// 拡張パレットオフセット
	u32				SubOffsetEx;					// サブの拡張パレットオフセット
	u32				MainExPlttVramSize;				// メインの拡張パレットVramサイズ
	u32				SubExPlttVramSize;				// サブの拡張パレットVramサイズ
	u16				main16VramArea;					// メインの１６色Vramエリア
	u16				sub16VramArea;					// サブの１６色Vramエリア
}PLTT_MANAGER_DATA;


//----------------------------------------------------------------------------
/**
 *					プロトタイプ宣言
 */
//-----------------------------------------------------------------------------
static void cleanPlttData(PLTT_DATA_TBL* data);						// パレットデータ初期化
static BOOL TransPlttData(const PLTT_MANAGER_HEADER* pPlttData, PLTT_DATA_TBL* tbl);							// パレットデータ転送
static BOOL TransPlttDataCleanVram(const PLTT_MANAGER_HEADER* pPlttData, PLTT_DATA_TBL* tbl);							// パレットデータ転送
static BOOL LoadPlttData(const PLTT_MANAGER_HEADER* pPlttData, PLTT_DATA_TBL* tbl);		// パレットデータ読み込み
static void setTransPltt( PLTT_DATA_TBL* pPlttData );
static void transVramPltt( void* p_data );		// パレット
static void setVramPlttSize( void );			// Vramのサイズをセット
static void dellPlttData( PLTT_DATA_TBL* pPlttData );	// パレットデータを破棄する
static PLTT_DATA_TBL* getPlttDataPtr( int id );	// IDのパレットデータ取得
static PLTT_DATA_TBL* getPlttDataClean( void );	// 空いているパレットデータ取得

// 転送エリアの設定
static void transAreaSet( u16* data, int num, int start );
static void transAreaClean( u16* data, int num, int start );
static int transAreaCheck( u16 data, int num );
static void transAreaInit( PLTT_MANAGER_DATA* data );
static void transAreaSetTbl( PLTT_DATA_TBL* data );
static void transAreaCleanTbl( PLTT_DATA_TBL* data );

// オフセット移動の時の転送エリア取得
static BOOL transAreaCheckOffset( PLTT_DATA_TBL* data, u32 m_offs, u32 s_offs, u32 m_limit, u32 s_limit );
static void transAreaSetOffset( PLTT_DATA_TBL* data, u32* m_offs, u32* s_offs );


// グローバル変数
static PLTT_MANAGER_DATA* PlttManagerData = NULL;
// 後々全関数はこのデータのポインタを引数にするように変更を行う
// 今はこのデータをどこで保持すればよいのかわからないため、
// 自分で持つ



//----------------------------------------------------------------------------
/**
 *
 *@brief	パレットマネージャー初期化
 *
 *@param	none
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void InitPlttManager(int PlttDataNum, int heap)
{
	int i;
	
	// パレットマネージャーシステムのデータを作成
	if(PlttManagerData == NULL){
		PlttManagerData = sys_AllocMemory(heap, sizeof(PLTT_MANAGER_DATA));
		MI_CpuClear32(PlttManagerData, sizeof(PLTT_MANAGER_DATA));
		
		PlttManagerData->plttDataNum = PlttDataNum;	// 管理パレット数を代入

		// パレット管理数分の管理領域を作成
		PlttManagerData->plttDataTbl = sys_AllocMemory(heap, sizeof(PLTT_DATA_TBL)*PlttDataNum);
		
		for(i=0;i<PlttDataNum;i++){	
			cleanPlttData(PlttManagerData->plttDataTbl + i);
		}
		
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	CleanArea関数使用禁止パレット設定
 *
 *	@param	msk		使用禁止パレットマスク
 *	@param	disp	画面
 *
 *	@return	none
 *
 *	disp
 *		mainに登録：NNS_G2D_VRAM_TYPE_2DMAIN = 1
 *		subに登録 ：NNS_G2D_VRAM_TYPE_2DSUB = 2
 *
 *	マスク定数
	// パレットVRAM予約マスク
	PLTTMAN_RESERVE_PLT0  =1 << 0,	
	PLTTMAN_RESERVE_PLT1  =1 << 1,	
	PLTTMAN_RESERVE_PLT2  =1 << 2,	
	PLTTMAN_RESERVE_PLT3  =1 << 3,	
	PLTTMAN_RESERVE_PLT4  =1 << 4,	
	PLTTMAN_RESERVE_PLT5  =1 << 5,	
	PLTTMAN_RESERVE_PLT6  =1 << 6,	
	PLTTMAN_RESERVE_PLT7  =1 << 7,	
	PLTTMAN_RESERVE_PLT8  =1 << 8,	
	PLTTMAN_RESERVE_PLT9  =1 << 9,	
	PLTTMAN_RESERVE_PLT10  =1 << 10,	
	PLTTMAN_RESERVE_PLT11  =1 << 11,	
	PLTTMAN_RESERVE_PLT12  =1 << 12,	
	PLTTMAN_RESERVE_PLT13  =1 << 13,	
	PLTTMAN_RESERVE_PLT14  =1 << 14,	
	PLTTMAN_RESERVE_PLT15  =1 << 15,	


 *	通信用OAM表示用パレット領域の確保などに使用してください。
 *
 *	＊使用上注意
	GLOBAL void PlttLoadStartAll( void );
	GLOBAL void PlttLoadStart( u32 start_offset );
	GLOBAL void PlttLoadStartSub( u32 start_offset );
	GLOBAL void PlttLoadStartEx( u32 start_offset );
	GLOBAL void PlttLoadStartSubEx( u32 start_offset );
 *	を使用した後にこの設定をしてください。
 *	上の５つの関数の中で、禁止領域の初期化を行ってしまいます
 */
//-----------------------------------------------------------------------------
void SetReserveCleanAreaPlttManager( u16 msk, u32 disp )
{
	if( disp == NNS_G2D_VRAM_TYPE_2DMAIN ){
		PlttManagerData->main16VramArea |= msk;
	}else if( disp == NNS_G2D_VRAM_TYPE_2DSUB ){
		PlttManagerData->sub16VramArea |= msk;
	}
}


//----------------------------------------------------------------------------
/**
 *
 *@brief	パレットマネージャー破棄
 *
 *@param	none
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void DeletePlttManager(void)
{
	if(PlttManagerData != NULL){
		DelPlttAll();		// 全パレットデータを破棄
		sys_FreeMemoryEz(PlttManagerData->plttDataTbl);	// パレット管理領域を破棄
		sys_FreeMemoryEz(PlttManagerData);				// パレットマネージャーシステム領域を破棄
		PlttManagerData = NULL;
	}
}

/*-----------------------------------------------------------------------------
 *
 *					
 *
 *	引数
 *		
 *
 *	戻り値
 *		
 *					
 *
 ----------------------------------------------------------------------------*/
static void now_debug_draw( void )
{
#ifdef PLTT_MANAGER_OS_PRINTF_ON
	OS_Printf( "今のオフセット\n" );
	OS_Printf( "メイン[%d] サブ[%d]\n", PlttManagerData->Offset, PlttManagerData->SubOffset );
	OS_Printf( "拡張メイン[%d] 拡張サブ[%d]\n", PlttManagerData->OffsetEx, PlttManagerData->SubOffsetEx );
#endif
}
//----------------------------------------------------------------------------
/**
 *
 *@brief	ロードを開始する関数
 *
 *@param	start_offset：読み込み開始offset
 *
 *@return	none
 *	(内部管理のオフセットを初期化)
 */
//-----------------------------------------------------------------------------
/// メイン画面　標準パレット
void PlttLoadStart( u32 start_offset )
{
	PlttManagerData->Offset = start_offset;
	setVramPlttSize();

	transAreaInit( PlttManagerData );
}
/// サブ画面　標準パレット
void PlttLoadStartSub( u32 start_offset )
{
	PlttManagerData->SubOffset = start_offset;
	setVramPlttSize();
	transAreaInit( PlttManagerData );
}

/// メイン画面　拡張パレット
void PlttLoadStartEx( u32 start_offset )
{
	PlttManagerData->OffsetEx = start_offset;
	setVramPlttSize();
	transAreaInit( PlttManagerData );
}

/// サブ画面　拡張パレット
void PlttLoadStartSubEx( u32 start_offset )
{
	PlttManagerData->SubOffsetEx = start_offset;
	setVramPlttSize();
	transAreaInit( PlttManagerData );
}


//----------------------------------------------------------------------------
/**
 *
 *	@brief	パレットが管理している内部オフセット値を取得する
 *
 *	@param	none 
 *
 *	@return	int		オフセット値
 *
 *
 */
//-----------------------------------------------------------------------------
/// メイン画面　標準パレット
int PlttLoadOffsetGetMain( void )
{
	return PlttManagerData->Offset;
}
/// サブ画面　標準パレット
int PlttLoadOffsetGetSub( void )
{
	return PlttManagerData->SubOffset;
}

/// メイン画面　拡張パレット
int PlttLoadOffsetGetMainEx( void )
{
	return PlttManagerData->OffsetEx;
}

/// サブ画面　拡張パレット
int PlttLoadOffsetGetSubEx( void )
{
	return PlttManagerData->SubOffsetEx;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	ロードを開始する関数
 *							全てを０で初期化する
 *
 *@param	none	
 *
 *@return	none
 *					(内部管理のオフセットを初期化)
 *
 */
//-----------------------------------------------------------------------------
void PlttLoadStartAll( void )
{
	PlttManagerData->Offset			= 0;					// 読み込み時のオフセット
	PlttManagerData->SubOffset		= 0;					// サブVramのオフセット
	PlttManagerData->OffsetEx		= 0;					// 拡張パレットオフセット
	PlttManagerData->SubOffsetEx	= 0;					// サブの拡張パレットオフセット
	setVramPlttSize();										// VramBankの割り当てからVramを使用できる量を計算
	transAreaInit( PlttManagerData );
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	パレットデータ単体をセットしてロード
 *
 *@param	pPlttData：パレットデータ
 *
 *@retval	TRUE ：セットできた
 *@retval	FALSE：セットできなかった
 *
 */
//-----------------------------------------------------------------------------
BOOL PlttSet( const PLTT_MANAGER_HEADER* pPlttData )
{
	PLTT_DATA_TBL* tbl;

	// 空いているテーブルを取得
	tbl = getPlttDataClean();

	// テーブル数が足りたかチェック
	if( tbl == NULL ){
		GF_ASSERT(0&&("テーブルが一杯で登録できません"))
		return FALSE;		// 登録不可能
	}
	
	// パレットデータ読み込み
	if(LoadPlttData(pPlttData, tbl) == FALSE){
		return FALSE;
	}
		

	// パレットデータ転送
	if( TransPlttData(pPlttData, tbl) == FALSE ){
		//失敗したときは破棄
		//失敗したとき＝Vramにあまりのサイズがない
		DelPltt( pPlttData->id );
		return FALSE;
	}

	// Vramエリア設定
	transAreaSetTbl( tbl );

	return TRUE;
}



//----------------------------------------------------------------------------
/**
 *
 *@brief	パレットデータを複数セット
 *
 *@param	pPlttData：パレットデータ
 *@param	num			セット数
 *
 *@return	いくつ登録成功したか
 *
 */
//-----------------------------------------------------------------------------
u16 PlttSets( const PLTT_MANAGER_HEADER* pPlttData, int num )
{
	int i;			// ループ用
	
	//
	// PLTT_ENDがくるまで読み込む
	//
	for(i=0;i<num;i++){
		// 読み込み＆セット処理
		if( PlttSet( pPlttData + i ) == FALSE ){
			// 失敗
			break;
		}
	}

	return i;
}


// ビットをチェックして
// 今空いている場所に転送します。
// OFFSET指定して転送したいときは上の転送関数を使用してください
//----------------------------------------------------------------------------
/**
 *@brief	パレットデータ単体をセットしてロード
 *
 *@param	pPlttData：パレットデータ
 *
 *@retval	TRUE ：セットできた
 *			FALSE：セットできなかった
 */
//-----------------------------------------------------------------------------
BOOL PlttSetCleanArea( const PLTT_MANAGER_HEADER* pPlttData )
{
	PLTT_DATA_TBL* tbl;

	// 空いているテーブルを取得
	tbl = getPlttDataClean();

	// テーブル数が足りたかチェック
	if( tbl == NULL ){
		GF_ASSERT(0&&("テーブルが一杯で登録できません"))
		return FALSE;		// 登録不可能
	}
	
	// パレットデータ読み込み
	if(LoadPlttData(pPlttData, tbl) == FALSE){
		return FALSE;
	}
		

	// パレットデータ転送
	if( TransPlttDataCleanVram(pPlttData, tbl) == FALSE ){
		//失敗したときは破棄
		//失敗したとき＝Vramにあまりのサイズがない
		DelPltt( pPlttData->id );
		return FALSE;
	}

	return TRUE;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	パレットデータを複数セット
 *
 *@param	pPlttData	パレットデータ
 *@param	num			セットする数
 *
 *@return	いくつ登録成功したか
 */
//-----------------------------------------------------------------------------
u16 PlttSetsCleanArea( const PLTT_MANAGER_HEADER* pPlttData, int num )
{
	int i;			// ループ用
	
	//
	// PLTT_ENDがくるまで読み込む
	//
	for(i=0;i<num;i++){
		// 読み込み＆セット処理
		if( PlttSetCleanArea( pPlttData + i ) == FALSE ){
			// 失敗
			break;
		}
	}

	return i;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	パレットデータ転送
 *
 *	@param	id			転送先のパレットID
 *	@param	pPlttData	パレットデータ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void PlttDataChg( int id, NNSG2dPaletteData* pPlttData )
{
	PLTT_DATA_TBL* tbl;
	
	GF_ASSERT( pPlttData );

	// idのデータ取得
	tbl = getPlttDataPtr(id);
	GF_ASSERT( tbl );
	
	
	tbl->pPlttData = pPlttData;
	
	if( tbl->type & NNS_G2D_VRAM_TYPE_2DMAIN ){
		// Vram
		// 転送マネージャで転送
		AddVramTransferManager(
			NNS_GFD_DST_2D_OBJ_PLTT_MAIN,
			tbl->offset,
			pPlttData->pRawData,
			tbl->load_size * PLTT_ONE_SIZE
			);
	}
	if( tbl->type & NNS_G2D_VRAM_TYPE_2DSUB ){
		// Vram
		// 転送マネージャで転送
		AddVramTransferManager(
			NNS_GFD_DST_2D_OBJ_PLTT_SUB,
			tbl->sub_offset,
			pPlttData->pRawData,
			tbl->load_size * PLTT_ONE_SIZE
			);
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	idのパレットデータがもう登録されているかチェック
 *
 *@param	id		チェックするid
 *
 *@retval	TRUE	登録されている
 *@retval	FALSE	登録されていない
 *
 *
 */
//-----------------------------------------------------------------------------
BOOL CheckPlttID(int id)
{
	PLTT_DATA_TBL* tbl;

	tbl = getPlttDataPtr(id);
	if(tbl){		// 登録済み
		return TRUE;
	}

	return FALSE;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	あといくつ登録できるのかを返す
 *
 *@param	none
 *
 *@return	int		残り登録可能数
 *
 *
 */
//-----------------------------------------------------------------------------
int CheckPlttRest(void)
{
	return PlttManagerData->plttDataNum - PlttManagerData->plttDataNow;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	パレットデータを破
 *
 *@param	p_str：パレットファイル名
 *	
 *@return	none
 *
 */
//-----------------------------------------------------------------------------
void DelPltt( int id )
{
	PLTT_DATA_TBL* tbl;			// 要素数取得用

	// 要素数を取得
	tbl = getPlttDataPtr(id);
	
	// 最大数かチェック
	GF_ASSERT(tbl);
	
	// キャラクタデータを破棄する
	// 稼動中かチェック
	if( tbl->flag == 1 ){
		// Vramエリア破棄
		transAreaCleanTbl( tbl );
		// データ破棄
		dellPlttData( tbl );	
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	全パレットデータを破棄
 *
 *@param	none
 *
 *@return	none
 *
 */
//-----------------------------------------------------------------------------
void DelPlttAll( void )
{
	int i;

	//
	// 全パレットデータを破棄
	//
	// パレットIDのテーブルを探す
	for( i = 0; i < PlttManagerData->plttDataNum; i++ ){
		// 稼動中かチェック
		if( PlttManagerData->plttDataTbl[ i ].flag == 1 ){
			// Vramエリア破棄
			transAreaCleanTbl( &PlttManagerData->plttDataTbl[ i ] );
			// データ破棄
			dellPlttData( &PlttManagerData->plttDataTbl[ i ] );

		}
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	IDのパレットプロクシを取得
 *
 *@param	id		パレットID
 *
 *@return	IDのプロクシ
 *
 */
//-----------------------------------------------------------------------------
NNSG2dImagePaletteProxy* GetPlttIDProxy( int id )
{
	PLTT_DATA_TBL* tbl;			// 要素データ

	// 要素数を取得
	tbl = getPlttDataPtr(id);
	if( tbl == NULL ){
		GF_ASSERT(tbl);
		return NULL;
	}

	// 稼動中なら返す
	if(tbl->flag == 1){
		return &tbl->PaletteProxy;
	}
	
	return NULL;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	パレットプロクシの取得
 *			パレットのモード（拡張パレット）にイメージプロクシを最適化する
 *					パレットプロクシ取得関数
 *
 *@param	id		パレットID
 *@param	pImage：イメージプロクシ
 *
 *@return	パレットプロクシ
 *
 */
//-----------------------------------------------------------------------------
NNSG2dImagePaletteProxy* GetPlttIDProxyJoin( int id, NNSG2dImageProxy* pImage )
{
	PLTT_DATA_TBL* tbl;			// 要素データ

	// 要素数を取得
	tbl = getPlttDataPtr(id);
	if( tbl == NULL ){
		GF_ASSERT(tbl);
		return NULL;
	}
	// 稼動中かチェック
	if( tbl->flag != 1 ){
		return NULL;
	}

	// 拡張パレットかチェック
	if( tbl->pPlttData->bExtendedPlt ){
		// イメージプロクシに拡張パレットをしようするように設定
		NNS_G2dSetImageExtPaletteFlag( pImage, TRUE );
	}
	
	return &tbl->PaletteProxy;
}


//----------------------------------------------------------------------------
/**
 *
 *@brief	パレットプロクシのあるパレットナンバーを取得する
 *
 *@param	pPltt：パレットナンバーを取得するパレットプロクシ
 *@param	vramType：メイン面かサブ面か
 *
 *@return	パレットナンバー
 *
 */
//-----------------------------------------------------------------------------
u32 GetPlttProxyOffset( const NNSG2dImagePaletteProxy* pPltt, u32 vramType )
{
	u32 size;			// １パレットサイズ
	u32 pltt_offset;	// パレットナンバー計算処理用
	
	// 拡張パレットかチェック
	if( pPltt->bExtendedPlt ){
		size = PLTT_ONE_SIZE * 16;
	}else{
		// 標準で256でないかチェック
		if( pPltt->fmt == GX_TEXFMT_PLTT256 ){
			// 256の時はサイズを０にして計算しない
			size = 0;
		}else{
			size = PLTT_ONE_SIZE;
		}
	}

	// 標準２５６色以外かチェック
	if( size != 0 ){
		// ずらす値取得
		pltt_offset = NNS_G2dGetImagePaletteLocation( pPltt, vramType );
		pltt_offset /= size;			// ずらす値にする(何パレットずらすか)
	}else{
		pltt_offset = 0;
	}

	return pltt_offset;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	パレットナンバーのプロクシを取得する
 *
 *@param	pltt_offset：このパレットナンバーのプロクシがあったら返す
 *@param	type：１６色、拡張パレットかのフラグ()
 *@param	vramType：パレットナンバーをあわせるVramのタイプ		１：メイン　２：サブ
 *
 *@return	見つかったプロクシ
 *@retval	見つからないときはNULL
 *
 */
//-----------------------------------------------------------------------------
NNSG2dImagePaletteProxy* GetPlttNumProxy( u32 pltt_offset, u32 type, u32 vramType )
{
	int i;			// ループ用
	u32	now_idx;	// 今のパレットナンバー
	u32 end_idx;	// 終了パレットナンバー
	
	
	//
	// 登録されている、パレットからpltt_offsetのパレットが
	// 登録されているパレットプロクシを返す
	//
	for( i = 0; i < PlttManagerData->plttDataNum; i++ ){
		// 稼動中かチェック
		if( PlttManagerData->plttDataTbl[ i ].flag == 1 ){
			// Typeが一緒かチェック
			if( ((type == 1) && (PlttManagerData->plttDataTbl[ i ].pPlttData->bExtendedPlt > 0 )) ||
				((type == 0) && (PlttManagerData->plttDataTbl[ i ].pPlttData->bExtendedPlt == 0 )) ){
				
				// Vramオフセット取得
				now_idx = NNS_G2dGetImagePaletteLocation( &PlttManagerData->plttDataTbl[ i ].PaletteProxy, vramType );

				// サイズから終了オフセットを計算
				end_idx = now_idx + (PlttManagerData->plttDataTbl[ i ].load_size * PLTT_ONE_SIZE);
		
				// テクスチャTypeのサイズで割る
				if(type == 1){
					now_idx /= PLTT_ONE_SIZE * 16;		// 拡張
					end_idx /= PLTT_ONE_SIZE * 16;		// 拡張
				}else{	
					now_idx /= PLTT_ONE_SIZE;			// 標準 １６色
					end_idx /= PLTT_ONE_SIZE;			// 標準 １６色
				}

				// now_idxとend_idxの中にpltt_offsetがあるかチェック
				if( (now_idx <= pltt_offset) && (end_idx >= pltt_offset) ){
					break;		// このパレットプロクシのデータ内にある
				}

				// もしnow_idxよりもpltt_offsetが小さくなったらもう
				// その位置に対応するパレットデータはないことになる
				if( now_idx > pltt_offset ){
					return NULL;
				}
			}
		}
	}

	// 最後まで行ったらNULLを返す
	if(i == PlttManagerData->plttDataNum){
		return NULL;
	}

	return &PlttManagerData->plttDataTbl[ i ].PaletteProxy;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	今動作されているパレットプロクシの中に引数のプロクシがあるか検索する
 *
 *@param	pPltt	検索するプロクシ
 *
 *@return	BOOL	TRUE	ある	FALSE	ない
 *
 *
 */
//-----------------------------------------------------------------------------
BOOL SearchPlttProxy( const  NNSG2dImagePaletteProxy* pPltt)
{
	int i;
	BOOL ret = FALSE;

	for(i=0;i<PlttManagerData->plttDataNum;i++){
		// 稼動中かチェック
		if( PlttManagerData->plttDataTbl[ i ].flag == 1 ){
			// IDをチェック
			if( &PlttManagerData->plttDataTbl[ i ].PaletteProxy == pPltt ){
				ret = TRUE;
				break;
			}	
		}
	}

	return ret;
}

//
// プライベート関数
//
//----------------------------------------------------------------------------
/**
 *
 *@brief	パレットデータを破棄する
 *
 *@param	pPlttData：破棄するパレットデータ
 *
 *@return	none
 *
 */
//-----------------------------------------------------------------------------
static void dellPlttData( PLTT_DATA_TBL* pPlttData )
{
	// 破棄する
	cleanPlttData(pPlttData);
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	パレットデータの読み込み
 *
 *@param	pPlttData	パレットENTRYデータ
 *@param	tbl			読み込むテーブルポインタ
 *
 *@return	BOOL	読み込み成功:TRUE	読み込み失敗:FALSE
 *
 *
 */
//-----------------------------------------------------------------------------
static BOOL LoadPlttData(const PLTT_MANAGER_HEADER* pPlttData, PLTT_DATA_TBL* tbl)
{
	// パレットデータ設定
	tbl->pPlttData = pPlttData->res_file;
	
	// IDが重複しないかチェック
	if(CheckPlttID(pPlttData->id) == TRUE){
		GF_ASSERT(0);
		return FALSE;
	}
	
	// IDをファイル名から取得
	tbl->act_num = pPlttData->id;
	
	// テーブルセット
	tbl->type	= pPlttData->type;			// Vramtype
	tbl->flag			= 1;						// 使用中
	tbl->load_size = pPlttData->pltt_num;	// 読み込むパレット数	

	return TRUE;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	パレットデータ初期化
 *
 *@param	data		パレットデータ
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void cleanPlttData(PLTT_DATA_TBL* data)
{
	memset( data, 0, sizeof(PLTT_DATA_TBL) );
	data->act_num	= PLT_DATA_ID_NONE;
	NNS_G2dInitImagePaletteProxy( &data->PaletteProxy );
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	パレットデータの転送
 *
 *@param	tbl	転送するパレットデータ
 *
 *@return	BOOL	転送成功:TRUE	転送失敗:FALSE
 *
 *
 */
//-----------------------------------------------------------------------------
static BOOL TransPlttData(const PLTT_MANAGER_HEADER* pPlttData, PLTT_DATA_TBL* tbl)
{
	u32* p_offset;
	u32* p_offset_sub;
	BOOL dell_flag = TRUE;		// 領域オーバーのときFALSEになるフラグ
	u32 vram_limit;				// メインのVram領域のlimit
	u32 vram_limit_sub;			// サブのVram領域のlimit
	
	// 拡張パレットかチェック
	if( tbl->pPlttData->bExtendedPlt ){
		// オフセット値のポインタをセット
		p_offset		= &PlttManagerData->OffsetEx;
		p_offset_sub	= &PlttManagerData->SubOffsetEx; 
		vram_limit = PlttManagerData->MainExPlttVramSize;			// Vramの領域のサイズ
		vram_limit_sub = PlttManagerData->SubExPlttVramSize;			// Vramの領域のサイズ
	}else{	
		// オフセット値のポインタをセット
		p_offset		= &PlttManagerData->Offset;
		p_offset_sub	= &PlttManagerData->SubOffset;
		vram_limit = PLTT_NORMAL_SIZE;		// Vramの領域のサイズ
		vram_limit_sub = PLTT_NORMAL_SIZE;	// Vramの領域のサイズ
	}
	
	// 転送先を設定
	transAreaCheckOffset( tbl, *p_offset, *p_offset_sub, vram_limit, vram_limit_sub );

	// offset位置にロード
	setTransPltt( tbl );

	// オフセットをずらす
	transAreaSetOffset( tbl, p_offset, p_offset_sub );

	return dell_flag;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	空いている領域を探してパレットデータを転送する
 *
 *	@param	pPlttData		パレットENTRYデータ
 *	@param	tbl				テーブル
 *
 *	@return
 *
 *
 */
//-----------------------------------------------------------------------------
static BOOL TransPlttDataCleanVram(const PLTT_MANAGER_HEADER* pPlttData, PLTT_DATA_TBL* tbl)
{
	int offset_m, offset_s;		// メインとサブのオフセット
	
	// 拡張パレットかチェック
	if( tbl->pPlttData->bExtendedPlt ){
		// 拡張パレットは無理です
		GF_ASSERT(0);
	}

	// エリア探索
	if( tbl->type & NNS_G2D_VRAM_TYPE_2DMAIN ){
		offset_m = transAreaCheck( PlttManagerData->main16VramArea, tbl->load_size );

		if(offset_m == PLTT_AREA_NONE){
			return FALSE;
		}
	}
	if( tbl->type & NNS_G2D_VRAM_TYPE_2DSUB ){
		offset_s = transAreaCheck( PlttManagerData->sub16VramArea, tbl->load_size );
		
		if(offset_s == PLTT_AREA_NONE){
			return FALSE;
		}
	}

	// オフセットを設定
	if( tbl->type & NNS_G2D_VRAM_TYPE_2DMAIN ){
		tbl->offset = offset_m;
	}
	if( tbl->type & NNS_G2D_VRAM_TYPE_2DSUB ){
		tbl->sub_offset = offset_s;
	}

	// パレットサイズ設定
	tbl->pPlttData->szByte = tbl->load_size * PLTT_ONE_SIZE;
	
	// 転送
	transVramPltt( tbl );

	// Vramエリア設定
	transAreaSetTbl( tbl );
	

	return TRUE;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	パスのパレットデータの要素数を取得する
 *
 *@param	id		パレットID
 *
 *@return	PLTT_DATA_TBL*	パレットデータテーブルポインタ
 *
 */
//-----------------------------------------------------------------------------
static PLTT_DATA_TBL*	getPlttDataPtr( int id )
{
	int i;			// ループ用

	
	
	// IDのデータを検索してプロクシを返す
	for( i = 0; i < PlttManagerData->plttDataNum; i++ ){
		// IDをチェック
		if( PlttManagerData->plttDataTbl[ i ].act_num == id ){
			return PlttManagerData->plttDataTbl + i;
		}	
	}

	return NULL;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	空いているテーブルを取得
 *
 *@param	none
 *
 *@return	PLTT_DATA_TBL* 空いているテーブル
 *
 *
 */
//-----------------------------------------------------------------------------
static PLTT_DATA_TBL* getPlttDataClean( void )
{
	int i;
	
	// パレットデータをテーブルにセット
	for( i = 0; i < PlttManagerData->plttDataNum; i++ ){
		// あいているところをサーチ
		if( PlttManagerData->plttDataTbl[ i ].flag == 0 ){
			return PlttManagerData->plttDataTbl + i;
		}
	}
	return NULL;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	パレットのVramサイズをセット
 *
 *@param	none
 *
 *@return	none
 *
 */
//-----------------------------------------------------------------------------
static void setVramPlttSize( void )
{
	GXVRamOBJExtPltt	vram_bank;		// メインVramバンク取得用
	GXVRamSubOBJExtPltt	sub_vram_bank;	// サブVramバンク取得用
	
	
	//
	// Vramのパレットサイズをセット
	//
	// メイン画面
	vram_bank = GX_GetBankForOBJExtPltt();
	switch( vram_bank ){
	case GX_VRAM_OBJEXTPLTT_0_F:	// メイン画面拡張パレット使用
	case GX_VRAM_OBJEXTPLTT_0_G:	// メイン画面拡張パレット使用
		PlttManagerData->MainExPlttVramSize = PLTT_EX_SIZE;
		break;

	default:
		PlttManagerData->MainExPlttVramSize = 0;	
		break;
	}

	// サブ画面
	sub_vram_bank = GX_GetBankForSubOBJExtPltt();
	switch( sub_vram_bank ){
	case GX_VRAM_SUB_OBJEXTPLTT_0_I:	// メイン画面拡張パレット使用
		PlttManagerData->SubExPlttVramSize = PLTT_EX_SIZE;
		break;

	default:
		PlttManagerData->SubExPlttVramSize = 0;	
		break;
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	パレットデータ転送処理をVブランク処理タスクにセット
 *
 *@param	pPlttData：パレットデータ
 *
 *@return	none
 *
 */
//-----------------------------------------------------------------------------
static void setTransPltt( PLTT_DATA_TBL* pPlttData )
{

	// リソースのサイズも変更
	pPlttData->pPlttData->szByte = pPlttData->load_size * PLTT_ONE_SIZE;
	
	transVramPltt( pPlttData);

}

//----------------------------------------------------------------------------
/**
 *
 *@brief	Vblank内で行うパレットデータのVramへの転送
 *
 *@param	p_data：転送するパレットデータ
 *
 *@return	none
 *
 */
//-----------------------------------------------------------------------------
static void transVramPltt( void* p_data )
{
	PLTT_DATA_TBL* p_pltt_data = (PLTT_DATA_TBL*)p_data;		// キャストしてデータ取得

	NNS_G2dInitImagePaletteProxy(&p_pltt_data->PaletteProxy);
	
	// Vramへ読み込む
	if(p_pltt_data->type & NNS_G2D_VRAM_TYPE_2DMAIN){
		// 両方に登録
		NNS_G2dLoadPalette(
				p_pltt_data->pPlttData,// キャラクタデータ
				p_pltt_data->offset,			// キャラクタベースアドレス
				NNS_G2D_VRAM_TYPE_2DMAIN,		// VramType
				&p_pltt_data->PaletteProxy );	// イメージプロクシ
	}

	if(p_pltt_data->type & NNS_G2D_VRAM_TYPE_2DSUB){
		NNS_G2dLoadPalette(
				p_pltt_data->pPlttData,// キャラクタデータ
				p_pltt_data->sub_offset,		// キャラクタベースアドレス
				NNS_G2D_VRAM_TYPE_2DSUB,		// VramType
				&p_pltt_data->PaletteProxy );	// イメージプロクシ
	}
}



// 転送エリアの設定
static void transAreaSet( u16* data, int num, int start )
{
	int i;		// ループ用
	
	for(i=0;i<num;i++){

		*data |= 1 << (start + i);
	}
}

static void transAreaClean( u16* data, int num, int start )
{
	int i;		// ループ用
	
	for(i=0;i<num;i++){

		*data &= ~( 1 << (start + i) );
	}
}

static int transAreaCheck( u16 data, int num )
{
	int i, j;		// ループ用
	
	for(i = 0; i < 16; i++ ){
		
		j = 0;
		// ビットがたっていなくて　カウンタがnumより小さいとき
		while( ( (data & (1 << ( i + j))) == 0 ) && (j < num) ){

			// サイズオーバーしたら終わり
			if( (i + j) >= 16 ){
				break;
			}

			j++;
		}
	
		// サイズ分の領域があったかチェック
		if(j >= num){
			break;
		}

		i += j;		// だめだった空間を飛ばす
	}

	// 最後までfor分が回っていたら入らないのでerrを返す
	if( i >= 16 )
	{
		return PLTT_AREA_NONE;
	}

	return i * PLTT_ONE_SIZE;
}

static void transAreaInit( PLTT_MANAGER_DATA* data )
{
	data->main16VramArea = 0;
	data->sub16VramArea = 0;
}

static void transAreaSetTbl( PLTT_DATA_TBL* data )
{
	if( data->type & NNS_G2D_VRAM_TYPE_2DMAIN ){
		transAreaSet( &PlttManagerData->main16VramArea, data->load_size, data->offset / PLTT_ONE_SIZE );
	}
	if( data->type & NNS_G2D_VRAM_TYPE_2DSUB ){
		transAreaSet( &PlttManagerData->sub16VramArea, data->load_size, data->sub_offset / PLTT_ONE_SIZE );
	}
}

static void transAreaCleanTbl( PLTT_DATA_TBL* data )
{
	if( data->type & NNS_G2D_VRAM_TYPE_2DMAIN ){
		transAreaClean( &PlttManagerData->main16VramArea, data->load_size, data->offset / PLTT_ONE_SIZE );
	}
	if( data->type & NNS_G2D_VRAM_TYPE_2DSUB ){
		transAreaClean( &PlttManagerData->sub16VramArea, data->load_size, data->sub_offset / PLTT_ONE_SIZE );
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	オフセットモードの転送エリアﾁｪｯｸ
 *
 *	@param	data	パレットデータ
 *	@param	m_offs	今のオフセット位置
 *	@param	s_offs	今のオフセット位置
 *
 *	@retval	TRUE		取得成功
 *	@retval	FALSE		取得失敗
 *
 *
 */
//-----------------------------------------------------------------------------
static BOOL transAreaCheckOffset( PLTT_DATA_TBL* data, u32 m_offs, u32 s_offs, u32 m_limit, u32 s_limit )
{
	BOOL dell_flag = TRUE;
	
	// メイン画面に読み込むかチェック
	if( data->type & NNS_G2D_VRAM_TYPE_2DMAIN ){

		// サイズオーバーチェック
		if( (m_offs + (data->load_size * PLTT_ONE_SIZE) > m_limit) ){

			// 登録しない
			GF_ASSERT(0&&("サイズオーバー"));
			now_debug_draw();		// 今の状況を描画
			dell_flag = FALSE;
		}else{
			data->offset = m_offs;	
		}
		
	}

	// サブ画面に読み込むかチェック
	if( data->type & NNS_G2D_VRAM_TYPE_2DSUB ){

		// サイズオーバーチェック
		if( (s_offs + (data->load_size * PLTT_ONE_SIZE) > s_limit) ){

			// 登録しない
			GF_ASSERT(0&&("サイズオーバー"));
			now_debug_draw();		// 今の状況を描画
			dell_flag = FALSE;
		}else{
			data->sub_offset = s_offs;
		}
	}

	return dell_flag;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	オフセットを移動させる
 *
 *	@param	data		パレットデータ
 *	@param	m_offs		メインオフセットのポインタ
 *	@param	s_offs		サブオフセットのポインタ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void transAreaSetOffset( PLTT_DATA_TBL* data, u32* m_offs, u32* s_offs )
{
	// ずらす
	if( data->type & NNS_G2D_VRAM_TYPE_2DMAIN ){
		*m_offs		+= data->load_size * PLTT_ONE_SIZE;
	}

	if( data->type & NNS_G2D_VRAM_TYPE_2DSUB ){
		*s_offs		+= data->load_size * PLTT_ONE_SIZE;
	}
}
