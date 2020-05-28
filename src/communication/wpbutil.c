/*---------------------------------------------------------------------------*
  Project:  Wireless PassBy Library
  File:     wpbutil.c

  2005 Ambrella
 *---------------------------------------------------------------------------*/

#include "communication/wpbutil.h"

const WMBssDesc *WPB_GetNextBssDesc(const WMBssDesc *bssDesc)
{
	return (const WMBssDesc *)((const u16 *)bssDesc + bssDesc->length);
}

BOOL WPB_IsValidGGID(const WMBssDesc *bssDesc)
{
	return bssDesc->gameInfoLength >=
		(char *)&bssDesc->gameInfo.ggid - (char *)&bssDesc->gameInfo
			+ sizeof bssDesc->gameInfo.ggid;
}

/*---------------------------------------------------------------------------*
  End of file
 *---------------------------------------------------------------------------*/
