//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *@file		touchpanel.c
 *@brief	タッチパネルシステムの実態
 *@author	tomoya takahashi
 *@data		2004.12.03
 *
 */
 //]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
#include "system.h"
#include "assert.h"
#include "calc2d.h"
#define __TOUCHPANEL_SYSTEM_H_GLOBAL
#include "touchpanel_system.h"
#include "bg_system.h"
#include "gflib_os_print.h"

/*-----------------------------------------------------------------------------
 *					定数宣言
 ----------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 *					構造体宣言
 ----------------------------------------------------------------------------*/
//----------------------------------------------------------------------------
/**
 *					プロトタイプ宣言
 */
//-----------------------------------------------------------------------------
//-------------------------------------
/// タッチパネルシステム用
static u32 startSampling( u32 sync );		// サンプリングの開始命令を転送
static u32 stopSampling( void );					// サンプリング停止
//static u32 mainBuff( u32 last_idx );		// バッファにサンプリングデータを格納
static u32 mainBuffComp( u32 type, u32 last_idx, u32 comp_num );	// 圧縮モード
static u32 mainBuffJust( u32 type, u32 last_idx );	// そのままバッファに格納
//static u32 mainBuffNoLoop( u32 type, u32 last_idx, u32 comp_num );				// 上のバッファがループしないバージョン
static void getThisSyncData( TP_ONE_DATA* pData, u32 last_idx );	// このシンクのタッチパネルの情報を取得
static u32 modeBuff( u32 type, u32 last_idx, u32 comp_num );				// バッファリングモードのメイン関数

static void setStartBufferingParam( u32 SampFlag, u32 auto_samp, void* pBuff, u32 buffSize, u32 nowBuffPoint, u32 Sync );
static void oneSyncBuffClean( TPData* pBuff, int num );

//-------------------------------------
// タッチパネル、絵情報用
//
// バッファから頂点とベクトルデータを作成する
static u32 makePointData( TPData* pBuff, u32 size, u16 check_num, Vec2DS32* p_work );
// 存在するべき交点数をチェック
static u8	checkInVector( Vec2DS32* p_main_s, Vec2DS32* p_main_e, Vec2DS32* vect_1, Vec2DS32* vect_2, Vec2DS32* vect_3 );
// 最終点と最初の点をつなげる
static u32	crossToPict( TPData s_TPData, Vec2DS32* p_check, Vec2DS32* p_in, u32 dist );
// 交点までのデータにする
static u32 crossEndPict( Vec2DS32* p_work, u32* p_size, u8 flag );
//----------------------------------------------------------------------------
/**
 *					グローバル変数宣言
 */
//-----------------------------------------------------------------------------
typedef struct {
	TPData* pTouchPanelBuff;					// バッファポインタ格納用
	u32		TouchPanelBuffSize;						// バッファサイズ格納用
	u32		TouchPanelSync;							// １フレームに何回サンプリングするか
	TPData	TouchPanelOneSync[ TP_ONE_SYNC_BUFF ];	// １フレームにサンプリングされたデータ格納用
	u32		TouchPanelNowBuffPoint;					// 今バッファにデータを入れているところ
	u16		TouchPanelSampFlag;						// サンプリングフラグ
	u16		TouchPanelExStop;						// サンプリング強制中止フラグ
} TOUCH_PANEL_WORK;

static TOUCH_PANEL_WORK TPWork;


//----------------------------------------------------------------------------
/**
 *
 *@brief	タッチパネルを使用する準備を行います
 *
 *@param	none
 *
 *@return	none
 *
 */
//-----------------------------------------------------------------------------
void InitTPSystem( void )
{

	// スリープ停止中
	GF_ASSERT( TPWork.TouchPanelExStop == FALSE );
	
	// サンプリングフラグを初期化
	TPWork.TouchPanelSampFlag = TP_SAMP_NONE;
	TPWork.TouchPanelExStop = FALSE;
}


//----------------------------------------------------------------------------
/**
 *@brief	タッチパネルのサンプリング開始
 *
 *@param	p_buff：サンプリングデータを入れるバッファ
 *@param	size：バッファのサイズ
 *@param	sync：１フレームに何回サンプリングするのか(MAX4)
 *
 *@retval	TP_OK：成功
 *@retval　	TP_FIFO_ERR：転送失敗
 *@retval	TP_ERR：転送以外の失敗
 */
