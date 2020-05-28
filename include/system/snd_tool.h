//==============================================================================================
/**
 * @file	snd_tool.h
 * @brief	�T�E���h�c�[���֐�
 * @author	Satoshi Nohara
 * @date	2005.06.09
 */
//==============================================================================================
#ifndef __SND_TOOL_H__
#define __SND_TOOL_H__

#include "system/snd_def.h"
#include "system/snd_play.h"

//�T�E���h�f�[�^�̎w���ԍ��ł͂Ȃ��A�T�E���h�f�U�C�i�[����`�������x���ōs����悤�ɂȂ�
//C:\NitroSystem\build\demos\snd\data
//#include "C:\NitroSystem\tools\nitro\SoundPlayer\data\sound_data.sadl"
#include "data/sound/sound_data.sadl"		//�T�E���h���x���t�@�C��


//==============================================================================================
//
//	��`
//
//==============================================================================================
//sound_data.sarc�̕ύX�́A���ӂ���I
#define SND_PLAYER_EXTRA_CH		(13)		//�\���̃`�����l��(�ʐM�o�g���{�C�X�`���b�g�Ŏg�p)

//�T�E���h�V�X�e����Ԓ�`
enum{
	//SND_STATUS_INIT = 0,
	//SND_STATUS_PLAYSTART,
	//SND_STATUS_FADENEXT,
	//SND_STATUS_FADENEXTFADE,
	SND_STATUS_STOP = 0,					//��~
	SND_STATUS_PLAY,						//�Đ�
	SND_STATUS_PLAING,						//�Đ���
	SND_STATUS_FADEIN,						//�t�F�[�h�C��
	SND_STATUS_FADEOUT,						//�t�F�[�h�A�E�g
	SND_STATUS_FADEOUT_NEXT_PLAY,			//�t�F�[�h�A�E�g �� �ǉ��g�`�ǂݍ��� �� BGM�Đ�
	SND_STATUS_FADEOUT_NEXT_FADEIN,			//�t�F�[�h�A�E�g �� �ǉ��g�`�ǂݍ��� �� BGM�t�F�[�h�C��
	SND_STATUS_TRACKFADE,					//�g���b�N�t�F�[�h
};

//�Đ����x��`
enum{
	WAVEOUT_PLAY_SPDx05		=	(32768 / 2),				//2����1�{��
	WAVEOUT_PLAY_SPDx1		=	(32768),					//1�{��
	WAVEOUT_PLAY_SPDx2		=	(32768 * 2),				//2�{��
	WAVEOUT_PLAY_SPDx3		=	(32768 * 3),				//3�{��
};

//�t�F�[�h�t���[����`
enum{
	BGM_FADE_ZUKAN_TIME		=	(15),						//�}�Ӊ��BGM
	BGM_FADE_ZUKAN_NAKIGOE_TIME	 =	(3),					//�}�Ӗ������BGM
	BGM_FADE_TR_CASE_TIME	= 	(15),						//�g���[�i�[�P�[�XBGM
	BGM_FADE_ROOM_TIME		=	(30),						//�����؂�ւ�
	BGM_FADE_FIELD_TIME		= 	(60),						//�t�B�[���h(�]�[��)�؂�ւ�
	BGM_FADE_CAVE_TIME		=	(60),						//���A�̏o����
	BGM_FADE_TANKOU_TIME	= 	(60),						//�Y�z��BGM�؂�ւ�
	BGM_FADE_CLIP_TIME		= 	(30),						//�C���[�W�N���b�v�؂�ւ�
	BGM_FADE_VCHAT_TIME		= 	(30),						//�{�C�X�`���b�g�؂�ւ�
	BGM_FADE_OTHERS_TIME	= 	(60),						//���̑�
	BGM_FADE_UG_TIME		= 	(30),						//�n���ւ̍s����
	BGM_FADE_MAPJUMP_TIME	= 	(40),						//map_jump.c
};

//�t�F�[�h���[�h��`(fld_bgm.c)
enum{
	BGM_FADE_ROOM_MODE		=	(0),						//�����̏o����
	BGM_FADE_FIELD_MODE,									//�t�B�[���h�̐؂�ւ�
	BGM_FADE_CAVE_MODE,										//���A�̏o����
	BGM_FADE_OTHERS_MODE,									//���̑�
};

//�V�[��(���)��`
enum{
	SND_SCENE_DUMMY = 0,				//�_�~�[(�N���A�R�[�h)

	//���C�����
	SND_SCENE_MAIN = 1,					//�X�^�[�g�i���o�[
	SND_SCENE_TITLE = SND_SCENE_MAIN,	//�^�C�g��
	SND_SCENE_OPENING,					//�I�[�v�j���O
	SND_SCENE_TRADE,					//�����f��
	SND_SCENE_FIELD,					//�t�B�[���h
	SND_SCENE_BATTLE,					//�o�g��
	SND_SCENE_CONTEST,					//�R���e�X�g
	SND_SCENE_CON_IMAGE,				//�C���[�W�N���b�v(�R���e�X�g)(06.04.18)
	SND_SCENE_DENDOU,					//�a���f��
	SND_SCENE_AGB,						//AGB�̃|�P�����������Ă�����
	SND_SCENE_HUSIGI,					//�ӂ����Ȃ�������̉��
	SND_SCENE_P2P,						//P2P���(��p���[�h����)
	SND_SCENE_NUTMIXER,					//����
	//SND_SCENE_WORLDTRADE,				//���E����(GTC)
	SND_SCENE_EGG,						//�^�}�S�z��
	SND_SCENE_ENDING,					//�G���f�B���O

	//�T�u���(���C����ʂ���Ă΂��)
	SND_SCENE_SUB = 51,					//�X�^�[�g�i���o�[
	SND_SCENE_SUB_BAG = SND_SCENE_SUB,	//�o�b�O
	SND_SCENE_SUB_NAMEIN,				//���O����
	SND_SCENE_SUB_IMAGE,				//�C���[�W�N���b�v
	SND_SCENE_SUB_ZUKAN,				//�}��
	SND_SCENE_SUB_TOWNMAP,				//�^�E���}�b�v
	SND_SCENE_SUB_TRCARD,				//�g���[�i�[�J�[�h
	SND_SCENE_SUB_POKELIST,				//�|�P�������X�g
	SND_SCENE_SUB_DIG,					//���Ό@��
	SND_SCENE_SUB_CUSTOM,				//�J�X�^���{�[��
	SND_SCENE_SUB_FIRSTPOKE,			//�ŏ��̃|�P�����I��
	SND_SCENE_SUB_PST,					//�|�P�����X�e�[�^�X
	SND_SCENE_SUB_PMS,					//�ȈՉ�b
	SND_SCENE_SUB_CLIMAX,				//�N���C�}�b�N�X(�e���K���R)��ʐ؂�ւ��ł͂Ȃ��I
	SND_SCENE_SUB_SHIP,					//�D(�f��)��ʐ؂�ւ��ł͂Ȃ��I
	SND_SCENE_SUB_TRAIN,				//�����b�R��(�f��)��ʐ؂�ւ��ł͂Ȃ��I
	SND_SCENE_SUB_SLOT,					//�X���b�g
	SND_SCENE_SUB_FNOTE,				//�`���m�[�g

	//�V�[���֘A����
	//Snd_DataSetByScene( u8 scene, u16 no, int flag );	
	//Snd_LoadSeByScene( u8 scene );
};

