//============================================================================================
/**
 * @file	scr_sodateya.c
 * @bfief	�X�N���v�g�R�}���h�F�����Ă�֘A
 * @author	Tomomichi Ohta
 * @date	06.06.26
 */
//============================================================================================
#include "common.h"
#include "system/lib_pack.h"
#include "fieldsys.h"

#include "script.h"
#include "scrcmd_def.h"
#include "field/eventflag.h"
#include "field/evwkdef.h"
#include "sysflag.h"
#include "syswork.h"

#include "savedata/sodateyadata.h"
#include "sodateya.h"

#include "scr_sodateya.h"

//============================================================================================
//
//	�R�}���h
//
//============================================================================================


//============================================================================================
//
//	��ĉ��֘A
//
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * �����Ă�@���O�̎擾
 *
 * @param	core		���z�}�V������\���̂ւ̃|�C���^
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdGetSodateyaName( VM_MACHINE * core )
{
	FIELDSYS_WORK* fsys = core->fsys;
	SAVEDATA * sv = fsys->savedata;
	WORDSET** wordset	= GetEvScriptWorkMemberAdrs( fsys, ID_EVSCR_WORDSET );

	SodateyaNameSet(SaveData_GetSodateyaWork(sv),*wordset);

	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * �����Ă�@��������̏�Ԏ擾
 *
 * @param	core		���z�}�V������\���̂ւ̃|�C���^
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdGetSodateyaZiisan( VM_MACHINE * core )
{
	u16 * work;
	FIELDSYS_WORK* fsys = core->fsys;
	SAVEDATA * sv = fsys->savedata;
	SODATEYA_WORK *sodateya;
	work = VMGetWork( core );

	sodateya = (SODATEYA_WORK *)(SaveData_Get(sv,GMDATA_ID_SODATEYA));
	*work = SodateyaZiisannCheck(sodateya);

	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 *			�����Ă�ɂ���^�}�S������
 * @brief   �����Ă�p�̃��[�N����A�^�}�S����������N���A����
 * 
 * @param	core		���z�}�V������\���̂ւ̃|�C���^
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdDelSodateyaEgg( VM_MACHINE * core )
{
	FIELDSYS_WORK* fsys = core->fsys;
	SAVEDATA * sv = fsys->savedata;
	SODATEYA_WORK *sodateya;
	sodateya = (SODATEYA_WORK *)(SaveData_Get(sv,GMDATA_ID_SODATEYA));

	DelSodateyaTamagoSub(sodateya);

	return 0;
}


BOOL EvCmdGetSodateyaEgg( VM_MACHINE * core )
{
	FIELDSYS_WORK* fsys = core->fsys;
	SAVEDATA * sv = fsys->savedata;
	SODATEYA_WORK *sodateya = (SODATEYA_WORK *)(SaveData_Get(sv,GMDATA_ID_SODATEYA));
	POKEPARTY     *temoti   = SaveData_GetTemotiPokemon(fsys->savedata);
	MYSTATUS* my	= SaveData_GetMyStatus( GameSystem_GetSaveData(core->fsys) );

	PokeTamagoDel(sodateya, temoti, my );

//�쐬�� 060302 by tomo
//xxxxx

	return 0;
}


BOOL EvCmdHikitoriPoke( VM_MACHINE * core )
{
	FIELDSYS_WORK* fsys = core->fsys;
	SODATEYA_WORK *sodateya;
	POKEPARTY * temoti;
	WORDSET** wordset		= GetEvScriptWorkMemberAdrs( fsys, ID_EVSCR_WORDSET );
	SAVEDATA * sv = fsys->savedata;
	u16 *ret_wk		= VMGetWork(core);
	u8 no		= VMGetWorkValue(core);
	sodateya = (SODATEYA_WORK *)(SaveData_Get(sv,GMDATA_ID_SODATEYA));
	temoti = SaveData_GetTemotiPokemon(fsys->savedata);

	*ret_wk = PokeHikitoriSub(temoti,*wordset,sodateya,no);

	return 0;
}

// =================================================================
/**
 * @brief ������藿���擾
 * @param  none
 * @retval  ������Ԃ��i�����Ƃ��āA���[�N�ɔԍ����Z�b�g����K�v������܂��j
 * @retval  �����o�b�t�@�O�֗����Z�b�g�A���������[�N�֕Ԃ�
 */
// =================================================================
BOOL EvCmdHikitoriRyoukin( VM_MACHINE * core )
{
	FIELDSYS_WORK* fsys = core->fsys;
	SODATEYA_WORK *sodateya;
	WORDSET** wordset		= GetEvScriptWorkMemberAdrs( fsys, ID_EVSCR_WORDSET );
	SAVEDATA * sv = fsys->savedata;
	u16 * work  = VMGetWork(core);
	u8 no		= VMGetWorkValue(core);
	sodateya = (SODATEYA_WORK *)(SaveData_Get(sv,GMDATA_ID_SODATEYA));

	*work = PokeHikitoriRyoukinSub(sodateya,no,*wordset);
	return 0;
}

