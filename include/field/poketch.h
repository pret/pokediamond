//============================================================================================
/**
 * @file	poketch.h
 * @bfief	ポケッチ　外部公開ヘッダ
 * @author	taya GAME FREAK inc.
 */
//============================================================================================
#ifndef _POKETCH_H_
#define _POKETCH_H_

#include "gflib\bg_system.h"
#include "field\field_common.h"
#include "field\poketch_data.h"


//====================================================
// ワークの型宣言
//====================================================
typedef struct _POKETCH_WORK  POKETCH_WORK;

//====================================================
// フィールド→ポケッチへの通知項目ID
//====================================================
typedef enum {
	POKETCH_SEND_SLEEP,
	POKETCH_SEND_MOVE_PLAYER,
	POKETCH_SEND_SODATEYA_UPDATE,
	POKETCH_SEND_POKELIST_UPDATE,
	POKETCH_SEND_SAVE,
	POKETCH_SEND_PEDOMATER,
}FIELD_POKETCH_SEND_ID;


//====================================================
// オーバーレイID宣言
//====================================================
FS_EXTERN_OVERLAY(ol_poketch);
FS_EXTERN_OVERLAY(ol_before_poketch);

//====================================================
// アプリナンバーとして無効な値（切り替え中の時など）
//====================================================
enum {
	POKETCH_APP_NONE = -1,
};

//====================================================
// 関数プロトタイプ
//====================================================
extern void PoketchInit(FIELDSYS_WORK* fsys, POKETCH_WORK **wk_adrs, SAVEDATA* savedata, GF_BGL_INI* bgl, NNSG2dOamManagerInstance* oamm);
extern void PoketchQuitReq(POKETCH_WORK *wk);
extern BOOL PoketchQuitWait( POKETCH_WORK *wk );
extern void Poketch_SendRequest( POKETCH_WORK* wk, FIELD_POKETCH_SEND_ID  id, u32 value );
extern BOOL Poketch_CheckTouch( POKETCH_WORK* wk );
extern int Poketch_GetRunningApplication( POKETCH_WORK* wk );

extern void PoketchBglIniSet( POKETCH_WORK * wk, GF_BGL_INI * ini );
extern GF_BGL_INI * PokethBglGet( POKETCH_WORK * wk );




//-------------------------------------------------------
// ポケッチ取得以前のコントロール関数
//-------------------------------------------------------
extern void BeforePoketchInit( GF_BGL_INI* bgl );
extern void BeforePoketchQuitReq( GF_BGL_INI* bgl );
extern BOOL BeforePoketchQuitWait( GF_BGL_INI* bgl );

#endif
