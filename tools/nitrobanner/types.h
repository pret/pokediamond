#pragma once

#include <cstdint>

#if (__GNUC__ <= 7) && !defined _MSC_VER
#include <experimental/filesystem>
namespace filesystem = std::experimental::filesystem;
#else
#include <filesystem>
namespace filesystem = std::filesystem;
#endif

using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
