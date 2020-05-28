//============================================================================================
/**
 * @file	agb_str.c
 * @brief	AGB -> DP 文字列変換
 * @author	taya
 * @date	2006.06.15
 */
//============================================================================================
#include "common.h"
#include "gflib\strcode.h"

#include "system\agb_str.h"




static const STRCODE CodeTable[][2] = {
	{ spc_, spc_ },	// 0x00
	{ a_, a_ },		
	{ i_, i_ },		
	{ u_, u_ },		
	{ e_, e_ },		
	{ o_, o_ },		
	{ ka_, ka_ },	
	{ ki_, ki_ },	
	{ ku_, ku_ },	
	{ ke_, ke_ },	
	{ ko_, ko_ },	
	{ sa_, sa_ },	
	{ si_, si_ },	
	{ su_, su_ },	
	{ se_, se_ },	
	{ so_, so_ },	
	{ ta_, ta_ },	// 0x10
	{ ti_, ti_ },	
	{ tu_, tu_ },	
	{ te_, te_ },	
	{ to_, to_ },	
	{ na_, na_ },	
	{ ni_, ni_ },	
	{ nu_, nu_ },	
	{ ne_, ne_ },	
	{ no_, no_ },	
	{ ha_, ha_ },	
	{ hi_, hi_ },	
	{ hu_, hu_ },	
	{ he_, he_ },	
	{ ho_, ho_ },	
	{ ma_, ma_ },	
	{ mi_, mi_ },	// 0x20
	{ mu_, mu_ },	
	{ me_, me_ },	
	{ mo_, mo_ },	
	{ ya_, ya_ },	
	{ yu_, yu_ },	
	{ yo_, yo_ },	
	{ ra_, ra_ },	
	{ ri_, ri_ },	
	{ ru_, ru_ },	
	{ re_, re_ },	
	{ ro_, ro_ },	
	{ wa_, wa_ },	
	{ wo_, wo_ },	
	{ n_, n_ },		
	{ aa_, aa_ },	
	{ ii_, ii_ },	// 0x30
	{ uu_, uu_ },	
	{ ee_, ee_ },	
	{ oo_, oo_ },	
	{ yya_, yya_ },	
	{ yyu_, yyu_ },	
	{ yyo_, yyo_ },	
	{ ga_, ga_ },	
	{ gi_, gi_ },	
	{ gu_, gu_ },	
	{ ge_, ge_ },	
	{ go_, go_ },	
	{ za_, za_ },	
	{ zi_, zi_ },	
	{ zu_, zu_ },	
	{ ze_, ze_ },	
	{ zo_, zo_ },	// 0x40
	{ da_, da_ },	
	{ di_, di_ },	
	{ du_, du_ },	
	{ de_, de_ },	
	{ do_, do_ },	
	{ ba_, ba_ },	
	{ bi_, bi_ },	
	{ bu_, bu_ },	
	{ be_, be_ },	
	{ bo_, bo_ },	
	{ pa_, pa_ },	
	{ pi_, pi_ },	
	{ pu_, pu_ },	
	{ pe_, pe_ },	
	{ po_, po_ },	
	{ ttu_, ttu_ },	// 0x50
	{ A_, A_ },		
	{ I_, I_ },		
	{ U_, U_ },		
	{ E_, E_ },		
	{ O_, O_ },		
	{ KA_, KA_ },	
	{ KI_, KI_ },	
	{ KU_, KU_ },	
	{ KE_, KE_ },	
	{ KO_, KO_ },	
	{ SA_, SA_ },	
	{ SI_, SI_ },	
	{ SU_, SU_ },	
	{ SE_, SE_ },	
	{ SO_, SO_ },	
	{ TA_, TA_ },	// 0x60
	{ TI_, TI_ },	
	{ TU_, TU_ },	
	{ TE_, TE_ },	
	{ TO_, TO_ },	
	{ NA_, NA_ },	
	{ NI_, NI_ },	
	{ NU_, NU_ },	
	{ NE_, NE_ },	
	{ NO_, NO_ },	
	{ HA_, HA_ },	
	{ HI_, HI_ },	
	{ HU_, HU_ },	
	{ HE_, HE_ },	
	{ HO_, HO_ },	
	{ MA_, MA_ },	
	{ MI_, MI_ },	// 0x70
	{ MU_, MU_ },	
	{ ME_, ME_ },	
	{ MO_, MO_ },	
	{ YA_, YA_ },	
	{ YU_, YU_ },	
	{ YO_, YO_ },	
	{ RA_, RA_ },	
	{ RI_, RI_ },	
	{ RU_, RU_ },	
	{ RE_, RE_ },	
	{ RO_, RO_ },	
	{ WA_, WA_ },	
	{ WO_, WO_ },	
	{ N_, N_ },		
	{ AA_, AA_ },	
	{ II_, II_ },	// 0x80
	{ UU_, UU_ },	
	{ EE_, EE_ },	
	{ OO_, OO_ },	
	{ YYA_, YYA_ },	
	{ YYU_, YYU_ },	
	{ YYO_, YYO_ },	
	{ GA_, GA_ },	
	{ GI_, GI_ },	
	{ GU_, GU_ },	
	{ GE_, GE_ },	
	{ GO_, GO_ },	
	{ ZA_, ZA_ },	
	{ ZI_, ZI_ },	
	{ ZU_, ZU_ },	
	{ ZE_, ZE_ },	
	{ ZO_, ZO_ },	// 0x90
	{ DA_, DA_ },	
	{ DI_, DI_ },	
	{ DU_, DU_ },	
	{ DE_, DE_ },	
	{ DO_, DO_ },	
	{ BA_, BA_ },	
	{ BI_, BI_ },	
	{ BU_, BU_ },	
	{ BE_, BE_ },	
	{ BO_, BO_ },	
	{ PA_, PA_ },	
	{ PI_, PI_ },	
	{ PU_, PU_ },	
	{ PE_, PE_ },	
	{ PO_, PO_ },	
	{ TTU_, TTU_ },	// 0xa0
	{ n0_, h_n0_ },	
	{ n1_, h_n1_ },	
	{ n2_, h_n2_ },	
	{ n3_, h_n3_ },	
	{ n4_, h_n4_ },	
	{ n5_, h_n5_ },	
	{ n6_, h_n6_ },	
	{ n7_, h_n7_ },	
	{ n8_, h_n8_ },	
	{ n9_, h_n9_ },	
	{ gyoe_, h_gyoe_ },			
	{ hate_, h_hate_ },			
	{ kten_, h_period_ },		
	{ bou_, h_bou_ },			
	{ nakag_, h_nakag_ },		
	{ tenten_, h_tenten_ },		// 0xb0
	{ kako2_, kako2_ },			
	{ kakot2_, kakot2_ },		
	{ kako_, us_quote1_ },		
	{ kakot_, us_h_quote1_ },	
	{ osu_, h_osu_ },			
	{ mesu_, h_mesu_ },			
	{ yen_, yen_ },				
	{ ten_, h_comma_ },			
	{ times_, h_times_ },		
	{ sura_, h_sura_ },			
	{ A__, h_A__ },	
	{ B__, h_B__ },	
	{ C__, h_C__ },	
	{ D__, h_D__ },	
	{ E__, h_E__ },	
	{ F__, h_F__ },	// 0xc0
	{ G__, h_G__ },	
	{ H__, h_H__ },	
	{ I__, h_I__ },	
	{ J__, h_J__ },	
	{ K__, h_K__ },	
	{ L__, h_L__ },	
	{ M__, h_M__ },	
	{ N__, h_N__ },	
	{ O__, h_O__ },	
	{ P__, h_P__ },	
	{ Q__, h_Q__ },	
	{ R__, h_R__ },	
	{ S__, h_S__ },	
	{ T__, h_T__ },	
	{ U__, h_U__ },	
	{ V__, h_V__ },	// 0xd0
	{ W__, h_W__ },	
	{ X__, h_X__ },	
	{ Y__, h_Y__ },	
	{ Z__, h_Z__ },	
	{ a__, h_a__ },	
	{ b__, h_b__ },	
	{ c__, h_c__ },	
	{ d__, h_d__ },	
	{ e__, h_e__ },	
	{ f__, h_f__ },	
	{ g__, h_g__ },	
	{ h__, h_h__ },	
	{ i__, h_i__ },	
	{ j__, h_j__ },	
	{ k__, h_k__ },	
	{ l__, h_l__ },	// 0xe0
	{ m__, h_m__ },	
	{ n__, h_n__ },	
	{ o__, h_o__ },	
	{ p__, h_p__ },	
	{ q__, h_q__ },	
	{ r__, h_r__ },	
	{ s__, h_s__ },	
	{ t__, h_t__ },	
	{ u__, h_u__ },	
	{ v__, h_v__ },	
	{ w__, h_w__ },	
	{ x__, h_x__ },	
	{ y__, h_y__ },	
	{ z__, h_z__ },	
	{ cursor_, cursor_ },	
	{ colon_, h_colon_ },	// 0xf0
	{ Auml_, Auml_ },	
	{ Ouml_, Ouml_ },	
	{ Uuml_, Uuml_ },	
	{ auml_, auml_ },	
	{ ouml_, ouml_ },	
	{ uuml_, uuml_ },	
};





