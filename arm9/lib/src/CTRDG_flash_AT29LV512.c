#include "CTRDG_flash_AT29LV512.h"
#include "function_target.h"
#include "CTRDG_backup.h"
#include "CTRDG_flash.h"
#include "MI_exMemory.h"
#include "OS_interrupt.h"
#include "OS_spinLock.h"

#define CTRDG_BACKUP_COM_ADR1   (CTRDG_AGB_FLASH_ADR+0x00005555)
#define CTRDG_BACKUP_COM_ADR2   (CTRDG_AGB_FLASH_ADR+0x00002aaa)

extern u16 ctrdgi_flash_lock_id;
extern BOOL ctrdgi_backup_irq;

extern u16 CTRDGi_PollingSR512kCOMMON(u16 phase, u8 *adr, u16 lastData);

extern u16 CTRDGi_EraseFlashChipAT(void);
extern u16 CTRDGi_EraseFlashSectorAT(u16 p_secNo);
extern u16 CTRDGi_EraseFlash4KBAT(u16 l_secNo);
extern u16 CTRDGi_WriteFlashSectorAT(u16 p_secNo, u8 *src);
extern u16 CTRDGi_WriteFlash4KBAT(u16 l_secNo, u8 *src);

extern void CTRDGi_EraseFlashChipAsyncAT(CTRDG_TASK_FUNC callback);
extern void CTRDGi_EraseFlash4KBAsyncAT(u16 secNo, CTRDG_TASK_FUNC callback);
extern void CTRDGi_WriteFlash4KBAsyncAT(u16 secNo, u8 *src, CTRDG_TASK_FUNC callback);
extern void CTRDGi_EraseFlashSectorAsyncAT(u16 secNo, CTRDG_TASK_FUNC callback);
extern void CTRDGi_WriteFlashSectorAsyncAT(u16 secNo, u8 *src, CTRDG_TASK_FUNC callback);

static const u16 atMaxTime[] = {
        10, 40, 0, 40
};

const CTRDGiFlashTypePlus AT29LV512_lib = {
        CTRDGi_WriteFlash4KBAT,
        CTRDGi_EraseFlashChipAT,
        CTRDGi_EraseFlash4KBAT,
        CTRDGi_WriteFlash4KBAsyncAT,
        CTRDGi_EraseFlashChipAsyncAT,
        CTRDGi_EraseFlash4KBAsyncAT,
        CTRDGi_PollingSR512kCOMMON,
        atMaxTime,
        {
                0x00010000, //ROM size
                {0x00001000, 12, 16, 0}, //sector
                {MI_CTRDG_RAMCYCLE_18, MI_CTRDG_RAMCYCLE_18}, //read cycle and write cycle
                0x1f, //maker ID
                0x3d, //device ID
        }
};

const CTRDGiFlashTypePlus AT29LV512_org = {
        CTRDGi_WriteFlashSectorAT,
        CTRDGi_EraseFlashChipAT,
        CTRDGi_EraseFlashSectorAT,
        CTRDGi_WriteFlashSectorAsyncAT,
        CTRDGi_EraseFlashChipAsyncAT,
        CTRDGi_EraseFlashSectorAsyncAT,
        CTRDGi_PollingSR512kCOMMON,
        atMaxTime,
        {
                0x00010000, //ROM size
                {0x00000080, 7, 512, 0}, //sector
                {MI_CTRDG_RAMCYCLE_18, MI_CTRDG_RAMCYCLE_18}, //read cycle and write cycle
                0x1f, //maker ID
                0x3d, //device ID
        }
};

ARM_FUNC u32 CTRDGi_EraseFlashChipCoreAT(CTRDGTaskInfo *arg)
{
    MICartridgeRamCycle ram_cycle;
    u32 result;
    (void)arg;

    (void)OS_LockCartridge(ctrdgi_flash_lock_id);

    ram_cycle = MI_GetCartridgeRamCycle();
    MI_SetCartridgeRamCycle(AgbFlash->agbWait[0]);

    ctrdgi_backup_irq = OS_DisableIrq();

    *(vu8 *)CTRDG_BACKUP_COM_ADR1 = 0xaa;
    *(vu8 *)CTRDG_BACKUP_COM_ADR2 = 0x55;
    *(vu8 *)CTRDG_BACKUP_COM_ADR1 = 0x80;
    *(vu8 *)CTRDG_BACKUP_COM_ADR1 = 0xaa;
    *(vu8 *)CTRDG_BACKUP_COM_ADR2 = 0x55;
    *(vu8 *)CTRDG_BACKUP_COM_ADR1 = 0x10;

    (void)OS_RestoreIrq(ctrdgi_backup_irq);

    result = CTRDGi_PollingSR(CTRDG_BACKUP_PHASE_CHIP_ERASE, (u8 *)CTRDG_AGB_FLASH_ADR, 0xff);

    MI_SetCartridgeRamCycle(ram_cycle);

    (void)OS_UnlockCartridge(ctrdgi_flash_lock_id);

    return result;
}

ARM_FUNC u32 CTRDGi_EraseFlashSectorCoreAT(CTRDGTaskInfo *arg)
{
    u32 i;
    u8 *dst;
    BOOL shlet_ime;
    MICartridgeRamCycle ram_cycle;
    u32 result;
    CTRDGTaskInfo p = *arg;
    u16 p_secNo = p.sec_num;

    dst = (u8 *)(CTRDG_AGB_FLASH_ADR + (p_secNo << AT29LV512_org.type.sector.shift));

    (void)OS_LockCartridge(ctrdgi_flash_lock_id);

    ram_cycle = MI_GetCartridgeRamCycle();
    MI_SetCartridgeRamCycle(AgbFlash->agbWait[0]);

    shlet_ime = OS_DisableIrq();

    *(vu8 *)CTRDG_BACKUP_COM_ADR1 = 0xaa;
    *(vu8 *)CTRDG_BACKUP_COM_ADR2 = 0x55;
    *(vu8 *)CTRDG_BACKUP_COM_ADR1 = 0xa0;

    for (i = AT29LV512_org.type.sector.size; i > 0; i--)
    {
        *dst++ = 0xff;
    }
    dst--;

    (void)OS_RestoreIrq(shlet_ime);

    result = CTRDGi_PollingSR(CTRDG_BACKUP_PHASE_PROGRAM, dst, 0xff);

    if (result)
    {
        result = (u16)((result & 0xff00) | CTRDG_BACKUP_PHASE_SECTOR_ERASE);
    }

    MI_SetCartridgeRamCycle(ram_cycle);

    (void)OS_UnlockCartridge(ctrdgi_flash_lock_id);

    return result;
}
