#ifndef POKEDIAMOND_EASY_CHAT_H
#define POKEDIAMOND_EASY_CHAT_H

#include "constants/easy_chat.h"

#include "msgdata.h"

typedef u16 ecword_t;

typedef struct EasyChatManager {
    HeapID heapId;
    MsgData *msgData[EC_GROUP_MAX];
} EasyChatManager;

typedef struct SaveEasyChat {
    u32 greetings;
    u32 trendy;
} SaveEasyChat;

EasyChatManager *EasyChatManager_New(HeapID heapId);
void EasyChatManager_Delete(EasyChatManager *easyChatManager);
void EasyChatManager_ReadWordIntoString(EasyChatManager *easyChatManager, u16 ecWord, String *dest);
void GetECWordIntoStringByIndex(u32 ecWord, String *dest);
u16 GetECWordIndexByPair(u32 category, u32 msgNo);
void GetCategoryAndMsgNoByECWordIdx(u32 ecWord, u32 *category, u32 *msgNo);
u32 Save_EasyChat_sizeof(void);
void Save_EasyChat_Init(SaveEasyChat *saveEasyChat);
SaveEasyChat *Save_EasyChat_Get(SaveData *saveData);
BOOL Save_EasyChat_GetTrendySayingFlag(SaveEasyChat *saveEasyChat, u32 flag);
u32 Save_EasyChat_SetRandomTrendySaying(SaveEasyChat *saveEasyChat);
BOOL Save_EasyChat_TrendySayingsUnlockedAllCheck(SaveEasyChat *saveEasyChat);
ecword_t TrendyWordIdxToECWord(u32 word);
BOOL Save_EasyChat_GetGreetingsFlag(SaveEasyChat *saveEasyChat, u32 flag);
void Save_EasyChat_SetGreetingFlag(SaveEasyChat *saveEasyChat, u32 flag);
s32 GetDuplicateWordNum(ecword_t word);
ecword_t RemapDuplicateWord(ecword_t word, s32 target);

#endif // POKEDIAMOND_EASY_CHAT_H
