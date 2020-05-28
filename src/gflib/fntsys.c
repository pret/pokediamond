//=============================================================================================
/**
 * @file	fntsys.c
 * @brief	文字データ取得関数群(共通)
 * @author	tomo
 * @date	2004.10.28
 */
//=============================================================================================
#include <nitro.h>
#include <nnsys.h>
#include "assert.h"
#include "system.h"
#include "fntsys.h"
#include "fntequ_agb_jp.h"


STRCODE*  STRCODE_SkipTag( const STRCODE* str )
{
	GF_ASSERT(*str==_CTRL_TAG);

	if( *str == _CTRL_TAG )
	{
		u32  params;

		str += 2;			// タグ種類スキップ
		params = *str++;	// パラメータ数スキップ
		str += params;
	}
	return (STRCODE*)str;
}

u32  STRCODE_GetTagType( const STRCODE* str )
{
	GF_ASSERT(*str==_CTRL_TAG);
	return *(str+1);
}

BOOL STRCODE_CheckWordSetTagType( const STRCODE* str )
{
	u32 tag = STRCODE_GetTagType( str );
	return ((tag & NC_WORDSET_MASK) == NC_WORDSET);
}

u32  STRCODE_GetTagParam( const STRCODE* str, u32 param_no )
{
	GF_ASSERT(*str==_CTRL_TAG);

	{
		u32  params;

		str += 2;			// タグ種類スキップ
		params = *str++;	// パラメータ数スキップ

		GF_ASSERT(param_no < params);

		return str[param_no];
	}
}

//-------------------------------------------------------------------------------
//-------------------------------------------------------------------------------
//-------------------------------------------------------------------------------
//-------------------------------------------------------------------------------

#if 0
typedef struct{
	u8 agb_code;
	u16 ds_code;
	u8 dummy;
}DS_AGB_TRANS;

