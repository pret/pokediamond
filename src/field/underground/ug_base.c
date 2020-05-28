//============================================================================================
/**
 * @file	ug_base.c
 * @brief	�閧��n
 * @author	saito
 * @date	2006.02.21
 *
 */
//============================================================================================

#include "common.h"
#include "../fieldsys.h"
#include "../field_event.h"

#include "savedata/undergrounddata.h"

#include "ug_base_bmp.h"

#include "../goods_data.h"

#include "../floor_touch.h"

#include "msgdata/msg_uwedit.h"
#include "ug_manager.h"
#include "fielddata/base_goods/goods_id_def.h"
#include "ug_base_se_def.h"

#include "../fieldmap_work.h"
#include "../fieldmap_func.h"

#include "ug_base.h"

#define GOODS_HIT_LIST_MAX	(32)	//�p�\�R��1�A�O�b�Y15�A��16

#define BASE_EDIT_BLOCK_OFS_X	(0)	//��n�ҏW���̒n���u���b�NX���W
#define BASE_EDIT_BLOCK_OFS_Z	(0) //��n�ҏW���̒n���u���b�NZ���W
#define BASE_EDIT_GRID_OFS_X	(BASE_EDIT_BLOCK_OFS_X*32)
#define BASE_EDIT_GRID_OFS_Z	(BASE_EDIT_BLOCK_OFS_Z*32)
#define EDIT_START_X	(16)		//�ҏW��_X���W
#define EDIT_START_Z	(13)		//�ҏW��_Z���W

#define BASE_LX			(10)
#define BASE_LZ			(12)
#define BASE_RX			(21)
#define BASE_RZ			(23)

#define PASO_LX			(15)
#define PASO_LZ			(13)
#define PASO_RX			(16)
#define PASO_RZ			(13)

#define EXIT_LX			(15)
#define EXIT_LZ			(23)
#define EXIT_RX			(15)
#define EXIT_RZ			(23)

#define PUT_BLINK_TIME	(4)
#define COLLECT_BLINK_TIME	(8)

#define GOODS_PUT_MAX	(15)	//�u�����Ƃ��ł���O�b�Y�̍ő吔

#define MSG_WAIT	(30)
#define MSG_DEL_WAIT	(10)

#define ROCK_MAX	(16)

#define KEY_RAG		(8)

typedef enum {
	BASE_SEQ_SETUP,
	BASE_SEQ_MAIN_MENU,
	BASE_SEQ_PUT_CONT,
	BASE_SEQ_COLLECT_CONT,
	BASE_SEQ_REPUT_CONT,
	BASE_SEQ_REPUT_SET_CONT,
	BASE_SEQ_MSG_WAIT,
	BASE_SEQ_END
};

//�e�@�\���̃V�[�P���X
//�ݒu
enum {
	PUT_SEQ_GOODS_LIST = 0,
	PUT_SEQ_INIT,
	PUT_SEQ_MAIN,
	PUT_SEQ_PUT_NG,
	PUT_SEQ_PUT_OK,
	PUT_SEQ_PUT_ALREADY,
};

//���
enum {
	COL_SEQ_INIT = 0,
	COL_SEQ_MAIN,
	COL_SEQ_COL_ROCK,
	COL_SEQ_COL_OK,
	COL_SEQ_COL_NG,
	COL_SEQ_ROCK_REST_BEFORE,
	COL_SEQ_ROCK_REST,
};

//�Ĕz�u�i�^�[�Q�b�g�w��j
enum {
	REPUT_SEQ_INIT = 0,
	REPUT_SEQ_MAIN,
	REPUT_SEQ_COL_NG,
};

//�Ĕz�u�i�ݒu�j
enum {
	REPUTSET_SEQ_INIT = 0,
	REPUTSET_SEQ_MAIN,
	REPUTSET_SEQ_PUT_NG,
	REPUTSET_SEQ_PUT_OK,
};

typedef struct KEY_CONT_tag
{
	int OldKey;
	u8 Count;
}KEY_CONT;

typedef struct BLINK_DATA_tag
{
	int TargetIndex;
	int Count;
	int CountMax;
	BOOL Vanish;
	BOOL Valid;
}BLINK_DATA;

typedef struct RECT_DATA_tag
{
	int GridLX;	//����O���b�h���WX
	int GridLZ;	//����O���b�h���WZ
	int GridRX;	//�E���O���b�h���WX
	int GridRZ;	//�E���O���b�h���WZ
}RECT_DATA;

typedef struct GOODS_HIT_DAT_tag
{
	RECT_DATA	Rect;
/**	
	int GridLX;	//����O���b�h���WX
	int GridLZ;	//����O���b�h���WZ
	int GridRX;	//�E���O���b�h���WX
	int GridRZ;	//�E���O���b�h���WZ
*/
	int ObjEntryIndex;	//OBJ�G���g���C���f�b�N�X
	int No;		//�O�b�Y�i���o�[
	int Width;
	int Depth;
}GOODS_HIT_DAT;

typedef struct GOODS_OLD_POS_INFO_tag
{
	int TargetIndex;
	VecFx32 Trans;
	GOODS_HIT_DAT Data;
}GOODS_OLD_POS_INFO;

typedef struct GOODS_HIT_LIST_ITEM_tag
{
	BOOL Valid;	//�f�[�^�L���t���O
	GOODS_HIT_DAT Data;
}GOODS_HIT_LIST_ITEM;


//�I���X�N�G�A
typedef struct UG_BASE_PANEL_tag
{
	NNSG3dRenderObj			renderobj;
	NNSG3dResFileHeader* 	resfileheader;

	VecFx32 trans;	//���W
	int GridX;
	int GridZ;
	BOOL DrawFlg;
}UG_BASE_PANEL;

typedef struct UG_BASE_TP_tag
{
	int TpX;//���݂̃^�b�`�ۑ����W
	int TpY;
	BOOL TrgFlg;//���݂̃^�b�`�󋵁i������Ă���A������Ă���j
}UG_BASE_TP;

typedef struct EVENT_BASE_EDIT_WORK_tag
{
	int seq;
	int SubSeq;
	int MesIndex;
	GOODS_OLD_POS_INFO OldPosInfo;
	GOODS_HIT_DAT	EditGoodsData;
	GOODS_HIT_LIST_ITEM	GoodsHitList[GOODS_HIT_LIST_MAX];
	BLINK_DATA	BlinkData;
	UG_BASE_TP	BaseTp;
	UG_BASE_PANEL *Panel;		//�t�B�[���h�}�b�v�t�@���N�̃��[�N�|�C���^
	FIELDSYS_WORK * fsys;
	UG_BASE_MENU *MainMenu;
	UG_BASE_LIST *GoodsList;
	FLDMAPFUNC_WORK* FldMapFunc;
	KEY_CONT	KeyCont;
	u16	MainMenuLine;
	u16	GoodsListLine;
	u16	MainMenuCurPos;
	u16	GoodsListCurPos;

	u8 MesWait;
	u8 GoodsCount;	//�u���Ă���O�b�Y��
	u8 RockCount;	//�閧��n�ɂ����̐�
	u8 RockLimit;	//�u���Ă����Ȃ���΂Ȃ�Ȃ���̐�
	u8 GoodsLimit;	//�u����O�b�Y��
}EVENT_BASE_EDIT_WORK;

static BOOL MenuEvent(GMEVENT_CONTROL * event);
static BOOL EditLayoutEvent(GMEVENT_CONTROL * event);

static BOOL PutControl(GMEVENT_CONTROL * event);
static BOOL CollectControl(GMEVENT_CONTROL * event);
static BOOL ReputControl(GMEVENT_CONTROL * event);
static BOOL ReputSetControl(GMEVENT_CONTROL * event);
static void EntryNewGoods(FIELDSYS_WORK * fsys, const int inGoodsNo, EVENT_BASE_EDIT_WORK *work);
static void CancelGoodsEntry(FIELDSYS_WORK * fsys, /*const int inCode,*/ const int inEntryIndex);
static void CopyEditDataFromList(const int inIndex, EVENT_BASE_EDIT_WORK *ebew);
static BOOL CheckPutGoods(const GOODS_HIT_DAT *inData, const GOODS_HIT_LIST_ITEM *inList);
static BOOL CheckCollectGoods(	const int inGridX, const int inGridZ,
								const GOODS_HIT_LIST_ITEM *inList,
								int *outIndex);
static int EntryGoodsList(const GOODS_HIT_DAT *inData, GOODS_HIT_LIST_ITEM *ioList);
static void EntryGoodsListByIndex(const GOODS_HIT_DAT *inData, const int inIndex, GOODS_HIT_LIST_ITEM *ioList);
static void ClearGoodListByIndex(const int inIndex, GOODS_HIT_LIST_ITEM *outList);
static BOOL CheckRectHit(const RECT_DATA *inData1, const RECT_DATA *inData2);
static BOOL CheckPointHit(const RECT_DATA *inData, const int inX, const int inZ);
static BOOL CheckHitWall(const RECT_DATA *inData);

static void MakeGoodsHitList(FIELDSYS_WORK * fsys, EVENT_BASE_EDIT_WORK *ebew, GOODS_HIT_LIST_ITEM *outList);
static void MakeGoodsHitData(	const int inIndex, const int inGoodsNo,
								const int inX, const int inZ,
								GOODS_HIT_LIST_ITEM *outList	);
static void MakeGoodsMap3DObj(FIELDSYS_WORK *fsys, GOODS_HIT_LIST_ITEM *ioList);
static void WriteSaveData(FIELDSYS_WORK *fsys, const GOODS_HIT_LIST_ITEM *inList);

static const int GetGoodsObjID(FIELDSYS_WORK *fsys, const int inGoodsNo);
static void SetGoodsOldPos(const int inIndex, EVENT_BASE_EDIT_WORK * ebew);
static void PutGoodsOldPos(EVENT_BASE_EDIT_WORK * ebew);

static void SetNextSeqCall(const int inSeq, EVENT_BASE_EDIT_WORK * ebew);

static void SetupPanel(UG_BASE_PANEL *outPanel);
static void ReleasePanel(UG_BASE_PANEL *outPanel);
static void DispOnPanelFlgOnly(UG_BASE_PANEL *outPanel);
static void SetPanelPos(const int inGridX, const int inGridZ, UG_BASE_PANEL *outPanel);
//static void DispOnPanel(void);
static void DispOffPanel(UG_BASE_PANEL *outPanel);

