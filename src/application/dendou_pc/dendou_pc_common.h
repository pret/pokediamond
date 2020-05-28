//============================================================================================
/**
 * @file	dendou_pc_common.h
 * @bfief	�a������p�\�R�����
 * @author	taya GAME FREAK inc.
 *
 * @date	2006.04.21
 */
//============================================================================================
#ifndef __DENDOU_PC_COMMON_H__
#define __DENDOU_PC_COMMON_H__

#include "system\gamedata.h"
#include "savedata\dendou_data.h"

#include "dendou_pc_sound.h"

//------------------------------------------------------
/**
 *	�`��R�}���h
 */
//------------------------------------------------------
enum {
	VCMD_INIT,				///< ��ʏ����\�z���t�F�[�h�C��
	VCMD_QUIT,				///< �t�F�[�h�A�E�g
	VCMD_CHANGE_POKE,		///< �I���|�P�����ύX
	VCMD_CHANGE_RECORD,		///< �\�����R�[�h�ύX
	VCMD_CHANGE_PARAMMODE,	///< �p�����[�^���[�h�ύX

	VCMD_MAX,
};

//------------------------------------------------------
/**
 *	�p�����[�^���[�h
 */
//------------------------------------------------------
typedef enum {
	PARAM_NORMAL,	///< �ʏ�\��
	PARAM_WAZA,		///< �킴���\��
}DendouPC_ParamMode;

//------------------------------------------------------
/**
 *	���C�����[�N�s���S�^
 */
//------------------------------------------------------
typedef  struct  _DENDOU_PC_WORK	DENDOU_PC_WORK;

//------------------------------------------------------
/**
 *	�`�惏�[�N�s���S�^
 */
//------------------------------------------------------
typedef  struct  _DENDOU_PC_VIEW	DENDOU_PC_VIEW;


//------------------------------------------------------
/**
 *	�`��p���
 */
//------------------------------------------------------
typedef struct {
	int			times;				///< ����ڂ̓a�����肩
	RTCDate		date;				///< �a��������t
	int			pokeCount;			///< �|�P�������̂��邩
	int			pokePos;			///< ���̖ڂ�I��ł��邩
	DendouPC_ParamMode	paramMode;	///< �p�����[�^���[�h
	DENDOU_POKEMON_DATA	pokemon[ TEMOTI_POKEMAX ];	///< �|�P�����f�[�^
}DENDOU_PC_VIEWPARAM;





//--------------------------------------------------------------
// �`�摤�֐��Q
//--------------------------------------------------------------
extern DENDOU_PC_VIEW* DendouPCView_CreateWork( DENDOU_PC_WORK* mainWork, const DENDOU_PC_VIEWPARAM* vpara );
extern void DendouPCView_DeleteWork( DENDOU_PC_VIEW* vwk );
extern BOOL DendouPCView_StartCommand( DENDOU_PC_VIEW* vwk, int command );
extern BOOL DendouPCView_WaitCommand( DENDOU_PC_VIEW* vwk );


#endif
