//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		laster.c
 *	@brief		���X�^�[�V�X�e��
 *	@author		tomoya takahashi
 *	@data		2005.12.01
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

#include <string.h>
#include "system.h"
#include "assert.h"
#include "system/tcbman.h"

#define __LASTER_H_GLOBAL
#include "system/laster.h"

//-----------------------------------------------------------------------------
/**
 *					�R�[�f�B���O�K��
 *		���֐���
 *				�P�����ڂ͑啶������ȍ~�͏������ɂ���
 *		���ϐ���
 *				�E�ϐ�����
 *						const�ɂ� c_ ��t����
 *						static�ɂ� s_ ��t����
 *						�|�C���^�ɂ� p_ ��t����
 *						�S�č��킳��� csp_ �ƂȂ�
 *				�E�O���[�o���ϐ�
 *						�P�����ڂ͑啶��
 *				�E�֐����ϐ�
 *						�������Ɓh�Q�h�Ɛ������g�p���� �֐��̈���������Ɠ���
*/
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
/**
 *					�萔�錾
*/
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/**
 *					�\���̐錾
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	
//	���X�^�[�V�X�e���\����
//	
//=====================================
typedef struct _LASTER_SYS{
	// ���X�^�[�f�[�^�o�b�t�@
	void* laster_buff[2];

	// ���X�^�[�f�[�^�̏������ݗp�o�b�t�@�w��t���O
	u8	write_buff;	// �z��v�f�����w�肵�܂� (0 or 1)

	// �o�b�t�@�X�C�b�`�t���O
	u8	switch_flag;	
/* 	LASTER_SWITCH_ON,	// �o�b�t�@�X�C�b�`�L��
 	LASTER_SWITCH_OFF	// �o�b�t�@�X�C�b�`����*/
	u8 dummy[2];

} LASTER_SYS;

