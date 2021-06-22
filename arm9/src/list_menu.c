#include "global.h"
#include "heap.h"
#include "main.h"
#include "list_menu.h"
#include "text.h"
#include "font.h"

void ListMenuPrintEntries(struct ListMenu * list, u16 startIndex, u16 yOffset, u16 count);
void ListMenuDrawCursor(struct ListMenu * list);
BOOL ListMenuChangeSelection(struct ListMenu * list, u8 updateCursorAndCallCallback, u8 count, u8 movingDown);
void ListMenuCallSelectionChangedCallback(struct ListMenu * list, u8 onInit);

static inline u32 MakeFontColor(u32 fgPal, u32 shdwPal, u32 bgPal)
{
    return (u32)(
        ((u32)(fgPal << 24) >> 8)
        | ((u32)(shdwPal << 24) >> 16)
        | ((u32)(bgPal << 24) >> 24)
    );
}

THUMB_FUNC struct ListMenu * ListMenuInit(const struct ListMenuTemplate * template, u16 cursorPos, u16 itemsAbove, u32 heap_id)
{
    struct ListMenu * list = AllocFromHeap(heap_id, sizeof(struct ListMenu));
    list->template = *template;
    list->cursor = ListMenuCursorNew(heap_id);
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
    list->overrideEnabled = FALSE;
    if (list->template.totalItems < list->template.maxShowed)
        list->template.maxShowed = list->template.totalItems;
    ListMenuCursorSetColor(
        list->cursor,
//        MakeFontColor(list->template.cursorPal, list->template.cursorShadowPal, list->fillValue)
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
        return list->template.items[list->cursorPos + list->itemsAbove].value;
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
            leftButton = (u16)(gMain.newAndRepeatedKeys & REG_PAD_KEYINPUT_LEFT_MASK);
            rightButton = (u16)(gMain.newAndRepeatedKeys & REG_PAD_KEYINPUT_RIGHT_MASK);
            break;
        case LIST_MULTIPLE_SCROLL_L_R:
            leftButton = (u16)(gMain.newAndRepeatedKeys & REG_PAD_KEYINPUT_L_MASK);
            rightButton = (u16)(gMain.newAndRepeatedKeys & REG_PAD_KEYINPUT_R_MASK);
            break;
        }
        if (leftButton)
        {
            if (!ListMenuChangeSelection(list, TRUE, (u8)list->template.maxShowed, FALSE))
                list->unk_33 = 3;
            return LIST_NOTHING_CHOSEN;
        }
        else if (rightButton)
        {
            if (!ListMenuChangeSelection(list, TRUE, (u8)list->template.maxShowed, TRUE))
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
    FreeToHeapExplicit(list->heap_id, list);
}

THUMB_FUNC void RedrawListMenu(struct ListMenu * list)
{
    FillWindowPixelBuffer(list->template.window, list->template.fillValue);
    ListMenuPrintEntries(list, list->cursorPos, 0, list->template.maxShowed);
    ListMenuDrawCursor(list);
    CopyWindowToVram(list->template.window);
}

THUMB_FUNC s32 ListMenuTestInputInternal(struct ListMenu * list, const struct ListMenuTemplate * template, u16 cursorPos, u16 itemsAbove, u16 updateFlag, u16 input, u16 *newCursorPos, u16 *newItemsAbove)
{
    if (template != NULL)
        list->template = *template;
    list->cursorPos = cursorPos;
    list->itemsAbove = itemsAbove;
    list->unk_30 = 0;
    list->unk_31 = 0;

    if (input == REG_PAD_KEYINPUT_UP_MASK)
    {
        ListMenuChangeSelection(list, (u8)updateFlag, 1, FALSE);
    }
    else if (input == REG_PAD_KEYINPUT_DOWN_MASK)
    {
        ListMenuChangeSelection(list, (u8)updateFlag, 1, TRUE);
    }
    if (newCursorPos != NULL)
    {
        *newCursorPos = list->cursorPos;
    }
    if (newItemsAbove != NULL)
    {
        *newItemsAbove = list->itemsAbove;
    }
    return -1;
}

THUMB_FUNC s32 ListMenuTestInput(struct ListMenu * list, const struct ListMenuTemplate * template, u16 cursorPos, u16 itemsAbove, u16 input, u16 *newCursorPos, u16 *newItemsAbove)
{
    return ListMenuTestInputInternal(list, template, cursorPos, itemsAbove, FALSE, input, newCursorPos, newItemsAbove);
}

THUMB_FUNC void ListMenuOverrideSetColors(struct ListMenu * list, u8 cursorPal, u8 fillValue, u8 cursorShadowPal)
{
    list->cursorPal = cursorPal;
    list->fillValue = fillValue;
    list->cursorShadowPal = cursorShadowPal;
    list->overrideEnabled = TRUE;
}

THUMB_FUNC void ListMenuGetCurrentItemArrayId(struct ListMenu * list, u16 * index_p)
{
    *index_p = (u16)(list->cursorPos + list->itemsAbove);
}

THUMB_FUNC void ListMenuGetScrollAndRow(struct ListMenu * list, u16 * cursorPos_p, u16 * itemsAbove_p)
{
    if (cursorPos_p != NULL)
        *cursorPos_p = list->cursorPos;
    if (itemsAbove_p != NULL)
        *itemsAbove_p = list->itemsAbove;
}

THUMB_FUNC u8 ListMenuGetUnk33(struct ListMenu * list)
{
    return list->unk_33;
}

THUMB_FUNC s32 ListMenuGetValueByArrayId(struct ListMenu * list, s32 index)
{
    return list->template.items[index].value;
}

THUMB_FUNC s32 ListMenuGetTemplateField(struct ListMenu * list, u32 attr)
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
        return GetFontAttribute((u8)list->template.fontId, 1) + list->template.itemVerticalPadding;
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
        return (s32)list->template.cursorKind;
    case 18:
        return (s32)list->template.window;
    case 19:
        return (s32)list->template.unk_1C;
    }

    return -1;
}

