//============================================================================================
/**
 * @file	safari_enc.c
 * @brief	サファリエンカウント関連
 * @author	saitou
 *
 */
//============================================================================================
#include "common.h"
#include "system/arc_tool.h"
#include "fielddata/maptable/zone_id.h"
#include "arc/encdata_ex.naix"

#include "encount_define.h"

#include "safari_enc.h"

#define SAFARI_BIT_SHIFT	(5)

static u8 GetSafariArea( const int inZoneID );

//-----------------------------------------------------------------------------
/**
 * サファリエンカウントテーブル差し替え
 *
 * @param	inRandomSeed		ランダムの種
 * @param	inBookGet			全国図鑑入手フラグ
 * @param	inZoneID			ゾーンＩＤ
 * @param	*outSafEncMonsNo1	エンカウントポケモン1体目
 * @param	*outSafEncMonsNo2	エンカウントポケモン2体目
 *
 * @return	none
 */
//-----------------------------------------------------------------------------
void SafariEnc_SetSafariEnc(	const int inRandomSeed, const BOOL inBookGet,
								const int inZoneID,
								int *outSafEncMonsNo1, int *outSafEncMonsNo2)
{
	int *tbl;
	int arc_idx;
	u8 tblno;
	u8 area = GetSafariArea( inZoneID );
	
	//全国図鑑完成かどうかで、テーブルを変える
	if(inBookGet){
		arc_idx = NARC_encdata_ex_safari_af_bin;
	}else{
		arc_idx = NARC_encdata_ex_safari_bef_bin;
	}
	//サファリエンカウントテーブル取得
	tbl = ArchiveDataLoadMallocLo(ARC_ENCDATA_EX, arc_idx, HEAPID_FIELD);
	//ランダムの種を元にサファリエンカウントテーブルからポケモン選出
	
	/* ---選出方法--- */
	/*サファリランダムの種を5ビットずつ下位ビットから6分割する。上位2ビットは使わない*/
	/*サファリエリア番号（0～5）から、使うビット群を決定*/
	/*0なら、下位5ビット。1なら次の5ビット・・・*/
	/*指定5ビットで決定される数字（0～31）がサファリ特殊テーブルで指定されるインデックスとなる*/
	/*そのインデックスで決定するポケモンナンバーが特殊枠に入る*/
	/*特殊枠2つには同じポケモンナンバーが入る*/
	
	tblno = ( (inRandomSeed >> (SAFARI_BIT_SHIFT*area)) & 0x1f );

	tblno %= SAFARI_TBL_MAX;//<<念のためテーブル最大数の余りを採用値とする

	(*outSafEncMonsNo1) = tbl[tblno];
	(*outSafEncMonsNo2) = tbl[tblno];

	sys_FreeMemoryEz(tbl);
}

//-----------------------------------------------------------------------------
/**
 * ゾーンＩＤからサファリエリア番号（0～5）を返す
 * 0：左上	・・・　5：右下
 *
 * @param	inZoneID		ゾーンＩＤ
 *
 * @return	u8				サファリエリア番号(0～5)
 */
//-----------------------------------------------------------------------------
static u8 GetSafariArea( const int inZoneID )
{
	u8 area = 0;

	switch(inZoneID){
	case ZONE_ID_D06R0201:
		area = 0;
		break;
	case ZONE_ID_D06R0202:
		area = 1;
		break;
	case ZONE_ID_D06R0203:
		area = 2;
		break;
	case ZONE_ID_D06R0204:
		area = 3;
		break;
	case ZONE_ID_D06R0205:
		area = 4;
		break;
	case ZONE_ID_D06R0206:
		area = 5;
		break;
	default:
		GF_ASSERT(0&&"サファリゾーンではない");
	}
	
	return area;
}


#ifdef PM_DEBUG
//サファリテーブル算出
void SafariEnc_DebugGetSafariTbl(	const int inRandomSeed, const BOOL inBookGet,
									const u8 inArea,
									int *outSaf, int *outSafEncMonsNo)
{
	int *tbl;
	int arc_idx;
	u8 tblno;
	u8 area = inArea;
	
	//全国図鑑完成かどうかで、テーブルを変える
	if(inBookGet){
		arc_idx = NARC_encdata_ex_safari_af_bin;
	}else{
		arc_idx = NARC_encdata_ex_safari_bef_bin;
	}
	//サファリエンカウントテーブル取得
	tbl = ArchiveDataLoadMallocLo(ARC_ENCDATA_EX, arc_idx, HEAPID_FIELD);
	//ランダムの種を元にサファリエンカウントテーブルからポケモン選出
	
	/* ---選出方法--- */
	/*サファリランダムの種を5ビットずつ下位ビットから6分割する。上位2ビットは使わない*/
	/*サファリエリア番号（0～5）から、使うビット群を決定*/
	/*0なら、下位5ビット。1なら次の5ビット・・・*/
	/*指定5ビットで決定される数字（0～31）がサファリ特殊テーブルで指定されるインデックスとなる*/
	/*そのインデックスで決定するポケモンナンバーが特殊枠に入る*/
	/*特殊枠2つには同じポケモンナンバーが入る*/
	
	tblno = ( (inRandomSeed >> (SAFARI_BIT_SHIFT*area)) & 0x1f );

	tblno %= SAFARI_TBL_MAX;//<<念のためテーブル最大数の余りを採用値とする

	(*outSaf) = tblno;
	(*outSafEncMonsNo) = tbl[tblno];

	sys_FreeMemoryEz(tbl);
}

#endif
