#ifndef POKEDIAMOND_ARM9_WIFI_STUBSMD5_DUMMY_H
#define POKEDIAMOND_ARM9_WIFI_STUBSMD5_DUMMY_H

#include "nitro/types.h"
#include "dgt.h"

void MD5Final(u8 *digest, struct DGTHash1Context *context);
void MD5Update(struct DGTHash1Context *context, u8 *input, u32 length);
void MD5Init(struct DGTHash1Context *context);

#endif //POKEDIAMOND_ARM9_WIFI_STUBSMD5_DUMMY_H
