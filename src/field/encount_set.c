//============================================================================================
/**
 * @file	encount_set.c
 * @brief	�G���J�E���g�֘A

 * @author	saitou
 *
 * 2005.12.18	field_encount.c����G���J�E���g���蕔�����ړ�
 */
//============================================================================================
#include "encount_set.h"
#include "syswork.h"
#include "poketool/poke_tool.h"
#include "poketool/pokeparty.h"
#include "eventdata.h"
#include "honey_tree_enc.h"

#include "field_encount.h"
#include "battle/tokusyu_def.h"

#include "system/pm_rtc.h"
#include "system/timezone.h"
#include "sysflag.h"
#include "system/zukanwork.h"
#include "debug_saito.h"

#include "situation_local.h"

#include "enc_tbl_change_def.h"
#include "arc/encdata_ex.naix"

#include "savedata/encount.h"
#include "move_pokemon_def.h"
#include "move_pokemon.h"
#include "encount_define.h"

#include "generate_zone.h"
#include "calendar_enc.h"
#include "sp_fishing_enc.h"

#include "weather_sys.h"
#include "fieldmap_work.h"
#include "field_fishing.h"
#include "ev_time.h"

#include "zonedata.h"

#include "battle/battle_server.h"	//for	FormChange
#include "ev_pokemon.h"
#include "itemtool/itemsym.h"		//for ITEM_KIYOMENOOHUDA�EITEM_KIYOMENOOKOU
#include "savedata/vidro_type.h"

#include "safari_enc.h"
#include "agb_slot_enc.h"

#include "poketool/tr_tool.h"
#include "battle/trno_def.h"		//BTFIVE�̑���̂��߂̎b��Ȃ͂� by soga

//============================================================================================
//============================================================================================


#define	WALK_COUNT_GLOBAL	( 8 )		// �G���J�E���g���Ȃ������̊�{�l
#define	WALK_NEXT_PERCENT	( 5 )		// �����J�E���g���s�Ŏ��̏����ɐi�ފm��
#define	NEXT_PERCENT	( 40 )		// �G���J�E���g�����Ɉڍs�����{�m��
#define CYCLE_PERCENT		( 30 )	//���]�Ԃɏ���Ă���Ƃ��̉��Z�m��
#define LONG_GRASS_PERCENT		( 30 )	//�������̒��ɂ���Ƃ��̉��Z�m��

#define	CALC_SHIFT			( 8 )		// �v�Z�V�t�g�l

#define ENC_MONS_NUM_MAX	ENC_MONS_NUM_NORMAL

#define ROD_TYPE_NONE	(0xff)		//�m���e�[�u���w�薳��
#define WEATHER_NONE	(0xff)		//�V�C�w�薳��

#ifdef PM_DEBUG

u8 DebugFishProbFlg = 0;

#endif

typedef struct SWAY_ENC_INFO_tag
{
	int Table;
	BOOL Decide;
	BOOL Rare;
	BOOL Enc;
}SWAY_ENC_INFO;

typedef struct ENC_COMMON_DATA_tag
{
	int MonsNo;
	u16 LvMax;
	u16 LvMin;
}ENC_COMMON_DATA;

typedef struct ENC_FLD_SPA_tag
{
	u32 TrainerID;			//�g���[�i�[�h�c
	BOOL SprayCheck;		//�X�v���[�`�F�b�N���邩�̃t���O	TRUE:�`�F�b�N����
	BOOL EncCancelSpInvalid;//�퓬����������	TRUE:����	FALSE:�L��		(����ł́A���܂�������E���܂��~�c�p)
	u8	 SpMyLv;			//�X�v���[�`�F�b�N�Ɏg�����x��
	u8	 Egg;				//�^�}�S�t���O
	u8	 Spa;				//����
	u8   FormProb[2];		//�V�[�E�V�E�V�[�h���S�p�t�H�����ύX�m���@0�F�V�[�E�V�@1�F�V�[�h���S
	u8	 AnnoonTblType;		//�A���m�[���e�[�u���^�C�v
}ENC_FLD_SPA;

static BOOL MapEncountCheck( FIELDSYS_WORK * fsys, const u32 map_encount, const u8 attr );
static u8 EncountAttributeCheck( FIELDSYS_WORK * fsys, u8 attr, u8 *outEncLocation );
static BOOL	EncountWalkCheck( FIELDSYS_WORK * fsys, u32 per );
static BOOL EncountCheckMain( FIELDSYS_WORK * fsys, u32 per );

static BOOL CheckFixTypeEcnt(	POKEMON_PARAM *inPokeParam,
							const ENC_FLD_SPA *inFldSpa,
							const ENC_COMMON_DATA *inData,
							const u8 inListNum,
							const u8 type, const u8 tokusei,u8 * outNo);
static BOOL CheckEcntCancelByLv( const ENC_FLD_SPA *inFldSpa, POKEMON_PARAM *inMyPokeParam, const u8 inEneLv);
static int GetEncountProbGround(FIELDSYS_WORK * fsys);
static int GetEncountProbWater(FIELDSYS_WORK * fsys);
static int GetEncountProbFishing(FIELDSYS_WORK * fsys, const FISHINGROD_TYPE inRodType);
static BOOL WildEncSingle(FIELDSYS_WORK * fsys,
							POKEMON_PARAM *poke_param,
							BATTLE_PARAM * param,
							ENCOUNT_DATA *data,
							ENC_COMMON_DATA *enc_data,
							const ENC_FLD_SPA *inFldSpa,
							const SWAY_ENC_INFO *inSwayEncInfo );
static BOOL WildEncDouble(	FIELDSYS_WORK * fsys,
							POKEMON_PARAM *poke_param,
							BATTLE_PARAM * param,
							ENC_COMMON_DATA *enc_data,
							const ENC_FLD_SPA *inFldSpa );
static BOOL WildWaterEncSingle(	FIELDSYS_WORK * fsys,
								POKEMON_PARAM *poke_param,
								BATTLE_PARAM * param,
								ENC_COMMON_DATA *enc_data,
								const ENC_FLD_SPA *inFldSpa );
static BOOL FishingEncSingle(	FIELDSYS_WORK * fsys,
								POKEMON_PARAM *poke_param,
								BATTLE_PARAM * battle_param,
								ENC_COMMON_DATA *inData,
								const ENC_FLD_SPA *inFldSpa,
								const FISHINGROD_TYPE inRodType );
static BOOL SetEncountData(	POKEMON_PARAM *param,
							const FISHINGROD_TYPE inRodType,
							const ENC_FLD_SPA *inFldSpa,
							const ENC_COMMON_DATA *inData,
							const u8 location,
							const int inTarget,
							BATTLE_PARAM *outBattleParam);
static BOOL SetSwayEncountData(	FIELDSYS_WORK * fsys,
								POKEMON_PARAM *param,
								const ENC_FLD_SPA *inFldSpa,
								const ENC_COMMON_DATA *inData,
								const int inTarget,
								BATTLE_PARAM *outBattleParam,
								const int inMonsNo, const int inLv);
static BOOL SetEncountDataDecideMons(	const int inMonsNo, const int inLv,
										const int inTarget,
										const BOOL inRare,
										const u32 inTrainerID,
										const ENC_FLD_SPA *inSpa,
										POKEMON_PARAM *param,
										BATTLE_PARAM *outBattleParam);

static u8 ChangeEncProb(	const BOOL IsFishing,
							const u8 inProb,
							const ENC_FLD_SPA *inFldSpa,
							const u32 inWeatherCode,
							POKEMON_PARAM *inPokeParam	);

static void SetFieldBattleParam(FIELDSYS_WORK * fsys, const BOOL inSafariFlg, BATTLE_PARAM **param);
static void SetSfariMonster(FIELDSYS_WORK * fsys, const BOOL inSafariFlg, const BOOL inBookGet, ENC_COMMON_DATA *enc_data);

static BOOL CheckSpray(const u8 inEneLv, const ENC_FLD_SPA *inSpa);
static void SetMovePokemon(const u32 inTrainerID, MPD_PTR mpd, BATTLE_PARAM *outBattleParam);
static BOOL CheckMovePokeEnc(FIELDSYS_WORK * fsys, MPD_PTR *outMpd);
static BOOL AddPokemonParam(const int inTarget, const ENC_FLD_SPA *inFldSpa,
							POKEMON_PARAM *ioPokeParam, BATTLE_PARAM *ioBattleParam );
static u8 GetMaxLvMonsTblNo(const ENC_COMMON_DATA *inEncCommonData, const ENC_FLD_SPA *inFldSpa, const u8 inTblNo);
static void SetSpaStruct(FIELDSYS_WORK *fsys, POKEMON_PARAM *inPokeParam, ENCOUNT_DATA* inData, ENC_FLD_SPA *outSpa  );
static void ChangeEncProbByEquipItem( POKEMON_PARAM *inMyPokeParam, u8 *ioPer );
static void ChangeEncProbByVidro( FIELDSYS_WORK *fsys, u8 *ioPer );

typedef struct ANNOON_TABLE_tag
{
	int Num;
	const u8 *Tbl;
}ANNOON_TABLE;

static const u8 Tbl1[] = {
	UNK_A, UNK_B, UNK_C, UNK_G, UNK_H,
	UNK_J, UNK_K, UNK_L, UNK_M, UNK_O,
	UNK_P, UNK_Q, UNK_S, UNK_T, UNK_U,
	UNK_V, UNK_W, UNK_X, UNK_Y, UNK_Z,
};

static const u8 Tbl2[] = {
	UNK_F, 
};

static const u8 Tbl3[] = {
	UNK_R, 
};

static const u8 Tbl4[] = {
	UNK_I, 
};

static const u8 Tbl5[] = {
	UNK_N, 
};

static const u8 Tbl6[] = {
	UNK_E, 
};

static const u8 Tbl7[] = {
	UNK_D, 
};

static const u8 Tbl8[] = {
	UNK_ENC, UNK_QUE, 
};

static const ANNOON_TABLE ANNOON_Table[] = {
	{ 20, Tbl1 },
	{ 1 , Tbl2 },
	{ 1 , Tbl3 },
	{ 1 , Tbl4 },
	{ 1 , Tbl5 },
	{ 1 , Tbl6 },
	{ 1 , Tbl7 },
	{ 2 , Tbl8 },
};

//-----------------------------------------------------------------------------
/**
 * ���ԑуG���J�E���g�e�[�u�������ւ�
 *
 * @param	inEncData			�G���J�E���g�f�[�^�|�C���^
 * @param	*outTZEncMonsNo1	�G���J�E���g�|�P����1�̖�
 * @param	*outTZEncMonsNo2	�G���J�E���g�|�P����2�̖�
 *
 * @return	none
 */
//-----------------------------------------------------------------------------
void EncSet_SetTimeZoneEnc(const ENCOUNT_DATA *inEncData, int *outTZEncMonsNo1, int *outTZEncMonsNo2)
{
	int time_zone;
	time_zone = GF_RTC_GetTimeZone();
	if ( (time_zone == TIMEZONE_NOON)||(time_zone == TIMEZONE_EVENING) ){
		(*outTZEncMonsNo1) = inEncData->NoonEnc[0];
		(*outTZEncMonsNo2) = inEncData->NoonEnc[1];
	}else if( (time_zone == TIMEZONE_NIGHT)||(time_zone == TIMEZONE_MIDNIGHT) ){
		(*outTZEncMonsNo1) = inEncData->NightEnc[0];
		(*outTZEncMonsNo2) = inEncData->NightEnc[1];
	}
}
#if 0
//-----------------------------------------------------------------------------
/**
 * �T�t�@���G���J�E���g�e�[�u�������ւ�
 *
 * @param	inRandomSeed		�����_���̎�
 * @param	inBookComp			�S���}�ӊ����t���O
 * @param	*outSafEncMonsNo1	�G���J�E���g�|�P����1�̖�
 * @param	*outSafEncMonsNo2	�G���J�E���g�|�P����2�̖�
 *
 * @return	none
 */
//-----------------------------------------------------------------------------
void EncSet_SetSafariEnc(	const int inRandomSeed, const BOOL inBookComp,
							int *outSafEncMonsNo1, int *outSafEncMonsNo2	)
{
	int *tbl;
	int arc_idx;
	u16 tblno1,tblno2;
	
	//�S���}�ӊ������ǂ����ŁA�e�[�u����ς���
	if(inBookComp){
		arc_idx = NARC_encdata_ex_safari_af_bin;
	}else{
		arc_idx = NARC_encdata_ex_safari_bef_bin;
	}
	//�T�t�@���G���J�E���g�e�[�u���擾
	tbl = ArchiveDataLoadMallocLo(ARC_ENCDATA_EX, arc_idx, HEAPID_FIELD);
	//�����_���̎�����ɃT�t�@���G���J�E���g�e�[�u������2�̑I�o
	
	/* ---�I�o���@--- */
	/*�T�t�@�������_���̎�̏��2�o�C�g�Ɖ���2�o�C�g��*/
	/*�T�t�@������e�[�u�����Ŋ������]���I�o�|�P�����e�[�u���ԍ��Ƃ���*/
	/*���̌��ʁA2�̒l�������ꍇ�́A�l��1���������l��2�ڂ̃e�[�u���ԍ��Ƃ���*/
	/*�I�o����2�̔ԍ����e�[�u���̍Ō�̔ԍ��������ꍇ�A�Е��́A�e�[�u���̎n�߂̔ԍ��ƂȂ�*/
	
	tblno1 = ( (inRandomSeed >> 16) & 0xffff );
	tblno2 = ( inRandomSeed & 0xffff );

	tblno1 %= SAFARI_TBL_MAX;
	tblno2 %= SAFARI_TBL_MAX;

	if (tblno1 == tblno2){
		tblno2 = (tblno2+1)%SAFARI_TBL_MAX;
	}
	
	(*outSafEncMonsNo1) = tbl[tblno1];
	(*outSafEncMonsNo2) = tbl[tblno2];

	sys_FreeMemoryEz(tbl);
}
#endif

//-----------------------------------------------------------------------------
/**
 * ��ʔ����G���J�E���g�e�[�u�������ւ�
 *
 * @param	fsys				�t�B�[���h�V�X�e���|�C���^
 * @param	inEncData			�G���J�E���g�f�[�^�|�C���^
 * @param	*outGeneEncMonsNo1	�G���J�E���g�|�P����1�̖�
 * @param	*outGeneEncMonsNo2	�G���J�E���g�|�P����2�̖�
 *
 * @return	none
 */
//-----------------------------------------------------------------------------
static void EncSet_SetGeneEnc(	FIELDSYS_WORK * fsys,
								const ENCOUNT_DATA *inEncData,
								int *outGeneEncMonsNo1, int *outGeneEncMonsNo2)
{
	u32 rnd_seed;
	ENC_SV_PTR data;
	data = EncDataSave_GetSaveDataPtr(fsys->savedata);
	
	//��ʔ����������H
	if ( EncDataSave_IsGenerate( data ) ){
		//�����_���̎�����ɑ�ʔ�������ꏊ������o��2�̍����ւ�
		rnd_seed = EncDataSave_GetRandSeed(data, ENC_RND_SEED_GENERATE);
		if ( fsys->location->zone_id == GenerateZone_GetZone(rnd_seed)){
			(*outGeneEncMonsNo1) = inEncData->GenerateEnc[0];
			(*outGeneEncMonsNo2) = inEncData->GenerateEnc[1];
		}
	}
}

