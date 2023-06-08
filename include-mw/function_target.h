#ifndef GUARD_FUNCTION_TARGET_H
#define GUARD_FUNCTION_TARGET_H

#define ENUMS_ALWAYS_INT_ON _Pragma("enumsalwaysint on")
#define ENUMS_ALWAYS_INT_OFF _Pragma("enumsalwaysint off")
#define ENUMS_ALWAYS_INT_RESET _Pragma("enumsalwaysint reset")

#define ALIGN(num) __attribute__ ((aligned(num)))

#endif //GUARD_FUNCTION_TARGET_H
