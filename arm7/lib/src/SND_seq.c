#include "SND_seq.h"

#include "SND_main.h"
#include "SND_work.h"
#include "SND_util.h"
#include "SND_lfo.h"
#include "SND_exChannel.h"
#include "SND_bank.h"

#define SND_TIMER_RATE 240

#define SND_TRACK_MUTE_MODE_UNMUTE 0
#define SND_TRACK_MUTE_MODE_MUTE 1
#define SND_TRACK_MUTE_MODE_MUTE_RELEASE 2
#define SND_TRACK_MUTE_MODE_MUTE_STOP 3

enum SNDSeqProc {
    SND_PROC_SKIP_NOTES = 0,
    SND_PROC_PLAY_NOTES = 1,
};

enum SNDSeqVal {
    SND_SEQ_VAL_U8  = 0,
    SND_SEQ_VAL_U16 = 1,
    SND_SEQ_VAL_VLV = 2,
    SND_SEQ_VAL_RAN = 3,
    SND_SEQ_VAL_VAR = 4,
};

static struct {
    const u8 *begin;
    const u8 *end;
    union {
        u8 buf[16];
        u32 buf32[4];
    };
} sSeqCache;
static int sPrintEnabled;

static void PlayerSeqMain(struct SNDPlayer *player);
static void PlayerUpdateChannel(struct SNDPlayer *player);
static void PlayerStop(struct SNDPlayer *player);
static void PlayerInit(struct SNDPlayer *player, struct SNDBankData *bank);
static int AllocateTrack(void);
static void TrackInit(struct SNDTrack *track);
static void TrackStart(struct SNDTrack *track, const void *seq, u32 offset);
static void SeqCacheFetch(const u8 *addr);
static u8 SeqReadByte(const u8 *addr);
static u16 TrackReadU16(struct SNDTrack *track);
static struct SNDTrack *PlayerGetTrack(struct SNDPlayer *player, int track);
static void TrackReleaseChannels(struct SNDTrack *track, struct SNDPlayer *player, int release);
static void TrackFreeChannels(struct SNDTrack *track);
static BOOL PlayerStepTicks(struct SNDPlayer *player, u32 ticks);
static void TrackMute(struct SNDTrack *track, struct SNDPlayer *player, int muteMode);
static s16 *PlayerGetVariablePointer(const struct SNDPlayer *player, int var);
static void TrackUpdateChannel(struct SNDTrack *track, struct SNDPlayer *player, int release);

void SND_SeqInit(void) {
    for (int i = 0; i < SND_PLAYER_COUNT; i++) {
        struct SNDPlayer *ply = &SNDi_Work.players[i];

        ply->flags.active = FALSE;
        ply->playerId = (u8)i;
    }

    for (int i = 0; i < SND_TRACK_COUNT; i++) {
        struct SNDTrack *trk = &SNDi_Work.tracks[i];

        trk->flags.active = FALSE;
    }
}

void SND_SeqMain(BOOL step) {
    struct SNDPlayer *ply;
    int i;
    u32 playerStatus = 0;

    for (i = 0; i < SND_PLAYER_COUNT; i++) {
        ply = &SNDi_Work.players[i];

        if (!ply->flags.active)
            continue;
        
        if (ply->flags.prepared) {
            if (step && !ply->flags.paused)
                PlayerSeqMain(ply);
            PlayerUpdateChannel(ply);
        }

        if (ply->flags.active)
            playerStatus |= 1 << i;
    }

    if (SNDi_SharedWork)
        SNDi_SharedWork->playerStatus = playerStatus;
}

