//============================================================================================
/**
 * @file	poketch_map.h
 * @bfief	�|�P�b�`�i�t�B�[���h�}�b�v�\���A�v�����ʃw�b�_�j
 * @author	taya GAME FREAK inc.
 */
//============================================================================================
#ifndef _POKETCH_MAP_H_
#define _POKETCH_MAP_H_

//------------------------------------------------------
/**
 *	�A�j���V�[�P���X
 */
//------------------------------------------------------
enum {
	POKETCH_MAPACT_ANMSEQ_PLAYERCURSOR,
	POKETCH_MAPACT_ANMSEQ_MARK1,
	POKETCH_MAPACT_ANMSEQ_MARK2,
	POKETCH_MAPACT_ANMSEQ_MARK3,
	POKETCH_MAPACT_ANMSEQ_MARK4,
	POKETCH_MAPACT_ANMSEQ_MARK5,
	POKETCH_MAPACT_ANMSEQ_MARK6,
	POKETCH_MAPACT_ANMSEQ_SEED,
	POKETCH_MAPACT_ANMSEQ_MARK1_EXPAND,
	POKETCH_MAPACT_ANMSEQ_MARK2_EXPAND,
	POKETCH_MAPACT_ANMSEQ_MARK3_EXPAND,
	POKETCH_MAPACT_ANMSEQ_MARK4_EXPAND,
	POKETCH_MAPACT_ANMSEQ_MARK5_EXPAND,
	POKETCH_MAPACT_ANMSEQ_MARK6_EXPAND,
	POKETCH_MAPACT_ANMSEQ_HIDEMAP1,
	POKETCH_MAPACT_ANMSEQ_HIDEMAP2,
	POKETCH_MAPACT_ANMSEQ_HIDEMAP3,
	POKETCH_MAPACT_ANMSEQ_HIDEMAP4,
	POKETCH_MAPACT_ANMSEQ_MOVEPOKE,
};


//------------------------------------------------------
/**
 *	�萔
 */
//------------------------------------------------------
enum {
	POKETCH_HIDEMAP_MAX = 4,	///< �B���}�b�v�G���A��
};



extern void PoketchMap_GridToDot( u32 glid_x, u32 glid_y, u32* dot_x, u32* dot_y );
extern void PoketchMap_GetHideMapPos( int hidemapID, u32* x, u32 *y );
extern BOOL PoketchMap_GetMovePokePos( int zone_id, u32* x, u32* y );

#endif
