//==============================================================================
/**
 * @file	west_sp.c
 * @brief	�T�|�[�g�֐��p�t�@�C��
 * @author	goto
 * @date	2005.07.14(��)
 *
 * �����ɐF�X�ȉ�����������Ă��悢
 *
 */
//==============================================================================

#include "common.h"
#include "system/lib_pack.h"

#include "west_sp.h"

// -----------------------------------------
//
//	���T�|�[�g�֐��p�̃w�b�_�[�L�q
//		�T�|�[�g�֐��͂��̃\�[�X�ɂ͋L�q���Ȃ��ł�������
//
// -----------------------------------------

#include "wsp_sample.h"

#include "wsp.h"


// -----------------------------------------
//
//	���֐��e�[�u��
//		���̃e�[�u���ɃT�|�[�g�֐���ǉ����Ă��������B
//
// -----------------------------------------
static const pWeFunc WeSysSP_FuncTable[] = {

	WestSp_Sample,					///< �T���v��
	WestSp_SampleEffectTCB,			///< �G�t�F�N�gTCB�T���v��
	WestSp_SampleSoundTCB,			///< �T�E���hTCB�T���v��
	WestSp_SampleTCB,				///< �]����TCB�T���v��
	
	WestSp_EffectTCBPokeRota00,		///< ���Ŏg�p���܂��B�|�P������������]������^�X�N�ł��B
	WestSp_WE_070,					///< we_070
	WestSp_WE_339,					///< we_339
	WestSp_WE_104,					///< we_104
	WestSp_WE_098,					///< we_098
	WestSp_WE_065,					///< we_065
	WestSp_WE_066,					///< we_066
	WestSp_WE_093,					///< we_093
	WestSp_WE_151,					///< we_151
	WestSp_WE_074,					///< we_074
	WestSp_WE_096,					///< we_096
	WestSp_WE_100,					///< we_100
	WestSp_WE_148,					///< we_148
	WestSp_WE_101AT,				///< we_101AT
	WestSp_WE_101DF,				///< we_101DF
	WestSp_WE_150,					///< we_150
	WestSp_WE_180,					///< we_180
	WestSp_WE_106,					///< we_106
	WestSp_WE_107,					///< we_107
	WestSp_WE_185,					///< we_185
	WestSp_WE_089,					///< we_089
	WestSp_WE_204,					///< we_204
	WestSp_WE_171,					///< we_171
	WestSp_WE_175,					///< we_175
	WestSp_WE_222,					///< we_222
	WestSp_WE_216,					///< we_216
	WestSp_WE_233,					///< we_233
	WestSp_WE_207_MAIN,				///< we_207_MAIN
	WestSp_WE_262,					///< we_262
	WestSp_WE_HaikeiPalFade,		///< �w�i�p���b�g�t�F�[�h
	WestSp_WE_SSPPokePalFade,		///< �\�t�g�E�F�A�X�v���C�g�|�P�������p���b�g�t�F�[�h
	WestSp_WE_CAPPokeScaleUpDown,	///< �|�P�����X�P�[���A�b�v�_�E��
	WestSp_WE_T01,					///< tool �h�炵
	WestSp_WE_326DF,				///< 326�@�h�䑤����
	WestSp_WE_CAP_NormalAlphaFade,	///< 
	WestSp_WE_316,					///< we_316
	WestSp_WE_SSP_PokeVanish,		///< �\�t�g�E�F�A�X�v���C�g�̃|�P�����̃o�j�b�V����ݒ�
	WestSp_WE_252Back,				///< we_252
	WestSp_WE_SSPPokeScaleUpDown,	///< ssp�|�P��L�΂��Č��ɖ߂�
	WestSp_WE_252SSPPoke,
	WestSp_WE_T02,					///< tool �X�N���[��
	WestSp_WE_T22,					///< tool �X�N���[��
	WestSp_WE_224,					///< ���K�z�[��
	WestSp_WE_224AT,				///< ���K�z�[��
	WestSp_WE_224DF,				///< ���K�z�[��
	WestSp_WE_057,					///< �Ȃ݂̂�
	WestSp_WE_T03,					///< tool
	WestSp_WE_T04,					///< tool
	WestSp_WE_T05,					///< tool
	WestSp_WE_T06,					///< tool
	WestSp_WE_T07,					///< tool
	WestSp_WE_293,					///< �ق����傭
	WestSp_WE_T08,					///< tool
	WestSp_WE_T10,					///< tool
	WestSp_WE_102,					///< ���̂܂�
	WestSp_WE_325,					///< �V���h�[�p���`
	WestSp_WE_Kaiten,				///< ��]
	WestSp_WE_DispOut,				///< ��ʊO��
	WestSp_WE_DispDef,				///< �K��ʒu��
	WestSp_WE_OAM_PalFade,			///< OAM�̃p���b�g�t�F�[�h
	WestSp_WE_VisibleSet,			///< �ϕ\���V�X�e��
	WSP_Emitter_Straight,			///< �G�~�b�^�[�̒����ړ�
	WSP_Emitter_Parabolic,			///< �G�~�b�^�[�̕������ړ�
	WSP_RectView,					///< ��`��
	WestSp_WE_BgShake,				///< BG�h�炵
	WSP_Mosaic,						///< ���U�C�N
	WSP_272,						///< �Ȃ肫��
	WSP_289,						///< �悱�ǂ�
	WSP_Emitter_Rotation,			///< �G�~�b�^�[�̉�]
	WSP_Emitter_SimpleUD,			///< �ȒP�ȏ㏸���~
	WSP_PalColChange,				///< �p���b�g�ύX
	WSP_PokeOAM_View,				///< OAMView
	WestSp_WE_Laster,				///< ���X�^�[
	WestSp_WE_DispMove,				///< ��ʓ��O�ړ�
	WSP_AllPokeDrop,				///< �S�|�P����OAM��
	WSP_166,						///< �X�P�b�`
	
	// ---- �X�e�[�^�X�G�t�F�N�g
	StatusEffect_Up,				///< �\�͏㏸
	StatusEffect_Down,				///< �\�͉��~
	StatusEffect_Recover,			///< ��
	StatusEffect_Metal,				///< ���^���n
};

