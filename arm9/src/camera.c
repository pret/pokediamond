#include "global.h"
#include "nitro/NNS_g3d.h"
#include "camera.h"
#include "GX_g3.h"
#include "fx.h"
#include "heap.h"

extern fx16 CalcAngleBetweenVecs(VecFx32 * a, VecFx32 * b);

GXBufferMode g3dDepthBufferingMode = GX_BUFFERMODE_W;
static struct CameraWork * sCameraWorkPtr;

void Camera_OffsetLookAtPosAndTarget(const VecFx32 *delta, struct CameraWork * camera);
void Camera_ApplyPerspectiveType(u8 perspectiveType, struct CameraWork * camera);

THUMB_FUNC void Camera_CalcLookAtPosFromTargetAndAngle(struct CameraWork * camera)
{
    u16 negx = -camera->angle.x;
    camera->lookAt.camPos.x = FX_Mul(FX_Mul(FX_SinIdx(camera->angle.y), camera->distance), FX_CosIdx(camera->angle.x));
    camera->lookAt.camPos.z = FX_Mul(FX_Mul(FX_CosIdx(camera->angle.y), camera->distance), FX_CosIdx(camera->angle.x));
    camera->lookAt.camPos.y = FX_Mul(FX_SinIdx(negx), camera->distance);
    VEC_Add(&camera->lookAt.camPos, &camera->lookAt.camTarget, &camera->lookAt.camPos);
}

THUMB_FUNC void Camera_CalcLookAtTargetFromPosAndAngle(struct CameraWork * camera)
{
    u16 negx = -camera->angle.x;
    camera->lookAt.camTarget.x = -FX_Mul(FX_Mul(FX_SinIdx(camera->angle.y), camera->distance), FX_CosIdx(camera->angle.x));
    camera->lookAt.camTarget.z = -FX_Mul(FX_Mul(FX_CosIdx(camera->angle.y), camera->distance), FX_CosIdx(camera->angle.x));
    camera->lookAt.camTarget.y = -FX_Mul(FX_SinIdx(negx), camera->distance);
    VEC_Add(&camera->lookAt.camTarget, &camera->lookAt.camPos, &camera->lookAt.camTarget);
}

THUMB_FUNC void Camera_InitInternal(u16 perspectiveAngle, struct CameraWork * camera)
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

THUMB_FUNC void Camera_VecResetCoordsIfOffsetComponentNotEnabled(struct CameraWork * camera, VecFx32 * vec)
{
    if (!camera->enableOffsetX)
        vec->x = 0;
    if (!camera->enableOffsetY)
        vec->y = 0;
    if (!camera->enableOffsetZ)
        vec->z = 0;
}

THUMB_FUNC void Camera_GetVecFromSomeRingBufferMaybe(struct CameraWork * camera, const VecFx32 * vecDefault, VecFx32 * vecDst)
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

THUMB_FUNC void Camera_AllocHistory(s32 count, s32 initialWriteIdx, s32 updateEnableFlags, s32 heap_id, struct CameraWork * camera)
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

THUMB_FUNC void Camera_FreeHistory(struct CameraWork * camera)
{
    if (camera->history != NULL)
    {
        FreeToHeap(camera->history->vecs);
        FreeToHeap(camera->history);
        camera->history = NULL;
    }
}

THUMB_FUNC struct CameraWork * Camera_Alloc(u32 heap_id)
{
    return AllocFromHeap(heap_id, sizeof(struct CameraWork));
}

THUMB_FUNC void Camera_Free(struct CameraWork * camera)
{
    FreeToHeap(camera);
}

THUMB_FUNC void Camera_Copy(struct CameraWork * src, struct CameraWork * dest)
{
    *dest = *src;
}

THUMB_FUNC void Camera_SetWorkPtr(struct CameraWork * camera)
{
    sCameraWorkPtr = camera;
}

THUMB_FUNC void Camera_UnsetWorkPtr(void)
{
    sCameraWorkPtr = NULL;
}

THUMB_FUNC void Camera_PushLookAtToNNSGlb(void)
{
    VecFx32 diff;
    VecFx32 offset;
    if (sCameraWorkPtr != NULL)
    {
        if (sCameraWorkPtr->currTarget_p != NULL)
        {
            VEC_Subtract(sCameraWorkPtr->currTarget_p, &sCameraWorkPtr->lastTarget, &diff);
            Camera_VecResetCoordsIfOffsetComponentNotEnabled(sCameraWorkPtr, &diff);
            Camera_GetVecFromSomeRingBufferMaybe(sCameraWorkPtr, &diff, &offset);
            Camera_OffsetLookAtPosAndTarget(&offset, sCameraWorkPtr);
            sCameraWorkPtr->lastTarget = *sCameraWorkPtr->currTarget_p;
        }
        NNS_G3dGlbLookAt(&sCameraWorkPtr->lookAt.camPos, &sCameraWorkPtr->lookAt.camUp, &sCameraWorkPtr->lookAt.camTarget);
    }
}

THUMB_FUNC void Camera_SetLookAtCamUp(VecFx32 * camUp, struct CameraWork * camera)
{
    camera->lookAt.camUp = *camUp;
}

