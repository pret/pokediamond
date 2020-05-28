//=============================================================================================
/**
 * @file	fontproc.c
 * @brief	�t�H���g�f�[�^����
 * @author	tetsu
 * @date	2003.03.25
 *
 *	�e�t�H���g�̉摜�f�[�^��K�v�ɉ����ă��[�h�E�A�����[�h�o����悤�ɏC��
 *	2005.08.24	taya
 *
 *
 *	�t�H���g�^�C�v���Ƃɏ����֐���p�ӂ��邱��܂ł̕��@���~�߁A
 *	�t�H���g�f�[�^���̂ɏ����ɕK�v�ȃp�����[�^���������āA���ʂ̊֐��Q�ő��삷��悤�ɂ����B
 *	2005.09.14	taya
 *
 */
//=============================================================================================
#include "common.h"

#include "gflib\msg_print.h"
#include "gflib\strbuf_family.h"
#include "system\pmfprint.h"
#include "system\fontproc.h"

#include "system\arc_util.h"
#include "system\font_arc.h"
#include "gflib\fontdata_man.h"

//---------------------------------------------------------------------------------------------
/**
 *	�t�H���g�f�[�^���[�h���p�����[�^�iFONT_TYPE�̏��ɕ���ł���j
 */
//---------------------------------------------------------------------------------------------
//
static const struct {
	u16  arcDataIdx;	///< �A�[�J�C�u���̃t�H���g�f�[�^�C���f�b�N�X
	u16  fixedFontFlag;	///< �����t�H���g�t���O
}FontDataTbl[] = {
	{ NARC_font_system_dat,  FALSE,  },
	{ NARC_font_talk_dat,    FALSE,  },
	{ NARC_font_button_dat,  FALSE,  },
	{ NARC_font_unknown_dat, FALSE,  },
};

//---------------------------------------------------------------------------------------------
/**
 *	�����쐬�����f�[�^�w�b�_�̐ݒ�iFONT_TYPE�̏��ɕ���ł���j
 */
//---------------------------------------------------------------------------------------------
static const MSG_FONT_HEADER font_header_data[] = {
	// ���b�Z�[�W�t�H���g�i�v���|�[�V���i���j
	{
		11, 16,			// �t�H���g�T�C�Y X, Y
		 0,  0, 0,		// ����, �s��, �t�H���g�X�^�C��
 		 1, 15, 2		// �����F�A�w�i�F�A�e�F
	},
	// �V�X�e���t�H���g�i�v���|�[�V���i���j
	{
		11, 16,			// �t�H���g�T�C�Y X, Y
		 0,  0, 0,		// ����, �s��, �t�H���g�X�^�C��
 		 1, 15, 2		// �����F�A�w�i�F�A�e�F
	},
	// �{�^���t�H���g�i�v���|�[�V���i���j
	{
		11, 16,			// �t�H���g�T�C�Y X, Y
		 0,  0, 0,		// ����, �s��, �t�H���g�X�^�C��
 		 1, 15, 2		// �����F�A�w�i�F�A�e�F
	},
	// �A���m�[���t�H���g�i�v���|�[�V���i���j
	{
		11, 16,			// �t�H���g�T�C�Y X, Y
		 0,  0, 0,		// ����, �s��, �t�H���g�X�^�C��
 		 1, 15, 2		// �����F�A�w�i�F�A�e�F
	},
	{	0,0,0,0,0,0,0,0},
};


//---------------------------------------------------------------------------------------------
/**
 *	���[�N��`
 */
//---------------------------------------------------------------------------------------------
typedef struct {
	MSG_FONT_DATA     letterBitData;		///< �r�b�g�f�[�^�P�����`�惏�[�N
	void*             fontData[ NELEMS(FontDataTbl) ];
	GF_FONTDATA_MAN*  fontMan[ NELEMS(FontDataTbl) ];

}FONT_PROC_WORK;

static FONT_PROC_WORK  WorkBody = {0};
static FONT_PROC_WORK* WorkPtr = NULL;

//------------------------------------------------------------------
/**
 * �t�H���g�������W���[���̏�����
 */
//------------------------------------------------------------------
void FontProcInit( void )
{
	u32 i;

	WorkPtr = &WorkBody;

	for(i = 0; i < NELEMS(FontDataTbl); i++)
	{
		WorkPtr->fontData[i] = NULL;
		WorkPtr->fontMan[i] = NULL;
	}

	MSG_PrintSysInit(font_header_data);
}

//------------------------------------------------------------------
/**
 * �t�H���g�f�[�^��RAM��Ƀ��[�h����
 *
 * @param   font		�t�H���g�^�C�v
 */
