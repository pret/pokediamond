//==============================================================================
/**
 * @file	ball_effect.h
 * @brief	�{�[���G�t�F�N�g
 * @author	goto
 * @date	2005.10.26(��)
 *
 * �����ɐF�X�ȉ�����������Ă��悢
 *
 */
//==============================================================================

#ifndef __BALL_EFFECT_H__
#define __BALL_EFFECT_H__

#include "include/system/particle.h"
#include "wazaeffect/wp_tbl.h"
#include "wazaeffect/wazatool.h"

#include "battle/battle_common.h"
#include "battle/fight_tool.h"

#include "include/itemtool/itemsym.h"

/*
#define ITEM_MASUTAABOORU		( 1 )		// �}�X�^�[�{�[��
#define ITEM_HAIPAABOORU		( 2 )		// �n�C�p�[�{�[��
#define ITEM_SUUPAABOORU		( 3 )		// �X�[�p�[�{�[��
#define ITEM_MONSUTAABOORU		( 4 )		// �����X�^�[�{�[��
#define ITEM_SAFARIBOORU		( 5 )		// �T�t�@���{�[��
#define ITEM_NETTOBOORU		( 6 )		// �l�b�g�{�[��
#define ITEM_DAIBUBOORU		( 7 )		// �_�C�u�{�[��
#define ITEM_NESUTOBOORU		( 8 )		// �l�X�g�{�[��
#define ITEM_RIPIITOBOORU		( 9 )		// ���s�[�g�{�[��
#define ITEM_TAIMAABOORU		( 10 )		// �^�C�}�[�{�[��
#define ITEM_GOOZYASUBOORU		( 11 )		// �S�[�W���X�{�[��
#define ITEM_PUREMIABOORU		( 12 )		// �v���~�A�{�[��
#define ITEM_DAAKUBOORU		( 13 )		// �_�[�N�{�[��
#define ITEM_HIIRUBOORU		( 14 )		// �q�[���{�[��
#define ITEM_KUIKKUBOORU		( 15 )		// �N�C�b�N�{�[��
#define ITEM_PURESYASUBOORU		( 16 )		// �v���V���X�{�[��
*/

#define BALL_EFF_EX_DP		(0xFF)						// DP�p�g��ID�@���g��Ȃ��ł�������

#define BALL_EFF_PARK_BALL	(BALL_EFF_EX_DP + 17)		// �p�[�N�{�[��
#define BALL_EFF_STONE		(BALL_EFF_EX_DP + 18)		// �D
#define BALL_EFF_FOOD		(BALL_EFF_EX_DP + 19)		// �G�T
#define BALL_EFF_BACK		(BALL_EFF_EX_DP + 20)		// �߂� �����ڎw��֎~

#define BALL_EFF_DP_END		(BALL_EFF_BACK)				// DP�̏I���

///< �����ǂݍ���
#define LOAD_SEQ_SEP
#define LOAD_SEQ_END		(0xFF)


// -----------------------------------------
//
//	�{�[���G�t�F�N�g�p�̒萔��`
//
// -----------------------------------------
#include "wazaeffect/effectdata/waza_particle_def.h"
//#include "wazaeffect/effectdata/p_ball_effect.h"
//#include "wazaeffect\effectdata\we_list.h"
#include "wazaeffect\effectdata\ball_effect_setup.h"
#define BALL_EFFECT_USE_SPA		(SPA_P_BALL_EFFECT)			///< ���p����SPA
#define BALL_EFFECT_BIT_MAX		(20)//P_BALL_EFFECT_SPAMAX)		///< SPA�̓o�^��


// -----------------------------------------
//
//	�{�[���G�t�F�N�g�Ǘ��V�X�e��
//
// -----------------------------------------
typedef struct _TBALL_EFFECT_SYS * BES_PTR;


// -----------------------------------------
//
//	�J�X�^�}�C�Y�p�����[�^�[
//
// -----------------------------------------
typedef struct {
	
	int	client_type;		///< �e�{�[���������p�����[�^�ɓn���K�v������
	
	int ball_id;

	POKEMON_PARAM*	pp;		///< �|�P�����p�����[�^

} TBALL_CUSTOM_PARAM;

