//============================================================================================
/**
 * @file	scr_climaxdemo.h
 * @bfief	スクリプトコマンド用:テンガンザン山頂デモ呼び出し
 * @author	tamada GAME FREAK inc.
 * @date	2006.06.21
 *
 */
//============================================================================================

#ifndef	__SCR_CLIMAXDEMO_H__
#define __SCR_CLIMAXDEMO_H__

#ifndef	__ASM_NO_DEF_
//テンガンザン山頂デモ関連
extern BOOL ClimaxDemoCall(FIELDSYS_WORK * fsys, int demo_id);
#endif

#define	CLIMAX_DEMO_LEGENDPOKE_START	0
#define	CLIMAX_DEMO_LEGENDPOKE_ENDCHK	1
#define	CLIMAX_DEMO_BLACKRING_START		2
#define	CLIMAX_DEMO_BLACKRING_END		3
#define	CLIMAX_DEMO_GINGA_START			4
#define	CLIMAX_DEMO_GINGA_ENDREQ		5
#define	CLIMAX_DEMO_GINGA_ENDCHK		6
#define	CLIMAX_DEMO_ANTEGG_00			7
#define	CLIMAX_DEMO_ANTEGG_01			8
#define	CLIMAX_DEMO_ANTEGG_02			9

#endif	// __SCR_CLIMAXDEMO_H__
