//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		laster.h
 *	@brief		���X�^�[�V�X�e��
 *	@author		tomoya takahashi
 *	@data		2005.12.01
 *
 * LABEL	LABEL_LASTER_SYS		���X�^�[�V�X�e��
 * LABEL	LABEL_LASTER_RAP_FUNC	���X�^�[�V�X�e�����g�p�����ėp�֐��S
 * 
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
#ifndef __LASTER_H__
#define __LASTER_H__

#undef GLOBAL
#ifdef	__LASTER_H_GLOBAL
#define	GLOBAL	/* */
#else
#define	GLOBAL	extern
#endif

//-----------------------------------------------------------------------------
/**
 *
 * ���X�^�[�V�X�e������		[ LABEL_LASTER_SYS ]
 *	���X�^�[�V�X�e���\��
 *		�������ݗp�o�b�t�@�A�Q�Ɨp�o�b�t�@�̂Q���������֐��Őݒ肵�܂��B
 *		�P���������ݗp�o�b�t�@�̎��A��������͎Q�Ɨp�o�b�t�@�ɂȂ�܂��B
 *
 *		�������݂��I�������A�������݃o�b�t�@���Q�Ɨp�ɎQ�Ɨp���������ݗp��
 *		�X�C�b�`���܂��B�i�_�u���o�b�t�@�����j
 *
 *		�������֐��Őݒ肵���Q�̃o�b�t�@�͂ǂ��炪�A�������ݗp���Q�Ɨp��
 *		�g�p���郆�[�U�[����́A�킩��܂���B
 *		�o�b�t�@���g�p����Ƃ��͕K�����֐����g�p���Ĕz��̐擪�|�C���^��
 *		�擾���Ă��������B
 *
 *		���擾�֐�
 *			void* LASTER_GetWriteBuff( CONST_LASTER_SYS_PTR cp_laster );
 *			const void* LASTER_GetReadBuff( CONST_LASTER_SYS_PTR cp_laster );
 *			
 */
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/**
 *					�萔�錾
*/
//-----------------------------------------------------------------------------

//-------------------------------------
//	
//	�X�C�b�`�t���O
//	
//=====================================
enum{
	LASTER_SWITCH_OFF,	// �o�b�t�@�X�C�b�`����
	LASTER_SWITCH_ON,	// �o�b�t�@�X�C�b�`�L��
};

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
typedef struct _LASTER_SYS * LASTER_SYS_PTR;
typedef const struct _LASTER_SYS * CONST_LASTER_SYS_PTR;


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
GLOBAL LASTER_SYS_PTR LASTER_Init( int heap, void* p_buff1, void* p_buff2 );

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
GLOBAL void LASTER_Delete( LASTER_SYS_PTR p_laster );

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
GLOBAL void* LASTER_GetWriteBuff( CONST_LASTER_SYS_PTR cp_laster );

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
GLOBAL const void* LASTER_GetReadBuff( CONST_LASTER_SYS_PTR cp_laster );

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
 */
//-----------------------------------------------------------------------------
GLOBAL void LASTER_SwitchFlagSet( LASTER_SYS_PTR p_laster, u8 switch_flag );

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
 *		�Q�Ɨp�o�b�t�@���������ݗp�ɕύX���܂��B
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void LASTER_VBlank( LASTER_SYS_PTR p_laster );



//-----------------------------------------------------------------------------
/**
 * 
 *		���X�^�[�V�X�e�����g�p�����ėp�֐��S	[ LABEL_LASTER_RAP_FUNC ]
 *		
 */
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
/**
 *
 *		���X�^�[H�u�����NDMA�]���֐�
 * 
 */
//-----------------------------------------------------------------------------
// �ʐM����O���t�B�b�N�f�[�^�]������
// �������Ȃ��Ƃ��N����Ȃ����̎������K�v�ł����A
// ���̂Ƃ����0�ɂ��Ă����܂��B
#define LASTER_USE_DMA	(0)		// �g�p����DMA�i���o�[
enum{
	LASTER_DMA_TYPE16,
	LASTER_DMA_TYPE32
};

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
GLOBAL void LASTER_DmaStop( void );

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
GLOBAL void LASTER_DmaSet( const void* p_src, void* p_dest, int szbyte, int dma_type );


//-----------------------------------------------------------------------------
/**
 *		���X�^�[�X�N���[��
 *			DMA�]���g�p
*/
//-----------------------------------------------------------------------------
#define LASTER_SCROLL_BUFF_SIZE	(192)	// �o�b�t�@�T�C�Y

// BG�ʒ萔
// �X�N���[�����W�X�^�@�����W�A�h���X
enum{
	LASTER_SCROLL_MBG0 = REG_BG0HOFS_ADDR,
	LASTER_SCROLL_MBG1 = REG_BG1HOFS_ADDR,
	LASTER_SCROLL_MBG2 = REG_BG2HOFS_ADDR,
	LASTER_SCROLL_MBG3 = REG_BG3HOFS_ADDR,
	LASTER_SCROLL_SBG0 = REG_DB_BG0HOFS_ADDR,
	LASTER_SCROLL_SBG1 = REG_DB_BG1HOFS_ADDR,
	LASTER_SCROLL_SBG2 = REG_DB_BG2HOFS_ADDR,
	LASTER_SCROLL_SBG3 = REG_DB_BG3HOFS_ADDR
};
typedef struct _LASTER_SCROLL* LASTER_SCROLL_PTR;
typedef const struct _LASTER_SCROLL* CONST_LASTER_SCROLL_PTR;

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
GLOBAL LASTER_SCROLL_PTR LASTER_ScrollInit( int heap );

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
 * start <= �X�N���[���͈� <= end
 * 
 * bg_no
 * 		LASTER_SCROLL_MBG0,		// ���C�����
 *		LASTER_SCROLL_MBG1,
 *		LASTER_SCROLL_MBG2,
 *		LASTER_SCROLL_MBG3,
 *		LASTER_SCROLL_SBG0,		// �T�u���
 *		LASTER_SCROLL_SBG1,
 *		LASTER_SCROLL_SBG2,
 *		LASTER_SCROLL_SBG3
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void LASTER_ScrollStart( LASTER_SCROLL_PTR p_lstscr, u8 start, u8 end, u16 add_r, fx32 r_w, s16 scr_sp, u32 bg_no, u32 init_num, u32 tsk_pri );

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
GLOBAL void LASTER_ScrollEnd( LASTER_SCROLL_PTR p_lstscr );

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
GLOBAL void LASTER_ScrollDelete( LASTER_SCROLL_PTR p_lstscr );

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
GLOBAL void* LASTER_GetScrollWriteBuff( LASTER_SCROLL_PTR p_lstscr );
GLOBAL const void* LASTER_GetScrollReadBuff( LASTER_SCROLL_PTR p_lstscr );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	���X�^�[�X�N���[��V�u�����N�֐�		
 *
 *	@param	p_lstscr	���X�^�[�X�N���[�����[�N
 *
 *	@return	none
 *
 * �o�b�t�@�X�C�b�`
 *		���̏�����30�t���[���œ����Ă���Ƃ���2��ڂ�
 *		VBlank���ԂŌĂ�ł��������B
 *
 *	HblankDma�]���ݒ�
 *		���̏�����VBlank���Ԃ����邽�тɌĂ�ł��������B
 *
 */
//-----------------------------------------------------------------------------
// �o�b�t�@�X�C�b�`
GLOBAL void LASTER_ScrollVBuffSwitch( LASTER_SCROLL_PTR p_lstscr );

// HblankDma�]���ݒ�
GLOBAL void LASTER_ScrollVDma( LASTER_SCROLL_PTR p_lstscr );

//-----------------------------------------------------------------------------
/**
 *	���̂�
 */
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *
 *	@brief	�T�C���J�[�u�e�[�u�����쐬����
 *
 *	@param	sinTbl	�i�[��z��
 *	@param	num		�z��v�f��	s16 buff[ 10 ]; �Ȃ�10���w��
 *	@param	add_r	�P��ɉ�]�p��ω�������l
 *	@param	r_w		���a
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void LASTER_ScrollMakeSinTbl( s16* sinTbl, u32 num, u16 add_r, fx32 r_w );


#undef	GLOBAL
#endif		// __LASTER_H__