//�T�E���h�n���h����`
enum{
	SND_HANDLE_FIELD = 0,									//�t�B�[���hBGM�T�E���h�n���h��
	SND_HANDLE_PMVOICE,										//�|�P���������T�E���h�n���h��
	SND_HANDLE_ME,											//ME�T�E���h�n���h��
	SND_HANDLE_SE_1,										//SE�T�E���h�n���h��
	SND_HANDLE_SE_2,										//SE�T�E���h�n���h��
	SND_HANDLE_SE_3,										//SE�T�E���h�n���h��
	SND_HANDLE_SE_4,										//SE�T�E���h�n���h��
	SND_HANDLE_BGM,											//�t�B�[���h�ȊO��BGM�n���h��
	SND_HANDLE_CHORUS,										//�R�[���X(������p)�n���h��

	SND_HANDLE_MAX,											//�ő吔
};

//�T���v�����O���[�g���Ⴂ�ƁA�L���v�`���@�\���g�����ɁA
//�������H���Ă��Ȃ��Ă��A���������Ȃ�̂Œ��ӁI
#define REVERB_SAMPLING_RATE	(16000)						//�T���v�����O���[�g(���o�[�u)
#define SAMPLING_RATE		(8000)							//�T���v�����O���[�g
//#define SAMPLING_RATE		(32000)//(8000)					//�T���v�����O���[�g
//#define SAMPLING_TIME		(2)								//�T���v�����O���鎞��
//#define WAVE_SAMPLE		(SAMPLING_RATE * SAMPLING_TIME)	//�T���v�����O�ɕK�v�ȃf�[�^��

#define WAVEOUT_CH_NORMAL	(14)							//�g�`�Ŏg�p����`�����l��NO
#define WAVEOUT_CH_CHORUS	(15)							//�g�`�Ŏg�p����`�����l��NO(�R�[���X)

//�t�F�[�h�C�����鎞�̊J�n���ʒ�`
#define BGM_FADEIN_START_VOL_MIN	(0)						//�t�F�[�h�C�����鎞�̊J�n����=0
#define BGM_FADEIN_START_VOL_NOW	(1)						//�t�F�[�h�C�����鎞�̊J�n����=���̂܂�

//����BGM��炷�܂ł̃E�F�C�g
#define BGM_NEXT_WAIT_CAVE_TIME	(15)						//���A�̏o����

//�t�F�[�h�C���t���[����
#define BGM_FADEIN_CYCLE_TIME	(30)					//���]�Ԃɏ���Ă��鎞�̃t�F�[�h�C��
#define BGM_FADEIN_RESTART_TIME	(30)					//�Q�[���I�[�o�[��ɍĊJ���鎞�̃t�F�[�h�C��

#define FILTER_SIZE				(8)							//�t�B���^�[�T�C�Y

#define SEQ_DP_TRADE			(SEQ_KOUKAN)				//�������BGM�i���o�[

//�T�E���hTCB�̒�`
enum{
	SND_TCB_PMVOICE_LENGTH = 0,				//�����Đ�����

	SND_TCB_MAX,							//�ő吔
};

//�}�Ӗ������
//#define SND_ZUKAN_PITCH_MIN		(-(64*12) * 1)		//�s�b�`�̍Œᐔ
#define SND_ZUKAN_PITCH_MIN		(-(64*12) * 2)			//�s�b�`�̍Œᐔ
#define SND_ZUKAN_PITCH_CHORUS	(20)					//�R�[���X�̂���s�b�`

//Snd_PMVoicePlayEx�̈����Ɏw��
#define PV_PTN_PARAM_NONE		(0x1ff)					//�����p�����[�^�Ȃ�

#define SND_BANK_CONTINUE		(0)						//�o���N���̂܂܌p��
#define SND_BANK_CHANGE			(1)						//�o���N�؂�ւ���

#define SND_HALF_PITCH			(64)					//�����̒l

#define SND_VCHAT_VOL_LV		(5)						//�{�C�X�`���b�g���ɉ��ʂ������郌�x��


//==============================================================================================
//
//	�\���̐錾
//
//==============================================================================================
//�g�`�f�[�^�Đ��ɕK�v�ȃf�[�^�\����
typedef struct{
	NNSSndWaveOutHandle*	handle;					//�g�`�Đ��n���h��
	NNSSndWaveFormat		format;					//�g�`�f�[�^�t�H�[�}�b�g
	const void*				dataaddr;				//�g�`�f�[�^�̐擪�A�h���X
	BOOL					loopFlag;				//���[�v�t���O
	int						loopStartSample;		//���[�v�J�n�T���v���ʒu
	int						samples;				//�g�`�f�[�^�̃T���v����
	int						sampleRate;				//�g�`�f�[�^�̃T���v�����O���[�g
	int						volume;					//����
	int						speed;					//�Đ��X�s�[�h
	int						pan;					//�p��(0-127)
}WAVEOUT_WORK;

typedef s16 smp_t;

//�L���v�`���G�t�F�N�g�̃R�[���o�b�N�\����
typedef struct EffectCallbackInfo{
    smp_t sample[ FILTER_SIZE-1 ][2];
} EffectCallbackInfo;


//==============================================================================================
//
//	extern�錾
//
//==============================================================================================

//--------------------------------------------------------------
/**
 * @brief	�V�[�P���X�A�[�J�C�u�ԍ���ݒ�
 *
 * @param	p		�T�E���h�n���h���̃A�h���X
 * @param	arc_no	�V�[�P���X�A�[�J�C�u�ԍ�
 * @param	index	�C���f�b�N�X
 *
 * @retval	none
 */
//--------------------------------------------------------------
extern void Snd_PlayerSetSeqArcNo( NNSSndHandle *p, int arc_no, int index );

//--------------------------------------------------------------
/**
 * @brief	�t�B�[���hBGM�Œ�t���O�Z�b�g(�Z�[�u�͂��Ȃ�)
 *
 * @param	flag	1=BGM�؂�ւ��Ȃ��A0E=BGM�؂�ւ��(�ʏ�)
 *
 * @retval	none
 */
//--------------------------------------------------------------
extern void Snd_CtrlBgmFlagSet( u8 flag );

//--------------------------------------------------------------
/**
 * @brief	�t�B�[���hBGM�Œ�t���O�`�F�b�N(�Z�[�u�͂��Ȃ�)
 *
 * @param	none
 *
 * @retval	"1=BGM�؂�ւ��Ȃ��A0E=BGM�؂�ւ��(�ʏ�)"
 */
//--------------------------------------------------------------
extern u8 Snd_CtrlBgmFlagCheck( void );

//--------------------------------------------------------------
/**
 * @brief	����BGM�i���o�[�X�V
 *
 * @param	no		�X�V����BGM�i���o�[
 *
 * @retval	none
 *
 * ����BGM�i���o�[(next_bgm_no)���N���A���Ă���I
 */
//--------------------------------------------------------------
extern void Snd_NowBgmNoSet( u16 no );

//--------------------------------------------------------------
/**
 * @brief	����BGM�i���o�[�擾
 *
 * @param	none
 *
 * @retval	"����BGM�i���o�["
 */
//--------------------------------------------------------------
extern u16 Snd_NowBgmNoGet();

//--------------------------------------------------------------
/**
 * @brief	����BGM�i���o�[�X�V
 *
 * @param	no		�X�V����BGM�i���o�[
 *
 * @retval	none
 */
//--------------------------------------------------------------
extern void Snd_NextBgmNoSet( u16 no );

//--------------------------------------------------------------
/**
 * @brief	����BGM�i���o�[�擾
 *
 * @param	none
 *
 * @retval	"����BGM�i���o�["
 */
//--------------------------------------------------------------
extern u16 Snd_NextBgmNoGet();

//--------------------------------------------------------------
/**
 * @brief	�]�[��BGM�i���o�[�Z�b�g
 *
 * @param	bgm		BGM�i���o�[
 *
 * @retval	none
 */
