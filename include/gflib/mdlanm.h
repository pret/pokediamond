/**
 *	@file	mdlanm.h
 *	@biref	�ėp3D���f���A�j���[�V�������\�[�X�Ǘ��⏕���C�u����
 *	@author	Miyuki Iwasawa
 *	@date	05.11.09
 */

#ifndef _MODEL_ANIME_H_
#define _MODEL_ANIME_H_

typedef enum{
	AMTYPE_SELF,
	AMTYPE_AUTO,
	AMTYPE_AUTOLOOP,
}MDLANM_TYPE;

#define MDLANM_DATA_NULL	(-1)

typedef struct _MDLANM_DATA{
	s16	no;			///<No
	u16	type;		///<�A�j���^�C�v
	u16	frame;		///<�t���[��No
	u16	frm_max;	///<�t���[���̍ő吔

	u16	valid:1;	///<�L���t���O
	u16	stop_f:1;	///<�A�j���X�g�b�v�t���O
	u16	end_f:1;	///<�A�j���I�������m����t���O
	u16	roop_f:1;	///<���[�v�ݒ������t���O
	u16	dmy:4;		///<�_�~�[
	u16	connect:8;	///<�A�j���R�l�N�g�J�E���g

	NNSG3dAnmObj*	pAnmObj;	///<�A�j���I�u�W�F
	void*	pAnmRes;	///<�A�j�����\�[�X
	void*	pFile;	///<�A�j���t�@�C�����\�[�X
}MDLANM_DATA;

typedef struct _MDLANN_MAN{
	int	dat_num;	///<�f�[�^��
	int	heapID;
	NNSFndAllocator	allocator;	///<�A���P�[�^
	MDLANM_DATA*	pData;	///<�f�[�^�i�[�|�C���^
}MDLANM_MAN;

typedef MDLANM_MAN*	GF_MDLANM_PTR;

/**
 *	@brief	���f���A�j���}�l�[�W��������
 *
 *	@param	num	s16:�m�ۂ������A�j���f�[�^�\���̂̐�
 *	@param	heapID	int:�g�p����q�[�v��ID
 
 *	@return	MDLANM_MAN*:�m�ۂ���MDLANM_MAN�\���̃f�[�^�ւ̃|�C���^
 */
extern MDLANM_MAN* MAnm_Init(s16 num,int heapID);

/**
 *	@brief	���f���A�j���}�l�[�W���G���A���
 *	@param	wk	MDLANM_MAN*:�e���W���[���ŗp�ӂ���MDLANM_MAN�\���̃f�[�^�ւ̃|�C���^
 */
extern void MAnm_End(MDLANM_MAN* wk);

/**
 *	@brief	3D���f���A�j���@���C���R���g���[��
 *
 *	@param	wk	MDLANM_MAN*�@�}�l�[�W���ւ̃|�C���^
 *
 *	���C���V�[�P���X���ŌĂяo���Ă�������	
 */
extern void MAnm_AnimeMain(MDLANM_MAN* wk);

/**
 *	@brief	���f���A�j���z�񂩂�󂫃f�[�^NO��Ԃ�
 *	@param	wk	MDLANM_MAN*:�e���W���[���ŗp�ӂ���MDLANM_MAN�\���̃f�[�^�ւ̃|�C���^
 *
 *	@retval	MDLANM_DATA_NULL:-1	�󂫂��Ȃ�
 *	@retval	����ȊO:�z��̃C���f�b�N�XNO
 */
extern s16	MAnm_SearchNullDataNo(MDLANM_MAN* wk);

/**
 *	@brief	ID����z��̃A�h���X��Ԃ�
 *	@param	wk	MDLANM_MAN*:�e���W���[���ŗp�ӂ���MDLANM_MAN�\���̃f�[�^�ւ̃|�C���^
 *
 *	@retval	NULL	������Ȃ�
 *	@retval	MDLANM_DATA* �\���̃A�h���X
 *
 */
