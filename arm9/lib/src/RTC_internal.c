#include "global.h"
#include "PXI_fifo.h"
#include "RTC_internal.h"

u32 RTCi_ReadRawDateTimeAsync(void)
{
    return RtcSendPxiCommand(16);
}

u32 RTCi_ReadRawDateAsync(void)
{
    return RtcSendPxiCommand(17);
}

u32 RTCi_ReadRawTimeAsync(void)
{
    return RtcSendPxiCommand(18);
}

u32 RTCi_WriteRawStatus2Async(void)
{
    return RtcSendPxiCommand(39);
}

u32 RtcSendPxiCommand(u8 command)
{
    s32 data = command << 8 & 0x7f00;
    if(PXI_SendWordByFifo(PXI_FIFO_TAG_RTC, data, FALSE) >= 0)
        return 1;
    else
        return 0;
}
