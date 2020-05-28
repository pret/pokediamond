//============================================================================================
/**
 * @file	fieldmap.c
 * @bfief	�t�B�[���h�}�b�v
 * @author	GAME FREAK inc.
 */
//============================================================================================

#include "common.h"
#include "system/bmp_list.h"
#include "system/bmp_menu.h"
#include "system/palanm.h"
#include "system/pm_rtc.h"
#include "talk_msg.h"
#include "vram_transfer_manager.h"
#include "vram_transfer_anm.h"
#include "fieldsys.h"
#include "fieldmap_work.h"
#include "sxy.h"
#include "fld_debug.h"
#include "worldmap.h"
#include "mapresource.h"
#include "system/snd_tool.h"
#include "fld_bgm.h"
#include "div_map.h"
#include "system/pm_overlay.h"

#include "camera_move_test.h"
#include "field_light.h"
#include "field_anime.h"
#include "field_glb_state.h"
#include "field_event.h"
#include "fieldobj.h"
#include "weather_sys.h"

#include "player.h"
#include "field_anime.h"
#include "effect_uground.h"

#include "system/render_oam.h"
#include "system/arc_util.h"

#include "debug_saito.h"

#include "fieldmap.h"

#include "mapdefine.h"
#include "zonedata.h"
#include "eventdata.h"

#include "field_3d_anime.h"
#include "place_name.h"	//�n���\��

#include "field_effect.h"

#include "script.h"

#include "field_subscreen.h"

#include "situation_local.h"	//Situation_GetTMFootMark
#include "townmap_footmark.h"	//TMFootMark_Update
#include "honey_tree_enc.h"		//HTE_SetHoneyTreeAnimeCallBack

#include "field_camera.h"
#include "ev_time.h"
#include "ev_mapchange.h"		//MapChg_UpdateGameData

#include "fieldmap_func.h"
#include "field_gimmick.h"
#include "field_poketch.h"

#include "system/wipe.h"		//for wipe

#include "ug_base_layout.h"
#include "mapdata_weather.h"
#include "comm_player.h"    //���j���[���畜�A��������FIELDOBJ�ʒu

#include "quick_sand.h"

#include "system/pm_debug_wifi.h"

#ifdef PM_DEBUG
#include "debug_3d_draw_count.h"
#endif


// WIFI�@�ΐ�AUTOӰ�ރf�o�b�N
#ifdef _WIFI_DEBUG_TUUSHIN

extern WIFI_DEBUG_BATTLE_WK WIFI_DEBUG_BATTLE_Work;
#endif	//_WIFI_DEBUG_TUUSHIN

//============================================================================================
//	�萔��`
//============================================================================================

#define	BG_CLEAR_COLOR		( 0x0000 )

#define	SET_FIELD_ANIME		( 1 )
#define	SET_DIVMAP_LOAD		( 2 )
#define	SET_MAP3D_WRITE		( 4 )
#define	SET_FIELD_3D_ANIME	( 8 )

#define	SET_FUNC_CHECK(p,flg)	( p & flg )

//** Vram�]���}�l�[�W���[�^�X�N�� **//
#define VRAM_TRANFER_TASK_NUM	(128)

//** CharManager PlttManager�p **//
#define FLD_CHAR_CONT_NUM				(20)
#define FLD_CHAR_VRAMTRANS_MAIN_SIZE	(0x4000)
#define FLD_CHAR_VRAMTRANS_SUB_SIZE		(0x4000)
#define FLD_PLTT_CONT_NUM				(20)

//�����}�b�v�f�[�^�̒n�`�p�������ƍ����f�[�^�p�������̃T�C�Y��`
#define GROUND_MEM_SIZE			(0xf000)
#define HEIGHT_MEM_SIZE			(0x9000)
#define UNDER_GROUND_MEM_SIZE	(0xa800)
#define UNDER_HEIGHT_MEM_SIZE	(0x0)

//�v���W�F�N�V�����}�g���N�X�𑀍삷��ۂ̂y�I�t�Z�b�g
#define	PRO_MAT_Z_OFS	(4)

//�g�������̌�
#define EX_HEIGHT_NUM	(8)

//============================================================================================
//	�v���g�^�C�v�錾
//============================================================================================
static void bg_set( GF_BGL_INI * ini );
static void bg_exit( GF_BGL_INI * ini );
static void join_clact_oam_init(void);				// �Z���A�N�^�[�p���LOAM�}�l�[�W���̏�����
static void clact_delete(void);		// �Z���A�N�^�[�̔j��

static void field_glb_state_init(GLST_DATA_PTR glb);		// �f�t�H���g�̃O���[�o���X�e�[�g�̐ݒ�

static void	Map3Dwrite(FIELDSYS_WORK * repw);



static void vram_bank_set(void);
static void debug_vram_bank_set(void);
static void char_pltt_manager_init(void);		// �L�����N�^�E�p���b�g�}�l�[�W���[�̏�����
static void char_pltt_manager_delete(void);		// �L�����N�^�E�p���b�g�}�l�[�W���[�̔j��


static void FieldMapLoadSeq( FIELDSYS_WORK * repw );
static void FieldMapLoadSeqDivMap( FIELDSYS_WORK * repw );
static void FieldMapLoadSeqFeMoveObj( FIELDSYS_WORK * repw );
static void FieldMapLoadSeqRest( FIELDSYS_WORK * repw );

static PROC_RESULT FieldMapProc_Init(PROC * proc, int * seq);
static PROC_RESULT FieldMapProc_Main(PROC * proc, int * seq);
static PROC_RESULT FieldMapProc_End(PROC * proc, int * seq);

static BOOL FieldMap_ZoneChange(FIELDSYS_WORK * fsys);
static void FieldMap_Update(FIELDSYS_WORK * fsys, u8 flag);
static BOOL WatchPlayerPosition(FIELDSYS_WORK * fsys);

static void vBlankFunc(void * work);
static void UpdateFootMark(FIELDSYS_WORK * fsys);



//#define	OSP_HEAP_SIZE

#ifdef PM_DEBUG
void DebugDispTexBank(const u8 inNo);
#endif

//------------------------------------------------------------------
//	���샂�f�����X�g����֘A
//------------------------------------------------------------------
static MMDL_WORK * MMDL_Create(int heapID, int area_id);
static const int * MMDL_GetList(const MMDL_WORK * mmdl);
static const int MMDL_GetListSize(const MMDL_WORK * mmdl);
static void MMDL_Delete(MMDL_WORK * mmdl);