//-----------------------------------------------------------------------------
u32 InitTP( TPData* p_buff, u32 size, u32 sync )
{
	int	check_num = 0;
	u32	result;
	int i;

	// スリープ停止中
	GF_ASSERT( TPWork.TouchPanelExStop == FALSE );
	
	// タッチパネルサンプリングシステムにサンプリング開始命令を送り、
	// 正常に実行されたかをチェックする
	// １フレームに５以上サンプリングしようとしたらエラーを返す
	if( (sync >= 5) || (sync <= 0) ){
#ifdef TOUCHPANEL_SYSTEM_OS_PRINTF_ON
		OS_Printf( "１フレームのサンプリングは４が最高です。%dはできません\n", sync );
#endif
		return TP_ERR;
	}

	// サンプリング中なら抜ける
	if( TPWork.TouchPanelSampFlag != TP_SAMP_NONE ){
#ifdef TOUCHPANEL_SYSTEM_OS_PRINTF_ON
		OS_Printf("InitTP：サンプリング中です\n");
#endif
		return TP_ERR;
	}
	
	// サンプリング命令転送
	result = startSampling( sync );

	// 転送に失敗したらエラーを返す
	if( result != TP_OK ){
		return result;
	}

	// サンプリングデータ設定
	setStartBufferingParam( TP_BUFFERING, TRUE,
			p_buff, size, 0,
			sync * 2 ); // 30フレーム動作のため

	return TP_OK;
}

//----------------------------------------------------------------------------
/**
 *@brief	タッチパネルのサンプリング開始	バッファリングなし
 *
 *@param	sync：１フレームに何回サンプリングするのか(MAX4)
 *
 *@retval	TP_OK：成功
 *@retval　	TP_FIFO_ERR：転送失敗
 *@retval	TP_ERR：転送以外の失敗
 */
//-----------------------------------------------------------------------------
u32 InitTPNoBuff( u32 sync )
{
	u32	result;
	int i;

	// スリープ停止中
	GF_ASSERT( TPWork.TouchPanelExStop == FALSE );
	
	// タッチパネルサンプリングシステムにサンプリング開始命令を送り、
	// 正常に実行されたかをチェックする
	// １フレームに５以上サンプリングしようとしたらエラーを返す
	if( (sync >= 5) || (sync <= 0) ){
#ifdef TOUCHPANEL_SYSTEM_OS_PRINTF_ON
		OS_Printf( "１フレームのサンプリングは４が最高です。%dはできません\n", sync );
#endif
		return TP_ERR;
	}

	// サンプリング中なら抜ける
	if( TPWork.TouchPanelSampFlag != TP_SAMP_NONE ){
#ifdef TOUCHPANEL_SYSTEM_OS_PRINTF_ON
		OS_Printf("InitTP：サンプリング中です\n");
#endif
		return TP_ERR;
	}
	
	// サンプリング命令転送
	result = startSampling( sync );

	// 転送に失敗したらエラーを返す
	if( result != TP_OK ){
		return result;
	}

	// サンプリングデータ設定
	setStartBufferingParam( TP_NO_BUFF, TRUE,
			NULL, 0, 0,
			sync * 2 ); // 30フレーム動作のため
	

	return TP_OK;
}


//----------------------------------------------------------------------------
/**
 *	@brief	サンプリング開始時のデータ設定
 *
 *	@param	SampFlag		サンプリングフラグ
 *	@param	auto_samp		AUTOサンプリングフラグ
 *	@param	pBuff			バッファポインタ
 *	@param	buffSize		バッファサイズ
 *	@param	nowBuffPoint	今サンプル中の位置
 *	@param	Sync			シンク数
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void setStartBufferingParam( u32 SampFlag, u32 auto_samp, void* pBuff, u32 buffSize, u32 nowBuffPoint, u32 Sync )
{
	// サンプリングフラグをセット
	TPWork.TouchPanelSampFlag = SampFlag;
	sys.tp_auto_samp = auto_samp;		// システムのフラグをオートサンプリング中にする
	// バッファのポインタとサイズを格納
	TPWork.pTouchPanelBuff = pBuff;
	TPWork.TouchPanelBuffSize = buffSize;
	TPWork.TouchPanelSync = Sync;
	TPWork.TouchPanelNowBuffPoint = nowBuffPoint;
	oneSyncBuffClean( TPWork.TouchPanelOneSync, TP_ONE_SYNC_BUFF );
}

//----------------------------------------------------------------------------
/**
 *	@brief	1シンク用バッファの初期化
 *
 *	@param	pBuff	バッファ
 *	@param	num		数
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void oneSyncBuffClean( TPData* pBuff, int num )
{
	int i;

	for( i = 0; i < num; i++ ){
		pBuff[ i ].touch = 0;
	}	
}

//----------------------------------------------------------------------------
/**
 *	@brief	サンプリング停止
 */
