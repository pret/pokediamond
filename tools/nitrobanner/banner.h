#pragma once

#include <array>
#include "types.h"

constexpr int TITLE_LENGTH = 0x100 / sizeof(u16); // 128 UTF-16 characters
constexpr int ICON_BITMAP_SIZE = 0x200; // 512 bytes
constexpr int ICON_PALETTE_SIZE = 0x20; // 32 bytes

struct SpecFileData {
    u16 version;
    std::wstring icon_bitmap_filename;
    std::wstring icon_palette_filename;
    std::u16string japanese_title;
    std::u16string english_title;
    std::u16string french_title;
    std::u16string german_title;
    std::u16string italian_title;
    std::u16string spanish_title;
};

using IconBitmap = std::array<u8, ICON_BITMAP_SIZE>;
using IconPalette = std::array<u8, ICON_PALETTE_SIZE>;

struct Banner {
    u16 version;
    u16 crc;
    const std::array<u16, 3> crc_padding {};
    const std::array<u8, 0x16> padding {};
    IconBitmap bitmap {};
    IconPalette palette {};
    std::array<u16, TITLE_LENGTH> japanese_title {};
    std::array<u16, TITLE_LENGTH> english_title {};
    std::array<u16, TITLE_LENGTH> french_title {};
    std::array<u16, TITLE_LENGTH> german_title {};
    std::array<u16, TITLE_LENGTH> italian_title {};
    std::array<u16, TITLE_LENGTH> spanish_title {};
};
static_assert(sizeof(Banner) == 0x840, "Size of banner struct is wrong");

template <typename T>
void SerializeData(std::ofstream& ostream, T data);

void ProcessSpecFileCommand(SpecFileData& specfile_data, const std::wstring_view& command_name, const std::wstring_view& command_argument);
SpecFileData ParseSpecFile(const filesystem::path& specfile_path);

IconBitmap GetIconBitmap(const filesystem::path& icon_bitmap_filename);
IconPalette GetIconPalette(const filesystem::path& icon_palette_filename);

void OutputBanner(std::ofstream& ostream, const Banner& banner);
bool MakeBanner(const filesystem::path& specfile_path, const filesystem::path& outfile_path);

inline bool CommandIsForTitleAndDeveloper(const std::wstring& command_name) {
    return command_name == L"JP" ||
           command_name == L"EN" ||
           command_name == L"FR" ||
           command_name == L"GE" ||
           command_name == L"IT" ||
           command_name == L"SP";
}
