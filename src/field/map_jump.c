//============================================================================================
/**
 * @file	map_jump.c
 * @brief	�}�b�v�W�����v����
 * @date	2006.02.07
 * @author	Nozomu Saito
 */
//============================================================================================
#include "common.h"
#include "fieldsys.h"
#include "field_event.h"
#include "field/location.h"
#include "ev_mapchange.h"
#include "field_3d_anime_ev.h"
#include "system/snd_tool.h"		//���ꂪ�Ȃ��ƁAfld_bgm.h�ŃG���[���o��
#include "system/wipe.h"
#include "fld_bgm.h"

#include "map_jump_def.h"
#include "map_jump.h"

#include "fieldmap.h"		//for FieldFadeWipeSet

#include "map_attr.h"		//for attribute

#include "fieldmap_work.h"	//for hblamk wipe
#include "field_hblank.h"	//for hblank wipe

#include "zonedata.h"

#include "fld_flg_init.h"

static BOOL MJUMPEVT_Wipe(GMEVENT_CONTROL * event);

static BOOL MJUMPEVT_MapChangeParent(GMEVENT_CONTROL * event);

static BOOL MJUMPEVT_MapFadeOutMat(GMEVENT_CONTROL * event);
static BOOL MJUMPEVT_MapFadeOutDoor(GMEVENT_CONTROL * event);
static BOOL MJUMPEVT_MapFadeOutEsca(GMEVENT_CONTROL * event);
static BOOL MJUMPEVT_MapFadeOutStairs(GMEVENT_CONTROL * event);
static BOOL MJUMPEVT_MapFadeOutDunIn(GMEVENT_CONTROL * event);
static BOOL MJUMPEVT_MapFadeOutDunOut(GMEVENT_CONTROL * event);

static BOOL MJUMPEVT_MapFadeInDoor(GMEVENT_CONTROL * event);
static BOOL MJUMPEVT_MapFadeInBlack(GMEVENT_CONTROL * event);
static BOOL MJUMPEVT_MapFadeInEsca(GMEVENT_CONTROL * event);
static BOOL MJUMPEVT_MapFadeInStairs(GMEVENT_CONTROL * event);
static BOOL MJUMPEVT_MapFadeInDunOut(GMEVENT_CONTROL * event);

static void SetEscalatorIOPos(FIELDSYS_WORK *fsys);
static void SetStairsIOPos(FIELDSYS_WORK *fsys);
//�t�F�[�h�A�E�g�G�t�F�N�g���X�g
		//�K�i
static const MAP_JUMP_FUNC MapJumpFadeOutFuncTbl[MAP_JUMP_TYPE_MAX] = {
	MJUMPEVT_MapFadeOutMat,		//�������O
	MJUMPEVT_MapFadeOutDoor,	//�h�A�i�O�j������
	MJUMPEVT_MapFadeOutEsca,	//�G�X�J���[�^�[
	MJUMPEVT_MapFadeOutStairs,	//�K�i
	MJUMPEVT_MapFadeOutDunIn,	//�_���W��������
	MJUMPEVT_MapFadeOutDunOut,	//�_���W�����z���C�g�A�E�g
	MJUMPEVT_MapFadeOutMat,		//�O�}�b�g������
};

//�t�F�[�h�C���G�t�F�N�g���X�g
		//�K�i
static const MAP_JUMP_FUNC MapJumpFadeInFuncTbl[MAP_JUMP_TYPE_MAX] = {
	MJUMPEVT_MapFadeInDoor,		//�������O
	MJUMPEVT_MapFadeInBlack,	//�h�A�i�O�j������
	MJUMPEVT_MapFadeInEsca,		//�G�X�J���[�^�[
	MJUMPEVT_MapFadeInStairs,	//�K�i
	MJUMPEVT_MapFadeInBlack,	//�_���W��������
	MJUMPEVT_MapFadeInDunOut,	//�_���W�����z���C�g�C��
	MJUMPEVT_MapFadeInBlack,	//�O�}�b�g������
};

//�}�b�v�W�����v�ʕ\���ʒu�␳�֐��Q
static const MAP_JUMP_POS_SET MapJumpPosSetFuncTbl[MAP_JUMP_TYPE_MAX] = {
	NULL,						//�������O
	NULL,						//�h�A�i�O�j������
	SetEscalatorIOPos,			//�G�X�J���[�^�[
	SetStairsIOPos,				//�K�i
	NULL,						//�_���W��������
	NULL,						//�_���W�����o��
	NULL,						//�O�}�b�g������
};

typedef struct {
	int seq;							///<�V�[�P���X�ێ����[�N
	int call_seq;						///<�R�[����V�[�P���X���[�N
	LOCATION_WORK next;					///<�}�b�v�J�ڐ�w��p���[�N
	///FLD_3D_ANIME_WORK_PTR DoorAnimeWork;
	void	*JumpEffectWork;
	int JumpType;
}EVENT_MAPCHG_WORK;


