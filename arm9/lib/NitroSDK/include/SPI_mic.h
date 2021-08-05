#ifndef NITRO_SPI_MIC_H_
#define NITRO_SPI_MIC_H_

struct MIC_SamplingData
{
    int unk00;
    void *unk04;
    int unk08;
    int unk0c;
    int unk10;
    int unk14;
    int unk18;
};

void MIC_Init(void);
int MIC_StartAutoSampling(struct MIC_SamplingData *data);
int MIC_StopAutoSampling(void);
int MIC_DoSamplingAsync(int param0, int param1, int param2, int param3);

#endif //NITRO_SPI_MIC_H_
