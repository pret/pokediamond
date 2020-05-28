//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *	@file		pltt_manager.h
 *	@brief		�p���b�g�}�l�[�W���[�w�b�_
 *	@author		tomoya takahashi
 *	@data		2004.11.22
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]


#ifndef PLTT_MANAGER_H__
#define	PLTT_MANAGER_H__

#undef	GLOBAL
#ifdef	PLTT_MANAGER_H_GLOBAL
#define	GLOBAL	/* */
#else
#define	GLOBAL	extern
#endif


//-----------------------------------------------------------------------------
/**
 *					�萔�錾
 */
//-----------------------------------------------------------------------------
// �p���b�gVRAM�\��}�X�N
enum{
	PLTTMAN_RESERVE_PLT0  =1 << 0,	
	PLTTMAN_RESERVE_PLT1  =1 << 1,	
	PLTTMAN_RESERVE_PLT2  =1 << 2,	
	PLTTMAN_RESERVE_PLT3  =1 << 3,	
	PLTTMAN_RESERVE_PLT4  =1 << 4,	
	PLTTMAN_RESERVE_PLT5  =1 << 5,	
	PLTTMAN_RESERVE_PLT6  =1 << 6,	
	PLTTMAN_RESERVE_PLT7  =1 << 7,	
	PLTTMAN_RESERVE_PLT8  =1 << 8,	
	PLTTMAN_RESERVE_PLT9  =1 << 9,	
	PLTTMAN_RESERVE_PLT10  =1 << 10,	
	PLTTMAN_RESERVE_PLT11  =1 << 11,	
	PLTTMAN_RESERVE_PLT12  =1 << 12,	
	PLTTMAN_RESERVE_PLT13  =1 << 13,	
	PLTTMAN_RESERVE_PLT14  =1 << 14,	
	PLTTMAN_RESERVE_PLT15  =1 << 15,	
};

//-----------------------------------------------------------------------------
/**
 *					�\���̐錾
 */
//-----------------------------------------------------------------------------
//-------------------------------------
//	
//	�p���b�g�f�[�^�w�b�_�[
//	
//=====================================
typedef struct {
	NNSG2dPaletteData*	res_file;		// �p���b�g���\�[�X
	u32		type;			// VramType
							// main�ɓo�^�FNNS_G2D_VRAM_TYPE_2DMAIN
							// sub�ɓo�^ �FNNS_G2D_VRAM_TYPE_2DSUB
							// �����ɓo�^�FNNS_G2D_VRAM_TYPE_2DMAX
	u32		pltt_num;		// �o�^�i�f�[�^�]������j�p���b�g��
	u32		id;				// �p���b�gID
} PLTT_MANAGER_HEADER;



//----------------------------------------------------------------------------
/**
 *					�v���g�^�C�v�錾
 */
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *
 *@brief	�p���b�g�}�l�[�W���[������
 *
 *@param	PlttDataNum		�p���b�g���䐔
 *@param	heap			�g�p�q�[�v
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void InitPlttManager(int PlttDataNum, int heap);

//----------------------------------------------------------------------------
/**
 *	@brief	CleanArea�֐��g�p�֎~�p���b�g�ݒ�
 *
 *	@param	msk		�g�p�֎~�p���b�g�}�X�N
 *	@param	disp	���
 *
 *	@return	none
 *
 *	disp
 *		main�ɓo�^�FNNS_G2D_VRAM_TYPE_2DMAIN = 1
 *		sub�ɓo�^ �FNNS_G2D_VRAM_TYPE_2DSUB = 2
 *
 *	�}�X�N�萔
	// �p���b�gVRAM�\��}�X�N
	PLTTMAN_RESERVE_PLT0  =1 << 0,	
	PLTTMAN_RESERVE_PLT1  =1 << 1,	
	PLTTMAN_RESERVE_PLT2  =1 << 2,	
	PLTTMAN_RESERVE_PLT3  =1 << 3,	
	PLTTMAN_RESERVE_PLT4  =1 << 4,	
	PLTTMAN_RESERVE_PLT5  =1 << 5,	
	PLTTMAN_RESERVE_PLT6  =1 << 6,	
	PLTTMAN_RESERVE_PLT7  =1 << 7,	
	PLTTMAN_RESERVE_PLT8  =1 << 8,	
	PLTTMAN_RESERVE_PLT9  =1 << 9,	
	PLTTMAN_RESERVE_PLT10  =1 << 10,	
	PLTTMAN_RESERVE_PLT11  =1 << 11,	
	PLTTMAN_RESERVE_PLT12  =1 << 12,	
	PLTTMAN_RESERVE_PLT13  =1 << 13,	
	PLTTMAN_RESERVE_PLT14  =1 << 14,	
	PLTTMAN_RESERVE_PLT15  =1 << 15,	


 *	�ʐM�pOAM�\���p�p���b�g�̈�̊m�ۂȂǂɎg�p���Ă��������B
 *
 *	���g�p�㒍��
	GLOBAL void PlttLoadStartAll( void );
	GLOBAL void PlttLoadStart( u32 start_offset );
	GLOBAL void PlttLoadStartSub( u32 start_offset );
	GLOBAL void PlttLoadStartEx( u32 start_offset );
	GLOBAL void PlttLoadStartSubEx( u32 start_offset );
 *	���g�p������ɂ��̐ݒ�����Ă��������B
 *	��̂T�̊֐��̒��ŁA�֎~�̈�̏��������s���Ă��܂��܂�
 */
//-----------------------------------------------------------------------------
GLOBAL void SetReserveCleanAreaPlttManager( u16 msk, u32 disp );


//----------------------------------------------------------------------------
/**
 *
 *@brief	�p���b�g�}�l�[�W���[�j��
 *
 *@param	none
 *
 *@return	none
 *
 * ������Ăׂ΂ǂ�ȏ�Ԃł����S�ɔj������܂��B
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void DeletePlttManager(void);

//----------------------------------------------------------------------------
/**
 *
 *@brief	���[�h���J�n����֐�
 *
 *@param	start_offset�F�ǂݍ��݊J�noffset
 *
 *@return	none
 *	(�����Ǘ��̃I�t�Z�b�g��������)
 */
//-----------------------------------------------------------------------------
GLOBAL void PlttLoadStart( u32 start_offset );						// ���C����ʃp���b�g
GLOBAL void PlttLoadStartSub( u32 start_offset );					// �T�u��ʃp���b�g
GLOBAL void PlttLoadStartEx( u32 start_offset );					// ���C����ʊg���p���b�g
GLOBAL void PlttLoadStartSubEx( u32 start_offset );					// �T�u��ʊg���p���b�g

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�p���b�g���Ǘ����Ă�������I�t�Z�b�g�l���擾����
 *
 *	@param	none 
 *
 *	@return	int		�I�t�Z�b�g�l
 *
 *
 */
//-----------------------------------------------------------------------------
/// ���C����ʁ@�W���p���b�g
GLOBAL int PlttLoadOffsetGetMain( void );
	
/// �T�u��ʁ@�W���p���b�g
GLOBAL int PlttLoadOffsetGetSub( void );

/// ���C����ʁ@�g���p���b�g
GLOBAL int PlttLoadOffsetGetMainEx( void );

/// �T�u��ʁ@�g���p���b�g
GLOBAL int PlttLoadOffsetGetSubEx( void );

//----------------------------------------------------------------------------
/**
 *
 *@brief	���[�h���J�n����֐�
 *
 *@param	none
 *
 *@return	none
 *	�S�ẴI�t�Z�b�g���O�ŏ�����
 */
//-----------------------------------------------------------------------------
GLOBAL void PlttLoadStartAll( void );

// �r�b�g���`�F�b�N����
// ���󂢂Ă���ꏊ�ɓ]�����܂��B
//----------------------------------------------------------------------------
/**
 *@brief	�p���b�g�f�[�^�P�̂��Z�b�g���ă��[�h
 *
 *@param	pPlttData�F�p���b�g�f�[�^
 *
 *@retval	TRUE �F�Z�b�g�ł���
 *			FALSE�F�Z�b�g�ł��Ȃ�����
 *
 * �󂢂Ă����Ԃ��r�b�g����ŊǗ����Ă��܂��B
 * ��{���������g�p���Ă��������B
 */
//-----------------------------------------------------------------------------
GLOBAL BOOL PlttSetCleanArea( const PLTT_MANAGER_HEADER* pPlttData );

//----------------------------------------------------------------------------
/**
 *
 *@brief	�p���b�g�f�[�^�𕡐��Z�b�g
 *
 *@param	pPlttData	�p���b�g�f�[�^
 *@param	num			�Z�b�g���鐔
 *
 *@return	�����o�^����������
 * �󂢂Ă����Ԃ��r�b�g����ŊǗ����Ă��܂��B
 * ��{���������g�p���Ă��������B
 */
//-----------------------------------------------------------------------------
GLOBAL u16 PlttSetsCleanArea( const PLTT_MANAGER_HEADER* pPlttData, int num );



//OFFSET���炵�ł��B
//----------------------------------------------------------------------------
/**
 *@brief	�p���b�g�f�[�^�P�̂��Z�b�g���ă��[�h
 *
 *@param	pPlttData�F�p���b�g�f�[�^
 *
 *@retval	TRUE �F�Z�b�g�ł���
 *			FALSE�F�Z�b�g�ł��Ȃ�����
 *
 *	�I�t�Z�b�g���炵�ŁA�ォ�炸�炵�Ȃ���ݒ肵�Ă����܂��B
 *	CleanArea�Ƃ̓����͂��܂���B
 *	�I�t�Z�b�g���炵�̂Ƃ��́A�I�t�Z�b�g���炵�����ł��܂���
 */
//-----------------------------------------------------------------------------
GLOBAL BOOL PlttSet( const PLTT_MANAGER_HEADER* pPlttData );

//----------------------------------------------------------------------------
/**
 *
 *@brief	�p���b�g�f�[�^�𕡐��Z�b�g
 *
 *@param	pPlttData	�p���b�g�f�[�^
 *@param	num			�Z�b�g���鐔
 *
 *@return	�����o�^����������

 *	�I�t�Z�b�g���炵�ŁA�ォ�炸�炵�Ȃ���ݒ肵�Ă����܂��B
 *	CleanArea�Ƃ̓����͂��܂���B
 *	�I�t�Z�b�g���炵�̂Ƃ��́A�I�t�Z�b�g���炵�����ł��܂���
 */
//-----------------------------------------------------------------------------
GLOBAL u16 PlttSets( const PLTT_MANAGER_HEADER* pPlttData, int num );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�p���b�g�f�[�^�]��
 *
 *	@param	id			�]����̃p���b�gID
 *	@param	pPlttData	�p���b�g�f�[�^
 *
 *	@return	none
 *
 *	id�̃p���b�g�̗̈�ɂ�����x�p���b�g�f�[�^��ǂݍ��݂܂�
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void PlttDataChg( int id, NNSG2dPaletteData* pPlttData );

//----------------------------------------------------------------------------
/**
 *
 *@brief	id�̃p���b�g�f�[�^�������o�^����Ă��邩�`�F�b�N
 *
 *@param	id		�`�F�b�N����id
 *
 *@retval	TRUE	�o�^����Ă���
 *@retval	FALSE	�o�^����Ă��Ȃ�
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL BOOL CheckPlttID(int id);

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
GLOBAL int CheckPlttRest(void);

//----------------------------------------------------------------------------
/**
 *
 *@brief	�p���b�g�f�[�^��j
 *
 *@param	id		�p���b�gID
 *	
 *@return	none
 */
//-----------------------------------------------------------------------------
GLOBAL void DelPltt( int id );

//----------------------------------------------------------------------------
/**
 *
 *@brief	�S�p���b�g�f�[�^��j��
 *
 *@param	none
 *
 *@return	none
 */
//-----------------------------------------------------------------------------
GLOBAL void DelPlttAll( void );

//----------------------------------------------------------------------------
/**
 *
 *@brief	ID�̃p���b�g�v���N�V���擾
 *
 *@param	id		�p���b�gID
 *
 *@return	ID�̃v���N�V
 *
 * �g���p���b�g�̎��͂����̊֐����g�p���Ă�������
 * 
 */
//-----------------------------------------------------------------------------
GLOBAL NNSG2dImagePaletteProxy* GetPlttIDProxy( int id );

//----------------------------------------------------------------------------
/**
 *
 *@brief	�p���b�g�v���N�V�̎擾
 *			�p���b�g�̃��[�h�i�g���p���b�g�j�ɃC���[�W�v���N�V���œK������
 *					�p���b�g�v���N�V�擾�֐�
 *
 *@param	id		�p���b�gID
 *@param	ppImage�F�C���[�W�v���N�V
 *
 *@return	�p���b�g�v���N�V
 *
 * �g���p���b�g���g�p����Ƃ��͂������̊֐����g�p���Ă��������B
 * 
 */
//-----------------------------------------------------------------------------
GLOBAL NNSG2dImagePaletteProxy* GetPlttIDProxyJoin( int id, NNSG2dImageProxy* pImage );	
																			// ��ID�̃v���N�V���擾
																			// �C���[�W�v���N�V��
																			// �g���p���b�g���[�h���`�F�b�N����
																			// �œK�ȃ��[�h�ɐݒ肷��擾�֐�

//----------------------------------------------------------------------------
/**
 *
 *@brief	�p���b�gNo�̃v���N�V���擾����
 *
 *@param	pltt_offset�F���̃p���b�g�i���o�[�̃v���N�V����������Ԃ�
 *@param	type�F�P�U�F�A�g���p���b�g���̃t���O()
 *@param	vramType�F�p���b�g�i���o�[�����킹��Vram�̃^�C�v		�P�F���C���@�Q�F�T�u
 *
 *@retval	���������v���N�V
 *@retval	������Ȃ��Ƃ���NULL
 *
 * �C���[�W�v���N�V�̃I�t�Z�b�g�A�h���X��ύX���āA�����I�ɈႤ�p���b�g��
 * �Q�Ƃ���悤�ɂ��܂��B
 * 
 */
//-----------------------------------------------------------------------------
GLOBAL NNSG2dImagePaletteProxy* GetPlttNumProxy( u32 pltt_offset, u32 type, u32 vramType );

//----------------------------------------------------------------------------
/**
 *
 *@brief	�p���b�g�v���N�V�̂���p���b�g�i���o�[���擾����
 *
 *@param	pPltt�F�p���b�g�i���o�[���擾����p���b�g�v���N�V
 *@param	vramType�F���C���ʂ��T�u�ʂ�
 *
 *@return	�p���b�g�i���o�[
 *
 *	���̃v���N�V�����{�ڂ̃p���b�g���Q�Ƃ��Ă���̂����擾���܂��B
 */
//-----------------------------------------------------------------------------
GLOBAL u32 GetPlttProxyOffset( const NNSG2dImagePaletteProxy* pPltt, u32 vramType  );


//----------------------------------------------------------------------------
/**
 *
 *@brief �����삳��Ă���p���b�g�v���N�V�̒��Ɉ����̃v���N�V�����邩��������
 *
 *@param	pPltt	��������v���N�V
 *
 *@return	BOOL	TRUE	���� FALSE �Ȃ�
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL BOOL SearchPlttProxy( const  NNSG2dImagePaletteProxy* pPltt);


//----------------------------------------------------------------------------
/**
 *					�O���[�o���ϐ��錾
 */
//-----------------------------------------------------------------------------

#undef	GLOBAL
#endif

