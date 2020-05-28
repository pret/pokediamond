//============================================================================================
/**
 * @file	pst_bmp.h
 * @brief	ポケモンステータス画面 BMP定義
 * @author	Hiroyuki Nakamura
 * @date	2006.02.24
 */
//============================================================================================


//============================================================================================
//	固定文字列
//============================================================================================
// 「ポケモンじょうほう」
#define	WIN_P1_TITLE_PX		( 1 )
#define	WIN_P1_TITLE_PY		( 0 )
#define	WIN_P1_TITLE_SX		( 13 )
#define	WIN_P1_TITLE_SY		( 2 )
#define	WIN_P1_TITLE_PAL	( 15 )
#define	WIN_P1_TITLE_CGX	( 1 )
// 「トレーナーメモ」
#define	WIN_P2_TITLE_PX		( 1 )
#define	WIN_P2_TITLE_PY		( 0 )
#define	WIN_P2_TITLE_SX		( 11 )
#define	WIN_P2_TITLE_SY		( 2 )
#define	WIN_P2_TITLE_PAL	( 15 )
#define	WIN_P2_TITLE_CGX	( WIN_P1_TITLE_CGX + WIN_P1_TITLE_SX * WIN_P1_TITLE_SY )
// 「ポケモンのうりょく」
#define	WIN_P3_TITLE_PX		( 1 )
#define	WIN_P3_TITLE_PY		( 0 )
#define	WIN_P3_TITLE_SX		( 14 )
#define	WIN_P3_TITLE_SY		( 2 )
#define	WIN_P3_TITLE_PAL	( 15 )
#define	WIN_P3_TITLE_CGX	( WIN_P2_TITLE_CGX + WIN_P2_TITLE_SX * WIN_P2_TITLE_SY )
// 「コンディション」
#define	WIN_P4_TITLE_PX		( 1 )
#define	WIN_P4_TITLE_PY		( 0 )
#define	WIN_P4_TITLE_SX		( 11 )
#define	WIN_P4_TITLE_SY		( 2 )
#define	WIN_P4_TITLE_PAL	( 15 )
#define	WIN_P4_TITLE_CGX	( WIN_P3_TITLE_CGX + WIN_P3_TITLE_SX * WIN_P3_TITLE_SY )
// 「たたかうわざ」
#define	WIN_P5_TITLE_PX		( 1 )
#define	WIN_P5_TITLE_PY		( 0 )
#define	WIN_P5_TITLE_SX		( 9 )
#define	WIN_P5_TITLE_SY		( 2 )
#define	WIN_P5_TITLE_PAL	( 15 )
#define	WIN_P5_TITLE_CGX	( WIN_P4_TITLE_CGX + WIN_P4_TITLE_SX * WIN_P4_TITLE_SY )
// 「コンテストわざ」
#define	WIN_P6_TITLE_PX		( 1 )
#define	WIN_P6_TITLE_PY		( 0 )
#define	WIN_P6_TITLE_SX		( 11 )
#define	WIN_P6_TITLE_SY		( 2 )
#define	WIN_P6_TITLE_PAL	( 15 )
#define	WIN_P6_TITLE_CGX	( WIN_P5_TITLE_CGX + WIN_P5_TITLE_SX * WIN_P5_TITLE_SY )
// 「もちもの」
#define	WIN_MOTIMONO_PX		( 1 )
#define	WIN_MOTIMONO_PY		( 20 )
#define	WIN_MOTIMONO_SX		( 6 )
#define	WIN_MOTIMONO_SY		( 2 )
#define	WIN_MOTIMONO_PAL	( 15 )
#define	WIN_MOTIMONO_CGX	( WIN_P6_TITLE_CGX + WIN_P6_TITLE_SX * WIN_P6_TITLE_SY )
// 「ずかんNo.」
#define	WIN_P1_ZUKANNO_PX	( 14 )
#define	WIN_P1_ZUKANNO_PY	( 5 )
#define	WIN_P1_ZUKANNO_SX	( 9 )
#define	WIN_P1_ZUKANNO_SY	( 2 )
#define	WIN_P1_ZUKANNO_PAL	( 15 )
#define	WIN_P1_ZUKANNO_CGX	( WIN_MOTIMONO_CGX + WIN_MOTIMONO_SX * WIN_MOTIMONO_SY )
// 「なまえ」
#define	WIN_P1_NAME_PX		( 14 )
#define	WIN_P1_NAME_PY		( 7 )
#define	WIN_P1_NAME_SX		( 5 )
#define	WIN_P1_NAME_SY		( 2 )
#define	WIN_P1_NAME_PAL		( 15 )
#define	WIN_P1_NAME_CGX		( WIN_P1_ZUKANNO_CGX + WIN_P1_ZUKANNO_SX * WIN_P1_ZUKANNO_SY )
// 「タイプ」
#define	WIN_P1_TYPE_PX		( 14 )
#define	WIN_P1_TYPE_PY		( 9 )
#define	WIN_P1_TYPE_SX		( 5 )
#define	WIN_P1_TYPE_SY		( 2 )
#define	WIN_P1_TYPE_PAL		( 15 )
#define	WIN_P1_TYPE_CGX		( WIN_P1_NAME_CGX + WIN_P1_NAME_SX * WIN_P1_NAME_SY )
// 「おや」
#define	WIN_P1_OYA_PX		( 14 )
#define	WIN_P1_OYA_PY		( 11 )
#define	WIN_P1_OYA_SX		( 5 )
#define	WIN_P1_OYA_SY		( 2 )
#define	WIN_P1_OYA_PAL		( 15 )
#define	WIN_P1_OYA_CGX		( WIN_P1_TYPE_CGX + WIN_P1_TYPE_SX * WIN_P1_TYPE_SY )
// 「IDNo.」
#define	WIN_P1_IDNO_PX		( 14 )
#define	WIN_P1_IDNO_PY		( 13 )
#define	WIN_P1_IDNO_SX		( 5 )
#define	WIN_P1_IDNO_SY		( 2 )
#define	WIN_P1_IDNO_PAL		( 15 )
#define	WIN_P1_IDNO_CGX		( WIN_P1_OYA_CGX + WIN_P1_OYA_SX * WIN_P1_OYA_SY )
// 「げんざいの　けいけんち」
#define	WIN_P1_NOWEXP_PX	( 14 )
#define	WIN_P1_NOWEXP_PY	( 15 )
#define	WIN_P1_NOWEXP_SX	( 15 )
#define	WIN_P1_NOWEXP_SY	( 2 )
#define	WIN_P1_NOWEXP_PAL	( 15 )
#define	WIN_P1_NOWEXP_CGX	( WIN_P1_IDNO_CGX + WIN_P1_IDNO_SX * WIN_P1_IDNO_SY )
// 「つぎのレベルまで」
#define	WIN_P1_NEXTLV_PX	( 14 )
#define	WIN_P1_NEXTLV_PY	( 19 )
#define	WIN_P1_NEXTLV_SX	( 12 )
#define	WIN_P1_NEXTLV_SY	( 2 )
#define	WIN_P1_NEXTLV_PAL	( 15 )
#define	WIN_P1_NEXTLV_CGX	( WIN_P1_NOWEXP_CGX + WIN_P1_NOWEXP_SX * WIN_P1_NOWEXP_SY )
// 「あと」
#define	WIN_P1_ATO_PX		( 19 )
#define	WIN_P1_ATO_PY		( 21 )
#define	WIN_P1_ATO_SX		( 3 )
#define	WIN_P1_ATO_SY		( 2 )
#define	WIN_P1_ATO_PAL		( 15 )
#define	WIN_P1_ATO_CGX		( WIN_P1_NEXTLV_CGX + WIN_P1_NEXTLV_SX * WIN_P1_NEXTLV_SY )
// 「HP」
#define	WIN_P3_HP_PX		( 18 )
#define	WIN_P3_HP_PY		( 4 )
#define	WIN_P3_HP_SX		( 2 )
#define	WIN_P3_HP_SY		( 2 )
#define	WIN_P3_HP_PAL		( 15 )
#define	WIN_P3_HP_CGX		( WIN_P1_ATO_CGX + WIN_P1_ATO_SX * WIN_P1_ATO_SY )
// 「こうげき」
#define	WIN_P3_POW_PX		( 16 )
#define	WIN_P3_POW_PY		( 7 )
#define	WIN_P3_POW_SX		( 6 )
#define	WIN_P3_POW_SY		( 2 )
#define	WIN_P3_POW_PAL		( 15 )
#define	WIN_P3_POW_CGX		( WIN_P3_HP_CGX + WIN_P3_HP_SX * WIN_P3_HP_SY )
// 「ぼうぎょ」
#define	WIN_P3_DEF_PX		( 16 )
#define	WIN_P3_DEF_PY		( 9 )
#define	WIN_P3_DEF_SX		( 6 )
#define	WIN_P3_DEF_SY		( 2 )
#define	WIN_P3_DEF_PAL		( 15 )
#define	WIN_P3_DEF_CGX		( WIN_P3_POW_CGX + WIN_P3_POW_SX * WIN_P3_POW_SY )
// 「とくこう」
#define	WIN_P3_SPP_PX		( 16 )
#define	WIN_P3_SPP_PY		( 11 )
#define	WIN_P3_SPP_SX		( 6 )
#define	WIN_P3_SPP_SY		( 2 )
#define	WIN_P3_SPP_PAL		( 15 )
#define	WIN_P3_SPP_CGX		( WIN_P3_DEF_CGX + WIN_P3_DEF_SX * WIN_P3_DEF_SY )
// 「とくぼう」
#define	WIN_P3_SPD_PX		( 16 )
#define	WIN_P3_SPD_PY		( 13 )
#define	WIN_P3_SPD_SX		( 6 )
#define	WIN_P3_SPD_SY		( 2 )
#define	WIN_P3_SPD_PAL		( 15 )
#define	WIN_P3_SPD_CGX		( WIN_P3_SPP_CGX + WIN_P3_SPP_SX * WIN_P3_SPP_SY )
// 「すばやさ」
#define	WIN_P3_AGI_PX		( 16 )
#define	WIN_P3_AGI_PY		( 15 )
#define	WIN_P3_AGI_SX		( 6 )
#define	WIN_P3_AGI_SY		( 2 )
#define	WIN_P3_AGI_PAL		( 15 )
#define	WIN_P3_AGI_CGX		( WIN_P3_SPD_CGX + WIN_P3_SPD_SX * WIN_P3_SPD_SY )
// 「とくせい」
#define	WIN_P3_SPA_PX		( 14 )
#define	WIN_P3_SPA_PY		( 18 )
#define	WIN_P3_SPA_SX		( 6 )
#define	WIN_P3_SPA_SY		( 2 )
#define	WIN_P3_SPA_PAL		( 15 )
#define	WIN_P3_SPA_CGX		( WIN_P3_AGI_CGX + WIN_P3_AGI_SX * WIN_P3_AGI_SY )
// 「けづや」
#define	WIN_P4_KEDUYA_PX	( 14 )
#define	WIN_P4_KEDUYA_PY	( 20 )
#define	WIN_P4_KEDUYA_SX	( 5 )
#define	WIN_P4_KEDUYA_SY	( 2 )
#define	WIN_P4_KEDUYA_PAL	( 15 )
#define	WIN_P4_KEDUYA_CGX	( WIN_P3_SPA_CGX + WIN_P3_SPA_SX * WIN_P3_SPA_SY )
// 「せいかく」
#define	WIN_P4_SEIKAKU_PX	( 1 )
#define	WIN_P4_SEIKAKU_PY	( 22 )
#define	WIN_P4_SEIKAKU_SX	( 6 )
#define	WIN_P4_SEIKAKU_SY	( 2 )
#define	WIN_P4_SEIKAKU_PAL	( 15 )
#define	WIN_P4_SEIKAKU_CGX	( WIN_P4_KEDUYA_CGX + WIN_P4_KEDUYA_SX * WIN_P4_KEDUYA_SY )
/*
// 「くわしく」
#define	WIN_P5_KUWASIKU_PX	( 26 )
#define	WIN_P5_KUWASIKU_PY	( 0 )
#define	WIN_P5_KUWASIKU_SX	( 6 )
#define	WIN_P5_KUWASIKU_SY	( 2 )
#define	WIN_P5_KUWASIKU_PAL	( 15 )
#define	WIN_P5_KUWASIKU_CGX	( WIN_P4_SEIKAKU_CGX + WIN_P4_SEIKAKU_SX * WIN_P4_SEIKAKU_SY )
// 「いれかえ」
#define	WIN_P5_IREKAE_PX	( 26 )
#define	WIN_P5_IREKAE_PY	( 0 )
#define	WIN_P5_IREKAE_SX	( 6 )
#define	WIN_P5_IREKAE_SY	( 2 )
#define	WIN_P5_IREKAE_PAL	( 15 )
#define	WIN_P5_IREKAE_CGX	( WIN_P5_KUWASIKU_CGX + WIN_P5_KUWASIKU_SX * WIN_P5_KUWASIKU_SY )
// 「けってい」
#define	WIN_P5_KETTEI_PX	( 26 )
#define	WIN_P5_KETTEI_PY	( 0 )
#define	WIN_P5_KETTEI_SX	( 6 )
#define	WIN_P5_KETTEI_SY	( 2 )
#define	WIN_P5_KETTEI_PAL	( 15 )
#define	WIN_P5_KETTEI_CGX	( WIN_P5_IREKAE_CGX + WIN_P5_IREKAE_SX * WIN_P5_IREKAE_SY )
*/
// 「もどる」
#define	WIN_P5_MODORU_PX	( 21 )
#define	WIN_P5_MODORU_PY	( 20 )
#define	WIN_P5_MODORU_SX	( 5 )
#define	WIN_P5_MODORU_SY	( 2 )
#define	WIN_P5_MODORU_PAL	( 15 )
#define	WIN_P5_MODORU_CGX	( WIN_P4_SEIKAKU_CGX + WIN_P4_SEIKAKU_SX * WIN_P4_SEIKAKU_SY )
// 「ぶんるい」
#define	WIN_P5_BUNRUI_PX	( 1 )
#define	WIN_P5_BUNRUI_PY	( 8 )
#define	WIN_P5_BUNRUI_SX	( 6 )
#define	WIN_P5_BUNRUI_SY	( 2 )
#define	WIN_P5_BUNRUI_PAL	( 15 )
#define	WIN_P5_BUNRUI_CGX	( WIN_P5_MODORU_CGX + WIN_P5_MODORU_SX * WIN_P5_MODORU_SY )
// 「いりょく」
#define	WIN_P5_IRYOKU_PX	( 1 )
#define	WIN_P5_IRYOKU_PY	( 10 )
#define	WIN_P5_IRYOKU_SX	( 6 )
#define	WIN_P5_IRYOKU_SY	( 2 )
#define	WIN_P5_IRYOKU_PAL	( 15 )
#define	WIN_P5_IRYOKU_CGX	( WIN_P5_BUNRUI_CGX + WIN_P5_BUNRUI_SX * WIN_P5_BUNRUI_SY )
// 「めいちゅう」
#define	WIN_P5_HIT_PX	( 1 )
#define	WIN_P5_HIT_PY	( 12 )
#define	WIN_P5_HIT_SX	( 8 )
#define	WIN_P5_HIT_SY	( 2 )
#define	WIN_P5_HIT_PAL	( 15 )
#define	WIN_P5_HIT_CGX	( WIN_P5_IRYOKU_CGX + WIN_P5_IRYOKU_SX * WIN_P5_IRYOKU_SY )
/*
// 「もどる」
#define	WIN_P8_MODORU_PX	( 26 )
#define	WIN_P8_MODORU_PY	( 0 )
#define	WIN_P8_MODORU_SX	( 5 )
#define	WIN_P8_MODORU_SY	( 2 )
#define	WIN_P8_MODORU_PAL	( 15 )
#define	WIN_P8_MODORU_CGX	( WIN_P5_HIT_CGX + WIN_P5_HIT_SX * WIN_P5_HIT_SY )
*/
// 「もどります」
#define	WIN_P8_MODORIMASU_PX	( 18 )
#define	WIN_P8_MODORIMASU_PY	( 11 )
#define	WIN_P8_MODORIMASU_SX	( 9 )
#define	WIN_P8_MODORIMASU_SY	( 2 )
#define	WIN_P8_MODORIMASU_PAL	( 15 )
#define	WIN_P8_MODORIMASU_CGX	( WIN_P5_HIT_CGX + WIN_P5_HIT_SX * WIN_P5_HIT_SY )
// 「アピールポイント」
#define	WIN_P6_AP_POINT_PX	( 2 )
#define	WIN_P6_AP_POINT_PY	( 13 )
#define	WIN_P6_AP_POINT_SX	( 12 )
#define	WIN_P6_AP_POINT_SY	( 2 )
#define	WIN_P6_AP_POINT_PAL	( 15 )
#define	WIN_P6_AP_POINT_CGX	( WIN_P8_MODORIMASU_CGX + WIN_P8_MODORIMASU_SX * WIN_P8_MODORIMASU_SY )
// 「もっているかず」
#define	WIN_P7_MOTTEIRU_PX	( 14 )
#define	WIN_P7_MOTTEIRU_PY	( 21 )
#define	WIN_P7_MOTTEIRU_SX	( 12 )
#define	WIN_P7_MOTTEIRU_SY	( 2 )
#define	WIN_P7_MOTTEIRU_PAL	( 15 )
#define	WIN_P7_MOTTEIRU_CGX	( WIN_P6_AP_POINT_CGX + WIN_P6_AP_POINT_SX * WIN_P6_AP_POINT_SY )
// 「きねんリボン」
#define	WIN_P7_TITLE_PX		( 1 )
#define	WIN_P7_TITLE_PY		( 0 )
#define	WIN_P7_TITLE_SX		( 11 )
#define	WIN_P7_TITLE_SY		( 2 )
#define	WIN_P7_TITLE_PAL	( 15 )
#define	WIN_P7_TITLE_CGX	( WIN_P7_MOTTEIRU_CGX + WIN_P7_MOTTEIRU_SX * WIN_P7_MOTTEIRU_SY )


