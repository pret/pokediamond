//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		imc_bg.c
 *	@brief		BG�I�u�W�F�N�g
 *	@author		tomoya takahashi
 *	@data		2005.09.29
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

#include <string.h>
#include "system.h"
#include "bg_system.h"
#include "include/system/arc_util.h"
#include "system/lib_pack.h"

#define	__IMC_BG_H_GLOBAL
#include "include/application/imageClip/imc_bg.h"

//-----------------------------------------------------------------------------
/**
 *					�萔�錾
*/
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
/**
 *					�\���̐錾
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	
//	BG�X�N���[���^�X�N
//	
//=====================================
typedef struct {
	IMC_BG* imc_bg;			// ���\�����Ă���BG
	IMC_BG_ADD	new_bg;		// �V����BG�̓o�^�f�[�^
	BOOL*	end_flg;		// �I���t���O

	int count;
	int add_x;
	int add_y;

	int ret_scr_x;		// ����Scroll�ʒu
	int ret_scr_y;		// ����Scroll�ʒu
} IMC_BG_SCR_TASK;

//-------------------------------------
//	V�u�����N�@�L�����N�^�f�[�^�]���^�X�N
//=====================================
typedef struct {
	GF_BGL_INI* ini;
	NNSG2dCharacterData* p_char;
	void* p_buff;	
	int bg_frame;
	int char_ofs;
} IMC_BG_CHARACTER_TRANS;

//-------------------------------------
//	V�u�����N�@�p���b�g�f�[�^�]���^�X�N
//=====================================
typedef struct {
	NNSG2dPaletteData* p_pltt;
	void* p_buff;	
	int pltype;	// �p���b�g�]����
	int ofs;
	int size;
} IMC_BG_PALETTE_TRANS;



//-----------------------------------------------------------------------------
/**
 *					�v���g�^�C�v�錾
*/
//-----------------------------------------------------------------------------
static void imc_bg_set_screen_charofs( const NNSG2dScreenData* scrn, int char_offs );

static void imc_bg_addCore( IMC_BG_ADD* add, int* scrn_width, int* scrn_height );

static void imc_bg_scrTsk( TCB_PTR tcb, void* work );

static void imc_bg_scrnChg( GF_BGL_INI* bg_ini, int frame, const NNSG2dScreenData* scrn, int width, int height, int x, int y, int char_offs, int pltt_offs );

