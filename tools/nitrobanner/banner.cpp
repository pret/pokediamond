#include <cstdio>
#include <codecvt>
#include <exception>
#include <fstream>
#include <locale>
#include <string>
#include "banner.h"
#include "crc16.h"

template <typename T>
void SerializeData(std::ofstream& ostream, T data) {
    for (std::size_t i = 0; i < sizeof(T); i++) {
        ostream.put(static_cast<u8>((data >> (i * 8)) & 0xFF));
    }
}

std::wstring GetTitleAndDeveloperFromSpecCommandArgument(std::wifstream& stream, const std::wstring& command_argument) {
    std::wstring title_and_developer = command_argument;
    constexpr int max_lines = 3;
    int current_line = 1;

    while (true) {
        wchar_t first_char = stream.get();
        stream.unget();
        if (first_char != L' ') {
            return title_and_developer;
        }

        if (current_line++ == max_lines) {
            throw std::runtime_error("Title and developer can not be more than " + std::to_string(max_lines) + " lines");
        }

        std::wstring line;
        std::getline(stream, line);

        title_and_developer += '\n';
        title_and_developer += line.substr(line.find_first_not_of(L' '), line.size());
    }
}

SpecFileData ParseSpecFile(const filesystem::path& specfile_path) {
    std::wifstream stream(specfile_path, std::ios::binary);
    if (!stream.is_open()) {
        throw std::runtime_error("could not open specfile " + specfile_path.string() + " for parsing");
    }

    // convert utf-16 to utf-32
    stream.imbue(std::locale(stream.getloc(), new std::codecvt_utf16<wchar_t, 0x10ffff, std::little_endian>));

    // first character of the file has to be U+FEFF.
    if (stream.get() != 0xFEFF) {
        throw std::runtime_error("specfile must be encoded as UTF-16");
    }

    SpecFileData specfile_data = {};

    for (std::wstring line; std::getline(stream, line);) {
        const std::size_t end_of_command_name = line.find(L':');
        if (end_of_command_name == std::wstring::npos) {
            continue;
        }

        const std::size_t beginning_of_command_name = line.find_first_not_of(' ');
        const std::wstring command_name = line.substr(beginning_of_command_name, end_of_command_name - beginning_of_command_name);

        const std::size_t beginning_of_command_argument = line.find_first_of(L": ") + 2;
        const std::wstring command_argument = line.substr(beginning_of_command_argument, line.size());

        if (command_name == L"Version") {
            printf("warning: Version command is currently unsupported, defaulting to version 1\n");
            specfile_data.version = 1;
        } else if (command_name == L"ImageFile") {
            specfile_data.icon_bitmap_filename = command_argument;
        } else if (command_name == L"PlttFile") {
            specfile_data.icon_palette_filename = command_argument;
        } else if (CommandIsForTitleAndDeveloper(command_name)) {
            const std::wstring& title_and_developer = GetTitleAndDeveloperFromSpecCommandArgument(stream, command_argument);

            if (command_name == L"JP") {
                for (wchar_t c : title_and_developer) {
                    specfile_data.japanese_title += char16_t(c);
                }
            } else if (command_name == L"EN") {
                for (wchar_t c : title_and_developer) {
                    specfile_data.english_title += char16_t(c);
                }
            } else if (command_name == L"FR") {
                for (wchar_t c : title_and_developer) {
                    specfile_data.french_title += char16_t(c);
                }
            } else if (command_name == L"GE") {
                for (wchar_t c : title_and_developer) {
                    specfile_data.german_title += char16_t(c);
                }
            } else if (command_name == L"IT") {
                for (wchar_t c : title_and_developer) {
                    specfile_data.italian_title += char16_t(c);
                }
            } else if (command_name == L"SP") {
                for (wchar_t c : title_and_developer) {
                    specfile_data.spanish_title += char16_t(c);
                }
            }
        } else {
            printf("warning: unsupported command '%ls', ignoring...\n", command_name.data());
        }
    }

    if (specfile_data.version == 0) {
        // no banner version provided, assuming version 1
        specfile_data.version = 1;
    }

    if (specfile_data.icon_bitmap_filename.empty()) {
        throw std::runtime_error("missing required ImageFile command (filename of icon bitmap)");
    }

    if (specfile_data.icon_palette_filename.empty()) {
        throw std::runtime_error("missing required PlttFile command (filename of icon palette)");
    }

    if (specfile_data.japanese_title.empty()) {
        throw std::runtime_error("missing required JP command (Japanese title & developer)");
    }

    if (specfile_data.english_title.empty()) {
        throw std::runtime_error("missing required EN command (English title & developer)");
    }

    if (specfile_data.french_title.empty()) {
        throw std::runtime_error("missing required FR command (French title & developer)");
    }

    if (specfile_data.german_title.empty()) {
        throw std::runtime_error("missing required GE command (German title & developer)");
    }

    if (specfile_data.italian_title.empty()) {
        throw std::runtime_error("missing required IT command (Italian title & developer)");
    }

    if (specfile_data.spanish_title.empty()) {
        throw std::runtime_error("missing required SP command (Spanish title & developer)");
    }

    return specfile_data;
}

