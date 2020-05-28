//=============================================================================
/**
 * @file	honey_tree_enc.c
 * @bfief	���h��G���J�E���g
 * @author	Nozomu Saito
 *
 *
 */
//=============================================================================
#include "common.h"
#include "system/arc_tool.h"
#include "honey_tree_enc.h"
#include "map_tool.h"
#include "player.h"
#include "fieldsys.h"
#include "..\fielddata\script\common_scr_def.h"		//for SCRID_HONEY_TREE
#include "honey_tree_def.h"
#include "..\fielddata\maptable\zone_id.h"

#include "../fielddata/build_model/build_model_id.h"

#include "savedata/encount.h"
#include "arc/encdata_ex.naix"

#define START_TIME	(24*60)		//����h��������̎��� 24��60��

#define ENC_START_TIME	(18*60)	//�G���J�E���g�\�Ȏ��ԁ@18��60��

typedef enum{
	TH_ENC_TBL_NORM,
	TH_ENC_TBL_RARE,
	TH_ENC_TBL_G_RARE,
}HT_ENC_TBL;

typedef enum{
	SWAY_LV_NONE,		//�h��Ȃ�
	SWAY_LV_NORMAL,		//�ʏ�h��
	SWAY_LV_GRATE,		//�������h���
	SWAY_LV_G_GRATE,	//���̂����h���
}SWAY_LV;

enum{
	HTE_NONE,
	HTE_NORMAL,
	HTE_RARE,
	HTE_GRATE_RARE,
};

typedef struct HONEY_DATA_ANM_tag
{
	u8 AnimeNo;
	BOOL AnimeFlg;
}HONEY_DATA_ANM;

typedef struct HONEY_TREE_DAT_tag
{
	HONEY_DATA_ANM HoneyData[HONEY_TREE_MAX];
	int ZoneList[HONEY_TREE_MAX];
}HONEY_TREE_DAT;

//�h���؂̃]�[�����X�g(�]�[�����܂������Ƃ��ɎQ�Ƃ���̂ŁA�A�[�J�C�u�ɂ��Ȃ��ŁA�Œ�Ŏ����܂�)
static const int HoneyTreeZoneList[HONEY_TREE_MAX] = {
	ZONE_ID_R205A,
	ZONE_ID_R205B,
	ZONE_ID_R206,
	ZONE_ID_R207,
	ZONE_ID_R208,
	ZONE_ID_R209,
	ZONE_ID_R210A,
	ZONE_ID_R210B,
	ZONE_ID_R211B,
	ZONE_ID_R212A,
	ZONE_ID_R212B,
	ZONE_ID_R213,
	ZONE_ID_R214,
	ZONE_ID_R215,
	ZONE_ID_R218,
	ZONE_ID_R221,
	ZONE_ID_R222,
	ZONE_ID_D02,
	ZONE_ID_D03,
	ZONE_ID_D04,
	ZONE_ID_D13R0101,
};

//�G���J�E���g�|�P�����A�[�J�C�u�C���f�b�N�X�e�[�u��
//�_�C��
static const int HoneyEncArcTbl_Dia[] = {
	NARC_encdata_ex_honey_dia_nrm_bin,		//�ʏ�
	NARC_encdata_ex_honey_dia_rare_bin,		//���A
	NARC_encdata_ex_honey_dia_s_rare_bin,	//�����A
};

//�p�[��
static const int HoneyEncArcTbl_Perl[] = {
	NARC_encdata_ex_honey_perl_nrm_bin,		//�ʏ�
	NARC_encdata_ex_honey_perl_rare_bin,		//���A
	NARC_encdata_ex_honey_perl_s_rare_bin,	//�����A
};

