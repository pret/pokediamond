//============================================================================================
/**
 * @file	savedata.c
 * @brief	�Z�[�u�f�[�^�Ǘ�
 * @author	tamada	GAME FREAK Inc.
 * @date	2005.10.12
 *
 * @li		2006.04.17	�Z�[�u���[�h�V�X�e����saveload_system.c�ɕ���
 */
//============================================================================================

#include "common.h"
#include "gflib/system.h"


#include "system/gamedata.h"

#include "savedata/savedata.h"
#include "savedata_local.h"


//�Z�[�u�f�[�^���e�������̂ɕK�v�Ȋ֐��Q�Ƃ̂��߂̃w�b�_

#include "poketool/poke_tool.h"
#include "../poketool/poke_tool_def.h"

#include "savedata/system_data.h"
#include "playerdata_local.h"
#include "poketool/pokeparty.h"
#include "itemtool/myitem.h"
#include "field/eventflag.h"
#include "field/poketch_data.h"
#include "field/situation.h"
#include "savedata/zukanwork.h"
#include "savedata/sodateyadata.h"
#include "savedata/friendlist.h"
#include "savedata/undergrounddata.h"
#include "savedata/regulation.h"
#include "savedata/imageclip_data.h"
#include "savedata/honeytree_data.h"
#include "savedata/wifilist.h"
#include "savedata/randomgroup.h"
#include "savedata/fnote_mem.h"
#include "savedata/trainercard_data.h"
#include "savedata/wifihistory.h"

#include "savedata/mail_util.h"
#include "savedata/poruto_util.h"
#include "poketool/boxdata.h"
#include "savedata/record.h"
#include "savedata/guinness.h"

#include "savedata/custom_ball.h"
#include "savedata/contest_savedata.h"

#include "savedata/misc.h"
#include "misc_local.h"

#include "savedata/perapvoice.h"
#include "savedata/perapvoice_local.h"
#include "savedata/b_tower.h"
#include "savedata/b_tower_local.h"

#include "savedata/sp_ribbon.h"
#include "savedata/dendou_data.h"
#include "savedata/encount.h"
#include "savedata/fushigi_data.h"
#include "savedata/worldtrade_data.h"
#include "savedata/tv_work.h"
#include "savedata/pokepark_data.h"
#include "system/pms_word.h"


//=============================================================================
//=============================================================================

//============================================================================================
//
//
//		�����f�[�^
//
//
//============================================================================================
//---------------------------------------------------------------------------
/**
 * @brief	�Z�[�u�f�[�^���e��`
 */
