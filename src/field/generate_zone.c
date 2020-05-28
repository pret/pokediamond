//============================================================================================
/**
 * @file	generate_zone.c
 * @bfief	大量発生ゾーン
 * @author	Nozomu Saitou
 *
 * @date	2006.05.13
 */
//============================================================================================
#include "common.h"
#include "fieldsys.h"		//for eventdata.h
#include "fielddata/maptable/zone_id.h"
#include "enc_tbl_change_def.h"
#include "encount_dat.h"
#include "eventdata.h"

#include "generate_zone.h"

#define GENERATE_ZONE_MAX	(28)

static const u32 GenerateZoneTbl[GENERATE_ZONE_MAX] = 
{
	ZONE_ID_R201,
	ZONE_ID_R202,
	ZONE_ID_R203,
	ZONE_ID_R206,
	ZONE_ID_R207,
	ZONE_ID_R208,
	ZONE_ID_R209,
	ZONE_ID_R213,
	ZONE_ID_R214,
	ZONE_ID_R215,
	ZONE_ID_R216,
	ZONE_ID_R217,
	ZONE_ID_R218,
	ZONE_ID_R221,
	ZONE_ID_R222,
	ZONE_ID_R224,
	ZONE_ID_R225,
	ZONE_ID_W226,
	ZONE_ID_R227,
	ZONE_ID_R228,
	ZONE_ID_R229,
	ZONE_ID_W230,
	ZONE_ID_D27R0102,
	ZONE_ID_D28R0102,
	ZONE_ID_D29R0102,
	ZONE_ID_D02,
	ZONE_ID_D03R0101,
	ZONE_ID_D04
};

//-----------------------------------------------------------------------------
/**
 * 大量発生しているゾーンの取得
 *
 * @param	inRnadSeed			ランダムの種
 *
 * @return	u32					ゾーンＩＤ
 */
//-----------------------------------------------------------------------------
u32 GenerateZone_GetZone(const u32 inRandSeed)
{
	/* ---ゾーン決定方法--- */
	/*大量発生ランダムの種を大量発生ゾーンテーブル数で割った余りをインデックスとして*/
	/*大量発生ゾーンテーブルからゾーンＩＤを決定する*/
	return GenerateZoneTbl[(inRandSeed % GENERATE_ZONE_MAX)];
}

//-----------------------------------------------------------------------------
/**
 * 大量発生情報（ゾーン、発生ポケモン）取得
 *
 * @param	inRnadSeed			ランダムの種
 *
 * @return	none
 */
//-----------------------------------------------------------------------------
void GenerateZone_GetInfo(const u32 inRandSeed, u16 *outZone, u16 *outMonsNo)
{
	ENCOUNT_DATA enc_data;
	u32 zone_id;
	zone_id = GenerateZoneTbl[(inRandSeed % GENERATE_ZONE_MAX)];
	EventData_LoadEncountData(&enc_data, zone_id);
	(*outMonsNo) = enc_data.GenerateEnc[GENE_ENC_1];
	(*outZone) = zone_id;
}
