// Copyright (c) 2021 red031000

#include "global.h"
#include "cJSON.h"
#include "json.h"
#include "util.h"
#include <string.h>
#include <stdlib.h>

static inline bool GetBool(cJSON * in)
{
    if (!cJSON_IsBool(in))
        return false;

    return cJSON_IsTrue(in);
}

static inline int GetInt(cJSON * in)
{
    if (!cJSON_IsNumber(in))
        return 0;

    return in->valueint;
}

static inline char *GetString(cJSON * in)
{
    if (!cJSON_IsString(in))
        return NULL;

    return in->valuestring;
}

struct JsonToCellOptions *ParseNCERJson(char *path)
{
    int fileLength;
    unsigned char *jsonString = ReadWholeFile(path, &fileLength);

    cJSON *json = cJSON_Parse((const char *)jsonString);

    struct JsonToCellOptions *options = malloc(sizeof(struct JsonToCellOptions));

    if (json == NULL)
    {
        const char *errorPtr = cJSON_GetErrorPtr();
        FATAL_ERROR("Error in line \"%s\"\n", errorPtr);
    }

    cJSON *labelBool = cJSON_GetObjectItemCaseSensitive(json, "labelEnabled");
    cJSON *extended = cJSON_GetObjectItemCaseSensitive(json, "extended");
    cJSON *imageHeight = cJSON_GetObjectItemCaseSensitive(json, "imageHeight");
    cJSON *imageWidth = cJSON_GetObjectItemCaseSensitive(json, "imageWidth");
    cJSON *cellCount = cJSON_GetObjectItemCaseSensitive(json, "cellCount");

    options->labelEnabled = GetBool(labelBool);
    options->extended = GetBool(extended);
    options->imageHeight = GetInt(imageHeight);
    options->imageWidth = GetInt(imageWidth);
    options->cellCount = GetInt(cellCount);

    options->cells = malloc(sizeof(struct Cell *) * options->cellCount);


    if (options->labelEnabled)
    {
        cJSON *labelCount = cJSON_GetObjectItemCaseSensitive(json, "labelCount");
        options->labelCount = GetInt(labelCount);
        options->labels = malloc(sizeof(char *) * options->labelCount);

        cJSON *labels = cJSON_GetObjectItemCaseSensitive(json, "labels");
        cJSON *label = NULL;

        int j = 0;
        cJSON_ArrayForEach(label, labels)
        {
            char *labelString = GetString(label);
            options->labels[j] = malloc(strlen(labelString) + 1);
            strcpy(options->labels[j], labelString);
            j++;
        }
    }

    for (int i = 0; i < options->cellCount; i++)
    {
        options->cells[i] = malloc(sizeof(struct Cell));
    }

    int i = 0;
    cJSON *cells = cJSON_GetObjectItemCaseSensitive(json, "cells");
    cJSON *cell = NULL;

    cJSON_ArrayForEach(cell, cells)
    {
        if (i > options->cellCount - 1)
            FATAL_ERROR("Cell count is incorrect.\n");

        cJSON *readOnly = cJSON_GetObjectItemCaseSensitive(cell, "readOnly");

        options->cells[i]->readOnly = (short)GetInt(readOnly);
        if (options->extended)
        {
            cJSON *maxX = cJSON_GetObjectItemCaseSensitive(cell, "maxX");
            cJSON *maxY = cJSON_GetObjectItemCaseSensitive(cell, "maxY");
            cJSON *minX = cJSON_GetObjectItemCaseSensitive(cell, "minX");
            cJSON *minY = cJSON_GetObjectItemCaseSensitive(cell, "minY");

            options->cells[i]->maxX = (short)GetInt(maxX);
            options->cells[i]->maxY = (short)GetInt(maxY);
            options->cells[i]->minX = (short)GetInt(minX);
            options->cells[i]->minY = (short)GetInt(minY);
        }
        //OAM data
        cJSON *OAM = cJSON_GetObjectItemCaseSensitive(cell, "OAM");

        //Attr0
        cJSON *Attr0 = cJSON_GetObjectItemCaseSensitive(OAM, "Attr0");

        cJSON *YCoordinate = cJSON_GetObjectItemCaseSensitive(Attr0, "YCoordinate");
        cJSON *Rotation = cJSON_GetObjectItemCaseSensitive(Attr0, "Rotation");
        cJSON *SizeDisable = cJSON_GetObjectItemCaseSensitive(Attr0, "SizeDisable");
        cJSON *Mode = cJSON_GetObjectItemCaseSensitive(Attr0, "Mode");
        cJSON *Mosaic = cJSON_GetObjectItemCaseSensitive(Attr0, "Mosaic");
        cJSON *Colours = cJSON_GetObjectItemCaseSensitive(Attr0, "Colours");
        cJSON *Shape = cJSON_GetObjectItemCaseSensitive(Attr0, "Shape");

        options->cells[i]->oam.attr0.YCoordinate = GetInt(YCoordinate);
        options->cells[i]->oam.attr0.Rotation = GetBool(Rotation);
        options->cells[i]->oam.attr0.SizeDisable = GetBool(SizeDisable);
        options->cells[i]->oam.attr0.Mode = GetInt(Mode);
        options->cells[i]->oam.attr0.Mosaic = GetBool(Mosaic);
        options->cells[i]->oam.attr0.Colours = GetInt(Colours);
        options->cells[i]->oam.attr0.Shape = GetInt(Shape);

        //Attr1
        cJSON *Attr1 = cJSON_GetObjectItemCaseSensitive(OAM, "Attr1");

        cJSON *XCoordinate = cJSON_GetObjectItemCaseSensitive(Attr1, "XCoordinate");
        cJSON *RotationScaling = cJSON_GetObjectItemCaseSensitive(Attr1, "RotationScaling");
        cJSON *Size = cJSON_GetObjectItemCaseSensitive(Attr1, "Size");

        options->cells[i]->oam.attr1.XCoordinate = GetInt(XCoordinate);
        options->cells[i]->oam.attr1.RotationScaling = GetInt(RotationScaling);
        options->cells[i]->oam.attr1.Size = GetInt(Size);

        //Attr2
        cJSON *Attr2 = cJSON_GetObjectItemCaseSensitive(OAM, "Attr2");

        cJSON *CharName = cJSON_GetObjectItemCaseSensitive(Attr2, "CharName");
        cJSON *Priority = cJSON_GetObjectItemCaseSensitive(Attr2, "Priority");
        cJSON *Palette = cJSON_GetObjectItemCaseSensitive(Attr2, "Palette");

        options->cells[i]->oam.attr2.CharName = GetInt(CharName);
        options->cells[i]->oam.attr2.Priority = GetInt(Priority);
        options->cells[i]->oam.attr2.Palette = GetInt(Palette);

        i++;
    }

