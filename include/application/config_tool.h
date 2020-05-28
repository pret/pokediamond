/**
 *	@file	confing.h
 *	@brief	コンフィグ画面外部公開ヘッダ
 *	@date	06.01.30
 *	@author	Miyuki Iwasawa
 */

#ifndef __H_CONFIG_H__
#define __H_CONFIG_H__

///外部公開ワーク
typedef struct _CONFIG_PARAM
{
	u16 msg_spd:4;
	u16 sound:2;
	u16 btl_eff:1;
	u16 btl_rule:1;
	u16 input_mode:2;
	u16 win_type:5;
	u16 pad_dmy:1;
}CONFIG_PARAM;

///オーバーレイプロセス
extern PROC_RESULT ConfigProc_Init( PROC *proc,int *seq);
extern PROC_RESULT ConfigProc_Main( PROC *proc,int *seq);
extern PROC_RESULT ConfigProc_End( PROC *proc,int *seq);

#endif	//__H_CONFIG_H__
