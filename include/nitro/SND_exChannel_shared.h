#ifndef GUARD_SND_EXCHANNEL_SHARED_H
#define GUARD_SND_EXCHANNEL_SHARED_H

#include "nitro/types.h"

#define SND_ENV_ATTACK 0
#define SND_ENV_DECAY 1
#define SND_ENV_SUSTAIN 2
#define SND_ENV_RELEASE 3

#define SND_CHN_TYPE_PCM 0
#define SND_CHN_TYPE_PSG 1
#define SND_CHN_TYPE_NOISE 2

#define SND_CHN_SYNC_START 0x1
#define SND_CHN_SYNC_STOP 0x2
#define SND_CHN_SYNC_TIMER 0x4
#define SND_CHN_SYNC_VOLUME 0x8
#define SND_CHN_SYNC_PAN 0x10

#define SND_LFO_PITCH 0
#define SND_LFO_VOLUME 1
#define SND_LFO_PAN 2

struct SNDWaveParam
{
    u8 format; // 0x0
    u8 loopEnabled; // 0x1
    u16 samplerate; // 0x2
    u16 timer; // 0x4
    u16 loopStart; // 0x6
    u32 loopLength; // 0x8
}; // size = 0xC

struct SNDLfoParam
{
    u8 target; // 0x0
    u8 speed; // 0x1
    u8 depth; // 0x2
    u8 range; // 0x3
    u16 delay; // 0x4
}; // size = 0x6

struct SNDLfo
{
    struct SNDLfoParam param; // 0x0
    u16 delayCounter; // 0x6
    u16 counter; // 0x8
}; // size = 0xA

struct SNDExChannel;

typedef void (*SNDExChannelCallback)(struct SNDExChannel *chn, int status, void *userData);

struct SNDExChannel
{
    u8 id; // 0x00
    u8 type; // 0x01
    u8 envStatus; // 0x02

    struct
    {
        u8 active : 1;
        u8 start : 1;
        u8 autoSweep : 1;
        u8 syncFlag : 5;
    } flags; // 0x03

    u8 panRange; // 0x04
    u8 rootMidiKey; // 0x05
    s16 userDecay2; // 0x06

    u8 midiKey; // 0x08
    u8 velocity; // 0x09
    s8 initPan; // 0x0A
    s8 userPan; // 0x0B

    s16 userDecay; // 0x0C
    s16 userPitch; // 0x0E

    s32 envAttenuation; // 0x10
    s32 sweepCounter; // 0x14
    s32 sweepLength; // 0x18

    u8 envAttack; // 0x1C
    u8 envSustain; // 0x1D
    u16 envDecay; // 0x1E
    u16 envRelease; // 0x20
    u8 priority; // 0x22
    u8 pan; // 0x23
    u16 volume; // 0x24
    u16 timer; // 0x26

    struct SNDLfo lfo; // 0x28

    s16 sweepPitch; // 0x32

    s32 length; // 0x34

    struct SNDWaveParam waveParam; // 0x38

    union
    {
        const void *waveDataPtr;
        s32 dutyCycle;
    }; // 0x44

    SNDExChannelCallback callback; // 0x48
    void *callbackUserData; // 0x4C

    struct SNDExChannel *channelLLNext; // 0x50
}; // size = 0x54

#endif // GUARD_SND_EXCHANNEL_SHARED_H
