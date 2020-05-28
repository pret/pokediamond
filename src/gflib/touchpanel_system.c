//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *@file		touchpanel.c
 *@brief	�^�b�`�p�l���V�X�e���̎���
 *@author	tomoya takahashi
 *@data		2004.12.03
 *
 */
 //]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
#include "system.h"
#include "assert.h"
#include "calc2d.h"
#define __TOUCHPANEL_SYSTEM_H_GLOBAL
#include "touchpanel_system.h"
#include "bg_system.h"
#include "gflib_os_print.h"

/*-----------------------------------------------------------------------------
 *					�萔�錾
 ----------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 *					�\���̐錾
 ----------------------------------------------------------------------------*/
//----------------------------------------------------------------------------
/**
 *					�v���g�^�C�v�錾
 */
//-----------------------------------------------------------------------------
//-------------------------------------
/// �^�b�`�p�l���V�X�e���p
static u32 startSampling( u32 sync );		// �T���v�����O�̊J�n���߂�]��
static u32 stopSampling( void );					// �T���v�����O��~
//static u32 mainBuff( u32 last_idx );		// �o�b�t�@�ɃT���v�����O�f�[�^���i�[
static u32 mainBuffComp( u32 type, u32 last_idx, u32 comp_num );	// ���k���[�h
static u32 mainBuffJust( u32 type, u32 last_idx );	// ���̂܂܃o�b�t�@�Ɋi�[
//static u32 mainBuffNoLoop( u32 type, u32 last_idx, u32 comp_num );				// ��̃o�b�t�@�����[�v���Ȃ��o�[�W����
static void getThisSyncData( TP_ONE_DATA* pData, u32 last_idx );	// ���̃V���N�̃^�b�`�p�l���̏����擾
static u32 modeBuff( u32 type, u32 last_idx, u32 comp_num );				// �o�b�t�@�����O���[�h�̃��C���֐�

static void setStartBufferingParam( u32 SampFlag, u32 auto_samp, void* pBuff, u32 buffSize, u32 nowBuffPoint, u32 Sync );
static void oneSyncBuffClean( TPData* pBuff, int num );

//-------------------------------------
// �^�b�`�p�l���A�G���p
//
// �o�b�t�@���璸�_�ƃx�N�g���f�[�^���쐬����
static u32 makePointData( TPData* pBuff, u32 size, u16 check_num, Vec2DS32* p_work );
// ���݂���ׂ���_�����`�F�b�N
static u8	checkInVector( Vec2DS32* p_main_s, Vec2DS32* p_main_e, Vec2DS32* vect_1, Vec2DS32* vect_2, Vec2DS32* vect_3 );
// �ŏI�_�ƍŏ��̓_���Ȃ���
static u32	crossToPict( TPData s_TPData, Vec2DS32* p_check, Vec2DS32* p_in, u32 dist );
// ��_�܂ł̃f�[�^�ɂ���
static u32 crossEndPict( Vec2DS32* p_work, u32* p_size, u8 flag );
//----------------------------------------------------------------------------
/**
 *					�O���[�o���ϐ��錾
 */
//-----------------------------------------------------------------------------
typedef struct {
	TPData* pTouchPanelBuff;					// �o�b�t�@�|�C���^�i�[�p
	u32		TouchPanelBuffSize;						// �o�b�t�@�T�C�Y�i�[�p
	u32		TouchPanelSync;							// �P�t���[���ɉ���T���v�����O���邩
	TPData	TouchPanelOneSync[ TP_ONE_SYNC_BUFF ];	// �P�t���[���ɃT���v�����O���ꂽ�f�[�^�i�[�p
	u32		TouchPanelNowBuffPoint;					// ���o�b�t�@�Ƀf�[�^�����Ă���Ƃ���
	u16		TouchPanelSampFlag;						// �T���v�����O�t���O
	u16		TouchPanelExStop;						// �T���v�����O�������~�t���O
} TOUCH_PANEL_WORK;

static TOUCH_PANEL_WORK TPWork;


//----------------------------------------------------------------------------
/**
 *
 *@brief	�^�b�`�p�l�����g�p���鏀�����s���܂�
 *
 *@param	none
 *
 *@return	none
 *
 */
//-----------------------------------------------------------------------------
void InitTPSystem( void )
{

	// �X���[�v��~��
	GF_ASSERT( TPWork.TouchPanelExStop == FALSE );
	
	// �T���v�����O�t���O��������
	TPWork.TouchPanelSampFlag = TP_SAMP_NONE;
	TPWork.TouchPanelExStop = FALSE;
}


//----------------------------------------------------------------------------
/**
 *@brief	�^�b�`�p�l���̃T���v�����O�J�n
 *
 *@param	p_buff�F�T���v�����O�f�[�^������o�b�t�@
 *@param	size�F�o�b�t�@�̃T�C�Y
 *@param	sync�F�P�t���[���ɉ���T���v�����O����̂�(MAX4)
 *
 *@retval	TP_OK�F����
 *@retval�@	TP_FIFO_ERR�F�]�����s
 *@retval	TP_ERR�F�]���ȊO�̎��s
 */
//-----------------------------------------------------------------------------
u32 InitTP( TPData* p_buff, u32 size, u32 sync )
{
	int	check_num = 0;
	u32	result;
	int i;

	// �X���[�v��~��
	GF_ASSERT( TPWork.TouchPanelExStop == FALSE );
	
	// �^�b�`�p�l���T���v�����O�V�X�e���ɃT���v�����O�J�n���߂𑗂�A
	// ����Ɏ��s���ꂽ�����`�F�b�N����
	// �P�t���[���ɂT�ȏ�T���v�����O���悤�Ƃ�����G���[��Ԃ�
	if( (sync >= 5) || (sync <= 0) ){
#ifdef TOUCHPANEL_SYSTEM_OS_PRINTF_ON
		OS_Printf( "�P�t���[���̃T���v�����O�͂S���ō��ł��B%d�͂ł��܂���\n", sync );
#endif
		return TP_ERR;
	}

	// �T���v�����O���Ȃ甲����
	if( TPWork.TouchPanelSampFlag != TP_SAMP_NONE ){
#ifdef TOUCHPANEL_SYSTEM_OS_PRINTF_ON
		OS_Printf("InitTP�F�T���v�����O���ł�\n");
#endif
		return TP_ERR;
	}
	
	// �T���v�����O���ߓ]��
	result = startSampling( sync );

	// �]���Ɏ��s������G���[��Ԃ�
	if( result != TP_OK ){
		return result;
	}

	// �T���v�����O�f�[�^�ݒ�
	setStartBufferingParam( TP_BUFFERING, TRUE,
			p_buff, size, 0,
			sync * 2 ); // 30�t���[������̂���

	return TP_OK;
}

