#include "common.h"
//------------------------------------------------------------------
/**
 * @brief	モンスター番号の変換
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
typedef struct {
  u16 old, new;
} POKEMON_CHANGE_TABLE;

POKEMON_CHANGE_TABLE PokemonOld2NewTable[] = {
  { 277, 252 },				/* キモリ */
  { 278, 253 },				/* ジュプトル */
  { 279, 254 },				/* ジュカイン */
  { 280, 255 },				/* アチャモ */
  { 281, 256 },				/* ワカシャモ */
  { 282, 257 },				/* バシャーモ */
  { 283, 258 },				/* ミズゴロウ */
  { 284, 259 },				/* ヌマクロー */
  { 285, 260 },				/* ラグラージ */
  { 286, 261 },				/* ポチエナ */
  { 287, 262 },				/* グラエナ */
  { 288, 263 },				/* ジグザグマ */
  { 289, 264 },				/* マッスグマ */
  { 290, 265 },				/* ケムッソ */
  { 291, 266 },				/* カラサリス */
  { 292, 267 },				/* アゲハント */
  { 293, 268 },				/* マユルド */
  { 294, 269 },				/* ドクケイル */
  { 295, 270 },				/* ハスボー */
  { 296, 271 },				/* ハスブレロ */
  { 297, 272 },				/* ルンパッパ */
  { 298, 273 },				/* タネボー */
  { 299, 274 },				/* コノハナ */
  { 300, 275 },				/* ダーテング */
  { 301, 290 },				/* ツチニン */
  { 302, 291 },				/* テッカニン */
  { 303, 292 },				/* ヌケニン */
  { 304, 276 },				/* スバメ */
  { 305, 277 },				/* オオスバメ */
  { 306, 285 },				/* キノココ */
  { 307, 286 },				/* キノガッサ */
  { 308, 327 },				/* パッチール */
  { 309, 278 },				/* キャモメ */
  { 310, 279 },				/* ペリッパー */
  { 311, 283 },				/* アメタマ */
  { 312, 284 },				/* アメモース */
  { 313, 320 },				/* ホエルコ */
  { 314, 321 },				/* ホエルオー */
  { 315, 300 },				/* エネコ */
  { 316, 301 },				/* エネコロロ */
  { 317, 352 },				/* カクレオン */
  { 318, 343 },				/* ヤジロン */
  { 319, 344 },				/* ネンドール */
  { 320, 299 },				/* ノズパス */
  { 321, 324 },				/* コータス */
  { 322, 302 },				/* ヤミラミ */
  { 323, 339 },				/* ドジョッチ */
  { 324, 340 },				/* ナマズン */
  { 325, 370 },				/* ラブカス */
  { 326, 341 },				/* ヘイガニ */
  { 327, 342 },				/* シザリガー */
  { 328, 349 },				/* ヒンバス */
  { 329, 350 },				/* ミロカロス */
  { 330, 318 },				/* キバニア */
  { 331, 319 },				/* サメハダー */
  { 332, 328 },				/* ナックラー */
  { 333, 329 },				/* ビブラーバ */
  { 334, 330 },				/* フライゴン */
  { 335, 296 },				/* マクノシタ */
  { 336, 297 },				/* ハリテヤマ */
  { 337, 309 },				/* ラクライ */
  { 338, 310 },				/* ライボルト */
  { 339, 322 },				/* ドンメル */
  { 340, 323 },				/* バクーダ */
  { 341, 363 },				/* タマザラシ */
  { 342, 364 },				/* トドグラー */
  { 343, 365 },				/* トドゼルガ */
  { 344, 331 },				/* サボネア */
  { 345, 332 },				/* ノクタス */
  { 346, 361 },				/* ユキワラシ */
  { 347, 362 },				/* オニゴーリ */
  { 348, 337 },				/* ルナトーン */
  { 349, 338 },				/* ソルロック */
  { 350, 298 },				/* ルリリ */
  { 351, 325 },				/* バネブー */
  { 352, 326 },				/* ブーピッグ */
  { 353, 311 },				/* プラスル */
  { 354, 312 },				/* マイナン */
  { 355, 303 },				/* クチート */
  { 356, 307 },				/* アサナン */
  { 357, 308 },				/* チャーレム */
  { 358, 333 },				/* チルット */
  { 359, 334 },				/* チルタリス */
  { 360, 360 },				/* ソーナノ */
  { 361, 355 },				/* ヨマワル */
  { 362, 356 },				/* サマヨール */
  { 363, 315 },				/* ロゼリア */
  { 364, 287 },				/* ナマケロ */
  { 365, 288 },				/* ヤルキモノ */
  { 366, 289 },				/* ケッキング */
  { 367, 316 },				/* ゴクリン */
  { 368, 317 },				/* マルノーム */
  { 369, 357 },				/* トロピウス */
  { 370, 293 },				/* ゴニョニョ */
  { 371, 294 },				/* ドゴーム */
  { 372, 295 },				/* バクオング */
  { 373, 366 },				/* パールル */
  { 374, 367 },				/* ハンテール */
  { 375, 368 },				/* サクラビス */
  { 376, 359 },				/* アブソル */
  { 377, 353 },				/* カゲボウズ */
  { 378, 354 },				/* ジュペッタ */
  { 379, 336 },				/* ハブネーク */
  { 380, 335 },				/* ザングース */
  { 381, 369 },				/* ジーランス */
  { 382, 304 },				/* ココドラ */
  { 383, 305 },				/* コドラ */
  { 384, 306 },				/* ボスゴドラ */
  { 385, 351 },				/* ポワルン */
  { 386, 313 },				/* バルビート */
  { 387, 314 },				/* イルミーゼ */
  { 388, 345 },				/* リリーラ */
  { 389, 346 },				/* ユレイドル */
  { 390, 347 },				/* アノプス */
  { 391, 348 },				/* アーマルド */
  { 392, 280 },				/* ラルトス */
  { 393, 281 },				/* キルリア */
  { 394, 282 },				/* サーナイト */
  { 395, 371 },				/* タツベイ */
  { 396, 372 },				/* コモルー */
  { 397, 373 },				/* ボーマンダ */
  { 398, 374 },				/* ダンバル */
  { 399, 375 },				/* メタング */
  { 400, 376 },				/* メタグロス */
  { 401, 377 },				/* レジロック */
  { 402, 378 },				/* レジアイス */
  { 403, 379 },				/* レジスチル */
  { 404, 382 },				/* カイオーガ */
  { 405, 383 },				/* グラードン */
  { 406, 384 },				/* レックウザ */
  { 407, 380 },				/* ラティアス */
  { 408, 381 },				/* ラティオス */
  { 409, 385 },				/* ジラーチ */
  { 410, 386 },				/* デオキシス */
  { 411, 358 },				/* チリーン */
  { 412, 412 },				/* ゴンベ */
  { 413, 413 },				/* ウソハチ */
  { 414, 414 },				/* マネネ */
  { 415, 415 },				/* マニューラ */
  { 416, 416 },				/* ルカリオ */
  { 417, 417 },				/* マンタイン前 */
  { 418, 418 },				/* バレッタス */
  { 419, 419 },				/* オウム */
  { 420, 420 },				/* ミミット */
};


#if 0
// system/agb_str.c に格納されました

//------------------------------------------------------------------
/**
 * @brief	メッセージコードの変換
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
#include <gflib/fntequ_agb_jp.h>
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
 {JP_AGB_nakag_,nakag_},	// #####
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
int GBAcode2DSuni(int c_id, u8 *agb_str, u16 *ds_str)
{
  int i,j,chk;

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
#endif

/*  */
