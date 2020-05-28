//============================================================================================
/**
 * @file	scr_poke.c
 * @bfief	�X�N���v�g�R�}���h�F�|�P��������֘A
 * @author	Tomomichi Ohta
 * @date	06.06.26
 */
//============================================================================================
#include "common.h"

#include <nitro/code16.h> 
#include "system/pm_str.h"
#include "system\msgdata.h"			//MSGMAN_GetString
#include "system/brightness.h"		//ChangeBrightnessRequest
#include "system\wordset.h"			//WordSet_RegistPlayerName
#include "system/bmp_menu.h"
#include "system/bmp_list.h"
#include "system/get_text.h"
#include "system/window.h"
#include "system/fontproc.h"
#include "system/pms_data.h"
#include "system/wipe.h"
#include "system/placename.h"

#include "system/lib_pack.h"
#include "fieldsys.h"

#include "script.h"
#include "scrcmd_def.h"
#include "field/eventflag.h"
#include "field/evwkdef.h"
#include "sysflag.h"
#include "syswork.h"

#include "poketool/boxdata.h"

#include "..\application\p_status\ribbon.h"

#include "vm.h"
#include "scrcmd.h"
#include "script.h"
#include "scr_tool.h"
#include "ev_win.h"
#include "ev_time.h"

#include "battle/attr_def.h"
#include "zonedata.h"

#include "d_print.h"
#include "sodateya.h"

#include "ev_pokemon.h"				//EvPoke_Add
#include "poketool/poke_memo.h"

#include "scr_poke.h"
#include "msgdata/msg_place_name_tokusyu.h"
#include "itemtool/itemsym.h"
#include "itemtool/itemequip.h"
#include "itemtool/item.h"