//--------------------------------------------------------------
extern void Snd_ZoneBgmSet( u16 bgm );


//==============================================================================================
//
//	�V�[�P���X�֘A
//
//==============================================================================================

//--------------------------------------------------------------
/**
 * @brief	�V�[�P���X���Đ�(�v���C���[�ԍ��w��)(�ʏ�g�p���Ȃ��I)
 *
 * @param	handle_no	�T�E���h�n���h���i���o�[
 * @param	player_no	�v���C���[�i���o�[
 * @param	no			BGM�i���o�[
 *
 * @retval	"�Đ�����=TRUE�A���s=FALSE"
 *
 * �Đ��ɐ�������ƁA�T�E���h�n���h���ɃV�[�P���X�����т����܂��B 
 *
 * �V�[�P���X�f�[�^���v���C���[�q�[�v�Ń��[�h���鎞�́A
 * �e�ʂ�����Ȃ��ƍĐ����s����I
 */
//--------------------------------------------------------------
extern BOOL Snd_ArcPlayerStartSeqEx( int handle_no, int player_no, u16 no );


//==============================================================================================
//
//	�v���C���[�֘A
//
//==============================================================================================

//--------------------------------------------------------------
/**
 * @brief	�Đ����̃V�[�P���X�̐���Ԃ�
 *
 * @param	player_no	�v���C���[�ԍ�
 *
 * @retval	"�Đ����̃V�[�P���X�̐�"
 */
//--------------------------------------------------------------
extern int Snd_PlayerCountPlayingSeq( int player_no );

//--------------------------------------------------------------
/**
 * @brief	�w��v���C���[�̃V�[�P���X�ő哯���Đ�����ݒ�(���d�Đ������������Ɏg�p�I)
 *
 * @param	player_no	�v���C���[�ԍ�
 * @param	no			�V�[�P���X�ő哯���Đ���
 *
 * @retval	"�ύX�O�̃V�[�P���X�ő哯���Đ���"
 *
 * PLAYER_FIELD	: �t�B�[���hBGM
 * PLAYER_ME 	: ME
 * PLAYER_SE_1 	: ���ʉ�
 * PLAYER_SE_2 	: ���ʉ�
 * PLAYER_SE_3 	: ���ʉ�
 * PLAYER_SE_4 	: ���ʉ�
 * PLAYER_PV	: �|�P��������
 * PLAYER_VOICE	: ����
 * PLAYER_BGM	: �t�B�[���h�ȊOBGM
 *
 * �g�p��́A�K�����̐ݒ�ɖ߂��悤�ɂ��ĉ������I
 */
//--------------------------------------------------------------
//extern u8 Snd_PlayerSetPlayableSeqCount( int player_no, int no );

//--------------------------------------------------------------
/**
 * @brief	�V�[�P���X�i���o�[����v���C���[�i���o�[�擾
 *
 * @param	no		�V�[�P���X�i���o�[
 *
 * @retval	"�v���C���[�i���o�["
 */
//--------------------------------------------------------------
extern u8 Snd_GetPlayerNo( u16 no );

//--------------------------------------------------------------
/**
 * @brief	�T�E���h�n���h������V�[�P���X�i���o�[���擾
 *
 * @param	p			�T�E���h�n���h���̃A�h���X
 *
 * @retval	"�V�[�P���X�i���o�["
 */
//--------------------------------------------------------------
extern int Snd_GetSeqNo( NNSSndHandle *p );


//==============================================================================================
//
//	�o���N�֘A
//
//==============================================================================================

//--------------------------------------------------------------
/**
 * @brief	�o���N���\���̂̃A�h���X���擾
 *
 * @param	no		�V�[�P���X�i���o�[
 *
 * @retval	"�o���N���\���̂̃A�h���X"
 */
//--------------------------------------------------------------
extern const NNSSndArcBankInfo* Snd_GetBankInfo( int no );

//--------------------------------------------------------------
/**
 * @brief	�V�[�P���X�i���o�[����o���N�i���o�[�擾
 *
 * @param	no		�V�[�P���X�i���o�[
 *
 * @retval	"0=�G���[�A0�ȊO=�o���N�i���o�["
 */
//--------------------------------------------------------------
extern u16 Snd_GetBankNo( int no );


//==============================================================================================
//
//	�T�E���h�f�[�^�̃��[�h�֘A
//
//==============================================================================================

//--------------------------------------------------------------
/**
 * @brief	�V�[���Z�b�g
 *
 * @param	scene	�V�[��
 *
 * @retval	none
 */
//--------------------------------------------------------------
extern void Snd_SceneSet( u8 scene );

//--------------------------------------------------------------
/**
 * @brief	�V�[�����L�[�ɂ��āASE�f�[�^�����[�h(�V�[����`��snd_tool.h�Q��)
 *
 * @param	scene		�V�[��
 *
 * @retval	"����=TRUE�A���s=FALSE"
 */
//--------------------------------------------------------------
extern int Snd_LoadSeByScene( u8 scene );

//--------------------------------------------------------------
/**
 * @brief	�V�[�����L�[�ɂ��āA�T�E���h�f�[�^�Z�b�g
 *
 * @param	scene	�V�[��
 * @param	no		�V�[�P���X�i���o�[
 * @param	flag	"���g�p"
 *
 * @retval	"0=�������Ȃ��A1=�f�[�^���[�h"
 */
//--------------------------------------------------------------
extern BOOL Snd_DataSetByScene( u8 scene, u16 no, int flag );

//--------------------------------------------------------------
/**
 * @brief	�t�B�[���h�f�[�^�Z�b�g�̋��ʏ���(snd_tool.c,snd_play.c)
 *
 * @param	no			�V�[�P���X�i���o�[
 * @param	old_bank_no	�t�B�[���h�̃o���N�i���o�[
 *
 * @retval	none
 */
//--------------------------------------------------------------
extern void Snd_FieldDataSetSub( u16 no, u16 old_bank_no );

//--------------------------------------------------------------
/**
 * @brief	�����Ȃɐ؂�ւ�鎞�̃T�E���h�f�[�^�Z�b�g
 *
 * @param	no		�V�[�P���X�i���o�[
 *
 * @retval	none
 *
 * FIELD����Ă΂�邱�Ƃ�O��Ƃ��Ă���I
 */
//--------------------------------------------------------------
extern void Snd_EyeBgmSet( u16 no );

//--------------------------------------------------------------
/**
 * @brief	�������[�h���Ă��Ȃ���Ԃɂ���(�T�E���h�e�X�g�݂̂Ŏg��)
 *
 * @param	none
 *
 * @retval	none
 */
//--------------------------------------------------------------
extern void Snd_HeapStateClear(void);


//==============================================================================================
//
//	�q�[�v�֘A
//
//==============================================================================================

//--------------------------------------------------------------
/**
 * @brief	BGM�̌��̃f�[�^������
 *
 * @param	none
 *
 * @retval	none
 */
//--------------------------------------------------------------
extern void Snd_DeleteHeapAfterBgm( void );

//--------------------------------------------------------------
/**
 * @brief	�K�w���x�����擾
 *
 * @param	wk		SND_WORK�^�̃A�h���X
 * @param	type	�K�w���x�����(snd_tool.h�Q��)
 *
 * @retval	"�K�w���x��"
 */
//--------------------------------------------------------------
extern int Snd_GetHeapSaveLv( int type );


//==============================================================================================
//
//	�V�[�P���X�֘A
//
//==============================================================================================

