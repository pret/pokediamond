//=============================================================================
/**
 * @file	bmp_list.h	
 * @brief	�r�b�g�}�b�v�a�f��ł̃��X�g�\���V�X�e��
 * @author	GAME FREAK inc.
 * @date	tetsu
 */
//=============================================================================
#ifndef __BMP_LIST_H__
#define __BMP_LIST_H__


#include "bmp_menu_list.h"


#undef GLOBAL
#ifdef __BMP_LIST_H_GLOBAL__
#define GLOBAL /*	*/
#else
#define GLOBAL extern
#endif

#undef GLOBAL_WORK
#ifdef __BMP_LIST_H_GLOBAL__
#define GLOBAL_WORK //
#else
#define GLOBAL_WORK extern
#endif

/********************************************************************/
/*                                                                  */
/*				�g�p��`											*/
/*                                                                  */
/********************************************************************/
#define	BMPLIST_MAX		( 4 )		// �o�^�ő吔�i�K���j


typedef struct _BMPLIST_WORK	BMPLIST_WORK;


///���X�g�w�b�_�\����
typedef struct {
	const BMPLIST_DATA*	list;//�\�������f�[�^�|�C���^
	void	(*call_back)(BMPLIST_WORK * wk,u32 param,u8 mode);	//�J�[�\���ړ����Ƃ̃R�[���o�b�N�֐�
	void	(*icon)(BMPLIST_WORK * wk,u32 param,u8 y);	//���\�����Ƃ̃R�[���o�b�N�֐�

	GF_BGL_BMPWIN * win;

	u16		count;		//���X�g���ڐ�
	u16		line;		//�\���ő區�ڐ�
	u8		rabel_x;	//���x���\���w���W
	u8		data_x;		//���ڕ\���w���W
	u8		cursor_x;	//�J�[�\���\���w���W
	u8		line_y:4;	//�\���x���W
	u8		f_col:4;	//�\�������F
	u8		b_col:4;	//�\���w�i�F
	u8		s_col:4;	//�\�������e�F
	u16		msg_spc:3;	//�����Ԋu�w
	u16		line_spc:4;	//�����Ԋu�x
	u16		page_skip:2;//�y�[�W�X�L�b�v�^�C�v
	u16		font:6;		//�����w��(�{���� u8 �����ǁA����Ȃɍ��Ȃ��Ǝv���̂�)
	u16		c_disp_f:1;	//�a�f�J�[�\��(allow)�\���t���O(0:ON,1:OFF)

	void * work;
}BMPLIST_HEADER;






///���X�g�w�b�_��`
#define	BMPLIST_NO_SKIP		(0)
#define	BMPLIST_LRKEY_SKIP	(1)
#define	BMPLIST_LRBTN_SKIP	(2)

///���X�g�A�g���r���[�g�\����
typedef struct {
	u8		pos_x;		//�J�n�w���W�I�t�Z�b�g(�L�����P��)
	u8		pos_y;		//�J�n�x���W�I�t�Z�b�g(�L�����P��)
	u8		siz_x;		//�w�T�C�Y(�L�����P��)
	u8		siz_y;		//�x�T�C�Y(�L�����P��)
	u8		pal;		//�w��p���b�g
}BMPLIST_ATTR;

///���X�g�p�����[�^���Ԃ�l��`
#define	BMPLIST_NULL	(0xffffffff)
#define	BMPLIST_CANCEL	(0xfffffffe)
#define	BMPLIST_RABEL	(0xfffffffd)