#define TRANS_NORMAL_CODE_MAX		247
static DS_AGB_TRANS ds_agb_normal_trans[TRANS_NORMAL_CODE_MAX]={
 {JP_AGB_spc_,spc_},
 {JP_AGB_a_,a_},
 {JP_AGB_i_,i_},
 {JP_AGB_u_,u_},
 {JP_AGB_e_,e_},
 {JP_AGB_o_,o_},
 {JP_AGB_ka_,ka_},
 {JP_AGB_ki_,ki_},
 {JP_AGB_ku_,ku_},
 {JP_AGB_ke_,ke_},
 {JP_AGB_ko_,ko_},
 {JP_AGB_sa_,sa_},
 {JP_AGB_si_,si_},
 {JP_AGB_su_,su_},
 {JP_AGB_se_,se_},
 {JP_AGB_so_,so_},
 {JP_AGB_ta_,ta_},
 {JP_AGB_ti_,ti_},
 {JP_AGB_tu_,tu_},
 {JP_AGB_te_,te_},
 {JP_AGB_to_,to_},
 {JP_AGB_na_,na_},
 {JP_AGB_ni_,ni_},
 {JP_AGB_nu_,nu_},
 {JP_AGB_ne_,ne_},
 {JP_AGB_no_,no_},
 {JP_AGB_ha_,ha_},
 {JP_AGB_hi_,hi_},
 {JP_AGB_hu_,hu_},
 {JP_AGB_he_,he_},
 {JP_AGB_ho_,ho_},
 {JP_AGB_ma_,ma_},
 {JP_AGB_mi_,mi_},
 {JP_AGB_mu_,mu_},
 {JP_AGB_me_,me_},
 {JP_AGB_mo_,mo_},
 {JP_AGB_ya_,ya_},
 {JP_AGB_yu_,yu_},
 {JP_AGB_yo_,yo_},
 {JP_AGB_ra_,ra_},
 {JP_AGB_ri_,ri_},
 {JP_AGB_ru_,ru_},
 {JP_AGB_re_,re_},
 {JP_AGB_ro_,ro_},
 {JP_AGB_wa_,wa_},
 {JP_AGB_wo_,wo_},
 {JP_AGB_n_,n_},
 {JP_AGB_aa_,aa_},
 {JP_AGB_ii_,ii_},
 {JP_AGB_uu_,uu_},
 {JP_AGB_ee_,ee_},
 {JP_AGB_oo_,oo_},
 {JP_AGB_yya_,yya_},
 {JP_AGB_yyu_,yyu_},
 {JP_AGB_yyo_,yyo_},
 {JP_AGB_ga_,ga_},
 {JP_AGB_gi_,gi_},
 {JP_AGB_gu_,gu_},
 {JP_AGB_ge_,ge_},
 {JP_AGB_go_,go_},
 {JP_AGB_za_,za_},
 {JP_AGB_zi_,zi_},
 {JP_AGB_zu_,zu_},
 {JP_AGB_ze_,ze_},
 {JP_AGB_zo_,zo_},
 {JP_AGB_da_,da_},
 {JP_AGB_di_,di_},
 {JP_AGB_du_,du_},
 {JP_AGB_de_,de_},
 {JP_AGB_do_,do_},
 {JP_AGB_ba_,ba_},
 {JP_AGB_bi_,bi_},
 {JP_AGB_bu_,bu_},
 {JP_AGB_be_,be_},
 {JP_AGB_bo_,bo_},
 {JP_AGB_pa_,pa_},
 {JP_AGB_pi_,pi_},
 {JP_AGB_pu_,pu_},
 {JP_AGB_pe_,pe_},
 {JP_AGB_po_,po_},
 {JP_AGB_ttu_,ttu_},
 {JP_AGB_A_,A_},
 {JP_AGB_I_,I_},
 {JP_AGB_U_,U_},
 {JP_AGB_E_,E_},
 {JP_AGB_O_,O_},
 {JP_AGB_KA_,KA_},
 {JP_AGB_KI_,KI_},
 {JP_AGB_KU_,KU_},
 {JP_AGB_KE_,KE_},
 {JP_AGB_KO_,KO_},
 {JP_AGB_SA_,SA_},
 {JP_AGB_SI_,SI_},
 {JP_AGB_SU_,SU_},
 {JP_AGB_SE_,SE_},
 {JP_AGB_SO_,SO_},
 {JP_AGB_TA_,TA_},
 {JP_AGB_TI_,TI_},
 {JP_AGB_TU_,TU_},
 {JP_AGB_TE_,TE_},
 {JP_AGB_TO_,TO_},
 {JP_AGB_NA_,NA_},
 {JP_AGB_NI_,NI_},
 {JP_AGB_NU_,NU_},
 {JP_AGB_NE_,NE_},
 {JP_AGB_NO_,NO_},
 {JP_AGB_HA_,HA_},
 {JP_AGB_HI_,HI_},
 {JP_AGB_HU_,HU_},
 {JP_AGB_HE_,HE_},
 {JP_AGB_HO_,HO_},
 {JP_AGB_MA_,MA_},
 {JP_AGB_MI_,MI_},
 {JP_AGB_MU_,MU_},
 {JP_AGB_ME_,ME_},
 {JP_AGB_MO_,MO_},
 {JP_AGB_YA_,YA_},
 {JP_AGB_YU_,YU_},
 {JP_AGB_YO_,YO_},
 {JP_AGB_RA_,RA_},
 {JP_AGB_RI_,RI_},
 {JP_AGB_RU_,RU_},
 {JP_AGB_RE_,RE_},
 {JP_AGB_RO_,RO_},
 {JP_AGB_WA_,WA_},
 {JP_AGB_WO_,WO_},
 {JP_AGB_N_,N_},
 {JP_AGB_AA_,AA_},
 {JP_AGB_II_,II_},
 {JP_AGB_UU_,UU_},
 {JP_AGB_EE_,EE_},
 {JP_AGB_OO_,OO_},
 {JP_AGB_YYA_,YYA_},
 {JP_AGB_YYU_,YYU_},
 {JP_AGB_YYO_,YYO_},
 {JP_AGB_GA_,GA_},
 {JP_AGB_GI_,GI_},
 {JP_AGB_GU_,GU_},
 {JP_AGB_GE_,GE_},
 {JP_AGB_GO_,GO_},
 {JP_AGB_ZA_,ZA_},
 {JP_AGB_ZI_,ZI_},
 {JP_AGB_ZU_,ZU_},
 {JP_AGB_ZE_,ZE_},
 {JP_AGB_ZO_,ZO_},
 {JP_AGB_DA_,DA_},
 {JP_AGB_DI_,DI_},
 {JP_AGB_DU_,DU_},
 {JP_AGB_DE_,DE_},
 {JP_AGB_DO_,DO_},
 {JP_AGB_BA_,BA_},
 {JP_AGB_BI_,BI_},
 {JP_AGB_BU_,BU_},
 {JP_AGB_BE_,BE_},
 {JP_AGB_BO_,BO_},
 {JP_AGB_PA_,PA_},
 {JP_AGB_PI_,PI_},
 {JP_AGB_PU_,PU_},
 {JP_AGB_PE_,PE_},
 {JP_AGB_PO_,PO_},
 {JP_AGB_TTU_,TTU_},
 {JP_AGB_n0_,n0_},
 {JP_AGB_n1_,n1_},
 {JP_AGB_n2_,n2_},
 {JP_AGB_n3_,n3_},
 {JP_AGB_n4_,n4_},
 {JP_AGB_n5_,n5_},
 {JP_AGB_n6_,n6_},
 {JP_AGB_n7_,n7_},
 {JP_AGB_n8_,n8_},
 {JP_AGB_n9_,n9_},
 {JP_AGB_gyoe_,gyoe_},
 {JP_AGB_hate_,hate_},
 {JP_AGB_kten_,kten_},
 {JP_AGB_bou_,bou_},
// {JP_AGB_nakag_,nakag_},
 {JP_AGB_tenten_,tenten_},
 {JP_AGB_kako2_,kako2_},
 {JP_AGB_kakot2_,kakot2_},
 {JP_AGB_kako_,kako_},
 {JP_AGB_kakot_,kakot_},
 {JP_AGB_osu_,osu_},
 {JP_AGB_mesu_,mesu_},
 {JP_AGB_yen_,yen_},
 {JP_AGB_ten_,ten_},
 {JP_AGB_batu_,times_},
 {JP_AGB_sura_,sura_},
 {JP_AGB_A__,A__},
 {JP_AGB_B__,B__},
 {JP_AGB_C__,C__},
 {JP_AGB_D__,D__},
 {JP_AGB_E__,E__},
 {JP_AGB_F__,F__},
 {JP_AGB_G__,G__},
 {JP_AGB_H__,H__},
 {JP_AGB_I__,I__},
 {JP_AGB_J__,J__},
 {JP_AGB_K__,K__},
 {JP_AGB_L__,L__},
 {JP_AGB_M__,M__},
 {JP_AGB_N__,N__},
 {JP_AGB_O__,O__},
 {JP_AGB_P__,P__},
 {JP_AGB_Q__,Q__},
 {JP_AGB_R__,R__},
 {JP_AGB_S__,S__},
 {JP_AGB_T__,T__},
 {JP_AGB_U__,U__},
 {JP_AGB_V__,V__},
 {JP_AGB_W__,W__},
 {JP_AGB_X__,X__},
 {JP_AGB_Y__,Y__},
 {JP_AGB_Z__,Z__},
 {JP_AGB_a__,a__},
 {JP_AGB_b__,b__},
 {JP_AGB_c__,c__},
 {JP_AGB_d__,d__},
 {JP_AGB_e__,e__},
 {JP_AGB_f__,f__},
 {JP_AGB_g__,g__},
 {JP_AGB_h__,h__},
 {JP_AGB_i__,i__},
 {JP_AGB_j__,j__},
 {JP_AGB_k__,k__},
 {JP_AGB_l__,l__},
 {JP_AGB_m__,m__},
 {JP_AGB_n__,n__},
 {JP_AGB_o__,o__},
 {JP_AGB_p__,p__},
 {JP_AGB_q__,q__},
 {JP_AGB_r__,r__},
 {JP_AGB_s__,s__},
 {JP_AGB_t__,t__},
 {JP_AGB_u__,u__},
 {JP_AGB_v__,v__},
 {JP_AGB_w__,w__},
 {JP_AGB_x__,x__},
 {JP_AGB_y__,y__},
 {JP_AGB_z__,z__},
 {JP_AGB_cursor_,cursor_},
 {JP_AGB_colon_,colon_},
 {JP_AGB_Auml_,Auml_},
 {JP_AGB_Ouml_,Ouml_},
 {JP_AGB_Uuml_,Uuml_},
 {JP_AGB_auml_,auml_},
 {JP_AGB_ouml_,ouml_},
 {JP_AGB_uuml_,uuml_}
};

