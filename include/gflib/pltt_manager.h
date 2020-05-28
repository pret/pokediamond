//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *	@file		pltt_manager.h
 *	@brief		パレットマネージャーヘッダ
 *	@author		tomoya takahashi
 *	@data		2004.11.22
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]


#ifndef PLTT_MANAGER_H__
#define	PLTT_MANAGER_H__

#undef	GLOBAL
#ifdef	PLTT_MANAGER_H_GLOBAL
#define	GLOBAL	/* */
#else
#define	GLOBAL	extern
#endif


//-----------------------------------------------------------------------------
/**
 *					定数宣言
 */
//-----------------------------------------------------------------------------
// パレットVRAM予約マスク
enum{
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
};

//-----------------------------------------------------------------------------
/**
 *					構造体宣言
 */
//-----------------------------------------------------------------------------
//-------------------------------------
//	
//	パレットデータヘッダー
//	
//=====================================
typedef struct {
	NNSG2dPaletteData*	res_file;		// パレットリソース
	u32		type;			// VramType
							// mainに登録：NNS_G2D_VRAM_TYPE_2DMAIN
							// subに登録 ：NNS_G2D_VRAM_TYPE_2DSUB
							// 両方に登録：NNS_G2D_VRAM_TYPE_2DMAX
	u32		pltt_num;		// 登録（データ転送する）パレット数
	u32		id;				// パレットID
} PLTT_MANAGER_HEADER;



//----------------------------------------------------------------------------
/**
 *					プロトタイプ宣言
 */
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *
 *@brief	パレットマネージャー初期化
 *
 *@param	PlttDataNum		パレット制御数
 *@param	heap			使用ヒープ
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void InitPlttManager(int PlttDataNum, int heap);

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
GLOBAL void SetReserveCleanAreaPlttManager( u16 msk, u32 disp );


//----------------------------------------------------------------------------
/**
 *
 *@brief	パレットマネージャー破棄
 *
 *@param	none
 *
 *@return	none
 *
 * これを呼べばどんな状態でも完全に破棄されます。
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void DeletePlttManager(void);

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
GLOBAL void PlttLoadStart( u32 start_offset );						// メイン画面パレット
GLOBAL void PlttLoadStartSub( u32 start_offset );					// サブ画面パレット
GLOBAL void PlttLoadStartEx( u32 start_offset );					// メイン画面拡張パレット
GLOBAL void PlttLoadStartSubEx( u32 start_offset );					// サブ画面拡張パレット

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
GLOBAL int PlttLoadOffsetGetMain( void );
	
/// サブ画面　標準パレット
GLOBAL int PlttLoadOffsetGetSub( void );

/// メイン画面　拡張パレット
GLOBAL int PlttLoadOffsetGetMainEx( void );

/// サブ画面　拡張パレット
GLOBAL int PlttLoadOffsetGetSubEx( void );

//----------------------------------------------------------------------------
/**
 *
 *@brief	ロードを開始する関数
 *
 *@param	none
 *
 *@return	none
 *	全てのオフセットを０で初期化
 */
//-----------------------------------------------------------------------------
GLOBAL void PlttLoadStartAll( void );

// ビットをチェックして
// 今空いている場所に転送します。
//----------------------------------------------------------------------------
/**
 *@brief	パレットデータ単体をセットしてロード
 *
 *@param	pPlttData：パレットデータ
 *
 *@retval	TRUE ：セットできた
 *			FALSE：セットできなかった
 *
 * 空いている空間をビット操作で管理しています。
 * 基本こっちを使用してください。
 */
//-----------------------------------------------------------------------------
GLOBAL BOOL PlttSetCleanArea( const PLTT_MANAGER_HEADER* pPlttData );

//----------------------------------------------------------------------------
/**
 *
 *@brief	パレットデータを複数セット
 *
 *@param	pPlttData	パレットデータ
 *@param	num			セットする数
 *
 *@return	いくつ登録成功したか
 * 空いている空間をビット操作で管理しています。
 * 基本こっちを使用してください。
 */
//-----------------------------------------------------------------------------
GLOBAL u16 PlttSetsCleanArea( const PLTT_MANAGER_HEADER* pPlttData, int num );



//OFFSETずらしです。
//----------------------------------------------------------------------------
/**
 *@brief	パレットデータ単体をセットしてロード
 *
 *@param	pPlttData：パレットデータ
 *
 *@retval	TRUE ：セットできた
 *			FALSE：セットできなかった
 *
 *	オフセットずらしで、上からずらしながら設定していきます。
 *	CleanAreaとの同居はしません。
 *	オフセットずらしのときは、オフセットずらししかできません
 */
