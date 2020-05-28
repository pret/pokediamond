#ifndef	__EVCTYPE_H__
#define	__EVCTYPE_H__

typedef struct _TAG_FIELD_OBJ_H
{
	unsigned short id;			///<����ID
	unsigned short obj_code;		///<�\������OBJ�R�[�h
	unsigned short move_code;	///<����R�[�h
	unsigned short event_type;	///<�C�x���g�^�C�v
	unsigned short event_flag;		///<�C�x���g�t���O
	unsigned short event_id;		///<�C�x���gID
	short dir;			///<�w�����
	unsigned short param;		///<�w��p�����^
	short move_limit_x;	///<X�����ړ�����
	short move_limit_z;	///<Z�����ړ�����
	unsigned short gx;			///<�O���b�hX		//�O���b�h���W��int�ň������Ƃ͂Ȃ��̂� unsigned short�ł��肢���܂�
	unsigned short gz;			///<�O���b�hZ
	int gy;			///<Y�l	Y�l��gy�̌^�� fx32�ł��肢���܂�
}_TAG_FIELD_OBJ_H;

#define SCRID_NULL 0
#define EVOBJ_NULL 0

#endif	/* __EVCTYPE_H__ */
