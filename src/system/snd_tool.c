//==============================================================================================
/**
 * @file	snd_tool.c
 * @brief	�T�E���h�c�[���֐�
 * @author	Satoshi Nohara
 * @date	2005.06.09
 *
 * ��������
 * �퓬�ŃQ�[���I�[�o�[�ɂȂ��āA�|�P�Z���ɖ߂鎞�Ȃǂ́A
 * Snd_PauseClearAll���Ă�ŁA�|�[�Y�t���O���N���A���Ȃ��Ƃ����Ȃ��I
 */
//==============================================================================================
#include "common.h"
#include "snd_system.h"
#include "system/snd_tool.h"
#include "system/snd_perap.h"
#include "src_os_print.h"
#include "poketool/monsno.h"

#include "communication/communication.h"


//�ʎq���r�b�g�^�C�v8bit,�T���v�����O���[�g8k
//#define MIC_TYPE_8BIT_RATE_8K


//==============================================================================================
//
//	����
//
//==============================================================================================
#if 0
	//���X���[�v���[�h���畜�A��̍Đ����
	//�X���[�v�O�̍Đ���ԂƊ��S�Ɉ�v����킯�ł͂Ȃ�
	//�ꎞ�I�ɉ������������Ȃ�����A������񂾂肷�邱�Ƃ�����
	//���ꂪ���ɂȂ鎞�́A�X���[�v�O�ɍĐ����~���A
	//�X���[�v��ɍĐ����ĊJ����Ƃ������Ώ����K�v�ɂȂ�
#endif


//==============================================================================================
//
//	��`
//
//==============================================================================================
//PLAYER_BGM�̎g�p�`�����l���̃r�b�g�w��
#define PLAYER_BGM_NORMAL_CH	(0x07ff)		//�ʏ�̎g�pCH
#define PLAYER_BGM_EXTRA_CH		(0x7fff)		//����̃V�[���̂ݎg�pCH
#define SND_REVERB_NUM_OP		(30)//(40)//(50)//OP���o�[�u�̒l(0-63)
#define SND_REVERB_NUM_ED		(15)//(50)		//ED���o�[�u�̒l(0-63)

#define SND_CH_SET								//��`�L���Ŏg�p�\�`�����l���̑��������


//==============================================================================================
//
//	�ϐ�
//
//==============================================================================================
//�Z�[�u����K�v���胏�[�N(�ǂ̊��ŕK�v������)
static s8 sWaveBuffer[ SWAVE_BUFFER_SIZE ] ATTRIBUTE_ALIGN(32);	//�g�`�i�[�o�b�t�@

static int mono_flag;										//���m�����t���O


//==============================================================================================
//
//	�v���g�^�C�v�錾
//
//==============================================================================================
void Snd_PlayerSetSeqArcNo( NNSSndHandle *p, int arc_no, int index );

void Snd_NowBgmNoSet( u16 no );
u16 Snd_NowBgmNoGet();
void Snd_NextBgmNoSet( u16 no );
u16 Snd_NextBgmNoGet();
void Snd_ZoneBgmSet( u16 bgm );

void Snd_DeleteHeapAfterBgm( void );
int Snd_GetHeapSaveLv( int type );
void Snd_SceneSet( u8 scene );

int Snd_LoadSeByScene( u8 scene );
BOOL Snd_DataSetByScene( u8 scene, u16 no, int flag );
static void Snd_DataSetSub( u8 scene );
static void Snd_FieldDataSet( u16 no, int flag );
static void Snd_FieldDataSet_PauseOffStart( u16 no, u16 player_field_seq_no );
void Snd_FieldDataSetSub( u16 no, u16 old_bank_no );
static void Snd_BattleDataSet( u16 no, int flag );
static void Snd_P2PDataSet( u16 no, int flag );
static void Snd_ContestDataSet( u16 no, int flag );
static void Snd_ConImageDataSet( u16 no, int flag );
static void Snd_AddSceneSeDataSet( u8 scene );
static void Snd_DemoDataSet( u8 scene, u16 no, int flag );
void Snd_EyeBgmSet( u16 no );
void Snd_HeapStateClear(void);

void Snd_PlayerPause( u8 player, BOOL flag );
void Snd_PauseClearAll();
void Snd_PlayerMoveVolume( int handle_no, int vol, int frame );
void Snd_AllPlayerMoveVolume( int vol, int frame );
void Snd_PlayerSetInitialVolume( int handle_no, int vol );
void Snd_VChatVolSet( int seq_no, int handle_no );
void Snd_PlayerSetInitialVolumeBySeqNo( u16 no, int vol );
BOOL Snd_ArcPlayerStartSeqEx( int handle_no, int player_no, u16 no );

int Snd_PlayerCountPlayingSeq( int player_no );
u8 Snd_GetPlayerNo( u16 no );
int Snd_GetSeqNo( NNSSndHandle *p );

const NNSSndArcBankInfo* Snd_GetBankInfo( int no );
u16 Snd_GetBankNo( int no );

static void MicCallback( MICResult /*result*/, void* /*arg*/ );
MICResult Snd_MicStartAutoSampling( MICAutoParam* p);
MICResult Snd_MicStopAutoSampling(void);

NNSSndWaveOutHandle * Snd_WaveOutHandleGet( u32 no );
BOOL Snd_WaveOutAllocChannel( u32 no );
void Snd_WaveOutFreeChannel( u32 no );
void Snd_WaveOutSetPan( u32 no, u8 pan );
void Snd_WaveOutSetSpeed( u32 no, u32 spd );
void Snd_WaveOutSetVolume( u32 no, int vol );
BOOL Snd_WaveOutStart( WAVEOUT_WORK* p, u32 ch );
void Snd_WaveOutStop( u32 no );
BOOL Snd_WaveOutIsPlaying( u32 no );

//�t�Đ�
BOOL Snd_WaveOutStartReverse( u16 no, int vol, int pan, u32 ch, int heap_id );
BOOL Snd_WaveOutStartReverseChorus( int vol, int pan );
void Snd_WaveOutStopReverse( u32 );
static void Snd_BufReverse( u8* p, u32 size );

void Snd_CaptureCreateThread(void);
BOOL Snd_CaptureIsActive(void);
NNSSndCaptureType Snd_CaptureGetCaptureType(void);
void Snd_CaptureChangeOutputEffect( NNSSndCaptureOutputEffectType type );

void Snd_CaptureStartOutputEffect( NNSSndCaptureOutputEffectType type );
BOOL Snd_CaptureStartReverb( int vol );
void Snd_CaptureStopReverb( int frame );
void Snd_CaptureReverbVol( int vol, int frame );

BOOL Snd_CaptureStartEffect(void);
void Snd_CaptureStopEffect(void);
void Snd_CaptureEffectLevel( int level );
void EffectCallback( void* lp, void* rp, u32 len, NNSSndCaptureFormat format, void* arg );
void EffectCallback2( void* lp, void* rp, u32 len, NNSSndCaptureFormat format, void* arg );
static inline smp_t GetSample( smp_t* p, int x, int n, const EffectCallbackInfo* info );
static inline int abs( int x );
void SamplingCallback( void* bufferL_p, void* bufferR_p, u32 len, NNSSndCaptureFormat format, void* arg );

void Snd_PlayerSetTrackMute( int handle_no, u16 bitmask, BOOL flag );
void Snd_PlayerSetTrackVolume( NNSSndHandle *p, u16 bitmask, int vol );
void Snd_PlayerSetTrackPitch( int handle_no, u16 bitmask, int pitch );
void Snd_PlayerSetTrackPitchBySeqNo( u16 no, u16 bitmask, int pitch );
void Snd_PlayerSetTrackPan( int handle_no, u16 bitmask, int pan );
void Snd_PlayerSetTempoRatio( int handle_no, int tempo );

void Snd_SetMonoFlag( BOOL flag );
void Snd_FadeCountSet( int frame );
int Snd_FadeCountCheck();
void Snd_NextWaitSet( int frame );
int Snd_NextWaitCheck();
//void Snd_SetMasterVolume( int vol );

void* Snd_GetWaveBufAdrs();

//�f�o�b�N�p
BOOL Snd_PlayerHeapCreate( int player_no, u32 size );

void Snd_BankFlagSet( int no );
u8 Snd_BankFlagGet();

BOOL Snd_FadeOutNextPlaySet( u8 scene, u16 no, int frame, int next_wait, u8 flag, void* adrs );
BOOL Snd_FadeOutNextFadeInSet( u8 scene, u16 no, int frame, int next_wait, int next_frame, u8 flag, void* adrs );
static void Snd_FadeCommonSet( u8 scene, u16 no, int frame, int next_wait, u8 flag, void* adrs );

BOOL Snd_PlayerWriteVariable( s16 num );
static void Snd_PlayerBgmChannelSet( u16 ch_bit );

void Snd_BgmChannelSetAndReverbSet( int flag );
static void Snd_FieldPauseOrStop( void );


//==============================================================================================
//
//	�v���O����
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
void Snd_PlayerSetSeqArcNo( NNSSndHandle *p, int arc_no, int index )
{
	NNS_SndPlayerSetSeqArcNo( p, arc_no, index );
	return;
}

//--------------------------------------------------------------
/**
 * @brief	�t�B�[���hBGM�Œ�t���O�Z�b�g(�Z�[�u�͂��Ȃ�)
 *
 * @param	flag	1=BGM�؂�ւ��Ȃ��A0E=BGM�؂�ւ��(�ʏ�)
 *
 * @retval	none
 */
//--------------------------------------------------------------
void Snd_CtrlBgmFlagSet( u8 flag )
{
	u8* ctrl_bgm_flag = Snd_GetParamAdrs(SND_W_ID_CTRL_BGM_FLAG);
	*ctrl_bgm_flag = flag;
	return;
}

//--------------------------------------------------------------
/**
 * @brief	�t�B�[���hBGM�Œ�t���O�`�F�b�N(�Z�[�u�͂��Ȃ�)
 *
 * @param	none
 *
 * @retval	"1=BGM�؂�ւ��Ȃ��A0E=BGM�؂�ւ��(�ʏ�)"
 */
//--------------------------------------------------------------
u8 Snd_CtrlBgmFlagCheck( void )
{
	u8* ctrl_bgm_flag = Snd_GetParamAdrs(SND_W_ID_CTRL_BGM_FLAG);
	return *ctrl_bgm_flag;
}

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
void Snd_NowBgmNoSet( u16 no )
{
	u16* now_bgm_no = Snd_GetParamAdrs(SND_W_ID_NOW_BGM_NO);
	*now_bgm_no = no;
	Snd_NextBgmNoSet( 0 );			//���ӁI ����BGM�i���o�[���N���A�I
	return;
}

//--------------------------------------------------------------
/**
 * @brief	����BGM�i���o�[�擾
 *
 * @param	none
 *
 * @retval	"����BGM�i���o�["
 */
//--------------------------------------------------------------
u16 Snd_NowBgmNoGet()
{
	u16* now_bgm_no = Snd_GetParamAdrs(SND_W_ID_NOW_BGM_NO);
	return *now_bgm_no;
}

//--------------------------------------------------------------
/**
 * @brief	����BGM�i���o�[�X�V
 *
 * @param	no		�X�V����BGM�i���o�[
 *
 * @retval	none
 */
//--------------------------------------------------------------
void Snd_NextBgmNoSet( u16 no )
{
	u16* next_bgm_no = Snd_GetParamAdrs(SND_W_ID_NEXT_BGM_NO);
	*next_bgm_no = no;
	return;
}

//--------------------------------------------------------------
/**
 * @brief	����BGM�i���o�[�擾
 *
 * @param	none
 *
 * @retval	"����BGM�i���o�["
 */
//--------------------------------------------------------------
u16 Snd_NextBgmNoGet()
{
	u16* next_bgm_no = Snd_GetParamAdrs(SND_W_ID_NEXT_BGM_NO);
	return *next_bgm_no;
}

//--------------------------------------------------------------
/**
 * @brief	�t�B�[���h�o���N�i���o�[�Z�b�g
 *
 * @param	bank_no		�o���N�i���o�[
 *
 * @retval	none
 */
