//==============================================================================
/**
 * @file	clact_tool.h
 * @brief	clact��ʊ֐��S
 * @author	goto
 * @date	2005.09.12(��)
 *
 * �����ɐF�X�ȉ�����������Ă��悢
 *
 */
//==============================================================================

#ifndef	_CLACT_TOOL_H_
#define _CLACT_TOOL_H_

#include "gflib/clact.h"

#include "system/clact_util.h"
#include "system/render_oam.h"
#include "system/palanm.h"


// -----------------------------------------------------------------------------
//
//
//	���L���E�����t���O����n��`
//
//
// -----------------------------------------------------------------------------
// -----------------------------------------
//
//	���ψ������\�[�X���[�h�𗘗p����
//
//		�L�� = ���p����
//
// -----------------------------------------
#define CATS_CBP_RES_LOAD


// -----------------------------------------
//
//	��RENDER �𗘗p����
//
//		�L�� = ���p����
//
// -----------------------------------------
#define CATS_RENDER_USE


// -----------------------------------------------------------------------------
//
//
//	��������
//
//
// -----------------------------------------------------------------------------
// -----------------------------------------
//
//	���V�X�e���Ǘ��\����
//
//		�e�A�v���łP�����p�ӂ���
//		clact_tool���ł�[ csp ]�ŕ\������Ă���
//
// -----------------------------------------
typedef struct _TCATS_SYSTEM   * CATS_SYS_PTR;


// -----------------------------------------
//
//	�����\�[�X�Ǘ��\����
//
//		�P�ʂ��Ƃɗp�ӂ���(�G�t�F�N�g�P�Ȃ�)
//		clact_tool���ł�[ crp ]�ŕ\������Ă���
//
// -----------------------------------------
typedef struct _TCATS_RESOURCE * CATS_RES_PTR;


// -----------------------------------------
//
//	��CATS ���g�����̐�p�A�N�^�[�\����
//
// -----------------------------------------
typedef struct _TCATS_ACT {
	
	CLACT_WORK_PTR			act;		///< �A�N�^�[�̃|�C���^
	CLACT_HEADER_PTR		act_hd;		///< �A�N�^�[�w�b�_�[�̃|�C���^
	CLACT_HEADER_TBL_PTR	act_htp;	///< �A�N�^�[�w�b�_�[�e�[�u���̃|�C���^
	
	int vram_trans;
	
} TCATS_ACT;

typedef struct _TCATS_ACT * CATS_ACT_PTR;


// -----------------------------------------
//
//	��OAM�������p�\����
//
// -----------------------------------------
typedef struct {
	
	int mos;		///< ���C��	OAM�Ǘ��̈�E�J�n
	int moe;		///< ���C��	OAM�Ǘ��̈�E�I��
	int mas;		///< ���C��	�A�t�B���Ǘ��̈�E�J�n
	int mae;		///< ���C��	�A�t�B���Ǘ��̈�E�I��
	int sos;		///< �T�u	OAM�Ǘ��̈�E�J�n
	int soe;		///< �T�u	OAM�Ǘ��̈�E�J�n
	int sas;		///< �T�u	�A�t�B���Ǘ��̈�E�J�n
	int sae;		///< �T�u	�A�t�B���Ǘ��̈�E�I��
	
} TCATS_OAM_INIT;


// -----------------------------------------
//
//	���L�����}�l�[�W���������p�\����
//
// -----------------------------------------
typedef struct {
	
	int num;						///< �L�����N�^ID�Ǘ���
	int m_size;						///< ���C����ʃT�C�Y(byte�P��)
	int s_size;						///< �T�u��ʃT�C�Y(byte�P��)

	GXOBJVRamModeChar	main_mode;	///< �L�����N�^�}�b�s���O���[�h ���C�����
	GXOBJVRamModeChar	sub_mode;	///< �L�����N�^�}�b�s���O���[�h �T�u���
	
} TCATS_CHAR_MANAGER_MAKE;


