//============================================================================================
/**
 * @file	field_3d_anime_ev.c
 * @brief	�C�x���g�p3D�A�j���֘A�t�@�C��
 * @author	Nozomu Saito
 * @date	2006.01.26
 */
//============================================================================================
#include "common.h"
#include "system/wipe.h"
#include "field_3d_anime.h"
#include "fieldsys.h"
#include "field_event.h"

#include "map_tool.h"
#include "system/snd_tool.h"	//for SE

#include "field_3d_anime_ev.h"
#include "field_3d_anime_def.h"

#include "mapresource.h"		//for texture

#include "fieldmap.h"		//for FieldFadeWipeSet

#include "map_jump.h"

#include "debug_saito.h"

#define DOOR_ANIME_ENTRY_ID	(1)
#define ESCA_ANIME_ENTRY_ID	(2)

#define ANM_CAM_ZOOM	(12)
#define ANM_CAM_ZOOM_OUT	(16)

#define	ZOOM_VAL	(96)

typedef struct FLD_3D_ANIME_WORK_tag{
	int seq;
	TARGET_RECT TargetRect;
	int GridX;
	int GridZ;
	u8 EntryID;
	u8 CameraZoomCount;
	u8 AnimeNum;
	BOOL CameraZoomStartFlg;
	u16 PerspWayWork;
}FLD_3D_ANIME_WORK;

static void AnimeCameraZoomIn(GF_CAMERA_PTR camera_ptr, u8 *ioCount);
static void AnimeCameraZoomOut(GF_CAMERA_PTR camera_ptr,  u8 *ioCount);
static BOOL IsAutoDoor(const int inObjID);
//==============================================================================
/**
 * �C�x���g�p3D�A�j���\���̃������A���P�[�V����
 * 
 * @param	none
 *
 * @retval  FLD_3D_ANIME_WORK_PTR	�C�x���g�A�j���[�V�������[�N�|�C���^
 */
//==============================================================================
FLD_3D_ANIME_WORK_PTR	Fld3DAnm_AllocEvent3DAnimeWork(void)
{
	FLD_3D_ANIME_WORK_PTR anime_3d_work_ptr;
	anime_3d_work_ptr = sys_AllocMemoryLo( HEAPID_FIELD, sizeof(FLD_3D_ANIME_WORK) );
	anime_3d_work_ptr->seq = 0;
	return anime_3d_work_ptr;
}

//==============================================================================
/**
 * �C�x���g�p3D�A�j���\���̉��
 * 
 * @param	outAnime3DWorkPtr	�C�x���g�A�j���[�V�������[�N�|�C���^
 *
 * @retval  none
 */
//==============================================================================
void Fld3DAnm_FreeEvent3DAnimeWork(FLD_3D_ANIME_WORK_PTR outAnime3DWorkPtr)
{
	sys_FreeMemoryEz(outAnime3DWorkPtr);
}

//==============================================================================
/**
 * �C�x���g�p3D�A�j���Ώۍ��W�Z�b�g
 * 
 * @param	inGridX				���[���h�O���b�hX���W
 * @param	inGridZ				���[���h�O���b�hZ���W
 * @param	outAnime3DWorkPtr	�C�x���g�A�j���[�V�������[�N�|�C���^
 *
 * @retval  none
 */
//==============================================================================
void Fld3DAnm_EventSetGrid(	const int inGridX, const int inGridZ,
							FLD_3D_ANIME_WORK_PTR outAnime3DWorkPtr)
{
	outAnime3DWorkPtr->GridX = inGridX;
	outAnime3DWorkPtr->GridZ = inGridZ;
}

//==============================================================================
/**
 * �h�A�A�j���C�x���g(����)
 * 
 * @param	fsys	�t�B�[���h�V�X�e���|�C���^
 * @param	work	�C�x���g�A�j���[�V�������[�N�|�C���^
 *
 * @retval  BOOL	TRUE:�C�x���g�I���@FALSE�F�C�x���g�p��
 */
