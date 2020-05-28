//============================================================================================
/**
 * @file	arc_util.h
 * @bfief	�A�[�J�C�u�f�[�^��֗��Ɏg�����߂̃��[�e�B���e�B�֐��Q
 * @author	taya
 * @date	05.08.30
 */
//============================================================================================
#ifndef __ARC_UTIL_H__
#define __ARC_UTIL_H__

#include "gflib\bg_system.h"
#include "system\arc_tool.h"


//------------------------------------------------------------------
/**
 *  �L�����f�[�^�}�b�s���O�^�C�v
 */
//------------------------------------------------------------------
typedef enum {
	ALLOC_TOP = 0,			///< �q�[�v�̐擪����
	ALLOC_BOTTOM = 1,		///< �q�[�v�̏I�[����
}ALLOC_TYPE;

//------------------------------------------------------------------
/**
 *  �p���b�g�]����^�C�v�w��
 */
//------------------------------------------------------------------
typedef enum {
	PALTYPE_MAIN_BG,			// ���C��BG
	PALTYPE_MAIN_OBJ,			// ���C��OBJ
	PALTYPE_MAIN_BG_EX,			// ���C���g��BG
	PALTYPE_MAIN_OBJ_EX,		// ���C���g��OBJ
	PALTYPE_SUB_BG,				// �T�uBG
	PALTYPE_SUB_OBJ,			// �T�uOBJ
	PALTYPE_SUB_BG_EX,			// �T�u�g��BG
	PALTYPE_SUB_OBJ_EX,			// �T�u�g��OBJ
}PALTYPE;

//------------------------------------------------------------------
/**
 *  OBJ�L�����f�[�^�]����^�C�v�w��
 */
//------------------------------------------------------------------
typedef enum {
	OBJTYPE_MAIN,
	OBJTYPE_SUB,
}OBJTYPE;

//------------------------------------------------------------------
/**
 *  �L�����f�[�^�}�b�s���O�^�C�v
 */
//------------------------------------------------------------------
typedef enum {
	CHAR_MAP_1D,		// 1D 
	CHAR_MAP_2D,		// 2D
}CHAR_MAPPING_TYPE;


//------------------------------------------------------------------
/**
 * BG����ް��� VRAM �]��
 *
 * @param   arcFile			�A�[�J�C�u�t�@�C���C���f�b�N�X
 * @param   arcIndex		�A�[�J�C�u�f�[�^�C���f�b�N�X
 * @param   bgl				BGL�ް�
 * @param   frm				�]�����ڰ�����
 * @param   offs			�]���̾�āi��גP�ʁj
 * @param	transSize		�]�����黲�ށi�޲ĒP�� ==0�őS�]���j
 * @param   compressedFlag	���k����Ă����ް����H
 * @param   heapID			�ް��ǂݍ��݁E�������؂Ƃ��Ďg��˰��ID
 *
 * @return  �]�������f�[�^�T�C�Y�i�o�C�g�j
 */
//------------------------------------------------------------------
extern u32 ArcUtil_BgCharSet(u32 arcFile, u32 dataIdx, GF_BGL_INI* bgl, u32 frm, u32 offs, u32 transSize, BOOL compressedFlag, u32 heapID);


//------------------------------------------------------------------
/**
 * OBJ ����ް� �� VRAM �]��
 *
 * @param   fileIdx				�A�[�J�C�u�t�@�C���C���f�b�N�X
 * @param   dataIdx				�A�[�J�C�u�f�[�^�C���f�b�N�X
 * @param   objType				OBJ����
 * @param   offs				�̾�āi�޲ĒP�ʁj
 * @param   transSize			�]�����ށi�޲ĒP�� : 0 �őS�]���j
 * @param   compressedFlag		���k���ꂽ�ް����H
 * @param   heapID				�ǂݍ��݁E�������؂Ƃ��Ďg��˰��ID
 *
 * @return  �]�������f�[�^�T�C�Y�i�o�C�g�j
 */
