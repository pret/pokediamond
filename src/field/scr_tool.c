//============================================================================================
/**
 * @file	scr_tool.c
 * @bfief	�X�N���v�g�Ŏg�p����v���O����
 * @author	Satoshi Nohara
 * @date	05.11.16
 */
//============================================================================================
#include "common.h"
#include "gflib/msg_print.h"
#include "system/lib_pack.h"
#include "system/window.h"
//#include "fieldmap.h"
#include "fieldsys.h"
#include "zonedata.h"
#include "mapdefine.h"
#include "itemtool/itemsym.h"							//ITEM_KIZUGUSURI
#include "poketool/monsno.h"
#include "field/eventflag.h"							//EventWork_CheckEventFlag
#include "field/evwkdef.h"								//FH_FLAG_START
#include "field/fieldobj.h"
#include "script.h"										//ID_HIDE_ITEM_SCR_OFFSET
#include "scr_tool.h"									//HIDEITEM_ID_FLAG

#include "msgdata/msg_gameover.h"						//msg_
#include "msgdata/msg_hyouka.h"

#include "system/wipe.h"


//============================================================================================
//
//	�v���g�^�C�v�錾	
//
//============================================================================================
u16 GetNumKeta(u32 num);
u16 WazaMachineItemNoCheck( u16 itemno );

u16 GetShinouZukanHyoukaMsgID( u16 num ,u16 c04_arrive);
u16 GetZenkokuZukanHyoukaMsgID( u16 num ,u16 sex);


//============================================================================================
//
//	���̑�
//
//============================================================================================

//--------------------------------------------------------------
/**
 * �n���ꂽ�l�̌������擾
 *
 * @param   num			�l
 *
 * @retval  "����"
 */
//--------------------------------------------------------------
u16 GetNumKeta(u32 num)
{
	if( num / 10 == 0 )	return 1;
	else if( num / 100 == 0 ) return 2;
	else if( num / 1000 == 0 ) return 3;
	else if( num / 10000 == 0 ) return 4;
	else if( num / 100000 == 0 ) return 5;
	else if( num / 1000000 == 0 ) return 6;
	else if( num / 10000000 == 0 ) return 7;
	else if( num / 100000000 == 0 ) return 8;

	return 1;	//���Ă͂܂�Ȃ�������P����Ԃ�
}

//--------------------------------------------------------------
/**
 * �Z�}�V���̃A�C�e���i���o�[���`�F�b�N
 *
 * @param   itemno		�A�C�e���i���o�[
 *
 * @retval  TRUE		�Z�}�V��
 * @retval  FALSE		����ȊO
 */
//--------------------------------------------------------------
u16 WazaMachineItemNoCheck( u16 itemno )
{
	//�Z�}�V�����`�F�b�N
	if( (itemno >= ITEM_WAZAMASIN01) && (itemno <= ITEM_HIDENMASIN08) ){
		return TRUE;
	}

	return FALSE;
}


//============================================================================================
//
//	�}�ӕ]��
//
//============================================================================================

//--------------------------------------------------------------
/**
 * �V���I�E�}�ӕ]�����b�Z�[�WID�擾
 *
 * @param   num		�B��6�C��������������
 * @param	c04_arrive	c04�n�N�^�C�V�e�B�̓����t���O
 *
 * @retval  "���b�Z�[�WID"
 */
//--------------------------------------------------------------
u16 GetShinouZukanHyoukaMsgID( u16 num ,u16 c04_arrive)
{
	//�V���I�E�}�ӊ������Ă邩�`�F�b�N
	if( num <= 14 ){	return msg_hyouka_s00; }
	if( num <= 24 ){	return msg_hyouka_s01; }
	if( num <= 39 ){	return msg_hyouka_s02; }
	if( num <= 59 ){	return msg_hyouka_s03; }
	if( num <= 89 ){	return msg_hyouka_s04; }
	if( num <= 114 ){	return msg_hyouka_s05; }
	if( num <= 134 ){	return msg_hyouka_s06; }
	if( num <= 144 ){	return msg_hyouka_s07; }
	if( num <= 149 ){	return msg_hyouka_s08; }

	//�����Ŋ���
	if(c04_arrive){
		//�n�N�^�C�ɓ������Ă�����A�������ւ����Ń��b�Z�[�W
		return msg_hyouka_doctor_07;
	}else{
		//�������Ă��Ȃ���΁A�S�������˃��b�Z�[�W
		return msg_hyouka_doctor_08;
	}
}

