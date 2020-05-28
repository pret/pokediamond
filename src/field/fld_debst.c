//============================================================================================
/**
 *	@file	fld_debst.c
 *	@brief	�t�B�[���h�f�o�b�O���j���[�@�풓�̈�
 *	@author	Miyuki Iwasawa
 *	@date	06.03.16
 *
 *	�t�B�[���h�f�o�b�O���j���[�\�[�X�ŏ풓���ė~�������̂͂���
 */
//============================================================================================

#ifdef PM_DEBUG
#include "common.h"
#include "system/bmp_list.h"
#include "system/bmp_menu.h"
#include "fld_bmp.h"
#include "system/fontproc.h"
#include "fieldmap.h"
#include "fieldsys.h"
#include "ev_mapchange.h"
#include "fld_debug.h"
#include "zonedata.h"
#include "system/builddate.h"
#include "system/window.h"
#include "system/wipe.h"
#include "mapdefine.h"
#include "system/snd_tool.h"
#include "field/field.h"
#include "field/field_matrix.h"

#include "application/townmap.h"

#include "system/bmp_cursor.h"
#include "system/arc_util.h"


//�L���ɂ���ƃf�o�b�O���j���[�u������Ƃԁv�ɃJ�b�g�C�������� 060505 kaga
//#define DEBUG_SKYJUMP_CUTIN_ON

#ifdef DEBUG_SKYJUMP_CUTIN_ON
#include "field_cutin.h"
#endif

//SkyJump
#ifdef DEBUG_SKYJUMP_CUTIN_ON
typedef struct _DEB_SKYJUMP{
	FIELDSYS_WORK* fsys;
	void* pWork;
	TCB_PTR tcb_cutin;
	int	seq;
	int	wipe_f;
}DEB_SKYJUMP;
#else	//DEBUG_SKYJUMP_CUTIN_ON off
typedef struct _DEB_SKYJUMP{
	FIELDSYS_WORK* fsys;
	void* pWork;
	int	seq;
	int	wipe_f;
}DEB_SKYJUMP;
#endif

//�v���g�^�C�v
void DebugSkyJump_CreateTask(FIELDSYS_WORK* fsys);
void DBJump_JumpMapControl(struct _FIELDSYS_WORK * fsys);

/**
 *	@brief	�f�o�b�O����ԃR���g���[���^�X�N
 */

extern void FieldTMap_CallDataSet(FIELDSYS_WORK* fsys,TOWNMAP_PARAM *tp,int mode);