static BOOL TpGoodsPutControl(EVENT_BASE_EDIT_WORK * ebew, FIELDSYS_WORK * fsys, BOOL *outPut);
static BOOL TpGoodsCollectControl(EVENT_BASE_EDIT_WORK * ebew, FIELDSYS_WORK * fsys, BOOL *outCollect);
static BOOL TpGoodsReputControl(EVENT_BASE_EDIT_WORK * ebew, FIELDSYS_WORK * fsys, BOOL *outReput);
static BOOL TpGoodsReputSetControl(EVENT_BASE_EDIT_WORK * ebew, FIELDSYS_WORK * fsys, BOOL *outReput);

static void InitBlinkData(BLINK_DATA *outBlinkData);
static void SetBlinkTarget(const int inTarget, const int inCountMax, BLINK_DATA *outBlinkData);
static void BlinkTarget(FIELDSYS_WORK *fsys, BLINK_DATA *ioBlinkData);
static void StopBlink(FIELDSYS_WORK *fsys, BLINK_DATA *inBlinkData);
static const int GetBlinkTarget(BLINK_DATA *inBlinkData);

static void InitBasePanel(FLDMAPFUNC_WORK * fwk, FIELDSYS_WORK * fsys, void * work);
static void BasePanelDummy(FLDMAPFUNC_WORK * fwk, FIELDSYS_WORK * fsys, void * work);
static void EndBasePanel(FLDMAPFUNC_WORK * fwk, FIELDSYS_WORK * fsys, void * work);
static void DrawBasePanel(FLDMAPFUNC_WORK * fwk, FIELDSYS_WORK * fsys, void * work);

static const FLDMAPFUNC_DATA BasePanelData = {
	FLDMAP_PRI_BASE_PANEL,
	sizeof(UG_BASE_PANEL),
	InitBasePanel,
	EndBasePanel,
	BasePanelDummy,
	DrawBasePanel,
};


//������u������z�u���f���Ƃ��ēo�^
static void EntryNewGoods(FIELDSYS_WORK * fsys, const int inGoodsNo, EVENT_BASE_EDIT_WORK *ebew)
{
	GOODS_HIT_DAT *data;
	VecFx32 trans;

	GF_ASSERT(inGoodsNo!=0&&"�i���o�[0�̃O�b�Y�͂���܂���");
	
	//������u�������Z�b�g
	data = &ebew->EditGoodsData;

	//�O�b�Y���ɃA�N�Z�X���āA�c���T�C�Y���擾
	data->Width = GOODS_GetGoodsSizeX(inGoodsNo);
	data->Depth = GOODS_GetGoodsSizeZ(inGoodsNo);

///	OS_Printf("Goods:%d,size = %d,%d\n",inGoodsNo,data->Width,data->Depth);	
	
	trans.x = (FX32_ONE*16)*(BASE_EDIT_GRID_OFS_X+EDIT_START_X)+((FX32_ONE*8)*data->Width);
	trans.y = /*0*/FX32_ONE;
	trans.z = (FX32_ONE*16)*(BASE_EDIT_GRID_OFS_Z+EDIT_START_Z)+((FX32_ONE*8)*data->Depth);

	data->ObjEntryIndex =  
		M3DO_SetMap3DObjExp(fsys->Map3DObjExp,
							fsys->MapResource,
							GetGoodsObjID(fsys, inGoodsNo),
							&trans,	NULL,		//
							fsys->field_3d_anime);

	
	//��n���ǂ����z�u����悤�ƁA�Ǘ���0,0��_�ōs��
	data->Rect.GridLX = EDIT_START_X;
	data->Rect.GridLZ = EDIT_START_Z;
	data->Rect.GridRX = EDIT_START_X+(data->Width-1);
	data->Rect.GridRZ = EDIT_START_Z+(data->Depth-1);
	data->No = inGoodsNo;//�O�b�Y�i���o�[�Z�b�g
}

//�G���g��������
static void CancelGoodsEntry(FIELDSYS_WORK * fsys, const int inEntryIndex)
{
	M3DO_CleanMap3DObj(inEntryIndex, fsys->Map3DObjExp);
}

//���X�g�̎w��f�[�^��ҏW�o�b�t�@�ɃR�s�[����
static void CopyEditDataFromList(const int inIndex, EVENT_BASE_EDIT_WORK *ebew)
{
	GOODS_HIT_DAT *data;
	GF_ASSERT(ebew->GoodsHitList[inIndex].Valid&&"�f�[�^�͖�����Ԃł�");
	data = &(ebew->GoodsHitList[inIndex].Data);
	ebew->EditGoodsData = (*data);
}

//�閧��n���C�A�E�g�ύX����C�x���g�̔��s
static BOOL EditLayoutEvent(GMEVENT_CONTROL * event)
{
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	EVENT_BASE_EDIT_WORK * ebew = FieldEvent_GetSpecialWork(event);
	switch(ebew->seq){
	case BASE_SEQ_SETUP:
		sys_KeyRepeatSpeedSet( 4, 8 );
		//��n���C�����j���[�ݒ�
		ebew->MainMenu = BMENU_AllocUgBaseMenu();
		BMENU_InitBaseMainMenu(	ebew->MainMenu, fsys,
								&ebew->MainMenuLine, &ebew->MainMenuCurPos);

		//�O�b�Y���X�g�ݒ�
		ebew->GoodsList = BMENU_AllocUgBaseGoodsList();
		BMENU_InitBaseGoodsList(ebew->GoodsList, fsys,
								&ebew->GoodsListLine, &ebew->GoodsListCurPos);
		
		//���j���[�R���g���[��
///		OS_Printf("�Z�[�u�f�[�^��ǂ�Ń��X�g�쐬\n");
		MakeGoodsHitList(fsys, ebew, ebew->GoodsHitList);
///		OS_Printf("Map3DObj���N���A���āA�G�f�B�b�g�p�ɍăZ�b�g\n");
		MakeGoodsMap3DObj(fsys, ebew->GoodsHitList);	
		
		SetNextSeqCall(BASE_SEQ_MAIN_MENU, ebew);
		break;
	case BASE_SEQ_MAIN_MENU:
///		OS_Printf("���j���[�E�B���h�E\n");
		FieldEvent_Call(event, MenuEvent, ebew);
		break;
	case BASE_SEQ_PUT_CONT:
		//�ݒu
		FieldEvent_Call(event, PutControl, ebew);
		break;
	case BASE_SEQ_COLLECT_CONT:
		//���
		FieldEvent_Call(event, CollectControl, ebew);
		break;
	case BASE_SEQ_REPUT_CONT:
		//�Ĕz�u(�O�b�Y�w��)
		FieldEvent_Call(event, ReputControl, ebew);
		break;
	case BASE_SEQ_REPUT_SET_CONT:
		//�Ĕz�u�i�ݒu�j
		FieldEvent_Call(event, ReputSetControl, ebew);
		break;
	case BASE_SEQ_MSG_WAIT:
		//���b�Z�[�W�҂�
		if( GF_MSG_PrintEndCheck( ebew->MesIndex ) == 0 ){
			if ((ebew->MesWait++)>=MSG_WAIT){
				UgSecretBaseTalkEnd();
				SetNextSeqCall(BASE_SEQ_MAIN_MENU, ebew);
			}
		}	
		break;
	case BASE_SEQ_END:
		//�I��
///		OS_Printf("��n�����I��\n");
		
		//�O�b�Y���X�g���
		BMENU_FreeUgBaseGoodsList(ebew->GoodsList);

		//��n���C�����j���[���
		BMENU_FreeUgBaseMenu(ebew->MainMenu);

		//�t�B�[���h�}�b�v�t�@���N���
		FLDMAPFUNC_Delete(ebew->FldMapFunc);
		
		sys_FreeMemoryEz(ebew);
		return TRUE;
	}
	return FALSE;
}

//���j���[�C�x���g
static BOOL MenuEvent(GMEVENT_CONTROL * event)
{
	BOOL rc;
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	EVENT_BASE_EDIT_WORK * ebew = FieldEvent_GetSpecialWork(event);

	//�G�f�B�b�g���C�����j���[
	rc = BMENU_EditMainMenuControl(ebew->MainMenu);

	if (rc){
		//���j���[�̃C���f�b�N�X�����Ăǂ̃��[�h�ɔ�΂����𔻒�
		switch(BMENU_GetReturnIndex(ebew->MainMenu)){
		case 0:		//�ݒu���[�h
			{
				//���`�F�b�N
				UNDERGROUNDDATA* pUGData;
				int count;
				pUGData = SaveData_GetUnderGroundData(fsys->savedata);
				count = UnderGroundGetNumGoodsPCItem(pUGData);
				if (count == 0){//�������Ă�O�b�Y�����邩�H
					//���b�Z�[�W�F�O�b�Y���@����܂���
					ebew->MesIndex = UgSecretBaseTalkStart(mes_uw_edit_20);
					ebew->MesWait = 0;
					SetNextSeqCall(BASE_SEQ_MSG_WAIT, ebew);
					return TRUE;
				}
				if (ebew->GoodsCount>GOODS_PUT_MAX){
///					OS_Printf("����ȏ�͒u���܂���\n");
					//���b�Z�[�W�F���ꂢ���傤�@�O�b�Y�́@�����܂���
					ebew->MesIndex = UgSecretBaseTalkStart(mes_uw_edit_21);
					ebew->MesWait = 0;
					SetNextSeqCall(BASE_SEQ_MSG_WAIT, ebew);
					return TRUE;
				}
				if (ebew->GoodsCount+1>ebew->GoodsLimit){
///					OS_Printf("�O�b�Y��u���ɂ́A���x��������Ȃ�\n");
					//���b�Z�[�W�F���ꂢ���傤�@�O�b�Y�́@�����܂���
					ebew->MesIndex = UgSecretBaseTalkStart(mes_uw_edit_21);
					ebew->MesWait = 0;
					SetNextSeqCall(BASE_SEQ_MSG_WAIT, ebew);
					return TRUE;
				}
			}
			//�G���g��
///			OS_Printf("�ݒu���[�h\n");
			//�u����O�b�Y���ƒu���Ă���O�b�Y�������X�g�ɃZ�b�g
			BMENU_SetGoodsNumToList(ebew->GoodsList, ebew->GoodsCount, ebew->GoodsLimit);
			
			SetNextSeqCall(BASE_SEQ_PUT_CONT, ebew);
			return TRUE;
		case 1:		//������[�h
			//���
///			OS_Printf("������[�h\n");
			//����̂݃p�l���ʒu�Z�b�g
			SetPanelPos(EDIT_START_X, EDIT_START_Z, ebew->Panel);
			SetNextSeqCall(BASE_SEQ_COLLECT_CONT, ebew);
			return TRUE;
		case 2:		//�Ĕz�u���[�h
			//�Ĕz�u
///			OS_Printf("�Ĕz�u���[�h\n");
			//����̂݃p�l���ʒu�Z�b�g
			SetPanelPos(EDIT_START_X, EDIT_START_Z, ebew->Panel);
			SetNextSeqCall(BASE_SEQ_REPUT_CONT, ebew);
			return TRUE;
		default:	//�I��
			//�Z�[�u�ɏ���
			WriteSaveData(fsys, ebew->GoodsHitList)	;
			SetNextSeqCall(BASE_SEQ_END, ebew);
			return TRUE;
			break;
		}
	}
	return FALSE;
}