//------------------------------------------------------------------
/**
 * 各国語の引用符（開き）コードを取得
 *
 * @param   langCode		
 *
 * @retval  STRCODE		
 */
//------------------------------------------------------------------
static STRCODE get_kako2_code( u32 langCode )
{
	switch( langCode ){
	case LANG_JAPAN:
	default:
		return kako2_;

	case LANG_ENGLISH:
	case LANG_ITALY:
	case LANG_SPAIN:
		return us_quote2_;

	case LANG_FRANCE:
		return fre_quote_;

	case LANG_GERMANY:
		return ger_quote2_;
	}
}

//------------------------------------------------------------------
/**
 * 各国語の引用符（閉じ）コードを取得
 *
 * @param   langCode		
 *
 * @retval  STRCODE		
 */
//------------------------------------------------------------------
static STRCODE get_kakot2_code( u32 langCode )
{
	switch( langCode ){
	case LANG_JAPAN:
	default:
		return kakot2_;

	case LANG_ENGLISH:
	case LANG_ITALY:
	case LANG_SPAIN:
		return us_quote2d_;

	case LANG_FRANCE:
		return fre_quoted_;

	case LANG_GERMANY:
		return us_quote2_;
	}
}





#define AGB_EOM_CODE	(0xff)
#define UNKNOWN_STR_LEN	(5)

