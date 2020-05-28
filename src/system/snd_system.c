//==============================================================================================
/**
 * @file	snd_system.c
 * @brief	�T�E���h�V�X�e��
 * @author	Satoshi Nohara
 * @date	2005.11.08
 *
 * ��snd_tool,snd_play,(main)����̂݃A�N�Z�X�����
 * snd_system
 *     |
 *     |
 * ���f�[�^�Z�b�g�Ȃǂ̏������܂Ƃ߂�	���Đ��A��~�Ȃǂ̏������܂Ƃ߂�
 * snd_tool								snd_play
 *     |
 *     |
 * ���e��f������Ă΂��(��Ƀt�B�[���h�C�x���g)
 * fld_bgm
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

#include "savedata/savedata.h"
#include "savedata/perapvoice.h"
#include "savedata/config.h"


//==============================================================================================
//
//	��`
//
//==============================================================================================
//sound_data.smap�̃T�C�Y��菭���傫�߂Ɋm�ۂ���
#define SOUND_HEAP_SIZE		(0xbbc00)				//�T�E���h�q�[�v�T�C�Y(��750k)
//#define SOUND_HEAP_SIZE	(0xbd000)				//�T�E���h�q�[�v�T�C�Y(��750k)
//#define SOUND_HEAP_SIZE	(0xc0000)				//�T�E���h�q�[�v�T�C�Y(��750k)
//#define SOUND_HEAP_SIZE	(0x80000)				//�T�E���h�q�[�v�T�C�Y(��500k)


//==============================================================================================
//
//	�\���̐錾
//
//==============================================================================================
//�T�E���h�V�X�e�����[�N
struct _SND_WORK{

	//�V�X�e���֘A
	NNSSndArc arc;									//�T�E���h�A�[�J�C�u
	NNSSndHeapHandle heap;							//�T�E���h�q�[�v�n���h��
	u8 sndHeap[ SOUND_HEAP_SIZE ];					//�T�E���h�q�[�v
	NNSSndHandle Handle[ SND_HANDLE_MAX ];			//�T�E���h�n���h��
	NNSSndWaveOutHandle sWaveOutHandle[2];			//�g�`�n���h��
	const NNSSndArcBankInfo* info;					//�o���N���\����

	//�L���v�`���֘A
	u8 sCaptureBuffer[ CAPTURE_BUFSIZE ] ATTRIBUTE_ALIGN(32);	//�L���v�`���o�b�t�@
	EffectCallbackInfo callbackInfo;				//�G�t�F�N�g�̃R�[���o�b�N�ϐ�

#ifdef STREAM_ON
	//�X�g���[���֘A
	NNSSndStrmHandle strmHandle;
#endif
	
	u16 seq;										//�V�[�P���X
	u8	ctrl_bgm_flag;								//�t�B�[���hBGM�Œ�t���O(�Z�[�u����Ȃ�)
	u8	dmy101;

	int fade_count;									//�t�F�[�h�J�E���^�[
	int next_wait;									//����BGM��炷�܂ł̃E�F�C�g
	int next_frame;									//����BGM�̃t�F�[�h�C���t���[��

	u16 now_bgm_no;									//����BGM�i���o�[
	u16 next_bgm_no;								//����BGM�i���o�[

	u8	field_pause_flag;							//PLAYER_FIELD���|�[�Y���Ă��邩�t���O
	u8	bgm_pause_flag;								//PLAYER_BGM���|�[�Y���Ă��邩�t���O
	u16 me_wait;									//ME�E�F�C�g

	u8  reverse_flag;								//�t�Đ��g�p�t���O
	u8  waveout_ch_normal_flag;						//�g�`�Ŏg�p����CH���m�ۂ������t���O
	u8  waveout_ch_chorus_flag;						//�g�`�Ŏg�p����CH���m�ۂ������t���O(CHORUS)
	u8  chorus_flag;								//�R�[���X�g�p�t���O

	u8  bank_flag;									//�����邩�t���O
	//u8	wavearc_count;							//�ǂݍ��񂾔g�`�A�[�J�C�u��
	u8	filter_size;								//�t�B���^�[�T�C�Y
	u8	scene_main;									//���݂̃��C���V�[��
	u8  scene_sub;									//���݂̃T�u�V�[��

	int heap_save[SND_HEAP_SAVE_MAX];				//�T�E���h�q�[�v�K�w���x��

	u8	perap_play_flag;							//�y���b�v�̘^�������������Đ����Ă��邩�t���O
	u8	perap_default_flag;							//�y���b�v�̃f�t�H���g�̖������Đ�����t���O
	u16	zone_bgm;									//�]�[��BGM�i���o�[

	const SNDWaveData* wave_data;					//�g�`�f�[�^�̃|�C���^

	void* reverse_buf;								//�t�Đ��p�̃o�b�t�@�̃|�C���^

	int volume;										//BGM�{�����[��

	TCB_PTR length_tcb;								//�����Đ�����TCB

	PERAPVOICE*	my_perap_ptr;						//�����̂؃��b�v�{�C�X�̃|�C���^
	PERAPVOICE*	perap_ptr[4];						//�؃��b�v�{�C�X�̃|�C���^
};


//==============================================================================================
//
//	��`
//
//==============================================================================================


//==============================================================================================
//
//	�ϐ�
//
//==============================================================================================
static SND_WORK snd_work;							//�T�E���h�V�X�e�����[�N
static int snd_status;								//�T�E���h�X�e�[�^�X

//�g�p���Ȃ������B�B
static NNSSndCaptureOutputEffectType stereo_mono;	//�X�e���I�����m������

//�f�o�b�N�p
u32 aki_size;										//�T�E���h�q�[�v�T�C�Y�m�F


//==============================================================================================
//
//	�v���g�^�C�v�錾
//
//==============================================================================================
void Snd_AllInit( PERAPVOICE* perap, CONFIG* config );
void Snd_Main(void);
static void Snd_StatusCall(void);
void Snd_StatusSet( int status );
BOOL Snd_StatusCheck( int chg_status );
static BOOL Snd_MeUseCheck(void);

SND_WORK* Snd_GetSystemAdrs();
void* Snd_GetParamAdrs( int type );

int Snd_HeapSaveState(int* heap_lv);
void Snd_HeapLoadState( int level );
void Snd_UseHeapSizeOsPrint(void);
NNSSndHeapHandle* Snd_HeapHandleGet(void);

BOOL Snd_ArcLoadGroup( u16 no );
BOOL Snd_ArcLoadSeq( u16 no );
BOOL Snd_ArcLoadSeqEx( u16 no, u32 flag );
BOOL Snd_ArcLoadSeqArc( u16 no );
BOOL Snd_ArcLoadWaveArc( u16 no );
BOOL Snd_ArcLoadBank( u16 no );

NNSSndHandle * Snd_HandleGet( int type );
int Snd_GetHandleNoByPlayerNo( int player_no );

void Snd_PlayerPauseAll( BOOL flag );

//���[�J���֐�
static void Snd_WorkInit( SND_WORK* wk );
static void Snd_HandleInit( SND_WORK* wk );
static void Snd_GameStartLoad( SND_WORK* wk );
static void Snd_MicInit(void);

//PLAYER_BGM�̒�~�A�n���h�������[�X
static void Snd_PlayerBgmStop( void );


//==============================================================================================
//
//	�v���O����
//
//==============================================================================================

//--------------------------------------------------------------
/**
 * @brief	�T�E���h������
 *
 * @param	none
 *
 * @retval	none
 *
 * ���̑S�ẴT�E���h�֐�����ɌĂт����Ă��������B
 * �������A���炩���߁AOS�����������Ă����K�v������܂��B 
 *
 * IRQ���荞�݂͗L���ɂ��Ă��������B�܂��A���̊֐��̌�ŁA
 * OS_SetIrqMask�֐� �ȂǂŊ��荞�݂̐ݒ���㏑�����Ȃ��悤�ɂ��Ă��������B 
 */
