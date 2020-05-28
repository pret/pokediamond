#ifndef __BEACONDOWNLOAD__
#define __BEACONDOWNLOAD__
/**
 * @version "$Id: beacondownload.h,v 1.3 2006/07/05 13:50:25 mitsuhara Exp $"
 *
 * @file beacondownload.h
 * @brief ビーコンを使用したデータダウンロード処理
 * 
 */
 
#ifndef BEACONDOWNLOAD
#define DEBUG_BEACONDOWNLOAD	1
#endif

// コールバック型
typedef void (*BSDOWN_CALLBACK)( int code );

// 以下の処理がおこなわれたときにコールバックが返ります。
enum
{
	BSDOWNCALLBACK_STARTSCAN,	// スキャン開始時
	BSDOWNCALLBACK_START,		// 親機をみつけたとき
	BSDOWNCALLBACK_SUCCESS,		// データを完全に受け取ったとき
	BSDOWNCALLBACK_FINISH,		// 無線の終了処理（キャンセル時、データを完全に受け取ったとき共通）
	BSDOWNCALLBACK_ERROR,		// エラー発生時
	BSDOWNCALLBACK_RESTART,		// 受信中に親機が情報を変更した場合など、データに食い違いが生じた場合。
								//　この場合、自動的に再ダウンロードが開始されます。
	BSDOWNCALLBACK_FILEINFO		// ファイルのタイトル等が取得できたときにコールバックとしてかえります。
};

/* ======================================================================
   関数群
   ====================================================================== */

// 作業に必要なバッファのサイズを返します。
extern int bsdown_c_worksize();

/*---------------------------------------------------------------------------*
  Name:         bsdown_c_init
  Description:  
	  子機用初期化。
	  内部でWM_INITを呼び出し、スキャン開始まで一気に進めます。
  Arguments:    
  				target 　… データを格納する先のポインタ。
  						　　４バイト領域にあわせて下さい。
  				callback … コールバック関数]
  				buffer   … 作業領域。

  Returns:      成功すれば真。
 *---------------------------------------------------------------------------*/
extern BOOL bsdown_c_init( void *target, BSDOWN_CALLBACK callback, void *buffer );

// 現在までに受信したパケット量を取得
extern int bsdown_c_received(void);

// 受信すべきパケットの量
extern int bsdown_c_total(void);

// 受信しているデータのサイズ。まだ受信が開始されていなければ０を返す。
extern int bsdown_c_size(void);

// 終了する。完了したらコールバックでBSDOWNCALLBACK_ERROR2が返ってくる。
extern BOOL bsdown_end( void );

// 最後に受信したパケットのインデックス
extern int bsdown_c_lastreceive(void);
// 現在まで受け取ったパケットの表
extern u8 *bsdown_c_downloadpacket(void);

// 受信済みのＣＲＣが正しいかチェック。
// この関数を呼び出さない限り、ＣＲＣのチェックは行いません。
// BSDOWNCALLBACK_SUCCESS のコールバックがあった後に、呼び出してください。
extern int bsdown_c_checkcrc(void);

// 最後にうけとったビーコンの強度を取得。（アンテナアイコンの表示等にご利用ください）
extern int bsdown_c_linklevel(void);

// タイトルなど、ダウンロードしているファイルの情報を取得します。
// まだ受信できていないときは、NULLを返します。
extern void* bsdown_c_fileheader(void);

// 何回連続で違う種類のパケットを受け取った場合、タイムアウトと判定するか？
#define BSDOWN_TIMEOUT 16

/* ======================================================================
   以下は子機親機共通の設定にする必要がある。
   ====================================================================== */

// GGIDは定数で定義。ビーコン配信は専用のものをつかってください。
#if 0
#define BDOWN_GGID 0x003fff20
#else
#define BDOWN_GGID 0x00000345
#endif

// 受信/送信する可能性のあるファイルの最大値
#define BSOWN_MAXSIZE (128*1024)

#define BSDOWN_SCANTIME 220



#endif	// __BEACONDOWNLOAD__
