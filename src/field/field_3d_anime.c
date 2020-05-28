//=============================================================================
/**
 * @file	field_3d_anime.c
 * @bfief	�t�B�[���h3D�A�j���[�V�����֘A����
 * @author	Nozomu Saito
 *
 */
//=============================================================================

#include "common.h"

#include "field_3d_anime.h"
#include "fieldsys.h"
#include "field_event.h"

#include "map_tool.h"
#include "system/snd_tool.h"	//for SE
#include "system/arc_tool.h"

#include "fielddata/build_model/build_model_id.h"

#define ONE_MODEL_ANM_NUM_MAX	(4)	//�P�̃��f���ɑ΂��čő�S�܂ŃA�j�������Ă�Ƃ���
#define NO_ANIME		(0)
#define NO_ENTRY		(0)
#define ANIME_CONT_MAX	(16)	//16�܂œ����Ǘ�
#define CONT_RENDER_OBJ_MAX	(6)	//�A�j���Ǘ��f�[�^�����Ă�ő僌���_�[�n�a�i��

#define SUICIDE_ANIME_MAX	(2)	//���E�A�j���Ǘ��ő吔

#define ANIME_NONE_CODE		(0xffffffff)

typedef enum{
	STATE_END,	//�I��
	STATE_MOVE,	//�ғ���
}ANIME_STATE;

typedef enum{
	DATA_INVALID,
	DATA_VALID,
}DATA_VAL_STATE;

//���E�A�j���Ǘ��\����
typedef struct SUICIDE_ANIME_DATA_tag
{
	BOOL Valid;						//�f�[�^�L���t���O
	NNSG3dRenderObj *RenderObj;		//�A�j�����K�p����郌���_�[OBJ
	FLD_3D_ANM_DAT_PTR AnimePtr;	//�ΏۃA�j���|�C���^
//	int ObjID;						//OBJID
	int AnimeCode;					//�ΏۃA�j���R�[�h
}SUICIDE_ANIME_DATA;

typedef struct FLD_3D_ANIME_DATA_tag{
	NNSG3dAnmObj* pAnmObj;
	DATA_VAL_STATE Valid;
	int LoopCount;
//	BOOL OneFrameEnd;
//	BOOL *EndFlg;
	int AnimeCode;
	BOOL StopFlg;
	void *pFile;
	int LoopMax;
	ANIME_STATE State;	//
	BOOL Reverse;
	int ControlCode;
}FLD_3D_ANIME_DATA;

typedef struct ANIME_INFO_tag
{
	u8 Flg;			//�A�j�����邩�ǂ���
	u8 Type;		//�A�j���^�C�v
	u8 Suicide;		//���E�t���O
	u8 dummy;		//�_�~�[
	int Code[4];	//�A�j���R�[�h
}ANIME_INFO;

typedef struct FLD_3D_ANIME_MANAGER_tag{
	NNSFndAllocator AnimeAllocator;
	FLD_3D_ANIME_DATA Fld3DAnimeData[FLD_3D_ANIME_MAX];
	SUICIDE_ANIME_DATA SuicideData[SUICIDE_ANIME_MAX];
	ARCHANDLE* AnimeHandle;
	ARCHANDLE* AnmInfoHandle;
}FLD_3D_ANIME_MANAGER;

typedef struct ANIME_DATA_LIST_tag{
	FLD_3D_ANM_DAT_PTR Data[ONE_MODEL_ANM_NUM_MAX];	//�A�j���[�V�����f�[�^���X�g�|�C���^
	int AnimeNum;						//�A�j���[�V�����f�[�^�̐�;
}ANIME_DATA_LIST;

typedef struct ANIME_CONT_tag
{
	ANIME_DATA_LIST	AnimeList;			//�A�j���[�V�����f�[�^���X�g
	NNSG3dRenderObj *RenderObj[CONT_RENDER_OBJ_MAX];			//�A�j�����K�p����郌���_�[OBJ
	FLD_3D_ANM_DAT_PTR BindAnime;			//�o�C���h����Ă���A�j��
	int ObjID;							//OBJID
	u8 EntryID;							//�o�^ID
}ANIME_CONT;

typedef struct ANIME_CONT_MNG_tag
{
	ANIME_CONT AnimeCont[ANIME_CONT_MAX];
}ANIME_CONT_MNG;

typedef struct ANIME_TABLE_tag
{
	int AnimeCode[ONE_MODEL_ANM_NUM_MAX];
}ANIME_TABLE;

//==============================================================================
/**
 * ���E�A�j���G���g���[
 *
 * @param	*ioSuicideData				���E�A�j���Ǘ��\���̂ւ̃|�C���^
 * @param	*objectdata					�Ώۃ����_�[OBJ
 * @param	anime						�A�j���|�C���^
 * @param	inAnimeCode					�ΏۃA�j���R�[�h
 *
 * @return	BOOL	TRUE:���E�ς݂œo�^��	FALSE:�܂������Ă�
 */
//==============================================================================
static BOOL EntrySuicideAnime(	SUICIDE_ANIME_DATA *ioSuicideData,
								NNSG3dRenderObj *objectdata,
								FLD_3D_ANM_DAT_PTR	anime,
								const u8 inAnimeCode	)
{
	int i;
	GF_ASSERT(anime->LoopMax!=LOOP_INFINIT&&"���[�v�񐔂ɐ������������̂́A�ΏۊO�ł�");
	
	//����G���g���[����
	for(i=0;i<SUICIDE_ANIME_MAX;i++){
		if (ioSuicideData[i].Valid){
			if ( (ioSuicideData[i].AnimeCode == inAnimeCode)&&
					(ioSuicideData[i].RenderObj == objectdata) ){
///				OS_Printf("�������̂����łɃG���g������Ă���\n");
				return FALSE;
			}
		}
	}
	//�G���g���[
	for(i=0;i<SUICIDE_ANIME_MAX;i++){
		if (!ioSuicideData[i].Valid){
			ioSuicideData[i].Valid = TRUE;
			ioSuicideData[i].AnimeCode = inAnimeCode;
			ioSuicideData[i].AnimePtr = anime;
			ioSuicideData[i].RenderObj = objectdata;
			break;
		}
	}
	return TRUE;
}


//==============================================================================
/**
 * �A�j���擾
 *
 * @param	inHandle			�A�[�J�C�u�n���h��
 * @param	inID				�A�[�J�C�u�h�c
 * @param	pModel				���f�����\�[�X
 * @param	pAnmObj				�A�j��OBJ
 * @param	pTex				�e�N�X�`��
 * @param	allocator			�A���P�[�^
 *
 * @return	void*				�A�j���|�C���^
 */
//==============================================================================
static void *GetField3DAnimeByArc(	ARCHANDLE *inHandle,
									const u32 inID,
									NNSG3dResMdl* pModel,
									NNSG3dAnmObj** pAnmObj,
									NNSG3dResTex	*pTex,
									NNSFndAllocator *allocator)
{
    void *pAnmRes;
	void *mem = NULL;

	GF_ASSERT(inID != ANIME_NONE_CODE);

	mem = ArchiveDataLoadAllocByHandle( inHandle, inID, HEAPID_FIELD );

	GF_ASSERT(mem != NULL);
    {
        pAnmRes = NNS_G3dGetAnmByIdx(mem, 0);
        GF_ASSERT(pAnmRes != NULL);

        // �K�v�ʂ̃��������A���P�[�g����B�C�j�V�����C�Y�͕ʓr�K�v�ɂȂ�B
        *pAnmObj = NNS_G3dAllocAnmObj(allocator, // �g�p����A���P�[�^���w��
                                     pAnmRes,    // �A�j���[�V�������\�[�X���w��
                                     pModel);    // ���f�����\�[�X���w��
		GF_ASSERT(pAnmObj != NULL);

        //
        // AnmObj ������������B�W���C���g�A�j���[�V�����ȊO�����l
        //
        NNS_G3dAnmObjInit(*pAnmObj, // �A�j���[�V�����I�u�W�F�N�g�ւ̃|�C���^
                          pAnmRes, // �A�j�����\�[�X�ւ̃|�C���^
                          pModel,  // NNSG3dResMdl�ւ̃|�C���^
                          pTex );  // NNSG3dResTex�ւ̃|�C���^(�e�N�X�`���p�^�[���A�j���ȊO�Ȃ��NULL�ł��悢)
		return mem;
    }
}

//==============================================================================
/**
 * �A�j�������[�u
 *
 * @param	inRenderObj				�����_�[OBJ
 * @param	inAnmObj				�A�j��OBJ
 *
 * @return	BOOL				TRUE:�����[�u����	FALSE:�����[�u���Ȃ�����		
 */
