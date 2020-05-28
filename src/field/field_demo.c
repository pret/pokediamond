//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		field_demo.c
 *	@brief		�t�B�[���h��ł̊ȒP�ȃf������
 *	@author		tomoya takahashi	
 *	@data		2006.04.17
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

#include "common.h"

#include "include/system/swsprite.h"
#include "include/system/arc_util.h"
#include "demo_climax.naix"
#include "fieldmap.h"
#include "fieldmap_work.h"
#include "fieldsys.h"
#include "motion_bl.h"
#include "field_subscreen.h"
#include "fieldobj_draw_legendpoke.h"
#include "field_3dobj.h"
#include "src/fielddata/eventdata/zone_d05r0114evc.h"
#include "field_light.h"

#include "system/snd_tool.h"

#define	__FIELD_DEMO_H_GLOBAL
#include "field_demo.h"

//-----------------------------------------------------------------------------
/**
 *					�R�[�f�B���O�K��
 *		���֐���
 *				�P�����ڂ͑啶������ȍ~�͏������ɂ���
 *		���ϐ���
 *				�E�ϐ�����
 *						const�ɂ� c_ ��t����
 *						static�ɂ� s_ ��t����
 *						�|�C���^�ɂ� p_ ��t����
 *						�S�č��킳��� csp_ �ƂȂ�
 *				�E�O���[�o���ϐ�
 *						�P�����ڂ͑啶��
 *				�E�֐����ϐ�
 *						�������Ɓh�Q�h�Ɛ������g�p���� �֐��̈���������Ɠ���
*/
//-----------------------------------------------------------------------------
#ifdef PM_DEBUG
//#define FIELD_DEMO_DEBUG		// �f�o�b�N�^�X�N���܂킷���H
#endif // PM_DEBUG 

#ifdef FIELD_DEMO_DEBUG
static int FIELD_DEMO_DEBUG_STOP = 0;
static TCB_PTR pFieldDemoDebugTcb = NULL;
static void FieldDemoDebugTcb( TCB_PTR tcb, void* p_work );
static void FieldDemoDebugStart( void );
static void FieldDemoDebugEnd( void );
#endif // FIELD_DEMO_DEBUG


#define USE_HEAPID		( HEAPID_FIELD )


//-------------------------------------
//	����`
//=====================================
#define FLD_DEMO_LEGENDEFF_SND_00	( SEQ_SE_DP_CLIMAX01 )		// �V���[
#define FLD_DEMO_LEGENDEFF_SND_01	( SEQ_SE_DP_CLIMAX03 )		// �ڂ�[
#define FLD_DEMO_LEGENDEFF_SND_02	( SEQ_SE_DP_CLIMAX06 )		// �҂��[	�t���b�V��
#define FLD_DEMO_LEGENDEFF_SND_03	( SEQ_SE_DP_CLIMAX09 )		// �S�[�S�S�S	��ʗh�炵
#define FLD_DEMO_LEGENDEFF_SND_04	( SEQ_SE_DP_CLIMAX10 )		// �E�B��	
#define FLD_DEMO_LEGENDEFF_SND_05	( SEQ_SE_DP_CLIMAX12 )		// �V���[��

//#define FLD_DEMO_LEGENDEFF_SND_06	( SEQ_SE_DP_CLIMAX16 )		// �v�V���[
#define FLD_DEMO_LEGENDEFF_SND_06	( SEQ_SE_DP_CLIMAX15 )		// �v�V���[




//-----------------------------------------------------------------------------
/**
 * 
 *			�y�f���p���[�V�����u���[�ݒ�֐��z
 * 
 */
//-----------------------------------------------------------------------------
#define FLD_DEMO_MOTIONBL_DRAWDATA_SETUP_TCB_PRI (1024)
//-------------------------------------
//	����V�[�P���X
//=====================================
enum{
	FLD_DEMO_MOTIONBL_SEQ_BGINIT,
	FLD_DEMO_MOTIONBL_SEQ_BLINIT,
	FLD_DEMO_MOTIONBL_SEQ_ENDWAIT,
	FLD_DEMO_MOTIONBL_SEQ_BLEND,
	FLD_DEMO_MOTIONBL_SEQ_BGRESET,
	FLD_DEMO_MOTIONBL_SEQ_END,
};



//-------------------------------------
//	���[�V�����u���[���[�N
//=====================================
typedef struct {
	FIELDSYS_WORK* p_fsys;
	// �ۑ��̈�
	GF_BGL_DISPVRAM vrambank;		// VRAM�o���N�ݒ�
	// ���[�V�����u���[
	MOTION_BL_PTR motion_bl;

	int eva;
	int evb;

	u32 seq;		// �V�[�P���X
} FLD_DEMO_MOTIONBL;

static void FLD_DEMO_MOTIONBL_Init( FLD_DEMO_MOTIONBL* p_data, FIELDSYS_WORK* p_fsys, int eva, int evb );
static void FLD_DEMO_MOTIONBL_Main( FLD_DEMO_MOTIONBL* p_data );
static void FLD_DEMO_MOTIONBL_EndReq( FLD_DEMO_MOTIONBL* p_data );
static u32 FLD_DEMO_MOTIONBL_GetState( const FLD_DEMO_MOTIONBL* cp_data );

static void FLD_DEMO_MOTIONBL_GetNowVramBank( GF_BGL_DISPVRAM* p_vrambank );
static void FLD_DEMO_MOTIONBL_SetUpBnk( void );
static void FLD_DEMO_MOTIONBL_SetUpBGIni( GF_BGL_INI* p_bg );
static void FLD_DEMO_MOTIONBL_SetUpBGIni_Field( GF_BGL_INI* p_bg );
static void FLD_DEMO_MOTIONBL_DeleteBGIni( GF_BGL_INI* p_bgini );
static MOTION_BL_PTR FLD_DEMO_MOTIONBL_MotionBlInit( int eva, int evb );
static void FLD_DEMO_MOTIONBL_MotionBlDelete( FLD_DEMO_MOTIONBL* p_data );
static void FLD_DEMO_MOTIONBL_SetUpDrawSystemReq( FLD_DEMO_MOTIONBL* p_data );
static void FLD_DEMO_MOTIONBL_ResetDrawSystemReq( FLD_DEMO_MOTIONBL* p_data );

static void FLD_DEMO_MOTIONBL_MotionBlDeleteTcb( TCB_PTR tcb, void* p_work );
static void FLD_DEMO_MOTIONBL_SetUpDrawSystemTCB( TCB_PTR tcb, void* p_work );
static void FLD_DEMO_MOTIONBL_ResetDrawSystemTCB( TCB_PTR tcb, void* p_work );


//----------------------------------------------------------------------------
/**
 *	@brief	���[�V�����u���[������
 *
 *	@param	p_data		���[�N
 *	@param	p_fsys		�t�B�[���h�V�X�e��
 *	@param	eva			�`�悳�ꂽ�G�u�����h�W��
 *	@parem	evb			VRAM_C�u�����h�W��
 *	
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void FLD_DEMO_MOTIONBL_Init( FLD_DEMO_MOTIONBL* p_data, FIELDSYS_WORK* p_fsys, int eva, int evb )
{
	p_data->p_fsys = p_fsys;
	FLD_DEMO_MOTIONBL_GetNowVramBank( &p_data->vrambank );
	p_data->seq = 0;
	p_data->eva = eva;
	p_data->evb = evb;
}

//----------------------------------------------------------------------------
/**
 *	@brief	���[�V�����u���[���C��
 *
 *	@param	p_data	���[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void FLD_DEMO_MOTIONBL_Main( FLD_DEMO_MOTIONBL* p_data )
{
	switch( p_data->seq ){
	case FLD_DEMO_MOTIONBL_SEQ_BGINIT:
		FLD_DEMO_MOTIONBL_SetUpDrawSystemReq( p_data );
		p_data->seq++;
		break;
		
	case FLD_DEMO_MOTIONBL_SEQ_BLINIT:
		p_data->motion_bl = FLD_DEMO_MOTIONBL_MotionBlInit( p_data->eva, p_data->evb );
		p_data->seq++;
		break;
		
	case FLD_DEMO_MOTIONBL_SEQ_ENDWAIT:
		break;
		
	case FLD_DEMO_MOTIONBL_SEQ_BLEND:
		FLD_DEMO_MOTIONBL_MotionBlDelete( p_data );
		p_data->seq++;
		break;
		
	case FLD_DEMO_MOTIONBL_SEQ_BGRESET:
		FLD_DEMO_MOTIONBL_ResetDrawSystemReq( p_data );
		p_data->seq++;
		break;
		
	case FLD_DEMO_MOTIONBL_SEQ_END:
		break;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	���[�V�����u���[�I�����N�G�X�g
 *
 *	@param	p_data	���[�N
 *	
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void FLD_DEMO_MOTIONBL_EndReq( FLD_DEMO_MOTIONBL* p_data )
{
	GF_ASSERT( p_data->seq == FLD_DEMO_MOTIONBL_SEQ_ENDWAIT );
	p_data->seq = FLD_DEMO_MOTIONBL_SEQ_BLEND;
}

//----------------------------------------------------------------------------
/**
 *	@brief	���݂̃V�[�P���X���擾
 *
 *	@param	cp_data		���[�N
 *
 *	@return		FLD_DEMO_MOTIONBL_SEQ_BGINIT,
 *	@return     FLD_DEMO_MOTIONBL_SEQ_BLINIT,
 *	@return     FLD_DEMO_MOTIONBL_SEQ_ENDWAIT,
 *	@return     FLD_DEMO_MOTIONBL_SEQ_BLEND,
 *	@return     FLD_DEMO_MOTIONBL_SEQ_BGRESET,
 *	@return     FLD_DEMO_MOTIONBL_SEQ_END,
 */             
//-----------------------------------------------------------------------------
static u32 FLD_DEMO_MOTIONBL_GetState( const FLD_DEMO_MOTIONBL* cp_data )
{
	return cp_data->seq;
}


//----------------------------------------------------------------------------
/**
 *			�y�f���p���[�V�����u���[�ݒ�֐��z
 *	@brief	VRAM�o���N��Ԃ̎擾
 *
 *	@param	p_vrambank	�i�[��
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void FLD_DEMO_MOTIONBL_GetNowVramBank( GF_BGL_DISPVRAM* p_vrambank )
{
	p_vrambank->main_bg			= GX_GetBankForBG();
	p_vrambank->main_bg_expltt	= GX_GetBankForBGExtPltt();
	p_vrambank->sub_bg			= GX_GetBankForSubBG();
	p_vrambank->sub_bg_expltt	= GX_GetBankForSubBGExtPltt();
	p_vrambank->main_obj		= GX_GetBankForOBJ();
	p_vrambank->main_obj_expltt	= GX_GetBankForOBJExtPltt();
	p_vrambank->sub_obj			= GX_GetBankForSubOBJ();
	p_vrambank->sub_obj_expltt	= GX_GetBankForSubOBJExtPltt();
	p_vrambank->teximage		= GX_GetBankForTex();
	p_vrambank->texpltt			= GX_GetBankForTexPltt();
}

//----------------------------------------------------------------------------
/**
 *			�y�f���p���[�V�����u���[�ݒ�֐��z
 *	@brief	climax�f���@�o���N�ݒ�
 */
//-----------------------------------------------------------------------------
static void FLD_DEMO_MOTIONBL_SetUpBnk( void )
{
	GF_BGL_DISPVRAM vramSetTable = {
		GX_VRAM_BG_32_FG,				// ���C��2D�G���W����BG
		GX_VRAM_BGEXTPLTT_NONE,			// ���C��2D�G���W����BG�g���p���b�g
		GX_VRAM_SUB_BG_32_H,			// �T�u2D�G���W����BG
		GX_VRAM_SUB_BGEXTPLTT_NONE,		// �T�u2D�G���W����BG�g���p���b�g
		GX_VRAM_OBJ_NONE,				// ���C��2D�G���W����OBJ
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
 *			�y�f���p���[�V�����u���[�ݒ�֐��z
 *	@brief		BG�R���g���[���쐬
 *	@param		BG�R���g���[���f�[�^
 */
//-----------------------------------------------------------------------------
static void FLD_DEMO_MOTIONBL_SetUpBGIni( GF_BGL_INI* p_bg )
{
	{
		GF_BGL_SYS_HEADER BGsys_data = {
			GX_DISPMODE_GRAPHICS,GX_BGMODE_0,GX_BGMODE_0, GX_BG0_AS_3D
		};
		GF_BGL_InitBG(&BGsys_data);
	}

	GF_Disp_GX_VisibleControl(
		GX_PLANEMASK_BG0, VISIBLE_ON );

	{	// MAIN DISP�i���b�Z�[�W�j
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0x4000, GX_BG_CHARBASE_0x00000, GX_BG_EXTPLTT_23,
			0, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( p_bg, FLD_MBGFRM_FONT, &TextBgCntDat, GF_BGL_MODE_TEXT );
		GF_BGL_ClearCharSet( FLD_MBGFRM_FONT, 32, 0, USE_HEAPID );
		GF_BGL_ScrClear( p_bg, FLD_MBGFRM_FONT );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	���[�V�����u���[��ԃZ�b�g���N�G�X�g
 *
 *	@param	p_data	���[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void FLD_DEMO_MOTIONBL_SetUpDrawSystemReq( FLD_DEMO_MOTIONBL* p_data )
{
//	VIntrTCB_Add( FLD_DEMO_MOTIONBL_SetUpDrawSystemTCB, p_data, FLD_DEMO_MOTIONBL_DRAWDATA_SETUP_TCB_PRI );
	VWaitTCB_Add( FLD_DEMO_MOTIONBL_SetUpDrawSystemTCB, p_data, FLD_DEMO_MOTIONBL_DRAWDATA_SETUP_TCB_PRI );
}

//----------------------------------------------------------------------------
/**
 *	@brief	���[�V�����u���[��ԃ��Z�b�g���N�G�X�g
 *
 *	@param	p_data	���[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void FLD_DEMO_MOTIONBL_ResetDrawSystemReq( FLD_DEMO_MOTIONBL* p_data )
{
//	VIntrTCB_Add( FLD_DEMO_MOTIONBL_ResetDrawSystemTCB, p_data, FLD_DEMO_MOTIONBL_DRAWDATA_SETUP_TCB_PRI );
	VWaitTCB_Add( FLD_DEMO_MOTIONBL_ResetDrawSystemTCB, p_data, FLD_DEMO_MOTIONBL_DRAWDATA_SETUP_TCB_PRI );
}

//----------------------------------------------------------------------------
/**
 *			�y�f���p���[�V�����u���[�ݒ�֐��z
 *	@brief	�`��V�X�e���ݒ�^�X�N
 *
 *	@param	tcb			�^�X�N���[�N
 *	@param	p_work		���[�N
 *	
 *	@return	none
 *
 *	V�u�����N���ԓ��ōs��Ȃ��Ɖ�ʂɂ��݂��o��Ǝv���̂ŁA
 *	�^�X�N�ŐV�����`��ݒ���s��
 */
//-----------------------------------------------------------------------------
static void FLD_DEMO_MOTIONBL_SetUpDrawSystemTCB( TCB_PTR tcb, void* p_work )
{
	FLD_DEMO_MOTIONBL* p_drawsys = p_work;

	// �o���N�ݒ�
	FLD_DEMO_MOTIONBL_SetUpBnk();

	// BG�R���g���[���ݒ�
	FLD_DEMO_MOTIONBL_DeleteBGIni(p_drawsys->p_fsys->bgl);
	FLD_DEMO_MOTIONBL_SetUpBGIni( p_drawsys->p_fsys->bgl );

	// �j��
	TCB_Delete( tcb );
}

//----------------------------------------------------------------------------
/**
 *			�y�f���p���[�V�����u���[�ݒ�֐��z
 *	@brief	�`��V�X�e���f�[�^�����Ƃɖ߂�
 *
 *	@param	tcb		TCB���[�N
 *	@param	p_work	���[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void FLD_DEMO_MOTIONBL_ResetDrawSystemTCB( TCB_PTR tcb, void* p_work )
{
	FLD_DEMO_MOTIONBL* p_drawsys = p_work;

	// VRAM�o���N�ݒ�
	GF_Disp_SetBank( &p_drawsys->vrambank );

	// BG�R���g���[���č쐬
	FLD_DEMO_MOTIONBL_DeleteBGIni(p_drawsys->p_fsys->bgl);
	FLD_DEMO_MOTIONBL_SetUpBGIni_Field( p_drawsys->p_fsys->bgl );

	TCB_Delete( tcb );
}

//----------------------------------------------------------------------------
/**
 *			�y�f���p���[�V�����u���[�ݒ�֐��z
 *	@brief	BG�V�X�e�����[�N�j��
 *
 *	@param	p_bgini		BG�V�X�e�����[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void FLD_DEMO_MOTIONBL_DeleteBGIni( GF_BGL_INI* p_bgini )
{
	Fieldmap_BgExit( p_bgini );
}

//----------------------------------------------------------------------------
/**
 *			�y�f���p���[�V�����u���[�ݒ�֐��z
 *	@brief	�t�B�[���h�pGF�R���g���[���ݒ�
 *	@param	BG�V�X�e�����[�N
 */
//-----------------------------------------------------------------------------
static void FLD_DEMO_MOTIONBL_SetUpBGIni_Field( GF_BGL_INI* p_bg )
{
	Fieldmap_BgSet( p_bg );

	GF_Disp_GX_VisibleControl(
		GX_PLANEMASK_BG0, VISIBLE_ON );
}

//----------------------------------------------------------------------------
/**
 *			�y�f���p���[�V�����u���[�ݒ�֐��z
 *	@brief	���[�V�����u���[������
 *
 *	@param	eva		�W��A�@���ݕ`�悳�ꂽ����
 *	@param	evb		�W��B�@��VRAM�ɕۑ�����Ă������
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static MOTION_BL_PTR FLD_DEMO_MOTIONBL_MotionBlInit( int eva, int evb )
{
	MOTION_BL_PTR motion_bl;
	
	// ���[�V�����u���[�ݒ�
	{
		MOTION_BL_DATA mb = {
			GX_DISPMODE_VRAM_C,
			GX_BGMODE_0,
			GX_BG0_AS_3D,
			
			GX_CAPTURE_SIZE_256x192,
			GX_CAPTURE_MODE_AB,
			GX_CAPTURE_SRCA_2D3D,
			GX_CAPTURE_SRCB_VRAM_0x00000,
			GX_CAPTURE_DEST_VRAM_C_0x00000,
			0,
			0,
			USE_HEAPID
		};
		mb.eva = eva;
		mb.evb = evb;

		motion_bl = MOTION_BL_Init(&mb);
	}	
		

	return motion_bl;
}

//----------------------------------------------------------------------------
/**
 *			�y�f���p���[�V�����u���[�ݒ�֐��z
 *	@brief	���[�V�����u���[�j��
 *
 *	@param	data	���[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void FLD_DEMO_MOTIONBL_MotionBlDelete( FLD_DEMO_MOTIONBL* p_data )
{
//	VIntrTCB_Add( FLD_DEMO_MOTIONBL_MotionBlDeleteTcb, p_data, FLD_DEMO_MOTIONBL_DRAWDATA_SETUP_TCB_PRI );
	VWaitTCB_Add( FLD_DEMO_MOTIONBL_MotionBlDeleteTcb, p_data, FLD_DEMO_MOTIONBL_DRAWDATA_SETUP_TCB_PRI );
}

//----------------------------------------------------------------------------
/**
 *			�y�f���p���[�V�����u���[�ݒ�֐��z
 *	@brief	���[�V�����u���[�j��TCB
 *
 *	@param	tcb			TCB���[�N
 *	@param	p_work		���[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void FLD_DEMO_MOTIONBL_MotionBlDeleteTcb( TCB_PTR tcb, void* p_work )
{
	FLD_DEMO_MOTIONBL* p_data = p_work;
	
	// ���ɖ߂�
	MOTION_BL_Delete(&p_data->motion_bl, GX_DISPMODE_GRAPHICS, GX_BGMODE_0,GX_BG0_AS_3D);
	TCB_Delete( tcb );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�I�u�W�F�eONOFF
 *
 *	@param	fsys	�t�B�[���h�V�X�e��
 *	@param	objid	�I�u�W�FID
 *	@param	flg		�t���O TRUE�FOFF�@FALSE�FON
 */
//-----------------------------------------------------------------------------
static void FLD_DEMO_ObjShadowVanish( FIELDSYS_WORK* fsys, u32 objid, BOOL flg )
{
	FIELD_OBJ_PTR fldobj;
	fldobj = FieldOBJSys_OBJIDSearch( fsys->fldobjsys, objid );

	if( flg == TRUE ){
		FieldOBJ_StatusBit_ON( fldobj, FLDOBJ_STA_BIT_SHADOW_VANISH );
	}else{
		FieldOBJ_StatusBit_OFF( fldobj, FLDOBJ_STA_BIT_SHADOW_VANISH );
	}
}





//-----------------------------------------------------------------------------
/**
 *
 *		�t�B�[���h�}�b�v�^�X�N����
 *
 */
//-----------------------------------------------------------------------------
static void FLDMAP_DEMO_SetFieldObjSysOfs( FIELD_OBJ_SYS_PTR fos, const VecFx32 *vec )
{
	int no = 0;
	FIELD_OBJ_PTR fldobj;

	while( FieldOBJSys_FieldOBJSearch( fos, &fldobj, &no, FLDOBJ_STA_BIT_USE ) == TRUE ){
		FieldOBJ_VecDrawOffsOutSideSet( fldobj, vec );
	}
}
static void FLDMAP_DEMO_ReSetFieldObjSysOfs( FIELD_OBJ_SYS_PTR fos )
{
	VecFx32 ofs;
	int no = 0;
	FIELD_OBJ_PTR fldobj;

	ofs.x = 0;
	ofs.y = 0;
	ofs.z = 0;
	while( FieldOBJSys_FieldOBJSearch( fos, &fldobj, &no, FLDOBJ_STA_BIT_USE ) == TRUE ){
		FieldOBJ_VecDrawOffsOutSideSet( fldobj, &ofs );
	}
}


//-------------------------------------
//	�n�k�C�x���g���[�N
//=====================================
typedef struct {
	FLD_DEMO_SHAKE_SCRN* p_zishin;
	int wait;
	u32 last_count;
	u32 seq;
} EVENT_ZISHIN_WORK;
#define EVENT_ZISHIN_WIDTH	( FX32_CONST( 2.0f ) )
#define EVENT_ZISHIN_SHAKE_SYNC	( 1 )	// �P�̂��̃V���N��
#define EVENT_ZISHIN_SHAKE_COUNT	( 16 )	// ��ꐔ

//----------------------------------------------------------------------------
/**
 *	@brief	�n�k�C�x���g���C��
 */
//-----------------------------------------------------------------------------
static BOOL FLD_MAP_DEMO_ZishinEventMain( GMEVENT_CONTROL * event )
{
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	EVENT_ZISHIN_WORK* p_work = FieldEvent_GetSpecialWork(event);

	switch( p_work->seq ){
	case 0:
		FLD_DEMO_ShakeScrn_Main( p_work->p_zishin );
		if( FLD_DEMO_ShakeScrn_EndCheck( p_work->p_zishin ) == TRUE ){
			p_work->seq ++;
		}
		break;

	case 1:
		FLD_DEMO_ShakeScrn_Free( p_work->p_zishin );	
		sys_FreeMemoryEz( p_work );
		return TRUE;
	}
	return FALSE;
}
//----------------------------------------------------------------------------
/**
 *	@brief	�n�k�C�x���g����
 *
 *	@param	ev	�C�x���g���[�N
 *
 *	@retval	TRUE	����
 *	@retval	FALSE	���s
 */
//-----------------------------------------------------------------------------
void FLD_MAP_DEMO_ZishinEventCall(GMEVENT_CONTROL *event)
{
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	EVENT_ZISHIN_WORK* p_work = sys_AllocMemory( HEAPID_FIELD, sizeof(EVENT_ZISHIN_WORK) );
	memset( p_work, 0, sizeof(EVENT_ZISHIN_WORK) );

	p_work->p_zishin = FLD_DEMO_ShakeScrn_Alloc( HEAPID_FIELD );
	FLD_DEMO_ShakeScrn_Start( p_work->p_zishin, EVENT_ZISHIN_WIDTH, 0, EVENT_ZISHIN_SHAKE_SYNC, EVENT_ZISHIN_SHAKE_COUNT, fsys->camera_ptr );
	
	FieldEvent_Call( event, FLD_MAP_DEMO_ZishinEventMain, p_work );
}


// �~�I�V�e�B�p�n�k
#define EVENT_MIO_ZISHIN_WIDTH	( FX32_CONST( 4.0f ) )
#define EVENT_MIO_ZISHIN_SHAKE_SYNC	( 1 )	// �P�̂��̃V���N��
#define EVENT_MIO_ZISHIN_SHAKE_COUNT	( 24 )	// ��ꐔ
#define EVENT_MIO_ZISHIN_SHAKE_DIV	( 8*FX32_ONE )
#define EVENT_MIO_BGM_FADE_OUT_SYNC	( 1 )
#define EVENT_MIO_BGM_FADE_IN_SYNC	( 16 )
#define EVENT_MIO_WAIT				( 16 )

enum{
	EVENT_MIO_ZISHIN_FADEOUT,
	EVENT_MIO_ZISHIN_FADEOUT_WAIT,
	EVENT_MIO_ZISHIN_START_WAIT,
	EVENT_MIO_ZISHIN_MAIN,
	EVENT_MIO_ZISHIN_END_WAIT,
	EVENT_MIO_ZISHIN_FADEIN,
	EVENT_MIO_ZISHIN_FADEIN_WAIT,
	EVENT_MIO_ZISHIN_END,
};

static void FLD_MAP_Demo_MioZishinShakeWidthSub( EVENT_ZISHIN_WORK* p_work )
{
	fx32 width = FLD_DEMO_ShakeScrn_GetNowShakeWidth( p_work->p_zishin );
	fx32 set_width;
	u32 count = FLD_DEMO_ShakeScrn_GetNowCount( p_work->p_zishin );

	if( p_work->last_count != count ){
		p_work->last_count = count;

		set_width = FX_Div( width, EVENT_MIO_ZISHIN_SHAKE_DIV );
		set_width = width - set_width;
		FLD_DEMO_ShakeScrn_SetNowShakeWidth( p_work->p_zishin, set_width );
	}
}
//----------------------------------------------------------------------------
/**
 *	@brief	�n�k�C�x���g���C��
 */
//-----------------------------------------------------------------------------
static BOOL FLD_MAP_DEMO_MioZishinEventMain( GMEVENT_CONTROL * event )
{
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	EVENT_ZISHIN_WORK* p_work = FieldEvent_GetSpecialWork(event);

	switch( p_work->seq ){
	case EVENT_MIO_ZISHIN_FADEOUT:		// BGM�t�F�[�h�A�E�g�i��u�j
		Snd_BgmFadeOut( 0, EVENT_MIO_BGM_FADE_OUT_SYNC );
		p_work->seq ++;
		break;

	case EVENT_MIO_ZISHIN_FADEOUT_WAIT:
		if( Snd_FadeCheck() == 0 ){
			p_work->seq ++;
			p_work->wait = EVENT_MIO_WAIT;
		}
		break;

	case EVENT_MIO_ZISHIN_START_WAIT:
		p_work->wait --;
		if( p_work->wait <= 0 ){
			p_work->seq ++;	
			Snd_SePlay(	SE_SHAKE );		// ��ꉹ�J�n
		}
		break;
	
	case EVENT_MIO_ZISHIN_MAIN:
		FLD_DEMO_ShakeScrn_Main( p_work->p_zishin );
		// ��ꐔ���ς�������ꕝ�����炷
		FLD_MAP_Demo_MioZishinShakeWidthSub( p_work );
		if( FLD_DEMO_ShakeScrn_EndCheck( p_work->p_zishin ) == TRUE ){
			Snd_SeStopBySeqNo( SE_SHAKE, 0 );	// ��ꉹ��~
			p_work->seq ++;
			p_work->wait = EVENT_MIO_WAIT;
		}
		break;

	case EVENT_MIO_ZISHIN_END_WAIT:
		p_work->wait --;
		if( p_work->wait <= 0 ){
			p_work->seq ++;
		}
		break;

	case EVENT_MIO_ZISHIN_FADEIN:
		Snd_BgmFadeIn( BGM_VOL_MAX, EVENT_MIO_BGM_FADE_IN_SYNC, BGM_FADEIN_START_VOL_MIN );
		p_work->seq ++;
		break;

	case EVENT_MIO_ZISHIN_FADEIN_WAIT:
		if( Snd_FadeCheck() == 0 ){
			p_work->seq ++;
		}
		break;

	case EVENT_MIO_ZISHIN_END:
		FLD_DEMO_ShakeScrn_Free( p_work->p_zishin );	
		sys_FreeMemoryEz( p_work );
		return TRUE;
	}
	return FALSE;
}
//----------------------------------------------------------------------------
/**
 *	@brief	�n�k�C�x���g����
 *
 *	@param	ev	�C�x���g���[�N
 *
 *	@retval	TRUE	����
 *	@retval	FALSE	���s
 */
//-----------------------------------------------------------------------------
void FLD_MAP_DEMO_MioZishinEventCall(GMEVENT_CONTROL *event)
{
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	EVENT_ZISHIN_WORK* p_work = sys_AllocMemory( HEAPID_FIELD, sizeof(EVENT_ZISHIN_WORK) );
	memset( p_work, 0, sizeof(EVENT_ZISHIN_WORK) );

	p_work->p_zishin = FLD_DEMO_ShakeScrn_Alloc( HEAPID_FIELD );
	FLD_DEMO_ShakeScrn_Start( p_work->p_zishin, EVENT_MIO_ZISHIN_WIDTH, 0, EVENT_MIO_ZISHIN_SHAKE_SYNC, EVENT_MIO_ZISHIN_SHAKE_COUNT, fsys->camera_ptr );
	
	// �c���ꐔ��ݒ�
	p_work->last_count = FLD_DEMO_ShakeScrn_GetNowCount( p_work->p_zishin );
	FieldEvent_Call( event, FLD_MAP_DEMO_MioZishinEventMain, p_work );
}



//-----------------------------------------------------------------------------
/**
 *		�`���|�P�����o��
 */
//-----------------------------------------------------------------------------
//-------------------------------------
//	�`���|�P�����o���V�[�P���X
//=====================================
enum{
	FLDMAP_DEMO_LEGEND_MOTION_BP_SET,
	FLDMAP_DEMO_LEGEND_MOTION_BP_SET_WAIT,
	FLDMAP_DEMO_LEGEND_START,
	FLDMAP_DEMO_LEGEND_EFF_WAIT,
	FLDMAP_DEMO_LEGEND_END_WAIT,
	FLDMAP_DEMO_LEGEND_FLASH,
	FLDMAP_DEMO_LEGEND_MOTION_BP_END,
	FLDMAP_DEMO_LEGEND_MOTION_BP_END_WAIT,
	FLDMAP_DEMO_LEGEND_ARITAMA_ON,
	FLDMAP_DEMO_LEGEND_ARITAMA_SHADOWOFF_WAIT,
	FLDMAP_DEMO_LEGEND_ARITAMA_WAIT,
	FLDMAP_DEMO_LEGEND_END,
};
#define FLDMAP_DEMO_LEGEND_TASK_PRI	( 1024 )
#define FLDMAP_DEMO_LEGEND_OBJID	( D05R0114_SPPOKE_01 )	// �o��������C�A�G�A�̊Ǘ�ID
#define FLDMAP_DEMO_LEGEND_EFFSTART	( 240 )		// �G�t�F�N�g�J�n

//-------------------------------------
//	�΂�΂�΁`��@�t���b�V��
//=====================================
typedef struct {
	u32 seq;
	s32 wait;
	FLD_DEMO_FLASH* p_flash;			// FLDMAP_DEMO_LEGEND������炤
} FLDMAP_DEMO_LEGEND_BANBANFLASH;
enum{
	FLD_DEMO_LEGEND_BANBANFLASH_FLASHWAIT,
	FLD_DEMO_LEGEND_BANBANFLASH_FLASH00,
	FLD_DEMO_LEGEND_BANBANFLASH_FLASH01,
	FLD_DEMO_LEGEND_BANBANFLASH_FLASH02,
	FLD_DEMO_LEGEND_BANBANFLASH_END,
};

// �v���g�^�C�v
static void FLDMAP_DEMO_LegendPokeApp_Eff_BanBanFlash_Init( FLDMAP_DEMO_LEGEND_BANBANFLASH* p_eff, FLD_DEMO_FLASH* p_flash );
static BOOL FLDMAP_DEMO_LegendPokeApp_Eff_BanBanFlash_Main( FLDMAP_DEMO_LEGEND_BANBANFLASH* p_eff );


//-------------------------------------
//	��ʗh�炵���t���b�V���G�t�F�N�g
//=====================================
typedef struct {
	u32 seq;
	s32 wait;
	FLD_DEMO_SHAKE_SCRN* p_shake;		// FLDMAP_DEMO_LEGEND������炤
	FLD_DEMO_FLASH* p_flash;			// FLDMAP_DEMO_LEGEND������炤
	GF_CAMERA_PTR copy_camera;			// �J����
} FLDMAP_DEMO_LEGEND_SHAKEFLASH;
// �V�[�P���X
enum{
	FLD_DEMO_LEGEND_SHAKEFLASH_START,
	FLD_DEMO_LEGEND_SHAKEFLASH_FLASH00,
	FLD_DEMO_LEGEND_SHAKEFLASH_SHAKE_FLASH00,
	FLD_DEMO_LEGEND_SHAKEFLASH_FLASH01,
	FLD_DEMO_LEGEND_SHAKEFLASH_SHAKE00,
	FLD_DEMO_LEGEND_SHAKEFLASH_FLASH02,
	FLD_DEMO_LEGEND_SHAKEFLASH_SHAKE_FLASH01,
	FLD_DEMO_LEGEND_SHAKEFLASH_END,
};
#define FLD_DEMO_LEGEND_SHAKEFLASH_ALPHAMAX	( 13 )	// ���ő�l

#define FLD_DEMO_LEGEND_SHAKEFLASH_SHAKE_X	( FX32_CONST( 2.0f ) )	// ��ꕝ
#define FLD_DEMO_LEGEND_SHAKEFLASH_SHAKE_SYNC	( 1 )	// �P�̂��̃V���N��
#define FLD_DEMO_LEGEND_SHAKEFLASH_SHAKE_COUNT	( 8 )	// ��ꐔ

#define FLD_DEMO_LEGEND_SHAKEFLASH_FLASH00_WAIT	( 0 )	// �E�G�C�g
#define FLD_DEMO_LEGEND_SHAKEFLASH_SHAKE_FLASH00_WAIT	( 80 )	// �E�G�C�g
#define FLD_DEMO_LEGEND_SHAKEFLASH_FLASH01_WAIT	( 32 )	// �E�G�C�g
#define FLD_DEMO_LEGEND_SHAKEFLASH_SHAKE00_WAIT	( 60 )	// �E�G�C�g
#define FLD_DEMO_LEGEND_SHAKEFLASH_FLASH02_WAIT	( 60 )	// �E�G�C�g
#define FLD_DEMO_LEGEND_SHAKEFLASH_SHAKE_FLASH01_WAIT	( 40 )	// �E�G�C�g

#define FLD_DEMO_LEGEND_BANBAN_START_WAIT	( 32 )

#define FLD_DEMO_LEGEND_SHADOW_OFF_WAIT	( 72 )

// �v���g�^�C�v
static void FLDMAP_DEMO_LegendPokeApp_Eff_ShakeFlash_Init( FLDMAP_DEMO_LEGEND_SHAKEFLASH* p_eff, FLD_DEMO_SHAKE_SCRN* p_shake, FLD_DEMO_FLASH* p_flash, GF_CAMERA_PTR copy_camera );
static BOOL FLDMAP_DEMO_LegendPokeApp_Eff_ShakeFlash_Main( FLDMAP_DEMO_LEGEND_SHAKEFLASH* p_eff );

//-------------------------------------
//	�`���|�P�����o�����[�N
//=====================================
typedef struct {
	u32 seq;		// �V�[�P���X
	s32 count;		// �ėp����
	
	FLD_DEMO_MOTIONBL motion_bl;		// ���[�V�����u���[

	FLD_DEMO_LEGENDPOKE_APP* p_legend;
	FLD_DEMO_SHAKE_SCRN* p_shake;
	FLD_DEMO_FLASH* p_flash;
	FLD_DEMO_ARITAMA_START* p_aritama;	// �A���̗��J�n

	FLDMAP_DEMO_LEGEND_SHAKEFLASH shakeflash;	// ���t���b�V���R���g���[��
	FLDMAP_DEMO_LEGEND_BANBANFLASH banbanflash;	// �΂�΂�΁`��t���b�V��
} FLDMAP_DEMO_LEGEND;

#define FLD_DEMO_LEGEND_MOTIONBL_EVA	( 8 )
#define FLD_DEMO_LEGEND_MOTIONBL_EVB	( 8 )

//----------------------------------------------------------------------------
/**
 *		�y�`���|�P�����o���z
 *	@brief	����������
 */
//-----------------------------------------------------------------------------
static void FLDMAP_DEMO_LegendPokeApp_Init(FLDMAPFUNC_WORK * p_fwk, FIELDSYS_WORK * p_fsys, void * p_work)
{
	FLDMAP_DEMO_LEGEND* p_lgd = p_work;

	memset( p_lgd, 0, sizeof(FLDMAP_DEMO_LEGEND) );

	//	�C�A�G�A�o��
	p_lgd->p_legend = FLD_DEMO_LegendPokeApp_Alloc( USE_HEAPID, p_fsys );
	// �n�k
	p_lgd->p_shake = FLD_DEMO_ShakeScrn_Alloc( USE_HEAPID );
	// �t���b�V��
	p_lgd->p_flash = FLD_DEMO_Flash_Alloc( USE_HEAPID );
	// �V�[�P���X
	p_lgd->seq = 0;

#ifdef FIELD_DEMO_DEBUG
	FieldDemoDebugStart();
#endif
}

//----------------------------------------------------------------------------
/**
 *		�y�`���|�P�����o���z
 *	@brief	�j������
 */
//-----------------------------------------------------------------------------
static void FLDMAP_DEMO_LegendPokeApp_Delete(FLDMAPFUNC_WORK * p_fwk, FIELDSYS_WORK * p_fsys, void * p_work)
{
	FLDMAP_DEMO_LEGEND* p_lgd = p_work;

	// �C�A�G�A�o��
	FLD_DEMO_LegendPokeApp_Free( p_lgd->p_legend );
	// �A���̗�
	FLD_DEMO_AriTamaStart_Free( p_lgd->p_aritama );
	// �n�k
	FLD_DEMO_ShakeScrn_Free( p_lgd->p_shake );
	// �t���b�V��
	FLD_DEMO_Flash_Free( p_lgd->p_flash );

#ifdef FIELD_DEMO_DEBUG
	FieldDemoDebugEnd();
#endif
}

//----------------------------------------------------------------------------
/**
 *		�y�`���|�P�����o���z
 *	@brief	���C������
 */
//-----------------------------------------------------------------------------
static void FLDMAP_DEMO_LegendPokeApp_Main(FLDMAPFUNC_WORK * p_fwk, FIELDSYS_WORK * p_fsys, void * p_work)
{
	FLDMAP_DEMO_LEGEND* p_lgd = p_work;
	BOOL check[2];
	BOOL result;

#ifdef FIELD_DEMO_DEBUG
	if( FIELD_DEMO_DEBUG_STOP == 1 ){
		return ;
	}
#endif
	
	// �����̕���
	switch( p_lgd->seq ){
	case FLDMAP_DEMO_LEGEND_MOTION_BP_SET:	// ���[�V�����u���[�ݒ�
		FLD_DEMO_MOTIONBL_Init( &p_lgd->motion_bl, p_fsys, FLD_DEMO_LEGEND_MOTIONBL_EVA, FLD_DEMO_LEGEND_MOTIONBL_EVB );
		
		p_lgd->seq ++;
		break;

	case FLDMAP_DEMO_LEGEND_MOTION_BP_SET_WAIT:
		FLD_DEMO_MOTIONBL_Main( &p_lgd->motion_bl );
		if( FLD_DEMO_MOTIONBL_GetState( &p_lgd->motion_bl ) == FLD_DEMO_MOTIONBL_SEQ_ENDWAIT ){
			p_lgd->seq ++;
		}
		break;

	case FLDMAP_DEMO_LEGEND_START:
		FLD_DEMO_LegendPokeApp_Start( p_lgd->p_legend, FLDMAP_DEMO_LEGEND_OBJID );
		p_lgd->count = FLDMAP_DEMO_LEGEND_EFFSTART;
		p_lgd->seq ++;
		break;

	case FLDMAP_DEMO_LEGEND_EFF_WAIT:
		p_lgd->count--;
		if( p_lgd->count < 0 ){
			FLDMAP_DEMO_LegendPokeApp_Eff_ShakeFlash_Init( &p_lgd->shakeflash, p_lgd->p_shake, p_lgd->p_flash, p_fsys->camera_ptr );
			p_lgd->seq++;
		}
		break;

	case FLDMAP_DEMO_LEGEND_END_WAIT:
		check[0] = FLDMAP_DEMO_LegendPokeApp_Eff_ShakeFlash_Main( &p_lgd->shakeflash );
		check[1] = FLD_DEMO_LegendPokeApp_EndCheck( p_lgd->p_legend );
		// ���암
		if( (check[0] == TRUE) && (check[1] == TRUE) ){
			FLDMAP_DEMO_LegendPokeApp_Eff_BanBanFlash_Init( &p_lgd->banbanflash, p_lgd->p_flash );
			p_lgd->seq++;
		}
		break;

	case FLDMAP_DEMO_LEGEND_FLASH:
		check[0] = FLDMAP_DEMO_LegendPokeApp_Eff_BanBanFlash_Main( &p_lgd->banbanflash );

		// �^������Ԃł���̗��ǂݍ���
		// �e�N�X�`���T�C�Y���傫���A��ʂɉe�����ł邽��
		if( p_lgd->banbanflash.seq == FLD_DEMO_LEGEND_BANBANFLASH_FLASH02 ){
			if( FLD_DEMO_Flash_GetAlpha( p_lgd->banbanflash.p_flash ) == FLD_DEMO_LEGEND_SHAKEFLASH_ALPHAMAX ){
				// �A���̗�
				p_lgd->p_aritama = FLD_DEMO_AriTamaStart_Alloc( USE_HEAPID, p_fsys );
			}
		}
		
		if( check[0] == TRUE ){
			p_lgd->seq++;
		}
		break;

	case FLDMAP_DEMO_LEGEND_MOTION_BP_END:	// ���[�V�����u���[�j��
		FLD_DEMO_MOTIONBL_EndReq( &p_lgd->motion_bl );
		p_lgd->seq ++;
		break;

	case FLDMAP_DEMO_LEGEND_MOTION_BP_END_WAIT:
		FLD_DEMO_MOTIONBL_Main( &p_lgd->motion_bl );

		if( FLD_DEMO_MOTIONBL_GetState( &p_lgd->motion_bl ) == FLD_DEMO_MOTIONBL_SEQ_END ){
			p_lgd->seq ++;
		}
		break;

	case FLDMAP_DEMO_LEGEND_ARITAMA_ON:
		FLD_DEMO_AriTamaStart_Start( p_lgd->p_aritama, FLDMAP_DEMO_LEGEND_OBJID );
		p_lgd->count = FLD_DEMO_LEGEND_SHADOW_OFF_WAIT;
		p_lgd->seq ++;
		break;

	case FLDMAP_DEMO_LEGEND_ARITAMA_SHADOWOFF_WAIT:
		p_lgd->count --;
		if( p_lgd->count <= 0 ){	
			FLD_DEMO_ObjShadowVanish( p_fsys, FLDMAP_DEMO_LEGEND_OBJID, TRUE );
			p_lgd->seq ++;
		}

	case FLDMAP_DEMO_LEGEND_ARITAMA_WAIT:
		result = FLD_DEMO_AriTamaStart_Main( p_lgd->p_aritama );
		if( result == TRUE ){

			FLD_DEMO_ObjShadowVanish( p_fsys, FLDMAP_DEMO_LEGEND_OBJID, FALSE );
			p_lgd->seq ++;
		}
		break;
		
	case FLDMAP_DEMO_LEGEND_END:
		break;


	default:
		break;
	}
	
	FLD_DEMO_LegendPokeApp_Main( p_lgd->p_legend );
	FLD_DEMO_ShakeScrn_Main( p_lgd->p_shake );
	FLD_DEMO_Flash_Main( p_lgd->p_flash );
}

//----------------------------------------------------------------------------
/**
 *		�y�`���|�P�����o���z
 *	@brief	�`�揈��
 */
//-----------------------------------------------------------------------------
static void FLDMAP_DEMO_LegendPokeApp_Draw(FLDMAPFUNC_WORK * p_fwk, FIELDSYS_WORK * p_fsys, void * p_work)
{
	FLDMAP_DEMO_LEGEND* p_lgd = p_work;

	FLD_DEMO_LegendPokeApp_Draw( p_lgd->p_legend );
	if( p_lgd->p_aritama ){
		FLD_DEMO_AriTamaStart_Draw( p_lgd->p_aritama );
	}
}

//----------------------------------------------------------------------------
/**
 *		�y�`���|�P�����o���z
 *	@brief	�`���|�P�����o���@�f���J�n
 *
 *	@param	fsys	�t�B�[���h�V�X�e�����[�N
 *
 *	@return	�f�����[�N
 */
//-----------------------------------------------------------------------------
FLDMAPFUNC_WORK* FLDMAP_DEMO_LegendPokeApp_Start( FIELDSYS_WORK* fsys )
{
	static const FLDMAPFUNC_DATA FLDMAP_DEMO_LegendPokeAppData = {
		FLDMAP_DEMO_LEGEND_TASK_PRI,
		sizeof(FLDMAP_DEMO_LEGEND),
		FLDMAP_DEMO_LegendPokeApp_Init,
		FLDMAP_DEMO_LegendPokeApp_Delete,
		FLDMAP_DEMO_LegendPokeApp_Main,
		FLDMAP_DEMO_LegendPokeApp_Draw
	};
	FLDMAPFUNC_WORK* p_fwk;
	
	p_fwk = FLDMAPFUNC_Create( fsys->fldmap->fmapfunc_sys, &FLDMAP_DEMO_LegendPokeAppData );
	return p_fwk;
}

//----------------------------------------------------------------------------
/**
 *		�y�`���|�P�����o���z
 *	@brief	�`���|�P�����o��	�f���I��
 *
 *	@param	p_demo	�f�����[�N
 *
 *	@return	none
 */	
//-----------------------------------------------------------------------------
void FLDMAP_DEMO_LegendPokeApp_End( FLDMAPFUNC_WORK* p_demo )
{
	FLDMAPFUNC_Delete( p_demo );
}

//----------------------------------------------------------------------------
/**
 *		�y�`���|�P�����o���z
 *	@brief	�f���I���`�F�b�N
 *
 *	@param	p_demo 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
BOOL FLDMAP_DEMO_LegendPokeApp_EndCheck( FLDMAPFUNC_WORK* p_demo )
{
	FLDMAP_DEMO_LEGEND* p_lgd = FLDMAPFUNC_GetFreeWork( p_demo );
	if( p_lgd->seq == FLDMAP_DEMO_LEGEND_END ){
		return TRUE;
	}
	return FALSE;
}



//----------------------------------------------------------------------------
/**
 *		�y�`���|�P�����o���z
 *	@brief	�h�炵���t���b�V��	������
 *
 *	@param	p_eff		�G�t�F�N�g���[�N
 *	@param	p_shake		�h�炵�I�u�W�F
 *	@param	p_flash		�t���b�V���I�u�W�F
 *	@param	copy_camera	�J����
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void FLDMAP_DEMO_LegendPokeApp_Eff_ShakeFlash_Init( FLDMAP_DEMO_LEGEND_SHAKEFLASH* p_eff, FLD_DEMO_SHAKE_SCRN* p_shake, FLD_DEMO_FLASH* p_flash, GF_CAMERA_PTR copy_camera )
{
	p_eff->seq	= 0;
	p_eff->wait = 0; 
	p_eff->p_shake = p_shake;
	p_eff->p_flash = p_flash;
	p_eff->copy_camera = copy_camera;
}

//----------------------------------------------------------------------------
/**
 *		�y�`���|�P�����o���z
 *	@brief	�h�炵���t���b�V��	���C��
 *
 *	@param	p_eff	�G�t�F�N�g���[�N
 *
 *	@retval	TRUE	�I��
 *	@retval	FALSE	�r��
 */
//-----------------------------------------------------------------------------
static BOOL FLDMAP_DEMO_LegendPokeApp_Eff_ShakeFlash_Main( FLDMAP_DEMO_LEGEND_SHAKEFLASH* p_eff )
{
	switch( p_eff->seq ){
	case FLD_DEMO_LEGEND_SHAKEFLASH_START:
		p_eff->wait = FLD_DEMO_LEGEND_SHAKEFLASH_FLASH00_WAIT;
		p_eff->seq++;
		break;
		
	case FLD_DEMO_LEGEND_SHAKEFLASH_FLASH00:
		p_eff->wait --;
		if( p_eff->wait < 0 ){
			FLD_DEMO_Flash_Start( p_eff->p_flash, FLD_DEMO_LEGEND_SHAKEFLASH_ALPHAMAX, 4, 16 );
			p_eff->seq++;
			p_eff->wait = FLD_DEMO_LEGEND_SHAKEFLASH_SHAKE_FLASH00_WAIT;
		}
		break;
		
	case FLD_DEMO_LEGEND_SHAKEFLASH_SHAKE_FLASH00:
		p_eff->wait --;
		if( p_eff->wait < 0 ){
			FLD_DEMO_Flash_Start( p_eff->p_flash, FLD_DEMO_LEGEND_SHAKEFLASH_ALPHAMAX, 4, 24 );
			FLD_DEMO_ShakeScrn_Start( p_eff->p_shake, FLD_DEMO_LEGEND_SHAKEFLASH_SHAKE_X, 0, FLD_DEMO_LEGEND_SHAKEFLASH_SHAKE_SYNC, FLD_DEMO_LEGEND_SHAKEFLASH_SHAKE_COUNT, p_eff->copy_camera );
			p_eff->seq++;
			p_eff->wait = FLD_DEMO_LEGEND_SHAKEFLASH_FLASH01_WAIT;
		}
		break;

	case FLD_DEMO_LEGEND_SHAKEFLASH_FLASH01:
		p_eff->wait --;
		if( p_eff->wait < 0 ){
			FLD_DEMO_Flash_Start( p_eff->p_flash, FLD_DEMO_LEGEND_SHAKEFLASH_ALPHAMAX, 4, 27 );
			p_eff->seq++;
			p_eff->wait = FLD_DEMO_LEGEND_SHAKEFLASH_SHAKE00_WAIT;
		}
		break;

	case FLD_DEMO_LEGEND_SHAKEFLASH_SHAKE00:
		p_eff->wait --;
		if( p_eff->wait < 0 ){
			FLD_DEMO_ShakeScrn_Start( p_eff->p_shake, 3*FX32_ONE, 0, FLD_DEMO_LEGEND_SHAKEFLASH_SHAKE_SYNC, 10, p_eff->copy_camera );
			p_eff->seq++;
			p_eff->wait = FLD_DEMO_LEGEND_SHAKEFLASH_FLASH02_WAIT;
		}
		break;

	case FLD_DEMO_LEGEND_SHAKEFLASH_FLASH02:
		p_eff->wait --;
		if( p_eff->wait < 0 ){
			FLD_DEMO_Flash_Start( p_eff->p_flash, FLD_DEMO_LEGEND_SHAKEFLASH_ALPHAMAX, 8, 32 );
			p_eff->seq++;
			p_eff->wait = FLD_DEMO_LEGEND_SHAKEFLASH_SHAKE_FLASH01_WAIT;
		}
		break;
		
	case FLD_DEMO_LEGEND_SHAKEFLASH_SHAKE_FLASH01:
		p_eff->wait --;
		if( p_eff->wait < 0 ){
			FLD_DEMO_Flash_Start( p_eff->p_flash, FLD_DEMO_LEGEND_SHAKEFLASH_ALPHAMAX, 4, 16 );
			FLD_DEMO_ShakeScrn_Start( p_eff->p_shake, 4*FX32_ONE, 0, FLD_DEMO_LEGEND_SHAKEFLASH_SHAKE_SYNC, 12, p_eff->copy_camera );
			p_eff->seq++;
		}
		break;
		
	case FLD_DEMO_LEGEND_SHAKEFLASH_END:
		return TRUE;
	}

	return FALSE;
}

//----------------------------------------------------------------------------
/**
 *		�y�`���|�P�����o���z
 *	@brief	�o���o���t���b�V��	������
 *
 *	@param	p_eff		�G�t�F�N�g���[�N
 *	@param	p_flash		�t���b�V���I�u�W�F
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void FLDMAP_DEMO_LegendPokeApp_Eff_BanBanFlash_Init( FLDMAP_DEMO_LEGEND_BANBANFLASH* p_eff, FLD_DEMO_FLASH* p_flash )
{
	p_eff->seq	= 0;
	p_eff->wait = FLD_DEMO_LEGEND_BANBAN_START_WAIT; 
	p_eff->p_flash = p_flash;
}

//----------------------------------------------------------------------------
/**
 *		�y�`���|�P�����o���z
 *	@brief	�o���o���t���b�V��	���C��
 *
 *	@param	p_eff	�G�t�F�N�g���[�N
 *
 *	@retval	TRUE	�I��
 *	@retval	FALSE	�r��
 */
//-----------------------------------------------------------------------------
static BOOL FLDMAP_DEMO_LegendPokeApp_Eff_BanBanFlash_Main( FLDMAP_DEMO_LEGEND_BANBANFLASH* p_eff )
{
	switch( p_eff->seq ){
	case FLD_DEMO_LEGEND_BANBANFLASH_FLASHWAIT:
		p_eff->wait --;
		if( p_eff->wait < 0 ){
			p_eff->seq ++;
		}
		break;

	case FLD_DEMO_LEGEND_BANBANFLASH_FLASH00:
		FLD_DEMO_Flash_Start( p_eff->p_flash, FLD_DEMO_LEGEND_SHAKEFLASH_ALPHAMAX, 4, 8 );
		p_eff->seq++;
		p_eff->wait = 16;
		break;
		
	case FLD_DEMO_LEGEND_BANBANFLASH_FLASH01:
		p_eff->wait --;
		
		if( p_eff->wait < 0 ){
			FLD_DEMO_Flash_Start( p_eff->p_flash, FLD_DEMO_LEGEND_SHAKEFLASH_ALPHAMAX, 4, 8 );
			p_eff->seq++;
			p_eff->wait = 16;
		}
		break;
		
	case FLD_DEMO_LEGEND_BANBANFLASH_FLASH02:
		p_eff->wait --;
		
		if( p_eff->wait < 0 ){
			FLD_DEMO_Flash_Start( p_eff->p_flash, FLD_DEMO_LEGEND_SHAKEFLASH_ALPHAMAX, 4, 32 );
			p_eff->seq++;
			p_eff->wait = 40;
		}
		break;
		
	case FLD_DEMO_LEGEND_BANBANFLASH_END:
		p_eff->wait --;
		if( p_eff->wait < 0 ){
			return TRUE;
		}
		break;
	}

	return FALSE;
}





//-----------------------------------------------------------------------------
/**
 * 
 *		�������b�J���o
 * 
 */
//-----------------------------------------------------------------------------
//-------------------------------------
//	�����b�J���o�V�[�P���X
//=====================================
enum{
	FLDMAP_DEMO_BLACKRING_END,
};
#define FLDMAP_DEMO_BLACKRING_TASK_PRI	( 1024 )
#define FLDMAP_DEMO_BLACKRING_OBJID	( D05R0114_SPPOKE_01 )	// �o��������C�A�G�A�̊Ǘ�ID

//-------------------------------------
//	�������b�J���o���[�N
//=====================================
typedef struct {
	FLD_DEMO_BLACK_RING* p_blackring;
} FLDMAP_DEMO_BLACKRING;

//----------------------------------------------------------------------------
/**
 *		�y�������b�J���o�z
 *	@brief	����������
 */
//-----------------------------------------------------------------------------
static void FLDMAP_DEMO_BlackRing_Init(FLDMAPFUNC_WORK * p_fwk, FIELDSYS_WORK * p_fsys, void * p_work)
{
	FLDMAP_DEMO_BLACKRING* p_br = p_work;
	FIELD_OBJ_PTR fldobj;
	u16 x, y, z;
	
	// �C�A�G�A�����߂�
	fldobj = FieldOBJSys_OBJIDSearch( p_fsys->fldobjsys, FLDMAP_DEMO_BLACKRING_OBJID );
	GF_ASSERT( fldobj );
	x = FieldOBJ_NowPosGX_Get( fldobj );
	y = 0;	// 0����
	z = FieldOBJ_NowPosGZ_Get( fldobj );

	// �����b�J
	p_br->p_blackring = FLD_DEMO_BlackRing_Alloc( USE_HEAPID );

	// ��Ring���o
	FLD_DEMO_BlackRing_Start( p_br->p_blackring, x, y, z );
}

//----------------------------------------------------------------------------
/**
 *		�y�������b�J���o�z
 *	@brief	�j������
 */
//-----------------------------------------------------------------------------
static void FLDMAP_DEMO_BlackRing_Delete(FLDMAPFUNC_WORK * p_fwk, FIELDSYS_WORK * p_fsys, void * p_work)
{
	FLDMAP_DEMO_BLACKRING* p_br = p_work;
	
	// �����b�J
	FLD_DEMO_BlackRing_Free( p_br->p_blackring );
}

//----------------------------------------------------------------------------
/**
 *		�y�������b�J���o�z
 *	@brief	���C������
 */
//-----------------------------------------------------------------------------
static void FLDMAP_DEMO_BlackRing_Main(FLDMAPFUNC_WORK * p_fwk, FIELDSYS_WORK * p_fsys, void * p_work)
{
	FLDMAP_DEMO_BLACKRING* p_br = p_work;

	// �����b�J���C��
	FLD_DEMO_BlackRing_Main( p_br->p_blackring );
}

//----------------------------------------------------------------------------
/**
 *		�y�������b�J���o�z
 *	@brief	�`�揈��
 */
//-----------------------------------------------------------------------------
static void FLDMAP_DEMO_BlackRing_Draw(FLDMAPFUNC_WORK * p_fwk, FIELDSYS_WORK * p_fsys, void * p_work)
{
	FLDMAP_DEMO_BLACKRING* p_br = p_work;

	// �����b�J�`��
	FLD_DEMO_BlackRing_Draw( p_br->p_blackring );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�������b�J���o�@�f���J�n
 *
 *	@param	fsys	�t�B�[���h�V�X�e�����[�N
 *
 *	@return	�f�����[�N
 */
//-----------------------------------------------------------------------------
FLDMAPFUNC_WORK* FLDMAP_DEMO_BlackRing_Start( FIELDSYS_WORK* fsys )
{
	static const FLDMAPFUNC_DATA FLDMAP_DEMO_Data = {
		FLDMAP_DEMO_BLACKRING_TASK_PRI,
		sizeof(FLDMAP_DEMO_BLACKRING),
		FLDMAP_DEMO_BlackRing_Init,
		FLDMAP_DEMO_BlackRing_Delete,
		FLDMAP_DEMO_BlackRing_Main,
		FLDMAP_DEMO_BlackRing_Draw
	};
	FLDMAPFUNC_WORK* p_fwk;
	p_fwk = FLDMAPFUNC_Create( fsys->fldmap->fmapfunc_sys, &FLDMAP_DEMO_Data );
	return p_fwk;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�������b�J���o�@�f���I��
 *
 *	@param	p_demo ���[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void FLDMAP_DEMO_BlackRing_End( FLDMAPFUNC_WORK* p_demo )
{
	FLDMAPFUNC_Delete( p_demo );
}

//-----------------------------------------------------------------------------
/**
 * 
 *		����̗�
 * 
 */
//-----------------------------------------------------------------------------
#define FLDMAP_DEMO_ANTEGG_TASK_PRI	( 1024 )

//-------------------------------------
//	����̗����[�N
//=====================================
typedef struct {
	u32 seq;		// �V�[�P���X
	FLD_DEMO_ANTEGG* p_antegg;
	FLD_DEMO_BLACK_RING* p_blackring;
} FLDMAP_DEMO_ANTEGG;

//----------------------------------------------------------------------------
/**
 *		�y����̗��z
 *	@brief	����������
 */
//-----------------------------------------------------------------------------
static void FLDMAP_DEMO_AntEggCut00_Init(FLDMAPFUNC_WORK * p_fwk, FIELDSYS_WORK * p_fsys, void * p_work)
{
	FLDMAP_DEMO_ANTEGG* p_dwk = p_work;
	VecFx32 matrix;
	CAMERA_ANGLE angle;

#if ( PM_VERSION == VERSION_DIAMOND )

	// �J�����p�����[�^�ݒ�
	GFC_SetCameraPerspWay( 0x1701, p_fsys->camera_ptr );	
	GFC_SetCameraDistance( 0xc8a55, p_fsys->camera_ptr );
	matrix.x = 0x2280ef;
	matrix.y = 0xca424;
	matrix.z = 0x268c50;
	GFC_SetLookTarget( &matrix, p_fsys->camera_ptr );
	angle.x = 0x22a2;
	angle.y = 0xf800;
	angle.z = 0;
	GFC_SetCameraAngleRev( &angle, p_fsys->camera_ptr );

	GFC_SetCameraClip( 2*FX32_ONE, 2000*FX32_ONE, p_fsys->camera_ptr );

#elif( PM_VERSION == VERSION_PEARL )

	// �J�����p�����[�^�ݒ�
	GFC_SetCameraPerspWay( 0x10c1, p_fsys->camera_ptr );	
	GFC_SetCameraDistance( 0xD5052, p_fsys->camera_ptr );
	matrix.x = 0x1bffbd;
	matrix.y = 0xaa361;
	matrix.z = 0x25dfdc;
	GFC_SetLookTarget( &matrix, p_fsys->camera_ptr );
	angle.x = 0x19a3;
	angle.y = 0x90c;
	angle.z = 0;
	GFC_SetCameraAngleRev( &angle, p_fsys->camera_ptr );

	GFC_SetCameraClip( 14*FX32_ONE, 2031*FX32_ONE, p_fsys->camera_ptr );

#endif


	p_dwk->p_antegg = FLD_DEMO_AntEgg_Cut_Alloc( USE_HEAPID );
	p_dwk->p_blackring = FLD_DEMO_BlackRing_AntEggCat_Alloc( USE_HEAPID );
	matrix = GFC_GetLookTarget( p_fsys->camera_ptr );
	FLD_DEMO_AntEgg_Cut00_Start( p_dwk->p_antegg, matrix.x, matrix.y, matrix.z );
	FLD_DEMO_BlackRing_AntEggCat00_Start( p_dwk->p_blackring, matrix.x, matrix.y, matrix.z );
}
static void FLDMAP_DEMO_AntEggCut01_Init(FLDMAPFUNC_WORK * p_fwk, FIELDSYS_WORK * p_fsys, void * p_work)
{
	FLDMAP_DEMO_ANTEGG* p_dwk = p_work;
	VecFx32 matrix;
	CAMERA_ANGLE angle;

	// �J�����p�����[�^�ݒ�
	GFC_SetCameraPerspWay( 0xf81, p_fsys->camera_ptr );	
	GFC_SetCameraDistance( 0x17e532, p_fsys->camera_ptr );
	matrix.x = 0xf99d58;
	matrix.y = 0xc5502;
	matrix.z = 0x28cf549;
	GFC_SetLookTarget( &matrix, p_fsys->camera_ptr );
	angle.x = 0x642;
	angle.y = 0xeda0;
	angle.z = 0;
	GFC_SetCameraAngleRev( &angle, p_fsys->camera_ptr );
	GFC_SetCameraClip( 88*FX32_ONE, 2000*FX32_ONE, p_fsys->camera_ptr );

	// LIGHT�ݒ�ύX
	DellLightCont( &p_fsys->light_cont_data );
	p_fsys->light_cont_data = InitLightCont( p_fsys->glst_data, LIGHT_TYPE3 );

	p_dwk->p_antegg = FLD_DEMO_AntEgg_Cut_Alloc( USE_HEAPID );
	p_dwk->p_blackring = FLD_DEMO_BlackRing_AntEggCat_Alloc( USE_HEAPID );
	matrix = GFC_GetLookTarget( p_fsys->camera_ptr );
	FLD_DEMO_AntEgg_Cut01_Start( p_dwk->p_antegg, matrix.x, matrix.y, matrix.z );
	FLD_DEMO_BlackRing_AntEggCat01_Start( p_dwk->p_blackring, matrix.x, matrix.y, matrix.z );
}
static void FLDMAP_DEMO_AntEggCut02_Init(FLDMAPFUNC_WORK * p_fwk, FIELDSYS_WORK * p_fsys, void * p_work)
{
	FLDMAP_DEMO_ANTEGG* p_dwk = p_work;
	VecFx32 matrix;
	CAMERA_ANGLE angle;

	// �J�����p�����[�^�ݒ�
	GFC_SetCameraPerspWay( 0x4c1, p_fsys->camera_ptr );	
	GFC_SetCameraDistance( 0x26bec1, p_fsys->camera_ptr );
	matrix.x = 0x1df5dfd;
	matrix.y = 0x73a0c;
	matrix.z = 0x2b9f4a2;
	GFC_SetLookTarget( &matrix, p_fsys->camera_ptr );
	angle.x = 0x4c2;
	angle.y = 0xa40;
	angle.z = 0;
	GFC_SetCameraAngleRev( &angle, p_fsys->camera_ptr );

	GFC_SetCameraClip( 176*FX32_ONE, 1480*FX32_ONE, p_fsys->camera_ptr );


	// LIGHT�ݒ�ύX
	DellLightCont( &p_fsys->light_cont_data );
	p_fsys->light_cont_data = InitLightCont( p_fsys->glst_data, LIGHT_TYPE3 );

	p_dwk->p_antegg = FLD_DEMO_AntEgg_Cut_Alloc( USE_HEAPID );
	p_dwk->p_blackring = FLD_DEMO_BlackRing_AntEggCat_Alloc( USE_HEAPID );
	matrix = GFC_GetLookTarget( p_fsys->camera_ptr );
	FLD_DEMO_AntEgg_Cut02_Start( p_dwk->p_antegg, matrix.x, matrix.y, matrix.z );
	FLD_DEMO_BlackRing_AntEggCat02_Start( p_dwk->p_blackring, matrix.x, matrix.y, matrix.z );
}

//----------------------------------------------------------------------------
/**
 *		�y����̗��z
 *	@brief	�j������
 */
//-----------------------------------------------------------------------------
static void FLDMAP_DEMO_AntEgg_Delete(FLDMAPFUNC_WORK * p_fwk, FIELDSYS_WORK * p_fsys, void * p_work)
{
	FLDMAP_DEMO_ANTEGG* p_dwk = p_work;

	FLD_DEMO_AntEgg_Cut_Free( p_dwk->p_antegg );
	FLD_DEMO_BlackRing_AntEggCat_Free( p_dwk->p_blackring );
}

//----------------------------------------------------------------------------
/**
 *		�y����̗��z
 *	@brief	���C������
 */
//-----------------------------------------------------------------------------
static void FLDMAP_DEMO_AntEgg_Main(FLDMAPFUNC_WORK * p_fwk, FIELDSYS_WORK * p_fsys, void * p_work)
{
	FLDMAP_DEMO_ANTEGG* p_dwk = p_work;

	FLD_DEMO_AntEgg_Cut_Main( p_dwk->p_antegg );
	FLD_DEMO_BlackRing_AntEggCat_Main( p_dwk->p_blackring );
}

//----------------------------------------------------------------------------
/**
 *		�y����̗��z
 *	@brief	�`�揈��
 */
//-----------------------------------------------------------------------------
static void FLDMAP_DEMO_AntEgg_Draw(FLDMAPFUNC_WORK * p_fwk, FIELDSYS_WORK * p_fsys, void * p_work)
{
	FLDMAP_DEMO_ANTEGG* p_dwk = p_work;

	FLD_DEMO_AntEgg_Cut_Draw( p_dwk->p_antegg );
	FLD_DEMO_BlackRing_AntEggCat_Draw( p_dwk->p_blackring );
}

//----------------------------------------------------------------------------
/**
 *	@brief	����̗��@�f���J�n
 *
 *	@param	fsys		�t�B�[���h�V�X�e�����[�N
 *	@param	cut			�J�b�g
 *
 *	@return	�f�����[�N
 *
 *	FLDMAP_DEMO_ANTEGG_CUT00		�J�b�g00
 *	FLDMAP_DEMO_ANTEGG_CUT01		�J�b�g01
 *	FLDMAP_DEMO_ANTEGG_CUT02		�J�b�g02
 */
//-----------------------------------------------------------------------------
FLDMAPFUNC_WORK* FLDMAP_DEMO_AntEgg_Start( FIELDSYS_WORK* fsys, u32 cut )
{
	static FLDMAPFUNC_DATA FLDMAP_DEMO_Data = {
		FLDMAP_DEMO_ANTEGG_TASK_PRI	,
		sizeof(FLDMAP_DEMO_ANTEGG),
		NULL,
		FLDMAP_DEMO_AntEgg_Delete,
		FLDMAP_DEMO_AntEgg_Main,
		FLDMAP_DEMO_AntEgg_Draw
	};
	static const FLDMAPFUNC_CREATE FLDMAP_DEMO_Create[] = {
		FLDMAP_DEMO_AntEggCut00_Init,
		FLDMAP_DEMO_AntEggCut01_Init,
		FLDMAP_DEMO_AntEggCut02_Init,
	};
	FLDMAPFUNC_WORK* p_fwk;

	FLDMAP_DEMO_Data.create_func = FLDMAP_DEMO_Create[ cut ];
	p_fwk = FLDMAPFUNC_Create( fsys->fldmap->fmapfunc_sys, &FLDMAP_DEMO_Data );
	return p_fwk;
}

//----------------------------------------------------------------------------
/**
 *	@brief	����̗��@�f���I��
 *
 *	@param	p_demo	�f�����[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void FLDMAP_DEMO_AntEgg_End( FLDMAPFUNC_WORK* p_demo )
{
	FLDMAPFUNC_Delete( p_demo );
}



//-----------------------------------------------------------------------------
/**
 * 
 *		��͕��o
 * 
 */
//-----------------------------------------------------------------------------
#define FLDMAP_DEMO_GINGA_TASK_PRI		( 1024 )
#define FLDMAP_DEMO_GINGA_Y_OFS			( FX32_CONST( 0x2 ) )
#define FLDMAP_DEMO_GINGA_DARKOFF_WAIT	( 64 )
//-------------------------------------
//	��͕��o���[�N
//=====================================
typedef struct {
	u32 seq;		// �V�[�P���X
	u32 wait;		// �҂����ԂȂǂɎg�p
	FLD_DEMO_GINGA* p_ginga;	//�@��͕��o
	FLD_DEMO_DARKLIGHT* p_dark;	// �_�[�N���C�g
} FLDMAP_DEMO_GINGA;

//----------------------------------------------------------------------------
/**
 *		�y��͕��o�z
 *	@brief	����������
 */
//-----------------------------------------------------------------------------
static void FLDMAP_DEMO_Ginga_Init(FLDMAPFUNC_WORK * p_fwk, FIELDSYS_WORK * p_fsys, void * p_work)
{
	FLDMAP_DEMO_GINGA* p_dwk = p_work;

	p_dwk->p_ginga = FLD_DEMO_GINGA_Alloc( p_fsys );
	p_dwk->p_dark = FLD_DEMO_DarkLight_Alloc( USE_HEAPID, p_fsys );
	p_dwk->seq		= 0;
}

//----------------------------------------------------------------------------
/**
 *		�y��͕��o�z
 *	@brief	�j������
 */
//-----------------------------------------------------------------------------
static void FLDMAP_DEMO_Ginga_Delete(FLDMAPFUNC_WORK * p_fwk, FIELDSYS_WORK * p_fsys, void * p_work)
{
	FLDMAP_DEMO_GINGA* p_dwk = p_work;
	
	FLD_DEMO_GINGA_Free( p_dwk->p_ginga );
	FLD_DEMO_DarkLight_Free( p_dwk->p_dark );
}

//----------------------------------------------------------------------------
/**
 *		�y��͕��o�z
 *	@brief	���C������
 */
//-----------------------------------------------------------------------------
static void FLDMAP_DEMO_Ginga_Main(FLDMAPFUNC_WORK * p_fwk, FIELDSYS_WORK * p_fsys, void * p_work)
{
	FLDMAP_DEMO_GINGA* p_dwk = p_work;
	u32 result[2];
	VecFx32 matrix;

	switch( p_dwk->seq ){
	case FLDMAP_DEMO_GINGA_SEQ_START:
		matrix = GFC_GetLookTarget( p_fsys->camera_ptr );
		FLD_DEMO_GINGA_Init( p_dwk->p_ginga, matrix.x, matrix.y + FLDMAP_DEMO_GINGA_Y_OFS, matrix.z );
		FLD_DEMO_DarkLight_Start( p_dwk->p_dark );
		p_dwk->seq++;
		break;
		
	case FLDMAP_DEMO_GINGA_SEQ_SCALEUP:
		result[0] = FLD_DEMO_GINGA_GetState( p_dwk->p_ginga );
		result[1] = FLD_DEMO_DarkLight_GetState( p_dwk->p_dark );
		
		if( (result[0] == FLD_DEMO_GINGA_MOTIONBL_REQWAIT) &&
			(result[1] == FLD_DEMO_DARKLIGHT_ENDWAIT)){	
			p_dwk->seq++;
		}
		break;
		
	case FLDMAP_DEMO_GINGA_SEQ_ENDREQ_WAIT:
		break;

	case FLDMAP_DEMO_GINGA_SEQ_ENDREQ:
		FLD_DEMO_GINGA_EndReq( p_dwk->p_ginga );
		p_dwk->wait = FLDMAP_DEMO_GINGA_DARKOFF_WAIT;
		p_dwk->seq++;
		break;
		
	case FLDMAP_DEMO_GINGA_SEQ_SCALEDOWN_DARKOFF_WAIT:
		p_dwk->wait --;
		if( p_dwk->wait <= 0 ){
			FLD_DEMO_DarkLight_EndReq( p_dwk->p_dark );
			p_dwk->seq++;
		}
		break;
		
	case FLDMAP_DEMO_GINGA_SEQ_SCALEDOWN_DARKOFF:
		result[0] = FLD_DEMO_GINGA_GetState( p_dwk->p_ginga );
		result[1] = FLD_DEMO_DarkLight_GetState( p_dwk->p_dark );
		
		if( (result[0] == FLD_DEMO_GINGA_MOTIONBL_END) &&
			(result[1] == FLD_DEMO_DARKLIGHT_END)){	
			p_dwk->seq++;
		}
		break;
		
	case FLDMAP_DEMO_GINGA_SEQ_END:
		break;

	default:
		break;
	}
	
	FLD_DEMO_GINGA_Main( p_dwk->p_ginga );
	FLD_DEMO_DarkLight_Main( p_dwk->p_dark );
}

//----------------------------------------------------------------------------
/**
 *		�y��͕��o�z
 *	@brief	�`�揈��
 */
//-----------------------------------------------------------------------------
static void FLDMAP_DEMO_Ginga_Draw(FLDMAPFUNC_WORK * p_fwk, FIELDSYS_WORK * p_fsys, void * p_work)
{
	FLDMAP_DEMO_GINGA* p_dwk = p_work;


	FLD_DEMO_GINGA_Draw( p_dwk->p_ginga );
}


//----------------------------------------------------------------------------
/**
 *	@brief	��̓f���J�n
 *
 *	@param	fsys	�t�B�[���h�V�X�e�����[�N
 *
 *	@return	�f�����[�N
 */
//-----------------------------------------------------------------------------
FLDMAPFUNC_WORK* FLDMAP_DEMO_Ginga_Start( FIELDSYS_WORK* fsys )
{
	static const FLDMAPFUNC_DATA FLDMAP_DEMO_Data = {
		FLDMAP_DEMO_GINGA_TASK_PRI,
		sizeof(FLDMAP_DEMO_GINGA),
		FLDMAP_DEMO_Ginga_Init,
		FLDMAP_DEMO_Ginga_Delete,
		FLDMAP_DEMO_Ginga_Main,
		FLDMAP_DEMO_Ginga_Draw
	};
	FLDMAPFUNC_WORK* p_fwk;
	p_fwk = FLDMAPFUNC_Create( fsys->fldmap->fmapfunc_sys, &FLDMAP_DEMO_Data );
	return p_fwk;
}

//----------------------------------------------------------------------------
/**
 *	@brief	��̓f���@�I��
 *
 *	@param	p_demo	�f�����[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void FLDMAP_DEMO_Ginga_End( FLDMAPFUNC_WORK* p_demo )
{
	FLDMAPFUNC_Delete( p_demo );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�I�����N�G�X�g
 *
 *	@param	p_demo	�f�����[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void FLDMAP_DEMO_Ginga_EndReq( FLDMAPFUNC_WORK* p_demo )
{
	FLDMAP_DEMO_GINGA* p_dwk = FLDMAPFUNC_GetFreeWork( p_demo );
	p_dwk->seq = FLDMAP_DEMO_GINGA_SEQ_ENDREQ;
}

//----------------------------------------------------------------------------
/**
 *	@brief	��͂̌��݂̃V�[�P���X�擾
 *
 *	@param	p_demo	�f�����[�N
 *
 *	@retval	FLDMAP_DEMO_GINGA_SEQ_START,		// �G�t�F�N�g�J�n
 *	@retval	FLDMAP_DEMO_GINGA_SEQ_SCALEUP,		// ��͊g��
 * 	@retval	FLDMAP_DEMO_GINGA_SEQ_ENDREQ_WAIT,	// �I�����N�G�X�g�҂�
 *	@retval	FLDMAP_DEMO_GINGA_SEQ_ENDREQ,		// �I���G�t�F�N�g�J�n
 *	@retval	FLDMAP_DEMO_GINGA_SEQ_SCALEDOWN_DARKOFF_WAIT,	// ��͏k
 *	@retval	FLDMAP_DEMO_GINGA_SEQ_SCALEDOWN_DARKOFF,	// ��͏k���{���邭
 *	@retval	FLDMAP_DEMO_GINGA_SEQ_END			// �I��
 */         
//-----------------------------------------------------------------------------
u32 FLDMAP_DEMO_Ginga_GetState( FLDMAPFUNC_WORK* p_demo )
{
	FLDMAP_DEMO_GINGA* p_dwk = FLDMAPFUNC_GetFreeWork( p_demo );
	return p_dwk->seq;
}




//-----------------------------------------------------------------------------
/**
 *
 *		��������́A�X�̃G�t�F�N�g�P��
 *
 */
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/**
 *
 *
 *		�ėp����
 * 
 */
//-----------------------------------------------------------------------------
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
//	���샏�[�N
//=====================================
typedef struct {
	s32 data;
	s32 s_data;
	s32 add_data;
	s32 count_max;
} FLD_DEMO_MOVE_PARAM;

//-------------------------------------
//	���샏�[�N
//=====================================
typedef struct {
	fx32 data;
	fx32 s_data;
	fx32 add_data;
	s32 count_max;
} FLD_DEMO_MOVE_PARAM_FX;


//-----------------------------------------------------------------------------
/**
 *					�v���g�^�C�v�錾
*/
//-----------------------------------------------------------------------------
static void FLD_DEMO_MoveInit( FLD_DEMO_MOVE_PARAM* p_data, s32 s_num, s32 e_num, s32 count );
static BOOL FLD_DEMO_MoveMain( FLD_DEMO_MOVE_PARAM* p_data, s32 count );
static void FLD_DEMO_MoveInit_FX( FLD_DEMO_MOVE_PARAM_FX* p_data, fx32 s_num, fx32 e_num, s32 count );
static BOOL FLD_DEMO_MoveMain_FX( FLD_DEMO_MOVE_PARAM_FX* p_data, s32 count );

// ���f��
static void FLD_DEMO_3DObjMdlLoad( FLD_3DOBJ_MDL* p_mdl, u32 arc_idx, u32 data_idx, u32 heap );
static void FLD_DEMO_3DObjMdlDelete( FLD_3DOBJ_MDL* p_mdl );

// �A�j��
static void FLD_DEMO_3DObjAnmLoad( FLD_3DOBJ_ANM* p_anm, const FLD_3DOBJ_MDL* cp_mdl, u32 arc_idx, u32 data_idx, u32 heap, NNSFndAllocator* pallocator );
static void FLD_DEMO_3DObjAnmDelete( FLD_3DOBJ_ANM* p_anm, NNSFndAllocator* pallocator );
static BOOL FLD_DEMO_3DObjAnmNoLoop( FLD_3DOBJ_ANM* p_anm );
static void FLD_DEMO_3DObjAnmLoop( FLD_3DOBJ_ANM* p_anm );
static void FLD_DEMO_3DObjAnmLoopAdd( FLD_3DOBJ_ANM* p_anm, fx32 add );
static void FLD_DEMO_3DObjAnmSet( FLD_3DOBJ_ANM* p_anm, fx32 num );
static fx32 FLD_DEMO_3DObjAnmGet( const FLD_3DOBJ_ANM* cp_anm );

// �`��I�u�W�F
static void FLD_DEMO_3DObjDrawInit( FLD_3DOBJ* p_draw, FLD_3DOBJ_MDL* cp_mdl );
static void FLD_DEMO_3DObjDrawAddAnm( FLD_3DOBJ* p_draw, FLD_3DOBJ_ANM* p_anm );
static void FLD_DEMO_3DObjDrawDraw( FLD_3DOBJ* p_draw );
static void FLD_DEMO_3DObjDrawSetDraw( FLD_3DOBJ* p_draw, BOOL flag );
static BOOL FLD_DEMO_3DObjDrawGetDraw( const FLD_3DOBJ* cp_draw );
static void FLD_DEMO_3DObjDrawSetMatrix( FLD_3DOBJ* p_draw, fx32 x, fx32 y, fx32 z );
static void FLD_DEMO_3DObjDrawGetMatrix( FLD_3DOBJ* p_draw, fx32* p_x, fx32* p_y, fx32* p_z );
static void FLD_DEMO_3DObjDrawSetScale( FLD_3DOBJ* p_draw, fx32 x, fx32 y, fx32 z );
static void FLD_DEMO_3DObjDrawGetScale( FLD_3DOBJ* p_draw, fx32* p_x, fx32* p_y, fx32* p_z );
static void FLD_DEMO_3DObjDrawSetRota( FLD_3DOBJ* p_draw, u16 rota, u32 way );
static u16 FLD_DEMO_3DObjDrawGetRota( FLD_3DOBJ* p_draw, u32 way );



//----------------------------------------------------------------------------
/**
 *	@brief	����p�����[�^
 *
 *	@param	p_data	���[�N
 *	@param	s_num	�J�n�l
 *	@param	e_num	�I���l
 *	@param	count	�ő�J�E���g
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void FLD_DEMO_MoveInit( FLD_DEMO_MOVE_PARAM* p_data, s32 s_num, s32 e_num, s32 count )
{
	p_data->data		= s_num;
	p_data->s_data		= s_num;
	p_data->add_data	= e_num - s_num;
	p_data->count_max	= count;
}

//----------------------------------------------------------------------------
/**
 *	@brief	����v�Z����
 *
 *	@param	p_data
 *	@param	count	���݃J�E���g
 *
 *	@retval TRUE	�I��
 *	@retval	FALSE	�����傤
 */
//-----------------------------------------------------------------------------
static BOOL FLD_DEMO_MoveMain( FLD_DEMO_MOVE_PARAM* p_data, s32 count )
{
	s32 local_count;
	BOOL ret;
	s32 num;
	
	if( count >= p_data->count_max ){
		local_count = p_data->count_max;
		ret = TRUE;
	}else{
		local_count = count;
		ret = FALSE;
	}

	// �v�Z
	num = p_data->add_data * local_count;
	num = num / p_data->count_max;
	num += p_data->s_data;

	// �ݒ�
	p_data->data = num;

	return ret;
}

//----------------------------------------------------------------------------
/**
 *	@brief	FX�R�Q�@�ł̔ėp�v�Z�֐�
 *
 *	@param	p_data		���[�N
 *	@param	s_num		�J�n�l
 *	@param	e_num		�I���l
 *	@param	count		����
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void FLD_DEMO_MoveInit_FX( FLD_DEMO_MOVE_PARAM_FX* p_data, fx32 s_num, fx32 e_num, s32 count )
{
	p_data->data		= s_num;
	p_data->s_data		= s_num;
	p_data->add_data	= e_num - s_num;
	p_data->count_max	= count;
}

//----------------------------------------------------------------------------
/**
 *	@brief	FX�R�Q�@�ėp����֐����C��
 *
 *	@param	p_data	���[�N
 *	@param	count	�J�E���g�l
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static BOOL FLD_DEMO_MoveMain_FX( FLD_DEMO_MOVE_PARAM_FX* p_data, s32 count )
{
	s32 local_count;
	BOOL ret;
	fx32 num;
	
	if( count >= p_data->count_max ){
		local_count = p_data->count_max;
		ret = TRUE;
	}else{
		local_count = count;
		ret = FALSE;
	}

	// �v�Z
	num = FX_Mul( p_data->add_data, local_count << FX32_SHIFT );
	num = FX_Div( num, p_data->count_max << FX32_SHIFT );
	num += p_data->s_data;

	// �ݒ�
	p_data->data = num;

	return ret;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�RD���f���ǂݍ���
 *
 *	@param	p_mdl		���f�����[�N
 *	@param	arc_idx		�A�[�J�C�uID
 *	@param	data_idx	�f�[�^IDX
 *	@param	heap		�q�[�v
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void FLD_DEMO_3DObjMdlLoad( FLD_3DOBJ_MDL* p_mdl, u32 arc_idx, u32 data_idx, u32 heap )
{
	FLD_3DObjMdlLoad( p_mdl, arc_idx, data_idx, heap );
}

//----------------------------------------------------------------------------
/**
 *	@brief	���f�����[�N�j��
 *
 *	@param	p_mdl ���f�����[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void FLD_DEMO_3DObjMdlDelete( FLD_3DOBJ_MDL* p_mdl )
{
	FLD_3DObjMdlDelete( p_mdl );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�RD�A�j���f�[�^�ǂݍ���
 *
 *	@param	p_anm		�A�j�����[�N
 *	@param	cp_mdl		���f�����[�N
 *	@param	arc_idx		�A�[�J�C�u�t�@�C��ID
 *	@param	data_idx	�f�[�^IDX
 *	@param	heap		�q�[�v
 *	@param	pallocator	�A���P�[�^
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void FLD_DEMO_3DObjAnmLoad( FLD_3DOBJ_ANM* p_anm, const FLD_3DOBJ_MDL* cp_mdl, u32 arc_idx, u32 data_idx, u32 heap, NNSFndAllocator* pallocator )
{
	FLD_3DObjAnmLoad( p_anm, cp_mdl, arc_idx, data_idx, heap, pallocator );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�RD�A�j���f�[�^�j��
 *
 *	@param	p_anm		�A�j�����[�N
 *	@param	pallocator	�A���P�[�^
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void FLD_DEMO_3DObjAnmDelete( FLD_3DOBJ_ANM* p_anm, NNSFndAllocator* pallocator )
{
	FLD_3DObjAnmDelete( p_anm, pallocator );
}

//----------------------------------------------------------------------------
/**
 *	@brief	���[�v�Đ�
 *
 *	@param	p_anm	�A�j���I�u�W�F�N�g
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void FLD_DEMO_3DObjAnmLoop( FLD_3DOBJ_ANM* p_anm )
{
	FLD_3DObjAnmLoop( p_anm, FX32_ONE );
}

//----------------------------------------------------------------------------
/**
 *	@brief	���[�v�Đ��Ői�߂�l���w��ł���
 *
 *	@param	p_anm	�A�j���I�u�W�F�N�g
 *	@param	add		�i�߂�l
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void FLD_DEMO_3DObjAnmLoopAdd( FLD_3DOBJ_ANM* p_anm, fx32 add )
{
	FLD_3DObjAnmLoop( p_anm, add );
}

//----------------------------------------------------------------------------
/**
 *	@brief	���[�v�Ȃ��Đ�
 *
 *	@param	p_anm �A�j�����[�N
 *
 *	@retval	TRUE	�Đ��I��
 *	@retval	FALSE	�Đ��r��
 */
//-----------------------------------------------------------------------------
static BOOL FLD_DEMO_3DObjAnmNoLoop( FLD_3DOBJ_ANM* p_anm )
{
	return FLD_3DObjAnmNoLoop( p_anm, FX32_ONE );
}


//----------------------------------------------------------------------------
/**
 *	@brief	�A�j���l�ݒ�
 *
 *	@param	p_anm	�A�j���I�u�W�F
 *	@param	num		�ݒ�l
 *	
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void FLD_DEMO_3DObjAnmSet( FLD_3DOBJ_ANM* p_anm, fx32 num )
{
	FLD_3DObjAnmSet( p_anm, num );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�A�j���t���[���擾
 *
 *	@param	p_anm	�A�j���I�u�W�F
 *
 *	@return	�t���[����
 */
//-----------------------------------------------------------------------------
static fx32 FLD_DEMO_3DObjAnmGet( const FLD_3DOBJ_ANM* cp_anm )
{
	return FLD_3DObjAnmGet( cp_anm );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�`��I�u�W�F�N�g������
 *
 *	@param	p_draw	���[�N
 *	@param	p_mdl	���f�����[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void FLD_DEMO_3DObjDrawInit( FLD_3DOBJ* p_draw, FLD_3DOBJ_MDL* p_mdl )
{
	FLD_3DObjInit( p_draw, p_mdl );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�A�j���f�[�^�������N
 *
 *	@param	p_draw	���[�N
 *	@param	p_anm	�A�j�����[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void FLD_DEMO_3DObjDrawAddAnm( FLD_3DOBJ* p_draw, FLD_3DOBJ_ANM* p_anm )
{
	FLD_3DObjAddAnm( p_draw, p_anm );
}

//----------------------------------------------------------------------------
/**
 *	@brief	���f���`��
 *
 *	@param	p_draw �`�惏�[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void FLD_DEMO_3DObjDrawDraw( FLD_3DOBJ* p_draw )
{
	FLD_3DObjDraw( p_draw );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�`��t���O�ݒ�
 *
 *	@param	p_draw	���[�N
 *	@param	flag	�t���O
 *
 *	@return	none
 *
 *	flag
 *		TRUE	�\��
 *		FALSE	��\��
 */
//-----------------------------------------------------------------------------
static void FLD_DEMO_3DObjDrawSetDraw( FLD_3DOBJ* p_draw, BOOL flag )
{
	FLD_3DObjSetDraw( p_draw, flag );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�`��t���O�擾
 *
 *	@param	cp_draw		���[�N
 *
 *	@retval	TRUE	�\��
 *	@retval	FALSE	��\��
 */
//-----------------------------------------------------------------------------
static BOOL FLD_DEMO_3DObjDrawGetDraw( const FLD_3DOBJ* cp_draw )
{
	return FLD_3DObjGetDraw( cp_draw );
}

//----------------------------------------------------------------------------
/**
 *	@brief	���W�ݒ�
 *	
 *	@param	p_draw		���[�N
 *	@param	x			�����W
 *	@param	y			�����W
 *	@param	z			�����W
 *	
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void FLD_DEMO_3DObjDrawSetMatrix( FLD_3DOBJ* p_draw, fx32 x, fx32 y, fx32 z )
{
	FLD_3DObjSetMatrix( p_draw, x, y, z );
}

//----------------------------------------------------------------------------
/**
 *	@brief	���W�擾
 *
 *	@param	p_draw	���[�N
 *	@param	p_x		�i�[��
 *	@param	p_y		�i�[��
 *	@param	p_z		�i�[��
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void FLD_DEMO_3DObjDrawGetMatrix( FLD_3DOBJ* p_draw, fx32* p_x, fx32* p_y, fx32* p_z )
{
	FLD_3DObjGetMatrix( p_draw, p_x, p_y, p_z );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�g�k�l�ݒ�
 *
 *	@param	p_draw	�`�惏�[�N
 *	@param	x		���g�k�l
 *	@param	y		���g�k�l
 *	@param	z 		���g�k�l
 *
 *	@return	noen
 */
//-----------------------------------------------------------------------------
static void FLD_DEMO_3DObjDrawSetScale( FLD_3DOBJ* p_draw, fx32 x, fx32 y, fx32 z )
{
	FLD_3DObjSetScale( p_draw, x, y, z );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�g�k�l���擾
 *
 *	@param	p_draw	�`�惏�[�N
 *	@param	p_x		�����W�擾��
 *	@param	p_y		�����W�擾��
 *	@param	p_z		�����W�擾��
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void FLD_DEMO_3DObjDrawGetScale( FLD_3DOBJ* p_draw, fx32* p_x, fx32* p_y, fx32* p_z )
{
	FLD_3DObjGetScale( p_draw, p_x, p_y, p_z );
}

//----------------------------------------------------------------------------
/**
 *	@brief	��]�e�ݒ�
 *
 *	@param	p_draw	�`�惏�[�N
 *	@param	rota	��]�p
 *	@param	way		����
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void FLD_DEMO_3DObjDrawSetRota( FLD_3DOBJ* p_draw, u16 rota, u32 way )
{
	FLD_3DObjSetRota( p_draw, rota, way );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�`�惏�[�N	��]�p�擾
 *	
 *	@param	p_draw	�`�惏�[�N
 *	@param	way		����
 *
 *	@return	��]�p
 */
//-----------------------------------------------------------------------------
static u16 FLD_DEMO_3DObjDrawGetRota( FLD_3DOBJ* p_draw, u32 way )
{
	return FLD_3DObjGetRota( p_draw, way );
}








//-----------------------------------------------------------------------------
/**
 *
 *
 *		�y��ʗh�炵�z
 * 
 */
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
/**
 *					�萔�錾
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	�V�[�P���X
//=====================================
enum{
	FLD_DEMO_SHAKE_SCRN_SEQ_LEFTUP_FRONT,
	FLD_DEMO_SHAKE_SCRN_SEQ_LEFTUP_BACK,
	FLD_DEMO_SHAKE_SCRN_SEQ_RIGHTDOWN_FRONT,
	FLD_DEMO_SHAKE_SCRN_SEQ_RIGHTDOWN_BACK,
	FLD_DEMO_SHAKE_SCRN_SEQ_CLEAN,
	FLD_DEMO_SHAKE_SCRN_SEQ_END,
};

//-----------------------------------------------------------------------------
/**
 *					�\���̐錾
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	��ʗh�炵���[�N
//=====================================
typedef struct _FLD_DEMO_SHAKE_SCRN{
	GF_CAMERA_PTR p_camera;		// �J�����\����
	GF_CAMERA_PTR p_fld_camera;	// �t�B�[���h�Ŏg�p����Ă���J�����\����
	FLD_DEMO_MOVE_PARAM_FX move_x;
	FLD_DEMO_MOVE_PARAM_FX move_y;
	VecFx32 target;
	VecFx32 def_mat;
	u32 seq;					// �V�[�P���X
	u32 move_count;				// ���춳��
	u32 shake_count;			// �h�炵��
} ;


//-----------------------------------------------------------------------------
/**
 *					�v���g�^�C�v�錾
*/
//-----------------------------------------------------------------------------
static void FldScrn_ShakeScrn_Clean( FLD_DEMO_SHAKE_SCRN* p_data );
static BOOL FldScrn_ShakeScrn_Move( FLD_DEMO_SHAKE_SCRN* p_data );
static void FldScrn_ShakeScrn_DataSet( FLD_DEMO_SHAKE_SCRN* p_data, fx32 x, fx32 y );


//----------------------------------------------------------------------------
/**
 *		�y��ʗh�炵�z
 *	@brief	��ʗh�炵���[�N�쐬
 *
 *	@param	heapID	�q�[�v
 *
 *	@return	���[�N�|�C���^
 */
//-----------------------------------------------------------------------------
FLD_DEMO_SHAKE_SCRN* FLD_DEMO_ShakeScrn_Alloc( u32 heapID )
{
	FLD_DEMO_SHAKE_SCRN* p_data;

	p_data = sys_AllocMemory( heapID, sizeof(FLD_DEMO_SHAKE_SCRN) );
	memset( p_data, 0, sizeof(FLD_DEMO_SHAKE_SCRN) );

	// �J�����쐬
	p_data->p_camera = GFC_AllocCamera( heapID );

	// �V�[�P���X���I���ɂ��Ă���
	p_data->seq  = FLD_DEMO_SHAKE_SCRN_SEQ_END;
	
	return p_data;
}

//----------------------------------------------------------------------------
/**
 *		�y��ʗh�炵�z
 *	@brief	��ʗh�炵���[�N�j��
 *
 *	@param	p_data	���[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void FLD_DEMO_ShakeScrn_Free( FLD_DEMO_SHAKE_SCRN* p_data )
{
	// �J�����j��
	GFC_FreeCamera( p_data->p_camera );
	sys_FreeMemoryEz( p_data );
}

//----------------------------------------------------------------------------
/**
 *		�y��ʗh�炵�z
 *	@brief	�J�����h�炵�J�n
 *
 *	@param	p_data			�f�[�^�i�[��
 *	@param	width			�h�炵��
 *	@param	height			�h�炵����
 *	@param	one_sync		�h�炵��1�؂�(�O����width�ړ��������)
 *	@param	count			�h�炵��
 *	@param	copy_camera		���܃t�B�[���h�Ŏg���Ă���J����
 *
 * one_sync�ɂ���
 *	0����width�ړ�������Ԃ̃V���N���ł��B
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void FLD_DEMO_ShakeScrn_Start( FLD_DEMO_SHAKE_SCRN* p_data, fx32 width, fx32 height, u32 one_sync, u32 count, GF_CAMERA_PTR copy_camera )
{
	// ���[�N������
	FldScrn_ShakeScrn_Clean( p_data );

	// �J�����f�[�^�R�s�[
	GFC_CopyCamera( copy_camera, p_data->p_camera );
	// ���݂̃^�[�Q�b�g���W�擾
	p_data->target = GFC_GetLookTarget( copy_camera );
	p_data->def_mat = p_data->target;
	// �^�[�Q�b�g���W�o�C���h
	GFC_BindCameraTarget( &p_data->target, p_data->p_camera );
	// �J������L����
	GFC_AttachCamera( p_data->p_camera );
	// �t�B�[���h�Ŏg�p����Ă���J�����ۑ�
	p_data->p_fld_camera = copy_camera;
		
	// ���샏�[�N�ݒ�
	FLD_DEMO_MoveInit_FX( &p_data->move_x, 0, width, one_sync );
	FLD_DEMO_MoveInit_FX( &p_data->move_y, 0, height, one_sync );

	// �����
	p_data->shake_count = count;

	// ����������
	Snd_SePlay( FLD_DEMO_LEGENDEFF_SND_03 );
}

//----------------------------------------------------------------------------
/**
 *		�y��ʗh�炵�z
 *	@brief	��ʗh�炵���C���֐�
 *
 *	@param	p_data	���[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void FLD_DEMO_ShakeScrn_Main( FLD_DEMO_SHAKE_SCRN* p_data )
{
	BOOL check;
	
	switch( p_data->seq ){
	case FLD_DEMO_SHAKE_SCRN_SEQ_LEFTUP_FRONT:
		p_data->move_count ++;
		check = FldScrn_ShakeScrn_Move( p_data );
		FldScrn_ShakeScrn_DataSet( p_data, p_data->move_x.data, p_data->move_y.data );
		if( check == TRUE ){
			p_data->seq ++;
		}
		break;
		
	case FLD_DEMO_SHAKE_SCRN_SEQ_LEFTUP_BACK:
		p_data->move_count --;
		FldScrn_ShakeScrn_Move( p_data );
		FldScrn_ShakeScrn_DataSet( p_data, p_data->move_x.data, p_data->move_y.data );
		if( p_data->move_count <= 0 ){
			p_data->seq ++;
		}
		break;
		
	case FLD_DEMO_SHAKE_SCRN_SEQ_RIGHTDOWN_FRONT:
		p_data->move_count ++;
		check = FldScrn_ShakeScrn_Move( p_data );
		FldScrn_ShakeScrn_DataSet( p_data, -p_data->move_x.data, -p_data->move_y.data );
		if( check == TRUE ){
			p_data->seq ++;
		}
		break;
		
	case FLD_DEMO_SHAKE_SCRN_SEQ_RIGHTDOWN_BACK:
		p_data->move_count --;
		FldScrn_ShakeScrn_Move( p_data );
		FldScrn_ShakeScrn_DataSet( p_data, -p_data->move_x.data, -p_data->move_y.data );
		if( p_data->move_count <= 0 ){

			// �h�炵�����O�ɂȂ�����I���
			p_data->shake_count --;
			if( p_data->shake_count > 0 ){
				p_data->seq = FLD_DEMO_SHAKE_SCRN_SEQ_LEFTUP_FRONT;
			}else{
				p_data->seq ++;
			}
		}
		break;

	case FLD_DEMO_SHAKE_SCRN_SEQ_CLEAN:
		// �J���������ɖ߂�
		GFC_AttachCamera( p_data->p_fld_camera );
		p_data->seq ++;
		break;
		
	case FLD_DEMO_SHAKE_SCRN_SEQ_END:
		break;

	default:
		break;
	}
}


//----------------------------------------------------------------------------
/**
 *		�y��ʗh�炵�z
 *	@brief	�J�����h�炵�I���`�F�b�N
 *
 *	@param	p_data	���[�N
 *
 *	@retval	TRUE	�I��
 *	@retval	FALSE	�r��
 */
//-----------------------------------------------------------------------------
BOOL FLD_DEMO_ShakeScrn_EndCheck( FLD_DEMO_SHAKE_SCRN* p_data )
{
	if( p_data->seq == FLD_DEMO_SHAKE_SCRN_SEQ_END ){
		return TRUE;
	}
	return FALSE;
}

//----------------------------------------------------------------------------
/**
 *		�y��ʗh�炵�z
 *	@brief	���[�N�̏�����
 *
 *	@param	p_data	���[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void FldScrn_ShakeScrn_Clean( FLD_DEMO_SHAKE_SCRN* p_data )
{
	memset( &p_data->move_x, 0, sizeof(FLD_DEMO_MOVE_PARAM_FX) );
	memset( &p_data->move_y, 0, sizeof(FLD_DEMO_MOVE_PARAM_FX) );
	memset( &p_data->target, 0, sizeof(VecFx32) );
	p_data->seq = 0;					// �V�[�P���X
	p_data->move_count = 0;				// ���춳��
	p_data->shake_count = 0;			// �h�炵��
}

//----------------------------------------------------------------------------
/**
 *		�y��ʗh�炵�z
 *	@brief	�v�Z
 *
 *	@param	p_data	���[�N
 *
 *	@retval	TRUE	�I��
 *	@retval	FALSE	�r��
 */
//-----------------------------------------------------------------------------
static BOOL FldScrn_ShakeScrn_Move( FLD_DEMO_SHAKE_SCRN* p_data )
{
	BOOL check;
	check = FLD_DEMO_MoveMain_FX( &p_data->move_x, p_data->move_count );
	FLD_DEMO_MoveMain_FX( &p_data->move_y, p_data->move_count );
	return check;
}

//----------------------------------------------------------------------------
/**
 *		�y��ʗh�炵�z
 *	@brief	���[�N�����Z
 *
 *	@param	p_data	���[�N
 *	@param	x		������
 *	@param	y		������
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void FldScrn_ShakeScrn_DataSet( FLD_DEMO_SHAKE_SCRN* p_data, fx32 x, fx32 y )
{
	p_data->target.x = p_data->def_mat.x + x;
	p_data->target.y = p_data->def_mat.y + y;
}

//----------------------------------------------------------------------------
/**
 *	@brief	���ݎc���ꐔ��Ԃ�
 *
 *	@param	p_data	���[�N
 *
 *	@return	�c���ꐔ
 */
//-----------------------------------------------------------------------------
u32 FLD_DEMO_ShakeScrn_GetNowCount( const FLD_DEMO_SHAKE_SCRN* p_data )
{
	return p_data->shake_count;
}

//----------------------------------------------------------------------------
/**
 *	@brief	���݂̂�ꕝ��Ԃ�
 *
 *	@param	p_data	���[�N
 *
 *	@return	��ꕝ
 */
//-----------------------------------------------------------------------------
fx32 FLD_DEMO_ShakeScrn_GetNowShakeWidth( const FLD_DEMO_SHAKE_SCRN* p_data )
{
	return p_data->move_x.add_data;
}

//----------------------------------------------------------------------------
/**
 *	@brief	��ꕝ��ݒ�
 *
 *	@param	p_data	���[�N
 *	@param	width	��ꕝ
 */
//-----------------------------------------------------------------------------
void FLD_DEMO_ShakeScrn_SetNowShakeWidth( FLD_DEMO_SHAKE_SCRN* p_data, fx32 width )
{
	p_data->move_x.add_data = width;
}




//-----------------------------------------------------------------------------
/**
 *
 *
 *		�y�t���b�V���z
 * 
 */
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
/**
 *					�萔�錾
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	�t���b�V���V�[�P���X
//=====================================
enum{
	FLD_DEMO_FLASH_ADD,
	FLD_DEMO_FLASH_SUB,
	FLD_DEMO_FLASH_CLEAN,
	FLD_DEMO_FLASH_END
};

#define FLD_DEMO_FLASH_ALPHASET_TCB	( 1024 )

//-----------------------------------------------------------------------------
/**
 *					�\���̐錾
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	�t���b�V�����[�N
//=====================================
typedef struct _FLD_DEMO_FLASH{
	FLD_DEMO_MOVE_PARAM alpha;	// ������
	int count;					// ����
	u32 alphamax;				// ���ő�l
	u32 in_sync;				// �t���b�V���C�����̃V���N��
	int seq;
	TCB_PTR	setalpha_tcb;		// ���l��ݒ肷��TCB
} ;


//-----------------------------------------------------------------------------
/**
 *					�v���g�^�C�v�錾
*/
//-----------------------------------------------------------------------------
static void FldDemo_FlashSetAlphaTcb( TCB_PTR tcb, void* p_work );

//----------------------------------------------------------------------------
/**
 *		�y�t���b�V���z
 *	@brief	�t���b�V�����[�N�m�ہ@�O���t�B�b�N�f�[�^�ݒ�
 *
 *	@param	heapID	�q�[�v
 *	@param	p_bgini	BG�R���g���[��
 *
 *	@return	���[�N
 */
//-----------------------------------------------------------------------------
FLD_DEMO_FLASH* FLD_DEMO_Flash_Alloc( u32 heapID )
{
	FLD_DEMO_FLASH* p_data;

	p_data = sys_AllocMemory( heapID, sizeof(FLD_DEMO_FLASH) );
	memset( p_data, 0, sizeof(FLD_DEMO_FLASH) );

	// �V�[�P���X���I���V�[�P���X�ɂ���
	p_data->seq = FLD_DEMO_FLASH_END;

	return p_data;
}

//----------------------------------------------------------------------------
/**
 *		�y�t���b�V���z
 *	@brief	�t���b�V���j��
 *
 *	@param	p_data	���[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void FLD_DEMO_Flash_Free( FLD_DEMO_FLASH* p_data )
{
	if( p_data->setalpha_tcb ){
		TCB_Delete( p_data->setalpha_tcb );
		p_data->setalpha_tcb = NULL;
	} 
	sys_FreeMemoryEz( p_data );
}

//----------------------------------------------------------------------------
/**
 *		�y�t���b�V���z
 *	@brief	�t���b�V���J�n
 *
 *	@param	p_data		���[�N
 *	@param	alphamax	�ő僿�l
 *	@param	out_sync	�t���b�V���A�E�g�V���N��
 *	@param	out_sync	�t���b�V���C���V���N��
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void FLD_DEMO_Flash_Start( FLD_DEMO_FLASH* p_data, u32 alphamax, u32 out_sync, u32 in_sync )
{
	// �����쒆�̂Ƃ��́A�^�X�N�����j������
	if(p_data->seq != FLD_DEMO_FLASH_END){ 
		if( p_data->setalpha_tcb != NULL ){
			TCB_Delete( p_data->setalpha_tcb );
			p_data->setalpha_tcb = NULL;
		} 
	}
	
	FLD_DEMO_MoveInit( &p_data->alpha, 0, alphamax, out_sync );
	p_data->count = 0;
	p_data->seq = FLD_DEMO_FLASH_ADD;
	p_data->in_sync = in_sync;
	p_data->alphamax = alphamax;

	// Ͻ���P�x
	GX_SetMasterBrightness( p_data->alpha.data );

	// ���l�ݒ�^�X�N�o�^
//	p_data->setalpha_tcb = VIntrTCB_Add( FldDemo_FlashSetAlphaTcb, p_data, FLD_DEMO_FLASH_ALPHASET_TCB );
	p_data->setalpha_tcb = VWaitTCB_Add( FldDemo_FlashSetAlphaTcb, p_data, FLD_DEMO_FLASH_ALPHASET_TCB );

	// �t���b�V���I
	Snd_SePlay( FLD_DEMO_LEGENDEFF_SND_02 );
}

//----------------------------------------------------------------------------
/**
 *		�y�t���b�V���z
 *	@brief	�I���`�F�b�N
 *
 *	@param	p_data	���[�N
 *
 *	@retval	TRUE	�I��
 *	@retval	FALSE	�r��
 */
//-----------------------------------------------------------------------------
BOOL FLD_DEMO_Flash_EndCheck( FLD_DEMO_FLASH* p_data )
{
	if( p_data->seq == FLD_DEMO_FLASH_END ){
		return TRUE;
	}
	return FALSE;
}

//----------------------------------------------------------------------------
/**
 *		�y�t���b�V���z
 *	@brief	�t���b�V�����C������
 *
 *	@param	p_data	���[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void FLD_DEMO_Flash_Main( FLD_DEMO_FLASH* p_data )
{
	BOOL check;
	
	switch( p_data->seq ){
	case FLD_DEMO_FLASH_ADD:
		p_data->count++;
		check = FLD_DEMO_MoveMain( &p_data->alpha, p_data->count );

		if( check == TRUE ){
			FLD_DEMO_MoveInit( &p_data->alpha, p_data->alphamax, 0, p_data->in_sync );
			p_data->count = 0;
			p_data->seq ++;
		}
		break;
		
	case FLD_DEMO_FLASH_SUB:
		p_data->count++;
		check = FLD_DEMO_MoveMain( &p_data->alpha, p_data->count );
		if( check == TRUE ){
			p_data->seq ++;
		}
		break;

	case FLD_DEMO_FLASH_CLEAN:
		// ���ݒ�TCB�j��
		TCB_Delete( p_data->setalpha_tcb );
		p_data->setalpha_tcb = NULL;

		p_data->seq ++;
		break;
		
	case FLD_DEMO_FLASH_END:
		break;

	default:
		break;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	���̃��l���擾
 */
//-----------------------------------------------------------------------------
int FLD_DEMO_Flash_GetAlpha( const FLD_DEMO_FLASH* cp_data )
{
	return cp_data->alpha.data;
}

//----------------------------------------------------------------------------
/**
 *		�y�t���b�V���z
 *	@brief	���lV�u�����N���Ԑݒ�^�X�N
 *
 *	@param	tcb		TCB���[�N
 *	@param	p_work	���[�N
 *	
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void FldDemo_FlashSetAlphaTcb( TCB_PTR tcb, void* p_work )
{
	FLD_DEMO_FLASH* p_data = p_work;
	// ���ݒ�
	GX_SetMasterBrightness( p_data->alpha.data );
}





//-----------------------------------------------------------------------------
/**
 *
 *
 *		�y��̓f���z
 * 
 */
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
/**
 *					�萔�錾
*/
//-----------------------------------------------------------------------------
#define FLD_DEMO_GINGA_MOTION_BL_EVA	( 8 )
#define FLD_DEMO_GINGA_MOTION_BL_EVB	( 8 )


// �`��֌W
// �\�t�g�E�F�A�X�v���C�g
#define FLD_DEMO_GINGA_SWSP_OBJNUM		(1)		// SWSP�I�u�W�F�N�g��
#define FLD_DEMO_GINGA_SWSP_CHARNUM	(1)		// SWSP�I�u�W�F�N�g��
#define FLD_DEMO_GINGA_SWSP_PLTTNUM	(1)		// SWSP�I�u�W�F�N�g��


//-------------------------------------
//	��̓I�u�W�F�N�g�f�[�^
//=====================================
#define FLD_DEMO_GINGA_OBJ_ROTA_ADD		( FX32_CONST( 2.0f ) )
#define FLD_DEMO_GINGA_OBJ_ROTA_SUB		( -FX32_CONST(0.050f) )
#define FLD_DEMO_GINGA_OBJ_SUB_ROTA_ADD	( -FX32_CONST( 40.0f ) )
#define FLD_DEMO_GINGA_OBJ_SCAL_S	( FX32_CONST( 0.0f ) )
#define FLD_DEMO_GINGA_OBJ_SCAL_E	( FX32_CONST( 1.0f ) )
#define FLD_DEMO_GINGA_OBJ_SCAL_COUNT	( 128 )	// �g��ɂ�����l
#define FLD_DEMO_GINGA_OBJ_SCAL_SUB_COUNT	( 32 )	// �k���ɂ�����l
#define FLD_DEMO_GINGA_OBJ_WAIT_COUNT		( 8 )	// �g�傩��k���̎��́Aweight
#define FLD_DEMO_GINGA_OBJ_FLASH_S_NUM	( FX32_CONST( 0.40f ) )

enum{
	FLD_DEMO_GINGA_OBJ_SCALE_UP,
	FLD_DEMO_GINGA_OBJ_SCALE_DOWN_WAIT,
	FLD_DEMO_GINGA_OBJ_ROTA_STOP_FLASH,
	FLD_DEMO_GINGA_OBJ_ROTA_STOP,
	FLD_DEMO_GINGA_OBJ_WAIT,
	FLD_DEMO_GINGA_OBJ_SCALE_DOWN,
};

#define FLD_DEMO_GINGA_ANM_NUM	(2)

//-----------------------------------------------------------------------------
/**
 *					�\���̐錾
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	��̓I�u�W�F�N�g
//=====================================
typedef struct {
	FLD_3DOBJ		draw;		// �`��I�u�W�F�N�g
	FLD_3DOBJ_MDL	mdl;		// ���f��
	FLD_3DOBJ_ANM	anm[FLD_DEMO_GINGA_ANM_NUM];		// �A�j��

	FLD_DEMO_FLASH* p_flash;	// �t���b�V���I�u�W�F�N�g

	// ����p�����[�^
	FLD_DEMO_MOVE_PARAM_FX scale;
	int count;
	int wait;
	TCB_PTR tcb;
	s32 rota_add;
	u16 rota;
	u16 seq;	// �V�[�P���X

	fx32 x_scale_way;	// 1or-1
} FLD_DEMO_CLM_GINGA;


//-------------------------------------
//	�t�B�[���h�O���t�B�b�N��ԕۑ��̈�
//=====================================
typedef struct _FLD_DEMO_GINGA{
	FIELDSYS_WORK * fsys;			// �t�B�[���h�V�X�e��
	
	FLD_DEMO_MOTIONBL motion_bl;

	// ��̓I�u�W�F�N�g
	FLD_DEMO_CLM_GINGA ginga;


	// �A���P�[�^
	NNSFndAllocator allocator;

	// �X�e�[�^�X
	u32 status;

	// ���[�J���V�[�P���X
	u32 sub_sequence;

	fx32 x;
	fx32 y;
	fx32 z;
} ;


//-----------------------------------------------------------------------------
/**
 *					�v���g�^�C�v�錾
*/
//-----------------------------------------------------------------------------

static void FLD_DEMO_GINGA_DeleteReq( FLD_DEMO_GINGA* p_data );


// �������@�j���@��{�^�X�N
static void FLD_DEMO_CLM_InitDrawSystem( TCB_PTR tcb, void* p_work );
static void FLD_DEMO_CLM_DeleteDrawSystem( TCB_PTR tcb, void* p_work );

// �\�t�g�E�F�A�X�v���C�g������ �j��
static SWSP_SYS_PTR FLD_DEMO_CLM_InitSwsp( void );
static void FLD_DEMO_CLM_DeleteSwsp( SWSP_SYS_PTR swsp );

// ��̓I�u�W�F�N�g
static void FLD_DEMO_CLM_GingaObjInit( FLD_DEMO_CLM_GINGA* p_obj, NNSFndAllocator* pallocator, u32 heapID, fx32 x, fx32 y, fx32 z );
static void FLD_DEMO_CLM_GingaObjDelete( FLD_DEMO_CLM_GINGA* p_obj, NNSFndAllocator* pallocator );
static BOOL FLD_DEMO_CLM_GingaObjMain( FLD_DEMO_CLM_GINGA* p_obj );
static void FLD_DEMO_CLM_GingaObjEndReq( FLD_DEMO_CLM_GINGA* p_obj );


//----------------------------------------------------------------------------
/**
 *		�y��̓f���z
 *	@brief	��̓f�����[�N�쐬
 *
 *	@param	heapID	�q�[�v
 *	@param	fsys	�t�B�[���h�V�X�e��
 *
 *	@return	��̓��[�N
 */
//-----------------------------------------------------------------------------
FLD_DEMO_GINGA* FLD_DEMO_GINGA_Alloc( FIELDSYS_WORK * fsys )
{
	FLD_DEMO_GINGA* p_tmp;
	p_tmp = sys_AllocMemory( USE_HEAPID, sizeof(FLD_DEMO_GINGA) );
	memset( p_tmp, 0, sizeof(FLD_DEMO_GINGA) );

	// FSYS��ۑ�
	p_tmp->fsys = fsys;

	// ��Ԃ��I���ɂ��Ă���
	p_tmp->status = FLD_DEMO_GINGA_MOTIONBL_END;

	// �A���P�[�^�쐬
	sys_InitAllocator( &p_tmp->allocator, USE_HEAPID, 32 );

	return p_tmp;
}

//----------------------------------------------------------------------------
/**
 *		�y��̓f���z
 *	@brief	���[�N�j������
 *
 *	@param	p_data	���[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void FLD_DEMO_GINGA_Free( FLD_DEMO_GINGA* p_data )
{
	// �j���o���܂���
	GF_ASSERT( p_data->status == FLD_DEMO_GINGA_MOTIONBL_END );
	sys_FreeMemoryEz( p_data );
}


//----------------------------------------------------------------------------
/**
 *		�y��̓f���z
 *	@brief	����������
 *
 *	@param	p_data	��̓��[�N
 *	@param	x		�����W
 *	@param	y		�����W
 *	@param	z		�����W
 *
 *	@return	�t�B�[���h�O���t�B�b�N��ԕۑ��̈�
 */
//-----------------------------------------------------------------------------
void FLD_DEMO_GINGA_Init( FLD_DEMO_GINGA* p_data, fx32 x, fx32 y, fx32 z )
{
	// ��Ԑݒ�
	p_data->status = FLD_DEMO_GINGA_MOTIONBL_INIT;

	// �\�����W���i�[
	p_data->x = x;
	p_data->y = y;
	p_data->z = z;

	// �������^�X�N�o�^
	TCB_Add( FLD_DEMO_CLM_InitDrawSystem, p_data, FLD_DEMO_GINGA_DRAWSYSTEM_INIT_TCB_PRI );
}

//----------------------------------------------------------------------------
/**
 *	@brief	��̓f���I�����N�G�X�g
 *
 *	@param	p_data	���[�N
 *
 *	@return	none
 *
 *	���̃��N�G�X�g�ŋ�͂����ڂ�Ńf�����I���܂�
 */
//-----------------------------------------------------------------------------
void FLD_DEMO_GINGA_EndReq( FLD_DEMO_GINGA* p_data )
{
	GF_ASSERT( p_data->status == FLD_DEMO_GINGA_MOTIONBL_REQWAIT );

	p_data->status = FLD_DEMO_GINGA_MOTIONBL_SCALEDOWN;
	FLD_DEMO_CLM_GingaObjEndReq( &p_data->ginga );
}

//----------------------------------------------------------------------------
/**
 *		�y��̓f���z
 *	@brief	��̓f���j��
 *
 *	@param	p_data	���[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void FLD_DEMO_GINGA_DeleteReq( FLD_DEMO_GINGA* p_data )
{
	p_data->sub_sequence = 0;
	p_data->status = FLD_DEMO_GINGA_MOTIONBL_DELETE;

	// �j���^�X�N�o�^
	TCB_Add( FLD_DEMO_CLM_DeleteDrawSystem, p_data, FLD_DEMO_GINGA_DRAWSYSTEM_INIT_TCB_PRI );
}

//----------------------------------------------------------------------------
/**
 *		�y��̓f���z
 *	@brief	���݂̏�Ԏ擾
 *	
 *	@param	cp_data	���[�N
 *
 *	@retval	DEMO_GINGA_MOTIONBL_INIT,			// ��������
 *	@retval	FLD_DEMO_GINGA_MOTIONBL_SCALEUP,	// �g�咆
 * 	@retval	FLD_DEMO_GINGA_MOTIONBL_REQWAIT,	// �k�����N�G�X�g�҂�
 *	@retval	FLD_DEMO_GINGA_MOTIONBL_SCALEDOWN,	// �k����
 *	@retval	DEMO_GINGA_MOTIONBL_DELTE,			// �j��������
 *	@retval	DEMO_GINGA_MOTIONBL_END				// �S��ƏI�� or �������O
 */
//-----------------------------------------------------------------------------
u32 FLD_DEMO_GINGA_GetState( const FLD_DEMO_GINGA* cp_data )
{
	return cp_data->status;
}

//----------------------------------------------------------------------------
/**
 *		�y��̓f���z
 *	@brief	���[�V�����u���[�W���̐ݒ�
 *
 *	@param	p_data		���[�N
 *	@param	a			Capture���W��
 *	@param	b			Capture��W��
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void FLD_DEMO_GINGA_SetMotionBlNum( FLD_DEMO_GINGA* p_data, int a, int b )
{
	MOTION_BL_ParamChg( p_data->motion_bl.motion_bl, a, b );
}


//----------------------------------------------------------------------------
/**
 *		�y��̓f���z
 *	@brief	�f���`�揈��
 *
 *	@param	p_data	���[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void FLD_DEMO_GINGA_Draw( FLD_DEMO_GINGA* p_data )
{
	if( (p_data->status == FLD_DEMO_GINGA_MOTIONBL_INIT) ||
		(p_data->status == FLD_DEMO_GINGA_MOTIONBL_DELETE) ||
		(p_data->status == FLD_DEMO_GINGA_MOTIONBL_END) ){
		return ;
	}
	
	// �N���A
	G3_Identity();	

	NNS_G3dGePushMtx();
	{
		FLD_DEMO_3DObjDrawDraw( &p_data->ginga.draw );
	}
	NNS_G3dGePopMtx(1);
}

//----------------------------------------------------------------------------
/**
 *		�y��̓f���z
 *	@brief	���C���֐�
 *
 *	@param	p_data	���[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void FLD_DEMO_GINGA_Main( FLD_DEMO_GINGA* p_data )
{
	BOOL result;
	
	if( (p_data->status == FLD_DEMO_GINGA_MOTIONBL_INIT) ||
		(p_data->status == FLD_DEMO_GINGA_MOTIONBL_DELETE) ||
		(p_data->status == FLD_DEMO_GINGA_MOTIONBL_END) ){
		return ;
	}
	
	result = FLD_DEMO_CLM_GingaObjMain( &p_data->ginga );

	// ��͂̃V�[�P���X��FLD_DEMO_GINGA_OBJ_SCALE_DOWN_WAIT
	// �ɂȂ�����k�����N�G�X�g�҂����
	if( p_data->status == FLD_DEMO_GINGA_MOTIONBL_SCALEUP ){
		if( p_data->ginga.seq == FLD_DEMO_GINGA_OBJ_SCALE_DOWN_WAIT ){
			p_data->status = FLD_DEMO_GINGA_MOTIONBL_REQWAIT;
		}
	}

	// �I�����N�G�X�g
	if( result == TRUE ){
		FLD_DEMO_GINGA_DeleteReq( p_data );
	}
}

//----------------------------------------------------------------------------
/**
 *		�y��̓f���z
 *	@brief	�`��V�X�e���@�������^�X�N
 *
 *	@param	tcb		TCB���[�N
 *	@param	p_work	���[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void FLD_DEMO_CLM_InitDrawSystem( TCB_PTR tcb, void* p_work )
{
	FLD_DEMO_GINGA* p_data = p_work;

	switch( p_data->sub_sequence ){
		
	case 0:
		FLD_DEMO_MOTIONBL_Init( &p_data->motion_bl, p_data->fsys, FLD_DEMO_GINGA_MOTION_BL_EVA, FLD_DEMO_GINGA_MOTION_BL_EVB );
		p_data->sub_sequence ++;
		break;

	case 1:
		FLD_DEMO_MOTIONBL_Main( &p_data->motion_bl );
		if( FLD_DEMO_MOTIONBL_GetState( &p_data->motion_bl ) == FLD_DEMO_MOTIONBL_SEQ_ENDWAIT ){
			p_data->sub_sequence ++;
		}
		break;

	case 2:	// �`��V�X�e���ƃ��[�N�̍쐬
		FLD_DEMO_CLM_GingaObjInit( &p_data->ginga, &p_data->allocator, USE_HEAPID,
			p_data->x, p_data->y, p_data->z	);
		p_data->sub_sequence++;
		break;
		
	case 3:
		p_data->status = FLD_DEMO_GINGA_MOTIONBL_SCALEUP;
		TCB_Delete( tcb );
		break;
	}
}

//----------------------------------------------------------------------------
/**
 *		�y��̓f���z
 *	@brief	�`��V�X�e���@�j���^�X�N
 *
 *	@param	tcb		TCB���[�N
 *	@param	p_work	���[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void FLD_DEMO_CLM_DeleteDrawSystem( TCB_PTR tcb, void* p_work )
{
	FLD_DEMO_GINGA* p_data = p_work;

	switch( p_data->sub_sequence ){
	case 0:	// �O���t�B�b�N�j��
		FLD_DEMO_CLM_GingaObjDelete( &p_data->ginga, &p_data->allocator );
		p_data->sub_sequence++;
		break;

	case 1:	// ���[�V�����u���[�j���@��ʃ��Z�b�g
		FLD_DEMO_MOTIONBL_EndReq( &p_data->motion_bl );
		p_data->sub_sequence++;
		break;

	case 2:
		FLD_DEMO_MOTIONBL_Main( &p_data->motion_bl );
		if( FLD_DEMO_MOTIONBL_GetState( &p_data->motion_bl ) == FLD_DEMO_MOTIONBL_SEQ_END ){
			p_data->sub_sequence ++;
		}
		break;
		
	case 3:
		p_data->status = FLD_DEMO_GINGA_MOTIONBL_END;
		TCB_Delete( tcb );
		break;
	}
}


//----------------------------------------------------------------------------
/**
 *		�y��̓f���z
 *	@brief	�\�t�g�E�F�A�X�v���C�g������
 *
 *	@return	�\�t�g�E�F�A�X�v���C�g���[�N
 */
//-----------------------------------------------------------------------------
static SWSP_SYS_PTR FLD_DEMO_CLM_InitSwsp( void )
{
	SWSP_SYSDATA swsp_sys_data = {
		FLD_DEMO_GINGA_SWSP_OBJNUM,
		FLD_DEMO_GINGA_SWSP_CHARNUM,			
		FLD_DEMO_GINGA_SWSP_PLTTNUM,
		0
	};
	swsp_sys_data.heap = USE_HEAPID;
	return SWSP_SysInit( &swsp_sys_data );
}

//----------------------------------------------------------------------------
/**
 *		�y��̓f���z
 *	@brief	�\�t�g�E�F�A�X�v���C�g�j��
 *
 *	@param	swsp	���[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void FLD_DEMO_CLM_DeleteSwsp( SWSP_SYS_PTR swsp )
{
	// �\�t�g�E�F�A�X�v���C�g
	SWSP_SysDelete( swsp );
}

//----------------------------------------------------------------------------
/**
 *		�y��̓f���z
 *	@brief	��̓I�u�W�F�N�g������
 *
 *	@param	p_obj			�I�u�W�F�N�g
 *	@param	pallocator		�A���P�[�^
 *	@param	heapID			�q�[�v
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void FLD_DEMO_CLM_GingaObjInit( FLD_DEMO_CLM_GINGA* p_obj, NNSFndAllocator* pallocator, u32 heapID, fx32 x, fx32 y, fx32 z )
{
	int i;


	// �t���b�V���I�u�W�F�N�g�쐬
	p_obj->p_flash = FLD_DEMO_Flash_Alloc( USE_HEAPID );
	
	// ���f���f�[�^�ǂݍ���
	FLD_DEMO_3DObjMdlLoad( &p_obj->mdl, ARC_FIELD_DEMO_CLI_GRA, NARC_demo_climax_ginga_nsbmd, heapID );

	for( i=0; i<FLD_DEMO_GINGA_ANM_NUM; i++ ){
		// �A�j���ǂݍ���
		FLD_DEMO_3DObjAnmLoad( &p_obj->anm[i], &p_obj->mdl, ARC_FIELD_DEMO_CLI_GRA, NARC_demo_climax_ginga_nsbca+i, heapID, pallocator );
	}
	// �`�惂�f��������
	FLD_DEMO_3DObjDrawInit( &p_obj->draw, &p_obj->mdl );
	for( i=0; i<FLD_DEMO_GINGA_ANM_NUM; i++ ){
		FLD_DEMO_3DObjDrawAddAnm( &p_obj->draw, &p_obj->anm[i] );
	}
	// ���Ђ傤
	FLD_DEMO_3DObjDrawSetMatrix( &p_obj->draw, x, y, z );
	// �������キ�p�����[�^
	FLD_DEMO_MoveInit_FX( &p_obj->scale, FLD_DEMO_GINGA_OBJ_SCAL_S, FLD_DEMO_GINGA_OBJ_SCAL_E, FLD_DEMO_GINGA_OBJ_SCAL_COUNT );
	p_obj->count = 0;
	FLD_DEMO_3DObjDrawSetScale( &p_obj->draw, p_obj->scale.data, p_obj->scale.data, p_obj->scale.data );
	// ��]���Z�l
	p_obj->rota_add  = FLD_DEMO_GINGA_OBJ_ROTA_ADD;
	// �V�[�P���X
	p_obj->seq = FLD_DEMO_GINGA_OBJ_SCALE_UP;

	p_obj->x_scale_way = FX32_ONE;
}

//----------------------------------------------------------------------------
/**
 *		�y��̓f���z
 *	@brief	��̓I�u�W�F�N�g�j��
 *	
 *	@param	p_obj	�I�u�W�F�N�g
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void FLD_DEMO_CLM_GingaObjDelete( FLD_DEMO_CLM_GINGA* p_obj, NNSFndAllocator* pallocator )
{
	int i;
	
	//�@���f���j��
	FLD_DEMO_3DObjMdlDelete( &p_obj->mdl );
	
	//�@�A�j���j��
	for( i=0; i<FLD_DEMO_GINGA_ANM_NUM; i++ ){
		FLD_DEMO_3DObjAnmDelete( &p_obj->anm[i], pallocator );
	}

	FLD_DEMO_Flash_Free( p_obj->p_flash );

	memset( p_obj, 0, sizeof(FLD_DEMO_CLM_GINGA) );
}

//----------------------------------------------------------------------------
/**
 *		�y��̓f���z
 *	@brief	��̓I�u�W�F�N�g���C��
 *
 *	@param	p_obj	�I�u�W�F�N�g
 *
 *	@retval	TRUE	�I��
 *	@retval	FALSE	�r��
 */
//-----------------------------------------------------------------------------
static BOOL FLD_DEMO_CLM_GingaObjMain( FLD_DEMO_CLM_GINGA* p_obj )
{
	BOOL result;
	int i;
	
	// �g��k��
	result = FLD_DEMO_MoveMain_FX( &p_obj->scale, p_obj->count );
	FLD_DEMO_3DObjDrawSetScale( &p_obj->draw, FX_Mul( p_obj->scale.data, p_obj->x_scale_way ), FX32_ONE, p_obj->scale.data );

	// �A�j��
	for( i=0; i<FLD_DEMO_GINGA_ANM_NUM; i++ ){
		FLD_DEMO_3DObjAnmLoopAdd( &p_obj->anm[i], p_obj->rota_add );	
	}

	// �t���b�V�����C��
	FLD_DEMO_Flash_Main( p_obj->p_flash );

	switch( p_obj->seq ){
	case FLD_DEMO_GINGA_OBJ_SCALE_UP:
		if( result != TRUE ){
			p_obj->count ++;
		}else{
			p_obj->seq++;
		}
		break;

	case FLD_DEMO_GINGA_OBJ_SCALE_DOWN_WAIT:
		break;
		
	case FLD_DEMO_GINGA_OBJ_ROTA_STOP_FLASH:
		p_obj->rota_add += FLD_DEMO_GINGA_OBJ_ROTA_SUB;

		if( p_obj->rota_add <= FLD_DEMO_GINGA_OBJ_FLASH_S_NUM ){
			FLD_DEMO_Flash_Start( p_obj->p_flash, 16, 12, 28 );
			p_obj->seq++;
		}
		break;

	case FLD_DEMO_GINGA_OBJ_ROTA_STOP:
		p_obj->rota_add += FLD_DEMO_GINGA_OBJ_ROTA_SUB;

		if( p_obj->rota_add <= 0 ){
			p_obj->seq++;

			// �҂�����
			p_obj->wait = FLD_DEMO_GINGA_OBJ_WAIT_COUNT;
		}
		break;

	case FLD_DEMO_GINGA_OBJ_WAIT:	// �҂�
		p_obj->wait --;
		if( p_obj->wait <= 0 ){
			// �����Z�V�[�P���X
			p_obj->seq++;

			// ��]�p�x
			p_obj->rota_add = FLD_DEMO_GINGA_OBJ_SUB_ROTA_ADD;

			// ���]
			p_obj->x_scale_way = -FX32_ONE;
			FLD_DEMO_3DObjDrawSetScale( &p_obj->draw, FX_Mul( p_obj->scale.data, p_obj->x_scale_way ), p_obj->scale.data, p_obj->scale.data );

			// �������キ
			FLD_DEMO_MoveInit_FX( &p_obj->scale, FLD_DEMO_GINGA_OBJ_SCAL_E, FLD_DEMO_GINGA_OBJ_SCAL_S, FLD_DEMO_GINGA_OBJ_SCAL_SUB_COUNT );
			p_obj->count = 0;
		}
		break;
		
	case FLD_DEMO_GINGA_OBJ_SCALE_DOWN:
		if( result != TRUE ){
			p_obj->count ++;
		}else{
			// �J�E���g�_�E���i�k�����j��result��TURE�Ȃ�I���		
			if( p_obj->seq == FLD_DEMO_GINGA_OBJ_SCALE_DOWN ){
				return TRUE;
			}
		}
		break;
	
	default:
		break;
	}
	return FALSE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�I�����N�G�X�g
 *
 *	@param	p_obj	��̓I�u�W�F�N�g
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void FLD_DEMO_CLM_GingaObjEndReq( FLD_DEMO_CLM_GINGA* p_obj )
{
	// ��]�X�g�b�v
	p_obj->seq = FLD_DEMO_GINGA_OBJ_ROTA_STOP_FLASH;
}



//-----------------------------------------------------------------------------
/**
 *
 *		�y�C�A�E�G�A�o��z
 *
*/
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
/**
 *					�萔�錾
*/
//-----------------------------------------------------------------------------
// �f�������̗���
enum{
	FLD_DEMO_LEGENDPOKE_APP_STARTWAIT,
	FLD_DEMO_LEGENDPOKE_APP_EFF_MAIN,
	FLD_DEMO_LEGENDPOKE_APP_POKE_APP_REQ,
	FLD_DEMO_LEGENDPOKE_APP_POKE_APP,
	FLD_DEMO_LEGENDPOKE_APP_CLEAR,
	FLD_DEMO_LEGENDPOKE_APP_END,
};


// �`���|�P�����萔
#define FLD_DEMO_LEGEND_POKE_OBJ_SCALE_S	( 0 )
#define FLD_DEMO_LEGEND_POKE_OBJ_SCALE_E	( FX32_CONST( 1.50f ) )
#define FLD_DEMO_LEGEND_POKE_OBJ_SCALE_EDOWN	( FX32_CONST( 1 ) )
#define FLD_DEMO_LEGEND_POKE_OBJ_COUNT		( 6 )
#define FLD_DEMO_LEGEND_POKE_OBJ_COUNTDOWN	( 2 )
#define FLD_DEMO_LEGEND_POKE_OBJ_MOVE_Y		( FX32_CONST( 32 ) )
#define FLD_DEMO_LEGEND_POKE_OBJ_MOVE_COUNT	( 44 )
enum{
	FLD_DEMO_LEGENDPOKEOBJ_SEQ_STARTWAIT,
	FLD_DEMO_LEGENDPOKEOBJ_SEQ_SCALE_UP,
	FLD_DEMO_LEGENDPOKEOBJ_SEQ_SCALE_DOWN,
	FLD_DEMO_LEGENDPOKEOBJ_SEQ_MOVE,
	FLD_DEMO_LEGENDPOKEOBJ_SEQ_END,
};

// 3D�̪�Ē萔
enum{
	FLD_DEMO_LEGENDEFF_ANMOBJ_CA,
	FLD_DEMO_LEGENDEFF_ANMOBJ_MA,
	FLD_DEMO_LEGENDEFF_ANMOBJ_TA,
	FLD_DEMO_LEGENDEFF_ANMOBJ_VA,
	FLD_DEMO_LEGENDEFF_ANMOBJ_NUM,
};
enum{
	FLD_DEMO_LEGENDEFF_SEQ_ANM,
	FLD_DEMO_LEGENDEFF_SEQ_FEDEOUT_WAIT,
	FLD_DEMO_LEGENDEFF_SEQ_FADEOUT,
	FLD_DEMO_LEGENDEFF_SEQ_END,
};

#define FLD_DEMO_LEGENDEFF_MOVE_Y_OFS	( 0x0*FX32_ONE )	// �|�P������Y���W���Ƒ����𒆐S�ɂ���̂Ń|�P�����̒��S�ɂł�悤�ɂ���
#define FLD_DEMO_LEGENDEFF_MOVE_Z_OFS	( -0x10*FX32_ONE )	// �|�P������z���W���ƃ|�P�����Ƃ��Ԃ�̂ŉ��ɂ���
#define FLD_DEMO_LEGENDEFF_MOVE_Y_DIS	( FX32_CONST( 0xF8 ) )
#define FLD_DEMO_LEGENDEFF_MOVE_SYNC	( 84 )
#define FLD_DEMO_LEGENDEFF_MOVE_SYNC_OUT	( 16 )


//-------------------------------------
//	���E�G�C�g
//=====================================
#define FLD_DEMO_LEGENDDEFF_SND_00_WAIT	( 82 )
#define FLD_DEMO_LEGENDDEFF_SND_01_WAIT	( 72 )
#define FLD_DEMO_LEGENDDEFF_SND_04_WAIT	( 300 )
#define FLD_DEMO_LEGENDDEFF_SND_05_WAIT	( 132 )



//-----------------------------------------------------------------------------
/**
 *					�\���̐錾
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	�`���|�P�������샏�[�N
//=====================================
typedef struct {
	FIELD_OBJ_PTR p_fldobj;
	FLD_DEMO_MOVE_PARAM_FX scale;
	FLD_DEMO_MOVE_PARAM_FX move;
	int count;
	int seq;
} FLD_DEMO_LEGENDPOKE;

//-------------------------------------
//	�`���|�P�����̂RD�̪�ăI�u�W�F�N�g
//=====================================
typedef struct {
	FLD_3DOBJ		draw;		// �`��I�u�W�F�N�g
	FLD_3DOBJ_MDL		mdl;		// ���f��
	FLD_3DOBJ_ANM		anm[FLD_DEMO_LEGENDEFF_ANMOBJ_NUM];	// �A�j��
	u32 seq;
	FLD_DEMO_MOVE_PARAM_FX scale;
	int count;

	int snd_count;	// ���J�E���g
	int snd_seq;

#ifdef FIELD_DEMO_DEBUG
	u32 debug_count;
#endif
} FLD_DEMO_LEGEND3D_EFF;


//-------------------------------------
//	�C�A�G�A�o��@���[�N
//=====================================
typedef struct _FLD_DEMO_LEGENDPOKE_APP{
	u32 seq;		// �V�[�P���X
	FIELDSYS_WORK * fsys;	// �t�B�[���h�V�X�e��
	FLD_DEMO_LEGENDPOKE legend_poke;// �`���|�P����
	FLD_DEMO_LEGEND3D_EFF legend_eff;// 3D�̪��OBJ
	NNSFndAllocator allocator;
	u32 heapID;

};

//-----------------------------------------------------------------------------
/**
 *					�v���g�^�C�v�錾
*/
//-----------------------------------------------------------------------------
static void FldDemo_LegendPokeObjInit( FLD_DEMO_LEGENDPOKE* p_obj, FIELDSYS_WORK * fsys, u32 obj_id );
static void FldDemo_LegendPokeObjStart( FLD_DEMO_LEGENDPOKE* p_obj );
static BOOL FldDemo_LegendPokeObjMain( FLD_DEMO_LEGENDPOKE* p_obj );
static BLACT_WORK_PTR FldDemo_LegendPokeObjFldobjGetActor( FLD_DEMO_LEGENDPOKE* p_obj );
static void FldDemo_LefendPokeObjScaleSet( BLACT_WORK_PTR act, fx32 scale );

static void FldDemo_LegendEffObjAlloc( FLD_DEMO_LEGEND3D_EFF* p_eff, u32 heapID, NNSFndAllocator* p_allocator );
static void FldDemo_LegendEffObjInit( FLD_DEMO_LEGEND3D_EFF* p_eff, fx32 x, fx32 y, fx32 z );
static void FldDemo_LegendEffObjDelete( FLD_DEMO_LEGEND3D_EFF* p_eff, NNSFndAllocator* p_allocator );
static u32 FldDemo_LegendEffObjMain( FLD_DEMO_LEGEND3D_EFF* p_eff );
static void FldDemo_LegendEffObjDraw( FLD_DEMO_LEGEND3D_EFF* p_eff );
static void FldDemo_LegendEffObjEndReq( FLD_DEMO_LEGEND3D_EFF* p_eff );
static void FldDemo_LegendEffObjMoveY( FLD_DEMO_LEGEND3D_EFF* p_eff, fx32 y );

static void FldDemo_LegendEffObjSndMain( FLD_DEMO_LEGEND3D_EFF* p_eff );

//----------------------------------------------------------------------------
/**
 *		�y�C�A�E�G�A�o��z
 *	@brief	���[�N�쐬
 *
 *	@param	heapID		�q�[�vID
 *
 *	@return	���[�N
 */
//-----------------------------------------------------------------------------
FLD_DEMO_LEGENDPOKE_APP* FLD_DEMO_LegendPokeApp_Alloc( u32 heapID, FIELDSYS_WORK * fsys )
{
	FLD_DEMO_LEGENDPOKE_APP* p_data;
	p_data = sys_AllocMemory( heapID, sizeof(FLD_DEMO_LEGENDPOKE_APP) );
	memset( p_data, 0, sizeof(FLD_DEMO_LEGENDPOKE_APP) );
	p_data->fsys = fsys;
	p_data->seq = FLD_DEMO_LEGENDPOKE_APP_STARTWAIT;
	p_data->heapID = heapID;

	// �A���P�[�^�[�쐬
	sys_InitAllocator( &p_data->allocator, heapID, 32 );

	// �̪�ăO���t�B�b�N�t�@�C��������
	FldDemo_LegendEffObjAlloc( &p_data->legend_eff, p_data->heapID, &p_data->allocator );
	
	return p_data;
}

//----------------------------------------------------------------------------
/**
 *		�y�C�A�E�G�A�o��z
 *	@brief	���[�N�j��
 *
 *	@param	p_data	���[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void FLD_DEMO_LegendPokeApp_Free( FLD_DEMO_LEGENDPOKE_APP* p_data )
{
	// �̪�Ĕj��
	FldDemo_LegendEffObjDelete( &p_data->legend_eff, &p_data->allocator );
	
	sys_FreeMemoryEz( p_data );
}

//----------------------------------------------------------------------------
/**
 *		�y�C�A�E�G�A�o��z
 *	@brief	�f���J�n
 *
 *	@param	p_data			���[�N
 *	@param	legendpoke_id	�`���|�P�����t�B�[���h�I�u�W�F�Ǘ�ID
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void FLD_DEMO_LegendPokeApp_Start( FLD_DEMO_LEGENDPOKE_APP* p_data, u32 legendpoke_id )
{
	VecFx32 mat;
	
	// �`���|�P�������[�N�쐬
	FldDemo_LegendPokeObjInit( &p_data->legend_poke, p_data->fsys, legendpoke_id );

	// �|�P�����̍��W�擾
	FieldOBJ_VecPosGet( p_data->legend_poke.p_fldobj, &mat );


	// �|�P�����̑�������|�P�����̒��S�֕\��Y�ʒu��ύX
	mat.y += FLD_DEMO_LEGENDEFF_MOVE_Y_OFS;
	mat.z += FLD_DEMO_LEGENDEFF_MOVE_Z_OFS;
	

	// �̪�Ẵ��[�N�쐬
	FldDemo_LegendEffObjInit( &p_data->legend_eff, mat.x, mat.y, mat.z );

	// �J�n
	p_data->seq  = FLD_DEMO_LEGENDPOKE_APP_EFF_MAIN;
}

//----------------------------------------------------------------------------
/**
 *		�y�C�A�E�G�A�o��z
 *	@brief	�t�B�[���h�I�u�W�F�N�g�I���`�F�b�N
 *
 *	@param	p_data	���[�N
 *
 *	@retval	TRUE	�I��
 *	@retval	FALSE	�r��
 */
//-----------------------------------------------------------------------------
BOOL FLD_DEMO_LegendPokeApp_EndCheck( FLD_DEMO_LEGENDPOKE_APP* p_data )
{
	if( (p_data->seq == FLD_DEMO_LEGENDPOKE_APP_STARTWAIT) ||
		(p_data->seq == FLD_DEMO_LEGENDPOKE_APP_END) ){
		return TRUE;
	}
	return FALSE;
}

//----------------------------------------------------------------------------
/**
 *		�y�C�A�E�G�A�o��z
 *	@brief	���C������
 *
 *	@param	p_data	���[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void FLD_DEMO_LegendPokeApp_Main( FLD_DEMO_LEGENDPOKE_APP* p_data )
{
	switch( p_data->seq ){
	case FLD_DEMO_LEGENDPOKE_APP_STARTWAIT:
		break;

	case FLD_DEMO_LEGENDPOKE_APP_EFF_MAIN:
		{
			u32 seq;
			seq = FldDemo_LegendEffObjMain( &p_data->legend_eff );
			if( seq == FLD_DEMO_LEGENDEFF_SEQ_FEDEOUT_WAIT ){
				p_data->seq ++;
			}
		}
		break;

	case FLD_DEMO_LEGENDPOKE_APP_POKE_APP_REQ:
		// �|�P�����o��
		FldDemo_LegendPokeObjStart( &p_data->legend_poke );
		// �̪�ďI��
		FldDemo_LegendEffObjEndReq( &p_data->legend_eff );

		FldDemo_LegendEffObjMain( &p_data->legend_eff );
		p_data->seq ++;
		break;
		
	case FLD_DEMO_LEGENDPOKE_APP_POKE_APP:
		FldDemo_LegendEffObjMain( &p_data->legend_eff );
		if( FldDemo_LegendPokeObjMain( &p_data->legend_poke ) ){
			p_data->seq ++;
		}
		break;

	case FLD_DEMO_LEGENDPOKE_APP_CLEAR:
		p_data->seq ++;
		break;
		
	case FLD_DEMO_LEGENDPOKE_APP_END:
		break;

	default:
		break;
	}
}

//----------------------------------------------------------------------------
/**
 *		�y�C�A�E�G�A�o��z
 *	@brief	�`�揈��
 *
 *	@param	p_data	���[�N
 *
 *	@return	none
 */	
//-----------------------------------------------------------------------------
void FLD_DEMO_LegendPokeApp_Draw( FLD_DEMO_LEGENDPOKE_APP* p_data )
{
	if( FLD_DEMO_LegendPokeApp_EndCheck( p_data ) == TRUE ){
		return;
	}
	
	FldDemo_LegendEffObjDraw( &p_data->legend_eff );
}

//----------------------------------------------------------------------------
/**
 *		�y�C�A�E�G�A�o��z
 *	@brief	�`���|�P�������[�N�̏�����
 *
 *	@param	p_obj	�I�u�W�F�N�g
 *	@param	fsys	�t�B�[���h�V�X�e��
 *	@param	obj_id	�I�u�W�F�N�gID
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void FldDemo_LegendPokeObjInit( FLD_DEMO_LEGENDPOKE* p_obj, FIELDSYS_WORK* fsys, u32 obj_id )
{
	// �t�B�[���h�I�u�W�F�N�g�擾
	p_obj->p_fldobj = FieldOBJSys_OBJIDSearch( fsys->fldobjsys, obj_id );
	GF_ASSERT( p_obj->p_fldobj );
	
	p_obj->count = 0;
	p_obj->seq = FLD_DEMO_LEGENDPOKEOBJ_SEQ_STARTWAIT;
}

//----------------------------------------------------------------------------
/**
 *		�y�C�A�E�G�A�o��z
 *	@brief	�A�j�������J�n
 *
 *	@param	p_obj	���[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void FldDemo_LegendPokeObjStart( FLD_DEMO_LEGENDPOKE* p_obj )
{
	BLACT_WORK_PTR p_act;
	VecFx32 ofs;

	// �A�N�^�[���[�N�擾
	p_act = FldDemo_LegendPokeObjFldobjGetActor( p_obj );
	
	// ����J�n
	p_obj->seq = FLD_DEMO_LEGENDPOKEOBJ_SEQ_SCALE_UP;

	// �t�B�[���h�I�u�W�F����J�n
	FieldOBJ_StatusBitSet_Vanish( p_obj->p_fldobj, FALSE );

	// �A�N�^�[�̊g�k�l�ݒ�
	FldDemo_LefendPokeObjScaleSet( p_act, FLD_DEMO_LEGEND_POKE_OBJ_SCALE_S );

	// �g�k
	FLD_DEMO_MoveInit_FX( &p_obj->scale, FLD_DEMO_LEGEND_POKE_OBJ_SCALE_S, FLD_DEMO_LEGEND_POKE_OBJ_SCALE_E, FLD_DEMO_LEGEND_POKE_OBJ_COUNT );

	// �ړ�
	FLD_DEMO_MoveInit_FX( &p_obj->move, FLD_DEMO_LEGEND_POKE_OBJ_MOVE_Y, 0, FLD_DEMO_LEGEND_POKE_OBJ_MOVE_COUNT );

	// ���W��ύX
	// Y�I�t�Z�b�g�ݒ�
	ofs.x = 0;
	ofs.y = p_obj->move.data;
	ofs.z = 0;
	FieldOBJ_VecDrawOffsOutSideSet( p_obj->p_fldobj, &ofs );
}

//----------------------------------------------------------------------------
/**
 *		�y�C�A�E�G�A�o��z
 *	@brief	�`���|�P�������C������
 *
 *	@param	p_obj	�I�u�W�F�N�g
 *
 *	@retval	TRUE	�I��
 *	@retval	FALSE	���쒆
 */
//-----------------------------------------------------------------------------
static BOOL FldDemo_LegendPokeObjMain( FLD_DEMO_LEGENDPOKE* p_obj )
{
	BLACT_WORK_PTR p_act;	// �A�N�^�[���[�N
	BOOL result;
	VecFx32 ofs;

	// �A�N�^�[���[�N�擾
	p_act = FldDemo_LegendPokeObjFldobjGetActor( p_obj );

	switch( p_obj->seq ){
	case FLD_DEMO_LEGENDPOKEOBJ_SEQ_STARTWAIT:
		break;
		
	case FLD_DEMO_LEGENDPOKEOBJ_SEQ_SCALE_UP:
		p_obj->count++;
		result = FLD_DEMO_MoveMain_FX( &p_obj->scale, p_obj->count );
		FldDemo_LefendPokeObjScaleSet( p_act, p_obj->scale.data );
		if( result == TRUE ){
			// �g�k
			FLD_DEMO_MoveInit_FX( &p_obj->scale, FLD_DEMO_LEGEND_POKE_OBJ_SCALE_E, FLD_DEMO_LEGEND_POKE_OBJ_SCALE_EDOWN, FLD_DEMO_LEGEND_POKE_OBJ_COUNTDOWN );
			p_obj->count = 0;
			p_obj->seq++;
		}
		break;

	case FLD_DEMO_LEGENDPOKEOBJ_SEQ_SCALE_DOWN:
		p_obj->count++;
		result = FLD_DEMO_MoveMain_FX( &p_obj->scale, p_obj->count );
		FldDemo_LefendPokeObjScaleSet( p_act, p_obj->scale.data );
		if( result == TRUE ){
			p_obj->count = 0;
			p_obj->seq++;
		}
		break;

	case FLD_DEMO_LEGENDPOKEOBJ_SEQ_MOVE:
		p_obj->count++;
		result = FLD_DEMO_MoveMain_FX( &p_obj->move, p_obj->count );
		// Y�I�t�Z�b�g�ݒ�
		ofs.x = 0;
		ofs.y = p_obj->move.data;
		ofs.z = 0;
		FieldOBJ_VecDrawOffsOutSideSet( p_obj->p_fldobj, &ofs );
		if( result == TRUE ){
			p_obj->seq++;
		}
		break;
		
	case FLD_DEMO_LEGENDPOKEOBJ_SEQ_END:
		return TRUE;
	
	default:
		break;
	}

	return FALSE;
}

//----------------------------------------------------------------------------
/**
 *		�y�C�A�E�G�A�o��z
 *	@brief	�`���ۂ����񃏁[�N����r���{�[�h�A�N�^�[�擾
 *
 *	@param	p_obj	���[�N
 *
 *	@return	�r���{�[�h�A�N�^�[
 */
//-----------------------------------------------------------------------------
static BLACT_WORK_PTR FldDemo_LegendPokeObjFldobjGetActor( FLD_DEMO_LEGENDPOKE* p_obj )
{
	LEGENDPOKE_WORK* p_legend_w;

	p_legend_w = FieldOBJ_DrawLegend_GetWrokPtr( p_obj->p_fldobj );
	return FieldOBJ_DrawLegend_GetBlactPtr( p_legend_w );
}

//----------------------------------------------------------------------------
/**
 *		�y�C�A�E�G�A�o��z
 *	@brief	�g�k�l�ݒ�
 *
 *	@param	act		�r���{�[�h�A�N�^�[
 *	@param	scale	�g�k�l
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void FldDemo_LefendPokeObjScaleSet( BLACT_WORK_PTR act, fx32 scale )
{
	VecFx32	scale_vec;
	scale_vec.x = scale;
	scale_vec.y = FX32_ONE;
	scale_vec.z = FX32_ONE;
	BLACT_ScaleSet( act, &scale_vec );
}


//----------------------------------------------------------------------------
/**
 *		�y�C�A�E�G�A�o��z
 *	@brief	�̪�ăI�u�W�F�@�`�揉����
 *
 *	@param	p_eff		�̪�ă��[�N
 *	@param	heapID		�q�[�vID
 *	@param	p_allocator	�A���P�[�^
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void FldDemo_LegendEffObjAlloc( FLD_DEMO_LEGEND3D_EFF* p_eff, u32 heapID, NNSFndAllocator* p_allocator )
{
	int i;
	
	// ���f���ǂݍ���
	FLD_DEMO_3DObjMdlLoad( &p_eff->mdl, ARC_FIELD_DEMO_CLI_GRA, NARC_demo_climax_kurotama_nsbmd, heapID );	

	// �A�j���ǂݍ���
	for( i=0; i<FLD_DEMO_LEGENDEFF_ANMOBJ_NUM; i++ ){
		FLD_DEMO_3DObjAnmLoad( &p_eff->anm[i],
				&p_eff->mdl, ARC_FIELD_DEMO_CLI_GRA,
				NARC_demo_climax_kurotama_nsbca + i, 
				heapID, p_allocator );
	}

	// �`��I�u�W�F�N�g�쐬
	FLD_DEMO_3DObjDrawInit( &p_eff->draw, &p_eff->mdl );
	for( i=0; i<FLD_DEMO_LEGENDEFF_ANMOBJ_NUM; i++ ){
		FLD_DEMO_3DObjDrawAddAnm( &p_eff->draw, &p_eff->anm[i] );
	}

	// �\��OFF
	FLD_DEMO_3DObjDrawSetDraw( &p_eff->draw, FALSE );
}

//----------------------------------------------------------------------------
/**
 *		�y�C�A�E�G�A�o��z
 *	@brief	�̪�ăI�u�W�F�N�g������
 *
 *	@param	p_eff			�̪�ăI�u�W�F�N�g
 *	@param	x				x���W
 *	@param	y				y���W
 *	@param	z				z���W
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void FldDemo_LegendEffObjInit( FLD_DEMO_LEGEND3D_EFF* p_eff, fx32 x, fx32 y, fx32 z )
{
	int i;

	// ����ݒ�
	FLD_DEMO_3DObjDrawSetMatrix( &p_eff->draw, x, y, z );

	FLD_DEMO_3DObjDrawSetScale( &p_eff->draw, FX32_ONE, FX32_ONE, FX32_ONE );

	// �t���[�����ݒ�
	for( i=0; i<FLD_DEMO_LEGENDEFF_ANMOBJ_NUM; i++ ){
		FLD_DEMO_3DObjAnmSet( &p_eff->anm[i], 0 );
	}
	p_eff->count = 0;
	p_eff->seq = 0;
	
	p_eff->snd_count = FLD_DEMO_LEGENDDEFF_SND_00_WAIT;
	p_eff->snd_seq = 0;

#ifdef FIELD_DEMO_DEBUG
	p_eff->debug_count = 0;
#endif

	// �\��ON
	FLD_DEMO_3DObjDrawSetDraw( &p_eff->draw, TRUE );
}

//----------------------------------------------------------------------------
/**
 *		�y�C�A�E�G�A�o��z
 *	@brief	�̪�ăI�u�W�F�N�g�j��
 *
 *	@param	p_eff			�̪�ăI�u�W�F�N�g
 *	@param	p_allocator		�A���P�[�^
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void FldDemo_LegendEffObjDelete( FLD_DEMO_LEGEND3D_EFF* p_eff, NNSFndAllocator* p_allocator )
{
	int i;
	// ���f���j��
	FLD_DEMO_3DObjMdlDelete( &p_eff->mdl );

	// �A�j���j��
	for( i=0; i<FLD_DEMO_LEGENDEFF_ANMOBJ_NUM; i++ ){
		FLD_DEMO_3DObjAnmDelete( &p_eff->anm[ i ], p_allocator );
	}
}

//----------------------------------------------------------------------------
/**
 *		�y�C�A�E�G�A�o��z
 *	@brief	�̪�ăI�u�W�F�N�g���C���֐�
 *
 *	@param	p_eff	�̪�ăI�u�W�F�N�g
 *
 * @retval	�V�[�P���X
 */
//-----------------------------------------------------------------------------
static u32 FldDemo_LegendEffObjMain( FLD_DEMO_LEGEND3D_EFF* p_eff )
{
	BOOL result;
	int i;

#ifdef FIELD_DEMO_DEBUG
	p_eff->debug_count ++;

	if( sys.trg & PAD_BUTTON_L ){
		OS_Printf( "p_eff->debug_count %d\n", p_eff->debug_count );
	}
#endif
	
	switch( p_eff->seq ){
	case FLD_DEMO_LEGENDEFF_SEQ_ANM:		// �A�j��
		// ���[�v�Ȃ��A�j��
		for( i=0; i<FLD_DEMO_LEGENDEFF_ANMOBJ_NUM; i++ ){
			result = FLD_DEMO_3DObjAnmNoLoop( &p_eff->anm[i] );
		}
		
		if( result == TRUE ){
			p_eff->seq ++;
		}
		break;

	case FLD_DEMO_LEGENDEFF_SEQ_FEDEOUT_WAIT:
		break;

	case FLD_DEMO_LEGENDEFF_SEQ_FADEOUT:	// �t�F�[�h�A�E�g
		p_eff->count  ++;
		result = FLD_DEMO_MoveMain_FX( &p_eff->scale, p_eff->count );
		FLD_DEMO_3DObjDrawSetScale( &p_eff->draw, p_eff->scale.data, p_eff->scale.data, p_eff->scale.data );
		if( result == TRUE ){
			p_eff->seq++;
			// �\��OFF
			FLD_DEMO_3DObjDrawSetDraw( &p_eff->draw, FALSE );
		}
		break;
		
	case FLD_DEMO_LEGENDEFF_SEQ_END:
		break;

	defautl:
		break;
	}

	// �����C��
	FldDemo_LegendEffObjSndMain( p_eff );

	return p_eff->seq;
}

//----------------------------------------------------------------------------
/**
 *	@brief	Y���W�ݒ�֐�
 *
 *	@param	p_eff	���[�N
 *	@param	y		�����W
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void FldDemo_LegendEffObjMoveY( FLD_DEMO_LEGEND3D_EFF* p_eff, fx32 y )
{
	VecFx32 matrix;

	// ���W�擾
	FLD_DEMO_3DObjDrawGetMatrix( &p_eff->draw, &matrix.x,  &matrix.y, &matrix.z );
	// �ݒ�
	matrix.y = y;
	FLD_DEMO_3DObjDrawSetMatrix( &p_eff->draw, matrix.x, matrix.y, matrix.z );
}

//----------------------------------------------------------------------------
/**
 *	@brief	���Ɩ炵���C��
 *
 *	@param	p_eff ���[�N
 */
//-----------------------------------------------------------------------------
static void FldDemo_LegendEffObjSndMain( FLD_DEMO_LEGEND3D_EFF* p_eff )
{
	switch( p_eff->snd_seq ){
	case 0:
		p_eff->snd_count --;
		if( p_eff->snd_count < 0 ){
			Snd_SePlay( FLD_DEMO_LEGENDEFF_SND_00 );
			p_eff->snd_count = FLD_DEMO_LEGENDDEFF_SND_01_WAIT;
			p_eff->snd_seq = 1;
		}
		break;
	
	case 1:
		p_eff->snd_count --;
		if( p_eff->snd_count < 0 ){
			Snd_SePlay( FLD_DEMO_LEGENDEFF_SND_01 );
			p_eff->snd_count = FLD_DEMO_LEGENDDEFF_SND_04_WAIT;
			p_eff->snd_seq = 2;
		}
		break;

	case 2:
		p_eff->snd_count --;
		if( p_eff->snd_count < 0 ){
			Snd_SePlay( FLD_DEMO_LEGENDEFF_SND_04 );
			p_eff->snd_count = FLD_DEMO_LEGENDDEFF_SND_05_WAIT;
			p_eff->snd_seq = 3;
		}
		break;

	case 3:
		p_eff->snd_count --;
		if( p_eff->snd_count < 0 ){
			Snd_SePlay( FLD_DEMO_LEGENDEFF_SND_05 );
			p_eff->snd_seq = 4;
		}
		break;

	case 4:
		break;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�̪�ďI�����N�G�X�g
 *
 *	@param	p_eff	�̪�ăI�u�W�F
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void FldDemo_LegendEffObjEndReq( FLD_DEMO_LEGEND3D_EFF* p_eff )
{
	p_eff->seq = FLD_DEMO_LEGENDEFF_SEQ_FADEOUT;
	p_eff->count = 0;

	// �g�k�ݒ�
	FLD_DEMO_MoveInit_FX( &p_eff->scale, FX32_ONE, 0, FLD_DEMO_LEGENDEFF_MOVE_SYNC_OUT );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�̪�ăI�u�W�F�N�g�`��
 *
 *	@param	p_eff �̪�ă��[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void FldDemo_LegendEffObjDraw( FLD_DEMO_LEGEND3D_EFF* p_eff )
{
	FLD_DEMO_3DObjDrawDraw( &p_eff->draw );
}


//-----------------------------------------------------------------------------
/**
 *
 *		�y�C�A�E�G�A�𒆐S���������o���z
 * 
 */
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
/**
 *					�萔�錾
*/
//-----------------------------------------------------------------------------
#define FLD_DEMO_BLACK_RING_NUM	( 3 )
//-------------------------------------
//	���
//=====================================
enum{
	FLD_DEMO_BLACKRING_STANDBY,
	FLD_DEMO_BLACKRING_DO,

	// �����O�I�u�W�F�N�g
	FLD_DEMO_BLACKRINGOBJ_STANDBY = 0,
	FLD_DEMO_BLACKRINGOBJ_DO,
};

// �O���t�B�b�NNO
#define FLD_DEMO_BLACK_RING_IMD	( NARC_demo_climax_ring_t_nsbmd )
//int FLD_DEMO_BLACK_RING_IMD	= NARC_demo_climax_ring_h_nsbmd;

// ���ѕ`��J�n�^�C�~���O
#define FLD_DEMO_BLACK_RING_START_TIMING	( 64 )

// 1���уI�u�W�F�N�g
#define FLD_DEMO_BLACKRING_OBJ_SSCALE	(0)
#define FLD_DEMO_BLACKRING_OBJ_ESCALE	( FX32_CONST(16) )
#define FLD_DEMO_BLACKRING_OBJ_SYNC		(96)
#define FLD_DEMO_BLACKRING_OBJ_OFS_X	(GRID_HALF_FX32)
#define FLD_DEMO_BLACKRING_OBJ_GRID_Y	(10)
#define FLD_DEMO_BLACKRING_OBJ_GRID_Z	(1)
//int FLD_DEMO_BLACKRING_OBJ_GRID_Y	= 2;
//int FLD_DEMO_BLACKRING_OBJ_GRID_Z	= 1;

//-----------------------------------------------------------------------------
/**
 *					�\���̐錾
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	������I�u�W�F�N�g
//=====================================
typedef struct {
	u32 status;					// �X�e�[�^�X
	FLD_3DOBJ draw;	// �`�惏�[�N
	FLD_DEMO_MOVE_PARAM_FX scale;	// �g�k�p�����[�^
	int count;
} FLD_DEMO_BLACK_RING_OBJ;


//-------------------------------------
//	�C�A�E�G�A�𒆐S�ɂ�����o���@���[�N
//=====================================
typedef struct _FLD_DEMO_BLACK_RING{
	FLD_3DOBJ_MDL mdl;			// ���f��
	FLD_DEMO_BLACK_RING_OBJ blackring[ FLD_DEMO_BLACK_RING_NUM ];
	u32 status;					// �X�e�[�^�X
	s32 start_count;
	s32 start_count_max;
	fx32 x;
	fx32 y;
	fx32 z;
	u16 rota_x;
	u16 rota_y;
	u16 rota_z;
};


//-----------------------------------------------------------------------------
/**
 *					�v���g�^�C�v�錾
*/
//-----------------------------------------------------------------------------
static FLD_DEMO_BLACK_RING* FLD_DEMO_BlackRing_Alloc_Core( u32 heapID, u32 dataIdx );
static void FLD_DEMO_BlackRing_Free_Core( FLD_DEMO_BLACK_RING* p_data );
static void FLD_DEMO_BlackRing_Start_Core( FLD_DEMO_BLACK_RING* p_data, fx32 x, fx32 y, fx32 z, s32 start_count, u16 rota_x, u16 rota_y, u16 rota_z );
static void FLD_DEMO_BlackRing_Main_Core( FLD_DEMO_BLACK_RING* p_data );
static void FLD_DEMO_BlackRing_Draw_Core( FLD_DEMO_BLACK_RING* p_data );

static void FLD_DEMO_BlackRingObj_Init( FLD_DEMO_BLACK_RING_OBJ* p_obj, FLD_3DOBJ_MDL* p_mdl );
static void FLD_DEMO_BlackRingObj_Delete( FLD_DEMO_BLACK_RING_OBJ* p_obj );
static void FLD_DEMO_BlackRingObj_Start( FLD_DEMO_BLACK_RING_OBJ* p_obj, fx32 s_scale, fx32 e_scale, int sync, fx32 x, fx32 y, fx32 z, u16 rota_x, u16 rota_y, u16 rota_z );
static void FLD_DEMO_BlackRingObj_Main( FLD_DEMO_BLACK_RING_OBJ* p_obj );
static void FLD_DEMO_BlackRingObj_Draw( FLD_DEMO_BLACK_RING_OBJ* p_obj );
static FLD_DEMO_BLACK_RING_OBJ* FLD_DEMO_BlackRingCleanObjGet( FLD_DEMO_BLACK_RING* p_data );


//----------------------------------------------------------------------------
/**
 *		�y�������O�z
 *	@brief	���[�N�m��Core
 *
 *	@param	heapID		�q�[�v
 *	@param	dataIdx		�f�[�^IDX
 *
 *	@return	���[�N
 */
//-----------------------------------------------------------------------------
static FLD_DEMO_BLACK_RING* FLD_DEMO_BlackRing_Alloc_Core( u32 heapID, u32 dataIdx )
{
	FLD_DEMO_BLACK_RING* p_data;
	int i;

	p_data = sys_AllocMemory( heapID, sizeof(FLD_DEMO_BLACK_RING) );
	memset( p_data, 0, sizeof(FLD_DEMO_BLACK_RING) );
	
	// ���f���ǂݍ���
	FLD_DEMO_3DObjMdlLoad( &p_data->mdl, ARC_FIELD_DEMO_CLI_GRA, dataIdx, heapID );

	// �`�揉����
	for( i=0; i<FLD_DEMO_BLACK_RING_NUM; i++ ){
		FLD_DEMO_BlackRingObj_Init( &p_data->blackring[i], &p_data->mdl );
	}
	p_data->status = FLD_DEMO_BLACKRING_STANDBY;

	return p_data;
}

//----------------------------------------------------------------------------
/**
 *		�y�������O�z
 *	@brief	���[�N�j��
 *
 *	@param	p_data	���[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void FLD_DEMO_BlackRing_Free_Core( FLD_DEMO_BLACK_RING* p_data )
{
	int i;

	// �`�揉����
	for( i=0; i<FLD_DEMO_BLACK_RING_NUM; i++ ){
		FLD_DEMO_BlackRingObj_Delete( &p_data->blackring[i] );
	}
	
	// ���f���f�[�^�j��
	FLD_DEMO_3DObjMdlDelete( &p_data->mdl );
	sys_FreeMemoryEz( p_data );
}

//----------------------------------------------------------------------------
/**
 *		�y�������O�z
 *	@brief�@�̪�ĊJ�n
 *
 *	@param	p_data	���[�N
 *	@param	x		�����W
 *	@param	y		�����W
 *	@param	z		�����W
 *	@param	start_count	�J�n�J�E���g�l
 *	@param	rota_x	y����]�p
 *	@param	rota_y	y����]�p
 *	@param	rota_z	z����]�p
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void FLD_DEMO_BlackRing_Start_Core( FLD_DEMO_BLACK_RING* p_data, fx32 x, fx32 y, fx32 z, s32 start_count, u16 rota_x, u16 rota_y, u16 rota_z )
{
	GF_ASSERT( p_data->status == FLD_DEMO_BLACKRING_STANDBY );

	p_data->start_count = 0;
	p_data->x = x;
	p_data->y = y;
	p_data->z = z;
	p_data->rota_x = rota_x;
	p_data->rota_y = rota_y;
	p_data->rota_z = rota_z;
	p_data->start_count_max = start_count;
	p_data->status = FLD_DEMO_BLACKRING_DO;
}

//----------------------------------------------------------------------------
/**
 *		�y�������O�z
 *	@brief	�̪�ă��C��
 *
 *	@param	p_data	���[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void FLD_DEMO_BlackRing_Main_Core( FLD_DEMO_BLACK_RING* p_data )
{
	int i;
	FLD_DEMO_BLACK_RING_OBJ* p_obj;
	
	// ���ˊǗ���
	p_data->start_count --;
	if( p_data->start_count < 0 ){
		p_data->start_count = p_data->start_count_max;
	
		p_obj = FLD_DEMO_BlackRingCleanObjGet( p_data );
		GF_ASSERT( p_obj );	// �󂫃I�u�W�F�Ȃ�

		// �I�u�W�F����J�n
		FLD_DEMO_BlackRingObj_Start( p_obj, 
				FLD_DEMO_BLACKRING_OBJ_SSCALE,
				FLD_DEMO_BLACKRING_OBJ_ESCALE,
				FLD_DEMO_BLACKRING_OBJ_SYNC,
				p_data->x, 
				p_data->y, 
				p_data->z,
				p_data->rota_x,
				p_data->rota_y,
				p_data->rota_z
				);
	}

	// �I�u�W�F�N�g���암
	for( i=0; i<FLD_DEMO_BLACK_RING_NUM; i++ ){
		FLD_DEMO_BlackRingObj_Main( &p_data->blackring[ i ] );
	}
}

//----------------------------------------------------------------------------
/**
 *		�y�������O�z
 *	@brief	�̪�ĕ`��
 *
 *	@param	p_data	���[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void FLD_DEMO_BlackRing_Draw_Core( FLD_DEMO_BLACK_RING* p_data )
{
	int i;
	// �I�u�W�F�N�g�`�敔
	for( i=0; i<FLD_DEMO_BLACK_RING_NUM; i++ ){
		FLD_DEMO_BlackRingObj_Draw( &p_data->blackring[ i ] );
	}
}







//----------------------------------------------------------------------------
/**
 *		�y�C�A�E�G�A�𒆐S���������o���z
 *	@brief	���[�N�m��
 *
 *	@param	heapID	�q�[�v
 *
 *	@return	���[�N
 */
//-----------------------------------------------------------------------------
FLD_DEMO_BLACK_RING* FLD_DEMO_BlackRing_Alloc( u32 heapID )
{
	return FLD_DEMO_BlackRing_Alloc_Core( heapID, FLD_DEMO_BLACK_RING_IMD );
}

//----------------------------------------------------------------------------
/**
 *		�y�C�A�E�G�A�𒆐S���������o���z
 *	@brief	���[�N�j��
 *
 *	@param	p_data	���[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void FLD_DEMO_BlackRing_Free( FLD_DEMO_BLACK_RING* p_data )
{
	FLD_DEMO_BlackRing_Free_Core( p_data );
}

//----------------------------------------------------------------------------
/**
 *		�y�C�A�E�G�A�𒆐S���������o���z
 *	@brief	�f���X�^�[�g
 *
 *	@param	p_data	���[�N
 *	@param	grid_x	�C�A�G�A�ʒu�O���b�h��
 *	@param	grid_y	�C�A�G�A�ʒu�O���b�h��
 *	@param	grid_z	�C�A�G�A�ʒu�O���b�h��
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void FLD_DEMO_BlackRing_Start( FLD_DEMO_BLACK_RING* p_data, u16 grid_x, u16 grid_y, u16 grid_z )
{
	FLD_DEMO_BlackRing_Start_Core( p_data, 
			GRID_SIZE_FX32( grid_x ) + FLD_DEMO_BLACKRING_OBJ_OFS_X,
			GRID_SIZE_FX32( grid_y ) + GRID_SIZE_FX32( FLD_DEMO_BLACKRING_OBJ_GRID_Y ),
			GRID_SIZE_FX32( grid_z ) + GRID_SIZE_FX32( FLD_DEMO_BLACKRING_OBJ_GRID_Z ),
			FLD_DEMO_BLACK_RING_START_TIMING, 0, 0, 0 );
}

//----------------------------------------------------------------------------
/**
 *		�y�C�A�E�G�A�𒆐S���������o���z
 *	@brief	�f�����C��
 *
 *	@param	p_data	���[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void FLD_DEMO_BlackRing_Main( FLD_DEMO_BLACK_RING* p_data )
{
	FLD_DEMO_BlackRing_Main_Core( p_data );
}

//----------------------------------------------------------------------------
/**
 *		�y�C�A�E�G�A�𒆐S���������o���z
 *	@brief	�`��
 *
 *	@param	p_data	���[�N
 *	
 *	@return	none
 */
//-----------------------------------------------------------------------------
void FLD_DEMO_BlackRing_Draw( FLD_DEMO_BLACK_RING* p_data )
{
	FLD_DEMO_BlackRing_Draw_Core( p_data );
}



//----------------------------------------------------------------------------
/**
 *		�y�C�A�E�G�A�𒆐S���������o���z
 *	@brief	�����O�I�u�W�F�N�g������
 *
 *	@param	p_obj		���[�N
 *	@param	p_mdl		���f��
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void FLD_DEMO_BlackRingObj_Init( FLD_DEMO_BLACK_RING_OBJ* p_obj, FLD_3DOBJ_MDL* p_mdl )
{
	memset( p_obj, 0, sizeof(FLD_DEMO_BLACK_RING_OBJ) );
	
	// �I�u�W�F�N�g������
	FLD_DEMO_3DObjDrawInit( &p_obj->draw, p_mdl );
	FLD_DEMO_3DObjDrawSetDraw( &p_obj->draw, FALSE );	// �\��OFF
	p_obj->status = FLD_DEMO_BLACKRINGOBJ_STANDBY;
}

//----------------------------------------------------------------------------
/**
 *		�y�C�A�E�G�A�𒆐S���������o���z
 *	@brief	�����O�I�u�W�F�N�g�j��
 *
 *	@param	p_obj	�I�u�W�F�N�g
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void FLD_DEMO_BlackRingObj_Delete( FLD_DEMO_BLACK_RING_OBJ* p_obj )
{
	memset( p_obj, 0, sizeof(FLD_DEMO_BLACK_RING_OBJ) );
}

//----------------------------------------------------------------------------
/**
 *		�y�C�A�E�G�A�𒆐S���������o���z
 *	@brief	�����O�I�u�W�F�N�g�@����J�n
 *
 *	@param	p_obj		�I�u�W�F�N�g
 *	@param	s_scale		�g�k�J�n�l
 *	@param	e_scale		�g�k�I���l
 *	@param	sync		�V���N��
 *	@param	x			�����W
 *	@param  y			�����W
 *	@param	z			�����W
 *	@param	rota_x		������]�p
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void FLD_DEMO_BlackRingObj_Start( FLD_DEMO_BLACK_RING_OBJ* p_obj, fx32 s_scale, fx32 e_scale, int sync, fx32 x, fx32 y, fx32 z, u16 rota_x, u16 rota_y, u16 rota_z )
{
	// ���d�Ăяo���`�F�b�N
	GF_ASSERT( p_obj->status == FLD_DEMO_BLACKRINGOBJ_STANDBY );

	// ���쏉����
	FLD_DEMO_MoveInit_FX( &p_obj->scale, s_scale, e_scale, sync );

	// �`�揉����
	FLD_DEMO_3DObjDrawSetDraw( &p_obj->draw, TRUE );
	FLD_DEMO_3DObjDrawSetMatrix( &p_obj->draw, x, y, z );
	FLD_DEMO_3DObjDrawSetScale( &p_obj->draw, s_scale, FX32_ONE, s_scale );
	FLD_DEMO_3DObjDrawSetRota( &p_obj->draw, rota_x, FLD_3DROTA_WAY_X );
	FLD_DEMO_3DObjDrawSetRota( &p_obj->draw, rota_y, FLD_3DROTA_WAY_Y );
	FLD_DEMO_3DObjDrawSetRota( &p_obj->draw, rota_z, FLD_3DROTA_WAY_Z );

	p_obj->status = FLD_DEMO_BLACKRINGOBJ_DO;
	p_obj->count = 0;
}

//----------------------------------------------------------------------------
/**
 *		�y�C�A�E�G�A�𒆐S���������o���z
 *	@brief	�����O�I�u�W�F�N�g���C������
 *
 *	@param	p_obj	�I�u�W�F�N�g���[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void FLD_DEMO_BlackRingObj_Main( FLD_DEMO_BLACK_RING_OBJ* p_obj )
{
	BOOL result;

	if( p_obj->status == FLD_DEMO_BLACKRINGOBJ_STANDBY ){
		return ;
	}
	
	// �g�k�l��ύX����
	p_obj->count ++;
	result = FLD_DEMO_MoveMain_FX( &p_obj->scale, p_obj->count );
	FLD_DEMO_3DObjDrawSetScale( &p_obj->draw, p_obj->scale.data, FX32_ONE, p_obj->scale.data );

	if( result == TRUE ){
		p_obj->status = FLD_DEMO_BLACKRINGOBJ_STANDBY;
	}
}

//----------------------------------------------------------------------------
/**
 *		�y�C�A�E�G�A�𒆐S���������o���z
 *	@brief	�����O�I�u�W�F�N�g�`�揈��
 *
 *	@param	p_obj	���[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void FLD_DEMO_BlackRingObj_Draw( FLD_DEMO_BLACK_RING_OBJ* p_obj )
{
	FLD_DEMO_3DObjDrawDraw( &p_obj->draw );
}

//----------------------------------------------------------------------------
/**
 *		�y�C�A�E�G�A�𒆐S���������o���z
 *	@brief	�󂢂Ă��郊���O�I�u�W�F�N�g�擾
 *
 *	@param	p_data	�I�u�W�F�N�g���[�N
 *
 *	@return	�󂢂Ă���I�u�W�F�N�g���[�N
 */
//-----------------------------------------------------------------------------
static FLD_DEMO_BLACK_RING_OBJ* FLD_DEMO_BlackRingCleanObjGet( FLD_DEMO_BLACK_RING* p_data )
{
	int i;

	for( i=0; i<FLD_DEMO_BLACK_RING_NUM; i++ ){
		if( p_data->blackring[i].status == FLD_DEMO_BLACKRINGOBJ_STANDBY ){
			return &p_data->blackring[i];
		}
	}
	return NULL;
}





//-----------------------------------------------------------------------------
/**
 *
 *		�y����̗����o���z
 * 
 */
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
/**
 *					�萔�錾
*/
//-----------------------------------------------------------------------------
#ifdef PM_DEBUG
//#define FLD_DEMO_ANT_DEBUG
#endif

#ifdef FLD_DEMO_ANT_DEBUG
int FLD_DEMO_ANTEGG_DEBUG_SEQ = 0;

int FLD_DEMO_ANTEGG_CUT00_ROTA_X =	( 62623 );
int FLD_DEMO_ANTEGG_CUT00_ROTA_Y = 	( 32949 );
int FLD_DEMO_ANTEGG_CUT00_ROTA_Z = 	( 32942 );
int FLD_DEMO_ANTEGG_CUT00_OFS_X	 = 	( 170920 );
int FLD_DEMO_ANTEGG_CUT00_OFS_Y	 = 	( -225940 );
int FLD_DEMO_ANTEGG_CUT00_OFS_Z	 =	( -747638 );
#else



#endif


//-------------------------------------
//	�V�[���O�O
//=====================================
#if ( PM_VERSION == VERSION_DIAMOND )

#define FLD_DEMO_ANTEGG_CUT00_ROTA_X	( 62623 )
#define FLD_DEMO_ANTEGG_CUT00_ROTA_Y	( 32949 )
#define FLD_DEMO_ANTEGG_CUT00_ROTA_Z	( 32942 )
#define FLD_DEMO_ANTEGG_CUT00_OFS_X		( 170920 )
#define FLD_DEMO_ANTEGG_CUT00_OFS_Y		( -225940 )
#define FLD_DEMO_ANTEGG_CUT00_OFS_Z		( -747638 )

#elif( PM_VERSION == VERSION_PEARL )

#define FLD_DEMO_ANTEGG_CUT00_ROTA_X	( 58983 )
#define FLD_DEMO_ANTEGG_CUT00_ROTA_Y	( 30219 )
#define FLD_DEMO_ANTEGG_CUT00_ROTA_Z	( 34216 )
#define FLD_DEMO_ANTEGG_CUT00_OFS_X		( -307200 )
#define FLD_DEMO_ANTEGG_CUT00_OFS_Y		( -87729 )
#define FLD_DEMO_ANTEGG_CUT00_OFS_Z		( -629017 )

#endif



#define FLD_DEMO_ANTEGG_CUT01_ROTA_X	( 58801 )
#define FLD_DEMO_ANTEGG_CUT01_ROTA_Y	( 49507 )
#define FLD_DEMO_ANTEGG_CUT01_ROTA_Z	( 32760 )
#define FLD_DEMO_ANTEGG_CUT01_OFS_X		( 1141327 )
#define FLD_DEMO_ANTEGG_CUT01_OFS_Y		( 323947 )
#define FLD_DEMO_ANTEGG_CUT01_OFS_Z		( -598296 )

#define FLD_DEMO_ANTEGG_CUT02_ROTA_X	( 59165 )
#define FLD_DEMO_ANTEGG_CUT02_ROTA_Y	( 21301 )
#define FLD_DEMO_ANTEGG_CUT02_ROTA_Z	( 31122 )
#define FLD_DEMO_ANTEGG_CUT02_OFS_X		( -811008 )
#define FLD_DEMO_ANTEGG_CUT02_OFS_Y		( 356351 )
#define FLD_DEMO_ANTEGG_CUT02_OFS_Z		( -2162696 )



#define FLD_DEMO_ANTEGG_ANM_NUM	(3)	// �R���A�j���[�V������

//-----------------------------------------------------------------------------
/**
 *					�\���̐錾
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	����̗��@���[�N
//=====================================
typedef struct _FLD_DEMO_ANTEGG {
	FLD_3DOBJ draw;		// �`�惏�[�N
	FLD_3DOBJ_MDL mdl;		// ���f��
	FLD_3DOBJ_ANM anm[FLD_DEMO_ANTEGG_ANM_NUM];	// �A�j��

	NNSFndAllocator allocator;	// �A���P�[�^
} ;


//-----------------------------------------------------------------------------
/**
 *					�v���g�^�C�v�錾
*/
//-----------------------------------------------------------------------------
static FLD_DEMO_ANTEGG* FLD_DEMO_AntEgg_Alloc( u32 heapID, u32 dataIdx );
static void FLD_DEMO_AntEgg_Free( FLD_DEMO_ANTEGG* p_data );
static void FLD_DEMO_AntEgg_Start( FLD_DEMO_ANTEGG* p_data, fx32 x, fx32 y, fx32 z, u16 rota_x, u16 rota_y, u16 rota_z );
static void FLD_DEMO_AntEgg_Main( FLD_DEMO_ANTEGG* p_data );
static void FLD_DEMO_AntEgg_Draw( FLD_DEMO_ANTEGG* p_data );



//----------------------------------------------------------------------------
/**
 *		�y����̗����o���z
 *	@brief	���[�N�m��
 *
 *	@param	heapID	�q�[�vID
 *	@param	dataIdx	�f�[�^�C���f�b�N�X�@�A�[�J�C�u�f�[�^
 *
 *	@return	���[�N�|�C���^
 */
//-----------------------------------------------------------------------------
static FLD_DEMO_ANTEGG* FLD_DEMO_AntEgg_Alloc( u32 heapID, u32 dataIdx )
{
	FLD_DEMO_ANTEGG* p_data;
	int i;
	p_data = sys_AllocMemory( heapID, sizeof(FLD_DEMO_ANTEGG) );
	memset( p_data, 0, sizeof(FLD_DEMO_ANTEGG) );

	// �A���P�[�^�쐬
	sys_InitAllocator( &p_data->allocator, heapID, 32 );	

	// ���f���ǂݍ���
	FLD_DEMO_3DObjMdlLoad( &p_data->mdl, ARC_FIELD_DEMO_CLI_GRA, dataIdx, heapID );
	for( i=0; i<FLD_DEMO_ANTEGG_ANM_NUM; i++ ){
		FLD_DEMO_3DObjAnmLoad( &p_data->anm[i], &p_data->mdl, ARC_FIELD_DEMO_CLI_GRA, NARC_demo_climax_aritama_nsbta + i, heapID, &p_data->allocator );
	}
	FLD_DEMO_3DObjDrawInit( &p_data->draw, &p_data->mdl );
	for( i=0; i<FLD_DEMO_ANTEGG_ANM_NUM; i++ ){
		FLD_DEMO_3DObjDrawAddAnm( &p_data->draw, &p_data->anm[i] );
	}
	FLD_DEMO_3DObjDrawSetDraw( &p_data->draw, FALSE );

	return p_data;
}

//----------------------------------------------------------------------------
/**
 *		�y����̗����o���z
 *	@brief	���[�N�j��
 *
 *	@param	p_data	���[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void FLD_DEMO_AntEgg_Free( FLD_DEMO_ANTEGG* p_data )
{
	int i;

	FLD_DEMO_3DObjMdlDelete( &p_data->mdl );
	for( i=0; i<FLD_DEMO_ANTEGG_ANM_NUM; i++ ){
		FLD_DEMO_3DObjAnmDelete( &p_data->anm[i], &p_data->allocator );
	}
	sys_FreeMemoryEz( p_data );
}

//----------------------------------------------------------------------------
/**
 *		�y����̗����o���z
 *	@brief	���X�^�[�g
 *
 *	@param	p_data	���[�N
 *	@param	x		�����W
 *	@param	y		�����W
 *	@param	z		�����W
 *	@param	rota_x	��]�p��
 *	@param	rota_y	��]�p��
 *	@param	rota_z	��]�p��
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void FLD_DEMO_AntEgg_Start( FLD_DEMO_ANTEGG* p_data, fx32 x, fx32 y, fx32 z, u16 rota_x, u16 rota_y, u16 rota_z )
{
	FLD_DEMO_3DObjDrawSetMatrix( &p_data->draw, 
			x, 
			y, 
			z );

	FLD_DEMO_3DObjDrawSetRota( &p_data->draw, rota_x, FLD_3DROTA_WAY_X );
	FLD_DEMO_3DObjDrawSetRota( &p_data->draw, rota_z, FLD_3DROTA_WAY_Z );
	FLD_DEMO_3DObjDrawSetRota( &p_data->draw, rota_y, FLD_3DROTA_WAY_Y );
	

	FLD_DEMO_3DObjDrawSetDraw( &p_data->draw, TRUE );
}

//----------------------------------------------------------------------------
/**
 *		�y����̗����o���z
 *	@brief	�����상�C��
 *
 *	@param	p_data	���[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void FLD_DEMO_AntEgg_Main( FLD_DEMO_ANTEGG* p_data )
{
	int i;
	
	// �A�j���������ǉ������\��
	for( i=0; i<FLD_DEMO_ANTEGG_ANM_NUM; i++ ){
		FLD_DEMO_3DObjAnmLoop( &p_data->anm[i] );
	}
	
}

//----------------------------------------------------------------------------
/**
 *		�y����̗����o���z
 *	@brief	����̗��`��
 *
 *	@param	p_data ���[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void FLD_DEMO_AntEgg_Draw( FLD_DEMO_ANTEGG* p_data )
{
	FLD_DEMO_3DObjDrawDraw( &p_data->draw );
}

//----------------------------------------------------------------------------
/**
 *		�y����̗����o���z
 *	@brief	����̗��@���[�N�쐬
 *
 *	@param	heapID 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
FLD_DEMO_ANTEGG* FLD_DEMO_AntEgg_Cut_Alloc( u32 heapID )
{
	return FLD_DEMO_AntEgg_Alloc( heapID, NARC_demo_climax_aritama_nsbmd );
}

//----------------------------------------------------------------------------
/**
 *		�y����̗����o���z
 *	@brief	����̗��@���[�N�j��
 *
 *	@param	p_data	���[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void FLD_DEMO_AntEgg_Cut_Free( FLD_DEMO_ANTEGG* p_data )
{
	FLD_DEMO_AntEgg_Free( p_data );
}

//----------------------------------------------------------------------------
/**
 *		�y����̗����o���z
 *	@brief	���C������
 *
 *	@param	p_data �@���[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void FLD_DEMO_AntEgg_Cut_Main( FLD_DEMO_ANTEGG* p_data )
{
	VecFx32 matrix;

	FLD_DEMO_AntEgg_Main( p_data );

#ifdef FLD_DEMO_ANT_DEBUG
	if( sys.tp_trg ){
		FLD_DEMO_ANTEGG_DEBUG_SEQ = (FLD_DEMO_ANTEGG_DEBUG_SEQ + 1) % 3;
		if( FLD_DEMO_ANTEGG_DEBUG_SEQ == 0 ){
			OS_Printf( "��]\n" );
		}else if( FLD_DEMO_ANTEGG_DEBUG_SEQ == 1 ){
			OS_Printf( "���W\n" );
		}else if( FLD_DEMO_ANTEGG_DEBUG_SEQ == 2 ){
			OS_Printf( "��Ring\n" );
		}
	}

	switch(FLD_DEMO_ANTEGG_DEBUG_SEQ){
	case 0:	
		if( sys.cont & PAD_BUTTON_R ){
			if( sys.cont & PAD_BUTTON_A ){
				FLD_DEMO_ANTEGG_CUT00_ROTA_Y += FX_GET_ROTA_NUM( 1 );
				OS_Printf( "ROTA_Y %d\n", FLD_DEMO_ANTEGG_CUT00_ROTA_Y );
			}else if( sys.cont & PAD_BUTTON_Y ){
				FLD_DEMO_ANTEGG_CUT00_ROTA_Y -= FX_GET_ROTA_NUM( 1 );
				OS_Printf( "ROTA_Y %d\n", FLD_DEMO_ANTEGG_CUT00_ROTA_Y );
			}
			FLD_DEMO_3DObjDrawSetRota( &p_data->draw, FLD_DEMO_ANTEGG_CUT00_ROTA_Y, FLD_3DROTA_WAY_Y );
		}

		if( sys.cont & PAD_BUTTON_L ){
			if( sys.cont & PAD_BUTTON_A ){
				FLD_DEMO_ANTEGG_CUT00_ROTA_Z += FX_GET_ROTA_NUM( 1 );
				OS_Printf( "ROTA_Z %d\n", FLD_DEMO_ANTEGG_CUT00_ROTA_Z );
			}else if( sys.cont & PAD_BUTTON_Y ){

				FLD_DEMO_ANTEGG_CUT00_ROTA_Z -= FX_GET_ROTA_NUM( 1 );
				OS_Printf( "ROTA_Z %d\n", FLD_DEMO_ANTEGG_CUT00_ROTA_Z );
			}
			// �����P�W�O�x��]
			FLD_DEMO_3DObjDrawSetRota( &p_data->draw, FLD_DEMO_ANTEGG_CUT00_ROTA_Z, FLD_3DROTA_WAY_Z );
		}

		if( sys.cont & PAD_BUTTON_START ){
			if( sys.cont & PAD_BUTTON_A ){
				FLD_DEMO_ANTEGG_CUT00_ROTA_X += FX_GET_ROTA_NUM( 1 );
				OS_Printf( "ROTA_X %d\n", FLD_DEMO_ANTEGG_CUT00_ROTA_X );
			}else if( sys.cont & PAD_BUTTON_Y ){

				FLD_DEMO_ANTEGG_CUT00_ROTA_X -= FX_GET_ROTA_NUM( 1 );
				OS_Printf( "ROTA_X %d\n", FLD_DEMO_ANTEGG_CUT00_ROTA_X );
			}
			FLD_DEMO_3DObjDrawSetRota( &p_data->draw, FLD_DEMO_ANTEGG_CUT00_ROTA_X, FLD_3DROTA_WAY_X );
		}
		break;

	case 1:
		FLD_DEMO_3DObjDrawGetMatrix( &p_data->draw, &matrix.x, &matrix.y, &matrix.z );
		if( sys.cont & PAD_BUTTON_R ){
			if( sys.cont & PAD_BUTTON_A ){
				matrix.x += FX32_CONST( 1 );
				FLD_DEMO_ANTEGG_CUT00_OFS_X += FX32_CONST( 1 );
				OS_Printf( "MATRIX_X %d\n", FLD_DEMO_ANTEGG_CUT00_OFS_X );
			}else if( sys.cont & PAD_BUTTON_Y ){

				matrix.x -= FX32_CONST( 1 );
				FLD_DEMO_ANTEGG_CUT00_OFS_X -= FX32_CONST( 1 );
				OS_Printf( "MATRIX_X %d\n", FLD_DEMO_ANTEGG_CUT00_OFS_X );
			}
			FLD_DEMO_3DObjDrawSetMatrix( &p_data->draw, matrix.x, matrix.y, matrix.z );
		}

		if( sys.cont & PAD_BUTTON_L ){
			if( sys.cont & PAD_BUTTON_A ){
				matrix.y += FX32_CONST( 1 );
				FLD_DEMO_ANTEGG_CUT00_OFS_Y += FX32_CONST( 1 );
				OS_Printf( "MATRIX_Y %d\n", FLD_DEMO_ANTEGG_CUT00_OFS_Y );
			}else if( sys.cont & PAD_BUTTON_Y ){

				matrix.y -= FX32_CONST( 1 );
				FLD_DEMO_ANTEGG_CUT00_OFS_Y -= FX32_CONST( 1 );
				OS_Printf( "MATRIX_Y %d\n", FLD_DEMO_ANTEGG_CUT00_OFS_Y );
			}
			FLD_DEMO_3DObjDrawSetMatrix( &p_data->draw, matrix.x, matrix.y, matrix.z );
		}

		if( sys.cont & PAD_BUTTON_START ){
			if( sys.cont & PAD_BUTTON_A ){
				matrix.z += FX32_CONST( 1 );
				FLD_DEMO_ANTEGG_CUT00_OFS_Z += FX32_CONST( 1 );
				OS_Printf( "MATRIX_Z %d\n", FLD_DEMO_ANTEGG_CUT00_OFS_Z );
			}else if( sys.cont & PAD_BUTTON_Y ){

				matrix.z -= FX32_CONST( 1 );
				FLD_DEMO_ANTEGG_CUT00_OFS_Z -= FX32_CONST( 1 );
				OS_Printf( "MATRIX_Z %d\n", FLD_DEMO_ANTEGG_CUT00_OFS_Z );
			}
			FLD_DEMO_3DObjDrawSetMatrix( &p_data->draw, matrix.x, matrix.y, matrix.z );
		}
		break;

	default:
		break;
	}
#endif
}

//----------------------------------------------------------------------------
/**
 *		�y����̗����o���z
 *	@brief	�`�揈��
 *
 *	@param	p_data	���[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void FLD_DEMO_AntEgg_Cut_Draw( FLD_DEMO_ANTEGG* p_data )
{
	FLD_DEMO_AntEgg_Draw( p_data );
}


//----------------------------------------------------------------------------
/**
 *		�y����̗����o���@�J�b�g�O�O�z
 *	@brief	�f���J�n
 *
 *	@param	p_data	���[�N
 *	@param	x	�J�������ړ_���W��
 *	@param	y	�J�������ړ_���W��
 *	@param	z	�J�������ړ_���W��
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void FLD_DEMO_AntEgg_Cut00_Start( FLD_DEMO_ANTEGG* p_data, fx32 x, fx32 y, fx32 z )
{
	FLD_DEMO_AntEgg_Start( p_data,
			x + FLD_DEMO_ANTEGG_CUT00_OFS_X,
			y + FLD_DEMO_ANTEGG_CUT00_OFS_Y,
			z + FLD_DEMO_ANTEGG_CUT00_OFS_Z,
			FLD_DEMO_ANTEGG_CUT00_ROTA_X,
			FLD_DEMO_ANTEGG_CUT00_ROTA_Y,
			FLD_DEMO_ANTEGG_CUT00_ROTA_Z );
}

//----------------------------------------------------------------------------
/**
 *		�y����̗����o���@�J�b�g�O�P�z
 *	@brief	�f���J�n
 *
 *	@param	p_data	���[�N
 *	@param	x	�J�������ړ_���W��
 *	@param	y	�J�������ړ_���W��
 *	@param	z	�J�������ړ_���W��
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void FLD_DEMO_AntEgg_Cut01_Start( FLD_DEMO_ANTEGG* p_data, fx32 x, fx32 y, fx32 z )
{
	FLD_DEMO_AntEgg_Start( p_data,
			x + FLD_DEMO_ANTEGG_CUT01_OFS_X,
			y + FLD_DEMO_ANTEGG_CUT01_OFS_Y,
			z + FLD_DEMO_ANTEGG_CUT01_OFS_Z,
			FLD_DEMO_ANTEGG_CUT01_ROTA_X,
			FLD_DEMO_ANTEGG_CUT01_ROTA_Y,
			FLD_DEMO_ANTEGG_CUT01_ROTA_Z );
}

//----------------------------------------------------------------------------
/**
 *		�y����̗����o���@�J�b�g�O�Q�z
 *	@brief	�f���J�n
 *
 *	@param	p_data	���[�N
 *	@param	x	�J�������ړ_���W��
 *	@param	y	�J�������ړ_���W��
 *	@param	z	�J�������ړ_���W��
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void FLD_DEMO_AntEgg_Cut02_Start( FLD_DEMO_ANTEGG* p_data, fx32 x, fx32 y, fx32 z )
{
	FLD_DEMO_AntEgg_Start( p_data,
			x + FLD_DEMO_ANTEGG_CUT02_OFS_X,
			y + FLD_DEMO_ANTEGG_CUT02_OFS_Y,
			z + FLD_DEMO_ANTEGG_CUT02_OFS_Z,
			FLD_DEMO_ANTEGG_CUT02_ROTA_X,
			FLD_DEMO_ANTEGG_CUT02_ROTA_Y,
			FLD_DEMO_ANTEGG_CUT02_ROTA_Z );
}



//-----------------------------------------------------------------------------
/**
 *
 *		�y����̗��̎��̍������O	�R���e�B�z
 * 
 */
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
/**
 *		�萔��`
 */
//-----------------------------------------------------------------------------

#ifdef FLD_DEMO_ANT_DEBUG
int FLD_DEMO_BLACKRING_ANTEGGCUT00_OBJ_OFS_X =	(0xfffc2000);
int FLD_DEMO_BLACKRING_ANTEGGCUT00_OBJ_OFS_Y =	(0xfffb1000);
int FLD_DEMO_BLACKRING_ANTEGGCUT00_OBJ_OFS_Z =	(0xfff30000);
#else


#endif



// �J�������ړ_����̋���
#if ( PM_VERSION == VERSION_DIAMOND )

#define FLD_DEMO_BLACKRING_ANTEGGCUT00_OBJ_OFS_X	(0x11000)
#define FLD_DEMO_BLACKRING_ANTEGGCUT00_OBJ_OFS_Y	(0xfff91000)
#define FLD_DEMO_BLACKRING_ANTEGGCUT00_OBJ_OFS_Z	(0xfff35000)

#elif( PM_VERSION == VERSION_PEARL )

#define FLD_DEMO_BLACKRING_ANTEGGCUT00_OBJ_OFS_X	(0xfffc2000)
#define FLD_DEMO_BLACKRING_ANTEGGCUT00_OBJ_OFS_Y	(0xfffb1000)
#define FLD_DEMO_BLACKRING_ANTEGGCUT00_OBJ_OFS_Z	(0xfff30000)

#endif

#define FLD_DEMO_BLACKRING_ANTEGGCUT01_OBJ_OFS_X	(0x252000)
#define FLD_DEMO_BLACKRING_ANTEGGCUT01_OBJ_OFS_Y	(0x43000)
#define FLD_DEMO_BLACKRING_ANTEGGCUT01_OBJ_OFS_Z	(0xfffc8000)

#define FLD_DEMO_BLACKRING_ANTEGGCUT02_OBJ_OFS_X	(0xffeb4000)
#define FLD_DEMO_BLACKRING_ANTEGGCUT02_OBJ_OFS_Y	(0xffff3000)
#define FLD_DEMO_BLACKRING_ANTEGGCUT02_OBJ_OFS_Z	(0xffe3c000)



//----------------------------------------------------------------------------
/**
 *		�y����̗��̎��̍������O	�R���e�B�z
 *	@brief	����̗��̎��̍������O
 *
 *	@param	heapID	�q�[�vID
 *
 *	@return	���[�N
 */
//-----------------------------------------------------------------------------
FLD_DEMO_BLACK_RING* FLD_DEMO_BlackRing_AntEggCat_Alloc( u32 heapID )
{
	return FLD_DEMO_BlackRing_Alloc_Core( heapID, NARC_demo_climax_ring_t_nsbmd );
}

//----------------------------------------------------------------------------
/**
 *		�y����̗��̎��̍������O	�R���e�B�z
 *	@brief	���[�N�j��
 *
 *	@param	p_data	���[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void FLD_DEMO_BlackRing_AntEggCat_Free( FLD_DEMO_BLACK_RING* p_data )
{
	FLD_DEMO_BlackRing_Free_Core( p_data );

}

//----------------------------------------------------------------------------
/**
 *		�y����̗��̎��̍������O	�R���e�B�z
 *	@brief	�̪�ă��C��
 *
 *	@param	p_data	���[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void FLD_DEMO_BlackRing_AntEggCat_Main( FLD_DEMO_BLACK_RING* p_data )
{
	FLD_DEMO_BlackRing_Main_Core( p_data );

#ifdef FLD_DEMO_ANT_DEBUG
	if( FLD_DEMO_ANTEGG_DEBUG_SEQ == 2 ){
		if( sys.cont & PAD_BUTTON_R ){
			if( sys.cont & PAD_BUTTON_A ){
				p_data->y += FX32_ONE;
				FLD_DEMO_BLACKRING_ANTEGGCUT00_OBJ_OFS_Y += FX32_ONE;
				OS_Printf( "MAT_Y %x\n", FLD_DEMO_BLACKRING_ANTEGGCUT00_OBJ_OFS_Y );
			}else if( sys.cont & PAD_BUTTON_Y ){
				p_data->y -= FX32_ONE;
				FLD_DEMO_BLACKRING_ANTEGGCUT00_OBJ_OFS_Y -= FX32_ONE;
				OS_Printf( "MAT_Y %x\n", FLD_DEMO_BLACKRING_ANTEGGCUT00_OBJ_OFS_Y );
			}
		}

		if( sys.cont & PAD_BUTTON_L ){
			if( sys.cont & PAD_BUTTON_A ){
				p_data->z += FX32_ONE;
				FLD_DEMO_BLACKRING_ANTEGGCUT00_OBJ_OFS_Z += FX32_ONE;
				OS_Printf( "MAT_Z %x\n", FLD_DEMO_BLACKRING_ANTEGGCUT00_OBJ_OFS_Z );
			}else if( sys.cont & PAD_BUTTON_Y ){

				p_data->z -= FX32_ONE;
				FLD_DEMO_BLACKRING_ANTEGGCUT00_OBJ_OFS_Z -= FX32_ONE;
				OS_Printf( "MAT_Z %x\n", FLD_DEMO_BLACKRING_ANTEGGCUT00_OBJ_OFS_Z );
			}
		}

		if( sys.cont & PAD_BUTTON_START ){
			if( sys.cont & PAD_BUTTON_A ){
				p_data->x += FX32_ONE;
				FLD_DEMO_BLACKRING_ANTEGGCUT00_OBJ_OFS_X += FX32_ONE;
				OS_Printf( "MAT_X %x\n", FLD_DEMO_BLACKRING_ANTEGGCUT00_OBJ_OFS_X );
			}else if( sys.cont & PAD_BUTTON_Y ){

				p_data->x -= FX32_ONE;
				FLD_DEMO_BLACKRING_ANTEGGCUT00_OBJ_OFS_X -= FX32_ONE;
				OS_Printf( "MAT_X %x\n", FLD_DEMO_BLACKRING_ANTEGGCUT00_OBJ_OFS_X );
			}
		}
	}
#endif
}

//----------------------------------------------------------------------------
/**
 *		�y����̗��̎��̍������O	�R���e�B�z
 *	@brief	�̪�ĕ`��
 *
 *	@param	p_data	���[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void FLD_DEMO_BlackRing_AntEggCat_Draw( FLD_DEMO_BLACK_RING* p_data )
{
	FLD_DEMO_BlackRing_Draw_Core( p_data );
}

//----------------------------------------------------------------------------
/**
 *		�y����̗��̎��̍������O	�R���e�B�z
 *	@brief	�̪�ĊJ�n	�J�b�g00
 *
 *	@param	p_data	���[�N
 *	@param	x	�J�������ړ_�@�����W
 *	@param	y	�J�������ړ_�@�����W	
 *	@param	z	�J�������ړ_�@�����W 
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void FLD_DEMO_BlackRing_AntEggCat00_Start( FLD_DEMO_BLACK_RING* p_data, fx32 x, fx32 y, fx32 z )
{
	FLD_DEMO_BlackRing_Start_Core( p_data, 
			x + FLD_DEMO_BLACKRING_ANTEGGCUT00_OBJ_OFS_X,
			y + FLD_DEMO_BLACKRING_ANTEGGCUT00_OBJ_OFS_Y,
			z + FLD_DEMO_BLACKRING_ANTEGGCUT00_OBJ_OFS_Z,
			FLD_DEMO_BLACK_RING_START_TIMING,
			FLD_DEMO_ANTEGG_CUT00_ROTA_X,
			FLD_DEMO_ANTEGG_CUT00_ROTA_Y,
			FLD_DEMO_ANTEGG_CUT00_ROTA_Z
			);
}

//----------------------------------------------------------------------------
/**
 *		�y����̗��̎��̍������O	�R���e�B�z
 *	@brief	�̪�ĊJ�n	�J�b�g01
 *
 *	@param	p_data	���[�N
 *	@param	x	�J�������ړ_�@�����W
 *	@param	y	�J�������ړ_�@�����W	
 *	@param	z	�J�������ړ_�@�����W 
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void FLD_DEMO_BlackRing_AntEggCat01_Start( FLD_DEMO_BLACK_RING* p_data, fx32 x, fx32 y, fx32 z )
{
	FLD_DEMO_BlackRing_Start_Core( p_data, 
			x + FLD_DEMO_BLACKRING_ANTEGGCUT01_OBJ_OFS_X,
			y + FLD_DEMO_BLACKRING_ANTEGGCUT01_OBJ_OFS_Y,
			z + FLD_DEMO_BLACKRING_ANTEGGCUT01_OBJ_OFS_Z,
			FLD_DEMO_BLACK_RING_START_TIMING,
			FLD_DEMO_ANTEGG_CUT01_ROTA_X,
			FLD_DEMO_ANTEGG_CUT01_ROTA_Y,
			FLD_DEMO_ANTEGG_CUT01_ROTA_Z
			);
}

//----------------------------------------------------------------------------
/**
 *		�y����̗��̎��̍������O	�R���e�B�z
 *	@brief	�̪�ĊJ�n	�J�b�g02
 *
 *	@param	p_data	���[�N
 *	@param	x	�J�������ړ_�@�����W
 *	@param	y	�J�������ړ_�@�����W	
 *	@param	z	�J�������ړ_�@�����W 
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void FLD_DEMO_BlackRing_AntEggCat02_Start( FLD_DEMO_BLACK_RING* p_data, fx32 x, fx32 y, fx32 z )
{
	FLD_DEMO_BlackRing_Start_Core( p_data, 
			x + FLD_DEMO_BLACKRING_ANTEGGCUT02_OBJ_OFS_X,
			y + FLD_DEMO_BLACKRING_ANTEGGCUT02_OBJ_OFS_Y,
			z + FLD_DEMO_BLACKRING_ANTEGGCUT02_OBJ_OFS_Z,
			FLD_DEMO_BLACK_RING_START_TIMING,
			FLD_DEMO_ANTEGG_CUT02_ROTA_X,
			FLD_DEMO_ANTEGG_CUT02_ROTA_Y,
			FLD_DEMO_ANTEGG_CUT02_ROTA_Z
			);
}


//-----------------------------------------------------------------------------
/**
 * 
 *		�t�B�[���h�S�̂��Â�����
 * 
 */
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
/**
 *		�萔��`
 */
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/**
 *		�\���̒�`
 */
//-----------------------------------------------------------------------------
//-------------------------------------
//	���x�̒ႢLIGHT���t�B�[���h�S�̂ɂ�����
//=====================================
typedef struct _FLD_DEMO_DARKLIGHT{
	FIELDSYS_WORK* p_fsys;	// �t�B�[���h�V�X�e��
	const LIGHT_CONT_DATA* p_lightdata;		// LIGHT�f�[�^
	u32 light_num;			// LIGHT�f�[�^��
	u32 light_count;		// LIGHT����
	u32 light_set;			// ���ݒ蒆��LIGHT�f�[�^
	u32 status;				// ������
};

//-----------------------------------------------------------------------------
/**
 *		�v���g�^�C�v�錾
 */
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/**
 *		�O���[�o���ϐ�
 */
//-----------------------------------------------------------------------------
#define FLD_DEMO_DARKLIGHT_LIGHTDATANUM	( 3 )
static const LIGHT_CONT_DATA FLD_DEMO_DARKLIGHT_LIGHTDATA[ FLD_DEMO_DARKLIGHT_LIGHTDATANUM ] = {
	{
		8,				// LIGHT�I�������l
		0xD,			// LIGHT���f�t���O
		{				// LIGHT�J���[
			GX_RGB(13, 11, 11),
			GX_RGB(0, 0, 0),
			GX_RGB(10, 3, 0),
			GX_RGB(31, 31, 31),
		},	
		{				// LIGHT�x�N�g��
			{-2022,-3561,93},
			{0,0,4096},	
			{0,0,4096},
			{0,0,4096},
		},
		GX_RGB(13, 13, 14),// �f�B�t���[�Y
		GX_RGB(13, 12, 12),// �A���r�G���g
		GX_RGB(13, 11, 14),// �X�y�L�����[
		GX_RGB(11, 9, 10) // ����
	},
	{
		16,				// LIGHT�I�������l
		0xD,			// LIGHT���f�t���O
		{				// LIGHT�J���[
			GX_RGB(11, 9, 9),
			GX_RGB(0, 0, 0),
			GX_RGB(10, 3, 0),
			GX_RGB(31, 31, 31),
		},	
		{				// LIGHT�x�N�g��
			{-2022,-3561,93},
			{0,0,4096},	
			{0,0,4096},
			{0,0,4096},
		},
		GX_RGB(11, 11, 12),// �f�B�t���[�Y
		GX_RGB(13, 12, 12),// �A���r�G���g
		GX_RGB(13, 11, 14),// �X�y�L�����[
		GX_RGB(11, 9, 10) // ����
	},
	{
		24,				// LIGHT�I�������l
		0xD,			// LIGHT���f�t���O
		{				// LIGHT�J���[
			GX_RGB(9, 8, 8),
			GX_RGB(0, 0, 0),
			GX_RGB(10, 3, 0),
			GX_RGB(31, 31, 31),
		},	
		{				// LIGHT�x�N�g��
			{-2022,-3561,93},
			{0,0,4096},	
			{0,0,4096},
			{0,0,4096},
		},
		GX_RGB(10, 9, 9),// �f�B�t���[�Y
		GX_RGB(11, 10, 10),// �A���r�G���g
		GX_RGB(13, 11, 14),// �X�y�L�����[
		GX_RGB(11, 9, 10) // ����
	},
};

//----------------------------------------------------------------------------
/**
 *		�y�t�B�[���h�S�̂��Â�����z
 *	@brief	���[�N�m��
 *
 *	@param	heapID	�q�[�vID
 *	@param	p_fsys	�t�B�[���h�V�X�e�� 
 *
 *	@return	���[�N
 */
//-----------------------------------------------------------------------------
FLD_DEMO_DARKLIGHT* FLD_DEMO_DarkLight_Alloc( u32 heapID, FIELDSYS_WORK* p_fsys )
{
	FLD_DEMO_DARKLIGHT* p_data;

	p_data = sys_AllocMemory( heapID, sizeof(FLD_DEMO_DARKLIGHT) );
	memset( p_data, 0, sizeof(FLD_DEMO_DARKLIGHT) );
	p_data->p_fsys = p_fsys;
	p_data->status = FLD_DEMO_DARKLIGHT_INIT;
	
	return p_data;
}

//----------------------------------------------------------------------------
/**
 *		�y�t�B�[���h�S�̂��Â�����z
 *	@brief	���[�N�j��
 *
 *	@param	p_data	���[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void FLD_DEMO_DarkLight_Free( FLD_DEMO_DARKLIGHT* p_data )
{
	sys_FreeMemoryEz( p_data );
}

//----------------------------------------------------------------------------
/**
 *		�y�t�B�[���h�S�̂��Â�����z
 *	@brief	�f���J�n
 *
 *	@param	p_data	���[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void FLD_DEMO_DarkLight_Start( FLD_DEMO_DARKLIGHT* p_data )
{
	p_data->p_lightdata = FLD_DEMO_DARKLIGHT_LIGHTDATA;
	p_data->light_num = FLD_DEMO_DARKLIGHT_LIGHTDATANUM;
	p_data->light_count = 0;
	p_data->light_set = 0;
	p_data->status = FLD_DEMO_DARKLIGHT_FADEOUT;

	// LIGHT���f���~
	SetLightContReflect( p_data->p_fsys->light_cont_data, FALSE );
}

//----------------------------------------------------------------------------
/**
 *		�y�t�B�[���h�S�̂��Â�����z
 *	@brief	���C���֐�
 *
 *	@param	p_data ���[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void FLD_DEMO_DarkLight_Main( FLD_DEMO_DARKLIGHT* p_data )
{
	switch( p_data->status ){
	case FLD_DEMO_DARKLIGHT_FADEOUT:	// �Â��Ȃ��Ă��܂��B
		p_data->light_count ++;
		if( p_data->p_lightdata[ p_data->light_set ].lightEnd <= p_data->light_count ){
			if( (p_data->light_set + 1) >= p_data->light_num ){
				p_data->status++;
			}else{
				p_data->light_set ++;
				DataSetLightCont( &p_data->p_lightdata[ p_data->light_set ], p_data->p_fsys->glst_data );
			}
		}
		break;
		
	case FLD_DEMO_DARKLIGHT_ENDWAIT:	// �I�����N�G�X�g�҂��B
		break;
		
	case FLD_DEMO_DARKLIGHT_FADEIN:	// ���邭�Ȃ��Ă��܂��B
		p_data->light_count --;
		
		if( p_data->light_set > 0 ){
			if( p_data->p_lightdata[ p_data->light_set - 1 ].lightEnd > p_data->light_count ){
				p_data->light_set --;
				DataSetLightCont( &p_data->p_lightdata[ p_data->light_set ], p_data->p_fsys->glst_data );
			}
		}else{
			if( 0 >= p_data->light_count ){

				// LIGHT���A
				SetLightContReflect( p_data->p_fsys->light_cont_data, TRUE );
				p_data->status++;
			}
		}
		break;
		
	case FLD_DEMO_DARKLIGHT_END:		// �S�H���I��
		break;
		
	default:
		break;
	}
}

//----------------------------------------------------------------------------
/**
 *		�y�t�B�[���h�S�̂��Â�����z
 *	@brief	���ݏ�Ԏ擾
 *
 *	@param	cp_data	���[�N
 *	
 *	@retval	FLD_DEMO_DARKLIGHT_INIT,	// ������
 *	@retval	FLD_DEMO_DARKLIGHT_FADEOUT,	// �Â��Ȃ��Ă��܂��B
 * 	@retval	FLD_DEMO_DARKLIGHT_ENDWAIT,	// �I�����N�G�X�g�҂��B
 * 	@retval	FLD_DEMO_DARKLIGHT_FADEIN,	// ���邭�Ȃ��Ă��܂��B
 *	@retval	FLD_DEMO_DARKLIGHT_END,		// �S�H���I��
 */
//-----------------------------------------------------------------------------
u32 FLD_DEMO_DarkLight_GetState( const FLD_DEMO_DARKLIGHT* cp_data )
{
	return cp_data->status;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�I�����N�G�X�g
 *
 *	@param	p_data	���[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void FLD_DEMO_DarkLight_EndReq( FLD_DEMO_DARKLIGHT* p_data )
{
	GF_ASSERT_MSG( p_data->status == FLD_DEMO_DARKLIGHT_ENDWAIT, "status %d", p_data->status );
	p_data->status = FLD_DEMO_DARKLIGHT_FADEIN;
}



//-----------------------------------------------------------------------------
/**
 *
 *
 *		�A���̃^�}�S���o�J�n�f��
 *
 */
//-----------------------------------------------------------------------------
enum{
	FLD_DEMO_ARITAMA_ANM_CA,
	FLD_DEMO_ARITAMA_ANM_MA,
	FLD_DEMO_ARITAMA_ANM_TA,
	FLD_DEMO_ARITAMA_ANM_VA,
	FLD_DEMO_ARITAMA_ANM_NUM
};
//-------------------------------------
//	�A���̗����o�J�n�f��
//=====================================
typedef struct _FLD_DEMO_ARITAMA_START{
	FLD_3DOBJ draw;		// �`�惏�[�N
	FLD_3DOBJ_MDL mdl;		// ���f��
	FLD_3DOBJ_ANM anm[FLD_DEMO_ARITAMA_ANM_NUM];	// �A�j��
	FIELDSYS_WORK* p_fsys;	// �t�B�[���h�V�X�e��
	NNSFndAllocator allocator;	// �A���P�[�^
};



//----------------------------------------------------------------------------
/**
 *	@brief	�A���̗��J�n�@�������m��
 *
 *	@param	heapID		�q�[�vID
 *	@param	p_fsys		�t�B�[���h�V�X�e��
 *
 *	@return	���[�N
 */
//-----------------------------------------------------------------------------
FLD_DEMO_ARITAMA_START* FLD_DEMO_AriTamaStart_Alloc( u32 heapID, FIELDSYS_WORK* p_fsys )
{
	FLD_DEMO_ARITAMA_START * p_work;
	int i;
	p_work = sys_AllocMemory( heapID, sizeof(FLD_DEMO_ARITAMA_START) );
	memset( p_work, 0, sizeof(FLD_DEMO_ARITAMA_START) );

	// fieldsys
	p_work->p_fsys = p_fsys;

	// �A���P�[�^�쐬
	sys_InitAllocator( &p_work->allocator, heapID, 32 );	

	// ���f���ǂݍ���
	FLD_DEMO_3DObjMdlLoad( &p_work->mdl, ARC_FIELD_DEMO_CLI_GRA, NARC_demo_climax_ari_start_nsbmd, heapID );
	for( i=0; i<FLD_DEMO_ARITAMA_ANM_NUM; i++ ){
		FLD_DEMO_3DObjAnmLoad( &p_work->anm[i], &p_work->mdl, ARC_FIELD_DEMO_CLI_GRA, NARC_demo_climax_ari_start_nsbca + i, heapID, &p_work->allocator );
	}
	FLD_DEMO_3DObjDrawInit( &p_work->draw, &p_work->mdl );
	for( i=0; i<FLD_DEMO_ARITAMA_ANM_NUM; i++ ){
		FLD_DEMO_3DObjDrawAddAnm( &p_work->draw, &p_work->anm[i] );
	}
	FLD_DEMO_3DObjDrawSetDraw( &p_work->draw, FALSE );

	return p_work;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�A���̗��J�n�@���[�N�j��
 *
 *	@param	p_data	���[�N
 */
//-----------------------------------------------------------------------------
void FLD_DEMO_AriTamaStart_Free( FLD_DEMO_ARITAMA_START* p_data )
{
	int i;

	FLD_DEMO_3DObjMdlDelete( &p_data->mdl );
	for( i=0; i<FLD_DEMO_ARITAMA_ANM_NUM; i++ ){
		FLD_DEMO_3DObjAnmDelete( &p_data->anm[i], &p_data->allocator );
	}
	sys_FreeMemoryEz( p_data );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�A���̗����o	�J�n
 *
 *	@param	p_data			���[�N
 *	@param	legendpoke_id	�`���|�P����OBJID
 */
//-----------------------------------------------------------------------------
void FLD_DEMO_AriTamaStart_Start( FLD_DEMO_ARITAMA_START* p_data, u32 legendpoke_id )
{
	VecFx32 mat;
	FIELD_OBJ_PTR fldobj;
	fldobj = FieldOBJSys_OBJIDSearch( p_data->p_fsys->fldobjsys, legendpoke_id );
	

	// �|�P�����̍��W�擾
	FieldOBJ_VecPosGet( fldobj, &mat );
	
	FLD_DEMO_3DObjDrawSetMatrix( &p_data->draw, 
			mat.x,
			mat.y,
			mat.z );

	FLD_DEMO_3DObjDrawSetDraw( &p_data->draw, TRUE );
	// �v�V���[
	Snd_SePlay( FLD_DEMO_LEGENDEFF_SND_06 );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�A���̗����o�A�j���@���C��
 *
 *	@param	p_data	���[�N
 *
 *	@retval	TRUE	�I��
 *	@retval	FALSE	�r��
 */
//-----------------------------------------------------------------------------
BOOL FLD_DEMO_AriTamaStart_Main( FLD_DEMO_ARITAMA_START* p_data )
{
	int i;
	BOOL retval;
	
	// �A�j���������ǉ������\��
	for( i=0; i<FLD_DEMO_ARITAMA_ANM_NUM; i++ ){
		retval = FLD_DEMO_3DObjAnmNoLoop( &p_data->anm[i] );
	}
	return retval;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�`�揈��
 *
 *	@param	p_data	���[�N
 */
//-----------------------------------------------------------------------------
void FLD_DEMO_AriTamaStart_Draw( FLD_DEMO_ARITAMA_START* p_data )
{
	FLD_DEMO_3DObjDrawDraw( &p_data->draw );
}



#ifdef FIELD_DEMO_DEBUG
static void FieldDemoDebugStart( void )
{
	pFieldDemoDebugTcb = TCB_Add( FieldDemoDebugTcb, NULL, 0 );
}

static void FieldDemoDebugEnd( void )
{
	TCB_Delete( pFieldDemoDebugTcb );
}

static void FieldDemoDebugTcb( TCB_PTR tcb, void* p_work )
{
	// ������~
	if( sys.tp_trg ){
		FIELD_DEMO_DEBUG_STOP ^= 1;

		OS_Printf( "��~:1 �Đ�:0 %d\n", FIELD_DEMO_DEBUG_STOP );
	}

	// �l�ύX
	if( sys.cont & PAD_BUTTON_L ){
		if( sys.repeat & PAD_BUTTON_A ){
//			OS_Printf( "%d\n", );
		}
		if( sys.repeat & PAD_BUTTON_Y ){
//			OS_Printf( "%d\n", );
		}
	}
	if( sys.cont & PAD_BUTTON_R ){
		if( sys.repeat & PAD_BUTTON_A ){
//			OS_Printf( "%d\n", );
		}
		if( sys.repeat & PAD_BUTTON_Y ){
//			OS_Printf( "%d\n", );
		}
	}
	if( sys.cont & PAD_BUTTON_START ){
		if( sys.repeat & PAD_BUTTON_A ){
//			OS_Printf( "%d\n", );
		}
		if( sys.repeat & PAD_BUTTON_Y ){
//			OS_Printf( "%d\n", );
		}
	}
}
#endif // FIELD_DEMO_DEBUG
