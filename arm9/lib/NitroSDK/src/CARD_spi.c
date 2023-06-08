#include "nitro/types.h"
#include "CARD_common.h"
#include "CARD_spi.h"
#include "MI_memory.h"
#include "code32.h"

extern CARDiCommon cardi_common;

void CARDi_IdentifyBackupCore(CARDBackupType type)
{
    CARDiCommandArg *const p = cardi_common.cmd;

    MI_CpuFill8(&p->spec, 0, sizeof(p->spec));
    p->type = type;
    p->spec.caps = CARD_BACKUP_CAPS_AVAILABLE;
    if (type != CARD_BACKUP_TYPE_NOT_USE)
    {
        const u32 size = (u32)(1 << ((type >> CARD_BACKUP_TYPE_SIZEBIT_SHIFT) & CARD_BACKUP_TYPE_SIZEBIT_MASK));

        const s32 device = ((type >> CARD_BACKUP_TYPE_DEVICE_SHIFT) & CARD_BACKUP_TYPE_DEVICE_MASK);

        p->spec.total_size = size;
        p->spec.initial_status = 0xFF;
        if (device == CARD_BACKUP_TYPE_DEVICE_EEPROM)
        {
            switch (size)
            {
                default:
                    goto invalid_type;
                case 0x000200: //CARD_BACKUP_TYPE_EEPROM_4KBITS
                    p->spec.page_size = 0x10;
                    p->spec.addr_width = 1;
                    p->spec.program_page = 5;
                    p->spec.initial_status = 0xF0;
                    break;
                case 0x002000: //CARD_BACKUP_TYPE_EEPROM_64KIBTS
                    p->spec.page_size = 0x0020;
                    p->spec.addr_width = 2;
                    p->spec.program_page = 5;
                    p->spec.initial_status = 0x00;
                    break;
                case 0x010000: //CARD_BACKUP_TYPE_EEPROM_512KBITS
                    p->spec.page_size = 0x0080;
                    p->spec.addr_width = 2;
                    p->spec.program_page = 10;
                    p->spec.initial_status = 0x00;
                    break;
            }
            p->spec.sect_size = p->spec.page_size;
            p->spec.caps |= CARD_BACKUP_CAPS_READ;
            p->spec.caps |= CARD_BACKUP_CAPS_PROGRAM;
            p->spec.caps |= CARD_BACKUP_CAPS_VERIFY;
        }
        else if (device == CARD_BACKUP_TYPE_DEVICE_FLASH)
        {
            switch (size)
            {
                default:
                    goto invalid_type;
                case 0x040000: //CARD_BACKUP_TYPE_FLASH_2MBITS
                case 0x080000: //CARD_BACKUP_TYPE_FLASH_4MBITS
                case 0x100000: //CARD_BACKUP_TYPE_FLASH_8MBITS
                    p->spec.write_page = 25;
                    p->spec.write_page_total = 300;
                    p->spec.erase_page = 300;
                    p->spec.erase_sector = 5000;
                    p->spec.caps |= CARD_BACKUP_CAPS_WRITE;
                    p->spec.caps |= CARD_BACKUP_CAPS_ERASE_PAGE;
                    break;
                case 0x200000: //CARD_BACKUP_TYPE_FLASH_16MBITS
                    p->spec.erase_sector = 1000;
                    p->spec.erase_sector_total = 3000;
                    p->spec.erase_chip = 17000;
                    p->spec.erase_chip_total = 40000;
                    p->spec.initial_status = 0x00;
                    p->spec.caps |= CARD_BACKUP_CAPS_ERASE_CHIP;
                    break;
                case 0x800000: //CARD_BACKUP_TYPE_FLASH_64MBITS
                    p->spec.erase_sector = 1000;
                    p->spec.erase_sector_total = 3000;
                    p->spec.erase_chip = 68000;
                    p->spec.erase_chip_total = 160000;
                    p->spec.initial_status = 0x00;
                    p->spec.caps |= CARD_BACKUP_CAPS_ERASE_CHIP;
                    break;
            }
            p->spec.sect_size = 0x010000;
            p->spec.page_size = 0x0100;
            p->spec.addr_width = 3;
            p->spec.program_page = 5;
            p->spec.caps |= CARD_BACKUP_CAPS_READ;
            p->spec.caps |= CARD_BACKUP_CAPS_PROGRAM;
            p->spec.caps |= CARD_BACKUP_CAPS_VERIFY;
            p->spec.caps |= CARD_BACKUP_CAPS_ERASE_SECTOR;
        }
        else if (device == CARD_BACKUP_TYPE_DEVICE_FRAM)
        {
            switch (size)
            {
                default:
                    goto invalid_type;
                case 0x002000: //CARD_BACKUP_TYPE_FRAM_64KBITS
                case 0x008000: //CARD_BACKUP_TYPE_FRAM_64KBITS
                    break;
            }
            p->spec.page_size = size;
            p->spec.sect_size = size;
            p->spec.addr_width = 2;
            p->spec.initial_status = 0x00;
            p->spec.caps |= CARD_BACKUP_CAPS_READ;
            p->spec.caps |= CARD_BACKUP_CAPS_PROGRAM;
            p->spec.caps |= CARD_BACKUP_CAPS_VERIFY;
        }
        else
        {
            invalid_type:
            p->type = CARD_BACKUP_TYPE_NOT_USE;
            p->spec.total_size = 0;
            cardi_common.cmd->result = CARD_RESULT_UNSUPPORTED;
            return;
        }
    }
}
