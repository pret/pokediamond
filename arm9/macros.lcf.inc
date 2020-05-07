#define OVERLAY_TABLE(module, number)                   \
WRITEW number;                                          \
WRITEW SDK_OVERLAY_##module##_START;             \
WRITEW SDK_OVERLAY_##module##_SIZE;              \
WRITEW SDK_OVERLAY_##module##_BSSSIZE;           \
WRITEW SDK_OVERLAY_##module##_STATIC_INIT_START; \
WRITEW SDK_OVERLAY_##module##_STATIC_INIT_END;   \
WRITEW number;                                          \
WRITEW 0;
