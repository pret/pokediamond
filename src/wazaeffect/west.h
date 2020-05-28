//==============================================================================
/**
 * @file	west.h
 * @brief	技エフェクトマクロ定義
 * @author	goto
 * @date	2005.07.12(火)
 *
 * ここに色々な解説等を書いてもよい
 *
 */
//==============================================================================

// サポート関数用 .h

	.include	"west_sp_def.h"
	.include	"../data/sound/sound_data.sadl"
	.include	"wp_num.h"
	.include	"we_def.h"
	.include	"wpcb_def.h"
	.include	"effectdata/we_list.h"
	
	.include	"effectclact/wechar_def.h"
	.include	"effectclact/wepltt_def.h"
	.include	"effectclact/wecell_def.h"
	.include	"effectclact/wecellanm_def.h"
	.include	"effectdata/waza_particle_def.h"
	.include	"pt_debug/debug_particle.h"
	.include	"../../include/system/snd_def.h"
//	.include	"battle/battle_tcb_pri.h"

#define	CATS_NONE_ID	(0xffffffff)

//技SEのパン定義 "system/snd_tool.h"が開けない
//#define WAZA_SE_PAN_L			(-128)
//#define WAZA_SE_PAN_N			(0)
//#define WAZA_SE_PAN_R			(127)
//#define WAZA_SE_PAN_ADD		(+8)//(+2)
#define WAZA_SE_PAN_ADD			(+4)//(+2)
#define WAZA_SE_PAN_WAIT		(2)

#define WAZA_SE_PAN_AT			(WAZA_SE_PAN_L)
#define WAZA_SE_PAN_NM			(WAZA_SE_PAN_N)
#define WAZA_SE_PAN_DF			(WAZA_SE_PAN_R)

#define WAZA_EFF_SE1	(SEQ_SE_DP_BASI)	///< hit


// =============================================================================
//
//
//	■技エフェクトマクロ定義
//
//
// =============================================================================
	.macro	INIT_CMD
		DEF_CMD_COUNT	=	0;
	.endm

	.macro	DEF_CMD	symname
		\symname		= DEF_CMD_COUNT
		DEF_CMD_COUNT	= (DEF_CMD_COUNT + 1)
	.endm
	
	INIT_CMD
	DEF_CMD		WEST_WAIT
	DEF_CMD		WEST_WAIT_FLAG
	DEF_CMD		WEST_LOOP_LABEL
	DEF_CMD		WEST_LOOP
	DEF_CMD		WEST_SEQEND
	DEF_CMD		WEST_SE
	DEF_CMD		WEST_POKEBG
	DEF_CMD		WEST_POKEBG_RESET
	DEF_CMD		WEST_BLDALPHA_SET
	DEF_CMD		WEST_BLDALPHA_RESET
	DEF_CMD		WEST_SEQ_CALL
	DEF_CMD		WEST_END_CALL
	DEF_CMD		WEST_WORK_SET
	DEF_CMD		WEST_TURN_CHK
	DEF_CMD		WEST_TURN_JP
	DEF_CMD		WEST_SEQ_JP
	DEF_CMD		WEST_HAIKEI_CHG
	DEF_CMD		WEST_HAIKEI_PARA_CHG
	DEF_CMD		WEST_HAIKEI_RECOVER
	DEF_CMD		WEST_HAIKEI_HALF_WAIT
	DEF_CMD		WEST_HAIKEI_CHG_WAIT
	DEF_CMD		WEST_HAIKEI_SET
	DEF_CMD		WEST_SEPLAY_PAN
	DEF_CMD		WEST_SEPAN
	DEF_CMD		WEST_SEPAN_FLOW
	DEF_CMD		WEST_SE_REPEAT
	DEF_CMD		WEST_SE_WAITPLAY
	DEF_CMD		WEST_BLDCNT_SET
	DEF_CMD		WEST_SE_TASK
	DEF_CMD		WEST_SEWAIT_FLAG
	DEF_CMD		WEST_WORKCHK_JP
	DEF_CMD		WEST_POKEBG_DROP
	DEF_CMD		WEST_POKEBG_DROP_RESET
	DEF_CMD		WEST_CONTEST_CHK_JP
	DEF_CMD		WEST_HAIKEI_CHKCHG
	DEF_CMD		WEST_SEPAN_FLOWFIX
	DEF_CMD		WEST_SEPAN_FLOW_AF
	DEF_CMD		WEST_BGPRI_GAPSET
	DEF_CMD		WEST_BGPRI_GAPSET2
	DEF_CMD		WEST_BGPRI_GAPSET3
	DEF_CMD		WEST_POKE_BANISH_ON
	DEF_CMD		WEST_POKE_BANISH_OFF
	DEF_CMD		WEST_PARTY_ATTACK_BGOFF
	DEF_CMD		WEST_PARTY_ATTACK_BGEND
	DEF_CMD		WEST_SE_STOP
	
	// ----- 新規 -----
	DEF_CMD		WEST_FUNC_CALL
	DEF_CMD		WEST_ADD_PARTICLE
	DEF_CMD		WEST_ADD_PARTICLE_EMIT_SET
	DEF_CMD		WEST_ADD_PARTICLE_SEP
	DEF_CMD		WEST_ADD_PARTICLE_PTAT
	DEF_CMD		WEST_WAIT_PARTICLE
	DEF_CMD		WEST_LOAD_PARTICLE
	DEF_CMD		WEST_LOAD_PARTICLE_EX
	DEF_CMD		WEST_EXIT_PARTICLE
	DEF_CMD		WEST_OLDACT_FUNC_CALL
	DEF_CMD		WEST_EX_DATA
	DEF_CMD		WEST_POKEOAM_RES_INIT
	DEF_CMD		WEST_POKEOAM_RES_LOAD
	DEF_CMD		WEST_POKEOAM_DROP
	DEF_CMD		WEST_POKEOAM_RES_FREE
	DEF_CMD		WEST_POKEOAM_DROP_RESET
	DEF_CMD		WEST_POKEOAM_AUTO_STOP
	DEF_CMD		WEST_CAMERA_CHG
	DEF_CMD		WEST_CAMERA_REVERCE
	DEF_CMD		WEST_SIDE_JP
	DEF_CMD		WEST_VOICE_PLAY
	DEF_CMD		WEST_VOICE_WAIT_STOP
	DEF_CMD		WEST_WORK_CLEAR
	DEF_CMD		WEST_HENSIN_ON
	DEF_CMD		WEST_HENSIN_ON_RC
	DEF_CMD		WEST_TENKI_JP
	DEF_CMD		WEST_CONTEST_JP
	DEF_CMD		WEST_PTAT_JP
	
	// ----- CATS用 ------
	DEF_CMD		WEST_CATS_RES_INIT
	DEF_CMD		WEST_CATS_CAHR_RES_LOAD
	DEF_CMD		WEST_CATS_PLTT_RES_LOAD
	DEF_CMD		WEST_CATS_CELL_RES_LOAD
	DEF_CMD		WEST_CATS_CELLANM_RES_LOAD
	DEF_CMD		WEST_CATS_ACT_ADD
	DEF_CMD		WEST_CATS_ACT_ADD_EZ
	DEF_CMD		WEST_CATS_RES_FREE
	DEF_CMD		WEST_POKE_OAM_ENABLE
	
	DEF_CMD		WEST_PT_DROP
	DEF_CMD		WEST_PT_DROP_RESET
	
	// ----- デバッグ用はココから定義 -----
	DEF_CMD		WEST_KEY_WAIT