//-----------------------------------------------------------------------------
/**
 * ���R�G���J�E���g�e�[�u�������ւ�
 *
 * @param	fsys				�t�B�[���h�V�X�e���|�C���^
 * @param	inBookGet			�S���}�ӓ���t���O
 * @param	*outHillEncMonsNo1	�G���J�E���g�|�P����1�̖�
 * @param	*outHillEncMonsNo2	�G���J�E���g�|�P����2�̖�
 *
 * @return	none
 */
//-----------------------------------------------------------------------------
static void EncSet_SetHillBackEnc(	FIELDSYS_WORK * fsys, const BOOL inBookGet,
									int *outHillEncMonsNo1, int *outHillEncMonsNo2)
{
	int *tbl;
	u16 idx1,idx2;
	
	//���R�H
	if ( ZoneData_IsHillBackZone( fsys->location->zone_id ) ){
		EncDataSave_GetHillBackPokeIdx(fsys->savedata, &idx1, &idx2);
		//�S���}�ӓ��肵�Ă邩�H
		if ( inBookGet ){
			//���R�G���J�E���g�e�[�u���擾
			tbl = ArchiveDataLoadMallocLo(ARC_ENCDATA_EX, NARC_encdata_ex_mnt_af_bin, HEAPID_FIELD);
		
			//2�̍����ւ�
			if (idx1 != HILL_BACK_POKE_NONE){
				(*outHillEncMonsNo1) = tbl[idx1];
			}
			if (idx2 != HILL_BACK_POKE_NONE){
				(*outHillEncMonsNo2) = tbl[idx2];
			}
			sys_FreeMemoryEz(tbl);
		}
	}
}
//============================================================================================
//
//
//					�G���J�E���g���菈��
//
//
//============================================================================================
//-----------------------------------------------------------------------------
/**
 * �Q�΂Q�쐶��̂Ƃ��͗h�ꑐ�G���J�E���g�͂Ȃ��d�l�����A�`�F�b�N�͒ʂ��Ă܂�
 *
 * @param	fsys				�t�B�[���h�V�X�e���|�C���^
 *
 * @return	none
 */
//-----------------------------------------------------------------------------
BOOL FieldEncount_Check(FIELDSYS_WORK * fsys)
{
	BATTLE_PARAM * param;
	POKEMON_PARAM *poke_param;
	int x, z;
	u8	attr;
	u8 enc_location;	//�G���J�E���g����n�`�i�n�ォ���ォ�j
	BOOL rc;
	BOOL result;
	BOOL companion;
	BOOL safari_flg;	//�T�t�@���t���O

	SWAY_ENC_INFO sway_enc_info;
	
	POKEPARTY *my_party;
	ENCOUNT_DATA *data;
	ENC_COMMON_DATA enc_data[ENC_MONS_NUM_MAX];
	
	ENC_FLD_SPA f_spa;
	
	x = Player_NowGPosXGet( fsys->player );
	z = Player_NowGPosZGet( fsys->player );
	
	attr = (u8)GetAttributeLSB( fsys, x, z );

	{
		u8	prob;
		// �G���J�E���g�A�g���r���[�g�`�F�b�N
		prob = EncountAttributeCheck( fsys, attr, &enc_location );
		if( prob == 0 ){
			return FALSE;		//�G���J�E���g����A�g���r���[�g�ł͂Ȃ� �������͊m����0
		}

		//�莝���p�[�e�B�擾
		my_party = SaveData_GetTemotiPokemon(fsys->savedata);
		
		data = (ENCOUNT_DATA*)EventData_GetEncountData(fsys);
		poke_param = PokeParty_GetMemberPointer(my_party, 0);	//�擪�|�P�����擾
		
		SetSpaStruct(fsys, poke_param, data, &f_spa  );

		{
			//�X�v���[�g�p���Ȃ�΃X�v���[�`�F�b�N����
			if ( !EncDataSave_CanUseSpray( EncDataSave_GetSaveDataPtr(fsys->savedata) ) ){
				POKEMON_PARAM *spray_poke_param;
				OS_Printf("supure-chekku\n");
				spray_poke_param = EvPoke_GetLivingPokemonTop(my_party);
				//�X�v���[�`�F�b�N����
				f_spa.SprayCheck = TRUE;
				//�X�v���[�`�F�b�N�Ɏg�����x�����擾
				f_spa.SpMyLv = PokeParaGet(spray_poke_param, ID_PARA_level, NULL);
			}
		}
		
		//�����ɂ���ăG���J�E���g�m���ύX
		prob = ChangeEncProb(	FALSE, prob, &f_spa,
								Situation_GetWeatherID(SaveData_GetSituation(fsys->savedata)),
								poke_param	);
		//�r�[�h���ɂ��m���ύX
		ChangeEncProbByVidro( fsys, &prob );
		
		//�����A�C�e���i����߂̂��ӂ��j�ɂ��m���ϓ�
		ChangeEncProbByEquipItem( poke_param, &prob );
		
		if( MapEncountCheck( fsys, prob, attr ) == FALSE ){
			rc = FALSE;
		}else{
			rc = TRUE;
		}
	}

	memset( &sway_enc_info, 0, sizeof(SWAY_ENC_INFO) );

	//��ꑐ�G���J�E���g�`�F�b�N
	//��ꑐ�Ƀq�b�g������A���O�`�F�b�N�ŁA�G���J�E���g���Ȃ��������Ƃ��Ă��G���J�E���g����
	if ( !SwayGrass_CheckSpEncount(x, z, fsys, fsys->SwayGrass,
									&sway_enc_info.Table,
									&sway_enc_info.Decide,
									&sway_enc_info.Rare) ){
		sway_enc_info.Enc = FALSE;		//��ꑐ�G���J�E���g�s����
	}else{
		sway_enc_info.Enc = TRUE;		//��ꑐ�G���J�E���g����
		rc = TRUE;
	}

	if (rc == FALSE){
		return FALSE;
	}

	//�A���������
	if (!SysFlag_PairCheck(SaveData_GetEventWork(fsys->savedata))){	//�ʏ�
		companion = FALSE;
	}else{	//�A�����
		//�o�g���p�����[�^�̃A���P�[�V�����ƃ|�P�����p�[�e�B�̏�����
		companion = TRUE;
	}

	//�ړ��|�P�����`�F�b�N(�A��������A�h�ꑐ�G���J�E���g�������̓`�F�b�N���Ȃ�)
	if ( (!companion)&&(sway_enc_info.Enc==FALSE) ){
		MPD_PTR mpd;
		//�ړ��|�P�����G���J�E���g�`�F�b�N
		if ( CheckMovePokeEnc(fsys, &mpd) ){
			//�X�v���[�`�F�b�N
			if ( !CheckSpray( EncDataSave_GetMovePokeDataParam(mpd, MP_PARAM_LV),  &f_spa ) ){
				//�o�g���p�����쐬
				param = BattleParam_Create(HEAPID_WORLD, FIGHT_TYPE_MOVE);	//�t�@�C�g�^�C�v�͈ړ��|�P������p
				//�莝���|�P�����ȂǃZ�b�g
				BattleParam_SetParamByGameData(param, fsys);
				//�p�����[�^�Z�b�g
				SetMovePokemon(f_spa.TrainerID, mpd, param);
				//�G���J�E���g�����ꍇ�́A��ꑐ�����N���A
				SwayGrass_InitSwayGrass(fsys->SwayGrass);
				FieldEncount_Set(fsys, param);		//�ړ��|�P�����ƃG���J�E���g
				return TRUE;
			}else{
				return FALSE;		//�X�v���[�Ő퓬���(�o�g���p�����쐬�O�Ȃ̂ŉ�����Ȃ��Ăn�j)
			}
		}
	}

	//�o�g���p�����̍쐬
	if (!companion){
		//�T�t�@���t���O���擾
		safari_flg = SysFlag_SafariCheck(SaveData_GetEventWork(fsys->savedata));
		SetFieldBattleParam(fsys, safari_flg, &param);
	}else{
		param = BattleParam_Create(HEAPID_WORLD, FIGHT_TYPE_2vs2_YASEI);	//�t�@�C�g�^�C�v�͌Œ�
	}
	
	//�莝���|�P�����ȂǃZ�b�g
	BattleParam_SetParamByGameData(param, fsys);
	
	//�n�㐅�㕪��
	if (enc_location == GROUND_ENCOUNT){			//�n��
		//���ʃG���J�E���g�f�[�^�쐬
		int i;
		BOOL book_get;
		for(i=0;i<ENC_MONS_NUM_NORMAL;i++){
			enc_data[i].MonsNo = data->NormalEnc[i].MonsterNo;
			enc_data[i].LvMax = data->NormalEnc[i].Level;
			enc_data[i].LvMin = data->NormalEnc[i].Level;
		}

		//�S���}�ӓ���t���O�擾
		book_get = ZukanWork_GetZenkokuZukanFlag(
								SaveData_GetZukanWork(GameSystem_GetSaveData(fsys)));
		
		//����e�[�u����������
		EncSet_SetTimeZoneEnc( data, &enc_data[TIME_ENC_1].MonsNo, &enc_data[TIME_ENC_2].MonsNo);
		//��ʔ����e�[�u����������
		EncSet_SetGeneEnc(fsys, data, &enc_data[GENE_ENC_1].MonsNo, &enc_data[GENE_ENC_2].MonsNo);
		//���R�e�[�u����������
		EncSet_SetHillBackEnc(	fsys, book_get, &enc_data[SP_ENC_1].MonsNo, &enc_data[SP_ENC_2].MonsNo);
		//AGB�X���b�g�e�[�u����������
		AgbSlotEnc_SetAgbSlotEnc(data, book_get, &enc_data[AGB_ENC_1].MonsNo, &enc_data[AGB_ENC_2].MonsNo);

		if (!companion){
			//�T�t�@������g�̃Z�b�g
			SetSfariMonster(fsys, safari_flg, book_get, enc_data);
			//�V���O����Z�b�g
			result = WildEncSingle(	fsys, poke_param, param, data, enc_data, &f_spa,
							&sway_enc_info );
		}else{
			//�����|�P�����Z�b�g
			{
				//�{���͘A������Ă���ܐl�O��ID���� by soga 2006.06.20
				param->trainer_id[CLIENT_NO_MINE2] =
					SysWork_PairTrainerIDGet( SaveData_GetEventWork(fsys->savedata) ); //BTFIVE1_01
				TT_EncountTrainerDataMake(param,fsys->savedata,HEAPID_WORLD);
			}
			result = WildEncDouble(	fsys, poke_param, param, enc_data, &f_spa );
		}
	}else if(enc_location == WATER_ENCOUNT){		//����
		//���ʃG���J�E���g�f�[�^�쐬
		int i;
		for(i=0;i<ENC_MONS_NUM_SEA;i++){
			enc_data[i].MonsNo = data->EncSea[i].MonsterNo;
			enc_data[i].LvMax = data->EncSea[i].MaxLevel;
			enc_data[i].LvMin = data->EncSea[i].MinLevel;
		}
		result = WildWaterEncSingle(	fsys, poke_param, param, enc_data, &f_spa);
	}else{
		GF_ASSERT(0&&"�G���J�E���g���P�[�V�����s��");
		BattleParam_Delete(param);	//�o�g���p�������
		return FALSE;
	}

	if (result){
		FieldEncount_Set(fsys, param);
	}else{
		rc = FALSE;
	}

	GF_ASSERT( sys_CheckHeapSafe( HEAPID_FIELD ) );
	GF_ASSERT( sys_CheckHeapSafe( HEAPID_WORLD ) );

	if (rc == FALSE){
		BattleParam_Delete(param);	//�o�g���p�������
	}
	//�����J�E���g�N���A����
	fsys->encount.walk_count = 0;
	
	return rc;
}

//-----------------------------------------------------------------------------
/**
 * �ނ�G���J�E���g
 * ���T�t�@���ɂ����Ƃ��Ă��A�ނł͓���g�������̂ŁA�T�t�@�������X�^�[�̃Z�b�g�͍s��Ȃ�
 *
 * @param	fsys				�t�B�[���h�V�X�e���|�C���^
 * @param	inRodtype			�ނ��
 * @param	outBattleParam		�o�g���p�����[�^�̃|�C���^�̃|�C���^
 *
 * @return	BOOL
 */
//-----------------------------------------------------------------------------
BOOL SetFishingEncount( FIELDSYS_WORK * fsys, const FISHINGROD_TYPE inRodType, BATTLE_PARAM **outBattleParam )
{
	POKEMON_PARAM *poke_param;
	POKEPARTY *my_party;
	BOOL safari_flg;		//�T�t�@���t���O

	ENC_COMMON_DATA enc_data[ENC_MONS_NUM_MAX];
	ENC_FLD_SPA f_spa;		//����\��

	{
		u8 prob;
#ifdef PM_DEBUG
		if (DebugFishProbFlg){
			prob = 100;
		}else{
			// �G���J�E���g��
			prob = GetEncountProbFishing(fsys, inRodType);
		}
#else
		// �G���J�E���g��
		prob = GetEncountProbFishing(fsys, inRodType);
#endif
		if(  prob == 0 ){
			return FALSE;		//�m����0
		}

		//�莝���|�P�p�[�e�B�擾
		my_party = SaveData_GetTemotiPokemon(fsys->savedata);
		poke_param = PokeParty_GetMemberPointer(my_party, 0);	//�擪�|�P�����擾	
		SetSpaStruct(fsys, poke_param, NULL, &f_spa);

		//�����ɂ���ăG���J�E���g���ύX
		prob = ChangeEncProb(	TRUE, prob, &f_spa,
								Situation_GetWeatherID(SaveData_GetSituation(fsys->savedata)),
								poke_param	);
		//�m���ŃG���J�E���g
		if (gf_p_rand(100) >= prob){
			return FALSE;		//�G���J�E���g���Ȃ�
		}
	}
	//�T�t�@���t���O���擾
	safari_flg = SysFlag_SafariCheck(SaveData_GetEventWork(fsys->savedata));

	//�o�g���p�����[�^�Z�b�g
	SetFieldBattleParam(fsys, safari_flg, outBattleParam);
	//�莝���|�P�����ȂǃZ�b�g
	BattleParam_SetParamByGameData(*outBattleParam, fsys);
	//��p�̐ݒ�
	BattleParam_SetFisingParam(*outBattleParam);


	if ( (ZoneData_IsSpFishingZone(fsys->location->zone_id))&&
			 SpFishing_CheckPoint(fsys) ){
		//����ނ�f�[�^�쐬
		u8 i;
		int monsno;
		u8 max,min;
		SpFishing_GetMaxMinLv(&max, &min);
		SpFishing_GetMonsNo(&monsno);
		
		for(i=0;i<ENC_MONS_NUM_FISH;i++){
			enc_data[i].MonsNo = monsno;
			enc_data[i].LvMax = max;
			enc_data[i].LvMin = min;
		}
	}else{
		//���ʃG���J�E���g�f�[�^�쐬
		{
			NON_GROUND_ENC_MONSTER_DAT *enc_fish;
			u8 i;
			ENCOUNT_DATA *data;

			data = (ENCOUNT_DATA*)EventData_GetEncountData(fsys);
			//�V�[�E�V�E�V�[�h���S�t�H�����ύX�m���Z�b�g<<�ނ�ł͏o�Ȃ��̂ŃZ�b�g�s�v

			//�ނ�ƕʂɃf�[�^�쐬
			switch(inRodType){
			case FISHINGROD_BAD:		//�{��
				enc_fish = data->EncFish1;
				break;
			case FISHINGROD_GOOD:		//����
				enc_fish = data->EncFish2;
				break;
			case FISHINGROD_GREAT:		//������
				enc_fish = data->EncFish3;
				break;
			}
		
			for(i=0;i<ENC_MONS_NUM_FISH;i++){
				enc_data[i].MonsNo = enc_fish[i].MonsterNo;
				enc_data[i].LvMax = enc_fish[i].MaxLevel;
				enc_data[i].LvMin = enc_fish[i].MinLevel;
			}	
		}
	}

	//�ނ�G���J�E���g
	{
		BOOL rc;
		rc = FishingEncSingle( fsys, poke_param, *outBattleParam, enc_data, &f_spa, inRodType );
		if (!rc){
			return FALSE;
		}
	}
	
	return TRUE;
}