//--------------------------------------------------------------
void Snd_AllInit( PERAPVOICE* perap, CONFIG* config )
{
	SND_WORK* wk = Snd_GetSystemAdrs();

	//Snd_LocalWorkCreate();				//�T�E���h���[�J�����[�N�m��
	
    NNS_SndInit();							//�T�E���h���C�u�����̏�����

	Snd_MicInit();							//MIC������

	Snd_WorkInit(wk);						//�T�E���h�V�X�e�����[�N������

	//�T�E���h�q�[�v�̍쐬
    wk->heap = NNS_SndHeapCreate( &wk->sndHeap, sizeof(wk->sndHeap) );

	//�T�E���h�A�[�J�C�u�̏�����
    NNS_SndArcInit( &wk->arc, "data/sound/sound_data.sdat", wk->heap, FALSE );

	//�v���C���[�̃Z�b�g�A�b�v
	//�T�E���h�A�[�J�C�u���Œ�`����Ă���v���C���[�ݒ�Ɋ�Â��Z�b�g�A�b�v�����
    (void)NNS_SndArcPlayerSetup( wk->heap );

#ifdef STREAM_ON
	NNS_SndArcStrmInit( STREAM_THREAD_PRIO, wk->heap );

    NNS_SndStrmHandleInit( &wk->strmHandle );
#endif

    //�T�E���h�n���h��������
    Snd_HandleInit(wk);

#ifdef SOUND_OS_PRINT_ON
	//aki_size = NNS_SndHeapGetFreeSize( wk->heap );
	aki_size = NNS_SndHeapGetSize( wk->heap );
	OS_Printf( "\n\n//========================================\n" );
	OS_Printf( "//\t�T�E���h\n" );
	OS_Printf( "//========================================\n" );
	OS_Printf( "�����e�ʁ��T�E���h�q�[�v = %d\n", aki_size );

	OS_Printf( "\n���v���C���[�q�[�v���蓖�ĕ�\n" );
	Snd_UseHeapSizeOsPrint();							//�ǉ������T�E���h�q�[�v�̗e�ʂ��o�͂���

	OS_Printf( "���Q�[���J�n���̃T�E���h�f�[�^���[�h��\n" );
#endif

	Snd_GameStartLoad(wk);								//�Q�[���J�n���̃T�E���h�f�[�^�̃��[�h

	//�o�̓G�t�F�N�g�ݒ�
	stereo_mono = NNS_SND_CAPTURE_OUTPUT_EFFECT_NORMAL;	//�ʏ�̃X�e���I���[�h
	//Snd_CaptureStartOutputEffect( stereo_mono );
	
	//�����̂؃��b�v�̃|�C���^����ɂ����Ă���(06.04.20)
	wk->my_perap_ptr = perap;

	//�R���t�B�O�ݒ�ɕύX
	Snd_SetMonoFlag( config->sound_mode );

	return;
}

