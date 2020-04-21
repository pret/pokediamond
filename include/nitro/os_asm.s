
# TODO: make this syntax look correct in CLion
# Potentially switch to AT&T syntax?
OS_GetProcMode:
    mrs r0, cpsr
    and r0, r0, #0x80
    bx lr
