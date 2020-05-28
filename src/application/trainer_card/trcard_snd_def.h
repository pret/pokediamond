//============================================================================================
/**
 * @file	trcard_snd_def.h
 * @bfief	トレーナーカードSE定義
 * @author	Nozomu Saito
 * @date	05.11.15
 */
//============================================================================================
#ifndef __TRCARD_SND_DEF_H__
#define __TRCARD_SND_DEF_H__

//#define SND_TRCARD_REV		(SEQ_SE_DP_CARD2)		//カードをひっくり返す音
#define SND_TRCARD_REV			(SEQ_SE_DP_CARD5)		//カードをひっくり返す音

//#define SND_TRCARD_CALL		(SEQ_SE_DP_CARD7)		//呼び出した時
#define SND_TRCARD_CALL			(SEQ_SE_DP_CARD3)		//呼び出した時
#define SND_TRCARD_END			(SEQ_SE_DP_SELECT)		//終了時

//#define SND_TRCARD_REV_AFTER	(SEQ_SE_DP_CARD3)		//カードをひっくり返して表示された時
#define SND_TRCARD_REV_AFTER	(SEQ_SE_DP_CARD2)		//カードをひっくり返して表示された時

#define SND_TRCARD_SCRUCH01		(SEQ_SE_DP_MIGAKU01)	//バッジ磨き音その1
#define SND_TRCARD_SCRUCH02		(SEQ_SE_DP_MIGAKU02)	//バッジ磨き音その2

#define SND_TRCARD_BUTTON		(SEQ_SE_DP_BUTTON9)		//ケースボタン
//#define SND_TRCARD_CASE_OP	(SEQ_SE_DP_CARD9)		//ケースオープン
//#define SND_TRCARD_CASE_OP	(SEQ_SE_DP_CARD2)		//ケースオープン
#define SND_TRCARD_CASE_OP		(SEQ_SE_DP_CARD11)		//ケースオープン

//#define SND_TRCARD_CASE_CL	(SEQ_SE_DP_CARD10)		//ケースクローズ
//#define SND_TRCARD_CASE_CL	(SEQ_SE_DP_CARD2)		//ケースクローズ
#define SND_TRCARD_CASE_CL		(SEQ_SE_DP_CARD11)		//ケースクローズ

#endif	//__TRCARD_SND_DEF_H__
