#include "global.h"
#include "nitro/NNS_g3d.h"
#include "camera.h"
#include "GX_g3.h"
#include "fx.h"
#include "heap.h"

extern fx16 CalcAngleBetweenVecs(VecFx32 * a, VecFx32 * b);

GXBufferMode g3dDepthBufferingMode = GX_BUFFERMODE_W;
static struct Camera * sCameraPtr;

void Camera_OffsetLookAtPosAndTarget(const VecFx32 *delta, struct Camera * camera);
void Camera_ApplyPerspectiveType(u8 perspectiveType, struct Camera * camera);

void Camera_CalcLookAtPosFromTargetAndAngle(struct Camera * camera)
{
    u16 negx = -camera->angle.x;
    camera->lookAt.camPos.x = FX_Mul(FX_Mul(FX_SinIdx(camera->angle.y), camera->distance), FX_CosIdx(camera->angle.x));
    camera->lookAt.camPos.z = FX_Mul(FX_Mul(FX_CosIdx(camera->angle.y), camera->distance), FX_CosIdx(camera->angle.x));
    camera->lookAt.camPos.y = FX_Mul(FX_SinIdx(negx), camera->distance);
    VEC_Add(&camera->lookAt.camPos, &camera->lookAt.camTarget, &camera->lookAt.camPos);
}

void Camera_CalcLookAtTargetFromPosAndAngle(struct Camera * camera)
{
    u16 negx = -camera->angle.x;
    camera->lookAt.camTarget.x = -FX_Mul(FX_Mul(FX_SinIdx(camera->angle.y), camera->distance), FX_CosIdx(camera->angle.x));
    camera->lookAt.camTarget.z = -FX_Mul(FX_Mul(FX_CosIdx(camera->angle.y), camera->distance), FX_CosIdx(camera->angle.x));
    camera->lookAt.camTarget.y = -FX_Mul(FX_SinIdx(negx), camera->distance);
    VEC_Add(&camera->lookAt.camTarget, &camera->lookAt.camPos, &camera->lookAt.camTarget);
}

void Camera_InitInternal(u16 perspectiveAngle, struct Camera * camera)
{
    camera->perspectiveAngle = perspectiveAngle;
    camera->perspective.fovySin = FX_SinIdx(perspectiveAngle);
    camera->perspective.fovyCos = FX_CosIdx(perspectiveAngle);
    camera->perspective.aspect = FX32_CONST(1.33333333); // 4x3
    camera->perspective.near = FX32_CONST(150);
    camera->perspective.far = FX32_CONST(900);
    camera->lookAt.camUp.x = 0;
    camera->lookAt.camUp.y = FX32_ONE;
    camera->lookAt.camUp.z = 0;
    camera->currTarget_p = NULL;
    camera->enableOffsetX = FALSE;
    camera->enableOffsetY = FALSE;
    camera->enableOffsetZ = FALSE;
    camera->history = NULL;
}

void Camera_VecResetCoordsIfOffsetComponentNotEnabled(struct Camera * camera, VecFx32 * vec)
{
    if (!camera->enableOffsetX)
        vec->x = 0;
    if (!camera->enableOffsetY)
        vec->y = 0;
    if (!camera->enableOffsetZ)
        vec->z = 0;
}

void Camera_GetVecFromSomeRingBufferMaybe(struct Camera * camera, const VecFx32 * vecDefault, VecFx32 * vecDst)
{
    s32 * idx_p;
    s32 * idx2_p;
    if (camera->history == NULL)
    {
        *vecDst = *vecDefault;
    }
    else
    {
        idx_p = &camera->history->readIdx;
        idx2_p = &camera->history->writeIdx;
        if (!camera->history->overrideEnabled)
        {
            *vecDst = *vecDefault;
            if (*idx_p == camera->history->writeIdxInit)
                camera->history->overrideEnabled = TRUE;
        }
        else
        {
            *vecDst = camera->history->vecs[camera->history->readIdx];
        }
        *idx_p = (*idx_p + 1) % camera->history->count;
        camera->history->vecs[*idx2_p] = *vecDefault;
        *idx2_p = (*idx2_p + 1) % camera->history->count;
        if (!camera->history->enableUpdateX)
            vecDst->x = vecDefault->x;
        if (!camera->history->enableUpdateY)
            vecDst->y = vecDefault->y;
        if (!camera->history->enableUpdateZ)
            vecDst->z = vecDefault->z;
    }
}

void Camera_AllocHistory(s32 count, s32 initialWriteIdx, s32 updateEnableFlags, s32 heap_id, struct Camera * camera)
{
    s32 i;
    struct CameraHistory * history;

    if (camera->currTarget_p != NULL)
    {
        GF_ASSERT(initialWriteIdx + 1 <= count);
        history = AllocFromHeap(heap_id, sizeof(struct CameraHistory));
        history->vecs = AllocFromHeap(heap_id, sizeof(VecFx32) * count);
        for (i = 0; i < count; i++)
        {
            history->vecs[i].x = 0;
            history->vecs[i].y = 0;
            history->vecs[i].z = 0;
        }
        history->count = count;
        history->readIdx = 0;
        history->writeIdx = initialWriteIdx;
        history->writeIdxInit = initialWriteIdx;
        history->overrideEnabled = FALSE;
        history->enableUpdateX = FALSE;
        history->enableUpdateY = FALSE;
        history->enableUpdateZ = FALSE;
        if (updateEnableFlags & 1)
            history->enableUpdateX = TRUE;
        if (updateEnableFlags & 2)
            history->enableUpdateY = TRUE;
        if (updateEnableFlags & 4)
            history->enableUpdateZ = TRUE;
        camera->history = history;
    }
}