//---------------------------------------------------------------------------
const SAVEDATA_TABLE SaveDataTable[] = {
//�m�[�}���f�[�^�O���[�v
	{	//�V�X�e���f�[�^
		GMDATA_ID_SYSTEM_DATA,
		SVBLK_ID_NORMAL,
		(FUNC_GET_SIZE)SYSTEMDATA_GetWorkSize,
		(FUNC_INIT_WORK)SYSTEMDATA_Init,
	},
	{	//�v���C���[�f�[�^
		GMDATA_ID_PLAYER_DATA,
		SVBLK_ID_NORMAL,
		(FUNC_GET_SIZE)PLAYERDATA_GetWorkSize,
		(FUNC_INIT_WORK)PLAYERDATA_Init,
	},
	{	//�莝���|�P����
		GMDATA_ID_TEMOTI_POKE,
		SVBLK_ID_NORMAL,
		(FUNC_GET_SIZE)PokeParty_GetWorkSize,
		(FUNC_INIT_WORK)PokeParty_InitWork,
	},
	{	//�莝���ǂ���
		GMDATA_ID_TEMOTI_ITEM,
		SVBLK_ID_NORMAL,
		(FUNC_GET_SIZE)MyItem_GetWorkSize,
		(FUNC_INIT_WORK)MyItem_Init,
	},
	{	//�C�x���g���[�N
		GMDATA_ID_EVENT_WORK,
		SVBLK_ID_NORMAL,
		(FUNC_GET_SIZE)EventWork_GetWorkSize,
		(FUNC_INIT_WORK)EventWork_Init,
	},
	{	//�|�P�b�`�f�[�^
		GMDATA_ID_POKETCH_DATA,
		SVBLK_ID_NORMAL,
		(FUNC_GET_SIZE)PoketchData_GetWorkSize,
		(FUNC_INIT_WORK)PoketchData_Init,
	},
	{	//�󋵃f�[�^
		GMDATA_ID_SITUATION,
		SVBLK_ID_NORMAL,
		(FUNC_GET_SIZE)Situation_GetWorkSize,
		(FUNC_INIT_WORK)Situation_Init,
	},
	{	//������f�[�^
		GMDATA_ID_ZUKANWORK,
		SVBLK_ID_NORMAL,
		(FUNC_GET_SIZE)ZukanWork_GetWorkSize,
		(FUNC_INIT_WORK)ZukanWork_Init,
	},
	{	//��ĉ��f�[�^
		GMDATA_ID_SODATEYA,
		SVBLK_ID_NORMAL,
		(FUNC_GET_SIZE)SodateyaWork_GetWorkSize,
		(FUNC_INIT_WORK)SodateyaWork_Init,
	},
	{	//���肠���O���[�v
		GMDATA_ID_FRIEND,
		SVBLK_ID_NORMAL,
		(FUNC_GET_SIZE)FriendList_GetWorkSize,
		(FUNC_INIT_WORK)FriendList_Init,
	},
	{	//���̑��f�[�^
		GMDATA_ID_MISC,
		SVBLK_ID_NORMAL,
		(FUNC_GET_SIZE)MISC_GetWorkSize,
		(FUNC_INIT_WORK)MISC_Init,
	},
	{	//�t�B�[���hOBJ�Z�[�u
		GMDATA_ID_FIELDOBJSV,
		SVBLK_ID_NORMAL,
		(FUNC_GET_SIZE)FieldObjSv_GetWorkSize,
		(FUNC_INIT_WORK)FieldObjSv_Init,
	},
	{	//�n���A�C�e���f�[�^+�閧��n�f�[�^
		GMDATA_ID_UNDERGROUNDDATA,
		SVBLK_ID_NORMAL,
		(FUNC_GET_SIZE)UnderGroundData_GetWorkSize,
		(FUNC_INIT_WORK)UnderGroundData_Init,
	},
    {  // ���M�����[�V�����f�[�^
        GMDATA_ID_REGULATION,
		SVBLK_ID_NORMAL,
		(FUNC_GET_SIZE)RegulationData_GetWorkSize,
		(FUNC_INIT_WORK)RegulationData_Init,
    },
	{	//�C���[�W�N���b�v�̃f�[�^
		GMDATA_ID_IMAGECLIPDATA,
		SVBLK_ID_NORMAL,
		(FUNC_GET_SIZE)ImcSaveData_GetWorkSize,
		(FUNC_INIT_WORK)ImcSaveData_Init,
	},
	{	//���[���̃f�[�^
		GMDATA_ID_MAILDATA,
		SVBLK_ID_NORMAL,
		(FUNC_GET_SIZE)MAIL_GetBlockWorkSize,
		(FUNC_INIT_WORK)MAIL_Init,
	},
	{	//�|���g�̃f�[�^
		GMDATA_ID_PORUTODATA,
		SVBLK_ID_NORMAL,
		(FUNC_GET_SIZE)PORUTO_GetSaveWorkSize,
		(FUNC_INIT_WORK)PORUTO_Init,
	},
	{	// �����̎�O���[�v
		GMDATA_ID_RANDOMGROUP,
		SVBLK_ID_NORMAL,
		(FUNC_GET_SIZE)RandomGroup_GetWorkSize,
		(FUNC_INIT_WORK)RandomGroup_Init,
	},
	{	//�`���m�[�g�̃f�[�^
		GMDATA_ID_FNOTE,
		SVBLK_ID_NORMAL,
		(FUNC_GET_SIZE)FNOTE_GetWorkSize,
		(FUNC_INIT_WORK)FNOTE_InitAll,
	},
	{	//�g���[�i�[�J�[�h
		GMDATA_ID_TRCARD,
		SVBLK_ID_NORMAL,
		(FUNC_GET_SIZE)TRCSave_GetSaveDataSize,
		(FUNC_INIT_WORK)TRCSave_InitSaveData,
	},
	{	//���R�[�h�p�J�E���g�A�b�v�f�[�^
		GMDATA_ID_RECORD,
		SVBLK_ID_NORMAL,
		(FUNC_GET_SIZE)RECORD_GetWorkSize,
		(FUNC_INIT_WORK)RECORD_Init,
	},
	{	//�J�X�^���{�[��
		GMDATA_ID_CUSTOM_BALL,
		SVBLK_ID_NORMAL,
		(FUNC_GET_SIZE)CustomBall_GetWorkSize,
		(FUNC_INIT_WORK)CustomBall_Init,
	},
	{	//�؃��b�v�����f�[�^
		GMDATA_ID_PERAPVOICE,
		SVBLK_ID_NORMAL,
		(FUNC_GET_SIZE)PERAPVOICE_GetWorkSize,
		(FUNC_INIT_WORK)PERAPVOICE_Init,
	},
	{	//�o�g���^���[�f�[�^
		GMDATA_ID_BTLTOWER,
		SVBLK_ID_NORMAL,
		(FUNC_GET_SIZE)TowerData_GetWorkSize,
		(FUNC_INIT_WORK)TowerData_Init,
	},
	{	//�z�z���{���f�[�^
		GMDATA_ID_SP_RIBBON,
		SVBLK_ID_NORMAL,
		(FUNC_GET_SIZE)SP_RIBBON_GetWorkSize,
		(FUNC_INIT_WORK)SP_RIBBON_Init,
	},
	{
		// �G���J�E���g�֘A�f�[�^
		GMDATA_ID_ENCOUNT,
		SVBLK_ID_NORMAL,
		(FUNC_GET_SIZE)EncDataSave_GetWorkSize,
		(FUNC_INIT_WORK)EncDataSave_InitSaveData,
	},
	{	//���E�����f�[�^
		GMDATA_ID_WORLDTRADEDATA,
		SVBLK_ID_NORMAL,
		(FUNC_GET_SIZE)WorldTradeData_GetWorkSize,
		(FUNC_INIT_WORK)WorldTradeData_Init,
	},
	{	//TV�f�[�^
		GMDATA_ID_TVWORK,
		SVBLK_ID_NORMAL,
		(FUNC_GET_SIZE)TVWORK_GetWorkSize,
		(FUNC_INIT_WORK)TVWORK_Init,
	},
	{	//�M�l�X�z�[���f�[�^
		GMDATA_ID_GUINNESS,
		SVBLK_ID_NORMAL,
		(FUNC_GET_SIZE)GuinnessData_GetWorkSize,
		(FUNC_INIT_WORK)GuinnessData_Init,
	},
	{	// Wifi�p�A�������E�F�B���
		GMDATA_ID_WIFILIST,
		SVBLK_ID_NORMAL,
		(FUNC_GET_SIZE)WifiList_GetWorkSize,
		(FUNC_INIT_WORK)WifiList_Init,
	},

	{	//WiFi�ʐM�����f�[�^
		GMDATA_ID_WIFIHISTORY,
		SVBLK_ID_NORMAL,
		(FUNC_GET_SIZE)WIFIHISTORY_GetWorkSize,
		(FUNC_INIT_WORK)WIFIHISTORY_Init,
	},
	{	//�ӂ����ȑ��蕨�f�[�^
		GMDATA_ID_FUSHIGIDATA,
		SVBLK_ID_NORMAL,
		(FUNC_GET_SIZE)FUSHIGIDATA_GetWorkSize,
		(FUNC_INIT_WORK)FUSHIGIDATA_Init,
	},
	{	//�|�P�p�[�N�p�|�P�����f�[�^
		GMDATA_ID_POKEPARKDATA,
		SVBLK_ID_NORMAL,
		(FUNC_GET_SIZE)POKEPARKDATA_GetWorkSize,
		(FUNC_INIT_WORK)POKEPARKDATA_Init,
	},
	{	//�R���e�X�g
		GMDATA_ID_CONTEST,
		SVBLK_ID_NORMAL,
		(FUNC_GET_SIZE)CONDATA_GetWorkSize,
		(FUNC_INIT_WORK)CONDATA_Init,
	},
	{	// �ȈՉ�b�P��
		GMDATA_ID_PMS,
		SVBLK_ID_NORMAL,
		(FUNC_GET_SIZE)PMSW_GetSaveDataSize,
		(FUNC_INIT_WORK)PMSW_InitSaveData,
	},
//�{�b�N�X�f�[�^�O���[�v
	{	//�|�P�����{�b�N�X�̃f�[�^
		GMDATA_ID_BOXDATA,
		SVBLK_ID_BOX,
		(FUNC_GET_SIZE)BOXDAT_GetTotalSize,
		(FUNC_INIT_WORK)BOXDAT_Init,
	},

};

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
const int SaveDataTableMax = NELEMS(SaveDataTable);



