//==============================================================================================
/**
 * @file	snd_play.c
 * @brief	�T�E���h�Đ��֐�
 * @author	Satoshi Nohara
 * @date	2005.06.09
 *
 *	��������
 * �|�P�����i���o�[�ƁA�����V�[�P���X�f�[�^�̕��т��������m�F����I
 * (�S���}�Ӄi���o�[�ɑΉ����Ă���炵���B050722��V��������)
 *
 *	�g�`�Đ�(�t�Đ�)���g�p���Ă���Z�̍Ō�ɁAFreeChannel������I
 */
//==============================================================================================
#include "common.h"
#include "snd_system.h"
#include "system/snd_tool.h"
#include "system/snd_perap.h"
#include "poketool/monsno.h"


#ifdef PM_DEBUG
//BGM��OFF�ɂ��鏈��
u8 debug_bgm_flag;
void Snd_DebugBgmFlagSet( u8 sw );
static BOOL Snd_DebugBgmFlagCheck();
#endif

//==============================================================================================
//
//	��`
//
//==============================================================================================
#define	SND_ME_COMMON_WAIT		(15)			//ME���ʃE�F�C�g�l

//�����p�^�[���̃p�����[�^��`
#define VOICE_SMALL_VOL			(90)			//���ʏ�����
#define DEFAULT_RELEASE			(0)				//�L�[�I�t��̃����[�X

//#define W_HYPER_VOICE_PITCH	(32768+16384)	//�Z�u�n�C�p�[�{�C�X�v�̃s�b�`
//#define W_HYPER_VOICE_PITCH	(32768+8192)	//�Z�u�n�C�p�[�{�C�X�v�̃s�b�`
//#define W_HYPER_VOICE_PITCH	(32768+4096)	//�Z�u�n�C�p�[�{�C�X�v�̃s�b�`
//#define W_HYPER_VOICE_PITCH	(32768+3072)	//�Z�u�n�C�p�[�{�C�X�v�̃s�b�`
//#define W_HYPER_VOICE_PITCH	(32768+2048)	//�Z�u�n�C�p�[�{�C�X�v�̃s�b�`
#define W_HYPER_VOICE_PITCH		(32768+1536)	//�Z�u�n�C�p�[�{�C�X�v�̃s�b�`

//#define W_NAKIGOE_PITCH		(32768+16384)	//�Z�u�����v�̃s�b�`
//#define W_NAKIGOE_PITCH		(32768-8192)	//�Z�u�����v�̃s�b�`
#define W_NAKIGOE_PITCH			(32768-6144)	//�Z�u�����v�̃s�b�`


//==============================================================================================
//
//	�\���̐錾
//
//==============================================================================================
//�|�P���������Đ����ԃ��[�N
typedef struct{
	int length;
	TCB_PTR	tcb;
}SND_PMVOICE_LENGTH_WORK;


//==============================================================================================
//
//	�v���g�^�C�v�錾
//
//==============================================================================================
BOOL Snd_BgmPlayBasicData( u16 no );
BOOL Snd_BgmPlay( u16 no );
static void Snd_BgmPlayCommon_01( u16 seq_no, int handle_no );
static BOOL Snd_BgmPlay_PlayerBgm( u16 no, u8 player_no, int type );
static BOOL Snd_BgmPlay_PlayerField( u16 no, u8 player_no, int type );
BOOL Snd_PlayerFieldDemoBgmPlay( u8 scene, u16 no );
void Snd_BgmStop( u16 no, int frame );
static void Snd_BgmStopSub(void);
void Snd_BgmFadeIn( int vol, int frame, int flag );
void Snd_BgmFadeOut( int vol, int frame );
int Snd_FadeCheck();
int Snd_BgmPlayCheck( u16 no );
void Snd_Stop(void);
void Snd_StopEx(void);

BOOL Snd_SePlay( u16 no );
BOOL Snd_SePlayPan( u16 no, int pan );
void Snd_SeStopBySeqNo( u16 no, int frame );
void Snd_SeStop( int type, int frame );
int Snd_SePlayCheck( u16 no );
int Snd_SePlayCheckAll(void);
void Snd_SePanSet( u16 no, u16 bitmask, int pan );
void Snd_SePanSetAll( int pan );

static void Snd_PMVoiceVolSet( u16 seq_no, int handle_no, int vol );
BOOL Snd_PMVoicePlay( u16 no );
void Snd_PMVoiceStop( int frame );
int Snd_PMVoicePlayCheck(void);
BOOL Snd_PMVoicePlayEx( int ptn, u16 no, int pan, int vol, int heap_id );
static u8 Snd_PMVoiceLengthChk();
void Snd_PMVoiceLengthSet(int length, int heap_id );
static void Snd_PMVoiceLengthMainTCB( TCB_PTR tcb, void* wk );
void Snd_PMVoiceLengthTcbDel();
static BOOL Snd_ChorusPlay( u16 no, s8 chorus );
static BOOL Snd_ChorusPlayReverse( u16 no, s8 chorus, int vol, int pan, int heap_id );

BOOL Snd_MePlay( u16 no );
int Snd_MePlayCheck(void);
static void Snd_MeStop( int frame );
int Snd_MePlayCheckBgmPlay(void);
static void Snd_MeWaitSet( u16 no );


//==============================================================================================
//
//	BGM�֘A
//
//==============================================================================================

//--------------------------------------------------------------
/**
 * @brief	BANK_BASIC�ō쐬����BGM�Đ�(�S�ă��[�h�ς݃f�[�^���Đ�)
 *
 * @param	no		BGM�i���o�[
 *
 * @retval	"�Đ�����=TRUE�A���s=FALSE"
 *
 * �f�[�^�̃��[�h����������܂���B�ʏ�͎g�p���܂���B
 */
//--------------------------------------------------------------
BOOL Snd_BgmPlayBasicData( u16 no )
{
	int ret;
	u8 player_no= Snd_GetPlayerNo(no);					//seq�i���o�[����A�v���C���[�i���o�[���擾
	int type	= Snd_GetHandleNoByPlayerNo(player_no);	//player�i���o�[����A�n���h���i���o�[���擾

	//BANK_BASIC�ō쐬���Ă����āASEQ�݂̂����[�h����`���ƁA
	//�T�u�V�[�����Ă΂�邱�Ƃ�����ƁASEQ�͏�����Ă��܂��I
	//�i����ʂ͋Z�Y���ʂ��Ăяo���߂��Ă���̂ŁA
	//�|�P�������X�g�̃T�u�V�[�����Ă΂��̂Ń_���I

	//�n���h���̃A�h���X���擾���āA�Đ�
	ret = NNS_SndArcPlayerStartSeq( Snd_HandleGet(type), no );

	//�Đ����s�`�F�b�N
	if( ret == 0 ){
		OS_Printf( "BGM �Đ����s\tno = %d\n", no );
	}

	Snd_BgmPlayCommon_01( no, type );
	return ret;
}

//--------------------------------------------------------------
/**
 * @brief	BGM�Đ�(SE�̏�ɐς񂾃f�[�^���J�����āABGM�f�[�^�̃��[�h���s��)
 *
 * @param	no		BGM�i���o�[
 *
 * @retval	"�Đ�����=TRUE�A���s=FALSE"
 */
//--------------------------------------------------------------
BOOL Snd_BgmPlay( u16 no )
{
	int ret;
	u8 player_no = Snd_GetPlayerNo(no);				//seq�i���o�[����A�v���C���[�i���o�[���擾
	int type = Snd_GetHandleNoByPlayerNo(player_no);//player�i���o�[����A�n���h���i���o�[���擾

	if( player_no == PLAYER_BGM ){										//"�T�E���h�q�[�v"
		ret = Snd_BgmPlay_PlayerBgm( no, player_no, type );
	}else if( player_no == PLAYER_FIELD ){								//"�v���C���[�q�[�v"
		ret = Snd_BgmPlay_PlayerField( no, player_no, type );
	}else{
		GF_ASSERT( (0) && "�Đ����悤�Ƃ��Ă���BGM�i���o�[���s���ł��I" );
		return FALSE;
	}

	//�o���N�؂�ւ��邩�t���O�����Z�b�g
	Snd_BankFlagSet( SND_BANK_CONTINUE );		//�N���A = �p��

	//�Đ����s�`�F�b�N
	if( ret == 0 ){
		OS_Printf( "BGM �Đ����s\tno = %d\n", no );
	}

	Snd_BgmPlayCommon_01( no, type );
	return ret;
}

//���ʏ���
static void Snd_BgmPlayCommon_01( u16 seq_no, int handle_no )
{
	Snd_NowBgmNoSet( seq_no );											//����BGM�i���o�[�X�V
	Snd_VChatVolSet( seq_no, handle_no );								//�{�C�X�`���b�g���ʑ���
	Snd_StatusSet( SND_STATUS_PLAY );									//�X�e�[�^�X(�Đ�)
	return;
}

//PLAYER_BGM�̍Đ�����
static BOOL Snd_BgmPlay_PlayerBgm( u16 no, u8 player_no, int type )
{
	int ret;

	//�V�[�P���X�A�o���N�A�g�`�A�[�J�C�u���[�h
	Snd_HeapLoadState( Snd_GetHeapSaveLv(SND_HEAP_SAVE_SE) );		//BGM���J��
	Snd_ArcLoadSeq( no );
	Snd_HeapSaveState( Snd_GetParamAdrs(SND_W_ID_HEAP_SAVE_BGM) );	//�K�w�ۑ�(BGM�̌������)

#ifdef PM_DEBUG
	if( Snd_DebugBgmFlagCheck() == 1 ){
		return 0;
	}
#endif

	//�n���h���̃A�h���X���擾���āA�Đ�
	ret = NNS_SndArcPlayerStartSeq( Snd_HandleGet(type), no );
	return ret;
}

