#include "nitro.h"
#include "MI_uncompress.h"
#include "code32.h"

extern void NitroMain(void);
extern void SDK_IRQ_STACKSIZE(void);
extern void SDK_AUTOLOAD_START(void);
extern void SDK_AUTOLOAD_LIST(void);
extern void SDK_AUTOLOAD_LIST_END(void);
extern void SDK_STATIC_BSS_START(void);
extern void SDK_STATIC_BSS_END(void);
extern void OS_IrqHandler(void);

extern void *const _start_ModuleParams[];

static void init_cp15(void);
static void do_autoload(void);
static void INITi_CpuClear32(register u32 data, register void *destp, register u32 size);
void _start_AutoloadDoneCallback(void *argv[]);

extern void __call_static_initializers(void);
extern void _fp_init(void);
void NitroStartUp(void);
void _start(void);

#define SDK_VERSION_ID ((3 << 24) | (2 << 16) | 30001)
#define SDK_NITROCODE_LE 0x2106c0de
#define SDK_NITROCODE_BE 0xdec00621

asm void _start(void)
{
    //set IME to 0
    mov r12, #0x4000000
    str r12, [r12, #0x208]

    //adjust VCOUNT
_02000808:
    ldrh r0, [r12, #6]
    cmp r0, #0
    bne _02000808

    //init cp15
    bl init_cp15

    //init stack pointer
    //SVC mode
    mov r0, #OS_PROCMODE_SVC
    msr CPSR_c, r0
    ldr r0, =SDK_AUTOLOAD_DTCM_START
    add r0, r0, #0x3fc0
    mov sp, r0

    //IRQ mode
    mov r0, #OS_PROCMODE_IRQ
    msr CPSR_c, r0
    ldr r0, =SDK_AUTOLOAD_DTCM_START
    add r0, r0, #0x3fc0
    sub r0, r0, #HW_SVC_STACK_SIZE
    sub sp, r0, #4
    tst sp, #4
    subeq sp, sp, #4

    //system mode
    ldr r1, =SDK_IRQ_STACKSIZE
    sub r1, r0, r1
    mov r0, #OS_PROCMODE_SYS
    msr CPSR_csfx, r0
    sub sp, r1, #4

    //clear memory
    //DTCM
    mov r0, #0
    ldr r1, =SDK_AUTOLOAD_DTCM_START
    mov r2, #HW_DTCM_SIZE
    bl INITi_CpuClear32

    //BG/OBJ palette
    mov r0, #0
    ldr r1, =HW_PLTT
    mov r2, #HW_PLTT_SIZE
    bl INITi_CpuClear32

    //OAM
    mov r0, #0x0200
    ldr r1, =HW_OAM
    mov r2, #HW_OAM_SIZE
    bl INITi_CpuClear32

    //load autoload block and init bss
    ldr r1, =_start_ModuleParams
    ldr r0, [r1, #20]
    bl MIi_UncompressBackward
    bl do_autoload

    //fill static bss with 0
    ldr r0, =_start_ModuleParams
    ldr r1, [r0, #12]
    ldr r2, [r0, #16]
    mov r3, r1
    mov r0, #0
_020008B4:
    cmp r1, r2
    strcc r0, [r1], #4
    bcc _020008B4

    //flush static bss region
    bic r1, r3, #HW_CACHE_LINE_SIZE - 1
_020008C4:
    mcr p15, 0, r0, c7, c10, 4 //Drain Write Buffer
    mcr p15, 0, r1, c7, c5, 1 //Invalidate Instruction Cache Line VA
    mcr p15, 0, r1, c7, c14, 1 //Clean and Invalidate Data Cache Line VA
    add r1, r1, #HW_CACHE_LINE_SIZE
    cmp r1, r2
    blt _020008C4

    //print buffer
    ldr r1, =HW_COMPONENT_PARAM
    str r0, [r1, #0]

    //set interrput vector
    ldr r1, =SDK_AUTOLOAD_DTCM_START
    add r1, r1, #0x3fc0
    add r1, r1, #HW_DTCM_SYSRV_OFS_INTR_VECTOR
    ldr r0, =OS_IrqHandler
    str r0, [r1, #0]

    bl _fp_init
    bl NitroStartUp
    bl __call_static_initializers

    //start
    ldr r1, =NitroMain
    ldr lr, =HW_RESET_VECTOR

    tst sp, #4
    subne sp, sp, #4
    bx r1
}

static asm void INITi_CpuClear32(register u32 data, register void *destp, register u32 size)
{
    add r12, r1, r2
_02000940:
    cmp r1, r12
    stmltia r1!, {r0}
    blt _02000940
    bx lr
}

void   *const _start_ModuleParams[] = {
        (void *)SDK_AUTOLOAD_LIST,
        (void *)SDK_AUTOLOAD_LIST_END,
        (void *)SDK_AUTOLOAD_START,
        (void *)SDK_STATIC_BSS_START,
        (void *)SDK_STATIC_BSS_END,
        (void *)0,                         // CompressedStaticEnd
        (void *)SDK_VERSION_ID,            // SDK version info
        (void *)SDK_NITROCODE_BE,          // Checker 1
        (void *)SDK_NITROCODE_LE,          // Checker 2
};

asm void MIi_UncompressBackward(register void *bottom)
{
    cmp r0, #0
    beq _020009F8
    stmfd sp!, {r4-r7}
    ldmdb r0, {r1-r2}
    add r2, r0, r2
    sub r3, r0, r1, lsr #24
    bic r1, r1, #0xff000000
    sub r1, r0, r1
    mov r4, r2
_02000974:
    cmp r3, r1
    ble _020009D4
    ldrb r5, [r3, #-1]!
    mov r6, #8
_02000984:
    subs r6, r6, #1
    blt _02000974
    tst r5, #0x80
    bne _020009A0

    ldrb r0, [r3, #-1]!
    strb r0, [r2, #-1]!
    b _020009C8
_020009A0:
    ldrb r12, [r3, #-1]!
    ldrb r7, [r3, #-1]!
    orr r7, r7, r12, lsl #8
    bic r7, r7, #0xf000
    add r7, r7, #0x0002
    add r12, r12, #0x0020
_020009B8:
    ldrb r0, [r2, r7]
    strb r0, [r2, #-1]!
    subs r12, r12, #0x0010
    bge _020009B8
_020009C8:
    cmp r3, r1
    mov r5, r5, lsl #1
    bgt _02000984
_020009D4:
    mov r0, #0
    bic r3, r1, #HW_CACHE_LINE_SIZE - 1
_020009DC:
    mcr p15, 0, r0, c7, c10, 4 //Drain Write Buffer
    mcr p15, 0, r3, c7, c5, 1 //Invalidate Instruction Cache Line VA
    mcr p15, 0, r3, c7, c14, 1 //Clean and Invalidate Data Cache Line VA
    add r3, r3, #HW_CACHE_LINE_SIZE
    cmp r3, r4
    blt _020009DC

    ldmfd sp!, {r4-r7}
_020009F8:
    bx lr
}

static asm void do_autoload(void)
{
    ldr r0, =_start_ModuleParams
    ldr r1, [r0, #0]
    ldr r2, [r0, #4]
    ldr r3, [r0, #8]

_02000A0C:
    cmp r1, r2
    beq _02000A6C

    ldr r5, [r1], #4
    ldr r7, [r1], #4
    add r6, r5, r7
    mov r4, r5
_02000A24:
    cmp r4, r6
    ldrmi r7, [r3], #4
    strmi r7, [r4], #4
    bmi _02000A24

    //fill bss with 0
    ldr r7, [r1], #4
    add r6, r4, r7
    mov r7, #0
_02000A40:
    cmp r4, r6
    strcc r7, [r4], #4
    bcc _02000A40

    bic r4, r5, #HW_CACHE_LINE_SIZE - 1
_02000A50:
    mcr p15, 0, r7, c7, c10, 4 //Drain Write Buffer
    mcr p15, 0, r4, c7, c5, 1 //Invalidate Instruction Cache Line VA
    mcr p15, 0, r4, c7, c14, 1 //Clean and Invalidate Data Cache Line VA
    add r4, r4, #HW_CACHE_LINE_SIZE
    cmp r4, r6
    blt _02000A50

    b _02000A0C

_02000A6C:
    b _start_AutoloadDoneCallback
}

asm void _start_AutoloadDoneCallback(void *argv[])
{
    bx lr
}

#define SET_PROTECTION_A(id, addr, size)        ldr r0, =(addr|HW_C6_PR_##size|HW_C6_PR_ENABLE)
#define SET_PROTECTION_B(id, addr, size)        mcr p15, 0, r0, c6, id, 0
#define REGION_BIT(a,b,c,d,e,f,g,h)     (((a)<<0)|((b)<<1)|((c)<<2)|((d)<<3)|((e)<<4)|((f)<<5)|((g)<<6)|((h)<<7))
#define REGION_ACC(a,b,c,d,e,f,g,h)     (((a)<<0)|((b)<<4)|((c)<<8)|((d)<<12)|((e)<<16)|((f)<<20)|((g)<<24)|((h)<<28))
static asm void init_cp15(void)
{
    //Disable TCM/Cache/Protection Unit
    mrc p15, 0, r0, c1, c0, 0 //Save Control Register

    /*
     * The following bits are disabled
     * * Instruction Cache
     * * Data/Unified Cache
     * * ITCM
     * * DTCM
     * * ITCM Load Mode
     * * DTCM Load Mode
     * * LD Interwork Disable
     * * Protection Unit Enable
     */
    ldr r1, =0x000f9005
    bic r0, r0, r1
    mcr p15, 0, r0, c1, c0, 0 //Set Control Register

    //Disable Cache
    mov r0, #0
    mcr p15, 0, r0, c7, c5, 0 //Invalidate Entire Instruction Cache
    mcr p15, 0, r0, c7, c6, 0 //Invalidate Entire Data Cache

    mcr p15, 0, r0, c7, c10, 4 //Drain Write Buffer

    SET_PROTECTION_A(c0, HW_IOREG, 64MB) //Protection Unit Unified Region
    SET_PROTECTION_B(c0, HW_IOREG, 64MB)

    SET_PROTECTION_A(c1, HW_MAIN_MEM, 8MB)
    SET_PROTECTION_B(c1, HW_MAIN_MEM, 8MB)

    SET_PROTECTION_A(c2, HW_MAIN_MEM_SUB, 128KB)
    SET_PROTECTION_B(c2, HW_MAIN_MEM_SUB, 128KB)

    SET_PROTECTION_A(c3, HW_CTRDG_ROM, 128MB)
    SET_PROTECTION_B(c3, HW_CTRDG_ROM, 128MB)

    ldr r0, =SDK_AUTOLOAD_DTCM_START
    orr r0, r0, #0x1a
    orr r0, r0, #1
    SET_PROTECTION_B(c4, HW_DTCM, 16KB)

    SET_PROTECTION_A(c5, HW_ITCM_IMAGE, 16MB)
    SET_PROTECTION_B(c5, HW_ITCM_IMAGE, 16MB)

    SET_PROTECTION_A(c6, HW_BIOS, 32KB)
    SET_PROTECTION_B(c6, HW_BIOS, 32KB)

    SET_PROTECTION_A(c7, HW_MAIN_MEM_SHARED, 4KB)
    SET_PROTECTION_B(c7, HW_MAIN_MEM_SHARED, 4KB)

    mov r0, #HW_C9_TCMR_32MB
    mcr p15, 0, r0, c9, c1, 1 //ITCM Size/Base

    ldr r0, =SDK_AUTOLOAD_DTCM_START
    orr r0, r0, #HW_C9_TCMR_16KB
    mcr p15, 0, r0, c9, c1, 0 //DTCM Size/Base

    mov r0, #REGION_BIT(0,1,0,0,0,0,1,0)
    mcr p15, 0, r0, c2, c0, 1 //Cache Bits for Instruction Protection Region

    mov r0, #REGION_BIT(0,1,0,0,0,0,1,0)
    mcr p15, 0, r0, c2, c0, 0 //Cache Bits for Data Protection Region

    mov r0, #REGION_BIT(0,1,0,0,0,0,0,0)
    mcr p15, 0, r0, c3, c0, 0 //Cache Write Buffer Bits for Data Protection Region

    ldr r0, =REGION_ACC(1,1,0,0,0,1,5,0)
    mcr p15, 0, r0, c5, c0, 3 //Extended Access Permission Instruction Protection Region

    ldr r0, =REGION_ACC(1,1,0,1,1,1,5,1)
    mcr p15, 0, r0, c5, c0, 2 //Extended Access Permission Data Protection Region

    mrc p15, 0, r0, c1, c0, 0 //Save Control Register

    /*
     * The following bits are enabled
     * * Instruction Cache
     * * Data Cache
     * * Cache Replacement - Round Robin
     * * ITCM
     * * DTCM
     * * SB1 Bit Set
     * * Exception Vectors
     * * Protection Unit
     */
    ldr r1, =0x0005707D
    orr r0, r0, r1
    mcr p15, 0, r0, c1, c0, 0 //Set Control Register

    bx lr
}
#undef SET_PROTECTION_A
#undef SET_PROTECTION_B
#undef REGION_BIT
#undef REGION_ACC

void NitroStartUp(void)
{
}

void OSi_ReferSymbol(void *symbol)
{
#pragma unused(symbol)
}
