#ifndef NITRO_TP_H_
#define NITRO_TP_H_

#define     TP_TOUCH_OFF                0       // Not being touched
#define     TP_TOUCH_ON                 1       // Being touched

#define     TP_VALIDITY_VALID           0       // Valid
#define     TP_VALIDITY_INVALID_X       1       // Data with invalid X coordinate
#define     TP_VALIDITY_INVALID_Y       2       // Data with invalid Y coordinate
#define     TP_VALIDITY_INVALID_XY      (TP_VALIDITY_INVALID_X | TP_VALIDITY_INVALID_Y) // Data with invalid X and Y coordinates

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