#ifdef DEBUG_SKYJUMP_CUTIN_ON
static void DebugSkyjumpTask(TCB_PTR tcb,void* work)
{
	DEB_SKYJUMP	*wp = (DEB_SKYJUMP*)work;
	TOWNMAP_PARAM* twork;
	
	switch(wp->seq){
	case 0:
		wp->wipe_f = 0;
		WIPE_SYS_Start(WIPE_PATTERN_WMS,
				WIPE_TYPE_FADEOUT,
				WIPE_TYPE_FADEOUT,0x0000,COMM_BRIGHTNESS_SYNC,1,HEAPID_BASE_DEBUG
				);
		break;
	case 1:
		if(!WIPE_SYS_EndCheck()){
			return;
		}
		//�^�E���}�b�v�@����ԃ��[�h�Ăяo��
		wp->pWork = sys_AllocMemory(HEAPID_BASE_DEBUG,sizeof(TOWNMAP_PARAM));
		FieldTMap_CallDataSet(wp->fsys,wp->pWork,TMAP_MJUMP);
		//�f�o�b�O���[�h�t���OON
		twork = (TOWNMAP_PARAM*)wp->pWork;
		twork->debug_f = TRUE;
		FieldTMap_SetProc(wp->fsys,wp->pWork);
		break;
	case 2:
		//�^�E���}�b�v�v���Z�X�I���҂�
		if(FieldEvent_Cmd_WaitSubProcEnd(wp->fsys)){
			return;
		}
		//�t�B�[���h�v���Z�X���A
		FieldEvent_Cmd_SetMapProc(wp->fsys);
		break;
	case 3:
		//�t�B�[���h�v���Z�X�J�n�I���҂�
		if(!FieldEvent_Cmd_WaitMapProcStart(wp->fsys)){
			return;
		}
		
		//�u���b�N�C�����N�G�X�g
		wp->wipe_f = 0;
		WIPE_SYS_Start(WIPE_PATTERN_WMS,
				WIPE_TYPE_FADEIN,
				WIPE_TYPE_FADEIN,0x0000,COMM_BRIGHTNESS_SYNC,1,HEAPID_BASE_DEBUG
				);
		break;
	case 4:
		//�t�F�[�h�C���҂�
		if(!WIPE_SYS_EndCheck()){
			return;
		}
		
		//�p�����[�^�擾
		twork = (TOWNMAP_PARAM*)wp->pWork;
		if(!twork->retval){
			wp->seq = 6;
			return;
		}
		
		//�J�b�g�C�����N�G�X�g
		{
			POKEMON_PARAM *param =
				PokeParty_GetMemberPointer(
					SaveData_GetTemotiPokemon(wp->fsys->savedata), 0 );
			
			wp->tcb_cutin = FieldCutIn_Init(
				wp->fsys, CUTIN_TYPE_SKY,
				param, Player_SexGet(wp->fsys->player) );
		}
		
		break;
	case 5:
		
		//�J�b�g�C���I���҂�
		if( FieldCutIn_EndCheck(wp->tcb_cutin) == FALSE ){
			return;
		}
		FieldCutIn_End( wp->tcb_cutin );
		
		twork = (TOWNMAP_PARAM*)wp->pWork;
		
		//�W�����v
		EventSet_MapChangeBySky(wp->fsys,
			twork->ret_zone,DOOR_ID_JUMP_CODE,
			twork->ret_x*32+16,twork->ret_z*32+16, DIR_DOWN);
		break;
	case 6:
		sys_FreeMemoryEz(wp->pWork);
		sys_FreeMemoryEz(wp);
		TCB_Delete(tcb);
		return;
	}
	wp->seq++;
}
#else	//DEBUG_SKYJUMP_CUTIN_ON off
static void DebugSkyjumpTask(TCB_PTR tcb,void* work)
{
	DEB_SKYJUMP	*wp = (DEB_SKYJUMP*)work;
	TOWNMAP_PARAM* twork;
	
	switch(wp->seq){
	case 0:
		wp->wipe_f = 0;
		WIPE_SYS_Start(WIPE_PATTERN_WMS,
				WIPE_TYPE_FADEOUT,
				WIPE_TYPE_FADEOUT,0x0000,COMM_BRIGHTNESS_SYNC,1,HEAPID_BASE_DEBUG
				);
		break;
	case 1:
		if(!WIPE_SYS_EndCheck()){
			return;
		}
		//�^�E���}�b�v�@����ԃ��[�h�Ăяo��
		wp->pWork = sys_AllocMemory(HEAPID_BASE_DEBUG,sizeof(TOWNMAP_PARAM));
		FieldTMap_CallDataSet(wp->fsys,wp->pWork,TMAP_MJUMP);
		//�f�o�b�O���[�h�t���OON
		twork = (TOWNMAP_PARAM*)wp->pWork;
		twork->debug_f = TRUE;
		FieldTMap_SetProc(wp->fsys,wp->pWork);
		break;
	case 2:
		//�^�E���}�b�v�v���Z�X�I���҂�
		if(FieldEvent_Cmd_WaitSubProcEnd(wp->fsys)){
			return;
		}
		//�t�B�[���h�v���Z�X���A
		FieldEvent_Cmd_SetMapProc(wp->fsys);
		break;
	case 3:
		//�t�B�[���h�v���Z�X�J�n�I���҂�
		if(!FieldEvent_Cmd_WaitMapProcStart(wp->fsys)){
			return;
		}
		//�u���b�N�C�����N�G�X�g
		wp->wipe_f = 0;
		WIPE_SYS_Start(WIPE_PATTERN_WMS,
				WIPE_TYPE_FADEIN,
				WIPE_TYPE_FADEIN,0x0000,COMM_BRIGHTNESS_SYNC,1,HEAPID_BASE_DEBUG
				);
		break;
	case 4:
		//�t�F�[�h�C���҂�
		if(!WIPE_SYS_EndCheck()){
			return;
		}
		//�p�����[�^�擾
		twork = (TOWNMAP_PARAM*)wp->pWork;
		if(!twork->retval){
			break;
		}
	
		//�W�����v
		EventSet_EasyMapChange(wp->fsys,
			twork->ret_zone,DOOR_ID_JUMP_CODE,
			twork->ret_x*32+16,twork->ret_z*32+16, DIR_DOWN);
		break;
	case 5:
		sys_FreeMemoryEz(wp->pWork);
		sys_FreeMemoryEz(wp);
		TCB_Delete(tcb);
		return;
	}
	wp->seq++;
}
#endif

