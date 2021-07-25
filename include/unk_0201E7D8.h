#ifndef POKEDIAMOND_UNK_0201E7D8_H
#define POKEDIAMOND_UNK_0201E7D8_H

#include "fx.h"


struct CameraHistory
{
    s32 count;
    s32 readIdx;
    s32 writeIdx;
    s32 writeIdxInit;
    BOOL overrideEnabled;
    BOOL enableUpdateX;
    BOOL enableUpdateY;
    BOOL enableUpdateZ;
    VecFx32 * vecs;
};

struct CameraAngle
{
    u16 x;
    u16 y;
    u16 z;
    u16 unused;
};

struct CameraPerspective
{
    fx32 fovySin;
    fx32 fovyCos;
    fx32 aspect;
    fx32 near;
    fx32 far;
};

struct CameraLookAt
{
    VecFx32 camPos;
    VecFx32 camTarget;
    VecFx32 camUp;
};

struct CameraWork
{
    struct CameraPerspective perspective;
    struct CameraLookAt lookAt;
    fx32 distance;
    struct CameraAngle angle;
    u8 perspectiveType;
    u16 perspectiveAngle;
    VecFx32 lastTarget;
    const VecFx32 * currTarget_p;
    BOOL enableOffsetX;
    BOOL enableOffsetY;
    BOOL enableOffsetZ;
    struct CameraHistory * history;
};


#endif //POKEDIAMOND_UNK_0201E7D8_H
