//============================================================================================
/**
 * @file	b_app_tool.c
 * @brief	戦闘用アプリ共通処理
 * @author	Hiroyuki Nakamura
 * @date	06.03.30
 */
//============================================================================================
#include "common.h"
#include "system/clact_tool.h"
#include "battle_snd_def.h"

#define	B_APP_TOOL_H_GLOBAL
#include "b_app_tool.h"


//============================================================================================
//	定数定義
//============================================================================================
struct _BAPP_CURSOR_MVWK {
	BCURSOR_PTR	cursor;			// カーソルデータ
	const POINTER_WORK * cp_wk;	// カーソル位置ワーク
	u8	cur_flg;				// カーソルON/OFF
	u8	cur_pos;				// カーソル位置
	u8	old_pos;				// 前回のカーソル位置
	u32	mv_tbl;					// 移動テーブル
};

#define	PAD_KEY_ALL	( PAD_KEY_UP | PAD_KEY_DOWN | PAD_KEY_LEFT | PAD_KEY_RIGHT )





BAPP_CURSOR_MVWK * BAPP_CursorMoveWorkAlloc( u32 heap )
{
	BAPP_CURSOR_MVWK * wk = sys_AllocMemory( heap, sizeof(BAPP_CURSOR_MVWK) );
	memset( wk, 0, sizeof(BAPP_CURSOR_MVWK) );
	return wk;
}

void BAPP_CursorMoveWorkFree( BAPP_CURSOR_MVWK * wk )
{
	sys_FreeMemoryEz( wk );
}

BCURSOR_PTR BAPP_CursorMvWkGetBCURSOR_PTR( BAPP_CURSOR_MVWK * wk )
{
	return wk->cursor;
}

u8 BAPP_CursorMvWkGetPos( BAPP_CURSOR_MVWK * wk )
{
	return wk->cur_pos;
}

u8 BAPP_CursorMvWkGetFlag( BAPP_CURSOR_MVWK * wk )
{
	return wk->cur_flg;
}

void BAPP_CursorMvWkSetFlag( BAPP_CURSOR_MVWK * wk, u8 flg )
{
	wk->cur_flg = flg;
}

void BAPP_CursorMvWkSetBCURSOR_PTR( BAPP_CURSOR_MVWK * wk, BCURSOR_PTR cur )
{
	wk->cursor = cur;
}

void BAPP_CursorMvWkSetPos( BAPP_CURSOR_MVWK * wk, u8 pos )
{
	wk->cur_pos = pos;

	if( wk->cur_flg == 1 ){
		BCURSOR_PosSetON(
			wk->cursor,
			wk->cp_wk[wk->cur_pos].px, wk->cp_wk[wk->cur_pos].sx,
			wk->cp_wk[wk->cur_pos].py, wk->cp_wk[wk->cur_pos].sy );
	}
}

void BAPP_CursorMvWkPosInit( BAPP_CURSOR_MVWK * wk )
{
	wk->cur_pos = 0;
	wk->old_pos = 0xff;
}

void BAPP_CursorMvWkSetPoint( BAPP_CURSOR_MVWK * wk, const POINTER_WORK * pwk )
{
	BAPP_CursorMvWkPosInit( wk );
	wk->cp_wk  = pwk;
	wk->mv_tbl = 0xffffffff;

	if( wk->cur_flg == 1 ){
		BCURSOR_PosSetON(
			wk->cursor, wk->cp_wk[0].px, wk->cp_wk[0].sx, wk->cp_wk[0].py, wk->cp_wk[0].sy );
	}
}

void BAPP_CursorMvWkSetMvTbl( BAPP_CURSOR_MVWK * wk, u32 mv_tbl )
{
	wk->mv_tbl = mv_tbl;
}


static u8 BAPP_CursorOnOffCheck( BAPP_CURSOR_MVWK * wk )
{
	if( wk->cur_flg == 1 ){
		return TRUE;
	}

	if( sys.trg & ( PAD_KEY_ALL | PAD_BUTTON_CANCEL | PAD_BUTTON_DECIDE ) ){
		wk->cur_flg = 1;
		BCURSOR_PosSetON(
			wk->cursor,
			wk->cp_wk[ wk->cur_pos ].px, wk->cp_wk[ wk->cur_pos ].sx,
			wk->cp_wk[ wk->cur_pos ].py, wk->cp_wk[ wk->cur_pos ].sy );
		Snd_SePlay( BCURSOR_MOVE_SE );
	}
	return FALSE;
}

