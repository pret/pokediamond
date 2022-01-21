#ifndef NITRO_WM_WM_API_H_
#define NITRO_WM_WM_API_H_

static inline BOOL WM_IsBssidEqual(const u8 *mac0, const u8 *mac1) {
    return (*(mac0 + 0) == *(mac1 + 0)
         && *(mac0 + 1) == *(mac1 + 1)
         && *(mac0 + 2) == *(mac1 + 2)
         && *(mac0 + 3) == *(mac1 + 3)
         && *(mac0 + 4) == *(mac1 + 4)
         && *(mac0 + 5) == *(mac1 + 5)
    );
}

#endif //NITRO_WM_WM_API_H_
