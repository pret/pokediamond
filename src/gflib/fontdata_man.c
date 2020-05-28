//=============================================================================================
/**
 * @file	fontdata_man.c
 * @brief	�t�H���g�f�[�^�}�l�[�W��
 * @author	taya
 * @date	2005.09.14
 */
//=============================================================================================
#include	"common.h"
#include	"bg_system.h"
#include	"fntsys.h"
#include	"gflib\fontdata_man.h"

#include	"system\arc_tool.h"

typedef u8 (*pWidthGetFunc)(const GF_FONTDATA_MAN*, u32);
typedef void (*pGetBitmapFunc)(const GF_FONTDATA_MAN*, STRCODE, MSG_FONT_DATA* );


enum {
	SRC_CHAR_SIZE = 0x10,
	SRC_CHAR_MAX = 4,

	SRC_CHAR_MAXSIZE = SRC_CHAR_SIZE*SRC_CHAR_MAX,
};

// �P����������̃L�����T�C�Y
enum {
	LETTERSIZE_1x1 = 0,
	LETTERSIZE_1x2,
	LETTERSIZE_2x1,
	LETTERSIZE_2x2,
};

//------------------------------------------------------------------
/**
 * �t�H���g�f�[�^�w�b�_
 */
//------------------------------------------------------------------
typedef struct {
	u32		bitDataOffs;	// �f�[�^�擪����t�H���g�f�[�^�e�[�u���ւ̃o�C�g�P�ʃI�t�Z�b�g
	u32		widthTblOffs;	// �f�[�^�擪���當�����e�[�u���ւ̃o�C�g�P�ʃI�t�Z�b�g�i�e�[�u����������΂O�j
	u32		letterMax;		// �o�^������
	u8		maxWidth;		// �ő啶�����i�h�b�g�j
	u8		maxHeight;		// �ő啶�������i�h�b�g�j
	u8		letterCharX;	// �P�����̉��L������
	u8		letterCharY;	// �P�����̏c�L������
}FONTDATA_HEADER;


typedef struct {

	ARCHANDLE*    file_handle;
	u8            read_buffer[SRC_CHAR_MAXSIZE];


}FILEREAD_TYPE_WORK;

//------------------------------------------------------------------
/**
 * �}�l�[�W�����[�N
 */
//------------------------------------------------------------------
struct  _GF_FONTDATA_MAN	{
	FONTDATA_LOADTYPE        loadType;
	pGetBitmapFunc           GetBitmapFunc;

	u32                      charShape;
	u32                      letterCharSize;

	u8*                      fontBitData;
	u8                       readBuffer[SRC_CHAR_MAXSIZE];

	ARCHANDLE*               fileHandle;
	u32                      fileDatID;

	FONTDATA_HEADER          fontHeader;
	BOOL                     fixedFontFlag;

	pWidthGetFunc            WidthGetFunc;
	u8*                      widthTbl;
};



//==============================================================
// Prototype
//==============================================================
static void load_font_header( GF_FONTDATA_MAN* wk, u32 arcID, u32 datID, BOOL fixedFontFlag, u32 heapID );
static void unload_font_header( GF_FONTDATA_MAN* wk );
static void setup_font_datas( GF_FONTDATA_MAN* wk, FONTDATA_LOADTYPE loadType, u32 heapID );
static void setup_type_on_memory( GF_FONTDATA_MAN* wk, u32 heapID );
static void setup_type_read_file( GF_FONTDATA_MAN* wk, u32 heapID );
static void cleanup_font_datas( GF_FONTDATA_MAN* wk );
static void cleanup_type_on_memory( GF_FONTDATA_MAN* wk );
static void cleanup_type_read_file( GF_FONTDATA_MAN* wk );
static void GetBitmapOnMemory( const GF_FONTDATA_MAN* wk, STRCODE fcode, MSG_FONT_DATA* dst );
static void GetBitmapFileRead( const GF_FONTDATA_MAN* wk, STRCODE fcode, MSG_FONT_DATA* dst );
static u8 GetWidthProportionalFont( const GF_FONTDATA_MAN* wk, u32 bcode );
static u8 GetWidthFixedFont( const GF_FONTDATA_MAN* wk, u32 bcode );



