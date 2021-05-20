#ifndef POKEDIAMOND_LIST_MENU_H
#define POKEDIAMOND_LIST_MENU_H

struct ListMenu;

// TODO: Move to its own header, and fill it out
struct Window
{
    u8 * unk_00;
    u8 unk_04;
};

// TODO: Document remaining fields.
// A lot of these are named based on similar fields in gen 3.
struct ListMenuTemplate
{
    u8 filler_00[12];
    /*0x0C*/ struct Window * window;
    /*0x10*/ u16 totalItems;
    /*0x12*/ u16 maxShowed;
    /*0x14*/ u8 header_X;
    /*0x15*/ u8 item_X;
    /*0x16*/ u8 cursor_X;
    /*0x17*/ u8 upText_Y:4;
             u8 cursorPal:4;
    /*0x18*/ u8 fillValue:4;
             u8 cursorShadowPal:4;
    /*0x1A*/ u16 lettersSpacing:3;
             u16 unk_1a_3:6;
             u16 fontId:6;
    /*0x1C*/ u8 filler_1C[4];
};

struct ListMenu
{
    /*0x00*/ struct ListMenuTemplate template;
    // ListMenuOverride from gen 3
    /*0x20*/ u8 cursorPal:4;
             u8 fillValue:4;
    /*0x21*/ u8 cursorShadowPal:4;
             u8 unk_21_4:4;
    /*0x22*/ u8 lettersSpacing:6;
    /*0x23*/ u8 unk_23;
    /*0x24*/ u8 fontId:7;
             u8 enabled:1;
    /*0x28*/ void * unk_28;
    /*0x2c*/ u16 cursorPos;
    /*0x2e*/ u16 itemsAbove;
    /*0x30*/ u8 unk_30;
    /*0x31*/ u8 unk_31;
    /*0x32*/ u8 taskId;
    /*0x33*/ u8 unk_33;
    /*0x34*/ u8 heap_id;
};

#endif // POKEDIAMOND_LIST_MENU_H
