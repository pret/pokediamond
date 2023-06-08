#include "consts.h"
#include "OS_interrupt.h"
#include "OS_system.h"
#include "PXI_fifo.h"
#include "systemWork.h"
#include "code32.h"

static u16 FifoCtrlInit = 0;
static PXIFifoCallback FifoRecvCallbackTable[PXI_MAX_FIFO_TAG];

static inline PXIFifoStatus PXIi_SetToFifo(u32 data);

void PXI_InitFifo(void)
{
    OSSystemWork *p = OS_GetSystemWork();
    OSIntrMode enabled = OS_DisableInterrupts();
    s32 i;

    if (!FifoCtrlInit)
    {
        FifoCtrlInit = TRUE;

        p->pxiHandleChecker[PXI_PROC_ARM9] = 0UL;

        for (i = 0; i < PXI_MAX_FIFO_TAG; i++)
        {
            FifoRecvCallbackTable[i] = NULL;
        }

        reg_PXI_SUBP_FIFO_CNT = (REG_PXI_SUBP_FIFO_CNT_SEND_CL_MASK
                                 | REG_PXI_SUBP_FIFO_CNT_RECV_RI_MASK | REG_PXI_SUBP_FIFO_CNT_E_MASK | REG_PXI_SUBP_FIFO_CNT_ERR_MASK);

        (void)OS_ResetRequestIrqMask(OS_IE_SPFIFO_RECV);
        (void)OS_SetIrqFunction(OS_IE_SPFIFO_RECV, PXIi_HandlerRecvFifoNotEmpty);
        (void)OS_EnableIrqMask(OS_IE_SPFIFO_RECV);

        {
            s32 timeout;
            s32 c;

            for (i = 0; ; i++)
            {
                c = reg_PXI_SUBPINTF & 15;
                reg_PXI_SUBPINTF = (u16)(c << 8);

                if (c == 0 && i > 4)
                {
                    break;
                }

                for (timeout = 1000; (reg_PXI_SUBPINTF & 15) == c; timeout--)
                {
                    if (timeout == 0)
                    {
                        i = 0;
                        break;
                    }
                }
            }
        }
    }
    (void)OS_RestoreInterrupts(enabled);
}

void PXI_SetFifoRecvCallback(s32 fifotag, PXIFifoCallback callback)
{
    OSSystemWork *p = OS_GetSystemWork();
    OSIntrMode enabled = OS_DisableInterrupts();

    FifoRecvCallbackTable[fifotag] = callback;
    if (callback)
    {
        p->pxiHandleChecker[PXI_PROC_ARM9] |= (1UL << fifotag);
    }
    else
    {
        p->pxiHandleChecker[PXI_PROC_ARM9] &= ~(1UL << fifotag);
    }
    (void)OS_RestoreInterrupts(enabled);
}

BOOL PXI_IsCallbackReady(s32 fifotag, PXIProc proc)
{
    OSSystemWork *p = OS_GetSystemWork();

    return (p->pxiHandleChecker[proc] & (1UL << fifotag)) ? TRUE : FALSE;
}

s32 PXI_SendWordByFifo(s32 fifotag, u32 data, BOOL err)
{
    PXIFifoMessage fifomsg;

    fifomsg.e.tag = (PXIFifoTag)fifotag;
    fifomsg.e.err = (u32)err;
    fifomsg.e.data = data;

    return PXIi_SetToFifo(fifomsg.raw);
}

static inline PXIFifoStatus PXIi_SetToFifo(u32 data)
{
    if (reg_PXI_SUBP_FIFO_CNT & REG_PXI_SUBP_FIFO_CNT_ERR_MASK)
    {
        reg_PXI_SUBP_FIFO_CNT |= (REG_PXI_SUBP_FIFO_CNT_E_MASK | REG_PXI_SUBP_FIFO_CNT_ERR_MASK);
        return PXI_FIFO_FAIL_SEND_ERR;
    }

    OSIntrMode enabled = OS_DisableInterrupts();
    if (reg_PXI_SUBP_FIFO_CNT & REG_PXI_SUBP_FIFO_CNT_SEND_FULL_MASK)
    {
        (void)OS_RestoreInterrupts(enabled);
        return PXI_FIFO_FAIL_SEND_FULL;
    }

    reg_PXI_SEND_FIFO = data;
    (void)OS_RestoreInterrupts(enabled);
    return PXI_FIFO_SUCCESS;
}

static inline PXIFifoStatus PXIi_GetFromFifo(u32 *data_buf)
{
    if (reg_PXI_SUBP_FIFO_CNT & REG_PXI_SUBP_FIFO_CNT_ERR_MASK)
    {
        reg_PXI_SUBP_FIFO_CNT |= (REG_PXI_SUBP_FIFO_CNT_E_MASK | REG_PXI_SUBP_FIFO_CNT_ERR_MASK);
        return PXI_FIFO_FAIL_RECV_ERR;
    }

    OSIntrMode enabled = OS_DisableInterrupts();
    if (reg_PXI_SUBP_FIFO_CNT & REG_PXI_SUBP_FIFO_CNT_RECV_EMP_MASK)
    {
        (void)OS_RestoreInterrupts(enabled);
        return PXI_FIFO_FAIL_RECV_EMPTY;
    }


    *data_buf = reg_PXI_RECV_FIFO;
    (void)OS_RestoreInterrupts(enabled);

    return PXI_FIFO_SUCCESS;
}

void PXIi_HandlerRecvFifoNotEmpty(void)
{
    PXIFifoMessage fifomsg;
    PXIFifoStatus ret_code;
    PXIFifoTag tag;

    while (TRUE)
    {
        ret_code = PXIi_GetFromFifo(&fifomsg.raw);

        if (ret_code == PXI_FIFO_FAIL_RECV_EMPTY)
        {
            break;
        }
        if (ret_code == PXI_FIFO_FAIL_RECV_ERR)
        {
            continue;
        }

        tag = (PXIFifoTag)fifomsg.e.tag;

        if (tag)
        {
            if (FifoRecvCallbackTable[tag])
            {
                (FifoRecvCallbackTable[tag])(tag, fifomsg.e.data, (BOOL)fifomsg.e.err);
            }
            else
            {
                if (fifomsg.e.err)
                {
                }
                else
                {
                    fifomsg.e.err = TRUE;
                    (void)PXIi_SetToFifo(fifomsg.raw);
                }
            }
        }
        else
        {
        }
    }
}
