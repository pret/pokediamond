//============================================================================================
/**
 * @file	tv_topic.h
 * @brief	�e���r�̃g�s�b�N�o�^�p�w�b�_
 * @date	2006.05.22
 * @author	tamada GAME FREAK inc.
 */
//============================================================================================

#ifndef	__TV_TOPIC_H__
#define	__TV_TOPIC_H__

#include "field_common.h"

#include "poketool/poke_tool.h"
#include "field/tvtopic_battle.h"
#include "system/pms_data.h"

//============================================================================================
//
//
//		�ʃg�s�b�N�p����
//
//
//============================================================================================
//02-01,02-02	�g�s�b�N�����F�ߊl���������s
//--------------------------------------------------------------------
/**
 * @brief	�e���r�g�s�b�N�����F�ߊl
 * @param	fsys	�t�B�[���h���䃏�[�N�ւ̃|�C���^
 * @param	tvwbw			�e���r�g�s�b�N�p���ێ����[�N
 */
//--------------------------------------------------------------------
extern void TVTOPIC_Entry_Watch_Capture(FIELDSYS_WORK * fsys,
		const TVWATCH_BATTLE_WORK * wcw_result, int win_lose_flag);

//02-03	�g�s�b�N�����F���E��ނ�I
//--------------------------------------------------------------------
/**
 * @brief	�g�s�b�N�����F���E��ނ�I
 * @param	fsys	�t�B�[���h���䃏�[�N�ւ̃|�C���^
 * @param	success_flag	�����������ǂ���
 * @param	itemno			�g�p�����肴���̃A�C�e���i���o�[
 * @param	pp				�ނ�グ���|�P������POKEMON_PARAM�ւ̃|�C���^
 *
 * �ނ�グ���Ȃ������ꍇ�Asuccess_flag == FALSE��PP==NULL�ł悢
 */
//--------------------------------------------------------------------
extern void TVTOPIC_Entry_Watch_Fishing(FIELDSYS_WORK * fsys, BOOL success_flag,
		u16 itemno, POKEMON_PARAM * pp);

//02-04	�g�s�b�N�����F�O���[�v�����ւ���
extern void TVTOPIC_Entry_Watch_ChangeGroup(FIELDSYS_WORK * fsys);

//02-06	�g�s�b�N�����F�B���A�C�e������
//--------------------------------------------------------------------
/**
 * @brief	�g�s�b�N�����F�B���A�C�e�������I
 * @param	fsys	�t�B�[���h���䃏�[�N�ւ̃|�C���^
 * @param	item_no		�������A�C�e���̃i���o�[
 */
//--------------------------------------------------------------------
extern void TVTOPIC_Entry_Watch_HideItem(FIELDSYS_WORK * fsys, u16 item_no);

//02-08	�g�s�b�N�����F�^�}�S���z�����I
//--------------------------------------------------------------------
/**
 * @brief	�g�s�b�N�����F�^�}�S���z�����I
 * @param	fsys	�t�B�[���h���䃏�[�N�ւ̃|�C���^
 * @param	�z�����|�P�����ւ̃|�C���^
 */
//--------------------------------------------------------------------
extern void TVTOPIC_Entry_Watch_HatchEgg(FIELDSYS_WORK * fsys, POKEMON_PARAM * pp);

//02-10	�g�s�b�N�����F�������f
//--------------------------------------------------------------------
/**
 * @brief	�g�s�b�N�����F�������f	�j�b�N�l�[����ύX�����Ƃ�
 * @param	fsys	�t�B�[���h���䃏�[�N�ւ̃|�C���^
 * @param	pp		���O��ς����|�P�����ւ̃|�C���^
 */
//--------------------------------------------------------------------
extern void TVTOPIC_Entry_Watch_ChangeName(FIELDSYS_WORK * fsys, POKEMON_PARAM * pp);

//02-13	�g�s�b�N�����F�n�����Ό@��
//--------------------------------------------------------------------
/**
 * @brief	�g�s�b�N�����F���Ό@��	���Ό@�����������
 * @param	fsys	�t�B�[���h���䃏�[�N�ւ̃|�C���^
 * @param	fossil_type		���΂̃A�C�e���i���o�[
 * @param	fossil_num		��ꂽ���΂̐�
 */
//--------------------------------------------------------------------
extern void TVTOPIC_Entry_Watch_DigFossil(FIELDSYS_WORK * fsys, int fossil_type, int fossil_num);