//==============================================================================
BOOL Fld3DAnm_EventDoorInAnime(FIELDSYS_WORK * fsys, FLD_3D_ANIME_WORK_PTR work)
{
	FIELD_OBJ_PTR fop;

	switch (work->seq) {
	case 0:
		{
			BOOL rc;
			M3DO_PTR obj_ptr;
			TARGET_RECT rect;
			int obj_id;
			int list[] = {	BMID_DOOR01,BMID_T1_DOOR1,BMID_T2_DOOR1,BMID_T2_DOOR2,
							BMID_C1_DOOR1,BMID_P_DOOR, BMID_DOOR_PC01, BMID_DOOR_WI01,
							BMID_GYM_DOOR01,BMID_C3_DOOR1, BMID_C3_DOOR2,BMID_T3_DOOR1,
							BMID_C4_DOOR1,BMID_D3_DOOR1, BMID_C5_DOOR_S, BMID_GYM_DOOR00,
							BMID_CARD_DOOR01, BMID_COUNTER_PC04, BMID_L2_DOOR1, BMID_ELE_DOOR1 };
			
			//�J�����Y�[��������
			work->CameraZoomStartFlg = FALSE;
			work->CameraZoomCount = 0;
		
			MPTL_MakeTargetRect( work->GridX, work->GridZ, -1, -1, 3, 1, &rect );

			//�o�^�R�[�h��ݒ�
			work->EntryID = DOOR_ANIME_ENTRY_ID;
			
			rc = MPTL_CheckPluralMap3DObjInRect(fsys,
												list,
												NELEMS(list),
												&rect,
												&obj_ptr,
												&obj_id);

			if (rc){
				u8 no;
				u8 anime_num;
				NNSG3dResTex *tex;

				anime_num = F3DA_GetAnimeNum(fsys->field_3d_anime, obj_id);
				work->AnimeNum = anime_num;
#if 0
				if (IsAutoDoor(obj_id)){	//�����h�A�̂Ƃ�
					anime_num = 2;			//�Z�b�g����A�j���Q�i�J���A����j
				}else{						//����ȊO
					anime_num = 4;			//�Z�b�g����A�j���S�i�J���A����A�O�o�J���A�O�o����j
				}
#endif				
				tex = GetMapResourceBmTexturePTR(fsys->MapResource);

				F3DASub_SetUpAnimation(	fsys->field_3d_anime,
										fsys->AnimeContMng,
										DOOR_ANIME_ENTRY_ID,
										obj_id,
										M3DO_GetRenderObj(obj_ptr),
										M3DO_GetObjModel(obj_ptr),
										tex,anime_num,
										1,		//���[�v1��
										FALSE);
			}else{
				OS_Printf_saitou("�h�A�Ȃ��ł�\n");
				GF_ASSERT(0&&"No Door");
				return TRUE;	//�h�A�Ȃ�
			}//end if
			(work->seq) ++;
		}
		
		break;
	
	case 1:
		{
			int obj_id;
			int sound;
			int anime_no;
			obj_id = F3DASub_GetObjIDFromEntryID(fsys->AnimeContMng, DOOR_ANIME_ENTRY_ID);
			//�G���x�[�^�[�̏ꍇ�̂݃J�����Y�[�������Ȃ�<<20060704 add
			if (obj_id != BMID_ELE_DOOR1){
				//�J�����o�C���h������
				GFC_PurgeCameraTarget(fsys->camera_ptr);
				//�J�����Y�[���J�n
				work->CameraZoomStartFlg = TRUE;
			}
			
			if ( IsAutoDoor(obj_id) ){
				//SE�Z�b�g
				sound = SE_JIDO_DOOR_OPEN;	//�����h�A�J��
			}else{
				//SE�Z�b�g
				sound = SE_DOOR_OPEN;		//�h�A�J��
			}
			
			if (work->AnimeNum == 2){
				anime_no = ANIME_NO_DOOR_AUTO_OPEN;
			}else if(work->AnimeNum == 4){
				anime_no = ANIME_NO_DOOR_OPEN_IN;
			}else{
				GF_ASSERT(0);
				anime_no = ANIME_NO_DOOR_AUTO_OPEN;
			}
			
			F3DASub_StartAnimeSnd(fsys->AnimeContMng, DOOR_ANIME_ENTRY_ID, anime_no, sound);	//�h�A�J���A�j��
		}
		(work->seq) ++;
		break;
	case 2:
		{
			BOOL wait;
			wait = F3DASub_WaitAnimation(fsys->AnimeContMng, DOOR_ANIME_ENTRY_ID);
			//�J���A�j���I���҂�
			if (wait) {
				(work->seq) ++;
			}
		}
		break;
	case 3:
		fop = Player_FieldOBJGet( fsys->player );
#if 0		
		if( FieldOBJ_AcmdSetCheck(fop) == TRUE ){	//�A�j���Z�b�g�ł��邩?
			FieldOBJ_AcmdSet(fop,AC_WALK_U_32F);	//�o����B�C�ӂ̃A�j���Z�b�g
		}else{
			GF_ASSERT(0&&"�A�j���o�^�ł��Ȃ�����");
		}
#else
		//�h�A�A�j���̏ꍇ�Ɍ���A�j���o�^�`�F�b�N���s��Ȃ��Ă悢�i�h�A�͕ǂɂȂ��Ă��āA�O���b�h�̃Y���������Ȃ����߁j
		FieldOBJ_AcmdSet(fop,AC_WALK_U_8F);	//�A�j���Z�b�g	
#endif
		(work->seq) ++;
		break;
	case 4:
		fop = Player_FieldOBJGet( fsys->player );
		
		if( FieldOBJ_AcmdEndCheck(fop) == TRUE ){	//�A�j���I���`�F�b�N
			FieldOBJ_AcmdEnd(fop); //�A�j���I��

			//���@������
			FieldOBJ_StatusBitSet_Vanish( fop, TRUE );
			{
				int obj_id;
				int sound;
				int anime_no;
				obj_id = F3DASub_GetObjIDFromEntryID(fsys->AnimeContMng, DOOR_ANIME_ENTRY_ID);
				if ( IsAutoDoor(obj_id) ){
					//SE�Z�b�g
					sound = SE_JIDO_DOOR_CLOSE;	//�����h�A����
				}else{
					//SE�Z�b�g
					sound = SE_DOOR_CLOSE;		//�h�A����
				}

				if (work->AnimeNum == 2){
					anime_no = ANIME_NO_DOOR_AUTO_CLOSE;
				}else if(work->AnimeNum == 4){
					anime_no = ANIME_NO_DOOR_CLOSE_IN;
				}else{
					GF_ASSERT(0);
					anime_no = ANIME_NO_DOOR_AUTO_CLOSE;
				}
				F3DASub_StartAnimeSnd(fsys->AnimeContMng, DOOR_ANIME_ENTRY_ID, anime_no, sound);	//�h�A����A�j��
			}
			(work->seq) ++;
		}
		break;
	case 5:
		{
			BOOL wait;
			wait = F3DASub_WaitAnimation(fsys->AnimeContMng, DOOR_ANIME_ENTRY_ID);
			//����A�j���I���҂�
			if (wait) {
				F3DASub_RereaseAnimation(	fsys->field_3d_anime,
											fsys->AnimeContMng,
											DOOR_ANIME_ENTRY_ID	);
				return TRUE;
			}
		}
		break;
	}
	if (work->CameraZoomStartFlg){
		//�J�����Y�[���C��
		AnimeCameraZoomIn(fsys->camera_ptr, &work->CameraZoomCount);
	}
	return FALSE;	
}

//==============================================================================
/**
 * �h�A�A�j���C�x���g(�o��)
 * 
 * @param	fsys	�t�B�[���h�V�X�e���|�C���^
 * @param	work	�C�x���g�A�j���[�V�������[�N�|�C���^
 *
 * @retval  BOOL	TRUE:�C�x���g�I���@FALSE�F�C�x���g�p��
 */