FS_EXTERN_OVERLAY(fieldmap_sub);

//============================================================================================
//	�O���[�o���ϐ�
//============================================================================================


//============================================================================================
//
//
//				�֐�
//
//
//============================================================================================

//----------------------------------------------------------------------------
/**
 *	@brief	�t�B�[���h�I�u�W�F�p�r���{�[�h�A�N�^�[V�u�����N����
 */
//-----------------------------------------------------------------------------
static inline void fldobj_BlactVblank( FIELDSYS_WORK * fsys )
{
	FIELD_OBJ_BLACT_CONT *conot = FieldOBJSys_BlActContGet( fsys->fldobjsys );
	BLACT_SET_PTR blactset = FieldOBJ_BlActCont_SetPtrGet( conot );
	BLACT_VBlankFunc( blactset );
}

//------------------------------------------------------------------
/**
 * @brief	�t�B�[���h�pVBLANK�֐�
 * @param	work
 */
//------------------------------------------------------------------
static void vBlankFunc(void * work)
{
	FIELDSYS_WORK * fsys = work;

	// BG��������
	GF_BGL_VBlankFunc( fsys->bgl );

	// Vram�]���}�l�[�W���[���s
	DoVramTransferManager();

	// �����_�����LOAM�}�l�[�W��Vram�]��
	REND_OAMTrans();	

	// �j���|���S���̊��S�`��j��
	// ��ʒm
	fldobj_BlactVblank( fsys );
}

//============================================================================================
//
//
//		�v���Z�X�֐�
//
//
//============================================================================================
//------------------------------------------------------------------
/**
 * @brief	�v���Z�X�֐��F�������F�t�B�[���h�}�b�v
 */
//------------------------------------------------------------------
static PROC_RESULT FieldMapProc_Init(PROC * proc, int * seq)
{
	u16 bgm_no;
	FIELDSYS_WORK * fsys;
	PROC_RESULT pr = PROC_RES_CONTINUE;
	
	fsys = PROC_GetParentWork(proc);

	switch (*seq) {
	case 0:
		sys_VBlankFuncChange(NULL, NULL);
		sys_HBlankIntrStop();	//HBlank���荞�ݒ�~
		G2_BlendNone();//������ʖ�����
		G2S_BlendNone();//������ʖ�����

// WIFI�@�ΐ�AUTOӰ�ރf�o�b�N
#ifdef _WIFI_DEBUG_TUUSHIN
		WIFI_DEBUG_BATTLE_Work.DEBUG_WIFI_SEQ = 1;
		WIFI_DEBUG_BATTLE_Work.DEBUG_WIFI_A_REQ = TRUE;
#endif	//_WIFI_DEBUG_TUUSHIN

		//���C�v�E�B���h�E�}�X�N���Z�b�g
		WIPE_ResetWndMask( WIPE_DISP_MAIN );
		WIPE_ResetWndMask( WIPE_DISP_SUB );

		//��ʐݒ�
		MapChg_Set3DDisplay(fsys);
		
		if (fsys->MapModeData->UseOverlayFlag) {
		//�t�B�[���h�T�u�I�[�o�[���C�̈��ǂݍ���
			Overlay_Load(FS_OVERLAY_ID(fieldmap_sub), OVERLAY_LOAD_NOT_SYNCHRONIZE);
		}
		//�t�B�[���h�q�[�v�쐬
		sys_CreateHeap( HEAPID_BASE_APP, HEAPID_FIELD, fsys->MapModeData->HeapSize );
		GF_ASSERT(fsys->fldmap == NULL);
		fsys->fldmap = sys_AllocMemory(HEAPID_FIELD, sizeof(FIELDMAP_WORK));
		MI_CpuClear8(fsys->fldmap, sizeof(FIELDMAP_WORK));
		fsys->fldmap->fmapfunc_sys = FLDMAPFUNC_Sys_Create(fsys, HEAPID_FIELD, 8);

		vram_bank_set();				// �u�q�`�l�o���N�ݒ�
		initVramTransferManagerHeap( VRAM_TRANFER_TASK_NUM, HEAPID_FIELD );// �u�q�`�l�]���}�l�[�W���[��������
		BLACT_InitSys(FIELDSYS_BLACTSET_NUM, HEAPID_FIELD);	// �r���{�[�h�A�N�^�[�V�X�e��������
		simple_3DBGInit(HEAPID_FIELD);
		char_pltt_manager_init();		// �L�����N�^�E�p���b�g�}�l�[�W���[�̏�����
		join_clact_oam_init();// �t�B�[���h�p�Z���A�N�^�[������

		GF_Disp_DispSelect();

		fsys->bgl = GF_BGL_BglIniAlloc( HEAPID_FIELD );
		bg_set( fsys->bgl );			// �a�f�ݒ� 
		FieldMsgPrintInit( PALTYPE_MAIN_BG, MSG_PRINT_INIT_ON );

		SpScriptSearch(fsys, SP_SCRID_INIT_CHANGE);

		DEBUG_ENTRY_STRESSPRINT_TASK(fsys);
		break;


	case 1:
		FieldMapLoadSeq( fsys );

		//FieldMapLoadSeq�̌�Ɂifsys->MapResource�̃������m�ۂ��ς�ł���j�Ă�
		SetupMapResource(fsys->MapResource);
		//�g���z�u���f��
		fsys->Map3DObjExp = M3DO_AllocMap3DObjList(HEAPID_FIELD);

		//�n���閧��n�O�b�Y�z�u(�n��ɂ���Ƃ��̓X���[���܂�)
		BaseLayout_SetupUGBaseGoodsObj(fsys);	
		FieldMapLoadSeqDivMap( fsys );
		FieldMapLoadSeqFeMoveObj( fsys );
		FieldMapLoadSeqRest( fsys );

		{
			u16 weather = Situation_GetWeatherID(SaveData_GetSituation(fsys->savedata));
			WEATHER_Set(fsys->fldmap->weather_data, weather);
		}

		//�t�B�[���h�������F�T�E���h�f�[�^�Z�b�g(�V�[�����ύX����Ȃ����͉������Ȃ�)
		Snd_FieldMapInitBgmPlay( fsys, fsys->location->zone_id );

		//����X�N���v�g�ɂ��OBJ����
		SpScriptSearch(fsys, SP_SCRID_OBJ_CHANGE);
		// �t�B�[���h��̪��HBLANK���[�N�̍쐬��
		// HBLANK���荞�݂̎��s	tomoya takahashi 
		fsys->fldmap->hblanksys = FLDHBLANK_SYS_Init( HEAPID_FIELD );
		FLDHBLANK_SYS_Start( fsys->fldmap->hblanksys );
		// �Ŵ̪��
		fsys->fldmap->poisoneffect = POISON_EFFE_Init( HEAPID_FIELD, fsys->fldmap->hblanksys );
		break;


	case 2:
		FieldSubScreen_Init(fsys);					//�T�u��ʊJ�n�������N�G�X�g
		break;


	case 3:
		if (FieldSubScreen_WaitInit(fsys)) {		//�T�u��ʊJ�n�����҂�
			fsys->main_mode_flag = TRUE;
			pr = PROC_RES_FINISH;
		}
		break;
	}

	(*seq)++;
	return pr;
}

