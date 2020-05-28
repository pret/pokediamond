#include "common.h"
//------------------------------------------------------------------
/**
 * @brief	�����X�^�[�ԍ��̕ϊ�
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
typedef struct {
  u16 old, new;
} POKEMON_CHANGE_TABLE;

POKEMON_CHANGE_TABLE PokemonOld2NewTable[] = {
  { 277, 252 },				/* �L���� */
  { 278, 253 },				/* �W���v�g�� */
  { 279, 254 },				/* �W���J�C�� */
  { 280, 255 },				/* �A�`���� */
  { 281, 256 },				/* ���J�V���� */
  { 282, 257 },				/* �o�V���[�� */
  { 283, 258 },				/* �~�Y�S���E */
  { 284, 259 },				/* �k�}�N���[ */
  { 285, 260 },				/* ���O���[�W */
  { 286, 261 },				/* �|�`�G�i */
  { 287, 262 },				/* �O���G�i */
  { 288, 263 },				/* �W�O�U�O�} */
  { 289, 264 },				/* �}�b�X�O�} */
  { 290, 265 },				/* �P���b�\ */
  { 291, 266 },				/* �J���T���X */
  { 292, 267 },				/* �A�Q�n���g */
  { 293, 268 },				/* �}�����h */
  { 294, 269 },				/* �h�N�P�C�� */
  { 295, 270 },				/* �n�X�{�[ */
  { 296, 271 },				/* �n�X�u���� */
  { 297, 272 },				/* �����p�b�p */
  { 298, 273 },				/* �^�l�{�[ */
  { 299, 274 },				/* �R�m�n�i */
  { 300, 275 },				/* �_�[�e���O */
  { 301, 290 },				/* �c�`�j�� */
  { 302, 291 },				/* �e�b�J�j�� */
  { 303, 292 },				/* �k�P�j�� */
  { 304, 276 },				/* �X�o�� */
  { 305, 277 },				/* �I�I�X�o�� */
  { 306, 285 },				/* �L�m�R�R */
  { 307, 286 },				/* �L�m�K�b�T */
  { 308, 327 },				/* �p�b�`�[�� */
  { 309, 278 },				/* �L������ */
  { 310, 279 },				/* �y���b�p�[ */
  { 311, 283 },				/* �A���^�} */
  { 312, 284 },				/* �A�����[�X */
  { 313, 320 },				/* �z�G���R */
  { 314, 321 },				/* �z�G���I�[ */
  { 315, 300 },				/* �G�l�R */
  { 316, 301 },				/* �G�l�R���� */
  { 317, 352 },				/* �J�N���I�� */
  { 318, 343 },				/* ���W���� */
  { 319, 344 },				/* �l���h�[�� */
  { 320, 299 },				/* �m�Y�p�X */
  { 321, 324 },				/* �R�[�^�X */
  { 322, 302 },				/* ���~���~ */
  { 323, 339 },				/* �h�W���b�` */
  { 324, 340 },				/* �i�}�Y�� */
  { 325, 370 },				/* ���u�J�X */
  { 326, 341 },				/* �w�C�K�j */
  { 327, 342 },				/* �V�U���K�[ */
  { 328, 349 },				/* �q���o�X */
  { 329, 350 },				/* �~���J���X */
  { 330, 318 },				/* �L�o�j�A */
  { 331, 319 },				/* �T���n�_�[ */
  { 332, 328 },				/* �i�b�N���[ */
  { 333, 329 },				/* �r�u���[�o */
  { 334, 330 },				/* �t���C�S�� */
  { 335, 296 },				/* �}�N�m�V�^ */
  { 336, 297 },				/* �n���e���} */
  { 337, 309 },				/* ���N���C */
  { 338, 310 },				/* ���C�{���g */
  { 339, 322 },				/* �h������ */
  { 340, 323 },				/* �o�N�[�_ */
  { 341, 363 },				/* �^�}�U���V */
  { 342, 364 },				/* �g�h�O���[ */
  { 343, 365 },				/* �g�h�[���K */
  { 344, 331 },				/* �T�{�l�A */
  { 345, 332 },				/* �m�N�^�X */
  { 346, 361 },				/* ���L�����V */
  { 347, 362 },				/* �I�j�S�[�� */
  { 348, 337 },				/* ���i�g�[�� */
  { 349, 338 },				/* �\�����b�N */
  { 350, 298 },				/* ������ */
  { 351, 325 },				/* �o�l�u�[ */
  { 352, 326 },				/* �u�[�s�b�O */
  { 353, 311 },				/* �v���X�� */
  { 354, 312 },				/* �}�C�i�� */
  { 355, 303 },				/* �N�`�[�g */
  { 356, 307 },				/* �A�T�i�� */
  { 357, 308 },				/* �`���[���� */
  { 358, 333 },				/* �`���b�g */
  { 359, 334 },				/* �`���^���X */
  { 360, 360 },				/* �\�[�i�m */
  { 361, 355 },				/* ���}���� */
  { 362, 356 },				/* �T�}���[�� */
  { 363, 315 },				/* ���[���A */
  { 364, 287 },				/* �i�}�P�� */
  { 365, 288 },				/* �����L���m */
  { 366, 289 },				/* �P�b�L���O */
  { 367, 316 },				/* �S�N���� */
  { 368, 317 },				/* �}���m�[�� */
  { 369, 357 },				/* �g���s�E�X */
  { 370, 293 },				/* �S�j���j�� */
  { 371, 294 },				/* �h�S�[�� */
  { 372, 295 },				/* �o�N�I���O */
  { 373, 366 },				/* �p�[���� */
  { 374, 367 },				/* �n���e�[�� */
  { 375, 368 },				/* �T�N���r�X */
  { 376, 359 },				/* �A�u�\�� */
  { 377, 353 },				/* �J�Q�{�E�Y */
  { 378, 354 },				/* �W���y�b�^ */
  { 379, 336 },				/* �n�u�l�[�N */
  { 380, 335 },				/* �U���O�[�X */
  { 381, 369 },				/* �W�[�����X */
  { 382, 304 },				/* �R�R�h�� */
  { 383, 305 },				/* �R�h�� */
  { 384, 306 },				/* �{�X�S�h�� */
  { 385, 351 },				/* �|������ */
  { 386, 313 },				/* �o���r�[�g */
  { 387, 314 },				/* �C���~�[�[ */
  { 388, 345 },				/* �����[�� */
  { 389, 346 },				/* �����C�h�� */
  { 390, 347 },				/* �A�m�v�X */
  { 391, 348 },				/* �A�[�}���h */
  { 392, 280 },				/* �����g�X */
  { 393, 281 },				/* �L�����A */
  { 394, 282 },				/* �T�[�i�C�g */
  { 395, 371 },				/* �^�c�x�C */
  { 396, 372 },				/* �R�����[ */
  { 397, 373 },				/* �{�[�}���_ */
  { 398, 374 },				/* �_���o�� */
  { 399, 375 },				/* ���^���O */
  { 400, 376 },				/* ���^�O���X */
  { 401, 377 },				/* ���W���b�N */
  { 402, 378 },				/* ���W�A�C�X */
  { 403, 379 },				/* ���W�X�`�� */
  { 404, 382 },				/* �J�C�I�[�K */
  { 405, 383 },				/* �O���[�h�� */
  { 406, 384 },				/* ���b�N�E�U */
  { 407, 380 },				/* ���e�B�A�X */
  { 408, 381 },				/* ���e�B�I�X */
  { 409, 385 },				/* �W���[�` */
  { 410, 386 },				/* �f�I�L�V�X */
  { 411, 358 },				/* �`���[�� */
  { 412, 412 },				/* �S���x */
  { 413, 413 },				/* �E�\�n�` */
  { 414, 414 },				/* �}�l�l */
  { 415, 415 },				/* �}�j���[�� */
  { 416, 416 },				/* ���J���I */
  { 417, 417 },				/* �}���^�C���O */
  { 418, 418 },				/* �o���b�^�X */
  { 419, 419 },				/* �I�E�� */
  { 420, 420 },				/* �~�~�b�g */
};


