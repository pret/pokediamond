#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cstring>
extern "C" {
#include "elf.h"
}

enum Proc : unsigned char {
    PROC_ARM = EM_ARM,
    PROC_PPC = EM_PPC,
};

enum Endian : unsigned char {
    END_LITTLE = ELFDATA2LSB,
    END_BIG    = ELFDATA2MSB,
};

enum Shndx {
    SHNDX_SHSTRTAB = 1,
    SHNDX_SYMTAB,
    SHNDX_STRTAB,
    SHNDX_PROGBITS,
};

static inline void usage() {
    std::cout << "Usage: bin2obj [-b|--begin SYMBOL_BEGIN]" << std::endl;
    std::cout << "               [-e|--end   SYMBOL_END]" << std::endl;
    std::cout << "               [-C|--compatible]" << std::endl;
    std::cout << "               [-a|--align ALIGNMENT]" << std::endl;
    std::cout << "               [-r|--readonly]" << std::endl;
    std::cout << "               [-s|--section SECTION]" << std::endl;
    std::cout << "               [-m|--machine [arm|ppc]]" << std::endl;
    std::cout << "               [-B|--big-endian]" << std::endl;
    std::cout << "               [-L|--little-endian] BINARY_FILE OBJECT_FILE" << std::endl;
    std::cout << std::endl;
    std::cout << " -b or --begin             Set symbol name for top of binary. (*)" << std::endl;
    std::cout << " -e or --end               Set symbol name for bottom of binary. (*)" << std::endl;
    std::cout << " -C or --compatible        Use compatible symbols with BinToElf.exe." << std::endl;
    std::cout << "                           Same as \"-b _binary_%f -e _binary_%f_end\"." << std::endl;
    std::cout << " -a or --align             Set binary data alignment in bytes." << std::endl;
    std::cout << " -r or --readonly          Handle binary data as readonly." << std::endl;
    std::cout << " -s or --section           Set section name." << std::endl;
    std::cout << " -m or --machine [arm|ppc] Machine arch [arm|ppc].(default=arm)" << std::endl;
    std::cout << " -B or --big-endian        Output in big    endian format." << std::endl;
    std::cout << " -L or --little-endian     Output in little endian format." << std::endl;
    std::cout << std::endl;
    std::cout << "  (*) special % rules for symbols (ex. binary_file = \"filename.dat\")" << std::endl;
    std::cout << "       %f,%t replaced to file name of binary   (%f = \"filename.dat\")" << std::endl;
    std::cout << "       %b    replaced to base name of binary   (%b = \"filename\")" << std::endl;
    std::cout << "       %e    replaced to extension of binary   (%e = \"dat\")" << std::endl;
}

std::string& ntrsprintf(std::string& templ, std::string binfname) {
    size_t pos;
    if ((pos = binfname.rfind('/')) != std::string::npos) {
        binfname = binfname.substr(pos + 1);
    }
    size_t extpos = binfname.rfind('.');
    if (extpos == std::string::npos) extpos = binfname.length() - 1;
    if ((pos = templ.find("%f")) != std::string::npos || (pos = templ.find("%t")) != std::string::npos) {
        templ = templ.substr(0, pos) + binfname + templ.substr(pos + 2);
    }
    if ((pos = templ.find("%b")) != std::string::npos) {
        templ = templ.substr(0, pos) + binfname.substr(0, extpos) + templ.substr(pos + 2);
    }
    if ((pos = templ.find("%e")) != std::string::npos) {
        templ = templ.substr(0, pos) + binfname.substr(extpos + 1) + templ.substr(pos + 2);
    }
    return templ;
}

