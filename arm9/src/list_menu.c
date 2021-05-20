#pragma thumb on

#include "global.h"
#include "heap.h"
#include "main.h"
#include "list_menu.h"

extern void * FUN_02013690(u32 heap_id);
extern void FUN_020136E0(void *, u32);
extern void FillWindowPixelBuffer(struct Window *, u32);
void ListMenuPrintEntries(struct ListMenu *, u16, u16, u16);
void ListMenuDrawCursor(struct ListMenu *);
BOOL ListMenuChangeSelection(struct ListMenu *, s32, u8, s32);
void ListMenuCallSelectionChangedCallback(struct ListMenu *, BOOL);
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
    FillWindowPixelBuffer(list->template.window, list->template.fillValue);
    ListMenuPrintEntries(list, list->cursorPos, 0, list->template.maxShowed);
    ListMenuDrawCursor(list);
    ListMenuCallSelectionChangedCallback(list, TRUE);
    CopyWindowToVram(template->window);
    return list;
}

s32 ListMenu_ProcessInput(struct ListMenu * list)
{
    list->unk_33 = 0;

    if (gMain.newKeys & REG_PAD_KEYINPUT_A_MASK) {
        return list->template.items[list->cursorPos + list->itemsAbove].index;
    }
    else if (gMain.newKeys & REG_PAD_KEYINPUT_B_MASK) {
        return LIST_CANCEL;
    }
    else if (gMain.newAndRepeatedKeys & REG_PAD_KEYINPUT_UP_MASK) {
        if (!ListMenuChangeSelection(list, TRUE, 1, FALSE))
            list->unk_33 = 1;
        return LIST_NOTHING_CHOSEN;
    }
    else if (gMain.newAndRepeatedKeys & REG_PAD_KEYINPUT_DOWN_MASK) {
        if (!ListMenuChangeSelection(list, TRUE, 1, TRUE))
            list->unk_33 = 2;
        return LIST_NOTHING_CHOSEN;
    }
    else
    {
        u16 rightButton, leftButton;
        switch (list->template.scrollMultiple)
        {
        case LIST_NO_MULTIPLE_SCROLL:
        default:
            leftButton = FALSE;
            rightButton = FALSE;
            break;
        case LIST_MULTIPLE_SCROLL_DPAD:
            leftButton = gMain.newAndRepeatedKeys & REG_PAD_KEYINPUT_LEFT_MASK;
            rightButton = gMain.newAndRepeatedKeys & REG_PAD_KEYINPUT_RIGHT_MASK;
            break;
        case LIST_MULTIPLE_SCROLL_L_R:
            leftButton = gMain.newAndRepeatedKeys & REG_PAD_KEYINPUT_L_MASK;
            rightButton = gMain.newAndRepeatedKeys & REG_PAD_KEYINPUT_R_MASK;
            break;
        }
        if (leftButton)
        {
            if (!ListMenuChangeSelection(list, TRUE, list->template.maxShowed, FALSE))
                list->unk_33 = 3;
            return LIST_NOTHING_CHOSEN;
        }
        else if (rightButton)
        {
            if (!ListMenuChangeSelection(list, TRUE, list->template.maxShowed, TRUE))
                list->unk_33 = 4;
            return LIST_NOTHING_CHOSEN;
        }
        else
        {
            return LIST_NOTHING_CHOSEN;
        }
    }
}
