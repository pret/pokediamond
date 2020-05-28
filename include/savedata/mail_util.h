/**
 *	@file	mail_util.h
 *	@brief	���[���f�[�^�Q�Ɨp�s���S�^��`�����[�e�B���e�B�֐���`
 *	@author	MiyukiIwasawa
 *	@date	06.02.09
 */

#ifndef __H_MAIL_UTIL_H__
#define __H_MAIL_UTIL_H__

///�萔��`
#include "savedata/mail_def.h"

#include "savedata/savedata_def.h"
#include "system/pm_str.h"
#include "system/pms_data.h"

//------------------------------------------------------------
/**
 * @brief	���[���Z�[�u�f�[�^�u���b�N�Ǘ��\���ւ̕s���S�^�|�C���^
 *
 * ���g�͌����Ȃ����ǃ|�C���^�o�R�ŎQ�Ƃ͂ł���
 */
//------------------------------------------------------------
typedef struct _MAIL_BLOCK MAIL_BLOCK;

//------------------------------------------------------------
/**
 * @brief	���[���f�[�^�Ǘ��\���ւ̕s���S�^�|�C���^
 *
 * ���g�͌����Ȃ����ǃ|�C���^�o�R�ŎQ�Ƃ͂ł���
 */
//------------------------------------------------------------
typedef struct _MAIL_DATA MAIL_DATA;

/**
 *	@brief	�󂢂Ă��郁�[���f�[�^ID���擾
 *
 *	@param	id �ǉ����������[���u���b�NID
 *
 *	@return	int	�f�[�^��ǉ��ł���ꍇ�͎Q��ID
 *				�ǉ��ł��Ȃ��ꍇ�̓}�C�i�X�l���Ԃ�
 */
extern int MAIL_SearchNullID(MAIL_BLOCK* block,MAILBLOCK_ID id);

/**
 *	@brief	���[���f�[�^���폜
 *
 *	@param	blockID	�u���b�N��ID
 *	@param	dataID	�f�[�^ID
 */
extern void MAIL_DelMailData(MAIL_BLOCK* block,MAILBLOCK_ID blockID,int dataID);

/**
 *	@brief	���[���f�[�^���Z�[�u�u���b�N�ɒǉ�
 *
 *	�������n����MAIL_DATA�\���̌^�f�[�^�̒��g���Z�[�u�f�[�^�ɔ��f�����̂�
 *	�@�������ȃf�[�^�����Ȃ��悤�ɒ��ӁI
 */
extern void MAIL_AddMailFormWork(MAIL_BLOCK* block,
		MAILBLOCK_ID blockID,int dataID,MAIL_DATA* src);


//=============================================================
/**
 *	���[���Z�[�u�f�[�^�u���b�N�A�N�Z�X�n�֐�
 */
//=============================================================
//
/**
 *	@brief	�Z�[�u�f�[�^�u���b�N�ւ̃|�C���^���擾
 */
extern MAIL_BLOCK* SaveData_GetMailBlock(SAVEDATA* sv);

/**
 *	@brief	���[���Z�[�u�f�[�^�u���b�N�T�C�Y�擾
 *
 *	�����[���f�[�^��ʂ̃T�C�Y�ł͂Ȃ��̂Œ��ӁI
 */
extern int MAIL_GetBlockWorkSize(void);

/**
 *	@brief	���[���Z�[�u�f�[�^�u���b�N������
 */
extern void MAIL_Init(MAIL_BLOCK* dat);

/**
 *	@brief	�󂢂Ă��郁�[���f�[�^ID���擾
 *
 *	@param	id �ǉ����������[���u���b�NID
 *
 *	@return	int	�f�[�^��ǉ��ł���ꍇ�͎Q��ID
 *				�ǉ��ł��Ȃ��ꍇ�̓}�C�i�X�l���Ԃ�
 */
extern int MAIL_SearchNullID(MAIL_BLOCK* block,MAILBLOCK_ID id);

/**
 *	@brief	���[���f�[�^���폜
 *
 *	@param	blockID	�u���b�N��ID
 *	@param	dataID	�f�[�^ID
 */
