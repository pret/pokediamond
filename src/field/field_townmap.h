//============================================================================================
/**
 * @file	field_townmap.h
 * @brief	タウンマップ関連ヘッダ
 * @author	tamada GAME FREAK inc.
 * @date	2005.10.25
 */
//============================================================================================

#ifndef	__FIELD_TOWNMAP_H__
#define	__FIELD_TOWNMAP_H__

#include "fieldsys.h"
#include "zonedata.h"
#include "situation_local.h"

static inline void FLDTOWNMAP_GetGridXZ(FIELDSYS_WORK * fsys, int * x, int *z)
{
	SITUATION * sit = SaveData_GetSituation(fsys->savedata);
	LOCATION_WORK * escape = Situation_GetEscapeLocation(sit);

	if (ZoneData_IsSinouField(fsys->location->zone_id)) {
		*x = fsys->location->grid_x;
		*z = fsys->location->grid_z;
	} else {
		*x = escape->grid_x;
		*z = escape->grid_z;
	}
}

static inline void FLDTOWNMAP_GetBlockXZ(FIELDSYS_WORK * fsys, int * x, int * z)
{
	FLDTOWNMAP_GetGridXZ(fsys, x, z);
	*x /= 32;
	*z /= 32;
}

#endif	__FIELD_TOWNMAP_H__