void SND_PrepareSeq(int player, const void *seq, u32 offset, struct SNDBankData *bankData) {
    struct SNDPlayer *ply = &SNDi_Work.players[player];

    if (ply->flags.active)
        PlayerStop(ply);
    
    PlayerInit(ply, bankData);

    int allocTrkIdx = AllocateTrack();

    if (allocTrkIdx < 0)
        return;
    
    struct SNDTrack *trk = &SNDi_Work.tracks[allocTrkIdx];
    TrackInit(trk);
    TrackStart(trk, seq, offset);
    ply->tracks[0] = (u8)allocTrkIdx;
    SeqCacheFetch(trk->cur);

    u8 cmd = SeqReadByte(trk->cur);

    trk->cur++;

    if (cmd != 0xFE) {
        trk->cur--;
    } else {
        int track;
        u16 trackMask;

        for (trackMask = (u16)(TrackReadU16(trk) >> 1), track = 1; trackMask != 0; track++, trackMask >>= 1) {
            if (trackMask & 1) {
                allocTrkIdx = AllocateTrack();
                if (allocTrkIdx < 0)
                    break;
                TrackInit(&SNDi_Work.tracks[allocTrkIdx]);
                ply->tracks[track] = (u8)allocTrkIdx;
            }
        }
    }

    ply->flags.active = TRUE;
    ply->flags.prepared = FALSE;

    if (SNDi_SharedWork) {
        SNDi_SharedWork->playerStatus |= 1 << player;
    }
}

void SND_StartPreparedSeq(int player) {
    SNDi_Work.players[player].flags.prepared = TRUE;
}

void SND_StartSeq(int player, const void *seq, u32 offset, struct SNDBankData *bankData) {
    SND_PrepareSeq(player, seq, offset, bankData);
    SND_StartPreparedSeq(player);
}

void SND_StopSeq(int player) {
    struct SNDPlayer *ply = &SNDi_Work.players[player];

    if (ply->flags.active) {
        PlayerStop(ply);

        if (SNDi_SharedWork) {
            SNDi_SharedWork->playerStatus &= ~(1 << player);
        }
    }
}

void SND_PauseSeq(int player, BOOL flag) {
    struct SNDPlayer *ply = &SNDi_Work.players[player];

    ply->flags.paused = flag;

    if (flag) {
        for (int i = 0; i < SND_TRACK_COUNT_PER_PLAYER; i++) {
            struct SNDTrack *trk = PlayerGetTrack(ply, i);

            if (trk) {
                TrackReleaseChannels(trk, ply, 127);
                TrackFreeChannels(trk);
            }
        }
    }
}

void SND_SkipSeq(int player, u32 ticks) {
    struct SNDPlayer *ply = &SNDi_Work.players[player];

    for (int i = 0; i < SND_TRACK_COUNT_PER_PLAYER; i++) {
        struct SNDTrack *trk = PlayerGetTrack(ply, i);

        if (trk) {
            TrackReleaseChannels(trk, ply, 127);
            TrackFreeChannels(trk);
        }
    }

    SND_StopIntervalTimer();

    u32 i;
    for (i = 0; i < ticks; i++) {
        if (PlayerStepTicks(ply, 0)) {
            PlayerStop(ply);
            break;
        }
    }

    SND_StartIntervalTimer();

    if (SNDi_SharedWork) {
        SNDi_SharedWork->players[ply->playerId].tickCounter += i;
    }
}

void SND_SetTrackMute(int player, u32 trackMask, int muteMode) {
    struct SNDPlayer *ply = &SNDi_Work.players[player];

    for (int i = 0; i < SND_TRACK_COUNT_PER_PLAYER && trackMask != 0; i++, trackMask >>= 1) {
        if (trackMask & 1) {
            struct SNDTrack *trk = PlayerGetTrack(ply, i);
            
            if (trk) {
                TrackMute(trk, ply, muteMode);
            }
        }
    }
}

void SND_SetTrackAllocatableChannel(int player, u32 trackMask, u32 channelMask) {
    struct SNDPlayer *ply = &SNDi_Work.players[player];

    for (int i = 0; i < SND_TRACK_COUNT_PER_PLAYER && trackMask != 0; i++, trackMask >>= 1) {
        if (trackMask & 1) {
            struct SNDTrack *trk = PlayerGetTrack(ply, i);

            if (trk) {
                trk->channelMask = (u16)channelMask;
                trk->flags.channelMask = TRUE;
            }
        }
    }
}

void SND_InvalidateSeq(const void *start, const void *end) {
    struct SNDPlayer *ply;
    struct SNDTrack *trk;
    int i;
    int j;

    for (i = 0; i < SND_PLAYER_COUNT; i++) {
        ply = &SNDi_Work.players[i];

        if (!ply->flags.active)
            continue;
        
        for (j = 0; j < SND_TRACK_COUNT_PER_PLAYER; j++) {
            trk = PlayerGetTrack(ply, j);

            if (!trk)
                continue;
            
            if (start <= trk->cur && trk->cur <= end) {
                PlayerStop(ply);
                break;
            }
        }
    }
}