//-----------------------------------------------------------------------------
GLOBAL BOOL PlttSet( const PLTT_MANAGER_HEADER* pPlttData );

//----------------------------------------------------------------------------
/**
 *
 *@brief	パレットデータを複数セット
 *
 *@param	pPlttData	パレットデータ
 *@param	num			セットする数
 *
 *@return	いくつ登録成功したか

 *	オフセットずらしで、上からずらしながら設定していきます。
 *	CleanAreaとの同居はしません。
 *	オフセットずらしのときは、オフセットずらししかできません
 */
//-----------------------------------------------------------------------------
GLOBAL u16 PlttSets( const PLTT_MANAGER_HEADER* pPlttData, int num );

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
 *	idのパレットの領域にもう一度パレットデータを読み込みます
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void PlttDataChg( int id, NNSG2dPaletteData* pPlttData );

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
GLOBAL BOOL CheckPlttID(int id);

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
GLOBAL int CheckPlttRest(void);

//----------------------------------------------------------------------------
/**
 *
 *@brief	パレットデータを破
 *
 *@param	id		パレットID
 *	
 *@return	none
 */
//-----------------------------------------------------------------------------
GLOBAL void DelPltt( int id );

//----------------------------------------------------------------------------
/**
 *
 *@brief	全パレットデータを破棄
 *
 *@param	none
 *
 *@return	none
 */
//-----------------------------------------------------------------------------
GLOBAL void DelPlttAll( void );

//----------------------------------------------------------------------------
/**
 *
 *@brief	IDのパレットプロクシを取得
 *
 *@param	id		パレットID
 *
 *@return	IDのプロクシ
 *
 * 拡張パレットの時はしたの関数を使用してください
 * 
 */
//-----------------------------------------------------------------------------
GLOBAL NNSG2dImagePaletteProxy* GetPlttIDProxy( int id );

//----------------------------------------------------------------------------
/**
 *
 *@brief	パレットプロクシの取得
 *			パレットのモード（拡張パレット）にイメージプロクシを最適化する
 *					パレットプロクシ取得関数
 *
 *@param	id		パレットID
 *@param	ppImage：イメージプロクシ
 *
 *@return	パレットプロクシ
 *
 * 拡張パレットを使用するときはこっちの関数を使用してください。
 * 
 */
//-----------------------------------------------------------------------------
GLOBAL NNSG2dImagePaletteProxy* GetPlttIDProxyJoin( int id, NNSG2dImageProxy* pImage );	
																			// ↑IDのプロクシを取得
																			// イメージプロクシを
																			// 拡張パレットモードかチェックして
																			// 最適なモードに設定する取得関数

//----------------------------------------------------------------------------
/**
 *
 *@brief	パレットNoのプロクシを取得する
 *
 *@param	pltt_offset：このパレットナンバーのプロクシがあったら返す
 *@param	type：１６色、拡張パレットかのフラグ()
 *@param	vramType：パレットナンバーをあわせるVramのタイプ		１：メイン　２：サブ
 *
 *@retval	見つかったプロクシ
 *@retval	見つからないときはNULL
 *
 * イメージプロクシのオフセットアドレスを変更して、強制的に違うパレットを
 * 参照するようにします。
 * 
 */
//-----------------------------------------------------------------------------
GLOBAL NNSG2dImagePaletteProxy* GetPlttNumProxy( u32 pltt_offset, u32 type, u32 vramType );

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
 *	このプロクシが何本目のパレットを参照しているのかを取得します。
 */
//-----------------------------------------------------------------------------
GLOBAL u32 GetPlttProxyOffset( const NNSG2dImagePaletteProxy* pPltt, u32 vramType  );


//----------------------------------------------------------------------------
/**
 *
 *@brief 今動作されているパレットプロクシの中に引数のプロクシがあるか検索する
 *
 *@param	pPltt	検索するプロクシ
 *
 *@return	BOOL	TRUE	ある FALSE ない
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL BOOL SearchPlttProxy( const  NNSG2dImagePaletteProxy* pPltt);


//----------------------------------------------------------------------------
/**
 *					グローバル変数宣言
 */
//-----------------------------------------------------------------------------

#undef	GLOBAL
#endif

