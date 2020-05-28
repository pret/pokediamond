#include <string.h>
#include "res_tex.h"
#include "system.h"
#include "str_tool.h"
#include "vram_transfer_manager.h"

//==============================================================================
/**
 * �p���b�g���\�[�X����r
 *
 * @param   const NNSG3dResName* inName
 * @oaram	const char * inTargetName
 *
 * @retval  BOOL		TRUE:��v�@FALSE:�s��v
 */
//==============================================================================
BOOL CmpPaletteName(const NNSG3dResName* inName,const char * inTargetName)
{
	NNSG3dResName	target_name;

	SetResName(&target_name,inTargetName);
	if (inName->val[0] == target_name.val[0] &&
		inName->val[1] == target_name.val[1] &&
		inName->val[2] == target_name.val[2] &&
		inName->val[3] == target_name.val[3]){
		return TRUE;
	}
	
	return FALSE;
}

//==============================================================================
/**
 * �w��e�N�X�`���p���b�g�T�C�Y�̎擾
 *
 * @param   const NNSG3dResTex* inResTex
 * @oaram	const NNSG3dResName *inResName
 *
 * @retval  u32		
 */
//==============================================================================
u32 GetTexPaletteSize(const NNSG3dResTex* inResTex, const NNSG3dResName *inResName)
{
	u8 idx;
	u32 size;
	NNSG3dResDict* dict;
	const NNSG3dResDictPlttData* plttData = NNS_G3dGetPlttDataByName(inResTex, inResName);
	
	size = 0;
	
	if (plttData){
		//�e�N�X�`�����\�[�X���̃p���b�g�G���g�������擾
		dict = (NNSG3dResDict*)((u8*)inResTex + inResTex->plttInfo.ofsDict);

		//�p���b�g������p���b�g�C���f�b�N�X���擾
		idx = NNS_G3dGetPlttIdxByName(inResTex, inResName);
		
		//�]���T�C�Y���v�Z(if����ł�size�́A���ۂ̃T�C�Y��3�r�b�g�E�V�t�g�����l)
		//4colors�Ȃ�]���T�C�Y��4�F���i8�o�C�g�j�ł���
		if (plttData->flag & 1){
			size = 1;
		}
		//���݃G���g�����Ō�̏ꍇ�̓e�N�X�`�����\�[�X��񂪎���
		//���p���b�g�T�C�Y�ƌ��݂̊J�n�A�h���X�Ƃ̍����ŎZ�o
		else if (idx == dict->numEntry-1){
			size = inResTex->plttInfo.sizePltt - plttData->offset;
		}
		else{
			//���̃p���b�g�G���g���̊J�n�A�h���X���擾
			const NNSG3dResDictPlttData* next_plttData = NNS_G3dGetPlttDataByIdx(inResTex, idx+1);
			// �e�N�X�`���u���b�N����p���b�g���ɑΉ�����f�[�^�t�B�[���h�𓾂�
			//��������T�C�Y���v�Z
			size = next_plttData->offset - plttData->offset;
		}
		//3�r�b�g���V�t�g�����l�����ۂ̃T�C�Y�ɂȂ�
		size = (size<<3);
	}
	return size;
}

//==============================================================================
/**
 * �w��e�N�X�`���p���b�g�̕ύX
 *
 * @param	const NNSG3dResTex* inResTex
 * @param   const char * inStr
 *
 * @retval  none		
 */
//==============================================================================
void ChangeTexPalette(const NNSG3dResTex* inResTex, const char * inStr, u16* inPalette)
{
	NNSG3dResName res_name;
	NNSG3dResDict* dict;
	u32 adr;
	u32 size;
    u32 i;
    BOOL result = TRUE;
	
	//���O�Z�b�g
	SetResName(&res_name,inStr);
    
	//�e�N�X�`�����\�[�X���̃p���b�g�G���g�������擾
    dict = (NNSG3dResDict*)((u8*)inResTex + inResTex->plttInfo.ofsDict);
	
    for (i = 0; i < dict->numEntry; ++i)
    {
	    // �e�N�X�`���u���b�N����p���b�g���ɑΉ�����f�[�^�t�B�[���h�𓾂�
	    const NNSG3dResDictPlttData* plttData = NNS_G3dGetPlttDataByName(inResTex, &res_name);
		if (plttData){
			//�p���b�g��������
			if (inResTex->plttInfo.flag & NNS_G3D_RESPLTT_LOADED){//VRAM�Ƀ��[�h����Ă�����]�������s
	        
				u16 plttBase = plttData->offset;
				u16 vramOffset = (u16)(inResTex->plttInfo.vramKey & 0xffff);
			
				adr = (u16)(plttBase + vramOffset);
			
				//�]���T�C�Y���v�Z
				size = GetTexPaletteSize(inResTex, &res_name);
			
				//VRAM�]�����N�G�X�g
				AddVramTransferManager(
						NNS_GFD_DST_3D_TEX_PLTT,									// �p���b�g��]��
						NNS_GfdGetPlttKeyAddr( adr ),	// �]����
						(void*)inPalette,														// �]���f�[�^
						size	// �]���T�C�Y
						);
				return;
			}
		}//endif (plttData)
	}//end for
    return;
}

