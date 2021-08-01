#include "SND_command.h"

#include "registers.h"
#include "mmap.h"

#include "MI_memory.h"
#include "PXI_fifo.h"
#include "OS_message.h"
#include "OS_system.h"
#include "SND.h"
#include "SND_alarm.h"
#include "SND_capture.h"
#include "SND_channel.h"
#include "SND_exChannel.h"
#include "SND_main.h"
#include "SND_seq.h"
#include "SND_work.h"

#define SND_MSG_ARRAY_SIZE 8

static OSMessage sMsgArray[SND_MSG_ARRAY_SIZE];
static struct OSMessageQueue sMsgQueue;

static void InitPXI(void);
static void StartTimer(u32 channelMask, u32 captureMask, u32 alarmMask, s32 unused);
static void StopTimer(u32 channelMask, u32 captureMask, u32 alarmMask, s32 hold);
static void SetChannelTimer(u32 channelMask, int timer);
static void SetChannelVolume(u32 channelMask, int vol, int shift);
static void SetChannelPan(u32 channelMask, int pan);
static void ReadDriverInfo(struct SNDDriverInfo *driverInfo);

void SND_CommandInit(void) {
    OS_InitMessageQueue(&sMsgQueue, sMsgArray, SND_MSG_ARRAY_SIZE);
    InitPXI();
    SNDi_SharedWork = NULL;
}