//-----------------------------------------------------------------------------
/**
 * �Â����E�Â�����G���J�E���g
 *
 * @param	fsys				�t�B�[���h�V�X�e���|�C���^
 * @param	event			�C�x���g�|�C���^
 *
 * @return	BOOL
 */
//-----------------------------------------------------------------------------
BOOL SetSweetEncount(FIELDSYS_WORK * fsys, GMEVENT_CONTROL * event)
{
	BATTLE_PARAM * param;
	POKEMON_PARAM *poke_param;
	int x, z;
	u8	attr;
	u8 enc_location;	//�G���J�E���g����n�`�i�n�ォ���ォ�j
	BOOL companion;
	BOOL safari_flg;	//�T�t�@���t���O
	BOOL result;
	SWAY_ENC_INFO sway_enc_info;
	
	POKEPARTY *my_party;
	ENCOUNT_DATA *data;
	ENC_COMMON_DATA enc_data[ENC_MONS_NUM_MAX];
	ENC_FLD_SPA f_spa;		//����\��

	x = Player_NowGPosXGet( fsys->player );
	z = Player_NowGPosZGet( fsys->player );

	
	attr = (u8)GetAttributeLSB( fsys, x, z );
	
	{
		u8	prob;
		prob = EncountAttributeCheck( fsys, attr, &enc_location );
		if( prob == 0 ){
			return FALSE;		//�G���J�E���g����A�g���r���[�g�ł͂Ȃ� �������͊m����0
		}
	}
	
	//�莝���p�[�e�B�擾
	my_party = SaveData_GetTemotiPokemon(fsys->savedata);

	data = (ENCOUNT_DATA*)EventData_GetEncountData(fsys);
	poke_param = PokeParty_GetMemberPointer(my_party, 0);	//�擪�|�P�����擾
	SetSpaStruct(fsys, poke_param, data, &f_spa);
	//�X�v���[�`�F�b�N���Ȃ�
	f_spa.SprayCheck = FALSE;
	//�G���J�E���g���������L�����Z������
	f_spa.EncCancelSpInvalid = TRUE;

	memset( &sway_enc_info, 0, sizeof(SWAY_ENC_INFO) );
	
	//�A���������
	if (!SysFlag_PairCheck(SaveData_GetEventWork(fsys->savedata))){	//�ʏ�
		companion = FALSE;
	}else{	//�A�����
		companion = TRUE;
	}

	//�ړ��|�P�����`�F�b�N(�A��������̓`�F�b�N���Ȃ��B���܂�������ŗh�ꑐ�͖����̂ŁA�`�F�b�N�͏Ȃ�)
	if (!companion){
		MPD_PTR mpd;
		//�ړ��|�P�����G���J�E���g�`�F�b�N
		if ( CheckMovePokeEnc(fsys, &mpd) ){
			//����ŃG���J�E���g�Ȃ̂ŃX�v���[�`�F�b�N�Ȃ�
			//�o�g���p�����쐬
			param = BattleParam_Create(HEAPID_WORLD, FIGHT_TYPE_MOVE);	//�t�@�C�g�^�C�v�͈ړ��|�P������p
			//�莝���|�P�����ȂǃZ�b�g
			BattleParam_SetParamByGameData(param, fsys);
			//�p�����[�^�Z�b�g
			SetMovePokemon(f_spa.TrainerID,mpd, param);
			//�G���J�E���g�����ꍇ�́A��ꑐ�����N���A
			SwayGrass_InitSwayGrass(fsys->SwayGrass);
			FieldEncount_Change(fsys, event, param);		//�ړ��|�P�����ƃG���J�E���g
			return TRUE;
		}
	}

	//�o�g���p�����̍쐬
	if (!companion){
		//�T�t�@���t���O���擾
		safari_flg = SysFlag_SafariCheck(SaveData_GetEventWork(fsys->savedata));
		SetFieldBattleParam(fsys, safari_flg, &param);
	}else{
		param = BattleParam_Create(HEAPID_WORLD, FIGHT_TYPE_2vs2_YASEI);	//�t�@�C�g�^�C�v�͌Œ�
	}
	
	//�莝���|�P�����ȂǃZ�b�g
	BattleParam_SetParamByGameData(param, fsys);

	//�n�㐅�㕪��
	if (enc_location == GROUND_ENCOUNT){			//�n��
		//���ʃG���J�E���g�f�[�^�쐬
		int i;
		BOOL book_get;
		for(i=0;i<ENC_MONS_NUM_NORMAL;i++){
			enc_data[i].MonsNo = data->NormalEnc[i].MonsterNo;
			enc_data[i].LvMax = data->NormalEnc[i].Level;
			enc_data[i].LvMin = data->NormalEnc[i].Level;
		}

		//�S���}�ӓ���t���O�擾
		book_get = ZukanWork_GetZenkokuZukanFlag(
								SaveData_GetZukanWork(GameSystem_GetSaveData(fsys)));

		//����e�[�u����������
		EncSet_SetTimeZoneEnc( data, &enc_data[TIME_ENC_1].MonsNo, &enc_data[TIME_ENC_2].MonsNo);
		//��ʔ����e�[�u����������
		EncSet_SetGeneEnc(fsys, data, &enc_data[GENE_ENC_1].MonsNo, &enc_data[GENE_ENC_2].MonsNo);
		//���R�e�[�u����������
		EncSet_SetHillBackEnc(	fsys, book_get, &enc_data[SP_ENC_1].MonsNo, &enc_data[SP_ENC_2].MonsNo);
		//AGB�X���b�g�e�[�u����������
		AgbSlotEnc_SetAgbSlotEnc(data, book_get, &enc_data[AGB_ENC_1].MonsNo, &enc_data[AGB_ENC_2].MonsNo);
		
		if (!companion){
			//�T�t�@������g�̃Z�b�g
			SetSfariMonster(fsys, safari_flg, book_get, enc_data);
			//�V���O����Z�b�g
			result = WildEncSingle(	fsys, poke_param, param, data, enc_data, &f_spa,
							&sway_enc_info );
		}else{
			//�����|�P�����Z�b�g
			{
				//�{���͘A������Ă���ܐl�O��ID���� by soga 2006.06.20
				param->trainer_id[CLIENT_NO_MINE2] = 
					SysWork_PairTrainerIDGet( SaveData_GetEventWork(fsys->savedata) ); //BTFIVE1_01;
				TT_EncountTrainerDataMake(param,fsys->savedata,HEAPID_WORLD);
			}
			result = WildEncDouble(	fsys, poke_param, param, enc_data, &f_spa );
		}
	}else if(enc_location == WATER_ENCOUNT){		//����
		//���ʃG���J�E���g�f�[�^�쐬
		int i;
		for(i=0;i<ENC_MONS_NUM_SEA;i++){
			enc_data[i].MonsNo = data->EncSea[i].MonsterNo;
			enc_data[i].LvMax = data->EncSea[i].MaxLevel;
			enc_data[i].LvMin = data->EncSea[i].MinLevel;
		}
		result = WildWaterEncSingle(	fsys, poke_param, param, enc_data, &f_spa);
	}else{
		GF_ASSERT(0&&"�G���J�E���g���P�[�V�����s��");
		return FALSE;
	}

	if (result){
		FieldEncount_Change(fsys, event, param);
	}else{
		GF_ASSERT(0);
	}
	//�����J�E���g�N���A����
	fsys->encount.walk_count = 0;
	return TRUE;
}

//-----------------------------------------------------------------------------
/**
 * ���o�K�`���G���J�E���g
 *
 * @param	fsys				�t�B�[���h�V�X�e���|�C���^
 * @param	outBattleParam		�o�g���p�����[�^�̃|�C���^�̃|�C���^
 *
 * @return	BOOL		TRUE:�G���J�E���g����	FALSE:�G���J�E���g�s����
 */
//-----------------------------------------------------------------------------
BOOL SetKeyRandEncount( FIELDSYS_WORK * fsys, BATTLE_PARAM **outBattleParam )
{
	POKEMON_PARAM *poke_param;
	int x, z;
	u8	attr;
	u8 enc_location;	//�G���J�E���g����n�`�i�n�ォ���ォ�j
	BOOL rc;
	BOOL result;
	BOOL companion;
	BOOL safari_flg;	//�T�t�@���t���O

	SWAY_ENC_INFO sway_enc_info;
	
	POKEPARTY *my_party;
	ENCOUNT_DATA *data;
	ENC_COMMON_DATA enc_data[ENC_MONS_NUM_MAX];
	
	ENC_FLD_SPA f_spa;

	*outBattleParam = NULL;
	
	x = Player_NowGPosXGet( fsys->player );
	z = Player_NowGPosZGet( fsys->player );
	
	attr = (u8)GetAttributeLSB( fsys, x, z );

	{
		u8	prob;
		// �G���J�E���g�A�g���r���[�g�`�F�b�N
		prob = EncountAttributeCheck( fsys, attr, &enc_location );
		if( prob == 0 ){
			return FALSE;		//�G���J�E���g����A�g���r���[�g�ł͂Ȃ� �������͊m����0
		}

		//�莝���p�[�e�B�擾
		my_party = SaveData_GetTemotiPokemon(fsys->savedata);
		
		data = (ENCOUNT_DATA*)EventData_GetEncountData(fsys);
		poke_param = PokeParty_GetMemberPointer(my_party, 0);	//�擪�|�P�����擾
		
		SetSpaStruct(fsys, poke_param, data, &f_spa  );

		{
			//�X�v���[�g�p���Ȃ�΃X�v���[�`�F�b�N����
			if ( !EncDataSave_CanUseSpray( EncDataSave_GetSaveDataPtr(fsys->savedata) ) ){
				POKEMON_PARAM *spray_poke_param;
				OS_Printf("supure-chekku\n");
				spray_poke_param = EvPoke_GetLivingPokemonTop(my_party);
				//�X�v���[�`�F�b�N����
				f_spa.SprayCheck = TRUE;
				//�X�v���[�`�F�b�N�Ɏg�����x�����擾
				f_spa.SpMyLv = PokeParaGet(spray_poke_param, ID_PARA_level, NULL);
			}
		}
		
		//�����ɂ���ăG���J�E���g�m���ύX
		prob = ChangeEncProb(	FALSE, prob, &f_spa,
								Situation_GetWeatherID(SaveData_GetSituation(fsys->savedata)),
								poke_param	);
		//�r�[�h���ɂ��m���ύX
		ChangeEncProbByVidro( fsys, &prob );
		
		//�����A�C�e���i����߂̂��ӂ��j�ɂ��m���ϓ�
		ChangeEncProbByEquipItem( poke_param, &prob );
		
		if( MapEncountCheck( fsys, prob, attr ) == FALSE ){
			rc = FALSE;
		}else{
			rc = TRUE;
		}
	}

	memset( &sway_enc_info, 0, sizeof(SWAY_ENC_INFO) );
	sway_enc_info.Enc = FALSE;		//��ꑐ�G���J�E���g�m���ɕs����
	
	//�A���������
	if (!SysFlag_PairCheck(SaveData_GetEventWork(fsys->savedata))){	//�ʏ�
		companion = FALSE;
	}else{	//�A�����
		//�o�g���p�����[�^�̃A���P�[�V�����ƃ|�P�����p�[�e�B�̏�����
		companion = TRUE;
	}

	//�ړ��|�P�����`�F�b�N(�A��������̓`�F�b�N���Ȃ��B���o�K�`���ŗh�ꑐ�͂Ȃ��̂ŁA�`�F�b�N�͏Ȃ�)
	if (!companion){
		MPD_PTR mpd;
		//�ړ��|�P�����G���J�E���g�`�F�b�N
		if ( CheckMovePokeEnc(fsys, &mpd) ){
			//�X�v���[�`�F�b�N
			if ( !CheckSpray( EncDataSave_GetMovePokeDataParam(mpd, MP_PARAM_LV),  &f_spa ) ){
				//�o�g���p�����쐬
				*outBattleParam = BattleParam_Create(HEAPID_WORLD, FIGHT_TYPE_MOVE);	//�t�@�C�g�^�C�v�͈ړ��|�P������p
				//�莝���|�P�����ȂǃZ�b�g
				BattleParam_SetParamByGameData(*outBattleParam, fsys);
				//�p�����[�^�Z�b�g
				SetMovePokemon(f_spa.TrainerID,mpd, *outBattleParam);
				//�G���J�E���g�����ꍇ�́A��ꑐ�����N���A
				SwayGrass_InitSwayGrass(fsys->SwayGrass);
				return TRUE;
			}else{
				return FALSE;		//�X�v���[�Ő퓬���(�o�g���p�����쐬�O�Ȃ̂ŉ�����Ȃ��Ăn�j)
			}
		}
	}

	//�o�g���p�����̍쐬
	if (!companion){
		//�T�t�@���t���O���擾
		safari_flg = SysFlag_SafariCheck(SaveData_GetEventWork(fsys->savedata));
		SetFieldBattleParam(fsys, safari_flg, outBattleParam);
	}else{
		*outBattleParam = BattleParam_Create(HEAPID_WORLD, FIGHT_TYPE_2vs2_YASEI);	//�t�@�C�g�^�C�v�͌Œ�
	}
	
	//�莝���|�P�����ȂǃZ�b�g
	BattleParam_SetParamByGameData(*outBattleParam, fsys);
	
	//�n�㐅�㕪��	���ヌ�o�K�`���͖������낤�B����
	if (enc_location == GROUND_ENCOUNT){			//�n��
		//���ʃG���J�E���g�f�[�^�쐬
		int i;
		BOOL book_get;
		for(i=0;i<ENC_MONS_NUM_NORMAL;i++){
			enc_data[i].MonsNo = data->NormalEnc[i].MonsterNo;
			enc_data[i].LvMax = data->NormalEnc[i].Level;
			enc_data[i].LvMin = data->NormalEnc[i].Level;
		}

		//�S���}�ӓ���t���O�擾
		book_get = ZukanWork_GetZenkokuZukanFlag(
								SaveData_GetZukanWork(GameSystem_GetSaveData(fsys)));
		
		//����e�[�u����������
		EncSet_SetTimeZoneEnc( data, &enc_data[TIME_ENC_1].MonsNo, &enc_data[TIME_ENC_2].MonsNo);
		//��ʔ����e�[�u����������
		EncSet_SetGeneEnc(fsys, data, &enc_data[GENE_ENC_1].MonsNo, &enc_data[GENE_ENC_2].MonsNo);
		//���R�e�[�u����������
		EncSet_SetHillBackEnc(	fsys, book_get, &enc_data[SP_ENC_1].MonsNo, &enc_data[SP_ENC_2].MonsNo);
		//AGB�X���b�g�e�[�u����������
		AgbSlotEnc_SetAgbSlotEnc(data, book_get, &enc_data[AGB_ENC_1].MonsNo, &enc_data[AGB_ENC_2].MonsNo);

		if (!companion){
			//�T�t�@������g�̃Z�b�g
			SetSfariMonster(fsys, safari_flg, book_get, enc_data);
			//�V���O����Z�b�g
			result = WildEncSingle(	fsys, poke_param, *outBattleParam, data, enc_data, &f_spa,
							&sway_enc_info );
		}else{
			{
				//�{���͘A������Ă���ܐl�O��ID���� by soga 2006.06.20
				(*outBattleParam)->trainer_id[CLIENT_NO_MINE2] =
					SysWork_PairTrainerIDGet( SaveData_GetEventWork(fsys->savedata) ); //BTFIVE1_01
				TT_EncountTrainerDataMake(*outBattleParam,fsys->savedata,HEAPID_WORLD);
			}
			result = WildEncDouble(	fsys, poke_param, *outBattleParam, enc_data, &f_spa );
		}
	}else{
		GF_ASSERT(0&&"�G���J�E���g���P�[�V�����s��");
		BattleParam_Delete(*outBattleParam);	//�o�g���p�������
		return FALSE;
	}

	if (!result){
		rc = FALSE;
	}

	GF_ASSERT( sys_CheckHeapSafe( HEAPID_FIELD ) );
	GF_ASSERT( sys_CheckHeapSafe( HEAPID_WORLD ) );

	if (rc == FALSE){
		BattleParam_Delete(*outBattleParam);	//�o�g���p�������
	}else{
		//�����J�E���g�N���A����
		fsys->encount.walk_count = 0;
	}
	return rc;
}


