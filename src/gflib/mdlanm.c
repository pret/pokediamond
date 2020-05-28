/**
 *	@file	mdlanm.c
 *	@brief	�ėp3D���f���A�j���[�V�������\�[�X�Ǘ��⏕���C�u����
 *	@author	Miyuki Iwasawa
 *	@date	05.11.09
 */

#include "common.h"
#include "gflib/heapsys.h"
#include "gflib/mdlanm.h"

//�v���g�^�C�v
static void* SMAnm_LoadAnmFile(MDLANM_DATA* pData,const char* path,int heapID);

/**
 *	@brief	���f���A�j���}�l�[�W��������
 *
 *	@param	num	s16:�m�ۂ������A�j���f�[�^�\���̂̐�
 *	@param	heapID	int:�g�p����q�[�v��ID
 
 *	@return	MDLANM_MAN*:�m�ۂ���MDLANM_MAN�\���̃f�[�^�ւ̃|�C���^
 */
MDLANM_MAN* MAnm_Init(s16 num,int heapID) 
{
	MDLANM_MAN* wk = NULL;
	u16	i;

	wk = sys_AllocMemory(heapID,sizeof(MDLANM_MAN));
	if(wk == NULL){
		return NULL;
	}
	memset(wk,0,sizeof(MDLANM_MAN));

	wk->dat_num = num;
	wk->heapID = heapID;
	wk->pData = sys_AllocMemory(heapID,sizeof(MDLANM_DATA)*wk->dat_num);
	if(wk->pData == NULL){
		sys_FreeMemoryEz(wk);
		return NULL;
	}

	//�f�[�^�̈揉����
	for(i = 0;i < wk->dat_num;i++){
		MAnm_ClearData(&wk->pData[i]);
	}
	
	//�A���P�[�^������
	sys_InitAllocator(&wk->allocator,heapID,4);

	return wk;
}

/**
 *	@brief	���f���A�j���}�l�[�W���G���A���
 *	@param	wk	MDLANM_MAN*:�e���W���[���ŗp�ӂ���MDLANM_MAN�\���̃f�[�^�ւ̃|�C���^
 */
void MAnm_End(MDLANM_MAN* wk) 
{
	s16	i;

	for(i = 0;i < wk->dat_num;i++){
		if(!wk->pData[i].valid){
			continue;
		}
		MAnm_ReleaseAnmData(&(wk->pData[i]),&(wk->allocator));
	}
	sys_FreeMemoryEz(wk->pData);
	sys_FreeMemoryEz(wk);
}

/**
 *	@brief	3D���f���A�j���@���C���R���g���[��
 *
 *	@param	wk	MDLANM_MAN*�@�}�l�[�W���ւ̃|�C���^
 *
 *	���C���V�[�P���X���ŌĂяo���Ă�������	
 */
void MAnm_AnimeMain(MDLANM_MAN* wk)
{
	s16	i = 0;
	MDLANM_DATA* wp;
	if(wk == NULL){
		return;
	}

	for(i = 0;i < wk->dat_num;i++){
		wp = &wk->pData[i];
		if(wp->valid == 0 || wp->end_f == 1 || wp->stop_f == 1){
			continue;
		}
		if(wp->type == AMTYPE_SELF){
			continue;
		}
		wp->pAnmObj->frame = FX32_CONST(wp->frame++);

		if(wp->frame < wp->frm_max){
			continue;
		}
		if(wp->roop_f){
			wp->frame = 0;
		}else{
			wp->end_f = 1;
		}
	}
}

/**
 *	@brief	���f���A�j���z�񂩂�󂫃f�[�^NO��Ԃ�
 *	@param	wk	MDLANM_MAN*:�e���W���[���ŗp�ӂ���MDLANM_MAN�\���̃f�[�^�ւ̃|�C���^
 *
 *	@retval	MDLANM_DATA_NULL:-1	�󂫂��Ȃ�
 *	@retval	����ȊO:�z��̃C���f�b�N�XNO
 *
 */
s16	MAnm_SearchNullDataNo(MDLANM_MAN* wk)
{
	s16	i;

	if(wk->pData == NULL){
		return MDLANM_DATA_NULL;
	}
	for(i = 0;i < wk->dat_num;i++){
		if(!wk->pData[i].valid){
			return i;
		}
	}
	return MDLANM_DATA_NULL;
}
/**
 *	@brief	ID����z��̃A�h���X��Ԃ�
 *	@param	wk	MDLANM_MAN*:�e���W���[���ŗp�ӂ���MDLANM_MAN�\���̃f�[�^�ւ̃|�C���^
 *
 *	@retval	NULL	������Ȃ�
 *	@retval	MDLANM_DATA* �\���̃A�h���X
 *
 */
