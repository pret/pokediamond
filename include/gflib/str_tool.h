#ifndef	__STR_TOOL_H__
#define	__STR_TOOL_H__

#include "gflib\msg_print.h"

#undef GLOBAL
#ifdef __STR_TOOL_H_GLOBAL__
#define GLOBAL /*	*/
#else
#define GLOBAL extern
#endif

#define RETURN_CODE (0x0d)

GLOBAL int StrLen(char *str);
GLOBAL char* StrTok(char *str, char *des, char token);
GLOBAL int StrTokNum(char *str,char token);
GLOBAL int AtoI(char *str);
GLOBAL int StrCopy(char *des, const char *src);
GLOBAL void SetResName(NNSG3dResName *outName,const char *inName);


extern BOOL IsJapaneseCode( STRCODE code );

#undef GLOBAL
#endif /*__STR_TOOL_H__*/