static void SetRareLv(const BOOL inHit, u8 *outRare);
static void SetHoneyTreeTblMonsNo(u8 *outTblMonsNo);
static void SetHoneyTreeAnimation(FIELDSYS_WORK *fsys, M3DOL_PTR inMap3DObjList, const int inBlockIdx);
static u8 GetTreeNoFromZoneID(const int inZoneID);
static const int SetHoneyTreeEncTbl(const u8 inRareLv);
static const int SetSwayLv(const u8 inRareLv);
static const BOOL GetAnimeNoForHoneyTree(const int inSwayLv, u8 *outAnimeNo);
static const BOOL CheckHoneyTreeEncTime(const int inTime);
static BOOL CheckRareFlg(const u32 inTrainerID, const u8 inIndex);

//==============================================================================
/**
 * ���؃f�[�^�̊m�ۂƏ�����
 *
 * 
 * @retval	HTD_PTR			���؃f�[�^�|�C���^		
 * 
 */
//==============================================================================
HTD_PTR HTE_AllocHoneyTreeDat(void)
{
	u8 i;
	HTD_PTR htd_p;
	htd_p = sys_AllocMemory(HEAPID_FIELD, sizeof(HONEY_TREE_DAT));
	for(i=0;i<HONEY_TREE_MAX;i++){
		htd_p->HoneyData[i].AnimeNo = 0;
		htd_p->HoneyData[i].AnimeFlg = FALSE;
	}
	return htd_p;
}

//==============================================================================
/**
 * �������
 *
 * @param	outHoneyTree	���؃f�[�^�|�C���^	
 * 
 * @retval  none		
 */
//==============================================================================
void HTE_FreeHoneyTreeDat(HTD_PTR *outHoneyTree)
{
	sys_FreeMemoryEz(*outHoneyTree);
	*outHoneyTree = NULL;
}

//==============================================================================
/**
 * ���h��؂̐ڐG�`�F�b�N
 *
 * @param	fsys		�t�B�[���h�V�X�e���|�C���^
 * @param	outScrID	�X�N���v�gID�i�[�A�h���X
 *
 * @return	BOOL	TRUE:HIT�@FALSE:NO HIT
 */
//==============================================================================
BOOL HTE_CheckHoneyTree(FIELDSYS_WORK *fsys, int *outScrID)
{
	TARGET_RECT rect;
	int x,z;
	BOOL rc;
	int dir;

	*outScrID = SCRID_HONEY_TREE;
	//���@���W�擾(�O���b�h)
	x = Player_NowGPosXGet( fsys->player );
	z = Player_NowGPosZGet( fsys->player );
	
	//���@�����擾
	dir = Player_DirGet( fsys->player );
	if (dir == DIR_UP){
		//���@�����̑O��1�O���b�h�̋�`���쐬
		MPTL_MakeTargetRect( x, z, 0, -1, 1, 1, &rect);

		rc = MPTL_CheckMap3DObjInRect(	fsys,
										BMID_TREEEFF,			//�h����
										&rect,
										NULL);
	}else{
		rc = FALSE;
	}
	return rc;
}

//==============================================================================
/**
 * ���݂���]�[���̖��h��؂̃X�e�[�g�擾
 *
 * @param	fsys		�t�B�[���h�V�X�e���|�C���^
 *
 * @return	u16			�؂̃X�e�[�g
 */
//==============================================================================
u16 HTE_GetNowLocHoneyTreeState(FIELDSYS_WORK *fsys)
{
	u8 tree_no;
	HT_PTR ptr;
	HONEY_DATA *data;
	//���݂̃]�[��ID���擾
	tree_no = GetTreeNoFromZoneID(fsys->location->zone_id);
	GF_ASSERT(tree_no!=HONEY_TREE_MAX&&"���h��؂��o�^����Ă��܂���" );

	ptr = EncDataSave_GetHoneyTree(EncDataSave_GetSaveDataPtr(fsys->savedata));
///	ptr = HTSave_GetHoneyTree(fsys->savedata);
	data = HTSave_GetHoneyDataPtr(tree_no, ptr);
	if ( CheckHoneyTreeEncTime(data->Time) ){
		return HONEY_SPREAD_ENCOUNT;//�G���J�E���g��
	}else{
		if (data->Time != 0){
			//����h���Ď��Ԍo�߂��J�n����Ă���ꍇ
			return HONEY_SPREAD_ALREADY;	//���h��i���łɓh���Ă����ԁj
		}else{
			return HONEY_SPREAD_OK;	//���h���
		}
	}
}

