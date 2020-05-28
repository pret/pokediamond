//============================================================================================
/**
 * @file	check_data.h
 * @brief	�C�x���g�N���`�F�b�N�p�f�[�^��`�w�b�_
 * @date	2005.10.14
 *
 * src/fielddata/eventdata/�̃C�x���g�f�[�^�R���o�[�^������Q�Ƃ���Ă���B
 * ���̂��߂��̒��ɋL�q�ł�����e�ɂ͂��Ȃ萧�������邱�Ƃ𒍈ӂ��邱�ƁB
 */
//============================================================================================
#ifndef	__CHECK_DATA_H__
#define	__CHECK_DATA_H__

//------------------------------------------------------------------
///����ڑ��w��pID
//------------------------------------------------------------------
#define	ZONE_ID_SPECIAL		(0x0fff)
#define	SPECIAL_SPEXIT01	(0x0100)

//------------------------------------------------------------------
//------------------------------------------------------------------
typedef struct _EVENTDATA_HEADER EVENTDATA_HEADER;

struct _EVENTDATA_HEADER {
	u32 bg_count;
	u32 obj_count;
	u32 connect_count;
	u32 pos_count;
};
//------------------------------------------------------------------
///�h�A�����N�p�f�[�^�\����
//------------------------------------------------------------------
typedef struct _CONNECT_DATA CONNECT_DATA;

struct _CONNECT_DATA{
	u16	x;
	u16	z;
	u16	link_zone_id;
	u16	link_door_id;
	int	height;
};

//------------------------------------------------------------------
///BG�b�����f�[�^�\����
//------------------------------------------------------------------
typedef struct _BG_TALK_DATA BG_TALK_DATA;

struct _BG_TALK_DATA{
	u16	id;			// ID
	u16	type;		// �f�[�^�^�C�v
	int	gx;			// X���W
	int	gz;			// Y���W
	int	height;		// ����
	u16	dir;		// �b�����������^�C�v
};

//------------------------------------------------------------------
///POS�����C�x���g�f�[�^�\����
//------------------------------------------------------------------
typedef struct _POS_EVENT_DATA POS_EVENT_DATA;

struct _POS_EVENT_DATA{
	u16	id;			//ID
	u16	gx;			//x
	u16	gz;			//z
	u16	sx;			//sizeX
	u16	sz;			//sizeZ
	u16	height;		//height
	u16 param;
	u16 workID;
};



#endif	/*	__CHECK_DATA_H__ */
