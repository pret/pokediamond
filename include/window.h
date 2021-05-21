#ifndef POKEDIAMOND_WINDOW_H
#define POKEDIAMOND_WINDOW_H

struct Window
{
    u8 * unk_00;
    u8 unk_04;
    u8 unk_05;
    u8 unk_06;
    u8 width;
    u8 height;
    u8 unk_9;
    u16 unk_A_0:15;
    u16 unk_A_15:1;
    void * unk_C;
};

extern void FillWindowPixelBuffer(struct Window *, u32);
extern void CopyWindowToVram(struct Window *);
extern void FillWindowPixelRect(struct Window *, u32 fillValue, u16 x, u16 y, u16 width, u16 height);
extern void ScrollWindow(struct Window *, u8, u8, u8);
extern u16 GetWindowWidth(struct Window *);
extern u16 GetWindowHeight(struct Window *);

#endif // POKEDIAMOND_WINDOW_H