//==============================================================================
/**
 * ���݂���]�[���̖��h��؂̃Z�b�g�A�b�v
 *
 * @param	fsys		�t�B�[���h�V�X�e���|�C���^
 *
 * @return	none
 */
//==============================================================================
void HTE_SetupNowLocHoneyTree(FIELDSYS_WORK *fsys)
{
	u8 tree_no;
	HT_PTR ptr;
	HONEY_DATA *data;
	BOOL rare_flg;
	//���݂̃]�[��ID���擾
	tree_no = GetTreeNoFromZoneID(fsys->location->zone_id);
	GF_ASSERT(tree_no!=HONEY_TREE_MAX&&"���h��؂��o�^����Ă��܂���" );
	
	ptr = EncDataSave_GetHoneyTree(EncDataSave_GetSaveDataPtr(fsys->savedata));
	data = HTSave_GetHoneyDataPtr(tree_no, ptr);
	
	data->Time = START_TIME;
	{
		MYSTATUS *my_st = SaveData_GetMyStatus(fsys->savedata);
		//�g���[�i�[ID����A������ԍ�������
		rare_flg = CheckRareFlg(MyStatus_GetID(my_st), tree_no);
	}
	//�O��̖؂Ɣ�r�B�����؂Ȃ�A�O��̃|�P�����Ƃ̃G���J�E���g���������Ȃ�>�e�[�u���̂ݓ����ɕύX 20060619
	if (HTSave_GetBeforeTreeNo(ptr) == tree_no){
		if ( (gf_p_rand(100) ) <90){	//�����|�P�����ƃG���J�E���g(9����œ���)
			SetHoneyTreeTblMonsNo(&data->TblMonsNo);
			//�؂̗h���������
			data->SwayLv = SetSwayLv(data->RareLv);
			return;
		}
	}
	{	//�Ē��I
		SetRareLv(rare_flg, &data->RareLv);
		//�n�Y���ȊO�Ȃ�
		if (data->RareLv != HTE_NONE){
			SetHoneyTreeTblMonsNo(&data->TblMonsNo);
			//�e�[�u������
			data->TblNo = SetHoneyTreeEncTbl( data->RareLv );
		}else{	//�n�Y���̂Ƃ��́A�e�[�u�����m�[�}���ɂ���
			data->TblNo = TH_ENC_TBL_NORM;
			data->TblMonsNo = 0;
			//�n�Y���Ȃ̂ŁA���Ԃ�������
			data->Time = 0;
		}
		//�؂̗h���������
		data->SwayLv = SetSwayLv(data->RareLv);
	}
	//�؂̔ԍ����L��
	HTSave_SetBeforeTreeNo(tree_no, ptr);
}

//==============================================================================
/**
 * ���h��؂̐퓬�㏈��
 *
 * @param	fsys		�t�B�[���h�V�X�e���|�C���^
 *
 * @return	none
 */