//==============================================================================
/**
 * �w��e�N�X�`���p���b�g�̎擾�@�����Ń������m�ۂ��Ă���
 *
 * @param   const NNSG3dResTex* inResTex
 *
 * @param   const char *inName
 *
 * @retval  u16*		
 */
//==============================================================================
u16* GetTexPalette(const NNSG3dResTex* inResTex, const char *inName, const int inHeapID)
{
	u8 idx;
	u8 entry;
	void *data;
	u16 *palette;
	u32 size;
	const NNSG3dResDictPlttData* plttData;
	NNSG3dResName res_name;
	NNSG3dResDict* dict;
    NNS_G3D_NULL_ASSERT(inResTex);

	//���O�Z�b�g
	SetResName(&res_name,inName);
	//�e�N�X�`�����\�[�X���̃p���b�g�G���g�������擾
    dict = (NNSG3dResDict*)((u8*)inResTex + inResTex->plttInfo.ofsDict);
	entry = dict->numEntry;

	// �e�N�X�`���u���b�N����p���b�g���ɑΉ�����f�[�^�t�B�[���h�𓾂�
	plttData = NNS_G3dGetPlttDataByName(inResTex, &res_name);
	if (plttData){
		//�p���b�g������C���f�b�N�X���擾
		idx = NNS_G3dGetPlttIdxByName(inResTex,&res_name);
		if (idx < entry){
			//�T�C�Y�擾
			size = GetTexPaletteSize(inResTex,&res_name);
			//size���������m��
			palette = sys_AllocMemory( inHeapID, size );
			//�e�N�X�`���p���b�g�f�[�^
			data = (u8*)inResTex + inResTex->plttInfo.ofsPlttData;
			//�f�[�^���R�s�[
			MI_CpuCopy16(data,palette,size);
			return palette;
		}
	}//end if (plttData)
	return NULL;
}

//==============================================================================
/**
 * �w��e�N�X�`���p���b�g��VRAM�A�h���X�ƃT�C�Y���擾
 *
 * @param   const NNSG3dResTex* inResTex
 *
 * @param   const char *inName
 *
 * @param	void *outAdr				�擾�����u�q�`�l�A�h���X
 *
 * @retval  u32							�p���b�g�T�C�Y
 */
//==============================================================================
u32 GetTexPaletteAdr(const NNSG3dResTex* inResTex, const char *inName, void *outAdr)
{
	NNSG3dResName res_name;
	NNSG3dResDict* dict;
	u32 adr;
	u32 size;
    u32 i;
    BOOL result = TRUE;
	
	size = 0;
	//���O�Z�b�g
	SetResName(&res_name,inName);
    
	//�e�N�X�`�����\�[�X���̃p���b�g�G���g�������擾
    dict = (NNSG3dResDict*)((u8*)inResTex + inResTex->plttInfo.ofsDict);
	
    for (i = 0; i < dict->numEntry; ++i)
    {
	    // �e�N�X�`���u���b�N����p���b�g���ɑΉ�����f�[�^�t�B�[���h�𓾂�
	    const NNSG3dResDictPlttData* plttData = NNS_G3dGetPlttDataByName(inResTex, &res_name);
		if (plttData){
			//�p���b�g��������
			if (inResTex->plttInfo.flag & NNS_G3D_RESPLTT_LOADED){//VRAM�Ƀ��[�h����Ă�����擾
	        
				u16 plttBase = plttData->offset;
				u16 vramOffset = (u16)(inResTex->plttInfo.vramKey & 0xffff);
			
				adr = (u16)(plttBase + vramOffset);
			
				//�T�C�Y���v�Z
				size = GetTexPaletteSize(inResTex, &res_name);
			
				outAdr = (void*)adr;
				return size;
			}
		}//endif (plttData)
	}//end for
	outAdr = NULL;
    return size;
}

