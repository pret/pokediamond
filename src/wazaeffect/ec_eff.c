//==============================================================================
/**
 * @file	ec_eff.c
 * @brief	�ȒP�Ȑ���������
 * @author	goto
 * @date	2006.01.17(��)
 *
 * �����ɐF�X�ȉ�����������Ă��悢
 *
 */
//==============================================================================

#include "common.h"
#include "system/lib_pack.h"
#include "system/fontproc.h"
#include "system/pm_str.h"

#include "str_tool.h"
#include "wazaeffect/we_mana.h"
#include "system/snd_tool.h"
#include "system/msgdata.h"

#include "spl.h"
#include "include/battle/battle_tcb_pri.h"
#include "effectdata/we_list.h"

#include "we_tool.h"
#include "we_def.h"
#include "we_sys.h"

#include "ec_eff.h"
#include "battle_particle.h"

#include "d_tool.h"

#include "wazatool.h"


// .h �֍s������
#include "wazaeffect/wp_tbl.h"


// -----------------------------------------
//
//	�� �V�X�e�����[�N
//
// -----------------------------------------
typedef struct _TEC_EFF_SYS {
	
	int				id;					///< �}�l�[�W���Ǘ��p
	int				heap_area;			///< HEAP_ID
	TEC_ADD_PARAM	param;				///< �O���擾�p�����[�^�[
	
	PTC_PTR			ptc;				///< PTC
	EMIT_PTR		emit;				///< EMIT	
	TCB_PTR			tcb;				///< ����TCB
	
	int				spr_num;			///< Spr�̐�
	BOOL			active;				///< ���s����
	
} TEC_EFF_SYS;

typedef struct _TEC_EFF_MANAGER {

	int				heap_area;			///< HEAP_ID
	TECM_ADD_PARAM	param;				///< �O���擾�p�����[�^�[
	
	ECE_PTR			ecp[ PARTICLE_GLOBAL_MAX ];	///< �G�t�F�N�g�Ǘ��p
	
} TEC_EFF_MANAGER;

static void ECE_MainTCB(TCB_PTR tcb, void* work);
static void ECE_EmitSet(ECE_PTR ecp, pEmitFunc callback);
static void ECE_CallBack(EMIT_PTR emit);
static int	ECE_SprNumGet(int eff_no);


// =============================================================================
//
//
//	�� �O���Q�Ɗ֐�
//
//
// =============================================================================
ECEM_PTR ECEM_Init(int heap_area, TECM_ADD_PARAM* ecmap)
{
	ECEM_PTR ecmp;
	
	ecmp = NULL;

	ecmp = sys_AllocMemory(heap_area, sizeof(TEC_EFF_MANAGER));
	
	if (ecmp == NULL){
		GF_ASSERT(0);
		return NULL;
	}
	DefaultBlendSet();
	
	ecmp->heap_area	= heap_area;
	
	if (ecmap != NULL){
		ecmp->param	= *ecmap;
	}
	
	{
		int i;
		
		for (i = 0; i < PARTICLE_GLOBAL_MAX; i++){
			ecmp->ecp[i] = NULL;
		}
	}
	
	return ecmp;
}


//--------------------------------------------------------------
/**
 * @brief	�}�l�[�W���[����ǂݍ���
 *
 * @param	ecmp	
 * @param	ecap	
 *
 * @retval	ECE_PTR	
 *
 */
//--------------------------------------------------------------
ECE_PTR ECEM_Load(ECEM_PTR ecmp, TEC_ADD_PARAM* ecap)
{
	int i;
	ECE_PTR ret = NULL;
	
	for (i = 0; i < PARTICLE_GLOBAL_MAX; i++){
		if (ecmp->ecp[i] != NULL){ continue; }
		
		ecmp->ecp[i] = ECE_Init(ecmp->heap_area, ecap);
		ecmp->ecp[i]->tcb = NULL;
		
		ret = ecmp->ecp[i];

		ret->id = i;
		
		break;
	}
	
	if (ret == NULL){
		GF_ASSERT(0);
	}
	
	return ret;
}


//--------------------------------------------------------------
/**
 * @brief	�}�l�[�W���[�̊Ǘ����� ECE_PTR���
 *
 * @param	ecmp	
 * @param	ecp	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void ECEM_ECE_Free(ECEM_PTR ecmp, ECE_PTR ecp)
{
	int i;
	
	for (i = 0; i < PARTICLE_GLOBAL_MAX; i++){
		if (ecp->id != i){ continue; }
		
		sys_FreeMemoryEz(ecmp->ecp[i]);
		ecmp->ecp[i] = NULL;
		
		return;
	}
	
	GF_ASSERT(0);
}

//--------------------------------------------------------------
/**
 * @brief	�}�l�[�W���[���
 *
 * @param	ecmp	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void ECEM_Free(ECEM_PTR ecmp)
{
	int i;
	
	for (i = 0; i < PARTICLE_GLOBAL_MAX; i++){

		if (ecmp->ecp[i] == NULL){ continue; }

		sys_FreeMemoryEz(ecmp->ecp[i]);
	}
	
	sys_FreeMemoryEz(ecmp);
}


//--------------------------------------------------------------
/**
 * @brief	�X�L�b�v
 *
 * @param	ecmp	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void ECEM_Skip(ECEM_PTR ecmp)
{
	int i;
	
	for (i = 0; i < PARTICLE_GLOBAL_MAX; i++){

		if (ecmp->ecp[i] == NULL){ continue; }
		
		Wp_Exit(ecmp->ecp[i]->ptc);
		
		if (ecmp->ecp[i]->active == FALSE){ continue; }
		
		if (ecmp->ecp[i]->tcb == NULL){ continue; }
	
		TCB_Delete(ecmp->ecp[i]->tcb);
	}	
}


//--------------------------------------------------------------
/**
 * @brief	ECE ������
 *
 * @param	ecap		�p�����[�^
 *
 * @retval	ECE_PTR		�V�X�e�����[�N
 *
 */