void SND_InvalidateBank(const void *start, const void *end) {
    for (int i = 0; i < SND_PLAYER_COUNT; i++) {
        struct SNDPlayer *ply = &SNDi_Work.players[i];

        if (ply->flags.active && start <= ply->bank && ply->bank <= end)
            PlayerStop(ply);
    }
}

void SNDi_SetPlayerParam(int player, u32 offset, u32 data, int size) {
    struct SNDPlayer *ply = &SNDi_Work.players[player];

    switch (size) {
    case 1:
        *(u8 *)((u8 *)ply + offset) = (u8)data;
        break;
    case 2:
        *(u16 *)((u8 *)ply + offset) = (u16)data;
        break;
    case 4:
        *(u32 *)((u8 *)ply + offset) = (u32)data;
        break;
    }
}

void SNDi_SetTrackParam(int player, u32 trackMask, u32 offset, u32 data, int size) {
    struct SNDPlayer *ply = &SNDi_Work.players[player];

    for (int i = 0; i < SND_TRACK_COUNT_PER_PLAYER && trackMask != 0; i++, trackMask >>= 1) {
        if (!(trackMask & 1))
            continue;
        
        struct SNDTrack *trk = PlayerGetTrack(ply, i);

        if (!trk)
            continue;

        switch (size) {
        case 1:
            *(u8 *)((u8 *)trk + offset) = (u8)data;
            break;
        case 2:
            *(u16 *)((u8 *)trk + offset) = (u16)data;
            break;
        case 4:
            *(u32 *)((u8 *)trk + offset) = (u32)data;
            break;
        }
    }
}

static void SeqCacheFetch(const u8 *addr) {
    addr = (const u8 *)((u32)addr & ~3);
    sSeqCache.begin = addr;
    sSeqCache.end = sSeqCache.begin + 16;

    const u32 *src = (const u32 *)addr;

    sSeqCache.buf32[0] = src[0];
    sSeqCache.buf32[1] = src[1];
    sSeqCache.buf32[2] = src[2];
    sSeqCache.buf32[3] = src[3];
}

static u8 SeqReadByte(const u8 *addr) {
    if (addr < sSeqCache.begin || addr >= sSeqCache.end)
        SeqCacheFetch(addr);
    
    return sSeqCache.buf[(u32)addr - (u32)sSeqCache.begin];
}

static inline u8 TrackReadU8(struct SNDTrack *track) {
    u8 retval = SeqReadByte(track->cur);
    track->cur++;
    return retval;
}

static u16 TrackReadU16(struct SNDTrack *track) {
    int retval;

    retval = TrackReadU8(track);
    retval |= TrackReadU8(track) << 8;

    return (u16)retval;
}

static u32 TrackReadU24(struct SNDTrack *track) {
    u32 retval;

    retval = TrackReadU8(track);
    retval |= TrackReadU8(track) << 8;
    retval |= TrackReadU8(track) << 16;

    return retval;
}

static int TrackReadVLV(struct SNDTrack *track) {
    int retval = 0;
    int b;

    do {
        b = TrackReadU8(track);
        retval = (retval << 7) | (b & 0x7F);
    } while(b & 0x80);

    return retval;
}

static int TrackParseValue(struct SNDTrack *track, struct SNDPlayer *player, int valueType) {
    int retval;
    int hi;
    int lo;
    int ran;
    s16 *var;

    // BUG: undefined behavior if invalid valueType is passed (uninitialized return value)

    switch (valueType) {
    case SND_SEQ_VAL_U8:
        retval = TrackReadU8(track);
        break;
    case SND_SEQ_VAL_U16:
        retval = TrackReadU16(track);
        break;
    case SND_SEQ_VAL_VLV:
        retval = TrackReadVLV(track);
        break;
    case SND_SEQ_VAL_VAR:
        var = PlayerGetVariablePointer(player, TrackReadU8(track));
        if (var)
            retval = *var;
        break;
    case SND_SEQ_VAL_RAN:
        lo = TrackReadU16(track) << 16;
        hi = (s16)TrackReadU16(track);
        ran = SND_CalcRandom();
        retval = hi - (lo >> 16);
        retval += 1;
        retval = (ran * retval) >> 16;
        retval += lo >> 16;
        break;
    }
    
    return retval;
}

