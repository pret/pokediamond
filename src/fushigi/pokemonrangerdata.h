//#include <nitro/types.h>
#include "gflib/strcode.h"		// fntequ

#define	ranger_EOM_		 0
#define	ranger_gyoe_		33
#define	ranger_Twquo_		34
#define	ranger_Tsharp_		35
#define	ranger_Tdoll_		36
#define	ranger_Tper_		37
#define	ranger_Tapos_		38
#define	ranger_Tkako3_		39
#define	ranger_Tkakot3_		40
#define	ranger_Taster_		41
#define	ranger_Tplus_		42
#define	ranger_Tcomma_		43
#define	ranger_bou_		44
#define	ranger_ten_		45
#define	ranger_sura_		46
#define	ranger_n0_		48
#define	ranger_n1_		49
#define	ranger_n2_		50
#define	ranger_n3_		51
#define	ranger_n4_		52
#define	ranger_n5_		53
#define	ranger_n6_		54
#define	ranger_n7_		55
#define	ranger_n8_		56
#define	ranger_n9_		57
#define	ranger_Tcolon_		58
#define	ranger_Tscolon_		59
#define	ranger_Tkako4_		60
#define	ranger_Tequ_		61
#define	ranger_Tkakot4_		62
#define	ranger_hate_		63
#define	ranger_Tat_		64
#define	ranger_A__		65
#define	ranger_B__		66
#define	ranger_C__		67
#define	ranger_D__		68
#define	ranger_E__		69
#define	ranger_F__		70
#define	ranger_G__		71
#define	ranger_H__		72
#define	ranger_I__		73
#define	ranger_J__		74
#define	ranger_K__		75
#define	ranger_L__		76
#define	ranger_M__		77
#define	ranger_N__		78
#define	ranger_O__		79
#define	ranger_P__		80
#define	ranger_Q__		81
#define	ranger_R__		82
#define	ranger_S__		83
#define	ranger_T__		84
#define	ranger_U__		85
#define	ranger_V__		86
#define	ranger_W__		87
#define	ranger_X__		88
#define	ranger_Y__		89
#define	ranger_Z__		90
#define	ranger_Tkako5_		91
#define	ranger_Tyen2_		92
#define	ranger_Tkako5t_		93
#define	ranger_Tjyo_		94
#define	ranger_Tuber_		95
#define	ranger_Tapor_		96
#define	ranger_a__		97
#define	ranger_b__		98
#define	ranger_c__		99
#define	ranger_d__		100
#define	ranger_e__		101
#define	ranger_f__		102
#define	ranger_g__		103
#define	ranger_h__		104
#define	ranger_i__		105
#define	ranger_j__		106
#define	ranger_k__		107
#define	ranger_l__		108
#define	ranger_m__		109
#define	ranger_n__		110
#define	ranger_o__		111
#define	ranger_p__		112
#define	ranger_q__		113
#define	ranger_r__		114
#define	ranger_s__		115
#define	ranger_t__		116
#define	ranger_u__		117
#define	ranger_v__		118
#define	ranger_w__		119
#define	ranger_x__		120
#define	ranger_y__		121
#define	ranger_z__		122
#define	ranger_Tkako6_		123
#define	ranger_Ttate_		124
#define	ranger_Tkako6t_		125
#define	ranger_Tcill_		126
#define	ranger_aa_		129
#define	ranger_a_		130
#define	ranger_ii_		131
#define	ranger_i_		132
#define	ranger_uu_		133
#define	ranger_u_		134
#define	ranger_ee_		135
#define	ranger_e_		136
#define	ranger_oo_		137
#define	ranger_o_		138
#define	ranger_ka_		139
#define	ranger_ga_		140
#define	ranger_ki_		141
#define	ranger_gi_		142
#define	ranger_ku_		143
#define	ranger_gu_		144
#define	ranger_ke_		145
#define	ranger_ge_		146
#define	ranger_ko_		147
#define	ranger_go_		148
#define	ranger_sa_		149
#define	ranger_za_		150
#define	ranger_si_		151
#define	ranger_zi_		152
#define	ranger_su_		153
#define	ranger_zu_		154
#define	ranger_se_		155
#define	ranger_ze_		156
#define	ranger_so_		157
#define	ranger_zo_		158
#define	ranger_ta_		159
#define	ranger_da_		160
#define	ranger_ti_		161
#define	ranger_di_		162
#define	ranger_ttu_		163
#define	ranger_tu_		164
#define	ranger_du_		165
#define	ranger_te_		166
#define	ranger_de_		167
#define	ranger_to_		168
#define	ranger_do_		169
#define	ranger_na_		170
#define	ranger_ni_		171
#define	ranger_nu_		172
#define	ranger_ne_		173
#define	ranger_no_		174
#define	ranger_ha_		175
#define	ranger_ba_		176
#define	ranger_pa_		177
#define	ranger_hi_		178
#define	ranger_bi_		179
#define	ranger_pi_		180
#define	ranger_fu_		181
#define	ranger_bu_		182
#define	ranger_pu_		183
#define	ranger_he_		184
#define	ranger_be_		185
#define	ranger_pe_		186
#define	ranger_ho_		187
#define	ranger_bo_		188
#define	ranger_po_		189
#define	ranger_ma_		190
#define	ranger_mi_		191
#define	ranger_mu_		192
#define	ranger_me_		193
#define	ranger_mo_		194
#define	ranger_yya_		195
#define	ranger_ya_		196
#define	ranger_yyu_		197
#define	ranger_yu_		198
#define	ranger_yyo_		199
#define	ranger_yo_		200
#define	ranger_ra_		201
#define	ranger_ri_		202
#define	ranger_ru_		203
#define	ranger_re_		204
#define	ranger_ro_		205
#define	ranger_Twwa_		206
#define	ranger_wa_		207
#define	ranger_Tiii_		208
#define	ranger_Teee_		209
#define	ranger_wo_		210
#define	ranger_n_		211
#define	ranger_AA_		225
#define	ranger_A_		226
#define	ranger_II_		227
#define	ranger_I_		228
#define	ranger_UU_		229
#define	ranger_U_		230
#define	ranger_EE_		231
#define	ranger_E_		232
#define	ranger_OO_		233
#define	ranger_O_		234
#define	ranger_KA_		235
#define	ranger_GA_		236
#define	ranger_KI_		237
#define	ranger_GI_		238
#define	ranger_KU_		239
#define	ranger_GU_		240
#define	ranger_KE_		241
#define	ranger_GE_		242
#define	ranger_KO_		243
#define	ranger_GO_		244
#define	ranger_SA_		245
#define	ranger_ZA_		246
#define	ranger_SI_		247
#define	ranger_ZI_		248
#define	ranger_SU_		249
#define	ranger_ZU_		250
#define	ranger_SE_		251
#define	ranger_ZE_		252
#define	ranger_SO_		253
#define	ranger_ZO_		254
#define	ranger_TA_		255
#define	ranger_DA_		256
#define	ranger_TI_		257
#define	ranger_DI_		258
#define	ranger_TTU_		259
#define	ranger_TU_		260
#define	ranger_DU_		261
#define	ranger_TE_		262
#define	ranger_DE_		263
#define	ranger_TO_		264
#define	ranger_DO_		265
#define	ranger_NA_		266
#define	ranger_NI_		267
#define	ranger_NU_		268
#define	ranger_NE_		269
#define	ranger_NO_		270
#define	ranger_HA_		271
#define	ranger_BA_		272
#define	ranger_PA_		273
#define	ranger_HI_		274
#define	ranger_BI_		275
#define	ranger_PI_		276
#define	ranger_FU_		277
#define	ranger_BU_		278
#define	ranger_PU_		279
#define	ranger_HE_		280
#define	ranger_BE_		281
#define	ranger_PE_		282
#define	ranger_HO_		283
#define	ranger_BO_		284
#define	ranger_PO_		285
#define	ranger_MA_		286
#define	ranger_MI_		287
#define	ranger_MU_		288
#define	ranger_ME_		289
#define	ranger_MO_		290
#define	ranger_YYA_		291
#define	ranger_YA_		292
#define	ranger_YYU_		293
#define	ranger_YU_		294
#define	ranger_YYO_		295
#define	ranger_YO_		296
#define	ranger_RA_		297
#define	ranger_RI_		298
#define	ranger_RU_		299
#define	ranger_RE_		300
#define	ranger_RO_		301
#define	ranger_WWA_		302
#define	ranger_WA_		303
#define	ranger_III_		304
#define	ranger_EEE_		305
#define	ranger_WO_		306
#define	ranger_N_		307
#define	ranger_tVU_		308
#define	ranger_tKKA_		309
#define	ranger_tKKE_		310
#define	ranger_kako2_		320
#define	ranger_kakot2_		321
#define	ranger_kako_		322
#define	ranger_kakot_		323
#define	ranger_Tdaku_		324
#define	ranger_Thatu_		325
#define	ranger_nakag_		326
#define	ranger_tenten_		327
#define	ranger_osu_		328
#define	ranger_mesu_		329
#define	ranger_kten_		330
#define	ranger_yen_		331
#define	ranger_Tbou2_		332
#define ranger_ArrowU__		333
#define ranger_ArrowR__		334
#define ranger_ArrowD__		335
#define ranger_ArrowL__		336
#define ranger_Tand_		337

