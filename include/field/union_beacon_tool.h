//=============================================================================
/**
 * @file	union_beacon_tool.H
 * @brief	ユニオンルーム見た目設定処理
 * @author	Akito Mori
 * @date    	2006.03.16
 */
//=============================================================================

#ifndef __UNION_BEACON_TOOL_H__
#define __UNION_BEACON_TOOL_H__

enum UNION_VIEW_INFO {
  UNIONVIEW_ICONINDEX,	// ２Ｄ画像用(人物ＯＢＪ）のテーブルの場所（0-18)
  UNIONVIEW_TRTYPE,		// トレーナーグラフィックのＩＤ（バトルやカード時のグラフィック）
  UNIONVIEW_MSGTYPE,	// トレーナータイプのメッセージＮＯ(msg_trtype_name_dat)

};

// トレーナーVIEWTYPEと性別から情報を引き出す
extern int  UnionView_GetTrainerInfo( int view_type, int sex, int info );

extern int  UnionView_GetTrainerType( u32 id, int sex, u32 select );
extern void UnionView_SetUpTrainerTypeSelect( u32 id, int sex, WORDSET *wordset );


#endif