//=============================================================================================
/**
 * @file	tcb.c
 * @brief	�ėp�^�X�N���䃂�W���[���{��
 * @author	tamada(GAME FREAK Inc.)
 * @date	2005.10.06
 * @since	2003.01.20
 *
 * @data	2004.10.14 AGB -> NDS
 * @author	Hiroyuki Nakamura
 *
 * @date	2005.10.06
 */
//=============================================================================================
#include <nitro.h>
#include "tcb.h"
#include "heapsys.h"
#include "assert.h"

//=============================================================================================
//	
//=============================================================================================
#define TASK_ADDPROC_CHECK		///< ���̃t���O���L�����ƁATCB_Add ���쒆�Ɋ��荞�݂�TCB_Main���Ă΂ꂽ���A�������s��Ȃ��B



//=============================================================================================
//	��`
//=============================================================================================
enum{
	TCB_ENABLE = 0,
	TCB_DISABLE = 1,
};

//------------------------------------------------------------------
/** @brief	TCB�\���̂̒�`
 *
 * TCB�\���̂́A����D�揇�ʂɏ]���ă����N�����B
 * ���̂��ߑo���������N���\������悤�ɑO��ւ̃|�C���^�����B
 *
 * �܂��A���ꂼ��̎��ۂ̏����ɕK�v�ȃ��[�N�G���A�͎������A
 * TCB�o�^���Ɏg�p���郏�[�N�G���A�������Ƃ��ēn���B
 *
 * ���[�U�[���x���ł͎Q�Ƃ���K�v�̂Ȃ������o�ւ̃A�N�Z�X�𐧌����邽�߁A
 * ���̍\���̂̓��W���[�������炵���A�N�Z�X�ł��Ȃ��B
 * �K�v�ȕ����̓A�N�Z�X�֐����o�R����悤�ɂȂ��Ă���B
 */
//------------------------------------------------------------------
typedef struct _TCB {
	TCBSYS* sys;				///<�������Ǘ����Ă���TCB�V�X�e���ւ̃|�C���^
	TCB_PTR prev;				///<�O��TCB�ւ̃|�C���^
	TCB_PTR next;				///<����TCB�ւ̃|�C���^
	u32 pri;					///<�v���C�I���e�B
	void * work;				///<���[�N�G���A�ւ̃|�C���^
	TCB_FUNC func;				///<���s�֐��ւ̃|�C���^

	u32 sw_flag;				///<�֐��ǉ��t���O
}TCB;	// 52 bytes


typedef struct _TCBSYS {
	u16			tcb_max;		///< �o�^�\��TCB�̍ő吔
	u16			tcb_stack_ptr;	///< ���M�������Ă���TCB�p�X�^�b�N�̃|�C���^
	TCB			tcb_first;		///< TCB�擪����
	TCB_PTR*	tcb_stack;		///< TCB�p�X�^�b�N
	TCB*		tcb_table;		///< TCB���̃e�[�u��
	BOOL		adding_flag;	///< TCB�ǉ��������s���t���O�i���̃t���O�������Ă���Ԃ�Main�����s���Ȃ��j


	TCB_PTR		now_chain;		///< ���C�����[�v������g�p�A�������ێ�TCB�|�C���^
	TCB_PTR		next_chain;		///< ���C�����[�v������g�p�A�������ێ�TCB�|�C���^
}TCBSYS;	// 68 bytes


//==============================================================
// Prototype
//==============================================================
static void TCB_WorkClear( TCBSYS* tcbsys, TCB_PTR tcb);
static void InitTCBStack( TCBSYS* tcbsys );
static TCB * PopTCB( TCBSYS* tcbsys );
static int PushTCB( TCBSYS* tcbsys, TCB * tcb );
static TCB_PTR AddTask( TCBSYS* tcbsys, TCB_FUNC func, void* work, u32 pri );