//============================================================================================
//
//
//
//============================================================================================
//---------------------------------------------------------------------------
/**
 * @brief	�e���r�f�[�^�̃|�C���^�擾
 * @param	sv			�Z�[�u�f�[�^�\���ւ̃|�C���^
 * @return	BOX_DATA	�e���r�f�[�^�ւ̃|�C���^
 */
//---------------------------------------------------------------------------
TV_WORK * SaveData_GetTvWork(SAVEDATA * sv)
{
	return SaveData_Get(sv, GMDATA_ID_TVWORK);
}

//---------------------------------------------------------------------------
/**
 * @brief	�{�b�N�X�f�[�^�̃|�C���^�擾
 * @param	sv			�Z�[�u�f�[�^�\���ւ̃|�C���^
 * @return	BOX_DATA	�{�b�N�X�f�[�^�ւ̃|�C���^
 */
//---------------------------------------------------------------------------
BOX_DATA * SaveData_GetBoxData(SAVEDATA * sv)
{
	return SaveData_Get(sv, GMDATA_ID_BOXDATA);
}

//---------------------------------------------------------------------------
/**
 * @brief	�ӂ����ȑ��蕨�p�Z�[�u�f�[�^�ւ̃|�C���^�擾
 * @param	sv				�Z�[�u�f�[�^�\���ւ̃|�C���^
 * @return	FUSHIGI_DATA	�ӂ����ȑ��蕨�f�[�^�ւ̃|�C���^
 */