//==============================================================================
static const BOOL RemoveAnime(NNSG3dRenderObj *inRenderObj, NNSG3dAnmObj *inAnmObj)
{
	if (inAnmObj == NULL){
		return FALSE;
	}
	if (inRenderObj == NULL){
		return FALSE;
	}

	//���s�ł́A�����[�u����Ώۂ������Ă����̊֐���ʂ�(���̏ꍇ�A�����ł̓����[�u�����ɖ߂�)
	NNS_G3dRenderObjRemoveAnmObj( inRenderObj, inAnmObj );
	return TRUE;
}

//==============================================================================
/**
 * ���E�A�j���Ď�
 *
 * @param	*ioSuicideData				���E�A�j���Ǘ��\���̂ւ̃|�C���^
 * @param	*objectdata					�Ώۃ����_�[OBJ
 * @param	inAnimeCode					�ΏۃA�j���R�[�h
 *
 * @return	none
 */
//==============================================================================
static void SuicideAnimeMain(SUICIDE_ANIME_DATA *ioSuicideData)
{
	int i;
	for(i=0;i<SUICIDE_ANIME_MAX;i++){
		if (ioSuicideData[i].Valid){
			//�A�j���I�����`�F�b�N
			if (F3DA_IsAnimeEnd(ioSuicideData[i].AnimePtr)){
				//�I�����Ă�����A�j���p�[�W
				RemoveAnime(ioSuicideData[i].RenderObj, ioSuicideData[i].AnimePtr->pAnmObj);
				ioSuicideData[i].Valid = FALSE;
				ioSuicideData[i].AnimeCode = 0;
				ioSuicideData[i].AnimePtr = NULL;
				ioSuicideData[i].RenderObj = NULL;
			}
		}
	}
}

//==============================================================================
/**
 * 3D�A�j���}�l�[�W���̃������A���P�[�V����
 *
 * @return	FLD_3D_ANM_MNG_PTR				�A�j���Ǘ��\���̂ւ̃|�C���^
 */
//==============================================================================
FLD_3D_ANM_MNG_PTR F3DA_Field3DAnimeInit(void)
{
	int i;
	FLD_3D_ANM_MNG_PTR field_3d_anime_ptr;
	field_3d_anime_ptr = sys_AllocMemory( HEAPID_FIELD, sizeof(FLD_3D_ANIME_MANAGER) );
	//�󂢂Ă�A�j���z�������
	for(i=0;i<FLD_3D_ANIME_MAX;i++){
		field_3d_anime_ptr->Fld3DAnimeData[i].Valid = DATA_INVALID;
		field_3d_anime_ptr->Fld3DAnimeData[i].StopFlg = FALSE;
		field_3d_anime_ptr->Fld3DAnimeData[i].pAnmObj = NULL;
		field_3d_anime_ptr->Fld3DAnimeData[i].LoopCount = 0;
//		field_3d_anime_ptr->Fld3DAnimeData[i].EndFlg = NULL;
		field_3d_anime_ptr->Fld3DAnimeData[i].AnimeCode = 0;
		field_3d_anime_ptr->Fld3DAnimeData[i].pFile = NULL;
		field_3d_anime_ptr->Fld3DAnimeData[i].LoopMax = LOOP_INFINIT;
		field_3d_anime_ptr->Fld3DAnimeData[i].State = STATE_END;
		field_3d_anime_ptr->Fld3DAnimeData[i].Reverse = FALSE;
		field_3d_anime_ptr->Fld3DAnimeData[i].ControlCode = 0;
	}
	for(i=0;i<SUICIDE_ANIME_MAX;i++){
		field_3d_anime_ptr->SuicideData[i].Valid = FALSE;
		field_3d_anime_ptr->SuicideData[i].RenderObj = NULL;
		field_3d_anime_ptr->SuicideData[i].AnimePtr = NULL;
		field_3d_anime_ptr->SuicideData[i].AnimeCode = 0;
	}
	//�A�j���A���P�[�^
	sys_InitAllocator(&field_3d_anime_ptr->AnimeAllocator,HEAPID_FIELD,4);
	//�A�j���A�[�J�C�u�n���h���I�[�v��
	field_3d_anime_ptr->AnimeHandle = ArchiveDataHandleOpen( ARC_BM_ANM, HEAPID_FIELD );
	//�A�j�����A�[�J�C�u�n���h���I�[�v��
	field_3d_anime_ptr->AnmInfoHandle = ArchiveDataHandleOpen( ARC_BM_ANM_LIST, HEAPID_FIELD );	
//	field_3d_anime_ptr->EndFlg = FALSE;
	return field_3d_anime_ptr;
}


//==============================================================================
/**
 * �A�j��OBJ�擾
 * @param	inFld3DAnmDat			�A�j���f�[�^�|�C���^
 *
 * @return	NNSG3dAnmObj			�A�j��OBJ
 */
//==============================================================================
static NNSG3dAnmObj *GetAnmObj(FLD_3D_ANM_DAT_PTR inFld3DAnmDat)
{
	if (inFld3DAnmDat == NULL){
		return NULL;
	}
	return inFld3DAnmDat->pAnmObj;
}

//==============================================================================
/**
 * �ǉ��ɏ��������邩�ǂ������`�F�b�N
 * @param	inType			�A�j���^�C�v
 *
 * @return	BOOL			TRUE:����	FALSE:�Ȃ�
 */
//==============================================================================
static BOOL CheckAddConditional(const u8 inType)
{
	if ( (inType&0x01) == 0x01 ){
		return TRUE;		//��������
	}else{
		return FALSE;		//��������
	}
}

//==============================================================================
/**
 * �Z�b�g�ɏ��������邩�ǂ������`�F�b�N
 * @param	inType			�A�j���^�C�v
 *
 * @return	BOOL			TRUE:����	FALSE:�Ȃ�
 */
//==============================================================================
static BOOL CheckSetConditional(const u8 inType)
{
	if ( ((inType>>1)&0x01) == 0x01){
		return TRUE;		//��������
	}else{
		return FALSE;		//��������
	}
}

//==============================================================================
/**
 * �A�j���X�e�[�g�̎擾
 *
 * @param	inAnimeData				�A�j���f�[�^�|�C���^
 *
 * @return	int						�A�j���X�e�[�g
 */
//==============================================================================
static int GetAnimeState(const FLD_3D_ANM_DAT_PTR inAnimeData)
{
	GF_ASSERT((inAnimeData->Valid == DATA_VALID)&&"�f�[�^�͖����ł�");
	return inAnimeData->State;
}

//==============================================================================
/**
 * �A�j���[�V�����ǉ�
 *
 * @param	inObjCode				OBJID
 * @param	inAnimeNo				�Đ�����A�j���i���o�[
 * @param	inLoopCount				�J��Ԃ���
 * @param	inCode					����R�[�h
 * @param	inReverse				�t�Đ��t���O
 * @param	inStopFlg				��~�t���O
 * @param	inAnimeType				�ǉ�����A�j���^�C�v
 * @param	objectmodel				���\�[�X���f��
 * @oaram	pTex					�e�N�X�`�����\�[�X�i�e�N�X�`���p�^�[���A�j���p�j
 * @param	field_3d_anime_ptr		�A�j���}�l�[�W���ւ̃|�C���^
 *
 * @return	ANIME_CONT_PTR	�A�j���f�[�^�|�C���^
 */
