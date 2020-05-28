//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *	@file		char_manager.c
 *	@brief		キャラクタマネージャーの実態部
 *	@author		tomoya takahashi
 *	@data		2004.11.22
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

#define __CHAR_MANAGER_H_GLOBAL
#include "char_manager.h"
#include "system.h"
#include "gflib_os_print.h"
#include "assert.h"
#include "vram_transfer_manager.h"
#include <string.h>



//-----------------------------------------------------------------------------
/**
 *					定数宣言
 */
//-----------------------------------------------------------------------------
#define		CHAR_VRAM_TRANS_SHIFT	(8)		// Vramモードかのフラグにシフト

#define	CHAR_DATA_ID_NONE	(0xffffffff)

// Vram領域管理定数
#define CHAR_VRAM_BANK_GET_ERR	(0xffffffff)				// サイズがないときの戻り値
#define CHAR_ONE_SIZE	(32)		// １キャラクタサイズ


/// フラグの設定
enum
{
	CHAR_MAN_NONE,			// 動作なし
	CHAR_MAN_DO_NORMAL,		// NORMAL動作中
	CHAR_MAN_WAIT_VRAM_ORIG,// Vram転送のオリジナルデータ待ち状態
	CHAR_MAN_DO_VRAM_ORIG,	// Vram転送のオリジナルデータ動作中
	CHAR_MAN_DO_VRAM_COPY,	// Vram転送のCopyデータ動作中
};

// キャラクタ境界計算用
enum{
	CHAR_MAN_LIM_SUB,		// あまりを切り取る
	CHAR_MAN_LIM_ADD		// あまりを埋める
};
//-----------------------------------------------------------------------------
/**
 *					構造体宣言
 */
//-----------------------------------------------------------------------------
//-------------------------------------
///	キャラクタデータテーブル
//
typedef struct
{
	NNSG2dCharacterData*	pCharData;	// キャラクタデータ構造体(大本データの保持)
	NNS_G2D_VRAM_TYPE		type;		// VramType
										// mainに登録：NNS_G2D_VRAM_TYPE_2DMAIN = 1
										// subに登録 ：NNS_G2D_VRAM_TYPE_2DSUB = 2
										// 両方に登録：NNS_G2D_VRAM_TYPE_2DMAX = 3
	u8			vramType;				// Vram転送かのフラグ	１：Vram転送
	u32			act_num;				// 登録　識別ID
	NNSG2dImageProxy	ImageProxy;		// イメージプロクシ
	u32			offset;					// 自分のベースアドレス
	u32			sub_offset;				// サブのオフセット
	u8			flag;					// 使用しているかのフラグ
	BOOL		mapModeAdjust;			// キャラクタマッピングモードを今の状態に合わせるか
	u32			cont_type;				// Vramコントロールタイプ
	
	BOOL		have_area;				// Vramエリアを保持しているか
	u32			have_szByte;			// Vram確保サイズメイン
	u32			have_szByteSub;			// Vram確保サイズサブ
} CHAR_DATA_TBL;



//-------------------------------------
//	
//	キャラクタマネージャー構造体
//	
//=====================================
typedef struct {
	CHAR_DATA_TBL*	charDataTbl;	// キャラクタデータテーブル
	int		charDataNum;			// キャラクタデータ数
	int		charDataNow;			// キャラクタデータ登録数 
	u32		Offset;					// 読み込み時のオフセット
	u32		SubOffset;				// サブVramのオフセット
	s32		MainObjVramSize;		// メイン画面のVramBankのサイズ
	s32		SubObjVramSize;			// サブ画面のVramBankのサイズ
	s32		MainVramTransStart;		// メイン画面のVram管理領域のスタート位置
	s32		SubVramTransStart;		// サブ画面のVram管理領域のスタート位置
	u32		TransAreaMainSize;		// メイン画面のVram管理領域	（1024の内いくつを転送に使うかを指定します）
	u32		TransAreaSubSize;		// メイン画面のVram管理領域	（1024の内いくつを転送に使うかを指定します）
	u32		MainModeCharLimit;		// メイン画面のキャラクタ境界
	u32		SubModeCharLimit;		// サブ画面のキャラクタ境界
	u8*		TransAreaFlagMain;		// VramBank数分のフラグメイン画面用
	u8*		TransAreaFlagSub;		// VramBank数分のフラグサブ画面用
} CHAR_MANAGER_DATA;


//----------------------------------------------------------------------------
/**
 *					プロトタイプ宣言
 */
//-----------------------------------------------------------------------------
static void cleanCharData(CHAR_DATA_TBL* data);		// 初期化
static BOOL LoadCharData(const CHAR_MANAGER_HEADER* pEntData, CHAR_DATA_TBL* pCharData);		// キャラクタデータを読み込む
static CHAR_DATA_TBL* getImageProxyTbl(const NNSG2dImageProxy* pImage);
static BOOL TransCharData(CHAR_DATA_TBL* tbl);		// キャラクタデータを転送する
static BOOL TransCharOffset(CHAR_DATA_TBL* tbl);	// Offset転送モード
static BOOL TransCharAreaCont(CHAR_DATA_TBL* tbl);	// areaCont転送モード

static void setTransChar( CHAR_DATA_TBL* pCharData, u32 p_offset, u32 p_sub_offset );	// 転送マネージャーにセット

static BOOL getvramTransOffset(int type, u32* main, u32* sub, u32 szByte, u32* get_size, u32* get_size_sub);
static void setvramTransOffsetProxy(CHAR_DATA_TBL* data, u32 main, u32 sub);
static void setvramTransBitData(int type, u32 main, u32 sub, u32 szByte, u32 szByteSub);

static void transVramChar( void* p_data );				// キャラクタ
static void transVramCharCore( CHAR_DATA_TBL* data, int vram_type);
static void transVramCharVramMode( void* p_data );		// Vram転送アニメモードのキャラクタ
static void transVramCharVramModeCore( CHAR_DATA_TBL* data, int vram_type);
static u32 getTransAreaSize( u8* p_trans_flag );		// Vram転送Vram管理領域のサイズ取得用

static CHAR_DATA_TBL* getCharData( void );				// 空のデータテーブルを取得
static void setObjVramSize( void );						// Vramバンクのサイズをセット
static void dellCharData( CHAR_DATA_TBL* pCharData );	// キャラクタデータを破棄
static void delCharTblTransArea( CHAR_DATA_TBL* pCharData );	// キャラクタデータのVramエリアを開放
static CHAR_DATA_TBL* getCharDataPtr( int id );			// idのキャラクタデータを取得
static void MakeTransArea( u32 main_size, u32 sub_size, int heap );		// Vram転送用Vramエリアの作成
static void DellTransArea( u8* p_trans_flag );					// Vram転送用Vramエリアの破棄
static void TransAreaInit( u8* p_trans_flag );			// Vram転送用Vramエリアの初期化

static void TransBitSet( u32 num, u32 size, u8* p_trans_flag );	// 転送したエリアのビットを設定
static u32 TransBitCheck( u32 size, u8* p_trans_flag );	// 転送したサイズのエリアが残っているかチェック
static void TransBitClean( u32 start_num, u32 size, u8* p_trans_flag );	// 返却したエリアを初期化する

static int charModeAdjust( CHAR_DATA_TBL* pCharData, int type );


// 転送すべきオフセット値を取得する関数
static BOOL modeNormOffsetGet( u32 szByte, int type, u32* offs_main, u32* offs_sub );
static void modeNormOffsetMove( u32 szByte, int type );

static void byte8_byte1_Get( int num, u32* byte8, u8* byte1 );


static int getCharModeLimNum( int num, int limit, int flag );
static int getCharModeNum( int szByte, int limit );
static int getCharModeNum_byte( int szChar, int limit );

static void getReserveAreaContData( u32 areacont_start, u32 offset, u32 size, int* start_offset, int* set_size );

//----------------------------------------------------------------------------
/**
 *					グローバル変数宣言
 */
//-----------------------------------------------------------------------------
static CHAR_MANAGER_DATA*	CharManager = NULL;
// 後々はこのデータを外部の持ち、
// 各関数の引数にこのデータを渡して動作するようにする
// 今は誰に持たせればよいのかわからないため、自分で持つ


//
// グローバル関数
//
//----------------------------------------------------------------------------
/**
 *
 *@brief	  キャラクタマネージャーを初期化
 *
 *@param	CharMakeData	キャラクタマネージャー作成データ
 *
 *@return	none
 *
 */
//-----------------------------------------------------------------------------
void InitCharManager( const CHAR_MANAGER_MAKE* CharMakeData )
{
	// 初期化
	InitCharManagerReg( CharMakeData, GX_GetOBJVRamModeChar(), GXS_GetOBJVRamModeChar() );
}