static void TrackInit(struct SNDTrack *track) {
    track->base = NULL;
    track->cur = NULL;

    track->flags.noteWait = TRUE;
    track->flags.muted = FALSE;
    track->flags.tie = FALSE;
    track->flags.noteFinishWait = FALSE;
    track->flags.portamento = FALSE;
    track->flags.cmp = TRUE;
    track->flags.channelMask = FALSE;

    track->callStackDepth = 0;
    track->program = 0;
    track->priority = 64;
    track->volume = 127;
    track->expression = 127;
    track->extFader = 0;
    track->pan = 0;
    track->extPan = 0;
    track->pitchBend = 0;
    track->extPitch = 0;
    track->envAttack = 255;
    track->envDecay = 255;
    track->envSustain = 255;
    track->envRelease = 255;
    track->panRange = 127;
    track->bendRange = 2;
    track->portamentoKey = 60;
    track->portamentoTime = 0;
    track->sweepPitch = 0;
    track->transpose = 0;
    track->channelMask = 0xFFFF;
    SND_InitLfoParam(&track->mod);
    track->wait = 0;
    track->channelLLHead = NULL;
}

static void TrackStart(struct SNDTrack *track, const void *seq, u32 offset) {
    track->base = (const u8 *)seq;
    track->cur = &track->base[offset];
}

static void PlayerInit(struct SNDPlayer *player, struct SNDBankData *bank) {
    player->flags.paused = FALSE;
    player->bank = bank;
    player->tempo = 120;
    player->tempoRatio = 256;
    player->tempoCounter = SND_TIMER_RATE;
    player->volume = 0x7F;
    player->extFader = 0;
    player->prio = 64;

    for (int i = 0; i < SND_TRACK_COUNT_PER_PLAYER; i++) {
        player->tracks[i] = 0xFF;
    }

    if (SNDi_SharedWork) {
        SNDi_SharedWork->players[player->playerId].tickCounter = 0;

        for (int i = 0; i < SND_TRACK_COUNT_PER_PLAYER; i++) {
            SNDi_SharedWork->players[player->playerId].localVars[i] = -1;
        }
    }
}

static void TrackReleaseChannels(struct SNDTrack *track, struct SNDPlayer *player, int release) {
    TrackUpdateChannel(track, player, 0);

    for (struct SNDExChannel *chn = track->channelLLHead; chn; chn = chn->channelLLNext) {
        if (SND_IsExChannelActive(chn)) {
            if (release >= 0)
                SND_SetExChannelRelease(chn, release & 0xFF);
            chn->priority = 1;
            SND_ReleaseExChannel(chn);
        }
    }
}

static void TrackFreeChannels(struct SNDTrack *track) {
    for (struct SNDExChannel *chn = track->channelLLHead; chn; chn = chn->channelLLNext) {
        SND_FreeExChannel(chn);
    }

    track->channelLLHead = NULL;
}

static void PlayerSeqMain(struct SNDPlayer *player) {
    int ticks = 0;
    int tempoInc;
    int i;

    while (player->tempoCounter >= SND_TIMER_RATE) {
        player->tempoCounter -= SND_TIMER_RATE;
        ticks++;
    }

    for (i = 0; i < ticks; i++) {
        if (PlayerStepTicks(player, SND_PROC_PLAY_NOTES)) {
            PlayerStop(player);
            break;
        }
    }

    if (SNDi_SharedWork) {
        SNDi_SharedWork->players[player->playerId].tickCounter += i;
    }

    tempoInc = player->tempo;
    tempoInc *= player->tempoRatio;
    tempoInc >>= 8;

    player->tempoCounter += tempoInc;
}

static struct SNDTrack *PlayerGetTrack(struct SNDPlayer *player, int track) {
    if (track > (SND_TRACK_COUNT_PER_PLAYER - 1))
        return NULL;
    
    if (player->tracks[track] == 0xFF)
        return NULL;
    
    return &SNDi_Work.tracks[player->tracks[track]];
}

static void TrackStop(struct SNDTrack *track, struct SNDPlayer *player) {
    TrackReleaseChannels(track, player, -1);
    TrackFreeChannels(track);
}

