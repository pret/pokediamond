
//============================================================================
/**
 *
 *@file		sub_011.s
 *@brief	�퓬�V�[�P���X
 *			�|�P�����ߊl�V�[�P���X
 *@author	HisashiSogabe
 *@data		2005.07.20
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_011:
	MESSAGE				ItemUseMsg,TAG_TRNAME_ITEM,SIDE_ATTACK,SIDE_WORK
	SERVER_WAIT
	POKEMON_GET_INIT	GET_NORMAL
	POKEMON_GET
SUB_011_END:
	SEQ_END