//============================================================================================
//
//	�R�}���h
//
//============================================================================================
//--------------------------------------------------------------------------------------------
/**
 * �|�P�������莝���ɉ�����
 *
 * @param	core		���z�}�V������\���̂ւ̃|�C���^
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdAddPokemon(VM_MACHINE * core)
{
	int place_id = ZoneData_GetPlaceNameID(core->fsys->location->zone_id);
	int ground_id = GROUND_ID_ALL;
	POKEPARTY * temoti;
	FIELDSYS_WORK * fsys	= core->fsys;
	u16 monsno				= VMGetWorkValue(core);
	u16 lv					= VMGetWorkValue(core);
	u16 itemno				= VMGetWorkValue(core);
	u16* ret_wk				= VMGetWork( core );

	//06.05.19
	//AGB�̃|�P�����ǉ��́A�莝���������ς��̎��́A�{�b�N�X�ɓ]�������悤�ɂȂ��Ă��āA
	//�ǂ���ɒǉ�������(�ǉ��ł��Ȃ�����)���߂�l�ɂȂ��Ă���

	temoti = SaveData_GetTemotiPokemon(fsys->savedata);
	*ret_wk = EvPoke_Add(HEAPID_WORLD, fsys->savedata, monsno, lv, itemno, place_id, ground_id);

	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 *	�莝���̈ʒu�i���o�[����A�|�P�����ԍ��֕ϊ�
 *
 * @param	core		���z�}�V������\���̂ւ̃|�C���^
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdTemotiMonsNo(VM_MACHINE * core)
{
	FIELDSYS_WORK * fsys	= core->fsys;
	POKEMON_PARAM * poke;
	u16* in_wk				= VMGetWork( core );
	u16* out_wk				= VMGetWork( core );

	//�|�P�����ւ̃|�C���^�擾
	poke = PokeParty_GetMemberPointer( SaveData_GetTemotiPokemon(fsys->savedata), *in_wk);

	//�����X�^�[�ԍ��擾
	if( PokeParaGet( poke, ID_PARA_tamago_flag, NULL ) == 0 ){
		*out_wk = PokeParaGet(poke,ID_PARA_monsno,NULL);
	}else{	//�^�}�S
		*out_wk = 0;
	}

	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 *	�莝���|�P�����̂���l�l�`�F�b�N
 *
 * @param	core		���z�}�V������\���̂ւ̃|�C���^
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdMonsOwnChk(VM_MACHINE * core)
{
	FIELDSYS_WORK * fsys	= core->fsys;
	POKEMON_PARAM * poke;
	MYSTATUS* my		= SaveData_GetMyStatus( GameSystem_GetSaveData(core->fsys) );
	u16* in_wk				= VMGetWork( core );
	u16* out_wk				= VMGetWork( core );
	u16 poke_id,my_id;

	//�|�P�����ւ̃|�C���^�擾
	poke = PokeParty_GetMemberPointer( SaveData_GetTemotiPokemon(fsys->savedata), *in_wk);

	//�|�P������ID
	poke_id = PokeParaGet( poke, ID_PARA_id_no, NULL );

	my_id = MyStatus_GetID(my);

	if(poke_id == my_id){	//��v
		*out_wk = 0;
	}else{					//�s��v
		*out_wk = 1;
	}

	return 0;
}


//--------------------------------------------------------------------------------------------
/**
 * �^�}�S���莝���ɉ�����
 *
 * @param	core		���z�}�V������\���̂ւ̃|�C���^
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdAddTamago(VM_MACHINE * core)
{
	int index;
	u8	max;
	BOOL result;
	POKEPARTY * temoti;
	POKEMON_PARAM* poke_param;
	FIELDSYS_WORK * fsys	= core->fsys;
	MYSTATUS	  * my      = SaveData_GetMyStatus(fsys->savedata);
	u16 monsno				= VMGetWorkValue(core);
	u16 msgid				= VMGetWorkValue(core);

	temoti = SaveData_GetTemotiPokemon(fsys->savedata);

	max = PokeParty_GetPokeCount(temoti);
	if(max<6){		//���O�̂��߁B�|�P�������ő吔�̂Ƃ��ɌĂ΂�Ă���΂Ȃ��悤��
		poke_param = PokemonParam_AllocWork(HEAPID_WORLD);
		PokeParaInit(poke_param);

		index = PlaceName_IndexToParamNumber( PLACENAME_TYPE_GAME_EVENT, msgid );
		OS_Printf( "msgid = %d\n", msgid );
		OS_Printf( "index = %d\n", index );
		PokemonTamagoSet_forEvent(poke_param,monsno,1, my, TRMEMO_SODATEYA_PLACESET, index);

		result = PokeParty_Add(temoti, poke_param);
		sys_FreeMemoryEz(poke_param);
	}
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * �莝���|�P�����̋Z��u��������
 *
 * @param	core		���z�}�V������\���̂ւ̃|�C���^
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdChgPokeWaza( VM_MACHINE * core )
{
	u16 poke_pos, waza_pos, waza_no;
	poke_pos = VMGetWorkValue(core);
	waza_pos = VMGetWorkValue(core);
	waza_no = VMGetWorkValue(core);
	EvPoke_ChangeWaza(SaveData_GetTemotiPokemon(core->fsys->savedata),
			poke_pos, waza_pos, waza_no);

	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * �莝���|�P�������w�肳�ꂽ�Z���o���Ă��邩�`�F�b�N�i�P�́j
 *
 * @param	core		���z�}�V������\���̂ւ̃|�C���^
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdChkPokeWaza( VM_MACHINE * core )
{
	FIELDSYS_WORK * fsys	= core->fsys;
	POKEMON_PARAM * poke;
	u16* ret_wk	= VMGetWork( core );
	u16 waza	= VMGetWorkValue(core);
	u16 tno		= VMGetWorkValue(core);
	u16 my_waza;

	poke = PokeParty_GetMemberPointer( SaveData_GetTemotiPokemon(fsys->savedata), tno);

	*ret_wk = 0;
	//���܂��`�F�b�N
	if( PokeParaGet( poke, ID_PARA_tamago_flag, NULL ) != 0 ){
		return 0;
	}

	//���U���X�g����`�F�b�N
	if( (PokeParaGet( poke, ID_PARA_waza1, NULL ) == waza) ||(PokeParaGet( poke, ID_PARA_waza2, NULL ) == waza) ||(PokeParaGet( poke, ID_PARA_waza3, NULL ) == waza) ||(PokeParaGet( poke, ID_PARA_waza4, NULL ) == waza) ){
		*ret_wk = 1;
	}

	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * �莝���|�P�������w�肳�ꂽ�Z���o���Ă��邩�`�F�b�N
 *
 * @param	core		���z�}�V������\���̂ւ̃|�C���^
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdChkPokeWazaGroup( VM_MACHINE * core )
{
	FIELDSYS_WORK * fsys	= core->fsys;
	POKEMON_PARAM * poke;
	u16* ret_wk	= VMGetWork( core );
	u16 waza	= VMGetWorkValue(core);
	u16 my_waza;
	u8	i,max;

	max = PokeParty_GetPokeCount(SaveData_GetTemotiPokemon(fsys->savedata));

	for( i=0, *ret_wk=6 ; i<max; i++ ){
		poke = PokeParty_GetMemberPointer( SaveData_GetTemotiPokemon(fsys->savedata), i);

		//���܂��`�F�b�N
		if( PokeParaGet( poke, ID_PARA_tamago_flag, NULL ) != 0 ){
			continue;
		}

		//���U���X�g����`�F�b�N
		if( (PokeParaGet( poke, ID_PARA_waza1, NULL ) == waza) ||(PokeParaGet( poke, ID_PARA_waza2, NULL ) == waza) ||(PokeParaGet( poke, ID_PARA_waza3, NULL ) == waza) ||(PokeParaGet( poke, ID_PARA_waza4, NULL ) == waza) ){
			*ret_wk = i;		//�����Ă���|�P�����̃��X�g��̕��т�Ԃ�
			break;
		}

	}

	return	0;
}

//--------------------------------------------------------------------------------------------
/**
 * �|�P�������łŎ��񂾂��ǂ����̔F��
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdApprovePoisonDead(VM_MACHINE * core)
{
	POKEMON_PARAM * pp;
	u16 num;
	u16 * ret_wk;
	ret_wk = VMGetWork(core);
	num = VMGetWorkValue(core);
	pp = PokeParty_GetMemberPointer(SaveData_GetTemotiPokemon(core->fsys->savedata), num);
	*ret_wk = EvPoke_ApprovePoisonDead(pp);
	OS_Printf("POS:%d RESULT:%d\n",num, *ret_wk);
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 *	�莝���|�P�����̃��x���`�F�b�N�i�����̐�)
 *
 * @param	core		���z�}�V������\���̂ւ̃|�C���^
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdPokeLevelChk(VM_MACHINE * core)
{
	FIELDSYS_WORK* fsys = core->fsys;
	POKEMON_PARAM * poke;
	u16* ret_wk			= VMGetWork( core );
	u16 level			= VMGetWorkValue( core );
	u8 i,max,ct;

	max = PokeParty_GetPokeCount(SaveData_GetTemotiPokemon(fsys->savedata));

	*ret_wk = 0;
	for(i=0,ct=0;i<max;i++){
		poke = PokeParty_GetMemberPointer( SaveData_GetTemotiPokemon(fsys->savedata), i);

		//�����X�^�[�ԍ��擾(0�ȊO�Ȃ�^�}�S�j
		if( PokeParaGet( poke, ID_PARA_tamago_flag, NULL ) == 0 ){

			//�����ȉ��̃|�P���������邩�`�F�b�N
			if( PokeParaGet( poke, ID_PARA_level, NULL ) <= level ){
				ct++;
			}

		}
	}

	*ret_wk = ct;

	return 0;

}

//--------------------------------------------------------------------------------------------
/**
 *	�莝���|�P�����̃��x���擾
 *
 * @param	core		���z�}�V������\���̂ւ̃|�C���^
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdPokeLevelGet(VM_MACHINE * core)
{
	FIELDSYS_WORK* fsys = core->fsys;
	POKEMON_PARAM * poke;
	u16* ret_wk			= VMGetWork( core );
	u16 tno			= VMGetWorkValue( core );

	poke = PokeParty_GetMemberPointer( SaveData_GetTemotiPokemon(fsys->savedata), tno);

	*ret_wk = 0;
	if( PokeParaGet( poke, ID_PARA_tamago_flag, NULL ) == 0 ){
		*ret_wk = PokeParaGet( poke, ID_PARA_level, NULL );
	}

	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * ���i�Q�b�g
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdGetPokeSeikaku(VM_MACHINE * core)
{
	FIELDSYS_WORK * fsys	= core->fsys;
	POKEMON_PARAM * poke;
	u16* ret_wk	= VMGetWork( core );
	u16 tno	= VMGetWorkValue(core);
	u8 max;

	max = PokeParty_GetPokeCount(SaveData_GetTemotiPokemon(fsys->savedata));

	if(tno >= max) {		//�����Ă���|�P�����ȏ�̔ԍ��̂Ƃ�
		*ret_wk = 0;
		return 0;
	}

	poke = PokeParty_GetMemberPointer( SaveData_GetTemotiPokemon(fsys->savedata), tno);

	//�^�}�S�`�F�b�N
	if( PokeParaGet( poke, ID_PARA_tamago_flag, NULL ) != 0 ){
		*ret_wk = 0;
		return 0;
	}

	//���i�擾
	*ret_wk = PokeSeikakuGet(poke);

	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * ����̐��i�̃|�P���������邩���`�F�b�N
 * 0xff:���Ȃ� 0�`5:�莝���ԍ�
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdChkPokeSeikakuAll(VM_MACHINE * core)
{
	FIELDSYS_WORK * fsys	= core->fsys;
	POKEMON_PARAM * poke;
	u16* ret_wk	= VMGetWork( core );
	u16 seikaku_no	= VMGetWorkValue(core);
	u8 max,i;

	max = PokeParty_GetPokeCount(SaveData_GetTemotiPokemon(fsys->savedata));

	*ret_wk = 0xff;
	for(i=0;i<max;i++){
		poke = PokeParty_GetMemberPointer( SaveData_GetTemotiPokemon(fsys->savedata), i);

		//�^�}�S�łȂ��Ƃ��̂݃`�F�b�N
		if( PokeParaGet( poke, ID_PARA_tamago_flag, NULL ) == 0 ){
			//���i�`�F�b�N
			if(PokeSeikakuGet(poke) == seikaku_no){
				*ret_wk = i;
				break;
			}
		}

	}

	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * �Ȃ��x�̎擾
 *
 * @param	core		���z�}�V������\���̂ւ̃|�C���^
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdGetNatsuki( VM_MACHINE * core )
{
	FIELDSYS_WORK* fsys = core->fsys;
	POKEMON_PARAM * poke;
	u16* ret_wk			= VMGetWork( core );
	u16 tno	= VMGetWorkValue(core);

	//�|�P�����ւ̃|�C���^�擾
	poke = PokeParty_GetMemberPointer( SaveData_GetTemotiPokemon(fsys->savedata), tno);

	//�|�P�����̂Ȃ��x�擾
	*ret_wk = PokeParaGet( poke, ID_PARA_friend, NULL );
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * �Ȃ��x�𑝂₷
 *
 * @param	core		���z�}�V������\���̂ւ̃|�C���^
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdAddNatsuki( VM_MACHINE * core )
{
	FIELDSYS_WORK* fsys = core->fsys;
	POKEMON_PARAM * poke;
	u16 add_value			= VMGetWorkValue( core );
	u16 tno	= VMGetWorkValue(core);
	u16 value;
	u32 place_id = ZoneData_GetPlaceNameID(core->fsys->location->zone_id);

	//�|�P�����ւ̃|�C���^�擾
	poke = PokeParty_GetMemberPointer( SaveData_GetTemotiPokemon(fsys->savedata), tno);

	//�|�P�����̂Ȃ��x�擾
	value = PokeParaGet( poke, ID_PARA_friend, NULL );

#if 0
	value += add_value;
	if(value > 255) {			//�Ȃ��xMax=255
		value = 255;
	}
#else
	if( add_value > 0 ){
		// ��������
		if( ItemParamGet(PokeParaGet(poke,ID_PARA_item,NULL),ITEM_PRM_EQUIP,HEAPID_WORLD) == SOUBI_NATUKIDOUP ){
			add_value = add_value * 150 / 100;
		}
		// �ߊl�{�[��
		if( PokeParaGet( poke, ID_PARA_get_ball, NULL ) == ITEM_GOOZYASUBOORU ){
			add_value++;
		}
		// �ߊl�ꏊ
		if( PokeParaGet( poke, ID_PARA_get_place, NULL ) == place_id ){
			add_value++;
		}
	}

	value += add_value;
	if( value > FRIEND_MAX ){
		value = FRIEND_MAX;
	}
#endif

	//�|�P�����̂Ȃ��x�Z�b�g
	PokeParaPut( poke, ID_PARA_friend, &value );
	return 0;
}


//--------------------------------------------------------------------------------------------
/**
 * �Ȃ��x�����炷
 *
 * @param	core		���z�}�V������\���̂ւ̃|�C���^
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdSubNatsuki( VM_MACHINE * core )
{
	FIELDSYS_WORK* fsys = core->fsys;
	POKEMON_PARAM * poke;
	u16 sub_value			= VMGetWorkValue( core );
	u16 tno	= VMGetWorkValue(core);
	u16 value;

	//�|�P�����ւ̃|�C���^�擾
	poke = PokeParty_GetMemberPointer( SaveData_GetTemotiPokemon(fsys->savedata), tno);

	//�|�P�����̂Ȃ��x�擾
	value = PokeParaGet( poke, ID_PARA_friend, NULL );

	if(sub_value > value) {
		value = 0;
	}else{
		value -= sub_value;
	}

	//�|�P�����̂Ȃ��x�Z�b�g
	PokeParaPut( poke, ID_PARA_friend, &value );
	return 0;
}


//--------------------------------------------------------------------------------------------
/**
 * �莝���|�P�����̃R���e�X�g�X�e�[�^�X�擾(�������悳�A���킢����)
 *
 * @param	core		���z�}�V������\���̂ւ̃|�C���^
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdTemotiPokeContestStatusGet( VM_MACHINE * core )
{
	POKEMON_PARAM * poke;
	u16 pos		= VMGetWorkValue( core );
	u16 con_type = VMGetWorkValue( core );
	u16* ret_wk	= VMGetWork( core );

	//�|�P�����ւ̃|�C���^�擾
	poke = PokeParty_GetMemberPointer( SaveData_GetTemotiPokemon(core->fsys->savedata), pos );

	*ret_wk = PokeParaGet(poke, ID_PARA_style + con_type, NULL);
	return 0;
}

//-----------------------------------------------------------------------------
/**
 *	�擪�̃|�P������Ԃ��i�^�}�S�𔲂������j
 */
