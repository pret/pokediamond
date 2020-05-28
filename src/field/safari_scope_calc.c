//===========================================================================
/**
 * @file	safari_scope_calc.c
 * @brief	サファリ望遠鏡
 * @author	Nozomu Saito
 * @date	2006.04.24
 * 
 */
//===========================================================================
#include "common.h"
#include "fieldsys.h"
#include "encount_dat.h"
#include "eventdata.h"
#include "ev_mapchange.h"
#include "zonedata.h"
#include "system/arc_tool.h"
#include "system/timezone.h"
#include "system/zukanwork.h"
#include "safari_scope_common.h"
#include "safari_scope_calc.h"
#include "enc_tbl_change_def.h"
#include "encount_set.h"
#include "savedata/encount.h"

#include "fielddata/mapmatrix/map_matrix_id.h"
#include "arc/encdata_ex.naix"

#include "safari_enc.h"
#include "agb_slot_enc.h"

#define SPOT_LIST_MAX	(36)

typedef struct SCOPE_WIEWSPOT_tag
{
	u16 X;
	u16 Z;
}SCOPE_VIEWSPOT;

typedef struct SCOPE_DATA_tag
{
	SCOPE_VIEWSPOT Spot[SCOPE_DISP_CNT+1];
	LOCATION_WORK Next;
	FIELDSYS_WORK * fsys;
	int ReturnZoneID;
}SCOPE_DATA;

//--------------------------------------------------------------------------------------------
/**
 * 望遠鏡に出すポケモンの決定
 *
 * @param	fsys	フィールドシステムポインタ
 *
 * @return	int		モンスターナンバー
 */
//--------------------------------------------------------------------------------------------
int SSC_GetSafScpMons(FIELDSYS_WORK * fsys)
{
	u8 i;
	BOOL book_get;
	int monsno[ENC_MONS_NUM_NORMAL];
	ENCOUNT_DATA *data;
	//fsysからエンカウントデータを取得
	data = (ENCOUNT_DATA*)EventData_GetEncountData(fsys);

	for(i=0;i<ENC_MONS_NUM_NORMAL;i++){
		monsno[i] = data->NormalEnc[i].MonsterNo;
	}

	book_get = ZukanWork_GetZenkokuZukanFlag(SaveData_GetZukanWork(GameSystem_GetSaveData(fsys)));

	//サファリ特殊枠セット
	SafariEnc_SetSafariEnc(	EncDataSave_GetRandSeed(
								EncDataSave_GetSaveDataPtr(fsys->savedata), ENC_RND_SEED_SAFARI),
							book_get,
							fsys->location->zone_id,
							&monsno[SP_ENC_1], &monsno[SP_ENC_2]);
	//昼夜テーブル差し替え
	EncSet_SetTimeZoneEnc(data, &monsno[TIME_ENC_1], &monsno[TIME_ENC_2]);	
	
	//ＡＧＢスロットテーブル差し替え
	AgbSlotEnc_SetAgbSlotEnc(data, book_get, &monsno[AGB_ENC_1], &monsno[AGB_ENC_2]);
	
	//ランダムで1匹選出
	return monsno[gf_p_rand(ENC_MONS_NUM_NORMAL)];
}

//--------------------------------------------------------------------------------------------
/**
 * 望遠鏡注視点リスト作成
 *
 * @param	inHeapID	ヒープＩＤ
 * @param	fsys		フィールドシステムポインタ
 * 
 * @return	ptr			データポインタ
 */
//--------------------------------------------------------------------------------------------
SSC_SD_PTR SSC_CreateScopePointList(const int inHeapID, FIELDSYS_WORK * fsys)
{
	u8 i;
	SSC_SD_PTR ptr;
	ptr = sys_AllocMemoryLo(inHeapID, sizeof(SCOPE_DATA));
	ptr->fsys = fsys;
	//データをロード
	{
		u8 no;
		SCOPE_VIEWSPOT *spot;
		spot = ArchiveDataLoadMallocLo(ARC_ENCDATA_EX, NARC_encdata_ex_safari_scope_bin, HEAPID_FIELD);
//		spot = sys_LoadFile(HEAPID_FIELD,"data/safari_scope.bin" );
		//ランダムで5箇所取得
		for(i=0;i<SCOPE_DISP_CNT;i++){
			no = gf_p_rand(SPOT_LIST_MAX);
			ptr->Spot[i].X = spot[no].X;
			ptr->Spot[i].Z = spot[no].Z;
//			OS_Printf("xz=%d,%d\n",spot[no].X,spot[no].Z);
		}
		//6つ目は望遠鏡の場所（戻ってくる位置）
		{
			ptr->Spot[SCOPE_DISP_CNT].X = Player_NowGPosXGet( fsys->player );
			ptr->Spot[SCOPE_DISP_CNT].Z = Player_NowGPosZGet( fsys->player );
			ptr->ReturnZoneID = fsys->location->zone_id;
		}
		//データ解放
		sys_FreeMemoryEz(spot);
	}
	
	return ptr;
}

//--------------------------------------------------------------------------------------------
/**
 * 望遠鏡注視点リスト破棄
 *
 * @param	fsys	望遠鏡データポインタ
 * 
 * @return	none	
 */
//--------------------------------------------------------------------------------------------
void SSC_RereaseScopePointList(SSC_SD_PTR ptr)
{
	sys_FreeMemoryEz(ptr);
}

//--------------------------------------------------------------------------------------------
/**
 * ロケーションセット
 *
 * @param	inNo	望遠鏡を見た回数
 * @param	ptr		望遠鏡データポインタ
 * 
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void SSC_SetNextLocation(const u8 inNo, SSC_SD_PTR ptr)
{
	int zone_id;
	int block_x,block_z;

	if (inNo == 0){
		int matrix_id;
		matrix_id = MATRIX_ID_DUN0602;	///サファリ
		block_x = ptr->Spot[inNo].X/32;
		block_z = ptr->Spot[inNo].Z/32;
		zone_id = GetZoneIDFromMatID(matrix_id, block_x, block_z );
	}else if (inNo == SCOPE_DISP_CNT){
		zone_id = ptr->ReturnZoneID;
	}else{
		block_x = ptr->Spot[inNo].X/32;
		block_z = ptr->Spot[inNo].Z/32;
		zone_id = World_GetZoneIDFromMatrixXZ(ptr->fsys->World, block_x, block_z);
	}
	SetLocation(&ptr->Next, zone_id, DOOR_ID_JUMP_CODE, ptr->Spot[inNo].X, ptr->Spot[inNo].Z, DIR_UP);
}

//--------------------------------------------------------------------------------------------
/**
 * ジャンプ
 *
 * @param		event	イベントポインタ
 * @param		ptr		望遠鏡データポインタ
 * @return		none
 */
//--------------------------------------------------------------------------------------------
void SSC_JumpMap(GMEVENT_CONTROL * event, SSC_SD_PTR ptr)
{
	EventCmd_MapChangeByLocation(event, &ptr->Next);
}

//--------------------------------------------------------------------------------------------
/**
 * 次のロー家ションデータのポインタを返す
 *
 * @param		ptr					望遠鏡データポインタ
 * @return		LOCATION_WORK *		ロケーションデータポインタ
 */
//--------------------------------------------------------------------------------------------
LOCATION_WORK *SSC_GetNextLocaton(SSC_SD_PTR ptr)
{
	return &ptr->Next;
}



