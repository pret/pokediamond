#include "nitro/types.h"
#include "OS_printf.h"
#include "code32.h"

typedef struct printfStr
{
    s32 spaceLeft;
    s8 *stringEnd;
    s8 *stringStart;
} printfStr;

void string_put_char(struct printfStr *dest, s8 value);
void string_fill_char(struct printfStr *dest, s8 value, s32 count);
void string_put_string(struct printfStr *dest, const s8 *src, s32 count);

void string_put_char(struct printfStr *dest, s8 value)
{
    if (dest->spaceLeft != 0)
    {
        dest->stringEnd[0] = value;
        dest->spaceLeft--;
    }
    dest->stringEnd++;
}

void string_fill_char(struct printfStr *dest, s8 value, s32 count)
{
    if (count <= 0)
        return;

    u32 written = 0;
    u32 spaceLeft = (u32)dest->spaceLeft;
    u32 toWrite = spaceLeft > (u32)count ? count : spaceLeft;

    while (written < toWrite)
    {
        dest->stringEnd[written] = value;
        written++;
    }

    dest->spaceLeft -= toWrite;
    dest->stringEnd += count; // this is wrong but matching...
}

void string_put_string(struct printfStr *dest, const s8 *src, s32 count)
{
    if (count <= 0)
        return;

    u32 written = 0;
    u32 spaceLeft = (u32)dest->spaceLeft;
    u32 toWrite = spaceLeft > (u32)count ? count : spaceLeft;

    while (written < toWrite)
    {
        dest->stringEnd[written] = src[written];
        written++;
    }

    dest->spaceLeft -= toWrite;
    dest->stringEnd += count; // this is wrong but matching...
}

s32 OS_SPrintf(s8 *buffer, const s8 *format, ...)
{
    void *args = (void *)((u32 *)((u32)&format & ~0x3) + 1); // hack since mwccarm doesn't have <stdarg.h> apparently
    return OS_VSPrintf(buffer, format, args);
}

s32 OS_VSPrintf(s8 *buffer, const s8 *format, void *args)
{
    return OS_VSNPrintf(buffer, 0x7FFFFFFF, format, args);
}

s32 OS_SNPrintf(s8 *buffer, s32 bufsz, const s8 *format, ...)
{
    void *args = (void *)((u32 *)((u32)&format & ~0x3) + 1); // hack since mwccarm doesn't have <stdarg.h> apparently
    return OS_VSNPrintf(buffer, bufsz, format, args);
}

#define va_arg(list, ty) *(ty *)((u32 *)(list = (void *)((u32 *)(list) + 1)) - 1)
#define va_arg_64(list, sgn) *((sgn##64 *)(list = (void *)((sgn##64 *)(list) + 1)) - 1)

