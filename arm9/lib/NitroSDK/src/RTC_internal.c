#include "function_target.h"
#include "PXI_fifo.h"
#include "RTC_internal.h"

static BOOL RtcSendPxiCommand(u8 command);

ARM_FUNC BOOL RTCi_ReadRawDateTimeAsync(void)
{
    return RtcSendPxiCommand(16);
}

ARM_FUNC BOOL RTCi_ReadRawDateAsync(void)
{
    return RtcSendPxiCommand(17);
}

ARM_FUNC BOOL RTCi_ReadRawTimeAsync(void)
{
    return RtcSendPxiCommand(18);
}

ARM_FUNC BOOL RTCi_WriteRawStatus2Async(void)
{
    return RtcSendPxiCommand(39);
}

ARM_FUNC static BOOL RtcSendPxiCommand(u8 command)
{
    s32 data = command << 8 & 0x7f00;
    return PXI_SendWordByFifo(PXI_FIFO_TAG_RTC, (u32)data, FALSE) >= 0;
}