//=============================================================================================
//
//	���[�J���֐�
//
//=============================================================================================
//------------------------------------------------------------------
/**
 * @brief	TCB�\���̂̏�����
 *
 * TCB�̃����o�ϐ�������������
 * ���֐��łƃ}�N���ł�����܂�
 *
 * @param	tcb	TCB�ւ̃|�C���^
 * @return	none	
 */
//------------------------------------------------------------------
#define TCBWorkClear(psys,ptcb)			\
{										\
	(ptcb)->sys = (psys);				\
	(ptcb)->prev = 						\
	(ptcb)->next = &(psys->tcb_first);	\
										\
	(ptcb)->pri = 0;					\
	(ptcb)->work = NULL;				\
	(ptcb)->func = NULL;				\
}

static void TCB_WorkClear( TCBSYS* tcbsys, TCB_PTR tcb)
{
	tcb->sys = tcbsys;

	tcb->prev = 
	tcb->next = &(tcbsys->tcb_first);

	tcb->pri = 0;
	tcb->work = NULL;
	tcb->func = NULL;
}
//------------------------------------------------------------------
/**
 * @brief	TCB�X�^�b�N������
 *
 * ���g�pTCB��ێ�����X�^�b�N������������
 */
//------------------------------------------------------------------
static void InitTCBStack( TCBSYS* tcbsys )
{
	int i;

	for( i=0; i<tcbsys->tcb_max; i++ )
	{
		TCB_WorkClear( tcbsys, &(tcbsys->tcb_table[i]) );
		tcbsys->tcb_stack[i] = tcbsys->tcb_table + i;
	}
	tcbsys->tcb_stack_ptr = 0;
}

//------------------------------------------------------------------
/**
 * @brief	TCB�X�^�b�N����̎��o��
 *
 * @retval	NULL�ȊO	TCB�ւ̃|�C���^
 * @retval	NULL		���o���Ɏ��s�i�X�^�b�N���󂾂����ꍇ�j
 */
//------------------------------------------------------------------
static TCB * PopTCB( TCBSYS* tcbsys )
{
	TCB_PTR tcb;
	if(tcbsys->tcb_stack_ptr == tcbsys->tcb_max)
	{
		return NULL;
	}
	tcb = tcbsys->tcb_stack[ tcbsys->tcb_stack_ptr ];
	tcbsys->tcb_stack_ptr++;
	return tcb;
}

//------------------------------------------------------------------
/**
	@brief	TCB�X�^�b�N�ւ̃v�b�V��

	@param	tcb		�v�b�V������TCB�̃|�C���^
	@retval	TRUE	����
	@retval	FALSE	���s�i�X�^�b�N�������ς��̏ꍇ�j
*/
//------------------------------------------------------------------
static int PushTCB( TCBSYS* tcbsys, TCB * tcb )
{
	if(tcbsys->tcb_stack_ptr == 0)
	{
		return FALSE;
	}
	TCBWorkClear( tcbsys, tcb );	//�l���N���A���Ă���X�^�b�N�ɐς�
	tcbsys->tcb_stack_ptr--;
	tcbsys->tcb_stack[ tcbsys->tcb_stack_ptr ] = tcb;
	return TRUE;
}


//=============================================================================================
//
//	���J�֐�
//
//=============================================================================================

//------------------------------------------------------------------
/**
 * TCB �V�X�e�����\�z����̂ɕK�v�ȃ������ʂ��v�Z
 *
 * @param   task_max		�ғ��ł���ő�^�X�N��
 *
 * @retval  u32		�������T�C�Y�i�o�C�g�P�ʁj
 */
//------------------------------------------------------------------
u32 TCBSYS_CalcSystemWorkSize( u32 task_max )
{
	return sizeof(TCBSYS) + (sizeof(TCB_PTR)+sizeof(TCB)) * task_max;
}

