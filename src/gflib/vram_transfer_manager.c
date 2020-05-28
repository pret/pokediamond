//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *	H16/11/08		Tomoya Takahashi
 *
 *		Vram�]���}�l�[�W���[�̃^�X�N���Ǘ�����
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
#include <nitro.h>
#include <nnsys.h>
#include "system.h"
#include "vram_transfer_manager.h"
#include "assert.h"


//-------------------------------------
//	Vram�]���}�l�[�W��
//=====================================
typedef struct _VRAM_TRANSFER_MANAGER{
	u32						tasksNum;			// �o�^�\�^�X�N��
	u32						add_task_num;		// �^�X�N�o�^��
	NNSGfdVramTransferTask*	pTaskArray;			// �^�X�N�ϐ�
} VRAM_TRANSFER_MANAGER;


//----------------------------------------------------------------------------
/**
 *					�O���[�o���ϐ��錾
 */
//-----------------------------------------------------------------------------
static VRAM_TRANSFER_MANAGER* pVramTransferManager;

static BOOL CallbackRegistTransferTask( NNS_GFD_DST_TYPE type, u32 dstAddr, void* pSrc, u32 szByte );

//----------------------------------------------------------------------------
/**
 *
 *@brief	Vram�]���}�l�[�W���[�̏�����
 *
 *@param	tasks_num�F�o�^�\�^�X�N��
 *@param	heap		�g�p����q�[�v
 *
 *@return	none
 *
 *����ȊO�̓f�t�H���g�̊֐����g�p���Ă��������B
 *
 */
//-----------------------------------------------------------------------------
void initVramTransferManagerHeap( u32 tasks_num, int heap )
{
	// �����ς�
	GF_ASSERT( pVramTransferManager == NULL );


	// ���̍쐬
	pVramTransferManager = sys_AllocMemory( heap, sizeof(VRAM_TRANSFER_MANAGER) );
	// �������m�ێ��s
	GF_ASSERT( pVramTransferManager );
	
	//
	// �^�X�N�̈���m�ۂ��AVram�]���}�l�[�W���[�������� 
	//
	// �̈���m��
	pVramTransferManager->pTaskArray = (NNSGfdVramTransferTask*)sys_AllocMemory( heap, sizeof(NNSGfdVramTransferTask) * tasks_num );

	// �^�X�N������
	pVramTransferManager->tasksNum = tasks_num;
	pVramTransferManager->add_task_num = 0;

	// Vram�]���}�l�[�W���[��������
	NNS_GfdInitVramTransferManager( pVramTransferManager->pTaskArray, pVramTransferManager->tasksNum );
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	Vram�]���}�l�[�W���[�̔j��
 *
 *@param	none
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void DellVramTransferManager( void )
{
	// �j���ς�
	GF_ASSERT( pVramTransferManager != NULL );
	//
	//�^�X�N�̈��j�� 
	//
	// �̈��j��
	sys_FreeMemoryEz( pVramTransferManager->pTaskArray );

	sys_FreeMemoryEz( pVramTransferManager );
	pVramTransferManager = NULL;
}


//----------------------------------------------------------------------------
/**
 *
 *@brief	Vram�]���}�l�[�W���[�^�X�N��o�^
 *
 *@param	type		�f�[�^�]����̎��
 *@param	dstAddr		�]����A�h���X
 *@param	pSrc		�]�����f�[�^�ւ̃|�C���^
 *@param	szByte		�]���T�C�Y
 *
 *@retval	TRUE		����	
 *@retval	FALSE		���s
 *
 *
 */
//-----------------------------------------------------------------------------
BOOL AddVramTransferManager( NNS_GFD_DST_TYPE type, u32 dstAddr, void* pSrc, u32 szByte )
{	
	// ����������Ă��Ȃ�
	GF_ASSERT( pVramTransferManager );
	pVramTransferManager->add_task_num++;		// �^�X�N�����Z

	if(pVramTransferManager->add_task_num >= pVramTransferManager->tasksNum){	// �^�X�N�I�[�o�[�`�F�b�N
		GF_ASSERT(0&&("VramTransferManager�^�X�N�I�[�o�["));
		return FALSE;
	}

	return NNS_GfdRegisterNewVramTransferTask(type, dstAddr, pSrc, szByte);
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	���ۂɓ]������
 *
 *@param	none
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void DoVramTransferManager( void )
{
	if(pVramTransferManager){
		NNS_GfdDoVramTransfer();
		pVramTransferManager->add_task_num = 0;
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	���̃^�X�N�o�^�����擾
 *
 *@param	none
 *
 *@return	int		�^�X�N�o�^��
 *
 *
 */
//-----------------------------------------------------------------------------
int GetVramTransferManagerAddNum( void )
{
	// ����������Ă��Ȃ�
	GF_ASSERT( pVramTransferManager );
	return pVramTransferManager->add_task_num;
}


//----------------------------------------------------------------------------
/**
 *
 *@brief	�Z���]���}�l�[�W���̏�����
 *
 *@param	num		�ő�Z���o�^��
 *@param	heap	�g�p�q�[�v
 *	
 *@return	NNSG2dCellTransferState*	�m�ۂ����Z���]���o�b�t�@
 *
 *
 */
//-----------------------------------------------------------------------------
NNSG2dCellTransferState* InitCellTransfer(int num, int heap)
{
	NNSG2dCellTransferState* buff;

	// CellVram�]��������
	buff = sys_AllocMemory(heap, sizeof(NNSG2dCellTransferState)*num);
	
	NNS_G2dInitCellTransferStateManager(
				buff,
				num,
				CallbackRegistTransferTask          // <- (1)
			);

	return buff;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�Z���̃f�[�^��Vram�]���^�X�N�ɐݒ肷��
 *
 *@param	none
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void UpdateCellTransfer(void)
{
	// Vram�]���^�X�N��ݒ�
	NNS_G2dUpdateCellTransferStateManager();
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�Z���]���}�l�[�W����j��
 *
 *@param	data		�Z���]���f�[�^�o�b�t�@
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void DeleteCellTransfer(NNSG2dCellTransferState* data)
{
	sys_FreeMemoryEz(data);
}

//-----------------------------------------------------------------------------
/**
 *@brief				NNS_G2dDraw�֐������ŃL�����N�^�f�[�^�̓]���^�X�N��
 *							�o�^���邽�߂ɌĂ΂��֐�
 *
 *@param	type�F�]����Vram�̈���
 *@param	dstAddr�F�]����I�t�Z�b�g
 *@param	pStr�F�]�����f�[�^�ւ̃|�C���^
 *@param	szByte�F�]���T�C�Y
 *
 *@retval	�����FTRUE
 *@retval	���s�FFALSE
 *
 */
 //----------------------------------------------------------------------------
static BOOL CallbackRegistTransferTask( NNS_GFD_DST_TYPE type, u32 dstAddr, void* pSrc, u32 szByte )
{
	// VRAM �]���}�l�[�W���ɂ��̂܂ܓn��
    return AddVramTransferManager(
                type,
                dstAddr,
                pSrc,
                szByte );
}