//==============================================================================
BOOL Fld3DAnm_EventDoorOutAnime(FIELDSYS_WORK * fsys, FLD_3D_ANIME_WORK_PTR work)
{
	FIELD_OBJ_PTR fop;

	switch (work->seq) {
	case 0:
		{
			BOOL rc;
			M3DO_PTR obj_ptr;
			TARGET_RECT rect;
			int obj_id;
			int list[] = {BMID_DOOR01,BMID_T1_DOOR1,BMID_T2_DOOR1,BMID_T2_DOOR2,
							BMID_C1_DOOR1,BMID_P_DOOR, BMID_DOOR_PC01, BMID_DOOR_WI01,
							BMID_GYM_DOOR01,BMID_C3_DOOR1, BMID_C3_DOOR2,BMID_T3_DOOR1,
							BMID_C4_DOOR1,BMID_D3_DOOR1, BMID_C5_DOOR_S, BMID_GYM_DOOR00,
							BMID_CARD_DOOR01, BMID_COUNTER_PC04, BMID_L2_DOOR1, BMID_ELE_DOOR1};

			//�J�����Y�[��������
			work->CameraZoomStartFlg = FALSE;
			work->CameraZoomCount = 0;	
			
			MPTL_MakeTargetRect( work->GridX, work->GridZ, -1, 0, 3, 1, &rect );
			//�o�^�R�[�h��ݒ�
			work->EntryID = DOOR_ANIME_ENTRY_ID;
			
			rc = MPTL_CheckPluralMap3DObjInRect(fsys,
												list,
												NELEMS(list),
												&rect,
												&obj_ptr,
												&obj_id);

			if (rc){
				u8 no;
				u8 anime_num;
				NNSG3dResTex *tex;
				anime_num = F3DA_GetAnimeNum(fsys->field_3d_anime, obj_id);
				work->AnimeNum = anime_num;
#if 0				
				if (IsAutoDoor(obj_id)){	//�����h�A�̂Ƃ�
					anime_num = 2;			//�Z�b�g����A�j���Q�i�J���A����j
				}else{						//����ȊO
					anime_num = 4;			//�Z�b�g����A�j���S�i�J���A����A�O�o�J���A�O�o����j
				}
#endif				
				tex = GetMapResourceBmTexturePTR(fsys->MapResource);
				F3DASub_SetUpAnimation(	fsys->field_3d_anime,
										fsys->AnimeContMng,
										DOOR_ANIME_ENTRY_ID,
										obj_id,
										M3DO_GetRenderObj(obj_ptr),
										M3DO_GetObjModel(obj_ptr),
										tex,anime_num,
										1,		//���[�v1��
										FALSE);
			}else{
				OS_Printf_saitou("�h�A�Ȃ��ł�\n");
				GF_ASSERT(0&&"No Door");
				//�t�F�[�h�C���J�n
				FieldFadeWipeSet(FLD_DISP_BRIGHT_BLACKIN);
				(work->seq)  = 6;
				return FALSE;
			}//end if

			//�p�[�X�̕ۑ�
			work->PerspWayWork = GFC_GetCameraPerspWay(fsys->camera_ptr);	
			
			//�G���x�[�^�[�̏ꍇ�̂݃J�����Y�[�������Ȃ�<<20060704 add
			if (obj_id != BMID_ELE_DOOR1){
				//�J�����̃Y�[�����Z�b�g���Ȃ���
				//�p�[�X��������
				GFC_AddCameraPerspWay(-(ZOOM_VAL),fsys->camera_ptr);	
			}
			(work->seq) ++;
		}
		break;
	case 1:
		//���C�v�X�^�[�g	�X�v���b�g�C��
		MJUMP_RequestWipe(	fsys->event, WIPE_PATTERN_WMS, WIPE_TYPE_SPLITIN_VCENTER,
							WIPE_TYPE_FADEIN,0x0000,6,1,HEAPID_WORLD );
		{
			int obj_id;
			int sound;
			int anime_no;
			obj_id = F3DASub_GetObjIDFromEntryID(fsys->AnimeContMng, DOOR_ANIME_ENTRY_ID);

			//�G���x�[�^�[�̏ꍇ�̂݃J�����Y�[�������Ȃ�<<20060704 add
			if (obj_id != BMID_ELE_DOOR1){
				work->CameraZoomStartFlg = TRUE;	//�Y�[���J�n
			}
			
			if ( IsAutoDoor(obj_id) ){
				//SE�Z�b�g
				sound = SE_JIDO_DOOR_OPEN;	//�����h�A�J��
			}else{
				//SE�Z�b�g
				sound = SE_DOOR_OPEN;		//�h�A�J���i�O�o�j
			}

			if (work->AnimeNum == 2){
				anime_no = ANIME_NO_DOOR_AUTO_OPEN;
			}else if(work->AnimeNum == 4){
				anime_no = ANIME_NO_DOOR_OPEN_OUT;
			}else{
				GF_ASSERT(0);
				anime_no = ANIME_NO_DOOR_AUTO_OPEN;
			}
			
			F3DASub_StartAnimeSnd(fsys->AnimeContMng, DOOR_ANIME_ENTRY_ID, anime_no, sound);	//�h�A�J���A�j��
		}
		
		(work->seq) ++;
		break;
	case 2:
		{
			BOOL wait;
			wait = F3DASub_WaitAnimation(fsys->AnimeContMng, DOOR_ANIME_ENTRY_ID);
			//�J���A�j���I���҂�
			if (wait) {
				fop = Player_FieldOBJGet( fsys->player );
				//���@��\��
				FieldOBJ_StatusBitSet_Vanish( fop, FALSE );
				(work->seq) ++;
			}
		}
		break;
	case 3:
		fop = Player_FieldOBJGet( fsys->player );
#if 0			
		if( FieldOBJ_AcmdSetCheck(fop) == TRUE ){	//�A�j���Z�b�g�ł��邩?
			FieldOBJ_AcmdSet(fop,AC_WALK_D_32F);	//�o����B�C�ӂ̃A�j���Z�b�g
		}else{
			GF_ASSERT(0&&"�A�j���o�^�ł��Ȃ�����");
		}
#else
		//�h�A�A�j���̏ꍇ�Ɍ���A�j���o�^�`�F�b�N���s��Ȃ��Ă悢�i�h�A�͕ǂɂȂ��Ă��āA�O���b�h�̃Y���������Ȃ����߁j
		FieldOBJ_AcmdSet(fop,AC_WALK_D_8F);	//�A�j���Z�b�g	
#endif
		(work->seq) ++;
		break;
	case 4:
		fop = Player_FieldOBJGet( fsys->player );
		if( FieldOBJ_AcmdEndCheck(fop) == TRUE ){	//�A�j���I���`�F�b�N
			FieldOBJ_AcmdEnd(fop); //�A�j���I��
			{
				int obj_id;
				int sound;
				int anime_no;
				obj_id = F3DASub_GetObjIDFromEntryID(fsys->AnimeContMng, DOOR_ANIME_ENTRY_ID);
				if ( IsAutoDoor(obj_id) ){
					//SE�Z�b�g
					sound = SE_JIDO_DOOR_CLOSE;	//�����h�A����
				}else{
					//SE�Z�b�g
					sound = SE_DOOR_CLOSE;		//�h�A����(�O�o)
				}

				if (work->AnimeNum == 2){
					anime_no = ANIME_NO_DOOR_AUTO_CLOSE;
				}else if(work->AnimeNum == 4){
					anime_no = ANIME_NO_DOOR_CLOSE_OUT;
				}else{
					GF_ASSERT(0);
					anime_no = ANIME_NO_DOOR_AUTO_CLOSE;
				}
				F3DASub_StartAnimeSnd(fsys->AnimeContMng, DOOR_ANIME_ENTRY_ID, anime_no, sound);	//�h�A����A�j��
			}
			(work->seq) ++;
		}
		break;
	case 5:
		{
			BOOL wait;
			wait = F3DASub_WaitAnimation(fsys->AnimeContMng, DOOR_ANIME_ENTRY_ID);
			//����A�j���I���A�u���b�N�A�E�g�I���A�Y�[���I���҂�
			if (wait&&WIPE_SYS_EndCheck()&&
					(work->PerspWayWork == GFC_GetCameraPerspWay(fsys->camera_ptr))) {
				
				F3DASub_RereaseAnimation(	fsys->field_3d_anime,
											fsys->AnimeContMng,
											DOOR_ANIME_ENTRY_ID	);
				return TRUE;
			}
		}
		break;
	case 6:	//�h�A���Ȃ��Ƃ��p�V�[�P���X
		if (WIPE_SYS_EndCheck()){
			return TRUE;
		}
		break;
	}
	if (work->CameraZoomStartFlg){
		AnimeCameraZoomOut(fsys->camera_ptr, &work->CameraZoomCount);		//�Y�[���A�E�g
	}
	return FALSE;
}

//==============================================================================
/**
 * �h�A�A�j���ƘA������J����(�Y�[���C��)
 * 
 * @param	camera_ptr		�J�����|�C���^
 * @param	ioCoint			�J�����Y�[���J�E���^
 *
 * @retval  none
 */
//==============================================================================
static void AnimeCameraZoomIn(GF_CAMERA_PTR camera_ptr, u8 *ioCount)
{
	u8 sp;
	u16 zoom;
	
	if ( (*ioCount)*ANM_CAM_ZOOM> ZOOM_VAL ){
		return;
	}
	
	zoom = (*ioCount)*ANM_CAM_ZOOM;

	if (zoom>ZOOM_VAL){
		sp = zoom-ZOOM_VAL;
	}else{
		sp = ANM_CAM_ZOOM;
	}

	{
		u16 persp_way;
		persp_way = GFC_GetCameraPerspWay(camera_ptr);
		if ((u16)(persp_way-sp)>0x0000){
			GFC_AddCameraPerspWay(-sp,camera_ptr);
		}
		(*ioCount)++;
	}
}

