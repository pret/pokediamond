//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		imc_drawsys.c
 *	@brief		�C���[�W�N���b�v�`��V�X�e���f�[�^�Ǘ��V�X�e��
 *				���̃V�X�e�����g�p����΁A���ׂĕ`��o����悤�ɂ��܂��B
 *	@author		tomoya takahashi
 *	@data		2005.09.21
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

#include <string.h>
#include "system.h"
#include "assert.h"
#include "display.h"
#include "include/system/heapdefine.h"
#include "include/system/arc_util.h"
#include "include/system/arc_tool.dat"
#include "include/system/render_oam.h"
#include "char_manager.h"
#include "pltt_manager.h"
#include "include/gflib/gf_gx.h"


#define	__IMC_DRAWSYS_H_GLOBAL
#include "include/application/imageClip/imc_drawsys.h"

//-----------------------------------------------------------------------------
/**
 *					�萔�錾
*/
//-----------------------------------------------------------------------------
#define IMC_DRAW_MAIN_PLANE	(GX_PLANEMASK_BG0 | GX_PLANEMASK_BG1 | GX_PLANEMASK_BG2 | GX_PLANEMASK_BG3 | GX_PLANEMASK_OBJ)
#define IMC_DRAW_SUB_PLANE	(GX_PLANEMASK_BG0 | GX_PLANEMASK_BG1 | GX_PLANEMASK_OBJ)


#define IMC_POKE_OBJ_TEX_SIZE	(0x2800)
#define IMC_POKE_OBJ_PLTT_SIZE	(0x20)


//-------------------------------------
//	
//	�Z���A�N�^�[�������p
//	
//=====================================
#define	IMC_CHAR_NUM	(8)
#define IMC_PLTT_NUM	(5)
#define IMC_CELL_NUM	(48)

//-----------------------------------------------------------------------------
/**
 *					�\���̐錾
*/
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
/**
*		�O���[�o��
*/
//-----------------------------------------------------------------------------
/*
//	�p���b�g�I�t�Z�b�g�Ή��\
static u8 plttOfs[ IMC_ACCE_MAX ] = {
	0,0,1,1,0,0,0,0,0,0,		// 1~
	0,0,0,0,0,0,0,0,0,0,		// 11~
	0,0,0,0,0,0,0,0,0,0,		// 21~
	0,1,0,0,0,0,0,0,0,0,		// 31~
	0,0,0,0,0,0,0,0,0,0,		// 41~
	0,0,0,0,2,0,0,1,0,0,		// 51~
	0,0,0,0,0,0,0,0,0,0,		// 61~
	0,0,0,0,0,0,1,0,0,0,		// 71~
	0,0,0,0,0,0,0,0,0,0,		// 81~
	0,0,0,0,0,0,0,0,0,0,		// 91~
};
//*/

//-----------------------------------------------------------------------------
/**
 *					�v���g�^�C�v�錾
*/
//-----------------------------------------------------------------------------
static void vram_bank_set( void );
static void setup_3d( void );
static void setup_2d_imgClip( void );

static void putback_3d( void );
static void putback_2d_imgClip( void );


static void initSWSP( IMC_DRAW_DATA* data, const SWSP_SYSDATA* cp_sys );
static void deleteSWSP( IMC_DRAW_DATA* data );
static void drawSWSP( IMC_DRAW_DATA* data );

static void initSoftSprite( IMC_DRAW_DATA* drawData, int heap, int tex_size, int pltt_size );
static void deleteSoftSprite( IMC_DRAW_DATA* drawData );

static void initAccePlttOfs( IMC_DRAW_DATA* data, int heap );
static void deleteAccePlttOfs( IMC_DRAW_DATA* data );

static void initCLACT( IMC_DRAW_DATA* data );
static void deleteCLACT( IMC_DRAW_DATA* data );
static void drawCLACT( IMC_DRAW_DATA* data );

static void initCharRes( IMC_DRAW_DATA* data );
static void deleteCharRes( IMC_DRAW_DATA* data );


static void loadSWSPChar( IMC_DRAW_DATA* data, SWSP_CHARDATA* char_data, int num );
static void loadSWSPPltt( IMC_DRAW_DATA* data, SWSP_PLTTDATA* pltt_data, int num );

static void setBg( IMC_DRAW_DATA* data );
static void delBg( IMC_DRAW_DATA* data );

static void getCharSize( NNSG2dCharacterData* char_data, int* x, int* y );

static void loadSWSPResDataAllocMemory( IMC_DRAW_LOADRES_DATA* loadData, int char_num, int pltt_num, int heap );
static void loadSWSPResDataDeleteMemory( IMC_DRAW_LOADRES_DATA* loadData );
static void loadAcceData( IMC_DRAW_DATA* drawData, IMC_DRAW_LOADRES_DATA* loadData );
static void loadBGThumData( IMC_DRAW_DATA* drawData, IMC_DRAW_LOADRES_DATA* loadData );


//----------------------------------------------------------------------------
//
/**
 *
 *	@brief	�`��V�X�e����`��o����悤�Ɋ���ݒ肵�܂�
 *
 *	@param	none
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_DRAW_SetUp( void )
{
	// �o���N�ݒ�
	vram_bank_set();
	
	// �RD�ݒ�
	setup_3d();
	
	// �QD�ݒ�
	setup_2d_imgClip();

	// �`����ύX
	sys.disp3DSW = DISP_3D_TO_SUB;
	GF_Disp_DispSelect();
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�ݒ肵�����f�[�^��j�����܂�
 *
 *	@param	none
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_DRAW_PutBack( void )
{
	// �`����ύX
	sys.disp3DSW = DISP_3D_TO_MAIN;
	GF_Disp_DispSelect();
	
	// 2d�ݒ��j��
	putback_2d_imgClip();

	// 3d�ݒ��j��
	putback_3d();

	GX_ResetBankForTex();
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�`��p�V�X�e���̐ݒ���s���܂��B
 *
 *	@param	drawData	�`��f�[�^
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_DRAW_InitSys( IMC_DRAW_DATA* drawData )
{
	// �X�v���C�g�f�[�^�쐬
	SWSP_SYSDATA swsp = {
		IMC_SPRITE_OBJ_NUM,
		IMC_SPRITE_CHAR_NUM,
		IMC_SPRITE_PLTT_NUM,
		HEAPID_IMAGECLIP_DRAW
	};//*/
	initSWSP( drawData, &swsp );

	// �|�P�����`��X�v���C�g�f�[�^�쐬
	initSoftSprite( drawData, HEAPID_IMAGECLIP_DRAW, IMC_POKE_OBJ_TEX_SIZE, IMC_POKE_OBJ_PLTT_SIZE );


	// �L�����N�^���\�[�X�}�l�[�W���쐬	�o�^�ő吔�@=�@IMC_SPRITE_OBJ_CHAR_NUM
	initCharRes( drawData );

	// �A�N�Z�T���p�p���b�g�I�t�Z�b�g�e�[�u���쐬
	initAccePlttOfs( drawData, HEAPID_IMAGECLIP_DATA );

	// �Z���A�N�^�[�쐬
	initCLACT( drawData );

	// BG�V�X�e���f�[�^�쐬
	drawData->BG_Ini = GF_BGL_BglIniAlloc( HEAPID_IMAGECLIP_DRAW );
	setBg( drawData );

}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�`��V�X�e���f�[�^��j������
 *
 *	@param	drawData	�`��f�[�^
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_DRAW_DeleteSys( IMC_DRAW_DATA* drawData )
{
	// �p���b�g�I�t�Z�b�g�e�[�u���j��
	deleteAccePlttOfs( drawData );
	
	// �X�v���C�g�f�[�^�j��
	deleteSWSP( drawData );

	// BG�V�X�e���f�[�^�j��
	delBg( drawData );
	sys_FreeMemoryEz( drawData->BG_Ini );
	
	// �|�P�����`��V�X�e���j��
	deleteSoftSprite( drawData );

	// �Z���A�N�^�[�j��
	deleteCLACT( drawData );

	// �L�����N�^�f�[�^�j��
	deleteCharRes( drawData );

	// �L�����N�^�f�[�^�ۑ��̈�j��
	sys_FreeMemoryEz( drawData->SWSP_charData );
	drawData->SWSP_charData = NULL;
	
	// �p���b�g�f�[�^�ۑ��̈�j��
	sys_FreeMemoryEz( drawData->SWSP_plttData );
	drawData->SWSP_plttData = NULL;
	
}


//----------------------------------------------------------------------------
/**
 *
 *	@brief	�`��֐��̂���`��V�X�e���̕`��
 *
 *	@param	drawData	�`��f�[�^
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_DRAW_DrawSys( IMC_DRAW_DATA* drawData )
{
	//�R�c�`��J�n
	GF_G3X_Reset();

	NNS_G2dSetupSoftwareSpriteCamera();

	// �X�v���C�g�`��
	if( drawData->SWSP_DrawFlag ){
		drawSWSP( drawData );	
	}
	
	// �|�P�����`��
	if( drawData->SSM_DrawFlag ){
		SoftSpriteMain( drawData->SSM_drawSys );
	}
	
	/* �W�I���g���������_�����O�G���W���֘A�������̃X���b�v */
	GF_G3_RequestSwapBuffers(GX_SORTMODE_AUTO, GX_BUFFERMODE_Z);

	// �QD�`��
	// �Z���A�N�^�[�`��
	drawCLACT( drawData );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	���\�[�X�̓ǂݍ��݂��s���܂�	�X��Vram��ɓW�J���܂�
 *
 *	@param	drawData	�`��f�[�^�i�[�̈�
 *	@param	loadData	�ǂݍ��ރ��\�[�X�f�[�^
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_DRAW_LoadResource( IMC_DRAW_DATA* drawData, IMC_DRAW_LOADRES_DATA* loadData )
{
	// �L�����N�^�f�[�^�ǂݍ���
	loadSWSPChar( drawData, loadData->SWSP_charTbl, loadData->SWSP_charNum );
	
	// �p���b�g�f�[�^�ǂݍ���
	loadSWSPPltt( drawData, loadData->SWSP_plttTbl, loadData->SWSP_plttNum );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	���\�[�X�̔j�����s���܂�
 *
 *	@param	drawData	�`��f�[�^�i�[�̈�
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_DRAW_DeleteResource( IMC_DRAW_DATA* drawData )
{
	// �X�v���C�g�f�[�^���S�j��
	SWSP_CharDeleteAll( drawData->SWSP_drawSys );
	SWSP_PlttDeleteAll( drawData->SWSP_drawSys );
}


//----------------------------------------------------------------------------
/**
 *	@brief	�A�N�^�[�o�^
 *
 *	@param	drawData	���[�N
 *	@param	contid		�Ǘ�ID
 *	@param	x			�����W
 *	@param	y			�����W
 *	@param	pri			�D�揇��
 *	@param	draw_area	�`��G���A
 *
 *	@return	�A�N�^�[���[�N
 */
//-----------------------------------------------------------------------------
CLACT_WORK_PTR IMC_DRAW_AddClact( IMC_DRAW_DATA* drawData, int contid, int x, int y, int pri, int draw_area )
{
	CLACT_HEADER head;
	CLACT_ADD_SIMPLE add;

	CLACT_U_MakeHeader( &head,
			contid, contid, contid, contid,
			CLACT_U_HEADER_DATA_NONE, CLACT_U_HEADER_DATA_NONE,
			0, 0,
			drawData->resMan[ CLACT_U_CHAR_RES ],
			drawData->resMan[ CLACT_U_PLTT_RES ],
			drawData->resMan[ CLACT_U_CELL_RES ],
			drawData->resMan[ CLACT_U_CELLANM_RES ],
			NULL, NULL );

	add.ClActSet = drawData->clactSet;
	add.ClActHeader = &head;
	add.mat.x	= x << FX32_SHIFT;
	add.mat.y	= y << FX32_SHIFT;
	add.mat.z	= 0;
	add.pri		= pri;
	add.DrawArea = draw_area;
	add.heap	= HEAPID_IMAGECLIP_DRAW;

	return CLACT_AddSimple( &add );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�L�����N�^�f�[�^�ǂݍ���
 *
 *	@param	drawData		�`��V�X�e���f�[�^
 *	@param	fileIdx			�t�@�C���C���f�b�N�X
 *	@param	dataIdx			�f�[�^�C���f�b�N�X
 *	@param	comp			���k�t���O
 *	@param	vramType		Vram�^�C�v
 *	@param	id				�Ǘ�ID
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_DRAW_CLACT_LoadCharData( IMC_DRAW_DATA* drawData, int fileIdx, int dataIdx, BOOL comp, int vramType, int id )
{
	CLACT_U_RES_OBJ_PTR res;
	
	// �f�[�^�ǂݍ���
	res = CLACT_U_ResManagerResAddArcChar( 
			drawData->resMan[ CLACT_U_CHAR_RES ],
			fileIdx, dataIdx, comp, id, vramType,
			HEAPID_IMAGECLIP_DRAW);

	// �f�[�^�]��
	CLACT_U_CharManagerSetAreaCont( res );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�p���b�g�f�[�^�ǂݍ���
 *
 *	@param	drawData		�`��V�X�e���f�[�^
 *	@param	fileIdx			�t�@�C���C���f�b�N�X
 *	@param	dataIdx			�f�[�^�C���f�b�N�X
 *	@param	comp			���k�t���O
 *	@param	vramType		Vram�^�C�v
 *	@param	load_num		�p���b�g�ǂݍ��ݐ�
 *	@param	id				�Ǘ�ID
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_DRAW_CLACT_LoadPlttData( IMC_DRAW_DATA* drawData, int fileIdx, int dataIdx, BOOL comp, int vramType, int load_num, int id )
{
	CLACT_U_RES_OBJ_PTR	res;
	
	// �f�[�^�ǂݍ���
	res = CLACT_U_ResManagerResAddArcPltt( 
			drawData->resMan[ CLACT_U_PLTT_RES ],
			fileIdx, dataIdx, comp, id, vramType,
			load_num, HEAPID_IMAGECLIP_DRAW);

	// �f�[�^�]��
	CLACT_U_PlttManagerSetCleanArea( res );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�Z���f�[�^�ǂݍ���
 *
 *	@param	drawData		�`��V�X�e���f�[�^
 *	@param	fileIdx			�t�@�C���C���f�b�N�X
 *	@param	dataIdx			�f�[�^�C���f�b�N�X
 *	@param	comp			���k�t���O
 *	@param	id				�Ǘ�ID
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_DRAW_CLACT_LoadCellData( IMC_DRAW_DATA* drawData, int fileIdx, int dataIdx, BOOL comp, int id )
{
	// �f�[�^�ǂݍ���
	CLACT_U_ResManagerResAddArcKindCell( 
			drawData->resMan[ CLACT_U_CELL_RES ],
			fileIdx, dataIdx, comp, id, CLACT_U_CELL_RES,
			HEAPID_IMAGECLIP_DRAW);
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�Z���A�j���f�[�^�ǂݍ���
 *
 *	@param	drawData		�`��V�X�e���f�[�^
 *	@param	fileIdx			�t�@�C���C���f�b�N�X
 *	@param	dataIdx			�f�[�^�C���f�b�N�X
 *	@param	comp			���k�t���O
 *	@param	id				�Ǘ�ID
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_DRAW_CLACT_LoadCellAnmData( IMC_DRAW_DATA* drawData, int fileIdx, int dataIdx, BOOL comp, int id )
{
	// �f�[�^�ǂݍ���
	CLACT_U_ResManagerResAddArcKindCell( 
			drawData->resMan[ CLACT_U_CELLANM_RES ],
			fileIdx, dataIdx, comp, id, CLACT_U_CELLANM_RES,
			HEAPID_IMAGECLIP_DRAW);
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�L�����N�^���\�[�X�f�[�^�݂̂̔j��
 *
 *	@param	drawData	�`��V�X�e���f�[�^
 *	@param	id			�Ǘ�ID
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_DRAW_CLACT_DeleteCharRes( IMC_DRAW_DATA* drawData, int id )
{
	CLACT_U_RES_OBJ_PTR	res;

	res = CLACT_U_ResManagerGetIDResObjPtr(
			drawData->resMan[ CLACT_U_CHAR_RES ], id);

	// ���\�[�X�j��
	CLACT_U_ResManagerResDelete( 
			drawData->resMan[ CLACT_U_CHAR_RES ], res );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�p���b�g���\�[�X�f�[�^�݂̂̔j��
 *
 *	@param	drawData	�`��V�X�e���f�[�^
 *	@param	id			�Ǘ�ID
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_DRAW_CLACT_DeletePlttRes( IMC_DRAW_DATA* drawData, int id )
{
	CLACT_U_RES_OBJ_PTR	res;

	res = CLACT_U_ResManagerGetIDResObjPtr(
			drawData->resMan[ CLACT_U_PLTT_RES ], id);

	CLACT_U_ResManagerResDelete( 
			drawData->resMan[ CLACT_U_PLTT_RES ], res );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�Z�����\�[�X�f�[�^�݂̂̔j��
 *
 *	@param	drawData	�`��V�X�e���f�[�^
 *	@param	id			�Ǘ�ID
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_DRAW_CLACT_DeleteCellRes( IMC_DRAW_DATA* drawData, int id )
{
	CLACT_U_RES_OBJ_PTR	res;

	res = CLACT_U_ResManagerGetIDResObjPtr(
			drawData->resMan[ CLACT_U_CELL_RES ], id);

	// ���\�[�X�j��
	CLACT_U_ResManagerResDelete( 
			drawData->resMan[ CLACT_U_CELL_RES ], res );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�Z���A�j���f�[�^�݂̂̔j��
 *
 *	@param	drawData	�`��V�X�e���f�[�^
 *	@param	id			�Ǘ�ID
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_DRAW_CLACT_DeleteCellAnmRes( IMC_DRAW_DATA* drawData, int id )
{
	CLACT_U_RES_OBJ_PTR	res;

	res = CLACT_U_ResManagerGetIDResObjPtr(
			drawData->resMan[ CLACT_U_CELLANM_RES ], id);

	CLACT_U_ResManagerResDelete( 
			drawData->resMan[ CLACT_U_CELLANM_RES ], res );
}



//----------------------------------------------------------------------------
/**
 *
 *	@brief	�X�v���C�g�p�̓ǂݍ��ރt�@�C�����쐬	������
 *
 *	@param	loadData	�쐬��
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_DRAW_MakeLoadSWSP_samp( IMC_DRAW_DATA* drawData, IMC_DRAW_LOADRES_DATA* loadData )
{
	// SWSP�̃��\�[�X�o�^�f�[�^���������m��
	loadSWSPResDataAllocMemory( loadData, IMC_SPRITE_CHAR_NUM, IMC_SPRITE_PLTT_NUM, HEAPID_IMAGECLIP_DRAW );
	
	// �A�N�Z�T���p���\�[�X
	loadAcceData( drawData, loadData );

	// BG�T���l�C���p���\�[�X
	loadBGThumData( drawData, loadData );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�X�v���C�g�p�̓ǂݍ��݃t�@�C����j������
 *
 *	@param	loadData	�ǂݍ��݃f�[�^
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_DRAW_DestLoadSWSP( IMC_DRAW_LOADRES_DATA* loadData )
{
	loadSWSPResDataDeleteMemory( loadData );
}


//----------------------------------------------------------------------------
/**
 *
 *	@brief	�L�����N�^�f�[�^�̓o�^
 *
 *	@param	drawData	�`��f�[�^�\����
 *	@param	buff		�L�����N�^�f�[�^�o�b�t�@
 *	@param	char_no		�o�^�L�����N�^�i���o�[�i�A�N�Z�T���i���o�[��Link�j
 *
 *	@return	�A���p�b�N��̃L�����N�^�f�[�^
 *
 *
 */
//-----------------------------------------------------------------------------
NNSG2dCharacterData* IMC_DRAW_SetCharData( IMC_DRAW_DATA* drawData, void* buff, int char_no )
{
	// ���\�[�X�}�l�[�W���ɓo�^
	RESM_AddResNormal( drawData->SWSP_charRes, buff, char_no );
	NNS_G2dGetUnpackedCharacterData( buff, &drawData->SWSP_UPchar[ char_no ] );
	return drawData->SWSP_UPchar[ char_no ];
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�ʏ펞�̃E�B���h�E�}�X�N�ݒ�
 *
 *	@param	none	
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_DRAW_WndMaskNormalSet( void )
{
/*	GX_SetVisibleWnd(GX_WNDMASK_W0 | GX_WNDMASK_W1);

	G2_SetWnd0InsidePlane( GX_WND_PLANEMASK_BG0 | GX_WND_PLANEMASK_BG2, FALSE );
	G2_SetWnd1InsidePlane( GX_WND_PLANEMASK_BG0 | GX_WND_PLANEMASK_BG3, FALSE );
	G2_SetWndOutsidePlane( GX_WND_PLANEMASK_BG1, FALSE );
	
	G2_SetWnd0Position( IMC_LBOX_AREA_X,
						IMC_LBOX_AREA_Y,
						IMC_LBOX_AREA_X + IMC_LBOX_AREA_WIDTH,
						IMC_LBOX_AREA_Y + IMC_LBOX_AREA_HEIGHT);
	
	G2_SetWnd1Position( IMC_RBOX_AREA_X,
						IMC_RBOX_AREA_Y,
						IMC_RBOX_AREA_X + IMC_RBOX_AREA_WIDTH,
						IMC_RBOX_AREA_Y + IMC_RBOX_AREA_HEIGHT);//*/
	GX_SetVisibleWnd(GX_WNDMASK_NONE);
	// BG�D�揇�ʂ̕ύX
	G2_SetBG0Priority( 1 );
	G2_SetBG1Priority( 0 );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�I�u�W�F�N�g�𓮂����Ă���Ƃ��̃E�B���h�E�}�X�N��ݒ�
 *
 *	@param	none	
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_DRAW_WndMaskObjMoveSet( void )
{
	GX_SetVisibleWnd(GX_WNDMASK_W0);

	G2_SetWnd0InsidePlane( GX_WND_PLANEMASK_BG0 | GX_WND_PLANEMASK_BG1 | GX_WND_PLANEMASK_BG2 | GX_WND_PLANEMASK_BG3 | GX_WND_PLANEMASK_OBJ, FALSE );
	G2_SetWndOutsidePlane( GX_WND_PLANEMASK_BG1 | GX_WND_PLANEMASK_OBJ, FALSE );

	// �|�W�V�����ݒ�
	// �t���[���̕����l�������l��ݒ�
	G2_SetWnd0Position( IMC_LBOX_AREA_X_MOVEOK,
						IMC_LBOX_AREA_Y_MOVEOK,
						IMC_RBOX_AREA_X_MOVEOK + IMC_RBOX_AREA_WIDTH_MOVEOK,
						IMC_RBOX_AREA_Y_MOVEOK + IMC_RBOX_AREA_HEIGHT_MOVEOK );
	// BG�D�揇�ʂ̕ύX
	G2_SetBG0Priority( 0 );
	G2_SetBG1Priority( 1 );//*/
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�I���`�F�b�N���̕\���D�揇�ʐݒ�
 *
 *	@param	none	
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_DRAW_EndCheckBGPri( void )
{
	G2_SetBG1Priority( 3 );
}


//----------------------------------------------------------------------------
/**
 *
 *	@brief	�`��V�X�e���pV�u�����N�֐�
 *
 *	@param	drawData	�`��V�X�e���f�[�^
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_DRAW_VBlank( IMC_DRAW_DATA* drawData )
{
	// BG�V�X�e����Vblank�֐�
	GF_BGL_VBlankFunc( drawData->BG_Ini );

	// �\�t�g�E�F�A�X�v���C�g
	SoftSpriteTextureTrans( drawData->SSM_drawSys );

	// �����_���[���LOAM�}�l�[�W����OAM�]��
	REND_OAMTrans();
}

//----------------------------------------------------------------------------
/**
 *	@brief	�A�N�Z�T���p�\�t�g�E�F�A�X�v���C�g�f�[�^�������m��
 *
 *	@param	drawData	�ǂݍ��݃f�[�^���[�N	
 *	@param	heap		�q�[�v
 *		
 *	@return	none
 */
//-----------------------------------------------------------------------------
void IMC_DRAW_SWSPResDataAllocMemory( IMC_DRAW_LOADRES_DATA* loadData, int heap )
{
	// SWSP�̃��\�[�X�o�^�f�[�^���������m��
	loadSWSPResDataAllocMemory( loadData, IMC_SPRITE_CHAR_NUM, IMC_SPRITE_PLTT_NUM, heap );
}



//-----------------------------------------------------------------------------
/**
*		�L�����N�^�f�[�^�����āA�ق�Ƃɂ��̈ʒu�ɔ����F�ȊO�̐F�ɂȂ���
*		���邩���`�F�b�N����
*/
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *
 *	@brief	�L�����N�^�f�[�^�̎w��ʒu�ɐF��param�Ŗ������`�F�b�N
 *
 *	@param	char_data		�`�F�b�N�Ɏg���L�����N�^�f�[�^
 *	@param	offs_x			x�I�t�Z�b�g
 *	@param	offs_y			y�I�t�Z�b�g
 *	@param	param			�`�F�b�N�F�i���o�[
 *
 *	@retval	IMC_DRAW_CHAR_CHECK_TRUE	param�̐F
 *	@retval	IMC_DRAW_CHAR_CHECK_FALSE	param�̐F����Ȃ�
 *	@retval	IMC_DRAW_CHAR_CHECK_ERR		�G���[
 *
 * �P�U�F����
 *
 */
//-----------------------------------------------------------------------------
int IMC_DRAW_CharCheck( NNSG2dCharacterData* char_data, int offs_x, int offs_y, int param )
{
	u32* char_res;				// �L�����N�^���f�[�^
	int char_x, char_y;			// �L�����N�^�f�[�^�T�C�Y
	int char_px;				// �`�F�b�N����f�[�^�i���o�[
	int char_px_offs;			// �`�F�b�N����f�[�^���I�t�Z�b�g


		
	// �L�����N�^�f�[�^�T�C�Y���v�Z
	char_x = char_data->W;
	char_y = char_data->H;
	char_x *= 8;		// �s�N�Z���P�ʂɂ���
	char_y *= 8;		// �s�N�Z���P�ʂɂ���

	// �T�C�Yover�`�F�b�N
	if( (offs_x < 0) || (offs_y < 0) ||
		(offs_x >= char_x) || (offs_y >= char_y) ){

		return IMC_DRAW_CHAR_CHECK_ERR;
	}

//	OS_Printf( "char_x %d, char_y %d\n", char_data->W, char_data->H );

	// �L�����N�^�f�[�^�擾
	char_res = char_data->pRawData;

	// �I�t�Z�b�g�ʒu�̃L�����N�^�i���o�[
	char_px = (offs_y * char_x) + offs_x;
	char_px_offs = (char_px % 8);	// u32��8�s�N�Z�������邽��
	char_px /= 8;

//	OS_Printf( "char_px %d char_px_offs %d \n",char_px, char_px_offs );

//	OS_Printf( "%x \n", char_res[ char_px ] );
	
//	OS_Printf( " %d \n", (char_res[ char_px ] & (0xf << (char_px_offs * 4))) );

//	OS_Printf( " %d \n", ((param << (char_px_offs * 4))) );
	
	// ���̃L�����N�^�f�[�^���`�F�b�N
	if( (char_res[ char_px ] & (0xf << (char_px_offs * 4))) == (param << (char_px_offs * 4)) ){
		return IMC_DRAW_CHAR_CHECK_TRUE;
	}
	return IMC_DRAW_CHAR_CHECK_FALSE;
}


//-----------------------------------------------------------------------------
/**
 * 
 *	�C���[�W�N���b�v�v���C���[�V�X�e���p�֐��S
 * 
 */
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *
 *	@brief	�`��V�X�e��	�C���[�W�N���b�v�v���C���[�p�������ݒ�
 *
 *	@param	drawData	�`��V�X�e���f�[�^�i�[��
 *	@param	cp_swsp		�\�t�g�E�F�A�V�X�e���������f�[�^
 *	@param	BG_Ini		BG�V�X�e��
 *	@param	heap		�g�p�q�[�vID
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_DRAW_InitSysPlayer( IMC_DRAW_DATA* drawData, const SWSP_SYSDATA* cp_swsp, int heap )
{

	// �X�v���C�g�f�[�^�쐬
	initSWSP( drawData, cp_swsp );

	// �|�P�����`��X�v���C�g�f�[�^�쐬
	initSoftSprite( drawData, heap, IMC_POKE_OBJ_TEX_SIZE, IMC_POKE_OBJ_PLTT_SIZE );

	// �|�P�����`�惋�[�`��
	// �`�惂�[�h�ݒ�
	SoftSpriteDrawModeSet( drawData->SSM_drawSys, SS_DRAW_MODE_NO_IDENTITY );

	// �A�N�Z�T���p�p���b�g�I�t�Z�b�g�e�[�u���쐬
	initAccePlttOfs( drawData, heap );

}

//----------------------------------------------------------------------------
/**
 *	@brief	�v���C���[��BG�����̏�����
 *
 *	@param	BG_Ini		BG�R���g���[��
 *	@param	heap		�q�[�v
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void IMC_DRAW_InitSysPlayerBG( IMC_DRAW_DATA* drawData, GF_BGL_INI* BG_Ini, int heap )
{
	// BGIni�͊O������󂯎��
	drawData->BG_Ini = BG_Ini;

	{	// ���C���ʃt���[��2
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xf000, GX_BG_CHARBASE_0x04000, GX_BG_EXTPLTT_01,
			2, 0, 0, FALSE
		};
		GF_BGL_BGControlExit( drawData->BG_Ini, GF_BGL_FRAME2_M );
		GF_BGL_BGControlSet( drawData->BG_Ini, GF_BGL_FRAME2_M, &TextBgCntDat, GF_BGL_MODE_TEXT );
		GF_BGL_ClearCharSet( GF_BGL_FRAME2_M, 32, 0, heap );
		GF_BGL_ScrClear( drawData->BG_Ini, GF_BGL_FRAME2_M );
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�`��V�X�e���f�[�^��j������
 *
 *	@param	drawData	�`��f�[�^
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_DRAW_DeleteSysPlayer( IMC_DRAW_DATA* drawData )
{
	// �p���b�g�I�t�Z�b�g�e�[�u���j��
	deleteAccePlttOfs( drawData );
	
	// �X�v���C�g�f�[�^�j��
	deleteSWSP( drawData );

	// �|�P�����`��V�X�e���j��
	deleteSoftSprite( drawData );

	// �L�����N�^�f�[�^�ۑ��̈�j��
	sys_FreeMemoryEz( drawData->SWSP_charData );
	drawData->SWSP_charData = NULL;
	
	// �p���b�g�f�[�^�ۑ��̈�j��
	sys_FreeMemoryEz( drawData->SWSP_plttData );
	drawData->SWSP_plttData = NULL;

}

//----------------------------------------------------------------------------
/**
 *	@brief	�v���C���[�@�`��O���[�o��	BG�����̔j��
 *
 *	@param	drawData	
 *		
 *	@return	none
 */
//-----------------------------------------------------------------------------
void IMC_DRAW_DeleteSysPlayerBG( IMC_DRAW_DATA* drawData )
{
	//BG�j��
	GF_BGL_BGControlExit( drawData->BG_Ini, GF_BGL_FRAME2_M );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�`��V�X�e���pV�u�����N�֐�
 *
 *	@param	drawData	�`��V�X�e���f�[�^
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_DRAW_VBlankPlayer( IMC_DRAW_DATA* drawData )
{
	// �\�t�g�E�F�A�X�v���C�g
	SoftSpriteTextureTrans( drawData->SSM_drawSys );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�`��֐��̂���`��V�X�e���̕`��
 *
 *	@param	drawData	�`��f�[�^
 *	@param	center_x	���S��
 *	@param	center_y	���S��
 *	@param	rota_num	��]�p
 *	@param	scale		�X�P�[���x�N�g��
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_DRAW_DrawSysPlayer( IMC_DRAW_DATA* drawData, int center_x, int center_y, u16 rota_num, const VecFx32* p_scale )
{
	//�R�c�`��J�n
//	GF_G3X_Reset();
	G3_Identity();

	G3_PushMtx();
	{
		NNS_G2dSetupSoftwareSpriteCamera();

		// �S�̂ɂ��������s��ݒ�
		G3_Translate( center_x*FX32_ONE, center_y*FX32_ONE, 0 );
		{
			G3_RotZ( FX_SinIdx( rota_num ), FX_CosIdx( rota_num ) );
			G3_Scale( p_scale->x, p_scale->y, p_scale->z );
		}
		G3_Translate( -center_x*FX32_ONE, -center_y*FX32_ONE, 0 );//*/
		
		G3_PushMtx();
		{	
			if( drawData->SWSP_DrawFlag ){
				// �X�v���C�g�`��
				drawSWSP( drawData );	
			}
			
			// �|�P�����`��
			if( drawData->SSM_DrawFlag ){
				SoftSpriteMain( drawData->SSM_drawSys );
			}
		}
		G3_PopMtx(1);
		
		/* �W�I���g���������_�����O�G���W���֘A�������̃X���b�v */
	//	GF_G3_RequestSwapBuffers(GX_SORTMODE_AUTO, GX_BUFFERMODE_Z);
	}
	G3_PopMtx(1);
}




//----------------------------------------------------------------------------
/**
 *	@brief	preview������
 *
 *	@param	drawData	���[�N
 *	@param	heap		�q�[�v
 */
//-----------------------------------------------------------------------------
void IMC_DRAW_InitSysPrev( IMC_DRAW_DATA* drawData, int heap )
{
	// �Z���A�N�^�[�쐬
	initCLACT( drawData );

	// BG�V�X�e���f�[�^�쐬
	drawData->BG_Ini = GF_BGL_BglIniAlloc( HEAPID_IMAGECLIP_DRAW );
	setBg( drawData );

}

//----------------------------------------------------------------------------
/**
 *	@brief	preview�p�`�惏�[�N�j��
 *
 *	@param	drawData	���[�N
 */
//-----------------------------------------------------------------------------
void IMC_DRAW_DeleteSysPrev( IMC_DRAW_DATA* drawData )
{
	// BG�V�X�e���f�[�^�j��
	delBg( drawData );
	sys_FreeMemoryEz( drawData->BG_Ini );

	// �Z���A�N�^�[�j��
	deleteCLACT( drawData );
}

//----------------------------------------------------------------------------
/**
 *	@brief	previewV�u�����N����
 *
 *	@param	drawData	���[�N
 */
//-----------------------------------------------------------------------------
void IMC_DRAW_VBlankPrev( IMC_DRAW_DATA* drawData )
{
	// BG�V�X�e����Vblank�֐�
	GF_BGL_VBlankFunc( drawData->BG_Ini );

	// �����_���[���LOAM�}�l�[�W����OAM�]��
	REND_OAMTrans();
}

//----------------------------------------------------------------------------
/**
 *	@brief	�`�揈��
 *
 *	@param	drawData 
 */
//-----------------------------------------------------------------------------
void IMC_DRAW_DrawSysPrev( IMC_DRAW_DATA* drawData )
{
	// �QD�`��
	// �Z���A�N�^�[�`��
	drawCLACT( drawData );
}




//-----------------------------------------------------------------------------
/**
*	�v���C�x�[�g�֐�
*/
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *
 *	@brief	�o���N�ݒ�
 *
 *	@param	none
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void vram_bank_set( void )
{
	GF_BGL_DISPVRAM vramSetTable = {
		GX_VRAM_BG_128_C,				// ���C��2D�G���W����BG
		GX_VRAM_BGEXTPLTT_NONE,			// ���C��2D�G���W����BG�g���p���b�g
		GX_VRAM_SUB_BG_32_H,			// �T�u2D�G���W����BG
		GX_VRAM_SUB_BGEXTPLTT_NONE,		// �T�u2D�G���W����BG�g���p���b�g
		GX_VRAM_OBJ_32_FG,				// ���C��2D�G���W����OBJ
		GX_VRAM_OBJEXTPLTT_NONE,		// ���C��2D�G���W����OBJ�g���p���b�g
		GX_VRAM_SUB_OBJ_16_I,			// �T�u2D�G���W����OBJ
		GX_VRAM_SUB_OBJEXTPLTT_NONE,	// �T�u2D�G���W����OBJ�g���p���b�g
		GX_VRAM_TEX_01_AB,				// �e�N�X�`���C���[�W�X���b�g
		GX_VRAM_TEXPLTT_0123_E			// �e�N�X�`���p���b�g�X���b�g
	};
	GF_Disp_SetBank( &vramSetTable );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	3D�ʐݒ�
 *
 *	@param	none
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void setup_3d( void )
{
	// NitroSystem:�R�c�G���W���̏�����
	NNS_G3dInit();
	// �}�g���N�X�X�^�b�N�̏�����
    G3X_InitMtxStack();

	GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG0, VISIBLE_ON );
    G2_SetBG0Priority(1);

	// �e��`�惂�[�h�̐ݒ�(�V�F�[�h���A���`�G�C���A�X��������)
    G3X_SetShading(GX_SHADING_TOON);
    G3X_AntiAlias(TRUE);
	G3X_AlphaTest(FALSE, 0);	// �A���t�@�e�X�g�@�@�I�t
	G3X_AlphaBlend(TRUE);		// �A���t�@�u�����h�@�I��

	// �N���A�J���[�̐ݒ�
    G3X_SetClearColor(GX_RGB(0, 0, 0),	// clear color
                      0,				// clear alpha
                      0x7fff,			// clear depth
                      63,				// clear polygon ID
                      FALSE				// fog
                      );

	// �W�I���g���G���W���N����K���Ă΂�Ȃ���΂Ȃ�Ȃ�
    G3_SwapBuffers(GX_SORTMODE_AUTO, GX_BUFFERMODE_W);

	// �r���[�|�[�g�̐ݒ�
    G3_ViewPort(0, 0, 255, 191);

	// �}�l�[�W�����e�N�X�`���C���[�W�X���b�g���w��X���b�g���Ǘ��ł���悤�ɂ���
	// �f�t�H���g�}�l�[�W���ɂ���B
	NNS_GfdInitFrmTexVramManager(2, TRUE);
		
	// �}�l�[�W�����p���b�g��16KB���Ǘ��ł���悤�ɂ���
	// �f�t�H���g�}�l�[�W���ɂ���B
	NNS_GfdInitFrmPlttVramManager(0x4000, TRUE);
	
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�C���[�W�N���b�v��ʗp2D�ʐݒ�
 *
 *	@param	none
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void setup_2d_imgClip( void )
{
	// BG�ݒ�
	{
		GF_BGL_SYS_HEADER bg_head = {
			GX_DISPMODE_GRAPHICS,
			GX_BGMODE_0,
			GX_BGMODE_0,
			GX_BG0_AS_3D
		};
		GF_BGL_InitBG( &bg_head );
	}
	
	// OBJ�ݒ�
	// �}�b�s���O���[�h32K
	GX_SetOBJVRamModeChar( GX_OBJVRAMMODE_CHAR_1D_32K );
	// OAM�}�l�[�W��������
	NNS_G2dInitOamManagerModule();

	// �`��ʐݒ�
	GF_Disp_GX_VisibleControlInit();
	GF_Disp_GXS_VisibleControlInit();
	GF_Disp_GX_VisibleControl( IMC_DRAW_MAIN_PLANE, VISIBLE_ON );
	GF_Disp_GXS_VisibleControl( IMC_DRAW_SUB_PLANE, VISIBLE_ON );

}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�RD�ݒ�Ŏg�p������������j��
 *
 *	@param	none 
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void putback_3d( void )
{
	NNS_GfdResetFrmTexVramState();
	NNS_GfdResetFrmPlttVramState();
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�Q���ݒ�Ŏg�p������������j��
 *
 *	@param	none
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void putback_2d_imgClip( void )
{
	GF_Disp_GX_VisibleControlInit();
	GF_Disp_GXS_VisibleControlInit();
	// OAM�}�l�[�W��������
	NNS_G2dInitOamManagerModule();
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�\�t�g�E�F�A�X�v���C�g������
 *
 *	@param	data	�`��f�[�^
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void initSWSP( IMC_DRAW_DATA* data, const SWSP_SYSDATA* cp_sys )
{
/*	SWSP_SYSDATA sys = {
		IMC_SPRITE_OBJ_NUM,
		IMC_SPRITE_CHAR_NUM,
		IMC_SPRITE_PLTT_NUM,
		HEAPID_IMAGECLIP_DRAW
	};//*/

	data->SWSP_drawSys = SWSP_SysInit( cp_sys );

	// �L�����N�^�f�[�^�i�[�p�̈���쐬
	data->SWSP_charData = sys_AllocMemory( cp_sys->heap, sizeof(SWSP_CHAR_PTR) * IMC_SPRITE_CHAR_NUM );
	
	data->SWSP_charNum = IMC_SPRITE_CHAR_NUM;
	data->SWSP_charNow = 0;

	// �p���b�g�f�[�^�i�[�̈���쐬
	data->SWSP_plttData = sys_AllocMemory( cp_sys->heap, sizeof(SWSP_PLTT_PTR) * IMC_SPRITE_PLTT_NUM );
	data->SWSP_plttNum = IMC_SPRITE_PLTT_NUM;
	data->SWSP_plttNow = 0;

	data->SWSP_DrawFlag = TRUE;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�\�t�g�E�F�A�X�v���C�g�j��
 *
 *	@param	data	�`��f�[�^
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void deleteSWSP( IMC_DRAW_DATA* data )
{
	SWSP_SysDelete( data->SWSP_drawSys );
	data->SWSP_drawSys = NULL;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�X�v���C�g�V�X�e���̕`��
 *
 *	@param	data	�`��f�[�^
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void drawSWSP( IMC_DRAW_DATA* data )
{
	SWSP_SysDraw( data->SWSP_drawSys );
	
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�L�����N�^�f�[�^�]��
 *
 *	@param	data		�`��V�X�e���f�[�^
 *	@param	char_data	�L�����N�^�f�[�^
 *	@param	num			�]���L�����N�^�f�[�^��
 *
 *	@return	none
 *
 * char_data�̗v�f�����L�����N�^�f�[�^�Ǘ�ID�ƂȂ�܂�
 *
 */
//-----------------------------------------------------------------------------
static void loadSWSPChar( IMC_DRAW_DATA* data, SWSP_CHARDATA* char_data, int num )
{
	int i;		// ���[�v�p

	for(i=0; i<num; i++){

		GF_ASSERT( data->SWSP_charNow < data->SWSP_charNum );

		// �A�N�Z�T���@�T���l�C���̑Ή������ʒu�ɓ����K�v�����邽�߁A
		// �i�[���΂����Ƃ�����
		if(char_data[i].res_file != NULL){
			data->SWSP_charData[ data->SWSP_charNow ] = SWSP_CharLoad( char_data + i );
		}else{
			data->SWSP_charData[ data->SWSP_charNow ] = NULL;
		}
		data->SWSP_charNow++;
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�p���b�g�f�[�^��]������
 *
 *	@param	data			�`��V�X�e���f�[�^
 *	@param	pltt_data		�p���b�g�]���f�[�^
 *	@param	num				�p���b�g��	
 *		
 *	@return	none
 *
 * pltt_data�̗v�f�����p���b�g�Ǘ�ID�ƂȂ�܂�
 *
 */
//-----------------------------------------------------------------------------
static void loadSWSPPltt( IMC_DRAW_DATA* data, SWSP_PLTTDATA* pltt_data, int num )
{
	int i;		// ���[�v�p

	for(i=0; i<num; i++){

		GF_ASSERT( data->SWSP_plttNow < data->SWSP_plttNum );
		
		// �A�N�Z�T���@�T���l�C���̑Ή������ʒu�ɓ����K�v�����邽�߁A
		// �i�[���΂����Ƃ�����
		if(pltt_data[i].res_file != NULL){
			data->SWSP_plttData[ data->SWSP_plttNow ] = SWSP_PlttLoad( pltt_data + i );
		}else{
			data->SWSP_plttData[ data->SWSP_plttNow ] = NULL;
		}

		data->SWSP_plttNow++;
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	BG�ʐݒ���s��
 *
 *	@param	data	�`��V�X�e���f�[�^
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void setBg( IMC_DRAW_DATA* data )
{
	
	{	// ���C���ʃt���[��1
		GF_BGL_BGCNT_HEADER  TextBgCntDat = {
			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xf800, GX_BG_CHARBASE_0x00000, GX_BG_EXTPLTT_01,
			0, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( data->BG_Ini, GF_BGL_FRAME1_M, &TextBgCntDat, GF_BGL_MODE_TEXT );
		GF_BGL_ClearCharSet( GF_BGL_FRAME1_M, 32, 0, HEAPID_IMAGECLIP_DRAW );
		GF_BGL_ScrClear( data->BG_Ini, GF_BGL_FRAME1_M );
	}
	
	{	// ���C���ʃt���[��2
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xf000, GX_BG_CHARBASE_0x04000, GX_BG_EXTPLTT_01,
			2, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( data->BG_Ini, GF_BGL_FRAME2_M, &TextBgCntDat, GF_BGL_MODE_TEXT );
		GF_BGL_ClearCharSet( GF_BGL_FRAME2_M, 32, 0, HEAPID_IMAGECLIP_DRAW );
		GF_BGL_ScrClear( data->BG_Ini, GF_BGL_FRAME2_M );
	}

	{	// ���C���ʃt���[��3
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, -(IMC_LBOX_AREA_Y + IMC_LBOX_AREA_HEIGHT), 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xe800, GX_BG_CHARBASE_0x08000, GX_BG_EXTPLTT_01,
			3, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( data->BG_Ini, GF_BGL_FRAME3_M, &TextBgCntDat, GF_BGL_MODE_TEXT );
		GF_BGL_ClearCharSet( GF_BGL_FRAME3_M, 32, 0, HEAPID_IMAGECLIP_DRAW );
		GF_BGL_ScrClear( data->BG_Ini, GF_BGL_FRAME3_M );
	}

	// �T�u�ʐݒ�
	{	// �T�u�ʃt���[��0
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0x7800, GX_BG_CHARBASE_0x00000, GX_BG_EXTPLTT_01,
			1, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( data->BG_Ini, GF_BGL_FRAME0_S, &TextBgCntDat, GF_BGL_MODE_TEXT );
		GF_BGL_ClearCharSet( GF_BGL_FRAME0_S, 32, 0, HEAPID_IMAGECLIP_DRAW );
		GF_BGL_ScrClear( data->BG_Ini, GF_BGL_FRAME0_S );
	}

	{	// ���C���ʃt���[��3
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0x7000, GX_BG_CHARBASE_0x04000, GX_BG_EXTPLTT_01,
			0, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( data->BG_Ini, GF_BGL_FRAME1_S, &TextBgCntDat, GF_BGL_MODE_TEXT );
		GF_BGL_ClearCharSet( GF_BGL_FRAME1_S, 32, 0, HEAPID_IMAGECLIP_DRAW );
		GF_BGL_ScrClear( data->BG_Ini, GF_BGL_FRAME1_S );
	}
	// �E�B���h�E�}�X�NBG�̐ݒ�
//	IMC_DRAW_WndMaskNormalSet();
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	BG�ʐݒ��j������
 *
 *	@param	data	�`��V�X�e���f�[�^
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void delBg( IMC_DRAW_DATA* data )
{
	GF_BGL_BGControlExit( data->BG_Ini, GF_BGL_FRAME1_M );
	GF_BGL_BGControlExit( data->BG_Ini, GF_BGL_FRAME2_M );
	GF_BGL_BGControlExit( data->BG_Ini, GF_BGL_FRAME3_M );
	GF_BGL_BGControlExit( data->BG_Ini, GF_BGL_FRAME0_S );
	GF_BGL_BGControlExit( data->BG_Ini, GF_BGL_FRAME1_S );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�L�����N�^���\�[�X�f�[�^�쐬
 *
 *	@param	data	�`��f�[�^�\����
 *
 *	@return	none
 *
 * �^�b�`�p�l�������蔻��Ɏg�p���܂�
 *
 */
//-----------------------------------------------------------------------------
static void initCharRes( IMC_DRAW_DATA* data )
{
	data->SWSP_charRes = RESM_Init( IMC_SPRITE_OBJ_CHAR_NUM, HEAPID_IMAGECLIP_DRAW );
	data->SWSP_UPchar = sys_AllocMemory( HEAPID_IMAGECLIP_DRAW,
			sizeof(NNSG2dCharacterData*) * IMC_SPRITE_OBJ_CHAR_NUM );

	memset( data->SWSP_UPchar, 0, sizeof(NNSG2dCharacterData*) * IMC_SPRITE_OBJ_CHAR_NUM );
	
	data->SWSP_UPcharNum = IMC_SPRITE_OBJ_CHAR_NUM;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�L�����N�^���\�[�X�f�[�^�j��
 *
 *	@param	data 
 *
 *	@return
 *
 *
 */
//-----------------------------------------------------------------------------
static void deleteCharRes( IMC_DRAW_DATA* data )
{
	sys_FreeMemoryEz( data->SWSP_UPchar );
	RESM_Delete( data->SWSP_charRes );	
	data->SWSP_UPcharNum = 0;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�Z���A�N�^�[������
 *
 *	@param	data	�`��V�X�e���f�[�^ 
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void initCLACT( IMC_DRAW_DATA* data )
{
	// �L�����N�^�}�l�[�W��������
	{
		CHAR_MANAGER_MAKE init = {
			IMC_CHAR_NUM, 0x8000, 0x4000, HEAPID_IMAGECLIP_DRAW
		};

		InitCharManagerReg(&init, 
				GX_OBJVRAMMODE_CHAR_1D_32K,
				GX_OBJVRAMMODE_CHAR_1D_32K);
	}

	// �p���b�g�}�l�[�W��������
	InitPlttManager(IMC_PLTT_NUM, HEAPID_IMAGECLIP_DRAW);

	// �L�����N�^�ǂݍ��݊J�n�I�t�Z�b�g�ݒ�
	CharLoadStartAll();

	// �p���b�g�ǂݍ��݊J�n�I�t�Z�b�g�ݒ�
	PlttLoadStartAll();

	
	// OAM�}�l�[�W���[�̏�����
	NNS_G2dInitOamManagerModule();


	// �����_���pOAM�}�l�[�W���쐬
	REND_OAMInit( 
	0, 124,		// ���C�����OAM�Ǘ��̈�
	0, 31,		// ���C����ʃA�t�B���Ǘ��̈�
	0, 124,		// �T�u���OAM�Ǘ��̈�
	0, 31,		// �T�u��ʃA�t�B���Ǘ��̈�
	HEAPID_IMAGECLIP_DRAW);
	
	// �Z���A�N�^�[�Z�b�g�쐬
	data->clactSet = CLACT_U_SetEasyInit( IMC_CELL_NUM, 
			&data->renddata,
			HEAPID_IMAGECLIP_DRAW );
	CLACT_U_SetSubSurfaceMatrix( &data->renddata, MAIN_SURFACE_X, IMC_CLACT_SUB_SURFACE_Y );

	// ���\�[�X�}�l�[�W���̍쐬
	// �L�����N�^
	data->resMan[ CLACT_U_CHAR_RES ] = CLACT_U_ResManagerInit( 
			IMC_CHAR_NUM,
			CLACT_U_CHAR_RES,
			HEAPID_IMAGECLIP_DRAW );
	// �p���b�g
	data->resMan[ CLACT_U_PLTT_RES ] = CLACT_U_ResManagerInit( 
			IMC_PLTT_NUM,
			CLACT_U_PLTT_RES,
			HEAPID_IMAGECLIP_DRAW );
	// �Z��
	data->resMan[ CLACT_U_CELL_RES ] = CLACT_U_ResManagerInit( 
			IMC_CELL_NUM,
			CLACT_U_CELL_RES,
			HEAPID_IMAGECLIP_DRAW );
	// �Z���A�j��
	data->resMan[ CLACT_U_CELLANM_RES ] = CLACT_U_ResManagerInit( 
			IMC_CELL_NUM,
			CLACT_U_CELLANM_RES,
			HEAPID_IMAGECLIP_DRAW );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�Z���A�N�^�[�j��
 *
 *	@param	data	�`��V�X�e���f�[�^
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void deleteCLACT( IMC_DRAW_DATA* data )
{
	// �A�N�^�[�Z�b�g�j��
	CLACT_DestSet(data->clactSet);

	// ���\�[�X�}�l�[�W���j��
	{
		int i;
		for(i=0; i<IMC_DRAW_USE_RES_NUM; i++){
			CLACT_U_ResManagerDelete(data->resMan[i]);
		}
	}
	// �L�����N�^�}�l�[�W���j��
	DeleteCharManager();

	// �p���b�g�}�l�[�W���j��
	DeletePlttManager();
	
	// �����_���[���LOAM�}�l�[�W���j��
	REND_OAM_Delete();	
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�Z���A�N�^�[�`��
 *
 *	@param	data 
 *
 *	@return
 *
 *
 */
//-----------------------------------------------------------------------------
static void drawCLACT( IMC_DRAW_DATA* data )
{
	// �`��
	CLACT_Draw(data->clactSet);
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�A�N�Z�T�����\�[�X�t�@�C���ǂݍ���
 *
 *	@param	drawData	�`��V�X�e���f�[�^
 *	@param	loadData	�ǂݍ��݃f�[�^�i�[��
 *
 *	@return	none
 *
 * �p���b�g�͌Œ�̗v�f���ʒu�ɓo�^����̂ň�ԍŏ��ɕK��
 * �A�N�Z�T���̃f�[�^��ǂݍ���ł�������
 * 
 *
 */
//-----------------------------------------------------------------------------
static void loadAcceData( IMC_DRAW_DATA* drawData, IMC_DRAW_LOADRES_DATA* loadData )
{
	int i;			// ���[�v�p
	int cont_id;	// �f�[�^�o�^��ID
	void* buff;

	// �A�N�Z�T���p�f�[�^�ǂݍ���
	for(i=0; i<IMC_ACCE_MAX; i++ ){
		// �L�����N�^�f�[�^�擾
		buff = ArcUtil_Load(ARC_IMAGECLIP_GRA,
				IMC_ACCE_ARC_NO_GET( i ),
				FALSE, HEAPID_IMAGECLIP_DRAW, ALLOC_BOTTOM);

		GF_ASSERT( buff );

		// �Ǘ�ID�擾
		cont_id = IMC_ACCE_CHAR_CONT_ID(i);

		// ���\�[�X�}�l�[�W���ɓo�^
		// �A���p�b�N��̃f�[�^��o�^
		loadData->SWSP_charTbl[ cont_id ].res_file = IMC_DRAW_SetCharData( drawData, buff, i );
		
		// �X�v���C�g�`��V�X�e���|�C���^�ݒ�
		loadData->SWSP_charTbl[ cont_id ].s_sys = drawData->SWSP_drawSys;
	}

	// �p���b�g�f�[�^�o�^
	buff = ArcUtil_Load(ARC_IMAGECLIP_GRA,
			IMC_DRAW_ACCESSORIE_PLTT_ARC, FALSE, HEAPID_IMAGECLIP_DRAW, ALLOC_BOTTOM);
	
	// ���\�[�X�}�l�[�W���ɓo�^
	RESM_AddResNormal( loadData->SWSP_plttRes, buff, IMC_DRAW_ACCESSORIE_PLTT_ID );		
	
	// �A���p�b�N
	NNS_G2dGetUnpackedPaletteData( buff,
			&loadData->SWSP_plttTbl[ IMC_DRAW_ACCESSORIE_PLTT_ID ].res_file );

	// �`��V�X�e���f�[�^
	loadData->SWSP_plttTbl[ IMC_DRAW_ACCESSORIE_PLTT_ID ].s_sys = drawData->SWSP_drawSys;

	// �ǂݍ��݂���
	loadData->SWSP_plttTbl[ IMC_DRAW_ACCESSORIE_PLTT_ID ].load_num = IMC_DRAW_ACCESSORIE_PLTT_NUM;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	BG�T���l�C���p���\�[�X�f�[�^�ǂݍ���
 *
 *	@param	drawData	�`��V�X�e���f�[�^
 *	@param	loadData	�ǂݍ��݃f�[�^�i�[��
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void loadBGThumData( IMC_DRAW_DATA* drawData, IMC_DRAW_LOADRES_DATA* loadData )
{
	int i;		// ���[�v�p
	void* buff;
	int num;		// �o�^��

	// �A�N�Z�T���p�f�[�^�ǂݍ���
	for(i=0; i<IMC_BG_RIGHT_MAX; i++ ){
		// �L�����N�^�f�[�^�擾
		buff = ArcUtil_Load(ARC_IMAGECLIP_GRA,
				IMC_BG_THUMB_CG_ARC_GET( i ),
				FALSE, HEAPID_IMAGECLIP_DRAW, ALLOC_BOTTOM);

		num = IMC_BG_THUMB_CHAR_CONT_ID(i);

		// �A���p�b�N��̃f�[�^��o�^
		loadData->SWSP_charTbl[ num ].res_file = IMC_DRAW_SetCharData( drawData, buff, num );
		
		// �X�v���C�g�`��V�X�e���|�C���^�ݒ�
		loadData->SWSP_charTbl[ num ].s_sys = drawData->SWSP_drawSys;

		
		num = IMC_BG_THUMB_PLTT_CONT_ID(i);
		
		// �p���b�g�f�[�^�o�^
		buff = ArcUtil_Load(ARC_IMAGECLIP_GRA,
				IMC_BG_RIGHT_CL_ARC_GET(i), FALSE, HEAPID_IMAGECLIP_DRAW, ALLOC_BOTTOM);

		// ���\�[�X�}�l�[�W���ɓo�^
		RESM_AddResNormal( loadData->SWSP_plttRes, buff, num );				

		// �A���p�b�N
		NNS_G2dGetUnpackedPaletteData( buff,
				&loadData->SWSP_plttTbl[ num ].res_file );
		GF_ASSERT_MSG( loadData->SWSP_plttTbl[ num ].res_file, "thum %d", IMC_BG_RIGHT_CL_ARC_GET(i) );

		// �`��V�X�e���f�[�^
		loadData->SWSP_plttTbl[ num ].s_sys = drawData->SWSP_drawSys;

		// �ǂݍ��݂���
		loadData->SWSP_plttTbl[ num ].load_num = IMC_BG_COLOR_NUM;
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�A�N�Z�T���p���b�g�I�t�Z�b�g�e�[�u���쐬
 *
 *	@param	data	�`��V�X�e���f�[�^
 *	@param	heap	�q�[�vID
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void initAccePlttOfs( IMC_DRAW_DATA* data, int heap )
{
//	data->accePlttOfsTbl = plttOfs;
	data->accePlttOfsTbl = ArcUtil_Load( ARC_IMAGECLIP_GRA, IMC_ACCESSORIE_PLTT_LINK, FALSE, heap, ALLOC_TOP );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�A�N�Z�T���p���b�g�I�t�Z�b�g�f�[�^�j��
 *
 *	@param	data	�`��V�X�e���f�[�^
 *
 *	@return
 *
 *
 */
//-----------------------------------------------------------------------------
static void deleteAccePlttOfs( IMC_DRAW_DATA* data )
{
	sys_FreeMemoryEz( data->accePlttOfsTbl );
	data->accePlttOfsTbl = NULL;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�|�P�����`��V�X�e���̏�����
 *
 *	@param	drawData		�i�[��
 *	@param	heap			�q�[�vID
 *	@param	tex_size		�e�N�X�`���T�C�Y
 *	@param	pltt_size		�p���b�g�T�C�Y
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void initSoftSprite( IMC_DRAW_DATA* drawData, int heap, int tex_size, int pltt_size )
{
	NNSGfdTexKey	texKey;
	NNSGfdPlttKey	plttKey;

	// �|�P�����f�[�^�]���̈��Vram���m�ہ��]���A�h���X�ƃT�C�Y��ݒ�
	drawData->SSM_drawSys = SoftSpriteInit( heap );	
	texKey = NNS_GfdAllocTexVram(tex_size, FALSE, 0);
	plttKey = NNS_GfdAllocPlttVram(pltt_size, FALSE, NNS_GFD_ALLOC_FROM_LOW);
	SoftSpriteTextureTransParamSet( 
			drawData->SSM_drawSys,
			NNS_GfdGetTexKeyAddr(texKey),
			NNS_GfdGetTexKeySize(texKey) );
	SoftSpritePaletteTransParamSet( 
			drawData->SSM_drawSys,
			NNS_GfdGetPlttKeyAddr(plttKey),
			NNS_GfdGetPlttKeySize(plttKey) );

	drawData->SSM_DrawFlag = TRUE;
/*
	OS_Printf( 
			" addr %x size %x \n",
			NNS_GfdGetTexKeyAddr(texKey),
			NNS_GfdGetTexKeySize(texKey) );
	OS_Printf( 
			" addr %x size %x \n ",
			NNS_GfdGetPlttKeyAddr(plttKey),
			NNS_GfdGetPlttKeySize(plttKey) );
//*/
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�|�P�����`��V�X�e���̔j��
 *
 *	@param	drawData	
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void deleteSoftSprite( IMC_DRAW_DATA* drawData )
{
	// �|�P�����`��X�v���C�g�f�[�^�j��
	SoftSpriteEnd( drawData->SSM_drawSys );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	SWSP�̃��\�[�X�o�^�f�[�^���������m��
 *
 *	@param	loadData		�o�^�f�[�^�̃������m�ې�
 *	@param	char_num		�L�����N�^�f�[�^��
 *	@param	pltt_num		�p���b�g�f�[�^��
 *	@param	heap			�g�p�q�[�v
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void loadSWSPResDataAllocMemory( IMC_DRAW_LOADRES_DATA* loadData, int char_num, int pltt_num, int heap )
{
	// �o�^�f�[�^�̈���쐬
	// �L�����N�^
	loadData->SWSP_charTbl = sys_AllocMemory( heap, sizeof(SWSP_CHARDATA) * char_num );
	memset( loadData->SWSP_charTbl, 0, sizeof(SWSP_CHARDATA) * char_num );
	loadData->SWSP_charRes = RESM_Init( char_num, heap );	// �A���p�b�N�O�̃f�[�^�i�[��
	loadData->SWSP_charNum = char_num;

	// �p���b�g
	loadData->SWSP_plttTbl = sys_AllocMemory( heap, sizeof(SWSP_PLTTDATA) * pltt_num );
	memset( loadData->SWSP_plttTbl, 0, sizeof(SWSP_PLTTDATA) * pltt_num );
	loadData->SWSP_plttRes = RESM_Init( pltt_num, heap );	// �A���p�b�N�O�̃f�[�^�i�[��
	loadData->SWSP_plttNum = pltt_num;
	
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	SWSP�̃��\�[�X�o�^�f�[�^��������j��
 *
 *	@param	loadData		�j������f�[�^
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void loadSWSPResDataDeleteMemory( IMC_DRAW_LOADRES_DATA* loadData )
{
	// �쐬�f�[�^�j��
	// ���\�[�X�j��
	if(loadData->SWSP_charRes){
		RESM_Delete( loadData->SWSP_charRes );
		loadData->SWSP_charRes = NULL;
	}
	if(loadData->SWSP_plttRes){
		RESM_Delete( loadData->SWSP_plttRes );
		loadData->SWSP_plttRes = NULL;
	}
	
	// �o�^�f�[�^�j��
	sys_FreeMemoryEz( loadData->SWSP_charTbl );
	loadData->SWSP_charTbl = NULL;
	sys_FreeMemoryEz( loadData->SWSP_plttTbl );
	loadData->SWSP_plttTbl = NULL;
}
