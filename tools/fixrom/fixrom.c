#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <stdnoreturn.h>
#include <stdarg.h>

#define HEADER_SIZE                0x4000
#define HEADER_CODE_OFFSET            0xC
#define HEADER_SECURE_CRC_OFFSET     0x6C
#define HEADER_CRC_OFFSET           0x15E

// ROM header buffer
uint8_t RomHeader[HEADER_SIZE];

static inline noreturn __attribute__((format(printf, 1, 2))) void fatal_error(const char * message, ...)
{
    va_list va_args;
    va_start(va_args, message);
    fputs("Error: ", stderr);
    vfprintf(stderr, message, va_args);
    fputc('\n', stderr);
    va_end(va_args);
    exit(EXIT_FAILURE);
}

// Pedantic check to make sure you're writing to or reading from a valid range
// within the ROM header buffer.
// Call twice, once with the first offset and again with the last address.
static inline void OffsetCheck(int offset)
{
    if (offset < 0 || offset >= HEADER_SIZE)
    {
        fatal_error("illegal access to header+%d", offset);
    }
}

// Wrapper for memcpy that writes to the ROM header buffer
static inline uint8_t * SafeCopyToHeader(int offset, const void * src, size_t size)
{
    OffsetCheck(offset);
    OffsetCheck(offset + size - 1);
    return memcpy(RomHeader + offset, src, size);
}

// Read a 16-bit word from the header buffer
static inline uint16_t HeaderReadU16LE(int offset)
{
    OffsetCheck(offset);
    OffsetCheck(offset + 1);
    return RomHeader[offset] |
        (RomHeader[offset + 1] << 8);
}

// Read a 32-bit word from the header buffer
static inline uint32_t HeaderReadU32LE(int offset)
{
    OffsetCheck(offset);
    OffsetCheck(offset + 3);
    return RomHeader[offset] |
        (RomHeader[offset + 1] << 8) |
        (RomHeader[offset + 2] << 16) |
        (RomHeader[offset + 3] << 24);
}

// Write a 16-bit word to the header buffer
static inline void HeaderWriteU16LE(int offset, uint16_t value)
{
    OffsetCheck(offset);
    OffsetCheck(offset + 1);
    RomHeader[offset] = value;
    RomHeader[offset + 1] = value >> 8;
}
// Write a 32-bit word to the header buffer
static inline void HeaderWriteU32LE(int offset, uint32_t value)
{
    OffsetCheck(offset);
    OffsetCheck(offset + 3);
    RomHeader[offset] = value;
    RomHeader[offset + 1] = value >> 8;
    RomHeader[offset + 2] = value >> 16;
    RomHeader[offset + 3] = value >> 24;
}

// Standard CRC16 routine
#define CRC16_POLYNOMIAL 0xA001

static uint16_t Calc_CRC16(uint8_t * data, size_t length, uint16_t crc)
{
    static uint16_t CrcTable[256] = {};
    static int initialized = 0;
    int i;

    if (!initialized) {
        for (i = 0; i < 256; i++) {
            int c = i;
            for (int j = 0; j < 8; j++) {
                c = (c >> 1) ^ ((c & 1) ? CRC16_POLYNOMIAL : 0);
            }
            CrcTable[i] = c;
        }
        initialized = 1;
    }

    for (i = 0; i < length; i++) {
        crc = (crc >> 8) ^ CrcTable[(uint8_t)crc] ^ CrcTable[data[i]];
    }

    return crc;
}

int main(int argc, char ** argv)
{
    uint16_t secure_crc = 0xFFFF;
    char game_code[4] = "NTRJ";
    int override_crc = 0;
    int override_code = 0;
    FILE * rom = NULL;

    // Parse arguments
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--secure-crc") == 0)
        {
            // Enforce zero or one
            if (override_crc)
            {
                fatal_error("multiple --secure-crc options specified");
            }
            // Parse integer
            char * endptr;
            unsigned long secure_crc_l = strtoul(argv[++i], &endptr, 0);
            if (secure_crc_l == 0 && endptr == argv[i])
            {
                fatal_error("argument to --secure-crc must be an integer");
            }
            // Enforce width
            if (secure_crc_l > UINT16_MAX)
            {
                fatal_error("argument to --secure-crc must be a 16-bit integer");
            }
            secure_crc = secure_crc_l;
            override_crc = 1;
        }
        else if (strcmp(argv[i], "--game-code") == 0)
        {
            // Enforce zero or one
            if (override_code)
            {
                fatal_error("multiple --game-code options specified");
            }
            // Enforce max length
            if (strlen(argv[++i]) > sizeof(game_code))
            {
                fatal_error("argument to --game-code must be 4 characters or fewer");
            }
            memset(game_code, 0, sizeof(game_code));
            strncpy(game_code, argv[i], sizeof(game_code));
            override_code = 1;
        }
        // Positional arguments
        else if (rom == NULL)
        {
            rom = fopen(argv[i], "r+b");
            if (rom == NULL)
            {
                fatal_error(argv[i][0] == '-' ? "unrecognized flag argument: %s" : "unable to open file '%s' for reading", argv[i]);
            }
        }
        else
        {
            // Invalid argument, complain about it
            fatal_error("unrecognized %s argument: %s", argv[i][0] == '-' ? "flag" : "positional", argv[i]);
        }
    }

    // Read header to buffer
    if (fread(RomHeader, 1, HEADER_SIZE, rom) != HEADER_SIZE)
    {
        fatal_error("error reading the ROM header");
    }

    // Update CRC
    if (override_crc)
    {
        HeaderWriteU16LE(HEADER_SECURE_CRC_OFFSET, secure_crc);
    }

    // Update code
    if (override_code)
    {
        SafeCopyToHeader(HEADER_CODE_OFFSET, game_code, sizeof(game_code));
    }

    // Recompute CRC of header not including the crc offset
    uint16_t header_crc = Calc_CRC16((uint8_t *)RomHeader, HEADER_CRC_OFFSET, 0xFFFF);
    HeaderWriteU16LE(HEADER_CRC_OFFSET, header_crc);

    // Write the header back
    fseek(rom, 0, SEEK_SET);
    if (fwrite(RomHeader, 1, HEADER_SIZE, rom) != HEADER_SIZE)
    {
        fatal_error("error writing the ROM header");
    }

    // Hooray, we done did it!
    fclose(rom);
    return EXIT_SUCCESS;
}
