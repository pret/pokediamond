//============================================================================================
/**
 * @file	scr_contest.c
 * @bfief	�X�N���v�g�R�}���h�F�R���e�X�g�֘A
 * @author	Satoshi Nohara
 * @date	06.06.23
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

#include "contest/contest.h"
#include "savedata/perapvoice.h"
#include "field/field_hblank.h"
#include "field/fieldmap_work.h"
#include "savedata/zukanwork.h"
#include "field/zonedata.h"
#include "savedata/fnote_mem.h"


//============================================================================================
//
//	�v���g�^�C�v�錾
//
//============================================================================================
static BOOL EvWaitConSioTimingCheck(VM_MACHINE * core);
static BOOL EvWaitConSioParamInitSet(VM_MACHINE * core);
static BOOL EvWaitConCameraFlashCheck(VM_MACHINE * core);
BOOL EvCmdConSioTimingSend( VM_MACHINE * core );
BOOL EvCmdConSioTimingCheck( VM_MACHINE * core );
BOOL EvCmdConSystemCreate( VM_MACHINE * core );
BOOL EvCmdConSystemExit( VM_MACHINE * core );
BOOL EvCmdConJudgeNameGet( VM_MACHINE * core );
BOOL EvCmdConBreederNameGet( VM_MACHINE * core );
BOOL EvCmdConNickNameGet( VM_MACHINE * core );
BOOL EvCmdConSioParamInitSet( VM_MACHINE * core );
BOOL EvCmdContestProc( VM_MACHINE * core );
BOOL EvCmdConRankNameGet( VM_MACHINE * core );
BOOL EvCmdConTypeNameGet( VM_MACHINE * core );
BOOL EvCmdConVictoryBreederNameGet( VM_MACHINE * core );
BOOL EvCmdConVictoryItemNoGet( VM_MACHINE * core );
BOOL EvCmdConVictoryNickNameGet( VM_MACHINE * core );
BOOL EvCmdConRankingCheck( VM_MACHINE * core );
BOOL EvCmdConVictoryEntryNoGet( VM_MACHINE * core );
BOOL EvCmdConMyEntryNoGet( VM_MACHINE * core );
BOOL EvCmdConObjCodeGet( VM_MACHINE * core );
BOOL EvCmdConPopularityGet( VM_MACHINE * core );
BOOL EvCmdConCameraFlashSet( VM_MACHINE * core );
BOOL EvCmdConCameraFlashCheck( VM_MACHINE * core );
BOOL EvCmdConHBlankStop( VM_MACHINE * core );
BOOL EvCmdConHBlankStart( VM_MACHINE * core );
BOOL EvCmdConEndingSkipCheck( VM_MACHINE * core );
BOOL EvCmdConRecordDisp( VM_MACHINE * core );
BOOL EvCmdConMsgPrintFlagSet( VM_MACHINE * core );
BOOL EvCmdConMsgPrintFlagReset( VM_MACHINE * core );
BOOL EvCmdConNumTagSet( VM_MACHINE * core );
BOOL EvCmdConDeskModeGet( VM_MACHINE * core );
BOOL EvCmdConEntryParamGet( VM_MACHINE * core );
BOOL EvCmdConHaveRibbonCheck( VM_MACHINE * core );
BOOL EvCmdConRibbonNameGet( VM_MACHINE * core );
BOOL EvCmdConAcceNoGet( VM_MACHINE * core );


//============================================================================================
//
//	�R�}���h
//
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * ���M
 *
 * @param	core		���z�}�V������\���̂ւ̃|�C���^
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdConSioTimingSend( VM_MACHINE * core )
{
	void** pwork	= GetEvScriptWorkMemberAdrs( core->fsys, ID_EVSCR_PWORK );
	u16 timing_no	= VMGetWorkValue(core);

	ConScr_SioTimingSend( *pwork, timing_no );
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * �����`�F�b�N
 *
 * @param	core		���z�}�V������\���̂ւ̃|�C���^
 *
 * @return	"1"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdConSioTimingCheck( VM_MACHINE * core )
{
	void** pwork	= GetEvScriptWorkMemberAdrs( core->fsys, ID_EVSCR_PWORK );
	u16 timing_no	= VMGetWorkValue(core);

	//���z�}�V���̔ėp���W�X�^�Ƀ��[�N��ID���i�[
	core->reg[0] = timing_no;

	VM_SetWait( core, EvWaitConSioTimingCheck );
	return 1;
}

//return 1 = �I��
static BOOL EvWaitConSioTimingCheck(VM_MACHINE * core)
{
	void** pwork		= GetEvScriptWorkMemberAdrs( core->fsys, ID_EVSCR_PWORK );
	return ConScr_SioTimingCheck( *pwork, core->reg[0] );
}

//--------------------------------------------------------------------------------------------
/**
 * �V�X�e�����[�N�쐬
 *
 * @param	core		���z�}�V������\���̂ւ̃|�C���^
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdConSystemCreate( VM_MACHINE * core )
{
	STRBUF* buf;
	POKEMON_PARAM * poke;
	void** pwork	= GetEvScriptWorkMemberAdrs( core->fsys, ID_EVSCR_PWORK );
	MYSTATUS* my	= SaveData_GetMyStatus( GameSystem_GetSaveData(core->fsys) );
	u16 rank		= VMGetWorkValue(core);
	u16 type		= VMGetWorkValue(core);
	u16 mode		= VMGetWorkValue(core);
	u16 pos			= VMGetWorkValue(core);
	CONTEST_INIT_DATA cid;
	
	//�|�P�����ւ̃|�C���^�擾
	poke = PokeParty_GetMemberPointer( SaveData_GetTemotiPokemon(core->fsys->savedata), pos );

	//�����̖��O�擾
	buf	= MyStatus_CreateNameString( my, HEAPID_FIELD );

	cid.type = type;
	cid.rank = rank;
	cid.mode = mode;
	cid.hof_flag = SysFlag_GameClearCheck(SaveData_GetEventWork(core->fsys->savedata));
	cid.zenkoku_zukan_flag = 
		ZukanWork_GetZenkokuZukanFlag(SaveData_GetZukanWork(core->fsys->savedata));
	cid.temoti_pos = pos;
	cid.my_pp = poke;
	cid.player_name_str = buf;
	cid.my_status = my;
	cid.imc_save = SaveData_GetImcSaveData(core->fsys->savedata);
	cid.config = SaveData_GetConfig(core->fsys->savedata);
	cid.sv = core->fsys->savedata;
	cid.perap_voice = SaveData_GetPerapVoice(core->fsys->savedata);
	
	*pwork = Contest_SystemCreate(&cid);

	//STRBUF�J��
	STRBUF_Delete( buf );

#if 0
	//�R���e�X�g�́A��t�}�b�v����A�I�[�v�j���O���}�b�v�֐؂�ւ��̂ŁA
	//�X�N���v�g���I������ƁA�R���e�X�g�V�X�e���̃|�C���^���ێ��ł��Ȃ��̂ŁA
	//�Z�[�u���[�N�ɕۑ����Ă���(�b��)
	SysWork_ContestAdrsSet( core->fsys, *pwork );
#endif

	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * �V�X�e�����[�N�폜
 *
 * @param	core		���z�}�V������\���̂ւ̃|�C���^
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdConSystemExit( VM_MACHINE * core )
{
#if 1
	POKEMON_PARAM * poke;
	void** pwork	= GetEvScriptWorkMemberAdrs( core->fsys, ID_EVSCR_PWORK );
	u16 pos			= VMGetWorkValue(core);	//�Q�������|�P�������莝���̉��Ԗڂ��擾
	u32 place_id = ZoneData_GetPlaceNameID(core->fsys->location->zone_id);

	//�|�P�����ւ̃|�C���^�擾
//	poke = PokeParty_GetMemberPointer( SaveData_GetTemotiPokemon(core->fsys->savedata), pos );

	//�e��p�����[�^�X�V
	ConScr_EndParamSet( *pwork, core->fsys->savedata, place_id, core->fsys->fnote );

	Contest_SystemExit( *pwork );
#else
	//�R���e�X�g�́A��t�}�b�v����A�I�[�v�j���O���}�b�v�֐؂�ւ��̂ŁA
	//�X�N���v�g���I������ƁA�R���e�X�g�V�X�e���̃|�C���^���ێ��ł��Ȃ��̂ŁA
	//�Z�[�u���[�N�ɕۑ����Ă���(�b��)
	Contest_SystemExit( SysWork_ContestAdrsGet(core->fsys) );
#endif
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * �R�����擾
 *
 * @param	core		���z�}�V������\���̂ւ̃|�C���^
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdConJudgeNameGet( VM_MACHINE * core )
{
	void** pwork		= GetEvScriptWorkMemberAdrs( core->fsys, ID_EVSCR_PWORK );
	WORDSET** wordset	= GetEvScriptWorkMemberAdrs( core->fsys, ID_EVSCR_WORDSET );
	u16 judge_no		= VMGetWorkValue(core);
	u16 buf_id			= VMGetWorkValue(core);

#if 1
	ConScr_JudgeNameGet( *pwork, judge_no, *wordset, buf_id );
#else
	ConScr_JudgeNameGet( SysWork_ContestAdrsGet(core->fsys), judge_no, *wordset, buf_id );
#endif
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * �u���[�_�[���擾
 *
 * @param	core		���z�}�V������\���̂ւ̃|�C���^
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdConBreederNameGet( VM_MACHINE * core )
{
	void** pwork		= GetEvScriptWorkMemberAdrs( core->fsys, ID_EVSCR_PWORK );
	WORDSET** wordset	= GetEvScriptWorkMemberAdrs( core->fsys, ID_EVSCR_WORDSET );
	u16 entry_no		= VMGetWorkValue(core);
	u16 buf_id			= VMGetWorkValue(core);

#if 1
	ConScr_BreederNameGet( *pwork, entry_no, *wordset, buf_id );
#else
	ConScr_BreederNameGet( SysWork_ContestAdrsGet(core->fsys), entry_no, *wordset, buf_id );
#endif
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * �j�b�N�l�[���擾
 *
 * @param	core		���z�}�V������\���̂ւ̃|�C���^
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdConNickNameGet( VM_MACHINE * core )
{
	void** pwork		= GetEvScriptWorkMemberAdrs( core->fsys, ID_EVSCR_PWORK );
	WORDSET** wordset	= GetEvScriptWorkMemberAdrs( core->fsys, ID_EVSCR_WORDSET );
	u16 entry_no		= VMGetWorkValue(core);
	u16 buf_id			= VMGetWorkValue(core);

#if 1
	ConScr_NickNameGet( *pwork, entry_no, *wordset, buf_id );
#else
	ConScr_NickNameGet( SysWork_ContestAdrsGet(core->fsys), entry_no, *wordset, buf_id );
#endif
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * ���l���^�O�Z�b�g
 *
 * @param	core		���z�}�V������\���̂ւ̃|�C���^
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdConNumTagSet( VM_MACHINE * core )
{
	void** pwork		= GetEvScriptWorkMemberAdrs( core->fsys, ID_EVSCR_PWORK );
	WORDSET** wordset	= GetEvScriptWorkMemberAdrs( core->fsys, ID_EVSCR_WORDSET );
	u16 num				= VMGetWorkValue(core);
	u16 buf_id			= VMGetWorkValue(core);

	WORDSET_RegisterNumber(*wordset, buf_id, num, 1, 
		NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT);
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * �ʐM�p�Ƀ��[�N�̏����ݒ�ƍŏ��̒ʐM���s���^�X�N�𐶐�
 *
 * @param	core		���z�}�V������\���̂ւ̃|�C���^
 *
 * @return	"1"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdConSioParamInitSet( VM_MACHINE * core )
{
	void** pwork		= GetEvScriptWorkMemberAdrs( core->fsys, ID_EVSCR_PWORK );
	Contest_SioParamInitSet( *pwork );
	VM_SetWait( core, EvWaitConSioParamInitSet );
	return 1;
}

//return 1 = �I��
static BOOL EvWaitConSioParamInitSet(VM_MACHINE * core)
{
	void** pwork		= GetEvScriptWorkMemberAdrs( core->fsys, ID_EVSCR_PWORK );
#if 1
	return Contest_SioFastDataEndCheck( *pwork );
#else
	return Contest_SioFastDataEndCheck( SysWork_ContestAdrsGet(core->fsys) );
#endif
}

//--------------------------------------------------------------------------------------------
/**
 * �R���e�X�g�Ăяo��
 *
 * @param	core		���z�}�V������\���̂ւ̃|�C���^
 *
 * @return	"1"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdContestProc( VM_MACHINE * core )
{
	void** pwork = GetEvScriptWorkMemberAdrs( core->fsys, ID_EVSCR_PWORK );
#if 1
	EventCmd_ContestProc( core->event_work, *pwork );	//�C�x���g�؂�ւ�
#else
	EventCmd_ContestProc( core->event_work, SysWork_ContestAdrsGet(core->fsys) );//�C�x���g�؂�ւ�
#endif
	//VM_SetWait( core, EvCmdWaitSubProcEnd );
	return 1;
}

//--------------------------------------------------------------------------------------------
/**
 * �����N���擾
 *
 * @param	core		���z�}�V������\���̂ւ̃|�C���^
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdConRankNameGet( VM_MACHINE * core )
{
	void** pwork		= GetEvScriptWorkMemberAdrs( core->fsys, ID_EVSCR_PWORK );
	WORDSET** wordset	= GetEvScriptWorkMemberAdrs( core->fsys, ID_EVSCR_WORDSET );
	u16 buf_id			= VMGetWorkValue(core);

#if 1
	ConScr_RankNameGet( *pwork, *wordset, buf_id );
#else
	ConScr_RankNameGet( SysWork_ContestAdrsGet(core->fsys), *wordset, buf_id );
#endif
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * �^�C�v���擾
 *
 * @param	core		���z�}�V������\���̂ւ̃|�C���^
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdConTypeNameGet( VM_MACHINE * core )
{
	void** pwork		= GetEvScriptWorkMemberAdrs( core->fsys, ID_EVSCR_PWORK );
	WORDSET** wordset	= GetEvScriptWorkMemberAdrs( core->fsys, ID_EVSCR_WORDSET );
	u16 buf_id			= VMGetWorkValue(core);

#if 1
	ConScr_TypeNameGet( *pwork, *wordset, buf_id );
#else
	ConScr_TypeNameGet( SysWork_ContestAdrsGet(core->fsys), *wordset, buf_id );
#endif
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * �D���Җ��擾
 *
 * @param	core		���z�}�V������\���̂ւ̃|�C���^
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdConVictoryBreederNameGet( VM_MACHINE * core )
{
	void** pwork		= GetEvScriptWorkMemberAdrs( core->fsys, ID_EVSCR_PWORK );
	WORDSET** wordset	= GetEvScriptWorkMemberAdrs( core->fsys, ID_EVSCR_WORDSET );
	u16 buf_id			= VMGetWorkValue(core);

#if 1
	ConScr_VictoryBreederNameGet( *pwork, *wordset, buf_id );
#else
	ConScr_VictoryBreederNameGet( SysWork_ContestAdrsGet(core->fsys), *wordset, buf_id );
#endif
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * �D�����i�i���o�[�擾
 *
 * @param	core		���z�}�V������\���̂ւ̃|�C���^
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdConVictoryItemNoGet( VM_MACHINE * core )
{
	void** pwork		= GetEvScriptWorkMemberAdrs( core->fsys, ID_EVSCR_PWORK );
	u16* ret_wk			= VMGetWork( core );

#if 1
	*ret_wk = ConScr_VictoryItemNoGet( *pwork );
#else
	*ret_wk = ConScr_VictoryItemNoGet( SysWork_ContestAdrsGet(core->fsys) );
#endif
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * �D�������u���[�_�[�̃|�P�����j�b�N�l�[�����擾
 *
 * @param	core		���z�}�V������\���̂ւ̃|�C���^
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdConVictoryNickNameGet( VM_MACHINE * core )
{
	void** pwork		= GetEvScriptWorkMemberAdrs( core->fsys, ID_EVSCR_PWORK );
	WORDSET** wordset	= GetEvScriptWorkMemberAdrs( core->fsys, ID_EVSCR_WORDSET );
	u16 buf_id			= VMGetWorkValue(core);

	ConScr_VictoryNickNameGet( *pwork, *wordset, buf_id );
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * ���Q�����Ă����R���e�X�g�Ŏ��������ʂ����������擾
 *
 * @param	core		���z�}�V������\���̂ւ̃|�C���^
 *
 * @return	"0"
 *
 * @li	����(0�I���W���ł��B 0=1�ʁA1=2�ʁA2=3�ʁA3=4��)
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdConRankingCheck( VM_MACHINE * core )
{
	void** pwork		= GetEvScriptWorkMemberAdrs( core->fsys, ID_EVSCR_PWORK );
	u16* ret_wk			= VMGetWork( core );

	*ret_wk = ConScr_RankingCheck( *pwork );
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * �D�������u���[�_�[�̃G���g���[�ԍ����擾����
 *
 * @param	core		���z�}�V������\���̂ւ̃|�C���^
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdConVictoryEntryNoGet( VM_MACHINE * core )
{
	void** pwork		= GetEvScriptWorkMemberAdrs( core->fsys, ID_EVSCR_PWORK );
	u16* ret_wk			= VMGetWork( core );

	*ret_wk = ConScr_VictoryEntryNoGet( *pwork );
	OS_TPrintf("victory_entry = %d\n", *ret_wk);
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * �����̃G���g���[�ԍ����擾
 *
 * @param	core		���z�}�V������\���̂ւ̃|�C���^
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdConMyEntryNoGet( VM_MACHINE * core )
{
	void** pwork		= GetEvScriptWorkMemberAdrs( core->fsys, ID_EVSCR_PWORK );
	u16* ret_wk			= VMGetWork( core );

	*ret_wk = ConScr_MyEntryNoGet( *pwork );
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * OBJ�R�[�h���擾
 *
 * @param	core		���z�}�V������\���̂ւ̃|�C���^
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdConObjCodeGet( VM_MACHINE * core )
{
	void** pwork		= GetEvScriptWorkMemberAdrs( core->fsys, ID_EVSCR_PWORK );
	u16 entry_no		= VMGetWorkValue( core );
	u16* ret_wk			= VMGetWork( core );

	*ret_wk = ConScr_OBJCodeGet( *pwork, entry_no );
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * �l�C���擾
 *
 * @param	core		���z�}�V������\���̂ւ̃|�C���^
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdConPopularityGet( VM_MACHINE * core )
{
	void** pwork		= GetEvScriptWorkMemberAdrs( core->fsys, ID_EVSCR_PWORK );
	u16 entry_no		= VMGetWorkValue( core );
	u16* ret_wk			= VMGetWork( core );

	*ret_wk = ConScr_PopularityGet( *pwork, entry_no );
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * ��t�i���o�[(�V���O��DESK_SINGLE�A�}���`DESK_MULTI, ���KDESK_PRACTICE)���擾
 *
 * @param	core		���z�}�V������\���̂ւ̃|�C���^
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdConDeskModeGet( VM_MACHINE * core )
{
	void** pwork		= GetEvScriptWorkMemberAdrs( core->fsys, ID_EVSCR_PWORK );
	u16* ret_wk			= VMGetWork( core );

	*ret_wk = ConScr_DeskModeGet(*pwork);
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * �R���e�X�g�V�X�e�����[�N���烉���N�⃂�[�h�Ȃǂ��擾����
 *
 * @param	core		���z�}�V������\���̂ւ̃|�C���^
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdConEntryParamGet( VM_MACHINE * core )
{
	void** pwork		= GetEvScriptWorkMemberAdrs( core->fsys, ID_EVSCR_PWORK );
	u16* ret_rank			= VMGetWork( core );
	u16* ret_type			= VMGetWork( core );
	u16* ret_mode			= VMGetWork( core );
	u16* ret_temoti_pos		= VMGetWork( core );

	ConScr_EntryParamGet(*pwork, ret_rank, ret_type, ret_mode, ret_temoti_pos);
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * �Q�����Ă���R���e�X�g�ŗD���������ɖႦ�郊�{�������Ɏ����Ă��邩�`�F�b�N
 *
 * @param	core		���z�}�V������\���̂ւ̃|�C���^
 *
 * @return	"0"
 *
 * TRUE:���Ɏ����Ă���(�D���o���ς�)�B�@FALSE:�����Ă��Ȃ�
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdConHaveRibbonCheck( VM_MACHINE * core )
{
	void** pwork		= GetEvScriptWorkMemberAdrs( core->fsys, ID_EVSCR_PWORK );
	u16* ret_wk			= VMGetWork( core );

	*ret_wk = ConScr_HaveRibbonCheck(*pwork);
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * �Q�����Ă���R���e�X�g�ŗD���������ɖႦ�郊�{���̖��O���擾
 *
 * @param	core		���z�}�V������\���̂ւ̃|�C���^
 *
 * @return	"0"
 *
 * TRUE:���Ɏ����Ă���(�D���o���ς�)�B�@FALSE:�����Ă��Ȃ�
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdConRibbonNameGet( VM_MACHINE * core )
{
	void** pwork		= GetEvScriptWorkMemberAdrs( core->fsys, ID_EVSCR_PWORK );
	WORDSET** wordset	= GetEvScriptWorkMemberAdrs( core->fsys, ID_EVSCR_WORDSET );
	u16 buf_id			= VMGetWorkValue(core);

	ConScr_RibbonItemNameGet(*pwork, *wordset, buf_id, HEAPID_WORLD);
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * ��t�ŖႦ��A�N�Z�T���ԍ����擾
 *
 * @param	core		���z�}�V������\���̂ւ̃|�C���^
 *
 * @return	"0"
 *
 * ret_wk = �A�N�Z�T���ԍ��B���D�����Ă��Ȃ� or ���Ɍ��E���܂ŏ������Ă���ꍇ��0xffff
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdConAcceNoGet( VM_MACHINE * core )
{
	void** pwork		= GetEvScriptWorkMemberAdrs( core->fsys, ID_EVSCR_PWORK );
	u16* ret_wk			= VMGetWork( core );

	*ret_wk = ConScr_AcceNoGet(*pwork);
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * �R���e�X�g�̃��b�Z�[�W����ݒ���s��
 *
 * @param	core		���z�}�V������\���̂ւ̃|�C���^
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdConMsgPrintFlagSet( VM_MACHINE * core )
{
	void** pwork		= GetEvScriptWorkMemberAdrs( core->fsys, ID_EVSCR_PWORK );

	ConScr_MsgPrintFlagSet(*pwork);
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * �R���e�X�g�̃��b�Z�[�W����ݒ�����Z�b�g����
 *
 * @param	core		���z�}�V������\���̂ւ̃|�C���^
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdConMsgPrintFlagReset( VM_MACHINE * core )
{
	void** pwork		= GetEvScriptWorkMemberAdrs( core->fsys, ID_EVSCR_PWORK );

	ConScr_MsgPrintFlagReset(*pwork);
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * �J�����̃t���b�V���G�t�F�N�g�^�X�N�𐶐�����
 *
 * @param	core		���z�}�V������\���̂ւ̃|�C���^
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdConCameraFlashSet( VM_MACHINE * core )
{
	void** pwork		= GetEvScriptWorkMemberAdrs( core->fsys, ID_EVSCR_PWORK );
	u16 entry_no		= VMGetWorkValue( core );

	ConScr_FlashTaskCreate(*pwork, entry_no);
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * �J�����̃t���b�V���G�t�F�N�g���I�����Ă��邩�m�F
 *
 * @param	core		���z�}�V������\���̂ւ̃|�C���^
 *
 * @return	"1"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdConCameraFlashCheck( VM_MACHINE * core )
{
	void** pwork		= GetEvScriptWorkMemberAdrs( core->fsys, ID_EVSCR_PWORK );

	VM_SetWait(core, EvWaitConCameraFlashCheck);
	return 1;
}

//return 1 = �I��
static BOOL EvWaitConCameraFlashCheck(VM_MACHINE * core)
{
	void** pwork		= GetEvScriptWorkMemberAdrs( core->fsys, ID_EVSCR_PWORK );

	if(ConScr_FlashTaskCheck(*pwork) == TRUE){
		return 1;
	}
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * �t�B�[���h��H�u�����N���~����
 *
 * @param	core		���z�}�V������\���̂ւ̃|�C���^
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdConHBlankStop( VM_MACHINE * core )
{
	FLDHBLANK_SYS_Stop(core->fsys->fldmap->hblanksys);
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * EvCmdConHBlankStop�Œ�~�������t�B�[���h��H�u�����N���ĊJ������
 *
 * @param	core		���z�}�V������\���̂ւ̃|�C���^
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdConHBlankStart( VM_MACHINE * core )
{
	FLDHBLANK_SYS_Start(core->fsys->fldmap->hblanksys);
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * CPU���D���������A���͒ʐM�ΐ�̎��̓G���f�B���O�̈ꕔ���X�L�b�v����
 *
 * @param	core		���z�}�V������\���̂ւ̃|�C���^
 *
 * @return	"0"
 *
 * ret_wk�F1�ACPU���D��or�ʐM�ΐ�
 * ret_wk�F0�A�ǂ���̏������������Ȃ�����
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdConEndingSkipCheck( VM_MACHINE * core )
{
	void** pwork		= GetEvScriptWorkMemberAdrs( core->fsys, ID_EVSCR_PWORK );
	u16* ret_wk			= VMGetWork( core );
	int entry_no, sio_flag, cpu_flag, tutorial, practice;
	
	ConScr_VictoryParamGet(*pwork, &entry_no, &sio_flag, &cpu_flag, &tutorial, &practice);
	if(sio_flag == TRUE || cpu_flag == TRUE || tutorial == TRUE || practice == TRUE){
		*ret_wk = 1;
	}
	else{
		*ret_wk = 0;
	}
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * �R���e�X�g�ʐM�ΐ퐬�щ�ʌĂяo��
 *
 * @param	core		���z�}�V������\���̂ւ̃|�C���^
 *
 * @return	"1"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdConRecordDisp( VM_MACHINE * core )
{
	EventCmd_ConRecordDisp(core->event_work);
	return 1;
}