//-----------------------------------------------------------------------------
/**
 *					�v���g�^�C�v�錾
*/
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *
 *	@brief	���X�^�[�V�X�e��������
 *
 *	@param	heap	�g�p����q�[�v
 *	@param	p_buff1	�o�b�t�@�P
 *	@param	p_buff2	�o�b�t�@�Q
 *
 *	@return	�쐬�������X�^�[�V�X�e��
 *
 */
//-----------------------------------------------------------------------------
LASTER_SYS_PTR LASTER_Init( int heap, void* p_buff1, void* p_buff2 )
{
	LASTER_SYS_PTR p_laster;

	p_laster = sys_AllocMemory( heap, sizeof(LASTER_SYS) );
	memset( p_laster, 0, sizeof(LASTER_SYS) );

	// �X�C�b�`����ON
	p_laster->switch_flag = LASTER_SWITCH_ON;

	// �X�C�b�`�o�b�t�@�i�[
	p_laster->laster_buff[ 0 ] = p_buff1;
	p_laster->laster_buff[ 1 ] = p_buff2;

	return p_laster;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	���X�^�[�V�X�e���j��
 *
 *	@param	lster	�j�����郉�X�^�[�V�X�e��
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void LASTER_Delete( LASTER_SYS_PTR p_laster )
{
	GF_ASSERT( p_laster );

	sys_FreeMemoryEz( p_laster );
	p_laster = NULL;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�������ݗp���X�^�[�o�b�t�@���擾
 *
 *	@param	cp_laster	���X�^�[�X�X�e��
 *
 *	@return	�������ݗp���X�^�[�o�b�t�@
 *
 *
 */
//-----------------------------------------------------------------------------
void* LASTER_GetWriteBuff( CONST_LASTER_SYS_PTR cp_laster )
{
	GF_ASSERT( cp_laster );
	
	return cp_laster->laster_buff[ cp_laster->write_buff ];
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�Q�Ɨp���X�^�[�o�b�t�@���擾
 *
 *	@param	cp_laster	���X�^�[�V�X�e��
 *
 *	@return	�Q�Ɨp���X�^�[�o�b�t�@
 *
 *
 */
//-----------------------------------------------------------------------------
const void* LASTER_GetReadBuff( CONST_LASTER_SYS_PTR cp_laster )
{
	GF_ASSERT( cp_laster );
	
	return cp_laster->laster_buff[ cp_laster->write_buff ^ 1 ];
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�o�b�t�@�X�C�b�`�t���O��ݒ肵�܂��B
 *
 *	@param	p_laster	���X�^�[�V�X�e��
 *	@param	switch_flag	�X�C�b�`�t���O
 *
 *	@return	none
 *
 * switch_flag	
 *	LASTER_SWITCH_ON,	// �o�b�t�@�X�C�b�`�L��
 *	LASTER_SWITCH_OFF	// �o�b�t�@�X�C�b�`����
 *
 *	LASTERE_Init�֐����Ă񂾏�ԂŃo�b�t�@�X�C�b�`�͗L���ɂȂ��Ă��܂��B
 * 
 */
//-----------------------------------------------------------------------------
void LASTER_SwitchFlagSet( LASTER_SYS_PTR p_laster, u8 switch_flag )
{
	GF_ASSERT( p_laster );
	
	p_laster->switch_flag = switch_flag;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	���X�^�[�@V�u�����N�֐�
 *
 *	@param	p_laster	���X�^�[�V�X�e��
 *
 *	@return	none
 *
 * �o�b�t�@�X�C�b�`�t���O���L���̂Ƃ�
 *		�������ݗp�o�b�t�@���Q�Ɨp��
 *		�Q�Ɨp�o�b�t�@���������ݗp�Ɂ@�ύX���܂��B
 *
 *		�ύX��@�V�����������݂悤�ɂȂ����o�b�t�@���O�ŏ��������܂��B
 *
 */
//-----------------------------------------------------------------------------
void LASTER_VBlank( LASTER_SYS_PTR p_laster )
{
	if( p_laster == NULL ){
		return ;
	}
	
	// �o�b�t�@�X�C�b�`�L���`�F�b�N
	if( p_laster->switch_flag == LASTER_SWITCH_OFF ){
		return ;
	}

	// ���X�^�[�o�b�t�@�X�C�b�`
	p_laster->write_buff ^= 1;
}



//-----------------------------------------------------------------------------
/**
 *
 *		���X�^�[H�u�����NDMA�]���֐�
 * 
 */
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *
 *	@brief	���X�^�[�Ŏg�p����DMA���~����
 *
 *	@param	none
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void LASTER_DmaStop( void )
{
	MI_StopDma( LASTER_USE_DMA );
	MI_WaitDma( LASTER_USE_DMA );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	H�u�����NDMA�]���p�����[�^�ݒ�
 *
 *	@param	p_src		�]����
 *	@param	p_dest		�]����
 *	@param	szbyte		�]���T�C�Y	�i�P��̓]���œ]������T�C�Y�j
 *	@param	dma_type
 *
 *	@return	none
 *
 *	LASTER_DMA_TYPE16,	16bit�P��
 *	LASTER_DMA_TYPE32	32bit�P��
 *
 */
//-----------------------------------------------------------------------------
void LASTER_DmaSet( const void* p_src, void* p_dest, int szbyte, int dma_type )
{
	
	// �]���^�C�v�`�F�b�N
	if( dma_type == LASTER_DMA_TYPE32 ){
		MI_HBlankDmaCopy32( LASTER_USE_DMA, p_src, p_dest, szbyte );
	}else{
		MI_HBlankDmaCopy16( LASTER_USE_DMA, p_src, p_dest, szbyte );
	}
}


//-----------------------------------------------------------------------------
/**
 *		���X�^�[�X�N���[��
 *			DMA�]���g�p
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	
//	���X�^�[�X�N���[�����[�N
//	
//=====================================
typedef struct _LASTER_SCROLL{
	// ���X�^�[�o�b�t�@
	u32	buff1[ LASTER_SCROLL_BUFF_SIZE ];
	u32 buff2[ LASTER_SCROLL_BUFF_SIZE ];

	LASTER_SYS_PTR p_laster;	// ���X�^�[�V�X�e��
	TCB_PTR	p_tcb;				// tcb���[�N
	BOOL	end_flag;			// �I���t���O


	// �T�C���J�[�u�e�[�u��
	s16 sinTbl[ LASTER_SCROLL_BUFF_SIZE ];

	u8 start;	// �X�N���[�����f�J�nY���W
	u8 end;		// �X�N���[�����f�I��Y���W
	
	u32	addr;		// DMA�]����
	u32	init_num;	// ���[�N������������l
	
	s16 scr_now;	// �X���[�����݈ʒu
	s16 scr_sp;	// �X�N���[���X�s�[�h	����*100 ���ꂽ��

} LASTER_SCROLL;

// DMA�]��RAPPER
static void LASTER_ScrollDmaStop( void );
static void LASTER_ScrollDmaSet( CONST_LASTER_SCROLL_PTR cp_lstscr );


// ���X�^�[�p
static void LASTER_ScrollTcb( TCB_PTR tcb, void* work );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	���X�^�[�X�N���[���I�u�W�F����
 *
 *	@param	heap	�q�[�v
 *
 *	@return	�쐬�������X�^�[�X�N���[���I�u�W�F
 *
 *
 */
//-----------------------------------------------------------------------------
LASTER_SCROLL_PTR LASTER_ScrollInit( int heap )
{
	LASTER_SCROLL_PTR p_lstscr;

	// �I�u�W�F�N�g����
	p_lstscr = sys_AllocMemory( heap, sizeof(LASTER_SCROLL) );
	memset( p_lstscr, 0, sizeof(LASTER_SCROLL) );
	
	// ���X�^�[�V�X�e������
	p_lstscr->p_laster = LASTER_Init( heap, p_lstscr->buff1, p_lstscr->buff2 );

	return p_lstscr;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	���X�^�[�X�N���[���J�n
 *
 *	@param	start		���X�^�[�X�N���[��������J�n�����W
 *	@param	end			���X�^�[�X�N���[��������I�������W
 *	@param	add_r		sin�J�[�u�e�[�u���쐬���̊p�x�𑫂��Ă����l(0�`65535)
 *	@param	r_w			sin�J�[�u�̔��a
 *	@param	scr_sp		���X�^�[�X�N���[���X�s�[�h	����*100�����l	�}�C�i�X�L��
 *	@param	bg_no		���X�^�[��������BG�̔ԍ�
 *	@param	init_num	���[�N������������l
 *	@param	tsk_pri		�^�X�N�D�揇��
 *
 *	@return	none
 *
 * bg_no
 * 		LASTER_SCROLL_MBG0,
 *		LASTER_SCROLL_MBG1,
 *		LASTER_SCROLL_MBG2,
 *		LASTER_SCROLL_MBG3,
 *		LASTER_SCROLL_SBG0,
 *		LASTER_SCROLL_SBG1,
 *		LASTER_SCROLL_SBG2,
 *		LASTER_SCROLL_SBG3
 *
 */
//-----------------------------------------------------------------------------
void LASTER_ScrollStart( LASTER_SCROLL_PTR p_lstscr, u8 start, u8 end, u16 add_r, fx32 r_w, s16 scr_sp, u32 bg_no, u32 init_num, u32 tsk_pri )
{
	GF_ASSERT( p_lstscr );
	GF_ASSERT_MSG( p_lstscr->p_tcb == NULL, "tcb�o�^�ς݂ł�." );

	// ����p�����[�^�ݒ�
	p_lstscr->start		= start;
	p_lstscr->end		= end;
	p_lstscr->scr_now	= 0;
	p_lstscr->scr_sp	= scr_sp;
	p_lstscr->addr		= bg_no;
	p_lstscr->init_num	= init_num;

	// sin�J�[�u�쐬
	LASTER_ScrollMakeSinTbl( p_lstscr->sinTbl, LASTER_SCROLL_BUFF_SIZE, add_r, r_w );

	// tcb�o�^
	p_lstscr->p_tcb = TCB_Add( LASTER_ScrollTcb, p_lstscr, tsk_pri );	

	// ���[�N��������
	MI_CpuFill32( p_lstscr->buff1, p_lstscr->init_num, sizeof(u32) * LASTER_SCROLL_BUFF_SIZE );
	MI_CpuFill32( p_lstscr->buff2, p_lstscr->init_num, sizeof(u32) * LASTER_SCROLL_BUFF_SIZE );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	���X�^�[�X�N���[���I��
 *
 *	@param	p_lstscr	�I�������郉�X�^�[�X�N���[�����[�N
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void LASTER_ScrollEnd( LASTER_SCROLL_PTR p_lstscr )
{
	void* buff;
	
	GF_ASSERT( p_lstscr );
	
	if( p_lstscr->p_tcb ){
		// TCB�̔j��
		TCB_Delete( p_lstscr->p_tcb );
		p_lstscr->p_tcb = NULL;

		// ���ɊJ�n����Ƃ��̂��߂�
		// �������ݗp�o�b�t�@�̏�����
		buff = LASTER_GetWriteBuff( p_lstscr->p_laster );
		memset( buff, p_lstscr->init_num, sizeof(u32) * LASTER_SCROLL_BUFF_SIZE );
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	���X�^�[�X�N���[���j��
 *
 *	@param	p_lstscr	���X�^�[�X�N���[�����[�N
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void LASTER_ScrollDelete( LASTER_SCROLL_PTR p_lstscr )
{
	// �^�X�N�I��
	LASTER_ScrollEnd( p_lstscr );

	// DMA�I��
	LASTER_ScrollDmaStop();
	
	// ���X�^�[�V�X�e���j��
	LASTER_Delete( p_lstscr->p_laster );

	// �S�f�[�^�j��
	sys_FreeMemoryEz( p_lstscr );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�o�b�t�@�擾
 *
 *	@param	p_lstscr	���X�^�[�X�N���[�����[�N
 *
 *	@return	�o�b�t�@�|�C���^
 *
 *
 */
//-----------------------------------------------------------------------------
void* LASTER_GetScrollWriteBuff( LASTER_SCROLL_PTR p_lstscr )
{
	return LASTER_GetWriteBuff( p_lstscr->p_laster );
}
const void* LASTER_GetScrollReadBuff( LASTER_SCROLL_PTR p_lstscr )
{
	return LASTER_GetReadBuff( p_lstscr->p_laster );
}


//----------------------------------------------------------------------------
/**
 *
 *	@brief	���X�^�[�X�N���[��V�u�����N�֐�
 *
 *	@param	p_lstscr	���X�^�[�X�N���[�����[�N
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
//	�o�b�t�@�X�C�b�`
void LASTER_ScrollVBuffSwitch( LASTER_SCROLL_PTR p_lstscr )
{
	void* buff;
	
	if( p_lstscr == NULL ){
		return ;
	}
	
	// �^�X�N�������Ă���Ƃ�
	// �_�u���o�b�t�@�����O�̎��s
	if( p_lstscr->p_tcb ){
		// ���X�^�[�V�X�e��VBlank�֐����s
		LASTER_VBlank( p_lstscr->p_laster );

		// ���[�N��������
		buff = LASTER_GetWriteBuff( p_lstscr->p_laster );
		MI_CpuFill32( buff, p_lstscr->init_num, sizeof(u32) * LASTER_SCROLL_BUFF_SIZE );
	}
}

// DMA�ݒ�
void LASTER_ScrollVDma( LASTER_SCROLL_PTR p_lstscr )
{
	if( p_lstscr == NULL ){
		return ;
	}
	
	// �^�X�N�������Ă���Ƃ�
	// H�u�����NDMA�̐ݒ�
	if( p_lstscr->p_tcb ){

		// DMA��~
		LASTER_ScrollDmaStop();
		// DMA�]���ݒ�
		LASTER_ScrollDmaSet( p_lstscr );
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	���X�^�[�X�N���[���T�C���e�[�u���쐬
 *
 *	@param	sinTbl	�T�C���e�[�u��
 *	@param	num		�z��v�f��	u16 buff[ 10 ]; �Ȃ�10���w��
 *	@param	add_r	��]�p�̑����l
 *	@param	r_w		���a��
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void LASTER_ScrollMakeSinTbl( s16* sinTbl, u32 num, u16 add_r, fx32 r_w )
{
	int i;	// ���[�v�p
	u16 rota;

	// �o�b�t�@�T�C�Y��add_r���i�߂�sin�J�[�u��
	// �o�b�t�@�Ɋi�[
	rota = 0;
	for( i=0; i<num; i++ ){
		sinTbl[ i ] = FX_Mul( FX_SinIdx( rota ), r_w) >> FX32_SHIFT;
		rota += add_r;	// 0�`65535�����[�v
	}
}


//----------------------------------------------------------------------------
/**
 *
 *	@brief	�X�N���[���v�ZTCB
 *
 *	@param	tcb		tcb���[�N
 *	@param	work	���[�N
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void LASTER_ScrollTcb( TCB_PTR tcb, void* work )
{
	LASTER_SCROLL_PTR p_lstscr = work;
	int i;			// ���[�v�p
	u32* w_buff;	// �������ݗp�o�b�t�@
	u8 write;		// �������ݗv�f��
	s16	mat_x;		// x���W
	u16 mat_y;		// y���W

	// �������ݗp�o�b�t�@�擾
	w_buff = LASTER_GetWriteBuff( p_lstscr->p_laster );
	
	// �o�b�t�@�Ƀf�[�^��ݒ�
	write = p_lstscr->scr_now / 100;
	for( i=p_lstscr->start; i<=p_lstscr->end; i++ ){
		// ���̒l�擾
		mat_x = w_buff[ i ] & 0xffff;
		mat_y = w_buff[ i ] >> 16;
		
		// �T�C���J�[�u���f
		mat_x += p_lstscr->sinTbl[ write ];
		
		// �l�ݒ�
		w_buff[ i ] = (mat_y << 16) | (mat_x & 0xffff);
		
		write = (write + 1) % LASTER_SCROLL_BUFF_SIZE;
	}

	// �X�N���[���ʒu�v�Z
	p_lstscr->scr_now += p_lstscr->scr_sp;
	if( p_lstscr->scr_now >= (LASTER_SCROLL_BUFF_SIZE * 100) ){
		p_lstscr->scr_now %= (LASTER_SCROLL_BUFF_SIZE * 100);
	}else{
		if( p_lstscr->scr_now < 0 ){
			p_lstscr->scr_now += (LASTER_SCROLL_BUFF_SIZE * 100);
		}
	}
}

// DMA�]��RAPPER
//----------------------------------------------------------------------------
/**
 *
 *	@brief	DMA�]���I��
 *
 *	@param	none
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void LASTER_ScrollDmaStop( void )
{
	LASTER_DmaStop();
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	H�u�����NDMA�]���ݒ�
 *
 *	@param	cp_lstscr	���X�^�[�X�N���[�����[�N
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void LASTER_ScrollDmaSet( CONST_LASTER_SCROLL_PTR cp_lstscr )
{
	const void* buff;

	GF_ASSERT( cp_lstscr );
	
	// �Q�Ɨp�o�b�t�@�擾
	buff = LASTER_GetReadBuff( cp_lstscr->p_laster );

	// �t���b�V�������W
	DC_FlushRange( buff, sizeof(u32) * LASTER_SCROLL_BUFF_SIZE );
	
	// HBlankDMA�]���ɐݒ�
	LASTER_DmaSet( buff, (void*)cp_lstscr->addr, sizeof(u32), LASTER_DMA_TYPE32 );
}