// �p�����[�^�擾�E�ύX�h�c
enum {
	BMPLIST_ID_CALLBACK = 0,	///<�J�[�\���ړ����Ƃ̃R�[���o�b�N�֐�
	BMPLIST_ID_ICONFUNC,		///<���\�����Ƃ̃R�[���o�b�N�֐�
	BMPLIST_ID_COUNT,			///<���X�g���ڐ�
	BMPLIST_ID_LINE,			///<�\���ő區�ڐ�
	BMPLIST_ID_INDEX,			///<�g�p�r�b�g�}�b�v�h�m�c�d�w
	BMPLIST_ID_RABEL_X,			///<���x���\���w���W
	BMPLIST_ID_DATA_X,			///<���ڕ\���w���W
	BMPLIST_ID_CURSOR_X,		///<�J�[�\���\���w���W
	BMPLIST_ID_LINE_Y,			///<�\���x���W
	BMPLIST_ID_LINE_YBLK,       ///<�P�s���V�t�g�ʎ擾(�t�H���g�̑傫���{�x�Ԋu)
	BMPLIST_ID_F_COL,			///<�\�������F
	BMPLIST_ID_B_COL,			///<�\���w�i�F
	BMPLIST_ID_S_COL,			///<�\�������e�F
	BMPLIST_ID_MSG_SPC,			///<�����Ԋu�w
	BMPLIST_ID_LINE_SPC,		///<�����Ԋu�x
	BMPLIST_ID_PAGE_SKIP,		///<�y�[�W�X�L�b�v�^�C�v
	BMPLIST_ID_FONT,			///<�����w��
	BMPLIST_ID_C_DISP_F,		///<�a�f�J�[�\��(allow)�\���t���O
	BMPLIST_ID_WIN,				///<�E�B���h�E�f�[�^
	BMPLIST_ID_WORK				///<���[�N
};

// �ړ�����
enum {
	BMPLIST_MOVE_NONE = 0,	// ����Ȃ�
	BMPLIST_MOVE_UP,		// ��ֈړ�
	BMPLIST_MOVE_DOWN,		// ���ֈړ�
	BMPLIST_MOVE_UP_SKIP,	// ��ֈړ��i�X�L�b�v�j
	BMPLIST_MOVE_DOWN_SKIP,	// ���ֈړ��i�X�L�b�v�j
};


/********************************************************************/
/**
 *					�ȈՃ��X�g�֐�
 *
 * @param	bmpdata		���X�g�p�r�b�g�}�b�v�f�[�^�|�C���^
 * @param	bmplist		�\�����X�g�w�b�_�|�C���^
 * @param	mode		�W���E�C���h�E�g�\���X�C�b�`
 *							EASYBMPLIST_NO_FRAME	�g�Ȃ�
 *							EASYBMPLIST_SCRFRAME	�g����A�L�����]���Ȃ�
 *							EASYBMPLIST_ALLFRAME	�g�A�L�����]������
 * @param	cgx			�g�b�f�w�]���I�t�Z�b�g
 * @param	pal			�g�o�`�k�]���I�t�Z�b�g(palanm.h �̒�`�ɏ���)
 *
 * @retval	param		BMPLIST_NULL�łȂ���΁A�I�����ꂽ���ڃp�����[�^
 */
/********************************************************************/
#define	EASYBMPLIST_NO_FRAME	(0)
#define	EASYBMPLIST_SCRFRAME	(1)
#define	EASYBMPLIST_ALLFRAME	(2)



/*u32	BmpListEasy
(const BMPWIN_DAT *bmpdata,const BMPLIST_HEADER *bmplist,u8 mode,u16 cgx,u16 pal);
*/

/********************************************************************/
/**
 *					�ݒ�֐��i�g���j
 *
 * @param	bmplist		�\�����X�g�w�b�_�|�C���^
 * @param	bmplist		�\�����X�g�p���b�g�A�g���r���[�g�|�C���^
 * @param	list_p		���X�g�����ʒu
 * @param	cursor_p	�J�[�\�������ʒu
 *
 * @retval	id			���X�g�h�c(=work_id)
 *						�����C���֐��̈����ƂȂ�̂ŊǗ���Y�ꂸ��
 *
 * call_back �ݒ�Ɋւ��āA���̊֐�����̈����� 
 *   BMPLIST_DATA �\���� param
 * �ƂȂ�
 */
/********************************************************************/
/*
GLOBAL u8		BmpListSetExpand
	(const BMPLIST_HEADER* bmplist,const BMPLIST_ATTR* bmpattr,u16 list_p,u16 cursor_p);
*/










//--------------------------------------------------------------------------------------------
/**
 * �ݒ�֐�
 *
 * @param	bmplist		�\�����X�g�w�b�_�|�C���^
 * @param	list_p		���X�g�����ʒu
 * @param	cursor_p	�J�[�\�������ʒu
 * @param	mode		�������擾���[�h
 *
 * @return	BMP���X�g���[�N
 *
 * @li	BMP���X�g���[�N��sys_AllocMemory�Ŋm��
 */
//--------------------------------------------------------------------------------------------
GLOBAL BMPLIST_WORK * BmpListSet(
						const BMPLIST_HEADER * bmplist, u16 list_p, u16 cursor_p, u8 mode );

