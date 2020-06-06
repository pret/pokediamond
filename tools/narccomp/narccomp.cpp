#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>
#include <sstream>
#include <map>
#include <set>

using namespace std;

struct Options
{
    fstream outfile;
    map<string, string> infiles;
    unsigned char padval;
    bool keep_names;
    string host_root;
    string nitro_root;
    Options(int const & argc, char ** const & argv) :
        // Default values
        padval(255),
        keep_names(false)
    {
        char last_opt = 0;
        string outfname; // Use this to avoid clobbering an existing file in the event of an error
        for (string arg : vector<char *>(argv + 1, argv + argc))
        {
            if (last_opt != 0) {
                switch (last_opt)
                {
                case 'p':
                {
                    // Padding
                    unsigned long x;
                    stringstream is(arg);
                    is >> x;
                    if (x >= 256) {
                        stringstream ss;
                        ss << "Invalid value for -p: " << x << endl;
                        throw invalid_argument(ss.str());
                    }
                    padval = x;
                    break;
                }
                case 'o':
                    // Outfile
                    if (!outfname.empty()) {
                        throw invalid_argument("Can't output more than one file\n");
                    }
                    outfname = arg;
                    break;
                case 'r':
                    // Not fully implemented
                    if (!host_root.empty()) {
                        throw invalid_argument("Duplicate settings for option -r\n");
                    }
                    host_root = arg;
                    break;
                case 'R':
                    // Not fully implemented
                    if (!nitro_root.empty()) {
                        throw invalid_argument("Duplicate settings for option -R\n");
                    }
                    nitro_root = arg;
                    break;
                default:
                    stringstream ss;
                    ss << "Unrecognized option: -" << (char)last_opt << endl;
                    throw invalid_argument(ss.str());
                }
                last_opt = 0;
            }
            else if (arg[0] == '-') {
                if (arg[1] == 0 || arg[2] != 0) {
                    stringstream ss;
                    ss << "Unrecognized option: " << arg << endl;
                    throw invalid_argument(ss.str());
                }
                switch (arg[1]) {
                case 'h':
                    cout << "Usage: " << argv[0] << " [-p PADVAL] [-h] -o OUTFILE FILE [FILE ...]" << endl;
                    cout << endl;
                    cout << "  FILE [FILE ...]     List of files to be packed into the archive." << endl;
                    cout << "  -o OUTFILE          The destination archive, in NARC format" << endl;
                    cout << "  -p PADVAL           Pad archive members to word with this character. Default: 255" << endl;
                    cout << "  -h                  Print this message and exit" << endl;
                    exit(0);
                case 'k':
                    throw invalid_argument("'-k': not implemented\n");
//                    if (keep_names) {
//                        throw invalid_argument("'-k' specified more than once\n");
//                    }
//                    keep_names = true;
//                    break;
                default:
                    last_opt = arg[1];
                }
            }
            else
            {
                fstream file;
                stringstream uss;

                if (!infiles[arg].empty()) {
                    stringstream ss;
                    ss << "Duplicate file: " << arg << endl;
                    throw invalid_argument(ss.str());
                }
                file.open(arg, ios_base::in | ios_base::binary);
                uss << file.rdbuf();
                file.close();
                infiles[arg] = uss.str();
            }
        }
        if (outfname.empty()) {
            throw invalid_argument("Must specify an output file (-o OUTFILE)\n");
        }
        if (infiles.empty()) {
            throw invalid_argument("No input files\n");
        }
        outfile.open(outfname, ios_base::binary | ios_base::out);
    }
};

struct FatbEntry
{
    uint32_t start;
    uint32_t end;
};

struct FatbHeader
{
    char magic[4];
    uint32_t chunk_size;
    uint16_t file_count;
    char padding[2];
    FatbHeader(uint16_t numfiles) :
        chunk_size(sizeof(FatbHeader) + sizeof(FatbEntry) * numfiles),
        file_count(numfiles)
    { strncpy(magic, "BTAF", 4); memset(padding, 0, 2); }
};

struct FntbDirHeader
{
    uint32_t offset;
    uint16_t first_file;
    uint16_t id_or_count;
};