//----------------------------------------------------------------------------
/**
 *
 *	@brief	キャラクタマネージャを初期化
 *
 *	@param	CharMakeData	キャラクタマネージャ作成データ
 *	@param	modeMain		キャラクタマッピングモード　メイン画面
 *	@param	modeSub			キャラクタマッピングモード　サブ画面
 *
 *	@return	none
 *
 */
//-----------------------------------------------------------------------------
void InitCharManagerReg( const CHAR_MANAGER_MAKE* CharMakeData, GXOBJVRamModeChar modeMain, GXOBJVRamModeChar modeSub )
{
	int i;
	int main_size_cm;
	int sub_size_cm;
	
	if(CharManager == NULL){
		CharManager = sys_AllocMemory(CharMakeData->heap, sizeof(CHAR_MANAGER_DATA));
		MI_CpuClear32(CharManager, sizeof(CHAR_MANAGER_DATA));

		CharManager->charDataNum = CharMakeData->CharDataNum;
		CharManager->charDataTbl = sys_AllocMemory(CharMakeData->heap, sizeof(CHAR_DATA_TBL)*CharManager->charDataNum);


		for(i=0;i<CharMakeData->CharDataNum;i++){
			cleanCharData(CharManager->charDataTbl + i);	
		}

		// キャラクタ境界取得
		CharManager->MainModeCharLimit = CharModeMinNum( modeMain );
		CharManager->SubModeCharLimit = CharModeMinNum( modeSub );
		// レジスタに設定
		GX_SetOBJVRamModeChar( modeMain );
		GXS_SetOBJVRamModeChar( modeSub );


		// キャラクタ境界サイズずつでVramを管理する領域を作成
		main_size_cm = getCharModeNum( CharMakeData->VramTransAreaMain,
										CharManager->MainModeCharLimit );
		sub_size_cm = getCharModeNum( CharMakeData->VramTransAreaSub,
										CharManager->SubModeCharLimit );
		MakeTransArea(main_size_cm, sub_size_cm, CharMakeData->heap);
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	キャラクタマネージャーを完全に破棄します。
 *
 *@param	none
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void DeleteCharManager(void)
{
	if(CharManager != NULL){
		DellTransArea(CharManager->TransAreaFlagMain);
		DellTransArea(CharManager->TransAreaFlagSub);
		
		DelCharAll();
		sys_FreeMemoryEz(CharManager->charDataTbl);
		sys_FreeMemoryEz(CharManager);
		CharManager = NULL;
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	  ロードを開始する関数	(内部管理のオフセットを初期化)
 *
 *@param	  start_offset：読み込み開始offset
 *
 *@return	  none
 *
 */
//-----------------------------------------------------------------------------
///メイン面
void CharLoadStart( u32 start_offset )
{
	CharManager->Offset = start_offset;
	setObjVramSize();			// Vramのサイズをセット
}

/// サブ面
void CharLoadStartSub( u32 start_offset )
{
	CharManager->SubOffset = start_offset;
	setObjVramSize();			// Vramのサイズをセット
}

/// 全体
void CharLoadStartAll( void )
{
	CharManager->Offset    = 0;
	CharManager->SubOffset = 0;
	TransAreaInit( CharManager->TransAreaFlagMain );
	TransAreaInit( CharManager->TransAreaFlagSub );
	setObjVramSize();			// Vramのサイズをセット
}

//----------------------------------------------------------------------------
/**
 *	@brief	AreaCont関数用	使用禁止領域設定
 *
 *	@param	offset		使用禁止オフセット位置
 *	@param	size		使用禁止サイズ
 *	@param	disp		画面
 *
 *	disp
 *		mainに登録：NNS_G2D_VRAM_TYPE_2DMAIN = 1
 *		subに登録 ：NNS_G2D_VRAM_TYPE_2DSUB = 2
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void SetReserveAreaContCharManager( u32 offset, u32 size, u32 disp )
{
	int start_offset;
	int set_size;
	
	// 管理ビット設定
	if( disp == NNS_G2D_VRAM_TYPE_2DMAIN ){
		// offsetが管理領域以下のときもあるので、ケアしておく
		getReserveAreaContData( 
				CharManager->MainVramTransStart,
				offset, size,
				&start_offset, &set_size );
		
		if( set_size > 0 ){
			setvramTransBitData( NNS_G2D_VRAM_TYPE_2DMAIN, start_offset, 0, set_size, 0 );
		}
	}else{

		// offsetが管理領域以下のときもあるので、ケアしておく
		getReserveAreaContData( 
				CharManager->SubVramTransStart,
				offset, size,
				&start_offset, &set_size );
		
		if( set_size > 0 ){
			setvramTransBitData( NNS_G2D_VRAM_TYPE_2DSUB, 0, start_offset, 0, set_size );
		}
	}
}


//----------------------------------------------------------------------------
/**
 *
 *@brief		キャラクタデータ単体をセットしてロード
 *
 *@param		pChatData：キャラクタENTRYデータ
 *
 *@retval		TRUE ：セットできた  
 *@retval		FALSE：セットできなかった
 *
 */
//-----------------------------------------------------------------------------
BOOL CharSet( const CHAR_MANAGER_HEADER* pCharData )
{
	CHAR_DATA_TBL* tbl;
	u32* p_offset;
	u8 dell_flag = 0;		// 破棄フラグ
	u32	vram_limit;			// Vramの最大サイズ	

	if(CheckCharID(pCharData->id) == TRUE){
		GF_ASSERT(0&&("IDが重複しています"));
	}

	//
	// キャラクタデータをテーブルにセット
	//
	tbl = getCharData();
	if( tbl == NULL ){
		GF_ASSERT(0&&("データ登録テーブルMAXです。もう登録できません。"));
		return FALSE;		// 登録不可能
	}


	// キャラクタデータ読み込み
	if(LoadCharData(pCharData, tbl) == FALSE){
		return FALSE;
	}

	// Vramに転送する
	if( TransCharData(tbl) == FALSE ){
		DelChar( tbl->act_num );
		return FALSE;
	}

	// 登録数アッド
	CharManager->charDataNow++;

	return TRUE;
}




//----------------------------------------------------------------------------
/**
 *
 *@brief		キャラクタデータを複数セット
 *
 *@param		pChatData：キャラクタデータ
 *@param		num			配列要素数
 *
 *@return		いくつ登録成功したか
 *
 */
//-----------------------------------------------------------------------------
u16 CharSets( const CHAR_MANAGER_HEADER* pCharData, int num )
{
	int i;	// ループ用

	// CHAR_ENDがくるまで読み込む
	for(i=0;i<num;i++){
		// 読み込み＆セット処理
		if( CharSet( pCharData + i ) == FALSE ){
			// 失敗
			break;
		}
	}

	return i;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief		キャラクタデータ単体をセットしてロード
 *				マッピングモードを今の状態に変更するモード
 *
 *@param		pChatData：キャラクタENTRYデータ
 *
 *@retval		TRUE ：セットできた  
 *@retval		FALSE：セットできなかった
 *
 */
//-----------------------------------------------------------------------------
BOOL CharSetCharModeAdjust( const CHAR_MANAGER_HEADER* pCharData )
{
	CHAR_DATA_TBL* tbl;
	u32* p_offset;
	u8 dell_flag = 0;		// 破棄フラグ
	u32	vram_limit;			// Vramの最大サイズ	

	if(CheckCharID(pCharData->id) == TRUE){
		GF_ASSERT(0&&("IDが重複しています"));
	}

	//
	// キャラクタデータをテーブルにセット
	//
	tbl = getCharData();
	if( tbl == NULL ){
		GF_ASSERT(0&&("データ登録テーブルMAXです。もう登録できません。"));
		return FALSE;		// 登録不可能
	}


	// キャラクタデータ読み込み
	if(LoadCharData(pCharData, tbl) == FALSE){
		return FALSE;
	}

	// キャラクタデータのモードを今の状態に変更する
	tbl->mapModeAdjust = TRUE;
	

	// Vramに転送する
	if( TransCharData(tbl) == FALSE ){
		DelChar( tbl->act_num );
		return FALSE;
	}

	// 登録数アッド
	CharManager->charDataNow++;

	return TRUE;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief		キャラクタデータを複数セット
 *				マッピングモードを今の状態に変更するモード
 *
 *@param		pChatData	キャラクタデータ配列
 *@param		num			配列要素数
 *
 *@return		いくつ登録成功したか
 */
//-----------------------------------------------------------------------------
u16 CharSetsCharModeAdjust( const CHAR_MANAGER_HEADER* pCharData, int num )
{
	int i;	// ループ用

	// CHAR_ENDがくるまで読み込む
	for(i=0;i<num;i++){
		// 読み込み＆セット処理
		if( CharSetCharModeAdjust( pCharData + i ) == FALSE ){
			// 失敗
			break;
		}
	}

	return i;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	idのキャラクタデータがもう登録されているかチェック
 *
 *@param	id		チェックするid
 *
 *@retval	TRUE	登録されている
 *@retval	FALSE	登録されていない
 *
 *
 */
//-----------------------------------------------------------------------------
BOOL CheckCharID(int id)
{
	int i;

	for(i=0;i<CharManager->charDataNum;i++){
		if(CharManager->charDataTbl[i].act_num == id){
			return TRUE;
		}
	}

	return FALSE;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	管理IDのVramにキャラクタデータを転送する
 *
 *	@param	id				転送先のデータid
 *	@param	pCharData		転送するキャラクタデータ
 *
 *	@return	none
 *
 * キャラクタデータのサイズが一緒である必要があります
 *
 */
//-----------------------------------------------------------------------------
void CharDataChg( int id, NNSG2dCharacterData* pCharData )
{
	CHAR_DATA_TBL* tbl;	// キャラクタテーブル

	GF_ASSERT( pCharData );
	
	tbl = getCharDataPtr(id);
	GF_ASSERT(tbl);
	tbl->pCharData	= pCharData;

	if( (tbl->type & NNS_G2D_VRAM_TYPE_2DMAIN) ){
		// Vram
		// 転送マネージャで転送
		AddVramTransferManager(
			NNS_GFD_DST_2D_OBJ_CHAR_MAIN,
			tbl->offset,
			pCharData->pRawData,
			pCharData->szByte
			);
	}
	if( tbl->type & NNS_G2D_VRAM_TYPE_2DSUB ){
		// Vram
		// 転送マネージャで転送
		AddVramTransferManager(
			NNS_GFD_DST_2D_OBJ_CHAR_SUB,
			tbl->sub_offset,
			pCharData->pRawData,
			pCharData->szByte
			);
	}

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
int CheckCharRest(void)
{
	return CharManager->charDataNum - CharManager->charDataNow;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	キャラクタデータを破棄
 *
 *@param	id		キャラクタid
 *
 *@return	none
 *
 */
//-----------------------------------------------------------------------------
void DelChar( int id )
{
	CHAR_DATA_TBL* tbl;		// キャラクタデータ
	int flag = 1;
	do{
		// キャラクタデータの要素数を取得
		tbl = getCharDataPtr(id);
		GF_ASSERT(tbl);
	
		// コピーは破棄
		if(tbl->flag == CHAR_MAN_DO_VRAM_COPY){
			DelVramTransData( &tbl->ImageProxy );	
		}else{
			// オリジナルデータの時破棄に行く
			flag = 0;
		}
	}while( flag );
	
	// キャラクタデータを破棄する
	// 稼動中かチェック
	if( (tbl->flag != CHAR_MAN_NONE) ){
		// 破棄
		dellCharData( tbl );
		CharManager->charDataNow--;
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	全キャラクタデータを破棄
 *
 *@param	none
 *
 *@return	none
 *
 */
//-----------------------------------------------------------------------------
void DelCharAll( void )
{
	int i;

	//
	// 全キャラクタデータを破棄
	//
	// キャラクタIDのテーブルを探す
	for( i = 0; i < CharManager->charDataNum; i++ ){
		// 稼動中かチェック
		if( CharManager->charDataTbl[ i ].flag != CHAR_MAN_NONE ){
			// データ破棄
			dellCharData( &CharManager->charDataTbl[ i ] );
			CharManager->charDataNow--;
		}
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	IDのイメージプロクシを取得
 *
 *@param	id			キャラクタID
 *
 *@return	IDのプロクシ
 *
 */
//-----------------------------------------------------------------------------
NNSG2dImageProxy* GetCharIDProxy( int id )
{
	CHAR_DATA_TBL* tbl;

	// キャラクタデータの要素数を取得
	tbl = getCharDataPtr(id);
	GF_ASSERT(tbl);

	// 稼動中でなければNULLを返す
	if( tbl->flag == CHAR_MAN_NONE ){
		return NULL;
	}
	
	return &tbl->ImageProxy;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	IDのキャラクタデータを取得
 *
 *@param	pImage：イメージプロクシポインタ
 *
 *@return	キャラクタデータ
 *
 */
//-----------------------------------------------------------------------------
NNSG2dCharacterData* GetCharIDData( const NNSG2dImageProxy* pImage )
{
	CHAR_DATA_TBL* data;
	
	data = getImageProxyTbl(pImage);

	return data->pCharData;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	セルVram転送アニメーション用のキャラクタプロクシを取得
 *
 *@param	id			キャラクタID
 *@param	szByte		使用サイズ
 *
 *@retval	イメージプロクシ
 *@retval	NULL			オリジナルは使用中なのでコピーを作成してください
 *
 *
 */
//-----------------------------------------------------------------------------
NNSG2dImageProxy* GetCharVramTransData( int id, u32 szByte )
{
	u32	offset, offset_sub;		// オフセット
	CHAR_DATA_TBL* now_tbl;	// 今登録済みテーブル
	CHAR_DATA_TBL* pTbl;	// 登録するテーブル
	u32	size_m, size_s;		// 実際に確保したVramサイズ

	// キャラクタデータの要素数を取得
	now_tbl = getCharDataPtr(id);
	GF_ASSERT(now_tbl);
	
	// 稼動中でなければNULLを返す
	if( now_tbl->flag == CHAR_MAN_NONE ){
		return NULL;
	}
	
	//
	// Vramのサイズがしようする画面のVramにあるかチェック
	//
	getvramTransOffset(now_tbl->type, &offset, &offset_sub, szByte, &size_m, &size_s);

	// オリジナルデータが使用中ならエラーを返す
	if( now_tbl->flag == CHAR_MAN_DO_VRAM_ORIG ){
		
		return NULL;
		
	}else{
		// オリジナルが使えるならオリジナルを使用
		// フラグを実行にする
		now_tbl->flag = CHAR_MAN_DO_VRAM_ORIG;
		pTbl = now_tbl;
	}

	// プロクシをセット
	setvramTransOffsetProxy(pTbl, offset, offset_sub);

	// Vramエリア保持
	pTbl->have_area = TRUE;
	pTbl->have_szByte		= size_m;
	pTbl->have_szByteSub	= size_s;

	// 転送
	transVramCharVramMode(pTbl);

	//
	// Vram領域フラグを使用中にする
	//
	setvramTransBitData(pTbl->type, offset, offset_sub, size_m, size_s);

	return &pTbl->ImageProxy;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	セルVram転送アニメーション用のキャラクタプロクシをコピーして取得
 *
 *@param	Orig	オリジナルイメージプロクシ
 *
 *@return	コピーしてVram転送オフセットを取得したイメージプロクシ
 *@return	NULL	オリジナルが使用中でない可能性があります。
 */
//-----------------------------------------------------------------------------
NNSG2dImageProxy* GetCharVramTransProxyCopy( const NNSG2dImageProxy* Orig )
{
	CHAR_DATA_TBL* data;
	CHAR_DATA_TBL* copy;
	u32 main, sub;		// オフセット
	u32	size_m, size_s;	// 実際に確保したVramサイズ
	u32 data_size;
	

	// イメージプロクシのテーブル取得
	data = getImageProxyTbl(Orig);
	GF_ASSERT(data);
	
	// コピー先取得
	copy = getCharData();
	GF_ASSERT(copy);

	// フラグをチェック
	if(data->flag != CHAR_MAN_DO_VRAM_ORIG){
		return NULL;
	}

	// コピー
	*copy = *data;

	// フラグをコピーにする
	copy->flag = CHAR_MAN_DO_VRAM_COPY;

	if( copy->type & NNS_G2D_VRAM_TYPE_2DMAIN ){
		data_size = copy->have_szByte;
	}else{
		data_size = copy->have_szByteSub;
	}
	
	// オフセット取得
	getvramTransOffset(copy->type, &main, &sub, data_size, &size_m, &size_s);

	// プロクシに設定
	setvramTransOffsetProxy(copy, main, sub);

	// Vramエリア保持
	copy->have_area = TRUE;
	copy->have_szByte = size_m;
	copy->have_szByteSub = size_s;
	
	transVramCharVramMode( (void*)copy );

	// Vram領域フラグを使用中にする
	setvramTransBitData(copy->type, main, sub, size_m, size_s );

	return &copy->ImageProxy;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	セルVram転送アニメのVram領域を開放
 *
 *@param	pImage：破棄するキャラクタ領域の
 *			イメージプロクシ
 *
 *@return	none
 *
 */
//-----------------------------------------------------------------------------
void DelVramTransData( const NNSG2dImageProxy* pImage )
{
	int i;			// ループ用
	
	//
	// プロクシのポインタと同じプロクシを探す
	// 
	for( i = 0; i < CharManager->charDataNum; i++ )
	{
		// 稼動中かチェック
		if( (CharManager->charDataTbl[ i ].flag == CHAR_MAN_DO_VRAM_ORIG) || 
			(CharManager->charDataTbl[ i ].flag == CHAR_MAN_DO_VRAM_COPY) ){
			// IDをチェック
			if( &CharManager->charDataTbl[ i ].ImageProxy == pImage ){
				break;
			}	
		}
	}

	if( i >= CharManager->charDataNum ){
		return ;
	}

	// Vramエリアの解放
	delCharTblTransArea( CharManager->charDataTbl + i );

	//
	// フラグをチェン
	// オリジナルかチェック
	if( CharManager->charDataTbl[ i ].flag == CHAR_MAN_DO_VRAM_ORIG ){
		// 待ち状態にする
		CharManager->charDataTbl[ i ].flag = CHAR_MAN_WAIT_VRAM_ORIG;
	}else{
		// Copyの時はデータなし状態にする
		CharManager->charDataTbl[ i ].flag = CHAR_MAN_NONE;
		cleanCharData( &CharManager->charDataTbl[ i ] );
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	NNSG2dCharacterDataを使用しないときのVramエリア確保用
 *
 *	@param	szByte		キャラクタデータサイズ
 *	@param	cont_type	Vramコントロールタイプ
 *	@param	type		登録画面
 *	@param	allocData	確保データ格納先
 *
 *	@retval	TRUE	領域確保できた
 *	@retval	FALSE	領域確保できなかった
 *
 *	cont_type
 *		CHARM_CONT_OFFSET	オフセットタイプ
 *		CHARM_CONT_AREACONT	エリアコントロールタイプ
 *
 *	type
 *		NNS_G2D_VRAM_TYPE_2DMAIN	メイン画面VRAM
 *		NNS_G2D_VRAM_TYPE_2DSUB		サブ画面VRAM
 *
 */
//-----------------------------------------------------------------------------
BOOL CharVramAreaAlloc( int szByte, int cont_type, int type, CHAR_MANAGER_ALLOCDATA* allocData )
{
	u32 offs_m, offs_s;
	u32 size_m, size_s;
	BOOL check;
	
	if( cont_type == CHARM_CONT_OFFSET ){
		
		// 転送できるかチェック
		check = modeNormOffsetGet( szByte, type, &offs_m, &offs_s );

		if(check){

			// オフセットをずらす
			modeNormOffsetMove( szByte, type );

			// 確保データ作成
			allocData->type = type;
			allocData->alloc_size	= szByte;
			if( type == NNS_G2D_VRAM_TYPE_2DMAIN ){
				allocData->alloc_ofs	= offs_m;
			}else{
				allocData->alloc_ofs	= offs_s;
			}
		}

	}else{
		
		// 転送できるかチェック
		check = getvramTransOffset(type, &offs_m, &offs_s, szByte, &size_m, &size_s);
		if(check){

			// Vram領域フラグを使用中にする
			setvramTransBitData(type, offs_m, offs_s, size_m, size_s);

			// 確保データ作成
			allocData->type = type;
			if( type == NNS_G2D_VRAM_TYPE_2DMAIN ){
				allocData->alloc_size	= size_m;
				allocData->alloc_ofs	= offs_m;
			}else{
				allocData->alloc_size	= size_s;
				allocData->alloc_ofs	= offs_s;
			}
		}
	}

	return check;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	NNSG2dCharacterDataを使用しないときのVramエリア破棄用
 *			cont_type = CHARM_CONT_AREACONTのときよう
 *
 *	@param	allocData	登録データ
 * 
 *	@return	none
 *
 * オフセットずらしモードで確保したものは解放できません
 *
 */
//-----------------------------------------------------------------------------
void CharVramAreaFree( CHAR_MANAGER_ALLOCDATA* allocData )
{
	int cm_s;		// キャラクタ境界単位のサイズ
	int cm_ofs;		// キャラクタ境界単位のオフセット
	
	
	// セルVramアニメの領域を開放
	if( allocData->type & NNS_G2D_VRAM_TYPE_2DMAIN ){
		cm_s = getCharModeNum( allocData->alloc_size ,CharManager->MainModeCharLimit);
		cm_ofs = getCharModeNum( allocData->alloc_ofs - CharManager->MainVramTransStart, CharManager->MainModeCharLimit );
		TransBitClean( cm_ofs,
				cm_s,
				CharManager->TransAreaFlagMain );

	}
	
	if( allocData->type & NNS_G2D_VRAM_TYPE_2DSUB ){
		cm_s = getCharModeNum( allocData->alloc_size ,CharManager->SubModeCharLimit);
		cm_ofs = getCharModeNum( allocData->alloc_ofs - CharManager->SubVramTransStart, CharManager->SubModeCharLimit );

		TransBitClean( cm_ofs,
				cm_s,
				CharManager->TransAreaFlagSub );
	}

}


//----------------------------------------------------------------------------
/**
 *	@brief	キャラクタマネージャポインタの取得
 *
 *	@param	none
 *
 *	@return	キャラクタマネージャポインタ
 */
//-----------------------------------------------------------------------------
void* CharManagerPtrGet( void )
{
	void* buff;
	
	// 破棄済みのキャラクタマネージャです
	GF_ASSERT( CharManager );

	buff = CharManager;
	CharManager = NULL;
	return buff;
}

//----------------------------------------------------------------------------
/**
 *	@brief	キャラクタマネージャポインタを設定
 *
 *	@param	pdata	キャラクタマネージャポインタ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void CharManagerPtrSet( void* pdata )
{
	// まだ破棄されていないのに上書きしようとしています
	GF_ASSERT( CharManager == NULL );

	CharManager = pdata;
}


//
// プライベート関数
//
//----------------------------------------------------------------------------
/**
 *
 *@brief	キャラクタデータを初期化
 *
 *@param	data	データ
 *
 *@return	void
 *
 *
 */
//-----------------------------------------------------------------------------
static void cleanCharData(CHAR_DATA_TBL* data)
{
	data->pCharData		= NULL;
	data->type			= 0;
	data->vramType		= 0;
	data->act_num		= CHAR_DATA_ID_NONE;
	data->offset		= 0;
	data->sub_offset	= 0;
	data->flag			= 0;
	data->mapModeAdjust = 0;
	NNS_G2dInitImageProxy( &data->ImageProxy );
	
}
//----------------------------------------------------------------------------
/**
 *
 *@brief	キャラクタデータを読み込む
 *
 *@param	pEntData		ENTRYデータ
 *@param	pCharData		キャラクタデータ読み込みテーブル
 *
 *@return	BOOL	成功：TRUE	失敗：FALSE	(パスがあっていない　又はメモリがたりない)
 *
 *
 */
//-----------------------------------------------------------------------------
static BOOL LoadCharData(const CHAR_MANAGER_HEADER* pEntData, CHAR_DATA_TBL* pCharData)
{
	// データ設定
	pCharData->pCharData = pEntData->res_file;
	
	// IDを設定
	pCharData->act_num = pEntData->id;
	
	// テーブルセット
	pCharData->type		= pEntData->type;	// VramTypeをセット
	pCharData->vramType	= pCharData->pCharData->characterFmt >> CHAR_VRAM_TRANS_SHIFT;

	// コントロールタイプ設定
	pCharData->cont_type = pEntData->cont_type;

	// Vram管理データ
	pCharData->have_area = FALSE;
	pCharData->have_szByte		= 0;
	pCharData->have_szByteSub	= 0;

	return TRUE;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	イメージプロクシと同じテーブルを探す
 *
 *@param	pImage		探すテーブルのイメージプロクシ
 *
 *@return	CHAR_DATA_TBL*	見つかったテーブル
 *
 *
 */
//-----------------------------------------------------------------------------
static CHAR_DATA_TBL* getImageProxyTbl(const NNSG2dImageProxy* pImage)
{
	int i;			// ループ用

	//
	// プロクシのポインタと同じプロクシを探しそのキャラクタデータを返す
	// 
	for( i = 0; i < CharManager->charDataNum; i++ ){
		// 稼動中かチェック
		if( CharManager->charDataTbl[ i ].flag != CHAR_MAN_NONE ){
			// IDをチェック
			if( &CharManager->charDataTbl[ i ].ImageProxy == pImage ){
				break;
			}	
		}
	}

	if( i >= CharManager->charDataNum ){
		return NULL;
	}

	return (CharManager->charDataTbl + i);
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	キャラクタデータ転送
 *
 *@param	pCharData	エントリーデータ
 *@param	tbl			キャラクタデータ
 *
 *@return	BOOL	成功：TRUE	失敗：FALSE	（Vramサイズが足りない）
 *
 *
 */
//-----------------------------------------------------------------------------
static BOOL TransCharData(CHAR_DATA_TBL* tbl)
{
	BOOL dell_flag = TRUE;	// Vramに入らないときFALSEになる
	
	// Vram転送かチェック
	if( tbl->vramType ){
		tbl->flag = CHAR_MAN_WAIT_VRAM_ORIG;// Vram転送待機中
	}else{
		tbl->flag = CHAR_MAN_DO_NORMAL;		// 通常使用中

		if(tbl->cont_type == CHARM_CONT_OFFSET){
			// オフセットずらしモード
			dell_flag = TransCharOffset( tbl );
		}else{
			// エリアコントロールモード
			dell_flag = TransCharAreaCont( tbl );
		}
	}

	return dell_flag;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	管理タイプオフセットで転送
 *
 *	@param	tbl		テーブル
 *
 *	@retval	TRUE	転送成功
 *	@retval	FALSE	転送失敗
 *
 *
 */
//-----------------------------------------------------------------------------
static BOOL TransCharOffset(CHAR_DATA_TBL* tbl)
{
	BOOL dell_flag = TRUE;	// Vramに入らないときFALSEになる
	u32 offs_m, offs_s;		// メインサブオフセット

	// オフセット取得
	dell_flag = modeNormOffsetGet( tbl->pCharData->szByte, tbl->type, &offs_m, &offs_s );
	
	if( dell_flag ){
		
		// 転送
		setTransChar( tbl, offs_m, offs_s );
		
		// オフセット移動
		modeNormOffsetMove( tbl->pCharData->szByte, tbl->type );
	}

	return dell_flag;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	管理タイプエリアコントロールで転送
 *
 *	@param	tbl		キャラクタテーブル
 *
 *	@retval	TRUE	転送成功
 *	@retval	FALSE	転送失敗
 *
 *
 */
//-----------------------------------------------------------------------------
static BOOL TransCharAreaCont(CHAR_DATA_TBL* tbl)
{
	u32	offset, offset_sub;		// オフセット
	u32 size_m, size_s;			// 実際に確保したVramサイズ
	BOOL check;

	//
	// Vramのサイズがしようする画面のVramにあるかチェック
	//
	check = getvramTransOffset(tbl->type, &offset, &offset_sub, tbl->pCharData->szByte, &size_m, &size_s);
	// 領域確保失敗
	if( check == FALSE ){
		return FALSE;
	}

	// オフセットをセット
	setvramTransOffsetProxy(tbl, offset, offset_sub);

	// Vramエリア保持
	tbl->have_area = TRUE;
	tbl->have_szByte = size_m;
	tbl->have_szByteSub = size_s;

	// 転送
	transVramChar(tbl);

	// Vram領域フラグを使用中にする
	setvramTransBitData(tbl->type, offset, offset_sub, size_m, size_s);

	return TRUE;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	キャラクタデータを破棄する
 *
 *@param	pCharData：キャラクタデータ
 *
 *@return	 none
 *
 */
//-----------------------------------------------------------------------------
static void dellCharData( CHAR_DATA_TBL* pCharData )
{
	// Vramエリアを保持しているときは返す
	if(pCharData->have_area){		
		delCharTblTransArea( pCharData );	
	}
	
	// データ破棄
	cleanCharData(pCharData);
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	このパスのキャラクタデータの要素数を取得
 *
 *@param	id		キャラクタデータid
 *
 *@return	CHAR_DATA_TBL* キャラクタデータテーブル
 *
 */
//-----------------------------------------------------------------------------
static CHAR_DATA_TBL* getCharDataPtr( int id )
{
	int	i;		// ループ用
	
	// IDのデータを検索してプロクシを返す
	for( i = 0; i < CharManager->charDataNum; i++ ){
		// IDをチェック
		if( CharManager->charDataTbl[i].act_num == id ){
			return &CharManager->charDataTbl[i];
		}	
	}

	return NULL;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	キャラクタモードを合わせる
 *
 *	@param	pCharData	キャラクタデータ
 *	@param	type		Vramタイプ
 *
 *	@return	int		マッピングモード
 *
 *
 */
//-----------------------------------------------------------------------------
static int charModeAdjust( CHAR_DATA_TBL* pCharData, int type )
{
	if(type == NNS_G2D_VRAM_TYPE_2DMAIN){
		pCharData->pCharData->mapingType = GX_GetOBJVRamModeChar();
	}else{
		pCharData->pCharData->mapingType = GXS_GetOBJVRamModeChar();
	}

	return pCharData->pCharData->mapingType;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	キャラクタデータ転送処理をVブランク処理タスクにセット
 *
 *@param	pCharData：キャラクタデータ
 *@param	p_offset：オフセット値
 *@param	p_sub_offset：サブ画面のオフセット値
	*
 *@return	none
 *
 */
//-----------------------------------------------------------------------------
static void setTransChar( CHAR_DATA_TBL* pCharData, u32 p_offset, u32 p_sub_offset )
{
	//
	// offset値をセットしてサイズ分ずらす
	//
	pCharData->offset		= p_offset;
	pCharData->sub_offset	= p_sub_offset;

	// ずらす
	// Vram転送かチェック
	if( !pCharData->vramType )
	{
		// Vram転送
		transVramChar((void*)pCharData);
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	Vramに転送する転送オフセットを取得
 *
 *@param	type		表示先
 *@param	main		メインオフセット格納先
 *@param	sub			サブオフセット格納先
 *@param	szByte		サイズ
 *@param	get_size	メイン実際に確保したサイズ
 *@param	get_size_subサブ実際に確保したサイズ
 *
 *@retval	TRUE	領域確保成功
 *@retval	FALSE	領域確保失敗
 *
 *
 */
//-----------------------------------------------------------------------------
static BOOL getvramTransOffset(int type, u32* main, u32* sub, u32 szByte, u32* get_size, u32* get_size_sub)
{
	u32 size_cm;
	
	
	if( type & NNS_G2D_VRAM_TYPE_2DMAIN ){
		// サイズをキャラクタ境界サイズで割り切れる値にする
		*get_size = getCharModeLimNum( szByte, CharManager->MainModeCharLimit, CHAR_MAN_LIM_ADD );
		
		
		// キャラクタ境界サイズの単位にする
		size_cm = getCharModeNum( *get_size, CharManager->MainModeCharLimit );	

		// メイン画面側
		*main = TransBitCheck( size_cm, CharManager->TransAreaFlagMain );
		
		// エラーが帰ってきたらもう無理
		if( *main == CHAR_VRAM_BANK_GET_ERR ){
			GF_ASSERT(0&&("Vram転送セルの領域取得オーバー"));
			return FALSE;
		}

		// オフセット値をキャラクタ境界サイズからバイトサイズに変更
		*main = getCharModeNum_byte( *main, CharManager->MainModeCharLimit );
	}

	if( type & NNS_G2D_VRAM_TYPE_2DSUB ){
		// サイズをキャラクタ境界サイズで割り切れる値にする
		*get_size_sub = getCharModeLimNum( szByte, CharManager->SubModeCharLimit, CHAR_MAN_LIM_ADD );
		
		// キャラクタ境界サイズの単位にする
		size_cm = getCharModeNum( *get_size_sub, CharManager->SubModeCharLimit );	
		
		// サブ画面側
		*sub = TransBitCheck( size_cm, CharManager->TransAreaFlagSub );

		// エラーが帰ってきたらもう無理
		if( *sub == CHAR_VRAM_BANK_GET_ERR ){
			GF_ASSERT(0&&("Vram転送セルの領域取得オーバー"));
			return FALSE;
		}

		// オフセット値をキャラクタ境界サイズからバイトサイズに変更
		*sub = getCharModeNum_byte( *sub, CharManager->SubModeCharLimit );
	}

	return TRUE;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	プロクシにVram転送用オフセットを設定
 *
 *@param	data	キャラクタデータテーブル
 *@param	main	メインオフセット
 *@param	sub		サブオフセット
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void setvramTransOffsetProxy(CHAR_DATA_TBL* data, u32 main, u32 sub)
{
	if( data->type & NNS_G2D_VRAM_TYPE_2DMAIN ){		// メイン画面表示の時
		data->offset = main + CharManager->MainVramTransStart;
	}
	if( data->type & NNS_G2D_VRAM_TYPE_2DSUB ){			// サブ画面表示の時
		data->sub_offset = sub + CharManager->SubVramTransStart;
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	プロクシにVram転送用オフセットを設定
 *
 *@param	type	画面タイプ
 *@param	main	メインオフセット
 *@param	sub		サブオフセット
 *@param	szByte		メインサイズ
 *@param	szByteSub	サブサイズ
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void setvramTransBitData(int type, u32 main, u32 sub, u32 szByte, u32 szByteSub)
{
	int size_cm;
	int offs_cm;
	
	
	if( type & NNS_G2D_VRAM_TYPE_2DMAIN ){		// メイン画面表示の時
		size_cm = getCharModeNum( szByte, CharManager->MainModeCharLimit );	
		offs_cm = getCharModeNum( main, CharManager->MainModeCharLimit );	
		TransBitSet( offs_cm, size_cm, CharManager->TransAreaFlagMain );

	}
	if( type & NNS_G2D_VRAM_TYPE_2DSUB ){			// サブ画面表示の時
		size_cm = getCharModeNum( szByteSub, CharManager->SubModeCharLimit );	
		offs_cm = getCharModeNum( sub, CharManager->SubModeCharLimit );	
		TransBitSet( offs_cm, size_cm, CharManager->TransAreaFlagSub );
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	Vblank内で行うキャラクタデータのVramへの転送
 *
 *@param	p_data：転送するキャラクタデータ
 *
 *@return	none
 *
 */
//-----------------------------------------------------------------------------
static void transVramChar( void* p_data )
{
	CHAR_DATA_TBL* p_char_data = (CHAR_DATA_TBL*)p_data;		// キャストしてデータ取得
	int mapping_mode;		// マッピングモード

	// プロクシの初期化
	NNS_G2dInitImageProxy(&p_char_data->ImageProxy);
	
	//
	// Vramへ読み込む
	//
	if( p_char_data->type != NNS_G2D_VRAM_TYPE_MAX )
	{
		
		transVramCharCore( p_char_data, p_char_data->type);
	}
	else
	{
		// 両方に登録
		transVramCharCore( p_char_data, NNS_G2D_VRAM_TYPE_2DMAIN);
		
		transVramCharCore( p_char_data, NNS_G2D_VRAM_TYPE_2DSUB);
		
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	転送コア関数
 *
 *	@param	data			キャラクタデータ
 *	@param	vram_type		Vramタイプ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void transVramCharCore( CHAR_DATA_TBL* data, int vram_type)
{
	int mapping_mode;
	int offset;
	u32 before_mapping;
	
	if(data->mapModeAdjust){
		mapping_mode = charModeAdjust( data, vram_type );
	}else{
		mapping_mode = vram_type;
	}

	if(vram_type == NNS_G2D_VRAM_TYPE_2DMAIN){
		offset = data->offset;
		before_mapping = GX_GetOBJVRamModeChar();
	}else{
		offset = data->sub_offset;
		before_mapping = GXS_GetOBJVRamModeChar();
	}
	
	if(mapping_mode == GX_OBJVRAMMODE_CHAR_2D){
		NNS_G2dLoadImage2DMapping( 
				data->pCharData,		// キャラクタデータ
				offset,					// キャラクタベースアドレス
				vram_type,					// VramType
				&data->ImageProxy );	// イメージプロクシ
	}else{
		NNS_G2dLoadImage1DMapping( 
				data->pCharData,		// キャラクタデータ
				offset,					// キャラクタベースアドレス
				vram_type,					// VramType
				&data->ImageProxy );	// イメージプロクシ
		
	}

	if(vram_type == NNS_G2D_VRAM_TYPE_2DMAIN){
		if(GX_GetOBJVRamModeChar() != before_mapping){
			OS_Printf("キャラ転送によりOBJマッピングモードが変更されました\n");
		}
	}
	else{
		if(GXS_GetOBJVRamModeChar() != before_mapping){
			OS_Printf("キャラ転送によりOBJマッピングモードが変更されました\n");
		}
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	Vblank内で行うキャラクタデータのVramへの転送
 *						Vram転送アニメモードのキャラクタ
 *
 *@param	p_data：転送するキャラクタデータ
 *
 *@return	none
 *
 */
//-----------------------------------------------------------------------------
static void transVramCharVramMode( void* p_data )
{
	CHAR_DATA_TBL* p_char_data = (CHAR_DATA_TBL*)p_data;		// キャストしてデータ取得

	// プロクシの初期化
	NNS_G2dInitImageProxy(&p_char_data->ImageProxy);
	
	//
	// Vramへ読み込む
	//
	if( p_char_data->type != NNS_G2D_VRAM_TYPE_MAX )
	{
		transVramCharVramModeCore( p_char_data, p_char_data->type );
	}
	else
	{
		// 両方に登録
		transVramCharVramModeCore( p_char_data, NNS_G2D_VRAM_TYPE_2DMAIN );
		transVramCharVramModeCore( p_char_data, NNS_G2D_VRAM_TYPE_2DSUB );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	VRAM転送Core
 */
//-----------------------------------------------------------------------------
static void transVramCharVramModeCore( CHAR_DATA_TBL* data, int vram_type)
{
	int mapping_mode;
	int offset;
	u32 before_mapping;
	
	if(data->mapModeAdjust){
		mapping_mode = charModeAdjust( data, vram_type );
	}else{
		mapping_mode = vram_type;
	}

	if(vram_type == NNS_G2D_VRAM_TYPE_2DMAIN){
		offset = data->offset;
		before_mapping = GX_GetOBJVRamModeChar();
	}else{
		offset = data->sub_offset;
		before_mapping = GXS_GetOBJVRamModeChar();
	}
	
	NNS_G2dLoadImageVramTransfer( 
			data->pCharData,		// キャラクタデータ
			offset,					// キャラクタベースアドレス
			vram_type,				// VramType
			&data->ImageProxy );	// イメージプロクシ

	if(vram_type == NNS_G2D_VRAM_TYPE_2DMAIN){
		if(GX_GetOBJVRamModeChar() != before_mapping){
			OS_Printf("キャラ転送によりOBJマッピングモードが変更されました\n");
		}
	}
	else{
		if(GXS_GetOBJVRamModeChar() != before_mapping){
			OS_Printf("キャラ転送によりOBJマッピングモードが変更されました\n");
		}
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	空のデータテーブルを取得
 *
 *@param	none
 *	
 *@return	CHAR_DATA_TBL* 型：からのテーブル	NULLの時はもう空のテーブルがない
 *
 */
//-----------------------------------------------------------------------------
static CHAR_DATA_TBL* getCharData( void )
{
	int i;		// ループ用
	
	//
	// 空のデータテーブルを取得
	//
	for( i = 0; i < CharManager->charDataNum; i++ ){
		// あいているところをサーチ
		if( CharManager->charDataTbl[ i ].flag == CHAR_MAN_NONE ){
			return &CharManager->charDataTbl[ i ];
		}
	}

	return NULL;		// 登録不可能
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	  オブジェのVramサイズをセット
 *
 *@param	 none
 *
 *@return	 none
 *
 */
//-----------------------------------------------------------------------------
static void setObjVramSize( void )
{
	GXVRamOBJ vram_bank;			// Vramバンク取得用
	GXVRamSubOBJ sub_vram_bank;		// サブ画面のVramバンク取得用
	int vram_cont_area_size;
	
	//
	// Vramバンクの状態を取得して
	// Vramサイズセット
	//
	// メイン側
	vram_bank = GX_GetBankForOBJ();
	switch( vram_bank ){
	case GX_VRAM_OBJ_NONE:		// なし
		CharManager->MainObjVramSize = 0;
		break;

	case GX_VRAM_OBJ_16_F:		// 16KByte
	case GX_VRAM_OBJ_16_G:
		CharManager->MainObjVramSize = 16 * 1024;
		break;

	case GX_VRAM_OBJ_32_FG:		// 32KByte
		CharManager->MainObjVramSize = 32 * 1024;
		break;

	case GX_VRAM_OBJ_64_E:		// 64KByte
		CharManager->MainObjVramSize = 64 * 1024;
		break;

	case GX_VRAM_OBJ_80_EF:		// 80KByte
	case GX_VRAM_OBJ_80_EG:
		CharManager->MainObjVramSize = 80 * 1024;
		break;

	case GX_VRAM_OBJ_96_EFG:	// 96KByte
		CharManager->MainObjVramSize = 96 * 1024;
		break;

	case GX_VRAM_OBJ_128_A:		// 128KByte
	case GX_VRAM_OBJ_128_B:
		CharManager->MainObjVramSize = 128 * 1024;	
		break;

	case GX_VRAM_OBJ_256_AB:	// 256KByte
		CharManager->MainObjVramSize = 256 * 1024;
		break;

	default:
		CharManager->MainObjVramSize = 0;
		break;
	}
	
	// サブ側
	sub_vram_bank = GX_GetBankForSubOBJ();
	switch( sub_vram_bank ){
	case GX_VRAM_SUB_OBJ_NONE:		// なし
		CharManager->SubObjVramSize = 0;
		break;

	case GX_VRAM_SUB_OBJ_16_I:		// 16KByte
		CharManager->SubObjVramSize = 16 * 1024;
		break;

	case GX_VRAM_SUB_OBJ_128_D:		// 128KByte
		CharManager->SubObjVramSize = 128 * 1024;	
		break;

	default:
		CharManager->SubObjVramSize = 0;
		break;
	}

	//
	// Vram転送用管理領域スタート位置 
	//
	vram_cont_area_size = getCharModeNum_byte( CharManager->TransAreaMainSize, CharManager->MainModeCharLimit );
	CharManager->MainVramTransStart = CharManager->MainObjVramSize - vram_cont_area_size;
	
	vram_cont_area_size = getCharModeNum_byte( CharManager->TransAreaSubSize, CharManager->SubModeCharLimit );
	CharManager->SubVramTransStart = CharManager->SubObjVramSize - vram_cont_area_size;

	//
	// Vram転送用管理領域スタート位置が０未満になったらエラーをプリントする
	//
	GF_ASSERT_MSG( ((CharManager->MainVramTransStart >= 0)&&(CharManager->SubVramTransStart >= 0)),
				"warning：Vram転送用セルのVram領域管理領域のサイズより、Vramバンクの割り当てが少ないです。\n" );
	GF_ASSERT_MSG( ((CharManager->MainVramTransStart >= 0)&&(CharManager->SubVramTransStart >= 0)),
				"warning：Vram転送用セルのVram領域はメイン[byte] サブ[byte]です。\n" );
}

//
// Vram領域管理用
//
// この管理領域は"InitCharManager()関数"に渡した、Vram用領域サイズ分確保されます。
//　配置位置は"CharManager->MainVramTransStart""CharManager->SubVramTransStart"
//	から"CharManager->TransAreaMainSize","CharManager->TransAreaSubSize"分です。
//
//----------------------------------------------------------------------------
/**
 *
 *@brief	メイン、サブの両管理領域を初期化
 *
 *@param	none
 *
 *@return	none
 *
 */
//-----------------------------------------------------------------------------
void TransAreaInitAll( void )
{
	TransAreaInit( CharManager->TransAreaFlagMain );
	TransAreaInit( CharManager->TransAreaFlagSub );
}
//----------------------------------------------------------------------------
/**
 *
 *@brief	  Vram転送セル用Vram管理領域を作成
 *
 *@param	main_size：メイン画面側のサイズ(キャラクタ境界サイズ)
 *@param	sub_size：サブ画面側のサイズ(キャラクタ境界サイズ)
 *@param	main_limit	メイン画面キャラクタ境界
 *@param	sub_limit	サブ画面キャラクタ境界
 *
 *@return	none
 *
 */
//-----------------------------------------------------------------------------
static void MakeTransArea( u32 main_size, u32 sub_size, int heap )
{
	//
	// サイズを変数に格納し、管理領域を再取得する
	//
	CharManager->TransAreaMainSize = main_size;
	CharManager->TransAreaSubSize = sub_size;

	// 領域解放
	if(CharManager->TransAreaFlagMain != NULL){
		sys_FreeMemoryEz( CharManager->TransAreaFlagMain );
	}
	if(CharManager->TransAreaFlagSub != NULL){
		sys_FreeMemoryEz( CharManager->TransAreaFlagSub );
	}

	// 領域確保
	if(CharManager->TransAreaMainSize != 0){
		CharManager->TransAreaFlagMain = sys_AllocMemory( heap, sizeof(u8) * (main_size / 8) );
	}
	if(CharManager->TransAreaSubSize != 0){
		CharManager->TransAreaFlagSub = sys_AllocMemory( heap, sizeof(u8) * (sub_size / 8) );
	}

	// 領域を初期化
	TransAreaInitAll();
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	  Vram転送セル用Vram管理領域を破棄
 *
 *@param	p_trans_flag：メイン画面かサブ画面かのフラグ
 *
 *@return	none
 *
 */
//-----------------------------------------------------------------------------
static void DellTransArea( u8* p_trans_flag )
{	
	// NULL チェック
	if(p_trans_flag != NULL){
		//
		// メイン画面サブ画面どっちかチェック
		//
		if( p_trans_flag == CharManager->TransAreaFlagMain ){
			CharManager->TransAreaMainSize = 0;

			// 破棄
			sys_FreeMemoryEz( p_trans_flag );	
		}else{
			CharManager->TransAreaSubSize = 0;

			// 破棄
			sys_FreeMemoryEz( p_trans_flag );
		}

		p_trans_flag = NULL;
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	メイン、サブの両管理領域のサイズを取得
 *
 *@param	p_trans_flag：メインかサブのフラグ
 *
 *@return	キャラクタサイズ
 *
 * 
 */
//-----------------------------------------------------------------------------
static u32 getTransAreaSize( u8* p_trans_flag )
{
	//
	// メイン面かサブ面かチェック
	//
	if( p_trans_flag == CharManager->TransAreaFlagMain ){
		return 	CharManager->TransAreaMainSize;
	}
	
	return CharManager->TransAreaSubSize;
}



//----------------------------------------------------------------------------
/**
 *
 *@brief	転送先エリアのフラグの初期化
 *
 *@param	p_trans_flag：メインかサブのフラグ
 *
 *@return	none
 *
 */
//-----------------------------------------------------------------------------
static void TransAreaInit( u8* p_trans_flag )
{
	int i;					// ループ用
	u32	char_vram_max;		// 領域最大数セット用

	// NULLチェック
	if( p_trans_flag != NULL ){
	
		// サイズ取得
		char_vram_max = getTransAreaSize( p_trans_flag );

		
		//
		// 領域の初期化
		memset( p_trans_flag, 0, sizeof(u8) * (char_vram_max / 8) );
/*		for( i = 0; i < char_vram_max / 8; i++ )
		{
			p_trans_flag[ i ] = 0;
		}//*/
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	バイトを指定して使用中をセット
 *
 *@param	num		開始バイト
 *@param	size	使用サイズ		単位（キャラクタ境界サイズ）
 *@param	p_trans_flag：メインかサブのフラグ
 *
 *@return	none
 *
 */
//-----------------------------------------------------------------------------
static void TransBitSet( u32 num, u32 size, u8* p_trans_flag )
{
	int i;			// ループ用
	u32	char_vram_max;		// 領域最大数セット用


	
	// NULL チェック
	if(p_trans_flag != NULL){
		
		// サイズ取得
		char_vram_max = getTransAreaSize( p_trans_flag );
		
		//
		// 転送フラグに１をセットしていく
		//
		for( i = num; i < num + size; i++ )
		{
			u32 byte8;
			u8 byte1, mask;
			
			// オーバーしたら抜ける
			if( i >= char_vram_max )
			{
				break;
			}
				
			// セット
			byte8_byte1_Get( i, &byte8, &byte1 );

			// 今からたたせるところがすでにたたされている
			GF_ASSERT( (p_trans_flag[ byte8 ] & (1 << byte1)) == 0 );

			mask = (1 << byte1);
			p_trans_flag[ byte8 ] |= mask;
		}
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	サイズ分の領域が開いているかチェック
 *
 *@param	size：サイズ	単位（キャラクタ境界サイズ）
 *@param	p_trans_flag	メインかサブのフラグ
 *
 *@return	オフセット	単位（キャラクタ境界サイズ）
 *				だめなときは0xffffffff(CHAR_VRAM_BANK_GET_ERR)
 *
 */
//-----------------------------------------------------------------------------
static u32 TransBitCheck( u32 size, u8* p_trans_flag )
{
	int i, j;			// ループ用
	u32	char_vram_max;		// 領域最大数セット用
	
	// NULL チェック
	if(p_trans_flag != NULL){

		// サイズ取得
		char_vram_max = getTransAreaSize( p_trans_flag );
		
		// 転送サイズ分あいているかチェック
		for( i = 0; i < char_vram_max; i++ )
		{
			u32 byte8;
			u8 byte1, mask;
			// あいているかチェック
			byte8_byte1_Get( i, &byte8, &byte1 );
			mask = (1 << byte1);

			// チェック
			j = 0;
			while( ((p_trans_flag[ byte8 ] & mask) == 0) && (j <= size) ){
				int num = i + j;
				byte8_byte1_Get( num, &byte8, &byte1 );
				mask = (1 << byte1);

				// numがchar_vram_max以上なら抜ける
				if( num >= char_vram_max ){
					return CHAR_VRAM_BANK_GET_ERR;
				}
				
				j++;
			}

			// sizeになったら抜ける
			if( j > size ){
				return i;
			}

			i += j;
		}
	}
	return CHAR_VRAM_BANK_GET_ERR;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	指定された転送先エリアのフラグの初期化
 *
 *@param	start_num		初期化開始バイト数	単位（キャラクタ境界サイズ）
 *@param	size			初期化サイズ		単位（キャラクタ境界サイズ）
 *@param	limit			キャラクタ境界
 *@param	p_trans_flag	メインかサブのフラグ
 *
 *@return	none
 *
 */
//-----------------------------------------------------------------------------
static void TransBitClean( u32 start_num, u32 size, u8* p_trans_flag )
{
	int i;			// ループ用


	// NULL チェック
	if(p_trans_flag != NULL){
		// 領域の初期化
		for( i = start_num; i < start_num + size; i++ )
		{
			u32 byte8;
			u8 byte1, mask;
			
			// 初期化
			byte8_byte1_Get( i, &byte8, &byte1 );

			// 今から消すところがすでに消されている
			GF_ASSERT( (p_trans_flag[ byte8 ] & (1 << byte1)) );

			mask = (1 << byte1) ^ 0xff;
			p_trans_flag[ byte8 ] &= mask;
		}
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	キャラクタテーブルの転送エリアを開放
 *
 *	@param	pCharData	キャラクタデータ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void delCharTblTransArea( CHAR_DATA_TBL* pCharData )
{
	u32	offs_cm;
	u32 size_cm;
	
	//
	// セルVramアニメの領域を開放
	//
	if( pCharData->type & NNS_G2D_VRAM_TYPE_2DMAIN ){
		offs_cm = getCharModeNum( NNS_G2dGetImageLocation(&pCharData->ImageProxy,NNS_G2D_VRAM_TYPE_2DMAIN ) - CharManager->MainVramTransStart, CharManager->MainModeCharLimit );
		size_cm = getCharModeNum( pCharData->have_szByte, CharManager->MainModeCharLimit  );
		TransBitClean( offs_cm,
				size_cm,
				CharManager->TransAreaFlagMain );

	}
	
	if( pCharData->type & NNS_G2D_VRAM_TYPE_2DSUB ){
		offs_cm = getCharModeNum( NNS_G2dGetImageLocation(&pCharData->ImageProxy,NNS_G2D_VRAM_TYPE_2DSUB ) - CharManager->SubVramTransStart, CharManager->SubModeCharLimit );
		size_cm = getCharModeNum( pCharData->have_szByteSub, CharManager->SubModeCharLimit );
		TransBitClean( offs_cm,
				size_cm,
				CharManager->TransAreaFlagSub );
	}
	pCharData->have_area = FALSE;	// Vramエリア解放したので
}


//----------------------------------------------------------------------------
/**
 *
 *	@brief	キャラクタモードから何キャラずつ転送するべきか取得
 *
 *	@param	mode		キャラクタモード
 *
 *	@return	int			転送するべきキャラクタ数
 *
 *
 */
//-----------------------------------------------------------------------------
int CharModeMinNum( int mode )
{
	int char_num;
	
	switch(mode){
	case GX_OBJVRAMMODE_CHAR_1D_32K:
		char_num = 1;
		break;
	case GX_OBJVRAMMODE_CHAR_1D_64K:
		char_num = 2;
		break;
	case GX_OBJVRAMMODE_CHAR_1D_128K:
		char_num = 4;
		break;
	case GX_OBJVRAMMODE_CHAR_1D_256K:
		char_num = 8;
		break;
	default:
		char_num = 1;
		break;
	}

	return char_num;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	リミットの値にあわせる
 *
 *	@param	num		リミットにあわせる値
 *	@param	limit	リミット
 *	@param	flag	切り取りか埋めるかのフラグ
 *
 *	@return	int		リミットにあわせた値
 *
 *flag
 *	CHAR_MAN_LIM_SUB,		// あまりを切り取る
 *	CHAR_MAN_LIM_ADD		// あまりを埋める
 *
 */
//-----------------------------------------------------------------------------
static int getCharModeLimNum( int num, int limit, int flag )
{
	if( num % limit ){
		num -= (num % limit);
		if( flag == CHAR_MAN_LIM_ADD ){
			num += limit;
		}
	}

	return num;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	キャラクタ境界でのサイズを取得
 *
 *	@param	szByte	バイトサイズ
 *	@param	limit	キャラクタ境界
 *
 *	@return	int		キャラクタ境界でのサイズ
 *
 *
 */
//-----------------------------------------------------------------------------
static int getCharModeNum( int szByte, int limit )
{
	szByte /= CHAR_ONE_SIZE;
	szByte /= limit;
	
	return szByte; 
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	キャラクタ境界サイズからバイトサイズに変更
 *
 *	@param	szChar	キャラクタ境界サイズの値
 *	@param	limit	キャラクタ境界数
 *
 *	@return	int		バイトサイズ
 *
 *
 */
//-----------------------------------------------------------------------------
static int getCharModeNum_byte( int szChar, int limit )
{
	szChar *= limit;
	szChar *= CHAR_ONE_SIZE;
	return szChar; 
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	ノーマルコントロールタイプ時の今転送すべきオフセット値を取得
 *
 *	@param	szByte		転送データサイズ
 *	@param	type		転送先
 *	@param	offs_main	メイン転送先格納先
 *	@param	offs_sub	サブ転送先格納先
 *
 *	@retval	TRUE	転送する領域があった
 *	@retval	FALSE	領域なし	offs_main offs_subの値無効
 *
 *
 */
//-----------------------------------------------------------------------------
static BOOL modeNormOffsetGet( u32 szByte, int type, u32* offs_main, u32* offs_sub )
{
	BOOL ret = TRUE;
	
	// メイン画面かサブ画面かチェック
	if( type & NNS_G2D_VRAM_TYPE_2DMAIN ){
		// Vramリミットチェック
		if( (CharManager->Offset + szByte) > CharManager->MainVramTransStart ){
			GF_ASSERT(0);
			ret = FALSE;
		}else{

			*offs_main = CharManager->Offset;
		}
	}
	if( type & NNS_G2D_VRAM_TYPE_2DSUB ){
		// Vramリミットチェック
		if( (CharManager->SubOffset + szByte) > CharManager->SubVramTransStart ){
			GF_ASSERT(0);
			ret = FALSE;
		}else{

			*offs_sub = CharManager->SubOffset;
		}
	}

	return ret;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	グローバルのオフセットをサイズ分ずらす
 *
 *	@param	szByte		バイトサイズ
 *	@param	type		表示先画面
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void modeNormOffsetMove( u32 szByte, int type )
{
	// メイン画面かサブ画面かチェック
	if( type & NNS_G2D_VRAM_TYPE_2DMAIN ){
		CharManager->Offset += szByte;

		// オフセットをキャラクタ境界で割り切れる値にする
		CharManager->Offset = getCharModeLimNum( CharManager->Offset, CharManager->MainModeCharLimit, CHAR_MAN_LIM_ADD );
	}
	if( type & NNS_G2D_VRAM_TYPE_2DSUB ){
		CharManager->SubOffset += szByte;

		CharManager->SubOffset = getCharModeLimNum( CharManager->SubOffset, CharManager->SubModeCharLimit, CHAR_MAN_LIM_ADD );
	}

}

//----------------------------------------------------------------------------
/**
 *	@brief	バイト8バイト1の値を取得
 *
 *	@param	num		値
 *	@param	byte8	8ビット単位の値
 *	@param	byte1	8ビット単位内の1ビット単位の値
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void byte8_byte1_Get( int num, u32* byte8, u8* byte1 )
{
	*byte8 = num >> 3;
	*byte1 = num & 7;
}

//----------------------------------------------------------------------------
/**
 *	@brief	管理領域の禁止設定ﾃﾞｰﾀ作成
 *
 *	@param	areacont_start	管理領域開始オフセット
 *	@param	offset			禁止設定オフセット
 *	@param	size			サイズ
 *	@param	start_offset	開始オフセット格納先
 *	@param	set_size		サイズ格納先
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void getReserveAreaContData( u32 areacont_start, u32 offset, u32 size, int* start_offset, int* set_size )
{
	*start_offset = offset - areacont_start;
	if( *start_offset < 0 ){
		// オフセットを0にして足りない分のサイズをsizeから引くと
		// ちょうど良くなる
		*set_size = size + *start_offset;
		*start_offset = 0;
	}else{
		*set_size = size;
	}
	
}
