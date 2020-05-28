#ifndef	__EVDTYPE_H__
#define	__EVDTYPE_H__

//ドアリンク用データ構造体
typedef struct{
	unsigned short	gx;
	unsigned short	gz;
	unsigned short	link_zone_id;
	unsigned short	link_door_id;
}CONNECT_DATA;

#define DOORID_NULL 0
#define ZONEID_NULL 0

#endif	/* __EVDTYPE_H__ */
