#ifndef _TRAINER_CARD_OBJ_H_
#define _TRAINER_CARD_OBJ_H_

#include "system/clact_tool.h"

// CellActor�ɏ��������郊�\�[�X�}�l�[�W���̎�ނ̐��i���}���`�Z���E�}���`�Z���A�j���͎g�p���Ȃ��j
#define RESOURCE_NUM		(4)
#define TR_CARD_BADGE_ACT_MAX	(8)
#define TR_CARD_STAR_ACT_MAX	(8)
#define TR_CARD_GRATE_STAR_ACT_MAX	(8)
#define TR_CARD_BTNEFF_ACT_MAX	(1)

#define TR_CARD_BADGE_ACT_START	(0)
#define TR_CARD_STAR_ACT_START	( TR_CARD_BADGE_ACT_MAX )
#define TR_CARD_GRATE_STAR_ACT_START	(TR_CARD_STAR_ACT_START+TR_CARD_STAR_ACT_MAX)
#define TR_CARD_BTNEFF_ACT_START	(TR_CARD_GRATE_STAR_ACT_START+TR_CARD_GRATE_STAR_ACT_MAX)

#define TR_CARD_ACT_MAX	(TR_CARD_BADGE_ACT_MAX+TR_CARD_STAR_ACT_MAX+\
		TR_CARD_GRATE_STAR_ACT_MAX+TR_CARD_BTNEFF_ACT_MAX)

///typedef struct TR_CARD_OBJ_WORK_tag *TR_CARD_OBJ_PTR;

typedef struct TR_CARD_OBJ_WORK_tag
{
	CLACT_SET_PTR 			ClactSet;								// �Z���A�N�^�[�Z�b�g
	CLACT_U_EASYRENDER_DATA	RendData;								// �ȈՃ����_�[�f�[�^
	CLACT_U_RES_MANAGER_PTR	ResMan[RESOURCE_NUM];				// ���\�[�X�}�l�[�W��
	CLACT_U_RES_OBJ_PTR 	ResObjTbl[2][RESOURCE_NUM];		// ���\�[�X�I�u�W�F�e�[�u��(�㉺���)
	///CLACT_HEADER			ClActHeader_m;							// �Z���A�N�^�[�w�b�_�[(���C��)
	///CLACT_HEADER			ClActHeader_s;							// �Z���A�N�^�[�w�b�_�[(�T�u)
	CLACT_WORK_PTR			ClActWork[TR_CARD_ACT_MAX];				// �Z���A�N�^�[���[�N�|�C���^�z��

	void *PalDataBuf[TR_CARD_BADGE_ACT_MAX];		//�p���b�g�f�[�^TR_CARD_BADGE_ACT_MAX��
	NNSG2dPaletteData *PalData[TR_CARD_BADGE_ACT_MAX];	//�p���b�g�f�[�^TR_CARD_BADGE_ACT_MAX��
}TR_CARD_OBJ_WORK;


extern void InitTRCardCellActor( TR_CARD_OBJ_WORK *wk );
extern void SetTrCardActor( TR_CARD_OBJ_WORK *wk, const u8 *inBadgeDisp );
extern void RereaseCellObject(TR_CARD_OBJ_WORK *wk);

extern void SetBadgePalette(TR_CARD_OBJ_WORK *wk,
							const u8 inBadgeNo,
							const u8 inPalNo );

#endif //_TRAINER_CARD_OBJ_H_

