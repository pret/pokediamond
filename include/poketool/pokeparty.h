//============================================================================================
/**
 * @file	pokeparty.h
 * @brief	�|�P�����p�[�e�B����
 * @author	tamada	GAME FREAK Inc.
 * @date	2005.10.13
 *
 * �|�P�����p�[�e�B�[�Ƃ͎�����ΐ푊��̎莝���ȂǁA�����̃|�P�������ЂƂ����܂�Ƃ���
 * ���������ꍇ�Ɏg�p����B
 * �莝���Ƀ|�P��������������A���邢�͎莝������O������A�ʒu�����ւ�����Ȃǂ̑����
 * POKEPARTY��ΏۂƂ��čs���B
 */
//============================================================================================

#ifndef	__POKEPARTY_H__
#define	__POKEPARTY_H__

#include "system/savedata_def.h"	//SAVEDATA�Q�Ƃ̂���
#include "poketool/poke_tool.h"

//============================================================================================
//============================================================================================
//----------------------------------------------------------
/**
 * @param	�|�P�����p�[�e�B�^��`
 */
//----------------------------------------------------------
typedef struct _POKEPARTY POKEPARTY;

//============================================================================================
//============================================================================================
//----------------------------------------------------------
//	�Z�[�u�f�[�^�V�X�e�����ˑ�����֐�
//----------------------------------------------------------
extern int PokeParty_GetWorkSize(void);
extern POKEPARTY * PokeParty_AllocPartyWork(u32 heapID);
extern void PokeParty_InitWork(POKEPARTY * party);

//----------------------------------------------------------
//	POKEPARTY����̂��߂̊֐�
//----------------------------------------------------------
extern void PokeParty_Init(POKEPARTY * party, int max);
extern POKEMON_PARAM * PokeParty_GetMemberPointer(const POKEPARTY * party, int pos);
extern BOOL PokeParty_Add(POKEPARTY * party, POKEMON_PARAM * poke);
extern BOOL PokeParty_Delete(POKEPARTY * party, int pos);
BOOL PokeParty_ExchangePosition(POKEPARTY * party, int pos1, int pos2);
extern void PokeParty_Copy(const POKEPARTY * src, POKEPARTY * dst);
extern BOOL PokeParty_PokemonCheck(const POKEPARTY * ppt, int mons_no);
extern int PokeParty_GetPokeCount(const POKEPARTY* party);
extern void PokeParty_SetMemberData( POKEPARTY* party, int pos, POKEMON_PARAM* pp );

extern void Debug_PokeParty_MakeParty(POKEPARTY * party);
//----------------------------------------------------------
//	�Z�[�u�f�[�^�擾�̂��߂̊֐�
//----------------------------------------------------------
extern POKEPARTY * SaveData_GetTemotiPokemon(SAVEDATA * sv);

#ifdef CREATE_INDEX
extern void *Index_Get_PokeCount_Offset(POKEPARTY *pt);
#endif

#endif	/* __POKEPARTY_H__ */