//PLAYER_FIELD�̍Đ�����
static BOOL Snd_BgmPlay_PlayerField( u16 no, u8 player_no, int type )
{
	int field_seq_no;
	u8* bank_flag	= Snd_GetParamAdrs(SND_W_ID_BANK_FLAG);
	u16* zone_bgm	= Snd_GetParamAdrs(SND_W_ID_ZONE_BGM);

	//PLAYER_FIELD��BGM�i���o�[�擾
	field_seq_no = Snd_GetSeqNo( Snd_HandleGet(SND_HANDLE_FIELD) );

	//(�n���h���������̎���"-1"���Ԃ�)
	//OS_Printf( "player_field_seq_no = %d\n", Snd_GetSeqNo(Snd_HandleGet(SND_HANDLE_FIELD)) );
		
	//�Đ����悤�Ƃ��Ă���BGM�i���o�[�APLAYER_FIELD�ɂ��łɐݒ肳��Ă���o���N�i���o�[
	Snd_FieldDataSetSub( no, Snd_GetBankNo(field_seq_no) );

#ifdef PM_DEBUG
	if( Snd_DebugBgmFlagCheck() == 1 ){
		return 0;
	}
#endif

	//�n���h���̃A�h���X���擾���āA�Đ�
#if 0
	return NNS_SndArcPlayerStartSeq( Snd_HandleGet(type), no );
#else
	//BANK_BASIC�ł͂Ȃ��A�]�[���Ȃ̃o���N��ǂݍ��ނ悤�ɂ���I
	return NNS_SndArcPlayerStartSeqEx( Snd_HandleGet(type), -1, Snd_GetBankNo(*zone_bgm), -1, no );
#endif
}

//--------------------------------------------------------------
/**
 * @brief	���oBGM�Đ�(���C�o���A�T�|�[�g�A��Ă�)
 *
 * @param	scene	�V�[��(���)�i���o�[
 * @param	no		BGM�i���o�[
 *
 * @retval	"�Đ�����=TRUE�A���s=FALSE"
 *
 * �A�����BGM�ȂǂŎg�p����I
 *
 * �T�u��ʂ��Ăяo���ƃV�[�P���X�f�[�^�������Ă��܂��̂Œ��ӁI
 */
//--------------------------------------------------------------
BOOL Snd_PlayerFieldDemoBgmPlay( u8 scene, u16 no )
{
	int ret;

#ifdef SOUND_OS_PRINT_ON
	OS_Printf( "\n��Snd_PlayerFieldPauseBgmPlay��\n" );
#endif

	//SEQ_TSURETEKE�́APLAYER_BGM�Ȃ̂ŁA
	//Snd_BgmPlay�ŏ�������ƁA
	//BGM�̈�̊J��������̂Ń_���I

	//�t�B�[���h�V�[���̂ݑΉ�
	if( scene != SND_SCENE_FIELD ){
		GF_ASSERT( (0) && "Snd_BgmPlayEx�́ASND_SCENE_FIELD�̂ݑΉ��ł��I" );
		return FALSE;
	}

	//PLAYER_BGM�̂ݑΉ�
	if( Snd_GetPlayerNo(no) != PLAYER_BGM ){
		GF_ASSERT( (0) && "Snd_BgmPlayEx�́APLAYER_BGM�̂ݑΉ��ł��I" );
		return FALSE;
	}

#ifdef PM_DEBUG
	if( Snd_DebugBgmFlagCheck() == 1 ){
		ret = 0;
	}else{

	//�V�[�P���X�̂݃��[�h(��ɐςނ����Ńq�[�v�Z�[�u�͂��Ȃ�)
	ret = Snd_ArcLoadSeqEx( no, NNS_SND_ARC_LOAD_SEQ );

	//SND_HANDLE_BGM�̃A�h���X���擾���čĐ�
	ret = NNS_SndArcPlayerStartSeq( Snd_HandleGet(SND_HANDLE_BGM), no );

	}
#else
	//�V�[�P���X�̂݃��[�h(��ɐςނ����Ńq�[�v�Z�[�u�͂��Ȃ�)
	ret = Snd_ArcLoadSeqEx( no, NNS_SND_ARC_LOAD_SEQ );

	//SND_HANDLE_BGM�̃A�h���X���擾���čĐ�
	ret = NNS_SndArcPlayerStartSeq( Snd_HandleGet(SND_HANDLE_BGM), no );
#endif	//PM_DEBUG

	//�Đ����s�`�F�b�N
	if( ret == 0 ){
		OS_Printf( "Snd_PlayerFieldPauseBgmPlay �Đ����s\tno = %d\n", no );
	}

	Snd_NowBgmNoSet( no );													//����BGM�i���o�[�X�V
	Snd_StatusSet( SND_STATUS_PLAY );										//�X�e�[�^�X(�Đ�)
	return ret;
}

//--------------------------------------------------------------
/**
 * @brief	BGM��~
 *
 * @param	no		BGM�i���o�[
 * @param	frame	�w�肵���t���[���������ď��X�ɉ��ʂ𗎂Ƃ��Ă���
 *
 * @retval	none
 */
//--------------------------------------------------------------
void Snd_BgmStop( u16 no, int frame )
{
	u8 player_no;
	int type;

	NNS_SndPlayerStopSeqBySeqNo( no, frame );

	//----------------------------------------------------------
	//�T�E���h�n���h���Ɍ��т����Ă���V�[�P���X��������܂��B
	//�V�[�P���X�����т����Ă��Ȃ��ꍇ�́A�������܂���B
	//
	//�V�[�P���X�i���o�[����A�v���C���[�i���o�[���擾�A
	//�v���C���[�i���o�[����A�n���h���i���o�[���擾
	player_no = Snd_GetPlayerNo( no );
	if( player_no != 0xff ){
		type = Snd_GetHandleNoByPlayerNo( player_no );
		NNS_SndHandleReleaseSeq( Snd_HandleGet(type) );
	}
	//
	//BGM��~�݂̂ɏ��������Ă��܂��B(BGM�ȊO�̃n���h���ɂ��Ă͖��Ώ�)
	//
	//----------------------------------------------------------

	//�ǉ������́��̊֐��ɒǉ�����I
	Snd_BgmStopSub();
	return;
}

//BGM��~�T�u(�ʏ��Snd_BgmStop���g�p���ĉ�����)
static void Snd_BgmStopSub(void)
{
	Snd_NowBgmNoSet( 0 );					//����BGM�i���o�[�N���A
	Snd_NextBgmNoSet( 0 );					//����BGM�i���o�[�N���A
	Snd_StatusSet( SND_STATUS_STOP );		//�X�e�[�^�X(��~)
	return;
}

//--------------------------------------------------------------
/**
 * @brief	����BGM���t�F�[�h�C��
 *
 * @param	vol		�t�F�[�h�C����̃{�����[��(0-127)
 * @param	frame	�t���[����
 * @param	flag	"BGM_FADEIN_START_VOL_NOW = ���݂̉��ʂ���FADEIN"
 * @param	(flag)	"BGM_FADEIN_START_VOL_MIN = ����0����FADEIN"
 *
 * @retval	none
 *
 * �t�F�[�h�J�E���^�[���Z�b�g���Ă��܂�
 */
//--------------------------------------------------------------
void Snd_BgmFadeIn( int vol, int frame, int flag )
{
	u8 player_no;
	int type;
	u16 now_bgm_no = Snd_NowBgmNoGet();		//����BGM�i���o�[�擾

	//�V�[�P���X�i���o�[����A�v���C���[�i���o�[���擾
	player_no = Snd_GetPlayerNo( now_bgm_no );
	if( player_no == 0xff ){
		return;		//���݂̃V�[�P���X�i���o�[��0�Ȃ̂ŉ������Ȃ��I
	}

	//�v���C���[�i���o�[����A�n���h���i���o�[���擾
	type = Snd_GetHandleNoByPlayerNo( player_no );

	//�t�F�[�h�C���̊J�n���ʂ�0�ɂ��鎞
	if( flag == BGM_FADEIN_START_VOL_MIN ){
		//�n���h���̃A�h���X���擾
		Snd_PlayerMoveVolume( type, 0, 0 );
	}

	Snd_PlayerMoveVolume( type, vol, frame );
	Snd_FadeCountSet( frame );				//�t�F�[�h�J�E���^�[�Z�b�g
	Snd_StatusSet( SND_STATUS_FADEIN );		//�X�e�[�^�X(�t�F�[�h�C��)
	return;
}

//--------------------------------------------------------------
/**
 * @brief	����BGM���t�F�[�h�A�E�g
 *
 * @param	vol		�t�F�[�h�A�E�g��̃{�����[��(0-127)
 * @param	frame	�t���[����
 *
 * @retval	none
 *
 * �t�F�[�h�J�E���^�[���Z�b�g���Ă��܂�
 */
//--------------------------------------------------------------
void Snd_BgmFadeOut( int vol, int frame )
{
	u8 player_no;
	int type;
	u16 now_bgm_no = Snd_NowBgmNoGet();		//����BGM�i���o�[�擾

	//�V�[�P���X�i���o�[����A�v���C���[�i���o�[���擾
	player_no = Snd_GetPlayerNo( now_bgm_no );
	if( player_no == 0xff ){
		return;		//���݂̃V�[�P���X�i���o�[��0�Ȃ̂ŉ������Ȃ��I
	}

	//���łɃt�F�[�h�A�E�g���̎��́A�]�[�����s�����藈���肵�Ă��A
	//�t�F�[�h�A�E�g����BGM�͂��̂܂܂ɂ���I
	
	//�t�F�[�h���łȂ���
	if( Snd_FadeCheck() == 0 ){

		//�v���C���[�i���o�[����A�n���h���i���o�[���擾
		type = Snd_GetHandleNoByPlayerNo( player_no );

		//�n���h���̃A�h���X���擾
		Snd_PlayerMoveVolume( type, vol, frame );
		Snd_FadeCountSet( frame );			//�t�F�[�h�J�E���^�[�Z�b�g
	}

	Snd_StatusSet( SND_STATUS_FADEOUT );	//�X�e�[�^�X(�t�F�[�h�A�E�g)
	return;
}

//--------------------------------------------------------------
/**
 * @brief	�t�F�[�h�I���҂�
 *
 * @param	none
 *
 * @retval	"0=�I���A0�ȊO�̓t�F�[�h�J�E���^�[�̒l"
 */
//--------------------------------------------------------------
int Snd_FadeCheck()
{
	u16* fade_count = Snd_GetParamAdrs(SND_W_ID_FADE_COUNT);
	return (*fade_count);
}

//--------------------------------------------------------------
/**
 * @brief	BGM�I���҂�
 *
 * @param	no		BGM�i���o�[
 *
 * @retval	"�Đ���=TRUE�A�Đ��I��=FALSE"
 */