// -----------------------------------------
//			
//	キャラセットマクロ
//
//------------------------------------------
	.macro	CHAR_SET	chrID
	.long	WEST_CHAR_SET			
	.long	\chrID
	.endm

// -----------------------------------------
//
//	キャラ削除マクロ
//
// -----------------------------------------
	.macro	CHAR_DEL	chrID
	.long	WEST_CHAR_DEL			
	.long	\chrID
	.endm
	
// -----------------------------------------
//
//	アクター追加マクロ
//
// -----------------------------------------
	.macro	ADD_ACTOR	adrs,pri,cnt,p0,p1,p2,p3,p4,p5,p6,p7
	.long	WEST_ADD_ACTOR			
	.long	\adrs
	.long	\pri
	.long	\cnt
.if \cnt>0
	.long	\p0
.endif
.if	\cnt>1
	.long	\p1
.endif
.if	\cnt>2
	.long	\p2
.endif
.if	\cnt>3
	.long	\p3
.endif
.if	\cnt>4
	.long	\p4
.endif
.if	\cnt>5
	.long	\p5
.endif
.if	\cnt>6
	.long	\p6
.endif
.if	\cnt>7
	.long	\p7
.endif
	.endm

// -----------------------------------------
//
//	タスク登録マクロ
//
// -----------------------------------------
	.macro	ADD_TASK	adrs,pri,cnt,p0,p1,p2,p3,p4,p5,p6,p7
	.long	WEST_ADD_TASK			
	.long	\adrs
	.long	\pri
	.long	\cnt
.if \cnt>0
	.long	\p0
.endif
.if	\cnt>1
	.long	\p1
.endif
.if	\cnt>2
	.long	\p2
.endif
.if	\cnt>3
	.long	\p3
.endif
.if	\cnt>4
	.long	\p4
.endif
.if	\cnt>5
	.long	\p5
.endif
.if	\cnt>6
	.long	\p6
.endif
.if	\cnt>7
	.long	\p7
.endif
	.endm

// -----------------------------------------
//
//	待ちマクロ
//
// -----------------------------------------
	.macro	WAIT		time
	.long	WEST_WAIT				
	.long	\time
	.endm

// -----------------------------------------
//
//	待ちマクロ フラグ
//
// -----------------------------------------
	.macro	WAIT_FLAG
	.long	WEST_WAIT_FLAG
	.endm

// -----------------------------------------
//
//	ループラベルマクロ
//
// -----------------------------------------
	.macro	LOOP_LABEL	cnt
	.long	WEST_LOOP_LABEL			
	.long	\cnt
	.endm

// -----------------------------------------
//
//	ループマクロ
//
// -----------------------------------------
	.macro	LOOP
	.long	WEST_LOOP				
	.endm

// -----------------------------------------
//
//	シーケンス終了マクロ
//
// -----------------------------------------
	.macro	SEQEND
	.long	WEST_SEQEND				
	.endm