//------------------------------------------------------------------
/**
 * @brief	�v���Z�X�֐��F���C���F�t�B�[���h�}�b�v
 */
//------------------------------------------------------------------
static PROC_RESULT FieldMapProc_Main(PROC * proc, int * seq)
{
	FIELDSYS_WORK * fsys;
	fsys = PROC_GetParentWork(proc);

	//���̕����͎��@�̓����ԂłȂ��J�����ړ��ȂǂƓ��������W�����Ő���\�ɂ������B
	//�i���̓]�[���ؑւ����@����Ɉˑ��������Ă��邽�߁j
	//if ( Player_MoveStateGet(fsys->player) == OBJ_MOVE_STATE_START ) {
	//
	//�c�Ƃ������ƂŎ��@���W�`�F�b�N�Ɉڍs���Ă݂��B2005.12.22	tamada
	if ( WatchPlayerPosition(fsys)) {
		SeedSys_CheckInScreen(fsys);
		UpdateFootMark(fsys);
		Field_SendPoketchInfo(fsys, POKETCH_SEND_MOVE_PLAYER, TRUE);
		if (FieldMap_ZoneChange(fsys)) {
			//SwayGrass_InitSwayGrass(fsys->SwayGrass);	//�h�ꑐ�N���A
		}
	}

	FieldMap_Update(fsys, SET_FIELD_3D_ANIME | SET_FIELD_ANIME | SET_DIVMAP_LOAD | SET_MAP3D_WRITE );

	if (fsys->main_mode_flag) {
		return PROC_RES_CONTINUE;
	} else {
		return PROC_RES_FINISH;
	}
}


//------------------------------------------------------------------
/**
 * @brief	�v���Z�X�֐��F�I���F�t�B�[���h�}�b�v
 */
//------------------------------------------------------------------
static PROC_RESULT FieldMapProc_End(PROC * proc, int * seq)
{
	FIELDSYS_WORK * fsys;

	fsys = PROC_GetParentWork(proc);
	DivMapLoadMain(fsys, fsys->map_cont_dat);				//�}�b�v���[�h���C���֐�
	switch(*seq){
	case 0:
		//�M�~�b�N�I��
		FLDGMK_EndFieldGimmick(fsys);
		//�o�C���h�Ώۂ��͂���
		DivMapPurgeTarget(fsys->map_cont_dat);
		//���@���ݍ��W�̑ޔ�
		fsys->location->grid_x = Player_NowGPosXGet( fsys->player );
		fsys->location->grid_z = Player_NowGPosZGet( fsys->player );
		fsys->location->dir = Player_DirGet( fsys->player );
		//�g�������f�[�^�̈���
		EXH_FreeExHeightList(fsys->ExHeightList);
		
		{
			GF_ASSERT(fsys->field_3d_anime!=0);
			DivMapLoad_FreeMap(fsys->map_cont_dat);
		}
		
		RereaseFld3DAnimeAll(fsys->field_3d_anime);
		FreeFld3DAnimeManager(fsys->field_3d_anime);
		F3DASub_FreeAnimeContManager(&fsys->AnimeContMng);

		FieldAnimeAllRelease(fsys->fldmap->field_trans_anime);
		ReleaseFieldAnime(fsys->fldmap->field_trans_anime);
		fsys->fldmap->field_trans_anime = NULL;

		FieldOBJ_DrawProcPushAll( fsys->fldobjsys );			//�`�揈���ޔ�
		FieldOBJSys_DrawDelete( fsys->fldobjsys );				//�`�揈���폜
		FieldOBJSys_MoveStopAll( fsys->fldobjsys );
		FE_Delete( fsys->fes );	//�t�B�[���h�G�t�F�N�g�폜
		
		MMDL_Delete(fsys->mmdl);					// ���샂�f�����X�g���
		fsys->mmdl = NULL;

		M3DO_FreeMap3DObjList(fsys->Map3DObjExp);

		(*seq)++;
		break;
	case 1:
		if(WaitMapFree(fsys->map_cont_dat) == TRUE){
			ReleaseMapResource(&fsys->MapResource);		// �}�b�v���\�[�X���
			FreeDivMapCont(fsys->map_cont_dat);

			HTE_FreeHoneyTreeDat(&fsys->HoneyTreePtr);//���؃f�[�^���

			FieldCameraEnd(fsys);					//�t�B�[���h�J�����I��
			
			DellLightCont(&fsys->light_cont_data);	// ���C�g�j��
			BoardWorkDelete( fsys->board );			// �Ŕ��[�N���
			FreePlaceNameCont(fsys->fldmap->place_name_cont);	//�n���\���\���̉��
			WEATHER_Delete(fsys->fldmap->weather_data);	// �V�C�j��
			POISON_EFFE_Delete( fsys->fldmap->poisoneffect );// �Ŵ̪��
			FLDHBLANK_SYS_Delete( fsys->fldmap->hblanksys );// H�u�����N
			SeedSys_Finish(fsys->fldmap->seedsys);
			FogSys_Delete(&fsys->fog_data);			// �t�H�O�f�[�^
			GLST_Delete(&fsys->glst_data);			// �O���[�o���X�e�[�g�f�[�^ 
			
			clact_delete();							// �Z���A�N�^�[�f�[�^
			
//			FieldMessageWinDel(fsys->bgl);		// ���b�Z�[�W�E�B���h�E�J��
			bg_exit(fsys->bgl);					// BGL�J��

			FieldSubScreen_Quit(fsys);			//�T�u��ʏI���������N�G�X�g
			(*seq) ++;
		}
		break;

	case 2:
		if (FieldSubScreen_WaitQuit(fsys)) {	//�T�u��ʏI�������҂�
			char_pltt_manager_delete();	// �L�����N�^�E�p���b�g�}�l�[�W���[�̔j��
			BLACT_DestSys();		// �r���{�[�h�A�N�^�[�V�X�e����j��
			DellVramTransferManager();
			simple_3DBGExit();
			FLDMAPFUNC_Sys_Delete(fsys->fldmap->fmapfunc_sys);
			sys_VBlankFuncChange(NULL, NULL);
			sys_FreeMemoryEz( fsys->bgl );
			sys_FreeMemoryEz( fsys->fldmap );
			fsys->fldmap = NULL;

// WIFI�@�ΐ�AUTOӰ�ރf�o�b�N
#ifdef _WIFI_DEBUG_TUUSHIN
		WIFI_DEBUG_BATTLE_Work.DEBUG_WIFI_SEQ = 0;
#endif	//_WIFI_DEBUG_TUUSHIN

			//�t�B�[���h�q�[�v���
			sys_DeleteHeap( HEAPID_FIELD );

			if (fsys->MapModeData->UseOverlayFlag) {
			//�t�B�[���h�T�u�I�[�o�[���C�̈���A�����[�h
				Overlay_UnloadID(FS_OVERLAY_ID(fieldmap_sub));
			}

			return PROC_RES_FINISH;
		}
		break;

	}
	return PROC_RES_CONTINUE;
}