// eurofont start = 352(spc)	// 0x00
#define ranger_iexcl_		353	// 0x01
//#define xxxxx_	354	// 0x02
//#define xxxxx_	355	// 0x03
//#define xxxxx_	356	// 0x04
//#define xxxxx_	357	// 0x05
//#define xxxxx_	358	// 0x06
//#define xxxxx_	359	// 0x07
//#define xxxxx_	360	// 0x08
//#define xxxxx_	361	// 0x09
#define ranger_ordf_		362	// 0x0A
#define ranger_less__		363	// 0x0B
//#define xxxxx_	364	// 0x0C
//#define xxxxx_	365	// 0x0D
//#define xxxxx_	366	// 0x0E
//#define xxxxx_	367	// 0x0F

//#define xxxxx		368	// 0x10
//#define xxxxx		369	// 0x11
//#define xxxxx		370	// 0x12
//#define xxxxx		371	// 0x13
//#define xxxxx		372	// 0x14
//#define xxxxx		373	// 0x15
//#define xxxxx		374	// 0x16
//#define xxxxx		375	// 0x17
//#define xxxxx		376	// 0x18
//#define xxxxx		377	// 0x19
#define ranger_ordm_		378	// 0x1A
#define ranger_greater_	379	// 0x1B
#define ranger_OElig_		380	// 0x1C
#define ranger_oelig_		381	// 0x1D
//#define xxxxx		382	// 0x1E
#define ranger_iquest_		383	// 0x1F