//02-15	�g�s�b�N�����F�T�t�@���Q�[��
//--------------------------------------------------------------------
/**
 * @brief	�g�s�b�N�����F�T�t�@���Q�[��	�T�t�@���Q�[�����I���������Ƃ�
 * @param	fsys	�t�B�[���h���䃏�[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------------
extern void TVTOPIC_Entry_Watch_Safari(FIELDSYS_WORK * fsys);

//02-17	�g�s�b�N�����F�ǖ�͌��ɋꂵ�I	�|�P�����Ɋ�������������Ƃ�
//tvtopic_extern.h�ɂ���܂�

//02-18,02-19,03-06	�g�s�b�N�����F���̂݊֘A
//--------------------------------------------------------------------
/**
 * @brief	�g�s�b�N�����F���݂̂��Ƃ����Ƃ�
 * @param	fsys			�t�B�[���h���䃏�[�N�ւ̃|�C���^
 * @param	nuts_item_no	�Ƃ������݂̂̃A�C�e���i���o�[
 * @param	hp				�Ƃ����Ƃ���HP�̒l
 * @param	nuts_count		�Ƃ������݂̂̐�
 */
//--------------------------------------------------------------------
extern void TVTOPIC_Entry_TakeNuts(FIELDSYS_WORK  *fsys, u16 nuts_item_no, u8 hp, u16 nuts_count);

//02-20	�g�s�b�N�����F�O���[�v�����
extern void TVTOPIC_Entry_Watch_MakeGroup(FIELDSYS_WORK * fsys);

//02-21	�g�s�b�N�����F�J�X�^���{�[���Z�b�g
//field/tvtopic_extern.h�ɂ���܂�

//02-22	�g�s�b�N�����F���������A�����I
//--------------------------------------------------------------------
/**
 * @brief	�g�s�b�N�����F����������I		�l�̊��������A�����I
 * @param	fsys	�t�B�[���h���䃏�[�N�ւ̃|�C���^
 * @param	rival		�����MYSTATUS�ւ̃|�C���^
 */
//--------------------------------------------------------------------
extern void TVTOPIC_Entry_Watch_GetFlag(FIELDSYS_WORK * fsys, const MYSTATUS * rival);

//02-23	�g�s�b�N�����F���������A��ꂽ�I
//--------------------------------------------------------------------
/**
 * @brief	�g�s�b�N�����F�������ꂽ�I		�����̊��������A��ꂽ�I
 * @param	fsys	�t�B�[���h���䃏�[�N�ւ̃|�C���^
 * @param	rival		�����MYSTATUS�ւ̃|�C���^
 */
//--------------------------------------------------------------------
extern void TVTOPIC_Entry_Watch_LoseFlag(FIELDSYS_WORK * fsys, const MYSTATUS * rival);


//--------------------------------------------------------------------
/**
 * @brief	�g�s�b�N�����F�o�g���^���[�A��
 * @param	fsys			�t�B�[���h���䃏�[�N�ւ̃|�C���^
 * @param	renshou			�A����
 * @param	pp				�擪�̃|�P�����ւ̃|�C���^
 * @param	IsSingleFlag	�V���O���킩�ǂ���
 */
//--------------------------------------------------------------------
extern void TVTOPIC_Entry_Record_BTower(FIELDSYS_WORK * fsys,
		u32 renshou, POKEMON_PARAM * pp, BOOL IsSingleFlag);

//--------------------------------------------------------------------
/**
 * @brief	�g�s�b�N�����F�傫������L�^�X�V	�傫������ŋL�^���X�V�����Ƃ�
 * @param	fsys	�t�B�[���h���䃏�[�N�ւ̃|�C���^
 * @param	size		�L�^
 * @param	pp			�X�V�����|�P�����ւ̃|�C���^
 */
//--------------------------------------------------------------------
extern void TVTOPIC_Entry_Record_Ookisa(FIELDSYS_WORK * fsys, u32 size, POKEMON_PARAM * pp);

//--------------------------------------------------------------------
/**
 * @brief	�g�s�b�N�����F�X���b�g�B�l	�X���b�g�ň�薇���ȏ���҂����Ƃ�
 * @param	fsys	�t�B�[���h���䃏�[�N�ւ̃|�C���^
 * @param	start_coin		�J�n���̃R�C������
 * @param	end_coin		�I�����̃R�C������
 * @param	playtime		�v���C���ԁi���P�ʁj
 */
//--------------------------------------------------------------------
extern void TVTOPIC_Entry_Record_Slot(FIELDSYS_WORK * fsys, u32 start_coin, u32 end_coin, u32 playtime);