// -----------------------------------------
//
//	SE再生マクロ
//
// -----------------------------------------
	.macro	SE		seID
	.long	WEST_SE					
	.long	\seID
	.endm

// -----------------------------------------
//
//	ポケモン⇒BGマクロ
//
// -----------------------------------------
	.macro	POKEBG	flag
	.long	WEST_POKEBG
	.long	\flag
	.endm

// -----------------------------------------
//
//	ポケモン⇒BGリセットマクロ
//
// -----------------------------------------
	.macro	POKEBG_RESET	flag
	.long	WEST_POKEBG_RESET
	.long	\flag
	.endm

// -----------------------------------------
//
//	α値セットマクロ
//
// -----------------------------------------
	.macro	BLDALPHA_SET	eva,evb
	.long	WEST_BLDALPHA_SET
	.long	\eva
	.long	\evb
	.endm

// -----------------------------------------
//
//	α値リセットマクロ
//
// -----------------------------------------
	.macro	BLDALPHA_RESET
	.long	WEST_BLDALPHA_RESET
	.endm

// -----------------------------------------
//
//	シーケンス呼び出しマクロ
//
// -----------------------------------------
/*
	元のシーケンスジャンプマクロ
	.macro	SEQ_CALL	adrs
	.long	WEST_SEQ_CALL
	.long	\adrs
	.endm
*/	
	.macro	SEQ_CALL	adrs
	.long	WEST_SEQ_CALL
	.long	(\adrs-.)/4
	.endm

// -----------------------------------------
//
//	シーケンス復帰マクロ
//
// -----------------------------------------
	.macro	END_CALL
	.long	WEST_END_CALL
	.endm

// -----------------------------------------
//
//	ワークの設定マクロ
//
// -----------------------------------------
	.macro	WORK_SET	soeji,work
	.long	WEST_WORK_SET
	.long	\soeji
	.long	\work
	.endm

//	ワークの初期化
	.macro	WORK_CLEAR
	.long	WEST_WORK_CLEAR
	.endm

// へんしん
	.macro	HENSIN_ON			type
	.long	WEST_HENSIN_ON
	.long	\type
	.endm

	.macro	HENSIN_ON_RC		type
	.long	WEST_HENSIN_ON_RC
	.long	\type
	.endm
	
// -----------------------------------------
//
//	ターンチェックマクロ
//
// -----------------------------------------
	.macro	TURN_CHK	adrs1,adrs2
	.long	WEST_TURN_CHK
	.long	(\adrs1-.)/4
	.long	(\adrs2-.)/4
	.endm

// -----------------------------------------
//
//	ターンチェックジャンプマクロ
//
// -----------------------------------------
	.macro	TURN_JP		turn,adrs
	.long	WEST_TURN_JP			
	.long	\turn
	.long	(\adrs-.)/4
	.endm

// -----------------------------------------
//
//	シーケンス切り替えマクロ
//
// -----------------------------------------
	.macro	SEQ_JP	adrs
	.long	WEST_SEQ_JP
	.long	(\adrs-.)/4
	.endm

// -----------------------------------------
//
//	サイドでジャンプ先変更
//
//	type == 0 攻撃ポケモン
//	type != 0 対象ポケモン
//
// -----------------------------------------
	.macro	SIDE_JP			type, adrs1, adrs2
	.long	WEST_SIDE_JP
	.long	\type
	.long	(\adrs1-.)/4
	.long	(\adrs2-.)/4
	.endm

// -----------------------------------------
//
//	天気で変更
//
// -----------------------------------------
	.macro	TENKI_JP		type1,type2,type3,type4,type5,
	.long	WEST_TENKI_JP
	.long	(\type1-.)/4
	.long	(\type2-.)/4
	.long	(\type3-.)/4
	.long	(\type4-.)/4
	.long	(\type5-.)/4
	.endm


// -----------------------------------------
//
//	コンテスト専用ジャンプ
//
// -----------------------------------------
	.macro	CONTEST_JP		adrs
	.long	WEST_CONTEST_JP
	.long	(\adrs-.)/4
	.endm

	
// -----------------------------------------
//
//	パーティアタック専用ジャンプ
//
// -----------------------------------------
	.macro	PTAT_JP		adrs
	.long	WEST_PTAT_JP
	.long	(\adrs-.)/4
	.endm


// -----------------------------------------
//
//	背景切り替えマクロ
//
// -----------------------------------------
	.macro	HAIKEI_CHG	map_id, ch_mode
	.long	WEST_HAIKEI_CHG
	.long	\map_id
	.long	\ch_mode
	.endm

// -----------------------------------------
//
//	背景切り替え値変更マクロ
//
// -----------------------------------------
	.macro	HAIKEI_PARA_CHG	para_id, para
	.long	WEST_HAIKEI_PARA_CHG
	.long	\para_id
	.long	\para
	.endm

// -----------------------------------------
//
//	背景復帰マクロ
//
// -----------------------------------------
	.macro	HAIKEI_RECOVER			map_id, ch_mode
	.long	WEST_HAIKEI_RECOVER
	.long	\map_id
	.long	\ch_mode
	.endm

// -----------------------------------------
//
//	背景待ちマクロ
//
// -----------------------------------------
	.macro	HAIKEI_HALF_WAIT
	.long	WEST_HAIKEI_HALF_WAIT
	.endm