//==============================================================================================
/**
 * �t�H���g�f�[�^�}�l�[�W���쐬
 *
 * @param   arcID			�t�H���g�f�[�^���i�[����Ă���A�[�J�C�uID
 * @param   datID			�t�H���g�f�[�^���i�[����Ă���A�[�J�C�u���t�@�C��ID
 * @param   loadType		�t�H���g�f�[�^�̓ǂݏo������
 * @param   fixedFontFlag	TRUE�Ȃ瓙���t�H���g�Ƃ��Ĉ���
 * @param   heapID			�}�l�[�W���쐬��q�[�vID
 *
 * @retval  GF_FONTDATA_MAN*	�t�H���g�f�[�^�}�l�[�W���|�C���^
 *
 * @li  loadType �� FONTDATA_LOADTYPE_ON_MEMORY �̏ꍇ�A�}�l�[�W���Ɠ����q�[�v�̈�Ƀt�H���g�f�[�^��ǂݍ���
 */
//==============================================================================================
GF_FONTDATA_MAN* FontDataMan_Create( u32 arcID, u32 datID, FONTDATA_LOADTYPE loadType, BOOL fixedFontFlag, u32 heapID )
{
	GF_FONTDATA_MAN* wk = sys_AllocMemory( heapID, sizeof(GF_FONTDATA_MAN) );
	if( wk )
	{
		load_font_header( wk, arcID, datID, fixedFontFlag, heapID );
		setup_font_datas( wk, loadType, heapID );
	}
	return wk;
}
//==============================================================================================
/**
 * �t�H���g�f�[�^�}�l�[�W���폜
 *
 * @param   wk		�t�H���g�f�[�^�}�l�[�W���̃|�C���^
 *
 */
//==============================================================================================
void FontDataMan_Delete( GF_FONTDATA_MAN* wk )
{
	cleanup_font_datas( wk );
	unload_font_header( wk );
	sys_FreeMemoryEz( wk );
}
//==============================================================================================
/**
 * �t�H���g�r�b�g�f�[�^�̓ǂݍ��݃^�C�v��ύX����
 *
 * @param   wk			�t�H���g�f�[�^�}�l�[�W���|�C���^
 * @param   loadType	�ύX��̓ǂݍ��݃^�C�v
 *
 */
//==============================================================================================
void FontDataMan_ChangeLoadType( GF_FONTDATA_MAN* wk, FONTDATA_LOADTYPE loadType, u32 heapID )
{
	if( wk->loadType != loadType )
	{
		cleanup_font_datas( wk );
		setup_font_datas( wk, loadType, heapID );
	}
}




//------------------------------------------------------------------
/**
 * ���^�C�v�ŋ��L����w�b�_�f�[�^��ǂݍ��݁E�\�z
 *
 * @param   wk				���[�N�|�C���^
 * @param   arcID			�t�H���g�t�@�C���̃A�[�J�C�uID
 * @param   datID			�t�H���g�t�@�C���̃f�[�^ID
 * @param   fixedFontFlag	�Œ�t�H���g�t���O
 * @param   heapID			�q�[�vID
 *
 */
//------------------------------------------------------------------
static void load_font_header( GF_FONTDATA_MAN* wk, u32 arcID, u32 datID, BOOL fixedFontFlag, u32 heapID )
{
	wk->fileHandle = ArchiveDataHandleOpen( arcID, heapID );
	if( wk->fileHandle )
	{
		ArchiveDataLoadOfsByHandle( wk->fileHandle, datID, 0, sizeof(FONTDATA_HEADER), &(wk->fontHeader) );

		wk->fixedFontFlag = fixedFontFlag;
		if( fixedFontFlag )
		{
			wk->widthTbl = NULL;
			wk->WidthGetFunc = GetWidthFixedFont;
		}
		else
		{
			GF_ASSERT(wk->fontHeader.widthTblOffs);

			wk->widthTbl = sys_AllocMemory( heapID, wk->fontHeader.letterMax );
			wk->WidthGetFunc = GetWidthProportionalFont;

			ArchiveDataLoadOfsByHandle( wk->fileHandle, datID, wk->fontHeader.widthTblOffs,
						wk->fontHeader.letterMax, (void*)(wk->widthTbl) );
		}


		{
			static const u8 charShapeTbl[2][2] = {
				{  LETTERSIZE_1x1, LETTERSIZE_1x2 },
				{  LETTERSIZE_2x1, LETTERSIZE_2x2 },
			};

			GF_ASSERT( wk->fontHeader.letterCharX <= 2 && wk->fontHeader.letterCharY <= 2 );

			wk->charShape = charShapeTbl[ wk->fontHeader.letterCharX-1 ][ wk->fontHeader.letterCharY-1 ];
			wk->letterCharSize = SRC_CHAR_SIZE * wk->fontHeader.letterCharX * wk->fontHeader.letterCharY;
		}

		wk->fileDatID = datID;
	}
}
//------------------------------------------------------------------
/**
 * �\�z�����w�b�_�f�[�^�̉��
 *
 * @param   wk		���[�N�|�C���^
 *
 */
