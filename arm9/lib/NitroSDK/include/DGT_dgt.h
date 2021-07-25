#ifndef NITRO_DGT_DGT_H_
#define NITRO_DGT_DGT_H_

#include "nitro/types.h"

void DGT_Hash2CalcHmac(void* digest, void* bin_ptr, u32 bin_len, void* key_ptr, u32 keylen);

#endif //NITRO_DGT_DGT_H_