#define WEST_SP_FUNC_MAX (NELEMS(WeSysSP_FuncTable))


// ----------------------------------------
//
//	��OBJ�o�^�p
//
// ----------------------------------------
static const pWeClactFunc WeSysSP_ClactFuncTable[] = {

	WestSp_CAT_SampleTCB,
	WestSp_CAT_WE_081,				///< we_081
	WestSp_CAT_WE_134,				///< we_134
	WestSp_CAT_WE_271,				///< we_271
	WestSp_CAT_WE_118,				///< we_118
	WestSp_CAT_WE_132,				///< we_132
	WestSp_CAT_WE_155,				///< we_155
	WestSp_CAT_WE_184,				///< we_184
	WestSp_CAT_WE_193,				///< we_193
	WestSp_CAT_WE_199,				///< we_199
	WestSp_CAT_WE_207_SUB,			///< we_207_SUB	����܁[��
	WestSp_CAT_WE_212,				///< we_212
	WestSp_CAT_WE_259,				///< we_259
	WestSp_CAT_WE_226,				///< we_226
	WestSp_CAT_WE_286,				///< we_286
	WestSp_CAT_WE_288,				///< we_288
	WestSp_CAT_WE_320,				///< we_320
	WestSp_CAT_WE_333,				///< we_333
	WestSp_CAT_WE_252_DrawCap,		///< we_252 cap draw
	WestSp_CAT_WE_269,				///< we_269
	WestSp_CAT_WE_270,				///< we_270
	WestSp_CAT_WE_274,				///< we_270
	WestSp_CAT_WE_232,				///< �߂��邭��[
	WestSp_CAT_WE_275,				///< �˂��͂�
	WestSp_CAT_WE_338,				///< �n�[�h�v�����g
	WestSp_Free,					///< �����G���o�ăA�j�����I���
	WestSp_266,						///< ���̎w
	WestSp_090,						///< �����
	WestSp_Item,					///< �A�C�e��

	/**** �X�e�[�^�X�G�t�F�N�g ****/
	WestSp_CAT_ST_001,
	WestSp_CAT_ST_003,
	WestSp_CAT_ST_004,
	WestSp_CAT_ST_006,
};

#define WEST_SP_CATS_FUNC_MAX (NELEMS(WeSysSP_ClactFuncTable))



// ----------------------------------------
//
//	�����A�N�^�[�o�^�p
//
// ----------------------------------------
static const pWeOldActFunc WeSysSP_OldActFuncTable[] = {

	NULL,//SeqWazaIaigiriInit,

};

#define WEST_SP_OLDACT_FUNC_MAX (NELEMS(WeSysSP_OldActFuncTable))


// =============================================================================
//
//
//	���O���Q��
//
//
// =============================================================================
//--------------------------------------------------------------
/**
 * @brief	�T�|�[�g�֐����擾����
 *
 * @param	id			�擾����֐���ID
 *
 * @retval	pWeFunc		�T�|�[�g�֐��̃|�C���^
 *
 */
//--------------------------------------------------------------
pWeFunc WazaEffectSupportFuncGet(u32 id)
{
	pWeFunc func;
	
	if (id >= WEST_SP_FUNC_MAX){
		SDK_ASSERT(id < WEST_SP_FUNC_MAX);
		return NULL;
	}
	
	func = WeSysSP_FuncTable[id];
	
	return func;
}


//--------------------------------------------------------------
/**
 * @brief	�Z���A�N�^�[�p �T�|�[�g�֐��Ăяo��
 *
 * @param	id				�擾����֐���ID
 *
 * @retval	pWeClactFunc	�T�|�[�g�֐��̃|�C���^
 *
 */
//--------------------------------------------------------------
pWeClactFunc WazaEffectSupportFuncGet_CATS(u32 id)
{
	pWeClactFunc func;
	
	if (id >= WEST_SP_CATS_FUNC_MAX){
		SDK_ASSERT(id < WEST_SP_CATS_FUNC_MAX);
		return NULL;
	}
	
	func = WeSysSP_ClactFuncTable[id];
	
	return func;
}


//--------------------------------------------------------------
/**
 * @brief	�T�|�[�g�֐����擾����
 *
 * @param	id			�擾����֐���ID
 *
 * @retval	pWeCatFunc	�T�|�[�g�֐��̃|�C���^
 *
 */
//--------------------------------------------------------------
pWeOldActFunc WazaEffectSupportFuncGet_OLDACT(u32 id)
{
	pWeOldActFunc func;
	
	if (id >= WEST_SP_OLDACT_FUNC_MAX){
		return NULL;
	}
	
	func = WeSysSP_OldActFuncTable[id];
	
	return func;
}