//==============================================================================
/**
 * �h�A�A�j���ƘA������J����(�Y�[���A�E�g)
 * 
 * @param	camera_ptr		�J�����|�C���^
 * @param	ioCoint			�J�����Y�[���J�E���^
 *
 * @retval  none
 */
//==============================================================================
static void AnimeCameraZoomOut(GF_CAMERA_PTR camera_ptr, u8 *ioCount)
{
	u8 sp;
	u16 zoom;
	if ( (*ioCount)*ANM_CAM_ZOOM_OUT>= ZOOM_VAL ){
		return;
	}
	zoom = (*ioCount)*ANM_CAM_ZOOM_OUT;
	if (zoom>ZOOM_VAL){
		sp = zoom-ZOOM_VAL;
	}else{
		sp = ANM_CAM_ZOOM_OUT;
	}

	{
		u16 persp_way;
		persp_way = GFC_GetCameraPerspWay(camera_ptr);
		if ((u16)(persp_way+sp)>0x0000){
			GFC_AddCameraPerspWay(sp,camera_ptr);
		}
		(*ioCount)++;
	}
}

//==============================================================================
/**
 * �����h�A����
 * 
 * @param	inObjID		OBJID
 *
 * @retval  BOOL		TRUE:�����h�A	FALSE:�����h�A�ł͂Ȃ�
 */
//==============================================================================
static BOOL IsAutoDoor(const int inObjID)
{
	return ( (inObjID == BMID_P_DOOR)||(inObjID == BMID_C5_DOOR_S)||
			 (inObjID == BMID_GYM_DOOR00)||(inObjID == BMID_DOOR_WI01)||
			 (inObjID == BMID_DOOR_PC01)||(inObjID == BMID_CARD_DOOR01)||
			 (inObjID == BMID_ELE_DOOR1)
			 /*||(inObjID == BMID_D3_DOOR1)||(inObjID == BMID_COUNTER_PC04)*/ );
}

//==============================================================================
/**
 * �G�X�J���[�^�[(�㉺���E�֌W�����A�G�X�J���[�^�[�~���)
 * 
 * @param	fsys	�t�B�[���h�V�X�e���|�C���^
 * @param	work	�C�x���g�A�j���[�V�������[�N�|�C���^
 * @param	inDir	���@����
 *
 * @retval  BOOL	TRUE:�C�x���g�I���@FALSE�F�C�x���g�p��
 */
//==============================================================================
BOOL Fld3DAnm_EventEscalatorOutAnime(FIELDSYS_WORK * fsys, FLD_3D_ANIME_WORK_PTR work, const u8 inDir)
{
	FIELD_OBJ_PTR fop;
	switch (work->seq) {
	case 0:
		{
			BOOL rc;
			M3DO_PTR obj_ptr;
			TARGET_RECT rect;
			int obj_id;
			int list[] = {BMID_STAIR_PC_U01, BMID_STAIR_PC_D01, BMID_STAIR_PC_U02, BMID_STAIR_PC_D02};
			
			//���@�����ɂ���Č����͈͂𕪊�
			if (inDir == DIR_LEFT){
				MPTL_MakeTargetRect(work->GridX,work->GridZ,-1, 0, 2, 1, &rect );
			}else{	//(inDir == DIR_RIGHT)
				MPTL_MakeTargetRect(work->GridX,work->GridZ,0, 0, 2, 1, &rect );
			}
			//�o�^�R�[�h��ݒ�
			work->EntryID = ESCA_ANIME_ENTRY_ID;
			
			rc = MPTL_CheckPluralMap3DObjInRect(fsys,
												list,
												NELEMS(list),
												&rect,
												&obj_ptr,
												&obj_id);

			if (rc){
				u8 no;
				NNSG3dResTex *tex;
				tex = GetMapResourceBmTexturePTR(fsys->MapResource);
				F3DASub_SetUpAnimation(	fsys->field_3d_anime,
										fsys->AnimeContMng,
										ESCA_ANIME_ENTRY_ID,
										obj_id,
										M3DO_GetRenderObj(obj_ptr),
										M3DO_GetObjModel(obj_ptr),
										tex, 1, //�Z�b�g����A�j��1��
										1,		//���[�v1��
										TRUE);	//�t�Đ�
			}else{
				GF_ASSERT(0&&"�G�X�J���[�^�[���Ȃ�");
				return TRUE;
			}//end if
			
			fop = Player_FieldOBJGet( fsys->player );
			if( FieldOBJ_AcmdSetCheck(fop) == TRUE ){	//�A�j���Z�b�g�ł��邩?
				FieldOBJ_AcmdSet(fop,AC_ANM_PAUSE_ON);	//�o����B�������|�[�Y
			}else{
				GF_ASSERT(0&&"�A�j���o�^�ł��Ȃ�����");
			}
			(work->seq) ++;
		}
		break;
	case 1:
		//�t�F�[�h�C���J�n
		FieldFadeWipeSet(FLD_DISP_BRIGHT_BLACKIN);
		
		F3DASub_StartAnimeSnd(fsys->AnimeContMng, ESCA_ANIME_ENTRY_ID, ANIME_NO_ESCA, SEQ_SE_DP_ESUKA);	//�G�X�J���[�^�[�A�j��
		fop = Player_FieldOBJGet( fsys->player );
		
		if( FieldOBJ_AcmdSetCheck(fop) == TRUE ){	//�A�j���Z�b�g�ł��邩?
			int code;
			if (inDir == DIR_RIGHT){
				code = AC_WALK_R_16F;
			}else{	//(inDir == DIR_LEFT)
				code = AC_WALK_L_16F;
			}
			FieldOBJ_AcmdSet(fop,code);	//�o����B�C�ӂ̃A�j���Z�b�g
		}else{
			GF_ASSERT(0&&"�A�j���o�^�ł��Ȃ�����");
		}
		(work->seq) ++;
		break;
	case 2:
		fop = Player_FieldOBJGet( fsys->player );
		if( FieldOBJ_AcmdSetCheck(fop) == TRUE ){	//�A�j���Z�b�g�ł��邩?
			FieldOBJ_AcmdSet(fop,AC_ANM_PAUSE_OFF);	//�o����B�|�[�Y����
			(work->seq) ++;
		}
		break;
	case 3:
		fop = Player_FieldOBJGet( fsys->player );
		if( FieldOBJ_AcmdSetCheck(fop) == TRUE ){	//�A�j���Z�b�g�ł��邩?
			int code;
			if (inDir == DIR_RIGHT){
				code = AC_WALK_R_16F;
			}else{	//(inDir == DIR_LEFT)
				code = AC_WALK_L_16F;
			}
			FieldOBJ_AcmdSet(fop,code);	//�o����B�P�����ɕ���
			(work->seq) ++;
		}
		break;
	case 4:
		fop = Player_FieldOBJGet( fsys->player );
		if( FieldOBJ_AcmdEndCheck(fop) == TRUE ){	//�A�j���I���`�F�b�N
			FieldOBJ_AcmdEnd(fop); //�A�j���I��	
			(work->seq) ++;
		}
		break;
	case 5:
		{
			BOOL wait;
			wait = F3DASub_WaitAnimation(fsys->AnimeContMng, ESCA_ANIME_ENTRY_ID);
			//�G�X�J���[�^�[�A�j���I���A�u���b�N�C���I���҂�
			if (wait&&WIPE_SYS_EndCheck()) {
				F3DASub_RereaseAnimation(	fsys->field_3d_anime,
											fsys->AnimeContMng,
											ESCA_ANIME_ENTRY_ID	);
				//�r�d�X�g�b�v
				Snd_SeStopBySeqNo( SEQ_SE_DP_ESUKA, 0 );
				return TRUE;
			}
		}
		break;
	}
	return FALSE;
}

