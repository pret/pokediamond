//============================================================================================
/**
 * @brief	pokepark_data.h
 * @brief	�|�P�p�[�N�p�|�P��������
 * @date	2006.06.01
 * @author	tamada
 *
 * AGB��DS�Ɉړ�����|�P�����f�[�^���������߂̃w�b�_�ł��B
 */
//============================================================================================

#ifndef	__POKEPARK_DATA_H__
#define	__POKEPARK_DATA_H__

#include "savedata/savedata_def.h"

#include "poketool/poke_tool.h"
//============================================================================================
//============================================================================================
//---------------------------------------------------------------------------
/**
 * @brief	�|�P�p�[�N�f�[�^�̕s���S�^��`
 */
//---------------------------------------------------------------------------
typedef struct POKEPARK_DATA POKEPARK_DATA;

//---------------------------------------------------------------------------
/**
 * @brief	�|�P�p�[�N�f�[�^�̍ő�l�̒�`
 */
//---------------------------------------------------------------------------
#define	POKEPARK_MONS_MAX  (6)

//============================================================================================
//		�Z�[�u�V�X�e���֘A
//============================================================================================

extern POKEPARK_DATA * SaveData_GetPokeParkData(SAVEDATA * sv);
extern int POKEPARKDATA_GetWorkSize(void);
extern void POKEPARKDATA_Init(POKEPARK_DATA * ppark);
extern void POKEPARKDATA_PreInit(POKEPARK_DATA * ppark);

//============================================================================================
//		����֐�
//============================================================================================
extern void POKEPARKDATA_SetData(POKEPARK_DATA *ppark, POKEMON_PASO_PARAM *ppp, int index);
extern void POKEPARKDATA_SetMasterData(POKEPARK_DATA *ppark, u32 agb_id);
extern void POKEPARKDATA_CopyPokemonParam(const POKEPARK_DATA * ppark, int index, POKEMON_PARAM * pp);
extern int POKEPARKDATA_CountPokemon(const POKEPARK_DATA * ppark);;
extern int POKEPARKDATA_CheckHistoryID(const POKEPARK_DATA *ppark, u32 agb_id);
extern BOOL POKEPARKDATA_CheckMacAddress(const POKEPARK_DATA *ppark);
extern BOOL POKEPARKDATA_CheckRTCOffset(const POKEPARK_DATA *ppark);
extern BOOL POKEPARKDATA_isNewSave(const POKEPARK_DATA *ppark);
#ifdef	PM_DEBUG
extern void POKEPARKDATA_Debug_SetData(POKEPARK_DATA *ppark, int index,
		int mons_no, int level, int pow, u32 rnd, u32 id);
#endif

#endif	__POKEPARK_DATA_H__
