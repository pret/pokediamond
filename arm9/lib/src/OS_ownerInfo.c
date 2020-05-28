#include "function_target.h"
#include "OS_ownerInfo.h"
#include "MI_memory.h"

ARM_FUNC void OS_GetMacAddress(u8 *macAddress)
{
    MI_CpuCopy8((void *)0x027FFCF4, macAddress, 0x6);
}

ARM_FUNC void OS_GetOwnerInfo(OSOwnerInfo* info)
{
    NVRAMConfig *src = (NVRAMConfig *)OS_GetSystemWork()->nvramUserInfo;
    info->language = (u8)src->ncd.option.language;
    info->favoriteColour = (u8)src->ncd.owner.favouriteColour;
    info->birthday.month = (u8)src->ncd.owner.birthday.month;
    info->birthday.day = (u8)src->ncd.owner.birthday.day;
    info->nickNameLength = (u16)src->ncd.owner.nickname.length;
    info->commentLength = (u16)src->ncd.owner.comment.length;
    MIi_CpuCopy16(src->ncd.owner.nickname.str, info->nickName, 10 * sizeof(u16));
    MIi_CpuCopy16(src->ncd.owner.comment.str, info->comment, 26 * sizeof(u16));
}

ARM_FUNC s64 OS_GetOwnerRtcOffset(void)
{
    NVRAMConfig *src = (NVRAMConfig *)OS_GetSystemWork()->nvramUserInfo;
    return src->ncd.option.rtcOffset;
}