//------------------------------------------------------------------
static void unload_font_header( GF_FONTDATA_MAN* wk )
{
	if( wk->widthTbl )
	{
		sys_FreeMemoryEz( wk->widthTbl );
	}
	if( wk->fileHandle )
	{
		ArchiveDataHandleClose( wk->fileHandle );
	}
}



//------------------------------------------------------------------
/**
 * �Ǘ�����t�H���g�f�[�^�̓ǂݍ��ݏ���
 *
 * @param   wk				�}�l�[�W�����[�N�|�C���^
 * @param   loadType		�ǂݍ��݃^�C�v
 * @param   heapID			�풓�^�C�v�̏ꍇ�A�t�H���g�r�b�g�f�[�^�m�ۗp�q�[�v�̎w��B
 *							�t�@�C�����[�h�^�C�v�̏ꍇ�A�g�p���Ȃ�
 *
 */
//------------------------------------------------------------------
static void setup_font_datas( GF_FONTDATA_MAN* wk, FONTDATA_LOADTYPE loadType, u32 heapID )
{
	static void (* const setup_func[])( GF_FONTDATA_MAN*, u32 ) = {
		setup_type_on_memory,
		setup_type_read_file,
	};

	wk->loadType = loadType;

	setup_func[loadType]( wk, heapID );
}
//------------------------------------------------------------------
/**
 * �Ǘ�����t�H���g�f�[�^�̓ǂݍ��ݏ����i�r�b�g�f�[�^�풓�^�C�v�j
 *
 * @param   wk				�}�l�[�W�����[�N�|�C���^
 * @param   heapID			�r�b�g�f�[�^�̈�m�ۗp�̃q�[�vID
 */
//------------------------------------------------------------------
static void setup_type_on_memory( GF_FONTDATA_MAN* wk, u32 heapID )
{
//	void* fontData = ArcUtil_Load( arcID, datID, FALSE, heapID, ALLOC_TOP );
	u32  bit_data_size = wk->letterCharSize * wk->fontHeader.letterMax;

	wk->fontBitData = sys_AllocMemory( heapID, bit_data_size );
	wk->GetBitmapFunc = GetBitmapOnMemory;

	ArchiveDataLoadOfsByHandle( wk->fileHandle, wk->fileDatID, wk->fontHeader.bitDataOffs,
						bit_data_size, wk->fontBitData );
}
//------------------------------------------------------------------
/**
 * �Ǘ�����t�H���g�f�[�^�̓ǂݍ��ݏ����i�r�b�g�f�[�^�����ǂݏo���^�C�v�j
 *
 * @param   wk				�}�l�[�W�����[�N�|�C���^
 * @param   heapID			�g�p���Ȃ�
 */
//------------------------------------------------------------------
static void setup_type_read_file( GF_FONTDATA_MAN* wk, u32 heapID )
{
	wk->GetBitmapFunc = GetBitmapFileRead;
}

//------------------------------------------------------------------
/**
 * �ǂݍ��񂾃t�H���g�f�[�^�̔j��
 *
 * @param   wk		�t�H���g�f�[�^�}�l�[�W���|�C���^
 *
 */
