/*
 * MSGENC: Encodes a Pokemon DP message file to binary
 *
 * Usage:
 *     msgenc TXTFILE KEYFILE CHARMAP OUTFILE
 */

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <map>
#include <vector>
#include <algorithm>

#if (__GNUC__ <= 7) && !defined _MSC_VER
#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;
#else
#include <filesystem>
namespace fs = std::filesystem;
#endif

struct MsgArcHeader
{
    uint16_t count;
    uint16_t key;
};

struct MsgAlloc
{
    uint32_t offset;
    uint32_t length;
};

using namespace std;
using namespace fs;

u16string ReadTextFileU16LE(path filename) {
    FILE * file = fopen(filename.c_str(), "rb");
    if (file == NULL) {
        stringstream ss;
        ss << "unable to open " << filename << " for reading";
        throw runtime_error(ss.str());
    }
    char16_t bom;
    if (fread(&bom, 2, 1, file) != 1) {
        stringstream ss;
        ss << "read error in " << filename;
        throw runtime_error(ss.str());
    }
    if (bom != u'\uFEFF') {
        stringstream ss;
        ss << "invalid bom in " << filename;
        throw runtime_error(ss.str());
    }
    fseek(file, 0, SEEK_END);
    size_t count = ftell(file) / 2 - 1;
    fseek(file, 2, SEEK_SET);
    auto buf = new char16_t[count + 1];
    if (fread(buf, 2, count, file) != count) {
        stringstream ss;
        ss << "read error in " << filename;
        throw runtime_error(ss.str());
    }
    buf[count] = L'\0';
    fclose(file);
    return buf;
}

static map<u16string, uint16_t> charmap;

uint16_t u16rstoi(u16string s, int base = 10) {
    int pow = 1;
    int nybble;
    uint16_t value_i = 0;
    if (base != 10 && base != 16) {
        stringstream ss;
        ss << "Unrecognized numeric base: " << base;
        throw runtime_error(ss.str());
    }
    reverse(s.begin(), s.end());
    for (auto c : s) {
        switch (c) {
        case u'0' ... u'9':
            nybble = c - u'0';
            break;
        case u'A' ... u'F':
            if (base == 10)
                return value_i;
            nybble = c - u'A' + 10;
            break;
        case u'a' ... u'f':
            if (base == 10)
                return value_i;
            nybble = c - u'a' + 10;
            break;
        default:
            return value_i;
        }
        value_i += nybble * pow;
        pow *= base;
    }
    return value_i;
}

void read_charmap(path filename) {
    u16string raw = ReadTextFileU16LE(filename);
    size_t pos, eqpos, last_pos = 0;
    while (last_pos != u16string::npos && (pos = raw.find_first_of(u"\r\n", last_pos)) != u16string::npos) {
        eqpos = raw.find(u'=', last_pos);
        if (eqpos == u16string::npos)
        {
            stringstream s;
            s << "charmap syntax error at " << (charmap.size() + 1);
            throw(runtime_error(s.str()));
        }
        u16string value = raw.substr(last_pos, eqpos - last_pos);
        u16string code = raw.substr(eqpos + 1, pos - eqpos - 1);
        uint16_t value_i = u16rstoi(value, 16);
        charmap[code] = value_i;
        last_pos = raw.find_last_of(u"\r\n", pos + 1, 2) + 1;
    }
}

static MsgArcHeader header;
vector<MsgAlloc> alloc_table;
static vector<u16string> files;
static vector<u16string> outfiles;

void read_key(path keyfname) {
    fstream keyfile(keyfname, ios_base::in | ios_base::binary);
    keyfile.read((char *)&header.key, 2);
}

void read_msgs(path fname) {
    u16string text = ReadTextFileU16LE(fname);
    size_t pos = 0;
    do {
        text = text.substr(pos);
        if (text.empty())
            break;
        pos = text.find_first_of(u"\r\n");
        files.push_back(text.substr(0, pos));
        pos = text.find_last_of(u"\r\n", pos + 1, 2);
        if (pos == u16string::npos)
            break;
        pos++;
    } while (pos != u16string::npos);
    header.count = files.size();
}

uint16_t enc_short(uint16_t value, uint16_t & seed) {
    value ^= seed;
    seed += 18749;
    return value;
}

void encode_messages() {
    int i = 1;
    for (auto message : files) {
        u16string encoded;
        uint16_t seed = i * 596947;
        for (size_t j = 0; j < message.size(); j++) {
            if (message[j] == u'{') {
                size_t k = message.find(u'}', j);
                u16string enclosed = message.substr(j + 1, k - j - 1);
                j = k;
                if (enclosed.find(u"STRVAR ") == 0) {
                    enclosed = enclosed.substr(7);
                    encoded += enc_short(0xFFFE, seed);
                    do {
                        k = enclosed.find(u',');
                        u16string num = enclosed.substr(0, k);
                        uint16_t num_i = u16rstoi(num);
                        encoded += enc_short(num_i, seed);
                        enclosed = enclosed.substr(k + 1);
                    } while (k++ != u16string::npos);
                } else {
                    encoded += enc_short(u16rstoi(enclosed, 16), seed);
                }
            } else {
                uint16_t code = 0;
                size_t k;
                u16string substr;
                for (k = 0; k < message.size() - j; k++) {
                    substr = message.substr(j, k + 1);
                    code = charmap[substr];
                    if (code != 0 || substr == u"\\x0000")
                        break;
                }
                if (code == 0 && substr != u"\\x0000") {
                    stringstream ss;
                    ss << "unrecognized character: file " << i << " pos " << (j + 1);
                    throw runtime_error(ss.str());
                }
                encoded += enc_short(code, seed);
                j += k;
            }
        }
        encoded += enc_short(0xFFFF, seed);
        MsgAlloc alloc {0, 0};
        if (i > 1) {
            alloc.offset = alloc_table[i - 2].offset + alloc_table[i - 2].length * 2;
        } else {
            alloc.offset = sizeof(header) + sizeof(MsgAlloc) * header.count;
        }
        alloc.length = encoded.size();
        outfiles.push_back(encoded);
        alloc_table.push_back(alloc);
        i++;
    }
    i = 1;
    for (auto & x : alloc_table) {
        uint32_t alloc_key = (765 * i * header.key) & 0xFFFF;
        alloc_key |= alloc_key << 16;
        x.offset ^= alloc_key;
        x.length ^= alloc_key;
        i++;
    }
}

void write_messages(path filename) {
    ofstream outfile(filename, ios_base::binary);
    outfile.write((char *)&header, sizeof(header));
    outfile.write((char *)alloc_table.data(), sizeof(MsgAlloc) * alloc_table.size());
    for (auto m : outfiles) {
        outfile.write((char *)m.c_str(), m.size() * 2);
    }
    outfile.close();
}

int main(int argc, char ** argv) {
    // msgenc TXTFILE KEYFILE CHARMAP OUTFILE
    if (argc < 5)
        throw invalid_argument("usage: msgenc TXTFILE KEYFILE CHARMAP OUTFILE");
    read_msgs(argv[1]);
    read_key(argv[2]);
    read_charmap(argv[3]);
    encode_messages();
    write_messages(argv[4]);
    return 0;
}
