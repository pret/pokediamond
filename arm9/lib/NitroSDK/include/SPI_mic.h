#ifndef NITRO_SPI_MIC_H_
#define NITRO_SPI_MIC_H_

#include "global.h"


struct MIC_SamplingData
{
    u32 unk00;
    u8 *unk04;
    u32 unk08;
    u32 unk0c;
    u32 unk10;
    u32 unk14;
    u32 unk18;
};

void MIC_Init(void);
u32 MIC_StartAutoSampling(struct MIC_SamplingData *data);
u32 MIC_StopAutoSampling();
u32 MIC_DoSamplingAsync(u32 param0, u32 param1, u32 param2, u32 param3);

#endif //NITRO_SPI_MIC_H_