//------------------------------------------------------------------
void FontProc_LoadFont( FONT_TYPE font, u32 heapID )
{
#if 0
	u32 i;
	void *fontData = NULL;

	// ���łɓ����t�H���g�f�[�^�����[�h���Ă���ꍇ�͂�����g��
	for(i = 0; i < NELEMS(FontDataTbl); i++)
	{
		if( i == font ){
			continue;
		}
		if( (FontDataTbl[i].arcDataIdx == FontDataTbl[font].arcDataIdx )
		&&	(WorkPtr->fontData[font] != NULL)
		){
			fontData = WorkPtr->fontData[font];
			break;
		}
	}

	// �܂����[�h����Ă��Ȃ���ΐV�K�Ƀ��[�h
	if( fontData == NULL )
	{
		fontData = ArcUtil_Load( ARC_FONT, FontDataTbl[font].arcDataIdx, FALSE, heapID, ALLOC_TOP );
		if(fontData != NULL)
		{
			WorkPtr->fontData[font] = fontData;
		}
		else
		{
			GF_ASSERT(0 && "�t�H���g�f�[�^�̃��[�h�Ɏ��s\n");
			return;
		}
	}

	WorkPtr->fontMan[font] = FontDataMan_Create( fontData, FontDataTbl[font].fixedFontFlag, heapID );
#else
	WorkPtr->fontMan[font] = FontDataMan_Create( ARC_FONT, FontDataTbl[font].arcDataIdx,
								FONTDATA_LOADTYPE_READ_FILE,
//								FONTDATA_LOADTYPE_ON_MEMORY,
								FontDataTbl[font].fixedFontFlag, heapID );
#endif
}


//------------------------------------------------------------------
/**
 * �t�H���g�̃r�b�g�f�[�^���������ɏ풓�����A�ǂݍ��ݏ���������������
 *
 * @param   font			�t�H���gID
 * @param   heapID			�r�b�g�f�[�^�풓�p�q�[�vID
 *
 */
//------------------------------------------------------------------
void FontProc_LoadBitData( FONT_TYPE font, u32 heapID )
{
	GF_ASSERT( font < FONT_MAX );
	GF_ASSERT( WorkPtr->fontMan[font] );

	FontDataMan_ChangeLoadType( WorkPtr->fontMan[font], FONTDATA_LOADTYPE_ON_MEMORY, heapID );
}

//------------------------------------------------------------------
/**
 * FontProc_LoadBitData �ŏ풓�������r�b�g�f�[�^��j�����A
 * �����t�@�C���ǂݍ��ݕ����ɖ߂�
 *
 * @param   font			�t�H���gID
 *
 */
//------------------------------------------------------------------
void FontProc_UnloadBitData( FONT_TYPE font )
{
	GF_ASSERT( font < FONT_MAX );
	GF_ASSERT( WorkPtr->fontMan[font] );

	FontDataMan_ChangeLoadType( WorkPtr->fontMan[font], FONTDATA_LOADTYPE_READ_FILE, 0 );
}



//------------------------------------------------------------------
/**
 * RAM��Ƀ��[�h����Ă���t�H���gBMP���A�����[�h����
 *
 * @param   font		�t�H���g�^�C�v
 */
//------------------------------------------------------------------
void FontProc_UnloadFont( FONT_TYPE font )
{
	GF_ASSERT( font < FONT_MAX );

	if( WorkPtr->fontData[font] != NULL )
	{
		int i;

		// �����t�H���g�f�[�^���Q�Ƃ��Ă���}�l�[�W���������
		// ����̊Ǘ��������ɔC���āA�����Ƀf�[�^�̉���͂��Ȃ�
		for(i = 0; i < NELEMS(FontDataTbl); i++)
		{
			if( i == font ){ continue; }
			if(	(FontDataTbl[i].arcDataIdx == FontDataTbl[font].arcDataIdx )
			&&	(WorkPtr->fontMan[i] != NULL)
			){
				WorkPtr->fontData[i] = WorkPtr->fontData[font];
				break;
			}
		}
		if( i == NELEMS(FontDataTbl) )
		{
			sys_FreeMemoryEz( WorkPtr->fontData[font] );
			WorkPtr->fontData[font] = NULL;
		}
	}

	if( WorkPtr->fontMan[font] != NULL )
	{
		FontDataMan_Delete( WorkPtr->fontMan[font] );
		WorkPtr->fontMan[font] = NULL;
	}
}
//------------------------------------------------------------------
/**
 * �t�H���gBMP�f�[�^�P�����������[�N�ɓǂݍ��݁A���̃A�h���X��n��
 *
 * @param   font		�t�H���g�^�C�v
 * @param   code		�����R�[�h
 *
 * @retval  const MSG_FONT_DATA*		�ǂݍ��ݐ�A�h���X
 */
//------------------------------------------------------------------
const MSG_FONT_DATA* FontDataGet( FONT_TYPE font, STRCODE code )
{
	FontDataMan_GetBitmap( WorkPtr->fontMan[font], code, &WorkPtr->letterBitData );
	return &(WorkPtr->letterBitData);
}
//------------------------------------------------------------------
/**
 * �t�H���g�f�[�^���E�B���h�E�L�������[�N�̈�ɕ`��
 *
 * @param   font		�t�H���g�^�C�v
 * @param   ini			BGL�V�X�e�����[�N
 * @param   mdh		
 *
 */