//--------------------------------------------------------------
/**
 * @brief	�T�E���h�t���[�����[�N
 *
 * @param	none
 *
 * @retval	none
 *
 * 1�t���[����1�x�Ăяo����������΁A�ǂ��ŃR�[�����Ă��\��Ȃ�
 */
//--------------------------------------------------------------
void Snd_Main(void)
{
	SND_WORK* wk = Snd_GetSystemAdrs();

	//ME�g�p���̎��́ABGM�X�e�[�^�X�����͂��Ȃ��I
	if( Snd_MeUseCheck() == FALSE ){

		//�t�F�[�h�J�E���g�f�N�������g
		if( wk->fade_count > 0 ){
			wk->fade_count--;
		}
	
		//�T�E���h�X�e�[�^�X�Ăяo��
		Snd_StatusCall();
	}

	//�؃��b�v�̘^�������������Đ����Ă��邩�t���O�������Ă�����A
	//�g�`�Đ����I�����Ă��邩�`�F�b�N���āA�g�`�Đ��`�����l�����J������
	Snd_MainPerapCheck();

	NNS_SndMain();
	return;
}

//--------------------------------------------------------------
/**
 * @brief	�T�E���h�X�e�[�^�X�Ăяo��
 *
 * @param	status		�X�e�[�^�X(snd_system.h�Q��)
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void Snd_StatusCall(void)
{
	int ret;
	SND_WORK* wk = Snd_GetSystemAdrs();

	switch( snd_status ){

	//������
	//case SND_STATUS_INIT:
	//	break;

	//��~
	case SND_STATUS_STOP:
		//�������Ȃ�
		break;

	//
	//case SND_STATUS_PLAYSTART:
	//	break;

	//�Đ�
	case SND_STATUS_PLAY:
		Snd_StatusSet( SND_STATUS_PLAING );					//�X�e�[�^�X(�Đ���)
		break;

	//�Đ���
	case SND_STATUS_PLAING:
		//�������Ȃ�
		break;

	//�t�F�[�h�C��
	case SND_STATUS_FADEIN:
		if( Snd_FadeCheck() == 0 ){							//�t�F�[�h�I�����Ă�����
			Snd_StatusSet( SND_STATUS_PLAING );				//�X�e�[�^�X(�Đ���)
		}
		break;

	//�t�F�[�h�A�E�g
	case SND_STATUS_FADEOUT:
		//�����ɂ��鎞�ƁA���ʏ��������鎞������I
		if( Snd_FadeCheck() == 0 ){							//�t�F�[�h�I�����Ă�����
			Snd_StatusSet( SND_STATUS_PLAING );				//�X�e�[�^�X(�Đ���)
		}
		break;

	//
	//case SND_STATUS_FADENEXT:
	//	break;

	//
	//case SND_STATUS_FADENEXTFADE:
	//	break;

	//�t�F�[�h�A�E�g �� BGM�Đ�
	case SND_STATUS_FADEOUT_NEXT_PLAY:
		if( Snd_FadeCheck() == 0 ){							//�t�F�[�h�I���҂�
			if( Snd_NextWaitCheck() == 0 ){					//����BGM��炷�܂ł̃E�F�C�g�`�F�b�N

				//PLAYER_BGM��炵�Ȃ���}�b�v�J�ڂ������̑Ή�
				//PLAYER_BGM���|�[�Y���Ă��������󋵂́A
				//ME�Ɍ��肳��AME�͕K����~�A�|�[�Y����������I
				//�����ŕK���APLAYER_BGM���~���Ă����Ȃ��I
				Snd_PlayerBgmStop();

				Snd_BgmPlay( wk->next_bgm_no );				//BGM�Đ�(�X�e�[�^�X���Đ�)
			}
		}
		break;

	//�t�F�[�h�A�E�g �� BGM�t�F�[�h�C��
	case SND_STATUS_FADEOUT_NEXT_FADEIN:
		if( Snd_FadeCheck() == 0 ){							//�t�F�[�h�I���҂�
			if( Snd_NextWaitCheck() == 0 ){					//����BGM��炷�܂ł̃E�F�C�g�`�F�b�N

				//PLAYER_BGM��炵�Ȃ���}�b�v�J�ڂ������̑Ή�
				//PLAYER_BGM���|�[�Y���Ă��������󋵂́A
				//ME�Ɍ��肳��AME�͕K����~�A�|�[�Y����������I
				//�����ŕK���APLAYER_BGM���~���Ă����Ȃ��I
				Snd_PlayerBgmStop();

				Snd_BgmPlay( wk->next_bgm_no );				//BGM�Đ�(�X�e�[�^�X���Đ�)

				//�t�F�[�h�C��(�X�e�[�^�X���t�F�[�h�C��)
				Snd_BgmFadeIn( BGM_VOL_MAX, wk->next_frame, BGM_FADEIN_START_VOL_MIN );
			}
		}
		break;

	};

	return;
}

//--------------------------------------------------------------
/**
 * @brief	�T�E���h�X�e�[�^�X�Z�b�g
 *
 * @param	status		�X�e�[�^�X(snd_system.h�Q��)
 *
 * @retval	none
 */
//--------------------------------------------------------------
void Snd_StatusSet( int status )
{
	SND_WORK* wk = Snd_GetSystemAdrs();
	wk->seq = 0;
	snd_status = status;

#ifdef SOUND_OS_PRINT_ON
	OS_Printf( "\n���݂̃T�E���h�X�e�[�^�X = %d\n\n", snd_status );
#endif

	return;
}

