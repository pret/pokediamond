//============================================================================================
/**
 * @file	height_ex.c
 * @brief	�g�������f�[�^
 * @author	Nozomu Saito
 * @date	2005.12.05
 */
//============================================================================================
#include "common.h"
#include "../height_def.h"

typedef struct EX_HEIGHT_DATA_tag
{
	int StartGridX;
	int StartGridZ;
	int SizeGridX;
	int SizeGridZ;
	fx32 Height;
	BOOL Valid;
}EX_HEIGHT_DATA;

typedef struct EX_HEIGHT_LIST_tag
{
	int Num;
	EX_HEIGHT_DATA *ExHeightData;
}EX_HEIGHT_LIST;

static BOOL HitCheckExHeightFromData(	const int inGridX,
										const int inGridZ,
										const EX_HEIGHT_DATA *inExHeightData );

//--------------------------------------------------------------------------------------------
/**
 * �g�������f�[�^�̃q�b�g�`�F�b�N
 *
 * @param	inGridX			�`�F�b�N����O���b�hX���W
 * @param	inGridZ			�`�F�b�N����O���b�hZ���W
 * @param	inExHeightData	�g�������f�[�^�ւ̃|�C���^
 *
 * @return	BOOL	TRUE:�q�b�g	FALSE:�m�[�q�b�g
 */
//--------------------------------------------------------------------------------------------
static BOOL HitCheckExHeightFromData(	const int inGridX,
										const int inGridZ,
										const EX_HEIGHT_DATA *inExHeightData )
{
	//�f�[�^�������Ȃ�q�b�g���Ȃ������Ƃ݂Ȃ�
	if (inExHeightData->Valid == FALSE){
		return FALSE;
	}
#if 0	
#ifdef DEBUG_ONLY_FOR_saitou	
OS_Printf("local_printt search%d,%d\n",inGridX,inGridZ);	
#endif
#endif
	{
		int st_x = inExHeightData->StartGridX;
		int st_z = inExHeightData->StartGridZ;
		int end_x = st_x+inExHeightData->SizeGridX-1;
		int end_z = st_z+inExHeightData->SizeGridZ-1;

		if ( (st_x<=inGridX)&&(inGridX<=end_x)&&
				(st_z<=inGridZ)&&(inGridZ<=end_z) ){
#if 0			
#ifdef DEBUG_ONLY_FOR_saitou			
OS_Printf("local_print HIT!!\n");
#endif
#endif
			return TRUE;
		}
	}
	return FALSE;
}

//--------------------------------------------------------------------------------------------
/**
 * �g�������f�[�^�̃������A���P�[�g
 *
 * @param	inNum		�m�ۂ���f�[�^��
 * @param	inHeapID	�m�ۂ���q�[�vID
 *
 * @return	EHL_PTR	�m�ۂ����̈�̐擪�|�C���^
 */
//--------------------------------------------------------------------------------------------
EHL_PTR EXH_AllocExHeightList(const u8 inNum, const u8 inHeapID)
{
	u8 i;
	EHL_PTR ehl_p;
	ehl_p = sys_AllocMemory( inHeapID, sizeof(EX_HEIGHT_LIST) );
	ehl_p->ExHeightData = sys_AllocMemory( inHeapID, sizeof(EX_HEIGHT_DATA)*inNum );
	ehl_p->Num = inNum;
	//�f�[�^�𖳌���
	for(i=0;i<inNum;i++){
		ehl_p->ExHeightData[i].Valid = FALSE;
	}
	
	return ehl_p;
}

//--------------------------------------------------------------------------------------------
/**
 * �g�������f�[�^�̃Z�b�g�A�b�v
 *
 * @param	inIndex		�擾���鍂���f�[�^�̃C���f�b�N�X
 * @param	inStX			�̈�J�n�O���b�hX���W
 * @param	instZ			�̈�J�n�O���b�hZ���W
 * @param	inSizX			�̈�O���b�h����
 * @param	inSizZ			�̈�O���b�h�c��
 * @param	inHeight		�̈������
 * @param	outExHeightList	�g�������f�[�^�ւ̃|�C���^
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void EXH_SetUpExHeightData(	const u8 inIndex,
							const int inStX,
							const int inStZ,
							const int inSizX,
							const int inSizZ,
							const fx32 inHeight,
							EHL_PTR outExHeightList )
{
	outExHeightList->ExHeightData[inIndex].StartGridX = inStX;
	outExHeightList->ExHeightData[inIndex].StartGridZ = inStZ;
	outExHeightList->ExHeightData[inIndex].SizeGridX = inSizX;
	outExHeightList->ExHeightData[inIndex].SizeGridZ = inSizZ;
	outExHeightList->ExHeightData[inIndex].Height = inHeight;
	outExHeightList->ExHeightData[inIndex].Valid = TRUE;
}

//--------------------------------------------------------------------------------------------
/**
 * �g�������f�[�^���
 *
 * @param	outExHeightData	�g�������f�[�^�̐擪�|�C���^
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void EXH_FreeExHeightList(EHL_PTR outExHeightList)
{
	sys_FreeMemoryEz(outExHeightList->ExHeightData);
	sys_FreeMemoryEz(outExHeightList);
}

//--------------------------------------------------------------------------------------------
/**
 * �g�������f�[�^�̃q�b�g�`�F�b�N
 *
 * @param	inGridX			�`�F�b�N����O���b�hX���W
 * @param	inGridZ			�`�F�b�N����O���b�hZ���W
 * @param	inExHeightList	�g�������f�[�^�ւ̃|�C���^
 *
 * @return	BOOL	TRUE:�q�b�g	FALSE:�m�[�q�b�g
 */
