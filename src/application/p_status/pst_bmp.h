//============================================================================================
/**
 * @file	pst_bmp.h
 * @brief	ポケモンステータス画面BMP
 * @author	Hiroyuki Nakamura
 * @date	2005.11.15
 */
//============================================================================================
#ifndef PST_BMP_H
#define PST_BMP_H
#undef GLOBAL
#ifdef PST_BMP_H_GLOBAL
#define GLOBAL	/*	*/
#else
#define GLOBAL	extern
#endif


//============================================================================================
//	定数定義
//============================================================================================
#define	PST_MSG_PRMNONE	( 0xfe )	// メッセージID：「なにも　かわらなかった！」
#define	PST_MSG_EATNONE	( 0xff )	// メッセージID：「もう　これいじょう　たべない　みたい」


//============================================================================================
//	プロトタイプ宣言
//============================================================================================

GLOBAL void PokeStatusBmpAdd( PST_WORK * wk );
GLOBAL void PokeStatusBmpExit( PST_WORK * wk );
GLOBAL void PokeStatusTitlePut( PST_WORK * wk );
GLOBAL void PokeStatusNamePut( PST_WORK * wk );
GLOBAL void PokeStatusLvPut( PST_WORK * wk );
GLOBAL void PokeStatusItemPut( PST_WORK * wk );
GLOBAL void PokeStatusTagParamMsgPut( PST_WORK * wk );
GLOBAL void PokeStatusInfoParamPut( PST_WORK * wk );
GLOBAL void PokeStatusPageMemoPut( PST_WORK * wk );
GLOBAL void PokeStatusPageParamPut( PST_WORK * wk );
GLOBAL void PokeStatusPageConditionPut( PST_WORK * wk );
GLOBAL void PokeStatusPageSkillPut( PST_WORK * wk );
GLOBAL void PokeStatus_WazaInfoPut( PST_WORK * wk, u32 waza );
GLOBAL void PokeStatus_WazaInfoOff( PST_WORK * wk );
GLOBAL void PokeStatus_ContestWazaInfoPut( PST_WORK * wk, u32 waza );
GLOBAL void PokeStatus_ContestWazaInfoOff( PST_WORK * wk );
GLOBAL void PokeStatusPageReturnPut( PST_WORK * wk );
GLOBAL void PokeStatus_SkillCancelPut( PST_WORK * wk );
GLOBAL void PokeStatus_SkillCancelDel( PST_WORK * wk );
GLOBAL void PokeStatus_SkillChgRewrite( PST_WORK * wk );

GLOBAL void PokeStatus_WazaOboeErrorMsgPut( PST_WORK * wk );

GLOBAL void PokeStatus_GuideStrPut( PST_WORK * wk, u32 midx );



GLOBAL void PokeStatus_NickNamePut( PST_WORK * wk );

GLOBAL void PokeStatus_LvPut( PST_WORK * wk );

GLOBAL void PokeStatus_ItemPut( PST_WORK * wk );

GLOBAL void PokeStatus_DefaultBmpAdd( PST_WORK * wk );

GLOBAL void PokeStatus_PageBmpAdd( PST_WORK * wk );

GLOBAL void PokeStatus_PageBmpFree( PST_WORK * wk );

GLOBAL void PokeStatus_BmpFreeAll( PST_WORK * wk );

GLOBAL void PokeStatus_PageBmpPut( PST_WORK * wk );

GLOBAL void PokeStatus_RibbonPosNumPut( PST_WORK * wk );

GLOBAL void PokeStatus_RibbonInfoPut( PST_WORK * wk );

GLOBAL void PokeStatus_CondUpMsgPut( PST_WORK * wk, u8 num );




#undef GLOBAL
#endif	/* PST_BMP_H */
