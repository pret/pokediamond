#ifndef POKEDIAMOND_WM_KS_H
#define POKEDIAMOND_WM_KS_H

#include "WM.h"

WMErrCode WM_StartKeySharing(WMKeySetBuf *buf, u16 port);
WMErrCode WM_EndKeySharing(WMKeySetBuf *buf);

#endif //POKEDIAMOND_WM_KS_H
