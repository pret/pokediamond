//============================================================================================
/**
 * @file	pst_sub.h
 * @brief	ポケモンステータス画面　下画面のボタン処理
 * @author	Hiroyuki Nakamura
 * @date	2006.03.03
 */
//============================================================================================
#ifndef PST_SUB_H
#define PST_SUB_H
#undef GLOBAL
#ifdef PST_SUB_H_GLOBAL
#define GLOBAL	/*	*/
#else
#define GLOBAL	extern
#endif


//============================================================================================
//	プロトタイプ宣言
//============================================================================================

GLOBAL void PokeStatus_SubButtonMake( PST_WORK * wk );
GLOBAL void PokeStatus_SubButtonBgInit( PST_WORK * wk );

GLOBAL u8 PokeStatus_SubBottonPageGet( PST_WORK * wk );

GLOBAL u8 PokeStatus_SubButtonAnm( PST_WORK * wk );

GLOBAL void PokeStatus_ButtonPosGet( PST_WORK * wk, s16 * x, s16 * y );

GLOBAL u8 PokeStatus_ButtonPosPageGet( PST_WORK * wk, u8 pos );


#undef GLOBAL
#endif	/* PST_SUB_H */
