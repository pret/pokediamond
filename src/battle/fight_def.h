
//============================================================================================
/**
 * @file	fight_def.h
 * @bfief	戦闘メインプログラム
 * @author	HisashiSogabe
 * @date	05.05.24
 */
//============================================================================================

#include	"battle/battle_common.h"
#include	"poketool/poke_tool.h"
#include	"../src/poketool/poke_tool_def.h"
#include	"battle/server.h"
#include	"battle/client.h"
#include	"system/softsprite.h"
#include	"wazaeffect/we_mana.h"
#include	"system/clact_tool.h"
#include	"battle/ground.h"
#include	"battle/battle_input.h"
#include "system/numfont.h"
#include "system/msgdata.h"
#include "system/wordset.h"
#include "system/palanm.h"
#include "system/gra_tool.h"
#include "vs_demo.h"
#include "field/tvtopic_battle.h"		//TVWATCH_BATTLE_WORK
#include "battle/temoti_gauge.h"
#include "gflib/vram_transfer_manager.h"

#ifndef __FIGHT_DEF_H_
#define __FIGHT_DEF_H_

typedef struct _MYSTATUS MYSTATUS;
typedef struct _MYITEM MYITEM;
typedef struct _POKEPARTY POKEPARTY;
typedef struct _ZUKAN_WORK ZUKAN_WORK;
typedef struct _BOX_DATA BOX_DATA;
typedef struct PERAPVOICE PERAPVOICE;
typedef struct _CONFIG CONFIG;
typedef struct _POKETCH_DATA POKETCH_DATA;

///<戦闘用ワーク構造体宣言
struct battle_work
{
	GF_G3DMAN			*g3Dman;					///<3D面初期化マネージャーのポインタ
	GF_BGL_INI			*bgl;
	GF_BGL_BMPWIN		*win;
	MSGDATA_MANAGER		*fight_msg;					///<戦闘メッセージ用メッセージデータマネージャのポインタ
	MSGDATA_MANAGER		*attack_msg;				///<戦闘メッセージ用メッセージデータマネージャのポインタ（アタックメッセージ）
	WORDSET				*wordset;					///<戦闘メッセージ用単語バッファ
	STRBUF				*msg_buf;					///<メッセージ用に確保したワークへのポインタ
	TCB_PTR				update_tcb;
	TCB_PTR				pinch_tcb;					///<ピンチSEの制御タスク
	TCB_PTR				msgwinmove_tcb;				///<最初の演出用(BG1面（メッセージ面）を上にスクロールさせる）
	PALETTE_FADE_PTR	pfd;						///<パレットフェードシステムワークへのポインタ
	u32					fight_type;
	SERVER_PARAM		*server_param;
	CLIENT_PARAM		*client_param[CLIENT_MAX];
	int					client_set_max;
	MYSTATUS			*my_status[CLIENT_MAX];		///<プレーヤー情報
	MYITEM				*my_item;					///<手持ちアイテム情報
	BAG_CURSOR			*bag_cursor;				///<バッグのカーソルデータ
	ZUKAN_WORK			*zw;						///<図鑑ワーク
	BOX_DATA			*box;						///<ボックスデータ
	POKEPARTY			*poke_party[CLIENT_MAX];	///<手持ちポケモンの構造体
	PERAPVOICE			*poke_voice[CLIENT_MAX];	///<ポケモンの鳴き声データ
	SOFT_SPRITE_MANAGER	*soft_sprite;
	WE_SYS_PTR			wsp;
	CATS_SYS_PTR		csp;
	CATS_RES_PTR		crp;
	POKETCH_DATA		*poketch_data;				///<ポケッチデータ
	TVWATCH_BATTLE_WORK * TVWatchBattleWork;		///<テレビ：捕獲番組用
	u16					trainer_id[CLIENT_MAX];
	u8					trainer_sex[CLIENT_MAX];
	TRAINER_DATA		trainer_data[CLIENT_MAX];	///<トレーナーデータ
	GROUND_WORK			ground[GROUND_MAX];			///<地面ワーク(自機側 + 敵側)
	BI_PARAM_PTR		bip;						///<戦闘入力画面システムワークへのポインタ
	TEMOTIGAUGE_PTR		tg[TEMOTIGAUGE_MAX];		///<手持ちゲージワークへのポインタ
	NUMFONT				*numfont_hp;				///<8x8フォント(HP用)
	NUMFONT				*numfont_lv;				///<8x8フォント(レベル用)
	void				*msg_icon;					///<メッセージウインドウのDSアイコン用ポインタ
	CONFIG				*config;					///<ゲームコンフィグ
	FRIEND_LIST			*friendlist;				///<ともだちグループデータ
	void				*time_icon;					///<通信待機中の時計アイコンタスク
	

