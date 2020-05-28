#ifndef	__EVPTYPE_H__
#define	__EVPTYPE_H__

typedef struct {
	unsigned short	id;			//ID
	unsigned short	gx;			//x
	unsigned short	gz;			//z
	unsigned short	sx;			//sizeX
	unsigned short	sz;			//sizeZ
	unsigned short	height;		//height
	unsigned short	param;		//param
	unsigned short	workID;		//workID
}POS_EVENT_DATA;

#define SCRID_NULL 0

#endif	/* __EVPTYPE_H__ */