THUMB_FUNC void ListMenuSetTemplateField(struct ListMenu * list, u32 attr, s32 value)
{
    switch (attr)
    {
    case 0:
        list->template.moveCursorFunc = (LM_MoveCursorFunc_t)value;
        break;
    case 1:
        list->template.itemPrintFunc = (LM_ItemPrintFunc_t)value;
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
        list->template.cursorKind = (u8)value;
        break;
    case 18:
        list->template.window = (struct Window *)value;
        break;
    case 19:
        list->template.unk_1C = (u32)value;
        break;
    }
}

THUMB_FUNC void ListMenuGetItemStr(struct ListMenu * list, struct ListMenuItem * items)
{
    list->template.items = items;
}

THUMB_FUNC void ListMenuPrint(struct ListMenu * list, struct String * str, u8 x, u8 y)
{
    if (str != NULL)
    {
        if (list->overrideEnabled)
        {
            AddTextPrinterParameterized3(list->template.window, list->fontId, str, x, y, 0xFF, MakeFontColor(list->cursorPal, list->cursorShadowPal, list->fillValue), list->lettersSpacing, 0, NULL);
        }
        else
        {
            AddTextPrinterParameterized3(list->template.window, list->template.fontId, str, x, y, 0xFF, MakeFontColor(list->template.cursorPal, list->template.cursorShadowPal, list->template.fillValue), list->template.lettersSpacing, 0, NULL);
        }
    }
}

THUMB_FUNC void ListMenuPrintEntries(struct ListMenu * list, u16 startIndex, u16 yOffset, u16 count)
{
    s32 i;
    u8 x, y;
    u8 yMultiplier = (u8)(GetFontAttribute((u8)list->template.fontId, 1) + list->template.itemVerticalPadding);

    for (i = 0; i < count; i++)
    {
        if (list->template.items[startIndex].value != LIST_HEADER)
            x = list->template.item_X;
        else
            x = list->template.header_X;
        y = (u8)((yOffset + i) * yMultiplier + list->template.upText_Y);
        if (list->template.itemPrintFunc != NULL)
            list->template.itemPrintFunc(list, list->template.items[startIndex].value, y);
        ListMenuPrint(list, list->template.items[startIndex].text, x, y);
        startIndex++;
    }
}

THUMB_FUNC void ListMenuDrawCursor(struct ListMenu * list)
{
    u8 yMultiplier = (u8)(GetFontAttribute((u8)list->template.fontId, 1) + list->template.itemVerticalPadding);
    u8 x = list->template.cursor_X;
    u8 y = (u8)(list->itemsAbove * yMultiplier + list->template.upText_Y);
    switch (list->template.cursorKind)
    {
    case 0:
        ListMenuUpdateCursorObj(list->cursor, list->template.window, x, y);
        break;
    case 1:
    case 2: // leftover
    case 3: // leftover
        break;
    }
}

THUMB_FUNC void ListMenuErasePrintedCursor(struct ListMenu * list, u16 itemsAbove)
{
    switch (list->template.cursorKind)
    {
    case 0:
        u8 yMultiplier = (u8)(GetFontAttribute(list->template.fontId, 1) + list->template.itemVerticalPadding);
        u8 width  = 8;
        u8 height = 16;
        FillWindowPixelRect(list->template.window,
                            list->template.fillValue,
                            list->template.cursor_X,
                            (u16)(itemsAbove * yMultiplier + list->template.upText_Y),
                            width,
                            height);
        break;
    case 1:
    case 2: // leftover
    case 3: // leftover
        break;
    }
}