//--------------------------------------------------------------
/**
 * @brief	�V�[�P���X���ꎞ��~�܂��͍ĊJ���܂��B 
 *
 * @param	player	�v���C���[�i���o�[(sound_data.sadl�Q��)
 * @param	flag	TRUE=�ꎞ��~�AFALSE=�ĊJ
 *
 * @retval	none
 *
 * �T�E���h�n���h���������̏ꍇ�́A�������܂���B 
 * ��Ԃ��ς��Ȃ��ꍇ�A�Ⴆ�΁A���łɈꎞ��~��Ԃ̎��Ɉꎞ��~���s���Ă��A�������܂���B 
 *
 * ����
 * �ꎞ��~���s���ƁA�������̉��͋����I�ɒ�~�������܂��B
 * �ĊJ���s���Ă��A�������̉�����������Đ�����邱�Ƃ͂���܂���̂Œ��ӂ��Ă��������B
 * �ĊJ��́A���̃m�[�g�I�����特����n�߂܂��B 
 */
//--------------------------------------------------------------
extern void Snd_PlayerPause( u8 player, BOOL flag );

//--------------------------------------------------------------
/**
 * @brief	�S�Ẵ|�[�Y���Ă��邩�t���O�̃N���A
 *
 * @param	none
 *
 * @retval	none
 *
 * �퓬�ŃQ�[���I�[�o�[�ɂȂ��āA�|�P�Z���ɖ߂�Ƃ��ȂǂɁA
 * FieldDataSet���ĂԑO�ɁA�|�[�Y�t���O���N���A���Ȃ��Ƃ����Ȃ��I
 */
//--------------------------------------------------------------
extern void Snd_PauseClearAll();	//Snd_GameOverSet����ĂԂ悤�ɕύX

//--------------------------------------------------------------
/**
 * @brief	�V�[�P���X�̃{�����[�������X�ɕύX����
 *
 * @param	handle_no	�T�E���h�n���h���i���o�[
 * @param	vol			�{�����[��
 * @param	frame		�t���[��
 *
 * @retval	none
 *
 * frames��0�̎��A�����Ɍ��݂̃{�����[���l���X�V����܂��B
 * ���Ƃ��΁A���݂̃{�����[���l�Ƃ͖��֌W�ɁA
 * �{�����[��������l����A�ʂ̒l�Ɏ��ԕω����������ꍇ�́A
 * �܂��Aframes��0�Ƃ��Ă��̊֐����Ăт����āA���݂̃{�����[���l���X�V������A
 * �Ăѓ����֐��ŁA�ڕW�Ƃ���{�����[���l���w�肵�܂��B 
 *
 * �V�[�P���X�X�^�[�g����̃{�����[���l��0�ŁA���� NNS_SndMain�֐��ŁA127 �ɕω����܂��B
 * ���̂��߁A�V�[�P���X�X�^�[�g����ɂ��̊֐����Ăт����ƁA
 * �{�����[��0���珙�X�Ɏw��̃{�����[���֕ω�����悤�ȁA�t�F�[�h�C�����ʂ������܂��B 
 *
 * ���̃{�����[���l�́A NNS_SndPlayerSetVolume�֐��̒l�Ƃ́A�Ɨ����Č��ʂ𔭊����A
 * �݂��ɏd�ˍ��킳��܂��B�������A�t�F�[�h�A�E�g���́A�����Őݒ肵���l�͖�������܂��B 
 */
//--------------------------------------------------------------
extern void Snd_PlayerMoveVolume( int handle_no, int vol, int frame );

//--------------------------------------------------------------
/**
 * @brief	�S�ẴV�[�P���X�̃{�����[����ύX����
 *
 * @param	p		�T�E���h�n���h���̃A�h���X
 *
 * @retval	none
 */
//--------------------------------------------------------------
extern void Snd_AllPlayerMoveVolume( int vol, int frame );

//--------------------------------------------------------------
/**
 * @brief	�V�[�P���X�̏����{�����[���ݒ�
 *
 * @param	handle_no	�T�E���h�n���h���i���o�[
 * @param	vol			�{�����[��(0-127)
 *
 * @retval	none
 *
 * �T�E���h�n���h���������̏ꍇ�́A�������܂���B 
 *
 * �{�����[���̃f�t�H���g�l�́A�ő��127�ł��B
 * ���̒l�̉e���̓V�[�P���X�S�̂ɂ�����܂��B
 *
 * ���̊֐��́ANNS_SndArcPlayerStartSeq*�֐��� NNS_SndArcPlayerStartSeqArc*�֐�����
 * �Ăт�����Ă��܂��B�ēx�A���̊֐����Ăт����ƁA�ݒ肵���l���㏑������܂��B
 * �㏑���������Ȃ��ꍇ�́A NNS_SndPlayerSetVolume�֐��Ȃǂ��g���Ă��������B
 */
//--------------------------------------------------------------
extern void Snd_PlayerSetInitialVolume( int handle_no, int vol );

//--------------------------------------------------------------
/**
 * @brief	�{�C�X�`���b�g���̉��ʑ���
 *
 * @param	seq_no		�V�[�P���X�i���o�[
 * @param	handle_no	�n���h���i���o�[
 *
 * @retval	none
 */
//--------------------------------------------------------------
extern void Snd_VChatVolSet( int seq_no, int handle_no );

//--------------------------------------------------------------
/**
 * @brief	�V�[�P���X�̏����{�����[���ݒ�(�V�[�P���X�i���o�[�w���)
 *
 * @param	no		�V�[�P���X�i���o�[
 * @param	vol		�{�����[��(0-127)
 *
 * @retval	none
 *
 * �T�E���h�n���h���������̏ꍇ�́A�������܂���B 
 *
 * �{�����[���̃f�t�H���g�l�́A�ő��127�ł��B
 * ���̒l�̉e���̓V�[�P���X�S�̂ɂ�����܂��B
 *
 * ���̊֐��́ANNS_SndArcPlayerStartSeq*�֐��� NNS_SndArcPlayerStartSeqArc*�֐�����
 * �Ăт�����Ă��܂��B�ēx�A���̊֐����Ăт����ƁA�ݒ肵���l���㏑������܂��B
 * �㏑���������Ȃ��ꍇ�́A NNS_SndPlayerSetVolume�֐��Ȃǂ��g���Ă��������B
 *
 * ��
 * Snd_PMVoicePlay( no );
 * Snd_PlayerSetInitialVolume( handle_no. 30 );
 * �{�����[��30�ōĐ������
 *
 * ���̂��ƁA
 * Snd_PMVoicePlay( no );
 * �f�t�H���g�̒l127�ōĐ������(���ɖ߂��Ă���)
 *
 * �t�ɂ����ƁA��Ƀ{�����[��30�ɂ�����������A
 * Snd_PlayerSetInitialVolume( handle_no. 30 );
 * �𖈉�Z�b�g����
 */
//--------------------------------------------------------------
extern void Snd_PlayerSetInitialVolumeBySeqNo( u16 no, int vol );

//--------------------------------------------------------------
/**
 * @brief	�g���b�N�����ύX
 *
 * @param	handle_no	�T�E���h�n���h���i���o�[
 * @param	bitmask		�g���b�N�r�b�g�}�X�N
 * @param	pitch		�����ω��̒l(-32768�`32767)
 *
 * @retval	none
 *
 * pitch�͐��̒l�ō������ցA���̒l�ŒႢ���֕ω����܂��B 
 * �}64�ł��傤�ǔ����ω����܂��B�i�ĂԂ��тɌ��ʂ��ݐς����킯�ł͂���܂���)
 */
//--------------------------------------------------------------
extern void Snd_PlayerSetTrackPitch( int handle_no, u16 bitmask, int pitch );

