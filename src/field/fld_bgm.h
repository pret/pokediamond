//==============================================================================================
/**
 * @file	fld_bgm.h
 * @brief	�t�B�[���h�T�E���h����
 * @author	Satoshi Nohara
 * @date	2005.10.14
 */
//==============================================================================================
#ifndef __FLD_BGM_H__
#define __FLD_BGM_H__

#include "field_common.h"


//==============================================================================================
//
//	extern�錾
//
//==============================================================================================

//--------------------------------------------------------------
/**
 * @brief	�Q�[���I�[�o�[���ɂ��鏈��(field_encount.c����Ă΂��)
 *
 * @param	none
 *
 * @retval	none
 */
//--------------------------------------------------------------
extern void Snd_GameOverSet();

//--------------------------------------------------------------
/**
 * @brief	�Q�[���I�[�o�[��ɍĊJ���鎞�̏���(field_encount.c����Ă΂��)
 *
 * @param	fsys	FIELDSYS_WORK�^�̃|�C���^
 *
 * @retval	none
 */
//--------------------------------------------------------------
extern void Snd_RestartSet( FIELDSYS_WORK* fsys );

//--------------------------------------------------------------
/**
 * @brief	BGM�w��Z�b�g
 *
 * @param	fsys	FIELDSYS_WORK�^�̃|�C���^
 * @param	bgm_no	BGM�i���o�[
 *
 * @retval	none
 *
 * �}�b�v�������BGM�w�肪�Z�b�g�����
 * ���]��BGM�̐���ȂǂɎg�p
 */
//--------------------------------------------------------------
extern void Snd_FieldBgmSetSpecial( FIELDSYS_WORK* fsys, u16 bgm_no );

//--------------------------------------------------------------
/**
 * @brief	BGM�w��Q�b�g
 *
 * @param	fsys	FIELDSYS_WORK�^�̃|�C���^
 *
 * @retval	"BGM�i���o�["
 *
 * �}�b�v�������BGM�w�肪�Z�b�g�����
 * ���]��BGM�̐���ȂǂɎg�p
 */
//--------------------------------------------------------------
extern u16 Snd_FieldBgmGetSpecial( FIELDSYS_WORK* fsys );

//--------------------------------------------------------------
/**
 * @brief	BGM�w��N���A
 *
 * @param	fsys	FIELDSYS_WORK�^�̃|�C���^
 *
 * @retval	none
 *
 * �}�b�v�������BGM�w�肪�N���A�����
 * ���]��BGM�̐���ȂǂɎg�p
 */
//--------------------------------------------------------------
extern void Snd_FieldBgmClearSpecial( FIELDSYS_WORK* fsys );

//--------------------------------------------------------------
/**
 * @brief	�t�B�[���hBGM�i���o�[�擾
 *
 * @param	fsys	FIELDSYS_WORK�^�̃|�C���^
 * @param	zone_id	�]�[��ID
 *
 * @retval	"�t�B�[���hBGM�i���o�["
 */
//--------------------------------------------------------------
extern u16 Snd_FieldBgmNoGet( FIELDSYS_WORK* fsys, int zone_id );

//--------------------------------------------------------------
/**
 * @brief	�t�B�[���hBGM�i���o�[�擾(BASIC_BANK������)
 *
 * @param	fsys	FIELDSYS_WORK�^�̃|�C���^
 * @param	zone_id	�]�[��ID
 *
 * @retval	"�t�B�[���hBGM�i���o�["
 *
 * �ʏ�͎g�p���Ȃ��I
 */
//--------------------------------------------------------------
extern u16 Snd_FieldBgmNoGetNonBasicBank( FIELDSYS_WORK* fsys, int zone_id );

//--------------------------------------------------------------
/**
 * @brief	"�]�[�����܂�����p"�@�t�F�[�h�A�E�g �� BGM�Đ�(�t�B�[���h��p)
 *
 * @param	fsys	FIELDSYS_WORK�^�̃|�C���^
 * @param	seq_no	�V�[�P���X�i���o�[
 * @param	mode	���[�h(fld_bgm.h�Q��)
 *
 * @retval	"0=�������Ȃ��A1=�J�n"
 *
 * �t�B�[���h�ȊO�́A���̊֐����g�p���ĉ������I
 * ��Snd_BgmFadeOutNextPlaySet(...);
 *
 * �]�[�����܂�����p�ł��B���H�A���̃]�[�����܂������Ɏg�p���܂��B
 * �}�b�v�J�ڂɂ͎g�p�ł��܂���B
 */