//============================================================================================
//	可変文字列
//============================================================================================
// アイテム名
#define	WIN_ITEMNAME_PX		( 1 )
#define	WIN_ITEMNAME_PY		( 22 )
#define	WIN_ITEMNAME_SX		( 12 )
#define	WIN_ITEMNAME_SY		( 2 )
#define	WIN_ITEMNAME_PAL	( 15 )
#define	WIN_ITEMNAME_CGX	( WIN_P7_TITLE_CGX + WIN_P7_TITLE_SX * WIN_P7_TITLE_SY )
// レベル
#define	WIN_LV_PX	( 1 )
#define	WIN_LV_PY	( 5 )
#define	WIN_LV_SX	( 6 )
#define	WIN_LV_SY	( 2 )
#define	WIN_LV_PAL	( 15 )
#define	WIN_LV_CGX	( WIN_ITEMNAME_CGX + WIN_ITEMNAME_SX * WIN_ITEMNAME_SY )
// ニックネーム
#define	WIN_NICKNAME_PX		( 3 )
#define	WIN_NICKNAME_PY		( 3 )
#define	WIN_NICKNAME_SX		( 9 )
#define	WIN_NICKNAME_SY		( 2 )
#define	WIN_NICKNAME_PAL	( 15 )
#define	WIN_NICKNAME_CGX	( WIN_LV_CGX + WIN_LV_SX * WIN_LV_SY )
// ガイドメッセージ
#define	WIN_GUIDE_PX		( 26 )
#define	WIN_GUIDE_PY		( 0 )
#define	WIN_GUIDE_SX		( 6 )
#define	WIN_GUIDE_SY		( 2 )
#define	WIN_GUIDE_PAL		( 15 )
#define	WIN_GUIDE_CGX		( WIN_NICKNAME_CGX + WIN_NICKNAME_SX * WIN_NICKNAME_SY )

