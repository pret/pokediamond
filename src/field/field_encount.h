//============================================================================================
/**
 * @file	field_encount.h
 * @brief
 * @date	2005.07.28
 */
//============================================================================================

#ifndef	__FIELD_ENCOUNT_H__
#define __FIELD_ENCOUNT_H__

#include "battle/battle_common.h"
#include "poketool/pokeparty.h"
#include "field_event.h"
#include "b_tower_scr.h"

extern void FieldEncount_Set(FIELDSYS_WORK * fsys, BATTLE_PARAM * param);
extern void FieldEncount_Change(FIELDSYS_WORK * fsys, GMEVENT_CONTROL * event, BATTLE_PARAM * param);
extern BOOL FieldEncount_Check(FIELDSYS_WORK * fsys);
extern void FieldBattle_SetProc(FIELDSYS_WORK * fsys, BATTLE_PARAM * param);

extern void EventCmd_NormalLose(GMEVENT_CONTROL * event);
extern void EventCmd_BattleProc(GMEVENT_CONTROL * event, BATTLE_PARAM * battle_param);
extern void EventCmd_TrainerBattle(GMEVENT_CONTROL * event, int tr_id_0, int tr_id_1, int partner_id,
		int heapID, int * win_flag);
extern void EventCmd_HoneyTreeBattle(GMEVENT_CONTROL * event, int * win_flag);
extern void EventCmd_WildBattle(GMEVENT_CONTROL * event, u16 monsno, u8 level, int * win_flag,BOOL densetsu);
extern void EventCmd_FirstBattle(GMEVENT_CONTROL * event, u16 monsno, u8 level);

extern void EventCmd_CommBattle(GMEVENT_CONTROL * event);
extern void EventCmd_TemotiListBattle(GMEVENT_CONTROL * event,const u8* temotiList, int fightType);
extern void EventCmd_WifiBattle(GMEVENT_CONTROL * event,int targetID, int lvLimit,BOOL bSingle);
extern void EventSet_CommDirectBattle(FIELDSYS_WORK * fsys, const u8 * temotilist, int fightType);
extern void EventSet_CommDirectMixBattle(FIELDSYS_WORK * fsys, const POKEPARTY* party, int fightType);

//-----------------------------------------------------------------------------
/**
 * @brief	�C�x���g�[���R�}���h�F�o�g���^���[���[�J���ΐ�
 * @param	event		�C�x���g���䃏�[�N�ւ̃|�C���^
 * @param	trainer_id	�g���[�i�[�w��f�[�^
 * @param	fight_type	�퓬���
 * @param	heapID		�q�[�vID
 * @param	win_flag	�퓬���ʂ��󂯎��t���O
 */
//-----------------------------------------------------------------------------
extern void EventCmd_TowerLocalBattle(GMEVENT_CONTROL * event,BTOWER_SCRWORK* wk, int * win_flag);


//�C�x���g�R�}���h�F�|�P�p�[�N�G���J�E���g
extern void EventSet_PokeParkBattle(FIELDSYS_WORK * fsys, BATTLE_PARAM * btlprm);

//�C�x���g�R�}���h�F�ߊl�f���Ăяo��
extern void EventCmd_CaptureDemo(GMEVENT_CONTROL * event);

#ifdef	PM_DEBUG
extern BOOL DebugFieldEncount(FIELDSYS_WORK * fsys);
extern BOOL DebugFieldEncount2vs2(FIELDSYS_WORK * fsys);
extern BOOL DebugFieldTrainerEncount(FIELDSYS_WORK * fsys);
#endif
#endif	/* __FIELD_ENCOUNT_H__ */

