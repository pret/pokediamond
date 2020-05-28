//============================================================================================
/**
 * @file	exindexdata.c
 * @bfief	�O���Q�ƃt�@�C���̍쐬
 * @author	Satoshi Mitsuhara
 * @date	06.07.30
 *
 * $Id: exindexdata.c,v 1.3 2006/08/02 12:08:42 mitsuhara Exp $
 */
//============================================================================================
#include "common.h"
#include "savedata/savedata.h"
#include "savedata/zukanwork.h"
#include "savedata/system_data.h"

#include "field/eventflag.h"
#include "field/evwkdef.h"
#include "../field/sysflag_def.h"

#include "field/location.h"
#include "field/situation.h"

#include "poketool/poke_tool.h"
#include "poketool/pokeparty.h"
#include "poketool/boxdata.h"

#include "itemtool/myitem.h"

#ifdef CREATE_INDEX

void CreateIndexData(int heapid);

typedef struct {
  // �Z�[�u�f�[�^�̍\���̂�src/savedata/saveload_system.c�ɂ���̂ŎQ�Ƃ��鎖
  // ���SAVEDATA.SAVEWORK�̍\�����`

  // SAVEDATA����̊e�Z�[�u���ڂ̃I�t�Z�b�g
  // ���������e�\���̂̓��e�͌Œ肪�ۏႳ��Ă��Ȃ����߁A�����œ���ꂽ�|�C���^��
  // �@���ɍ\���̂𒼐ڃA�N�Z�X���鎞�ɂ͌݊����ɒ��ӂ����Ă��������I
  u32 savework_offset[GMDATA_ID_MAX];

  // ��������������p���[�N�Q�Ɨp(GMDATA_ID_ZUKANWORK����̃I�t�Z�b�g)
  // ������������Ă��邩�t���O�̃I�t�Z�b�g
  u32 zukan_get_offset;
  // ���񂱂������񃂁[�h���̃t���O�̃I�t�Z�b�g
  u32 zenkoku_flag_offset;
  // ������F�߂܂����t���O�p���[�N�̃I�t�Z�b�g
  u32 get_flag_offset;
  // ������F�������t���O�p���[�N�̃I�t�Z�b�g
  u32 see_flag_offset;
  // ������F�I�X���X�t���O�p���[�N�̃I�t�Z�b�g
  u32 sex_flag_offset;

  // ���������Q�[���̐i�s�󋵎Q�Ɨp(GMDATA_ID_EVENT_WORK����̃I�t�Z�b�g)
  // �Q�[���t���O�Q�Ɨp
  u32 game_flag_offset;
  // �Q�[���N���A�t���O�̔ԍ�(u8 game_flag_offset[game_clear_flag / 8])
  u32 game_clear_flag;
  // �o�b�O����肵�����t���O
  u32 game_bag_flag;

  // ���������|�P�����Z���^�[�ŃZ�[�u���Ă邩�𓾂邽�߂̕z��
  // �|�P�����Z���^�[�ŃZ�[�u���Ă��邩�𒲂ׂ���@
  // ���L��situation_offset����Z�[�u����LOCATION_WORK�\���̂ւ̃|�C���^�𓾂�
  // ���̒��ɂ���zone_id���Z�[�u�����ۂ̃}�b�v�Ǘ�ID�ɂȂ�܂��B
  // zone_id��ZONE_ID_???PC0101�`ZONE_ID_???PC0103�Ȃ�΃|�P�����Z���^�[�ł��B
  // �S����51�}�b�v�Ɣ�r����K�v������܂��B
  // ���Q�ƃt�@�C��
  // src/field/situation.c��LOCATION_WORK now�����o
  // src/fielddata/maptable/zone_id.h
  // ���ugrep PC src/fielddata/maptable/zone_id.h�v
  u32 situation_now_offset;

  // ���������������
  // MYSTATUS�ւ̃I�t�Z�b�g
  //  u32 mystatus_offset; �� �����savework_offset[GMDATA_ID_PLAYER_DATA]�Ɠ���
  // �v���C���[�̖��O�ւ̃I�t�Z�b�g
  u32 mystatus_name_offset;
  // �v���C���[��ID
  u32 mystatus_id_offset;
  // �v���C���[�̐���
  u32 mystatus_sex_offset;
  
  // ���������莝���|�P�����֘A
  // �莝���|�P������POKEPARTY�\���̂ŊǗ�����Ă���
  // u32 pokeparty_offset; �� �����savework_offset[GMDATA_ID_TEMOTI_POKE]�Ɠ���
  // �莝���̃|�P������
  u32 pokecount_offset;
  // �莝���|�P�����ւ̃I�t�Z�b�g(POKEMON_PARAM��TEMOTI_POKEMAX��)
  u32 pokemon_member_offset;
  // sizeof(POKEMON_PARAM) �������ύX�Ȃ��Ǝv�����ǔO�̂���
  u32 sizeof_pokemon_param;

  // ���莝���A�C�e���֘A
  // u32 myitem_offset; �� �����savework_offset[GMDATA_ID_TEMOTI_ITEM]�Ɠ���
  // sizeof(MINEITEM)
  u32 sizeof_mineitem;
  // ����|�P�b�g�ő吔
  u32 bag_normal_item_max;
  // ��؂ȕ��|�P�b�g�ő吔
  u32 bag_event_item_max;
  // �Z�}�V���|�P�b�g�ő吔
  u32 bag_waza_item_max;
  // �V�[���|�P�b�g�ő吔
  u32 bag_seal_item_max;
  // ��|�P�b�g�ő吔
  u32 bag_drug_item_max;
  // �؂̎��|�P�b�g�ő吔
  u32 bag_nuts_item_max;
  // �����X�^�[�{�[���|�P�b�g�ő吔
  u32 bag_ball_item_max;
  // �퓬�p�A�C�e���|�P�b�g�ő吔
  u32 bag_battle_item_max;
  // ����|�P�b�g�ւ̃I�t�Z�b�g
  u32 bag_normal_item_offset;
  // ��؂ȕ��|�P�b�g�ւ̃I�t�Z�b�g
  u32 bag_event_item_offset;
  // �Z�}�V���|�P�b�g�ւ̃I�t�Z�b�g
  u32 bag_waza_item_offset;
  // �V�[���|�P�b�g�ւ̃I�t�Z�b�g
  u32 bag_seal_item_offset;
  // ��|�P�b�g�ւ̃I�t�Z�b�g
  u32 bag_drug_item_offset;
  // �؂̎��|�P�b�g�ւ̃I�t�Z�b�g
  u32 bag_nuts_item_offset;
  // �����X�^�[�{�[���|�P�b�g�ւ̃I�t�Z�b�g
  u32 bag_ball_item_offset;
  // �퓬�p�A�C�e���|�P�b�g�ւ̃I�t�Z�b�g
  u32 bag_battle_item_offset;
  
  // ���������{�b�N�X�֘A
  // �p�\�R���ɗa���Ă���|�P������POKEMON_PASO_PARAM�ŊǗ�����Ă���(�����ς��Ȃ����ǔO�̂���)
  // u32 box_data_offset; �� �����savework_offset[GMDATA_ID_BOXDATA]�Ɠ���
  // �{�b�N�X�̃g���C��
  u32 box_data_tray_max;
  // �{�b�N�X���̐擪�ւ̃I�t�Z�b�g
  u32 box_data_offset;
  // sizeof(POKEMON_PASO_PARAM) �������ύX�Ȃ��Ǝv�����ǔO�̂���
  u32 sizeof_pokemon_paso_param;

  // ��������Wi-Fi�֘A
  // ���O�C���pGameSpyID�������Ă���ꏊ
  // �������O���\�t�g�œ����ID�𗘗p�������ꍇ�ɎQ�Ƃ���\��������܂�
  // �Ȃ��A���������͐�΂ɕs�I����I��"READ-ONLY"�ł�
  // u32 system_data_offset; �� �����savework_offset[GMDATA_ID_SYSTEM_DATA]�Ɠ���
  // GTS�EWifi�o�g���^���[���O�C���pGameSpyID�i���߂Ď擾����GameSpyId��ۑ�����j
  u32 profile_id_offset;
  
} EXINDEX;