/*** これ以降はページ毎の領域 ***/
#define	ADD_WIN_PAGE_CGX	( WIN_GUIDE_CGX + WIN_GUIDE_SX * WIN_GUIDE_SY )
// ページ１（ポケモン情報）
// 図鑑No.
#define	A_WIN_P1_LIBNUM_PX	( 23 )
#define	A_WIN_P1_LIBNUM_PY	( 5 )
#define	A_WIN_P1_LIBNUM_SX	( 6 )
#define	A_WIN_P1_LIBNUM_SY	( 2 )
#define	A_WIN_P1_LIBNUM_PAL	( 15 )
#define	A_WIN_P1_LIBNUM_CGX	( ADD_WIN_PAGE_CGX )
// 名前
#define	A_WIN_P1_NAME_PX	( 23 )
#define	A_WIN_P1_NAME_PY	( 7 )
#define	A_WIN_P1_NAME_SX	( 8 )
#define	A_WIN_P1_NAME_SY	( 2 )
#define	A_WIN_P1_NAME_PAL	( 15 )
#define	A_WIN_P1_NAME_CGX	( A_WIN_P1_LIBNUM_CGX + A_WIN_P1_LIBNUM_SX * A_WIN_P1_LIBNUM_SY )
// 親名
#define	A_WIN_P1_OYANAME_PX		( 23 )
#define	A_WIN_P1_OYANAME_PY		( 11 )
#define	A_WIN_P1_OYANAME_SX		( 8 )
#define	A_WIN_P1_OYANAME_SY		( 2 )
#define	A_WIN_P1_OYANAME_PAL	( 15 )
#define	A_WIN_P1_OYANAME_CGX	( A_WIN_P1_NAME_CGX + A_WIN_P1_NAME_SX * A_WIN_P1_NAME_SY )
// IDNo.
#define	A_WIN_P1_IDNO_PX	( 23 )
#define	A_WIN_P1_IDNO_PY	( 13 )
#define	A_WIN_P1_IDNO_SX	( 5 )
#define	A_WIN_P1_IDNO_SY	( 2 )
#define	A_WIN_P1_IDNO_PAL	( 15 )
#define	A_WIN_P1_IDNO_CGX	( A_WIN_P1_OYANAME_CGX + A_WIN_P1_OYANAME_SX * A_WIN_P1_OYANAME_SY )
// 現在の経験値
#define	A_WIN_P1_NOWEXP_PX	( 23 )
#define	A_WIN_P1_NOWEXP_PY	( 17 )
#define	A_WIN_P1_NOWEXP_SX	( 7 )
#define	A_WIN_P1_NOWEXP_SY	( 2 )
#define	A_WIN_P1_NOWEXP_PAL	( 15 )
#define	A_WIN_P1_NOWEXP_CGX	( A_WIN_P1_IDNO_CGX + A_WIN_P1_IDNO_SX * A_WIN_P1_IDNO_SY )
// 次のレベルまで@
#define	A_WIN_P1_NEXTEXP_PX		( 23 )
#define	A_WIN_P1_NEXTEXP_PY		( 21 )
#define	A_WIN_P1_NEXTEXP_SX		( 6 )
#define	A_WIN_P1_NEXTEXP_SY		( 2 )
#define	A_WIN_P1_NEXTEXP_PAL	( 15 )
#define	A_WIN_P1_NEXTEXP_CGX	( A_WIN_P1_NOWEXP_CGX+A_WIN_P1_NOWEXP_SX*A_WIN_P1_NOWEXP_SY )

