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

  Description:  ���̐e�@���ւ̃|�C���^�𓾂�B

  Arguments:    bssDesc - �e�@���ւ̃|�C���^

  Returns:      const WMBssDesc * - ���̐e�@���ւ̃|�C���^
 *---------------------------------------------------------------------------*/
const WMBssDesc *WPB_GetNextBssDesc(const WMBssDesc *bssDesc);

/*---------------------------------------------------------------------------*
  Name:         WPB_IsValidGGID

  Description:  GGID ���L�����ǂ����𔻒肷��

  Arguments:    bssDesc - �e�@���ւ̃|�C���^

  Returns:      BOOL - GGID ���L���Ȃ� TRUE
 *---------------------------------------------------------------------------*/
BOOL WPB_IsValidGGID(const WMBssDesc *bssDesc);

#ifdef  __cplusplus
}       /* extern "C" */
#endif

#endif /* WPBUTIL_H_ */

/*---------------------------------------------------------------------------*
  End of file
 *---------------------------------------------------------------------------*/
