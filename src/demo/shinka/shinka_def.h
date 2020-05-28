
#include	"system/softsprite.h"
#include	"battle/battle_common.h"
#include	"system/particle.h"
#include	"application/p_status.h"

// -----------------------------------------
//
//	□パーティクル登録用ワーク
//
// -----------------------------------------
typedef struct {
	
	int heap_id;
	
	int spa_id;
//	int	spr_id;
	
} SHINKA_PARTICLE_PARAM;


// -----------------------------------------
//
//	□パーティクル管理
//
// -----------------------------------------
typedef struct  {
	
	SHINKA_PARTICLE_PARAM	param;
	
	EMIT_PTR			emit;
	PTC_PTR				ptc;
	
} SHINKA_PARTICLE_SYS;


///<進化デモ用ワーク構造体宣言
struct shinka_work
{
	GF_BGL_INI			*bgl;
	GF_BGL_BMPWIN		*win;
	MSGDATA_MANAGER		*msg_man;
	WORDSET				*wordset;					///<戦闘メッセージ用単語バッファ
	STRBUF				*msg_buf;					///<メッセージ用に確保したワークへのポインタ
	PALETTE_FADE_PTR	pfd;						///<パレットフェードシステムワークへのポインタ
	SOFT_SPRITE_MANAGER	*ssm;
	SOFT_SPRITE			*ss[2];
	POKEPARTY			*ppt;
	POKEMON_PARAM		*pp;
	CONFIG				*config;
	SHINKA_PARTICLE_SYS	*shinka_pt;
	GF_G3DMAN			*g3Dman;
	PROC				*proc;
	PSTATUS_DATA		*psd;
	void				*work_p;
	POKE_ANM_SYS_PTR	pasp;
	ZUKAN_WORK			*zw;
	MYITEM				*my_item;
	RECORD				*record;
	POKETCH_DATA		*poketch_data;
	void				*msg_icon;
	int					heapID;
	u16					before_mons_no;
	u16					after_mons_no;
	u8					seq_no;
	u8					msg_index;
	u8					wait;
	u8					end_flag;

	int					waza_cnt;					///<技覚えテーブルのインデックス

	u16					waza_no;					///<覚える技ナンバー
	u8					waza_pos;					///<技を忘れる時のポジション
	u8					dummy;

	u8					morph_flag;
	u8					morph_speed;
	
	u8					wx1;
	u8					wy1;
	u8					wx2;
	u8					wy2;

	int					shinka_cond;
	int					shinka_status_flag;
};