static void PlayerStopTrack(struct SNDPlayer *player, int trackIdx) {
    struct SNDTrack *track = PlayerGetTrack(player, trackIdx);

    if (track == NULL)
        return;
    
    TrackStop(track, player);
    SNDi_Work.tracks[player->tracks[trackIdx]].flags.active = FALSE;
    player->tracks[trackIdx] = 0xFF;
}

static void PlayerStop(struct SNDPlayer *player) {
    for (int i = 0; i < SND_TRACK_COUNT_PER_PLAYER; i++) {
        PlayerStopTrack(player, i);
    }
    player->flags.active = FALSE;
}

static void ChannelCallback(struct SNDExChannel *chn, int status, void *track_) {
    struct SNDExChannel *cur;
    struct SNDTrack *track;
    
    track = (struct SNDTrack *)track_;

    if (status == 1) {
        chn->priority = 0;
        SND_FreeExChannel(chn);
    }

    if (track->channelLLHead == chn) {
        track->channelLLHead = chn->channelLLNext;
    } else {
        cur = track->channelLLHead;

        while (cur->channelLLNext) {
            if (cur->channelLLNext == chn) {
                cur->channelLLNext = chn->channelLLNext;
                return;
            }
            cur = cur->channelLLNext;
        }
    }
}

static void TrackUpdateChannel(struct SNDTrack *track, struct SNDPlayer *player, int release) {
    int vol;
    int fader;
    int pan;
    int pitch;

    vol = SNDi_DecibelSquareTable[track->volume] +
        SNDi_DecibelSquareTable[track->expression] +
        SNDi_DecibelSquareTable[player->volume];

    fader = track->extFader + player->extFader;

    pitch = track->pitchBend;
    pitch *= track->bendRange << 6;
    pitch >>= 7;
    pitch += track->extPitch;

    pan = track->pan;

    if (track->panRange != 127)
        pan = (pan * track->panRange + 0x40) >> 7;
    
    pan += track->extPan;

    if (vol < -0x8000)
        vol = -0x8000;
    
    if (fader < -0x8000)
        fader = -0x8000;
    
    if (pan < -128)
        pan = -128;
    else if (pan > 127)
        pan = 127;
    
    for (struct SNDExChannel *chn = track->channelLLHead; chn != NULL; chn = chn->channelLLNext) {
        chn->userDecay2 = (short)fader;

        if (chn->envStatus == 3)
            continue;

        chn->userDecay = (s16)vol;
        chn->userPitch = (s16)pitch;
        chn->userPan = (s8)pan;
        chn->panRange = track->panRange;
        chn->lfo.param = track->mod;

        if (chn->length == 0 && release != 0) {
            chn->priority = 1;
            SND_ReleaseExChannel(chn);
        }
    }
}

static void PlayerUpdateChannel(struct SNDPlayer *player) {
    for (int i = 0; i < SND_TRACK_COUNT_PER_PLAYER; i++) {
        struct SNDTrack *trk = PlayerGetTrack(player, i);
        if (trk) {
            TrackUpdateChannel(trk, player, 1);
        }
    }
}

