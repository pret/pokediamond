#ifndef __P_ANM_SYS_H__
#define __P_ANM_SYS_H__

#include "common.h"
#include "system/softsprite.h"

#define POKE_ANIME_MAX	(50+84)		//アニメーション最大数

typedef struct POKE_ANIME_SYS_tag * POKE_ANM_SYS_PTR;

typedef struct P_ANM_SETTING_PARAM_tag
{
	u16		AnimeNo;		//アニメーション番号
	u16		Wait;			//アニメ開始ウェイト（フレーム数）
	u8		Reverse;		//反転フラグ（指定されたポケモンは　0：左右逆動作できない　1：左右逆動作できる)
}P_ANM_SETTING_PARAM;

extern void PokeAnm_CreateSettingParam(const int inMonsNo, P_ANM_SETTING_PARAM *outParam);

extern POKE_ANM_SYS_PTR PokeAnm_AllocMemory(const int inHeapID,
											const int inAllocNum,
											const u8 inReverse);

extern void PokeAnm_FreeMemory(POKE_ANM_SYS_PTR ptr);

extern u8 PokeAnm_GetBackAnmSlotNo( const u8 inChar );

extern void PokeAnm_SetPokeAnime(	POKE_ANM_SYS_PTR _ptr, SOFT_SPRITE *ss,
									const P_ANM_SETTING_PARAM *inParam, const u8 inEntryIndex);

extern BOOL PokeAnm_IsFinished(POKE_ANM_SYS_PTR ptr, const u8 inEntryIndex);

extern void PokeAnm_EndAnimeForce(POKE_ANM_SYS_PTR ptr, const u8 inEntryIndex);

#endif //__P_ANM_SYS_H__
