//============================================================================================
/**
 * @file	scr_pokelot.c
 * @bfief	�|�P�����N�W			����풆�̈�Ɉړ�����Ɠ��삵�܂���
 * @author	Tomomichi Ohta
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

#include "scr_tool.h"
#include "poketool/boxdata.h"

#include "scr_pokelot.h"
#include "poketool/boxdata.h"

//===========================================
// �}�N��
//===========================================
#define POKELOT_MAXNUMBER  (65535)  // ���I�i���o�[�ő�l

//===========================================
// �v���g�^�C�v
//===========================================
static u8 check_hit_keta(u16 val1, u16 val2);


//============================================================================================
//						�N�W�֘A
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * �N�W�̂�����ԍ��擾
 * @brief   �N�W�̂�����ԍ��擾
 * 
 * @param	core		���z�}�V������\���̂ւ̃|�C���^
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
#define POKELOT_MAXNUMBER  (65535)  /* ���I�i���o�[�ő�l*/

BOOL EvCmdGetKujiAtariNum(VM_MACHINE * core)
{
	EVENTWORK* ev = SaveData_GetEventWork(core->fsys->savedata);
	u16* ret_wk			= VMGetWork( core );
	u32 value;

	value = SysWork_pokelot_value_get(ev);
	*ret_wk = (u16)(value % (POKELOT_MAXNUMBER+1));

	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * �N�W�̂�����`�F�b�N
 * @brief   �N�W�̂�����`�F�b�N
 * 
 * @param	core		���z�}�V������\���̂ւ̃|�C���^
 *
 * @return	"1"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdKujiAtariChk(VM_MACHINE * core)
{
	FIELDSYS_WORK * fsys	= core->fsys;
	POKEMON_PARAM * poke;
	POKEMON_PASO_PARAM* ppp;
	BOX_DATA* boxData = SaveData_GetBoxData( fsys->savedata );
	u16* ret_wk1			= VMGetWork( core );
	u16* ret_wk2			= VMGetWork( core );
	u16* ret_wk3			= VMGetWork( core );
	u16 num			= VMGetWorkValue( core );
	u16 max,i,j;
	u16 t_keta,t_no;
	u16 pc_keta,pc_no;
	u32 id;
	u8  keta;
	u32 pos, trayno, monsno;

	max = PokeParty_GetPokeCount(SaveData_GetTemotiPokemon(fsys->savedata));

	for(t_keta=0,t_no=0,i=0;i<max;i++){
		poke = PokeParty_GetMemberPointer( SaveData_GetTemotiPokemon(fsys->savedata), i);

		//�����X�^�[�ԍ��擾(0�ȊO�Ȃ�^�}�S�j
		if( PokeParaGet( poke, ID_PARA_tamago_flag, NULL ) == 0 ){

			id = (PokeParaGet( poke, ID_PARA_id_no, NULL ) & 0xffff);

			keta = check_hit_keta(num, id);	//�����擾
			if((keta > 0)&&(t_keta < keta)) {		//����or�������Ƃ�
				t_keta = keta;
				t_no = i;
			}
		}
	}


	for( pc_keta = 0, pc_no = 0,trayno = 0; trayno < BOX_MAX_TRAY; trayno++ ) {
		for( pos = 0; pos < BOX_MAX_POS; pos++ ){
			ppp = BOXDAT_GetPokeDataAddress( boxData, trayno, pos );
			monsno = PokePasoParaGet( ppp, ID_PARA_monsno, NULL );
			if( monsno ){
				if( PokePasoParaGet( ppp, ID_PARA_tamago_flag, NULL ) == 0 ){

					id = (PokePasoParaGet( ppp, ID_PARA_id_no, NULL ) & 0xffff);

					keta = check_hit_keta(num, id);	//�����擾
					if((keta > 0)&&(pc_keta < keta)) {		//����or�������Ƃ�
						pc_keta = keta;
						pc_no = trayno * BOX_MAX_POS + pos;
					}
				}
			}
		}
	}

	if((t_keta == 0)&&(pc_keta==0)){		//�ǂ�����O��
		*ret_wk1 = 0;
		*ret_wk2 = 0;
		*ret_wk3 = 0;
	}else{
		if(t_keta >= pc_keta){		//�莝���̂ق�����𓖂����Ă���(or�����j
			*ret_wk1 = t_no;
			*ret_wk2 = t_keta;
			*ret_wk3 = 0;
		}else{						//PC�̂ق�����
			*ret_wk1 = pc_no;
			*ret_wk2 = pc_keta;
			*ret_wk3 = 1;
		}
	}
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * �N�W�̂�����ԍ�������
 * @brief   �N�W�̂�����ԍ�������
 * 
 * @param	core		���z�}�V������\���̂ւ̃|�C���^
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdKujiAtariInit(VM_MACHINE * core)
{
	EVENTWORK* ev = SaveData_GetEventWork(core->fsys->savedata);

	SysWorkInitPokeLot(ev);

	return 0;
}

