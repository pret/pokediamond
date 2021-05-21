#include "global.h"
#include "heap.h"
#include "main.h"
#include "list_menu.h"

extern void * FUN_02013690(u32 heap_id);
extern void CreateListMenuCursorObj(void *, u32);
extern void DestroyListMenuCursorObj(void *);
extern void FillWindowPixelBuffer(struct Window *, u32);
void ListMenuPrintEntries(struct ListMenu *, u16, u16, u16);
void ListMenuDrawCursor(struct ListMenu *);
BOOL ListMenuChangeSelection(struct ListMenu *, u8, u8, s32);
void ListMenuCallSelectionChangedCallback(struct ListMenu *, BOOL);
extern void CopyWindowToVram(struct Window *);

THUMB_FUNC struct ListMenu * ListMenuInit(const struct ListMenuTemplate * template, u16 cursorPos, u16 itemsAbove, u32 heap_id)
{
    struct ListMenu * list = AllocFromHeap(heap_id, sizeof(struct ListMenu));
    list->template = *template;
    list->cursor = FUN_02013690(heap_id);
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
    CreateListMenuCursorObj(
        list->cursor,
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

THUMB_FUNC s32 ListMenu_ProcessInput(struct ListMenu * list)
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

THUMB_FUNC void DestroyListMenu(struct ListMenu * list, u16 * cursorPos, u16 * itemsAbove)
{
    if (cursorPos != NULL)
        *cursorPos = list->cursorPos;
    if (itemsAbove != NULL)
        *itemsAbove = list->itemsAbove;
    DestroyListMenuCursorObj(list->cursor);
    FUN_02016A8C(list->heap_id, list);
}

THUMB_FUNC void RedrawListMenu(struct ListMenu * list)
{
    FillWindowPixelBuffer(list->template.window, list->template.fillValue);
    ListMenuPrintEntries(list, list->cursorPos, 0, list->template.maxShowed);
    ListMenuDrawCursor(list);
    CopyWindowToVram(list->template.window);
}

THUMB_FUNC s32 FUN_02001354(struct ListMenu * list, const struct ListMenuTemplate * template, u16 cursorPos, u16 itemsAbove, u16 updateFlag, u16 input, u16 *cursorPosDest_p, u16 *itemsAboveDest_p)
{
    if (template != NULL)
        list->template = *template;
    list->cursorPos = cursorPos;
    list->itemsAbove = itemsAbove;
    list->unk_30 = 0;
    list->unk_31 = 0;

    if (input == REG_PAD_KEYINPUT_UP_MASK)
    {
        ListMenuChangeSelection(list, updateFlag, 1, FALSE);
    }
    else if (input == REG_PAD_KEYINPUT_DOWN_MASK)
    {
        ListMenuChangeSelection(list, updateFlag, 1, TRUE);
    }
    if (cursorPosDest_p != NULL)
    {
        *cursorPosDest_p = list->cursorPos;
    }
    if (itemsAboveDest_p != NULL)
    {
        *itemsAboveDest_p = list->itemsAbove;
    }
    return -1;
}

s32 FUN_020013C8(struct ListMenu * list, const struct ListMenuTemplate * template, u16 cursorPos, u16 itemsAbove, u16 input, u16 *cursorPosDest_p, u16 *itemsAboveDest_p)
{
    return FUN_02001354(list, template, cursorPos, itemsAbove, FALSE, input, cursorPosDest_p, itemsAboveDest_p);
}

void FUN_020013E8(struct ListMenu * list, u8 cursorPal, u8 fillValue, u8 cursorShadowPal)
{
    list->cursorPal = cursorPal;
    list->fillValue = fillValue;
    list->cursorShadowPal = cursorShadowPal;
    list->enabled = TRUE;
}

void FUN_0200143C(struct ListMenu * list, u16 * index_p)
{
    *index_p = list->cursorPos + list->itemsAbove;
}

void FUN_02001448(struct ListMenu * list, u16 * cursorPos_p, u16 * itemsAbove_p)
{
    if (cursorPos_p != NULL)
        *cursorPos_p = list->cursorPos;
    if (itemsAbove_p != NULL)
        *itemsAbove_p = list->itemsAbove;
}

u8 FUN_0200145C(struct ListMenu * list)
{
    return list->unk_33;
}

s32 FUN_02001464(struct ListMenu * list, s32 index)
{
    return list->template.items[index].index;
}