static void TrackPlayNote(struct SNDTrack *track, struct SNDPlayer *player, int midiKey, int velocity, int length) {
    struct SNDExChannel *chn = NULL;

    if (track->flags.tie) {
        chn = track->channelLLHead;
        if (chn) {
            chn->midiKey = (u8)midiKey;
            chn->velocity = (u8)velocity;
        }
    }

    if (chn == NULL) {
        struct SNDInstData inst;
        if (!SND_ReadInstData(player->bank, track->program, midiKey, &inst))
            return;

        u32 allowedChannels;

        switch (inst.type) {
        case SND_INST_PCM:
        case SND_INST_DIRECTPCM:
            // all channels support PCM
            allowedChannels = 0xFFFF;
            break;
        case SND_INST_PSG:
            // only channels 8, 9, 10, 11, 12, 13 support PSG
            allowedChannels = 0x3F00;
            break;
        case SND_INST_NOISE:
            // only channels 14 and 15 support noise
            allowedChannels = 0xC000;
            break;
        default:
            return;
        }

        allowedChannels &= track->channelMask;

        chn = SND_AllocExChannel(allowedChannels, player->prio + track->priority, track->flags.channelMask, ChannelCallback, track);
        if (chn == NULL)
            return;
        
        if (!SND_NoteOn(chn, midiKey, velocity, track->flags.tie ? -1 : length, player->bank, &inst)) {
            chn->priority = 0;
            SND_FreeExChannel(chn);
            return;
        }

        chn->channelLLNext = track->channelLLHead;
        track->channelLLHead = chn;
    }

    if (track->envAttack != 0xFF)
        SND_SetExChannelAttack(chn, track->envAttack);
    
    if (track->envDecay != 0xFF)
        SND_SetExChannelDecay(chn, track->envDecay);

    if (track->envSustain != 0xFF)
        SND_SetExChannelSustain(chn, track->envSustain);

    if (track->envRelease != 0xFF)
        SND_SetExChannelRelease(chn, track->envRelease);
    
    chn->sweepPitch = track->sweepPitch;
    if (track->flags.portamento)
        chn->sweepPitch += (short)((track->portamentoKey - midiKey) << 6);
    
    if (track->portamentoTime == 0) {
        chn->sweepLength = length;
        chn->flags.autoSweep = FALSE;
    } else {
        int swp = track->portamentoTime * track->portamentoTime;
        swp *= chn->sweepPitch < 0 ? -chn->sweepPitch : chn->sweepPitch;
        swp >>= 11;
        chn->sweepLength = swp;
    }

    chn->sweepCounter = 0;
}

