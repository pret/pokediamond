#include <array>
#include "banner.h"
#include "crc16.h"

u16 CalculateCRC16FromBannerData(const u8* banner_data) {
    const std::array<u16, 16> crc_table = {
        0x0000, 0xCC01, 0xD801, 0x1400,
        0xF001, 0x3C00, 0x2800, 0xE401,
        0xA001, 0x6C00, 0x7800, 0xB401,
        0x5000, 0x9C01, 0x8801, 0x4400,
    };

    u16 checksum = 0xFFFF;

    const std::size_t data_size = sizeof(Banner) - offsetof(Banner, bitmap);
    for (std::size_t i = 0; i < data_size; i++) {
        u16 lookup_index = crc_table[banner_data[i] & 0xF] ^ (checksum >> 4) ^ crc_table[checksum & 0xF];
        checksum = crc_table[banner_data[i] >> 4] ^ (lookup_index >> 4) ^ crc_table[lookup_index & 0xF];
    }

    return checksum;
}