#define TRANS_ETC_CODE_MAX		23
static DS_AGB_TRANS ds_agb_etc_trans[TRANS_ETC_CODE_MAX]={
 {JP_AGB_ArrowU__,ArrowU__},
 {JP_AGB_ArrowD__,ArrowD__},
 {JP_AGB_ArrowL__,ArrowL__},
 {JP_AGB_ArrowR__,ArrowR__},
// {JP_AGB_No__,No__},
// {JP_AGB_ID__,ID__},
// {JP_AGB_PP__,PP__},
// {JP_AGB_Lv__,Lv__},
// {JP_AGB_UnderBer_,UnderBar_},
 {JP_AGB_Plus__,Plus__},
// {JP_AGB_NijuMaru_,NijuMaru_},
// {JP_AGB_Sankaku_,Sankaku_},
 {JP_AGB_MaruKako__,MaruKako__},
 {JP_AGB_MaruKakot__,MaruKakot__},
};

//---------------------------------------------------------------------------------------------
/*
 *	文字コード変換　ポケモンＡＧＢ->ポケモンＤＳ
 *	※通常文字、終了、改行、トリガー待ち、バッファメッセージに対応
 *
 * @param	c_id		国番号(0:日本,1:....)
 * @param	agb_str		入力するＡＧＢ文字列のポインタ
 * @param	ds_str		出力するＤＳ文字列のポインタ
 *
 * @retval	ret		0:問題なし,1:解釈不可能なコードがあった（変換失敗）
 */