extern MDLANM_DATA* MAnm_SearchDataByID(MDLANM_MAN* wk,s16 no);

/**
 *	@brief	���f���A�j���f�[�^�\���̃N���A
 *
 *	@param	pData	�N���A������MDLANM_DATA�^�\���̃f�[�^�ւ̃|�C���^
 */
extern void MAnm_ClearData(MDLANM_DATA* pData);

/**
 *	@brief	���f���A�j���ǉ�
 *	@param	wk	MDLANM_MAN*:�e���W���[���ŗp�ӂ���MDLANM_MAN�\���̃f�[�^�ւ̃|�C���^
 *	@param	inName	�A�j���f�[�^�t�@�C����
 *	@param	inType	�A�j���[�V�����^�C�v
 *	@param	pModel	�֘A�t���郂�f�����\�[�X
 *	@param	pTex	�֘A�t����e�N�X�`�����\�[�X(�p�^�[���A�j���ȊO�Ȃ�NULL�w���)
 *
 *	@retval	NULL			�A�j���ǉ����s
 *	@retval	MDLANM_DATA*	�A�j���f�[�^�^�\���̂ւ̃|�C���^
 */
extern MDLANM_DATA* MAnm_AddAnime(MDLANM_MAN* wk,const char* inName,const u8 inType,
		NNSG3dResMdl* pModel,NNSG3dResTex* pTex);

/**
 *	@brief	MDLANM_DATA�\���̂̃��\�[�X�����
 *	@param	pData	MDLANM_DATA*�@�A�j���f�[�^�\���̂ւ̃|�C���^
 *	@param	allocator	NNSFncAllocator*�@�}�l�[�W���̃A���P�[�^
 *
 *	@retval	TRUE	�������
 *	@retval FLASE	������s
 */
extern BOOL MAnm_ReleaseAnmData(MDLANM_DATA* pData,NNSFndAllocator* allocator);

/**
 *	@brief	���f���A�j�����(IndexNo ver) 
 *	@param	wk	MDLANM_MAN*:�e���W���[���ŗp�ӂ���MDLANM_MAN�\���̃f�[�^�ւ̃|�C���^
 *	@param	no	����������A�j���f�[�^��IndexNo
 *
 *	@retval	1	�������
 *	@retval 0	������s(�������ׂ����̂�������Ȃ�)
 */
extern BOOL MAnm_ReleaseAnimeByID(MDLANM_MAN* wk,s16 no);

/**
 *	@brief	�A�j���f�[�^�R�l�N�g(�A�h���XVer)
 *
 *	@param	pData	MDLANM_DATA*
 *	@param	render	NNSG3dRenderObj�ւ̃|�C���^
 *
 *	@retval	TRUE	����
 *	@retval FALSE	���s
 */
extern BOOL MAnm_ConnectAnimeByAdrs(MDLANM_DATA* pData,NNSG3dRenderObj* render);

/**
 *	@brief	�A�j���f�[�^�f�B�X�R�l�N�g(�A�h���XVer)
 *
 *	@param	pData	MDLANM_DATA*
 *	@param	render	NNSG3dRenderObj�ւ̃|�C���^
 *
 *	@retval	TRUE	����
 *	@retval FALSE	���s
 */
extern BOOL MAnm_DisconnectAnimeByAdrs(MDLANM_DATA* pData,NNSG3dRenderObj* render);

/**
 *	@brief	�A�j���f�[�^ �t���[��No�Z�b�g(�A�h���XVer)
 *
 *	@param	pData	MDLANM_DATA*
 *	@param	no		�A�j���t���[��No	
 *
 *	@retval	TRUE	����
 *	@retval FALSE	���s
 */
extern BOOL MAnm_SetAnimeFrameByAdrs(MDLANM_DATA* pData,u16 no);












#endif	//_MODEL_ANIME_H_

