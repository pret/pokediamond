
#ifndef __SYSTEM_H__
#define __SYSTEM_H__

///#define DEBUG_PRINT	//デバッグ情報を表示したい場合は、コメントをはずす
#include <nitro.h>
#include <nnsys.h>

#include "gflib\heapsys.h"
#include "gflib\tcb.h"
#include "system\heapdefine.h"
#include "system\tcbman.h"


/*---------------------------------------------------------------------------*
  File:     system.h
 *---------------------------------------------------------------------------*/
#undef GLOBAL
#ifdef __SYSTEM_H_GLOBAL__
#define GLOBAL /*	*/
#else
#define GLOBAL extern
#endif



#define XtOffset(p_type,field)     ((unsigned int)&(((p_type )NULL)->field))
#define	NELEMS(array)	( sizeof(array) / sizeof(array[0]) )
#define	ALIGN4 __attribute__((aligned(4)))
#define ROUND_UP(value, alignment) \
    (((u32)(value) + (alignment-1)) & ~(alignment-1))
#define ROUND_DOWN(value, alignment) \
    ((u32)(value) & ~(alignment-1))


#ifdef PM_DEBUG
#define TPRINTF(fmt, ...) \
	OS_TPrintf("%s:%d: " fmt, __FILE__, __LINE__, __VA_ARGS__)
#else
#define TPRINTF(fmt, ...) \
	((void)0)
#endif


/*
 * @brief	割り込み関数用ポインタ型
 */
typedef void (*INTR_FUNC)(void *);

typedef void (*pFunc)(void);	// 関数ポインタ型
typedef int (*appFunc)(int command, void* set_up, void* rep);	// アプリ関数ポインタ型
enum {
	APP_ON = 0,
	APP_BUSY = 1,
	APP_END = -1,
};
enum {
	APP_INIT_REQ = 0,
	APP_ON_REQ = 1,
	APP_PAUSE_REQ = 2,
	APP_END_REQ = -1,
};

enum {
	DISP_3D_TO_MAIN = 0,
	DISP_3D_TO_SUB = 1,
};

enum {
	KEYCONTROL_NORMAL = 0,
	KEYCONTROL_PATTERN1 = 1,
	KEYCONTROL_PATTERN2 = 2,
	KEYCONTROL_PATTERN3 = 3,
};

enum {  //スリープ状態にしてはいけない定義
  SLEEPTYPE_SAVELOAD = 0x01,
  SLEEPTYPE_AGBROM = 0x02,
  SLEEPTYPE_COMM = 0x04,
};

enum {  //ソフトウエアリセットをしたくない状態の定義
  SOFTRESET_TYPE_WIFI = 0x01,   // WIFI通信時
  SOFTRESET_TYPE_TRADE = 0x02,  // ポケモン交換時
  SOFTRESET_TYPE_SAVELOAD = 0x04, // セーブロード交換時
};


