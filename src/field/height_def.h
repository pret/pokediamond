#ifndef _HEIGHT_DEF_H_
#define _HEIGHT_DEF_H_

#include "system/arc_tool.h"

typedef struct MAP_HEIGHT_INFO_tag * MHI_PTR;
typedef struct MAP_HEIGHT_INFO_tag const * MHI_CONST_PTR;

typedef struct EX_HEIGHT_LIST_tag * EHL_PTR;
typedef struct EX_HEIGHT_LIST_tag const * EHL_CONST_PTR;

//�������m��
extern MHI_PTR	AllocMapHeightInfo(void);

//���[�h�֘A
extern void SetupHeightData(const char  *path,
							MHI_PTR	outMapHeightInfo,
							u8 *inHeightMem);
extern void SetupHeightDataArc(	ARCHANDLE *ioHandle,
								const int inDataSize,
								MHI_PTR outMapHeightInfo, u8 * inHeightMem );
extern void FreeMapHeightInfo(MHI_PTR	outMapHeightInfo);
/*
extern TCB_PTR SetupHeightDataTask(const char  *path, 
		MHI_PTR	ioMapHeightInfo,
		int *inEndFlg,
		u8 **inHeightMem);
*/
extern TCB_PTR SetupHeightDataArcTask(	ARCHANDLE *inHandle,
										const int DataSize,
										MHI_PTR ioMap3DInfo,
										int *inEndFlg,
										u8 **inHeightMem,
										int *inStartFlg);
extern void StopHeightLoadTaskRequest(TCB_PTR tcb);
extern void InitHeightData(MHI_PTR outData);

extern VecFx32 MoveRevise(fx32 inMoveVal, VecFx32 inNewVec, VecFx32 inOldVec);

extern void SetInvalidHeightData(MHI_PTR outMap3DInfo);

//�����擾
extern BOOL GetHeightForBlock(	const fx32 inNowY, const fx32 inX, const fx32 inZ,
								MHI_CONST_PTR inMap3DInfo,fx32 *outY);

extern BOOL GetInvalidHeightDataFlg(MHI_CONST_PTR inMap3DInfo);

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
extern EHL_PTR EXH_AllocExHeightList(const u8 inNum, const u8 inHeapID);

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
extern void EXH_SetUpExHeightData(	const u8 inIndex,
									const int inStX,
									const int inStZ,
									const int inSizX,
									const int inSizZ,
									const fx32 inHeight,
									EHL_PTR outExHeightList );

//--------------------------------------------------------------------------------------------
/**
 * �g�������f�[�^���
 *
 * @param	outExHeightData	�g�������f�[�^�̐擪�|�C���^
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
extern void EXH_FreeExHeightList(EHL_PTR outExHeightList);

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
extern BOOL EXH_HitCheckExHeight(	const int inGridX, const int inGridZ,
									EHL_CONST_PTR inExHeightList,
									u8 *outIndex);

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
extern fx32 EXH_GetExHeight(const u8 inIndex, EHL_CONST_PTR inExHeightList);

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
extern void EXH_SetExHeight(	const u8 inIndex, const fx32 inHeight, EHL_PTR outExHeightList );

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
extern void EXH_SetExHeightValid(	const u8 inIndex, const BOOL inValid, EHL_PTR outExHeightList );

#endif //_HEIGHT_DEF_H_