//�C�x���gCALL
void UGBase_CallBaseEditEvent(FIELDSYS_WORK * fsys,GMEVENT_CONTROL* mainEvent)
{
	//��n�G�f�B�b�g�p���[�N
	EVENT_BASE_EDIT_WORK * ebew = sys_AllocMemoryLo(HEAPID_WORLD, sizeof(EVENT_BASE_EDIT_WORK));
	MI_CpuClear8(ebew, sizeof(EVENT_BASE_EDIT_WORK));

	SetNextSeqCall(BASE_SEQ_SETUP, ebew);
	ebew->fsys = fsys;

	//�p�l���`��p�t�B�[���h�}�b�v�t�@���N�쐬
	ebew->FldMapFunc = FLDMAPFUNC_Create(fsys->fldmap->fmapfunc_sys, &BasePanelData);
	//�p�l���`��p�t�B�[���h�}�b�v�t�@���N�̃|�C���^���擾
	ebew->Panel = FLDMAPFUNC_GetFreeWork(ebew->FldMapFunc);

	//�}�b�v�W�����v�C�x���g���쐬
	FieldEvent_Call(mainEvent, EditLayoutEvent, ebew);
}

static BOOL PutControl(GMEVENT_CONTROL * event)
{
	
	fx32 plus_x, plus_z;
	M3DO_PTR ptr;
	BOOL tp_touch;
	BOOL put;

	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	EVENT_BASE_EDIT_WORK * ebew = FieldEvent_GetSpecialWork(event);

	switch(ebew->SubSeq){
	case PUT_SEQ_GOODS_LIST:
		{
			BOOL rc;
			//�G�f�B�b�g���C�����j���[
			rc = BMENU_EditGoodsListControl(ebew->GoodsList);
			if (rc){
				u32 idx;
				int goods_no;
				UNDERGROUNDDATA* pUGData;
				pUGData = SaveData_GetUnderGroundData(ebew->fsys->savedata);

				//���^�[���R�[�h�𒲂ׂ�
				idx = BMENU_GetReturnListIdx(ebew->GoodsList);
				if (idx == LIST_CANCEL_CODE){	//�L�����Z���̏ꍇ
					//�V�[�P���X�����C�����j���[��
					SetNextSeqCall(BASE_SEQ_MAIN_MENU, ebew);//���C�����j���[
					return TRUE;
				}
				
				goods_no = UnderGroundGetGoodsPCItem(pUGData,idx);
				if (goods_no!=GOODS_INVALID){	//�O�b�Y�̏ꍇ
					//���łɊ�n�ɂ����Ă��邩���`�F�b�N
					BOOL check;
					check = UnderGroundIsEntryGoodsPCItem(pUGData, idx);
					if (!check){//�z�u����Ă��Ȃ�
						//�z�u���Ƃ��ēo�^����
						EntryNewGoods(fsys, goods_no, ebew);
						ebew->SubSeq = PUT_SEQ_INIT;
					}else{	//�u���Ă���
						//���b�Z�[�W�F���̃O�b�Y�́@�����@������Ă��܂�
						ebew->MesIndex = UgSecretBaseTalkStart(mes_uw_edit_22);
						ebew->MesWait = 0;
						ebew->SubSeq = PUT_SEQ_PUT_ALREADY;
					}
				}else{			
					GF_ASSERT(0&&"�O�b�Y�����ʂł��܂���");
				}
			}
		}
		break;	
	case PUT_SEQ_INIT:
		InitBlinkData(&ebew->BlinkData);
		SetBlinkTarget(ebew->EditGoodsData.ObjEntryIndex, PUT_BLINK_TIME, &ebew->BlinkData);
		ebew->SubSeq = PUT_SEQ_MAIN;
		break;
	case PUT_SEQ_MAIN:
		//�_�ŏ���
		BlinkTarget(fsys, &ebew->BlinkData);
	
		tp_touch = TpGoodsPutControl(ebew, fsys, &put);
	
		if (!tp_touch){	//�^�b�`���Ă��Ȃ��ꍇ
			BOOL edit;
			RECT_DATA rect;
			edit = TRUE;
			rect = ebew->EditGoodsData.Rect;
			if (sys.repeat & PAD_KEY_LEFT){
				plus_x = -(FX32_ONE*16);
				plus_z = 0;
				rect.GridLX--;
				rect.GridRX--;
			}else if (sys.repeat & PAD_KEY_RIGHT){
				plus_x = (FX32_ONE*16);
				plus_z = 0;
				rect.GridLX++;
				rect.GridRX++;
			}else if (sys.repeat & PAD_KEY_UP){
				plus_x = 0;
				plus_z = -(FX32_ONE*16);
				rect.GridLZ--;
				rect.GridRZ--;
			}else if (sys.repeat & PAD_KEY_DOWN){
				plus_x = 0;
				plus_z = (FX32_ONE*16);
				rect.GridLZ++;
				rect.GridRZ++;
			}else{
				edit = FALSE;
			}

			if (edit != FALSE){
				if ( !CheckHitWall(&rect) ){
					VecFx32 vec;
					ebew->EditGoodsData.Rect = rect;
					ptr = M3DO_GetMap3DObjDataFromIndex(fsys->Map3DObjExp, ebew->EditGoodsData.ObjEntryIndex);
					vec = M3DO_GetGlobalVec(ptr);
					vec.x += (plus_x);
					vec.z += (plus_z);
					vec.y = FX32_ONE;
					M3DO_SetGlobalVec(ptr, &vec);
				}
			}

			if (sys.trg & PAD_BUTTON_DECIDE){
				put = TRUE;
			}else if(sys.trg & PAD_BUTTON_CANCEL){
				//�}�b�v3DOBJ����G���g���N���A
				CancelGoodsEntry(fsys, ebew->EditGoodsData.ObjEntryIndex);
				//���j���[��
				ebew->SubSeq = PUT_SEQ_GOODS_LIST;
				return FALSE;
			}
		}

		if (put){
			BOOL rc;
			//�u���邩�`�F�b�N
			rc = CheckPutGoods(&ebew->EditGoodsData, ebew->GoodsHitList);
			if (rc){		//�ݒuOK
				u32 idx;
				int pos;
				UNDERGROUNDDATA* pUGData;
				pUGData = SaveData_GetUnderGroundData(ebew->fsys->savedata);
				pos = EntryGoodsList(&ebew->EditGoodsData, ebew->GoodsHitList);
				idx = BMENU_GetReturnListIdx(ebew->GoodsList);	
				//�z�u���Ƃ��ēo�^����
				UnderGroundEntryGoodsPCItem(pUGData, idx, pos);

				Snd_SePlay( UG_BASE_SE_PUT );		//�O�b�Y�u����
				
				UgSecretBaseTalkRegisterGoodsName(ebew->EditGoodsData.No);
				//���b�Z�[�W�F�`�@���@�����������I
				ebew->MesIndex = UgSecretBaseTalkStart(mes_uw_edit_12);
				
				//�_�ł�����
				StopBlink(fsys, &ebew->BlinkData);
				ebew->GoodsCount++;
/**				
				//�V�[�P���X�����C�����j���[��
				SetNextSeqCall(BASE_SEQ_MAIN_MENU, ebew);//���C�����j���[//<<060306move
				return TRUE;
*/
				ebew->MesWait = 0;
				ebew->SubSeq = PUT_SEQ_PUT_OK;
				break;
			}else{
				Snd_SePlay( UG_BASE_SE_PUT_NG );		//�O�b�Y�u���Ȃ���
				//���b�Z�[�W�F���́@�΂���ɂ́@�����܂���
				ebew->MesIndex = UgSecretBaseTalkStart(mes_uw_edit_13);
				ebew->MesWait = 0;
				ebew->SubSeq = PUT_SEQ_PUT_NG;
			}
		}
		break;
	case PUT_SEQ_PUT_NG:	//�u���Ȃ��Ƃ�
		//���b�Z�[�W�҂�
		if( GF_MSG_PrintEndCheck( ebew->MesIndex ) == 0 ){
			if ((ebew->MesWait++)>=MSG_WAIT){
				UgSecretBaseTalkEnd();
				ebew->SubSeq = PUT_SEQ_MAIN;
			}
		}
		break;
	case PUT_SEQ_PUT_OK:	//�u�����Ƃ�
		//���b�Z�[�W�҂�
		if( GF_MSG_PrintEndCheck( ebew->MesIndex ) == 0 ){
			if ((ebew->MesWait++)>=MSG_WAIT){
				UgSecretBaseTalkEnd();
				//�V�[�P���X�����C�����j���[��
				SetNextSeqCall(BASE_SEQ_MAIN_MENU, ebew);//���C�����j���[
				return TRUE;
			}
		}
		break;
	case PUT_SEQ_PUT_ALREADY:	//���łɒu���Ă����Ƃ��̃��b�Z�[�W�E�F�C�g
		//���b�Z�[�W�҂�
		if( GF_MSG_PrintEndCheck( ebew->MesIndex ) == 0 ){
			if ((ebew->MesWait++)>=MSG_WAIT){
				UgSecretBaseTalkEnd();
				ebew->SubSeq = PUT_SEQ_GOODS_LIST;
			}
		}
		break;
	}//end switch
	return FALSE;
}