static int TrackStepTicks(struct SNDTrack *track, struct SNDPlayer *player, int trackIdx, u32 playNotes) {
    (void)trackIdx;

    struct SNDExChannel *chn;
    u8 cmd;
    enum SNDSeqVal valueType;
    BOOL specialValueType;
    BOOL runCmd;
    s32 length;
    int midiKey;

    s32 par;


    for (chn = track->channelLLHead; chn; chn = chn->channelLLNext) {
        if (chn->length > 0)
            chn->length--;
        
        if (!chn->flags.autoSweep && chn->sweepCounter < chn->sweepLength)
            chn->sweepCounter++;
    }

    if (track->flags.noteFinishWait) {
        if (track->channelLLHead)
            return 0;
        track->flags.noteFinishWait = FALSE;
    }

    if (track->wait > 0) {
        track->wait--;
        if (track->wait > 0)
            return 0;
    }

    SeqCacheFetch(track->cur);

    while (track->wait == 0 && !track->flags.noteFinishWait) {
        specialValueType = FALSE;
        runCmd = TRUE;

        cmd = TrackReadU8(track);

        if (cmd == 0xA2) {
            cmd = TrackReadU8(track);
            runCmd = track->flags.cmp;
        }

        if (cmd == 0xA0) {
            cmd = TrackReadU8(track);
            valueType = SND_SEQ_VAL_RAN;
            specialValueType = TRUE;
        }

        if (cmd == 0xA1) {
            cmd = TrackReadU8(track);
            valueType = SND_SEQ_VAL_VAR;
            specialValueType = TRUE;
        }

        if ((cmd & 0x80) == 0) {
            par = TrackReadU8(track);

            length = TrackParseValue(track, player, specialValueType ? valueType : SND_SEQ_VAL_VLV);
            midiKey = cmd + track->transpose;

            if (!runCmd)
                continue;
            
            if (midiKey < 0)
                midiKey = 0;
            else if (midiKey > 127) {
                midiKey = 127;
            }

            if (!track->flags.muted && playNotes != 0) {
                TrackPlayNote(track, player, midiKey, par, (length > 0) ? length : -1);
            }
            
            track->portamentoKey = (u8)midiKey;

            if (track->flags.noteWait) {
                track->wait = length;
                if (length == 0) {
                    track->flags.noteFinishWait = TRUE;
                }
            }

            continue;
        }

        switch (cmd & 0xF0) {
        case 0x80:
            par = TrackParseValue(track, player, specialValueType ? valueType : SND_SEQ_VAL_VLV);
            if (!runCmd)
                break;
            
            switch (cmd) {
            case 0x80:
                track->wait = par;
                break;
            case 0x81:
                if (par < 0x10000)
                    track->program = (u16)par;
                break;
            }
            break;
        case 0x90:
            switch (cmd) {
            case 0x93:
                {
                    u32 off;
                    struct SNDTrack *newTrack;

                    par = TrackReadU8(track);
                    off = TrackReadU24(track);
                    if (!runCmd)
                        break;

                    newTrack = PlayerGetTrack(player, par);
                    if (newTrack && newTrack != track) {
                        TrackStop(newTrack, player);
                        TrackStart(newTrack, track->base, off);
                    }
                }
                break;
            case 0x94:
                {
                    u32 off = TrackReadU24(track);
                    if (!runCmd)
                        break;
                    track->cur = &track->base[off];
                }
                break;
            case 0x95:
                {
                    u32 off = TrackReadU24(track);
                    if (!runCmd)
                        break;

                    if (track->callStackDepth < SND_TRACK_MAX_CALL) {
                        track->posCallStack[track->callStackDepth] = track->cur;
                        track->callStackDepth++;
                        track->cur = &track->base[off];
                    }
                    break;
                }
            }
            break;
        case 0xC0:
        case 0xD0:
            {
                union {
                    u8 _u8;
                    s8 _s8;
                } par;
                par._u8 = (u8)TrackParseValue(track, player, specialValueType ? valueType : SND_SEQ_VAL_U8);
                if (!runCmd)
                    break;

                switch (cmd) {
                case 0xC1:
                    track->volume = par._u8;
                    break;
                case 0xD5:
                    track->expression = par._u8;
                    break;
                case 0xC2:
                    player->volume = par._u8;
                    break;
                case 0xC5:
                    track->bendRange = par._u8;
                    break;
                case 0xC6:
                    track->priority = par._u8;
                    break;
                case 0xC7:
                    track->flags.noteWait = par._u8;
                    break;
                case 0xCF:
                    track->portamentoTime = par._u8;
                    break;
                case 0xCA:
                    track->mod.depth = par._u8;
                    break;
                case 0xCB:
                    track->mod.speed = par._u8;
                    break;
                case 0xCC:
                    track->mod.target = par._u8;
                    break;
                case 0xCD:
                    track->mod.range = par._u8;
                    break;
                case 0xD0:
                    track->envAttack = par._u8;
                    break;
                case 0xD1:
                    track->envDecay = par._u8;
                    break;
                case 0xD2:
                    track->envSustain = par._u8;
                    break;
                case 0xD3:
                    track->envRelease = par._u8;
                    break;
                case 0xD4:
                    if (track->callStackDepth < SND_TRACK_MAX_CALL) {
                        track->posCallStack[track->callStackDepth] = track->cur;
                        track->loopCount[track->callStackDepth] = par._u8;
                        track->callStackDepth++;
                    }
                    break;
                case 0xC8:
                    track->flags.tie = par._u8;
                    TrackReleaseChannels(track, player, -1);
                    TrackFreeChannels(track);
                    break;
                case 0xD7:
                    TrackMute(track, player, par._u8);
                    break;
                case 0xC9:
                    track->portamentoKey = (u8)(par._u8 + track->transpose);
                    track->flags.portamento = TRUE;
                    break;
                case 0xCE:
                    track->flags.portamento = par._u8;
                    break;
                case 0xC3:
                    track->transpose = par._s8;
                    break;
                case 0xC4:
                    track->pitchBend = par._s8;
                    break;
                case 0xC0:
                    track->pan = (s8)(par._u8 - 0x40);
                    break;
                case 0xD6:
                    {
                        s16 *varPtr;

                        if (sPrintEnabled) {
                            varPtr = PlayerGetVariablePointer(player, par._u8);
                        }
                    }
                    break;
                }
            }
            break;
        case 0xE0:
            {
                s16 par = (s16)TrackParseValue(track, player, specialValueType ? valueType : SND_SEQ_VAL_U16);
                if (!runCmd)
                    break;

                switch (cmd) {
                case 0xE3:
                    track->sweepPitch = par;
                    break;
                case 0xE1:
                    player->tempo = (u16)par;
                    break;
                case 0xE0:
                    track->mod.delay = (u16)par;
                    break;
                }
            }
            break;
        case 0xB0:
            {
                int varNum = TrackReadU8(track);

                s16 par = (s16)TrackParseValue(track, player, specialValueType ? valueType : SND_SEQ_VAL_U16);
                s16 *varPtr = PlayerGetVariablePointer(player, varNum);

                if (!runCmd)
                    break;

                if (varPtr == NULL)
                    break;

                switch (cmd) {
                case 0xB0:
                    *varPtr = par;
                    break;
                case 0xB1:
                    *varPtr += par;
                    break;
                case 0xB2:
                    *varPtr -= par;
                    break;
                case 0xB3:
                    *varPtr *= par;
                    break;
                case 0xB4:
                    if (par != 0)
                        *varPtr /= par;
                    break;
                case 0xB5:
                    if (par >= 0)
                        *varPtr <<= par;
                    else
                        *varPtr >>= -par;
                    break;
                case 0xB6:
                    {
                        BOOL neg = FALSE;
                        if (par < 0) {
                            neg = TRUE;
                            par = (s16)(-par);
                        }
                        s32 random = SND_CalcRandom();
                        random = (random * (par + 1)) >> 16;
                        if (neg)
                            random = -random;
                        *varPtr = (s16)random;
                    }
                    break;
                case 0xB7:
                    break;
                case 0xB8:
                    track->flags.cmp = *varPtr == par;
                    break;
                case 0xB9:
                    track->flags.cmp = *varPtr >= par;
                    break;
                case 0xBA:
                    track->flags.cmp = *varPtr > par;
                    break;
                case 0xBB:
                    track->flags.cmp = *varPtr <= par;
                    break;
                case 0xBC:
                    track->flags.cmp = *varPtr < par;
                    break;
                case 0xBD:
                    track->flags.cmp = *varPtr != par;
                    break;
                }
            }
            break;
        case 0xF0:
            if (!runCmd)
                break;
            
            switch (cmd) {
            case 0xFD:
                if (track->callStackDepth != 0) {
                    track->callStackDepth--;
                    track->cur = track->posCallStack[track->callStackDepth];
                }
                break;
            case 0xFC:
                {
                    if (track->callStackDepth == 0)
                        break;

                    // gosh, this was nasty to figure out
                    u8 loopCount = track->loopCount[track->callStackDepth - 1];
                    if (loopCount != 0) {
                        loopCount--;
                        if (loopCount == 0) {
                            track->callStackDepth--;
                            break;
                        }
                    }
                    track->loopCount[track->callStackDepth - 1] = loopCount;
                    track->cur = track->posCallStack[track->callStackDepth - 1];
                }
                break;
            case 0xFE:
                break;
            case 0xFF:
                return -1;
            }
            break;
        }
    }

    return 0;
}

