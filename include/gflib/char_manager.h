//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *	@file		char_manager.h
 *	@brief		�L�����N�^�f�[�^�}�l�[�W���[�w�b�_
 *	@author		tomoya takahashi
 *	@data		2004.11.22
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]



#ifndef CHAR_MANAGER_H__
#define	CHAR_MANAGER_H__

#include "nnsys.h"

#undef	GLOBAL
#ifdef	CHAR_MANAGER_H_GLOBAL
#define	GLOBAL	/* */
#else
#define	GLOBAL	extern
#endif

//-----------------------------------------------------------------------------
/**
*		OBJ�}�b�s���O���[�h�̐���
*
���n�a�i�}�b�s���O���[�h�ɂ��Ă̐���
	�n�`�l�A�g���r���[�g�̐擪�L�����N�^�l�[���̃��W�X�^��10bit�ŁA0~1023�̒l�����邱�Ƃ��o���܂��B
	����ŁA�擪����32KByte�܂łɓ������L�����N�^�f�[�^�͎Q�Əo���܂��B

	�������c�r�ł́A�X�v���C�g�̃L�����N�^�f�[�^��16KByte~256KByte�w��ł��܂��B
	16Kbyte 32Kbyte�͑��v�ł����A64KByte~256KByte�͐擪����I�[�܂ł̑S�ẴL�����N�^�f�[�^��
	�O�`�P�O�Q�R�ł͎Q�Ƃ��邱�Ƃ��o���Ȃ��Ȃ��Ă��܂��܂��B

	�����������邽�߂ɁA�n�a�i�}�b�s���O���[�h�ŁA�L�����N�^���E���w�肵�܂��B
	��jOBJ�}�b�s���O���[�h�@�P�Q�W�jb yte�@�̎�
	�L�����N�^���E�@�� �@128Byte�@���@�S�L�����N�^
	�S�L�����N�^���擪�L�����N�^�l�[����ݒ�o���܂��B
	�O		�|���O�L�����N�^����Q��	�i���W�X�^�̒l�@�[���@���ۂ̎Q�Ɛ�̃L�����N�^�i���o�[�j
	�P		�|���S�L�����N�^����Q��
	�Q		�[���W�L�����N�^����Q��
	�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
	�P�O�Q�R	�[���W�P�W�S�L�����N�^����Q��

	����ŁA�O�`�P�O�Q�R�̒l�ŁA�P�Q�W�j�a�������̗̈���w�肷�邱�Ƃ��o����悤�ɂȂ�܂��B
	���̑���ɁA�P�L�����N�^�T�C�Y�̃L�����N�^�f�[�^���g�p�������ł��A�S�L�����N�^����
	�u�������ɔz�u���Ă����K�v������܂��B

	��̎�����AVram�T�C�Y�ɍ��킹�āA�K�؂Ȃn�a�i�}�b�s���O���[�h��ݒ肷��K�v������܂��B

*
*	�ENitroCharacter�ł́A��̂��Ƃ��l�������L�����N�^�f�[�^�������o���Ă���Ă��܂�
*	�@�̂ŁA�Z���f�[�^�쐬����OBJ�}�b�s���O���[�h�ݒ�����Ă��������B
*	�E�ȉ�NitroSDK�w���v
*	GX_OBJVRAMMODE_CHAR_2D	
*		2�����}�b�s���O���[�h��I�����܂��B 
*		
*	GX_OBJVRAMMODE_CHAR_1D_32K
*		�P�����}�b�s���O���[�h�ŁA�擪�L�����N�^���E��32�o�C�g�Ƃ��܂��B
*		���p�\��OBJ-VRAM�̍ő�e�ʂ�32KB�ɂȂ�܂��B 
*		
*	 GX_OBJVRAMMODE_CHAR_1D_64K
*		�P�����}�b�s���O���[�h�ŁA�擪�L�����N�^���E��64�o�C�g�Ƃ��܂��B
*		���p�\��OBJ-VRAM�̍ő�e�ʂ�64KB�ɂȂ�܂��B 
*		
*	 GX_OBJVRAMMODE_CHAR_1D_128K
*		�P�����}�b�s���O���[�h�ŁA�擪�L�����N�^���E��128�o�C�g�Ƃ��܂��B
*		���p�\��OBJ-VRAM�̍ő�e�ʂ�128KB�ɂȂ�܂��B 
*		
*	 GX_OBJVRAMMODE_CHAR_1D_256K
*		�P�����}�b�s���O���[�h�ŁA�擪�L�����N�^���E��256�o�C�g�Ƃ��܂��B
*		���p�\��OBJ-VRAM�̍ő�e�ʂ�256KB�ɂȂ�܂��B 
*
*
*	�Q��Vram�Ǘ����@�ɂ���
*	
*	��CharSet-CharSets�̓���
*		Vram�̐擪����L�����N�^�f�[�^�Â�Offset�����炵��
*		�]�����Ă����܂��BDelChar�֐����g�p���Ă�
*		Offset��߂��Ȃǂ̏������o���Ȃ����߁A
*		�ēx�g�p�����̈���g���Ƃ������Ƃ��o���܂���B
*
*	��CharSetAreaCont-CharSetsAreaCont�̓���
*		Vram�̊Ǘ��̈���쐬���āA�g�p�󋵂��Ǘ����܂��B
*		�T�C�Y���̃L�����N�^�f�[�^��]������̈悪�󂢂Ă��邩��
*		�`�F�b�N���Ă���L�����N�^�f�[�^��]�����܂��B
*		DelChar������Ǝg�p�̈����ɂ��܂��̂ŁA
*		�̈���ė��p���邱�Ƃ��o���܂��B
*/
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
/**
*		�萔��`
*/
//-----------------------------------------------------------------------------
// �萔
// �L�����N�^�f�[�^�R���g���[���^�C�v
// �R���g���[���^�C�v
//		�I�t�Z�b�g�[�[�[�[�[�擪����I�t�Z�b�g�����炵�āA
//							�]���I�t�Z�b�g�����߂�
//		�G���A�R���g���[���[Vram�̈�Ǘ��z�񂩂�󂢂Ă���̈���`�F�b�N����
//							�]���I�t�Z�b�g�����߂�
enum{
	CHARM_CONT_OFFSET,		// �I�t�Z�b�g�^�C�v
	CHARM_CONT_AREACONT,	// �G���A�R���g���[���^�C�v
};

//----------------------------------------------------------------------------
/**
 *					�\���̐錾
 */
//-----------------------------------------------------------------------------
//-------------------------------------
//	
//	�L�����N�^�}�l�[�W���[�쐬
//	�\����
//	
//=====================================
typedef struct {
	int CharDataNum;		// �L�����N�^���䐔
	int VramTransAreaMain;	// ���C����ʂ�AreaCont�p�ɗp�ӂ���Vram�T�C�Y
	int VramTransAreaSub;	// �T�u��ʂ�AreaCont�p�ɗp�ӂ���Vram�T�C�Y
	int heap;				// �g�p����q�[�v
} CHAR_MANAGER_MAKE;


//-------------------------------------
//	
//	�L�����N�^�f�[�^�w�b�_�[
//	
//=====================================
typedef struct {
	NNSG2dCharacterData*	res_file;		// �L�����N�^���\�[�X
	u32		type;			// �o�^�^�C�v
							// main�ɓo�^�FNNS_G2D_VRAM_TYPE_2DMAIN
							// sub�ɓo�^ �FNNS_G2D_VRAM_TYPE_2DSUB
							// �����ɓo�^�FNNS_G2D_VRAM_TYPE_2DMAX
	u32		id;				// ���̃L�����N�^�f�[�^��ID

	u32		cont_type;		// Vram�R���g���[���^�C�v
							// CHARM_CONT_OFFSET	�I�t�Z�b�g�^�C�v
							// CHARM_CONT_AREACONT	�G���A�R���g���[���^�C�v
} CHAR_MANAGER_HEADER;

//-------------------------------------
//	
//	�L�����N�^�]�������̃V�X�e����
//	�g�p���Ȃ��Ƃ���VRAM�̗̈�̂݊m�ۂ���
//	�V�X�e���̊m�ۗ̈�f�[�^
//	
//=====================================
typedef struct {
	u32 alloc_size;
	u32 alloc_ofs;
	u32	type;		// Vram�m�ۂ����\����
	// main�ɓo�^�FNNS_G2D_VRAM_TYPE_2DMAIN = 1
	// sub�ɓo�^ �FNNS_G2D_VRAM_TYPE_2DSUB = 2
} CHAR_MANAGER_ALLOCDATA;


//----------------------------------------------------------------------------
/**
 *					�v���g�^�C�v�錾
 */
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
/**
 *	�y�L�����N�^�}�l�[�W���������̓���z		
 *	typedef struct {
 *		int CharDataNum;		// �L�����N�^���䐔
 *		int VramTransAreaMain;	// ���C����ʂ�AreaCont�p�ɗp�ӂ���Vram�T�C�Y
 *		int VramTransAreaSub;	// �T�u��ʂ�AreaCont�p�ɗp�ӂ���Vram�T�C�Y
 *		int heap;				// �g�p����q�[�v
 *	} CHAR_MANAGER_MAKE;
 *	
 *	��̃f�[�^�ŏ��������܂��B
 *	CharDataNum			�o�^����L�����N�^�̐���n���Ă��������B
 *						CharDataNum���̃��[�N���쐬���܂��B
 *
 *	VramTransAreaMain	AreaCont�֐��Ŏg�p����Vram�Ǘ��̈�T�C�Y�ł��B
 *	VramTransAreaSub	���̃T�C�Y�����Ǘ����܂��B
 *	
 *	heap				�g�p����q�[�vID
 *
 *
 *	���̃f�[�^�ŏ����������Vram�Ǘ����
 *		�����AVram�̍ő傪0x20000��VramTransAreaMain��0x10000
 *		��ݒ肵���Ƃ��́A�ȉ��̂悤�ȊǗ���ԂɂȂ�܂��B
 *		Vram�̈�
 *		offset
 *		0x00000000
 *					�I�t�Z�b�g�Â炵�p�̈�		CharSet CharSets
 *		0x00010000
 *					AreaCont�p�̈�		CharSetAreaCont CharSetsAreaCont
 *		0x00020000
 */
//-----------------------------------------------------------------------------

//----------------------------------------------------------------------------
/**
 *
 *@brief	  �L�����N�^�}�l�[�W���[��������
 
 *@param	CharMakeData	�L�����N�^�}�l�[�W���[�쐬�f�[�^
 *
 *@return	none
 *
 * ���ݒ肳��Ă���L�����N�^���[�h�����āAVram�̊Ǘ��̈�Ȃǂ̍쐬��
 * �s���܂��B
 * �L�����N�^���[�h���ꏏ�ɐݒ肷�鏉�����֐����쐬���܂����̂ŁA
 * �ꏏ�ɐݒ肵�����Ƃ��́A����������g�����������B
 *	InitCharManagerReg�֐�
 * 
 */
//-----------------------------------------------------------------------------
GLOBAL void InitCharManager( const CHAR_MANAGER_MAKE* CharMakeData );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�L�����N�^�}�l�[�W����������
 *
 *	@param	CharMakeData	�L�����N�^�}�l�[�W���쐬�f�[�^
 *	@param	modeMain		�L�����N�^�}�b�s���O���[�h�@���C�����
 *	@param	modeSub			�L�����N�^�}�b�s���O���[�h�@�T�u���
 *
 *	@return	none
 *
 *	GX_OBJVRAMMODE_CHAR_2D			2�����}�b�s���O���[�h��I�����܂��B 
 *	GX_OBJVRAMMODE_CHAR_1D_32K		�P�����}�b�s���O���[�h�ŁA�擪�L�����N�^���E��32�o�C�g�Ƃ��܂��B
 *									���p�\��OBJ-VRAM�̍ő�e�ʂ�32KB�ɂȂ�܂��B 
 *	GX_OBJVRAMMODE_CHAR_1D_64K		�P�����}�b�s���O���[�h�ŁA�擪�L�����N�^���E��64�o�C�g�Ƃ��܂��B
 *									���p�\��OBJ-VRAM�̍ő�e�ʂ�64KB�ɂȂ�܂��B 
 *	GX_OBJVRAMMODE_CHAR_1D_128K		�P�����}�b�s���O���[�h�ŁA�擪�L�����N�^���E��128�o�C�g�Ƃ��܂��B
 *									���p�\��OBJ-VRAM�̍ő�e�ʂ�128KB�ɂȂ�܂��B 
 *	GX_OBJVRAMMODE_CHAR_1D_256K		�P�����}�b�s���O���[�h�ŁA�擪�L�����N�^���E��256�o�C�g�Ƃ��܂��B
 *									���p�\��OBJ-VRAM�̍ő�e�ʂ�256KB�ɂȂ�܂��B 
 *
 * 
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void InitCharManagerReg( const CHAR_MANAGER_MAKE* CharMakeData, GXOBJVRamModeChar modeMain, GXOBJVRamModeChar modeSub );

//----------------------------------------------------------------------------
/**
 *
 *@brief	�L�����N�^�}�l�[�W���[�����S�ɔj�����܂��B
 *
 *@param	none
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void DeleteCharManager(void);

//----------------------------------------------------------------------------
/**
 *
 *@brief	  ���[�h���J�n����֐�	(�����Ǘ��̃I�t�Z�b�g��������)
 *
 *@param	  start_offset�F�ǂݍ��݊J�noffset
 *
 *@return	  none
 */
//-----------------------------------------------------------------------------
GLOBAL void CharLoadStart( u32 start_offset );	
GLOBAL void CharLoadStartSub( u32 start_offset );

//----------------------------------------------------------------------------
/**
 *
 *@brief	AreaCont�p�̃��C���A�T�u�̗��Ǘ��̈��������
 *
 *@param	none
 *
 *@return	none
 */
//-----------------------------------------------------------------------------
GLOBAL void TransAreaInitAll( void );

//----------------------------------------------------------------------------
/**
 *
 *@brief	  ���[�h���J�n����֐�	�O�Ń��C���A�T�u�ʂ̃I�t�Z�b�g������������
 *				AreaCont�pVram�G���A�̏��������s���Ă��܂��B
 *
 *@param	  none
 *
 *@return	  none
 */
//-----------------------------------------------------------------------------
GLOBAL void CharLoadStartAll( void );

//----------------------------------------------------------------------------
/**
 *	@brief	AreaCont�֐��p	�g�p�֎~�̈�ݒ�
 *
 *	@param	offset		�g�p�֎~�I�t�Z�b�g�ʒu
 *	@param	size		�g�p�֎~�T�C�Y
 *	@param	disp		���
 *
 *	disp
 *		main�ɓo�^�FNNS_G2D_VRAM_TYPE_2DMAIN = 1
 *		sub�ɓo�^ �FNNS_G2D_VRAM_TYPE_2DSUB = 2
 *
 *	@return	none
 *	
 *	���g�p��̒���
 *	GLOBAL void TransAreaInitAll( void );
 *	GLOBAL void CharLoadStartAll( void );
 *	���g�p������ɂ��̐ݒ�����Ă��������B
 *	��̂Q�̊֐��̒��ŁA�֎~�̈�̏��������s���Ă��܂��܂�	
 */
//-----------------------------------------------------------------------------
GLOBAL void SetReserveAreaContCharManager( u32 offset, u32 size, u32 disp );

//----------------------------------------------------------------------------
/**
 *
 *@brief		�L�����N�^�f�[�^�P�̂��Z�b�g���ă��[�h
 *
 *@param		pChatData�F�L�����N�^ENTRY�f�[�^
 *
 *@retval		TRUE �F�Z�b�g�ł���  
 *@retval		FALSE�F�Z�b�g�ł��Ȃ�����
 *
 */
//-----------------------------------------------------------------------------
GLOBAL BOOL CharSet( const CHAR_MANAGER_HEADER* pCharData );

//----------------------------------------------------------------------------
/**
 *
 *@brief		�L�����N�^�f�[�^�𕡐��Z�b�g
 *
 *@param		pChatData	�L�����N�^�f�[�^�z��
 *@param		num			�z��v�f��
 *
 *@return		�����o�^����������
 */
//-----------------------------------------------------------------------------
GLOBAL u16 CharSets( const CHAR_MANAGER_HEADER* pCharData, int num );

//----------------------------------------------------------------------------
/**
 *
 *@brief		�L�����N�^�f�[�^�P�̂��Z�b�g���ă��[�h
 *				�}�b�s���O���[�h�����̃��W�X�^��ԂɕύX���郂�[�h
 *
 *@param		pChatData�F�L�����N�^ENTRY�f�[�^
 *
 *@retval		TRUE �F�Z�b�g�ł���  
 *@retval		FALSE�F�Z�b�g�ł��Ȃ�����
 *
 * ���̊֐��̈Ӗ�
 *	�@CharSet�֐����ŁA�I�u�W�F�L�����N�^�̃}�b�s���O���[�h�̕ύX�����Ă��܂��Ă��邽�߁A
 *	2D�}�b�s���O���[�h�ŃR���o�[�g�����L�����N�^�f�[�^��1D�œ]������ȂǏo���܂���B
 *	�@�����������邽�߂ɍ��ݒ肳��Ă���}�b�s���O���[�h���L�����N�^�f�[�^�ɐݒ肵�āA
 *	�]������֐����쐬���܂����B
 *
 */
//-----------------------------------------------------------------------------
GLOBAL BOOL CharSetCharModeAdjust( const CHAR_MANAGER_HEADER* pCharData );

//----------------------------------------------------------------------------
/**
 *
 *@brief		�L�����N�^�f�[�^�𕡐��Z�b�g
 *				�}�b�s���O���[�h�����̃��W�X�^��ԂɕύX���郂�[�h
 *
 *@param		pChatData	�L�����N�^�f�[�^�z��
 *@param		num			�z��v�f��
 *
 *@return		�����o�^����������
 */
//-----------------------------------------------------------------------------
GLOBAL u16 CharSetsCharModeAdjust( const CHAR_MANAGER_HEADER* pCharData, int num );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�Ǘ�ID��Vram�ɃL�����N�^�f�[�^��]������
 *
 *	@param	id				�]����̃f�[�^�Ǘ�ID
 *	@param	pCharData		�]������L�����N�^�f�[�^
 *
 *	@return	none
 *
 * �L�����N�^�f�[�^�̃T�C�Y���ꏏ�ł���K�v������܂�
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void CharDataChg( int id, NNSG2dCharacterData* pCharData );

//----------------------------------------------------------------------------
/**
 *
 *@brief	id�̃L�����N�^�f�[�^�������o�^����Ă��邩�`�F�b�N
 *
 *@param	id		�`�F�b�N����id
 *
 *@retval	TRUE	�o�^����Ă���
 *@retval	FALSE	�o�^����Ă��Ȃ�
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL BOOL CheckCharID(int id);

//----------------------------------------------------------------------------
/**
 *
 *@brief	���Ƃ����o�^�ł���̂���Ԃ�
 *
 *@param	none
 *
 *@return	int		�c��o�^�\��
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL int CheckCharRest(void);

//----------------------------------------------------------------------------
/**
 *
 *@brief	�L�����N�^�f�[�^��j��
 *
 *@param	�L�����N�^�f�[�^ID
 *
 *@return	none
 */
//-----------------------------------------------------------------------------
GLOBAL void DelChar( int id );

//----------------------------------------------------------------------------
/**
 *
 *@brief	�S�L�����N�^�f�[�^��j��
 *
 *@param	none
 *
 *@return	none
 */
//-----------------------------------------------------------------------------
GLOBAL void DelCharAll( void );

//----------------------------------------------------------------------------
/**
 *
 *@brief	ID�̃C���[�W�v���N�V���擾
 *
 *@param	�L�����N�^�f�[�^ID
 *
 *@return	ID�̃v���N�V
 */
//-----------------------------------------------------------------------------
GLOBAL NNSG2dImageProxy* GetCharIDProxy( int id );

//----------------------------------------------------------------------------
/**
 *
 *@brief	�v���N�V�̃L�����N�^�f�[�^���擾
 *
 *@param	pImage�F�C���[�W�v���N�V�|�C���^
 *
 *@return	�L�����N�^�f�[�^
 */
//-----------------------------------------------------------------------------
GLOBAL NNSG2dCharacterData* GetCharIDData( const NNSG2dImageProxy* pImage );

//----------------------------------------------------------------------------
/**
 *
 *@brief	�Z��Vram�]���A�j���[�V�����p�̃L�����N�^�v���N�V���擾
 *
 *@param	id		�L�����N�^�f�[�^ID
 *@param	szByte	�g�p�T�C�Y
 *
 *@return	�C���[�W�v���N�V
 *@return	NULL		���s
 *	
 *	NULL���A�����Ƃ��̓I���W�i���f�[�^���g�p���Ƃ������ƂȂ̂ŁA�R�s�[���쐬���Ă��������B�i���̊֐��j
 *	
 */
//-----------------------------------------------------------------------------
GLOBAL NNSG2dImageProxy* GetCharVramTransData( int id, u32 szByte );

//----------------------------------------------------------------------------
/**
 *
 *@brief	�Z��Vram�]���A�j���[�V�����p�̃L�����N�^�v���N�V���R�s�[���Ď擾
 *
 *@param	Orig	�I���W�i���C���[�W�v���N�V
 *
 *@return	�R�s�[����Vram�]���I�t�Z�b�g���擾�����C���[�W�v���N�V
 *@return	NULL	�I���W�i�����g�p���łȂ��\��������܂��B
 */
//-----------------------------------------------------------------------------
GLOBAL NNSG2dImageProxy* GetCharVramTransProxyCopy( const NNSG2dImageProxy* Orig );

//----------------------------------------------------------------------------
/**
 *
 *@brief	�Z��Vram�]���A�j����Vram�̈���J��
 *
 *@param	pImage�F�j������L�����N�^�̈��
 *			�C���[�W�v���N�V
 *
 *@return	none
 */
//-----------------------------------------------------------------------------
GLOBAL void DelVramTransData( const NNSG2dImageProxy* pImage );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	OBJ�L�����N�^�}�b�s���O���[�h����L�����N�^���E���擾
 *
 *	@param	mode	OBJ�L�����N�^�}�b�s���O���[�h
 *
 *	@return	�L�����N�^���E
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL int CharModeMinNum( int mode );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	NNSG2dCharacterData���g�p���Ȃ��Ƃ���Vram�G���A�m�ۗp
 *
 *	@param	szByte		�L�����N�^�f�[�^�T�C�Y
 *	@param	cont_type	Vram�R���g���[���^�C�v
 *	@param	type		�o�^���
 *	@param	allocData	�m�ۃf�[�^�i�[��
 *
 *	@retval	TRUE	�̈�m�ۂł���
 *	@retval	FALSE	�̈�m�ۂł��Ȃ�����
 *
 *	cont_type
 *		CHARM_CONT_OFFSET	�I�t�Z�b�g�^�C�v
 *		CHARM_CONT_AREACONT	�G���A�R���g���[���^�C�v
 *
 *	type
 *		NNS_G2D_VRAM_TYPE_2DMAIN	���C�����VRAM
 *		NNS_G2D_VRAM_TYPE_2DSUB		�T�u���VRAM
 *
 *		**����ʂ͎w�肵�Ȃ��ł�������
 *
 */
//-----------------------------------------------------------------------------
GLOBAL BOOL CharVramAreaAlloc( int szByte, int cont_type, int type, CHAR_MANAGER_ALLOCDATA* allocData );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	NNSG2dCharacterData���g�p���Ȃ��Ƃ���Vram�G���A�j���p
 *			cont_type = CHARM_CONT_AREACONT�̂Ƃ��悤
 *
 *	@param	allocData	�o�^�f�[�^
 * 
 *	@return	none
 *
 * �I�t�Z�b�g���炵���[�h�Ŋm�ۂ������͉̂���ł��܂���
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void CharVramAreaFree( CHAR_MANAGER_ALLOCDATA* allocData );


//----------------------------------------------------------------------------
/**
 *	@brief	�L�����N�^�}�l�[�W���|�C���^�̎擾
 *
 *	@param	none
 *
 *	@return	�L�����N�^�}�l�[�W���|�C���^
 */
//-----------------------------------------------------------------------------
GLOBAL void* CharManagerPtrGet( void );
//----------------------------------------------------------------------------
/**
 *	@brief	�L�����N�^�}�l�[�W���|�C���^��ݒ�
 *
 *	@param	pdata	�L�����N�^�}�l�[�W���|�C���^
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
GLOBAL void CharManagerPtrSet( void* pdata );

//----------------------------------------------------------------------------
/**
 *					�O���[�o���ϐ��錾
 */
//-----------------------------------------------------------------------------
#undef	GLOBAL
#endif		// __CHAR_MANAGER_H__