// -----------------------------------------
//
//	�����\�[�X�ƃw�b�_�[���܂Ƃ߂����p��
//
// -----------------------------------------
typedef union {

	const char* res_file[ CLACT_U_RES_MAX + 1];	///< ���\�[�X�z�� + �w�b�_�[
	
	struct {
	
		const char* char_path;					///< �L����
		const char* pltt_path;					///< �p���b�g
		const char* cell_path;					///< �Z��
		const char* cell_anm_path;				///< �Z���A�j��
		const char* mcell_path;					///< �}���`�Z��
		const char* mcell_anm_path;				///< �}���`�Z���A�j��
		
		const char* clact_header_path;			///< �Z���A�N�^�[�w�b�_�[

	} resource;
	
} TCATS_RESOURCE_FILE_LIST;

// -----------------------------------------
//
//	�����\�[�X�݂̂܂Ƃ߂�����
//
// -----------------------------------------
typedef union {
	
	const char* res_file[ CLACT_U_RES_MAX ];
	
	struct {
		
		const char* char_path;					///< �L����
		const char* pltt_path;					///< �p���b�g
		const char* cell_path;					///< �Z��
		const char* cell_anm_path;				///< �Z���A�j��
		const char* mcell_path;					///< �}���`�Z��
		const char* mcell_anm_path;				///< �}���`�Z���A�j��
		
	} resource;
	
} TCATS_ADD_FILE_LIST;


// -----------------------------------------
//
//	��OBJ�o�^�p�\����
//
// -----------------------------------------
typedef struct {
	
	int no;				///< ���\�[�X���f�[�^�̓o�^�ԍ�
	
	s16 x;				///< [ X ] ���W
	s16 y;				///< [ Y ] ���W
	s16 z;				///< [ Z ] ���W
	
	u16	anm;			///< �A�j���ԍ�
	int pri;			///< �D�揇��
	int	pal;			///< �p���b�g�ԍ�
	int d_area;			///< �`��G���A
	
	int param1;			///< �]���p�t���O
	int param2;
	int param3;
	int param4;
	
} TCATS_OBJECT_ADD_PARAM;

// -----------------------------------------
//
//	�����\�[�X�o�^�ő吔��`�\����
//
// -----------------------------------------
typedef union {
	
	int res_num[ CLACT_U_RES_MAX ];
	
	struct {
		
		int char_num;				///< �L�����̐�
		int pltt_num;				///< �p���b�g�̐�
		int cell_num;				///< �Z���̐�
		int cell_anm_num;			///< �Z���A�j���̐�
		int mcell_num;				///< �}���`�Z���̐�
		int mcell_anm_num;			///< �}���`�Z���A�j���̐�
		
	} resource_num;	
	
} TCATS_RESOURCE_NUM_LIST;

// -----------------------------------------
//
//	���o�^�p�\���� �P�̓o�^�p
//
// -----------------------------------------
typedef struct {
	
	s16 x;							///< [ X ] ���W
	s16 y;							///< [ Y ] ���W
	s16 z;							///< [ Z ] ���W
	
	u16	anm;						///< �A�j���ԍ�
	int pri;						///< �D�揇��
	int	pal;						///< �p���b�g�ԍ�
	int d_area;						///< �`��G���A
	
	int id[ CLACT_U_RES_MAX ];		///< �g�p���\�[�XID�e�[�u��
		
	int bg_pri;						///< BG�ʂւ̗D��x
	int vram_trans;					///< Vram�]���t���O
	
} TCATS_OBJECT_ADD_PARAM_S;


// -----------------------------------------
//
//	��CATS ��p�̒�`�Q
//
// -----------------------------------------
enum ECATS {
	
	CATS_ENABLE_TRUE	= 1,
	CATS_ENABLE_FALSE	= 0,
	
	CATS_D_AREA_MAIN	= NNS_G2D_VRAM_TYPE_2DMAIN,
	CATS_D_AREA_SUB		= NNS_G2D_VRAM_TYPE_2DSUB,
	
	CATS_ANM_AUTO_ON	= 1,
	CATS_ANM_AUTO_OFF	= 0,
	
	CATS_RENDER_USE_ON	= 1,
	CATS_RENDER_USE_OFF = 0,
		
};


// =============================================================================
//
//
//	�����ʑ���֐� �| �P�̓o�^�A�w�b�_�[�o�^���p
//
//
// =============================================================================
// -----------------------------------------
//
//	��CATS_SYSTEM �̃������m��
//
// -----------------------------------------
extern CATS_SYS_PTR CATS_AllocMemory(int heap_area);