//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------

#if 0
/*==============================================================
==  AnswerWork �ɓ����Ă���i���o�[�œ��I�`�F�b�N
==  �y���ʁz
==    ScriptParameter0  ... 0(�͂���j�`4�i�����j
==  ��ScriptParameter1  ... ���炦��A�C�e���i���o�[
==  ��ScriptParameter2  ... ���I�|�P�������i0:�Ă��� 1:�{�b�N�X�j
==  ��StrTempBuffer0   ... ���I�|�P������
==
==  �����I���Ȃ������ꍇ�A�����̒l�͓��e���ۏ؂���܂���
==============================================================*/
void CheckPokeLotNumber(void)
{
	u32 id;
	u16 monsbox, monspos, i, j;
	u8  keta;

	ScriptParameter0 = 0;
	monsbox = monspos = 0;

	// �莝���`�F�b�N
	for(i = 0; i < TEMOTI_POKEMAX; i++)
	{
		if(PokeParaGet(PokeParaMine+i, ID_monsno) != 0)
		{
			if(PokeParaGet(PokeParaMine+i, ID_tamago_flag) == 0)
			{
				id = (PokeParaGet(PokeParaMine + i, ID_id_no) & 0xffff);
				keta = check_hit_keta(AnswerWork, id);
				if(keta > ScriptParameter0 && keta > 1)
				{
					ScriptParameter0 = keta - 1;
					monsbox = BOX_KAZU;
					monspos = i;
				}
			}
		}else{
			break;
		}
	}

	// �{�b�N�X�`�F�b�N
	for(i = 0; i < BOX_KAZU; i++)
	{
		for(j = 0; j < BOX_PM_KAZU; j++)
		{
			if(PokePasoParaGet(&(BoxData.PPPBox[i][j]), ID_monsno) != 0)
			{
				if(PokePasoParaGet(&(BoxData.PPPBox[i][j]), ID_tamago_flag) == 0)
				{
					id = (PokePasoParaGet(&(BoxData.PPPBox[i][j]), ID_id_no) & 0xffff);
					keta = check_hit_keta(AnswerWork, id);
					if(keta > ScriptParameter0 && keta > 1)
					{
						ScriptParameter0 = keta - 1;
						monsbox = i;
						monspos = j;
					}
				}
			}
		}
	}

	// ���I���Ă���
	if(ScriptParameter0)
	{
		ScriptParameter1 = PokeLotPrizeTable[ScriptParameter0-1];
		if(monsbox == BOX_KAZU){
			ScriptParameter2 = 0;
			PokeParaGet(PokeParaMine + monspos, ID_nickname, StrTempBuffer0);
		}else{
			ScriptParameter2 = 1;
			PokePasoParaGet(&(BoxData.PPPBox[monsbox][monspos]), ID_nickname, StrTempBuffer0);
		}
		NickNameCutOff(StrTempBuffer0);
	}
}
#endif


/*====================================================*/
/*  ��v�������v�Z                                    */
/*  val1, val2   ��r���鐔�l                         */
/*  return:  ��v�����i0�`5�j                         */
/*====================================================*/
static u16 V1 = 0, V2 = 0;

static u8 check_hit_keta(u16 val1, u16 val2)
{
	u8  i, hit;

	hit = 0;

	for(i = 0; i < 5; i++)
	{
		V1 = val1 % 10;
		V2 = val2 % 10;
		if((val1%10) != (val2%10)){ break; }
		val1 /= 10;
		val2 /= 10;
		hit++;
	}

	return hit;
}

/*====================================================*/
/*====================================================*/