#if 0
// system/agb_str.c �Ɋi�[����܂���

//------------------------------------------------------------------
/**
 * @brief	���b�Z�[�W�R�[�h�̕ϊ�
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
 *	�����R�[�h�ϊ��@�|�P�����`�f�a->�|�P�����c�r
 *	���ʏ핶���A�I���A���s�A�g���K�[�҂��A�o�b�t�@���b�Z�[�W�ɑΉ�
 *
 * @param	c_id		���ԍ�(0:���{,1:....)
 * @param	agb_str		���͂���`�f�a������̃|�C���^
 * @param	ds_str		�o�͂���c�r������̃|�C���^
 *
 * @retval	ret		0:���Ȃ�,1:���ߕs�\�ȃR�[�h���������i�ϊ����s�j
 */
//---------------------------------------------------------------------------------------------
int GBAcode2DSuni(int c_id, u8 *agb_str, u16 *ds_str)
{
  int i,j,chk;

  //���ݎ������Ȃ����߁A���{��̂ݑΉ�
  if(c_id!=0) return 1;

  for(i=0;i < 255;i++){
    if(*agb_str <= 0xf6){	//�ʏ핶��
      chk=0;
      for(j=0;j<TRANS_NORMAL_CODE_MAX;j++){
	if(*agb_str == ds_agb_normal_trans[j].agb_code) {
	  *ds_str = ds_agb_normal_trans[j].ds_code;
	  chk=1;
	  break;
	}
      }

      //�Y���R�[�h���Ȃ������Ƃ��G���[
      if(chk==0) return 1;
    }else{					//���䕶��
      switch(*agb_str){
      case JP_AGB_EOM_:		//�I���R�[�h
	*ds_str = EOM_;
	return 0;
      case JP_AGB_CR_:		//���s�R�[�h
	*ds_str = CR_;
	break;
      case JP_AGB_NORMAL_WAIT_:		//"��"		�g���K�[�҂���MSG�G���A�N���A
	*ds_str = NORMAL_WAIT_;
	break;
      case JP_AGB_SCROLL_WAIT_:		//"��"		�g���K�[�҂�����s�X�N���[�� 
	*ds_str = SCROLL_WAIT_;
	break;
      case JP_AGB_I_MSG_:		//�w��o�b�t�@�̃��b�Z�[�W�W�J(ID)
	*ds_str++ = I_MSG_;
	*ds_str = (u16)(*(++agb_str));
	break;
      case JP_AGB_S_MSG_:		//�w��o�b�t�@�̃��b�Z�[�W�W�J(�C��)
	*ds_str++ = S_MSG_;
	*ds_str = (u16)(*(++agb_str));
	break;
      case JP_AGB_EXFONT1_:	//�g���t�H���g(fontnum = 0x100�`0x1ff)
	++agb_str;
	chk=0;
	for(j=0;j<TRANS_ETC_CODE_MAX;j++){
	  if(*agb_str == ds_agb_etc_trans[j].agb_code) {
	    *ds_str = ds_agb_etc_trans[j].ds_code;
	    chk=1;
	    break;
	  }
	}

	//�Y���R�[�h���Ȃ������Ƃ��G���[
	if(chk==0) return 1;
	break;
      case JP_AGB_EXICON_:	// �g���A�C�R��(�L�[�A�C�R��)
				//�����݃L�[�A�C�R���Ȃ�
	break;
      case JP_AGB_CTRL_:		// �t�H���g����R�}���h
	//������n���Ⴄ�̂Ŗ��Ή�
	break;
      }
    }
    agb_str++;
    ds_str++;
  }

  //EOM_�����o�ł��Ȃ�or���͂�255�����ȏ�̂Ƃ��̓G���[
  return 1;
}
#endif

/*  */