// -----------------------------------------
//
//	��CATS_RESOURCE �̃������m��
//
// -----------------------------------------
extern CATS_RES_PTR CATS_ResourceCreate(CATS_SYS_PTR csp);


// -----------------------------------------
//
//	��CATS ���\�[�X�̐����擾
//
// -----------------------------------------
extern int CATS_ResourceNumGet(CATS_SYS_PTR csp);


//------------------------------------------
//
//	��CATS �����_���[�f�[�^���擾
//
//------------------------------------------
extern CLACT_U_EASYRENDER_DATA * CATS_EasyRenderGet(CATS_SYS_PTR csp);


// -----------------------------------------
//
//	��CATS �V�X�e���̏�����
//
// -----------------------------------------
extern BOOL CATS_SystemInit(CATS_SYS_PTR csp, const TCATS_OAM_INIT* coi, const TCATS_CHAR_MANAGER_MAKE* ccmm, int pal_num);


// -----------------------------------------
//
//	��CATS RENDER�̗��p�t���O�ݒ�
//
// -----------------------------------------
extern void CATS_RenderUseSet(CATS_SYS_PTR csp, int flag);

// -----------------------------------------
//
//	��CATS �Z���A�N�^�[�Z�b�g�̍쐬
//
// -----------------------------------------
extern BOOL CATS_ClactSetInit(CATS_SYS_PTR csp, CATS_RES_PTR crp, int num);


// -----------------------------------------
//
//	��CATS OBJ�j��
//
// -----------------------------------------
extern void CATS_ObjectDel(CLACT_WORK_PTR act);


// -----------------------------------------
//
//	��CATS �`��
//
// -----------------------------------------
extern void CATS_Draw(CATS_RES_PTR crp);


// -----------------------------------------
//
//	��CATS Vram�]���ݒ�
//
// -----------------------------------------
extern void CATS_UpdateTransfer(void);


// -----------------------------------------
//
//	��CATS OAM�]��
//
// -----------------------------------------
extern void CATS_RenderOamTrans(void);
extern void CATS_RenderOamTransEx(CATS_SYS_PTR csp);


// -----------------------------------------
//
//	��CATS �Z���A�N�^�[�Z�b�g�j��	��
//
// -----------------------------------------
extern void CATS_ClactSetDelete(CATS_RES_PTR crp);


// -----------------------------------------
//
//	��CATS �w�b�_�[�e�[�u���j��		��
//
// -----------------------------------------
extern void CATS_HeaderTblDelete(CATS_RES_PTR crp);


// -----------------------------------------
//
//	��CATS ���\�[�X�f�[�^�j��		��
//
// -----------------------------------------
extern void CATS_ResourceDelete(CATS_RES_PTR crp);


// -----------------------------------------
//
//	��CATS �}�l�[�W���[�j��			��
//
// -----------------------------------------
extern void CATS_ManagerDelete(CATS_SYS_PTR csp);


// -----------------------------------------
//
//	��CATS ���\�[�X�p�̃������j��	��
//
// -----------------------------------------
extern void CATS_ResourceFree(CATS_SYS_PTR csp, CATS_RES_PTR crp);


// -----------------------------------------
//
//	��CATS ���\�[�X�֘A�̔j�� [ ���� ]
//
//	 ���̕t���Ă��铮������ׂčs�Ȃ��̂Ő���
//
// -----------------------------------------
extern void CATS_ResourceDestructor(CATS_SYS_PTR csp, CATS_RES_PTR crp);


// -----------------------------------------
//
//	��CATS System�{�̂̃������j��
//
// -----------------------------------------
extern void CATS_FreeMemory(CATS_SYS_PTR csp);


// =============================================================================
//
//
//	���w�b�_�[�ǂݍ��݊֐�
//
//
// =============================================================================
// -----------------------------------------
//
//	��CATS ���\�[�X���[�h
//
// -----------------------------------------
extern BOOL CATS_ResourceLoad(CATS_SYS_PTR csp, CATS_RES_PTR crp, const TCATS_RESOURCE_FILE_LIST* res_list);
extern BOOL CATS_ResourceLoadBinary(
			CATS_SYS_PTR csp, CATS_RES_PTR crp, const TCATS_RESOURCE_FILE_LIST* res_list );