//--------------------------------------------------------------
void Snd_ZoneBgmSet( u16 bgm )
{
	u16* zone_bgm	= Snd_GetParamAdrs(SND_W_ID_ZONE_BGM);
	*zone_bgm		= bgm;
	return;
}


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
 *
 * ���C���V�[�����Z�b�g����ƁA
 * �T�u�V�[����"SND_SCENE_DUMMY"�ɃN���A�����
 */
//--------------------------------------------------------------
void Snd_SceneSet( u8 scene )
{
	u8* scene_main	= Snd_GetParamAdrs(SND_W_ID_SCENE_MAIN);
	u8* scene_sub	= Snd_GetParamAdrs(SND_W_ID_SCENE_SUB);

	if( scene < SND_SCENE_SUB ){
		*scene_main	= scene;			//���C���V�[��
		*scene_sub  = SND_SCENE_DUMMY;	//�N���A
	}else{
		*scene_sub	= scene;			//�T�u�V�[��
	}

#ifdef SOUND_OS_PRINT_ON
	OS_Printf( "\n--------�T�E���h�@�V�[��--------\n" );
	OS_Printf( "���C�� = %d\n", *scene_main );
	OS_Printf( "�T�u = %d\n", *scene_sub );
	OS_Printf( "\n--------------------------------\n\n" );
#endif

	return;
}

//--------------------------------------------------------------
/**
 * @brief	�V�[�����L�[�ɂ��āASE�f�[�^�����[�h
 *
 * @param	scene		�V�[��
 *
 * @retval	"����=TRUE�A���s=FALSE"
 */
//--------------------------------------------------------------
int Snd_LoadSeByScene( u8 scene )
{
	int ret;

	//SE�V�[�P���X�O���[�v
	switch( scene ){

	//�^�C�g��
	//AGB
	//���E����(�K���t�B�[���h�ɂ���I��t�A��p��ʂŋȂ������Ȃ��̂Ő�p�̃��[�h�͂��߁I)
	//�ӂ����Ȃ��������(�K���t�B�[���h�ɂ���Iug_20�g�p)
	//�G���f�B���O
	case SND_SCENE_TITLE:
	case SND_SCENE_AGB:
	//case SND_SCENE_WORLDTRADE:
	case SND_SCENE_HUSIGI:
	case SND_SCENE_ENDING:
		//��p�̉����Ȃ����́A�t�B�[���h�����[�h���Ă����I
		ret = Snd_ArcLoadGroup( GROUP_SE_FIELD );
		break;

	//�I�[�v�j���O
	//�^�}�S�z��
	case SND_SCENE_OPENING:
	case SND_SCENE_EGG:
		ret = Snd_ArcLoadGroup( GROUP_SE_BATTLE );		//�o�g���̉����K�v�Ȃ̂ŁI
		break;

	//�����f��
	case SND_SCENE_TRADE:
		ret = Snd_ArcLoadGroup( GROUP_SE_TRADE );
		break;

	//�t�B�[���h
	case SND_SCENE_FIELD:
		ret = Snd_ArcLoadGroup( GROUP_SE_FIELD );
		break;

	//�o�g��
	case SND_SCENE_BATTLE:
		ret = Snd_ArcLoadGroup( GROUP_SE_BATTLE );
		break;

	//P2P
	case SND_SCENE_P2P:
		ret = Snd_ArcLoadGroup( GROUP_SE_FIELD );
		break;

	//�R���e�X�g
	case SND_SCENE_CONTEST:
		ret = Snd_ArcLoadGroup( GROUP_SE_CONTEST );
		break;

	//�a���f��
	case SND_SCENE_DENDOU:
		ret = Snd_ArcLoadGroup( GROUP_SE_FIELD );		//SEQ_SE_DP_SAVE���g�p���Ă���I
		break;

	//����
	case SND_SCENE_NUTMIXER:
		ret = Snd_ArcLoadGroup( GROUP_SE_NUTMIXER );
		break;

	//�o�b�O
	case SND_SCENE_SUB_BAG:
		ret = Snd_ArcLoadGroup( GROUP_SE_BAG );
		break;

	//�X���b�g
	case SND_SCENE_SUB_SLOT:
		ret = Snd_ArcLoadGroup( GROUP_SE_SLOT );
		break;

	//���O����
	case SND_SCENE_SUB_NAMEIN:
		ret = Snd_ArcLoadGroup( GROUP_SE_NAMEIN );
		break;

	//�C���[�W�N���b�v
	case SND_SCENE_CON_IMAGE:	//�R���e�X�g
	case SND_SCENE_SUB_IMAGE:
		ret = Snd_ArcLoadGroup( GROUP_SE_IMAGE );
		break;

	//�}��
	case SND_SCENE_SUB_ZUKAN:
		ret = Snd_ArcLoadGroup( GROUP_SE_ZUKAN );
		break;

	//�^�E���}�b�v(���ӁI)
	//�`���m�[�g
	case SND_SCENE_SUB_TOWNMAP:
	case SND_SCENE_SUB_FNOTE:
		ret = Snd_ArcLoadBank( BANK_SE_TOWNMAP );			//�o���N���[�h
		ret = Snd_ArcLoadWaveArc( WAVE_ARC_SE_TOWNMAP );	//�g�`�A�[�J�C�u
		break;

	//�g���[�i�[�J�[�h
	case SND_SCENE_SUB_TRCARD:
		ret = Snd_ArcLoadGroup( GROUP_SE_TRCARD );
		break;

	//�|�P�������X�g
	case SND_SCENE_SUB_POKELIST:
		ret = Snd_ArcLoadGroup( GROUP_SE_POKELIST );
		break;

	//���Ό@��
	case SND_SCENE_SUB_DIG:
		ret = Snd_ArcLoadGroup( GROUP_SE_DIG );
		break;

	//�J�X�^���{�[��
	case SND_SCENE_SUB_CUSTOM:
		ret = Snd_ArcLoadGroup( GROUP_SE_CUSTOM );
		break;

	//�ŏ��̃|�P�����I��
	case SND_SCENE_SUB_FIRSTPOKE:
		ret = Snd_ArcLoadGroup( GROUP_SE_BAG );			//���ӁF���̃O���[�v���g���񂵂Ă���I
		break;

	//�|�P�����X�e�[�^�X
	case SND_SCENE_SUB_PST:
		ret = Snd_ArcLoadGroup( GROUP_SE_NAMEIN );		//���ӁF���̃O���[�v���g���񂵂Ă���I
		break;

	//�ȈՉ�b
	case SND_SCENE_SUB_PMS:
		ret = Snd_ArcLoadGroup( GROUP_SE_CUSTOM );		//���ӁF���̃O���[�v���g���񂵂Ă���I
		break;

	//�N���C�}�b�N�X
	case SND_SCENE_SUB_CLIMAX:
		ret = Snd_ArcLoadGroup( GROUP_SE_CLIMAX );
		break;

	//�D�f��(���ӁI)
	case SND_SCENE_SUB_SHIP:
		ret = Snd_ArcLoadBank( BANK_SE_SHIP );			//�o���N���[�h
		ret = Snd_ArcLoadWaveArc( WAVE_ARC_SE_SHIP );	//�g�`�A�[�J�C�u
		break;

	//�����b�R��(���ӁI)
	case SND_SCENE_SUB_TRAIN:
		ret = Snd_ArcLoadBank( BANK_SE_TRAIN );			//�o���N���[�h
		ret = Snd_ArcLoadWaveArc( WAVE_ARC_SE_TRAIN );	//�g�`�A�[�J�C�u
		break;

	//�G���[
	defalut:
		GF_ASSERT( (0) && "�V�[���i���o�[���s���ł��I" );
		ret = FALSE;
		break;
	}

	return ret;
}

//--------------------------------------------------------------
/**
 * @brief	�V�[�����L�[�ɂ��āA�T�E���h�f�[�^�Z�b�g
 *
 * @param	scene	�V�[��
 * @param	no		�V�[�P���X�i���o�[
 * @param	flag	"���g�p"
 *
 * @retval	"0=�������Ȃ��A1=�f�[�^���[�h"
 *
 * ���݂̃V�[���ƁA�n���ꂽ�V�[�����������́A
 * �T�E���h�f�[�^�����[�h����K�v���Ȃ��̂ŉ������Ȃ��I
 */
//--------------------------------------------------------------
BOOL Snd_DataSetByScene( u8 scene, u16 no, int flag )
{
	u8* scene_main	= Snd_GetParamAdrs(SND_W_ID_SCENE_MAIN);
	u8* scene_sub	= Snd_GetParamAdrs(SND_W_ID_SCENE_SUB);
	u16* me_wait	= Snd_GetParamAdrs(SND_W_ID_ME_WAIT);

	//�V�[�����������͉������Ȃ�
	if( scene < SND_SCENE_SUB ){
		if( *scene_main == scene ){	
			return 0;
		}
	}else{
		if( *scene_sub == scene ){	
			return 0;
		}
	}

	//�V�[���Z�b�g
	Snd_SceneSet( scene );

	switch( scene ){

	//�t�B�[���h
	case SND_SCENE_FIELD:
		Snd_BgmChannelSetAndReverbSet( 0 );		//�g�p�\�`�����l������A���o�[�u�ݒ�(�N���A)
		Snd_FieldDataSet( no, flag );

		//ME�Đ����ɒʐM�G���[�ȂǂŁAME�J��������Ȃ���Ԃ��ƁA
		//Snd_Main��ME�g�p���̂܂܂ɂȂ��Ă��܂��̂ŁA
		//�t�B�[���h�f�[�^���[�h�̃^�C�~���O�ŕK�����Ƃ��悤�ɉ��}���������Ă���(06.07.27)
		(*me_wait) = 0;	//�N���A
		break;

	//�o�g��
	case SND_SCENE_BATTLE:
		Snd_BattleDataSet( no, flag );
		break;

	//P2P
	case SND_SCENE_P2P:
		Snd_P2PDataSet( no, flag );
		break;

	//�R���e�X�g
	case SND_SCENE_CONTEST:
		Snd_ContestDataSet( no, flag );
		break;

	//�C���[�W�N���b�v(�R���e�X�g)
	case SND_SCENE_CON_IMAGE:
		Snd_ConImageDataSet( no, flag );
		break;

	//�T�u���(BGM�������p���ASE��ǉ����[�h����)
	case SND_SCENE_SUB_BAG:
	case SND_SCENE_SUB_NAMEIN:
	case SND_SCENE_SUB_IMAGE:
	case SND_SCENE_SUB_ZUKAN:
	case SND_SCENE_SUB_TOWNMAP:
	case SND_SCENE_SUB_TRCARD:
	case SND_SCENE_SUB_POKELIST:
	case SND_SCENE_SUB_DIG:
	case SND_SCENE_SUB_CUSTOM:
	case SND_SCENE_SUB_FIRSTPOKE:
	case SND_SCENE_SUB_PST:
	case SND_SCENE_SUB_PMS:
	case SND_SCENE_SUB_CLIMAX:
	case SND_SCENE_SUB_SHIP:
	case SND_SCENE_SUB_TRAIN:
	case SND_SCENE_SUB_SLOT:
	case SND_SCENE_SUB_FNOTE:
		/************/
		//�ǉ����Ă���
		/************/
		Snd_AddSceneSeDataSet( scene );
		break;

	//�S�Ē�~���āA�풓�ȊO�����[�h������
	case SND_SCENE_TITLE:
		Snd_BgmChannelSetAndReverbSet( 1 );		//�g�p�\�`�����l������A���o�[�u�ݒ�(�Z�b�g)
		Snd_DemoDataSet( scene, no, flag );
		break;

	//�S�Ē�~���āA�풓�ȊO�����[�h������
	case SND_SCENE_ENDING:
		Snd_BgmChannelSetAndReverbSet( 2 );		//�g�p�\�`�����l������A���o�[�u�ݒ�(�Z�b�g)
		Snd_DemoDataSet( scene, no, flag );
		break;

	//�S�Ē�~���āA�풓�ȊO�����[�h������
	case SND_SCENE_OPENING:
		Snd_BgmChannelSetAndReverbSet( 0 );		//�g�p�\�`�����l������A���o�[�u�ݒ�(�N���A)
		Snd_DemoDataSet( scene, no, flag );
		break;

	//�S�Ē�~���āA�풓�ȊO�����[�h������
	case SND_SCENE_TRADE:
	case SND_SCENE_DENDOU:
	case SND_SCENE_AGB:
	case SND_SCENE_HUSIGI:
	case SND_SCENE_NUTMIXER:
	//case SND_SCENE_WORLDTRADE:
	case SND_SCENE_EGG:
		/************/
		//�ǉ����Ă���
		/************/
		Snd_DemoDataSet( scene, no, flag );
		break;

	//�|�[�Y���K�v�ȃf���͕ʂ̃Z�b�g�R�}���h���
	//case SND_SCENE_DEMO:
		//break;

	//�������Ȃ�
	defalut:
		return 0;
	};

	return 1;		//�f�[�^���[�h
}

//--------------------------------------------------------------
/**
 * @brief	�T�E���h�f�[�^�Z�b�g���ʏ���
 *
 * @param	scene	�V�[��
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void Snd_DataSetSub( u8 scene )
{
	int* heap_save_global	= Snd_GetParamAdrs(SND_W_ID_HEAP_SAVE_GLOBAL);

	Snd_HeapLoadState( *heap_save_global );						//�풓�ȊO������
	//�풓�͏����Ȃ��̂ŁA�ēx�K�w��ۑ�����K�v�͂Ȃ��I
	//Snd_HeapSaveState(&wk->heap_save[SND_HEAP_SAVE_GLOBAL]);	//�K�w�ۑ�(�풓�ȊO���������Ɏg�p)
	
	//�ꉞ�Ă�ł���
	Snd_HeapSaveState(Snd_GetParamAdrs(SND_W_ID_HEAP_SAVE_BGM_BANK));	//�ۑ�(�풓,bnk,SE�ȊO����)

	Snd_LoadSeByScene( scene );									//SE�V�[�P���X�O���[�v
	Snd_HeapSaveState(Snd_GetParamAdrs(SND_W_ID_HEAP_SAVE_SE));	//�K�w�ۑ�(�풓�ASE�ȊO�������g�p)

	return;
}

//--------------------------------------------------------------
/**
 * @brief	�t�B�[���h��ʂɐ؂�ւ�鎞�̃T�E���h�f�[�^�Z�b�g
 *
 * @param	no		�V�[�P���X�i���o�[
 * @param	flag	"���g�p"
 *
 * @retval	none
 *
 * ���f�[�^���[�h����
 * �풓
 * SE
 * BGM(WAVEARC)
 *
 * �V�[�P���X�A�o���N�̓v���C���[�q�[�v�Ń��[�h���Ă���I
 *
 * �퓬�ŃQ�[���I�[�o�[�ɂȂ��āA�|�P�Z���ɖ߂�Ƃ��Ȃǂ́A
 * Snd_PauseClearAll���Ă�ŁA�|�[�Y�t���O���N���A���Ȃ��Ƃ����Ȃ��I
 */
//--------------------------------------------------------------
static void Snd_FieldDataSet( u16 no, int flag )
{
	int ret,player_seq_no;
	u16 bgm;
	u8* field_pause_flag	= Snd_GetParamAdrs(SND_W_ID_FIELD_PAUSE_FLAG);
	int* heap_save_global	= Snd_GetParamAdrs(SND_W_ID_HEAP_SAVE_GLOBAL);
	u16* zone_bgm			= Snd_GetParamAdrs(SND_W_ID_ZONE_BGM);

#ifdef SOUND_OS_PRINT_ON
	OS_Printf( "\n���T�E���h�f�[�^���[�h�@�t�B�[���h�V�[���؂�ւ�聄\n" );
#endif


	//�|�[�Y���Ă��Ȃ��āA�����Ȃ�炻���Ƃ�����ABGM���p���ɂ��Ă���I

	//PLAYER_FIELD��BGM�i���o�[�擾
	player_seq_no = Snd_GetSeqNo( Snd_HandleGet(SND_HANDLE_FIELD) );

	//PLAYER_FIELD���|�[�Y���Ă��Ȃ���
	if( *field_pause_flag == 0 ){
	
		//�����Ȃ�炻���Ƃ�����
		if( player_seq_no == no ){

			//Snd_AddSceneSeDataSet( SND_SCENE_FIELD );			//SE��ǉ����[�h����

			//PLAYER_FIELD���~���Ă���A�ʉ�ʂɍs���΁A
			//�߂��Ă����Ƃ��ɁABGM�i���o�[�擾�̒l���ς��̂ŁA
			//FieldData�����[�h�����I
			
			//����BGM�Ɏ��]�Ԃ��Z�b�g���Ă����Ԃ�(�t�F�[�h�A�E�g��)
			//�v���C���[�V�[�P���X�i���o�[�́A�܂����]�ԂɂȂ��Ă��Ȃ��̂ŁA
			//�����������^�[�����Ă��܂��I�Ȃ̂Ń`�F�b�N������
			if( Snd_NextBgmNoGet() != SEQ_BICYCLE ){
				return;		//���ӁI
			}
		}
	}

	//�|�[�Y���A�̕���ɂ��K�v�I
	//�g�`�A�[�J�C�u�̃��[�h���K�v�Ȃ̂ŁI
	Snd_BankFlagSet( SND_BANK_CHANGE );							//�o���N�؂�ւ��邩�t���O���Z�b�g

	//�菇(1)
	Snd_StopEx();												//�t�B�[���hBGM�𔲂����đS��~

	//PLAYER_FIELD���|�[�Y���Ă��鎞�ł��A
	//���Ɩ邪�؂�ւ�������́A�Ⴄ�Ȃ�炷�悤�ɂ���I
	//���̎��́A�|�[�Y�t���O�𗎂Ƃ��āA������Ⴄ�Ȃ��Đ��ɂ����悤�ɂ���I(06.04.12)
	if( player_seq_no != no ){
		Snd_PlayerPause( PLAYER_FIELD, FALSE );					//�t�B�[���hBGM�ĊJ
		Snd_Stop();
	}

	//�t�B�[���hBGM���|�[�Y���Ă������������I
	if( *field_pause_flag == 1 ){

#if 1
		Snd_HeapLoadState( Snd_GetHeapSaveLv(SND_HEAP_SAVE_BGM_BANK) );

		Snd_LoadSeByScene( SND_SCENE_FIELD );						//SE�V�[�P���X�O���[�v
		Snd_HeapSaveState(Snd_GetParamAdrs(SND_W_ID_HEAP_SAVE_SE));	//�K�w�ۑ�(�풓�ASE�ȊO������)
#else

		//���ʏ���
		Snd_DataSetSub( SND_SCENE_FIELD );
#endif

		//���Ɩ邪�؂�ւ���āA�Ⴄ�Ȃ�炻���Ƃ������́A
		//�|�[�Y�t���O�𗎂Ƃ��āA������Ⴄ�Ȃ��Đ��ɂ����悤�ɂ���I(06.04.12)
		if( player_seq_no != no ){
			Snd_PlayerPause( PLAYER_FIELD, FALSE );					//�t�B�[���hBGM�ĊJ
		}

		Snd_FieldDataSet_PauseOffStart( no, player_seq_no );
		return;
	}

#if 0	//snd_play�̒��ŁASnd_FieldDataSetSub���Ă΂��̂ō폜(06/07/11)

	//�|�[�Y���Ă��Ȃ����́A�o���N���܂߁A�풓�ȊO������

	Snd_HeapLoadState( Snd_GetHeapSaveLv(SND_HEAP_SAVE_GLOBAL) );		//�풓�ȊO������

	Snd_ArcLoadSeqEx( *zone_bgm, NNS_SND_ARC_LOAD_BANK );				//�o���N���[�h
	Snd_HeapSaveState(Snd_GetParamAdrs(SND_W_ID_HEAP_SAVE_BGM_BANK));	//�ۑ�(�풓,bnk,SE�ȊO����)
	
	Snd_LoadSeByScene( SND_SCENE_FIELD );								//SE�V�[�P���X�O���[�v
	Snd_HeapSaveState(Snd_GetParamAdrs(SND_W_ID_HEAP_SAVE_SE));	//�K�w�ۑ�(�풓�ASE�ȊO�������g�p)
#endif

	//BGM�Đ�(�X�e�[�^�X���Đ�)
	Snd_BgmPlay( no );											//�t�B�[���hBGM�Đ�

	return;
}

//--------------------------------------------------------------
/**
 * @brief	�t�B�[���hBGM���|�[�Y�������闬��
 *
 * @param	no					�V�[�P���X�i���o�[
 * @param	player_field_seq_no	�t�B�[���h�̃V�[�P���X�i���o�[
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void Snd_FieldDataSet_PauseOffStart( u16 no, u16 player_field_seq_no )
{
	u16* zone_bgm	= Snd_GetParamAdrs(SND_W_ID_ZONE_BGM);
	u16 tmp_bank_no = Snd_GetBankNo(*zone_bgm);					//�s���Ȓl�������Ă��Ȃ����`�F�b�N

#ifdef SOUND_OS_PRINT_ON
	OS_Printf( "���t�B�[���hBGM�|�[�Y�����I��\n" );
#endif

#if 0
	//�Đ����悤�Ƃ��Ă���BGM�i���o�[�APLAYER_FIELD�ɂ��łɐݒ肳��Ă���o���N�i���o�[
	Snd_FieldDataSetSub( no, Snd_GetBankNo(player_field_seq_no) );
#else
	if( (tmp_bank_no != BANK_BGM_FIELD) && (tmp_bank_no != BANK_BGM_DUNGEON) ){
		Snd_ArcLoadSeqEx( no, NNS_SND_ARC_LOAD_WAVE );				//�g�`�A�[�J�C�u���[�h
		OS_Printf( "zone_bgm = %d\n", *zone_bgm );
		OS_Printf( "tmp_bank_no = %d\n", tmp_bank_no );
		GF_ASSERT( (0) && "bgm play : *zone_bgm error" );
	}else{
		Snd_ArcLoadSeqEx( *zone_bgm, NNS_SND_ARC_LOAD_WAVE | NNS_SND_ARC_LOAD_BANK);//arc,bank
	}

	Snd_HeapSaveState( Snd_GetParamAdrs(SND_W_ID_HEAP_SAVE_BGM) );	//�K�w�ۑ�(BGM�̌������)
#endif

	//�|�[�Y��Ԃ��畜�A����ɂ́A�o���N���ă��[�h����K�v�����邪�A
	//�v���C���[�q�[�v�Ńo���N�����[�h���Ă���̂ő��v�I

	//Snd_NowBgmNoSet( Snd_GetSeqNo(Snd_HandleGet(SND_HANDLE_FIELD)) );	//����BGM�i���o�[�Z�b�g

	//�v���C���[�q�[�v��BGM_FIELD_BANK(BGM_DUNGEON_BANK)���c���Ă���̂��O��I
	//���ꂪ�o���Ȃ��V�`���G�[�V��������������ABGM_DUNGEON_BANK�͔p�~���Ȃ��ƃ_���I
	
	Snd_PlayerPause( PLAYER_FIELD, FALSE );						//�t�B�[���hBGM�ĊJ
	Snd_BgmFadeIn( BGM_VOL_MAX, 40, BGM_FADEIN_START_VOL_MIN );	//�t�F�[�h�C��

	//�o���N�؂�ւ��邩�t���O�����Z�b�g
	Snd_BankFlagSet( SND_BANK_CONTINUE );					//�N���A = �p��
	return;
}

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
void Snd_FieldDataSetSub( u16 no, u16 old_bank_no )
{
	u16 tmp_bank_no;
	u8* bank_flag	= Snd_GetParamAdrs(SND_W_ID_BANK_FLAG);
	u16* zone_bgm	= Snd_GetParamAdrs(SND_W_ID_ZONE_BGM);

	/*
	//PLAYER_FIELD�Ŗ炷BGM�̃o���N�w��͒��ӂ���I
	//Snd_DataSetByScene��������ɁABGM�f�[�^�̃��[�h���������Ȃ����Ƃ��N����̂ŁI
	//
	//BANK_BASIC���w�肵�Ă���΁A���[�h������Ȃ��Ă����C�B
	//�Q�[���J�n���́Aold_bank_no��0�Ȃ̂ŁA�K���K�w�ۑ��܂ŌĂ΂��B
	*/

	//�o���N�؂�ւ���t���O��ON�ɂȂ��Ă��邩�`�F�b�N
	if( (*bank_flag == SND_BANK_CHANGE) || (old_bank_no == 0) ){

		//�}�b�v�J�ڂ̎��A�o���N�����[�h����
		//�]�[�����܂������A�o���N�����[�h���Ȃ�
		
		//�V�[�P���X�A�o���N�̓v���C���[�q�[�v�Ń��[�h���Ă���I
#if 0
		Snd_HeapLoadState( Snd_GetHeapSaveLv(SND_HEAP_SAVE_SE) );		//BGM���J��
#else
		Snd_HeapLoadState( Snd_GetHeapSaveLv(SND_HEAP_SAVE_GLOBAL) );	//�풓�ȊO������

		Snd_ArcLoadSeqEx( *zone_bgm, NNS_SND_ARC_LOAD_BANK );			//�o���N���[�h
		Snd_HeapSaveState(Snd_GetParamAdrs(SND_W_ID_HEAP_SAVE_BGM_BANK));//�ۑ�(�풓,bnk,SE�ȊO����)
	
		Snd_LoadSeByScene( SND_SCENE_FIELD );							//SE�V�[�P���X�O���[�v
		Snd_HeapSaveState(Snd_GetParamAdrs(SND_W_ID_HEAP_SAVE_SE));		//�ۑ�(�풓�ASE�ȊO����)
#endif

		//�g���A��ꑐ��ԂŐ퓬�ɂ����āA���A����ƁA
		//�ǂݍ��܂��f�[�^�́ABANK_BASIC�ɂȂ��Ă��܂��I
		//�]�[�����܂��������A���ɏ㗤�������ȂǂɁA
		//BANK_FIELD(BANK_DUNGEON)���ǂݍ��܂�Ă��Ȃ��̂ŁA
		//BGM�Đ������Ŏ��s���Ă��܂��̂ŁA
		//�ۑ����Ă������]�[���̋ȃi���o�[�����āA
		//�K�v�Ȕg�`���t�F�[�h�A�E�g���Ƀ��[�h����

		tmp_bank_no = Snd_GetBankNo(*zone_bgm);				//�s���Ȓl�������Ă��Ȃ����`�F�b�N
		if( (tmp_bank_no != BANK_BGM_FIELD) && (tmp_bank_no != BANK_BGM_DUNGEON) ){
			Snd_ArcLoadSeqEx( no, NNS_SND_ARC_LOAD_WAVE );				//�g�`�A�[�J�C�u���[�h
			OS_Printf( "zone_bgm = %d\n", *zone_bgm );
			OS_Printf( "tmp_bank_no = %d\n", tmp_bank_no );
			GF_ASSERT( (0) && "bgm play : *zone_bgm error" );
		}else{
#if 1
			Snd_ArcLoadSeqEx( *zone_bgm, NNS_SND_ARC_LOAD_WAVE );		//�g�`�A�[�J�C�u���[�h
#else
	//		Snd_ArcLoadSeqEx( *zone_bgm, NNS_SND_ARC_LOAD_WAVE | NNS_SND_ARC_LOAD_BANK);//arc,bank
#endif
		}

		Snd_HeapSaveState( Snd_GetParamAdrs(SND_W_ID_HEAP_SAVE_BGM) );	//�K�w�ۑ�(BGM�̌������)
	}

	return;
}

//--------------------------------------------------------------
/**
 * @brief	�o�g����ʂɐ؂�ւ�鎞�̃T�E���h�f�[�^�Z�b�g
 *
 * @param	no		�V�[�P���X�i���o�[
 * @param	flag	"���g�p"
 *
 * @retval	none
 *
 * ���f�[�^���[�h����
 * �풓
 * SE
 * BGM
 */
//--------------------------------------------------------------
static void Snd_BattleDataSet( u16 no, int flag )
{
	int* heap_save_global	= Snd_GetParamAdrs(SND_W_ID_HEAP_SAVE_GLOBAL);

#ifdef SOUND_OS_PRINT_ON
	OS_Printf( "\n���T�E���h�f�[�^���[�h�@�o�g���V�[���؂�ւ�聄\n" );
#endif

	//�t�B�[���hBGM���|�[�Y���邩�A��~���邩�𔻕ʂ��ď���
	Snd_FieldPauseOrStop();

#if 0
	//���ʏ���
	Snd_DataSetSub( SND_SCENE_BATTLE );
#else
	Snd_HeapLoadState( Snd_GetHeapSaveLv(SND_HEAP_SAVE_BGM_BANK) );	//�풓��field_bnk�ȊO����

	Snd_LoadSeByScene( SND_SCENE_BATTLE );							//SE�V�[�P���X�O���[�v
	Snd_HeapSaveState(Snd_GetParamAdrs(SND_W_ID_HEAP_SAVE_SE));	//�K�w�ۑ�(�풓�ASE�ȊO�������g�p)
#endif

	//�t�B�[���hBGM�̃V�[�P���X�A�o���N�́A�v���C���[�q�[�v�ŏ������Ă���̂ŁA
	//��~�������Ă΂Ȃ��ƊJ������Ȃ�(�|�[�Y��Ԃɂ��Ă���)

	Snd_BankFlagSet( SND_BANK_CHANGE );							//�o���N�؂�ւ��邩�t���O���Z�b�g
	Snd_BgmPlay( no );											//BGM�Đ�
	return;
}

//--------------------------------------------------------------
/**
 * @brief	P2P��ʂɐ؂�ւ�鎞�̃T�E���h�f�[�^�Z�b�g
 *
 * @param	no		�V�[�P���X�i���o�[
 * @param	flag	"���g�p"
 *
 * @retval	none
 *
 * ���f�[�^���[�h����
 * �풓
 * SE
 * BGM
 */
//--------------------------------------------------------------
static void Snd_P2PDataSet( u16 no, int flag )
{
	int* heap_save_global	= Snd_GetParamAdrs(SND_W_ID_HEAP_SAVE_GLOBAL);

#ifdef SOUND_OS_PRINT_ON
	OS_Printf( "\n���T�E���h�f�[�^���[�h�@P2P�V�[���؂�ւ�聄\n" );
#endif

	//�菇(1)
	Snd_Stop();													//�S��~

	//�|�[�Y�t���O�𗎂Ƃ��Ȃ��Ƃ����Ȃ��I
	//Snd_PlayerPause( PLAYER_FIELD, FALSE );					//�t�B�[���hBGM�|�[�Y����
	
	//�S�Ẵ|�[�Y�t���O�N���A
	Snd_PauseClearAll();

	//���ʏ���
	Snd_DataSetSub( SND_SCENE_FIELD );

	//Snd_BankFlagSet( SND_BANK_CONTINUE );						//�o���N���̂܂܌p��
	Snd_BgmPlay( no );											//BGM�Đ�
	return;
}

//--------------------------------------------------------------
/**
 * @brief	�R���e�X�g��ʂɐ؂�ւ�鎞�̃T�E���h�f�[�^�Z�b�g
 *
 * @param	no		�V�[�P���X�i���o�[
 * @param	flag	"���g�p"
 *
 * @retval	none
 *
 * ���f�[�^���[�h����
 * �풓
 * SE
 * BGM
 *
 * �b��ŁA�o�b�O�̃T�u�V�[�������[�h���Ă���
 */
//--------------------------------------------------------------
void Snd_ContestDataSet( u16 no, int flag )
{
	int* heap_save_global	= Snd_GetParamAdrs(SND_W_ID_HEAP_SAVE_GLOBAL);

#ifdef SOUND_OS_PRINT_ON
	OS_Printf( "\n���T�E���h�f�[�^���[�h�@�R���e�X�g�V�[���؂�ւ�聄\n" );
#endif

	//�菇(1)
	Snd_Stop();													//�S��~

	//���ʏ���
	Snd_DataSetSub( SND_SCENE_CONTEST );

	Snd_BankFlagSet( SND_BANK_CHANGE );							//�o���N�؂�ւ��邩�t���O���Z�b�g
	Snd_BgmPlay( no );											//BGM�Đ�

	/***********************************************************/
	//�b�菈��
	//�R���e�X�g�Ńo�b�O�̉����g�p���Ă���̂Œǉ����[�h���Ă���
	/***********************************************************/
	//Snd_DataSetByScene( SND_SCENE_SUB_BAG, 0, 0 );	// �T�E���h�f�[�^���[�h(�o�b�O)(BGM���p��)

	return;
}

//--------------------------------------------------------------
/**
 * @brief	�C���[�W�N���b�v(�R���e�X�g)��ʂɐ؂�ւ�鎞�̃T�E���h�f�[�^�Z�b�g
 *
 * @param	no		�V�[�P���X�i���o�[
 * @param	flag	"���g�p"
 *
 * @retval	none
 *
 * ���f�[�^���[�h����
 * �풓
 * SE
 * BGM
 *
 * �b��ŁA�o�b�O�̃T�u�V�[�������[�h���Ă���
 */
//--------------------------------------------------------------
void Snd_ConImageDataSet( u16 no, int flag )
{
	int* heap_save_global	= Snd_GetParamAdrs(SND_W_ID_HEAP_SAVE_GLOBAL);

#ifdef SOUND_OS_PRINT_ON
	OS_Printf( "\n���T�E���h�f�[�^���[�h�@�C���[�W�N���b�v(�R���e�X�g)�V�[���؂�ւ�聄\n" );
#endif

	//�菇(1)
	Snd_Stop();													//�S��~

	//���ʏ���
	Snd_DataSetSub( SND_SCENE_CON_IMAGE );

	Snd_BankFlagSet( SND_BANK_CHANGE );							//�o���N�؂�ւ��邩�t���O���Z�b�g
	Snd_BgmPlay( no );											//BGM�Đ�

	return;
}

//--------------------------------------------------------------
/**
 * @brief	BGM�������p���ASE��ǉ����[�h����A�؂�ւ��̃T�E���h�f�[�^�Z�b�g
 *
 * @param	scene		�V�[��
 *
 * @retval	none
 *
 * ���f�[�^���[�h����
 * �풓
 * SE
 * BGM(WAVEARC)
 * ADD_SCENE_SE
 */
//--------------------------------------------------------------
static void Snd_AddSceneSeDataSet( u8 scene )
{
#ifdef SOUND_OS_PRINT_ON
	OS_Printf( "\n���T�E���h�f�[�^���[�h %d �؂�ւ�� �T�u��ʁ�\n", scene );
#endif

	//���ʏ���
	//Snd_DataSetSub( scene );

	Snd_DeleteHeapAfterBgm();										//BGM�̌�������
	Snd_LoadSeByScene( scene );										//SE�V�[�P���X�O���[�v
	Snd_HeapSaveState(Snd_GetParamAdrs(SND_W_ID_HEAP_SAVE_SUB_SE));	//�K�w�ۑ�(�T�u��ʂ̏������)
	return;
}

//--------------------------------------------------------------
/**
 * @brief	�f����ʂɐ؂�ւ�鎞�̃T�E���h�f�[�^�Z�b�g
 *
 * @param	scene	�V�[��
 * @param	no		�V�[�P���X�i���o�[
 * @param	flag	"���g�p"
 *
 * @retval	none
 *
 * ���f�[�^���[�h����
 * �풓
 * SE
 * BGM(SEQ,BANK,WAVEARC)
 */
//--------------------------------------------------------------
static void Snd_DemoDataSet( u8 scene, u16 no, int flag )
{
	int* heap_save_global	= Snd_GetParamAdrs(SND_W_ID_HEAP_SAVE_GLOBAL);

#ifdef SOUND_OS_PRINT_ON
	OS_Printf( "���T�E���h�f�[�^���[�h�@�f���V�[���؂�ւ�聄\n" );
#endif

	//�菇(1)
	Snd_Stop();													//�S��~

	//���ʏ���
	Snd_DataSetSub( scene );

	//Snd_BankFlagSet( SND_BANK_CONTINUE );						//�o���N���̂܂܌p��
	Snd_BgmPlay( no );											//BGM�Đ�

	return;
}

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
void Snd_EyeBgmSet( u16 no )
{
	int ret;
	SND_WORK* wk	= Snd_GetSystemAdrs();

#ifdef SOUND_OS_PRINT_ON
	OS_Printf( "\n���T�E���h�f�[�^���[�h�@�����Ȑ؂�ւ�聄\n" );
#endif

	//BattleDataSet�ŃV�[���̃Z�b�g������̂ŁA
	//���̃^�C�~���O�ŃV�[�����Z�b�g����K�v�͂Ȃ��I

	//�t�B�[���hBGM���|�[�Y���邩�A��~���邩�𔻕ʂ��ď���
	Snd_FieldPauseOrStop();

	//Snd_BankFlagSet( SND_BANK_CONTINUE );						//�o���N���̂܂܌p��
	ret = Snd_BgmPlay( no );									//BGM�Đ�

	return;
}

//--------------------------------------------------------------
/**
 * @brief	�������[�h���Ă��Ȃ���Ԃɂ���(�T�E���h�e�X�g�݂̂Ŏg��)
 *
 * @param	none
 *
 * @retval	none
 */
//--------------------------------------------------------------
void Snd_HeapStateClear(void)
{
	int* heap_save_start = Snd_GetParamAdrs(SND_W_ID_HEAP_SAVE_START);
	Snd_HeapLoadState( *heap_save_start );
	//Snd_HeapSaveState( heap_save_start );		//�K�w�ۑ�(�S�ď������Ɏg�p)
	return;
}


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
void Snd_DeleteHeapAfterBgm( void )
{
	Snd_HeapLoadState( Snd_GetHeapSaveLv(SND_HEAP_SAVE_BGM) );				//BGM�̌�������
	return;
}

//--------------------------------------------------------------
/**
 * @brief	�K�w���x�����擾
 *
 * @param	wk		SND_WORK�^�̃A�h���X
 * @param	type	�K�w���x����`(snd_tool.h�Q��)
 *
 * @retval	"�K�w���x��"
 */
//--------------------------------------------------------------
int Snd_GetHeapSaveLv( int type )
{
	int* heap_save;
	SND_WORK* wk = Snd_GetSystemAdrs();

	if( type >= SND_HEAP_SAVE_MAX ){
		GF_ASSERT( (0) && "�K�w���x�����s���ł��I" );
		heap_save = Snd_GetParamAdrs(SND_W_ID_HEAP_SAVE_BGM);
		return *heap_save;
	}

	switch( type ){
	case SND_HEAP_SAVE_START:
		heap_save = Snd_GetParamAdrs(SND_W_ID_HEAP_SAVE_START);
		break;
	case SND_HEAP_SAVE_GLOBAL:
		heap_save = Snd_GetParamAdrs(SND_W_ID_HEAP_SAVE_GLOBAL);
		break;
	case SND_HEAP_SAVE_BGM_BANK:
		heap_save = Snd_GetParamAdrs(SND_W_ID_HEAP_SAVE_BGM_BANK);
		break;
	case SND_HEAP_SAVE_SE:
		heap_save = Snd_GetParamAdrs(SND_W_ID_HEAP_SAVE_SE);
		break;
	case SND_HEAP_SAVE_BGM:
		heap_save = Snd_GetParamAdrs(SND_W_ID_HEAP_SAVE_BGM);
		break;
	case SND_HEAP_SAVE_SUB_SE:
		heap_save = Snd_GetParamAdrs(SND_W_ID_HEAP_SAVE_SUB_SE);
		break;
	case SND_HEAP_SAVE_ME:
		heap_save = Snd_GetParamAdrs(SND_W_ID_HEAP_SAVE_ME);
		break;
	};

	return *heap_save;
}


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
void Snd_PlayerPause( u8 player, BOOL flag )
{
	u8 handle_no;
	u8* pause_flag;

	if( player == PLAYER_FIELD ){
		pause_flag	= Snd_GetParamAdrs( SND_W_ID_FIELD_PAUSE_FLAG );
		handle_no	= SND_HANDLE_FIELD;

	}else if( player == PLAYER_BGM ){
		pause_flag	= Snd_GetParamAdrs( SND_W_ID_BGM_PAUSE_FLAG );
		handle_no	= SND_HANDLE_BGM;

	}else{
		return;			//�������Ȃ�
	}

	//�ĊJ������̂ŁA����BGM�i���o�[�ɃZ�b�g���Ȃ���
	if( flag == FALSE ){
		Snd_NowBgmNoSet( Snd_GetSeqNo(Snd_HandleGet(handle_no)) );
	}

	NNS_SndPlayerPause( Snd_HandleGet(handle_no), flag );
	*pause_flag = flag;	//�|�[�Y���Ă��邩�t���O
	return;
}

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
void Snd_PauseClearAll()
{
	u8* field_pause_flag	= Snd_GetParamAdrs( SND_W_ID_FIELD_PAUSE_FLAG );
	u8* bgm_pause_flag		= Snd_GetParamAdrs( SND_W_ID_BGM_PAUSE_FLAG );

	//�ǉ����ꂽ���̑Ή��Y����l����Ɣz��Ŏ����Ă����ق����悳����
	//����ȏ�͑����Ȃ��͂������B�B�B
	
	*field_pause_flag = 0;
	*bgm_pause_flag = 0;
	return;
}

//--------------------------------------------------------------
/**
 * @brief	�V�[�P���X�̃{�����[�������X�ɕύX����
 *
 * @param	p		�T�E���h�n���h���̃A�h���X
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
void Snd_PlayerMoveVolume( int handle_no, int vol, int frame )
{
	NNS_SndPlayerMoveVolume( Snd_HandleGet(handle_no), vol, frame );
	return;
}

//--------------------------------------------------------------
/**
 * @brief	�S�ẴV�[�P���X�̃{�����[����ύX����
 *
 * @param	p		�T�E���h�n���h���̃A�h���X
 *
 * @retval	none
 */
//--------------------------------------------------------------
void Snd_AllPlayerMoveVolume( int vol, int frame )
{
	int i;

	for( i=0; i < SND_HANDLE_MAX ;i++ ){
		Snd_PlayerMoveVolume( i, vol, frame );
	}
	return;
}

//--------------------------------------------------------------
/**
 * @brief	�V�[�P���X�̏����{�����[���ݒ�
 *
 * @param	p		�T�E���h�n���h���̃A�h���X
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
void Snd_PlayerSetInitialVolume( int handle_no, int vol )
{
	//�G���[���
	if( vol < 0 ){
		vol = 0;
	}

	if( vol > 127 ){
		vol = 127;
	}

	//���̊֐��́ANNS_SndArcPlayerStartSeq*�֐��� NNS_SndArcPlayerStartSeqArc*�֐�����
	//�Ăт�����Ă��܂��B�ēx�A���̊֐����Ăт����ƁA�ݒ肵���l���㏑������܂��B
	//�㏑���������Ȃ��ꍇ�́A NNS_SndPlayerSetVolume�֐��Ȃǂ��g���Ă��������B
	NNS_SndPlayerSetInitialVolume( Snd_HandleGet(handle_no), vol );
	return;
}

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
void Snd_VChatVolSet( int seq_no, int handle_no )
{
	u8 vol;
	const NNSSndSeqParam* p = NNS_SndArcGetSeqParam( seq_no );	//�V�[�P���X�p�����[�^�擾

	switch( handle_no ){

	//����
	case SND_HANDLE_PMVOICE:
	case SND_HANDLE_CHORUS:
		vol = PV_VOL_MAX;
		break;

	//�����ȊO
	default:
		//�G���[���
		if( p == NULL ){
			return;
		}

		vol = p->volume;
		break;
	};

	//�{�C�X�`���b�g�����`�F�b�N
	if( CommIsVChat() == TRUE ){
		Snd_PlayerSetInitialVolume( handle_no, (vol / SND_VCHAT_VOL_LV) );	//���ʔ���(06.07.20)
	}

	return;
}

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
void Snd_PlayerSetInitialVolumeBySeqNo( u16 no, int vol )
{
	u8 player_no = Snd_GetPlayerNo(no);				//seq�i���o�[����A�v���C���[�i���o�[���擾
	int type = Snd_GetHandleNoByPlayerNo(player_no);//player�i���o�[����A�n���h���i���o�[���擾
	Snd_PlayerSetInitialVolume( type, vol );
	return;
}

//--------------------------------------------------------------
/**
 * @brief	�V�[�P���X���Đ�(�v���C���[�ԍ��w��)
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
BOOL Snd_ArcPlayerStartSeqEx( int handle_no, int player_no, u16 no )
{
	return NNS_SndArcPlayerStartSeqEx( Snd_HandleGet(handle_no), player_no, -1, -1, no );
}


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
 */
//--------------------------------------------------------------
int Snd_PlayerCountPlayingSeq( int player_no )
{
	//����̓`�F�b�N���Ă��Ȃ��̂Œ��ӁI
	if( player_no < 0 ){
		GF_ASSERT( (0) && "�������s���ł��I" );
	}

	return NNS_SndPlayerCountPlayingSeqByPlayerNo( player_no );
}

//--------------------------------------------------------------
/**
 * @brief	�V�[�P���X�i���o�[����v���C���[�i���o�[�擾
 *
 * @param	no		�V�[�P���X�i���o�[
 *
 * @retval	"�v���C���[�i���o�[�A0xff=�擾���s"
 */
//--------------------------------------------------------------
u8 Snd_GetPlayerNo( u16 no )
{
	const NNSSndSeqParam* param;
	
	if( no == 0 ){
		//GF_ASSERT( (0) && "�V�[�P���X�i���o�[���s���Ȃ̂Ńv���C���[�i���o�[�擾���s�I" );
		return 0xff;	//�G���[
	}

	//�T�E���h�A�[�J�C�u���̊e�V�[�P���X�ɑ΂���A�V�[�P���X�p�����[�^�\���̂��擾
	param = NNS_SndArcGetSeqParam( no );
	//OS_Printf( "�v���C���[�i���o�[ = %d\n", param->playerNo );

	if( param == NULL ){
		//GF_ASSERT( (0) && "�V�[�P���X�i���o�[���s���Ȃ̂Ńv���C���[�i���o�[�擾���s�I" );
		OS_Printf( "�V�[�P���X�i���o�[���s���Ȃ̂Ńv���C���[�i���o�[�擾���s�I\n" );
		return 0xff;	//�G���[
	}

	return param->playerNo;
}

//--------------------------------------------------------------
/**
 * @brief	�T�E���h�n���h������V�[�P���X�i���o�[���擾
 *
 * @param	p			�T�E���h�n���h���̃A�h���X
 *
 * @retval	"�V�[�P���X�i���o�[�A�ݒ肳��Ă��Ȃ�����-1"
 */
//--------------------------------------------------------------
int Snd_GetSeqNo( NNSSndHandle *p )
{
	return NNS_SndPlayerGetSeqNo( p );
}


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
const NNSSndArcBankInfo* Snd_GetBankInfo( int no )
{
	const NNSSndArcBankInfo* info;

	info = NNS_SndArcGetBankInfo( Snd_GetBankNo(no) );

	//�������`�F�b�N
	if( info == NULL ){
		OS_Printf( "�o���N���\���̂̃A�h���X���擾�o���܂���ł����B\n" );
	}

	return info;
}

//--------------------------------------------------------------
/**
 * @brief	�V�[�P���X�i���o�[����o���N�i���o�[�擾
 *
 * @param	no		�V�[�P���X�i���o�[
 *
 * @retval	"0=�G���[�A0�ȊO=�o���N�i���o�["
 */
//--------------------------------------------------------------
u16 Snd_GetBankNo( int no )
{
	const NNSSndSeqParam* param;
	
	//�T�E���h�A�[�J�C�u���̊e�V�[�P���X�ɑ΂���A�V�[�P���X�p�����[�^�\���̂��擾
	param = NNS_SndArcGetSeqParam( no );
	if( param == NULL ){
		OS_Printf( "�o���N�i���o�[���擾�o���܂���ł����B\n" );
		OS_Printf( "�n���ꂽ�V�[�P���X�i���o�[�� %d �ł��B\n", no );
		return 0;
	}

	return param->bankNo;
}


//==============================================================================================
//
//	�}�C�N�֘A
//
//==============================================================================================
      
//--------------------------------------------------------------
/**
 * @brief	�}�C�N�R�[���o�b�N�֐�
 *
 * @param	none
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void MicCallback( MICResult /*result*/, void* /*arg*/ )
{
    OS_Printf( "Mic Callback Done\n" );
}

