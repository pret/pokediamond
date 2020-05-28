//============================================================================================
/**
 * @file	arc_util.c
 * @bfief	�A�[�J�C�u�f�[�^��֗��Ɏg�����߂̃��[�e�B���e�B�֐��Q
 * @author	taya
 * @date	05.08.30
 */
//============================================================================================
#include "common.h"

#include "system\arc_tool.h"
#include "system\arc_util.h"


//==============================================================
// Prototype
//==============================================================



//------------------------------------------------------------------
/**
 * BG����ް��� VRAM �]��
 *
 * @param   fileIdx			������̧�ٲ��ޯ��
 * @param   dataIndex		�������ް����ޯ��
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
u32 ArcUtil_BgCharSet(u32 fileIdx, u32 dataIdx, GF_BGL_INI* bgl, u32 frm, u32 offs, u32 transSize, BOOL compressedFlag, u32 heapID)
{
	void* arcData = ArcUtil_Load( fileIdx, dataIdx, compressedFlag, heapID, ALLOC_TOP );

	if( arcData != NULL )
	{
		NNSG2dCharacterData* charData;

		if( NNS_G2dGetUnpackedBGCharacterData( arcData, &charData ) )
		{
			if( transSize == 0 )
			{
				transSize = charData->szByte;
			}
			GF_BGL_LoadCharacter(bgl, frm, charData->pRawData, transSize, offs);
		}

		sys_FreeMemoryEz( arcData );
	}
    return transSize;
}
//--------------------------------------------------------------------------------------------
/**
 * ��ذ��ް��� VRAM �]��
 * �� BGL���� ��ذ��ޯ̧ ���p�ӂ���Ă���΁A��ذ��ޯ̧ �ւ̓]�����s��
 *
 * @param   fileIdx			������̧�ٲ��ޯ��
 * @param   arcIndex		�������ް����ޯ��
 * @param   bgl				BGL�ް�
 * @param   frm				�]�����ڰ�����
 * @param   offs			�]���̾�āi��גP�ʁj
 * @param	transSize		�]�����黲�ށi�޲ĒP�� ==0�őS�]���j
 * @param   compressedFlag	���k����Ă����ް����H
 * @param   heapID			�ް��ǂݍ��݁E�������؂Ƃ��Ďg��˰��ID
 *
 */
//--------------------------------------------------------------------------------------------
void ArcUtil_ScrnSet(u32 fileIdx, u32 dataIdx, GF_BGL_INI* bgl, u32 frm, u32 offs, u32 transSize, BOOL compressedFlag, u32 heapID)
{
	void* arcData = ArcUtil_Load( fileIdx, dataIdx, compressedFlag, heapID, ALLOC_BOTTOM );

	if( arcData != NULL )
	{
		NNSG2dScreenData* scrnData;

		if( NNS_G2dGetUnpackedScreenData( arcData, &scrnData ) )
		{
			if( transSize == 0 )
			{
				transSize = scrnData->szByte;
			}

			if( GF_BGL_ScreenAdrsGet( bgl, frm ) != NULL )
			{
				GF_BGL_ScreenBufSet( bgl, frm, scrnData->rawData, transSize );
			}
			GF_BGL_LoadScreen( bgl, frm, scrnData->rawData, transSize, offs );
		}
		sys_FreeMemoryEz( arcData );
	}
}
//------------------------------------------------------------------
/**
 * ��گ��ް� �� VRAM �]��
 *
 * @param   fileIdx		������̧�ٲ��ޯ��
 * @param   dataIdx		�������ް����ޯ��
 * @param   palType		��گē]��������
 * @param   offs		��گē]����̾��
 * @param   transSize	��گē]�����ށi0 �őS�]���j
 * @param   heapID		�ް��ǂݍ��������؂Ƃ��Ďg��˰��ID
 *
 */