//-----------------------------------------------------------------------------
/**
 * �쐶�V���O����Z�b�g�A�b�v
 *
 * @param	fsys				�t�B�[���h�V�X�e���|�C���^
 * @param	poke_param			�|�P�����p����
 * @param	param				�o�g���p����
 * @param	data				�G���J�E���g�f�[�^
 * @param	enc_data			���ʃG���J�E���g�f�[�^�e�[�u��
 * @param	inFldSpa			�����`�F�b�N�E�t�H�����ύX�p�\���̂ւ̃|�C���^
 * @param	inSwayEncInfo		�h�ꑐ���f�[�^�ւ̃|�C���^
 *
 * @return	BOOL	TRUE:�G���J�E���g����	FALSE:�G���J�E���g���Ȃ�
 */
//-----------------------------------------------------------------------------
static BOOL WildEncSingle(FIELDSYS_WORK * fsys,
							POKEMON_PARAM *poke_param,
							BATTLE_PARAM * param,
							ENCOUNT_DATA *data,
							ENC_COMMON_DATA *enc_data,
							const ENC_FLD_SPA *inFldSpa,
							const SWAY_ENC_INFO *inSwayEncInfo )
{
	BOOL rc;
	//�h�ꑐ���ǂ����ŕ���
	if (inSwayEncInfo->Enc){	//�h�ꑐ�G���J�E���g
		int monsno,lv;
		//��ꑐ��p�e�[�u���ɏ�������
		if (inSwayEncInfo->Table == SWAY_GRASS_ENC_SP){
			enc_data[SWAY_ENC_1].MonsNo = data->SwayEnc[0];
			enc_data[SWAY_ENC_2].MonsNo = data->SwayEnc[1];
			enc_data[SWAY_ENC_3].MonsNo = data->SwayEnc[2];
			enc_data[SWAY_ENC_4].MonsNo = data->SwayEnc[3];
		}

		//�h�ꑐ�O��|�P���������擾�i���񎞂́A0�������Ă�j
		SwayGrass_GetEncMonsNoLv(fsys->SwayGrass, &monsno, &lv);
		//�G���J�E���g���郂���X�^�[�����肵�Ă���ꍇ
		if (inSwayEncInfo->Decide == TRUE)	{
			MYSTATUS *my_st;
			//�g���[�i�[�h�c�擾
			my_st = SaveData_GetMyStatus(GameSystem_GetSaveData(fsys));
			//�w��|�P������100���G���J�E���g
			rc = SetEncountDataDecideMons(	monsno, lv,
											POKEPARTY_ENEMY,
											inSwayEncInfo->Rare,
											MyStatus_GetID(my_st),//�g���[�i�[�h�c
											inFldSpa,
											poke_param,
											param );
		}else{	//���肵�Ă��Ȃ��ꍇ�A�������͏���
			//�G���J�E���g�f�[�^���Z�b�g
			rc = SetSwayEncountData(fsys, poke_param, inFldSpa, enc_data, POKEPARTY_ENEMY,
									param,  monsno, lv);
		}
		
		if (rc){
			//����h�ꑐ�ꏊ������
			{
				int x,z;
				//���@�̈ʒu�擾
				x = Player_NowGPosXGet(fsys->player);
				z = Player_NowGPosZGet(fsys->player);
				SwayGrass_SearchSwayGrass(fsys, x, z, fsys->SwayGrass);
			}
		}
	}else{			//�ʏ�
		rc = SetEncountData(poke_param, ROD_TYPE_NONE, inFldSpa, enc_data,
							GROUND_ENCOUNT, POKEPARTY_ENEMY,
							param);
		if (rc){
			//�ʏ�G���J�E���g�����ꍇ�́A��ꑐ��񓙂��N���A
			SwayGrass_InitSwayGrass(fsys->SwayGrass);
		}
	}
	return rc;
}

//-----------------------------------------------------------------------------
/**
 * �쐶�_�u����Z�b�g�A�b�v
 *
 * @param	fsys				�t�B�[���h�V�X�e���|�C���^
 * @param	poke_param			�|�P�����p����
 * @param	param				�o�g���p����
 * @param	enc_data			���ʃG���J�E���g�f�[�^�e�[�u��
 * @param	inFldSpa			�����`�F�b�N�E�t�H�����ύX�p�\���̂ւ̃|�C���^
 *
 * @return	BOOL	TRUE:�G���J�E���g����	FALSE:�G���J�E���g���Ȃ�
 */
//-----------------------------------------------------------------------------
static BOOL WildEncDouble(	FIELDSYS_WORK * fsys,
							POKEMON_PARAM *poke_param,
							BATTLE_PARAM * param,
							ENC_COMMON_DATA *enc_data,
							const ENC_FLD_SPA *inFldSpa )
{
	BOOL rc;
	{
		{
			//�G���J�E���g�f�[�^���Z�b�g
			rc = SetEncountData(	poke_param, ROD_TYPE_NONE, inFldSpa, enc_data,
									GROUND_ENCOUNT, POKEPARTY_ENEMY,
									param );
			if (!rc){
				return FALSE;
			}
			
			rc = SetEncountData(	poke_param, ROD_TYPE_NONE, inFldSpa, enc_data,
									GROUND_ENCOUNT, POKEPARTY_ENEMY_PAIR,
									param );
		}
		
	}
	return rc;
}

//-----------------------------------------------------------------------------
/**
 * �쐶����V���O����Z�b�g�A�b�v
 *
 * @param	fsys				�t�B�[���h�V�X�e���|�C���^
 * @param	poke_param			�|�P�����p����
 * @param	param				�o�g���p����
 * @param	enc_data			���ʃG���J�E���g�f�[�^�e�[�u��
 * @param	inFldSpa			�����`�F�b�N�E�t�H�����ύX�p�\���̂ւ̃|�C���^
 *
 * @return	BOOL	TRUE:�G���J�E���g����	FALSE:�G���J�E���g���Ȃ�
 */
//-----------------------------------------------------------------------------
static BOOL WildWaterEncSingle(	FIELDSYS_WORK * fsys,
								POKEMON_PARAM *poke_param,
								BATTLE_PARAM * param,
								ENC_COMMON_DATA *enc_data,
								const ENC_FLD_SPA *inFldSpa )
{
	BOOL rc;

	{
		//�G���J�E���g�f�[�^���Z�b�g
		rc = SetEncountData(	poke_param, ROD_TYPE_NONE, inFldSpa, enc_data,
								WATER_ENCOUNT, POKEPARTY_ENEMY,
								param );
	}
	return rc;
}

//-----------------------------------------------------------------------------
/**
 * �ނ�
 *
 * @param	fsys				�t�B�[���h�V�X�e���|�C���^
 * @param	poke_param			�|�P�����p����
 * @param	battle_param		�o�g���p����
 * @param	inData				�G���J�E���g�f�[�^
 * @param	inFldSpa			�����`�F�b�N�E�t�H�����ύX�p�\���̂ւ̃|�C���^
 * @param	inRodType			�ފ�
 *
 * @return	BOOL	TRUE:�G���J�E���g����	FALSE:�G���J�E���g���Ȃ�
 */
//-----------------------------------------------------------------------------
static BOOL FishingEncSingle(	FIELDSYS_WORK * fsys,
								POKEMON_PARAM *poke_param,
								BATTLE_PARAM * battle_param,
								ENC_COMMON_DATA *inData,
								const ENC_FLD_SPA *inFldSpa,
								const FISHINGROD_TYPE inRodType )
{
	BOOL rc;
	rc = SetEncountData(poke_param, inRodType, inFldSpa, inData,
						FISHING_ENCOUNT, POKEPARTY_ENEMY,
						battle_param );
	return rc;
}

//-----------------------------------------------------------------------------
/**
 * �G���J�E���g�`�F�b�N�i�����֘A�j
 *
 * @param	fsys				�t�B�[���h�V�X�e���|�C���^
 * @param	map_encount			�G���J�E���g�m��
 * @param	attr				�A�g���r���[�g
 *
 * @return	BOOL	TRUE:�G���J�E���g����	FALSE:�G���J�E���g���Ȃ�
 */
//-----------------------------------------------------------------------------
static BOOL MapEncountCheck( FIELDSYS_WORK * fsys, const u32 per, const u8 attr )
{
	u8 next_base;
	u32 map_encount;
	
	//100%�����
	if (per>100){
		map_encount = 100;
	}
	map_encount = per << CALC_SHIFT;

	// �G���J�E���g�������
	if( EncountWalkCheck( fsys, map_encount ) == FALSE ){
		fsys->encount.walk_count++;			// �����J�E���g�{
		// 5%�Ŏ��̏�����
		if( ( gf_p_rand(100) ) >= WALK_NEXT_PERCENT ){
			return FALSE;
		}
	}

	next_base = NEXT_PERCENT;	//��{40��

	//�������̏ꍇ��+30��
	if ( MATR_IsLongGrass(attr) ){
		next_base += LONG_GRASS_PERCENT;
	}else{
		//���]�Ԃɏ���Ă���Ȃ�+30��
		if ( Player_FormGet( fsys->player ) == HERO_FORM_CYCLE ){
			next_base += CYCLE_PERCENT;
		}
	}
	//���t�ɂ��m���ϓ�
	next_base = CalEnc_GetProb(next_base, EVTIME_IsPenaltyMode(fsys));

	//100%�����
	if (next_base>100){
		next_base = 100;
	}

	// next_base%�Ŏ��̏����i��{��60%�ŏ�����ł��؂�)
	if( ( gf_p_rand(100) ) < next_base  ){
		// ���C��
		if( EncountCheckMain( fsys, per ) ){
			return TRUE;
		}	
	}
	return FALSE;
	
}

//-----------------------------------------------------------------------------
/**
 * �m����Ԃ�
 *
 * @param	fsys				�t�B�[���h�V�X�e���|�C���^
 * @param	attr				�A�g���r���[�g
 * @param	outEncLocation		�G���J�E���g�ꏊ���i�[����o�b�t�@
 *
 * @return	u8					�m��
 */
//-----------------------------------------------------------------------------
static u8 EncountAttributeCheck( FIELDSYS_WORK * fsys, u8 attr, u8 *outEncLocation  )
{
	if (MATR_IsEncount(attr)){
		if (MATR_IsWater(attr)){			//��
			(*outEncLocation) = WATER_ENCOUNT;
			return GetEncountProbWater( fsys );
		}else{								//��
			(*outEncLocation) = GROUND_ENCOUNT;
			return GetEncountProbGround( fsys );
		}
	}
	return 0;
}

//-----------------------------------------------------------------------------
/**
 * �k���`�F�b�N
 *
 * @param	fsys	�t�B�[���h�V�X�e���|�C���^
 * @param	per		�m��
 *
 * @return	BOOL	
 */
//-----------------------------------------------------------------------------
static BOOL	EncountWalkCheck( FIELDSYS_WORK * fsys, u32 per )
{
	per = (per/10)>>CALC_SHIFT;
	if (per > WALK_COUNT_GLOBAL) {
		per = WALK_COUNT_GLOBAL;
	}
	per = WALK_COUNT_GLOBAL - ( per );

	if( fsys->encount.walk_count >= per ){
		return TRUE;
	}
	return FALSE;
}

//-----------------------------------------------------------------------------
/**
 * �G���J�E���g�`�F�b�N
 *
 * @param	fsys	�t�B�[���h�V�X�e���|�C���^
 * @param	per		�m��
 *
 * @return	BOOL	TRUE:�G���J�E���g����	FALSE:�G���J�E���g���Ȃ�
 */
//-----------------------------------------------------------------------------
static BOOL EncountCheckMain( FIELDSYS_WORK * fsys, u32 per )
{
	if ( gf_p_rand(100) >= per ){
		return FALSE;
	}else{
		return TRUE;
	}
}

//-----------------------------------------------------------------------------
/**
 * �����_���|�P�����Z�b�g�i���ނ�/����/���A�j
 *
 * @return	u8 �G���J�E���g�f�[�^�̃e�[�u���ԍ�
 */
