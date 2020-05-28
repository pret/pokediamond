
//============================================================================================
/**
 * @file	waza_tool.c
 * @bfief	�Z�p�����[�^�c�[���S
 * @author	HisashiSogabe
 * @date	05.07.28
 */
//============================================================================================

#include	"common.h"

#include	"battle/battle_common.h"
#include	"battle/battle_server.h"
#include	"battle/fight_tool.h"
#include	"battle/server.h"
#include	"battle/server_tool.h"
#include	"battle/tokusyu_def.h"
#include	"battle/wazano_def.h"
#include	"poketool/monsno.h"
#include	"poketool/poke_tool.h"
#include	"poketool/waza_tool.h"
#include	"system/arc_tool.h"

#include	"itemtool/item.h"
#include	"itemtool/itemequip.h"
#include	"itemtool/itemsym.h"

#include	"waza_tool_def.h"

//============================================================================================
/**
 * �萔�錾
 */
//============================================================================================

typedef struct{
	u16	monsno;
	s16 hp;

	u16	hpmax;
	u8	eqp;
	u8	atc;

	u32 condition;

	u8	speabino;
	u8	sex;
	u8	type1;
	u8	type2;
}WAZA_DAMAGE_CALC_PARAM;

//============================================================================================
/**
 * �v���g�^�C�v�錾
 */
//============================================================================================
void		WT_WazaTableDataGet(void *buffer);
ARCHANDLE	*WT_WazaDataParaHandleOpen(u32 heapID);
void		WT_WazaDataParaHandleClose(ARCHANDLE *handle);
u32			WT_WazaDataParaGet(int waza_no,int id);
u32			WT_WazaDataParaGetHandle(ARCHANDLE *handle,int waza_no,int id);
u8			WT_PPMaxGet(u16 wazano,u8 maxupcnt);
u32			WT_WazaDataParaGetAct(WAZA_TABLE_DATA *wtd,int id);

static	void	WT_WazaDataGet(int waza_no,WAZA_TABLE_DATA *wtd);

//============================================================================================
/**
 *	�Z�f�[�^�e�[�u���f�[�^��Alloc�����������ɓW�J
 *
 * @param[in]	heapID	�f�[�^��W�J���郁�����q�[�vID
 */
//============================================================================================
void	WT_WazaTableDataGet(void *buffer)
{
	ArchiveDataLoadOfs(buffer,ARC_WAZA_TBL,0,0,sizeof(WAZA_TABLE_DATA)*(WAZANO_MAX+1));
}

//============================================================================================
/**
 *	�Z�f�[�^�e�[�u���t�@�C���n���h���I�[�v��
 *
 * @param[in]	heapID	�n���h����Alloc����q�[�vID
 */
//============================================================================================
ARCHANDLE	*WT_WazaDataParaHandleOpen(u32 heapID)
{
	return	ArchiveDataHandleOpen(ARC_WAZA_TBL,heapID);
}

//============================================================================================
/**
 *	�Z�f�[�^�e�[�u���t�@�C���n���h���N���[�Y
 *
 * @param[in]	handle	�N���[�Y����Handle
 */
//============================================================================================
void	WT_WazaDataParaHandleClose(ARCHANDLE *handle)
{
	ArchiveDataHandleClose(handle);
}

//============================================================================================
/**
 *	�Z�f�[�^�e�[�u������l���擾
 *
 * @param[in]	waza_no		�擾�������Z�i���o�[
 * @param[in]	id			�擾�������l�̎��
 */
//============================================================================================
u32	WT_WazaDataParaGet(int waza_no,int id)
{
	WAZA_TABLE_DATA wtd;

	WT_WazaDataGet(waza_no,&wtd);

	return	WT_WazaDataParaGetAct(&wtd,id);
}

//============================================================================================
/**
 *	�Z�f�[�^�e�[�u������l���擾�i�t�@�C���n���h�����g�p����j
 *
 * @param[in]	waza_no		�擾�������Z�i���o�[
 * @param[in]	id			�擾�������l�̎��
 */
//============================================================================================
u32	WT_WazaDataParaGetHandle(ARCHANDLE *handle,int waza_no,int id)
{
	WAZA_TABLE_DATA wtd;

	ArchiveDataLoadByHandle(handle,waza_no,&wtd);

	return	WT_WazaDataParaGetAct(&wtd,id);
}

//============================================================================================
/**
 *	PPMax���擾
 *
 * @param[in]	wazano		�擾����Z�i���o�[
 * @param[in]	maxupcnt	�}�b�N�X�A�b�v���g�p������
 *
 * @retval	PPMAX
 */
//============================================================================================
u8	WT_PPMaxGet(u16 wazano,u8 maxupcnt)
{
	u8	ppmax;

	if(maxupcnt>3){
		maxupcnt=3;
	}

	ppmax=WT_WazaDataParaGet(wazano,ID_WTD_pp);
	ppmax+=(ppmax*20*maxupcnt)/100;

	return	ppmax;
}

//============================================================================================
/**
 *	�Z�e�[�u���\���̃f�[�^����l���擾
 *
 * @param[in]	wtd		�Z�e�[�u���\���̃f�[�^�ւ̃|�C���^
 * @param[in]	id		�擾�������Z�f�[�^��Index
 */
//============================================================================================
u32	WT_WazaDataParaGetAct(WAZA_TABLE_DATA *wtd,int id)
{
	u32	ret;

	switch(id){
	case ID_WTD_battleeffect:
		ret=wtd->battleeffect;
		break;
	case ID_WTD_kind:
		ret=wtd->kind;
		break;
	case ID_WTD_damage:
		ret=wtd->damage;
		break;
	case ID_WTD_wazatype:
		ret=wtd->wazatype;
		break;
	case ID_WTD_hitprobability:
		ret=wtd->hitprobability;
		break;
	case ID_WTD_pp:
		ret=wtd->pp;
		break;
	case ID_WTD_addeffect:
		ret=wtd->addeffect;
		break;
	case ID_WTD_attackrange:
		ret=wtd->attackrange;
		break;
	case ID_WTD_attackpri:
		ret=wtd->attackpri;
		break;
	case ID_WTD_flag:
		ret=wtd->flag;
		break;
	case ID_WTD_ap_no:				//�R���e�X�g�p�p�����[�^�@�A�s�[��No
		ret=wtd->condata.ap_no;
		break;
	case ID_WTD_contype:			//�R���e�X�g�p�p�����[�^�@�R���e�X�g�Z�^�C�v
		ret=wtd->condata.contype;
		break;
	}
	return ret;
}

//============================================================================================
/**
 *							�O�����J���Ȃ��֐��S
 */
//============================================================================================
//============================================================================================
/**
 *	�Z�e�[�u���\���̃f�[�^���擾
 *
 * @param[in]	waza_no		�擾�������Z�i���o�[
 * @param[out]	wtd			�擾�����Z�f�[�^�̊i�[����w��
 */
//============================================================================================
static	void	WT_WazaDataGet(int waza_no,WAZA_TABLE_DATA *wtd)
{
	ArchiveDataLoad(wtd,ARC_WAZA_TBL,waza_no);
}

