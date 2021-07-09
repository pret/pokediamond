#include "SND_seq.h"

#include "SND_main.h"
#include "SND_work.h"
#include "SND_unk_037FD440.h"

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
            PlayerUpdateChannelVolume(ply);
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
    
    PlayerSetBank(ply, bankData);

    int allocTrkIdx = AllocateTrack();

    if (allocTrkIdx < 0)
        return;
    
    struct SNDTrack *trk = &SNDi_Work.tracks[allocTrkIdx];
    TrackInit(trk);
    TrackSetSeq(trk, seq, offset);
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