//------------------- 定義 -----------------------------------------
typedef	struct {
//	pFunc	pMainProc;		// メイン画面プロセス呼び出し関数ポインタ
//	pFunc	pReturnProc;	// 特定処理後に復帰する先の関数ポインタ
//	appFunc pSubProc;		// アプリケーション呼び出し関数ポインタ

	INTR_FUNC pVBlank;		// Ｖブランク割込み内呼び出し関数ポインタ
	void * pVBlankWork;		// Ｖブランク割込み内呼び出し関数用ワークへのポインタ
	INTR_FUNC pHBlank;		// Ｈブランク割込み内呼び出し関数ポインタ
	void * pHBlankWork;		// Ｈブランク割込み内呼び出し関数用ワークへのポインタ
	pFunc pVCount;			// Ｖカウント割込み内呼び出し関数ポインタ
	pFunc pSio;				// ＳＩＯ割込み内呼び出し関数ポインタ

	TCBSYS*  mainTCBSys;	// メインループ用TCB(30fps)
	TCBSYS*  vintrTCBSys;	// Vblank割り込み用TCB
	TCBSYS*  vwaitTCBSys;	// VBlank２回終了後の30fps同期用TCB
	TCBSYS*  printTCBSys;	// 文字出力処理用に,VBlank待ち前に稼働するTCB

	u32* main_timer;			// タイマー(ソフト)用カウンタポインタ
	u32 vsync_counter;			// Ｖブランク用カウンタ
	u32 vsync_flame_counter;	// フレーム制御用カウンタ

	int key_control_mode;	// キー取得モード(0がdefault)
	int cont_org;			// キー状態
	int trg_org;			// キートリガ
	int repeat_org;			// キーリピート
	int cont;				// キー状態(ゲーム設定により変換処理が入る)
	int trg;				// キートリガ(ゲーム設定により変換処理が入る)
	int repeat;				// キーリピート(ゲーム設定により変換処理が入る)
	int repeatWait_Count;	// キーリピートカウンタ
	int repeatSpeed;		// キーリピートスピード
	int repeatWait;			// キーリピートウェイト

	u16		tp_x;			// タッチパネルX座標
	u16		tp_y;			// タッチパネルY座標
	u16		tp_trg;			// タッチパネル接触判定トリガ
	u16		tp_cont;		// タッチパネル接触判定状態

	u8		tp_auto_samp;	// タッチパネルオートサンプリングフラグ(0:サンプリングしていない　1:サンプリング中)
	u8 		disp3DSW;			// ３Ｄ表示ディスプレイスイッチ
	u8  	AgbCasetteVersion;	// 差し込まれているAgbカーットリッジのバージョン（GBAポケモンが差し込まれている時のみ）
	u8 		DontSleep;          //スリープ状態にしてはいけない場合BITがたっている 大丈夫な場合0
	u8 		DontSoftReset;      //ソフトリセットしたくない場合BITがたっている 大丈夫な場合0

	BOOL 	DS_Boot_Flag;		// 

}SystemArea;


//==================================================================
//	グローバル変数
//==================================================================
GLOBAL SystemArea sys;						// システムリソース

//==================================================================
//	初期化関数
//==================================================================
GLOBAL void sys_InitSystem(void);
GLOBAL void sys_InitVRAM(void);
GLOBAL void sys_InitKeyRead(void);
GLOBAL void sys_InitAgbCasetteVer(int version);

//==================================================================
//	デフォルト割り込み関数
//==================================================================
GLOBAL void sys_VBlankIntr(void);

// HBlank設定
GLOBAL void sys_HBlankIntrStop( void );
GLOBAL BOOL sys_HBlankIntrSet( INTR_FUNC func, void * work );

//==================================================================
//	ユーティリティー関数
//==================================================================


//Vブランク中呼び出し関数の登録
GLOBAL void sys_VBlankFuncChange(INTR_FUNC func, void * work);

//	ファイルロード関数
GLOBAL void* sys_LoadFile( int mode, const char *path);
GLOBAL void * sys_LoadFileEx( int mode, const char * path, u32 * siz );
GLOBAL void* sys_LoadGraphFile(const char *path, const u8 inMode);
GLOBAL void sys_LoadFileNoMem(const char *path,void **mem);
/*---------------------------------------------------------------------------*
  Name:         sys_LoadFileDiv

  Description:  通常ファイルの読み込み分割 
  
  Arguments:    mode	指定ヒープ領域定義
				path	ファイルへのパス
				memory	ファイル読み込み先アドレス格納ポインタ
				offset	読み込みオフセット格納ポインタ
				divsiz	読み込み分割サイズ
Returns:		0:継続、1=終了
 *---------------------------------------------------------------------------*/
GLOBAL int sys_LoadFileDiv( int mode, const char * path, void** memory, u32* offset, u16 divsiz );