//------------------------------------------------------------------
PRINT_RESULT FontDataPrint( FONT_TYPE font, MSG_DATA_HEADER * mdh_p )
{
	MSG_PRINT_USER * mpu_p;

	mpu_p = (MSG_PRINT_USER *)&(mdh_p->userwork[0]);
	if(!mpu_p->modechg_f)
	{
		mpu_p->fmode = font;
		mpu_p->modechg_f = 1;
	}
	return PokeFontPrint( mdh_p );
}

//------------------------------------------------------------------
/**
 * ��������r�b�g�}�b�v���������̉����擾
 *
 * @param   font		�t�H���g�^�C�v
 * @param   str			������
 * @param   margin		���ԁi�h�b�g�j
 *
 * @retval  u32			�����i�h�b�g�j
 */
//------------------------------------------------------------------
u32 FontProc_GetStrWidth( FONT_TYPE font, const STRCODE* str, u32 margin )
{
	GF_ASSERT(WorkPtr->fontMan[font] != NULL);
	return FontDataMan_GetStrWidth( WorkPtr->fontMan[font], str, margin );
}

//------------------------------------------------------------------
/**
 * ��������r�b�g�}�b�v���������̉����擾(STRBUF�Łj
 *
 * @param   font		�t�H���g�^�C�v
 * @param   str			������
 * @param   margin		���ԁi�h�b�g�j
 *
 * @retval  u32			�����i�h�b�g�j
 */
//------------------------------------------------------------------
u32 FontProc_GetPrintStrWidth( FONT_TYPE font, const STRBUF* str, u32 margin )
{
	GF_ASSERT(WorkPtr->fontMan[font] != NULL);
	return FontDataMan_GetStrWidth( WorkPtr->fontMan[font], STRBUF_GetStringCodePointer(str), margin );
}


//--------------------------------------------------------------------------------------------
/**
 * �t�H���g�f�[�^�擾
 *
 * @param	fnt_index	�t�H���g�C���f�b�N�X
 * @param	param		�擾�p�����[�^
 *
 * @return	�w�肳�ꂽ�p�����[�^
 */
//--------------------------------------------------------------------------------------------
u8 FontHeaderGet( u8 fnt_index, u8 param )
{
	u8	ret = 0;

	switch( param ){
	case FONT_HEADER_SIZE_X:	// �t�H���gX�T�C�Y�w��
		ret = font_header_data[ fnt_index ].size_x;
		break;
	case FONT_HEADER_SIZE_Y:	// �t�H���gY�T�C�Y�w��
		ret = font_header_data[ fnt_index ].size_y;
		break;
	case FONT_HEADER_SPACE_X:	// �����ԊuX(�����ݒ�)
		ret = font_header_data[ fnt_index ].space_x;
		break;
	case FONT_HEADER_SPACE_Y: 	// �����ԊuY(�����ݒ�)
		ret = font_header_data[ fnt_index ].space_y;
		break;
	case FONT_HEADER_STYLE:		// �t�H���g�X�^�C��(�����ݒ�)
		ret = font_header_data[ fnt_index ].style;
		break;
	case FONT_HEADER_F_COLOR:	// �����F�i���o�[
		ret = font_header_data[ fnt_index ].f_col;
		break;
	case FONT_HEADER_B_COLOR:	// �w�i�F�i���o�[
		ret = font_header_data[ fnt_index ].b_col;
		break;
	case FONT_HEADER_S_COLOR:	// �e�F�@�i���o�[
		ret = font_header_data[ fnt_index ].s_col;
		break;
	}

	return	ret;
}


//--------------------------------------------------------------------------------------------
/**
 * �V�X�e���t�H���g�p���b�g�ǂݍ���
 *
 * @param	type	�p���b�g�]����^�C�v
 * @param	offs	�ǂݍ��݃I�t�Z�b�g�i�o�C�g�P�ʁj
 * @param	heap	�q�[�vID
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void SystemFontPaletteLoad( u32 type, u32 offs, u32 heap )
{
	ArcUtil_PalSet( ARC_FONT, NARC_font_system_ncrl, (PALTYPE)type, offs, 0x20, heap );
}

//--------------------------------------------------------------------------------------------
/**
 * ��b�t�H���g�p���b�g�ǂݍ���
 *
 * @param	type	�p���b�g�]����^�C�v
 * @param	offs	�ǂݍ��݃I�t�Z�b�g�i�o�C�g�P�ʁj
 * @param	heap	�q�[�vID
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void TalkFontPaletteLoad( u32 type, u32 offs, u32 heap )
{
	ArcUtil_PalSet( ARC_FONT, NARC_font_talk_ncrl, (PALTYPE)type, offs, 0x20, heap );
}
