#ifndef __NUMBER_STR_H__
#define __NUMBER_STR_H__

//-----------------------------------------------------------
/**
 * ���l�𕶎��񉻂���ۂ̕\���^�C�v
 */
//-----------------------------------------------------------
typedef enum {
	NUMBER_DISPTYPE_LEFT,		///< ���l��
	NUMBER_DISPTYPE_SPACE,		///< �E�l�߁i�ő包�ɑ���Ȃ��ꍇ�̓X�y�[�X�Ŗ��߂�j
	NUMBER_DISPTYPE_ZERO,		///< �E�l�߁i�ő包�ɑ���Ȃ��ꍇ�̓[���Ŗ��߂�j
}NUMBER_DISPTYPE;

//-----------------------------------------------------------
/**
 * ���l�𕶎��񉻂���ۂ̕����R�[�h�^�C�v
 */
//-----------------------------------------------------------
typedef enum {
	NUMBER_CODETYPE_ZENKAKU,	///< �S�p
	NUMBER_CODETYPE_HANKAKU,	///< ���p

	// ����{�I�ɂ̓R�����g���B�R�C�c�����ɉ����ď���������B
	NUMBER_CODETYPE_DEFAULT = NUMBER_CODETYPE_ZENKAKU,
}NUMBER_CODETYPE;

#endif