THUMB_FUNC u8 ListMenuUpdateSelectedRowIndexAndScrollOffset(struct ListMenu *list, u8 movingDown)
{
    u32 cursorPos;
    u16 itemsAbove;
    u16 newRow;

    itemsAbove = list->itemsAbove;
    cursorPos = list->cursorPos;

    if (!movingDown)
    {
        if (list->template.maxShowed == 1)
            newRow = 0;
        else
            newRow = (u16)(list->template.maxShowed - ((list->template.maxShowed / 2) + (list->template.maxShowed % 2)) - 1);

        if (cursorPos == 0)
        {
            while (itemsAbove != 0)
            {
                itemsAbove--;
                if (list->template.items[cursorPos + itemsAbove].value != LIST_HEADER)
                {
                    list->itemsAbove = itemsAbove;
                    return 1;
                }
            }
            return 0;
        }
        else
        {
            while (itemsAbove > newRow)
            {
                itemsAbove--;
                if (list->template.items[cursorPos + itemsAbove].value != LIST_HEADER)
                {
                    list->itemsAbove = itemsAbove;
                    return 1;
                }
            }
            list->itemsAbove = newRow;
            list->cursorPos = (u16)(cursorPos - 1);
        }
    }
    else
    {
        if (list->template.maxShowed == 1)
            newRow = 0;
        else
            newRow = (u16)((list->template.maxShowed / 2) + (list->template.maxShowed % 2));

        if (cursorPos == list->template.totalItems - list->template.maxShowed)
        {
            while (itemsAbove < list->template.maxShowed - 1)
            {
                itemsAbove++;
                if (list->template.items[cursorPos + itemsAbove].value != LIST_HEADER)
                {
                    list->itemsAbove = itemsAbove;
                    return 1;
                }
            }
            return 0;
        }
        else
        {
            while (itemsAbove < newRow)
            {
                itemsAbove++;
                if (list->template.items[cursorPos + itemsAbove].value != LIST_HEADER)
                {
                    list->itemsAbove = itemsAbove;
                    return 1;
                }
            }
            list->itemsAbove = newRow;
            list->cursorPos = (u16)(cursorPos + 1);
        }
    }
    return 2;
}

THUMB_FUNC void ListMenuScroll(struct ListMenu * list, u8 count, u8 movingDown)
{
    if (count >= list->template.maxShowed)
    {
        FillWindowPixelBuffer(list->template.window, list->template.fillValue);
        ListMenuPrintEntries(list, list->cursorPos, 0, list->template.maxShowed);
    }
    else
    {
        u8 yMultiplier = (u8)(GetFontAttribute((u8)list->template.fontId, 1) + list->template.itemVerticalPadding);

        if (!movingDown)
        {
            u16 y, width, height;

            ScrollWindow(list->template.window, 1, (u8)(count * yMultiplier), (u8)((list->template.fillValue << 4) | list->template.fillValue));
            ListMenuPrintEntries(list, list->cursorPos, 0, count);

            y = (u16)((list->template.maxShowed * yMultiplier) + list->template.upText_Y);
            width = GetWindowWidth(list->template.window);
            height = GetWindowHeight(list->template.window);
            FillWindowPixelRect(list->template.window,
                                list->template.fillValue,
                                0, y, (u16)(width * 8), (u16)(height * 8 - y));
        }
        else
        {
            u32 width;

            ScrollWindow(list->template.window, 0, (u8)(count * yMultiplier), (u8)((list->template.fillValue << 4) | list->template.fillValue));
            ListMenuPrintEntries(list, (u16)(list->cursorPos + (list->template.maxShowed - count)), (u16)(list->template.maxShowed - count), count);

            width = GetWindowWidth(list->template.window);
            FillWindowPixelRect(list->template.window,
                                list->template.fillValue,
                                0, 0, (u16)(width * 8), list->template.upText_Y);
        }
    }
}

THUMB_FUNC BOOL ListMenuChangeSelection(struct ListMenu * list, u8 updateCursorAndCallCallback, u8 count, u8 movingDown)
{
    u16 oldSelectedRow;
    u8 selectionChange, i, cursorCount;

    oldSelectedRow = list->itemsAbove;
    cursorCount = 0;
    selectionChange = 0;
    for (i = 0; i < count; i++)
    {
        do
        {
            u8 ret = ListMenuUpdateSelectedRowIndexAndScrollOffset(list, movingDown);

            selectionChange |= ret;
            if (ret != 2)
                break;
            cursorCount++;
        }
        while (list->template.items[list->cursorPos + list->itemsAbove].value == LIST_HEADER);
    }

    if (updateCursorAndCallCallback)
    {
        switch (selectionChange)
        {
        case 0:
        default:
            return TRUE;
        case 1:
            ListMenuErasePrintedCursor(list, oldSelectedRow);
            ListMenuDrawCursor(list);
            ListMenuCallSelectionChangedCallback(list, FALSE);
            CopyWindowToVram(list->template.window);
            break;
        case 2:
        case 3:
            ListMenuErasePrintedCursor(list, oldSelectedRow);
            ListMenuScroll(list, cursorCount, movingDown);
            ListMenuDrawCursor(list);
            ListMenuCallSelectionChangedCallback(list, FALSE);
            CopyWindowToVram(list->template.window);
            break;
        }
    }
    return FALSE;
}

THUMB_FUNC void ListMenuCallSelectionChangedCallback(struct ListMenu * list, u8 onInit)
{
    if (list->template.moveCursorFunc != NULL)
    {
        list->template.moveCursorFunc(list, list->template.items[list->cursorPos + list->itemsAbove].value, onInit);
    }
}

THUMB_FUNC void ListMenuCopyToVram(struct ListMenu * list)
{
    CopyWindowToVram(list->template.window);
}
