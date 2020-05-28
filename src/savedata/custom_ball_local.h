
#ifndef	__CUSTOM_BALL_LOCAL_H__
#define __CUSTOM_BALL_LOCAL_H__

#include "savedata/custom_ball.h"


#if 0 ///< 公開する
///< custom
struct _CUSTOM_BALL_SEAL {
	
	u8	seal_id;		///< シール番号
	u8	x;				///< x 座標
	u8	y;				///< y 座標
	
};

struct _CUSTOM_BALL_CORE {

	CB_SEAL	cb_seal[ CB_DEF_SEAL_MAX ];

};
#endif

#if 1
///< item
struct _CUSTOM_BALL_ITEM_DATA {
	
	u8	seal[ CB_DEF_ITEM_DATA_NUM_MAX ];
	
};


///< save
struct _CUSTOM_BALL_SAVE_DATA {
	
	CB_CORE			cb_core[ CB_DEF_CORE_MAX ];

	CB_ITEM_DATA	cb_item;
	
};
#endif


#endif