typedef struct WIPE_PARAM_tag
{
	int Seq;
	int Pattern;
	int Main;
	int Sub;
	u16 Col;
	int Div;
	int Sync;
	int Heap;
}WIPE_PARAM;

//-----------------------------------------------------------------------------
/**
 * @brief	���C�v�C�x���g�R�[��(���X�^�Ƃ����g�����C�v�̂Ƃ�)
 * ������H�u�����N���荞�݂��~�����A���C�v�I���ŁA�u�����N�������ăX�^�[�g�����܂�
 * @param	event		�C�x���g�|�C���^
 * @param	inPattern	�؂�ւ��p�^�[���ԍ�
 * @param	inMain		���C�v�@���C����ʃ��C�v�p�^�[��
 * @param	inSub		���C�v�@�T�u��ʃ��C�v�p�^�[��
 * @param	inCol		���C�v�̐F	
 * @param	inDiv		�e���C�v�����̕�����	(1.2.3.4.....)
 * @param	inSync		�e���C�v�̏����𕪊������P�Ђ̃V���N��	(1.2.3.4.....)
 * @param	inHeap		�g�p����q�[�v
 *
 * @return none
 */
//-----------------------------------------------------------------------------
void MJUMP_RequestWipe(	GMEVENT_CONTROL * event,
						int inPattern, int inMain,
						int inSub, u16 inCol,
						int inDiv, int inSync,
						int inHeap)
{
	WIPE_PARAM *wp = sys_AllocMemory(inHeap, sizeof(WIPE_PARAM));
	wp->Pattern = inPattern;
	wp->Main = inMain;
	wp->Sub = inSub;
	wp->Col = inCol;
	wp->Div = inDiv;
	wp->Sync = inSync;
	wp->Heap = inHeap;
	wp->Seq = 0;

	FieldEvent_Call(event, MJUMPEVT_Wipe, wp);
}

//-----------------------------------------------------------------------------
/**
 * @brief	���C�v�C�x���g
 * @param	event	�C�x���g�|�C���^
 * 
 * @return  BOOL	TRUE:�I���@FALSE:�p��
 */
//-----------------------------------------------------------------------------
static BOOL MJUMPEVT_Wipe(GMEVENT_CONTROL * event)
{
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	WIPE_PARAM *wp = FieldEvent_GetSpecialWork(event);
	switch (wp->Seq) {
	case 0:
		FLDHBLANK_SYS_Stop( fsys->fldmap->hblanksys );
		//���C�v�X�^�[�g
		WIPE_SYS_Start(	wp->Pattern, wp->Main, wp->Sub,
				wp->Col,wp->Div,wp->Sync,wp->Heap );
		wp->Seq++;
		break;
	case 1:
		if ( WIPE_SYS_EndCheck() ){
			FLDHBLANK_SYS_Start(fsys->fldmap->hblanksys);
			sys_FreeMemoryEz(wp);
			return TRUE;
		}
	}

	return FALSE;
}

//-----------------------------------------------------------------------------
/**
 * @brief	�}�b�v�J�ڃC�x���g�Z�b�g(�h�A�A�j����)
 * @param	fsys		�t�B�[���h���䃏�[�N�ւ̃|�C���^
 * @param	zone		�J�ڐ�}�b�v�̃]�[���w��
 * @param	door_id		�J�ڐ�}�b�v�ł̏o���o�����w��
 * @param	inX			�J�ڐ�}�b�v�ł�X�O���b�h�ʒu
 * @param	inZ			�J�ڐ�}�b�v�ł�Y�O���b�h�ʒu
 * @param	inDir		�J�ڐ�}�b�v�ł̏�������
 * @param	inType		�W�����v�^�C�v
 *
 * �J�ڐ�}�b�v�̂ǂ��ɏo�����邩�̏��͎��̃}�b�v��ǂݍ��ނ܂ł͂킩��Ȃ��͂��Ȃ̂�
 * �{���͍��W�w��͖��ʂ�������Ȃ����ǁA�O�̂��߁B�܂��G���A�ƃ]�[���̊֌W�͍čl�����̂�
 * �G���A�w�������Ȃ��Ȃ�\��������B
 */
//-----------------------------------------------------------------------------
void MJUMP_ChangeMap(FIELDSYS_WORK * fsys, const int zone, const int door_id,
						const int inX, const int inZ, const int inDir, const int inType )
{
	EVENT_MAPCHG_WORK * emw = sys_AllocMemoryLo(HEAPID_WORLD, sizeof(EVENT_MAPCHG_WORK));
	emw->seq = 0;
	emw->call_seq = 0;
	//���P�[�V�����f�[�^�쐬
	SetLocation(&emw->next, zone, door_id, inX, inZ, inDir);

	//�W�����v�^�C�v���Z�b�g
	emw->JumpType = inType;

	//�}�b�v�W�����v�C�x���g���쐬
	FieldEvent_Set(fsys, MJUMPEVT_MapChangeParent, emw);
}

