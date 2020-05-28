//==============================================================================
/**
 * @file	wsp_sample.c
 * @brief	�T�|�[�g�T���v��
 * @author	goto
 * @date	2005.07.14(��)
 *
 * �����ɐF�X�ȉ�����������Ă��悢
 *
 */
//==============================================================================

// -----------------------------------------
//
//	include
//
// -----------------------------------------
#include "common.h"				///< �K�{
#include "system/lib_pack.h"	///< �K�{
#include "we_def.h"
#include "west_sp.h"			///< �K�{
#include "wsp_sample.h"			///< xxx.c�ɑ΂���xxx.h�͕K�{

#include "wazatool.h"			///< �Z�G�t�F�N�g�x���֐��S
#include "we_tool.h"			///< 

#include "ball_effect.h"
#include "system/arc_tool.h"				///< �A�[�J�C�u�p
#include "system/arc_util.h"				///< �A�[�J�C�u�p

// -----------------------------------------
//
//	�������p
//
//		[ NORMAL_SAMPLE ]			�֐��Ăяo��
//		[ EFFECT_TCB_ADD_SAMPLE ]	�G�t�F�N�g�pTCB�o�^
//		[ SOUND_TCB_ADD_SAMLE ]		�T�E���h�pTCB�o�^
//		[ TCB_ADD_SAMPLE ]			�]����TCB�o�^
//
// -----------------------------------------



// =============================================================================
//
//
//	��[ NORMAL_SAMPLE ]		�֐��Ăяo�����@
//
//
// =============================================================================
//--------------------------------------------------------------
/**
 * @brief	�T���v���֐�
 *
 * @param	we_sys	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
typedef struct {
	BES_PTR bes;
} TSAMPLE;
void WestSp_Sample(WE_SYS_PTR we_sys)
{
	///< �P�Ȃ�֐��Ăяo���ł��B
}






// =============================================================================
//
//
//	��[ EFFECT_TCB_ADD_SAMPLE ] �G�t�F�N�gTCB�o�^���@
//
//
// =============================================================================
typedef struct {
	
	u8	seq;
	
	WE_SYS_PTR	ws;			///< ���[�U�[���p�ӂ��郏�[�N�ɕK�{�̃����o
	
} TEFFECT_TCB_SAMPLE;

// -------------------------------------------------------------
/*
 *	�o�^����TCB
 */
// -------------------------------------------------------------
static void Sample_EffectTCB(TCB_PTR tcb, void* work)
{
	TEFFECT_TCB_SAMPLE* wk = (TEFFECT_TCB_SAMPLE*)work;
	
	switch(wk->seq){
	case 0:
		///< �Ƃ肠����

		wk->seq++;
		break;

	case 1:
		///< �J������
		
		///< �G�t�F�N�g�p��TCB�́A���̊֐����Ăяo�����ƂŔj��
		///< �łȂ��ƁA�Ǘ�����Ă���G�t�F�N�g�Ǘ���������Ȃ�
		WEEffect_TCB_Delete(wk->ws, tcb);
		sys_FreeMemoryEz(wk);
		break;
	}
}

//--------------------------------------------------------------
/**
 * @brief	�G�t�F�N�g�p��TCB�쐬�T���v��
 *
 * @param	we_sys	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void WestSp_SampleEffectTCB(WE_SYS_PTR we_sys)
{
	TEFFECT_TCB_SAMPLE* wk;
	
	wk = sys_AllocMemory(HEAPID_BATTLE, sizeof(TEFFECT_TCB_SAMPLE));
	
	wk->seq = 0;
	wk->ws	= we_sys;
	
	WEEffect_TCB_Add(wk->ws, Sample_EffectTCB, wk, 0x1000);
}





// =============================================================================
//
//
//	��[ SOUND_TCB_ADD_SAMPLE ] �T�E���hTCB�o�^���@
//
//
// =============================================================================
typedef struct {
	
	u8	seq;
	
	WE_SYS_PTR	ws;			///< ���[�U�[���p�ӂ��郏�[�N�ɕK�{�̃����o
	
} TSOUND_TCB_SAMPLE;

// -------------------------------------------------------------
/*
 *	�o�^����TCB
 */
// -------------------------------------------------------------
static void Sample_SoundTCB(TCB_PTR tcb, void* work)
{
	TSOUND_TCB_SAMPLE* wk = (TSOUND_TCB_SAMPLE*)work;
	
	switch(wk->seq){
	case 0:
		///< �Ƃ肠����

		wk->seq++;
		break;
	case 1:
		///< �J������
		
		///< �T�E���h�p��TCB�́A���̊֐����Ăяo�����ƂŔj��
		///< �łȂ��ƁA�Ǘ�����Ă���T�E���h�Ǘ���������Ȃ�
		WESound_TCB_Delete(wk->ws, tcb);
		sys_FreeMemoryEz(wk);
		break;
	}
}

