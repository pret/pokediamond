//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *	H16/11/08		Tomoya Takahashi
 *
 *	�e�N�X�`���p�^�[���A�j���[�V������Vram�]���A�j���[�V�����ōs��
 *																�V�X�e��
 *
 *	���p����Ƃ��̒���
 *	���̃V�X�e����Vram�]���}�l�[�W���[���g�p���Ă���̂ŁA
 *	���̃V�X�e�����g�p����O��Vram�]���}�l�[�W���[�����������Ă����Ă��������B
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

#ifndef	__VRAM_TRANSFER_ANM_H__
#define	__VRAM_TRANSFER_ANM_H__

#include <nitro.h>
#include <nnsys.h>
#include "texanm_sys.h"


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
//	Vram�A�j���I�u�W�F�f�[�^
//	
//=====================================
typedef struct _ITP_VRAM_ANM* ITP_VRAM_ANM_PTR;

//-------------------------------------
//	
//	Vram�A�j���[�V�����V�X�e���\����
//	
//=====================================
typedef struct _ITP_VRAM_SYS* ITP_VRAM_SYS_PTR;

//----------------------------------------------------------------------------
/**
 *					�v���g�^�C�v�錾
 */
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *
 *@brief	Vram�A�j���[�V�����V�X�e���I�u�W�F�N�g�̍쐬
 *
 *@param	WorkNum		�쐬���[�N��
 *@param	heap		�g�p����q�[�v
 *
 *@return	ITP_VRAM_SYS_PTR		Vram�A�j���[�V�����f�[�^
 */
//-----------------------------------------------------------------------------
extern ITP_VRAM_SYS_PTR initItpVramAnm(int WorkNum, int heap);

//----------------------------------------------------------------------------
/**
 *
 *@brief	Vram�A�j���[�V�����V�X�e���I�u�W�F�N�g�̔j��
 *
 *@param	pDat		Vram�A�j���[�V�����f�[�^
 *
 *@return	none
 */
//-----------------------------------------------------------------------------
extern void destItpVramAnm(ITP_VRAM_SYS_PTR pDat);

//----------------------------------------------------------------------------
/**
 *
 *@brief	Vram�A�j���[�V������ǉ�
 *
 *@param	pDat		Vram�A�j���[�V�����f�[�^
 *@param	cp_anmtbl	�A�j���[�V�����e�[�u��
 *@param	cp_tex		�]���e�N�X�`���f�[�^
 *@param	texKey		�e�N�X�`���L�[
 *@param	plttKey		�p���b�g�L�[
 *@param	c_frame		���݃t���[���l
 *
 *@return	ITP_VRAM_ANM_PTR	Vram�A�j���I�u�W�F
 */
//-----------------------------------------------------------------------------
extern ITP_VRAM_ANM_PTR addItpVramAnm( ITP_VRAM_SYS_PTR pDat, const TEXANM_DATATBL* cp_anmtbl, const NNSG3dResTex* cp_tex, NNSGfdTexKey texKey, NNSGfdPlttKey plttKey, const fx32 c_frame );

//----------------------------------------------------------------------------
/**
 *
 *@brief	Vram�A�j���[�V�������폜
 *
 *@param	pDat	Vram�A�j���[�V�����f�[�^
 *@param	pAnmObj	�폜����A�j���[�V�����̃A�j���[�V�����I�u�W�F
 *	
 *@return	none	
 */
//-----------------------------------------------------------------------------
extern	void remItpVramAnm( ITP_VRAM_ANM_PTR pAnmObj );

//----------------------------------------------------------------------------
/**
 *
 *@brief	�SVram�A�j���[�V�������폜
 *
 *@param	pDat	Vram�A�j���[�V�����f�[�^
 *	
 *@return	none
 *	
 */
//-----------------------------------------------------------------------------
extern	void remItpVramAnmAll( ITP_VRAM_SYS_PTR pDat );

//----------------------------------------------------------------------------
/**
 *
 *@brief	�]�������s����
 *
 *@param	obj		�]������f�[�^
 *@param	c_frame	���݃t���[����
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
extern void transItpVramAnm( ITP_VRAM_ANM_PTR obj, const fx32 c_frame );

//----------------------------------------------------------------------------
/**
 *
 *@brief	�e�N�X�`�����\�[�X�ƃe�N�X�`���h�c����e�N�Z���J�n�A�h���X���m�肷��
 *
 *@param	inResTex�F�e�N�X�`�����\�[�X
 *@param	inIndex �F�e�N�X�`���h�c
 *
 *@return	void*	: �A�h���X
 *
 */
//-----------------------------------------------------------------------------
extern void* GetTexStartAdr(NNSG3dResTex *inResTex, const u8 inIndex);
extern void* GetPlttStartAdr(NNSG3dResTex *inResTex, const u8 inIndex);

//----------------------------------------------------------------------------
/**
 *
 *@brief	�e�N�X�`�����\�[�X�ƃe�N�X�`���h�c����e�N�Z���J�nVRAM�A�h���X���m�肷��
 *
 *@param	inResTex�F�e�N�X�`�����\�[�X
 *@param	inIndex �F�e�N�X�`���h�c
 *
 *@return	void*	: �A�h���X
 *
 */
//-----------------------------------------------------------------------------
extern void* GetTexStartVRAMAdr(NNSG3dResTex *inResTex, const u8 inIndex);
extern void* GetTexStartVRAMAdrByName(NNSG3dResTex *inResTex, const char *name);

//----------------------------------------------------------------------------
/**
 *
 *@brief	�e�N�X�`�����\�[�X�ƃe�N�X�`���h�c����e�N�X�`���T�C�Y���m�肷��
 *
 *@param	inResTex�F�e�N�X�`�����\�[�X
 *@param	inIndex �F�e�N�X�`���h�c
 *
 *@return	int	: �e�N�X�`���T�C�Y
 *
 */
//-----------------------------------------------------------------------------
extern int GetTexByteSize(NNSG3dResTex *inResTex, const u8 inIndex);
extern int GetTexByteSizeByName(NNSG3dResTex *inResTex, const char *name);


#endif // __VRAM_TRANSFER_ANM_H__