//--------------------------------------------------------------------------------------------
/**
 * ���C���֐�
 *
 * @param	lw		BMP���X�g���[�N
 *
 * @retval	"param = �I���p�����[�^"
 * @retval	"BMPLIST_NULL = �I��"
 * @retval	"BMPLIST_CANCEL	= �L�����Z��(�a�{�^��)"
 */
//--------------------------------------------------------------------------------------------
GLOBAL u32 BmpListMain( BMPLIST_WORK * lw );

//--------------------------------------------------------------------------------------------
/**
 * �I���֐�
 *
 * @param	lw			BMP���X�g���[�N
 * @param	list_bak	���X�g�ʒu�o�b�N�A�b�v���[�N�|�C���^
 * @param	cursor_bak	�J�[�\���ʒu�o�b�N�A�b�v���[�N�|�C���^
 *
 * @return	none
 *
 * @li	lw��sys_FreeMemory�ŊJ��
 * @li	�o�b�N�A�b�v���[�N�́ANULL�w��ŕۑ����Ȃ�
 */
//--------------------------------------------------------------------------------------------
GLOBAL void BmpListExit( BMPLIST_WORK * lw, u16 * list_bak, u16 * cursor_bak );

//--------------------------------------------------------------------------------------------
/**
 * ���X�g�ĕ`��
 *
 * @param	lw		BMP���X�g���[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
GLOBAL void BmpListRewrite( BMPLIST_WORK * lw );

//--------------------------------------------------------------------------------------------
/**
 * �����F�ύX�֐�
 *
 * @param	lw			BMP���X�g���[�N
 * @param	f_col		�����F
 * @param	b_col		�w�i�F
 * @param	s_col		�e�F
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
GLOBAL void BmpListColorControl( BMPLIST_WORK * lw, u8 f_col, u8 b_col, u8 s_col );

//--------------------------------------------------------------------------------------------
/**
 * �\���ʒu�ύX�֐�
 *
 * @param	lw			BMP���X�g���[�N
 * @param	x			�\���w���W(�L�����P��)
 * @param	y			�\���x���W(�L�����P��)
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
GLOBAL void BmpListMoveControl( BMPLIST_WORK * lw, u8 x, u8 y );

//--------------------------------------------------------------------------------------------
/**
 * �O���R���g���[���֐�(�`��E�R�[���o�b�N�w��)
 *
 * @param	lw			BMP���X�g���[�N
 * @param	lh			�\�����X�g�w�b�_�|�C���^
 * @param	list_p		���X�g�����ʒu
 * @param	cursor_p	�J�[�\�������ʒu
 * @param	print		�`��t���O
 * @param	direct		�w�����(�L�[��`)
 * @param	list_bak	���X�g�ʒu�o�b�N�A�b�v���[�N�|�C���^
 * @param	cursor_bak	�J�[�\���ʒu�o�b�N�A�b�v���[�N�|�C���^
 *
 * @return	BMPLIST_NULL	
 *
 * ���X�g�֐������삵�Ă��Ȃ��Ƃ��A�O������̎w��ɂ��
 * �J�[�\���ʒu�̕ϓ����`�F�b�N���A�w��o�b�N�A�b�v���[�N�ɕۑ�
 */
//--------------------------------------------------------------------------------------------
GLOBAL u32 BmpListMainOutControlEx(
			BMPLIST_WORK * lw, BMPLIST_HEADER * bmplist,
			u16 list_p, u16 cursor_p, u16 print, u16 direct, u16 * list_bak, u16 * cursor_bak );

//--------------------------------------------------------------------------------------------
/**
 * �O���R���g���[���֐�(�J�[�\���ړ�����)
 *
 * @param	lw			BMP���X�g���[�N
 * @param	bmplist		�\�����X�g�w�b�_�|�C���^
 * @param	list_p		���X�g�����ʒu
 * @param	cursor_p	�J�[�\�������ʒu
 * @param	direct		�w�����(�L�[��`)
 * @param	list_bak	���X�g�ʒu�o�b�N�A�b�v���[�N�|�C���^
 * @param	cursor_bak	�J�[�\���ʒu�o�b�N�A�b�v���[�N�|�C���^
 *
 * @return	BMPLIST_NULL	
 *
 * ���X�g�֐������삵�Ă��Ȃ��Ƃ��A�O������̎w��ɂ��
 * �J�[�\���ʒu�̕ϓ����`�F�b�N���A�w��o�b�N�A�b�v���[�N�ɕۑ�
 */