//-----------------------------------------------------------------------------
static u8 RandamPokeSet(void)
{
	u8	i;

	i = gf_p_rand(100);

	if( i < 20 )			return	0;		// 20%
	if( i >= 20 && i < 40 )	return	1;		// 20%
	if( i >= 40 && i < 50 )	return	2;		// 10%
	if( i >= 50 && i < 60 )	return	3;		// 10%
	if( i >= 60 && i < 70 )	return	4;		// 10%
	if( i >= 70 && i < 80 )	return	5;		// 10%
	if( i >= 80 && i < 85 )	return	6;		//  5%
	if( i >= 85 && i < 90 )	return	7;		//  5%
	if( i >= 90 && i < 94 )	return	8;		//  4%
	if( i >= 94 && i < 98 )	return	9;		//  4%
	if( i == 98 )			return	10;		//  1%
	return	11;								//  1%
}

//-----------------------------------------------------------------------------
/**
 * �����_���|�P�����Z�b�g�i����j
 *
 * @return	u8 �G���J�E���g�f�[�^�̃e�[�u���ԍ�
 */
//-----------------------------------------------------------------------------
static u8 RandamPokeSetNoGround(void)
{
	u8	i;

	i = gf_p_rand(100);

	if( i < 60 )			return	0;		// 60%
	if( i >= 60 && i < 90 )	return	1;		// 30%
	if( i >= 90 && i < 95 )	return	2;		//  5%
	if( i >= 95 && i < 99 )	return	3;		//  4%
	return	4;								//  1%
}

//-----------------------------------------------------------------------------
/**
 * �����_���|�P�����Z�b�g�i�ނ�j
 *
 * @param	inFishingRod		�ފ�
 *
 * @return	u8		�G���J�E���g�f�[�^�̃e�[�u���ԍ�		
 */
//-----------------------------------------------------------------------------
static u8 RandamPokeSetFishing( const FISHINGROD_TYPE inFishingRod )
{
	u8	i;
	u8	p = 0;

	i = gf_p_rand(100);

	switch( inFishingRod ){
	case FISHINGROD_BAD:		// �{���̒ފ�
		if		( i < 60 )	p = 0;	// 60%
		else if ( i < 90 )	p = 1;	// 30%
		else if ( i < 95 )	p = 2;	// 5%
		else if ( i < 99 )	p = 3;	// 4%	
		else				p = 4;	// 1%
		break;
	case FISHINGROD_GOOD:		// �ǂ��ފ�
		if		( i < 40 )	p = 0;	// 40%
		else if ( i < 80 )	p = 1;	// 40%
		else if ( i < 95 )	p = 2;	// 15%
		else if ( i < 99 )	p = 3;	// 4%
		else				p = 4;	// 1%
		break;
	case FISHINGROD_GREAT:		// �����ފ�
		if		( i < 40 )	p = 0;	// 40%
		else if ( i < 80 )	p = 1;	// 40%
		else if ( i < 95 )	p = 2;	// 15%
		else if ( i < 99 )	p = 3;	// 4%
		else				p = 4;	// 1%
		break;
	default:
		GF_ASSERT(0&&"unknown fishing rod");
	}

	return	p;
}

//-----------------------------------------------------------------------------
/**
 * �����A�C�e���ɂ��G���J�E���g���ω�
 *
 * @param	inMyPokeParam	�莝���擪�|�P����
 * @param	ioPer			�m��
 *
 * @return	none
 */
//-----------------------------------------------------------------------------
static void ChangeEncProbByEquipItem( POKEMON_PARAM *inMyPokeParam, u8 *ioPer )
{
	u16 item;
	item = PokeParaGet( inMyPokeParam, ID_PARA_item, NULL );
	// �擪�̃|�P�������u����߂̂��ӂ��v�E�u����߂̂������v�𑕔����Ă���ꍇ�A2/3
	if( (item == ITEM_KIYOMENOOHUDA)||
		(item == ITEM_KIYOMENOOKOU) ){
		(*ioPer) = ( (*ioPer) * 2 ) / 3;
	}
}

//-----------------------------------------------------------------------------
/**
 * �r�[�h�����G���J�E���g���ω�
 *
 * @param	fsys		�t�B�[���h�V�X�e���|�C���^
 * @param	ioPer		�m��
 *
 * @return	none
 */
//-----------------------------------------------------------------------------
static void ChangeEncProbByVidro( FIELDSYS_WORK *fsys, u8 *ioPer )
{
	u8 type;
	//�Z�[�u�f�[�^����r�[�h���^�C�v���擾
	type = EncDataSave_GetVidro( EncDataSave_GetSaveDataPtr(fsys->savedata) );
	if( type == VIDRO_BLACK ){			//�u���낢�r�[�h���v���g�p���Ă���ꍇ�A1/2�{
		(*ioPer)/=2;
//		OS_Printf("���g�p��%d\n",(*ioPer));
	}else if (type == VIDRO_WHITE){		//�u���낢�r�[�h���v���g�p���Ă���ꍇ�A1.5�{
		(*ioPer) = (*ioPer) + ((*ioPer)/2);
//		OS_Printf("���g�p��%d\n",(*ioPer));
	}
}

//-----------------------------------------------------------------------------
/**
 * ���i�ݒ�
 *
 * @param	inPokeParam			�|�P�����p����
 * @param	inFldSpa			�����`�F�b�N�E�t�H�����ύX�p�\���̂ւ̃|�C���^
 *
 * @return	u8					���i
 */
//-----------------------------------------------------------------------------
static u8 GetEncountChar(POKEMON_PARAM *inPokeParam, const ENC_FLD_SPA *inFldSpa)
{
	u32	type;

	//�V���N���̓����ɂ��G���J�E���g�|�P�����̐��i�𓯂��ɂȂ�₷������
	// �擪�̃|�P�������^�}�S�łȂ�
	if( inFldSpa->Egg == 0 ){
		if( inFldSpa->Spa == TOKUSYU_SINKURO ){	//�V���N��
			if ( gf_p_rand(2) == 0 ){//�����K�p�@�m��1/2
				type = (u32)PokeParaGet( inPokeParam, ID_PARA_personal_rnd, NULL );
				type = type % 25;
				return (u8)type;
			}
		}
	}
	
	return gf_p_rand(25);	// �����_���Ō���
	
}

//-----------------------------------------------------------------------------
/**
 * ���x���ݒ�
 *
 * @param	inData			���ʃG���J�E���g�f�[�^�e�[�u��
 * @param	inFldSpa		�����`�F�b�N�E�t�H�����ύX�p�\���̂ւ̃|�C���^
 *
 * @return	u8				���x��
 */
//-----------------------------------------------------------------------------
static u8 SetEncountPokeLv( const ENC_COMMON_DATA *inData, const ENC_FLD_SPA *inFldSpa )
{
	u8	size;
	u8	plus;
	u8	min, max;
	u8	spa;

	// Max Lv �� Min Lv ��菬�����ꍇ�̏C������
	if( inData->LvMax >= inData->LvMin ){
		min = inData->LvMin;
		max = inData->LvMax;
	}else{
		min = inData->LvMax;
		max = inData->LvMin;
	}

	size = max - min + 1;		// �␳�T�C�Y
	plus = gf_rand() % size;	// �␳�l

	//�u��邫�v�u�v���b�V���[�v�u�͂肫��v�̓��������`�F�b�N���x���̍����|�P�����ƂT���ŃG���J�E���g
	// �擪�̃|�P�������^�}�S�łȂ�
	if( inFldSpa->Egg == 0 ){
		if( (inFldSpa->Spa == TOKUSYU_HARIKIRI)||
			(inFldSpa->Spa == TOKUSYU_YARUKI)||
			(inFldSpa->Spa == TOKUSYU_PURESSYAA) ){
			// 1/2�œ�������
			if( gf_p_rand(2) == 0 ){
				return 	( min + plus );		// ����������
			}
			return	( max );	//���������B���x����max�ɂ���
		}
	}

	return	( min + plus );		// �G���J�E���g���x��
}

//-----------------------------------------------------------------------------
/**
 * �G���J�E���g�|�P�����Z�b�g�i���A�j
 *
 * @param	poke				�����X�^�[�i���o�[
 * @param	lv					���x��
 * @param	inTarget			�ǉ��Ώ�
 * @param	inTrainerID			�g���[�i�[�h�c
 * @param	inFldSpa			�����`�F�b�N�E�t�H�����ύX�p�\���̂ւ̃|�C���^
 * @param	inPokeParam			�|�P�����p�����i�����j
 * @param	outBattleParam		�o�g���p�����|�C���^
 *
 * @return	none
 */
//-----------------------------------------------------------------------------
static void EncountParamSetRare(	const u16 poke, const u8 lv, const int inTarget,
									const u32 inTrainerID, const ENC_FLD_SPA *inFldSpa,
									POKEMON_PARAM *inPokeParam, BATTLE_PARAM *outBattleParam )
{
	BOOL rc;
	u32 rnd_val;
	BOOL sp_use;	//�����K�p���邩�H
	u8 my_poke_sex;
	u8 my_poke_chr;
	
	POKEMON_PARAM *poke_param;
	poke_param = PokemonParam_AllocWork(HEAPID_WORLD);
	PokeParaInit(poke_param);

	sp_use = FALSE;

	//�����`�F�b�N	���A�ƂȂ�h�c�͕������ɁA�����𔽉f
	//�`�F�b�N��������́A���������{�f�B�ƃV���N��
	if (inFldSpa->Egg == 0){
		if (inFldSpa->Spa == TOKUSYU_MEROMEROBODHI){
			//�G���J�E���g����|�P�����̐��ʃx�N�g���𒲂ׂ�
			u32 sex_vec;
			sex_vec = PokePersonalParaGet( poke, ID_PER_sex );
			switch(sex_vec){
			case    MONS_MALE:
			case    MONS_FEMALE:
			case    MONS_UNKNOWN:
					break;		//���ʖ����������́A�Œ�̏ꍇ�́A�����������Ȃ�
			default:
				// 2/3�œ�������
				if( gf_p_rand(3) > 0 ){
					my_poke_sex = PokeParaGet(inPokeParam, ID_PARA_sex, NULL);//PokeSexGet(inPokeParam);
					sp_use = TRUE;
				}
			}
		}else if (inFldSpa->Spa == TOKUSYU_SINKURO){
			if ( gf_p_rand(2) == 0 ){//�����K�p�@�m��1/2
				my_poke_chr = PokeSeikakuGet(inPokeParam);
				sp_use = TRUE;
			}
		}
	}

	//���A�������擾
	rnd_val = PokeRareRndGet(inTrainerID);

	if (sp_use){//������K�p����ꍇ
		u8 sex,chr;
		do{
			if (inFldSpa->Spa == TOKUSYU_MEROMEROBODHI){
				//����̐��ʂ��擾�i���ʖ����͏�Œe���Ă�̂ŕK�����Y��������͂��j
				sex = PokeSexGetMonsNo(poke, rnd_val);
				GF_ASSERT(sex!=PARA_UNK&&"ERROR:ENCOUNT_SEX_ERROR");
				//�����̐��ʂƔ�r�i���������{�f�B�������Ă���|�P�����͕K�����ʂ����邱�Ƃ�O��Ƃ���j
				if (sex != my_poke_sex){
					break;	//�ِ��Ȃ̂ŏI��
				}else{
					rnd_val = PokeRareRndGet(inTrainerID);	//���A�������Ď擾
				}
			}else if (inFldSpa->Spa == TOKUSYU_SINKURO){
				//����̐��i���擾
				chr = PokeSeikakuGetRnd(rnd_val);
				//�����̐��i�Ɣ�r
				if (chr == my_poke_chr){
					break;	//�������i�Ȃ̂ŏI��
				}else{
					rnd_val = PokeRareRndGet(inTrainerID);	//���A�������Ď擾
				}
				

			}
		}while(1);
	}
	
	PokeParaSet(poke_param, poke, lv, POW_RND, RND_SET, rnd_val, ID_SET, inFldSpa->TrainerID);
	rc = AddPokemonParam(inTarget, inFldSpa, poke_param, outBattleParam);
	GF_ASSERT(rc&&"�|�P�����̒ǉ��Ɏ��s");
	sys_FreeMemoryEz(poke_param);

	OS_Printf("RARE_POKEMON_ENCOUNT!!!!!\n");
}

//-----------------------------------------------------------------------------
/**
 * �G���J�E���g�|�P�����Z�b�g
 *
 * @param	poke				�����X�^�[�i���o�[
 * @param	lv					���x��
 * @param	inTarget			�ǉ��Ώ�
 * @param	inFldSpa			�����`�F�b�N�E�t�H�����ύX�p�\���̂ւ̃|�C���^
 * @param	inPokeParam			�|�P�����p�����i�����j
 * @param	outBattleParam		�o�g���p�����|�C���^
 *
 * @return	none
 */
//-----------------------------------------------------------------------------
static void EncountParamSet(u16 poke, u8 lv, const int inTarget, const ENC_FLD_SPA *inFldSpa,
							POKEMON_PARAM *inPokeParam, BATTLE_PARAM *outBattleParam )
{
	u8 valid_flg;	//�����L���`�F�b�N�t���O
	u8 sex;
	BOOL rc;
	POKEMON_PARAM *poke_param;
	poke_param = PokemonParam_AllocWork(HEAPID_WORLD);
	PokeParaInit(poke_param);

	valid_flg = 1;

	//�G���J�E���g����|�P�����̐��ʃx�N�g���𒲂ׂ�
	{
		u32 sex_vec;
		sex_vec = PokePersonalParaGet( poke, ID_PER_sex );
		switch(sex_vec){
        case    MONS_MALE:
        case    MONS_FEMALE:
        case    MONS_UNKNOWN:
			valid_flg = 0;
		}
	}

	if (valid_flg){//�I�o�����|�P���������ʂȂ��A�������́A�Œ�̏ꍇ�́A�����`�F�b�N�Ȃ�
		//�擪�|�P�����̓��������������{�f�B�̂Ƃ��ِ͈����o�₷���Ȃ�
		// �擪�̃|�P�������^�}�S�łȂ�
		if( inFldSpa->Egg == 0 ){
			if( inFldSpa->Spa == TOKUSYU_MEROMEROBODHI ){
				// 2/3�œ�������
				if( gf_p_rand(3) > 0 ){
					sex = PokeParaGet(inPokeParam, ID_PARA_sex, NULL);//PokeSexGet(inPokeParam);
					//�ِ��𔭐�������
					if (sex == PARA_FEMALE){
						sex = PARA_MALE;
						OS_Printf("���X�Ȃ̂ŃI�X�Z�b�g\n");
					}else if (sex == PARA_MALE){
						sex = PARA_FEMALE;
						OS_Printf("�I�X�Ȃ̂Ń��X�Z�b�g\n");
					}else{			GF_ASSERT(0&&"���ʕs��");
					}
					PokeParaSetSexChr(poke_param, poke, lv, POW_RND, sex, GetEncountChar(inPokeParam, inFldSpa), 0);
					PokeParaPut(poke_param, ID_PARA_id_no, &inFldSpa->TrainerID);
#if 0	//�f�o�b�O�p
					{
						u8 d_sex;
						d_sex = PokeParaGet(inPokeParam, ID_PARA_sex, NULL);//PokeSexGet(poke_param);
						if (d_sex == PARA_FEMALE){
							OS_Printf("���X\n");
						}else if (d_sex == PARA_MALE){
							OS_Printf("�I�X\n");
						}else{
							GF_ASSERT(0&&"�Z�b�g�������ʕs��");
						}
					}
#endif				
					rc = AddPokemonParam(inTarget, inFldSpa, poke_param, outBattleParam);
					GF_ASSERT(rc&&"�|�P�����̒ǉ��Ɏ��s");
					sys_FreeMemoryEz(poke_param);
					return;
				}
			}
		}
	}

	PokeParaSetChr( poke_param, poke, lv, POW_RND, GetEncountChar(inPokeParam, inFldSpa) );
	PokeParaPut(poke_param, ID_PARA_id_no, &inFldSpa->TrainerID);
	rc = AddPokemonParam(inTarget, inFldSpa, poke_param, outBattleParam);
	GF_ASSERT(rc&&"�|�P�����̒ǉ��Ɏ��s");
	sys_FreeMemoryEz(poke_param);
}

