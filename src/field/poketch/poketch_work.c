//============================================================================================
/**
 * @file	poketch_work.c
 * @bfief	�|�P�b�`�i�t�B�[���h <-> ����� �؂�ւ�莞�ɂ��e��A�v���̏󋵂��L�����Ă����̈�j
 * @author	taya GAME FREAK inc.
 */
//============================================================================================
#include "common.h"
#include "field\poketch.h"
#include "poketch_prv.h"

enum {
	APPNUMBER_NULL = 0xffffffff,
	POKETCH_WORK_SIZE = 0x3000,
};

static int ReserveAppNumber = APPNUMBER_NULL;
static u8 PoketchWork[ POKETCH_WORK_SIZE ];



//------------------------------------------------------------------
/**
 * �A�v���؂�ւ����ɌĂ΂�A�\��A�v���ԍ������Z�b�g����
 */
//------------------------------------------------------------------
void PoketchWork_Reset( void )
{
	ReserveAppNumber = APPNUMBER_NULL;
}


//------------------------------------------------------------------
/**
 * �|�P�b�`���[�N�G���A�փA�v���̔C�Ӄf�[�^��ۑ�
 *
 * @param   appNumber	�A�v���i���o�[
 * @param   dat			�ۑ��f�[�^�|�C���^
 * @param   size		�f�[�^�T�C�Y
 *
 */
//------------------------------------------------------------------
void PoketchWork_Save( u32 appNumber, const void* dat, u32 size )
{
	if( size < POKETCH_WORK_SIZE )
	{
		MI_CpuCopy32( dat, PoketchWork, size );
		ReserveAppNumber = appNumber;
	}
	else
	{
		GF_ASSERT(0);
	}
}


//------------------------------------------------------------------
/**
 * �|�P�b�`���[�N�G���A���璼�O�ɃZ�[�u�����A�v���f�[�^���R�s�[
 *
 * @param   appNumber	�A�v���i���o�[�i��v���Ȃ���΃R�s�[���Ȃ��j
 * @param   buf			�f�[�^�R�s�[��o�b�t�@
 * @param   size		�f�[�^�T�C�Y
 *
 * @retval  BOOL		�������R�s�[���ꂽ��TRUE���Ԃ�
 */
//------------------------------------------------------------------
BOOL PoketchWork_Load( u32 appNumber, void* buf, u32 size )
{
	if( size < POKETCH_WORK_SIZE )
	{
		if( appNumber == ReserveAppNumber )
		{
			MI_CpuCopy32( PoketchWork, buf, size );
			return TRUE;
		}
	}
	else
	{
		GF_ASSERT(0);
	}
	return FALSE;
}


//------------------------------------------------------------------
/**
 * �|�P�b�`���[�N�G���A�փA�v���̔C�Ӄf�[�^��ۑ��i�����Łj
 *
 * @param   appNumber	�A�v���i���o�[
 * @param   dat			�ۑ��f�[�^�|�C���^
 * @param   size		�f�[�^�T�C�Y
 *
 */
//------------------------------------------------------------------
void PoketchWork_SaveFast( u32 appNumber, const void* dat, u32 size )
{
	if( size < POKETCH_WORK_SIZE )
	{
		MI_CpuCopyFast( dat, PoketchWork, size );
		ReserveAppNumber = appNumber;
	}
	else
	{
		GF_ASSERT(0);
	}
}
//------------------------------------------------------------------
/**
 * �|�P�b�`���[�N�G���A���璼�O�ɃZ�[�u�����A�v���f�[�^���R�s�[�i�����Łj
 *
 * @param   appNumber	�A�v���i���o�[�i��v���Ȃ���΃R�s�[���Ȃ��j
 * @param   buf			�f�[�^�R�s�[��o�b�t�@
 * @param   size		�f�[�^�T�C�Y
 *
 * @retval  BOOL		�������R�s�[���ꂽ��TRUE���Ԃ�
 */
//------------------------------------------------------------------
BOOL PoketchWork_LoadFast( u32 appNumber, void* buf, u32 size )
{
	if( size < POKETCH_WORK_SIZE )
	{
		if( appNumber == ReserveAppNumber )
		{
			MI_CpuCopyFast( PoketchWork, buf, size );
			return TRUE;
		}
	}
	else
	{
		GF_ASSERT(0);
	}
	return FALSE;
}