//==============================================================================
void HTE_SetHoneyTreeInfoAfterBtl(FIELDSYS_WORK *fsys)
{
	u8 tree_no;
	
	tree_no = GetTreeNoFromZoneID(fsys->location->zone_id);
	GF_ASSERT(tree_no!=HONEY_TREE_MAX&&"���h��؂��o�^����Ă��܂���" );
	//�A�j���X�g�b�v
	if (fsys->HoneyTreePtr->HoneyData[tree_no].AnimeFlg){
		u8 idx;
		M3DO_PTR obj_ptr;
		M3DOL_PTR obj_list;
		NNSG3dRenderObj *render_obj;
		//���[�J���C���f�b�N�X���擾
		idx = GetNowLocalIndex(fsys->map_cont_dat);
		//�n�a�i���X�g���擾
		Get3DObjListFromLocalIdx(idx, fsys->map_cont_dat, &obj_list);
		obj_ptr = M3DO_GetMap3DObjDataFromID(obj_list, BMID_TREEEFF);
		render_obj = M3DO_GetRenderObj(obj_ptr);
		if (obj_ptr != NULL){
			F3DA_RemoveFld3DAnime(	fsys->field_3d_anime,
									render_obj,
									BMID_TREEEFF,
									fsys->HoneyTreePtr->HoneyData[tree_no].AnimeNo);
		}
		fsys->HoneyTreePtr->HoneyData[tree_no].AnimeFlg = FALSE;
///		OS_Printf("�h�ꑐ�A�j���X�g�b�v\n");
	}
	//�����X�^�[�e�[�u���ԍ��͏����Ȃ�����!!
}

//==============================================================================
/**
 * ���h��؂̃��A�x������
 *
 * @param	inHit		������t���O
 * @param	outRare		���A�x���i�[����o�b�t�@		
 * 
 * @return	none
 */
//==============================================================================
static void SetRareLv(const BOOL inHit, u8 *outRare)
{
	int rand;
	rand = gf_p_rand(100);
	if (inHit){
		if(rand<1){			//1%
			*outRare = HTE_GRATE_RARE;	//�����A
		}else if(rand<10){	//9%
			*outRare = HTE_NONE;		//�n�Y��
		}else if(rand<30){	//20%
			*outRare = HTE_NORMAL;	//�ʏ�
		}else{				//70%
			*outRare = HTE_RARE;	//���A
		}
	}else{
		if(rand<10){	//10%
			*outRare = HTE_NONE;		//�n�Y��
		}else if(rand<30){	//20%
			*outRare = HTE_RARE;	//���A
		}else{				//70%
			*outRare = HTE_NORMAL;	//�ʏ�
		}
	}
}

//==============================================================================
/**
 * ���h��؂̃G���J�E���g�����X�^�[�e�[�u���i���o�[������
 *
 * @param	outTblMonsNo		�����X�^�[�e�[�u���i���o�[���i�[����o�b�t�@
 *
 * @return	none
 */
//==============================================================================
static void SetHoneyTreeTblMonsNo(u8 *outTblMonsNo)
{
	int rand;
	rand = gf_p_rand(100);
	if(rand<5){			//5%
		*outTblMonsNo = 5;
	}else if(rand<10){	//5%
		*outTblMonsNo = 4;
	}else if(rand<20){	//10%
		*outTblMonsNo = 3;
	}else if(rand<40){	//20%
		*outTblMonsNo = 2;
	}else if(rand<60){	//20%
		*outTblMonsNo = 1;
	}else{				//40%
		*outTblMonsNo = 0;
	}
}

//==============================================================================
/**
 * ���h��G���J�E���g�e�[�u������
 *
 * @param	inRareLv		���A�x
 *
 * @return	int				�e�[�u���ԍ�
 */
//==============================================================================
static const int SetHoneyTreeEncTbl(const u8 inRareLv)
{
	int tbl_no;
	if (inRareLv == HTE_GRATE_RARE){	//�����A
		tbl_no = TH_ENC_TBL_G_RARE;
	}else if(inRareLv == HTE_RARE){		//���A
		tbl_no = TH_ENC_TBL_RARE;
	}else{								//�m�[�}��
		tbl_no = TH_ENC_TBL_NORM;
	}
	return tbl_no;
}

//==============================================================================
/**
 * �h�����Z�b�g
 *
 * @param	inRareLv		���A�x
 *
 * @return	int				�h��
 */