//-----------------------------------------------------------------------------
static u32 stopSampling( void )
{
	u32 check_num = 0;			// ﾁｪｯｸ数
	u32 result;					// 結果
	int	i;						// ループ用

	// 現在のサンプリングを終了する
	// 正常に命令の転送が完了したか管理する
	//
	// 今サンプリングしているのかﾁｪｯｸ
	if( TPWork.TouchPanelSampFlag == TP_SAMP_NONE )
	{
		// サンプリングしていないのでとまった状態です。
		return TP_OK;
	}

	// 終了命令をエラーが帰ってくる間送り続ける
	// （FIFOでARM7に命令を送っているため、同期を取る必要がある）
	do
	{
		// 終了命令を送る
		TP_RequestAutoSamplingStopAsync();
		
		// 命令リクエスト終了待ち
		TP_WaitBusy( TP_REQUEST_COMMAND_FLAG_AUTO_OFF );
	
		// エラー終了していないかチェック
		result = TP_CheckError( TP_REQUEST_COMMAND_FLAG_AUTO_OFF );
		if( result != 0 )
		{
			check_num++;		// エラー数カウント
		}

		// エラーが帰っていて、エラーﾁｪｯｸ数がTP_REQUEST_CHECK_MAX以下の間ループ
	}while( (result != 0) && (check_num <= TP_REQUEST_CHECK_MAX) );


	// check_num が５より大きいときはFALSEを転送
	if( check_num > TP_REQUEST_CHECK_MAX )
	{
#ifdef TOUCHPANEL_SYSTEM_OS_PRINTF_ON
		OS_Printf( "終了命令転送失敗\n" );
#endif
		return TP_FIFO_ERR;
	}
	return TP_OK;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	サンプリングを終了する
 *
 *@param	none
 *
 *@retval	TP_OK：成功
 *@retval　	TP_FIFO_ERR：転送失敗
 *@retval	TP_ERR：転送以外の失敗
 *
 */
//-----------------------------------------------------------------------------
u32 StopTP( void )
{
	u32 result;

	// スリープ停止中
	GF_ASSERT( TPWork.TouchPanelExStop == FALSE );
	
	result = stopSampling();
	if( result == TP_OK ){
		// 格納しておいたデータ破棄
		setStartBufferingParam( TP_SAMP_NONE, 0, NULL, 0, 0, 0 );
	}
	return result;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	サンプリング情報を管理し、今の状態を返す	
 *
 *@param	pData：このフレームの情報(initで指定したサンプリング回数分の情報)
 *@param	type：サンプリング種別の番号
 *@param	comp_num：バッファに格納するときに、comp_num位のさがあったら格納する
 *
 *@return	u32：サンプリング種別による変化
					type：TP_BUFFERING		サンプリングされたバッファサイズ
					type：TP_NO_LOOP		サンプリングされたバッファサイズ
											バッファが一杯になったとき TP_END_BUFF
					type：TP_NO_BUFF		TP_OK

					type：TP_SAMP_NOT_START	サンプリング開始されていません
 */
//-----------------------------------------------------------------------------
u32 MainTP( TP_ONE_DATA* pData, u32 type, u32 comp_num )
{
	u32 ret = TP_SAMP_NOT_START;	// 戻り値
	u32 last_idx;					// 最後にサンプリングされた位置

	// スリープ停止中
	GF_ASSERT( TPWork.TouchPanelExStop == FALSE );

	// サンプリングされているかチェック
	if( TPWork.TouchPanelSampFlag != TP_SAMP_NONE ){

		// 最後にサンプリングした位置を取得
		last_idx  = TP_GetLatestIndexInAuto();
		
		// 画面座標に変更
		ChangeTPDataBuff( TPWork.TouchPanelOneSync, TP_ONE_SYNC_BUFF );

		// このフレームの情報を取得
		if( pData != NULL ){
			getThisSyncData( pData, last_idx );
		}
		
		// typeのバッファリングまたは今のフレーム情報を取得し
		// データをセットして返す
		// まずバッファリングありでInitされているかチェック
		if( TPWork.TouchPanelSampFlag == TP_BUFFERING ){
			ret = modeBuff( type, last_idx, comp_num );	
		}else{
			// その他のときはTP_OKを返す
			ret = TP_OK;
		}
	}else{
#ifdef TOUCHPANEL_SYSTEM_OS_PRINTF_ON
	
		OS_Printf( "MainTP関数 warning：サンプリング開始されていません\n" );
#endif
	}

	return ret;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	生の座標を画面座標にして返す
 *
 *@param	pData：変更するタッチパネルデータ
 *
 *@return	変更後のデータ
 *
 */
//-----------------------------------------------------------------------------
TPData ChangeTPData( TPData* pData )
{
	TPData sample;		// 取得用

	// スリープ停止中
	GF_ASSERT( TPWork.TouchPanelExStop == FALSE );
	
	// 生のタッチパネル値から画面座標に変換して返す
	TP_GetCalibratedPoint( &sample, pData );

	return sample;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	生の座標を画面座標にして返す(TPData配列用)
 *
 *@param	pData：変更するタッチパネルデータ配列
 *@param	size：配列サイズ
 *
 *@return	none
 *
 */
//-----------------------------------------------------------------------------
void ChangeTPDataBuff( TPData* pData, u32 size )
{	
	int i;		// ループ用
	TPData sample;

	// 生のタッチパネル値から画面座標に変換して返す
	for( i = 0; i < size; i++ ){
		TP_GetCalibratedPoint( &sample, &(pData[ i ]) );
		pData[ i ] = sample;
	}
}


//----------------------------------------------------------------------------
/**
 *	@brief	スリープ処理前の停止　
 */
//-----------------------------------------------------------------------------
void ReStartTP_Sleep( void )
{
	u32 result;
	
	// 停止中かチェック
	if( TPWork.TouchPanelExStop == FALSE ){
		return ;
	}
	// サンプリング中かチェック
	if( TPWork.TouchPanelSampFlag == TP_SAMP_NONE ){
		return ;
	}

	// サンプリングを開始させる
	result = startSampling( TPWork.TouchPanelSync / 2 );	// /2は30シンクのため
	GF_ASSERT( result == TP_OK );

	TPWork.TouchPanelExStop = FALSE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	スリープ処理前の復帰
 */
//-----------------------------------------------------------------------------
void StopTP_Sleep( void )
{
	u32 result;
	// すでに停止中かチェック
	if( TPWork.TouchPanelExStop == TRUE ){
		return ;
	}
	// サンプリング中かチェック
	if( TPWork.TouchPanelSampFlag == TP_SAMP_NONE ){
		return ;
	}

	// サンプリングを停止させる
	result = stopSampling();
	GF_ASSERT( result == TP_OK );

	TPWork.TouchPanelExStop = TRUE;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	オートサンプリング開始命令を転送
 *
 *@param	sync：１フレームのサンプリング数
 *
 *@return	TP_OK：成功
 *@return　	TP_FIFO_ERR：転送失敗
 *
 */
//-----------------------------------------------------------------------------
static u32 startSampling( u32 sync )
{
	int	check_num = 0;
	u32	result;


	// 開始命令をエラーが帰ってくる間送り続ける
	// （FIFOでARM7に命令を送っているため、同期を取る必要がある）
	do
	{
		// 開始命令を送る
		TP_RequestAutoSamplingStartAsync( 
				0,			// ベースVカウント
				sync,		// １フレームに何回サンプリングするか
				TPWork.TouchPanelOneSync,				// サンプリングデータ格納用バッファ
				TP_ONE_SYNC_BUFF );		// バッファサイズ
		
		// 命令リクエスト終了待ち
		TP_WaitBusy( TP_REQUEST_COMMAND_FLAG_AUTO_ON );

		// エラー終了していないかチェック
		result = TP_CheckError( TP_REQUEST_COMMAND_FLAG_AUTO_ON );
		if( result != 0 )
		{
			check_num++;		// エラー数カウント
		}

		// エラーが帰っていて、エラーﾁｪｯｸ数がTP_REQUEST_CHECK_MAX以下の間ループ
	}while( (result != 0) && (check_num <= TP_REQUEST_CHECK_MAX) );


	// check_num が５より大きいときはFALSEを転送
	if( check_num > TP_REQUEST_CHECK_MAX )
	{
#ifdef TOUCHPANEL_SYSTEM_OS_PRINTF_ON
		OS_Printf( "スタート命令転送失敗\n" );
#endif
		return TP_FIFO_ERR;
	}

	return TP_OK;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	サンプリング情報を管理し、今の状態を返す
 *			バッファリングモード
 *
 *@param	type：サンプリング種別の番号
 *@param	last_idx：ラストインデックス
 *@param	comp_num：バッファに格納するときに、comp_num位のさがあったら格納する(圧縮モード時のみ)
 *
 *@return	サンプリング種別による変化
					TP_BUFFERING---サンプリングされたバッファサイズ
					TP_NO_LOOP---サンプリングされたバッファサイズ
								 バッファが一杯になったとき TP_END_BUFF
					TP_NO_BUFF---TP_OK
 *
 */
//-----------------------------------------------------------------------------
static u32 modeBuff( u32 type, u32 last_idx, u32 comp_num )
{		
	u32 ret;		// 戻り値
	
	
	//
	// typeのモードでバッファリング
	switch( type ){
	case TP_BUFFERING:
	case TP_NO_LOOP:
		ret = mainBuffComp( type, last_idx, comp_num );
		break;
		
	case TP_BUFFERING_JUST:	// そのまま格納
	case TP_NO_LOOP_JUST:
		ret = mainBuffJust( type, last_idx );
		break;

	default:		// その他
		ret = TP_OK;
		break;			// なにもしない
	}

	return ret;
}

// 通常で圧縮モードに変更
// 圧縮なしでのバッファリングは圧縮値に０を指定すればよい
#if 0
//----------------------------------------------------------------------------
/**
 *
 *@brief	バッファに圧縮なしで、座標を格納
 *
 *@param	last_idx：最後にサンプリングした位置
 *
 *@return	バッファに格納したサイズ
 *
 */
//-----------------------------------------------------------------------------
u32 mainBuff( u32 last_idx )
{
	int i;				// ループ用
	s16	samp_work;		// サンプリング作業用

	//
	// タッチパネルのサンプリング情報を管理し、今の状態を返す
	//	
	// タッチパネルバッファとこのフレームのサンプリングデータ
	// に格納する
	for( i = 0; i < TouchPanelSync; i++ ){
		samp_work = last_idx - TouchPanelSync + i + 1;

		// 0以下のときは最終要素数にする
		if( samp_work < 0 ){
			samp_work += TP_ONE_SYNC_BUFF;
		}

		// 有効なデータの時バッファに格納
		if( (TouchPanelOneSync[ samp_work ].touch == TP_TOUCH_ON) &&
			(TouchPanelOneSync[ samp_work ].validity == TP_VALIDITY_VALID) ){
			// サンプリングデータ格納
			pTouchPanelBuff[ TouchPanelNowBuffPoint ] = TouchPanelOneSync[ samp_work ];				
			TouchPanelNowBuffPoint = (TouchPanelNowBuffPoint + 1) % TouchPanelBuffSize;		// バッファが超えたらループ
		}
	}

	
	// 最後にサンプリングされたインデックスを返す	
	return TouchPanelNowBuffPoint;
}

#endif

static  inline int TouchPanel_GetDiff( int n1, int n2 )
{
	int calc = (n1 >= n2) ? (n1 - n2) : (n2 - n1);
	return calc;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	バッファに圧縮して、座標を格納
 *
 *@param	type		バッファリングタイプ
 *@param	last_idx	最後にサンプリングした位置
 *@param	comp_num	バッファに格納するときに、comp_num位のさがあったら格納する
 *
 *@return	バッファに格納したサイズ
 *
 */
//-----------------------------------------------------------------------------
static u32 mainBuffComp( u32 type, u32 last_idx, u32 comp_num )
{
	int i;				// ループ用
	s32 dist_x;			// 差がどのくらいあるか
	s32 dist_y;			// 差がどのくらいあるか
	s16	samp_work;		// サンプリング作業用

	//
	// タッチパネルのサンプリング情報を管理し、今の状態を返す
	//
	// タッチパネルバッファとこのフレームのサンプリングデータ
	// に格納する
	for( i = 0; i < TPWork.TouchPanelSync; i++ ){
		samp_work = last_idx - TPWork.TouchPanelSync + i + 1;

		// 0以下のときは最終要素数にする
		if( samp_work < 0 ){
			samp_work += TP_ONE_SYNC_BUFF;
		}

		// 有効なデータの時バッファに格納
		if( (TPWork.TouchPanelOneSync[ samp_work ].touch == TP_TOUCH_ON) &&
			(TPWork.TouchPanelOneSync[ samp_work ].validity == TP_VALIDITY_VALID) ){
			// 差を求める
			dist_x = TouchPanel_GetDiff(TPWork.pTouchPanelBuff[ TPWork.TouchPanelNowBuffPoint - 1 ].x, TPWork.TouchPanelOneSync[ samp_work ].x);
			dist_y = TouchPanel_GetDiff(TPWork.pTouchPanelBuff[ TPWork.TouchPanelNowBuffPoint - 1 ].y, TPWork.TouchPanelOneSync[ samp_work ].y);
			
			// 差がcomp_num以上かチェック
			if( (dist_x >= comp_num) ||
				(dist_y >= comp_num)){
					
				// サンプリングデータ格納
				TPWork.pTouchPanelBuff[ TPWork.TouchPanelNowBuffPoint ] = TPWork.TouchPanelOneSync[ samp_work ];				
				TPWork.TouchPanelNowBuffPoint++;
				
				// バッファサイズオーバーチェック
				if(TPWork.TouchPanelNowBuffPoint >= TPWork.TouchPanelBuffSize){
					// バッファをループさせるかチェック
					if(type == TP_BUFFERING){
						TPWork.TouchPanelNowBuffPoint %= TPWork.TouchPanelBuffSize;	// ループさせる
					}else{
						return TP_END_BUFF;		// ループさせない
					}
				}
			}
		}
	}

	
	// 最後にサンプリングされたインデックスを返す	
	return TPWork.TouchPanelNowBuffPoint;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	バッファに有効データ、タッチの判定をせずに格納
 *
 *@param	type		バッファリングタイプ
 *@param	last_idx	最後にサンプリングした位置
 *
 *@return	バッファに格納したサイズ
 *
 */
//-----------------------------------------------------------------------------
static u32 mainBuffJust( u32 type, u32 last_idx )
{
	int i;				// ループ用
	s16	samp_work;		// サンプリング作業用

	//
	// タッチパネルのサンプリング情報を管理し、今の状態を返す
	//
	// タッチパネルバッファとこのフレームのサンプリングデータ
	// に格納する
	for( i = 0; i < TPWork.TouchPanelSync; i++ ){
		samp_work = last_idx - TPWork.TouchPanelSync + i + 1;

		// 0以下のときは最終要素数にする
		if( samp_work < 0 ){
			samp_work += TP_ONE_SYNC_BUFF;
		}

		// サンプリングデータ格納
		TPWork.pTouchPanelBuff[ TPWork.TouchPanelNowBuffPoint ] = TPWork.TouchPanelOneSync[ samp_work ];
		TPWork.TouchPanelNowBuffPoint++;

		// バッファサイズオーバーチェック
		if(TPWork.TouchPanelNowBuffPoint >= TPWork.TouchPanelBuffSize){
			// バッファをループさせるかチェック
			if(type == TP_BUFFERING_JUST){
				TPWork.TouchPanelNowBuffPoint %= TPWork.TouchPanelBuffSize;	// ループさせる
			}else{
				return TP_END_BUFF;		// ループさせない
			}
		}
	}

	
	// 最後にサンプリングされたインデックスを返す	
	return TPWork.TouchPanelNowBuffPoint;
}


// バッファリング処理の分岐はmodeBuff()のみで行うように変更
// 一杯になるかのチェックをmodeBuff()を呼ぶ前に作成し、
// サンプリングは終了しないように変更します		05/03/29	tomoya
#if 0
//----------------------------------------------------------------------------
/**
 *
 *@brief	バッファがループしないようにバッファに格納
 *
 *@param	type：圧縮方式か
 *@param	last_idx：最後にサンプリングした位置
 *@param	comp_num：バッファに格納するときに、comp_num位のさがあったら格納する(圧縮モード時のみ)
 *
 *@return	バッファに格納したサイズ 
 *			バッファが一杯になり、ストップさせたときは TP_END_BUFF
 *
 */
//-----------------------------------------------------------------------------
u32 mainBuffNoLoop( u32 type, u32 last_idx, u32 comp_num )
{
	u32 last_buff;
	int	i;			// ループ用
	
	//
	// タッチパネルのサンプリング情報を管理し、今の状態を返す
	// この関数はバッファをループしないように管理します。
	//
	// 圧縮モードでないかチェック
	switch( type ){
	case TP_NO_LOOP:
		// 圧縮なし
		last_buff = mainBuff( last_idx );
		break;
	
	case TP_NO_LOOP_COMP:
		// 圧縮あり
		last_buff = mainBuffComp( last_idx, comp_num );
		break;

	case TP_NO_LOOP_JUST:
		// そのまま
		last_buff = mainBuffJust( last_idx );
		break;

	default:
		last_buff = 0;
		break;
	}

	// もし次のフレームで最大より大きくなるなら終了
	if( last_buff + TouchPanelSync >= TouchPanelBuffSize )
	{
		// 終わりまで最終の値を入れる
		for( i = last_buff; i < TouchPanelBuffSize; i++ ){
			pTouchPanelBuff[ i ] = pTouchPanelBuff[ i - 1 ];
		}

		// 終了させる必要がないので終了はさせない
//		while( StopTP() != TRUE ) ;

		return TP_END_BUFF;
	}

	return last_buff;
}

#endif

//----------------------------------------------------------------------------
/**
 *
 *@brief	このシンクのサンプリング情報を取得
 *
 *@param	pData：このシンクのデータ保存用領域のポインタ
 *@param	last_idx：最後にサンプリングした位置
 *
 *@return	none
 *
 */
//-----------------------------------------------------------------------------
static void getThisSyncData( TP_ONE_DATA* pData, u32 last_idx )
{
	int i;				// ループ用
	s16	samp_work;		// サンプリング作業用

	//
	// 初期化
	//
	pData->Size = 0;
	for( i = 0; i < TP_ONE_SYNC_DATAMAX; i++ ){
		pData->TPDataTbl[ i ].validity = TP_VALIDITY_VALID;
		pData->TPDataTbl[ i ].touch = TP_TOUCH_OFF;
		pData->TPDataTbl[ i ].x = 0;
		pData->TPDataTbl[ i ].y = 0;
	}
	
	//
	// タッチパネルのサンプリング情報を管理し、今の状態を返す
	//
	// タッチパネルバッファとこのフレームのサンプリングデータ
	// に格納する
	for( i = 0; i < TPWork.TouchPanelSync; i++ ){
		samp_work = last_idx - TPWork.TouchPanelSync + i + 1;

		// 0以下のときは最終要素数にする
		if( samp_work < 0 ){
			samp_work += TP_ONE_SYNC_BUFF;
		}

		//
		// 有効無効データかチェック
		//
		if( TPWork.TouchPanelOneSync[ samp_work ].validity == TP_VALIDITY_VALID ){	
			// このフレームのサンプリング情報を格納
			pData->TPDataTbl[ pData->Size ]  = TPWork.TouchPanelOneSync[ samp_work ];
			pData->Size++;
		}
	}
}

//
/// タッチパネルの絵の情報関係関数
//
//----------------------------------------------------------------------------
/**
 *
 *@brief	タッチパネル情報から絵の情報を作成する
 *
 *@param	u32 type：タイプ
 *@param	TPData* pBuff：タッチパネル情報のバッファ
 *@param	u32 size：バッファの要素数
 *@param	u16 check_num：	タッチパネルの点情報を減らすときの角度
 *							（小さくすると精度が増し、データが多くなる）
 *@param	u32 dist：終点と始点をつなげるときの終点と始点の長さの境界線
					：０なら線と線をつなげない
					：３２０なら線と線を絶対につなげる
 *@param	BOOL* p_cross：絵の情報は交点で閉じているのか
 *@param	heap	使用するヒープ
 *
 *@return	TP_PICTURE_DATA* 型：作成した絵の情報
 *		********交点で閉じていなくてもデータは帰ってくるので、
 *				この関数を読んだら必ず戻り値のデータを破棄する
 *				必要があります。**********
 *		
 *		
 *		頂点数が１～２のサイズの時は閉じていない絵のデータを返します。
 *
 */
//-----------------------------------------------------------------------------
TP_PICTURE_DATA* MakeTPPictureData( u32 type, TPData* pBuff, u32 size, u16 check_num, u32 dist, BOOL* p_cross, int heap )
{
	int i;						// ループ用
	u32 count;					// 必要な頂点とベクトルデータ数
	Vec2DS32* p_work;			// データ作成用の頂点とベクトルのデータ
	TP_PICTURE_DATA* p_ret;		// 戻り値で返す絵データ
	u8	cross_flag = 0;			// 絵のデータが閉じたか
	
	//
	/// タッチパネルの情報から絵の情報を作成する
	/// 絵の情報とは頂点と次の点までのベクトルです。
	/// 内外判定に使用します。
	//
	// 頂点ベクトルデータ作成用領域を確保(作業用で必要最大値分確保)
	p_work = sys_AllocMemory( heap, sizeof(Vec2DS32) * (size + 1) );		// 始点と終点をつなぐ可能性があるので＋１
	

	//
	// 図形データの頂点数初期化
	//
	count = 0;

	//
	// 絵の情報データを作成
	//
	if( size > 3 ){	
		
		// ４以上のときは頂点を減らす
		count = makePointData( pBuff, size, check_num, p_work );
	}else{
		
		// ３以下の時は頂点を減らさせずにそのまま入れる
		for( i = 0; i < size; i++ ){
			p_work[ i ].x = pBuff[ i ].x;
			p_work[ i ].y = pBuff[ i ].y;
			count++;
		}
	}


	// p_cross（閉じているか）を閉じていない（FALSE）で
	// 初期化
	if( p_cross != NULL ){
		*p_cross = FALSE;
	}
	
	//
	// 頂点数が３以下の時は交点はありえない
	//
	if( count > 3 ){
		//
		// 交点が１つモードかチェック
		//
		if( (type == TP_MAKE_PICT_ONE_FAST) || 
			(type == TP_MAKE_PICT_ONE_END)){
			if( crossEndPict( p_work, &count, type ) == 1 ){
				// 閉じたデータになった
				if( p_cross != NULL ){
					*p_cross = TRUE;
				}
				// 閉じた
				cross_flag = 1;
			}
		}
	}

	// 閉じてないかチェック
	if( cross_flag == 0 ){
		//
		// 頂点数が２以下の時は直線なので終点と先頭をつなげる必要がない
		//
		if( count > 2 ){
	
			//
			// 終点と先頭をつなげるかチェック
			//
			if( crossToPict( pBuff[ 0 ], &p_work[ count - 1 ], &p_work[ count ], dist ) == 1 ){
				count++;		// データを入れた分カウント

				// 閉じたデータになった
				if( p_cross != NULL ){
					*p_cross = TRUE;
				}
			}
		}
	}

		
		
	//
	// 作成した頂点とベクトルデータをTP_PICTURE_DATAデータにコピー
	//
	p_ret				= sys_AllocMemory( heap, sizeof(TP_PICTURE_DATA) );
	p_ret->pPointData	= sys_AllocMemory( heap, sizeof(Vec2DS32) * count );
	p_ret->Size			= count;



	// コピー
	for( i = 0; i < count; i++ )
	{
		p_ret->pPointData[ i ] = p_work[ i ];

#if 0
		// コピーしながら描画(デバック用)
		if( i > 0 ){
			drawVect( &p_ret->pPointData[ i - 1 ], &p_ret->pPointData[ i ] );
		}

		DrawTPPaste();
#endif
	}


	// 作業用領域を破棄
	sys_FreeMemoryEz( p_work );

	return p_ret;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	終点と始点を繋げる
 *
 *@param	TPData s_TPData：始点のデータ
 *@param	Vec2DS32* p_check：終点のポインタ
 *@param	Vec2DS32* p_in：格納する位置のポインタ
 *@param	u32 dist：離れていてよい距離
 *
 *@return	u32型：つなげたか　１：繋げた
 *
 */
//-----------------------------------------------------------------------------
static u32	crossToPict( TPData s_TPData, Vec2DS32* p_check, Vec2DS32* p_in, u32 dist )
{
	//
	// 終点と先頭をつなげるかチェック
	//
	if( GetVectorDistance( s_TPData.x, s_TPData.y,
				p_check->x, p_check->y ) <= dist ){
		// 先頭とくっつける
		// タッチパネルの情報の有効な最初のデータと有効な最後のデータのベクトルを最後にセットする
		//
		p_in->x = s_TPData.x;		// ベクトル座標
		p_in->y = s_TPData.y;		// ベクトル座標

		return 1;
	}

	return 0;
}


//----------------------------------------------------------------------------
/**
 *
 *@brief	p_workのデータを交点までのデータにする
 *
 *@param	Vec2DS32* p_work：絵のデータ
 *@param	u32* p_size：そのデータ
 *@param	u8 flag：一番最初の交点のデータにするか、最後の交点のデータにするか
 *
 *@return	u32型：交点があったか １：あった
 *
 */
//-----------------------------------------------------------------------------
static u32 crossEndPict( Vec2DS32* p_work, u32* p_size, u8 flag )
{
	int i, j;					// ループ用
	int cross_i, cross_j;		// 交点のあったiとjの値
	Vec2DS32 cross_mat;			// 交点座標
	Vec2DS32 cross_tmp;			// 交点座標保存用
	u8	cross_num;				// 交点があった数
	
	
	// フラグを初期化
	cross_num = 0;

	//
	// 先頭のベクトルから交点の位置を求める
	//
	for( i = 0; i < *p_size - 1; i++ ){
		for( j = *p_size - 2; j >= 0; j-- ){
			// もしiとjが逆転したらもう交点はない
			if( i + 1 >= j ){
				break;
			}
			
			if( CheckCrossMatrix( &p_work[ i ], &p_work[ i + 1 ],
								  &p_work[ j ], &p_work[ j + 1 ], 
								  &cross_mat) == 1 )
			{
				cross_i = i;			// 交点のあったi
				cross_j = j;			// 交点のあったj
				cross_num++;			// 交点数カウント
				cross_tmp = cross_mat;	// 交点保存
				break;
			}
		}

		// 交点があったかチェック
		if( (cross_num == 1) && (flag == TP_MAKE_PICT_ONE_FAST) ){
			break;
		}
	}

	//
	// 交点があったかチェック
	//
	if( cross_num > 0 ){
		//
		// i + 1とｊが交点のあったベクトルの先頭の頂点
		// cross_matの中身が交点の座標
		// 
		// p_workの0と最後のデータの位置に交点座標をセットし、i未満とjより大きい情報を削除
		p_work[ 0 ] = cross_tmp;
	
		*p_size = 1;
		// iの情報を０からj - (i +1)になるまでつめる
		for( i = cross_i + 1; i < cross_j; i++ ){
			p_work[ *p_size ] = p_work[ i ];
			(*p_size)++;		// データ数カウント
		}
		p_work[ *p_size ] = cross_tmp;
		(*p_size)++;		// データ数カウント
		return 1;
	}

	return 0;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	ピクチャーデータを破棄する
 *
 *@param	TP_PICTURE_DATA* pPictData：絵のデータ
 *
 *@return	なし
 *
 */
//-----------------------------------------------------------------------------
void DestTPPictureData( TP_PICTURE_DATA* pPictData )
{
	//
	// ピクチャーデータを破棄
	//
	if( pPictData != NULL ){
		sys_FreeMemoryEz( pPictData->pPointData );
		sys_FreeMemoryEz( pPictData );
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	タッチパネルデータから頂点とベクトルのデータを作成する
 *
 *@param	Vec2DS32* p_point：頂点とベクトルデータ
 *
 *@return	u32型：データ数
 *
 */
//-----------------------------------------------------------------------------
static u32 makePointData( TPData* pBuff, u32 size, u16 check_num, Vec2DS32* p_work )
{
	int	i, j;			// ループ用
	u32 count;			// カウンタ
	u32	next;			// チェックする次の頂点

	
	//
	// 絵の情報作成
	//
	count = 0;		// カウンタ初期化
	i = 0;
	while( i <= size - 3 ){

		// 次の点をセット	
		next = i + 1;
		// チェックすベクトル２の要素数をjにセット
		j = next + 1;
		
		while( GetVectorAngle( 
				pBuff[ i ].x, pBuff[ i ].y,
				pBuff[ next ].x, pBuff[ next ].y,
				pBuff[ i ].x, pBuff[ i ].y,
				pBuff[ j ].x, pBuff[ j ].y ) <= check_num ){
			//
			// 絵の情報にセットする点を探す
			//
			j++;

			// サイズになったら終了
			if( j >= size )
			{
				break;		// 要素のマックスになったら抜ける
			}
		}

		//
		// iの点をセット<F9>
		// j - 1の点までは格納しなくてよい。j - 1からチェックしていく
		//
		p_work[ count ].x = pBuff[ i ].x;		// ベクトル開始座標
		p_work[ count ].y = pBuff[ i ].y;		// ベクトル開始座標
		count++;

		// 終点の(j - 1)の値をiにセット
		i = j - 1;

	}
	
	// 
	// 点が残り２つ以下になってしまったのでチェックできないため
	// 最後にiからsize -1の値になるまで座標を入れる
	// 
	while( i < size ){
		p_work[ count ].x = pBuff[ i ].x;
		p_work[ count ].y = pBuff[ i ].y;
		count++;
		i++;
	}

	return count;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	内外判定
 *
 *@param	TP_PICTURE_DATA* pData：絵のデータ
 *@param	u16 x：判定座標横
 *@param	u16 y：判定座標たて
 *
 *@return	u32型：０：外　１：内
 *
 */
//-----------------------------------------------------------------------------
u32 CheckTPPictureInOut( TP_PICTURE_DATA* pData, u16 x, u16 y )
{
	return CheckInOut( pData->pPointData, pData->Size, x, y );
}
