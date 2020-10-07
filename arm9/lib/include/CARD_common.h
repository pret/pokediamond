#ifndef POKEDIAMOND_CARD_COMMON_H
#define POKEDIAMOND_CARD_COMMON_H

#include "nitro/types.h"
#include "OS_thread.h"
#include "MI_dma.h"

#define	CARD_THREAD_PRIORITY_DEFAULT	4

#define	CARD_BACKUP_TYPE_DEVICE_SHIFT	0
#define	CARD_BACKUP_TYPE_DEVICE_EEPROM	1
#define	CARD_BACKUP_TYPE_DEVICE_FLASH	2
#define	CARD_BACKUP_TYPE_DEVICE_FRAM	3
#define	CARD_BACKUP_TYPE_SIZEBIT_SHIFT	8
#define	CARD_BACKUP_TYPE_VENDER_SHIFT	16
#define	CARD_BACKUP_TYPE_DEFINE(type, size, vender)	\
	(((CARD_BACKUP_TYPE_DEVICE_ ## type) << CARD_BACKUP_TYPE_DEVICE_SHIFT) |	\
	((size) << CARD_BACKUP_TYPE_SIZEBIT_SHIFT) |	\
	((vender) << CARD_BACKUP_TYPE_VENDER_SHIFT))

typedef enum
{
    CARD_BACKUP_TYPE_EEPROM_4KBITS = CARD_BACKUP_TYPE_DEFINE(EEPROM, 9, 0),
    CARD_BACKUP_TYPE_EEPROM_64KBITS = CARD_BACKUP_TYPE_DEFINE(EEPROM, 13, 0),
    CARD_BACKUP_TYPE_EEPROM_512KBITS = CARD_BACKUP_TYPE_DEFINE(EEPROM, 16, 0),
    CARD_BACKUP_TYPE_FLASH_2MBITS = CARD_BACKUP_TYPE_DEFINE(FLASH, 18, 0),
    CARD_BACKUP_TYPE_FLASH_4MBITS = CARD_BACKUP_TYPE_DEFINE(FLASH, 19, 0),
    CARD_BACKUP_TYPE_FLASH_8MBITS = CARD_BACKUP_TYPE_DEFINE(FLASH, 20, 0),
    CARD_BACKUP_TYPE_FRAM_256KBITS = CARD_BACKUP_TYPE_DEFINE(FRAM, 15, 0),
    CARD_BACKUP_TYPE_NOT_USE = 0
} CARDBackupType;

typedef enum
{
    CARD_RESULT_SUCCESS = 0,
    CARD_RESULT_FAILURE,
    CARD_RESULT_INVALID_PARAM,
    CARD_RESULT_UNSUPPORTED,
    CARD_RESULT_TIMEOUT,
    CARD_RESULT_ERROR,
    CARD_RESULT_NO_RESPONSE,
    CARD_RESULT_CANCELED
} CARDResult;

typedef enum
{
    CARD_TARGET_NONE,
    CARD_TARGET_ROM,
    CARD_TARGET_BACKUP
} CARDTargetMode;

typedef enum
{
    CARD_REQ_INIT = 0,
    CARD_REQ_ACK,
    CARD_REQ_IDENTIFY,
    CARD_REQ_READ_ID,
    CARD_REQ_READ_ROM,
    CARD_REQ_WRITE_ROM,
    CARD_REQ_READ_BACKUP,
    CARD_REQ_WRITE_BACKUP,
    CARD_REQ_PROGRAM_BACKUP,
    CARD_REQ_VERIFY_BACKUP,
    CARD_REQ_ERASE_PAGE_BACKUP,
    CARD_REQ_ERASE_SECTOR_BACKUP,
    CARD_REQ_ERASE_CHIP_BACKUP,
    CARD_REQ_MAX
} CARDRequest;

typedef enum
{
    CARD_REQUEST_MODE_RECV,
    CARD_REQUEST_MODE_SEND,
    CARD_REQUEST_MODE_SEND_VERIFY,
    CARD_REQUEST_MODE_SPECIAL
} CARDRequestMode;

enum
{
    CARD_STAT_INIT = (1 << 0),
    CARD_STAT_INIT_CMD = (1 << 1),
    CARD_STAT_BUSY = (1 << 2),
    CARD_STAT_TASK = (1 << 3),
    CARD_STAT_RECV = (1 << 4),
    CARD_STAT_REQ = (1 << 5),
    CARD_STAT_CANCEL = (1 << 6)
};

typedef s32 CARDiOwner;

typedef struct CARDiCommandArg
{
    CARDResult result;
    CARDBackupType type;
    u32 id;
    u32 src;
    u32 dest;
    u32 len;

    struct
    {
        u32 total_size;
        u32 sect_size;
        u32 page_size;
        u32 addr_width;
        u32 program_page;
        u32 write_page;
        u32 write_page_total;
        u32 erase_chip;
        u32 erase_chip_total;
        u32 erase_sector;
        u32 erase_sector_total;
        u32 erase_page;
        u8 initial_status;
        u8 padding1[3];
        u32 caps;
        u8 padding2[16];
    } spec;
} CARDiCommandArg;

typedef struct CARDiCommon
{
    CARDiCommandArg *cmd;
    s32 command;

    volatile CARDiOwner lock_owner;
    volatile s32 lock_ref;
    OSThreadQueue lock_queue[1];
    CARDTargetMode lock_target;

    u32 src;
    u32 dst;
    u32 len;
    u32 dma;
    CARDRequest req_type;
    s32 req_retry;
    CARDRequestMode req_mode;
    MIDmaCallback callback;
    void *callback_arg;
    void (*task_func) (struct CARDiCommon *);

    OSThread thread[1];
    OSThread *cur_th;

    u32 priority;
    OSThreadQueue busy_q[1];

    volatile u32 flag;

    u8 dummy[8];

    u8 backup_cache_page_buf[256] ALIGN(32);
} CARDiCommon;

void CARDi_SetTask(void (*task) (CARDiCommon *));
void CARDi_InitCommon(void);
BOOL CARD_IsEnabled(void);
void CARD_CheckEnabled(void);
void CARD_Enable(BOOL enable);
BOOL CARDi_WaitAsync(void);
BOOL CARDi_TryWaitAsync(void);
CARDResult CARD_GetResultCode(void);
void CARD_LockRom(u16 lock_id);
void CARD_UnlockRom(u16 lock_id);
void CARD_LockBackup(u16 lock_id);
void CARD_UnlockBackup(u16 lock_id);

#define CARD_RETRY_COUNT_MAX 10

void CARD_Init(void);

#endif //POKEDIAMOND_CARD_COMMON_H