//--------------------------------------------------------------
/**
 * �]�����b�Z�[�WID�擾
 *
 * @param   num		�B�����������߂܂�����
 * @param	sex		��l���̐���
 *
 * @retval  "���b�Z�[�WID"
 */
//--------------------------------------------------------------
u16 GetZenkokuZukanHyoukaMsgID( u16 num ,u16 sex)
{
	if( num <= 39 ){	return msg_hyouka_z00; }
	if( num <= 59 ){	return msg_hyouka_z01; }
	if( num <= 89 ){	return msg_hyouka_z02; }
	if( num <= 119 ){	return msg_hyouka_z03; }
	if( num <= 149 ){	return msg_hyouka_z04; }
	if( num <= 189 ){	return msg_hyouka_z05; }
	if( num <= 229 ){	return msg_hyouka_z06; }
	if( num <= 269 ){	return msg_hyouka_z07; }
	if( num <= 309 ){	return msg_hyouka_z08; }
	if( num <= 349 ){	return msg_hyouka_z09; }
	if( num <= 379 ){	return msg_hyouka_z10; }
	if( num <= 409 ){	return msg_hyouka_z11; }
	if( num <= 429 ){
		if(sex){	//���̎qver
			return msg_hyouka_z19;
		}else{
			return msg_hyouka_z12; 
		}
	}
	if( num <= 449 ){	return msg_hyouka_z13; }
	if( num <= 459 ){	return msg_hyouka_z14; }
	if( num <= 469 ){	return msg_hyouka_z15; }
	if( num <= 475 ){	return msg_hyouka_z16; }
	if( num <= 481 ){	return msg_hyouka_z17; }

	//����
	if(sex){
		return msg_hyouka_z20;
	}else{
		return msg_hyouka_z18;
	}
}

//--------------------------------------------------------------
/**
 * �擪�|�P�����Z�o
 *
 * @param   sv		�|�P�����Z�[�u���\����
 *
 * @retval  �ԍ�
 */
//--------------------------------------------------------------
u16 GetFrontPokemon(SAVEDATA * sv)
{
	POKEMON_PARAM * poke;
	u16 i,max;

	max = PokeParty_GetPokeCount(SaveData_GetTemotiPokemon(sv));

	for(i=0;i<max;i++){
		poke = PokeParty_GetMemberPointer( SaveData_GetTemotiPokemon(sv), i);

		//�����X�^�[�ԍ��擾(0�ȊO�Ȃ�^�}�S����Ȃ��j
		if( PokeParaGet( poke, ID_PARA_tamago_flag, NULL ) == 0 ){
			return i;
		}
	}

	return 0;	//���s���ȃ|�P�������΍�i�ʏ�͂����͒ʂ�܂���j
}

//--------------------------------------------------------------
/**
 *	@brief	���W�L���O�C�x���g�@�莝���ɃA�C�X�E���b�N�E�X�`�������邩�ǂ����H
 */
//--------------------------------------------------------------
BOOL EventCheck_IsReziUnseal(SAVEDATA* sv)
{
	int i,j,num,ct = 0;
	POKEPARTY *party;
	static const u16 rezino[] = {MONSNO_REZIROKKU,MONSNO_REZIAISU,MONSNO_REZISUTIRU};
	u16	monsno[6];
	
	party = SaveData_GetTemotiPokemon(sv);
	num = PokeParty_GetPokeCount(party);
	for(i = 0;i < num;i++){
		monsno[i] = PokeParaGet(PokeParty_GetMemberPointer(party,i),
						ID_PARA_monsno,NULL);	
	}
					
	for(i = 0;i < 3;i++){
		for(j = 0;j < num;j++){
			if(monsno[j] == rezino[i]){
				++ct;
				break;
			}
		}
	}
	if(ct == 3){
		return TRUE;
	}
	return FALSE;
}

//--------------------------------------------------------------
///�t�B�[���hOBJ��h�炸�A�j��
//--------------------------------------------------------------
typedef struct _OBJ_SHAKE_ANM{
	FIELD_OBJ_PTR	obj;
	fx32	ofsx,ofsz;
	u16	time;
	u16	r,spd;
}OBJ_SHAKE_ANM;

//--------------------------------------------------------------
/**
 * @brief	�t�B�[���h�I�u�W�F��h�炷�C�x���g 
 * @param	ev	GMEVENT_CONTROL *
 * @param	obj		FIELD_OBJ_PTR	�t�B�[���h�I�u�W�F�ւ̃|�C���^
 * @param	time	�h�炷��
 * @param	spd		�h�炷�X�s�[�h(360������؂�鐔�����悢)
 * @param	ofsx	�h�炷��X	
 * @param	ofsz	�h�炷��Z	
 * @retval	BOOL	TRUE=�C�x���g�I��
 */