//--------------------------------------------------------------
/**
 * @brief	�T�E���h�X�e�[�^�X�`�F�b�N
 *
 * @param	chg_status	�X�e�[�^�X(snd_system.h�Q��)
 *
 * @retval	"TRUE=���AFALSE=�s��"
 */
//--------------------------------------------------------------
BOOL Snd_StatusCheck( int chg_status )
{
	//�X�e�[�^�X(�t�F�[�h�A�E�g���Đ�)�̎��ɁA�g���b�N�t�F�[�h�ɐ؂�ւ��邱�Ƃ͕s�I
	if( (snd_status == SND_STATUS_FADEOUT_NEXT_PLAY) && (chg_status == SND_STATUS_TRACKFADE ) ){
		return FALSE;
	}

	return TRUE;
}

//--------------------------------------------------------------
/**
 * @brief	ME�g�p�����`�F�b�N
 *
 * @param	none
 *
 * @retval	"TRUE=�g�p���AFALSE=�g�p���Ă��Ȃ�"
 */
//--------------------------------------------------------------
static BOOL Snd_MeUseCheck(void)
{
	SND_WORK* wk = Snd_GetSystemAdrs();

	if( Snd_PlayerCountPlayingSeq(PLAYER_ME) != 0 ){ return TRUE; }		//ME�V�[�P���X�`�F�b�N
	if( wk->me_wait != 0 ){ return TRUE; }								//ME�E�F�C�g�`�F�b�N

	return FALSE;
}


//==============================================================================================
//
//	�T�E���h�V�X�e�����[�N�A�N�Z�X�֘A
//
//==============================================================================================

//--------------------------------------------------------------
/**
 * @brief	�T�E���h�V�X�e�����[�N�̃A�h���X���擾
 *
 * @param	none
 *
 * @retval	"�T�E���h�V�X�e�����[�N�̃A�h���X"
 */
//--------------------------------------------------------------
SND_WORK* Snd_GetSystemAdrs()
{
	return (SND_WORK*)&snd_work;
}

//--------------------------------------------------------------
/**
 * @brief	�T�E���h�V�X�e�����[�N�̃����o�̃A�h���X���擾
 *
 * @param	type	�����oID
 *
 * @retval	"�����o�̃A�h���X"
 */