// -----------------------------------------
//
//	背景切り替え待ちマクロ
//
// -----------------------------------------
	.macro	HAIKEI_CHG_WAIT
	.long	WEST_HAIKEI_CHG_WAIT
	.endm

// -----------------------------------------
//
//	背景セットマクロ
//
// -----------------------------------------
	.macro	HAIKEI_SET	map_id
	.long	WEST_HAIKEI_SET
	.long	\map_id
	.endm

// -----------------------------------------
//
//	SEパン設定再生マクロ
//
// -----------------------------------------
	.macro	SEPLAY_PAN	seID,pan
	.long	WEST_SEPLAY_PAN					
	.long	\seID
	.long	\pan
	.endm

	.macro	SE_L	seID
	SEPLAY_PAN	\seID,WAZA_SE_PAN_AT
	.endm

	.macro	SE_R	seID
	SEPLAY_PAN	\seID,WAZA_SE_PAN_DF
	.endm

	.macro	SE_C	seID
	SEPLAY_PAN	\seID,WAZA_SE_PAN_NM
	.endm

// -----------------------------------------
//
//	SEパン設定マクロ
//
// -----------------------------------------
	.macro	SEPAN	pan
	.long	WEST_SEPAN					
	.long	\pan
	.endm

// -----------------------------------------
//
//	SEパン移動マクロ
//
// -----------------------------------------
	.macro	SEPAN_FLOW	seID,start_pan,end_pan,add_pan,wait
	.long	WEST_SEPAN_FLOW					
	.long	\seID
	.long	\start_pan
	.long	\end_pan
	.long	\add_pan
	.long	\wait
	.endm

	.macro	SE_FLOW_LR	seID
	SEPAN_FLOW	\seID, WAZA_SE_PAN_AT, WAZA_SE_PAN_DF, WAZA_SE_PAN_ADD, WAZA_SE_PAN_WAIT
	.endm

	.macro	SE_FLOW_RL	seID
	SEPAN_FLOW	\seID, WAZA_SE_PAN_DF, WAZA_SE_PAN_AT, WAZA_SE_PAN_ADD, WAZA_SE_PAN_WAIT
	.endm
	
	.macro	SE_FLOW_LR_H	seID
	SEPAN_FLOW	\seID, WAZA_SE_PAN_AT, WAZA_SE_PAN_DF, WAZA_SE_PAN_ADD*2, WAZA_SE_PAN_WAIT
	.endm

	.macro	SE_FLOW_RL_H	seID
	SEPAN_FLOW	\seID, WAZA_SE_PAN_DF, WAZA_SE_PAN_AT, WAZA_SE_PAN_ADD*2, WAZA_SE_PAN_WAIT
	.endm
	
// -----------------------------------------
//
//	SE繰り返しマクロ
//
// -----------------------------------------
	.macro	SE_REPEAT	seID,pan,wait,repeat
	.long	WEST_SE_REPEAT					
	.long	\seID
	.long	\pan
	.long	\wait
	.long	\repeat
	.endm

	.macro	SE_REPEAT_L	seID,wait,repeat
	SE_REPEAT	\seID, WAZA_SE_PAN_AT, \wait, \repeat
	.endm

	.macro	SE_REPEAT_R	seID,wait,repeat
	SE_REPEAT	\seID, WAZA_SE_PAN_DF, \wait, \repeat
	.endm

	.macro	SE_REPEAT_C	seID,wait,repeat
	SE_REPEAT	\seID, WAZA_SE_PAN_NM, \wait, \repeat
	.endm

// -----------------------------------------
//
//	SE待ち再生マクロ
//
// -----------------------------------------
	.macro	SE_WAITPLAY	seID,pan,wait
	.long	WEST_SE_WAITPLAY					
	.long	\seID
	.long	\pan
	.long	\wait
	.endm

	.macro	SE_WAITPLAY_L	seID, wait
	SE_WAITPLAY	\seID, WAZA_SE_PAN_AT, \wait
	.endm

	.macro	SE_WAITPLAY_R	seID, wait
	SE_WAITPLAY	\seID, WAZA_SE_PAN_DF, \wait
	.endm

	.macro	SE_WAITPLAY_C	seID, wait
	SE_WAITPLAY	\seID, WAZA_SE_PAN_NM, \wait
	.endm

//	泣き声再生
	.macro		VOICE_PLAY			type, pan, vol,
	.long		WEST_VOICE_PLAY
	.long		\type
	.long		\pan
	.long		\vol
	.endm

//	泣き声待ち＋停止
	.macro		VOICE_WAIT_STOP		frame
	.long		WEST_VOICE_WAIT_STOP
	.long		\frame
	.endm

// -----------------------------------------
//
//	ブレンドコントロールセット
//
// -----------------------------------------
	.macro	BLDCNT_SET	work
	.long	WEST_BLDCNT_SET
	.long	\work
	.endm

// -----------------------------------------
//
//	SEタスク登録マクロ
//
// -----------------------------------------
	.macro	SE_TASK		adrs,cnt,p0,p1,p2,p3,p4,p5,p6,p7
	.long	WEST_SE_TASK			
	.long	\adrs
	.long	\cnt
.if \cnt>0
	.long	\p0
