/**
 *	@brief	�|���g���X�g BMP���j���[�R���g���[��
 */

#ifndef __H_PORUCASE_BMP_H__
#define __H_PORUCASE_BMP_H__

typedef enum{
 MLIST_PUT,
 MLIST_DEL,
 MLIST_EXIT,
 MLIST_MAX
};

/**
 *	@brief	�|���g���X�g���j���[�쐬
 */
extern void PoruList_CreatePMenu(PORU_CASE_WORK* wk);
/**
 *	@brief	�|���g���X�g�@���j���[���X�g�폜
 */
extern void PoruList_DeletePMenu(PORU_CASE_WORK* wk,BOOL trans);

/**
 *	@brief	�|���g�{�^���v�b�V��������
 */
extern void PoruBtn_StateSet(PORU_CASE_WORK* wk,u8 idx,u8 state);

/**
 *	@brief	�|���g���X�g�\�[�g
 */
extern void PoruList_SortMenu(PORU_CASE_WORK* wk,u8 mode);

/**
 *	@brief	���j���[���X�g�쐬
 */
extern void MenuList_Create(PORU_CASE_WORK* wk);

/**
 *	@brief	���j���[���X�g�폜
 */
extern void MenuList_Delete(PORU_CASE_WORK* wk);

/**
 *	@brief	YesNo�E�B���h�E�`��O���b�Z�[�W�\��
 */
extern void YesNoList_StartMsgSet(PORU_CASE_WORK* wk);
/**
 *	@brief	�|���g���̂Ă܂����b�Z�[�W�Z�b�g
 */
extern void YesNoList_DelMsgSet(PORU_CASE_WORK* wk);

/**
 *	@brief	YesNo�E�B���h�E������
 */
extern void YesNoList_Create(PORU_CASE_WORK* wk);

/**
 *	@brief	������ʕ`�惁�b�Z�[�W�Z�b�g
 */
extern void PoruCase_DrawInitialMsg(PORU_CASE_WORK* wk);

#endif	//__H_PORUCASE_BMP_H__
