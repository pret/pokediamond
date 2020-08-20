//
// Created by Scott Norton on 8/20/20.
//

#ifndef NITRO_TP_H_
#define NITRO_TP_H_

// Touch panel input structure
typedef struct
{
    u16 x;        // x coordinate ( 0 - 4095 )
    u16 y;        // y coordinate ( 0 - 4095 )
    u16 touch;    // Touch yes/no
    u16 validity; // Valid yes/no
}
TPData;

typedef struct NvTpData
{
    s16 x0;       // X origin coordinate
    s16 y0;       // Y origin coordinate
    s16 xDotSize; // X dot size
    s16 yDotSize; // Y dot size
}
TPCalibrateParam;

void TP_Init(void);
void TP_SetCalibrateParam(const TPCalibrateParam *param);
BOOL TP_GetUserInfo(TPCalibrateParam *calibrate);
void TP_RequestSamplingAsync(void);
u32 TP_WaitRawResult(TPData *result);
void TP_GetLatestRawPointInAuto(TPData *result);
void TP_GetCalibratedPoint(TPData *disp, const TPData *raw);

static inline u32 TP_RequestRawSampling(TPData *result)
{
    TP_RequestSamplingAsync();
    return TP_WaitRawResult(result);
}

#endif //NITRO_TP_H_