#ifdef PM_DEBUG
//----------------------------------------------------
//	�f�o�b�O�G���J�E���g�|�P�����Z�b�g
//	���� : u16 poke = �|�P����ID
//		   u8 lv    = �G���J�E���gLv
//----------------------------------------------------
static void DebugEncountParamSet(	u16 poke, u8 lv, const int inTarget,
									BATTLE_PARAM *outBattleParam )
{
	u16 monsno;
	u32 rnd;
	u8 sex;
	u8 spa;
	BOOL rc;
	POKEMON_PARAM *poke_param;
	poke_param = PokemonParam_AllocWork(HEAPID_WORLD);
	PokeParaInit(poke_param);
	
	PokeParaSetChr( poke_param, poke, lv, POW_RND, (gf_p_rand(25)) );
	rc = PokeParty_Add(outBattleParam->poke_party[inTarget], poke_param);
	GF_ASSERT(rc&&"�|�P�����̒ǉ��Ɏ��s");
	sys_FreeMemoryEz(poke_param);
}
#endif

//-----------------------------------------------------------------------------
/**
 * �G���J�E���g�f�[�^�Z�b�g
 *
 * @param	param				�����X�^�[�i���o�[
 * @param	inRodType					���x��
 * @param	inFldSpa			�����`�F�b�N�E�t�H�����ύX�p�\���̂ւ̃|�C���^
 * @param	inData				���ʃG���J�E���g�f�[�^�e�[�u��
 * @param	location			�ꏊ
 * @param	intarget			�ǉ��Ώ�
 * @param	outBattleParam		�o�g���p�����|�C���^
 *
 * @return	none
 */
//-----------------------------------------------------------------------------
static BOOL SetEncountData(	POKEMON_PARAM *param,
							const FISHINGROD_TYPE inRodType,
							const ENC_FLD_SPA *inFldSpa,
							const ENC_COMMON_DATA *inData,
							const u8 location,
							const int inTarget,
							BATTLE_PARAM *outBattleParam)
{
	BOOL result;
	u8	no = 0;
	u8	lv = 0;
	
	// �G���J�E���g�|�P��������
	switch( location ){
	case GROUND_ENCOUNT:	// ���n
		//����傭�����ɂ��A�͂��˃^�C�v�̃G���J�E���g���̌���
		result = CheckFixTypeEcnt(	param, inFldSpa, inData,
									ENC_MONS_NUM_NORMAL, METAL_TYPE,TOKUSYU_ZIRYOKU, &no);
		if (result == FALSE){
			//�����ł񂫓����ɂ��A�ł񂫃^�C�v�̃G���J�E���g���̌���
			result = CheckFixTypeEcnt(	param, inFldSpa, inData,
										ENC_MONS_NUM_NORMAL, ELECTRIC_TYPE,TOKUSYU_SEIDENKI, &no);
			if (result == FALSE){
				//�����ɂ��w��^�C�v�Ƃ̃G���J�E���g�Ɏ��s�B�ʏ�̃G���J�E���g
				no = RandamPokeSet();
				//OS_Printf("enc_random = %d\n",no);				
			}
		}
		//�B�������ɂ��ő僌�x���|�P�����I�o(�n��)
		no = GetMaxLvMonsTblNo(inData, inFldSpa, no);
		lv = inData[no].LvMax;
		break;
	case WATER_ENCOUNT:		// ����
		//����傭�����ɂ��A�͂��˃^�C�v�̃G���J�E���g���̌���
		result = CheckFixTypeEcnt(	param, inFldSpa, inData,
									ENC_MONS_NUM_SEA, METAL_TYPE,TOKUSYU_ZIRYOKU, &no);
		//�����ł񂫓����ɂ��A�ł񂫃^�C�v�̃G���J�E���g���̌���
		result = CheckFixTypeEcnt(	param, inFldSpa, inData,
									ENC_MONS_NUM_SEA, ELECTRIC_TYPE,TOKUSYU_SEIDENKI, &no);
		if (result == FALSE){
			//�����ɂ��w��^�C�v�Ƃ̃G���J�E���g�Ɏ��s�B�ʏ�̃G���J�E���g
			no = RandamPokeSetNoGround();
		}
		//���x���Z�b�g
		lv = SetEncountPokeLv( &inData[no], inFldSpa );
		break;
	case FISHING_ENCOUNT:	//�ނ�
		//����傭�����ɂ��A�͂��˃^�C�v�̃G���J�E���g���̌���
		result = CheckFixTypeEcnt(	param, inFldSpa, inData,
									ENC_MONS_NUM_FISH, METAL_TYPE,TOKUSYU_ZIRYOKU, &no);
		//�����ł񂫓����ɂ��A�ł񂫃^�C�v�̃G���J�E���g���̌���
		result = CheckFixTypeEcnt(	param, inFldSpa, inData,
									ENC_MONS_NUM_FISH, ELECTRIC_TYPE,TOKUSYU_SEIDENKI, &no);
		if (result == FALSE){
			//�����ɂ��w��^�C�v�Ƃ̃G���J�E���g�Ɏ��s�B�ʏ�̃G���J�E���g
			no = RandamPokeSetFishing(inRodType);
		}
		//���x���Z�b�g
		lv = SetEncountPokeLv( &inData[no], inFldSpa );
		break;
	default:
		GF_ASSERT(0);
	}

	//�����ɂ�郌�x�����퓬���
	if( CheckEcntCancelByLv( inFldSpa, param, lv )){
		return FALSE;
	}

	// �X�v���[�`�F�b�N Lv�̒Ⴂ�|�P�����̓G���J�E���g���Ȃ�
	if( CheckSpray(lv, inFldSpa) == TRUE ){
		return FALSE;		//�X�v���[�Ő퓬���
	}
	
	// �G���J�E���g�|�P�����Z�b�g
	EncountParamSet( inData[no].MonsNo, lv, inTarget, inFldSpa, param, outBattleParam );
	return	TRUE;
}

//-----------------------------------------------------------------------------
/**
 * �G���J�E���g�f�[�^�Z�b�g�i�|�P�����w��j
 *
 * @param	inMonsNo			�����X�^�[�i���o�[
 * @param	inLv				���x��
 * @param	inTarget			�ǉ��Ώ�
 * @param	inRare				���A�t���O
 * @param	inTrainerID			�g���[�i�[�h�c
 * @param	inFldSpa			�����`�F�b�N�E�t�H�����ύX�p�\���̂ւ̃|�C���^
 * @param	param				�|�P�����p�����i�����j
 * @param	outBattleParam		�o�g���p�����|�C���^
 *
 * @return	none
 */
//-----------------------------------------------------------------------------
static BOOL SetEncountDataDecideMons(	const int inMonsNo, const int inLv,
										const int inTarget,
										const BOOL inRare,
										const u32 inTrainerID,
										const ENC_FLD_SPA *inFldSpa,
										POKEMON_PARAM *param,
										BATTLE_PARAM *outBattleParam)
{
	u8	lv = 0;

	GF_ASSERT(inMonsNo != 0);
	
	//�G���J�E���g����|�P���������łɌ��܂��Ă���̂ŁA����傭�A�����ł񂫓����͖�������
	//��邫�A�͂肫��A�v���b�V���[�ɂ��A���x���ϓ����s��Ȃ�
	lv = inLv;

	//�X�v���[�`�F�b�N����
	
	// �G���J�E���g�|�P�����Z�b�g
	if (inRare){
		EncountParamSetRare(inMonsNo, lv, inTarget, inTrainerID,
							inFldSpa, param, outBattleParam );
	}else{
		EncountParamSet( inMonsNo, lv, inTarget, inFldSpa, param, outBattleParam );
	}
	return	TRUE;
}

//-----------------------------------------------------------------------------
/**
 * �G���J�E���g�f�[�^�Z�b�g�i�h�ꑐ�j
 *
 * @param	fsys				�t�B�[���h�V�X�e���|�C���^
 * @param	param				�|�P�����p����
 * @param	inFldSpa			�����`�F�b�N�E�t�H�����ύX�p�\���̂ւ̃|�C���^
 * @param	inData				���ʃG���J�E���f�[�^�e�[�u��
 * @param	inTartget			�ǉ��Ώ�
 * @param	outBattleParam		�o�g���p�����|�C���^
 *
 * @return	none
 */
//-----------------------------------------------------------------------------
static BOOL SetSwayEncountData(	FIELDSYS_WORK * fsys,
								POKEMON_PARAM *param,
								const ENC_FLD_SPA *inFldSpa,
								const ENC_COMMON_DATA *inData,
								const int inTarget,
								BATTLE_PARAM *outBattleParam,
								const int inMonsNo, const int inLv)
{
	u8 result;
	u8	no = 0;
	u8	lv = 0;

	int monsno;
	
	// �G���J�E���g�|�P��������
	//����傭�����ɂ��A�͂��˃^�C�v�̃G���J�E���g���̌���
	result = CheckFixTypeEcnt(	param, inFldSpa, inData,
								ENC_MONS_NUM_NORMAL, METAL_TYPE,TOKUSYU_ZIRYOKU, &no);
	if (result == FALSE){
		//�����ł񂫓����ɂ��A�ł񂫃^�C�v�̃G���J�E���g���̌���
		result = CheckFixTypeEcnt(	param, inFldSpa, inData,
									ENC_MONS_NUM_NORMAL, ELECTRIC_TYPE,TOKUSYU_SEIDENKI, &no);
		if (result == FALSE){
			//�����ɂ��w��^�C�v�Ƃ̃G���J�E���g�Ɏ��s�B�ʏ�̃G���J�E���g
			no = RandamPokeSet();
		}
	}
	lv = inData[no].LvMax;
	monsno = inData[no].MonsNo;

	//���񂩁H
	if (inMonsNo == 0){	//����
		//�����ꑐ�G���J�E���g�Ƃ��āA�G���J�E���g�����ꍇ�́A�Z�b�g�����|�P�������L������
		SwayGrass_SetEncMonsNoLv(fsys->SwayGrass, monsno, lv);
		//�A�����̍X�V<<�d�l�ύX 2006/0519 add�@���񂩂�X�V����i�����ɂ͘A�����ł͂Ȃ��Đ퓬���ɂȂ�j
		SwayGrass_UpDateChain(fsys);
	}else{			//���񂶂�Ȃ�
		//�h�ꑐ�n�Y�����������Ǔ����|�P�����̏ꍇ�͘A���𕜊�������
		if (monsno == inMonsNo ){
			monsno = inMonsNo;
			lv = inLv;
			//�A�����̍X�V
			SwayGrass_UpDateChain(fsys);
		}else{
			//�n�Y���Ȃ̂ŗh�ꑐ�I���
			SwayGrass_InitSwayGrass(fsys->SwayGrass);
		}
	}

	//�X�v���[�`�F�b�N����
	
	// �G���J�E���g�|�P�����Z�b�g
	EncountParamSet( monsno, lv, inTarget, inFldSpa, param, outBattleParam );
	return	TRUE;
}

//-----------------------------------------------------------------------------
/**
 * �G���J�E���g�f�[�^�Z�b�g�i���h��j
 *
 * @param	fsys				�t�B�[���h�V�X�e���|�C���^
 * @param	outBattleParam		�o�g���p�����|�C���^
 *
 * @return	none
 */
//-----------------------------------------------------------------------------
void SetHoneyTreeEncountData(FIELDSYS_WORK *fsys, BATTLE_PARAM *outBattleParam)
{
	POKEMON_PARAM *param;
	int monsno;
	ENC_FLD_SPA f_spa;		//����\��
	u8 lv;
	
	monsno = HTE_GetHoneyTreeMonster(fsys);
	//�擪�|�P�����̃^�}�S�`�F�b�N
	{	
		POKEPARTY *my_party;
		my_party = SaveData_GetTemotiPokemon(fsys->savedata);
		param = PokeParty_GetMemberPointer(my_party, 0);	//�擪�|�P�����擾
		SetSpaStruct(fsys, param, NULL, &f_spa );
	}

	//���x���ݒ�i5�`15�j
	{
		u8 plus = HONEY_TREE_LV_MAX-HONEY_TREE_LV_MIN+1;
		lv = HONEY_TREE_LV_MIN + gf_p_rand(plus);

		//�u��邫�v�u�v���b�V���[�v�u�͂肫��v�̓��������`�F�b�N���x���̍����|�P�����ƂT���ŃG���J�E���g
		// �擪�̃|�P�������^�}�S�łȂ�
		if( f_spa.Egg == 0 ){
			if( (f_spa.Spa == TOKUSYU_HARIKIRI)||
				(f_spa.Spa == TOKUSYU_YARUKI)||
				(f_spa.Spa == TOKUSYU_PURESSYAA) ){
				// 1/2�œ�������
				if( gf_p_rand(2) == 0 ){
					;		// ����������
				}else{
					lv = HONEY_TREE_LV_MAX;	//���������B���x����max�ɂ���
				}
			}
		}
	}

	//�X�v���[�`�F�b�N����
	
	//���؃A�j���t���O�I�t
	HTE_ResetAnimeFlg(fsys);
	outBattleParam->battle_status_flag |= BATTLE_STATUS_FLAG_MITSUNURI_BATTLE;
	
	EncountParamSet( monsno, lv, POKEPARTY_ENEMY, &f_spa, param, outBattleParam );
	return;
}

//-----------------------------------------------------------------------------
/**
 * �G���J�E���g�f�[�^�Z�b�g�i�C�x���g�j
 *
 * @param	fsys				�t�B�[���h�V�X�e���|�C���^
 * @param	monsno				�����X�^�[�i���o�[
 * @param	level				���x��
 * @param	outBattleParam		�o�g���p�����|�C���^
 *
 * @return	none
 */