//--------------------------------------------------------------
int Snd_BgmPlayCheck( u16 no )
{
	u8 player_no;;

	//�V�[�P���X�i���o�[����A�v���C���[�i���o�[���擾
	player_no = Snd_GetPlayerNo( no );

	return Snd_PlayerCountPlayingSeq( player_no );
}

//--------------------------------------------------------------
/**
 * @brief	�S�Ă̍Đ����̃V�[�P���X���~
 *
 * @param	none
 *
 * @retval	none
 */
//--------------------------------------------------------------
void Snd_Stop(void)
{
	u8* ch_normal_flag = Snd_GetParamAdrs(SND_W_ID_WAVEOUT_CH_NORMAL_FLAG);
	u8* ch_chorus_flag = Snd_GetParamAdrs(SND_W_ID_WAVEOUT_CH_CHORUS_FLAG);

	NNS_SndPlayerStopSeqAll(0);										//�S��

	//Snd_WaveOutStop �� Snd_WaveOutHandleGet���ŁA
	//�m�ۂ��Ă��Ȃ��`�����l���ɃA�N�Z�X���悤�Ƃ���ƁA
	//�A�T�[�g�Ŏ~�܂�̂ŁA�����Ń`�F�b�N���ČĂ΂Ȃ��悤�ɂ��Ă���
	if( *ch_normal_flag == 1 ){										//�m�ۃt���O��ON��������
		Snd_WaveOutStop( WAVEOUT_CH_NORMAL );						//�g�`��~
	}

	if( *ch_chorus_flag == 1 ){										//�m�ۃt���O��ON��������
		Snd_WaveOutStop( WAVEOUT_CH_CHORUS );						//�g�`��~
	}

	Snd_StatusSet( SND_STATUS_STOP );								//�X�e�[�^�X(��~)
	return;
}

//--------------------------------------------------------------
/**
 * @brief	�t�B�[���hBGM�ȊO�̑S�Ă̍Đ����̃V�[�P���X���~
 *
 * @param	none
 *
 * @retval	none
 */
//--------------------------------------------------------------
void Snd_StopEx(void)
{
	int i;
	u8* ch_normal_flag = Snd_GetParamAdrs(SND_W_ID_WAVEOUT_CH_NORMAL_FLAG);
	u8* ch_chorus_flag = Snd_GetParamAdrs(SND_W_ID_WAVEOUT_CH_CHORUS_FLAG);

	NNS_SndPlayerStopSeq( Snd_HandleGet(SND_HANDLE_BGM), 0 );		//�t�B�[���hBGM�ȊO
	Snd_BgmStopSub();

	for( i=0; i < SE_HANDLE_MAX ;i++ ){			//SE
		Snd_SeStop( (SND_HANDLE_SE_1 + i), 0 ); 
	}

	Snd_PMVoiceStop(0);							//PV

	//Snd_WaveOutStop �� Snd_WaveOutHandleGet���ŁA
	//�m�ۂ��Ă��Ȃ��`�����l���ɃA�N�Z�X���悤�Ƃ���ƁA
	//�A�T�[�g�Ŏ~�܂�̂ŁA�����Ń`�F�b�N���ČĂ΂Ȃ��悤�ɂ��Ă���
	if( *ch_normal_flag == 1 ){										//�m�ۃt���O��ON��������
		Snd_WaveOutStop( WAVEOUT_CH_NORMAL );						//�g�`��~
	}

	if( *ch_chorus_flag == 1 ){										//�m�ۃt���O��ON��������
		Snd_WaveOutStop( WAVEOUT_CH_CHORUS );						//�g�`��~
	}

	//�t�B�[���hBGM�̓|�[�Y�A���A����̂ŁA��~�������Ă�ł͂����Ȃ��I
	//�|�[�Y��Ԃ̂܂܂ɂ��Ă����I
	
	return;
}


//==============================================================================================
//
//	SE�֘A
//
//==============================================================================================

//--------------------------------------------------------------
/**
 * @brief	SE�Đ� + �p������
 *
 * @param	no		SE�i���o�[
 * @param	pan		-128 �` 127
 *
 * @retval	"�Đ�����=TRUE�A���s=FALSE"
 */
//--------------------------------------------------------------
BOOL Snd_SePlayPan( u16 no, int pan )
{
	int ret;

	ret = Snd_SePlay( no );
	Snd_SePanSet( no, 0xffff, pan );

	return ret;
}


//--------------------------------------------------------------
/**
 * @brief	SE�Đ�
 *
 * @param	no		SE�i���o�[
 *
 * @retval	"�Đ�����=TRUE�A���s=FALSE"
 */
//--------------------------------------------------------------
BOOL Snd_SePlay( u16 no )
{
	int type,ret;

	//OS_Printf( "\n***************SE �Đ�\tno = %d\n", no );

	//�V�[�P���X�i���o�[����ASE�̃v���C���[�i���o�[���擾�A
	//SE�̃v���C���[�i���o�[����ASE�̃n���h���i���o�[���擾
	type = Snd_GetHandleNoByPlayerNo( Snd_GetPlayerNo(no) );

	//�V�[�P���X�Đ�
	ret = NNS_SndArcPlayerStartSeq( Snd_HandleGet(type), no );
	Snd_VChatVolSet( no, type );										//�{�C�X�`���b�g���ʑ���

	//�Đ����s�`�F�b�N
	if( ret == 0 ){
//#ifdef SOUND_OS_PRINT_ON
		OS_Printf( "SE �Đ����s\tno = %d\n", no );
//#endif
	}

	return ret;
}

//--------------------------------------------------------------
/**
 * @brief	SE��~(�V�[�P���X�i���o�[�w���)
 *
 * @param	no		SE�ԍ�
 * @param	frame	�w�肵���t���[���������ď��X�ɉ��ʂ𗎂Ƃ��Ă���
 *
 * @retval	none
 */
//--------------------------------------------------------------
void Snd_SeStopBySeqNo( u16 no, int frame )
{
	NNS_SndPlayerStopSeqBySeqNo( no, frame );
	return;
}

//--------------------------------------------------------------
/**
 * @brief	SE��~(�T�E���h�n���h���w���)
 *
 * @param	type	�T�E���h�n���h���^�C�v
 * @param	frame	�w�肵���t���[���������ď��X�ɉ��ʂ𗎂Ƃ��Ă���
 *
 * @retval	none
 *
 * �T�E���h�n���h���������̏ꍇ�́A�������܂���B 
 */
//--------------------------------------------------------------
void Snd_SeStop( int type, int frame )
{
	NNS_SndPlayerStopSeq( Snd_HandleGet(type), frame );
	return;
}

//--------------------------------------------------------------
/**
 * @brief	SE�I���҂�
 *
 * @param	no		SE�i���o�[
 *
 * @retval	"�Đ���=TRUE�A�Đ��I��=FALSE"
 *
 * �w�肵��SE���I�����Ă��邩�`�F�b�N�ł͂Ȃ��A
 * �w�肵��SE�̎g�p����v���C���[�ɁA
 * �Đ����̃V�[�P���X�����邩�̃`�F�b�N�ł��B
 */
//--------------------------------------------------------------
int Snd_SePlayCheck( u16 no )
{
	return Snd_PlayerCountPlayingSeq( Snd_GetPlayerNo(no) );

	//�ȉ��ۗ�
	//(�v���C���[�i���o�[�ł͂Ȃ��A�V�[�P���X�i���o�[�ł��`�F�b�N�ł���)
	//NNS_SndPlayerCountPlayingSeqBySeqNo�֐��́A
	//�V�[�P���X�ԍ�seqNo���w�肵�āA�Đ����̃V�[�P���X�̐��𐔂��܂��B
	//����́ANNS_SndPlayerSetSeqNo�֐��ŃZ�b�g�����V�[�P���X�ԍ����A
	//seqNo�Ɠ����ł���V�[�P���X�̐��𐔂��܂��B 
}

//--------------------------------------------------------------
/**
 * @brief	�S�Ă�SE�I���҂�
 *
 * @param	none
 *
 * @retval	"�Đ���=TRUE�A�Đ��I��=FALSE"
 */
//--------------------------------------------------------------
int Snd_SePlayCheckAll()
{
	int i;

	for( i=0; i < SE_HANDLE_MAX ;i++ ){
		if( Snd_PlayerCountPlayingSeq(PLAYER_SE_1+i) == TRUE ){
			return TRUE;
		}
	}

	return FALSE;
}

//--------------------------------------------------------------
/**
 * @brief	SE��PAN(���)��ύX
 *
 * @param	no		SE�i���o�[
 * @param	bitmask	�g���b�N�r�b�g�}�X�N
 * @param	pan		-128 �` 127
 *
 * @retval	none
 *
 * trackBitMask�ŁA�ݒ肷��g���b�N���w�肵�܂��B
 * ���ʃr�b�g���珇�ɁA�g���b�N0�A�g���b�N1�A�g���b�N2�A�A�A��\���A
 * �r�b�g�������Ă���g���b�N�S�Ăɑ΂��āA�p����ύX���܂��B
 *
 * �Ⴆ�΁A�g���b�N2�ƃg���b�N5�̃p����ύX�������ꍇ�́A 
 * (1 << 2) | (1 << 5) ���Ȃ킿�A0x0024 �Ƃ��܂��B 
 */
//--------------------------------------------------------------
void Snd_SePanSet( u16 no, u16 bitmask, int pan )
{
	int type;

	//�V�[�P���X�i���o�[����ASE�̃v���C���[�i���o�[���擾�A
	//SE�̃v���C���[�i���o�[����ASE�̃n���h���i���o�[���擾
	type = Snd_GetHandleNoByPlayerNo( Snd_GetPlayerNo(no) );

	NNS_SndPlayerSetTrackPan( Snd_HandleGet(type), bitmask, pan );
	return;
}

//--------------------------------------------------------------
/**
 * @brief	�S�Ă�SE��PAN(���)��ύX
 *
 * @param	pan		-128 �` 127
 *
 * @retval	none
 */
//--------------------------------------------------------------
void Snd_SePanSetAll( int pan )
{
	int type, i;

	//SE�̃v���C���[�i���o�[����ASE�̃n���h���i���o�[���擾
	type = Snd_GetHandleNoByPlayerNo( PLAYER_SE_1 );

	for( i=0; i < SE_HANDLE_MAX ;i++ ){
		NNS_SndPlayerSetTrackPan( Snd_HandleGet(type+i), 0xffff, pan );
	}

	return;
}


