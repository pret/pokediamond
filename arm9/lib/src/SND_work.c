#include "SND_work.h"
#include "SND_alarm.h"
#include "SND_main.h"

struct SNDSharedWork *SNDi_SharedWork;

void DC_InvalidateRange(void *mem, u32 size);
void DC_FlushRange(void *mem, u32 size);

u32 SND_GetPlayerStatus(void) {
    DC_InvalidateRange(&SNDi_SharedWork->playerStatus, 4);
    return SNDi_SharedWork->playerStatus;
}

u16 SND_GetChannelStatus(void) {
    DC_InvalidateRange(&SNDi_SharedWork->channelStatus, 2);
    return SNDi_SharedWork->channelStatus;
}

//u16 SND_GetCaptureStatus(void) {
//    DC_InvalidateRange(&SNDi_SharedWork->captureStatus, 2);
//    return SNDi_SharedWork->captureStatus;
//}

u32 SND_GetPlayerTickCounter(u32 playerId) {
    DC_InvalidateRange(&SNDi_SharedWork->players[playerId].tickCounter, 4);
    return SNDi_SharedWork->players[playerId].tickCounter;
}

//s16 SND_GetPlayerLocalVariable(u32 playerId, u32 var) {
//    DC_InvalidateRange(&SNDi_SharedWork->players[playerId].localVars[var], 2);
//    return SNDi_SharedWork->players[playerId].localVars[var];
//}
//
//s16 SND_GetPlayerLocalVariable(u32 var) {
//    DC_InvalidateRange(&SNDi_SharedWork->globalVars[var], 2);
//    return SNDi_SharedWork->globalVars[var];
//}
//
//BOOL SND_ReadChannelInfo(const SNDDriverInfo *driverInfo, s32 chnId, SNDChannelInfo *chnInfo) {
//    // T O D O, implement if it's actually used
//}
//
//BOOL SND_ReadPlayerInfo(const SNDDriverInfo *driverInfo, s32 playerId, SNDPlayerInfo *playerInfo) {
//    if (playerId < 0 || playerId >= SND_PLAYER_COUNT)
//        return FALSE;
//    SNDPlayer *player = &driverInfo->work.players[playerId];
//    playerInfo->trackBitMask = 0;
//    for (s32 i = 0; i < SND_TRACK_COUNT; i++) {
//        if (player->tracks[i] != SND_INVALID_TRACK_INDEX) {
//            playerInfo->trackBitMask |= (1 << i);
//        }
//    }
//    playerInfo->flags.active = player->flags.active;
//    playerInfo->flags.paused = player->flags.paused;
//    playerInfo->tempo = player->tempo;
//    playerInfo->volume = player->volume;
//    return TRUE;
//}
//
//
//BOOL SND_ReadTrackInfo(const SNDDriverInfo *driverInfo s32 playerId, s32 trackId, SNDTrackInfo *trackInfo) {
//    if (playerId < 0 || playerId >= SND_PLAYER_COUNT)
//        return FALSE;
//    if (trackId < 0 || trackId >= SND_TRACK_COUNT)
//        return FALSE;
//    SNDPlayer *player = &driverInfo->work.players[playerId];
//    if (player->tracks[trackId] == SND_INVALID_TRACK_INDEX)
//        return FALSE;
//    SNDTrack *track = &driverInfo->work.tracks[trackId];
//    trackInfo->program = track->program;
//    trackInfo->volume = track->volume;
//    trackInfo->expression = track->expression;
//    trackInfo->pitchBend = track->pitchBend;
//    trackInfo->bendRange = track->bendRange;
//    trackInfo->pan = track->pan + 0x40; // 0x40 == MIDI center pan
//    trackInfo->transpose = track->transpose;
//    trackInfo->chnCount = 0;
//
//    //#define LL_READ_PTR(ptr, basePtr, base) (ptr ? ((typeof(ptr))(s32)(ptr) - (s32)(basePtr) + (s32)&(base)) : NULL)
//    //for (SNDExChannel *exChn = LL_READ_PTR(track->channelLLHead, driverInfo->workPtr, driverInfo->work);
//    //        exChn != NULL; exChn = LL_READ_PTR(exChn->channelLLNext, driverInfo->workPtr, driverInfo->work))
//    //{
//    //    trackInfo->channel[trackInfo->chnCount] = exChn->id;
//    //    trackInfo->chnCount++;
//    //}
//    //#undef LL_READ_PTR
//
//    return TRUE;
//}

ARM_FUNC u32 SNDi_GetFinishedCommandTag(void) {
    DC_InvalidateRange(&SNDi_SharedWork->finishedCommandTag, 4);
    return SNDi_SharedWork->finishedCommandTag;
}

ARM_FUNC void SNDi_InitSharedWork(struct SNDSharedWork *sw) {
    sw->playerStatus = 0;
    sw->channelStatus = 0;
    sw->captureStatus = 0;
    sw->finishedCommandTag = 0;

    for (s32 i = 0; i < SND_PLAYER_COUNT; i++) {
        sw->players[i].tickCounter = 0;
        for (s32 j = 0; j < 16; j++) {
            sw->players[i].localVars[j] = -1;
        }
    }

    for (s32 i = 0; i < 16; i++) {
        sw->globalVars[i] = -1;
    }

    DC_FlushRange(sw, sizeof(*sw));
}
