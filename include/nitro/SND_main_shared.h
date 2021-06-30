/*
 * NOTE:
 * This file is shared between ARM9 and ARM7
 * DO NOT PUT PROC SPECIFIC CODE IN HERE
 * Thank You!
 */

/*
 * DO NOT INCLUDE THIS FILE DIRECTLY
 * Include SND_main.h from the specific proc's lib
 */

#ifndef POKEDIAMOND_SND_MAIN_SHARED_H
#define POKEDIAMOND_SND_MAIN_SHARED_H

struct SNDWaveParam {
    u8 format;      // 0x0
    u8 loopEnabled; // 0x1
    u16 samplerate; // 0x2
    u16 timer;      // 0x4
    u16 loopStart;  // 0x6
    u32 loopLength; // 0x8
}; // size = 0xC

struct SNDLfoParam {
    u8 target;  // 0x0
    u8 speed;   // 0x1
    u8 depth;   // 0x2
    u8 range;   // 0x3
    u16 delay;  // 0x4
}; // size = 0x6

struct SNDLfo {
    struct SNDLfoParam param;   // 0x0
    u16 delayCounter;           // 0x6
    u16 counter;                // 0x8
}; // size = 0xA

struct SNDExChannel {
    u8 id;              // 0x00
    u8 type;            // 0x01
    u8 envStatus;       // 0x02

    struct {
        u8 active : 1;
        u8 start : 1;
        u8 autoSweep : 1;
        u8 syncFlag : 5;
    } flags;            // 0x03

    u8 panRange;        // 0x04
    u8 rootMidiKey;     // 0x05
    s16 userDecay2;     // 0x06

    u8 midiKey;         // 0x08
    u8 velocity;        // 0x09
    s8 initPan;         // 0x0A
    s8 userPan;         // 0x0B

    s16 userDecay;      // 0x0C
    s16 userPitch;      // 0x0E

    s32 envAttenuation; // 0x10
    s32 sweepCounter;   // 0x14
    s32 sweepLength;    // 0x18

    u8 envAttack;       // 0x1C
    u8 envSustain;      // 0x1D
    u16 envDecay;       // 0x1E
    u16 envRelease;     // 0x20
    u8 priority;        // 0x22
    u8 pan;             // 0x23
    u16 volume;         // 0x24
    u16 timer;          // 0x26

    struct SNDLfo lfo;  // 0x28

    s16 sweepPitch;     // 0x32

    s32 length;         // 0x34

    struct SNDWaveParam waveParam;  // 0x38

    union {
        const void *waveDataPtr;
        s32 dutyCycle;
    };                  // 0x44

    void (*callback)(struct SNDExChannel *chn, u32 status, void *userData); // 0x48
    void *callbackUserData; // 0x4C

    struct SNDExChannel *channelLLNext; // 0x50
};  // size = 0x54

#define SND_TRACK_COUNT_PER_PLAYER 16
#define SND_INVALID_TRACK_INDEX 0xFF

struct SNDBankData;

struct SNDPlayer {
    struct {
        u8 active : 1;
        u8 prepared : 1;
        u8 paused : 1;
    } flags;            // 0x0

    u8 playerId;        // 0x1
    u8 unk_2[2];        // 0x2

    u8 prio;            // 0x4
    u8 volume;          // 0x5
    s16 extFader;       // 0x6

    u8 tracks[SND_TRACK_COUNT_PER_PLAYER];  // 0x8

    u16 tempo;          // 0x18
    u16 tempoRatio;     // 0x1A
    u16 tempoCounter;   // 0x1C
    u8 unk_1E[2];       // 0x1E

    struct SNDBankData *bank;   // 0x20
};  // size = 0x24

#define SND_TRACK_MAX_CALL 3

struct SNDTrack {
    struct {
        u8 active : 1;
        u8 noteWait : 1;
        u8 muted : 1;
        u8 tie : 1;
        u8 noteFinishWait : 1;
        u8 portamento : 1;
        u8 cmp : 1; // ???
        u8 channelMask : 1;
    } flags;        // 0x00

    u8 panRange;    // 0x01
    u16 program;    // 0x02

    u8 volume;      // 0x04
    u8 expression;  // 0x05
    s8 pitchBend;   // 0x06
    u8 bendRange;   // 0x07

    s8 pan;         // 0x08
    s8 extPan;      // 0x09
    s16 extFader;   // 0x0A
    s16 extPitch;   // 0x0C
    u8 envAttack;   // 0x0E
    u8 envDecay;    // 0x0F
    u8 envSustain;  // 0x10
    u8 envRelease;  // 0x11
    u8 priority;    // 0x12
    s8 transpose;   // 0x13

    u8 portamentoKey;           // 0x14
    u8 portamentoTime;          // 0x15
    s16 sweepPitch;             // 0x16

    struct SNDLfoParam mod;     // 0x18
    u16 channelMask;            // 0x1E

    s32 wait;                   // 0x20

    const u8 *trackDataStart;   // 0x24
    const u8 *trackDataPos;     // 0x28
    const u8 *posCallStack[SND_TRACK_MAX_CALL]; // 0x34
    u8 loopCount[SND_TRACK_MAX_CALL];           // 0x38
    u8 callStackDepth;                          // 0x3B

    struct SNDExChannel *channelLLHead; // 0x3C
};  // size = 0x40
 
 #endif //POKEDIAMOND_SND_MAIN_SHARED_H
 
