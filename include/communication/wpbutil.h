/*---------------------------------------------------------------------------*
  Project:  Wireless PassBy Library - include
  File:     wpbutil.h

  2005 Ambrella
 *---------------------------------------------------------------------------*/

#ifndef WPBUTIL_H_
#define WPBUTIL_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <nitro/wm.h>

/*---------------------------------------------------------------------------*
  Name:         WPB_GetNextBssDesc

  Description:  次の親機情報へのポインタを得る。

  Arguments:    bssDesc - 親機情報へのポインタ

  Returns:      const WMBssDesc * - 次の親機情報へのポインタ
 *---------------------------------------------------------------------------*/
const WMBssDesc *WPB_GetNextBssDesc(const WMBssDesc *bssDesc);

/*---------------------------------------------------------------------------*
  Name:         WPB_IsValidGGID

  Description:  GGID が有効かどうかを判定する

  Arguments:    bssDesc - 親機情報へのポインタ

  Returns:      BOOL - GGID が有効なら TRUE
 *---------------------------------------------------------------------------*/
BOOL WPB_IsValidGGID(const WMBssDesc *bssDesc);

#ifdef  __cplusplus
}       /* extern "C" */
#endif

#endif /* WPBUTIL_H_ */

/*---------------------------------------------------------------------------*
  End of file
 *---------------------------------------------------------------------------*/