//------------------------------------------------------------------
/**
 * AGB -> DP 文字列変換
 *
 * @param   src				AGB文字列ポインタ
 * @param   dst				変換文字列の格納先バッファ
 * @param   dst_arysize		dstの要素数
 * @param   langCode		言語コード
 *
 * @retval	TRUEだと正常終了／FALSEだと変換できない文字が含まれていた（"?????"になる）
 */
//------------------------------------------------------------------
BOOL AGBSTR_to_DSSTR( const u8* src, STRCODE* dst, u32 dst_arysize, u32 langCode )
{
	u32 i, jp;

	jp = (langCode != LANG_JAPAN);

	for(i=0; i<(dst_arysize-1); i++)
	{
		if( src[i] == AGB_EOM_CODE )
		{
			break;
		}
		if( src[i] >= NELEMS(CodeTable) )
		{
			int p, max;

			max = ((dst_arysize-1) < UNKNOWN_STR_LEN)? (dst_arysize-1) : UNKNOWN_STR_LEN;
			for(p=0; p<max; p++)
			{
				dst[p] = hate_;
			}
			dst[p] = EOM_;
			return FALSE;
		}

		switch( CodeTable[src[i]][jp] ){
		case kako2_:
			dst[i] = get_kako2_code( langCode );
			break;

		case kakot2_:
			dst[i] = get_kakot2_code( langCode );
			break;

		default:
			dst[i] = CodeTable[src[i]][jp];
			break;
		}
	}

	dst[i] = EOM_;
	return TRUE;
}

