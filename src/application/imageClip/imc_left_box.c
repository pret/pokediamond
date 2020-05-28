//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		imc_left_box.c
 *	@brief		���{�b�N�X�V�X�e��
 *	@author		tomoya takahashi
 *	@data		2005.09.23
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]



#include <string.h>
#include "system.h"
#include "assert.h"
#include "calctool.h"
#include "tcb.h"
#include "include/system/lib_pack.h"
#include "include/application/imageClip/imc_drawdata_define.h"
#include "include/system/heapdefine.h"
#include "include/application/imageClip/imc_obj_list_func.h"

#define __IMC_LEFT_BOX_H_GLOBAL
#include "include/application/imageClip/imc_left_box.h"

//-----------------------------------------------------------------------------
/**
 *					�萔�錾
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	
//	�T���l�C���f�[�^�z�u���W�萔
//	
//=====================================
#define IMC_LBOX_THUMB_SIZE_X	(24)		// �T���l�C���T�C�Y
#define IMC_LBOX_THUMB_SIZE_Y	(32)		// �T���l�C���T�C�Y
#define IMC_LBOX_MAT_SPACE_X	(8)			// �z�u����Ƃ��̃X�y�[�X
#define IMC_LBOX_MAT_SPACE_Y	(8)			// �z�u����Ƃ��̃X�y�[�X

#define IMC_LBOX_MAT_LINE_NUM	(3)			// �P���C���ɉ��T���l�C��������


//-----------------------------------------------------------------------------
/**
*		�p���b�g�ύX�@�����f�[�^
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	
//	�V�[�P���X
//	
//=====================================
enum{
	IMC_LBOX_PLTT_CHG_INIT,		// ������
	IMC_LBOX_PLTT_CHG_OUT_ACCE_S,// �A�N�Z�T���ޏ�J�n
	IMC_LBOX_PLTT_CHG_IN_ACCE_S,	// �A�N�Z�T������J�n
	IMC_LBOX_PLTT_CHG_WAIT,		// �e�A�N�Z�T���t�F�[�h�I���҂�
	IMC_LBOX_PLTT_CHG_END,		// �I��
};

#define IMC_LBOX_PLTT_CHG_MOVE_Y	(132)		// �ړ��l
#define IMC_LBOX_PLTT_CHG_COUNT	(3)			// �ړ���
#define IMC_LBOX_PLTT_CHG_ADD	(IMC_LBOX_PLTT_CHG_MOVE_Y / IMC_LBOX_PLTT_CHG_COUNT)		// �P��̈ړ���
#define IMC_LBOX_PLTT_CHG_OBJ_S_NUM	(2)		// �t�F�[�h�C���I�u�W�F�N�g�̐������������邩
#define IMC_LBOX_PLTT_CHG_OBJ_E_NUM	(1)		// �t�F�[�h�A�E�g�I�u�W�F�N�g�̐������������邩
#define IMC_LBOX_PLTT_BG_SYNC	(5)		// BG�����V���N�œ�������


//-----------------------------------------------------------------------------
/**
 *					�\���̐錾
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	
//	�p���b�g�t�F�[�h�X�̃I�u�W�F�N�g�ړ�
//	�\����
//	
//=====================================
typedef struct {
	IMC_OBJLIST* obj;
	
	int count;
	int add_y;
} IMC_LBOX_PLTT_OBJ_MOVE;

//-------------------------------------
//	
//	�p���b�g�t�F�[�h�^�X�N
//	
//=====================================
typedef struct {
	IMC_LEFT_BOX* lbox;	// ���{�b�N�X

	int out_mode;		// �t�F�[�h�A�E�g���郊�X�gmode
	int out_list;		// �t�F�[�h�A�E�g���郊�X�gno
	int in_mode;		// �t�F�[�h�C�����郊�X�gmode
	int in_list;		// �t�F�[�h�C�����郊�X�gno
	BOOL bg_fade;		// BG�t�F�[�h�I���`�F�b�N
	int count;			// �ėp�J�E���^

	int seq;			// �V�[�P���X	
	int out_count;		// �J�E���^
	int in_count;		// �J�E���^

	IMC_LBOX_PLTT_OBJ_MOVE* move_obj;	// �I�u�W�F�ړ��f�[�^
	// ���e�[�u������out_obj_count + in_obj_count
	int move_obj_num;		// �e�[�u����
} IMC_LBOX_PLTT_TASK;



//-----------------------------------------------------------------------------
/**
 *					�v���g�^�C�v�錾
*/
//-----------------------------------------------------------------------------
static void makeAcceList( IMC_LEFT_BOX* lbox, IMC_LEFT_BOX_INIT* init );
static void drawSetList( IMC_OBJLIST* dummy, int flag );
static void listDataMake( IMC_LEFT_LIST_DATA* list, int dummy_num );
static void listDataDest( IMC_LEFT_LIST_DATA* list );
static IMC_OBJLIST* getCurrentDummy( IMC_LEFT_BOX* lbox );
static IMC_OBJLIST* getDummyTbl( IMC_LEFT_BOX* lbox, int mode, int tbl_no );
static int getListSetDataNum( IMC_LEFT_BOX* lbox, int mode, int tbl_no );
static IMC_OBJLIST* getNoListObjData( IMC_LEFT_BOX* lbox, int mode, int tbl_no, int no );
static void drawFlgCurrentDummy( IMC_LEFT_BOX* lbox, int flag );
static void drawFlgSetCheck( IMC_LEFT_BOX* lbox, IMC_ACCESSORIE_OBJ* acce_obj, int mode, int list_num );
static void getBgSndThumbMat( int no, int* x, int* y );

static void plttChgTaskStart( IMC_LEFT_BOX* lbox, int out_mode, int out_list, int in_mode, int in_list );
static void plttChgTask( TCB_PTR tcb, void* work );
static void startPlttChgObj( IMC_OBJLIST* obj, IMC_LBOX_PLTT_OBJ_MOVE* data, int num );
static IMC_LBOX_PLTT_OBJ_MOVE* getCleanPlttChgObj( IMC_LBOX_PLTT_OBJ_MOVE* data, int num );
static void movePlttChgObj( IMC_LBOX_PLTT_OBJ_MOVE* data, int num );
static void movePlttChgObjCore( IMC_LBOX_PLTT_OBJ_MOVE* data );