//------------------------------------------------------------------
/**
 * @brief	�v���Z�X��`�f�[�^�F�t�B�[���h
 */
//------------------------------------------------------------------
const PROC_DATA FieldProcData = {
	FieldMapProc_Init,
	FieldMapProc_Main,
	FieldMapProc_End,
	NO_OVERLAY_ID,
};



//============================================================================================
//============================================================================================
//------------------------------------------------------------------
/**
 * @brief	���@���W�X�V�̊Ď�
 * @param	fsys	�t�B�[���h���䃏�[�N�ւ̃|�C���^
 */
//------------------------------------------------------------------
static BOOL WatchPlayerPosition(FIELDSYS_WORK * fsys)
{
	int x,z;
	x = Player_NowGPosXGet( fsys->player );
	z = Player_NowGPosZGet( fsys->player );
	if (x != fsys->location->grid_x || z != fsys->location->grid_z) {
		fsys->location->grid_x = x;
		fsys->location->grid_z = z;
		return TRUE;
	} else {
		return FALSE;
	}
}

//------------------------------------------------------------------
/**
 * @brief	�t�B�[���h�����ł̃]�[���ؑ�
 * @param	fsys	�t�B�[���h���䃏�[�N�ւ̃|�C���^
 * @return	BOOL	TRUE�̂Ƃ��A�]�[�����؂�ւ����
 */
//------------------------------------------------------------------
static BOOL FieldMap_ZoneChange(FIELDSYS_WORK * fsys)
{
	u32 new_zone_id;
	u32 old_zone_id;
	int x,z;
	SITUATION * sit;

	x = Player_NowGPosXGet( fsys->player ) / BLOCK_GRID_W;
	z = Player_NowGPosZGet( fsys->player ) / BLOCK_GRID_H;
	new_zone_id = World_GetZoneIDFromMatrixXZ(fsys->World, x, z);
	old_zone_id = fsys->location->zone_id;
	//���O�̃]�[���Ǝ��̃]�[���������ꍇ�͉������Ȃ�
	if (new_zone_id == old_zone_id) {
		return FALSE;
	}
	
	//++++++++++++++	�]�[���X�V����			++++++++++++
	sit = SaveData_GetSituation(fsys->savedata);
	{
		//���P�[�V�����X�V�i�n�����̕ψڂ̂��߁A�]�[���h�c�݂̂̍X�V�ƂȂ�B�j
		fsys->location->zone_id = new_zone_id;
		//�]�[���ʃf�[�^�̓ǂݍ���
		EventData_LoadZoneData(fsys, new_zone_id);
		
		//�}�b�v�J�ڎ��̃f�[�^�X�V����
		MapChg_UpdateGameData(fsys, TRUE);
	}
	
	//++++++++++++++	���]�[�����샂�f���폜����	++++++++++++
	{
		int max = EventData_GetNpcCount( fsys );
		const FIELD_OBJ_H *head = EventData_GetNpcData( fsys );
		FieldOBJSys_ZoneUpdateDelete( fsys->fldobjsys, old_zone_id, new_zone_id, max, head );
	}

	//++++++++++++++	�V�]�[���f�[�^�ǉ�����	++++++++++++
	{
		SwayGrass_InitSwayGrass(fsys->SwayGrass);	//�h�ꑐ�N���A
			
		//�t�F�[�h�A�E�g �� �ǉ��g�`�ǂݍ��� �� BGM�Đ�
		Snd_FadeOutNextPlayCall( fsys, Snd_FieldBgmNoGet(fsys,fsys->location->zone_id), 
									BGM_FADE_FIELD_MODE );

		;//OBJ�o�^
		EventData_SetFieldOBJ(fsys);

		//�V�󃊃N�G�X�g
		WEATHER_ChengeReq(fsys->fldmap->weather_data, Situation_GetWeatherID(sit));
	}

	//�n���\�����N�G�X�g
	{
		int place_id_old,place_id_new;
		place_id_old = ZoneData_GetPlaceNameID(old_zone_id);
		place_id_new = ZoneData_GetPlaceNameID(new_zone_id);
		if (place_id_old != place_id_new){
			PlaceNameRequest(fsys->fldmap->place_name_cont, place_id_new);//�n���\��
		}
	}
	
	return TRUE;
}

//------------------------------------------------------------------
/**
 * @brief	�t�B�[���h�}�b�v�X�V����
 * @param	fsys	�t�B�[���h���䃏�[�N�ւ̃|�C���^
 */