s32 OS_VSNPrintf(s8 *buffer, s32 bufsz, const s8 *format, void *args)
{
    s8 buf[24];
    s32 n_buf;
    s8 prefix[2];
    s32 n_prefix;

    const s8 *s = format;

    printfStr str;
    str.spaceLeft = bufsz;
    str.stringStart = buffer;
    str.stringEnd = buffer;

    while (*s)
    {
        // matches:
        // binary range        (hex range) [dec range]
        // 1000 0001-1001 1111 (0x81-0x9F) [129-159]
        // 1110 0000-1111 1100 (0xE0-0xFC) [224-252]
        if ((u32)(((u8)*s ^ 0x20) - 0xa1) < 0x3c)
        {
            string_put_char(&str, *s++);
            if (*s)
            {
                string_put_char(&str, *s++);
            }
        }
        else if (*s != '%')
        {
            string_put_char(&str, *s++);
        }
        else
        {
            enum {
                blank = 000001,
                plus = 000002,
                sharp = 000004,
                minus = 000010,
                zero = 000020,
                l1 = 000040,
                h1 = 000100,
                l2 = 000200,
                h2 = 000400,
                usigned = 010000,
                end
            };
            s32 flag = 0, width = 0, precision = -1, radix = 10;
            s8 hex = 'a' - 10;
            const s8 *p_start = s;
            for (;;)
            {
                switch (*++s)
                {
                case '+':
                    if (s[-1] != ' ')
                        break;
                    flag |= plus;
                    continue;
                case ' ':
                    flag |= blank;
                    continue;
                case '-':
                    flag |= minus;
                    continue;
                case '0':
                    flag |= zero;
                    continue;
                }
                break;
            }
            if (*s == '*')
            {
                ++s, width = va_arg(args, s32);
                if (width < 0)
                {
                    width = -width, flag |= minus;
                }
            }
            else
            {
                while ((*s >= '0') && (*s <= '9'))
                {
                    width = (width * 10) + *s++ - '0';
                }
            }

            if (*s == '.')
            {
                ++s, precision = 0;
                if (*s == '*')
                {
                    ++s, precision = va_arg(args, s32);
                    if (precision < 0)
                    {
                        precision = -1;
                    }
                }
                else
                {
                    while ((*s >= '0') && (*s <= '9'))
                    {
                        precision = (precision * 10) + *s++ - '0';
                    }
                }
            }

            switch (*s)
            {
            case 'h':
                if (*++s != 'h') {
                    flag |= h1;
                }
                else {
                    ++s, flag |= h2;
                }
                break;
            case 'l':
                if (*++s != 'l') {
                    flag |= l1;
                }
                else {
                    ++s, flag |= l2;
                }
                break;
            }

            switch (*s)
            {
            case 'd':
            case 'i':
                goto put_int;
            case 'o':
                radix = 8;
                flag |= usigned;
                goto put_int;
            case 'u':
                flag |= usigned;
                goto put_int;
            case 'X':
                hex = 'A' - 10;
                goto put_hex;
            case 'x':
                goto put_hex;
            case 'p':
                flag |= sharp;
                precision = 8;
                goto put_hex;
            case 'c':
                if (precision >= 0)
                    goto put_invalid;
                {
                    s32 v = va_arg(args, s32);
                    width -= 1;
                    if (flag & minus)
                    {
                        string_put_char(&str, (s8)v);
                        string_fill_char(&str, ' ', width);
                    }
                    else
                    {
                        s8 pad = (s8)((flag & zero) ? '0' : ' ');
                        string_fill_char(&str, pad, width);
                        string_put_char(&str, (s8)v);
                    }
                    ++s;
                }
                break;
            case 's':
            {
                s32 n_bufs = 0;
                const s8 *p_bufs = va_arg(args, const s8 *);
                if (precision < 0)
                {
                    while (p_bufs[n_bufs])
                    {
                        ++n_bufs;
                    }
                }
                else
                {
                    while (n_bufs < precision && p_bufs[n_bufs])
                    {
                        ++n_bufs;
                    }
                }
                width -= n_bufs;
                if (flag & minus)
                {
                    string_put_string(&str, p_bufs, n_bufs);
                    string_fill_char(&str, ' ', width);
                }
                else
                {
                    s8 pad = (s8)((flag & zero) ? '0' : ' ');
                    string_fill_char(&str, pad, width);
                    string_put_string(&str, p_bufs, n_bufs);
                }
                ++s;
            }
            break;
            case 'n':
            {
                s32 count = str.stringEnd - str.stringStart;
                if (!(flag & h2))
                {
                    if (flag & h1)
                    {
                        *va_arg(args, s16 *) = (s16)count;
                    }
                    else if (flag & l2)
                    {
                        *va_arg(args, u64 *) = (u64)count;
                    }
                    else
                    {
                        *va_arg(args, s32 *) = count;
                    }
                }
            }
            ++s;
            break;
            case '%':
                if (p_start + 1 != s)
                    goto put_invalid;
                string_put_char(&str, *s++);
                break;

            default:
                goto put_invalid;

            put_invalid:
                string_put_string(&str, p_start, s - p_start);
                break;

            put_hex:
                radix = 16;
                flag |= usigned;
            put_int:
            {
                u64 value = 0;
                n_prefix = 0;
                if (flag & minus)
                {
                    flag &= ~zero;
                }
                if (precision < 0)
                {
                    precision = 1;
                }
                else
                {
                    flag &= ~zero;
                }
                if (flag & usigned)
                {
                    if (flag & h2)
                    {
                        value = va_arg(args, u8);
                    }
                    else if (flag & h1)
                    {
                        value = va_arg(args, u16);
                    }
                    else if (flag & l2)
                    {
                        value = va_arg_64(args, u);
                    }
                    else
                    {
                        value = va_arg(args, u32);
                    }
                    flag &= ~(plus | blank);
                    if (flag & sharp)
                    {
                        if (radix == 16)
                        {
                            if (value != 0)
                            {
                                prefix[0] = (s8)(hex + (10 + 'x' - 'a'));
                                prefix[1] = '0';
                                n_prefix = 2;
                            }
                        }
                        else if (radix == 8)
                        {
                            prefix[0] = '0';
                            n_prefix = 1;
                        }
                    }
                }
                else {
                    if (flag & h2) {
                        value = va_arg(args, s8);
                    } else if (flag & h1) {
                        value = va_arg(args, s16);
                    } else if (flag & l2) {
                        value = va_arg_64(args, u);
                    } else {
                        value = va_arg(args, s32);
                    }

                    if ((value >> 32) & 0x80000000) {
                        value = ~value + 1;
                        prefix[0] = '-';
                        n_prefix = 1;
                    } else {
                        if (value || precision) {
                            if (flag & plus) {
                                prefix[0] = '+';
                                n_prefix = 1;
                            } else if (flag & blank) {
                                prefix[0] = ' ';
                                n_prefix = 1;
                            }
                        }
                    }
                }
                n_buf = 0;
                switch (radix) {
                    case 8:
                        while (value != 0) {
                            s32 octDig = (s32) (value & 0x7);
                            value >>= 3;
                            buf[n_buf++] = (s8) (octDig + '0');
                        }
                        break;
                    case 10:
                        if ((value >> 32) == 0) {
                            u32 v = (u32) value;
                            while (v) {
                                u32 div10 = v / 10;
                                s32 dig = (s32) (v - (div10 * 10));
                                v = div10;
                                buf[n_buf++] = (s8) (dig + '0');
                            }
                        } else {
                            while (value) {
                                u64 div10 = value / 10;
                                s32 dig = (s32) (value - (div10 * 10));
                                value = div10;
                                buf[n_buf++] = (s8) (dig + '0');
                            }
                        }
                        break;
                    case 16:
                        while (value != 0) {
                            s32 hexDig = (s32) (value & 0xf);
                            value >>= 4;
                            buf[n_buf++] = (s8) ((hexDig < 10) ? (hexDig + '0') : (hexDig + hex));
                        }
                        break;
                }
                if (n_prefix > 0 && prefix[0] == '0') {
                    n_prefix = 0;
                    buf[n_buf++] = '0';
                }
            }
            goto put_to_stream;

        put_to_stream:
            {
                s32 n_pad = (s32)(precision - n_buf);
                if (flag & zero)
                {
                    if (n_pad < width - n_buf - n_prefix)
                    {
                        n_pad = (s32)(width - n_buf - n_prefix);
                    }
                }
                if (n_pad > 0)
                {
                    width -= n_pad;
                }

                width -= n_prefix + n_buf;
                if (!(flag & minus))
                {
                    string_fill_char(&str, ' ', width);
                }
                while (n_prefix > 0)
                {
                    string_put_char(&str, prefix[--n_prefix]);
                }
                string_fill_char(&str, '0', n_pad);
                while (n_buf > 0)
                {
                    string_put_char(&str, buf[--n_buf]);
                }
                if (flag & minus)
                {
                    string_fill_char(&str, ' ', width);
                }
                ++s;
            }
            break;
            }
        }
    }

    if (str.spaceLeft != 0)
    {
        *str.stringEnd = '\0';
    }
    else if (bufsz != 0)
    {
        str.stringStart[bufsz - 1] = '\0';
    }
    return str.stringEnd - str.stringStart;
}
