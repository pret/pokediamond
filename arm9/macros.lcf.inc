#define OVERLAY_TABLE(module, number) \
WRITEW number;                        \
WRITEW module##_START;                \
WRITEW module##_SIZE;                 \
WRITEW module##_BSSSIZE;              \
WRITEW module##_STATIC_INIT_START;    \
WRITEW module##_STATIC_INIT_END;      \
WRITEW number;                        \
WRITEW 0;

#define OVERLAY_FILE(number, offset, filename) \
.MODULE.##number : AT (offset) {               \
	. = ALIGN(512);                            \
	filename (.text)                           \
} > MODULE_##number