// �O���֐���`
extern LOCATION_WORK * Situation_GetNowLocation(SITUATION * st);


//------------------------------------------------------------------
/**
 * @brief	���Q�[���p�C���f�b�N�X�����쐬����֐�
 * @param	NONE
 * @return	NONE
 * �� �Ăяo���ꂽ��͖������[�v�ɂĒ�~
 */
//------------------------------------------------------------------
void CreateIndexData(int heapid)
{
  u32 uval1;
  void *up1, *up2;
  int i, ival1;

  SAVEDATA *sv;
  EXINDEX *ex;

  ex = sys_AllocMemory(heapid, sizeof(EXINDEX));

  sv = SaveData_GetPointer();

  // �e�Z�[�u���ڂւ̃I�t�Z�b�g���Z�b�g
  up2 = SaveData_Get(sv, 0);
  for(i = 0; i < GMDATA_ID_MAX; i++){
    up1 = SaveData_Get(sv, i);	// up1 = absolute address
    ex->savework_offset[i] = (u32)up1 - (u32)up2;
  }

  // ������������Ă��邩�̃t���O�ʒu
  up1 = SaveData_Get(sv, GMDATA_ID_ZUKANWORK);
  ex->zukan_get_offset = (u32)Index_Get_Zukan_Offset(up1) - (u32)up1;
  ex->zenkoku_flag_offset = (u32)Index_Get_Zenkoku_Zukan_Offset(up1) - (u32)up1;
  ex->get_flag_offset = (u32)Index_Get_Get_Flag_Offset(up1) - (u32)up1;
  ex->see_flag_offset = (u32)Index_Get_See_Flag_Offset(up1) - (u32)up1;
  ex->sex_flag_offset = (u32)Index_Get_Sex_Flag_Offset(up1) - (u32)up1;

  // �Q�[���t���O�֘A
  up1 = SaveData_Get(sv, GMDATA_ID_EVENT_WORK);
  ex->game_flag_offset = (u32)EventWork_GetEventFlagAdrs(up1, 1) - (u32)up1;
  ex->game_clear_flag = SYS_FLAG_GAME_CLEAR;
  ex->game_bag_flag = SYS_FLAG_BAG_GET;

  // �Z�[�u�����ꏊ�𓾂�(�|�P�����Z���^�[�ŃZ�[�u�������̔�r�p)
  up1 = SaveData_Get(sv, GMDATA_ID_SITUATION);
  ex->situation_now_offset = (u32)Situation_GetNowLocation(up1) - (u32)up1;

  // MYSTATUS�֘A
  up1 = SaveData_Get(sv, GMDATA_ID_PLAYER_DATA);
  ex->mystatus_name_offset = (u32)Index_Get_Mystatus_Name_Offset(up1) - (u32)up1;
  ex->mystatus_id_offset = (u32)Index_Get_Mystatus_Id_Offset(up1) - (u32)up1;
  ex->mystatus_sex_offset = (u32)Index_Get_Mystatus_Sex_Offset(up1) - (u32)up1;

  // �莝���|�P�����֘A
  up1 = SaveData_Get(sv, GMDATA_ID_TEMOTI_POKE);
  ex->pokecount_offset = (u32)Index_Get_PokeCount_Offset(up1) - (u32)up1;
  ex->pokemon_member_offset = (u32)PokeParty_GetMemberPointer(up1, 0) - (u32)up1;
  ex->sizeof_pokemon_param = PokemonParam_GetWorkSize();

  // �A�C�e���֘A
  up1 = SaveData_Get(sv, GMDATA_ID_TEMOTI_ITEM);
  ex->sizeof_mineitem = sizeof(MINEITEM);
  ex->bag_normal_item_max = BAG_NORMAL_ITEM_MAX;
  ex->bag_event_item_max = BAG_EVENT_ITEM_MAX;
  ex->bag_waza_item_max = BAG_WAZA_ITEM_MAX;
  ex->bag_seal_item_max = BAG_SEAL_ITEM_MAX;
  ex->bag_drug_item_max = BAG_DRUG_ITEM_MAX;
  ex->bag_nuts_item_max = BAG_NUTS_ITEM_MAX;
  ex->bag_ball_item_max = BAG_BALL_ITEM_MAX;
  ex->bag_battle_item_max = BAG_BATTLE_ITEM_MAX;
  ex->bag_normal_item_offset = (u32)Index_Get_Myitem_Offset(up1, BAG_POKE_NORMAL) - (u32)up1;
  ex->bag_event_item_offset =  (u32)Index_Get_Myitem_Offset(up1, BAG_POKE_EVENT) - (u32)up1;
  ex->bag_waza_item_offset = (u32)Index_Get_Myitem_Offset(up1, BAG_POKE_WAZA) - (u32)up1;
  ex->bag_seal_item_offset = (u32)Index_Get_Myitem_Offset(up1, BAG_POKE_SEAL) - (u32)up1;
  ex->bag_drug_item_offset = (u32)Index_Get_Myitem_Offset(up1, BAG_POKE_DRUG) - (u32)up1;
  ex->bag_nuts_item_offset = (u32)Index_Get_Myitem_Offset(up1, BAG_POKE_NUTS) - (u32)up1;
  ex->bag_ball_item_offset = (u32)Index_Get_Myitem_Offset(up1, BAG_POKE_BALL) - (u32)up1;
  ex->bag_battle_item_offset = (u32)Index_Get_Myitem_Offset(up1, BAG_POKE_BATTLE) - (u32)up1;

  // �{�b�N�X�֘A
  up1 = SaveData_Get(sv, GMDATA_ID_BOXDATA);
  ex->box_data_tray_max = BOX_MAX_TRAY;
  ex->box_data_offset = (u32)BOXDAT_GetPokeDataAddress(up1, 0, 0) - (u32)up1;
  ex->sizeof_pokemon_paso_param = PokemonPasoParamSizeGet();

  // Wi-Fi�֘A
  up1 = SaveData_Get(sv, GMDATA_ID_SYSTEM_DATA);
  ex->profile_id_offset = (u32)Index_Get_Profile_Offset(up1) - (u32)up1;
  
  OS_TPrintf("�O��Index: %08X - %08X\n", ex, (u32)ex + sizeof(EXINDEX));
  OS_TPrintf("zukan_get_offset = %08X\n", &ex->zukan_get_offset);
  OS_TPrintf("game_flag_offset = %08X\n", &ex->game_flag_offset);
  OS_TPrintf("mystatus_name_offset = %08X\n", &ex->mystatus_name_offset);
  OS_TPrintf("pokecount_offset = %08X\n", &ex->pokecount_offset);
  OS_TPrintf("sizeof_mineitem = %08X\n", &ex->sizeof_mineitem);
  OS_TPrintf("box_data_tray_max = %08X\n", &ex->box_data_tray_max);
  OS_TPrintf("profile_id_offset = %08X\n", &ex->profile_id_offset);
  
  // �����I��
  OS_Terminate();
}

/*  */

#endif	// CREATE_INDEX