//==============================================================================================
//
//	�|�P���������֘A
//
//	�����Ή���
//	�g�`�Đ�(�t�Đ�)���g�p���Ă���Z�̍Ō�ɁAFreeChannel������I
//
//==============================================================================================
 
//--------------------------------------------------------------
/**
 * @brief	�|�P���������Đ�(�����ōĐ��O�ɒ�~���Ă΂�܂�)
 *
 * @param	no		�|�P�����i���o�[
 *
 * @retval	"�Đ�����=TRUE�A���s=FALSE"
 *
 * ��O�Ƃ��āA�R�[���X���g�p���鎞�́A��~�͌Ă΂�܂���B
 *
 * �|�P�����i���o�[�ƁA�����V�[�P���X�f�[�^�̕��т��������m�F����I
 * (�S���}�Ӄi���o�[�ɑΉ����Ă���炵���B050722��V��������)
 *
 * <����>
 * �V�[�P���X�A�[�J�C�u���ƁA�v���C���[�q�[�v���g���Ȃ��I
 * �V�[�P���X���ƁA�v���C���[�q�[�v���g����I
 */
//--------------------------------------------------------------
BOOL Snd_PMVoicePlay( u16 no )
{
	int ret;
	u8* chorus_flag			= Snd_GetParamAdrs( SND_W_ID_CHORUS_FLAG );
	PERAPVOICE** my_perap	= Snd_GetParamAdrs( SND_W_ID_MY_PERAP_PTR );

	//�s���Ȓl�`�F�b�N
	if( no != MONSNO_PERAPPU ){								//�f�o�b�N�̂��߂؃��b�v�͗�O�ɂ��Ă���
		if( (no > MONSNO_MAX) || (no == 0) ){
			//GF_ASSERT( (0) && "�|�P�����i���o�[���s���ł��I" );
			//return FALSE;	//�G���[
			OS_Printf( "�|�P�����i���o�[���s���ł��I" );
			no = MONSNO_HUSIGIDANE;
		}
	}

#if 1
	//�ʐM�̎��́A���̊֐��͎g�p���Ȃ��I

	//Snd_PerapVoicePlay�ő��l�̂؃��b�v�Đ����o���Ȃ��āA
	//���̊֐��ɂ������́Adefault_flag�������Ă���̂ŁA
	//�������Đ��ł����ɁA�ʏ�̍Đ��֐i��
	
	//�؃��b�v�i���o�[���`�F�b�N
	if( no == MONSNO_PERAPPU ){
		
		//�����̂؃��b�v�̘^�������f�[�^���Đ�
		if( Snd_PerapVoicePlaySub(*my_perap, PM_MALE, PV_VOL_MAX, 0) == TRUE ){	//���ʑΉ�����I
			//�Đ��������̂Ńt���O�𗎂Ƃ�
			Snd_PerapVoiceDefaultFlagSet(FALSE);//�؃��b�v�̃f�t�H���g�̖������Đ�����t���OOFF
			return TRUE;
		}
	}
#endif

	//�R�[���X�g�p�t���O���`�F�b�N
	if( *chorus_flag == 0 ){
		//�V�[�P���X��2�Đ�����Ȃ��悤�ɒ�~�������Ă�
		Snd_PMVoiceStop(0);
#if 0
		ret = NNS_SndArcPlayerStartSeq( Snd_HandleGet(SND_HANDLE_PMVOICE), no );
#else
		//�e�ʍ팸
		//
		//sound_data.sarc��seq�f�[�^���L�q���Ȃ��Ă��o���N�i���o�[���擾�o����B
		//(���ʃe�[�u���͕ʂɎ����Ȃ��Ƃ����Ȃ��Ȃ邪5000byte���炢�팸�o����)
		//
		//�����A�S���}�Ӄi���o�[���p�ɂɕς�邱�Ƃ�z�肷��ƁA
		//�F�X�ȏ��Ń|�P�����i���o�[�̏��Ԃ��֘A����̂͑Ή����Y��̂��ƂȂ̂ŁA
		//sound_data.sarc��seq�f�[�^�������`�Ői�߂�I
		//
		//���ʂ��V�[�P���X�f�[�^�Ŏ��������Ȃ������B�B�B
		//����O���特�ʂ�������čĐ��Ȃǂ̌`�Ȃ̂ŁA
		//��{�̉��ʐݒ���������ɂ́A���̒l�ɑ΂��Ăǂ����邩�����߂Ȃ��Ƃ����Ȃ��B
		//�O�́A�X�̃|�P�����̉��ʐݒ肪����Ǝv���Ă��Ȃ��`�ɂȂ��Ă���B�B�B
		ret = NNS_SndArcPlayerStartSeqEx( Snd_HandleGet(SND_HANDLE_PMVOICE), -1, no, -1, SEQ_PV );
#endif
		Snd_VChatVolSet( no, SND_HANDLE_PMVOICE );						//�{�C�X�`���b�g���ʑ���
	}else{
		//�V�[�P���X��2�Đ������
#if 0
		ret = NNS_SndArcPlayerStartSeq( Snd_HandleGet(SND_HANDLE_CHORUS), no );
#else
		ret = NNS_SndArcPlayerStartSeqEx( Snd_HandleGet(SND_HANDLE_CHORUS), -1, no, -1, SEQ_PV );
#endif
		Snd_VChatVolSet( no, SND_HANDLE_CHORUS );						//�{�C�X�`���b�g���ʑ���
	}

	//�Đ��������̂Ńt���O�𗎂Ƃ�
	Snd_PerapVoiceDefaultFlagSet(FALSE);	//�؃��b�v�̃f�t�H���g�̖������Đ�����t���OOFF

	//�Đ����s�`�F�b�N
	if( ret == 0 ){
		OS_Printf( "PMVOICE �Đ����s\tno = %d\n", no );
	}

	return ret;
}
 
//--------------------------------------------------------------
/**
 * @brief	�|�P����������~(�T�E���h�n���h���w���)
 *
 * @param	frame	�w�肵���t���[���������ď��X�ɉ��ʂ𗎂Ƃ��Ă���
 *
 * @retval	none
 *
 * �T�E���h�n���h���������̏ꍇ�́A�������܂���B 
 *
 * �R�[���X(������p)�T�E���h�n���h������~�����Ă��܂��B
 *
 * �t�Đ��g�p�t���O�������Ă�����A�g�`��~�������ĂԂ悤�ɂ��Ă���
 * �|�P�����̖������~���鏈���͂��̊֐����Ăׂ΂悢�B
 */
//--------------------------------------------------------------
void Snd_PMVoiceStop( int frame )
{
	u8* ch_normal_flag = Snd_GetParamAdrs(SND_W_ID_WAVEOUT_CH_NORMAL_FLAG);
	u8* ch_chorus_flag = Snd_GetParamAdrs(SND_W_ID_WAVEOUT_CH_CHORUS_FLAG);
	u8* reverse_flag   = Snd_GetParamAdrs(SND_W_ID_REVERSE_FLAG);

	NNS_SndPlayerStopSeq( Snd_HandleGet(SND_HANDLE_PMVOICE), frame );	//����
	NNS_SndPlayerStopSeq( Snd_HandleGet(SND_HANDLE_CHORUS), frame );	//�R�[���X

	//Snd_WaveOutStopReverse�̒��ł��`�F�b�N���Ă���̂ō폜(06.03.09)
	//if( *reverse_flag == 1 ){								//�t�Đ��g�p�t���O�������Ă�����

		if( *ch_normal_flag == 1 ){										//CH�m�ۂ��Ă�����
			Snd_WaveOutStopReverse( WAVEOUT_CH_NORMAL );				//buf�J��
			Snd_WaveOutFreeChannel( WAVEOUT_CH_NORMAL );				//ch �J��(06.07.17)
		}
		if( *ch_chorus_flag == 1 ){										//CH�m�ۂ��Ă�����
			Snd_WaveOutStopReverse( WAVEOUT_CH_CHORUS );				//buf�J��
			Snd_WaveOutFreeChannel( WAVEOUT_CH_CHORUS );				//ch �J��(06.07.17)
		}
	//}

	Snd_PerapVoiceStop();									//�y���b�v�Đ����t���O�̃N���A

	return;
}

//--------------------------------------------------------------
/**
 * @brief	�|�P���������I���҂�
 *
 * @param	none
 *
 * @retval	"�Đ���=1�ȏ�A�Đ��I��=0"
 */
//--------------------------------------------------------------
int Snd_PMVoicePlayCheck(void)
{
	u8* ch_normal_flag = Snd_GetParamAdrs(SND_W_ID_WAVEOUT_CH_NORMAL_FLAG);
	u8* ch_chorus_flag = Snd_GetParamAdrs(SND_W_ID_WAVEOUT_CH_CHORUS_FLAG);
	u8* reverse_flag   = Snd_GetParamAdrs(SND_W_ID_REVERSE_FLAG);

	//�t�Đ����g�p���Ă��鎞�́A�g�`�Đ��������`�F�b�N����悤�ɂ���I
	//if( *reverse_flag == 1 ){									//�t�Đ��g�p�t���O�������Ă�����
		if( *ch_normal_flag == 1 ){								//CH�m�ۂ��Ă�����
			return Snd_WaveOutIsPlaying( WAVEOUT_CH_NORMAL );
		}
		if( *ch_chorus_flag == 1 ){								//CH�m�ۂ��Ă�����
			return Snd_WaveOutIsPlaying( WAVEOUT_CH_CHORUS );
		}
	//}

	//OS_Printf( "play check %d\n", Snd_PlayerCountPlayingSeq( PLAYER_PV ) );
	return Snd_PlayerCountPlayingSeq( PLAYER_PV );
}


//==============================================================================================
//
//	�|�P���������p�^�[���֘A
//
//	<���Ή�>
//	�Z�̏I���̃^�C�~���O�ŁA�g�`�Đ��p�Ɋm�ۂ����`�����l���̊J���������I
//
//==============================================================================================

