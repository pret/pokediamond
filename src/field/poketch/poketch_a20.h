//============================================================================================
/**
 * @file	poketch_a20.h
 * @bfief	ポケッチ（アプリNo20:アラーム時計）　内部ヘッダ
 * @author	taya GAME FREAK inc.
 */
//============================================================================================
#ifndef _POKETCH_A20_H_
#define _POKETCH_A20_H_


//====================================================
// 描画コマンド
//====================================================
enum {
	CMD_INIT,
	CMD_QUIT,
	CMD_CHANGE_ON,
	CMD_CHANGE_OFF,
	CMD_UPDATE_TIME,
	CMD_ALARM,
};

//====================================================
// 描画パラメータ
//====================================================
typedef struct {
	u8   switch_on;
	s8   hour_now;
	s8   min_now;
	s8   hour_set;
	s8   min_set;

}VIEWPARAM;

//====================================================
// 描画パラメータ
//====================================================
typedef	struct _POKETCH_A20_VIEWWORK  VIEWWORK;

//====================================================
// 関数プロトタイプ
//====================================================
extern BOOL Poketch_A20_SetViewWork( VIEWWORK** wk_ptr, const VIEWPARAM* vpara, GF_BGL_INI* bgl );
extern void Poketch_A20_SetViewCommand(VIEWWORK* wk, u32 cmd);
extern BOOL Poketch_A20_WaitViewCommand(VIEWWORK* wk, u32 cmd);
extern BOOL Poketch_A20_WaitViewCommandAll(VIEWWORK* wk);
extern void Poketch_A20_DeleteViewWork(VIEWWORK* wk);
extern void Poketch_A20_ForceStopAlarm( VIEWWORK* vwk );

#endif
