#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

int main(int argc, char ** argv) {
    FILE * infile = fopen(argv[1], "r");
    char * infname_ext = strrchr(argv[1], '.');
    char * outfname = malloc(infname_ext - argv[1] + 5);
    char * outfname_ext = stpncpy(outfname, argv[1], infname_ext - argv[1]);
    strcpy(outfname_ext, ".bin");
    FILE * outfile = fopen(outfname, "wb");
    uint32_t value;
    size_t size = 0;
    char * line = NULL;
    char * end = NULL;
    while (getline(&line, &size, infile) > 0) {
        value = strtoul(line, &end, 10);
        if (value == 0 && end == line) break;
        fwrite(&value, 1, 4, outfile);
    }
    free(line);
    free(outfname);
    fclose(outfile);
    fclose(infile);
    return 0;
}