void Camera_FreeHistory(struct Camera * camera)
{
    if (camera->history != NULL)
    {
        FreeToHeap(camera->history->vecs);
        FreeToHeap(camera->history);
        camera->history = NULL;
    }
}

struct Camera * Camera_Alloc(u32 heap_id)
{
    return AllocFromHeap(heap_id, sizeof(struct Camera));
}

void Camera_Free(struct Camera * camera)
{
    FreeToHeap(camera);
}

void Camera_Copy(struct Camera * src, struct Camera * dest)
{
    *dest = *src;
}

void Camera_SetWorkPtr(struct Camera * camera)
{
    sCameraPtr = camera;
}

void Camera_UnsetWorkPtr(void)
{
    sCameraPtr = NULL;
}

void Camera_PushLookAtToNNSGlb(void)
{
    VecFx32 diff;
    VecFx32 offset;
    if (sCameraPtr != NULL)
    {
        if (sCameraPtr->currTarget_p != NULL)
        {
            VEC_Subtract(sCameraPtr->currTarget_p, &sCameraPtr->lastTarget, &diff);
            Camera_VecResetCoordsIfOffsetComponentNotEnabled(sCameraPtr, &diff);
            Camera_GetVecFromSomeRingBufferMaybe(sCameraPtr, &diff, &offset);
            Camera_OffsetLookAtPosAndTarget(&offset, sCameraPtr);
            sCameraPtr->lastTarget = *sCameraPtr->currTarget_p;
        }
        NNS_G3dGlbLookAt(&sCameraPtr->lookAt.camPos, &sCameraPtr->lookAt.camUp, &sCameraPtr->lookAt.camTarget);
    }
}

void Camera_SetLookAtCamUp(VecFx32 * camUp, struct Camera * camera)
{
    camera->lookAt.camUp = *camUp;
}

void Camera_SetFixedTarget(VecFx32 * target, struct Camera * camera)
{
    camera->currTarget_p = target;
    camera->lastTarget = *target;
    camera->enableOffsetX = TRUE;
    camera->enableOffsetY = TRUE;
    camera->enableOffsetZ = TRUE;
}

void Camera_ClearFixedTarget(struct Camera * camera)
{
    camera->currTarget_p = NULL;
    camera->enableOffsetX = FALSE;
    camera->enableOffsetY = FALSE;
    camera->enableOffsetZ = FALSE;
}

void Camera_SetPerspectiveClippingPlane(s32 n, s32 f, struct Camera * camera)
{
    camera->perspective.near = n;
    camera->perspective.far = f,
        Camera_ApplyPerspectiveType(camera->perspectiveType, camera);
}

void Camera_InitWithTargetAndAngle(VecFx32 * target, fx32 distance, struct CameraAngle * angle, u16 perspectiveAngle, u8 perspectiveType, BOOL fixReference, struct Camera * camera)
{
    Camera_InitInternal(perspectiveAngle, camera);
    camera->lookAt.camTarget = *target;
    camera->distance = distance;
    camera->angle = *angle;
    Camera_CalcLookAtPosFromTargetAndAngle(camera);
    Camera_ApplyPerspectiveType(perspectiveType, camera);
    if (fixReference)
    {
        camera->currTarget_p = target;
        camera->lastTarget = *target;
        camera->enableOffsetX = TRUE;
        camera->enableOffsetY = TRUE;
        camera->enableOffsetZ = TRUE;
    }
}

void Camera_InitWithPosAndAngle(VecFx32 * pos, fx32 distance, struct CameraAngle * angle, u16 perspectiveAngle, u8 sp18, struct Camera * camera)
{
    Camera_InitInternal(perspectiveAngle, camera);
    camera->lookAt.camPos = *pos;
    camera->distance = distance;
    camera->angle = *angle;
    Camera_CalcLookAtTargetFromPosAndAngle(camera);
    Camera_ApplyPerspectiveType(sp18, camera);
}