//--------------------------------------------------------------
/**
 * @brief	�|�P���������Đ�(�p�^�[���w���)
 *
 * @param	no		�|�P�����i���o�[
 * @param	pan		-128 �` 127
 * @param	vol		�{�����[��(0-127)
 * @param	ptn		�p�^�[��(snd_tool.h�Q��)
 * @param	heap_id	�q�[�vID
 *
 * @retval	"����=TRUE�A���s=FALSE"(����́A�K�������ɂȂ��Ă���B�B�B)
 *
 * <����>
 * PITCH	ABG=256,DS=64������
 * CHORUS	�s�b�`�̍�(-64�`64)
 *
 * �������g�p����Z�́A�u�Ȃ������A�ق���A�Ƃ��ڂ��A�n�C�p�[�{�C�X�v���炢�B
 *
 * PLAYER_PV�́A�V�[�P���X�����ő吔��2�ɐݒ肵�Ă���B
 * Snd_PMVoicePlay�֐����ŁA�Đ������O�ɒ�~�������Ă�ŁA
 * 2�̃V�[�P���X���Đ�����Ȃ��悤�ɂ��Ă���B
 * �R�[���X���g�p���鎞�́Awk->chorus_flag�����̂ŁA
 * Snd_PMVoicePlay�֐����ŁA�t���O���݂āA��~�������Ă΂Ȃ��悤�ɂ��Ă���
 *
 * �g�p���Ă��Ȃ������ɂ́A"PV_PTN_PARAM_NONE"��n���Ă����ĉ�����
 */