static u8 BAPP_OldCursorSetCheck( const POINTER_WORK * pw, u8 mv )
{
	switch( mv ){
	case POINT_MV_UP:
		if( pw->down & BAPP_CMV_RETBIT ){
			return TRUE;
		}
		break;
	case POINT_MV_DOWN:
		if( pw->up & BAPP_CMV_RETBIT ){
			return TRUE;
		}
		break;
	case POINT_MV_LEFT:
		if( pw->right & BAPP_CMV_RETBIT ){
			return TRUE;
		}
		break;
	case POINT_MV_RIGHT:
		if( pw->left & BAPP_CMV_RETBIT ){
			return TRUE;
		}
		break;
	}
	return FALSE;
}

u32 BAPP_CursorMove( BAPP_CURSOR_MVWK * wk )
{
	u8	lx, ly, rx, ry;
	u8	pm_ret;
	u8	mv;

	if( BAPP_CursorOnOffCheck( wk ) == FALSE ){ return BAPP_CMV_NONE; }

	if( sys.trg & PAD_KEY_UP ){
		pm_ret = PointerWkMoveSel( wk->cp_wk,NULL,NULL,NULL,NULL,wk->cur_pos,POINT_MV_UP );
		mv     = POINT_MV_UP;
	}else if( sys.trg & PAD_KEY_DOWN ){
		pm_ret = PointerWkMoveSel( wk->cp_wk,NULL,NULL,NULL,NULL,wk->cur_pos,POINT_MV_DOWN );
		mv     = POINT_MV_DOWN;
	}else if( sys.trg & PAD_KEY_LEFT ){
		pm_ret = PointerWkMoveSel( wk->cp_wk,NULL,NULL,NULL,NULL,wk->cur_pos,POINT_MV_LEFT );
		mv     = POINT_MV_LEFT;
	}else if( sys.trg & PAD_KEY_RIGHT ){
		pm_ret = PointerWkMoveSel( wk->cp_wk,NULL,NULL,NULL,NULL,wk->cur_pos,POINT_MV_RIGHT );
		mv     = POINT_MV_RIGHT;
	}else{
		pm_ret = BAPP_CMV_NONE;
	}

	if( pm_ret != POINT_SEL_NOMOVE ){
		u8	old_save = 1;

		if( pm_ret & BAPP_CMV_RETBIT ){
			if( wk->old_pos != 0xff ){
				pm_ret = wk->old_pos;
			}else{
				pm_ret ^= BAPP_CMV_RETBIT;
			}
		}

		while(1){
			u8	tmp;
			if( wk->mv_tbl & (1<<pm_ret) ){
				break;
			}
			old_save = 0;
			tmp = PointerWkMoveSel( wk->cp_wk,NULL,NULL,NULL,NULL,pm_ret,mv )&(0xff^BAPP_CMV_RETBIT);
			if( tmp == pm_ret || tmp == wk->cur_pos ){
				pm_ret = wk->cur_pos;
				break;
			}
			pm_ret = tmp;
		}

		if( wk->cur_pos != pm_ret ){
			PointerWkPosGet( &wk->cp_wk[pm_ret], &lx, &ly );
			PointerWkSizeGet( &wk->cp_wk[pm_ret], &rx, &ry );

			if( BAPP_OldCursorSetCheck(&wk->cp_wk[pm_ret],mv) == TRUE && old_save != 0 ){
				wk->old_pos = wk->cur_pos;
			}else{
				wk->old_pos = 0xff;
			}

			wk->cur_pos = pm_ret;
			BCURSOR_PosSetON( wk->cursor, lx, rx, ly, ry );
			Snd_SePlay( BCURSOR_MOVE_SE );
		}
		return BAPP_CMV_NONE;
	}

	if( sys.trg & PAD_BUTTON_DECIDE ){
//		Snd_SePlay( SEQ_SE_DP_DECIDE );
		return wk->cur_pos;
	}

	if( sys.trg & PAD_BUTTON_CANCEL ){
		Snd_SePlay( SEQ_SE_DP_DECIDE );
		return BAPP_CMV_CANCEL;
	}

	return BAPP_CMV_NONE;
}