//--------------------------------------------------------------------------------------------
GLOBAL u32 BmpListMainOutControl(
				BMPLIST_WORK * lw, BMPLIST_HEADER * bmplist,
				u16 list_p, u16 cursor_p, u16 direct, u16 * list_bak, u16 * cursor_bak );

//--------------------------------------------------------------------------------------------
/**
 * BMP_MENULIST_DATA���ēx�ݒ肷��
 *
 * @param	BMP_MENULIST_DATA			BMPMENU���X�g�|�C���^
 * @return	none
 */
//--------------------------------------------------------------------------------------------
GLOBAL void BmpListSetMenuListData(BMPLIST_WORK * lw, BMP_MENULIST_DATA* pList);

//--------------------------------------------------------------------------------------------
/**
 * �����F�ꎞ�ύX
 *
 * @param	lw		BMP���X�g���[�N
 * @param	f_col	�����F
 * @param	b_col	�w�i�F
 * @param	s_col	�e�F
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
GLOBAL void BmpListTmpColorChange( BMPLIST_WORK * lw, u8 f_col, u8 b_col, u8 s_col );

//--------------------------------------------------------------------------------------------
/**
 * BMP���X�g�̑S�̈ʒu���擾
 *
 * @param	lw			BMP���X�g���[�N
 * @param	pos_bak		�S�̃��X�g�ʒu�o�b�N�A�b�v���[�N�|�C���^
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
GLOBAL void BmpListDirectPosGet( BMPLIST_WORK * lw, u16 * pos_bak );

//--------------------------------------------------------------------------------------------
/**
 * BMP���X�g�̃��X�g�ʒu�A�J�[�\���ʒu���擾
 *
 * @param	lw			BMP���X�g���[�N
 * @param	list_bak	���X�g�ʒu�o�b�N�A�b�v���[�N�|�C���^
 * @param	cursor_bak	�J�[�\���ʒu�o�b�N�A�b�v���[�N�|�C���^
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
GLOBAL void BmpListPosGet( BMPLIST_WORK * lw, u16 * list_bak, u16 * cursor_bak );

//--------------------------------------------------------------------------------------------
/**
 * BMP���X�g�̃J�[�\��Y���W���擾
 *
 * @param	lw		BMP���X�g���[�N
 *
 * @return	�J�[�\��Y���W
 */
//--------------------------------------------------------------------------------------------
GLOBAL u16 BmpListCursorYGet( BMPLIST_WORK * lw );

//--------------------------------------------------------------------------------------------
/**
 * BMP���X�g�̃J�[�\���ړ������擾
 *
 * @param	lw		BMP���X�g���[�N
 *
 * @return	�J�[�\���ړ������擾
 */
//--------------------------------------------------------------------------------------------
GLOBAL u8 BmpListMoveSiteGet( BMPLIST_WORK * lw );

//--------------------------------------------------------------------------------------------
/**
 * �w��ʒu�̃p�����[�^�擾
 *
 * @param	lw		BMP���X�g���[�N
 * @param	pos		�ʒu
 *
 * @return	�p�����[�^
 */
//--------------------------------------------------------------------------------------------
GLOBAL u32 BmpListPosParamGet( BMPLIST_WORK * lw, u16 pos );

//--------------------------------------------------------------------------------------------
/**
 * �p�����[�^�擾�֐�
 *
 * @param	lw		BMP���X�g���[�N
 * @param	mode	�p�����[�^�擾�h�c
 *
 * @retval	"0xffffffff = �G���["
 * @retval	"0xffffffff != �p�����[�^"
 */
//--------------------------------------------------------------------------------------------
GLOBAL u32	BmpListParamGet( BMPLIST_WORK * lw, u8 mode );

//--------------------------------------------------------------------------------------------
/**
 * �p�����[�^�ύX�֐�
 *
 * @param	lw		BMP���X�g���[�N
 * @param	mode	�p�����[�^�擾�h�c
 * @param	param	�ύX�l
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
GLOBAL void BmpListParamSet( BMPLIST_WORK * lw, u8 mode, u32 param );



#undef GLOBAL_WORK
#undef GLOBAL

#endif