struct FntbHeader
{
    char magic[4];
    uint32_t chunk_size;
    FntbHeader() :
        chunk_size(sizeof(FntbHeader) + sizeof(FntbDirHeader))
    { strncpy(magic, "BTNF", 4); }
    string set_names(Options*& opt, FntbDirHeader*& dirHeader) {
        throw runtime_error("not implemented\n");
//        typedef struct NitroFS {
//            bool is_dir;
//            vector<struct NitroFS> children;
//        } nitrofs_t;
//        map<string, nitrofs_t> fs;
//        fs[opt->nitro_root].is_dir = true;
//        string host_root;
//        for (auto pair : opt->infiles) {
//            string fname = pair.first;
//            fname = fname.replace(0, opt->host_root.size(), opt->nitro_root);
//            int pos;
//            while ((pos = fname.find("//")) != fname.npos) {
//                fname = fname.replace(pos, 2, 1, '/');
//            }
//        }
//        return nullptr;
    }
};

#define FNT_END 0
#define FNT_LENGTH_MASK 0x7F
#define FNT_IS_DIR_MASK 0x80

struct FimgHeader
{
    char magic[4];
    uint32_t chunk_size;
    FimgHeader(size_t image_size) :
        chunk_size(sizeof(FimgHeader) + image_size)
    { strncpy(magic, "GMIF", 4); }
};

struct NarcHeader
{
    char magic[4]; // NARC
    uint16_t bom;
    uint16_t version;
    uint32_t size;
    uint16_t chunk_size;
    uint16_t num_chunks;
    NarcHeader(uint16_t numfiles, size_t image_size) :
        bom(0xFFFE),
        version(0x0100),
        size(sizeof(NarcHeader) + sizeof(FatbHeader) + sizeof(FatbEntry) * numfiles + sizeof(FntbHeader) + sizeof(FntbDirHeader) + sizeof(FimgHeader) + image_size),
        chunk_size(sizeof(NarcHeader)),
        num_chunks(3)
    { strncpy(magic, "NARC", 4); }
};

int main(int argc, char ** argv)
{
    try
    {
        auto opt = new Options(argc, argv);
        size_t nfiles = opt->infiles.size();
        auto fatb = new FatbEntry[nfiles];
        FatbEntry *entry = fatb;
        for (auto pair : opt->infiles)
        {
            entry->start = (entry == fatb ? 0 : (entry[-1].end + 3) & ~3);
            entry->end = entry->start + pair.second.size();
            entry++;
        }
        size_t image_size = (fatb[nfiles - 1].end + 3) & ~3;
        FntbHeader fntbHeader;
        auto fntbDir = new FntbDirHeader;
        *fntbDir = (FntbDirHeader) {4, 0, 1}; // dummy
        stringstream fnt;
        if (opt->keep_names)
        {
            fntbHeader.set_names(opt, fntbDir);
        }
        NarcHeader narcHeader(nfiles, (fatb[nfiles - 1].end + 3) & ~3);
        FatbHeader fatbHeader(nfiles);
        FimgHeader fimgHeader((fatb[nfiles - 1].end + 3) & ~3);
        opt->outfile.write((char *) &narcHeader, sizeof(NarcHeader));
        opt->outfile.write((char *) &fatbHeader, sizeof(FatbHeader));
        opt->outfile.write((char *) fatb, sizeof(FatbEntry) * nfiles);
        opt->outfile.write((char *) &fntbHeader, sizeof(FntbHeader));
        opt->outfile.write((char *) fntbDir, sizeof(FntbDirHeader));
        opt->outfile.write((char *) &fimgHeader, sizeof(FimgHeader));
        char padding[4];
        memset(padding, opt->padval, 4);
        for (auto pair : opt->infiles)
        {
            stringstream uss(pair.second);
            opt->outfile.write(pair.second.c_str(), pair.second.size());
            opt->outfile.write(padding, (4 - pair.second.size()) & 3);
        }
        opt->outfile.close();
        return 0;
    } catch (invalid_argument e) {
        cerr << "Invalid exception: " << e.what() << endl;
        return 1;
    } catch (runtime_error e) {
        cerr << "Runtime error: " << e.what() << endl;
        return 2;
    } catch (exception e) {
        cerr << "unhandled exception caught" << endl;
        return 3;
    }
}