/**
 *	@brief	�f�o�b�O����ԁ@�^�X�N�o�^
 */
void DebugSkyJump_CreateTask(FIELDSYS_WORK* fsys)
{
	DEB_SKYJUMP *wp;

	//����ԃ^�X�N�쐬
	wp = sys_AllocMemory(HEAPID_BASE_DEBUG,sizeof(DEB_SKYJUMP));
	MI_CpuClear8(wp,sizeof(DEB_SKYJUMP));

	wp->fsys = fsys;
	TCB_Add(DebugSkyjumpTask,wp,0);
}

typedef struct {
	int seq;
	int subseq;
	int next_zone_id;
	int next_door_id;
	int next_x;
	int next_z;
	BOOL brightness;
}EVENT_UGCHG_WORK;

typedef struct {
	GF_BGL_BMPWIN	win;//BMP
	u8 cur_pos;
	int grid_val[2];	// 0=x�A1=Z
	FIELDSYS_WORK * fsys;
	BMPCURSOR *Cursor;
}JUMP_CONT;

/**
 *	@brief	���W�w��W�����v�t�F�[�h�A�E�g
 */
static BOOL Sub_FadeOut(GMEVENT_CONTROL * event)
{
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	EVENT_UGCHG_WORK * mcw = FieldEvent_GetSpecialWork(event);

	switch (mcw->subseq) {
		case 0:	
		GameSystem_FinishFieldProc(fsys);
		(mcw->subseq) ++;
		break;
	case 1:
		if (!GameSystem_CheckFieldProcExists(fsys)) {
			mcw->subseq = 0;
			return TRUE;
		}
		break;
	}
	return FALSE;
}

/**
 *	@brief	���W�w��W�����v�t�F�[�h�C��
 */
static BOOL Sub_FadeIn(GMEVENT_CONTROL * event)
{
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	EVENT_UGCHG_WORK * mcw = FieldEvent_GetSpecialWork(event);

	switch (mcw->subseq) {
	case 0:
		GameSystem_CreateFieldProc(fsys);
		(mcw->subseq) ++;
		break;
	case 1:
		if (FieldEvent_Cmd_WaitMapProcStart(fsys)) {
			mcw->subseq = 0;
			return TRUE;
		}
		break;
	}
	return FALSE;
}


/**
 *	@brief	���W�w��W�����v�`��
 */
static void DrawJumpCont(JUMP_CONT *work)
{
	u16 buff[10];
	
	GF_BGL_BmpWinDataFill( &work->win, 0x0f );
	
	BMPCURSOR_Print( work->Cursor, &work->win, 0, work->cur_pos*16 );
	
	{
		STRBUF* str1 = STRBUF_Create(3, HEAPID_BASE_DEBUG);
		STRBUF* str2 = STRBUF_Create(3, HEAPID_BASE_DEBUG);
		STRBUF_SetNumber( str1, work->grid_val[0], 2, NUMBER_DISPTYPE_ZERO, NUMBER_CODETYPE_DEFAULT );
		GF_STR_PrintSimple(&work->win, FONT_SYSTEM, str1, 2*8, 0, MSG_ALLPUT, NULL );
		STRBUF_SetNumber( str2, work->grid_val[1], 2, NUMBER_DISPTYPE_ZERO, NUMBER_CODETYPE_DEFAULT );
		GF_STR_PrintSimple(&work->win, FONT_SYSTEM, str2, 2*8, 16, MSG_ALLPUT, NULL );
		STRBUF_Delete(str2);
		STRBUF_Delete(str1);
	}
	
	GF_BGL_BmpWinOn( &work->win );
}

