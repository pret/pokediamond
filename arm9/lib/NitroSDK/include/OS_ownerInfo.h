#ifndef POKEDIAMOND_OS_OWNERINFO_H
#define POKEDIAMOND_OS_OWNERINFO_H

#include "consts.h"
#include "userInfo.h"

typedef struct OSBirthday
{
    u8 month;
    u8 day;
} OSBirthday;

typedef struct OSOwnerInfo
{
    u8 language;
    u8 favoriteColour;
    OSBirthday birthday;
    u16 nickName[10]; //either 10 or 8
    u16 nickNameLength;
    u16 comment[26];
    u16 commentLength;
} OSOwnerInfo;

void OS_GetMacAddress(u8 *macAddress);
void OS_GetOwnerInfo(OSOwnerInfo* info);
s64 OS_GetOwnerRtcOffset(void);

#endif //POKEDIAMOND_OS_OWNERINFO_H