//------------------------------------------------------------------
static void FieldMap_Update(FIELDSYS_WORK * fsys, u8 flag)
{

	if (FieldEvent_Check(fsys) == FALSE) {
		EVTIME_Update(fsys);
	}

	MainLightCont(fsys->light_cont_data);		// ���C�g���C��

	//�`�����l���t�F�[�h�V�X�e��(���Ɩ�ŋȂ̃`�����l������)
	//Snd_TrackFadeCall( fsys,Snd_FieldBgmNoGet(fsys,fsys->location->zone_id) );


	BoardMain( fsys );		// �Ŕ���

	DEBUG_INIT_TICK();
	DEBUG_STORE_TICK(0);
	if( SET_FUNC_CHECK( flag, SET_FIELD_ANIME ) != 0 ){
		FieldAnimeMain(fsys->fldmap->field_trans_anime);	// �t�B�[���h�]���A�j��
	}
	if( SET_FUNC_CHECK( flag, SET_FIELD_3D_ANIME ) != 0 ){	//�t�B�[���h3�c�A�j��
		F3DA_Main(fsys->field_3d_anime);
	}
	DEBUG_STORE_TICK(1);
	if( SET_FUNC_CHECK( flag, SET_DIVMAP_LOAD ) != 0 ){
		DivMapLoadMain(fsys, fsys->map_cont_dat);				//�}�b�v���[�h���C���֐�
	}
	DEBUG_STORE_TICK(2);
	if( SET_FUNC_CHECK( flag, SET_MAP3D_WRITE ) != 0 ){
		Map3Dwrite( fsys );						// �`��G���W��
	}
	DEBUG_STORE_TICK(3);

	if (sys.trg & PAD_BUTTON_X){
		DEBUG_CLEAR_TICK();
	}

}


//------------------------------------------------------------------
/**
 * @brief	�^�E���}�b�v���Տ��̃A�b�v�f�[�g
 * @param	fsys	�t�B�[���h���䃏�[�N�ւ̃|�C���^
 * 
 * townmap_footmark.c�Ɉړ����邩������Ȃ��B
 */
//------------------------------------------------------------------
static void UpdateFootMark(FIELDSYS_WORK * fsys)
{
	TOWN_MAP_FOOTMARK * footmark;
	int x, z, dir;

	if (ZoneData_IsSinouField(fsys->location->zone_id) == FALSE) {
		//�t�B�[���h�ȊO�ł͑��Ղ̍X�V�͂Ȃ��I
		return;
	}
	footmark = Situation_GetTMFootMark(SaveData_GetSituation(fsys->savedata));
	x = Player_NowGPosXGet(fsys->player) / BLOCK_GRID_W;
	z = Player_NowGPosZGet(fsys->player) / BLOCK_GRID_H;
	dir = Player_DirGet(fsys->player);
	TMFootMark_Update(footmark, x, z, dir);
}


//============================================================================================
//============================================================================================
//===========================================================================
/**
 * 
 * �u�q�`�l�o���N�ݒ�
 *
 */
//===========================================================================
static void vram_bank_set(void)
{
	GF_BGL_DISPVRAM vramSetTable = {
		GX_VRAM_BG_128_C,				// ���C��2D�G���W����BG
		GX_VRAM_BGEXTPLTT_NONE,			// ���C��2D�G���W����BG�g���p���b�g
		GX_VRAM_SUB_BG_32_H,			// �T�u2D�G���W����BG
		GX_VRAM_SUB_BGEXTPLTT_NONE,		// �T�u2D�G���W����BG�g���p���b�g
		GX_VRAM_OBJ_16_F,				// ���C��2D�G���W����OBJ
		GX_VRAM_OBJEXTPLTT_NONE,		// ���C��2D�G���W����OBJ�g���p���b�g
		GX_VRAM_SUB_OBJ_16_I,			// �T�u2D�G���W����OBJ
		GX_VRAM_SUB_OBJEXTPLTT_NONE,	// �T�u2D�G���W����OBJ�g���p���b�g
		GX_VRAM_TEX_01_AB,				// �e�N�X�`���C���[�W�X���b�g
		GX_VRAM_TEXPLTT_0123_E			// �e�N�X�`���p���b�g�X���b�g
	};
	GF_Disp_SetBank( &vramSetTable );
}

static void debug_vram_bank_set(void)
{
	GF_BGL_DISPVRAM vramSetTable = {
		GX_VRAM_BG_128_C,				// ���C��2D�G���W����BG
		GX_VRAM_BGEXTPLTT_NONE,			// ���C��2D�G���W����BG�g���p���b�g
		GX_VRAM_SUB_BG_32_H,			// �T�u2D�G���W����BG
		GX_VRAM_SUB_BGEXTPLTT_NONE,		// �T�u2D�G���W����BG�g���p���b�g
		GX_VRAM_OBJ_16_F,				// ���C��2D�G���W����OBJ
		GX_VRAM_OBJEXTPLTT_NONE,		// ���C��2D�G���W����OBJ�g���p���b�g
		GX_VRAM_SUB_OBJ_16_I,			// �T�u2D�G���W����OBJ
		GX_VRAM_SUB_OBJEXTPLTT_NONE,	// �T�u2D�G���W����OBJ�g���p���b�g
		GX_VRAM_TEX_NONE,				// �e�N�X�`���C���[�W�X���b�g
		GX_VRAM_TEXPLTT_0123_E			// �e�N�X�`���p���b�g�X���b�g
	};
	GF_Disp_SetBank( &vramSetTable );
}

//===========================================================================
/**
 * 
 * �a�f�ݒ� 
 *
 */
//===========================================================================
// �O�����J�p�֐�
void Fieldmap_BgSet( GF_BGL_INI * ini )
{
	bg_set( ini );
}
void Fieldmap_BgExit( GF_BGL_INI * ini )
{
	bg_exit( ini );
}

