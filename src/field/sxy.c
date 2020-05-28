//============================================================================================
/**
 * @file	sxy.c
 * @brief	イベント関連処理
 * @author	Hiroyuki Nakamura
 * @date	2004.11.30
 */
//============================================================================================
#define	SXY_H_GLOBAL

#include "common.h"
#include "talk_msg.h"
#include "fntsys.h"
#include "system/lib_pack.h"

#include "fieldobj.h"
#include "fieldsys.h"

#include "fieldmap.h"
#include "fld_bmp.h"

#include "script.h"
#include "field/evwkdef.h"

#include "sxy.h"

#include "zonedata.h"
#include "eventdata.h"		//ゾーン毎のイベントデータ参照のため

#include "scr_tool.h"


//============================================================================================
//	定数定義
//============================================================================================
// BG話しかけイベント：話しかけ方向
enum {
	BG_TALK_DIR_DOWN = 0,		// 下から
	BG_TALK_DIR_LEFT,			// 左から
	BG_TALK_DIR_RIGHT,			// 右から
	BG_TALK_DIR_UP,				// 上から
	BG_TALK_DIR_ALL,			// 全方向
	BG_TALK_DIR_SIDE,			// 左右から
	BG_TALK_DIR_UPDOWN,			// 上下から
};


//============================================================================================
//	プロトタイプ宣言
//============================================================================================
static u8 TalkBgDirCheck( FIELDSYS_WORK * repw, const BG_TALK_DATA * bg );
static u8 TalkBgHideItemCheck( FIELDSYS_WORK * repw, const BG_TALK_DATA * bg );



//============================================================================================
//============================================================================================
//	話しかけ処理
//============================================================================================
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * 主人公の前の位置を取得
 *
 * @param	repw	フィールドデータ
 * @param	gx		X座標格納場所
 * @param	gz		Z座標格納場所
 *
 * @return	向き
 */
//--------------------------------------------------------------------------------------------
static int Player_FrontPosGet( FIELDSYS_WORK * repw, int * gx, int * gz )
{
	int	dir = Player_DirGet( repw->player );

	*gx = Player_NowGPosXGet( repw->player );
	*gz = Player_NowGPosZGet( repw->player );

	switch( dir ){
	case DIR_UP:		// 上向き
		*gz -= 1;
		break;
	case DIR_DOWN:		// 下向き
		*gz += 1;
		break;
	case DIR_LEFT:		// 左向き
		*gx -= 1;
		break;
	case DIR_RIGHT:		// 右向き
		*gx += 1;
		break;
	}

	//OS_Printf( "TALK_FRONT : %d, %d\n", *gx, *gz );
	return dir;
}

static u8 TalkObjEventHeightChack( PLAYER_STATE_PTR jiki, FIELD_OBJ_PTR obj )
{
	FIELD_OBJ_PTR jiki_obj = Player_FieldOBJGet( jiki );

	if( FieldOBJ_HeightGridGet(jiki_obj) == FieldOBJ_HeightGridGet(obj) ){
		return TRUE;
	}
	return FALSE;
}


//--------------------------------------------------------------------------------------------
/**
 * 会話キャラOBJ取得
 *
 * @param	repw	フィールドデータ
 * @param	obj		キャラデータ格納場所
 *
 * @retval	"TRUE = キャラがいる"
 * @retval	"FALSE = キャラがいない"
 */
//--------------------------------------------------------------------------------------------
void SXY_HeroFrontObjGet( FIELDSYS_WORK * repw, FIELD_OBJ_PTR * obj )
{
	int	gx, gz;
	int	dir;
	MATR attr;

	dir  = Player_FrontPosGet( repw, &gx, &gz );
	attr = GetAttributeLSB( repw, gx, gz );

	if( MATR_IsCounter( attr ) == TRUE ){
		switch( dir ){
		case DIR_UP:		// 上向き
			gz -= 1;
			break;
		case DIR_DOWN:		// 下向き
			gz += 1;
			break;
		case DIR_LEFT:		// 左向き
			gx -= 1;
			break;
		case DIR_RIGHT:		// 右向き
			gx += 1;
			break;
		}
	}
	*obj = FieldOBJ_SearchGPos( repw->fldobjsys, gx, gz );
}

u8 TalkObjEventCheck( FIELDSYS_WORK * repw, FIELD_OBJ_PTR * obj )
{
	SXY_HeroFrontObjGet( repw, obj );
	if( *obj != NULL ){
		if( FieldOBJ_StatusBitCheck_Talk(*obj) == TRUE &&
			TalkObjEventHeightChack( repw->player, *obj ) == TRUE ){
			return TRUE;
		}
	}
	return FALSE;

/*
	int	gx, gz;
	int	dir;
	MATR attr;

	dir  = Player_FrontPosGet( repw, &gx, &gz );
	attr = GetAttributeLSB( repw, gx, gz );

	if( MATR_IsCounter( attr ) == TRUE ){
		switch( dir ){
		case DIR_UP:		// 上向き
			gz -= 1;
			break;
		case DIR_DOWN:		// 下向き
			gz += 1;
			break;
		case DIR_LEFT:		// 左向き
			gx -= 1;
			break;
		case DIR_RIGHT:		// 右向き
			gx += 1;
			break;
		}
	}

	*obj = FieldOBJ_SearchGPos( repw->fldobjsys, gx, gz );
	if( *obj != NULL ){
		if( FieldOBJ_StatusBitCheck_Talk(*obj) == TRUE &&
			TalkObjEventHeightChack( repw->player, *obj ) == TRUE ){
			return TRUE;
		}
	}

	return FALSE;
*/
}

