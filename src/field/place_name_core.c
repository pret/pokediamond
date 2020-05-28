//============================================================================================
/**
 * @file	place_name.c	
 * @bfief	地名表示(常駐部)
 * @author	Nozomu Saito
 * @date	06.07.11
 *
 */
//============================================================================================

#include "common.h"
#include "place_name_core.h"
#include "zonedata.h"
#include "system/fontproc.h"
#include "system/pm_str.h"
#include "msgdata/msg.naix"				//NARC_msg_??_dat
#include "msgdata/msg_place_name.h"
#include "system/buflen.h"

#include "fieldmap_work.h"

//------------------------------------------------------------------
/**
 * @brief	地名の取得
 * @param	inPlaceNameCont	地名構造体へのポインタ
 * @param	inNameID		地名
 * @param	outName			格納バッファ
 * @return	u32				文字列長
 */
//------------------------------------------------------------------
u32 PNC_GetPlaceName(MSGDATA_MANAGER* manager, const int inNameID, STRBUF *outName)
{
	u32 len;
	MSGMAN_GetString(manager , inNameID, outName);
	len = FontProc_GetPrintStrWidth(FONT_SYSTEM,outName,0);
	return len;
}

//------------------------------------------------------------------
/**
 * @brief	ゾーンIDから地名を取得
 *	
 * @param	inZoneID	ゾーンID
 * @param	inHeapID	ヒープID
 * @param	outName		取得地名
 * @return	none
 *
 * ※バッファは必ずBUFLEN_PLACE_NAMEの長さ分確保してください
 */
//------------------------------------------------------------------
void PNC_GetPlaceNameFromZoneID(const int inZoneID, const u32 inHeapID, STRBUF *outName)
{
	int name_id;
	MSGDATA_MANAGER* manager;
	manager = MSGMAN_Create( MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_place_name_dat, inHeapID );
	
	name_id = ZoneData_GetPlaceNameID(inZoneID);
	PNC_GetPlaceName(manager, name_id, outName);

	MSGMAN_Delete(manager);
}
