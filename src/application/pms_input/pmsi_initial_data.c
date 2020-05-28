//============================================================================================
/**
 * @file	pmsi_initial_data.c
 * @bfief	簡易会話入力画面（カテゴリイニシャルモード用のデータテーブル処理）
 * @author	taya
 * @date	06.02.14
 */
//============================================================================================
#include "common.h"
#include "gflib\heapsys.h"
#include "gflib\strbuf_family.h"
#include "system\arc_util.h"
#include "system\window.h"
#include "system\buflen.h"
#include "system\pms_word.h"
#include "system\winframe.naix"
#include "system\msgdata.h"
#include "msgdata\msg_pms_category.h"
#include "msgdata\msg.naix"


#include "pms_input_prv.h"
#include "pmsi_initial_data.h"

//======================================================================
// イニシャルモード時の選択文字テーブル（言語ごとに設定）
//======================================================================

//-------------------------------------------------------------
/**
 *  各文字の描画幅
 */
//-------------------------------------------------------------
enum {
	INITIAL_WRITE_X_MARGIN = 13,		// １文字ごとの描画幅
	INITIAL_WRITE_Y_MARGIN = 16,		// １文字ごとの描画高さ
};

#define INITIAL_XPOS(n)	((n)*INITIAL_WRITE_X_MARGIN)
#define INITIAL_YPOS(n)	((n)*INITIAL_WRITE_Y_MARGIN)

//-------------------------------------------------------------
/**
 *  各文字のインデックス
 */
//-------------------------------------------------------------
enum {
	INI_A = 0,
	INI_I,
	INI_U,
	INI_E,
	INI_O,
	INI_KA,
	INI_KI,
	INI_KU,
	INI_KE,
	INI_KO,
	INI_SA,
	INI_SI,
	INI_SU,
	INI_SE,
	INI_SO,
	INI_TA,
	INI_TI,
	INI_TU,
	INI_TE,
	INI_TO,
	INI_NA,
	INI_NI,
	INI_NU,
	INI_NE,
	INI_NO,
	INI_HA,
	INI_HI,
	INI_HU,
	INI_HE,
	INI_HO,
	INI_MA,
	INI_MI,
	INI_MU,
	INI_ME,
	INI_MO,
	INI_YA,
	INI_YU,
	INI_YO,
	INI_RA,
	INI_RI,
	INI_RU,
	INI_RE,
	INI_RO,
	INI_WA,
	INI_OTHER,

	INI_BACK = CATEGORY_POS_BACK,
	INI_DIS  = CATEGORY_POS_DISABLE,
};