//-----------------------------------------------------------------------------
void SetWildEncountData(FIELDSYS_WORK *fsys, u16 monsno, u8 level,BATTLE_PARAM *outBattleParam)
{
	POKEMON_PARAM *param;
	ENC_FLD_SPA f_spa;		//����\��
	//�擪�|�P�����̃^�}�S�`�F�b�N
	{	
		POKEPARTY *my_party;
		my_party = SaveData_GetTemotiPokemon(fsys->savedata);
		param = PokeParty_GetMemberPointer(my_party, 0);	//�擪�|�P�����擾

		SetSpaStruct(fsys, param, NULL, &f_spa );
	}
	
	/*-�B�������̔���-*/
	/*-�C�x���g����Ă΂��쐶��́A-*/
	/*-���������{�f�B�[�A�V���N���A�ӂ�����-*/
	/*-��3���@�\����-*/
	EncountParamSet( monsno, level, POKEPARTY_ENEMY, &f_spa, param, outBattleParam );
	return;
}

//-----------------------------------------------------------------------------
/**
 * �G���J�E���g���邩�ǂ�����Ԃ��i�]�[���̃G���J�E���g�t���O�͔��肵�Ȃ��j
 *
 * @param	fsys				�t�B�[���h�V�X�e���|�C���^
 * @param	attr				�A�g���r���[�g
 *
 * @return	BOOL				TRUE: �G���J�E���g����	FALSE:�G���J�E���g���Ȃ�
 */
//-----------------------------------------------------------------------------
BOOL EncSet_CheckEncount( FIELDSYS_WORK * fsys, u8 attr  )
{
	int prob = 0;
	
	if (MATR_IsEncount(attr)){
		if (MATR_IsWater(attr)){			//��
			prob = GetEncountProbWater( fsys );
		}else{								//��
			prob = GetEncountProbGround( fsys );
		}
	}
	
	if (prob){
		return TRUE;
	}else{
		return FALSE;
	}
}

#ifdef PM_DEBUG
//----------------------------------------------------
//	�m�[�}��
//	����   : ENCOUNT_DATA * inData = �G���J�E���g�f�[�^
//			 u8 id             = �G���J�E���g�n�`
//			 u8 sp_check       = ����`�F�b�N
//	�߂�l : TRUE = ENCOUNT�@FALSE = NOT ENCOUNT
//----------------------------------------------------
BOOL DebugSetEncountData(	const ENCOUNT_DATA * inData,
							const u8 id,
							BATTLE_PARAM *outBattleParam)
{
	DebugEncountParamSet( 1, 10, POKEPARTY_ENEMY, outBattleParam );//�擪�̓^�}�S�ł͂Ȃ��Ƃ���

	return	TRUE;
}
#endif

//-----------------------------------------------------------------------------
/**
 * �n��G���J�E���g����Ԃ�
 *
 * @param	fsys				�t�B�[���h�V�X�e���|�C���^
 *
 * @return	int					�m��
 */
//-----------------------------------------------------------------------------
static int GetEncountProbGround(FIELDSYS_WORK * fsys)
{
	ENCOUNT_DATA *data;
	data = (ENCOUNT_DATA*)EventData_GetEncountData(fsys);
	return data->EncProbGround;
}

//-----------------------------------------------------------------------------
/**
 * ����G���J�E���g����Ԃ�
 *
 * @param	fsys				�t�B�[���h�V�X�e���|�C���^
 *
 * @return	int					�m��
 */
//-----------------------------------------------------------------------------
static int GetEncountProbWater(FIELDSYS_WORK * fsys)
{
	ENCOUNT_DATA *data;
	data = (ENCOUNT_DATA*)EventData_GetEncountData(fsys);
	return data->EncProbSea;
}

//-----------------------------------------------------------------------------
/**
 * �ނ�G���J�E���g����Ԃ�
 *
 * @param	fsys				�t�B�[���h�V�X�e���|�C���^
 * @param	inRodType			�ފ�
 *
 * @return	int					�m��
 */
//-----------------------------------------------------------------------------
static int GetEncountProbFishing(FIELDSYS_WORK * fsys, const FISHINGROD_TYPE inRodType)
{
	ENCOUNT_DATA *data;
	data = (ENCOUNT_DATA*)EventData_GetEncountData(fsys);
	switch(inRodType){
	case FISHINGROD_BAD:				//�{���ފ�
		return data->EncProbFish1;
	case FISHINGROD_GOOD:				//�����ފ�
		return data->EncProbFish2;
	case FISHINGROD_GREAT:				//�������ފ�
		return data->EncProbFish3;
	default:
		GF_ASSERT(0);
		return 0;
	}
}

//-----------------------------------------------------------------------------
/**
 * �w��^�C�v�̃|�P�����ƃG���J�E���g������
 *
 * @param	inData			���ʃG���J�E���g�f�[�^�e�[�u��
 * @param	inListNum		���X�g��
 * @param	type			�^�C�v
 * @param	outNo			�e�[�u���ԍ��i�[�o�b�t�@
 *
 * @return	BOOL		TRUE:����	FALSE:���s
 */
//-----------------------------------------------------------------------------
static BOOL FixPokeSet(const ENC_COMMON_DATA *inData, const u8 inListNum, const u8 type, u8 * outNo)
{
	u8 same_type[ENC_MONS_NUM_MAX];	//�w�肵���^�C�v�Ɠ����^�C�v�̃|�P�����̃G���J�E���g���X�g
	u8 cnt;				//�G���g���[������
	u8 i;
	u8 type1,type2;
	//������
	for (i=0;i<ENC_MONS_NUM_MAX;i++){
		same_type[i] = 0;
	}
	cnt = 0;
	
	//�w��^�C�v�ƃG���J�E���g���X�g���̃|�P�����̃^�C�v���r����
	for (i=0;i<inListNum;i++){
		type1 = PokePersonalParaGet( inData[i].MonsNo, ID_PER_type1 );
		type2 = PokePersonalParaGet( inData[i].MonsNo, ID_PER_type2 );
		if ( (type1 == type)||(type2 == type) ){
			//�����^�C�v�Ȃ烊�X�g�ɃG���g���[
			same_type[cnt++] = i; 
		}
	}
	//�G���J�E���g���X�g���Ɏw��^�C�v�����Ȃ��A�������́A���X�g���͑S�Ďw��^�C�v�Ȃ畁�ʂɃG���J�E���g������
	if ( (cnt == 0)||(cnt==inListNum) ){
		return FALSE;
	}
	*outNo = same_type[gf_rand()%cnt];//�w��^�C�v�̃|�P�������o��������(�m�����)
	return TRUE;
}

//-----------------------------------------------------------------------------
/**
 * �w��^�C�v�̃|�P�����ƃG���J�E���g������
 *
 * @param	inPokeParam		�|�P�����p����
 * @param	inFldSpa		�����`�F�b�N�E�t�H�����ύX�p�\���̂ւ̃|�C���^
 * @param	inData			���ʃG���J�E���g�f�[�^�e�[�u��
 * @param	inListNum		���X�g��
 * @param	type			�^�C�v
 * @param	tokusei			����
 * @param	outNo			�e�[�u���ԍ��i�[�o�b�t�@
 *
 * @return	BOOL		TRUE:����	FALSE:���s
 */
//-----------------------------------------------------------------------------
static BOOL CheckFixTypeEcnt(	POKEMON_PARAM *inPokeParam,
							const ENC_FLD_SPA *inFldSpa,
							const ENC_COMMON_DATA *inData,
							const u8 inListNum,
							const u8 type, const u8 tokusei,u8 * outNo)
{
	// �擪�̃|�P�������^�}�S�łȂ�
	if( inFldSpa->Egg == 0 ){
		if( inFldSpa->Spa == tokusei ){
			// 1/2�œ�������
			if( gf_p_rand(2) == 0 ){
				return FixPokeSet(inData, inListNum, type, outNo);
			}
		}
	}
	//�����������Ȃ�
	return FALSE;
}

//-----------------------------------------------------------------------------
/**
 * �G���J�E���g���ύX
 *
 * @param	IsFishing		�ނ肩�ǂ���
 * @param	inProb			�m��
 * @param	inFldSpa		�����`�F�b�N�E�t�H�����ύX�p�\���̂ւ̃|�C���^
 * @param	inWeatherCode	�V�C
 * @param	inPokeParam		�|�P�����p����
 *
 * @return	u8				�m��
 */
//-----------------------------------------------------------------------------
static u8 ChangeEncProb(	const BOOL inIsFishing,
							const u8 inProb,
							const ENC_FLD_SPA *inFldSpa,
							const u32 inWeatherCode,
							POKEMON_PARAM *inPokeParam	)
{
	int prob;

	prob = inProb;
	// �擪�̃|�P�������^�}�S�łȂ�
	if( inFldSpa->Egg == 0 ){
		if (inIsFishing){		//�ނ�
			//���イ�΂�A�˂񂿂Ⴍ�Ȃ�G���J�E���g��2�{
			if( (inFldSpa->Spa == TOKUSYU_NENTYAKU)||(inFldSpa->Spa == TOKUSYU_KYUUBAN) ){
				prob*2;
			}
		}else{					//�ނ�ȊO
			//���肶�����A�m�[�K�[�h�Ȃ�G���J�E���g��2�{
			//�������A���Ȃ�����Ȃ�1/2
			//���ᒆ�A�䂫������Ȃ�1/2
			//���낢����Ȃ�1/2
			//�͂₠���Ȃ�1/2
			if( (inFldSpa->Spa == TOKUSYU_ARIZIGOKU)||
				(inFldSpa->Spa == TOKUSYU_NOOGAADO)||
				(inFldSpa->Spa == TOKUSYU_HAKKOU) ){	//�����͉B�������ł͂���܂���
				prob*=2;
			}else if(inFldSpa->Spa == TOKUSYU_SUNAGAKURE){
				//�V��`�F�b�N(����)
				if(inWeatherCode == WEATHER_SYS_SANDSTORM){
					prob/=2;
				}
			}else if(inFldSpa->Spa == TOKUSYU_YUKIGAKURE){
				//�V��`�F�b�N�i��A����A�Ґ���j
				if ( (inWeatherCode == WEATHER_SYS_SNOW)||
					 (inWeatherCode == WEATHER_SYS_SNOWSTORM)||
					 (inWeatherCode == WEATHER_SYS_SNOWSTORM_H) ){
					prob/=2;
				}
			}else if( (inFldSpa->Spa == TOKUSYU_SIROIKEMURI)||
					  (inFldSpa->Spa == TOKUSYU_HAYAASI)||
					  (inFldSpa->Spa == TOKUSYU_AKUSYUU) ){		//���L�͉B�������ł͂���܂���
				prob/=2;
			}
		}

		if (prob>100){		//100%��������@100%�ɂ���
			prob = 100;
		}
	}
	
	return prob;
}

//-----------------------------------------------------------------------------
/**
 * ���x�����ɂ��퓬����i�B�������j
 *
 * @param	inFldSpa		�����`�F�b�N�E�t�H�����ύX�p�\���̂ւ̃|�C���^
 * @param	inMyPokeParam	�|�P�����p����
 * @param	inEneLv			����̃��x��
 *
 * @return	BOOL	TRUE:��𐬌�	FALSE:������s
 */
//-----------------------------------------------------------------------------
static BOOL CheckEcntCancelByLv( const ENC_FLD_SPA *inFldSpa, POKEMON_PARAM *inMyPokeParam, const u8 inEneLv)
{
	u8 my_poke_lv;
	//�L�����Z������ꍇ�͉�����Ȃ�
	if ( inFldSpa->EncCancelSpInvalid ){
		return FALSE;
	}
	
	if (inFldSpa->Egg == 0){
		if( (inFldSpa->Spa == TOKUSYU_SURUDOIME)||(inFldSpa->Spa == TOKUSYU_IKAKU) ){//����ǂ��߁A������
			//�莝���̃��x�����擾
			my_poke_lv = PokeParaGet(inMyPokeParam, ID_PARA_level, NULL);
			//�莝�������x���T�ȉ��̂Ƃ��͓�������
			if (my_poke_lv<=5){
				return FALSE;		//�퓬������Ȃ�
			}
			// ����LV�����莝��LV-�T
			if( inEneLv <= my_poke_lv-5 ){
				// 1/2�ŃG���J�E���g���
				if (gf_p_rand(2) == 0){
					return TRUE;		//�퓬���
				}
			}
		}
	}

	return FALSE;		//�퓬������Ȃ�
}

//-----------------------------------------------------------------------------
/**
 * �t�@�C�g�^�C�v�̌���
 *
 * @param	fsys			�t�B�[���h�V�X�e���|�C���^
 * @param	inSafariFlg		�T�t�@���t���O
 * @param	param			�o�g���p����
 *
 * @return	none
 */
//-----------------------------------------------------------------------------
static void SetFieldBattleParam(FIELDSYS_WORK * fsys, const BOOL inSatafiFlg, BATTLE_PARAM **param)
{
	if (!inSatafiFlg){
		//�o�g���p�����[�^�̃A���P�[�V�����ƃ|�P�����p�[�e�B�̏�����(�쐶��)
		(*param) = BattleParam_Create(HEAPID_WORLD, FIGHT_TYPE_1vs1_YASEI);
	}else {		//�T�t�@���t���O�����Ȃ�
		//�o�g���p�����[�^�̃A���P�[�V�����ƃ|�P�����p�[�e�B�̏�����(�T�t�@��)
		u16 * ball = Situation_GetSafariBallCount(SaveData_GetSituation(fsys->savedata));
		(*param) = BattleParam_CreateForSafari(HEAPID_WORLD, *ball);
	}
}

//-----------------------------------------------------------------------------
/**
 * �T�t�@������g�����X�^�[�̃Z�b�g
 *
 * @param	fsys			�t�B�[���h�V�X�e���|�C���^
 * @param	inSafariFlg		�T�t�@���t���O
 * @param	inBookGet		�S���}�ӓ���t���O
 * @param	enc_data		���ʃG���J�E���g�f�[�^�e�[�u��
 *
 * @return	none
 */
//-----------------------------------------------------------------------------

static void SetSfariMonster(FIELDSYS_WORK * fsys, const BOOL inSafariFlg, const BOOL inBookGet, ENC_COMMON_DATA *enc_data)
{
	if (inSafariFlg){	//�T�t�@���t���O�����Ȃ�
		//�T�t�@������g�̃|�P�����Z�b�g
		SafariEnc_SetSafariEnc(	EncDataSave_GetRandSeed(
								EncDataSave_GetSaveDataPtr(fsys->savedata), ENC_RND_SEED_SAFARI),
								inBookGet,
								fsys->location->zone_id,
								&enc_data[SP_ENC_1].MonsNo, &enc_data[SP_ENC_2].MonsNo);
	}
}

//-----------------------------------------------------------------------------
/**
 * �X�v���[�`�F�b�N
 *
 * @param	
 *
 * @return	BOOL	TRUE:�X�v���[����	FALSE:�X�v���[�s��
 */
//-----------------------------------------------------------------------------
static BOOL CheckSpray(const u8 inEneLv, const ENC_FLD_SPA *inSpa)
{
	if (inSpa->SprayCheck){
		//���x����r
		if (inSpa->SpMyLv > inEneLv){
			OS_Printf("�X�v���[���ʔ���\n");
			return TRUE;
		}
	}
	return FALSE;
}

//-----------------------------------------------------------------------------
/**
 * �ړ��|�P�����G���Z�b�g
 *
 * @param	
 *
 * @return	BOOL	TRUE:�G���J�E���g	FALSE:�G���J�E���g���Ȃ�
 */
