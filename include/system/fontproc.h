#ifndef __FONTPROC_H__
#define __FONTPROC_H__

#include "gflib\fontdata_loadtype.h"
#include "gflib\msg_print.h"
#include "gflib\strbuf.h"

//--------------------------------------------------------------
/**
 *		�t�H���g�^�C�v
 */
//--------------------------------------------------------------
typedef enum {
	FONT_SYSTEM = 0,
	FONT_TALK,
	FONT_BUTTON,
	FONT_UNKNOWN,

	FONT_MAX,

	// ------ �ȉ��� make ��ʂ����߂Ɏc�� -----
	// ------ ������S�Ēu�������Ă��炢���� ---

	POKE_8x16 = FONT_SYSTEM,
	POKE_9x12 = FONT_SYSTEM,
	POKE_11x16 = FONT_TALK,
	POKE_SYS = FONT_SYSTEM,
	POKE_SYSTEM = FONT_SYSTEM,
	POKE_FNTEND = FONT_MAX,

}FONT_TYPE;


//--------------------------------------------------------------
/**
 * �퓬�Q�[�WOBJ�p�̃t�H���g��`
 *		font_header_data�̔z��f�[�^�ɂ͕K�v�Ȃ��̂ŕʂɒ�`�B
 *		���l�����͔��Ȃ��悤�ɂ���K�v������
 */
//--------------------------------------------------------------
#define POKE_8x12BATTLE		(POKE_FNTEND)

enum {
	FONT_HEADER_SIZE_X = 0,		// �t�H���gX�T�C�Y�w��
	FONT_HEADER_SIZE_Y,			// �t�H���gY�T�C�Y�w��
	FONT_HEADER_SPACE_X,		// �����ԊuX(�����ݒ�)
	FONT_HEADER_SPACE_Y,		// �����ԊuY(�����ݒ�)
	FONT_HEADER_STYLE,			// �t�H���g�X�^�C��(�����ݒ�)
	FONT_HEADER_F_COLOR,		// �����F�i���o�[
	FONT_HEADER_B_COLOR,		// �w�i�F�i���o�[
	FONT_HEADER_S_COLOR			// �e�F�@�i���o�[
};

#define	FONT_CURSOR_SIZE_X		( 0 )
#define	FONT_CURSOR_SIZE_Y		( 1 )


//------------------------------------------------------------------
/**
 * �t�H���g�����V�X�e���������i���C���łP�x�ĂԂ����j
 *
 * @param   none		
 */
//------------------------------------------------------------------
extern void FontProcInit( void );


//------------------------------------------------------------------
/**
 * �t�H���g�f�[�^��RAM��Ƀ��[�h����
 *
 * @param   font		�t�H���g�h�c
 * @param   heapID		���[�h����q�[�v�̂h�c
 *
 */
//------------------------------------------------------------------
extern void FontProc_LoadFont( FONT_TYPE font, u32 heapID );

//------------------------------------------------------------------
/**
 * RAM��Ƀ��[�h����Ă���t�H���g�f�[�^���A�����[�h����
 *
 * @param   font		�t�H���g�^�C�v
 */
//------------------------------------------------------------------
extern void FontProc_UnloadFont( FONT_TYPE font );






//------------------------------------------------------------------
/**
 * �t�H���g�̃r�b�g�f�[�^���������ɏ풓�����A�ǂݍ��ݏ���������������
 *
 * @param   font			�t�H���gID
 * @param   heapID			�r�b�g�f�[�^�풓�p�q�[�vID
 *
 */
//------------------------------------------------------------------
extern void FontProc_LoadBitData( FONT_TYPE font, u32 heapID );

//------------------------------------------------------------------
/**
 * FontProc_LoadBitData �ŏ풓�������r�b�g�f�[�^��j�����A
 * �����t�@�C���ǂݍ��ݕ����ɖ߂�
 *
 * @param   font			�t�H���gID
 *
 */
//------------------------------------------------------------------
extern void FontProc_UnloadBitData( FONT_TYPE font );




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
extern const MSG_FONT_DATA* FontDataGet( FONT_TYPE font, STRCODE code );


//--------------------------------------------------------------------------------------------
/**
 * �t�H���g�w�b�_�f�[�^�擾
 *
 * @param	fnt_index	�t�H���g�C���f�b�N�X
 * @param	param		�擾�p�����[�^
 *
 * @return	�w�肳�ꂽ�p�����[�^
 */
//--------------------------------------------------------------------------------------------
extern u8 FontHeaderGet( u8 fnt_index, u8 param );

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
extern void SystemFontPaletteLoad( u32 type, u32 offs, u32 heap );

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
extern void TalkFontPaletteLoad( u32 type, u32 offs, u32 heap );



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
extern PRINT_RESULT FontDataPrint( FONT_TYPE font, MSG_DATA_HEADER * mdh_p );


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
extern u32 FontProc_GetStrWidth( FONT_TYPE font, const STRCODE* str, u32 margin );
extern u32 FontProc_GetPrintStrWidth( FONT_TYPE font, const STRBUF* str, u32 margin );

//--------------------------------------------------------------------------------------------
/**
 * �J�[�\���T�C�Y�擾
 *
 * @param	fnt_index	�t�H���g�C���f�b�N�X
 * @param	param		�擾�p�����[�^
 *
 * @return	�w�肳�ꂽ�p�����[�^
 */
//--------------------------------------------------------------------------------------------
extern u8 FontCursorSizeGet( u8 fnt_index, u8 param );


#endif