//--------------------------------------------------------------
void* Snd_GetParamAdrs( int type )
{
	SND_WORK* wk = Snd_GetSystemAdrs();

	switch( type ){

	case SND_W_ID_CTRL_BGM_FLAG:				//�t�B�[���hBGM�Œ�t���O
		return &wk->ctrl_bgm_flag;

	case SND_W_ID_WAVEOUT_HANDLE_NORMAL:		//�g�`�n���h��
		return &wk->sWaveOutHandle[0];

	case SND_W_ID_WAVEOUT_HANDLE_CHORUS:		//�g�`�n���h��
		return &wk->sWaveOutHandle[1];

	case SND_W_ID_BANK_INFO:					//�o���N���\����
		return &wk->info;

	case SND_W_ID_CAPTURE_BUF:					//�L���v�`���o�b�t�@
		return &wk->sCaptureBuffer;

	case SND_W_ID_CALLBACK_INFO:				//�G�t�F�N�g�̃R�[���o�b�N�ϐ�
		return &wk->callbackInfo;

	case SND_W_ID_FADE_COUNT:					//�t�F�[�h�J�E���^�[
		return &wk->fade_count;

	case SND_W_ID_NEXT_WAIT:					//����BGM��炷�܂ł̃E�F�C�g
		return &wk->next_wait;

	case SND_W_ID_NEXT_FRAME:					//����BGM�̃t�F�[�h�C���t���[����
		return &wk->next_frame;

	case SND_W_ID_NOW_BGM_NO:					//����BGM�i���o�[
		return &wk->now_bgm_no;					//�Z�[�u����K�v����I(���Ƃňړ�����)

	case SND_W_ID_NEXT_BGM_NO:					//����BGM�i���o�[
		return &wk->next_bgm_no;				//�Z�[�u����K�v����I(���Ƃňړ�����)

	case SND_W_ID_FIELD_PAUSE_FLAG:				//PLAYER_FIELD���|�[�Y���Ă��邩�t���O
		return &wk->field_pause_flag;

	case SND_W_ID_BGM_PAUSE_FLAG:				//PLAYER_BGM���|�[�Y���Ă��邩�t���O
		return &wk->bgm_pause_flag;

	case SND_W_ID_ME_WAIT:						//ME�E�F�C�g
		return &wk->me_wait;

	case SND_W_ID_REVERSE_FLAG:					//�t�Đ��g�p�t���O
		return &wk->reverse_flag;

	case SND_W_ID_WAVEOUT_CH_NORMAL_FLAG:		//�g�`�Ŏg�p����CH���m�ۂ������t���O
		return &wk->waveout_ch_normal_flag;

	case SND_W_ID_WAVEOUT_CH_CHORUS_FLAG:		//�g�`�Ŏg�p����CH���m�ۂ������t���O(CHORUS)
		return &wk->waveout_ch_chorus_flag;

	case SND_W_ID_CHORUS_FLAG:					//�R�[���X�g�p�t���O
		return &wk->chorus_flag;

	case SND_W_ID_BANK_FLAG:					//�o���N�؂�ւ��邩�t���O
		return &wk->bank_flag;

	case SND_W_ID_FILTER_SIZE:					//�t�B���^�[�T�C�Y
		return &wk->filter_size;

	case SND_W_ID_SCENE_MAIN:					//���݂̃��C���V�[��
		return &wk->scene_main;

	case SND_W_ID_SCENE_SUB:					//���݂̃T�u�V�[��
		return &wk->scene_sub;

	case SND_W_ID_HEAP_SAVE_START:				//�T�E���h�q�[�v�K�w���x��
		return &wk->heap_save[SND_HEAP_SAVE_START];

	case SND_W_ID_HEAP_SAVE_GLOBAL:				//�T�E���h�q�[�v�K�w���x��
		return &wk->heap_save[SND_HEAP_SAVE_GLOBAL];

	case SND_W_ID_HEAP_SAVE_BGM_BANK:			//�T�E���h�q�[�v�K�w���x��
		return &wk->heap_save[SND_HEAP_SAVE_BGM_BANK];

	case SND_W_ID_HEAP_SAVE_SE:					//�T�E���h�q�[�v�K�w���x��
		return &wk->heap_save[SND_HEAP_SAVE_SE];

	case SND_W_ID_HEAP_SAVE_BGM:				//�T�E���h�q�[�v�K�w���x��
		return &wk->heap_save[SND_HEAP_SAVE_BGM];

	case SND_W_ID_HEAP_SAVE_SUB_SE:				//�T�E���h�q�[�v�K�w���x��
		return &wk->heap_save[SND_HEAP_SAVE_SUB_SE];

	case SND_W_ID_HEAP_SAVE_ME:					//�T�E���h�q�[�v�K�w���x��
		return &wk->heap_save[SND_HEAP_SAVE_ME];

	case SND_W_ID_PERAP_PLAY_FLAG:				//�y���b�v�̘^�������������Đ����Ă��邩�t���O
		return &wk->perap_play_flag;

	case SND_W_ID_PERAP_DEFAULT_FLAG:			//�y���b�v�̃f�t�H���g�̖������Đ�����t���O
		return &wk->perap_default_flag;

	case SND_W_ID_ZONE_BGM:						//�]�[��BGM�i���o�[
		return &wk->zone_bgm;

	case SND_W_ID_WAVE_DATA:					//�g�`�f�[�^�̃|�C���^
		return &wk->wave_data;

	case SND_W_ID_REVERSE_BUF:					//�t�Đ��p�̃o�b�t�@�̃|�C���^
		return &wk->reverse_buf;

	case SND_W_ID_LENGTH_TCB:					//�����Đ�����TCB
		return &wk->length_tcb;

	case SND_W_ID_MY_PERAP_PTR:					//�����̂؃��b�v�{�C�X�̃|�C���^
		return &wk->my_perap_ptr;

	case SND_W_ID_PERAP_PTR1:					//�؃��b�v�{�C�X�̃|�C���^
		return &wk->perap_ptr[0];

	case SND_W_ID_PERAP_PTR2:					//�؃��b�v�{�C�X�̃|�C���^
		return &wk->perap_ptr[1];

	case SND_W_ID_PERAP_PTR3:					//�؃��b�v�{�C�X�̃|�C���^
		return &wk->perap_ptr[2];

	case SND_W_ID_PERAP_PTR4:					//�؃��b�v�{�C�X�̃|�C���^
		return &wk->perap_ptr[3];
	};

	GF_ASSERT( (0) && "�������s���ł��I" );
	return NULL;
}


//==============================================================================================
//
//	�q�[�v�������֘A
//
//==============================================================================================

//--------------------------------------------------------------
/**
 * @brief	�������̏�Ԃ�ۑ�
 *
 * @param	heap_lv		�ۑ���̏�Ԃ̊K�w���x�����Ƃ��Ă������[�N�ւ̃|�C���^
 *						(NULL���Ɖ������Ȃ�)
 *
 * @retval	"�ۑ���̊K�w���x���A���s�����-1"
 *
 * �q�[�v�쐬����̊K�w���x����0�ŁA���̊֐����ĂԖ��ɁA�K�w���x�����P�����܂��B 
 * NNS_SndHeapLoadState�֐����Ăт������ƂŁA
 * �w�肵���K�w���x���̕ۑ�����̏�Ԃɕ��������邱�Ƃ��ł��܂��B 
 *
 * ��Ԃ̕ۑ��ɂ́A�q�[�v����������܂��B�q�[�v�̋󂫗e�ʂ����Ȃ��ꍇ�́A�֐��Ɏ��s���܂��B 
 */
//--------------------------------------------------------------
int Snd_HeapSaveState( int* heap_lv )
{
	int ret;
	SND_WORK* wk = Snd_GetSystemAdrs();

	ret = NNS_SndHeapSaveState(wk->heap);

	//���s�`�F�b�N
	if( ret == -1 ){
		GF_ASSERT( (0) && "NNS_SndHeapSaveState ERROR�I" );
	}

	if( heap_lv != NULL ){
		*heap_lv = ret;
	}

#ifdef SOUND_OS_PRINT_ON
	OS_Printf( "��ԕۑ��ɂ̓q�[�v������܂�\n�ۑ���̊K�w���x�� = %d\n", ret );
	Snd_UseHeapSizeOsPrint();						//��ԕۑ��ɂ̓q�[�v�������
#endif

	return ret;
}

