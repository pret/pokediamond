#include <cstdio>
#include <cstring>
#include "banner.h"
#include "types.h"

#ifdef _MSC_VER
#define strcasecmp _stricmp
#endif

int main(int argc, char* argv[]) {
    if (argc != 2 && argc != 3) {
        printf("usage: %s <specfile> [outfile]\n", argv[0]);
        return 1;
    }

    const filesystem::path specfile_path = argv[1];
    if (!filesystem::is_regular_file(specfile_path)) {
        printf("error: provided specfile does not exist / is not a regular file. (did you put the right path?)\n");
        return 1;
    }

    if (specfile_path.extension() == ".bnr") {
        printf("error: can't use a bnr file as a specfile\n");
        return 1;
    }

    // If the user doesn't provide a path to an outfile, or if the provided outfile is
    // identical to the provided specfile, use the specfile's name + the .bnr extension.
    filesystem::path outfile_path;
    if (argc == 2 || strcasecmp(argv[1], argv[2]) == 0) {
        outfile_path = specfile_path.stem().string() + ".bnr";
    } else {
        outfile_path = argv[2];
    }

    // printf("debug: specfile: %s\n", specfile_path.c_str());
    // printf("debug: outfile:  %s\n", outfile_path.c_str());

    if (!MakeBanner(specfile_path, outfile_path)) {
        printf("error: failed to create banner file\n");
        return 1;
    }

    return 0;
}