//---------------------------------------------------------------------------------------------
u8	GBAcode2DSuni(u8 c_id, u8 *agb_str, u16 *ds_str)
{
	u8 i,j,chk;

	//現在資料がないため、日本語のみ対応
	if(c_id!=0) return 1;

	for(i=0;i < 255;i++){
		if(*agb_str <= 0xf6){	//通常文字
			chk=0;
			for(j=0;j<TRANS_NORMAL_CODE_MAX;j++){
				if(*agb_str == ds_agb_normal_trans[j].agb_code) {
					*ds_str = ds_agb_normal_trans[j].ds_code;
					chk=1;
					break;
				}
			}

			//該当コードがなかったときエラー
			if(chk==0) return 1;
		}else{					//制御文字
			switch(*agb_str){
			case JP_AGB_EOM_:		//終了コード
				*ds_str = EOM_;
				return 0;
			case JP_AGB_CR_:		//改行コード
				*ds_str = CR_;
				break;
			case JP_AGB_NORMAL_WAIT_:		//"▼"		トリガー待ち→MSGエリアクリア
				*ds_str = NORMAL_WAIT_;
				break;
			case JP_AGB_SCROLL_WAIT_:		//"↓"		トリガー待ち→一行スクロール 
				*ds_str = SCROLL_WAIT_;
				break;
			case JP_AGB_I_MSG_:		//指定バッファのメッセージ展開(ID)
				*ds_str++ = I_MSG_;
				*ds_str = (u16)(*(++agb_str));
				break;
			case JP_AGB_S_MSG_:		//指定バッファのメッセージ展開(任意)
				*ds_str++ = S_MSG_;
				*ds_str = (u16)(*(++agb_str));
				break;
			case JP_AGB_EXFONT1_:	//拡張フォント(fontnum = 0x100～0x1ff)
				++agb_str;
				chk=0;
				for(j=0;j<TRANS_ETC_CODE_MAX;j++){
					if(*agb_str == ds_agb_etc_trans[j].agb_code) {
						*ds_str = ds_agb_etc_trans[j].ds_code;
						chk=1;
						break;
					}
				}

				//該当コードがなかったときエラー
				if(chk==0) return 1;
				break;
			case JP_AGB_EXICON_:	// 拡張アイコン(キーアイコン)
				//※現在キーアイコンなし
				break;
			case JP_AGB_CTRL_:		// フォント制御コマンド
				//※制御系が違うので未対応
				break;
			}
		}
		agb_str++;
		ds_str++;
	}

	//EOM_が検出できないor文章が255文字以上のときはエラー
	return 1;
}

