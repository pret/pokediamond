//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *@file		vram_transfer_anm.c
 *@brief	�e�N�X�`���p�^�[���A�j���[�V������Vram�]���A�j���[�V�����ōs��
 *																�V�X�e��
 *@author	tomoya takahashi
 *@data		2004.11.08
 *
 *	
 *
 *	���p����Ƃ��̒���
 *	���̃V�X�e����Vram�]���}�l�[�W���[���g�p���Ă���̂ŁA
 *	���̃V�X�e�����g�p����O��Vram�]���}�l�[�W���[�����������Ă����Ă��������B
 *
 *	
 *	���X�g�ɃZ�b�g����f�[�^�ɂ���
 *		NNSG3dAnmObj�F�A�j���[�V�����f�[�^�Ƃ��̃A�j���[�V�����g���e�N�X�`�����\�[�X���Z�b�g�������
 *					�@�ŃZ�b�g���܂��B�i�e�N�X�`����Vram�ɓ]�����Ȃ��悤�Ɂj
 *					�@TexKey�ɂ�0x00���Z�b�g���Ă����܂��B
 *
 *		NNSG3dResTex�F�f�t�H���g�̃r���{�[�h�ɃZ�b�g����Ă���P���̊G�̃��\�[�X�ł��B
 *					�@Vram�ɊG�̃f�[�^��]�������Ă�������TexKey���i�[���Ă����Ă��������B
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
#include "vram_transfer_anm.h"
#include "vram_transfer_manager.h"
#include "system.h"
#include "str_tool.h"
#include "gflib_os_print.h"



//-------------------------------------
//
///�@Vram�A�j���[�V�������X�g�\����
//
//-------------------------------------
typedef struct _ITP_VRAM_ANM
{
	const TEXANM_DATATBL* cp_anmtbl;// �A�j���[�V�����f�[�^�e�[�u��
	const NNSG3dResTex*	cp_tex;		// �]���e�N�X�`���f�[�^
	NNSGfdTexKey  texKey;			// �e�N�X�`��VramKey
	NNSGfdPlttKey plttKey;			// �p���b�gVramKey
	
	u8			  oldTexNum;		// �P�O�ɓ]�������e�N�X�`���i���o�[
	u8			  oldPlttNum;		// �P�O�ɓ]�������p���b�g�i���o�[
	
} ITP_VRAM_ANM;


//-------------------------------------
//
//	Vram�A�j���[�V�����V�X�e���\����
//
//=====================================
typedef struct _ITP_VRAM_SYS{
	ITP_VRAM_ANM*	pWork;		// Vram�A�j���[�V�������X�g
	int				WorkNum;	// ���X�g��
} ITP_VRAM_SYS;

//----------------------------------------------------------------------------
/**
 *					�v���g�^�C�v�錾
 */
//-----------------------------------------------------------------------------
// ���C���ŌĂ΂��e���X�g�̃f�[�^������ۂɊG��]������֐�
static void ItpVramAnmMainApp( ITP_VRAM_ANM* pItpData, const u16 c_frame );
// �]������G�̃f�[�^���擾
static void* getGraphicData( ITP_VRAM_ANM* pItpData, const TEXANM_DATA* cp_texdata );
// �]������p���b�g�̃f�[�^���擾
static void* getPalletData( ITP_VRAM_ANM* pItpData, const TEXANM_DATA* cp_texdata );
// �A�j���[�V�����f�[�^���擾
// ���[�N�̏�����
static void cleanItpWork(ITP_VRAM_ANM* work);
// �e�N�X�`���f�[�^�]��
static void trans_tex(ITP_VRAM_ANM* pItpData, const TEXANM_DATA* cp_texdata);
// �p���b�g�f�[�^�]��
static void trans_pltt(ITP_VRAM_ANM* pItpData, const TEXANM_DATA* cp_texdata);

//----------------------------------------------------------------------------
/**
 *					�O���[�o���ϐ��錾
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
ITP_VRAM_SYS_PTR initItpVramAnm(int WorkNum, int heap)
{
	ITP_VRAM_SYS_PTR vl_sys;
	int i;

	// Vram�A�j���[�V�����V�X�e���f�[�^�쐬
	vl_sys = sys_AllocMemory(heap, sizeof(ITP_VRAM_SYS));

	// ���[�N�쐬
	vl_sys->pWork = sys_AllocMemory(heap, sizeof(ITP_VRAM_ANM)*WorkNum);
	vl_sys->WorkNum = WorkNum;
	for(i=0;i<vl_sys->WorkNum;i++){
		cleanItpWork(&vl_sys->pWork[i]);
	}

	return vl_sys;
}

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
void destItpVramAnm(ITP_VRAM_SYS_PTR pDat)
{
	// �S�j��
	remItpVramAnmAll(pDat);

	sys_FreeMemoryEz(pDat->pWork);
	sys_FreeMemoryEz(pDat);
}

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
ITP_VRAM_ANM_PTR addItpVramAnm( ITP_VRAM_SYS_PTR pDat, const TEXANM_DATATBL* cp_anmtbl, const NNSG3dResTex* cp_tex, NNSGfdTexKey texKey, NNSGfdPlttKey plttKey, const fx32 c_frame )
{
	ITP_VRAM_ANM_PTR	p_itp_anm;			// �A�j���[�V�����f�[�^
	u32					pltt_size;			// �p���b�g�]�����s�����̃`�F�b�N
	int					i;					// ���[�v�p
	p_itp_anm = NULL;
	//
	// �f�[�^�������ݗ̈�T��
	//
	for(i=0;i<pDat->WorkNum;i++){
		if(pDat->pWork[i].cp_anmtbl == NULL){
			p_itp_anm = &pDat->pWork[i];
			break;
		}
	}

	if(p_itp_anm == NULL){
		return NULL;
	}
	
	// �e�f�[�^���Z�b�g
	p_itp_anm->cp_anmtbl= cp_anmtbl;		// �A�j���[�V�����f�[�^
	p_itp_anm->cp_tex	= cp_tex;			// �]���e�N�X�`���f�[�^
	p_itp_anm->texKey	= texKey;			// Vram�]���Œ��g������������e�N�X�`���L�[
	p_itp_anm->plttKey	= plttKey;			// Vram�]���Œ��g������������p���b�g�L�[
	p_itp_anm->oldTexNum  = -1;				// �P�O�ɓ]�������e�N�X�`���i���o�[
	p_itp_anm->oldPlttNum = -1;				// �P�O�ɓ]�������p���b�g�i���o�[
	// �P��]��
	// (�����ł́A�p���b�g�ƃe�N�X�`�������]��)
	ItpVramAnmMainApp(p_itp_anm, c_frame >> FX32_SHIFT );

	return p_itp_anm;
}

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
void remItpVramAnm( ITP_VRAM_ANM_PTR pAnmObj )
{
	// �̈���폜
	cleanItpWork(pAnmObj);
}

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
void remItpVramAnmAll( ITP_VRAM_SYS_PTR pDat )
{
	int i;	

	// �SVram�A�j���[�V������j��
	for(i=0;i<pDat->WorkNum;i++){
		cleanItpWork( (pDat->pWork + i) );
	}
}
	
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
void transItpVramAnm( ITP_VRAM_ANM_PTR obj, const fx32 c_frame )
{
	u16	frame_16;		// u16�^�ɂ����Ƃ��̃t���[����

	// �����_�ȉ���؂�̂Ă�
	// u16�^�̃t���[���l���擾
	frame_16 = c_frame >> FX32_SHIFT;	
		
	// �]������
	ItpVramAnmMainApp( obj, frame_16 );
}

/*-----------------------------------------------------------------------------
 *			�v���C�x�[�g�֐��̎��ԕ�
 ----------------------------------------------------------------------------*/
// ���[�N�̏�����
static void cleanItpWork(ITP_VRAM_ANM* work)
{
	work->cp_anmtbl		= NULL;
	work->cp_tex		= NULL;
	work->texKey		= 0;
	work->plttKey		= 0;
	work->oldTexNum		= 0;
	work->oldPlttNum	= 0;
}


//----------------------------------------------------------------------------
/**
 *
 *@brief		���ۂɓ]���������s��
 *			VramKey�̈ʒu�ɍ��̊G�̃f�[�^��]������
 *		�@	AnmObj���獡�̊G�̃i���o�[���擾
 *		�@	Vram�]���^�X�N��o�^����
 *
 *@param	pItpData�FVram�]���A�j���[�V�������s���A�j���f�[�^
 *@param	c_frame	���݃t���[��
 *
 *@return	none
 *
 */
//-----------------------------------------------------------------------------
static void ItpVramAnmMainApp( ITP_VRAM_ANM* pItpData, const u16 c_frame )
{	
	TEXANM_DATA	texdata;	// ���̃t���[���̃e�N�X�`��ID�ƃp���b�gID


	// ���̃A�j���[�V�����f�[�^���擾
	texdata = TEXANM_GetFrameData( pItpData->cp_anmtbl, c_frame );
	
	// �ЂƂO�ɓ]�������e�N�X�`���i���o�[�ƈႤ���`�F�b�N
	if( pItpData->oldTexNum != texdata.tex_idx )
	{
		trans_tex(pItpData, &texdata);
	}

	// �P�O�ɓ]�������p���b�g�i���o�[�ƈႤ���`�F�b�N
	if( pItpData->oldPlttNum != texdata.pltt_idx )
	{
		trans_pltt(pItpData, &texdata);
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�e�N�X�`���f�[�^�]��
 *
 *@param	pItpData	�]���f�[�^
 *@param	cp_texdata	���̃e�N�X�`��no
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void trans_tex(ITP_VRAM_ANM* pItpData, const TEXANM_DATA* cp_texdata)
{
	void*		p_buff;				// �G�̃f�[�^�̃o�b�t�@
	//
	// ���̊G�̃i���o�[�A�G�̃T�C�Y���擾
	//
	p_buff = getGraphicData( pItpData, cp_texdata );


	//
	// �]���^�X�N���Z�b�g
	//
	AddVramTransferManager(
			NNS_GFD_DST_3D_TEX_VRAM,					// �e�N�X�`����]��
			NNS_GfdGetTexKeyAddr( pItpData->texKey ),	// �]����
			p_buff,										// �]���f�[�^
			NNS_GfdGetTexKeySize( pItpData->texKey )	// �]���T�C�Y
			);

	// �]�������e�N�X�`���i���o�[�ۑ�
	pItpData->oldTexNum = cp_texdata->tex_idx;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�p���b�g�f�[�^�]��
 *
 *@param	pItpData	�]���f�[�^
 *@param	cp_texdata	���̃p���b�gno
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void trans_pltt(ITP_VRAM_ANM* pItpData, const TEXANM_DATA* cp_texdata)
{
	void*		p_buff;				// �G�̃f�[�^�̃o�b�t�@
	
	// ���̃p���b�g�f�[�^���擾
	p_buff = getPalletData( pItpData, cp_texdata );

	// �]���^�X�N���Z�b�g
	AddVramTransferManager(
			NNS_GFD_DST_3D_TEX_PLTT,					// �p���b�g��]��
			NNS_GfdGetPlttKeyAddr( pItpData->plttKey ),	// �]����
			p_buff,										// �]���f�[�^
			NNS_GfdGetPlttKeySize( pItpData->plttKey )	// �]���T�C�Y
			);

	// �]�������p���b�g�i���o�[�ۑ�
	pItpData->oldPlttNum = cp_texdata->pltt_idx;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	���̃t���[���̊G�̃f�[�^���擾
 *
 *@param	pItpData�F�A�j���[�V�����f�[�^
 *@param	cp_texdata	���̃t���[���̃e�N�X�`��ID�ƃp���b�gID
 *
 *@return	�]������f�[�^�̃o�b�t�@
 *
 */
//-----------------------------------------------------------------------------
static void* getGraphicData( ITP_VRAM_ANM* pItpData, const TEXANM_DATA* cp_texdata )
{
	/*
	//
	// ���̃t���[���̊G�����Ԗڂ����擾���A�G�̑傫������
	// �G�̃f�[�^�̐擪����̃I�t�Z�b�g���v�Z���o�b�t�@��
	// ���̃|�C���^���Z�b�g����
	//
	
	//
	// ���̃t���[���̊G�̃i���o�[�ƊG�̃T�C�Y���擾����
	//
	// ���̃e�N�X�`��ID�̊G�̃f�[�^���擾
	const NNSG3dResDictTexData* pData = NNS_G3dGetTexDataByIdx( pItpData->cp_tex, cp_texdata->tex_idx );

	// �I�t�Z�b�g�l
	u32 offset = (pData->texImageParam & NNS_G3D_TEXIMAGE_PARAM_TEX_ADDR_MASK);
//	u32 offset = (pData->texImageParam & NNS_G3D_TEXIMAGE_PARAM_TEX_ADDR_MASK) + pItpData->pAnmObj->resTex->texInfo.vramKey;
		
	
	// �������ރf�[�^�̃|�C���^��������
	return (void*)((u8*)pItpData->cp_tex + pItpData->cp_tex->texInfo.ofsTex + (offset << 3) );//*/

	// �R���X�g�����̃��\�[�X�ł����A�������L�����p�̂��߂��̊֐������悤
	return GetTexStartAdr( (NNSG3dResTex*)pItpData->cp_tex, cp_texdata->tex_idx );
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	���̃t���[���̃p���b�g�f�[�^���擾
 *
 *@param	pItpData�F�A�j���[�V�����f�[�^
 *@param	cp_texdata	���̃t���[���̃e�N�X�`��ID�ƃp���b�gID
 *
 *@return	�������ރf�[�^�̃|�C���^
 *
 */
//-----------------------------------------------------------------------------
static void* getPalletData( ITP_VRAM_ANM* pItpData, const TEXANM_DATA* cp_texdata )
{
/*
	//
	// ���̃t���[���̃p���b�g�����Ԗڂ����擾���A�p���b�g�̑傫������
	// �p���b�g�̃f�[�^�̐擪����̃I�t�Z�b�g���v�Z���o�b�t�@��
	// ���̃|�C���^���Z�b�g����
	//
	
	//
	// ���̃t���[���̃p���b�g�̃i���o�[���擾����
	//
	const NNSG3dResDictPlttData* pPlttData = NNS_G3dGetPlttDataByIdx( pItpData->cp_tex, cp_texdata->pltt_idx );
	
	
	//
	// �I�t�Z�b�g�l�̈ʒu����̃f�[�^��]��
	//
	return (void*)((u8*)pItpData->cp_tex + pItpData->cp_tex->plttInfo.ofsPlttData + (pPlttData->offset << 3));
//*/
	// �R���X�g�����̃��\�[�X�ł����A�������L�����p�̂��߂��̊֐������悤
	return GetPlttStartAdr( (NNSG3dResTex*)pItpData->cp_tex, cp_texdata->pltt_idx );
}

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
void* GetTexStartAdr(NNSG3dResTex *inResTex, const u8 inIndex)
{
	u32 offset;
	const NNSG3dResDictTexData* pData = NNS_G3dGetTexDataByIdx( inResTex, inIndex );
	
	if (pData == NULL){
		return NULL;
	}

	// �I�t�Z�b�g�l
	offset = (pData->texImageParam & NNS_G3D_TEXIMAGE_PARAM_TEX_ADDR_MASK) + inResTex->texInfo.vramKey;

	return (void*)((u8*)inResTex + inResTex->texInfo.ofsTex + (offset << 3) );
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�e�N�X�`�����\�[�X�ƃp���b�g�h�c����p���b�g�J�n�A�h���X���m�肷��
 *
 *@param	inResTex�F�e�N�X�`�����\�[�X
 *@param	inIndex �F�p���b�g�h�c
 *
 *@return	void*	: �A�h���X
 *
 */
//-----------------------------------------------------------------------------
void* GetPlttStartAdr(NNSG3dResTex *inResTex, const u8 inIndex)
{
	const NNSG3dResDictPlttData* pPlttData = NNS_G3dGetPlttDataByIdx( inResTex, inIndex );
	
	if (pPlttData == NULL){
		return NULL;
	}
	
	// �I�t�Z�b�g�l�̈ʒu����̃f�[�^��]��
	return (void*)((u8*)inResTex + inResTex->plttInfo.ofsPlttData + (pPlttData->offset << 3));
}


//------------------------------------------------------------------
/**
 * �e�N�Z���J�nVRAM�A�h���X���m�肷�邽�߂̎Z�o�֐�
 *
 * @param   pData		�e�N�X�`���A�h���X�����̂��߂̏��
 *
 * @retval  void*		�e�N�X�`���A�h���X
 */
//------------------------------------------------------------------
static void* GetTexStartVRAMAdrSub(NNSG3dResTex *inResTex,const NNSG3dResDictTexData* pData)
{
	// �I�t�Z�b�g�l
	u32 offset = (pData->texImageParam & NNS_G3D_TEXIMAGE_PARAM_TEX_ADDR_MASK)<<3;
	offset += NNS_GfdGetTexKeyAddr( inResTex->texInfo.vramKey );
	return (void*)(offset);

}
//----------------------------------------------------------------------------
/**
 *
 *@brief	�e�N�X�`�����\�[�X�ƃe�N�X�`��������e�N�Z���J�nVRAM�A�h���X���m�肷��
 *
 *@param	inResTex�F�e�N�X�`�����\�[�X
 *@param	name    �F�e�N�X�`����
 *
 *@return	void*	: �A�h���X
 *
 */
//-----------------------------------------------------------------------------
void* GetTexStartVRAMAdrByName(NNSG3dResTex *inResTex, const char *name)
{
	NNSG3dResName tmpResName;
	const NNSG3dResDictTexData* pData;

	//�e�N�X�`���̎��̂��T�[�`
	SetResName(&tmpResName,name);	//�������NNSG3dResName�ɕϊ�
	pData = NNS_G3dGetTexDataByName( inResTex, &tmpResName );

	if (pData == NULL){
		return NULL;
	}

	//�A�h���X���Z�o
	return GetTexStartVRAMAdrSub(inResTex, pData);
}


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
void* GetTexStartVRAMAdr(NNSG3dResTex *inResTex, const u8 inIndex)
{
	//�e�N�X�`���̎��̂��T�[�`
	const NNSG3dResDictTexData* pData = NNS_G3dGetTexDataByIdx( inResTex, inIndex );
	if (pData == NULL){
		return NULL;
	}
	//�A�h���X���Z�o
	return GetTexStartVRAMAdrSub(inResTex, pData);
}



//----------------------------------------------------------------------------
/**
 *
 *@brief	�e�N�X�`���T�C�Y���m�肷��Z�o�֐�
 *
 *@param	inResTex�F�e�N�X�`�����\�[�X
 *@param	inIndex �FGetTexByteSize & GetTexByteSizeByName����n�����|�C���^
 *
 *@return	int	: �e�N�X�`���T�C�Y
 *
 */
//-----------------------------------------------------------------------------
static int GetTexByteSizeSub(NNSG3dResTex *inResTex, const NNSG3dResDictTexData* pData)
{
	u32 byte_size;
	u32 format;
	u32 t_size,s_size;
	u32 texel_size;
	
	//�t�H�[�}�b�g�𒲂ׂ�
	format = (pData->texImageParam & NNS_G3D_TEXIMAGE_PARAM_TEXFMT_MASK)>>NNS_G3D_TEXIMAGE_PARAM_TEXFMT_SHIFT;
#ifdef VRAM_TRANSFER_ANM_OS_PRINT_ON
	OS_Printf("TEX_FORMAT_IS:%d\n",format);	
#endif
	
	//�t�H�[�}�b�g�ɏ]���A1�e�N�Z�����̃f�[�^�ʂ�����
	switch(format){
	case GX_TEXFMT_PLTT4:
		//4�e�N�Z��1�o�C�g
		texel_size = 4;
		break;
	case GX_TEXFMT_PLTT16:
		//2�e�N�Z��1�o�C�g
		texel_size = 2;
		break;
	case GX_TEXFMT_PLTT256:
		//1�e�N�Z��1�o�C�g
		texel_size = 1;
		break;
	case GX_TEXFMT_A3I5:
		//1�e�N�Z��1�o�C�g
		texel_size = 1;
		break;
	default:
#ifdef VRAM_TRANSFER_ANM_OS_PRINT_ON
		OS_Printf("ERROR:NO_SUPPORT_TEX_FORMAT\n");
#endif
		return 0;
	}
	
	//�e�N�X�`���̉��T�C�Y���擾
	s_size = (pData->texImageParam & NNS_G3D_TEXIMAGE_PARAM_S_SIZE_MASK)>>NNS_G3D_TEXIMAGE_PARAM_S_SIZE_SHIFT;
	s_size <<= 4;
#ifdef VRAM_TRANSFER_ANM_OS_PRINT_ON
	OS_Printf("TEX_S_SIZE_IS:%d\n",s_size);
#endif
	//�e�N�X�`���̏c�T�C�Y���擾
	t_size = (pData->texImageParam & NNS_G3D_TEXIMAGE_PARAM_T_SIZE_MASK)>>NNS_G3D_TEXIMAGE_PARAM_T_SIZE_SHIFT;
	t_size <<= 4;
#ifdef VRAM_TRANSFER_ANM_OS_PRINT_ON
	OS_Printf("TEX_T_SIZE_IS:%d\n",t_size);
#endif
	//�o�C�g�T�C�Y���v�Z
	byte_size = (s_size*t_size)/texel_size;
#ifdef VRAM_TRANSFER_ANM_OS_PRINT_ON
	OS_Printf("TEX_BYTE_SIZE_IS:%d\n",byte_size);
#endif
	
	return byte_size;
}




//==============================================================================
/**
 * �e�N�X�`�����\�[�X�ƃe�N�X�`���h�c����m�肷��
 *
 * @param   inResTex	�e�N�X�`�����\�[�X
 * @param   inIndex		�e�N�X�`���h�c
 *
 * @retval  int			�e�N�X�`���T�C�Y
 */
//==============================================================================
int GetTexByteSize(NNSG3dResTex *inResTex, const u8 inIndex)
{
	
	//�e�N�X�`���̎��̂��T�[�`
	const NNSG3dResDictTexData* pData = NNS_G3dGetTexDataByIdx( inResTex, inIndex );

	//�T�C�Y���Z�o
	return GetTexByteSizeSub(inResTex, pData);

}

//==============================================================================
/**
 * �e�N�X�`�����\�[�X�ƃe�N�X�`��������m�肷��
 *
 * @param   inResTex	�e�N�X�`�����\�[�X	
 * @param   name		�e�N�X�`����
 *
 * @retval  int			�e�N�X�`���T�C�Y
 */
//==============================================================================
int GetTexByteSizeByName(NNSG3dResTex *inResTex, const char *name)
{
	const NNSG3dResDictTexData* pData;
	NNSG3dResName tmpResName;		
	
	SetResName(&tmpResName,name);		//�������NNSG3dResName�ɕϊ�

	//�e�N�X�`���̎��̂��T�[�`
	pData = NNS_G3dGetTexDataByName( inResTex, &tmpResName );

	//�T�C�Y���Z�o
	return GetTexByteSizeSub(inResTex, pData);

}