//==============================================================================
static const int SetSwayLv(const u8 inRareLv)
{
	int sway_lv;
	int rand;
	rand = gf_p_rand(100);
	
	if (inRareLv == HTE_GRATE_RARE){	//�����A
		if (rand<5){		//5%
			sway_lv = SWAY_LV_GRATE;
		}else if(rand<6){	//1%
			sway_lv = SWAY_LV_NORMAL;
		}else if(rand<7){	//1%
			sway_lv = SWAY_LV_NONE;
		}else{				//93%
			sway_lv = SWAY_LV_G_GRATE;
		}
	}else if(inRareLv == HTE_RARE){		//���A
		if (rand<75){		//75%
			sway_lv = SWAY_LV_GRATE;
		}else if(rand<95){	//20%
			sway_lv = SWAY_LV_NORMAL;
		}else if(rand<96){	//1%
			sway_lv = SWAY_LV_NONE;
		}else{				//4%
			sway_lv = SWAY_LV_G_GRATE;
		}
	}else if(inRareLv == HTE_NORMAL){	//�m�[�}��
		if (rand<19){		//19%
			sway_lv = SWAY_LV_GRATE;
		}else if(rand<79){	//60%
			sway_lv = SWAY_LV_NORMAL;
		}else if(rand<99){	//20%
			sway_lv = SWAY_LV_NONE;
		}else{				//1%
			sway_lv = SWAY_LV_G_GRATE;
		}
	}else{								//�n�Y��
		if (rand<1){		//1%
			sway_lv = SWAY_LV_GRATE;
		}else if(rand<19){	//18%
			sway_lv = SWAY_LV_NORMAL;
		}else if(rand<99){	//80%
			sway_lv = SWAY_LV_NONE;
		}else{				//1%
			sway_lv = SWAY_LV_G_GRATE;
		}
	}
	return sway_lv;
}

//==============================================================================
/**
 * �h��A�j���i���o�[�̃Z�b�g
 * �A�j���i���o�[�́Afield_3d_anime.c���̃A�j���e�[�u���Ɉˑ����܂�
 *
 * @param	inRareLv		�h��
 * @oaram	outAnimeNo		�A�j���i���o�[�@0�F�m�[�}���@1�������h���@2�F���̂����h���
 *
 * @return	BOOL			TRUE�F�A�j������	FALSE�F�A�j�����Ȃ�
 */
//==============================================================================
static const BOOL GetAnimeNoForHoneyTree(const int inSwayLv, u8 *outAnimeNo)
{
	u8 anime_no;	//�A�j���i���o�[
	BOOL rc;
	rc = TRUE;
	if (inSwayLv == SWAY_LV_G_GRATE){
		*outAnimeNo = 2;
	}else if (inSwayLv == SWAY_LV_GRATE){
		*outAnimeNo = 1;
	}else if (inSwayLv == SWAY_LV_NORMAL){
		*outAnimeNo = 0;
	}else{
		rc = FALSE;
	}
	return rc;
}

//==============================================================================
/**
 * ���h��؂̃A�j���[�V�����Z�b�g���C��
 *
 * @param	fsys			�t�B�[���h�V�X�e���|�C���^
 * @param	inMap3DObjList	�}�b�v3DOBJ���X�g
 * @param	inBlockIdx		�u���b�N�C���f�b�N�X
 *
 * @return	none
 */