//------------------------------------------------------------------
extern u32 ArcUtil_ObjCharSet( u32 fileIdx, u32 dataIdx, OBJTYPE objType, u32 offs, u32 transSize, BOOL compressedFlag, u32 heapID );


//--------------------------------------------------------------------------------------------
/**
 * ��ذ��ް��� VRAM �]��
 * �� BGL���� ��ذ��ޯ̧ ���p�ӂ���Ă���΁A��ذ��ޯ̧ �ւ̓]�����s��
 *
 * @param   arcFile			�A�[�J�C�u�t�@�C���C���f�b�N�X
 * @param   arcIndex		�A�[�J�C�u�f�[�^�C���f�b�N�X
 * @param   bgl				BGL�ް�
 * @param   frm				�]�����ڰ�����
 * @param   offs			�]���̾�āi��גP�ʁj
 * @param	transSize		�]�����黲�ށi�޲ĒP�� ==0�őS�]���j
 * @param   compressedFlag	���k����Ă����ް����H
 * @param   heapID			�ް��ǂݍ��݁E�������؂Ƃ��Ďg��˰��ID
 *
 */
//--------------------------------------------------------------------------------------------
extern void ArcUtil_ScrnSet(u32 arcFile, u32 dataIdx, GF_BGL_INI* bgl, u32 frm, u32 offs, u32 transSize, BOOL compressedFlag, u32 heapID);


//------------------------------------------------------------------
/**
 * ��گ��ް� �� VRAM �]��
 *
 * @param   arcFile		�A�[�J�C�u�t�@�C���C���f�b�N�X
 * @param   dataIdx		�A�[�J�C�u�f�[�^�C���f�b�N�X
 * @param   palType		��گē]��������
 * @param   offs		��گē]����̾��
 * @param   transSize	��گē]�����ށi0 �őS�]���j
 * @param   heapID		�ް��ǂݍ��������؂Ƃ��Ďg��˰��ID
 *
 */
//------------------------------------------------------------------
extern void ArcUtil_PalSet( u32 arcFile, u32 dataIdx, PALTYPE palType, u32 offs, u32 transSize, u32 heapID );


//------------------------------------------------------------------
/**
 * ��گ��ް� �� VRAM �]���i�]�����̓ǂݍ��݊J�n�̾�Ďw��Łj
 *
 * @param   fileIdx		������̧�ٲ��ޯ��
 * @param   dataIdx		�������ް����ޯ��
 * @param   palType		��گē]��������
 * @param   srcOfs		��گē]�����ǂݍ��݊J�n�̾��
 * @param   dstOfs		��گē]����̾��
 * @param   transSize	��گē]�����ށi0 �őS�]���j
 * @param   heapID		�ް��ǂݍ��������؂Ƃ��Ďg��˰��ID
 *
 */
//------------------------------------------------------------------
extern void ArcUtil_PalSetEx( u32 fileIdx, u32 dataIdx, PALTYPE palType, u32 srcOfs, u32 dstOfs, u32 transSize, u32 heapID );

//------------------------------------------------------------------
/**
 * ��گ��ް� �� VRAM �]���� NITRO System ��گ���۷� ���쐬
 *�i3D, OBJ �p�ɂ̂ݑΉ��BBG �ɂ͎g���܂���j
 *
 * @param   fileIdx		������̧�ٲ��ޯ��
 * @param   dataIdx		�������ް����ޯ��
 * @param   type		�]��������
 * @param   offs		�]���̾��
 * @param   heapID		˰��ID
 * @param   proxy		�쐬������۷��̱��ڽ
 *
 *	[ type ]
 *		NNS_G2D_VRAM_TYPE_3DMAIN = 0,
 *		NNS_G2D_VRAM_TYPE_2DMAIN = 1,
 *		NNS_G2D_VRAM_TYPE_2DSUB  = 2,
 *
 */
//------------------------------------------------------------------
extern void ArcUtil_PalSysLoad( u32 fileIdx, u32 dataIdx, NNS_G2D_VRAM_TYPE type, u32 offs, u32 heapID, NNSG2dImagePaletteProxy* proxy );