static const struct {
	STRCODE		code;
	u8			xpos;
	u8			ypos;
	u8			up;
	u8			down;
	u8			left;
	u8			right;
	u8			col_top;
	u8			col_bottom;
}InitialParamTbl[] = {

	{  a_,  INITIAL_XPOS(0),  INITIAL_YPOS(0), INI_BACK,    INI_KA,      INI_YO,    INI_I,     INI_A,   INI_TA, },
	{  i_,  INITIAL_XPOS(1),  INITIAL_YPOS(0), INI_BACK,    INI_KI,      INI_A,     INI_U,     INI_I,   INI_TI, },
	{  u_,  INITIAL_XPOS(2),  INITIAL_YPOS(0), INI_BACK,    INI_KU,      INI_I,     INI_E,     INI_U,   INI_TU, },
	{  e_,  INITIAL_XPOS(3),  INITIAL_YPOS(0), INI_BACK,    INI_KE,      INI_U,     INI_O,     INI_E,   INI_TE, },
	{  o_,  INITIAL_XPOS(4),  INITIAL_YPOS(0), INI_BACK,    INI_KO,      INI_E,     INI_NA,    INI_O,   INI_TO, },
	{ ka_,  INITIAL_XPOS(0),  INITIAL_YPOS(1), INI_A,       INI_SA,      INI_OTHER, INI_KI,    INI_A,   INI_TA, },
	{ ki_,  INITIAL_XPOS(1),  INITIAL_YPOS(1), INI_I,       INI_SI,      INI_KA,    INI_KU,    INI_I,   INI_TI, },
	{ ku_,  INITIAL_XPOS(2),  INITIAL_YPOS(1), INI_U,       INI_SU,      INI_KI,    INI_KE,    INI_U,   INI_TU, },
	{ ke_,  INITIAL_XPOS(3),  INITIAL_YPOS(1), INI_E,       INI_SE,      INI_KU,    INI_KO,    INI_E,   INI_TE, },
	{ ko_,  INITIAL_XPOS(4),  INITIAL_YPOS(1), INI_O,       INI_SO,      INI_KE,    INI_HA,    INI_O,   INI_TO, },
	{ sa_,  INITIAL_XPOS(0),  INITIAL_YPOS(2), INI_KA,      INI_TA,      INI_MO,    INI_SI,    INI_A,   INI_TA, },
	{ si_,  INITIAL_XPOS(1),  INITIAL_YPOS(2), INI_KI,      INI_TI,      INI_SA,    INI_SU,    INI_I,   INI_TI, },
	{ su_,  INITIAL_XPOS(2),  INITIAL_YPOS(2), INI_KU,      INI_TU,      INI_SI,    INI_SE,    INI_U,   INI_TU, },
	{ se_,  INITIAL_XPOS(3),  INITIAL_YPOS(2), INI_KE,      INI_TE,      INI_SU,    INI_SO,    INI_E,   INI_TE, },
	{ so_,  INITIAL_XPOS(4),  INITIAL_YPOS(2), INI_KO,      INI_TO,      INI_SE,    INI_MA,    INI_O,   INI_TO, },
	{ ta_,  INITIAL_XPOS(0),  INITIAL_YPOS(3), INI_SA,      INI_BACK,    INI_RO,    INI_TI,    INI_A,   INI_TA, },
	{ ti_,  INITIAL_XPOS(1),  INITIAL_YPOS(3), INI_SI,      INI_BACK,    INI_TA,    INI_TU,    INI_I,   INI_TI, },
	{ tu_,  INITIAL_XPOS(2),  INITIAL_YPOS(3), INI_SU,      INI_BACK,    INI_TI,    INI_TE,    INI_U,   INI_TU, },
	{ te_,  INITIAL_XPOS(3),  INITIAL_YPOS(3), INI_SE,      INI_BACK,    INI_TU,    INI_TO,    INI_E,   INI_TE, },
	{ to_,  INITIAL_XPOS(4),  INITIAL_YPOS(3), INI_SO,      INI_BACK,    INI_TE,    INI_RA,    INI_O,   INI_TO, },
	{ na_,  INITIAL_XPOS(6),  INITIAL_YPOS(0), INI_BACK,    INI_HA,      INI_O,     INI_NI,    INI_NA,  INI_RA, },
	{ ni_,  INITIAL_XPOS(7),  INITIAL_YPOS(0), INI_BACK,    INI_HI,      INI_NA,    INI_NU,    INI_NI,  INI_RI, },
	{ nu_,  INITIAL_XPOS(8),  INITIAL_YPOS(0), INI_BACK,    INI_HU,      INI_NI,    INI_NE,    INI_NU,  INI_RU, },
	{ ne_,  INITIAL_XPOS(9),  INITIAL_YPOS(0), INI_BACK,    INI_HE,      INI_NU,    INI_NO,    INI_NE,  INI_RE, },
	{ no_,  INITIAL_XPOS(10), INITIAL_YPOS(0), INI_BACK,    INI_HO,      INI_NE,    INI_YA,    INI_NO,  INI_RO, },
	{ ha_,  INITIAL_XPOS(6),  INITIAL_YPOS(1), INI_NA,      INI_MA,      INI_KO,    INI_HI,    INI_NA,  INI_RA, },
	{ hi_,  INITIAL_XPOS(7),  INITIAL_YPOS(1), INI_NI,      INI_MI,      INI_HA,    INI_HU,    INI_NI,  INI_RI, },
	{ hu_,  INITIAL_XPOS(8),  INITIAL_YPOS(1), INI_NU,      INI_MU,      INI_HI,    INI_HE,    INI_NU,  INI_RU, },
	{ he_,  INITIAL_XPOS(9),  INITIAL_YPOS(1), INI_NE,      INI_ME,      INI_HU,    INI_HO,    INI_NE,  INI_RE, },
	{ ho_,  INITIAL_XPOS(10), INITIAL_YPOS(1), INI_NO,      INI_MO,      INI_HE,    INI_WA,    INI_NO,  INI_RO, },
	{ ma_,  INITIAL_XPOS(6),  INITIAL_YPOS(2), INI_HA,      INI_RA,      INI_SO,    INI_MI,    INI_NA,  INI_RA, },
	{ mi_,  INITIAL_XPOS(7),  INITIAL_YPOS(2), INI_HI,      INI_RI,      INI_MA,    INI_MU,    INI_NI,  INI_RI, },
	{ mu_,  INITIAL_XPOS(8),  INITIAL_YPOS(2), INI_HU,      INI_RU,      INI_MI,    INI_ME,    INI_NU,  INI_RU, },
	{ me_,  INITIAL_XPOS(9),  INITIAL_YPOS(2), INI_HE,      INI_RE,      INI_MU,    INI_MO,    INI_NE,  INI_RE, },
	{ mo_,  INITIAL_XPOS(10), INITIAL_YPOS(2), INI_HO,      INI_RO,      INI_ME,    INI_SA,    INI_NO,  INI_RO, },
	{ ya_,  INITIAL_XPOS(12), INITIAL_YPOS(0), INI_BACK,    INI_WA,      INI_NO,    INI_YU,    INI_YA,  INI_WA, },
	{ yu_,  INITIAL_XPOS(13), INITIAL_YPOS(0), INI_BACK,    INI_OTHER,   INI_YA,    INI_YO,    INI_YU,  INI_OTHER, },
	{ yo_,  INITIAL_XPOS(14), INITIAL_YPOS(0), INI_BACK,    INI_BACK,    INI_YU,    INI_A,     INI_YO,  INI_YO, },
	{ ra_,  INITIAL_XPOS(6),  INITIAL_YPOS(3), INI_MA,      INI_BACK,    INI_TO,    INI_RI,    INI_NA,  INI_RA, },
	{ ri_,  INITIAL_XPOS(7),  INITIAL_YPOS(3), INI_MI,      INI_BACK,    INI_RA,    INI_RU,    INI_NI,  INI_RI, },
	{ ru_,  INITIAL_XPOS(8),  INITIAL_YPOS(3), INI_MU,      INI_BACK,    INI_RI,    INI_RE,    INI_NU,  INI_RU, },
	{ re_,  INITIAL_XPOS(9),  INITIAL_YPOS(3), INI_ME,      INI_BACK,    INI_RU,    INI_RO,    INI_NE,  INI_RE, },
	{ ro_,  INITIAL_XPOS(10), INITIAL_YPOS(3), INI_MO,      INI_BACK,    INI_RE,    INI_TA,    INI_NO,  INI_RO, },
	{ wa_,  INITIAL_XPOS(12), INITIAL_YPOS(1), INI_YA,      INI_BACK,    INI_HO,    INI_OTHER, INI_YA,  INI_WA, },
	{ gyoe_,INITIAL_XPOS(13), INITIAL_YPOS(1), INI_YU,      INI_BACK,    INI_WA,    INI_KA,    INI_YU,  INI_OTHER },


};