//--------------------------------------------------------------
/**
 * @brief	�T�E���h�p��TCB�쐬�T���v��
 *
 * @param	we_sys	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void WestSp_SampleSoundTCB(WE_SYS_PTR we_sys)
{
	TSOUND_TCB_SAMPLE* wk;
	
	wk = sys_AllocMemory(HEAPID_BATTLE, sizeof(TSOUND_TCB_SAMPLE));
	
	wk->seq = 0;
	wk->ws	= we_sys;

	WESound_TCB_Add(wk->ws, Sample_SoundTCB, wk, 0x1000);
}



// =============================================================================
//
//
//	��[ TCB_ADD_SAMPLE ] �ʏ�TCB�o�^���@
//
//
// =============================================================================
typedef struct {
	
	u8	seq;
	
	///< �ʏ��TCB�́AWE-SYS�Ɉˑ����Ȃ��̂Ŏ󂯎��Ȃ��Ă��ǂ�
	WE_SYS_PTR	ws;
	
} TTCB_SAMPLE;

// -------------------------------------------------------------
/*
 *	�o�^����TCB
 */
// -------------------------------------------------------------
static void Sample_TCB(TCB_PTR tcb, void* work)
{
	TTCB_SAMPLE* wk = (TTCB_SAMPLE*)work;
	
	switch(wk->seq){
	case 0:
		///< �Ƃ肠����

		wk->seq++;
		break;
	case 1:
		///< �j��
		
		///< �]����TCB�J�������ł悢
		TCB_Delete(tcb);
		sys_FreeMemoryEz(wk);
		break;
	}
}

//--------------------------------------------------------------
/**
 * @brief	�ʏ��TCB�쐬�T���v��
 *
 * @param	we_sys	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void WestSp_SampleTCB(WE_SYS_PTR we_sys)
{
	TTCB_SAMPLE* wk;
	
	wk = sys_AllocMemory(HEAPID_BATTLE, sizeof(TTCB_SAMPLE));
	
	wk->seq = 0;
	
	///< �g��Ȃ��̂ŁA�����o���̂��s�v �����ƌx���o�邯�ǥ��
	wk->ws = we_sys;
	
	///< �]����TCB�o�^���@�ōs��
	TCB_Add(Sample_TCB, wk, 0x1000);
}


// =============================================================================
//
//
//	��[ TCB_ADD_SAMPLE ] �ʏ�TCB�o�^���@
//
//
#define TOM		(100)
// =============================================================================
typedef struct {
	
	u8	seq;
	
	///< �ʏ��TCB�́AWE-SYS�Ɉˑ����Ȃ��̂Ŏ󂯎��Ȃ��Ă��ǂ�
	WE_SYS_PTR	ws;
	
	CATS_SYS_PTR csp;
	CATS_RES_PTR crp;
	
	CATS_ACT_PTR cap;
	
	CATS_ACT_PTR caps[TOM];
	
	CLACT_WORK_PTR act[10];
	
} TTCB_CAT_SAMPLE;

// -------------------------------------------------------------
/*
 *	�o�^����TCB
 */
static int err_flag = 0;
// -------------------------------------------------------------
static void Sample_CAT_TCB(TCB_PTR tcb, void* work)
{
	TTCB_CAT_SAMPLE* wk = (TTCB_CAT_SAMPLE*)work;
	
	switch(wk->seq){
	case 0:
		CATS_ObjectUpdate(wk->caps[0]->act);
		CATS_ObjectUpdate(wk->caps[1]->act);
		CATS_ObjectUpdate(wk->caps[2]->act);
		
		CATS_ObjectPosMove(wk->caps[0]->act, 1, 0);
		CATS_ObjectPosMove(wk->caps[1]->act, -1, 0);
		CATS_ObjectPosMove(wk->caps[2]->act, 1, 1);
			
		CATS_Draw(wk->crp);
		break;
	case 1:
		{
			WE_SYS_PTR wsp = wk->ws;
			CATS_ActorPointerDelete_S(wk->cap);
			sys_FreeMemoryEz(wk);
			WEEffect_TCB_Delete(wsp, tcb);
		}
		break;
	}
}

//--------------------------------------------------------------
/**
 * @brief	�ʏ��TCB�쐬�T���v��
 *
 * @param	we_sys	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void WestSp_CAT_SampleTCB(WE_SYS_PTR we_sys, CATS_SYS_PTR csp, CATS_RES_PTR crp, CATS_ACT_PTR cap)
{
	TTCB_CAT_SAMPLE* wk;
	TCATS_OBJECT_ADD_PARAM_S coap;
	
	wk = sys_AllocMemory(HEAPID_BATTLE, sizeof(TTCB_CAT_SAMPLE));
	
	GF_ASSERT(wk != NULL);
	
	wk->seq = 0;
	wk->csp = csp;
	wk->crp = crp;
	wk->cap = cap;

	wk->ws = we_sys;
	coap   = WeSysCoapGet(we_sys);

	wk->caps[0] = cap;
	{
		int i;
		
		for (i = 1; i < 3; i++){
			wk->caps[i] = CATS_ObjectAdd_S(wk->csp, wk->crp, &coap);
		}
	}

	WEEffect_TCB_Add(we_sys, Sample_CAT_TCB, wk, 0x1000);
}