//--------------------------------------------------------------
/**
 * @brief	�g���b�N�����ύX(�V�[�P���X�i���o�[�w���)
 *
 * @param	no			�V�[�P���X�i���o�[
 * @param	bitmask		�g���b�N�r�b�g�}�X�N
 * @param	pitch		�����ω��̒l(-32768�`32767)
 *
 * @retval	none
 *
 * pitch�͐��̒l�ō������ցA���̒l�ŒႢ���֕ω����܂��B 
 * �}64�ł��傤�ǔ����ω����܂��B�i�ĂԂ��тɌ��ʂ��ݐς����킯�ł͂���܂���)
 */
//--------------------------------------------------------------
extern void Snd_PlayerSetTrackPitchBySeqNo( u16 no, u16 bitmask, int pitch );

//--------------------------------------------------------------
/**
 * @brief	�g���b�N�p���ύX
 *
 * @param	handle_no	�T�E���h�n���h���i���o�[
 * @param	bitmask		�g���b�N�r�b�g�}�X�N
 * @param	pan			�p���ω��̒l(-128�`127)
 *
 * @retval	none
 */
//--------------------------------------------------------------
extern void Snd_PlayerSetTrackPan( int handle_no, u16 bitmask, int pan );


//==============================================================================================
//
//	�}�C�N�֘A
//
//==============================================================================================
  
//--------------------------------------------------------------
/**
 * @brief	�^���J�n
 *
 * @param	p		MICAutoParam�^�̃|�C���^
 *
 * @retval	"MIC_RESULT_SUCCESS		����������Ɋ���"
 * @retval	"����ȊO				���炩�̌����Ŏ��s"
 */
//--------------------------------------------------------------
extern MICResult Snd_MicStartAutoSampling( MICAutoParam* p );

//--------------------------------------------------------------
/**
 * @brief	�^����~
 *
 * @param	none
 *
 * @retval	"MIC_RESULT_SUCCESS		����������Ɋ���"
 * @retval	"����ȊO				���炩�̌����Ŏ��s"
 */
//--------------------------------------------------------------
extern MICResult Snd_MicStopAutoSampling(void);


//--------------------------------------------------------------
/**
 * @brief	�蓮�^��
 * @param	type      �T���v�����O���[�g�̃^�C�v
 * @param	heap      �L�^�̈�
 * @param	callback  �L�^�����ۂ̃R�[���o�b�N
 * @param	arg       �R�[���o�b�N�ɓn�������|�C���^
 * @retval	"MIC_RESULT_SUCCESS		����������Ɋ���"
 * @retval	"����ȊO				���炩�̌����Ŏ��s"
 */
//--------------------------------------------------------------
extern MICResult Snd_MicManualSampling(MICSamplingType type ,void* heap,MICCallback callback,void* arg);

//==============================================================================================
//
//	�g�`�Đ��֘A
//
//==============================================================================================

//--------------------------------------------------------------
/**
 * @brief	�g�`�n���h���̃A�h���X���擾
 *
 * @param	no		�g�p����`�����l���i���o�[
 *
 * @retval	"�g�`�n���h���̃A�h���X"
 *
 * BGM		NNSSndHandle
 * �g�`		NNSSndWaveOutHandle
 * �n���h���̃^�C�v���Ⴄ�̂Œ��ӁI
 */
//--------------------------------------------------------------
extern NNSSndWaveOutHandle * Snd_WaveOutHandleGet( u32 no );

//--------------------------------------------------------------
/**
 * @brief	�g�`�Đ��p�Ƀ`�����l�����m�ۂ���
 *
 * @param	no		�g�p����`�����l���i���o�[
 *
 * @retval	BOOL	TRUE=�����AFALSE=���s
 */
//--------------------------------------------------------------
extern BOOL Snd_WaveOutAllocChannel( u32 no );
 
//--------------------------------------------------------------
/**
 * @brief	�g�`�Đ��p�̃`�����l�����������
 *
 * @param	no		�g�p����`�����l���i���o�[
 *
 * @retval	none
 */
//--------------------------------------------------------------
extern void Snd_WaveOutFreeChannel( u32 no );

//--------------------------------------------------------------
/**
 * @brief	�g�`�Đ�
 *
 * @param	p		WAVEOUT_WORK�^�̃|�C���^
 * @param	ch		�g�p����`�����l���i���o�[(�ʏ�́AWAVEOUT_CH_NORMAL)
 *
 * @retval	BOOL	TRUE=�����AFALSE=���s
 */
//--------------------------------------------------------------
BOOL Snd_WaveOutStart( WAVEOUT_WORK *p, u32 ch );

//--------------------------------------------------------------
/**
 * @brief	�g�`��~
 *
 * @param	no		�g�p����`�����l���i���o�[
 *
 * @retval	none
 */
//--------------------------------------------------------------
void Snd_WaveOutStop( u32 no );

//--------------------------------------------------------------
/**
 * @brief	�g�`�Đ������`�F�b�N
 *
 * @param	no		�g�p����`�����l���i���o�[
 *
 * @retval	BOOL	TRUE=�Đ����AFALSE=�Đ����łȂ�
 */
//--------------------------------------------------------------
extern BOOL Snd_WaveOutIsPlaying( u32 no );

//--------------------------------------------------------------
/**
 * @brief	�g�`�Đ���PAN�ݒ�
 *
 * @param	no		�g�p����`�����l���i���o�[
 * @param	pan		�p���̒l(0-127�A64��center)
 *
 * @retval	none
 */
//--------------------------------------------------------------
extern void Snd_WaveOutSetPan( u32 no, u8 pan );

//--------------------------------------------------------------
/**
 * @brief	�g�`�Đ��̍Đ��X�s�[�h�ݒ�
 *
 * @param	no		�g�p����`�����l���i���o�[
 * @param	spd		�Đ��X�s�[�h
 *
 * @retval	none
 *
 * 2����1�{��	(32768 / 2)
 * 1�{��		(32768)
 * 2�{��		(32768 * 2)
 * 3�{��		(32768 * 3)
 */
//--------------------------------------------------------------
extern void Snd_WaveOutSetSpeed( u32 no, u32 spd );
 
//--------------------------------------------------------------
/**
 * @brief	�g�`�Đ��̃{�����[���ύX
 *
 * @param	no		�g�p����`�����l���i���o�[
 * @param	vol		�{�����[���l(0-127)
 *
 * @retval	none
 */
//--------------------------------------------------------------
extern void Snd_WaveOutSetVolume( u32 no, int vol );
 

//==============================================================================================
//
//	�g�`�t�Đ��֘A(�|�P�����̖�����p)
//
//==============================================================================================

//--------------------------------------------------------------
/**
 * @brief	�t�Đ��̃|�P�����������Đ�
 *
 * @param	no		�|�P�����i���o�[
 * @param	vol		�{�����[��(0-127)
 * @param	pan		�p��(0-127)
 * @param	ch		�g�p����`�����l���i���o�[(�ʏ�́AWAVEOUT_CH_NORMAL)
 * @param	heap_id	�q�[�vID
 *
 * @retval	BOOL	TRUE=�����AFALSE=���s
 *
 * �����ŋt�Đ��p�̃o�b�t�@���m�ۂ��Ă��܂��B
 *
 * Snd_WaveOutStopReverse(...)���Ă�ŁA
 * �o�b�t�@���J�����Ă��������B
 *
 * �|�P�����i���o�[�Ɩ����̔g�`�A�[�J�C�u�i���o�[�������ɂȂ�悤�ɂ���I
 */
//--------------------------------------------------------------
extern BOOL Snd_WaveOutStartReverse( u16 no, int vol, int pan, u32 ch, int heap_id );

//--------------------------------------------------------------
/**
 * @brief	�t�Đ��̃|�P�����������~���ăo�b�t�@���J������
 *
 * @param	no		�g�p����`�����l���i���o�[
 *
 * @retval	none
 */
