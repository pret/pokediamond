#ifndef GUARD_SND_SEQ_SHARED_H
#define GUARD_SND_SEQ_SHARED_H

#include "nitro/SND_exChannel_shared.h"

#define SND_TRACK_COUNT_PER_PLAYER 16
#define SND_INVALID_TRACK_INDEX 0xFF

struct SNDBankData;

struct SNDPlayer
{
    struct
    {
        u8 active : 1;
        u8 prepared : 1;
        u8 paused : 1;
    } flags; // 0x0

    u8 playerId; // 0x1
    u8 unk_2[2]; // 0x2

    u8 prio; // 0x4
    u8 volume; // 0x5
    s16 extFader; // 0x6

    u8 tracks[SND_TRACK_COUNT_PER_PLAYER]; // 0x8

    u16 tempo; // 0x18
    u16 tempoRatio; // 0x1A
    u16 tempoCounter; // 0x1C
    u8 unk_1E[2]; // 0x1E

    struct SNDBankData *bank; // 0x20
}; // size = 0x24

#define SND_TRACK_MAX_CALL 3

struct SNDTrack
{
    struct
    {
        u8 active : 1;
        u8 noteWait : 1;
        u8 muted : 1;
        u8 tie : 1;
        u8 noteFinishWait : 1;
        u8 portamento : 1;
        u8 cmp : 1; // ???
        u8 channelMask : 1;
    } flags; // 0x00

    u8 panRange; // 0x01
    u16 program; // 0x02

    u8 volume; // 0x04
    u8 expression; // 0x05
    s8 pitchBend; // 0x06
    u8 bendRange; // 0x07

    s8 pan; // 0x08
    s8 extPan; // 0x09
    s16 extFader; // 0x0A
    s16 extPitch; // 0x0C
    u8 envAttack; // 0x0E
    u8 envDecay; // 0x0F
    u8 envSustain; // 0x10
    u8 envRelease; // 0x11
    u8 priority; // 0x12
    s8 transpose; // 0x13

    u8 portamentoKey; // 0x14
    u8 portamentoTime; // 0x15
    s16 sweepPitch; // 0x16

    struct SNDLfoParam mod; // 0x18
    u16 channelMask; // 0x1E

    s32 wait; // 0x20

    const u8 *base; // 0x24
    const u8 *cur; // 0x28
    const u8 *posCallStack[SND_TRACK_MAX_CALL]; // 0x2C
    u8 loopCount[SND_TRACK_MAX_CALL]; // 0x38
    u8 callStackDepth; // 0x3B

    struct SNDExChannel *channelLLHead; // 0x3C
}; // size = 0x40

#endif // GUARD_SND_SEQ_SHARED_H
