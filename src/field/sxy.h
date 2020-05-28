//============================================================================================
/**
 * @file	sxy.h
 * @brief	�C�x���g�֘A����
 * @author	Hiroyuki Nakamura
 * @date	2004.11.30
 */
//============================================================================================
#ifndef SXY_H
#define SXY_H
#undef GLOBAL
#ifdef SXY_H_GLOBAL
#define GLOBAL	/*	*/
#else
#define GLOBAL	extern
#endif


//============================================================================================
//	�萔��`
//============================================================================================
#define	EVENT_ID_NONE	( 0xffff )		///<�C�x���g�f�[�^�Ȃ�

// BG�b�������C�x���g�^�C�v
enum {
	BG_TALK_TYPE_NORMAL = 0,	// �m�[�}��
	BG_TALK_TYPE_BOARD,			// �Ŕ�
	BG_TALK_TYPE_HIDE,			// �B���A�C�e��
};


//============================================================================================
//	�v���g�^�C�v�錾
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * ��b�L����OBJ�擾
 *
 * @param	repw	�t�B�[���h�f�[�^
 * @param	obj		�L�����f�[�^�i�[�ꏊ
 *
 * @retval	"TRUE = �L����������"
 * @retval	"FALSE = �L���������Ȃ�"
 */
//--------------------------------------------------------------------------------------------
GLOBAL u8 TalkObjEventCheck( FIELDSYS_WORK * repw, FIELD_OBJ_PTR * obj );

//--------------------------------------------------------------------------------------------
/**
 * BG�b�������C�x���g��ID�擾
 *
 * @param	repw	�t�B�[���h�f�[�^
 * @param	data	BG�b�������f�[�^
 * @param	size	BG�b�������f�[�^��
 *
 * @retval	"EVENT_ID_NONE = �f�[�^�Ȃ�"
 * @retvel	"EVENT_ID_NONE != BG�f�[�^��ID"
 */
//--------------------------------------------------------------------------------------------
GLOBAL u16 TalkBgEventCheck( FIELDSYS_WORK * repw, void * data, int size );

GLOBAL u16 TalkAutoBgBoardEventCheck( FIELDSYS_WORK * repw, void * data, int size );
GLOBAL u8 TalkAutoObjBoardEventCheck( FIELDSYS_WORK * repw, FIELD_OBJ_PTR * obj );


//--------------------------------------------------------------------------------------------
/**
 * POS�C�x���gID�擾
 *
 * @param	repw	�t�B�[���h�f�[�^
 * @param	data	POS�C�x���g�f�[�^
 * @param	size	POS�C�x���g�f�[�^��
 *
 * @retval	"EVENT_ID_NONE = �f�[�^�Ȃ�"
 * @retvel	"EVENT_ID_NONE != POS�C�x���g�f�[�^��ID"
 */
//--------------------------------------------------------------------------------------------
GLOBAL u16 PosEventCheck( FIELDSYS_WORK * repw, void * data, int size );

//--------------------------------------------------------------------------------------------
/**
 * @brief	�ڂ̑O��OBJ���T�[�`
 * @param	repw	�t�B�[���h�f�[�^
 * @param	obj		�L�����f�[�^�i�[�ꏊ
 *
 * ���݂��Ȃ��Ƃ�NULL���Ԃ�
 */
//--------------------------------------------------------------------------------------------
extern void SXY_HeroFrontObjGet( FIELDSYS_WORK * repw, FIELD_OBJ_PTR * obj );

#undef	GLOBAL
#endif	/* SXY_H */