/**
 *	@brief	���W�w��W�����v�C�x���g
 */
static BOOL GMEVENT_JumpMap(GMEVENT_CONTROL * event)
{
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	EVENT_UGCHG_WORK * mcw = FieldEvent_GetSpecialWork(event);
		
	switch (mcw->seq) {
	case 0:
		if(Sub_FadeOut(event)){		// �v���b�NChange
			(mcw->seq) ++;
		}
		break;
	case 1:
		EventCmd_MapChange(event, mcw->next_zone_id, mcw->next_door_id,
				mcw->next_x, mcw->next_z, DIR_DOWN);

		(mcw->seq) ++;
		break;
	case 2:
		if(Sub_FadeIn(event)){		// �v���b�NChange
			(mcw->seq) ++;
		}
		break;
	case 3:
		///PlaceNameRequest(fsys->place_name_cont,0);//�n���\��
		sys_FreeMemoryEz(mcw);
		return TRUE;
	}
	return FALSE;
}

/**
 *	@brief	���W�w��W�����v�R���g���[��
 */
static void DebugJumpControlTask(TCB_PTR tcb,void* work)
{
	JUMP_CONT	*wp;
	BOOL write;
	
	wp = (JUMP_CONT*)work;

	write = FALSE;
	//�L�[���씻��
	if ( (sys.trg & PAD_KEY_DOWN) ||
			(sys.trg & PAD_KEY_UP) ){
		//�J�[�\��������
		//�J�[�\���ړ�
		wp->cur_pos = (wp->cur_pos+1)%2;
		//�J�[�\����`��
		write = TRUE;
	}else if(sys.trg & PAD_KEY_LEFT){
		//�l�����炷
		if (wp->grid_val[wp->cur_pos]-1<0){
			wp->grid_val[wp->cur_pos] = 29;
		}else{
			wp->grid_val[wp->cur_pos]--;
		}
		write = TRUE;
	}else if(sys.trg & PAD_KEY_RIGHT){
		//�l�𑝂₷
		wp->grid_val[wp->cur_pos] = (wp->grid_val[wp->cur_pos]+1)%30;
		write = TRUE;
	}

	if (write){
		DrawJumpCont(wp);
	}


	if(sys.trg & PAD_BUTTON_A){
		//�W�����v
		EVENT_UGCHG_WORK * mcw;

		//�C�x���g����
		mcw = sys_AllocMemoryLo(HEAPID_BASE_DEBUG, sizeof(EVENT_UGCHG_WORK));
		mcw->seq = 0;
		mcw->subseq = 0;

		{
			int x,z;
			x = wp->grid_val[0];
			z = wp->grid_val[1];
			
			mcw->next_door_id = DOOR_ID_JUMP_CODE;
			mcw->next_x = x*32+16;
			mcw->next_z = z*32+16;
			//mcw->next_dir = DIR_DOWN;
		
			if (wp->fsys->location->zone_id == ZONE_ID_UG){//���n��
				mcw->next_zone_id = ZONE_ID_UG;
				///FieldEvent_Set(wp->fsys, GMEVENT_JumpMapForUG, mcw);
				JumpUnderGroundDirect(wp->fsys,x,z);
			}else{											//���n��
				mcw->next_zone_id = GetZoneIDFromMatrixID(	wp->fsys->World,
															MATRIX_ID_SINOU,
															wp->grid_val[0],
															wp->grid_val[1],
															30);
				FieldEvent_Set(wp->fsys, GMEVENT_JumpMap, mcw);
			}
		}
		GF_BGL_BmpWinOff( &wp->win );
		GF_BGL_BmpWinDel( &wp->win );
		//���[�N�������J��
		BMPCURSOR_Delete(  wp->Cursor );
		sys_FreeMemoryEz(work);
		//�^�X�N����
		TCB_Delete(tcb);
		//OBJ���̓����~����
		FieldSystemProc_SeqHoldEnd();
		return;
	}
	//���j���[�L�����Z��
	if(sys.trg & PAD_BUTTON_B){
		GF_BGL_BmpWinOff( &wp->win );
		GF_BGL_BmpWinDel( &wp->win );
		//���[�N�������J��
		BMPCURSOR_Delete(  wp->Cursor );
		sys_FreeMemoryEz(work);
		//�^�X�N����
		TCB_Delete(tcb);
		//OBJ���̓����~����
		FieldSystemProc_SeqHoldEnd();
		return;
	}
}

