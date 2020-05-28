//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *@file		clact.c
 *@brief	�Z���A�N�^�[
 *@author	tomoya takahashi
 *@data		2005.05.19
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
#define	_CLACT_H_GLOBAL
#include <string.h>
#include "clact.h"
#include "system.h"
#include "gflib_os_print.h"
#include "vram_transfer_manager.h"
#include "assert.h"

//
#include "char_manager.h"
#include "pltt_manager.h"
#include "str_tool.h"

//-----------------------------------------------------------------------------
/**
 *					�萔�錾
 */
//-----------------------------------------------------------------------------
#define PLTT_ONE_SIZE	(32)	
#define	SIMPLE_DRAW_OAM_TMP	(128)

// �A�g���r���[�g����
#define		CLACT_ATTR_PRIORITY_MASK	(0x0c00)			// �D��x�f�[�^�����o���}�X�N
#define		CLACT_ATTR_PRIORITY_SHIFT	(10)				// �D��x�f�[�^�̃V�t�g��

// �I�[�g�A�j���[�V�����t���[��
#define		CLACT_AUTO_ANM_FRAME		(FX32_ONE * 2)

// �A�j���[�V�����^�C�v�\���̂̍ő�T�C�Y(int��)
#define		CLACT_ANM_DATA_MAX			(29)		// �{���̃T�C�Y�͂��ꂘ�S

//-------------------------------------
///	�A�j���[�V�����^�C�v�\����
enum
{
	CLACT_NONE,			// �g�p���Ă��Ȃ�
	CLACT_CELL,			// �Z���A�j���[�V����
	CLACT_MULTICELL,	// �}���`�Z���A�j���[�V����
	CLACT_VRAM_CELL,	// �Z���A�j��Vram�]���A�j���[�V����
};

//-----------------------------------------------------------------------------
/**
 *					�\���̐錾
 */
//-----------------------------------------------------------------------------
//-------------------------------------
///	�Z���A�j���[�V�����\����	
typedef	struct CLACT_ANIM_DATA_tag
{
	const NNSG2dCellDataBank*             pCellBank;   // �Z���f�[�^
	const NNSG2dCellAnimBankData*         pAnimBank;   // �Z���A�j���[�V����

	NNSG2dCellAnimation				AnmCtrl;	// �A�j���[�V�����R���g���[��
} CLACT_ANIM_DATA;


//-------------------------------------
///	Vram�]���Z���A�j���[�V�����\����
typedef struct CLACT_VRAM_ANIM_DATA_tag
{
	NNSG2dCellDataBank*             pCellBank;   // �Z���f�[�^
	const NNSG2dCellAnimBankData*         pAnimBank;   // �Z���A�j���[�V����

	NNSG2dCellAnimation				AnmCtrl;	// �A�j���[�V�����R���g���[��

	u32								CellTransManHandle;	// �Z���A�j���[�V������Vram�]�����Ǘ�����
														// �Z���]����ԊǗ��I�u�W�F�N�g�̃n���h��
} CLACT_VRAM_ANIM_DATA;

//-------------------------------------
///	�}���`�Z���A�j���[�V�����\����	
typedef	struct CLACT_MULTICELL_ANIM_DATA_tag
{
	const NNSG2dCellDataBank*             pCellBank;	// �Z���f�[�^
    const NNSG2dCellAnimBankData*         pAnimBank;  // �Z���A�j���[�V����
	
	NNSG2dMultiCellAnimation		AnmCtrl;	// �A�j���[�V�����R���g���[��
	
	const NNSG2dMultiCellDataBank*        pMCBank;    // �}���`�Z���f�[�^
    const NNSG2dMultiCellAnimBankData*    pMCABank;   // �}���`�Z���A�j���[�V����
	NNSG2dNode*						pNode;		// �}���`�Z���ɕK�v�ȃm�[�h
	NNSG2dCellAnimation*			pCellAnim;	// �}���`�Z���ɕK�v�ȃA�j���[�V�����R���g���[��
	
} CLACT_MULTICELL_ANIM_DATA;


//-------------------------------------
///	�Z���A�N�^�[����\����
typedef struct CLACT_WORK_tag{
	VecFx32		Matrix;						// ���W
	VecFx32		AffineMatrix;				// �A�t�B���ϊ����W
	VecFx32		Scale;						// �X�P�[��
	u16			Rotation;					// ��]
	u8			affin;						// �A�t�B���A�{�p�A�t�B���t���O
	u8			flip;						// �t���b�v�t���O
	u8			over_write;					// �����_���[�I�[�o�[���C�g�t���O
	u8			palNo;						// �p���b�g�i���o�[
	u8			palOfs;						// �p���b�g�I�t�Z�b�g
	BOOL		mosaic;						// ���U�C�N
	GXOamMode	objmode;					// OBJ���[�h
		
	// �`���ރt���O
	u8			DrawFlag;	// 0:��`��		1:�����_���[�`��
	// �I�[�g�A�j���[�V�����t���O
	u8			AnmFlag;	// 0:��A�j��	1:�I�[�g�A�j��
	fx32		Frame;		// �A�j���[�V�����X�s�[�h
											
	
	CLACT_SET_PTR	pClActSet;		// �e�̃A�N�^�[�Z�b�g�̃|�C���^
	u32				AnmData[ CLACT_ANM_DATA_MAX ];	// �A�j���[�V�����f�[�^�\���́i�Z���A�j���[�V�����A�}���`�Z���A�j���[�V�����AVram�]���A�j���[�V�����e�\���̃f�[�^�@flag�̃A�j���[�V�����f�[�^�^�ɃL���X�g�����Ďg���j
	NNSG2dImageProxy        ImageProxy;		// �L�����N�^/�e�N�X�`���v���L�V
	NNSG2dImagePaletteProxy  PaletteProxy;	// �p���b�g�v���L�V
	u32			flag;						// �Z���A�j���[�V�����A�}���`�Z���A�j���[�V�����AVram�]���A�j���[�V�������̃t���O
	u16			AnmNum;						// �V�[�P���X�i���o�[�i���̃A�j���i���o�[�j
	u8			Priority;					// BG�ʂƂ̗D�揇��(0,1,2,3)
	u16			DrawPriority;				// �`��ł̗D�揇��(0=�őO��	1,2,3....)
	NNS_G2D_VRAM_TYPE	type;				// VramType �ǂ����ɕ`�悵�Ă��邩
	/*	typedef enum NNS_G2D_VRAM_TYPE
		{
			NNS_G2D_VRAM_TYPE_3DMAIN = 0,		// �X�v���C�g�͍��͎g��Ȃ��̂Ŏw�肵�Ȃ�
			NNS_G2D_VRAM_TYPE_2DMAIN = 1,
			NNS_G2D_VRAM_TYPE_2DSUB  = 2,
			NNS_G2D_VRAM_TYPE_MAX    = 3
		}NNS_G2D_VRAM_TYPE;
	 */
	// ���X�g�\��
	struct CLACT_WORK_tag*		pLast;		// �O�̃A�N�^�[
	struct CLACT_WORK_tag*		pNext;		// ���̃A�N�^�[
} CLACT_WORK;

//-------------------------------------
//
//	�Z���A�N�^�[�Z�b�g
//
//	�Z���A�N�^�[�V�X�e���̎���
//
//=====================================
typedef struct _CLACT_SET{
	CLACT_WORK*		pWork;			// �Z���A�N�^�[����\����
	int				WorkNum;		// �z��
	CLACT_WORK**	ppWorkStack;	// �X�^�b�N
	int				WorkStackNow;	// ���̃X�^�b�N��pop�ʒu
	
	CLACT_WORK	Dummy;	// �A�N�^�[���X�g�_�~�[�f�[�^
	
	// OAM�}�l�[�W���|�C���^
//	NNSG2dOamManagerInstance* pMainMan;
//	NNSG2dOamManagerInstance* pSubMan;
	
	
	// �����_���[
	NNSG2dRendererInstance*		pRender;			// �`��p Renderer

	// �f�t�H���g�A�j���[�V�����f�[�^
	void*							pAnimBuff;	// �o�b�t�@
    NNSG2dCellAnimBankData*         pAnimBank;  // �Z���A�j���[�V����

	u32			DrawFlag;		// 1:�\���@0:��\��
}CLACT_SET;

//-------------------------------------
//	
//	�`��֐��e�[�u���p
//	
//=====================================
typedef void (*CLACT_DRAW)( const CLACT_SET* pClActSet, CLACT_WORK* act );

//-------------------------------------
//	
//	�I�[�g�A�j���[�V�����֐��e�[�u���p
//	
//=====================================
typedef void (*CLACT_ANM)( CLACT_WORK* act );

//----------------------------------------------------------------------------
/**
 *					�v���g�^�C�v�錾
 */
//-----------------------------------------------------------------------------
//-------------------------------------
//	�Z���A�N�^�[�Z�b�g���샍�[�J���֐�
//=====================================
static void CleanActSet(CLACT_SET* pClAct);

//-------------------------------------
//	�Z���A�N�^�[���[�N�p
//=====================================
static u32	getActType( const CLACT_HEADER* pHeader );	// �Z���A�j�����A�}���`�Z���A�j������Ԃ�
static void LoadCell( const NNSG2dCellDataBank* Cell, CLACT_WORK* pWork );		// �Z����ǂݍ���
static void LoadCellAnm( const NNSG2dCellAnimBankData* Anm, CLACT_WORK* pWork );	// �Z���A�j����ǂݍ���
static void LoadMultiCell( const NNSG2dMultiCellDataBank* Mlt, CLACT_WORK* pWork );// �}���`�Z����ǂݍ���
static void LoadMultiCellAnm( const NNSG2dMultiCellAnimBankData* Anm, CLACT_WORK* pWork );// �}���`�Z���A�j����ǂݍ���
static void MakeCellAnm( CLACT_WORK* pWork, int heap );
static void MakeCellAnmVram( const CLACT_HEADER* pHeader, CLACT_WORK* pWork , int heap);
static void MakeMultiCellAnm( CLACT_WORK* pWork, int heap );							// �}���`�Z���A�j���̍\�z���s��
static BOOL LoadData( const CLACT_SET* pSet, const CLACT_HEADER* pHeader, CLACT_WORK* pWork, int heap );
static u32 GetPlttProxyOffset( const NNSG2dImagePaletteProxy* pPltt, u32 vramType );	// �p���b�g�����炷�l���擾
// �����_���[���g�p�������x�ȕ`��
static void renderDraw( const CLACT_SET* pClActSet, CLACT_WORK* act );
static void noDraw( const CLACT_SET* pClActSet, CLACT_WORK* act );

// �I�[�g�A�j���[�V����
static void autoAnm( CLACT_WORK* act );
static void noAnm( CLACT_WORK* act );

//-----------------------------------------------------------------------------
//				�A�N�^�[���X�g����
//				�`��D�揇�ʂŕ`�悷�邽��
//=============================================================================
static void addCellActList( CLACT_SET* cs, CLACT_WORK* pWork );		// ���X�g�ɒǉ�
static void dellCellActList( CLACT_WORK* pWork );	// ���X�g����j��(�������̈�̔j���͂��Ȃ�)
//-------------------------------------
//	stack�̏���
//=====================================
static void initStack(CLACT_SET* pSet);			// ������
static CLACT_WORK* popStack(CLACT_SET* pSet);	// ���o��
static BOOL pushStack(CLACT_SET* pSet, CLACT_WORK* pDat);	// �i�[
//=============================================================================
//----------------------------------------------------------------------------
/**
 *					�O���[�o���ϐ��錾
 */
//-----------------------------------------------------------------------------

//=============================================================================
//
//		�A�N�^�[�V�X�e������
//
//				�A�N�^�[�Z�b�g�쐬�O
//				�A�N�^�[�Z�b�g�j����
//				
//			�ɍs�������̊֐�
//
//=============================================================================
//=============================================================================
//
//	�A�N�^�[�Z�b�g����֐��S
//
//=============================================================================
//-----------------------------------------------------------------------------
/**
 *@brief			�Z���A�N�^�[�Z�b�g�̏�����
 *
 *@param	pSetData		�Z���A�N�^�[�Z�b�g�쐬�f�[�^
 *
 *@retval	CLACT_SET_PTR	�쐬�����Z���A�N�^�[�Z�b�g�|�C���^
 *@retval	NULL			���s
 *
 * �Z���A�N�^�[�Z�b�g���쐬
 *
 */
 //----------------------------------------------------------------------------
CLACT_SET_PTR CLACT_InitSet( const CLACT_SETDATA* pSetData )
{
	CLACT_SET*	cs;		// �Z���A�N�^�[�Z�b�g	
	int			idx;	// �Z���A�N�^�[�C���f�b�N�X
	
	GF_ASSERT(pSetData);
	GF_ASSERT(pSetData->pRender);
	
	// �A�N�^�[�Z�b�g�������m��
	cs = sys_AllocMemory(pSetData->heap, sizeof(CLACT_SET));
	GF_ASSERT(cs);
	CleanActSet(cs);
	
	// ���[�N�̍쐬
	cs->pWork = sys_AllocMemory(pSetData->heap, sizeof(CLACT_WORK)*pSetData->WorkNum);
	GF_ASSERT(cs->pWork);
	cs->WorkNum = pSetData->WorkNum;	// ���[�N��
	// �X�^�b�N�̏�����
	cs->ppWorkStack = sys_AllocMemory(pSetData->heap, sizeof(CLACT_WORK*)*pSetData->WorkNum);
	GF_ASSERT(cs->ppWorkStack);
	initStack(cs);
	
	// ���X�g�̃_�~�[�̏�����
	CLACT_WorkClear(&cs->Dummy);
	cs->Dummy.pLast = &cs->Dummy;
	cs->Dummy.pNext = &cs->Dummy;

	// OAM�}�l�[�W��
//	cs->pMainMan	= pSetData->pMainMan;
//	cs->pSubMan		= pSetData->pSubMan;
	
	// �����_���[ 
	cs->pRender = pSetData->pRender;

	// �f�t�H���g�A�j���f�[�^�ǂݍ���
	cs->pAnimBuff = sys_LoadFile( pSetData->heap, "data/clact_default.NANR" );
	NNS_G2dGetUnpackedAnimBank( cs->pAnimBuff, &cs->pAnimBank );

	// �`��t���O
	cs->DrawFlag = 1;

	return cs;
}

//-----------------------------------------------------------------------------
/**
 *@brief			�Z���A�N�^�[�Z�b�g�̔j��
 *
 *@param	ClActSet			�j������Z���A�N�^�[�Z�b�g�|�C���^
 *
 *@retval	TRUE	����
 *@retval	FALSE	���s	(ClActSet���ԈႢ)
 *
 * �Z���A�N�^�[�Z�b�g��j������
 *		���s���Ă����A�N�^�[�I�u�W�F����ĉ��
 *
 */
 //----------------------------------------------------------------------------
BOOL CLACT_DestSet( CLACT_SET_PTR ClActSet )
{	

	if(ClActSet == NULL){
		return FALSE;
	}

	if(ClActSet->pWork == NULL){	// �폜�ς݂��`�F�b�N
		return TRUE;
	}
	
	// �A�N�^�[�j��
	CLACT_DelAllSet(ClActSet);

	// �A�j���f�[�^�j��
	sys_FreeMemoryEz( ClActSet->pAnimBuff );
	
	// �X�^�b�N�j��
	sys_FreeMemoryEz(ClActSet->ppWorkStack);

	// ���[�N�j��
	sys_FreeMemoryEz(ClActSet->pWork);

	// �A�N�^�[�Z�b�g������
	CleanActSet(ClActSet);

	sys_FreeMemoryEz(ClActSet);
	ClActSet = NULL;

	return TRUE;
}

//-----------------------------------------------------------------------------
/**
 *@brief			�Z���A�N�^�[�Z�b�g�̕`��t���O��ݒ�
 *
 *@param	ClActSet			�j������Z���A�N�^�[�Z�b�g�|�C���^
 *@param	flag				0:��`��	1:�`��
 *
 *@retval	TRUE	����
 *@retval	FALSE	���s	(ClActSet���ԈႢ)
 *
 *	�o�^����Ă���r���{�[�h�S�Ă�`��/��`�悷�邩��ݒ�
 *
 */
 //----------------------------------------------------------------------------
BOOL CLACT_DrawFlagSet( CLACT_SET_PTR ClActSet, u8 flag )
{
	if(ClActSet == NULL){
		return FALSE;
	}

	if(ClActSet->pWork == NULL){	// �o�^���Ă��邩�`�F�b�N
		return FALSE;
	}

	ClActSet->DrawFlag = flag;

	return TRUE;
}

//-----------------------------------------------------------------------------
/**
 *@brief			�S�A�N�^�[�j��
 *
 *@param	ClActSet		�Z���A�N�^�[�Z�b�g�|�C���^
 *
 *@retval	TRUE	����
 *@retval	FALSE	���s	(ClActSet���ԈႢ)
 */
 //----------------------------------------------------------------------------
BOOL CLACT_DelAllSet( CLACT_SET_PTR ClActSet )
{
	CLACT_WORK*	p_work;		// ���[�v�p
	CLACT_WORK*	p_next;		// ����ۑ��p

	if(ClActSet == NULL){
		return FALSE;
	}
	
	if(ClActSet->pWork == NULL){	// �o�^���Ă��邩�`�F�b�N
		return TRUE;
	}
	
	// �j��
	p_work = ClActSet->Dummy.pNext;
	while(p_work != &ClActSet->Dummy){
		p_next = p_work->pNext;
		
		CLACT_Delete(p_work);

		p_work = p_next;
	}

	return TRUE;
}

//-----------------------------------------------------------------------------
/**
 *@brief				�`�悷��
 *
 *@param	pClActSys	�Z���A�N�^�[�V�X�e��
 *@param	pClAct		�Z���A�N�^�[�Z�b�g
 *
 *@return	none
 */
 //----------------------------------------------------------------------------
void CLACT_Draw( const CLACT_SET* pClAct )
{
	CLACT_WORK*	p_work;		// ���[�v�p
	// �`��֐��e�[�u��
	static const CLACT_DRAW	drawTbl[] = {
		noDraw,		// �`�悵�Ȃ�
		renderDraw,
	};
	
	// �I�[�g�A�j���[�V�����e�[�u��
	static const CLACT_ANM	anmTbl[] = {
		noAnm,
		autoAnm,	
	};

	GF_ASSERT( pClAct );
	
	if( pClAct->DrawFlag == 0 ){
		return ;
	}

	// �`�悷��
	p_work = pClAct->Dummy.pNext;
	while(p_work != &pClAct->Dummy){

		// �`��
		drawTbl[ p_work->DrawFlag ]( pClAct, p_work );

		// �I�[�g�A�j���[�V����
		anmTbl[ p_work->AnmFlag ]( p_work );
		
		p_work = p_work->pNext;
	}
}

#if 0
//----------------------------------------------------------------------------
/**
 *
 *@brief	�Z���A�N�^�[�Z�b�g�ɓo�^����Ă���OAM�}�l�[�W����OAM��]��
 *
 *@param	pClAct		�Z���A�N�^�[�Z�b�g
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void CLACT_OAMTrans( CLACT_SET_PTR pClAct )
{
	if(pClAct->pMainMan != NULL){
		NNS_G2dApplyOamManagerToHW(pClAct->pMainMan);
		NNS_G2dResetOamManagerBuffer(pClAct->pMainMan);
	}
	if(pClAct->pSubMan != NULL){
		NNS_G2dApplyOamManagerToHW(pClAct->pSubMan);
		NNS_G2dResetOamManagerBuffer(pClAct->pSubMan);
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�o�^����Ă���OAM�}�l�[�W�����擾
 *
 *@param	pClAct			�Z���A�N�^�[
 *@param	vramType		Vram�^�C�v	
					main	NNS_G2D_VRAM_TYPE_2DMAIN
					sub		NNS_G2D_VRAM_TYPE_2DSUB
 *
 *@retval	NNSG2dOamManagerInstance* OAM�}�l�[�W��
 *@retval	NULL						�ݒ肳��Ă��Ȃ�
 *
 *
 */
//-----------------------------------------------------------------------------
NNSG2dOamManagerInstance* CLACT_OAMManagerGet( CLACT_SET_PTR pClAct, int vramType )
{
	if(vramType == NNS_G2D_VRAM_TYPE_2DMAIN){
		return pClAct->pMainMan;
	}
	if(vramType == NNS_G2D_VRAM_TYPE_2DSUB){
		return pClAct->pSubMan;
	}

	return NULL;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	OAM�}�l�[�W����ݒ�
 *
 *@param	pClAct		�Z���A�N�^�[
 *@param	pOamMan		OAM�}�l�[�W��
 *@param	vramType	
				main�ɓo�^�FNNS_G2D_VRAM_TYPE_2DMAIN
				sub�ɓo�^ �FNNS_G2D_VRAM_TYPE_2DSUB
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void CLACT_OAMManagerSet( CLACT_SET_PTR pClAct, NNSG2dOamManagerInstance* pOamMan, int vramType )
{
	if(vramType == NNS_G2D_VRAM_TYPE_2DMAIN){
		pClAct->pMainMan = pOamMan;
	}
	if(vramType == NNS_G2D_VRAM_TYPE_2DSUB){
		pClAct->pSubMan = pOamMan;
	}
}
#endif

//----------------------------------------------------------------------------
/**
 *
 *@brief	�o�^����Ă��郌���_���[���擾
 *
 *@param	pClAct			�Z���A�N�^�[
 *
 *@retval	NNSG2dRendererInstance*		OAM�}�l�[�W��
 *@retval	NULL						�ݒ肳��Ă��Ȃ�
 *
 *
 */
//-----------------------------------------------------------------------------
NNSG2dRendererInstance* CLACT_RenderGet( CONST_CLACT_SET_PTR pClAct)
{
	return pClAct->pRender;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�����_���[��ݒ�
 *
 *@param	pClAct		�Z���A�N�^�[
 *@param	pRender		�����_���[
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void CLACT_RenderSet( CLACT_SET_PTR pClAct, NNSG2dRendererInstance* pRender)
{
	pClAct->pRender = pRender;
}

//-----------------------------------------------------------------------------
/**
 *@brief			�A�N�^�[�Z�b�g������
 *
 *@param	pClAct		�Z���A�N�^�[�Z�b�g
 *
 *@return	none
 */
 //----------------------------------------------------------------------------
static void CleanActSet(CLACT_SET* pClAct)
{
	pClAct->pWork		= NULL;		// �Z���A�N�^�[����\����
	pClAct->WorkNum		= 0;		// �z��
	pClAct->ppWorkStack	= NULL;		// �X�^�b�N
	pClAct->WorkStackNow= 0;		// ���̃X�^�b�N��pop�ʒu
//	pClAct->pMainMan	= NULL;
//	pClAct->pSubMan		= NULL;
	pClAct->pRender		=NULL;		// �����_���[
	
	CLACT_WorkClear(&pClAct->Dummy);	// �A�N�^�[���X�g�_�~�[�f�[�^
	pClAct->DrawFlag = 0;
}

//=============================================================================
//
//	�A�N�^�[���[�N����֐��S
//
//=============================================================================
//-----------------------------------------------------------------------------
/**
 *@brief		�Z���A�N�^�[�f�[�^������
 *						
 *
 *@param	pWork		����������(0 Clear)�f�[�^
 *
 *@return	none
 *
 */
 //----------------------------------------------------------------------------
void CLACT_WorkClear( CLACT_WORK_PTR pWork )
{
	int i;		// ���[�v�p
	
	pWork->pClActSet		= NULL;
	memset( pWork, 0, sizeof(CLACT_WORK) );
//	memset(&pWork->AnmData, 0, sizeof(u32) * CLACT_ANM_DATA_MAX);
	NNS_G2dInitImageProxy( &pWork->ImageProxy );
	NNS_G2dInitImagePaletteProxy( &pWork->PaletteProxy );
	pWork->objmode			= GX_OAM_MODE_NORMAL;
}

//-----------------------------------------------------------------------------
/**
 *@brief		�Z���A�N�^�[���[�N�̎擾
 *						
 *
 *@param	ClActSetIdx		�Z���A�N�^�[�Z�b�g�|�C���^
 *@param	ClActIdx		�Z���A�N�^�[���[�N�C���f�b�N�X
 *
 *@retval	CLACT_WORK_PTR		����
 *@retval	NULL			���s
 *
 */
//----------------------------------------------------------------------------
CLACT_WORK_PTR CLACT_GetWork(CONST_CLACT_SET_PTR ClActSet, s16 ClActIdx)
{
	if(ClActSet == NULL){
		return NULL;
	}
	if(ClActIdx >= ClActSet->WorkNum){
		return NULL;
	}

	return &ClActSet->pWork[ClActIdx];
}

//-----------------------------------------------------------------------------
/**
 *@brief			�ǉ�����
 *
 *@param	add		�o�^�f�[�^
 *
 *@retval	BLACT_WORK*		�o�^�����A�N�^�[�̃|�C���^
 *@retval	NULL			���s
 */
// ----------------------------------------------------------------------------
CLACT_WORK_PTR CLACT_Add(const CLACT_ADD* add)
{
	CLACT_WORK*	cl_w;		// �ǉ�����A�N�^�[���[�N
	
	// �X�^�b�N���烏�[�N���擾
	cl_w = popStack(add->ClActSet);

	if(cl_w == NULL){
		return NULL;
	}

	
	// ���̗v�f�̃f�[�^������������
	cl_w->pClActSet		= add->ClActSet;		// �A�N�^�[�Z�b�g����
	cl_w->AnmNum		= 0;
	cl_w->Matrix		= add->mat;			// ���W�Z�b�g
	cl_w->Scale			= add->sca;			// �g�k�Z�b�g
	cl_w->Rotation		= add->rot;			// ��]�p�Z�b�g
	cl_w->type			= add->DrawArea;	// �]����ʃZ�b�g
	cl_w->DrawPriority	= add->pri;			// �`��D�揇��
	cl_w->affin			= 0;				// �f�t�H�̓A�t�B���Ȃ�
	cl_w->flip			= 0;				// �f�t�H�̓t���b�v�Ȃ�
	cl_w->mosaic		= FALSE;			// ���U�C�N�t���O
	cl_w->objmode		= GX_OAM_MODE_NORMAL;// �I�u�W�F���[�h�m�[�}��

	// �p���b�g�i���o�[
	// BG�\���D�揇�ʂ�over���C�g����
	cl_w->over_write	= NNS_G2D_RND_OVERWRITE_PLTTNO_OFFS | NNS_G2D_RND_OVERWRITE_PRIORITY;	

	// �A�t�B���ϊ��ݒ�
	NNS_G2dSetRndCoreAffineOverwriteMode(
			&( add->ClActSet->pRender->rendererCore ),
			cl_w->affin );
	// �t���b�v�ݒ�
	NNS_G2dSetRndCoreFlipMode(
			&( add->ClActSet->pRender->rendererCore ),
			cl_w->flip & CLACT_FLIP_H,
			cl_w->flip & CLACT_FLIP_V);

	// �`��t���O��ݒ�
	cl_w->DrawFlag		= 1;		// �����_���[�`��
	
	// �I�[�g�A�j���[�V�����ݒ�
	cl_w->AnmFlag		= 0;
	cl_w->Frame			= CLACT_AUTO_ANM_FRAME;

	// �A�j���[�V�����f�[�^��ǂݍ���
	if( LoadData( add->ClActSet, add->ClActHeader,cl_w, add->heap ) == FALSE ){
		// ���s
		CLACT_Delete( cl_w );

		return NULL;
	}

	// �p���b�g�I�t�Z�b�g���擾
	cl_w->palOfs = GetPlttProxyOffset( &cl_w->PaletteProxy, cl_w->type );
	cl_w->palNo = cl_w->palOfs;	// �����l�̓p���b�g�I�t�Z�b�g�ʒu�ɂ���

	// �A�N�^�[���X�g�ɒǉ�
	addCellActList(add->ClActSet, cl_w);
	
	return cl_w;
}

//-----------------------------------------------------------------------------
/**
 *@brief			�V���v���ǉ�����
 *
 *@param	add		�o�^�f�[�^
 *
 *@retval	CLACT_WORK_PTR		�o�^�����A�N�^�[�|�C���^
 *@retval	NULL				���s
 */
// ----------------------------------------------------------------------------
CLACT_WORK_PTR CLACT_AddSimple(const CLACT_ADD_SIMPLE* add)
{
	CLACT_ADD add_ex;

	add_ex.ClActSet		= add->ClActSet;
	add_ex.ClActHeader	= add->ClActHeader;
	add_ex.mat			= add->mat;
	add_ex.sca.x		= FX32_ONE;
	add_ex.sca.y		= FX32_ONE;
	add_ex.sca.z		= FX32_ONE;
	add_ex.rot			= 0;
	add_ex.pri			= add->pri;
	add_ex.DrawArea		= add->DrawArea;
	add_ex.heap			= add->heap;

	return CLACT_Add( &add_ex );
}

//-----------------------------------------------------------------------------
/**
 *@brief			�폜����
 *
 *@param	del		�폜����A�N�^�[���[�N
 *
 *@return	none
 * 
 */
// ----------------------------------------------------------------------------
void CLACT_Delete(CLACT_WORK_PTR del)
{
	CLACT_SET* cs;
	
	// �f�[�^�����邩�`�F�b�N
	if( del->flag != CLACT_NONE ){
			
		CLACT_ANIM_DATA* cell_anm = (CLACT_ANIM_DATA*)&del->AnmData;

		// �`�惊�X�g����j��
		if(del->pLast != NULL){
			dellCellActList( del );
		}

		
		// Vram�]���A�j���[�V�����̃n���h�����
		if( del->flag == CLACT_VRAM_CELL ){
			CLACT_VRAM_ANIM_DATA* p_vram = (CLACT_VRAM_ANIM_DATA*)&del->AnmData;	

			if( NNS_G2dGetImageLocation(&del->ImageProxy, del->type) != NNS_G2D_VRAM_ADDR_NONE ){
				NNS_G2dFreeCellTransferStateHandle( p_vram->CellTransManHandle );
			}
		}

		// �}���`�Z���f�[�^�̉��
		if( del->flag == CLACT_MULTICELL ){
			CLACT_MULTICELL_ANIM_DATA* p_multi = (CLACT_MULTICELL_ANIM_DATA*)&del->AnmData;

			// �m�[�h
			if(p_multi->pNode != NULL){
				sys_FreeMemoryEz( p_multi->pNode );
			}

			// �A�j���[�V�����R���g���[��
			if(p_multi->pCellAnim != NULL){
				sys_FreeMemoryEz( p_multi->pCellAnim );
			}
		}
		
		// �g�p���Ă��Ȃ��ɂ���
		del->flag = CLACT_NONE;	

		// �X�^�b�N�Ƀv�b�V��
		cs = (CLACT_SET*)del->pClActSet;
		pushStack(cs, del);
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	���W��ݒ�
 *
 *@param	act			�A�N�^�[
 *@param	Matrix		���W
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void CLACT_SetMatrix(CLACT_WORK_PTR act, const VecFx32* Matrix)
{
	act->Matrix = *Matrix;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�A�t�B���ϊ����W��ݒ�
 *
 *@param	act			�A�N�^�[
 *@param	Matrix		���W
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void CLACT_SetAffineMatrix(CLACT_WORK_PTR act, const VecFx32* Matrix)
{
	act->AffineMatrix = *Matrix;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�g��l��ݒ�
 *
 *@param	act		�A�N�^�[
 *@param	Scale	�g��l
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void CLACT_SetScale(CLACT_WORK_PTR act, const VecFx32* Scale)
{
	act->Scale = *Scale;
}
//----------------------------------------------------------------------------
/**
 *
 *@brief	�g��l��ݒ肵�A�A�t�B���t���O��ݒ肷��
 *
 *@param	act		�A�N�^�[
 *@param	Scale	�g��l
 *@param	affine	�A�t�B���t���O
 *
 *@return	none
 *
 *affine�t���O
 *	enum{
 *		CLACT_AFFINE_NONE,		// �A�t�B���ϊ��Ȃ�
 *		CLACT_AFFINE_NORMAL,	// �A�t�B���ϊ�
 *		CLACT_AFFINE_DOUBLE,	// �{�p�A�t�B���ϊ�
 *	};
 *
 */
//-----------------------------------------------------------------------------
void CLACT_SetScaleAffine(CLACT_WORK_PTR act, const VecFx32* Scale, int affine)
{
	CLACT_SetScale( act, Scale );
	CLACT_SetAffineParam( act, affine );
}
//----------------------------------------------------------------------------
/**
 *
 *@brief	��]�p��ݒ�
 *
 *@param	act			�A�N�^�[
 *@param	Rotation	��]�p
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void CLACT_SetRotation(CLACT_WORK_PTR act, u16 Rotation)
{
	act->Rotation = Rotation;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	��]�p��ݒ肵�ăA�t�B���t���O��ݒ�
 *
 *@param	act			�A�N�^�[
 *@param	Rotation	��]�p		(0�`65535)
 *@param	affine		�A�t�B���t���O
 *
 *@return	none
 *
 *affine�t���O
 *	enum{
 *		CLACT_AFFINE_NONE,		// �A�t�B���ϊ��Ȃ�
 *		CLACT_AFFINE_NORMAL,	// �A�t�B���ϊ�
 *		CLACT_AFFINE_DOUBLE,	// �{�p�A�t�B���ϊ�
 *	};
 *
 */
//-----------------------------------------------------------------------------
void CLACT_SetRotationAffine(CLACT_WORK_PTR act, u16 Rotation, int affine)
{
	CLACT_SetRotation( act, Rotation );
	CLACT_SetAffineParam( act, affine );
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�`��t���O��ݒ�
 *
 *@param	act		�A�N�^�[
 *@param	flag	�`��t���O	0:��`��	1:�����_���`��	
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void CLACT_SetDrawFlag(CLACT_WORK_PTR act, int flag)
{
	GF_ASSERT( act );
	GF_ASSERT( flag < 2 );		// 2��菬�����K�v������
	act->DrawFlag = flag;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�I�[�g�A�j���t���O��ݒ�
 *
 *@param	act		�A�N�^�[
 *@param	flag	�I�[�g�A�j���t���O	0:��A�j��	1:�I�[�g�A�j��
 *
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void CLACT_SetAnmFlag(CLACT_WORK_PTR act, int flag)
{
	GF_ASSERT( act );
	GF_ASSERT( flag < 2 );		// 2��菬�����K�v������
	act->AnmFlag = flag;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�I�[�g�A�j���[�V�����t���[����ݒ�
 *
 *@param	act		�A�N�^�[
 *@param	frame	�P�V���N�ɐi�߂�t���[����
 *
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void CLACT_SetAnmFrame(CLACT_WORK_PTR act, fx32 frame)
{
	GF_ASSERT( act );

	act->Frame = frame;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�A�t�B���ϊ��p�����[�^
 *
 *	@param	act		�A�N�^�[
 *	@param	param	�A�t�B���ϊ��p�����[�^
 *
 *	@return	none
 *
 * param
 *	enum{
 *		CLACT_AFFINE_NONE,		// �A�t�B���ϊ��Ȃ�
 *		CLACT_AFFINE_NORMAL,	// �A�t�B���ϊ�
 *		CLACT_AFFINE_DOUBLE,	// �{�p�A�t�B���ϊ�
 *	};
 *
 */
//-----------------------------------------------------------------------------
void CLACT_SetAffineParam( CLACT_WORK_PTR act, int param )
{
	GF_ASSERT(act);

	act->affin	= param;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�t���b�v�̐ݒ�
 *
 *	@param	act		�A�N�^�[
 *	@param	flag	�t���b�v�t���O 
 *
 *	@return	none
 *
 * flag
 *	enum{
 * 		CLACT_FLIP_NONE,		// �t���b�v�Ȃ�
 * 		CLACT_FLIP_H,			// �t���b�v��������
 *		CLACT_FLIP_V,			// �t���b�v��������
 *		CLACT_FLIP_HV,			// �������t���b�v
 *	};
 *
 */
//-----------------------------------------------------------------------------
void CLACT_SetFlip( CLACT_WORK_PTR act, int flag )
{
	GF_ASSERT(act);
	act->flip = flag;
	act->affin	= CLACT_AFFINE_NONE;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	���W���擾
 *
 *@param	act		�A�N�^�[
 *
 *@return	VecFx32	���W
 *
 *
 */
//-----------------------------------------------------------------------------
const VecFx32* CLACT_GetMatrix(CONST_CLACT_WORK_PTR act)
{
	return &act->Matrix;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�A�t�B���ϊ����W���擾
 *
 *@param	act		�A�N�^�[
 *
 *@return	VecFx32	���W
 *
 *
 */
//-----------------------------------------------------------------------------
const VecFx32* CLACT_GetAffineMatrix(CONST_CLACT_WORK_PTR act)
{
	return &act->AffineMatrix;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�g��l���擾
 *
 *@param	act		�A�N�^�[
 *
 *@return	VecFx32	�g��l
 *
 *
 */
//-----------------------------------------------------------------------------
const VecFx32* CLACT_GetScale(CONST_CLACT_WORK_PTR act)
{
	return &act->Scale;
}
//----------------------------------------------------------------------------
/**
 *
 *@brief	��]�p�x���擾
 *
 *@param	act		�A�N�^�[
 *
 *@return	u16		��]�p�x
 *
 *
 */
//-----------------------------------------------------------------------------
u16 CLACT_GetRotation(CONST_CLACT_WORK_PTR act)
{
	return act->Rotation;
}
//----------------------------------------------------------------------------
/**
 *
 *@brief	�`��t���O���擾
 *
 *@param	act	�A�N�^�[
 *
 *@return	int		0:��`��	1:�`��
 *
 *
 */
//-----------------------------------------------------------------------------
int CLACT_GetDrawFlag(CONST_CLACT_WORK_PTR act)
{
	return act->DrawFlag;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�I�[�g�A�j���t���O���擾
 *
 *@param	act	�A�N�^�[
 *
 *@return	int		0:��A�j��	1:�I�[�g�A�j���[�V����
 *
 *
 */
//-----------------------------------------------------------------------------
int CLACT_GetAnmFlag(CONST_CLACT_WORK_PTR act)
{
	return act->AnmFlag;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�I�[�g�A�j���[�V�����t���[�����擾
 *
 *@param	act	�A�N�^�[
 *
 *@return	fx32		�P�V���N�ɐi�߂�t���[����
 *
 *
 */
//-----------------------------------------------------------------------------
fx32 CLACT_GetAnmFrame(CONST_CLACT_WORK_PTR act)
{
	return act->Frame;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�A�t�B���p�����[�^	�擾
 *
 *	@param	act		�A�N�^�[
 *
 *	@return	int		�A�t�B���p�����[�^
 *
 * ret
 *	enum{
 *		CLACT_AFFINE_NONE,		// �A�t�B���ϊ��Ȃ�
 *		CLACT_AFFINE_NORMAL,	// �A�t�B���ϊ�
 *		CLACT_AFFINE_DOUBLE,	// �{�p�A�t�B���ϊ�
 *	};
 *
 */
//-----------------------------------------------------------------------------
int CLACT_GetAffineParam( CONST_CLACT_WORK_PTR act )
{
	GF_ASSERT(act);
	return act->affin;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�t���b�v�ݒ���擾
 *
 *	@param	act		�A�N�^�[
 *
 *	@return	int		�t���b�v�ݒ�
 *
 * ret
 *	enum{
 * 		CLACT_FLIP_NONE,		// �t���b�v�Ȃ�
 * 		CLACT_FLIP_H,			// �t���b�v��������
 *		CLACT_FLIP_V,			// �t���b�v��������
 *		CLACT_FLIP_HV,			// �������t���b�v
 *	};
 *
 */
//-----------------------------------------------------------------------------
int CLACT_GetFlip( CONST_CLACT_WORK_PTR act )
{
	GF_ASSERT(act);
	return act->flip;
}

//-----------------------------------------------------------------------------
/*
 *@brief	�A�j���[�V�����̃V�[�P���X���`�F���W����
 *
 *@param	actCell�F�Z���A�N�^�[
 *@param	num�F�V�[�P���X�i���o�[
 *
 *@return	none
 */
 //----------------------------------------------------------------------------
void CLACT_AnmChg( CLACT_WORK_PTR actCell, u32 num )
{
	const NNSG2dAnimSequence* pSeq;		// �V�[�P���X

	// �ύX�����V�[�P���X�i���o�[���Z�b�g
	actCell->AnmNum = num;
	
	// �Z���A�j���[�V�������`�F�b�N
	if( (actCell->flag == CLACT_CELL) || (actCell->flag == CLACT_VRAM_CELL) ){
		CLACT_ANIM_DATA* anm = (CLACT_ANIM_DATA*)&actCell->AnmData;
		
		// �V�[�P���X���擾
		pSeq = NNS_G2dGetAnimSequenceByIdx( anm->pAnimBank, num );

		// �V�[�P���X��K�p
		NNS_G2dSetCellAnimationSequence( &anm->AnmCtrl, pSeq );

		// �A�j���[�V�����X�^�[�g
		NNS_G2dStartAnimCtrl( &anm->AnmCtrl.animCtrl );
	}else{
		CLACT_MULTICELL_ANIM_DATA* anm = (CLACT_MULTICELL_ANIM_DATA*)&actCell->AnmData;
		
		// �}���`�Z���A�j���[�V����
		// �V�[�P���X���擾
		pSeq = NNS_G2dGetAnimSequenceByIdx( anm->pMCABank, num );

		// �V�[�P���X��K�p
		NNS_G2dSetAnimSequenceToMCAnimation( &anm->AnmCtrl, pSeq );

		// �A�j���[�V�����X�^�[�g
		NNS_G2dStartAnimCtrl( &anm->AnmCtrl.animCtrl );
	}
}

//-----------------------------------------------------------------------------
/*
 *@brief	�A�j���[�V�����̃V�[�P���X���`�F���W����
 *
 *@param	actCell�F�Z���A�N�^�[
 *@param	num�F�V�[�P���X�i���o�[
 *
 *@return	none
 */
 //----------------------------------------------------------------------------
void CLACT_AnmChgCheck( CLACT_WORK_PTR actCell, u32 num )
{
	// �V�[�P���X���������`�F���W
	if( actCell->AnmNum != num ){
		CLACT_AnmChg( actCell, num );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�A�j���[�V�������X�^�[�g
 *
 *	@param	actCell		�Z���A�N�^�|
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void CLACT_AnmReStart( CLACT_WORK_PTR actCell )
{
	// �Z���A�j���[�V�������`�F�b�N
	if( (actCell->flag == CLACT_CELL) || (actCell->flag == CLACT_VRAM_CELL) ){
		CLACT_ANIM_DATA* anm = (CLACT_ANIM_DATA*)&actCell->AnmData;
		
		// �X�e�[�^�X���Z�b�g
		NNS_G2dResetAnimCtrlState( &anm->AnmCtrl.animCtrl );

		// �A�j���[�V�����X�^�[�g
		NNS_G2dStartAnimCtrl( &anm->AnmCtrl.animCtrl );
		
		CLACT_AnmFrameSet( actCell, 0 );
	}else{
		CLACT_MULTICELL_ANIM_DATA* anm = (CLACT_MULTICELL_ANIM_DATA*)&actCell->AnmData;
		
		// �}���`�Z���A�j���[�V����
		// �X�e�[�^�X���Z�b�g
		NNS_G2dResetAnimCtrlState( &anm->AnmCtrl.animCtrl );

		// �A�j���[�V�����X�^�[�g
		NNS_G2dStartAnimCtrl( &anm->AnmCtrl.animCtrl );

		CLACT_AnmFrameSet( actCell, 0 );
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	���݂̃A�j���[�V�����V�[�P���X���擾
 *
 *@param	actCell		�A�N�^�[
 *
 *@return	s32		�A�j���[�V�����V�[�P���X�i���o�[
 *
 *
 */
//-----------------------------------------------------------------------------
u32 CLACT_AnmGet( CONST_CLACT_WORK_PTR actCell )
{
	return actCell->AnmNum;
}

//-----------------------------------------------------------------------------
/**	
 *@brief	�A�j���[�V����������
 *
 *@param	actCell�F����\����
 *@param	num�F�t���[����i�߂�l
 *
 *@return	none
 */
 //----------------------------------------------------------------------------
void CLACT_AnmFrameChg( CLACT_WORK_PTR actCell, fx32 num )
{
	// �A�j���[�V����
	// �Z���A�j���[�V�������`�F�b�N
	if( (actCell->flag == CLACT_CELL) || (actCell->flag == CLACT_VRAM_CELL) ){
		CLACT_ANIM_DATA* anm = (CLACT_ANIM_DATA*)&actCell->AnmData;
		NNS_G2dTickCellAnimation( &anm->AnmCtrl, num );
	}else{
		CLACT_MULTICELL_ANIM_DATA* anm = (CLACT_MULTICELL_ANIM_DATA*)&actCell->AnmData;
		NNS_G2dTickMCAnimation( &anm->AnmCtrl, num );
	}
}

//-----------------------------------------------------------------------------
/**	
 *@brief	�A�j���[�V�����t���[�����Z�b�g
 *
 *@param	actCell�F����\����
 *@param	num�F�Z�b�g����A�j���[�V�����t���[����
 *
 *@return	none
 */
//----------------------------------------------------------------------------
void CLACT_AnmFrameSet( CLACT_WORK_PTR actCell, u16 num )
{
	// �V�[�P���X�ԍ��̃t���[�����̂Ƃ���ɂ���
	// �Z���A�j���[�V�������`�F�b�N
	if( (actCell->flag == CLACT_CELL) || (actCell->flag == CLACT_VRAM_CELL) ){
		CLACT_ANIM_DATA* anm = (CLACT_ANIM_DATA*)&actCell->AnmData;
		NNS_G2dSetCellAnimationCurrentFrame( &anm->AnmCtrl, num );
	}else{
		CLACT_MULTICELL_ANIM_DATA* anm = (CLACT_MULTICELL_ANIM_DATA*)&actCell->AnmData;
		NNS_G2dSetMCAnimationCurrentFrame( &anm->AnmCtrl, num );
	}
}

//-----------------------------------------------------------------------------
/**	
 *@brief				�A�j���[�V�����t���[�����擾
 *
 *@param	actCell�F����\����
 *
 *@return	���̃t���[����
 */
//----------------------------------------------------------------------------
u16 CLACT_AnmFrameGet( CONST_CLACT_WORK_PTR actCell)
{
	NNSG2dAnimController*	anm_cntl;		// �A�j���[�V�����R���g���[��
	
	// �Z���A�j���[�V�������`�F�b�N
	if( (actCell->flag == CLACT_CELL) || (actCell->flag == CLACT_VRAM_CELL) ){
		CLACT_ANIM_DATA* anm = (CLACT_ANIM_DATA*)&actCell->AnmData;
		anm_cntl = NNS_G2dGetCellAnimationAnimCtrl( &anm->AnmCtrl );
	}else{
		CLACT_MULTICELL_ANIM_DATA* anm = (CLACT_MULTICELL_ANIM_DATA*)&actCell->AnmData;
		anm_cntl = NNS_G2dGetMCAnimAnimCtrl( &anm->AnmCtrl );
	}
	return NNS_G2dGetAnimCtrlCurrentFrame( anm_cntl );
}

//-----------------------------------------------------------------------------
/**
 *@brief	BG�ʂƂ̗D��x��ύX����
 *
 *@param	actCell�F����\����
 *@param	Priority�F�D��x
 *
 *@return	none
 */
 //----------------------------------------------------------------------------
void CLACT_BGPriorityChg( CLACT_WORK_PTR actCell, u8 Priority )
{
	actCell->Priority = Priority;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	BG�ʂƂ̕`��D��x���擾
 *
 *@param	actCell		�A�N�^�[
 *
 *@return	u8			�D��x
 *
 *
 */
//-----------------------------------------------------------------------------
u8 CLACT_BGPriorityGet( CONST_CLACT_WORK_PTR actCell)
{
	return actCell->Priority;
}

//-----------------------------------------------------------------------------
/**
 *@brief				�p���b�g�i���o�[��ύX
 *
 *@param	actCell�F����\����
 *@param	pltt_num�F�ύX����p���b�g�i���o�[
 * 
 *@return	none
 *
 * ���p���b�g�i���o�[�ݒ�ƃp���b�g�I�t�Z�b�g�ݒ�͓������܂���B
 *�@�@���p���b�g�i���o�[��ݒ肷��ƃI�t�Z�b�g�̒l�͔��f����Ȃ��Ȃ�܂��B
 *	�@���I�t�Z�b�g�l��ݒ肵���Ƃ��̓p���b�g�i���o�[�����f����Ȃ��Ȃ�܂��B
 */
 //----------------------------------------------------------------------------
void CLACT_PaletteNoChg( CLACT_WORK_PTR actCell, u32 pltt_num )
{
	GF_ASSERT( actCell );

	actCell->palNo = pltt_num;

	// �p���b�g�i���o�[���f
	// �p���b�g�I�t�Z�b�g���f
	actCell->over_write	|= NNS_G2D_RND_OVERWRITE_PLTTNO;	
	actCell->over_write &= ~NNS_G2D_RND_OVERWRITE_PLTTNO_OFFS;
}

//-----------------------------------------------------------------------------
/**
 * ��CLACT_PaletteNoChg�̌��ʂɃp���b�g�]���擪�i���o�[�����Z���܂��B
 *
 *@brief				�p���b�g�i���o�[��ύX
 *
 *@param	actCell			����\����
 *@param	pltt_num		�ύX����p���b�g�i���o�[
 * 
 *@return	none
 *
 * ���p���b�g�i���o�[�ݒ�ƃp���b�g�I�t�Z�b�g�ݒ�͓������܂���B
 *�@�@���p���b�g�i���o�[��ݒ肷��ƃI�t�Z�b�g�̒l�͔��f����Ȃ��Ȃ�܂��B
 *	�@���I�t�Z�b�g�l��ݒ肵���Ƃ��̓p���b�g�i���o�[�����f����Ȃ��Ȃ�܂��B
 * 
 */
 //----------------------------------------------------------------------------
void CLACT_PaletteNoChgAddTransPlttNo( CLACT_WORK_PTR actCell, u32 pltt_num )
{
	CLACT_PaletteNoChg( actCell, pltt_num );

	actCell->palNo += GetPlttProxyOffset( &actCell->PaletteProxy, actCell->type );

}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�p���b�g�i���o�[�擾
 *
 *@param	actCell		�A�N�^�[
 *
 *@return	u32		���̃p���b�g�i���o�[
 *
 *
 */
//-----------------------------------------------------------------------------
u32 CLACT_PaletteNoGet( CONST_CLACT_WORK_PTR actCell )
{
	return actCell->palNo;
}

//-----------------------------------------------------------------------------
/**
 * ��OAM�A�g���r���[�g�ɐݒ肳��Ă���p���b�g�i���o�[�ɉ��Z����܂��B
 * 
 *@brief	�p���b�g�I�t�Z�b�g��ݒ�
 *
 *@param	actCell		����\����
 *@param	pltt_num	�p���b�g�I�t�Z�b�g�i���o�[
 * 
 *@return	none
 *
 * ���p���b�g�i���o�[�ݒ�ƃp���b�g�I�t�Z�b�g�ݒ�͓������܂���B
 *�@�@���p���b�g�i���o�[��ݒ肷��ƃI�t�Z�b�g�̒l�͔��f����Ȃ��Ȃ�܂��B
 *	�@���I�t�Z�b�g�l��ݒ肵���Ƃ��̓p���b�g�i���o�[�����f����Ȃ��Ȃ�܂��B
 * 
 */
 //----------------------------------------------------------------------------
void CLACT_PaletteOffsetChg( CLACT_WORK_PTR actCell, u32 pltt_num )
{
	GF_ASSERT( actCell );

	actCell->palOfs = pltt_num;

	// �p���b�g�i���o�[�񔽉f
	// �p���b�g�I�t�Z�b�g���f
	actCell->over_write	|= NNS_G2D_RND_OVERWRITE_PLTTNO_OFFS;	
	actCell->over_write &= ~NNS_G2D_RND_OVERWRITE_PLTTNO;
}

//----------------------------------------------------------------------------
/**
 * ��CLACT_PaletteOffsetChg�֐��̌��ʂɃp���b�g�̓]����擪�p���b�g�i���o�[�����Z���܂��B
 *
 *@brief	�p���b�g�I�t�Z�b�g��ݒ�
 *
 *	@param	act		�A�N�^�[
 *
 *	@return	�p���b�g�i���o�[
 *
 *
 * ���p���b�g�i���o�[�ݒ�ƃp���b�g�I�t�Z�b�g�ݒ�͓������܂���B
 *�@�@���p���b�g�i���o�[��ݒ肷��ƃI�t�Z�b�g�̒l�͔��f����Ȃ��Ȃ�܂��B
 *	�@���I�t�Z�b�g�l��ݒ肵���Ƃ��̓p���b�g�i���o�[�����f����Ȃ��Ȃ�܂��B
 */
//-----------------------------------------------------------------------------
void CLACT_PaletteOffsetChgAddTransPlttNo( CLACT_WORK_PTR act, u32 pltt_num )
{
	CLACT_PaletteOffsetChg( act, pltt_num );

	act->palOfs += GetPlttProxyOffset( &act->PaletteProxy, act->type );
}


//----------------------------------------------------------------------------
/**
 *
 *@brief	�p���b�g�I�t�Z�b�g�l�擾
 *
 *@param	actCell		�A�N�^�[
 *
 *@return	u32		���̃p���b�g�I�t�Z�b�g�l
 *
 *
 */
//-----------------------------------------------------------------------------
u32 CLACT_PaletteOffsetGet( CONST_CLACT_WORK_PTR actCell )
{
	GF_ASSERT( actCell );

	return actCell->palOfs;
}

//-----------------------------------------------------------------------------
/**
 *@brief	�`��D�揇�ʂ�ݒ�
 *
 *@param	actCell		����\����
 *@param	Priority	�D�揇��
 *				
 * 
 *@return	none
 */
 //----------------------------------------------------------------------------
void CLACT_DrawPriorityChg( CLACT_WORK_PTR actCell, u32 Priority )
{
	CLACT_SET* cs = (CLACT_SET*)actCell->pClActSet;
	
	// �D�揇�ʂ�ύX
	actCell->DrawPriority = Priority;
	
	// �A�N�^�[���X�g�̍ēo�^���s��
	dellCellActList(actCell);
	addCellActList(cs, actCell);
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�`��D�揇�ʂ��擾
 *
 *@param	actCell		�A�N�^�[
 *
 *@return	u32			�`��D�揇��
 *
 *
 */
//-----------------------------------------------------------------------------
u32 CLACT_DrawPriorityGet( CONST_CLACT_WORK_PTR actCell )
{
	return actCell->DrawPriority;
}

//----------------------------------------------------------------------------
//
/**
 *
 *	@brief	�v���N�V�f�[�^��ݒ�
 *
 *	@param	act			�A�N�^�[
 *	@param	pImageProxy	�ݒ肷��C���[�W�v���N�V
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void CLACT_ImageProxySet( CLACT_WORK_PTR act, const NNSG2dImageProxy* pImageProxy )
{
	act->ImageProxy = *pImageProxy;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�v���N�V�f�[�^���擾
 *
 *	@param	act			�A�N�^�[
 *
 *	@return	�A�N�^�[���������Ă���C���[�W�v���N�V
 */
//-----------------------------------------------------------------------------
NNSG2dImageProxy * CLACT_ImageProxyGet( CLACT_WORK_PTR act )
{
	return &act->ImageProxy;
}


//--------------------------------------------------------------
/**
 * @brief	�v���N�V�f�[�^��ݒ�
 *
 * @param	act	
 * @param	PaletteProxy	
 *
 * @retval	GLOBAL void	
 *
 */
//--------------------------------------------------------------
void CLACT_PaletteProxySet( CLACT_WORK_PTR act, const NNSG2dImagePaletteProxy*  PaletteProxy)
{
	act->PaletteProxy = *PaletteProxy;
}


//--------------------------------------------------------------
/**
 * @brief	�v���N�V�f�[�^���擾
 *
 * @param	act	
 *
 * @retval	�A�N�^�[���������Ă�v���N�V
 *
 */
//--------------------------------------------------------------
NNSG2dImagePaletteProxy * CLACT_PaletteProxyGet( CLACT_WORK_PTR act )
{
	return &act->PaletteProxy;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	���U�C�N�ݒ�
 *
 *	@param	act		�A�N�^�[���[�N
 *	@param	flag	�t���O	TRUE�����U�C�NON	FALSE�����U�C�NOFF
 *
 *	@return	none
 *
 * ���U�C�NOFF�̎��ł��A�j�g���L�����N�^�Ń��U�C�NON�ɂ���OAM��
 * ���U�C�N���������ĕ`�悳��܂��B
 *
 */
//-----------------------------------------------------------------------------
void CLACT_MosaicSet( CLACT_WORK_PTR act, BOOL flag )
{
	act->mosaic = flag;

	if(flag == TRUE){
		act->over_write |= NNS_G2D_RND_OVERWRITE_MOSAIC;
	}else{
		act->over_write ^= NNS_G2D_RND_OVERWRITE_MOSAIC;
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	���U�C�N�ݒ��Ԃ��擾
 *
 *	@param	act		�A�N�^�[���[�N
 *
 *	@retval	TRUE	���U�C�N��ON
 *	@retval	FALSE	���U�C�N��OFF	�i�j�g���L�����N�^�Őݒ肵�Ă�Ƃ��͔��f�����j
 *
 *
 */
//-----------------------------------------------------------------------------
BOOL CLACT_MosaicGet( CONST_CLACT_WORK_PTR act )
{
	return act->mosaic;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	VRAM�^�C�v���擾
 *
 *	@param	act		�A�N�^�[���[�N
 *
 *	@retval	VRAM�^�C�v
 *
 *
 */
//-----------------------------------------------------------------------------
NNS_G2D_VRAM_TYPE CLACT_VramTypeGet( CONST_CLACT_WORK_PTR act )
{
	return act->type;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�A�N�^�[���A�j���[�V���������`�F�b�N
 *
 *	@param	act		�A�N�^�[���[�N
 *
 *	@retval	TRUE	�A�j���[�V������
 *	@retval	FALSE	�X�g�b�v
 *
 *
 */
//-----------------------------------------------------------------------------
BOOL CLACT_AnmActiveCheck( CLACT_WORK_PTR act )
{
	GF_ASSERT( act );

	// �V�[�P���X�ԍ��̃t���[�����̂Ƃ���ɂ���
	// �Z���A�j���[�V�������`�F�b�N
	if( (act->flag == CLACT_CELL) || (act->flag == CLACT_VRAM_CELL) ){
		CLACT_ANIM_DATA* anm = (CLACT_ANIM_DATA*)&act->AnmData;
		return NNS_G2dIsAnimCtrlActive( &anm->AnmCtrl.animCtrl );
	}else{
		CLACT_MULTICELL_ANIM_DATA* anm = (CLACT_MULTICELL_ANIM_DATA*)&act->AnmData;
		return NNS_G2dIsAnimCtrlActive( &anm->AnmCtrl.animCtrl );
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�I�u�W�F���[�h��ݒ�
 *
 *	@param	act			�A�N�^�[���[�N
 *	@param	objmode		�I�u�W�F���[�h 
 *
 *	@return	none
 *
 *	�I�u�W�F���[�h��GX_OAM_MODE_NORMAL�ɂ����NitroCharacter�Őݒ肵��
 *	�I�u�W�F���[�h�ŕ`�悳��܂��B
 *	
	GX_OAM_MODE_NORMAL		�m�[�}��OBJ 
	GX_OAM_MODE_XLU			������OBJ 
	GX_OAM_MODE_OBJWND OBJ	�E�B���h�E 
	GX_OAM_MODE_BITMAPOBJ	�r�b�g�}�b�vOBJ 
 *
 *
 */
//-----------------------------------------------------------------------------
void CLACT_ObjModeSet( CLACT_WORK_PTR act, GXOamMode objmode )
{
	GF_ASSERT(act);
	
	act->objmode = objmode;

	if(objmode == GX_OAM_MODE_NORMAL){
		act->over_write ^= NNS_G2D_RND_OVERWRITE_OBJMODE;
	}else{
		act->over_write |= NNS_G2D_RND_OVERWRITE_OBJMODE;
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�I�u�W�F���[�h���擾
 *
 *	@param	act		�A�N�^�[���[�N
 *
 *	@retval	GX_OAM_MODE_NORMAL		�m�[�}��OBJ 
 *	@retval	GX_OAM_MODE_XLU			������OBJ 
 *	@retval	GX_OAM_MODE_OBJWND OBJ	�E�B���h�E 
 *	@retval	GX_OAM_MODE_BITMAPOBJ	�r�b�g�}�b�vOBJ 
 *
 *	�I�u�W�F���[�h��GX_OAM_MODE_NORMAL�̎���NitroCharacter�Őݒ肵��
 *	�I�u�W�F���[�h�ŕ`�悳��܂��B
 *
 */
//-----------------------------------------------------------------------------
GXOamMode CLACT_ObjModeGet( CONST_CLACT_WORK_PTR act )
{
	GF_ASSERT( act );
	return act->objmode;
}

//----------------------------------------------------------------------------
/**
 *	@brief	OAM���W�X�^�N���A�@���C��
 *
 *	@param	heap �q�[�v
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void CLACT_UtilOamRamClear_Main( int heap )
{
	void* p_cbff;	// �������p�o�b�t�@

	p_cbff = sys_AllocMemory( heap, sizeof(GXOamAttr) * 128 );
	memset( p_cbff, 0xC0, sizeof(GXOamAttr) * 128 );
	DC_FlushRange( p_cbff, sizeof(GXOamAttr) * 128 );
	GX_LoadOAM( p_cbff, 0, sizeof(GXOamAttr) * 128 );
	sys_FreeMemoryEz( p_cbff );
}

//----------------------------------------------------------------------------
/**
 *	@brief	OAM���W�X�^�N���A�@�T�u
 *
 *	@param	heap �q�[�v
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void CLACT_UtilOamRamClear_Sub( int heap )
{
	void* p_cbff;	// �������p�o�b�t�@

	p_cbff = sys_AllocMemory( heap, sizeof(GXOamAttr) * 128 );
	memset( p_cbff, 0xC0, sizeof(GXOamAttr) * 128 );
	GXS_LoadOAM( p_cbff, 0, sizeof(GXOamAttr) * 128 );
	sys_FreeMemoryEz( p_cbff );
}


//=============================================================================
//
//	�v���C�x�[�g�֐�
//
//=============================================================================
//-----------------------------------------------------------------------------
/**
 *@brief				�A�j���[�V�����f�[�^��ǂݍ���
 *		
 *@param	pSet	�Z���A�N�^�[�Z�b�g
 *@param	pHeader�F�e�t�@�C���̓������\����
 *@param	pWork�F����\����
 *		 	
 *@retval	TRUE �F����
 *@retval 	FALSE�F���s
 *
 */
 //----------------------------------------------------------------------------
static BOOL LoadData( const CLACT_SET* pSet, const CLACT_HEADER* pHeader, CLACT_WORK* pWork, int heap )
{
	//
	// �A�j���[�V����Type�𒲂ׂăA�j���[�V�����̓ǂݍ��݂�����
	// �A�j���[�V����Type�̎擾
	pWork->flag = getActType( pHeader );

	// �v���N�V�ݒ�
	pWork->ImageProxy = *pHeader->pImageProxy;
	// �p���b�g�f�[�^
	pWork->PaletteProxy = *pHeader->pPaletteProxy;

	// Type�̃A�j���[�V������ǂݍ���
	// Cell�f�[�^
	LoadCell( pHeader->pCellBank, pWork );

	// Cell�A�j���[�V�����f�[�^
	if( pHeader->pAnimBank ){
		
		LoadCellAnm( pHeader->pAnimBank, pWork );
	}else{
		
		LoadCellAnm( pSet->pAnimBank, pWork );
	}

	// type���}���`�Z���̂Ƃ�
	if( pWork->flag == CLACT_MULTICELL ){
		// MultiCell�f�[�^
		LoadMultiCell( pHeader->pMCBank, pWork );

		// MultiCell�A�j���[�V�����f�[�^
		LoadMultiCellAnm( pHeader->pMCABank, pWork );

		// MultiCell�A�j���[�V�����R���g���[�����쐬
		MakeMultiCellAnm( pWork , heap);
	}else{
		// Vram�]�����`�F�b�N
		if( pWork->flag == CLACT_VRAM_CELL ){
			CLACT_VRAM_ANIM_DATA* p_vram = (CLACT_VRAM_ANIM_DATA*)&pWork->AnmData;
		
			
			// �Z���]���A�j���[�V�����ŃA�j���[�V�����R���g���[�����쐬
			MakeCellAnmVram( pHeader, pWork, heap );
		}else{
			// �Z���A�j���[�V�����R���g���[�����쐬
			MakeCellAnm( pWork, heap );
		}
	}

	// BG�ʂƂ̗D��x���Z�b�g
	pWork->Priority = pHeader->priority;


	return TRUE;
}

//-----------------------------------------------------------------------------
/**
 *@brief				�A�j���[�V����Type���擾����
 *
 *@param	pHeader�F�A�j���f�[�^�i�t�@�C���p�X�̏W�܂�j
 *		
 *@return	Type�̒l
 *
 */
 //----------------------------------------------------------------------------
static u32	getActType( const CLACT_HEADER* pHeader )
{
	//
	// �t�@�C���������邩���`�F�b�N���ăA�j���[�V�������@��Ԃ�
	//
	// �}���`�Z���A�j���[�V�������`�F�b�N
	if( pHeader->pMCBank != NULL ){
		return CLACT_MULTICELL;
	}

	// Vram�]�����`�F�b�N
	if( pHeader->flag == 1 ){
		return CLACT_VRAM_CELL;
	}

	return CLACT_CELL;
}




//-----------------------------------------------------------------------------
/**
 *@brief				�Z���f�[�^��ǂݍ���
 *
 *@param	p_str�F�t�@�C���p�X
 *@param	pWork�F����\����
 *
 *@return	none
 *
 */
 //----------------------------------------------------------------------------
static void LoadCell( const NNSG2dCellDataBank* Cell, CLACT_WORK* pWork )
{
	CLACT_ANIM_DATA*	pCell;	

	//
	// �Z���f�[�^���擾
	//
	pCell = (CLACT_ANIM_DATA*)&pWork->AnmData;
	
	// �f�[�^�̐ݒ�
	pCell->pCellBank = Cell;
}

//-----------------------------------------------------------------------------
/**
 *@brief				�Z���A�j���[�V�����f�[�^��ǂݍ���
 *
 *@param	p_str�F�t�@�C���p�X
 *@param	pWork�F����\����
 *
 *@return	none
 *
 */
 //----------------------------------------------------------------------------
static void LoadCellAnm( const NNSG2dCellAnimBankData* Anm, CLACT_WORK* pWork )
{
	CLACT_ANIM_DATA*	pCell;	

	//
	// �Z���f�[�^���擾
	//
	pCell = (CLACT_ANIM_DATA*)&pWork->AnmData;
	
	// �f�[�^�̐ݒ�
	pCell->pAnimBank = Anm;
}

//-----------------------------------------------------------------------------
/**
 *@brief			�}���`�Z���̓ǂݍ���
 *				
 *@param	p_str�F�t�@�C���p�X
 *@param	pWork�F����\����
 *
 *@return	none
 *
 */
 //----------------------------------------------------------------------------
static void LoadMultiCell( const NNSG2dMultiCellDataBank* Mlt, CLACT_WORK* pWork )
{
	CLACT_MULTICELL_ANIM_DATA*	pMulti;		// �}���`�Z���p�̃f�[�^�擾�p

	// �}���`�Z���p�̃f�[�^�擾
	pMulti = (CLACT_MULTICELL_ANIM_DATA*)&pWork->AnmData;

	// �f�[�^�ݒ�
	pMulti->pMCBank = Mlt;
}

//-----------------------------------------------------------------------------
/**
 *@brief			�}���`�Z���A�j���[�V�����̓ǂݍ���
 *				
 *@param	p_str�F�t�@�C���p�X
 *@param	pWork�F����\����
 *
 *preturn	none
 *
 */
 //----------------------------------------------------------------------------
static void LoadMultiCellAnm( const NNSG2dMultiCellAnimBankData* Anm, CLACT_WORK* pWork )
{
	CLACT_MULTICELL_ANIM_DATA*	pMulti;		// �}���`�Z���p�̃f�[�^�擾�p

	// �}���`�Z���p�̃f�[�^�擾
	pMulti = (CLACT_MULTICELL_ANIM_DATA*)&pWork->AnmData;

	// �f�[�^�̐ݒ�
	pMulti->pMCABank = Anm;
}

//-----------------------------------------------------------------------------
/**
 *@brief			�Z���A�j���[�V�������\�z
 *
 *@param	pWork�F����\����
 *
 *@return	none
 *
 */
 //----------------------------------------------------------------------------
static void MakeCellAnm( CLACT_WORK* pWork, int heap )
{
	CLACT_ANIM_DATA*	pCell;			// �Z���f�[�^���擾


	//
	// �Z���f�[�^���擾
	//
	pCell = (CLACT_ANIM_DATA*)&pWork->AnmData;

	//
	// �Z���A�j���[�V������������
	//
	NNS_G2dInitCellAnimation(
                (NNSG2dCellAnimation*)&pCell->AnmCtrl,
                NNS_G2dGetAnimSequenceByIdx(pCell->pAnimBank, 0),
                pCell->pCellBank );
}

//-----------------------------------------------------------------------------
/**
 *@brief			�Z��Vram�]���A�j���[�V�������\�z
 *
 *@param	pWork�F����\����
 *
 *@return	none
 *
 */
 //----------------------------------------------------------------------------
static void MakeCellAnmVram( const CLACT_HEADER* pHeader, CLACT_WORK* pWork , int heap)
{
	CLACT_VRAM_ANIM_DATA*	pCell;			// �Z���f�[�^���擾
	const NNSG2dCharacterData* pCharData;	// �L�����N�^�f�[�^

	//
	// �Z���f�[�^���擾
	//
	pCell = (CLACT_VRAM_ANIM_DATA*)&pWork->AnmData;

	// �Z���A�j���[�V����Vram�]���Ǘ��I�u�W�F�N�g�n���h���擾
	pCell->CellTransManHandle = NNS_G2dGetNewCellTransferStateHandle();
	

	// �L�����N�^�f�[�^��ݒ�
	pCharData = pHeader->pCharData;

	//
	// �Z��Vram�]���A�j���̏�����
	//
	NNS_G2dInitCellAnimationVramTransfered(
                (NNSG2dCellAnimation*)&pCell->AnmCtrl,
                NNS_G2dGetAnimSequenceByIdx(pCell->pAnimBank, 0),
                pCell->pCellBank,

                pCell->CellTransManHandle,  // ���̃Z���A�j���[�V������VRAM�]�����Ǘ�����
											// �Z���]����ԊǗ��I�u�W�F�N�g�̃n���h��
											// �ȉ���3�� (1) ��Callback�֐��� dstAddr �Ƃ��ēn����܂�
				// �ʏ�� ImageProxy �Ɏw�肵�����̂Ɠ����l���w�肵�܂�
                NNS_G2D_VRAM_ADDR_NONE ,		// �e�N�X�`���]����I�t�Z�b�g�g�p���܂���
                NNS_G2dGetImageLocation(&pWork->ImageProxy, NNS_G2D_VRAM_TYPE_2DMAIN),      // ���C����ʃL�����N�^�]����I�t�Z�b�g
                NNS_G2dGetImageLocation(&pWork->ImageProxy, NNS_G2D_VRAM_TYPE_2DSUB),		// �T�u��ʃL�����N�^�]����I�t�Z�b�g
                pCharData->pRawData,  // �L�����N�^�f�[�^
                NULL,				  // �e�N�X�`���f�[�^
                pCharData->szByte     // �e�N�X�`���f�[�^ or �L�����N�^�f�[�^�̃T�C�Y
            );
}

//-----------------------------------------------------------------------------
/**
 *@brief			�}���`�Z���A�j���[�V�������\�z
 *					������s���O�ɃZ���A�j���[�V�����̍\�z���K�v
 *
 *@param	pWork�F����\����
 *
 *@return	none
 *
 */
 //----------------------------------------------------------------------------
static void MakeMultiCellAnm( CLACT_WORK* pWork, int heap )
{
	CLACT_MULTICELL_ANIM_DATA*	pCell;			// �Z���f�[�^���擾
	const NNSG2dMultiCellAnimSequence* pSequence;
    u16 numNodes;


	//
	// �Z���f�[�^���擾
	//
	pCell = (CLACT_MULTICELL_ANIM_DATA*)&pWork->AnmData;

	
	// �Đ�����V�[�P���X���擾
	pSequence = NNS_G2dGetAnimSequenceByIdx( pCell->pMCABank, 0 );

	// ���̃}���`�Z���̊e�V�[�P���X�ɕK�v�ȃm�[�h�̍ő吔���擾
	numNodes = NNS_G2dGetMCBankNumNodesRequired( pCell->pMCBank );
	
	// �q�[�v���� numNode �Ԃ�� NNSG2dNode �� NNSG2dCellAnimation ���擾
    pCell->pNode     = sys_AllocMemory( heap, sizeof(NNSG2dNode) * numNodes );
    pCell->pCellAnim = sys_AllocMemory( heap, sizeof(NNSG2dCellAnimation) * numNodes );

	
	
	//
	// �}���`�Z���A�j���[�V�����R���g���[�����\�z
	// 
    NNS_G2dInitMCAnimation( (NNSG2dMultiCellAnimation*)&pCell->AnmCtrl,	// �}���`�Z���A�j���[�V����
                            pCell->pNode,			// �m�[�h�z��
                            pCell->pCellAnim,		// �Z���A�j���[�V�����z��
                            numNodes,				// �m�[�h��
                            pCell->pAnimBank,		// �A�j���[�V�����f�[�^�o���N
                            pCell->pCellBank,		// �Z���f�[�^�o���N
                            pCell->pMCBank );		// �}���`�Z���f�[�^�o���N


	// �}���`�Z���A�j���[�V�����ɍĐ�����V�[�P���X���Z�b�g
    NNS_G2dSetAnimSequenceToMCAnimation(
                (NNSG2dMultiCellAnimation*)&pCell->AnmCtrl,
                pSequence );

}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�p���b�g�v���N�V�̂���p���b�g�i���o�[���擾����
 *
 *@param	pPltt�F�p���b�g�i���o�[���擾����p���b�g�v���N�V
 *@param	vramType�F���C���ʂ��T�u�ʂ�
 *
 *@return	�p���b�g�i���o�[
 *
 */
//-----------------------------------------------------------------------------
static u32 GetPlttProxyOffset( const NNSG2dImagePaletteProxy* pPltt, u32 vramType )
{
	u32 size;			// �P�p���b�g�T�C�Y
	u32 pltt_offset;	// �p���b�g�i���o�[�v�Z�����p
	
	// �g���p���b�g���`�F�b�N
	if( pPltt->bExtendedPlt ){
		size = PLTT_ONE_SIZE * 16;
	}else{
		// �W����256�łȂ����`�F�b�N
		if( pPltt->fmt == GX_TEXFMT_PLTT256 ){
			// 256�̎��̓T�C�Y���O�ɂ��Čv�Z���Ȃ�
			size = 0;
		}else{
			size = PLTT_ONE_SIZE;
		}
	}

	// �W���Q�T�U�F�ȊO���`�F�b�N
	if( size != 0 ){
		// ���炷�l�擾
		pltt_offset = NNS_G2dGetImagePaletteLocation( pPltt, vramType );
		pltt_offset /= size;			// ���炷�l�ɂ���(���p���b�g���炷��)
	}else{
		pltt_offset = 0;
	}

	return pltt_offset;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�����_���[���g�p�������x�ȕ`��
 *
 *@param	pClActSet	�Z���A�N�^�[�Z�b�g
 *@param	act			�A�N�^�[�|�C���^
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void renderDraw(const CLACT_SET* pClActSet, CLACT_WORK* act)
{
	
	VecFx32	matrix = act->Matrix;
	
	// �v���L�V�o�^
	NNS_G2dSetRendererImageProxy( pClActSet->pRender, &act->ImageProxy, &act->PaletteProxy );
	
	NNS_G2dBeginRendering( pClActSet->pRender );		// �`��J�n
	
	// �`��
	NNS_G2dPushMtx();{

		// �A�t�B���ϊ��@�t���b�v���[�h�ݒ�
		// �A�t�B���ϊ��ݒ�
		NNS_G2dSetRndCoreAffineOverwriteMode(
				&( pClActSet->pRender->rendererCore ),
				act->affin );
		
		if(act->affin == CLACT_AFFINE_NONE){
			// �t���b�v�ݒ�
			NNS_G2dSetRndCoreFlipMode(
					&( pClActSet->pRender->rendererCore ),
					act->flip & CLACT_FLIP_H,
					act->flip & CLACT_FLIP_V);
		}else{
			// �t���b�v�ݒ�
			NNS_G2dSetRndCoreFlipMode(
					&( pClActSet->pRender->rendererCore ),
					FALSE,
					FALSE );
		}
		
		
		NNS_G2dTranslate( matrix.x, matrix.y, matrix.z );
		
		if(act->affin != CLACT_AFFINE_NONE){
			NNS_G2dTranslate( act->AffineMatrix.x, act->AffineMatrix.y, act->AffineMatrix.z );
			NNS_G2dScale( act->Scale.x, act->Scale.y, act->Scale.z );
			NNS_G2dRotZ( FX_SinIdx(act->Rotation), FX_CosIdx(act->Rotation) );
			NNS_G2dTranslate( -act->AffineMatrix.x, -act->AffineMatrix.y, -act->AffineMatrix.z );
		}

	
		// �I�[�o�[���C�g�L���t���O�ݒ�
		NNS_G2dSetRendererOverwriteEnable( pClActSet->pRender, act->over_write );

		// �I�[�o�[���C�g�����t���O�ݒ�
		NNS_G2dSetRendererOverwriteDisable( pClActSet->pRender, ~act->over_write );
		
		// �p���b�g�i���o�[�ݒ�
		NNS_G2dSetRendererOverwritePlttNo( pClActSet->pRender, act->palNo );
		
		// �p���b�g�I�t�Z�b�g�ݒ�
		NNS_G2dSetRendererOverwritePlttNoOffset( pClActSet->pRender, act->palOfs );

		// �I�[�o�[���C�g�Ƀ��U�C�N�̒l��ݒ�
		NNS_G2dSetRendererOverwriteMosaicFlag( pClActSet->pRender, act->mosaic );

		// �I�[�o�[���C�g��OBJ���[�h�̒l��ݒ�
		NNS_G2dSetRendererOverwriteOBJMode( pClActSet->pRender, act->objmode );

		// BG�D�揇�ʂ�ݒ�
		NNS_G2dSetRendererOverwritePriority( pClActSet->pRender, act->Priority );
		
		// �Z���A�j�����}���`�Z�����ɂ߂��`�F�b�N
		if( (act->flag == CLACT_CELL) || (act->flag == CLACT_VRAM_CELL) ){
			CLACT_ANIM_DATA* anim = (CLACT_ANIM_DATA*)&act->AnmData;
			
			// �`��
			NNS_G2dDrawCellAnimation( &anim->AnmCtrl );
		}
		else{
			CLACT_MULTICELL_ANIM_DATA* anim = (CLACT_MULTICELL_ANIM_DATA*)&act->AnmData;

			// �`��
			NNS_G2dDrawMultiCellAnimation( &anim->AnmCtrl );
		}
	}
	NNS_G2dPopMtx();
	NNS_G2dEndRendering();					// �`��I��
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�`�悵�Ȃ�
 *
 *	@param	pClActSet		�Z���A�N�^�[�Z�b�g
 *	@param	act				�Z���A�N�^�[
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void noDraw( const CLACT_SET* pClActSet, CLACT_WORK* act )
{
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�I�[�g�A�j���[�V����
 *
 *	@param	act			�A�N�^�[
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void autoAnm( CLACT_WORK* act )
{
	// �A�j���[�V����
	CLACT_AnmFrameChg( act, act->Frame );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�I�[�g�A�j���[�V�����Ȃ�
 *
 *	@param	act		�A�N�^�[
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void noAnm( CLACT_WORK* act )
{
}

/*-----------------------------------------------------------------------------
 *
 *		���X�g����
 * 
 *===========================================================================*/
//-----------------------------------------------------------------------------
/**
 *@brief			���X�g�ɒǉ�
 *
 *@param	cs			�Z���A�N�^�[�Z�b�g
 *@param	pWork		�ǉ�����Z���A�N�^�[�f�[�^
 *
 *@return	none
 *
 *
 */
 //----------------------------------------------------------------------------
static void addCellActList( CLACT_SET* cs, CLACT_WORK* pWork )
{
	CLACT_WORK* p_work;		// ���[�v�p
	
	
	// �擪���J���Ă��邩�`�F�b�N
	if(cs->Dummy.pNext == &cs->Dummy){
		
		cs->Dummy.pNext	= pWork;
		cs->Dummy.pLast	= pWork;
		pWork->pLast			= &cs->Dummy;
		pWork->pNext			= &cs->Dummy;
	}else{
		
		// �Ō�̃f�[�^�̗D�揇�ʂ������̗D�揇�ʈȉ��Ȃ�Ō�ɃZ�b�g
		if(cs->Dummy.pLast->DrawPriority <= pWork->DrawPriority){
			
			pWork->pLast			= cs->Dummy.pLast;
			cs->Dummy.pLast->pNext	= pWork;
			pWork->pNext			= &cs->Dummy;
			cs->Dummy.pLast			= pWork;
		}else{
		
			// �����̗D�揇�ʂ��傫���f�[�^�̑O�ɒǉ�
			p_work = cs->Dummy.pNext;		// �擪�f�[�^�Z�b�g
			while(p_work != &cs->Dummy){		// �_�~�[�f�[�^�ɂȂ�܂�
				// p_work�̗D�揇�ʂ�pWork�̗D�揇�ʂ�葽���Ƃ�
				// p_work�̑O�ɓo�^����
				if(p_work->DrawPriority > pWork->DrawPriority){

					p_work->pLast->pNext	= pWork;
					pWork->pLast			= p_work->pLast;
					p_work->pLast			= pWork;
					pWork->pNext			= p_work;
					break;
				}

				p_work = p_work->pNext;
			}
		}
	}
}

//-----------------------------------------------------------------------------
/**
 *@brief			���X�g����폜
 *
 *@param	pWork		�폜����Z���A�N�^�[�f�[�^
 *
 *@return	none
 *
 *
 */
 //----------------------------------------------------------------------------
static void dellCellActList( CLACT_WORK* pWork )
{
	// ���X�g���O��
	pWork->pLast->pNext = pWork->pNext;
	pWork->pNext->pLast = pWork->pLast;
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
static void initStack(CLACT_SET* pSet)
{
	int i;

	// ������
	for (i=0; i<pSet->WorkNum; i++) {
		CLACT_WorkClear(&pSet->pWork[i]);
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
static CLACT_WORK* popStack(CLACT_SET* pSet)
{
	CLACT_WORK*	ret;
	
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
static BOOL pushStack(CLACT_SET* pSet, CLACT_WORK* pDat)
{
	if(pSet->WorkStackNow <= 0){	// �󂫃`�F�b�N
		return FALSE;
	}
	CLACT_WorkClear(pDat);
	pSet->WorkStackNow--;
	pSet->ppWorkStack[pSet->WorkStackNow] = pDat;

	return TRUE;
}
