//==============================================================================================
/**
 * @file	snd_perap.c
 * @brief	�T�E���h �y���b�v�֐�
 * @author	Satoshi Nohara
 * @date	2006.04.15
 */
//==============================================================================================
#include "common.h"
#include "snd_system.h"
#include "system/snd_tool.h"
#include "savedata/savedata.h"				//
#include "savedata/perapvoice.h"			//
#include "poketool/monsno.h"


//==============================================================================================
//
//	�v���g�^�C�v�錾
//
//==============================================================================================
BOOL Snd_MainPerapCheck( void );

BOOL Snd_PerapVoiceCheck( const PERAPVOICE* perap );
BOOL Snd_PerapVoicePlayingCheck( const PERAPVOICE* perap );

BOOL Snd_PerapVoicePlaySub( const PERAPVOICE* perap, u32 sex, int vol, int pan );
void Snd_PerapVoiceStop( void );

MICResult Snd_PerapVoiceRecStart( void );
MICResult Snd_PerapVoiceRecStop( void );

void Snd_PerapVoiceDataSave( PERAPVOICE* perap );

void Snd_PerapVoiceDefaultFlagSet( u8 no );

BOOL Snd_PerapVoicePlay( PERAPVOICE* perap, u32 sex, int vol, int pan );

int Snd_PerapVoiceWazaParamGet( PERAPVOICE* perap );
BOOL Snd_PerapVoicePMVoiceTypeCheck( int type );


//==============================================================================================
//
//	��`
//
//==============================================================================================
#define PERAP_SAMPLING_RATE		(2000)									//�T���v�����O���[�g
#define PERAP_SAMPLING_TIME		(1)										//�T���v�����O���鎞��
#define PERAP_SAMPLING_SIZE		(PERAP_SAMPLING_RATE * PERAP_SAMPLING_TIME)	//�K�v�ȃf�[�^��

#define PERAP_MALE_WAVEOUT_SPD		(WAVEOUT_PLAY_SPDx1 - 4096)			//�I�X�̍Đ��X�s�[�h
#define PERAP_FEMALE_WAVEOUT_SPD	(WAVEOUT_PLAY_SPDx1 + 9192)			//���X�̍Đ��X�s�[�h
#define PERAP_WAVEOUT_SPD_RAND	(8192)									//�Đ��X�s�[�h�̃����_��


//==============================================================================================
//
//	
//
//==============================================================================================

//--------------------------------------------------------------
/**
 * @brief	�T�E���h���C������Ă΂��
 *			�؃��b�v�̘^�������f�[�^�̍Đ��I�����Ď����ă`�����l���J��������
 *
 * @param	none
 *
 * @retval	"��������=TRUE�A�������Ȃ�=FALSE"
 */
//--------------------------------------------------------------
BOOL Snd_MainPerapCheck( void )
{
	u8* perap_play_flag	= Snd_GetParamAdrs(SND_W_ID_PERAP_PLAY_FLAG);

	//�y���b�v�̘^�������������Đ����Ă��邩�t���O
	if( *perap_play_flag == 1 ){

		//�g�`�Đ����I�����Ă�����
		if( Snd_WaveOutIsPlaying(WAVEOUT_CH_NORMAL) == FALSE ){

			Snd_PerapVoiceStop();	//��~

			return TRUE;
		}
	}

	return FALSE;
}

//--------------------------------------------------------------
/**
 * @brief	�y���b�v�̘^�������f�[�^���Đ��\���`�F�b�N
 *
 * @param	no		�|�P�����i���o�[
 *
 * @retval	"�Đ��\=TRUE�A�Đ��s��=FALSE"
 */
//--------------------------------------------------------------
BOOL Snd_PerapVoiceCheck( const PERAPVOICE* perap )
{
	u8* perap_default_flag	= Snd_GetParamAdrs(SND_W_ID_PERAP_DEFAULT_FLAG);

	//���f�[�^�����݂��邩�ǂ����̃`�F�b�N
	if( PERAPVOICE_GetExistFlag(perap) == FALSE ){
		return FALSE;
	}

	//�f�t�H���g�̖������Đ�����t���O�̃`�F�b�N
	if( *perap_default_flag == TRUE ){
		return FALSE;
	}

	return TRUE;
}