//---------------------------------------------------------------------------------------------
/*
 *	文字コード変換　ポケモンＤＳ->ポケモンＡＧＢ
 *	※通常文字、終了、改行、トリガー待ち、バッファメッセージに対応
 *
 * @param	c_id		国番号(0:日本,1:....)
 * @param	ds_str		入力するＤＳ文字列のポインタ
 * @param	agb_str		出力するＡＧＢ文字列のポインタ
 *
 * @retval	ret		0:問題なし,1:解釈不可能なコードがあった（変換失敗）
 */
//---------------------------------------------------------------------------------------------
u8	DSuni2GBAcode(u8 c_id, u16 *ds_str, u8 *agb_str)
{
	u8 i,j,chk;

	//現在資料がないため、日本語のみ対応
	if(c_id!=0) return 1;

	for(i=0;i < 255;i++){

		switch(*ds_str){
		case EOM_:
			*agb_str = JP_AGB_EOM_;
			return 0;
		case CR_:
			*agb_str = JP_AGB_CR_;
			break;
		case NORMAL_WAIT_:		//"▼"		トリガー待ち→MSGエリアクリア
			*agb_str = JP_AGB_NORMAL_WAIT_;
			break;
		case SCROLL_WAIT_:		//"↓"		トリガー待ち→一行スクロール 
			*agb_str = JP_AGB_SCROLL_WAIT_;
			break;
		case I_MSG_:		//指定バッファのメッセージ展開(ID)
			*agb_str++ = JP_AGB_I_MSG_;
			*agb_str = (u8)(*(++ds_str));
			break;
		case S_MSG_:		//指定バッファのメッセージ展開(任意)
			*agb_str++ = JP_AGB_S_MSG_;
			*agb_str = (u8)(*(++ds_str));
			break;
		case EXICON_:	// 拡張アイコン(キーアイコン)
			//※現在キーアイコンなし
			break;
		case CTRL_:		// フォント制御コマンド
			//※制御系が違うので未対応
			break;
		default:
			chk=0;
			//通常文字チェック
			for(j=0;j<TRANS_NORMAL_CODE_MAX;j++){
				if(*ds_str == ds_agb_normal_trans[j].ds_code) {
					*agb_str = ds_agb_normal_trans[j].agb_code;
					chk=1;
					break;
				}
			}

			//拡張フォント(fontnum = 0x100～0x1ff)
			if(chk==0){
				for(j=0;j<TRANS_ETC_CODE_MAX;j++){
					if(*ds_str == ds_agb_etc_trans[j].ds_code) {
						*agb_str++ = JP_AGB_EXFONT1_;
						*agb_str = ds_agb_etc_trans[j].agb_code;
						chk=1;
						break;
					}
				}

				//該当コードがなかったときエラー
				if(chk==0) return 1;
			}

			break;
		}

		agb_str++;
		ds_str++;
	}

	//EOM_が検出できないor文章が255文字以上のときはエラー
	return 1;

}
#endif


#ifdef PM_DEBUG
//===============================================
//	ASCII 2 PokemonDP	Debug only!
//===============================================
typedef struct{
	u16 ds_code;
	u16 ascii_code;
}DS_ASCII2_TRANS;
typedef struct{
	u16	ds_code;
	u8	ascii_code;
	u8	dmy;
}DS_ASCII1_TRANS;