#ifdef CATS_CBP_RES_LOAD	///< �ψ���

extern BOOL CATS_ResourceLoad_FileName(CATS_SYS_PTR csp, CATS_RES_PTR crp, ...);

#endif


// -----------------------------------------
//
//	��CATS OBJ�o�^
//
// -----------------------------------------
extern CLACT_WORK_PTR CATS_ObjectAdd(CATS_SYS_PTR csp, CATS_RES_PTR crp, const TCATS_OBJECT_ADD_PARAM* coap);
extern CLACT_WORK_PTR CATS_ObjectAdd_EX(CATS_SYS_PTR csp, CATS_RES_PTR crp, int no,
							 				s16 x, s16 y, s16 z, u16 anm, int pri, int pal, int d_area,
							 				int param1, int param2, int param3, int param4); 




// =============================================================================
//
//
//	���P�̓o�^�p
//
//
// =============================================================================
// -----------------------------------------
//
//	��CATS ���\�[�X�Ǘ����̐ݒ�
//
// -----------------------------------------
extern BOOL CATS_ResourceManagerInit(CATS_SYS_PTR csp, CATS_RES_PTR crp, const TCATS_RESOURCE_NUM_LIST* crnl);


// -----------------------------------------
//
//	��CATS ���\�[�X�o�^
//
// -----------------------------------------
extern BOOL CATS_LoadResourceChar(CATS_SYS_PTR csp, CATS_RES_PTR crp, const char* path, int trans_mode, int id);
extern BOOL CATS_LoadResourceCharArc(CATS_SYS_PTR csp, CATS_RES_PTR crp, int arc_id, int data_id, int comp, int trans_mode, int id);
extern u8 CATS_LoadResourcePltt(CATS_SYS_PTR csp, CATS_RES_PTR crp, const char* path, 
	int num, int trans_mode, int id);
extern s8 CATS_LoadResourcePlttArc(CATS_SYS_PTR csp, CATS_RES_PTR crp, 
	int arc_id, int data_id, int comp, int num, int trans_mode, int id);
extern BOOL CATS_LoadResourceCell(CATS_SYS_PTR csp, CATS_RES_PTR crp, const char* path, int id);
extern BOOL CATS_LoadResourceCellArc(CATS_SYS_PTR csp, CATS_RES_PTR crp, int arc_id, int data_id, int comp, int id);
extern BOOL CATS_LoadResourceCellAnm(CATS_SYS_PTR csp, CATS_RES_PTR crp, const char* path, int id);
extern BOOL CATS_LoadResourceCellAnmArc(CATS_SYS_PTR csp, CATS_RES_PTR crp, int arc_id, int data_id, int comp, int id);
extern BOOL CATS_LoadResourceMCell(CATS_SYS_PTR csp, CATS_RES_PTR crp, const char* path, int id);
extern BOOL CATS_LoadResourceMCellArc(CATS_SYS_PTR csp, CATS_RES_PTR crp, int arc_id, int data_id, int comp, int id);
extern BOOL CATS_LoadResourceMCellAnm(CATS_SYS_PTR csp, CATS_RES_PTR crp, const char* path, int id);
extern BOOL CATS_LoadResourceMCellAnmArc(CATS_SYS_PTR csp, CATS_RES_PTR crp, int arc_id, int data_id, int comp, int id);
extern u8 CATS_LoadResourcePlttWork(PALETTE_FADE_PTR pfd, FADEREQ req, CATS_SYS_PTR csp, 
	CATS_RES_PTR crp, const char* path, int num, int trans_mode, int id);
extern u8 CATS_LoadResourcePlttWorkArc(PALETTE_FADE_PTR pfd, FADEREQ req, CATS_SYS_PTR csp, 
	CATS_RES_PTR crp, int arc_id, int data_id, int comp, int num, int trans_mode, int id);