//--------------------------------------------------------------
/**
 * @brief	�y���b�v�̘^�������f�[�^���Đ����Ă��邩�`�F�b�N
 *
 * @param	no		�|�P�����i���o�[
 *
 * @retval	"�Đ���=TRUE�A�Đ����Ă��Ȃ�=FALSE"
 */
//--------------------------------------------------------------
BOOL Snd_PerapVoicePlayingCheck( const PERAPVOICE* perap )
{
	u8* perap_play_flag		= Snd_GetParamAdrs( SND_W_ID_PERAP_PLAY_FLAG );

	if( *perap_play_flag == 0 ){
		return FALSE;
	}

	return TRUE;
}

//--------------------------------------------------------------
/**
 * @brief	�y���b�v�̘^�������f�[�^���Đ�
 *
 * @param	perap	PERAPVOICE�^�̃|�C���^
 * @param	sex		����
 * @param	vol		�{�����[��
 * @param	pan		�p��
 *
 * @retval	"�Đ�����=TRUE�A���s=FALSE"
 */
//--------------------------------------------------------------
BOOL Snd_PerapVoicePlaySub( const PERAPVOICE* perap, u32 sex, int vol, int pan )
{
	u16 add_spd;
	int ret,wave_pan;
	s8* sWaveBuffer			= Snd_GetWaveBufAdrs();
	u8* perap_play_flag		= Snd_GetParamAdrs( SND_W_ID_PERAP_PLAY_FLAG );

	//�y���b�v�̘^�������f�[�^���Đ��s�\���`�F�b�N
	if( Snd_PerapVoiceCheck(perap) == FALSE ){
		return FALSE;
	}

	//�V�[�P���X�Đ��̃p����(-127 - 0 - 127)�ƂȂ��Ă���
	//�g�`�Đ��̃p����(0 - 64 - 127)�ƂȂ��Ă���
	
	//�g�`�Đ��p�����擾
	if( pan < 0 ){
		wave_pan = 64 + (pan / 2);		//0 - 64  �ɂ���
	}else{
		wave_pan = 64 + (pan / 2);		//64 - 127 �ɂ���
	}

	Snd_PMVoiceStop(0);		//������~

	//�Đ��I���O�ɁA
	//�ēx���̊֐����Ă΂�邱�Ƃ�����̂ŁA
	//��x��~���Ă���A�Đ��֐i�ނ悤�ɂ���
	Snd_PerapVoiceStop();

	//�g�`�Đ��p�`�����l�����m�ۂ���
	Snd_WaveOutAllocChannel( WAVEOUT_CH_NORMAL );

	//�����_���ɉ�����ς���
	//gf_srand( sys.vsync_counter );
	add_spd = ( gf_rand() % PERAP_WAVEOUT_SPD_RAND );

	//���f�[�^�̓W�J
	PERAPVOICE_ExpandVoiceData( sWaveBuffer, PERAPVOICE_GetVoiceData(perap) );

	{
		WAVEOUT_WORK waveout_wk;
		waveout_wk.handle			= Snd_WaveOutHandleGet(WAVEOUT_CH_NORMAL);	//�g�`�Đ��n���h��
		waveout_wk.format			= NNS_SND_WAVE_FORMAT_PCM8;		//�g�`�f�[�^�t�H�[�}�b�g

		waveout_wk.dataaddr			= Snd_GetWaveBufAdrs();			//�g�`�f�[�^�̐擪�A�h���X

		waveout_wk.loopFlag			= FALSE;						//���[�v�t���O
		waveout_wk.loopStartSample	= 0;							//���[�v�J�n�T���v���ʒu
		waveout_wk.samples			= PERAP_SAMPLING_SIZE;			//�g�`�f�[�^�̃T���v����
		waveout_wk.sampleRate		= PERAP_SAMPLING_RATE;			//�g�`�f�[�^�̃T���v�����O���[�g
		waveout_wk.volume			= vol;							//����
		waveout_wk.speed			= (WAVEOUT_PLAY_SPDx1+add_spd);	//�Đ��X�s�[�h
		waveout_wk.pan				= wave_pan;						//�p��(0-127)
		ret = Snd_WaveOutStart( &waveout_wk, WAVEOUT_CH_NORMAL );

		//�{�C�X�`���b�g�̉��ʑΉ�
		Snd_WaveOutSetVolume( WAVEOUT_CH_NORMAL, vol );
	}

#if 0
	//������ς���
	if( ret == TRUE ){
		if( sex == PM_MALE ){
			Snd_WaveOutSetSpeed( WAVEOUT_CH_NORMAL, PERAP_MALE_WAVEOUT_SPD );	//�I�X
		}else{
			Snd_WaveOutSetSpeed( WAVEOUT_CH_NORMAL, PERAP_FEMALE_WAVEOUT_SPD );	//���X
		}
	}
#endif

	*perap_play_flag = 1;					//�؃��b�v�̘^�������������Đ����Ă���t���OON
	Snd_PerapVoiceDefaultFlagSet( FALSE );	//�؃��b�v�̃f�t�H���g�̖������Đ�����t���OOFF

	return ret;
}