// ページ２（トレーナーメモ）
// トレーナーメモ
#define	A_WIN_P2_TMEMO_PX	( 14 )
#define	A_WIN_P2_TMEMO_PY	( 5 )
#define	A_WIN_P2_TMEMO_SX	( 17 )
#define	A_WIN_P2_TMEMO_SY	( 18 )
#define	A_WIN_P2_TMEMO_PAL	( 15 )
#define	A_WIN_P2_TMEMO_CGX	( ADD_WIN_PAGE_CGX )

// ページ３（ポケモン能力）
// HP/MHP
#define	A_WIN_P3_HP_PX	( 23 )
#define	A_WIN_P3_HP_PY	( 4 )
#define	A_WIN_P3_HP_SX	( 7 )
#define	A_WIN_P3_HP_SY	( 2 )
#define	A_WIN_P3_HP_PAL	( 15 )
#define	A_WIN_P3_HP_CGX	( ADD_WIN_PAGE_CGX )
// 攻撃
#define	A_WIN_P3_POW_PX		( 25 )
#define	A_WIN_P3_POW_PY		( 7 )
#define	A_WIN_P3_POW_SX		( 3 )
#define	A_WIN_P3_POW_SY		( 2 )
#define	A_WIN_P3_POW_PAL	( 15 )
#define	A_WIN_P3_POW_CGX	( A_WIN_P3_HP_CGX + A_WIN_P3_HP_SX * A_WIN_P3_HP_SY )
// 防御
#define	A_WIN_P3_DEF_PX		( 25 )
#define	A_WIN_P3_DEF_PY		( 9 )
#define	A_WIN_P3_DEF_SX		( 3 )
#define	A_WIN_P3_DEF_SY		( 2 )
#define	A_WIN_P3_DEF_PAL	( 15 )
#define	A_WIN_P3_DEF_CGX	( A_WIN_P3_POW_CGX + A_WIN_P3_POW_SX * A_WIN_P3_POW_SY )
// 特攻
#define	A_WIN_P3_SPP_PX		( 25 )
#define	A_WIN_P3_SPP_PY		( 11 )
#define	A_WIN_P3_SPP_SX		( 3 )
#define	A_WIN_P3_SPP_SY		( 2 )
#define	A_WIN_P3_SPP_PAL	( 15 )
#define	A_WIN_P3_SPP_CGX	( A_WIN_P3_DEF_CGX + A_WIN_P3_DEF_SX * A_WIN_P3_DEF_SY )
// 特防
#define	A_WIN_P3_SPD_PX		( 25 )
#define	A_WIN_P3_SPD_PY		( 13 )
#define	A_WIN_P3_SPD_SX		( 3 )
#define	A_WIN_P3_SPD_SY		( 2 )
#define	A_WIN_P3_SPD_PAL	( 15 )
#define	A_WIN_P3_SPD_CGX	( A_WIN_P3_SPP_CGX + A_WIN_P3_SPP_SX * A_WIN_P3_SPP_SY )
// 素早さ
#define	A_WIN_P3_AGI_PX		( 25 )
#define	A_WIN_P3_AGI_PY		( 15 )
#define	A_WIN_P3_AGI_SX		( 3 )
#define	A_WIN_P3_AGI_SY		( 2 )
#define	A_WIN_P3_AGI_PAL	( 15 )
#define	A_WIN_P3_AGI_CGX	( A_WIN_P3_SPD_CGX + A_WIN_P3_SPD_SX * A_WIN_P3_SPD_SY )
// 特性名
#define	A_WIN_P3_SPANAME_PX		( 21 )
#define	A_WIN_P3_SPANAME_PY		( 18 )
#define	A_WIN_P3_SPANAME_SX		( 11 )
#define	A_WIN_P3_SPANAME_SY		( 2 )
#define	A_WIN_P3_SPANAME_PAL	( 15 )
#define	A_WIN_P3_SPANAME_CGX	( A_WIN_P3_AGI_CGX + A_WIN_P3_AGI_SX * A_WIN_P3_AGI_SY )
// 特性説明
#define	A_WIN_P3_SPAINFO_PX		( 14 )
#define	A_WIN_P3_SPAINFO_PY		( 20 )
#define	A_WIN_P3_SPAINFO_SX		( 18 )
#define	A_WIN_P3_SPAINFO_SY		( 4 )
#define	A_WIN_P3_SPAINFO_PAL	( 15 )
#define	A_WIN_P3_SPAINFO_CGX	( A_WIN_P3_SPANAME_CGX+A_WIN_P3_SPANAME_SX*A_WIN_P3_SPANAME_SY )

