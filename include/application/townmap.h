/**
 *	@file	worldmap.h
 *	@brief	���[���h�}�b�v���W���[���@���C���w�b�_
 *	@author	Miyuki Iwasawa
 *	@date	05.09.07
 */

#ifndef _TOWN_MAP_H_
#define _TOWN_MAP_H_


#include "field/field_common.h"
#include "field/sysflag.h"

//��ʃ��W���[���f�[�^IO
typedef struct _TMAP_IO_DAT{
	u8	mode;	///<���샂�[�h�ۑ�	
	int	retval;	///<Return value
}TMAP_IO_DAT;

///�O�����J�\���̌^
///�^�E���}�b�v�Ăяo�����[�hID
typedef enum{
	TMAP_MNORMAL = 0,	///<�^�E���}�b�v���[�h
	TMAP_MJUMP,			///<�����
	TMAP_MBG,			///<BG�b���������[�h
	TMAP_NTENKI,		///<���V�C�j���[�X
	TMAP_MNEWS,			///<��ʔ���
	TMAP_MODE_MAX = 3,		///<���[�h��
}TMAP_MODE;

///���Ճf�[�^�\����
typedef struct _TMAP_FOOT{
	int	x;
	int	z;
	u16	dir;
	u16	valid;
}TMAP_FOOT;
#define TMAP_FVIEW_MAX	(5)

///�Z�[�u�t���O���p���f�[�^�\����
typedef union{
	struct{
		u8	ex01_f:2;
		u8	ex01:2;
		u8	ex02_f:2;
		u8	ex02:2;
	};
	u8	flag;
}TMAP_FLAGS;
#define TMAP_BLOCK_MAX	(200)
/**
 *	@brief	�����t���Oindex�擾
 */
#define TMAP_ARRIVEDATA_MAX	(20)

///�^�E���}�b�v�p�����[�^���p���\����
typedef struct {
	int player_x;	///<�v���C���[���[���h�O���b�h���W
	int player_z;	///<�v���C���[���[���h�O���b�h���W
	int zone_id;	///<���݂̃]�[��ID
	int	player_sex;	///<�v���C���[�̐���
	int	retval;	///<�߂�l
	int	ret_x;
	int ret_z;
	int ret_zone;
	
	TMAP_FOOT	foot[TMAP_FVIEW_MAX];
	TMAP_FLAGS	flags[TMAP_BLOCK_MAX];
	u8			arrive[TMAP_ARRIVEDATA_MAX+1];	///<�����t���O
	
	u8	mode;		///<���샂�[�h�ۑ�	
	u8	flag_num;	///<�t���O��
	u16	view_f;	///<View�t���O

#ifdef PM_DEBUG
	int	debug_f;	///<�f�o�b�Omake���̂ݗL���ȃt���O
#endif	//PM_DEBUG
}TOWNMAP_PARAM;

/**
 *	@brief	�t�B�[���h ���[���h�}�b�v���W���[���Ăяo��
 *
 *	@param	fsys FIELDSYS_WORK *
 *	@param	mode	u8:�Ăяo�����[�h(enum WMAP_MODE)
 *	@param	work	void*:���[�N�̈��p��
 *
 *	@retval	0:����
 *	@retval else	���s
 */
extern void FieldTMap_SetProc(FIELDSYS_WORK *fsys, TOWNMAP_PARAM * tp);

/**
 *	@brief	�^�E���}�b�v���W���[���ֈ����p���p�����[�^���Z�b�g
 *
 *	@param	fsys	FIELDSYS_WORK�^�ւ̃|�C���^
 *	@param	mode	u8:���W���[���̓��샂�[�h(townmap.h�Œ�`)
 *
 *	@return	�m�ۂ���TOWNMAP_PARAM�^�ւ̃|�C���^
 *
 *	@li	���̊֐����Ŋm�ۂ��ꂽ�������̈�́A�Ăяo�������W���[����
 *		������邱�ƁI
 */
extern TOWNMAP_PARAM* FieldTMap_SetParam(FIELDSYS_WORK *fsys,u8 mode);

/**
 *	@brief	�t�B�[���h �^�E���}�b�v���W���[���f�[�^�Z�b�g
 *
 *	@param	fsys FIELDSYS_WORK *
 *	@param	tp	TOWNMAP_PARAM*:�f�[�^���i�[����\���̌^�ւ̃|�C���^
 *	@param	mode	u8:�Ăяo�����[�h(enum TMAP_MODE)
 */
extern void FieldTMap_CallDataSet(FIELDSYS_WORK* fsys,TOWNMAP_PARAM *tp,int mode);

///�I�[�o�[���C�v���Z�X
extern PROC_RESULT TMapProc_Init( PROC *proc,int *seq);
extern PROC_RESULT TMapProc_Main( PROC *proc,int *seq);
extern PROC_RESULT TMapProc_End( PROC *proc,int *seq);


/**
	1,���C�����W���[���̏�����
	2,�T�u���W���[���̏�����

	,���C�����W���[������
	,�T�u���W���[������
	,���C���摜�`��
	,�T�u�摜�`��
	
	2,�T�u���W���[���I��
	,���C�����W���[���I��
	
*/
#endif	//_TOWN_MAP_H_

