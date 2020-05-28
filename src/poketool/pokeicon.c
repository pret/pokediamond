//============================================================================================
/**
 * @file	pokeicon.c
 * @brief	ポケモンアイコン関連処理
 * @author	Hiroyuki Nakamura
 * @date	05.09.16
 */
//============================================================================================
#include "common.h"
#include "system/arc_tool.h"

#define POKEICON_H_GLOBAL
#include "poketool/pokeicon.h"
#include "poketool/monsno.h"
#include "icongra/poke_icon.naix"


//============================================================================================
//	定数定義
//============================================================================================
#define	POKEICON_PAL_TAMAGO			( 1 )	// タマゴのパレット番号
#define	POKEICON_PAL_TAMAGO_MNF		( 2 )	// マナフィのタマゴのパレット番号


//============================================================================================
//	グローバル変数
//============================================================================================
#include "pokeicon.dat"


//--------------------------------------------------------------------------------------------
/**
 * キャラのアーカイブインデックス取得 ( POKEMON_PASO_PARAM 版 )
 *
 * @param	ppp			POKEMON_PASO_PARAM
 *
 * @return	アーカイブインデックス
 *
 */
//--------------------------------------------------------------------------------------------
u32 PokeIconCgxArcIndexGet( const POKEMON_PASO_PARAM* ppp )
{
	u32  monsno;
	u32  arcIndex;
	BOOL fastMode;
	u32  pat;
	u32  egg;

	fastMode = PokePasoParaFastModeOn((POKEMON_PASO_PARAM*)ppp);
	monsno = PokePasoParaGet( (POKEMON_PASO_PARAM*)ppp, ID_PARA_monsno, NULL );
	egg = PokePasoParaGet( (POKEMON_PASO_PARAM*)ppp, ID_PARA_tamago_flag, NULL );
	pat = PokeIconCgxPatternGet((POKEMON_PASO_PARAM*)ppp);

	arcIndex = PokeIconCgxArcIndexGetByMonsNumber( monsno, egg, pat );
	PokePasoParaFastModeOff((POKEMON_PASO_PARAM*)ppp, fastMode);
	return arcIndex;
}

//--------------------------------------------------------------------------------------------
/**
 * キャラのアーカイブインデックス取得 ( POKEMON_PARAM 版 )
 *
 * @param	pp			POKEMON_PARAM
 *
 * @return	アーカイブインデックス
 *
 */
//--------------------------------------------------------------------------------------------
u32 PokeIconCgxArcIndexGetByPP( POKEMON_PARAM * pp )
{
	return PokeIconCgxArcIndexGet( (const POKEMON_PASO_PARAM *)PPPPointerGet( pp ) );
}

//--------------------------------------------------------------------------------------------
/**
 * キャラのアーカイブインデックス取得
 *
 * @param	mons		ポケモン番号
 * @param	egg			タマゴフラグ
 * @param	pat			拡張パターン
 *
 * @return	アーカイブインデックス
 *
 *	patはデオキシスやアンノーンに使用
 */
//--------------------------------------------------------------------------------------------
u32 PokeIconCgxArcIndexGetByMonsNumber( u32 mons, u32 egg, u32 pat )
{
	if( egg == 1 ){
		if( mons == MONSNO_MANAFI ){
			return NARC_poke_icon_poke_icon_mnf_NCGR;
		}else{
			return NARC_poke_icon_poke_icon_tam_NCGR;
		}
	}

	if( pat != 0 ){
		if( mons == MONSNO_DEOKISISU ){
			return ( NARC_poke_icon_poke_icon_d01_NCGR + pat - 1 );
		}
		if( mons == MONSNO_ANNOON ){
			return ( NARC_poke_icon_poke_icon_u02_NCGR + pat - 1 );
		}
		if( mons == MONSNO_MINOMUTTI ){
			return ( NARC_poke_icon_poke_icon_455_01_NCGR + pat - 1 );
		}
		if( mons == MONSNO_MINOMESU ){
			return ( NARC_poke_icon_poke_icon_457_01_NCGR + pat - 1 );
		}
		if( mons == MONSNO_SIIUSI ){
			return ( NARC_poke_icon_poke_icon_458_01_NCGR + pat - 1 );
		}
		if( mons == MONSNO_SIIDORUGO ){
			return ( NARC_poke_icon_poke_icon_459_01_NCGR + pat - 1 );
		}
	}

	if( mons > MONSNO_END ){ mons = 0; }
//	if( mons > MONSNO_DEOKISISU ){ mons = 0; }

	return ( NARC_poke_icon_poke_icon_000_NCGR + mons );
}

//------------------------------------------------------------------
/**
 * キャラの拡張パターンナンバーを取得
 *
 * @param   ppp		
 *
 * @retval  u16		格調パターンナンバー
 */
