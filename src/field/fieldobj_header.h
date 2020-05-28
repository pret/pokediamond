//==============================================================================
/**
 * @file	fieldobj_header.h
 * @brief	�t�B�[���h�I�u�W�F�N�g�w�b�_�[�\���̒�`�w�b�_�[
 * @author	kagaya
 * @data	05.07.13
 */
//==============================================================================
#ifndef FIELD_OBJ_HEADER_FILE
#define FIELD_OBJ_HEADER_FILE

//==============================================================================
//	typedef strcut
//==============================================================================
//--------------------------------------------------------------
//	�f�o�b�O
//--------------------------------------------------------------

//--------------------------------------------------------------
//	FIELD_OBJ ����A�`��֐����[�N�T�C�Y (byte size)
//--------------------------------------------------------------
#define FLDOBJ_MOVE_WORK_SIZE		(16)					///<����֐��p���[�N�T�C�Y
#define FLDOBJ_MOVE_SUB_WORK_SIZE	(16)					///<����T�u�֐��p���[�N�T�C�Y
#define FLDOBJ_MOVE_CMD_WORK_SIZE	(16)					///<����R�}���h�p���[�N�T�C�Y
#define FLDOBJ_DRAW_WORK_SIZE		(32)					///<�`��֐��p���[�N�T�C�Y

//--------------------------------------------------------------
//	�^��`
//--------------------------------------------------------------
typedef struct _TAG_FIELD_OBJ_H FIELD_OBJ_H;
typedef struct _TAG_FIELD_OBJ_SAVE_DATA * FIELD_OBJ_SAVE_DATA_PTR;

//--------------------------------------------------------------
///	FIELD_OBJ_H�\����
//--------------------------------------------------------------
struct _TAG_FIELD_OBJ_H
{
	unsigned short id;										///<����ID
	unsigned short obj_code;								///<�\������OBJ�R�[�h
	unsigned short move_code;								///<����R�[�h
	unsigned short event_type;								///<�C�x���g�^�C�v
	unsigned short event_flag;								///<�C�x���g�t���O
	unsigned short event_id;								///<�C�x���gID
	short dir;												///<�w�����
	unsigned short param0;									///<�w��p�����^ 0
	unsigned short param1;									///<�w��p�����^ 1
	unsigned short param2;									///<�w��p�����^ 2
	short move_limit_x;										///<X�����ړ�����
	short move_limit_z;										///<Z�����ړ�����
	unsigned short gx;										///<�O���b�hX
	unsigned short gz;										///<�O���b�hZ
	int gy;													///<Y�l fx32�^
};

#define FIELD_OBJ_H_SIZE (sizeof(FIELD_OBJ_H))				///<FIELD_OBJ_H�T�C�Y

//--------------------------------------------------------------
///	FIELD_OBJ_SAVE_DATA�\����
//--------------------------------------------------------------
typedef struct _TAG_FIELD_OBJ_SAVE_DATA
{
	u32 status_bit;											///<�X�e�[�^�X�r�b�g
	u32 move_bit;											///<����r�b�g
	u8 obj_id;												///<OBJ ID
	u8 move_code;											///<����R�[�h
	s8 move_limit_x;										///<X�����ړ�����
	s8 move_limit_z;										///<Z�����ړ�����
	s8 dir_head;											///<FIELD_OBJ_H�w�����
	s8 dir_disp;											///<���݌����Ă������
	s8 dir_move;											///<���ݓ����Ă������
	u8 dummy;												///<�_�~�[
	u16 zone_id;											///<�]�[�� ID
	u16 obj_code;											///<OBJ�R�[�h
	u16 event_type;											///<�C�x���g�^�C�v
	u16 event_flag;											///<�C�x���g�t���O
	u16 event_id;											///<�C�x���gID
	s16 param0;												///<�w�b�_�w��p�����^
	s16 param1;												///<�w�b�_�w��p�����^
	s16 param2;												///<�w�b�_�w��p�����^
	s16 gx_init;											///<�����O���b�hX
	s16 gy_init;											///<�����O���b�hY
	s16 gz_init;											///<�����O���b�hZ
	s16 gx_now;												///<���݃O���b�hX
	s16 gy_now;												///<���݃O���b�hY
	s16 gz_now;												///<���݃O���b�hZ
	fx32 fx32_y;											///<fx32�^�̍����l
	u8 move_proc_work[FLDOBJ_MOVE_WORK_SIZE];				///<����֐��p���[�N
	u8 move_sub_proc_work[FLDOBJ_MOVE_SUB_WORK_SIZE];		///<����T�u�֐��p���[�N
}FIELD_OBJ_SAVE_DATA;

#define FIELD_OBJ_SAVE_DATA_SIZE (sizeof(FIELD_OBJ_SAVE_DATA))	///<FIELD_OBJ_SAVE_DATA size

//--------------------------------------------------------------
///	FIELD_OBJ_SAVE_DATA�\���� old
//--------------------------------------------------------------
typedef struct _TAG_FIELD_OBJ_SAVE_DATA_OLD
{
	u32 status_bit;											///<�X�e�[�^�X�r�b�g
	u32 move_bit;											///<����r�b�g
	u32 obj_id;												///<OBJ ID
	u32 zone_id;											///<�]�[�� ID
	u32 obj_code;											///<OBJ�R�[�h
	u32 move_code;											///<����R�[�h
	u32 event_type;											///<�C�x���g�^�C�v
	u32 event_flag;											///<�C�x���g�t���O
	u32 event_id;											///<�C�x���gID
	int dir_head;											///<FIELD_OBJ_H�w�����
	int dir_disp;											///<���݌����Ă������
	int dir_move;											///<���ݓ����Ă������
	int param0;												///<�w�b�_�w��p�����^
	int param1;												///<�w�b�_�w��p�����^
	int param2;												///<�w�b�_�w��p�����^
	int move_limit_x;										///<X�����ړ�����
	int move_limit_z;										///<Z�����ړ�����
	int gx_init;											///<�����O���b�hX
	int gy_init;											///<�����O���b�hY
	int gz_init;											///<�����O���b�hZ
	int gx_now;												///<���݃O���b�hX
	int gy_now;												///<���݃O���b�hY
	int gz_now;												///<���݃O���b�hZ
	u8 move_proc_work[FLDOBJ_MOVE_WORK_SIZE];				///<����֐��p���[�N
	u8 move_sub_proc_work[FLDOBJ_MOVE_SUB_WORK_SIZE];		///<����T�u�֐��p���[�N
}FIELD_OBJ_SAVE_DATA_OLD;

#define FIELD_OBJ_SAVE_DATA_OLD_SIZE (sizeof(FIELD_OBJ_SAVE_DATA_OLD))

#endif //FIELD_OBJ_HEADER_FILE