//����R���g���[��
static BOOL CollectControl(GMEVENT_CONTROL * event)
{
	BOOL edit;
	RECT_DATA rect;
	fx32 trans_x,trans_z;
	BOOL tp_touch;
	BOOL collect;
	
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	EVENT_BASE_EDIT_WORK * ebew = FieldEvent_GetSpecialWork(event);
	
	switch(ebew->SubSeq){
	case COL_SEQ_INIT:
		InitBlinkData(&ebew->BlinkData);
		DispOnPanelFlgOnly(ebew->Panel); //<2003.04.28 add
		//�����ʒu�ɕ����u���Ă���ꍇ�A�_�ŏ�Ԃ����
		{
			BOOL hit;
			int list_idx;
			hit = CheckCollectGoods(ebew->Panel->GridX, ebew->Panel->GridZ, ebew->GoodsHitList, &list_idx);
			if (hit){
				SetBlinkTarget(	ebew->GoodsHitList[list_idx].Data.ObjEntryIndex,
								COLLECT_BLINK_TIME,
								&ebew->BlinkData	);
			}
		}
		ebew->SubSeq = COL_SEQ_MAIN;
		break;
	case COL_SEQ_MAIN:
		edit = TRUE;
		//�_�ŏ���
		BlinkTarget(fsys, &ebew->BlinkData);
		
		tp_touch = TpGoodsCollectControl(ebew, fsys, &collect);
		rect.GridLX = ebew->Panel->GridX;
		rect.GridRX = ebew->Panel->GridX;
		rect.GridLZ = ebew->Panel->GridZ;
		rect.GridRZ = ebew->Panel->GridZ;
		trans_x = ebew->Panel->trans.x;
		trans_z = ebew->Panel->trans.z;
		if (!tp_touch){	//�^�b�`���Ă��Ȃ��ꍇ
			if (sys.repeat & PAD_KEY_LEFT){
				Snd_SePlay( UG_BASE_SE_MOVE );
				trans_x-=(FX32_ONE*16);
				rect.GridLX--;
				rect.GridRX--;
			}else if (sys.repeat & PAD_KEY_RIGHT){
				Snd_SePlay( UG_BASE_SE_MOVE );
				trans_x+=(FX32_ONE*16);
				rect.GridLX++;
				rect.GridRX++;
			}else if (sys.repeat & PAD_KEY_UP){
				Snd_SePlay( UG_BASE_SE_MOVE );
				trans_z-=(FX32_ONE*16);
				rect.GridLZ--;
				rect.GridRZ--;
			}else if (sys.repeat & PAD_KEY_DOWN){
				Snd_SePlay( UG_BASE_SE_MOVE );
				trans_z+=(FX32_ONE*16);
				rect.GridLZ++;
				rect.GridRZ++;
			}else{
				edit = FALSE;
			}

			if (sys.trg & PAD_BUTTON_DECIDE){
				collect = TRUE;
			}else if(sys.trg & PAD_BUTTON_CANCEL){
				//�L�����Z��
///				OS_Printf("������L�����Z�����܂���\n");
				DispOffPanel(ebew->Panel);

				//���_�ł��Ă��邩������Ȃ�OBJ�̓_�ł��X�g�b�v
				StopBlink(fsys, &ebew->BlinkData);
				
				SetNextSeqCall(BASE_SEQ_MAIN_MENU, ebew);//���C�����j���[
				return TRUE;
			}
		}//end if(!tp_touch)

		if (edit){
			if ( !CheckHitWall(&rect) ){
				BOOL hit;
				int list_idx;

				ebew->Panel->trans.x = trans_x;
				ebew->Panel->trans.z = trans_z;
				ebew->Panel->GridX = rect.GridLX;
				ebew->Panel->GridZ = rect.GridLZ;
				
				hit = CheckCollectGoods(ebew->Panel->GridX, ebew->Panel->GridZ, ebew->GoodsHitList, &list_idx);
				if (hit){
					int idx;
					idx = GetBlinkTarget( &ebew->BlinkData );
					if (ebew->GoodsHitList[list_idx].Data.ObjEntryIndex != idx){
						//���_�ł��Ă��邩������Ȃ�OBJ�̓_�ł��X�g�b�v
						StopBlink(fsys, &ebew->BlinkData);
						//�O��ƈႤ���̂Ƀq�b�g�����ꍇ�̓Z�b�g������
						SetBlinkTarget(	ebew->GoodsHitList[list_idx].Data.ObjEntryIndex,
										COLLECT_BLINK_TIME,
										&ebew->BlinkData	);
					}
				}else{
					StopBlink(fsys, &ebew->BlinkData);
					InitBlinkData(&ebew->BlinkData);
				}
			}
		}

		if (collect){	
			BOOL rc;
			int x,z;
			int index;
			GF_ASSERT(ebew->Panel->GridX<32&&"�O���b�h�l���s��");
			GF_ASSERT(ebew->Panel->GridZ<32&&"�O���b�h�l���s��");

			x = ebew->Panel->GridX;
			z = ebew->Panel->GridZ;

			//���̃`�F�b�N
			rc = CheckCollectGoods(x, z, ebew->GoodsHitList, &index);
			if (rc){
				if (index!=SECRETBASE_PC_INDEX_NO){	//�p�\�R������
					UgSecretBaseTalkRegisterGoodsName(ebew->GoodsHitList[index].Data.No);
					if (ebew->GoodsHitList[index].Data.No == GOODS_UG_IWA){	//�┻��
						//���P���ł��邩���`�F�b�N
						if (ebew->RockLimit == ROCK_MAX){
							//���x���O�Ȃ̂Ŋ�j�󖳗�
							////���b�Z�[�W�F������@�������イ�@���邱�Ƃ�	 �ł��܂���
							ebew->MesIndex = UgSecretBaseTalkStart(mes_uw_edit_16);
							ebew->MesWait = 0;
							ebew->SubSeq = COL_SEQ_COL_NG;
							break;
						}
						else if (ebew->RockCount-1<ebew->RockLimit){
							//���x��������Ȃ��ĉ���s��
							//���b�Z�[�W�F���ꂢ���傤�@�����	�������イ�@���邱�Ƃ́@�ł��܂���
							ebew->MesIndex = UgSecretBaseTalkStart(mes_uw_edit_19);
							ebew->MesWait = 0;
							ebew->SubSeq = COL_SEQ_COL_NG;
							break;
						}else{
							Snd_SePlay( UG_BASE_SE_BREAK );		//��󂵉�
							//���b�Z�[�W�F������@�������イ�@���ā@���킵�܂����I
							ebew->MesIndex = UgSecretBaseTalkStart(mes_uw_edit_15);
							GF_ASSERT(ebew->RockCount>0);
							ebew->RockCount--;	//�␔�f�N�������g
							ebew->MesWait = 0;
							ebew->SubSeq = COL_SEQ_COL_ROCK;
						}
					}else{
						UNDERGROUNDDATA* pUGData;
						pUGData = SaveData_GetUnderGroundData(ebew->fsys->savedata);
						Snd_SePlay( UG_BASE_SE_PICK );		//�O�b�Y�߂���
						//�p�\�R���ɖ߂�
						UnderGroundTrashGoodsPCItem(pUGData, index);
						//���b�Z�[�W�F�`�@���@�p�\�R���Ɂ@���ǂ���
						ebew->MesIndex = UgSecretBaseTalkStart(mes_uw_edit_14);
						GF_ASSERT(ebew->GoodsCount>0);
						ebew->GoodsCount--;//�O�b�Y���f�N�������g
						ebew->MesWait = 0;
						ebew->SubSeq = COL_SEQ_COL_OK;
					}
					//�}�b�v3DOBJ����G���g���N���A
					CancelGoodsEntry(fsys, ebew->GoodsHitList[index].Data.ObjEntryIndex);
					//���X�g����͂���
					ClearGoodListByIndex(index, ebew->GoodsHitList);
///					OS_Printf("������܂�\n");
									
					DispOffPanel(ebew->Panel);
/**
					SetNextSeqCall(BASE_SEQ_MAIN_MENU, ebew);//���C�����j���[<060306move
					return TRUE;
*/
					ebew->MesWait = 0;
				}else{
///					OS_Printf("�p�\�R���͉���ΏۊO�ł�\n");
					//���b�Z�[�W�F�p�\�R���́@���ǂ��܂���
					ebew->MesIndex = UgSecretBaseTalkStart(mes_uw_edit_23);
					ebew->MesWait = 0;
					ebew->SubSeq = COL_SEQ_COL_NG;
				}
			}else{
///				OS_Printf("��������܂���\n");
			}		
		}
		break;
	case COL_SEQ_COL_ROCK:
		//���b�Z�[�W�҂�
		if( GF_MSG_PrintEndCheck( ebew->MesIndex ) == 0 ){
			if ((ebew->MesWait++)>=MSG_WAIT){
				int num;
				UgSecretBaseTalkEnd();
				num = ebew->RockCount-ebew->RockLimit;
				GF_ASSERT(num>=0);
				if (num == 0){	//���b�Z�[�W�Ȃ�
					SetNextSeqCall(BASE_SEQ_MAIN_MENU, ebew);//���C�����j���[
					return TRUE;
				}else{
					/**
					UgSecretBaseTalkRegisterNum2(num, 0);
					//���b�Z�[�W�F����	�`��	�������イ	�ł��܂�
					ebew->MesIndex = UgSecretBaseTalkStart(mes_uw_edit_18);
					ebew->MesWait = 0;
					ebew->SubSeq = COL_SEQ_ROCK_REST;
					*/
					ebew->MesWait = 0;
					ebew->SubSeq = COL_SEQ_ROCK_REST_BEFORE;
				}
			}
		}
		break;
	case COL_SEQ_COL_OK:	//�������
		//���b�Z�[�W�҂�
		if( GF_MSG_PrintEndCheck( ebew->MesIndex ) == 0 ){
			if ((ebew->MesWait++)>=MSG_WAIT){
				UgSecretBaseTalkEnd();
//				SetNextSeqCall(BASE_SEQ_MAIN_MENU, ebew);//���C�����j���[
				//���p���ŉ���ł���悤�ɕύX	2006.04.28
				ebew->SubSeq = COL_SEQ_INIT;
				return TRUE;
			}
		}	
		break;
	case COL_SEQ_COL_NG:	//������s
		//���b�Z�[�W�҂�
		if( GF_MSG_PrintEndCheck( ebew->MesIndex ) == 0 ){
			if ((ebew->MesWait++)>=MSG_WAIT){
				UgSecretBaseTalkEnd();
				ebew->SubSeq = COL_SEQ_MAIN;
			}
		}
		break;
	case COL_SEQ_ROCK_REST_BEFORE:
		if ((ebew->MesWait++)>=MSG_DEL_WAIT){
			int num;
			num = ebew->RockCount-ebew->RockLimit;
			UgSecretBaseTalkRegisterNum2(num, 0);
			//���b�Z�[�W�F����	�`��	�������イ	�ł��܂�
			ebew->MesIndex = UgSecretBaseTalkStart(mes_uw_edit_18);
			ebew->MesWait = 0;
			ebew->SubSeq = COL_SEQ_ROCK_REST;
		}
		break;
	case COL_SEQ_ROCK_REST:
		//���b�Z�[�W�҂�
		if( GF_MSG_PrintEndCheck( ebew->MesIndex ) == 0 ){
			if ((ebew->MesWait++)>=MSG_WAIT){
				UgSecretBaseTalkEnd();
				SetNextSeqCall(BASE_SEQ_MAIN_MENU, ebew);//���C�����j���[
				return TRUE;
			}
		}
		break;
	}	//end switch
	return FALSE;
}

