//=============================================================================
/**
 * @file	comm_union_view_def.h
 * @brief	���j�I�����[���ł̏��ʕ`�揈��
 *          
 * @author	Akito Mori
 * @date    2005.12.20
 */
//=============================================================================

#ifndef __COMM_UNION_VIEW_DEF_H__
#define __COMM_UNION_VIEW_DEF_H__

// ���j�I���n�a�i�̐�
#define UNION_BEACON_OBJ_MAX	( 50 )

// �G�t�F�N�g����l���n�a�i�ɂ����鎞�̔ԍ�
#define UNION_EFFECT_HERO_NO	( 50 )	

// ���j�I���`���b�g�̍ő吔
#define UNION_CHAT_MAX		( 30 )

// =======================================================================
// �萔�錾
// =======================================================================
enum{
	OBJ_NO_APPEAR=0,
	OBJ_FALL_WAIT,
	OBJ_OK,
	OBJ_RISE_WAIT,
	OBJ_RISED,
};

enum{
	OBJ_REQ_NO    =0,
	OBJ_REQ_FALL,
	OBJ_REQ_FALL_NOMOVE,
	OBJ_REQ_RISE,
};

enum{
	OBJ_MOVE_STAND=0,
	OBJ_MOVE_WALK,
};


// =======================================================================
// �n�a�i�Ǘ��p�\���̐錾
// =======================================================================
typedef struct{
	u8      request;		// �o�����N�G�X�g
	u8		appear;			// �o���t���O
	u8		friend;			// ���肠���O���[�v�ɓo�^����Ă��邩�H
	u8 		effect;			// �G�t�F�N�g�J�n�t���O
	u8		effect_onflag;	// �G�t�F�N�g�\�����̎��
	u8      arrow;			// �����Ă������
	u16		wait;			// �G�t�F�N�g��������
	u8		view;			// �����ڔԍ�
	u8      appearmode;     // OBJ�s�����[�h�i0:�����Ȃ�	1:�������)
	u32		trainerId;		// �g���[�i�[�h�c
	EOA_PTR effect_ptr;		// �Ԃ��g�G�t�F�N�g�Ǘ��|�C���^
	EOA_PTR shadow_ptr;		// �Ƃ������O���[�v�}�[�N�i�����̐Ԃ��ہE���ہj�Ǘ��|�C���^
}OBJ_VIEW_WORK;


// =======================================================================
// ���j�I���`���b�g���[�N�\���̐錾
// =======================================================================
typedef struct{
	STRBUF		*name;
    STRBUF		*message;
    STRBUF		*friend;
	u32			id;
	int			sex;
	PMS_DATA	PmsData;
}UNION_CHAT;

struct UNION_CHAT_RINGBUF{
	UNION_CHAT mes[UNION_CHAT_MAX];		// ���b�Z�[�W���i�[�����i�����O�o�b�t�@�j
	int 		  num;					// �o�^����Ă��郁�b�Z�[�W�̐�
	int			  start;				// �����O�o�b�t�@�̃X�^�[�g�|�C���g
};


// =======================================================================
// ���j�I���r���[�\���̐錾
// =======================================================================
struct COMM_UNIONROOM_VIEW{
	COMM_UNIONROOM_WORK *cuw;
	TCB_PTR				viewTask;
	PLAYER_STATE_PTR    jiki;
	OBJ_VIEW_WORK 		objwork[UNION_BEACON_OBJ_MAX+1];	// FIELDOBJ50�l�{��l��
	FIELDSYS_WORK		*fsys;
	FRIEND_LIST	  		*friendlist;
	UNION_CHAT_RINGBUF  *unionBoardChat;
	int 				nowobj;

	int 				vanishflag;
};

#endif