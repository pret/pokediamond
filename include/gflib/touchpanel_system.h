/*[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
 *
 *	@file		touchpanel_system.h
 *	@brief		�^�b�`�p�l���V�X�e���̃w�b�_
 *	@author		tomoya takahashi
 *	@data		2004.12.03
 *				2006.02.14	30�t���[���g�p�ɕύX
 *
 ]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]*/


#ifndef __TOUCHPANEL_SYSTEM_H__
#define	__TOUCHPANEL_SYSTEM_H__

#undef	GLOBAL
#ifdef	__TOUCHPANEL_SYSTEM_H_GLOBAL
#define	GLOBAL	/* */
#else
#define	GLOBAL	extern
#endif


/*-----------------------------------------------------------------------------
 *					�萔�錾
 ----------------------------------------------------------------------------*/
#define TP_REQUEST_CHECK_MAX		5		// ���߂��o���Ď��s������G���[��Ԃ���
											
#define		TP_ONE_SYNC_BUFF (9)			// �P�V���N�ɃT���v�����O�ł���ő�̐���
											// �T���v�����O����̂ɕK�v�ȃo�b�t�@�T�C�Y
											
#define		TP_ONE_SYNC_DATAMAX	(8)			// �P�V���N�Ɏ擾�ł���f�[�^�ő吔



//-------------------------------------
/// �G���[�̗�
enum
{
	TP_END_BUFF = 0xffffffff,	// �T���v�����O�p�o�b�t�@����t
	TP_ERR = 0,					// ARM7�]���ȊO�̃G���[
	TP_OK,						// Touch�p�l���֐���OK
	TP_FIFO_ERR,				// ARM7��FIFO���ߓ]���G���[	
	TP_SAMP_NOT_START			// �T���v�����O�J�n����Ă��܂���
};

//-------------------------------------
/// �T���v�����O��ʗ�
enum{
	TP_SAMP_NONE,			// �T���v�����O���Ă��Ȃ�
	TP_BUFFERING,			// �o�b�t�@�i�[���[�h
	TP_NO_BUFF,				// �i�[�����Ȃ����[�h
	TP_NO_LOOP,				// �o�b�t�@�����[�v�����Ȃ�
	TP_BUFFERING_JUST,		// ���̂܂܃o�b�t�@�����O����(�����Ă��Ă��o�b�t�@�����O)
	TP_NO_LOOP_JUST,		// ���̂܂܃o�b�t�@�����O����(�����Ă��Ă��o�b�t�@�����O)
							// ���[�v�����Ȃ�
};
// ���̃o�[�W�����ł�TP_BUFFERING_JUST,	TP_NO_LOOP_JUST���g�p�����f�[�^�œ��O����͂ł��Ȃ�


//-------------------------------------
/// �G�̃f�[�^�쐬�t���O
enum{
	TP_MAKE_PICT_NORMAL,		// �͂܂ꂽ�G���A�����������Ă��悢
	TP_MAKE_PICT_ONE_FAST,		// �]�v�ȕ������Ȃ���
								// ��ԍŏ��ɂ�������_������Ă���
								// �}�`�̃f�[�^���쐬

	TP_MAKE_PICT_ONE_END		// �������̐悩�猩�Ĉ�ԍŌ�ɂ�������_
								// ������Ă���}�`�̃f�[�^���쐬
								// ���̃t���O���Z�b�g����ƕK���}�`�͂P�ɂȂ�
};

/*-----------------------------------------------------------------------------
 *					�\���̐錾
 ----------------------------------------------------------------------------*/
//-------------------------------------
/// �^�b�`�p�l���̓��O����p�}�`�f�[�^�\����
typedef struct
{
	u32	Size;					// TP_VECTOR_DATA�̔z��̗v�f��
	Vec2DS32*	pPointData;		// ���_�f�[�^�̔z��
} TP_PICTURE_DATA;