//--------------------------------------------------------------------------------------------
BOOL EXH_HitCheckExHeight(	const int inGridX,
							const int inGridZ,
							EHL_CONST_PTR inExHeightList,
							u8 *outIndex)
{
	u8 i;
	BOOL rc;
	EX_HEIGHT_DATA *ehd_p;

	GF_ASSERT((outIndex != NULL)&&"�i�[�ϐ���NULL");

	for(i=0;i<inExHeightList->Num;i++){
		ehd_p = &inExHeightList->ExHeightData[i];
		if ( HitCheckExHeightFromData( inGridX, inGridZ, ehd_p ) ){
			*outIndex = i;
			return TRUE;
		}
	}
	return FALSE;
}

//--------------------------------------------------------------------------------------------
/**
 * �g�������f�[�^���獂�����擾(���X�g)
 *
 * @param	inIndex	�g�������f�[�^�C���f�b�N�X
 * @param	inExHeightList	�g�������f�[�^�ւ̃|�C���^
 *
 * @return	fx32	����
 */
//--------------------------------------------------------------------------------------------
fx32 EXH_GetExHeight(const u8 inIndex, EHL_CONST_PTR inExHeightList)
{
	GF_ASSERT((inIndex<inExHeightList->Num)&&"�g�������f�[�^�̃C���f�b�N�X�I�[�o�[");
	GF_ASSERT((inExHeightList->ExHeightData[inIndex].Valid)&&"�f�[�^�͖����ł�");
	return inExHeightList->ExHeightData[inIndex].Height;
}

//--------------------------------------------------------------------------------------------
/**
 * �g�������f�[�^�̍����Z�b�g(���X�g)
 *
 * @param	inIndex	�g�������f�[�^�C���f�b�N�X
 * @param	inHeight		�̈������
 * @param	outExHeightList	�g�������f�[�^�ւ̃|�C���^
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void EXH_SetExHeight(	const u8 inIndex,
						const fx32 inHeight,
						EHL_PTR outExHeightList )
{
	GF_ASSERT((inIndex<outExHeightList->Num)&&"�g�������f�[�^�̃C���f�b�N�X�I�[�o�[");
	outExHeightList->ExHeightData[inIndex].Height = inHeight;
}

//--------------------------------------------------------------------------------------------
/**
 * �g�������f�[�^�̗L���E������(���X�g)
 *
 * @param	inIndex	�g�������f�[�^�C���f�b�N�X
 * @param	inValid			TRUE:�L��	FALSE:����
 * @param	outExHeightData	�g�������f�[�^�ւ̃|�C���^
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void EXH_SetExHeightValid(	const u8 inIndex,
							const BOOL inValid,
							EHL_PTR outExHeightList )
{
	GF_ASSERT((inIndex<outExHeightList->Num)&&"�g�������f�[�^�̃C���f�b�N�X�I�[�o�[");
	outExHeightList->ExHeightData[inIndex].Valid = inValid;
}

#if 0
//--------------------------------------------------------------------------------------------
/**
 * �g�������f�[�^�̎擾
 *
 * @param	inIndex		�擾���鍂���f�[�^�̃C���f�b�N�X
 *
 * @return	EHD_PTR		�g�������f�[�^�ւ̃|�C���^
 */
//--------------------------------------------------------------------------------------------
EHD_PTR GetExHeightData(const u8 inIndex, EHL_PTR inExHeightList)
{
	GF_ASSERT((inIndex<inExHeightList->Num)&"�g�������f�[�^�̃C���f�b�N�X�I�[�o�[");
	return inExHeightList->ExHeightData;
}

//--------------------------------------------------------------------------------------------
/**
 * �g�������f�[�^�̃Z�b�g�A�b�v
 *
 * @param	inStX			�̈�J�n�O���b�hX���W
 * @param	instZ			�̈�J�n�O���b�hZ���W
 * @param	inSizX			�̈�O���b�h����
 * @param	inSizZ			�̈�O���b�h�c��
 * @param	inHeight		�̈������
 * @param	outExHeightData	�g�������f�[�^�ւ̃|�C���^
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void SetUpExHeightData(	const int inStX,
						const int inStZ,
						const int inSizX,
						const int inSizZ,
						const fx32 inHeigt,
						EHD_PTR outExHeightData )
{
	outExHeightData->StartGridX = inStX;
	outExHeightData->StartGridZ = inStZ;
	outExHeightData->SizeGridX = inSizX;
	outExHeightData->SizeGridZ = inSizZ;
	outExHeightData->Heigt = inHeight;
	outExHeightData->Valid = TRUE;
}

//--------------------------------------------------------------------------------------------
/**
 * �g�������f�[�^�̍����Z�b�g
 *
 * @param	inHeight		�̈������
 * @param	outExHeightData	�g�������f�[�^�ւ̃|�C���^
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void SetExHeight(	const fx32 inHeigt,
					EHD_PTR outExHeightData )
{
	outExHeightData->Heigt = inHeight;
}

//--------------------------------------------------------------------------------------------
/**
 * �g�������f�[�^�̗L���E������
 *
 * @param	inValid			TRUE:�L��	FALSE:����
 * @param	outExHeightData	�g�������f�[�^�ւ̃|�C���^
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void SetExHeightValid(	const BOOL inValid,
					EHD_PTR outExHeightData )
{
	outExHeightData->Valid = inValid;
}
//--------------------------------------------------------------------------------------------
/**
 * �g�������f�[�^���獂�����擾
 *
 * @param	inExHeightData	�g�������f�[�^�ւ̃|�C���^
 *
 * @return	fx32	����
 */
//--------------------------------------------------------------------------------------------
fx32 GetExHeightFromData(EHD_CONST_PTR inExHeightData)
{
	GF_ASSERT(inExHeightData->Valid&"�f�[�^�͖����ł�");
	return inExHeightData->Height;
}

#endif