IconBitmap GetIconBitmap(const filesystem::path& icon_bitmap_filename) {
    if (!filesystem::is_regular_file(icon_bitmap_filename)) {
        throw std::runtime_error("icon bitmap file '" + icon_bitmap_filename.string() + "' does not exist / is not a regular file");
    }

    if (filesystem::file_size(icon_bitmap_filename) != ICON_BITMAP_SIZE) {
        throw std::runtime_error("icon bitmap is not 512 bytes");
    }

    std::ifstream stream(icon_bitmap_filename, std::ios::binary);
    if (!stream.is_open()) {
        throw std::runtime_error("could not open icon bitmap file '" + icon_bitmap_filename.string() + "' for reading");
    }

    IconBitmap bitmap = {};
    stream.read(reinterpret_cast<char*>(bitmap.data()), ICON_BITMAP_SIZE);
    return bitmap;
}

IconPalette GetIconPalette(const filesystem::path& icon_palette_filename) {
    if (!filesystem::is_regular_file(icon_palette_filename)) {
        throw std::runtime_error("icon palette file '" + icon_palette_filename.string() + "' does not exist / is not a regular file");
    }

    if (filesystem::file_size(icon_palette_filename) != ICON_PALETTE_SIZE) {
        throw std::runtime_error("icon palette is not 32 bytes");
    }

    std::ifstream stream(icon_palette_filename, std::ios::binary);
    if (!stream.is_open()) {
        throw std::runtime_error("could not open icon palette file '" + icon_palette_filename.string() + "' for reading");
    }

    IconPalette palette = {};
    stream.read(reinterpret_cast<char*>(palette.data()), ICON_PALETTE_SIZE);
    return palette;
}

void OutputBanner(std::ofstream& ostream, const Banner& banner) {
    SerializeData<u16>(ostream, banner.version);
    SerializeData<u16>(ostream, banner.crc);

    for ([[maybe_unused]] u16 i : banner.crc_padding) {
        SerializeData<u16>(ostream, 0);
    }

    for ([[maybe_unused]] u8 i : banner.padding) {
        SerializeData<u8>(ostream, 0);
    }

    for (u8 i : banner.bitmap) {
        SerializeData<u8>(ostream, i);
    }

    for (u8 i : banner.palette) {
        SerializeData<u8>(ostream, i);
    }

    for (char16_t c : banner.japanese_title) {
        SerializeData<u16>(ostream, c);
    }

    for (char16_t c : banner.english_title) {
        SerializeData<u16>(ostream, c);
    }

    for (char16_t c : banner.french_title) {
        SerializeData<u16>(ostream, c);
    }

    for (char16_t c : banner.german_title) {
        SerializeData<u16>(ostream, c);
    }

    for (char16_t c : banner.italian_title) {
        SerializeData<u16>(ostream, c);
    }

    for (char16_t c : banner.spanish_title) {
        SerializeData<u16>(ostream, c);
    }
}

bool MakeBanner(const filesystem::path& specfile_path, const filesystem::path& outfile_path) {
    std::ofstream ostream(outfile_path, std::ios::binary);
    if (!ostream.is_open()) {
#ifdef _MSC_VER
        printf("error: could not open %ls for writing\n", outfile_path.c_str());
#else
        printf("error: could not open %s for writing\n", outfile_path.c_str());
#endif
        return false;
    }

    SpecFileData specfile_data = {};
    try {
        specfile_data = ParseSpecFile(specfile_path);
    } catch (std::runtime_error& e) {
        printf("error: %s\n", e.what());
        return false;
    }

    Banner banner = {};

    banner.version = specfile_data.version;
    banner.bitmap = GetIconBitmap(specfile_data.icon_bitmap_filename);
    banner.palette = GetIconPalette(specfile_data.icon_palette_filename);

    std::copy(specfile_data.japanese_title.begin(), specfile_data.japanese_title.end(), banner.japanese_title.data());
    std::copy(specfile_data.english_title.begin(), specfile_data.english_title.end(), banner.english_title.data());
    std::copy(specfile_data.french_title.begin(), specfile_data.french_title.end(), banner.french_title.data());
    std::copy(specfile_data.german_title.begin(), specfile_data.german_title.end(), banner.german_title.data());
    std::copy(specfile_data.italian_title.begin(), specfile_data.italian_title.end(), banner.italian_title.data());
    std::copy(specfile_data.spanish_title.begin(), specfile_data.spanish_title.end(), banner.spanish_title.data());

    // checksum the banner data, starting from the icon bitmap and ending at the end of the file.
    banner.crc = CalculateCRC16FromBannerData(banner.bitmap.data());

    // check against diamond's icon crc
    // if (banner.crc != 0x048B) {
    //     printf("CRC did not match (expected 0x048B, got 0x%04X)\n", banner.crc);
    // } else {
    //     printf("CRC matched\n");
    // }

    OutputBanner(ostream, banner);
    return true;
}
