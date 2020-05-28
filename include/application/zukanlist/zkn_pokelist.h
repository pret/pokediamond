//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		zkn_pokelist.h
 *	@brief		�|�P�������X�g
 *	@author		tomoya takahashi
 *	@data		2006.01.18
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
#ifndef __ZKN_POKELIST_H__
#define __ZKN_POKELIST_H__

#include "include/application/zukanlist/zkn_sys_static.h"

#undef GLOBAL
#ifdef	__ZKN_POKELIST_H_GLOBAL
#define	GLOBAL	/* */
#else
#define	GLOBAL	extern
#endif

//-----------------------------------------------------------------------------
/**
 *					�萔�錾
*/
//-----------------------------------------------------------------------------
// ����^�C�~���O�萔
#define ZKN_POKELIST_MOVE_COUNT_UNIT	( 10 )	// 1 = 10�̒P�ʂŌv�Z
#define ZKN_POKELIST_MOVE_END_COUNT		( 64 * ZKN_POKELIST_MOVE_COUNT_UNIT )


// �G�t�F�N�g�p
// �|�P���X�g�e�[�u���ʒu
#define ZKN_POKELIST_TBL_MAT_Y	( 82 )
#define ZKN_POKELIST_TBL_MAT_X	( 170 )
// �|�P�����O���t�B�b�N
#define ZKN_POKELIST_POKEGRA_X				( 56 )	// �|�P�������W
#define ZKN_POKELIST_POKEGRA_Y				( 80 )	// �|�P�������W

//-------------------------------------
//	���X�g�̐i�ޕ���
//=====================================
enum{
	ZKN_POKE_LIST_NO_MOVE,		// ����Ȃ�
	ZKN_POKE_LIST_UP,			// ��Ɉړ�
	ZKN_POKE_LIST_DOWN,			// ���Ɉړ�
};

//-------------------------------------
//	�t�F�[�h���[�h
//=====================================
enum{
	ZKN_POKELIST_BG_FADE_NORMAL,
	ZKN_POKELIST_BG_FADE_SHUTTER,
};

//-------------------------------------
//	�z�C�[�����샍�b�N���[�h
//=====================================
enum{
	ZKN_POKELIST_WHEEL_LOCK_NONE,		// lock�Ȃ�
	ZKN_POKELIST_WHEEL_LOCK_NORMAL,		// lock���邵�����L�[����Ńz�C�[��������
	ZKN_POKELIST_WHEEL_LOCK_ALL			// ���S��lock����
};



// ���[�e�B���e�B�ʃV���b�^�[�t�F�[�h�ް�
#define ZKN_POKELIST_SCR_START_UP_CYSIZ		( 3 )
#define ZKN_POKELIST_SCR_START_DOWN_CYSIZ	( 14 )
#define ZKN_POKELIST_SCR_START_DOWN_YSIZ	( ZKN_POKELIST_SCR_START_DOWN_CYSIZ * 8 )
// BGShutter�t�F�[�h��
#define ZKN_POKELIST_BGSHUTTER_FADE00_TOP_S		( 0 )
#define ZKN_POKELIST_BGSHUTTER_FADE00_BOTTOM_S	( 0 )
#define ZKN_POKELIST_BGSHUTTER_FADE00_TOP_E		( ZKN_POKELIST_SCR_START_UP_CYSIZ )
#define ZKN_POKELIST_BGSHUTTER_FADE00_BOTTOM_E	( ZKN_POKELIST_SCR_START_DOWN_CYSIZ )

#define ZKN_POKELIST_BGSHUTTER_FADE01_TOP_S		( 12 )
#define ZKN_POKELIST_BGSHUTTER_FADE01_BOTTOM_S	( 20 )
#define ZKN_POKELIST_BGSHUTTER_FADE01_TOP_E		( ZKN_POKELIST_SCR_START_UP_CYSIZ )
#define ZKN_POKELIST_BGSHUTTER_FADE01_BOTTOM_E	( ZKN_POKELIST_SCR_START_DOWN_CYSIZ )
#define ZKN_POKELIST_BGSHUTTER_FADE_FONTBG_LIMIT	( -48 )



//-------------------------------------
//	�|�P�������X�g�O���[�o���f�[�^
//
//	�T�u��ʂƋ��L���邽�ߌ��J
//=====================================
typedef struct {
	int*				p_event_key;		// �C�x���g�L�[
	ZKN_GLB_DATA*		p_glb;				// �O���[�o���f�[�^

	int move_way;				// �i��ł������
	int move_count;				// ����J�E���g�l

	int fade_mode;				// �t�F�[�h���[�h
	BOOL fade_zukan_data;		// �}�Ӄf�[�^�t�F�[�h���[�h
	BOOL fade_sort_data;		// ��ĉ�ʂ���t�F�[�h���Ă���

	// �`��X�VONOFF
	BOOL move_draw;				// �ʏ�TRUE�@�X�VOFF�@FALSE

	u32 sub_wheel_lock;			// �T�u��ʂ̃z�C�[����lock����

	BOOL zukan_sort_end;		// SORT���[�h�I��
	BOOL zukan_end;				// �}�ӏI��
	BOOL zukan_see;				// �}�Ӄf�[�^������
	BOOL zukan_chg;				// �}�Ӄ��[�h�ύX
	BOOL sort_chg;				// SORT��ʂ֕ύX
} ZKN_POKELIST_GLB_DATA;

//-----------------------------------------------------------------------------
/**
 *					�\���̐錾
*/
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
/**
 *					�v���g�^�C�v�錾
*/
//-----------------------------------------------------------------------------
GLOBAL void ZKN_PokeListAplMake( ZKN_APL_DATA* p_data, ZKN_SYS_PTR zkn_sys, int heap );
GLOBAL void ZKN_PokeListAplDelete( ZKN_APL_DATA* p_data );

GLOBAL BOOL ZKN_PokeList_SubEventSetOkCheck( const ZKN_POKELIST_GLB_DATA* cp_glb );

#undef	GLOBAL
#endif		// __ZKN_POKELIST_H__

