#include <iostream>
#include <fstream>
#include <sstream>
#include <elf.h>
#include <glob.h>
#include <string.h>
#include <vector>
#include <string>

using namespace std;

struct Glob : public vector<char const *> {
    glob_t glob_result;
public:
    Glob(string const & pattern) {
        int result = ::glob(pattern.c_str(), GLOB_TILDE | GLOB_BRACE, NULL, &glob_result);
        if (result) {
            stringstream ss;
            ss << "Glob::glob(" << pattern << ") failed with error " << result << endl;
            throw runtime_error(ss.str());
        }
        assign(glob_result.gl_pathv, glob_result.gl_pathv + glob_result.gl_pathc);
    };
    void operator~() {
        globfree(&glob_result);
    }
};

int main()
{
    fstream elf;
    Elf32_Ehdr ehdr;
    Elf32_Shdr shdr_buf;
    vector<Elf32_Shdr> shdr(0);

    // Accumulate sizes
    //        src   asm
    // data  _____|_____
    // text       |
    unsigned sizes[2][2] = {{0, 0}, {0, 0}};
    char * shstrtab = NULL;
    size_t shstrsz = 0;
    for (char const * & fname : Glob("../../arm9/{src,asm,lib/{src,asm},modules/*/{src,asm}}/*.{c,s,cpp}"))
    {
        string fname_s(fname);
        string ext = fname_s.substr(fname_s.rfind('.'), 4);
        bool is_asm = ext == ".s";
        fname_s = fname_s.replace(fname_s.find("arm9"), 4, "arm9/build");
        fname_s = fname_s.replace(fname_s.rfind('.'), 4, ".o");
        elf.open(fname_s, ios_base::in | ios_base::binary);
        elf.read((char *)&ehdr, sizeof(ehdr));
        if (memcmp(ehdr.e_ident, ELFMAG, SELFMAG) != 0) {
            elf.close();
            stringstream ss;
            ss << "Error validating " << fname_s << " as an ELF file" << endl;
            throw runtime_error(ss.str());
        }
        // Read ELF sections
        elf.seekg(ehdr.e_shoff);
        shdr.resize(ehdr.e_shnum);
        elf.read((char *)shdr.data(), ehdr.e_shnum * ehdr.e_shentsize);
        // Read .shstrtab
        if (shstrsz < shdr[ehdr.e_shstrndx].sh_size) {
            shstrtab = (char *)realloc(shstrtab, shdr[ehdr.e_shstrndx].sh_size);
            shstrsz = shdr[ehdr.e_shstrndx].sh_size;
        }
        elf.seekg(shdr[ehdr.e_shstrndx].sh_offset);
        elf.read(shstrtab, shdr[ehdr.e_shstrndx].sh_size);
        elf.close();
        for (Elf32_Shdr & hdr : shdr) {
            string shname = shstrtab + hdr.sh_name;
            bool is_text = (shname == ".text" || shname == ".init");
            bool is_data = (shname == ".data" || shname == ".rodata" || shname == ".sdata");
            size_t size = hdr.sh_size + (hdr.sh_size & 3 ? 4 - (hdr.sh_size & 3) : 0);
            if (is_text || is_data)
            {
                sizes[is_text][is_asm] += size;
            }
        }
    }
    free(shstrtab);

    cout << "Analysis of ARM9 binary:" << endl;
    // Report code
    unsigned total_text = sizes[1][0] + sizes[1][1];
    double total_text_d = total_text;
    double src_text_d = sizes[1][0];
    double asm_text_d = sizes[1][1];
    cout << total_text << " total bytes of code" << endl;
    cout << "  " << sizes[1][0] << " bytes of code in src (" << (src_text_d / total_text_d * 100.0) << "%)" << endl;
    cout << "  " << sizes[1][1] << " bytes of code in asm (" << (asm_text_d / total_text_d * 100.0) << "%)" << endl;
    cout << endl;
    // Report data
    unsigned total_data = sizes[0][0] + sizes[0][1];
    double total_data_d = total_data;
    double src_data_d = sizes[0][0];
    double asm_data_d = sizes[0][1];
    cout << total_data << " total bytes of data" << endl;
    cout << "  " << sizes[0][0] << " bytes of data in src (" << (src_data_d / total_data_d * 100.0) << "%)" << endl;
    cout << "  " << sizes[0][1] << " bytes of data in asm (" << (asm_data_d / total_data_d * 100.0) << "%)" << endl;
    // Let vectors fall to gc
    return 0;
}