//-------------------------------------
/// �P�t���[���̃^�b�`���i�[�\����
typedef struct
{
	u16		Size;			// ���̃t���[���̗L���T���v�����O��
	TPData	TPDataTbl[ TP_ONE_SYNC_DATAMAX ];	// ���̃t���[���̃T���v�����O�f�[�^
} TP_ONE_DATA;


/*-----------------------------------------------------------------------------
 *					�v���g�^�C�v�錾
 ----------------------------------------------------------------------------*/
//----------------------------------------------------------------------------
/**
 *
 *@brief	�^�b�`�p�l�����g�p���鏀�����s���܂�
 *
 *@param	none
 *
 *@return	none
 */
//-----------------------------------------------------------------------------
GLOBAL void InitTPSystem( void );

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
GLOBAL u32 InitTP( TPData* p_buff, u32 size, u32 sync );

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
GLOBAL u32 InitTPNoBuff( u32 sync );

//----------------------------------------------------------------------------
/**
 *
 *@brief	�T���v�����O�����Ǘ����A���̏�Ԃ�Ԃ�	
 *
 *@param	pData�F���̃t���[���̏��(init�Ŏw�肵���T���v�����O�񐔕��̏��)
 *@param	type�F�T���v�����O��ʂ̔ԍ�
 *@param	comp_num�F�o�b�t�@�Ɋi�[����Ƃ��ɁAcomp_num�ʂ̂�����������i�[����(���k���[�h���̂�)
 *
 *@return	u32�F�T���v�����O��ʂɂ��ω�
					type�FTP_BUFFERING		�T���v�����O���ꂽ�o�b�t�@�T�C�Y
					type�FTP_NO_LOOP		�T���v�����O���ꂽ�o�b�t�@�T�C�Y
											�o�b�t�@����t�ɂȂ����Ƃ� TP_END_BUFF
					type�FTP_NO_BUFF		TP_OK

					type�FTP_SAMP_NOT_START	�T���v�����O�J�n����Ă��܂���
 */
//-----------------------------------------------------------------------------
GLOBAL u32 MainTP( TP_ONE_DATA* pData, u32 type, u32 comp_num );
															
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
 */
//-----------------------------------------------------------------------------
GLOBAL u32 StopTP( void );


//----------------------------------------------------------------------------
/**
 *	@brief	�X���[�v�����O�̒�~�@���A����
 */
//-----------------------------------------------------------------------------
GLOBAL void ReStartTP_Sleep( void );
GLOBAL void StopTP_Sleep( void );



// ���̍��W����ʍ��W�ɕς���֐��iMainTP���g�p���Ă���Ƃ��͎g���K�v�͂���܂���j
GLOBAL TPData ChangeTPData( TPData* pData );					// �L�����u���[�V�����l���g�p
																// ���č��W����ʍ��W�ɂ���TPData���擾
GLOBAL void ChangeTPDataBuff( TPData* pData, u32 size );		// �L�����u���[�V�����l���g�p
																// ���č��W����ʍ��W�ɂ���TPData���擾

/// �^�b�`�p�l������n���Ă��̊G�̏����g�����O����Ȃǂ��s���V�X�e��
// �G�̏����쐬
GLOBAL TP_PICTURE_DATA* MakeTPPictureData( u32 type, TPData* pBuff, u32 size, u16 check_num, u32 dist, BOOL* p_cross, int heap );
// ���O�`�F�b�N������
GLOBAL u32 CheckTPPictureInOut( TP_PICTURE_DATA* pData, u16 x, u16 y );
// �G�̏���j��
GLOBAL void DestTPPictureData( TP_PICTURE_DATA* pPictData );

/*-----------------------------------------------------------------------------
 *					�O���[�o���ϐ��錾
 ----------------------------------------------------------------------------*/
#undef	GLOBAL
#endif		//__TOUCHPANEL_SYSTEM_H__

