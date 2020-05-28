//============================================================================================
/**
 * @file	field_3d_anime_ev.h
 * @bfief	�C�x���g�p3D�A�j���֘A�t�@�C��
 * @author	Nozomu Saito
 * @date	2006.01.26
 *
 */
//============================================================================================

#ifndef _FIELD_3D_ANIME_EV_H_
#define _FIELD_3D_ANIME_EV_H_

#include "field_common.h"

typedef struct FLD_3D_ANIME_WORK_tag*	FLD_3D_ANIME_WORK_PTR;

//�������m��
extern FLD_3D_ANIME_WORK_PTR	Fld3DAnm_AllocEvent3DAnimeWork(void);
//���
extern void Fld3DAnm_FreeEvent3DAnimeWork(FLD_3D_ANIME_WORK_PTR outAnime3DWorkPtr);
//���W�Z�b�g
extern void Fld3DAnm_EventSetGrid(const int inGridX, const int inGridZ, FLD_3D_ANIME_WORK_PTR outAnime3DWorkPtr);
//�h�A�A�j���C�x���g
extern BOOL Fld3DAnm_EventDoorInAnime(FIELDSYS_WORK * fsys, FLD_3D_ANIME_WORK_PTR work);
extern BOOL Fld3DAnm_EventDoorOutAnime(FIELDSYS_WORK * fsys, FLD_3D_ANIME_WORK_PTR work);
extern BOOL Fld3DAnm_EventEscalatorInAnime(FIELDSYS_WORK * fsys, FLD_3D_ANIME_WORK_PTR work, const u8 inDir);
extern BOOL Fld3DAnm_EventEscalatorOutAnime(FIELDSYS_WORK * fsys, FLD_3D_ANIME_WORK_PTR work, const u8 inDir);

extern void FLD_SCR_ANM_DOOR_Setup(FIELDSYS_WORK * fsys,
						const int inGridX, const int inGridZ, const u8 inEntryID);
extern void FLD_SCR_ANM_DOOR_StartOpenDoorAnm(	FIELDSYS_WORK * fsys, const u8 inEntryID );

extern void FLD_SCR_ANM_DOOR_StartCloseDoorAnm(	FIELDSYS_WORK * fsys, const u8 inEntryID );

extern void FLD_SCR_ANM_DOOR_WaitAnime(FIELDSYS_WORK * fsys, const u8 inEntryID);

//�h�A�A�j�����
extern void FLD_SCR_ANM_DOOR_FreeDoor(FIELDSYS_WORK * fsys, const u8 inEntryID);

//�����A�j���X�^�[�g
extern void Fld3DAnm_StartQuickSandAnime(	const int inGridX,
											const int inGridZ,
											const int inAnmNo,
											FIELDSYS_WORK * fsys);


typedef struct FLD_MAP_JUMP_WORK_tag*	FMJ_WORK_PTR;
//�������m��
extern FMJ_WORK_PTR	MapJump_AllocWork(void);
extern BOOL MapJump_EventFadeOutWhite(GMEVENT_CONTROL * event);
extern BOOL MapJump_EventFadeInWhite(GMEVENT_CONTROL * event);
extern BOOL MapJump_EventFadeOutHole(GMEVENT_CONTROL * event);
extern BOOL MapJump_EventFadeInShutSlide(GMEVENT_CONTROL * event);
extern BOOL MapJump_EventFadeInBlack(GMEVENT_CONTROL * event);
#endif //_FIELD_3D_ANIME_EV_H_