//---------------------------------------------------------------------------
FUSHIGI_DATA * SaveData_GetFushigiData(SAVEDATA * sv)
{
	return SaveData_Get(sv, GMDATA_ID_FUSHIGIDATA);
}

//---------------------------------------------------------------------------
/**
 * @brief	�|�P�p�[�N�p�Z�[�u�f�[�^�ւ̃|�C���^�擾
 * @param	sv				�Z�[�u�f�[�^�\���ւ̃|�C���^
 * @return	POKEPARK_DATA	�|�P�p�[�N�p�Z�[�u�f�[�^�ւ̃|�C���^
 */
//---------------------------------------------------------------------------
POKEPARK_DATA * SaveData_GetPokeParkData(SAVEDATA * sv)
{
	return SaveData_Get(sv, GMDATA_ID_POKEPARKDATA);
}

//============================================================================================
//
//
//			����Z�[�u�f�[�^
//
//
//============================================================================================
//---------------------------------------------------------------------------
/**
 * @brief	����Z�[�u�f�[�^�̒�`�e�[�u��
 */
//---------------------------------------------------------------------------
const EXSAVEDATA_TABLE ExtraSaveDataTable[] = {
	{
		// �a������f�[�^
		EXDATA_ID_DENDOU,
		SAVE_PAGE_MAX + 0,
		(FUNC_GET_SIZE)DendouData_GetWorkSize,
		(FUNC_INIT_WORK)DendouData_Init,
	},

	{	//�ӂ������蕨�f�[�^
		EXDATA_ID_FUSHIGIDATA,
		SAVE_PAGE_MAX + 3,
		(FUNC_GET_SIZE)FUSHIGIDATA_GetWorkSize,
		(FUNC_INIT_WORK)FUSHIGIDATA_Init,
	},

};
//---------------------------------------------------------------------------
/**
 * @brief	����Z�[�u�f�[�^�̃e�[�u����
 */