//�Đݒu�R���g���[��
static BOOL ReputControl(GMEVENT_CONTROL * event)
{
	BOOL edit;
	RECT_DATA rect;
	fx32 trans_x,trans_z;
	BOOL tp_touch;
	BOOL reput;
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	EVENT_BASE_EDIT_WORK * ebew = FieldEvent_GetSpecialWork(event);

	switch(ebew->SubSeq){
	case REPUT_SEQ_INIT:
		InitBlinkData(&ebew->BlinkData);
		DispOnPanelFlgOnly(ebew->Panel);
		//����ȊO�̂Ƃ��́A�p�l����OBJ�Ƀq�b�g���Ă���̂ŁA
		//�_�ŏ�Ԃ����(�����u���Ă���΁A������q�b�g����)
		{
			BOOL hit;
			int list_idx;
			hit = CheckCollectGoods(ebew->Panel->GridX, ebew->Panel->GridZ, ebew->GoodsHitList, &list_idx);
			if (hit){
				SetBlinkTarget(	ebew->GoodsHitList[list_idx].Data.ObjEntryIndex,
								COLLECT_BLINK_TIME,
								&ebew->BlinkData	);
			}
		}
		ebew->SubSeq = REPUT_SEQ_MAIN;
		break;
	case REPUT_SEQ_MAIN:
		edit = TRUE;
		//�_�ŏ���
		BlinkTarget(fsys, &ebew->BlinkData);
		
		tp_touch = TpGoodsReputControl(ebew, fsys, &reput);
		rect.GridLX = ebew->Panel->GridX;
		rect.GridRX = ebew->Panel->GridX;
		rect.GridLZ = ebew->Panel->GridZ;
		rect.GridRZ = ebew->Panel->GridZ;
		trans_x = ebew->Panel->trans.x;
		trans_z = ebew->Panel->trans.z;
		if (!tp_touch){	//�^�b�`���Ă��Ȃ��ꍇ
			if (sys.repeat & PAD_KEY_LEFT){
				Snd_SePlay( UG_BASE_SE_MOVE );
				trans_x-=(FX32_ONE*16);
				rect.GridLX--;
				rect.GridRX--;
			}else if (sys.repeat & PAD_KEY_RIGHT){
				Snd_SePlay( UG_BASE_SE_MOVE );
				trans_x+=(FX32_ONE*16);
				rect.GridLX++;
				rect.GridRX++;
			}else if (sys.repeat & PAD_KEY_UP){
				Snd_SePlay( UG_BASE_SE_MOVE );
				trans_z-=(FX32_ONE*16);
				rect.GridLZ--;
				rect.GridRZ--;
			}else if (sys.repeat & PAD_KEY_DOWN){
				Snd_SePlay( UG_BASE_SE_MOVE );
				trans_z+=(FX32_ONE*16);
				rect.GridLZ++;
				rect.GridRZ++;
			}else{
				edit = FALSE;
			}
			if (sys.trg & PAD_BUTTON_DECIDE){
				reput = TRUE;
			}else if(sys.trg & PAD_BUTTON_CANCEL){
				//�L�����Z��
///				OS_Printf("�Ĕz�u���L�����Z�����܂���\n");
				DispOffPanel(ebew->Panel);
				
				//���_�ł��Ă��邩������Ȃ�OBJ�̓_�ł��X�g�b�v
				StopBlink(fsys, &ebew->BlinkData);
				
				SetNextSeqCall(BASE_SEQ_MAIN_MENU, ebew);	//���C�����j���[
				return TRUE;
			}
		}//end if(!tp_touch)

		if (edit){
			if ( !CheckHitWall(&rect) ){
				BOOL hit;
				int list_idx;

				ebew->Panel->trans.x = trans_x;
				ebew->Panel->trans.z = trans_z;
				ebew->Panel->GridX = rect.GridLX;
				ebew->Panel->GridZ = rect.GridLZ;

				hit = CheckCollectGoods(ebew->Panel->GridX, ebew->Panel->GridZ, ebew->GoodsHitList, &list_idx);
				if (hit){
					int idx;
					idx = GetBlinkTarget( &ebew->BlinkData );
					if (ebew->GoodsHitList[list_idx].Data.ObjEntryIndex != idx){
						//���_�ł��Ă��邩������Ȃ�OBJ�̓_�ł��X�g�b�v
						StopBlink(fsys, &ebew->BlinkData);
						//�O��ƈႤ���̂Ƀq�b�g�����ꍇ�̓Z�b�g������
						SetBlinkTarget(	ebew->GoodsHitList[list_idx].Data.ObjEntryIndex,
										COLLECT_BLINK_TIME,
										&ebew->BlinkData	);
					}
				}else{
					StopBlink(fsys, &ebew->BlinkData);
					InitBlinkData(&ebew->BlinkData);
				}
			}
		}

		if (reput){	
			BOOL rc;
			int x,z;
			int index;
			GF_ASSERT(ebew->Panel->GridX<32&&"�O���b�h�l���s��");
			GF_ASSERT(ebew->Panel->GridZ<32&&"�O���b�h�l���s��");

			x = ebew->Panel->GridX;
			z = ebew->Panel->GridZ;
		
			//���̃`�F�b�N
			rc = CheckCollectGoods(x, z, ebew->GoodsHitList, &index);
			if (rc){
				if (index!=SECRETBASE_PC_INDEX_NO){	//�p�\�R������
					if (ebew->GoodsHitList[index].Data.No == GOODS_UG_IWA){	//�┻��
						//��Ȃ̂ŁA�ړ��s��
						//���b�Z�[�W�F������@���ǂ������邱�Ƃ́@�ł��܂���
						ebew->MesIndex = UgSecretBaseTalkStart(mes_uw_edit_17);
						ebew->MesWait = 0;
						ebew->SubSeq = REPUT_SEQ_COL_NG;
					}else{
						//�ҏW�o�b�t�@�Ƀf�[�^�R�s�[
						CopyEditDataFromList(index, ebew);
						SetGoodsOldPos(index,ebew);				//���݈ʒu�����ʒu�Ƃ��ĕۑ�
						//���̈ʒu�̏����N���A
						ClearGoodListByIndex(index, ebew->GoodsHitList);
						
						Snd_SePlay( UG_BASE_SE_PICK );	//�O�b�Y����������
						
///						OS_Printf("�Ĕz�u���[�h�Ɉڍs���܂�\n");
						DispOffPanel(ebew->Panel);
						SetNextSeqCall(BASE_SEQ_REPUT_SET_CONT, ebew);	//�Đݒu���[�h��
						return TRUE;
					}
				}else{
///					OS_Printf("�p�\�R���͑ΏۊO�ł�\n");
					//���b�Z�[�W�F�p�\�R���́@���ǂ��@�ł��܂���
					ebew->MesIndex = UgSecretBaseTalkStart(mes_uw_edit_24);
					ebew->MesWait = 0;
					ebew->SubSeq = REPUT_SEQ_COL_NG;
				}
			}else{
///				OS_Printf("��������܂���\n");
			}		
		}
		break;
	case REPUT_SEQ_COL_NG:
		//���b�Z�[�W�҂�
		if( GF_MSG_PrintEndCheck( ebew->MesIndex ) == 0 ){
			if ((ebew->MesWait++)>=MSG_WAIT){
				UgSecretBaseTalkEnd();
				ebew->SubSeq = REPUT_SEQ_MAIN;
			}
		}
		break;
	}	//end switch
	return FALSE;
}

