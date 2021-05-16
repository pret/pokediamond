#ifndef NITRO_RTC_INTERNAL_H_
#define NITRO_RTC_INTERNAL_H_

#include "nitro/types.h"

BOOL RTCi_WriteRawStatus2Async(void);
BOOL RTCi_ReadRawTimeAsync(void);
BOOL RTCi_ReadRawDateAsync(void);
BOOL RTCi_ReadRawDateTimeAsync(void);

#endif //NITRO_RTC_INTERNAL_H_
