//============================================================================================
/**
 * @file	field_subscreen.c
 * @brief
 * @author	tamada
 * @date	2006.02.03
 */
//============================================================================================

#include "common.h"
#include "system/pm_overlay.h"


#include "fieldsys.h"

#include "field_subscreen.h"

#include "comm_union.h"
#include "comm_union_view.h"
#include "comm_union_view_def.h"
#include "union_board.h"
#include "comm_field_state.h"
#include "field_poketch.h"



//============================================================================================
//============================================================================================
//------------------------------------------------------------------
/**
 * @brief	�T�u��ʏ����c�[���̂܂Ƃ�
 */
//------------------------------------------------------------------
typedef struct SUBSCRN_FUNCLIST{
	void (*set_init)(FIELDSYS_WORK *);		///<�T�u��ʏ������������N�G�X�g�֐�
	BOOL (*wait_init)(FIELDSYS_WORK *);		///<�T�u��ʏ����������҂��֐�
	void (*set_quit)(FIELDSYS_WORK *);		///<�T�u��ʏI���������N�G�X�g�֐�
	BOOL (*wait_quit)(FIELDSYS_WORK *);		///<�T�u��ʏI�������҂��֐�
}SUBSCRN_FUNCLIST;



FS_EXTERN_OVERLAY(unionroom_board);

//============================================================================================
//============================================================================================
static void FieldSubScreen_Init_Normal(FIELDSYS_WORK * fsys);
static void FieldSubScreen_Init_Under(FIELDSYS_WORK * fsys);
static void FieldSubScreen_Init_Union(FIELDSYS_WORK * fsys);
static void FieldSubScreen_Quit_Normal(FIELDSYS_WORK * fsys);
static void FieldSubScreen_Quit_Under(FIELDSYS_WORK * fsys);
static void FieldSubScreen_Quit_Union(FIELDSYS_WORK * fsys);
static BOOL FieldSubScreen_WaitQuit_Normal(FIELDSYS_WORK * fsys);
static BOOL FieldSubScreen_WaitQuit_Under(FIELDSYS_WORK * fsys);
static BOOL FieldSubScreen_WaitQuit_Union(FIELDSYS_WORK * fsys);

//------------------------------------------------------------------
/**
 * @brief	�T�u��ʐ���p�֐��S
 *
 * �T�u��ʂɊւ��鏉����������I���������܂Ƃ߂����́B
 * �����ɂ܂Ƃ߂邱�ƂŃt�B�[���h�}�b�v�{�̂���ڍ׏�����
 * �������Ă���B
 */
//------------------------------------------------------------------
static const SUBSCRN_FUNCLIST SubScreenFuncList[] = {
	{	///�ʏ�t�B�[���h�p��`
		FieldSubScreen_Init_Normal,			// ������
		NULL,								// �����������I���҂�
		FieldSubScreen_Quit_Normal,			// �I���������N�G�X�g
		FieldSubScreen_WaitQuit_Normal,		// �I�������҂�
	},
	{	///�Y�z�p��`
		FieldSubScreen_Init_Under,
		NULL,
		FieldSubScreen_Quit_Under,
		FieldSubScreen_WaitQuit_Under,
	},

	{	/// ���j�I�����[���p��`
		FieldSubScreen_Init_Union,			// ������
		NULL,								// �����������I���҂�
		FieldSubScreen_Quit_Union,			// �I���������N�G�X�g
		FieldSubScreen_WaitQuit_Union,	// �I�������҂�
	
	},
	{
		FieldBeforePoketch_Init,			// ������
		NULL,								// �����������I���҂�
		FieldBeforePoketch_QuitReq,			// �I���������N�G�X�g
		FieldBeforePoketch_QuitWait,		// �I�������҂�
	},
};

//============================================================================================
//============================================================================================
//------------------------------------------------------------------
//------------------------------------------------------------------
static int GetType(FIELDSYS_WORK * fsys)
{
	FIELD_SUBSCRN_TYPE type = fsys->subscreen;
	GF_ASSERT(type != 0);
	GF_ASSERT(type < FIELD_SUBSCRN_MAX);
	return type - 1;
}

//============================================================================================
//
//
//		�t�B�[���h�}�b�v����Ă΂��T�u��ʏ����֐�
//
//
//============================================================================================
//------------------------------------------------------------------
/**
 * @brief	�T�u��ʏ����F���������N�G�X�g
 * @param	fsys	�Q�[���V�X�e���ւ̃|�C���^
 */
//------------------------------------------------------------------
void FieldSubScreen_Init(FIELDSYS_WORK * fsys)
{
	SubScreenFuncList[GetType(fsys)].set_init(fsys);
}

//------------------------------------------------------------------
/**
 * @brief	�T�u��ʏ����F�������҂�
 * @param	fsys	�Q�[���V�X�e���ւ̃|�C���^
 * @return	BOOL	TRUE�̂Ƃ��A�����I��
 */
//------------------------------------------------------------------
BOOL FieldSubScreen_WaitInit(FIELDSYS_WORK * fsys)
{
	BOOL (*func)(FIELDSYS_WORK *);
	func = SubScreenFuncList[GetType(fsys)].wait_init;
	if (func == NULL) {
		return TRUE;
	}
	return func(fsys);
}