void SND_CommandProc(void) {
    struct SNDCommand cmd;
    struct SNDCommand *cmd_ptr;
    OSMessage msg;

    while (OS_ReceiveMessage(&sMsgQueue, &msg, 0)) {
        // casting it directly below doesn't appear to match
        cmd_ptr = (struct SNDCommand *)msg;

        while (cmd_ptr) {
            cmd = *cmd_ptr;

            switch (cmd.id) {
            case SND_CMD_START_SEQ:
                SND_StartSeq((int)cmd.arg[0], (const void *)cmd.arg[1], cmd.arg[2], (struct SNDBankData *)cmd.arg[3]);
                break;
            case SND_CMD_STOP_SEQ:
                SND_StopSeq((int)cmd.arg[0]);
                break;
            case SND_CMD_PREPARE_SEQ:
                SND_PrepareSeq((int)cmd.arg[0], (const void *)cmd.arg[1], cmd.arg[2], (struct SNDBankData *)cmd.arg[3]);
                break;
            case SND_CMD_START_PREPARED_SEQ:
                SND_StartPreparedSeq((int)cmd.arg[0]);
                break;
            case SND_CMD_PAUSE_SEQ:
                SND_PauseSeq((int)cmd.arg[0], (BOOL)cmd.arg[1]);
                break;
            case SND_CMD_SKIP_SEQ:
                SND_SkipSeq((int)cmd.arg[0], cmd.arg[1]);
                break;
            case SND_CMD_PLAYER_PARAM:
                SNDi_SetPlayerParam((int)cmd.arg[0], cmd.arg[1], cmd.arg[2], (int)cmd.arg[3]);
                break;
            case SND_CMD_TRACK_PARAM:
                SNDi_SetTrackParam((int)cmd.arg[0] & 0xFFFFFF, cmd.arg[1], cmd.arg[2], cmd.arg[3], (u8)(cmd.arg[0] >> 24));
                break;
            case SND_CMD_MUTE_TRACK:
                SND_SetTrackMute((int)cmd.arg[0], cmd.arg[1], (BOOL)cmd.arg[2]);
                break;
            case SND_CMD_ALLOCATABLE_CHANNEL:
                SND_SetTrackAllocatableChannel((int)cmd.arg[0], cmd.arg[1], cmd.arg[2]);
                break;
            case SND_CMD_PLAYER_LOCAL_VAR:
                SND_SetPlayerLocalVariable((int)cmd.arg[0], (int)cmd.arg[1], (s16)cmd.arg[2]);
                break;
            case SND_CMD_PLAYER_GLOBAL_VAR:
                SND_SetPlayerGlobalVariable((int)cmd.arg[0], (s16)cmd.arg[1]);
                break;
            case SND_CMD_START_TIMER:
                StartTimer(cmd.arg[0], cmd.arg[1], cmd.arg[2], (int)cmd.arg[3]);
                break;
            case SND_CMD_STOP_TIMER:
                StopTimer(cmd.arg[0], cmd.arg[1], cmd.arg[2], (int)cmd.arg[3]);
                break;
            case SND_CMD_SETUP_CAPTURE:
                SND_SetupCapture(
                    (int)(cmd.arg[2] >> 31u) & 1,
                    (int)(cmd.arg[2] >> 30u) & 1,
                    (void *)cmd.arg[0],
                    (int)cmd.arg[1],
                    (BOOL)(cmd.arg[2] >> 29u) & 1,
                    (int)(cmd.arg[2] >> 28u) & 1,
                    (int)(cmd.arg[2] >> 27u) & 1
                );
                break;
            case SND_CMD_SETUP_ALARM:
                SND_SetupAlarm(
                    (int)cmd.arg[0],
                    cmd.arg[1],
                    cmd.arg[2],
                    cmd.arg[3]
                );
                break;
            case SND_CMD_CHANNEL_TIMER:
                SetChannelTimer(cmd.arg[0], (int)cmd.arg[1]);
                break;
            case SND_CMD_CHANNEL_VOLUME:
                SetChannelVolume(cmd.arg[0], (int)cmd.arg[1], (int)cmd.arg[2]);
                break;
            case SND_CMD_CHANNEL_PAN:
                SetChannelPan(cmd.arg[0], (int)cmd.arg[1]);
                break;
            case SND_CMD_SETUP_CHANNEL_PCM:
                SND_SetupChannelPcm(
                    (int)cmd.arg[0] & 0xFFFF,
                    (void *)(cmd.arg[1] & 0x7FFFFFFu),
                    (int)(cmd.arg[3] >> 24u) & 0x3,
                    (int)(cmd.arg[3] >> 26u) & 0x3,
                    (int)cmd.arg[3] & 0xFFFF,
                    (int)cmd.arg[2] & 0x3FFFFF,
                    (int)(cmd.arg[2] >> 24u) & 0x7F,
                    (int)(cmd.arg[2] >> 22u) & 0x3,
                    (int)(cmd.arg[0] >> 16u) & 0xFFFF,
                    (int)(cmd.arg[3] >> 16u) & 0x7F
                );
                break;
            case SND_CMD_SETUP_CHANNEL_PSG:
                SND_SetupChannelPsg(
                    (int)cmd.arg[0],
                    (int)cmd.arg[3],
                    (int)cmd.arg[1] & 0x7F,
                    (int)(cmd.arg[1] >> 8u) & 0x3,
                    (int)(cmd.arg[2] >> 8u) & 0xFFFF,
                    (int)cmd.arg[2] & 0x7F
                );
                break;
            case SND_CMD_SETUP_CHANNEL_NOISE:
                SND_SetupChannelNoise(
                    (int)cmd.arg[0],
                    (int)cmd.arg[1] & 0x7F,
                    (int)(cmd.arg[1] >> 8u) & 0x3,
                    (int)(cmd.arg[2] >> 8u) & 0xFFFF,
                    (int)cmd.arg[2] & 0x7F
                );
                break;
            case SND_CMD_SURROUND_DECAY:
                SNDi_SetSurroundDecay((int)cmd.arg[0]);
                break;
            case SND_CMD_MASTER_VOLUME:
                SND_SetMasterVolume((int)cmd.arg[0]);
                break;
            case SND_CMD_MASTER_PAN:
                SND_SetMasterPan((int)cmd.arg[0]);
                break;
            case SND_CMD_OUTPUT_SELECTOR:
                SND_SetOutputSelector((int)cmd.arg[0], (int)cmd.arg[1], (int)cmd.arg[2], (int)cmd.arg[3]);
                break;
            case SND_CMD_LOCK_CHANNEL:
                SND_LockChannel(cmd.arg[0], cmd.arg[1]);
                break;
            case SND_CMD_UNLOCK_CHANNEL:
                SND_UnlockChannel(cmd.arg[0], cmd.arg[1]);
                break;
            case SND_CMD_STOP_UNLOCKED_CHANNEL:
                SND_StopUnlockedChannel(cmd.arg[0], cmd.arg[1]);
                break;
            case SND_CMD_INVALIDATE_SEQ:
                SND_InvalidateSeq((void *)cmd.arg[0], (void *)cmd.arg[1]);
                break;
            case SND_CMD_INVALIDATE_BANK:
                SND_InvalidateBank((void *)cmd.arg[0], (void *)cmd.arg[1]);
                break;
            case SND_CMD_INVALIDATE_WAVE:
                SND_InvalidateWave((void *)cmd.arg[0], (void *)cmd.arg[1]);
                break;
            case SND_CMD_SET_SHARED_WORK:
                SNDi_SharedWork = (struct SNDSharedWork *)cmd.arg[0];
                break;
            case SND_CMD_READ_DRIVER_INFO:
                ReadDriverInfo((struct SNDDriverInfo *)cmd.arg[0]);
                break;
            } // end switch

            cmd_ptr = cmd.llNext;
        } // end loop over command linked list

        SNDi_SharedWork->finishedCommandTag++;
    } // end loop over receive message
}