//--------------------------------------------------------------
ECE_PTR	ECE_Init(int heap_area, TEC_ADD_PARAM* ecap )
{
	ECE_PTR ecp;
	
	ecp == NULL;
	
	ecp = sys_AllocMemory(heap_area, sizeof(TEC_EFF_SYS));
	
	if (ecp == NULL){
		GF_ASSERT(0);
		return NULL;
	}
	
	ecp->heap_area	= heap_area;
	ecp->param		= *ecap;
	ecp->spr_num	= ECE_SprNumGet(ecp->param.eff_no);
	
	ecp->ptc		= Wp_Init(ecp->heap_area, ecp->param.eff_no, TRUE);
	
	return ecp;
}


//--------------------------------------------------------------
/**
 * @brief	ECE �Ăяo��
 *
 * @param	ecp			�V�X�e�����[�N
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void ECE_Call( ECE_PTR ecp )
{
	ecp->active = TRUE;
	
	ECE_EmitSet(ecp, ECE_CallBack);
	
	ecp->tcb	= TCB_Add(ECE_MainTCB, ecp, TCBPRI_BALL_EFFECT);	
}


//--------------------------------------------------------------
/**
 * @brief	ECE �I���`�F�b�N
 *
 * @param	ecp			�V�X�e�����[�N
 *
 * @retval	BOOL		TRUE	= ���s��
 *						FALSE	= ����I��
 *
 */
//--------------------------------------------------------------
BOOL ECE_EndCheck( ECE_PTR ecp )
{	
	return ecp->active;
}


//--------------------------------------------------------------
/**
 * @brief	ECE ���
 *
 * @param	ecp			�V�X�e�����[�N
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void ECE_Free( ECE_PTR ecp )
{
	sys_FreeMemoryEz(ecp);
}



// =============================================================================
//
//
//	�� �����Q�Ɗ֐�
//
//
// =============================================================================
//--------------------------------------------------------------
/**
 * @brief	TCB
 *
 * @param	tcb	
 * @param	work	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void ECE_MainTCB(TCB_PTR tcb, void* work)
{
	ECE_PTR wk	= (ECE_PTR)work;
	int		num	= 0;
	
	num = Particle_GetEmitterNum(wk->ptc);
	
	if (num != 0){ return; }
	
	wk->active = FALSE;
	
	Wp_Exit(wk->ptc);
	
	TCB_Delete(tcb);
}


//--------------------------------------------------------------
/**
 * @brief	Emitter / Camera �̐ݒ�
 *
 * @param	ecp	
 * @param	callback	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void ECE_EmitSet(ECE_PTR ecp, pEmitFunc callback)
{
	int i;

	for (i = 0; i < ecp->spr_num; i++){
		Particle_CreateEmitterCallback(ecp->ptc, i, callback, ecp);
	}

	Particle_CameraTypeSet(ecp->ptc, ecp->param.camera_type);
}


//--------------------------------------------------------------
/**
 * @brief	CallBack
 *
 * @param	emit	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void ECE_CallBack(EMIT_PTR emit)
{
	ECE_PTR ecp;
	
	ecp = Particle_GetTempPtr();
}


//--------------------------------------------------------------
/**
 * @brief	SprNumGet
 *
 * @param	eff_no	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static int ECE_SprNumGet(int eff_no)
{
	const int MaxSprTbl[] = {
		P_EC_001_1_SPAMAX,
		P_EC_001_2_SPAMAX,
		P_EC_002_1_SPAMAX,
		P_EC_002_2_SPAMAX,
		P_EC_003_1_SPAMAX,
		P_EC_003_2_SPAMAX,
		P_EC_004_1_SPAMAX,
		P_EC_004_2_SPAMAX,
		P_EC_005_1_SPAMAX,
		P_EC_005_2_SPAMAX,
		P_EC_006_1_SPAMAX,
		P_EC_006_2_SPAMAX,
		P_EC_007_1_SPAMAX,
		P_EC_007_2_SPAMAX,
		P_EC_008_1_SPAMAX,
		P_EC_008_2_SPAMAX,
		P_EC_009_1_SPAMAX,
		P_EC_009_2_SPAMAX,
		P_EC_010_1_SPAMAX,
		P_EC_010_2_SPAMAX,
		P_EC_011_1_SPAMAX,
		P_EC_011_2_SPAMAX,
	};
	
	int no;
	
	no = eff_no - ECE_DEF_SPA_START;
	
	if (no >= NELEMS(MaxSprTbl)){
		GF_ASSERT(0);
		return 0;
	}
	
	return MaxSprTbl[ no ];
}











