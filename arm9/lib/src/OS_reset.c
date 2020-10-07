#include "function_target.h"
#include "OS_reset.h"
#include "MB_mb.h"
#include "OS_terminate_proc.h"
#include "OS_interrupt.h"
#include "OS_system.h"
#include "OS_spinLock.h"
#include "OS_cache.h"
#include "sections.h"
#include "MI_dma.h"
#include "CARD_common.h"
#include "PXI_init.h"

static u16 OSi_IsInitReset = 0;
vu16 OSi_IsResetOccurred = 0;

extern u32 PXI_IsCallbackReady(u32 param1, u32 param2);
extern void PXI_SetFifoRecvCallback(u32 param1, void* callback);
extern u32 PXI_SendWordByFifo(u32 param1, u32 data, u32 param2);

static void OSi_CommonCallback(PXIFifoTag tag, u32 data, BOOL err);
static void OSi_SendToPxi(u16 data);
static void OSi_DoResetSystem(void);
static void OSi_CpuClear32(register u32 data, register void *destp, register u32 size);
static void OSi_ReloadRomData(void);
static void OSi_ReadCardRom32(u32 src, void *dst, s32 len);

ARM_FUNC void OS_InitReset(void) {
    if (OSi_IsInitReset) {
        return;
    }
    OSi_IsInitReset = TRUE;
    PXI_Init();
    while (!PXI_IsCallbackReady(PXI_FIFO_TAG_OS, PXI_PROC_ARM7)) { }

    PXI_SetFifoRecvCallback(PXI_FIFO_TAG_OS, OSi_CommonCallback);
}

ARM_FUNC static void OSi_CommonCallback(PXIFifoTag tag, u32 data, BOOL err) {
#pragma unused(tag, err) //needed because otherwise -W all errors
    u16 command = (u16)((data & OS_PXI_COMMAND_MASK) >> OS_PXI_COMMAND_SHIFT);
    if (command == OS_PXI_COMMAND_RESET)
    {
        OSi_IsResetOccurred = TRUE;
        return;
    }
    OS_Terminate();
}

ARM_FUNC static void OSi_SendToPxi(u16 data) {
    while (PXI_SendWordByFifo(PXI_FIFO_TAG_OS, (u32)data << 0x8, FALSE)) {}
}

ARM_FUNC void OS_ResetSystem(u32 parameter) {
    if (MB_IsMultiBootChild()) {
        OS_Terminate();
    }
    CARD_LockRom((u16)OS_GetLockID());
    MI_StopDma(0);
    MI_StopDma(1);
    MI_StopDma(2);
    MI_StopDma(3);
    (void)OS_SetIrqMask(0x40000);
    (void)OS_ResetRequestIrqMask((u32)~0);
    *(u32 *)HW_RESET_PARAMETER_BUF = parameter;
    OSi_SendToPxi(OS_PXI_COMMAND_RESET);
    OSi_DoResetSystem();
}

#pragma section ITCM begin
ARM_FUNC static void OSi_DoResetSystem(void)
{
    while (!OSi_IsResetOccurred) { }

    reg_OS_IME = 0;
    OSi_ReloadRomData();
    OSi_DoBoot();
}