//==============================================================================
static void SetHoneyTreeAnimation(FIELDSYS_WORK *fsys, M3DOL_PTR inMap3DObjList, const int inBlockIdx)
{
	u16 zone_id;
	u8 tree_no;
	
	//�u���b�N�̃]�[��ID���擾
	zone_id = World_GetZoneIDFromBlockIdx(fsys->World, inBlockIdx);
	//�擾�����]�[���h�c�͖��h�肷��ꏊ���𒲂ׂ�
	tree_no = GetTreeNoFromZoneID(zone_id);

	if (tree_no != HONEY_TREE_MAX){
		HT_PTR ptr;
		HONEY_DATA *data;
		M3DO_PTR obj_ptr;

		ptr = EncDataSave_GetHoneyTree(EncDataSave_GetSaveDataPtr(fsys->savedata));
///		ptr = HTSave_GetHoneyTree(fsys->savedata);
		data = HTSave_GetHoneyDataPtr(tree_no, ptr);	
		
		//���h�肷��ꏊ�̏ꍇ�A���̏ꏊ�́A���h��؂̏󋵂��擾
		if ( CheckHoneyTreeEncTime(data->Time) ){
			BOOL rc;
			u8 anime_no;
			//�����𕪊�
			rc = GetAnimeNoForHoneyTree(data->SwayLv, &anime_no);
			
			if(!rc){
				return;
			}
			
			//�A�j���[�V�����Z�b�g�i�A�j�����̂��̂́A�u���b�N�A�E�g���ɍς܂��Ă����j
			obj_ptr = M3DO_GetMap3DObjDataFromID(inMap3DObjList, BMID_TREEEFF);
			if (obj_ptr != NULL){
				NNSG3dRenderObj *render_obj;
				render_obj = M3DO_GetRenderObj(obj_ptr);
				//���łɃA�j�����Ă邩������Ȃ��̂ŁA�����ŁA�A�j�����I�t�ɂ���
				F3DA_RemoveFld3DAnime(	fsys->field_3d_anime,
										render_obj,
										BMID_TREEEFF,
										fsys->HoneyTreePtr->HoneyData[tree_no].AnimeNo);

				fsys->HoneyTreePtr->HoneyData[tree_no].AnimeNo = anime_no;
				fsys->HoneyTreePtr->HoneyData[tree_no].AnimeFlg = rc;
				
				F3DA_SetFld3DAnime(	BMID_TREEEFF, anime_no, TRUE,
									render_obj,
									fsys->field_3d_anime	);
			}
		}
	}
}

//==============================================================================
/**
 * �]�[��ID���疨�h��؂̃i���o�[���擾
 *
 * @param	inZoneID		�]�[��ID
 *
 * @return	u8				�؃i���o�[
 */
//==============================================================================
static u8 GetTreeNoFromZoneID(const int inZoneID)
{
	u8 i;
	for(i=0;i<HONEY_TREE_MAX;i++){
		if (inZoneID == HoneyTreeZoneList[i]){
			return i;
		}
	}
	return i;
}

//==============================================================================
/**
 * �G���J�E���g�ł��鎞�Ԃ����`�F�b�N
 *
 * @param	inTime		����
 *
 * @return  BOOL	TRUE:�G���J�E���g��		FALSE�F�G���J�E���g�s��
 */
//==============================================================================
static const BOOL CheckHoneyTreeEncTime(const int inTime)
{
///	OS_Printf("time%d\n",inTime);
	if ( (0<inTime)&&(inTime<=ENC_START_TIME) ){
		return TRUE;
	}else{
		return FALSE;
	}
}

//==============================================================================
/**
 * �g���[�i�[�h�c���L�[�ɂ��ē����������o��
 *
 * @param	inTrainerID		�g���[�i�[�h�c
 * @param	inIndex			���݂̖؃C���f�b�N�X
 *
 * @return	BOOL		TRUE:������		FALSE:�n�Y��
 */
//==============================================================================
static BOOL CheckRareFlg(const u32 inTrainerID, const u8 inIndex)
{
	u8 i,j;
	u8 temp[4];
	//4�ɕ���
	temp[0] = (inTrainerID >> 24) & 0xff;
	temp[1] = (inTrainerID >> 16) & 0xff;
	temp[2] = (inTrainerID >> 8) & 0xff;
	temp[3] = inTrainerID & 0xff;

	temp[0] %= HONEY_TREE_MAX;
	temp[1] %= HONEY_TREE_MAX;
	temp[2] %= HONEY_TREE_MAX;
	temp[3] %= HONEY_TREE_MAX;

	for(i=1;i<4;i++){
		for(j=0;j<i;j++){
			if (temp[j] == temp[i]){
				temp[i]++;
				if (temp[i]>=HONEY_TREE_MAX){
					temp[i] = 0;
				}
			}
		}
	}

	OS_Printf("honey_rare_hit:%d,%d,%d,%d\n",temp[0],temp[1],temp[2],temp[3]);

	for(i=0;i<4;i++){
		if (inIndex == temp[i]){
			return TRUE;	//������
		}
	}

	return FALSE;		//�n�Y��
}