static int movePlttChgGetObjAddNum( int obj_num, int div );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	���{�b�N�X�p�̈�쐬
 *
 *	@param	lbox		���{�b�N�X�p�f�[�^
 *	@param	init		���{�b�N�X�������f�[�^
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_LBOX_InitSys( IMC_LEFT_BOX* lbox, IMC_LEFT_BOX_INIT* init )
{
	// �`��f�[�^�ݒ�
	lbox->boxDraw.SWSP_drawSys		= init->SWSP_drawSys;
	lbox->boxDraw.SWSP_charData		= init->SWSP_charData;
	lbox->boxDraw.SWSP_plttData		= init->SWSP_plttData;
	lbox->boxDraw.accePlttOfsTbl	= init->accePlttOfsTbl;
	lbox->boxDraw.BG_Ini			= init->BG_Ini;
	lbox->boxDraw.acce		= init->acce;
	
	// �I�u�W�F�N�g���X�g�e�[�u��
	lbox->boxData.objListTbl = init->objListTbl;
	lbox->boxData.p_item_buff = init->p_item_buff;

	// �w�i�i���o
	IMC_LBOX_BGSet( lbox, 0 );
	
	// �A�N�Z�T�����X�g�쐬
	makeAcceList( lbox, init );

}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	���{�b�N�p�̈�j��
 *
 *	@param	lbox		�j�����鍶�{�b�N�X�f�[�^
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_LBOX_DeleteSys( IMC_LEFT_BOX* lbox )
{
	int i;
	
	IMC_LBOX_DeleteAccessorieAll( lbox );

	for( i=0; i<IMC_LBOX_LIST_NUM; i++ ){
		listDataDest( &lbox->boxData.acce_list[ i ] );
	}
	
	memset( lbox, 0, sizeof( IMC_LEFT_BOX ) );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�A�N�Z�T���[�i���o�[���烊�X�g�i���o�[���擾
 *
 *	@param	mode			���[�h
 *	@param	accessorie_no	�A�N�Z�T���i���o�[
 *
 *	@return	int		�A�N�Z�T���[���X�g�i���o�[
 *
 *
 */
//-----------------------------------------------------------------------------
int IMC_LBOX_GetListNo( int mode, int accessorie_no, IMC_ITEM_BUFF* p_item_buff )
{
	int list_no;
	
	switch(mode){
	case IMC_OBJLIST_ACCE:
		if( accessorie_no <= IMC_LBOX_ACCE_LIST00_END ){
			list_no = 0;
		}else if( accessorie_no <= IMC_LBOX_ACCE_LIST01_END ){
			list_no = 1;
		}else if( accessorie_no <= IMC_LBOX_ACCE_LIST02_END ){
			list_no = 2;
		}else if( accessorie_no <= IMC_LBOX_ACCE_LIST03_END ){
			list_no = 3;
		}else if( accessorie_no <= IMC_LBOX_ACCE_LIST04_END ){
			list_no = 4;
		}else if( accessorie_no <= IMC_LBOX_ACCE_LIST05_END ){
			list_no = 5;
		}else if( accessorie_no <= IMC_LBOX_ACCE_LIST06_END ){
			list_no = 6;
		}else if( accessorie_no <= IMC_LBOX_ACCE_LIST07_END ){
			list_no = 7;
		}else if( accessorie_no <= IMC_LBOX_ACCE_LIST08_END ){
			list_no = 8;
		}else if( accessorie_no <= IMC_LBOX_ACCE_LIST09_END ){
			list_no = 9;
		}else if( accessorie_no <= IMC_LBOX_ACCE_LIST10_END ){
			list_no = 10;
		}else if( accessorie_no <= IMC_LBOX_ACCE_LIST11_END ){
			list_no = 11;
		}else if( accessorie_no <= IMC_LBOX_ACCE_LIST12_END ){
			list_no = 12;
		}else if( accessorie_no <= IMC_LBOX_ACCE_LIST13_END ){
			list_no = 13;
		}
		break;

	case IMC_OBJLIST_BG:
		accessorie_no = IMC_ITEM_BUFF_BgNoTurnGet( p_item_buff, accessorie_no );
		list_no = accessorie_no / IMC_LBOX_BG_ONE_LIST_NUM;
		break;

	case IMC_OBJLIST_SND:
		accessorie_no = IMC_ITEM_BUFF_BgNoTurnGet( p_item_buff, accessorie_no );
		list_no = accessorie_no / IMC_LBOX_SND_ONE_LIST_NUM;
		break;
	}
	
	return list_no;
}


//----------------------------------------------------------------------------
/**
 *
 *	@brief	���[�h�ƃA�N�Z�T���i���o�[����o�^����Ă����ׂ����W���擾
 *
 *	@param	mode			���[�h
 *	@param	accessorie_no	�A�N�Z�T���i���o�[
 *	@param	x				�����W�i�[��
 *	@param	y				�����W�i�[��
 *	@param	size_x			���T�C�Y
 *	@param	size_y			���T�C�Y
 *
 *	@return	none
 *	
 *
 */
//-----------------------------------------------------------------------------
void IMC_LBOX_GetMat( int mode, int accessorie_no, int* x, int* y, int size_x, int size_y, IMC_ITEM_BUFF* p_item_buff )
{
	switch(mode){
	case IMC_OBJLIST_ACCE:
		// �A�N�Z�T���������W�͗���
		*x = IMC_LBOX_AREA_X_MOVEOK;
		*y = IMC_LBOX_AREA_Y_MOVEOK;
		*x += ( gf_mtRand() % (IMC_LBOX_AREA_WIDTH_MOVEOK - size_x) );
		*y += ( gf_mtRand() % (IMC_LBOX_AREA_HEIGHT_MOVEOK - size_y) );
		break;

	case IMC_OBJLIST_BG:
	case IMC_OBJLIST_SND:
		accessorie_no = IMC_ITEM_BUFF_BgNoTurnGet( p_item_buff, accessorie_no );
		getBgSndThumbMat( accessorie_no, x, y );
		break;
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�A�N�Z�T���̐V�K�ǉ�
 *
 *	@param	lbox				���{�b�N�X�p�f�[�^
 *	@param	list_num			�ǉ�����A�N�Z�T�����X�g��
 *	@param	mode				�A�N�Z�T�����[�h
 *	@param	accessorie_no		�ǉ�����A�N�Z�T���i���o�[
 *
 *	@return	none
 *
 * mode
	IMC_OBJLIST_ACCE,		// �A�N�Z�T���ύX���[�h
	IMC_OBJLIST_BG,			// BG�ύX���[�h
	IMC_OBJLIST_SND,		// �T�E���h�ύX���[�h
	IMC_OBJLIST_ACCE_MAX	// ���[�h�ő吔
 *
 */
//-----------------------------------------------------------------------------
void IMC_LBOX_AddAccessorie( IMC_LEFT_BOX* lbox, int mode, int accessorie_no )
{
	IMC_ACCE_ADD acce_add;
	IMC_ACCESSORIE_OBJ* acce_obj;
	IMC_OBJLIST* objList;
	int list_num;
	int char_no, pltt_no;
	int set_x, set_y;
	int size_x, size_y;
	
	// �A�N�Z�T����o�^���A���X�g�ɓo�^
	// �A�N�Z�T���o�^�f�[�^�쐬
	acce_add.objTbl = lbox->boxDraw.acce;
	acce_add.accessorie_no = accessorie_no;
	acce_add.SWSPsys	= lbox->boxDraw.SWSP_drawSys;
	acce_add.m_x	= 0;
	acce_add.m_y	= 0;

	// mode	�ɂ��킹�ēo�^����
	switch( mode ){
	case IMC_OBJLIST_ACCE:
		char_no = IMC_ACCE_CHAR_CONT_ID( accessorie_no );
		pltt_no = IMC_ACCE_PLTT_CONT_ID( accessorie_no );
		acce_add.pltt_offs	= lbox->boxDraw.accePlttOfsTbl[ accessorie_no ];
		break;
	case IMC_OBJLIST_BG:
		char_no = IMC_BG_THUMB_CHAR_CONT_ID( accessorie_no );
		pltt_no = IMC_BG_THUMB_PLTT_CONT_ID( accessorie_no );
		acce_add.pltt_offs = 0;
		break;
	case IMC_OBJLIST_SND:
		char_no = IMC_SND_THUMB_CHAR_CONT_ID( accessorie_no );
		pltt_no = IMC_SND_THUMB_PLTT_CONT_ID( accessorie_no );
		acce_add.pltt_offs = 0;
		break;
	default:
		GF_ASSERT_MSG( 0, "mode���s���Ȓl�ł�" );
		break;
	}
	acce_add.SWSPchar	= lbox->boxDraw.SWSP_charData[ char_no ];
	acce_add.SWSPpltt	= lbox->boxDraw.SWSP_plttData[ pltt_no ];
	GF_ASSERT( acce_add.SWSPchar );
	GF_ASSERT_MSG( acce_add.SWSPpltt, "pltt_no %d", pltt_no );

	// ���X�g�i���o�[�擾
	list_num = IMC_LBOX_GetListNo( mode, accessorie_no, lbox->boxData.p_item_buff );


	// �o�^
	acce_obj = IMC_ACCE_ObjAdd( &acce_add );

	// �I�u�W�F���X�g�̍쐬
	objList = IMC_OBJLIST_MakeObjList( lbox->boxData.objListTbl, acce_obj, mode );
	
	// ���X�g�̌��ɓo�^
	IMC_OBJLIST_Set( objList,
					lbox->boxData.acce_list[ mode ].dummyTbl[ list_num ].prev );

	// ���W��ݒ�
	IMC_OBJLIST_ACCEPOKE_SizeGet( objList, &size_x, &size_y );
	IMC_LBOX_GetMat( mode, accessorie_no, &set_x, &set_y, size_x, size_y, lbox->boxData.p_item_buff );
	IMC_OBJLIST_ACCEPOKE_Mat( objList, set_x, set_y );

	// �\��/��\���ݒ�
	drawFlgSetCheck( lbox, acce_obj, mode, list_num );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�A�N�Z�T���̈ړ��ǉ�
 *
 *	@param	lbox		���{�b�N�X�p�f�[�^
 *	@param	acce_obj	�A�N�Z�T���f�[�^
 *	@param	mode		�A�N�Z�T�����[�h
 *	@param	list_num	�o�^���郊�X�g
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_LBOX_AddAccessorieMove( IMC_LEFT_BOX* lbox, int mode, int list_num, IMC_OBJLIST* acce_obj )
{
	// ���X�g�̐擪�ɓo�^
	IMC_OBJLIST_Set(acce_obj, lbox->boxData.acce_list[ mode ].dummyTbl + list_num);


	// �\��/��\���ݒ�
	drawFlgSetCheck( lbox, acce_obj->obj_data, mode, list_num );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�A�N�Z�T���I�u�W�F�j��
 *
 *	@param	acce_obj	�j������A�N�Z�T��
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_LBOX_DeleteAccessorie( IMC_OBJLIST* acce_obj )
{
	// ���X�g����j��
	IMC_OBJLIST_Delete( acce_obj );
	
	// �A�N�Z�T���j��
	IMC_ACCE_ObjDelete( (IMC_ACCESSORIE_OBJ*)acce_obj->obj_data );

	// ���X�g��j��
	IMC_OBJLIST_DeleteObjList( acce_obj );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�ړ������邽�߂̃��X�g����̍폜
 *
 *	@param	acce_obj	�ړ������邽�߂Ƀ��X�g����폜����A�N�Z�T���f�[�^
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_LBOX_DeleteAccessorieMove( IMC_OBJLIST* acce_obj )
{
	// ���X�g����j��
	IMC_OBJLIST_Delete( acce_obj );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�o�^����Ă���A�N�Z�T���S�Ă��͂�
 *
 *	@param	lbox	���{�b�N�X
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_LBOX_DeleteAccessorieAll( IMC_LEFT_BOX* lbox )
{
	int i, j;
	
	// ���X�g�j��
	for( i=0; i<IMC_OBJLIST_ACCE_MAX; i++ ){
		for( j=0; j<lbox->boxData.acce_list[ i ].dummyNum; j++ ){
	
			IMC_OBJLIST_DeleteAll( lbox->boxData.acce_list[ i ].dummyTbl + j );
		}
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	���{�b�N�X�A�N�Z�T���̕\���D�揇��ݒ�
 *
 *	@param	lbox	���u���b�N
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_LBOX_SetAccessoriePriority( IMC_LEFT_BOX* lbox )
{
	IMC_OBJLIST* work;
	IMC_OBJLIST* dummyTbl;
	BOOL	ret;
	
	int	priority = IMC_LBOX_ACCE_PRIORITY_START;

	dummyTbl = getCurrentDummy( lbox );
	
	work = dummyTbl->next;
	while( work != dummyTbl ){

		if( (work->flag == IMC_OBJLIST_ACCE) ||
			(work->flag == IMC_OBJLIST_BG) ||
			(work->flag == IMC_OBJLIST_SND)){

			IMC_ACCE_ObjDrawPrioritySet( work->obj_data, priority );	
		}

		priority --;
		
		work = work->next;
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�J�����g�A�N�Z�T�����X�g��ύX
 *
 *	@param	lbox			���{�b�N�X�f�[�^
 *	@param	mode			�A�N�Z�T�����[�h
 *	@param	list_num		�ݒ肷��J�����g�A�N�Z�T�����X�g
 *
 *	@retval	TRUE			����
 *	@retval	FALSE			���s
 *
 * mode
	IMC_OBJLIST_ACCE,		// �A�N�Z�T���ύX���[�h
	IMC_OBJLIST_BG,		// BG�ύX���[�h
	IMC_OBJLIST_SND,		// �T�E���h�ύX���[�h
	IMC_OBJLIST_ACCE_MAX		// ���[�h�ő吔
 *
 */
//-----------------------------------------------------------------------------
BOOL IMC_LBOX_ChangeCurrentAccessorie( IMC_LEFT_BOX* lbox, int mode, int list_num )
{
	// �ʏ��Ԃ̎��ɂ����ύX����
	if( lbox->boxData.state == IMC_LBOX_STATE_NORM ){
		
		// �p���b�g�ύX�^�X�N�X�^�[�g
		plttChgTaskStart( lbox,
				lbox->boxData.mode, 
				lbox->boxData.acce_list[ lbox->boxData.mode ].dummyCurrent,
				mode,
				list_num );

			
		// �V�������[�h�ƃJ�����g���X�g�ԍ���ݒ�
		lbox->boxData.mode		= mode;
		lbox->boxData.acce_list[ mode ].dummyCurrent = list_num;

		// �D�揇�ʂ̐ݒ�
		IMC_LBOX_SetAccessoriePriority( lbox );

		return TRUE;
	}

	return FALSE;
}

//----------------------------------------------------------------------------
/**
 * �������ŃG�t�F�N�g���s���܂��B
 *
 *	@brief	�J�����g�A�N�Z�T�����X�g�̑����Z
 *
 *	@param	lbox			���{�b�N�X�f�[�^
 *	@param	mode			�A�N�Z�T�����[�h
 *	@param	add_mode		�������[�h
 *
 *	@retval	TRUE			����
 *	@retval	FALSE			���s
 *
 * mode
	IMC_OBJLIST_ACCE,		// �A�N�Z�T���^�C�v
	IMC_OBJLIST_BG,			// BG�T���l�C���^�C�v
	IMC_OBJLIST_SND,		// �T�E���h�T���l�C���^�C�v
	IMC_LBOX_FADELIST_MODE	// �t�F�[�h���p���X�g	list_num�͂O�Œ�
 */
//-----------------------------------------------------------------------------
BOOL IMC_LBOX_AddCurrentAccessorie( IMC_LEFT_BOX* lbox, int mode, int add_mode )
{
	IMC_OBJLIST* dummy;
	int currentno;
	int work;
	int i;
	int check_list;
	BOOL ret;
	
	// ���݂̃J�����g�i���o�[
	currentno = IMC_LBOX_GetCurrentNo( lbox, mode );

	// ���X�g���܂킵�āA�ǂ����A�A�N�Z�T���������Ă���e�[�u����T���@���Ɠ������̂ɂȂ����牽�����Ȃ�
	for( i=1; i<lbox->boxData.acce_list[mode].dummyNum; i++ ){

		if( add_mode == IMC_LBOX_ADD_ONE ){
			check_list = (i + currentno) % lbox->boxData.acce_list[mode].dummyNum;
		}else{
			check_list = currentno - i;
			if( check_list < 0 ){
				check_list += lbox->boxData.acce_list[mode].dummyNum;
			}
		}
		
		// �A�N�Z�T����1�ł������Ă���p���b�g��I��
		dummy = getDummyTbl( lbox, mode, check_list );
		if( dummy->next != dummy ){

			// ���X�g�ݒ肵�Ĕ�����
			ret = IMC_LBOX_ChangeCurrentAccessorie( lbox, mode, check_list );
			return ret; 
		}
	}
	return FALSE;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�J�����g�A�N�Z�T�����X�g��ݒ�
 *
 *	@param	lbox			���{�b�N�X�f�[�^
 *	@param	mode			�A�N�Z�T�����[�h
 *	@param	list_num		�ݒ肷��J�����g�A�N�Z�T�����X�g
 *
 *	@return	none
 *
 * mode
	IMC_OBJLIST_ACCE,		// �A�N�Z�T���^�C�v
	IMC_OBJLIST_BG,			// BG�T���l�C���^�C�v
	IMC_OBJLIST_SND,		// �T�E���h�T���l�C���^�C�v
	IMC_OBJLIST_ACCE_MAX	// ���[�h�ő吔
 *
 */
//-----------------------------------------------------------------------------
void IMC_LBOX_SetCurrentAccessorie( IMC_LEFT_BOX* lbox, int mode, int list_num )
{
	// �J�����g�_�~�[���X�g��\���ݒ�
	drawFlgCurrentDummy( lbox, FALSE );
	
	// �V�������[�h�ƃJ�����g���X�g�ԍ���ݒ�
	lbox->boxData.mode		= mode;
	lbox->boxData.acce_list[ mode ].dummyCurrent = list_num;

	// �J�����g�_�~�[���X�g�\���ݒ�
	drawFlgCurrentDummy( lbox, TRUE );
	
	IMC_LBOX_SetAccessoriePriority( lbox );
}


//----------------------------------------------------------------------------
/**
 *
 *	@brief	�^�b�`�p�l�������{�b�N�X�ɓ������Ă邩�`�F�b�N
 *
 *	@param	lbox		���{�b�N�X�f�[�^
 *
 *	@retval	TRUE		�q�b�g
 *	@retval	FALSE		��q�b�g
 *
 *
 */
//-----------------------------------------------------------------------------
BOOL IMC_LBOX_TPHit( IMC_LEFT_BOX* lbox )
{
	// �����蔻���`�f�[�^
	TP_HIT_TBL	tp_hit;
	
	// �����蔻��p�f�[�^�쐬
	tp_hit.rect.top		= IMC_LBOX_AREA_Y_MOVEOK;
	tp_hit.rect.bottom	= IMC_LBOX_AREA_Y_MOVEOK + IMC_LBOX_AREA_HEIGHT_MOVEOK;
	tp_hit.rect.left	= IMC_LBOX_AREA_X_MOVEOK;
	tp_hit.rect.right	= IMC_LBOX_AREA_X_MOVEOK + IMC_LBOX_AREA_WIDTH_MOVEOK;
	return GF_TP_SingleHitCont( &tp_hit );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�w����W�����{�b�N�X�ɓ������Ă邩�`�F�b�N
 *
 *	@param	lbox		���{�b�N�X�f�[�^
 *	@param	x			���肘���W
 *	@param	y			���肙���W
 *
 *	@retval	TRUE		�q�b�g
 *	@retval	FALSE		��q�b�g
 *
 *
 */
//-----------------------------------------------------------------------------
BOOL IMC_LBOX_TPHitSelf( IMC_LEFT_BOX* lbox, int x, int y )
{
	// �����蔻���`�f�[�^
	TP_HIT_TBL	tp_hit;
	
	// �����蔻��p�f�[�^�쐬
	tp_hit.rect.top		= IMC_LBOX_AREA_Y_MOVEOK;
	tp_hit.rect.bottom	= IMC_LBOX_AREA_Y_MOVEOK + IMC_LBOX_AREA_HEIGHT_MOVEOK;
	tp_hit.rect.left	= IMC_LBOX_AREA_X_MOVEOK;
	tp_hit.rect.right	= IMC_LBOX_AREA_X_MOVEOK + IMC_LBOX_AREA_WIDTH_MOVEOK;
	return GF_TP_SingleHitSelf( &tp_hit, x, y );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�A�N�Z�T�����Ƃ̓����蔻����s��
 *
 *	@param	lbox	���{�b�N�X
 *
 *	@return	none
 *
 *	�J�����g�A�N�Z�T�����X�g���`�F�b�N���܂��B
 *
 */
//-----------------------------------------------------------------------------
IMC_OBJLIST* IMC_LBOX_TPHitAccessorie( IMC_LEFT_BOX* lbox )
{
	IMC_OBJLIST* work;
	IMC_OBJLIST* dummyTbl;
	BOOL	ret;
	
	// ���̃J�����g�_�~�[�e�[�u���擾
	dummyTbl = getCurrentDummy( lbox );
	
	work = dummyTbl->next;
	while( work != dummyTbl ){

		ret = FALSE;

		if( (work->flag == IMC_OBJLIST_ACCE) ||
			(work->flag == IMC_OBJLIST_BG) ||
			(work->flag == IMC_OBJLIST_SND)){
			
			ret = IMC_ACCE_ObjTpHit( work->obj_data );
		}

		if(ret == TRUE){

			return work;
		}
		
		work = work->next;
	}

	return NULL;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�A�N�Z�T�����Ƃ̓����蔻����ׂ����s��
 *
 *	@param	lbox	���{�b�N�X
 *	@param	offset_x	�I�t�Z�b�g�����W
 *	@param	offset_y	�I�t�Z�b�g�����W
 *	@param	SWSP_UPchar	�L�����N�^���\�[�X�e�[�u��
 *
 *	@return	none
 *
 *	�J�����g�A�N�Z�T�����X�g���`�F�b�N���܂��B
 *
 */
//-----------------------------------------------------------------------------
IMC_OBJLIST* IMC_LBOX_TPHitAccessorieEx( IMC_LEFT_BOX* lbox, int* offset_x, int* offset_y, NNSG2dCharacterData** SWSP_UPchar )
{
	IMC_OBJLIST* work;
	IMC_OBJLIST* dummyTbl;
	BOOL	ret;
	
	// ���̃J�����g�_�~�[�e�[�u���擾
	dummyTbl = getCurrentDummy( lbox );

	work = dummyTbl->next;
	while( work != dummyTbl ){

		ret = FALSE;

		ret = IMC_OBJLIST_ACCEPOKE_HitEx( work, offset_x, offset_y, SWSP_UPchar );

		if(ret == TRUE){

			return work;
		}
		
		work = work->next;
	}

	return NULL;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	BG��\��
 *
 *	@param	lbox		���{�b�N�X
 *	@param	bg_num		���{�b�N�XBG�i���o�[
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_LBOX_BGSet( IMC_LEFT_BOX* lbox, int bg_num )
{
	IMC_BG_ADD add;
	
	// �o�^�f�[�^�ݒ�
	add.bg_ini		= lbox->boxDraw.BG_Ini;
	add.arc_file	= ARC_IMAGECLIP_GRA;
	add.char_arc	= IMC_BG_LEFT_CG_ARC_GET(bg_num);
	add.pltt_arc	= IMC_BG_LEFT_FRAME_CL;
	add.scrn_arc	= IMC_BG_LEFT_SC_ARC_GET(bg_num);
	add.x			= IMC_LBOX_AREA_X;
	add.y			= IMC_LBOX_AREA_HEIGHT;
	add.frame		= GF_BGL_FRAME3_M;
	add.pltt_num	= IMC_LBOX_BG_PLTT_NUM;
	add.pltt_offs	= IMC_LBOX_BG_PLTT_OFFS;
	add.char_offs	= 0;
	add.heap		= HEAPID_IMAGECLIP_DRAW;

	IMC_BG_MakaObj( &lbox->boxDraw.bg, &add );

	lbox->boxData.back_no = bg_num;
}

//----------------------------------------------------------------------------
/**
 * ���G�t�F�N�g�t��
 *
 *	@brief	���{�b�N�X�w�i��ύX
 *
 *	@param	lbox		���{�b�N�f�[�^
 *	@param	bg_num		�ύX���BG�i���o�[
 *	@param	fade_way	�t�F�[�h����
 *	@param	sync		���V���N�ōs����
 *	@param	end_flg		�I�����m�t���O
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_LBOX_BGChange( IMC_LEFT_BOX* lbox, int bg_num, int fade_way, int sync, BOOL* end_flg )
{
	IMC_BG_ADD add;
	int fade_x, fade_y;
	
	// �o�^�f�[�^�ݒ�
	add.bg_ini		= lbox->boxDraw.BG_Ini;
	add.arc_file	= ARC_IMAGECLIP_GRA;
	add.char_arc	= IMC_BG_LEFT_CG_ARC_GET(bg_num);
	add.pltt_arc	= IMC_BG_LEFT_FRAME_CL;
	add.scrn_arc	= IMC_BG_LEFT_SC_ARC_GET(bg_num);
	add.x			= IMC_LBOX_AREA_X;
	add.y			= IMC_LBOX_AREA_HEIGHT;
	add.frame		= GF_BGL_FRAME3_M;
	add.pltt_num	= IMC_LBOX_BG_PLTT_NUM;
	add.pltt_offs	= IMC_LBOX_BG_PLTT_OFFS;
	add.char_offs	= 0;
	add.heap		= HEAPID_IMAGECLIP_DRAW;

	if( fade_way & IMC_LBOX_FADE_X ){
		fade_x = IMC_LBOX_AREA_WIDTH;
	}else{
		fade_x = 0;
	}

	if( fade_way & IMC_LBOX_FADE_Y ){
		fade_y = IMC_LBOX_AREA_HEIGHT;
	}else{
		fade_y = 0;
	}

	IMC_BG_ScrollReq( &lbox->boxDraw.bg, &add, fade_x, fade_y, sync, end_flg );

	lbox->boxData.back_no = bg_num;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	BG���N���[������
 *
 *	@param	lbox		���{�b�N�X
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_LBOX_BGClean( IMC_LEFT_BOX* lbox )
{
	IMC_BG_DeleteObj( &lbox->boxDraw.bg );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	���݂̃��[�h
 *
 *	@param	lbox	���{�b�N�X
 *
 *	@return	�A�N�Z�T�����[�h
 *
 * mode
	IMC_OBJLIST_ACCE,		// �A�N�Z�T���^�C�v
	IMC_OBJLIST_BG,			// BG�T���l�C���^�C�v
	IMC_OBJLIST_SND,		// �T�E���h�T���l�C���^�C�v
	IMC_OBJLIST_ACCE_MAX	// ���[�h�ő吔
 *
 */
//-----------------------------------------------------------------------------
int IMC_LBOX_GetMode( IMC_LEFT_BOX* lbox )
{
	GF_ASSERT( lbox );
	return lbox->boxData.mode;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	���݂̃J�����g�_�~�[�e�[�u���i���o�[���擾
 *
 *	@param	lbox	���{�b�N�X�f�[�^
 *	@param	mode	���ׂ������[�h
 *	
 *	@return	�J�����g�_�~�[�e�[�u���i���o�[
 *
 *
 */
//-----------------------------------------------------------------------------
int IMC_LBOX_GetCurrentNo( IMC_LEFT_BOX* lbox, int mode  )
{
	IMC_LEFT_LIST_DATA mode_list;
	
	GF_ASSERT( lbox );

	mode_list = lbox->boxData.acce_list[ mode ];
	return mode_list.dummyCurrent;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�_�~�[�e�[�u�������擾
 *
 *	@param	lbox		���{�b�N�X�I�u�W�F
 *	@param	mode		�A�N�Z�T�����[�h
 *
 *	@return	�_�~�[�e�[�u����
 *
 *
 */
//-----------------------------------------------------------------------------
int IMC_LBOX_GetDummyTblNum( IMC_LEFT_BOX* lbox, int mode )
{
	IMC_LEFT_LIST_DATA mode_list;
	
	GF_ASSERT( lbox );

	mode_list = lbox->boxData.acce_list[ mode ];
	return mode_list.dummyNum;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�A�N�Z�T�����X�g�S�Ă̍��W�𓮂���
 *
 *	@param	lbox		���{�b�N�X
 *	@param	mode		���[�h
 *	@param	list_no		���X�g�i���o�[
 *	@param	x			�����������W
 *	@param	y			�����������W
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_LBOX_AccessorieListMove( IMC_LEFT_BOX* lbox, int mode, int list_no, int x, int y )
{
	IMC_OBJLIST* dummyTbl;
	
	// mode�ƃ��X�g����擪�_�~�[�f�[�^�擾
	dummyTbl = getDummyTbl( lbox, mode, list_no );
	
	IMC_OBJLIST_ACCEPOKE_ListMove( dummyTbl, x, y );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�����{�b�N���󂵂Ă悢��ԂȂ̂����`�F�b�N
 *
 *	@param	lbox	���{�b�N�X�f�[�^
 *
 *	@retval	TRUE	OK
 *	@retval FALSE	NG		�t�F�[�h���ł�
 *
 *
 */
//-----------------------------------------------------------------------------
BOOL IMC_LBOX_ENDCheck( IMC_LEFT_BOX* lbox )
{
	if( lbox->boxData.state == IMC_LBOX_STATE_NORM ){
		return TRUE;
	}

	return FALSE;
}

//-----------------------------------------------------------------------------
/**
*		�v���C�x�[�g�֐�
*/
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *
 *	@brief	�A�N�Z�T�����X�g�쐬
 *
 *	@param	lbox	���{�b�N�X�f�[�^
 *	@param	init	�������f�[�^
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void makeAcceList( IMC_LEFT_BOX* lbox, IMC_LEFT_BOX_INIT* init )
{
	// �A�N�Z�T�����X�g�쐬
	listDataMake( &lbox->boxData.acce_list[ IMC_OBJLIST_ACCE ], init->accelist_num );

	// �J�����g�ɐݒ�
	lbox->boxData.mode	= IMC_OBJLIST_ACCE;
	drawSetList( lbox->boxData.acce_list[ IMC_OBJLIST_ACCE ].dummyTbl, TRUE );

	// BG�T���l�C�����X�g�쐬
	listDataMake( &lbox->boxData.acce_list[ IMC_OBJLIST_BG ], init->bglist_num );
	
	// �����T���l�C�����X�g�쐬
	listDataMake( &lbox->boxData.acce_list[ IMC_OBJLIST_SND ], init->sndlist_num );

	// �t�F�[�h�p���X�g
	listDataMake( &lbox->boxData.acce_list[ IMC_LBOX_FADELIST_MODE ], IMC_LBOX_FADELIST_LISTNUM );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�I�u�W�F�N�g���X�g�̕\����\���ݒ�
 *
 *	@param	dummy		�_�~�[�f�[�^
 *	@param	flag		�\����\���t���O
 *
 *	@return
 *
 *
 */
//-----------------------------------------------------------------------------
static void drawSetList( IMC_OBJLIST* dummy, int flag )
{
	IMC_OBJLIST* work;
	
	work = dummy->next;
	while( work != (dummy) ){


		if( (work->flag == IMC_OBJLIST_ACCE) ||
			(work->flag == IMC_OBJLIST_BG) ||
			(work->flag == IMC_OBJLIST_SND)){
			
			IMC_ACCE_ObjListDrawSet( work->obj_data, flag );
		}

		work = work->next;
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�\����\���ݒ��ʊ֐�
 *
 *	@param	lbox		���{�b�N�X
 *	@param	mode		�A�N�Z�T�����[�h
 *	@param	list		���X�g�ԍ�
 *	@param	flag		�\����\��
 *
 *	@return	none
 *	
 *
 */
//-----------------------------------------------------------------------------
static void drawSetListPack( IMC_LEFT_BOX* lbox, int mode, int list, int flag )
{
	IMC_OBJLIST* dummytbl;
	dummytbl = getDummyTbl( lbox, mode, list );

	drawSetList( dummytbl, flag );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�J�����g�_�~�[���X�g�̕\����\���̐ݒ�
 *
 *	@param	lbox		���{�b�N�X�I�u�W�F
 *	@param	flag		�\��/��\���t���O
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void drawFlgCurrentDummy( IMC_LEFT_BOX* lbox, int flag )
{
	IMC_OBJLIST* dummyTbl;
	
	// �J�����g�_�~�[���X�g�擾
	dummyTbl = getCurrentDummy( lbox );

	// ���ꂩ��̃J�����g�`��ON
	drawSetList( 
			dummyTbl,
			flag );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�_�~�[���X�g�e�[�u���̍쐬	
 *
 *	@param	list		�_�~�[���X�g�e�[�u��
 *	@param	dummy_num	�쐬����擪�_�~�[�f�[�^��
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void listDataMake( IMC_LEFT_LIST_DATA* list, int dummy_num )
{
	int i;
	
	list->dummyTbl	= sys_AllocMemory( HEAPID_IMAGECLIP_DRAW, sizeof(IMC_OBJLIST) * dummy_num );
	list->dummyNum	= dummy_num;
	list->dummyCurrent	= 0;

	for( i=0; i<list->dummyNum; i++ ){
		list->dummyTbl[ i ].next = list->dummyTbl + i;
		list->dummyTbl[ i ].prev = list->dummyTbl + i;

		drawSetList( 
				list->dummyTbl + i,
				FALSE );
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�A�N�Z�T�����X�g�f�[�^�j��
 *
 *	@param	list	�A�N�Z�T�����X�g
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void listDataDest( IMC_LEFT_LIST_DATA* list )
{
	sys_FreeMemoryEz( list->dummyTbl );
	list->dummyTbl	= NULL;

	memset( list, 0, sizeof(IMC_LEFT_LIST_DATA) );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	���̃J�����g�_�~�[���X�g���擾
 *
 *	@param	lbox	���{�b�N�X�I�u�W�F
 *
 *	@return	�J�����g�̃_�~�[���X�g
 *
 *
 */
//-----------------------------------------------------------------------------
static IMC_OBJLIST* getCurrentDummy( IMC_LEFT_BOX* lbox )
{
	IMC_LEFT_LIST_DATA mode_list;
		
	mode_list = lbox->boxData.acce_list[ lbox->boxData.mode ];
	return &mode_list.dummyTbl[ mode_list.dummyCurrent ];
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�_�~�[���X�g��I�����Ď擾
 *
 *	@param	lbox		���{�b�N�X�I�u�W�F
 *	@param	mode		���[�h
 *	@param	tbl_no		�e�[�u���ԍ�
 *
 *	@return	�_�~�[���X�g
 *
 *
 */
//-----------------------------------------------------------------------------
static IMC_OBJLIST* getDummyTbl( IMC_LEFT_BOX* lbox, int mode, int tbl_no )
{
	IMC_LEFT_LIST_DATA mode_list;
		
	mode_list = lbox->boxData.acce_list[ mode ];
	return &mode_list.dummyTbl[ tbl_no ];
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	���X�g�ɓo�^����Ă���A�N�Z�T�������擾����
 *
 *	@param	lbox		���{�b�N�X
 *	@param	mode		���X�g���[�h
 *	@param	tbl_no		�_�~�[�f�[�^�i���o�[
 *
 *	@return	�o�^����Ă���I�u�W�F�N�g��
 *
 *
 */
//-----------------------------------------------------------------------------
static int getListSetDataNum( IMC_LEFT_BOX* lbox, int mode, int tbl_no )
{
	IMC_OBJLIST* dummy;
	IMC_OBJLIST* work;
	int count = 0;

	// �_�~�[�e�[�u��
	dummy = getDummyTbl( lbox, mode, tbl_no );
	work = dummy->next;

	while( work != dummy ){
		
		count++;
		work = work->next;
	}

	return count;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�I�u�W�F�N�g���X�g�̎w�萔�ڂ̃f�[�^���擾
 *
 *	@param	lbox		���{�b�N�X
 *	@param	mode		���X�g���[�h
 *	@param	tbl_no		���X�g�i���o�[
 *	@param	no			�w�萔
 *
 *	@retval	NULL		�w�萔�����������Ȃ���
 *	@retval	���̑�		�擾����
 *
 *
 */
//-----------------------------------------------------------------------------
static IMC_OBJLIST* getNoListObjData( IMC_LEFT_BOX* lbox, int mode, int tbl_no, int no )
{
	IMC_OBJLIST* dummy;
	IMC_OBJLIST* work;
	int count = 0;

	// �_�~�[�e�[�u��
	dummy = getDummyTbl( lbox, mode, tbl_no );
	work = dummy->next;

	while( work != dummy ){
		
		if( count == no ){

			return work;
		}

		count++;
		work = work->next;
	}

	return NULL;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�\��/��\�����f�𔻒肵�ĕ\����\����ݒ肷��
 *
 *	@param	lbox		���{�b�N�X�I�u�W�F
 *	@param	acce_obj	�A�N�Z�T���I�u�W�F
 *	@param	mode		���[�h
 *	@param	list_num	�_�~�[�f�[�^�i���o�[
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void drawFlgSetCheck( IMC_LEFT_BOX* lbox, IMC_ACCESSORIE_OBJ* acce_obj, int mode, int list_num )
{
	// �ǉ��悪�J�����g�̃��X�g�łȂ���Δ�\���ɂ���
	if( (lbox->boxData.mode != mode) || 
		(lbox->boxData.acce_list[ mode ].dummyCurrent != list_num) ){

		IMC_ACCE_ObjListDrawSet( acce_obj, FALSE );
	}else{

		IMC_ACCE_ObjListDrawSet( acce_obj, TRUE );
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�T���l�C�����W���擾����
 *
 *	@param	no		�A�N�Z�T��No
 *	@param	x		X���W�i�[��
 *	@param	y		�����W�i�[��
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void getBgSndThumbMat( int no, int* x, int* y )
{
	int step_y;		// �c���i�ڂ�
	int step_x;		// �����i�ڂ�
	
	// ���X�g���i���o�[�ɂ���
	no %= IMC_LBOX_BG_ONE_LIST_NUM;
	
	// �i�����v�Z
	step_y = no / IMC_LBOX_MAT_LINE_NUM;
	step_x = no % IMC_LBOX_MAT_LINE_NUM;

	// �܂�������
	*y = IMC_LBOX_MAT_SPACE_Y * (step_y + 1);
	*y += IMC_LBOX_THUMB_SIZE_Y * step_y;
	*y += IMC_LBOX_AREA_Y;

	// ������
	*x = IMC_LBOX_MAT_SPACE_X * (step_x + 1);
	*x += IMC_LBOX_THUMB_SIZE_X * step_x;
	*x += IMC_LBOX_AREA_X;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�p���b�g�t�F�[�h�J�n
 *
 *	@param	lbox			���{�b�N�X
 *	@param	out_mode		�t�F�[�h�A�E�g�p���b�gmode
 *	@param	out_list		�t�F�[�h�A�E�g�p���b�gno
 *	@param	in_mode			�t�F�[�h�C���p���b�gmode
 *	@param	in_list			�t�F�[�h�C���p���b�gno
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void plttChgTaskStart( IMC_LEFT_BOX* lbox, int out_mode, int out_list, int in_mode, int in_list )
{
	TCB_PTR tcb;
	IMC_LBOX_PLTT_TASK* pltt_tsk;
	
	// �^�X�N����
	tcb = PMDS_taskAdd( plttChgTask, sizeof(IMC_LBOX_PLTT_TASK), 0, HEAPID_IMAGECLIP_DATA );

	// ���[�N�ɒl��ݒ�
	pltt_tsk = TCB_GetWork( tcb );

	// �f�[�^�ݒ�
	pltt_tsk->lbox		= lbox;
	pltt_tsk->out_mode	= out_mode;
	pltt_tsk->out_list	= out_list;
	pltt_tsk->in_mode	= in_mode;
	pltt_tsk->in_list	= in_list;
	pltt_tsk->seq		= IMC_LBOX_PLTT_CHG_INIT;
	pltt_tsk->out_count	= getListSetDataNum( lbox, out_mode, out_list );
	pltt_tsk->in_count	= getListSetDataNum( lbox, in_mode, in_list );
	pltt_tsk->move_obj_num = pltt_tsk->out_count + pltt_tsk->in_count;

	pltt_tsk->move_obj = sys_AllocMemory( HEAPID_IMAGECLIP_DATA, sizeof(IMC_LBOX_PLTT_OBJ_MOVE) * pltt_tsk->move_obj_num );
	GF_ASSERT( pltt_tsk->move_obj );
	memset( pltt_tsk->move_obj, 0, 
			sizeof(IMC_LBOX_PLTT_OBJ_MOVE) * pltt_tsk->move_obj_num );

	// ���p���b�g��Ԃ��t�F�[�h���ɂ���
	lbox->boxData.state = IMC_LBOX_STATE_FADE;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�p���b�g�t�F�[�h
 *
 *	@param	tcb		tcb�^�X�N
 *	@param	work	���[�N
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void plttChgTask( TCB_PTR tcb, void* work )
{
	IMC_LBOX_PLTT_TASK* tsk_w = work;
	int i;
	int bg_no;
	
	switch( tsk_w->seq ){
	case IMC_LBOX_PLTT_CHG_INIT:
		
		// �t�F�[�h�C�����郊�X�g�̍��W��ݒ�
		IMC_LBOX_AccessorieListMove( tsk_w->lbox, tsk_w->in_mode, tsk_w->in_list, 0, -IMC_LBOX_PLTT_CHG_MOVE_Y );
		
		// �t�F�[�h�C�����郊�X�g��\��������
		drawSetListPack( tsk_w->lbox, tsk_w->in_mode, tsk_w->in_list, TRUE );

		// BG�t�F�[�h�A�E�g�J�n
		tsk_w->bg_fade = FALSE;
		bg_no = (tsk_w->lbox->boxData.back_no + 1) % IMC_BG_LEFT_MAX;
		IMC_LBOX_BGChange( tsk_w->lbox, bg_no, IMC_LBOX_FADE_Y, IMC_LBOX_PLTT_BG_SYNC, &tsk_w->bg_fade );

		// ��x�ɑ����������߂�
		tsk_w->count = movePlttChgGetObjAddNum( tsk_w->out_count, IMC_LBOX_PLTT_CHG_OBJ_E_NUM );

		tsk_w->seq++;
		break;
		
	case IMC_LBOX_PLTT_CHG_OUT_ACCE_S:
		
		// ������BG�ƃA�N�Z�T������ʊO��
		for( i=0; i<tsk_w->count; i++ ){
			
			// �o�^
			if( (tsk_w->out_count - 1) >= 0 ){
				IMC_OBJLIST* obj;	

				tsk_w->out_count --;
				obj = getNoListObjData( tsk_w->lbox, tsk_w->out_mode, tsk_w->out_list, tsk_w->out_count );
				startPlttChgObj( obj, tsk_w->move_obj, tsk_w->move_obj_num );
			}
		}
		if(tsk_w->out_count == 0){

			// ��x�ɑ����������߂�
			tsk_w->count = movePlttChgGetObjAddNum( tsk_w->in_count, IMC_LBOX_PLTT_CHG_OBJ_S_NUM );

			// ����
			tsk_w->seq ++;
		}
		break;

	case IMC_LBOX_PLTT_CHG_IN_ACCE_S:
		// �V�A�N�Z�T������ʂ�
		for( i=0; i<tsk_w->count; i++ ){
			
			// �o�^
			if( (tsk_w->in_count - 1) >= 0 ){
				IMC_OBJLIST* obj;	

				tsk_w->in_count --;
				obj = getNoListObjData( tsk_w->lbox, tsk_w->in_mode, tsk_w->in_list, tsk_w->in_count );
				startPlttChgObj( obj, tsk_w->move_obj, tsk_w->move_obj_num );
			}
		}
		if(tsk_w->in_count == 0){
			// ����
			tsk_w->seq ++;
			tsk_w->count = 0;
		}
		break;
		
	case IMC_LBOX_PLTT_CHG_WAIT:
		// �S�Ă������I���̂�҂�
		tsk_w->count ++;

		// �I�u�W�F�N�g�̓���
		if( tsk_w->count > IMC_LBOX_PLTT_CHG_COUNT ){
				
			// BG�t�F�[�h
			if( tsk_w->bg_fade ){

				tsk_w->seq ++;
			}
		}
		break;

	case IMC_LBOX_PLTT_CHG_END:
		// ���W���Đݒ肵�ďI���
		// �t�F�[�h�A�E�g���郊�X�g���\���ɂ���
		drawSetListPack( tsk_w->lbox, tsk_w->out_mode, tsk_w->out_list, FALSE );
		
		// �t�F�[�h�A�E�g���X�g�̍��W��ݒ�
		IMC_LBOX_AccessorieListMove( tsk_w->lbox, tsk_w->out_mode, tsk_w->out_list, 0, -IMC_LBOX_PLTT_CHG_MOVE_Y );

		// ���p���b�g��Ԃ�ʏ�ɂ���
		tsk_w->lbox->boxData.state = IMC_LBOX_STATE_NORM;

		// �m�ۂ����������j��
		sys_FreeMemoryEz( tsk_w->move_obj );
	
		// �^�X�N�I��
		PMDS_taskDel( tcb );
		
		return ;

	default:
		GF_ASSERT(0);
		break;
	}

	// �I�u�W�F�N�g����
	movePlttChgObj( tsk_w->move_obj, tsk_w->move_obj_num );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�t�F�[�h�p�^�[���I�u�W�F�N�g����^�X�N�ɐݒ�
 *
 *	@param	obj		�I�u�W�F�f�[�^
 *	@param	data	����f�[�^�e�[�u��
 *	@param	num		�e�[�u����
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void startPlttChgObj( IMC_OBJLIST* obj, IMC_LBOX_PLTT_OBJ_MOVE* data, int num )
{
	IMC_LBOX_PLTT_OBJ_MOVE* obj_move;

	// ��̃I�u�W�F����e�[�u���擾
	obj_move = getCleanPlttChgObj( data, num );


	obj_move->obj		= obj;
	obj_move->count		= IMC_LBOX_PLTT_CHG_COUNT;
	obj_move->add_y		= IMC_LBOX_PLTT_CHG_ADD;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�N���[����Ԃ̃e�[�u�����擾
 *
 *	@param	data	�e�[�u��
 *
 *	@return	�����ݒ肳��Ă��Ȃ��e�[�u��
 *
 *
 */
//-----------------------------------------------------------------------------
static IMC_LBOX_PLTT_OBJ_MOVE* getCleanPlttChgObj( IMC_LBOX_PLTT_OBJ_MOVE* data, int num )
{
	int i;	// ���[�v�p

	for( i=0; i<num; i++ ){

		if( data[i].obj == NULL ){
			return data + i;
		}
	}

	return NULL;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�p���b�g�t�F�[�h�X�I�u�W�F����֐������s
 *
 *	@param	data	����e�[�u��
 *	@param	num		�e�[�u����
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void movePlttChgObj( IMC_LBOX_PLTT_OBJ_MOVE* data, int num )
{
	int i;		// ���[�v�p

	for( i=0; i<num; i++ ){
		if( data[i].obj ){

			movePlttChgObjCore( data + i );
		}
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�p���b�g�t�F�[�h�X�I�u�W�F����֐�
 *
 *	@param	data	����e�[�u��
 *
 *	@return none
 *
 */
//-----------------------------------------------------------------------------
static void movePlttChgObjCore( IMC_LBOX_PLTT_OBJ_MOVE* data )
{
	int x, y;
	
	IMC_OBJLIST_ACCEPOKE_MatGet( data->obj, &x, &y );

	y += data->add_y;

	IMC_OBJLIST_ACCEPOKE_Mat( data->obj, x, y );

	data->count --;

	// �I���`�F�b�N
	if( data->count <= 0 ){

		memset( data, 0, sizeof(IMC_LBOX_PLTT_OBJ_MOVE) );
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	��x�ɓ������A�N�Z�T�������擾
 *
 *	@param	obj_num		�A�N�Z�T������
 *	@param	div			���V���N�ɕ����邩
 *
 *	@return	��x�ɓ�������
 *
 *
 */
//-----------------------------------------------------------------------------
static int movePlttChgGetObjAddNum( int obj_num, int div )
{
	// ����؂��l�ɂ���
	obj_num += div - (obj_num % div);

	return obj_num / div;
}