.endif
.if	\cnt>1
	.long	\p1
.endif
.if	\cnt>2
	.long	\p2
.endif
.if	\cnt>3
	.long	\p3
.endif
.if	\cnt>4
	.long	\p4
.endif
.if	\cnt>5
	.long	\p5
.endif
.if	\cnt>6
	.long	\p6
.endif
.if	\cnt>7
	.long	\p7
.endif
	.endm

// -----------------------------------------
//
//	SE待ちマクロ
//
// -----------------------------------------
	.macro	SE_WAIT_FLAG
	.long	WEST_SEWAIT_FLAG			
	.endm

// -----------------------------------------
//
//	ワーク比較ジャンプマクロ
//
// -----------------------------------------
	.macro	WORKCHK_JP		soeji,num,adrs
	.long	WEST_WORKCHK_JP			
	.long	\soeji
	.long	\num
	.long	\adrs
	.endm

// -----------------------------------------
//
//	ポケモンBGドロップマクロ
//
// -----------------------------------------
	.macro	POKEBG_DROP			flag, auto_move
	.long	WEST_POKEBG_DROP
	.long	\flag
	.long	\auto_move
	.endm


// -----------------------------------------
//
//	ポケモンOAM用のリソース初期化マクロ
//
// -----------------------------------------
	.macro	POKEOAM_RES_INIT
	.long	WEST_POKEOAM_RES_INIT
	.endm


// -----------------------------------------
//
//	ポケモンOAMリソース読み込み
//
// -----------------------------------------
	.macro	POKEOAM_RES_LOAD		use_no
	.long	WEST_POKEOAM_RES_LOAD
	.long	\use_no
	.endm


// -----------------------------------------
//
//	ポケモンOAMドロップマクロ
//
// -----------------------------------------
	.macro	POKEOAM_DROP			flag, auto_move, cap_id, use_no
	.long	WEST_POKEOAM_DROP
	.long	\flag
	.long	\auto_move
	.long	\cap_id
	.long	\use_no
	.endm

// -----------------------------------------
//
//	ポケモンリソース解放
//
// -----------------------------------------
	.macro	POKEOAM_RES_FREE
	.long	WEST_POKEOAM_RES_FREE
	.endm

// -----------------------------------------
//
//	ポケモンOAM解放
//
// -----------------------------------------
	.macro	POKEOAM_DROP_RESET		cap_id
	.long	WEST_POKEOAM_DROP_RESET
	.long	\cap_id
	.endm

// -----------------------------------------
//
//	自動追尾停止
//
// -----------------------------------------
	.macro	POKEOAM_AUTO_STOP		move_cap_id
	.long	WEST_POKEOAM_AUTO_STOP
	.long	\move_cap_id
	.endm

// -----------------------------------------
//
//	カメラの変更
//
// -----------------------------------------
	.macro	CAMERA_CHG		no, camera_mode
	.long	WEST_CAMERA_CHG
	.long	\no
	.long	\camera_mode
	.endm

// -----------------------------------------
//
//	カメラの上下のみ反転　0 = 通常 1 = 反転
//
// -----------------------------------------
	.macro	CAMERA_REVERCE	no, flag
	.long	WEST_CAMERA_REVERCE
	.long	\no
	.long	\flag
	.endm
	

// -----------------------------------------
//
//	ポケモンBGドロップリセットマクロ
//
// -----------------------------------------
	.macro	POKEBG_DROP_RESET	flag
	.long	WEST_POKEBG_DROP_RESET
	.long	\flag
	.endm

// -----------------------------------------
//
//	コンテストチェックマクロ
//
// -----------------------------------------
	.macro	CONTEST_CHK_JP	adrs
	.long	WEST_CONTEST_CHK_JP
	.long	\adrs
	.endm

// -----------------------------------------
//
//	背景チェック切り替えマクロ
//
// -----------------------------------------
	.macro	HAIKEI_CHKCHG	mine_haikei,enemy_haikei,contest_haikei
	.long	WEST_HAIKEI_CHKCHG
	.long	\mine_haikei
	.long	\enemy_haikei
	.long	\contest_haikei
	.endm

// -----------------------------------------
//
//	SEパン移動マクロ
//
// -----------------------------------------
	.macro	SEPAN_FLOWFIX	seID,start_pan,end_pan,add_pan,wait
	.long	WEST_SEPAN_FLOWFIX					
	.long	\seID
	.long	\start_pan
	.long	\end_pan
	.long	\add_pan
	.long	\wait
	.endm

// -----------------------------------------
//
//	SEパン移動マクロ
//
// -----------------------------------------
	.macro	SEPAN_FLOW_AF	seID,start_pan,end_pan,add_pan,wait
	.long	WEST_SEPAN_FLOW_AF					
	.long	\seID
	.long	\start_pan
	.long	\end_pan
	.long	\add_pan
	.long	\wait
	.endm

// -----------------------------------------
//
//	BGプライオリティーリセットマクロ
//
// -----------------------------------------
	.macro	BGPRI_GAPSET		which
	.long	WEST_BGPRI_GAPSET
	.long	\which
	.endm

// -----------------------------------------
//
//	BG2セットマクロ
//
// -----------------------------------------
	.macro	BGPRI_GAPSET2
	.long	WEST_BGPRI_GAPSET2
	.endm