//==============================================================================
FLD_3D_ANM_DAT_PTR F3DA_AddField3DAnime(const int inObjCode,
										const int inAnimeNo,
										const int inLoopCount,
										const int inCode,
										const BOOL inReverse,
										const BOOL inStopFlg,
										const BOOL inConditional,
										NNSG3dResMdl *objectmodel,
										NNSG3dResTex	*pTex,
										FLD_3D_ANM_MNG_PTR field_3d_anime_ptr)
{
	FLD_3D_ANM_DAT_PTR data;
	int i;
	int anime_code;
	ANIME_INFO info;

	//�w��n�a�i�A�j�������A�[�J�C�o�������
	ArchiveDataLoadByHandle(field_3d_anime_ptr->AnmInfoHandle, inObjCode, &info);

	GF_ASSERT(inAnimeNo<ONE_MODEL_ANM_NUM_MAX);

	anime_code = info.Code[inAnimeNo];
	if (anime_code == ANIME_NONE_CODE){
		return NULL;
	}

	if ( CheckAddConditional(info.Type) != inConditional){
///		OS_Printf("�������������Ă��Ȃ�:%d\n",anime_code);
		return NULL;
	}
	
	//����R�[�h�d���`�F�b�N
	for(i=0;i<FLD_3D_ANIME_MAX;i++){
		if ((inCode != 0)&&
				(field_3d_anime_ptr->Fld3DAnimeData[i].ControlCode == inCode)){
///			OS_Printf("%d:�d���o�^�ł�\n",inCode);
			GF_ASSERT(0);
		}
	}

	//�󂢂Ă�A�j���z�������
	for(i=0;i<FLD_3D_ANIME_MAX;i++){
		if (field_3d_anime_ptr->Fld3DAnimeData[i].Valid == DATA_INVALID){
			field_3d_anime_ptr->Fld3DAnimeData[i].Valid = DATA_VALID;
			field_3d_anime_ptr->Fld3DAnimeData[i].StopFlg = inStopFlg;
			field_3d_anime_ptr->Fld3DAnimeData[i].pAnmObj = NULL;
			field_3d_anime_ptr->Fld3DAnimeData[i].LoopCount = 0;
			//field_3d_anime_ptr->Fld3DAnimeData[i].EndFlg = NULL;
			field_3d_anime_ptr->Fld3DAnimeData[i].AnimeCode = anime_code;
			field_3d_anime_ptr->Fld3DAnimeData[i].Reverse = inReverse;
			field_3d_anime_ptr->Fld3DAnimeData[i].ControlCode = inCode;

			field_3d_anime_ptr->Fld3DAnimeData[i].pFile =
									GetField3DAnimeByArc(	field_3d_anime_ptr->AnimeHandle,
																anime_code,
																objectmodel,
																&field_3d_anime_ptr->Fld3DAnimeData[i].pAnmObj,
																pTex,
																&field_3d_anime_ptr->AnimeAllocator);
			field_3d_anime_ptr->Fld3DAnimeData[i].LoopMax = inLoopCount;
			field_3d_anime_ptr->Fld3DAnimeData[i].State = STATE_MOVE;
			data = &(field_3d_anime_ptr->Fld3DAnimeData[i]);
			//�Đ����������āA�J�n�t���[�����Z�b�g
			F3DA_SetStartFrame(&field_3d_anime_ptr->Fld3DAnimeData[i]);
			return data;
		}
	}
	//�ǉ��ł��Ȃ��ꍇ
	GF_ASSERT(0&&"3D�A�j���ǉ��ł��܂���ł���");
	return NULL;
}

//==============================================================================
/**
 * �A�j���[�V�����ǉ�(�ڍׂȐݒ�͍s��Ȃ��A�풓�A�j���������p)
 *
 * @param	inObjCode				OBJID
 * @param	objectmodel				���\�[�X���f��
 * @oaram	pTex					�e�N�X�`�����\�[�X�i�e�N�X�`���p�^�[���A�j���p�j
 * @param	field_3d_anime_ptr		�A�j���}�l�[�W���ւ̃|�C���^
 *
 * @return	none
 */
//==============================================================================
void F3DA_AddField3DAnimeEasy(	const int inObjCode,
								NNSG3dResMdl *objectmodel,
								NNSG3dResTex	*pTex,
								FLD_3D_ANM_MNG_PTR field_3d_anime_ptr)
{
	int anime_code;
	int n;
	int i;

	ANIME_INFO info;
	//�w��n�a�i�A�j�������A�[�J�C�o�������
	ArchiveDataLoadByHandle(field_3d_anime_ptr->AnmInfoHandle, inObjCode, &info);

	//�A�j�����Ȃ����̂͏������Ȃ�
	if (!info.Flg){
		return;
	}
		
	for(n=0;n<ONE_MODEL_ANM_NUM_MAX;n++){
		anime_code = info.Code[n];
		if (anime_code == ANIME_NONE_CODE){
			return;//�����𔲂���
		}
		
		if ( CheckAddConditional(info.Type) != FALSE){
///				OS_Printf("�������������Ă��Ȃ�:%d\n",anime_code);
				return;
		}

		//�󂢂Ă�A�j���z�������
		for(i=0;i<FLD_3D_ANIME_MAX;i++){
			if (field_3d_anime_ptr->Fld3DAnimeData[i].Valid == DATA_INVALID){
				field_3d_anime_ptr->Fld3DAnimeData[i].Valid = DATA_VALID;
				field_3d_anime_ptr->Fld3DAnimeData[i].StopFlg = FALSE;
				field_3d_anime_ptr->Fld3DAnimeData[i].pAnmObj = NULL;
				field_3d_anime_ptr->Fld3DAnimeData[i].LoopCount = 0;
				//field_3d_anime_ptr->Fld3DAnimeData[i].EndFlg = NULL;
				field_3d_anime_ptr->Fld3DAnimeData[i].AnimeCode = anime_code;
				field_3d_anime_ptr->Fld3DAnimeData[i].Reverse = FALSE;
				field_3d_anime_ptr->Fld3DAnimeData[i].ControlCode = 0;

				field_3d_anime_ptr->Fld3DAnimeData[i].pFile =
										GetField3DAnimeByArc(	field_3d_anime_ptr->AnimeHandle,
																anime_code,
																objectmodel,
																&field_3d_anime_ptr->Fld3DAnimeData[i].pAnmObj,
																pTex,
																&field_3d_anime_ptr->AnimeAllocator);
				field_3d_anime_ptr->Fld3DAnimeData[i].LoopMax = LOOP_INFINIT;
				field_3d_anime_ptr->Fld3DAnimeData[i].State = STATE_MOVE;
				//�Đ����������āA�J�n�t���[�����Z�b�g
				F3DA_SetStartFrame(&field_3d_anime_ptr->Fld3DAnimeData[i]);
	
				//���E�A�j���͊J�n���͂Ƃ߂Ă����i���̂Ƃ���Ώۂ͗����j
				if ( info.Suicide/*(inObjCode == BMID_CY_SLOPE) || (inObjCode == BMID_CY_SLOPE_DUN)*/ ){	
					field_3d_anime_ptr->Fld3DAnimeData[i].StopFlg = TRUE;
					field_3d_anime_ptr->Fld3DAnimeData[i].LoopMax = 1;
				}
				break;//���̓o�^��
			}
		}//end for(i)
		
		//�ǉ��ł��Ȃ��ꍇ
		GF_ASSERT((i!=FLD_3D_ANIME_MAX)&&"3D�A�j���ǉ��ł��܂���ł���");
	}// end for(n)
}

//==============================================================================
/**
 * �A�j���[�V�����Z�b�g
 *
 * @param	inObjCode				OBJID
 * @param	inAnimeNo				�Đ�����A�j���i���o�[
 * @param	objectdata				�����_�[OBJ
 * @param	field_3d_anime_ptr		�A�j���}�l�[�W���ւ̃|�C���^
 *
 * @return	BOOL	TRUE:�Z�b�g�ł���	FALSE:�Z�b�g�ł��Ȃ�����
 */
//==============================================================================
BOOL F3DA_SetFld3DAnime(const int inObjCode,
						const int inAnimeNo,
						const BOOL inConditional,
						NNSG3dRenderObj *objectdata,
						FLD_3D_ANM_MNG_PTR field_3d_anime_ptr)
{
	int i;
	int anime_code;
	ANIME_INFO info;
	
	BOOL rc;
	if (field_3d_anime_ptr==NULL){
		GF_ASSERT_MSG(0,"�A�j���}�l�[�W����NULL�ł�");
		return FALSE;
	}

	if (inObjCode >= F3DA_GetAnimeArcObjNum(field_3d_anime_ptr)){
		return FALSE;
	}
		
	//�w��n�a�i�A�j�������A�[�J�C�o�������
	ArchiveDataLoadByHandle(field_3d_anime_ptr->AnmInfoHandle, inObjCode, &info);

	GF_ASSERT(inAnimeNo<ONE_MODEL_ANM_NUM_MAX);
	
	anime_code = info.Code[inAnimeNo];
	if (anime_code == ANIME_NONE_CODE){
		return FALSE;
	}

	if ( CheckSetConditional(info.Type) != inConditional){
///		OS_Printf("�����𖞂����Ă��Ȃ�:%d\n",anime_code);
		return FALSE;
	}

	//�w��A�j����OBJ�ɃZ�b�g
	for(i=0;i<FLD_3D_ANIME_MAX;i++){
		if(anime_code == field_3d_anime_ptr->Fld3DAnimeData[i].AnimeCode){
			//���E�A�j���[�V�����G���g���[
			if (info.Suicide){
				rc = EntrySuicideAnime(	field_3d_anime_ptr->SuicideData,
										objectdata,
										&field_3d_anime_ptr->Fld3DAnimeData[i],
										anime_code	);
			}else{
				rc = TRUE;
			}

			if (rc){
				NNS_G3dRenderObjAddAnmObj( objectdata, field_3d_anime_ptr->Fld3DAnimeData[i].pAnmObj );
			}
			
			return TRUE;
		}
	}
	//�A�j�����Ȃ��ꍇ
///	OS_Printf("ObjID=%d:3D�A�j������܂���\n",inObjCode);
	return FALSE;
}

