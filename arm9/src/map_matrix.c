#include "global.h"
#include "map_matrix.h"
#include "MI_memory.h"
#include "filesystem.h"
#include "heap.h"
#include "map_header.h"

static void MapMatrix_MapMatrixData_Load(
    struct MapMatrixData *map_matrix, u16 file_id, u32 map_id)
{
    map_matrix->width = 0;
    map_matrix->height = 0;

    s32 i;
    for (i = 0; i < MAP_MATRIX_MAX_SIZE; i++)
    {
        map_matrix->headers[i] = 0;
        map_matrix->altitudes[i] = 0;
        map_matrix->maps.data[i] = 0;
    }

    for (i = 0; i < MAP_MATRIX_MAX_NAME_LENGTH; i++)
    {
        map_matrix->name[i] = 0;
    }

    void *buffer =
        AllocAtEndAndReadWholeNarcMemberByIdPair(NARC_FIELDDATA_MAPMATRIX_MAP_MATRIX, file_id, HEAP_ID_FIELD);
    u8 *cursor = (u8 *)buffer;

    map_matrix->width = *(cursor++);
    map_matrix->height = *(cursor++);
    u8 has_headers_section = *(cursor++);
    u8 has_altitudes_section = *(cursor++);
    u8 name_length = *(cursor++);

    GF_ASSERT(name_length <= MAP_MATRIX_MAX_NAME_LENGTH);

    MI_CpuCopy8(cursor, &map_matrix->name, name_length);
    cursor += name_length;

    if (has_headers_section != 0)
    {
        MI_CpuCopy8(
            cursor, &map_matrix->headers, map_matrix->width * map_matrix->height * sizeof(u16));
        cursor += map_matrix->width * map_matrix->height * sizeof(u16);
    }
    else
    {
        MIi_CpuClear16((u16)map_id,
            &map_matrix->headers,
            map_matrix->width * map_matrix->height * sizeof(u16));
    }

    if (has_altitudes_section != 0)
    {
        MI_CpuCopy8(
            cursor, &map_matrix->altitudes, map_matrix->width * map_matrix->height * sizeof(u8));
        cursor += map_matrix->width * map_matrix->height * sizeof(u8);
    }

    MI_CpuCopy8(
        cursor, map_matrix->maps.data, map_matrix->width * map_matrix->height * sizeof(u16));
    FreeToHeap(buffer);
}

struct MapMatrix *MapMatrix_New(void)
{
    struct MapMatrix *map_matrix = AllocFromHeap(HEAP_ID_FIELD, sizeof(struct MapMatrix));

    map_matrix->width = 0;
    map_matrix->height = 0;
    map_matrix->matrix_id = 0;

    return map_matrix;
}

void MapMatrix_Load(u16 map_id, struct MapMatrix *map_matrix)
{
    u16 matrix_id = MapHeader_GetMatrixId(map_id);

    MapMatrix_MapMatrixData_Load(&map_matrix->data, matrix_id, map_id);

    map_matrix->matrix_id = (u8)matrix_id;
    map_matrix->height = map_matrix->data.height;
    map_matrix->width = map_matrix->data.width;
}

void MapMatrix_Free(struct MapMatrix *map_matrix)
{
    FreeToHeap(map_matrix);
}

u16 MapMatrix_GetMapData(s32 map_id, struct MapMatrix *map_matrix)
{
    GF_ASSERT(map_id < map_matrix->width * map_matrix->height);

    return map_matrix->data.maps.data[map_id];
}

u8 MapMatrix_GetWidth(struct MapMatrix *map_matrix)
{
    GF_ASSERT(map_matrix != NULL);

    return map_matrix->width;
}

u8 MapMatrix_GetHeight(struct MapMatrix *map_matrix)
{
    GF_ASSERT(map_matrix != NULL);

    return map_matrix->height;
}

