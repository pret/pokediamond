/**
 *	@file	fld_nmixer.c
 *	@brief	�t�B�[���h�p�@�i�b�c�~�L�T�[�\�[�X
 *	@author	Miyuki Iwasawa
 *	@date	06.04.06
 */

#include "common.h"
#include "system/procsys.h"
#include "system/snd_tool.h"
#include "system/fontproc.h"
#include "system/pm_str.h"
#include "system/buflen.h"
#include "system/palanm.h"
#include "system/savedata.h"
#include "itemtool/itemsym.h"
#include "itemtool/item.h"
#include "gflib/strbuf_family.h"

#define __FIELDSYS_H_GLOBAL__
#include "fieldsys.h"

#include "application/nutmixer.h"

///�v���g�^�C�v
NUTMIXER_PARAM* NutMixer_CreateCallWork(int mode,SAVEDATA* savedata,int heapID, FNOTE_DATA * fnote);
NUTMIXER_PARAM* FieldNutMixer_InitCall(FIELDSYS_WORK* fsys,int mode,int heapID);

/**
 *	@brief	�i�b�c�~�L�T�[�Ăяo�����[�N�f�[�^�쐬
 *
 *	@param	mode	NUTMIXER_CALL_LOCAL:0	��l�v���C���[�h
 *					NUTMIXER_CALL_COMM:1	�ʐM���[�h
 */
NUTMIXER_PARAM* NutMixer_CreateCallWork(int mode,SAVEDATA* savedata,int heapID, FNOTE_DATA * fnote)
{
	NUTMIXER_PARAM* wk;
	
	wk = sys_AllocMemory(heapID,sizeof(NUTMIXER_PARAM));
	MI_CpuClear8(wk,sizeof(NUTMIXER_PARAM));

	//�Z�[�u�f�[�^�u���b�N�擾
	wk->SaveData = savedata;
	wk->poruSave = SaveData_GetPorutoBlock(savedata);
	wk->mySave = SaveData_GetMyStatus(savedata);
	wk->itemSave = SaveData_GetMyItem(savedata);
	wk->configSave = SaveData_GetConfig(savedata);
	wk->fnote = fnote;

	//���샂�[�h�擾
	wk->sys_mode = mode;

	return wk;
}

//-----------------------------------------------------------------------------
/**
*	�i�b�c�~�L�T�[�֘A
*/
//-----------------------------------------------------------------------------
/**
 *	@brief	�i�b�c�~�L�T�[�T�u�v���Z�X�o�^
 */
static void NutMixer_SetProc(FIELDSYS_WORK* fsys,NUTMIXER_PARAM* np)
{
	GameSystem_StartSubProc(fsys, &NutMixerProcData,np);
}

/**
 *	@brief	�i�b�c�~�L�T�[�Ăяo��
 *
 *	@param	mode	NUTMIXER_CALL_LOCAL:0	��l�v���C���[�h
 *					NUTMIXER_CALL_COMM:1	�ʐM���[�h
 */
NUTMIXER_PARAM* FieldNutMixer_InitCall(FIELDSYS_WORK* fsys,int mode,int heapID)
{
	NUTMIXER_PARAM* np;
	
	np = NutMixer_CreateCallWork(mode,GameSystem_GetSaveData(fsys),heapID,fsys->fnote);	
	NutMixer_SetProc(fsys,np);
	
	return np;
}

