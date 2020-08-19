#ifndef GUARD_MATH_CRC_H
#define GUARD_MATH_CRC_H

#include "nitro/types.h"

typedef u8 MATHCRC8Context;
typedef u16 MATHCRC16Context;
typedef u32 MATHCRC32Context;

#define MATH_CRC16_CCITT_POLY 0x1021

struct MATHCRC8Table {
    u8 table[256];
};

struct MATHCRC16Table {
    u16 table[256];
};

struct MATHCRC32Table {
    u32 table[256];
};

u32 MATH_CalcCRC32(const struct MATHCRC32Table *table, const void *data, u32 dataLength);
void MATHi_CRC32UpdateRev(const struct MATHCRC32Table *table, MATHCRC32Context *context, const void *input, u32 length);
u16 MATH_CalcCRC16CCITT(const struct MATHCRC16Table *table, const void *data, u32 dataLength);
void MATHi_CRC16Update(const struct MATHCRC16Table *table, MATHCRC16Context *context, const void *input, u32 length);
u16 MATH_CalcCRC16(const struct MATHCRC16Table *table, const void *data, u32 dataLength);
void MATHi_CRC16UpdateRev(const struct MATHCRC16Table *table, MATHCRC16Context *context, const void *input, u32 length);
u8 MATH_CalcCRC8(const struct MATHCRC8Table *table, const void *data, u32 dataLength);
void MATHi_CRC8Update(const struct MATHCRC8Table *table, MATHCRC8Context *context, const void *input, u32 length);
void MATHi_CRC32InitTableRev(struct MATHCRC32Table *table, u32 poly);
void MATHi_CRC16UpdateRev(const struct MATHCRC16Table *table, MATHCRC16Context *context, const void *input, u32 length);
void MATHi_CRC16Update(const struct MATHCRC16Table *table, MATHCRC16Context *context, const void *input, u32 length);
void MATHi_CRC16InitTableRev(struct MATHCRC16Table *table, u16 poly);
void MATHi_CRC16InitTable(struct MATHCRC16Table *table, u16 poly);
void MATHi_CRC8Update(const struct MATHCRC8Table *table, MATHCRC8Context *context, const void *input, u32 length);
void MATHi_CRC8InitTable(struct MATHCRC8Table *table, u8 poly);

static inline void MATH_CRC16InitTable(struct MATHCRC16Table * table)
{
    MATHi_CRC16InitTable(table, MATH_CRC16_CCITT_POLY);
}

#endif