extern void MAIL_DelMailData(MAIL_BLOCK* block,MAILBLOCK_ID blockID,int dataID);

/**
 *	@brief	���[���f�[�^���Z�[�u�u���b�N�ɒǉ�
 *
 *	�������n����MAIL_DATA�\���̌^�f�[�^�̒��g���Z�[�u�f�[�^�ɔ��f�����̂�
 *	�@�������ȃf�[�^�����Ȃ��悤�ɒ��ӁI
 */
extern void MAIL_AddMailFormWork(MAIL_BLOCK* block,MAILBLOCK_ID blockID,int dataID,MAIL_DATA* src);

/**
 *	@brief	�w��u���b�N�ɗL���f�[�^���������邩�Ԃ�
 */
extern int MAIL_GetEnableDataNum(MAIL_BLOCK* block,MAILBLOCK_ID blockID);

/**
 *	@brief	���[���f�[�^�̃R�s�[���擾
 *
 *	�������Ń��������m�ۂ���̂ŁA�Ăяo�������ӔC�����ė̈���J�����邱��
 */
extern MAIL_DATA* MAIL_AllocMailData(MAIL_BLOCK* block,MAILBLOCK_ID blockID,int dataID,int heapID);

/**
 *	@brief	���[���f�[�^�̃R�s�[���擾
 *
 *	�����炩���ߊm�ۂ���MAIL_DATA�^�������ɃZ�[�u�f�[�^���R�s�[���Ď擾
 */
extern void MAIL_GetMailData(MAIL_BLOCK* block,MAILBLOCK_ID blockID,int dataID,MAIL_DATA* dest);


//=============================================================
/**
 *	���[���f�[�^�A�N�Z�X�n�֐�
 */
//=============================================================
/**
 *	@brief	���[���f�[�^�T�C�Y�擾
 *
 *	�����[���f�[�^��ʂ̃T�C�Y
 */
extern int MailData_GetDataWorkSize(void);

/**
 *	@brief	���[���f�[�^�N���A(�����f�[�^�Z�b�g)
 */
extern void MailData_Clear(MAIL_DATA* dat);

/**
 *	@brief	���[���f�[�^���L�����ǂ����Ԃ�
 *	@retval	FALSE	����
 *	@retval	TRUE	�L��
 */
extern BOOL MailData_IsEnable(MAIL_DATA* dat);

/**
 *	@brief	���[���f�[�^�̃��[�N���擾���ĕԂ�
 *
 *	���Ăяo�������ӔC�����ĉ�����邱��
 *	
 */
extern MAIL_DATA* MailData_CreateWork(int heapID);

/**
 *	@brief	���[���f�[�^�̍\���̃R�s�[
 */
extern void MailData_Copy(MAIL_DATA* src,MAIL_DATA* dest);

/**
 *	@brief	�f�U�C��No,��������|�P�����̃|�W�V�����A�Z�[�u�f�[�^���w�肵��
 *			���[���f�[�^��V�K�쐬��Ԃɏ�����
 *	@param	dat	�f�[�^���쐬����MAIL_DATA�\���̌^�ւ̃|�C���^
 *	@param	design_no	���[���̃C���[�WNo
 *	@param	pos		���[������������|�P�����̎莝�����̃|�W�V����
 *	@param	save	�Z�[�u�f�[�^�ւ̃|�C���^
 */
extern void MailData_CreateFromSaveData(MAIL_DATA* dat,u8 design_no,u8 pos,SAVEDATA* save);

/**
 *	@brief	���[���f�[�^�@�g���[�i�[ID�A�N�Z�X
 */
extern u32	MailData_GetWriterID(const MAIL_DATA* dat);
extern void MailData_SetWriterID(MAIL_DATA* dat,u32 id);

/**
 *	@brief	���[���f�[�^�@���C�^�[���A�N�Z�X
 */
extern STRCODE* MailData_GetWriterName(MAIL_DATA* dat);
extern void MailData_SetWriterName(MAIL_DATA* dat,STRCODE* name);

