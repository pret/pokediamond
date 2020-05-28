/**
 *  @file	fld_comact.c
 *	@brief	�t�B�[���h��ɋ��L�`�悳���J�[�\���A�N�^�[�̃R���g���[��
 *	@author	Miyuki iwasawa
 *	@date	06.03.23
 */

#include "common.h"
#include "field/fld_comact.h"
#include "field/fld_comact.naix"

#define FCOMACT_CHR_RES_MAX	(1)
#define FCOMACT_PAL_RES_MAX	(1)
#define FCOMACT_CEL_RES_MAX	(1)
#define FCOMACT_ANM_RES_MAX	(1)

enum {
	FCOMACT_CHR_H_ID_CURSOR	= 13528,
};
enum {
	FCOMACT_PAL_H_ID = 13528,
};
enum {
	FCOMACT_CEL_H_ID_CURSOR	= 13528,
};
enum {
	FCOMACT_ANM_H_ID_CURSOR	= 13528,
};

#define CURSOR_PX	(80)
#define CURSOR_PRI	(0)
#define CURSOR_SPRI	(0)
#define CURSOR_PAL	(0)

#define UPCUR_PY	(16)
#define UPCUR_ANMNO	(0)
#define DOWNCUR_PY	(224)
#define DOWNCUR_ANMNO	(1)

static const TCATS_RESOURCE_FILE_LIST FCA_ResFileList = {
	"data/fcomact_chr.resdat",	// �L�����N�^
	"data/fcomact_pal.resdat",	// �p���b�g
	"data/fcomact_cell.resdat",	// �Z��
	"data/fcomact_canm.resdat",	// �Z���A�j��
	NULL,						// �}���`�Z��
	NULL,						// �}���`�Z���A�j��
	"data/fcomact_h.cldat"		// �w�b�_�[
};

static const TCATS_OBJECT_ADD_PARAM_S ActAddParam_S[] =
{
	{	// �A�b�v�J�[�\��
		CURSOR_PX, UPCUR_PY, 0,
		UPCUR_ANMNO, CURSOR_SPRI, CURSOR_PAL, NNS_G2D_VRAM_TYPE_2DMAIN,
		{
			FCOMACT_CHR_H_ID_CURSOR, FCOMACT_PAL_H_ID,
			FCOMACT_CEL_H_ID_CURSOR, FCOMACT_ANM_H_ID_CURSOR, 0, 0,
		},
		CURSOR_PRI, 0
	},
	{	//�_�E���J�[�\�� 
		CURSOR_PX, DOWNCUR_PY, 0,
		DOWNCUR_ANMNO, CURSOR_SPRI, CURSOR_PAL, NNS_G2D_VRAM_TYPE_2DMAIN,
		{
			FCOMACT_CHR_H_ID_CURSOR, FCOMACT_PAL_H_ID,
			FCOMACT_CEL_H_ID_CURSOR, FCOMACT_ANM_H_ID_CURSOR, 0, 0,
		},
		CURSOR_PRI, 0
	},
};

/**
 *	@brief	�t�B�[���h�C�x���g�@���ʃZ���A�N�^�[������
 */
FLD_COMACT_WORK* FComAct_Init(int heapID)
{
	TCATS_RESOURCE_NUM_LIST	crnl = {
		FCOMACT_CHR_RES_MAX, FCOMACT_PAL_RES_MAX,
		FCOMACT_CEL_RES_MAX, FCOMACT_ANM_RES_MAX, 0, 0
	};
	
	u32	i;
	FLD_COMACT_WORK* wk;
	
	wk = sys_AllocMemory(heapID,sizeof(FLD_COMACT_WORK));
	MI_CpuClear8(wk,sizeof(FLD_COMACT_WORK));

	//�t�B�[���h�Z���A�N�^�[������
	FieldCellActSet_S( &wk->fcat, &crnl, FCA_ACTMAX, HEAPID_WORLD );

	FldClact_LoadResPlttArc(
		&wk->fcat, ARC_FLDCOMACT_GRA,NARC_fld_comact_fld_comact_nclr,
		0, 2, NNS_G2D_VRAM_TYPE_2DMAIN, FCOMACT_PAL_H_ID );

	FldClact_LoadResCellArc(
		&wk->fcat, ARC_FLDCOMACT_GRA, NARC_fld_comact_fld_comact_ncer,
		0, FCOMACT_CEL_H_ID_CURSOR );

	FldClact_LoadResCellAnmArc(
		&wk->fcat, ARC_FLDCOMACT_GRA, NARC_fld_comact_fld_comact_nanr,
		0, FCOMACT_ANM_H_ID_CURSOR );

	FldClact_LoadResourceCharArc(
		&wk->fcat, ARC_FLDCOMACT_GRA, NARC_fld_comact_fld_comact_ncgr,
		0, NNS_G2D_VRAM_TYPE_2DMAIN, FCOMACT_CHR_H_ID_CURSOR );

	for(i = 0;i < FCA_ACTMAX;i++){
		wk->act[i] = FieldCellActAdd_S( &wk->fcat, &ActAddParam_S[i] );
	}
	return wk;
}

/**
 *	@brief	�R���g���[���[�j��
 */
void FComAct_Delete(FLD_COMACT_WORK* wk)
{
	int i;

	for(i = 0;i < FCA_ACTMAX;i++){
		if(wk->act[i] != NULL){
			CATS_ActorPointerDelete_S(wk->act[i]);
		}
	}
	FieldCellActDelete_S(&wk->fcat);

	sys_FreeMemoryEz(wk);
}

/**
 *	@brief	�Z���A�N�^�[�R���g���[��
 */
void FActCom_Main(FLD_COMACT_WORK* wk)
{
	int i = 0;

	for(i = 0;i < FCA_ACTMAX;i++){
		if(wk->act[i] != NULL){
			CLACT_AnmFrameChg(wk->act[i]->act,FX32_ONE);
		}
	}
	CLACT_Draw(wk->fcat.cas);
}

/**
 *	@brief	�J�[�\���|�W�V�����Z�b�g
 *
 *	@param	px	�J�[�\��X���W
 *	@param	uy	�A�b�v�J�[�\��Y���W
 *	@param	dy	�_�E���J�[�\��Y���W
 */
void FComAct_CursorPosSet(FLD_COMACT_WORK* wk,s16 px,s16 uy,s16 dy)
{
	CATS_ObjectPosSetCap(wk->act[FCA_UCURSOR],px,uy);
	CATS_ObjectPosSetCap(wk->act[FCA_DCURSOR],px,dy);
}

/**
 *	@brief	�`���ԃR���g���[��
 *
 *	@param	vanish	TRUE:�`��,FALSE:�o�j�b�V��
 */
void FComAct_SetDrawFlg(FLD_COMACT_WORK* wk,u16 idx,BOOL draw)
{
	if(idx >= FCA_ACTMAX){
		return;
	}
	CATS_ObjectEnableCap(wk->act[idx],draw);
}

/**
 *	@brief	�I�[�g�A�j����ԃR���g���[��
 *
 *	@param	anm	TRUE:�I�[�g�A�j��,FALSE:�I�[�g�A�j��Off
 */
void FComAct_SetAutoAnmFlg(FLD_COMACT_WORK* wk,u16 idx,BOOL anm)
{
	if(idx >= FCA_ACTMAX){
		return;
	}
	CATS_ObjectAutoAnimeSetCap(wk->act[idx],anm);
}
