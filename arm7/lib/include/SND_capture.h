#ifndef GUARD_SND_CAPTURE_H
#define GUARD_SND_CAPTURE_H

#include "nitro/types.h"

void SND_SetupCapture(
    int idx, int format, void *captureData, int size, BOOL loop, int capCtrlSrc, int capCtrlDst);
BOOL SND_IsCaptureActive(int idx);

#endif // GUARD_SND_CAPTURE_H
