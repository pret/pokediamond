//============================================================================================
/**
 * @file	waza_oshie.c
 * @brief	技教え/思い出し処理
 * @author	Hiroyuki Nakamura
 * @date	06.05.09
 */
//============================================================================================
#include "common.h"
#include "system/procsys.h"
#include "savedata/mystatus.h"
#include "savedata/config.h"
#include "poketool/poke_tool.h"

#define WAZA_OSHIE_H_GLOBAL
#include "application/waza_oshie.h"


#define LV_WAZA_OBOE_MAX	( LEVELUPWAZA_OBOE_MAX/2 )	// レベルアップで覚える技数 + 終端コード
#define LV_WAZA_OBOE_END	( LEVELUPWAZA_OBOE_END )	// 終端コード
#define LV_WAZA_LV_MASK		( LEVELUPWAZA_LEVEL_MASK )	// 覚えるレベル部分
#define LV_WAZA_WAZA_MASK   ( LEVELUPWAZA_WAZA_MASK )	// 覚える技部分
#define LV_WAZA_LV_SHIFT	( LEVELUPWAZA_LEVEL_SHIFT )	// レベル取得シフト


//--------------------------------------------------------------------------------------------
/**
 * 技教えデータ領域取得
 *
 * @param	heap	ヒープID
 *
 * @return	技教えデータ領域
 */
//--------------------------------------------------------------------------------------------
WAZAOSHIE_DATA * WazaOshie_DataAlloc( u32 heap )
{
	WAZAOSHIE_DATA * dat = sys_AllocMemory( heap, sizeof(WAZAOSHIE_DATA) );
	memset( dat, 0, sizeof(WAZAOSHIE_DATA) );
	return dat;
}

//--------------------------------------------------------------------------------------------
/**
 * 技教えデータ領域解放
 *
 * @param	heap	ヒープID
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void WazaOshie_DataFree( WAZAOSHIE_DATA * dat )
{
	sys_FreeMemoryEz( dat );
}

//--------------------------------------------------------------------------------------------
/**
 * 思い出し可能な技を取得
 *
 * @param	pp		ポケモンデータ
 * @param	heap	ヒープID
 *
 * @return	取得した技データ
 *
 *	解放は各自で
 */
//--------------------------------------------------------------------------------------------
u16 * RemaindWazaGet( POKEMON_PARAM * pp, u32 heap )
{
	u16 * get;
	u16 * ret;
	u16	waza[4];
	u16	mons;
	u8	lv;
	u8	form;
	u8	h, i, j;

	mons = (u16)PokeParaGet( pp, ID_PARA_monsno, NULL );
	form = (u8)PokeParaGet( pp, ID_PARA_form_no, NULL );
	lv   = (u8)PokeParaGet( pp, ID_PARA_level, NULL );
	for( i=0; i<4; i++ ){
		waza[i] = (u16)PokeParaGet( pp, ID_PARA_waza1+i, NULL );
	}

	get = sys_AllocMemory( heap, LV_WAZA_OBOE_MAX * 2 );
	ret = sys_AllocMemory( heap, LV_WAZA_OBOE_MAX * 2 );

//	PokeWazaOboeDataGet( mons, get );
	PokeFormNoWazaOboeDataGet( mons, form, get );

	j = 0;
	for( i=0; i<LV_WAZA_OBOE_MAX; i++ ){
		// 終端コードチェック
		if( get[i] == LV_WAZA_OBOE_END ){
			ret[j] = WAZAOSHIE_TBL_MAX;
			break;
		// 現在のレベルで覚えられる技か
		}else if( ((get[i]&LV_WAZA_LV_MASK)>>LV_WAZA_LV_SHIFT) > lv ){
//			ret[j] = WAZAOSHIE_TBL_MAX;
//			break;
			continue;
		}else{
			get[i] &= LV_WAZA_WAZA_MASK;
			// すでに覚えているか
			for( h=0; h<4; h++ ){
				if( get[i] == waza[h] ){ break; }
			}
			if( h == 4 ){
				// テーブルに同じ技がないか
				for( h=0; h<j; h++ ){
					if( ret[h] == get[i] ){ break; }
				}
				if( h == j ){
					ret[j] = get[i];
					j++;
				}
			}
		}
	}

	sys_FreeMemoryEz( get );

	return ret;
}

//--------------------------------------------------------------------------------------------
/**
 * 教えられる/思い出せる技があるかチェック
 *
 * @param	tbl		技テーブル
 *
 * @retval	"TRUE = あり"
 * @retval	"FALSE = なし"
 */
//--------------------------------------------------------------------------------------------
BOOL WazaOshie_WazaTableChack( u16 * tbl )
{
	if( tbl[0] == WAZAOSHIE_TBL_MAX ){
		return FALSE;
	}
	return TRUE;
}
