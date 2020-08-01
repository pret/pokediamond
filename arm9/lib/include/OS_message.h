#ifndef POKEDIAMOND_OS_MESSAGE_H
#define POKEDIAMOND_OS_MESSAGE_H

#include "nitro/types.h"
#include "OS_thread.h"

typedef void *OSMessage;

typedef struct OSMessageQueue
{
    OSThreadQueue queueSend;
    OSThreadQueue queueReceive;
    OSMessage *msgArray;
    s32 msgCount;
    s32 firstIndex;
    s32 usedCount;
} OSMessageQueue;

#define  OS_MESSAGE_NOBLOCK   0
#define  OS_MESSAGE_BLOCK     1

void OS_InitMessageQueue(OSMessageQueue *mq, OSMessage *msgArray, s32 msgCount);
BOOL OS_SendMessage(OSMessageQueue *mq, OSMessage msg, s32 flags);
BOOL OS_ReceiveMessage(OSMessageQueue *mq, OSMessage *msg, s32 flags);
BOOL OS_JamMessage(OSMessageQueue *mq, OSMessage msg, s32 flags);
BOOL OS_ReadMessage(OSMessageQueue *mq, OSMessage *msg, s32 flags);

#endif //POKEDIAMOND_OS_MESSAGE_H