//--------------------------------------------------------------
extern void Snd_WaveOutStopReverse( u32 no );


//==============================================================================================
//
//	�L���v�`���֘A
//
//==============================================================================================

//--------------------------------------------------------------
/**
 * @brief	�L���v�`���[�X���b�h���N��(�Ƃ肠�����D��x�͌Œ�)
 *
 * @param	none
 *
 * @retval	none
 *
 * �L���v�`���[�X���b�h���N�����Ă����ƁA
 * �L���v�`���[������IRQ�n���h���ł͂Ȃ��A
 * �L���v�`���[�X���b�h�ŏ��������悤�ɂȂ�܂��B 
 *
 * �X���b�h�̗D��xthreadPrio�́A
 * �ʏ�A�X�g���[���X���b�h���������ݒ肵�܂��B
 * �������x���ƁA����ȍĐ����s���Ȃ��Ȃ�܂��̂ŁA���ӂ��Ă��������B 
 */
//--------------------------------------------------------------
extern void Snd_CaptureCreateThread(void);
  
//--------------------------------------------------------------
/**
 * @brief	�L���v�`�������s�����擾
 *
 * @param	none
 *
 * @retval	"TRUE=���s���AFALSE=���s���Ă��Ȃ�"
 */
//--------------------------------------------------------------
extern BOOL Snd_CaptureIsActive(void);

//--------------------------------------------------------------
/**
 * @brief	���s���̃L���v�`���^�C�v���擾
 *
 * @param	none
 *
 * @retval	"NNS_SND_CAPTURE_TYPE_REVERB = ���o�[�u"
 * @retval	"NNS_SND_CAPTURE_TYPE_EFFECT = �G�t�F�N�g"
 * @retval	"NNS_SND_CAPTURE_TYPE_SAMPLING = �T���v�����O"
 *
 * �L���v�`���[�����s���̎��̂݌Ăт������Ƃ��ł��܂��B
 * �L���v�`���[�����s�����ǂ����𒲂ׂ邽�߂ɂ́A NNS_SndCaptureIsActive�֐����Ăт����܂��B 
 */
//--------------------------------------------------------------
extern NNSSndCaptureType Snd_CaptureGetCaptureType(void);
 
//--------------------------------------------------------------
/**
 * @brief	�o�̓G�t�F�N�g������ύX
 *
 * @param	none
 *
 * @retval	none
 *
 * NNS_SND_CAPTURE_OUTPUT_EFFECT_NORMAL		�����������܂���(�ʏ�̃X�e���I���[�h)
 *
 * NNS_SND_CAPTURE_OUTPUT_EFFECT_MONO		���m�������[�h 
 *
 * NNS_SND_CAPTURE_OUTPUT_EFFECT_SURROUND	�T���E���h���[�h 
 * DS�X�s�[�J�[����o�͂������Ƃ��ɁA
 * �X�s�[�J�[�ʒu���L�����ĉ�����������悤�ɂ���G�t�F�N�g�������܂��B
 *
 * NNS_SND_CAPTURE_OUTPUT_EFFECT_HEADPHONE	�w�b�h�t�H�����[�h 
 * �w�b�h�t�H���g�p���ɁA���̕��S���y������G�t�F�N�g�������܂��B
 */
//--------------------------------------------------------------
extern void Snd_CaptureChangeOutputEffect( NNSSndCaptureOutputEffectType type );


//==============================================================================================
//
//	�L���v�`���@���o�[�u
//
//==============================================================================================

//--------------------------------------------------------------
/**
 * @brief	�o�̓G�t�F�N�g�������J�n
 *
 * @param	none
 *
 * @retval	none
 *
 * �L���v�`���[�@�\���g���ă~�L�T�[�o�͂��L���v�`�����A
 * �R�[���o�b�N�֐��ŃG�t�F�N�g�������s������A�ŏI�����Ƃ��ďo�͂��܂��B
 * �G�t�F�N�g���쒆�́A16�`�����l������2�`�����l���i�`�����l��1�y�у`�����l��3�j������܂��B
 * �`�����l��1�܂��̓`�����l��3���A�V�[�P���X�ɂ���Ďg�p���̏ꍇ�A
 * �������̉��͋����I�ɒ�~�������܂��B 
 *
 * NNS_SND_CAPTURE_OUTPUT_EFFECT_NORMAL		�����������܂���(�ʏ�̃X�e���I���[�h)
 *
 * NNS_SND_CAPTURE_OUTPUT_EFFECT_MONO		���m�������[�h 
 *
 * NNS_SND_CAPTURE_OUTPUT_EFFECT_SURROUND	�T���E���h���[�h 
 * DS�X�s�[�J�[����o�͂������Ƃ��ɁA
 * �X�s�[�J�[�ʒu���L�����ĉ�����������悤�ɂ���G�t�F�N�g�������܂��B
 *
 * NNS_SND_CAPTURE_OUTPUT_EFFECT_HEADPHONE	�w�b�h�t�H�����[�h 
 * �w�b�h�t�H���g�p���ɁA���̕��S���y������G�t�F�N�g�������܂��B
 */
//--------------------------------------------------------------
extern void Snd_CaptureStartOutputEffect( NNSSndCaptureOutputEffectType type );

//--------------------------------------------------------------
/**
 * @brief	���o�[�u�@�J�n
 *
 * @param	vol		���o�[�u�����̃{�����[��(0-63)
 *
 * @retval	BOOL	TRUE=�����AFALSE=���s
 *
 * �������Đ����Ȃ��炱�̊֐����Ăт����ƁA�Đ�����鉹���r�؂�܂��B 
 *
 * �`�����l��1,3���g�p����̂Œ��ӁI
 */
//--------------------------------------------------------------
extern BOOL Snd_CaptureStartReverb( int vol );

//--------------------------------------------------------------
/**
 * @brief	���o�[�u�@�I��
 *
 * @param	frame	�t���[����
 *
 * @retval	none
 */
//--------------------------------------------------------------
extern void Snd_CaptureStopReverb( int frame );

//--------------------------------------------------------------
/**
 * @brief	���o�[�u�@�{�����[���ύX
 *
 * @param	vol		���o�[�u�����̃{�����[��(0-63)
 * @param	frame	�t���[����
 *
 * @retval	none
 *
 * frame�Ŏw�肵���t���[�����ŁA���X�Ɍ��݂̃{�����[���l����A
 * vol�Ŏw�肵���{�����[���l�֕ω����܂��B  
 *
 * ���o�[�u�����삵�Ă��Ȃ��ꍇ�́A�������܂���B 
 */
//--------------------------------------------------------------
extern void Snd_CaptureReverbVol( int vol, int frame );

//--------------------------------------------------------------
/**
 * @brief	�G�t�F�N�g�J�n
 *
 * @param	none
 *
 * @retval	BOOL	TRUE=�����AFALSE=���s
 *
 * �`�����l��1,3���g�p����̂Œ��ӁI
 */
//--------------------------------------------------------------
extern BOOL Snd_CaptureStartEffect(void);

//--------------------------------------------------------------
/**
 * @brief	�G�t�F�N�g��~
 *
 * @param	none
 *
 * @retval	none
 */
//--------------------------------------------------------------
extern void Snd_CaptureStopEffect(void);

//--------------------------------------------------------------
/**
 * @brief	�G�t�F�N�g���x���̑���
 *
 * @param	level	���x��(0-8)
 *
 * @retval	none
 */
//--------------------------------------------------------------
extern void Snd_CaptureEffectLevel( int level );


//==============================================================================================
//
//	�g���b�N����
//
//==============================================================================================