ARM_FUNC asm void OSi_DoBoot(void)
{
    mov ip, #0x04000000
    str ip, [ip, #0x208]
    ldr r1, =SDK_AUTOLOAD_DTCM_START
    add r1, r1, #0x3fc0
    add r1, r1, #0x3c
    mov r0, #0x0
    str r0, [r1]
    ldr r1, =REG_SUBPINTF_ADDR
_01FF81D4:
    ldrh r0, [r1]
    and r0, r0, #0xf
    cmp r0, #0x1
    bne _01FF81D4
    mov r0, #0x100
    strh r0, [r1]
    mov r0, #0x0
    ldr r3, =HW_EXCP_VECTOR_MAIN
    ldr r4, [r3]
    ldr r1, =HW_BIOS_EXCP_STACK_MAIN
    mov r2, #0x80
    bl OSi_CpuClear32
    str r4, [r3]
    ldr r1, =HW_PXI_SIGNAL_PARAM_ARM9
    mov r2, #0x18
    bl OSi_CpuClear32
    ldr r1, =HW_WM_RSSI_POOL
    strh r0, [r1]
    ldr r1, =HW_COMPONENT_PARAM
    mov r2, #0x64
    bl OSi_CpuClear32
    ldr r1, =REG_SUBPINTF_ADDR
_01FF822C:
    ldrh r0, [r1]
    and r0, r0, #0xf
    cmp r0, #0x1
    beq _01FF822C
    mov r0, #0x0
    strh r0, [r1]
    ldr r3, =HW_ROM_HEADER_BUF
    ldr ip, [r3, #0x24]
    mov lr, ip
    ldr r11, =HW_PXI_SIGNAL_PARAM_ARM9
    ldmia r11, {r0-r10}
    mov r11, #0x0
    bx ip
}

ARM_FUNC static asm void OSi_CpuClear32(register u32 data, register void *destp, register u32 size)
{
    add ip, r1, r2
_01FF8284:
    cmp r1, ip
    stmltia r1!, {r0}
    blt _01FF8284
    bx lr
}

ARM_FUNC static void OSi_ReloadRomData(void)
{
    u32 header = (u32)HW_ROM_HEADER_BUF;
    const u32 rom_base = *(u32 *)HW_ROM_BASE_OFFSET_BUF;

    if (rom_base >= 0x8000)
    {
        OSi_ReadCardRom32(rom_base, (void *)header, 0x160);
    }

    u32 src_arm9 = *(u32 *)(header + 0x20);
    u32 dst_arm9 = *(u32 *)(header + 0x28);
    u32 len_arm9 = *(u32 *)(header + 0x2c);
    u32 src_arm7 = *(u32 *)(header + 0x30);
    u32 dst_arm7 = *(u32 *)(header + 0x38);
    u32 len_arm7 = *(u32 *)(header + 0x3c);

    OSIntrMode prevIntrMode = OS_DisableInterrupts();
    DC_StoreAll();
    DC_InvalidateAll();
    (void)OS_RestoreInterrupts(prevIntrMode);

    IC_InvalidateAll();
    DC_WaitWriteBufferEmpty();

    src_arm9 += rom_base;
    src_arm7 += rom_base;

    if (src_arm9 < 0x8000)
    {
        u32 diff = 0x8000 - src_arm9;
        src_arm9 = 0x8000;
        dst_arm9 += diff;
        len_arm9 -= diff;
    }
    OSi_ReadCardRom32(src_arm9, (void *)dst_arm9, (s32)len_arm9);

    OSi_ReadCardRom32(src_arm7, (void *)dst_arm7, (s32)len_arm7);
}

enum
{
    CARD_MASTER_SELECT_ROM = 0x0,
    CARD_MASTER_ENABLE = 0x80,
    CARD_CMD_READ_PAGE = 0xb7,
    CARD_CTRL_CMD_MASK = 0x07000000,
    CARD_CTRL_CMD_PAGE = 0x01000000,
    CARD_CTRL_READ = 0x00000000,
    CARD_CTRL_RESET_HI = 0x20000000,
    CARD_CTRL_START = 0x80000000,
    CARD_CTRL_READY = 0x00800000,
    CARD_ENUM_END
};

ARM_FUNC static void OSi_ReadCardRom32(u32 src, void *dst, s32 len)
{
    vu32 *const hdr_GAME_BUF = (vu32 *)(HW_ROM_HEADER_BUF + 0x60);

    const u32 ctrl_start = (u32)((*hdr_GAME_BUF &~CARD_CTRL_CMD_MASK)
                                 | (CARD_CTRL_CMD_PAGE | CARD_CTRL_READ
                                    | CARD_CTRL_START | CARD_CTRL_RESET_HI));

    s32 pos = -(s32)(src & 511);

    while (reg_CARD_CNT & CARD_CTRL_START) {}
    reg_CARD_MASTERCNT = (u32)(CARD_MASTER_SELECT_ROM | CARD_MASTER_ENABLE);

    for (src = (u32)(src + pos); pos < len; src += 512)
    {
        (&reg_CARD_CMD)[0] = (u8)(CARD_CMD_READ_PAGE);
        (&reg_CARD_CMD)[1] = (u8)(src >> 24);
        (&reg_CARD_CMD)[2] = (u8)(src >> 16);
        (&reg_CARD_CMD)[3] = (u8)(src >> 8);
        (&reg_CARD_CMD)[4] = (u8)(src >> 0);
        (&reg_CARD_CMD)[5] = 0;
        (&reg_CARD_CMD)[6] = 0;
        (&reg_CARD_CMD)[7] = 0;

        reg_CARD_CNT = ctrl_start;
        for (;;)
        {
            u32 ctrl = reg_CARD_CNT;

            if ((ctrl & CARD_CTRL_READY))
            {
                const u32 data = reg_CARD_DATA;

                if ((pos >= 0) && (pos < len))
                {
                    *(u32 *)((u32)dst + pos) = data;
                }

                pos += sizeof(u32);
            }

            if (!(ctrl & CARD_CTRL_START))
            {
                break;
            }
        }
    }
}
#pragma section ITCM end