//------------------------------------------------------------------
/**
 * TCB�V�X�e�����쐬
 *
 * @param   task_max		�ғ��ł���ő�^�X�N��
 * @param   work_area		�V�X�e���쐬�ɕK�v�[���ȃT�C�Y�̃��[�N�G���A�A�h���X
 *
 * @retval  TCBSYS*		�쐬���ꂽTCB�V�X�e���|�C���^
 *
 * work_area �ɕK�v�ȃT�C�Y�́ATCBSYS_CalcSystemWorkSize �Ōv�Z����B
 */
//------------------------------------------------------------------
TCBSYS*  TCBSYS_Create( u32 task_max, void* work_area )
{
	TCBSYS* tcbsys;

	GF_ASSERT( work_area );

	tcbsys = work_area;

	tcbsys->tcb_stack = (TCB_PTR*) ((u8*)(tcbsys) + sizeof(TCBSYS));
	tcbsys->tcb_table = (TCB*) ((u8*)(tcbsys->tcb_stack) + sizeof(TCB_PTR)*task_max);

	tcbsys->tcb_max = task_max;
	tcbsys->tcb_stack_ptr = 0;
	tcbsys->adding_flag = FALSE;

	TCBSYS_Init( tcbsys );

	return tcbsys;
}

//------------------------------------------------------------------
/**
 *	�V�X�e���g�p�O�̏�����
 */
//------------------------------------------------------------------
void TCBSYS_Init( TCBSYS* tcbsys )
{
	//�X�^�b�N�̏�����
	InitTCBStack( tcbsys );
	//�擪�u���b�N�̏�����
	TCBWorkClear( tcbsys, &tcbsys->tcb_first );

	tcbsys->now_chain = tcbsys->tcb_first.next;
}

//------------------------------------------------------------------
//	TCB���C��
//------------------------------------------------------------------
void TCBSYS_Main( TCBSYS* tcbsys )
{
	#ifdef TASK_ADDPROC_CHECK
	if( tcbsys->adding_flag )
	{
		return;
	}
	#endif

	tcbsys->now_chain = tcbsys->tcb_first.next;	//���������s�̎n�߂̏ꏊ
	while (tcbsys->now_chain != &(tcbsys->tcb_first))
	{
		//���s�֐����Ńu���b�N���폜���ꂽ���p�ɃA�h���X��ۑ�
		tcbsys->next_chain = tcbsys->now_chain->next;

		if(tcbsys->now_chain->sw_flag == TCB_ENABLE){//�o�^����̓���������
			if(tcbsys->now_chain->func != NULL){
				tcbsys->now_chain->func(tcbsys->now_chain, tcbsys->now_chain->work);
			}
		}else{
			tcbsys->now_chain->sw_flag = TCB_ENABLE;
		}
		tcbsys->now_chain = tcbsys->next_chain;	//���̘A����
	}
	tcbsys->now_chain->func = NULL;
}

//------------------------------------------------------------------------------
/**
	@brief	TCB��ǉ�����
	@param	tcbsys	TCB�V�X�e���|�C���^
	@param	func	TCB_FUNC:�֘A�t������s�֐��|�C���^
	@param	work	void*:�֘A�t���郏�[�N�G���A�ւ�void�^�|�C���^
	@param	pri		u32:�^�X�N�v���C�I���e�B

	@return	TCB_PTR	�ǉ�����TCB�������|�C���^
*/
//------------------------------------------------------------------------------
TCB_PTR TCBSYS_AddTask( TCBSYS* tcbsys, TCB_FUNC func, void* work, u32 pri )
{
	TCB_PTR  ret;

	tcbsys->adding_flag = TRUE;
	ret = AddTask( tcbsys, func, work, pri );
	tcbsys->adding_flag = FALSE;
	return ret;

}
//------------------------------------------------------------------
/**
 * TCB�ǉ�����
 *
 * @param   tcbsys		TCB�V�X�e���|�C���^
 * @param   func		TCB�Ɋ֘A�t����֐��|�C���^
 * @param   work		TCB�Ɋ֘A�t���郏�[�N�G���A�ւ̃|�C���^
 * @param   pri			�^�X�N�v���C�I���e�B
 *
 * @retval  TCB_PTR		�ǉ�����TCB�|�C���^
 */
