//============================================================================================
/**
 * @file	p_status.h
 * @brief	�|�P�����X�e�[�^�X���
 * @author	Hiroyuki Nakamura
 * @date	2005.10.26
 */
//============================================================================================
#ifndef P_STATUS_H
#define P_STATUS_H

#include "savedata/config.h"

#undef GLOBAL
#ifdef P_STATUS_H_GLOBAL
#define GLOBAL	/*	*/
#else
#define GLOBAL	extern
#endif


//============================================================================================
//	�萔��`
//============================================================================================
typedef struct {
	void * ppd;		// �|�P�����f�[�^
	CONFIG * cfg;	// �R���t�B�O�f�[�^

	const STRCODE * player_name;	// ���Ă���l�̖��O
	u32	player_id;					// ���Ă���l��ID
	u8	player_sex;					// ���Ă���l�̐���

	u8	ppt;		// �p�����[�^�^�C�v
	u8	mode;		// ���[�h
	u8	max;		// �ő吔
	u8	pos;		// ���Ԗڂ̃f�[�^��

	u8	page_flg;	// �y�[�W�t���O
	u8	ret_sel;	// �I�����ꂽ�Z�ʒu
	u8	ret_mode;
	u16	waza;

	u32	zukan_mode;	// �}�Ӄi���o�[�\�����[�h

	void * ribbon;	// �z�z���{���f�[�^

	void * poruto;	// �^����|���g�̃f�[�^ ( _PURUTO_DATA )

	PERAPVOICE * perap;	// �؃��b�v�̖����f�[�^

	BOOL	ev_contest;	// �R���e�X�g�֘AON/OFF

}PSTATUS_DATA;

// ���[�h
enum {
	PST_MODE_NORMAL = 0,	// �ʏ�
	PST_MODE_NO_WAZACHG,	// �Z����ւ��s��
	PST_MODE_WAZAADD,		// �Z�o��/�Z�Y��
	PST_MODE_PORUTO,		// �|���g�g�p
	PST_MODE_CONDITION,		// �R���f�B�V�����ύX�f��
};

// �p�����[�^�^�C�v
enum {
	PST_PP_TYPE_POKEPARAM = 0,		// POKEMON_PARAM
	PST_PP_TYPE_POKEPARTY,			// POKEPARTY
	PST_PP_TYPE_POKEPASO,			// POKEMON_PASO_PARAM
};

// �߂�
enum {
	PST_RET_DECIDE = 0,
	PST_RET_CANCEL,
};


// �y�[�WID
enum {
	PST_PAGE_INFO = 0,		// �u�|�P�������傤�ق��v
	PST_PAGE_MEMO,			// �u�g���[�i�[�����v
	PST_PAGE_PARAM,			// �u�|�P�����̂���傭�v
	PST_PAGE_B_SKILL,		// �u���������킴�v
	PST_PAGE_CONDITION,		// �u�R���f�B�V�����v
	PST_PAGE_C_SKILL,		// �u�R���e�X�g�킴�v
	PST_PAGE_RIBBON,		// �u���˂񃊃{���v
	PST_PAGE_RET,			// �u���ǂ�v
	PST_PAGE_MAX
};

enum {
	ST_ICON_POKERUS = 0,	// �|�P���X
	ST_ICON_MAHI,			// ���
	ST_ICON_KOORI,			// �X
	ST_ICON_NEMURI,			// ����
	ST_ICON_DOKU,			// ��
	ST_ICON_YAKEDO,			// �Ώ�
	ST_ICON_HINSI,			// �m��

	ST_ICON_NONE,			// ��Ԉُ�Ȃ�
};


//============================================================================================
//	�O���[�o���ϐ�
//============================================================================================
#ifndef P_STATUS_H_GLOBAL
GLOBAL const PROC_DATA PokeStatusProcData;	// �v���Z�X��`�f�[�^
#endif


//============================================================================================
//	�v���g�^�C�v�錾
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * �R���e�X�g�t���O���擾
 *
 * @param	sv		�Z�[�u�f�[�^
 *
 * @return	�R���e�X�g�t���O
 */
//--------------------------------------------------------------------------------------------
GLOBAL BOOL PokeStatus_ContestFlagGet( SAVEDATA * sv );

//--------------------------------------------------------------------------------------------
/**
 * �y�[�W�쐬
 *
 * @param	dat		�X�e�[�^�X��ʃf�[�^
 * @param	tbl		�y�[�W�e�[�u��
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
GLOBAL void PokeStatus_PageSet( PSTATUS_DATA * dat, const u8 * tbl );

//--------------------------------------------------------------------------------------------
/**
 * �v���C���[���Z�b�g
 *
 * @param	dat		�X�e�[�^�X��ʃf�[�^
 * @param	my		MYSTATUS
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
GLOBAL void PokeStatus_PlayerSet( PSTATUS_DATA * dat, const MYSTATUS * my );

//--------------------------------------------------------------------------------------------
/**
 * ��Ԉُ�A�C�R���̃A�[�J�C�u�C���f�b�N�X���擾�i�L�����j
 *
 * @param	none
 *
 * @return	�A�[�J�C�u�C���f�b�N�X
 */
//--------------------------------------------------------------------------------------------
GLOBAL u32 BadStatusIconCharArcGet(void);

//--------------------------------------------------------------------------------------------
/**
 * ��Ԉُ�A�C�R���̃A�[�J�C�u�C���f�b�N�X���擾�i�p���b�g�j
 *
 * @param	none
 *
 * @return	�A�[�J�C�u�C���f�b�N�X
 */
//--------------------------------------------------------------------------------------------
GLOBAL u32 BadStatusIconPlttArcGet(void);

//--------------------------------------------------------------------------------------------
/**
 * ��Ԉُ�A�C�R���̃A�[�J�C�u�C���f�b�N�X���擾�i�Z���j
 *
 * @param	none
 *
 * @return	�A�[�J�C�u�C���f�b�N�X
 */
//--------------------------------------------------------------------------------------------
GLOBAL u32 BadStatusIconCellArcGet(void);

//--------------------------------------------------------------------------------------------
/**
 * ��Ԉُ�A�C�R���̃A�[�J�C�u�C���f�b�N�X���擾�i�Z���A�j���j
 *
 * @param	none
 *
 * @return	�A�[�J�C�u�C���f�b�N�X
 */
//--------------------------------------------------------------------------------------------
GLOBAL u32 BadStatusIconCanmArcGet(void);

//--------------------------------------------------------------------------------------------
/**
 * ��Ԉُ�A�C�R���̃A�j���ԍ����擾
 *
 * @param	pp		�|�P�����f�[�^
 *
 * @return	�A�j���ԍ�
 */
//--------------------------------------------------------------------------------------------
GLOBAL u32 BadStatusIconAnmGet( POKEMON_PARAM * pp );


#undef GLOBAL
#endif	/* P_STATUS_H */