//--------------------------------------------------------------
BOOL Snd_PMVoicePlayEx( int ptn, u16 no, int pan, int vol, int heap_id )
{
	int wave_pan,chorus_vol;
	u16 monsno;
	u16	pitch;						//����(64)
	//u8	release;				//�L�[�I�t��̃����[�X�w��p
	int ret1,ret2,ret3,ret4;
	u8* ch_normal_flag		= Snd_GetParamAdrs(SND_W_ID_WAVEOUT_CH_NORMAL_FLAG);
	u8* ch_chorus_flag		= Snd_GetParamAdrs(SND_W_ID_WAVEOUT_CH_CHORUS_FLAG);
	u8* chorus_flag			= Snd_GetParamAdrs(SND_W_ID_CHORUS_FLAG);
	u8* perap_play_flag		= Snd_GetParamAdrs( SND_W_ID_PERAP_PLAY_FLAG );
	PERAPVOICE** my_perap	= Snd_GetParamAdrs( SND_W_ID_MY_PERAP_PTR );

	ret1 = 0;
	ret2 = 0;
	ret3 = 0;
	ret4 = 0;

	//�V�[�P���X�Đ��̃p����(-127 - 0 - 127)�ƂȂ��Ă���
	//�g�`�Đ��̃p����(0 - 64 - 127)�ƂȂ��Ă���
	
	//�g�`�Đ��p�����擾
	if( pan < 0 ){
		wave_pan = 64 + (pan / 2);		//0 - 64  �ɂ���
	}else{
		wave_pan = 64 + (pan / 2);		//64 - 127 �ɂ���
	}

	//�R�[���X�̉��ʐݒ�
	chorus_vol = vol - 30;
	if( chorus_vol <= 0 ){
		chorus_vol = 1;
	}

	//�����l���
	//release	= DEFAULT_RELEASE;
	pitch = 0;

	*chorus_flag = 0;			//�R�[���X�g�p�t���OOFF

	//�`�����l�����m�ۂ��Ă�����J��
	if( *ch_normal_flag == 1 ){
		Snd_WaveOutStopReverse( WAVEOUT_CH_NORMAL );		//buf�J��
		Snd_WaveOutFreeChannel( WAVEOUT_CH_NORMAL );		//ch �J��
	}
	if( *ch_chorus_flag == 1 ){
		Snd_WaveOutStopReverse( WAVEOUT_CH_CHORUS );		//buf�J��
		Snd_WaveOutFreeChannel( WAVEOUT_CH_CHORUS );		//ch �J��
	}

#if 1
	//�s���Ȓl�`�F�b�N
	
	monsno = no;

	if( no != MONSNO_PERAPPU ){								//�f�o�b�N�̂��߂؃��b�v�͗�O�ɂ��Ă���
		if( (no > MONSNO_MAX) || (no == 0) ){
			OS_Printf( "�|�P�����i���o�[���s���ł��I" );
			monsno = MONSNO_HUSIGIDANE;
		}
	}
#endif

#if 1
	//�؃��b�v��������
	if( no == MONSNO_PERAPPU ){

		switch( ptn ){

		//�����̂؃��b�v�̘^�������f�[�^���Đ�
		case PV_NORMAL:		// = 0 �ʏ�Đ�
		case PV_HALF:		// = 1 �Đ����ԒZ�k�i�Q�����Q�o�g���Ń|�P�����o�ꎞ�j
		case PV_FLDEVENT:	// = 2 �{�����|�P�����i�t�B�[���h�C�x���g�j
		case PV_POKEDOWN:	// = 5 �|�P���������ꂽ��
		case PV_PINCHNORMAL:// =11 �ʏ�Đ�(���C�Ȃ�)
		case PV_PINCHHALF:	// =12 �Đ����ԒZ�k�i�Q�����Q�o�g���Ń|�P�����o�ꎞ�j(���C�Ȃ�)

			Snd_PMVoicePlay( MONSNO_PERAPPU );

			//�؃��b�v�̘^�������f�[�^���Đ����Ă��邩�t���O���`�F�b�N
			if( *perap_play_flag == 0 ){
				Snd_PlayerSetTrackPan( SND_HANDLE_PMVOICE, 0xffff, pan );
				Snd_PMVoiceVolSet( monsno, SND_HANDLE_PMVOICE, vol );				//���ʑ���
			}else{
				Snd_WaveOutSetPan( WAVEOUT_CH_NORMAL, wave_pan );
				Snd_WaveOutSetVolume( WAVEOUT_CH_NORMAL, vol );
			}
			return TRUE;		//���ӁI

		//��L�ȊO�́A�f�t�H���g�̖������Đ�����I
		default:
			Snd_PerapVoiceDefaultFlagSet(TRUE);	//�؃��b�v�̃f�t�H���g�̖������Đ�����t���OON
			break;
		}
	}
#endif

	switch( ptn ){

	// = 0 �ʏ�Đ�
	case PV_NORMAL:
		//----------------
		//play
		//pan,vol
		//----------------
		ret1 = Snd_PMVoicePlay( monsno );
		Snd_PlayerSetTrackPan( SND_HANDLE_PMVOICE, 0xffff, pan );
		Snd_PMVoiceVolSet( monsno, SND_HANDLE_PMVOICE, vol );					//���ʑ���
		break;

	// = 1 �Đ����ԒZ�k�i�Q�����Q�o�g���Ń|�P�����o�ꎞ�j
	case PV_HALF:
		//----------------
		//play
		//pan,vol,length
		//----------------
		ret1 = Snd_PMVoicePlay( monsno );
		Snd_PlayerSetTrackPan( SND_HANDLE_PMVOICE, 0xffff, pan );
		Snd_PMVoiceVolSet( monsno, SND_HANDLE_PMVOICE, vol );					//���ʑ���
		Snd_PMVoiceLengthSet(20,heap_id);										//release = 225;
		break;

	// = 2 �{�����|�P�����i�t�B�[���h�C�x���g�j
	case PV_FLDEVENT:		
		//----------------
		//play
		//pan,vol,pitch
		//
		//chorus
		//pan,vol
		//----------------
		ret1 = Snd_PMVoicePlay( monsno );
		Snd_PlayerSetTrackPan( SND_HANDLE_PMVOICE, 0xffff, pan );
		//release		= 225;
		Snd_PMVoiceVolSet( monsno, SND_HANDLE_PMVOICE, vol );				//���ʑ���
		//Snd_PlayerSetTrackPitch( SND_HANDLE_PMVOICE, 0xffff, 3840/6 );	//�s�b�`
		Snd_PlayerSetTrackPitch( SND_HANDLE_PMVOICE, 0xffff, 64 );			//�s�b�`

		ret3 = Snd_ChorusPlay( monsno, 20 );								//�R�[���X(���ӁI)
		Snd_PlayerSetTrackPan( SND_HANDLE_CHORUS, 0xffff, pan );
		Snd_PMVoiceVolSet( monsno, SND_HANDLE_CHORUS, chorus_vol );			//���ʑ���
		break;

	// = 3 �Z���ʉ��E�Ƃ��ڂ��p
	case PV_W_TOOBOE:	
		//----------------
		//play
		//pan,vol,length,pitch
		//
		//chorus
		//pan,vol
		//----------------
		ret1 = Snd_PMVoicePlay( monsno );
		Snd_PlayerSetTrackPan( SND_HANDLE_PMVOICE, 0xffff, pan );
		Snd_PMVoiceVolSet( monsno, SND_HANDLE_PMVOICE, vol );					//���ʑ���
		//Snd_PMVoiceLengthSet(15,heap_id);//(50);
		Snd_PMVoiceLengthSet(30,heap_id);//(50);								//release = 200;
		//Snd_PlayerSetTrackPitch( SND_HANDLE_PMVOICE, 0xffff, 3904/6 );		//�s�b�`
		//Snd_PlayerSetTrackPitch( SND_HANDLE_PMVOICE, 0xffff, 110 );			//�s�b�`
		//Snd_PlayerSetTrackPitch( SND_HANDLE_PMVOICE, 0xffff, 120 );			//�s�b�`
		//Snd_PlayerSetTrackPitch( SND_HANDLE_PMVOICE, 0xffff, 160 );			//�s�b�`
		Snd_PlayerSetTrackPitch( SND_HANDLE_PMVOICE, 0xffff, 192 );				//�s�b�`

		//ret3 = Snd_ChorusPlay( monsno, 20 );									//�R�[���X(���ӁI)
		ret3 = Snd_ChorusPlay( monsno, 16 );									//�R�[���X(���ӁI)
		Snd_PlayerSetTrackPan( SND_HANDLE_CHORUS, 0xffff, pan );
		Snd_PMVoiceVolSet( monsno, SND_HANDLE_CHORUS, chorus_vol );				//���ʑ���
		break;

	// = 4 �Z���ʉ��E�n�C�p�[�{�C�X�p�P
	case PV_W_HYPER1:		
		//----------------
		//reverse
		//
		//chorus
		//----------------
		ret2 = Snd_WaveOutAllocChannel( WAVEOUT_CH_NORMAL );
		ret2 = Snd_WaveOutStartReverse( monsno, vol, wave_pan, WAVEOUT_CH_NORMAL, heap_id );
		Snd_WaveOutSetPan( WAVEOUT_CH_NORMAL, wave_pan );					//�p��
		//Snd_PMVoiceLengthSet(25,heap_id);									//release = 100;
		//Snd_PMVoiceLengthSet(20,heap_id);									//release = 100;
		Snd_PMVoiceLengthSet(15,heap_id);									//release = 100;
		Snd_WaveOutSetSpeed( WAVEOUT_CH_NORMAL, W_HYPER_VOICE_PITCH );

		//�R�[���X(���ӁI)
		//ret4 = Snd_ChorusPlayReverse(monsno, -64, VOICE_SMALL_VOL, wave_pan, heap_id);
		ret4 = Snd_ChorusPlayReverse(monsno, -64, chorus_vol, wave_pan, heap_id);
		Snd_WaveOutSetSpeed( WAVEOUT_CH_CHORUS, W_HYPER_VOICE_PITCH );
		break;

	// = 5 �|�P���������ꂽ��
	case PV_POKEDOWN:			
		//----------------
		//play
		//pan,vol,pitch
		//----------------
		ret1 = Snd_PMVoicePlay( monsno );
		Snd_PlayerSetTrackPan( SND_HANDLE_PMVOICE, 0xffff, pan );
		Snd_PMVoiceVolSet( monsno, SND_HANDLE_PMVOICE, vol );					//���ʑ���
		//Snd_PlayerSetTrackPitch( SND_HANDLE_PMVOICE, 0xffff, 3584/6 );		//�s�b�`
		Snd_PlayerSetTrackPitch( SND_HANDLE_PMVOICE, 0xffff, -224 );			//�s�b�`
		break;

	// = 6 �Z���ʉ��E�n�C�p�[�{�C�X�p�Q
	case PV_W_HYPER2:			
		//----------------
		//play
		//pan,vol,pitch
		//
		//chorus
		//pan
		//----------------
		ret1 = Snd_PMVoicePlay( monsno );
		Snd_PlayerSetTrackPan( SND_HANDLE_PMVOICE, 0xffff, pan );
		//release		= 220;
		Snd_PMVoiceVolSet( monsno, SND_HANDLE_PMVOICE, vol );						//���ʑ���
		//Snd_PlayerSetTrackPitch( SND_HANDLE_PMVOICE, 0xffff, 3904/6 );			//�s�b�`
		Snd_PlayerSetTrackPitch( SND_HANDLE_PMVOICE, 0xffff, 44 );					//�s�b�`

		ret3 = Snd_ChorusPlay( monsno, -64 );	//�R�[���X(���ӁI)
		Snd_PlayerSetTrackPan( SND_HANDLE_CHORUS, 0xffff, pan );
		Snd_PMVoiceVolSet( monsno, SND_HANDLE_CHORUS, chorus_vol );					//���ʑ���
		break;

	// = 7 �Z���ʉ��E�ق���P
	case PV_W_HOERU1:		
		//----------------
		//play
		//pan,vol,length,pitch
		//----------------
		ret1 = Snd_PMVoicePlay( monsno );
		Snd_PlayerSetTrackPan( SND_HANDLE_PMVOICE, 0xffff, pan );
		Snd_PMVoiceVolSet( monsno, SND_HANDLE_PMVOICE, vol );					//���ʑ���
		//Snd_PMVoiceLengthSet(10,heap_id);										//release = 100;
		Snd_PMVoiceLengthSet(11,heap_id);										//release = 100;
		//Snd_PlayerSetTrackPitch( SND_HANDLE_PMVOICE, 0xffff, 3584/6 );		//�s�b�`
		Snd_PlayerSetTrackPitch( SND_HANDLE_PMVOICE, 0xffff, -128 );			//�s�b�`
		break;

	// = 8 �Z���ʉ��E�ق���Q
	case PV_W_HOERU2:			
		//----------------
		//play
		//pan,vol,length,pitch
		//----------------
		ret1 = Snd_PMVoicePlay( monsno );
		Snd_PlayerSetTrackPan( SND_HANDLE_PMVOICE, 0xffff, pan );
		Snd_PMVoiceVolSet( monsno, SND_HANDLE_PMVOICE, vol );					//���ʑ���
		Snd_PMVoiceLengthSet(60,heap_id);										//release = 225;
		//Snd_PlayerSetTrackPitch( SND_HANDLE_PMVOICE, 0xffff, 3904/6 );		//�s�b�`
		Snd_PlayerSetTrackPitch( SND_HANDLE_PMVOICE, 0xffff, 60 );				//�s�b�`
		break;

	// = 9 �Z���ʉ��E�Ȃ������P
	case PV_W_NAKIGOE1:		
		//----------------
		//reverse
		//----------------
		ret2 = Snd_WaveOutAllocChannel( WAVEOUT_CH_NORMAL );
		ret2 = Snd_WaveOutStartReverse( monsno, vol, wave_pan, WAVEOUT_CH_NORMAL, heap_id );
		Snd_WaveOutSetPan( WAVEOUT_CH_NORMAL, wave_pan );						//�p��
		//Snd_PMVoiceLengthSet(15,heap_id);
		Snd_PMVoiceLengthSet(13,heap_id);										//release = 125;
		Snd_WaveOutSetSpeed( WAVEOUT_CH_NORMAL, W_NAKIGOE_PITCH );
		break;

	// =10 �Z���ʉ��E�Ȃ������Q
	case PV_W_NAKIGOE2:			
		//----------------
		//play
		//pan,vol,length,pitch
		//----------------
		ret1 = Snd_PMVoicePlay( monsno );
		Snd_PlayerSetTrackPan( SND_HANDLE_PMVOICE, 0xffff, pan );
		Snd_PMVoiceVolSet( monsno, SND_HANDLE_PMVOICE, vol );					//���ʑ���
		Snd_PMVoiceLengthSet(100,heap_id);										//release = 225
		//Snd_PlayerSetTrackPitch( SND_HANDLE_PMVOICE, 0xffff, 3904/6 );		//�s�b�`
		//Snd_PlayerSetTrackPitch( SND_HANDLE_PMVOICE, 0xffff, -96 );			//�s�b�`
		//Snd_PlayerSetTrackPitch( SND_HANDLE_PMVOICE, 0xffff, -64 );			//�s�b�`
		//Snd_PlayerSetTrackPitch( SND_HANDLE_PMVOICE, 0xffff, -21 );			//�s�b�`
		//Snd_PlayerSetTrackPitch( SND_HANDLE_PMVOICE, 0xffff, -32 );			//�s�b�`
		//Snd_PlayerSetTrackPitch( SND_HANDLE_PMVOICE, 0xffff, -48 );			//�s�b�`
		Snd_PlayerSetTrackPitch( SND_HANDLE_PMVOICE, 0xffff, -44 );				//�s�b�`
		break;

	// =11 �ʏ�Đ�(���C�Ȃ�)
	case PV_PINCHNORMAL:		
		//----------------
		//play
		//pan,vol,pitch
		//----------------
		ret1 = Snd_PMVoicePlay( monsno );
		Snd_PlayerSetTrackPan( SND_HANDLE_PMVOICE, 0xffff, pan );
		Snd_PMVoiceVolSet( monsno, SND_HANDLE_PMVOICE, vol );					//���ʑ���
		//Snd_PlayerSetTrackPitch( SND_HANDLE_PMVOICE, 0xffff, 3904/6 );		//�s�b�`
		//Snd_PlayerSetTrackPitch( SND_HANDLE_PMVOICE, 0xffff, -44 );			//�s�b�`
		Snd_PlayerSetTrackPitch( SND_HANDLE_PMVOICE, 0xffff, -96 );				//�s�b�`
		break;

	// =12 �Đ����ԒZ�k�i�Q�����Q�o�g���Ń|�P�����o�ꎞ�j(���C�Ȃ�)
	case PV_PINCHHALF:		
		//----------------
		//play
		//pan,vol,length,pitch
		//----------------
		ret1 = Snd_PMVoicePlay( monsno );
		Snd_PlayerSetTrackPan( SND_HANDLE_PMVOICE, 0xffff, pan );
		Snd_PMVoiceVolSet( monsno, SND_HANDLE_PMVOICE, vol );					//���ʑ���
		//Snd_PMVoiceLengthSet(20,heap_id);
		//Snd_PMVoiceLengthSet(15,heap_id);
		//Snd_PMVoiceLengthSet(13,heap_id);										//release = 225;
		Snd_PMVoiceLengthSet(20,heap_id);										//release = 225;
		//Snd_PlayerSetTrackPitch( SND_HANDLE_PMVOICE, 0xffff, 3904/6 );		//�s�b�`
		//Snd_PlayerSetTrackPitch( SND_HANDLE_PMVOICE, 0xffff, -128 );			//�s�b�`
		Snd_PlayerSetTrackPitch( SND_HANDLE_PMVOICE, 0xffff, -96 );				//�s�b�`
		break;	

	// =13 �}�ӃR�[���X�Đ�
	case PV_ZUKAN_CHORUS:		
		//----------------
		//play
		//
		//chorus
		//pan,vol
		//----------------
		Snd_PMVoicePlay( monsno );

		//���ӁI�@�{�����[���͌Œ�
		Snd_PMVoiceVolSet( monsno, SND_HANDLE_PMVOICE, PV_VOL_MAX );			//���ʑ���

		Snd_ChorusPlay( monsno, SND_ZUKAN_PITCH_CHORUS );						//�R�[���X(���ӁI)
		Snd_PlayerSetTrackPan( SND_HANDLE_CHORUS, 0xffff, pan );

		//���ӁI�@�R�[���X�̃{�����[���𑀍�o����悤�ɂ���
		//Snd_PlayerMoveVolume( SND_HANDLE_CHORUS, chorus_vol, 0 );			//�R�[���X�{�����[��
		Snd_PlayerMoveVolume( SND_HANDLE_CHORUS, vol, 0 );					//�R�[���X�{�����[��
		break;

	// =14 �}�Ӄm�[�}���Đ�
	case PV_ZUKAN_NORMAL:		
		//----------------
		//play
		//----------------
		ret1 = Snd_PMVoicePlay( monsno );
		break;
	}

#ifdef SOUND_OS_PRINT_ON
	OS_Printf( "1)pv play ptn normal = %d\n", ret1 );
	OS_Printf( "2)pv play ptn reverse = %d\n", ret2 );
	OS_Printf( "3)pv play ptn chorus = %d\n", ret3 );
	OS_Printf( "4)pv play ptn reverse chorus = %d\n\n", ret4 );
#endif

	return TRUE;
}

