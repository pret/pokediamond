#include "WM_ks.h"
#include "code32.h"

extern WMErrCode WM_StartDataSharing(WMKeySetBuf *buf, u16 port, u16 aidBitmap, u16 dataLength, BOOL doubleMode);
extern WMErrCode WM_EndDataSharing(WMKeySetBuf *buf);

WMErrCode WM_StartKeySharing(WMKeySetBuf *buf, u16 port)
{
    return WM_StartDataSharing(buf, port, 0xffff, 2, TRUE);
}

WMErrCode WM_EndKeySharing(WMKeySetBuf *buf)
{
    return WM_EndDataSharing(buf);
}