static BOOL PlayerStepTicks(struct SNDPlayer *player, u32 ticks) {
    BOOL isPlaying = FALSE;

    for (int i = 0; i < SND_TRACK_COUNT_PER_PLAYER; i++) {
        struct SNDTrack *trk = PlayerGetTrack(player, i);

        if (trk && trk->cur) {
            if (TrackStepTicks(trk, player, i, ticks))
                PlayerStopTrack(player, i);
            else
                isPlaying = TRUE;
        }
    }

    return !isPlaying;
}

static s16 *PlayerGetVariablePointer(const struct SNDPlayer *player, int var) {
    if (SNDi_SharedWork == NULL)
        return NULL;
    else if (var < 16) {
        return &SNDi_SharedWork->players[player->playerId].localVars[var];
    } else {
        return &SNDi_SharedWork->globalVars[var - 16];
    }
}

static int AllocateTrack(void) {
    for (int i = 0; i < SND_TRACK_COUNT; i++) {
        if (!SNDi_Work.tracks[i].flags.active) {
            SNDi_Work.tracks[i].flags.active = TRUE;
            return i;
        }
    }

    return -1;
}

static void TrackMute(struct SNDTrack *track, struct SNDPlayer *player, int muteMode) {
    switch (muteMode) {
    case SND_TRACK_MUTE_MODE_UNMUTE:
        track->flags.muted = FALSE;
        break;
    case SND_TRACK_MUTE_MODE_MUTE:
        track->flags.muted = TRUE;
        break;
    case SND_TRACK_MUTE_MODE_MUTE_RELEASE:
        track->flags.muted = TRUE;
        TrackReleaseChannels(track, player, -1);
        break;
    case SND_TRACK_MUTE_MODE_MUTE_STOP:
        track->flags.muted = TRUE;
        TrackReleaseChannels(track, player, 127);
        TrackFreeChannels(track);
        break;
    }
}