//-----------------------------------------------------------------------------
/**
 * @brief	�}�b�v�J�ڃC�x���g�Z�b�g(�}�b�v�^�C�v���Q�Ƃ���)
 * @param	fsys		�t�B�[���h���䃏�[�N�ւ̃|�C���^
 * @param	zone		�J�ڐ�}�b�v�̃]�[���w��
 * @param	door_id		�J�ڐ�}�b�v�ł̏o���o�����w��
 * @param	inX			�J�ڐ�}�b�v�ł�X�O���b�h�ʒu
 * @param	inZ			�J�ڐ�}�b�v�ł�Y�O���b�h�ʒu
 * @param	inDir			�J�ڐ�}�b�v�ł̏�������
 *
 * �J�ڐ�}�b�v�̂ǂ��ɏo�����邩�̏��͎��̃}�b�v��ǂݍ��ނ܂ł͂킩��Ȃ��͂��Ȃ̂�
 * �{���͍��W�w��͖��ʂ�������Ȃ����ǁA�O�̂��߁B�܂��G���A�ƃ]�[���̊֌W�͍čl�����̂�
 * �G���A�w�������Ȃ��Ȃ�\��������B
 */
//-----------------------------------------------------------------------------
void MJUMP_ChangeMapByLocation(FIELDSYS_WORK * fsys, const int zone, const int door_id,
						const int inX, const int inZ, const int inDir)
{
	int now_zone;
	int type;
	EVENT_MAPCHG_WORK * emw = sys_AllocMemoryLo(HEAPID_WORLD, sizeof(EVENT_MAPCHG_WORK));
	
	emw->seq = 0;
	emw->call_seq = 0;
	//���P�[�V�����f�[�^�쐬
	SetLocation(&emw->next, zone, door_id, inX, inZ, inDir);

	//���݃}�b�v��ނ𒲂ׂ�
	now_zone = fsys->location->zone_id;
	type = 0;
	if (ZoneData_IsDungeon(now_zone)){		//���݃_���W����
		//��ѐ�𒲂ׂ�
		if (ZoneData_IsDungeon(zone)){
			type = M_JUMP_MATIN;			//�_���W�����Ԉړ�(�����ɓ���̂Ɠ���)
		}else if (ZoneData_IsOutDoor(zone)){
			type = M_JUMP_DUNOUT;			//�_���W�����O��
		}else if (ZoneData_IsRoom(zone)){
			type = M_JUMP_MATIN;			//�����̒���
		}else{
			GF_ASSERT(0);
		}
	}else if (ZoneData_IsOutDoor(now_zone)){//���݉��O
		//��ѐ�𒲂ׂ�
		if (ZoneData_IsDungeon(zone)){
			type = M_JUMP_DUNIN;			//�_���W�����̒���
		}else if (ZoneData_IsRoom(zone)){
			type = M_JUMP_MATIN;			//�����̒���
		}else{
			GF_ASSERT(0);
		}
	}else if (ZoneData_IsRoom(now_zone)){	//���ݎ���
		//��ѐ�𒲂ׂ�
		if (ZoneData_IsOutDoor(zone)){
			type = M_JUMP_MATOUT;			//���O��
		}else if(ZoneData_IsRoom(zone)){
			type = M_JUMP_MATIN;			//�������̈ړ��i�����ɓ���̂Ɠ����j
		}else if (ZoneData_IsDungeon(zone)){
			type = M_JUMP_MATOUT;			//�_���W�����ցi���O�ւł�̂Ɠ���)
		}else{
			GF_ASSERT(0);
		}
	}else{
		GF_ASSERT(0);
	}

	//�W�����v�^�C�v���Z�b�g
	emw->JumpType = type;

	//�}�b�v�W�����v�C�x���g���쐬
	FieldEvent_Set(fsys, MJUMPEVT_MapChangeParent, emw);
}