//------------------------------------------------------------------
void ArcUtil_PalSet( u32 fileIdx, u32 dataIdx, PALTYPE palType, u32 offs, u32 transSize, u32 heapID )
{
	ArcUtil_PalSetEx( fileIdx, dataIdx, palType, 0, offs, transSize, heapID );
}

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
void ArcUtil_PalSetEx( u32 fileIdx, u32 dataIdx, PALTYPE palType, u32 srcOfs, u32 dstOfs, u32 transSize, u32 heapID )
{
		static void (* const load_func[])(const void*, u32, u32) = {
		GX_LoadBGPltt,
		GX_LoadOBJPltt,
		GX_LoadBGExtPltt,
		GX_LoadOBJExtPltt,
		GXS_LoadBGPltt,
		GXS_LoadOBJPltt,
		GXS_LoadBGExtPltt,
		GXS_LoadOBJExtPltt,
	};

	void* arcData = ArcUtil_Load( fileIdx, dataIdx, FALSE, heapID, ALLOC_BOTTOM );

	if( arcData != NULL )
	{
		NNSG2dPaletteData* palData;

		if( NNS_G2dGetUnpackedPaletteData( arcData, &palData ) )
		{
			(u8*)(palData->pRawData) += srcOfs;
			if( transSize == 0 )
			{
				transSize = palData->szByte - srcOfs;
			}
			DC_FlushRange( palData->pRawData, transSize );

			switch( palType ){
			case PALTYPE_MAIN_BG_EX:
				GX_BeginLoadBGExtPltt();
				load_func[ palType ]( palData->pRawData, dstOfs, transSize );
				GX_EndLoadBGExtPltt();
				break;

			case PALTYPE_SUB_BG_EX:
				GXS_BeginLoadBGExtPltt();
				load_func[ palType ]( palData->pRawData, dstOfs, transSize );
				GXS_EndLoadBGExtPltt();
				break;

			case PALTYPE_MAIN_OBJ_EX:
				GX_BeginLoadOBJExtPltt();
				load_func[ palType ]( palData->pRawData, dstOfs, transSize );
				GX_EndLoadOBJExtPltt();
				break;

			case PALTYPE_SUB_OBJ_EX:
				GXS_BeginLoadOBJExtPltt();
				load_func[ palType ]( palData->pRawData, dstOfs, transSize );
				GXS_EndLoadOBJExtPltt();
				break;

			default:
				load_func[ palType ]( palData->pRawData, dstOfs, transSize );
				break;
			}
		}

		sys_FreeMemoryEz( arcData );
	}
}

//------------------------------------------------------------------
/**
 * OBJ ����ް� �� VRAM �]��
 *
 * @param   fileIdx				������̧�ٲ��ޯ��
 * @param   dataIdx				�������ް����ޯ��
 * @param   objType				OBJ����(OBJTYPE_MAIN or OBJTYPE_SUB�j
 * @param   offs				�̾�āi�޲ĒP�ʁj
 * @param   transSize			�]�����ށi�޲ĒP�� : 0 �őS�]���j
 * @param   compressedFlag		���k���ꂽ�ް����H
 * @param   heapID				�ǂݍ��݁E�������؂Ƃ��Ďg��˰��ID
 *
 * @return  �]�������f�[�^�T�C�Y�i�o�C�g�j
 */
//------------------------------------------------------------------
u32 ArcUtil_ObjCharSet( u32 fileIdx, u32 dataIdx, OBJTYPE objType, u32 offs, u32 transSize, BOOL compressedFlag, u32 heapID )
{
	static void (* const load_func[])(const void*, u32, u32) = {
		GX_LoadOBJ,
		GXS_LoadOBJ,
	};

	void* arcData = ArcUtil_Load( fileIdx, dataIdx, compressedFlag, heapID, ALLOC_BOTTOM );

	if( arcData != NULL )
	{
		NNSG2dCharacterData* charData;

		if( NNS_G2dGetUnpackedCharacterData( arcData, &charData ) )
		{
			if( transSize == 0 )
			{
				transSize = charData->szByte;
			}

			DC_FlushRange( charData->pRawData, transSize );
			load_func[ objType ]( charData->pRawData, offs, transSize );
		}
		sys_FreeMemoryEz( arcData );
	}
	return transSize;
}