//==============================================================================
/**
 * �G�X�J���[�^�[(�㉺���E�֌W�����A�G�X�J���[�^�[�ɏ��)
 * 
 * @param	fsys	�t�B�[���h�V�X�e���|�C���^
 * @param	work	�C�x���g�A�j���[�V�������[�N�|�C���^
 * @param	inDir	���@����
 *
 * @retval  BOOL	TRUE:�C�x���g�I���@FALSE�F�C�x���g�p��
 */
//==============================================================================
BOOL Fld3DAnm_EventEscalatorInAnime(FIELDSYS_WORK * fsys, FLD_3D_ANIME_WORK_PTR work, const u8 inDir)
{
	FIELD_OBJ_PTR fop;
	switch (work->seq) {
	case 0:
		{
			BOOL rc;
			M3DO_PTR obj_ptr;
			TARGET_RECT rect;
			int obj_id;
			int list[] = {BMID_STAIR_PC_U01, BMID_STAIR_PC_D01, BMID_STAIR_PC_U02, BMID_STAIR_PC_D02};
			

			//���@�����ɂ���Č����͈͂𕪊�
			if (inDir == DIR_LEFT){
				MPTL_MakeTargetRect(work->GridX,work->GridZ,-1, 0, 2, 1, &rect );
			}else{	//(inDir == DIR_RIGHT)
				MPTL_MakeTargetRect(work->GridX,work->GridZ,0, 0, 2, 1, &rect );
			}
			//�o�^�R�[�h��ݒ�
			work->EntryID = ESCA_ANIME_ENTRY_ID;
			
			rc = MPTL_CheckPluralMap3DObjInRect(fsys,
												list,
												NELEMS(list),
												&rect,
												&obj_ptr,
												&obj_id);

			if (rc){
				u8 no;
				NNSG3dResTex *tex;
				tex = GetMapResourceBmTexturePTR(fsys->MapResource);
				F3DASub_SetUpAnimation(	fsys->field_3d_anime,
										fsys->AnimeContMng,
										ESCA_ANIME_ENTRY_ID,
										obj_id,
										M3DO_GetRenderObj(obj_ptr),
										M3DO_GetObjModel(obj_ptr),
										tex, 1,	//�Z�b�g����A�j��1��
										1,		//���[�v1��
										FALSE);
			}else{
				GF_ASSERT(0&&"�G�X�J���[�^�[���Ȃ�");
				return TRUE;
			}//end if
			
			fop = Player_FieldOBJGet( fsys->player );
			if( FieldOBJ_AcmdSetCheck(fop) == TRUE ){	//�A�j���Z�b�g�ł��邩?
				FieldOBJ_AcmdSet(fop,AC_ANM_PAUSE_ON);	//�o����B�������|�[�Y
			}else{
				GF_ASSERT(0&&"�A�j���o�^�ł��Ȃ�����");
			}
			(work->seq) ++;
		}
		break;
	case 1:
		F3DASub_StartAnimeSnd(fsys->AnimeContMng, ESCA_ANIME_ENTRY_ID, ANIME_NO_ESCA, SEQ_SE_DP_ESUKA);	//�G�X�J���[�^�[�A�j��
		fop = Player_FieldOBJGet( fsys->player );
		
		if( FieldOBJ_AcmdSetCheck(fop) == TRUE ){	//�A�j���Z�b�g�ł��邩?
			int code;
			if (inDir == DIR_LEFT){
				code = AC_WALK_L_16F;
			}else{
				code = AC_WALK_R_16F;
			}
			FieldOBJ_AcmdSet(fop,code);	//�o����B�C�ӂ̃A�j���Z�b�g
		}else{
			GF_ASSERT(0&&"�A�j���o�^�ł��Ȃ�����");
		}
		(work->seq) ++;
		break;
	case 2:
		fop = Player_FieldOBJGet( fsys->player );
		if( FieldOBJ_AcmdSetCheck(fop) == TRUE ){	//�A�j���Z�b�g�ł��邩?
			FieldOBJ_AcmdSet(fop,AC_ANM_PAUSE_OFF);	//�o����B�|�[�Y����
			//�t�F�[�h�A�E�g�J�n
			FieldFadeWipeSet(FLD_DISP_BRIGHT_BLACKOUT);
			(work->seq) ++;
		}
		break;
	case 3:
		fop = Player_FieldOBJGet( fsys->player );
		if( FieldOBJ_AcmdEndCheck(fop) == TRUE ){	//�A�j���I���`�F�b�N
			FieldOBJ_AcmdEnd(fop); //�A�j���I��	
			(work->seq) ++;
		}
		break;
	case 4:
		{
			BOOL wait;
			wait = F3DASub_WaitAnimation(fsys->AnimeContMng, ESCA_ANIME_ENTRY_ID);
			//�G�X�J���[�^�[�A�j���I���A�u���b�N�A�E�g�I���҂�
			if (wait&&WIPE_SYS_EndCheck()) {
				F3DASub_RereaseAnimation(	fsys->field_3d_anime,
											fsys->AnimeContMng,
											ESCA_ANIME_ENTRY_ID	);
				//�r�d�X�g�b�v
				Snd_SeStopBySeqNo( SEQ_SE_DP_ESUKA, 0 );
				return TRUE;
			}
		}
		break;
	}
	return FALSE;
}


//==============================================================================
//
//	���X�N���v�g�p�֐��Q
//
//==============================================================================


//==============================================================================
/**
 * �A�j���҂�
 * 
 * @param	event	�C�x���g�|�C���^
 *
 * @retval  BOOL	TRUE:�C�x���g�I���@FALSE�F�C�x���g�p��
 */
//==============================================================================
static BOOL WaitAnime(GMEVENT_CONTROL * event)
{
	BOOL wait;
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	u8 *entry  = FieldEvent_GetSpecialWork(event);
	wait = F3DASub_WaitAnimation(fsys->AnimeContMng, *entry);
	//�J���A�j���I���҂�
	if (wait) {
		sys_FreeMemoryEz(entry);
		return TRUE;
	}
	return FALSE;
}

