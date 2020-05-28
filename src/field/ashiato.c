//============================================================================================
/**
 * @file	ashiato.c
 * @bfief	�t�g�}�L����p���Պ֐��S
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
//	��`
//
//============================================================================================

typedef struct{
	u16	group;
	u16	ato;
}ASHIATO_TT;


//============================================================================================
//
//	�v���g�^�C�v�錾
//
//============================================================================================



//============================================================================================
//
//	�ϐ�
//
//============================================================================================
//060609��
static const ASHIATO_TT ashi_data[MONSNO_END+1]={
	// ����			 ���Ղ̗L��
	{ 0	, 0},			//dummy(1origin�̈א����킹)
	{ KAWAII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�1
	{ KAWAII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�2
	{ KAKKOII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�3
	{ KAWAII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�4
	{ KAKKOII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�5
	{ KAKKOII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�6
	{ KAWAII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�7
	{ KAWAII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�8
	{ KAKKOII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�9
	{ KAWAII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�10
	{ UNOWN_KEI		,ASHIATO_NASHI},		//�}�Ӕԍ�11
	{ KAWAII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�12
	{ KAWAII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�13
	{ UNOWN_KEI		,ASHIATO_NASHI},		//�}�Ӕԍ�14
	{ KAKKOII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�15
	{ KAWAII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�16
	{ KAWAII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�17
	{ KAKKOII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�18
	{ KAWAII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�19
	{ KAKKOII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�20
	{ KAKKOII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�21
	{ KAKKOII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�22
	{ KOWAI_KEI		,ASHIATO_NASHI},		//�}�Ӕԍ�23
	{ KOWAI_KEI		,ASHIATO_NASHI},		//�}�Ӕԍ�24
	{ KAWAII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�25
	{ KAWAII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�26
	{ KAWAII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�27
	{ KAWAII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�28
	{ KAWAII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�29
	{ KAWAII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�30
	{ KAKKOII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�31
	{ KAWAII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�32
	{ KAKKOII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�33
	{ KAKKOII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�34
	{ KAWAII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�35
	{ KAWAII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�36
	{ KAWAII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�37
	{ KAKKOII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�38
	{ KAWAII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�39
	{ KAWAII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�40
	{ KOWAI_KEI		,ASHIATO_NASHI},		//�}�Ӕԍ�41
	{ KOWAI_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�42
	{ KAWAII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�43
	{ KAWAII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�44
	{ KAWAII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�45
	{ UNOWN_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�46
	{ UNOWN_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�47
	{ KAWAII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�48
	{ UNOWN_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�49
	{ KAWAII_KEI		,ASHIATO_NASHI},		//�}�Ӕԍ�50
	{ KAWAII_KEI		,ASHIATO_NASHI},		//�}�Ӕԍ�51
	{ KAWAII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�52
	{ KAKKOII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�53
	{ OTOBOKE_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�54
	{ KAKKOII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�55
	{ KAKKOII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�56
	{ KAKKOII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�57
	{ KAWAII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�58
	{ KAKKOII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�59
	{ KAWAII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�60
	{ KAWAII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�61
	{ KAKKOII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�62
	{ KAWAII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�63
	{ KAKKOII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�64
	{ KAKKOII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�65
	{ KAWAII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�66
	{ KAKKOII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�67
	{ KAKKOII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�68
	{ KAWAII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�69
	{ OTOBOKE_KEI		,ASHIATO_NASHI},		//�}�Ӕԍ�70
	{ OTOBOKE_KEI		,ASHIATO_NASHI},		//�}�Ӕԍ�71
	{ KAKKOII_KEI		,ASHIATO_NASHI},		//�}�Ӕԍ�72
	{ KAKKOII_KEI		,ASHIATO_NASHI},		//�}�Ӕԍ�73
	{ KAWAII_KEI		,ASHIATO_NASHI},		//�}�Ӕԍ�74
	{ KAKKOII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�75
	{ KAKKOII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�76
	{ KAWAII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�77
	{ KAKKOII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�78
	{ OTOBOKE_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�79
	{ OTOBOKE_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�80
	{ UNOWN_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�81
	{ UNOWN_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�82
	{ KAKKOII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�83
	{ KAWAII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�84
	{ KAKKOII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�85
	{ OTOBOKE_KEI		,ASHIATO_NASHI},		//�}�Ӕԍ�86
	{ OTOBOKE_KEI		,ASHIATO_NASHI},		//�}�Ӕԍ�87
	{ KOWAI_KEI		,ASHIATO_NASHI},		//�}�Ӕԍ�88
	{ KOWAI_KEI		,ASHIATO_NASHI},		//�}�Ӕԍ�89
	{ OTOBOKE_KEI		,ASHIATO_NASHI},		//�}�Ӕԍ�90
	{ KAKKOII_KEI		,ASHIATO_NASHI},		//�}�Ӕԍ�91
	{ KOWAI_KEI		,ASHIATO_NASHI},		//�}�Ӕԍ�92
	{ KOWAI_KEI		,ASHIATO_NASHI},		//�}�Ӕԍ�93
	{ KOWAI_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�94
	{ KAKKOII_KEI		,ASHIATO_NASHI},		//�}�Ӕԍ�95
	{ KOWAI_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�96
	{ KOWAI_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�97
	{ KAWAII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�98
	{ KAKKOII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�99
	{ KAKKOII_KEI		,ASHIATO_NASHI},		//�}�Ӕԍ�100
	{ KAKKOII_KEI		,ASHIATO_NASHI},		//�}�Ӕԍ�101
	{ KAWAII_KEI		,ASHIATO_NASHI},		//�}�Ӕԍ�102
	{ OTOBOKE_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�103
	{ KAWAII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�104
	{ KAKKOII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�105
	{ KAKKOII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�106
	{ KAKKOII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�107
	{ OTOBOKE_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�108
	{ KOWAI_KEI		,ASHIATO_NASHI},		//�}�Ӕԍ�109
	{ KOWAI_KEI		,ASHIATO_NASHI},		//�}�Ӕԍ�110
	{ KAKKOII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�111
	{ KAKKOII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�112
	{ KAWAII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�113
	{ KAWAII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�114
	{ KAKKOII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�115
	{ KAWAII_KEI		,ASHIATO_NASHI},		//�}�Ӕԍ�116
	{ KAKKOII_KEI		,ASHIATO_NASHI},		//�}�Ӕԍ�117
	{ KAWAII_KEI		,ASHIATO_NASHI},		//�}�Ӕԍ�118
	{ KAKKOII_KEI		,ASHIATO_NASHI},		//�}�Ӕԍ�119
	{ UNOWN_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�120
	{ UNOWN_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�121
	{ KAWAII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�122
	{ KAKKOII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�123
	{ KAWAII_KEI		,ASHIATO_NASHI},		//�}�Ӕԍ�124
	{ KAKKOII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�125
	{ KAKKOII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�126
	{ KAKKOII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�127
	{ KAKKOII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�128
	{ OTOBOKE_KEI		,ASHIATO_NASHI},		//�}�Ӕԍ�129
	{ KOWAI_KEI		,ASHIATO_NASHI},		//�}�Ӕԍ�130
	{ KAWAII_KEI		,ASHIATO_NASHI},		//�}�Ӕԍ�131
	{ OTOBOKE_KEI		,ASHIATO_NASHI},		//�}�Ӕԍ�132
	{ KAWAII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�133
	{ KAKKOII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�134
	{ KAKKOII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�135
	{ KAKKOII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�136
	{ UNOWN_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�137
	{ KAWAII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�138
	{ KAKKOII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�139
	{ UNOWN_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�140
	{ KAKKOII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�141
	{ KAKKOII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�142
	{ OTOBOKE_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�143
	{ KAKKOII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�144
	{ KAKKOII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�145
	{ KAKKOII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�146
	{ KAWAII_KEI		,ASHIATO_NASHI},		//�}�Ӕԍ�147
	{ KAKKOII_KEI		,ASHIATO_NASHI},		//�}�Ӕԍ�148
	{ KAKKOII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�149
	{ KAKKOII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�150
	{ KAWAII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�151
	{ KAWAII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�152
	{ KAWAII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�153
	{ KAKKOII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�154
	{ KAWAII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�155
	{ KAKKOII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�156
	{ KAKKOII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�157
	{ KAWAII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�158
	{ KAKKOII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�159
	{ KAKKOII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�160
	{ KAWAII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�161
	{ KAWAII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�162
	{ KAWAII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�163
	{ KAKKOII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�164
	{ KAWAII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�165
	{ KAKKOII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�166
	{ KOWAI_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�167
	{ KOWAI_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�168
	{ KOWAI_KEI		,ASHIATO_NASHI},		//�}�Ӕԍ�169
	{ OTOBOKE_KEI		,ASHIATO_NASHI},		//�}�Ӕԍ�170
	{ KAKKOII_KEI		,ASHIATO_NASHI},		//�}�Ӕԍ�171
	{ KAWAII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�172
	{ KAWAII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�173
	{ KAWAII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�174
	{ KAWAII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�175
	{ KAWAII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�176
	{ KAWAII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�177
	{ UNOWN_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�178
	{ KAWAII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�179
	{ KAWAII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�180
	{ KAWAII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�181
	{ KAWAII_KEI		,ASHIATO_NASHI},		//�}�Ӕԍ�182
	{ KAWAII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�183
	{ KAWAII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�184
	{ OTOBOKE_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�185
	{ KAWAII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�186
	{ KAWAII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�187
	{ KAWAII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�188
	{ KAWAII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�189
	{ KAWAII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�190
	{ KAWAII_KEI		,ASHIATO_NASHI},		//�}�Ӕԍ�191
	{ KAWAII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�192
	{ KAWAII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�193
	{ KAWAII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�194
	{ OTOBOKE_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�195
	{ KAKKOII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�196
	{ KAKKOII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�197
	{ KOWAI_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�198
	{ OTOBOKE_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�199
	{ KOWAI_KEI		,ASHIATO_NASHI},		//�}�Ӕԍ�200
	{ UNOWN_KEI		,ASHIATO_NASHI},		//�}�Ӕԍ�201
	{ OTOBOKE_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�202
	{ KAWAII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�203
	{ UNOWN_KEI		,ASHIATO_NASHI},		//�}�Ӕԍ�204
	{ UNOWN_KEI		,ASHIATO_NASHI},		//�}�Ӕԍ�205
	{ OTOBOKE_KEI		,ASHIATO_NASHI},		//�}�Ӕԍ�206
	{ OTOBOKE_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�207
	{ KAKKOII_KEI		,ASHIATO_NASHI},		//�}�Ӕԍ�208
	{ KAWAII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�209
	{ KAWAII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�210
	{ KAKKOII_KEI		,ASHIATO_NASHI},		//�}�Ӕԍ�211
	{ KAKKOII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�212
	{ KAWAII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�213
	{ KAKKOII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�214
	{ KAKKOII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�215
	{ KAWAII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�216
	{ KAKKOII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�217
	{ OTOBOKE_KEI		,ASHIATO_NASHI},		//�}�Ӕԍ�218
	{ OTOBOKE_KEI		,ASHIATO_NASHI},		//�}�Ӕԍ�219
	{ KAWAII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�220
	{ OTOBOKE_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�221
	{ KAWAII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�222
	{ UNOWN_KEI		,ASHIATO_NASHI},		//�}�Ӕԍ�223
	{ OTOBOKE_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�224
	{ KAWAII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�225
	{ KAKKOII_KEI		,ASHIATO_NASHI},		//�}�Ӕԍ�226
	{ KAKKOII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�227
	{ KOWAI_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�228
	{ KOWAI_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�229
	{ KAKKOII_KEI		,ASHIATO_NASHI},		//�}�Ӕԍ�230
	{ KAWAII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�231
	{ KAKKOII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�232
	{ UNOWN_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�233
	{ KAKKOII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�234
	{ OTOBOKE_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�235
	{ KAWAII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�236
	{ KAKKOII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�237
	{ KAWAII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�238
	{ KAWAII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�239
	{ KAWAII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�240
	{ KAWAII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�241
	{ KAWAII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�242
	{ KAKKOII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�243
	{ KAKKOII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�244
	{ KAKKOII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�245
	{ KAWAII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�246
	{ UNOWN_KEI		,ASHIATO_NASHI},		//�}�Ӕԍ�247
	{ KOWAI_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�248
	{ KAKKOII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�249
	{ KAKKOII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�250
	{ KAWAII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�251
	{ KAWAII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�252
	{ KAKKOII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�253
	{ KAKKOII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�254
	{ KAWAII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�255
	{ KAKKOII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�256
	{ KAKKOII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�257
	{ KAWAII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�258
	{ KAWAII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�259
	{ KAKKOII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�260
	{ KAWAII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�261
	{ KAKKOII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�262
	{ OTOBOKE_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�263
	{ OTOBOKE_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�264
	{ KAWAII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�265
	{ UNOWN_KEI		,ASHIATO_NASHI},		//�}�Ӕԍ�266
	{ KAWAII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�267
	{ UNOWN_KEI		,ASHIATO_NASHI},		//�}�Ӕԍ�268
	{ KAKKOII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�269
	{ KAWAII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�270
	{ OTOBOKE_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�271
	{ OTOBOKE_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�272
	{ UNOWN_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�273
	{ KAKKOII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�274
	{ KOWAI_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�275
	{ KAWAII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�276
	{ KAKKOII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�277
	{ KAWAII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�278
	{ KAWAII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�279
	{ KAWAII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�280
	{ KAWAII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�281
	{ KAWAII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�282
	{ KAWAII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�283
	{ KAKKOII_KEI		,ASHIATO_NASHI},		//�}�Ӕԍ�284
	{ KAWAII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�285
	{ KAKKOII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�286
	{ OTOBOKE_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�287
	{ KAKKOII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�288
	{ OTOBOKE_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�289
	{ UNOWN_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�290
	{ KAKKOII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�291
	{ OTOBOKE_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�292
	{ OTOBOKE_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�293
	{ OTOBOKE_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�294
	{ KAKKOII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�295
	{ KAWAII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�296
	{ KAKKOII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�297
	{ KAWAII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�298
	{ UNOWN_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�299
	{ KAWAII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�300
	{ KAWAII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�301
	{ KOWAI_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�302
	{ KAWAII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�303
	{ KAWAII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�304
	{ KAKKOII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�305
	{ KAKKOII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�306
	{ KAWAII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�307
	{ KAKKOII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�308
	{ KAWAII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�309
	{ KAKKOII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�310
	{ KAWAII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�311
	{ KAWAII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�312
	{ KAKKOII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�313
	{ KAWAII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�314
	{ KAWAII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�315
	{ OTOBOKE_KEI		,ASHIATO_NASHI},		//�}�Ӕԍ�316
	{ OTOBOKE_KEI		,ASHIATO_NASHI},		//�}�Ӕԍ�317
	{ KOWAI_KEI		,ASHIATO_NASHI},		//�}�Ӕԍ�318
	{ KOWAI_KEI		,ASHIATO_NASHI},		//�}�Ӕԍ�319
	{ KAWAII_KEI		,ASHIATO_NASHI},		//�}�Ӕԍ�320
	{ KAKKOII_KEI		,ASHIATO_NASHI},		//�}�Ӕԍ�321
	{ OTOBOKE_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�322
	{ OTOBOKE_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�323
	{ OTOBOKE_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�324
	{ KAWAII_KEI		,ASHIATO_NASHI},		//�}�Ӕԍ�325
	{ KAKKOII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�326
	{ OTOBOKE_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�327
	{ OTOBOKE_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�328
	{ KAKKOII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�329
	{ KAKKOII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�330
	{ KAWAII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�331
	{ KOWAI_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�332
	{ KAWAII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�333
	{ KAWAII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�334
	{ KAKKOII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�335
	{ KOWAI_KEI		,ASHIATO_NASHI},		//�}�Ӕԍ�336
	{ UNOWN_KEI		,ASHIATO_NASHI},		//�}�Ӕԍ�337
	{ UNOWN_KEI		,ASHIATO_NASHI},		//�}�Ӕԍ�338
	{ KAWAII_KEI		,ASHIATO_NASHI},		//�}�Ӕԍ�339
	{ OTOBOKE_KEI		,ASHIATO_NASHI},		//�}�Ӕԍ�340
	{ KAKKOII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�341
	{ KOWAI_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�342
	{ UNOWN_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�343
	{ UNOWN_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�344
	{ UNOWN_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�345
	{ UNOWN_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�346
	{ UNOWN_KEI		,ASHIATO_NASHI},		//�}�Ӕԍ�347
	{ KAKKOII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�348
	{ OTOBOKE_KEI		,ASHIATO_NASHI},		//�}�Ӕԍ�349
	{ KAKKOII_KEI		,ASHIATO_NASHI},		//�}�Ӕԍ�350
	{ KAWAII_KEI		,ASHIATO_NASHI},		//�}�Ӕԍ�351
	{ KAWAII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�352
	{ KOWAI_KEI		,ASHIATO_NASHI},		//�}�Ӕԍ�353
	{ KOWAI_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�354
	{ KOWAI_KEI		,ASHIATO_NASHI},		//�}�Ӕԍ�355
	{ KOWAI_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�356
	{ KAKKOII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�357
	{ KAWAII_KEI		,ASHIATO_NASHI},		//�}�Ӕԍ�358
	{ KOWAI_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�359
	{ OTOBOKE_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�360
	{ KAWAII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�361
	{ KAKKOII_KEI		,ASHIATO_NASHI},		//�}�Ӕԍ�362
	{ KAWAII_KEI		,ASHIATO_NASHI},		//�}�Ӕԍ�363
	{ KAKKOII_KEI		,ASHIATO_NASHI},		//�}�Ӕԍ�364
	{ KAKKOII_KEI		,ASHIATO_NASHI},		//�}�Ӕԍ�365
	{ KAWAII_KEI		,ASHIATO_NASHI},		//�}�Ӕԍ�366
	{ KAKKOII_KEI		,ASHIATO_NASHI},		//�}�Ӕԍ�367
	{ KAWAII_KEI		,ASHIATO_NASHI},		//�}�Ӕԍ�368
	{ OTOBOKE_KEI		,ASHIATO_NASHI},		//�}�Ӕԍ�369
	{ KAWAII_KEI		,ASHIATO_NASHI},		//�}�Ӕԍ�370
	{ KAWAII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�371
	{ UNOWN_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�372
	{ KAKKOII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�373
	{ UNOWN_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�374
	{ UNOWN_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�375
	{ KAKKOII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�376
	{ UNOWN_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�377
	{ UNOWN_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�378
	{ UNOWN_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�379
	{ KAWAII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�380
	{ KAKKOII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�381
	{ KAKKOII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�382
	{ KAKKOII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�383
	{ KAKKOII_KEI		,ASHIATO_NASHI},		//�}�Ӕԍ�384
	{ KAWAII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�385
	{ KAKKOII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�386
	{ KAWAII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�387
	{ KAWAII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�388
	{ KAKKOII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�389
	{ KAWAII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�390
	{ KAKKOII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�391
	{ KAKKOII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�392
	{ KAWAII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�393
	{ KAKKOII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�394
	{ KAKKOII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�395
	{ KAWAII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�396
	{ KAWAII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�397
	{ KAKKOII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�398
	{ OTOBOKE_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�399
	{ OTOBOKE_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�400
	{ KAWAII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�401
	{ KAKKOII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�402
	{ KAWAII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�403
	{ KAWAII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�404
	{ KAKKOII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�405
	{ KAWAII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�406
	{ KAKKOII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�407
	{ KAKKOII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�408
	{ KAKKOII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�409
	{ KAKKOII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�410
	{ KAKKOII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�411
	{ KAWAII_KEI		,ASHIATO_NASHI},		//�}�Ӕԍ�412
	{ KAWAII_KEI		,ASHIATO_NASHI},		//�}�Ӕԍ�413
	{ KAKKOII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�414
	{ KAWAII_KEI		,ASHIATO_NASHI},		//�}�Ӕԍ�415
	{ KAWAII_KEI		,ASHIATO_NASHI},		//�}�Ӕԍ�416
	{ KAWAII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�417
	{ KAWAII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�418
	{ KAKKOII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�419
	{ KAWAII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�420
	{ KAWAII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�421
	{ KAWAII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�422
	{ KOWAI_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�423
	{ KAWAII_KEI	,ASHIATO_ARI},		//�}�Ӕԍ�424
	{ KOWAI_KEI		,ASHIATO_NASHI},		//�}�Ӕԍ�425
	{ KOWAI_KEI		,ASHIATO_NASHI},		//�}�Ӕԍ�426
	{ KAWAII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�427
	{ KAWAII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�428
	{ KOWAI_KEI		,ASHIATO_NASHI},		//�}�Ӕԍ�429
	{ KOWAI_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�430
	{ KAWAII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�431
	{ KAWAII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�432
	{ KAWAII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�433
	{ KOWAI_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�434
	{ KOWAI_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�435
	{ UNOWN_KEI		,ASHIATO_NASHI},		//�}�Ӕԍ�436
	{ UNOWN_KEI		,ASHIATO_NASHI},		//�}�Ӕԍ�437
	{ OTOBOKE_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�438
	{ KAWAII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�439
	{ KAWAII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�440
	{ OTOBOKE_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�441
	{ KOWAI_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�442
	{ KAWAII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�443
	{ KAKKOII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�444
	{ KAKKOII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�445
	{ OTOBOKE_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�446
	{ KAWAII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�447
	{ KAKKOII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�448
	{ OTOBOKE_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�449
	{ KAKKOII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�450
	{ KOWAI_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�451
	{ KOWAI_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�452
	{ KOWAI_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�453
	{ KOWAI_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�454
	{ OTOBOKE_KEI		,ASHIATO_NASHI},		//�}�Ӕԍ�455
	{ KAWAII_KEI		,ASHIATO_NASHI},		//�}�Ӕԍ�456
	{ KAKKOII_KEI		,ASHIATO_NASHI},		//�}�Ӕԍ�457
	{ KAWAII_KEI		,ASHIATO_NASHI},		//�}�Ӕԍ�458
	{ KAWAII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�459
	{ KAKKOII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�460
	{ KAKKOII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�461
	{ UNOWN_KEI		,ASHIATO_NASHI},		//�}�Ӕԍ�462
	{ OTOBOKE_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�463
	{ KAKKOII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�464
	{ OTOBOKE_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�465
	{ KAKKOII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�466
	{ KAKKOII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�467
	{ KAKKOII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�468
	{ KAKKOII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�469
	{ KAKKOII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�470
	{ KAKKOII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�471
	{ KAKKOII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�472
	{ OTOBOKE_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�473
	{ UNOWN_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�474
	{ KAKKOII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�475
	{ UNOWN_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�476
	{ KOWAI_KEI		,ASHIATO_NASHI},		//�}�Ӕԍ�477
	{ KAWAII_KEI		,ASHIATO_NASHI},		//�}�Ӕԍ�478
	{ KAKKOII_KEI		,ASHIATO_NASHI},		//�}�Ӕԍ�479
	{ KAWAII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�480
	{ KAWAII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�481
	{ KAWAII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�482
	{ KAKKOII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�483
	{ KAKKOII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�484
	{ KAKKOII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�485
	{ UNOWN_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�486
	{ KAKKOII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�487
	{ KAKKOII_KEI		,ASHIATO_NASHI},		//�}�Ӕԍ�488
	{ KAWAII_KEI		,ASHIATO_NASHI},		//�}�Ӕԍ�489
	{ KAWAII_KEI		,ASHIATO_NASHI},		//�}�Ӕԍ�490
	{ KOWAI_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�491
	{ KAWAII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�492
	{ KAKKOII_KEI		,ASHIATO_ARI},		//�}�Ӕԍ�493
};

//============================================================================================
//
//	�֐��Q
//
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 *	�|�P�����ԍ����瑫�Ղ̕��ނɕϊ�
 *
 * @param	monsno		�|�P�����ԍ�
 *
 * @return	����(1�`5)
 */
//--------------------------------------------------------------------------------------------
u16 ashiato_group_chk(u16 mons_no)
{
	return ashi_data[mons_no].group;
}

//--------------------------------------------------------------------------------------------
/**
 *	�|�P�����ԍ����瑫�Ղ̗L�����`�F�b�N
 *
 * @param	monsno		�|�P�����ԍ�
 *
 * @return	0:���ՂȂ� 1:���Ղ���
 */
//--------------------------------------------------------------------------------------------
u16 ashiato_ato_chk(u16 mons_no)
{
	return ashi_data[mons_no].ato;
}

//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------
