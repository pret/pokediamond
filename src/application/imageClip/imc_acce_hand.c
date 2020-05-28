//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		imc_acce_hand.c
 *	@brief		イメージクリップ アクセサリハンド システム
 *				アクセサリ操作モード時のハンドシステムです
 *	@author		tomoya takahashi
 *	@data		2005.09.23
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

#include "system.h"
#include "assert.h"
#include "calctool.h"
#include "tcb.h"
#include "include/system/lib_pack.h"
#include "include/system/heapdefine.h"
#include "include/application/imageClip/imc_drawdata_define.h"
#include "include/application/imageClip/imc_obj_list_func.h"
#include "include/application/imageClip/imc_snd_def.h"
#include <string.h>

#define __IMC_ACCE_HAND_H_GLOBAL
#include "include/application/imageClip/imc_acce_hand.h"

//-----------------------------------------------------------------------------
/**
 *					定数宣言
*/
//-----------------------------------------------------------------------------
#define	IMC_ACCE_HAND_PRI		(0)	// つかんだアクセサリの優先順位


//-------------------------------------
//	
//	左ボックス返却タスク用
//	
//=====================================
#define IMC_ACCE_HAND_LBOX_RET_SYNC	(4)

//-----------------------------------------------------------------------------
/**
 *					構造体宣言
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	
//	アクセサリハンド　構造体
//	
//=====================================
typedef struct {
	IMC_DRAW_DATA* drawData;	// 描画データ構造体
	IMC_RIGHT_BOX*	rbox;		// 右ボックス構造体
	IMC_LEFT_BOX*	lbox;		// 左ボックス構造体
	IMC_SUBWIN*		subwin;		// サブウィンドウ構造体

	IMC_OBJLIST* obj;			// 持ってるオブジェクトデータ
	int offset_x;				// 左上からのオフセットｘ座標
	int offset_y;				// 左上からのオフセットｙ座標
	s16 from_x;					// 持ったときの座標
	s16 from_y;
	u8	from;					// 元いた場所	
	u8	from_list;				// 元いた場所のリストナンバー

	// ポケモンが使う
	int last_x;
	int last_y;
	BOOL poketouch;		// ポケモンに振れることが出来るかどうか

	u32 push_flg;

} IMC_ACCE_HAND;

//-------------------------------------
//	
//	左ボックス返却エフェクトタスク
//	
//=====================================
typedef struct {
	IMC_LEFT_BOX*	lbox;	// 左ボックス構造体
	IMC_OBJLIST* obj;		// 持ってるオブジェクトデータ
	int one_x;		// 1syncに動く値
	int one_y;		// 1syncに動く値
	int targ_x;		// ターゲットｘ座標
	int targ_y;		// ターゲットｙ座標
	int lbox_mode;	// 登録先左ボックスアクセサリモード
	int list_no;	// 登録先左ボックスアクセサリリストNo
	int count;		// 後何回動くか
	int* p_left_state;	// 左ボックスステータス
	u32* p_new_push_flg;// アクセサリ戻り中に新しいプッシュがあった
} IMC_ACCE_HAND_EFE_LBOX_RET;


//-----------------------------------------------------------------------------
/**
 *					プロトタイプ宣言
*/
//-----------------------------------------------------------------------------
static void imcAcceHandPushFunc( IMC_HAND* hand );
static void imcAcceHandPopFunc( IMC_HAND* hand );
static void imcAcceHandPushIngFunc( IMC_HAND* hand );

static void setAcceHandAcce( IMC_ACCE_HAND* hand, IMC_OBJLIST* obj, int from, int offset_x, int offset_y, int pri );
static void cleanAcceHandAcce( IMC_ACCE_HAND* hand );

static void imcSubWinMsgPrint( IMC_ACCE_HAND* hand );


// ポケモン用
static void imcAcceHandPopForPokeFunc( IMC_HAND* hand );
static void imcAcceHandPushIngForPokeFunc( IMC_HAND* hand );

static void imcAcceHandGetObjRect( IMC_HAND* hand, int* top, int* bottom, int* left, int* right );
static void imcAcceHandGetObjRectSubInSize( IMC_HAND* hand, int* top, int* bottom, int* left, int* right );
static void imcAcceHandSetPokeMatrix( IMC_HAND* hand, int x, int y );


static void imcAcceHandBgDummyPop( IMC_HAND* hand );
static void imcAcceHandBgDummy( IMC_HAND* hand );
static void imcBGHandRefFunc( IMC_HAND* hand );