//--------------------------------------------------------------
/**
 * @brief	�������̏�Ԃ𕜌�
 *
 * @param	level	��������K�w���x��
 *
 * @retval	none
 *
 * NNS_SndHeapSaveState�֐����Ă񂾒���̏�Ԃɖ߂����Ƃ��o����
 * ���Ȃ킿�ANNS_SndHeapSaveState�֐����Ă񂾌�Ƀ��[�h�����f�[�^���폜�����
 * ���̎��A���[�h�ς݃T�E���h�f�[�^���g���čĐ�����Ă��鉹�͎~�܂�܂���
 */
//--------------------------------------------------------------
void Snd_HeapLoadState( int level )
{
	SND_WORK* wk = Snd_GetSystemAdrs();

	NNS_SndHeapLoadState( wk->heap, level );

#ifdef SOUND_OS_PRINT_ON
	Snd_UseHeapSizeOsPrint();	//�ǉ������T�E���h�q�[�v�̗e�ʂ��o�͂���
#endif

	return;
}

//--------------------------------------------------------------
/**
 * @brief	�ǉ������T�E���h�q�[�v�̗e�ʂƁA�󂫗e�ʂ��o�͂���
 *
 * @param	none
 *
 * @retval	none
 *
 * �v���C���[�q�[�v���m�ۂ���ƁA���̕��e�ʂ������Ă���̂Œ��ӁI
 */
//--------------------------------------------------------------
void Snd_UseHeapSizeOsPrint(void)
{
	u32 size;
	SND_WORK* wk = Snd_GetSystemAdrs();

#ifdef SOUND_OS_PRINT_ON
	size = NNS_SndHeapGetFreeSize( wk->heap );							//���݂̋󂫗e�ʂ��擾

	//�T�C�Y��r
	if( aki_size < size ){
		OS_Printf( "�J�������T�E���h�q�[�v�� = %d\n", (size-aki_size) );//�J�������e�ʂ�\��
	}else if( aki_size == size ){
		OS_Printf( "�T�E���h�q�[�v�ʂɕω��Ȃ�\n" );
	}else{
		OS_Printf( "�ǉ������T�E���h�q�[�v�� = %d\n", (aki_size-size) );//�ǉ������e�ʂ�\��
	}

	aki_size = size;
	OS_Printf( "�T�E���h�q�[�v�̋󂫗e�� = %d\n\n", aki_size );			//�󂫗e�ʂ�\��
#endif
	return;
}

//--------------------------------------------------------------
/**
 * @brief	�T�E���h�q�[�v�̃A�h���X���擾
 *
 * @param	none
 *
 * @retval	"�T�E���h�q�[�v�̃A�h���X"
 */
//--------------------------------------------------------------
NNSSndHeapHandle* Snd_HeapHandleGet(void)
{
	SND_WORK* wk = Snd_GetSystemAdrs();
	return &wk->heap;
}


//==============================================================================================
//
//	�f�[�^���[�h�֘A
//
//	snd_tool.c
//	FILED,BATTLE�Ȃǂ̃f�[�^�Z�b�g�֐������ɌĂ΂��
//
//==============================================================================================

//--------------------------------------------------------------
/**
 * @brief	�O���[�v���[�h
 *
 * @param	no		�O���[�v�i���o�[
 *
 * @retval	"����=TRUE�A���s=FALSE"
 */
//--------------------------------------------------------------
BOOL Snd_ArcLoadGroup( u16 no )
{
	int ret;
	SND_WORK* wk = Snd_GetSystemAdrs();

	ret = NNS_SndArcLoadGroup( no, wk->heap );

#ifdef SOUND_OS_PRINT_ON
	OS_Printf( "�����O���[�v���[�h�� �O���[�vNo = %d ����=TRUE�A���s=FALSE ����=%d\n", no, ret );
	Snd_UseHeapSizeOsPrint();							//�ǉ������T�E���h�q�[�v�̗e�ʂ��o�͂���
#endif

	return ret;
}

//--------------------------------------------------------------
/**
 * @brief	�V�[�P���X�f�[�^�A�o���N�f�[�^�A�g�`�f�[�^��(����)�Ƀ��[�h
 *
 * @param	no		�V�[�P���X�i���o�[
 *
 * @retval	"����=TRUE�A���s=FALSE"
 */
//--------------------------------------------------------------
BOOL Snd_ArcLoadSeq( u16 no )
{
	int ret;
	SND_WORK* wk = Snd_GetSystemAdrs();

    ret = NNS_SndArcLoadSeq( no, wk->heap );

#ifdef SOUND_OS_PRINT_ON
	OS_Printf( "�����V�[�P���X���[�h�� �V�[�P���XNo = %d ����=TRUE�A���s=FALSE ����=%d\n", no, ret );
	Snd_UseHeapSizeOsPrint();							//�ǉ������T�E���h�q�[�v�̗e�ʂ��o�͂���
#endif

	return ret;
}

//--------------------------------------------------------------
/**
 * @brief	�V�[�P���X�f�[�^�A�o���N�f�[�^�A�g�`�f�[�^��(�I���)���[�h
 *
 * @param	no		�V�[�P���X�i���o�[
 * @param	flag	�ǂ̃f�[�^�����[�h���邩
 *
 * @retval	"����=TRUE�A���s=FALSE"
 *
 * �����[�h��`��
 * �V�[�P���X�f�[�^	NNS_SND_ARC_LOAD_SEQ 
 * �o���N�f�[�^		NNS_SND_ARC_LOAD_BANK
 * �g�`�A�[�J�C�u	NNS_SND_ARC_LOAD_WAVE
 */
