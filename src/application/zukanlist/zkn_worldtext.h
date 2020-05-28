/* 外国語データ */
#ifndef __ZKN_WORLD_TEXT_H__
#define __ZKN_WORLD_TEXT_H__

#undef GLOBAL
#ifdef	__ZKN_WORLD_TEXT_H_GLOBAL
#define	GLOBAL	/* */
#else
#define	GLOBAL	extern
#endif
#define ZKN_WORLD_TEXT_POKE_NUM (14) // 言語のあるポケモンの数

GLOBAL const u16 TEXTVER_PokeNum[ZKN_WORLD_TEXT_POKE_NUM];
#undef	GLOBAL
#endif
