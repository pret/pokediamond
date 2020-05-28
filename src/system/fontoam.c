//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		fontoam.c
 *	@brief		OAM���g�p����������`��V�X�e��
 *	@author		tomoya takahashi 
 *	@data		2005.10.20
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

#include <string.h>
#include "system.h"
#include "assert.h"
#include "char_manager.h"
#include "system/arc_tool.dat"
#include "system/arc_util.h"
#include "system/fontoam.naix"

#define	__FONTOAM_H_GLOBAL
#include "system/fontoam.h"

//-----------------------------------------------------------------------------
/**
 *					�萔�錾
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	
//	OAM�D�揇�ʒ萔	
//	
//=====================================
enum{
	FONTOAM_PRI_8x8 = 0,	
	FONTOAM_PRI_8x4,
	FONTOAM_PRI_4x8,
	FONTOAM_PRI_4x4,
	FONTOAM_PRI_4x2,
	FONTOAM_PRI_4x1,
	FONTOAM_PRI_2x4,
	FONTOAM_PRI_2x2,
	FONTOAM_PRI_2x1,
	FONTOAM_PRI_1x4,
	FONTOAM_PRI_1x2,
	FONTOAM_PRI_1x1,
	FONTOAM_PRI_MAX
};
enum{
	FONTOAM_PRI_X = 0,
	FONTOAM_PRI_Y,
	FONTOAM_PRI_XY
};

//-------------------------------------
//	
//	OAM���ߐs�����f�[�^�̗L��
//	
//=====================================
enum{
	FONTOAM_OAM_AREA_NONE,
	FONTOAM_OAM_AREA_RIGHT,		// �E�G���A����
};

#define FONTOAM_CHAR_BYTE	(32)	// 1char�T�C�Y
#define FONTOAM_CHAR_SIZE	(8)		// ���A����

//-----------------------------------------------------------------------------
/**
 *					�\���̐錾
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	
//	�Z���Ƃ��̍��W��ۑ�����\����
//	
//=====================================
typedef struct _FONTOAM_OBJ_CORE{
	CLACT_WORK_PTR clact;
	int	x;		// �h�b�g�P��
	int y;		// �h�b�g�P��
} FONTOAM_OBJ_CORE;

//-------------------------------------
//	
//	1OAM�t�H���g�f�[�^
//	
//=====================================
typedef struct _FONTOAM_OBJ{
	// ������E�B���h�E�̌`������킵�Ă���
	// �Z���̃f�[�^
	FONTOAM_OBJ_CORE*	obj_w;
	int obj_num;

	// ����Z���A�N�^�[
	CONST_CLACT_WORK_PTR parent;

	// ���̐ݒ���W
	int x;		// �h�b�g�P��
	int y;		// �h�b�g�P��
} FONTOAM_OBJ;

//-------------------------------------
//	
//	�V�X�e���f�[�^
//	
//=====================================
typedef struct _FONTOAM_SYSTEM{
	// OAM�T�C�Y���̃Z���f�[�^
	void*	pCellBuff[ FONTOAM_PRI_MAX ];
	NNSG2dCellDataBank* pCellBank[ FONTOAM_PRI_MAX ];

	// 1OAM�t�H���g�f�[�^���[�N
	FONTOAM_OBJ*	fontoam_work;
	int				fontoam_num;		// ���[�N��
} FONTOAM_SYSTEM;


//-------------------------------------
//	
//	OAM���ߐs�����G���A
//	�P�G���A�f�[�^
//	
//=====================================
typedef struct _FONTOAM_OAM_AREA_ONE{
	// �S�ăL�����N�^�P��
	int top;		// ��
	int left;		// ��
	int width;		// ��
	int height;		// ����
} FONTOAM_OAM_AREA_ONE;

//-------------------------------------
//	
//	OAM���ߐs�����G���A
//
//	�܂�now�ɓ����Ă���G���A����OAM���쐬
//	now���S�ĂO�ɂȂ�����right��now�ɑ������
//	now���܂��S�ĂO�ɂȂ�܂�OAM�Ŗ��߂Ă���
//	
//=====================================
typedef struct _FONTOAM_OAM_AREA{
	FONTOAM_OAM_AREA_ONE now;
	FONTOAM_OAM_AREA_ONE right;
	u8	tmp_flg;					// �l�̗L��
/*						
	FONTOAM_OAM_AREA_NONE,
	FONTOAM_OAM_AREA_RIGHT,		// �E�G���A����
	FONTOAM_OAM_AERA_MAX		// ����*/
} FONTOAM_OAM_AREA;

//-------------------------------------
//	
//	���ߐs����OAM�f�[�^
//	
//=====================================
typedef struct _FONTOAM_OAM_DATA{
	int x;			// �L�����N�^�P�ʍ��W
	int y;			// �L�����N�^�P�ʍ��W
	int oam_size;	// OAM�T�C�Y

	struct _FONTOAM_OAM_DATA* next;
	struct _FONTOAM_OAM_DATA* prev;

} FONTOAM_OAM_DATA;

//-------------------------------------
//	
//	���ߐs����OAM�f�[�^
//	
//=====================================
typedef struct _FONTOAM_OAM_DATA_SET{
	FONTOAM_OAM_DATA fontoamdata;
	int data_num;
} FONTOAM_OAM_DATA_SET;



//-----------------------------------------------------------------------------
/**
*		�O���[�o���ϐ�
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	
//	OAM�D�揇�ʒ萔	
//	�ɑΉ������L�����N�^�P�ʂ�OAM�T�C�Y
//	
//=====================================
static const u8 FONTOAM_PriTbl[ FONTOAM_PRI_MAX ][ FONTOAM_PRI_XY ] = {
	{8, 8},
	{8, 4},
	{4, 8},
	{4, 4},
	{4, 2},
	{4, 1},
	{2, 4},
	{2, 2},
	{2, 1},
	{1, 4},
	{1, 2},
	{1, 1},
};



//-----------------------------------------------------------------------------
/**
 *					�v���g�^�C�v�錾
*/
//-----------------------------------------------------------------------------
static void cleanFONTOAM_OBJ( FONTOAM_OBJ* fontoam );
static FONTOAM_OBJ* getCleanFONTOAM_OBJ( const FONTOAM_SYSTEM* fontoam_sys );


static int searchOamSize( int x, int y );

static BOOL sumOamArea( FONTOAM_OAM_AREA* oam, FONTOAM_OAM_DATA* list, int heap );
static int getOamData( int x, int y, int heap,  FONTOAM_OAM_DATA* list );

static void charTransOamDataList( const GF_BGL_BMPWIN* bmp, const FONTOAM_OAM_DATA* list, NNSG2dImageProxy* img_proxy, int offs, int draw_area, int heap );
static int charTransOamDataOne( const GF_BGL_BMPWIN* bmp, const FONTOAM_OAM_DATA* oamdata, NNSG2dImageProxy* img_proxy, int char_min_num, int char_mode, int offs, int draw_arae, int heap );

static int charAreaSizeOamDataList( const FONTOAM_OAM_DATA* list, int draw_area );

static void addClActOamDataList( const FONTOAM_INIT* font_init, const FONTOAM_OAM_DATA* list, const NNSG2dImageProxy* img_proxy, FONTOAM_OBJ_PTR font_obj );
static CLACT_WORK_PTR addClActOamDataOne( const FONTOAM_INIT* font_init, const FONTOAM_OAM_DATA* oamdata, const NNSG2dImageProxy* img_proxy );

static void delClActOamDataList( FONTOAM_OBJ_PTR fontoam );

static FONTOAM_OAM_DATA* makeOamList( int heap );
static void destOamList( FONTOAM_OAM_DATA* oamdata );
static void destOamListAll( FONTOAM_OAM_DATA* dummy );
static void setOamList( FONTOAM_OAM_DATA* oamdata, FONTOAM_OAM_DATA* prev );
static void resetOamList( FONTOAM_OAM_DATA* oamdata );


