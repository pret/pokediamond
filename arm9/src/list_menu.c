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
extern s32 FUN_02002E4C(u8 fontId, s32 attr);

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

s32 ListMenuGetTemplateField(struct ListMenu * list, u32 attr)
{
    switch (attr)
    {
    case 0:
        return (s32)list->template.moveCursorFunc;
    case 1:
        return (s32)list->template.itemPrintFunc;
    case 2:
        return (s32)list->template.totalItems;
    case 3:
        return (s32)list->template.maxShowed;
    case 4:
        break;
    case 5:
        return (s32)list->template.header_X;
    case 6:
        return (s32)list->template.item_X;
    case 7:
        return (s32)list->template.cursor_X;
    case 8:
        return (s32)list->template.upText_Y;
    case 9:
        return FUN_02002E4C(list->template.fontId, 1) + list->template.itemVerticalPadding;
    case 10:
        return (s32)list->template.cursorPal;
    case 11:
        return (s32)list->template.fillValue;
    case 12:
        return (s32)list->template.cursorShadowPal;
    case 13:
        return (s32)list->template.lettersSpacing;
    case 14:
        return (s32)list->template.itemVerticalPadding;
    case 15:
        return (s32)list->template.scrollMultiple;
    case 16:
        return (s32)list->template.fontId;
    case 17:
        return (s32)list->template.unk_1B_7;
    case 18:
        return (s32)list->template.window;
    case 19:
        return (s32)list->template.unk_1C;
    }

    return -1;
}

void ListMenuSetTemplateField(struct ListMenu * list, u32 attr, s32 value)
{
    switch (attr)
    {
    case 0:
        list->template.moveCursorFunc = (LM_MOVECURSORFUNC)value;
        break;
    case 1:
        list->template.itemPrintFunc = (LM_ITEMPRINTFUNC)value;
        break;
    case 2:
        list->template.totalItems = (u16)value;
        break;
    case 3:
        list->template.maxShowed = (u16)value;
        break;
    case 4:
        break;
    case 5:
        list->template.header_X = (u8)value;
        break;
    case 6:
        list->template.item_X = (u8)value;
        break;
    case 7:
        list->template.cursor_X = (u8)value;
        break;
    case 8:
        list->template.upText_Y = (u8)value;
        break;
    case 9:
        break;
    case 10:
        list->template.cursorPal = (u8)value;
        break;
    case 11:
        list->template.fillValue = (u8)value;
        break;
    case 12:
        list->template.cursorShadowPal = (u8)value;
        break;
    case 13:
        list->template.lettersSpacing = (u8)value;
        break;
    case 14:
        list->template.itemVerticalPadding = (u8)value;
        break;
    case 15:
        list->template.scrollMultiple = (u8)value;
        break;
    case 16:
        list->template.fontId = (u8)value;
        break;
    case 17:
        list->template.unk_1B_7 = (u8)value;
        break;
    case 18:
        list->template.window = (struct Window *)value;
        break;
    case 19:
        list->template.unk_1C = (u32)value;
        break;
    }
}