//------------------------------------------------------------------
/**
 * ����ް� �� VRAM �]���� NITRO System �Ұ����۷� ���쐬
 *�i3D, OBJ �p�ɂ̂ݑΉ��BBG �ɂ͎g���܂���j
 *
 *
 * @param   fileIdx			������̧�ٲ��ޯ��
 * @param   dataIdx			�������ް����ޯ��
 * @param   compressedFlag	���k����Ă��邩
 * @param   mapType			ϯ��ݸ�����
 * @param   transSize		�]�����ށi0�Ȃ�S�]���j
 * @param   vramType		�]��������
 * @param   offs			�]���̾��
 * @param   heapID			�����؂Ɏg��˰��ID
 * @param   proxy			�쐬������۷��̱��ڽ
 *
 * @retval  �]�����ꂽ�ް����ށi�޲ĒP�ʁj
 *
 *	[ mapType ]
 *		MAP_TYPE_1D = 0,
 *		MAP_TYPE_2D = 1,
 *
 *	�� VRAM�]���^�͕ʊ֐� ArcUtil_TranCharSysLoad ���g��
 *
 *	[ vramType ]
 *		NNS_G2D_VRAM_TYPE_3DMAIN = 0,
 *		NNS_G2D_VRAM_TYPE_2DMAIN = 1,
 *		NNS_G2D_VRAM_TYPE_2DSUB  = 2,
 *
 */
//------------------------------------------------------------------
extern u32 ArcUtil_CharSysLoad( u32 fileIdx, u32 dataIdx, BOOL compressedFlag, CHAR_MAPPING_TYPE mapType,
	u32 transSize, NNS_G2D_VRAM_TYPE vramType, u32 offs, u32 heapID, NNSG2dImageProxy* proxy );


//------------------------------------------------------------------
/**
 * ����ް� �� VRAM �]���� NITRO System �Ұ����۷� ���쐬
 *�i3D, OBJ �p�ɂ̂ݑΉ��BBG �ɂ͎g���܂���j
 *
 * ����ް���ϯ��ݸ�Ӱ�ޒl���A���݂�ڼ޽��ݒ�ɍ��킹�ď��������܂�
 *
 * @param   fileIdx			������̧�ٲ��ޯ��
 * @param   dataIdx			�������ް����ޯ��
 * @param   compressedFlag	���k����Ă��邩
 * @param   mapType			ϯ��ݸ�����
 * @param   transSize		�]���T�C�Y�B�O�Ȃ�S�]���B
 * @param   vramType		�]��������
 * @param   offs			�]���̾��
 * @param   heapID			�����؂Ɏg��˰��ID
 * @param   proxy			�쐬������۷����ڽ
 *
 *
 *	[ mapType ]
 *		CHAR_MAP_1D = 0,
 *		CHAR_MAP_2D = 1,
 *
 *	�� VRAM�]���^�͕ʊ֐� ArcUtil_TranCharSysLoad ���g��
 *
 *	[ vramType ]
 *		NNS_G2D_VRAM_TYPE_3DMAIN = 0,
 *		NNS_G2D_VRAM_TYPE_2DMAIN = 1,
 *		NNS_G2D_VRAM_TYPE_2DSUB  = 2,
 *
 */
//------------------------------------------------------------------
extern void ArcUtil_CharSysLoadSyncroMappingMode( u32 fileIdx, u32 dataIdx, BOOL compressedFlag, CHAR_MAPPING_TYPE mapType, u32 transSize,
	NNS_G2D_VRAM_TYPE vramType, u32 offs, u32 heapID, NNSG2dImageProxy* proxy );