THUMB_FUNC void Camera_SetFixedTarget(VecFx32 * target, struct CameraWork * camera)
{
    camera->currTarget_p = target;
    camera->lastTarget = *target;
    camera->enableOffsetX = TRUE;
    camera->enableOffsetY = TRUE;
    camera->enableOffsetZ = TRUE;
}

THUMB_FUNC void Camera_ClearFixedTarget(struct CameraWork * camera)
{
    camera->currTarget_p = NULL;
    camera->enableOffsetX = FALSE;
    camera->enableOffsetY = FALSE;
    camera->enableOffsetZ = FALSE;
}

THUMB_FUNC void Camera_SetPerspectiveClippingPlane(s32 n, s32 f, struct CameraWork * camera)
{
    camera->perspective.near = n;
    camera->perspective.far = f,
        Camera_ApplyPerspectiveType(camera->perspectiveType, camera);
}

THUMB_FUNC void Camera_InitWithTargetAndAngle(VecFx32 * target, fx32 distance, struct CameraAngle * angle, u16 perspectiveAngle, u8 perspectiveType, BOOL fixReference, struct CameraWork * camera)
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

THUMB_FUNC void Camera_InitWithPosAndAngle(VecFx32 * pos, fx32 distance, struct CameraAngle * angle, u16 perspectiveAngle, u8 sp18, struct CameraWork * camera)
{
    Camera_InitInternal(perspectiveAngle, camera);
    camera->lookAt.camPos = *pos;
    camera->distance = distance;
    camera->angle = *angle;
    Camera_CalcLookAtTargetFromPosAndAngle(camera);
    Camera_ApplyPerspectiveType(sp18, camera);
}

THUMB_FUNC void Camera_InitWithPosAndTarget(const VecFx32 *target, const VecFx32 *pos, u16 perspectiveAngle, u8 perspectiveType, BOOL setReference, struct CameraWork * camera)
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

THUMB_FUNC void Camera_ApplyPerspectiveType(u8 perspectiveType, struct CameraWork * camera)
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

THUMB_FUNC void Camera_SetPerspectiveAngle(u16 perspectiveAngle, struct CameraWork * camera)
{
    camera->perspectiveAngle = perspectiveAngle;
    camera->perspective.fovySin = FX_SinIdx(camera->perspectiveAngle);
    camera->perspective.fovyCos = FX_CosIdx(camera->perspectiveAngle);
    Camera_ApplyPerspectiveType(camera->perspectiveType, camera);
}

THUMB_FUNC void Camera_AdjustPerspectiveAngle(u16 rotation, struct CameraWork * camera)
{
    camera->perspectiveAngle += rotation;
    camera->perspective.fovySin = FX_SinIdx(camera->perspectiveAngle);
    camera->perspective.fovyCos = FX_CosIdx(camera->perspectiveAngle);
    Camera_ApplyPerspectiveType(camera->perspectiveType, camera);
}

THUMB_FUNC void Camera_OffsetLookAtPosAndTarget(const VecFx32 *delta, struct CameraWork * camera)
{
    VEC_Add(&camera->lookAt.camPos, delta, &camera->lookAt.camPos);
    VEC_Add(&camera->lookAt.camTarget, delta, &camera->lookAt.camTarget);
}

THUMB_FUNC void Camera_SetAngle(const struct CameraAngle * angle, struct CameraWork * camera)
{
    camera->angle = *angle;
    Camera_CalcLookAtPosFromTargetAndAngle(camera);
}

THUMB_FUNC void Camera_AdjustAngle(const struct CameraAngle * delta, struct CameraWork * camera)
{
    camera->angle.x += delta->x;
    camera->angle.y += delta->y;
    camera->angle.z += delta->z;
    Camera_CalcLookAtTargetFromPosAndAngle(camera);
}

THUMB_FUNC void Camera_SetDistance(fx32 distance, struct CameraWork * camera)
{
    camera->distance = distance;
    Camera_CalcLookAtPosFromTargetAndAngle(camera);
}

THUMB_FUNC void Camera_SetLookAtTargetAndRecalcPos(const VecFx32 * target, struct CameraWork * camera)
{
    camera->lookAt.camTarget = *target;
    Camera_CalcLookAtPosFromTargetAndAngle(camera);
}

THUMB_FUNC u16 Camera_GetPerspectiveAngle(struct CameraWork * camera)
{
    return camera->perspectiveAngle;
}

THUMB_FUNC fx32 Camera_GetDistance(struct CameraWork * camera)
{
    return camera->distance;
}

THUMB_FUNC void Camera_GetAngle(struct CameraAngle * dest, struct CameraWork * camera)
{
    *dest = camera->angle;
}

THUMB_FUNC void Camera_GetLookAtCamTarget(VecFx32 * dest, const struct CameraWork * camera)
{
    *dest = camera->lookAt.camTarget;
}
THUMB_FUNC void Camera_GetLookAtCamPos(VecFx32 * dest, const struct CameraWork * camera)
{
    *dest = camera->lookAt.camPos;
}

THUMB_FUNC void Camera_SetLookAtCamTarget(const VecFx32 * target, struct CameraWork * camera)
{
    camera->lookAt.camTarget = *target;
}

THUMB_FUNC void Camera_SetLookAtCamPos(const VecFx32 * pos, struct CameraWork * camera)
{
    camera->lookAt.camPos = *pos;
}