//�Đݒu�R���g���[��
static BOOL ReputSetControl(GMEVENT_CONTROL * event)
{
	fx32 plus_x, plus_z;
	M3DO_PTR ptr;

	BOOL tp_touch;
	BOOL reput;
	
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	EVENT_BASE_EDIT_WORK * ebew = FieldEvent_GetSpecialWork(event);

	switch(ebew->SubSeq){
	case REPUTSET_SEQ_INIT:
		InitBlinkData(&ebew->BlinkData);
		SetBlinkTarget(ebew->EditGoodsData.ObjEntryIndex, PUT_BLINK_TIME, &ebew->BlinkData);
		ebew->SubSeq = REPUTSET_SEQ_MAIN;
		break;
	case REPUTSET_SEQ_MAIN:
		//�_�ŏ���
		BlinkTarget(fsys, &ebew->BlinkData);
		tp_touch = TpGoodsReputSetControl(ebew, fsys, &reput);

		if (!tp_touch){	//�^�b�`����Ă��Ȃ��ꍇ
			BOOL edit;
			RECT_DATA rect;
			edit = TRUE;
			rect = ebew->EditGoodsData.Rect;
			if (sys.repeat & PAD_KEY_LEFT){
				plus_x = -(FX32_ONE*16);
				plus_z = 0;
				rect.GridLX--;
				rect.GridRX--;
			}else if (sys.repeat & PAD_KEY_RIGHT){
				plus_x = (FX32_ONE*16);
				plus_z = 0;
				rect.GridLX++;
				rect.GridRX++;
			}else if (sys.repeat & PAD_KEY_UP){
				plus_x = 0;
				plus_z = -(FX32_ONE*16);
				rect.GridLZ--;
				rect.GridRZ--;
			}else if (sys.repeat & PAD_KEY_DOWN){
				plus_x = 0;
				plus_z = (FX32_ONE*16);
				rect.GridLZ++;
				rect.GridRZ++;
			}else{
				edit = FALSE;
			}

			if (edit != FALSE){
				if ( !CheckHitWall(&rect) ){
					VecFx32 vec;
					ebew->EditGoodsData.Rect = rect;
					ptr = M3DO_GetMap3DObjDataFromIndex(fsys->Map3DObjExp, ebew->EditGoodsData.ObjEntryIndex);
					vec = M3DO_GetGlobalVec(ptr);
					vec.x += (plus_x);
					vec.z += (plus_z);
					vec.y = FX32_ONE;
					M3DO_SetGlobalVec(ptr, &vec);
				}
			}

			if (sys.trg & PAD_BUTTON_DECIDE){
				reput = TRUE;
			}else if(sys.trg & PAD_BUTTON_CANCEL){
				//���̈ʒu�ɁA���X�g�o�^
				EntryGoodsListByIndex(&ebew->OldPosInfo.Data, ebew->OldPosInfo.TargetIndex, ebew->GoodsHitList);
				//�L�����Z�����ꂽ�̂Ō��̕\�����W�ɖ߂�
				PutGoodsOldPos(ebew);
		
///				OS_Printf("�L�����Z���B���̈ʒu�ɖ߂�\n");
				//�_�ł�����
				StopBlink(fsys, &ebew->BlinkData);
				
				//�Ĕz�u���[�h��
				SetNextSeqCall(BASE_SEQ_REPUT_CONT, ebew);
				return TRUE;
			}
		}//end if(!tp_touch)
	

		if (reput){
			BOOL rc;
			//�u���邩�`�F�b�N
			rc = CheckPutGoods(&ebew->EditGoodsData, ebew->GoodsHitList);
			if (rc){
				//���̈ʒu�ɁA���X�g�o�^
				EntryGoodsListByIndex(&ebew->EditGoodsData, ebew->OldPosInfo.TargetIndex, ebew->GoodsHitList);
///				OS_Printf("�u���܂���\n");

				Snd_SePlay( UG_BASE_SE_PUT );		//�O�b�Y�u����
#if 0			//<<���b�Z�[�W�͂���Ȃ��炵��2006.04.28
				UgSecretBaseTalkRegisterGoodsName(ebew->EditGoodsData.No);
				//���b�Z�[�W�F�`�@���@�����������I
				ebew->MesIndex = UgSecretBaseTalkStart(mes_uw_edit_12);
#endif				
				//�p�l���̈ړ�
				SetPanelPos(ebew->EditGoodsData.Rect.GridLX, ebew->EditGoodsData.Rect.GridLZ, ebew->Panel);
				//�_�ł�����
				StopBlink(fsys, &ebew->BlinkData);
				ebew->MesWait = 0;
				ebew->SubSeq = REPUTSET_SEQ_PUT_OK;
				break;
			}else{
				Snd_SePlay( UG_BASE_SE_PUT_NG );	//�O�b�Y�u���Ȃ���
				//���b�Z�[�W�F���́@�΂���ɂ́@�����܂���
				ebew->MesIndex = UgSecretBaseTalkStart(mes_uw_edit_13);
				ebew->MesWait = 0;
				ebew->SubSeq = REPUTSET_SEQ_PUT_NG;
			}
		}
		break;
	case REPUTSET_SEQ_PUT_NG:
		//���b�Z�[�W�҂�
		if( GF_MSG_PrintEndCheck( ebew->MesIndex ) == 0 ){
			if ((ebew->MesWait++)>=MSG_WAIT){
				UgSecretBaseTalkEnd();
				ebew->SubSeq = REPUTSET_SEQ_MAIN;
			}
		}
		break;
	case REPUTSET_SEQ_PUT_OK:
		if( GF_MSG_PrintEndCheck( ebew->MesIndex ) == 0 ){
			if ((ebew->MesWait++)>=MSG_WAIT){
				UgSecretBaseTalkEnd();
				//�Ĕz�u���[�h��
				SetNextSeqCall(BASE_SEQ_REPUT_CONT, ebew);
				return TRUE;
			}
		}
		break;
	}//end switch

	return FALSE;
}

//�u���邩�`�F�b�N
static BOOL CheckPutGoods(const GOODS_HIT_DAT *inData, const GOODS_HIT_LIST_ITEM *inList)
{
	int i;
	//���X�g�Əƍ�
	for (i=0;i<GOODS_HIT_LIST_MAX;i++){
		if (inList[i].Valid == TRUE){
///			OS_Printf("%d:�`�F�b�N�J�n\n",i);
			if ( CheckRectHit(&inList[i].Data.Rect,&inData->Rect) ){
				return FALSE;	//�Փ˂����̂ŕ��͒u���Ȃ�
			}
		}
	}

	//�p�\�R����O���u���Ȃ����Ƃɂ���
	{
		RECT_DATA paso_front_rect = {PASO_LX,PASO_LZ,PASO_RX,PASO_RZ};
		if ( CheckRectHit(&inData->Rect,&paso_front_rect) ){
			return FALSE;	//�Փ˂����̂ŕ��͒u���Ȃ�
		}
	}

	//�o�����u���Ȃ����Ƃɂ���
	{
		RECT_DATA exit_rect = {EXIT_LX,EXIT_LZ,EXIT_RX,EXIT_RZ};
		if ( CheckRectHit(&inData->Rect,&exit_rect) ){
			return FALSE;	//�Փ˂����̂ŕ��͒u���Ȃ�
		}
	}
	
	return TRUE;	//���u����
}

//�w����W�ɕ��̂����邩���`�F�b�N
static BOOL CheckCollectGoods(	const int inGridX, const int inGridZ,
								const GOODS_HIT_LIST_ITEM *inList,
								int *outIndex)
{
	int i;
	for (i=0;i<GOODS_HIT_LIST_MAX;i++){
		if (inList[i].Valid == TRUE){
			if ( CheckPointHit(&(inList[i].Data.Rect), inGridX, inGridZ) ){
				//�q�b�g�����̂œP���\
				(*outIndex) = i;
				return TRUE;
			}
		}
	}
	(*outIndex) = GOODS_HIT_LIST_MAX;
	return FALSE;	//�����Ȃ�
}

//�ǃ`�F�b�N
static BOOL CheckHitWall(const RECT_DATA *inData)
{
	
	if ( (BASE_LX<=inData->GridLX)&&(inData->GridRX<=BASE_RX) &&
			(BASE_LZ<=inData->GridLZ)&&(inData->GridRZ<=BASE_RZ) ){
		return FALSE;	//NOHIT
	}else{
		return TRUE;	//HIT
	};
}

//���X�g�ɃG���g��
static int EntryGoodsList(const GOODS_HIT_DAT *inData, GOODS_HIT_LIST_ITEM *ioList)
{
	int i;

	for(i=0;i<GOODS_HIT_LIST_MAX;i++){
		if (ioList[i].Valid == FALSE){
			//�G���g��
			ioList[i].Valid = TRUE;
			ioList[i].Data = (*inData);
///			OS_Printf("%d�ɃG���g��\n",i);
			return i;
		}
	}
	GF_ASSERT(0&&"�G���g�����I�[�o�[");
	return 0;
}

//���X�g�ɃG���g��(�ꏊ�w��)
static void EntryGoodsListByIndex(const GOODS_HIT_DAT *inData, const int inIndex, GOODS_HIT_LIST_ITEM *ioList)
{
	GF_ASSERT((inIndex<GOODS_HIT_LIST_MAX)&&"�C���f�b�N�X�I�[�o�[");
	GF_ASSERT((!ioList[inIndex].Valid)&&"�w��C���f�b�N�X�ɂ͂��łɓo�^����Ă��܂�");

	//�G���g��
	ioList[inIndex].Valid = TRUE;
	ioList[inIndex].Data = (*inData);
///	OS_Printf("%d�ɃG���g��\n",inIndex);
}

//�w��C���f�b�N�X�f�[�^�����X�g����폜
static void ClearGoodListByIndex(const int inIndex, GOODS_HIT_LIST_ITEM *outList)
{
	GF_ASSERT_MSG((inIndex<GOODS_HIT_LIST_MAX),"�C���f�b�N�X�I�[�o�[");
	GF_ASSERT_MSG((inIndex!=0),"�C���f�b�N�X0�̃p�\�R���͓P���ł��܂���");
	GF_ASSERT_MSG(outList[inIndex].Valid,"���łɖ����ƂȂ��Ă��܂�");
	{
		outList[inIndex].Data.ObjEntryIndex = 0;
		outList[inIndex].Data.Rect.GridLX = 0;
		outList[inIndex].Data.Rect.GridLZ = 0;
		outList[inIndex].Data.Rect.GridRX = 0;
		outList[inIndex].Data.Rect.GridRZ = 0;
		outList[inIndex].Data.No = 0;
		outList[inIndex].Valid = FALSE;
	}
}

//��`�����蔻��
static BOOL CheckRectHit(const RECT_DATA *inData1, const RECT_DATA *inData2)
{
	if ( (inData1->GridLX<=inData2->GridRX)&&(inData2->GridLX<=inData1->GridRX) &&
			(inData1->GridLZ<=inData2->GridRZ)&&(inData2->GridLZ<=inData1->GridRZ) ){
		return TRUE;	//HIT
	}else{
		return FALSE;	//NOHIT
	}	
}

//�w��_����`���ɂ��邩�𔻒�
static BOOL CheckPointHit(const RECT_DATA *inData, const int inX, const int inZ)
{
	if ( (inData->GridLX<=inX)&&(inX<=inData->GridRX) &&
			(inData->GridLZ<=inZ)&&(inZ<=inData->GridRZ) ){
		return TRUE;	//HIT
	}else{
		return FALSE;	//NOHIT
	}
}

