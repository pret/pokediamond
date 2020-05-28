/**
 *	@brief	ギネスホール　セーブデータ型
 */

#include "savedata/guinness.h"
///ギネスデータ型
struct _GUINNESS_DATA{
	u32	groupID;
	u32	record;
	STRCODE	name[PERSON_NAME_SIZE+EOM_SIZE];
};

///ギネスデータブロック型
struct _GUINNESS_BLOCK{
	struct _GUINNESS_DATA	dat[GNS_DATA_NUM];
};

///ギネスレコードデータ型(レコード交換時に使用)
struct _GUINNESS_RECORD{
	struct	_GUINNESS_DATA	dat[GNS_RECORD_NUM];
};

///ギネスホールデータ型
struct _GUINNESS{
	struct _GUINNESS_BLOCK	block[GNS_BLOCK_NUM];
};