//------------------------------------------------------------------
/**
 * ��گ��ް� �� VRAM �]���� NITRO System ��گ���۷� ���쐬
 *�i3D, OBJ �p�ɂ̂ݑΉ��BBG �ɂ͎g���܂���j
 *
 * @param   fileIdx		[in] ������̧�ٲ��ޯ��
 * @param   dataIdx		[in] �������ް����ޯ��
 * @param   type		[in] �]��������
 * @param   offs		[in] �]���̾��
 * @param   heapID		[in] ˰��ID
 * @param   proxy		[out]�쐬������۷����ڽ
 *
 *	[ type ]
 *		NNS_G2D_VRAM_TYPE_3DMAIN = 0,
 *		NNS_G2D_VRAM_TYPE_2DMAIN = 1,
 *		NNS_G2D_VRAM_TYPE_2DSUB  = 2,
 *
 */
//------------------------------------------------------------------
void ArcUtil_PalSysLoad( u32 fileIdx, u32 dataIdx, NNS_G2D_VRAM_TYPE type, u32 offs, u32 heapID, NNSG2dImagePaletteProxy* proxy )
{
	void* arcData = ArcUtil_Load( fileIdx, dataIdx, FALSE, heapID, ALLOC_BOTTOM );

	if( arcData != NULL )
	{
		NNSG2dPaletteData*  palData;
		NNSG2dPaletteCompressInfo*  cmpData;
		BOOL  cmpFlag;

		cmpFlag = NNS_G2dGetUnpackedPaletteCompressInfo( arcData, &cmpData );

		if( NNS_G2dGetUnpackedPaletteData( arcData, &palData ) )
		{
			if( cmpFlag )
			{
				NNS_G2dLoadPaletteEx( palData, cmpData, offs, type, proxy );
			}
			else
			{
				NNS_G2dLoadPalette( palData, offs, type, proxy );
			}
		}

		sys_FreeMemoryEz( arcData );
	}
}
//------------------------------------------------------------------
/**
 * ����ް� �� VRAM �]���� NITRO System �Ұ����۷� ���쐬
 *�i3D, OBJ �p�ɂ̂ݑΉ��BBG �ɂ͎g���܂���j
 *
 *
 * @param   fileIdx			[in] ������̧�ٲ��ޯ��
 * @param   dataIdx			[in] �������ް����ޯ��
 * @param   compressedFlag	[in] ���k����Ă��邩
 * @param   mapType			[in] ϯ��ݸ�����
 * @param   transSize		[in] �]���T�C�Y�B�O�Ȃ�S�]���B
 * @param   vramType		[in] �]��������
 * @param   offs			[in] �]���̾��
 * @param   heapID			[in] �����؂Ɏg��˰��ID
 * @param   proxy			[out] �쐬������۷����ڽ
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
u32 ArcUtil_CharSysLoad( u32 fileIdx, u32 dataIdx, BOOL compressedFlag, CHAR_MAPPING_TYPE mapType, u32 transSize,
	NNS_G2D_VRAM_TYPE vramType, u32 offs, u32 heapID, NNSG2dImageProxy* proxy )
{
	static void (* const load_func[])(const NNSG2dCharacterData*, u32, NNS_G2D_VRAM_TYPE, NNSG2dImageProxy*) = {
		NNS_G2dLoadImage1DMapping,
		NNS_G2dLoadImage2DMapping,
	};

	void* arcData = ArcUtil_Load( fileIdx, dataIdx, compressedFlag, heapID, ALLOC_BOTTOM );
	u32  transed_size = 0;

	if( arcData != NULL )
	{
		NNSG2dCharacterData* charData;

		if( NNS_G2dGetUnpackedCharacterData( arcData, &charData ) )
		{
			if( transSize )
			{
				charData->szByte = transSize;
			}
			load_func[ mapType ]( charData, offs, vramType, proxy );
			transed_size = charData->szByte;
		}
		sys_FreeMemoryEz( arcData );
	}

	return transed_size;
}
//------------------------------------------------------------------
/**
 * ����ް� �� VRAM �]���� NITRO System �Ұ����۷� ���쐬
 *�i3D, OBJ �p�ɂ̂ݑΉ��BBG �ɂ͎g���܂���j
 *
 * ����ް���ϯ��ݸ�Ӱ�ޒl���A���݂�ڼ޽��ݒ�ɍ��킹�ď��������܂�
 *
 * @param   fileIdx			[in] ������̧�ٲ��ޯ��
 * @param   dataIdx			[in] �������ް����ޯ��
 * @param   compressedFlag	[in] ���k����Ă��邩
 * @param   mapType			[in] ϯ��ݸ�����
 * @param   transSize		[in] �]���T�C�Y�B�O�Ȃ�S�]���B
 * @param   vramType		[in] �]��������
 * @param   offs			[in] �]���̾��
 * @param   heapID			[in] �����؂Ɏg��˰��ID
 * @param   proxy			[out] �쐬������۷����ڽ
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
void ArcUtil_CharSysLoadSyncroMappingMode( u32 fileIdx, u32 dataIdx, BOOL compressedFlag, CHAR_MAPPING_TYPE mapType, u32 transSize,
	NNS_G2D_VRAM_TYPE vramType, u32 offs, u32 heapID, NNSG2dImageProxy* proxy )
{
	static void (* const load_func[])(const NNSG2dCharacterData*, u32, NNS_G2D_VRAM_TYPE, NNSG2dImageProxy*) = {
		NNS_G2dLoadImage1DMapping,
		NNS_G2dLoadImage2DMapping,
	};

	void* arcData = ArcUtil_Load( fileIdx, dataIdx, compressedFlag, heapID, ALLOC_BOTTOM );

	if( arcData != NULL )
	{
		NNSG2dCharacterData* charData;

		if( NNS_G2dGetUnpackedCharacterData( arcData, &charData ) )
		{
			if( transSize )
			{
				charData->szByte = transSize;
			}

			switch( vramType ){
			case NNS_G2D_VRAM_TYPE_2DMAIN:
				charData->mapingType = GX_GetOBJVRamModeChar();
				break;
			case NNS_G2D_VRAM_TYPE_2DSUB:
				charData->mapingType = GXS_GetOBJVRamModeChar();
				break;
			}
			load_func[ mapType ]( charData, offs, vramType, proxy );
		}
		sys_FreeMemoryEz( arcData );
	}
}

//------------------------------------------------------------------
/**
 * ����ް� �� VRAM �]���� NITRO System �Ұ����۷� ���쐬�BVRAM�]���^�̉摜�f�ޗp�B
 *
 * �� ���̊֐����g���Ă��AVRAM�ɉ摜�͓]������܂���
 *    ���̊֐���۰�ނ����ް��͉������܂���B�߂�l��const void*���Ǘ����āA
 *    �s�v�ɂȂ��������������s���Ă��������B
 *
 * @param   fileIdx			[in] ������̧�ٲ��ޯ��
 * @param   dataIdx			[in] �������ް����ޯ��
 * @param   compressedFlag	[in] ���k����Ă��邩
 * @param   vramType		[in] �]��������
 * @param   offs			[in] �]���̾��
 * @param   heapID			[in] �����؂Ɏg��˰��ID
 * @param   proxy			[out] �쐬������۷��̱��ڽ
 * @param   charData		[out] ����ް����ڽ��ێ������߲���̱��ڽ
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
const void* ArcUtil_TransTypeCharSysLoad( u32 fileIdx, u32 dataIdx, BOOL compressedFlag, 
	NNS_G2D_VRAM_TYPE vramType, u32 offs, u32 heapID, NNSG2dImageProxy* proxy, NNSG2dCharacterData** charData )
{
	void* arcData = ArcUtil_Load( fileIdx, dataIdx, compressedFlag, heapID, ALLOC_TOP );

	if( arcData != NULL )
	{
		if( NNS_G2dGetUnpackedCharacterData( arcData, charData ) )
		{
			NNS_G2dLoadImageVramTransfer( *charData, offs, vramType, proxy );
		}
	}
	return arcData;
}



//------------------------------------------------------------------
/**
 * ����ް��� ۰�ނ��� Unpack ���邾���ł��B����͊e���ŁB
 *
 * @param   fileIdx				[in] ������̧�ٲ��ޯ��
 * @param   dataIdx				[in] �ް����ޯ��
 * @param   compressedFlag		[in] ���k����Ă��邩
 * @param   charData			[out] ����ް����ڽ��ێ������߲���̱��ڽ
 * @param   heapID				[in] ˰��ID
 *
 * @retval  void*		۰�ނ����ް��̐擪�߲��
 */