//----------------------------------------------------------------------------
/**
 *@brief	�^�b�`�p�l���̃T���v�����O�J�n	�o�b�t�@�����O�Ȃ�
 *
 *@param	sync�F�P�t���[���ɉ���T���v�����O����̂�(MAX4)
 *
 *@retval	TP_OK�F����
 *@retval�@	TP_FIFO_ERR�F�]�����s
 *@retval	TP_ERR�F�]���ȊO�̎��s
 */
//-----------------------------------------------------------------------------
u32 InitTPNoBuff( u32 sync )
{
	u32	result;
	int i;

	// �X���[�v��~��
	GF_ASSERT( TPWork.TouchPanelExStop == FALSE );
	
	// �^�b�`�p�l���T���v�����O�V�X�e���ɃT���v�����O�J�n���߂𑗂�A
	// ����Ɏ��s���ꂽ�����`�F�b�N����
	// �P�t���[���ɂT�ȏ�T���v�����O���悤�Ƃ�����G���[��Ԃ�
	if( (sync >= 5) || (sync <= 0) ){
#ifdef TOUCHPANEL_SYSTEM_OS_PRINTF_ON
		OS_Printf( "�P�t���[���̃T���v�����O�͂S���ō��ł��B%d�͂ł��܂���\n", sync );
#endif
		return TP_ERR;
	}

	// �T���v�����O���Ȃ甲����
	if( TPWork.TouchPanelSampFlag != TP_SAMP_NONE ){
#ifdef TOUCHPANEL_SYSTEM_OS_PRINTF_ON
		OS_Printf("InitTP�F�T���v�����O���ł�\n");
#endif
		return TP_ERR;
	}
	
	// �T���v�����O���ߓ]��
	result = startSampling( sync );

	// �]���Ɏ��s������G���[��Ԃ�
	if( result != TP_OK ){
		return result;
	}

	// �T���v�����O�f�[�^�ݒ�
	setStartBufferingParam( TP_NO_BUFF, TRUE,
			NULL, 0, 0,
			sync * 2 ); // 30�t���[������̂���
	

	return TP_OK;
}


//----------------------------------------------------------------------------
/**
 *	@brief	�T���v�����O�J�n���̃f�[�^�ݒ�
 *
 *	@param	SampFlag		�T���v�����O�t���O
 *	@param	auto_samp		AUTO�T���v�����O�t���O
 *	@param	pBuff			�o�b�t�@�|�C���^
 *	@param	buffSize		�o�b�t�@�T�C�Y
 *	@param	nowBuffPoint	���T���v�����̈ʒu
 *	@param	Sync			�V���N��
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void setStartBufferingParam( u32 SampFlag, u32 auto_samp, void* pBuff, u32 buffSize, u32 nowBuffPoint, u32 Sync )
{
	// �T���v�����O�t���O���Z�b�g
	TPWork.TouchPanelSampFlag = SampFlag;
	sys.tp_auto_samp = auto_samp;		// �V�X�e���̃t���O���I�[�g�T���v�����O���ɂ���
	// �o�b�t�@�̃|�C���^�ƃT�C�Y���i�[
	TPWork.pTouchPanelBuff = pBuff;
	TPWork.TouchPanelBuffSize = buffSize;
	TPWork.TouchPanelSync = Sync;
	TPWork.TouchPanelNowBuffPoint = nowBuffPoint;
	oneSyncBuffClean( TPWork.TouchPanelOneSync, TP_ONE_SYNC_BUFF );
}

//----------------------------------------------------------------------------
/**
 *	@brief	1�V���N�p�o�b�t�@�̏�����
 *
 *	@param	pBuff	�o�b�t�@
 *	@param	num		��
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void oneSyncBuffClean( TPData* pBuff, int num )
{
	int i;

	for( i = 0; i < num; i++ ){
		pBuff[ i ].touch = 0;
	}	
}

//----------------------------------------------------------------------------
/**
 *	@brief	�T���v�����O��~
 */
//-----------------------------------------------------------------------------
static u32 stopSampling( void )
{
	u32 check_num = 0;			// ������
	u32 result;					// ����
	int	i;						// ���[�v�p

	// ���݂̃T���v�����O���I������
	// ����ɖ��߂̓]���������������Ǘ�����
	//
	// ���T���v�����O���Ă���̂�����
	if( TPWork.TouchPanelSampFlag == TP_SAMP_NONE )
	{
		// �T���v�����O���Ă��Ȃ��̂łƂ܂�����Ԃł��B
		return TP_OK;
	}

	// �I�����߂��G���[���A���Ă���ԑ��葱����
	// �iFIFO��ARM7�ɖ��߂𑗂��Ă��邽�߁A���������K�v������j
	do
	{
		// �I�����߂𑗂�
		TP_RequestAutoSamplingStopAsync();
		
		// ���߃��N�G�X�g�I���҂�
		TP_WaitBusy( TP_REQUEST_COMMAND_FLAG_AUTO_OFF );
	
		// �G���[�I�����Ă��Ȃ����`�F�b�N
		result = TP_CheckError( TP_REQUEST_COMMAND_FLAG_AUTO_OFF );
		if( result != 0 )
		{
			check_num++;		// �G���[���J�E���g
		}

		// �G���[���A���Ă��āA�G���[��������TP_REQUEST_CHECK_MAX�ȉ��̊ԃ��[�v
	}while( (result != 0) && (check_num <= TP_REQUEST_CHECK_MAX) );


	// check_num ���T���傫���Ƃ���FALSE��]��
	if( check_num > TP_REQUEST_CHECK_MAX )
	{
#ifdef TOUCHPANEL_SYSTEM_OS_PRINTF_ON
		OS_Printf( "�I�����ߓ]�����s\n" );
#endif
		return TP_FIFO_ERR;
	}
	return TP_OK;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�T���v�����O���I������
 *
 *@param	none
 *
 *@retval	TP_OK�F����
 *@retval�@	TP_FIFO_ERR�F�]�����s
 *@retval	TP_ERR�F�]���ȊO�̎��s
 *
 */
