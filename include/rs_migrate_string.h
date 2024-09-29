#ifndef POKEDIAMOND_RS_MIGRATE_STRING_H
#define POKEDIAMOND_RS_MIGRATE_STRING_H

#include "nitro/types.h"

// --------------------------------------------
// ConvertRSStringToDPStringInternational
// ============================================
//     Param rs_str: Pointer to u8 representing
//                   the name of a Pokemon or
//                   its OT when migrating from
//                   Advanced Gameboy.
//     Param dp_str: Pointer to u16 representing
//                   the destination string buffer
//                   for migration to Diamond
//                   or Pearl.
//     Param length: The length of the string
//                   to convert, including the
//                   terminator byte.
//     Param language: Game language of origin.
//                     See include/config.h.
//     Return: TRUE if the conversion was completed
//             successfully. Otherwise, dp_str will
//             be filled with up to 10 question mark
//             characters.
BOOL ConvertRSStringToDPStringInternational(const u8 *rs_str, u16 *dp_str, u32 length, u32 language);

#endif // POKEDIAMOND_RS_MIGRATE_STRING_H