//==============================================================================
/**
 * �A�j���[�V�����Z�b�g
 *
 * @param	inObjCode				OBJID
 * @param	objectdata				�����_�[OBJ
 * @param	field_3d_anime_ptr		�A�j���}�l�[�W���ւ̃|�C���^
 *
 * @return	BOOL	TRUE:�Z�b�g�ł���	FALSE:�Z�b�g�ł��Ȃ�����
 */
//==============================================================================
BOOL F3DA_SetFld3DAnimeEasy(const int inObjCode,
							NNSG3dRenderObj *objectdata,
							FLD_3D_ANM_MNG_PTR field_3d_anime_ptr)
{
	int n;
	int i;
	int anime_code;
	ANIME_INFO info;
	
	BOOL set_flg;
	BOOL rc;

	set_flg = FALSE;
	
	if (field_3d_anime_ptr==NULL){
		GF_ASSERT(0&&"�A�j���}�l�[�W����NULL�ł�");
	}

	if (inObjCode >= F3DA_GetAnimeArcObjNum(field_3d_anime_ptr)){
		return FALSE;
	}
		
	//�w��n�a�i�A�j�������A�[�J�C�o�������
	ArchiveDataLoadByHandle(field_3d_anime_ptr->AnmInfoHandle, inObjCode, &info);

	if ( CheckSetConditional(info.Type) != FALSE){
///		OS_Printf("�����𖞂����Ă��Ȃ�:%d\n",anime_code);
		return FALSE;
	}
	
	for(n=0;n<ONE_MODEL_ANM_NUM_MAX;n++){
		anime_code = info.Code[n];
		if (anime_code == ANIME_NONE_CODE){
			return set_flg;//�����𔲂���
		}

		//�w��A�j����OBJ�ɃZ�b�g
		for(i=0;i<FLD_3D_ANIME_MAX;i++){
			if(anime_code == field_3d_anime_ptr->Fld3DAnimeData[i].AnimeCode){
				//���E�A�j���[�V�����G���g���[
				if (info.Suicide){
					rc = EntrySuicideAnime(	field_3d_anime_ptr->SuicideData,
											objectdata,
											&field_3d_anime_ptr->Fld3DAnimeData[i],
											anime_code	);
				}else{
					rc = TRUE;
				}

				if (rc){
					NNS_G3dRenderObjAddAnmObj( objectdata, field_3d_anime_ptr->Fld3DAnimeData[i].pAnmObj );
					set_flg = TRUE;
				}
			
				break;
			}
		}
		//�A�j�����Ȃ��ꍇ
///		OS_Printf("ObjID=%d:3D�A�j������܂���\n",inObjCode);
	}
	
	return set_flg;
}

//==============================================================================
/**
 * �A�j���[�V�����S���
 *
 * @param	field_3d_anime_ptr		�A�j���}�l�[�W���ւ̃|�C���^
 *
 * @return	none
 */
//==============================================================================
void RereaseFld3DAnimeAll(FLD_3D_ANM_MNG_PTR field_3d_anime_ptr)
{
	int i;
	if (field_3d_anime_ptr==NULL) return;
	
	for(i=0;i<FLD_3D_ANIME_MAX;i++){
		if (field_3d_anime_ptr->Fld3DAnimeData[i].Valid != DATA_INVALID){
			if (field_3d_anime_ptr->Fld3DAnimeData[i].Valid == DATA_VALID){
				NNS_G3dFreeAnmObj(&field_3d_anime_ptr->AnimeAllocator,field_3d_anime_ptr->Fld3DAnimeData[i].pAnmObj);
				field_3d_anime_ptr->Fld3DAnimeData[i].pAnmObj = NULL;
				sys_FreeMemoryEz(field_3d_anime_ptr->Fld3DAnimeData[i].pFile);
			}
			field_3d_anime_ptr->Fld3DAnimeData[i].Valid = DATA_INVALID;
			field_3d_anime_ptr->Fld3DAnimeData[i].ControlCode = 0;
		}
	}
}

//==============================================================================
/**
 * �C���f�b�N�X�ɂ��A�j���[�V�������
 *
 * @param	inIdx				�C���f�b�N�X
 * @param	field_3d_anime_ptr		�A�j���}�l�[�W���ւ̃|�C���^
 *
 * @return	none
 */
//==============================================================================
void RereaseFld3DAnimeByIdx(const u8 inIdx, FLD_3D_ANM_MNG_PTR field_3d_anime_ptr)
{
	GF_ASSERT(inIdx<FLD_3D_ANIME_MAX);
	
	if (field_3d_anime_ptr==NULL) return;
	
	if (field_3d_anime_ptr->Fld3DAnimeData[inIdx].Valid != DATA_INVALID){
		if (field_3d_anime_ptr->Fld3DAnimeData[inIdx].Valid == DATA_VALID){
			NNS_G3dFreeAnmObj(	&field_3d_anime_ptr->AnimeAllocator,
								field_3d_anime_ptr->Fld3DAnimeData[inIdx].pAnmObj);
			field_3d_anime_ptr->Fld3DAnimeData[inIdx].pAnmObj = NULL;
			sys_FreeMemoryEz(field_3d_anime_ptr->Fld3DAnimeData[inIdx].pFile);
		}
		field_3d_anime_ptr->Fld3DAnimeData[inIdx].Valid = DATA_INVALID;
		field_3d_anime_ptr->Fld3DAnimeData[inIdx].ControlCode = 0;
	}
}

//==============================================================================
/**
 * �A�j���[�V�������
 *
 * @param	outAnimePtr				�A�j���f�[�^�|�C���^
 * @param	field_3d_anime_ptr		�A�j���}�l�[�W���ւ̃|�C���^
 *
 * @return	none
 */
//==============================================================================
void F3DA_RereaseFld3DAnime(FLD_3D_ANM_DAT_PTR outAnimePtr, FLD_3D_ANM_MNG_PTR field_3d_anime_ptr)
{
	if (field_3d_anime_ptr==NULL) return;
	
	GF_ASSERT(outAnimePtr!=NULL&&"NULL������悤�Ƃ��Ă��܂�");
	
	if (outAnimePtr->Valid != DATA_INVALID){
		if (outAnimePtr->Valid == DATA_VALID){
			NNS_G3dFreeAnmObj(	&field_3d_anime_ptr->AnimeAllocator,
								outAnimePtr->pAnmObj);
			outAnimePtr->pAnmObj = NULL;
			sys_FreeMemoryEz(outAnimePtr->pFile);
		}
		outAnimePtr->Valid = DATA_INVALID;
		outAnimePtr->ControlCode = 0;
	}
}

//==============================================================================
/**
 * �A�j���[�V���������[�u
 *
 * @param	field_3d_anime_ptr		�A�j���}�l�[�W���ւ̃|�C���^
 * @param	inRenderObj				�����_�[OBJ
 * @param	inObjCode				OBJID
 * @param	inAnimeNo				�����[�u����A�j���i���o�[
 * 
 * @return	none
 */
//==============================================================================
void F3DA_RemoveFld3DAnime(	FLD_3D_ANM_MNG_PTR field_3d_anime_ptr,
							NNSG3dRenderObj *inRenderObj,
							const int inObjCode,
							const int inAnimeNo	)
{
	u8 i;
	int anime_code;
	ANIME_INFO info;
	//�w��n�a�i�A�j�������A�[�J�C�o�������
	ArchiveDataLoadByHandle(field_3d_anime_ptr->AnmInfoHandle, inObjCode, &info);
	GF_ASSERT(inAnimeNo<ONE_MODEL_ANM_NUM_MAX);
	anime_code = info.Code[inAnimeNo];
	GF_ASSERT(anime_code != ANIME_NONE_CODE);
	for(i=0;i<FLD_3D_ANIME_MAX;i++){
		if ( field_3d_anime_ptr->Fld3DAnimeData[i].Valid == DATA_VALID ){
			if(field_3d_anime_ptr->Fld3DAnimeData[i].AnimeCode == anime_code){
				RemoveAnime(inRenderObj, field_3d_anime_ptr->Fld3DAnimeData[i].pAnmObj);
				return;
			}
		}
	}
}

//==============================================================================
/**
 * �A�j���[�V�����}�l�[�W�����
 *
 * @param	field_3d_anime_ptr		�A�j���}�l�[�W���ւ̃|�C���^
 * 
 * @return	none
 */