//------------------------------------------------------------------
static void cleanup_font_datas( GF_FONTDATA_MAN* wk )
{
	static void (* const cleanup_func[])( GF_FONTDATA_MAN* ) = {
		cleanup_type_on_memory,
		cleanup_type_read_file,
	};

	cleanup_func[ wk->loadType ]( wk );
}
//------------------------------------------------------------------
/**
 * �ǂݍ��񂾃t�H���g�f�[�^�̔j���i�r�b�g�f�[�^�풓�^�C�v�j
 *
 * @param   wk		�t�H���g�f�[�^�}�l�[�W���|�C���^
 *
 */
//------------------------------------------------------------------
static void cleanup_type_on_memory( GF_FONTDATA_MAN* wk )
{
	sys_FreeMemoryEz( wk->fontBitData );
	wk->fontBitData = NULL;
}
//------------------------------------------------------------------
/**
 * �ǂݍ��񂾃t�H���g�f�[�^�̔j���i�r�b�g�f�[�^�����ǂݍ��݃^�C�v�j
 *
 * @param   wk		�t�H���g�f�[�^�}�l�[�W���|�C���^
 *
 */
//------------------------------------------------------------------
static void cleanup_type_read_file( GF_FONTDATA_MAN* wk )
{
	
}



//==============================================================================================
//==============================================================================================


//==============================================================================================
/*
 *	�����r�b�g�}�b�v�f�[�^�擾
 *
 * @param	wk			�t�H���g�f�[�^�}�l�[�W��
 * @param	fcode		�����R�[�h
 * @param	dst			�擾���ʃ��[�N
 *
 */
//==============================================================================================
void FontDataMan_GetBitmap( const GF_FONTDATA_MAN* wk, STRCODE fcode, MSG_FONT_DATA* dst )
{
	if( fcode <= wk->fontHeader.letterMax )
	{
		fcode--;
		wk->GetBitmapFunc( wk, fcode, dst );
	}
	else
	{
		dst->size_x = 0;
		dst->size_y = 0;
	}
}

//------------------------------------------------------------------
/**
 * �����r�b�g�}�b�v�f�[�^�擾�����i�r�b�g�f�[�^�풓�^�C�v�j
 *
 * @param   wk			���[�N�|�C���^
 * @param   fcode		�����R�[�h
 * @param   dst			�r�b�g�f�[�^�ǂݍ��ݐ�o�b�t�@
 *
 */
//------------------------------------------------------------------
static void GetBitmapOnMemory( const GF_FONTDATA_MAN* wk, STRCODE fcode, MSG_FONT_DATA* dst )
{
	u32	fdata_adrs;

	fdata_adrs = (u32)(&wk->fontBitData[fcode * wk->letterCharSize]);

	switch( wk->charShape ){
	case LETTERSIZE_1x1:
		FntDataSet8x8_2bit(fdata_adrs + 0x10* 0,((u32)dst->data)+0x20*0);
		break;
	case LETTERSIZE_1x2:
		FntDataSet8x8_2bit(fdata_adrs + 0x10* 0,((u32)dst->data)+0x20*0);
		FntDataSet8x8_2bit(fdata_adrs + 0x10* 1,((u32)dst->data)+0x20*2);
		break;
	case LETTERSIZE_2x1:
		FntDataSet8x8_2bit(fdata_adrs + 0x10* 0,((u32)dst->data)+0x20*0);
		FntDataSet8x8_2bit(fdata_adrs + 0x10* 1,((u32)dst->data)+0x20*1);
		break;
	case LETTERSIZE_2x2:
		FntDataSet8x8_2bit(fdata_adrs + 0x10* 0,((u32)dst->data)+0x20*0);
		FntDataSet8x8_2bit(fdata_adrs + 0x10* 1,((u32)dst->data)+0x20*1);
		FntDataSet8x8_2bit(fdata_adrs + 0x10* 2,((u32)dst->data)+0x20*2);
		FntDataSet8x8_2bit(fdata_adrs + 0x10* 3,((u32)dst->data)+0x20*3);
		break;
	}

	dst->size_x = wk->WidthGetFunc( wk, fcode );
	dst->size_y = wk->fontHeader.maxHeight;
}
//------------------------------------------------------------------
/**
 * �����r�b�g�}�b�v�f�[�^�擾�����i�r�b�g�f�[�^�����ǂݍ��݃^�C�v�j
 *
 * @param   wk			���[�N�|�C���^
 * @param   fcode		�����R�[�h
 * @param   dst			�r�b�g�f�[�^�ǂݍ��ݐ�o�b�t�@
 *
 */