// -----------------------------------------
//
//	BG3セットマクロ
//
// -----------------------------------------
	.macro	BGPRI_GAPSET3		which
	.long	WEST_BGPRI_GAPSET3
	.long	\which
	.endm

// -----------------------------------------
//
//	ポケモン非表示マクロ
//
// -----------------------------------------
	.macro	POKE_BANISH_ON		client
	.long	WEST_POKE_BANISH_ON
	.long	\client
	.endm

// -----------------------------------------
//
//	ポケモン表示マクロ
//
// -----------------------------------------
	.macro	POKE_BANISH_OFF		client
	.long	WEST_POKE_BANISH_OFF
	.long	\client
	.endm

// -----------------------------------------
//
//	BGOFFマクロ
//
// -----------------------------------------
	.macro	PARTY_ATTACK_BGOFF		which
	.long	WEST_PARTY_ATTACK_BGOFF
	.long	\which
	.endm

// -----------------------------------------
//
//	BG終了マクロ
//
// -----------------------------------------
	.macro	PARTY_ATTACK_BGEND		which
	.long	WEST_PARTY_ATTACK_BGEND
	.long	\which
	.endm

// -----------------------------------------
//
//	SE停止マクロ
//
// -----------------------------------------
	.macro	SE_STOP seID
	.long	WEST_SE_STOP			
	.long	\seID
	.endm

// -----------------------------------------
//
//	関数呼び出しマクロ
//
// -----------------------------------------
	.macro	FUNC_CALL		adrs, cnt, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9
	.long	WEST_FUNC_CALL
	.long	\adrs
	.long	\cnt
.if \cnt>0
	.long	\p0
.endif
.if	\cnt>1
	.long	\p1
.endif
.if	\cnt>2
	.long	\p2
.endif
.if	\cnt>3
	.long	\p3
.endif
.if	\cnt>4
	.long	\p4
.endif
.if	\cnt>5
	.long	\p5
.endif
.if	\cnt>6
	.long	\p6
.endif
.if	\cnt>7
	.long	\p7
.endif
.if	\cnt>8
	.long	\p8
.endif
.if	\cnt>9
	.long	\p9
.endif
	.endm

// -----------------------------------------
//
//	パーティクルの追加
//
// -----------------------------------------
	.macro	ADD_PARTICLE		ptc_no, data_no, call_back
	.long	WEST_ADD_PARTICLE
	.long	\ptc_no
	.long	\data_no
	.long	\call_back
	.endm

	.macro	ADD_PARTICLE_EMIT_SET	ptc_no, emit_no, data_no, call_back
	.long	WEST_ADD_PARTICLE_EMIT_SET
	.long	\ptc_no
	.long	\emit_no
	.long	\data_no
	.long	\call_back
	.endm
	
	.macro	ADD_PARTICLE_SEP	ptc_no, data1, data2, data3, data4, data5, data6, call_back
	.long	WEST_ADD_PARTICLE_SEP
	.long	\ptc_no
	.long	\data1
	.long	\data2
	.long	\data3
	.long	\data4
	.long	\data5
	.long	\data6
	.long	\call_back
	.endm
	
	.macro	ADD_PARTICLE_PTAT	ptc_no, data1, data2, data3, data4, call_back
	.long	WEST_ADD_PARTICLE_PTAT
	.long	\ptc_no
	.long	\data1
	.long	\data2
	.long	\data3
	.long	\data4
	.long	\call_back
	.endm
	
// -----------------------------------------
//
//	パーティクルの終了待ち
//
// -----------------------------------------
	.macro	WAIT_PARTICLE
	.long	WEST_WAIT_PARTICLE
	.endm

// -----------------------------------------
//
//	パーティクルのロード
//
// -----------------------------------------
	.macro	LOAD_PARTICLE		ptc_no, data_no
	.long	WEST_LOAD_PARTICLE
	.long	\ptc_no
	.long	\data_no
	.endm

	.macro	LOAD_PARTICLE_EX	ptc_no, arc_no, data_no
	.long	WEST_LOAD_PARTICLE_EX
	.long	\ptc_no
	.long	\arc_no
	.long	\data_no
	.endm

// -----------------------------------------
//
//	パーティクルの破棄
//
// -----------------------------------------
	.macro	EXIT_PARTICLE		ptc_no,
	.long	WEST_EXIT_PARTICLE
	.long	\ptc_no
	.endm

// -----------------------------------------
//
//	CLACTヘッダー登録マクロ
//
// -----------------------------------------
	.macro	CLACT_HEADER_LOAD		list_id, ah_no, add_num
	.long	WEST_CLACT_HEADER_LOAD
	.long	\list_id
	.long	\ah_no
	.long	\add_num
	.endm

// -----------------------------------------
//
//	CLACTヘッダー削除マクロ
//
// -----------------------------------------
	.macro	CLACT_HEADER_DELETE		ah_no
	.long	WEST_CLACT_HEADER_DELETE
	.long	\ah_no
	.endm

// -----------------------------------------
//
//	CLACT用関数呼び出しマクロ
//
// -----------------------------------------
	.macro	CLACT_FUNC_CALL			func_id, ah_no, cnt, p0, p1, p2, p3, p4, p5, p6, p7,
	.long	WEST_CLACT_FUNC_CALL
	.long	\func_id
	.long	\ah_no
	.long	\cnt