MDLANM_DATA* MAnm_SearchDataByID(MDLANM_MAN* wk,s16 no)
{
	s16	i;

	if(wk == NULL || wk->pData == NULL){
		return NULL;
	}
	if(no >= wk->dat_num){
		return NULL;
	}
	for(i = 0;i < wk->dat_num;i++){
		if(wk->pData[i].no == no){
			return &(wk->pData[i]);
		}
	}
	return NULL;
}

/**
 *	@brief	���f���A�j���f�[�^�\���̃N���A
 *
 *	@param	pData	�N���A������MDLANM_DATA�^�\���̃f�[�^�ւ̃|�C���^
 */
void MAnm_ClearData(MDLANM_DATA* pData)
{
	pData->no = -1;
	pData->type = 0;
	pData->frame = 0;
	pData->connect = 0;
	pData->valid = 0;
	pData->stop_f = 0;
	pData->end_f = 0;
	pData->pAnmObj = NULL;
	pData->pFile = NULL;
}

/**
 *	@brief	���f���A�j���ǉ�
 *	@param	wk	MDLANM_MAN*:�e���W���[���ŗp�ӂ���MDLANM_MAN�\���̃f�[�^�ւ̃|�C���^
 *	@param	inName	�A�j���f�[�^�t�@�C����
 *	@param	inType	�A�j���[�V�����^�C�v
 *	@param	pModel	�֘A�t���郂�f�����\�[�X
 */
MDLANM_DATA* MAnm_AddAnime(MDLANM_MAN* wk,const char* inName,const u8 inType,
		NNSG3dResMdl* pModel,NNSG3dResTex* pTex)
{
	s16 ret = 0;
	void*	anmRes = NULL;
	MDLANM_DATA* wp = NULL;
	
	ret = MAnm_SearchNullDataNo(wk);
	if(ret == MDLANM_DATA_NULL){
		return NULL;	//�󂫂��Ȃ��̂Œǉ��ł��Ȃ�
	}
	
	wp = &wk->pData[ret];	//�|�C���^�擾
	MAnm_ClearData(wp);	//��U�N���A

	//�t�@�C�����[�h
	anmRes = SMAnm_LoadAnmFile(wp,inName,wk->heapID);
	GF_ASSERT((anmRes != NULL) && "model anime file load failed");

	// �K�v�ʂ̃��������A���P�[�g����B�C�j�V�����C�Y�͕ʓr�K�v�ɂȂ�B
    wp->pAnmObj = NNS_G3dAllocAnmObj(&(wk->allocator),	// �g�p����A���P�[�^���w��
                                     wp->pAnmRes,	// �A�j���[�V�������\�[�X���w��
                                     pModel);		// ���f�����\�[�X���w��
	SDK_NULL_ASSERT(wp->pAnmObj);

	// AnmObj ������������B�W���C���g�A�j���[�V�����ȊO�����l
	//
	NNS_G3dAnmObjInit(	wp->pAnmObj, // �A�j���[�V�����I�u�W�F�N�g�ւ̃|�C���^
						wp->pAnmRes, // �A�j�����\�[�X�ւ̃|�C���^
						pModel,  // NNSG3dResMdl�ւ̃|�C���^
                        pTex);  // NNSG3dResTex�ւ̃|�C���^(�e�N�X�`���p�^�[���A�j���ȊO�Ȃ��NULL�ł��悢)

	wp->frm_max =  (NNS_G3dAnmObjGetNumFrame(wp->pAnmObj) >> FX32_SHIFT);
	wp->type = inType;
	if(wp->type == AMTYPE_AUTOLOOP){
		wp->roop_f = 1;
	}
	//�L���ɂ���
	wp->valid = 1;
	wp->no = ret;
	return wp;
}

/**
 *	@brief	MDLANM_DATA�\���̂̃��\�[�X�����
 *	@param	pData	MDLANM_DATA*�@�A�j���f�[�^�\���̂ւ̃|�C���^
 *	@param	allocator	NNSFncAllocator*�@�}�l�[�W���̃A���P�[�^
 *
 *	@retval	TRUE	�������
 *	@retval FLASE	������s
 */
