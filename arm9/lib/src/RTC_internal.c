#include "global.h"
#include "PXI_fifo.h"
#include "RTC_internal.h"

BOOL RTCi_ReadRawDateTimeAsync(void)
{
    return RtcSendPxiCommand(16);
}

BOOL RTCi_ReadRawDateAsync(void)
{
    return RtcSendPxiCommand(17);
}

BOOL RTCi_ReadRawTimeAsync(void)
{
    return RtcSendPxiCommand(18);
}

BOOL RTCi_WriteRawStatus2Async(void)
{
    return RtcSendPxiCommand(39);
}

BOOL RtcSendPxiCommand(u8 command)
{
    s32 data = command << 8 & 0x7f00;
    return PXI_SendWordByFifo(PXI_FIFO_TAG_RTC, data, FALSE) >= 0;
}
