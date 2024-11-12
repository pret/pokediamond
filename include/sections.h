#ifndef GUARD_SECTIONS_H
#define GUARD_SECTIONS_H

#pragma define_section ITCM ".itcm"               \
                            ".itcm.bss" abs32 RWX
#pragma define_section DTCM ".dtcm"               \
                            ".dtcm.bss" abs32 RWX
#pragma define_section VERSION ".version" abs32 RWX
#pragma define_section PARENT ".parent" abs32 RWX

#endif // GUARD_SECTIONS_H
