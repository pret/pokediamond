//==============================================================================
/**
 * @file	battle_input.h
 * @brief	�퓬���͉�ʏ����̃w�b�_
 * @author	matsuda
 * @date	2005.10.12(��)
 */
//==============================================================================
#ifndef __BATTLE_INPUT_H__
#define __BATTLE_INPUT_H__

#include "battle/battle_common.h"


//==============================================================================
//	�^��`
//==============================================================================
///BI_PARAM�̕s��`�|�C���^
typedef struct _BI_PARAM * BI_PARAM_PTR;


//==============================================================================
//	�萔��`
//==============================================================================
///�\��BG�^�C�v(��BgMakeData�ƕ��т𓯂��ɂ��Ă������ƁI�I)
enum{
	BINPUT_TYPE_WALL,	///<��
//	BINPUT_TYPE_WALL_MISSING_PLAYER,	///<��l���L���������Ȃ���
	BINPUT_COMMAND_IN,		///<�X���C�h�C�����Ă���R�}���h�I�����
	BINPUT_COMMAND_IN_2,	///<2�̖�(����)�̃X���C�h�C�����Ă���R�}���h�I�����
	BINPUT_TYPE_A,
	BINPUT_TYPE_A_2,		///<2�̖�(����)�̃R�}���h�I�����
	BINPUT_COMMAND_IN_FIGHTONLY,		///<�u���������v�݂̂̃X���C�h�C�����Ă���R�}���h�I�����
	BINPUT_TYPE_FIGHTONLY,		///<�u���������v�݂̂̃R�}���h�I�����
	BINPUT_COMMAND_IN_SAFARI,
	BINPUT_TYPE_A_SAFARI,
	BINPUT_COMMAND_IN_PARK,	///<�|�P�p�[�N�p�̃X���C�h�C�����Ă���R�}���h�I�����
	BINPUT_TYPE_PARK,		///<�|�P�p�[�N�p�̃R�}���h�I�����
	BINPUT_TYPE_WAZA,		///<�Z�I��
	BINPUT_TYPE_POKE,		///<�ΏۑI��
	BINPUT_TYPE_YESNO,		///<�u�͂��v�u�������v�I��
	BINPUT_TYPE_WASURERU,	///<�Z�Y��
	BINPUT_TYPE_AKIRAMERU,	///<�Z������߂�
	BINPUT_TYPE_NEXT_POKEMON,	///<���̃|�P�������g��
	BINPUT_TYPE_CHANGE_POKEMON,	///<�|�P���������ւ���
};

///�|�P�����I��A���^�C�v
///ABC�̂悤�ɑ����ď����Ă���̂͘A���I���AA_B_C�̂悤�ɃA���_�[�o�[�������Ă���̂͒P�ƑI��
enum{
	POKESELE_A_B_C_D,	//c
	POKESELE_BD,		//f
	POKESELE_BCD,		//g
	POKESELE_ABCD,		//h
	POKESELE_A,			//i
	POKESELE_AC,		//j
	POKESELE_C,			//k
	POKESELE_ABD,		//l
	POKESELE_B_C_D,		//m
	POKESELE_A_B_D,		//n
	POKESELE_A_C,		//o
	POKESELE_B_D,		//2006.07.29(�y) �ǉ�
};

///�ǎ��̃X�N���[��IN���Ă��鎞�̑��x(����8�r�b�g����)
#define BIN_PLAYER_SCROLL_SP_X		(-0xd00)

///�퓬���͉�ʁF�w�i�t�F�[�h
enum{
	BINPUT_BACKFADE_LIGHT,		///<���邭����
	BINPUT_BACKFADE_DARK,		///<�Â�����
};

///�莝���{�[���̃A�j���V�[�P���X�ԍ�
enum{
	STOCK_ANMSEQ_NONE = 0,		///<�|�P���������Ȃ�
	STOCK_ANMSEQ_ALIVE = 1,		///<�|�P����������(�����Ă���)
	STOCK_ANMSEQ_DEAD = 3,		///<�|�P����������(�C��)
	STOCK_ANMSEQ_NG = 2,		///<�|�P����������(�X�e�[�^�X�ُ�)
};


//==============================================================================
//	�\���̒�`
//==============================================================================
//--------------------------------------------------------------
//	
//--------------------------------------------------------------
///�Z�I����ʍ\���p�̃f�[�^
typedef struct{
	u16	wazano[WAZA_TEMOTI_MAX];
	u16	pp[WAZA_TEMOTI_MAX];
	u16	ppmax[WAZA_TEMOTI_MAX];
}BINPUT_WAZA_PARAM;


//==============================================================================
//	�O���֐��錾
//==============================================================================
extern void BINPUT_DefaultFrameSet(GF_BGL_INI *bgl);
extern void BINPUT_FrameExit(GF_BGL_INI *bgl);
extern void * BINPUT_SystemInit(BATTLE_WORK *bw, int sex);
extern void BINPUT_CreateBG(BI_PARAM_PTR bip, int select_bg, int force_put, void *scene_work);
extern void BINPUT_SystemFree(BI_PARAM_PTR bip);
extern int BINPUT_TouchCheck(BI_PARAM_PTR bip);
extern BOOL BINPUT_EffectEndCheck(BI_PARAM_PTR bip);
extern void BINPUT_StockBallActorResourceLoad(BI_PARAM_PTR bip);
extern void BINPUT_StockBallAnimeUpdate(BI_PARAM_PTR bip, u8 stock_mine[], u8 stock_enemy[]);
extern void BINPUT_StockBallON(BI_PARAM_PTR bip);
extern void BINPUT_StockBallOFF(BI_PARAM_PTR bip);
extern int BINPUT_RangeBgTypeGet(int range, int client_type);
extern void BINPUT_PlayerBG_SetX(BI_PARAM_PTR bip, int x);
extern void BINPUT_PlayerBG_ScrollX(BI_PARAM_PTR bip, int sp_x, int end_x);
extern void BINPUT_PlayerBG_MaskWindow(BI_PARAM_PTR bip);
extern void BINPUT_EffBGWallSet(BI_PARAM_PTR bip);
extern void BINPUT_BackFadeReq(BI_PARAM_PTR bip, int fade_dir);
extern BOOL BINPUT_BackFadeExeCheck(BI_PARAM_PTR bip);
extern void BINPUT_TemotiMotivationParamSet(BI_PARAM_PTR bip, const u8 *motivation);
extern int BINPUT_CursorDecendGet(BI_PARAM_PTR bip);
extern void BINPUT_CursorDecendSet(BI_PARAM_PTR bip, int decend_key);
extern void BINPUT_DefaultDataSet(BI_PARAM_PTR bip);
extern void BINPUT_DefaultDataFree(BI_PARAM_PTR bip);
extern void BINPUT_WazaParaMemoryDecord(BI_PARAM_PTR bip, int client_type, 
	const BINPUT_WAZA_PARAM *wazapara);



#endif	//__BATTLE_INPUT_H__