// �����֐�
static void bg_set( GF_BGL_INI * ini )
{
	{
		GF_BGL_SYS_HEADER BGsys_data = {
			GX_DISPMODE_GRAPHICS,GX_BGMODE_0,GX_BGMODE_0, GX_BG0_AS_3D
		};
		GF_BGL_InitBG(&BGsys_data);
	}

	{	// MAIN DISP�i�G�t�F�N�g�P�j
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0x0000, GX_BG_CHARBASE_0x10000, GX_BG_EXTPLTT_01,
			3, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( ini, FLD_MBGFRM_EFFECT1, &TextBgCntDat, GF_BGL_MODE_TEXT );
		GF_BGL_ClearCharSet( FLD_MBGFRM_EFFECT1, 32, 0, HEAPID_FIELD );
		GF_BGL_ScrClear( ini, FLD_MBGFRM_EFFECT1 );
	}

	{	// MAIN DISP�i�G�t�F�N�g�Q�j
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0x0800, GX_BG_CHARBASE_0x14000, GX_BG_EXTPLTT_23,
			3, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( ini, FLD_MBGFRM_EFFECT2, &TextBgCntDat, GF_BGL_MODE_TEXT );
		GF_BGL_ClearCharSet( FLD_MBGFRM_EFFECT2, 32, 0, HEAPID_FIELD );
		GF_BGL_ScrClear( ini, FLD_MBGFRM_EFFECT2 );
	}
	{	// MAIN DISP�i���b�Z�[�W�j
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0x1000, GX_BG_CHARBASE_0x08000, GX_BG_EXTPLTT_23,
			0, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( ini, FLD_MBGFRM_FONT, &TextBgCntDat, GF_BGL_MODE_TEXT );
		GF_BGL_ClearCharSet( FLD_MBGFRM_FONT, 32, 0, HEAPID_FIELD );
		GF_BGL_ScrClear( ini, FLD_MBGFRM_FONT );
	}

//	OS_Printf(
//		"BGL_Alloc!! 1st appHeap = %ld\n", sys_GetHeapFreeSize(HEAPID_FIELD) );

	{
		u16	pal = BG_CLEAR_COLOR;
		DC_FlushRange( (void*)pal, 2 );
		GX_LoadBGPltt( &pal, 0, 2 );
	}

}


// BGL�J��
static void bg_exit( GF_BGL_INI * ini )
{
	GF_Disp_GX_VisibleControl(
		GX_PLANEMASK_BG0 | GX_PLANEMASK_BG1 | GX_PLANEMASK_BG2 | GX_PLANEMASK_BG3, VISIBLE_OFF );

	GF_BGL_BGControlExit( ini, FLD_MBGFRM_EFFECT1 );
	GF_BGL_BGControlExit( ini, FLD_MBGFRM_EFFECT2 );
	GF_BGL_BGControlExit( ini, FLD_MBGFRM_FONT );
}

// �Z���A�N�^�[�p���LOAM�}�l�[�W���̏�����
static void join_clact_oam_init(void)
{
	// OAM�}�l�[�W���[�̏�����
	NNS_G2dInitOamManagerModule();

	// ���LOAM�}�l�[�W���쐬
	// �����_���pOAM�}�l�[�W���쐬
	// �����ō쐬����OAM�}�l�[�W�����݂�Ȃŋ��L����
	REND_OAMInit( 
			0, 124,		// ���C�����OAM�Ǘ��̈�
			0, 31,		// ���C����ʃA�t�B���Ǘ��̈�
			0, 124,		// �T�u���OAM�Ǘ��̈�
			0, 31,		// �T�u��ʃA�t�B���Ǘ��̈�
			HEAPID_FIELD);
	
}

// �Z���A�N�^�[������
static void clact_delete(void)
{
	// �����_���[���LOAM�}�l�[�W���j��
	REND_OAM_Delete();
}


// �f�t�H���g�̃O���[�o���X�e�[�g�̏�Ԃ�ݒ�
static void field_glb_state_init(GLST_DATA_PTR glb)
{
	GLST_MdlPolyMode(glb, GX_POLYGONMODE_MODULATE, FALSE);
	GLST_MdlCullMode(glb, GX_CULL_BACK, FALSE);
	GLST_MdlAlpha(glb, 31, FALSE);
	GLST_MdlMisc(glb, GX_POLYGON_ATTR_MISC_FOG, TRUE, FALSE);

	GLST_Reflect(glb, GLST_ALL);		// �ݒ�
}

//-------------------------------------
//
//	�L�����N�^�}�l�[�W���[
//	�p���b�g�}�l�[�W���[�̏�����
//
//=====================================
void char_pltt_manager_init(void)
{
	// �L�����N�^�}�l�[�W���[������
	{
		CHAR_MANAGER_MAKE cm = {
			FLD_CHAR_CONT_NUM,
			FLD_CHAR_VRAMTRANS_MAIN_SIZE,
			FLD_CHAR_VRAMTRANS_SUB_SIZE,
			HEAPID_FIELD
		};
		
		InitCharManagerReg(&cm, GX_OBJVRAMMODE_CHAR_1D_32K, GX_OBJVRAMMODE_CHAR_1D_32K );
	}
	// �p���b�g�}�l�[�W���[������
	InitPlttManager(FLD_PLTT_CONT_NUM, HEAPID_FIELD);

	// �ǂݍ��݊J�n�ʒu��������
	CharLoadStartAll();
	PlttLoadStartAll();

	// �ʐM�A�C�R���̈��\�񂷂�
}

//-------------------------------------
//
//	�L�����N�^�}�l�[�W���[
//	�p���b�g�}�l�[�W���[�̔j��
//
//=====================================
void char_pltt_manager_delete(void)
{
	// �L�����N�^�f�[�^�j��
	DeleteCharManager();
	// �p���b�g�f�[�^�j��
	DeletePlttManager();
}

//===========================================================================
/**
 * 
 * �`��
 *
 */
//===========================================================================
static void Map3Dwrite(FIELDSYS_WORK * repw)
{
	MtxFx44 org_pm,pm;

	//�R�c�`��J�n
	GF_G3X_Reset();

	GFC_CameraLookAt();

	//�h�ꑐ�͈͊O�`�F�b�N
	SwayGrass_CheckIO(repw);
	
	DrawAroundBlock(repw->map_cont_dat,repw->glst_data);
		
	M3DO_DrawMap3DObjExp(repw->Map3DObjExp, repw->MapResource);
	//�v���W�F�N�V�����}�g���N�X�̕ϊ�
	{
		const MtxFx44 *m;
		m = NNS_G3dGlbGetProjectionMtx();
/**		
		OS_Printf("%x,%x,%x,%x\n%x,%x,%x,%x\n%x,%x,%x,%x\n%x,%x,%x,%x\n",
				m->_00,m->_01,m->_02,m->_03,
				m->_10,m->_11,m->_12,m->_13,
				m->_20,m->_21,m->_22,m->_23,
				m->_30,m->_31,m->_32,m->_33);
*/				
		org_pm = *m;
		pm = org_pm;
		pm._32 += FX_Mul(pm._22,PRO_MAT_Z_OFS*FX32_ONE);
		NNS_G3dGlbSetProjectionMtx(&pm);
		NNS_G3dGlbFlush();		//�@�W�I���g���R�}���h��]��
	}

	//�t�B�[���h�G�t�F�N�g�`��
	FE_Draw( repw->fes );
	
	// �r���{�[�h�A�N�^�[�V�X�e���`��
	BLACT_DrawSys();
	//�v���W�F�N�V�����}�g���N�X�����ɖ߂�
	{
		NNS_G3dGlbSetProjectionMtx(&org_pm);
		NNS_G3dGlbFlush();		//�@�W�I���g���R�}���h��]��
	}

	///<fieldmap_func�`�揈��
	FLDMAPFUNC_Sys_Draw3D( repw->fldmap->fmapfunc_sys );

	/* �W�I���g���������_�����O�G���W���֘A�������̃X���b�v */
	GF_G3_RequestSwapBuffers(GX_SORTMODE_AUTO, SwapBuffMode);
#ifdef DEBUG_3DDRAW_COUNT	
	D_3D_DC_DrawPolygonCountUp();
#endif
}

