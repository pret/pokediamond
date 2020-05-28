//============================================================================================
/**
 * @file	ev_check.h
 * @brief	�C�x���g�����`�F�b�N�V�X�e��
 * @author	Sousuke Tamada
 * @date	01.03.29
 *
 * 05.07.04 Hiroyuki Nakamura
 */
//============================================================================================
#ifndef __EV_CHECK_H__
#define __EV_CHECK_H__

#include "field_common.h"



//=========================================================================
//	��`
//=========================================================================

/* �C�x���g�`�F�b�N���N�G�X�g�\���� */
typedef struct {
	u16	TalkCheck:1;
	u16	StepCheck:1;
	u16	MenuOpen:1;
	u16	CnvButton:1;
	u16	MatCheck:1;
	u16	PushCheck:1;
	u16	MoveCheck:1;
	u16	FloatCheck:1;

	u16	DebugMenu:1;
	u16	DebugBattle:1;
	u16	DebugHook:1;
	u16 DebugKeyPush:1;
	u16	:4;

	u8	Site;
	s8	PushSite;
	u16 trg;
	u16 cont;
}EV_REQUEST;


//=========================================================================
//	�֐��v���g�^�C�v
//=========================================================================

//�C�x���g�N���`�F�b�N�̃��N�G�X�g�Z�b�g
extern void SetRequest( EV_REQUEST * req, FIELDSYS_WORK * repw, u16 trg, u16 cont );

//�C�x���g�N���`�F�b�N���C��
extern int CheckRequest(const EV_REQUEST * req, FIELDSYS_WORK * repw);
// �Y�z���̃C�x���g�N������
extern BOOL CheckRequestUG( EV_REQUEST * req, FIELDSYS_WORK * repw );
// �ΐ펞�̃C�x���g�N������
extern BOOL CheckRequestVSRoom( EV_REQUEST * req, FIELDSYS_WORK * repw );
// ���j�I�����[���ł̃C�x���g�N���`�F�b�N
extern BOOL CheckRequestUnion(const EV_REQUEST * req, FIELDSYS_WORK * repw);
//�o�g���^���[��p�C�x���g�N���`�F�b�N
extern int CheckRequestBTower(const EV_REQUEST * req, FIELDSYS_WORK * repw);


#endif	/*__EV_CHECK_H__*/

