#ifndef NITRO_RTC_INTERNAL_H_
#define NITRO_RTC_INTERNAL_H_

u32 RtcSendPxiCommand(u8 command);
u32 RTCi_WriteRawStatus2Async(void);
u32 RTCi_ReadRawTimeAsync(void);
u32 RTCi_ReadRawDateAsync(void);
u32 RTCi_ReadRawDateTimeAsync(void);

#endif //NITRO_RTC_INTERNAL_H_