//-----------------------------------------------------------------------------
// @brief	�}�b�v�J�ڃC�x���g
//-----------------------------------------------------------------------------
static BOOL MJUMPEVT_MapChangeParent(GMEVENT_CONTROL * event)
{
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	EVENT_MAPCHG_WORK * emw = FieldEvent_GetSpecialWork(event);
	LOCATION_WORK* location = &emw->next;

	switch (emw->seq) {
	case 0:		//�W�����v�^�C�v�ʂɃt�F�[�h�A�E�g�̃C�x���g���R�[��
		emw->call_seq = 0;

		//�t�B�[���hBGM�t�F�[�h�A�E�g
		Snd_EvMapChangeBgmFadeCheck( fsys, location->zone_id );

		FieldEvent_Call(event, MapJumpFadeOutFuncTbl[emw->JumpType], emw);
		(emw->seq) ++;
		break;
	case 1:	//�t�B�[���h�v���Z�X���I��
		EventCmd_FinishFieldMap(event);
		(emw->seq) ++;
		break;
	case 2:	//���ۂɃf�[�^��V�}�b�v�ɏ���������
		EventCmd_MapChangeByLocation(event, &emw->next);
		(emw->seq) ++;
		break;
	case 3:	//�t�B�[���h�v���Z�X�J�n
#if 0
		//�ړ��|�P�����אڈړ�
		MP_MovePokemonNeighboring(EncDataSave_GetSaveDataPtr(fsys->savedata));
#endif
		EventCmd_StartFieldMap(event);
		(emw->seq) ++;
		break;
	case 4:
		//�W�����v�^�C�v�ʂɁA���@�̏����\�����W�ɃI�t�Z�b�g������
		if (MapJumpPosSetFuncTbl[emw->JumpType] != NULL){
			MapJumpPosSetFuncTbl[emw->JumpType](fsys);
		}
		(emw->seq) ++;
		break;
	case 5:	//�W�����v�^�C�v�ʂɃt�F�[�h�C���̃C�x���g���R�[��
		if( Snd_FadeCheck() != 0 ){								//�T�E���h�t�F�[�h��
			break;
		}
		Snd_EvMapChangeBgmPlay( fsys, location->zone_id );		//�t�B�[���hBGM�Đ�

		//�n���\�����N�G�X�g
		PlaceNameRequestByFsys(fsys);

		emw->call_seq = 0;
		FieldEvent_Call(event, MapJumpFadeInFuncTbl[emw->JumpType], emw);
		(emw->seq) ++;
		break;
	case 6:	//�I������
		sys_FreeMemoryEz(emw);
		return TRUE;
	}
	return FALSE;
}

//-----------------------------------------------------------------------------
// @brief	0:�}�b�g�t�F�[�h�A�E�g�}�b�v�J�ڃC�x���g(�C�x���g�R�[��)
//-----------------------------------------------------------------------------
static BOOL MJUMPEVT_MapFadeOutMat(GMEVENT_CONTROL * event)
{
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	EVENT_MAPCHG_WORK * emw = FieldEvent_GetSpecialWork(event);

	switch (emw->call_seq) {
	case 0:
		Snd_SePlay( SEQ_SE_DP_KAIDAN2 );
/**
		//"�}�b�v�J�ڐ�p"�t�F�[�h�A�E�g �� BGM�Đ�
		{
			LOCATION_WORK* location = &emw->next;
			Snd_MapChangeFadeOutNextPlaySub( fsys, location->zone_id, BGM_FADE_ROOM_MODE );
		}
*/		
		EventCmd_FieldFadeOut(event);
		(emw->call_seq) ++;
		break;
	case 1:
		return TRUE;
	}
	return FALSE;
}
//-----------------------------------------------------------------------------
// @brief	1:�h�A�t�F�[�h�A�E�g�}�b�v�J�ڃC�x���g(�C�x���g�R�[��)
//-----------------------------------------------------------------------------
static BOOL MJUMPEVT_MapFadeOutDoor(GMEVENT_CONTROL * event)
{
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	EVENT_MAPCHG_WORK * emw = FieldEvent_GetSpecialWork(event);
	FLD_3D_ANIME_WORK_PTR	anime_work;
	switch (emw->call_seq) {
	case 0:	//�h�A�A�j�����[�N�m��
		emw->JumpEffectWork = Fld3DAnm_AllocEvent3DAnimeWork();
		anime_work = (FLD_3D_ANIME_WORK_PTR)emw->JumpEffectWork;
		Fld3DAnm_EventSetGrid(	Player_NowGPosXGet( fsys->player ),
								Player_NowGPosZGet( fsys->player ),
								anime_work	);
		(emw->call_seq) ++;
		break;
	case 1:	//�h�A�A�j��
		anime_work = (FLD_3D_ANIME_WORK_PTR)emw->JumpEffectWork;
		if ( Fld3DAnm_EventDoorInAnime(fsys, anime_work) ){
			Fld3DAnm_FreeEvent3DAnimeWork(emw->JumpEffectWork);	//�h�A�A�j�����[�N���
			(emw->call_seq) ++;
		}
		break;		
	case 2:
/**		
		//"�}�b�v�J�ڐ�p"�t�F�[�h�A�E�g �� BGM�Đ�
		{
			LOCATION_WORK* location = &emw->next;
			Snd_MapChangeFadeOutNextPlaySub( fsys, location->zone_id, BGM_FADE_ROOM_MODE );
		}
*/		
		EventCmd_FieldFadeOut(event);
		(emw->call_seq) ++;
		break;
	case 3:		//�I������
		return TRUE;
	}
	return FALSE;
}

