#include "overlay_manager.h"

#include "global.h"

#include "heap.h"
#include "main.h"
#include "poke_overlay.h"

struct OverlayManager *OverlayManager_New(const struct OverlayManagerTemplate *template, s32 *a1, HeapID heapId) {
    struct OverlayManager *ret = (struct OverlayManager *)AllocFromHeap(heapId, sizeof(struct OverlayManager));
    ret->template              = *template;
    ret->managerStatus         = 0;
    ret->overlayStatus         = 0;
    ret->unk18                 = a1;
    ret->data                  = NULL;
    ret->save                  = NULL;
    ret->unk24                 = 0;
    return ret;
}

void OverlayManager_Delete(struct OverlayManager *overlayManager) {
    FreeToHeap(overlayManager);
}

void *OverlayManager_CreateAndGetData(struct OverlayManager *overlayManager, u32 size, HeapID heapId) {
    return overlayManager->data = AllocFromHeap(heapId, size);
}

void *OverlayManager_GetData(struct OverlayManager *overlayManager) {
    return overlayManager->data;
}

void OverlayManager_FreeData(struct OverlayManager *overlayManager) {
    FreeToHeap(overlayManager->data);
    overlayManager->data = NULL;
}

s32 *OverlayManager_GetField18(struct OverlayManager *overlayManager) {
    return overlayManager->unk18;
}

BOOL OverlayManager_Run(struct OverlayManager *overlayManager) {
    switch (overlayManager->managerStatus) {
    case 0:
        if (overlayManager->template.ovly != SDK_OVERLAY_INVALID_ID) {
            HandleLoadOverlay(overlayManager->template.ovly, 2);
        }
        overlayManager->managerStatus = 1;
        // fallthrough
    case 1:
        if (overlayManager->template.initFunc(overlayManager, &overlayManager->overlayStatus) == TRUE) {
            overlayManager->managerStatus = 2;
            overlayManager->overlayStatus = 0;
        }
        break;
    case 2:
        if (overlayManager->template.mainFunc(overlayManager, &overlayManager->overlayStatus) == TRUE) {
            overlayManager->managerStatus = 3;
            overlayManager->overlayStatus = 0;
        }
        break;
    case 3:
        if (overlayManager->template.exitFunc(overlayManager, &overlayManager->overlayStatus) == TRUE) {
            if (overlayManager->template.ovly != SDK_OVERLAY_INVALID_ID) {
                UnloadOverlayByID(overlayManager->template.ovly);
            }
            return TRUE;
        }
        break;
    }
    return FALSE;
}
