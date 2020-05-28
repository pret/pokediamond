//============================================================================================
/**
 * @file	poketch.h
 * @bfief	�|�P�b�`�@�O�����J�w�b�_
 * @author	taya GAME FREAK inc.
 */
//============================================================================================
#ifndef _POKETCH_H_
#define _POKETCH_H_

#include "gflib\bg_system.h"
#include "field\field_common.h"
#include "field\poketch_data.h"


//====================================================
// ���[�N�̌^�錾
//====================================================
typedef struct _POKETCH_WORK  POKETCH_WORK;

//====================================================
// �t�B�[���h���|�P�b�`�ւ̒ʒm����ID
//====================================================
typedef enum {
	POKETCH_SEND_SLEEP,
	POKETCH_SEND_MOVE_PLAYER,
	POKETCH_SEND_SODATEYA_UPDATE,
	POKETCH_SEND_POKELIST_UPDATE,
	POKETCH_SEND_SAVE,
	POKETCH_SEND_PEDOMATER,
}FIELD_POKETCH_SEND_ID;


//====================================================
// �I�[�o�[���CID�錾
//====================================================
FS_EXTERN_OVERLAY(ol_poketch);
FS_EXTERN_OVERLAY(ol_before_poketch);

//====================================================
// �A�v���i���o�[�Ƃ��Ė����Ȓl�i�؂�ւ����̎��Ȃǁj
//====================================================
enum {
	POKETCH_APP_NONE = -1,
};

//====================================================
// �֐��v���g�^�C�v
//====================================================
extern void PoketchInit(FIELDSYS_WORK* fsys, POKETCH_WORK **wk_adrs, SAVEDATA* savedata, GF_BGL_INI* bgl, NNSG2dOamManagerInstance* oamm);
extern void PoketchQuitReq(POKETCH_WORK *wk);
extern BOOL PoketchQuitWait( POKETCH_WORK *wk );
extern void Poketch_SendRequest( POKETCH_WORK* wk, FIELD_POKETCH_SEND_ID  id, u32 value );
extern BOOL Poketch_CheckTouch( POKETCH_WORK* wk );
extern int Poketch_GetRunningApplication( POKETCH_WORK* wk );

extern void PoketchBglIniSet( POKETCH_WORK * wk, GF_BGL_INI * ini );
extern GF_BGL_INI * PokethBglGet( POKETCH_WORK * wk );




//-------------------------------------------------------
// �|�P�b�`�擾�ȑO�̃R���g���[���֐�
//-------------------------------------------------------
extern void BeforePoketchInit( GF_BGL_INI* bgl );
extern void BeforePoketchQuitReq( GF_BGL_INI* bgl );
extern BOOL BeforePoketchQuitWait( GF_BGL_INI* bgl );

#endif
