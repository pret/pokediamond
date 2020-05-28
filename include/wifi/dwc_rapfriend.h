#ifndef __DWC_RAP_FRIEND_H__
#define  __DWC_RAP_FRIEND_H__

#include <dwc.h>

#include "savedata/savedata.h"
#include "savedata/wifilist.h"

// すでに、同じデータがリスト上にある。この場合は何もする必要なし。
#define DWCFRIEND_INLIST 0
// すでに、同じデータがリスト上にあるが、上書きすることが望ましい場合。
#define DWCFRIEND_OVERWRITE 1
// 同じデータはリスト上にない。
#define DWCFRIEND_NODATA 2
// データが正しくない。
#define DWCFRIEND_INVALID 3

//==============================================================================
/**
 * すでに同じ人が登録されていないか。
 * @param   pSaveData フレンド関係がはいっているセーブデータ
 * @param   index 同じデータが見つかったときの、その場所。
 * @param         見つからない場合は空いているところを返す
 * @param         どこも空いていない場合は、-1 
 * @retval  DWCFRIEND_INLIST … すでに、同じデータがリスト上にある。この場合は何もする必要なし。
 * @retval  DWCFRIEND_OVERWRITE … すでに、同じデータがリスト上にあるが、上書きすることが望ましい場合。
 * @retval  DWCFRIEND_NODATA … 同じデータはリスト上にない。
 * @retval  DWCFRIEND_INVALID … 受け取ったDWCFriendDataが異常。
 */
//==============================================================================
extern int dwc_checkfriendByToken(SAVEDATA* pSaveData, DWCFriendData *data, int *index);

//==============================================================================
/**
 * すでに同じ人が登録されていないか。
 * @param   pSaveData フレンド関係がはいっているセーブデータ
 * @param   index 同じデータが見つかったときの、その場所。
 * @param         見つからない場合は空いているところを返す
 * @param         どこも空いていない場合は、-1 
 * @retval  DWCFRIEND_INLIST … すでに、同じデータがリスト上にある。
 * @retval  DWCFRIEND_NODATA … 同じデータはリスト上にない。
 * @retval  DWCFRIEND_INVALID … 受け取ったfriend_keyaが正しくない。
 */
//==============================================================================
extern int dwc_checkFriendCodeByToken(SAVEDATA* pSaveData, u64 friend_key, int *index);


extern BOOL dwc_friendAutoInputCheck( SAVEDATA* pSaveData, int* netIDList,
                                      int heapID);

extern void dwc_friendWrite(SAVEDATA* pSaveData, int netID, int addListIndex,
                            int heapID, int overWrite);


#endif