// -----------------------------------------
//
//	��CATS ���\�[�X�폜
//
// -----------------------------------------
extern BOOL CATS_FreeResourceChar(CATS_RES_PTR crp, int id);
extern BOOL CATS_FreeResourcePltt(CATS_RES_PTR crp, int id);
extern BOOL CATS_FreeResourceCell(CATS_RES_PTR crp, int id);
extern BOOL CATS_FreeResourceCellAnm(CATS_RES_PTR crp, int id);
extern BOOL CATS_FreeResourceMCell(CATS_RES_PTR crp, int id);
extern BOOL CATS_FreeResourceMCellAnm(CATS_RES_PTR crp, int id);


// -----------------------------------------
//
//	��CATS OBJ�o�^
//
// -----------------------------------------
extern CATS_ACT_PTR CATS_ObjectAdd_S(CATS_SYS_PTR csp, CATS_RES_PTR crp, const TCATS_OBJECT_ADD_PARAM_S* coap_s);


// -----------------------------------------
//
//	��CATS ���\�[�X�֘A�̔j��
//
// -----------------------------------------
extern void CATS_ResourceDestructor_S(CATS_SYS_PTR csp, CATS_RES_PTR crp);
extern void CATS_ActorPointerDelete_S(CATS_ACT_PTR cap);








// =============================================================================
//
//
//	��OBJ����֘A�܂Ƃ�
//
//
// =============================================================================
// =============================================================================
//
//	���\������
//
// =============================================================================
// -----------------------------------------
//
//	��CATS OBJ�̃A�j���X�V
//
// -----------------------------------------
extern void CATS_ObjectUpdate(CLACT_WORK_PTR act);
extern void CATS_ObjectUpdateCap(CATS_ACT_PTR cap);
extern void CATS_ObjectUpdateNumCap(CATS_ACT_PTR cap, fx32 frame);


// -----------------------------------------
//
//	��CATS OBJ�̃A�j���V�[�P���X�ݒ聕�擾
//
// -----------------------------------------
extern void CATS_ObjectAnimeSeqSetCap( CATS_ACT_PTR cap, u32 seq );
extern u32 CATS_ObjectAnimeSeqGetCap( CATS_ACT_PTR cap );


// -----------------------------------------
//
//	��CATS OBJ�̃I�[�g�A�j���ݒ�
//
// -----------------------------------------
extern void CATS_ObjectAutoAnimeSet(CLACT_WORK_PTR act, int flag);
extern void CATS_ObjectAutoAnimeSetCap(CATS_ACT_PTR cap, int flag);


// -----------------------------------------
//
//	��CATS OBJ�̃I�[�g�A�j���擾
//
// -----------------------------------------
extern int CATS_ObjectAutoAnimeGet(CLACT_WORK_PTR act);
extern int CATS_ObjectAutoAnimeGetCap(CATS_ACT_PTR cap);


// -----------------------------------------
//
//	��CATS OBJ�̃I�[�g�A�j���X�s�[�h�ݒ聕�擾
//
// -----------------------------------------
extern void CATS_ObjectAutoAnimeSpeedSet(CLACT_WORK_PTR act, fx32 frame);
extern void CATS_ObjectAutoAnimeSpeedSetCap(CATS_ACT_PTR cap, fx32 frame);
extern fx32 CATS_ObjectAutoAnimeSpeedGet(CLACT_WORK_PTR act);
extern fx32 CATS_ObjectAutoAnimeSpeedGetCap(CATS_ACT_PTR cap);


// -----------------------------------------
//
//	��CATS OBJ�̃A�j���t���[���ݒ聕�擾
//
// -----------------------------------------
extern void CATS_ObjectAnimeFrameSet(CLACT_WORK_PTR act, u16 frame);
extern void CATS_ObjectAnimeFrameSetCap(CATS_ACT_PTR cap, u16 frame);
extern u16 CATS_ObjectAnimeFrameGet(CLACT_WORK_PTR act);
extern u16 CATS_ObjectAnimeFrameGetCap(CATS_ACT_PTR cap);


// -----------------------------------------
//
//	��CATS OBJ�̃A�j������`�F�b�N
//
// -----------------------------------------
extern BOOL CATS_ObjectAnimeActiveCheck(CLACT_WORK_PTR act);
extern BOOL CATS_ObjectAnimeActiveCheckCap(CATS_ACT_PTR cap);


