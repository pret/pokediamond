//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		nmix_game_data.h
 *	@brief		�؂̎��~�L�T�[�@�f�[�^�Ǘ���
 *	@author		tomoya takahashi
 *	@data		2006.05.27
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
#ifndef __NMIX_GAME_DATA_H__
#define __NMIX_GAME_DATA_H__


#include "nmix_game_comm.h"

#include "savedata/poruto_util.h"

#undef GLOBAL
#ifdef	__NMIX_GAME_DATA_H_GLOBAL
#define	GLOBAL	/* */
#else
#define	GLOBAL	extern
#endif

//-----------------------------------------------------------------------------
/**
 *
 *		���ʒ萔��`
 *
 */
//-----------------------------------------------------------------------------


#define NMIX_SOOP_SCORE_MAX	(9999)	// ���_�ő�

// �_�ړ������X�[�v�X�s�[�h�ύX�}�N��
#define NMIX_SOOP_SPEED		( 160 )
#define NMIX_SOOP_SPEED_GET(x)	( (x) * NMIX_SOOP_SPEED )
#define NMIX_SOOP_SPEED_RESET(x) ( (x) / NMIX_SOOP_SPEED )

// ��]�v�Z���a
#define NMIX_SOOP_ROTA_GET_R	( 68 )


// �X�[�v��]�������N���鑬�x
#define NMIX_SOOP_KOBORE	( 3640 )
#define NMIX_SOOP_KOGE		( 910 )

// �ēx���ڂꂽ��A�������肷��@�^�C�~���O
#define NMIX_SOOP_KOBORE_RETIME	( 30 )
#define NMIX_SOOP_KOGE_RETIME	( 30 * 3 )

// �ő��]�X�s�[�h
#define NMIX_SOOP_MAX_ROTA	( NMIX_SOOP_KOBORE )

// �X�[�v�g�嗦�ő�
#define NMIX_SOOP_MAX_SCALE	( FX32_CONST( 0.25f ) )

// ��]�p�x�����߂�v�Z
GLOBAL s32	NMIX_DATA_CalcRota( int x, int y, int last_x, int last_y, int center_x, int center_y );


//-----------------------------------------------------------------------------
/**
 *
 *		�q�f�[�^
 *
 */
//-----------------------------------------------------------------------------
//-------------------------------------
//	�q�f�[�^
//=====================================
typedef struct {
	int x;
	int y;
	int last_x;
	int last_y;
	s32 rota;
	BOOL last_touch_flg;
} NMIX_DATA_KO;
GLOBAL void NMIX_DATA_KoInit( NMIX_DATA_KO* p_data );
GLOBAL void NMIX_DATA_KoMain( NMIX_DATA_KO* p_data );
GLOBAL void NMIX_DATA_KoMake( NUTMIX_ONE* p_commdata, NMIX_DATA_KO* p_data );



//-----------------------------------------------------------------------------
/**
 *				�e�̂ݕK�v�Ȃ���
 */
//-----------------------------------------------------------------------------
//-------------------------------------
//	�X�[�v��ԊǗ��f�[�^
//=====================================
typedef struct {
	u32	soop_type;	// ���݃X�[�v�^�C�v
	u32	rota_count;	// ��]���J�E���g
	s32 now_rota;	// ���݉�]�p�x
	s32	sp_rota;	// ��]�X�s�[�h

	BOOL ok_area;	// ���v�G���A
} NMIX_DATA_SOOP;

GLOBAL u16 NMIX_DATA_SoopRota( NMIX_DATA_SOOP* p_data, const NUTMIX_GAME_COMM_PACK* cp_commdata, u32 comm_count, u32 rota_way );
GLOBAL u16 NMIX_DATA_SoopGetRota( const NMIX_DATA_SOOP* cp_data );
GLOBAL u32 NMIX_DATA_SoopGetRotaCount( const NMIX_DATA_SOOP* cp_data );
GLOBAL void NMIX_DATA_SoopSetType( NMIX_DATA_SOOP* p_data, int type );
GLOBAL s32 NMIX_DATA_SoopGetRotaSpeed( const NMIX_DATA_SOOP* cp_data );

//-------------------------------------
//	�X�[�v�X�s�[�h�ɂ��ς��f�[�^�Ǘ���
//=====================================
typedef struct {
	u32 koge_count;			// ��������
	u32 kobosi_count;		// ���ڂ�����
	// ����
	u32 speed_none_count;	// ���������Ă��鎞��
	// ���ڂ�
	u32 speed_over_count;	// ���ڂꑱ���Ă��鎞��

	// �G�t�F�N�g���N�G�X�g
	u32 koge_eff;
	BOOL first_koge_eff;
	BOOL kobosi_eff;
} NMIX_DATA_SOOP_SPEED;

GLOBAL void NMIX_DATA_SoopSpeedMain( NMIX_DATA_SOOP_SPEED* p_data, s32 speed, int soop_type );
GLOBAL BOOL NMIX_DATA_SoopSpeedKobore( s32 speed, int soop_type );
GLOBAL BOOL NMIX_DATA_SoopSpeedKoge( s32 speed, int soop_type );
GLOBAL fx32 NMIX_DATA_SoopSpeedGraScale( u16 speed, int soop_type );


//-------------------------------------
//	��]�����Ǘ�
//=====================================
typedef struct {
	int rota_way_req;	// ��]���Ăق�������
	int rota_way_count;	// ���̕����`�F�b�N�܂ł̃J�E���g�l
	int left_par;		// ���̏o��p�[�Z���e�[�W�@�����͍ő�T	������2�Ƃ��Ă���, 2�ȉ��Ȃ獶�@�傫���Ȃ�E�@�E���o����left_par�𑫂� �����o����left_par������
	BOOL rota_way_chg;
} NMIX_DATA_ROTA_WAY_CONT;
GLOBAL void NMIX_DATA_RotaWayCont_Init( NMIX_DATA_ROTA_WAY_CONT* p_work );
GLOBAL void NMIX_DATA_RotaWayCont_Main( NMIX_DATA_ROTA_WAY_CONT* p_work, int soop_type, s32 speed, BOOL team_work );

GLOBAL BOOL NMIX_DATA_RotaWayReverseCheck( const NMIX_DATA_ROTA_WAY_CONT* cp_work, s32 speed );

//-------------------------------------
//	�X�[�v�i���Ǘ�
//=====================================
typedef struct {
	int next_time;
	int rota_alpha;
	int soop_type;	// ���̃X�[�v�^�C�v
} NMIX_DATA_SOOP_ADD;
GLOBAL BOOL NMIX_DATA_SoopAdd_Main( NMIX_DATA_SOOP_ADD* p_work, NMIX_DATA_SOOP* p_soop );
#define NMIX_DATA_SOOPADD_NEXT_TIME	( 20*30 )	// �����ύX�^�C��
#define NMIX_DATA_SOOP_COOK_MAX_TIME	( NMIX_DATA_SOOPADD_NEXT_TIME * 3 )	// �������Ԃ̍ő�


//-------------------------------------
//	�`�[�����[�N�v���C�Ǘ�
//=====================================
typedef struct {
	int team_work_time;	// TEAMWORK�𔭊���������
	int team_work_time_add_wait;
	BOOL team_work_time_add_flg;	// TRUE	TEAMWORK���_��
	BOOL team_work_req;	// �G�t�F�N�g���˃��N�G�X�g
} NMIX_DATA_TEAMWORK;
GLOBAL void NMIX_DATA_TeamWork_Main( NMIX_DATA_TEAMWORK* p_work, const NUTMIX_GAME_COMM_PACK* cp_comm_pack, int comm_count, s32 speed, int soop_type, BOOL ok_area, BOOL reverse );
#define NMIX_DATA_TEAMWORK_AREA	( 32 )	// ���a���ꂢ�Ȃ��ɓ����Ă��邩�`�F�b�N����
#define NMIX_DATA_TEAMWORK_EFF_TIMING	( 1 )	// ~�J�E���g�ɂP��������
#define NMIX_DATA_TEAMWORK_EFF_ADD_WAIT	( 4 )	// �Œ�ł����̃V���N���ꏏ�ɂ��Ȃ��ƁATEAMWORK���_���͂���Ȃ�


//-------------------------------------
//	�S�̊Ǘ�����
//=====================================
typedef struct {
	u32	cook_time;	// ��������
	u32 poruto_type;	// �|���g�̃^�C�v
	u32 poruto_lv;		// �|���g�̃��x��
	NMIX_DATA_ROTA_WAY_CONT rota_waycont;
	NMIX_DATA_SOOP soop_cont;
	NMIX_DATA_SOOP_SPEED soop_speed_data;
	NMIX_DATA_SOOP_ADD soop_add;
	NMIX_DATA_TEAMWORK team_work;
} NMIX_DATA_OYA;

GLOBAL void NMIX_DATA_OyaInit( NMIX_DATA_OYA* p_data );
GLOBAL BOOL NMIX_DATA_OyaMain( NMIX_DATA_OYA* p_data, const NUTMIX_GAME_COMM_PACK* cp_commdata, u32 comm_count );
GLOBAL void NMIX_DATA_OyaCommDataMake( NMIX_DATA_OYA* p_data, NUTMIX_GAME_COMM_PACK* p_comm_pack, int comm_count );
GLOBAL void NMIX_DATA_OyaCookCountAdd( NMIX_DATA_OYA* p_data );
GLOBAL void NMIX_DATA_OyaCommDataMake_Init( NMIX_DATA_OYA* p_data, NUTMIX_OYA* p_oya, int comm_count );

GLOBAL void NMIX_DATA_OyaCalcPorutoData( NMIX_DATA_OYA* p_data, PORUTO_DATA* p_poruto, const NUTMIX_GAME_COMM_PACK* cp_commdata, u32 comm_count, u32 heapID );

GLOBAL void NMIX_DATA_OyaCommDataMake_Result( NMIX_DATA_OYA* p_data, NUTMIX_GAME_COMM_PACK* p_comm_pack, int comm_count );

#ifdef NMIX_DEBUG_DUMMY_RESULT_ON
GLOBAL void NMIX_DATA_OyaCommDataMake_Result_MaxDebug( NMIX_DATA_OYA* p_data, NUTMIX_GAME_COMM_PACK* p_comm_pack, int comm_count );
#endif // NMIX_DEBUG_DUMMY_RESULT_ON


#undef	GLOBAL
#endif		// __NMIX_GAME_DATA_H__