//==============================================================================
/**
 * �h�A�A�j���[�V�����̃Z�b�g�A�b�v
 * 
 * @param	fsys		�t�B�[���h�V�X�e���|�C���^
 * @param	inGridX		�O���b�hX���W
 * @param	inGridZ		�O���b�hZ���W
 * @param	inEntryID	�o�^ID
 *
 * @retval  none
 */
//==============================================================================
void FLD_SCR_ANM_DOOR_Setup(FIELDSYS_WORK * fsys,
						const int inGridX, const int inGridZ, const u8 inEntryID)
{
	BOOL rc;
	M3DO_PTR obj_ptr;
	TARGET_RECT rect;
	int obj_id;
	int list[] = {	BMID_DOOR01,BMID_T1_DOOR1,BMID_T2_DOOR1,BMID_T2_DOOR2,
					BMID_C1_DOOR1,BMID_P_DOOR, BMID_DOOR_PC01, BMID_DOOR_WI01,
					BMID_GYM_DOOR01,BMID_C3_DOOR1, BMID_C3_DOOR2,BMID_T3_DOOR1,
					BMID_C4_DOOR1,BMID_D3_DOOR1, BMID_C5_DOOR_S, BMID_GYM_DOOR00,
					BMID_CARD_DOOR01, BMID_COUNTER_PC04, BMID_L2_DOOR1, BMID_ELE_DOOR1 };

	MPTL_MakeTargetRect( inGridX, inGridZ, -1, 0, 3, 1, &rect );

	rc = MPTL_CheckPluralMap3DObjInRect(fsys,
										list,
										NELEMS(list),
										&rect,
										&obj_ptr,
										&obj_id);

	if (rc){
		u8 no;
		u8 anime_num;
		NNSG3dResTex *tex;
		anime_num = F3DA_GetAnimeNum(fsys->field_3d_anime, obj_id);
#if 0		
		if (IsAutoDoor(obj_id)){	//�����h�A�̂Ƃ�
			anime_num = 2;			//�Z�b�g����A�j���Q�i�J���A����j
		}else{						//����ȊO
			anime_num = 4;			//�Z�b�g����A�j���S�i�J���A����A�O�o�J���A�O�o����j
		}
#endif		
		tex = GetMapResourceBmTexturePTR(fsys->MapResource);
		F3DASub_SetUpAnimation(	fsys->field_3d_anime,
								fsys->AnimeContMng,
								inEntryID,
								obj_id,
								M3DO_GetRenderObj(obj_ptr),
								M3DO_GetObjModel(obj_ptr),
								tex,anime_num,
								1,		//���[�v1��
								FALSE);
	}else{
		GF_ASSERT(0&&"�h�A����܂���");
	}
}

//==============================================================================
/**
 * �h�A�A�j���[�V����(�I�[�v��)
 * 
 * @param	fsys		�t�B�[���h�V�X�e���|�C���^
 * @param	inEntryID	�o�^ID
 *
 * @retval  none
 */
//==============================================================================
void FLD_SCR_ANM_DOOR_StartOpenDoorAnm(	FIELDSYS_WORK * fsys, const u8 inEntryID	)
{
	int obj_id;
	int sound;
	int anime_no;
	u8 anime_num;
	obj_id = F3DASub_GetObjIDFromEntryID(fsys->AnimeContMng, inEntryID);
	anime_num = F3DA_GetAnimeNum(fsys->field_3d_anime, obj_id);
	if ( IsAutoDoor(obj_id) ){
		//SE�Z�b�g
		sound = SE_JIDO_DOOR_OPEN;	//�����h�A�J��
	}else{
		//SE�Z�b�g
		sound = SE_DOOR_OPEN;		//�h�A�J��
	}

	if (anime_num == 2){
		anime_no = ANIME_NO_DOOR_AUTO_OPEN;
	}else if(anime_num ==4){
		anime_no = ANIME_NO_DOOR_OPEN_IN;
	}else{
		GF_ASSERT(0);
		anime_no = ANIME_NO_DOOR_AUTO_OPEN;
	}
	F3DASub_StartAnimeSnd(fsys->AnimeContMng, inEntryID, anime_no, sound);	//�h�A�J���A�j��
}

//==============================================================================
/**
 * �h�A�A�j���[�V����(�N���[�Y)
 * 
 * @param	fsys		�t�B�[���h�V�X�e���|�C���^
 * @param	inEntryID	�o�^ID
 *
 * @retval  none
 */
//==============================================================================
void FLD_SCR_ANM_DOOR_StartCloseDoorAnm(	FIELDSYS_WORK * fsys, const u8 inEntryID	)
{
	int obj_id;
	int sound;
	int anime_no;
	u8 anime_num;
	obj_id = F3DASub_GetObjIDFromEntryID(fsys->AnimeContMng, inEntryID);
	anime_num = F3DA_GetAnimeNum(fsys->field_3d_anime, obj_id);
	if ( IsAutoDoor(obj_id) ){
		//SE�Z�b�g
		sound = SE_JIDO_DOOR_CLOSE;	//�����h�A����
	}else{
		//SE�Z�b�g
		sound = SE_DOOR_CLOSE;		//�h�A����
	}

	if (anime_num == 2){
		anime_no = ANIME_NO_DOOR_AUTO_CLOSE;
	}else if(anime_num == 4){
		anime_no = ANIME_NO_DOOR_CLOSE_IN;
	}else{
		GF_ASSERT(0);
		anime_no = ANIME_NO_DOOR_AUTO_CLOSE;
	}
	F3DASub_StartAnimeSnd(fsys->AnimeContMng, inEntryID, anime_no, sound);	//�h�A����A�j��
}

//==============================================================================
/**
 * �A�j���[�V�����҂�
 * 
 * @param	fsys		�t�B�[���h�V�X�e���|�C���^
 * @param	inEntryID	�o�^ID
 *
 * @retval  none
 */
//==============================================================================
void FLD_SCR_ANM_DOOR_WaitAnime(FIELDSYS_WORK * fsys, const u8 inEntryID)
{
	u8 *entry = sys_AllocMemoryLo(HEAPID_FIELD, sizeof(u8));
	*entry = inEntryID;
	FieldEvent_Call(fsys->event, WaitAnime, entry);
}

//==============================================================================
/**
 * �h�A�A�j���[�V�������
 * 
 * @param	fsys		�t�B�[���h�V�X�e���|�C���^
 * @param	inEntryID	�o�^ID
 *
 * @retval  none
 */
//==============================================================================
void FLD_SCR_ANM_DOOR_FreeDoor(FIELDSYS_WORK * fsys, const u8 inEntryID)
{
	F3DASub_RereaseAnimation(	fsys->field_3d_anime,
								fsys->AnimeContMng,
								inEntryID	);
}

//==============================================================================
/**
 * �����A�j���[�V�����̃X�^�[�g
 * 
 * @param	inGridX		�O���b�hX���W
 * @param	inGridZ		�O���b�hZ���W
 * @param	inAnmNo		�A�j���i���o�[	0�F�������@1�F������
 * @param	fsys		�t�B�[���h�V�X�e���|�C���^
 *
 * @retval  none
 */
