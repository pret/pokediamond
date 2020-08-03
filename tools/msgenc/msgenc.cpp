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

string ReadTextFile(path filename) {
    fstream file(filename);
    stringstream ss;
    ss << file.rdbuf();
    file.close();
    return ss.str();
}

static map<string, uint16_t> charmap;

void read_charmap(path filename) {
    string raw = ReadTextFile(filename);
    size_t pos, eqpos, last_pos = 0;
    while (last_pos != string::npos && (pos = raw.find_first_of("\r\n", last_pos)) != string::npos) {
        eqpos = raw.find('=', last_pos);
        if (eqpos == string::npos)
        {
            stringstream s;
            s << "charmap syntax error at " << (charmap.size() + 1);
            throw(runtime_error(s.str()));
        }
        string value = raw.substr(last_pos, eqpos - last_pos);
        string code = raw.substr(eqpos + 1, pos - eqpos - 1);
        uint16_t value_i = stoi(value, nullptr, 16);
        charmap[code] = value_i;
        last_pos = raw.find_last_of("\r\n", pos + 1, 2) + 1;
    }
}

static MsgArcHeader header;
vector<MsgAlloc> alloc_table;
static vector<string> files;
static vector<string> outfiles;

void read_key(path keyfname) {
    fstream keyfile(keyfname, ios_base::in | ios_base::binary);
    keyfile.read((char *)&header.key, 2);
}

void read_msgs(path fname) {
    string text = ReadTextFile(fname);
    size_t pos = 0;
    do {
        text = text.substr(pos);
        if (text.empty())
            break;
        pos = text.find_first_of("\r\n");
        files.push_back(text.substr(0, pos));
        pos = text.find_last_of("\r\n", pos + 1, 2);
        if (pos == string::npos)
            break;
        pos++;
    } while (pos != string::npos);
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
        string encoded;
        uint16_t seed = i * 596947;
        for (size_t j = 0; j < message.size(); j++) {
            if (message[j] == '{') {
                size_t k = message.find('}', j);
                string enclosed = message.substr(j + 1, k - j - 1);
                j = k;
                if (enclosed.find("STRVAR ") == 0) {
                    enclosed = enclosed.substr(7);
                    encoded += enc_short(0xFFFE, seed);
                    do {
                        k = enclosed.find(',');
                        string num = enclosed.substr(0, k);
                        uint16_t num_i = stoi(num);
                        encoded += enc_short(num_i, seed);
                        enclosed = enclosed.substr(k + 1);
                    } while (k++ != string::npos);
                } else {
                    encoded += enc_short(stoi(enclosed, nullptr, 16), seed);
                }
            } else {
                uint16_t code = 0;
                size_t k;
                string substr;
                for (k = 0; k < message.size() - j; k++) {
                    substr = message.substr(j, k + 1);
                    code = charmap[substr];
                    if (code != 0 || substr == "\\x0000")
                        break;
                }
                if (code == 0 && substr != "\\x0000") {
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