	VS_DEMO_DATA		*vdd;						///<対戦開始前デモ用ワークへのポインタ
	POKE_ANM_SYS_PTR	pasp;						///<ポケモンプログラムアニメシステムワークへのポインタ
	NNSG2dCellTransferState	*cell_trans;			///<セル転送マネージャ
	

	EXCHR_PARAM			exchr_param[CLIENT_MAX];	///<技エフェクト用ポケモンキャラ展開パラメータ

	BATTLE_TOWER_RECORD	btr;						///<バトルタワー成績用ワーク

	RECORD				*record;					///<カウントアップ用ワーク

	u8					*bg_area;					///<背景グラフィック退避領域（キャラ）
	u16					*pal_area;					///<背景グラフィック退避領域（パレット）

	u8					sio_send_buffer[BATTLE_SIO_BUF_SIZE];	///<通信送信バッファ
	u8					sio_recv_buffer[BATTLE_SIO_BUF_SIZE];	///<通信受信バッファ

	u16					push_bg_palette[0x10*7];	///<BGパレット退避領域
	u16					push_obj_palette[0x10*7];	///<OBJパレット退避領域

	u16					sio_send_read;				///<通信送信バッファ読み込み位置
	u16					sio_send_write;				///<通信送信バッファ書き込み位置

	u16					sio_send_over;				///<通信送信バッファ書き込み時にオーバーしたときのワーク
	u16					sio_recv_read;				///<通信受信バッファ読み込み位置

	u16					sio_recv_write;				///<通信受信バッファ書き込み位置
	u16					sio_recv_over;				///<通信受信バッファ書き込み時にオーバーしたときのワーク

	u8					*tcb_sio_send_seq_no;		///<通信送信TCBのシーケンスナンバーへのポインタ
	u8					*tcb_sio_recv_seq_no;		///<通信受信TCBのシーケンスナンバーへのポインタ

	u8					server_flag;				///<サーバが起動しているかフラグ
	u8					proc_mode;					///<戦闘システムの動作モード
	u8					fight_end_flag;				///<戦闘終了フラグ
	u8					bld_init_req		:1;		///<ブレンド設定初期化要求フラグ
	u8					vram_init_req		:1;		///<VRAM設定初期化要求フラグ
	u8					bl_vram_init_req	:1;		///<VRAM設定初期化要求フラグ（バッグ＆リスト画面）
	u8					pinch_se_flag		:2;		///<ピンチSEフラグ
	u8					pinch_se_wait		:3;		///<ピンチSEウエイト

	int					ground_id;					///<地形ID
	int					bg_id;						///<背景ID
	int					place_id;					///<地域名ID
	u32					battle_status_flag;			///<戦闘効果フラグ
	int					time_zone;					///<時間帯

	int					safari_ball;				///<サファリボールの数

	u8					appear_flag[CLIENT_MAX];	///<繰り出したポケモンのSelMonsNoをビットで格納

	u32					regulation_flag;			///<レギュレーションフラグ

	u8					win_lose_flag;				///<勝敗フラグ
	u8					demo_seq_no;				///<捕獲デモ用シーケンスナンバー
	u16					ball_count;					///<ボールを投げた回数

	int					shinka_place_mode;			///<場所進化情報（SHINKA_PLACE～）	
	int					contest_see_flag;			///<コンテストを見たかどうかのフラグ
	int					weather;					///<フィールド天候
	int					mizuki_flag;				///<ミズキにあったかどうかのフラグ
	u32					seed_temp;					///<乱数の種の退避ワーク
	int					bg1_scroll;					///<BG1Yスクロール用ワーク
	int					get_pokemon_client;			///<捕獲したポケモンのClientNo

	int					command_select_flag;		///<コマンドセレクトでボタンのスライドインの終了時で落とすフラグ

	u8					no_reshuffle_client;		///<入れ替えできないClientNoをビットで管理（通信用）
	u8					dummy[3];
};

#endif __FIGHT_DEF_H_