static void PxiFifoCallback(PXIFifoTag tag, u32 data, BOOL error) {
    (void)tag;
    (void)error;

    OSIntrMode intrMode = OS_DisableInterrupts();

    if (data >= HW_MAIN_MEM) {
        (void)OS_SendMessage(&sMsgQueue, (OSMessage)data, 0);
    } else {
        if (data == 0)
            SND_SendWakeupMessage();
    }

    (void)OS_RestoreInterrupts(intrMode);
}

static void InitPXI(void) {
    PXI_SetFifoRecvCallback(PXI_FIFO_TAG_SOUND, PxiFifoCallback);
}

static void SetChannelTimer(u32 channelMask, int timer) {
    for (int i = 0; i < SND_CHANNEL_COUNT && channelMask != 0; i++, channelMask >>= 1) {
        if (channelMask & 1)
            SND_SetChannelTimer(i, timer);
    }
}

static void SetChannelVolume(u32 channelMask, int vol, int shift) {
    for (int i = 0; i < SND_CHANNEL_COUNT && channelMask != 0; i++, channelMask >>= 1) {
        if (channelMask & 1)
            SND_SetChannelVolume(i, vol, shift);
    }
}

static void SetChannelPan(u32 channelMask, int pan) {
    for (int i = 0; i < SND_CHANNEL_COUNT && channelMask != 0; i++, channelMask >>= 1) {
        if (channelMask & 1)
            SND_SetChannelPan(i, pan);
    }
}

static void StartTimer(u32 channelMask, u32 captureMask, u32 alarmMask, s32 unused) {
    (void)unused;

    OSIntrMode intrMode = OS_DisableInterrupts();

    for (int i = 0; i < SND_CHANNEL_COUNT && channelMask != 0; i++, channelMask >>= 1) {
        if (channelMask & 1)
            reg_SOUNDxCNT_STAT(i) |= 0x80;
    }

    if (captureMask & 1) {
        if (captureMask & 2) {
            *(vu16 *)&reg_SNDCAPxCNT(0) |= 0x8080;
        } else {
            reg_SNDCAPxCNT(0) |= 0x80;
        }
    } else if (captureMask & 2) {
        reg_SNDCAPxCNT(1) |= 0x80;
    }

    for (int i = 0; i < SND_ALARM_COUNT && alarmMask != 0; i++, alarmMask >>= 1) {
        if (alarmMask & 1)
            SND_StartAlarm(i);
    }

    (void)OS_RestoreInterrupts(intrMode);
    SND_UpdateSharedWork();
}

static void StopTimer(u32 channelMask, u32 captureMask, u32 alarmMask, s32 hold) {
    OSIntrMode intrMode = OS_DisableInterrupts();

    for (int i = 0; i < SND_ALARM_COUNT && alarmMask != 0; i++, alarmMask >>= 1) {
        if (alarmMask & 1)
            SND_StopAlarm(i);
    }

    for (int i = 0; i < SND_CHANNEL_COUNT && channelMask != 0; i++, channelMask >>= 1) {
        if (channelMask & 1)
            SND_StopChannel(i, hold);
    }

    if (captureMask & 1)
        reg_SNDCAPxCNT(0) = 0;
    if (captureMask & 2)
        reg_SNDCAPxCNT(1) = 0;

    (void)OS_RestoreInterrupts(intrMode);
    SND_UpdateSharedWork();
}

static void ReadDriverInfo(struct SNDDriverInfo *driverInfo) {
    MI_CpuCopy32(&SNDi_Work, driverInfo, sizeof(SNDi_Work));

    driverInfo->workPtr = &SNDi_Work;

    for (int i = 0; i < SND_CHANNEL_COUNT; i++) {
        driverInfo->channelControls[i] = SND_GetChannelControl(i);
    }

    driverInfo->lockedChannels = SND_GetLockedChannel(0);
}
