//============================================================================================
/**
 * @file	pokeicon.c
 * @brief	�|�P�����A�C�R���֘A����
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
//	�萔��`
//============================================================================================
#define	POKEICON_PAL_TAMAGO			( 1 )	// �^�}�S�̃p���b�g�ԍ�
#define	POKEICON_PAL_TAMAGO_MNF		( 2 )	// �}�i�t�B�̃^�}�S�̃p���b�g�ԍ�


//============================================================================================
//	�O���[�o���ϐ�
//============================================================================================
#include "pokeicon.dat"


//--------------------------------------------------------------------------------------------
/**
 * �L�����̃A�[�J�C�u�C���f�b�N�X�擾 ( POKEMON_PASO_PARAM �� )
 *
 * @param	ppp			POKEMON_PASO_PARAM
 *
 * @return	�A�[�J�C�u�C���f�b�N�X
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
 * �L�����̃A�[�J�C�u�C���f�b�N�X�擾 ( POKEMON_PARAM �� )
 *
 * @param	pp			POKEMON_PARAM
 *
 * @return	�A�[�J�C�u�C���f�b�N�X
 *
 */
//--------------------------------------------------------------------------------------------
u32 PokeIconCgxArcIndexGetByPP( POKEMON_PARAM * pp )
{
	return PokeIconCgxArcIndexGet( (const POKEMON_PASO_PARAM *)PPPPointerGet( pp ) );
}

//--------------------------------------------------------------------------------------------
/**
 * �L�����̃A�[�J�C�u�C���f�b�N�X�擾
 *
 * @param	mons		�|�P�����ԍ�
 * @param	egg			�^�}�S�t���O
 * @param	pat			�g���p�^�[��
 *
 * @return	�A�[�J�C�u�C���f�b�N�X
 *
 *	pat�̓f�I�L�V�X��A���m�[���Ɏg�p
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
 * �L�����̊g���p�^�[���i���o�[���擾
 *
 * @param   ppp		
 *
 * @retval  u16		�i���p�^�[���i���o�[
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
 * �p���b�g�ԍ��擾
 *
 * @param	mons		�|�P�����ԍ�
 * @param	form		�t�H�����ԍ�
 * @param	egg			�^�}�S�t���O
 *
 * @return	�p���b�g�ԍ�
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
 * �p���b�g�ԍ��擾�iPOKEMON_PASO_PARAM�Łj
 *
 * @param	ppp		POKEMON_PASO_PARAM
 *
 * @return	�p���b�g�ԍ�
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
 * �p���b�g�ԍ��擾�iPOKEMON_PARAM�Łj
 *
 * @param	pp		POKEMON_PARAM
 *
 * @return	�p���b�g�ԍ�
 */
//--------------------------------------------------------------------------------------------
const u8 PokeIconPalNumGetByPP( POKEMON_PARAM * pp )
{
	return PokeIconPalNumGetByPPP( (const POKEMON_PASO_PARAM *)PPPPointerGet( pp ) );
}

//--------------------------------------------------------------------------------------------
/**
 * �p���b�g�̃A�[�J�C�u�C���f�b�N�X�擾
 *
 * @param	none
 *
 * @return	�A�[�J�C�u�C���f�b�N�X
 */
//--------------------------------------------------------------------------------------------
u32 PokeIconPalArcIndexGet(void)
{
	return NARC_poke_icon_poke_icon_NCLR;
}

//--------------------------------------------------------------------------------------------
/**
 * �Z���̃A�[�J�C�u�C���f�b�N�X�擾
 *
 * @param	none
 *
 * @return	�A�[�J�C�u�C���f�b�N�X
 */
//--------------------------------------------------------------------------------------------
u32 PokeIconCellArcIndexGet(void)
{
	return NARC_poke_icon_poke_icon01_NCER;
}

//--------------------------------------------------------------------------------------------
/**
 * �Z���̃A�[�J�C�u�C���f�b�N�X�擾�i�A�j������j
 *
 * @param	none
 *
 * @return	�A�[�J�C�u�C���f�b�N�X
 */
//--------------------------------------------------------------------------------------------
u32 PokeIconAnmCellArcIndexGet(void)
{
	return NARC_poke_icon_poke_icon_anm_NCER;
}

//--------------------------------------------------------------------------------------------
/**
 * �Z���̃A�[�J�C�u�C���f�b�N�X�擾�i64k,�A�j������j
 *
 * @param	none
 *
 * @return	�A�[�J�C�u�C���f�b�N�X
 */
//--------------------------------------------------------------------------------------------
u32 PokeIcon64kCellArcIndexGet(void)
{
	return NARC_poke_icon_poke_icon_64k_NCER;
}

//--------------------------------------------------------------------------------------------
/**
 * �Z���A�j���̃A�[�J�C�u�C���f�b�N�X�擾
 *
 * @param	none
 *
 * @return	�A�[�J�C�u�C���f�b�N�X
 */
//--------------------------------------------------------------------------------------------
u32 PokeIconCellAnmArcIndexGet(void)
{
	return NARC_poke_icon_poke_icon01_NANR;
}

//--------------------------------------------------------------------------------------------
/**
 * �Z���A�j���̃A�[�J�C�u�C���f�b�N�X�擾�i�A�j������j
 *
 * @param	none
 *
 * @return	�A�[�J�C�u�C���f�b�N�X
 */
//--------------------------------------------------------------------------------------------
u32 PokeIconAnmCellAnmArcIndexGet(void)
{
	return NARC_poke_icon_poke_icon_anm_NANR;
}

//--------------------------------------------------------------------------------------------
/**
 * �Z���A�j���̃A�[�J�C�u�C���f�b�N�X�擾�i64k,�A�j������j
 *
 * @param	none
 *
 * @return	�A�[�J�C�u�C���f�b�N�X
 */
//--------------------------------------------------------------------------------------------
u32 PokeIcon64kCellAnmArcIndexGet(void)
{
	return NARC_poke_icon_poke_icon_64k_NANR;
}