//------------------------------------------------------------------
/**
 * イニシャルナンバー最大を返す
 *
 * @retval  u32		
 */
//------------------------------------------------------------------
u32 PMSI_INITIAL_DAT_GetInitialMax( void )
{
	return NELEMS(InitialParamTbl);
}

//------------------------------------------------------------------
/**
 * １文字の文字コードをバッファにコピー
 *
 * @param   initial		イニシャルナンバー
 * @param   buf			コピー先バッファ
 *
 */
//------------------------------------------------------------------
void PMSI_INITIAL_DAT_GetStr( u32 initial, STRBUF* buf )
{
	GF_ASSERT(initial < NELEMS(InitialParamTbl));

	STRBUF_SetStringCodeOrderLength( buf, &(InitialParamTbl[initial].code), 2);
}

//------------------------------------------------------------------
/**
 * 描画用基準位置（ドット単位）を取得
 *
 * @param   initial		イニシャルナンバー
 * @param   x			描画位置Ｘ
 * @param   y			描画位置Ｙ
 *
 */
//------------------------------------------------------------------
void PMSI_INITIAL_DAT_GetPrintPos( u32 initial, u32* x, u32* y )
{
	GF_ASSERT_MSG((initial < NELEMS(InitialParamTbl)), "pos=%d", initial);

	*x = InitialParamTbl[initial].xpos;
	*y = InitialParamTbl[initial].ypos;
}

