//============================================================================================
/**
 * @file	field_clact.c
 * @brief	�t�B�[���h�p�Z���A�N�^�[�ݒ菈��
 * @author	Hiroyuki Nakamura
 * @date	2005.01.13
 */
//============================================================================================
#ifndef FIELD_CLACT_H
#define FIELD_CLACT_H
#undef GLOBAL
#ifdef FIELD_CLACT_H_GLOBAL
#define GLOBAL	/*	*/
#else
#define GLOBAL	extern
#endif


//============================================================================================
//	�萔��`
//============================================================================================
typedef struct {
	CLACT_SET_PTR	cas;
	CLACT_U_EASYRENDER_DATA	renddata;	// �ȈՃ����_�[�f�[�^
	CLACT_HEADER_TBL_PTR	clh;		// �w�b�_�[
	CLACT_U_RES_MANAGER_PTR	resMan[6];	// ���\�[�X�}�l�[�W��
	CLACT_U_RES_OBJ_TBL * resObjTbl[6];	// ���\�[�X�I�u�W�F�e�[�u��
	u16	res_max;
	u16	heap;
}FIELD_CLACT;


//============================================================================================
//	�v���g�^�C�v�錾
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * �Z���A�N�^�[�ݒ�
 *
 * @param	fcat	�ݒ�f�[�^�ۑ��ꏊ
 * @param	list	�ǂݍ��݃t�@�C�����X�g
 * @param	max		�Z���A�N�^�[�ő吔
 * @param	heap	�q�[�vID
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
GLOBAL void FieldCellActSet(
				FIELD_CLACT * fcat, const TCATS_RESOURCE_FILE_LIST * list, u32 max, u32 heap );

//--------------------------------------------------------------------------------------------
/**
 * �Z���A�N�^�[�ݒ�j��
 *
 * @param	fcat	�ݒ�f�[�^
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
GLOBAL void FieldCellActDelete( FIELD_CLACT * fcat );

//--------------------------------------------------------------------------------------------
/**
 * �Z���A�N�^�[�o�^
 *
 * @param	fcat	�ݒ�f�[�^
 * @param	prm		�ǉ��f�[�^
 *
 * @return	�o�^�����Z���A�N�^�[�̃|�C���^
 */
//--------------------------------------------------------------------------------------------
GLOBAL CLACT_WORK_PTR FieldCellActAdd(
						FIELD_CLACT * fcat, const TCATS_OBJECT_ADD_PARAM * prm );


//--------------------------------------------------------------------------------------------
/**
 * �Z���A�N�^�[�ݒ�i�P���p�j
 *
 * @param	fcat	�ݒ�f�[�^�ۑ��ꏊ
 * @param	crnl	
 * @param	max		�Z���A�N�^�[�ő吔
 * @param	heap	�q�[�vID
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
GLOBAL void FieldCellActSet_S(
		FIELD_CLACT * fcat, TCATS_RESOURCE_NUM_LIST * crnl, u32 max, u32 heap );

//--------------------------------------------------------------------------------------------
/**
 * �p���b�g���\�[�X�ݒ�
 *
 * @param	fcat		�ݒ�f�[�^
 * @param	arc_id		�A�[�J�C�uID
 * @param	data_id		�f�[�^ID
 * @param	comp		���k�t���O
 * @param	num			�]���T�C�Y
 * @param	trans_mode	�]�����[�h
 * @param	id			���\�[�XID
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
GLOBAL void FldClact_LoadResPlttArc(
		FIELD_CLACT * fcat, int arc_id, int data_id, int comp, int num, int trans_mode, int id );

//--------------------------------------------------------------------------------------------
/**
 * �Z�����\�[�X�ݒ�
 *
 * @param	fcat		�ݒ�f�[�^
 * @param	arc_id		�A�[�J�C�uID
 * @param	data_id		�f�[�^ID
 * @param	comp		���k�t���O
 * @param	id			���\�[�XID
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
GLOBAL void FldClact_LoadResCellArc(
					FIELD_CLACT * fcat, int arc_id, int data_id, int comp, int id );

//--------------------------------------------------------------------------------------------
/**
 * �Z���A�j�����\�[�X�ݒ�
 *
 * @param	fcat		�ݒ�f�[�^
 * @param	arc_id		�A�[�J�C�uID
 * @param	data_id		�f�[�^ID
 * @param	comp		���k�t���O
 * @param	id			���\�[�XID
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
GLOBAL void FldClact_LoadResCellAnmArc(
						FIELD_CLACT * fcat, int arc_id, int data_id, int comp, int id );

//--------------------------------------------------------------------------------------------
/**
 * �L�������\�[�X�ݒ�
 *
 * @param	fcat		�ݒ�f�[�^
 * @param	arc_id		�A�[�J�C�uID
 * @param	data_id		�f�[�^ID
 * @param	comp		���k�t���O
 * @param	trans_mode	�]�����[�h
 * @param	id			���\�[�XID
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
GLOBAL void FldClact_LoadResourceCharArc(
		FIELD_CLACT * fcat, int arc_id, int data_id, BOOL comp, int trans_mode, int id );

//--------------------------------------------------------------------------------------------
/**
 * �L�����̃��[�\�[�X��ύX����
 *
 * @param	fcat		�ݒ�f�[�^
 * @param	arc_id		�A�[�J�C�uID
 * @param	data_id		�f�[�^ID
 * @param	comp		���k�t���O
 * @param	id			���\�[�XID
 *
 * @retval	BOOL	
 */
//--------------------------------------------------------------------------------------------
GLOBAL void FldClact_ChangeResourceCharArc(
					FIELD_CLACT * fcat, int arc_id, int data_id, BOOL comp, int id );

//--------------------------------------------------------------------------------------------
/**
 * �p���b�g�̃��[�\�[�X��ύX����
 *
 * @param	fcat		�ݒ�f�[�^
 * @param	arc_id		�A�[�J�C�uID
 * @param	data_id		�f�[�^ID
 * @param	comp		���k�t���O
 * @param	id			���\�[�XID
 *
 * @retval	BOOL	
 */
//--------------------------------------------------------------------------------------------
GLOBAL void FldClact_ChangeResourcePlttArc(
					FIELD_CLACT * fcat, int arc_id, int data_id, BOOL comp, int id );

//--------------------------------------------------------------------------------------------
/**
 * �Z���A�N�^�[�ǉ��i�P���p�j
 *
 * @param	fcat		�ݒ�f�[�^
 * @param	coap_s		�\���f�[�^
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
GLOBAL CATS_ACT_PTR FieldCellActAdd_S(
				FIELD_CLACT * fcat, const TCATS_OBJECT_ADD_PARAM_S * coap_s );

//--------------------------------------------------------------------------------------------
/**
 * �Z���A�N�^�[�폜�i�P���p�j
 *
 * @param	fcat		�ݒ�f�[�^
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
GLOBAL void FieldCellActDelete_S( FIELD_CLACT * fcat );





#undef GLOBAL
#endif	/* FIELD_CLACT_H */
