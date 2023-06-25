#ifndef POKEDIAMOND_OVERLAY_MANAGER_H
#define POKEDIAMOND_OVERLAY_MANAGER_H

#include "nitro/types.h"
#include "heap.h"

struct OverlayManager;

typedef struct OverlayManagerTemplate
{
    BOOL (*initFunc)(struct OverlayManager *manager, u32 *status);
    BOOL (*mainFunc)(struct OverlayManager *manager, u32 *status);
    BOOL (*exitFunc)(struct OverlayManager *manager, u32 *status);
    FSOverlayID ovly;
} OverlayManagerTemplate;

struct OverlayManager
{
    struct OverlayManagerTemplate template;
    u32 managerStatus;
    u32 overlayStatus;
    s32 * unk18; //args?
    void * data;
    struct SaveData *save;
    u32 unk24;
};

struct OverlayManager * OverlayManager_New(const struct OverlayManagerTemplate *template, s32 * a1, HeapID heapId);
void OverlayManager_Delete(struct OverlayManager * overlayManager);
void * OverlayManager_CreateAndGetData(struct OverlayManager * overlayManager, u32 size, HeapID heapId);
void * OverlayManager_GetData(struct OverlayManager * overlayManager);
void OverlayManager_FreeData(struct OverlayManager * overlayManager);
s32 * OverlayManager_GetField18(struct OverlayManager * overlayManager);
BOOL OverlayManager_Run(struct OverlayManager * overlayManager);

#endif //POKEDIAMOND_OVERLAY_MANAGER_H
