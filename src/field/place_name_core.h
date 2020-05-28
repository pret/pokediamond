//============================================================================================
/**
 * @file	place_name_core.h
 * @bfief	ínñºï\é¶(èÌíìïî)
 * @author	Nozomu Saito
 * @date	06.07.11
 *
 */
//============================================================================================
#ifndef _PLACE_NAME_CORE_H_
#define _PLACE_NAME_CORE_H_

#include "system/msgdata.h"

extern void PNC_GetPlaceNameFromZoneID(const int inZoneID, const u32 inHeapID, STRBUF *outName);
extern u32 PNC_GetPlaceName(MSGDATA_MANAGER* manager, const int inNameID, STRBUF *outName);

#endif	//_PLACE_NAME_CORE_H_