//------------------------------------------------------------------
/**
 * @brief	�T�u��ʏ����F�I�����N�G�X�g
 * @param	fsys	�Q�[���V�X�e���ւ̃|�C���^
 */
//------------------------------------------------------------------
void FieldSubScreen_Quit(FIELDSYS_WORK * fsys)
{
	SubScreenFuncList[GetType(fsys)].set_quit(fsys);
}

//------------------------------------------------------------------
/**
 * @brief	�T�u��ʏ����F�I���҂�
 * @param	fsys	�Q�[���V�X�e���ւ̃|�C���^
 * @return	BOOL	TRUE�̂Ƃ��A�����I��
 */
//------------------------------------------------------------------
BOOL FieldSubScreen_WaitQuit(FIELDSYS_WORK * fsys)
{
	return SubScreenFuncList[GetType(fsys)].wait_quit(fsys);
}


//============================================================================================
//
//
//		�T�u��ʂ��Ƃ̌ʊ֐�
//
//
//============================================================================================
//------------------------------------------------------------------
/**
 * @brief	�T�u��ʏ����F���������N�G�X�g�F�ʏ�t�B�[���h�p
 * @param	fsys	�Q�[���V�X�e���ւ̃|�C���^
 */
//------------------------------------------------------------------
static void FieldSubScreen_Init_Normal(FIELDSYS_WORK * fsys)
{
	FieldPoketch_Init(fsys);
}

//------------------------------------------------------------------
/**
 * @brief	�T�u��ʏ����F���������N�G�X�g�F�Y�z�p
 * @param	fsys	�Q�[���V�X�e���ւ̃|�C���^
 */
//------------------------------------------------------------------
static void FieldSubScreen_Init_Under(FIELDSYS_WORK * fsys)
{
	CommStateFieldUnderOptionReboot();  // �n���p�ʐM�̃I�v�V�����𕜋A
}

//------------------------------------------------------------------
/**
 * @brief	�T�u��ʏ����F���������N�G�X�g�F���j�I�����[���p�p
 * @param	fsys	�Q�[���V�X�e���ւ̃|�C���^
 */
//------------------------------------------------------------------
static void FieldSubScreen_Init_Union(FIELDSYS_WORK * fsys)
{

	Overlay_Load( FS_OVERLAY_ID( unionroom_board ), OVERLAY_LOAD_NOT_SYNCHRONIZE );
	fsys->union_board = UnionRoom_BoardInit( fsys );
}

//------------------------------------------------------------------
/**
 * @brief	�T�u��ʏ����F�I�����N�G�X�g�F�ʏ�t�B�[���h�p
 * @param	fsys	�Q�[���V�X�e���ւ̃|�C���^
 */
//------------------------------------------------------------------
static void FieldSubScreen_Quit_Normal(FIELDSYS_WORK * fsys)
{
	FieldPoketch_QuitReq( fsys );
}

//------------------------------------------------------------------
/**
 * @brief	�T�u��ʏ����F�I�����N�G�X�g�F�Y�B�p
 * @param	fsys	�Q�[���V�X�e���ւ̃|�C���^
 */
//------------------------------------------------------------------
static void FieldSubScreen_Quit_Under(FIELDSYS_WORK * fsys)
{
	CommStateFieldUnderOptionReset();  // �n���p�ʐM�̃I�v�V������j��
}

//------------------------------------------------------------------
/**
 * @brief	�T�u��ʏ����F�I�����N�G�X�g�F�Y�B�p
 * @param	fsys	�Q�[���V�X�e���ւ̃|�C���^
 */
//------------------------------------------------------------------
static void FieldSubScreen_Quit_Union(FIELDSYS_WORK * fsys)
{
	UnionRoom_BoardEnd( fsys->union_board );
	Overlay_UnloadID( FS_OVERLAY_ID( unionroom_board ) );

}

//------------------------------------------------------------------
/**
 * @brief	�T�u��ʏ����F�I���҂��F�ʏ�t�B�[���h�p
 * @param	fsys	�Q�[���V�X�e���ւ̃|�C���^
 * @return	BOOL	TRUE�̂Ƃ��A�����I��
 */
//------------------------------------------------------------------
static BOOL FieldSubScreen_WaitQuit_Normal(FIELDSYS_WORK * fsys)
{
	return FieldPoketch_QuitWait( fsys );
}

//------------------------------------------------------------------
/**
 * @brief	�T�u��ʏ����F�I���҂��F���j�I���p
 * @param	fsys	�Q�[���V�X�e���ւ̃|�C���^
 * @return	BOOL	TRUE�̂Ƃ��A�����I��
 */
//------------------------------------------------------------------
static BOOL FieldSubScreen_WaitQuit_Union(FIELDSYS_WORK * fsys)
{
	return TRUE;
}

//------------------------------------------------------------------
/**
 * @brief	�T�u��ʏ����F�I���҂��F�Y�z�p
 * @param	fsys	�Q�[���V�X�e���ւ̃|�C���^
 * @return	BOOL	TRUE�̂Ƃ��A�����I��
 */
//------------------------------------------------------------------
static BOOL FieldSubScreen_WaitQuit_Under(FIELDSYS_WORK * fsys)
{
	//�I���������A��������TRUE��Ԃ�
	return TRUE;
}

