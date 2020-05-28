/**
 *	@file	tmap_sub.h
 *	@brief	�^�E���}�b�v�@�T�u�c�[���Q
 *	@author	Miyuki Iwasawa
 *	@date	06.04.01
 */

#ifndef __H_TMAP_SUB_H__
#define __H_TMAP_SUB_H__

////////////////////////////////////////////////////////////////
///�^�E��View�p�f�[�^�\����
typedef struct _TOWN_VIEW{
	int		zoneID;	//<�]�[��ID
	int		sysflag;	//<�V�X�e���t���O�Q��ID
	u8		ptn;	//<�摜�p�^�[��	
	u8		typ;	//<�摜�p�^�[��	
	u16		r;	//<��]�p
	fx32	x;	//<x���W
	fx32	z;	//<y���W
}TOWN_VIEW;

typedef struct _TMAP_VIEW_OBJ{
	TOWN_VIEW	prm;
	int		flag;
	CLACT_WORK_PTR	pAct;
}TMAP_VIEW_OBJ;

typedef struct _TMAP_VIEW_DAT{
	u16	dat_num;
	u8	selCount;
	u8	selFrame;

	TMAP_VIEW_OBJ *selPos;
	TMAP_VIEW_OBJ *pDat;
}TMAP_VIEW_DAT;

//////////////////////////////////////////////////////////////
///�^�E���}�b�v�p�f�[�^�^
typedef struct _TMAP_GDAT{
	u16	x;			//<�O���b�h���WX
	u16	z;			//<�O���b�h���WZ
	u16	kType;		//<�Ŕ^�C�v��`
	u16 kIdx;		//<�Ŕ�IndexNo
	u16	gmes01;		//<�K�C�h���b�Z�[�W01�C���f�b�N�X
	u16	gmes02;		//<�K�C�h���b�Z�[�W02�C���f�b�N�X
	u16	gmes01_ox;	//<�K�C�h���b�Z�[�W01�\���I�t�Z�b�gX
	u16	gmes01_oy;	//<�K�C�h���b�Z�[�W01�\���I�t�Z�b�gY
	u16	gmes02_ox;	//<�K�C�h���b�Z�[�W02�\���I�t�Z�b�gX
	u16	gmes02_oy;	//<�K�C�h���b�Z�[�W02�\���I�t�Z�b�gY
	u16	view;		//<View�t���O
	u16	id;			//<ID
}TMAP_GDAT;

typedef struct _TMAP_GDAT_LIST{
	int	num;	///<�f�[�^��
	TMAP_GDAT *pDat;	//�f�[�^�z��
}TMAP_GDAT_LIST;


//========================================================================
//�T�u�c�[���Q�O���Q�ƒ�`�G���A
//

/**
 *	@brief	�^�E��View���\�[�X�쐬
 *
 *	@param	actSys	�������ς݃Z���A�N�^�[�V�X�e��
 *	@param	actRes	�������ς݃Z���A�N�^�[���\�[�X
 *
 *	@param	dat_num	�f�[�^��
 *	@param	heapID	�q�[�vID
 */
extern TMAP_VIEW_DAT* TownViewDataCreate(CATS_SYS_PTR actSys,CATS_RES_PTR actRes,
		u8 *arrive,short dat_num,int heapID);

/**
 *	@brief	�^�E��View���\�[�X���
 */
extern void TownViewDataRelease(TMAP_VIEW_DAT* wp);

/**
 *	@brief	�^�E��View ��{�`��
 */
extern void TownViewDataDraw(TMAP_VIEW_DAT* wp,int mode);

/**
 *	�^�E��View �f�[�^����������ZoneID�������̂�T��
 */
extern TMAP_VIEW_OBJ* TownViewDataSearchPos(TMAP_VIEW_DAT* wp,int zoneID,int x,int z);

/**
 *	@brief	�^�E��View
 */
extern int TownViewDataSelectPos(TMAP_VIEW_DAT* wp,int zoneID,int x,int z);

//============================================================
//�}�b�v�u���b�N�f�[�^�Q�Ɗ֘A
//============================================================
/**
 *	@brief	�}�b�v�u���b�N�f�[�^���[�h
 */
extern TMAP_GDAT_LIST* TMapBlockDataLoad(const char* path,int heapID);

/**
 *	@brief	�}�b�v�u���b�N�f�[�^���
 */
extern void TMapBlockDataRelease(TMAP_GDAT_LIST* pWork);

/**
 *	@brief	�}�b�v�u���b�N�f�[�^�@�u���b�N�f�[�^�擾
 *
 *	@param	pWork	�f�[�^���X�g�z��̐擪�|�C���^
 *	@param	x		��������u���b�N��X���W
 *	@param	z		��������u���b�N��Z���W
 *	@param	mapView	�z�z�}�b�v�`��t���O
 *	�u���b�N��x,z���W����u���b�N�f�[�^�ւ̃|�C���^���擾����
 *	������Ȃ������ꍇNULL��Ԃ�
 */
extern TMAP_GDAT* TMapBlockDataGet(TMAP_GDAT_LIST* pWork,int x,int z,u16 mapView);


#endif	//__H_TMAP_SUB_H__

