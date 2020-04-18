#include <stdint.h>
#include <stdio.h>
#include <openssl/sha.h>
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

void print_help(void) {
    printf("mwasmarm patcher usage: input (example: mwasmarm_patcher mwasmarm.exe)\n");
}

int main(int argc, char *argv[]) {
    unsigned char temp[SHA_DIGEST_LENGTH];
    char buf[SHA_DIGEST_LENGTH*2];

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
        char *string = malloc(fsize + 1);
        fread(string, 1, fsize, f);

        // Check if sha1 matches either known assembler hashes.
        SHA1(string, fsize, temp);
        
        for (int i=0; i < SHA_DIGEST_LENGTH; i++) {
            sprintf((char*)&(buf[i*2]), "%02x", temp[i]);
        }

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