//------------------------------------------------------------------
void* ArcUtil_CharDataGet( u32 fileIdx, u32 dataIdx, BOOL compressedFlag, NNSG2dCharacterData** charData, u32 heapID )
{
	void* arcData = ArcUtil_Load( fileIdx, dataIdx, compressedFlag, heapID, ALLOC_TOP );

	if( arcData != NULL )
	{
		if( NNS_G2dGetUnpackedBGCharacterData( arcData, charData ) == FALSE)
		{
			// ���s������NULL
			sys_FreeMemoryEz( arcData );
			return NULL;
		}
	}
	return arcData;
}
//--------------------------------------------------------------------------------------------
/**
 * ��ذ��ް��� ۰�ނ��� Unpack ���邾���ł��B����͊e���ŁB
 *
 * @param   fileIdx			[in] ������̧�ٲ��ޯ��
 * @param   arcIndex		[in] �������ް����ޯ��
 * @param   compressedFlag	[in] ���k����Ă����ް����H
 * @param   scrnData		[out] ��ذ��ް����ڽ��ێ������߲���̱��ڽ
 * @param   heapID			[in] ˰��ID
 *
 * @retval  void*		۰�ނ����ް��̐擪�߲��
 */
//--------------------------------------------------------------------------------------------
void* ArcUtil_ScrnDataGet(u32 fileIdx, u32 dataIdx, BOOL compressedFlag, NNSG2dScreenData** scrnData, u32 heapID)
{
	void* arcData = ArcUtil_Load( fileIdx, dataIdx, compressedFlag, heapID, ALLOC_TOP );

	if( arcData != NULL )
	{
		if( NNS_G2dGetUnpackedScreenData( arcData, scrnData ) == FALSE )
		{
			sys_FreeMemoryEz( arcData );
			return NULL;
		}
	}
	return arcData;
}
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
void* ArcUtil_PalDataGet( u32 fileIdx, u32 dataIdx, NNSG2dPaletteData** palData, u32 heapID )
{
	void* arcData = ArcUtil_Load( fileIdx, dataIdx, FALSE, heapID, ALLOC_TOP );

	if( arcData != NULL )
	{
		if( NNS_G2dGetUnpackedPaletteData( arcData, palData ) == FALSE )
		{
			sys_FreeMemoryEz( arcData );
			return NULL;
		}
	}
	return arcData;
}
//--------------------------------------------------------------------------------------------
/**
 * ����ݸ�ް��� ۰�ނ��� Unpack ���邾���ł��B����͊e���ŁB
 *
 * @param   fileIdx			������̧�ٲ��ޯ��
 * @param   arcIndex		�������ް����ޯ��
 * @param   compressedFlag	���k����Ă����ް����H
 * @param   cellBank		����ݸ�ް����ڽ��ێ������߲���̱��ڽ
 * @param   heapID			˰��ID
 * @param   pSize			����ݸ���޲Ļ��ނ��󂯎��ϐ��߲���i�v��Ȃ����NULL�Łj
 *
 * @retval  void*		۰�ނ����ް��̐擪�߲��
 */