//==============================================================================
void Fld3DAnm_StartQuickSandAnime(	const int inGridX,
									const int inGridZ,
									const int inAnmNo,
									FIELDSYS_WORK * fsys)
{

	BOOL rc;
	M3DO_PTR obj_ptr;
	TARGET_RECT rect;
	int obj_id;
	int list[] = {BMID_CY_SLOPE, BMID_CY_SLOPE_DUN};
		
	//�����͈͍쐬
	MPTL_MakeTargetRect( inGridX, inGridZ, 0, -1, 1, 3, &rect );
	//����OBJ�擾
/**
	rc = MPTL_CheckMap3DObjInRect(	fsys,
									BMID_CY_SLOPE,
									&rect,
									&obj_ptr);
*/									
	rc = MPTL_CheckPluralMap3DObjInRect(fsys,
										list,
										NELEMS(list),
										&rect,
										&obj_ptr,
										&obj_id);
	GF_ASSERT(rc&&"����������Ȃ�");
	
	//�A�j���Z�b�g
	{
		NNSG3dRenderObj *render_obj;
		render_obj = M3DO_GetRenderObj(obj_ptr);
		rc =	F3DA_SetFld3DAnime(	obj_id, inAnmNo, TRUE,
									render_obj,
									fsys->field_3d_anime );
		GF_ASSERT(rc&&"�����Z�b�g���s");
	}
	{
		FLD_3D_ANM_DAT_PTR anime;
		//�A�j���擾
		anime = F3DA_GetFld3DAnmPtr(obj_id, inAnmNo, fsys->field_3d_anime);
		//�A�j���J�n
		F3DA_SetStartFrame(anime);
		F3DA_SetStopFlg(anime, FALSE);
		F3DA_MoveAnime(anime);
	}
}

typedef struct FLD_MAP_JUMP_WORK_tag{
	int seq;
	u8 CameraZoomCount;
	BOOL CameraZoomStartFlg;
	u16 PerspWayWork;
}FLD_MAP_JUMP_WORK;

//�������m��
extern FMJ_WORK_PTR	MapJump_AllocWork(void)
{
	FMJ_WORK_PTR work_ptr;
	work_ptr = sys_AllocMemoryLo(HEAPID_FIELD,sizeof(FLD_MAP_JUMP_WORK));
	work_ptr->seq = 0;
	return work_ptr;
}

//==============================================================================
/**
 * �z���C�g�C��
 * 
 * @param	event	�C�x���g�|�C���^
 *
 * @retval  BOOL	TRUE:�C�x���g�I���@FALSE�F�C�x���g�p��
 */
//==============================================================================
BOOL MapJump_EventFadeInWhite(GMEVENT_CONTROL * event)
{
	FIELD_OBJ_PTR fop;
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	FMJ_WORK_PTR work = FieldEvent_GetSpecialWork(event);
	switch (work->seq) {
	case 0:
		fop = Player_FieldOBJGet( fsys->player );
		//�������̏ꍇ�͎��@��\��
		if (Player_DirGet( fsys->player ) == DIR_DOWN){
			FieldOBJ_StatusBitSet_Vanish( fop, TRUE );
			(work->seq) = 1;
		}else{
			//���@�\��
			FieldOBJ_StatusBitSet_Vanish( fop, FALSE );
			(work->seq) = 3;

		}
		//�J�����Y�[��������
		work->CameraZoomStartFlg = FALSE;
		work->CameraZoomCount = 0;	
			
		//�J�����̃Y�[�����Z�b�g���Ȃ���
		{
			//�p�[�X�̕ۑ�
			work->PerspWayWork = GFC_GetCameraPerspWay(fsys->camera_ptr);
			//�p�[�X��������
			GFC_AddCameraPerspWay(-(ZOOM_VAL),fsys->camera_ptr);	
		}
		
		//���C�v�X�^�[�g	�z���C�g�C��
		WIPE_SYS_Start(	WIPE_PATTERN_WMS, WIPE_TYPE_FADEIN,
						WIPE_TYPE_FADEIN,0x7fff,COMM_BRIGHTNESS_SYNC,1,HEAPID_WORLD );
		work->CameraZoomStartFlg = TRUE;	//�Y�[���A�E�g�J�n
		
		break;
	case 1:
		fop = Player_FieldOBJGet( fsys->player );
		//���@�\��
		FieldOBJ_StatusBitSet_Vanish( fop, FALSE );
		FieldOBJ_AcmdSet(fop,AC_WALK_D_8F);	//�A�j���Z�b�g
		(work->seq) ++;
		break;
	case 2:
		fop = Player_FieldOBJGet( fsys->player );
		if( FieldOBJ_AcmdEndCheck(fop) == TRUE ){	//�A�j���I���`�F�b�N
			FieldOBJ_AcmdEnd(fop); //�A�j���I��
			(work->seq) ++;
		}
		break;
	case 3:
		//���C�v�I���A�Y�[���I���҂�
		if ( WIPE_SYS_EndCheck()&&
				( work->PerspWayWork == GFC_GetCameraPerspWay(fsys->camera_ptr) ) ) {
			sys_FreeMemoryEz(work);
			return TRUE;
		}
		break;
	}

	if (work->CameraZoomStartFlg){
		AnimeCameraZoomOut(fsys->camera_ptr, &work->CameraZoomCount);		//�Y�[���A�E�g
	}

	return FALSE;
}


//==============================================================================
/**
 * �z���C�g�A�E�g
 * 
 * @param	event	�C�x���g�|�C���^
 *
 * @retval  BOOL	TRUE:�C�x���g�I���@FALSE�F�C�x���g�p��
 */
//==============================================================================
BOOL MapJump_EventFadeOutWhite(GMEVENT_CONTROL * event)
{
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	FMJ_WORK_PTR work = FieldEvent_GetSpecialWork(event);
	switch (work->seq) {
	case 0:
		{
			FIELD_OBJ_PTR fop;
			fop = Player_FieldOBJGet( fsys->player );
			//���@��\��
			FieldOBJ_StatusBitSet_Vanish( fop, TRUE );
			//�J�����Y�[��������
			work->CameraZoomStartFlg = FALSE;
			work->CameraZoomCount = 0;	
			//���鉹
			Snd_SePlay( SEQ_SE_DP_KAIDAN2 );
			//���C�v�X�^�[�g	�z���C�g�A�E�g
			WIPE_SYS_Start(	WIPE_PATTERN_WMS, WIPE_TYPE_FADEOUT,
							WIPE_TYPE_FADEOUT,0x7fff,COMM_BRIGHTNESS_SYNC,1,HEAPID_WORLD );
			work->CameraZoomStartFlg = TRUE;	//�Y�[���C���J�n
			(work->seq) ++;
		}
		break;
	case 1:
		//���C�v�I���҂�
		if ( WIPE_SYS_EndCheck() ) {
			sys_FreeMemoryEz(work);
			return TRUE;
		}
		break;
	}

	if (work->CameraZoomStartFlg){
		AnimeCameraZoomIn(fsys->camera_ptr, &work->CameraZoomCount);		//�Y�[���C��
	}

	return FALSE;
}

//==============================================================================
/**
 * �z�[���A�E�g
 * 
 * @param	event	�C�x���g�|�C���^
 *
 * @retval  BOOL	TRUE:�C�x���g�I���@FALSE�F�C�x���g�p��
 */