//--------------------------------------------------------------
/**
 * @brief	�y���b�v�̘^�������f�[�^���~
 *
 * @param	none
 *
 * @retval	none
 */
//--------------------------------------------------------------
void Snd_PerapVoiceStop( void )
{
	u8* ch_normal_flag	= Snd_GetParamAdrs(SND_W_ID_WAVEOUT_CH_NORMAL_FLAG);
	u8* perap_play_flag	= Snd_GetParamAdrs(SND_W_ID_PERAP_PLAY_FLAG);

	if( *ch_normal_flag == 1 ){										//CH�m�ۂ��Ă�����
		Snd_WaveOutStopReverse( WAVEOUT_CH_NORMAL );				//buf�J��
		Snd_WaveOutFreeChannel( WAVEOUT_CH_NORMAL );				//ch �J��
	}

	*perap_play_flag = 0;											//�t���O�N���A
	return;
}

//--------------------------------------------------------------
/**
 * @brief	�y���b�v�f�[�^�^���J�n(�T�E���h�V�X�e���̗̈�Ɉꎞ�ۑ�����)
 *
 * @param	none
 *
 * @retval	"MIC_RESULT_SUCCESS		����������Ɋ���"
 * @retval	"����ȊO				���炩�̌����Ŏ��s"
 */
//--------------------------------------------------------------
MICResult Snd_PerapVoiceRecStart( void )
{
	MICAutoParam mic;	//�}�C�N�p�����[�^

	//�g�`�Đ��p�`�����l�����m�ۂ���
	//Snd_WaveOutAllocChannel( WAVEOUT_CH_NORMAL );

	mic.type			= MIC_SAMPLING_TYPE_SIGNED_8BIT;	//�T���v�����O���

	//�o�b�t�@��32�o�C�g�A���C�����ꂽ�A�h���X�łȂ��ƃ_���I
	mic.buffer			= Snd_GetWaveBufAdrs();

	mic.size			= PERAP_SAMPLING_SIZE;

	if( (mic.size&0x1f) != 0 ){
		mic.size &= 0xffffffe0;
	}

	//��\�I�ȃT���v�����O���[�g��ARM7�̃^�C�}�[�����Ɋ��Z�����l�̒�`
	//mic.rate			= MIC_SAMPLING_RATE_8K;
	mic.rate			= HW_CPU_CLOCK_ARM7 / PERAP_SAMPLING_RATE;

	//�A���T���v�����O���Ƀo�b�t�@�����[�v������t���O
	mic.loop_enable		= FALSE;

	//�o�b�t�@���O�a�����ۂɌĂяo���R�[���o�b�N�֐��ւ̃|�C���^
	mic.full_callback	= NULL;

	//�o�b�t�@���O�a�����ۂɌĂяo���R�[���o�b�N�֐��֓n������
	mic.full_arg		= NULL;

	return Snd_MicStartAutoSampling( &mic );		//�^���J�n
}