//�Z�[�u�f�[�^����A�Ǘ����X�g���쐬����
static void MakeGoodsHitList(FIELDSYS_WORK *fsys, EVENT_BASE_EDIT_WORK *ebew, GOODS_HIT_LIST_ITEM *outList)
{
	int i;
	int goods_no;
	int x,z;
	SECRETBASEDATA *s_data;
	s_data = SaveData_GetSecretBaseData(fsys->savedata);
	ebew->GoodsCount = 0;
	ebew->RockCount = 0;
	//�⃊�~�b�g�Z�b�g
	ebew->RockLimit = SecretBaseData_GetPlaceRockLimit(s_data);
	//�O�b�Y���~�b�g�Z�b�g
	ebew->GoodsLimit = SecretBaseData_GetPlaceGoodsLimit(s_data);
	for(i=0;i<GOODS_HIT_LIST_MAX;i++){
		goods_no = SecretBaseData_GetGoodsType(s_data, i);
		if (goods_no != GOODS_INVALID){
			//��J�E���g
			if (goods_no == GOODS_UG_IWA){
				ebew->RockCount++;	//�␔�C���N�������g
			}else if( (goods_no != GOODS_UG_TABLE_L01)&&
						(goods_no != GOODS_UG_TABLE_L02)&&
						(goods_no != GOODS_UG_TABLE_L03)&&
						(goods_no != GOODS_UG_TABLE_L04)&&
						(goods_no != GOODS_UG_TABLE_L05)){
				ebew->GoodsCount++;	//�O�b�Y�̃C���N�������g
			}
			x = SecretBaseData_GetGoodsXPos(s_data, i);
			z = SecretBaseData_GetGoodsZPos(s_data, i);
			//�G���g��
///			OS_Printf("%d:�Z�[�u�f�[�^����O�b�Y�ԍ�%d���G���g��\n",i,goods_no);
///			OS_Printf("���W%d,%d\n",x,z);
			MakeGoodsHitData(i, goods_no, x, z, outList);
		}
	}
}

//�f�[�^�쐬
static void MakeGoodsHitData(	const int inIndex, const int inGoodsNo,
								const int inX, const int inZ,
								GOODS_HIT_LIST_ITEM *outList	)
{
	GOODS_HIT_DAT data;
	int w,d;
	
	data.ObjEntryIndex = 0;//��̏����ŁAOBJ�̃G���g���C���f�b�N�X���Z�b�g
	data.No = inGoodsNo;	//�O�b�Y�i���o�[
	data.Rect.GridLX = inX;
	data.Rect.GridLZ = inZ;
	//�O�b�Y�^�C�v���畝�A���s�����擾
	data.Width = GOODS_GetGoodsSizeX(inGoodsNo);
	data.Depth = GOODS_GetGoodsSizeZ(inGoodsNo);

	data.Rect.GridRX = inX+(data.Width-1);
	data.Rect.GridRZ = inZ+(data.Depth-1);

	outList[inIndex].Data = data;
	outList[inIndex].Valid = TRUE;	//�f�[�^��L��
}

//�f�[�^���X�g�����ƂɁA�}�b�v3DOBJ���쐬
static void MakeGoodsMap3DObj(FIELDSYS_WORK *fsys, GOODS_HIT_LIST_ITEM *ioList)
{
	int obj_id;
	int w,d;
	int i;
	VecFx32 trans;

	GOODS_HIT_DAT *data;

	//�n���}�b�v3DOBJ���N���A
	M3DO_CleanMap3DObjList(fsys->Map3DObjExp);
	
	for(i=0;i<GOODS_HIT_LIST_MAX;i++){
		if (!ioList[i].Valid){
			continue;
		}
		data = &ioList[i].Data;
		//OBJID���擾(�}�b�v���\�[�X�̃t�@�C���e�[�u���ƃO�b�Y�i���o�[����AOBJID���擾)
		obj_id = GetGoodsObjID(fsys, data->No);
		w = data->Width;
		d = data->Depth;
		
		//�`��ʒu���Z�o
		trans.x = (FX32_ONE*16)*(data->Rect.GridLX)+(FX32_ONE*8)*w;
		trans.z = (FX32_ONE*16)*(data->Rect.GridLZ)+(FX32_ONE*8)*d;
		trans.y = FX32_ONE/*0*/;
		data->ObjEntryIndex = M3DO_SetMap3DObjExp(	fsys->Map3DObjExp,
													fsys->MapResource,
													obj_id,			
													&trans, NULL,
													fsys->field_3d_anime);
	}
}

//�Z�[�u�ɏ���
static void WriteSaveData(FIELDSYS_WORK *fsys, const GOODS_HIT_LIST_ITEM *inList)
{
	int i;
	int goods_no;
	int x,z;
	
	SECRETBASEDATA *s_data;
	s_data = SaveData_GetSecretBaseData(fsys->savedata);
	
	for(i=0;i<GOODS_HIT_LIST_MAX;i++){
		if (inList[i].Valid == TRUE){
			goods_no = inList[i].Data.No;
			x = inList[i].Data.Rect.GridLX;
			z = inList[i].Data.Rect.GridLZ;
///			OS_Printf("�L���@%d:save_pos=%d,%d no=%d\n",i,x,z,goods_no);
		}else{
			goods_no = GOODS_INVALID;
			x = 0;
			z = 0;
///			OS_Printf("�����@%d:save_pos=%d,%d no=%d\n",i,x,z,goods_no);
		}
		SecretBaseData_SetGoodsPosition(s_data, i, goods_no, x, z);
	}
}

//OBJID�̎擾
static const int GetGoodsObjID(FIELDSYS_WORK *fsys, const int inGoodsNo)
{
	int obj_id;

	GF_ASSERT(inGoodsNo!=0&&"�i���o�[0�̃O�b�Y�͂���܂���");

	obj_id = MAPRES_GetObjIDFromModelFile(fsys->MapResource, inGoodsNo);
	/**
	M3DO_PTR ptr;
	ptr = M3DO_GetMap3DObjDataFromIndex(fsys->Map3DObjExp, inData->ObjEntryIndex);
	obj_id = M3DO_GetObjID(ptr);*/
	return obj_id;
}

//���̈ʒu�̋L��
static void SetGoodsOldPos(const int inIndex, EVENT_BASE_EDIT_WORK * ebew)
{
	M3DO_PTR ptr;
	GOODS_HIT_DAT *data;
	GF_ASSERT(ebew->GoodsHitList[inIndex].Valid&&"�f�[�^�͖�����Ԃł�");
	data = &(ebew->GoodsHitList[inIndex].Data);
	
	ptr = M3DO_GetMap3DObjDataFromIndex(ebew->fsys->Map3DObjExp, data->ObjEntryIndex);
	ebew->OldPosInfo.Trans = M3DO_GetGlobalVec(ptr);
	ebew->OldPosInfo.TargetIndex = inIndex;
	ebew->OldPosInfo.Data = (*data);
	
}
//���̈ʒu���W�ɕ���u��
static void PutGoodsOldPos(EVENT_BASE_EDIT_WORK * ebew)
{
	M3DO_PTR ptr;
	GOODS_HIT_DAT *data;
	int list_index;
	
	list_index = ebew->OldPosInfo.TargetIndex;
	GF_ASSERT(ebew->GoodsHitList[list_index].Valid&&"�f�[�^�͖�����Ԃł�");
	data = &(ebew->OldPosInfo.Data);

	ptr = M3DO_GetMap3DObjDataFromIndex(ebew->fsys->Map3DObjExp, data->ObjEntryIndex);
	M3DO_SetGlobalVec(ptr, &ebew->OldPosInfo.Trans);
}

static void SetNextSeqCall(const int inSeq, EVENT_BASE_EDIT_WORK * ebew)
{
	ebew->seq = inSeq;
	ebew->SubSeq = 0;
}

static void SetupPanel(UG_BASE_PANEL *outPanel)
{
	NNSG3dResMdl *resmodel;
	simple_3DModelSet(	HEAPID_FIELD,
						"data/ug_base_cur.nsbmd",
						&outPanel->renderobj,
						&resmodel,
						&outPanel->resfileheader);
	outPanel->trans.x = 0;
	outPanel->trans.y = 0;
	outPanel->trans.z = 0;
	outPanel->GridX = 0;
	outPanel->GridZ = 0;
	outPanel->DrawFlg = FALSE;
}

static void ReleasePanel(UG_BASE_PANEL *outPanel)
{
	sys_FreeMemoryEz(outPanel->resfileheader);
}

static void DispOnPanelFlgOnly(UG_BASE_PANEL *outPanel)
{
	outPanel->DrawFlg = TRUE;
}

static void SetPanelPos(const int inGridX, const int inGridZ, UG_BASE_PANEL *outPanel)
{
	outPanel->GridX = inGridX;
	outPanel->GridZ = inGridZ;
	outPanel->trans.x = (FX32_ONE*16)*(BASE_EDIT_GRID_OFS_X+inGridX)+((FX32_ONE*8));
	outPanel->trans.y = FX32_ONE;
	outPanel->trans.z = (FX32_ONE*16)*(BASE_EDIT_GRID_OFS_Z+inGridZ)+((FX32_ONE*8));
}

static void DispOffPanel(UG_BASE_PANEL *outPanel)
{
	outPanel->DrawFlg = FALSE;
}

static void GetTouchPos(const int inTpX, const int inTpY, UG_BASE_TP *outBaseTp)
{
	if (inTpX != 0xffff){
		outBaseTp->TpX = inTpX;
	}
	if (inTpY != 0xffff){
		outBaseTp->TpY = inTpY;
	}
}

static void TpUpdateGoodsPos(FIELDSYS_WORK * fsys, GOODS_HIT_DAT *ioData, UG_BASE_TP *outBaseTp)
{
	RECT_DATA rect;
	VecFx32 vec;
	int grid_x,grid_z;
	int w,d;
	TP_TO_3D_PTR tp_to_3d_ptr;
	tp_to_3d_ptr = fsys->TpTo3DPtr;
	
	//�^�b�`���W�擾
	GetTouchPos(sys.tp_x, sys.tp_y, outBaseTp);
	//�^�b�`�O���b�h�擾
	vec = FTouch_CalcTpXYTo3D(outBaseTp->TpX, outBaseTp->TpY, tp_to_3d_ptr);
	grid_x = vec.x/(FX32_ONE*16);
	grid_z = vec.z/(FX32_ONE*16);

	//�T�C�Y�擾
	w = ioData->Width;
	d = ioData->Depth;

	rect.GridLX = grid_x%32;
	rect.GridLZ = grid_z%32;
	rect.GridRX = rect.GridLX+(w-1);
	rect.GridRZ = rect.GridLZ+(d-1);

	//��n���Ȃ�΁A�ړ��\
	if ( !CheckHitWall(&rect) ){
		ioData->Rect = rect;
/**
	ioData->Rect.GridLX = grid_x%32;
	ioData->Rect.GridLZ = grid_z%32;
	ioData->Rect.GridRX = ioData->Rect.GridLX+(w-1);
	ioData->Rect.GridRZ = ioData->Rect.GridLZ+(d-1);
*/
		vec.x = grid_x*(FX32_ONE*16);
		vec.z = grid_z*(FX32_ONE*16);
		//���̂̃T�C�Y�ʂɃI�t�Z�b�g�v�Z
		vec.x += (FX32_ONE*8)*w;
		vec.z += (FX32_ONE*8)*d;
		vec.y = FX32_ONE;
		{
			M3DO_PTR ptr;
			ptr = M3DO_GetMap3DObjDataFromIndex(fsys->Map3DObjExp, ioData->ObjEntryIndex);
			M3DO_SetGlobalVec(ptr, &vec);
		}
	}
}

