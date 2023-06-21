#ifndef POKEDIAMOND_UNK_02022450_H
#define POKEDIAMOND_UNK_02022450_H

struct CARD_Header {
    u8 title[12];
    u32 tid;
    u16 maker_code;
    u8 filler[44];
    u32 header_40;
    u32 header_44;
    u32 header_48;
    u32 header_4C;
};

void sub_02022450();
void Reset_To_File(const char* path);

#endif //POKEDIAMOND_UNK_02022450_H
