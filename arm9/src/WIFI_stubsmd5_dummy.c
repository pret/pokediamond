#include "global.h"
#include "WIFI_stubsmd5_dummy.h"

ARM_FUNC void MD5Final(u8 *digest, struct DGTHash1Context *context)
{
    DGT_Hash1GetDigest_R(digest, context);
}

ARM_FUNC void MD5Update(struct DGTHash1Context *context, u8 *input, u32 length)
{
    DGT_Hash1SetSource(context, input, length);
}

ARM_FUNC void MD5Init(struct DGTHash1Context *context)
{
    DGT_Hash1Reset(context);
}