/*

�����X�^�[�{�[��
�X�[�p�[�{�[��
�n�C�p�[�{�[��
�}�X�^�[�{�[��
�T�t�@���{�[��
�l�b�g�{�[��
�_�C�u�{�[��
�l�X�g�{�[��
���s�[�g�{�[��
�^�C�}�[�{�[��
�S�[�W���X�{�[��
�v���~�A�{�[��
�_�[�N�{�[��
�q�[���{�[��
�N�C�b�N�{�[��
�v���V�A�{�[��

*/

// -----------------------------------------
//
//	�萔��`
//
// -----------------------------------------
#define BECB_INIT_DEF_POS	(1)			///< �������W�w��
#define	BECB_INIT_VELO		(1)			///< �����x�ύX
#define	BECB_GENE_RAITO		(1)			///< ���[�g�ύX
#define	BECB_INTERVAL		(0)			///< ���o�Ԋu�ύX
#define	BECB_INIT_POS		(0)			///< �������W�ύX

enum EEFF_TYPE {
	BE_EFF_MONSTAR_BALL = 0,			///< �ʏ�̃����X�^�[�{�[��
	BE_EFF_CUSTOM_BALL,					///< �J�X�^���{�[��
};

enum EBE_BIT {							///< �G�t�F�N�g�r�b�g���샂�[�h
	BEBIT_ON	= 0,					///< Set
	BEBIT_OFF,							///< Reset
	BEBIT_CHECK,						///< Check
};


// -----------------------------------------
//
//	�������m�ۏ�����
//
// -----------------------------------------
extern BES_PTR BallEffect_InitEz(int heap_area);


// -----------------------------------------
//
//	�������m�ہ{�p�����[�^�[�ݒ�
//
// -----------------------------------------
extern BES_PTR BallEffect_Init(int heap_area, const TBALL_CUSTOM_PARAM* bcp);


// -----------------------------------------
//
//	���\�[�X�ǂݍ���
//
// -----------------------------------------
extern void BallEffect_ResourceLoad(BES_PTR bes);
extern BOOL BallEffect_IsLoadEnd(BES_PTR bes);


// -----------------------------------------
//
//	�p�����[�^�[�ݒ�
//
// -----------------------------------------
extern void BallEffect_ParamSet(BES_PTR bes, const TBALL_CUSTOM_PARAM* bcp);


// -----------------------------------------
//
//	�G�t�F�N�g���s
//
// -----------------------------------------
extern void BallEffect_Executed(BES_PTR bes, pEmitFunc callback);
extern void BallEffect_ExecutedEz(BES_PTR bes);


// -----------------------------------------
//
//	�G�t�F�N�g�I���`�F�b�N
//
// -----------------------------------------
extern BOOL BallEffect_EndCheck(BES_PTR bes);


// -----------------------------------------
//
//	�������̉��
//
// -----------------------------------------
extern void BallEffect_FreeMemory(BES_PTR bes);



#define ALL_DATA_SET	(0xFF)
#define ONE_DATA_SET	(0xEE)

typedef struct {
	
	s16 x;
	s16 y;
	
	int	ball_id;
	int heap_id;
	
	int set_id;			///< ���̒l���A0xFF�̏ꍇ�́A���ׂēo�^ 0xFF �������Ȃ炻��̂ݓo�^
	int close_only;		///< ���̃t���O������ƁA�{�[���ԍ��������ĕ���p�̃G�t�F�N�g���o��
	
} TSP_BALL_PARAM;


typedef struct _TSP_BALL_SYS * SPB_PTR;

extern SPB_PTR	SPB_Init(TSP_BALL_PARAM* param);
extern void		SPB_Load(SPB_PTR spb);
extern BOOL		SPB_Main(SPB_PTR spb);
extern void		SPB_End(SPB_PTR spb);






// =============================================================================
//
//
//	���{�[�������G�t�F�N�g
//
//
// =============================================================================
typedef struct _TBALL_MOVE_SYS * BMS_PTR;

typedef struct {

	int type;
	int heap_id;
	int mode;
	int id;						///< �N���C�A���gNO
	int ball_id;				///< �{�[��ID
	int	bg_pri;
	int surface;				///< �T�[�t�F�C�X�ǂ����邩
	
	CATS_SYS_PTR		csp;
	PALETTE_FADE_PTR	pfd;
	
	BATTLE_WORK*		bw;
	
} TBALL_MOVE_DATA;

enum EBM_TYPE {
	