/**
 *	@brief	���W�w��W�����v
 */
void DBJump_JumpMapControl(struct _FIELDSYS_WORK * fsys)
{
	JUMP_CONT *d_work;

	//�n��ȊO�͖���
	if ( (ZoneData_GetMatrixID(fsys->location->zone_id) != MATRIX_ID_FIELD)&&
			(ZoneData_GetMatrixID(fsys->location->zone_id) != MATRIX_ID_UNDER_GROUND) ){
		//OBJ���̓����~����
		FieldSystemProc_SeqHoldEnd();
		return;
	}

	d_work = sys_AllocMemory(HEAPID_BASE_DEBUG,sizeof(JUMP_CONT));
	d_work->fsys = fsys;
	//�J�[�\��������
	d_work->cur_pos = 0;
	d_work->Cursor = BMPCURSOR_Create(HEAPID_BASE_DEBUG);
	//���݃u���b�N�擾
	d_work->grid_val[0] = Player_NowGPosXGet( fsys->player ) / 32;
	d_work->grid_val[1] = Player_NowGPosZGet( fsys->player ) / 32;
	//���C�������^�X�N�ǉ�
	TCB_Add(DebugJumpControlTask,d_work,0);

	GF_BGL_BmpWinAdd( fsys->bgl,&d_work->win,GF_BGL_FRAME3_M, 0, 0, 6, 4, 1, 1 );
	
	SystemFontPaletteLoad( PALTYPE_MAIN_BG, 16<<1, HEAPID_BASE_DEBUG );
	//���݃u���b�N�A�J�[�\���\��
	DrawJumpCont(d_work);

	return;
}

//============================================================================================
//
//
//		RTC����Ăяo��
//
//
//============================================================================================
#include "debug/d_rtcmenu.h"

FS_EXTERN_OVERLAY(title_debug);

static const PROC_DATA DebugRtcProcData = {
	DebugRtcMenuProc_Init,
	DebugRtcMenuProc_Main,
	DebugRtcMenuProc_End,
	FS_OVERLAY_ID(title_debug),
};

//------------------------------------------------------------------
//------------------------------------------------------------------
static BOOL GMEVENT_DebugRtcControl(GMEVENT_CONTROL * event)
{
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	int *seq = FieldEvent_GetSeqWork(event);

	switch (*seq) {
	case 0:
		GameSystem_StartSubProc(fsys, &DebugRtcProcData, NULL);
		(*seq) ++;
		break;
	case 1:
		if (FieldEvent_Cmd_WaitSubProcEnd(fsys) == FALSE) {
			FieldEvent_Cmd_SetMapProc(fsys);
			(*seq) ++;
		}
		break;
	case 2:
		if (FieldEvent_Cmd_WaitMapProcStart(fsys) == FALSE) {
			return TRUE;
		}
		break;
	}
	return FALSE;
}

//------------------------------------------------------------------
/**
 * @brief
 */
//------------------------------------------------------------------
void EventSet_DebugRtcCotrol(FIELDSYS_WORK * fsys)
{
	FieldEvent_Set(fsys, GMEVENT_DebugRtcControl, NULL);
}




#endif	//PM_DEBUG
