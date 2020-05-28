//============================================================================================
/**
 * @file	namein_snd_def.h
 * @bfief	名前入力画面用効果音定義
 * @author	Akito Mori
 * @date	06.02.24
 */
//============================================================================================

#ifndef __NAMEIN_SND_DEF_H__
#define __NAMEIN_SND_DEF_H__

#define NAMEIN_SE_MOVE			(SEQ_SE_DP_SELECT)		// カーソル移動音
//#define NAMEIN_SE_DECIDE		(SEQ_SE_DP_DECIDE)		// 決定音
//#define NAMEIN_SE_DECIDE		(SEQ_SE_DP_DECIDE2)		// 決定音
#define NAMEIN_SE_DECIDE		(SEQ_SE_DP_BOX02)		// 決定音
#define NAMEIN_SE_BS			(SEQ_SE_DP_SELECT)		// もどる、BSを押した音

//#define NAMEIN_SE_CHANGEPANEL	(SEQ_SE_DP_SYU01 )		// 文字入力パネル切り替え
//#define NAMEIN_SE_CHANGEPANEL	(SEQ_SE_DP_SYU02 )		// 文字入力パネル切り替え
#define NAMEIN_SE_CHANGEPANEL	(SEQ_SE_DP_SYU03 )		// 文字入力パネル切り替え

#define NAMEIN_SE_SETPANEL		(SEQ_SE_DP_NAMEIN_01 )	// 文字パネルがセットされた時の音
#define NAMEIN_SE_END			(SEQ_SE_DP_PIRORIRO )	// 終わりボタン
//#define NAMEIN_SE_END			(SEQ_SE_DP_PIRORIRO2 )	// 終わりボタン

#endif