//--------------------------------------------------------------
/**
 * @brief	�|�P���������@���ʑ���(�����͊O���特�ʂ����炤�̂ŕK�v)
 *
 * @param	no			�V�[�P���X�i���o�[
 * @param	handle_no	�n���h���i���o�[
 * @param	vol			�{�����[��
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void Snd_PMVoiceVolSet( u16 seq_no, int handle_no, int vol )
{
	//�O����{�����[�����炤�̂ŕK�v
	Snd_PlayerSetInitialVolume( handle_no, vol );

	//�O������炤�{�����[���Ƃ͊֌W�Ȃ��A�f�t�H���g�̐ݒ�̔����ɂ���
	Snd_VChatVolSet( seq_no, handle_no );									//�{�C�X�`���b�g���ʑ���
	return;
}

//--------------------------------------------------------------
/**
 * @brief	�|�P���������Đ����ԃZ�b�g(TCB�ǉ�)
 *
 * @param	no		�V�[�P���X�i���o�[
 * @param	heap_id	�q�[�vID
 *
 * @retval	none
 */
//--------------------------------------------------------------
void Snd_PMVoiceLengthSet( int length, int heap_id )
{
	SND_PMVOICE_LENGTH_WORK* wk = NULL;
	TCB_PTR* length_tcb			= Snd_GetParamAdrs(SND_W_ID_LENGTH_TCB);

	//���łɓo�^����Ă�����TCB�폜
	if( *length_tcb != NULL ){
		OS_Printf( "\n�x���@�|�P��������\n" );
		OS_Printf( "�Đ����ԑ���TCB���I�����Ă��Ȃ��̂ɁA�ēx�Ă΂�Ă��܂��I\n" );
	}
	Snd_PMVoiceLengthTcbDel();

	wk = sys_AllocMemory( heap_id, sizeof(SND_PMVOICE_LENGTH_WORK) );
	if( wk == NULL ){
		GF_ASSERT( (0) && "�������m�ێ��s�I" );
		return;
	}
	memset( wk, 0, sizeof(SND_PMVOICE_LENGTH_WORK) );

	wk->length	= length;
	wk->tcb		= TCB_Add( Snd_PMVoiceLengthMainTCB, wk, 0 );
	*length_tcb = wk->tcb;
	return;
}

//���̒l���"length"���������Ȃ�Ɖ��ʂ����킹��"0"�ɂ��Ă���
//#define SND_PMVOICE_LENGTH_VOL		(20)
//���̒l��"length"���Ȃ������ɉ��ʂ�"0"�ɂȂ�悤�ɃZ�b�g����
#define SND_PMVOICE_LENGTH_VOL_SET		(10)
//--------------------------------------------------------------
/**
 * @brief	TCB���C��
 *
 * @param	tcb		TCB_PTR
 * @param	wk		���[�N�̃A�h���X
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void Snd_PMVoiceLengthMainTCB( TCB_PTR tcb, void* wk )
{
	u8* ch_normal_flag = Snd_GetParamAdrs(SND_W_ID_WAVEOUT_CH_NORMAL_FLAG);
	u8* ch_chorus_flag = Snd_GetParamAdrs(SND_W_ID_WAVEOUT_CH_CHORUS_FLAG);
	SND_PMVOICE_LENGTH_WORK* swk = (SND_PMVOICE_LENGTH_WORK *)wk;

#if 1
	//���ʂ����R�ɏ��������Ă���
	//if( swk->length < SND_PMVOICE_LENGTH_VOL ){
	
	//���ʂ�"0"�ɂȂ��Ă����悤�ɃZ�b�g����
	if( swk->length == SND_PMVOICE_LENGTH_VOL_SET ){
		Snd_PlayerMoveVolume( SND_HANDLE_PMVOICE, 0, swk->length );
		Snd_PlayerMoveVolume( SND_HANDLE_CHORUS, 0, swk->length );
	}
#endif

	swk->length--;

#ifdef SOUND_OS_PRINT_ON
	//OS_Printf( "length = %d\n", swk->length );
#endif

	//�������I�����Ă����狭���I��(06.04.12)
	if( Snd_PMVoicePlayCheck() == 0 ){
		swk->length = 0;
	}

	if( swk->length <= 0 ){

		//�������~������
		Snd_PMVoiceStop(0);

		//Snd_WaveOutStopReverse�̒��ŁA
		//�t�Đ��g�p�t���O�`�F�b�N�����Ă���̂ŁA
		//�����ł́A���o�[�X�`�F�b�N�͂��Ă��Ȃ��I(06.03.09)

		//�g�`�Đ��@�`�����l�����m�ۂ��Ă�����J��
		if( *ch_normal_flag == 1 ){
			Snd_WaveOutStopReverse( WAVEOUT_CH_NORMAL );	//buf�J��
			Snd_WaveOutFreeChannel( WAVEOUT_CH_NORMAL );	//ch �J��
		}
		if( *ch_chorus_flag == 1 ){
			Snd_WaveOutStopReverse( WAVEOUT_CH_CHORUS );	//buf�J��
			Snd_WaveOutFreeChannel( WAVEOUT_CH_CHORUS );	//ch �J��
		}

		//TCB�폜
		Snd_PMVoiceLengthTcbDel();
	}

	return;
}

//--------------------------------------------------------------
/**
 * @brief	�|�P���������Đ�����TCB�폜
 *
 * @param	none
 *
 * @retval	none
 */
//--------------------------------------------------------------
void Snd_PMVoiceLengthTcbDel()
{
	void* wk;
	TCB_PTR* length_tcb = Snd_GetParamAdrs(SND_W_ID_LENGTH_TCB);

	//�o�^����Ă�����TCB�폜
	if( *length_tcb != NULL ){
		wk = TCB_GetWork( *length_tcb );
		TCB_Delete( *length_tcb );
		sys_FreeMemoryEz( wk );
	}

	*length_tcb = NULL;
	return;
}

#if 0
//--------------------------------------------------------------
/**
 * @brief	�|�P�������������Z�b�g(TCB�ǉ�)
 *
 * @param	no		�V�[�P���X�i���o�[
 * @param	heap_id �q�[�vID
 *
 * @retval	none
 */
//--------------------------------------------------------------
void Snd_PMVoiceReleaseSet(int reverse, u32 ch, int frame, int heap_id)
{
	int ret;
	SND_PMVOICE_RELEASE_WORK* wk = NULL;

	//���łɓo�^����Ă�����TCB�폜
	ret = Snd_TCBDelSub( SND_TCB_PMVOICE_RELEASE );
	if( ret == TRUE ){
		OS_Printf( "\n�x���@�|�P��������\n" );
		OS_Printf( "��������TCB���I�����Ă��Ȃ��̂ɁA�ēx�Ă΂�Ă��܂��I\n" );
	}

	wk = sys_AllocMemory( heap_id, sizeof(SND_PMVOICE_RELEASE_WORK) );
	if( wk == NULL ){
		GF_ASSERT( (0) && "�������m�ێ��s�I" );
		return;
	}
	memset( wk, 0, sizeof(SND_PMVOICE_RELEASE_WORK) );

	if( reverse == 0 ){
		Snd_PlayerMoveVolume( SND_HANDLE_PMVOICE, 0, frame );
	}else{
		//���ӁI�����127�ɌŒ�ɂ��Ă���
		//���݂̃{�����[��/frame�̒l���t���[�����ƂɈ����Ă���
		//Snd_WaveOutSetVolume( ch, int vol );
	}

	wk->reverse	= reverse;
	wk->frame	= frame;
	wk->count	= 0;

	wk->sub		= 127/frame;
	if( wk->sub == 0 ){
		wk->sub = 1;
	}

	wk->tcb		= TCB_Add( Snd_PMVoiceReleaseMainTCB, wk, 0 );
	*release_tcb= wk->tcb;
	return;
}

//--------------------------------------------------------------
/**
 * @brief	TCB���C��
 *
 * @param	tcb		TCB_PTR
 * @param	wk		���[�N�̃A�h���X
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void Snd_PMVoiceReleaseMainTCB( TCB_PTR tcb, void* wk )
{
	u8* ch_normal_flag;
	u8* ch_chorus_flag;
	SND_PMVOICE_RELEASE_WORK *swk;

	swk = (SND_PMVOICE_RELEASE_WORK *)wk;
	ch_normal_flag = Snd_GetParamAdrs(SND_W_ID_WAVEOUT_CH_NORMAL_FLAG);
	ch_chorus_flag = Snd_GetParamAdrs(SND_W_ID_WAVEOUT_CH_CHORUS_FLAG);

	if( swk->reverse == 1 ){
		if( swk->count < 255 ){
			swk->count++;
		}

		if( (swk->sub*swk->count) >= 127 )
			Snd_WaveOutSetVolume( ch, 0 );
		}else{
			//���ӁI�����127�ɌŒ�ɂ��Ă���
			//���݂̃{�����[��/frame�̒l���t���[�����ƂɈ����Ă���
			Snd_WaveOutSetVolume( ch, 127-(swk->sub*swk->count) );
		}
	}
		
	swk->frame--;
	if( swk->frame <= 0 ){

		//�V�[�P���X
		Snd_PMVoiceStop(0);

		//�g�`�Đ��@�`�����l�����m�ۂ��Ă�����J��
		if( *ch_normal_flag == 1 ){
			Snd_WaveOutStopReverse( WAVEOUT_CH_NORMAL );
			Snd_WaveOutFreeChannel( WAVEOUT_CH_NORMAL );
		}
		if( *ch_chorus_flag == 1 ){
			Snd_WaveOutStopReverse( WAVEOUT_CH_CHORUS );
			Snd_WaveOutFreeChannel( WAVEOUT_CH_CHORUS );
		}

#if 0
		TCB_Delete( swk->tcb );
		sys_FreeMemoryEz( wk );
#else
		Snd_PMVoiceReleaseTcbDel();
#endif
	}

	return;
}
#endif



#if 0
	//----------------
	//���ƂŎ�������I
	//----------------
	
	//���W�����[�V�����f�v�X�e�X�g
	NNS_SndPlayerSetTrackModDepth( Snd_HandleGet(SND_HANDLE_PMVOICE), 0xffff, 30 );
	//NNS_SndPlayerSetTrackModDepth( Snd_HandleGet(SND_HANDLE_PMVOICE), 0xffff, 60 );
	//NNS_SndPlayerSetTrackModDepth( Snd_HandleGet(SND_HANDLE_PMVOICE), 0xffff, 80 );
	
	//���W�����[�V�����X�s�[�h�e�X�g(0-255)
	//speed�̃f�t�H���g��16�ŁA��6.4Hz�ɑ������܂��B�l���Q�{�ɂȂ�ƁA���g�����Q�{�ɂȂ�܂��B
	//NNS_SndPlayerSetTrackModSpeed( Snd_HandleGet(SND_HANDLE_PMVOICE), 0xffff, 80 );
#endif


//==============================================================================================
//
//	�R�[���X�֘A
//
//==============================================================================================

//--------------------------------------------------------------
/**
 * @brief	�R�[���X����(�V�[�P���X�Đ�)
 *
 * @param	none
 *
 * @retval	"�Đ�����=TRUE�A���s=FALSE"
 */