// -----------------------------------------
//
//	��CATS OBJ�̕\����\��
//
// -----------------------------------------
extern void CATS_ObjectEnable(CLACT_WORK_PTR act, int enable);
extern void CATS_ObjectEnableCap(CATS_ACT_PTR cap, int enable);
extern int	CATS_ObjectEnableGet(CLACT_WORK_PTR act);
extern int	CATS_ObjectEnableGetCap(CATS_ACT_PTR cap);


// -----------------------------------------
//
//	��CATS �p���b�g�ύX
//
// -----------------------------------------
extern void CATS_ObjectPaletteSet(CLACT_WORK_PTR act, int pal);
extern void CATS_ObjectPaletteSetCap(CATS_ACT_PTR cap, int pal);
extern void CATS_ObjectPaletteOffsetSet(CLACT_WORK_PTR act, int pal_ofs);
extern void CATS_ObjectPaletteOffsetSetCap(CATS_ACT_PTR cap, int pal_ofs);
extern int CATS_ObjectPaletteOffsetGetCap(CATS_ACT_PTR cap);


// -----------------------------------------
//
//	��CATS BG�Ƃ̗D��x�ύX
//
// -----------------------------------------
extern void CATS_ObjectBGPriSet(CLACT_WORK_PTR act, int pri);
extern void CATS_ObjectBGPriSetCap(CATS_ACT_PTR cap, int pri);
extern int	CATS_ObjectBGPriGetCap(CATS_ACT_PTR cap);


// -----------------------------------------
//
//	��CATS OBJ�Ƃ̗D��x�ύX
//
// -----------------------------------------
extern void CATS_ObjectPriSet(CLACT_WORK_PTR act, int pri);
extern void CATS_ObjectPriSetCap(CATS_ACT_PTR cap, int pri);
extern u32	CATS_ObjectPriGet(CLACT_WORK_PTR act);
extern u32	CATS_ObjectPriGetCap(CATS_ACT_PTR cap);



// =============================================================================
//
//	�����W����
//
// =============================================================================
// -----------------------------------------
//
//	��CATS OBJ�̍��W�ύX
//
// -----------------------------------------
extern void CATS_ObjectPosSet(CLACT_WORK_PTR act, s16 x, s16 y);
extern void CATS_ObjectPosSetCap(CATS_ACT_PTR cap, s16 x, s16 y);
extern void CATS_ObjectPosSet_SubSurface(CLACT_WORK_PTR act, s16 x, s16 y, fx32 sub_surface_y);
extern void CATS_ObjectPosSetCap_SubSurface(CATS_ACT_PTR cap, s16 x, s16 y, fx32 sub_surface_y);


// -----------------------------------------
//
//	��CATS OBJ�̍��W�擾
//
// -----------------------------------------
extern void CATS_ObjectPosGet(CLACT_WORK_PTR act, s16 *x, s16 *y);
extern void CATS_ObjectPosGetCap(CATS_ACT_PTR cap, s16 *x, s16 *y);
extern void CATS_ObjectPosGet_SubSurface(CLACT_WORK_PTR act, s16 *x, s16 *y, fx32 sub_surface_y);
extern void CATS_ObjectPosGetCap_SubSurface(CATS_ACT_PTR cap, s16 *x, s16 *y, fx32 sub_surface_y);


// -----------------------------------------
//
//	��CATS OBJ�̈ړ�
//
// -----------------------------------------
extern void CATS_ObjectPosMove(CLACT_WORK_PTR act, s16 x, s16 y);
extern void CATS_ObjectPosMoveCap(CATS_ACT_PTR cap, s16 x, s16 y);



// =============================================================================
//
//	���A�t�B������ �t���b�v����
//
// =============================================================================
// -----------------------------------------
//
//	��CATS OBJ�̃A�t�B���p�����[�^���Z�b�g
//
// -----------------------------------------
extern void CATS_ObjectAffineSet(CLACT_WORK_PTR act, int affine);
extern void CATS_ObjectAffineSetCap(CATS_ACT_PTR cap, int affine);


// -----------------------------------------
//
//	��CATS OBJ�̃A�t�B���p�����[�^�擾
//
// -----------------------------------------
extern int CATS_ObjectAffineGet(CLACT_WORK_PTR act);
extern int CATS_ObjectAffineGetCap(CATS_ACT_PTR cap);


