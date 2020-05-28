//============================================================================================
/**
 * @file	ashiato.c
 * @bfief	ÉtÉgÉ}ÉLÇ≥ÇÒópë´ê’ä÷êîåS
 * @author	Tomomichi Ohta
 * @date	06.05.19
 */
//============================================================================================
#include <nitro.h>
#include <nnsys.h>
#include "common.h"
#include "system/bmp_list.h"
#include "system/bmp_menu.h"
#include "fld_bmp.h"
#include "system/lib_pack.h"
#include "fntsys.h"
#include "system/fontproc.h"
#include "talk_msg.h"
#include "fieldsys.h"
#include "poketool/monsno.h"

#include "ashiato.h"
#include "ashiato_def.h"

//============================================================================================
//
//	íËã`
//
//============================================================================================

typedef struct{
	u16	group;
	u16	ato;
}ASHIATO_TT;


//============================================================================================
//
//	ÉvÉçÉgÉ^ÉCÉvêÈåæ
//
//============================================================================================



//============================================================================================
//
//	ïœêî
//
//============================================================================================
//060609î≈
static const ASHIATO_TT ashi_data[MONSNO_END+1]={
	// ï™óﬁ			 ë´ê’ÇÃóLñ≥
	{ 0	, 0},			//dummy(1originÇÃà◊êîçáÇÌÇπ)
	{ KAWAII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ1
	{ KAWAII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ2
	{ KAKKOII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ3
	{ KAWAII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ4
	{ KAKKOII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ5
	{ KAKKOII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ6
	{ KAWAII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ7
	{ KAWAII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ8
	{ KAKKOII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ9
	{ KAWAII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ10
	{ UNOWN_KEI		,ASHIATO_NASHI},		//ê}ä”î‘çÜ11
	{ KAWAII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ12
	{ KAWAII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ13
	{ UNOWN_KEI		,ASHIATO_NASHI},		//ê}ä”î‘çÜ14
	{ KAKKOII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ15
	{ KAWAII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ16
	{ KAWAII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ17
	{ KAKKOII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ18
	{ KAWAII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ19
	{ KAKKOII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ20
	{ KAKKOII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ21
	{ KAKKOII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ22
	{ KOWAI_KEI		,ASHIATO_NASHI},		//ê}ä”î‘çÜ23
	{ KOWAI_KEI		,ASHIATO_NASHI},		//ê}ä”î‘çÜ24
	{ KAWAII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ25
	{ KAWAII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ26
	{ KAWAII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ27
	{ KAWAII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ28
	{ KAWAII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ29
	{ KAWAII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ30
	{ KAKKOII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ31
	{ KAWAII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ32
	{ KAKKOII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ33
	{ KAKKOII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ34
	{ KAWAII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ35
	{ KAWAII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ36
	{ KAWAII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ37
	{ KAKKOII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ38
	{ KAWAII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ39
	{ KAWAII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ40
	{ KOWAI_KEI		,ASHIATO_NASHI},		//ê}ä”î‘çÜ41
	{ KOWAI_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ42
	{ KAWAII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ43
	{ KAWAII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ44
	{ KAWAII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ45
	{ UNOWN_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ46
	{ UNOWN_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ47
	{ KAWAII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ48
	{ UNOWN_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ49
	{ KAWAII_KEI		,ASHIATO_NASHI},		//ê}ä”î‘çÜ50
	{ KAWAII_KEI		,ASHIATO_NASHI},		//ê}ä”î‘çÜ51
	{ KAWAII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ52
	{ KAKKOII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ53
	{ OTOBOKE_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ54
	{ KAKKOII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ55
	{ KAKKOII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ56
	{ KAKKOII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ57
	{ KAWAII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ58
	{ KAKKOII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ59
	{ KAWAII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ60
	{ KAWAII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ61
	{ KAKKOII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ62
	{ KAWAII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ63
	{ KAKKOII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ64
	{ KAKKOII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ65
	{ KAWAII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ66
	{ KAKKOII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ67
	{ KAKKOII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ68
	{ KAWAII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ69
	{ OTOBOKE_KEI		,ASHIATO_NASHI},		//ê}ä”î‘çÜ70
	{ OTOBOKE_KEI		,ASHIATO_NASHI},		//ê}ä”î‘çÜ71
	{ KAKKOII_KEI		,ASHIATO_NASHI},		//ê}ä”î‘çÜ72
	{ KAKKOII_KEI		,ASHIATO_NASHI},		//ê}ä”î‘çÜ73
	{ KAWAII_KEI		,ASHIATO_NASHI},		//ê}ä”î‘çÜ74
	{ KAKKOII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ75
	{ KAKKOII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ76
	{ KAWAII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ77
	{ KAKKOII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ78
	{ OTOBOKE_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ79
	{ OTOBOKE_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ80
	{ UNOWN_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ81
	{ UNOWN_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ82
	{ KAKKOII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ83
	{ KAWAII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ84
	{ KAKKOII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ85
	{ OTOBOKE_KEI		,ASHIATO_NASHI},		//ê}ä”î‘çÜ86
	{ OTOBOKE_KEI		,ASHIATO_NASHI},		//ê}ä”î‘çÜ87
	{ KOWAI_KEI		,ASHIATO_NASHI},		//ê}ä”î‘çÜ88
	{ KOWAI_KEI		,ASHIATO_NASHI},		//ê}ä”î‘çÜ89
	{ OTOBOKE_KEI		,ASHIATO_NASHI},		//ê}ä”î‘çÜ90
	{ KAKKOII_KEI		,ASHIATO_NASHI},		//ê}ä”î‘çÜ91
	{ KOWAI_KEI		,ASHIATO_NASHI},		//ê}ä”î‘çÜ92
	{ KOWAI_KEI		,ASHIATO_NASHI},		//ê}ä”î‘çÜ93
	{ KOWAI_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ94
	{ KAKKOII_KEI		,ASHIATO_NASHI},		//ê}ä”î‘çÜ95
	{ KOWAI_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ96
	{ KOWAI_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ97
	{ KAWAII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ98
	{ KAKKOII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ99
	{ KAKKOII_KEI		,ASHIATO_NASHI},		//ê}ä”î‘çÜ100
	{ KAKKOII_KEI		,ASHIATO_NASHI},		//ê}ä”î‘çÜ101
	{ KAWAII_KEI		,ASHIATO_NASHI},		//ê}ä”î‘çÜ102
	{ OTOBOKE_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ103
	{ KAWAII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ104
	{ KAKKOII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ105
	{ KAKKOII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ106
	{ KAKKOII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ107
	{ OTOBOKE_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ108
	{ KOWAI_KEI		,ASHIATO_NASHI},		//ê}ä”î‘çÜ109
	{ KOWAI_KEI		,ASHIATO_NASHI},		//ê}ä”î‘çÜ110
	{ KAKKOII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ111
	{ KAKKOII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ112
	{ KAWAII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ113
	{ KAWAII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ114
	{ KAKKOII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ115
	{ KAWAII_KEI		,ASHIATO_NASHI},		//ê}ä”î‘çÜ116
	{ KAKKOII_KEI		,ASHIATO_NASHI},		//ê}ä”î‘çÜ117
	{ KAWAII_KEI		,ASHIATO_NASHI},		//ê}ä”î‘çÜ118
	{ KAKKOII_KEI		,ASHIATO_NASHI},		//ê}ä”î‘çÜ119
	{ UNOWN_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ120
	{ UNOWN_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ121
	{ KAWAII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ122
	{ KAKKOII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ123
	{ KAWAII_KEI		,ASHIATO_NASHI},		//ê}ä”î‘çÜ124
	{ KAKKOII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ125
	{ KAKKOII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ126
	{ KAKKOII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ127
	{ KAKKOII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ128
	{ OTOBOKE_KEI		,ASHIATO_NASHI},		//ê}ä”î‘çÜ129
	{ KOWAI_KEI		,ASHIATO_NASHI},		//ê}ä”î‘çÜ130
	{ KAWAII_KEI		,ASHIATO_NASHI},		//ê}ä”î‘çÜ131
	{ OTOBOKE_KEI		,ASHIATO_NASHI},		//ê}ä”î‘çÜ132
	{ KAWAII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ133
	{ KAKKOII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ134
	{ KAKKOII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ135
	{ KAKKOII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ136
	{ UNOWN_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ137
	{ KAWAII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ138
	{ KAKKOII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ139
	{ UNOWN_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ140
	{ KAKKOII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ141
	{ KAKKOII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ142
	{ OTOBOKE_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ143
	{ KAKKOII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ144
	{ KAKKOII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ145
	{ KAKKOII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ146
	{ KAWAII_KEI		,ASHIATO_NASHI},		//ê}ä”î‘çÜ147
	{ KAKKOII_KEI		,ASHIATO_NASHI},		//ê}ä”î‘çÜ148
	{ KAKKOII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ149
	{ KAKKOII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ150
	{ KAWAII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ151
	{ KAWAII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ152
	{ KAWAII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ153
	{ KAKKOII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ154
	{ KAWAII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ155
	{ KAKKOII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ156
	{ KAKKOII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ157
	{ KAWAII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ158
	{ KAKKOII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ159
	{ KAKKOII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ160
	{ KAWAII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ161
	{ KAWAII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ162
	{ KAWAII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ163
	{ KAKKOII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ164
	{ KAWAII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ165
	{ KAKKOII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ166
	{ KOWAI_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ167
	{ KOWAI_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ168
	{ KOWAI_KEI		,ASHIATO_NASHI},		//ê}ä”î‘çÜ169
	{ OTOBOKE_KEI		,ASHIATO_NASHI},		//ê}ä”î‘çÜ170
	{ KAKKOII_KEI		,ASHIATO_NASHI},		//ê}ä”î‘çÜ171
	{ KAWAII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ172
	{ KAWAII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ173
	{ KAWAII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ174
	{ KAWAII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ175
	{ KAWAII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ176
	{ KAWAII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ177
	{ UNOWN_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ178
	{ KAWAII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ179
	{ KAWAII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ180
	{ KAWAII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ181
	{ KAWAII_KEI		,ASHIATO_NASHI},		//ê}ä”î‘çÜ182
	{ KAWAII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ183
	{ KAWAII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ184
	{ OTOBOKE_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ185
	{ KAWAII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ186
	{ KAWAII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ187
	{ KAWAII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ188
	{ KAWAII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ189
	{ KAWAII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ190
	{ KAWAII_KEI		,ASHIATO_NASHI},		//ê}ä”î‘çÜ191
	{ KAWAII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ192
	{ KAWAII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ193
	{ KAWAII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ194
	{ OTOBOKE_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ195
	{ KAKKOII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ196
	{ KAKKOII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ197
	{ KOWAI_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ198
	{ OTOBOKE_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ199
	{ KOWAI_KEI		,ASHIATO_NASHI},		//ê}ä”î‘çÜ200
	{ UNOWN_KEI		,ASHIATO_NASHI},		//ê}ä”î‘çÜ201
	{ OTOBOKE_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ202
	{ KAWAII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ203
	{ UNOWN_KEI		,ASHIATO_NASHI},		//ê}ä”î‘çÜ204
	{ UNOWN_KEI		,ASHIATO_NASHI},		//ê}ä”î‘çÜ205
	{ OTOBOKE_KEI		,ASHIATO_NASHI},		//ê}ä”î‘çÜ206
	{ OTOBOKE_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ207
	{ KAKKOII_KEI		,ASHIATO_NASHI},		//ê}ä”î‘çÜ208
	{ KAWAII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ209
	{ KAWAII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ210
	{ KAKKOII_KEI		,ASHIATO_NASHI},		//ê}ä”î‘çÜ211
	{ KAKKOII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ212
	{ KAWAII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ213
	{ KAKKOII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ214
	{ KAKKOII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ215
	{ KAWAII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ216
	{ KAKKOII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ217
	{ OTOBOKE_KEI		,ASHIATO_NASHI},		//ê}ä”î‘çÜ218
	{ OTOBOKE_KEI		,ASHIATO_NASHI},		//ê}ä”î‘çÜ219
	{ KAWAII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ220
	{ OTOBOKE_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ221
	{ KAWAII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ222
	{ UNOWN_KEI		,ASHIATO_NASHI},		//ê}ä”î‘çÜ223
	{ OTOBOKE_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ224
	{ KAWAII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ225
	{ KAKKOII_KEI		,ASHIATO_NASHI},		//ê}ä”î‘çÜ226
	{ KAKKOII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ227
	{ KOWAI_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ228
	{ KOWAI_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ229
	{ KAKKOII_KEI		,ASHIATO_NASHI},		//ê}ä”î‘çÜ230
	{ KAWAII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ231
	{ KAKKOII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ232
	{ UNOWN_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ233
	{ KAKKOII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ234
	{ OTOBOKE_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ235
	{ KAWAII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ236
	{ KAKKOII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ237
	{ KAWAII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ238
	{ KAWAII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ239
	{ KAWAII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ240
	{ KAWAII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ241
	{ KAWAII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ242
	{ KAKKOII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ243
	{ KAKKOII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ244
	{ KAKKOII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ245
	{ KAWAII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ246
	{ UNOWN_KEI		,ASHIATO_NASHI},		//ê}ä”î‘çÜ247
	{ KOWAI_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ248
	{ KAKKOII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ249
	{ KAKKOII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ250
	{ KAWAII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ251
	{ KAWAII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ252
	{ KAKKOII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ253
	{ KAKKOII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ254
	{ KAWAII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ255
	{ KAKKOII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ256
	{ KAKKOII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ257
	{ KAWAII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ258
	{ KAWAII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ259
	{ KAKKOII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ260
	{ KAWAII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ261
	{ KAKKOII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ262
	{ OTOBOKE_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ263
	{ OTOBOKE_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ264
	{ KAWAII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ265
	{ UNOWN_KEI		,ASHIATO_NASHI},		//ê}ä”î‘çÜ266
	{ KAWAII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ267
	{ UNOWN_KEI		,ASHIATO_NASHI},		//ê}ä”î‘çÜ268
	{ KAKKOII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ269
	{ KAWAII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ270
	{ OTOBOKE_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ271
	{ OTOBOKE_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ272
	{ UNOWN_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ273
	{ KAKKOII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ274
	{ KOWAI_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ275
	{ KAWAII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ276
	{ KAKKOII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ277
	{ KAWAII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ278
	{ KAWAII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ279
	{ KAWAII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ280
	{ KAWAII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ281
	{ KAWAII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ282
	{ KAWAII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ283
	{ KAKKOII_KEI		,ASHIATO_NASHI},		//ê}ä”î‘çÜ284
	{ KAWAII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ285
	{ KAKKOII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ286
	{ OTOBOKE_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ287
	{ KAKKOII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ288
	{ OTOBOKE_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ289
	{ UNOWN_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ290
	{ KAKKOII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ291
	{ OTOBOKE_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ292
	{ OTOBOKE_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ293
	{ OTOBOKE_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ294
	{ KAKKOII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ295
	{ KAWAII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ296
	{ KAKKOII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ297
	{ KAWAII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ298
	{ UNOWN_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ299
	{ KAWAII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ300
	{ KAWAII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ301
	{ KOWAI_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ302
	{ KAWAII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ303
	{ KAWAII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ304
	{ KAKKOII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ305
	{ KAKKOII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ306
	{ KAWAII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ307
	{ KAKKOII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ308
	{ KAWAII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ309
	{ KAKKOII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ310
	{ KAWAII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ311
	{ KAWAII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ312
	{ KAKKOII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ313
	{ KAWAII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ314
	{ KAWAII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ315
	{ OTOBOKE_KEI		,ASHIATO_NASHI},		//ê}ä”î‘çÜ316
	{ OTOBOKE_KEI		,ASHIATO_NASHI},		//ê}ä”î‘çÜ317
	{ KOWAI_KEI		,ASHIATO_NASHI},		//ê}ä”î‘çÜ318
	{ KOWAI_KEI		,ASHIATO_NASHI},		//ê}ä”î‘çÜ319
	{ KAWAII_KEI		,ASHIATO_NASHI},		//ê}ä”î‘çÜ320
	{ KAKKOII_KEI		,ASHIATO_NASHI},		//ê}ä”î‘çÜ321
	{ OTOBOKE_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ322
	{ OTOBOKE_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ323
	{ OTOBOKE_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ324
	{ KAWAII_KEI		,ASHIATO_NASHI},		//ê}ä”î‘çÜ325
	{ KAKKOII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ326
	{ OTOBOKE_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ327
	{ OTOBOKE_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ328
	{ KAKKOII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ329
	{ KAKKOII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ330
	{ KAWAII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ331
	{ KOWAI_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ332
	{ KAWAII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ333
	{ KAWAII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ334
	{ KAKKOII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ335
	{ KOWAI_KEI		,ASHIATO_NASHI},		//ê}ä”î‘çÜ336
	{ UNOWN_KEI		,ASHIATO_NASHI},		//ê}ä”î‘çÜ337
	{ UNOWN_KEI		,ASHIATO_NASHI},		//ê}ä”î‘çÜ338
	{ KAWAII_KEI		,ASHIATO_NASHI},		//ê}ä”î‘çÜ339
	{ OTOBOKE_KEI		,ASHIATO_NASHI},		//ê}ä”î‘çÜ340
	{ KAKKOII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ341
	{ KOWAI_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ342
	{ UNOWN_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ343
	{ UNOWN_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ344
	{ UNOWN_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ345
	{ UNOWN_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ346
	{ UNOWN_KEI		,ASHIATO_NASHI},		//ê}ä”î‘çÜ347
	{ KAKKOII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ348
	{ OTOBOKE_KEI		,ASHIATO_NASHI},		//ê}ä”î‘çÜ349
	{ KAKKOII_KEI		,ASHIATO_NASHI},		//ê}ä”î‘çÜ350
	{ KAWAII_KEI		,ASHIATO_NASHI},		//ê}ä”î‘çÜ351
	{ KAWAII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ352
	{ KOWAI_KEI		,ASHIATO_NASHI},		//ê}ä”î‘çÜ353
	{ KOWAI_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ354
	{ KOWAI_KEI		,ASHIATO_NASHI},		//ê}ä”î‘çÜ355
	{ KOWAI_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ356
	{ KAKKOII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ357
	{ KAWAII_KEI		,ASHIATO_NASHI},		//ê}ä”î‘çÜ358
	{ KOWAI_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ359
	{ OTOBOKE_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ360
	{ KAWAII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ361
	{ KAKKOII_KEI		,ASHIATO_NASHI},		//ê}ä”î‘çÜ362
	{ KAWAII_KEI		,ASHIATO_NASHI},		//ê}ä”î‘çÜ363
	{ KAKKOII_KEI		,ASHIATO_NASHI},		//ê}ä”î‘çÜ364
	{ KAKKOII_KEI		,ASHIATO_NASHI},		//ê}ä”î‘çÜ365
	{ KAWAII_KEI		,ASHIATO_NASHI},		//ê}ä”î‘çÜ366
	{ KAKKOII_KEI		,ASHIATO_NASHI},		//ê}ä”î‘çÜ367
	{ KAWAII_KEI		,ASHIATO_NASHI},		//ê}ä”î‘çÜ368
	{ OTOBOKE_KEI		,ASHIATO_NASHI},		//ê}ä”î‘çÜ369
	{ KAWAII_KEI		,ASHIATO_NASHI},		//ê}ä”î‘çÜ370
	{ KAWAII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ371
	{ UNOWN_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ372
	{ KAKKOII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ373
	{ UNOWN_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ374
	{ UNOWN_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ375
	{ KAKKOII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ376
	{ UNOWN_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ377
	{ UNOWN_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ378
	{ UNOWN_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ379
	{ KAWAII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ380
	{ KAKKOII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ381
	{ KAKKOII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ382
	{ KAKKOII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ383
	{ KAKKOII_KEI		,ASHIATO_NASHI},		//ê}ä”î‘çÜ384
	{ KAWAII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ385
	{ KAKKOII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ386
	{ KAWAII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ387
	{ KAWAII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ388
	{ KAKKOII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ389
	{ KAWAII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ390
	{ KAKKOII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ391
	{ KAKKOII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ392
	{ KAWAII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ393
	{ KAKKOII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ394
	{ KAKKOII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ395
	{ KAWAII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ396
	{ KAWAII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ397
	{ KAKKOII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ398
	{ OTOBOKE_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ399
	{ OTOBOKE_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ400
	{ KAWAII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ401
	{ KAKKOII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ402
	{ KAWAII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ403
	{ KAWAII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ404
	{ KAKKOII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ405
	{ KAWAII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ406
	{ KAKKOII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ407
	{ KAKKOII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ408
	{ KAKKOII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ409
	{ KAKKOII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ410
	{ KAKKOII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ411
	{ KAWAII_KEI		,ASHIATO_NASHI},		//ê}ä”î‘çÜ412
	{ KAWAII_KEI		,ASHIATO_NASHI},		//ê}ä”î‘çÜ413
	{ KAKKOII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ414
	{ KAWAII_KEI		,ASHIATO_NASHI},		//ê}ä”î‘çÜ415
	{ KAWAII_KEI		,ASHIATO_NASHI},		//ê}ä”î‘çÜ416
	{ KAWAII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ417
	{ KAWAII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ418
	{ KAKKOII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ419
	{ KAWAII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ420
	{ KAWAII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ421
	{ KAWAII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ422
	{ KOWAI_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ423
	{ KAWAII_KEI	,ASHIATO_ARI},		//ê}ä”î‘çÜ424
	{ KOWAI_KEI		,ASHIATO_NASHI},		//ê}ä”î‘çÜ425
	{ KOWAI_KEI		,ASHIATO_NASHI},		//ê}ä”î‘çÜ426
	{ KAWAII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ427
	{ KAWAII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ428
	{ KOWAI_KEI		,ASHIATO_NASHI},		//ê}ä”î‘çÜ429
	{ KOWAI_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ430
	{ KAWAII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ431
	{ KAWAII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ432
	{ KAWAII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ433
	{ KOWAI_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ434
	{ KOWAI_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ435
	{ UNOWN_KEI		,ASHIATO_NASHI},		//ê}ä”î‘çÜ436
	{ UNOWN_KEI		,ASHIATO_NASHI},		//ê}ä”î‘çÜ437
	{ OTOBOKE_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ438
	{ KAWAII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ439
	{ KAWAII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ440
	{ OTOBOKE_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ441
	{ KOWAI_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ442
	{ KAWAII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ443
	{ KAKKOII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ444
	{ KAKKOII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ445
	{ OTOBOKE_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ446
	{ KAWAII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ447
	{ KAKKOII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ448
	{ OTOBOKE_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ449
	{ KAKKOII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ450
	{ KOWAI_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ451
	{ KOWAI_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ452
	{ KOWAI_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ453
	{ KOWAI_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ454
	{ OTOBOKE_KEI		,ASHIATO_NASHI},		//ê}ä”î‘çÜ455
	{ KAWAII_KEI		,ASHIATO_NASHI},		//ê}ä”î‘çÜ456
	{ KAKKOII_KEI		,ASHIATO_NASHI},		//ê}ä”î‘çÜ457
	{ KAWAII_KEI		,ASHIATO_NASHI},		//ê}ä”î‘çÜ458
	{ KAWAII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ459
	{ KAKKOII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ460
	{ KAKKOII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ461
	{ UNOWN_KEI		,ASHIATO_NASHI},		//ê}ä”î‘çÜ462
	{ OTOBOKE_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ463
	{ KAKKOII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ464
	{ OTOBOKE_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ465
	{ KAKKOII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ466
	{ KAKKOII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ467
	{ KAKKOII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ468
	{ KAKKOII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ469
	{ KAKKOII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ470
	{ KAKKOII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ471
	{ KAKKOII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ472
	{ OTOBOKE_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ473
	{ UNOWN_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ474
	{ KAKKOII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ475
	{ UNOWN_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ476
	{ KOWAI_KEI		,ASHIATO_NASHI},		//ê}ä”î‘çÜ477
	{ KAWAII_KEI		,ASHIATO_NASHI},		//ê}ä”î‘çÜ478
	{ KAKKOII_KEI		,ASHIATO_NASHI},		//ê}ä”î‘çÜ479
	{ KAWAII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ480
	{ KAWAII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ481
	{ KAWAII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ482
	{ KAKKOII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ483
	{ KAKKOII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ484
	{ KAKKOII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ485
	{ UNOWN_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ486
	{ KAKKOII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ487
	{ KAKKOII_KEI		,ASHIATO_NASHI},		//ê}ä”î‘çÜ488
	{ KAWAII_KEI		,ASHIATO_NASHI},		//ê}ä”î‘çÜ489
	{ KAWAII_KEI		,ASHIATO_NASHI},		//ê}ä”î‘çÜ490
	{ KOWAI_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ491
	{ KAWAII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ492
	{ KAKKOII_KEI		,ASHIATO_ARI},		//ê}ä”î‘çÜ493
};

//============================================================================================
//
//	ä÷êîåQ
//
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 *	É|ÉPÉÇÉìî‘çÜÇ©ÇÁë´ê’ÇÃï™óﬁÇ…ïœä∑
 *
 * @param	monsno		É|ÉPÉÇÉìî‘çÜ
 *
 * @return	ï™óﬁ(1Å`5)
 */
//--------------------------------------------------------------------------------------------
u16 ashiato_group_chk(u16 mons_no)
{
	return ashi_data[mons_no].group;
}

//--------------------------------------------------------------------------------------------
/**
 *	É|ÉPÉÇÉìî‘çÜÇ©ÇÁë´ê’ÇÃóLñ≥ÇÉ`ÉFÉbÉN
 *
 * @param	monsno		É|ÉPÉÇÉìî‘çÜ
 *
 * @return	0:ë´ê’Ç»Çµ 1:ë´ê’Ç†ÇË
 */
//--------------------------------------------------------------------------------------------
u16 ashiato_ato_chk(u16 mons_no)
{
	return ashi_data[mons_no].ato;
}

//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------