BOOL EvCmdSodatePokeLevelStr( VM_MACHINE * core )
{
	FIELDSYS_WORK* fsys = core->fsys;
	SAVEDATA * sv = fsys->savedata;
	SODATEYA_WORK *sodateya;
	WORDSET** wordset	= GetEvScriptWorkMemberAdrs( core->fsys, ID_EVSCR_WORDSET );
	u16 *ret_wk		= VMGetWork( core );
	u16 no			= VMGetWorkValue( core );

	sodateya = (SODATEYA_WORK *)(SaveData_Get(sv,GMDATA_ID_SODATEYA));
	*ret_wk = SodatePokeLevelSet(sodateya,no,*wordset );

	return 0;
}

BOOL EvCmdMsgAzukeSet( VM_MACHINE * core )
{
	FIELDSYS_WORK* fsys = core->fsys;
	POKEPARTY * temoti;
	WORDSET** wordset	= GetEvScriptWorkMemberAdrs( core->fsys, ID_EVSCR_WORDSET );
	u16 wk_no			= VMGetU16( core );		//�����݂͂O�Œ�Ȃ̂Ŏg�p����
	u16 no				= VMGetWorkValue( core );
	u16* ret_wk			= VMGetWork( core );

	temoti = SaveData_GetTemotiPokemon(fsys->savedata);
	*ret_wk = SodateyaAzukeName(temoti,no,*wordset );

	return 0;
}

BOOL EvCmdSetSodateyaPoke( VM_MACHINE * core )
{
	FIELDSYS_WORK* fsys = core->fsys;
	SAVEDATA * sv = fsys->savedata;
	SODATEYA_WORK *sodateya;
	POKEPARTY * temoti;
	u8 no				= VMGetWorkValue(core);

	temoti = SaveData_GetTemotiPokemon(fsys->savedata);
	sodateya = (SODATEYA_WORK *)(SaveData_Get(sv,GMDATA_ID_SODATEYA));
	PokeSodateSet(temoti,no,sodateya,sv);

	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * �����Ă�X�N���v�g�F�������LIST�p�|�P���������Z�b�g
 *
 * @param	core		���z�}�V������\���̂ւ̃|�C���^
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdHikitoriListNameSet( VM_MACHINE * core )
{
	FIELDSYS_WORK* fsys = core->fsys;
	SAVEDATA * sv = fsys->savedata;
	WORDSET** wordset	= GetEvScriptWorkMemberAdrs( core->fsys, ID_EVSCR_WORDSET );

	u8	buf_id		= VMGetWorkValue( core );
	u8	buf2_id		= VMGetWorkValue( core );
	u8	buf3_id		= VMGetWorkValue( core );
	u8	no			= VMGetWorkValue( core );

	SodateyaListNameSet(SaveData_GetSodateyaWork(sv),buf_id,buf2_id,buf3_id,no,*wordset);
	return 0;
}


//--------------------------------------------------------------------------------------------
/**
 * �����Ă�X�N���v�g�F�a���Ă���2�̂̑����Q�b�g
 *
 * @param	core		���z�}�V������\���̂ւ̃|�C���^
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdGetSodateyaAishou( VM_MACHINE * core )
{
	FIELDSYS_WORK* fsys = core->fsys;
	SAVEDATA * sv = fsys->savedata;
	SODATEYA_WORK *sodateya;
	u16* ret_wk	= VMGetWork( core );

	sodateya = (SODATEYA_WORK *)(SaveData_Get(sv,GMDATA_ID_SODATEYA));

	*ret_wk = SodateyaGetAffinity( sodateya );

	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * �����Ă�X�N���v�g�F�^�}�S�����܂�Ă��邩�i�P�F����A�O�F���Ȃ��j
 *
 * @param	core		���z�}�V������\���̂ւ̃|�C���^
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdGetSodateyaTamagoCheck( VM_MACHINE * core )
{
	FIELDSYS_WORK* fsys = core->fsys;
	SAVEDATA * sv = fsys->savedata;
	SODATEYA_WORK *sodateya;
	u16* ret_wk	= VMGetWork( core );

	sodateya = (SODATEYA_WORK *)(SaveData_Get(sv,GMDATA_ID_SODATEYA));

	*ret_wk = SodateyaWork_GetEggFlag(sodateya);

	return 0;
}


//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------
/*���g�p�}���h*/


//060625 �g�p���܂���
BOOL EvCmdHikitoriList( VM_MACHINE * core )
{
	FIELDSYS_WORK* fsys = core->fsys;
	u16* ret_wk			= VMGetWork( core );

	return 0;
}

//060625 �g�p���܂���
BOOL EvCmdMsgSodateyaAishou( VM_MACHINE * core )
{
	FIELDSYS_WORK* fsys = core->fsys;

	return 0;
}

//060625 �g�p���܂���
BOOL EvCmdMsgExpandBuf( VM_MACHINE * core )
{
	FIELDSYS_WORK* fsys = core->fsys;

	return 0;
}

//060625 �g�p���܂���
BOOL EvCmdSodateyaPokeList( VM_MACHINE * core )
{
	FIELDSYS_WORK* fsys = core->fsys;
	u16* ret_wk			= VMGetWork( core );

	return 0;
}

//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------