//--------------------------------------------------------------
BOOL Snd_ArcLoadSeqEx( u16 no, u32 flag )
{
	int ret;
	SND_WORK* wk = Snd_GetSystemAdrs();

    ret = NNS_SndArcLoadSeqEx( no, flag, wk->heap );

#ifdef SOUND_OS_PRINT_ON
	OS_Printf( "�����V�[�P���X���[�h���ꁄ �V�[�P���XNo = %d ����=TRUE�A���s=FALSE ����=%d\n", no, ret );
	Snd_UseHeapSizeOsPrint();							//�ǉ������T�E���h�q�[�v�̗e�ʂ��o�͂���
#endif

	return ret;
}

//--------------------------------------------------------------
/**
 * @brief	�V�[�P���X�A�[�J�C�u�����[�h
 *
 * @param	no		�V�[�P���X�A�[�J�C�u�i���o�[
 *
 * @retval	"����=TRUE�A���s=FALSE"
 *
 * �V�[�P���X�A�[�J�C�u�́A�����̃o���N�Ɗ֘A�����邽�߁A
 * �����I�Ƀo���N�f�[�^��g�`�f�[�^�̓��[�h����Ȃ�
 */
//--------------------------------------------------------------
BOOL Snd_ArcLoadSeqArc( u16 no )
{
	int ret;
	SND_WORK* wk = Snd_GetSystemAdrs();

    ret = NNS_SndArcLoadSeqArc( no, wk->heap );

#ifdef SOUND_OS_PRINT_ON
	OS_Printf( "�����V�[�P���XARC���[�h�� SEQ_ARCNo = %d ����=TRUE�A���s=FALSE ����=%d\n", no, ret );
	Snd_UseHeapSizeOsPrint();							//�ǉ������T�E���h�q�[�v�̗e�ʂ��o�͂���
#endif

	return ret;
}

//--------------------------------------------------------------
/**
 * @brief	�g�`�A�[�J�C�u�����[�h
 *
 * @param	no		�g�`�A�[�J�C�u�i���o�[
 *
 * @retval	"����=TRUE�A���s=FALSE"
 */
//--------------------------------------------------------------
BOOL Snd_ArcLoadWaveArc( u16 no )
{
	int ret;
	SND_WORK* wk = Snd_GetSystemAdrs();

    ret = NNS_SndArcLoadWaveArc( no, wk->heap );

#ifdef SOUND_OS_PRINT_ON
	OS_Printf("�����g�`�A�[�J�C�u���[�h�� �o���NNo = %d ����=TRUE�A���s=FALSE ����=%d\n", no, ret );
	Snd_UseHeapSizeOsPrint();							//�ǉ������T�E���h�q�[�v�̗e�ʂ��o�͂���
#endif

	return ret;
}

//--------------------------------------------------------------
/**
 * @brief	�o���N�f�[�^�����[�h(�K�v�Ȕg�`�f�[�^�����[�h�����)
 *
 * @param	no		�o���N�i���o�[
 * @param	heap	�q�[�v�A�h���X
 *
 * @retval	"����=TRUE�A���s=FALSE"
 */
//--------------------------------------------------------------
BOOL Snd_ArcLoadBank( u16 no )
{
	int ret;
	SND_WORK* wk = Snd_GetSystemAdrs();

    ret = NNS_SndArcLoadBank( no, wk->heap );

#ifdef SOUND_OS_PRINT_ON
	OS_Printf( "�����o���N���[�h�� �o���NNo = %d ����=TRUE�A���s=FALSE ����=%d\n", no, ret );
	Snd_UseHeapSizeOsPrint();							//�ǉ������T�E���h�q�[�v�̗e�ʂ��o�͂���
#endif

	return ret;
}


//==============================================================================================
//
//	�T�E���h�n���h���A�g�`�n���h���֘A
//
//	snd_play.c
//	BGM,ME,SE,PMVOICE�̍Đ��֐������ɌĂ΂��
//
//==============================================================================================

//--------------------------------------------------------------
/**
 * @brief	�T�E���h�n���h���̃A�h���X���擾
 *
 * @param	type	�T�E���h�n���h���^�C�v
 *
 * @retval	"�T�E���h�n���h���̃A�h���X"
 */
//--------------------------------------------------------------
NNSSndHandle * Snd_HandleGet( int type )
{
	SND_WORK* wk = Snd_GetSystemAdrs();

	if( type >= SND_HANDLE_MAX ){
		GF_ASSERT( (0) && "�T�E���h�n���h���^�C�v���s���ł��I" );
		type = SND_HANDLE_FIELD;
	}

	return &wk->Handle[type];
}

//--------------------------------------------------------------
/**
 * @brief	�v���C���[�i���o�[����A�n���h���i���o�[�擾(�n���h���̃A�h���X�ł͂Ȃ��̂Œ��ӁI)
 *
 * @param	player_no	�v���C���[�i���o�[
 *
 * @retval	"�n���h���i���o�["
 */