.if \cnt>0
	.long	\p0
.endif
.if	\cnt>1
	.long	\p1
.endif
.if	\cnt>2
	.long	\p2
.endif
.if	\cnt>3
	.long	\p3
.endif
.if	\cnt>4
	.long	\p4
.endif
.if	\cnt>5
	.long	\p5
.endif
.if	\cnt>6
	.long	\p6
.endif
.if	\cnt>7
	.long	\p7
.endif
	.endm

// -----------------------------------------
//
//	OLDACT用関数呼び出しマクロ
//
// -----------------------------------------
	.macro	OLDACT_FUNC_CALL		func_id, ah_no, soft_pri, cnt, p0, p1, p2, p3, p4, p5, p6, p7
	.long	WEST_CLACT_FUNC_CALL
	.long	\func_id
	.long	\ah_no
	.long	\soft_pri
	.long	\cnt
.if \cnt>0
	.long	\p0
.endif
.if	\cnt>1
	.long	\p1
.endif
.if	\cnt>2
	.long	\p2
.endif
.if	\cnt>3
	.long	\p3
.endif
.if	\cnt>4
	.long	\p4
.endif
.if	\cnt>5
	.long	\p5
.endif
.if	\cnt>6
	.long	\p6
.endif
.if	\cnt>7
	.long	\p7
.endif
	.endm

// -----------------------------------------
//
//	データ列定義：EX_DATAマクロ
//
// -----------------------------------------
	.macro	EX_DATA			cnt, p0, p1, p2, p3, p4, p5, p6, p7,
	.long	WEST_EX_DATA
	.long	\cnt
.if \cnt>0
	.long	\p0
.endif
.if	\cnt>1
	.long	\p1
.endif
.if	\cnt>2
	.long	\p2
.endif
.if	\cnt>3
	.long	\p3
.endif
.if	\cnt>4
	.long	\p4
.endif
.if	\cnt>5
	.long	\p5
.endif
.if	\cnt>6
	.long	\p6
.endif
.if	\cnt>7
	.long	\p7
.endif
	.endm

	.macro	EX_DATA_WP_MAG	cnt, p0, p1, p2, p3, p4, p5, p6, p7,
	.long	WEST_EX_DATA
	.long	\cnt
.if \cnt>0
	.long	\p0
.endif
.if	\cnt>1
	.long	\p1
.endif
.if	\cnt>2
	.long	\p2
.endif
.if	\cnt>3
	.long	\p3
.endif
.if	\cnt>4
	.long	\p4
.endif
.if	\cnt>5
	.long	\p5
.endif
.if	\cnt>6
	.long	\p6
.endif
.if	\cnt>7
	.long	\p7
.endif
	.endm

	.macro	EX_DATA_WP_POS	cnt, p0, p1, p2, p3, p4, p5, p6, p7,
	.long	WEST_EX_DATA
	.long	\cnt
.if \cnt>0
	.long	\p0
.endif
.if	\cnt>1
	.long	\p1
.endif
.if	\cnt>2
	.long	\p2
.endif
.if	\cnt>3
	.long	\p3
.endif
.if	\cnt>4
	.long	\p4
.endif
.if	\cnt>5
	.long	\p5
.endif
.if	\cnt>6
	.long	\p6
.endif
.if	\cnt>7
	.long	\p7
.endif
	.endm

// -----------------------------------------
//
//	リソースの初期化
//
// -----------------------------------------
	.macro	CATS_RES_INIT		res_no, obj_num, r1, r2, r3, r4, r5, r6,
	.long	WEST_CATS_RES_INIT
	.long	\res_no
	.long	\obj_num
	.long	\r1
	.long	\r2
	.long	\r3
	.long	\r4
	.long	\r5
	.long	\r6
	.endm

// -----------------------------------------
//
//	リソースのロード
//
// -----------------------------------------
	.macro	CATS_CAHR_RES_LOAD			res_no, arc_no,
	.long	WEST_CATS_CAHR_RES_LOAD
	.long	\res_no
	.long	\arc_no
	.endm
	
	.macro	CATS_PLTT_RES_LOAD			res_no, arc_no, pal_num,
	.long	WEST_CATS_PLTT_RES_LOAD
	.long	\res_no
	.long	\arc_no
	.long	\pal_num
	.endm
	
	.macro	CATS_CELL_RES_LOAD			res_no, arc_no,
	.long	WEST_CATS_CELL_RES_LOAD
	.long	\res_no
	.long	\arc_no
	.endm
	
	.macro	CATS_CELL_ANM_RES_LOAD		res_no, arc_no,
	.long	WEST_CATS_CELLANM_RES_LOAD
	.long	\res_no
	.long	\arc_no
	.endm


// -----------------------------------------
//
//	アクター登録
//
// -----------------------------------------
	.macro	CATS_ACT_ADD	res_no, sp_func_id, id1, id2, id3, id4, id5, id6, cnt, p0, p1, p2, p3, p4, p5, p6, p7,
	.long	WEST_CATS_ACT_ADD
	.long	\res_no
	.long	\sp_func_id
	.long	\id1
	.long	\id2
	.long	\id3
	.long	\id4
	.long	\id5
	.long	\id6
	.long	\cnt
