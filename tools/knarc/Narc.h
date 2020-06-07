#pragma once

#include <cstdint>
#include <experimental/filesystem>
#include <fstream>
#include <string>
#include <vector>

enum class NarcError
{
	None,
	InvalidInputFile,
	InvalidHeaderId,
	InvalidByteOrderMark,
	InvalidVersion,
	InvalidHeaderSize,
	InvalidChunkCount,
	InvalidFileAllocationTableId,
	InvalidFileAllocationTableReserved,
	InvalidFileNameTableId,
	InvalidFileNameTableEntryId,
	InvalidFileImagesId,
	InvalidOutputFile
};

struct Header
{
	uint32_t Id;
	uint16_t ByteOrderMark;
	uint16_t Version;
	uint32_t FileSize;
	uint16_t ChunkSize;
	uint16_t ChunkCount;
};

struct FileAllocationTable
{
	uint32_t Id;
	uint32_t ChunkSize;
	uint16_t FileCount;
	uint16_t Reserved;
};

struct FileAllocationTableEntry
{
	uint32_t Start;
	uint32_t End;
};

struct FileNameTable
{
	uint32_t Id;
	uint32_t ChunkSize;
};

struct FileNameTableEntry
{
	uint32_t Offset;
	uint16_t FirstFileId;
	uint16_t Utility;
};

struct FileImages
{
	uint32_t Id;
	uint32_t ChunkSize;
};

class Narc
{
	public:
		NarcError GetError() const;

		bool Pack(const std::experimental::filesystem::path& fileName, const std::experimental::filesystem::path& directory);
		bool Unpack(const std::experimental::filesystem::path& fileName, const std::experimental::filesystem::path& directory);

	private:
		NarcError error = NarcError::None;

		void AlignDword(std::ofstream& ofs, uint8_t paddingChar);

		bool Cleanup(std::ifstream& ifs, const NarcError& e);
		bool Cleanup(std::ofstream& ofs, const NarcError& e);

		std::vector<std::experimental::filesystem::directory_entry> OrderedDirectoryIterator(const std::experimental::filesystem::path& path, bool recursive) const;
};