//-----------------------------------------------------------------------------
BOOL EvCmdFrontPokemon(VM_MACHINE * core)
{
	u16* ret_wk			= VMGetWork( core );

	*ret_wk = GetFrontPokemon(core->fsys->savedata);

	return 0;
}

//-----------------------------------------------------------------------------
/**
 *	�莝���|�P�����̃^�C�v���擾
 */
//-----------------------------------------------------------------------------
BOOL EvCmdTemotiPokeType(VM_MACHINE * core)
{
	FIELDSYS_WORK * fsys	= core->fsys;
	POKEMON_PARAM * poke;
	u16* ret_wk1				= VMGetWork( core );
	u16* ret_wk2				= VMGetWork( core );
	u16 tno		= VMGetWorkValue(core);

	//�|�P�����ւ̃|�C���^�擾
	poke = PokeParty_GetMemberPointer( SaveData_GetTemotiPokemon(fsys->savedata), tno);

	*ret_wk1 = PokeParaGet( poke, ID_PARA_type1, NULL );
	*ret_wk2 = PokeParaGet( poke, ID_PARA_type2, NULL );

	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * �|�P�������擾
 * @brief   �莝���̃|�P�������𒲂ׂĕԂ�
 * 
 * @param	core		���z�}�V������\���̂ւ̃|�C���^
 *
 * @return	"1"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdGetPokeCount( VM_MACHINE * core )
{
	int max;
	POKEMON_PARAM * poke;
	FIELDSYS_WORK* fsys = core->fsys;
	u16* ret_wk			= VMGetWork( core );

	max = PokeParty_GetPokeCount(SaveData_GetTemotiPokemon(fsys->savedata));

	//����A�^�}�S���ɂ���ďo�͂𕪂��邩��

	*ret_wk = max;

	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * �|�P�������擾(�^�}�S�������j
 * @brief   �莝���̃|�P�������𒲂ׂĕԂ�
 * 
 * @param	core		���z�}�V������\���̂ւ̃|�C���^
 *
 * @return	"1"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdGetPokeCount2( VM_MACHINE * core )
{
	int max,poke_max,i;
	POKEMON_PARAM * poke;
	FIELDSYS_WORK* fsys = core->fsys;
	u16* ret_wk			= VMGetWork( core );

	max = PokeParty_GetPokeCount(SaveData_GetTemotiPokemon(fsys->savedata));

	for(i=0,poke_max=0;i<max;i++){
		poke = PokeParty_GetMemberPointer( SaveData_GetTemotiPokemon(fsys->savedata), i);

		//�����X�^�[�ԍ��擾(0�ȊO�Ȃ�^�}�S����Ȃ��j
		if( PokeParaGet( poke, ID_PARA_tamago_flag, NULL ) == 0 ){
			poke_max++;
		}
	}

	*ret_wk = poke_max;

	return 0;
}


