#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h> 
#include <stdlib.h>

// mwasmarm patcher v1.1
// Patches the Metrowerk C compiler assembler to stop the line ending bug.

// Changelog:
// v1.1: Added patch definitions and looped over them to find the matching
// definition as well as the version.

struct PatchDef {
    char *version;
    char *sha1before;
    char *sha1after;
    int offsetPatch;
    int newByte;   
};

struct PatchDef gPatchDefs[] = {
    // mwasmarm 1.2/base definition
    {
        "mwasmarm 1.2/base",
        "87f942cc0a0e90e73550d8d6f3fffcdeb5f69fa5",
        "2f1ccff22eaa443bb79235ca6477d3b86bdfd7e4",
        0x57614,
        0x5
    },
    // mwasmarm 2.0/base definition
    {
        "mwasmarm 2.0/base",
        "9d63877c776245129b4727b41d3e9e63cfc9cd28",
        "f5dea73bf90791e104cb59458bebae8b08a55484",
        0x57644,
        0x5
    },
    // mwasmarm 2.0/sp2p4 definition
    {
        "mwasmarm 2.0/sp2p4",
        "448cb0c7f1ace4393e9a9562f819f7a9f049be83",
        "c82161527277b991a1b77e14617a93bcd19cf95c",
        0x57834,
        0x5
    },
    {
    }
};

void sha1_process_block (const unsigned char * block, uint32_t * state);

// Credit to ax6 for implementation
unsigned char * calculate_sha1 (const void * data, unsigned length) {
  uint32_t state[5] = {0x67452301, 0xefcdab89, 0x98badcfe, 0x10325476, 0xc3d2e1f0};
  const char * current;
  unsigned remaining;
  for (current = data, remaining = length; remaining >= 64; current += 64, remaining -= 64) sha1_process_block(current, state);
  // technically only {0} is necessary, but better safe than sorry
  unsigned char last_block[64] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  memcpy(last_block, current, remaining);
  last_block[remaining] = 0x80;
  if (remaining >= 56) {
    sha1_process_block(last_block, state);
    memset(last_block, 0, 64);
  }
  unsigned long long bit_length = ((unsigned long long) length) << 3;
  for (remaining = 5; remaining; remaining --) {
    last_block[58 + remaining] = bit_length;
    bit_length >>= 8;
  }
  sha1_process_block(last_block, state);
  unsigned char * result = malloc(20);
  for (remaining = 0; remaining < 20; remaining ++) result[remaining] = state[remaining >> 2] >> ((~remaining & 3) << 3);
  return result;
}

static inline unsigned sha1_rotate (unsigned value, unsigned count) {
  return (value << count) | (value >> (32 - count));
}

void sha1_process_block (const unsigned char * block, uint32_t * state) {
  uint32_t words[80];
  unsigned pos, temp, count, a, b, c, d, e;
  // constants used by SHA-1; they are actually simply the square roots of 2, 3, 5 and 10 as a fixed-point number (2.30 format)
  const uint32_t hash_constants[4] = {0x5a827999, 0x6ed9eba1, 0x8f1bbcdc, 0xca62c1d6};
  memset(words, 0, 16 * sizeof(uint32_t));
  for (pos = 0; pos < 64; pos ++) words[pos >> 2] = (words[pos >> 2] << 8) | block[pos];
  for (pos = 16; pos < 80; pos ++) words[pos] = sha1_rotate(words[pos - 3] ^ words[pos - 8] ^ words[pos - 14] ^ words[pos - 16], 1);
  a = *state;
  b = state[1];
  c = state[2];
  d = state[3];
  e = state[4];
  for (pos = 0; pos < 4; pos ++) for (count = 0; count < 20; count ++) {
    temp = sha1_rotate(a, 5) + e + words[pos * 20 + count] + hash_constants[pos];
    switch (pos) {
      case 0:
        temp += (b & c) | (~b & d);
        break;
      case 2:
        temp += (b & c) | (b & d) | (c & d);
        break;
      default:
        temp += b ^ c ^ d;
    }
    e = d;
    d = c;
    c = sha1_rotate(b, 30);
    b = a;
    a = temp;
  }
  *state += a;
  state[1] += b;
  state[2] += c;
  state[3] += d;
  state[4] += e;
}

void fatal_printf(char *str, ...) {
    va_list args;
    va_start(args, str);
    vprintf(str, args);
    va_end(args);
    exit(1);
}

// return size in bytes
int get_file_size (FILE * fp) {
    int curpos = ftell(fp);
    fseek(fp, 0, SEEK_END);
    int result = ftell(fp);
    fseek(fp, curpos, SEEK_SET);
    return result;
}

#define SHA_DIGEST_LENGTH 20

void print_help(void) {
    printf("mwasmarm patcher usage: input (example: mwasmarm_patcher mwasmarm.exe)\n");
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        print_help();
        return 1;
    } else {
        // Open the file and sha1 read it.
        FILE *f = fopen(argv[1], "rb+");
        if(f == NULL) {
            fatal_printf("ERROR: No file detected\n");
        }
        int fsize = get_file_size(f);
        unsigned char *string = malloc(fsize + 1);
        if(string == NULL) {
            fatal_printf("ERROR: Failed to allocate string variable\n");
        }
        int readvar = fread(string, 1, fsize, f); // var to surpress warning

        // Check if sha1 matches either known assembler hashes.
        unsigned char *sha1 = calculate_sha1(string, fsize);
        if(sha1 == NULL) {
            fatal_printf("ERROR: Failed to retrieve sha1 hash\n");
        }
        free(string);
        
        unsigned char buf[SHA_DIGEST_LENGTH*2];
        for (int i=0; i < SHA_DIGEST_LENGTH; i++) {
            sprintf((unsigned char*)&(buf[i*2]), "%02x", sha1[i]);
        }

        printf("SHA1: %s\n", buf);

        for(int i = 0; gPatchDefs[i].sha1before != NULL; i++) {
            // check if already patched for the current loop.
            if(!strcmp(buf, gPatchDefs[i].sha1after)) {
                printf("Supported patched version detected (%s): no action needed\n", gPatchDefs[i].version);
                return 0;
            } else if(!strcmp(buf, gPatchDefs[i].sha1before)) {
                fseek(f, gPatchDefs[i].offsetPatch, SEEK_SET);
                fputc(gPatchDefs[i].newByte, f);
                printf("Supported unpatched version detected (%s): assembler patched\n", gPatchDefs[i].version);
                return 0;
            }
        }
        fatal_printf("ERROR: Unsupported mwasmarm.exe version\n");
    }
    return 0;
}