//--------------------------------------------------------------
/**
 * @brief	�g���b�N�~���[�g
 *
 * @param	handle_no	�T�E���h�n���h���i���o�[
 * @param	bitmask		�g���b�N�r�b�g�}�X�N
 * @param	flag		TRUE=�~���[�g�AFALSE=����
 *
 * @retval	none
 *
 * trackBitMask�ŁA�ݒ肷��g���b�N���w�肵�܂��B
 * ���ʃr�b�g���珇�ɁA�g���b�N0�A�g���b�N1�A�g���b�N2�A�A�A��\���A
 * �r�b�g�������Ă���g���b�N�S�Ăɑ΂��āA�~���[�g�̐ݒ��ύX���܂��B
 * �Ⴆ�΁A�g���b�N2�ƃg���b�N5�̃~���[�g�ݒ��ύX�������ꍇ�́A 
 * (1 << 2) | (1 << 5) ���Ȃ킿�A0x0024 �Ƃ��܂��B 
 */
//--------------------------------------------------------------
extern void Snd_PlayerSetTrackMute( int handle_no, u16 bitmask, BOOL flag );

//--------------------------------------------------------------
/**
 * @brief	�g���b�N�{�����[���ύX
 *
 * @param	p			�T�E���h�n���h���̃A�h���X
 * @param	bitmask		�g���b�N�r�b�g�}�X�N
 * @param	vol			�{�����[��
 *
 * @retval	none
 */
//--------------------------------------------------------------
extern void Snd_PlayerSetTrackVolume( NNSSndHandle *p, u16 bitmask, int vol );

//--------------------------------------------------------------
/**
 * @brief	�e���|�ύX
 *
 * @param	handle_no	�T�E���h�n���h���i���o�[
 * @param	tempo		�{��(256=1�{)
 *
 * @retval	none
 */
//--------------------------------------------------------------
extern void Snd_PlayerSetTempoRatio( int no, int tempo );


//==============================================================================================
//
//	���̑��֘A
//
//==============================================================================================

//--------------------------------------------------------------
/**
 * @brief	���m�����t���O��ύX
 *
 * @param	flag	TRUE=���m�����AFALSE=�X�e���I
 *
 * @retval	none
 *
 * �f�t�H���g�́AFALSE�ł��B 
 * ���m�����t���O��L���ɂ���ƁA�p���̐ݒ�l�𖳎����āA
 * �S�Ă̔����������̒�ʂōs���܂��B 
 */
//--------------------------------------------------------------
extern void Snd_SetMonoFlag( BOOL flag );

//--------------------------------------------------------------
/**
 * @brief	�t�F�[�h�J�E���^�[�Z�b�g(fade_count�ɒl�Z�b�g)
 *
 * @param	frame		�t���[����
 *
 * @retval	none
 */
//--------------------------------------------------------------
extern void Snd_FadeCountSet( int frame );

//--------------------------------------------------------------
/**
 * @brief	����BGM��炷�܂ł̃E�F�C�g�Z�b�g
 *
 * @param	frame		�t���[����
 *
 * @retval	none
 */
//--------------------------------------------------------------
extern void Snd_NextWaitSet( int frame );

//--------------------------------------------------------------
/**
 * @brief	����BGM��炷�܂ł̃E�F�C�g�`�F�b�N(�J�E���^�[�����炵�Ă��܂�)
 *
 * @param	none
 *
 * @retval	"0=�I���A0�ȊO=�J�E���^�[�l"
 */
//--------------------------------------------------------------
extern int Snd_NextWaitCheck();

//--------------------------------------------------------------
/**
 * @brief	�}�X�^�[�{�����[���ݒ�(�f�t�H���g��127)
 *
 * @param	vol		�{�����[��(0-127)
 *
 * @retval	none
 */
//--------------------------------------------------------------
//extern void Snd_SetMasterVolume( int vol );

//--------------------------------------------------------------
/**
 * @brief	�g�`�i�[�o�b�t�@�̃A�h���X�擾
 *
 * @param	none
 *
 * @retval	none
 */
//--------------------------------------------------------------
extern void* Snd_GetWaveBufAdrs(void);

//--------------------------------------------------------------
/**
 * @brief	�v���C���[�q�[�v���쐬(snd_test.c�ł̂ݎg�p)
 *
 * @param	player_no	�v���C���[�i���o�[
 * @param	size		�v���C���[�q�[�v�T�C�Y
 *
 * @retval	"TRUE=�����AFALSE=���s"
 */
//--------------------------------------------------------------
extern BOOL Snd_PlayerHeapCreate( int player_no, u32 size );


//==============================================================================================
//
//	�t�B�[���h����؂�ւ�鎞�ɌĂԕK�v������폜�֐�
//
//	�P�j�퓬�ɓ���
//	�Q�j�����ɓ���
//	�R�j�ŃQ�[���I�[�o�[
//	�S�j���]�Ԃɏ������
//	�T�j�g��肵����
//	���ɂ͉������邩�H�H
//
//==============================================================================================


//==============================================================================================
//
//	fld_bgm�Ŏg�p����֐�
//
//==============================================================================================

//--------------------------------------------------------------
/**
 * @brief	�o���N�؂�ւ��邩�t���O�Z�b�g
 *
 * @param	no		SND_BANK_CONTINUE,SND_BANK_CHANGE
 *
 * @retval	none
 */
//--------------------------------------------------------------
extern void Snd_BankFlagSet( int no );

//--------------------------------------------------------------
/**
 * @brief	�o���N�؂�ւ��邩�t���O�擾
 *
 * @param	none
 *
 * @retval	"SND_BANK_CONTINUE,SND_BANK_CHANGE"
 */
//--------------------------------------------------------------
extern u8 Snd_BankFlagGet();

//--------------------------------------------------------------
/**
 * @brief	�t�F�[�h�A�E�g �� BGM�Đ�
 *
 * @param	scene		�V�[��(���)�i���o�[
 * @param	no			�V�[�P���X�i���o�[
 * @param	frame		�t���[����
 * @param	next_wait	����BGM��炷�܂ł̃E�F�C�g
 * @param	flag		0=���A1=��
 * @param	adrs		�t�F�[�h�f�[�^�̃A�h���X
 *
 * @retval	"0=�������Ȃ��A1=�J�n"
 *
 * �t�F�[�h�J�E���^�[���Z�b�g���Ă��܂�
 */
//--------------------------------------------------------------
extern BOOL Snd_FadeOutNextPlaySet(u8 scene, u16 no,int frame,int next_wait,u8 flag, void* adrs);

//--------------------------------------------------------------
/**
 * @brief	�t�F�[�h�A�E�g �� BGM�t�F�[�h�C��(�V�[����`��snd_tool.h�Q��)
 *
 * @param	scene		�V�[��(���)�i���o�[
 * @param	no			�V�[�P���X�i���o�[
 * @param	frame		�t���[����
 * @param	next_wait	����BGM��炷�܂ł̃E�F�C�g
 * @param	next_frame	����BGM�̃t�F�[�h�C���t���[����
 * @param	flag		0=���A1=��A0xff=����(�������Ȃ�)
 * @param	adrs		�t�F�[�h�f�[�^�̃A�h���X
 *
 * @retval	"0=�������Ȃ��A1=�J�n"
 *
 * �t�F�[�h�J�E���^�[���Z�b�g���Ă��܂�
 */
//--------------------------------------------------------------
extern BOOL Snd_FadeOutNextFadeInSet( u8 scene, u16 no, int frame, int next_wait, int next_frame, u8 flag, void* adrs );