//--------------------------------------------------------------------------------------------
/**
 * �|�P�������擾(�^�}�S�ƕm���������j
 * @brief   �莝���̃|�P�������𒲂ׂĕԂ�(�퓬�\�ȃ|�P������)
 *	no = ��������莝���ԍ�(6:�Ȃ��A0�`5)
 * 
 * @param	core		���z�}�V������\���̂ւ̃|�C���^
 *
 * @return	"1"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdGetPokeCount3( VM_MACHINE * core )
{
	int max,poke_max,i;
	POKEMON_PARAM * poke;
	FIELDSYS_WORK* fsys = core->fsys;
	u16* ret_wk			= VMGetWork( core );
	u16 no			= VMGetWorkValue( core );

	max = PokeParty_GetPokeCount(SaveData_GetTemotiPokemon(fsys->savedata));

	for(i=0,poke_max=0;i<max;i++){
		if(i==no) continue;
		poke = PokeParty_GetMemberPointer( SaveData_GetTemotiPokemon(fsys->savedata), i);
		//�����X�^�[�ԍ��擾(0�ȊO�Ȃ�^�}�S����Ȃ��j
		if( PokeParaGet( poke, ID_PARA_tamago_flag, NULL ) == 0 ){
			//�m�����O�`�F�b�N(0==�m��)
			if( PokeParaGet( poke,ID_PARA_hp , NULL ) != 0 ){
				poke_max++;
			}
		}
	}

	*ret_wk = poke_max;

	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * �|�P���������i�莝���{�{�b�N�X�j�擾(�^�}�S�ƁA�莝���̕m���������j
 *
 * �����ݎg�p����Ă��܂���
 * 
 * @brief   �莝���̃|�P�������𒲂ׂĕԂ�
 * 
 * @param	core		���z�}�V������\���̂ւ̃|�C���^
 *
 * @return	"1"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdGetPokeCount4( VM_MACHINE * core )
{
	int max,poke_max,i;
	POKEMON_PARAM * poke;
	FIELDSYS_WORK* fsys = core->fsys;
	u16* ret_wk			= VMGetWork( core );
	BOX_DATA* boxDat = SaveData_GetBoxData( fsys->savedata );

	max = PokeParty_GetPokeCount(SaveData_GetTemotiPokemon(fsys->savedata));

	for(i=0,poke_max=0;i<max;i++){
		poke = PokeParty_GetMemberPointer( SaveData_GetTemotiPokemon(fsys->savedata), i);

		//�����X�^�[�ԍ��擾(0�ȊO�Ȃ�^�}�S����Ȃ��j
		if( PokeParaGet( poke, ID_PARA_tamago_flag, NULL ) == 0 ){
			//�m�����O�`�F�b�N(0==�m��)
			if( PokeParaGet( poke,ID_PARA_hp , NULL ) != 0 ){
				poke_max++;
			}
		}
	}

	poke_max += BOXDAT_GetPokeExistCount2Total( boxDat );

	*ret_wk = poke_max;

	return 0;
}


//--------------------------------------------------------------------------------------------
/**
 * �^�}�S���擾
 * @brief   �莝���̃|�P�������𒲂ׂĕԂ�
 * 
 * @param	core		���z�}�V������\���̂ւ̃|�C���^
 *
 * @return	"1"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdGetTamagoCount( VM_MACHINE * core )
{
	int max,tamago_max,i;
	POKEMON_PARAM * poke;
	FIELDSYS_WORK* fsys = core->fsys;
	u16* ret_wk			= VMGetWork( core );

	max = PokeParty_GetPokeCount(SaveData_GetTemotiPokemon(fsys->savedata));

	for(i=0,tamago_max=0;i<max;i++){
		poke = PokeParty_GetMemberPointer( SaveData_GetTemotiPokemon(fsys->savedata), i);

		//�^�}�S���擾
		if( PokeParaGet( poke, ID_PARA_tamago_flag, NULL )){
//���ꍇ�ɂ���ẮA�_���^�}�S�`�F�b�N������邩���i�d�l�ɂ��j
			tamago_max++;
		}
	}

	*ret_wk = tamago_max;

	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * �莝���|�P�����̃|�P���X�ւ̊������`�F�b�N
 *
 * @param	core		���z�}�V������\���̂ւ̃|�C���^
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdChkTemotiPokerus( VM_MACHINE * core )
{
	u16 i, max;
	u16 * wk;
	u32 pokerus;
	POKEMON_PARAM * poke;
	FIELDSYS_WORK* fsys = core->fsys;

	wk = VMGetWork( core );


	max = PokeParty_GetPokeCount(SaveData_GetTemotiPokemon(fsys->savedata));

	//�|�P���X�������Ă��邩check
	*wk = 0;
	for(i=0;i<max;i++){
		//�|�P�����ւ̃|�C���^�擾
		poke = PokeParty_GetMemberPointer( SaveData_GetTemotiPokemon(fsys->savedata), i);

		pokerus = PokeParaGet(poke, ID_PARA_pokerus, NULL);

		if(pokerus!=0){
			*wk = 1;
			break;
		}
	}

	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * �莝���|�P�����̐��ʎ擾
 *
 * @param	core		���z�}�V������\���̂ւ̃|�C���^
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdTemotiPokeSexGet( VM_MACHINE * core )
{
	POKEMON_PARAM * poke;
	u16 pos		= VMGetWorkValue( core );
	u16* ret_wk	= VMGetWork( core );

	//�|�P�����ւ̃|�C���^�擾
	poke = PokeParty_GetMemberPointer( SaveData_GetTemotiPokemon(core->fsys->savedata), pos );

	*ret_wk = PokeParaGet(poke, ID_PARA_sex, NULL);
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * @brief	�Z�Y��֘A�F�����Ă���Z���J�E���g
 * @param	core		���z�}�V������\���̂ւ̃|�C���^
 * @return	0
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdWazaCount( VM_MACHINE * core )
{
	FIELDSYS_WORK * fsys	= core->fsys;
	POKEMON_PARAM * poke;
	u16* ret_wk	= VMGetWork( core );
	u16 t_no	= VMGetWorkValue( core );
	u8 i;

	poke = PokeParty_GetMemberPointer( SaveData_GetTemotiPokemon(fsys->savedata), t_no);

	//���܂��`�F�b�N
	if( PokeParaGet( poke, ID_PARA_tamago_flag, NULL ) != 0 ){
		*ret_wk =0;
		return 0;
	}

	i=0;
	if( (PokeParaGet( poke, ID_PARA_waza1, NULL ) != 0)){
		i++;
	}

	if( (PokeParaGet( poke, ID_PARA_waza2, NULL ) != 0)){
		i++;
	}

	if( (PokeParaGet( poke, ID_PARA_waza3, NULL ) != 0)){
		i++;
	}

	if( (PokeParaGet( poke, ID_PARA_waza4, NULL ) != 0)){
		i++;
	}

	*ret_wk = i;
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * @brief	�Z�Y��֘A�F���U������
 * @param	core		���z�}�V������\���̂ւ̃|�C���^
 * @return	0
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdWazaDel( VM_MACHINE * core )
{
	FIELDSYS_WORK* fsys = core->fsys;
	POKEMON_PARAM * poke;
	u32	buf;
	u8 i;

	u16 t_num = VMGetWorkValue(core);
	u16 w_num = VMGetWorkValue(core);

	poke = PokeParty_GetMemberPointer( SaveData_GetTemotiPokemon(fsys->savedata), t_num);

	PokeParaWazaDelPos(poke,w_num);

	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 *�@�莝���̂킴�ԍ����A�킴�ԍ���
 *
 * @param	core		���z�}�V������\���̂ւ̃|�C���^
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdTemotiWazaNo( VM_MACHINE * core )
{
	FIELDSYS_WORK* fsys = core->fsys;
	POKEMON_PARAM * poke;

	u16* ret_wk	= VMGetWork( core );
	u16 t_num = VMGetWorkValue(core);
	u16 w_num = VMGetWorkValue(core);

	poke = PokeParty_GetMemberPointer( SaveData_GetTemotiPokemon(fsys->savedata), t_num);

	*ret_wk = PokeParaGet( poke, ID_PARA_waza1+w_num, NULL );
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 *	���[���������Ă��邩�`�F�b�N
 *
 * @param	core		���z�}�V������\���̂ւ̃|�C���^
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdPokeMailChk(VM_MACHINE * core)
{
	FIELDSYS_WORK* fsys = core->fsys;
	POKEMON_PARAM * poke;
	u16* ret_wk	= VMGetWork( core );
	u16 tno	= VMGetWorkValue(core);

	poke = PokeParty_GetMemberPointer( SaveData_GetTemotiPokemon(fsys->savedata), tno);
	*ret_wk = PokeParaGet(poke, ID_PARA_item, NULL);

	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 *	�����Ă��郁�[�����폜
 *
 * @param	core		���z�}�V������\���̂ւ̃|�C���^
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdPokeMailDel(VM_MACHINE * core)
{
	FIELDSYS_WORK* fsys = core->fsys;
	POKEMON_PARAM * poke;
	u16 tno	= VMGetWorkValue(core);
	u16 itemno;

	poke = PokeParty_GetMemberPointer( SaveData_GetTemotiPokemon(fsys->savedata), tno);

	itemno = 0;	//�����Ă��Ȃ���Ԃ�
	PokeParaPut( poke, ID_PARA_item, &itemno );

	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 *�@�莝���ɓ���̃|�P���������邩���`�F�b�N
 *
 * @param	core		���z�}�V������\���̂ւ̃|�C���^
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdTemotiPokeChk( VM_MACHINE * core )
{
	FIELDSYS_WORK* fsys = core->fsys;
	POKEMON_PARAM * poke;
	POKEPARTY * temoti;
	u16* ret_wk	= VMGetWork( core );
	u16		num = VMGetWorkValue(core);
	u8 i,max;
	u16 poke_no;

	temoti = SaveData_GetTemotiPokemon(fsys->savedata);
	max = PokeParty_GetPokeCount(temoti);

	*ret_wk = FALSE;
	for(i=0;i<max;i++){
		//�|�P�����ւ̃|�C���^�擾
		poke = PokeParty_GetMemberPointer( SaveData_GetTemotiPokemon(fsys->savedata), i);

		//�^�}�S�͏��O
		if( PokeParaGet( poke, ID_PARA_tamago_flag, NULL ) == 0 ){
			//�|�P�����i���o�[�擾
			poke_no = PokeParaGet( poke, ID_PARA_monsno, NULL );

			if(num == poke_no){		//��v
				*ret_wk = TRUE;
				break;
			}
		}

	}

	return 0;
}

//-----------------------------------------------------------------------------
/**
 *	�u���{���v�̎擾���i�P�|�P�����j
 *	
 */