//------------------------------------------------------------------
/**
 * 上キー押下時の移動先イニシャルナンバーを返す
 *
 * @param   initial		イニシャルナンバー
 *
 * @retval  int		移動先イニシャルナンバー
 */
//------------------------------------------------------------------
int PMSI_INITIAL_DAT_GetUpCode( u32 initial )
{
	GF_ASSERT(initial < NELEMS(InitialParamTbl));
	return InitialParamTbl[initial].up;
}

//------------------------------------------------------------------
/**
 * 下キー押下時の移動先イニシャルナンバーを返す
 *
 * @param   initial		イニシャルナンバー
 *
 * @retval  int		移動先イニシャルナンバー
 */
//------------------------------------------------------------------
int PMSI_INITIAL_DAT_GetDownCode( u32 initial )
{
	GF_ASSERT(initial < NELEMS(InitialParamTbl));
	return InitialParamTbl[initial].down;
}

//------------------------------------------------------------------
/**
 * 左キー押下時の移動先イニシャルナンバーを返す
 *
 * @param   initial		イニシャルナンバー
 *
 * @retval  int		移動先イニシャルナンバー
 */
//------------------------------------------------------------------
int PMSI_INITIAL_DAT_GetLeftCode( u32 initial )
{
	GF_ASSERT(initial < NELEMS(InitialParamTbl));
	return InitialParamTbl[initial].left;
}

//------------------------------------------------------------------
/**
 * 右キー押下時の移動先イニシャルナンバーを返す
 *
 * @param   initial		イニシャルナンバー
 *
 * @retval  int		移動先イニシャルナンバー
 */
//------------------------------------------------------------------
int PMSI_INITIAL_DAT_GetRightCode( u32 initial )
{
	GF_ASSERT(initial < NELEMS(InitialParamTbl));
	return InitialParamTbl[initial].right;
}

//------------------------------------------------------------------
/**
 * 指定キーのある列の最上段ナンバーを返す
 *
 * @param   initial		イニシャルナンバー
 *
 * @retval  int		移動先イニシャルナンバー
 */
//------------------------------------------------------------------
int PMSI_INITIAL_DAT_GetColTopCode( u32 initial )
{
	GF_ASSERT(initial < NELEMS(InitialParamTbl));
	return InitialParamTbl[initial].col_top;
}

//------------------------------------------------------------------
/**
 * 指定キーのある列の最下段ナンバーを返す
 *
 * @param   initial		イニシャルナンバー
 *
 * @retval  int		移動先イニシャルナンバー
 */
//------------------------------------------------------------------
int PMSI_INITIAL_DAT_GetColBottomCode( u32 initial )
{
	GF_ASSERT(initial < NELEMS(InitialParamTbl));
	return InitialParamTbl[initial].col_bottom;
}