//===========================================================================
/**
 *
 * �t�B�[���h�p���C�v�V�X�e�����g�p�����P�x�t�F�[�h
 *
 */
//===========================================================================
void FieldFadeWipeSet(const u8 flg)
{
	if( flg == FLD_DISP_BRIGHT_BLACKIN ){
		WIPE_SYS_Start(
			WIPE_PATTERN_WMS, WIPE_TYPE_FADEIN,
			WIPE_TYPE_FADEIN, WIPE_FADE_BLACK, COMM_BRIGHTNESS_SYNC, 1, HEAPID_FIELD  );
	}else if (flg == FLD_DISP_BRIGHT_BLACKOUT){
		WIPE_SYS_Start(
			WIPE_PATTERN_WMS, WIPE_TYPE_FADEOUT,
			WIPE_TYPE_FADEOUT, WIPE_FADE_BLACK, COMM_BRIGHTNESS_SYNC, 1, HEAPID_FIELD );
	}else{
		GF_ASSERT(0&&"�t�F�[�h�w��~�X");
	}
}

static void FieldMapLoadSeq( FIELDSYS_WORK * repw )
{
	GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG0, VISIBLE_OFF );	// BG0���\��

	// �W�I���g���������_�����O�G���W���֘A�������̃X���b�v
	// �\���f�[�^�����S�ɏ����āA���[�h���̂������h���܂��B
	G3_SwapBuffers( GX_SORTMODE_AUTO, SwapBuffMode );

	//���P�[�V������񂩂�ǂݍ��ރ}�b�v������
	//
	repw->field_3d_anime = F3DA_Field3DAnimeInit();	//�t�B�[���h3�c�A�j���������m��
	repw->AnimeContMng = F3DASub_InitField3DAnimeCont();

//SetUpWorldMatrix( repw->location->zone_id, repw->World ); <<20060116 move
	{
		u16 area_id, mml_id;
		area_id = ZoneData_GetAreaID(repw->location->zone_id);
		repw->MapResource = AllocMapResource(	area_id,
												repw->field_3d_anime	);
		
		mml_id = ZoneData_GetMoveModelID(repw->location->zone_id);
		GF_ASSERT(repw->mmdl == NULL);
		repw->mmdl = MMDL_Create(HEAPID_FIELD, mml_id);
		
	}
}

static void FieldMapLoadSeqDivMap(FIELDSYS_WORK * repw)
{
	// �}�b�v�Ǘ��f�[�^�m��
	repw->map_cont_dat = InitDivMap(repw->World,
									repw->MapResource,
									repw->field_3d_anime,
									repw->DivMapMode);		
	
	//�g�������f�[�^�̈�m��
	repw->ExHeightList = EXH_AllocExHeightList(EX_HEIGHT_NUM, HEAPID_FIELD);

	repw->HoneyTreePtr = HTE_AllocHoneyTreeDat();	//���h��ؗp�f�[�^�m��(�n���ł͎g���܂��񂪁A�m�ۂ����Ⴂ�܂�)
	if (repw->MapMode == MAP_MODE_GROUND){
		//DIV�ɖ��h��p�̃R�[���o�b�N��ݒ�
		DIVM_SetLoadCallBack( repw->map_cont_dat, HTE_SetHoneyTreeAnimeCallBack, repw );
	}

	LoadDivMap( repw->map_cont_dat,
				repw->location->grid_x,
				repw->location->grid_z);
}

static void FieldMapLoadSeqFeMoveObj(FIELDSYS_WORK * repw)
{
	//�t�B�[���h�G�t�F�N�g������
	repw->fes = FE_Init( repw, FE_EFFECT_MAX, HEAPID_FIELD, FE_HEAP_SIZE );
	FE_ParamInit_EOA( repw->fes, FE_EOA_MAX );
	FE_ParamInit_BlAct( repw->fes, HEAPID_FIELD, FE_BLACT_MAX,
		FE_BLACT_MDL_MAX, FE_BLACT_ANM_MAX, FE_BLACT_TEX_MAX,
		FE_BLACT_MDL_HEAP_SIZE, FE_BLACT_ANM_HEAP_SIZE, FE_BLACT_TEX_HEAP_SIZE );
	
	//�n�������j�I���ł���΃t�B�[���hOBJ�ɉe��t���Ȃ�
	if( repw->MapMode == MAP_MODE_UNDER || repw->MapMode == MAP_MODE_UNION ){
		FieldOBJSys_ShadowJoinSet( repw->fldobjsys, FALSE );
	}

	//�n���Ƃ���ȊO�œo�^����G�t�F�N�g�f�[�^��ς���
	if( repw->MapMode == MAP_MODE_UNDER ){
        FE_EffectRegistMore( repw->fes, DATA_FE_UnderProcRegistTbl );
	}
    else{
        FE_EffectRegistMore( repw->fes, DATA_FE_GroundProcRegistTbl );
    }
	
	//�t�B�[���hOBJ�`�揈��������
	FieldOBJSys_DrawInit( repw->fldobjsys,
			FLDOBJ_RESM_MAX_TEX,		//�o�^�ő吔
			MMDL_GetListSize(repw->mmdl) + FLDOBJ_RESM_REG_ALWAYS_NUM,	//�풓�o�^�ő吔�i�V�X�e���p�S�j
			MMDL_GetList(repw->mmdl) );

	Player_DrawInit( repw->player );	//���@�`�揉����
	FieldOBJ_DrawProcPopAll( repw->fldobjsys );			//�������Ă���SOBJ�̕`�揈�����A
    CommPlayerSetForcePos();  // �ʐM���Ă���ꍇFLDOBJ�̌��݈ʒu�ւ̈ړ�
    FieldOBJSys_MoveStopAllClear( repw->fldobjsys );
	DivMapBindTarget(
			Player_VecPosPtrGet(repw->player), repw->map_cont_dat);//�n�`�o�C���h

	repw->fldmap->seedsys = SeedSys_Init(repw, HEAPID_FIELD);
}