//-----------------------------------------------------------------------------

BOOL EvCmdChkRibbonCount(VM_MACHINE * core)
{
	POKEMON_PARAM * pp;
	u16* ret_wk	= VMGetWork( core );
	u16		tno	= VMGetWorkValue(core);
	u16 i,cnt;

	pp = PokeParty_GetMemberPointer( SaveData_GetTemotiPokemon(core->fsys->savedata), tno);

	for(i=0,cnt=0;i<RIBBON_MAX;i++){
		if(PokeParaGet(pp, RIBBON_DataGet(i, RIBBON_PARA_POKEPARA ), NULL) != 0){
			cnt++;
		}
	}

	*ret_wk = cnt;

	return 0;
}

//-----------------------------------------------------------------------------
/**
 *	�u���{���v�̎擾���i�S�莝���|�P�������v�̎�ށj
 *	
 */
//-----------------------------------------------------------------------------

BOOL EvCmdChkRibbonCountAll(VM_MACHINE * core)
{
	POKEMON_PARAM * pp;
	POKEPARTY * temoti;
	u16* ret_wk	= VMGetWork( core );
	u16 i,j,cnt,max;

	max = PokeParty_GetPokeCount(SaveData_GetTemotiPokemon(core->fsys->savedata));

	//poke party�擾
	temoti = SaveData_GetTemotiPokemon(core->fsys->savedata);

	for(i=0,cnt=0;i<RIBBON_MAX;i++){
		for(j=0;j<max;j++){
			pp = PokeParty_GetMemberPointer( temoti, j);
			//�^�}�S�`�F�b�N
			if( PokeParaGet( pp, ID_PARA_tamago_flag, NULL ) != 0 ){
				break;
			}

			if(PokeParaGet(pp, RIBBON_DataGet(i, RIBBON_PARA_POKEPARA ), NULL) != 0){
				cnt++;
				break;
			}

		}
	}

	*ret_wk = cnt;

	return 0;
}