#define ranger_Agrave_		384	// 0x20
#define ranger_Aacute_		385
#define ranger_Acirc_		386
//#define xxxxx_	387
#define ranger_Auml_		388
//#define xxxxx_	389
//#define xxxxx_	390
#define ranger_Ccedil_		391
#define ranger_Egave_		392
#define ranger_Eacute_		393
#define ranger_Ecirc_		394
#define ranger_Euml_		395
#define ranger_Igrave_		396
#define ranger_Iacute_		397
#define ranger_Icirc_		398
#define ranger_Iuml_		399

//#define xxxx		400	// 0x30
#define ranger_Ntilda_		401
#define ranger_Ogave_		402
#define ranger_Oacute_		403
#define ranger_Ocirc_		404
//#define xxxx		405
#define ranger_Ouml_		406
//#define xxxx_		407
//#define xxxx_		408
#define ranger_Ugave_		409
#define ranger_Uacute_		410
#define ranger_Ucirc_		411
#define ranger_Uuml_		412
//#define xxxx_		413
//#define xxxx_		414
#define ranger_szlig_		415

#define ranger_agrave_		416	// 0x40
#define ranger_aacute_		417
#define ranger_acirc_		418
//#define xxxxx_	419
#define ranger_auml_		420
//#define xxxxx_	421
//#define xxxxx_	422
#define ranger_ccedil_		423
#define ranger_egave_		424
#define ranger_eacute_		425
#define ranger_ecirc_		426
#define ranger_euml_		427
#define ranger_igrave_		428
#define ranger_iacute_		429
#define ranger_icirc_		430
#define ranger_iuml_		431