//---------------------------------------------------------------------------
const int ExtraSaveDataTableMax = NELEMS(ExtraSaveDataTable);



//============================================================================================
//
//
//			�ʂ̓���Z�[�u�f�[�^�A�N�Z�X�֐�
//
//
//============================================================================================
//---------------------------------------------------------------------------
/**
 * @brief	����Z�[�u�f�[�^���[�h�F�a������f�[�^
 * @param	sv			�Z�[�u�f�[�^�\���ւ̃|�C���^
 * @param	heap_id		���[�N���擾����q�[�v��ID
 * @param	result
 * @return	void *	�擾�����Z�[�u�f�[�^���ڂ������[�N�ւ̃|�C���^
 */
//---------------------------------------------------------------------------
DENDOU_SAVEDATA * SaveData_Extra_LoadDendouData(SAVEDATA * sv, int heap_id, LOAD_RESULT * result)
{
	return SaveData_Extra_LoadAlloc(sv, heap_id, EXDATA_ID_DENDOU, result);
}

//---------------------------------------------------------------------------
/**
 * @brief	����Z�[�u�f�[�^�Z�[�u�F�a������f�[�^
 * @param	sv			�Z�[�u�f�[�^�\���ւ̃|�C���^
 * @param	data		�a������f�[�^�ւ̃|�C���^
 * @retval	SAVE_RESULT_OK		�Z�[�u����
 * @retval	SAVE_RESULT_NG		�Z�[�u���s
 */
//---------------------------------------------------------------------------
SAVE_RESULT SaveData_Extra_SaveDendouData(SAVEDATA * sv, DENDOU_SAVEDATA * data)
{
	return SaveData_Extra_Save(sv, EXDATA_ID_DENDOU, data);
}


#if 0

�ʏ�Z�[�u�f�[�^�Ɋ܂܂��悤�ɂȂ������߂ɍ폜

//---------------------------------------------------------------------------
/**
 * @brief	����Z�[�u�f�[�^���[�h�F�ӂ����Ȃ��������
 * @param	sv			�Z�[�u�f�[�^�\���ւ̃|�C���^
 * @param	heap_id		���[�N���擾����q�[�v��ID
 * @param	result		���[�h���ʎ擾�p�̃��[�N
 * @return	void *	�擾�����Z�[�u�f�[�^���ڂ������[�N�ւ̃|�C���^
 */
//---------------------------------------------------------------------------
FUSHIGI_DATA * SaveData_Extra_LoadFushigiData(SAVEDATA * sv, int heap_id, LOAD_RESULT * result)
{
	return SaveData_Extra_LoadAlloc(sv, heap_id, EXDATA_ID_FUSHIGIDATA, result);
}

//---------------------------------------------------------------------------
/**
 * @brief	����Z�[�u�f�[�^�Z�[�u�F�ӂ����Ȃ��������
 * @param	sv			�Z�[�u�f�[�^�\���ւ̃|�C���^
 * @param	data		�a������f�[�^�ւ̃|�C���^
 * @retval	SAVE_RESULT_OK		�Z�[�u����
 * @retval	SAVE_RESULT_NG		�Z�[�u���s
 */
//---------------------------------------------------------------------------
SAVE_RESULT SaveData_Extra_SaveFushigiData(SAVEDATA * sv, FUSHIGI_DATA * data)
{
	return SaveData_Extra_Save(sv, EXDATA_ID_FUSHIGIDATA, data);
}
#endif