//-----------------------------------------------------------------------------
u32 StopTP( void )
{
	u32 result;

	// �X���[�v��~��
	GF_ASSERT( TPWork.TouchPanelExStop == FALSE );
	
	result = stopSampling();
	if( result == TP_OK ){
		// �i�[���Ă������f�[�^�j��
		setStartBufferingParam( TP_SAMP_NONE, 0, NULL, 0, 0, 0 );
	}
	return result;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�T���v�����O�����Ǘ����A���̏�Ԃ�Ԃ�	
 *
 *@param	pData�F���̃t���[���̏��(init�Ŏw�肵���T���v�����O�񐔕��̏��)
 *@param	type�F�T���v�����O��ʂ̔ԍ�
 *@param	comp_num�F�o�b�t�@�Ɋi�[����Ƃ��ɁAcomp_num�ʂ̂�����������i�[����
 *
 *@return	u32�F�T���v�����O��ʂɂ��ω�
					type�FTP_BUFFERING		�T���v�����O���ꂽ�o�b�t�@�T�C�Y
					type�FTP_NO_LOOP		�T���v�����O���ꂽ�o�b�t�@�T�C�Y
											�o�b�t�@����t�ɂȂ����Ƃ� TP_END_BUFF
					type�FTP_NO_BUFF		TP_OK

					type�FTP_SAMP_NOT_START	�T���v�����O�J�n����Ă��܂���
 */
//-----------------------------------------------------------------------------
u32 MainTP( TP_ONE_DATA* pData, u32 type, u32 comp_num )
{
	u32 ret = TP_SAMP_NOT_START;	// �߂�l
	u32 last_idx;					// �Ō�ɃT���v�����O���ꂽ�ʒu

	// �X���[�v��~��
	GF_ASSERT( TPWork.TouchPanelExStop == FALSE );

	// �T���v�����O����Ă��邩�`�F�b�N
	if( TPWork.TouchPanelSampFlag != TP_SAMP_NONE ){

		// �Ō�ɃT���v�����O�����ʒu���擾
		last_idx  = TP_GetLatestIndexInAuto();
		
		// ��ʍ��W�ɕύX
		ChangeTPDataBuff( TPWork.TouchPanelOneSync, TP_ONE_SYNC_BUFF );

		// ���̃t���[���̏����擾
		if( pData != NULL ){
			getThisSyncData( pData, last_idx );
		}
		
		// type�̃o�b�t�@�����O�܂��͍��̃t���[�������擾��
		// �f�[�^���Z�b�g���ĕԂ�
		// �܂��o�b�t�@�����O�����Init����Ă��邩�`�F�b�N
		if( TPWork.TouchPanelSampFlag == TP_BUFFERING ){
			ret = modeBuff( type, last_idx, comp_num );	
		}else{
			// ���̑��̂Ƃ���TP_OK��Ԃ�
			ret = TP_OK;
		}
	}else{
#ifdef TOUCHPANEL_SYSTEM_OS_PRINTF_ON
	
		OS_Printf( "MainTP�֐� warning�F�T���v�����O�J�n����Ă��܂���\n" );
#endif
	}

	return ret;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	���̍��W����ʍ��W�ɂ��ĕԂ�
 *
 *@param	pData�F�ύX����^�b�`�p�l���f�[�^
 *
 *@return	�ύX��̃f�[�^
 *
 */
//-----------------------------------------------------------------------------
TPData ChangeTPData( TPData* pData )
{
	TPData sample;		// �擾�p

	// �X���[�v��~��
	GF_ASSERT( TPWork.TouchPanelExStop == FALSE );
	
	// ���̃^�b�`�p�l���l�����ʍ��W�ɕϊ����ĕԂ�
	TP_GetCalibratedPoint( &sample, pData );

	return sample;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	���̍��W����ʍ��W�ɂ��ĕԂ�(TPData�z��p)
 *
 *@param	pData�F�ύX����^�b�`�p�l���f�[�^�z��
 *@param	size�F�z��T�C�Y
 *
 *@return	none
 *
 */
//-----------------------------------------------------------------------------
void ChangeTPDataBuff( TPData* pData, u32 size )
{	
	int i;		// ���[�v�p
	TPData sample;

	// ���̃^�b�`�p�l���l�����ʍ��W�ɕϊ����ĕԂ�
	for( i = 0; i < size; i++ ){
		TP_GetCalibratedPoint( &sample, &(pData[ i ]) );
		pData[ i ] = sample;
	}
}


//----------------------------------------------------------------------------
/**
 *	@brief	�X���[�v�����O�̒�~�@
 */
//-----------------------------------------------------------------------------
void ReStartTP_Sleep( void )
{
	u32 result;
	
	// ��~�����`�F�b�N
	if( TPWork.TouchPanelExStop == FALSE ){
		return ;
	}
	// �T���v�����O�����`�F�b�N
	if( TPWork.TouchPanelSampFlag == TP_SAMP_NONE ){
		return ;
	}

	// �T���v�����O���J�n������
	result = startSampling( TPWork.TouchPanelSync / 2 );	// /2��30�V���N�̂���
	GF_ASSERT( result == TP_OK );

	TPWork.TouchPanelExStop = FALSE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�X���[�v�����O�̕��A
 */
//-----------------------------------------------------------------------------
void StopTP_Sleep( void )
{
	u32 result;
	// ���łɒ�~�����`�F�b�N
	if( TPWork.TouchPanelExStop == TRUE ){
		return ;
	}
	// �T���v�����O�����`�F�b�N
	if( TPWork.TouchPanelSampFlag == TP_SAMP_NONE ){
		return ;
	}

	// �T���v�����O���~������
	result = stopSampling();
	GF_ASSERT( result == TP_OK );

	TPWork.TouchPanelExStop = TRUE;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�I�[�g�T���v�����O�J�n���߂�]��
 *
 *@param	sync�F�P�t���[���̃T���v�����O��
 *
 *@return	TP_OK�F����
 *@return�@	TP_FIFO_ERR�F�]�����s
 *
 */
//-----------------------------------------------------------------------------
static u32 startSampling( u32 sync )
{
	int	check_num = 0;
	u32	result;


	// �J�n���߂��G���[���A���Ă���ԑ��葱����
	// �iFIFO��ARM7�ɖ��߂𑗂��Ă��邽�߁A���������K�v������j
	do
	{
		// �J�n���߂𑗂�
		TP_RequestAutoSamplingStartAsync( 
				0,			// �x�[�XV�J�E���g
				sync,		// �P�t���[���ɉ���T���v�����O���邩
				TPWork.TouchPanelOneSync,				// �T���v�����O�f�[�^�i�[�p�o�b�t�@
				TP_ONE_SYNC_BUFF );		// �o�b�t�@�T�C�Y
		
		// ���߃��N�G�X�g�I���҂�
		TP_WaitBusy( TP_REQUEST_COMMAND_FLAG_AUTO_ON );

		// �G���[�I�����Ă��Ȃ����`�F�b�N
		result = TP_CheckError( TP_REQUEST_COMMAND_FLAG_AUTO_ON );
		if( result != 0 )
		{
			check_num++;		// �G���[���J�E���g
		}

		// �G���[���A���Ă��āA�G���[��������TP_REQUEST_CHECK_MAX�ȉ��̊ԃ��[�v
	}while( (result != 0) && (check_num <= TP_REQUEST_CHECK_MAX) );


	// check_num ���T���傫���Ƃ���FALSE��]��
	if( check_num > TP_REQUEST_CHECK_MAX )
	{
#ifdef TOUCHPANEL_SYSTEM_OS_PRINTF_ON
		OS_Printf( "�X�^�[�g���ߓ]�����s\n" );
#endif
		return TP_FIFO_ERR;
	}

	return TP_OK;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�T���v�����O�����Ǘ����A���̏�Ԃ�Ԃ�
 *			�o�b�t�@�����O���[�h
 *
 *@param	type�F�T���v�����O��ʂ̔ԍ�
 *@param	last_idx�F���X�g�C���f�b�N�X
 *@param	comp_num�F�o�b�t�@�Ɋi�[����Ƃ��ɁAcomp_num�ʂ̂�����������i�[����(���k���[�h���̂�)
 *
 *@return	�T���v�����O��ʂɂ��ω�
					TP_BUFFERING---�T���v�����O���ꂽ�o�b�t�@�T�C�Y
					TP_NO_LOOP---�T���v�����O���ꂽ�o�b�t�@�T�C�Y
								 �o�b�t�@����t�ɂȂ����Ƃ� TP_END_BUFF
					TP_NO_BUFF---TP_OK
 *
 */
//-----------------------------------------------------------------------------
static u32 modeBuff( u32 type, u32 last_idx, u32 comp_num )
{		
	u32 ret;		// �߂�l
	
	
	//
	// type�̃��[�h�Ńo�b�t�@�����O
	switch( type ){
	case TP_BUFFERING:
	case TP_NO_LOOP:
		ret = mainBuffComp( type, last_idx, comp_num );
		break;
		
	case TP_BUFFERING_JUST:	// ���̂܂܊i�[
	case TP_NO_LOOP_JUST:
		ret = mainBuffJust( type, last_idx );
		break;

	default:		// ���̑�
		ret = TP_OK;
		break;			// �Ȃɂ����Ȃ�
	}

	return ret;
}

// �ʏ�ň��k���[�h�ɕύX
// ���k�Ȃ��ł̃o�b�t�@�����O�͈��k�l�ɂO���w�肷��΂悢
#if 0
//----------------------------------------------------------------------------
/**
 *
 *@brief	�o�b�t�@�Ɉ��k�Ȃ��ŁA���W���i�[
 *
 *@param	last_idx�F�Ō�ɃT���v�����O�����ʒu
 *
 *@return	�o�b�t�@�Ɋi�[�����T�C�Y
 *
 */
//-----------------------------------------------------------------------------
u32 mainBuff( u32 last_idx )
{
	int i;				// ���[�v�p
	s16	samp_work;		// �T���v�����O��Ɨp

	//
	// �^�b�`�p�l���̃T���v�����O�����Ǘ����A���̏�Ԃ�Ԃ�
	//	
	// �^�b�`�p�l���o�b�t�@�Ƃ��̃t���[���̃T���v�����O�f�[�^
	// �Ɋi�[����
	for( i = 0; i < TouchPanelSync; i++ ){
		samp_work = last_idx - TouchPanelSync + i + 1;

		// 0�ȉ��̂Ƃ��͍ŏI�v�f���ɂ���
		if( samp_work < 0 ){
			samp_work += TP_ONE_SYNC_BUFF;
		}

		// �L���ȃf�[�^�̎��o�b�t�@�Ɋi�[
		if( (TouchPanelOneSync[ samp_work ].touch == TP_TOUCH_ON) &&
			(TouchPanelOneSync[ samp_work ].validity == TP_VALIDITY_VALID) ){
			// �T���v�����O�f�[�^�i�[
			pTouchPanelBuff[ TouchPanelNowBuffPoint ] = TouchPanelOneSync[ samp_work ];				
			TouchPanelNowBuffPoint = (TouchPanelNowBuffPoint + 1) % TouchPanelBuffSize;		// �o�b�t�@���������烋�[�v
		}
	}

	
	// �Ō�ɃT���v�����O���ꂽ�C���f�b�N�X��Ԃ�	
	return TouchPanelNowBuffPoint;
}

#endif

static  inline int TouchPanel_GetDiff( int n1, int n2 )
{
	int calc = (n1 >= n2) ? (n1 - n2) : (n2 - n1);
	return calc;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�o�b�t�@�Ɉ��k���āA���W���i�[
 *
 *@param	type		�o�b�t�@�����O�^�C�v
 *@param	last_idx	�Ō�ɃT���v�����O�����ʒu
 *@param	comp_num	�o�b�t�@�Ɋi�[����Ƃ��ɁAcomp_num�ʂ̂�����������i�[����
 *
 *@return	�o�b�t�@�Ɋi�[�����T�C�Y
 *
 */
//-----------------------------------------------------------------------------
static u32 mainBuffComp( u32 type, u32 last_idx, u32 comp_num )
{
	int i;				// ���[�v�p
	s32 dist_x;			// �����ǂ̂��炢���邩
	s32 dist_y;			// �����ǂ̂��炢���邩
	s16	samp_work;		// �T���v�����O��Ɨp

	//
	// �^�b�`�p�l���̃T���v�����O�����Ǘ����A���̏�Ԃ�Ԃ�
	//
	// �^�b�`�p�l���o�b�t�@�Ƃ��̃t���[���̃T���v�����O�f�[�^
	// �Ɋi�[����
	for( i = 0; i < TPWork.TouchPanelSync; i++ ){
		samp_work = last_idx - TPWork.TouchPanelSync + i + 1;

		// 0�ȉ��̂Ƃ��͍ŏI�v�f���ɂ���
		if( samp_work < 0 ){
			samp_work += TP_ONE_SYNC_BUFF;
		}

		// �L���ȃf�[�^�̎��o�b�t�@�Ɋi�[
		if( (TPWork.TouchPanelOneSync[ samp_work ].touch == TP_TOUCH_ON) &&
			(TPWork.TouchPanelOneSync[ samp_work ].validity == TP_VALIDITY_VALID) ){
			// �������߂�
			dist_x = TouchPanel_GetDiff(TPWork.pTouchPanelBuff[ TPWork.TouchPanelNowBuffPoint - 1 ].x, TPWork.TouchPanelOneSync[ samp_work ].x);
			dist_y = TouchPanel_GetDiff(TPWork.pTouchPanelBuff[ TPWork.TouchPanelNowBuffPoint - 1 ].y, TPWork.TouchPanelOneSync[ samp_work ].y);
			
			// ����comp_num�ȏォ�`�F�b�N
			if( (dist_x >= comp_num) ||
				(dist_y >= comp_num)){
					
				// �T���v�����O�f�[�^�i�[
				TPWork.pTouchPanelBuff[ TPWork.TouchPanelNowBuffPoint ] = TPWork.TouchPanelOneSync[ samp_work ];				
				TPWork.TouchPanelNowBuffPoint++;
				
				// �o�b�t�@�T�C�Y�I�[�o�[�`�F�b�N
				if(TPWork.TouchPanelNowBuffPoint >= TPWork.TouchPanelBuffSize){
					// �o�b�t�@�����[�v�����邩�`�F�b�N
					if(type == TP_BUFFERING){
						TPWork.TouchPanelNowBuffPoint %= TPWork.TouchPanelBuffSize;	// ���[�v������
					}else{
						return TP_END_BUFF;		// ���[�v�����Ȃ�
					}
				}
			}
		}
	}

	
	// �Ō�ɃT���v�����O���ꂽ�C���f�b�N�X��Ԃ�	
	return TPWork.TouchPanelNowBuffPoint;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�o�b�t�@�ɗL���f�[�^�A�^�b�`�̔���������Ɋi�[
 *
 *@param	type		�o�b�t�@�����O�^�C�v
 *@param	last_idx	�Ō�ɃT���v�����O�����ʒu
 *
 *@return	�o�b�t�@�Ɋi�[�����T�C�Y
 *
 */
//-----------------------------------------------------------------------------
static u32 mainBuffJust( u32 type, u32 last_idx )
{
	int i;				// ���[�v�p
	s16	samp_work;		// �T���v�����O��Ɨp

	//
	// �^�b�`�p�l���̃T���v�����O�����Ǘ����A���̏�Ԃ�Ԃ�
	//
	// �^�b�`�p�l���o�b�t�@�Ƃ��̃t���[���̃T���v�����O�f�[�^
	// �Ɋi�[����
	for( i = 0; i < TPWork.TouchPanelSync; i++ ){
		samp_work = last_idx - TPWork.TouchPanelSync + i + 1;

		// 0�ȉ��̂Ƃ��͍ŏI�v�f���ɂ���
		if( samp_work < 0 ){
			samp_work += TP_ONE_SYNC_BUFF;
		}

		// �T���v�����O�f�[�^�i�[
		TPWork.pTouchPanelBuff[ TPWork.TouchPanelNowBuffPoint ] = TPWork.TouchPanelOneSync[ samp_work ];
		TPWork.TouchPanelNowBuffPoint++;

		// �o�b�t�@�T�C�Y�I�[�o�[�`�F�b�N
		if(TPWork.TouchPanelNowBuffPoint >= TPWork.TouchPanelBuffSize){
			// �o�b�t�@�����[�v�����邩�`�F�b�N
			if(type == TP_BUFFERING_JUST){
				TPWork.TouchPanelNowBuffPoint %= TPWork.TouchPanelBuffSize;	// ���[�v������
			}else{
				return TP_END_BUFF;		// ���[�v�����Ȃ�
			}
		}
	}

	
	// �Ō�ɃT���v�����O���ꂽ�C���f�b�N�X��Ԃ�	
	return TPWork.TouchPanelNowBuffPoint;
}


// �o�b�t�@�����O�����̕����modeBuff()�݂̂ōs���悤�ɕύX
// ��t�ɂȂ邩�̃`�F�b�N��modeBuff()���ĂԑO�ɍ쐬���A
// �T���v�����O�͏I�����Ȃ��悤�ɕύX���܂�		05/03/29	tomoya
#if 0
//----------------------------------------------------------------------------
/**
 *
 *@brief	�o�b�t�@�����[�v���Ȃ��悤�Ƀo�b�t�@�Ɋi�[
 *
 *@param	type�F���k������
 *@param	last_idx�F�Ō�ɃT���v�����O�����ʒu
 *@param	comp_num�F�o�b�t�@�Ɋi�[����Ƃ��ɁAcomp_num�ʂ̂�����������i�[����(���k���[�h���̂�)
 *
 *@return	�o�b�t�@�Ɋi�[�����T�C�Y 
 *			�o�b�t�@����t�ɂȂ�A�X�g�b�v�������Ƃ��� TP_END_BUFF
 *
 */
//-----------------------------------------------------------------------------
u32 mainBuffNoLoop( u32 type, u32 last_idx, u32 comp_num )
{
	u32 last_buff;
	int	i;			// ���[�v�p
	
	//
	// �^�b�`�p�l���̃T���v�����O�����Ǘ����A���̏�Ԃ�Ԃ�
	// ���̊֐��̓o�b�t�@�����[�v���Ȃ��悤�ɊǗ����܂��B
	//
	// ���k���[�h�łȂ����`�F�b�N
	switch( type ){
	case TP_NO_LOOP:
		// ���k�Ȃ�
		last_buff = mainBuff( last_idx );
		break;
	
	case TP_NO_LOOP_COMP:
		// ���k����
		last_buff = mainBuffComp( last_idx, comp_num );
		break;

	case TP_NO_LOOP_JUST:
		// ���̂܂�
		last_buff = mainBuffJust( last_idx );
		break;

	default:
		last_buff = 0;
		break;
	}

	// �������̃t���[���ōő���傫���Ȃ�Ȃ�I��
	if( last_buff + TouchPanelSync >= TouchPanelBuffSize )
	{
		// �I���܂ōŏI�̒l������
		for( i = last_buff; i < TouchPanelBuffSize; i++ ){
			pTouchPanelBuff[ i ] = pTouchPanelBuff[ i - 1 ];
		}

		// �I��������K�v���Ȃ��̂ŏI���͂����Ȃ�
//		while( StopTP() != TRUE ) ;

		return TP_END_BUFF;
	}

	return last_buff;
}

#endif

//----------------------------------------------------------------------------
/**
 *
 *@brief	���̃V���N�̃T���v�����O�����擾
 *
 *@param	pData�F���̃V���N�̃f�[�^�ۑ��p�̈�̃|�C���^
 *@param	last_idx�F�Ō�ɃT���v�����O�����ʒu
 *
 *@return	none
 *
 */
//-----------------------------------------------------------------------------
static void getThisSyncData( TP_ONE_DATA* pData, u32 last_idx )
{
	int i;				// ���[�v�p
	s16	samp_work;		// �T���v�����O��Ɨp

	//
	// ������
	//
	pData->Size = 0;
	for( i = 0; i < TP_ONE_SYNC_DATAMAX; i++ ){
		pData->TPDataTbl[ i ].validity = TP_VALIDITY_VALID;
		pData->TPDataTbl[ i ].touch = TP_TOUCH_OFF;
		pData->TPDataTbl[ i ].x = 0;
		pData->TPDataTbl[ i ].y = 0;
	}
	
	//
	// �^�b�`�p�l���̃T���v�����O�����Ǘ����A���̏�Ԃ�Ԃ�
	//
	// �^�b�`�p�l���o�b�t�@�Ƃ��̃t���[���̃T���v�����O�f�[�^
	// �Ɋi�[����
	for( i = 0; i < TPWork.TouchPanelSync; i++ ){
		samp_work = last_idx - TPWork.TouchPanelSync + i + 1;

		// 0�ȉ��̂Ƃ��͍ŏI�v�f���ɂ���
		if( samp_work < 0 ){
			samp_work += TP_ONE_SYNC_BUFF;
		}

		//
		// �L�������f�[�^���`�F�b�N
		//
		if( TPWork.TouchPanelOneSync[ samp_work ].validity == TP_VALIDITY_VALID ){	
			// ���̃t���[���̃T���v�����O�����i�[
			pData->TPDataTbl[ pData->Size ]  = TPWork.TouchPanelOneSync[ samp_work ];
			pData->Size++;
		}
	}
}

//
/// �^�b�`�p�l���̊G�̏��֌W�֐�
//
//----------------------------------------------------------------------------
/**
 *
 *@brief	�^�b�`�p�l����񂩂�G�̏����쐬����
 *
 *@param	u32 type�F�^�C�v
 *@param	TPData* pBuff�F�^�b�`�p�l�����̃o�b�t�@
 *@param	u32 size�F�o�b�t�@�̗v�f��
 *@param	u16 check_num�F	�^�b�`�p�l���̓_�������炷�Ƃ��̊p�x
 *							�i����������Ɛ��x�������A�f�[�^�������Ȃ�j
 *@param	u32 dist�F�I�_�Ǝn�_���Ȃ���Ƃ��̏I�_�Ǝn�_�̒����̋��E��
					�F�O�Ȃ���Ɛ����Ȃ��Ȃ�
					�F�R�Q�O�Ȃ���Ɛ����΂ɂȂ���
 *@param	BOOL* p_cross�F�G�̏��͌�_�ŕ��Ă���̂�
 *@param	heap	�g�p����q�[�v
 *
 *@return	TP_PICTURE_DATA* �^�F�쐬�����G�̏��
 *		********��_�ŕ��Ă��Ȃ��Ă��f�[�^�͋A���Ă���̂ŁA
 *				���̊֐���ǂ񂾂�K���߂�l�̃f�[�^��j������
 *				�K�v������܂��B**********
 *		
 *		
 *		���_�����P�`�Q�̃T�C�Y�̎��͕��Ă��Ȃ��G�̃f�[�^��Ԃ��܂��B
 *
 */
//-----------------------------------------------------------------------------
TP_PICTURE_DATA* MakeTPPictureData( u32 type, TPData* pBuff, u32 size, u16 check_num, u32 dist, BOOL* p_cross, int heap )
{
	int i;						// ���[�v�p
	u32 count;					// �K�v�Ȓ��_�ƃx�N�g���f�[�^��
	Vec2DS32* p_work;			// �f�[�^�쐬�p�̒��_�ƃx�N�g���̃f�[�^
	TP_PICTURE_DATA* p_ret;		// �߂�l�ŕԂ��G�f�[�^
	u8	cross_flag = 0;			// �G�̃f�[�^��������
	
	//
	/// �^�b�`�p�l���̏�񂩂�G�̏����쐬����
	/// �G�̏��Ƃ͒��_�Ǝ��̓_�܂ł̃x�N�g���ł��B
	/// ���O����Ɏg�p���܂��B
	//
	// ���_�x�N�g���f�[�^�쐬�p�̈���m��(��Ɨp�ŕK�v�ő�l���m��)
	p_work = sys_AllocMemory( heap, sizeof(Vec2DS32) * (size + 1) );		// �n�_�ƏI�_���Ȃ��\��������̂Ł{�P
	

	//
	// �}�`�f�[�^�̒��_��������
	//
	count = 0;

	//
	// �G�̏��f�[�^���쐬
	//
	if( size > 3 ){	
		
		// �S�ȏ�̂Ƃ��͒��_�����炷
		count = makePointData( pBuff, size, check_num, p_work );
	}else{
		
		// �R�ȉ��̎��͒��_�����炳�����ɂ��̂܂ܓ����
		for( i = 0; i < size; i++ ){
			p_work[ i ].x = pBuff[ i ].x;
			p_work[ i ].y = pBuff[ i ].y;
			count++;
		}
	}


	// p_cross�i���Ă��邩�j����Ă��Ȃ��iFALSE�j��
	// ������
	if( p_cross != NULL ){
		*p_cross = FALSE;
	}
	
	//
	// ���_�����R�ȉ��̎��͌�_�͂��肦�Ȃ�
	//
	if( count > 3 ){
		//
		// ��_���P���[�h���`�F�b�N
		//
		if( (type == TP_MAKE_PICT_ONE_FAST) || 
			(type == TP_MAKE_PICT_ONE_END)){
			if( crossEndPict( p_work, &count, type ) == 1 ){
				// �����f�[�^�ɂȂ���
				if( p_cross != NULL ){
					*p_cross = TRUE;
				}
				// ����
				cross_flag = 1;
			}
		}
	}

	// ���ĂȂ����`�F�b�N
	if( cross_flag == 0 ){
		//
		// ���_�����Q�ȉ��̎��͒����Ȃ̂ŏI�_�Ɛ擪���Ȃ���K�v���Ȃ�
		//
		if( count > 2 ){
	
			//
			// �I�_�Ɛ擪���Ȃ��邩�`�F�b�N
			//
			if( crossToPict( pBuff[ 0 ], &p_work[ count - 1 ], &p_work[ count ], dist ) == 1 ){
				count++;		// �f�[�^����ꂽ���J�E���g

				// �����f�[�^�ɂȂ���
				if( p_cross != NULL ){
					*p_cross = TRUE;
				}
			}
		}
	}

		
		
	//
	// �쐬�������_�ƃx�N�g���f�[�^��TP_PICTURE_DATA�f�[�^�ɃR�s�[
	//
	p_ret				= sys_AllocMemory( heap, sizeof(TP_PICTURE_DATA) );
	p_ret->pPointData	= sys_AllocMemory( heap, sizeof(Vec2DS32) * count );
	p_ret->Size			= count;



	// �R�s�[
	for( i = 0; i < count; i++ )
	{
		p_ret->pPointData[ i ] = p_work[ i ];

#if 0
		// �R�s�[���Ȃ���`��(�f�o�b�N�p)
		if( i > 0 ){
			drawVect( &p_ret->pPointData[ i - 1 ], &p_ret->pPointData[ i ] );
		}

		DrawTPPaste();
#endif
	}


	// ��Ɨp�̈��j��
	sys_FreeMemoryEz( p_work );

	return p_ret;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�I�_�Ǝn�_���q����
 *
 *@param	TPData s_TPData�F�n�_�̃f�[�^
 *@param	Vec2DS32* p_check�F�I�_�̃|�C���^
 *@param	Vec2DS32* p_in�F�i�[����ʒu�̃|�C���^
 *@param	u32 dist�F����Ă��Ă悢����
 *
 *@return	u32�^�F�Ȃ������@�P�F�q����
 *
 */
//-----------------------------------------------------------------------------
static u32	crossToPict( TPData s_TPData, Vec2DS32* p_check, Vec2DS32* p_in, u32 dist )
{
	//
	// �I�_�Ɛ擪���Ȃ��邩�`�F�b�N
	//
	if( GetVectorDistance( s_TPData.x, s_TPData.y,
				p_check->x, p_check->y ) <= dist ){
		// �擪�Ƃ�������
		// �^�b�`�p�l���̏��̗L���ȍŏ��̃f�[�^�ƗL���ȍŌ�̃f�[�^�̃x�N�g�����Ō�ɃZ�b�g����
		//
		p_in->x = s_TPData.x;		// �x�N�g�����W
		p_in->y = s_TPData.y;		// �x�N�g�����W

		return 1;
	}

	return 0;
}


//----------------------------------------------------------------------------
/**
 *
 *@brief	p_work�̃f�[�^����_�܂ł̃f�[�^�ɂ���
 *
 *@param	Vec2DS32* p_work�F�G�̃f�[�^
 *@param	u32* p_size�F���̃f�[�^
 *@param	u8 flag�F��ԍŏ��̌�_�̃f�[�^�ɂ��邩�A�Ō�̌�_�̃f�[�^�ɂ��邩
 *
 *@return	u32�^�F��_���������� �P�F������
 *
 */
//-----------------------------------------------------------------------------
static u32 crossEndPict( Vec2DS32* p_work, u32* p_size, u8 flag )
{
	int i, j;					// ���[�v�p
	int cross_i, cross_j;		// ��_�̂�����i��j�̒l
	Vec2DS32 cross_mat;			// ��_���W
	Vec2DS32 cross_tmp;			// ��_���W�ۑ��p
	u8	cross_num;				// ��_����������
	
	
	// �t���O��������
	cross_num = 0;

	//
	// �擪�̃x�N�g�������_�̈ʒu�����߂�
	//
	for( i = 0; i < *p_size - 1; i++ ){
		for( j = *p_size - 2; j >= 0; j-- ){
			// ����i��j���t�]�����������_�͂Ȃ�
			if( i + 1 >= j ){
				break;
			}
			
			if( CheckCrossMatrix( &p_work[ i ], &p_work[ i + 1 ],
								  &p_work[ j ], &p_work[ j + 1 ], 
								  &cross_mat) == 1 )
			{
				cross_i = i;			// ��_�̂�����i
				cross_j = j;			// ��_�̂�����j
				cross_num++;			// ��_���J�E���g
				cross_tmp = cross_mat;	// ��_�ۑ�
				break;
			}
		}

		// ��_�����������`�F�b�N
		if( (cross_num == 1) && (flag == TP_MAKE_PICT_ONE_FAST) ){
			break;
		}
	}

	//
	// ��_�����������`�F�b�N
	//
	if( cross_num > 0 ){
		//
		// i + 1�Ƃ�����_�̂������x�N�g���̐擪�̒��_
		// cross_mat�̒��g����_�̍��W
		// 
		// p_work��0�ƍŌ�̃f�[�^�̈ʒu�Ɍ�_���W���Z�b�g���Ai������j���傫�������폜
		p_work[ 0 ] = cross_tmp;
	
		*p_size = 1;
		// i�̏����O����j - (i +1)�ɂȂ�܂ł߂�
		for( i = cross_i + 1; i < cross_j; i++ ){
			p_work[ *p_size ] = p_work[ i ];
			(*p_size)++;		// �f�[�^���J�E���g
		}
		p_work[ *p_size ] = cross_tmp;
		(*p_size)++;		// �f�[�^���J�E���g
		return 1;
	}

	return 0;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�s�N�`���[�f�[�^��j������
 *
 *@param	TP_PICTURE_DATA* pPictData�F�G�̃f�[�^
 *
 *@return	�Ȃ�
 *
 */
//-----------------------------------------------------------------------------
void DestTPPictureData( TP_PICTURE_DATA* pPictData )
{
	//
	// �s�N�`���[�f�[�^��j��
	//
	if( pPictData != NULL ){
		sys_FreeMemoryEz( pPictData->pPointData );
		sys_FreeMemoryEz( pPictData );
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�^�b�`�p�l���f�[�^���璸�_�ƃx�N�g���̃f�[�^���쐬����
 *
 *@param	Vec2DS32* p_point�F���_�ƃx�N�g���f�[�^
 *
 *@return	u32�^�F�f�[�^��
 *
 */
//-----------------------------------------------------------------------------
static u32 makePointData( TPData* pBuff, u32 size, u16 check_num, Vec2DS32* p_work )
{
	int	i, j;			// ���[�v�p
	u32 count;			// �J�E���^
	u32	next;			// �`�F�b�N���鎟�̒��_

	
	//
	// �G�̏��쐬
	//
	count = 0;		// �J�E���^������
	i = 0;
	while( i <= size - 3 ){

		// ���̓_���Z�b�g	
		next = i + 1;
		// �`�F�b�N���x�N�g���Q�̗v�f����j�ɃZ�b�g
		j = next + 1;
		
		while( GetVectorAngle( 
				pBuff[ i ].x, pBuff[ i ].y,
				pBuff[ next ].x, pBuff[ next ].y,
				pBuff[ i ].x, pBuff[ i ].y,
				pBuff[ j ].x, pBuff[ j ].y ) <= check_num ){
			//
			// �G�̏��ɃZ�b�g����_��T��
			//
			j++;

			// �T�C�Y�ɂȂ�����I��
			if( j >= size )
			{
				break;		// �v�f�̃}�b�N�X�ɂȂ����甲����
			}
		}

		//
		// i�̓_���Z�b�g<F9>
		// j - 1�̓_�܂ł͊i�[���Ȃ��Ă悢�Bj - 1����`�F�b�N���Ă���
		//
		p_work[ count ].x = pBuff[ i ].x;		// �x�N�g���J�n���W
		p_work[ count ].y = pBuff[ i ].y;		// �x�N�g���J�n���W
		count++;

		// �I�_��(j - 1)�̒l��i�ɃZ�b�g
		i = j - 1;

	}
	
	// 
	// �_���c��Q�ȉ��ɂȂ��Ă��܂����̂Ń`�F�b�N�ł��Ȃ�����
	// �Ō��i����size -1�̒l�ɂȂ�܂ō��W������
	// 
	while( i < size ){
		p_work[ count ].x = pBuff[ i ].x;
		p_work[ count ].y = pBuff[ i ].y;
		count++;
		i++;
	}

	return count;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	���O����
 *
 *@param	TP_PICTURE_DATA* pData�F�G�̃f�[�^
 *@param	u16 x�F������W��
 *@param	u16 y�F������W����
 *
 *@return	u32�^�F�O�F�O�@�P�F��
 *
 */
//-----------------------------------------------------------------------------
u32 CheckTPPictureInOut( TP_PICTURE_DATA* pData, u16 x, u16 y )
{
	return CheckInOut( pData->pPointData, pData->Size, x, y );
}