//--------------------------------------------------------------------------------------------
void* ArcUtil_CellBankDataGet(u32 fileIdx, u32 dataIdx, BOOL compressedFlag, NNSG2dCellDataBank** cellBank, u32 heapID )
{
	void* arcData;

	arcData = ArcUtil_Load( fileIdx, dataIdx, compressedFlag, heapID, ALLOC_TOP );

	if( arcData != NULL )
	{
		if( NNS_G2dGetUnpackedCellBank( arcData, cellBank ) == FALSE )
		{
			sys_FreeMemoryEz( arcData );
			return NULL;
		}
	}
	return arcData;
}
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
void* ArcUtil_AnimBankDataGet(u32 fileIdx, u32 dataIdx, BOOL compressedFlag, NNSG2dAnimBankData** anmBank, u32 heapID)
{
	void* arcData = ArcUtil_Load( fileIdx, dataIdx, compressedFlag, heapID, ALLOC_TOP );

	if( arcData != NULL )
	{
		if( NNS_G2dGetUnpackedAnimBank( arcData, anmBank ) == FALSE )
		{
			sys_FreeMemoryEz( arcData );
			return NULL;
		}
	}
	return arcData;
}











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
void* ArcUtil_UnCompress(u32 fileIdx, u32 dataIdx, u32 heapID)
{
	return ArcUtil_Load(fileIdx, dataIdx, TRUE, heapID, ALLOC_TOP);
}