.if \cnt>0
	.long	\p0
.endif
.if	\cnt>1
	.long	\p1
.endif
.if	\cnt>2
	.long	\p2
.endif
.if	\cnt>3
	.long	\p3
.endif
.if	\cnt>4
	.long	\p4
.endif
.if	\cnt>5
	.long	\p5
.endif
.if	\cnt>6
	.long	\p6
.endif
.if	\cnt>7
	.long	\p7
.endif
	.endm

// -----------------------------------------
//
//	アクターだけ登録
//
// -----------------------------------------
	.macro	CATS_ACT_ADD_EZ	res_no, cap_id, id1, id2, id3, id4, id5, id6
	.long	WEST_CATS_ACT_ADD_EZ
	.long	\res_no
	.long	\cap_id
	.long	\id1
	.long	\id2
	.long	\id3
	.long	\id4
	.long	\id5
	.long	\id6
	.endm


// -----------------------------------------
//
//	リソース解放
//
// -----------------------------------------
	.macro	CATS_RES_FREE		res_no
	.long	WEST_CATS_RES_FREE
	.long	\res_no
	.endm

///< 表示操作
	.macro	POKE_OAM_ENABLE		no, flag
	.long	WEST_POKE_OAM_ENABLE
	.long	\no
	.long	\flag
	.endm

// 相方ドロップTCB作成
	.macro	PT_DROP				type, no, cap_no
	.long	WEST_PT_DROP
	.long	\type
	.long	\no
	.long	\cap_no
	.endm
	
// 通常使う用
	.macro	PT_DROP_EX			flag, type
			POKEOAM_RES_LOAD	WEDEF_POKE_RES_EX
			POKEOAM_DROP		\flag, WEDEF_POKE_AUTO_OFF, WEDEF_POKE_CAP_ID_EX, WEDEF_POKE_RES_EX,
			PT_DROP				\type, 0, WEDEF_POKE_CAP_ID_EX
			.endm
			
	.macro	PT_DROP_EX_2		flag, type, cap_no, res_no,
			POKEOAM_RES_LOAD	\res_no
			POKEOAM_DROP		\flag, WEDEF_POKE_AUTO_OFF, \cap_no, \res_no,
			PT_DROP				\type, 1, \cap_no
			.endm

// 相方ドロップTCB破棄
	.macro	PT_DROP_RESET		no,
	.long	WEST_PT_DROP_RESET
	.long	\no
	.endm
	
	.macro	PT_DROP_RESET_EX
			PT_DROP_RESET 		0
			POKEOAM_DROP_RESET	WEDEF_POKE_CAP_ID_EX
			.endm
			
	.macro	PT_DROP_RESET_EX_2	cap_no
			PT_DROP_RESET 		1
			POKEOAM_DROP_RESET	\cap_no
			.endm
	
	/*
	.macro	SE_REPEAT_C	seID,wait,repeat
	SE_REPEAT	\seID, WAZA_SE_PAN_NM, \wait, \repeat
	.endm
	*/

// -----------------------------------------
//
//	ポケモンをOAMドロップしてる隙に読み込む
//
// -----------------------------------------
	.macro	LOAD_PARTICLE_DROP, ptc_no, data_no
			POKEOAM_RES_INIT
			POKEOAM_RES_LOAD	WEDEF_POKE_RES_0,
			POKEOAM_RES_LOAD	WEDEF_POKE_RES_1,
			POKEOAM_RES_LOAD	WEDEF_POKE_RES_2,
			POKEOAM_RES_LOAD	WEDEF_POKE_RES_3,
			POKEOAM_DROP		WEDEF_DROP_A, WEDEF_POKE_AUTO_OFF, WEDEF_POKE_CAP_ID_0, WEDEF_POKE_RES_0,
			POKEOAM_DROP		WEDEF_DROP_B, WEDEF_POKE_AUTO_OFF, WEDEF_POKE_CAP_ID_1, WEDEF_POKE_RES_1,
			POKEOAM_DROP		WEDEF_DROP_C, WEDEF_POKE_AUTO_OFF, WEDEF_POKE_CAP_ID_2, WEDEF_POKE_RES_2,
			POKEOAM_DROP		WEDEF_DROP_D, WEDEF_POKE_AUTO_OFF, WEDEF_POKE_CAP_ID_3, WEDEF_POKE_RES_3,
			FUNC_CALL			WEST_SP_ALL_DROP, 1, 0
			
			LOAD_PARTICLE		\ptc_no, \data_no
					
			WAIT_FLAG
			
			POKEOAM_RES_FREE
			POKEOAM_DROP_RESET	WEDEF_POKE_CAP_ID_0
			POKEOAM_DROP_RESET	WEDEF_POKE_CAP_ID_1
			POKEOAM_DROP_RESET	WEDEF_POKE_CAP_ID_2
			POKEOAM_DROP_RESET	WEDEF_POKE_CAP_ID_3
	.endm

//
//	通常コマンド		ココまで
//
// ----------------------------------------------------------------------------
//
//	デバッグコマンド	ココから
//

// -----------------------------------------
//
//	キー待ち
//
// -----------------------------------------
	.macro	KEY_WAIT
	.long	WEST_KEY_WAIT
	.endm