/*---------------------------------------------------------------------------*
  Name:         sys_LoadFileDivNoMem

  Description:  通常ファイルの読み込み分割(メモリ確保しない)
  
  Arguments:    path	ファイルへのパス
				memory	ファイル読み込み先アドレス格納ポインタ
				offset	読み込みオフセット格納ポインタ
				divsiz	読み込み分割サイズ
Returns:		0:継続、1=終了
 *---------------------------------------------------------------------------*/
GLOBAL int sys_LoadFileDivNoMem( const char * path, void** memory, u32* offset, u16 divsiz );
#if 0
/*---------------------------------------------------------------------------*
  @brief	グラフィック用ファイルリソースの解放

  @param	addr	(void*)解放するリソースアドレス
  @param	free	TRUEならば、キャッシュ登録されているリソースでも解放する
					FALSEの場合、キャッシュ登録されていれば解放しない
  @retval	0		正常解放
  @retval	1		キャッシュから解放
  @retval	2		キャッシュ登録されているので非解放
  @retval	0xFF	パラメータが不正
 *---------------------------------------------------------------------------*/
GLOBAL s8 sys_FreeGraphFile(void* addr,u8 free);
#endif
	//	キー情報取得関数
GLOBAL void sys_MainKeyRead(void);

// キーリピートの速度とウェイトをセット
GLOBAL void sys_KeyRepeatSpeedSet( int speed, int wait );

/**
 * @brief	ファイル名からファイルキャッシュ用のハッシュ値を取得する
 * @param   path	ファイル名文字列
 * @retval  u32		
 */
GLOBAL u32 CreateFileHash(const char *path);

//==============================================================================
/**
 * 既にキャッシュとして存在しているいるか検索する
 * @param   hash	ファイル名から取得したハッシュ値
 * @retval  int		0～:見つかった配列の要素	-1:見つからなかった
 */
//==============================================================================
GLOBAL int SearchFileCache(u32 hash);

//==============================================================================
/**
 * 新しく読み込んだファイルをキャッシュ情報として登録する
 *
 * @param   memory		新しく確保したメモリのアドレス
 * @param   hash		ファイル名から取得したハッシュ値
 *
 * @retval  int			登録した番号
 */
//==============================================================================
GLOBAL int SetBlankCache(void* memory, u32 hash);

//==============================================================================
/**
 * キャッシュの全解放・ハッシュ情報のクリア
 * @param   none		
 * @retval  none		
 */
//==============================================================================
GLOBAL void ClearFileCache(void);

//==============================================================================
/**
 * @brief	ハッシュ配列をNULL初期化する
 */
//==============================================================================
GLOBAL void InitFileCache(void);

//==============================================================================
/**
 * @brief	特定のハッシュをクリアする(キー指定)
 *
 * @param   hash	ファイル名から取得したハッシュ値
 *
 * @retval  int		0～:削除した要素Index	-1:削除しなかった
 */
//==============================================================================
GLOBAL int ClearFileCacheKey(u32 hash);

//==============================================================================
/**
 * @brief	特定のハッシュをクリアする(アドレス指定)
 *
 * @param   addr	リソースのアドレス
 *
 * @retval  int		0～:削除した要素Index	-1:削除しなかった
 */
//==============================================================================
GLOBAL int ClearFileCacheAddr(void* addr);

/*---------------------------------------------------------------------------*
  @brief	スリープ状態を禁止する
 *---------------------------------------------------------------------------*/
GLOBAL void sys_SleepNG(u8 sleepTypeBit);

/*---------------------------------------------------------------------------*
  @brief	スリープ状態を許可する
 *---------------------------------------------------------------------------*/
GLOBAL void sys_SleepOK(u8 sleepTypeBit);

/*---------------------------------------------------------------------------*
  @brief	ソフトウエアリセット状態を禁止する
 *---------------------------------------------------------------------------*/
GLOBAL void sys_SoftResetNG(u8 sleepTypeBit);

/*---------------------------------------------------------------------------*
  @brief	ソフトウエアリセット状態を許可する
 *---------------------------------------------------------------------------*/
GLOBAL void sys_SoftResetOK(u8 sleepTypeBit);




#undef GLOBAL


#endif
