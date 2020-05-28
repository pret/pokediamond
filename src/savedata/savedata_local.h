//============================================================================================
/**
 * @file	savedata_local.h
 * @brief
 * @date	2006.04.17
 * @author	tamada GAME FREAK inc.
 */
//============================================================================================

#ifndef	__SAVEDATA_LOCAL_H__
#define	__SAVEDATA_LOCAL_H__

#include "savedata/savedata.h"

#ifdef	PM_DEBUG
//この定義を有効にするとフラッシュのエラーチェックが無効になる
//デバッグ期間用なので製品版では繁栄させないこと！
//#define	DISABLE_FLASH_CHECK
#endif

//=============================================================================
//=============================================================================

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
typedef int (*FUNC_GET_SIZE)(void);

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
typedef void (*FUNC_INIT_WORK)(void *);

//---------------------------------------------------------------------------
/**
 * @brief	セーブデータ内容データ用の構造体定義
 */
//---------------------------------------------------------------------------
typedef struct {
	GMDATA_ID gmdataID;				///<セーブデータ識別ID
	SVBLK_ID	blockID;
	FUNC_GET_SIZE get_size;			///<セーブデータサイズ取得関数
	FUNC_INIT_WORK	init_work;		///<セーブデータ初期化関数
}SAVEDATA_TABLE;


//---------------------------------------------------------------------------
/**
 * @brief	特殊セーブデータ定義データの構造体定義
 */
//---------------------------------------------------------------------------
typedef struct {
	EXDATA_ID id;					///<特殊セーブデータ識別ID
	u32 sector;						///<開始セクタ
	FUNC_GET_SIZE get_size;			///<データサイズ取得関数
	FUNC_INIT_WORK init_work;		///<セーブデータ初期化関数
}EXSAVEDATA_TABLE;

//=============================================================================
//=============================================================================

extern const SAVEDATA_TABLE SaveDataTable[];
extern const int SaveDataTableMax;

extern const EXSAVEDATA_TABLE ExtraSaveDataTable[];
extern const int ExtraSaveDataTableMax;

extern SAVE_RESULT SaveData_Extra_Save(const SAVEDATA * sv, EXDATA_ID id, void * data);
extern void * SaveData_Extra_LoadAlloc(SAVEDATA * sv,
		int heap_id, EXDATA_ID id, LOAD_RESULT * result);




#endif	/* __SAVEDATA_LOCAL_H__ */