static void FieldMapLoadSeqRest(FIELDSYS_WORK * repw)
{
	GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG0, VISIBLE_ON );	// BG0��\��

	GF_Disp_DispOn();		// �f�B�X�v���C�I��

	repw->glst_data = GLST_Init();			// ���C�g�E�}�e���A���E�|���S���ݒ�̏�Ԃ�ۑ�����V�X�e���쐬
	field_glb_state_init(repw->glst_data);	// �f�t�H���g�̏�Ԃ�ۑ�

	repw->fog_data = FogSys_Init();			// �t�H�O�̏�Ԃ�ۑ�����V�X�e�����쐬
	//�J�����̐ݒ�
	{
///		BOOL cycling_flg;
		int camera_id = Situation_GetCameraID(SaveData_GetSituation(repw->savedata));
///		cycling_flg = Player_MoveBitCheck_CyclingRoad( repw->player );
		FieldCameraInit( Player_VecPosPtrGet(repw->player), repw, camera_id, TRUE );
	}
	
	repw->light_cont_data = InitLightCont(repw->glst_data,
											MAPRES_GetLightIndex(repw->MapResource));
	repw->fldmap->weather_data = WEATHER_Init(repw);	// �V�C�V�X�e��������
	repw->fldmap->place_name_cont = AllocPlaceNameCont(repw->bgl);//�n���\���\���̊m��
	repw->board = BoardWorkAlloc( HEAPID_FIELD );		// �Ŕ��[�N�m��
	
	// �t�B�[���h�]���A�j������������
	repw->fldmap->field_trans_anime = InitFieldAnime();
	FieldAnimeSets(repw->fldmap->field_trans_anime, GetMapResourceTexturePTR(repw->MapResource));

	//�t�B�[���h�M�~�b�N�Z�b�g�A�b�v
	FLDGMK_SetUpFieldGimmick(repw);

	//�����`�F�b�N�^�X�N�ǉ�
	QuickSand_CheckTask(repw);
	
	//V�u�����N�֐��Z�b�g
	sys_VBlankFuncChange(vBlankFunc, repw);
}





//============================================================================================
//
//
//				�G���A�ʓ��샂�f�����X�g�֘A
//
//
//============================================================================================
//------------------------------------------------------------------
/**
 * @brief	���샂�f�����X�g�̏��
 */
//------------------------------------------------------------------
#define	MMDL_MAX	(FLDOBJ_RESM_REG_MAX_TEX)

//------------------------------------------------------------------
/**
 * @brief	���샂�f�����X�g���䃏�[�N��`
 */
//------------------------------------------------------------------
struct MMDL_WORK{
	u16 count;				///<���샂�f�����X�g�̒�`��
	int id[MMDL_MAX];		///<���샂�f�����X�g
};
//------------------------------------------------------------------
/**
 * @brief	���샂�f�����X�g�F����������
 * @param	fsys	�t�B�[���h���䃏�[�N�ւ̃|�C���^
 * @param	area_id	�Z�b�g����G���A�̎w��
 */
//------------------------------------------------------------------
static MMDL_WORK * MMDL_Create(int heapID, int area_id)
{
	int i;
	u16 * arc;
	MMDL_WORK * mmdl;

	mmdl = sys_AllocMemory(heapID, sizeof(MMDL_WORK));
	arc = ArchiveDataLoadMallocLo(ARC_MMODEL_LIST, area_id, heapID);
	//arc = ArchiveDataLoadMallocLo(ARC_MMDL, area_id, heapID);
	for (i = 0; i < MMDL_MAX; i++) {
		mmdl->id[i] = OBJCODEMAX;
	}
	for (i = 0; i < MMDL_MAX; i++) {
		mmdl->id[i] = arc[i];
		if (arc[i] == OBJCODEMAX) {
			break;
		}
	}
	mmdl->count = i;
	sys_FreeMemoryEz(arc);
	return mmdl;
}

//------------------------------------------------------------------
/**
 * @brief	���샂�f�����X�g�F���X�g���擾
 * @param	fsys	�t�B�[���h���䃏�[�N�ւ̃|�C���^
 * @return	u16		���샂�f�����X�g�ւ̃|�C���^
 */
//------------------------------------------------------------------
static const int * MMDL_GetList(const MMDL_WORK * mmdl)
{
	return mmdl->id;
}
//------------------------------------------------------------------
/**
 * @brief	���샂�f�����X�g�F���X�g�̒�`�����擾
 * @param	fsys	�t�B�[���h���䃏�[�N�ւ̃|�C���^
 * @return	u16		���샂�f�����X�g��̒�`��
 */
//------------------------------------------------------------------
static const int MMDL_GetListSize(const MMDL_WORK * mmdl)
{
	return mmdl->count;
}

//------------------------------------------------------------------
/**
 * @brief	���샂�f�����X�g�F�I������
 * @param	fsys	�t�B�[���h���䃏�[�N�ւ̃|�C���^
 */
//------------------------------------------------------------------
static void MMDL_Delete(MMDL_WORK * mmdl)
{
	sys_FreeMemoryEz(mmdl);
}

#ifdef PM_DEBUG
void DebugDispTexBank(const u8 inNo)
{
	GXVRamTex tex_bank;
	tex_bank = GX_GetBankForTex();
	if (tex_bank==0){
		OS_Printf("%d:disp_tex_bank=%d\n",inNo,tex_bank);
	}
	GF_ASSERT(tex_bank!=0&&"�e�N�X�`���o���N�j�󔭐�");
/*	
	if (tex_bank==0){
		OS_Printf("�e�N�X�`���o���N�j�󔭐�");
	}
*/	
}
#endif