// -----------------------------------------
//
//	��CATS OBJ�̊g�k���̕ύX
//
// -----------------------------------------
extern void CATS_ObjectScaleSet(CLACT_WORK_PTR act, f32 sx, f32 sy);
extern void CATS_ObjectScaleSetCap(CATS_ACT_PTR cap, f32 sx, f32 sy);


// -----------------------------------------
//
//	��CATS OBJ�̊g�k���̉����Z
//
// -----------------------------------------
extern void CATS_ObjectScaleAdd(CLACT_WORK_PTR act, f32 sx, f32 sy);
extern void CATS_ObjectScaleAddCap(CATS_ACT_PTR cap, f32 sx, f32 sy);


// -----------------------------------------
//
//	��CATS OBJ�̊g�k���̎擾
//
// -----------------------------------------
extern void CATS_ObjectScaleGet(CLACT_WORK_PTR act, f32* sx, f32* sy);
extern void CATS_ObjectScaleGetCap(CATS_ACT_PTR cap, f32* sx, f32* sy);


// -----------------------------------------
//
//	��CATS OBJ�̉�]���̕ύX
//
// -----------------------------------------
extern void CATS_ObjectRotationSet(CLACT_WORK_PTR act, u16 rot);
extern void CATS_ObjectRotationSetCap(CATS_ACT_PTR cap, u16 rot);


// -----------------------------------------
//
//	��CATS OBJ�̉�]���̉����Z
//
// -----------------------------------------
extern void CATS_ObjectRotationAdd(CLACT_WORK_PTR act, s32 rot);
extern void CATS_ObjectRotationAddCap(CATS_ACT_PTR cap, s32 rot);


// -----------------------------------------
//
//	��CATS OBJ�̉�]���擾
//
// -----------------------------------------
extern u16	CATS_ObjectRotationGet(CLACT_WORK_PTR act);
extern u16	CATS_ObjectRotationGetCap(CATS_ACT_PTR cap);


// -----------------------------------------
//
//	���t���b�v����
//
// -----------------------------------------
extern void CATS_ObjectFlipSet(CLACT_WORK_PTR act, int flip);
extern void CATS_ObjectFlipSetCap(CATS_ACT_PTR cap, int flip);


// -----------------------------------------
//
//	���t���b�v�擾
//
// -----------------------------------------
extern int CATS_ObjectFlipGet(CLACT_WORK_PTR act);
extern int CATS_ObjectFlipGetCap(CATS_ACT_PTR cap);

// -----------------------------------------
//
//	��CATS �A�t�B���ϊ����W�̐ݒ�
//		cap���W + �A�t�B�����W�@�ʒu�ŉ�]�g�傳��܂�
//
// -----------------------------------------
extern void CATS_ObjectAffinePosSetCap(CATS_ACT_PTR cap, s16 x, s16 y);


// -----------------------------------------
//
//	��CATS �A�t�B���ϊ����W�̎擾
//		cap���W + �A�t�B�����W�@�ʒu�ŉ�]�g�傳��܂�
//
// -----------------------------------------
extern void CATS_ObjectAffinePosGetCap(CATS_ACT_PTR cap, s16 *x, s16 *y);


// -----------------------------------------
//
//	��CATS �A�t�B���ϊ����W�̈ړ�
//		cap���W + �A�t�B�����W�@�ʒu�ŉ�]�g�傳��܂�
//
// -----------------------------------------
extern void CATS_ObjectAffinePosMoveCap(CATS_ACT_PTR cap, s16 x, s16 y);

// -----------------------------------------
//
//	��CATS ���U�C�N
//
// -----------------------------------------
extern void CATS_ObjectMosaicSet(CATS_ACT_PTR cap, BOOL flag);


// =============================================================================
//
//	��OBJ���[�h����
//
// =============================================================================
// -----------------------------------------
//
//	��OBJ���[�h����
//
// -----------------------------------------
extern void CATS_ObjectObjModeSet(CLACT_WORK_PTR act, GXOamMode objmode);
extern void CATS_ObjectObjModeSetCap(CATS_ACT_PTR cap, GXOamMode objmode);


