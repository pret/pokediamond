#include "SND_capture.h"

#include "registers.h"

enum SNDLoop {
    SND_CAP_LOOP = 0, SND_CAP_ONESHOT = 1
};

void SND_SetupCapture(int idx, int format, void *captureData, int size, BOOL loop, int capCtrlSrc, int capCtrlDst) {
    int off = idx * 8;

    reg_SNDCAPxCNT(idx) = (u8)((format << 3) | ((loop ? SND_CAP_LOOP : SND_CAP_ONESHOT) << 2) | (capCtrlSrc << 1) | capCtrlDst);
    *(vu32 *)(0x4000510 + off) = (u32)captureData;
    *(vu16 *)(0x4000514 + off) = (u16)size;
}

BOOL SND_IsCaptureActive(int idx) {
    return (reg_SNDCAPxCNT(idx) & 0x80) != 0;
}
