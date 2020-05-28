//============================================================================================
/**
 * @file	place_name.c	
 * @bfief	�n���\��(�풓��)
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
 * @brief	�n���̎擾
 * @param	inPlaceNameCont	�n���\���̂ւ̃|�C���^
 * @param	inNameID		�n��
 * @param	outName			�i�[�o�b�t�@
 * @return	u32				������
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
 * @brief	�]�[��ID����n�����擾
 *	
 * @param	inZoneID	�]�[��ID
 * @param	inHeapID	�q�[�vID
 * @param	outName		�擾�n��
 * @return	none
 *
 * ���o�b�t�@�͕K��BUFLEN_PLACE_NAME�̒������m�ۂ��Ă�������
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