//#define xxxx		432	// 0x50
#define ranger_ntilda_		433
#define ranger_ogave_		434
#define ranger_oacute_		435
#define ranger_ocirc_		436
//#define xxxx		437
#define ranger_ouml_		438
//#define xxxx_		439
//#define xxxx_		440
#define ranger_ugave_		441
#define ranger_uacute_		442
#define ranger_ucirc_		443
#define ranger_uuml_		444
//#define xxxx_		445
//#define xxxx_		446
//#define xxxx_		447

typedef struct {
  u16 ranger;
  u16 dp;
} STRCODETABLE;

STRCODETABLE Ranger2DpTable[] = {
  { ranger_EOM_,	EOM_ },
  { ranger_gyoe_,	gyoe_ },
  //  { ranger_Twquo_,	Twquo_ },
  { ranger_Tsharp_,	h_sharp_ },
  //  { ranger_Tdoll_,	Tdoll_ },
  { ranger_Tper_,	h_percent_ },
  //  { ranger_Tapos_,	Tapos_ },
  { ranger_Tkako3_,	kako2_ },
  { ranger_Tkakot3_,	kakot2_ },
  { ranger_Taster_,	h_asterisk_ },
  { ranger_Tplus_,	h_plus_ },
  { ranger_Tcomma_,	h_comma_ },
  { ranger_bou_,	h_bou_ },
  //  { ranger_ten_,	h_ten_ },
  { ranger_sura_,	h_sura_ },
  { ranger_n0_,	n0_ },
  { ranger_n1_,	n1_ },
  { ranger_n2_,	n2_ },
  { ranger_n3_,	n3_ },
  { ranger_n4_,	n4_ },
  { ranger_n5_,	n5_ },
  { ranger_n6_,	n6_ },
  { ranger_n7_,	n7_ },
  { ranger_n8_,	n8_ },
  { ranger_n9_,	n9_ },
  { ranger_Tcolon_,	h_colon_ },
  { ranger_Tscolon_,	h_semicolon_ },
  { ranger_Tkako4_,	MaruKako__ },
  //  { ranger_Tequ_,	Tequ_ },
  { ranger_Tkakot4_,	MaruKakot__ },
  { ranger_hate_,	h_hate_ },
  //  { ranger_Tat_,	Tat_ },
  { ranger_A__,	A__ },
  { ranger_B__,	B__ },
  { ranger_C__,	C__ },
  { ranger_D__,	D__ },
  { ranger_E__,	E__ },
  { ranger_F__,	F__ },
  { ranger_G__,	G__ },
  { ranger_H__,	H__ },
  { ranger_I__,	I__ },
  { ranger_J__,	J__ },
  { ranger_K__,	K__ },
  { ranger_L__,	L__ },
  { ranger_M__,	M__ },
  { ranger_N__,	N__ },
  { ranger_O__,	O__ },
  { ranger_P__,	P__ },
  { ranger_Q__,	Q__ },
  { ranger_R__,	R__ },
  { ranger_S__,	S__ },
  { ranger_T__,	T__ },
  { ranger_U__,	U__ },
  { ranger_V__,	V__ },
  { ranger_W__,	W__ },
  { ranger_X__,	X__ },
  { ranger_Y__,	Y__ },
  { ranger_Z__,	Z__ },
  //  { ranger_Tkako5_,	Tkako5_ },
  //  { ranger_Tyen2_,	Tyen2_ },
  //  { ranger_Tkako5t_,	Tkako5t_ },
  //  { ranger_Tjyo_,	Tjyo_ },
  //  { ranger_Tuber_,	Tuber_ },
  //  { ranger_Tapor_,	Tapor_ },
  { ranger_a__,	a__ },
  { ranger_b__,	b__ },
  { ranger_c__,	c__ },
  { ranger_d__,	d__ },
  { ranger_e__,	e__ },
  { ranger_f__,	f__ },
  { ranger_g__,	g__ },
  { ranger_h__,	h__ },
  { ranger_i__,	i__ },
  { ranger_j__,	j__ },
  { ranger_k__,	k__ },
  { ranger_l__,	l__ },
  { ranger_m__,	m__ },
  { ranger_n__,	n__ },
  { ranger_o__,	o__ },
  { ranger_p__,	p__ },
  { ranger_q__,	q__ },
  { ranger_r__,	r__ },
  { ranger_s__,	s__ },
  { ranger_t__,	t__ },
  { ranger_u__,	u__ },
  { ranger_v__,	v__ },
  { ranger_w__,	w__ },
  { ranger_x__,	x__ },
  { ranger_y__,	y__ },
  { ranger_z__,	z__ },
  //  { ranger_Tkako6_,	Tkako6_ },
  //  { ranger_Ttate_,	Ttate_ },
  //  { ranger_Tkako6t_,	Tkako6t_ },
  //  { ranger_Tcill_,	Tcill_ },
  { ranger_aa_,	aa_ },
  { ranger_a_,	a_ },
  { ranger_ii_,	ii_ },
  { ranger_i_,	i_ },
  { ranger_uu_,	uu_ },
  { ranger_u_,	u_ },
  { ranger_ee_,	ee_ },
  { ranger_e_,	e_ },
  { ranger_oo_,	oo_ },
  { ranger_o_,	o_ },
  { ranger_ka_,	ka_ },
  { ranger_ga_,	ga_ },
  { ranger_ki_,	ki_ },
  { ranger_gi_,	gi_ },
  { ranger_ku_,	ku_ },
  { ranger_gu_,	gu_ },
  { ranger_ke_,	ke_ },
  { ranger_ge_,	ge_ },
  { ranger_ko_,	ko_ },
  { ranger_go_,	go_ },
  { ranger_sa_,	sa_ },
  { ranger_za_,	za_ },
  { ranger_si_,	si_ },
  { ranger_zi_,	zi_ },
  { ranger_su_,	su_ },
  { ranger_zu_,	zu_ },
  { ranger_se_,	se_ },
  { ranger_ze_,	ze_ },
  { ranger_so_,	so_ },
  { ranger_zo_,	zo_ },
  { ranger_ta_,	ta_ },
  { ranger_da_,	da_ },
  { ranger_ti_,	ti_ },
  { ranger_di_,	di_ },
  { ranger_ttu_,	ttu_ },
  { ranger_tu_,	tu_ },
  { ranger_du_,	du_ },
  { ranger_te_,	te_ },
  { ranger_de_,	de_ },
  { ranger_to_,	to_ },
  { ranger_do_,	do_ },
  { ranger_na_,	na_ },
  { ranger_ni_,	ni_ },
  { ranger_nu_,	nu_ },
  { ranger_ne_,	ne_ },
  { ranger_no_,	no_ },
  { ranger_ha_,	ha_ },
  { ranger_ba_,	ba_ },
  { ranger_pa_,	pa_ },
  { ranger_hi_,	hi_ },
  { ranger_bi_,	bi_ },
  { ranger_pi_,	pi_ },
  { ranger_fu_,	hu_ },
  { ranger_bu_,	bu_ },
  { ranger_pu_,	pu_ },
  { ranger_he_,	he_ },
  { ranger_be_,	be_ },
  { ranger_pe_,	pe_ },
  { ranger_ho_,	ho_ },
  { ranger_bo_,	bo_ },
  { ranger_po_,	po_ },
  { ranger_ma_,	ma_ },
  { ranger_mi_,	mi_ },
  { ranger_mu_,	mu_ },
  { ranger_me_,	me_ },
  { ranger_mo_,	mo_ },
  { ranger_yya_,	yya_ },
  { ranger_ya_,	ya_ },
  { ranger_yyu_,	yyu_ },
  { ranger_yu_,	yu_ },
  { ranger_yyo_,	yyo_ },
  { ranger_yo_,	yo_ },
  { ranger_ra_,	ra_ },
  { ranger_ri_,	ri_ },
  { ranger_ru_,	ru_ },
  { ranger_re_,	re_ },
  { ranger_ro_,	ro_ },
  //  { ranger_Twwa_,	Twwa_ },
  { ranger_wa_,	wa_ },
  //  { ranger_Tiii_,	Tiii_ },
  //  { ranger_Teee_,	Teee_ },
  { ranger_wo_,	wo_ },
  { ranger_n_,	n_ },
  { ranger_AA_,	AA_ },
  { ranger_A_,	A_ },
  { ranger_II_,	II_ },
  { ranger_I_,	I_ },
  { ranger_UU_,	UU_ },
  { ranger_U_,	U_ },
  { ranger_EE_,	EE_ },
  { ranger_E_,	E_ },
  { ranger_OO_,	OO_ },
  { ranger_O_,	O_ },
  { ranger_KA_,	KA_ },
  { ranger_GA_,	GA_ },
  { ranger_KI_,	KI_ },
  { ranger_GI_,	GI_ },
  { ranger_KU_,	KU_ },
  { ranger_GU_,	GU_ },
  { ranger_KE_,	KE_ },
  { ranger_GE_,	GE_ },
  { ranger_KO_,	KO_ },
  { ranger_GO_,	GO_ },
  { ranger_SA_,	SA_ },
  { ranger_ZA_,	ZA_ },
  { ranger_SI_,	SI_ },
  { ranger_ZI_,	ZI_ },
  { ranger_SU_,	SU_ },
  { ranger_ZU_,	ZU_ },
  { ranger_SE_,	SE_ },
  { ranger_ZE_,	ZE_ },
  { ranger_SO_,	SO_ },
  { ranger_ZO_,	ZO_ },
  { ranger_TA_,	TA_ },
  { ranger_DA_,	DA_ },
  { ranger_TI_,	TI_ },
  { ranger_DI_,	DI_ },
  { ranger_TTU_,	TTU_ },
  { ranger_TU_,	TU_ },
  { ranger_DU_,	DU_ },
  { ranger_TE_,	TE_ },
  { ranger_DE_,	DE_ },
  { ranger_TO_,	TO_ },
  { ranger_DO_,	DO_ },
  { ranger_NA_,	NA_ },
  { ranger_NI_,	NI_ },
  { ranger_NU_,	NU_ },
  { ranger_NE_,	NE_ },
  { ranger_NO_,	NO_ },
  { ranger_HA_,	HA_ },
  { ranger_BA_,	BA_ },
  { ranger_PA_,	PA_ },
  { ranger_HI_,	HI_ },
  { ranger_BI_,	BI_ },
  { ranger_PI_,	PI_ },
  { ranger_FU_,	HU_ },
  { ranger_BU_,	BU_ },
  { ranger_PU_,	PU_ },
  { ranger_HE_,	HE_ },
  { ranger_BE_,	BE_ },
  { ranger_PE_,	PE_ },
  { ranger_HO_,	HO_ },
  { ranger_BO_,	BO_ },
  { ranger_PO_,	PO_ },
  { ranger_MA_,	MA_ },
  { ranger_MI_,	MI_ },
  { ranger_MU_,	MU_ },
  { ranger_ME_,	ME_ },
  { ranger_MO_,	MO_ },
  { ranger_YYA_,	YYA_ },
  { ranger_YA_,	YA_ },
  { ranger_YYU_,	YYU_ },
  { ranger_YU_,	YU_ },
  { ranger_YYO_,	YYO_ },
  { ranger_YO_,	YO_ },
  { ranger_RA_,	RA_ },
  { ranger_RI_,	RI_ },
  { ranger_RU_,	RU_ },
  { ranger_RE_,	RE_ },
  { ranger_RO_,	RO_ },
  //  { ranger_WWA_,	WWA_ },
  { ranger_WA_,	WA_ },
  //  { ranger_III_,	III_ },
  //  { ranger_EEE_,	EEE_ },
  { ranger_WO_,	WO_ },
  { ranger_N_,	N_ },
  //  { ranger_tVU_,	tVU_ },
  //  { ranger_tKKA_,	tKKA_ },
  //  { ranger_tKKE_,	tKKE_ },
  { ranger_kako2_,	kako2_ },
  { ranger_kakot2_,	kakot2_ },
  { ranger_kako_,	kako_ },
  { ranger_kakot_,	kakot_ },
  //  { ranger_Tdaku_,	Tdaku_ },
  //  { ranger_Thatu_,	Thatu_ },
  { ranger_nakag_,	nakag_ },
  { ranger_tenten_,	tenten_ },
  { ranger_osu_,	osu_ },
  { ranger_mesu_,	mesu_ },
  { ranger_kten_,	kten_ },
  { ranger_yen_,	yen_ },
  //  { ranger_Tbou2_,	Tbou2_ },
  { ranger_ArrowU__,	ArrowU__ },
  { ranger_ArrowR__,	ArrowR__ },
  { ranger_ArrowD__,	ArrowD__ },
  { ranger_ArrowL__,	ArrowL__ },
  //  { ranger_Tand_,	Tand_ },

// eurofont start = 352(spc)	// 0x00
//  { ranger_iexcl_,	iexcl_ },
//  { ranger_ordf_,	ordf_ },
//  { ranger_less__,	less__ },
//  { ranger_ordm_,	ordm_ },
//  { ranger_greater_,	greater_ },
  { ranger_OElig_,	OElig_ },
  { ranger_oelig_,	oelig_ },
  //  { ranger_iquest_,	iquest_ },
  { ranger_Agrave_,	Agrave_ },
  { ranger_Aacute_,	Aacute_ },
  { ranger_Acirc_,	Acirc_ },
  { ranger_Auml_,	Auml_ },
  { ranger_Ccedil_,	Ccedil_ },
  //  { ranger_Egave_,	Egave_ },
  { ranger_Eacute_,	Eacute_ },
  { ranger_Ecirc_,	Ecirc_ },
  { ranger_Euml_,	Euml_ },
  { ranger_Igrave_,	Igrave_ },
  { ranger_Iacute_,	Iacute_ },
  { ranger_Icirc_,	Icirc_ },
  { ranger_Iuml_,	Iuml_ },
  //  { ranger_Ntilda_,	Ntilda_ },
  //  { ranger_Ogave_,	Ogave_ },
  { ranger_Oacute_,	Oacute_ },
  { ranger_Ocirc_,	Ocirc_ },
  { ranger_Ouml_,	Ouml_ },
  //  { ranger_Ugave_,	Ugave_ },
  { ranger_Uacute_,	Uacute_ },
  { ranger_Ucirc_,	Ucirc_ },
  { ranger_Uuml_,	Uuml_ },
  { ranger_szlig_,	szlig_ },
  { ranger_agrave_,	agrave_ },
  { ranger_aacute_,	aacute_ },
  { ranger_acirc_,	acirc_ },
  { ranger_auml_,	auml_ },
  { ranger_ccedil_,	ccedil_ },
  //  { ranger_egave_,	egave_ },
  { ranger_eacute_,	eacute_ },
  { ranger_ecirc_,	ecirc_ },
  { ranger_euml_,	euml_ },
  { ranger_igrave_,	igrave_ },
  { ranger_iacute_,	iacute_ },
  { ranger_icirc_,	icirc_ },
  { ranger_iuml_,	iuml_ },
  //  { ranger_ntilda_,	ntilda_ },
  //  { ranger_ogave_,	ogave_ },
  { ranger_oacute_,	oacute_ },
  { ranger_ocirc_,	ocirc_ },
  { ranger_ouml_,	ouml_ },
  //  { ranger_ugave_,	ugave_ },
  { ranger_uacute_,	uacute_ },
  { ranger_ucirc_,	ucirc_ },
  { ranger_uuml_,	uuml_ },
};

static u16 ConvRanger2DP(u16 code)
{
  int i;
  for(i = 0; i < sizeof(Ranger2DpTable) / sizeof(STRCODETABLE); i++)
    if(code == Ranger2DpTable[i].ranger)
      return Ranger2DpTable[i].dp;
  // コードが見つからなかったら「？」を返す
  return hate_;
}

static u16 ConvDP2Ranger(u16 code)
{
  int i;
  for(i = 0; i < sizeof(Ranger2DpTable) / sizeof(STRCODETABLE); i++)
    if(code == Ranger2DpTable[i].dp)
      return Ranger2DpTable[i].ranger;
  // コードが見つからなかったら「？」を返す
  return ranger_hate_;
}

static void ConvDPDec2RangerDec(u16 *p, int value)
{
  p[0] = value / 10000 + ranger_n0_;
  value = value % 10000;
  p[1] = value / 1000 + ranger_n0_;
  value = value % 1000;
  p[2] = value / 100 + ranger_n0_;
  value = value % 100;
  p[3] = value / 10 + ranger_n0_;
  value = value % 10;
  p[4] = value + ranger_n0_;
}

/*  */
