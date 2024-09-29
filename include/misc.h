#ifndef GUARD_MISC_H
#define GUARD_MISC_H

// specify force-link.
void OSi_ReferSymbol(void *symbol);
#define SDK_REFER_SYMBOL(symbol) OSi_ReferSymbol((void *)(symbol))

// for embedding middleware version string in VERSION section.
#define SDK_MIDDLEWARE_STRING(vender, module)     "[SDK+" vender ":" module "]"
#define SDK_DEFINE_MIDDLEWARE(id, vender, module) static char id[] = SDK_MIDDLEWARE_STRING(vender, module)
#define SDK_USING_MIDDLEWARE(id)                  SDK_REFER_SYMBOL(id)

#endif // GUARD_MISC_H