//-----------------------------------------------------------------------------
/**
 *	�u���{���v�������Ă��邩
 *	0:�Ȃ��@1:����
 */
//-----------------------------------------------------------------------------
BOOL EvCmdChkRibbon(VM_MACHINE * core)
{
	POKEMON_PARAM * pp;
	u16* ret_wk	= VMGetWork( core );
	u16		tno	= VMGetWorkValue(core);
	u16		rno	= VMGetWorkValue(core);
	u8	flag = 1;

	pp = PokeParty_GetMemberPointer( SaveData_GetTemotiPokemon(core->fsys->savedata), tno);

	*ret_wk = PokeParaGet(pp, RIBBON_DataGet(rno, RIBBON_PARA_POKEPARA ), NULL);

	return 0;
}

//-----------------------------------------------------------------------------
/**
 *	�u���{���v���Z�b�g
 */
//-----------------------------------------------------------------------------
BOOL EvCmdSetRibbon(VM_MACHINE * core)
{
	POKEMON_PARAM * pp;
	u16		tno	= VMGetWorkValue(core);
	u16		rno	= VMGetWorkValue(core);
	u8	flag = 1;

	pp = PokeParty_GetMemberPointer( SaveData_GetTemotiPokemon(core->fsys->savedata), tno);

	PokeParaPut(pp, RIBBON_DataGet(rno, RIBBON_PARA_POKEPARA ), &flag);
	return 0;
}