// -----------------------------------------
//
//	��OBJ���[�h�擾
//
// -----------------------------------------
extern GXOamMode CATS_ObjectObjModeGet(CLACT_WORK_PTR act);
extern GXOamMode CATS_ObjectObjModeGetCap(CATS_ACT_PTR cap);





// =============================================================================
//
//	�����̑��̃c�[���n
//
// =============================================================================
extern BOOL CATS_LoadResourceCharArcModeAdjust(
				CATS_SYS_PTR csp, CATS_RES_PTR crp, int arc_id, int data_id, BOOL comp, int trans_mode, int id );
extern BOOL CATS_LoadResourceCharArcModeAdjustAreaCont(
				CATS_SYS_PTR csp, CATS_RES_PTR crp, int arc_id, int data_id, BOOL comp, int trans_mode, int id);
extern void CATS_ChangeResourceCharArc(
				CATS_SYS_PTR csp, CATS_RES_PTR crp, int arc_id, int data_id, BOOL comp, int id );
extern void CATS_ChangeResourcePlttArc(
				CATS_SYS_PTR csp, CATS_RES_PTR crp, int arc_id, int data_id, BOOL comp, int id );
extern CLACT_SET_PTR CATS_GetClactSetPtr(CATS_RES_PTR crp);
extern const NNSG2dImagePaletteProxy* CATS_PlttProxy( CATS_RES_PTR crp, int pltt_id );
extern u32 CATS_PlttID_NoGet(CATS_RES_PTR crp, int pltt_id, NNS_G2D_VRAM_TYPE vram_type);

#if 0
typedef struct {
	
	int x;
	int y;
	int w;
	int h;
	
} CHANGES_INTO_DATA_RECT;

#define CHAR_DOT_X		(8/2)						///< 1�L�����̃o�C�g�T�C�Y
#define CHAR_DOT_Y		(8)							///< 1�L�����̃o�C�g�T�C�Y
#define CHAR_BYTE		(CHAR_DOT_X * CHAR_DOT_Y)	///< 1�L�����o�C�g��
#define POKE_TEX_SX		(0)							///< �|�P�����ϊ��p�e�N�X�`���؂���ʒu
#define POKE_TEX_SY		(0)
#define POKE_TEX_EX		(10)
#define POKE_TEX_EY		(10)
#define POKE_TEX_SIZE	((POKE_TEX_EX - POKE_TEX_SX) *  (POKE_TEX_EY - POKE_TEX_SY) * CHAR_BYTE)

extern void	 ChangesInto_1D_from_2D(int arc_id, int index_no, int heap_id, int x, int y, int w, int h, void* buff);
extern void	 ChangesInto_1D_from_2D_RC(int arc_id, int index_no, int heap_id, CHANGES_INTO_DATA_RECT* rc, void* buff);

extern void* ChangesInto_1D_from_2D_Alloc(int arc_id, int index_no, int heap_id, int x, int y, int w, int h);
extern void* ChangesInto_1D_from_2D_Alloc_RC(int arc_id, int index_no, int heap_id, CHANGES_INTO_DATA_RECT* rc);

extern void  ChangesInto_OAM_from_1D(int sx, int sy, int x, int y, int w, int h, int* bofs, const void* src, void* dst);
extern void  ChangesInto_OAM_from_1D_RC(int sx, int sy, CHANGES_INTO_DATA_RECT* rc, int* bofs, const void* src, void* dst);

extern void  ChangesInto_OAM_from_PokeTex(int arc_id, int index_no, int heap_id, int x, int y, int w, int h, void* buff);
extern void  ChangesInto_OAM_from_PokeTex_RC(int arc_id, int index_no, int heap_id, CHANGES_INTO_DATA_RECT* rc, void* buff);

extern void* ChangesInto_OAM_from_PokeTex_Alloc(int arc_id, int index_no, int heap_id, int x, int y, int w, int h);
extern void* ChangesInto_OAM_from_PokeTex_Alloc_RC(int arc_id, int index_no, int heap_id, CHANGES_INTO_DATA_RECT* rc);

extern void  ChangesInto_BattlePokeData(int arc_id, int index_no, int heap_id, void* buff);
extern void* ChangesInto_BattlePokeData_Alloc(int arc_id, int index_no, int heap_id);
#endif

#endif
