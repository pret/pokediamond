//============================================================================================
/**
 * @file	pmsi_initial_data.h
 * @bfief	簡易会話入力画面（カテゴリイニシャルモード用のデータテーブル処理）
 * @author	taya
 * @date	06.02.14
 */
//============================================================================================
#ifndef __PMSI_INITIAL_DATA_H__
#define __PMSI_INITIAL_DATA_H__

extern u32 PMSI_INITIAL_DAT_GetInitialMax(void);
extern void PMSI_INITIAL_DAT_GetStr( u32 initial, STRBUF* buf );
extern void PMSI_INITIAL_DAT_GetPrintPos( u32 initial, u32* x, u32* y );
extern int PMSI_INITIAL_DAT_GetUpCode( u32 initial );
extern int PMSI_INITIAL_DAT_GetDownCode( u32 initial );
extern int PMSI_INITIAL_DAT_GetLeftCode( u32 initial );
extern int PMSI_INITIAL_DAT_GetRightCode( u32 initial );
extern int PMSI_INITIAL_DAT_GetColTopCode( u32 initial );
extern int PMSI_INITIAL_DAT_GetColBottomCode( u32 initial );



#endif
