// Copyright (c) 2018 huderlem

#ifndef OPTIONS_H
#define OPTIONS_H

#include <stdbool.h>

struct GbaToPngOptions {
    char *paletteFilePath;
    int bitDepth;
    bool hasTransparency;
    int width;
    int metatileWidth;
    int metatileHeight;
    int palIndex;
};

struct PngToGbaOptions {
    int numTiles;
    int bitDepth;
    int metatileWidth;
    int metatileHeight;
};

struct PngToNtrOptions {
    int numTiles;
    int bitDepth;
    int metatileWidth;
    int metatileHeight;
    bool clobberSize;
    bool byteOrder;
    bool version101;
    bool sopc;
    bool scanned;
    bool wrongSize;
};

struct Attr0 {
    int YCoordinate;
    bool Rotation;
    bool SizeDisable;
    int Mode;
    bool Mosaic;
    int Colours;
    int Shape;
};

struct Attr1 {
    int XCoordinate;
    int RotationScaling;
    int Size;
};

struct Attr2 {
    int CharName;
    int Priority;
    int Palette;
};

struct OAM {
    struct Attr0 attr0;
    struct Attr1 attr1;
    struct Attr2 attr2;
};

struct Cell {
    short readOnly;
    short maxX;
    short maxY;
    short minX;
    short minY;
    struct OAM oam;
};

struct JsonToCellOptions {
    bool labelEnabled;
    bool extended;
    int mappingType;
    int imageHeight;
    int imageWidth;
    int cellCount;
    struct Cell **cells;
    char **labels;
    int labelCount;
};

struct JsonToScreenOptions {
    int height;
    int width;
    unsigned short *data;
    int bitdepth;
};

struct SequenceData {
    short frameNumber;
    short loopStartFrame;
    short animationElement;
    short animationType;
    int playbackMode;
};

struct AnimationDataSRT {
    short index;
    unsigned short rotation;
    int scaleX;
    int scaleY;
    short positionX;
    short positionY;
};

struct AnimationDataT {
    short index;
    unsigned short rotation;
    short positionX;
    short positionY;
};

struct AnimationResults {
    union {
        short index;
        struct AnimationDataSRT dataSrt;
        struct AnimationDataT dataT;
    };
};

struct JsonToAnimationOptions {
    short sequenceCount;
    short frameCount;
    struct SequenceData **sequenceData;
    short *frameDelay;
    struct AnimationResults **animationResults;
    bool labelEnabled;
    char **labels;
    int labelCount;
};

#endif // OPTIONS_H