//--------------------------------------------------------------
/**
 * @brief	�^���J�n
 *
 * @param	p		MICAutoParam�^�̃A�h���X
 *
 * @retval	"MIC_RESULT_SUCCESS		����������Ɋ���"
 * @retval	"����ȊO				���炩�̌����Ŏ��s"
 */
//--------------------------------------------------------------
MICResult Snd_MicStartAutoSampling( MICAutoParam* p )
{
	MICResult ret;

	ret = MIC_StartAutoSampling( p );

	if( ret != MIC_RESULT_SUCCESS ){
		OS_Printf( "�}�C�N�����T���v�����O�J�n�����s���܂����I\n" );
	}

	return ret;
}

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
MICResult Snd_MicStopAutoSampling(void)
{
	MICResult ret;
	SND_WORK* wk = Snd_GetSystemAdrs();

	ret = MIC_StopAutoSampling();

	if( ret != MIC_RESULT_SUCCESS ){
		OS_Printf( "�}�C�N�����T���v�����O��~�����s���܂����I\n" );
	}

	return ret;
}

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
MICResult Snd_MicManualSampling(MICSamplingType type ,void* heap,MICCallback callback,void* arg)
{
	MICResult ret;

    ret = MIC_DoSamplingAsync( type, heap, callback, arg);
	if( ret != MIC_RESULT_SUCCESS ){
        OS_Printf( "�}�C�N�蓮�T���v�����O�����s\n" );
	}
	return ret;
}