//-----------------------------------------------------------------------------
// @brief	2:�G�X�J���[�^�[�t�F�[�h�A�E�g�}�b�v�J�ڃC�x���g(�C�x���g�R�[��)
//-----------------------------------------------------------------------------
static BOOL MJUMPEVT_MapFadeOutEsca(GMEVENT_CONTROL * event)
{
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	EVENT_MAPCHG_WORK * emw = FieldEvent_GetSpecialWork(event);
	FLD_3D_ANIME_WORK_PTR	anime_work;
	switch (emw->call_seq) {
	case 0:	//�A�j�����[�N�m��
		emw->JumpEffectWork = Fld3DAnm_AllocEvent3DAnimeWork();
		anime_work = (FLD_3D_ANIME_WORK_PTR)emw->JumpEffectWork;
		Fld3DAnm_EventSetGrid(	Player_NowGPosXGet( fsys->player ),
								Player_NowGPosZGet( fsys->player ),
								anime_work	);
		(emw->call_seq)++;
		break;
	case 1:	//�G�X�J���[�^�[�A�j���@���
		anime_work = (FLD_3D_ANIME_WORK_PTR)emw->JumpEffectWork;
		if ( Fld3DAnm_EventEscalatorInAnime(fsys, anime_work,Player_DirGet( fsys->player )) ){
			Fld3DAnm_FreeEvent3DAnimeWork(emw->JumpEffectWork);	//�A�j�����[�N���
			(emw->call_seq)++;
		}
		break;		
	case 2:		//�I������	
		return TRUE;
	}
	return FALSE;
}

//-----------------------------------------------------------------------------
// @brief	3:�K�i�t�F�[�h�A�E�g�}�b�v�J�ڃC�x���g(�C�x���g�R�[��)
//-----------------------------------------------------------------------------
static BOOL MJUMPEVT_MapFadeOutStairs(GMEVENT_CONTROL * event)
{
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	EVENT_MAPCHG_WORK * emw = FieldEvent_GetSpecialWork(event);
	FIELD_OBJ_PTR fop;
	switch (emw->call_seq) {
	case 0:	//���@�ړ�
		{
			int dir = Player_DirGet( fsys->player );
			fop = Player_FieldOBJGet( fsys->player );
		
			if (dir == DIR_LEFT){	//������
				FieldOBJ_AcmdSet(fop,AC_WALK_L_16F);
			}else if (dir == DIR_RIGHT){	//�E����
				FieldOBJ_AcmdSet(fop,AC_WALK_R_16F);
			}else{
				GF_ASSERT(0&&"���@�̌������s��");
			}
		}
		(emw->call_seq) ++;
		break;
	case 1:
		fop = Player_FieldOBJGet( fsys->player );
		if( FieldOBJ_AcmdEndCheck(fop) == TRUE ){	//�A�j���I���`�F�b�N
			FieldOBJ_AcmdEnd(fop); //�A�j���I��	
			(emw->call_seq) ++;
		}
		break;
	case 2:
		//���鉹
		Snd_SePlay( SEQ_SE_DP_KAIDAN2 );
		//�t�F�[�h�A�E�g�J�n
		FieldFadeWipeSet(FLD_DISP_BRIGHT_BLACKOUT);
		
		(emw->call_seq) ++;
		break;
	case 3:	
		if (WIPE_SYS_EndCheck()) {
/**			
			//"�}�b�v�J�ڐ�p"�t�F�[�h�A�E�g �� BGM�Đ�
			{
				LOCATION_WORK* location = &emw->next;
				Snd_MapChangeFadeOutNextPlaySub( fsys, location->zone_id, BGM_FADE_ROOM_MODE );
			}
			(emw->call_seq) ++;
*/			
			return TRUE;
		}
		break;
	}
	return FALSE;
}

//-----------------------------------------------------------------------------
// @brief	4:�_���W��������t�F�[�h�A�E�g�}�b�v�J�ڃC�x���g(�C�x���g�R�[��)
//-----------------------------------------------------------------------------
static BOOL MJUMPEVT_MapFadeOutDunIn(GMEVENT_CONTROL * event)
{
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	EVENT_MAPCHG_WORK * emw = FieldEvent_GetSpecialWork(event);
	FIELD_OBJ_PTR player = Player_FieldOBJGet( fsys->player );
	switch (emw->call_seq) {
	case 0:
		{
			FMJ_WORK_PTR work;
			work = MapJump_AllocWork();
			FieldEvent_Call(event, MapJump_EventFadeOutHole, work);
			emw->call_seq++;
		}
		break;
	case 1:
		return TRUE;
	}
	return FALSE;
}