int main(int argc, char** argv) {
    std::vector<std::string> args(argv + 1, argv + argc);
    std::vector<std::string> posargs;
    std::string sym_begin;
    std::string sym_end;
    bool compatible = false;
    int alignment = 4;
    bool readonly = false;
    std::string section;
    Proc proc = PROC_ARM;
    Endian endian = END_LITTLE;

    for (auto arg_i = args.cbegin(); arg_i < args.cend(); arg_i++) {
        const std::string cur_arg = *arg_i;
        if (cur_arg == "-b" || cur_arg == "--begin") {
            arg_i++;
            sym_begin = *arg_i;
        } else if (cur_arg == "-e" || cur_arg == "--end") {
            arg_i++;
            sym_end = *arg_i;
        } else if (cur_arg == "-C" || cur_arg == "--compatible") {
            compatible = true;
        } else if (cur_arg == "-a" || cur_arg == "--align") {
            arg_i++;
            try {
                alignment = std::stoi(*arg_i);
            } catch (std::invalid_argument& e) {
                if (e.what() == static_cast<std::string>("stoi")) {
                    std::cerr << "Invalid integer value for " << cur_arg << ": " << *arg_i << std::endl;
                } else {
                    std::cerr << "Unexpected error while parsing value for " << cur_arg << ": " << e.what() << std::endl;
                }
                return 1;
            }
        } else if (cur_arg == "-r" || cur_arg == "--readonly") {
            readonly = true;
        } else if (cur_arg == "-s" || cur_arg == "--section") {
            arg_i++;
            section = *arg_i;
        } else if (cur_arg == "-m" || cur_arg == "--machine") {
            arg_i++;
            if (*arg_i == "arm") {
                proc = PROC_ARM;
            } else if (*arg_i == "ppc") {
                proc = PROC_PPC;
            } else {
                std::cerr << "Invalid argument for " << cur_arg << ": " << *arg_i << std::endl;
                return 1;
            }
        } else if (cur_arg == "-B" || cur_arg == "--big-endian") {
            endian = END_BIG;
        } else if (cur_arg == "-L" || cur_arg == "--little-endian") {
            endian = END_LITTLE;
        } else {
            posargs.push_back(cur_arg);
        }
    }

    if (posargs.size() < 2) {
        usage();
        std::cerr << "Missing required position argument: " << (posargs.empty() ? "BINARY_FILE" : "OBJECT_FILE") << std::endl;
        return 1;
    } else if (posargs.size() > 2) {
        usage();
        std::cerr << "Unrecognized arguments (first one: " << posargs[2] << ")" << std::endl;
        return 1;
    }
    if (compatible) {
        sym_begin = "_binary_%f";
        sym_end = "_binary_%f_end";
    }
    if (sym_begin.empty()) {
        sym_begin = "%b_begin";
    }
    if (sym_end.empty()) {
        sym_end = "%b_end";
    }
    sym_begin = ntrsprintf(sym_begin, posargs[0]);
    sym_end = ntrsprintf(sym_end, posargs[0]);
    if (section.empty()) {
        section = readonly ? ".rodata" : ".data";
    }
    if (alignment == 0) {
        alignment = 1;
    } else {
        int i;
        for (i = 0; i < 10; i++) {
            if ((alignment >> i) & 1) {
                if ((alignment >> i) & ~1) {
                    std::cerr << "Alignment must be a power of 2" << std::endl;
                    return 1;
                }
                break;
            }
        }
        if (i == 10) {
            std::cerr << "Alignment exceeds maximum value of 512" << std::endl;
            return 1;
        }
    }
    if (alignment < 4) {
        alignment = 4;
    }
    std::ifstream binfile(posargs[0], std::ios::binary | std::ios::ate);
    if (!binfile.good()) {
        std::cerr << "Unable to open file " << posargs[0] << " for reading" << std::endl;
        return 1;
    }
    std::ofstream objfile(posargs[1], std::ios::binary);
    if (!objfile.good()) {
        binfile.close();
        std::cerr << "Unable to open file " << posargs[1] << " for writing" << std::endl;
        return 1;
    }
    size_t filesize = binfile.tellg();
    binfile.seekg(0);

    // Elf header
    Elf32_Ehdr ehdr;

    static const unsigned char _eident[EI_NIDENT] {
        ELFMAG0,        // EI_MAG0
        ELFMAG1,        // EI_MAG1
        ELFMAG2,        // EI_MAG2
        ELFMAG3,        // EI_MAG3
        ELFCLASS32,     // EI_CLASS
        endian,         // EI_DATA
        EV_CURRENT,     // EI_VERSION
        ELFOSABI_NONE,  // EI_OSABI
        0,              // EI_ABIVERSION
    };
    memcpy(ehdr.e_ident, _eident, EI_NIDENT);
    ehdr.e_type = ET_REL;
    ehdr.e_machine = proc;
    ehdr.e_version = EV_CURRENT;
    ehdr.e_shoff = sizeof(Elf32_Ehdr);
    ehdr.e_ehsize = sizeof(Elf32_Ehdr);
    ehdr.e_shentsize = sizeof(Elf32_Shdr);
    ehdr.e_shnum = 5;
    ehdr.e_shstrndx = 1;

    // Five sections: NULL, user section, symtab, strtab, shstrtab
    Elf32_Shdr shdr[5] = {};

    size_t sh_name = 1;
    shdr[SHNDX_SHSTRTAB].sh_type = SHT_STRTAB;
    shdr[SHNDX_SHSTRTAB].sh_offset = ehdr.e_shoff + 5 * sizeof(Elf32_Shdr);
    shdr[SHNDX_SHSTRTAB].sh_name = sh_name;
    sh_name += std::string(".shstrtab").length() + 1;
    shdr[SHNDX_SYMTAB].sh_type = SHT_SYMTAB;
    shdr[SHNDX_SYMTAB].sh_link = SHNDX_STRTAB;
    shdr[SHNDX_SYMTAB].sh_info = 2;
    shdr[SHNDX_SYMTAB].sh_addralign = 4;
    shdr[SHNDX_SYMTAB].sh_name = sh_name;
    shdr[SHNDX_SYMTAB].sh_entsize = sizeof(Elf32_Sym);
    sh_name += std::string(".symtab").length() + 1;
    shdr[SHNDX_STRTAB].sh_type = SHT_STRTAB;
    shdr[SHNDX_STRTAB].sh_addralign = 1;
    shdr[SHNDX_STRTAB].sh_name = sh_name;
    sh_name += std::string(".strtab").length() + 1;
    shdr[SHNDX_PROGBITS].sh_type = SHT_PROGBITS;
    shdr[SHNDX_PROGBITS].sh_flags = SHF_ALLOC | (readonly ? 0 : SHF_WRITE);
    shdr[SHNDX_PROGBITS].sh_addralign = alignment;
    shdr[SHNDX_PROGBITS].sh_name = sh_name;
    sh_name += section.length() + 1;
    shdr[SHNDX_SHSTRTAB].sh_size = sh_name;
    sh_name = (sh_name + 3) & ~3;
    shdr[SHNDX_SYMTAB].sh_offset = shdr[SHNDX_SHSTRTAB].sh_offset + sh_name;
    shdr[SHNDX_SYMTAB].sh_size = 3 * sizeof(Elf32_Sym);
    shdr[SHNDX_STRTAB].sh_offset = shdr[SHNDX_SYMTAB].sh_offset + shdr[SHNDX_SYMTAB].sh_size;
    size_t st_name = sym_begin.length() + sym_end.length() + 3;
    shdr[SHNDX_STRTAB].sh_size = st_name;
    st_name = (st_name + 3) & ~3;
    shdr[SHNDX_PROGBITS].sh_offset = shdr[SHNDX_STRTAB].sh_offset + st_name;
    shdr[SHNDX_PROGBITS].sh_size = filesize;

    // symtab
    Elf32_Sym syms[3] = {};
    // begin
    syms[1].st_info = ELF32_ST_INFO(STB_GLOBAL, STT_OBJECT);
    syms[1].st_shndx = SHNDX_PROGBITS;
    syms[1].st_size = filesize;
    syms[1].st_value = 0;
    syms[1].st_name = 1;
    // end
    syms[2].st_info = ELF32_ST_INFO(STB_GLOBAL, STT_OBJECT);
    syms[2].st_shndx = SHNDX_PROGBITS;
    syms[2].st_size = 0;
    syms[2].st_value = filesize;
    syms[2].st_name = sym_begin.length() + 2;

    // Write to file
    char zeroes[3] = {0, 0, 0};
    unsigned padding;
    // Elf header
    objfile.write((char*)&ehdr, sizeof(ehdr));
    // Section headers
    objfile.write((char*)shdr, sizeof(shdr));
    // Section string table
    objfile.write(zeroes, 1);
    objfile.write(".shstrtab", sizeof(".shstrtab"));
    objfile.write(".symtab", sizeof(".symtab"));
    objfile.write(".strtab", sizeof(".strtab"));
    objfile.write(section.c_str(), static_cast<long>(section.length() + 1));
    padding = (4 - (sizeof(".shstrtab") + sizeof(".symtab") + sizeof(".strtab") + section.length() + 2)) & 3;
    objfile.write(zeroes, padding);
    // Symbol table
    objfile.write((char*)syms, sizeof(syms));
    // String table
    objfile.write(zeroes, 1);
    objfile.write(sym_begin.c_str(), static_cast<long>(sym_begin.length() + 1));
    objfile.write(sym_end.c_str(), static_cast<long>(sym_end.length() + 1));
    padding = (4 - (sym_begin.length() + sym_end.length() + 3)) & 3;
    objfile.write(zeroes, padding);
    // Data
    char* rdbuf = new char[filesize];
    binfile.read(rdbuf, static_cast<long>(filesize));
    objfile.write(rdbuf, static_cast<long>(filesize));
    delete[] rdbuf;

    binfile.close();
    objfile.close();
    return 0;
}