//==============================================================================
/**
 * �w��e�N�X�`���T�C�Y�̎擾
 *
 * @param   const NNSG3dResTex* inResTex
 * @oaram	const NNSG3dResName *inResName
 *
 * @retval  u32		
 */
//==============================================================================
u32 GetTexSize(const NNSG3dResTex* inResTex, const NNSG3dResName *inResName)
{
	u8 idx;
	u32 size;
	NNSG3dResDict* dict;
	const NNSG3dResDictTexData* texData = NNS_G3dGetTexDataByName(inResTex, inResName);
	
	size = 0;
	
	if (texData){
		//�e�N�X�`�����\�[�X���̃e�N�X�`���G���g�������擾
		dict = (NNSG3dResDict*)((u8*)inResTex + inResTex->texInfo.ofsDict);

		//�p���b�g������p���b�g�C���f�b�N�X���擾
		idx = NNS_G3dGetTexIdxByName(inResTex, inResName);
		
		//�]���T�C�Y���v�Z(if����ł�size�́A���ۂ̃T�C�Y��3�r�b�g�E�V�t�g�����l)
		//���݃G���g�����Ō�̏ꍇ�̓e�N�X�`�����\�[�X��񂪎���
		//���p���b�g�T�C�Y�ƌ��݂̊J�n�A�h���X�Ƃ̍����ŎZ�o
		if (idx == dict->numEntry-1){
			size = inResTex->texInfo.sizeTex - (texData->texImageParam & NNS_G3D_TEXIMAGE_PARAM_TEX_ADDR_MASK);
		}
		else{
			//���̃p���b�g�G���g���̊J�n�A�h���X���擾
			const NNSG3dResDictTexData* next_texData = NNS_G3dGetTexDataByIdx(inResTex, idx+1);
			// �e�N�X�`���u���b�N����p���b�g���ɑΉ�����f�[�^�t�B�[���h�𓾂�
			//��������T�C�Y���v�Z
			size = (next_texData->texImageParam&NNS_G3D_TEXIMAGE_PARAM_TEX_ADDR_MASK) - (texData->texImageParam&NNS_G3D_TEXIMAGE_PARAM_TEX_ADDR_MASK);
		}
		//3�r�b�g���V�t�g�����l�����ۂ̃T�C�Y�ɂȂ�
		size = (size<<3);
	}
	return size;
}


//�e�N�X�`�����\�[�X����w��e�N�X�`�����̃e�N�X�`���̂u�q�`�l�A�h���X�ƃT�C�Y���擾
u32 GetResTexAdr(const NNSG3dResTex* inResTex, const char *inName, void *outAdr)
{
	NNSG3dResName res_name;
	NNSG3dResDict* dict;
	u32 adr;
	u32 size;
    u32 i;
    BOOL result = TRUE;
	
	size = 0;
	//���O�Z�b�g
	SetResName(&res_name,inName);
    
	//�e�N�X�`�����\�[�X���̃p���b�g�G���g�������擾
    dict = (NNSG3dResDict*)((u8*)inResTex + inResTex->texInfo.ofsDict);
	
    for (i = 0; i < dict->numEntry; ++i)
    {
	    // �e�N�X�`���u���b�N����p���b�g���ɑΉ�����f�[�^�t�B�[���h�𓾂�
	    const NNSG3dResDictTexData* texData = NNS_G3dGetTexDataByName(inResTex, &res_name);
		if (texData){
			//�e�N�X�`����������
			if (inResTex->texInfo.flag & NNS_G3D_RESTEX_LOADED){//VRAM�Ƀ��[�h����Ă�����擾
	        
				u16 texBase = (texData->texImageParam & NNS_G3D_TEXIMAGE_PARAM_TEX_ADDR_MASK);
				u16 vramOffset = (u16)(inResTex->texInfo.vramKey & 0xffff);
			
				adr = (u16)(texBase + vramOffset);
			
				//�T�C�Y���v�Z
				size = GetTexSize(inResTex, &res_name);
			
				outAdr = (void*)adr;
				return size;
			}
		}//endif (plttData)
	}//end for
	outAdr = NULL;
    return size;
}