//--------------------------------------------------------------------------------------------
/**
 * BG話しかけイベントのID取得
 *
 * @param	repw	フィールドデータ
 * @param	data	BG話しかけデータ
 * @param	size	BG話しかけデータ数
 *
 * @retval	"EVENT_ID_NONE = データなし"
 * @retvel	"EVENT_ID_NONE != BGデータのID"
 */
//--------------------------------------------------------------------------------------------
u16 TalkBgEventCheck( FIELDSYS_WORK * repw, void * data, int size )
{
	const BG_TALK_DATA * bg;
	int	gx, gz;
	int	i;

	bg = (const BG_TALK_DATA *)data;

	Player_FrontPosGet( repw, &gx, &gz );

	for( i=0; i<size; i++ ){
		if( gx == bg[i].gx && gz == bg[i].gz ){
			if( bg[i].type == BG_TALK_TYPE_HIDE ){
				if( TalkBgHideItemCheck( repw, &bg[i] ) == TRUE ){
					return bg[i].id;
				}
			}else{
				if( TalkBgDirCheck( repw, &bg[i] ) == TRUE ){
					return bg[i].id;
				}
			}
		}
	}

	return EVENT_ID_NONE;
}

static u8 TalkBgHideItemCheck( FIELDSYS_WORK * repw, const BG_TALK_DATA * bg )
{
	//隠しアイテムかチェック
	if( bg->type != BG_TALK_TYPE_HIDE ){
		return FALSE;
	}

	//すでに取得済みかチェック
	if( CheckEventFlag(repw, GetHideItemFlagNoByScriptId(bg->id)) == 1 ){
		return FALSE;
	}

	return TRUE;
}

static u8 TalkBgDirCheck( FIELDSYS_WORK * repw, const BG_TALK_DATA * bg )
{
	if( bg->dir == BG_TALK_DIR_ALL ){ return TRUE; }

	switch( Player_DirGet( repw->player ) ){
	case DIR_UP:		// 上向き
		if( bg->dir == BG_TALK_DIR_DOWN || bg->dir == BG_TALK_DIR_UPDOWN ){
			return TRUE;
		}
		break;
	case DIR_DOWN:		// 下向き
		if( bg->dir == BG_TALK_DIR_UP || bg->dir == BG_TALK_DIR_UPDOWN ){
			return TRUE;
		}
		break;
	case DIR_LEFT:		// 左向き
		if( bg->dir == BG_TALK_DIR_RIGHT || bg->dir == BG_TALK_DIR_SIDE ){
			return TRUE;
		}
		break;
	case DIR_RIGHT:		// 右向き
		if( bg->dir == BG_TALK_DIR_LEFT || bg->dir == BG_TALK_DIR_SIDE ){
			return TRUE;
		}
		break;
	}
	return FALSE;
}



u16 TalkAutoBgBoardEventCheck( FIELDSYS_WORK * repw, void * data, int size )
{
	const BG_TALK_DATA * bg;
	int	gx, gz;
	int	i;

	if( Player_DirGet( repw->player ) != DIR_UP ){
		return EVENT_ID_NONE;
	}

	bg = (const BG_TALK_DATA *)data;

	Player_FrontPosGet( repw, &gx, &gz );

	for( i=0; i<size; i++ ){
		if( gx == bg[i].gx && gz == bg[i].gz && bg[i].type == BG_TALK_TYPE_BOARD ){
			return bg[i].id;
		}
	}

	return EVENT_ID_NONE;
}

u8 TalkAutoObjBoardEventCheck( FIELDSYS_WORK * repw, FIELD_OBJ_PTR * obj )
{
	if( Player_DirGet( repw->player ) != DIR_UP ){
		return FALSE;
	}

	if( TalkObjEventCheck( repw, obj ) == TRUE ){
		u32	code = FieldOBJ_OBJCodeGet( *obj );
		if( code == BOARD_A || code == BOARD_B || code == BOARD_C ||
			code == BOARD_D || code == BOARD_E || code == BOARD_F ){
			return TRUE;
		}
	}
	return FALSE;
}




//============================================================================================
//============================================================================================
//	位置発動イベント処理	POS EVENT
//============================================================================================
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * POSイベントID取得
 *
 * @param	repw	フィールドデータ
 * @param	data	POSイベントデータ
 * @param	size	POSイベントデータ数
 *
 * @retval	"EVENT_ID_NONE = データなし"
 * @retvel	"EVENT_ID_NONE != POSイベントデータのID"
 */
//--------------------------------------------------------------------------------------------
u16 PosEventCheck( FIELDSYS_WORK * repw, void * data, int size )
{
	const POS_EVENT_DATA * ev;
	int	gx, gz;
	int	i;

	ev = (const POS_EVENT_DATA *)data;

	gx = Player_NowGPosXGet( repw->player );
	gz = Player_NowGPosZGet( repw->player );

//	Player_FrontPosGet( repw, &gx, &gz );

	for( i=0; i<size; i++ ){
		if( gx >= ev[i].gx && gx < ( ev[i].gx + ev[i].sx ) &&
			gz >= ev[i].gz && gz < ( ev[i].gz + ev[i].sz ) &&
			GetEventWorkValue( repw, ev[i].workID ) == ev[i].param ){
			
			return ev[i].id;
		}
	}

	return EVENT_ID_NONE;
}
