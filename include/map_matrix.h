#ifndef POKEDIAMOND_MAP_MATRIX_H
#define POKEDIAMOND_MAP_MATRIX_H

#include "heap.h"

#define MAP_MATRIX_MAX_WIDTH 30
#define MAP_MATRIX_MAX_HEIGHT 30
#define MAP_MATRIX_MAX_SIZE (MAP_MATRIX_MAX_WIDTH * MAP_MATRIX_MAX_HEIGHT)

#define MAP_MATRIX_MAX_NAME_LENGTH 16

struct MapData
{
    u16 data[MAP_MATRIX_MAX_SIZE];
};

struct MapMatrixData
{
    u8 height;
    u8 width;
    u16 headers[MAP_MATRIX_MAX_SIZE];
    u8 altitudes[MAP_MATRIX_MAX_SIZE];
    struct MapData maps;
    u8 name[MAP_MATRIX_MAX_NAME_LENGTH];
};

struct MapMatrix
{
    u8 width;
    u8 height;
    u8 matrix_id;
    struct MapMatrixData data;
};

struct MapMatrix *MapMatrix_New(void);
void MapMatrix_Load(u16 map_id, struct MapMatrix *map_matrix);
void MapMatrix_Free(struct MapMatrix *map_matrix);
u16 MapMatrix_GetMapData(s32 map_id, struct MapMatrix *map_matrix);
u8 MapMatrix_GetWidth(struct MapMatrix *map_matrix);
u8 MapMatrix_GetHeight(struct MapMatrix *map_matrix);
u16 MapMatrix_GetMapHeader(struct MapMatrix *map_matrix, s32 x, s32 y);
u16 MapMatrix_GetMapHeaderFromID(struct MapMatrix *map_matrix, s32 map_id);
u8 MapMatrix_GetMatrixID(struct MapMatrix *map_matrix);
u32 MapMatrix_GetMapAltitude(
    struct MapMatrix *map_matrix, u8 param1, s16 x, s16 y, int matrix_width);

struct MapData *MapMatrix_MapData_New(HeapID heapId);
void MapMatrix_MapData_Free(struct MapData *map_data);
u16 MapMatrix_MapData_GetData(struct MapData *map_data, s32 x, s32 y);

u16 GetMapHeader(u32 file_id, u16 x, u16 y);
u16 GetMapData(s32 map_id, struct MapMatrix *map_matrix);
void sub_02034678(struct MapMatrix *map_matrix);
void sub_020346CC(struct MapMatrix *map_matrix);

#endif // POKEDIAMOND_MAP_MATRIX_H