//-----------------------------------------------------------------------------
// @brief	5:�_���W�����o��t�F�[�h�A�E�g�}�b�v�J�ڃC�x���g(�C�x���g�R�[��)
//-----------------------------------------------------------------------------
static BOOL MJUMPEVT_MapFadeOutDunOut(GMEVENT_CONTROL * event)
{
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	EVENT_MAPCHG_WORK * emw = FieldEvent_GetSpecialWork(event);
	FIELD_OBJ_PTR player = Player_FieldOBJGet( fsys->player );
	switch (emw->call_seq) {
	case 0:
		{
			FMJ_WORK_PTR work;
			work = MapJump_AllocWork();
			FieldEvent_Call(event, MapJump_EventFadeOutWhite, work);
			emw->call_seq++;
		}
		break;
	case 1:
		return TRUE;
	}
/**	
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	EVENT_MAPCHG_WORK * emw = FieldEvent_GetSpecialWork(event);
	switch (emw->call_seq) {
	case 0:
		//�Y�[��������
		//�J�����Y�[��
		(emw->call_seq) ++;
		break;
	case 1:	//�J�����Y�[���҂�
		if(1){
			FIELD_OBJ_PTR fop;
			fop = Player_FieldOBJGet( fsys->player );
			//��l������
			FieldOBJ_StatusBitSet_Vanish( fop, TRUE );
			//���鉹
			Snd_SePlay( SEQ_SE_DP_KAIDAN2 );
			//���C�v�X�^�[�g	�z���C�g�A�E�g
			WIPE_SYS_Start(	WIPE_PATTERN_WMS, WIPE_TYPE_FADEOUT,
							WIPE_TYPE_FADEOUT,0x7fff,COMM_BRIGHTNESS_SYNC,1,HEAPID_WORLD );
			(emw->call_seq) ++;
		}
		break;
	case 2:	//���C�v�I���҂�
		if ( WIPE_SYS_EndCheck() ){
			//"�}�b�v�J�ڐ�p"�t�F�[�h�A�E�g �� BGM�Đ�
			LOCATION_WORK* location = &emw->next;
			Snd_MapChangeFadeOutNextPlaySub( fsys, location->zone_id, BGM_FADE_ROOM_MODE );
			(emw->call_seq) ++;
		}
		break;
	case 3:		//�I������
		return TRUE;
	}
*/	
	return FALSE;
}

//-----------------------------------------------------------------------------
// @brief	0:�O�ɏo���Ƃ��t�F�[�h�C���}�b�v�J�ڃC�x���g(�C�x���g�R�[��)
//-----------------------------------------------------------------------------
static BOOL MJUMPEVT_MapFadeInDoor(GMEVENT_CONTROL * event)
{
	FIELD_OBJ_PTR fop;
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	EVENT_MAPCHG_WORK * emw = FieldEvent_GetSpecialWork(event);
	FLD_3D_ANIME_WORK_PTR	anime_work;
	switch (emw->call_seq) {
	case 0:
		{
			u8 attr;
			FIELD_OBJ_PTR player = Player_FieldOBJGet( fsys->player );
			attr = GetAttributeLSB( fsys,
									Player_NowGPosXGet( fsys->player ),
									Player_NowGPosZGet( fsys->player ) );
			if (MATR_IsDoor(attr)){
				//���@���\��
				FieldOBJ_StatusBitSet_Vanish( player, TRUE );
				(emw->call_seq) = 1;
			}else{
				FMJ_WORK_PTR work;
				work = MapJump_AllocWork();
				FieldEvent_Call(event, MapJump_EventFadeInShutSlide, work);
				(emw->call_seq) = 3;
			}
		}
		break;
	case 1:
		//�h�A�A�j�����[�N�m��
		emw->JumpEffectWork = (FLD_3D_ANIME_WORK_PTR)Fld3DAnm_AllocEvent3DAnimeWork();
		anime_work = (FLD_3D_ANIME_WORK_PTR)emw->JumpEffectWork;
		Fld3DAnm_EventSetGrid(	Player_NowGPosXGet( fsys->player ),
								Player_NowGPosZGet( fsys->player ),
								anime_work	);
		(emw->call_seq) ++;
		break;
	case 2:			//�h�A�A�j��
		anime_work = (FLD_3D_ANIME_WORK_PTR)emw->JumpEffectWork;
		if ( Fld3DAnm_EventDoorOutAnime(fsys, anime_work) ){
			Fld3DAnm_FreeEvent3DAnimeWork(anime_work);	//�h�A�A�j�����[�N���
			{
				FIELD_OBJ_PTR player = Player_FieldOBJGet( fsys->player );
				//���@��\��
				FieldOBJ_StatusBitSet_Vanish( player, FALSE );
			}
			return TRUE;		//�I��
		}
		break;
	case 3:
		return TRUE;
	}
	return FALSE;
}