static void imc_bg_charTransReq( u32 fileIdx, u32 dataIdx, GF_BGL_INI* bgl, u32 frm, u32 offs, u32 heapID );
static void imc_bg_plttTransReq( u32 fileIdx, u32 dataIdx, PALTYPE palType, u32 offs, u32 transSize, u32 heapID );
static void imc_bg_charTransTsk( TCB_PTR tcb, void* p_work );
static void imc_bg_plttTransTsk( TCB_PTR tcb, void* p_work );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	BG�f�[�^�̓o�^ & �V�K�ύX
 *
 *	@param	obj		BG�I�u�W�F
 *	@param	add		�o�^�f�[�^
 *	@param	heap	�g�p����q�[�v
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_BG_MakaObj( IMC_BG* obj, IMC_BG_ADD* add )
{
	// �f�[�^�ݒ�
	obj->bg_ini		= add->bg_ini;
	obj->x			= add->x / 8;	
	obj->y			= add->y / 8;	
	obj->frame		= add->frame;	
	obj->pltt_offs	= add->pltt_offs;
	obj->pltt_num	= add->pltt_num;
	obj->char_offs	= add->char_offs;
	obj->arc_file	= add->arc_file;
	obj->scrn_arc	= add->scrn_arc;
	
	
	// BG�ݒ�
	imc_bg_addCore( add, &obj->width_char, &obj->height_char );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	BG�f�[�^�̔j��
 *
 *	@param	obj		BG�I�u�W�F
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_BG_DeleteObj( IMC_BG* obj )
{
	GF_BGL_ScrClear( obj->bg_ini, obj->frame );	

	memset( obj, 0, sizeof( IMC_BG ) );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	BG�A�j���[�V����������
 *
 *	@param	anm		�A�j��BG�f�[�^�i�[��
 *	@param	init	�������f�[�^
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_BG_AnmInit( IMC_BG_ANM* anm, IMC_BG_ANM_INIT* init )
{
	anm->bg			= init->bg;
	anm->scrn_arc01	= init->scrn_arc;
	anm->timing		= init->timing;
	anm->count		= 0;
	anm->scrn_no	= 0;
	anm->heap		= init->heap;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�A�j���[�V�����X�V
 *
 *	@param	anm		�A�j���[�V����BG
 *	@param	frame	�i�߂�t���[���l
 *	
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_BG_Anm( IMC_BG_ANM* anm, int frame )
{
	NNSG2dScreenData*	scrn;
	void*				scrn_buf;
	int					arc_id;
	
	anm->count += frame;

	if( anm->count > anm->timing ){
		anm->count = 0;

		// �X�N���[���t�@�C���I��
		if( anm->scrn_no == 0 ){
			arc_id = anm->scrn_arc01;
			anm->scrn_no = 1;
		}else{
			arc_id = anm->bg->scrn_arc;
			anm->scrn_no = 0;
		}
		
		// �X�N���[���f�[�^�����o��
		scrn_buf = ArcUtil_ScrnDataGet(anm->bg->arc_file, arc_id,
				FALSE, &scrn, anm->heap);

		// �X�N���[���f�[�^�]��
		imc_bg_scrnChg( anm->bg->bg_ini, anm->bg->frame, scrn,
				anm->bg->width_char, anm->bg->height_char,
				anm->bg->x, anm->bg->y,
				anm->bg->char_offs, anm->bg->pltt_offs );

		sys_FreeMemoryEz( scrn_buf );	
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	BG�A�j�����I��������
 *
 *	@param	anm		�A�j���[�V����BG
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_BG_AnmDelete( IMC_BG_ANM* anm )
{
	NNSG2dScreenData*	scrn;
	void*				scrn_buf;

	// �G���f�t�H�̊G�ɂ��ă������N���[��
	// �X�N���[���f�[�^�����o��
	scrn_buf = ArcUtil_ScrnDataGet(anm->bg->arc_file, anm->bg->scrn_arc,
			FALSE, &scrn, anm->heap);

	// �X�N���[���f�[�^�]��
	imc_bg_scrnChg( anm->bg->bg_ini, anm->bg->frame, scrn,
			anm->bg->width_char, anm->bg->height_char,
			anm->bg->x, anm->bg->y,
			anm->bg->char_offs, anm->bg->pltt_offs );

	sys_FreeMemoryEz( scrn_buf );	

	memset( anm, 0, sizeof(IMC_BG_ANM) );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	BG��Scroll�����܂��B
 *
 *	@param	obj		���\�����Ă���BG
 *	@param	scr_bg	�X�N���[����BG
 *	@param	scr_dis	�X�N���[��������l
 *	@param	scr_sync�X�N���[���Ɏg���V���N��
 *	@param	end_flg	�I�����m�t���O
 *
 *	@return	none
 *
 * �ŏI�I�ɂ�scr_bg�̕���BG����ʂɏo��悤�ɂȂ�܂�
 *
 * �܂�BG�f�[�^�z�u��
 * 256x256��
 * ����128~255�̕����ɃL�����N�^������悤�ɂȂ��Ă���K�v������܂��B
 *
 */
//-----------------------------------------------------------------------------
void IMC_BG_ScrollReq( IMC_BG* obj, IMC_BG_ADD* scr_bg, int scr_x, int scr_y, int scr_sync, BOOL* end_flg )
{
	IMC_BG_SCR_TASK* scr_tsk;
	TCB_PTR tcb;

	// �^�X�N�o�^
	tcb = PMDS_taskAdd( imc_bg_scrTsk, sizeof(IMC_BG_SCR_TASK), 0, HEAPID_IMAGECLIP_DATA );
	
	// ���[�N�擾
	scr_tsk = TCB_GetWork( tcb );

	// �e�f�[�^�ݒ�
	scr_tsk->imc_bg = obj;
	scr_tsk->new_bg = *scr_bg;
	scr_tsk->end_flg = end_flg;
	
	scr_tsk->count	= scr_sync;
	scr_tsk->add_x	= scr_x / scr_sync;
	scr_tsk->add_y	= scr_y / scr_sync;
	scr_tsk->ret_scr_x = GF_BGL_ScrollGetX( obj->bg_ini, obj->frame );
	scr_tsk->ret_scr_y = GF_BGL_ScrollGetY( obj->bg_ini, obj->frame );

	// �X�N���[�����āA��ʂɏo���G��z�u
	scr_bg->char_offs = IMC_BG_SCR_OFS;
	scr_bg->pltt_offs = IMC_BG_SCR_PLTT_OFS;
	scr_bg->x		  -= scr_x;
	scr_bg->y		  -= scr_y;
	scr_bg->heap	= HEAPID_IMAGECLIP_DRAW;
	imc_bg_addCore( scr_bg, NULL, NULL );
}


//----------------------------------------------------------------------------
/**
 *
 *	@brief	�X�N���[���f�[�^�̃L�����N�^�l�[���̒l���I�t�Z�b�g�����炷
 *
 *	@param	scrn			�X�N���[���f�[�^
 *	@param	char_offs		�L�����N�^�I�t�Z�b�g	�L�����N�^�P��
 *
 *	@return	none
 *
 * �L�����N�^�l�[���ő�l�`�F�b�N�����Ă��Ȃ��̂Œ��ӂ��Ă�������
 *
 */
//-----------------------------------------------------------------------------
static void imc_bg_set_screen_charofs( const NNSG2dScreenData* scrn, int char_offs )
{
	int i;							// ���[�v�p
	u16* scrndata;					// �X�N���[���f�[�^
	int size = scrn->szByte / 2;	// ���[�v��	�Q=2byte
	
	// �X�N���[���f�[�^���
	scrndata = (u16*)scrn->rawData;

	for(i=0; i<size; i++){

		scrndata[ i ] += char_offs;
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	��ʂɊG���o��܂ł̏������܂Ƃ߂��֐�
 *
 *	@param	add				BG�o�^�f�[�^
 *	@param	scrn_width		�X�N���[���f�[�^�̕��i�[��i�L�����N�^�P�ʁj
 *	@param	scrn_height		�X�N���[���f�[�^�̍����i�[��i�L�����N�^�P�ʁj
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void imc_bg_addCore( IMC_BG_ADD* add, int* scrn_width, int* scrn_height )
{
	int pltype;	// �p���b�g�]����
	NNSG2dScreenData* scrn;
	void* scrn_buf;
	int height, width;
	int x, y;

	x = add->x / 8;
	y = add->y / 8;
	
	// �L�����N�^�f�[�^�]��
	imc_bg_charTransReq( add->arc_file, add->char_arc,
			add->bg_ini, add->frame, add->char_offs, add->heap);

	// �p���b�g�f�[�^�]��
	if(add->frame < GF_BGL_FRAME0_S){	
		pltype = PALTYPE_MAIN_BG;
	}else{
		pltype = PALTYPE_SUB_BG;
	}
	imc_bg_plttTransReq( add->arc_file, add->pltt_arc,
			pltype, add->pltt_offs*32, add->pltt_num*32,  add->heap );

	// �X�N���[���f�[�^�����o��
	scrn_buf = ArcUtil_ScrnDataGet(add->arc_file, add->scrn_arc,
			FALSE, &scrn, add->heap);

	// ���@�������
	width = scrn->screenWidth/8;
	height = scrn->screenHeight/8;
	
	// �X�N���[���f�[�^�]��
	imc_bg_scrnChg( add->bg_ini, add->frame, scrn, width, height, x, y, add->char_offs, add->pltt_offs );

	sys_FreeMemoryEz( scrn_buf );	

	if(scrn_width){
		*scrn_width = width;
	}
	if(scrn_height){
		*scrn_height = height;
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�X�N���[���^�X�N
 *
 *	@param	tcb			�^�X�N�I�u�W�F
 *	@param	work		�f�[�^
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void imc_bg_scrTsk( TCB_PTR tcb, void* work )
{
	IMC_BG_SCR_TASK* task = work;

	task->count --;
	
	if( task->count >= 0 ){
		GF_BGL_ScrollReq( task->imc_bg->bg_ini, task->imc_bg->frame, GF_BGL_SCROLL_X_DEC, task->add_x );

		GF_BGL_ScrollReq( task->imc_bg->bg_ini, task->imc_bg->frame, GF_BGL_SCROLL_Y_DEC, task->add_y );
	}else{
		GF_BGL_ScrollReq( task->imc_bg->bg_ini, task->imc_bg->frame, GF_BGL_SCROLL_X_SET, task->ret_scr_x );

		GF_BGL_ScrollReq( task->imc_bg->bg_ini, task->imc_bg->frame, GF_BGL_SCROLL_Y_SET, task->ret_scr_y );

		IMC_BG_MakaObj( task->imc_bg, &task->new_bg );

		if( task->end_flg ){
			*task->end_flg = TRUE;
		}
		
		// �I��
		PMDS_taskDel( tcb );
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�X�N���[���f�[�^�ݒ�֐�
 *
 *	@param	bg_ini		BG�V�X�e���f�[�^
 *	@param	frame		BG�t���[��
 *	@param	scrn		�X�N���[���f�[�^
 *	@param	width		��
 *	@param	height		����
 *	@param	x			�����W
 *	@param	y			�����W
 *	@param	chr_offs	�L�����N�^�I�t�Z�b�g
 *	@param	pltt_offs	�p���b�g�I�t�Z�b�g
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void imc_bg_scrnChg( GF_BGL_INI* bg_ini, int frame, const NNSG2dScreenData* scrn, int width, int height, int x, int y, int char_offs, int pltt_offs )
{
	// �L�����N�^�I�t�Z�b�g�ݒ�
	imc_bg_set_screen_charofs( scrn, char_offs );
	
	// ��������
	GF_BGL_ScrWriteExpand(
				bg_ini, frame,
				x, y,
				width, height,
				scrn->rawData,
				0, 0,
				width, height );
	
	GF_BGL_ScrPalChange( bg_ini, frame,
				x, y,
				width,height,
			pltt_offs);
	
	GF_BGL_LoadScreenV_Req(bg_ini, frame );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�L�����N�^�f�[�^�]�����N�G�X�g
 *
 *	@param	fileIdx		�A�[�J�C�u�t�@�C���C���f�b�N�X
 *	@param	dataIdx		�f�[�^�C���f�b�N�X
 *	@param	bgl			BG�f�[�^
 *	@param	frm			�ڰуi���o�[
 *	@param	offs		�I�t�Z�b�g
 *	@param	heapID		�q�[�v
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void imc_bg_charTransReq( u32 fileIdx, u32 dataIdx, GF_BGL_INI* bgl, u32 frm, u32 offs, u32 heapID )
{
	IMC_BG_CHARACTER_TRANS* p_tw;

	p_tw = sys_AllocMemory( heapID, sizeof(IMC_BG_CHARACTER_TRANS) );
	memset( p_tw, 0, sizeof(IMC_BG_CHARACTER_TRANS) );

	// �L�����N�^�f�[�^�ǂݍ���
	p_tw->p_buff = ArcUtil_CharDataGet( fileIdx, dataIdx, FALSE, &p_tw->p_char, heapID );

	// �]���f�[�^�i�[
	p_tw->ini = bgl;
	p_tw->bg_frame = frm;
	p_tw->char_ofs = offs;

	// �^�X�N�o�^
	VWaitTCB_Add( imc_bg_charTransTsk, p_tw, 128 );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�p���b�g�f�[�^�]�����N�G�X�g
 *
 *	@param	fileIdx		�A�[�J�C�u�t�@�C���C���f�b�N�X
 *	@param	dataIdx		�f�[�^�C���f�b�N�X
 *	@param	palType		�p���b�g�]����
 *	@param	offs		�I�t�Z�b�g
 *	@param	transSize	�]��size
 *	@param	heapID		�q�[�v
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void imc_bg_plttTransReq( u32 fileIdx, u32 dataIdx, PALTYPE palType, u32 offs, u32 transSize, u32 heapID )
{
	IMC_BG_PALETTE_TRANS* p_tw;

	p_tw = sys_AllocMemory( heapID, sizeof(IMC_BG_PALETTE_TRANS) );
	memset( p_tw, 0, sizeof(IMC_BG_PALETTE_TRANS) );

	// �L�����N�^�f�[�^�ǂݍ���
	p_tw->p_buff = ArcUtil_PalDataGet( fileIdx, dataIdx, &p_tw->p_pltt, heapID );

	// �]���f�[�^�i�[
	p_tw->pltype = palType;
	p_tw->ofs = offs;
	p_tw->size = transSize;

	// �^�X�N�o�^
	VWaitTCB_Add( imc_bg_plttTransTsk, p_tw, 128 );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�L�����N�^�f�[�^�]���^�X�N
 *
 *	@param	tcb
 *	@param	p_work 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void imc_bg_charTransTsk( TCB_PTR tcb, void* p_work )
{
	IMC_BG_CHARACTER_TRANS* p_tw = p_work;


	DC_FlushRange( p_tw->p_char->pRawData, p_tw->p_char->szByte );
	GF_BGL_LoadCharacter( p_tw->ini, p_tw->bg_frame, 
			p_tw->p_char->pRawData, p_tw->p_char->szByte, p_tw->char_ofs );

	// ���������
	TCB_Delete( tcb );
	sys_FreeMemoryEz( p_tw->p_buff );
	sys_FreeMemoryEz( p_tw );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�p���b�g�f�[�^�]���^�X�N
 *
 *	@param	tcb
 *	@param	p_work 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void imc_bg_plttTransTsk( TCB_PTR tcb, void* p_work )
{
	IMC_BG_PALETTE_TRANS* p_tw = p_work;


	DC_FlushRange( p_tw->p_pltt->pRawData, p_tw->size );

	if( p_tw->pltype == PALTYPE_MAIN_BG ){
		GX_LoadBGPltt( p_tw->p_pltt->pRawData, p_tw->ofs, p_tw->size );
	}else if( p_tw->pltype == PALTYPE_SUB_BG ){
		GXS_LoadBGPltt( p_tw->p_pltt->pRawData, p_tw->ofs, p_tw->size );
	}

	// ���������
	TCB_Delete( tcb );
	sys_FreeMemoryEz( p_tw->p_buff );
	sys_FreeMemoryEz( p_tw );
}