#define TRANS_DS2A2B_CODE_MAX		240
static DS_ASCII2_TRANS ds_to_ascii2_trans[TRANS_DS2A2B_CODE_MAX]={
 {spc_,'　'},
 {a_,'あ'},
 {i_,'い'},
 {u_,'う'},
 {e_,'え'},
 {o_,'お'},
 {ka_,'か'},
 {ki_,'き'},
 {ku_,'く'},
 {ke_,'け'},
 {ko_,'こ'},
 {sa_,'さ'},
 {si_,'し'},
 {su_,'す'},
 {se_,'せ'},
 {so_,'そ'},
 {ta_,'た'},
 {ti_,'ち'},
 {tu_,'つ'},
 {te_,'て'},
 {to_,'と'},
 {na_,'な'},
 {ni_,'に'},
 {nu_,'ぬ'},
 {ne_,'ね'},
 {no_,'の'},
 {ha_,'は'},
 {hi_,'ひ'},
 {hu_,'ふ'},
 {he_,'へ'},
 {ho_,'ほ'},
 {ma_,'ま'},
 {mi_,'み'},
 {mu_,'む'},
 {me_,'め'},
 {mo_,'も'},
 {ya_,'や'},
 {yu_,'ゆ'},
 {yo_,'よ'},
 {ra_,'ら'},
 {ri_,'り'},
 {ru_,'る'},
 {re_,'れ'},
 {ro_,'ろ'},
 {wa_,'わ'},
 {wo_,'を'},
 {n_,'ん'},
 {aa_,'ぁ'},
 {ii_,'ぃ'},
 {uu_,'ぅ'},
 {ee_,'ぇ'},
 {oo_,'ぉ'},
 {yya_,'ゃ'},
 {yyu_,'ゅ'},
 {yyo_,'ょ'},
 {ga_,'が'},
 {gi_,'ぎ'},
 {gu_,'ぐ'},
 {ge_,'げ'},
 {go_,'ご'},
 {za_,'ざ'},
 {zi_,'じ'},
 {zu_,'ず'},
 {ze_,'ぜ'},
 {zo_,'ぞ'},
 {da_,'だ'},
 {di_,'ぢ'},
 {du_,'づ'},
 {de_,'で'},
 {do_,'ど'},
 {ba_,'ば'},
 {bi_,'び'},
 {bu_,'ぶ'},
 {be_,'べ'},
 {bo_,'ぼ'},
 {pa_,'ぱ'},
 {pi_,'ぴ'},
 {pu_,'ぷ'},
 {pe_,'ぺ'},
 {po_,'ぽ'},
 {ttu_,'っ'},
 {A_,'ア'},
 {I_,'イ'},
 {U_,'ウ'},
 {E_,'エ'},
 {O_,'オ'},
 {KA_,'カ'},
 {KI_,'キ'},
 {KU_,'ク'},
 {KE_,'ケ'},
 {KO_,'コ'},
 {SA_,'サ'},
 {SI_,'シ'},
 {SU_,'ス'},
 {SE_,'セ'},
 {SO_,'ソ'},
 {TA_,'タ'},
 {TI_,'チ'},
 {TU_,'ツ'},
 {TE_,'テ'},
 {TO_,'ト'},
 {NA_,'ナ'},
 {NI_,'ニ'},
 {NU_,'ヌ'},
 {NE_,'ネ'},
 {NO_,'ノ'},
 {HA_,'ハ'},
 {HI_,'ヒ'},
 {HU_,'フ'},
 {HE_,'ヘ'},
 {HO_,'ホ'},
 {MA_,'マ'},
 {MI_,'ミ'},
 {MU_,'ム'},
 {ME_,'メ'},
 {MO_,'モ'},
 {YA_,'ヤ'},
 {YU_,'ユ'},
 {YO_,'ヨ'},
 {RA_,'ラ'},
 {RI_,'リ'},
 {RU_,'ル'},
 {RE_,'レ'},
 {RO_,'ロ'},
 {WA_,'ワ'},
 {WO_,'オ'},
 {N_,'ン'},
 {AA_,'ァ'},
 {II_,'ィ'},
 {UU_,'ゥ'},
 {EE_,'ェ'},
 {OO_,'ォ'},
 {YYA_,'ャ'},
 {YYU_,'ュ'},
 {YYO_,'ョ'},
 {GA_,'ガ'},
 {GI_,'ギ'},
 {GU_,'グ'},
 {GE_,'ゲ'},
 {GO_,'ゴ'},
 {ZA_,'ザ'},
 {ZI_,'ジ'},
 {ZU_,'ズ'},
 {ZE_,'ゼ'},
 {ZO_,'ゾ'},
 {DA_,'ダ'},
 {DI_,'ヂ'},
 {DU_,'ヅ'},
 {DE_,'デ'},
 {DO_,'ド'},
 {BA_,'バ'},
 {BI_,'ビ'},
 {BU_,'ブ'},
 {BE_,'ベ'},
 {BO_,'ボ'},
 {PA_,'パ'},
 {PI_,'ピ'},
 {PU_,'プ'},
 {PE_,'ペ'},
 {PO_,'ポ'},
 {TTU_,'ッ'},
 {n0_,'０'},
 {n1_,'１'},
 {n2_,'２'},
 {n3_,'３'},
 {n4_,'４'},
 {n5_,'５'},
 {n6_,'６'},
 {n7_,'７'},
 {n8_,'８'},
 {n9_,'９'},
 {gyoe_,'！'},
 {hate_,'？'},
 {kten_,'。'},
 {bou_,'ー'},
 {tenten_,'…'},
 {kako2_,'『'},
 {kakot2_,'』'},
 {kako_,'「'},
 {kakot_,'」'},
 {osu_,'♂'},
 {mesu_,'♀'},
 {yen_,'￥'},
 {ten_,'、'},
 {times_,'×'},
 {sura_,'／'},
 {A__,'Ａ'},
 {B__,'Ｂ'},
 {C__,'Ｃ'},
 {D__,'Ｄ'},
 {E__,'Ｅ'},
 {F__,'Ｆ'},
 {G__,'Ｇ'},
 {H__,'Ｈ'},
 {I__,'Ｉ'},
 {J__,'Ｊ'},
 {K__,'Ｋ'},
 {L__,'Ｌ'},
 {M__,'Ｍ'},
 {N__,'Ｎ'},
 {O__,'Ｏ'},
 {P__,'Ｐ'},
 {Q__,'Ｑ'},
 {R__,'Ｒ'},
 {S__,'Ｓ'},
 {T__,'Ｔ'},
 {U__,'Ｕ'},
 {V__,'Ｖ'},
 {W__,'Ｗ'},
 {X__,'Ｘ'},
 {Y__,'Ｙ'},
 {Z__,'Ｚ'},
 {a__,'ａ'},
 {b__,'ｂ'},
 {c__,'ｃ'},
 {d__,'ｄ'},
 {e__,'ｅ'},
 {f__,'ｆ'},
 {g__,'ｇ'},
 {h__,'ｈ'},
 {i__,'ｉ'},
 {j__,'ｊ'},
 {k__,'ｋ'},
 {l__,'ｌ'},
 {m__,'ｍ'},
 {n__,'ｎ'},
 {o__,'ｏ'},
 {p__,'ｐ'},
 {q__,'ｑ'},
 {r__,'ｒ'},
 {s__,'ｓ'},
 {t__,'ｔ'},
 {u__,'ｕ'},
 {v__,'ｖ'},
 {w__,'ｗ'},
 {x__,'ｘ'},
 {y__,'ｙ'},
 {z__,'ｚ'},
 {cursor_,'＞'},
 {colon_,'：'},
};

