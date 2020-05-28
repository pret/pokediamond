#ifndef _RES_TEX_H_
#define _RES_TEX_H_
#include <nitro.h>
#include <nnsys.h>

extern BOOL CmpPaletteName(const NNSG3dResName* inName,const char * inTargetName);
extern void ChangeTexPalette(const NNSG3dResTex* inResTex, const char * inStr, u16* inPalette);
extern u16* GetTexPalette(const NNSG3dResTex* inResTex, const char *inName, const int inHeapID);
extern u32 GetTexPaletteAdr(const NNSG3dResTex* inResTex, const char *inName, void *outAdr);
#endif //_RES_TEX_H_