void Camera_InitWithPosAndTarget(const VecFx32 *target, const VecFx32 *pos, u16 perspectiveAngle, u8 perspectiveType, BOOL setReference, struct Camera * camera)
{
    VecFx32 vec_from_pos_to_target;
    Camera_InitInternal(perspectiveAngle, camera);

    camera->lookAt.camTarget = *target;
    camera->lookAt.camPos = *pos;

    VEC_Subtract(pos, target, &vec_from_pos_to_target);
    camera->distance = VEC_Mag(&vec_from_pos_to_target);
    {
        VecFx32 sp24 = {0, 0, 0}; // unused
        VecFx32 sp18 = {0, 0, 0}; // unused
        VecFx32 sp0C = {0, 0, 0};
        VecFx32 sp00;

        sp00.x = 0;
        sp00.y = 0;
        sp00.z = FX32_ONE;
        sp0C = vec_from_pos_to_target;
        sp0C.y = 0;
        camera->angle.y = CalcAngleBetweenVecs(&sp00, &sp0C);

        sp00.x = FX32_ONE;
        sp00.y = 0;
        sp00.z = 0;
        sp0C.x = vec_from_pos_to_target.z;
        sp0C.z = vec_from_pos_to_target.y;
        sp0C.y = 0;
        camera->angle.x = CalcAngleBetweenVecs(&sp00, &sp0C);

        camera->angle.z = 0;
    }
    Camera_ApplyPerspectiveType(perspectiveType, camera);

    if (setReference)
    {
        camera->currTarget_p = target;
        camera->lastTarget = *target;
        camera->enableOffsetX = TRUE;
        camera->enableOffsetY = TRUE;
        camera->enableOffsetZ = TRUE;
    }
}

void Camera_ApplyPerspectiveType(u8 perspectiveType, struct Camera * camera)
{
    if (perspectiveType == 0)
    {
        NNS_G3dGlbPerspective(camera->perspective.fovySin, camera->perspective.fovyCos, camera->perspective.aspect, camera->perspective.near, camera->perspective.far);
        camera->perspectiveType = 0;
        g3dDepthBufferingMode = GX_BUFFERMODE_Z;
    }
    else
    {
        fx32 y = FX_Mul(FX_Div(camera->perspective.fovySin, camera->perspective.fovyCos), camera->distance);
        fx32 x = FX_Mul(y, camera->perspective.aspect);
        NNS_G3dGlbOrtho(y, -y, -x, x, camera->perspective.near, camera->perspective.far);
        camera->perspectiveType = 1;
        g3dDepthBufferingMode = GX_BUFFERMODE_Z;
    }
}

void Camera_SetPerspectiveAngle(u16 perspectiveAngle, struct Camera * camera)
{
    camera->perspectiveAngle = perspectiveAngle;
    camera->perspective.fovySin = FX_SinIdx(camera->perspectiveAngle);
    camera->perspective.fovyCos = FX_CosIdx(camera->perspectiveAngle);
    Camera_ApplyPerspectiveType(camera->perspectiveType, camera);
}

void Camera_AdjustPerspectiveAngle(u16 rotation, struct Camera * camera)
{
    camera->perspectiveAngle += rotation;
    camera->perspective.fovySin = FX_SinIdx(camera->perspectiveAngle);
    camera->perspective.fovyCos = FX_CosIdx(camera->perspectiveAngle);
    Camera_ApplyPerspectiveType(camera->perspectiveType, camera);
}

void Camera_OffsetLookAtPosAndTarget(const VecFx32 *delta, struct Camera * camera)
{
    VEC_Add(&camera->lookAt.camPos, delta, &camera->lookAt.camPos);
    VEC_Add(&camera->lookAt.camTarget, delta, &camera->lookAt.camTarget);
}

void Camera_SetAngle(const struct CameraAngle * angle, struct Camera * camera)
{
    camera->angle = *angle;
    Camera_CalcLookAtPosFromTargetAndAngle(camera);
}

void Camera_AdjustAngle(const struct CameraAngle * delta, struct Camera * camera)
{
    camera->angle.x += delta->x;
    camera->angle.y += delta->y;
    camera->angle.z += delta->z;
    Camera_CalcLookAtTargetFromPosAndAngle(camera);
}

void Camera_SetDistance(fx32 distance, struct Camera * camera)
{
    camera->distance = distance;
    Camera_CalcLookAtPosFromTargetAndAngle(camera);
}

void Camera_SetLookAtTargetAndRecalcPos(const VecFx32 * target, struct Camera * camera)
{
    camera->lookAt.camTarget = *target;
    Camera_CalcLookAtPosFromTargetAndAngle(camera);
}

u16 Camera_GetPerspectiveAngle(struct Camera * camera)
{
    return camera->perspectiveAngle;
}

fx32 Camera_GetDistance(struct Camera * camera)
{
    return camera->distance;
}

void Camera_GetAngle(struct CameraAngle * dest, struct Camera * camera)
{
    *dest = camera->angle;
}

void Camera_GetLookAtCamTarget(VecFx32 * dest, const struct Camera * camera)
{
    *dest = camera->lookAt.camTarget;
}
void Camera_GetLookAtCamPos(VecFx32 * dest, const struct Camera * camera)
{
    *dest = camera->lookAt.camPos;
}

void Camera_SetLookAtCamTarget(const VecFx32 * target, struct Camera * camera)
{
    camera->lookAt.camTarget = *target;
}

void Camera_SetLookAtCamPos(const VecFx32 * pos, struct Camera * camera)
{
    camera->lookAt.camPos = *pos;
}