//==============================================================================
/**
 * ���h��؂̃G���J�E���g�|�P�������擾
 *
 * @param	fsys		�t�B�[���h�V�X�e���|�C���^
 *
 * @return	int			�����X�^�[�i���o�[
 */
//==============================================================================
int HTE_GetHoneyTreeMonster(FIELDSYS_WORK *fsys)
{
	u8 tree_no;
	//���݂̃]�[��ID���擾
	tree_no = GetTreeNoFromZoneID(fsys->location->zone_id);
	GF_ASSERT(tree_no!=HONEY_TREE_MAX&&"���h��؂��o�^����Ă��܂���" );
	{
		int *tbl;
		int monsno;
		HT_PTR ptr;
		HONEY_DATA *data;

		ptr = EncDataSave_GetHoneyTree(EncDataSave_GetSaveDataPtr(fsys->savedata));
///		ptr = HTSave_GetHoneyTree(fsys->savedata);
		data = HTSave_GetHoneyDataPtr(tree_no, ptr);
		if( PM_VERSION == VERSION_DIAMOND ){		//�_�C��
			tbl = ArchiveDataLoadMallocLo(ARC_ENCDATA_EX, HoneyEncArcTbl_Dia[data->TblNo], HEAPID_FIELD);
		}else{										//�p�[��
			tbl = ArchiveDataLoadMallocLo(ARC_ENCDATA_EX, HoneyEncArcTbl_Perl[data->TblNo], HEAPID_FIELD);
		}
#ifdef PM_DEBUG		
		{
			int i;
			OS_Printf("�e�[�u������\n");
			for(i=0;i<5;i++){
				OS_Printf("%d,",tbl[i]);
			}
			OS_Printf("\n");
		}
#endif
		monsno = tbl[data->TblMonsNo];
		sys_FreeMemoryEz(tbl);
		return monsno;
	}
}

//==============================================================================
/**
 * �A�j���Z�b�g�R�[���o�b�N
 *
 * @param	work			���[�N
 * @param	inBlockIndex	�u���b�N�C���f�b�N�X
 * @param	inObjList		OBJ���X�g
 *
 * @return	none
 */
//==============================================================================
void HTE_SetHoneyTreeAnimeCallBack(void* work, const int inBlockIndex, const M3DOL_PTR inObjList)
{
	FIELDSYS_WORK *fsys;
	u8 tree_no;
	if (inBlockIndex<0){
		return;
	}

	fsys = (FIELDSYS_WORK *)work;
	SetHoneyTreeAnimation(fsys, inObjList, inBlockIndex);
}

//==============================================================================
/**
 * ���݂���]�[���̖��؃A�j���t���O�𗎂Ƃ�
 *
 * @param	fsys		�t�B�[���h�V�X�e���|�C���^
 *
 * @return	none
 */
//==============================================================================
void HTE_ResetAnimeFlg(FIELDSYS_WORK *fsys)
{
	HT_PTR ptr;
	HONEY_DATA *data;
	u8 tree_no;
	//���݂̃]�[��ID���擾
	tree_no = GetTreeNoFromZoneID(fsys->location->zone_id);
	GF_ASSERT(tree_no!=HONEY_TREE_MAX&&"���h��؂��o�^����Ă��܂���" );
	fsys->HoneyTreePtr->HoneyData[tree_no].AnimeFlg = FALSE;
	
	ptr = EncDataSave_GetHoneyTree(EncDataSave_GetSaveDataPtr(fsys->savedata));
	data = HTSave_GetHoneyDataPtr(tree_no, ptr);
	//���f�[�^�̎��Ԃ�0�ɂ���
	data->Time = 0;
}