//------------------------------------------------------------------
static void GetBitmapFileRead( const GF_FONTDATA_MAN* wk, STRCODE fcode, MSG_FONT_DATA* dst )
{
	u32	fdata_adrs;

	ArchiveDataLoadOfsByHandle( wk->fileHandle, wk->fileDatID, wk->fontHeader.bitDataOffs+fcode*wk->letterCharSize,
		wk->letterCharSize, (void*)(wk->readBuffer) );

	switch( wk->charShape ){
	case LETTERSIZE_1x1:
		FntDataSet8x8_2bit( (u32)(&(wk->readBuffer[0x10*0])), ((u32)dst->data)+0x20*0 );
		break;
	case LETTERSIZE_1x2:
		FntDataSet8x8_2bit( (u32)(&(wk->readBuffer[0x10*0])), ((u32)dst->data)+0x20*0 );
		FntDataSet8x8_2bit( (u32)(&(wk->readBuffer[0x10*1])), ((u32)dst->data)+0x20*2 );
		break;
	case LETTERSIZE_2x1:
		FntDataSet8x8_2bit( (u32)(&(wk->readBuffer[0x10*0])), ((u32)dst->data)+0x20*0 );
		FntDataSet8x8_2bit( (u32)(&(wk->readBuffer[0x10*1])), ((u32)dst->data)+0x20*1 );
		break;
	case LETTERSIZE_2x2:
		FntDataSet8x8_2bit( (u32)(&(wk->readBuffer[0x10*0])), ((u32)dst->data)+0x20*0 );
		FntDataSet8x8_2bit( (u32)(&(wk->readBuffer[0x10*1])), ((u32)dst->data)+0x20*1 );
		FntDataSet8x8_2bit( (u32)(&(wk->readBuffer[0x10*2])), ((u32)dst->data)+0x20*2 );
		FntDataSet8x8_2bit( (u32)(&(wk->readBuffer[0x10*3])), ((u32)dst->data)+0x20*3 );
		break;
	}


	dst->size_x = wk->WidthGetFunc( wk, fcode );
	dst->size_y = wk->fontHeader.maxHeight;

}

//------------------------------------------------------------------
/**
 * ��������r�b�g�}�b�v���������̒����i�h�b�g�j���v�Z���ĕԂ�
 *
 * @param   wk		�t�H���g�f�[�^�}�l�[�W��
 * @param   str		������
 * @param   margin	���ԁi�h�b�g�j
 *
 * @retval  u32		����
 */
//------------------------------------------------------------------
u32 FontDataMan_GetStrWidth( const GF_FONTDATA_MAN* wk, const STRCODE* str, u32 margin )
{
	u32 len = 0;
	while( *str != EOM_ )
	{
		if (*str == _CTRL_TAG )
		{
			str = STRCODE_SkipTag(str);
			if( *str == EOM_ )
			{
				break;
			}
		}
		len += (wk->WidthGetFunc( wk, (*str)-1 ) + margin);
		str++;
	}
	return len - margin;
}


//------------------------------------------------------------------
/**
 * �P�������擾�֐��i�v���|�[�V���i���j
 *
 * @param   wk		
 * @param   bcode		
 *
 * @retval  u8		
 */
//------------------------------------------------------------------
static u8 GetWidthProportionalFont( const GF_FONTDATA_MAN* wk, u32 bcode )
{
	return wk->widthTbl[ bcode ];
}
//------------------------------------------------------------------
/**
 * �P�������擾�֐��i�����j
 *
 * @param   wk		
 * @param   bcode		
 *
 * @retval  u8		
 */
//------------------------------------------------------------------
static u8 GetWidthFixedFont( const GF_FONTDATA_MAN* wk, u32 bcode )
{
	return wk->fontHeader.maxWidth;
}