// ページ５（戦う技）
// 技名１
#define	A_WIN_P5_WAZA1_PX	( 21 )
#define	A_WIN_P5_WAZA1_PY	( 4 )
#define	A_WIN_P5_WAZA1_SX	( 11 )
#define	A_WIN_P5_WAZA1_SY	( 4 )
#define	A_WIN_P5_WAZA1_PAL	( 15 )
#define	A_WIN_P5_WAZA1_CGX	( ADD_WIN_PAGE_CGX )
// 技名２
#define	A_WIN_P5_WAZA2_PX	( 21 )
#define	A_WIN_P5_WAZA2_PY	( 8 )
#define	A_WIN_P5_WAZA2_SX	( 11 )
#define	A_WIN_P5_WAZA2_SY	( 4 )
#define	A_WIN_P5_WAZA2_PAL	( 15 )
#define	A_WIN_P5_WAZA2_CGX	( A_WIN_P5_WAZA1_CGX + A_WIN_P5_WAZA1_SX * A_WIN_P5_WAZA1_SY )
// 技名３
#define	A_WIN_P5_WAZA3_PX	( 21 )
#define	A_WIN_P5_WAZA3_PY	( 12 )
#define	A_WIN_P5_WAZA3_SX	( 11 )
#define	A_WIN_P5_WAZA3_SY	( 4 )
#define	A_WIN_P5_WAZA3_PAL	( 15 )
#define	A_WIN_P5_WAZA3_CGX	( A_WIN_P5_WAZA2_CGX + A_WIN_P5_WAZA2_SX * A_WIN_P5_WAZA2_SY )
// 技名４
#define	A_WIN_P5_WAZA4_PX	( 21 )
#define	A_WIN_P5_WAZA4_PY	( 16 )
#define	A_WIN_P5_WAZA4_SX	( 11 )
#define	A_WIN_P5_WAZA4_SY	( 4 )
#define	A_WIN_P5_WAZA4_PAL	( 15 )
#define	A_WIN_P5_WAZA4_CGX	( A_WIN_P5_WAZA3_CGX + A_WIN_P5_WAZA3_SX * A_WIN_P5_WAZA3_SY )
// 技名５
#define	A_WIN_P5_WAZA5_PX	( 21 )
#define	A_WIN_P5_WAZA5_PY	( 20 )
#define	A_WIN_P5_WAZA5_SX	( 11 )
#define	A_WIN_P5_WAZA5_SY	( 4 )
#define	A_WIN_P5_WAZA5_PAL	( 15 )
#define	A_WIN_P5_WAZA5_CGX	( A_WIN_P5_WAZA4_CGX + A_WIN_P5_WAZA4_SX * A_WIN_P5_WAZA4_SY )
// 威力
#define	A_WIN_P5_ATC_PX		( 12 )
#define	A_WIN_P5_ATC_PY		( 10 )
#define	A_WIN_P5_ATC_SX		( 3 )
#define	A_WIN_P5_ATC_SY		( 2 )
#define	A_WIN_P5_ATC_PAL	( 15 )
#define	A_WIN_P5_ATC_CGX	( A_WIN_P5_WAZA5_CGX + A_WIN_P5_WAZA5_SX * A_WIN_P5_WAZA5_SY )
// 命中
#define	A_WIN_P5_HIT_PX		( 12 )
#define	A_WIN_P5_HIT_PY		( 12 )
#define	A_WIN_P5_HIT_SX		( 3 )
#define	A_WIN_P5_HIT_SY		( 2 )
#define	A_WIN_P5_HIT_PAL	( 15 )
#define	A_WIN_P5_HIT_CGX	( A_WIN_P5_ATC_CGX + A_WIN_P5_ATC_SX * A_WIN_P5_ATC_SY )
// 技説明
#define	A_WIN_P5_INFO_PX	( 1 )
#define	A_WIN_P5_INFO_PY	( 14 )
#define	A_WIN_P5_INFO_SX	( 15 )
#define	A_WIN_P5_INFO_SY	( 10 )
#define	A_WIN_P5_INFO_PAL	( 15 )
#define	A_WIN_P5_INFO_CGX	( A_WIN_P5_HIT_CGX + A_WIN_P5_HIT_SX * A_WIN_P5_HIT_SY )