BOOL MAnm_ReleaseAnmData(MDLANM_DATA* pData,NNSFndAllocator* allocator)
{
	if(pData->connect  != 0){
		//���̃A�j�����R�l�N�g����Ă���I�u�W�F������̂ŉ������ׂ��ł͂Ȃ�
		GF_ASSERT("3D���f���A�j���[�V�������R�l�N�g���ꂽ�܂܂ł�\n");
//		return FALSE;
	}
	
	//�A�j���I�u�W�F���\�[�X���
	NNS_G3dFreeAnmObj(allocator,pData->pAnmObj);
	//�t�@�C�����\�[�X���
	sys_FreeMemoryEz(pData->pFile);

	//�f�[�^�G���A�N���A
	MAnm_ClearData(pData);

	return TRUE;
}

/**
 *	@brief	���f���A�j�����(IndexNo ver) 
 *	@param	wk	MDLANM_MAN*:�e���W���[���ŗp�ӂ���MDLANM_MAN�\���̃f�[�^�ւ̃|�C���^
 *	@param	no	����������A�j���f�[�^��IndexNo
 *
 *	@retval	1	�������
 *	@retval 0	������s(�������ׂ����̂�������Ȃ�)
 */
BOOL MAnm_ReleaseAnimeByID(MDLANM_MAN* wk,s16 no)
{
	MDLANM_DATA* wp;
	
	wp = MAnm_SearchDataByID(wk,no);
	if(wp == NULL){
		return FALSE;	//������Ȃ�
	}
	return MAnm_ReleaseAnmData(wp,&(wk->allocator));
}

/**
 *	@brief	�A�j���f�[�^�R�l�N�g(�A�h���XVer)
 *
 *	@param	pData	MDLANM_DATA*
 *	@param	render	NNSG3dRenderObj�ւ̃|�C���^
 *
 *	@retval	TRUE	����
 *	@retval FALSE	���s
 */
BOOL MAnm_ConnectAnimeByAdrs(MDLANM_DATA* pData,NNSG3dRenderObj* render)
{
	if(pData == NULL || render == NULL){
		return FALSE;
	}
	if(pData->valid == 0){
		return FALSE;
	}
	NNS_G3dRenderObjAddAnmObj(render,pData->pAnmObj);
	pData->connect++;
	return TRUE;
}

/**
 *	@brief	�A�j���f�[�^�f�B�X�R�l�N�g(�A�h���XVer)
 *
 *	@param	pData	MDLANM_DATA*
 *	@param	render	NNSG3dRenderObj�ւ̃|�C���^
 *
 *	@retval	TRUE	����
 *	@retval FALSE	���s
 */
BOOL MAnm_DisconnectAnimeByAdrs(MDLANM_DATA* pData,NNSG3dRenderObj* render)
{
	if(pData == NULL || render == NULL){
		return FALSE;
	}
	if(pData->valid == 0){
		return FALSE;
	}
	NNS_G3dRenderObjRemoveAnmObj(render,pData->pAnmObj);
	pData->connect--;
	return TRUE;
}

/**
 *	@brief	�A�j���f�[�^ �t���[��No�Z�b�g(�A�h���XVer)
 *
 *	@param	pData	MDLANM_DATA*
 *	@param	no		�A�j���t���[��No	
 *
 *	@retval	TRUE	����
 *	@retval FALSE	���s
 */
BOOL MAnm_SetAnimeFrameByAdrs(MDLANM_DATA* pData,u16 no)
{
	if(no > pData->frm_max){
		no = 0;
	}
	pData->frame = no;
	pData->pAnmObj->frame = FX32_CONST(pData->frame);

	return TRUE;
}

/**
 *	@brief	���f���A�j���@�t�@�C�����[�h
 *
 *	@param	MDLANM_DATA*	pData	�A�j����o�^����\���̃A�h���X
 *	@param	const char*		path	�t�@�C���p�X
 *	@param	NNSFndAllocator*	allocator	�A���P�[�^�|�C���^
 *	@param	heapID	�g�p����q�[�vID
 *
 *	@return �擾�����A�j�����\�[�X�ւ̃|�C���^
 */
static void* SMAnm_LoadAnmFile(MDLANM_DATA* pData,const char* path,int heapID)
{
	void* pAnmRes = NULL;

	if(path == NULL){
		return NULL;
	}

	pData->pFile = sys_LoadFile(heapID,path);	
	if(pData->pFile == NULL){
		return NULL;
	}

	//���\�[�X�擾
	pData->pAnmRes = NNS_G3dGetAnmByIdx(pData->pFile,0);
	if(pData->pAnmRes == NULL){
		return NULL;
	}
	
	return pData->pAnmRes;
}