	EBMT_STAY_AA = 0,	///< ��{�ʒu
	EBMT_STAY_BB,
	EBMT_STAY_A,
	EBMT_STAY_B,
	EBMT_STAY_C,
	EBMT_STAY_D,

	EBMT_THROW_C,		///< 1�C�̎�
	EBMT_THROW_R,		///< �E�ɓ���������
	EBMT_THROW_L,		///< ���ɓ���������
	
	EBMT_THROW_E0,		///< �G�ɓ�����
	EBMT_THROW_E1,		///< �G2�΂̉E��
	EBMT_THROW_E2,		///< �G2�΂̍���
	
	EBMT_THROW_E0_STONE,///< �G�ɓ�����@��
	EBMT_THROW_E0_FOOD,	///< �G�ɓ�����@�G�T
	
	EBMT_VISUAL,		///< �R���e�X�g�r�W���A������
	
	EBMT_CAPTURE_BB,	///< �ߊl�f��
	EBMT_CAPTURE_B,		///< �ߊl�f��
	EBMT_CAPTURE_D,		///< �ߊl�f��
	
	EBMT_MAX,
};

enum EBM_MODE {
	
	EBMM_THROW = 0,		///< ������
	EBMM_FAILURE,		///< ���s��p
	
	EBMM_SHAKE,			///< �h�炷
	
	EBMM_CAPTURE,		///< �ߊl�p

	EBMM_FREE,			///< ���R��
	
	EBMM_CLOSE,			///< �߂�
	
};

enum EBM_STATE {
	
	EBMS_START	= 0,	///< �J�n
	
	EBMS_THROW,			///< �����Ă���
	EBMS_THROW_END,		///< �|�P�����̓���ɓ���
	
	EBMS_OPEN,			///< �J���Ă���
	EBMS_OPEN_END,		///< �J���I�����
	
	EBMS_SHED,			///< �g���[�i�[�킾�����e��
	EBMS_SHED_END,		///< �g���[�i�[�킾�����I�����
	
	EBMS_CLOSE,			///< ���Ă���
	EBMS_CLOSE_END,		///< ���I�����
	
	EBMS_FLASH,			///< �����Ă���
	EBMS_FLASH_END,		///< ����I�����
	
	EBMS_FALL,			///< �������Ă���
	EBMS_FALL_END,		///< �������I�����
	
	EBMS_BOUNCE,		///< ���˂Ă���
	EBMS_BOUNCE_END,	///< ���ˏI�����
	
	EBMS_STOP,			///< ��~
	EBMS_STOP_END,		///< ��~���I�����
	
	EBMS_ROLL,			///< �]���� 5dot
	EBMS_ROLL_END,		///< �]����I�����
	
	EBMS_FAILURE,		///< ���s
	EBMS_FAILURE_END,	///< ���s�I�����
	
	EBMS_SUCCESS_1,		///< ���� - 1 �Â��Ȃ�
	EBMS_SUCCESS_1_END,	///< �����I�����
	
	EBMS_SUCCESS_2,		///< ���� - 2 ���ɖ߂�
	EBMS_SUCCESS_2_END,	///< �����I����� - 2
	
	EBMS_SUCCESS_3,		///< ���� - 3 ������
	EBMS_SUCCESS_3_END,	///< �����I����� - 3
	
	EBMS_END,			///< �I��
};

enum EBM_DEMO {
	
	EBM_DEMO_SCENE_THROW = 0,		///< �{�[�������`�܂�
	EBM_DEMO_SCENE_OPEN,			///< �J��
	EBM_DEMO_SCENE_SHED,			///< �e�����
	EBM_DEMO_SCENE_FALL,			///< ����`�o�E���h
	EBM_DEMO_SCENE_ROLL,			///< ��~�`���낱��
	EBM_DEMO_SCENE_END_FAILURE,		///< ���s�`�I��
	EBM_DEMO_SCENE_END_SUCCESS,		///< �ߊl�`�Â��Ȃ�܂�
	EBM_DEMO_SCENE_END_SUCCESS_2,	///< �Â��Ȃ��Ă���`�I��

};

enum EBM_ANIME {
	
	EBM_ANM_THROW = 0,
	EBM_ANM_CLOSE = 0,
	EBM_ANM_OPEN,
};

#define BM_STOP_TIME		(5)//(5)		///< 10
#define BM_OPEN_WAIT		(15)//(10)	///< 15
#define BM_OPEN_WAIT_2		(15)	///< 20