static void TpUpdatePanelPos(FIELDSYS_WORK * fsys, UG_BASE_TP *outBaseTp, UG_BASE_PANEL *outPanel)
{
	RECT_DATA rect;
	VecFx32 vec;
	int grid_x,grid_z;
	
	TP_TO_3D_PTR tp_to_3d_ptr;
	tp_to_3d_ptr = fsys->TpTo3DPtr;
	
	//�^�b�`���W�擾
	GetTouchPos(sys.tp_x, sys.tp_y, outBaseTp);
	//�^�b�`�O���b�h�擾
	vec = FTouch_CalcTpXYTo3D(outBaseTp->TpX, outBaseTp->TpY, tp_to_3d_ptr);
	grid_x = vec.x/(FX32_ONE*16);
	grid_z = vec.z/(FX32_ONE*16);

	rect.GridLX = grid_x%32;
	rect.GridLZ = grid_z%32;
	rect.GridRX = rect.GridLX;
	rect.GridRZ = rect.GridLZ;

	//��n���Ȃ�΁A�ړ��\
	if ( !CheckHitWall(&rect) ){
		vec.x = grid_x*(FX32_ONE*16)+(FX32_ONE*8);
		vec.z = grid_z*(FX32_ONE*16)+(FX32_ONE*8);
		vec.y = FX32_ONE;

		outPanel->trans = vec;
		outPanel->GridX = grid_x;
		outPanel->GridZ = grid_z;
	}
}

//�ݒu���̃^�b�`�p�l������
static BOOL TpGoodsPutControl(EVENT_BASE_EDIT_WORK * ebew, FIELDSYS_WORK * fsys, BOOL *outPut)
{
	VecFx32 vec;
	BOOL rc;	//�^�b�`�p�l���ɐG���Ă��邩��Ԃ�
	rc = FALSE;
	*outPut = FALSE;
	
	if ( sys.tp_trg ){	//�g���K�[
		if (!sys.cont){		//�L�[���S��������Ă��Ȃ����
			//�g���K�[�t���O�I��
			ebew->BaseTp.TrgFlg = TRUE;

			TpUpdateGoodsPos(fsys, &(ebew->EditGoodsData), &ebew->BaseTp);
		
		}//end if
		rc = TRUE;
	}else if(sys.tp_cont){	//�x�^
		if (ebew->BaseTp.TrgFlg){
			TpUpdateGoodsPos(fsys, &(ebew->EditGoodsData), &ebew->BaseTp);
			
		}
		rc = TRUE;
	}else{
		if (ebew->BaseTp.TrgFlg){
			ebew->BaseTp.TrgFlg = FALSE;
			//�������Ƃ��ɐݒu
			*outPut = TRUE;	//�u��
		}
	}
	return rc;
}

//������̃^�b�`�p�l������
static BOOL TpGoodsCollectControl(EVENT_BASE_EDIT_WORK * ebew, FIELDSYS_WORK * fsys, BOOL *outCollect)
{
	VecFx32 vec;
	BOOL rc;	//�^�b�`�p�l���ɐG���Ă��邩��Ԃ�
	rc = FALSE;
	*outCollect = FALSE;
	
	if ( sys.tp_trg ){	//�g���K�[
		if (!sys.cont){		//�L�[���S��������Ă��Ȃ����
			//�g���K�[�t���O�I��
			ebew->BaseTp.TrgFlg = TRUE;

			TpUpdatePanelPos(fsys, &ebew->BaseTp, ebew->Panel);
		
		}//end if
		rc = TRUE;
	}else if(sys.tp_cont){	//�x�^
		if (ebew->BaseTp.TrgFlg){
			TpUpdatePanelPos(fsys, &ebew->BaseTp, ebew->Panel);
			
		}
		rc = TRUE;
	}else{
		if (ebew->BaseTp.TrgFlg){
			ebew->BaseTp.TrgFlg = FALSE;
			//�������Ƃ��ɉ��
			*outCollect = TRUE;	//���
		}
	}
	return rc;
}

//�Ĕz�u���i�^�[�Q�b�g�w�莞�j�̃^�b�`�p�l������
static BOOL TpGoodsReputControl(EVENT_BASE_EDIT_WORK * ebew, FIELDSYS_WORK * fsys, BOOL *outReput)
{
	VecFx32 vec;
	BOOL rc;	//�^�b�`�p�l���ɐG���Ă��邩��Ԃ�
	rc = FALSE;
	*outReput = FALSE;
	
	if ( sys.tp_trg ){	//�g���K�[
		if (!sys.cont){		//�L�[���S��������Ă��Ȃ����
			//�g���K�[�t���O�I��
			ebew->BaseTp.TrgFlg = TRUE;
			//�������Ƃ��Ɍ���
			*outReput = TRUE;	//�^�[�Q�b�g����
			TpUpdatePanelPos(fsys, &ebew->BaseTp, ebew->Panel);
		}//end if
		rc = TRUE;
	}else{
		ebew->BaseTp.TrgFlg = FALSE;
	}
			
	return rc;
}

//�Ĕz�u���i�ݒu���j�̃^�b�`�p�l������
static BOOL TpGoodsReputSetControl(EVENT_BASE_EDIT_WORK * ebew, FIELDSYS_WORK * fsys, BOOL *outReput)
{
	VecFx32 vec;
	BOOL rc;	//�^�b�`�p�l���ɐG���Ă��邩��Ԃ�
	rc = FALSE;
	*outReput = FALSE;
	
	if ( sys.tp_trg ){	//�g���K�[
		if (!sys.cont){		//�L�[���S��������Ă��Ȃ����
			//�g���K�[�t���O�I��
			ebew->BaseTp.TrgFlg = TRUE;

			TpUpdateGoodsPos(fsys, &(ebew->EditGoodsData), &ebew->BaseTp);
		
		}//end if
		rc = TRUE;
	}else if(sys.tp_cont){	//�x�^
		if (ebew->BaseTp.TrgFlg){
			TpUpdateGoodsPos(fsys, &(ebew->EditGoodsData), &ebew->BaseTp);			
		}
		rc = TRUE;
	}else{
		if (ebew->BaseTp.TrgFlg){
			ebew->BaseTp.TrgFlg = FALSE;
			//�������Ƃ��ɐݒu
			*outReput = TRUE;	//�u��
		}
	}
	return rc;
}

static void InitBlinkData(BLINK_DATA *outBlinkData)
{
	outBlinkData->Count = 0;
	outBlinkData->CountMax = 0;
	outBlinkData->TargetIndex = 0xffff;
	outBlinkData->Vanish = FALSE;
	outBlinkData->Valid = FALSE;
}

static void SetBlinkTarget(const int inTarget, const int inCountMax, BLINK_DATA *outBlinkData)
{
	outBlinkData->Count = 0;
	outBlinkData->CountMax = inCountMax;
	outBlinkData->TargetIndex = inTarget;
	outBlinkData->Vanish = FALSE;
	outBlinkData->Valid = TRUE;
}

static void BlinkTarget(FIELDSYS_WORK *fsys, BLINK_DATA *ioBlinkData)
{
	M3DO_PTR ptr;
	if (!ioBlinkData->Valid){
		return;
	}
	//�����J�E���^�A�b�v
	ioBlinkData->Count++;
	if (ioBlinkData->Count >= ioBlinkData->CountMax){
		ioBlinkData->Count = 0;
		ioBlinkData->Vanish = (ioBlinkData->Vanish+1)%2;
		ptr = M3DO_GetMap3DObjDataFromIndex(fsys->Map3DObjExp, ioBlinkData->TargetIndex);
		//�o�j�b�V���t���b�O�Z�b�g
		M3DO_SetVanish(ptr, ioBlinkData->Vanish);
	}
}

static void StopBlink(FIELDSYS_WORK *fsys, BLINK_DATA *inBlinkData)
{
	M3DO_PTR ptr;
	if (!inBlinkData->Valid){
		return;
	}
	ptr = M3DO_GetMap3DObjDataFromIndex(fsys->Map3DObjExp, inBlinkData->TargetIndex);
	//�o�j�b�V���t���b�O���Ƃ�
	M3DO_SetVanish(ptr, FALSE);
}

static const int GetBlinkTarget(BLINK_DATA *inBlinkData)
{
	return inBlinkData->TargetIndex;
}

//�O�b�Y���X�g�C�x���g
static BOOL GoodsListEvent(GMEVENT_CONTROL * event)
{
	BOOL rc;
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	EVENT_BASE_EDIT_WORK * ebew = FieldEvent_GetSpecialWork(event);

	//�G�f�B�b�g���C�����j���[
	rc = BMENU_EditGoodsListControl(ebew->GoodsList);
	
	return FALSE;
}

static void InitBasePanel(FLDMAPFUNC_WORK * fwk, FIELDSYS_WORK * fsys, void * work)
{
	UG_BASE_PANEL *panel = (UG_BASE_PANEL*)(work);
	//�p�l���o�^
	SetupPanel(panel);
}

static void BasePanelDummy(FLDMAPFUNC_WORK * fwk, FIELDSYS_WORK * fsys, void * work)
{
	;
}

static void EndBasePanel(FLDMAPFUNC_WORK * fwk, FIELDSYS_WORK * fsys, void * work)
{
	UG_BASE_PANEL *panel = (UG_BASE_PANEL*)(work);
	//�p�l���폜
	ReleasePanel(panel);
}

static void DrawBasePanel(FLDMAPFUNC_WORK * fwk, FIELDSYS_WORK * fsys, void * work)
{
	UG_BASE_PANEL *panel = (UG_BASE_PANEL*)(work);	
	if (!(panel->DrawFlg)){
		return ;
	}
	{
		MtxFx33 rotate_tmp = {FX32_ONE,0,0,0,FX32_ONE,0,0,0,FX32_ONE};
		VecFx32 scale = {FX32_ONE,FX32_ONE,FX32_ONE};
		simple_3DModelDraw(	&panel->renderobj,
							&panel->trans,
							&rotate_tmp,
							&scale);
	}
}