//-----------------------------------------------------------------------------
/**
 *�@�_���^�}�S�`�F�b�N�S�̔�(�莝���ɂ���:TRUE,���Ȃ�:FALSE)
 */
//-----------------------------------------------------------------------------
BOOL EvCmdDameTamagoChkAll(VM_MACHINE * core)
{

	POKEMON_PARAM * pp;
	POKEPARTY * temoti;
	u16* ret_wk	= VMGetWork( core );
	u16 i,j,max;

	max = PokeParty_GetPokeCount(SaveData_GetTemotiPokemon(core->fsys->savedata));

	//poke party�擾
	temoti = SaveData_GetTemotiPokemon(core->fsys->savedata);

	//�d�l��A�_���^�}�S�@���@�^�}�S���_���^�}�S�t���O�������Ă���
	for(i=0;i<RIBBON_MAX;i++){
		for(j=0;j<max;j++){
			pp = PokeParty_GetMemberPointer( temoti, j);
			if( PokeParaGet( pp, ID_PARA_tamago_flag, NULL ) != 0 ){			//�^�}�S�`�F�b�N
				if( PokeParaGet( pp, ID_PARA_fusei_tamago_flag, NULL ) != 0 ){	//�_���^�}�S�`�F�b�N
					*ret_wk = TRUE;
					return 0;

				}
			}
		}
	}

	*ret_wk = FALSE;

	return 0;
}

//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------
//���g�p
BOOL EvCmdGetTemotiPokeNum( VM_MACHINE * core )
{

	return 0;
}

//============================================================================================
//============================================================================================