//--------------------------------------------------------------
/**
 * @brief	�y���b�v�f�[�^�^����~
 *
 * @param	none
 *
 * @retval	"MIC_RESULT_SUCCESS		����������Ɋ���"
 * @retval	"����ȊO				���炩�̌����Ŏ��s"
 */
//--------------------------------------------------------------
MICResult Snd_PerapVoiceRecStop( void )
{
	return Snd_MicStopAutoSampling();
}

//--------------------------------------------------------------
/**
 * @brief	�^�������f�[�^���Z�[�u�f�[�^�ɃZ�b�g
 *
 * @param	none
 *
 * @retval	none
 */
//--------------------------------------------------------------
void Snd_PerapVoiceDataSave( PERAPVOICE* perap )
{
	PERAPVOICE_SetVoiceData( perap, (const s8*)Snd_GetWaveBufAdrs() );
	return;
}


/***********/
//��~�A�Đ������`�F�b�N���Ή����Ă��邩�m�F�I
/***********/


//==============================================================================================
//
//	�T�E���h�V�X�e�����ŁA
//
//	���؃��b�v�i���o�[���`�F�b�N
//	���f�t�H���g�̖�����炷�t���O���`�F�b�N
//
//	�^�������f�[�^���Đ����邩�ɑΉ������֘A
//
//==============================================================================================

//--------------------------------------------------------------
/**
 * @brief	�؃��b�v�̃f�t�H���g�̖������Đ�����t���O����
 *
 * @param	no		�t���O����
 *
 * @retval	none
 */
//--------------------------------------------------------------
void Snd_PerapVoiceDefaultFlagSet( u8 no )
{
	u8* perap_default_flag	= Snd_GetParamAdrs(SND_W_ID_PERAP_DEFAULT_FLAG);
	*perap_default_flag		= no;
	return;
}


//==============================================================================================
//
//	�ʐM�m�ۂ����؃��b�v�f�[�^�̃|�C���^���󂯎��A�Đ�����֘A
//
//==============================================================================================

//--------------------------------------------------------------
/**
 * @brief	�y���b�v�̘^�������f�[�^���Đ�
 *
 * @param	perap	�y���b�v�f�[�^�̃|�C���^
 * @param	sex		����(PM_MALE�Ȃ�)
 * @param	vol		�{�����[��(0 �` 127)
 * @param	pan		�p��(-128 �` 127)
 *
 * @retval	"�Đ�����=TRUE�A���s=FALSE"
 */
//--------------------------------------------------------------
BOOL Snd_PerapVoicePlay( PERAPVOICE* perap, u32 sex, int vol, int pan )
{
	int ret;
	PERAPVOICE** my_p = Snd_GetParamAdrs( SND_W_ID_MY_PERAP_PTR );

	//�y���b�v�̘^�������f�[�^�Đ�
	if( perap == NULL ){
		ret = Snd_PerapVoicePlaySub( *my_p, sex, vol, pan );		//�G���[���
	}else{
		ret = Snd_PerapVoicePlaySub( perap, sex, vol, pan );
	}

	//�؃��b�v�̘^�������f�[�^�Đ��o���Ȃ�������
	if( ret == FALSE ){
		Snd_PerapVoiceDefaultFlagSet( TRUE );			//�f�t�H���g���Đ�����

		//�q�[�vID���w�肵�Ă��邪�������m�ۂ͂��Ă��Ȃ��I(PV_NORMAL�Œ�Ȃ̂�)
		ret = Snd_PMVoicePlayEx( PV_NORMAL, MONSNO_PERAPPU, pan, vol, HEAPID_WORLD );
	}

	//Snd_PMVoicePlayEx�̒��ŁASnd_PerapVoicePlaySub���Ă΂�邪�A
	//����ɓn�����̂́A�����̂؃��b�v�f�[�^�Ȃ̂ŁA�ЂƂ܂Ƃ߂ɂ��Ă͂��߁I
	//default_flag�������Ă���̂ŁA�����؃��b�v�̍Đ��ɂ͂������A
	//�f�t�H���g�̖������Ȃ�悤�ɂȂ�I
	
	return ret;
}