//------------------------------------------------------------------
static TCB_PTR AddTask( TCBSYS* tcbsys, TCB_FUNC func, void* work, u32 pri )
{
	TCB_PTR get;
	TCB_PTR find;

	get = PopTCB( tcbsys );	//�󂢂Ă���TCB���E��
	if(get == NULL)
	{
		//�o�^���悤�Ƃ������^�X�N���Ȃ�����
		OS_TPrintf("ERR : TCB wasn't get!");
		return NULL;
	}

	//�p�����[�^���Z�b�g
	get->pri = pri;
	get->work = work;
	get->func = func;
	//����t���O�ݒ�
	if(tcbsys->now_chain->func != NULL){
		//����t���O�ݒ�(�ʂ̃^�X�N����ǉ�����悤�Ƃ��Ă���ꍇ�A�o�^����̓��������鏈��)
		if(tcbsys->now_chain->pri <= pri){
			get->sw_flag = TCB_DISABLE;
		}else{
			get->sw_flag = TCB_ENABLE;
		}
	}
	else{
		//�{�^�X�N�O����̓o�^
		get->sw_flag = TCB_ENABLE;
	}

	//���s���X�g�ɐڑ�(�����v���C�I���e�B�̎��ɂ́A��ɓo�^�����ق�����)
	for(find = tcbsys->tcb_first.next; find != &(tcbsys->tcb_first); find = find->next)
	{
		if(find->pri > get->pri){	//find�̑O��get���Ȃ���
			get->prev = find->prev;
			get->next = find;
			find->prev->next = get;
			find->prev = get;
			if(find == tcbsys->next_chain){
				tcbsys->next_chain = get;
			}
			return get;
		}
	}
	//�Ō�܂Ōq���Ƃ��낪������Ȃ���΍Ō�Ɍq��
	if(tcbsys->next_chain == &(tcbsys->tcb_first)){
		tcbsys->next_chain = get;
	}
	get->prev = tcbsys->tcb_first.prev;	//���܂ł̍Ō�
	get->next = &(tcbsys->tcb_first);	//�������Ō�
	tcbsys->tcb_first.prev->next = get;	//���܂ōŌゾ�����u���b�N�̎��͎���
	tcbsys->tcb_first.prev = get;		//���X�g�̍Ō���X�V
	return get;
}

//------------------------------------------------------------------------------
/**
	@brief	TCB����������
	@param	tcb		TCB�|�C���^
*/
//------------------------------------------------------------------------------
void TCBSYS_DeleteTask( TCB_PTR tcb )
{
	//�A���V�X�e���̎��̃����N�悪�폜�Ώۂ̏ꍇ�̏���
	if(tcb->sys->next_chain == tcb){
		tcb->sys->next_chain = tcb->next;	//�폜�Ώ�TCB�̎�TCB�֘A�������ړ�
	}
	//���X�g����폜
	tcb->prev->next = tcb->next;
	tcb->next->prev = tcb->prev;

	PushTCB( tcb->sys, tcb );
}


//==================================================================
//	TCB�A�N�Z�X�֐�
//==================================================================

//------------------------------------------------------------------
//TCB�̓���֐���؂�ւ���
//------------------------------------------------------------------
void TCB_ChangeFunc(TCB_PTR tcb, TCB_FUNC func)
{
	tcb->func = func;
}

//------------------------------------------------------------------
//TCB�̃��[�N�A�h���X�擾
//------------------------------------------------------------------
void * TCB_GetWork(TCB_PTR tcb)
{
	return tcb->work;
}

//------------------------------------------------------------------
//TCB�v���C�I���e�B�̎擾
//------------------------------------------------------------------
u32 TCB_GetPriority(TCB_PTR tcb)
{
	return tcb->pri;
}