//--------------------------------------------------------------
extern BOOL Snd_FadeOutNextPlayCall( FIELDSYS_WORK* fsys, u16 seq_no, int mode );

//--------------------------------------------------------------
/**
 * @brief	"�}�b�v�J�ڐ�p"�@�t�F�[�h�A�E�g �� BGM�Đ�(�t�B�[���h��p)
 *
 * @param	fsys	FIELDSYS_WORK�^�̃|�C���^
 * @param	seq_no	�V�[�P���X�i���o�[
 * @param	mode	���[�h(fld_bgm.h�Q��)
 *
 * @retval	"0=�������Ȃ��A1=�J�n"
 *
 * �}�b�v�J�ڐ�p�ł��B�����A�_���W�����ɓ��鎞�Ɏg�p���܂��B
 * ���H�A���̃]�[�����܂������ɂ͎g�p�ł��܂���B
 */
//--------------------------------------------------------------
//extern BOOL Snd_MapChangeFadeOutNextPlayCall( FIELDSYS_WORK* fsys, u16 seq_no, int mode );

//--------------------------------------------------------------
/**
 * @brief	"�}�b�v�J�ڐ�p"�@ev_mapchange.c�p�̊֐�
 *
 * @param	fsys	FIELDSYS_WORK�^�̃|�C���^
 * @param	zone_id	�]�[��ID
 * @param	mode	���[�h(fld_bgm.h�Q��)
 *
 * @retval	"0=�������Ȃ��A1=�J�n"
 *
 * �}�b�v�J�ڐ�p�ł��B�����A�_���W�����ɓ��鎞�Ɏg�p���܂��B
 * ���H�A���̃]�[�����܂������ɂ͎g�p�ł��܂���B
 */
//--------------------------------------------------------------
extern BOOL Snd_MapChangeFadeOutNextPlaySub( FIELDSYS_WORK* fsys, int zone_id, int mode );

//--------------------------------------------------------------
/**
 * @brief	�g���[�i�[����BGM�擾(�X�N���v�g����Ă΂��)
 *
 * @param	tr_id	�g���[�i�[ID
 *
 * @retval	none
 */
//--------------------------------------------------------------
extern u16 Snd_EyeBgmGet( int tr_id );

//--------------------------------------------------------------
/**
 * @brief	�퓬BGM�擾
 *
 * @param	fight_type	�퓬��ʃt���O
 * @param	tr_id	�g���[�i�[ID
 *
 * @retval	none
 */
//--------------------------------------------------------------
extern u16 Snd_BattleBgmGet( u32 fight_type, int tr_id );

//--------------------------------------------------------------
/**
 * @brief	�]�[���f�[�^��BGM�i���o�[�擾
 *
 * @param	zone_id	�]�[��ID
 *
 * @retval	"BGM�i���o�["
 */
//--------------------------------------------------------------
extern u16 Snd_ZoneDataBgmNoGet( int zone_id );


//==============================================================================================
//
//	�}�b�v�J�ڗp(�܂������͎g�p�s�I)
//
//	ev_mapchange.c
//	map_jump.c
//
//==============================================================================================

//--------------------------------------------------------------
/**
 * @brief	�}�b�v�J�ځF�]�[���؂�ւ��鎞�Ƀt�F�[�h�A�E�g
 *
 * @param	fsys		FIELDSYS_WORK�^�̃|�C���^
 * @param	zone_id		�]�[��ID
 *
 * @retval	none
 */
//--------------------------------------------------------------
extern void Snd_EvMapChangeBgmFadeCheck( FIELDSYS_WORK* fsys, int zone_id );

//--------------------------------------------------------------
/**
 * @brief	�}�b�v�J�ځF�]�[���؂�ւ��鎞��BGM�Đ�
 *
 * @param	fsys		FIELDSYS_WORK�^�̃|�C���^
 * @param	zone_id		�]�[��ID
 *
 * @retval	none
 */
//--------------------------------------------------------------
extern void Snd_EvMapChangeBgmPlay( FIELDSYS_WORK* fsys, int zone_id );


//==============================================================================================
//
//	�t�B�[���h�������p
//
//	fieldmap.c
//
//==============================================================================================

//--------------------------------------------------------------
/**
 * @brief	�t�B�[���h�������F�T�E���h�f�[�^�Z�b�g
 *
 * @param	fsys		FIELDSYS_WORK�^�̃|�C���^
 * @param	zone_id		�]�[��ID
 *
 * @retval	none
 */
//--------------------------------------------------------------
extern void Snd_FieldMapInitBgmPlay( FIELDSYS_WORK* fsys, int zone_id );


#endif