/**
 *	@brief	���[���f�[�^�@���C�^�[�̐��ʃA�N�Z�X
 */
extern u8	MailData_GetWriterSex(const MAIL_DATA* dat);
extern void MailData_SetWriterSex(MAIL_DATA* dat,const u8 sex);

/**
 *	@brief	���[���f�[�^�@�f�U�C��No�A�N�Z�X
 */
extern u8	MailData_GetDesignNo(const MAIL_DATA* dat);
extern void MailData_SetDesignNo(MAIL_DATA* dat,const u8 design);

/**
 *	@brief	���[���f�[�^�@���R�[�h�A�N�Z�X
 */
extern u8	MailData_GetCountryCode(const MAIL_DATA* dat);
extern void MailData_SetCountryCode(MAIL_DATA* dat,const u8 code);

/**
 *	@brief	���[���f�[�^�@�J�Z�b�g�o�[�W�����A�N�Z�X
 */
extern u8	MailData_GetCasetteVersion(const MAIL_DATA* dat);
extern void MailData_SetCasetteVersion(MAIL_DATA* dat,const u8 version);

/**
 *	@brief	���[���f�[�^�@���[���A�C�R���p�����[�^�̎擾(�C���f�b�N�X�w���)
 *
 *	@param	mode	MAIL_ICONPRM_CGX:cgxNo�̎擾
 *					MAIL_ICONPRM_PLT:pltNo�̎擾
 *					MAIL_ICONPRM_ALL:u16�^(MAIL_ICON�^�փL���X�g��)�őo���̒l��Ԃ�
 *
 *	���A�C�R��CgxID�ƃ����X�^�[No�͓���ł͂���܂���B���ӁI
 */
extern u16	MailData_GetIconParamByIndex(const MAIL_DATA* dat,u8 index,u8 mode);
extern void MailData_SetIconParamByIndex(MAIL_DATA* dat,u16 id,u8 index,u8 mode);

/**
 *	@brief	���[���f�[�^�@���[���A�C�R���f�[�^�̎擾(�C���f�b�N�X�w���)
 *
 *	@param	index	�f�[�^�擾�J�n�C���f�b�N�XNo(index<MAILDAT_ICONMAX)
 *	@param	pi		�f�[�^�i�[�ꏊ�ւ̃|�C���^
 *	@param	num		�f�[�^�擾��
 *	
 *	���A�C�R��No�ƃ����X�^�[No�͓���ł͂���܂���B���ӁI
 *	���C���f�b�N�X���s���������ꍇ�ANULL�A�C�R���f�[�^���i�[���ĕԂ��܂�
 */
extern void MailData_GetIconArray(MAIL_DATA* dat,u8 index,MAIL_ICON* pi,u8 num);


/**
 *	@brief	���[���f�[�^�@�ȈՕ��擾(�C���f�b�N�X�w���)
 */
extern PMS_DATA*	MailData_GetMsgByIndex(MAIL_DATA* dat,u8 index);
extern void MailData_SetMsgByIndex(MAIL_DATA* dat,PMS_DATA* pms,u8 index);

/**
 *	@brief	���[���f�[�^�@�ȈՕ�������擾(�C���f�b�N�X�w��)
 *
 *	@param	dat	MAIL_DATA*
 *	@param	index	�ȈՕ��C���f�b�N�X
 *	@param	buf		�擾����������|�C���^�̊i�[�ꏊ
 *
 *	@retval	FALSE	������̎擾�Ɏ��s(�܂��͊ȈՕ����L���ȃf�[�^�ł͂Ȃ�)
 *	
 *	@li	buf�ɑ΂��ē����Ń��������m�ۂ��Ă���̂ŁA�Ăяo�����������I�ɉ�����邱��
 *	@li	FALSE���Ԃ����ꍇ�Abuf��NULL�N���A�����
 */
extern BOOL MailData_GetMsgStrByIndex(const MAIL_DATA* dat,u8 index,STRBUF* buf,int heapID);

#endif	//__H_MAIL_UTIL_H__


