//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *@file		clact_util.h
 *@brief	�Z���A�N�^�[�̓o�^���ȒP�ɍs���V�X�e��
 *@author	tomoya takahashi
 *@data		2005.09.02
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
#ifndef __CLACT_UTIL_H__
#define __CLACT_UTIL_H__

#include "nnsys.h"
#include "clact.h"
#include "include/system/clact_util_res.h"
#include "include/system/clact_util_vram.h"

#undef GLOBAL
#ifdef	__CLACT_UTIL_H_GLOBAL
#define	GLOBAL	/* */
#else
#define	GLOBAL	extern
#endif

//-----------------------------------------------------------------------------
/**
 *					�萔�錾
*/
//-----------------------------------------------------------------------------
#define	CLACT_U_HEADER_DATA_NONE	(0xffffffff)	// ��Ƀ}���`�Z���̗L���ɂ��悤

//-------------------------------------
//	�o�C�i���f�[�^����R�[�h
//=====================================
// "n"�}���`�Z���A�}���`�Z���A�j�����K�v�Ȃ��Ƃ��ɐݒ�
#define CLACT_U_HEADER_MAKE_NONE_CODE	(CLACT_U_HEADER_DATA_NONE)	
// "e"�o�C�i���f�[�^�̏I���R�[�h
#define CLACT_U_HEADER_MAKE_END_CODE	(0xfffffffe)


// �ȒP�A�N�^�[�Z�b�g�o�^�p
// �T�u��ʂɃZ�����o���Ƃ��́A"SUB_SURFACE_Y"����̍��W��
// �Z����o�^���Ă��������B
#define	MAIN_SURFACE_X	(0)					// ���C���T�[�t�F�[�X������W
#define MAIN_SURFACE_Y	(0)					// ���C���T�[�t�F�[�X������W
#define SUB_SURFACE_X	(0)					// �T�u�T�[�t�F�[�X������W
#define SUB_SURFACE_Y	(192 << FX32_SHIFT)	// �T�u�T�[�t�F�[�X������W
#define SURFACE_WIDTH	(255 << FX32_SHIFT)	// �T�[�t�F�[�X�T�C�Y
#define	SURFACE_HEIGHT	(192 << FX32_SHIFT)	// �T�[�t�F�[�X�T�C�Y
#define MAIN_SURFACE_Y_INTEGER	(0)
#define SUB_SURFACE_Y_INTEGER	(192)


//-----------------------------------------------------------------------------
/**
 *					�\���̐錾
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	
//	�Z���A�N�^�[�w�b�_�[�e�[�u��
//	
//=====================================
typedef struct _CLACT_HEADER_TBL{
	CLACT_HEADER_PTR tbl;		// �w�b�_�[
	int	tbl_num;			// �w�b�_�[�e�[�u��
} CLACT_HEADER_TBL;

//-------------------------------------
//	
//	�Z���A�N�^�[�w�b�_�[�e�[�u��	
//	
//=====================================
typedef struct _CLACT_HEADER_TBL* CLACT_HEADER_TBL_PTR;


//-------------------------------------
//	
//	�Z���A�N�^�[���[�e�B���e�B
//	�Z���A�N�^�[�w�b�_�[�쐬�o�C�i���f�[�^
//	�i�[�\����
//	
//=====================================
typedef struct {
	u32	char_id;				// �L�����N�^ID
	u32 pltt_id;				// �p���b�gID
	u32 cell_id;				// �Z��ID
	u32 cellanime_id;			// �Z���A�j��ID
	u32 multicell_id;			// �}���`�Z��ID
	u32 multicellanime_id;		// �}���`�Z���A�j��ID
	u32 vram_trans;				// Vram�]���t���O
	u32 bg_priority;			// BG�ʂƂ̗D�揇��
} CLACT_U_HEADER_MAKE_BINDATA;


///////////////////////////////////////////////////////////////////////////////
//
//
//	�ȒP�Z���A�N�^�[�Z�b�g�������p�\����
//
//
///////////////////////////////////////////////////////////////////////////////
//-------------------------------------
//	
//	�ȒP�Z���A�N�^�[�Z�b�g�p�����_���f�[�^
//	
//=====================================
typedef struct{
	NNSG2dRendererInstance	 Rend;		// �����_��
	NNSG2dRenderSurface		surface[2];	// �T�[�t�F�[�X
} CLACT_U_EASYRENDER_DATA;

//-----------------------------------------------------------------------------
/**
 *					�v���g�^�C�v�錾
*/
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *
 *@brief	�Z���A�N�^�[�w�b�_�[���쐬	�i�P�́j
 *
 *@param	tbl					�w�b�_�[�f�[�^�i�[��
 *@param	charID				�L�����N�^�f�[�^ID
 *@param	plttID				�p���b�g�f�[�^ID
 *@param	cellID				�Z���f�[�^ID
 *@param	cellAnmID			�Z���A�j���[�V����ID	"�����Ƃ���CLACT_U_HEADER_DATA_NONE"
 *@param	MultiID				�}���`�Z��ID		"�����Ƃ���CLACT_U_HEADER_DATA_NONE"
 *@param	MultiAnmID			�}���`�Z���A�j��ID	"�����Ƃ���CLACT_U_HEADER_DATA_NONE"
 *@param	vram_trans			Vram�]�����t���O
 *@param	priority			BG�Ƃ̗D�揇��
 *@param	charResMan			�L�����N�^�f�[�^���i�[����Ă郊�\�[�X�}�l�[�W��
 *@param	plttResMan			�p���b�g�f�[�^���i�[����Ă��郊�\�[�X�}�l�[�W��
 *@param	cellResMan			�Z���f�[�^���i�[����Ă��郊�\�[�X�}�l�[�W��
 *@param	cellAnmResMan		�Z���A�j���f�[�^���i�[����Ă��郊�\�[�X�}�l�[�W��	"�����Ƃ���NULL"
 *@param	multiCellResMan		�}���`�Z���f�[�^���i�[����Ă��郊�\�[�X�}�l�[�W��	"�����Ƃ���NULL"
 *@param	multiCellAnmResMan	�}���`�Z���A�j���f�[�^���i�[����Ă��郊�\�[�X�}�l�[�W��	"�����Ƃ���NULL"

 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void CLACT_U_MakeHeader(CLACT_HEADER_PTR tbl, int charID, int plttID, int cellID,
		int cellAnmID, int MultiID, int MultiAnmID, int vram_trans, int priority,
		CLACT_U_RES_MANAGER_PTR charResMan,
		CLACT_U_RES_MANAGER_PTR plttResMan,
		CLACT_U_RES_MANAGER_PTR cellResMan,
		CLACT_U_RES_MANAGER_PTR cellAnmResMan,
		CLACT_U_RES_MANAGER_PTR multiCellResMan,
		CLACT_U_RES_MANAGER_PTR multiCellAnmResMan);

//----------------------------------------------------------------------------
/**
 *
 *@brief	�w�b�_�[�̃��������������O�ɁA�w�b�_�[���̃f�[�^�Ŋm�ۂ�����������j������
 *
 *@param	tbl		���g�̃f�[�^��j������w�b�_�[
 *
 *@return	none
 *
 * Vram�]���p�Ɋm�ۂ���Vram�̈��j������
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void CLACT_U_DeleteInHeaderVramTransferArea(CLACT_HEADER_PTR tbl);

//----------------------------------------------------------------------------
/**
 *
 *@brief	�Z���A�N�^�[�w�b�_�[�e�[�u������������ǂݍ���	�i�����j
 *
 *@param	path				�p�X
 *@param	heap				�q�[�v
 *@param	charResMan			�L�����N�^�f�[�^���i�[����Ă郊�\�[�X�}�l�[�W��
 *@param	plttResMan			�p���b�g�f�[�^���i�[����Ă��郊�\�[�X�}�l�[�W��
 *@param	cellResMan			�Z���f�[�^���i�[����Ă��郊�\�[�X�}�l�[�W��
 *@param	cellAnmResMan		�Z���A�j���f�[�^���i�[����Ă��郊�\�[�X�}�l�[�W��
 *@param	multiCellResMan		�}���`�Z���f�[�^���i�[����Ă��郊�\�[�X�}�l�[�W��
 *@param	multiCellAnmResMan	�}���`�Z���A�j���f�[�^���i�[����Ă��郊�\�[�X�}�l�[�W��
 *
 *@return	CLACT_HEADER_TBL_PTR	�w�b�_�[�̃e�[�u�����i�[�����\���̂̃|�C���^
 *									�A�N�Z�X�֐��ŌX�̃w�b�_�[���擾���邱�Ƃ��o���܂��B
 *
 * �w�b�_�[����			"�i���ۂ͉��ɂȂ��Ă��������j"
 *	�L�����N�^ID,		�i���\�[�X�}�l�[�W���[�Ɗ֘A�t�����ꂽID�j
 *	�p���b�gID,
 *	�Z��ID,
 *	�Z���A�j��ID,
 *	�}���`�Z��ID,		�i�}���`�Z���A�}���`�Z���A�j���������Ƃ���'n'�j
 *	�}���`�Z���A�j��ID,
 *	Vram�]���A�j���m�F�t���O,
 *	BG�ʂƂ̗D��x�i���s�j
 *	���̃e�[�u����������
 *	0,1,0,2,n,n,0,0			��j�������ĕ��ׂ�
 *	1,2,3,2,0,0,1,2
 *	�I���R�[�h
 *	e,e,e,e,e,e,e,e			���̃f�[�^���o�Ă�����I��
 *
 */
//-----------------------------------------------------------------------------
GLOBAL CLACT_HEADER_TBL_PTR CLACT_U_LoadHeaderTbl(const char* path, int heap,
		CLACT_U_RES_MANAGER_PTR charResMan,
		CLACT_U_RES_MANAGER_PTR plttResMan,
		CLACT_U_RES_MANAGER_PTR cellResMan,
		CLACT_U_RES_MANAGER_PTR cellAnmResMan,
		CLACT_U_RES_MANAGER_PTR multiCellResMan,
		CLACT_U_RES_MANAGER_PTR multiCellAnmResMan);

//----------------------------------------------------------------------------
/**
 *
 *@brief	�Z���A�N�^�[�w�b�_�[�e�[�u�����o�C�i���f�[�^����쐬	�i�����j
 *
 *@param	bindata				�o�C�i���f�[�^
 *@param	p_header_tbl		�w�b�_�[�e�[�u��
 *@param	heap				�q�[�v
 *@param	charResMan			�L�����N�^�f�[�^���i�[����Ă郊�\�[�X�}�l�[�W��
 *@param	plttResMan			�p���b�g�f�[�^���i�[����Ă��郊�\�[�X�}�l�[�W��
 *@param	cellResMan			�Z���f�[�^���i�[����Ă��郊�\�[�X�}�l�[�W��
 *@param	cellAnmResMan		�Z���A�j���f�[�^���i�[����Ă��郊�\�[�X�}�l�[�W��
 *@param	multiCellResMan		�}���`�Z���f�[�^���i�[����Ă��郊�\�[�X�}�l�[�W��
 *@param	multiCellAnmResMan	�}���`�Z���A�j���f�[�^���i�[����Ă��郊�\�[�X�}�l�[�W��
 *
 *@return	CLACT_HEADER_TBL_PTR	�w�b�_�[�̃e�[�u�����i�[�����\���̂̃|�C���^
 *									�A�N�Z�X�֐��ŌX�̃w�b�_�[���擾���邱�Ƃ��o���܂��B
 *
 * �o�C�i���f�[�^����		�e�f�[�^2byte���̔z�u�ƂȂ��Ă��܂��B
 *	�L�����N�^ID,		�i���\�[�X�}�l�[�W���[�Ɗ֘A�t�����ꂽID�j
 *	�p���b�gID,
 *	�Z��ID,
 *	�Z���A�j��ID,
 *	�}���`�Z��ID,		�i�}���`�Z���A�}���`�Z���A�j���������Ƃ���'CLACT_U_HEADER_MAKE_NONE_CODE'�j
 *	�}���`�Z���A�j��ID,
 *	Vram�]���A�j���m�F�t���O,
 *	BG�ʂƂ̗D��x
 *	���̃e�[�u����������
 *	0x0000,0x0001,0x0000,0x0002,CLACT_U_HEADER_MAKE_NONE_CODE, CLACT_U_HEADER_MAKE_NONE_CODE, 0,0			<-�P�̃f�[�^
 *	0x0001,0x0002,0x0003,0x0002,0x0000,0x0000,0x0001,0x0002
 *	�I���R�[�h
 *	CLACT_U_HEADER_MAKE_END_CODE, CLACT_U_HEADER_MAKE_END_CODE, CLACT_U_HEADER_MAKE_END_CODE, CLACT_U_HEADER_MAKE_END_CODE, CLACT_U_HEADER_MAKE_END_CODE, CLACT_U_HEADER_MAKE_END_CODE, CLACT_U_HEADER_MAKE_END_CODE, CLACT_U_HEADER_MAKE_END_CODE			���̃f�[�^���o�Ă�����I��	
 *
 */
//-----------------------------------------------------------------------------
GLOBAL CLACT_HEADER_TBL_PTR CLACT_U_MakeHeaderBinary(
		const CLACT_U_HEADER_MAKE_BINDATA* bindata,
		int heap,
		CLACT_U_RES_MANAGER_PTR charResMan,
		CLACT_U_RES_MANAGER_PTR plttResMan,
		CLACT_U_RES_MANAGER_PTR cellResMan,
		CLACT_U_RES_MANAGER_PTR cellAnmResMan,
		CLACT_U_RES_MANAGER_PTR multiCellResMan,
		CLACT_U_RES_MANAGER_PTR multiCellAnmResMan);

//----------------------------------------------------------------------------
/**
 *
 *@brief	�w�b�_�[�e�[�u����j������
 *
 *@param	data	�w�b�_�[�e�[�u��
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void CLACT_U_CLACT_HeaderTblDelete(CLACT_HEADER_TBL_PTR data);


///////////////////////////////////////////////////////////////////////////////
//
//	�ȒP�Z���A�N�^�[�Z�b�g�������֐�
//
//
///////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------
/**
 *
 *@brief	�Z���A�N�^�[�Z�b�g�̊ȒP������
 *
 *@param	work_num	�Z���A�N�^�[�ɐݒ肷��ő�A�N�^�[��
 *@param	data		�Z���A�N�^�[�ȒP�ݒ�Ɏg�p���郌���_�[�f�[�^
 *						(���Ԃ̃|�C���^)
 *@param	heap		�������m�ۂɎg�p����q�[�v��
 *
 *@return	CLACT_SET_PTR	�쐬���ꂽ�Z���A�N�^�[�Z�b�g
 *
 * ���e
 * �������_���̏������A�T�[�t�F�[�X�̐ݒ�Ȃǂ��s��
 *		���C���T�[�t�F�[�X���W	(0,0)
 *		�T�u�T�[�t�F�[�X���W	(0,192*FX32_ONE)
 *		�T�[�t�F�[�X�T�C�Y		(256*FX32_ONE,192*FX32_ONE)
 * ���Z���A�N�^�[�Z�b�g�쐬
 * ���Z���A�N�^�[�Z�b�g�ɏ��������������_����ݒ�
 *
 * �j���͕��ʂ̃Z���A�N�^�[�̔j���֐��ő��v�ł��B
 *
 */
//-----------------------------------------------------------------------------
GLOBAL CLACT_SET_PTR CLACT_U_SetEasyInit( int work_num, CLACT_U_EASYRENDER_DATA* data, int heap );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�����_���[��	���C����ʂ̃T�[�t�F�[�X�ʒu��ݒ�
 *
 *	@param	data	�ȒP�Z���A�N�^�[�Z�b�g�p�����_���f�[�^
 *	@param	x		���C����ʃT�[�t�F�[�X�����W
 *	@param	y		���C����ʃT�[�t�F�[�X�����W
 *
 *	@return	none
 *
 *		�T�[�t�F�[�X�̃T�C�Y�͖�������(256*FX32_ONE,192*FX32_ONE)
 *		�ɂȂ�܂��B
 *
 *	�������T�[�t�F�[�X�T�C�Y��ς���֐����K�v�ɂȂ����Ƃ���
 *	takahashi tomoya �܂ł�낵�����肢�������܂��B
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void CLACT_U_SetMainSurfaceMatrix( CLACT_U_EASYRENDER_DATA* data, fx32 x, fx32 y );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�����_���[��	�T�u��ʂ̃T�[�t�F�[�X�ʒu��ݒ�
 *
 *	@param	data	�ȒP�Z���A�N�^�[�Z�b�g�p�����_���f�[�^
 *	@param	x		�T�u��ʃT�[�t�F�[�X�����W
 *	@param	y		�T�u��ʃT�[�t�F�[�X�����W
 *
 *	@return	none
 *
 *		�T�[�t�F�[�X�̃T�C�Y�͖�������(256*FX32_ONE,192*FX32_ONE)
 *		�ɂȂ�܂��B
 *
 *	�������T�[�t�F�[�X�T�C�Y��ς���֐����K�v�ɂȂ����Ƃ���
 *	takahashi tomoya �܂ł�낵�����肢�������܂��B
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void CLACT_U_SetSubSurfaceMatrix( CLACT_U_EASYRENDER_DATA* data, fx32 x, fx32 y );



//-----------------------------------------------------------------------------
/**
 *
 *		�ʐM�A�C�R�����g�p����A�v���P�[�V�����p
 *		�L�����N�^�}�l�[�W���@�p���b�g�}�l�[�W��
 *		�g�p�֎~�̈�ݒ�֐�
 *
 *	@param	disp	�ݒ���	
 *	@param	mode	�I�u�W�F�}�b�s���OӰ��
 *	disp
 *		main��ʁFNNS_G2D_VRAM_TYPE_2DMAIN = 1
 *		sub��� �FNNS_G2D_VRAM_TYPE_2DSUB = 2
 *
 *	mode
 *		GX_OBJVRAMMODE_CHAR_1D_32K 
 *		GX_OBJVRAMMODE_CHAR_1D_64K 
 *		GX_OBJVRAMMODE_CHAR_1D_128K 
 *
 *	���L�����N�^�}�l�[�W����CharSetAreaCont�n�֐�
 *	  �p���b�g�}�l�[�W����PlttSetCleanArea�n�֐����g�p���Ă��������B
 *	  
 *	�@�I�t�Z�b�g�ړ��Ǘ��̕��ɂ́A���f����Ȃ��悤�ɂȂ��Ă��܂��B
 */
//-----------------------------------------------------------------------------
GLOBAL void CLACT_U_WmIcon_SetReserveAreaCharManager( u32 disp, GXOBJVRamModeChar mode );
GLOBAL void CLACT_U_WmIcon_SetReserveAreaPlttManager( u32 disp );



#undef	GLOBAL
#endif		// __CLACT_UTIL_H__