    cJSON_Delete(json);
    free(jsonString);
    return options;
}

struct JsonToScreenOptions *ParseNSCRJson(char *path)
{
    int fileLength;
    unsigned char *jsonString = ReadWholeFile(path, &fileLength);

    cJSON *json = cJSON_Parse((const char *)jsonString);

    struct JsonToScreenOptions *options = malloc(sizeof(struct JsonToScreenOptions));

    if (json == NULL)
    {
        const char *errorPtr = cJSON_GetErrorPtr();
        FATAL_ERROR("Error in line \"%s\"\n", errorPtr);
    }

    cJSON *Height = cJSON_GetObjectItemCaseSensitive(json, "height");
    cJSON *Width = cJSON_GetObjectItemCaseSensitive(json, "width");

    options->height = GetInt(Height);
    options->width = GetInt(Width);

    options->data = malloc(sizeof(unsigned short) * options->height * options->width);

    cJSON *layer = NULL;
    cJSON *layers = cJSON_GetObjectItemCaseSensitive(json, "layers");
    int palette = 0;
    cJSON *tilesets = cJSON_GetObjectItemCaseSensitive(json, "tilesets");
    int tilesetSize = 0;
    if (cJSON_GetArraySize(tilesets) != 1)
    {
        cJSON *tileset = cJSON_GetArrayItem(tilesets, 1);
        cJSON *firstGid = cJSON_GetObjectItemCaseSensitive(tileset, "firstgid");
        tilesetSize = GetInt(firstGid) - 1;
        if (tilesetSize <= 1)
            FATAL_ERROR("Wrong tileset index (tileset 0 should be added first)\n");
    }

    cJSON_ArrayForEach(layer, layers)
    {
        cJSON *tile = NULL;
        cJSON *data = cJSON_GetObjectItemCaseSensitive(layer, "data");
        int i = 0;
        cJSON_ArrayForEach(tile, data)
        {
            int tileInt = GetInt(tile) - 1;
            if (tileInt != -1)
            {
                if (tilesetSize != 0)
                {
                    palette = tileInt / tilesetSize;
                    tileInt %= tilesetSize;
                }
                bool vFlip = tileInt >> 30;
                bool hFlip = tileInt >> 31;
                tileInt |= vFlip << 11;
                tileInt |= hFlip << 10;
                tileInt |= palette << 12;
                options->data[i] = (short) (tileInt & 0xFFFF);
            }
            i++;
        }
    }

    cJSON_Delete(json);
    free(jsonString);
    return options;
}

void FreeNCERCell(struct JsonToCellOptions *options)
{
    for (int i = 0; i < options->cellCount; i++)
    {
        free(options->cells[i]);
    }
    if (options->labelEnabled)
    {
        for (int j = 0; j < options->labelCount; j++)
        {
            free(options->labels[j]);
        }
        free(options->labels);
    }
    free(options);
}

void FreeNSCRScreen(struct JsonToScreenOptions *options)
{
    free(options->data);
    free(options);
}