#define TRANS_DS2A1B_CODE_MAX	73	
static DS_ASCII1_TRANS ds_to_ascii1_trans[TRANS_DS2A1B_CODE_MAX]={
 {spc_,'_'},
 {n0_,'0'},
 {n1_,'1'},
 {n2_,'2'},
 {n3_,'3'},
 {n4_,'4'},
 {n5_,'5'},
 {n6_,'6'},
 {n7_,'7'},
 {n8_,'8'},
 {n9_,'9'},
 {gyoe_,'!'},
 {hate_,'?'},
 {kten_,'.'},
 {bou_,'-'},
 {yen_,'\\'},
 {ten_,','},
 {times_,'*'},
 {sura_,'/'},
 {A__,'A'},
 {B__,'B'},
 {C__,'C'},
 {D__,'D'},
 {E__,'E'},
 {F__,'F'},
 {G__,'G'},
 {H__,'H'},
 {I__,'I'},
 {J__,'J'},
 {K__,'K'},
 {L__,'L'},
 {M__,'M'},
 {N__,'N'},
 {O__,'O'},
 {P__,'P'},
 {Q__,'Q'},
 {R__,'R'},
 {S__,'S'},
 {T__,'T'},
 {U__,'U'},
 {V__,'V'},
 {W__,'W'},
 {X__,'X'},
 {Y__,'Y'},
 {Z__,'Z'},
 {a__,'a'},
 {b__,'b'},
 {c__,'c'},
 {d__,'d'},
 {e__,'e'},
 {f__,'f'},
 {g__,'g'},
 {h__,'h'},
 {i__,'i'},
 {j__,'j'},
 {k__,'k'},
 {l__,'l'},
 {m__,'m'},
 {n__,'n'},
 {o__,'o'},
 {p__,'p'},
 {q__,'q'},
 {r__,'r'},
 {s__,'s'},
 {t__,'t'},
 {u__,'u'},
 {v__,'v'},
 {w__,'w'},
 {x__,'x'},
 {y__,'y'},
 {z__,'z'},
 {cursor_,'>'},
 {colon_,':'},
};
/**
 *	@brief	引き渡されたコードが有効なASCIIマルチバイトコードかどうかを返す
 */