#define BM_BG_PRI_BATTLE	(1)
#define BM_BG_PRI_CUSTOM	(0)
#define BM_SUITABLE_ID		(0xFF)
#define BM_BOUNCE_WAIT		(20)
#define BM_STOP_WAIT		(14)
#define BM_ROLL_DOT_RAD(n)	( (n) * 2)
#define BM_ROLL_RAD(n)		( FX_GET_ROTA_NUM(BM_ROLL_DOT_RAD(n)) )
#define BM_ROLL_WAIT		(11)
#define BM_ROLL_NUM			(3)

#define BM_FALL_WAIT		(1)

#define BM_FADE_FLASH		(0x037F)
#define BM_FADE_FLASH_PARA	(12)
#define BM_FADE_FLASH_SPD	(-1)
#define BM_FADE_DARK		(0x0000)
#define BM_FADE_DARK_PARA	(10)			///< �Â��Ȃ�x
#define BM_FADE_DARK_SPD	(-5)			///< �Â��Ȃ�X�s�[�h

#if 0

#define BM_STOP_TIME		(10)//(5)		///< 10
#define BM_OPEN_WAIT		(15)//(10)	///< 15
#define BM_OPEN_WAIT_2		(15)	///< 20

#define BM_BG_PRI_BATTLE	(1)
#define BM_BG_PRI_CUSTOM	(0)
#define BM_SUITABLE_ID		(0xFF)
#define BM_BOUNCE_WAIT		(30)
#define BM_STOP_WAIT		(21)
#define BM_ROLL_DOT_RAD(n)	( (n) * 2)
#define BM_ROLL_RAD(n)		( FX_GET_ROTA_NUM(BM_ROLL_DOT_RAD(n)) )
#define BM_ROLL_WAIT		(9)
#define BM_ROLL_NUM			(3)

#define BM_FALL_WAIT		(4)

#define BM_FADE_FLASH		(0x037F)
#define BM_FADE_FLASH_PARA	(12)
#define BM_FADE_FLASH_SPD	(-4)
#define BM_FADE_DARK		(0x0000)
#define BM_FADE_DARK_PARA	(10)			///< �Â��Ȃ�x
#define BM_FADE_DARK_SPD	(-2)			///< �Â��Ȃ�X�s�[�h

#endif

extern BMS_PTR	BM_Init(TBALL_MOVE_DATA* bmd);
extern BOOL		BM_EndCheck(BMS_PTR bms);
extern BOOL 	BM_IsOpen(BMS_PTR bms);

extern void		BM_Delete(BMS_PTR bms);
extern void		BM_ModeChange(BMS_PTR bms, int mode);
extern int		BM_ModeGet(BMS_PTR bms);


extern int		BM_CaptureStateGet(BMS_PTR bms);
extern void		BM_CaptureStateSet(BMS_PTR bms, int state);
extern BOOL		BM_IsCaptureStateEnd(BMS_PTR bms, int state);

extern void		BM_SceneSet(BMS_PTR bms, int scene);
extern BOOL		BM_SceneStateGet(BMS_PTR bms, int scene);

///< �O������
extern void		BM_BallEnable(BMS_PTR bms, int flag);			///< �{�[���̕\����\��
/*
	CATS_ENABLE_TRUE	= �\��
	CATS_ENABLE_FALSE	= ��\��
*/
extern void		BM_BallPosGet(BMS_PTR bms, s16* x, s16* y);		///< �{�[���̈ʒu�擾
extern void		BM_BallPosSet(BMS_PTR bms, s16 x, s16 y);		///< �{�[���̈ʒu�ݒ�
extern void		BM_BallRadGet(BMS_PTR bms, u16* rot);			///< �{�[���̊p�x�擾
extern void		BM_BallRadSet(BMS_PTR bms, u16 rot);			///< �{�[���̊p�x�擾
extern void		BM_BallAnimeFlagSet(BMS_PTR bms, BOOL flag);	///< �{�[���̃A�j���t���O
extern void		BM_BallSoftPriSet(BMS_PTR bms, int pri);		///< �{�[���̗D��x
extern void		BM_BallBgPriSet(BMS_PTR bms, int pri);			///< �{�[���̗D��x
extern void		BM_BallFreeEnd(BMS_PTR bms);					///< ���R������I��点��
extern void		BM_BallWaitSet(BMS_PTR bms, int wait);			///< �O���w��E�F�C�g


#endif