// ページ６（コンテスト技）
// 技説明
#define	A_WIN_P6_INFO_PX	( 1 )
#define	A_WIN_P6_INFO_PY	( 18 )
#define	A_WIN_P6_INFO_SX	( 15 )
#define	A_WIN_P6_INFO_SY	( 6 )
#define	A_WIN_P6_INFO_PAL	( 15 )
#define	A_WIN_P6_INFO_CGX	( A_WIN_P5_WAZA5_CGX + A_WIN_P5_WAZA5_SX * A_WIN_P5_WAZA5_SY )

// ページ７（記念リボン）
// ???こ
#define	A_WIN_P7_NUM_PX		( 26 )
#define	A_WIN_P7_NUM_PY		( 21 )
#define	A_WIN_P7_NUM_SX		( 5 )
#define	A_WIN_P7_NUM_SY		( 2 )
#define	A_WIN_P7_NUM_PAL	( 15 )
#define	A_WIN_P7_NUM_CGX	( ADD_WIN_PAGE_CGX )
// ???/???
#define	A_WIN_P7_MAX_PX		( 24 )
#define	A_WIN_P7_MAX_PY		( 15 )
#define	A_WIN_P7_MAX_SX		( 7 )
#define	A_WIN_P7_MAX_SY		( 2 )
#define	A_WIN_P7_MAX_PAL	( 15 )
#define	A_WIN_P7_MAX_CGX	( A_WIN_P7_NUM_CGX + A_WIN_P7_NUM_SX * A_WIN_P7_NUM_SY )
// リボン名
#define	A_WIN_P7_NAME_PX	( 1 )
#define	A_WIN_P7_NAME_PY	( 18 )
#define	A_WIN_P7_NAME_SX	( 21 )
#define	A_WIN_P7_NAME_SY	( 2 )
#define	A_WIN_P7_NAME_PAL	( 15 )
#define	A_WIN_P7_NAME_CGX	( A_WIN_P7_MAX_CGX + A_WIN_P7_MAX_SX * A_WIN_P7_MAX_SY )
// リボン説明
#define	A_WIN_P7_INFO_PX	( 1 )
#define	A_WIN_P7_INFO_PY	( 20 )
#define	A_WIN_P7_INFO_SX	( 30 )
#define	A_WIN_P7_INFO_SY	( 4 )
#define	A_WIN_P7_INFO_PAL	( 15 )
#define	A_WIN_P7_INFO_CGX	( A_WIN_P7_NAME_CGX + A_WIN_P7_NAME_SX * A_WIN_P7_NAME_SY )


