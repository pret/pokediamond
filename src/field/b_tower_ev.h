/**
 *	@file	b_tower_ev.h
 *	@brief	�o�g���^���[�@�풓�C�x���g�R���g���[��
 *	@author	Miyuki Iwasawa
 *	@date	06.04.26
 */

#ifndef __H_B_TOWER_EV_H__
#define __H_B_TOWER_EV_H__

#ifdef GLOBAL
#undef GLOBAL
#endif

#ifdef _B_TOWER_EV_H_GLOBAL
#define GLOBAL	/***/
#else
#define GLOBAL	extern
#endif

//--------------------------------------------------------------
/**
 * @brief	�|�P�����I���@�T�u�C�x���g�Ăяo��
 * @param	event	GMEVENT_CONTROL*
 * @retval	nothing
 */
//--------------------------------------------------------------
GLOBAL void EventCmd_BTowerPokeSelectCall(GMEVENT_CONTROL *event,void** buf,
	u8 plmode,u8 psmode,u8 min,u8 max,u8 level,u8 pos);

//--------------------------------------------------------------
/**
 * @brief	WiFi�ڑ��@�T�u�C�x���g�Ăяo��
 * @param	event	GMEVENT_CONTROL*
 * @param	mode	�ڑ����[�h
 * @param	ret_wk_no	�Ԃ�l��Ԃ����[�NID
 * @param	dpw_code	DPW_INIT_PROC���Ԃ����Ԃ�l
 * @retval	nothing
 */
//--------------------------------------------------------------
GLOBAL void EventCmd_BTowerWifiCall(GMEVENT_CONTROL *event,u16 mode,u16 ret_wk_no,u16 dpw_code);

//--------------------------------------------------------------
/**
 * @brief	�ʐM�}���`�@�f�[�^��M�T�u�C�x���g
 * @param	event	GMEVENT_CONTROL*
 * @param	mode	��M���[�h
 * @param	ret_wk_no	�Ԃ�l�擾�p���[�NID
 * @retval	nothing
 */
//--------------------------------------------------------------
GLOBAL void EventCmd_BTowerSioRecvBuf(GMEVENT_CONTROL *event,u16 mode,u16 ret_wk_no);

/**
 *	@brief	�v���C�Y�����炦�邩�ǂ����`�F�b�N����
 *
 *	@retval	0	���炦�Ȃ�
 */
GLOBAL u16 BtlTower_IsPrizeGet(SAVEDATA* sv);

/**
 *	@brief	�v���C�Y�������q�g�̕\����Ԃ�Ԃ�
 *
 *	@retval	0	��\��
 *	@retval	1	
 */
GLOBAL u16 BtlTower_IsPrizemanSet(SAVEDATA* sv);

/**
 *	@brief	�^���[�ΐ팋�ʁ@�A�b�v�f�[�g����
 */
GLOBAL void BtlTower_BattleRecordUpdate(FIELDSYS_WORK* fsys,const BATTLE_TOWER_RECORD* rec);

/**
 *	@brief	�^���[�v���C�X�V�����_���v�Z
 *
 *	���o�g���^���[�ȊO����͌Ă�ł͂����܂���
 *	�@�����Ȃ��ƁA�f�[�^�ɃY�����������܂�
 */
GLOBAL u32	BtlTower_PlayFixRand(u32 seed);

/**
 *	@brief	�^���[���t�X�V�����_���v�Z
 *
 *	���o�g���^���[�ȊO����͌Ă�ł͂����܂���
 *	�@�����Ȃ��ƁA�f�[�^�ɃY�����������܂�
 */
GLOBAL u32	BtlTower_DayFixRand(u32 seed);

/**
 *	@brief	�^���[���t�X�V�����_���V�[�h�@������̍X�V�����V
 *�@2923037603
 *	�����t�X�V����&new game���Ɉ�x�����Ăׂ܂�
 *	�@����ȊO�ŌĂԂƁA�f�[�^�ɃY�����������܂�
 */
GLOBAL u32 BtlTower_UpdateDayRndSeed(SAVEDATA* sv);

/**
 *	@brief	�^���[���t/�v���C�X�V�����_���V�[�h�@����J�n���̍X�V����
 *
 *	���^���[new game�J�n���Ɉ�x�����Ăׂ܂�
 *	�@����ȊO�ŌĂԂƁA�f�[�^�ɃY�����������܂�
 */
GLOBAL u32	BtlTower_UpdatePlayRndSeed(SAVEDATA* sv);

/**
 *	@brief	�^���[���t/�v���C�X�V�����_���V�[�h�擾�@�p������J�n���̎擾����
 */
GLOBAL u32	BtlTower_GetContinuePlayRndSeed(SAVEDATA* sv);

/**
 *	@brief	�o�g���^���[�T��������
 *
 *	@retval	TRUE	�T����
 *	@retval	FALSE	�T��������Ȃ�
 */
GLOBAL BOOL BtlTower_IsSalon(FIELDSYS_WORK* fsys);

#endif	//__H_B_TOWER_EV_H__