//==============================================================================================
//
//	�g�`�Đ��֘A
//
//==============================================================================================

//--------------------------------------------------------------
/**
 * @brief	�g�`�n���h���̃A�h���X���擾
 *
 * @param	no		�g�p���Ă���`�����l���i���o�[
 *
 * @retval	"�g�`�n���h���̃A�h���X"
 *
 * BGM		NNSSndHandle
 * �g�`		NNSSndWaveOutHandle
 * �n���h���̃^�C�v���Ⴄ�̂Œ��ӁI
 */
//--------------------------------------------------------------
NNSSndWaveOutHandle * Snd_WaveOutHandleGet( u32 no )
{
	SND_WORK* wk = Snd_GetSystemAdrs();
	u8* ch_normal_flag = Snd_GetParamAdrs(SND_W_ID_WAVEOUT_CH_NORMAL_FLAG);
	u8* ch_chorus_flag = Snd_GetParamAdrs(SND_W_ID_WAVEOUT_CH_CHORUS_FLAG);

	if( (no != WAVEOUT_CH_NORMAL) && (no != WAVEOUT_CH_CHORUS) ){
		GF_ASSERT( (0) && "�`�����l���i���o�[���s���ł��I" );
	}

	if( (no == WAVEOUT_CH_NORMAL) && (*ch_normal_flag == 0) ){	//�m�ۃt���O��OFF��������
		GF_ASSERT( (0) && "�m�ۂ��Ă��Ȃ�NORMAL�n���h���ɃA�N�Z�X���Ă��܂��I" );
	}

	if( (no == WAVEOUT_CH_CHORUS) && (*ch_chorus_flag == 0) ){	//�m�ۃt���O��OFF��������
		GF_ASSERT( (0) && "�m�ۂ��Ă��Ȃ�CHORUS�n���h���ɃA�N�Z�X���Ă��܂��I" );
	}

	if( no == WAVEOUT_CH_NORMAL ){
		return Snd_GetParamAdrs(SND_W_ID_WAVEOUT_HANDLE_NORMAL);
	}else{
		return Snd_GetParamAdrs(SND_W_ID_WAVEOUT_HANDLE_CHORUS);
	}
}
 
//--------------------------------------------------------------
/**
 * @brief	�g�`�Đ��p�Ƀ`�����l�����m�ۂ���
 *
 * @param	no		�g�p����`�����l���i���o�[
 *
 * @retval	BOOL	TRUE=�����AFALSE=���s
 */
//--------------------------------------------------------------
BOOL Snd_WaveOutAllocChannel( u32 no )
{
	u8* ch_normal_flag;
	u8* ch_chorus_flag;
	NNSSndWaveOutHandle* wave_handle;
	SND_WORK* wk = Snd_GetSystemAdrs();

	ch_normal_flag = Snd_GetParamAdrs(SND_W_ID_WAVEOUT_CH_NORMAL_FLAG);
	ch_chorus_flag = Snd_GetParamAdrs(SND_W_ID_WAVEOUT_CH_CHORUS_FLAG);

	if( (no != WAVEOUT_CH_NORMAL) && (no != WAVEOUT_CH_CHORUS) ){
		GF_ASSERT( (0) && "�`�����l���i���o�[���s���ł��I" );
	}

	if( no == WAVEOUT_CH_NORMAL ){

		if( *ch_normal_flag == 0 ){		//�m�ۃt���O��OFF��������

			//�g�`�n���h���̃A�h���X�擾
			wave_handle = Snd_GetParamAdrs(SND_W_ID_WAVEOUT_HANDLE_NORMAL);
			*wave_handle = NNS_SndWaveOutAllocChannel( no );			//CH�m��

			if ( *wave_handle == NNS_SND_WAVEOUT_INVALID_HANDLE ) {
				OS_Printf("NNS_SndWaveOutAllocChannel is Failed\n");
				return FALSE;			//���s
			}
			*ch_normal_flag = 1;		//�m�ۃt���OON
		}else{
			GF_ASSERT( (0) && "�`�����l�����J�����Ă��Ȃ��̂ɁA�m�ۂ��悤�Ƃ��Ă��܂��I" );
		}

	}else{

		if( *ch_chorus_flag == 0 ){		//�m�ۃt���O��OFF��������

			wave_handle = Snd_GetParamAdrs(SND_W_ID_WAVEOUT_HANDLE_CHORUS);
			*wave_handle = NNS_SndWaveOutAllocChannel( no );			//CH�m��

			if ( *wave_handle == NNS_SND_WAVEOUT_INVALID_HANDLE ) {
				OS_Printf("NNS_SndWaveOutAllocChannel is Failed\n");
				return FALSE;			//���s
			}
			*ch_chorus_flag = 1;		//�m�ۃt���OON
		}else{
			GF_ASSERT( (0) && "�`�����l�����J�����Ă��Ȃ��̂ɁA�m�ۂ��悤�Ƃ��Ă��܂��I" );
		}
	}

	return TRUE;		//����
}
 
//--------------------------------------------------------------
/**
 * @brief	�g�`�Đ��p�̃`�����l�����������
 *
 * @param	no		�g�p����`�����l���i���o�[
 *
 * @retval	none
 */
//--------------------------------------------------------------
void Snd_WaveOutFreeChannel( u32 no )
{
	NNSSndWaveOutHandle* wave_handle;
	SND_WORK* wk		= Snd_GetSystemAdrs();
	u8* ch_normal_flag	= Snd_GetParamAdrs(SND_W_ID_WAVEOUT_CH_NORMAL_FLAG);
	u8* ch_chorus_flag	= Snd_GetParamAdrs(SND_W_ID_WAVEOUT_CH_CHORUS_FLAG);

	if( (no != WAVEOUT_CH_NORMAL) && (no != WAVEOUT_CH_CHORUS) ){
		GF_ASSERT( (0) && "�`�����l���i���o�[���s���ł��I" );
		return;
	}

	if( no == WAVEOUT_CH_NORMAL ){
		if( *ch_normal_flag == 1 ){	//�m�ۃt���O��ON��������

			wave_handle = Snd_WaveOutHandleGet(no);
			NNS_SndWaveOutFreeChannel( *wave_handle );
			*ch_normal_flag = 0;	//�m�ۃt���OOFF

		}else{
			GF_ASSERT( (0) && "�m�ۂ���Ă��Ȃ��`�����l�����J�����悤�Ƃ��Ă��܂��I" );
		}
	}else{
		if( *ch_chorus_flag == 1 ){	//�m�ۃt���O��ON��������

			wave_handle = Snd_WaveOutHandleGet(no);
			NNS_SndWaveOutFreeChannel( *wave_handle );
			*ch_chorus_flag = 0;	//�m�ۃt���OOFF

		}else{
			GF_ASSERT( (0) && "�m�ۂ���Ă��Ȃ��`�����l�����J�����悤�Ƃ��Ă��܂��I" );
		}
	}

	return;
}

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
BOOL Snd_WaveOutStart( WAVEOUT_WORK* p, u32 ch )
{
	int ret;

	ret = NNS_SndWaveOutStart( *p->handle, p->format, p->dataaddr, p->loopFlag, p->loopStartSample,
								p->samples, p->sampleRate, p->volume, p->speed, p->pan );

	if( ret == FALSE ){
		OS_Printf( "�g�`�Đ����s�I\n" );

		//���̊֐����Ă΂�鎞�́A�K���`�����l���m�ۂ��Ă���͂��Ȃ̂ŁA
		//�Đ��Ɏ��s�������́A�J������������悤�ɂ���I
		Snd_WaveOutFreeChannel( ch );
	}

	return ret;
}

//--------------------------------------------------------------
/**
 * @brief	�g�`��~
 *
 * @param	no		�g�p����`�����l���i���o�[
 *
 * @retval	none
 */