//------------------------------------------------------------------
u16 PokeIconCgxPatternGet( const POKEMON_PASO_PARAM* ppp )
{
	u32 monsno;

	monsno = PokePasoParaGet( (POKEMON_PASO_PARAM*)ppp, ID_PARA_monsno_egg, NULL );

	switch( monsno ){
	case MONSNO_ANNOON:
		return PokePasoParaUnknownFormGet( (POKEMON_PASO_PARAM *)ppp );

	case MONSNO_DEOKISISU:
	case MONSNO_MINOMUTTI:
	case MONSNO_MINOMESU:
	case MONSNO_SIIUSI:
	case MONSNO_SIIDORUGO:
		return PokePasoParaGet( (POKEMON_PASO_PARAM*)ppp, ID_PARA_form_no, NULL );

	default:
		return 0;
	}
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * パレット番号取得
 *
 * @param	mons		ポケモン番号
 * @param	form		フォルム番号
 * @param	egg			タマゴフラグ
 *
 * @return	パレット番号
 */
//--------------------------------------------------------------------------------------------
const u8 PokeIconPalNumGet( u32 mons, u32 form, u32 egg )
{
	if( egg == 1 ){
		if( mons == MONSNO_MANAFI ){
			mons = POKEICON_TAMAGO_MNF;
		}else{
			mons = POKEICON_TAMAGO;
		}
	}else if( mons > MONSNO_END ){
		mons = 0;
	}else if( form != 0 ){
		if( mons == MONSNO_DEOKISISU ){
			mons = POKEICON_DEOKISISU + form - 1;
		}else if( mons == MONSNO_ANNOON ){
			mons = POKEICON_ANNOON + form - 1;
		}else if( mons == MONSNO_MINOMUTTI ){
			mons = POKEICON_MINOMUTTI + form - 1;
		}else if( mons == MONSNO_MINOMESU ){
			mons = POKEICON_MINOMESU + form - 1;
		}else if( mons == MONSNO_SIIUSI ){
			mons = POKEICON_SIIUSI + form - 1;
		}else if( mons == MONSNO_SIIDORUGO ){
			mons = POKEICON_SIIDORUGO + form - 1;
		}
	}
	return IconPalAtr[mons];
}

//--------------------------------------------------------------------------------------------
/**
 * パレット番号取得（POKEMON_PASO_PARAM版）
 *
 * @param	ppp		POKEMON_PASO_PARAM
 *
 * @return	パレット番号
 */
//--------------------------------------------------------------------------------------------
const u8 PokeIconPalNumGetByPPP( const POKEMON_PASO_PARAM * ppp )
{
	BOOL fast;
	u32  mons;
	u32  form;
	u32  egg;

	fast = PokePasoParaFastModeOn( (POKEMON_PASO_PARAM *)ppp );

	form = PokeIconCgxPatternGet( ppp );
	mons = PokePasoParaGet( (POKEMON_PASO_PARAM*)ppp, ID_PARA_monsno, NULL );
	egg  = PokePasoParaGet( (POKEMON_PASO_PARAM*)ppp, ID_PARA_tamago_flag, NULL );

	PokePasoParaFastModeOff( (POKEMON_PASO_PARAM *)ppp, fast );

	return PokeIconPalNumGet( mons, form, egg );
}

//--------------------------------------------------------------------------------------------
/**
 * パレット番号取得（POKEMON_PARAM版）
 *
 * @param	pp		POKEMON_PARAM
 *
 * @return	パレット番号
 */
//--------------------------------------------------------------------------------------------
const u8 PokeIconPalNumGetByPP( POKEMON_PARAM * pp )
{
	return PokeIconPalNumGetByPPP( (const POKEMON_PASO_PARAM *)PPPPointerGet( pp ) );
}

//--------------------------------------------------------------------------------------------
/**
 * パレットのアーカイブインデックス取得
 *
 * @param	none
 *
 * @return	アーカイブインデックス
 */
//--------------------------------------------------------------------------------------------
u32 PokeIconPalArcIndexGet(void)
{
	return NARC_poke_icon_poke_icon_NCLR;
}

//--------------------------------------------------------------------------------------------
/**
 * セルのアーカイブインデックス取得
 *
 * @param	none
 *
 * @return	アーカイブインデックス
 */
//--------------------------------------------------------------------------------------------
u32 PokeIconCellArcIndexGet(void)
{
	return NARC_poke_icon_poke_icon01_NCER;
}

//--------------------------------------------------------------------------------------------
/**
 * セルのアーカイブインデックス取得（アニメ入り）
 *
 * @param	none
 *
 * @return	アーカイブインデックス
 */
//--------------------------------------------------------------------------------------------
u32 PokeIconAnmCellArcIndexGet(void)
{
	return NARC_poke_icon_poke_icon_anm_NCER;
}

//--------------------------------------------------------------------------------------------
/**
 * セルのアーカイブインデックス取得（64k,アニメ入り）
 *
 * @param	none
 *
 * @return	アーカイブインデックス
 */
//--------------------------------------------------------------------------------------------
u32 PokeIcon64kCellArcIndexGet(void)
{
	return NARC_poke_icon_poke_icon_64k_NCER;
}

//--------------------------------------------------------------------------------------------
/**
 * セルアニメのアーカイブインデックス取得
 *
 * @param	none
 *
 * @return	アーカイブインデックス
 */
//--------------------------------------------------------------------------------------------
u32 PokeIconCellAnmArcIndexGet(void)
{
	return NARC_poke_icon_poke_icon01_NANR;
}

//--------------------------------------------------------------------------------------------
/**
 * セルアニメのアーカイブインデックス取得（アニメ入り）
 *
 * @param	none
 *
 * @return	アーカイブインデックス
 */
//--------------------------------------------------------------------------------------------
u32 PokeIconAnmCellAnmArcIndexGet(void)
{
	return NARC_poke_icon_poke_icon_anm_NANR;
}

//--------------------------------------------------------------------------------------------
/**
 * セルアニメのアーカイブインデックス取得（64k,アニメ入り）
 *
 * @param	none
 *
 * @return	アーカイブインデックス
 */
//--------------------------------------------------------------------------------------------
u32 PokeIcon64kCellAnmArcIndexGet(void)
{
	return NARC_poke_icon_poke_icon_64k_NANR;
}