//--------------------------------------------------------------
static BOOL Snd_ChorusPlay( u16 no, s8 chorus )
{
	int ret;
	u8* chorus_flag = Snd_GetParamAdrs( SND_W_ID_CHORUS_FLAG );

	*chorus_flag = 1;	//�R�[���X�g�p�t���OON

	Snd_PerapVoiceDefaultFlagSet(TRUE);	//�؃��b�v�̃f�t�H���g�̖������Đ�����t���OON
	ret = Snd_PMVoicePlay( no );
	Snd_PlayerSetTrackPitch( SND_HANDLE_CHORUS, 0xffff, chorus );	//�s�b�`

	return ret; 
}

//--------------------------------------------------------------
/**
 * @brief	�R�[���X����(�g�`�t�Đ�)
 *
 * @param	no
 * @param	chorus
 * @param	vol
 * @param	pan
 * @param	heap_id	�q�[�vID
 *
 * @retval	"�Đ�����=TRUE�A���s=FALSE"
 */
//--------------------------------------------------------------
static BOOL Snd_ChorusPlayReverse( u16 no, s8 chorus, int vol, int pan, int heap_id )
{
	int ret;
	u8* chorus_flag = Snd_GetParamAdrs( SND_W_ID_CHORUS_FLAG );

	*chorus_flag = 1;	//�R�[���X�g�p�t���OON

	ret = Snd_WaveOutAllocChannel( WAVEOUT_CH_CHORUS );
	ret = Snd_WaveOutStartReverse( no, vol, pan, WAVEOUT_CH_CHORUS, heap_id );	//���ӁI(�R�[���X)

	return ret; 
}


//==============================================================================================
//
//	ME�֘A
//	BGM�̔g�`�̂݊J�����đ��v(����Ȃ��Ɨe�ʑ���Ȃ����m�F)
//
//	�g�p��1(ME�I����ABGM�ĊJ)
//	Snd_MePlay(bgm)
//	if( Snd_MePlayCheckBgmPlay(&wk) == FALSE ){
//
//==============================================================================================

//--------------------------------------------------------------
/**
 * @brief	BGM�|�[�Y �� ME�Đ�
 *
 * @param	no			ME�i���o�[
 *
 * @retval	"�Đ�����=TRUE�A���s=FALSE"
 *
 * �E�F�C�g���[�N��ME���ʃE�F�C�g�l���Z�b�g����܂�
 */
//--------------------------------------------------------------
BOOL Snd_MePlay( u16 no )
{
	u16 now_bgm_no;
	u8 player_no;
	int ret,i;
	const NNSSndArcBankInfo* info;									//�o���N���\����
	info = Snd_GetBankInfo( no );									//�o���N���\���̎擾

	Snd_MeWaitSet( no );											//ME���ʃE�F�C�g�l�Z�b�g

	//�|�[�Y����v���C���[�́A����BGM�i���o�[��炵�Ă���v���C���[�I
	now_bgm_no = Snd_NowBgmNoGet();									//����BGM�i���o�[�擾
	player_no = Snd_GetPlayerNo( now_bgm_no );

	//���݂̃V�[�P���X�i���o�[��0�łȂ�������
	if( player_no != 0xff ){
		Snd_PlayerPause( player_no, TRUE );							//BGM�|�[�Y
	}

	//�|�[�Y���́A�g�`�f�[�^�̂݊J�����Ă悢�I
	
	//ME�́A�ǉ��g�`�Ȃ�

	//�T�u��ʃf�[�^�����[�h���Ă��鎞������̂ŁAME�f�[�^�݂̂̒ǉ��폜������I
	Snd_HeapSaveState( Snd_GetParamAdrs(SND_W_ID_HEAP_SAVE_ME) );	//ME�ǉ��A�폜�p

	//�V�[�P���X�A�o���N�f�[�^�����[�h
	ret = Snd_ArcLoadSeqEx( no, (NNS_SND_ARC_LOAD_SEQ | NNS_SND_ARC_LOAD_BANK) );

#ifdef SOUND_OS_PRINT_ON
	OS_Printf( "ME�V�[�P���X�f�[�^���[�h = %d\n", ret );
#endif

	ret = NNS_SndArcPlayerStartSeq( Snd_HandleGet(SND_HANDLE_ME), no );
	Snd_VChatVolSet( no, SND_HANDLE_ME );							//�{�C�X�`���b�g���ʑ���

	return ret;
}

//--------------------------------------------------------------
/**
 * @brief	ME�I���҂�
 *
 * @param	none
 *
 * @retval	"�Đ���=TRUE�A�Đ��I��=FALSE"
 *
 * Snd_MePlay
 * Snd_MePlayCheck
 * �����܂ł��Ɖ�������������Ă��Ȃ��I
 * Snd_MeStop���K�v�I
 *
 * �������́A
 * Snd_MePlay
 * Snd_MePlayCheckBgmPlay
 * �Ŏg���I
 */
//--------------------------------------------------------------
int Snd_MePlayCheck(void)
{
	u16* me_wait = Snd_GetParamAdrs(SND_W_ID_ME_WAIT);

	if( Snd_PlayerCountPlayingSeq(PLAYER_ME) != 0 ){
		return TRUE;
	}

	if( *me_wait > 0 ){													//�E�F�C�g�`�F�b�N
		(*me_wait)--;
		return TRUE;													//�E�F�C�g��
	}

	return FALSE;
}

//--------------------------------------------------------------
/**
 * @brief	ME��~
 *
 * @param	frame	�w�肵���t���[���������ď��X�ɉ��ʂ𗎂Ƃ��Ă���
 *
 * @retval	none
 *
 * �T�E���h�n���h���������̏ꍇ�́A�������܂���B 
 */
//--------------------------------------------------------------
static void Snd_MeStop( int frame )
{
	int no,type;
	u16 i;

	NNS_SndPlayerStopSeq( Snd_HandleGet(SND_HANDLE_ME), frame );	//ME��~

	//�T�u��ʃf�[�^�����[�h���Ă��鎞������̂ŁAME�f�[�^�݂̂̒ǉ��폜������I
	Snd_HeapLoadState( Snd_GetHeapSaveLv(SND_HEAP_SAVE_ME) );		//ME�ǉ��A�폜�p
	
	return;
}

//--------------------------------------------------------------
/**
 * @brief	ME�I���҂� �� �I����A�E�F�C�g�����Ă���BGM�𕜋A������
 *
 * @param	none
 *
 * @retval	"ME�Đ���=TRUE�A�E�F�C�g��=TRUE�ABGM�ĊJ=FALSE"
 */
//--------------------------------------------------------------
int Snd_MePlayCheckBgmPlay(void)
{
	u8 player_no;
	u16 now_bgm_no;
	u16* me_wait = Snd_GetParamAdrs(SND_W_ID_ME_WAIT);

	//ME�I���҂�
	if( Snd_MePlayCheck() == TRUE ){
		return TRUE;
	}

	Snd_MeStop( 0 );												//ME��~

	now_bgm_no = Snd_NowBgmNoGet();									//����BGM�i���o�[�擾
	player_no = Snd_GetPlayerNo( now_bgm_no );

	//���݂̃V�[�P���X�i���o�[��0�łȂ�������
	if( player_no != 0xff ){
		Snd_PlayerPause( player_no, FALSE );						//BGM�ĊJ
	}

	return FALSE;
}

//--------------------------------------------------------------
/**
 * @brief	ME���ʃE�F�C�g�l�Z�b�g
 *
 * @param	no			ME�i���o�[
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void Snd_MeWaitSet( u16 no )
{
	u16* me_wait = Snd_GetParamAdrs(SND_W_ID_ME_WAIT);

#if 0
	//ME���Ƃ̋��ʃE�F�C�g������������
	switch( no ){
	case SEQ_FANFA1:
		break;
	case SEQ_FANFA4:
		break;
	}
#endif

	(*me_wait) = SND_ME_COMMON_WAIT;
	return;						
}


//==============================================================================================
//
//	�f�o�b�N�֐�
//
//==============================================================================================
#ifdef PM_DEBUG
//--------------------------------------------------------------
/**
 * @brief	�f�o�b�N�֐��FBGM�t���O�̃Z�b�g
 *
 * @param	sw		0=�ʏ�A1=BGM�I�t
 *
 * @retval	none
 */
//--------------------------------------------------------------
void Snd_DebugBgmFlagSet( u8 sw )
{
	debug_bgm_flag = sw;
	return;
}

//--------------------------------------------------------------
/**
 * @brief	�f�o�b�N�֐��FBGM�t���O�̎擾
 *
 * @param	none
 *
 * @retval	"0=�ʏ�A1=BGM�I�t"
 */
//--------------------------------------------------------------
static BOOL Snd_DebugBgmFlagCheck( void )
{
	return debug_bgm_flag;
}
#endif