//--------------------------------------------------------------------
/**
 * @brief	�g�s�b�N�����F���i�������l	�n���ɓ������Ƃ��A��������̃��i������������쐬
 * @param	fsys	�t�B�[���h���䃏�[�N�ւ̃|�C���^
 * @param	trap_no			�ŏ��ɉ����������i�̃i���o�[
 * @param	remove_count	���i������������
 *
 * �n���ɓ����Ă���o��܂ł̊Ԃ̉񐔂ł��B��x�o���烊�Z�b�g����܂��B
 */
//--------------------------------------------------------------------
extern void TVTOPIC_Entry_Record_RemoveTrap(FIELDSYS_WORK * fsys, u16 trap_no, u16 remove_count);

//--------------------------------------------------------------------
/**
 * @brief	�g�s�b�N�����F�n�^�g�����l
 * @param	fsys	�t�B�[���h���䃏�[�N�ւ̃|�C���^
 * @param	flag_count		�����������
 *
 * �n���ɓ����Ă���o��܂ł̊Ԃ̉񐔂ł��B��x�o���烊�Z�b�g����܂��B
 */
//--------------------------------------------------------------------
extern void TVTOPIC_Entry_Record_GetFlag(FIELDSYS_WORK * fsys, u16 flag_count);

//============================================================================================
//============================================================================================
//--------------------------------------------------------------------
/**
 * @brief	�g�s�b�N�����F�o�g���^���[�C���^�r���[
 * @param	fsys	�t�B�[���h���䃏�[�N�ւ̃|�C���^
 * @param	word		�ȈՉ�b�P��ID
 */
//--------------------------------------------------------------------
extern void TVTOPIC_Entry_QandA_BTower(FIELDSYS_WORK * fsys, PMS_WORD word);

//--------------------------------------------------------------------
/**
 * @brief	�g�s�b�N�����F���Ȃ��̃|�P�����C���^�r���[
 * @param	fsys	�t�B�[���h���䃏�[�N�ւ̃|�C���^
 * @param	word		�ȈՉ�b�P��ID
 */
//--------------------------------------------------------------------
extern void TVTOPIC_Entry_QandA_Pokemon(FIELDSYS_WORK * fsys, PMS_WORD word);

//--------------------------------------------------------------------
/**
 * @brief	�g�s�b�N�����F���C�ɓ���̃|�P�b�`
 * @param	fsys	�t�B�[���h���䃏�[�N�ւ̃|�C���^
 * @param	word		�ȈՉ�b�P��ID
 */
//--------------------------------------------------------------------
extern void TVTOPIC_Entry_QandA_Poketch(FIELDSYS_WORK * fsys, PMS_WORD word);

//--------------------------------------------------------------------
/**
 * @brief	�g�s�b�N�����F����I�R���e�X�g
 * @param	fsys	�t�B�[���h���䃏�[�N�ւ̃|�C���^
 * @param	word		�ȈՉ�b�P��ID
 */
//--------------------------------------------------------------------
extern void TVTOPIC_Entry_QandA_Contest(FIELDSYS_WORK * fsys, PMS_WORD word);

//--------------------------------------------------------------------
/**
 * @brief	�g�s�b�N�����F�|�P�����N���b�v�I
 * @param	fsys	�t�B�[���h���䃏�[�N�ւ̃|�C���^
 * @param	word		�ȈՉ�b�P��ID
 */
//--------------------------------------------------------------------
extern void TVTOPIC_Entry_QandA_Clip(FIELDSYS_WORK * fsys, PMS_WORD word);

//--------------------------------------------------------------------
/**
 * @brief	�g�s�b�N�����F���i�f�f�I
 * @param	fsys	�t�B�[���h���䃏�[�N�ւ̃|�C���^
 * @param	word		�ȈՉ�b�P��ID
 */
//--------------------------------------------------------------------
extern void TVTOPIC_Entry_QandA_Character(FIELDSYS_WORK * fsys, PMS_WORD word);

//--------------------------------------------------------------------
/**
 * @brief	�g�s�b�N�����F�|���g����
 * @param	fsys	�t�B�[���h���䃏�[�N�ւ̃|�C���^
 * @param	word		�ȈՉ�b�P��ID
 */
//--------------------------------------------------------------------
extern void TVTOPIC_Entry_QandA_Poruto(FIELDSYS_WORK * fsys, PMS_WORD word);

//--------------------------------------------------------------------
/**
 * @brief	�g�s�b�N�����F�|�P�����A�����
 * @param	fsys	�t�B�[���h���䃏�[�N�ւ̃|�C���^
 * @param	word		�ȈՉ�b�P��ID
 */
//--------------------------------------------------------------------
extern void TVTOPIC_Entry_QandA_Park(FIELDSYS_WORK * fsys, PMS_WORD word);

#endif	//__TV_TOPIC_H__
