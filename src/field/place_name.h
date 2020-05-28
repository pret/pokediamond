//============================================================================================
/**
 * @file	place_name.h
 * @bfief	’n–¼•\Ž¦
 * @author	Nozomu Saito
 * @date	01.03.29
 *
 */
//============================================================================================
#ifndef _PLACE_NAME_H_
#define _PLACE_NAME_H_

#include "msg_print.h"
#include "field_common.h"
#include "place_name_core.h"

typedef struct PLACE_NAME_CONT_tag * PNC_PTR;

extern PNC_PTR	AllocPlaceNameCont(GF_BGL_INI *bgl);
extern void FreePlaceNameCont(PNC_PTR outPlaceNameCont);
extern void PlaceNameRequest(PNC_PTR ioPlaceName, const int inPlaceID);
extern void PlaceNameRequestByFsys(FIELDSYS_WORK * fsys);

extern void StopPlaceName(PNC_PTR outPlaceNameCont);

///extern void GetPlaceNameFromZoneID(const int inZoneID, const u32 inHeapID, STRBUF *outName);

#endif //_PLACE_NAME_H_