static void charSetOamDataList( const GF_BGL_BMPWIN* bmp, char* pbuff, const FONTOAM_OAM_DATA* list, int draw_area, int heap );
static int charSetOamDataOne( const GF_BGL_BMPWIN* bmp, const FONTOAM_OAM_DATA* oamdata, char* pbuff, int idx, int char_min_num, int char_mode, int heap );


//----------------------------------------------------------------------------
/**
 *
 *	@brief	OAM�t�H���g�V�X�e���̍쐬
 *
 *	@param	workNum		�Ǘ����镶����
 *	@param	heap		�g�p����q�[�v
 *
 *	@return	FONTOAM_SYS_PTR		�쐬����OAM�t�H���g�V�X�e���f�[�^
 *
 *
 */
//-----------------------------------------------------------------------------
FONTOAM_SYS_PTR FONTOAM_SysInit( int workNum, int heap )
{
	FONTOAM_SYS_PTR fntoam_sys;
	int i;			// ���[�v�p
	
	fntoam_sys = sys_AllocMemory( heap, sizeof(FONTOAM_SYSTEM) );
	GF_ASSERT( fntoam_sys );
	

	// OAM�̃Z���f�[�^��ǂݍ���
	for( i=0; i<FONTOAM_PRI_MAX; i++ ){
		fntoam_sys->pCellBuff[ i ] = ArcUtil_CellBankDataGet( 
				ARC_FONTOAM,
				i, FALSE,
				&fntoam_sys->pCellBank[ i ],
				heap );

		GF_ASSERT( fntoam_sys->pCellBuff[ i ] );
	}
	
	// workNum����1OAM�t�H���g�f�[�^���쐬
	fntoam_sys->fontoam_work = sys_AllocMemory( heap, sizeof(FONTOAM_OBJ) * workNum );
	GF_ASSERT( fntoam_sys->fontoam_work );
	fntoam_sys->fontoam_num	= workNum;
	memset( fntoam_sys->fontoam_work, 0, sizeof(FONTOAM_OBJ) * workNum );

	return fntoam_sys;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	OAM�t�H���g�V�X�e���̔j��
 *
 *	@param	fntoam_sys	OAM�t�H���g�V�X�e���f�[�^
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void FONTOAM_SysDelete( FONTOAM_SYS_PTR fntoam_sys )
{
	int i;

	GF_ASSERT( fntoam_sys );
	
	for( i=0; i<FONTOAM_PRI_MAX; i++ ){
		sys_FreeMemoryEz(fntoam_sys->pCellBuff[ i ]);
	}
	sys_FreeMemoryEz( fntoam_sys->fontoam_work );
	sys_FreeMemoryEz( fntoam_sys );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	OAM�t�H���g�쐬
 *
 *	@param	fontoam_init	OAM�t�H���g�쐬�f�[�^
 *
 *	@return	FONTOAM_OBJ_PTR	OAM�t�H���g�f�[�^
 *
 *
 */
//-----------------------------------------------------------------------------
FONTOAM_OBJ_PTR FONTOAM_Init( const FONTOAM_INIT* fontoam_init )
{
	FONTOAM_OBJ_PTR fontoam;
	FONTOAM_OAM_DATA list_dummy;
	int oam_num;
	NNSG2dImageProxy* img_proxy;

	GF_ASSERT( fontoam_init );

	// ��̃e�[�u�����擾
	fontoam = getCleanFONTOAM_OBJ( fontoam_init->fontoam_sys );
	GF_ASSERT_MSG( fontoam, "���OAM�t�H���g�e�[�u��������܂���" );
	fontoam->parent	= fontoam_init->parent;	// �e�f�[�^���

	fontoam->x	= fontoam_init->x;
	fontoam->y	= fontoam_init->y;

	// OAM�f�[�^�쐬
	list_dummy.next = &list_dummy;
	list_dummy.prev = &list_dummy;
	oam_num = getOamData( fontoam_init->bmp->sizx, 
			fontoam_init->bmp->sizy,
			fontoam_init->heap, 
			&list_dummy );

	// oam_num���̃C���[�W�v���N�V�ƁA�Z���A�N�^�[�o�^�̈���쐬
	img_proxy = sys_AllocMemoryLo( fontoam_init->heap,
			sizeof(NNSG2dImageProxy) * oam_num );
	fontoam->obj_w = sys_AllocMemory( fontoam_init->heap,
			sizeof(FONTOAM_OBJ_CORE) * oam_num );
	fontoam->obj_num = oam_num;

	// �L�����N�^�f�[�^�]��
	charTransOamDataList( fontoam_init->bmp, 
			&list_dummy,
			img_proxy,
			fontoam_init->char_ofs,
			fontoam_init->draw_area,
			fontoam_init->heap );

	// �Z���A�N�^�[�o�^
	addClActOamDataList( fontoam_init,
			&list_dummy,
			img_proxy,
			fontoam );

	// �v���N�V�̔j��
	sys_FreeMemoryEz( img_proxy );

	// OAM�f�[�^�j��
	destOamListAll( &list_dummy );

	return fontoam;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	OAM�t�H���g�j��
 *
 *	@param	fontoam 
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void FONTOAM_Delete( FONTOAM_OBJ_PTR fontoam )
{
	GF_ASSERT( fontoam );
	GF_ASSERT( fontoam->obj_w );
	
	delClActOamDataList( fontoam );
	
	sys_FreeMemoryEz( fontoam->obj_w );
	cleanFONTOAM_OBJ( fontoam );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�r�b�g�}�b�v�E�B���h�E��OAM�t�H���g�V�X�e���ŕ\�����邽�߂ɕK�v�ȃL�����N�^�f�[�^�T�C�Y���擾
 *
 *	@param	bmp			�r�b�g�}�b�v�f�[�^
 *	@param	draw_area	�`��G���A
 *	@param	heap		�g�p����q�[�v
 *
 *	@return	�\�����邽�߂ɕK�v�ȃL�����N�^�T�C�Y
 *	
 *	char_manager���g�p���Ă���Ƃ��́A���̃T�C�Y��
 *	���Vram�̈���m�ۂ��Ă����K�v�����邽�ߍ쐬
 *
 *
 */
//-----------------------------------------------------------------------------
int FONTOAM_NeedCharSize( const GF_BGL_BMPWIN* bmp, int draw_area,  int heap )
{
	FONTOAM_OAM_DATA list_dummy;
	int offs;

	// OAM�f�[�^�쐬
	list_dummy.next = &list_dummy;
	list_dummy.prev = &list_dummy;
	getOamData( bmp->sizx, 
			bmp->sizy,
			heap, 
			&list_dummy );

	offs = charAreaSizeOamDataList( &list_dummy, draw_area );

	// OAM�f�[�^�j��
	destOamListAll( &list_dummy );

	return offs;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	OAM�t�H���g���W��ݒ�
 *
 *	@param	fontoam		OAM�t�H���g
 *	@param	x			�����W		�e�A�N�^�[������Ƃ��̓I�t�Z�b�g���W
 *	@param	y			�����W		�e�A�N�^�[������Ƃ��̓I�t�Z�b�g���W
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void FONTOAM_SetMat( FONTOAM_OBJ_PTR fontoam, int x, int y )
{
	int i;		// ���[�v�p
	VecFx32	set_mat;	// �ݒ���W
	const VecFx32* parent_mat;

	GF_ASSERT( fontoam );
	
	fontoam->x = x;
	fontoam->y = y;

	x *= FX32_ONE;
	y *= FX32_ONE;

	// �e������Ƃ��͐e����̃I�t�Z�b�g�ɂȂ�
	if( fontoam->parent ){

		parent_mat = CLACT_GetMatrix( fontoam->parent );

		x += parent_mat->x;
		y += parent_mat->y;
	}
	
		
	set_mat.z = 0;
	// �S�Z���A�N�^�[�ɍ��W��ݒ�
	for(i=0; i<fontoam->obj_num; i++ ){
		set_mat.x = x + (fontoam->obj_w[ i ].x << FX32_SHIFT);
		set_mat.y = y + (fontoam->obj_w[ i ].y << FX32_SHIFT);
		CLACT_SetMatrix( fontoam->obj_w[ i ].clact, &set_mat );
	}
}

//----------------------------------------------------------------------------
/**
 * ���e�Z���A�N�^�[��ݒ肵�Ă��Ȃ��ꍇ�͎g�p���Ă��Ӗ�������܂���B
 *	
 *	@brief	�e�A�N�^�[�̍��W�ʒu�Ɉʒu�����킹��
 *
 *	@param	fontoam 
 *
 *	@return
 *
 * ���e�Z���A�N�^�[�̈ʒu��ύX�����Ƃ��ɌĂ�ł��������B
 *	�@�e�ɍ��킹�ĕ����������܂�
 *
 */
//-----------------------------------------------------------------------------
void FONTOAM_ReflectParentMat( FONTOAM_OBJ_PTR fontoam )
{
	int i;		// ���[�v�p
	VecFx32	set_mat;	// �ݒ���W
	const VecFx32* parent_mat;
	fx32 x, y;

	GF_ASSERT( fontoam );

	// �e������Ƃ��͐e����̃I�t�Z�b�g�ɂȂ�
	if( fontoam->parent ){
		
		x = fontoam->x << FX32_SHIFT;
		y = fontoam->y << FX32_SHIFT;

		parent_mat = CLACT_GetMatrix( fontoam->parent );

		x += parent_mat->x;
		y += parent_mat->y;
			
		set_mat.z = 0;
		// �S�Z���A�N�^�[�ɍ��W��ݒ�
		for(i=0; i<fontoam->obj_num; i++ ){
			set_mat.x = x + (fontoam->obj_w[ i ].x << FX32_SHIFT);
			set_mat.y = y + (fontoam->obj_w[ i ].y << FX32_SHIFT);
			CLACT_SetMatrix( fontoam->obj_w[ i ].clact, &set_mat );
		}
	}
}


//----------------------------------------------------------------------------
/**
 *
 *	@brief	OAM�t�H���g���W���擾
 *
 *	@param	fontoam		OAM�t�H���g
 *	@param	x			�����W		�e�A�N�^�[������Ƃ��̓I�t�Z�b�g���W
 *	@param	y			�����W		�e�A�N�^�[������Ƃ��̓I�t�Z�b�g���W
 *
 *	@return
 *
 *
 */
//-----------------------------------------------------------------------------
void FONTOAM_GetMat( CONST_FONTOAM_OBJ_PTR fontoam, int* x, int* y )
{
	GF_ASSERT( fontoam );
	GF_ASSERT( x );
	GF_ASSERT( y );

	*x = fontoam->x;
	*y = fontoam->y;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�\��/��\���ݒ�
 *
 *	@param	fontoam		OAM�t�H���g�I�u�W�F
 *	@param	flag		�\��/��\���t���O
 *
 *	@return	none
 *
 * flag
 *	TRUE	�\��
 *	FALSE	��\��
 *
 */
//-----------------------------------------------------------------------------
void FONTOAM_SetDrawFlag( FONTOAM_OBJ_PTR fontoam, BOOL flag )
{
	int i;		// ���[�v�p

	GF_ASSERT( fontoam );
	// �S�Z���A�N�^�[�ɍ��W��ݒ�
	for(i=0; i<fontoam->obj_num; i++ ){

		CLACT_SetDrawFlag( fontoam->obj_w[ i ].clact, flag );
	}
}


//----------------------------------------------------------------------------
/**
 *
 *	@brief	�\��/��\�����擾
 *
 *	@param	fontoam		OAM�t�H���g�I�u�W�F
 *
 *	@retval	TRUE	�\����
 *	@retval	FALSE	��\����
 *
 *
 */
//-----------------------------------------------------------------------------
BOOL FONTOAM_GetDrawFlag( CONST_FONTOAM_OBJ_PTR fontoam )
{
	GF_ASSERT( fontoam );
	
	return CLACT_GetDrawFlag( fontoam->obj_w[0].clact );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	BG�ʂƂ̗D�揇�ʂ�ݒ�
 *
 *	@param	fontoam	OAM�t�H���g�f�[�^
 *	@param	pri		BG�Ƃ̗D�揇��
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void FONTOAM_SetBGPriority( FONTOAM_OBJ_PTR fontoam, u8 pri )
{
	int i;		// ���[�v�p

	GF_ASSERT( fontoam );
	// �S�Z���A�N�^�[�ɍ��W��ݒ�
	for(i=0; i<fontoam->obj_num; i++ ){

		CLACT_BGPriorityChg( fontoam->obj_w[ i ].clact, pri );
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	BG�ʂƂ̕`��D�揇�ʂ��擾
 *
 *	@param	fontoam		OAM�t�H���g�I�u�W�F
 *
 *	@return	BG�ʂƂ̗D�揇��
 *
 *
 */
//-----------------------------------------------------------------------------
int FONTOAM_GetBGPriority( CONST_FONTOAM_OBJ_PTR fontoam )
{
	GF_ASSERT( fontoam );
	
	return CLACT_BGPriorityGet( fontoam->obj_w[0].clact );
}

//-----------------------------------------------------------------------------
/**
 *	@brief	�`��D�揇�ʂ�ݒ�
 *
 *	@param	fontoam		OAM�t�H���g�f�[�^
 *	@param	pri			�\���D�揇��
 *				
 * 
 *	@return	none
 */
 //----------------------------------------------------------------------------
void FONTOAM_SetDrawPriority( FONTOAM_OBJ_PTR fontoam, u32 pri )
{
	int i;		// ���[�v�p

	GF_ASSERT( fontoam );
	// �S�Z���A�N�^�[�ɍ��W��ݒ�
	for(i=0; i<fontoam->obj_num; i++ ){

		CLACT_DrawPriorityChg( fontoam->obj_w[ i ].clact, pri );
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�`��D�揇�ʂ��擾
 *
 *	@param	fontoam		OAM�t�H���g�I�u�W�F
 *
 *	@return	u32			�`��D�揇��
 *
 *
 */
//-----------------------------------------------------------------------------
u32 FONTOAM_GetDrawPriority( CONST_FONTOAM_OBJ_PTR fontoam )
{
	GF_ASSERT( fontoam );
	
	return CLACT_DrawPriorityGet( fontoam->obj_w[0].clact );
}

//-----------------------------------------------------------------------------
/**
 * ��OAM�����̃p���b�g�i���o�[������悤�ɂȂ�܂��B
 *
 *	@brief				�p���b�g�i���o�[��ύX
 *
 *	@param	fontoam		OAM�t�H���g�I�u�W�F
 *	@param	pltt_no		�ݒ�p���b�g�i���o�[
 * 
 *	@return	none
 *
 * ���p���b�g�i���o�[�ݒ�ƃp���b�g�I�t�Z�b�g�ݒ�͓������܂���B
 *�@�@���p���b�g�i���o�[��ݒ肷��ƃI�t�Z�b�g�̒l�͔��f����Ȃ��Ȃ�܂��B
 *	�@���I�t�Z�b�g�l��ݒ肵���Ƃ��̓p���b�g�i���o�[�����f����Ȃ��Ȃ�܂��B
 * 
 */
 //----------------------------------------------------------------------------
void FONTOAM_SetPaletteNo( FONTOAM_OBJ_PTR fontoam, u32 pltt_no )
{
	int i;		// ���[�v�p

	GF_ASSERT( fontoam );
	// �S�Z���A�N�^�[�ɍ��W��ݒ�
	for(i=0; i<fontoam->obj_num; i++ ){

		CLACT_PaletteNoChg( fontoam->obj_w[ i ].clact, pltt_no );
	}
}
void FONTOAM_SetPaletteNoAddTransPlttNo( FONTOAM_OBJ_PTR fontoam, u32 pltt_no )
{
	int i;		// ���[�v�p

	GF_ASSERT( fontoam );
	// �S�Z���A�N�^�[�ɍ��W��ݒ�
	for(i=0; i<fontoam->obj_num; i++ ){

		CLACT_PaletteNoChgAddTransPlttNo( fontoam->obj_w[ i ].clact, pltt_no );
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�p���b�g�i���o�[�擾
 *
 *	@param	fontoam		OAM�t�H���g�I�u�W�F
 *
 *	@return	u32			���̃p���b�g�i���o�[
 *
 *
 */
//-----------------------------------------------------------------------------
u32 FONTOAM_GetPaletteNo( CONST_FONTOAM_OBJ_PTR fontoam )
{
	GF_ASSERT( fontoam );
	
	return CLACT_PaletteNoGet( fontoam->obj_w[0].clact );
}

//-----------------------------------------------------------------------------
/**
 * ��OAM�A�g���r���[�g�ɐݒ肳��Ă���p���b�g�i���o�[�ɉ��Z����܂��B
 *	 �����AOAM�A�g���r���[�g�̃J���[�p���b�gNo���Q�ŃI�t�Z�b�g�ɂQ��
 *	 �ݒ肷��ƁA�S�̃J���[�p���b�g���Q�Ƃ���悤�ɂȂ�܂�
 * 
 *	@brief	�p���b�g�I�t�Z�b�g��ݒ�
 *
 *	@param	fontoam		OAM�t�H���g�I�u�W�F
 *	@param	pltt_ofs	�p���b�g�I�t�Z�b�g
 * 
 *	@return	none
 *
 * ���p���b�g�i���o�[�ݒ�ƃp���b�g�I�t�Z�b�g�ݒ�͓������܂���B
 *�@�@���p���b�g�i���o�[��ݒ肷��ƃI�t�Z�b�g�̒l�͔��f����Ȃ��Ȃ�܂��B
 *	�@���I�t�Z�b�g�l��ݒ肵���Ƃ��̓p���b�g�i���o�[�����f����Ȃ��Ȃ�܂��B
 * 
 */
 //----------------------------------------------------------------------------
void FONTOAM_SetPaletteOffset( FONTOAM_OBJ_PTR fontoam, u32 pltt_ofs )
{
	int i;		// ���[�v�p

	GF_ASSERT( fontoam );
	// �S�Z���A�N�^�[�ɍ��W��ݒ�
	for(i=0; i<fontoam->obj_num; i++ ){

		CLACT_PaletteOffsetChg( fontoam->obj_w[ i ].clact, pltt_ofs );
	}
}
void FONTOAM_SetPaletteOffsetAddTransPlttNo( FONTOAM_OBJ_PTR fontoam, u32 pltt_ofs )
{
	int i;		// ���[�v�p

	GF_ASSERT( fontoam );
	// �S�Z���A�N�^�[�ɍ��W��ݒ�
	for(i=0; i<fontoam->obj_num; i++ ){

		CLACT_PaletteOffsetChgAddTransPlttNo( fontoam->obj_w[ i ].clact, pltt_ofs );
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�p���b�g�I�t�Z�b�g�l�擾
 *
 *	@param	fontoam	OAM�t�H���g�I�u�W�F
 *
 *	@return	u32		���̃p���b�g�I�t�Z�b�g�l
 *
 */
//-----------------------------------------------------------------------------
u32 FONTOAM_GetPaletteOffset( CONST_FONTOAM_OBJ_PTR fontoam )
{
	GF_ASSERT( fontoam );
	
	return CLACT_PaletteOffsetGet( fontoam->obj_w[0].clact );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	���U�C�N�ݒ�
 *
 *	@param	fontoam	OAM�t�H���g�I�u�W�F
 *	@param	flag	�t���O	TRUE�����U�C�NON	FALSE�����U�C�NOFF
 *
 *	@return	none
 *
 * ���U�C�NOFF�̎��ł��A�j�g���L�����N�^�Ń��U�C�NON�ɂ���OAM��
 * ���U�C�N���������ĕ`�悳��܂��B
 *
 */
//-----------------------------------------------------------------------------
void FONTOAM_SetMosaic( FONTOAM_OBJ_PTR fontoam, BOOL flag )
{
	int i;		// ���[�v�p

	GF_ASSERT( fontoam );
	// �S�Z���A�N�^�[�ɍ��W��ݒ�
	for(i=0; i<fontoam->obj_num; i++ ){

		CLACT_MosaicSet( fontoam->obj_w[ i ].clact, flag );
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	���U�C�N�ݒ��Ԃ��擾
 *
 *	@param	fontoam	OAM�t�H���g�I�u�W�F
 *
 *	@retval	TRUE	���U�C�N��ON
 *	@retval	FALSE	���U�C�N��OFF	�i�j�g���L�����N�^�Őݒ肵�Ă�Ƃ��͔��f�����j
 *
 *
 */
//-----------------------------------------------------------------------------
BOOL FONTOAM_GetMosaic( CONST_FONTOAM_OBJ_PTR fontoam )
{
	GF_ASSERT( fontoam );
	
	return CLACT_MosaicGet( fontoam->obj_w[0].clact );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�I�u�W�F�N�g���[�h�̐ݒ�
 *
 *	@param	fontoam		�t�H���gOAM
 *	@param	objmode		�I�u�W�F���[�h
 *
 *	@return	none
 *
	GX_OAM_MODE_NORMAL		�m�[�}��OBJ 
	GX_OAM_MODE_XLU			������OBJ 
	GX_OAM_MODE_OBJWND		OBJ�E�B���h�E 
	GX_OAM_MODE_BITMAPOBJ	�r�b�g�}�b�vOBJ 
 */
//-----------------------------------------------------------------------------
void FONTOAM_ObjModeSet( FONTOAM_OBJ_PTR fontoam, GXOamMode objmode )
{
	int i;		// ���[�v�p

	GF_ASSERT( fontoam );
	// �S�Z���A�N�^�[�ɍ��W��ݒ�
	for(i=0; i<fontoam->obj_num; i++ ){

		CLACT_ObjModeSet( fontoam->obj_w[ i ].clact, objmode );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�I�u�W�F���[�h�̎擾
 *
 *	@param	fontoam		FONTOAM
 *	@param	objmode		�I�u�W�F���[�h
 *
 *	@retval	GX_OAM_MODE_NORMAL		�m�[�}��OBJ 
 *	@retval	GX_OAM_MODE_XLU			������OBJ 
 *	@retval	GX_OAM_MODE_OBJWND		OBJ�E�B���h�E 
 *	@retval	GX_OAM_MODE_BITMAPOBJ	�r�b�g�}�b�vOBJ 
 */
//-----------------------------------------------------------------------------
GXOamMode FONTOAM_ObjModeGet( CONST_FONTOAM_OBJ_PTR fontoam, GXOamMode objmode )
{
	GF_ASSERT( fontoam );
	
	return CLACT_ObjModeGet( fontoam->obj_w[0].clact );
}



//-----------------------------------------------------------------------------
/**
 *		FONTOAM	�ׂ���������o�[�W����
 */
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *	@brief	�t�H���gOAM�����f�[�^�쐬
 *
 *	@param	bmp		�f�[�^�쐬���r�b�g�}�b�v
 *	@param	heap	�q�[�v
 *
 *	@return	�����f�[�^
 */
//-----------------------------------------------------------------------------
FONTOAM_OAM_DATA_PTR FONTOAM_OAMDATA_Make( const GF_BGL_BMPWIN* bmp, int heap )
{
	FONTOAM_OAM_DATA_PTR fontoam_data;

	fontoam_data = sys_AllocMemory( heap, sizeof(FONTOAM_OAM_DATA_SET) );
	fontoam_data->fontoamdata.next = &fontoam_data->fontoamdata;
	fontoam_data->fontoamdata.prev = &fontoam_data->fontoamdata;

	// OAM�f�[�^�쐬
	fontoam_data->data_num = getOamData( bmp->sizx, 
			bmp->sizy,
			heap, 
			&fontoam_data->fontoamdata );

	return fontoam_data;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�t�H���gOAM�����f�[�^�̔j��
 *
 *	@param	oamdata	�t�H���gOAM�����f�[�^
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void FONTOAM_OAMDATA_Free( FONTOAM_OAM_DATA_PTR oamdata )
{
	// OAM�f�[�^�j��
	destOamListAll( &oamdata->fontoamdata );

	sys_FreeMemoryEz( oamdata );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�t�H���gOAM�����f�[�^����]���ɕK�v���L�����N�^�T�C�Y���擾
 *
 *	@param	oamdata		�t�H���gOAM�����f�[�^
 *	@param	draw_area	�`��G���A
 *
 *	@return	�K�v���L�����N�^�T�C�Y
 */
//-----------------------------------------------------------------------------
int FONTOAM_OAMDATA_NeedCharSize( CONST_FONTOAM_OAM_DATA_PTR oamdata, int draw_area )
{
	return charAreaSizeOamDataList( &oamdata->fontoamdata, draw_area );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�t�H���gOAM�����f�[�^���g�p���ăt�H���gOAM�̍쐬
 *
 *	@param	fontoam_init		�ӂ����OAM �쐬�f�[�^
 *	@param	oamdata				OAM�����f�[�^
 *
 *	@return	�쐬���ꂽ�t�H���gOAM
 */
//-----------------------------------------------------------------------------
FONTOAM_OBJ_PTR FONTOAM_OAMDATA_Init( const FONTOAM_INIT* fontoam_init, CONST_FONTOAM_OAM_DATA_PTR oamdata )
{
	FONTOAM_OBJ_PTR fontoam;
	NNSG2dImageProxy* img_proxy;

	GF_ASSERT( fontoam_init );

	// ��̃e�[�u�����擾
	fontoam = getCleanFONTOAM_OBJ( fontoam_init->fontoam_sys );
	GF_ASSERT_MSG( fontoam, "���OAM�t�H���g�e�[�u��������܂���" );
	fontoam->parent	= fontoam_init->parent;	// �e�f�[�^���

	fontoam->x	= fontoam_init->x;
	fontoam->y	= fontoam_init->y;

	// oam_num���̃C���[�W�v���N�V�ƁA�Z���A�N�^�[�o�^�̈���쐬
	img_proxy = sys_AllocMemoryLo( fontoam_init->heap,
			sizeof(NNSG2dImageProxy) * oamdata->data_num );
	fontoam->obj_w = sys_AllocMemory( fontoam_init->heap,
			sizeof(FONTOAM_OBJ_CORE) * oamdata->data_num );
	fontoam->obj_num = oamdata->data_num;

	// �L�����N�^�f�[�^�]��
	charTransOamDataList( fontoam_init->bmp, 
			&oamdata->fontoamdata,
			img_proxy,
			fontoam_init->char_ofs,
			fontoam_init->draw_area,
			fontoam_init->heap );

	// �Z���A�N�^�[�o�^
	addClActOamDataList( fontoam_init,
			&oamdata->fontoamdata,
			img_proxy,
			fontoam );

	// �v���N�V�̔j��
	sys_FreeMemoryEz( img_proxy );

	return fontoam;
}

//----------------------------------------------------------------------------
/**
 *	@brief	OAM�t�H���g�j��
 *
 *	@param	fontoam 
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void FONTOAM_OAMDATA_Delete( FONTOAM_OBJ_PTR fontoam )
{
	FONTOAM_Delete( fontoam );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�t�H���gOAM�̃r�b�g�}�b�v�f�[�^��ύX����
 *
 *	@param	fontoam		�ύX����FONTOAM
 *	@param	oamdata		OAM�����f�[�^
 *	@param	bmp			�r�b�g�}�b�v 
 *	@param	heap		�q�[�v
 *
 *	@return	none
 *
 *	�����ӓ_
 *		�r�b�g�}�b�v�̑傫�����������K�v������܂��B
 */
//-----------------------------------------------------------------------------
void FONTOAM_OAMDATA_ResetBmp( FONTOAM_OBJ_PTR fontoam, CONST_FONTOAM_OAM_DATA_PTR oamdata, const GF_BGL_BMPWIN* bmp, int heap )
{
	int need_char;
	char* pbuff;
	NNSG2dImageProxy* p_prox;
	CLACT_WORK_PTR start_act = fontoam->obj_w[0].clact;
	int draw_area;

	// �`��G���A
	draw_area = CLACT_VramTypeGet( start_act );


	// �K�v�L�����N�^�o�b�t�@�쐬
	need_char = FONTOAM_OAMDATA_NeedCharSize( oamdata, draw_area );

	// �L�����N�^�o�b�t�@�쐬
	pbuff = (char*)sys_AllocMemoryLo( heap, need_char );
	memset( pbuff, 0, need_char );

	// �]���L�����N�^�f�[�^�쐬
	charSetOamDataList( bmp, pbuff, &oamdata->fontoamdata, draw_area, heap );

    DC_FlushRange(pbuff, need_char);

	// Vram�ɓ]��
	p_prox = CLACT_ImageProxyGet( start_act );
	if( draw_area == NNS_G2D_VRAM_TYPE_2DMAIN ){
		GX_LoadOBJ( pbuff, NNS_G2dGetImageLocation(	p_prox, NNS_G2D_VRAM_TYPE_2DMAIN ), need_char );	
	}else{
		GXS_LoadOBJ( pbuff, NNS_G2dGetImageLocation(	p_prox, NNS_G2D_VRAM_TYPE_2DSUB ), need_char );	
	}

	// �L�����N�^�o�b�t�@�j��
	sys_FreeMemoryEz( pbuff );
}



//-----------------------------------------------------------------------------
/**
 *		FONTOAM�Ƃ͖��֌W�ł����A�ėp�I�Ɏg�p�ł���֐�
 */
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *
 *	@brief	BMP�̃L�����N�^�f�[�^��OAM�̃T�C�Y�Ő؂���
 *
 *	@param	bmp				�r�b�g�}�b�v�f�[�^
 *	@param	oam_csx			OAM�̉��T�C�Y	�i�L�����N�^�P�ʁj
 *	@param	oam_csy			OAM�̏c�T�C�Y	�i�L�����N�^�P�ʁj
 *	@param	bmp_cmx			�r�b�g�}�b�v�؂��荶�゘���W	�i�L�����N�^�P�ʁj
 *	@param	bmp_cmy			�r�b�g�}�b�v�؂��荶�゙���W	�i�L�����N�^�P�ʁj
 *	@param	char_buff		�o�͐�L�����N�^�o�b�t�@ (oam_csx * oam_csy)*32byte�@�T�C�Y�ȏ�̗̈�
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void FONTOAM_BmpCutOamSize( const GF_BGL_BMPWIN* cp_bmp, int oam_csx, int oam_csy, int bmp_cmx, int bmp_cmy, char* char_buff )
{
	int i;				// ���[�v�p
	int buff_out;		// �o�b�t�@�������ݐ�
	int buff_in;		// �o�b�t�@�ǂݍ��ݐ�
	
	// bmp�f�[�^�̃T�C�Y������邩�`�F�b�N
	GF_ASSERT( cp_bmp->sizx >= (oam_csx + bmp_cmx) );
	GF_ASSERT( cp_bmp->sizy >= (oam_csy + bmp_cmy) );
	
	// ���[�J���o�b�t�@�Ƀf�[�^���
	for( i=0; i<oam_csy; i++ ){
		
		buff_out = i * oam_csx;
		buff_out *= FONTOAM_CHAR_BYTE;
		buff_in =  ((i + bmp_cmy) * cp_bmp->sizx);
		buff_in += bmp_cmx;
		buff_in *= FONTOAM_CHAR_BYTE;
		memcpy( char_buff + buff_out, (char*)(cp_bmp->chrbuf) + buff_in , FONTOAM_CHAR_BYTE * oam_csx );
	}
}

//-----------------------------------------------------------------------------
/**
*		�v���C�x�[�g�֐�
*/
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *
 *	@brief	�e�[�u����������
 *
 *	@param	fontoam		OAM�t�H���g
 *	
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void cleanFONTOAM_OBJ( FONTOAM_OBJ* fontoam )
{
	memset( fontoam, 0, sizeof(FONTOAM_OBJ) );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	��̃e�[�u�����擾
 *
 *	@param	fontoam_sys		OAM�t�H���g�V�X�e��
 *
 *	@return	FONTOAM_OBJ*	OAM�t�H���g
 *
 *
 */
//-----------------------------------------------------------------------------
static FONTOAM_OBJ* getCleanFONTOAM_OBJ( const FONTOAM_SYSTEM* fontoam_sys )
{
	int i;		// ���[�v�p

	for( i=0; i<fontoam_sys->fontoam_num; i++ ){

		if( fontoam_sys->fontoam_work[ i ].obj_w == NULL ){
			return fontoam_sys->fontoam_work  + i;
		}
	}


	return NULL;
}




//----------------------------------------------------------------------------
/**
 *
 *	@brief	���ƍ�������œK��OAM�T�C�Y���擾����
 *
 *	@param	x		��		�L�����N�^�P��
 *	@param	y		����	�L�����N�^�P��
 *
 *		
 *	@retval		FONTOAM_PRI_8x8 = 0,	
 * 	@retval		FONTOAM_PRI_8x4,
 *	@retval		FONTOAM_PRI_4x8,
 *	@retval		FONTOAM_PRI_4x4,
 *	@retval		FONTOAM_PRI_4x2,
 *	@retval		FONTOAM_PRI_4x1,
 *	@retval		FONTOAM_PRI_2x4,
 *	@retval		FONTOAM_PRI_2x2,
 *	@retval		FONTOAM_PRI_2x1,
 *	@retval		FONTOAM_PRI_1x4,
 *	@retval		FONTOAM_PRI_1x2,
 *	@retval		FONTOAM_PRI_1x1,
 *
 */
//-----------------------------------------------------------------------------
static int searchOamSize( int x, int y )
{
	int i;	// ���[�v�p

	for( i = 0; i < FONTOAM_PRI_MAX; i++ ){
		
		// ���������肫��l���`�F�b�N
		if( (FONTOAM_PriTbl[ i ][ FONTOAM_PRI_X ] <= x) &&
			(FONTOAM_PriTbl[ i ][ FONTOAM_PRI_Y ] <= y) ){
			return i;
		}
	}

	return FONTOAM_PRI_MAX;		//<-�����ɗ��邱�Ƃ͂Ȃ�
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	OAM���ߐs�����f�[�^�쐬
 *
 *	@param	oam		�G���A�f�[�^
 *	@param	list	���X�g�擪�_�~�[�f�[�^
 *	@param	heap	�g�p����q�[�v
 *
 *	@retval	TRUE	���ߐs�����f�[�^����
 *	@retval FALSE	���ߐs�����f�[�^�쐬��
 *
 * �����ɓn���Ă���l�̍�����8�L�����@4�L���� 2�L���� 1�L�����̂����ꂩ
 * �ɂ��Ă��������B
 * 
 *
 */
//-----------------------------------------------------------------------------
static BOOL sumOamArea( FONTOAM_OAM_AREA* oam, FONTOAM_OAM_DATA* list, int heap )
{
	FONTOAM_OAM_DATA* oam_data;
	int rest_height;	// ���܂荂��
	int rest_width;		// ���܂蕝

	
	// OAM�f�[�^�������m��
	oam_data = makeOamList( heap );
	setOamList( oam_data, list->prev );		// �Ō���ɓo�^
	
	// �T�C�Y����OAM�T�C�Y���擾
	oam_data->oam_size = searchOamSize( oam->now.width, oam->now.height );

	// ���̈ʒu��ݒ�
	oam_data->x = oam->now.left;
	oam_data->y = oam->now.top;

	// ����OAM���ߐs�����G���A���疄�߂�OAM�T�C�Y�����炷
	rest_width	= oam->now.width - FONTOAM_PriTbl[ oam_data->oam_size ][ FONTOAM_PRI_X ];
	rest_height = oam->now.height - FONTOAM_PriTbl[ oam_data->oam_size ][ FONTOAM_PRI_Y ];

	// ���ɂ��܂肪����Ƃ���
	// �c�ɂ͂��܂肪�Ȃ��͂�
	if( rest_width > 0 ){
		oam->right.height	= oam->now.height;
		oam->right.width	= rest_width;
		oam->right.top		= oam->now.top;
		oam->right.left		= oam->now.left + FONTOAM_PriTbl[ oam_data->oam_size ][ FONTOAM_PRI_X ];

		GF_ASSERT( (oam->tmp_flg != FONTOAM_OAM_AREA_RIGHT) );
		oam->tmp_flg = FONTOAM_OAM_AREA_RIGHT;
	}

	// �����ɂ��܂肪����Ƃ��́A���ɂ͂��܂�͂Ȃ�
	// �������܂�̂���Ƃ��͍��G���A���Đݒ�
	// �����ɂ��܂�̖����Ƃ��͉E�G���A�����G���A�ɂ���
	if( rest_height > 0 ){
		oam->now.top = oam->now.top + FONTOAM_PriTbl[ oam_data->oam_size ][ FONTOAM_PRI_Y ];
		oam->now.height = rest_height;
	}else{
		

		// �E�����邩�`�F�b�N
		if( oam->tmp_flg == FONTOAM_OAM_AREA_RIGHT ){
			oam->now = oam->right;
			oam->tmp_flg = FONTOAM_OAM_AREA_NONE;
		}else{
			// �I���
			return TRUE;
		}
	}

	return FALSE;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�f�[�^�������o��OAM�̃f�[�^���쐬����
 *
 *	@param	x		OAM�����o���r�b�g�}�b�v���T�C�Y
 *	@param	y		OAM�����o���r�b�g�}�b�v���T�C�Y
 *	@param	heap	�g�p����q�[�v
 *	@param	list	OAM�f�[�^���X�g�擪�f�[�^
 *
 *	@return	�K�v�Z���A�N�^�[��
 *
 *
 */
//-----------------------------------------------------------------------------
static int getOamData( int x, int y, int heap,  FONTOAM_OAM_DATA* list )
{
	FONTOAM_OAM_AREA_ONE next_area;		// ���`�F�b�N����G���A
	FONTOAM_OAM_AREA	now_area;		// ������`�F�b�N����G���A
	int in_oam_size;					// �G���A�ɓ���OAM�T�C�Y
	int count;							// �K�v�Z���A�N�^�[��
	
	// �T�C�Y�O�`�F�b�N
	GF_ASSERT( x );
	GF_ASSERT( y );

	count = 0;
	now_area.now.top	= 0;
	now_area.now.left	= 0;
	now_area.now.width	= x;
	now_area.now.height	= y;
	now_area.tmp_flg	= FONTOAM_OAM_AREA_NONE;
	next_area.left		= 0;
	next_area.width		= x;
	
	// �G���A��񂪂������
	while( now_area.now.height != 0 ){

		// ���̃G���A�̍�������`�F�b�N����G���A�̍���������
		in_oam_size			= searchOamSize( now_area.now.width, now_area.now.height );
		next_area.top		= now_area.now.top + FONTOAM_PriTbl[ in_oam_size ][ FONTOAM_PRI_Y ];
		next_area.height	= now_area.now.height - FONTOAM_PriTbl[ in_oam_size ][ FONTOAM_PRI_Y ];
		now_area.now.height = FONTOAM_PriTbl[ in_oam_size ][ FONTOAM_PRI_Y ];

		// ����OAM���쐬
		do{
			count ++;
		}while( sumOamArea( &now_area, list, heap ) == FALSE );

		// next��now�ɑ��
		now_area.now = next_area;
	}

	return count;
}


//----------------------------------------------------------------------------
/**
 *	
 *	@brief	OAM�f�[�^���X�g���̃L�����N�^�f�[�^��]�����A�C���[�W�v���N�V���쐬
 *
 *	@param	bmp			�r�b�g�}�b�v�E�B���h�E�f�[�^
 *	@param	list		OAM�f�[�^���X�g
 *	@param	img_proxy	�C���[�W�v���N�V
 *	@param	offs		�I�t�Z�b�g�l
 *	@param	draw_area	�`���
 *	@param	heap		�g�p����q�[�v
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void charTransOamDataList( const GF_BGL_BMPWIN* bmp, const FONTOAM_OAM_DATA* list, NNSG2dImageProxy* img_proxy, int offs, int draw_area, int heap )
{
	FONTOAM_OAM_DATA* work;
	int count;		// �J�E���^
	int char_min;	// �L�����N�^�f�[�^�̍ŏ��P��
	GXOBJVRamModeChar  map_mode;
	
	// �L�����N�^�f�[�^�̍ŏ��P�ʂ��v�Z
	if( draw_area == NNS_G2D_VRAM_TYPE_2DMAIN ){
		map_mode = GX_GetOBJVRamModeChar();
	}else{
		map_mode = GXS_GetOBJVRamModeChar();
	}
	char_min = CharModeMinNum( map_mode );

	count = 0;
	work = list->next;
	while( work != list ){

		NNS_G2dInitImageProxy( img_proxy + count );
		offs = charTransOamDataOne( bmp, work, img_proxy + count, char_min, map_mode, offs, draw_area, heap );
		work = work->next;
		count++;
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	OAM�f�[�^�P���̃L�����N�^�f�[�^���쐬���A�]��
 *
 *	@param	bmp			�r�b�g�}�b�v�E�B���h�E�f�[�^
 *	@param	oamdata		OAM�f�[�^
 *	@param	img_proxy	�ݒ�C���[�W�v���N�V
 *	@param	char_min_num�L�����N�^���[�h�Őݒ肳��Ă���Œ�̃L�����N�^�T�C�Y
 *	@param	char_mode	�}�b�s���O���[�h
 *	@param	offs		�I�t�Z�b�g�l
 *	@param	draw_area	�`���
 *	@param	heap		�g�p����q�[�v
 *
 *	@return	�]�����������炵���I�t�Z�b�g
 *
 *
 */
//-----------------------------------------------------------------------------
static int charTransOamDataOne( const GF_BGL_BMPWIN* bmp, const FONTOAM_OAM_DATA* oamdata, NNSG2dImageProxy* img_proxy, int char_min_num, int char_mode, int offs, int draw_arae, int heap )
{
	char* local_buff;		// OAM�P���̃L�����N�^�f�[�^
	int buff_size;
	int oam_x, oam_y;	// oam�T�C�Y

	oam_x = FONTOAM_PriTbl[ oamdata->oam_size ][ FONTOAM_PRI_X ];
	oam_y = FONTOAM_PriTbl[ oamdata->oam_size ][ FONTOAM_PRI_Y ]; 
	
	// oam�T�C�Y����L�����N�^�f�[�^�o�b�t�@���쐬
	buff_size =  oam_x;
	buff_size *= oam_y;
	if( buff_size < char_min_num ){
		buff_size = char_min_num;
	}
	buff_size *= FONTOAM_CHAR_BYTE;
	local_buff = sys_AllocMemoryLo( heap, buff_size );
	
	// ���[�J���o�b�t�@�Ƀf�[�^���
	FONTOAM_BmpCutOamSize( bmp, oam_x, oam_y, oamdata->x, oamdata->y, local_buff );

    DC_FlushRange(local_buff, buff_size);

	
	// �]��
	if( draw_arae == NNS_G2D_VRAM_TYPE_2DMAIN ){
		GX_LoadOBJ( local_buff, offs, buff_size );	
		img_proxy->vramLocation.baseAddrOfVram[ NNS_G2D_VRAM_TYPE_2DMAIN ] = offs;
		img_proxy->attr.mappingType = GX_GetOBJVRamModeChar();	  // ���C��
	}else{
		GXS_LoadOBJ( local_buff, offs, buff_size );	
		img_proxy->vramLocation.baseAddrOfVram[ NNS_G2D_VRAM_TYPE_2DSUB ] = offs;
		img_proxy->attr.mappingType = GXS_GetOBJVRamModeChar();   // �T�u
	}
	img_proxy->attr.sizeS         = NNS_G2D_1D_MAPPING_CHAR_SIZE;
    img_proxy->attr.sizeT         = NNS_G2D_1D_MAPPING_CHAR_SIZE;
    img_proxy->attr.fmt           = GX_TEXFMT_PLTT16;
    img_proxy->attr.bExtendedPlt  = FALSE;                
    img_proxy->attr.plttUse       = GX_TEXPLTTCOLOR0_TRNS;
    img_proxy->attr.mappingType   = char_mode;

	sys_FreeMemoryEz( local_buff );

	return (offs + buff_size);
}

//----------------------------------------------------------------------------
/**
 *	
 *	@brief	OAM�f�[�^���X�g���̃L�����N�^�f�[�^���쐬
 *
 *	@param	bmp			�r�b�g�}�b�v�E�B���h�E�f�[�^
 *	@param	pbuff		�L�����N�^�f�[�^�o�b�t�@
 *	@param	list		OAM�f�[�^���X�g
 *	@param	draw_area	�`��G���A
 *	@param	heap		�g�p����q�[�v
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void charSetOamDataList( const GF_BGL_BMPWIN* bmp, char* pbuff, const FONTOAM_OAM_DATA* list, int draw_area, int heap )
{
	FONTOAM_OAM_DATA* work;
	int count;		// �J�E���^
	int char_min;	// �L�����N�^�f�[�^�̍ŏ��P��
	int offs;
	GXOBJVRamModeChar  map_mode;
	
	// �L�����N�^�f�[�^�̍ŏ��P�ʂ��v�Z
	if( draw_area == NNS_G2D_VRAM_TYPE_2DMAIN ){
		map_mode = GX_GetOBJVRamModeChar();
	}else{
		map_mode = GXS_GetOBJVRamModeChar();
	}
	char_min = CharModeMinNum( map_mode );

	offs = 0;
	work = list->next;
	while( work != list ){

		offs = charSetOamDataOne( bmp, work, pbuff, offs, char_min, map_mode, heap );
		work = work->next;
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	OAM�f�[�^�P���̃L�����N�^�f�[�^���쐬
 *
 *	@param	bmp			�r�b�g�}�b�v�E�B���h�E�f�[�^
 *	@param	oamdata		OAM�f�[�^
 *	@param	pbuff		�L�����N�^�o�b�t�@
 *	@param	idx			�C���f�b�N�X
 *	@param	char_min_num�L�����N�^���[�h�Őݒ肳��Ă���Œ�̃L�����N�^�T�C�Y
 *	@param	char_mode	�}�b�s���O���[�h
 *	@param	heap		�g�p����q�[�v
 *
 *	@return	idx	���̊i�[��C���f�b�N�X
 *
 *
 */
//-----------------------------------------------------------------------------
static int charSetOamDataOne( const GF_BGL_BMPWIN* bmp, const FONTOAM_OAM_DATA* oamdata, char* pbuff, int idx, int char_min_num, int char_mode, int heap )
{
	int buff_size;
	int oam_x, oam_y;	// oam�T�C�Y

	oam_x = FONTOAM_PriTbl[ oamdata->oam_size ][ FONTOAM_PRI_X ];
	oam_y = FONTOAM_PriTbl[ oamdata->oam_size ][ FONTOAM_PRI_Y ]; 
	
	// oam�T�C�Y����L�����N�^�f�[�^�o�b�t�@���쐬
	buff_size =  oam_x;
	buff_size *= oam_y;
	if( buff_size < char_min_num ){
		buff_size = char_min_num;
	}
	buff_size *= FONTOAM_CHAR_BYTE;
	
	// ���[�J���o�b�t�@�Ƀf�[�^���
	FONTOAM_BmpCutOamSize( bmp, oam_x, oam_y, oamdata->x, oamdata->y, &pbuff[idx] );

	return (idx + buff_size);
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	����OAM�S��\������̂ɕK�v�ȃL�����N�^�f�[�^�T�C�Y���擾
 *
 *	@param	list 
 *
 *	@return
 *
 *
 */
//-----------------------------------------------------------------------------
static int charAreaSizeOamDataList( const FONTOAM_OAM_DATA* list, int draw_area )
{
	FONTOAM_OAM_DATA* work;
	int char_min;	// �L�����N�^�f�[�^�̍ŏ��P��
	GXOBJVRamModeChar  map_mode;
	int offs;
	int char_num;
	int oam_x, oam_y;	// oam�T�C�Y
	
	// �L�����N�^�f�[�^�̍ŏ��P�ʂ��v�Z
	if( draw_area == NNS_G2D_VRAM_TYPE_2DMAIN ){
		map_mode = GX_GetOBJVRamModeChar();
	}else{
		map_mode = GXS_GetOBJVRamModeChar();
	}
	char_min = CharModeMinNum( map_mode );

	offs = 0;
	work = list->next;
	while( work != list ){

		// �L�����N�^oam�T�C�Y����L�����N�^�����v�Z
		oam_x = FONTOAM_PriTbl[ work->oam_size ][ FONTOAM_PRI_X ];
		oam_y = FONTOAM_PriTbl[ work->oam_size ][ FONTOAM_PRI_Y ]; 
		
		char_num = oam_x * oam_y;
		if( char_num < char_min ){
			char_num = char_min;
		}
		
		offs += char_num * FONTOAM_CHAR_BYTE;
		
		work = work->next;
	}

	return offs;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	OAM�f�[�^���X�g�̃Z���A�N�^�[���쐬����
 *
 *	@param	font_init		�t�H���g�쐬�f�[�^
 *	@param	list			OAM�f�[�^���X�g�擪�f�[�^
 *	@param	img_proxy		�C���[�W�v���N�V�z��f�[�^
 *	@param	font_obj		�t�H���g�I�u�W�F
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void addClActOamDataList( const FONTOAM_INIT* font_init, const FONTOAM_OAM_DATA* list, const NNSG2dImageProxy* img_proxy, FONTOAM_OBJ_PTR font_obj )
{
	FONTOAM_OAM_DATA* work;
	int count;

	count = 0;
	work = list->next;
	while( work != list ){
		
		font_obj->obj_w[ count ].clact = addClActOamDataOne( font_init, work, img_proxy + count );
		GF_ASSERT( font_obj->obj_w[ count ].clact );
		font_obj->obj_w[ count ].x = work->x * FONTOAM_CHAR_SIZE;
		font_obj->obj_w[ count ].y = work->y * FONTOAM_CHAR_SIZE;
		
		work = work->next;
		count++;
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	���X�g�̃Z���A�N�^�[�j��
 *
 *	@param	fontoam 
 *
 *	@return
 *
 *
 */
//-----------------------------------------------------------------------------
static void delClActOamDataList( FONTOAM_OBJ_PTR fontoam )
{
	int i;		// ���[�v�p

	for( i=0; i<fontoam->obj_num; i++ ){

		CLACT_Delete( fontoam->obj_w[ i ].clact );
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�POAM�̃A�N�^�[���쐬
 *
 *	@param	font_init	�t�H���g�쐬�f�[�^
 *	@param	oamdata		OAM�f�[�^
 *	@param	img_proxy	�g�p����C���[�W�v���N�V
 *
 *	@return	�쐬�����A�N�^�[�|�C���^
 *
 *
 */
//-----------------------------------------------------------------------------
static CLACT_WORK_PTR addClActOamDataOne( const FONTOAM_INIT* font_init, const FONTOAM_OAM_DATA* oamdata, const NNSG2dImageProxy* img_proxy )
{
	CLACT_ADD_SIMPLE	add;		// �o�^�f�[�^
	CLACT_HEADER		head;		// �w�b�_�[

	// �Z���A�N�^�[�w�b�_�[�쐬
	head.pImageProxy	= img_proxy;
	head.pCharData		= NULL;
	head.pPaletteProxy	= font_init->pltt;
	head.pCellBank		= font_init->fontoam_sys->pCellBank[ oamdata->oam_size ];
	head.pAnimBank		= NULL;
	head.pMCBank		= NULL;
	head.pMCABank		= NULL;

	head.flag			= 0;
	head.priority		= font_init->bg_pri;
	
	// �o�^�f�[�^�쐬
	add.ClActSet		= font_init->clact_set;
	add.ClActHeader		= &head;
	add.pri				= font_init->soft_pri;
	add.DrawArea		= font_init->draw_area;
	add.heap			= font_init->heap;

	// �o�^���W�v�Z
	add.mat.x = 0;
	add.mat.y = 0;
	add.mat.z = 0;
	
	if( font_init->parent ){
		const VecFx32* parent_mat;			// �e���W
		parent_mat = CLACT_GetMatrix( font_init->parent );

		add.mat = *parent_mat;
	}
	add.mat.x	+= (font_init->x << FX32_SHIFT) + ((oamdata->x * FONTOAM_CHAR_SIZE) << FX32_SHIFT);
	add.mat.y	+= (font_init->y << FX32_SHIFT) + ((oamdata->y * FONTOAM_CHAR_SIZE) << FX32_SHIFT);

	// �o�^
	return CLACT_AddSimple( &add );
}







//----------------------------------------------------------------------------
/**
 *
 *	@brief	OAM�f�[�^���쐬
 *
 *	@param	heap	�g�p����q�[�v
 *
 *	@return	OAM�f�[�^
 *
 *
 */
//-----------------------------------------------------------------------------
static FONTOAM_OAM_DATA* makeOamList( int heap )
{
	FONTOAM_OAM_DATA* oamdata;

	oamdata = sys_AllocMemoryLo( heap, sizeof(FONTOAM_OAM_DATA) );
	GF_ASSERT_MSG( oamdata, "�������I�[�o�[" );

	oamdata->next = NULL;
	oamdata->prev = NULL;

	return oamdata;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	OAM�f�[�^���������
 *
 *	@param	oamdata OAM�f�[�^
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void destOamList( FONTOAM_OAM_DATA* oamdata )
{
	GF_ASSERT( oamdata );

	sys_FreeMemoryEz( oamdata );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	���X�g�̑S�f�[�^�j��
 *
 *	@param	dummy	�_�~�[�f�[�^
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void destOamListAll( FONTOAM_OAM_DATA* dummy )
{
	FONTOAM_OAM_DATA* work;
	FONTOAM_OAM_DATA* next;

	work = dummy->next;
	while( work != dummy ){
		next = work->next;
		destOamList( work );
		work = next;
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	���X�g�ɐݒ�
 *
 *	@param	oamdata	OAM�f�[�^
 *	@param	prev	�O�̃f�[�^
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void setOamList( FONTOAM_OAM_DATA* oamdata, FONTOAM_OAM_DATA* prev )
{
	oamdata->next		= prev->next;
	oamdata->prev		= prev;
	prev->next->prev	= oamdata;
	prev->next			= oamdata;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	oam�f�[�^�����X�g����͂���
 *
 *	@param	oamdata	OAM�f�[�^
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void resetOamList( FONTOAM_OAM_DATA* oamdata )
{
	oamdata->prev->next	= oamdata->next;
	oamdata->next->prev	= oamdata->prev;
}
