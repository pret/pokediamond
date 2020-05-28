/**
 * @file	field_anime.h
 * @brief	フィールド転送アニメ処理
 * @author	Akito Mori
 * @date	2005.04.
 *
 */



#include "field_anime_def.h"




extern FIELD_ANIME_PTR InitFieldAnime(void);
extern int  FieldAnimeSets(FIELD_ANIME_PTR faw, NNSG3dResTex *tex);
extern int  FieldAnimeSet(FIELD_ANIME_PTR faw, NNSG3dResTex *tex, const char *name, int AnimeNo);
extern void FieldAnimeMain(FIELD_ANIME_PTR faw);
extern void FieldAnimeRelease(FIELD_ANIME_PTR faw, int no );
extern void FieldAnimeAllRelease(FIELD_ANIME_PTR faw);
extern void ReleaseFieldAnime(FIELD_ANIME_PTR faw);
