//=============================================================================
/**
 * @file	savedata.h
 * @brief	セーブデータ用ヘッダ
 * @author	tamada	GAME FREAK Inc.
 * @date	2005.10.12
 *
 * このヘッダはセーブデータの生成処理など、直接セーブデータにかかわる部分にのみ必要。
 * それ以外の箇所ではsavedata_def.hのSAVEDATA型経由でアクセスできればよい。
 * そのため、このヘッダをインクルードする箇所は限定されるはず
 */
//=============================================================================
#ifndef	__SAVEDATA_H__
#define	__SAVEDATA_H__

#include "savedata/savedata_def.h"

//---------------------------------------------------------------------------
///	セーブに使用しているセクタ数
//---------------------------------------------------------------------------
#define	SAVE_PAGE_MAX		(32)

#define	SAVE_SECTOR_SIZE	(0x1000)

//以下はデバッグツール用のセーブ領域です by soga
#define	POKE_ANM_SAVE		(60*SAVE_SECTOR_SIZE)		//ポケモンアニメツール用セーブ領域
#define	DEBUG_FIGHT_SAVE	(63*SAVE_SECTOR_SIZE)		//デバッグファイト用セーブ領域

//---------------------------------------------------------------------------
///	セーブブロックの定義
//---------------------------------------------------------------------------
typedef enum {
	SVBLK_ID_NORMAL = 0,	///<通常ゲーム進行データ
	SVBLK_ID_BOX,			///<ポケモンボックス

	SVBLK_ID_MAX,
}SVBLK_ID;

//---------------------------------------------------------------------------
///	セーブ項目の定義
//---------------------------------------------------------------------------
typedef enum {
	//ノーマルデータグループ
	GMDATA_ID_SYSTEM_DATA,
	GMDATA_ID_PLAYER_DATA,
	GMDATA_ID_TEMOTI_POKE,
	GMDATA_ID_TEMOTI_ITEM,
	GMDATA_ID_EVENT_WORK,
	GMDATA_ID_POKETCH_DATA,
	GMDATA_ID_SITUATION,
	GMDATA_ID_ZUKANWORK,
	GMDATA_ID_SODATEYA,
	GMDATA_ID_FRIEND,
	GMDATA_ID_MISC,
	GMDATA_ID_FIELDOBJSV,
	GMDATA_ID_UNDERGROUNDDATA,
    GMDATA_ID_REGULATION,
	GMDATA_ID_IMAGECLIPDATA,
	GMDATA_ID_MAILDATA,
	GMDATA_ID_PORUTODATA,
	GMDATA_ID_RANDOMGROUP,
	GMDATA_ID_FNOTE,
	GMDATA_ID_TRCARD,
	GMDATA_ID_RECORD,
	GMDATA_ID_CUSTOM_BALL,
	GMDATA_ID_PERAPVOICE,
	GMDATA_ID_BTLTOWER,
	GMDATA_ID_SP_RIBBON,
	GMDATA_ID_ENCOUNT,
	GMDATA_ID_WORLDTRADEDATA,
	GMDATA_ID_TVWORK,
	GMDATA_ID_GUINNESS,
	GMDATA_ID_WIFILIST,
	GMDATA_ID_WIFIHISTORY,
	GMDATA_ID_FUSHIGIDATA,
	GMDATA_ID_POKEPARKDATA,
	GMDATA_ID_CONTEST,
	GMDATA_ID_PMS,

	//ボックスデータグループ
	GMDATA_ID_BOXDATA,

	GMDATA_ID_MAX,
}GMDATA_ID;

//---------------------------------------------------------------------------
/**
 * @brief	外部セーブデータのID定義
 */
//---------------------------------------------------------------------------
typedef enum {
	EXDATA_ID_DENDOU,			///<殿堂入りデータ
	EXDATA_ID_FUSHIGIDATA,		///<ふしぎなおくりものデータ
	EXDATA_ID_MAX,
}EXDATA_ID;


//============================================================================================
//============================================================================================
//---------------------------------------------------------------------------
//	フラッシュアクセス用関数
//	※デバッグ用途以外ではSaveData_～を呼ぶはずなので、通常は直接使わない。
//---------------------------------------------------------------------------
extern BOOL PMSVLD_Init(void);
extern BOOL PMSVLD_Save(u32 src, void * dst, u32 len);
extern BOOL PMSVLD_Load(u32 src, void * dst, u32 len);


//---------------------------------------------------------------------------
//	セーブデータ制御関数
//---------------------------------------------------------------------------
//セーブロードシステム初期化
extern SAVEDATA * SaveData_System_Init(void);

//フラッシュ存在チェック
extern BOOL SaveData_GetFlashExistsFlag(const SAVEDATA * sv);

//ロード処理
extern BOOL SaveData_Load(SAVEDATA * sv);
//セーブ処理
extern SAVE_RESULT SaveData_Save(SAVEDATA * sv);
//消去処理
extern BOOL SaveData_Erase(SAVEDATA * sv);
//部分セーブ処理
extern SAVE_RESULT SaveData_SaveParts(SAVEDATA * sv, SVBLK_ID id);
//セーブデータ初期化（書き込まない）
extern void SaveData_ClearData(SAVEDATA * sv);

//最初の読み込み時のセーブデータ状態取得
extern LOAD_RESULT SaveData_GetLoadResult(const SAVEDATA * sv);

//既存データへの新規データ上書きチェック
extern BOOL SaveData_IsOverwritingOtherData(const SAVEDATA * sv);
//新規データかどうかの判別フラグ取得
extern BOOL SaveData_GetNewDataFlag(const SAVEDATA * sv);
//データが存在するかどうかの判別フラグ取得
extern BOOL SaveData_GetExistFlag(const SAVEDATA * sv);

//全体セーブが必要かどうかの判別フラグ取得
extern BOOL SaveData_GetTotalSaveFlag(const SAVEDATA * sv);

//全体セーブリクエストフラグセット
extern void SaveData_RequestTotalSave(void);

//分割セーブ：初期化
extern void SaveData_DivSave_Init(SAVEDATA * sv, int BlockID);
//分割セーブ：メイン
extern SAVE_RESULT SaveData_DivSave_Main(SAVEDATA * sv);
//分割セーブ：キャンセル
extern void SaveData_DivSave_Cancel(SAVEDATA * sv);


//---------------------------------------------------------------------------
//	セーブデータアクセス用関数
//---------------------------------------------------------------------------
extern void * SaveData_Get(SAVEDATA * sv, GMDATA_ID gmdataID);
extern const void * SaveData_GetReadOnlyData(const SAVEDATA * sv, GMDATA_ID gmdataID);


//---------------------------------------------------------------------------
//	デバッグ用関数
//	許可なく使ってはいけません。
//---------------------------------------------------------------------------
extern SAVEDATA * SaveData_GetPointer(void);

// インデックスを作る時のみ有効
// 通常はOFFなのでONになってるのを見つけたら無条件にOFFで良い
//#define CREATE_INDEX

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------


#endif	/* __SAVEDATA_H__ */