//==============================================================================================
//
//	�Z�u������ׂ�v
//
//==============================================================================================

//--------------------------------------------------------------
/**
 * @brief	�Z�̃p�����[�^���擾
 *
 * @param	perap		�؃��b�v�f�[�^�̃|�C���^
 *
 * @retval	"�p�����[�^ 0�`2"
 */
//--------------------------------------------------------------
int Snd_PerapVoiceWazaParamGet( PERAPVOICE* perap )
{
	const s8* voicedata;
	s8 num;

	//���f�[�^�����݂��邩�ǂ����̃`�F�b�N
	if( PERAPVOICE_GetExistFlag(perap) == FALSE ){
		return 0;
	}

	//�v�f��[15]�����ăp�����[�^�����肷��
	voicedata = PERAPVOICE_GetVoiceData(perap);
	num = voicedata[15];
	//OS_Printf( "voicedata[15] = %d\n", voicedata[15] );
	//OS_Printf( "num = %d\n", num );

	if( (-128 <= num) && (num < -30) ){
		return 1;
	}

	if( (30 <= num) && (num < 128) ){
		return 2;
	}

	return 0;
}


//--------------------------------------------------------------
/**
 * @brief	�^���f�[�^�A�f�t�H���g�f�[�^�ǂ�����Đ����邩�`�F�b�N
 *
 * @param	type		�Đ��p�^�[��
 *
 * @retval	"TRUE=�^�������f�[�^���Đ�����AFALSE=�f�t�H���g�̖������Đ�����"
 */
//--------------------------------------------------------------
BOOL Snd_PerapVoicePMVoiceTypeCheck( int type )
{
	switch( type ){
	case PV_NORMAL:				//�ʏ�Đ�
	case PV_HALF:				//�Đ����ԒZ�k�i�Q�����Q�o�g���Ń|�P�����o�ꎞ�j
	//case PV_FLDEVENT:			//�{�����|�P�����i�t�B�[���h�C�x���g�j
	//case PV_W_TOOBOE:			//�Z���ʉ��E�Ƃ��ڂ��p
	//case PV_W_HYPER1:			//�Z���ʉ��E�n�C�p�[�{�C�X�p�P
	case PV_POKEDOWN:			//�|�P���������ꂽ��
	//case PV_W_HYPER2:			//�Z���ʉ��E�n�C�p�[�{�C�X�p�Q
	//case PV_W_HOERU1:			//�Z���ʉ��E�ق���P
	//case PV_W_HOERU2:			//�Z���ʉ��E�ق���Q
	//case PV_W_NAKIGOE1:		//�Z���ʉ��E�Ȃ������P
	//case PV_W_NAKIGOE2:		//�Z���ʉ��E�Ȃ������Q
	case PV_PINCHNORMAL:		//�ʏ�Đ�(���C�Ȃ�)
	case PV_PINCHHALF:			//�Đ����ԒZ�k�i�Q�����Q�o�g���Ń|�P�����o�ꎞ�j(���C�Ȃ�)
	//case PV_ZUKAN_CHORUS:		//�}�ӃR�[���X�Đ�(�ǉ�06.03.03)
	//case PV_ZUKAN_NORMAL:		//�}�Ӄm�[�}���Đ�(�ǉ�06.04.21)
		return TRUE;
	};

	return FALSE;
}