static BOOL isMulti(u16* code)
{
	u8*	byte = (u8*)code;

	if(	(byte[0] < 0x81) ||
		(byte[0] > 0x9F && 0xE0 > byte[0]) ||
		(byte[0] > 0xFC)){
		return FALSE;
	}

	if(	(byte[1] < 0x40) ||
		(byte[1] > 0x7E && 0x80 > byte[1]) ||
		(byte[1] > 0xFC)){
		return FALSE;
	}
	return TRUE;
}
//---------------------------------------------------------------------------------------------
/*
 *	文字コード変換　ASCII->ポケモンＤＰ
 *	※通常文字、終了、改行対応
 *	　トリガー待ち、バッファメッセージ、ポケモン特殊コード非対応
 *
 *	デバッグ専用です！
 *
 * @param	c_id		国番号(0:日本,1:....)
 * @param	agb_str		入力するASCII文字列のポインタ
 * @param	ds_str		出力するDS文字列のポインタ
 *
 * @retval	ret		0:問題なし,1:解釈不可能なコードがあった（変換失敗）
 */
//---------------------------------------------------------------------------------------------
u8	ASCIIcode2DSuni(u8 c_id, u8 *ascii_str, u16 *ds_str)
{
	u8 i,j,chk;
	u16	*wide;

	//現在資料がないため、日本語のみ対応
	if(c_id!=0) return 1;
	for(i=0;i < 255;i++){
		if(*ascii_str == 0x00){	//終了
			*ds_str = EOM_;
			return 0;
		}
		//改行取得
		if(*ascii_str == 0x0D && *(ascii_str+1) == 0x0A){
			*ds_str = CR_;
			ascii_str += 2;
			continue;
		}else if(*ascii_str == 0x0A){
			*ds_str = CR_;
			++ascii_str;
			continue;
		}
		//1or2byteコード
		chk = 0;
		if(isMulti((u16*)ascii_str)){
			wide = (u16*)ascii_str;
			for(j=0;j<TRANS_DS2A2B_CODE_MAX;j++){
				if(*wide == ds_to_ascii2_trans[j].ascii_code) {
					*ds_str = ds_to_ascii2_trans[j].ds_code;
					chk=1;
					break;
				}
			}
		}else{
			for(j=0;j<TRANS_DS2A1B_CODE_MAX;j++){
				if(*ascii_str == ds_to_ascii1_trans[j].ascii_code) {
					*ds_str = ds_to_ascii1_trans[j].ds_code;
					chk=1;
					break;
				}
			}
		}
		//該当コードがなかったときエラー
		if(chk==0){
			return 1;
		}
		ascii_str++;
		ds_str++;
	}

	//EOM_が検出できないor文章が255文字以上のときはエラー
	return 1;
}

#endif	//PM_DEBUG

////////////////////////////////////////////////////////////////////////////
