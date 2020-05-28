//============================================================================================
/**
 * @file	itemuse.h
 * @brief	�t�B�[���h�A�C�e���g�p����
 * @author	Hiroyuki Nakamura
 * @date	05.12.12
 */
//============================================================================================
#ifndef ITEMUSE_H
#define ITEMUSE_H
#undef GLOBAL
#ifdef ITEMUSE_H_GLOBAL
#define GLOBAL	/*	*/
#else
#define GLOBAL	extern
#endif



#include "../../src/field/player.h"


//============================================================================================
//	�萔��`
//============================================================================================
// �A�C�e���g�p���[�N
typedef struct {
	GMEVENT_CONTROL * event;	// �C�x���g
	u16	item;					// �A�C�e���ԍ�
	u8	use_poke;				// �g�p����|�P����
}ITEMUSE_WORK;

// �A�C�e���g�p�`�F�b�N���[�N
typedef struct {
	int	zone_id;	// �]�[��ID
	BOOL Companion;	//�@�A�������Ԃ��H
	int PlayerForm;	//�@���@�̌`��i���]�Ԃɏ���Ă��邩�Ƃ��j
	u16 FrontAttr;	//�@���@�O���A�g���r���[�g
	u16 NowAttr;	//�@���@���݃A�g���r���[�g
	u16 SeedInfo;	//�g�p�\�ȃA�C�e�����i���̂݊֘A�j
	PLAYER_STATE_PTR player;	//���@���Q�ƃ|�C���^
	FIELDSYS_WORK * fsys;
}ITEMCHECK_WORK;

typedef u32 (*ITEMCHECK_FUNC)(const ITEMCHECK_WORK*);	// �A�C�e���g�p�`�F�b�N�֐�

typedef void (*ITEMUSE_FUNC)(ITEMUSE_WORK*, const ITEMCHECK_WORK *);	// �A�C�e���g�p�֐�

// �A�C�e���g�p�֐��擾�p�����[�^
enum {
	ITEMUSE_PRM_USEFUNC = 0,	// �o�b�O����̎g�p�֐�
	ITEMUSE_PRM_CNVFUNC,		// �֗��{�^������̎g�p�֐�
	ITEMUSE_PRM_CHECKFUNC		// �`�F�b�N�֐�
};

// �A�C�e���g�p�`�F�b�N�̖߂�l
enum {
	ITEMCHECK_TRUE = 0,				// �g�p�\

	ITEMCHECK_ERR_CYCLE_OFF,		// ���]�Ԃ��~���Ȃ�
	ITEMCHECK_ERR_COMPANION,		// �g�p�s�E�A�����

	ITEMCHECK_FALSE = 0xffffffff	// �g�p�s�E���m�̌��t
};



//============================================================================================
//	�v���g�^�C�v�錾
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * �g�p�֐��擾
 *
 * @param	prm		�擾�p�����[�^
 * @param	id		�֐�ID
 *
 * @return	�g�p�֐�
 */
//--------------------------------------------------------------------------------------------
GLOBAL u32 ItemUse_FuncGet( u16 prm, u16 id );

//--------------------------------------------------------------------------------------------
/**
 * �g�p�`�F�b�N���[�N�쐬
 *
 * @param	fsys	�t�B�[���h���[�N
 * @param	id		�`�F�b�N���[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
GLOBAL void ItemUse_CheckWorkMake( FIELDSYS_WORK * fsys, ITEMCHECK_WORK * icwk );


GLOBAL BOOL ItemUse_KinomiTypeCheck( const ITEMCHECK_WORK * icwk );

GLOBAL BOOL FieldConvButtonEventInit( FIELDSYS_WORK * repw );


#undef GLOBAL
#endif	/* ITEMUSE_H */