//==============================================================================
BOOL MapJump_EventFadeOutHole(GMEVENT_CONTROL * event)
{
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	FMJ_WORK_PTR work = FieldEvent_GetSpecialWork(event);
	switch (work->seq) {
	case 0:
		{
			//�J�����Y�[��������
			work->CameraZoomStartFlg = FALSE;
			work->CameraZoomCount = 0;	
			//���鉹
			Snd_SePlay( SEQ_SE_DP_KAIDAN2 );
			//���C�v�X�^�[�g	�z�[���A�E�g
			MJUMP_RequestWipe(	event, WIPE_PATTERN_WMS, WIPE_TYPE_HOLEOUT,
								WIPE_TYPE_FADEOUT,0x0000,6,1,HEAPID_WORLD );
			work->CameraZoomStartFlg = TRUE;	//�Y�[���C���J�n
			(work->seq) ++;
		}
		break;
	case 1:
		//���C�v�I���҂�
		if ( WIPE_SYS_EndCheck() ) {
			sys_FreeMemoryEz(work);
			return TRUE;
		}
		break;
	}

	if (work->CameraZoomStartFlg){
		AnimeCameraZoomIn(fsys->camera_ptr, &work->CameraZoomCount);		//�Y�[���C��
	}

	return FALSE;
}

//==============================================================================
/**
 * �V���b�g�E�X���C�h�C��
 * 
 * @param	event	�C�x���g�|�C���^
 *
 * @retval  BOOL	TRUE:�C�x���g�I���@FALSE�F�C�x���g�p��
 */
//==============================================================================
BOOL MapJump_EventFadeInShutSlide(GMEVENT_CONTROL * event)
{
	FIELD_OBJ_PTR fop;
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	FMJ_WORK_PTR work = FieldEvent_GetSpecialWork(event);
	switch (work->seq) {
	case 0:
		{
			u8 dir;
			u8 main_wipe_type;
			fop = Player_FieldOBJGet( fsys->player );
			dir = Player_DirGet( fsys->player );
			//�������̏ꍇ�͎��@��\��
			if ( dir == DIR_DOWN){
				FieldOBJ_StatusBitSet_Vanish( fop, TRUE );
				(work->seq) = 1;
			}else{
				//���@�\��
				FieldOBJ_StatusBitSet_Vanish( fop, FALSE );
				(work->seq) = 3;
		
			}
			//�J�����Y�[��������
			work->CameraZoomStartFlg = FALSE;
			work->CameraZoomCount = 0;	
			
			//�J�����̃Y�[�����Z�b�g���Ȃ���
			{
				//�p�[�X�̕ۑ�
				work->PerspWayWork = GFC_GetCameraPerspWay(fsys->camera_ptr);
				//�p�[�X��������
				GFC_AddCameraPerspWay(-(ZOOM_VAL),fsys->camera_ptr);	
			}

			//�����ʂɃ��C�v�̎�ނ𕪂���
			switch(dir){
			case DIR_UP:
				main_wipe_type = WIPE_TYPE_SHUTTERIN_DOWN;
				break;
			case DIR_DOWN:
				main_wipe_type = WIPE_TYPE_SHUTTERIN_UP;
				break;
			case DIR_LEFT:
				main_wipe_type = WIPE_TYPE_SLIDEIN;
				break;
			case DIR_RIGHT:
				main_wipe_type = WIPE_TYPE_SLIDEIN_LR;
				break;
			default:
				GF_ASSERT(0);
			}
			
			//���C�v�X�^�[�g	�V���b�g�E�X���C�h�C��
			MJUMP_RequestWipe(	event, WIPE_PATTERN_WMS, main_wipe_type,
								WIPE_TYPE_FADEIN,0x0000,COMM_BRIGHTNESS_SYNC,1,HEAPID_WORLD );
			work->CameraZoomStartFlg = TRUE;	//�Y�[���A�E�g�J�n
		}
		break;
	case 1:
		fop = Player_FieldOBJGet( fsys->player );
		//���@�\��
		FieldOBJ_StatusBitSet_Vanish( fop, FALSE );
		FieldOBJ_AcmdSet(fop,AC_WALK_D_8F);	//�A�j���Z�b�g
		(work->seq) ++;
		break;
	case 2:
		fop = Player_FieldOBJGet( fsys->player );
		if( FieldOBJ_AcmdEndCheck(fop) == TRUE ){	//�A�j���I���`�F�b�N
			FieldOBJ_AcmdEnd(fop); //�A�j���I��
			(work->seq) ++;
		}
		break;
	case 3:
		//���C�v�I���A�Y�[���I���҂�
		if ( WIPE_SYS_EndCheck()&&
				( work->PerspWayWork == GFC_GetCameraPerspWay(fsys->camera_ptr) ) ) {
			sys_FreeMemoryEz(work);
			return TRUE;
		}
		break;
	}

	if (work->CameraZoomStartFlg){
		AnimeCameraZoomOut(fsys->camera_ptr, &work->CameraZoomCount);		//�Y�[���A�E�g
	}

	return FALSE;
}

//==============================================================================
/**
 * �u���b�N�C��
 * 
 * @param	event	�C�x���g�|�C���^
 *
 * @retval  BOOL	TRUE:�C�x���g�I���@FALSE�F�C�x���g�p��
 */
//==============================================================================
BOOL MapJump_EventFadeInBlack(GMEVENT_CONTROL * event)
{
	FIELD_OBJ_PTR fop;
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	FMJ_WORK_PTR work = FieldEvent_GetSpecialWork(event);
	switch (work->seq) {
	case 0:
		{
			u8 dir;
			u8 main_wipe_type;
			fop = Player_FieldOBJGet( fsys->player );
			dir = Player_DirGet( fsys->player );
			//�������̏ꍇ�͎��@��\��
			if ( dir == DIR_DOWN){
				FieldOBJ_StatusBitSet_Vanish( fop, TRUE );
				(work->seq) = 1;
			}else{
				//���@�\��
				FieldOBJ_StatusBitSet_Vanish( fop, FALSE );
				(work->seq) = 3;
		
			}
			
			MJUMP_RequestWipe(	event, WIPE_PATTERN_WMS, WIPE_TYPE_FADEIN,
								WIPE_TYPE_FADEIN,0x0000,COMM_BRIGHTNESS_SYNC,1,HEAPID_WORLD );
		}
		break;
	case 1:
		fop = Player_FieldOBJGet( fsys->player );
		//���@�\��
		FieldOBJ_StatusBitSet_Vanish( fop, FALSE );
		FieldOBJ_AcmdSet(fop,AC_WALK_D_8F);	//�A�j���Z�b�g
		(work->seq) ++;
		break;
	case 2:
		fop = Player_FieldOBJGet( fsys->player );
		if( FieldOBJ_AcmdEndCheck(fop) == TRUE ){	//�A�j���I���`�F�b�N
			FieldOBJ_AcmdEnd(fop); //�A�j���I��
			(work->seq) ++;
		}
		break;
	case 3:
		//���C�v�I���҂�
		if ( WIPE_SYS_EndCheck() ){
			sys_FreeMemoryEz(work);
			return TRUE;
		}
		break;
	}

	return FALSE;
}

