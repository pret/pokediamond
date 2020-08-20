#ifndef NITRO_CARD_COMMON_H_
#define NITRO_CARD_COMMON_H_

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
}
CARDResult;

typedef enum
{
    CARD_REQ_INIT = 0,                 /* initialize (setting from ARM9)*/
    CARD_REQ_ACK,                      /* request done (acknowledge from ARM7)*/
    CARD_REQ_IDENTIFY,                 /* CARD_IdentifyBackup*/
    CARD_REQ_READ_ID,                  /* CARD_ReadRomID (TEG && ARM9)*/
    CARD_REQ_READ_ROM,                 /* CARD_ReadRom (TEG && ARM9)*/
    CARD_REQ_WRITE_ROM,                /* (reserved)*/
    CARD_REQ_READ_BACKUP,              /* CARD_ReadBackup*/
    CARD_REQ_WRITE_BACKUP,             /* CARD_WriteBackup*/
    CARD_REQ_PROGRAM_BACKUP,           /* CARD_ProgramBackup*/
    CARD_REQ_VERIFY_BACKUP,            /* CARD_VerifyBackup*/
    CARD_REQ_ERASE_PAGE_BACKUP,        /* CARD_EraseBackupPage*/
    CARD_REQ_ERASE_SECTOR_BACKUP,      /* CARD_EraseBackupSector*/
    CARD_REQ_ERASE_CHIP_BACKUP,        /* CARD_EraseBackupChip*/
    CARD_REQ_MAX
}
CARDRequest;

typedef enum
{
    CARD_REQUEST_MODE_RECV,            /* Data reception*/
    CARD_REQUEST_MODE_SEND,            /* Send data (Including single verify)*/
    CARD_REQUEST_MODE_SEND_VERIFY,     /* Send data + verify*/
    CARD_REQUEST_MODE_SPECIAL          /* special operations like sector deletion*/
}
CARDRequestMode;

CARDResult CARD_GetResultCode(void);

#define CARD_RETRY_COUNT_MAX 10

void CARD_Init(void);

#endif //NITRO_CARD_COMMON_H_