u16 MapMatrix_GetMapHeader(struct MapMatrix *map_matrix, s32 x, s32 y)
{
    s32 width = map_matrix->width;
    s32 height = map_matrix->height;

    GF_ASSERT(x >= 0 && x < width);
    GF_ASSERT(y >= 0 && y < height);

    return map_matrix->data.headers[y * width + x];
}

u16 MapMatrix_GetMapHeaderFromID(struct MapMatrix *map_matrix, s32 map_id)
{
    s32 max_map_id = map_matrix->width * map_matrix->height;

    GF_ASSERT(0 <= map_id && map_id < max_map_id);

    return map_matrix->data.headers[map_id];
}

u8 MapMatrix_GetMatrixID(struct MapMatrix *map_matrix)
{
    return map_matrix->matrix_id;
}

u32 MapMatrix_GetMapAltitude(
    struct MapMatrix *map_matrix, u8 param1, s16 x, s16 y, int matrix_width)
{
#pragma unused(param1)
    GF_ASSERT(x < matrix_width);
    GF_ASSERT(y * matrix_width + x < MAP_MATRIX_MAX_SIZE);

    return map_matrix->data.altitudes[y * matrix_width + x];
}

struct MapData *MapMatrix_MapData_New(HeapID heapId)
{
    struct MapData *map_data = AllocFromHeap(heapId, sizeof(struct MapData));
    void *buffer =
        AllocAtEndAndReadWholeNarcMemberByIdPair(NARC_FIELDDATA_MAPMATRIX_MAP_MATRIX, 0, heapId);
    u8 *cursor = (u8 *)buffer;

    cursor += 4;
    u8 name_length = *cursor;
    cursor++;
    cursor += name_length;

    MI_CpuCopy8(cursor, map_data, sizeof(struct MapData));
    FreeToHeap(buffer);

    return map_data;
}

void MapMatrix_MapData_Free(struct MapData *map_data)
{
    GF_ASSERT(map_data != NULL);
    FreeToHeap(map_data);
}

u16 MapMatrix_MapData_GetData(struct MapData *map_data, s32 x, s32 y)
{
    return map_data->data[MAP_MATRIX_MAX_WIDTH * y + x];
}

u16 GetMapHeader(u32 file_id, u16 x, u16 y)
{
    struct MapMatrixData map_matrix;

    MapMatrix_MapMatrixData_Load(&map_matrix, (u16)file_id, 0);
    GF_ASSERT(x < map_matrix.width);
    GF_ASSERT(y < map_matrix.height);

    return map_matrix.headers[y * map_matrix.width + x];
}

u16 GetMapData(s32 map_id, struct MapMatrix *map_matrix)
{
    GF_ASSERT(map_matrix != NULL);
    return MapMatrix_GetMapData(map_id, map_matrix);
}

void sub_02034678(struct MapMatrix *map_matrix)
{
    u16 *maps = map_matrix->data.maps.data;
    u8 *altitudes = map_matrix->data.altitudes;
    u8 width = map_matrix->width;

    if (map_matrix->matrix_id != 0)
    {
        return;
    }

    maps[width * 0x15 + 0x17] = 0xB0;
    maps[width * 0x15 + 0x18] = 0xB0;
    maps[width * 0x16 + 0x17] = 0xB0;
    maps[width * 0x16 + 0x18] = 0xB0;
    altitudes[width * 0x15 + 0x17] = 2;
    altitudes[width * 0x15 + 0x18] = 2;
    altitudes[width * 0x16 + 0x17] = 2;
    altitudes[width * 0x16 + 0x18] = 2;
}

void sub_020346CC(struct MapMatrix *map_matrix)
{
    u16 *maps = map_matrix->data.maps.data;
    u8 width = map_matrix->width;

    if (map_matrix->matrix_id != 0)
    {
        return;
    }

    maps[width * 0x0F + 0x1C] = 0x77;
    maps[width * 0x10 + 0x1B] = 0x78;
    maps[width * 0x10 + 0x1C] = 0x79;
    maps[width * 0x11 + 0x1B] = 0x7A;
}
