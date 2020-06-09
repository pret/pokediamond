#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <ctype.h>

char * ReadWholeFile(char * filename) {
    FILE * infile = fopen(filename, "rb");
    if (infile == NULL) return NULL;
    fseek(infile, 0, SEEK_END);
    size_t fsize = ftell(infile);
    fseek(infile, 0, SEEK_SET);
    char * ret = malloc(fsize);
    if (ret != NULL) {
        if (fread(ret, 1, fsize, infile) != fsize) {
            free(ret);
            ret = NULL;
        }
    }
    fclose(infile);
    return ret;
}

int main(int argc, char ** argv) {
    int width = 4;
    char * buffer = NULL;
    char * endptr = NULL;
    FILE * outfile = NULL;
    char * infname = NULL;
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-w") == 0 || strcmp(argv[i], "--width") == 0) {
            ++i;
            width = strtol(argv[i], &endptr, 10);
            if (width == 0) {
                fprintf(stderr, "invalid integer value for %s: %s\n", argv[i - 1], argv[i]);
                return EXIT_FAILURE;
            }
        } else if (strcmp(argv[i], "-o") == 0 || strcmp(argv[i], "--output") == 0) {
            ++i;
            outfile = fopen(argv[i], "wb");
            if (outfile == NULL) {
                fprintf(stderr, "unable to open file '%s' for writing\n", argv[i]);
                return EXIT_FAILURE;
            }
        } else {
            if (buffer == NULL)
            {
                buffer = ReadWholeFile(argv[i]);
            }
            if (buffer == NULL)
            {
                fprintf(stderr, "invalid argument: %s\n", argv[i]);
                return EXIT_FAILURE;
            }
            infname = argv[i];
        }
    }
    if (buffer == NULL) {
        fprintf(stderr, "missing required argument: INFILE\n");
        return EXIT_FAILURE;
    }
    if (outfile == NULL) {
        char * infname_ext = strrchr(infname, '.');
        char * outfname = malloc(infname_ext - infname + 5);
        char * outfname_ext = stpncpy(outfname, argv[1], infname_ext - argv[1]);
        strcpy(outfname_ext, ".bin");
        outfile = fopen(outfname, "wb");
        if (outfile == NULL) {
            fprintf(stderr, "unable to open file '%s' for writing\n", outfname);
            return EXIT_FAILURE;
        }
        free(outfname);
    }
    uint32_t value;
    size_t size = 0;
    char * ptr = buffer;
    char * end = NULL;
    int lineno = 1;
    int colno = 1;
    while (1) {
        while (isspace(*ptr) || *ptr == ',') {
            if (*ptr == 0) break;
            if (*ptr == '\n')
            { lineno++; colno = 1; }
            if (*ptr == ',') colno++;
            ptr++;
        };
        if (*ptr == 0) break;
        value = strtoul(ptr, &end, 10);
        if (value == 0 && ptr == end) {
            fprintf(stderr, "syntax error: %d:%d\n", lineno, colno);
            return EXIT_FAILURE;
        }
        if (fwrite(&value, 1, width, outfile) != width) {
            fprintf(stderr, "write error\n");
            return EXIT_FAILURE;
        }
        ptr = end;
    }
    fclose(outfile);
    free(buffer);
    return EXIT_SUCCESS;
}
