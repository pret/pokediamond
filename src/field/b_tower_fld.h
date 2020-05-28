/**
 *	@file	b_tower_fld.h
 *	@brief	�o�g���^���[�@�X�N���v�g�֘A�@�T�u���[�`���Q
 *	@author	Miyuki Iwasawa
 *	@date	06.04.17
 */

#ifndef __H_B_TOWER_FLD_H__
#define __H_B_TOWER_FLD_H__

#ifdef GLOBAL
#undef GLOBAL
#endif

#ifdef __B_TOWER_FLD_H_GLOBAL
#define GLOBAL	/***/
#else
#define GLOBAL	extern
#endif

/**
 *	@brief	�Q���ł��Ȃ��|�P���������^�O�W�J
 */
GLOBAL WORDSET* BtlTower_SetNgPokeName(SAVEDATA* sv,u16 pokenum,u16 sex,u8 flag,u8* num);

/**
 *	@brief	�g���[�i�[�^�C�v����l��OBJ�R�[�h��Ԃ�
 */
GLOBAL u16 BtlTower_TrType2ObjCode(u8 tr_type);

/**
 *	@brief	�o�g���^���[�p�@�o�g���p�����[�^����
 */
GLOBAL BATTLE_PARAM* BtlTower_CreateBattleParam(BTOWER_SCRWORK* wk,FIELDSYS_WORK* fsys);


/**
 *	@brief	�o�g���^���[�@�����Ă����v���C���[�f�[�^���󂯎��
 */
GLOBAL u16 BTowerComm_RecvPlayerData(FIELDSYS_WORK* fsys,const u16* recv_buf);

/**
 *	@brief	�o�g���^���[�@�����Ă����g���[�i�[�f�[�^���󂯎��
 */
GLOBAL u16	BTowerComm_RecvTrainerData(FIELDSYS_WORK* fsys,const u16* recv_buf);

/**
 *	@brief	�o�g���^���[�@�����Ă������^�C�A���邩�ǂ����̌��ʂ��󂯎��
 *
 *	@retval	0	���^�C�A���Ȃ�
 *	@retval	1	���^�C�A����
 */
GLOBAL u16	BTowerComm_RecvRetireSelect(FIELDSYS_WORK* fsys,const u16* recv_buf);

/**
 *	@brief	�o�g���^���[�@���@���ʂƃ����X�^�[No�𑗐M
 */
GLOBAL void BTowerComm_SendPlayerData(BTOWER_SCRWORK* wk,SAVEDATA *sv);

/**
 *	@brief	�o�g���^���[�@�ʐM�}���`�@���I�����g���[�i�[No���q�@�ɑ��M
 */
GLOBAL void BTowerComm_SendTrainerData(BTOWER_SCRWORK* wk);

/**
 *	@brief	�o�g���^���[�@�ʐM�}���`�@���^�C�A���邩�ǂ������݂��ɑ��M
 *
 *	@param	retire	TRUE�Ȃ烊�^�C�A
 */
GLOBAL void BTowerComm_SendRetireSelect(BTOWER_SCRWORK* wk,u16 retire);

/**
 *	@brief	�g���[�i�[�i���o�[���I
 */
GLOBAL u16	BattleTowerTrainerNoGet(BTOWER_SCRWORK* wk,u8 stage,u8 round,int play_mode);

/**
 *	@brief	Wifi �g���[�i�[���I
 */
GLOBAL void btltower_BtlPartnerSelectWifi(SAVEDATA* sv,B_TOWER_PARTNER_DATA* wk,
		const u8 round);

//============================================================================================
/**
 *	�o�g���^���[�g���[�i�[�f�[�^�����i�����f�[�^��B_TOWER_PARTNER_DATA�\���̂ɓW�J�j
 *
 * @param[in/out]	tr_data		��������B_TOWER_PARTNAER_DATA�\����
 * @param[in]		tr_no		�������ɂȂ�g���[�i�[ID
 * @param[in]		cnt			�g���[�i�[�Ɏ�������|�P�����̐�
 * @param[in]		set_poke_no	�y�A��g��ł���g���[�i�[�̎����|�P�����iNULL���ƃ`�F�b�N�Ȃ��j
 * @param[in]		set_item_no	�y�A��g��ł���g���[�i�[�̎����|�P�����̑����A�C�e���iNULL���ƃ`�F�b�N�Ȃ��j
 * @param[in/out]	poke		���I���ꂽ�|�P�����̓�̂̃p�����[�^���i�[���ĕԂ��\���̌^�f�[�^�ւ̃|�C���^(NULL���ƃ`�F�b�N�Ȃ��j
 * @param[in]		heapID		�q�[�vID
 *
 * @retval	FALSE	���I���[�v��50��ȓ��ŏI�����
 * @retval	TRUE	���I���[�v��50��ȓ��ŏI���Ȃ�����
 */
//============================================================================================
GLOBAL BOOL	RomBattleTowerTrainerDataMake(BTOWER_SCRWORK* wk,B_TOWER_PARTNER_DATA *tr_data,u16 tr_no,int cnt,
							  u16 *set_poke_no,u16 *set_item_no,B_TOWER_PAREPOKE_PARAM* poke,int heapID);

//============================================================================================
/**
 *	�o�g���^���[ �y�A�g���[�i�[�f�[�^�Đ���
 *	�i�Z�[�u���ꂽAI�}���`�p�[�g�i�[�̃f�[�^��B_TOWER_PARTNER_DATA�\���̂ɓW�J�j
 *
 * @param[in/out]	tr_data		��������B_TOWER_PARTNAER_DATA�\����
 * @param[in]		tr_no		�������ɂȂ�g���[�i�[ID
 * @param[in]		fixitem		TURE�Ȃ�Œ�A�C�e�����AFALSE�Ȃ�rom�A�C�e�����Z�b�g����
 * @param[in]		poke		�|�P�����f�[�^�Đ����ɕK�v�ȍ\���̌^�f�[�^�ւ̃|�C���^
 * @param[in]		heapID		�q�[�vID
 */
//============================================================================================
GLOBAL void RomBattleTowerPartnerDataMake(BTOWER_SCRWORK* wk,B_TOWER_PARTNER_DATA *tr_data,u16 tr_no,BOOL itemfix,
		const B_TOWER_PAREPOKE_PARAM* poke,int heapID);


#endif	//__H_B_TOWER_FLD_H__
