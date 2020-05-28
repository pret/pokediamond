/**
 *	@file	b_tower_wifi.h
 *	@brief	�o�g���^���[wifi/�ʐM�}���`�֘A�\�[�X
 *	@author	Miyuki Iwasawa
 *	@date	06.05.23
 */

#ifndef __H_B_TOWER_WIFI_H__
#define __H_B_TOWER_WIFI_H__

#undef GLOBAL
#ifdef __B_TOWER_WIFI_H_GLOBAL
#define GLOBAL	/***/
#else
#define GLOBAL	extern
#endif

/**
 *	@brief	�ʐM�p�ɃA�b�v�f�[�g����v���C���[�f�[�^���Z�[�u�f�[�^����쐬����
 *
 *	@param	mode	0:�V���O���p(�g���[�i�[���[�h�p)
 *					1:wifi�p(�^���[wifi�p)
 */
GLOBAL void BtlTowerData_MakeUpdatePlayerData(SAVEDATA* sv,BTWR_SCORE_POKE_DATA mode,DPW_BT_PLAYER* dat);

#endif	//__H_B_TOWER_WIFI_H__
