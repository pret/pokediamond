#include "global.h"
#include "MATH_crc.h"

ARM_FUNC void MATHi_CRC8InitTable(struct MATHCRC8Table *table, u8 poly) {
    u32 r, i, j;
    u8 *t = table->table;

    for (i = 0; i < 256; i++) {
        r = i;
        for (j = 0; j < 8; j++) {
            if (r & 0x80) {
                r = (r << 1) ^ poly;
            }
            else {
                r <<= 1;
            }
        }
        t[i] = r;
    }
}

ARM_FUNC void MATHi_CRC8Update(const struct MATHCRC8Table *table, MATHCRC8Context *context, const void *input, u32 length) {
    u32 r, i;
    const u8* t = table->table;
    u8* data = (u8*)input;

    r = *context;
    for (i = 0; i < length; i++) {
        r = t[(r ^ *data) & 0xff];
        data++;
    }
    *context = r;
}

ARM_FUNC void MATHi_CRC16InitTable(struct MATHCRC16Table *table, u16 poly) {
    u32 r, i, j;
    u16 *t = table->table;

    for (i = 0; i < 256; i++) {
        r = i << 8;
        for (j = 0; j < 8; j++) {
            if (r & 0x8000) {
                r = (r << 1) ^ poly;
            }
            else {
                r <<= 1;
            }
        }
        t[i] = r;
    }
}

ARM_FUNC void MATHi_CRC16InitTableRev(struct MATHCRC16Table *table, u16 poly) {
    u32 r, i, j;
    u16 *t = table->table;

    for (i = 0; i < 256; i++) {
        r = i;
        for (j = 0; j < 8; j++) {
            if (r & 1) {
                r = (r >> 1) ^ poly;
            }
            else {
                r >>= 1;
            }
        }
        t[i] = r;
    }
}

ARM_FUNC void MATHi_CRC16Update(const struct MATHCRC16Table *table, MATHCRC16Context *context, const void *input, u32 length) {
    u32 r, i;
    const u16* t = table->table;
    u8* data = (u8*)input;

    r = *context;
    for (i = 0; i < length; i++) {
        r = (r << 8) ^ t[((r >> 8) ^ *data) & 0xff];
        data++;
    }
    *context = r;
}

ARM_FUNC void MATHi_CRC16UpdateRev(const struct MATHCRC16Table *table, MATHCRC16Context *context, const void *input, u32 length) {
    u32 r, i;
    const u16* t = table->table;
    u8* data = (u8*)input;

    r = *context;
    for (i = 0; i < length; i++) {
        r = (r >> 8) ^ t[(r ^ *data) & 0xff];
        data++;
    }
    *context = r;
}

ARM_FUNC void MATHi_CRC32InitTableRev(struct MATHCRC32Table *table, u32 poly) {
    u32 r, i, j;
    u32 *t = table->table;

    for (i = 0; i < 256; i++) {
        r = i;
        for (j = 0; j < 8; j++) {
            if (r & 1) {
                r = (r >> 1) ^ poly;
            }
            else {
                r >>= 1;
            }
        }
        t[i] = r;
    }
}

ARM_FUNC void MATHi_CRC32UpdateRev(const struct MATHCRC32Table *table, MATHCRC32Context *context, const void *input, u32 length) {
    u32 r, i;
    const u32* t = table->table;
    u8* data = (u8*)input;

    r = *context;
    for (i = 0; i < length; i++) {
        r = (r >> 8) ^ t[(r ^ *data) & 0xff];
        data++;
    }
    *context = r;
}

ARM_FUNC u8 MATH_CalcCRC8(const struct MATHCRC8Table *table, const void *data, u32 dataLength) {
    MATHCRC8Context ctx = 0;
    MATHi_CRC8Update(table, &ctx, data, dataLength);
    return ctx;
}

ARM_FUNC u16 MATH_CalcCRC16(const struct MATHCRC16Table *table, const void *data, u32 dataLength) {
    MATHCRC16Context ctx = 0;
    MATHi_CRC16UpdateRev(table, &ctx, data, dataLength);
    return ctx;
}

ARM_FUNC u16 MATH_CalcCRC16CCITT(const struct MATHCRC16Table *table, const void *data, u32 dataLength) {
    MATHCRC16Context ctx = 0xffff;
    MATHi_CRC16Update(table, &ctx, data, dataLength);
    return ctx;
}

ARM_FUNC u32 MATH_CalcCRC32(const struct MATHCRC32Table *table, const void *data, u32 dataLength) {
    MATHCRC32Context ctx = ~0;
    MATHi_CRC32UpdateRev(table, &ctx, data, dataLength);
    return ~ctx;
}