//============================================================================================
//============================================================================================
// ポルト関連のコンディションページ
// 「けってい」
#define	A_WIN_COND_KETTEI_PX	( 26 )
#define	A_WIN_COND_KETTEI_PY	( 0 )
#define	A_WIN_COND_KETTEI_SX	( 5 )
#define	A_WIN_COND_KETTEI_SY	( 2 )
#define	A_WIN_COND_KETTEI_PAL	( 15 )
#define	A_WIN_COND_KETTEI_CGX	( ADD_WIN_PAGE_CGX )
// 「もどる」
#define	A_WIN_COND_MODORU_PX	( 28 )
#define	A_WIN_COND_MODORU_PY	( 0 )
#define	A_WIN_COND_MODORU_SX	( 4 )
#define	A_WIN_COND_MODORU_SY	( 2 )
#define	A_WIN_COND_MODORU_PAL	( 15 )
#define	A_WIN_COND_MODORU_CGX	(A_WIN_COND_KETTEI_CGX+A_WIN_COND_KETTEI_SX*A_WIN_COND_KETTEI_SY)
// 「すきなたべもの」
#define	A_WIN_COND_LIKE_PX		( 1 )
#define	A_WIN_COND_LIKE_PY		( 20 )
#define	A_WIN_COND_LIKE_SX		( 12 )
#define	A_WIN_COND_LIKE_SY		( 4 )
#define	A_WIN_COND_LIKE_PAL		( 15 )
#define	A_WIN_COND_LIKE_CGX		(A_WIN_COND_MODORU_CGX+A_WIN_COND_MODORU_SX*A_WIN_COND_MODORU_SY)
// メッセージ
#define	A_WIN_COND_MSG_PX		( 2 )
#define	A_WIN_COND_MSG_PY		( 21 )
#define	A_WIN_COND_MSG_SX		( 27 )
#define	A_WIN_COND_MSG_SY		( 2 )
#define	A_WIN_COND_MSG_PAL		( 14 )
#define	A_WIN_COND_MSG_CGX		( A_WIN_COND_LIKE_CGX + A_WIN_COND_LIKE_SX * A_WIN_COND_LIKE_SY )