//-----------------------------------------------------------------------------
static void SetMovePokemon(const u32 inTrainerID, MPD_PTR mpd, BATTLE_PARAM *outBattleParam)
{
	int monsno;
	u8 lv;
	u32 pow_rnd;
	u32 per_rnd;
	u32 cond;
	u16 hp;
	
	BOOL rc;
	POKEMON_PARAM *poke_param;
	
	poke_param = PokemonParam_AllocWork(HEAPID_FIELD);
	
	monsno = EncDataSave_GetMovePokeDataParam(mpd, MP_PARAM_MONSNO);
	lv = EncDataSave_GetMovePokeDataParam(mpd, MP_PARAM_LV);
	pow_rnd = EncDataSave_GetMovePokeDataParam(mpd, MP_PARAM_POW_RND);
	per_rnd = EncDataSave_GetMovePokeDataParam(mpd, MP_PARAM_PER_RND);
	cond = EncDataSave_GetMovePokeDataParam(mpd, MP_PARAM_COND);
	hp = EncDataSave_GetMovePokeDataParam(mpd, MP_PARAM_HP);

	PokeParaSetPowRnd( poke_param, monsno, lv, pow_rnd, per_rnd );
	
	PokeParaPut( poke_param, ID_PARA_id_no, &inTrainerID );		// �h�c
	PokeParaPut( poke_param, ID_PARA_condition, &cond );		// �R���f�B�V����
	PokeParaPut( poke_param, ID_PARA_hp,        &hp );		// HP

	//�A�C�e�����������Ă��Ȃ��̂ŁA���ڃA�b�h����
	rc = PokeParty_Add(outBattleParam->poke_party[POKEPARTY_ENEMY], poke_param);
	GF_ASSERT(rc&&"�|�P�����̒ǉ��Ɏ��s");
	sys_FreeMemoryEz(poke_param);
}

//-----------------------------------------------------------------------------
/**
 * �ړ��|�P�����G���J�E���g�`�F�b�N
 *
 * @param	
 *
 * @return	BOOL	TRUE:�G���J�E���g	FALSE:�G���J�E���g���Ȃ�
 */
//-----------------------------------------------------------------------------
static BOOL CheckMovePokeEnc(FIELDSYS_WORK * fsys, MPD_PTR *outMpd)
{
	ENC_SV_PTR data;
	MPD_PTR temp[MOVE_POKE_MAX];
	u8 enc_count;
	u8 i;
	int zone;

	//�����ꏊ�ɂ���ړ��|�P�������擾
	enc_count = 0;
	data = EncDataSave_GetSaveDataPtr(fsys->savedata);
	for(i=0;i<MOVE_POKE_MAX;i++){
		zone = MP_GetMovePokeZone(EncDataSave_GetMovePokeZoneIdx(data,i));
		if( EncDataSave_IsMovePokeValid(data,i)&&
				(zone == fsys->location->zone_id) ){
			temp[enc_count] = EncDataSave_GetMovePokeDataPtr(data, i);
			enc_count++;
		}
	}

	if (enc_count == 0){
		return FALSE;			//�ړ��|�P�������Ȃ�
	}else{
		//����ꍇ�A5���ŃG���J�E���g
		if ( gf_p_rand(2) == 0 ){
			return FALSE;
		}
	}
	
	if (enc_count>1){
		//�����_���őI�o
		(*outMpd)  = temp[ gf_p_rand(enc_count) ];
	}else{
		//1�C�������Ȃ��̂Ŋm��
		(*outMpd)  = temp[0];
	}

	return TRUE;
}

//-----------------------------------------------------------------------------
/**
 * �퓬����|�P�������o�g���p�����ɒǉ�
 *
 * @param	inTarget			�ǉ��Ώ�
 * @param	inFldSpa			�����`�F�b�N�E�t�H�����ύX�p�\���̂ւ̃|�C���^
 * @param	ioPokeParam			�|�P�����p����
 * @param	ioBattleParam		�o�g���p����
 *
 * @return	BOOL		�|�P�p�[�e�B�ǉ�����
 */
//-----------------------------------------------------------------------------
static BOOL AddPokemonParam(const int inTarget, const ENC_FLD_SPA *inFldSpa,
							POKEMON_PARAM *ioPokeParam, BATTLE_PARAM *ioBattleParam )
{
	int range = ITEM_RANGE_NORMAL;
	//�����ӂ�����`�F�b�N
	if (inFldSpa->Egg == 0){
		if (inFldSpa->Spa == TOKUSYU_HUKUGAN){
			range = ITEM_RANGE_HUKUGAN;
		}
	}
	
	PokeItemSet(ioPokeParam, ioBattleParam->fight_type , range);

	//�t�H�����ύX
	{
		u8 change_flg;
		u8 form_no;
		int monsno;
		change_flg = 0;
		monsno = PokeParaGet( ioPokeParam, ID_PARA_monsno, NULL );
		//�t�H�����ύX�f�[�^�͊m���œ����Ă��邪�A����A�ω����邩���Ȃ����̂Q���Ȃ̂ŁA0�łȂ���΁A�ύX����
		if (monsno == MONSNO_SIIUSI ){
			change_flg = 1;
			if (!inFldSpa->FormProb[0]){
				form_no = FORMNO_SII_WEST;	//�����f�t�H���g
				OS_Printf("��\n");
			}else{
				form_no = FORMNO_SII_EAST;	//�����t�H�����ύX
				OS_Printf("��\n");
			}
		}else if(monsno == MONSNO_SIIDORUGO){
			change_flg = 1;
			if (!inFldSpa->FormProb[1]){
				form_no = FORMNO_SII_WEST;	//�����f�t�H���g
			}else{
				form_no = FORMNO_SII_EAST;	//�����t�H�����ύX
			}
		}else if(monsno == MONSNO_ANNOON){
			u8 num;
			change_flg = 1;
			//�o���^�C�v���擾
			num = ANNOON_Table[ inFldSpa->AnnoonTblType ].Num;
			form_no = ANNOON_Table[ inFldSpa->AnnoonTblType ].Tbl[ gf_rand()%num ];
		}

		if (change_flg){
			PokeParaPut(ioPokeParam,ID_PARA_form_no,(u8 *)&form_no);
		}

	}
	return PokeParty_Add(ioBattleParam->poke_party[inTarget], ioPokeParam);
}

//�n��폈���F�w�肵���e�[�u���ԍ��̎����|�P�����̒��ň�ԃ��x���̍����e�[�u���ԍ���Ԃ�(�B����������)
//-----------------------------------------------------------------------------
/**
 * �n��폈���F�w�肵���e�[�u���ԍ��̎����|�P�����̒��ň�ԃ��x���̍����e�[�u���ԍ���Ԃ�(�B����������)

 *
 * @param	inEncCommonData		���ʃG���J�E���g�f�[�^�e�[�u��
 * @param	inFldSpa			�����`�F�b�N�E�t�H�����ύX�p�\���̂ւ̃|�C���^
 * @param	inTblNo				�e�[�u���i���o�[
 *
 * @return	u8					�ύX��e�[�u���i���o�[
 */
//-----------------------------------------------------------------------------
static u8 GetMaxLvMonsTblNo(const ENC_COMMON_DATA *inEncCommonData, const ENC_FLD_SPA *inFldSpa, const u8 inTblNo)
{
	u8 tbl_no;
	u8 i;
	if (inFldSpa->Egg == 0){
		//��邫�A�͂肫��A�v���b�V���[ ���������`�F�b�N���x���̍����|�P�����ƂT���ŃG���J�E���g
		if ( (inFldSpa->Spa == TOKUSYU_YARUKI)||
			 (inFldSpa->Spa == TOKUSYU_HARIKIRI)||
			 (inFldSpa->Spa == TOKUSYU_PURESSYAA) ){
			
			//5���Ŕ���
			if (gf_p_rand(2) == 0){
				return inTblNo;			//����������
			}
			
			//�e�[�u���ԍ��ۑ�
			tbl_no = inTblNo;
			//���������X�^�[�i���o�[�̃e�[�u��������
			for(i=0;i<ENC_MONS_NUM_NORMAL;i++){
				if (inEncCommonData[i].MonsNo == inEncCommonData[tbl_no].MonsNo){ //���������X�^�[�i���o�[���H
					//���x����r
					if (inEncCommonData[i].LvMax > inEncCommonData[tbl_no].LvMax){
						//�e�[�u���ԍ��̍X�V
						tbl_no = i;
					}
				}
			}
			return tbl_no;
		}
	}

	return inTblNo;
}

//-----------------------------------------------------------------------------
/**
 * �����A�X�v���[�`�F�b�N�Ȃǂ̏����W�v���č\���̂ɃZ�b�g

 *
 * @param	fsys			�t�B�[���h�V�X�e���|�C���^
 * @param	inPokeParam		�����̃|�P�����p����
 * @param	inData			�G���J�E���g�f�[�^
 * @param	outSpa			���\���̃|�C���^
 *
 * @return	none
 */
//-----------------------------------------------------------------------------
static void SetSpaStruct(FIELDSYS_WORK *fsys, POKEMON_PARAM *inPokeParam, ENCOUNT_DATA* inData, ENC_FLD_SPA *outSpa  )
{
	//�擪�|�P�����̃^�}�S�`�F�b�N
	if( PokeParaGet( inPokeParam, ID_PARA_tamago_flag, NULL ) == 0 ){
		// �擪�̃|�P�������^�}�S�łȂ�
		outSpa->Egg = 0;
		outSpa->Spa = PokeParaGet(inPokeParam, ID_PARA_speabino, NULL);	// ����\�͎擾
	}else{
		// �擪�̃|�P�������^�}�S
		outSpa->Egg = 1;
		outSpa->Spa = TOKUSYU_MAX;
	}

	outSpa->SpMyLv = 0;
	outSpa->SprayCheck = FALSE;
	outSpa->EncCancelSpInvalid = FALSE;
	
	if (inData != NULL){
		//�V�[�E�V�E�V�[�h���S�t�H�����ύX�m���Z�b�g
		outSpa->FormProb[0] = inData->FormProb[0];	//�V�[�E�V
		outSpa->FormProb[1] = inData->FormProb[1];	//�V�[�h���S
		//�A���m�[��
		if (inData->AnnoonTable != 0){
			GF_ASSERT(inData->AnnoonTable<=8&&"annoon_table_over");
			//�A���m�[���e�[�u���^�C�v�Z�b�g
			outSpa->AnnoonTblType = inData->AnnoonTable-1;
		}else{
			outSpa->AnnoonTblType = 0;
		}
	}
	//�g���[�i�[�h�c�̃Z�b�g
	outSpa->TrainerID = MyStatus_GetID( SaveData_GetMyStatus(fsys->savedata) );
	
}

#ifdef PM_DEBUG

//-----------------------------------------------------------------------------
/**
 * �ނ�G���J�E���g
 * ���T�t�@���ɂ����Ƃ��Ă��A�ނł͓���g�������̂ŁA�T�t�@�������X�^�[�̃Z�b�g�͍s��Ȃ�
 *
 * @param	fsys				�t�B�[���h�V�X�e���|�C���^
 * @param	inRodtype			�ނ��
 *
 * @return	BOOL
 */
//-----------------------------------------------------------------------------
BOOL DebugSetFishingEncount( FIELDSYS_WORK * fsys, const u8 inRodType )
{
	BATTLE_PARAM * battle_param;
	POKEMON_PARAM *poke_param;
	POKEPARTY *my_party;
	BOOL safari_flg;		//�T�t�@���t���O

	ENC_COMMON_DATA enc_data[ENC_MONS_NUM_MAX];
	ENC_FLD_SPA f_spa;		//����\��

	{
		u8 prob;
#ifdef PM_DEBUG
		if (DebugFishProbFlg){
			prob = 100;
		}else{
			// �G���J�E���g��
			prob = GetEncountProbFishing(fsys, inRodType);
		}
#else
		// �G���J�E���g��
		prob = GetEncountProbFishing(fsys, inRodType);
#endif
		if(  prob == 0 ){
			return FALSE;		//�m����0
		}

		//�莝���|�P�p�[�e�B�擾
		my_party = SaveData_GetTemotiPokemon(fsys->savedata);
		poke_param = PokeParty_GetMemberPointer(my_party, 0);	//�擪�|�P�����擾
		SetSpaStruct(fsys, poke_param, NULL, &f_spa );
	
		//�ނ�ł́A�X�v���[�`�F�b�N�����Ȃ�
	
		//�����ɂ���ăG���J�E���g���ύX
		prob = ChangeEncProb(	TRUE, prob, &f_spa,
								Situation_GetWeatherID(SaveData_GetSituation(fsys->savedata)),
								poke_param	);
		//�m���ŃG���J�E���g
		if (gf_p_rand(100) >= prob){
			return FALSE;		//�G���J�E���g���Ȃ�
		}
	}
	//�T�t�@���t���O���擾
	safari_flg = SysFlag_SafariCheck(SaveData_GetEventWork(fsys->savedata));

	//�o�g���p�����[�^�Z�b�g
	SetFieldBattleParam(fsys, safari_flg, &battle_param);
	//�莝���|�P�����ȂǃZ�b�g
	BattleParam_SetParamByGameData(battle_param, fsys);


	if ( (ZoneData_IsSpFishingZone(fsys->location->zone_id))&&
			 SpFishing_CheckPoint(fsys) ){
		//����ނ�f�[�^�쐬
		u8 i;
		int monsno;
		u8 max,min;
		SpFishing_GetMaxMinLv(&max, &min);
		SpFishing_GetMonsNo(&monsno);
		
		for(i=0;i<ENC_MONS_NUM_FISH;i++){
			enc_data[i].MonsNo = monsno;
			enc_data[i].LvMax = max;
			enc_data[i].LvMin = min;
		}
	}else{
		//���ʃG���J�E���g�f�[�^�쐬
		{
			NON_GROUND_ENC_MONSTER_DAT *enc_fish;
			u8 i;
			ENCOUNT_DATA *data;

			data = (ENCOUNT_DATA*)EventData_GetEncountData(fsys);	
		
			//�ނ�ƕʂɃf�[�^�쐬
			switch(inRodType){
			case FISHINGROD_BAD:		//�{��
				enc_fish = data->EncFish1;
				break;
			case FISHINGROD_GOOD:		//����
				enc_fish = data->EncFish2;
				break;
			case FISHINGROD_GREAT:		//������
				enc_fish = data->EncFish3;
				break;
			}
		
			for(i=0;i<ENC_MONS_NUM_FISH;i++){
				enc_data[i].MonsNo = enc_fish[i].MonsterNo;
				enc_data[i].LvMax = enc_fish[i].MaxLevel;
				enc_data[i].LvMin = enc_fish[i].MinLevel;
			}	
		}
	}

	//�ނ�G���J�E���g
	{
		BOOL rc;
		rc = FishingEncSingle( fsys, poke_param, battle_param, enc_data, &f_spa, inRodType );
		if (!rc){
			return FALSE;
		}
	}
	
	return TRUE;
}

#endif