//--------------------------------------------------------------
void Snd_WaveOutStop( u32 no )
{
	NNS_SndWaveOutStop( *Snd_WaveOutHandleGet(no) );
	return;
}

//--------------------------------------------------------------
/**
 * @brief	�g�`�Đ������`�F�b�N
 *
 * @param	no		�g�p����`�����l���i���o�[
 *
 * @retval	BOOL	TRUE=�Đ����AFALSE=�Đ����łȂ�
 */
//--------------------------------------------------------------
BOOL Snd_WaveOutIsPlaying( u32 no )
{
	return NNS_SndWaveOutIsPlaying( *Snd_WaveOutHandleGet(no) );
}

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
void Snd_WaveOutSetPan( u32 no, u8 pan )
{
	u8 set_pan;

	if( pan > 127 ){
		set_pan = 127;
	}else{
		set_pan = pan;
	}

	NNS_SndWaveOutSetPan( *Snd_WaveOutHandleGet(no), set_pan );
	return;
}

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
 *
 * �Đ��X�s�[�h�𑬂�����ƁA�Đ����Ԃ��Z���Ȃ�A�Đ�����鉹�̍����������Ȃ�܂��B 
 */
//--------------------------------------------------------------
void Snd_WaveOutSetSpeed( u32 no, u32 spd )
{
	NNS_SndWaveOutSetSpeed( *Snd_WaveOutHandleGet(no), spd );
	return;
}

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
void Snd_WaveOutSetVolume( u32 no, int vol )
{
	//�{�C�X�`���b�g�����`�F�b�N
	if( CommIsVChat() == TRUE ){
		NNS_SndWaveOutSetVolume( *Snd_WaveOutHandleGet(no), (vol/SND_VCHAT_VOL_LV) );	//���ʑ���
	}else{
		NNS_SndWaveOutSetVolume( *Snd_WaveOutHandleGet(no), vol );
	}
	return;
}
 

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
 * Snd_WaveOutStopReverse(...)���Ă�ŁA�o�b�t�@���J�����Ă��������B
 *
 * �|�P�����i���o�[�Ɩ����̔g�`�A�[�J�C�u�i���o�[�������ɂȂ�悤�ɂ���I
 */
//--------------------------------------------------------------
BOOL Snd_WaveOutStartReverse( u16 no, int vol, int pan, u32 ch, int heap_id )
{
	u8* reverse_flag;
	const NNSSndArcWaveArcInfo* info;
	u32 size;
	int size2,ret;
	SND_WORK* wk = Snd_GetSystemAdrs();
	void** reverse_buf = Snd_GetParamAdrs(SND_W_ID_REVERSE_BUF);

	if( (ch != WAVEOUT_CH_NORMAL) && (ch != WAVEOUT_CH_CHORUS) ){
		GF_ASSERT( (0) && "�`�����l���i���o�[���s���ł��I" );
	}

	//�g�`�A�[�J�C�u���\����NNSSndArcWaveArcInfo�̃|�C���^��Ԃ��܂��B
	//info =  NNS_SndArcGetWaveArcInfo( WAVE_ARC_PV001 );
	info = NNS_SndArcGetWaveArcInfo( no );
	if( info == NULL ){
		GF_ASSERT( (0) && "�����Ȕg�`�A�[�J�C�u�ԍ����w�肳��܂����I" );
		return FALSE;
	}

	//�t�@�C���T�C�Y�擾
	size = NNS_SndArcGetFileSize( info->fileId );
	if( size == 0 ){
		GF_ASSERT( (0) && "�t�@�C��ID�������ł��I" );
		return FALSE;
	}
	OS_Printf( "�t�@�C���T�C�Y = %d\n", size );	//.smap�Ɣ�r���Ă݂�

	//�ʏ�̋t�Đ���������
	if( ch == WAVEOUT_CH_NORMAL ){
		//�o�b�t�@�m��
		*reverse_buf = sys_AllocMemory( heap_id, size );
		if( *reverse_buf == NULL ){
			GF_ASSERT( (0) && "�������m�ۂɎ��s���܂����I" );
			return FALSE;
		}
		memset( *reverse_buf, 0, size );

		//�T�E���h�A�[�J�C�u���̃t�@�C����ǂݍ���
		size2 = NNS_SndArcReadFile( info->fileId, *reverse_buf, size, 0 );
		if( size2 == -1 ){
			GF_ASSERT( (0) && "�ǂݍ��݂Ɏ��s���܂����I" );
			return FALSE;
		}

		//�f�[�^�����ւ���
		Snd_BufReverse( *reverse_buf, size );
	}

	//WAVEOUT_WORK�^�Ƀp�����[�^�Z�b�g
	{
		WAVEOUT_WORK waveout_wk;
		waveout_wk.handle			= Snd_WaveOutHandleGet(ch);	//�g�`�Đ��n���h��
		waveout_wk.format			= NNS_SND_WAVE_FORMAT_PCM8;	//�g�`�f�[�^�t�H�[�}�b�g
		waveout_wk.dataaddr			= *reverse_buf;				//�g�`�f�[�^�̐擪�A�h���X
		waveout_wk.loopFlag			= FALSE;					//���[�v�t���O
		waveout_wk.loopStartSample	= 0;						//���[�v�J�n�T���v���ʒu
		waveout_wk.samples			= size;						//�g�`�f�[�^�̃T���v����
		waveout_wk.sampleRate		= 13379;					//�g�`�f�[�^�̃T���v�����O���[�g
		waveout_wk.volume			= vol;						//����
		waveout_wk.speed			= 24576;					//�Đ��X�s�[�h
		waveout_wk.pan				= pan;						//�p��(0-127)

		//�g�`�Đ�
		ret = Snd_WaveOutStart( &waveout_wk, ch );

		//�{�C�X�`���b�g�̉��ʑΉ�
		Snd_WaveOutSetVolume( ch, vol );

		//BANK�̐ݒ��"PCM8"�ɂ���Ƃ��܂�����
	}

	reverse_flag = Snd_GetParamAdrs( SND_W_ID_REVERSE_FLAG );
	*reverse_flag = 1;	//�t�Đ��g�p�t���OON

	return ret;
}

//--------------------------------------------------------------
/**
 * @brief	�f�[�^�����ւ���
 *
 * @param	p		�g�`�f�[�^���i�[�����o�b�t�@�̃|�C���^
 * @param	size	�g�`�f�[�^�T�C�Y
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void Snd_BufReverse( u8* p, u32 size )
{
	int i;
	u8 temp;

	//�f�[�^�����ւ���( [0]-[MAX]�A[1]-[MAX-1]... )
	for( i=0; i < (size / 2) ;i++ ){
		temp		= p[i];			//�ޔ�
		p[i]		= p[size-1-i];
		p[size-1-i]	= temp;
	}

	return;
}

//--------------------------------------------------------------
/**
 * @brief	�t�Đ��̃|�P�����������~���ăo�b�t�@���J������
 *
 * @param	no		�g�p����`�����l���i���o�[
 *
 * @retval	none
 */
//--------------------------------------------------------------
void Snd_WaveOutStopReverse( u32 no )
{
	SND_WORK* wk		= Snd_GetSystemAdrs();
	u8* reverse_flag	= Snd_GetParamAdrs(SND_W_ID_REVERSE_FLAG);
	void** reverse_buf	= Snd_GetParamAdrs(SND_W_ID_REVERSE_BUF);

	if( (no != WAVEOUT_CH_NORMAL) && (no != WAVEOUT_CH_CHORUS) ){
		GF_ASSERT( (0) && "�`�����l���i���o�[���s���ł��I" );
	}

	Snd_WaveOutStop( no );										//������~

	//�t�Đ��g�p�t���O
	if( *reverse_flag == 1 ){									//�t�Đ��g�p�t���O�������Ă�����
		*reverse_flag = 0;										//�t�Đ��g�p�t���OOFF
		sys_FreeMemoryEz( *reverse_buf );						//�o�b�t�@�J��
	}

	return;
}


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
 * �L���v�`���[�X���b�h���N�����Ă����ƁA�L���v�`���[������IRQ�n���h���ł͂Ȃ��A
 * �L���v�`���[�X���b�h�ŏ��������悤�ɂȂ�܂��B 
 *
 * �X���b�h�̗D��xthreadPrio�́A�ʏ�A�X�g���[���X���b�h���������ݒ肵�܂��B
 * �������x���ƁA����ȍĐ����s���Ȃ��Ȃ�܂��̂ŁA���ӂ��Ă��������B 
 */
//--------------------------------------------------------------
void Snd_CaptureCreateThread(void)
{
    NNS_SndCaptureCreateThread( CAPTURE_THREAD_PRIO );
	return;
}

//--------------------------------------------------------------
/**
 * @brief	�L���v�`�������s�����擾
 *
 * @param	none
 *
 * @retval	"TRUE=���s���AFALSE=���s���Ă��Ȃ�"
 */
//--------------------------------------------------------------
BOOL Snd_CaptureIsActive(void)
{
	int type,ret;

	ret = NNS_SndCaptureIsActive();

#ifdef SOUND_OS_PRINT_ON
	OS_Printf( "�L���v�`�����L�����H = %d\n", ret );

	//�L����������A�L���v�`���^�C�v��\��
	if( ret == TRUE ){
		type = Snd_CaptureGetCaptureType();

		if( type == NNS_SND_CAPTURE_TYPE_REVERB ){
			OS_Printf( "���݂̃L���v�`���́ANNS_SND_CAPTURE_TYPE_REVERB\n" );
		}else if( type == NNS_SND_CAPTURE_TYPE_EFFECT ){
			OS_Printf( "���݂̃L���v�`���́ANNS_SND_CAPTURE_TYPE_EFFECT\n" );
		}else if( type == NNS_SND_CAPTURE_TYPE_SAMPLING ){
			OS_Printf( "���݂̃L���v�`���́ANNS_SND_CAPTURE_TYPE_SAMPLING\n" );
		}
	}
#endif

	return ret;
}

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
NNSSndCaptureType Snd_CaptureGetCaptureType(void)
{
	return NNS_SndCaptureGetCaptureType();
}

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
void Snd_CaptureChangeOutputEffect( NNSSndCaptureOutputEffectType type )
{
	switch( type ){
	case NNS_SND_CAPTURE_OUTPUT_EFFECT_NORMAL:
	case NNS_SND_CAPTURE_OUTPUT_EFFECT_MONO:
	case NNS_SND_CAPTURE_OUTPUT_EFFECT_SURROUND:
	case NNS_SND_CAPTURE_OUTPUT_EFFECT_HEADPHONE:
		break;
	default:
		return;	//�������Ȃ�
	}

    NNS_SndCaptureChangeOutputEffect( type );
	return;
}
 

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
void Snd_CaptureStartOutputEffect( NNSSndCaptureOutputEffectType type )
{
	SND_WORK* wk	= Snd_GetSystemAdrs();
	s8* capture_buf = Snd_GetParamAdrs(SND_W_ID_CAPTURE_BUF);

	switch( type ){
	case NNS_SND_CAPTURE_OUTPUT_EFFECT_NORMAL:
	case NNS_SND_CAPTURE_OUTPUT_EFFECT_MONO:
	case NNS_SND_CAPTURE_OUTPUT_EFFECT_SURROUND:
	case NNS_SND_CAPTURE_OUTPUT_EFFECT_HEADPHONE:
		//NNS_SndCaptureStartOutputEffect( wk->sCaptureBuffer, sizeof( wk->sCaptureBuffer ), type );
		NNS_SndCaptureStartOutputEffect( capture_buf, CAPTURE_BUFSIZE, type );
		break;
	}

	return;
}

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
BOOL Snd_CaptureStartReverb( int vol )
{
	SND_WORK* wk	= Snd_GetSystemAdrs();
	s8* capture_buf = Snd_GetParamAdrs(SND_W_ID_CAPTURE_BUF);

	//return NNS_SndCaptureStartReverb( wk->sCaptureBuffer, sizeof( wk->sCaptureBuffer ),
	return NNS_SndCaptureStartReverb( capture_buf, CAPTURE_BUFSIZE,
										CAPTURE_FORMAT, REVERB_SAMPLING_RATE, vol );

	//���o�[�u�o�b�t�@���傫���قǁA�x�����Ԃ������Ȃ�A�[�����o�[�u��������܂��B
	//�T���v�����O���[�g�́A�l���傫���قǃ��o�[�u�����̉����͗ǂ��Ȃ�܂����A
	//���̕��x�����Ԃ͒Z���Ȃ�܂��B�x�����Ԃ�ς������Ȃ��ꍇ�́A
	//���o�[�u�o�b�t�@�T�C�Y��傫������K�v������܂��B
	//�x�����ԁ�bufsize / samplerate;
}

//--------------------------------------------------------------
/**
 * @brief	���o�[�u�@�I��
 *
 * @param	frame	�t���[����
 *
 * @retval	none
 */
//--------------------------------------------------------------
void Snd_CaptureStopReverb( int frame )
{
	NNS_SndCaptureStopReverb( frame );
	return;
}

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
void Snd_CaptureReverbVol( int vol, int frame )
{
	NNS_SndCaptureSetReverbVolume( vol, frame );
	return;
}

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
BOOL Snd_CaptureStartEffect(void)
{
	SND_WORK* wk				= Snd_GetSystemAdrs();

	//MI_CpuClear8( &wk->callbackInfo, sizeof(wk->callbackInfo) );
	MI_CpuClear8( Snd_GetParamAdrs(SND_W_ID_CALLBACK_INFO), sizeof(EffectCallbackInfo) );

/*
	//return NNS_SndCaptureStartEffect( wk->sCaptureBuffer, sizeof( wk->sCaptureBuffer ),
	return NNS_SndCaptureStartEffect( wk->sCaptureBuffer, CAPTURE_BUFSIZE,
				CAPTURE_FORMAT, SAMPLING_RATE, 2, EffectCallback, &wk->callbackInfo );
*/

	//-----------------------------------------------------
	//�T���v�����O���[�g���Ⴂ�ƁA�L���v�`���@�\���g�����ɁA
	//�������H���Ă��Ȃ��Ă��A���������Ȃ�̂Œ��ӁI
	//-----------------------------------------------------

#if 1
	//return NNS_SndCaptureStartEffect( Snd_GetParamAdrs(SND_W_ID_CAPTURE_BUF),CAPTURE_BUFSIZE,
	//									CAPTURE_FORMAT, SAMPLING_RATE,2, 
	//								EffectCallback, Snd_GetParamAdrs(SND_W_ID_CALLBACK_INFO) );

	//�e�X�g��(06.02.24)
	return NNS_SndCaptureStartEffect( Snd_GetParamAdrs(SND_W_ID_CAPTURE_BUF),CAPTURE_BUFSIZE,
										//NNS_SND_CAPTURE_FORMAT_PCM16, 16000,2, 
										NNS_SND_CAPTURE_FORMAT_PCM16, 22000,2, 
									EffectCallback2, Snd_GetParamAdrs(SND_W_ID_CALLBACK_INFO) );
#else
	 //start sampling
    (void)NNS_SndCaptureStartSampling( Snd_GetParamAdrs(SND_W_ID_CAPTURE_BUF),CAPTURE_BUFSIZE,
										CAPTURE_FORMAT,SAMPLING_RATE,2,
										SamplingCallback,NULL );
	return 0;
#endif
}

//--------------------------------------------------------------
/**
 * @brief	�G�t�F�N�g��~
 *
 * @param	none
 *
 * @retval	none
 */
//--------------------------------------------------------------
void Snd_CaptureStopEffect(void)
{
	NNS_SndCaptureStopEffect();
	return;
}

//--------------------------------------------------------------
/**
 * @brief	�G�t�F�N�g���x���̑���
 *
 * @param	level	���x��(0-8)
 *
 * @retval	none
 */
//--------------------------------------------------------------
void Snd_CaptureEffectLevel( int level )
{
	u8* filter_size = Snd_GetParamAdrs(SND_W_ID_FILTER_SIZE);
	//���Ή�
	
	if( level > 8 ){
		level = 8;
	}else if( level < 0 ){
		level = 0;
	}

	*filter_size = level;
	return;
}
 
//--------------------------------------------------------------
/**
 * @brief	�G�t�F�N�g�̃R�[���o�b�N�֐�
 *
 * @param	bufferL_p	L�~�L�T�[����
 * @param	bufferR_p	R�~�L�T�[����
 * @param	len			�o�b�t�@�̃T�C�Y
 * @param	format		NNS_SndCaptureStartEffect�֐��̈���(CAPTURE_FORMAT)�Ɠ������̂��n�����
 * @param	arg			NNS_SndCaptureStartEffect�֐��̈���(callbackInfo)�Ɠ������̂��n�����
 *
 * @retval	none
 *
 * �ȒP�ȃ��[�p�X�t�B���^�i�ړ����ρj�������ďo�͂��Ă���
 *
 * �����Ԃ̊Ԋu���߁A���̊Ԋu���̕��ϒl��A�����Čv�Z���邱�Ƃɂ����
 * ����(��������)�I�ȓ�����m�낤�Ƃ�����́B
 * (��������ւƓ������� )
 */
//--------------------------------------------------------------
static void EffectCallback( void* bufferL_p, void* bufferR_p, u32 len, NNSSndCaptureFormat format, void* arg )
{
    smp_t* lp = (smp_t*)bufferL_p;
    smp_t* rp = (smp_t*)bufferR_p;
    EffectCallbackInfo* info = (EffectCallbackInfo*)arg;
    smp_t org[ FILTER_SIZE-1 ][2];

    int samples;
    int x;
    int i, j;
    
	//�T���v����8�r�b�gPCM�͂��̂܂�
	//�T���v����16�r�b�gPCM��������o�b�t�@�̃T�C�Y�𔼕��ɂ���
    samples = ( format == NNS_SND_CAPTURE_FORMAT_PCM8 ) ? len : ( len >> 1 );

#ifdef SOUND_OS_PRINT_ON
	OS_Printf( "\nSND_EFF=================================\n" );
	OS_Printf( "format = %d\n", format );			//0
	OS_Printf( "len = %d\n", len );					//1024
	OS_Printf( "samples = %d\n", samples );			//512
#endif
    
	//--------------------------------------------
	//�� �o�b�t�@�T�C�Y = 24 �t�B���^�[�T�C�Y = 8
	//lp[0+24-8+1]=17
	//17,18,19,20,21,22,23��ۑ�
	//--------------------------------------------
    //�o�b�t�@�̈�Ԍ�납��A�t�B���^�[�T�C�Y����ۑ�
    for( i = 0; i < FILTER_SIZE-1; i++ ) {
        org[i][0] = lp[ i + samples - FILTER_SIZE + 1 ];
        org[i][1] = rp[ i + samples - FILTER_SIZE + 1 ];
		OS_Printf( "org[i][��] = %d\n", org[i][0] );
    }
    
	//--------------------------------------------
	//�� �o�b�t�@�T�C�Y = 24 �t�B���^�[�T�C�Y = 8
    //for( i = 24 - 1; i >= 8 - 1 ; i-- ){
	//23...8�܂ŏ�������
	//--------------------------------------------
	//�o�b�t�@�̈�Ԍ�납��A�t�B���^�[�T�C�Y�̒l��菬�����Ȃ�܂ŏ�������
    for( i = samples - 1; i >= FILTER_SIZE - 1 ; i-- ){

		//--------------------------------------------
		//�� �o�b�t�@�T�C�Y = 24 �t�B���^�[�T�C�Y = 8
		//x += lp[ 23 - 0 ];
		//(-0����-7�܂�)
		//x += lp[ 23 - 7 ];
		//�t�B���^�[�T�C�Y�������Ă���
		//--------------------------------------------
		//L�~�L�T�[����
        x = 0;
        for( j = 0 ; j < FILTER_SIZE ; j++ ) {	//�t�B���^�[�T�C�Y�������Ă���
            x += lp[ i - j ];
        }
        lp[ i ] = (smp_t)(x /= FILTER_SIZE);	//�t�B���^�[�T�C�Y�Ŋ��蕽�ςŏ㏑������
        
		//R�~�L�T�[����
        x = 0;
        for( j = 0 ; j < FILTER_SIZE ; j++ ) {	//�t�B���^�[�T�C�Y�������Ă���
            x += rp[ i - j ];
        }
        rp[ i ] = (smp_t)(x /= FILTER_SIZE);	//�t�B���^�[�T�C�Y�Ŋ��蕽�ςŏ㏑������
    }
    
#if FILTER_SIZE >= 2    
	//--------------------------------------------
	//�� �o�b�t�@�T�C�Y = 24 �t�B���^�[�T�C�Y = 8
    //for( i = 8 - 2; i >= 0 ; i-- ){
	//6...0�܂ŏ�������
	//--------------------------------------------
    for( i = FILTER_SIZE - 2 ; i >= 0 ; i-- ){

		//L�~�L�T�[����
        x = lp[ i ];
        for( j = 1 ; j < FILTER_SIZE ; j++ ) {	//�t�B���^�[�T�C�Y��
            x += GetSample( lp, i-j, 0, info );
        }
        lp[ i ] = (smp_t)(x /= FILTER_SIZE);	//�t�B���^�[�T�C�Y�Ŋ��蕽�ςŏ㏑������
        
		//R�~�L�T�[����
        x = rp[ i ];
        for( j = 1 ; j < FILTER_SIZE ; j++ ) {
            x += GetSample( rp, i-j, 1, info );
        }
        rp[ i ] = (smp_t)(x /= FILTER_SIZE);	//�t�B���^�[�T�C�Y�Ŋ��蕽�ςŏ㏑������
    }
#endif
    
	//�L���v�`�������������̈�̃t�B���^�T�C�Y����
	//�ۑ����Ă������f�[�^�ŏ㏑������
	//(�o�b�t�@�̈�Ԍ�납��A�t�B���^�[�T�C�Y����ۑ����Ă������f�[�^)
    for( i = 0; i < FILTER_SIZE-1; i++ ) {
        info->sample[i][0] = org[i][0];
        info->sample[i][1] = org[i][1];
    }

	//���C���������Ɋm���ɏ�������
    DC_FlushRange( bufferL_p, len );
    DC_FlushRange( bufferR_p, len );

	//�����ɓn�����o�b�t�@�́A(���̊֐����ł�info)
	//�L���v�`�������������̈���w���Ă��܂��B
	//���̗̈���C�����邱�ƂŁA���ۂɏo�͂���鉹��ύX���邱�Ƃ��ł��܂��B 
}
 
//--------------------------------------------------------------
/**
 * @brief	�T���v���̒l�擾
 *
 * @param	p			�~�L�T�[����
 * @param	x			i-j
 * @param	n
 * @param	info		NNS_SndCaptureStartEffect�֐��̈���(callbackInfo)�Ɠ������̂��n�����
 *
 * @retval	none
 */
//--------------------------------------------------------------
static inline smp_t GetSample( smp_t* p, int x, int n, const EffectCallbackInfo* info )
{
	//i-j��0�ȏ�̎��́A�~�L�T�[�����̒l�����̂܂ܕԂ�
    if ( x >= 0 ){
		return p[x];
	}

	//i-j��0�����̎��Ax(i-j)�̒l�𒲐������l���擾
    x += FILTER_SIZE-1;
    return info->sample[x][n];
}

static inline int abs( int x )
{
    return x >= 0 ? x : -x;
}

void SamplingCallback( void* bufferL_p, void* bufferR_p, u32 len, NNSSndCaptureFormat format, void* arg )
{
#pragma unused( arg )    
    smp_t* lp = (smp_t*)bufferL_p;
    smp_t* rp = (smp_t*)bufferR_p;
    u32 samples;
    long sum = 0;
    int i;
    
    samples = ( format == NNS_SND_CAPTURE_FORMAT_PCM8 ) ? len : ( len >> 1 );
    
    for( i = 0 ; i < samples ; i++ ) {
        sum += abs( lp[ i ] ) + abs( rp[ i ] );
    }

    sum /= samples * 2;

#if 1
    //for( i = 0 ; i < samples ; i++ ) {
	//	if( sum < ( abs(lp[i]) + abs(rp[i]) ) ){
			//lp[i] = lp[i] - (sum/10);
			//rp[i] = rp[i] - (sum/10);
	//		lp[i] = sum;
	//		rp[i] = sum;
	//	}
    //}
    for( i = 0 ; i < samples ; i++ ) {
		lp[i] += 1000;
		rp[i] += 1000;
	}

   	//���C���������Ɋm���ɏ�������
    DC_FlushRange( bufferL_p, len );
    DC_FlushRange( bufferR_p, len );
#endif
 
    OS_Printf("output level : %5d\n", sum );
}


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
void Snd_PlayerSetTrackMute( int handle_no, u16 bitmask, BOOL flag )
{
	NNS_SndPlayerSetTrackMute( Snd_HandleGet(handle_no), bitmask, flag );
	return;
}

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
void Snd_PlayerSetTrackVolume( NNSSndHandle *p, u16 bitmask, int vol )
{
	NNS_SndPlayerSetTrackVolume( p, bitmask, vol );
	return;
}

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
void Snd_PlayerSetTrackPitch( int handle_no, u16 bitmask, int pitch )
{
	NNS_SndPlayerSetTrackPitch( Snd_HandleGet(handle_no), bitmask, pitch );
	return;
}

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
void Snd_PlayerSetTrackPitchBySeqNo( u16 no, u16 bitmask, int pitch )
{
	u8 player_no = Snd_GetPlayerNo(no);				//seq�i���o�[����A�v���C���[�i���o�[���擾
	int type = Snd_GetHandleNoByPlayerNo(player_no);//player�i���o�[����A�n���h���i���o�[���擾
	Snd_PlayerSetTrackPitch( type, bitmask, pitch );
	return;
}

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
void Snd_PlayerSetTrackPan( int handle_no, u16 bitmask, int pan )
{
	NNS_SndPlayerSetTrackPan( Snd_HandleGet(handle_no), bitmask, pan );
	return;
}

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
void Snd_PlayerSetTempoRatio( int handle_no, int tempo )
{
	NNS_SndPlayerSetTempoRatio( Snd_HandleGet(handle_no), tempo );
	return;
}


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
 *
 * ���m�����t���O��L���ɂ���ƁA�p���̐ݒ�l�𖳎����āA
 * �S�Ă̔����������̒�ʂōs���܂��B 
 */
//--------------------------------------------------------------
void Snd_SetMonoFlag( BOOL flag )
{
	NNS_SndSetMonoFlag( flag );
	mono_flag = flag;
	return;
}

//--------------------------------------------------------------
/**
 * @brief	�t�F�[�h�J�E���^�[�Z�b�g
 *
 * @param	frame		�t���[����
 *
 * @retval	none
 */
//--------------------------------------------------------------
void Snd_FadeCountSet( int frame )
{
	int* fade_count = Snd_GetParamAdrs(SND_W_ID_FADE_COUNT);
	*fade_count = frame;
	return;
}

//--------------------------------------------------------------
/**
 * @brief	����BGM��炷�܂ł̃E�F�C�g�Z�b�g
 *
 * @param	frame		�t���[����
 *
 * @retval	none
 */
//--------------------------------------------------------------
void Snd_NextWaitSet( int frame )
{
	int* next_wait = Snd_GetParamAdrs(SND_W_ID_NEXT_WAIT);
	*next_wait = frame;
	return;
}

//--------------------------------------------------------------
/**
 * @brief	����BGM��炷�܂ł̃E�F�C�g�`�F�b�N(�J�E���^�[�����炵�Ă��܂�)
 *
 * @param	none
 *
 * @retval	"0=�I���A0�ȊO=�J�E���^�[�l"
 */
//--------------------------------------------------------------
int Snd_NextWaitCheck()
{
	u16* next_wait = Snd_GetParamAdrs(SND_W_ID_NEXT_WAIT);

	if( *next_wait <= 0 ){
		*next_wait = 0;
		return 0;
	}

	(*next_wait)--;
	return *next_wait;
}

//--------------------------------------------------------------
/**
 * @brief	�}�X�^�[�{�����[���ݒ�(�f�t�H���g��127)
 *
 * @param	vol		�{�����[��(0-127)
 *
 * @retval	none
 */
//--------------------------------------------------------------
#if 0
void Snd_SetMasterVolume( int vol )
{
	NNS_SndSetMasterVolume( vol );
	return;
}
#endif

//--------------------------------------------------------------
/**
 * @brief	�g�`�i�[�o�b�t�@�̃A�h���X�擾(��)
 *
 * @param	vol		�{�����[��(0-127)
 *
 * @retval	none
 */
//--------------------------------------------------------------
void* Snd_GetWaveBufAdrs(void)
{
	return &sWaveBuffer[0];
}

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
BOOL Snd_PlayerHeapCreate( int player_no, u32 size )
{
	return NNS_SndPlayerCreateHeap( player_no, *( Snd_HeapHandleGet() ), size );
}


//==============================================================================================
//
//	���[�J���֐�
//
//==============================================================================================


//==============================================================================================
//
//	�t�B�[���h����؂�ւ��
//
//	�P�j�퓬�ɓ���
//	�Q�j�����ɓ���
//	�R�j�ŃQ�[���I�[�o�[
//	�S�j���]�Ԃɏ������
//	�T�j�g��肵����
//	���ɂ͉������邩�H�H
//
//	�i�K�I�ɕω�����֐������łɌĂ�ł���ꍇ�̑Ώ����m�F�I(TCB�ȊO�ł�)
//	����~�������Ă΂Ȃ��Ƃ����Ȃ��ȂǁB
//
//	���C�����t�B�[���h�łȂ��Ȃ�����폜�Ȃ�
//
//==============================================================================================


//==============================================================================================
//
//	���g�p�E�f�o�b�N�֘A
//
//==============================================================================================
#if 0
//--------------------------------------------------------------
/**
 * @brief	�T�E���h���[�J�����[�N�m��
 *
 * @param	none
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void Snd_LocalWorkCreate(void);
static void Snd_LocalWorkCreate(void)
{
	wk = sys_AllocMemory( HEAPID_WORLD, sizeof(SND_LOCAL_WORK) );
	if( wk == NULL ){
		GF_ASSERT( (0) && "�T�E���h���[�J�����[�N�m�ێ��s�I" );
	}
	memset( wk, 0, sizeof(SND_LOCAL_WORK) );

	return;
}

//--------------------------------------------------------------
/**
 * @brief	�S�ẴT�E���h�q�[�v�N���A(�ʏ�g�p���Ȃ�)
 *
 * @param	none
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void Snd_HeapClear(void);
static void Snd_HeapClear(void)
{
	SND_WORK* wk = Snd_GetSystemAdrs();
	NNS_SndHeapClear(wk->heap);
	return;
}

//--------------------------------------------------------------
/**
 * @brief	�V�[�P���X���Đ�
 *
 * @param	p		�T�E���h�n���h���̃A�h���X
 * @param	no		BGM�i���o�[
 *
 * @retval	"�Đ�����=TRUE�A���s=FALSE"
 *
 * �Đ��ɐ�������ƁA�T�E���h�n���h���ɃV�[�P���X�����т����܂��B 
 *
 * �V�[�P���X�f�[�^���v���C���[�q�[�v�Ń��[�h���鎞�́A
 * �e�ʂ�����Ȃ��ƍĐ����s����I
 */
//--------------------------------------------------------------
static BOOL Snd_ArcPlayerStartSeq( NNSSndHandle *p, u16 no )
{
	return NNS_SndArcPlayerStartSeq( p, no );
}

//--------------------------------------------------------------
/**
 * @brief	�V�[�P���X�A�[�J�C�u���Đ�
 *
 * @param	p		�T�E���h�n���h���̃A�h���X
 * @param	arc_no	�V�[�P���X�A�[�J�C�u�i���o�[(�V�[�P���X�A�[�J�C�u�̕��я�)
 * @param	index	�C���f�b�N�X
 *
 * @retval	"�Đ�����=TRUE�A���s=FALSE"
 *
 * �Đ��ɐ�������ƁA�T�E���h�n���h���ɃV�[�P���X�����т����܂��B 
 *
 * �Đ����s�̌����́A
 * �V�[�P���X�A�[�J�C�u�ԍ�������
 * �C���f�b�N�X�ԍ������� 
 * ���ɍĐ����̃V�[�P���X�����D��x���Ⴂ 
 * �f�[�^����������ɖ��� 
 * �q�[�v�̈悪����Ȃ�(�O���[�v���[�h�����s���Ă���)
 */
//--------------------------------------------------------------
BOOL Snd_ArcPlayerStartSeqArc( NNSSndHandle *p, int arc_no, int index )
{
	return NNS_SndArcPlayerStartSeqArc( p, arc_no, index );
}

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
static u8 Snd_PlayerSetPlayableSeqCount( int player_no, int no );
static u8 Snd_PlayerSetPlayableSeqCount( int player_no, int no )
{
	const NNSSndArcPlayerInfo* info;
	u8 ret;

	//���ӁI �T�E���h�A�[�J�C�u����̎擾
	info = NNS_SndArcGetPlayerInfo( player_no );		//�v���C���[���\���̎擾
	ret = info->seqMax;									//�ޔ�

	NNS_SndPlayerSetPlayableSeqCount( player_no, no );

	return ret;											//�ύX�O�̃V�[�P���X�ő哯���Đ���
}
#endif


//==============================================================================================
//
//	�X�g���[���֐�
//
//==============================================================================================
#ifdef STREAM_ON
//--------------------------------------------------------------
/**
 * @brief	�X�g���[���Đ�
 *
 * @param	no		�X�g���[���i���o�[
 *
 * @retval	none
 *
 * �p���A�{�����[���̂ݑ���o����
 * (��������A�R�[���X���ʂ͏o���Ȃ����ƂɂȂ�I)
 */
//--------------------------------------------------------------
BOOL Snd_ArcStrmStart( u16 no );
BOOL Snd_ArcStrmStart( u16 no )
{
	SND_WORK* wk = Snd_GetSystemAdrs();
	(void)NNS_SndArcStrmStart( &wk->strmHandle, no, 0 );
	return;
}
#endif


//==============================================================================================
//
//	fld_bgm�Ŏg�p����֐�
//
//==============================================================================================

//--------------------------------------------------------------
/**
 * @brief	�o���N�؂�ւ��邩�Z�b�g
 *
 * @param	no		0=���A1=��
 *
 * @retval	none
 */
//--------------------------------------------------------------
void Snd_BankFlagSet( int no )
{
	u8* bank_flag	= Snd_GetParamAdrs(SND_W_ID_BANK_FLAG);
	*bank_flag		= no;
	return;
}

//--------------------------------------------------------------
/**
 * @brief	�o���N�؂�ւ��邩�t���O�擾
 *
 * @param	none
 *
 * @retval	"���A1=��"
 */
//--------------------------------------------------------------
u8 Snd_BankFlagGet()
{
	u8* bank_flag = Snd_GetParamAdrs(SND_W_ID_BANK_FLAG);
	return (*bank_flag);
}

//--------------------------------------------------------------
/**
 * @brief	�t�F�[�h�A�E�g �� BGM�Đ�
 *
 * @param	scene		�V�[��(���)�i���o�[
 * @param	no			�V�[�P���X�i���o�[
 * @param	frame		�t���[����
 * @param	next_wait	����BGM��炷�܂ł̃E�F�C�g
 * @param	flag		0=���A1=��A0xff=����(�������Ȃ�)
 * @param	adrs		�t�F�[�h�f�[�^�̃A�h���X
 *
 * @retval	"0=�������Ȃ��A1=�J�n"
 *
 * �t�F�[�h�J�E���^�[���Z�b�g���Ă��܂�
 */
//--------------------------------------------------------------
BOOL Snd_FadeOutNextPlaySet( u8 scene, u16 no, int frame, int next_wait, u8 flag, void* adrs )
{
	u8* scene_sub	= Snd_GetParamAdrs(SND_W_ID_SCENE_SUB);

	//�t�F�[�h���ʏ���
	Snd_FadeCommonSet( scene, no, frame, next_wait, flag, adrs );
	
	//�T�u�V�[�����N���A
	*scene_sub = SND_SCENE_DUMMY;

	//�X�e�[�^�X���ăZ�b�g
	Snd_StatusSet( SND_STATUS_FADEOUT_NEXT_PLAY );	//�X�e�[�^�X(�t�F�[�h�A�E�g���Đ�)
	return 1;
}

//--------------------------------------------------------------
/**
 * @brief	�t�F�[�h�A�E�g �� BGM�t�F�[�h�C��
 *
 * @param	scene		�V�[��(���)�i���o�[
 * @param	no			�V�[�P���X�i���o�[
 * @param	frame		�t���[����
 * @param	next_wait	����BGM��炷�܂ł̃E�F�C�g
 * @param	next_frame	����BGM�̃t�F�[�h�C���t���[����
 * @param	flag		�o���N��؂�ւ��邩(SND_BANK_CONTINUE�ASND_BANK_CHANGE)
 * @param	adrs		�t�F�[�h�f�[�^�̃A�h���X
 *
 * @retval	"0=�������Ȃ��A1=�J�n"
 *
 * �t�F�[�h�J�E���^�[���Z�b�g���Ă��܂�
 */
//--------------------------------------------------------------
BOOL Snd_FadeOutNextFadeInSet( u8 scene, u16 no, int frame, int next_wait, int next_frame, u8 flag, void* adrs )
{
	int* next_frame_wk = Snd_GetParamAdrs(SND_W_ID_NEXT_FRAME);

	//�t�F�[�h���ʏ���
	Snd_FadeCommonSet( scene, no, frame, next_wait, flag, adrs );
	
	*next_frame_wk = next_frame;						//����BGM�̃t�F�[�h�C���t���[�����Z�b�g

	//�X�e�[�^�X���ăZ�b�g
	Snd_StatusSet( SND_STATUS_FADEOUT_NEXT_FADEIN );	//�X�e�[�^�X(�t�F�[�h�A�E�g���t�F�[�h�C��)
	return 1;
}

//���ʏ���
static void Snd_FadeCommonSet( u8 scene, u16 no, int frame, int next_wait, u8 flag, void* adrs )
{
	const NNSSndArcBankInfo** info		= Snd_GetParamAdrs(SND_W_ID_BANK_INFO);

	//�t�F�[�h�A�E�g�J�n(�X�e�[�^�X���t�F�[�h�A�E�g)
	Snd_BgmFadeOut( BGM_VOL_MIN, frame );

	//�t�F�[�h�A�E�g����"����BGM�i���o�["�́A�K��0�������Ă���悤�ɂ���I
	
	//�ēx�]�[���؂�ւ��������Ă΂��悤�ɁA����BGM�i���o�[���N���A����I
	Snd_NowBgmNoSet( 0 );							//����BGM�i���o�[�Z�b�g

	//����(�]�[��)BGM�i���o�[���Z�b�g���Ă���
	Snd_NextBgmNoSet( no );							//����BGM�i���o�[�Z�b�g
	Snd_NextWaitSet( next_wait );					//����BGM��炷�܂ł̃E�F�C�g�Z�b�g

	//06.01.25�폜
	//Snd_SceneSet( scene );						//�ύX����V�[���Z�b�g
	
	*info		= Snd_GetBankInfo( no );			//�o���N���\���̃Z�b�g

	Snd_BankFlagSet( flag );						//�o���N�؂�ւ��邩�Z�b�g
	return;
}


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
void Snd_DebugNormalChannelFree()
{
	u8* ch_normal_flag = Snd_GetParamAdrs(SND_W_ID_WAVEOUT_CH_NORMAL_FLAG);

	if( *ch_normal_flag == 1 ){	//�m�ۃt���O��ON��������
		Snd_WaveOutFreeChannel( WAVEOUT_CH_NORMAL );
	}

	return;
}


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
void Snd_DebugLoadBank( u16 no )
{
	Snd_ArcLoadBank( no );
	return;
}


//==============================================================================================
//
//	�g�`�֘A(�|�P�����}�ӂ̖�����ʂŎg�p)
//
//	<nitro/snd.h>
//	typedef struct SNDWaveData
//
//==============================================================================================
const u8* Snd_WaveDataSampleAdrsGet( const SNDWaveData* p_data );
const u32 Snd_WaveDataSampleSizeGet( const SNDWaveData* p_data );
const SNDWaveData* Snd_ZukanWaveDataSet( int wave_arc_no );
static const SNDWaveData* Snd_WaveDataAdrsGet( int wave_arc_no );
u32 Snd_PlayerGetSampleTick( int handle_no, const SNDWaveData* p_data );
u32 Snd_ZukanPlayerGetSampleTick( int handle_no, const SNDWaveData* p_data, int pitch );
u32 Snd_PlayerGetTick( int handle_no );

//--------------------------------------------------------------
/**
 * @brief	�g�`�f�[�^�̃A�h���X����T���v���f�[�^�̃A�h���X���擾
 *
 * @param	p_data		�g�`�f�[�^�̃A�h���X
 *
 * @retval	"�T���v���f�[�^�̃A�h���X�ANULL=���s"
 */
//--------------------------------------------------------------
const u8* Snd_WaveDataSampleAdrsGet( const SNDWaveData* p_data )
{
	if( p_data == NULL ){
		return NULL;
	}

	return &p_data->samples[0];
}

//--------------------------------------------------------------
/**
 * @brief	�g�`�f�[�^�̃A�h���X����T���v���f�[�^�̔z��̑傫�����擾
 *
 * @param	p_data		�g�`�f�[�^�̃A�h���X
 *
 * @retval	"�T���v���f�[�^�̔z��̑傫���A0=���s"
 */
//--------------------------------------------------------------
const u32 Snd_WaveDataSampleSizeGet( const SNDWaveData* p_data )
{
	if( p_data == NULL ){
		return 0;
	}

	return (p_data->param.looplen);
}

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
const SNDWaveData* Snd_ZukanWaveDataSet( int wave_arc_no )
{
	u16 monsno;

	Snd_HeapLoadState( Snd_GetHeapSaveLv(SND_HEAP_SAVE_SUB_SE) );	//�T�u���SE�̌�������

	monsno = wave_arc_no;

	//�s���Ȓl�`�F�b�N
	if( monsno != MONSNO_PERAPPU ){					//�f�o�b�N�̂��߂؃��b�v�͗�O�ɂ��Ă���
		if( (wave_arc_no > MONSNO_MAX) || (wave_arc_no == 0) ){
			//GF_ASSERT( (0) && "�|�P�����i���o�[���s���ł��I" );
			//return FALSE;	//�G���[
			OS_Printf( "�|�P�����i���o�[���s���ł��I" );
			monsno = MONSNO_HUSIGIDANE;
		}
	}

	//�g�`�A�[�J�C�u���[�h(���[�h���Ȃ��ƁA���Ƃ̏����Ŏ��s����I)
	Snd_ArcLoadWaveArc( monsno );

	//�g�`�f�[�^�̃A�h���X�擾
	return Snd_WaveDataAdrsGet( monsno );
}

//--------------------------------------------------------------
/**
 * @brief	�g�`�f�[�^�̃A�h���X���擾
 *
 * @param	wave_arc_no	�g�`�A�[�J�C�u�ԍ�(�|�P�����i���o�[)
 *
 * @retval	"�g�`�f�[�^�\���̂̃A�h���X�ANULL=���s"
 */
//--------------------------------------------------------------
static const SNDWaveData* Snd_WaveDataAdrsGet( int wave_arc_no )
{
	u16 monsno;
	const NNSSndArcWaveArcInfo* wave_arc_info;
	SNDWaveArc* wave_arc		= NULL;
	const SNDWaveData** p_data	= Snd_GetParamAdrs(SND_W_ID_WAVE_DATA);

	monsno = wave_arc_no;

	//�s���Ȓl�`�F�b�N
	if( monsno != MONSNO_PERAPPU ){					//�f�o�b�N�̂��߂؃��b�v�͗�O�ɂ��Ă���
		if( (wave_arc_no > MONSNO_MAX) || (wave_arc_no == 0) ){
			//GF_ASSERT( (0) && "�|�P�����i���o�[���s���ł��I" );
			//return FALSE;	//�G���[
			OS_Printf( "�|�P�����i���o�[���s���ł��I" );
			monsno = MONSNO_HUSIGIDANE;
		}
	}

	//�g�`�A�[�J�C�u���\���̎擾
    wave_arc_info = NNS_SndArcGetWaveArcInfo( monsno );
    if( wave_arc_info == NULL ){
		GF_ASSERT( (0) && "�g�`�A�[�J�C�u�i���o�[���s���ł��I" );
		return NULL;
	}

	//�t�@�C��ID����A�g�`�A�[�J�C�u���\���̎擾
	wave_arc = (SNDWaveArc*)NNS_SndArcGetFileAddress( wave_arc_info->fileId );
    if( wave_arc == NULL ){
		OS_Printf( "�T�E���h�q�[�v������Ȃ��āA�������[�h�Ɏ��s���܂����I\n" );
		OS_Printf( "�|�P�����i���o�[ = %d\n", wave_arc_no );
		GF_ASSERT( (0) && "�g�`�A�[�J�C�u�i���o�[���s���ł��I" );
		return NULL;
	}

	//SNDWaveData�^�̔g�`�f�[�^�̃A�h���X���擾
	*p_data = SND_GetWaveDataAddress( wave_arc, 0 );

	OS_Printf( "���g�`�f�[�^��\n" );
	OS_Printf( "wave_data formt    = %d\n", (*p_data)->param.format );
	OS_Printf( "wave_data loopflag = %d\n", (*p_data)->param.loopflag );
	OS_Printf( "wave_data rate     = %d\n", (*p_data)->param.rate );
	OS_Printf( "wave_data timer    = %d\n", (*p_data)->param.timer );
	OS_Printf( "wave_data loopstart= %d\n", (*p_data)->param.loopstart );
	OS_Printf( "wave_data looplen  = %d\n", (*p_data)->param.looplen );

	return (*p_data);
}

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
u32 Snd_PlayerGetSampleTick( int handle_no, const SNDWaveData* p_data )
{
	u32 num;
	u32 tick = Snd_PlayerGetTick( handle_no );
	u32 max  = p_data->param.looplen;

	//num = (max / 32);		//�Đ��I����������tick�̒l
	num = (tick * 32);		//�Đ����Ă���v�f��
	if( num >= max ){
		num = 0;
	}

	return num;
}

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
u32 Snd_ZukanPlayerGetSampleTick( int handle_no, const SNDWaveData* p_data, int pitch )
{
	int no;
	u32 num;
	u32 tick = Snd_PlayerGetTick( SND_HANDLE_PMVOICE );
	u32 max  = p_data->param.looplen;

#if 1
	//�ׂ����v�Z�͂��Ă��Ȃ��A�I�N�^�[�u�̂ݑΉ�
	
	no = pitch / (64*12);
	no = no * 2;

	if( no < 0 ){
		no = 32 / no * -1;	//���̒l�ɂ���
	}else if( no == 0 ){
		no = 32;
	}else{
		no = 32 * no;
	}

	//OS_Printf( "no = %d\n", no );
#else
	no = 32;
#endif

	//num = (max / no);		//�Đ��I����������tick�̒l
	num = (tick * no);		//�Đ����Ă���v�f��
	if( num >= max ){
		num = 0;
	}

	//OS_Printf( "pitch = %d\n", pitch );
	//OS_Printf( "no = %d\n", no );
	//OS_Printf( "tick = %d\n", tick );
	//OS_Printf( "num = %d\n", num );

	return num;
}

//--------------------------------------------------------------
/**
 * @brief	�e�B�b�N���擾
 *
 * @param	p_data		�g�`�f�[�^�̃A�h���X
 *
 * @retval	"�e�B�b�N��"
 */
//--------------------------------------------------------------
u32 Snd_PlayerGetTick( int handle_no )
{
	u32 tick = NNS_SndPlayerGetTick( Snd_HandleGet(handle_no) );
	//OS_Printf( "tick = %d\n", tick );
	return tick;
}


















#define WAVE_8_BIT_CENTER		(128)			//8bit �؂�ւ�(u8)
#define WAVE_16_BIT_CENTER		(0)				//16bit �؂�ւ�(s16)

//�{�[�O���t�p�̒�`
enum{
	//��������"3"tick���ƂɌĂ΂��̂ŁA32*3=96��100�ɂ��Ă���
	//WAVE_LEVEL_BEFORE_POS	=	(50),			//��r���鍷���̕�
	WAVE_LEVEL_BEFORE_POS	=	(100),			//��r���鍷���̕�
	//WAVE_LEVEL_BEFORE_POS	=	(150),			//��r���鍷���̕�
	//WAVE_LEVEL_BEFORE_POS	=	(200),			//��r���鍷���̕�

	//�������v�f�������߂�Ԋu
	//�Ԋu��������قǗv�f��[0]�̐������Ȃ��Ȃ�
	//
	//06.03.30�e�X�g
	WAVE_LEVEL_HABA				=	(1),		//���x���𕪂���Ԋu("0","1",...�ƕ������)
	//
	//06.03.29�ȑO
	//WAVE_LEVEL_HABA			=	(2),		//���x���𕪂���Ԋu("0,1","2,3",...�ƕ������)
	//
	//WAVE_LEVEL_HABA			=	(3),		//���x���𕪂���Ԋu("0,1,2","3,4,5",...�ƕ������)
	//WAVE_LEVEL_HABA		=	(4),				//���x���𕪂���Ԋu(("0,1,2,3",...�ƕ������)
	//WAVE_LEVEL_HABA		=	(8),				//���x���𕪂���Ԋu(("0,1,2,3",...�ƕ������)
};

//06.04.11
//�������v�f�������߂�Ԋu���e�[�u���ł��悤�ɂ��Ē�������I
#define WAVE_LEVEL_HABA_MAX	(9)
//static const u8 wave_level_haba[WAVE_LEVEL_HABA_MAX] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };	//�O�Ɠ���
//static const u8 wave_level_haba[WAVE_LEVEL_HABA_MAX] = { 1, 2, 4, 6, 7, 8, 9, 10, 11 };
static const u8 wave_level_haba[WAVE_LEVEL_HABA_MAX] = { 2, 3, 4, 5, 6, 7, 8, 9, 10 };


u32 Snd_ZukanPlayerGetTick();
void Snd_DebugWaveDataPut( const SNDWaveData* p_data, u32 start, u32 end );


//const SNDWaveData* snd_wave_data;				//�g�`�f�[�^�̃|�C���^

//�Đ��I��������A
//�Ō�Ɏ擾�������x������A
//�������Ã��x���𗎂Ƃ��Ă���
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
void Snd_DebugWaveDataPut( const SNDWaveData* p_data, u32 start, u32 end )
{
	u32 i,data_size;
	u8 pos;
	//const SNDWaveData** p_data = Snd_GetParamAdrs(SND_W_ID_WAVE_DATA);

	//OS_Printf( "wave_data formt    = %d\n", (p_data)->param.format );
	//OS_Printf( "wave_data loopflag = %d\n", (p_data)->param.loopflag );
	//OS_Printf( "wave_data rate     = %d\n", (p_data)->param.rate );
	//OS_Printf( "wave_data timer    = %d\n", (p_data)->param.timer );
	//OS_Printf( "wave_data loopstart= %d\n", (p_data)->param.loopstart );
	//OS_Printf( "wave_data looplen  = %d\n", (p_data)->param.looplen );

	data_size = ( (p_data)->param.looplen );

	for( i=start;  i < end ;i++ ){

		//�G���[���
		if( i >= data_size ){
			return;
		}

		//--------------------------------
		//			�f�[�^	��	�\���ʒu
		//			127			0
		//
		//			0			128
		//CENTER----0-----------128-------
		//			255			129
		//
		//			128			255
		//--------------------------------
		if( (p_data)->samples[i] == 255 ){								//255��������
			pos = 129;													//�\��129

		}else if( (p_data)->samples[i] < WAVE_8_BIT_CENTER ){				//0-127��������
			pos = (128 - (p_data)->samples[i]);							//�\��0-128

		}else{
			pos = (255 - ((p_data)->samples[i] - WAVE_8_BIT_CENTER));		//�\��129-255
		}

		//OS_Printf( "(p_data)->samples[%d] = %d\n", i, pos );
		OS_Printf( "buf[%d] = %d;\n", i, pos );
	}

	return;
}

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
void Snd_ZukanWaveLevelSet_New( const SNDWaveData* p_data, u8* buf, int max, int pitch );
void Snd_ZukanWaveLevelSet_New( const SNDWaveData* p_data, u8* buf, int max, int pitch )
{
	int flag;
	int start;									//�f�[�^���`�F�b�N����J�n�ʒu
	s8	status;									//���݂̏��(+1=��A-1=��)
	int i,j,pos,count;							//�v�Z�p
	u32 tick = Snd_ZukanPlayerGetSampleTick( SND_HANDLE_PMVOICE, p_data, pitch );

	//[100]��������A[50]�`[100]���`�F�b�N����
	start = tick - WAVE_LEVEL_BEFORE_POS;
	if( start < 0 ){
		start = 0;								//�␳
	}

	//������
	count = 0;
	pos	= 0;

	//���݂̏�ԃZ�b�g(128�ȉ��͏�A����ȊO�͉�)
	status = ((p_data)->samples[start] < 128 ) ? 1 : -1;

#ifdef SOUND_OS_PRINT_ON
	OS_Printf( "\n===========================\n" );
	OS_Printf( "�`�F�b�N�J�n�ʒu start = %d\n", start );
	OS_Printf( "��� 1=�� -1=�� status = %d\n", status );
	OS_Printf( "�`�F�b�N���݈ʒu tick = %d\n", tick );
#endif

	//�J�n�ʒu���猻�݈ʒu�܂Ń`�F�b�N����
	//for( i=start; i < tick ;i++ ){
	//for( i=start; i < tick ;i+=max ){	//�e�X�g�I1���Ã`�F�b�N�ł͂Ȃ��A�Ԉ����ă`�F�b�N����
	//for( i=start; i < tick ;i+=(max/2) ){	//�e�X�g�I1���Ã`�F�b�N�ł͂Ȃ��A�Ԉ����ă`�F�b�N����
	for( i=start; i < tick ;i+=2 ){	//�e�X�g�I1���Ã`�F�b�N�ł͂Ȃ��A�Ԉ����ă`�F�b�N����
	
		flag = 0;

		if( status > 0 ){									//��ɂ���
			if( (p_data)->samples[i] > 128 ){				//�����H
				flag = 1;
			}else{
				count++;									//��̂܂܂Ȃ̂ŃJ�E���^�C���N�������g
			}

		//}else if( status < 0 ){							//���ɂ���
		}else{												//���ɂ���
			if( (p_data)->samples[i] < 128 ){				//�ォ�H
				flag = 1;
			}else{
				count++;									//���̂܂܂Ȃ̂ŃJ�E���^�C���N�������g
			}
		}

		//�Z���^�[���������̂ŁA���x���C���N�������g
		if( flag == 1 ){
#if 0
			pos = (count / WAVE_LEVEL_HABA);
			//pos = (pos >= max) ? (max-1) : pos;		//�␳(�K�������H)
#else
			for( j=0; j < WAVE_LEVEL_HABA_MAX ;j++ ){ 
				if( count < wave_level_haba[j] ){
					pos = j;
					break;
				}
			}

#endif

			//�J�b�g����(�̂Ă�)���܂��Ă����������H
			if( pos >= max ){
				pos = ( max - 1 );						//�␳(�K�������H)
			}
			//------------------------------

			//�o�����X���Ƃ邽�߂ɊԊu�������鐬���͖�������
			if( count != 0 ){
				//�v�f���̎�O����
				//�v�f���̌�낪��
				buf[max - 1 - pos]++;						//���x���C���N�������g
			}else{
#ifdef SOUND_OS_PRINT_ON
				OS_Printf( "��count = 0 �𖳎����܂����I\n" );
#endif
			}

			count= 0;
			flag = 0;
			status = ((p_data)->samples[i] < 128 ) ? 1 : -1;
		}
	}

#ifdef SOUND_OS_PRINT_ON
	//�f�o�b�N�\��
	for( i=0; i < max ;i++ ){
		OS_Printf( "���␳�Obuf[%d] = %d\n", i, buf[i] );
	}
	OS_Printf( "\n------------\n" );
#endif

#if 0
	//�␳�e�X�g��
	
	//�c10�i�K�ɕ␳����
	for( i=0; i < max ;i++ ){
		if( buf[i] >= 100 ){
			buf[i] = 9;
		}else if( buf[i] >= 10){
			buf[i] /= 10;
		}
	}
#else

	//�c10�i�K�ɕ␳����
	for( i=0; i < max ;i++ ){
		if( buf[i] >= 10 ){
			buf[i] = 9;
		}
	}
#endif



#if 1

	//��ԍ�����f�[�^������Ȃ������v�f����T���āA
	//���ׂ̗̃f�[�^�̔����̃��x����␳���đ��

	for( i=0; i < (max-1) ;i++ ){
		if( (buf[i] == 0) && (buf[i+1] != 0) ){
			buf[i] = (buf[i+1] / 2);
			break;
		}
	}

#endif



#if 0
	//0�����݂�����A�ƂȂ�̃��x�������āA�␳����H
	//�ψ�ɂȂ肷���Ă��܂��H
	
	//�Ԉ����̊Ԋu���L����������ƁA���̃f�[�^���ǂ��Ȃ邩���A�^�������Ȃ�̂ł��߁I
	//�A�������`��������x�����邽�߂ɁA+1,+2���炢�̊Ԉ����͂��������H
	
	//�オ10�i�K�Ȃ̂ŁA�A�������`�͔����Ȃ��Ƃ����Ȃ��B
#endif

#ifdef SOUND_OS_PRINT_ON
	//�f�o�b�N�\��
	for( i=0; i < max ;i++ ){
		OS_Printf( "���␳��buf[%d] = %d\n", i, buf[i] );
	}
	OS_Printf( "\n------------\n" );
#endif

	return;
}
 
//--------------------------------------------------------------
/**
 * @brief	�G�t�F�N�g�̃R�[���o�b�N�֐�(�}�Ӗ����p)
 *
 * @param	bufferL_p	L�~�L�T�[����
 * @param	bufferR_p	R�~�L�T�[����
 * @param	len			�o�b�t�@�̃T�C�Y
 * @param	format		NNS_SndCaptureStartEffect�֐��̈���(CAPTURE_FORMAT)�Ɠ������̂��n�����
 * @param	arg			NNS_SndCaptureStartEffect�֐��̈���(callbackInfo)�Ɠ������̂��n�����
 *
 * @retval	none
 *
 * �ȒP�ȃ��[�p�X�t�B���^�i�ړ����ρj�������ďo�͂��Ă���
 *
 * �����Ԃ̊Ԋu���߁A���̊Ԋu���̕��ϒl��A�����Čv�Z���邱�Ƃɂ����
 * ����(��������)�I�ȓ�����m�낤�Ƃ�����́B
 * (��������ւƓ������� )
 */
//--------------------------------------------------------------
static void EffectCallback2( void* bufferL_p, void* bufferR_p, u32 len, NNSSndCaptureFormat format, void* arg )
{
    smp_t org[ FILTER_SIZE ][2];
    smp_t* lp = (smp_t*)bufferL_p;
    smp_t* rp = (smp_t*)bufferR_p;
    EffectCallbackInfo* info = (EffectCallbackInfo*)arg;
	u8* filter_size = Snd_GetParamAdrs(SND_W_ID_FILTER_SIZE);

    int samples;
    int x;
    int i, j;
    
	//�T���v����8�r�b�gPCM�͂��̂܂�
	//�T���v����16�r�b�gPCM��������o�b�t�@�̃T�C�Y�𔼕��ɂ���
    samples = ( format == NNS_SND_CAPTURE_FORMAT_PCM8 ) ? len : ( len >> 1 );

#ifdef SOUND_OS_PRINT_ON
	OS_Printf( "\n\n���T�E���h�@�L���v�`���@�G�t�F�N�g��\n" );
	OS_Printf( "format = %d\n", format );			//0
	OS_Printf( "len = %d\n", len );					//1024
	OS_Printf( "samples = %d\n", samples );			//
	OS_Printf( "\n" );
#endif
    
	if( (*filter_size) == 0 ){
		return;		//�������Ȃ�
	}

	//--------------------------------------------
	//��
	//	LR�~�L�T�[�����̃T�C�Y(samples)	= 256 
	//	�t�B���^�[�T�C�Y				= 8
	//
	//	lp[ 256 - 8 + i ]				= 248 + i
	//
	//	248,249,250,251,252,253,254,255��ۑ�
	//--------------------------------------------
    //LR�~�L�T�[�����̂�����A�t�B���^�[�T�C�Y����ۑ�
    for( i = 0; i < (*filter_size) ; i++ ) {
        org[i][0] = lp[ samples - (*filter_size) + i ];
        org[i][1] = rp[ samples - (*filter_size) + i ];
		OS_Printf( "org[%d][��] = %d\n", i, org[i][0] );
		OS_Printf( "org[%d][�E] = %d\n", i, org[i][1] );
    }
    
	//--------------------------------------------
	//�� 
	//	LR�~�L�T�[�����̃T�C�Y		= 256
	//	�t�B���^�[�T�C�Y			= 8
	//
    //	for( i = 256 - 1; i >= 8 - 1 ; i-- ){
	//	255...7�܂ŏ�������
	//--------------------------------------------
	//LR�~�L�T�[�����̂�����A�t�B���^�[�T�C�Y�̒l��菬�����Ȃ�܂ŏ�������
    for( i = samples - 1; i >= (*filter_size) - 1 ; i-- ){

		//--------------------------------------------
		//�� 
		//	LR�~�L�T�[�����̃T�C�Y		= 256
		//	�t�B���^�[�T�C�Y			= 8
		//
		//	j = 0 �` 7
		//	x += lp[ 255 - j ];
		//	lp[255],[254],...[248]�܂ł̒l�𑫂��āA
		//	�t�B���^�[�T�C�Y�Ŋ���A���ς̒l�����߂�
		//--------------------------------------------
		//L�~�L�T�[����
        x = 0;
        for( j = 0 ; j < (*filter_size) ; j++ ) {	//�t�B���^�[�T�C�Y�������Ă���
            x += lp[ i - j ];
        }
        lp[ i ] = (smp_t)(x /= (*filter_size));		//�t�B���^�[�T�C�Y�Ŋ��蕽�ς̒l�����߂ď㏑��
        
		//R�~�L�T�[����
        x = 0;
        for( j = 0 ; j < (*filter_size) ; j++ ) {	//�t�B���^�[�T�C�Y�������Ă���
            x += rp[ i - j ];
        }
        rp[ i ] = (smp_t)(x /= (*filter_size));		//�t�B���^�[�T�C�Y�Ŋ��蕽�ς̒l�����߂ď㏑��
    }
    


#if 0
#if FILTER_SIZE >= 2    
	//--------------------------------------------
	//�� �o�b�t�@�T�C�Y = 24 �t�B���^�[�T�C�Y = 8
    //for( i = 8 - 2; i >= 0 ; i-- ){
	//6...0�܂ŏ�������
	//--------------------------------------------
    for( i = (*filter_size) - 2 ; i >= 0 ; i-- ){

		//L�~�L�T�[����
        x = lp[ i ];
        for( j = 1 ; j < (*filter_size) ; j++ ) {	//�t�B���^�[�T�C�Y��
            x += GetSample( lp, i-j, 0, info );
        }
        lp[ i ] = (smp_t)(x /= (*filter_size));	//�t�B���^�[�T�C�Y�Ŋ��蕽�ςŏ㏑������
        
		//R�~�L�T�[����
        x = rp[ i ];
        for( j = 1 ; j < (*filter_size) ; j++ ) {
            x += GetSample( rp, i-j, 1, info );
        }
        rp[ i ] = (smp_t)(x /= (*filter_size));	//�t�B���^�[�T�C�Y�Ŋ��蕽�ςŏ㏑������
    }
#endif
#endif
    



	//�L���v�`�������������̈�̃t�B���^�T�C�Y����
	//�ۑ����Ă������f�[�^�ŏ㏑������
	//(�o�b�t�@�̈�Ԍ�납��A�t�B���^�[�T�C�Y����ۑ����Ă������f�[�^)
    for( i = 0; i < (*filter_size) ; i++ ) {
    	info->sample[i][0] = org[i][0];
		info->sample[i][1] = org[i][1];
    }

	//���C���������Ɋm���ɏ�������
    DC_FlushRange( bufferL_p, samples );
    DC_FlushRange( bufferR_p, samples );

	//�����ɓn�����o�b�t�@�́A(���̊֐����ł�info)
	//�L���v�`�������������̈���w���Ă��܂��B
	//���̗̈���C�����邱�ƂŁA���ۂɏo�͂���鉹��ύX���邱�Ƃ��ł��܂��B 
}

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
BOOL Snd_PlayerWriteVariable( s16 num )
{
	return NNS_SndPlayerWriteVariable( Snd_HandleGet(SND_HANDLE_BGM), 0, num );
}

//--------------------------------------------------------------
/**
 * @brief	PLAYER_BGM�̎g�p�`�����l����ύX����
 *
 * @param	ch		�g�p�`�����l���̃r�b�g�w��
 *
 * @retval	none
 *
 * �I�[�v�j���O�A�G���f�B���O�݂̂Ŏg�p����I
 *
 * 14,15ch�𔲂����Ďg�p�\�ɂ���I
 */
//--------------------------------------------------------------
static void Snd_PlayerBgmChannelSet( u16 ch_bit )
{
	NNS_SndPlayerSetAllocatableChannel( PLAYER_BGM, ch_bit );
	return;
}

#if 0 
//--------------------------------------------------------------
/**
 * @brief	�V�[�P���X�g���b�N�̊m�ۉ\�ȃ`�����l����ύX
 *
 * @param	ch_bit			�m�ۉ\�ȃ`�����l���̃r�b�g�t���O
 *
 * @retval	none
 *
 * �I�[�v�j���O�A�G���f�B���O�݂̂Ŏg�p����I
 *
 * 14,15ch�𔲂����Ďg�p�\�ɂ���I
 */
//--------------------------------------------------------------
static void Snd_PlayerBgmChannelSet( u16 ch_bit )
{
	NNS_SndPlayerSetTrackAllocatableChannel( Snd_HandleGet(SND_HANDLE_BGM), ch_bit );
	return;
}
#endif

//--------------------------------------------------------------
/**
 * @brief	�g�p�\�`�����l������A���o�[�u�ݒ�
 *
 * @param	flag	2=�Z�b�g(ED)�A1=�Z�b�g(OP)�A0=�N���A
 *
 * @retval	none
 */
//--------------------------------------------------------------
void Snd_BgmChannelSetAndReverbSet( int flag )
{
#ifdef SND_CH_SET
	if( flag == 0 ){
		Snd_PlayerBgmChannelSet( PLAYER_BGM_NORMAL_CH );	//PLAYER_GM�̎g�p�`�����l�������ɖ߂�
		Snd_CaptureStopReverb( 0 );							//���o�[�u��~
		//OS_Printf( "\n**********\nOP,ED ���o�[�u��~�I\n*********\n" );
	}else if( flag == 1 ){
		Snd_PlayerBgmChannelSet( PLAYER_BGM_EXTRA_CH );	//OP�AED�̂�BGM�̎g�p�`�����l���𑝂₷
		if( Snd_CaptureStartReverb( SND_REVERB_NUM_OP ) == FALSE ){	//���o�[�u�J�n
			OS_Printf( "\n**********\nOP,ED ���o�[�u���s�I\n*********\n" );
		}else{
			//OS_Printf( "\n**********\nOP,ED ���o�[�u�J�n�I\n*********\n" );
		}
	}else{
		Snd_PlayerBgmChannelSet( PLAYER_BGM_EXTRA_CH );	//OP�AED�̂�BGM�̎g�p�`�����l���𑝂₷
		if( Snd_CaptureStartReverb( SND_REVERB_NUM_ED ) == FALSE ){	//���o�[�u�J�n
			OS_Printf( "\n**********\nOP,ED ���o�[�u���s�I\n*********\n" );
		}else{
			//OS_Printf( "\n**********\nOP,ED ���o�[�u�J�n�I\n*********\n" );
		}
	}

	Snd_CaptureIsActive();
#endif
	return;
}

//--------------------------------------------------------------
/**
 * @brief	�t�B�[���hBGM���|�[�Y���邩�A��~���邩�𔻕ʂ��ď���
 *
 * @param	none
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void Snd_FieldPauseOrStop( void )
{
	//�t�F�[�h���ł͂Ȃ��A
	//PLAYER_FIELD�ɃV�[�P���X���ݒ肳��Ă��āA
	//���݂�BGM���u��ꑐ�v�łȂ�������
	if( (Snd_FadeCheck() == 0) && 
		(Snd_GetSeqNo(Snd_HandleGet(SND_HANDLE_FIELD)) != -1) &&
		(Snd_NowBgmNoGet() != SEQ_KUSAGASA) ){

		Snd_StopEx();											//�t�B�[���hBGM�𔲂����đS��~
		Snd_PlayerPause( PLAYER_FIELD, TRUE );					//�t�B�[���hBGM�|�[�Y

	}else{
		Snd_Stop();												//�S��~
	}

	return;
}


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
void Snd_PlayerSetPlayerVolume( int player_no, int volume )
{
	NNS_SndPlayerSetPlayerVolume( player_no, volume );
	return;
}


