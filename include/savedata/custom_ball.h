
#ifndef	__CUSTOM_BALL_H__
#define	__CUSTOM_BALL_H__

#include "system/savedata_def.h"


// とりあえず、セーブ領域fixのため必要なものを定義中
#define CB_DEF_SEAL_MAX				(8)			///< 貼れる枚数
#define CB_DEF_CORE_MAX				(12)		///< カスタムボールの数
#define CB_DEF_ITEM_DATA_NUM_MAX	(80)		///< シールの種類
#define CB_DEF_ITEM_DATA_NUM		(80 + 1)	//(80)		///< シールの種類
#define CB_DEF_SEAL_STOCK_MAX		(99)		///< シール最大数

#define CB_DEF_INDEX_ORIGIN			(1)			///< index の開始 (0 = 無 で扱うので 1 から)


enum {
	CB_ENUM_SEAL_ID_000 = 0,	///< 所持していない
	CB_ENUM_SEAL_ID_001,
};
#define CB_DEF_SEAL_NONE	(CB_ENUM_SEAL_ID_000)		///< シールを持っていない


///< custom
typedef struct _CUSTOM_BALL_SEAL		CB_SEAL;		///< シールのデータ
typedef struct _CUSTOM_BALL_CORE		CB_CORE;		///< カスタムボールのデータ

///< item
typedef struct _CUSTOM_BALL_ITEM_DATA	CB_ITEM_DATA;	///< アイテムデータ

///< save
typedef struct _CUSTOM_BALL_SAVE_DATA	CB_SAVE_DATA;	///< セーブデータ custom/core 含む


// -----------------------------------------
//
//	□ シールのデータ
//
// -----------------------------------------
struct _CUSTOM_BALL_SEAL {
	
	u8	seal_id;		///< シール番号
	u8	x;				///< x 座標
	u8	y;				///< y 座標
	
};


// -----------------------------------------
//
//	□ カスタムボールのデータ(ポケモンの手持ちも保持)
//
// -----------------------------------------
struct _CUSTOM_BALL_CORE {

	CB_SEAL	cb_seal[ CB_DEF_SEAL_MAX ];

};

#if 0
///< item
struct _CUSTOM_BALL_ITEM_DATA {
	
	u8	seal[ CB_DEF_ITEM_DATA_NUM ];
	
};


///< save
struct _CUSTOM_BALL_SAVE_DATA {
	
	CB_CORE			cb_core[ CB_DEF_CORE_MAX ];

	CB_ITEM_DATA	cb_item;
	
};
#endif

// =============================================================================
//
//
//	■関数
//
//
// =============================================================================
extern int				CustomBall_GetWorkSize(void);								///< セーブ領域のサイズを取得
extern CB_SAVE_DATA*	CustomBall_AllocSaveData(u32 heap_id);						///< セーブ領域を確保
extern void				CustomBall_Init(CB_SAVE_DATA* csd);							///< 初期化処理


///< アクセス関数 --- custom
extern CB_SAVE_DATA*	CB_SaveData_AllDataGet(SAVEDATA* sv);						///< セーブデータを取得する

extern CB_CORE*			CB_SaveData_CoreDataGet(CB_SAVE_DATA* save, int no);
extern void				CB_SaveData_CoreDataSet(CB_SAVE_DATA* save, CB_CORE* core, int no);

extern CB_SEAL*			CB_SaveData_SealDataGet(CB_CORE* core, int no);
extern void				CB_SaveData_SealDataSet(CB_CORE* core, CB_SEAL* seal, int no);

extern u8				CB_SaveData_SealIDGet(const CB_SEAL* seal);						///< 指定されたシールのIDを取得
extern void				CB_SaveData_SealIDSet(CB_SEAL* seal, u8 id);					///< 指定されたシールのIDを設定

extern u8				CB_SaveData_SealPXGet(const CB_SEAL* seal);						///< 指定されたシールのXを取得
extern void				CB_SaveData_SealPXSet(CB_SEAL* seal, u8 id);					///< 指定されたシールのXを設定

extern u8				CB_SaveData_SealPYGet(const CB_SEAL* seal);						///< 指定されたシールのYを取得
extern void				CB_SaveData_SealPYSet(CB_SEAL* seal, u8 id);					///< 指定されたシールのYを設定


///< アクセス関数 --- item
extern CB_ITEM_DATA*	CB_SaveData_ItemDataGet(CB_SAVE_DATA* save);					///< アイテムデータ全体

extern u8				CB_SaveData_ItemTypeGet(const CB_ITEM_DATA* save, int no);		///< アイテムタイプ取得
extern void				CB_SaveData_ItemTypeSet(CB_ITEM_DATA* save, int no, int type);	///< アイテムタイプ設定

extern u8				CB_SaveData_ItemNumGet(const CB_ITEM_DATA* save, int no);		///< アイテム個数取得
extern u8				CB_SaveData_ItemNumGet_CBO(const CB_ITEM_DATA* item, int no);	///< アイテム個数取得
extern void				CB_SaveData_ItemNumSet(CB_ITEM_DATA* save, int no, int stock);	///< アイテム個数設定
extern void				CB_SaveData_ItemNumAdd(CB_ITEM_DATA* save, int no, s16 stock);	///< アイテム個数増減

extern BOOL				CB_SaveData_ItemNumAddCheck(CB_SAVE_DATA* save, int no, s16 stock);	///< アイテム個数増減
extern BOOL				CB_SaveData_ItemNumAddCheck_CBO(CB_SAVE_DATA* save, int no, s16 stock);
extern BOOL				CB_SaveData_IsAddIt(CB_SAVE_DATA* save, int no, s16 stock);			///< アイテム個数増減チェックのみ


///< ツール系
extern void CB_Tool_SaveData_Copy(const CB_SAVE_DATA* from, CB_SAVE_DATA* to);
extern void CB_Tool_CoreData_Copy(const CB_CORE* from, CB_CORE* to);
extern void CB_Tool_SealData_Copy(const CB_SEAL* from, CB_SEAL* to);

extern BOOL CB_Tool_IsSeal(const CB_SAVE_DATA* save, int id);
extern BOOL CB_Tool_IsSealCore(const CB_CORE* cb_core, int id);
extern int CB_Tool_IsSealTotalNum(const CB_SAVE_DATA* save, int id);
extern int CB_Tool_SealCllectionGet(const CB_SAVE_DATA* save);
extern int CB_Tool_SealTotalNumGet(const CB_SAVE_DATA* save, int id);

#ifdef PM_DEBUG

#include "include/poketool/poke_tool.h"

///< デバッグ関数
enum {
	DEBUG_CB_MODE_CLEAR,			///< 無し
	DEBUG_CB_MODE_ITEM_FULL = 1,	///< アイテム最大
	DEBUG_CB_MODE_ITEM_RANDOM,		///< 適当なシールを用意
};

extern void Debug_CB_Set(POKEMON_PARAM* pp);
extern void Debug_CB_SaveData_Sample(CB_SAVE_DATA* save, int mode);
extern void Debug_CB_SaveData_Poke_Sample(SAVEDATA * save, int mode);
#endif

#endif

