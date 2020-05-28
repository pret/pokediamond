/**
 *	@file	nmix_game.h
 *	@brief	�i�b�c�~�L�T�[�@�Q�[���v���Z�X�w�b�_
 *	@author	Miyuki Iwasawa
 *	@date	06.07.08
 *	@data		2006.05.23		tomoya �X�V
 */

#ifndef __H_NMIX_GAME_H__
#define __H_NMIX_GAME_H__

#include "nutmixer_def.h"
#include "nutmix_comm_pack.h"
#include "nmix_game_comm.h"
#include "nmix_game_demo.h"
#include "nmix_game_data.h"
#include "nmix_stdata.h"

#include "common.h"
#include "system/clact_util.h"
#include "system/swsprite.h"

//-----------------------------------------------------------------------------
/**
 *
 *					�萔
 *
 */
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/**
 *					�\���̐錾
*/
//-----------------------------------------------------------------------------
// �����G�t�F�N�g�o���Ă���l
#define NMIX_GAME_WAY_FLAG_RIGHT	( 1 )
#define NMIX_GAME_WAY_FLAG_LEFT	( 2 )


//-------------------------------------
//	�؂̎��~�L�T�[���[�N
//=====================================
typedef struct {
	// �V�X�e���Ǘ�
	int	heapID;
	BOOL seqend_f;		///<�Q�[���V�[�P���X�I���t���O
	int	synchroID;		///<�ʐM����ID
	int	main_seq;		///<�Q�[�����C���V�[�P���X����
	int	sub_seq;		///<�Q�[���T�u�V�[�P���X����
	BOOL main_seq_chg_req;///<�ʐM�R�[���o�b�N����̃V�[�P���X�ύX���肢�����������t���O
	int main_seq_req;	///<�ʐM�R�[���o�b�N����̃V�[�P���X�ύX���肢

	int wait;

#ifdef PM_DEBUG
	int comm_err_count;
#endif
	
	// BG
	GF_BGL_INI* bgl;
	int wnd_type;
	int msg_speed;

	// OAM
	NMIXGAME_CLACT_SYS	clact;
	NMIXGAME_CLACT_RES_WORK def_clact_res[ NMIX_GAME_DEF_OAM_RES_NUM ];
	BOOL clact_draw;

	// �\�t�g�E�F�A�X�v���C�g
	SWSP_SYS_PTR	swsp_sys;


	// ��ʊǗ��f�[�^
	u32 houkou_draw_flg;	// �����؂�ւ��\����
	u32 gyaku_draw_flg;		// �t��]�\����
	BOOL kogeru_draw_flg;	// ������\����
	BOOL kobore_draw_flg;	// ���ڂ��\����

	// �������[�N
	NMIX_DATA_KO	ko_data;	// �ʐM�q�f�[�^
	NMIX_DATA_OYA	oya_data;
	u32 game_next;				// �Q�[���𑱂�������
	s32 last_rota;				// �P�O�̐e���痈����]�p
	u32 last_count_down;		// �J�E���g�_�E���f�[�^

	// �`�惏�[�N
	NMIX_DEMO_NUTS_IN nuts_in;	// �؂̎�����
	NMIX_DEMO_SUB_WIN sub_win;	// �T�u�E�B���h�E����
	NMIX_DEMO_COUNTDOWN countdown;	// �J�E���g�_�E��
	NMIX_DEMO_COUNTDOWN end_mark;	// �I��MARK
	NMIX_DEMO_COUNTDOWN pen;		// �y��
	NMIX_DEMO_NABE_GRA nabe_gra;	// ��O���t�B�b�N��������
	NMIX_DEMO_OTHER_MARK other_mark;	// ���̐l�̈ʒu
	NMIX_DEMO_MAIN_WIN main_win;		// ���C�����BG�Ǘ�
	NMIX_DEMO_SOOP_EFFECT soop_effect;	// �X�[�v�G�t�F�N�g
	NMIX_DEMO_YAZIRUSI	yazirusi;	// ���I�u�W�F�N�g
	NMIX_DEMO_HOSI_KIRAKIRA hosi_kira;	// ���L���L��
	NMIX_DEMO_PORUTO_DRAW poruto_draw;	// �|���g�`��
	NMIX_DEMO_YESNO_WND	yes_no;		// YESNO�E�B���h�E
	

	//�ʐM�֘A�f�[�^�̈�
	int				comm_count;	// �ʐM�����o�[��
	NUTMIX_COMMPACK_WORK* comm_work;// �ʐM���[�N
	int				commpack_flg;	// �ʐM�p�b�N�t���O
									// NUTMIX_COMM_PACK_ONE	( 0 )	// ��l�p
									// NUTMIX_COMM_PACK_COMM	( 1 )	// �ʐM

	// �ʐM�f�[�^
	NUTMIX_GAME_COMM_PACK game_comm_pack;

	// ���b�Z�[�W�f�[�^
	NMIXER_MSG	msgDat;

} NMIX_GAMEWORK;

extern void NMIX_SetMainSeq( NMIX_GAMEWORK* p_work, int seq );
extern void NMIX_SetSubSeq( NMIX_GAMEWORK* p_work, int seq );
extern void NMIX_SetEndReq( NMIX_GAMEWORK* p_work );


#endif	//__H_NMIX_GAME_H__

