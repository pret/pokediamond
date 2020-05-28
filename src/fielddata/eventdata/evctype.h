#ifndef	__EVCTYPE_H__
#define	__EVCTYPE_H__

typedef struct _TAG_FIELD_OBJ_H
{
	unsigned short id;			///<識別ID
	unsigned short obj_code;		///<表示するOBJコード
	unsigned short move_code;	///<動作コード
	unsigned short event_type;	///<イベントタイプ
	unsigned short event_flag;		///<イベントフラグ
	unsigned short event_id;		///<イベントID
	short dir;			///<指定方向
	unsigned short param;		///<指定パラメタ
	short move_limit_x;	///<X方向移動制限
	short move_limit_z;	///<Z方向移動制限
	unsigned short gx;			///<グリッドX		//グリッド座標もintで扱うことはないので unsigned shortでお願いします
	unsigned short gz;			///<グリッドZ
	int gy;			///<Y値	Y値のgyの型は fx32でお願いします
}_TAG_FIELD_OBJ_H;

#define SCRID_NULL 0
#define EVOBJ_NULL 0

#endif	/* __EVCTYPE_H__ */