//-----------------------------------------------------------------------------
// @brief	1,4:�����A�_���W�����������Ƃ��u���b�N�C���}�b�v�J�ڃC�x���g(�C�x���g�R�[��)
//-----------------------------------------------------------------------------
static BOOL MJUMPEVT_MapFadeInBlack(GMEVENT_CONTROL * event)
{
	FIELD_OBJ_PTR fop;
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	EVENT_MAPCHG_WORK * emw = FieldEvent_GetSpecialWork(event);
	FLD_3D_ANIME_WORK_PTR	anime_work;
	switch (emw->call_seq) {
	case 0:
		{
			//�����Ƀh�A���������肷��̂œ��ꏈ������
			u8 attr;
			FIELD_OBJ_PTR player = Player_FieldOBJGet( fsys->player );
			attr = GetAttributeLSB( fsys,
									Player_NowGPosXGet( fsys->player ),
									Player_NowGPosZGet( fsys->player ) );
			if (MATR_IsDoor(attr)){	//�h�A����������
				//���@���\��
				FieldOBJ_StatusBitSet_Vanish( player, TRUE );
				emw->call_seq = 1;		//�R�[����̃C�x���g�V�[�P���X1����X�^�[�g
				FieldEvent_Change(event,MJUMPEVT_MapFadeInDoor,emw);
			}else{					//�h�A�Ȃ�
				FMJ_WORK_PTR work;
				//�t�F�[�h�C���J�n
				work = MapJump_AllocWork();
				FieldEvent_Call(event, MapJump_EventFadeInBlack, work);
				(emw->call_seq) ++;
			}
		}
		break;
	case 1:
		return TRUE;
	}
	return FALSE;
}

//-----------------------------------------------------------------------------
// @brief	2:�G�X�J���[�^�[�t�F�[�h�C���}�b�v�J�ڃC�x���g(�C�x���g�R�[��)
//-----------------------------------------------------------------------------
static BOOL MJUMPEVT_MapFadeInEsca(GMEVENT_CONTROL * event)
{
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	EVENT_MAPCHG_WORK * emw = FieldEvent_GetSpecialWork(event);
	FLD_3D_ANIME_WORK_PTR	anime_work;
	switch (emw->call_seq) {
	case 0:	//�A�j�����[�N�m��
		emw->JumpEffectWork = Fld3DAnm_AllocEvent3DAnimeWork();
		anime_work = (FLD_3D_ANIME_WORK_PTR)emw->JumpEffectWork;
		Fld3DAnm_EventSetGrid(	Player_NowGPosXGet( fsys->player ),
								Player_NowGPosZGet( fsys->player ),
								anime_work	);
		(emw->call_seq)++;
		break;
	case 1:	//�G�X�J���[�^�[�A�j��	�~���
		anime_work = (FLD_3D_ANIME_WORK_PTR)emw->JumpEffectWork;
		if ( Fld3DAnm_EventEscalatorOutAnime(fsys, anime_work,Player_DirGet( fsys->player )) ){
			Fld3DAnm_FreeEvent3DAnimeWork(emw->JumpEffectWork);	//�A�j�����[�N���
			(emw->call_seq)++;
		}
		break;
	case 2:			//�I������
		return TRUE;
	}
	return FALSE;
}

//-----------------------------------------------------------------------------
// @brief	3:�K�i�t�F�[�h�C���}�b�v�J�ڃC�x���g(�C�x���g�R�[��)
//-----------------------------------------------------------------------------
static BOOL MJUMPEVT_MapFadeInStairs(GMEVENT_CONTROL * event)
{
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	EVENT_MAPCHG_WORK * emw = FieldEvent_GetSpecialWork(event);
	FIELD_OBJ_PTR fop;
	switch (emw->call_seq) {
	case 0:	//���@�ړ�
		//�t�F�[�h�C���J�n
		FieldFadeWipeSet(FLD_DISP_BRIGHT_BLACKIN);
		fop = Player_FieldOBJGet( fsys->player );
		
		if( /*FieldOBJ_AcmdSetCheck(fop) == TRUE*/1 ){	//�A�j���Z�b�g�ł��邩?
			int dir;
			dir = Player_DirGet( fsys->player );
			if (dir == DIR_LEFT){	//������
				FieldOBJ_AcmdSet(fop,AC_WALK_L_16F);	//�o����B�C�ӂ̃A�j���Z�b�g
			}else if (dir == DIR_RIGHT){	//�E����
				FieldOBJ_AcmdSet(fop,AC_WALK_R_16F);	//�o����B�C�ӂ̃A�j���Z�b�g
			}else{
				GF_ASSERT(0&&"���@�̌������s��");
			}
		}else{
			GF_ASSERT(0&&"�A�j���o�^�ł��Ȃ�����");
		}
		(emw->call_seq) ++;
		break;
	case 1:	
		fop = Player_FieldOBJGet( fsys->player );
		if( FieldOBJ_AcmdEndCheck(fop) == TRUE ){	//�A�j���I���`�F�b�N
			FieldOBJ_AcmdEnd(fop); //�A�j���I��	
			(emw->call_seq) ++;
		}
		break;
	case 2:	
		if (WIPE_SYS_EndCheck()) {
			(emw->call_seq) ++;
		}
		break;
	case 3:		//�I������
		return TRUE;
	}
	return FALSE;

}