//--------------------------------------------------------------
int Snd_GetHandleNoByPlayerNo( int player_no )
{
	int type;

	//SE�n���h���i���o�[�擾
	switch( player_no ){

	case PLAYER_FIELD:
		type = SND_HANDLE_FIELD;				//�t�B�[���hBGM�T�E���h�n���h��
		break;
		
	case PLAYER_PV:
		type = SND_HANDLE_PMVOICE;				//�|�P���������T�E���h�n���h��
		break;

	case PLAYER_ME:
		type = SND_HANDLE_ME;					//ME�T�E���h�n���h��
		break;

	case PLAYER_SE_1:
		type = SND_HANDLE_SE_1;
		break;

	case PLAYER_SE_2:
		type = SND_HANDLE_SE_2;
		break;

	case PLAYER_SE_3:
		type = SND_HANDLE_SE_3;
		break;

	case PLAYER_SE_4:
		type = SND_HANDLE_SE_4;
		break;

	case PLAYER_BGM:
		type = SND_HANDLE_BGM;					//�t�B�[���h�ȊO��BGM�n���h��
		break;

	//case PLAYER_CHORUS:						//PLAYER�Ƃ��Ă͑��݂��Ȃ��I
	//	type = SND_HANDLE_CHORUS;				//�R�[���X(������p)�n���h��
	//	break;

	default:
		GF_ASSERT( (0) && "�v���C���[�i���o�[���s���ł��I" );
		type = SND_HANDLE_SE_1;					//�G���[���
		break;
	};

	return type;
}


//==============================================================================================
//
//	�V�[�P���X�֘A
//
//==============================================================================================

//--------------------------------------------------------------
/**
 * @brief	�S�Ă̍Đ����̃V�[�P���X���ꎞ��~�܂��͍ĊJ
 *
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
void Snd_PlayerPauseAll( BOOL flag )
{
	NNS_SndPlayerPauseAll( flag );
	return;
}


//==============================================================================================
//
//	���[�J���֐�
//
//==============================================================================================

//--------------------------------------------------------------
/**
 * @brief	�T�E���h�V�X�e�����[�N�̏�����
 *
 * @param	wk		SND_WORK�^�̃A�h���X
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void Snd_WorkInit( SND_WORK* wk )
{
	int i;

	memset( wk, 0, sizeof(SND_WORK) );

	//�K�w���x��
	for( i=0; i < SND_HEAP_SAVE_MAX ;i++ ){
		//�J�n=1,�풓=2,BGM_BANK=3,SE=4,BGM=5,SUB_SE=6,ME=7
		wk->heap_save[i] = (i+1);						//�����l�Z�b�g
	}

	return;
}

//--------------------------------------------------------------
/**
 * @brief	�T�E���h�n���h��������
 *
 * @param	wk		SND_WORK�^�̃A�h���X
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void Snd_HandleInit( SND_WORK* wk )
{
	int i;

	for( i=0; i < SND_HANDLE_MAX ;i++ ){
		NNS_SndHandleInit( &wk->Handle[i] );
	}

	return;
}

//--------------------------------------------------------------
/**
 * @brief	�Q�[���J�n���̃T�E���h�f�[�^�̃��[�h
 *
 * @param	wk		SND_WORK�^�̃A�h���X
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void Snd_GameStartLoad( SND_WORK* wk )
{
	int ret;

	//�O���[�v���[�h(����=TRUE�A���s=FALSE)
	
	Snd_HeapSaveState(&wk->heap_save[SND_HEAP_SAVE_START]);		//�K�w�ۑ�(�S�ď������Ɏg�p)
	ret = Snd_ArcLoadGroup( GROUP_GLOBAL );	//�풓

	//basic.bnk�́A�S�풓�ɂ��Ă���
	
	Snd_HeapSaveState(&wk->heap_save[SND_HEAP_SAVE_GLOBAL]);	//�K�w�ۑ�(�풓�ȊO���������Ɏg�p)

	//�������́A�^�C�g���Ȃ�ǂݍ��ނ��ƂɂȂ�I
	//�V�[��(���)���ς�鎞�̃T�E���h�f�[�^�Z�b�g
	//Snd_SceneDataSet( SND_SCENE_FIELD, SEQ_DP_TITLE, 0 );
	//title.c�ɓ������������Ă���̂ŊO����

	return;
}

//--------------------------------------------------------------
/**
 * @brief	�}�C�N������(�Ƃ肠�����Q�C���ȂǌŒ�)
 *
 * @param	none
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void Snd_MicInit(void)
{
	//MIC_Init�֐��̏������́A2��ڈȍ~�̌Ăяo���͖����ɂȂ�悤�ɁA
	//�����t���O�Ń`�F�b�N����Ă��܂�
    MIC_Init();								//MIC_API������
    
	//OS_Init()���Ăԏꍇ�́A���̒�����Ă΂�܂��̂ŕK�v����܂���B
    //PM_Init();							//PMIC�}�l�[�W��������(OS_INIT���ł��Ă΂�Ă���)
	
    (void)PM_SetAmp( PM_AMP_ON );			//�v���O���}�u���Q�C���A���v�̃X�C�b�`ON
    (void)PM_SetAmpGain( PM_AMPGAIN_80 );	//�v���O���}�u���Q�C���A���v�̃Q�C����ݒ�

	return;
}

//--------------------------------------------------------------
/**
 * @brief	PLAYER_BGM�̒�~
 *
 * @param	none
 *
 * @retval	none
 *
 * �T�E���h�n���h���Ɍ��т����Ă���V�[�P���X��������܂��B
 * �V�[�P���X�����т����Ă��Ȃ��ꍇ�́A�������܂���B
 *
 * PLAYER�ɑ΂��Ă̂ݒ�~�A�����[�X�����Ă���
 */
//--------------------------------------------------------------
static void Snd_PlayerBgmStop( void )
{
	NNS_SndPlayerStopSeqByPlayerNo( PLAYER_BGM, 0 );
	NNS_SndHandleReleaseSeq( Snd_HandleGet(SND_HANDLE_BGM) );
	return;
}


