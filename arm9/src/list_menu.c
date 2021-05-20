#pragma thumb on

#include "global.h"
#include "heap.h"
#include "list_menu.h"

extern void * FUN_02013690(u32 heap_id);
extern void FUN_020136E0(void *, u32);
extern void FUN_02019620(struct Window *, u32);
void FUN_02001714(struct ListMenu *, u16, u16, u16);
void FUN_020017AC(struct ListMenu *);
void FUN_02001B64(struct ListMenu *, BOOL);
extern void CopyWindowToVram(struct Window *);

struct ListMenu * ListMenuInit(const struct ListMenuTemplate * template, u16 cursorPos, u16 itemsAbove, u32 heap_id)
{
    struct ListMenu * list = AllocFromHeap(heap_id, sizeof(struct ListMenu));
    list->template = *template;
    list->unk_28 = FUN_02013690(heap_id);
    list->cursorPos = cursorPos;
    list->itemsAbove = itemsAbove;
    list->unk_30 = 0;
    list->unk_31 = 0;
    list->taskId = 0xFF;
    list->unk_33 = 0;
    list->heap_id = (u8)heap_id;
    list->cursorPal = list->template.cursorPal;
    list->fillValue = list->template.fillValue;
    list->cursorShadowPal = list->template.cursorShadowPal;
    list->lettersSpacing = list->template.lettersSpacing;
    list->fontId = list->template.fontId;
    list->enabled = 0;
    if (list->template.totalItems < list->template.maxShowed)
        list->template.maxShowed = list->template.totalItems;
    FUN_020136E0(
        list->unk_28,
        (u32)(
            ((u32)(list->template.cursorPal << 24) >> 8)
            | ((u32)(list->template.cursorShadowPal << 24) >> 16)
            | ((u32)(list->template.fillValue << 24) >> 24)
        )
    );
    FUN_02019620(list->template.window, list->template.fillValue);
    FUN_02001714(list, list->cursorPos, 0, list->template.maxShowed);
    FUN_020017AC(list);
    FUN_02001B64(list, 1);
    CopyWindowToVram(template->window);
    return list;
}