//------------------------------------------------------------------
/**
 * �A�[�J�C�u�f�[�^�̓ǂݏo���i�������m�ۂ���j
 *
 * @param   fileIdx			�A�[�J�C�u�t�@�C���C���f�b�N�X
 * @param   dataIdx			�A�[�J�C�u�f�[�^�C���f�b�N�X
 * @param   compressedFlag	���k����Ă��邩�H
 * @param   heapID			�������m�ۂɎg���q�[�v�h�c
 * @param   allocType		�q�[�v�̂ǂ̈ʒu���烁�����m�ۂ��邩
 *
 * @retval  void*			�ǂݏo���̈�|�C���^
 */
//------------------------------------------------------------------
void* ArcUtil_Load(u32 fileIdx, u32 dataIdx, BOOL compressedFlag, u32 heapID, ALLOC_TYPE allocType)
{
	void* arcData;

	if( compressedFlag || allocType == ALLOC_BOTTOM )
	{
		arcData = sys_AllocMemoryLo( heapID, ArchiveDataSizeGet(fileIdx, dataIdx) );
	}
	else
	{
		arcData = sys_AllocMemory( heapID, ArchiveDataSizeGet(fileIdx, dataIdx) );
	}

	if( arcData != NULL )
	{
		ArchiveDataLoad(arcData, fileIdx, dataIdx);
		if( compressedFlag )
		{
			void* data;

			if( allocType == ALLOC_TOP )
			{
				data = sys_AllocMemory( heapID, MI_GetUncompressedSize( arcData ) );
			}
			else
			{
				data = sys_AllocMemoryLo( heapID, MI_GetUncompressedSize( arcData ) );
			}

			if( data )
			{
				MI_UncompressLZ8( arcData, data );
				sys_FreeMemoryEz( arcData );
			}
			arcData = data;
		}
	}
	return arcData;
}
//------------------------------------------------------------------
/**
 * �A�[�J�C�u�f�[�^�̓ǂݏo���i�ǂݏo�����T�C�Y���擾�ł���j
 *
 * @param   fileIdx			�A�[�J�C�u�t�@�C���C���f�b�N�X
 * @param   dataIdx			�A�[�J�C�u�f�[�^�C���f�b�N�X
 * @param   compressedFlag	���k����Ă��邩�H
 * @param   heapID			�������m�ۂɎg���q�[�v�h�c
 * @param   allocType		�q�[�v�̂ǂ̈ʒu���烁�����m�ۂ��邩
 * @param   pSize			���f�[�^�̃o�C�g�T�C�Y�i���k����Ă���ꍇ�͓W�J��j
 *
 * @retval  void*			�ǂݏo���̈�|�C���^
 */
//------------------------------------------------------------------
void* ArcUtil_LoadEx(u32 fileIdx, u32 dataIdx, BOOL compressedFlag, u32 heapID, ALLOC_TYPE allocType, u32* pSize)
{
	void* arcData;

	*pSize = ArchiveDataSizeGet(fileIdx, dataIdx);

	if( compressedFlag || allocType == ALLOC_BOTTOM )
	{
		arcData = sys_AllocMemoryLo( heapID, *pSize );
	}
	else
	{
		arcData = sys_AllocMemory( heapID, *pSize );
	}

	if( arcData != NULL )
	{
		ArchiveDataLoad(arcData, fileIdx, dataIdx);
		if( compressedFlag )
		{
			void* data;

			*pSize = MI_GetUncompressedSize( arcData );

			if( allocType == ALLOC_TOP )
			{
				data = sys_AllocMemory( heapID, *pSize );
			}
			else
			{
				data = sys_AllocMemoryLo( heapID, *pSize );
			}

			if( data )
			{
				MI_UncompressLZ8( arcData, data );
				sys_FreeMemoryEz( arcData );
			}
			arcData = data;
		}
	}
	return arcData;
}
