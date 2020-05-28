//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		blact.c
 *	@brief		�V�K�r���{�[�h�A�N�^�[
 *	@author		tomoya takahashi
 *	@data		2005.10.05
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

#define __BLACT_H_GLOBAL
#include "string.h"
#include "blact.h"
#include "vram_transfer_anm.h"
#include "vram_transfer_manager.h"
#include "simple_3dgraphics.h"
#include "system.h"
#include "str_tool.h"
#include "gflib_os_print.h"
#include "assert.h"

#include "bounding_box.h"

//-----------------------------------------------------------------------------
/**
 *					�萔�錾
 */
//-----------------------------------------------------------------------------
//-------------------------------------
// �A�j���[�V�����`�F���W�����̎��
//
// �A�j���[�V�����Z�b�g�ύX�����̏��
//=====================================
enum
{
	BLACT_CHG_NONE,		// �����Ȃ�
	BLACT_CHG_VRAM,		// Vram�]���o�^�ς�
};

enum{
	BLACT_RES_MAN_MDL,
	BLACT_RES_MAN_TEX,
	BLACT_RES_MAN_ANM
};

enum{
	BLACT_DRAW_REF_NONE,
	BLACT_DRAW_REF_DRAW_BEFORE,
	BLACT_DRAW_REF_DRAW_AFTER,
};

// �풓�A�j��
// �p���b�g�x�[�X�A�h���X���}�X�N
#define BLACT_PLTT_BASE_MASK	(0x000001fff)

//-----------------------------------------------------------------------------
/**
 *					�\���̐錾
 */
//-----------------------------------------------------------------------------


//-------------------------------------
//	�r���{�[�h�A�N�^�[����\����
//
//	�r���{�[�h�P�̂̃f�[�^
//=====================================
typedef struct BLACT_WORK_tag{
	//------------------------------------
	//	�v���O���}�[�����삷�郁���o�S
	//====================================
	VecFx32		Matrix;						// ���΍��W
	VecFx32		Scale;						// �X�P�[��
	
	u8			draw;						// �`����s����(0:�����Ȃ�Ȃ� 1:�s��)

	//------------------------------------
	//	���ڑ�����֎~���郁���o�S
	//===================================
	void*	pBlActSet;		// �����̑����Ă���A�j���[�V�����Z�b�g�̃|�C���^(�L���X�g���Ďg�p)

	const BLACT_ANIME_TBL*	pAnmTbl;		// �A�j���[�V�����e�[�u��
	
	NNSG3dRenderObj			RenderObj;		// �����_�[�I�u�W�F�N�g

	NNSG3dResMdlSet*		pModelSet;		// ���f���Z�b�g
	NNSG3dResMdl*			pModel;			// ���f�����\�[�X
	NNSG3dResTex*			pMdlTex;		// ���f���ɓ\��t����e�N�X�`��
	const NNSG3dResTex*		pAnmTex;		// �A�j���[�V�����p�e�N�X�`��
	NNSGfdTexKey			texKey;			// �e�N�X�`��VramKey
	NNSGfdTexKey			tex4x4Key;		// 4xp�e�N�X�`��VramKey
	NNSGfdPlttKey			plttKey;		// �p���b�gVramKey
	
	TEXANM_DATATBL				texAnm;		// �e�N�X�`���A�j���[�V�����f�[�^
	ITP_VRAM_ANM_PTR		ItpVramObj;		// Vram�]���p�I�u�W�F	(Vram�]�����̂�)
	
	u8			flag;						// On/Off�t���O
	u16			AnmOffs;					// ���̃A�j���[�V�����I�t�Z�b�g
	fx32		frame;						// ���݃t���[��
	
	// �o�^���X�g
	struct BLACT_WORK_tag*	next;	// ���̃A�N�^�[
	struct BLACT_WORK_tag*	prev;	// �O�̃A�N�^�[
	
} BLACT_WORK;


//===================================================================
//
//	�r���{�[�h�A�N�^�[�Z�b�g�\����
//
//	�r���{�[�h�A�N�^�[�̎���
//
//===================================================================
typedef struct _BLACT_SET{
	/* �R���g���[���t���O */
	u8				SysFlag;	// �o�^���Ă��邩	0:��o�^ 1:�o�^
	u8				DrawFlag;	// �`��t���O 0:��`�� 1:�`��(�f�t�H���g)
	u8				MoveFlag;	// TCB�^�X�N�t���O 0:�񓮍� 1:����(�f�t�H���g)

	/* �j�������I�u�W�F�N�g���܂���ʂɔ��f����Ă��� */
	u8				DelObjDrawRef;
	
	/* �r���{�[�h�A�N�^�[����\���� */
	BLACT_WORK*		pWork;		// ����
	int				WorkNum;	// ��
	
	/* ���X�g�g�b�v�f�[�^ */
	BLACT_WORK		Dummy;	
	
	/* �X�^�b�N */
	BLACT_WORK**	ppWorkStack;	// ����(��==WorkNum)
	int				WorkStackNow;	// ���̃g�b�v�̈ʒu
	
	/* �A���P�[�^�[ */
	NNSFndAllocator* pAlloc;		// �g�p����A���P�[�^
	
	/* Vram�]���A�j���[�V�����̃I�u�W�F�N�g */
	ITP_VRAM_SYS_PTR pItpTop;


}BLACT_SET;



//----------------------------------------------------------------------------
/**
 *					�v���g�^�C�v�錾
 */
//-----------------------------------------------------------------------------
//-------------------------------------
//	�r���{�[�h�A�N�^�[�V�X�e������֐�
//=====================================
static BLACT_SET_PTR getCleanBlActSet(void);
static void cleanBlActSet(BLACT_SET* work);

//-------------------------------------
//	BLACT_SET����֐�
//=====================================
static void drawBlActSet(BLACT_SET* pBlActSet);
static void drawBlAct( BLACT_WORK *act );

//-------------------------------------
//	�풓�A�j���p�V�X�e��
//=====================================
static void normAnmTexDataSet( BLACT_WORK* act );
static void normAnmTexParamSet( NNSG3dResMdl* p_mdl, const NNSG3dResTex* p_tex, u8 tex_idx );
static void normAnmTexParamSetOneMatData( NNSG3dResMat* pMat, const	NNSG3dResDictTexToMatIdxData* pBindData, u32 tex_offs );
static void normAnmPlttParamSet( NNSG3dResMdl* p_mdl, const NNSG3dResTex* p_tex, u8 pltt_idx );
static void normAnmPlttParamSetOneMatData( NNSG3dResMat* pMat, const NNSG3dResDictPlttToMatIdxData* pBindData, u32 pltt_offs );


//-------------------------------------
//	stack�̏���
//=====================================
static void initStack(BLACT_SET* pSet);			// ������
static BLACT_WORK* popStack(BLACT_SET* pSet);	// ���o��
static BOOL pushStack(BLACT_SET* pSet, BLACT_WORK* pDat);	// �i�[

//-------------------------------------
//	���X�g�Ǘ�
//=====================================
static void setList(BLACT_WORK* Dummy, BLACT_WORK* pDat);
static void remList(BLACT_WORK* pDat);

//-------------------------------------
//	�e�N�X�`���̕`��O����
//	�e�N�X�`���̕`��㏈��
//=====================================
static void DrawTexBind(BLACT_WORK* bl_w);
static void DrawTexreBind(BLACT_WORK* bl_w);

//-------------------------------------
//	�ւ����[���烊�\�[�X���擾
//=====================================
static void* getRes(const BLACT_HEADER* p_head, int flag);
static const BLACT_ANIME_TBL* getAnmTbl(const BLACT_ANIME_TBL* p_anm, int ofs);

//-------------------------------------
//	�f�[�^���[�h�n�֐��S
//=====================================
static NNSG3dResMdlSet* blact_getMdl(const BLACT_HEADER* p_head,NNSG3dResMdl** ppMdl, NNSG3dResTex** ppTex);
static NNSG3dAnmObj* blact_getItp(const BLACT_HEADER* p_head, const NNSG3dResMdl* p_mdl, const NNSG3dResTex* p_tex, NNSFndAllocator* pAlloc);
static NNSG3dResTex* blact_getTex(const BLACT_HEADER* p_head);

//-------------------------------------
//	�A�j���[�V�����Z�b�g�ύX�f�[�^
//=====================================
static void chgBillboadAnmSet_Core( BLACT_WORK* act, const BLACT_HEADER* header );
// Vram�]���p�e�[�u���f�[�^�ݒ�֐�
static void chgBillboadAnmSet_Core_VRAM( BLACT_WORK* act, const BLACT_HEADER* header );
// �풓�p�A�j���[�V�����Z�b�g�ύX�֐�
static void core_anmset_chg_norm( BLACT_WORK* blact_w, const BLACT_HEADER* header);

static fx32	nowOffsAnmStartFrame( const BLACT_WORK* act, int offs );
static int anmFrameChg_Core( BLACT_WORK* act, fx32 num );

static int anmFrameChgSys( const BLACT_ANIME_TBL* anm, fx32* frame, fx32 num );

//-------------------------------------
//
//�@�e�N�X�`���\��t���A�j������
//				�֐��S
//	
//=====================================
static void allocTexKey(const NNSG3dResTex* tex, NNSG3dTexKey* texkey, NNSG3dTexKey* tex4x4key, NNSG3dPlttKey* plttkey);
static void releaseTexture(NNSG3dResTex* tex, NNSG3dTexKey* texkey, NNSG3dTexKey* tex4x4key, NNSG3dPlttKey* plttkey);
static void reBindTexture(NNSG3dResTex* tex, NNSG3dResMdlSet* mdl, NNSG3dTexKey* texkey, NNSG3dTexKey* tex4x4key, NNSG3dPlttKey* plttkey);
static void delBindTexture(NNSG3dTexKey* texkey, NNSG3dTexKey* tex4x4key, NNSG3dPlttKey* plttkey);
static BOOL check_texsize_equal(const NNSG3dResTex* tex1, const NNSG3dResTex* tex2);

//-------------------------------------
//
//	�r���{�[�h�A�N�^�[�j������
//	�֐��S
//	
//=====================================
static void del_blact(BLACT_SET* pBlActSet, BLACT_WORK* delWork);// �j������

//-------------------------------------
//
//	�r���{�[�h�A�N�^�[�o�^����
//	�֐��S
//	
//=====================================
static void data_chg_vram_mdl_core(BLACT_WORK* blact_w, const BLACT_HEADER* header);
static void data_chg_vram_anm_core(const BLACT_SET* pBlActSet, BLACT_WORK* blact_w, const BLACT_HEADER* header);

static void data_chg_norm_mdl_core(BLACT_WORK* blact_w, const BLACT_HEADER* header);
static void data_chg_norm_anm_core(BLACT_WORK* blact_w, const BLACT_HEADER* header);

//----------------------------------------------------------------------------
/**
 *					�O���[�o���ϐ��錾
 */
//-----------------------------------------------------------------------------
static BLACT_SET*	pBlActSetTbl=NULL;	// �r���{�[�h�A�N�^�[�Ǘ��e�[�u��
static int			BlActSetNum=0;		// �o�^�\��


//-----------------------------------------------------------------------------
/**
 * 
 *	@brief	BLACT_SET�\���̌^�f�[�^�@�N���A
 *
 *	@param	work	BLACT_SET�\���̌^�f�[�^�ւ̃|�C���^
 *	@return none
 *	
 */
//-----------------------------------------------------------------------------
static void cleanBlActSet(BLACT_SET* work)
{
	work->SysFlag		= 0;
	work->DrawFlag		= 0;
	work->pWork			= NULL;
	work->WorkNum		= 0;
	work->ppWorkStack	= NULL;
	work->WorkStackNow	= 0;
	work->pAlloc		= NULL;
	work->pItpTop		= NULL;
	work->DelObjDrawRef = BLACT_DRAW_REF_NONE;
}

//-----------------------------------------------------------------------------
/**
 * 
 *	@brief	BLACT_WORK�\���̌^�f�[�^�@�N���A
 *
 *	@param	pDat	BLACT_WORK�\���̌^�f�[�^�ւ̃|�C���^
 *	@return none
 *	
 */
//-----------------------------------------------------------------------------
void BLACT_WorkClear( BLACT_WORK *pDat )
{
	u8 i = 0;

	pDat->pBlActSet = NULL;
	pDat->pAnmTbl	= NULL;
	
	pDat->pModelSet	= NULL;			// ���f���Z�b�g
	pDat->pModel	= NULL;			// ���f��
	pDat->pMdlTex	= NULL;			// ���f���ɓ\��t����e�N�X�`��
	pDat->pAnmTex	= NULL;			// �A�j���[�V�����p�e�N�X�`��
	// �A�j���[�V�����f�[�^
	memset( &pDat->texAnm, 0, sizeof(TEXANM_DATATBL) );
	pDat->texKey	= BLACT_TEXKEY_VRAMANM;
	pDat->tex4x4Key	= BLACT_TEXKEY_VRAMANM;
	pDat->plttKey	= BLACT_PLTTKEY_VRAMANM;
	pDat->ItpVramObj = NULL;

	VEC_Set(&(pDat->Matrix),0,0,0);
	VEC_Set(&(pDat->Scale),FX32_ONE,FX32_ONE,FX32_ONE);

	pDat->AnmOffs = 0;

	pDat->flag = 0;

	pDat->next = NULL;
	pDat->prev = NULL;
	pDat->draw = 0;
}

//=============================================================================
//
//		�r���{�[�h�A�N�^�[�V�X�e������֐��S
//		
//		�r���{�[�h�A�N�^�[�̃V�X�e���𑀍삷��֐�
//=============================================================================
//-----------------------------------------------------------------------------
/**
 *
 *	@brief	�r���{�[�h�A�N�^�[�V�X�e���̏�����
 *
 *	@param	ContNum			�Ǘ��r���{�[�h�A�N�^�[�Z�b�g��
 *	@param	heap			�g�p�q�[�v
 *
 *	@return none
 *
 * �r���{�[�h�A�N�^�[�g�p�O�ɂP�x���s
 * 
 */
//-----------------------------------------------------------------------------
void BLACT_InitSys(int ContNum, int heap)
{
	int i;		// ���[�v�p

	
	GF_ASSERT((pBlActSetTbl==NULL) && "�������ς݂ł�\n");
	
	// �Ǘ��e�[�u���쐬
	pBlActSetTbl = sys_AllocMemory(heap, sizeof(BLACT_SET) * ContNum);
	BlActSetNum = ContNum;

	// ������
	for(i=0;i<ContNum;i++){
		cleanBlActSet(&pBlActSetTbl[i]);
	}
}

//-----------------------------------------------------------------------------
/**
 *
 *	@brief	�r���{�[�h�A�N�^�[�V�X�e���̔j��
 *
 *	@param	none
 *
 *	@return none
 *
 * �r���{�[�h�A�N�^�[�g�p��ɂP�x�K�v
 * 
 */
//-----------------------------------------------------------------------------
void BLACT_DestSys(void)
{
	int i;		// ���[�v�p
	
	// �r���{�[�h�A�N�^�[�Z�b�g�S�Ă��͂�
	for(i=0;i<BlActSetNum;i++){
		BLACT_DestSet(pBlActSetTbl + i);
	}

	sys_FreeMemoryEz(pBlActSetTbl);
	pBlActSetTbl = NULL;
	BlActSetNum = 0;
}

//-----------------------------------------------------------------------------
/**
 *
 *	@brief	�r���{�[�h�A�N�^�[�V�X�e���̕`��
 *
 *	@param	none
 *
 *	@return none
 *
 * �o�^����Ă���r���{�[�h�A�N�^�[�Z�b�g��`�悵�܂��B
 *
 * �`�悵�����Ȃ��Ƃ���
 *		BLACT_SET�\���̂�DrawFlag ��0�ɂ���
 * 
 */
//-----------------------------------------------------------------------------
void BLACT_DrawSys(void)
{
	int i;		// ���[�v�p
	
	// �r���{�[�h�A�N�^�[�Z�b�g�S�Ă�`��
	for(i=0;i<BlActSetNum;i++){
		if(pBlActSetTbl[i].DrawFlag == 1){	
			drawBlActSet(&pBlActSetTbl[i]);
		}
		if( pBlActSetTbl[i].DelObjDrawRef == BLACT_DRAW_REF_DRAW_BEFORE ){
			pBlActSetTbl[i].DelObjDrawRef = BLACT_DRAW_REF_DRAW_AFTER;
		}
	}
}

//-----------------------------------------------------------------------------
/**
 *
 *	@brief	�r���{�[�h�A�N�^�[�P�̂̕`��
 *
 *	@param	act	BLACT_WORK_PTR
 *
 *	@return none
 *
 * �w�肵���r���{�[�h�A�N�^�[�Z�b�g��`�悵�܂��B
 *
 * �`�悵�����Ȃ��Ƃ���
 *		BLACT_SET�\���̂�DrawFlag ��0�ɂ���
 * 
 */
//-----------------------------------------------------------------------------
void BLACT_Draw(BLACT_WORK_PTR act)
{
	drawBlAct(act);
}

//=============================================================================
//
//		�r���{�[�h�A�N�^�[�Z�b�g����֐��S
//		
//=============================================================================
//-----------------------------------------------------------------------------
/**
 *
 *	@brief	�r���{�[�h�A�N�^�[�Z�b�g�ݒ�
 *
 *	@param	pSetData		�A�N�^�[�Z�b�g���	
 *
 *	@retval	BLACT_SET_PTR	�A�N�^�[�Z�b�g�|�C���^
 *	@retval	NULL			�o�^���s
 *
 * 
 */
//-----------------------------------------------------------------------------
BLACT_SET_PTR BLACT_InitSet(const BLACT_SETDATA* pSetData)
{
	BLACT_SET* set;
	
	// �e�[�u������󂢂Ă���A�N�^�[�Z�b�g���擾
	set = getCleanBlActSet();

	if(set == NULL){
		GF_ASSERT_MSG( 0, "�o�^�ł���A�N�^�[�Z�b�g������܂���B\n BLACT_InitSys�̑�P�����̐��𑝂₵�Ă�������\n" );
		return NULL;
	}

	// �e�f�[�^�̈���쐬
	set->SysFlag = 1;		// �o�^
	set->DrawFlag = 1;		// �`��
	
	// �A�N�^�[���[�N
	set->pWork = sys_AllocMemory(pSetData->heap, sizeof(BLACT_WORK)*pSetData->WorkNum);
	set->WorkNum = pSetData->WorkNum;
	
	// ���X�g�_�~�[�f�[�^
	BLACT_WorkClear(&set->Dummy);
	set->Dummy.next = &set->Dummy;
	set->Dummy.prev = &set->Dummy;
	
	// �X�^�b�N
	set->ppWorkStack = sys_AllocMemory(pSetData->heap, sizeof(BLACT_WORK*)*pSetData->WorkNum);
	initStack(set);
	
	// �A���P�[�^�쐬
	set->pAlloc = sys_AllocMemory(pSetData->heap, sizeof(NNSFndAllocator));
	sys_InitAllocator(set->pAlloc, pSetData->heap,4);
	// ITPVram�]���A�j�����쐬
	set->pItpTop = initItpVramAnm(pSetData->WorkNum, pSetData->heap);

	return set;
}

//-----------------------------------------------------------------------------
/**
 *
 *	@brief	�r���{�[�h�A�N�^�[�Z�b�g�j��
 *
 *	@param	bl_set			�A�N�^�[�Z�b�g�|�C���^
 *
 *	@retval	TRUE			����
 *	@retval	FALSE			���s
 *
 * 
 */
//-----------------------------------------------------------------------------
BOOL BLACT_DestSet(BLACT_SET_PTR bl_set)
{
	// �r���{�[�h�A�N�^�[�Z�b�g�擾
	if(bl_set == NULL){
		GF_ASSERT_MSG( 0, "NULL�ł�\n" );
		return FALSE;
	}

	if(bl_set->SysFlag != 0){
		// �r���{�[�h���S�j��
		BLACT_DeleteWorkAllSet(bl_set);

		// �Ǘ��f�[�^�j��
		sys_FreeMemoryEz(bl_set->pWork);
		sys_FreeMemoryEz(bl_set->ppWorkStack);
		sys_FreeMemoryEz(bl_set->pAlloc);
		destItpVramAnm(bl_set->pItpTop);

		cleanBlActSet(bl_set);
	}

	return TRUE;
}

//-----------------------------------------------------------------------------
/**
 *
 *	@brief	�r���{�[�h�A�N�^�[�Z�b�g�`��t���O��ݒ�
 *
 *	@param	bl_set			�A�N�^�[�Z�b�g�|�C���^	
 *	@param	flag			�ݒ肷��t���O�l	0:��`�� 1:�`��
 *
 *	@retval	TRUE			����
 *	@retval	FALSE			���s
 *
 * 
 */
//-----------------------------------------------------------------------------
BOOL BLACT_DrawFlagSet(BLACT_SET_PTR bl_set, u8 flag)
{
	// �r���{�[�h�A�N�^�[�Z�b�g�擾
	if(bl_set == NULL){
		GF_ASSERT_MSG( 0, "NULL�ł�\n" );
		return FALSE;
	}

	if(bl_set->SysFlag != 0){
		bl_set->DrawFlag = flag;
	}

	return TRUE;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�r���{�[�h�A�N�^�[�Z�b�g�̕`��t���O���擾
 *
 *@param	bl_set		�A�N�^�[�Z�b�g�|�C���^	
 *
 *@return	u8			1:�`��		0:��`��
 *
 *
 */
//-----------------------------------------------------------------------------
u8 BLACT_DrawFlagGet(CONST_BLACT_SET_PTR bl_set)
{
	if(bl_set == NULL){
		GF_ASSERT_MSG( 0, "NULL�ł�\n" );
		return 0;
	}

	if(bl_set->SysFlag != 0){
		return bl_set->DrawFlag;
	}

	return 0;
}

//-----------------------------------------------------------------------------
/**
 *
 *	@brief	�r���{�[�h�A�N�^�[�Z�b�g�̑S�r���{�[�h�j��
 *	
 *	@param	bl_set			�A�N�^�[�Z�b�g�|�C���^
 *
 *	@retval	TRUE			����
 *	@retval	FALSE			���s
 *
 */
//-----------------------------------------------------------------------------
BOOL BLACT_DeleteWorkAllSet(BLACT_SET_PTR bl_set)
{
	BLACT_WORK*	roop;
	BLACT_WORK*	next;
	
	// �r���{�[�h�A�N�^�[�Z�b�g�擾
	if(bl_set == NULL){
		GF_ASSERT_MSG(bl_set, "NULL�ł�\n");
		return FALSE;
	}

	if(bl_set->SysFlag != 0){
			
		// ���X�g�̃f�[�^�S�j��
		roop = bl_set->Dummy.next;
		while(roop != &bl_set->Dummy){
			next = roop->next;
			// �j��
			BLACT_Delete(roop);
			roop = next;
		}
		
	}

	return TRUE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�j�������I�u�W�F�N�g���܂���ʂɔ��f����Ă��邩�`�F�b�N
 *	
 *	@param	bl_set	�A�N�^�[�Z�b�g
 *
 *	@retval	TRUE	���f����Ă���
 *	@retval	FALSE	���f����Ă��Ȃ�
 */
//-----------------------------------------------------------------------------
BOOL BLACT_DelObjRefCheck( BLACT_SET_PTR bl_set )
{
	GF_ASSERT( bl_set );
	if( bl_set->DelObjDrawRef == BLACT_DRAW_REF_NONE ){
		return FALSE;
	}
	return TRUE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�r���{�[�h�A�N�^�[V�u�����N����
 *
 *	@param	act		���[�N
 */
//-----------------------------------------------------------------------------
void BLACT_VBlankFunc( BLACT_SET_PTR bl_set )
{
	// VBlank�ɂ����̂ŁA�X���b�v�o�b�t�@���s���
	// ���܂Ŕj�������̂ɕ`�悳��Ă����|���S����������
	if( bl_set->DelObjDrawRef == BLACT_DRAW_REF_DRAW_AFTER ){
		bl_set->DelObjDrawRef = BLACT_DRAW_REF_NONE;
	}
}


//=============================================================================
//
//		�r���{�[�h�A�N�^�[�Z�b�g����v���C�x�[�g�֐��S
//
//=============================================================================
//-----------------------------------------------------------------------------
/**
 *
 *	@brief	�󂢂Ă���r���{�[�h�A�N�^�[�Z�b�g�擾
 *
 *	@param	none
 *
 *	@retval	BLACT_SET_PTR	�A�N�^�[�Z�b�g�|�C���^
 *	@retval	NULL			���s
 *
 * 
 */
//-----------------------------------------------------------------------------
static BLACT_SET_PTR getCleanBlActSet(void)
{
	int i;		// ���[�v�p

	for(i=0;i<BlActSetNum;i++){
		if(pBlActSetTbl[i].SysFlag == 0){
			return &pBlActSetTbl[i];
		}
	}

	return NULL;
}

//-----------------------------------------------------------------------------
/**
 *
 *	@brief	�r���{�[�h�A�N�^�[�Z�b�g�̕`��
 *
 *	@param	pBlActSet	�`�悷��r���{�[�h�A�N�^�[�Z�b�g
 *	@return	none
 *
 * �r���{�[�h�A�N�^�[�Z�b�g�ɓo�^���ꂽ�A�N�^�[��`�悵�܂�
 *
 */
//-----------------------------------------------------------------------------
static void drawBlActSet( BLACT_SET* pBlActSet )
{
	BLACT_WORK* roop;		// ���[�v�p
	MtxFx33 rot;				// ��]�s��
	VecFx32	matrix;				// ��΍��W�{���΍��W

	GF_ASSERT( pBlActSet );
	
	// ��]�s���P�ʍs��ɂ���
	MTX_Identity33( &rot );
	
	roop = pBlActSet->Dummy.next;
	while(roop != &pBlActSet->Dummy){
		
		if(roop->draw == 1){		// �\�����邩�`�F�b�N
			
			// �e�N�X�`���o�C���h
			DrawTexBind(roop);
	
			// �e�A�j���[�V�����̍X�V����
			// �`��֐��Ȃ̂ɕ`��ȊO�̂��Ƃ��s���̂͗ǂ��Ȃ��ł����A
			// �o�C���h�����f�[�^�ɍs���K�v�����邽��
			// �����ōs���܂�
			if(roop->flag == BLACT_MOVE_NORM){
				//�풓�A�j���e�N�X�`���E�p���b�g�Q�Ɛ�ݒ�
				normAnmTexDataSet( roop );
			}else{
				if(roop->flag == BLACT_MOVE_VRAM){
					BLACT_VramAnmTransUserReq( roop );
				}
			}
			
			// �`��
			simple_3DModelDraw(
					&roop->RenderObj,		// �����_�[�I�u�W�F
					&roop->Matrix,			// ���W
					&rot,					// ��]�s��
					&roop->Scale);			// �g�k
			
			// �e�N�X�`�����o�C���h
			DrawTexreBind(roop);
			
		}
		roop = roop->next;
	}
}

//-----------------------------------------------------------------------------
/**
 *
 *	@brief	�r���{�[�h�A�N�^�[�`��
 *
 *	@param	act		�`�悷��r���{�[�h�A�N�^�[
 *	@return	none
 *
 * �A�N�^�[��`�悵�܂�
 *
 */
//-----------------------------------------------------------------------------
static void drawBlAct( BLACT_WORK *act )
{
	MtxFx33 rot;				// ��]�s��
	VecFx32	matrix;				// ��΍��W�{���΍��W

	GF_ASSERT( act );
	MTX_Identity33( &rot );
	
	if( act->draw == FALSE ){
		return;
	}
	
	DrawTexBind( act );
	
	if( act->flag == BLACT_MOVE_NORM){
		normAnmTexDataSet( act );
	}else if( act->flag == BLACT_MOVE_VRAM ){
		transItpVramAnm( act->ItpVramObj, act->frame );
	}
	
	simple_3DModelDraw( &act->RenderObj, &act->Matrix, &rot, &act->Scale );
	DrawTexreBind( act );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	Vram�]�����p�@�f�[�^�`�F���W�f�[�^�i�[�֐�
 *
 *	@param	act			�r���{�[�h�A�N�^�[
 *	@param	header		�w�b�_�[�f�[�^
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void chgBillboadAnmSet_Core_VRAM( BLACT_WORK* act, const BLACT_HEADER* header )
{
	BLACT_SET*	as;	// �A�N�^�[�Z�b�g

	// �����̐e�̃r���{�[�h�Z�b�g���
	as = (BLACT_SET*)act->pBlActSet;		

	// ���܂ł̃A�j���f�[�^�j��
	del_blact(as, act);

	// �V�������\�[�X�������_�[�I�u�W�F�Ɋ֘A�t����
	// ���f�����\�[�X
	// ������VramKey�̎擾���s��
	data_chg_vram_mdl_core(act, header);
	
	// �u�������]���}�l�[�W���[�Ƀ��X�g��ǉ�
	data_chg_vram_anm_core(as, act, header);

	if(act->flag == BLACT_MOVE_INIT){
		// ���X�g�ɐݒ�
		setList(&as->Dummy, act);
	}

	// ���s���[�h��ݒ�
	act->flag = BLACT_MOVE_VRAM;

	// �A�j���[�V�����e�[�u���ݒ�
	act->pAnmTbl	= header->anm;

	// �A�j���[�V�����I�t�Z�b�g�ƁA�t���[�������Z�b�g
	act->AnmOffs		= 0;
	act->frame			= 0;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�풓�A�j���̃A�j���[�V�����Z�b�g��ύX����֐�
 *
 *	@param	blact_w		�r���{�[�h���[�N
 *	@param	header		�w�b�_�[
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void core_anmset_chg_norm( BLACT_WORK* blact_w, const BLACT_HEADER* header)
{
	BLACT_SET* pBlActSet = blact_w->pBlActSet;

	// ���܂ł̃f�[�^��j��	
	// ���f�����\�[�X�����
	del_blact(pBlActSet, blact_w);

	// Vram�]�����[�h�̎��̓r���{�[�h�A�N�^�[��
	// Vram���m�ۂ��Ă���̂Ńr���{�[�h�A�N�^�[���Ŕj������
	if(blact_w->flag == BLACT_MOVE_VRAM){
		// VramKey��j��
		delBindTexture( &blact_w->texKey, &blact_w->tex4x4Key, &blact_w->plttKey );
	}

	// �f�[�^��ݒ�
	// ���f���f�[�^�@�A�j���f�[�^�@VramKey�̐ݒ�
	// VramKey��ݒ�
	blact_w->texKey		= header->texKey;
	blact_w->tex4x4Key	= header->tex4x4Key;
	blact_w->plttKey	= header->plttKey;

	// ���f�����\�[�X�������_�[�I�u�W�F�ɐݒ�
	data_chg_norm_mdl_core( blact_w, header );

	// �A�j���[�V�����I�u�W�F���\�z���A�����_�[�I�u�W�F�ɓo�^
	data_chg_norm_anm_core( blact_w, header );


	if(blact_w->flag == BLACT_MOVE_INIT){
		// ���X�g�ɐݒ�
		setList(&pBlActSet->Dummy, blact_w);
	}


	// ���s���[�h��ݒ�
	blact_w->flag = BLACT_MOVE_NORM;

	// �A�j���[�V�����e�[�u���ݒ�
	blact_w->pAnmTbl	= header->anm;

	// �A�j���[�V�����I�t�Z�b�g�ƁA�t���[�������Z�b�g
	blact_w->AnmOffs		= 0;
	blact_w->frame			= 0;
}


//----------------------------------------------------------------------------
//
//
//	�A�j���[�V�����Z�b�g�ύX�֐��̃R�A�֐��S
//
//
//============================================================================
//----------------------------------------------------------------------------
/**
 *
 *@brief	�e�N�X�`���L�[�̈��Vram�}�l�[�W���[����m�ۂ���
 *
 *@param	tex			�e�N�X�`�����\�[�X
 *@param	texkey		�e�N�X�`���L�[
 *@param	tex4x4key	4x4���k�e�N�X�`���L�[
 *@param	plttkey		�p���b�g�L�[
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void allocTexKey(const NNSG3dResTex* tex, NNSG3dTexKey* texkey, NNSG3dTexKey* tex4x4key, NNSG3dPlttKey* plttkey)
{
    u32 szTex, szTex4x4, szPltt;
	

	// �K�v�ȃT�C�Y���擾
	szTex    = NNS_G3dTexGetRequiredSize(tex);
	szTex4x4 = NNS_G3dTex4x4GetRequiredSize(tex);
	szPltt   = NNS_G3dPlttGetRequiredSize(tex);

	if (szTex > 0){
		// ���݂���΃e�N�X�`���C���[�W�X���b�g�Ɋm��
		*texkey = NNS_GfdAllocTexVram(szTex, FALSE, 0);
		GF_ASSERT(*texkey != BLACT_TEXKEY_VRAMANM);
//		OS_Printf( "tex addr %x size %x\n", NNS_GfdGetTexKeyAddr(*texkey), NNS_GfdGetTexKeySize(*texkey) );
	}else{
		*texkey = 0;
	}

	if (szTex4x4 > 0){
		// ���݂���΃e�N�X�`���C���[�W�X���b�g�Ɋm��
		*tex4x4key = NNS_GfdAllocTexVram(szTex4x4, TRUE, 0);
		GF_ASSERT(*tex4x4key != BLACT_TEXKEY_VRAMANM);
//		OS_Printf( "4x4tex addr %x size %x\n", NNS_GfdGetTexKeyAddr(*tex4x4key), NNS_GfdGetTexKeySize(*tex4x4key) );
	}else{
		*tex4x4key = 0;
	}

	if (szPltt > 0){
		// ���݂���΃e�N�X�`���p���b�g�X���b�g�Ɋm��
		*plttkey = NNS_GfdAllocPlttVram(szPltt,
							tex->tex4x4Info.flag & NNS_G3D_RESPLTT_USEPLTT4,
							0);
		GF_ASSERT(*plttkey != BLACT_PLTTKEY_VRAMANM);
//		OS_Printf( "pltt addr %x size %x\n", NNS_GfdGetPlttKeyAddr(*plttkey), NNS_GfdGetPlttKeySize(*plttkey) );
	}else{
		*plttkey = 0;
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�e�N�X�`���Ƀo�C���h����Ă���Vram�L�[����������
 *
 *@param	tex			�e�N�X�`��
 *@param	texkey		�ʏ�e�N�X�`���L�[
 *@param	tex4x4key	4x4���k�e�N�X�`���L�[
 *@param	plttkey		�p���b�g�L�[
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void releaseTexture(NNSG3dResTex* tex, NNSG3dTexKey* texkey, NNSG3dTexKey* tex4x4key, NNSG3dPlttKey* plttkey)
{
	// ���
	NNS_G3dTexReleaseTexKey( tex, texkey, tex4x4key );
	*plttkey = NNS_G3dPlttReleasePlttKey( tex );
}


//----------------------------------------------------------------------------
/**
 *
 *@brief	�e�N�X�`���L�[�̍Đݒ�
 *
 *@param	tex			�e�N�X�`�����[�X
 *@param	mdl			���f�����\�[�X�Z�b�g
 *@param	texkey		�ʏ�e�N�X�`���L�[
 *@param	tex4x4key	4x4���k�e�N�X�`���L�[
 *@param	plttkey		�p���b�g�L�[
 * 
 *@return
 *
 *
 */
//-----------------------------------------------------------------------------
static void reBindTexture(NNSG3dResTex* tex, NNSG3dResMdlSet* mdl, NNSG3dTexKey* texkey, NNSG3dTexKey* tex4x4key, NNSG3dPlttKey* plttkey)
{
	// �e�N�X�`���L�[
	NNS_G3dTexSetTexKey( tex, *texkey, *tex4x4key );
	// �p���b�g�L�[
	NNS_G3dPlttSetPlttKey( tex, *plttkey );

	// �o�C���h
	// ���f���Z�b�g�̃o�C���h
	NNS_G3dBindMdlSet(mdl, tex);
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�e�N�X�`���L�[��j������
 *
 *@param	texkey		�ʏ�e�N�X�`���L�[
 *@param	tex4x4key	4x4���k�e�N�X�`���L�[
 *@param	plttkey		�p���b�g�L�[
 *
 *@return
 *
 *
 */
//-----------------------------------------------------------------------------
static void delBindTexture(NNSG3dTexKey* texkey, NNSG3dTexKey* tex4x4key, NNSG3dPlttKey* plttkey)
{
	if(*texkey != BLACT_TEXKEY_VRAMANM){
		NNS_GfdFreeTexVram( *texkey );
	}
	if(*tex4x4key != BLACT_TEXKEY_VRAMANM){
		NNS_GfdFreeTexVram( *tex4x4key );
	}
	if(*plttkey != BLACT_PLTTKEY_VRAMANM){
		NNS_GfdFreePlttVram( *plttkey );
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�e�N�X�`���T�C�Y�����������`�F�b�N����
 *
 *@param	tex		�`�F�b�N����e�N�X�`�����\�[�X
 *
 *@retval	TRUE	������
 *@retval	FALSE	�������Ȃ�
 *
 *
 */
//-----------------------------------------------------------------------------
static BOOL check_texsize_equal(const NNSG3dResTex* tex1, const NNSG3dResTex* tex2)
{
	u32 szTex0, szTex4x40, szPltt0;		// �e�T�C�Y
	u32 szTex1, szTex4x41, szPltt1;		// �e�T�C�Y
	BOOL ret;

	if((tex1 == NULL) || (tex2 == NULL)){
		return FALSE;
	}
	
	szTex0    = NNS_G3dTexGetRequiredSize(tex1);  
	szTex4x40 = NNS_G3dTex4x4GetRequiredSize(tex1);
	szPltt0   = NNS_G3dPlttGetRequiredSize(tex1);

	szTex1    = NNS_G3dTexGetRequiredSize(tex2);  
	szTex4x41 = NNS_G3dTex4x4GetRequiredSize(tex2);
	szPltt1   = NNS_G3dPlttGetRequiredSize(tex2);

	// �T�C�Y���Ⴄ���`�F�b�N
	if( (szTex0 != szTex1) || (szTex4x40 != szTex4x41) || (szPltt0 != szPltt1) ){
		ret = FALSE;		// �������Ȃ�
	}else{
		ret = TRUE;			// ������
	}

	return ret;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�r���{�[�h�A�N�^�[�j������
 *
 *@param	pBlActSet	�r���{�[�h�A�N�^�[�Z�b�g
 *@param	delWork		�j������r���{�[�h�A�N�^�[
 *
 * ���S�ɔj������Ƃ���
 *	���̌ハ�[�N���X�^�b�N�Ƀv�b�V������K�v������B
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void del_blact(BLACT_SET* pBlActSet, BLACT_WORK* delWork)
{

	if(delWork->ItpVramObj){
		// �u�������]���A�j�����X�g����j��
		remItpVramAnm( delWork->ItpVramObj );
		delWork->ItpVramObj = NULL;
	}
}


//----------------------------------------------------------------------------
/**
 *
 *@brief	���f���f�[�^�����[�N�ɐݒ�
 *
 *@param	blact_w			�f�[�^�i�[�惏�[�N
 *@param	header			�w�b�_�[
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void data_chg_vram_mdl_core(BLACT_WORK* blact_w, const BLACT_HEADER* header)
{
	NNSG3dResTex* old_tex;
	int	result;

	// �e�N�X�`���̃T�C�Y���Ⴄ�����`�F�b�N���邽��
	// �Â��e�N�X�`����ۑ�
	old_tex = blact_w->pMdlTex;	

	// �r���{�[�h�̃f�[�^�����\�[�X�}�l�[�W���[����擾	
	blact_w->pModelSet = blact_getMdl(	// ���f�����\�[�X�Z�b�g�擾
			header,					// �w�b�_�[
			&blact_w->pModel,		// ���f�����\�[�X
			&blact_w->pMdlTex);		// �e�N�X�`�����\�[�X
	
	NNS_G3dRenderObjInit( &blact_w->RenderObj, blact_w->pModel );	// �����_�[�I�u�W�F������

	// �Â��e�N�X�`���Ɣ�ׁAVramKey��ς���K�v�����邩�`�F�b�N
	// �O���풓�A�j���̂Ƃ��͖�������VramKey���擾����
	if(blact_w->flag != BLACT_MOVE_NORM){
		
		result = check_texsize_equal(old_tex, blact_w->pMdlTex);
	}else{
		result = FALSE;
	}
	if(result == FALSE){	// result��FALSE�Ȃ�VramKey�̍Ď擾

		// �O��Vram�]���Ȃ獡��VramKey��j��
		if( blact_w->flag == BLACT_MOVE_VRAM ){
			delBindTexture(
					&(blact_w->texKey),
					&(blact_w->tex4x4Key),
					&(blact_w->plttKey) );
		}
		allocTexKey(
				blact_w->pMdlTex,
				&(blact_w->texKey),
				&(blact_w->tex4x4Key),
				&(blact_w->plttKey) );
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�e�N�X�`���p�^�[���A�j���[�V����
 *
 *@param	pBlActSet		�r���{�[�h�A�N�^�[�Z�b�g
 *@param	blact_w			�f�[�^�i�[�惏�[�N 
 *@param	header			�w�b�_�[
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void data_chg_vram_anm_core(const BLACT_SET* pBlActSet, BLACT_WORK* blact_w, const BLACT_HEADER* header)
{
	
	// �p�^�[���̃e�N�X�`���擾
	blact_w->pAnmTex = blact_getTex(
			header );

//	OS_Printf( "tex %x \n",NNS_G3dTexGetRequiredSize(p_tex) );

	// �e�N�X�`���A�j���[�V�����f�[�^��ݒ�
	blact_w->texAnm = header->texanm;

	// Vram�]���A�j���[�V�������`�F�b�N
	// �u�������]���A�j���[�V�����V�X�e���ɃZ�b�g
	blact_w->ItpVramObj = addItpVramAnm( 
				pBlActSet->pItpTop,
				&blact_w->texAnm,		// �A�j���[�V�����f�[�^�e�[�u��
				blact_w->pAnmTex,		// �e�N�X�`��
				blact_w->texKey,		// �e�N�X�`���f�[�^�]��VramKey
				blact_w->plttKey,		// �p���b�g�f�[�^�]��VramKey
				blact_w->frame			// �t���[���l
				);		

}


//----------------------------------------------------------------------------
/**
 *
 *	@brief	�풓�A�j���p���f���f�[�^�쐬
 *
 *	@param	blact_w		�r���{�[�h���[�N
 *	@param	header		�w�b�_�[
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void data_chg_norm_mdl_core(BLACT_WORK* blact_w, const BLACT_HEADER* header)
{
	// �r���{�[�h�̃f�[�^�����\�[�X�}�l�[�W���[����擾	
	blact_w->pModelSet = blact_getMdl(	// ���f�����\�[�X�Z�b�g�擾
			header,						// �w�b�_�[
			&blact_w->pModel,			// ���f�����\�[�X
			&blact_w->pMdlTex );		// �o�C���h�p�e�N�X�`�����\�[�X

	NNS_G3dRenderObjInit( &blact_w->RenderObj, blact_w->pModel );	// �����_�[�I�u�W�F������

	// �A�j���[�V�����p�e�N�X�`���擾
	blact_w->pAnmTex = blact_getTex(
			header );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�풓�A�j���p�A�j���[�V�����I�u�W�F�������֐�
 *
 *	@param	blact_w		�r���{�[�h���[�N
 *	@param	header		�w�b�_�[
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void data_chg_norm_anm_core(BLACT_WORK* blact_w, const BLACT_HEADER* header)
{
	// �e�N�X�`���A�j���[�V�����f�[�^��ݒ�
	blact_w->texAnm = header->texanm;

	// Vram�]���A�j���}�l�[�W����NULL��ݒ�
	blact_w->ItpVramObj = NULL;
}

//=============================================================================
//
//		�r���{�[�h�A�N�^�[���[�N����֐��S
//
//		�r���{�[�h�A�N�^�[�@�X�𑀍삷��
//
//=============================================================================
//-----------------------------------------------------------------------------
/**
 *
 *	@brief	�r���{�[�h�A�N�^�[�̒ǉ�
 *
 *	@param	add		�r���{�[�h�A�N�^�[�o�^�f�[�^
 *
 *	@retval BLACT_WORK_PTR	�o�^�������[�N�̃|�C���^
 *	@retval	NULL			���s
 *	
 */
//-----------------------------------------------------------------------------
BLACT_WORK_PTR BLACT_Add(const BLACT_ADD* add)
{
	BLACT_WORK*	bl_w;		// �o�^����r���{�[�h���[�N
	BLACT_SET*	bs;			// �r���{�[�h�A�N�^�[�Z�b�g

	// �r���{�[�h�A�N�^�[�Z�b�g�擾
	if(add->blact_s == NULL){
		return NULL;
	}

	bs = add->blact_s;

	// �X�^�b�N����擾
	bl_w = popStack(bs);
	if(bl_w == NULL){
		return NULL;
	}

	// �r���{�[�h�A�N�^�[����\���̔z��Ƀf�[�^��o�^
	bl_w->pBlActSet	= bs;					// �A�N�^�[�Z�b�g
	bl_w->Matrix	= add->matrix;			// ���΍��W
	bl_w->Scale		= add->scale;			// �g�k
	bl_w->AnmOffs	= 0;					// ���̃A�j���[�V�����I�t�Z�b�g
	bl_w->draw		= 1;					// �\��

	// �t���O�����������ɂ���
	bl_w->flag = BLACT_MOVE_INIT;	// ��������

	// �����ł̓ǂݍ��݂͂ł��Ȃ��̂ŃA�j���[�V�����Z�b�g�`�F���W�V�X�e���ɗ���
	chgBillboadAnmSet_Core( bl_w, add->pHeader );
	

	return bl_w;
}

//-----------------------------------------------------------------------------
/**
 *
 *	@brief	�r���{�[�h�A�N�^�[�̍폜
 *
 *	@param	del		�j������r���{�[�h�A�N�^�[����\����
 *
 *	@retval	TRUE	����(BOOL�^�F�폜�ɐ���������)
 *	@retval	FALSE	���s
 *
 */
//-----------------------------------------------------------------------------
BOOL BLACT_Delete(BLACT_WORK* del)
{
	BLACT_SET* as;	// �A�N�^�[�Z�b�g

	GF_ASSERT(del);

	// �������������ɒ����ɔj�����ꂽ�Ƃ��̓A�T�[�g���o��
	GF_ASSERT_MSG(del->flag != BLACT_MOVE_INIT,
			"���������Ē����̔j���͏o���܂���B");		

	as = (BLACT_SET*)del->pBlActSet;		// �A�N�^�[�Z�b�g���
	

	// �f�[�^������̂��`�F�b�N
	if( (del->flag == BLACT_MOVE_NONE) ){
		return FALSE;
	}

	// ���X�g����j��
	remList(del);

	// Vram�]�����[�h�̎���
	// �r���{�[�h�A�N�^�[��VramKey���擾���Ă���̂�
	// �e�N�X�`�����
	if( del->flag == BLACT_MOVE_VRAM ){
		delBindTexture(&(del->texKey), &(del->tex4x4Key), &(del->plttKey));
	}
	
	// ���܂ł̃f�[�^��j��	
	// ���f�����\�[�X�����
	del_blact(as, del);
	
	// �X�^�b�N�Ƀv�b�V��
	pushStack(as, del);

	// �j���������A���̕`��܂ł͎c���Ă���
	as->DelObjDrawRef = BLACT_DRAW_REF_DRAW_BEFORE;

	return TRUE;
}

//----------------------------------------------------------------------------
/**
 *
 * 
 *	@brief	�풓�A�j���p�@�r���{�[�h�A�N�^�[�w�b�_�[�f�[�^�쐬�x���֐�
 *
 *	@param	p_header		�r���{�[�h�A�N�^�[�w�b�_�[�f�[�^�i�[��
 *	@param	p_imd			�r���{�[�h���f�����\�[�X
 *	@param	cp_itx			�A�j���[�V�����e�N�X�`�����\�[�X
 *	@param	cp_anm			�A�j���[�V�����e�[�u��
 *	@param	cp_texanm		�e�N�X�`���A�j���[�V�����f�[�^�e�[�u��
 *	@param	texkey			�e�N�X�`���L�[
 *	@param	tex4x4key		4x4���k�e�N�X�`���L�[
 *	@param	plttkey			�p���b�g�L�[
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void BLACT_MakeHeaderNormalAnm( BLACT_HEADER* p_header, void* p_imd, const NNSG3dResTex* cp_itx, const BLACT_ANIME_TBL* cp_anm, const TEXANM_DATATBL* cp_texanm, NNSGfdTexKey texkey, NNSGfdTexKey tex4x4key, NNSGfdPlttKey plttkey  )
{
	p_header->ImdRes	= p_imd;
	p_header->ItxRes	= cp_itx;
	p_header->anm		= cp_anm;
	p_header->texanm	= *cp_texanm;
	p_header->texKey	= texkey;
	p_header->tex4x4Key	= tex4x4key;
	p_header->plttKey	= plttkey;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	Vram�]���A�j���p�@�r���{�[�h�A�N�^�[�w�b�_�[�f�[�^�쐬�x���֐�
 *
 *	@param	p_header		�r���{�[�h�A�N�^�[�w�b�_�[�f�[�^�i�[��
 *	@param	p_imd			�r���{�[�h���f�����\�[�X
 *	@param	cp_itx			�A�j���[�V�����e�N�X�`�����\�[�X
 *	@param	cp_anm			�A�j���[�V�����e�[�u��
 *	@param	cp_texanm		�e�N�X�`���A�j���[�V�����f�[�^�e�[�u��
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void BLACT_MakeHeaderVramAnm( BLACT_HEADER* p_header, void* p_imd, const NNSG3dResTex* cp_itx, const BLACT_ANIME_TBL* cp_anm, const TEXANM_DATATBL* cp_texanm )
{
	p_header->ImdRes	= p_imd;
	p_header->ItxRes	= cp_itx;
	p_header->anm		= cp_anm;
	p_header->texanm	= *cp_texanm;
	p_header->texKey	= BLACT_TEXKEY_VRAMANM;
	p_header->tex4x4Key	= BLACT_TEXKEY_VRAMANM;
	p_header->plttKey	= BLACT_PLTTKEY_VRAMANM;
}


//----------------------------------------------------------------------------
/**
 *
 *@brief	���W��ݒ�
 *
 *@param	act		�ݒ肷��A�N�^�[
 *@param	mat		�ݒ肷����W
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void BLACT_MatrixSet(BLACT_WORK_PTR act, const VecFx32* mat)
{
	GF_ASSERT(act);
	act->Matrix = *mat;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	���W���擾
 *
 *@param	act		�擾����A�N�^�[
 * 
 *@return	const VecFx32*	���W
 *
 */
//-----------------------------------------------------------------------------
const VecFx32* BLACT_MatrixGet(CONST_BLACT_WORK_PTR act)
{
	GF_ASSERT(act);
	return &act->Matrix;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�g��l��ݒ肷��
 *
 *@param	act		�ݒ肷��A�N�^�[
 *@param	sca		�ݒ肷��g��l
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void BLACT_ScaleSet(BLACT_WORK_PTR act, const VecFx32* sca)
{
	GF_ASSERT(act);

	act->Scale = *sca;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�g��l���擾����
 *
 *@param	act		�擾����A�N�^�[
 *
 *@return	const VecFx32*	�g��l
 *
 *
 */
//-----------------------------------------------------------------------------
const VecFx32* BLACT_ScaleGet(CONST_BLACT_WORK_PTR act)
{
	GF_ASSERT(act);
	return &act->Scale;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�`��t���O��ݒ肷��
 *
 *@param	act		�ݒ肷��A�N�^�[
 *@param	flag	�`��t���O	1:�`��	0:��`��
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void BLACT_ObjDrawFlagSet(BLACT_WORK_PTR act, u8 flag)
{
	GF_ASSERT(act);

	act->draw = flag;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�`��t���O���擾����
 *
 *@param	act		�擾����A�N�^�[
 *
 *@return	u8		1:�`��	0:��`��
 *
 *
 */
//-----------------------------------------------------------------------------
u8 BLACT_ObjDrawFlagGet(CONST_BLACT_WORK_PTR act)
{
	GF_ASSERT(act);
	return act->draw;
}

//-----------------------------------------------------------------------------
/**
 *
 *	@brief	�A�j���[�V������ς���
 *			�����ł̓^�X�N�Ƀf�[�^���Z�b�g���邾���ł��B
 *
 *							
 *	@param	act			�`�F���W���铮��z��
 *	@param	header		�`�F���W����A�j���[�V�����w�b�_�[
 *
 *	@return none
 *
 *	�E�o�^���Ă܂�BLACT_AfterDrawSys��ʂ��Ă��Ȃ��A�N�^�[�ɂ͎g�p�ł��܂���
 *	�E���ۂ̕ύX������BLACT_AfterDrawSys�֐��ōs���܂��B
 * 
 */
//-----------------------------------------------------------------------------
void BLACT_AnmSetChg( BLACT_WORK* act, const BLACT_HEADER* header )
{
	GF_ASSERT(act);
	
	// �A�j���[�V�����Z�b�g��ύX
	chgBillboadAnmSet_Core( act, header );
}

//-----------------------------------------------------------------------------
/**
 *
 *@brief	�A�j���[�V�����I�t�Z�b�g��ύX
 *
 *@param	act		�`�F���W���铮��z��
 *@param	num		�Z�b�g����A�j���[�V�����I�t�Z�b�g�i���o�[
 *
 *@return	none
 *
 */
//-----------------------------------------------------------------------------
void BLACT_AnmOffsChg( BLACT_WORK_PTR act, int num )
{
	GF_ASSERT(act);

	// �A�j���[�V�����I�t�Z�b�g��������
	act->AnmOffs = num;
}


//-----------------------------------------------------------------------------
/**
 *
 *@brief	�A�j���[�V�����I�t�Z�b�g��ύX�Ɠ����ɕύX����ʂɔ��f
 *
 *@param	act		�`�F���W���铮��z��
 *@param	num		�Z�b�g����A�j���[�V�����I�t�Z�b�g�i���o�[
 *
 *@return	none
 *
 */
//-----------------------------------------------------------------------------
void BLACT_AnmOffsChgRef( BLACT_WORK_PTR act, int num )
{
	BLACT_AnmOffsChg( act, num );
	BLACT_AnmFrameChg( act, FX32_ONE );	// ���f
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�A�j���[�V�����I�t�Z�b�g���擾
 *
 *@param	act		�擾����A�N�^�[
 *
 *@return	int		�A�j���[�V�����I�t�Z�b�g
 *
 *
 */
//-----------------------------------------------------------------------------
int BLACT_AnmOffsGet( CONST_BLACT_WORK_PTR act )
{
	GF_ASSERT(act);
	
	// �Ȃ��̂ŁA���̃A�j���[�V�����Z�b�g�i���o�[��Ԃ�
	return act->AnmOffs;
}

//----------------------------------------------------------------------------
/**
 *@brief	�A�j���[�V�����t���[���𓮂���
 *						���ۂɃA�j���[�V���������[�v�Đ�����Ƃ��Ɏg�p����
 *
 *@param	act		�A�j���[�V���������铮��z��
 *@param	num		�A�j���[�V�����X�s�[�h
 *
 *@retval	BLACT_ANISTA_LOOP	�Đ���
 *@retval	BLACT_ANISTA_END	�Đ��I��
 */
//-----------------------------------------------------------------------------
int BLACT_AnmFrameChg( BLACT_WORK* act, fx32 num )
{
	GF_ASSERT(act);

	return anmFrameChg_Core( act, num );
}

//----------------------------------------------------------------------------
/**
 *@brief	�A�j���[�V�����t���[������ݒ�
 *
 *@param	act		�A�j���[�V���������铮��z��
 *@param	num		�ݒ肷��t���[����
 *
 *@return	none
 */
//-----------------------------------------------------------------------------
void BLACT_AnmFrameSet( BLACT_WORK_PTR act, fx32 num )
{
	GF_ASSERT(act);
	act->frame = num;
}

//----------------------------------------------------------------------------
/**
 *@brief	�A�j���[�V�����t���[�������擾
 *
 *@param	act		�A�j���[�V���������铮��z��
 *
 *@return	fx32	�A�j���[�V�����t���[����
 */
//-----------------------------------------------------------------------------
fx32 BLACT_AnmFrameGet( CONST_BLACT_WORK_PTR act )
{
	GF_ASSERT(act);
	
	// �A�j���[�V�����I�u�W�F�N�g�̃A�j���[�V�����t���[���̒l��Ԃ�
	return act->frame;
}

//----------------------------------------------------------------------------
/**
 *@brief	���݂̃I�t�Z�b�g�J�n�t���[������̃A�j���[�V�����t���[�������Z�b�g
 *
 *@param	act		�A�j���[�V���������铮��z��
 *@param	num		�A�j���[�V�����X�s�[�h
 *
 *@return	none
 *
 *	�A�j���[�V�����I�t�Z�b�g�̊J�n�t���[��+num�̃t���[�����Z�b�g���܂��B
 *	���A�j���Ȃ獶�A�j���̊J�n�t���[��+num�̃t���[�����Z�b�g����܂��B 
 */
//-----------------------------------------------------------------------------
void BLACT_AnmFrameSetOffs( BLACT_WORK* act, fx32 num )
{
	GF_ASSERT(act);

	// �A�j���[�V�����I�u�W�F�N�g�̃A�j���[�V�����t���[���̒l���Z�b�g
	act->frame = nowOffsAnmStartFrame(act, act->AnmOffs);
	act->frame += num;
}

//----------------------------------------------------------------------------
/**
 *@brief	���݂̃I�t�Z�b�g�J�n�t���[������̃A�j���[�V�����t���[�������擾
 *
 *@param	act		�A�j���[�V���������铮��z��
 *
 *@return	fx32	�A�j���[�V�����t���[����
 *	���t���[���� - ���݂̃A�j���[�V�����I�t�Z�b�g�J�n�t���[���̒l��Ԃ��܂�
 */
//-----------------------------------------------------------------------------
fx32 BLACT_AnmFrameGetOffs( CONST_BLACT_WORK_PTR act )
{
	GF_ASSERT(act);
	
	// �A�j���[�V�����I�u�W�F�N�g�̃A�j���[�V�����t���[���̒l��Ԃ�
	return act->frame - nowOffsAnmStartFrame(act, act->AnmOffs);
}

//----------------------------------------------------------------------------
/**
 *	@brief	ID�̃r���{�[�h���f�����\�[�X���擾
 *
 *	@param	pDat		���f�����\�[�X���擾�������r���{�[�h�A�N�^�[���[�N
 *
 *	@return NNSG3dResMdl* ���f�����\�[�X
 *
 */
//-----------------------------------------------------------------------------
NNSG3dResMdl* BLACT_MdlResGet(CONST_BLACT_WORK_PTR pDat)
{
	GF_ASSERT( pDat );
	
	return pDat->pModel;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�r���{�[�h�A�N�^�[���[�N�̃|�C���^���擾
 *
 *	@param	set			�r���{�[�h�A�N�^�[�Z�b�g 
 *	@param	num			�r���{�[�h�A�N�^�[���[�N�C���f�b�N�X
 *
 *	@retval BLACT_WORK_PTR	�r���{�[�h�A�N�^�[���[�N
 *	@retval	NULL			���̃C���f�b�N�X�̃��[�N�͖���
 *
 */
//-----------------------------------------------------------------------------
BLACT_WORK_PTR BLACT_WorkGet(CONST_BLACT_SET_PTR set, int num)
{
	GF_ASSERT( set );

	return &set->pWork[num];
}


//----------------------------------------------------------------------------
/**
 *
 *	@brief	���݃r���{�[�h�A�N�^�[���[�N�͂ǂ�ȓ�����s���Ă��邩���擾
 *
 *	@param	act		�r���{�[�h�A�N�^�[���[�N
 *
 *	@retval	BLACT_MOVE_NONE			���삵�Ă��Ȃ�
 *	@retval BLACT_MOVE_INIT			��������
 *	@retval	BLACT_MOVE_VRAM			Vram�]���ғ���
 *	@retval	BLACT_MOVE_NORM			�풓�A�j���ғ���
 *
 */
//-----------------------------------------------------------------------------
int BLACT_GetState( CONST_BLACT_WORK_PTR act )
{
	GF_ASSERT(act);
	return act->flag;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�e�N�X�`���L�[�̎擾
 *
 *	@param	act �r���{�[�h�A�N�^�[���[�N
 *
 *	@return	�e�N�X�`���L�[
 *
 *
 */
//-----------------------------------------------------------------------------
NNSGfdTexKey BLACT_GetTexKey( CONST_BLACT_WORK_PTR act )
{
	GF_ASSERT( act );
	return act->texKey;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�p���b�g�L�[�̎擾
 *
 *	@param	act �r���{�[�h�A�N�^�[���[�N
 *
 *	@return	�p���b�g�L�[
 *
 *
 */
//-----------------------------------------------------------------------------
NNSGfdPlttKey BLACT_GetPlttKey( CONST_BLACT_WORK_PTR act )
{
	GF_ASSERT( act );
	return act->plttKey;
}

//----------------------------------------------------------------------------
/**
 * ���풓�A�j���[�V�����p
 *
 *	@brief	�e�N�X�`���L�[��ݒ肷��
 *
 *	@param	act		�r���{�[�h�A�N�^�[���[�N
 *	@param	texkey	�ݒ肷��e�N�X�`���L�[
 *
 *	@retval	TRUE	�ݒ萬��
 *	@retval	FALSE	�ݒ莸�s	�iVram�]���A�j���ł͎g�p���邱�Ƃ��o���Ȃ��ł��j
 *
 *	����ɂ��O���t�B�b�N�f�[�^��ύX���邱�Ƃ��o���܂��B
 *	�������A���̃O���t�B�b�N�f�[�^�ƃe�N�X�`���̍\���i�T�C�Y�j��
 *	�����łȂ��Ƃ����Ƃ����G���ł܂���B
 *
 *	�ݒ肵��texKey�̉���͊O���ŊǗ����Ă��������B
 *
 */
//-----------------------------------------------------------------------------
BOOL BLACT_SetTexKey( BLACT_WORK_PTR act, const NNSGfdTexKey* texKey )
{
	GF_ASSERT( act );
	GF_ASSERT( texKey );

	if( act->flag == BLACT_MOVE_NORM ){
		act->texKey = *texKey;
		return TRUE;
	}

	return FALSE;
}

//----------------------------------------------------------------------------
/**
 * ���풓�A�j���[�V�����p
 *
 *	@brief	�p���b�g�L�[��ݒ肷��
 *
 *	@param	act		�r���{�[�h�A�N�^�[���[�N
 *	@param	plttkey	�ݒ肷��p���b�g�L�[
 *
 *	@retval	TRUE	�ݒ萬��
 *	@retval	FALSE	�ݒ莸�s	�iVram�]���A�j���ł͎g�p���邱�Ƃ��o���Ȃ��ł��j
 *
 *	����ɂ��p���b�g��ύX���邱�Ƃ��o���܂��B
 *	�������A���̃p���b�g�f�[�^�ƃp���b�g�̍\���i�T�C�Y�j��
 *	�����łȂ��Ƃ����Ƃ����G���ł܂���B
 *
 *	�ݒ肵��plttKey�̉���͊O���ŊǗ����Ă��������B
 *
 */
//-----------------------------------------------------------------------------
BOOL BLACT_SetPlttKey( BLACT_WORK_PTR act, const NNSGfdPlttKey* plttKey )
{
	GF_ASSERT( act );
	GF_ASSERT( plttKey );

	if( act->flag == BLACT_MOVE_NORM ){
		act->plttKey = *plttKey;
		return TRUE;
	}

	return FALSE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�r���{�[�h�A�N�^�[�̃J�����O�`�F�b�N
 *
 *	@param	act		�A�N�^�[
 *
 *	@return	u32
 */
//-----------------------------------------------------------------------------
u32 BLACT_CullingCheck( BLACT_WORK_PTR act )
{
	MtxFx33 rot;
	
	//�@��]�s�񏉊���
	MTX_Identity33( &rot );
	
	return BB_CullingCheck3DModel( act->pModel, &act->Matrix, &rot, &act->Scale );
}


//----------------------------------------------------------------------------
/**
 *	@brief	Vram�]���������A�]�����N�G�X�g
 *	@param	act		�A�N�^�[
 */
//-----------------------------------------------------------------------------
void BLACT_VramAnmTransUserReq( BLACT_WORK_PTR act )
{
	if(act->flag == BLACT_MOVE_VRAM){
		// Vram�]�����s(Vram�]�����[�h�̂Ƃ��̂�)
		transItpVramAnm(act->ItpVramObj, act->frame);
	}
}


//=============================================================================
//
//		�v���C�x�[�g�֐��S
//
//=============================================================================
//-------------------------------------
//	�풓�A�j���p�V�X�e��
//=====================================
//----------------------------------------------------------------------------
/**
 *
 *	@brief	�e�N�X�`���E�p���b�g�Q�ƃA�h���X��ݒ�
 *
 *	@param	act		�r���{�[�h�A�N�^�[�f�[�^
 *
 *	@return	none
 *
 * (���f���Ƀe�N�X�`�����o�C���h����Ă���K�v������܂�)
 *
 */
//-----------------------------------------------------------------------------
static void normAnmTexDataSet( BLACT_WORK* act )
{
	TEXANM_DATA	texdata;		// ���݃t���[���̃e�N�X�`���C���f�b�N�X�@�p���b�g�C���f�b�N�X

	// ���݂̃t���[���̃e�N�X�`���E�p���b�g�C���f�b�N�X�擾
	texdata = TEXANM_GetFrameData( &act->texAnm, act->frame >> FX32_SHIFT );

	// �e�N�X�`���A�h���X�ݒ�
	// tex_idx�̃e�N�X�`����Vram�A�h���X�����f���̃}�e���A���f�[�^�ɐݒ�
	normAnmTexParamSet( act->pModel, act->pAnmTex, texdata.tex_idx );

	// �p���b�g�A�h���X�ݒ�
	// pltt_idx�̃p���b�g��Vram�A�h���X�����f���̃}�e���A���f�[�^�ɐݒ�
	normAnmPlttParamSet( act->pModel, act->pAnmTex, texdata.pltt_idx );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	���f�����̃o�C���h�f�[�^�S���@�e�N�X�`���C���f�b�N�X�̃e�N�X�`����Vram�A�h���X��ݒ肷��
 *
 *	@param	p_mdl		���f���f�[�^
 *	@param	p_tex		�e�N�X�`�����\�[�X�f�[�^
 *	@param	tex_idx		�e�N�X�`���C���f�b�N�X
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void normAnmTexParamSet( NNSG3dResMdl* p_mdl, const NNSG3dResTex* p_tex, u8 tex_idx )
{
	NNSG3dResMat*  mat;
    const NNSG3dResDict* dict_tex;
	const NNSG3dResDictTexToMatIdxData* data;
	const NNSG3dResDictTexData* texdict_data;
	u32	tex_offs;			// �e�N�X�`���̃I�t�Z�b�g�i���o�[
	int i;

	// �K�v�ȃ}�e���A���f�[�^
	// �e�N�X�`���o�C���h�p�}�e���A���񎫏����擾
    mat     = NNS_G3dGetMat(p_mdl);
    dict_tex = (NNSG3dResDict*)((u8*)mat + mat->ofsDictTexToMatList);

	// �e�N�X�`���I�t�Z�b�g���e�N�X�`�����\�[�X��������擾
	texdict_data = NNS_G3dGetTexDataByIdx( p_tex, tex_idx );
	tex_offs = (texdict_data->texImageParam & NNS_G3D_TEXIMAGE_PARAM_TEX_ADDR_MASK);
    
    // ���f�����\�[�X�̃e�N�X�`����->�}�e���A���C���f�b�N�X�񎫏�����
    // ���ꂼ��ɑ΂��ă��[�v����
    for (i = 0; i < dict_tex->numEntry; ++i){

		// i�Ԗڂ̃e�N�X�`���Ɋւ���o�C���h�f�[�^���擾
		data = (NNSG3dResDictTexToMatIdxData*) NNS_G3dGetResDataByIdx(dict_tex, i);

		// �o�C���h���ꂽ��Ԃ̂Ƃ��̂�
		// �e�N�X�`���A�h���X��ݒ�
		if ((data->flag & 1)){
			
			// �o�C���h����Ă���Ƃ��̓��f���f�[�^���̃}�e���A���[��TexImageParam�̒���VramKey�A�h���X�������Ă���
			normAnmTexParamSetOneMatData(mat, data, tex_offs );
		}
    }
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�o�C���h�����̃}�e���A���f�[�^�����@�e�N�X�`���C���f�b�N�X�̃e�N�X�`��Vram�A�h���X��ݒ肷��
 *
 *	@param	pMat			�}�e���A���f�[�^�S
 *	@param	pBindData		�o�C���h���
 *	@param	tex_offs		�e�N�X�`���I�t�Z�b�g
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void normAnmTexParamSetOneMatData( NNSG3dResMat* pMat, const	NNSG3dResDictTexToMatIdxData* pBindData, u32 tex_offs )
{
	u8* p_matidx;	// �}�e���A���f�[�^�C���f�b�N�X�z��
	int i;			// ���[�v�p
	NNSG3dResMatData* mat_data;	// �}�e���A���f�[�^

	// �}�e���A���f�[�^�C���f�b�N�X�z��擾
	p_matidx = (u8*)pMat + pBindData->offset;
	
	// �}�e���A���f�[�^���e�N�X�`���A�h���X��ݒ�
    for (i = 0; i < pBindData->numIdx; i++){
		
        // �emat_data�Ƀe�N�X�`�������Z�b�g�A�b�v���Ă����B
        mat_data = NNS_G3dGetMatDataByIdx(pMat, *(p_matidx + i));
		
		// �擪����̃I�t�Z�b�g�l��over�t���[���Ȃ����`�F�b�N
		GF_ASSERT( ((mat_data->texImageParam & NNS_G3D_TEXIMAGE_PARAM_TEX_ADDR_MASK) + tex_offs) <= NNS_G3D_TEXIMAGE_PARAM_TEX_ADDR_MASK );
		
        mat_data->texImageParam += tex_offs;
    }
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	���f�����̃o�C���h�f�[�^�S���@�p���b�g�A�h���X��ݒ肷��
 *
 *	@param	p_mdl		���f�����\�[�X
 *	@param	p_tex		�e�N�X�`�����\�[�X
 *	@param	pltt_idx	�p���b�g�f�[�^�C���f�b�N�X
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void normAnmPlttParamSet( NNSG3dResMdl* p_mdl, const NNSG3dResTex* p_tex, u8 pltt_idx )
{
    NNSG3dResMat*  mat;
    const NNSG3dResDict* dict_pltt;
	const NNSG3dResDictPlttToMatIdxData* data;
	const NNSG3dResDictPlttData* plttdict_data;
	u32	pltt_offs;			// �p���b�g�̃I�t�Z�b�g�i���o�[
    u32 i;

	// ���f���}�e���A���f�[�^�ɂ���p���b�g�o�C���h�f�[�^���擾
    mat      = NNS_G3dGetMat(p_mdl);
    dict_pltt = (NNSG3dResDict*)((u8*)mat + mat->ofsDictPlttToMatList);

	// �e�N�X�`���f�[�^����p���b�g�C���f�b�N�X�i���o�[��
	// ���̐擪����̃f�[�^�I�t�Z�b�g���擾
	// �I�t�Z�b�g�l��4bit�E�ɃV�t�g������Ԃœ����Ă��邪�A
	// 4�F�J���[�p���b�g�ȊO�̂Ƃ���3bit�E�V�t�g�����l�ɂ���K�v������
	plttdict_data = NNS_G3dGetPlttDataByIdx( p_tex, pltt_idx );
	pltt_offs = plttdict_data->offset;
	if( !(plttdict_data->flag & 1) ){		// 4�F�J���[�p���b�g�̎���1bit�������Ă���
		pltt_offs >>= 1;
	}

    for (i = 0; i < dict_pltt->numEntry; ++i){
		
		// �p���b�g�o�C���h�f�[�^�擾
		data = (NNSG3dResDictPlttToMatIdxData*) NNS_G3dGetResDataByIdx(dict_pltt, i);

		// �o�C���h����Ă���Ƃ��͕ύX
		if ((data->flag & 1)){
			
			// �o�C���h����Ă���Ƃ���PlttBase�̒���VramKey�A�h���X�������Ă���
			normAnmPlttParamSetOneMatData( mat, data, pltt_offs );
		}
    }
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�o�C���h�f�[�^���̃}�e���A���f�[�^�����p���b�g�I�t�Z�b�g��ݒ�
 *
 *	@param	pMat			�}�e���A���f�[�^�S
 *	@param	pBindData		�o�C���h���
 *	@param	pltt_offs		�p���b�g�I�t�Z�b�g 
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void normAnmPlttParamSetOneMatData( NNSG3dResMat* pMat, const NNSG3dResDictPlttToMatIdxData* pBindData, u32 pltt_offs )
{
    u8* matdata_idx;
    u32 i;

	// �}�e���A���f�[�^�C���f�b�N�X�z��擾
    matdata_idx = (u8*)pMat + pBindData->offset;
	
	// �o�C���h���̃f�[�^����
	// �}�e���A���f�[�^�̃p���b�g�A�h���X��ݒ�
    for (i = 0; i < pBindData->numIdx; i++) {
        // �ematData�Ƀp���b�g�����Z�b�g�A�b�v���Ă����B
        NNSG3dResMatData* matData = NNS_G3dGetMatDataByIdx(pMat, *(matdata_idx + i));
		
		// over�t���[���Ȃ����`�F�b�N
		GF_ASSERT( ((matData->texPlttBase & BLACT_PLTT_BASE_MASK) + pltt_offs) <= BLACT_PLTT_BASE_MASK );
		
        matData->texPlttBase += pltt_offs;
    }
}


//-------------------------------------
//	stack�̏���
//=====================================
//-----------------------------------------------------------------------------
/**
 *
 *	@brief	�X�^�b�N������
 *
 *	@param	pSet		�X�^�b�N�f�[�^�i�[��
 *	@return none
 *
 */
//-----------------------------------------------------------------------------
static void initStack(BLACT_SET* pSet)
{
	int i;

	// ������
	for (i=0; i<pSet->WorkNum; i++) {
		BLACT_WorkClear(&pSet->pWork[i]);
		pSet->ppWorkStack[i] = pSet->pWork + i;
	}
	pSet->WorkStackNow = 0;
}

//-----------------------------------------------------------------------------
/**
 *
 *	@brief	�X�^�b�N������o��
 *
 *	@param	pSet		�X�^�b�N�f�[�^�i�[��
 *	
 *	@retval	NULL�ȊO	�r���{�[�h���[�N
 *	@retval	NULL		���o���Ɏ��s�i�X�^�b�N���󂾂����ꍇ�j
 *
 */
//-----------------------------------------------------------------------------
static BLACT_WORK* popStack(BLACT_SET* pSet)
{
	BLACT_WORK*	ret;

	// ���~�b�g�`�F�b�N
	if(pSet->WorkStackNow >= pSet->WorkNum){
		return NULL;
	}

	ret = pSet->ppWorkStack[pSet->WorkStackNow];
	pSet->WorkStackNow++;

	return ret;
}

//-----------------------------------------------------------------------------
/**
 *
 *	@brief	�X�^�b�N�Ɋi�[
 *
 *	@param	pSet		�X�^�b�N�f�[�^�i�[��
 *	@param	pDat		�i�[�f�[�^
 *	
 *	@retval	TRUE		����
 *	@retval	FALSE		�X�^�b�N�����ς�
 */
//-----------------------------------------------------------------------------
static BOOL pushStack(BLACT_SET* pSet, BLACT_WORK* pDat)
{
	if(pSet->WorkStackNow <= 0){	// �󂫃`�F�b�N
		return FALSE;
	}
	BLACT_WorkClear(pDat);
	pSet->WorkStackNow--;
	pSet->ppWorkStack[pSet->WorkStackNow] = pDat;

	return TRUE;
}

//-------------------------------------
//	���X�g�Ǘ�
//=====================================
//-----------------------------------------------------------------------------
/**
 *
 *	@brief	���X�g�ɐݒ�
 *
 *	@param	pDummy		�擪�f�[�^
 *	@param	pDat		�ݒ�f�[�^
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void setList(BLACT_WORK* pDummy, BLACT_WORK* pDat)
{
	pDat->prev				= pDummy->prev;
	pDummy->prev->next		= pDat;
	pDat->next				= pDummy;
	pDummy->prev			= pDat;
}

static void remList(BLACT_WORK* pDat)
{
	// ���X�g���O��
	pDat->prev->next = pDat->next;
	pDat->next->prev = pDat->prev;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	���f�����\�[�X���擾����
 *
 *@param	bl_s		�r���{�[�h�A�N�^�[�Z�b�g
 *@param	p_head		�w�b�_�[
 *@param	num			�A�j���[�V�����Z�b�g�i���o�[
 *@param	ppMdl		���f�����\�[�X
 *@param	ppTex		�e�N�X�`�����\�[�X�i�[�p
 *
 *@return	NNSG3dResMdlSet
 *
 *
 */
//-----------------------------------------------------------------------------
static NNSG3dResMdlSet* blact_getMdl(const BLACT_HEADER* p_head,NNSG3dResMdl** ppMdl, NNSG3dResTex** ppTex)
{
	void*				res;		// ���\�[�X
	NNSG3dResMdlSet*	mdl_set;		// ���f�����\�[�X

	// ���\�[�X�擾	
	res = getRes(p_head, BLACT_RES_MAN_MDL);

	// ���f���擾
	mdl_set = NNS_G3dGetMdlSet(res);
	*ppMdl = NNS_G3dGetMdlByIdx( mdl_set, 0 );

	if(ppTex){

		*ppTex = NNS_G3dGetTex( res );
	}

	return mdl_set;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�e�N�X�`�����\�[�X���擾����
 *
 *@param	bl_s		�r���{�[�h�A�N�^�[�Z�b�g
 *@param	p_head		�w�b�_�[
 *@param	num			�A�j���[�V�����Z�b�g�i���o�[
 *
 *@return	NNSG3dResMdl
 *
 *
 */
//-----------------------------------------------------------------------------
static NNSG3dResTex* blact_getTex(const BLACT_HEADER* p_head)
{
	NNSG3dResTex*	tex;		// �e�N�X�`�����\�[�X

	// ���\�[�X�f�[�^�擾
	tex = (NNSG3dResTex*)getRes(p_head, BLACT_RES_MAN_TEX);
	return tex;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�e�N�X�`���p�^�[���A�j���[�V�����̓ǂݍ���
 *
 *@param	bl_s			�r���{�[�h�A�N�^�[�Z�b�g
 *@param	p_head			�r���{�[�h�A�N�^�[�w�b�_�[
 *@param	anm_set			�A�j���[�V�����Z�b�g�i���o�[
 *@param	p_mdl			���f�����\�[�X�i�ǂݍ��ݍς݁j
 *@param	p_tex			�e�N�X�`�����\�[�X�i�ǂݍ��ݍς݁�NULL��Vram�]���p�j
 *@param	pAlloc			�g�p�A���P�[�^
 *
 *@return	NNSG3dResFileHeader*	�ǂݍ��񂾃A�j���[�V�������\�[�X
 *
 *
 */
//-----------------------------------------------------------------------------
static NNSG3dAnmObj* blact_getItp(const BLACT_HEADER* p_head, const NNSG3dResMdl* p_mdl, const NNSG3dResTex* p_tex, NNSFndAllocator* pAlloc)
{
	void*			res;		// ���\�[�X
	NNSG3dAnmObj*	anm;		// �A�j���[�V�����I�u�W�F
    NNSG3dResTexPatAnm* pAnmRes;// �A�j���[�V�������\�[�X

	// ���\�[�X�擾
	res = getRes(p_head, BLACT_RES_MAN_ANM);

	// �C���f�b�N�X���O�̃A�j���[�V�������w��
    pAnmRes = (NNSG3dResTexPatAnm*)NNS_G3dGetAnmByIdx(res, 0);

	// �K�v�ʂ̃��������A���P�[�g����B�C�j�V�����C�Y�͕ʓr�K�v�ɂȂ�B
    anm = NNS_G3dAllocAnmObj(pAlloc, // �g�p����A���P�[�^���w��
                            pAnmRes,    // �A�j���[�V�������\�[�X���w��
                            p_mdl);    // ���f�����\�[�X���w��


	//
    // AnmObj ������������B
    //
    NNS_G3dAnmObjInit(anm,		// �A�j���[�V�����I�u�W�F�N�g�ւ̃|�C���^
                      pAnmRes,	// �A�j�����\�[�X�ւ̃|�C���^
                      p_mdl,	// NNSG3dResMdl�ւ̃|�C���^
					  p_tex );	// NNSG3dResTex�ւ̃|�C���^
	return anm;
}

//-----------------------------------------------------------------------------
/**
 *	@brief	�A�j���[�V�����Z�b�g�ύX�i���ۂɏ�������֐��j
 *
 *  @param	act		�`�F���W���铮��z��
 *  @param	header	�w�b�_�[�f�[�^
 *
 *	@return none
 *
 *�����ł̓^�X�N�Ƀf�[�^���Z�b�g����	
 *			���ۂɓ���ւ���̂�V�u�����N��BLACT_VlBank()
 *
 */
//-----------------------------------------------------------------------------
static void chgBillboadAnmSet_Core( BLACT_WORK* act, const BLACT_HEADER* header )
{
	// �풓�A�j����Vram�]���A�j�����`�F�b�N
	if( header->texKey == BLACT_TEXKEY_VRAMANM ){
		
		// Vram�]��
		chgBillboadAnmSet_Core_VRAM( act, header );
	}else{

		// �풓�A�j��
		core_anmset_chg_norm( act, header );
	}
}


//----------------------------------------------------------------------------
/**
 *
 *	@brief	�I�t�Z�b�g�l�̎��̊J�n�t���[�����擾
 *
 *	@param	act		�擾����r���{�[�h�A�N�^�[
 *	@param	offs	�I�t�Z�b�g�l
 *
 *	@return	fx32	�J�n�t���[��
 *
 *
 */
//-----------------------------------------------------------------------------
static fx32	nowOffsAnmStartFrame( const BLACT_WORK* act, int offs )
{
	const BLACT_ANIME_TBL* p_anm_tbl;				// �A�j���[�V�����e�[�u��
	p_anm_tbl	= getAnmTbl( act->pAnmTbl,  offs );	// �A�j���[�V�����e�[�u��

	return p_anm_tbl->start << FX32_SHIFT;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�A�j���[�V�����t���[���ύX�@�ʏ펞�p
 *
 *	@param	act		�r���{�[�h�A�N�^�[���[�N
 *	@param	num		�ύX��
 *
 *	@retval	BLACT_ANISTA_LOOP	�Đ���
 *	@retval	BLACT_ANISTA_END	�Đ��I��
 *
 *
 */
//-----------------------------------------------------------------------------
static int anmFrameChg_Core( BLACT_WORK* act, fx32 num )
{
	const BLACT_ANIME_TBL* p_anm_tbl;	// �A�j���[�V�����e�[�u��

	p_anm_tbl	= getAnmTbl( act->pAnmTbl, act->AnmOffs );

	return anmFrameChgSys( p_anm_tbl, &act->frame, num );
}


//----------------------------------------------------------------------------
/**
 *
 *	@brief	�t���[���ύX�V�X�e��
 *
 *	@param	anm		�A�j���[�V�����e�[�u��
 *	@param	frame	�t���[�����̃|�C���^
 *	@param	num		�������t���[����
 *
 *	@retval	BLACT_ANISTA_LOOP	�Đ���
 *	@retval	BLACT_ANISTA_END	�Đ��I��
 *
 *
 */
//-----------------------------------------------------------------------------
static int anmFrameChgSys( const BLACT_ANIME_TBL* anm, fx32* frame, fx32 num )
{
	int ret = BLACT_ANISTA_LOOP;
	
	// �A�j���[�V�����f�[�^���̃t���[���Ń��[�v�Đ�
	// �����[�v�͈͓��ɂ��邩���`�F�b�N
	if( ((anm->start * FX32_ONE) > *frame) || 
		((anm->end * FX32_ONE) < *frame) ){

		// �͈͊O�Ȃ̂ŃA�j���[�V�����̃X�^�[�g�t���[���ɂ���
		*frame = (anm->start * FX32_ONE);
	}else{
		// �A�j���[�V�������������ʂ��͈͊O�ɂȂ�Ȃ����`�F�b�N
		if( ((anm->end * FX32_ONE) < *frame + num) ){
			
			if(anm->cmd == BLACT_ANIM_LOOP){
				// �͈͊O�ɂȂ�̂ŃX�^�[�g�t���[���ɂ���
				*frame = (anm->start * FX32_ONE);
			}else{

				ret = BLACT_ANISTA_END;
				*frame = (anm->end * FX32_ONE);
			}
		}else{
			// ���̃`�F�b�N�ɂ�������Ȃ�������A�j���[�V����������
			*frame += num;
		}
	}

	return ret;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�`��O����	�e�N�X�`���o�C���h
 *
 *@param	bl_w	�o�C���h���郏�[�N
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void DrawTexBind(BLACT_WORK* bl_w)
{
	// �e�N�X�`���o�C���h
	reBindTexture(bl_w->pMdlTex, bl_w->pModelSet, &bl_w->texKey, &bl_w->tex4x4Key, &bl_w->plttKey);
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�`��㏈��	�e�N�X�`�����o�C���h
 *
 *@param	bl_w	���o�C���h���郏�[�N
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void DrawTexreBind(BLACT_WORK* bl_w)
{
	NNSG3dTexKey tex4x4key;
	NNSG3dTexKey texkey;
	NNSG3dPlttKey plttkey;
	

	// �o�C���h��j��
	NNS_G3dReleaseMdlSet(bl_w->pModelSet);

	// �e�N�X�`����Vram�L�[�̃����N���͂���
	releaseTexture(bl_w->pMdlTex, &texkey, &tex4x4key, &plttkey);
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	���\�[�X�}�l�[�W���[���烊�\�[�X���擾����
 *
 *@param	p_head		�w�b�_�[	
 *@param	flag		�ǂ̃��\�[�X���̃t���O
 *
 *@return	void*		���\�[�X
 *
 *
 */
//-----------------------------------------------------------------------------
static void* getRes(const BLACT_HEADER* p_head, int flag)
{
	void* ret;

	switch(flag){
	case BLACT_RES_MAN_MDL:
		ret = p_head->ImdRes;
		break;
	
	case BLACT_RES_MAN_TEX:
		ret = (void*)p_head->ItxRes;
		break;
	
	default:
		ret = NULL;
		break;
	}
	
	return ret;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�A�j���[�V�����e�[�u�����w�b�_����擾
 *
 *	@param	p_head	�A�j���[�V�����e�[�u��
 *	@param	ofs		�I�t�Z�b�g
 *
 *	@return	�A�j���[�V�����e�[�u��
 *
 *
 */
//-----------------------------------------------------------------------------
static const BLACT_ANIME_TBL* getAnmTbl(const BLACT_ANIME_TBL* p_anm, int ofs)
{
	return (p_anm + ofs);
}