//==============================================================================
void FreeFld3DAnimeManager(FLD_3D_ANM_MNG_PTR field_3d_anime_ptr)
{
	if (field_3d_anime_ptr==NULL) return;
	
	//�n���h���N���[�Y
	ArchiveDataHandleClose( field_3d_anime_ptr->AnimeHandle );
	ArchiveDataHandleClose( field_3d_anime_ptr->AnmInfoHandle );
	
	sys_FreeMemoryEz( field_3d_anime_ptr );
	field_3d_anime_ptr = NULL;
}

//==============================================================================
/**
 * �}�l�[�W���Ǘ��C���f�b�N�X�ŃA�j���f�[�^���擾
 *
 * @param	inIndex					�C���f�b�N�X
 * @param	field_3d_anime_ptr		�A�j���}�l�[�W���ւ̃|�C���^
 * 
 * @return	none
 */
//==============================================================================
FLD_3D_ANM_DAT_PTR F3DA_GetFld3DAnmPtrByIdx(const int inIndex,
											FLD_3D_ANM_MNG_PTR field_3d_anime_ptr)
{
	FLD_3D_ANM_DAT_PTR data;
	
	GF_ASSERT(inIndex<FLD_3D_ANIME_MAX);
	data = &(field_3d_anime_ptr->Fld3DAnimeData[inIndex]);

	GF_ASSERT(data->Valid!=DATA_INVALID&&"�w��f�[�^�͖�����Ԃł�");
	
	return data;
}

//==============================================================================
/**
 * ����R�[�h�ŃA�j���f�[�^���擾
 *
 * @param	inCode					����R�[�h
 * @param	field_3d_anime_ptr		�A�j���}�l�[�W���ւ̃|�C���^
 * 
 * @return	none
 */
//==============================================================================
FLD_3D_ANM_DAT_PTR F3DA_GetFld3DAnmPtrByCode(	const int inCode,
												FLD_3D_ANM_MNG_PTR field_3d_anime_ptr)
{
	FLD_3D_ANM_DAT_PTR data;
	int i;
	GF_ASSERT(inCode!=0&&"����R�[�h���ӂ��Ă��Ȃ��A�j���͎擾�ΏۊO�ł�");
	data = NULL;
	//����
	for(i=0;i<FLD_3D_ANIME_MAX;i++){
		if (field_3d_anime_ptr->Fld3DAnimeData[i].ControlCode == inCode){
			data = &(field_3d_anime_ptr->Fld3DAnimeData[i]);
			GF_ASSERT(data->Valid!=DATA_INVALID&&"�w��f�[�^�͖�����Ԃł�");
			break;
		}
	}
	GF_ASSERT(data!=NULL&&"�A�j����������܂���ł���");
	return data;
}

//==============================================================================
/**
 * �A�j���f�[�^���擾
 *
 * @param	inObjID					�n�a�i�h�c
 * @param	inAnimeNo				�A�j���i���o�[
 * @param	field_3d_anime_ptr		�A�j���}�l�[�W���ւ̃|�C���^
 * 
 * @return	none
 */
//==============================================================================
FLD_3D_ANM_DAT_PTR F3DA_GetFld3DAnmPtr(	const int inObjID,
										const int inAnimeNo,
										FLD_3D_ANM_MNG_PTR field_3d_anime_ptr)
{
	FLD_3D_ANM_DAT_PTR data;
	int anime_code;
	int i;
	ANIME_INFO info;
	//�w��n�a�i�A�j�������A�[�J�C�o�������
	ArchiveDataLoadByHandle(field_3d_anime_ptr->AnmInfoHandle, inObjID, &info);

	GF_ASSERT(inAnimeNo<ONE_MODEL_ANM_NUM_MAX);

	anime_code = info.Code[inAnimeNo];

	data = NULL;
	
	//����
	for(i=0;i<FLD_3D_ANIME_MAX;i++){
		if (field_3d_anime_ptr->Fld3DAnimeData[i].AnimeCode == anime_code){
			data = &(field_3d_anime_ptr->Fld3DAnimeData[i]);
			GF_ASSERT(data->Valid!=DATA_INVALID&&"�w��f�[�^�͖�����Ԃł�");
			break;
		}
	}
	GF_ASSERT(data!=NULL&&"�A�j����������܂���ł���");
	return data;
}

//==============================================================================
/**
 * �C���f�b�N�X�ɂ��X�g�b�v�t���O�̐؂�ւ�
 *
 * @param	inIdx					�C���f�b�N�X
 * @param	inFlg					�X�g�b�v�t���O
 * @param	field_3d_anime_ptr		�A�j���[�V�����}�l�[�W���ւ̃|�C���^
 * 
 * @return	none
 */
//==============================================================================
void F3DA_SetStopFlgByIdx(const u8 inIdx, const BOOL inFlg, FLD_3D_ANM_MNG_PTR field_3d_anime_ptr)
{
	GF_ASSERT(inIdx<FLD_3D_ANIME_MAX);
	field_3d_anime_ptr->Fld3DAnimeData[inIdx].StopFlg = inFlg;
}

//==============================================================================
/**
 * �X�g�b�v�t���O�̐؂�ւ�
 *
 * @param	inAnimePtr				�A�j���f�[�^�|�C���^
 * @param	inFlg					�X�g�b�v�t���O
 * 
 * @return	none
 */
//==============================================================================
void F3DA_SetStopFlg(FLD_3D_ANM_DAT_PTR inAnimePtr, const BOOL inFlg)
{
	inAnimePtr->StopFlg = inFlg;
}

//==============================================================================
/**
 * �A�j���[�V�����X�e�[�g�𓮍쒆�ɂ���
 *
 * @param	inAnimePtr				�A�j���f�[�^�|�C���^
 * 
 * @return	none
 */
//==============================================================================
void F3DA_MoveAnime(FLD_3D_ANM_DAT_PTR inAnimePtr)
{
	inAnimePtr->State = STATE_MOVE;
}

//==============================================================================
/**
 * �A�j���[�V�������ŏI�t���[������Ԃ�
 *
 * @param	inAnimeData	�A�j���[�V�����f�[�^�ւ̃|�C���^
 *
 * @return	BOOL TRUE:�ŏI�t���[��	FALSE:�ŏI�t���[���ȊO
 */
//==============================================================================
BOOL F3DA_IsLastFrame(FLD_3D_ANM_DAT_PTR	inAnimeData)
{
	BOOL rc;
	if (!inAnimeData->Reverse){	//�ʏ�܂킵
		if (inAnimeData->pAnmObj->frame >= 
				NNS_G3dAnmObjGetNumFrame(inAnimeData->pAnmObj)-(FX32_ONE)){
			rc = TRUE;
		}else{
			rc = FALSE;
		}
	}else{						//�t�܂킵
		if (inAnimeData->pAnmObj->frame == 0){
			rc = TRUE;
		}else{
			rc = FALSE;
		}
	}
	return rc;
}

//==============================================================================
/**
 * �J�n�A�j���[�V�����t���[���Z�b�g
 *
 * @param	outAnimeData	�A�j���[�V�����f�[�^�ւ̃|�C���^
 *
 * @return	none
 */
//==============================================================================
void F3DA_SetStartFrame(FLD_3D_ANM_DAT_PTR	outAnimeData)
{
	if (!outAnimeData->Reverse){	//�ʏ�܂킵
		outAnimeData->pAnmObj->frame = 0;
	}else{						//�t�܂킵
		outAnimeData->pAnmObj->frame = NNS_G3dAnmObjGetNumFrame(outAnimeData->pAnmObj)-(FX32_ONE);
	}
}

//==============================================================================
/**
 * �J�n�A�j���[�V�����t���[���Z�b�g
 *
 * @param	outAnimeData	�A�j���[�V�����f�[�^�ւ̃|�C���^
 *
 * @return	none
 */
//==============================================================================
void F3DA_SetLastFrame(FLD_3D_ANM_DAT_PTR	outAnimeData)
{
	if (!outAnimeData->Reverse){	//�ʏ�܂킵
		outAnimeData->pAnmObj->frame = NNS_G3dAnmObjGetNumFrame(outAnimeData->pAnmObj)-(FX32_ONE);
	}else{						//�t�܂킵
		outAnimeData->pAnmObj->frame = 0;
	}
}

//==============================================================================
/**
 * �J�n�A�j���[�V�����t���[���ύX
 *
 * @param	outAnimeData	�A�j���[�V�����f�[�^�ւ̃|�C���^
 *
 * @return	none
 */
//==============================================================================
void F3DA_ChangeFrame(FLD_3D_ANM_DAT_PTR	outAnimeData)
{
	if (!outAnimeData->Reverse){	//�ʏ�܂킵
		outAnimeData->pAnmObj->frame += (FX32_ONE);
		if (outAnimeData->pAnmObj->frame == NNS_G3dAnmObjGetNumFrame(outAnimeData->pAnmObj)){
			outAnimeData->pAnmObj->frame = 0;
		}

	}else{						//�t�܂킵
		if (outAnimeData->pAnmObj->frame <= 0){
			outAnimeData->pAnmObj->frame =
				NNS_G3dAnmObjGetNumFrame(outAnimeData->pAnmObj)-(FX32_ONE);
		}else{
			outAnimeData->pAnmObj->frame -= (FX32_ONE);
		}
	}
}

