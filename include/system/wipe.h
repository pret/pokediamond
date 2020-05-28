//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *@file		wipe.h
 *@brief	DP��ʐ؂�ւ��V�X�e��
 *@author	tomoya takahashi
 *@data		2005.08.18
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
#ifndef __WIPE_H__
#define __WIPE_H__

#undef GLOBAL
#ifdef	__WIPE_H_GLOBAL
#define	GLOBAL	/* */
#else
#define	GLOBAL	extern
#endif
//-----------------------------------------------------------------------------
/**
 *					�萔�錾
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	
//	��ʐ؂�ւ��p�^�[���ԍ�
//	
//=====================================
#define 	WIPE_PATTERN_WMS		(0)		// ����
#define 	WIPE_PATTERN_FMAS		(1)		// ���C����ʂ���T�u���
#define 	WIPE_PATTERN_FSAM		(2)		// �T�u��ʂ��烁�C�����
#define 	WIPE_PATTERN_M			(3)		// ���C����ʂ̂�
#define 	WIPE_PATTERN_S			(4)		// �T�u��ʂ̂�

//-------------------------------------
//	
//	���C�v�p�^�[����	
//	�|�P����DP/DP:��恕�d�l/��ʐ؂�ւ��d�l�Q��
//	
//=====================================
#define 	WIPE_TYPE_FADEOUT				(0)// �t�F�[�h�A�E�g	��					�u���C�g�l�X�g�p
#define 	WIPE_TYPE_FADEIN				(1)// �t�F�[�h�C��		��					�u���C�g�l�X�g�p
#define 	WIPE_TYPE_SHUTTEROUT_DOWN		(2)// �V���b�^�[�A�E�g	�ォ�牺			�n�[�h�E�F�A�E�B���h�E�g�p
#define 	WIPE_TYPE_SHUTTERIN_DOWN		(3)// �V���b�^�[�C��	�ォ�牺			�n�[�h�E�F�A�E�B���h�E�g�p
#define 	WIPE_TYPE_SHUTTEROUT_UP			(4)// �V���b�^�[�A�E�g	�������			�n�[�h�E�F�A�E�B���h�E�g�p
#define 	WIPE_TYPE_SHUTTERIN_UP			(5)// �V���b�^�[�C��	�������			�n�[�h�E�F�A�E�B���h�E�g�p
#define 	WIPE_TYPE_SLIDEOUT				(6)// �X���C�h�A�E�g	�E���獶			�n�[�h�E�F�A�E�B���h�E�g�p	
#define 	WIPE_TYPE_SLIDEIN				(7)// �X���C�h�C��		�E���獶			�n�[�h�E�F�A�E�B���h�E�g�p
#define 	WIPE_TYPE_SPLITOUT_VSIDE		(8)// �X�v���b�g�A�E�g	�c�@��ʏ㉺����	�n�[�h�E�F�A�E�B���h�E�g�p
#define 	WIPE_TYPE_SPLITIN_VCENTER		(9)// �X�v���b�g�C��	�c�@��ʒ�������	�n�[�h�E�F�A�E�B���h�E�g�p
#define 	WIPE_TYPE_SPLITOUT_VCENTER		(10)// �X�v���b�g�A�E�g	�c	��ʒ�������	�n�[�h�E�F�A�E�B���h�E�g�p
#define 	WIPE_TYPE_SPLITIN_VSIDE			(11)// �X�v���b�g�C��	�c	��ʏ㉺����	�n�[�h�E�F�A�E�B���h�E�g�p
#define 	WIPE_TYPE_SPLITOUT_HSIDE		(12)// �X�v���b�g�A�E�g	��	��ʍ��E����	�n�[�h�E�F�A�E�B���h�E�g�p
#define 	WIPE_TYPE_SPLITIN_HCENTER		(13)// �X�v���b�g�C��	��	��ʒ�������	�n�[�h�E�F�A�E�B���h�E�g�p
#define 	WIPE_TYPE_SPLITOUT_HCENTER		(14)// �X�v���b�g�A�E�g	��	��ʒ�������	�n�[�h�E�F�A�E�B���h�E�g�p
#define 	WIPE_TYPE_SPLITIN_HSIDE			(15)// �X�v���b�g�C��	��	��ʍ��E����	�n�[�h�E�F�A�E�B���h�E�g�p
#define 	WIPE_TYPE_HOLEOUT				(16)// �z�[���A�E�g							�n�[�h�E�F�A�E�B���h�E�g�p
#define 	WIPE_TYPE_HOLEIN				(17)// �z�[���C��							�n�[�h�E�F�A�E�B���h�E�g�p
#define 	WIPE_TYPE_TUNNELOUT				(18)// �g���l���A�E�g						�n�[�h�E�F�A�E�B���h�E�g�p
#define 	WIPE_TYPE_TUNNELIN				(19)// �g���l���C��							�n�[�h�E�F�A�E�B���h�E�g�p
#define 	WIPE_TYPE_CURTAINOUT			(20)// �J�[�e���A�E�g						�n�[�h�E�F�A�E�B���h�E�g�p
#define 	WIPE_TYPE_CURTAININ				(21)// �J�[�e���C��							�n�[�h�E�F�A�E�B���h�E�g�p
#define 	WIPE_TYPE_BOXOUT_OUTSIDE		(22)// �{�b�N�X�A�E�g	�O���璆			�n�[�h�E�F�A�E�B���h�E�g�p
#define 	WIPE_TYPE_BOXIN_INSIDE			(23)// �{�b�N�X�C��		������O			�n�[�h�E�F�A�E�B���h�E�g�p
#define 	WIPE_TYPE_BOXOUT_INSIDE			(24)// �{�b�N�X�A�E�g	������O			�n�[�h�E�F�A�E�B���h�E�g�p
#define 	WIPE_TYPE_BOXIN_OUTSIDE			(25)// �{�b�N�X�C��		�O���璆			�n�[�h�E�F�A�E�B���h�E�g�p
#define 	WIPE_TYPE_DOOROUT				(26)// �h�A�A�E�g							�n�[�h�E�F�A�E�B���h�E�g�p
#define 	WIPE_TYPE_DOORIN				(27)// �h�A�C��								�n�[�h�E�F�A�E�B���h�E�g�p
#define 	WIPE_TYPE_ALTERNATEOUT_H		(28)// �I���^�l�[�g�A�E�g	��				�n�[�h�E�F�A�E�B���h�E�g�p
#define 	WIPE_TYPE_ALTERNATEIN_H			(29)// �I���^�l�[�g�C��		��				�n�[�h�E�F�A�E�B���h�E�g�p
#define 	WIPE_TYPE_BLINDOUT_H			(30)// �u���C���h�A�E�g		��				�n�[�h�E�F�A�E�B���h�E�g�p
#define 	WIPE_TYPE_BLINDIN_H				(31)// �u���C���h�C��		��				�n�[�h�E�F�A�E�B���h�E�g�p
#define 	WIPE_TYPE_SCREWOUT				(32)// �X�N�����[�A�E�g						�n�[�h�E�F�A�E�B���h�E�g�p
#define 	WIPE_TYPE_SCREWIN				(33)// �X�N�����[�C��                       �n�[�h�E�F�A�E�B���h�E�g�p
#define 	WIPE_TYPE_FLASHOUT_FOREWAY		(34)// �t���b�V���A�E�g	�S����				�n�[�h�E�F�A�E�B���h�E�g�p
#define 	WIPE_TYPE_FLASHIN_FOREWAY		(35)// �t���b�V���C��	�S����              �n�[�h�E�F�A�E�B���h�E�g�p
#define 	WIPE_TYPE_TUNNELOUT_TOP			(36)// �g���l���A�E�g						�n�[�h�E�F�A�E�B���h�E�g�p
#define 	WIPE_TYPE_TUNNELIN_TOP			(37)// �g���l���C��							�n�[�h�E�F�A�E�B���h�E�g�p
#define 	WIPE_TYPE_SLIDEOUT_LR			(38)// �X���C�h�A�E�g�@������E 			�n�[�h�E�F�A�E�B���h�E�g�p
#define 	WIPE_TYPE_SLIDEIN_LR			(39)// �X���C�h�C��	�@ ������E				�n�[�h�E�F�A�E�B���h�E�g�p
#define 	WIPE_TYPE_PESOCOMOUT			(40)// �p�\�R���A�E�g 			�n�[�h�E�F�A�E�B���h�E�g�p
#define 	WIPE_TYPE_PESOCOMIN				(41)// �p�\�R���C��					�n�[�h�E�F�A�E�B���h�E�g�p
#define 	WIPE_TYPE_MAX					(42)// �ő吔

//-------------------------------------
//	
//	�t�F�[�h�C���E�A�E�g�J���[
//	
//=====================================
#define WIPE_FADE_WHITE		(0x7fff)	// �z���C�g�C���E�A�E�g
#define WIPE_FADE_BLACK		(0x0000)	// �u���b�N�C���E�A�E�g
#define WIPE_FADE_OUTCOLOR	(0xffff)	// 1�O�̃t�F�[�h�A�E�g�J���[�ŃC���E�A�E�g

//-------------------------------------
//	
//	���C����ʂ��@�T�u��ʂ�
//	
//=====================================
#define 	WIPE_DISP_MAIN		(0)		// ���C����
#define 	WIPE_DISP_SUB		(1)		// �T�u��

//-------------------------------------
//	��{�I�Ɏg�p���镪�����ƃV���N��
//=====================================
#define WIPE_DEF_DIV	( 6 )
#define WIPE_DEF_SYNC	( 1 )


//-------------------------------------
//	TCB�@�^�X�N�D�揇��
//=====================================
#define WIPE_VBLANK_WND_SWAP_TCB	( 1023 )	// �E�B���h�E�X���b�v
#define WIPE_HBLANK_INIT_TCB	( 1024 )	//H�u�����N������
#define WIPE_HBLANK_DELETE_TCB	( 1024 )	//H�u�����N�j��
#define WIPE_VBLANK_WND_DELETE_TCB	( 1025 )	// H�u�����N�E�B���h�E�f�[�^�j��
#define WIPE_VBLANK_BR_RESET_TCB	( 1024 )	// V�u�����N��ײ�Ƚ���Z�b�g
	


//�A�Z���u����include����Ă���ꍇ�́A���̐錾�𖳎��ł���悤��ifndef�ň͂�ł���
#ifndef	__ASM_NO_DEF_

//-----------------------------------------------------------------------------
/**
 *					�\���̐錾
*/
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
/**
 *					�v���g�^�C�v�錾
*/
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *
 *@brief	��ʐ؂�ւ����C�v���J�n
 *
 *@param	pattern		�؂�ւ��p�^�[���ԍ�
 *@param	wipe_m		���C�v�@���C����ʃ��C�v�p�^�[��
 *@param	wipe_s		���C�v�@�T�u��ʃ��C�v�p�^�[��
 *@param	color		���C�v�̐F	
 *@param	division	�e���C�v�����̕�����	(1.2.3.4.....)
 *@param	piece_sync	�e���C�v�̏����𕪊������P�Ђ̃V���N��	(1.2.3.4.....)
 *@param	heap		�g�p����q�[�v
 *
 *@return	none
 *
 *	color
 *		���C�v�̐F�͐�5bit ��5bit ��5bit�ł��B
 *		�t�F�[�h�C���E�A�E�g���͍�������������܂���̂�
			#define WIPE_FADE_WHITE		(0x7fff)	// �z���C�g�C���E�A�E�g
			#define WIPE_FADE_BLACK		(0x0000)	// �u���b�N�C���E�A�E�g
			#define WIPE_FADE_OUTCOLOR	(0xffff)	// 1�O�̃t�F�[�h�A�E�g�J���[�ŃC���E�A�E�g
		���w�肵�Ă��������B
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void WIPE_SYS_Start(int pattern, int wipe_m, int wipe_s, u16 color, int division, int piece_sync, int heap);

//----------------------------------------------------------------------------
/**
 *	@brief	��ʐ؂�ւ����C�v���C���֐�
 *
 *	�����̊֐��́Asystem/main.c�ŌĂ΂�Ă��܂��̂ŁA
 *	�@�ĂԕK�v�͂���܂���B
 */
//-----------------------------------------------------------------------------
GLOBAL void WIPE_SYS_Main( void );

//----------------------------------------------------------------------------
/**
 *	@brief	��ʐ؂�ւ����C�v�@�I���`�F�b�N
 *
 *	@param	none
 *
 *	@retval	TRUE	�I��
 *	@retval	FALSE	�r��
 */
//-----------------------------------------------------------------------------
GLOBAL BOOL WIPE_SYS_EndCheck( void );

//----------------------------------------------------------------------------
/**
 *	@brief	���C�v�̋����I��
 */
//-----------------------------------------------------------------------------
GLOBAL void WIPE_SYS_ExeEnd( void );

//----------------------------------------------------------------------------
/**
 *	@brief	���C�v����ʂɉe����^���Ă��邩�`�F�b�N
 *
 *	@retval	TRUE	���C�v��ԃN���A���Ă���
 *	@retval	FALSE	���C�v��ԃN���A����Ă��Ȃ�
 */
//-----------------------------------------------------------------------------
GLOBAL BOOL WIPE_SYS_EffectCheck( void );

//----------------------------------------------------------------------------
/**
 *
 * �����s���ꂽ�u�Ԕ��f����܂��B
 *
 *	@brief	�E�B���h�E�}�X�N��Ԃ���������
 *
 *	@param	disp	�������������
 *
 *	@return
 *
 * disp
	WIPE_DISP_MAIN,		// ���C����
	WIPE_DISP_SUB		// �T�u��
 *
 * �����̊֐���
 *	 �n�[�h�E�F�A�E�B���h�E���g�p�������C�v����
 * �@�u���C�g�l�X���g�p�������C�v�Ɉڍs���鎞�ɁA
 * �@�n�[�h�E�F�A�E�B���h�E�̐ݒ����������ׂɎg�p���܂��B
 * 
 */
//-----------------------------------------------------------------------------
GLOBAL void WIPE_ResetWndMask( int disp );

//----------------------------------------------------------------------------
/**
 *
 * �����s���ꂽ�u�Ԕ��f����܂��B
 *
 *	@brief	�u���C�g�l�X��Ԃ�����
 *
 *	@param	disp	�������������
 *
 *	@return	none
 *
 * disp
	WIPE_DISP_MAIN,		// ���C����
	WIPE_DISP_SUB		// �T�u��
 *
 * �����̊֐���
 *	 �u���C�g�l�X���g�p�������C�v����
 * �@�n�[�h�E�F�A�E�B���h�E���g�p�������C�v�Ɉڍs���鎞�ɁA
 * �@�u���C�g�l�X�̐ݒ����������ׂɎg�p���܂��B
 */
//-----------------------------------------------------------------------------
GLOBAL void WIPE_ResetBrightness( int disp );

//----------------------------------------------------------------------------
/**
 * �����s���ꂽ�u�Ԕ��f����܂��B
 *
 *	@brief	���C�v��Ԃ���������
 *
 *	@param	disp	�������������
 *	@param	heap	�g�p����q�[�v
 *
 *	@return	none
 *
 * disp
	WIPE_DISP_MAIN,		// ���C����
	WIPE_DISP_SUB		// �T�u��
 *
 *	�ǂ����Ă��t�F�[�h�C����WIPE�̃V�X�e�����g�p�ł��Ȃ����A
 *	�u���C�g�l�X�ƃE�B���h�E�}�X�N��Ԃ���������֐��ł��B
 * 
 */
//-----------------------------------------------------------------------------
GLOBAL void WIPE_Reset( int disp );

//----------------------------------------------------------------------------
/**
 *	@brief	���C�v�u���C�g�l�X��Ԃ�ݒ�
 *
 *	@param	disp	�ݒ肷����
 *	@param	color	�u���C�g�l�X�J���[
 *
 *	@return	none
 *
 * disp
	WIPE_DISP_MAIN,		// ���C����
	WIPE_DISP_SUB		// �T�u��

 *	color
			#define WIPE_FADE_WHITE		(0x7fff)	// �z���C�g�C���E�A�E�g
			#define WIPE_FADE_BLACK		(0x0000)	// �u���b�N�C���E�A�E�g
			#define WIPE_FADE_OUTCOLOR	(0xffff)	// 1�O�̃t�F�[�h�A�E�g�J���[�ŃC���E�A�E�g
 *
 * ���̊֐��́A�ǂ����Ă�WIPE�̃V�X�e�����g�p�ł��Ȃ��l���A
 * �t�F�[�h�A�E�g��A�}�X�^�[�u���C�g�l�X�l��ݒ肷�邽�߂̊֐��ł��B
 *
 * �p���b�g�t�F�[�h�Ȃǂ��g�p������ɁA���̊֐��Ń}�X�^�[�P�x��ݒ肵�A
 * �p���b�g�t�F�[�h�̉��������Ă��������B
 */
//-----------------------------------------------------------------------------
GLOBAL void WIPE_SetBrightness( int disp, u16 color );

//----------------------------------------------------------------------------
/**
 *	@brief	���C�v�E�B���h�E�}�X�N��Ԃ�ݒ�
 *
 *	@param	disp		�ݒ肷����
 *	@param	color		�J���[
 *
 * disp
	WIPE_DISP_MAIN,		// ���C����
	WIPE_DISP_SUB		// �T�u��

 *	color
			#define WIPE_FADE_WHITE		(0x7fff)	// �z���C�g�C���E�A�E�g
			#define WIPE_FADE_BLACK		(0x0000)	// �u���b�N�C���E�A�E�g
			#define WIPE_FADE_OUTCOLOR	(0xffff)	// 1�O�̃t�F�[�h�A�E�g�J���[�ŃC���E�A�E�g
 *
 *	���̊֐��́A
 *		�^�b�`�y���g�p��ʂ̏ꍇ�ɁA�t�F�[�h�C���O�Ƀ^�b�`�y����
 *		�o���ȂǁA��O����������܂��B���̂Ƃ��p�̊֐��ł�
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
GLOBAL void WIPE_SetWndMask( int disp, u16 color );

#endif	// __ASM_NO_DEF_

#undef	GLOBAL
#endif		// __WIPE_H__
