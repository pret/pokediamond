//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		nmix_game_comm.h
 *	@brief		�Q�[�����e�@�ʐM�f�[�^�\����
 *	@author		tomoya takahashi
 *	@data		2006.05.25
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
#ifndef __NMIX_GAME_COMM_H__
#define __NMIX_GAME_COMM_H__

#include "nutmixer_def.h"
#include "include/savedata/mystatus.h"
#include "communication/communication.h"
#include "include/savedata/poruto_util.h"

#undef GLOBAL
#ifdef	__NMIX_GAME_COMM_H_GLOBAL
#define	GLOBAL	/* */
#else
#define	GLOBAL	extern
#endif

//-----------------------------------------------------------------------------
/**
 *					�萔�錾
*/
//-----------------------------------------------------------------------------

#ifdef PM_DEBUG
#define NMIX_DEBUG_DUMMY_RESULT_ON
#endif // PM_DEBUG



//-------------------------------------
//	�������N�G�X�g�萔
//=====================================
#define NMIX_GAME_COMM_KOGE_KOGE_REQ	( 1 )
#define NMIX_GAME_COMM_KOGE_KEMURI_REQ	( 2 )

//-------------------------------------
//	�X�[�v�^�C�v��`
//=====================================
enum{
	NMIX_SOOPTYPE_SOOP_0,
	NMIX_SOOPTYPE_SOOP_1,
	NMIX_SOOPTYPE_SOOP_2,
	NMIX_SOOPTYPE_SOOP_NUM,
};


// �X�[�v��]���S���W
#define NMIX_SOOP_ROTA_CX	( 128 )
#define NMIX_SOOP_ROTA_CY	( 96 )

// ���[�h�Z�b�g�ő吔
#define NMIX_GAME_WORD_SET_MAX	( 4 )

//-----------------------------------------------------------------------------
/**
 *					�\���̐錾
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	�Q�[���J�n�O�f�[�^	�q�[���e
//	4
//=====================================
typedef struct {
	u32			nut_type;	// �؂̎��^�C�v			
} NUTMIX_GAME_BGFORE;

//-------------------------------------
//	�e�X�̃f�[�^
//	8byte
//=====================================
typedef struct {
	u8  x;			// ����X���W
	u8  y;			// ����Y���W
	u16 rota;		// ��]�p�x
	
	u8  rota_way;	// 0:�E 1:��	��]����
	u8	dummy[3];	// 4byte���E�p
} NUTMIX_ONE;

//-------------------------------------
//	�e�̓]������f�[�^
//	20byte
//=====================================
typedef struct {
	u8	x[NUTMIXER_MEMBER_MAX];	// �F�̂����W
	u8	y[NUTMIXER_MEMBER_MAX];	// �F�̂����W

	u16 rota;			// �X�[�v��]�p�x
	u16	rota_sp;		// ���̉�]���x
	u8  rota_way;		// 0:�E 1:��	��]����
	u8	mix_type;		// ���̃X�[�v�̌`��	3�^�C�v	
	u8	rota_req_eff;	// ��]�������ς�����̂ŃG�t�F�N�g�o��
	u8	kirakira_eff;	// �L���L���G�t�F�N�g���o���^�C�~���O

	u8	alpha_num;		// �`��̃��l�i���̌`��ɗn������ł����j
	u8	now_rota_req;	// ����]���Ăق��������@0:�E��] 1:����]
	u8	koge_req;		// �������N�G�X�g
	u8	kobore_req;		// ���ڂꃊ�N�G�X�g
} NUTMIX_OYA;

//-------------------------------------
//	�Q�[�����̒ʐM���[�N
//	28byte
//=====================================
typedef struct {
	NUTMIX_ONE one;		// ���ꂼ��̃f�[�^
	NUTMIX_OYA oya;		// �e�f�[�^
} NUTMIX_COMM_DATA;

//-------------------------------------
//	�F�̖؂̎��f�[�^
//	�e->�q
//=====================================
typedef struct {
	NUTMIX_GAME_BGFORE before[ NUTMIXER_MEMBER_MAX ];
	NUTMIX_OYA oya;		// �����e�f�[�^
} NUTMIX_COMM_BEFORE_KO;


//-------------------------------------
//	�v�Z���ʕ\���p�ʐM���[�N
//	�e�[���q
//	20byte
//=====================================
typedef struct {
	u32	kobore_num;	// ���ڂꂽ��
	
	u32	kogasi_num;	// �ł�������

	u32	match_num;	// �`�[�����[�N���_

	u8	poruto_type;// �o�����|���g�̃^�C�v
	u8	poruto_lv;	// �o�����|���g�̃��x��
	u8	min;		// ��
	u8	second;		// �b
	
	u8	dec;		// �R���}
	u8	dummy[3];	// 4byte���E�̂���
} NUTMIX_COMM_RESULT;


//-------------------------------------
//	�Q�[�����ʐM�f�[�^�@�p�b�N�\����
//=====================================
typedef struct {
	// ���M�f�[�^
	NUTMIX_GAME_BGFORE  send_before_data;	// �����̖؂̎��Ȃ�
	NUTMIX_COMM_DATA	send_game_data;		// �����̈ʒu�@��]�p	�e�̂Ƃ��A�����ɍ��̃Q�[����Ԃ�ǉ��Őݒ肷��

	// �e���M�f�[�^
	NUTMIX_COMM_RESULT	send_oya_result_data;		// �Q�[������
	NUTMIX_COMM_BEFORE_KO get_oya_ko_before_data;	// ���̖؂̎����

	// ��M�o�b�t�@
	NUTMIX_COMM_RESULT	get_result_data;			// �Q�[������
	NUTMIX_COMM_BEFORE_KO get_ko_before_data;		// �F�̖؂̎����
	NUTMIX_COMM_DATA	get_game_data[ NUTMIXER_MEMBER_MAX ];	// �Q�[���f�[�^
	PORUTO_DATA*	p_get_ko_poruto;	// �|���g�擾�o�b�t�@

	// �e��M�o�b�t�@
	u32		get_oya_resutl_end[ NUTMIXER_MEMBER_MAX ];
	NUTMIX_GAME_BGFORE  get_before_data[ NUTMIXER_MEMBER_MAX ];
	u8		get_before_data_flg[ NUTMIXER_MEMBER_MAX ];
	u8		game_next[NUTMIXER_MEMBER_MAX];	// �Q�[�����Â��邩
	u8		get_next_data_flg[ NUTMIXER_MEMBER_MAX ];

	// �v���C���[�i���o�[����l�b�gID�i���o�[���擾
	u8	playno_netid[NUTMIXER_MEMBER_MAX];
	// �v���C���[�X�e�[�^�X
	const MYSTATUS*	p_mystate[NUTMIXER_MEMBER_MAX];

	u8 my_netid;

	// ��M�f�[�^
	u8				get_game_next;		// �Q�[���𑱂���Ƃ� TRUE
} NUTMIX_GAME_COMM_PACK;



//-----------------------------------------------------------------------------
/**
 *					�v���g�^�C�v�錾
*/
//-----------------------------------------------------------------------------
#undef	GLOBAL
#endif		// __NMIX_GAME_COMM_H__