//------------------------------------------------------------------
/**
 * ����ް� �� VRAM �]���� NITRO System �Ұ����۷� ���쐬�BVRAM�]���^�̉摜�f�ޗp�B
 *
 * �� ���̊֐����g���Ă��AVRAM�ɉ摜�͓]������܂���
 *    ���̊֐���۰�ނ����ް��͉������܂���B�߂�l��const void*���Ǘ����āA
 *    �s�v�ɂȂ��������������s���Ă��������B
 *
 * @param   fileIdx			������̧�ٲ��ޯ��
 * @param   dataIdx			�������ް����ޯ��
 * @param   compressedFlag	���k����Ă��邩
 * @param   vramType		�]��������
 * @param   offs			�]���̾��
 * @param   heapID			�����؂Ɏg��˰��ID
 * @param   proxy			�쐬������۷��̱��ڽ
 * @param   charData		����ް����ڽ��ێ������߲���̱��ڽ
 *
 * @retval  const void*		۰�ނ����ް��̱��ڽ
 *
 *	[ vramType ]
 *		NNS_G2D_VRAM_TYPE_3DMAIN = 0,
 *		NNS_G2D_VRAM_TYPE_2DMAIN = 1,
 *		NNS_G2D_VRAM_TYPE_2DSUB  = 2,
 *
 */
//------------------------------------------------------------------
extern const void* ArcUtil_TransTypeCharSysLoad( u32 fileIdx, u32 dataIdx, BOOL compressedFlag, 
	NNS_G2D_VRAM_TYPE vramType, u32 offs, u32 heapID, NNSG2dImageProxy* proxy, NNSG2dCharacterData** charData );


//------------------------------------------------------------------
/**
 * ����ް��� ۰�ނ��� Unpack ���邾���ł��B����͊e���ŁB
 *
 * @param   fileIdx				������̧�ٲ��ޯ��
 * @param   dataIdx				�ް����ޯ��
 * @param   compressedFlag		���k����Ă��邩
 * @param   charData			����ް����ڽ��ێ������߲���̱��ڽ
 * @param   heapID				˰��ID
 *
 * @retval  void*		۰�ނ����ް��̐擪�߲��
 */
//------------------------------------------------------------------
extern void* ArcUtil_CharDataGet( u32 fileIdx, u32 dataIdx, BOOL compressedFlag, NNSG2dCharacterData** charData, u32 heapID );

//--------------------------------------------------------------------------------------------
/**
 * ��ذ��ް��� ۰�ނ��� Unpack ���邾���ł��B����͊e���ŁB
 *
 * @param   fileIdx			������̧�ٲ��ޯ��
 * @param   arcIndex		�������ް����ޯ��
 * @param   compressedFlag	���k����Ă����ް����H
 * @param   scrnData		��ذ��ް����ڽ��ێ������߲���̱��ڽ
 * @param   heapID			�ް��ǂݍ��݁E�������؂Ƃ��Ďg��˰��ID
 *
 * @retval  void*		۰�ނ����ް��̐擪�߲��
 */
//--------------------------------------------------------------------------------------------
extern void* ArcUtil_ScrnDataGet(u32 fileIdx, u32 dataIdx, BOOL compressedFlag, NNSG2dScreenData** scrnData, u32 heapID);

//------------------------------------------------------------------
/**
 * ��گ��ް���۰�ނ��� Unpack ���邾���ł��B����͊e���ŁB
 *
 * @param   fileIdx			������̧�ٲ��ޯ��
 * @param   arcIndex		�������ް����ޯ��
 * @param   palData			��گ��ް����ڽ��ێ������߲���̱��ڽ
 * @param   heapID			˰��ID
 *
 * @retval  void*		۰�ނ����ް��̐擪�߲��
 */
//------------------------------------------------------------------
extern void* ArcUtil_PalDataGet( u32 fileIdx, u32 dataIdx, NNSG2dPaletteData** palData, u32 heapID );

//--------------------------------------------------------------------------------------------
/**
 * ����ݸ�ް��� ۰�ނ��� Unpack ���邾���ł��B����͊e���ŁB
 *
 * @param   fileIdx			������̧�ٲ��ޯ��
 * @param   arcIndex		�������ް����ޯ��
 * @param   compressedFlag	���k����Ă����ް����H
 * @param   cellBank		����ݸ�ް����ڽ��ێ������߲���̱��ڽ
 * @param   heapID			˰��ID
 *
 * @retval  void*		۰�ނ����ް��̐擪�߲��
 */