//==============================================================================
/**
 * �w��A�j���[�V�����̍Đ��������t�ɂ���
 *
 * @param	outAnimeData	�A�j���[�V�����f�[�^�ւ̃|�C���^
 *
 * @return	none
 */
//==============================================================================
void F3DA_SetAnimeReverse(FLD_3D_ANM_DAT_PTR	outAnimeData)
{
	//�񐔎w��A�j���̏ꍇ�̓A�T�[�g�𔭍s
	///GF_ASSERT(outAnimeData->LoopMax != LOOP_INFINIT && "�񐔎w��A�j���[�V�����̋t�񂵂̓T�|�[�g���Ă��܂���");
	if (outAnimeData->Reverse){
		outAnimeData->Reverse = FALSE;
	}else{
		outAnimeData->Reverse = TRUE;
	}
}

//==============================================================================
/**
 * �w��A�j���[�V�����̍Đ��������t�ɂ���(���ڎw��)
 *
 * @param	outAnimeData	�A�j���[�V�����f�[�^�ւ̃|�C���^
 *
 * @return	none
 */
//==============================================================================
void F3DA_SetAnimeReverseDirect(FLD_3D_ANM_DAT_PTR	outAnimeData, const BOOL inReverse)
{
	//�񐔎w��A�j���̏ꍇ�̓A�T�[�g�𔭍s
	///GF_ASSERT(outAnimeData->LoopMax != LOOP_INFINIT && "�񐔎w��A�j���[�V�����̋t�񂵂̓T�|�[�g���Ă��܂���");
	outAnimeData->Reverse = inReverse;
}

//==============================================================================
/**
 * �w��A�j���[�V�����̍ő僋�[�v�����Z�b�g
 *
 * @param	outAnimeData	�A�j���[�V�����f�[�^�ւ̃|�C���^
 * @param	inLoopMax		���[�v��
 *
 * @return	none
 */
//==============================================================================
void F3DA_SetAnimeLoopMax(FLD_3D_ANM_DAT_PTR	outAnimeData, const int inLoopMax)
{
	outAnimeData->LoopMax = inLoopMax;
}

//==============================================================================
/**
 * �w��A�j���[�V�����̐���R�[�h���Z�b�g
 *
 * @param	outAnimeData	�A�j���[�V�����f�[�^�ւ̃|�C���^
 * @param	inControlCode	����R�[�h
 *
 * @return	none
 */
//==============================================================================
void F3DA_SetControlCode(FLD_3D_ANM_DAT_PTR	outAnimeData, const int inControlCode)
{
	outAnimeData->ControlCode = inControlCode;
}

//==============================================================================
/**
 * �A�j���[�V�������C���֐�
 *
 * @param	field_3d_anime_ptr	3D�A�j���[�V�����}�l�[�W���ւ̃|�C���^
 *
 * @return	none
 */
//==============================================================================
void F3DA_Main(FLD_3D_ANM_MNG_PTR field_3d_anime_ptr)
{
	int i;
	FLD_3D_ANM_DAT_PTR	anime_data;
	if (field_3d_anime_ptr==NULL) return;
	for(i=0;i<FLD_3D_ANIME_MAX;i++){
		anime_data = &(field_3d_anime_ptr->Fld3DAnimeData[i]);
		//�A�j���͗L�����ǂ���
		if (anime_data->Valid == DATA_VALID){
			//�A�j���[�V��������~���Ă���A�������̓A�j�����I�����Ă���ꍇ�͏������΂�
			if ((anime_data->StopFlg == TRUE)||(anime_data->State == STATE_END)){
				continue;
			}

			F3DA_ChangeFrame(anime_data);	//�t���[���؂�ւ�
			
			if ( anime_data->LoopMax != LOOP_INFINIT ){	//���[�v�w��񐔂���
				if (F3DA_IsLastFrame(anime_data)){			//�ŏI�t���[�����H
					if (anime_data->LoopCount+1 >= anime_data->LoopMax){//�ŏI�w�胋�[�v�񐔖ڂ��H
						//�A�j���I��
						anime_data->State = STATE_END;
					}else{
						anime_data->LoopCount++;	//���[�v�����C���N�������g
					}
				}
			}
		}
	}// end for
	//���E�Ď�
	SuicideAnimeMain(field_3d_anime_ptr->SuicideData);

}

//==============================================================================
/**
 * �A�j���[�V�������I�����Ă��邩��Ԃ�
 * @param	inAnimeData	�A�j���f�[�^�ւ̃|�C���^
 *
 * @return	BOOL	TRUE:�I���@FALSE:NO �p��
 */
//==============================================================================
BOOL F3DA_IsAnimeEnd(const FLD_3D_ANM_DAT_PTR inAnimeData)
{
	int state;
	state = GetAnimeState(inAnimeData);
	if (state == STATE_END){
		return TRUE;
	}else{
		return FALSE;
	}
}

//==============================================================================
/**
 * �A�j���A�[�J�C�u���ێ����Ă���n�a�i�̐���Ԃ�
 * 
 * @param	field_3d_anime_ptr	3D�A�j���[�V�����}�l�[�W���ւ̃|�C���^
 *
 * @return	u16 �t�@�C����
 */
//==============================================================================
u16 F3DA_GetAnimeArcObjNum(FLD_3D_ANM_MNG_PTR field_3d_anime_ptr)
{
	return ArchiveDataFileCntGetByHandle(field_3d_anime_ptr->AnmInfoHandle);
}

//==============================================================================
/**
 * �w��n�a�i�h�c�̃A�j������Ԃ�
 * 
 * @param	field_3d_anime_ptr	3D�A�j���[�V�����}�l�[�W���ւ̃|�C���^
 *
 * @return	u16 �A�j����
 */