//--------------------------------------------------------------
static BOOL FieldobjAnmEvent_ObjShake( GMEVENT_CONTROL *ev )
{
	VecFx32	vp;
	FIELDSYS_WORK *fsys = FieldEvent_GetFieldSysWork( ev );
	OBJ_SHAKE_ANM *wk = FieldEvent_GetSpecialWork( ev );


	vp.x = FX32_CONST(8);//FX_Mul(Sin360(wk->r),wk->ofsx);
	vp.z = FX32_CONST(8);//FX_Mul(Sin360(wk->r),wk->ofsz);
	vp.x = FX_Mul(Sin360(wk->r),wk->ofsx);
	vp.z = FX_Mul(Sin360(wk->r),wk->ofsz);
	vp.y = 0;
	FieldOBJ_VecDrawOffsOutSideSet(wk->obj,&vp);

	wk->r += wk->spd;
	if(wk->r >= 360){
		wk->r = 0;
		wk->time--;
	}
	if(wk->time == 0){
		vp.x = vp.y = vp.z = 0;//FX32_CONST(16);
		FieldOBJ_VecDrawOffsOutSideSet(wk->obj,&vp);
		sys_FreeMemoryEz(wk);
		return TRUE;
	}
	return FALSE;
}

void EventCmd_ObjShakeAnm( GMEVENT_CONTROL *event,FIELD_OBJ_PTR obj,
		u16 time,u16 spd,u16 ofsx,u16 ofsz)
{
	FIELDSYS_WORK *fsys = FieldEvent_GetFieldSysWork( event );
	
	OBJ_SHAKE_ANM *wk = sys_AllocMemoryLo( HEAPID_WORLD,sizeof(OBJ_SHAKE_ANM));
	MI_CpuClear8(wk,sizeof(OBJ_SHAKE_ANM));	
	
	wk->ofsx = FX32_CONST(ofsx);
	wk->ofsz = FX32_CONST(ofsz);
	wk->time = time;
	wk->spd = spd;
	wk->obj = obj;
	FieldEvent_Call( fsys->event, FieldobjAnmEvent_ObjShake, wk);
}

//--------------------------------------------------------------
///�t�B�[���hOBJ��Blink������A�j��
//--------------------------------------------------------------
typedef struct _OBJ_BLINK_ANM{
	FIELD_OBJ_PTR	obj;
	u16	count;
	u16	time;
	u8	ct;
	u8	flag;
}OBJ_BLINK_ANM;

//--------------------------------------------------------------
/**
 * @brief	�t�B�[���h�I�u�W�F��Blink������A�j���C�x���g 
 * @param	ev		GMEVENT_CONTROL *
 * @param	obj		FIELD_OBJ_PTR	�t�B�[���h�I�u�W�F�ւ̃|�C���^
 * @param	count	Blink�������
 * @param	time	onoff��؂�ւ���C���^�[�o��
 */
//--------------------------------------------------------------
static BOOL FieldobjAnmEvent_ObjBlink( GMEVENT_CONTROL *ev )
{
	FIELDSYS_WORK *fsys = FieldEvent_GetFieldSysWork( ev );
	OBJ_BLINK_ANM *wk = FieldEvent_GetSpecialWork( ev );

	FieldOBJ_StatusBitSet_Vanish(wk->obj, wk->flag);

	if(wk->ct++ >= wk->time){
		wk->flag ^= 1;
		wk->ct = 0;
		if(wk->count-- == 0){
			sys_FreeMemoryEz(wk);
			return TRUE;
		}
	}
	return FALSE;
}

void EventCmd_ObjBlinkAnm(GMEVENT_CONTROL *event,FIELD_OBJ_PTR obj,u16 count,u16 time)
{
	FIELDSYS_WORK *fsys = FieldEvent_GetFieldSysWork( event );
	
	OBJ_BLINK_ANM *wk = sys_AllocMemoryLo( HEAPID_WORLD,sizeof(OBJ_BLINK_ANM));
	MI_CpuClear8(wk,sizeof(OBJ_BLINK_ANM));	
	
	wk->count = count;
	wk->time = time;
	wk->obj = obj;
	wk->flag = 0;
	FieldEvent_Call( fsys->event, FieldobjAnmEvent_ObjBlink, wk);
}

//--------------------------------------------------------------
//--------------------------------------------------------------
