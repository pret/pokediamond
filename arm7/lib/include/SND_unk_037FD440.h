#ifndef GUARD_SND_UNK_H
#define GUARD_SND_UNK_H

#include "nitro/types.h"

struct SNDTrack *PlayerGetTrack(struct SNDPlayer *player, int track);
void PlayerStop(struct SNDPlayer *);
void TrackMute(struct SNDTrack *track, struct SNDPlayer *player, int muteMode);
void TrackReleaseChannels(struct SNDTrack *track, struct SNDPlayer *player, int release);
void TrackFreeChannels(struct SNDTrack *track);
BOOL PlayerStepTicks(struct SNDPlayer *player, u32 ticks);
void PlayerSetBank(struct SNDPlayer *player, struct SNDBankData *bankData);
int AllocateTrack(void);
void TrackInit(struct SNDTrack *track);
void TrackSetSeq(struct SNDTrack *track, const void *seq, u32 offset);
void SeqCacheFetch(const void *addr);
u8 SeqReadByte(const void *addr);
u16 TrackReadU16(struct SNDTrack *track);
void PlayerSeqMain(struct SNDPlayer *player);
void PlayerUpdateChannelVolume(struct SNDPlayer *player);

#endif //GUARD_SND_UNK_H