//==============================================================================
const u8 F3DA_GetAnimeNum(FLD_3D_ANM_MNG_PTR field_3d_anime_ptr, const int inObjCode)
{
	u8 n;
	ANIME_INFO info;
	//�w��n�a�i�A�j�������A�[�J�C�o�������
	ArchiveDataLoadByHandle(field_3d_anime_ptr->AnmInfoHandle, inObjCode, &info);

	//�A�j�����Ȃ����̂̐���0
	if (!info.Flg){
		return 0;
	}
		
	for(n=0;n<ONE_MODEL_ANM_NUM_MAX;n++){
		if (info.Code[n] == ANIME_NONE_CODE){
			break;
		}
	}
	return n;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//==============================================================================
/**
 * �A�j���[�V�����G���g���[
 *
 * @param	inAnimeContMng	�A�j���[�V�����Ǘ��}�l�[�W���ւ̃|�C���^
 * @param	inEntryID		�o�^ID
 *
 * @return	ANIME_CONT_PTR	�A�j���Ǘ��f�[�^�|�C���^
 */
//==============================================================================
static ANIME_CONT_PTR EntryAnimeCont(ANIME_CONT_MNG_PTR inAnimeContMng, const u8 inEntryID)
{	
	u8 i;
	u8 idx;
	ANIME_CONT_PTR	data;
	
	data = NULL;
	
	GF_ASSERT(inEntryID!=NO_ENTRY&&"ID=0�͎w��ł��܂���");
	idx = ANIME_CONT_MAX;
	//�󂢂Ă���Ƃ�����������A�\��ID�����łɂ��邩��T��
	for(i=0;i<ANIME_CONT_MAX;i++){
#ifdef PM_DEBUG		
		if (inAnimeContMng->AnimeCont[i].EntryID == inEntryID ){
			OS_Printf("ID=%d:�w�肳�ꂽID�͓o�^�ς݂ł�\n",inEntryID);
			GF_ASSERT(0);
		}
#endif		
		if ( (idx == ANIME_CONT_MAX)&&
			 (inAnimeContMng->AnimeCont[i].EntryID)==NO_ENTRY  ){
			idx = i;
		}
	}

	if (idx != ANIME_CONT_MAX){
		inAnimeContMng->AnimeCont[idx].EntryID = inEntryID;
	}else{
		GF_ASSERT_MSG(0,"idx == ANIME_CONT_MAX");
		return NULL;
	}
	
	return &(inAnimeContMng->AnimeCont[idx]);
}

//==============================================================================
/**
 *	�G���g���[�N���A
 * 
 * @param	outData	�A�j���Ǘ��f�[�^�|�C���^
 *
 * @return	none
 */
//==============================================================================
static void EntryClearAnimeCont(ANIME_CONT_PTR outData)
{
	u8 i;
	outData->EntryID = NO_ENTRY;
	outData->ObjID = 0;
	outData->BindAnime = NULL;
	for(i=0;i<CONT_RENDER_OBJ_MAX;i++){
		outData->RenderObj[i] = NULL;
	}
}

//==============================================================================
/**
 *	�o�^ID�ŃA�j���Ǘ��f�[�^���擾
 * 
 * @param	inAnimeContMng	�A�j���[�V�����Ǘ��}�l�[�W���ւ̃|�C���^
 * @param	inEntryID		�G���g���[�h�c
 *
 * @return	�A�j���Ǘ��f�[�^�|�C���^
 */
//==============================================================================
static ANIME_CONT_PTR GetAnmContPtrFromEntryID(	ANIME_CONT_MNG_PTR inAnimeContMng,
												const int inEntryID)
{
	int i;
	ANIME_CONT_PTR data;
	data = NULL;
	//�\�񂳂�Ă���ꏊ������
	for(i=0;i<ANIME_CONT_MAX;i++){
		if (inAnimeContMng->AnimeCont[i].EntryID == inEntryID){
			data = &(inAnimeContMng->AnimeCont[i]);
			break;
		}
	}
#ifdef PM_DEBUG
	if (i==ANIME_CONT_MAX){
		OS_Printf("%d:�w�肳�ꂽ�o�^ID�����A�j���[�V�������擾�ł��܂���ł���",inEntryID);
		GF_ASSERT(0);
	}
#endif
	return data;
}

//==============================================================================
/**
 *	�o�^ID�ŃA�j���Ǘ��f�[�^���擾
 * 
 * @param	*pRenderObj		�����_�[�n�a�i
 * @param	inNum			�A�j����
 * @param	outData			�A�j���Ǘ��f�[�^�|�C���^
 *
 * @return	none
 */
//==============================================================================
static void SetAnimeCont(	NNSG3dRenderObj *pRenderObj,
							const int inNum,
							ANIME_CONT_PTR	outData	)
{
	GF_ASSERT(inNum<=ONE_MODEL_ANM_NUM_MAX&&"1�̃��f�������Ă�A�j�������I�[�o�[���Ă܂�");
	if (pRenderObj != NULL){
		outData->RenderObj[0] = pRenderObj;	//�����_�[�n�a�i�̎w�肪����ꍇ��0�Ԗڂɓo�^����
	}
	outData->AnimeList.AnimeNum = inNum;
}

//==============================================================================
/**
 *	�A�j���f�[�^�Z�b�g
 * 
 * @param	inAnimeContPtr	�A�j���Ǘ��f�[�^�|�C���^
 * @param	inIndex			�C���f�b�N�X
 * @param	inAnimePtr		�A�j���f�[�^�ւ̃|�C���^
 *
 * @return	none
 */
//==============================================================================
static void SetAnimePtr(ANIME_CONT_PTR inAnimeContPtr,
						const int inIndex,
						FLD_3D_ANM_DAT_PTR inAnimePtr)
{
	GF_ASSERT(inIndex<inAnimeContPtr->AnimeList.AnimeNum&&"�C���f�b�N�X���I�[�o�[���Ă܂�");
	inAnimeContPtr->AnimeList.Data[inIndex] = inAnimePtr;
}

//==============================================================================
/**
 *	�A�j���f�[�^�擾
 * 
 * @param	inAnimeContPtr	�A�j���Ǘ��f�[�^�|�C���^
 * @param	inIndex			�C���f�b�N�X
 *
 * @return	FLD_3D_ANM_DAT_PTR	�A�j���f�[�^�|�C���^
 */
//==============================================================================
static FLD_3D_ANM_DAT_PTR GetAnimePtr(ANIME_CONT_PTR inAnimeContPtr, const int inIndex)
{
	GF_ASSERT(inIndex<inAnimeContPtr->AnimeList.AnimeNum&&"�C���f�b�N�X���I�[�o�[���Ă܂�");
	return inAnimeContPtr->AnimeList.Data[inIndex];
}

//==============================================================================
/**
 *	�A�j���o�C���h
 * 
 * @param	ioAnimeContPtr	�A�j���Ǘ��f�[�^�|�C���^
 * @param	inIndex			�C���f�b�N�X
 *
 */
//==============================================================================
static FLD_3D_ANM_DAT_PTR BindAnimation(ANIME_CONT_PTR ioAnimeContPtr, const int inIndex)
{
	u8 i;
	FLD_3D_ANM_DAT_PTR anime;
	NNSG3dAnmObj *anm_obj;
	NNSG3dAnmObj *bind_anmobj;
	GF_ASSERT(inIndex<ioAnimeContPtr->AnimeList.AnimeNum&&"�C���f�b�N�X���I�[�o�[���Ă܂�");
	anime = ioAnimeContPtr->AnimeList.Data[inIndex];
	anm_obj = GetAnmObj(anime);

	bind_anmobj = GetAnmObj(ioAnimeContPtr->BindAnime);
	for(i=0;i<CONT_RENDER_OBJ_MAX;i++){
		if (ioAnimeContPtr->RenderObj[i] != NULL){
			//���łɃA�j�������Ă���ꍇ�̓����[�u����
			RemoveAnime(ioAnimeContPtr->RenderObj[i], bind_anmobj);
			// RenderObj �� AnmObj ��ǉ�����B�W���C���g�A�j���[�V�����ȊO�����l
			NNS_G3dRenderObjAddAnmObj(ioAnimeContPtr->RenderObj[i], anm_obj );
		}
	}
	ioAnimeContPtr->BindAnime = anime;
	return anime;
}

//��풓�A�j���̂ݑΉ�
static void AddField3DAnime(const int inObjID,
							NNSG3dResMdl 	*inObjectModel,
							NNSG3dResTex *inTex,
							const int inAnimeNum,
							const int inLoopCount,
							const BOOL	inReverse,
							FLD_3D_ANM_MNG_PTR field_3d_anime_ptr,
							ANIME_CONT_PTR outData)
{
	FLD_3D_ANM_DAT_PTR	anm_data;
	int i;
	for(i=0;i<inAnimeNum;i++){
		anm_data = F3DA_AddField3DAnime(inObjID,
										i,
										inLoopCount,
										0,		//�O�����䂵�Ȃ�
										inReverse,	//����
										TRUE,	//�n�߂͒�~
										TRUE,	//�����t
										inObjectModel,
										inTex,
										field_3d_anime_ptr);
		GF_ASSERT(anm_data!=NULL&&"�o�^���s");

		//�A�j���Ǘ����X�g�ɓo�^�����A�j���|�C���^���擾���Ă���
		SetAnimePtr( outData, i, anm_data);	//�A�j���o�^
	}
}

static void RereaseField3DAnime(FLD_3D_ANM_MNG_PTR field_3d_anime_ptr,
								ANIME_CONT_PTR outData)
{
	int i;
	NNSG3dAnmObj *anmobj;
	anmobj = GetAnmObj(outData->BindAnime);
	//���łɃA�j�������Ă���ꍇ�̓����[�u����
	for(i=0;i<CONT_RENDER_OBJ_MAX;i++){
		if (outData->RenderObj[i] != NULL){
			RemoveAnime(outData->RenderObj[i], anmobj);
		}
	}
	for (i=0;i<outData->AnimeList.AnimeNum;i++){
		{		
			FLD_3D_ANM_DAT_PTR anime;
			anime = outData->AnimeList.Data[i];	
			F3DA_RereaseFld3DAnime(anime, field_3d_anime_ptr);
		}
		outData->AnimeList.Data[i] = NULL;
	}
}

//3D�A�j���}�l�[�W���̃������A���P�[�V����
ANIME_CONT_MNG_PTR F3DASub_InitField3DAnimeCont(void)
{
	int i;
	int size;
	ANIME_CONT_MNG_PTR anime_cont_mng;

	size = sizeof(ANIME_CONT_MNG);

	anime_cont_mng = sys_AllocMemory( HEAPID_FIELD, size );

	MI_CpuClearFast(anime_cont_mng,size);

	return anime_cont_mng;
}

//3D�A�j���}�l�[�W���̉��
void F3DASub_FreeAnimeContManager(ANIME_CONT_MNG_PTR *outAnimeContMng)
{
	if ((*outAnimeContMng)==NULL) return;

#ifdef	PM_DEBUG
	{
		int i;
		for(i=0;i<ANIME_CONT_MAX;i++){
			if ((*outAnimeContMng)->AnimeCont[i].EntryID != NO_ENTRY ){
				OS_Printf("EntryID:%d �o�^�̉���������Ȃ��܂܉�����悤�Ƃ��Ă��܂�\n",
						(*outAnimeContMng)->AnimeCont[i].EntryID);
				GF_ASSERT(0);
			}
		}
	}
#endif
	
	sys_FreeMemoryEz( (*outAnimeContMng) );
	(*outAnimeContMng) = NULL;
}


//�A�j���[�V�����Z�b�g�A�b�v
void F3DASub_SetUpAnimation(FLD_3D_ANM_MNG_PTR field_3d_anime_ptr,
							const ANIME_CONT_MNG_PTR inAnimeContMng,
							const int inEntryID,
							const int inObjID,
							NNSG3dRenderObj *inRenderObj,
							NNSG3dResMdl 	*inObjectModel,
							NNSG3dResTex *inTex,
							const int inAnimeNum,
							const u8 inLoop,
							const BOOL inReverse)
{
	int i;
	u8 loop;
	ANIME_CONT_PTR		cont_data = NULL;
	//�A�j���G���g���[
	cont_data = EntryAnimeCont(inAnimeContMng, inEntryID);
	if (!cont_data){
		GF_ASSERT_MSG(0,"FAIL_ANIME_ENTRY");
		return ;
	}

	//�g�p����A�j�������Ǘ��p�A�j���|�C���^���X�g���m��
	SetAnimeCont(inRenderObj, inAnimeNum, cont_data);
	loop = inLoop;
	GF_ASSERT(loop != 0);
	if (loop == 0){
		loop = 1;	//0�Z�b�g�h�~
	}
	
	//�A�j���[�V�����̒ǉ�
	AddField3DAnime(inObjID, inObjectModel, inTex, inAnimeNum, loop, inReverse,
					field_3d_anime_ptr, cont_data);
	//OBJID�L��(�قڃT�E���h�p)
	cont_data->ObjID = inObjID;
}

//�����_�[�n�a�i�̃G���g���[
//�����A�j���𕡐��̂n�a�i���g���ꍇ�Ɏg�p
//F3DASub_SetUpAnimation�Ń����_�[�n�a�i�w�肵�Ȃ������Ƃ���
//��ł�����g���ăG���g������
void F3DASub_EntryRenderObj(const ANIME_CONT_MNG_PTR inAnimeContMng,
							const int inEntryID,
							const u8 inEntryIndex,
							NNSG3dRenderObj *inRenderObj)
{
	ANIME_CONT_PTR cont_ptr;
	GF_ASSERT(inEntryIndex<CONT_RENDER_OBJ_MAX);
	cont_ptr = GetAnmContPtrFromEntryID( inAnimeContMng, inEntryID);
	GF_ASSERT_MSG((cont_ptr->RenderObj[inEntryIndex]==NULL),"�����_�[OBJ�����łɂ���܂�");
	cont_ptr->RenderObj[inEntryIndex] = inRenderObj;
}


//�A�j���J�n
void F3DASub_StartAnimation(const ANIME_CONT_MNG_PTR inAnimeContMng,
							const int inEntryID,
							const int inAnimeNo)
{
	ANIME_CONT_PTR cont_ptr;
	FLD_3D_ANM_DAT_PTR anime;
	GF_ASSERT_MSG((inEntryID!=NO_ENTRY),"ID=0�͎w��ł��܂���");
	cont_ptr = GetAnmContPtrFromEntryID(inAnimeContMng, inEntryID);

	anime = BindAnimation(cont_ptr, inAnimeNo);	//�A�j�����o�C���h
	//�A�j���[�V�������X�^�[�g
	F3DA_SetStopFlg(anime, FALSE);
}

//�A�j���J�n(����)
void F3DASub_StartAnimeSnd(const ANIME_CONT_MNG_PTR inAnimeContMng,
							const int inEntryID,
							const int inAnimeNo,
							const int inSound)
{
	ANIME_CONT_PTR cont_ptr;
	FLD_3D_ANM_DAT_PTR anime;
	GF_ASSERT(inEntryID!=NO_ENTRY&&"ID=0�͎w��ł��܂���");
	cont_ptr = GetAnmContPtrFromEntryID(inAnimeContMng, inEntryID);

	anime = BindAnimation(cont_ptr, inAnimeNo);	//�A�j�����o�C���h

	//�����h�A���鉹�ȊO��������SE�Đ�
	if( inSound != SE_JIDO_DOOR_CLOSE ){
		Snd_SePlay(inSound);
	}

	//�A�j���[�V�������X�^�[�g
	F3DA_SetStopFlg(anime, FALSE);
}

//�A�j���o�C���h
void F3DASub_BindAnimation( const ANIME_CONT_MNG_PTR inAnimeContMng,
							const int inEntryID,
							const int inAnimeNo)
{
	ANIME_CONT_PTR cont_ptr;
	FLD_3D_ANM_DAT_PTR anime;
	GF_ASSERT(inEntryID!=NO_ENTRY&&"ID=0�͎w��ł��܂���");
	cont_ptr = GetAnmContPtrFromEntryID(inAnimeContMng, inEntryID);

	anime = BindAnimation(cont_ptr, inAnimeNo);	//�A�j�����o�C���h
}

//�A�j���X�g�b�v�t���O�I���I�t
void F3DASub_SetStopFlg( const ANIME_CONT_MNG_PTR inAnimeContMng,
							const int inEntryID,
							const int inAnimeNo,
							const BOOL inFlg)
{
	ANIME_CONT_PTR cont_ptr;
	FLD_3D_ANM_DAT_PTR anime;
	GF_ASSERT(inEntryID!=NO_ENTRY&&"ID=0�͎w��ł��܂���");
	cont_ptr = GetAnmContPtrFromEntryID(inAnimeContMng, inEntryID);

	anime = BindAnimation(cont_ptr, inAnimeNo);	//�A�j�����o�C���h
	//�A�j���[�V�������X�^�[�g
	F3DA_SetStopFlg(anime, inFlg);
}

//�������
void F3DASub_RereaseAnimation(	FLD_3D_ANM_MNG_PTR field_3d_anime_ptr,
								ANIME_CONT_MNG_PTR inAnimeContMng,
								const int inEntryID)
{
	ANIME_CONT_PTR data;
	GF_ASSERT(inEntryID!=NO_ENTRY&&"ID=0�͎w��ł��܂���");
	data = GetAnmContPtrFromEntryID(inAnimeContMng, inEntryID);
	//�A�j���[�V�����̉��
	RereaseField3DAnime(field_3d_anime_ptr, data);
	//�G���g���[�N���A
	EntryClearAnimeCont(data);
}

//�A�j���擾
FLD_3D_ANM_DAT_PTR F3DASub_GetFld3DAnmPtr(	const ANIME_CONT_MNG_PTR inAnimeContMng,
											const int inEntryID,
											const int inAnimeNo	)
{
	ANIME_CONT_PTR cont_data;
	FLD_3D_ANM_DAT_PTR anime;
	GF_ASSERT(inEntryID!=NO_ENTRY&&"ID=0�͎w��ł��܂���");
	cont_data =  GetAnmContPtrFromEntryID(inAnimeContMng, inEntryID);
	anime = GetAnimePtr(cont_data, inAnimeNo);
	return anime;
}

//���݃o�C���h����Ă���A�j�����擾
FLD_3D_ANM_DAT_PTR F3DASub_GetFld3DBindAnmPtr(	const ANIME_CONT_MNG_PTR inAnimeContMng,
												const int inEntryID	)
{
	ANIME_CONT_PTR cont_data;
	FLD_3D_ANM_DAT_PTR anime;
	GF_ASSERT(inEntryID!=NO_ENTRY&&"ID=0�͎w��ł��܂���");
	cont_data =  GetAnmContPtrFromEntryID(inAnimeContMng, inEntryID);
	anime = cont_data->BindAnime;
	return anime;
}

//�A�j���[�V�����I���҂�
const BOOL F3DASub_WaitAnimation(	const ANIME_CONT_MNG_PTR inAnimeContMng,
									const int inEntryID	)
{
	FLD_3D_ANM_DAT_PTR data;
	data = F3DASub_GetFld3DBindAnmPtr(inAnimeContMng, inEntryID);

	GF_ASSERT_MSG((data!=NULL),"�A�j�����o�C���h����Ă��Ȃ�");
	
	if ( F3DA_IsAnimeEnd(data) ){
		return TRUE;
	}else{
		return FALSE;
	}
}

const int F3DASub_GetObjIDFromEntryID(	const ANIME_CONT_MNG_PTR inAnimeContMng,
										const int inEntryID)
{
	ANIME_CONT_PTR cont_ptr;
	cont_ptr = GetAnmContPtrFromEntryID(inAnimeContMng, inEntryID);
	return cont_ptr->ObjID;
}