//--------------------------------------------------------------------------------------------
extern void* ArcUtil_CellBankDataGet(u32 fileIdx, u32 dataIdx, BOOL compressedFlag, NNSG2dCellDataBank** cellBank, u32 heapID );

//--------------------------------------------------------------------------------------------
/**
 * �����ݸ�ް��� ۰�ނ��� Unpack ���邾���ł��B����͊e���ŁB
 *
 * @param   fileIdx			������̧�ٲ��ޯ��
 * @param   arcIndex		�������ް����ޯ��
 * @param   compressedFlag	���k����Ă����ް����H
 * @param   anmBank			�����ݸ�ް����ڽ��ێ������߲���̱��ڽ
 * @param   heapID			˰��ID
 *
 * @retval  void*		۰�ނ����ް��̐擪�߲��
 */
//--------------------------------------------------------------------------------------------
extern void* ArcUtil_AnimBankDataGet(u32 fileIdx, u32 dataIdx, BOOL compressedFlag, NNSG2dAnimBankData** anmBank, u32 heapID);


//------------------------------------------------------------------
/**
 * LZ���k��A�[�J�C�u����Ă���f�[�^��ǂݏo���A�𓀂��ĕԂ�
 *
 * @param   fileIdx		�A�[�J�C�u�t�@�C���C���f�b�N�X
 * @param   dataIdx		�A�[�J�C�u�f�[�^�C���f�b�N�X
 * @param   heapID		�ǂݏo���E�𓀂Ɏg���q�[�v�h�c
 *
 * @retval  void*		�𓀌�̃f�[�^�ۑ���A�h���X
 */
//------------------------------------------------------------------
extern void* ArcUtil_UnCompress(u32 fileIdx, u32 dataIdx, u32 heapID);


//------------------------------------------------------------------
/**
 * �A�[�J�C�u�f�[�^�̓ǂݏo��
 *
 * @param   fileIdx			�A�[�J�C�u�t�@�C���C���f�b�N�X
 * @param   dataIdx			�A�[�J�C�u�f�[�^�C���f�b�N�X
 * @param   compressedFlag	���k����Ă��邩�H
 * @param   heapID			�������m�ۂɎg���q�[�v�h�c
 * @param   allocType		�q�[�v�̂ǂ̈ʒu���烁�����m�ۂ��邩
 *
 * [allocType]
 *		ALLOC_TOP		�q�[�v�擪����m��
 *		ALLOC_BOTTOM	�q�[�v�������m��
 *
 * @retval  void*			�ǂݏo���̈�|�C���^
 */
//------------------------------------------------------------------
extern void* ArcUtil_Load(u32 fileIdx, u32 dataIdx, BOOL compressedFlag, u32 heapID, ALLOC_TYPE allocType);

//------------------------------------------------------------------
/**
 * �A�[�J�C�u�f�[�^�̓ǂݏo�����f�[�^�T�C�Y�擾�i���k����Ă�����𓀌�̃T�C�Y���擾����j
 *
 * @param   fileIdx			�A�[�J�C�u�t�@�C���C���f�b�N�X
 * @param   dataIdx			�A�[�J�C�u�f�[�^�C���f�b�N�X
 * @param   compressedFlag	���k����Ă��邩�H
 * @param   heapID			�������m�ۂɎg���q�[�v�h�c
 * @param   allocType		�q�[�v�̂ǂ̈ʒu���烁�����m�ۂ��邩
 * @param   pSize			���f�[�^�̃o�C�g�T�C�Y���󂯎��ϐ��̃|�C���^
 *
 * [allocType]
 *		ALLOC_TOP		�q�[�v�擪����m��
 *		ALLOC_BOTTOM	�q�[�v�������m��
 *
 * @retval  void*			�ǂݏo���̈�|�C���^
 */
//------------------------------------------------------------------
extern void* ArcUtil_LoadEx(u32 fileIdx, u32 dataIdx, BOOL compressedFlag, u32 heapID, ALLOC_TYPE allocType, u32* pSize);



#endif
