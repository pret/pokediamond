#include <stdint.h>
#include <stdio.h>
#include <openssl/sha.h>
#include <string.h>
#include <stdarg.h> 
#include <stdlib.h>

// mwasmarm patcher v1.0
// Patches the Metrowerk C compiler assembler to stop the line ending bug.

char mwasmarm_unpatched_sha1[] = "9d63877c776245129b4727b41d3e9e63cfc9cd28";
char mwasmarm_patched_sha1[]   = "f5dea73bf90791e104cb59458bebae8b08a55484";

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
        
        if(!strcmp(buf, mwasmarm_unpatched_sha1)) {
            // Unpatched, perform the patch.
            fseek(f, 0x57644, SEEK_SET);
            fputc(0x05, f);
            printf("Supported unpatched version detected: assembler patched\n");
        } else if(!strcmp(buf, mwasmarm_patched_sha1)) {
            printf("Supported patched version detected: no action needed\n");
        } else {
            fatal_printf("ERROR: Unsupported mwasmarm.exe version\n");
        }
    }
    return 0;
}