//--------------------------------------------------------------
/**
 * @brief	�g���b�N�t�F�[�h�Z�b�g
 *
 * @param	no		�V�[�P���X�i���o�[
 * @param	flag	0=���A1=��
 * @param	adrs	�t�F�[�h�f�[�^�̃A�h���X
 *
 * @retval	"0=�������Ȃ��A1=�J�n"
 */
//--------------------------------------------------------------
extern BOOL Snd_TrackFadeSet( u16 no, u8 flag, void* adrs );

//--------------------------------------------------------------
/**
 * @brief	�g���b�N�t�F�[�h"�f�[�^"�Z�b�g
 *
 * @param	adrs	�t�F�[�h�f�[�^�̃A�h���X
 *
 * @retval	none
 */
//--------------------------------------------------------------
extern void Snd_TrackFadeDataSet( void* adrs );


//==============================================================================================
//
//	d_nohara�Ŏg�p����֐�(�f�o�b�N�p)
//
//==============================================================================================

//--------------------------------------------------------------
/**
 * @brief	�g�`�Đ��p�̃`�����l�����������(�f�o�b�N����)
 *
 * @param	none
 *
 * @retval	none
 */
//--------------------------------------------------------------
extern void Snd_DebugNormalChannelFree();


//==============================================================================================
//
//	snd_test�Ŏg�p����֐�(�f�o�b�N�p)
//
//==============================================================================================

//--------------------------------------------------------------
/**
 * @brief	�o���N���[�h
 *
 * @param	no		�o���N�i���o�[
 *
 * @retval	none
 */
//--------------------------------------------------------------
extern void Snd_DebugLoadBank( u16 no );


//==============================================================================================
//
//	�}�ӊ֘A
//
//==============================================================================================

//--------------------------------------------------------------
/**
 * @brief	�g�`�f�[�^�̃A�h���X����T���v���f�[�^�̃A�h���X���擾
 *
 * @param	p_data		�g�`�f�[�^�̃A�h���X
 *
 * @retval	"�T���v���f�[�^�̃A�h���X�ANULL=���s"
 */
//--------------------------------------------------------------
extern const u8* Snd_WaveDataSampleAdrsGet( const SNDWaveData* p_data );

//--------------------------------------------------------------
/**
 * @brief	�g�`�f�[�^�̃A�h���X����T���v���f�[�^�̔z��̑傫�����擾
 *
 * @param	p_data		�g�`�f�[�^�̃A�h���X
 *
 * @retval	"�T���v���f�[�^�̔z��̑傫���A0=���s"
 */
//--------------------------------------------------------------
extern const u32 Snd_WaveDataSampleSizeGet( const SNDWaveData* p_data );

//--------------------------------------------------------------
/**
 * @brief	�g�`�f�[�^�̃A�h���X���擾(�}�Ӑ�p)
 *
 * @param	wave_arc_no	�g�`�A�[�J�C�u�ԍ�(�|�P�����i���o�[)
 *
 * @retval	"�g�`�f�[�^�\���̂̃A�h���X�ANULL=���s"
 *
 * 1)BGM�̌����J��
 * 2)�g�`�A�[�J�C�u���[�h
 * �̏��������Ă���̂Œ��ӁI
 */
//--------------------------------------------------------------
extern const SNDWaveData* Snd_ZukanWaveDataSet( int wave_arc_no );

//--------------------------------------------------------------
/**
 * @brief	�g�`�f�[�^�̍Đ����Ă���T���v���f�[�^�v�f����Ԃ�
 *
 * @param	handle_no	�n���h���i���o�[
 * @param	p_data		�g�`�f�[�^�̃A�h���X
 *
 * @retval	"�v�f��"
 */
//--------------------------------------------------------------
extern u32 Snd_PlayerGetSampleTick( int handle_no, const SNDWaveData* p_data );

//--------------------------------------------------------------
/**
 * @brief	�g�`�f�[�^�̍Đ����Ă���T���v���f�[�^�v�f����Ԃ�(�}�ӗp)
 *
 * @param	handle_no	�n���h���i���o�[
 * @param	p_data		�g�`�f�[�^�̃A�h���X
 * @param	pitch		�ݒ肵�Ă���s�b�`
 *
 * @retval	"�v�f��"
 */
//--------------------------------------------------------------
extern u32 Snd_ZukanPlayerGetSampleTick( int handle_no, const SNDWaveData* p_data, int pitch );

//--------------------------------------------------------------
/**
 * @brief	�e�B�b�N���擾
 *
 * @param	p_data		�g�`�f�[�^�̃A�h���X
 *
 * @retval	"�e�B�b�N��"
 */
//--------------------------------------------------------------
extern u32 Snd_PlayerGetTick( int handle_no );

//--------------------------------------------------------------
/**
 * @brief	�g�`���x���Z�b�g
 *
 * @param	p_data		�g�`�f�[�^�̃A�h���X
 * @param	buf			�i�[����o�b�t�@�̃|�C���^
 * @param	max			�i�[����o�b�t�@�̍ő吔
 *
 * @retval	none
 */
//--------------------------------------------------------------
extern void Snd_ZukanWaveLevelSet( const SNDWaveData* p_data, u8* buf, int max );

//--------------------------------------------------------------
/**
 * @brief	�g�`���x���Z�b�g(�}�ӗp)
 *
 * @param	p_data		�g�`�f�[�^�̃A�h���X
 * @param	buf			�i�[����o�b�t�@�̃|�C���^
 * @param	max			�i�[����o�b�t�@�̍ő吔
 * @param	pitch		�ݒ肵�Ă���s�b�`
 *
 * @retval	none
 */
//--------------------------------------------------------------
extern void Snd_ZukanWaveLevelSet_New( const SNDWaveData* p_data, u8* buf, int max, int pitch );











//--------------------------------------------------------------
/**
 * @brief	"�f�o�b�N"�@�g�`�f�[�^�\��
 *
 * @param	start		�\������f�[�^�̊J�n�ʒu
 * @param	end			�\������f�[�^�̏I���ʒu
 *
 * @retval	none
 */
//--------------------------------------------------------------
extern void Snd_DebugWaveDataPut( const SNDWaveData* p_data, u32 start, u32 end );

//--------------------------------------------------------------
/**
 * @brief	"�f�o�b�N"�@�g�`���x���\��
 *
 * @param	tick		���݂̃e�B�b�N��
 *
 * @retval	none
 */
//--------------------------------------------------------------
extern void Snd_DebugWaveLevelGet( u32 tick );

//--------------------------------------------------------------
/**
 * @brief	�V�[�P���X���[�J�����[�N��ύX����
 *
 * @param	num		�V�[�P���X���[�J�����[�N"0"�ɃZ�b�g����l
 *
 * @retval	"����=TRUE�A���s=FALSE"
 *
 * �F�X�o�����������A����͎g�p�����肵�Ă����I
 */
//--------------------------------------------------------------
extern BOOL Snd_PlayerWriteVariable( s16 num );

//--------------------------------------------------------------
/**
 * @brief	�g�p�\�`�����l������A���o�[�u�ݒ�
 *
 * @param	flag	1=�Z�b�g�A0=�N���A
 *
 * @retval	none
 */
//--------------------------------------------------------------
extern void Snd_BgmChannelSetAndReverbSet( int flag );

//--------------------------------------------------------------
/**
 * @brief	�v���C���[�̉��ʑ���(�f�t�H���g��127���ݒ肳��Ă���)
 *
 * @param	player_no	�v���C���[�i���o�[
 * @param	volume		�{�����[��
 *
 * @retval	none
 *
 * �g�p��́A�K��127�ɖ߂��Ă��������I
 */
//--------------------------------------------------------------
extern void Snd_PlayerSetPlayerVolume( int player_no, int volume );


#endif