//-------------------------------------
//	
//	動作タスク系
//	
//=====================================
// 左ボックスに戻す
static void imcAcceHandIconLboxRetStart( IMC_ACCE_HAND* acce_hand, int sync, int targ_x, int targ_y, int acce_mode, int list_no );
static void imcAcceHandIconLboxRetTsk( TCB_PTR tcb, void* work );


static void imcAcceHandSameThingHave( IMC_ACCE_HAND* acce_hand );
static void imcAcceHandTakaOff( IMC_ACCE_HAND* acce_hand );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	アクセサリハンド作成
 *
 *	@param	hand		ハンド構造体
 *	@param	rbox		右ボックス構造体
 *	@param	lbox		左ボックス構造体
 *	@param	drawData	描画データ構造体
 *	@param	subwin		サブウィンドウ構造体
 *	@param	poketouch	ポケモンにふれるかどうか
 *	
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_ACCE_HAND_Init( IMC_HAND* hand, IMC_RIGHT_BOX* rbox, IMC_LEFT_BOX* lbox, IMC_DRAW_DATA* drawData, IMC_SUBWIN* subwin, BOOL poketouch )
{
	IMC_ACCE_HAND* acce_hand;
	
	// ハンド構造体初期化
	IMC_HAND_Init( hand );

	// ワーク作成
	hand->hand_w = sys_AllocMemory( HEAPID_IMAGECLIP_DATA, sizeof( IMC_ACCE_HAND ) );
	memset( hand->hand_w, 0, sizeof( IMC_ACCE_HAND ) );
	acce_hand = hand->hand_w;

	acce_hand->rbox = rbox;
	acce_hand->lbox = lbox;
	acce_hand->drawData = drawData;
	acce_hand->subwin	= subwin;
	acce_hand->poketouch = poketouch;

	// 関数設定
	hand->push		= imcAcceHandPushFunc;
	hand->pop		= imcAcceHandPopFunc;
	hand->push_ing	= imcAcceHandPushIngFunc;
	hand->dest		= IMC_ACCE_HAND_Delete;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	アクセサリハンド破棄
 *
 *	@param	hand	ハンド構造体
 *
 *	@return
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_ACCE_HAND_Delete( IMC_HAND* hand )
{
	// ワーク破棄
	sys_FreeMemoryEz( hand->hand_w );

	// 初期化
	IMC_HAND_Init( hand );
}




//-----------------------------------------------------------------------------
/**
*		プライベート関数
*/
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *
 *	@brief	押したときの動作
 *
 *	@param	hand	ハンド構造体
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void imcAcceHandPushFunc( IMC_HAND* hand )
{
	IMC_ACCE_HAND* acce_hand		= hand->hand_w;
	IMC_OBJLIST* obj;			// オブジェクトデータ
	BOOL ret;
	int offset_x, offset_y;		// 左上からのオフセット値
	int set_list;				// アクセサリを設定するリストNo
	int draw_pri;
	
	// 右ボックスに入っているかチェック
	ret = IMC_RBOX_TPHit( acce_hand->rbox );
	if( ret ){

		// アクセサリを触ってるかチェック
		obj = IMC_RBOX_TPHitObjEx( acce_hand->rbox, &offset_x, &offset_y, acce_hand->drawData->SWSP_UPchar );

		if( obj ){
			// 取得したのがポケモンのとき
			// poketouchメンバをみて
			// 操作禁止なら触らなかったことにする
			if( obj->flag == IMC_OBJLIST_POKE ){
				if( acce_hand->poketouch == FALSE ){
					obj = NULL;
				}
			}
		}

		if( (obj != NULL) ){
			
			if( obj->flag == IMC_OBJLIST_ACCE ){
				// アクセサリ切り離し
				IMC_RBOX_DeleteAccessorieMove( acce_hand->rbox, obj );
				draw_pri = IMC_ACCE_HAND_PRI;

			}else{

				// ポケモン操作OFFならポケモンを動かすことはしない
				// ポケモン切り離し
				IMC_RBOX_MoveDeletePoke( obj );
				draw_pri = IMC_POKE_DrawPriorityGet( obj->obj_data );	// 表示優先順位いまの通り
				// 座標を取得
				IMC_OBJLIST_ACCEPOKE_MatGet( obj, &acce_hand->last_x, &acce_hand->last_y );
			}
			
			// 表示優先順位の再設定
			IMC_RBOX_SetObjPriority( acce_hand->rbox );
			
			// 登録
			setAcceHandAcce( acce_hand, obj, IMC_ACCE_HAND_FROM_RBOX,
					offset_x, offset_y,  draw_pri );

			// BG優先順位の設定
			IMC_DRAW_WndMaskObjMoveSet();
		}
	}else{

		// 左ボックスに入っているかチェック
		ret = IMC_LBOX_TPHit( acce_hand->lbox );
		if( ret ){

			// アクセサリを触ってるかチェック
			obj = IMC_LBOX_TPHitAccessorieEx( acce_hand->lbox, &offset_x, &offset_y, acce_hand->drawData->SWSP_UPchar );
			if( obj != NULL ){
				
				// アクセサリ切り離し
				IMC_LBOX_DeleteAccessorieMove( obj );
				
				// 表示優先順位の再設定
				IMC_LBOX_SetAccessoriePriority( acce_hand->lbox );
			
				setAcceHandAcce( acce_hand, obj, IMC_ACCE_HAND_FROM_LBOX, 
						offset_x, offset_y, IMC_ACCE_HAND_PRI );	

				// BG優先順位の設定
				IMC_DRAW_WndMaskObjMoveSet();
			}
		}
	}

	if( acce_hand->obj ){
		int se = IMC_SE_HAVE_SAMETHING;
		// 離すときの動作関数設定
		// 押しっぱなし動作関数設定
		switch( acce_hand->obj->flag ){
		case IMC_OBJLIST_ACCE:
			hand->pop		= imcAcceHandPopFunc; 
			hand->push_ing	= imcAcceHandPushIngFunc; 
			break;
		case IMC_OBJLIST_BG:
			hand->pop		= imcAcceHandBgDummyPop; 
			hand->push_ing	= imcAcceHandBgDummy;
			imcBGHandRefFunc( hand );	// BG反映
			se = IMC_SE_BG_CHANGE;
			break;
		case IMC_OBJLIST_POKE:
			hand->pop		= imcAcceHandPopForPokeFunc; 
			hand->push_ing	= imcAcceHandPushIngForPokeFunc; 
			break;
		default:
			break;
		}
	
		// 何かをつかんだ音
		Snd_SePlay( se );
		
		// 持ったときのエフェクト
//		imcAcceHandSameThingHave( acce_hand );
		
		imcSubWinMsgPrint( acce_hand );
	}
}

// 背景用ダミー
static void imcAcceHandBgDummy( IMC_HAND* hand )
{
}

//----------------------------------------------------------------------------
/**
 *	@brief	背景用POP関数
 */
//-----------------------------------------------------------------------------
static void imcAcceHandBgDummyPop( IMC_HAND* hand )
{
	IMC_ACCE_HAND* bg_hand = hand->hand_w;
	

	// タッチしたオブジェがあるなら
	// そのナンバーのBGを右パレットに反映
	if( bg_hand->obj ){

		// オブジェのタイプがBGであることをチェック
		GF_ASSERT( bg_hand->obj->flag == IMC_OBJLIST_BG );
	
		// 左ボックス返却タスク生成
		imcAcceHandIconLboxRetStart( bg_hand, IMC_ACCE_HAND_LBOX_RET_SYNC, bg_hand->from_x, bg_hand->from_y, bg_hand->obj->flag, bg_hand->from_list );

		// 受け継ぎ完了
		cleanAcceHandAcce( bg_hand );
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	離した時の動作
 *
 *	@param	hand	ハンド構造体
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void imcAcceHandPopFunc( IMC_HAND* hand )
{
	IMC_ACCE_HAND* acce_hand		= hand->hand_w;
	int	acce_list_no;				// アクセサリリストナンバー
	int ret;
	int top, bottom, left, right;	// 各座標
	int size_x, size_y;				// サイズ
	int x,y;						// 座標
	BOOL check;						// 追加チェック

	// オブジェクトがあるとき
	if( acce_hand->obj ){
		// 矩形データ取得
		imcAcceHandGetObjRectSubInSize( hand, &top, &bottom, &left, &right );
		
		// 右ボックスに入っているかチェック
		// どこかが出ていたらだめ
		ret = IMC_RBOX_TPHitSelf( acce_hand->rbox, left, top );
		ret += IMC_RBOX_TPHitSelf( acce_hand->rbox, right, top );
		ret += IMC_RBOX_TPHitSelf( acce_hand->rbox, left, bottom );
		ret += IMC_RBOX_TPHitSelf( acce_hand->rbox, right, bottom );

		if( ret >= 4 ){

			// 今の座標で右ボックスにおく
			check = IMC_RBOX_AddAccessorieMove( acce_hand->rbox, acce_hand->obj, acce_hand->drawData->SWSP_UPchar );
			if( check == FALSE ){		// 登録失敗なら左に戻す
				x = acce_hand->from_x;
				y = acce_hand->from_y;
				
				// 左ボックスに返却するエフェクトの音
				Snd_SePlay( IMC_SE_RET_LBOX );

				// コメント表示
				IMC_SUBWIN_SetBmpWin( acce_hand->subwin, ARC_MSG, NARC_msg_imageclip_dat, imgclip_ng0002 );
			
				// 左ボックス返却タスク生成
				imcAcceHandIconLboxRetStart( acce_hand, IMC_ACCE_HAND_LBOX_RET_SYNC, x, y, acce_hand->obj->flag, acce_hand->from_list );

			}else{
				
				// 表示優先順位の再設定
				IMC_RBOX_SetObjPriority( acce_hand->rbox );
				// BG優先順位の設定
				IMC_DRAW_WndMaskNormalSet();
				acce_hand->push_flg = FALSE;

				// 右ボックスにおいた音
				Snd_SePlay( IMC_SE_ON_RBOX );
			}

		}else{
			// 左パレット判定
			IMC_ACCESSORIE_OBJ* acce_obj = acce_hand->obj->obj_data;	// ここにはアクセサリしか置けない

			// 食い込んでよいサイズを考慮しない
			imcAcceHandGetObjRect( hand, &top, &bottom, &left, &right );

			// 左ボックスに入っているかチェック
			ret = IMC_LBOX_TPHitSelf( acce_hand->lbox, left, top );
			ret += IMC_LBOX_TPHitSelf( acce_hand->lbox, right, bottom );
			if( ret < 2 ){
				
				// fromが左パレットなら
				// 左パレットにいたときの座標がある
				if( acce_hand->from == IMC_ACCE_HAND_FROM_RBOX ){
					IMC_OBJLIST_ACCEPOKE_SizeGet( acce_hand->obj, &size_x, &size_y );

					// 左ボックス適当な位置に戻す
					x = (IMC_LBOX_AREA_X_MOVEOK) + (gf_mtRand() % (IMC_LBOX_AREA_WIDTH_MOVEOK - size_x) );
					y = (IMC_LBOX_AREA_Y_MOVEOK) + (gf_mtRand() % (IMC_LBOX_AREA_HEIGHT_MOVEOK - size_y) );
				}else{

					x = acce_hand->from_x;
					y = acce_hand->from_y;
				}

				// 左ボックスに返却するエフェクトの音
				Snd_SePlay( IMC_SE_RET_LBOX );
			}else{
				
				// 今の座標を取得
				IMC_OBJLIST_ACCEPOKE_MatGet( acce_hand->obj, &x, &y );

				// 放した音
				Snd_SePlay( IMC_SE_TAKE_OFF );
			}

			// 右から来たアクセサリの時はリストナンバーを取得
			if( acce_hand->from == IMC_ACCE_HAND_FROM_RBOX){
				acce_hand->from_list = IMC_LBOX_GetListNo( acce_hand->obj->flag, acce_obj->accessorie_no, acce_hand->lbox->boxData.p_item_buff );
			}

			// 左ボックス返却タスク生成
			imcAcceHandIconLboxRetStart( acce_hand, IMC_ACCE_HAND_LBOX_RET_SYNC, x, y, acce_hand->obj->flag, acce_hand->from_list );

		}

		// 放したときのエフェクト
//		imcAcceHandTakaOff( acce_hand );

		// 受け継ぎ完了
		cleanAcceHandAcce( acce_hand );
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brieof	押しっぱなし時の動作
 *
 *	@param	hand		ハンド構造体
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void imcAcceHandPushIngFunc( IMC_HAND* hand )
{
	IMC_ACCE_HAND* acce_hand		= hand->hand_w;
	int x, y;

	// アクセサリを持っているときは、タッチパネルの位置に
	// アクセサリを動かす
	if( acce_hand->obj != NULL ){

		// 座標の正当性をチェック
		if( (sys.tp_x != 0xffff) &&
			(sys.tp_x != 0xffff) ){
		
			x = sys.tp_x - acce_hand->offset_x;
			y = sys.tp_y - acce_hand->offset_y;

			IMC_OBJLIST_ACCEPOKE_Mat( acce_hand->obj, x, y );
		}
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	離したときの動作	ポケモン持ってるときよう
 *
 *	@param	hand		ハンド構造体 
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void imcAcceHandPopForPokeFunc( IMC_HAND* hand )
{
	IMC_ACCE_HAND* acce_hand		= hand->hand_w;
	BOOL ret1, ret2;
	int size_x,size_y;			// オブジェクトサイズXY

	// オブジェクトがあるとき
	if( acce_hand->obj ){

		// 今の座標で右ボックスにおく
		IMC_RBOX_MoveAddPoke( acce_hand->rbox, acce_hand->obj );

		// 表示優先順位の再設定
		IMC_RBOX_SetObjPriority( acce_hand->rbox );


		// BG優先順位の設定
		IMC_DRAW_WndMaskNormalSet();
		acce_hand->push_flg = FALSE;

		// 放したときのエフェクト
//		imcAcceHandTakaOff( acce_hand );

		// 放した音
		Snd_SePlay( IMC_SE_TAKE_OFF );

		cleanAcceHandAcce( acce_hand );
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brieof	押しっぱなし時の動作	ポケモン持ってるときよう
 *
 *	@param	hand	ハンドデータ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void imcAcceHandPushIngForPokeFunc( IMC_HAND* hand )
{
	IMC_ACCE_HAND* acce_hand		= hand->hand_w;
	int size_x, size_y;
	int x,y;
	int area_x, area_y;
	int in_s_x, in_s_y;	// 食い込んでいてよいサイズ

	// アクセサリを持っているときは、タッチパネルの位置に
	// アクセサリを動かす
	if( acce_hand->obj != NULL ){

		// 座標の正当性をチェック
		if( (sys.tp_x != 0xffff) &&
			(sys.tp_x != 0xffff) ){
			
			// 食い込んでよいサイズを取得
			IMC_OBJLIST_ACCEPOKE_InSizeGet( acce_hand->obj, &in_s_x, &in_s_y );

			// サイズを取得
			IMC_OBJLIST_ACCEPOKE_SizeGet( acce_hand->obj, &size_x, &size_y );
			// 新座標を計算
			x = sys.tp_x - acce_hand->offset_x;
			y = sys.tp_y - acce_hand->offset_y;

			// 実あたり判定エリアを作成
			area_x = x + in_s_x;
			area_y = y + in_s_y;
			size_x -= in_s_x;
			size_y -= in_s_y;

			// 座標が右ボックス内になるようにする
			if( area_x <= IMC_RBOX_AREA_X_MOVEOK){
				x = IMC_RBOX_AREA_X_MOVEOK - in_s_x;
			}else{
				if( x + size_x >= (IMC_RBOX_AREA_X_MOVEOK + IMC_RBOX_AREA_WIDTH_MOVEOK) ){
					x = (IMC_RBOX_AREA_X_MOVEOK + IMC_RBOX_AREA_WIDTH_MOVEOK) - size_x;
				}
			}
			if( area_y <= IMC_RBOX_AREA_Y_MOVEOK){
				y = IMC_RBOX_AREA_Y_MOVEOK - in_s_y;
			}else{
				if( y + size_y >= (IMC_RBOX_AREA_Y_MOVEOK + IMC_RBOX_AREA_HEIGHT_MOVEOK) ){
					y = (IMC_RBOX_AREA_Y_MOVEOK + IMC_RBOX_AREA_HEIGHT_MOVEOK) - size_y;
				}
			}
			
			// 座標設定
			imcAcceHandSetPokeMatrix( hand, x, y );

			// この位置でアクセサリが食い込まないかチェック
			IMC_RBOX_GetPokeUpListEncSize( acce_hand->rbox,
					&in_s_x, &in_s_y );

			// 上の食い込んでいるサイズ分動かして再設定
			x += in_s_x;
			y += in_s_y;
			imcAcceHandSetPokeMatrix( hand, x, y );
		}
	}
}

#if 0
//----------------------------------------------------------------------------
/**
 *
 *	@brief	BG変更ハンド関数	離したとき
 *
 *	@param	hand	ハンド構造体
 *
 *	@return	none
 *
 * 
 *
 */
//-----------------------------------------------------------------------------
static void imcBGHandPopFunc( IMC_HAND* hand )
{
	IMC_ACCE_HAND* bg_hand = hand->hand_w;
	IMC_ACCESSORIE_OBJ* acce;	// アクセサリーオブジェ
	int acce_list_no;
	
	// タッチしたオブジェがあるなら
	// そのナンバーのBGを右パレットに反映
	if( bg_hand->obj ){
		
		// オブジェのタイプがBGであることをチェック
		GF_ASSERT( bg_hand->obj->flag == IMC_OBJLIST_BG );
		
		// アクセサリデータ代入
		acce = bg_hand->obj->obj_data;

		// 右パレット内にいたらBGを反映
		if( IMC_RBOX_TPHitSelf( bg_hand->rbox, hand->old_x, hand->old_y ) ){

			// アクセサリナンバーのBGを右パレットに設定
			IMC_RBOX_BGClean( bg_hand->rbox );
			IMC_RBOX_BGSet( bg_hand->rbox, acce->accessorie_no, HEAPID_IMAGECLIP_DRAW );

			// BG変更した音
			Snd_SePlay( IMC_SE_BG_CHANGE );
		}else{

			// 左ボックスに戻す音
			Snd_SePlay( IMC_SE_RET_LBOX );
		}
		
		// 左ボックス返却タスク生成
		imcAcceHandIconLboxRetStart( bg_hand, IMC_ACCE_HAND_LBOX_RET_SYNC, bg_hand->from_x, bg_hand->from_y, bg_hand->obj->flag, bg_hand->from_list );
		
		// 放したときのエフェクト
//		imcAcceHandTakaOff( bg_hand );
		
		// 受け継ぎ完了
		cleanAcceHandAcce( bg_hand );
	}
}
#endif

//----------------------------------------------------------------------------
/**
 *
 *	@brief	BG変更ハンド関数	離したとき
 *
 *	@param	hand	ハンド構造体
 *
 *	@return	none
 *
 * 
 *
 */
//-----------------------------------------------------------------------------
static void imcBGHandRefFunc( IMC_HAND* hand )
{
	IMC_ACCE_HAND* bg_hand = hand->hand_w;
	IMC_ACCESSORIE_OBJ* acce;	// アクセサリーオブジェ
	int acce_list_no;
	
	// タッチしたオブジェがあるなら
	// そのナンバーのBGを右パレットに反映
	if( bg_hand->obj ){
		
		// オブジェのタイプがBGであることをチェック
		GF_ASSERT( bg_hand->obj->flag == IMC_OBJLIST_BG );
		
		// アクセサリデータ代入
		acce = bg_hand->obj->obj_data;


		// アクセサリナンバーのBGを右パレットに設定
		IMC_RBOX_BGClean( bg_hand->rbox );
		IMC_RBOX_BGSet( bg_hand->rbox, acce->accessorie_no, HEAPID_IMAGECLIP_DRAW );

		// 放したときのエフェクト
//		imcAcceHandTakaOff( bg_hand );
	}
}


//----------------------------------------------------------------------------
/**
 *
 *	@brief	オブジェクトの登録
 *
 *	@param	hand		ハンドデータ
 *	@param	obj			登録オブジェクト
 *	@param	from		元あった場所
 *	@param	offset_x	左上からのオフセット座標
 *	@param	offset_y	左上からのオフセット座標
 *	@param	pri			表示優先順位
 *
 *	@return	none
 *
 *	form
 *		enum{
 *			IMC_ACCE_HAND_FROM_LBOX,		// 左ボックス
 * 			IMC_ACCE_HAND_FROM_RBOX,		// 右ボックス
 *		};
 *
 */
//-----------------------------------------------------------------------------
static void setAcceHandAcce( IMC_ACCE_HAND* hand, IMC_OBJLIST* obj, int from, int offset_x, int offset_y, int pri )
{
	int pos_x, pos_y;
	IMC_OBJLIST_ACCEPOKE_MatGet( obj, &pos_x, &pos_y );
	
	hand->obj		= obj;
	hand->from_x	= pos_x;
	hand->from_y	= pos_y;
	hand->from		= from;
	hand->offset_x	= offset_x;
	hand->offset_y	= offset_y;

	if( from == IMC_ACCE_HAND_FROM_LBOX ){
		// 左ボックスからきたものなら
		// 今のモードを設定
		hand->from_list	= IMC_LBOX_GetCurrentNo( hand->lbox, hand->obj->flag );	// カレントリストNo
	}else{
		// 右から来たものはデフォルトでこれ
		hand->from_list	= 0;
	}

	// ハンドプッシュＯＮ
	hand->push_flg = TRUE;

	// 優先順位を最上にする
	IMC_OBJLIST_ACCEPOKE_Pri( obj, pri );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	アクセサリハンドのアクセサリデータ部のみ初期化
 *
 *	@param	hand	アクセサリハンド構造体
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void cleanAcceHandAcce( IMC_ACCE_HAND* hand )
{
	hand->obj		= NULL;
	hand->from_x	= 0;
	hand->from_y	= 0;
	hand->from		= 0;
	hand->from_list	= 0;
}


//----------------------------------------------------------------------------
/**
 *
 *	@brief	ハンド構造タイに登録されているオブジェクトの矩形サイズを取得する
 *	
 *	@param	hand		ハンド構造体
 *	@param	top			上座標
 *	@param	bottom		下座標
 *	@param	left		左座標
 *	@param	right		右座標	
 *
 *	@return	none
 *	
 *
 */
//-----------------------------------------------------------------------------
static void imcAcceHandGetObjRect( IMC_HAND* hand, int* top, int* bottom, int* left, int* right )
{
	IMC_ACCE_HAND* acce_hand		= hand->hand_w;
	int size_x,size_y;			// オブジェクトサイズXY
	int mat_x, mat_y;			// オブジェクト座標

	IMC_OBJLIST_ACCEPOKE_SizeGet( acce_hand->obj, &size_x, &size_y );
	IMC_OBJLIST_ACCEPOKE_MatGet( acce_hand->obj, &mat_x, &mat_y );
	
	*top	= mat_y;
	*bottom	= mat_y + size_y;
	*left	= mat_x;
	*right	= mat_x + size_x;
}


//----------------------------------------------------------------------------
/**
 * ●食い込んでよいサイズを減らす		右パレット用
 *
 *	@brief	ハンド構造タイに登録されているオブジェクトの矩形サイズを取得する
 *	
 *	@param	hand		ハンド構造体
 *	@param	top			上座標
 *	@param	bottom		下座標
 *	@param	left		左座標
 *	@param	right		右座標	
 *
 *	@return	none
 *	
 *
 *
 */
//-----------------------------------------------------------------------------
static void imcAcceHandGetObjRectSubInSize( IMC_HAND* hand, int* top, int* bottom, int* left, int* right )
{
	IMC_ACCE_HAND* acce_hand		= hand->hand_w;
	IMC_OBJLIST_GetObjRectSubInSize( acce_hand->obj, top, bottom, left, right );
}


//-------------------------------------
//	
//	動作タスク系
//	
//=====================================
//----------------------------------------------------------------------------
/**
 *
 *	@brief	左ボックスへのアクセサリ返却エフェクトタスク開始関数
 *	
 *	@param	acce_hand		アクセサリハンド構造体
 *	@param	sync			何シンクで動かすか
 *	@param	targ_x			返却先座標ｘ
 *	@param	targ_y			返却先座標ｙ
 *	@param	acce_mode		アクセサリモード
 *	@param	list_no			アクセサリリスト番号
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void imcAcceHandIconLboxRetStart( IMC_ACCE_HAND* acce_hand, int sync, int targ_x, int targ_y, int acce_mode, int list_no )
{
	TCB_PTR tcb;
	IMC_ACCE_HAND_EFE_LBOX_RET* work;
	int x, y;

	tcb = PMDS_taskAdd( imcAcceHandIconLboxRetTsk, sizeof(IMC_ACCE_HAND_EFE_LBOX_RET), 0, HEAPID_IMAGECLIP_DATA );

	work = TCB_GetWork( tcb );

	work->lbox		= acce_hand->lbox;
	work->obj		= acce_hand->obj;
	work->count		= sync;
	work->targ_x	= targ_x;
	work->targ_y	= targ_y;
	work->lbox_mode	= acce_mode;
	work->list_no	= list_no;
	work->p_left_state = &acce_hand->lbox->boxData.state;
	work->p_new_push_flg = &acce_hand->push_flg;
	
	// １シンクに動かす値を取得
	IMC_OBJLIST_ACCEPOKE_MatGet( acce_hand->obj, &x, &y );
	
	work->one_x		= (work->targ_x - x) / sync;
	work->one_y		= (work->targ_y - y) / sync;

	// アクセサリをはなした
	acce_hand->push_flg = FALSE;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	左ボックスへのアクセサリ返却エフェクトタスク
 *
 *	@param	tcb		tcbポインタ
 *	@param	work	ワーク
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void imcAcceHandIconLboxRetTsk( TCB_PTR tcb, void* work )
{
	IMC_ACCE_HAND_EFE_LBOX_RET* tsk_w = work;
	int x, y;			// 座標

	// 左ボックスがフェード中はとめる
	if( *tsk_w->p_left_state == IMC_LBOX_STATE_FADE ){
		return ;
	}
	
	IMC_OBJLIST_ACCEPOKE_MatGet( tsk_w->obj, &x, &y );

	x += tsk_w->one_x;
	y += tsk_w->one_y;

	tsk_w->count--;

	// 終了チェック
	if(tsk_w->count < 0){
		IMC_OBJLIST_ACCEPOKE_Mat( tsk_w->obj, tsk_w->targ_x, tsk_w->targ_y );

		// 今の座標で左ボックスにおく
		IMC_LBOX_AddAccessorieMove(
				tsk_w->lbox,
				tsk_w->lbox_mode,
				tsk_w->list_no,
				tsk_w->obj	);
		
		
		// 表示優先順位の再設定
		IMC_LBOX_SetAccessoriePriority( tsk_w->lbox );

		// BG優先順位の設定
		// 自分が左パレットに戻っている間に
		// 新しいものを手がつかんでいたら
		// マスクチェンジを行わない
		if( *(tsk_w->p_new_push_flg) == FALSE ){
			IMC_DRAW_WndMaskNormalSet();
		}
		
		// 終了
		PMDS_taskDel( tcb );
	}else{

		// 座標設定
		IMC_OBJLIST_ACCEPOKE_Mat( tsk_w->obj, x, y );
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	何か持ったときの関数
 *
 *	@param	acce_hand	何か持ったハンド構造体
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void imcAcceHandSameThingHave( IMC_ACCE_HAND* acce_hand )
{
	if( acce_hand->obj->flag < IMC_OBJLIST_POKE ){
		
		IMC_ACCE_ObjScaleSet( acce_hand->obj->obj_data, 
				FX32_ONE + 0x200,
				FX32_ONE + 0x200);
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	放すエフェクトの関数
 *
 *	@param	acce_hand	これから放す何かを持ったハンド構造体
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void imcAcceHandTakaOff( IMC_ACCE_HAND* acce_hand )
{
	if( acce_hand->obj->flag < IMC_OBJLIST_POKE ){
		
		IMC_ACCE_ObjScaleSet( acce_hand->obj->obj_data, 
				FX32_ONE,
				FX32_ONE);
	}
}


//----------------------------------------------------------------------------
/**
 *
 *	@brief		サブウィンドウに今保持している物のメッセージを出す
 *
 *	@param	hand アクセサリハンド構造体
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void imcSubWinMsgPrint( IMC_ACCE_HAND* hand )
{
	// アクセサリ
	if( hand->obj->flag == IMC_OBJLIST_ACCE ){
		IMC_ACCESSORIE_OBJ* acce = hand->obj->obj_data;
		
		IMC_SUBWIN_SetBmpWin( hand->subwin, ARC_MSG, NARC_msg_imageclip_acce_dat, acce->accessorie_no );
		
	// BG
	}else if( hand->obj->flag == IMC_OBJLIST_BG ){
		IMC_ACCESSORIE_OBJ* acce = hand->obj->obj_data;
		
		IMC_SUBWIN_SetBmpWin( hand->subwin, ARC_MSG, NARC_msg_imageclip_bg_dat, acce->accessorie_no );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	ポケモン座標を設定する
 *
 *	@param	hand	アクセサリハンド
 *	@param	x		ｘ座標
 *	@param	y		ｙ座標
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void imcAcceHandSetPokeMatrix( IMC_HAND* hand, int x, int y )
{
	IMC_ACCE_HAND* acce_hand = hand->hand_w;
	IMC_OBJLIST_ACCEPOKE_Mat( acce_hand->obj, x, y );

	// 移動距離分動かす
	// 右ボックスのポケモンの上のアクセサリも動かす
	IMC_RBOX_PokeUpListMove( acce_hand->rbox, 
			x - acce_hand->last_x, y - acce_hand->last_y );

	acce_hand->last_x = x;
	acce_hand->last_y = y;
}