//-----------------------------------------------------------------------------
// @brief	5:�_���W�����o��t�F�[�h�C���}�b�v�J�ڃC�x���g(�C�x���g�R�[��)
//-----------------------------------------------------------------------------
static BOOL MJUMPEVT_MapFadeInDunOut(GMEVENT_CONTROL * event)
{
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	EVENT_MAPCHG_WORK * emw = FieldEvent_GetSpecialWork(event);
	FIELD_OBJ_PTR player = Player_FieldOBJGet( fsys->player );
	switch (emw->call_seq) {
	case 0:
		{
			FMJ_WORK_PTR work;
			work = MapJump_AllocWork();
			FieldEvent_Call(event, MapJump_EventFadeInWhite, work);
			emw->call_seq++;
		}
		break;
	case 1:
		return TRUE;
/**		
		//���@���\��
		FieldOBJ_StatusBitSet_Vanish( player, TRUE );
		(emw->call_seq)++;
		break;
	case 1:
		//���C�v�X�^�[�g	�z���C�g�C��
		WIPE_SYS_Start(	WIPE_PATTERN_WMS, WIPE_TYPE_FADEIN,
						WIPE_TYPE_FADEIN,0x7fff,COMM_BRIGHTNESS_SYNC,1,HEAPID_WORLD );
		(emw->call_seq) ++;
		break;
	case 2:	//���@��\�����āA�����ʂ�1���O�i
		FieldOBJ_StatusBitSet_Vanish( player, FALSE );
		(emw->call_seq) ++;
		break;
	case 3:
		{
			FIELD_OBJ_PTR fop;
			fop = Player_FieldOBJGet( fsys->player );
			if( FieldOBJ_AcmdEndCheck(fop) == TRUE ){	//�A�j���I���`�F�b�N
				FieldOBJ_AcmdEnd(fop); //�A�j���I��	
				(emw->call_seq) ++;
			}
		}
		break;
	case 4:
		if (WIPE_SYS_EndCheck()) {
			return TRUE;
		}
*/		
	}
	return FALSE;
}

//-----------------------------------------------------------------------------
// @brief 2:�W�����v��A�G�X�J���[�^�[�A�j���[�V�������l���A���@�̏����ʒu��ύX����
//-----------------------------------------------------------------------------
static void SetEscalatorIOPos(FIELDSYS_WORK *fsys)
{
	int dir;
	VecFx32 vec;
	
	//�}�b�v�o���ʒu���獶�E�P�O���b�h�̏ꏊ�Ɏ��@���o��
	//���@�̍��W,�������擾
	dir = Player_DirGet( fsys->player );
	Player_VecPosGet( fsys->player, &vec );
	if (dir == DIR_RIGHT){
		vec.x -= (FX32_ONE*16);
	}else{	//(dir == DIR_LEFT)
		vec.x += (FX32_ONE*16);
	}
	//�����擾
	vec.y = GetHeightPack(	fsys, vec.y, vec.x, vec.z, NULL);

	//���W�Z�b�g
	Player_VecPosInit( fsys->player, &vec, dir );
	//���@���W���ړ������̂Ńo�C���h���Ȃ���
	GFC_ReSetCameraTarget(Player_VecPosPtrGet(fsys->player), fsys->camera_ptr);
	GFC_BindCameraTarget(Player_VecPosPtrGet(fsys->player), fsys->camera_ptr);
}

//-----------------------------------------------------------------------------
// @brief 3:�W�����v��A�K�i�A�j���[�V�������l���A���@�̏����ʒu��ύX����
//-----------------------------------------------------------------------------
static void SetStairsIOPos(FIELDSYS_WORK *fsys)
{
	int x,z,dir;
	VecFx32 vec;
	u8 attr;
	//���@�̌������݂āA�}�b�v�o���ʒu���獶�E�P�O���b�h���ꂽ�ꏊ�Ɏ��@���o��
	//���@�̍��W,�������擾
	dir = Player_DirGet( fsys->player );
	Player_VecPosGet( fsys->player, &vec );
	
	x = Player_NowGPosXGet( fsys->player );
	z = Player_NowGPosZGet( fsys->player );
	
	attr = GetAttributeLSB( fsys, x, z );
	if (MATR_IsRightStairs(attr)){//�E�K�i�̏ꍇ
		vec.x += (FX32_ONE*16);	//�E�ւP�O���b�h
		dir = DIR_LEFT;
	}else if(MATR_IsLeftStairs(attr)){	//���K�i�̏ꍇ
		vec.x -= (FX32_ONE*16);	//���ւP�O���b�h
		dir = DIR_RIGHT;
	}else{
		//GF_ASSERT(0&&"�K�i�A�g���r���[�g���͂��Ă��܂���");
		OS_Printf("�K�i�A�g���r���[�g���͂��Ă��܂���\n");
	}
	
	//�����擾
	vec.y = GetHeightPack(	fsys, vec.y, vec.x, vec.z, NULL);
	//���W�Z�b�g
	Player_VecPosInit( fsys->player, &vec, dir );
	//���@���W���ړ������̂Ńo�C���h���Ȃ���
	GFC_ReSetCameraTarget(Player_VecPosPtrGet(fsys->player), fsys->camera_ptr);
	GFC_BindCameraTarget(Player_VecPosPtrGet(fsys->player), fsys->camera_ptr);
}

